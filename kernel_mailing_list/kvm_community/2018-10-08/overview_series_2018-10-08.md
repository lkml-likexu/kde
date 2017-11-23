#### [PATCH 1/5] kvm: x86: Add payload to kvm_queued_exception and kvm_vcpu_events
##### From: Jim Mattson <jmattson@google.com>

```c
Under nested virtualization, the L1 hypervisor may intercept an
exception raised during the execution of L2 before the exception
is delivered. When the intercepted exception is #PF, the VM-exit
to the L1 hypervisor precedes the modification of CR2. When the
intercepted exception is #DB, the VM-exit to the L1 hypervisor
precedes the modifications of DR6 and DR7 under VMX, but the
VM-exit to the L1 hypervisor follows the modifications of DR6 and
DR7 under SVM.

At present, CR2 is modified too early under both VMX and SVM. DR6 is
modified too early under VMX. DR7 is modified at the appropriate time.
Unfortunately, it is possible to exit to userspace with one of these
exceptions pending, and userspace may rely on the premature
side-effects. It is also possible for userspace to inject one of these
exceptions, in which case, userspace will presumably have already
processed the side-effects.

To address this problem, a new per-VM capability
(KVM_CAP_EXCEPTION_PAYLOAD) will be introduced. When this capability
is enabled by userspace, the faulting linear address will be included
with the information about a pending #PF in L2, and the "new DR6 bits"
will be included with the information about a pending #DB in L2. This
ancillary exception information is carried in a new "payload" field.

Reported-by: Jim Mattson <jmattson@google.com>
Suggested-by: Paolo Bonzini <pbonzini@redhat.com>
Signed-off-by: Jim Mattson <jmattson@google.com>
Reviewed-by: Peter Shier <pshier@google.com>
Reviewed-by: Liran Alon <liran.alon@oracle.com>
---
 Documentation/virtual/kvm/api.txt     | 13 +++++++++++--
 arch/x86/include/asm/kvm_host.h       |  3 +++
 arch/x86/include/uapi/asm/kvm.h       |  6 ++++--
 arch/x86/kvm/x86.c                    | 28 ++++++++++++++++++++++++---
 tools/arch/x86/include/uapi/asm/kvm.h |  6 ++++--
 5 files changed, 47 insertions(+), 9 deletions(-)

```
#### [PATCH 4.18 156/168] iommu/amd: Clear memory encryption mask from physical address
##### From: Greg Kroah-Hartman <gregkh@linuxfoundation.org>

```c
4.18-stable review patch.  If anyone has any objections, please let me know.

------------------

From: Singh, Brijesh <brijesh.singh@amd.com>

commit b3e9b515b08e407ab3a026dc2e4d935c48d05f69 upstream.

Boris Ostrovsky reported a memory leak with device passthrough when SME
is active.

The VFIO driver uses iommu_iova_to_phys() to get the physical address for
an iova. This physical address is later passed into vfio_unmap_unpin() to
unpin the memory. The vfio_unmap_unpin() uses pfn_valid() before unpinning
the memory. The pfn_valid() check was failing because encryption mask was
part of the physical address returned. This resulted in the memory not
being unpinned and therefore leaked after the guest terminates.

The memory encryption mask must be cleared from the physical address in
iommu_iova_to_phys().

Fixes: 2543a786aa25 ("iommu/amd: Allow the AMD IOMMU to work with memory encryption")
Reported-by: Boris Ostrovsky <boris.ostrovsky@oracle.com>
Cc: Tom Lendacky <thomas.lendacky@amd.com>
Cc: Joerg Roedel <joro@8bytes.org>
Cc: <iommu@lists.linux-foundation.org>
Cc: Borislav Petkov <bp@suse.de>
Cc: Paolo Bonzini <pbonzini@redhat.com>
Cc: Radim Krčmář <rkrcmar@redhat.com>
Cc: kvm@vger.kernel.org
Cc: Boris Ostrovsky <boris.ostrovsky@oracle.com>
Cc: <stable@vger.kernel.org> # 4.14+
Signed-off-by: Brijesh Singh <brijesh.singh@amd.com>
Signed-off-by: Joerg Roedel <jroedel@suse.de>
Signed-off-by: Greg Kroah-Hartman <gregkh@linuxfoundation.org>
---
 drivers/iommu/amd_iommu.c |    2 +-
```
#### [PATCH 4.14 84/94] iommu/amd: Clear memory encryption mask from physical address
##### From: Greg Kroah-Hartman <gregkh@linuxfoundation.org>

```c
4.14-stable review patch.  If anyone has any objections, please let me know.

------------------

From: Singh, Brijesh <brijesh.singh@amd.com>

commit b3e9b515b08e407ab3a026dc2e4d935c48d05f69 upstream.

Boris Ostrovsky reported a memory leak with device passthrough when SME
is active.

The VFIO driver uses iommu_iova_to_phys() to get the physical address for
an iova. This physical address is later passed into vfio_unmap_unpin() to
unpin the memory. The vfio_unmap_unpin() uses pfn_valid() before unpinning
the memory. The pfn_valid() check was failing because encryption mask was
part of the physical address returned. This resulted in the memory not
being unpinned and therefore leaked after the guest terminates.

The memory encryption mask must be cleared from the physical address in
iommu_iova_to_phys().

Fixes: 2543a786aa25 ("iommu/amd: Allow the AMD IOMMU to work with memory encryption")
Reported-by: Boris Ostrovsky <boris.ostrovsky@oracle.com>
Cc: Tom Lendacky <thomas.lendacky@amd.com>
Cc: Joerg Roedel <joro@8bytes.org>
Cc: <iommu@lists.linux-foundation.org>
Cc: Borislav Petkov <bp@suse.de>
Cc: Paolo Bonzini <pbonzini@redhat.com>
Cc: Radim Krčmář <rkrcmar@redhat.com>
Cc: kvm@vger.kernel.org
Cc: Boris Ostrovsky <boris.ostrovsky@oracle.com>
Cc: <stable@vger.kernel.org> # 4.14+
Signed-off-by: Brijesh Singh <brijesh.singh@amd.com>
Signed-off-by: Joerg Roedel <jroedel@suse.de>
Signed-off-by: Greg Kroah-Hartman <gregkh@linuxfoundation.org>
---
 drivers/iommu/amd_iommu.c |    2 +-
```
#### [PATCH v2 1/4] KVM: nVMX: Flush TLB entries tagged by dest EPTP on L1<->L2 transitions
##### From: Liran Alon <liran.alon@oracle.com>

```c
If L1 and L2 share VPID (because L1 don't use VPID or we haven't allocated
a vpid02), we need to flush TLB on L1<->L2 transitions.

Before this patch, this TLB flushing was done by vmx_flush_tlb().
If L0 use EPT, this will translate into INVEPT(active_eptp);
However, if L1 use EPT, in L1->L2 VMEntry, active EPTP is EPTP01 but
TLB entries populated by L2 are tagged with EPTP02.
Therefore we should delay vmx_flush_tlb() until active_eptp is EPTP02.

To achieve this, instead of directly calling vmx_flush_tlb() we request
it to be called by KVM_REQ_TLB_FLUSH which is evaluated after
KVM_REQ_LOAD_CR3 which sets the active_eptp to EPTP02 as required.

Similarly, on L2->L1 VMExit, active EPTP is EPTP02 but TLB entries
populated by L1 are tagged with EPTP01 and therefore we should delay
vmx_flush_tlb() until active_eptp is EPTP01.

Reviewed-by: Mihai Carabas <mihai.carabas@oracle.com>
Reviewed-by: Darren Kenny <darren.kenny@oracle.com>
Reviewed-by: Nikita Leshenko <nikita.leshchenko@oracle.com>
Signed-off-by: Liran Alon <liran.alon@oracle.com>
---
 arch/x86/kvm/vmx.c | 16 ++++++++++++++--
 1 file changed, 14 insertions(+), 2 deletions(-)

```
#### [PATCH v5 01/33] powerpc: Turn off CPU_FTR_P9_TM_HV_ASSIST in non-hypervisor mode
##### From: Paul Mackerras <paulus@ozlabs.org>

```c
When doing nested virtualization, it is only necessary to do the
transactional memory hypervisor assist at level 0, that is, when
we are in hypervisor mode.  Nested hypervisors can just use the TM
facilities as architected.  Therefore we should clear the
CPU_FTR_P9_TM_HV_ASSIST bit when we are not in hypervisor mode,
along with the CPU_FTR_HVMODE bit.

Doing this will not change anything at this stage because the only
code that tests CPU_FTR_P9_TM_HV_ASSIST is in HV KVM, which currently
can only be used when when CPU_FTR_HVMODE is set.

Reviewed-by: David Gibson <david@gibson.dropbear.id.au>
Signed-off-by: Paul Mackerras <paulus@ozlabs.org>
---
 arch/powerpc/kernel/cpu_setup_power.S | 4 ++--
 1 file changed, 2 insertions(+), 2 deletions(-)

```
#### [kvm-unit-tests PATCH] x86: nVMX: fix EPT A/D disabled MMIO access test
##### From: Vitaly Kuznetsov <vkuznets@redhat.com>

```c
When testing MMIO interface to APIC we need to make sure that APIC is in
xAPIC mode (and not x2APIC). KVM started enforcing this since commit
d1766202779e ("x86/kvm/lapic: always disable MMIO interface in x2APIC
mode").

While the 'clean' fix would be to separate L2's APIC from L1's and put
it to xAPIC mode or create a different MMIO mapping just for the test
we lack the required infrastructure in vmx library. As a quick band-aid
put L1's APIC to xAPIC mode for both EPT A/D enabled and disabled tests,
it seems we don't require x2APIC for anything.

Reported-by: kernel test robot <rong.a.chen@intel.com>
Signed-off-by: Vitaly Kuznetsov <vkuznets@redhat.com>
---
 x86/vmx_tests.c | 2 ++
 1 file changed, 2 insertions(+)

```
#### [PATCH 1/2] KVM: x86: hyperv: fix 'tlb_lush' typo
##### From: Vitaly Kuznetsov <vkuznets@redhat.com>

```c
Regardless of whether your TLB is lush or not it still needs flushing.

Reported-by: Roman Kagan <rkagan@virtuozzo.com>
Signed-off-by: Vitaly Kuznetsov <vkuznets@redhat.com>
Reviewed-by: Roman Kagan <rkagan@virtuozzo.com>
---
 arch/x86/include/asm/kvm_host.h | 2 +-
 arch/x86/kvm/hyperv.c           | 6 +++---
 2 files changed, 4 insertions(+), 4 deletions(-)

```
#### [PATCH v2 1/2] arm/arm64: KVM: rename function kvm_arch_dev_ioctl_check_extension()
##### From: Dongjiu Geng <gengdongjiu@huawei.com>

```c
Rename kvm_arch_dev_ioctl_check_extension() to
kvm_arch_vm_ioctl_check_extension(), because it does
not have any relationship with device.

Renaming this function can make code readable.

Cc: James Morse <james.morse@arm.com>
Signed-off-by: Dongjiu Geng <gengdongjiu@huawei.com>
Reviewed-by: Suzuki K Poulose <suzuki.poulose@arm.com>
---
I remeber James also mentioned that rename this function.
---
 arch/arm/include/asm/kvm_host.h   | 2 +-
 arch/arm64/include/asm/kvm_host.h | 2 +-
 arch/arm64/kvm/reset.c            | 4 ++--
 virt/kvm/arm/arm.c                | 2 +-
 4 files changed, 5 insertions(+), 5 deletions(-)

```
#### [RFC PATCH] KVM: remove the writable page for read fault case in hva_to_pfn_slow()
##### From: Wei Yang <richard.weiyang@gmail.com>

```c
Case (!write_fault && writable) has been handled in hva_to_pfn_fast(),
it is not necessary to try again if hva_to_pfn_fast() already failed.

This patch removes this case in hva_to_pfn_slow().

Signed-off-by: Wei Yang <richard.weiyang@gmail.com>
---

Hope my understanding is correct.

---
 virt/kvm/kvm_main.c | 10 ----------
 1 file changed, 10 deletions(-)

```
#### [PATCH v2 1/1] Add attribute single_usage_restriction for mdev type-id
##### From: Kirti Wankhede <kwankhede@nvidia.com>

```c
Generally a single instance of mdev device, a share of physical device, is
assigned to user space application or a VM. There are cases when multiple
instances of mdev devices of same or different types are required by user
space application or VM. For example in case of vGPU, multiple mdev devices
of type which represents whole GPU can be assigned to one instance of
application or VM.

All types of mdev devices may not support assigning multiple mdev devices
to a user space application. In that case vendor driver can fail open()
call of mdev device. But there is no way to know User space application to
about the configuration supported by vendor driver.

To expose supported configuration, vendor driver should add
'single_usage_restriction' attribute to type-id directory. Returning Y for
this attribute indicates vendor driver has restriction of single mdev
device of particular <type-id> assigned to one user space application.
Returning N indicates that multiple mdev devices of particular <type-id>
can be assigned to one user space application.

User space application should read if 'single_usage_restriction' attibute
is present in <type-id> directory of all mdev devices which are going to be
used. If all read N then user space application can proceed with multiple
mdev devices.

This is optional and readonly attribute.

Signed-off-by: Kirti Wankhede <kwankhede@nvidia.com>
Reviewed-by: Neo Jia <cjia@nvidia.com>
---
 Documentation/ABI/testing/sysfs-bus-vfio-mdev | 16 ++++++++++++++++
 1 file changed, 16 insertions(+)

```
#### [PATCH v2] drivers/vfio: Fix a redundant copy bug
##### From: Wenwen Wang <wang6495@umn.edu>

```c
In vfio_spapr_iommu_eeh_ioctl(), if the ioctl command is VFIO_EEH_PE_OP,
the user-space buffer 'arg' is copied to the kernel object 'op' and the
'argsz' and 'flags' fields of 'op' are checked. If the check fails, an
error code EINVAL is returned. Otherwise, 'op.op' is further checked
through a switch statement to invoke related handlers. If 'op.op' is
VFIO_EEH_PE_INJECT_ERR, the whole user-space buffer 'arg' is copied again
to 'op' to obtain the err information. However, in the following execution
of this case, the fields of 'op', except the field 'err', are actually not
used. That is, the second copy has a redundant part. Therefore, for both
performance consideration, the redundant part of the second copy should be
removed.

This patch removes such a part in the second copy. It only copies from
'err.type' to 'err.mask', which is exactly required by the
VFIO_EEH_PE_INJECT_ERR op.

Signed-off-by: Wenwen Wang <wang6495@umn.edu>
---
 drivers/vfio/vfio_spapr_eeh.c | 9 ++++++---
 1 file changed, 6 insertions(+), 3 deletions(-)

```
#### [PATCH v4 1/9] x86/kvm/mmu: make vcpu->mmu a pointer to the current MMU
##### From: Vitaly Kuznetsov <vkuznets@redhat.com>

```c
As a preparation to full MMU split between L1 and L2 make vcpu->arch.mmu
a pointer to the currently used mmu. For now, this is always
vcpu->arch.root_mmu. No functional change.

Signed-off-by: Vitaly Kuznetsov <vkuznets@redhat.com>
Signed-off-by: Paolo Bonzini <pbonzini@redhat.com>
Reviewed-by: Sean Christopherson <sean.j.christopherson@intel.com>
---
 arch/x86/include/asm/kvm_host.h |   5 +-
 arch/x86/kvm/mmu.c              | 165 ++++++++++++++++----------------
 arch/x86/kvm/mmu.h              |   8 +-
 arch/x86/kvm/mmu_audit.c        |  12 +--
 arch/x86/kvm/paging_tmpl.h      |  15 +--
 arch/x86/kvm/svm.c              |  14 +--
 arch/x86/kvm/vmx.c              |  15 +--
 arch/x86/kvm/x86.c              |  20 ++--
 8 files changed, 130 insertions(+), 124 deletions(-)

```
