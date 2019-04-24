#### [GIT PULL 1/2] KVM: s390: fix typo in parameter description
##### From: Christian Borntraeger <borntraeger@de.ibm.com>

```c
From: Wei Yongjun <weiyongjun1@huawei.com>

Fix typo in parameter description.

Fixes: 8b905d28ee17 ("KVM: s390: provide kvm_arch_no_poll function")
Signed-off-by: Wei Yongjun <weiyongjun1@huawei.com>
Message-Id: <20190504065145.53665-1-weiyongjun1@huawei.com>
Reviewed-by: Cornelia Huck <cohuck@redhat.com>
Reviewed-by: David Hildenbrand <david@redhat.com>
Signed-off-by: Christian Borntraeger <borntraeger@de.ibm.com>
---
 arch/s390/kvm/kvm-s390.c | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
#### [PATCH v4 1/5] KVM: LAPIC: Extract adaptive tune timer advancement logic
##### From: Wanpeng Li <kernellwp@gmail.com>

```c
From: Wanpeng Li <wanpengli@tencent.com>

Extract adaptive tune timer advancement logic to a single function.

Cc: Paolo Bonzini <pbonzini@redhat.com>
Cc: Radim Krčmář <rkrcmar@redhat.com>
Cc: Sean Christopherson <sean.j.christopherson@intel.com>
Cc: Liran Alon <liran.alon@oracle.com>
Signed-off-by: Wanpeng Li <wanpengli@tencent.com>
---
 arch/x86/kvm/lapic.c | 57 ++++++++++++++++++++++++++++++----------------------
 1 file changed, 33 insertions(+), 24 deletions(-)

```
#### [PATCH 1/2] KVM: nVMX: Stash L1's CR3 in vmcs01.GUEST_CR3 on nested entry w/o EPT
##### From: Sean Christopherson <sean.j.christopherson@intel.com>

```c
KVM does not have 100% coverage of VMX consistency checks, i.e. some
checks that cause VM-Fail may only be detected by hardware during a
nested VM-Entry.  In such a case, KVM must restore L1's state to the
pre-VM-Enter state as L2's state has already been loaded into KVM's
software model.

L1's CR3 and PDPTRs in particular are loaded from vmcs01.GUEST_*.  But
when EPT is disabled, the associated fields hold KVM's shadow values,
not L1's "real" values.  Fortunately, when EPT is disabled the PDPTRs
come from memory, i.e. are not cached in the VMCS.  Which leaves CR3
as the sole anomaly.  Handle CR3 by overwriting vmcs01.GUEST_CR3 with
L1's CR3 during the nested VM-Entry when EPT is disabled *and* nested
early checks are disabled, so that nested_vmx_restore_host_state() will
naturally restore the correct vcpu->arch.cr3 from vmcs01.GUEST_CR3.

Note, these shenanigans work because nested_vmx_restore_host_state()
does a full kvm_mmu_reset_context(), i.e. unloads the current MMU,
which guarantees vmcs01.GUEST_CR3 will be rewritten with a new shadow
CR3 prior to re-entering L1.  Writing vmcs01.GUEST_CR3 is done if and
only if nested early checks are disabled as "late" VM-Fail should never
happen in that case (KVM WARNs), and the conditional write avoids the
need to restore the correct GUEST_CR3 when nested_vmx_check_vmentry_hw()
fails.

Reported-by: Paolo Bonzini <pbonzini@redhat.com>
Fixes: bd18bffca353 ("KVM: nVMX: restore host state in nested_vmx_vmexit for VMFail")
Cc: stable@vger.kernel.org
Signed-off-by: Sean Christopherson <sean.j.christopherson@intel.com>
---
 arch/x86/kvm/vmx/nested.c | 5 ++++-
 1 file changed, 4 insertions(+), 1 deletion(-)

```
#### [PATCH 1/3] KVM: PPC: Book3S HV: XIVE: clear file mapping when device is released
##### From: =?utf-8?q?C=C3=A9dric_Le_Goater?= <clg@kaod.org>

```c
Improve the release of the XIVE KVM device by clearing the file
address_space which is used to unmap the interrupt ESB pages when a
device is passed-through.

Suggested-by: Paul Mackerras <paulus@ozlabs.org>
Signed-off-by: Cédric Le Goater <clg@kaod.org>
---
 arch/powerpc/kvm/book3s_xive_native.c | 8 ++++++++
 1 file changed, 8 insertions(+)

```
#### [PATCH] kvm: selftests: avoid type punning
##### From: Paolo Bonzini <pbonzini@redhat.com>

```c
Avoid warnings from -Wstrict-aliasing by using memcpy.

Signed-off-by: Paolo Bonzini <pbonzini@redhat.com>
Reviewed-by: Thomas Huth <thuth@redhat.com>
---
 tools/testing/selftests/kvm/lib/ucall.c                        | 2 +-
 tools/testing/selftests/kvm/x86_64/vmx_set_nested_state_test.c | 2 +-
 2 files changed, 2 insertions(+), 2 deletions(-)

```
#### [PATCH] KVM: selftests: Remove duplicated TEST_ASSERT in hyperv_cpuid.c
##### From: Thomas Huth <thuth@redhat.com>

```c
The check for entry->index == 0 is done twice. One time should
be sufficient.

Suggested-by: Vitaly Kuznetsov <vkuznets@redhat.com>
Signed-off-by: Thomas Huth <thuth@redhat.com>
---
 Vitaly already noticed this in his review to the "Fix a condition
 in test_hv_cpuid()" patch a couple of days ago, but so far I haven't
 seen any patch yet on the list that fixes this ... if I missed it
 instead, please simply ignore this patch.

 tools/testing/selftests/kvm/x86_64/hyperv_cpuid.c | 3 ---
 1 file changed, 3 deletions(-)

```
#### [kvm-unit-tests PATCH] x86: Fix SMP stacks
##### From: Nadav Amit <nadav.amit@gmail.com>

```c
Avoid smashing the SMP stacks during boot as currently happens by
allocating sufficient space for them.

Signed-off-by: Nadav Amit <nadav.amit@gmail.com>
---
 x86/cstart64.S | 4 ++--
 1 file changed, 2 insertions(+), 2 deletions(-)

```
#### [kvm-unit-tests PATCH] x86: Remove xfail in entry check in enter_guest_with_bad_controls()
##### From: Nadav Amit <nadav.amit@gmail.com>

```c
The test succeeds in failing entry. This is not an expected failure.

Cc: Marc Orr <marcorr@google.com>
Signed-off-by: Nadav Amit <nadav.amit@gmail.com>
---
 x86/vmx.c | 3 +--
 1 file changed, 1 insertion(+), 2 deletions(-)

```
#### [PATCH] kvm: vmx: Fix -Wmissing-prototypes warnings
##### From: Yi Wang <wang.yi59@zte.com.cn>

```c
We get a warning when build kernel W=1:
arch/x86/kvm/vmx/vmx.c:6365:6: warning: no previous prototype for ‘vmx_update_host_rsp’ [-Wmissing-prototypes]
 void vmx_update_host_rsp(struct vcpu_vmx *vmx, unsigned long host_rsp)

Add the missing declaration to fix this.

Signed-off-by: Yi Wang <wang.yi59@zte.com.cn>
---
 arch/x86/kvm/vmx/vmx.h | 1 +
 1 file changed, 1 insertion(+)

```
#### [PATCH] KVM: x86: do not spam dmesg with VMCS/VMCB dumps
##### From: Paolo Bonzini <pbonzini@redhat.com>

```c
Userspace can easily set up invalid processor state in such a way that
dmesg will be filled with VMCS or VMCB dumps.  Disable this by default
using a module parameter.

Signed-off-by: Paolo Bonzini <pbonzini@redhat.com>
---
 arch/x86/kvm/svm.c     |  9 ++++++++-
 arch/x86/kvm/vmx/vmx.c | 26 +++++++++++++++++++-------
 2 files changed, 27 insertions(+), 8 deletions(-)

```
#### [PATCH 1/2] KVM: x86/pmu: mask the result of rdpmc according to the width of the counters
##### From: Paolo Bonzini <pbonzini@redhat.com>

```c
This patch will simplify the changes in the next, by enforcing the
masking of the counters to RDPMC and RDMSR.

Signed-off-by: Paolo Bonzini <pbonzini@redhat.com>
---
 arch/x86/kvm/pmu.c           | 10 +++-------
 arch/x86/kvm/pmu.h           |  3 ++-
 arch/x86/kvm/pmu_amd.c       |  2 +-
 arch/x86/kvm/vmx/pmu_intel.c | 13 +++++++++----
 4 files changed, 15 insertions(+), 13 deletions(-)

```
#### [PATCH 10/10] docs: fix broken documentation links
##### From: Mauro Carvalho Chehab <mchehab+samsung@kernel.org>

```c
Mostly due to x86 and acpi conversion, several documentation
links are still pointing to the old file. Fix them.

Signed-off-by: Mauro Carvalho Chehab <mchehab+samsung@kernel.org>
Reviewed-by: Wolfram Sang <wsa@the-dreams.de>
---
 Documentation/acpi/dsd/leds.txt                  |  2 +-
 Documentation/admin-guide/kernel-parameters.rst  |  6 +++---
 Documentation/admin-guide/kernel-parameters.txt  | 16 ++++++++--------
 Documentation/admin-guide/ras.rst                |  2 +-
 .../devicetree/bindings/net/fsl-enetc.txt        |  7 +++----
 .../bindings/pci/amlogic,meson-pcie.txt          |  2 +-
 .../bindings/regulator/qcom,rpmh-regulator.txt   |  2 +-
 Documentation/devicetree/booting-without-of.txt  |  2 +-
 Documentation/driver-api/gpio/board.rst          |  2 +-
 Documentation/driver-api/gpio/consumer.rst       |  2 +-
 .../firmware-guide/acpi/enumeration.rst          |  2 +-
 .../firmware-guide/acpi/method-tracing.rst       |  2 +-
 Documentation/i2c/instantiating-devices          |  2 +-
 Documentation/sysctl/kernel.txt                  |  4 ++--
 .../translations/it_IT/process/4.Coding.rst      |  2 +-
 .../translations/it_IT/process/howto.rst         |  2 +-
 .../it_IT/process/stable-kernel-rules.rst        |  4 ++--
 .../translations/zh_CN/process/4.Coding.rst      |  2 +-
 Documentation/x86/x86_64/5level-paging.rst       |  2 +-
 Documentation/x86/x86_64/boot-options.rst        |  4 ++--
 .../x86/x86_64/fake-numa-for-cpusets.rst         |  2 +-
 MAINTAINERS                                      |  6 +++---
 arch/arm/Kconfig                                 |  2 +-
 arch/arm64/kernel/kexec_image.c                  |  2 +-
 arch/powerpc/Kconfig                             |  2 +-
 arch/x86/Kconfig                                 | 16 ++++++++--------
 arch/x86/Kconfig.debug                           |  2 +-
 arch/x86/boot/header.S                           |  2 +-
 arch/x86/entry/entry_64.S                        |  2 +-
 arch/x86/include/asm/bootparam_utils.h           |  2 +-
 arch/x86/include/asm/page_64_types.h             |  2 +-
 arch/x86/include/asm/pgtable_64_types.h          |  2 +-
 arch/x86/kernel/cpu/microcode/amd.c              |  2 +-
 arch/x86/kernel/kexec-bzimage64.c                |  2 +-
 arch/x86/kernel/pci-dma.c                        |  2 +-
 arch/x86/mm/tlb.c                                |  2 +-
 arch/x86/platform/pvh/enlighten.c                |  2 +-
 drivers/acpi/Kconfig                             | 10 +++++-----
 drivers/net/ethernet/faraday/ftgmac100.c         |  2 +-
 .../fieldbus/Documentation/fieldbus_dev.txt      |  4 ++--
 drivers/vhost/vhost.c                            |  2 +-
 include/acpi/acpi_drivers.h                      |  2 +-
 include/linux/fs_context.h                       |  2 +-
 include/linux/lsm_hooks.h                        |  2 +-
 mm/Kconfig                                       |  2 +-
 security/Kconfig                                 |  2 +-
 tools/include/linux/err.h                        |  2 +-
 tools/objtool/Documentation/stack-validation.txt |  4 ++--
 tools/testing/selftests/x86/protection_keys.c    |  2 +-
 49 files changed, 78 insertions(+), 79 deletions(-)

```
#### [PATCH RESEND] kvm: make kvm_vcpu_(un)map dependency on CONFIG_HAS_IOMEM
##### From: Michal Kubecek <mkubecek@suse.cz>

```c
Recently introduced functions kvm_vcpu_map() and kvm_vcpu_unmap() call
memremap() and memunmap() which are only available if HAS_IOMEM is enabled
but this dependency is not explicit, so that the build fails with HAS_IOMEM
disabled.

As both function are only used on x86 where HAS_IOMEM is always enabled,
the easiest fix seems to be to only provide them when HAS_IOMEM is enabled.

Fixes: e45adf665a53 ("KVM: Introduce a new guest mapping API")
Signed-off-by: Michal Kubecek <mkubecek@suse.cz>
---
 include/linux/kvm_host.h | 6 +++++-
 virt/kvm/kvm_main.c      | 2 ++
 2 files changed, 7 insertions(+), 1 deletion(-)

```
