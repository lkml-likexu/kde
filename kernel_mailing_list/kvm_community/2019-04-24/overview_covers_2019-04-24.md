

#### [PATCH v2 0/7] KVM: s390: new guest facilities 
##### From: Christian Borntraeger <borntraeger@de.ibm.com>

```c

Here is support for new guest cpu facilities.

v1->v2: rework keywrapping patch (now the last one)
	- vsie
	- also check for aes keywrapping
	- add helper functions 

Christian Borntraeger (7):
  KVM: s390: add vector enhancements facility 2 to cpumodel
  KVM: s390: add vector BCD enhancements facility to cpumodel
  KVM: s390: add MSA9 to cpumodel
  KVM: s390: provide query function for instructions returning 32 byte
  KVM: s390: add enhanced sort facilty to cpu model
  KVM: s390: add deflate conversion facilty to cpu model
  KVM: s390: enable MSA9 keywrapping functions depending on cpu model

 Documentation/virtual/kvm/devices/vm.txt |   3 +-
 arch/s390/include/asm/cpacf.h            |   1 +
 arch/s390/include/asm/kvm_host.h         |   1 +
 arch/s390/include/uapi/asm/kvm.h         |   5 +-
 arch/s390/kvm/kvm-s390.c                 | 103 ++++++++++++++++++++++-
 arch/s390/kvm/vsie.c                     |   5 +-
 arch/s390/tools/gen_facilities.c         |   3 +
 tools/arch/s390/include/uapi/asm/kvm.h   |   3 +-
 8 files changed, 119 insertions(+), 5 deletions(-)
```
#### [RFC PATCH v1 00/10] Add AMD SEV guest live migration support
##### From: "Singh, Brijesh" <brijesh.singh@amd.com>

```c

The series add support for AMD SEV guest live migration commands. To protect the
confidentiality of an SEV protected guest memory while in transit we need to
use the SEV commands defined in SEV API spec [1].

SEV guest VMs have the concept of private and shared memory. Private memory
is encrypted with the guest-specific key, while shared memory may be encrypted
with hypervisor key. The commands provided by the SEV FW are meant to be used
for the private memory only. The patch series introduces a new hypercall.
The guest OS can use this hypercall to notify the page encryption status.
If the page is encrypted with guest specific-key then we use SEV command during
the migration. If page is not encrypted then fallback to default.

The patch adds a new ioctl KVM_GET_PAGE_ENC_BITMAP. The ioctl can be used
by the qemu to get the page encrypted bitmap. Qemu can consult this bitmap
during the migration to know whether the page is encrypted.

[1] https://developer.amd.com/wp-content/resources/55766.PDF

The series is tested with the Qemu, I am in process of cleaning
up the Qemu code and will submit soon.

While implementing the migration I stumbled on the follow question:

- Since there is a guest OS changes required to support the migration,
  so how do we know whether guest OS is updated? Should we extend KVM
  capabilities/feature bits to check this?

TODO:
 - add an ioctl to build encryption bitmap. The encryption bitmap is built during
   the guest bootup/execution. We should provide an ioctl so that destination
   can build the bitmap as it receives the pages. 
 - reset the bitmap on guest reboot.

The complete tree with patch is available at:
https://github.com/codomania/kvm/tree/sev-migration-rfc-v1

Cc: Thomas Gleixner <tglx@linutronix.de>
Cc: Ingo Molnar <mingo@redhat.com>
Cc: "H. Peter Anvin" <hpa@zytor.com>
Cc: Paolo Bonzini <pbonzini@redhat.com>
Cc: "Radim Krčmář" <rkrcmar@redhat.com>
Cc: Joerg Roedel <joro@8bytes.org>
Cc: Borislav Petkov <bp@suse.de>
Cc: Tom Lendacky <thomas.lendacky@amd.com>
Cc: x86@kernel.org
Cc: kvm@vger.kernel.org
Cc: linux-kernel@vger.kernel.org

Brijesh Singh (10):
  KVM: SVM: Add KVM_SEV SEND_START command
  KVM: SVM: Add KVM_SEND_UPDATE_DATA command
  KVM: SVM: Add KVM_SEV_SEND_FINISH command
  KVM: SVM: Add support for KVM_SEV_RECEIVE_START command
  KVM: SVM: Add KVM_SEV_RECEIVE_UPDATE_DATA command
  KVM: SVM: Add KVM_SEV_RECEIVE_FINISH command
  KVM: x86: Add AMD SEV specific Hypercall3
  KVM: X86: Introduce KVM_HC_PAGE_ENC_STATUS hypercall
  KVM: x86: Introduce KVM_GET_PAGE_ENC_BITMAP ioctl
  mm: x86: Invoke hypercall when page encryption status is changed

 .../virtual/kvm/amd-memory-encryption.rst     | 116 ++++
 Documentation/virtual/kvm/hypercalls.txt      |  14 +
 arch/x86/include/asm/kvm_host.h               |   3 +
 arch/x86/include/asm/kvm_para.h               |  12 +
 arch/x86/include/asm/mem_encrypt.h            |   3 +
 arch/x86/kvm/svm.c                            | 560 +++++++++++++++++-
 arch/x86/kvm/vmx/vmx.c                        |   1 +
 arch/x86/kvm/x86.c                            |  17 +
 arch/x86/mm/mem_encrypt.c                     |  45 +-
 arch/x86/mm/pageattr.c                        |  15 +
 include/uapi/linux/kvm.h                      |  51 ++
 include/uapi/linux/kvm_para.h                 |   1 +
 12 files changed, 834 insertions(+), 4 deletions(-)
```
#### [PATCH v8 00/15] x86/split_lock: Enable split lock detection
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

- Disable/enable split lock detection by sysfs interface
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
Patch 10: Handle #AC for split lock.
Patch 11-12: Enable split lock detection in KVM.
Patch 13: Enable split lock detection by default after #AC handler and KVM 
are installed.
Patch 14: Disable split lock detection by kernel parameter
"nosplit_lock_detect" during boot time.
Patch 15: Define a sysfs interface to enable/disable split lock
detection during run time.

==Changelog==
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

Fenghua Yu (11):
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
  x86/split_lock: Handle #AC exception for split lock
  x86/split_lock: Enable split lock detection by default
  x86/split_lock: Disable split lock detection by kernel parameter
    "nosplit_lock_detect"
  x86/split_lock: Add a sysfs interface to enable/disable split lock
    detection during run time

Paolo Bonzini (1):
  wlcore: simplify/fix/optimize reg_ch_conf_pending operations

Peter Zijlstra (1):
  drivers/net/b44: Align pwol_mask to unsigned long for better
    performance

Xiaoyao Li (2):
  kvm/x86: Emulate MSR IA32_CORE_CAPABILITY
  kvm/vmx: Emulate MSR TEST_CTL

 .../ABI/testing/sysfs-devices-system-cpu      |  22 +++
 .../admin-guide/kernel-parameters.txt         |   2 +
 arch/x86/include/asm/cpu.h                    |   8 ++
 arch/x86/include/asm/cpufeatures.h            |   2 +
 arch/x86/include/asm/kvm_host.h               |   1 +
 arch/x86/include/asm/msr-index.h              |   7 +
 arch/x86/include/asm/processor.h              |   4 +-
 arch/x86/kernel/cpu/common.c                  |   7 +-
 arch/x86/kernel/cpu/cpuid-deps.c              |  79 ++++++-----
 arch/x86/kernel/cpu/intel.c                   | 133 ++++++++++++++++++
 arch/x86/kernel/traps.c                       |  31 +++-
 arch/x86/kvm/cpuid.c                          |   6 +
 arch/x86/kvm/vmx/vmx.c                        |  42 ++++++
 arch/x86/kvm/vmx/vmx.h                        |   2 +
 arch/x86/kvm/x86.c                            |  39 +++++
 drivers/net/ethernet/broadcom/b44.c           |   4 +-
 drivers/net/wireless/ti/wlcore/cmd.c          |  15 +-
 drivers/net/wireless/ti/wlcore/wlcore.h       |   4 +-
 18 files changed, 352 insertions(+), 56 deletions(-)
```
