#### [PATCH] x86/kernel/hyper-v: xmm fast hypercall as guest
##### From: Isaku Yamahata <isaku.yamahata@gmail.com>

```c
hyper-v hypercall supports fast hypercall and xmm fast hypercall
where argument is exchanged though regular/xmm registers.
This patch implements them and make use of them.
With this patch, pci-hyperv.c, hv_apic.c(__send_ipi_mask), and
hyperv/mmu.c will use (xmm) fast hypercall.
---
 arch/x86/hyperv/hv_apic.c           |   3 +-
 arch/x86/hyperv/mmu.c               |   4 +-
 arch/x86/include/asm/hyperv-tlfs.h  |   1 +
 arch/x86/include/asm/mshyperv.h     | 184 ++++++++++++++++++++++++++++++++++--
 drivers/hv/hv.c                     |   3 +-
 drivers/pci/controller/pci-hyperv.c |   5 +-
 6 files changed, 186 insertions(+), 14 deletions(-)

```
#### [PATCH] x86/kernel/hyper-v: xmm fast hypercall as guest
##### From: Isaku Yamahata <isaku.yamahata@gmail.com>

```c
hyper-v hypercall supports fast hypercall and xmm fast hypercall
where argument is exchanged though regular/xmm registers.
This patch implements them and make use of them.
With this patch, pci-hyperv.c, hv_apic.c(__send_ipi_mask), and
hyperv/mmu.c will use (xmm) fast hypercall.

Signed-off-by: Isaku Yamahata <isaku.yamahata@gmail.com>
---
 arch/x86/hyperv/hv_apic.c           |   3 +-
 arch/x86/hyperv/mmu.c               |   4 +-
 arch/x86/include/asm/hyperv-tlfs.h  |   1 +
 arch/x86/include/asm/mshyperv.h     | 184 ++++++++++++++++++++++++++++++++++--
 drivers/hv/hv.c                     |   3 +-
 drivers/pci/controller/pci-hyperv.c |   5 +-
 6 files changed, 186 insertions(+), 14 deletions(-)

```
#### [PATCH] x86/kvm/lapic: always disable MMIO interface in x2APIC mode
##### From: Vitaly Kuznetsov <vkuznets@redhat.com>

```c
When VMX is used with flexpriority disabled (because of no support or
if disabled with module parameter) MMIO interface to lAPIC is still
available in x2APIC mode while it shouldn't be (kvm-unit-tests):

PASS: apic_disable: Local apic enabled in x2APIC mode
PASS: apic_disable: CPUID.1H:EDX.APIC[bit 9] is set
FAIL: apic_disable: *0xfee00030: 50014

The issue appears because we basically do nothing while switching to
x2APIC mode when APIC access page is not used. apic_mmio_{read,write}
only check if lAPIC is disabled before proceeding to actual write.

When APIC access is virtualized we correctly manipulate with VMX controls
in vmx_set_virtual_apic_mode() and we don't get vmexits from memory writes
in x2APIC mode so there's no issue.

Disabling MMIO interface seems to be easy. The question is: what do we
do with these reads and writes? If we add apic_x2apic_mode() check to
apic_mmio_in_range() and return -EOPNOTSUPP these reads and writes will
go to userspace. When lAPIC is in kernel, Qemu uses this interface to
inject MSIs only (see kvm_apic_mem_write() in hw/i386/kvm/apic.c). This
somehow works with disabled lAPIC but when we're in xAPIC mode we will
get a real injected MSI from every write to lAPIC. Not good.

The simplest solution seems to be to just ignore writes to the region
and return ~0 for all reads when we're in x2APIC mode. This is what this
patch does. However, this approach is inconsistent with what currently
happens when flexpriority is enabled: we allocate APIC access page and
create KVM memory region so in x2APIC modes all reads and writes go to
this pre-allocated page which is, btw, the same for all vCPUs.

Signed-off-by: Vitaly Kuznetsov <vkuznets@redhat.com>
---
Changes since RFC:
- add KVM_X86_QUIRK_LAPIC_MMIO_HOLE disabling the newly introduced
  'MMIO hole' behavior [Paolo Bonzini]
---
 arch/x86/include/uapi/asm/kvm.h |  1 +
 arch/x86/kvm/lapic.c            | 22 +++++++++++++++++++---
 2 files changed, 20 insertions(+), 3 deletions(-)

```
#### [PATCH 1/9] x86/kvm/mmu: make vcpu->mmu a pointer to the current MMU
##### From: Vitaly Kuznetsov <vkuznets@redhat.com>

```c
As a preparation to full MMU split between L1 and L2 make vcpu->arch.mmu
a pointer to the currently used mmu. For now, this is always
vcpu->arch.root_mmu. No functional change.

Signed-off-by: Vitaly Kuznetsov <vkuznets@redhat.com>
Signed-off-by: Paolo Bonzini <pbonzini@redhat.com>
---
 arch/x86/include/asm/kvm_host.h |   5 +-
 arch/x86/kvm/mmu.c              | 165 ++++++++++++++++++++--------------------
 arch/x86/kvm/mmu.h              |   8 +-
 arch/x86/kvm/mmu_audit.c        |  12 +--
 arch/x86/kvm/paging_tmpl.h      |  15 ++--
 arch/x86/kvm/svm.c              |  14 ++--
 arch/x86/kvm/vmx.c              |  15 ++--
 arch/x86/kvm/x86.c              |  20 ++---
 8 files changed, 130 insertions(+), 124 deletions(-)

```
