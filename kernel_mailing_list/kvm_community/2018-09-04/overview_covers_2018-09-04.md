

#### [PATCH v4 0/4] x86: Fix SEV guest regression
##### From: Brijesh Singh <brijesh.singh@amd.com>

```c

The following commit

"
x86/kvmclock: Remove memblock dependency

https://git.kernel.org/pub/scm/linux/kernel/git/torvalds/linux.git/commit/?id=368a540e0232ad446931f5a4e8a5e06f69f21343
"

introduced SEV guest regression.

The guest physical address holding the wall_clock and hv_clock_boot
are shared with the hypervisor must be mapped with C=0 when SEV
is active. To clear the C-bit we use  kernel_physical_mapping_init() to
split the large pages. The above commit moved the kvmclock initialization
very early and kernel_physical_mapping_init() fails to allocate memory
while spliting the large page.

To solve it, we add a special .data..decrypted section, this section can be
used to hold the shared variables. Early boot code maps this section with
C=0. The section is pmd aligned and sized to avoid the need to split the pages.
Caller can use __decrypted attribute to add the variables in .data..decrypted
section. 

Cc: Tom Lendacky <thomas.lendacky@amd.com>
Cc: Thomas Gleixner <tglx@linutronix.de>
Cc: Borislav Petkov <bp@suse.de>
Cc: Paolo Bonzini <pbonzini@redhat.com>
Cc: Sean Christopherson <sean.j.christopherson@intel.com>
Cc: "Radim Krčmář" <rkrcmar@redhat.com>

Changes since v3:
 - commit message improvements (based on Sean's feedback)

Changes since v2:
 - commit message and code comment improvements (based on Boris feedback)
 - move sme_populate_pgd fixes in new patch.
 - drop stable Cc - will submit to stable after patch is upstreamed.

Changes since v1:
 - move the logic to re-arrange mapping in new patch
 - move the definition of __start_data_* in mem_encrypt.h
 - map the workarea buffer as encrypted when SEV is enabled
 - enhance the sme_populate_pgd to update the pte/pmd flags when mapping exist

Brijesh Singh (4):
  x86/mm: Restructure sme_encrypt_kernel()
  x86/mm: fix sme_populate_pgd() to update page flags
  x86/mm: add .data..decrypted section to hold shared variables
  x86/kvm: use __decrypted attribute in shared variables

 arch/x86/include/asm/mem_encrypt.h |   6 +
 arch/x86/kernel/head64.c           |  11 ++
 arch/x86/kernel/kvmclock.c         |  30 ++++-
 arch/x86/kernel/vmlinux.lds.S      |  17 +++
 arch/x86/mm/mem_encrypt_identity.c | 232 +++++++++++++++++++++++++++----------
 5 files changed, 229 insertions(+), 67 deletions(-)
```
#### [kvm-unit-tests PATCH 0/2]: x86: VMX: Verify do not lose pending
##### From: Liran Alon <liran.alon@oracle.com>

```c

Hi,

This patch series aim to verify the fix introduced by KVM commit "KVM:
nVMX: Fix loss of pending event before entering L2". The tests aim to
verify that a pending interrupt while interrupts are disabled is
dispatched when we enter into VMX guest instead of being lost.

The 1st patch add the basic test for the scenario described above and
the 2nd patch adds another similar test but with entering guest in HLT
activity-state.

Regards,
-Liran
```
#### [kvm-unit-tests PATCH 0/3]: x86: VMX: Verify blocked vCPU in
##### From: Liran Alon <liran.alon@oracle.com>

```c

Hi,

This test aims to verify that when entering a guest in HLT activity
state but with a pending interrupt in RVI, the guest is in fact not
halted and an interrupt is indeed injected.

For more information, see commit message of kernel patch
"KVM: nVMX: Wake blocked vCPU in guest-mode if pending interrupt in
virtual APICv".

1st patch introduce util to disable intercept on x2APIC MSRs.
2nd patch inroduce util to enable virtual interrupt delivery.
3rd patch adds the test itself.

Regards,
-Liran
```
#### [PATCH kvm-unit-tests v3 0/2] Support micro operation measurement on
##### From: Andrew Jones <drjones@redhat.com>

```c

I dropped the version numbers, but this is v4 of Shih-Wei Li's series of
the same name, last posted in January. I took the liberty of
incorporating all the comments v3 had, plus making some other cleanup
tweaks. These tests are too nice to let them slip away, let's get them
reviewed and merged.

v3:
 - add missing breaks in switch statement [Shih-Wei]
v2:
 - add missing 'L' in 'UL' for PS_PER_SEC. There's a lot of picoseconds
   in a second!

Thanks,
drew

Shih-Wei Li (2):
  arm/arm64: add GICD_IIDR definition
  arm64: add micro-bench

 arm/Makefile.arm64 |   1 +
 arm/micro-bench.c  | 215 +++++++++++++++++++++++++++++++++++++++++++++
 arm/unittests.cfg  |   8 ++
 lib/arm/asm/gic.h  |   1 +
 4 files changed, 225 insertions(+)
 create mode 100644 arm/micro-bench.c
```
