

#### [RFC PATCH v1 0/5] s390: more vfio-ccw code rework
##### From: Eric Farman <farman@linux.ibm.com>

```c

A couple little improvements to the malloc load in vfio-ccw.
Really, there were just (the first) two patches, but then I
got excited and added a few stylistic ones to the end.

The routine ccwchain_calc_length() has this basic structure:

  ccwchain_calc_length
    a0 = kcalloc(CCWCHAIN_LEN_MAX, sizeof(struct ccw1))
    copy_ccw_from_iova(a0, src)
      copy_from_iova
        pfn_array_alloc
          b = kcalloc(len, sizeof(*pa_iova_pfn + *pa_pfn)
        pfn_array_pin
          vfio_pin_pages
        memcpy(a0, src)
        pfn_array_unpin_free
          vfio_unpin_pages
          kfree(b)
    kfree(a0)

We do this EVERY time we process a new channel program chain,
meaning at least once per SSCH and more if TICs are involved,
to figure out how many CCWs are chained together.  Once that
is determined, a new piece of memory is allocated (call it a1)
and then passed to copy_ccw_from_iova() again, but for the
value calculated by ccwchain_calc_length().

This seems inefficient.

Patch 1 moves the malloc of a0 from the CCW processor to the
initialization of the device.  Since only one SSCH can be
handled concurrently, we can use this space safely to
determine how long the chain being processed actually is.

Patch 2 then removes the second copy_ccw_from_iova() call
entirely, and replaces it with a memcpy from a0 to a1.  This
is done before we process a TIC and thus a second chain, so
there is no overlap in the storage in channel_program.

Patches 3-5 clean up some things that aren't as clear as I'd
like, but didn't want to pollute the first two changes.
For example, patch 3 moves the population of guest_cp to the
same routine that copies from it, rather than in a called
function.  Meanwhile, patch 4 (and thus, 5) was something I
had lying around for quite some time, because it looked to
be structured weird.  Maybe that's one bridge too far.

Eric Farman (5):
  vfio-ccw: Move guest_cp storage into common struct
  vfio-ccw: Skip second copy of guest cp to host
  vfio-ccw: Copy CCW data outside length calculation
  vfio-ccw: Factor out the ccw0-to-ccw1 transition
  vfio-ccw: Remove copy_ccw_from_iova()

 drivers/s390/cio/vfio_ccw_cp.c  | 108 +++++++++++---------------------
 drivers/s390/cio/vfio_ccw_cp.h  |   7 +++
 drivers/s390/cio/vfio_ccw_drv.c |   7 +++
 3 files changed, 52 insertions(+), 70 deletions(-)
```
#### [PATCH v9 00/17] x86/split_lock: Enable split lock detection
##### From: Fenghua Yu <fenghua.yu@intel.com>

```c

==Introduction==

A split lock is any atomic operation whose operand crosses two cache
lines. Since the operand spans two cache lines and the operation must
be atomic, the system locks the bus while the CPU accesses the two cache
lines.

During bus locking, request from other CPUs or bus agents for control
of the bus are blocked. Blocking bus access from other CPUs plus
overhead of configuring bus locking protocol degrade not only performance
on one CPU but also overall system performance.

If the operand is cacheable and completely contained in one cache line,
the atomic operation is optimized by less expensive cache locking on
Intel P6 and recent processors. If a split lock operation is detected
and a developer fixes the issue so that the operand can be operated in one
cache line, cache locking instead of more expensive bus locking will be
used for the atomic operation. Removing the split lock can improve overall
performance.

Instructions that may cause split lock issue include lock add, lock btc,
xchg, lsl, far call, ltr, etc.

More information about split lock, bus locking, and cache locking can be
found in the latest Intel 64 and IA-32 Architecture Software Developer's
Manual.

==Split lock detection==

Currently Linux can trace split lock event counter sq_misc.split_lock
for debug purpose. But for system deployed in the field, this event
counter after the fact is insufficient. We need a mechanism that
detects split lock before it happens to ensure that bus lock is never
incurred due to split lock.

Intel introduces a mechanism to detect split lock via Alignment Check
(#AC) exception before badly aligned atomic instructions might impact
whole system performance in Tremont and other future processors. 

This capability is critical for real time system designers who build
consolidated real time systems. These systems run hard real time
code on some cores and run "untrusted" user processes on some
other cores. The hard real time cannot afford to have any bus lock from
the untrusted processes to hurt real time performance. To date the
designers have been unable to deploy these solutions as they have no
way to prevent the "untrusted" user code from generating split lock and
bus lock to block the hard real time code to access memory during bus
locking.

This capability may also find usage in cloud. A user process with split
lock running in one guest can block other cores from accessing shared
memory during its split locked memory access. That may cause overall
system performance degradation.

Split lock may open a security hole where malicious user code may slow
down overall system by executing instructions with split lock.

==Enumerate split lock detection feature==

A control bit (bit 29) in MSR_TEST_CTL (0x33) will be introduced in
future x86 processors. When the bit 29 is set, the processor causes
#AC exception for split locked accesses at all CPL.

The split lock detection feature is enumerated through bit 5 in
MSR_IA32_CORE_CAPABILITY (0xcf). The MSR 0xcf itself is enumerated by
CPUID.(EAX=0x7,ECX=0):EDX[30].

The enumeration method is published in the latest Intel 64 and IA-32
Architecture Software Developer's Manual.

A few processors have the split lock detection feature. But they don't
have MSR_IA32_CORE_CAPABILITY to enumerate the feature. On those
processors, enumerate the split lock detection feature based on their
family/model/stepping numbers.

==Handle split lock===

There may be different considerations to handle split lock, e.g. how
to handle split lock issue in firmware after kernel enables the feature.

But this patch set uses a simple way to handle split lock which is
suggested by Thomas Gleixner and Dave Hansen:

- If split lock happens in kernel, a warning is issued and split lock
detection is disabled on the current CPU. The split lock issue should
be fixed in kernel.

- If split lock happens in user process, the process is killed by
SIGBUS. Unless the issue is fixed, the process cannot run in the
system.

- If split lock happens in firmware, system may hang in firmware. The
issue should be fixed in firmware.

- Enable split lock detection by default once the feature is enumerated.

- Disable split lock detection by kernel parameter "nosplit_lock_detect"
during boot time.

- Disable/enable split lock detection by debugfs interface
/sys/kernel/debug/x86/split_lock_detect during run time.

==Expose to guest==

To expose split lock detection to guest, it needs to
 1. Report the new CPUID bit to guest.
 2. Emulate IA32_CORE_CAPABILITIES MSR.
 3. Emulate TEST_CTL MSR.

To avoid  malicious guest from using split lock to produce a slowdown attack,
making the following policy:
 - If the host kernel has it enabled then the guest is not allowed to
change it.
 - If the host kernel has it disabled then the guest can enable it for
it's own purposes.

Accordingly, injecting #AC back to guest only when guest can handle it.

==Patches==
Patch 0001-0003: Fix a few existing split lock issues.
Patch 0004-0008: Enumerate features and define MSR_TEST_CTL.
Patch 0009: Handle #AC for split lock.
Patch 0010-0011: Enable split lock detection in KVM.
Patch 0012: Enable split lock detection by default after #AC handler and KVM 
are installed.
Patch 0013: Disable split lock detection by kernel parameter
"nosplit_lock_detect" during boot time.
Patch 0014-0015: Define a debugfs interface to enable/disable split lock
detection during run time.
Patch 0016-0017: Warn if addr is unaligned to unsigned long in atomic
ops xxx_bit().

==Changelog==
v9:
Address Thomas Gleixner's comments:
- wrmsr() in split_lock_update_msr() to spare RMW
- Print warnings in atomic bit operations xxx_bit() if the address is
unaligned to unsigned long.
- When host enables split lock detection, forcing it enabled for guest.
- Using the msr_test_ctl_mask to decide which bits need to be switched in
atomic_switch_msr_test_ctl().
- Warn if addr is unaligned to unsigned long in atomic ops xxx_bit().

Address Ingo Molnar's comments:
- Follow right MSR register and bits naming convention
- Use right naming convention for variables and functions
- Use split_lock_debug for atomic opertions of WARN_ONCE in #AC handler
and split_lock_detect_wr();
- Move the sysfs interface to debugfs interface /sys/kernel/debug/x86/
split_lock_detect

Other fixes:
- update vmx->msr_test_ctl_mask when changing MSR_IA32_CORE_CAP.
- Support resume from suspend/hibernation

- The split lock fix patch (#0003) for wlcore wireless driver is
upstreamed. So remove the patch from this patch set.

v8:
Address issues pointed out by Thomas Gleixner:
- Remove all "clearcpuid=" related patches.
- Add kernel parameter "nosplit_lock_detect" patch.
- Merge definition and initialization of msr_test_ctl_cache into #AC
  handling patch which first uses the variable.
- Add justification for the sysfs knob and combine function and doc
  patches into one patch 0015.
- A few other adjustments.

v7:
- Add per cpu variable to cach MSR TEST_CTL. Suggested by Thomas Gleixner.
- Change a few other changes including locking, simplifying code, work
flow, KVM fixes, etc. Suggested by Thomas Gleixner.
- Fix KVM issues pointed out by Sean Christopherson.

v6:
- Fix #AC handler issues pointed out by Dave Hansen
- Add doc for the sysfs interface pointed out by Dave Hansen
- Fix a lock issue around wrmsr during split lock init, pointed out by Dave
  Hansen
- Update descriptions and comments suggested by Dave Hansen
- Fix __le32 issue in wlcore raised by Kalle Valo
- Add feature enumeration based on family/model/stepping for Icelake mobile

v5:
- Fix wlcore issue from Paolo Bonzini
- Fix b44 issue from Peter Zijlstra
- Change init sequence by Dave Hansen
- Fix KVM issues from Paolo Bonzini
- Re-order patch sequence

v4:
- Remove "setcpuid=" option
- Enable IA32_CORE_CAPABILITY enumeration for split lock
- Handle CPUID faulting by Peter Zijlstra
- Enable /sys interface to enable/disable split lock detection

v3:
- Handle split lock as suggested by Thomas Gleixner.
- Fix a few potential spit lock issues suggested by Thomas Gleixner.
- Support kernel option "setcpuid=" suggested by Dave Hanson and Thomas
Gleixner.
- Support flag string in "clearcpuid=" suggested by Dave Hanson and
Thomas Gleixner.

v2:
- Remove code that handles split lock issue in firmware and fix
x86_capability issue mainly based on comments from Thomas Gleixner and
Peter Zijlstra.

In previous version:
Comments from Dave Hansen:
- Enumerate feature in X86_FEATURE_SPLIT_LOCK_AC
- Separate #AC handler from do_error_trap
- Use CONFIG to configure inherit BIOS setting, enable, or disable split
  lock. Remove kernel parameter "split_lock_ac="
- Change config interface to debugfs from sysfs
- Fix a few bisectable issues
- Other changes.

Comment from Tony Luck and Dave Hansen:
- Dump right information in #AC handler

Comment from Alan Cox and Dave Hansen:
- Description of split lock in patch 0

Others:
- Remove tracing because we can trace split lock in existing
  sq_misc.split_lock.
- Add CONFIG to configure either panic or re-execute faulting instruction
  for split lock in kernel.
- other minor changes.

Fenghua Yu (13):
  x86/common: Align cpu_caps_cleared and cpu_caps_set to unsigned long
  x86/split_lock: Align x86_capability to unsigned long to avoid split
    locked access
  x86/msr-index: Define MSR_IA32_CORE_CAP and split lock detection bit
  x86/cpufeatures: Enumerate MSR_IA32_CORE_CAP
  x86/split_lock: Enumerate split lock detection by MSR_IA32_CORE_CAP
  x86/split_lock: Enumerate split lock detection on Icelake mobile
    processor
  x86/split_lock: Define MSR TEST_CTL register
  x86/split_lock: Handle #AC exception for split lock
  x86/split_lock: Enable split lock detection by default
  x86/split_lock: Disable split lock detection by kernel parameter
    "nosplit_lock_detect"
  x86/split_lock: Add a debugfs interface to enable/disable split lock
    detection during run time
  x86/split_lock: Add documentation for split lock detection interface
  x86/split_lock: Warn on unaligned address in atomic bit operations

Peter Zijlstra (1):
  drivers/net/b44: Align pwol_mask to unsigned long for better
    performance

Sai Praneeth Prakhya (1):
  x86/split_lock: Reorganize few header files in order to call
    WARN_ON_ONCE() in atomic bit ops

Xiaoyao Li (2):
  kvm/x86: Emulate MSR IA32_CORE_CAPABILITY
  kvm/vmx: Emulate MSR TEST_CTL

 Documentation/ABI/testing/debugfs-x86         |  21 ++
 .../admin-guide/kernel-parameters.txt         |   2 +
 arch/microblaze/kernel/cpu/pvr.c              |   1 +
 arch/mips/ralink/mt7620.c                     |   1 +
 arch/powerpc/include/asm/cmpxchg.h            |   1 +
 arch/x86/include/asm/bitops.h                 |  16 ++
 arch/x86/include/asm/cpu.h                    |   8 +
 arch/x86/include/asm/cpufeatures.h            |   2 +
 arch/x86/include/asm/kvm_host.h               |   1 +
 arch/x86/include/asm/msr-index.h              |   8 +
 arch/x86/include/asm/processor.h              |   4 +-
 arch/x86/kernel/cpu/common.c                  |   7 +-
 arch/x86/kernel/cpu/cpuid-deps.c              |  79 +++----
 arch/x86/kernel/cpu/intel.c                   | 216 ++++++++++++++++++
 arch/x86/kernel/traps.c                       |  43 +++-
 arch/x86/kvm/cpuid.c                          |   6 +
 arch/x86/kvm/vmx/vmx.c                        |  92 +++++++-
 arch/x86/kvm/vmx/vmx.h                        |   2 +
 arch/x86/kvm/x86.c                            |  39 ++++
 arch/xtensa/include/asm/traps.h               |   1 +
 .../dvb-frontends/cxd2880/cxd2880_common.c    |   2 +
 drivers/net/ethernet/broadcom/b44.c           |   4 +-
 .../net/ethernet/freescale/fman/fman_muram.c  |   1 +
 drivers/soc/renesas/rcar-sysc.h               |   2 +-
 drivers/staging/fwserial/dma_fifo.c           |   1 +
 include/linux/assoc_array_priv.h              |   1 +
 include/linux/ata.h                           |   1 +
 include/linux/gpio/consumer.h                 |   1 +
 include/linux/iommu-helper.h                  |   1 +
 include/linux/kernel.h                        |   4 -
 include/linux/sched.h                         |   1 +
 kernel/bpf/tnum.c                             |   1 +
 lib/clz_ctz.c                                 |   1 +
 lib/errseq.c                                  |   1 +
 lib/flex_proportions.c                        |   1 +
 lib/hexdump.c                                 |   1 +
 lib/lz4/lz4defs.h                             |   1 +
 lib/math/div64.c                              |   1 +
 lib/math/gcd.c                                |   1 +
 lib/math/reciprocal_div.c                     |   1 +
 lib/siphash.c                                 |   1 +
 net/netfilter/nf_conntrack_h323_asn1.c        |   1 +
 42 files changed, 527 insertions(+), 53 deletions(-)
 create mode 100644 Documentation/ABI/testing/debugfs-x86
```
