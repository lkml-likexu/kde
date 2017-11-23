

#### [PATCH v2 0/2] virtio-balloon: tweak config_changed
##### From: Wei Wang <wei.w.wang@intel.com>

```c

Since virtio-ccw doesn't work with accessing to the config space
inside an interrupt context, this patch series avoids that issue by
moving the config register accesses to the related workqueue contexts.

v1->v2 ChangeLog:
    - add config_read_bitmap to indicate to the workqueue callbacks about
      the necessity of reading the related config fields.

Wei Wang (2):
  virtio-balloon: tweak config_changed implementation
  virtio-balloon: improve update_balloon_size_func

 drivers/virtio/virtio_balloon.c | 86 +++++++++++++++++++++++++++--------------
 1 file changed, 57 insertions(+), 29 deletions(-)
```
#### [PATCH 00/11] X86/KVM/Hyper-V: Add HV ept tlb range list flush
##### From: lantianyu1986@gmail.com
X-Google-Original-From: Tianyu.Lan@microsoft.com
From: Lan Tianyu <Tianyu.Lan@microsoft.com>

```c

From: Lan Tianyu <Tianyu.Lan@microsoft.com>

This patchset is to introduce hv ept tlb range list flush function
support in the KVM MMU component. Flushing ept tlbs of several address
range can be done via single hypercall and new list flush function is
used in the kvm_mmu_commit_zap_page() and FNAME(sync_page). This patchset
also adds more hv ept tlb range flush support in more KVM MMU function.

Lan Tianyu (11):
  X86/Hyper-V: Add parameter offset for
    hyperv_fill_flush_guest_mapping_list()
  KVM/VMX: Fill range list in kvm_fill_hv_flush_list_func()
  KVM: Add spte's point in the struct kvm_mmu_page
  KVM/MMU: Introduce tlb flush with range list
  KVM/MMU: Flush tlb directly in the kvm_mmu_slot_gfn_write_protect()
  KVM/MMU: Flush tlb with range list in sync_page()
  KVM: Remove redundant check in the kvm_get_dirty_log_protect()
  KVM: Make kvm_arch_mmu_enable_log_dirty_pt_masked() return value
  KVM/MMU: Flush tlb in the kvm_mmu_write_protect_pt_masked()
  KVM: Add flush parameter for kvm_age_hva()
  KVM/MMU: Flush tlb in the kvm_age_rmapp()

 arch/arm/include/asm/kvm_host.h     |  3 +-
 arch/arm64/include/asm/kvm_host.h   |  3 +-
 arch/mips/include/asm/kvm_host.h    |  3 +-
 arch/mips/kvm/mmu.c                 |  8 +++-
 arch/powerpc/include/asm/kvm_host.h |  3 +-
 arch/powerpc/kvm/book3s.c           |  3 +-
 arch/powerpc/kvm/e500_mmu_host.c    |  3 +-
 arch/x86/hyperv/nested.c            |  4 +-
 arch/x86/include/asm/kvm_host.h     | 11 +++++-
 arch/x86/include/asm/mshyperv.h     |  2 +-
 arch/x86/kvm/mmu.c                  | 73 ++++++++++++++++++++++++++++++++-----
 arch/x86/kvm/paging_tmpl.h          | 18 ++++++++-
 arch/x86/kvm/vmx/vmx.c              | 18 ++++++++-
 include/linux/kvm_host.h            |  2 +-
 virt/kvm/arm/mmu.c                  |  8 +++-
 virt/kvm/kvm_main.c                 | 18 ++++-----
 16 files changed, 141 insertions(+), 39 deletions(-)
```
