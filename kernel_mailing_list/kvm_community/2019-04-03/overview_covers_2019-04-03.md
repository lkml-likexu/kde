

#### [PATCH v4 0/5] virtio pmem driver 
##### From: Pankaj Gupta <pagupta@redhat.com>

```c

This patch series has implementation for "virtio pmem". 
 "virtio pmem" is fake persistent memory(nvdimm) in guest 
 which allows to bypass the guest page cache. This also
 implements a VIRTIO based asynchronous flush mechanism.  
 
 Sharing guest kernel driver in this patchset with the 
 changes suggested in v3. Tested with Qemu side device 
 emulation [6] for virtio-pmem. 

 We have incorporated all the suggestions in V3. Documented 
 the impact of possible page cache side channel attacks with 
 suggested countermeasures.
 
 Details of project idea for 'virtio pmem' flushing interface 
 is shared [3] & [4].

 Implementation is divided into two parts:
 New virtio pmem guest driver and qemu code changes for new 
 virtio pmem paravirtualized device.

1. Guest virtio-pmem kernel driver
---------------------------------
   - Reads persistent memory range from paravirt device and 
     registers with 'nvdimm_bus'.  
   - 'nvdimm/pmem' driver uses this information to allocate 
     persistent memory region and setup filesystem operations 
     to the allocated memory. 
   - virtio pmem driver implements asynchronous flushing 
     interface to flush from guest to host.

2. Qemu virtio-pmem device
---------------------------------
   - Creates virtio pmem device and exposes a memory range to 
     KVM guest. 
   - At host side this is file backed memory which acts as 
     persistent memory. 
   - Qemu side flush uses aio thread pool API's and virtio 
     for asynchronous guest multi request handling. 

   David Hildenbrand CCed also posted a modified version[7] of 
   qemu virtio-pmem code based on updated Qemu memory device API. 

 Virtio-pmem security implications and countermeasures:
 -----------------------------------------------------

 In previous posting of kernel driver, there was discussion [9]
 on possible implications of page cache side channel attacks with 
 virtio pmem. After thorough analysis of details of known side 
 channel attacks, below are the suggestions:

 - Depends entirely on how host backing image file is mapped 
   into guest address space. 

 - virtio-pmem device emulation, by default shared mapping is used
   to map host backing file. It is recommended to use separate
   backing file at host side for every guest. This will prevent
   any possibility of executing common code from multiple guests
   and any chance of inferring guest local data based based on 
   execution time.

 - If backing file is required to be shared among multiple guests 
   it is recommended to don't support host page cache eviction 
   commands from the guest driver. This will avoid any possibility
   of inferring guest local data or host data from another guest. 

 - Proposed device specification [8] for virtio-pmem device with 
   details of possible security implications and suggested 
   countermeasures for device emulation.

 Virtio-pmem errors handling:
 ----------------------------------------
  Checked behaviour of virtio-pmem for below types of errors
  Need suggestions on expected behaviour for handling these errors?

  - Hardware Errors: Uncorrectable recoverable Errors: 
  a] virtio-pmem: 
    - As per current logic if error page belongs to Qemu process, 
      host MCE handler isolates(hwpoison) that page and send SIGBUS. 
      Qemu SIGBUS handler injects exception to KVM guest. 
    - KVM guest then isolates the page and send SIGBUS to guest 
      userspace process which has mapped the page. 
  
  b] Existing implementation for ACPI pmem driver: 
    - Handles such errors with MCE notifier and creates a list 
      of bad blocks. Read/direct access DAX operation return EIO 
      if accessed memory page fall in bad block list.
    - It also starts backgound scrubbing.  
    - Similar functionality can be reused in virtio-pmem with MCE 
      notifier but without scrubbing(no ACPI/ARS)? Need inputs to 
      confirm if this behaviour is ok or needs any change?

Changes from PATCH v3: [1]

- Use generic dax_synchronous() helper to check for DAXDEV_SYNC 
  flag - [Dan, Darrick, Jan]
- Add 'is_nvdimm_async' function
- Document page cache side channel attacks implications & 
  countermeasures - [Dave Chinner, Michael]

Changes from PATCH v2: [2]
- Disable MAP_SYNC for ext4 & XFS filesystems - [Dan] 
- Use name 'virtio pmem' in place of 'fake dax' 

Changes from PATCH v1: 
- 0-day build test for build dependency on libnvdimm 

 Changes suggested by - [Dan Williams]
- Split the driver into two parts virtio & pmem  
- Move queuing of async block request to block layer
- Add "sync" parameter in nvdimm_flush function
- Use indirect call for nvdimm_flush
- Don’t move declarations to common global header e.g nd.h
- nvdimm_flush() return 0 or -EIO if it fails
- Teach nsio_rw_bytes() that the flush can fail
- Rename nvdimm_flush() to generic_nvdimm_flush()
- Use 'nd_region->provider_data' for long dereferencing
- Remove virtio_pmem_freeze/restore functions
- Remove BSD license text with SPDX license text

- Add might_sleep() in virtio_pmem_flush - [Luiz]
- Make spin_lock_irqsave() narrow

Changes from RFC v3
- Rebase to latest upstream - Luiz
- Call ndregion->flush in place of nvdimm_flush- Luiz
- kmalloc return check - Luiz
- virtqueue full handling - Stefan
- Don't map entire virtio_pmem_req to device - Stefan
- request leak, correct sizeof req- Stefan
- Move declaration to virtio_pmem.c

Changes from RFC v2:
- Add flush function in the nd_region in place of switching
  on a flag - Dan & Stefan
- Add flush completion function with proper locking and wait
  for host side flush completion - Stefan & Dan
- Keep userspace API in uapi header file - Stefan, MST
- Use LE fields & New device id - MST
- Indentation & spacing suggestions - MST & Eric
- Remove extra header files & add licensing - Stefan

Changes from RFC v1:
- Reuse existing 'pmem' code for registering persistent 
  memory and other operations instead of creating an entirely 
  new block driver.
- Use VIRTIO driver to register memory information with 
  nvdimm_bus and create region_type accordingly. 
- Call VIRTIO flush from existing pmem driver.

Pankaj Gupta (5):
   libnvdimm: nd_region flush callback support
   virtio-pmem: Add virtio-pmem guest driver
   libnvdimm: add nd_region buffered dax_dev flag
   ext4: disable map_sync for virtio pmem
   xfs: disable map_sync for virtio pmem

[1] https://lkml.org/lkml/2019/1/9/471
[2] https://lkml.org/lkml/2018/10/13/117
[3] https://www.spinics.net/lists/kvm/msg149761.html
[4] https://www.spinics.net/lists/kvm/msg153095.html  
[5] https://lkml.org/lkml/2018/8/31/413
[6] https://marc.info/?l=linux-kernel&m=153572228719237&w=2 
[7] https://marc.info/?l=qemu-devel&m=153555721901824&w=2
[8] https://lists.oasis-open.org/archives/virtio-dev/201903/msg00083.html
```
#### [PATCH v6 00/20] x86/split_lock: Enable split locked accesses
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
Patch 5-9: Enumerate features and define MSR_TEST_CTL.
Patch 10: Handle #AC for split lock
Patch 11-12: Enable split lock detection in KVM.
Patch 13: Enable #AC for split lock by default after #AC handler and KVM
are installed
Patch 14-15: Define a sysfs interface to enable/disable split lock
detection
Patch 16-20: Extend "clearcpuid=" option.

==Changelog==
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

Fenghua Yu (15):
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
  x86/split_lock: Define MSR_TEST_CTL register
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

 .../ABI/testing/sysfs-devices-system-cpu      |  15 ++
 .../admin-guide/kernel-parameters.txt         |  18 +-
 arch/x86/include/asm/cmdline.h                |   3 +
 arch/x86/include/asm/cpu.h                    |   7 +
 arch/x86/include/asm/cpufeature.h             |   5 +
 arch/x86/include/asm/cpufeatures.h            |   2 +
 arch/x86/include/asm/kvm_host.h               |   2 +
 arch/x86/include/asm/msr-index.h              |   7 +
 arch/x86/include/asm/processor.h              |   4 +-
 arch/x86/kernel/cpu/common.c                  |  14 +-
 arch/x86/kernel/cpu/cpuid-deps.c              | 157 ++++++++++----
 arch/x86/kernel/cpu/intel.c                   | 195 +++++++++++++++++-
 arch/x86/kernel/cpu/scattered.c               |  17 ++
 arch/x86/kernel/fpu/init.c                    |  33 ++-
 arch/x86/kernel/process.c                     |   3 +
 arch/x86/kernel/traps.c                       |  54 ++++-
 arch/x86/kvm/cpuid.c                          |   6 +
 arch/x86/kvm/vmx/vmx.c                        |  35 ++++
 arch/x86/kvm/vmx/vmx.h                        |   1 +
 arch/x86/kvm/x86.c                            |  39 ++++
 arch/x86/lib/cmdline.c                        |  17 +-
 drivers/net/ethernet/broadcom/b44.c           |   4 +-
 drivers/net/wireless/ti/wlcore/cmd.c          |  15 +-
 drivers/net/wireless/ti/wlcore/wlcore.h       |   4 +-
 24 files changed, 577 insertions(+), 80 deletions(-)
```
