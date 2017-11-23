

#### [kvm-unit-tests PATCH v2 0/6] 390x: Add cross hypervisor and disk
##### From: Janosch Frank <frankja@linux.ibm.com>

```c

With these patches kvm unit tests are now bootable under LPAR and
z/VM, as well as from KVM disks. Don't forget to convert the ELF files
to binary via:

objcopy -O binary s390x/test.elf test.bin

For this to work we added:
    * Initial PSW in lowcore
    * Switch to 64 bit and z/Arch
    * SCLP linemode console

This is an early version, linemode currently splits lines a bit too
often and I still need to polish comments and cleanup code.


v2:
	* Moved cleanup to the front and broadened patch
	* Split up SCLP patch into interrupt and linemode
	* Removed unneeded instructions
	* Improved comments and commit messages

Janosch Frank (6):
  s390x: Cleanup sclp-ascii.c and add sigp order definitions
  s390x: Make tests bootable from disk
  s390x: Switch to z/Arch if needed
  s390x: Add BSS clearing for non ELF boot
  s390x: Use interrupts in SCLP
  s390x: Add linemode console

 lib/s390x/asm/arch_def.h  |  19 ++++
 lib/s390x/asm/interrupt.h |   2 +
 lib/s390x/interrupt.c     |  12 ++-
 lib/s390x/io.c            |   5 +-
 lib/s390x/sclp-ascii.c    |  68 ---------------
 lib/s390x/sclp-console.c  | 214 ++++++++++++++++++++++++++++++++++++++++++++++
 lib/s390x/sclp.c          |  42 +++++++++
 lib/s390x/sclp.h          |  73 +++++++++++++++-
 s390x/Makefile            |   2 +-
 s390x/cstart64.S          |  40 ++++++++-
 s390x/flat.lds            |  10 ++-
 11 files changed, 409 insertions(+), 78 deletions(-)
 delete mode 100644 lib/s390x/sclp-ascii.c
 create mode 100644 lib/s390x/sclp-console.c
```
#### [PATCH v4 0/5] Various guest_msrs cleanups
##### From: Jim Mattson <jmattson@google.com>

```c

v1: Just one commit:
    "kvm: vmx: Set IA32_TSC_AUX for legacy mode guests"
v2: Added three more commits:
    "kvm: vmx: Omit MSR_STAR from vmx_msr_index[] for i386 builds"
    "kvm: vmx: Don't set hardware IA32_CSTAR MSR on VM-entry"
    "kvm: vmx: Skip all SYSCALL MSRs in setup_msrs() when !EFER.SCE"
v3: Changed "kvm: vmx: Omit MSR_STAR from vmx_msr_index[] for i386 builds" to
            "kvm: vmx: Document the need for MSR_STAR in i386 builds"
    Modified the commit message for:
            "kvm: vmx: Don't set hardware IA32_CSTAR MSR on VM-entry"
v4: Added a fifth commit:
    "kvm: vmx: Stop wasting a page for guest_msrs"

Jim Mattson (5):
  kvm: vmx: Set IA32_TSC_AUX for legacy mode guests
  kvm: vmx: Document the need for MSR_STAR in i386 builds
  kvm: vmx: Don't set hardware IA32_CSTAR MSR on VM-entry
  kvm: vmx: Skip all SYSCALL MSRs in setup_msrs() when !EFER.SCE
  kvm: vmx: Stop wasting a page for guest_msrs

 arch/x86/kvm/vmx.c | 62 +++++++++++++++++++---------------------------
 1 file changed, 26 insertions(+), 36 deletions(-)
```
