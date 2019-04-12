

#### [PATCH 0/7] KVM: s390: new guest facilities
##### From: Christian Borntraeger <borntraeger@de.ibm.com>

```c

Here is support for new guest cpu facilities.

Christian Borntraeger (7):
  KVM: s390: add vector enhancements facility 2 to cpumodel
  KVM: s390: add vector BCD enhancements facility to cpumodel
  KVM: s390: add MSA9 to cpumodel
  KVM: s390: enable MSA9 keywrapping functions depending on cpu model
  KVM: s390: provide query function for instructions returning 32 byte
  KVM: s390: add enhanced sort facilty to cpu model
  KVM: s390: add deflate conversion facilty to cpu model

 Documentation/virtual/kvm/devices/vm.txt |  3 +-
 arch/s390/include/asm/cpacf.h            |  1 +
 arch/s390/include/asm/kvm_host.h         |  1 +
 arch/s390/include/uapi/asm/kvm.h         |  5 +-
 arch/s390/kvm/kvm-s390.c                 | 77 ++++++++++++++++++++++++
 arch/s390/tools/gen_facilities.c         |  3 +
 tools/arch/s390/include/uapi/asm/kvm.h   |  3 +-
 7 files changed, 90 insertions(+), 3 deletions(-)
```
#### [PATCH v4 0/4] KVM: lapic: Fix a variety of timer adv issues
##### From: Sean Christopherson <sean.j.christopherson@intel.com>

```c

KVM's recently introduced adaptive tuning of lapic_timer_advance_ns has
several critical flaws:

  - The advancement is completely unbounded, e.g. there's nothing in the
    logic that prevents the advancement from creeping up to hundreds of
    milliseconds in case something goes awry with the guest's TSC.

  - TSC scaling is done on a per-vCPU basis, while the advancement value
    is global.  This issue is also present without adaptive tuning, but
    is now more pronounced.

  - Tuning the value concurrently on multiple CPUs can corrupt the
    advancement variable.

  - Userspace can't disable adaptive tuning.

Fix the above issues along with a theoretical bug found by inspenction,
where the wait_lapic_timer() delay could be inaccurate when the guest
TSC is running at a different ratio than the host's TSC.

v4:
 - Rebase to latest kvm/queue.
 - Kill the timer advancement if adaptive tuning goes above the
   abrbitrary threshold of 5000ns. [Paolo].
 - Revert back to disabling adaptive tuning via the existing param,
   except use '-1' as the "use adaptive tuning" indicator. [Paolo].
 - Do the conversion to nanoseconds when delaying iff the guest TSC
   is running at a different ratio, and move the patch to the end
   so that the other patches are not dependent on it since it's not
   100% clear (to me) that the conversion is correct/necessary.

v3:
 - https://patchwork.kernel.org/cover/10904163/
 - Split the refactoring of start_hv_timer() and ->set_hv_timer
   into three separate patches instead of attempting to do a big
   refactor in a single patch to fix three separate issues.
    - Explicitly cancel the hv timer to avoid
    - Use a param for "expired" instead of overloading the return
      value of ->set_hv_timer().
    - Check for a pending non-periodic in restart_apic_timer(). [Liran]
 - Add more Reviewed-by tags.

v2:
 - https://patchwork.kernel.org/cover/10903613/
 - Add explicit param to control automatic tuning. [Liran]
 - Document the effect of per-vCPU tracking on the module params.
 - Use fancy math to convert guest clockcycles to host nanoseconds
   instead of brute forcing the delay with a for loop. [Liran]
 - Refactor start_hv_timer()'s return semantics to move the "expired
   timer" handling up a level. [Liran and Paolo]
 - Add Liran's Reviewed-by tags.

v1: https://patchwork.kernel.org/cover/10899101/

Sean Christopherson (4):
  KVM: lapic: Disable timer advancement if adaptive tuning goes haywire
  KVM: lapic: Track lapic timer advance per vCPU
  KVM: lapic: Allow user to disable adaptive tuning of timer advancement
  KVM: lapic: Convert guest TSC to host time domain if necessary

 arch/x86/kvm/lapic.c   | 61 +++++++++++++++++++++++++++++++-----------
 arch/x86/kvm/lapic.h   |  4 ++-
 arch/x86/kvm/vmx/vmx.c |  4 ++-
 arch/x86/kvm/x86.c     | 14 ++++++----
 arch/x86/kvm/x86.h     |  2 --
 5 files changed, 61 insertions(+), 24 deletions(-)
```
#### [PATCH v7 00/21] x86/split_lock: Enable split lock detection
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

- Disable split lock detection by "clearcpuid=split_lock_detect" during
boot time.

- Disable/enable split lock detection by interface
/sys/devices/system/cpu/split_lock_detect during run time.

==Expose to guest==

To expose this feature to guest, need to
1. Report the new CPUID bit to guest.
2. Emulate IA32_CORE_CAPABILITIES MSR.
3. Emulate TEST_CTL MSR. Since this patch series enable split lock
detection in host kernel by default, if do not emulate MSR_TEST_CTL
for guest, guest will run with the value set by host without knowing
that. So guest will run with split lock detection enabled due to the
host's value. Thus guest running with buggy firmware and old kernel
will fail because they lack the ability to handle #AC for split lock.
So need to emulate MSR_TEST_CTL and separate its value between host
and guest.

==Patches==
Patch 1-4: Fix a few existing split lock issues.
Patch 5-10: Enumerate features and define MSR_TEST_CTL.
Patch 11: Handle #AC for split lock
Patch 12-13: Enable split lock detection in KVM.
Patch 14: Enable split lock detection by default after #AC handler and KVM
are installed
Patch 15-16: Define a sysfs interface to enable/disable split lock
detection
Patch 17-21: Extend "clearcpuid=" option.

==Changelog==
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

Fenghua Yu (16):
  x86/common: Align cpu_caps_cleared and cpu_caps_set to unsigned long
  x86/split_lock: Align x86_capability to unsigned long to avoid split
    locked access
  x86/msr-index: Define MSR_IA32_CORE_CAPABILITY and split lock
    detection bit
  x86/cpufeatures: Enumerate MSR_IA32_CORE_CAPABILITY
  x86/split_lock: Enumerate split lock detection by
    MSR_IA32_CORE_CAPABILITY
  x86/split_lock: Enumerate split lock detection on Icelake mobile
    processor
  x86/split_lock: Define MSR TEST_CTL register
  x86/split_lock: Define per CPU variable to cache MSR TEST_CTL
  x86/split_lock: Handle #AC exception for split lock
  x86/split_lock: Enable split lock detection by default
  x86/split_lock: Add a sysfs interface to enable/disable split lock
    detection during run time
  x86/split_lock: Document the new sysfs file for split lock detection
  x86/clearcpuid: Support multiple clearcpuid options
  x86/clearcpuid: Support feature flag string in kernel option
    clearcpuid
  x86/clearcpuid: Apply cleared feature bits that are forced set before
  x86/clearcpuid: Change document for kernel option clearcpuid

Paolo Bonzini (1):
  wlcore: simplify/fix/optimize reg_ch_conf_pending operations

Peter Zijlstra (2):
  drivers/net/b44: Align pwol_mask to unsigned long for better
    performance
  x86/clearcpuid: Clear CPUID bit in CPUID faulting

Xiaoyao Li (2):
  kvm/x86: Emulate MSR IA32_CORE_CAPABILITY
  kvm/vmx: Emulate MSR TEST_CTL

 .../ABI/testing/sysfs-devices-system-cpu      |  22 +++
 .../admin-guide/kernel-parameters.txt         |  18 +-
 arch/x86/include/asm/cmdline.h                |   3 +
 arch/x86/include/asm/cpu.h                    |   8 +
 arch/x86/include/asm/cpufeature.h             |   5 +
 arch/x86/include/asm/cpufeatures.h            |   2 +
 arch/x86/include/asm/kvm_host.h               |   1 +
 arch/x86/include/asm/msr-index.h              |   7 +
 arch/x86/include/asm/processor.h              |   4 +-
 arch/x86/kernel/cpu/common.c                  |  14 +-
 arch/x86/kernel/cpu/cpuid-deps.c              | 157 ++++++++++++----
 arch/x86/kernel/cpu/intel.c                   | 169 +++++++++++++++++-
 arch/x86/kernel/cpu/scattered.c               |  17 ++
 arch/x86/kernel/fpu/init.c                    |  33 ++--
 arch/x86/kernel/process.c                     |   3 +
 arch/x86/kernel/traps.c                       |  46 ++++-
 arch/x86/kvm/cpuid.c                          |   6 +
 arch/x86/kvm/vmx/vmx.c                        |  42 +++++
 arch/x86/kvm/vmx/vmx.h                        |   2 +
 arch/x86/kvm/x86.c                            |  39 ++++
 arch/x86/lib/cmdline.c                        |  17 +-
 drivers/net/ethernet/broadcom/b44.c           |   4 +-
 drivers/net/wireless/ti/wlcore/cmd.c          |  15 +-
 drivers/net/wireless/ti/wlcore/wlcore.h       |   4 +-
 24 files changed, 558 insertions(+), 80 deletions(-)
```
