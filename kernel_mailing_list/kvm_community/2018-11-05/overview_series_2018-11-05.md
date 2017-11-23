#### [PATCH 1/2] KVM: use same boundary check for async_pf
##### From: Wei Yang <richard.weiyang@gmail.com>

```c
Commit af585b921e5d ("KVM: Halt vcpu if page it tries to access is
swapped out") introduces async_pf.

The gfn hash table size is defined as:

	gfn_t gfns[roundup_pow_of_two(ASYNC_PF_PER_VCPU)];

And iterations in arch/x86/kvm/x86.c are checked with:

	i < roundup_pow_of_two(ASYNC_PF_PER_VCPU)

While the check in kvm_setup_async_pf() is:

	if (vcpu->async_pf.queued >= ASYNC_PF_PER_VCPU)

Generally this works good, while the check is not exact.

This patch adjust the check in kvm_setup_async_pf() to use the same
boundary as others.

Signed-off-by: Wei Yang <richard.weiyang@gmail.com>
---
 virt/kvm/async_pf.c | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
#### [PATCH] KVM: x86: Remove KF() macro placeholder
##### From: Sean Christopherson <sean.j.christopherson@intel.com>

```c
Although well-intentioned, keeping the KF() definition as a hint for
handling scattered CPUID features may be counter-productive.  Simply
redefining the bit position only works for directly manipulating the
guest's CPUID leafs, e.g. it doesn't make guest_cpuid_has() magically
work.  Taking an alternative approach, e.g. ensuring the bit position
is identical between the Linux-defined and hardware-defined features,
may be a simpler and/or more effective method of exposing scattered
features to the guest.

Signed-off-by: Sean Christopherson <sean.j.christopherson@intel.com>
---
 arch/x86/kvm/cpuid.c | 3 ---
 1 file changed, 3 deletions(-)

```
#### [PATCH 1/5] VSOCK: support fill mergeable rx buffer in guest
##### From: jiangyiwen <jiangyiwen@huawei.com>

```c
In driver probing, if virtio has VIRTIO_VSOCK_F_MRG_RXBUF feature,
it will fill mergeable rx buffer, support for host send mergeable
rx buffer. It will fill a page everytime to compact with small
packet and big packet.

Signed-off-by: Yiwen Jiang <jiangyiwen@huawei.com>
---
 include/linux/virtio_vsock.h     |  3 ++
 net/vmw_vsock/virtio_transport.c | 72 +++++++++++++++++++++++++++++-----------
 2 files changed, 56 insertions(+), 19 deletions(-)

```
#### [PATCH 1/4] KVM: arm64: Rework detection of SVE, !VHE systems
##### From: Marc Zyngier <marc.zyngier@arm.com>

```c
An SVE system is so far the only case where we mandate VHE. As we're
starting to grow this requirements, let's slightly rework the way we
deal with that situation, allowing for easy extension of this check.

Signed-off-by: Marc Zyngier <marc.zyngier@arm.com>
---
 arch/arm/include/asm/kvm_host.h   |  2 +-
 arch/arm64/include/asm/kvm_host.h |  7 ++-----
 virt/kvm/arm/arm.c                | 12 +++++++-----
 3 files changed, 10 insertions(+), 11 deletions(-)

```
#### [RFC PATCH v4 01/13] ktask: add documentation
##### From: Daniel Jordan <daniel.m.jordan@oracle.com>

```c
Motivates and explains the ktask API for kernel clients.

Signed-off-by: Daniel Jordan <daniel.m.jordan@oracle.com>
---
 Documentation/core-api/index.rst |   1 +
 Documentation/core-api/ktask.rst | 213 +++++++++++++++++++++++++++++++
 2 files changed, 214 insertions(+)
 create mode 100644 Documentation/core-api/ktask.rst

```
#### [PATCH v3] vhost/vsock: fix use-after-free in network stack callers
##### From: Stefan Hajnoczi <stefanha@redhat.com>

```c
If the network stack calls .send_pkt()/.cancel_pkt() during .release(),
a struct vhost_vsock use-after-free is possible.  This occurs because
.release() does not wait for other CPUs to stop using struct
vhost_vsock.

Switch to an RCU-enabled hashtable (indexed by guest CID) so that
.release() can wait for other CPUs by calling synchronize_rcu().  This
also eliminates vhost_vsock_lock acquisition in the data path so it
could have a positive effect on performance.

Reported-and-tested-by: syzbot+bd391451452fb0b93039@syzkaller.appspotmail.com
Reported-by: syzbot+e3e074963495f92a89ed@syzkaller.appspotmail.com
Reported-by: syzbot+d5a0a170c5069658b141@syzkaller.appspotmail.com
Signed-off-by: Stefan Hajnoczi <stefanha@redhat.com>
Acked-by: Jason Wang <jasowang@redhat.com>
---
I have now manually tested the RCU hashtable fix and am happy with this
patch.

 drivers/vhost/vsock.c | 57 +++++++++++++++++++++++++------------------
 1 file changed, 33 insertions(+), 24 deletions(-)

```
#### [PATCH v4 1/8] iommu: Add APIs for multiple domains per device
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

The APIs includes:

* iommu_get_dev_attr(dev, IOMMU_DEV_ATTR_AUXD_CAPABILITY)
  - Represents the ability of supporting multiple domains
    per device.

* iommu_get_dev_attr(dev, IOMMU_DEV_ATTR_AUXD_ENABLED)
  - Checks whether the device identified by @dev is working
    in auxiliary mode.

* iommu_set_dev_attr(dev, IOMMU_DEV_ATTR_AUXD_ENABLE)
  - Enables the multiple domains capability for the device
    referenced by @dev.

* iommu_set_dev_attr(dev, IOMMU_DEV_ATTR_AUXD_DISABLE)
  - Disables the multiple domains capability for the device
    referenced by @dev.

* iommu_attach_device_aux(domain, dev)
  - Attaches @domain to @dev in the auxiliary mode. Multiple
    domains could be attached to a single device in the
    auxiliary mode with each domain representing an isolated
    address space for an assignable subset of the device.

* iommu_detach_device_aux(domain, dev)
  - Detach @domain which has been attached to @dev in the
    auxiliary mode.

* iommu_domain_get_attr(domain, DOMAIN_ATTR_AUXD_ID)
  - Return ID used for finer-granularity DMA translation.
    For the Intel Scalable IOV usage model, this will be
    a PASID. The device which supports Scalalbe IOV needs
    to writes this ID to the device register so that DMA
    requests could be tagged with a right PASID prefix.

Many people involved in discussions of this design.

Kevin Tian <kevin.tian@intel.com>
Liu Yi L <yi.l.liu@intel.com>
Ashok Raj <ashok.raj@intel.com>
Sanjay Kumar <sanjay.k.kumar@intel.com>
Jacob Pan <jacob.jun.pan@linux.intel.com>
Alex Williamson <alex.williamson@redhat.com>
Jean-Philippe Brucker <jean-philippe.brucker@arm.com>

and some discussions can be found here [4].

[1] https://software.intel.com/en-us/download/intel-scalable-io-virtualization-technical-specification
[2] https://schd.ws/hosted_files/lc32018/00/LC3-SIOV-final.pdf
[3] https://software.intel.com/en-us/download/intel-virtualization-technology-for-directed-io-architecture-specification
[4] https://lkml.org/lkml/2018/7/26/4

Cc: Ashok Raj <ashok.raj@intel.com>
Cc: Jacob Pan <jacob.jun.pan@linux.intel.com>
Cc: Kevin Tian <kevin.tian@intel.com>
Cc: Liu Yi L <yi.l.liu@intel.com>
Suggested-by: Kevin Tian <kevin.tian@intel.com>
Suggested-by: Jean-Philippe Brucker <jean-philippe.brucker@arm.com>
Signed-off-by: Lu Baolu <baolu.lu@linux.intel.com>
---
 drivers/iommu/iommu.c | 52 +++++++++++++++++++++++++++++++++++++++++++
 include/linux/iommu.h | 52 +++++++++++++++++++++++++++++++++++++++++++
 2 files changed, 104 insertions(+)

```
#### [PATCH] vhost/vsock: switch to a mutex for vhost_vsock_hash
##### From: Stefan Hajnoczi <stefanha@redhat.com>

```c
Now that there are no more data path users of vhost_vsock_lock, it can
be turned into a mutex.  It's only used by .release() and in the
.ioctl() path.

Depends-on: <20181105103547.22018-1-stefanha@redhat.com>
Suggested-by: Jason Wang <jasowang@redhat.com>
Signed-off-by: Stefan Hajnoczi <stefanha@redhat.com>
Acked-by: Jason Wang <jasowang@redhat.com>
---
Hi Jason,
Thanks for pointing out that spin_lock_bh() is no longer necessary.
Let's switch to a mutex.
---
 drivers/vhost/vsock.c | 16 ++++++++--------
 1 file changed, 8 insertions(+), 8 deletions(-)

```
