#### [PATCH] KVM: nVMX: Restore a preemption timer consistency check
##### From: Sean Christopherson <sean.j.christopherson@intel.com>

```c
A recently added preemption timer consistency check was unintentionally
dropped when the consistency checks were being reorganized to match the
SDM's ordering.

Fixes: 461b4ba4c7ad ("KVM: nVMX: Move the checks for VM-Execution Control Fields to a separate helper function")
Cc: Krish Sadhukhan <krish.sadhukhan@oracle.com>
Signed-off-by: Sean Christopherson <sean.j.christopherson@intel.com>
---

The original bug fix, commit 14aa61d0a9eb ("nVMX x86: Check VMX-preemption
timer controls on vmentry of L2 guests"), was added in the v5.0 merge
window, i.e. this doesn't need to be backported to stable, but it should
get pushed to v5.0-rc7 if possible.

 arch/x86/kvm/vmx/nested.c | 4 ++++
 1 file changed, 4 insertions(+)

```
#### [tip:core/rcu] virt/kvm: Replace spin_is_locked() with lockdepGit-Commit-ID: 6706dae90d85d394d0134d0ec516c25560b9ce77
##### From: "tip-bot for Paul E. McKenney" <tipbot@zytor.com>

```c
Commit-ID:  6706dae90d85d394d0134d0ec516c25560b9ce77
Gitweb:     https://git.kernel.org/tip/6706dae90d85d394d0134d0ec516c25560b9ce77
Author:     Paul E. McKenney <paulmck@linux.ibm.com>
AuthorDate: Tue, 8 Jan 2019 10:39:49 -0800
Committer:  Paul E. McKenney <paulmck@linux.ibm.com>
CommitDate: Fri, 25 Jan 2019 15:36:05 -0800

virt/kvm: Replace spin_is_locked() with lockdep

lockdep_assert_held() is better suited to checking locking requirements,
since it only checks if the current thread holds the lock regardless of
whether someone else does. This is also a step towards possibly removing
spin_is_locked().

Signed-off-by: Paul E. McKenney <paulmck@linux.ibm.com>
Cc: Paolo Bonzini <pbonzini@redhat.com>
Cc: "Radim Krčmář" <rkrcmar@redhat.com>
Cc: <kvm@vger.kernel.org>
Acked-by: Paolo Bonzini <pbonzini@redhat.com>
---
 virt/kvm/kvm_main.c | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
#### [PATCH V2 1/7] mm/gup: Replace get_user_pages_longterm() with FOLL_LONGTERM
##### From: ira.weiny@intel.com

```c
From: Ira Weiny <ira.weiny@intel.com>

Rather than have a separate get_user_pages_longterm() call,
introduce FOLL_LONGTERM and change the longterm callers to use
it.

This patch does not change any functionality.

FOLL_LONGTERM can only be supported with get_user_pages() as it
requires vmas to determine if DAX is in use.

Signed-off-by: Ira Weiny <ira.weiny@intel.com>
---
 drivers/infiniband/core/umem.c             |   5 +-
 drivers/infiniband/hw/qib/qib_user_pages.c |   8 +-
 drivers/infiniband/hw/usnic/usnic_uiom.c   |   9 +-
 drivers/media/v4l2-core/videobuf-dma-sg.c  |   6 +-
 drivers/vfio/vfio_iommu_type1.c            |   3 +-
 include/linux/mm.h                         |  13 +-
 mm/gup.c                                   | 138 ++++++++++++---------
 mm/gup_benchmark.c                         |   5 +-
 8 files changed, 101 insertions(+), 86 deletions(-)

```
#### [PATCH v2] vfio_pci: Enable memory accesses before calling pci_map_rom
##### From: Eric Auger <eric.auger@redhat.com>

```c
pci_map_rom/pci_get_rom_size() performs memory access in the ROM.
In case the Memory Space accesses were disabled, readw() is likely to
crash the host with a synchronous external abort (aarch64).

In case memory accesses were disabled, re-enable them before the call
and disable them back again just after.

Signed-off-by: Eric Auger <eric.auger@redhat.com>
---

v1 -> v2:
- also re-enable in case of error
---
 drivers/vfio/pci/vfio_pci.c | 17 ++++++++++++++++-
 1 file changed, 16 insertions(+), 1 deletion(-)

```
#### [PATCH v6 1/9] iommu: Add APIs for multiple domains per device
##### From: Lu Baolu <baolu.lu@linux.intel.com>

```c
Sharing a physical PCI device in a finer-granularity way
is becoming a consensus in the industry. IOMMU vendors
are also engaging efforts to support such sharing as well
as possible. Among the efforts, the capability of support
finer-granularity DMA isolation is a common requirement
due to the security consideration. With finer-granularity
DMA isolation, all DMA requests out of or to a subset of
a physical PCI device can be protected by the IOMMU. As a
result, there is a request in software to attach multiple
domains to a physical PCI device. One example of such use
model is the Intel Scalable IOV [1] [2]. The Intel vt-d
3.0 spec [3] introduces the scalable mode which enables
PASID granularity DMA isolation.

This adds the APIs to support multiple domains per device.
In order to ease the discussions, we call it 'a domain in
auxiliary mode' or simply 'auxiliary domain' when multiple
domains are attached to a physical device.

The APIs include:

* iommu_dev_has_feature(dev, IOMMU_DEV_FEAT_AUX)
  - Check whether both IOMMU and device support IOMMU aux
    domain feature. Below aux-domain specific interfaces
    are available only after this returns true.

* iommu_dev_enable/disable_feature(dev, IOMMU_DEV_FEAT_AUX)
  - Enable/disable device specific aux-domain feature.

* iommu_dev_feature_enabled(dev, IOMMU_DEV_FEAT_AUX)
  - Check whether the aux domain specific feature enabled or
    not.

* iommu_aux_attach_device(domain, dev)
  - Attaches @domain to @dev in the auxiliary mode. Multiple
    domains could be attached to a single device in the
    auxiliary mode with each domain representing an isolated
    address space for an assignable subset of the device.

* iommu_aux_detach_device(domain, dev)
  - Detach @domain which has been attached to @dev in the
    auxiliary mode.

* iommu_aux_get_pasid(domain, dev)
  - Return ID used for finer-granularity DMA translation.
    For the Intel Scalable IOV usage model, this will be
    a PASID. The device which supports Scalable IOV needs
    to write this ID to the device register so that DMA
    requests could be tagged with a right PASID prefix.

This has been updated with the latest proposal from Joerg
posted here [5].

Many people involved in discussions of this design.

Kevin Tian <kevin.tian@intel.com>
Liu Yi L <yi.l.liu@intel.com>
Ashok Raj <ashok.raj@intel.com>
Sanjay Kumar <sanjay.k.kumar@intel.com>
Jacob Pan <jacob.jun.pan@linux.intel.com>
Alex Williamson <alex.williamson@redhat.com>
Jean-Philippe Brucker <jean-philippe.brucker@arm.com>
Joerg Roedel <joro@8bytes.org>

and some discussions can be found here [4] [5].

[1] https://software.intel.com/en-us/download/intel-scalable-io-virtualization-technical-specification
[2] https://schd.ws/hosted_files/lc32018/00/LC3-SIOV-final.pdf
[3] https://software.intel.com/en-us/download/intel-virtualization-technology-for-directed-io-architecture-specification
[4] https://lkml.org/lkml/2018/7/26/4
[5] https://www.spinics.net/lists/iommu/msg31874.html

Cc: Ashok Raj <ashok.raj@intel.com>
Cc: Jacob Pan <jacob.jun.pan@linux.intel.com>
Cc: Kevin Tian <kevin.tian@intel.com>
Cc: Liu Yi L <yi.l.liu@intel.com>
Suggested-by: Kevin Tian <kevin.tian@intel.com>
Suggested-by: Jean-Philippe Brucker <jean-philippe.brucker@arm.com>
Suggested-by: Joerg Roedel <jroedel@suse.de>
Signed-off-by: Lu Baolu <baolu.lu@linux.intel.com>
---
 drivers/iommu/iommu.c | 91 +++++++++++++++++++++++++++++++++++++++++++
 include/linux/iommu.h | 70 +++++++++++++++++++++++++++++++++
 2 files changed, 161 insertions(+)

```
#### [PATCH] vfio_pci: Enable memory accesses before calling pci_map_rom
##### From: Eric Auger <eric.auger@redhat.com>

```c
pci_map_rom/pci_get_rom_size() performs memory access in the ROM.
In case the Memory Space accesses were disabled, readw() is likely to
crash the host with a synchronous external abort (aarch64).

In case memory accesses were disabled, re-enable them before the call
and disable them back again just after.

Signed-off-by: Eric Auger <eric.auger@redhat.com>
---
 drivers/vfio/pci/vfio_pci.c | 14 ++++++++++++++
 1 file changed, 14 insertions(+)

```
