

#### [PATCH v5 0/3] KVM: x86: Enable user wait instructions
##### From: Tao Xu <tao3.xu@intel.com>

```c

UMONITOR, UMWAIT and TPAUSE are a set of user wait instructions.

UMONITOR arms address monitoring hardware using an address. A store
to an address within the specified address range triggers the
monitoring hardware to wake up the processor waiting in umwait.

UMWAIT instructs the processor to enter an implementation-dependent
optimized state while monitoring a range of addresses. The optimized
state may be either a light-weight power/performance optimized state
(c0.1 state) or an improved power/performance optimized state
(c0.2 state).

TPAUSE instructs the processor to enter an implementation-dependent
optimized state c0.1 or c0.2 state and wake up when time-stamp counter
reaches specified timeout.

Availability of the user wait instructions is indicated by the presence
of the CPUID feature flag WAITPKG CPUID.0x07.0x0:ECX[5].

The patches enable the umonitor, umwait and tpause features in KVM.
Because umwait and tpause can put a (psysical) CPU into a power saving
state, by default we dont't expose it to kvm and enable it only when
guest CPUID has it. If the instruction causes a delay, the amount
of time delayed is called here the physical delay. The physical delay is
first computed by determining the virtual delay (the time to delay
relative to the VM’s timestamp counter). 

The release document ref below link:
Intel 64 and IA-32 Architectures Software Developer's Manual,
https://software.intel.com/sites/default/files/\
managed/39/c5/325462-sdm-vol-1-2abcd-3abcd.pdf
This patch has a dependency on https://lkml.org/lkml/2019/6/19/972

Changelog:
v5:
	remove vmx_waitpkg_supported() to fix guest can rdmsr or wrmsr
	when the feature is off (Xiaoyao)
	rebase the patch because the kernel dependcy patch updated to
	v5: https://lkml.org/lkml/2019/6/19/972
v4:
	Set msr of IA32_UMWAIT_CONTROL can be 0 and add the check of
	reserved bit 1 (Radim and Xiaoyao)
	Use umwait_control_cached directly and add the IA32_UMWAIT_CONTROL
	in msrs_to_save[] to support migration (Xiaoyao)
v3:
	Simplify the patches, expose user wait instructions when the
	guest has CPUID (Paolo)
	Use mwait_control_cached to avoid frequently rdmsr of
	IA32_UMWAIT_CONTROL (Paolo and Xiaoyao)
	Handle vm-exit for UMWAIT and TPAUSE as "never happen" (Paolo)
v2:
	Separated from the series https://lkml.org/lkml/2018/7/10/160
	Add provide a capability to enable UMONITOR, UMWAIT and TPAUSE 
v1:
	Sent out with MOVDIRI/MOVDIR64B instructions patches

Tao Xu (3):
  KVM: x86: add support for user wait instructions
  KVM: vmx: Emulate MSR IA32_UMWAIT_CONTROL
  KVM: vmx: handle vm-exit for UMWAIT and TPAUSE

 arch/x86/include/asm/vmx.h      |  1 +
 arch/x86/include/uapi/asm/vmx.h |  6 ++++-
 arch/x86/kernel/cpu/umwait.c    |  3 ++-
 arch/x86/kvm/cpuid.c            |  2 +-
 arch/x86/kvm/vmx/vmx.c          | 44 +++++++++++++++++++++++++++++++++
 arch/x86/kvm/vmx/vmx.h          |  3 +++
 arch/x86/kvm/x86.c              |  1 +
 7 files changed, 57 insertions(+), 3 deletions(-)
```
#### [RFC PATCH v2 00/11] Add AMD SEV guest live migration support
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

The patch adds new ioctls KVM_{SET,GET}_PAGE_ENC_BITMAP. The ioctl can be used
by the qemu to get the page encrypted bitmap. Qemu can consult this bitmap
during the migration to know whether the page is encrypted.

[1] https://developer.amd.com/wp-content/resources/55766.PDF

While implementing the migration I stumbled on the follow question:

- Since there is a guest OS changes required to support the migration,
  so how do we know whether guest OS is updated? Should we extend KVM
  capabilities/feature bits to check this?

TODO:
 - reset the bitmap on guest reboot.

The complete tree with patch is available at:
https://github.com/codomania/kvm/tree/sev-migration-rfc-v2

Changes since v1:
 - Add support to share the page encryption between the source and target
   machine.
 - Fix review feedbacks from Tom Lendacky.
 - Add check to limit the session blob length.
 - Update KVM_GET_PAGE_ENC_BITMAP icotl to use the base_gfn instead of
   the memory slot when querying the bitmap.

Brijesh Singh (11):
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
  KVM: x86: Introduce KVM_SET_PAGE_ENC_BITMAP ioctl

 .../virtual/kvm/amd-memory-encryption.rst     | 120 ++++
 Documentation/virtual/kvm/hypercalls.txt      |  14 +
 arch/x86/include/asm/kvm_host.h               |   4 +
 arch/x86/include/asm/kvm_para.h               |  12 +
 arch/x86/include/asm/mem_encrypt.h            |   3 +
 arch/x86/kvm/svm.c                            | 573 +++++++++++++++++-
 arch/x86/kvm/vmx/vmx.c                        |   1 +
 arch/x86/kvm/x86.c                            |  29 +
 arch/x86/mm/mem_encrypt.c                     |  45 +-
 arch/x86/mm/pageattr.c                        |  15 +
 include/uapi/linux/kvm.h                      |  52 ++
 include/uapi/linux/kvm_para.h                 |   1 +
 12 files changed, 864 insertions(+), 5 deletions(-)
```
#### [RFC PATCH v1 00/12] Add SEV guest live migration support
##### From: "Singh, Brijesh" <brijesh.singh@amd.com>

```c

AMD SEV encrypts the memory of VMs and because this encryption is done using
an address tweak, the hypervisor will not be able to simply copy ciphertext
between machines to migrate a VM. Instead the AMD SEV Key Management API
provides a set of functions which the hypervisor can use to package a
guest encrypted pages for migration, while maintaining the confidentiality
provided by AMD SEV.

The patch series add the support required in Qemu to perform the SEV
guest live migration. Before initiating the live migration a user
should use newly added 'migrate-set-sev-info' command to pass the
target machines certificate chain. See the docs/amd-memory-encryption.txt
for further details.

The patch series depends on kernel patches available here:
https://marc.info/?l=kvm&m=156104873409876&w=2

The complete tree with patch is available at:
https://github.com/codomania/qemu/tree/sev-migration-rfc-v1

Brijesh Singh (12):
  linux-headers: update kernel header to include SEV migration commands
  kvm: introduce high-level API to support encrypted guest migration
  migration/ram: add support to send encrypted pages
  kvm: add support to sync the page encryption state bitmap
  doc: update AMD SEV API spec web link
  doc: update AMD SEV to include Live migration flow
  target/i386: sev: do not create launch context for an incoming guest
  target.json: add migrate-set-sev-info command
  target/i386: sev: add support to encrypt the outgoing page
  target/i386: sev: add support to load incoming encrypted page
  migration: add support to migrate page encryption bitmap
  target/i386: sev: remove migration blocker

 accel/kvm/kvm-all.c            |  75 ++++++
 accel/kvm/sev-stub.c           |  28 ++
 accel/stubs/kvm-stub.c         |  30 +++
 docs/amd-memory-encryption.txt |  46 +++-
 include/exec/ram_addr.h        |   2 +
 include/sysemu/kvm.h           |  33 +++
 include/sysemu/sev.h           |   9 +
 linux-headers/linux/kvm.h      |  53 ++++
 migration/ram.c                | 121 ++++++++-
 qapi/target.json               |  18 ++
 target/i386/monitor.c          |  10 +
 target/i386/sev-stub.c         |   5 +
 target/i386/sev.c              | 471 +++++++++++++++++++++++++++++++--
 target/i386/sev_i386.h         |  11 +-
 target/i386/trace-events       |   9 +
 15 files changed, 902 insertions(+), 19 deletions(-)
```
