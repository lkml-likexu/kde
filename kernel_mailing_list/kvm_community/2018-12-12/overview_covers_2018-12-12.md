

#### [PATCH 0/4] KVM: PPC: Book3S HV: Improve live migration of radix
##### From: Paul Mackerras <paulus@ozlabs.org>

```c

We have observed that live migration of radix guests tends to converge
slowly and sometimes doesn't converge at all.  This appears to be due
largely to the fact that if the host is using transparent huge pages,
page dirtiness only gets tracked with a 2MB granularity for the parts
of the guest memory that are mapped using 2MB pages.  The fix is to
break down the mappings in the partition-scoped page tables to 64k
pages (or 4k pages if 4k is the system page size).  This is
accomplished by flushing the partition-scoped page tables when turning
dirty page tracking on or off, and by only inserting small-page PTEs
into the partition-scoped page tables while dirty page tracking is
enabled.

Paul.

 arch/powerpc/include/asm/kvm_book3s.h    | 11 +++++-----
 arch/powerpc/include/asm/kvm_book3s_64.h |  2 +-
 arch/powerpc/include/asm/kvm_ppc.h       |  6 ++++--
 arch/powerpc/kvm/book3s.c                |  5 +++--
 arch/powerpc/kvm/book3s_64_mmu_hv.c      |  9 ++++----
 arch/powerpc/kvm/book3s_64_mmu_radix.c   | 37 ++++++++++++++++++++++++++------
 arch/powerpc/kvm/book3s_hv.c             | 20 ++++++++++++++++-
 arch/powerpc/kvm/book3s_hv_nested.c      |  2 +-
 arch/powerpc/kvm/book3s_hv_rm_mmu.c      |  2 +-
 arch/powerpc/kvm/book3s_pr.c             |  3 ++-
 arch/powerpc/kvm/powerpc.c               |  2 +-
 11 files changed, 73 insertions(+), 26 deletions(-)
```
#### [PATCH v2 0/5] VSOCK: support mergeable rx buffer in vhost-vsock
##### From: jiangyiwen <jiangyiwen@huawei.com>

```c

Now vsock only support send/receive small packet, it can't achieve
high performance. As previous discussed with Jason Wang, I revisit the
idea of vhost-net about mergeable rx buffer and implement the mergeable
rx buffer in vhost-vsock, it can allow big packet to be scattered in
into different buffers and improve performance obviously.

This series of patches mainly did three things：
- mergeable buffer implementation
- increase the max send pkt size
- add used and signal guest in a batch

And I write a tool to test the vhost-vsock performance, mainly send big
packet(64K) included guest->Host and Host->Guest. I test performance
independently and the result as follows:

Before performance:
              Single socket            Multiple sockets(Max Bandwidth)
Guest->Host   ~400MB/s                 ~480MB/s
Host->Guest   ~1450MB/s                ~1600MB/s

After performance only use implement mergeable rx buffer:
              Single socket            Multiple sockets(Max Bandwidth)
Guest->Host   ~400MB/s                 ~480MB/s
Host->Guest   ~1280MB/s                ~1350MB/s

In this case, max send pkt size is still limited to 4K, so Host->Guest
performance will worse than before.

After performance increase the max send pkt size to 64K:
              Single socket            Multiple sockets(Max Bandwidth)
Guest->Host   ~1700MB/s                ~2900MB/s
Host->Guest   ~1500MB/s                ~2440MB/s

After performance all patches are used:
              Single socket            Multiple sockets(Max Bandwidth)
Guest->Host   ~1700MB/s                ~2900MB/s
Host->Guest   ~1700MB/s                ~2900MB/s

From the test results, the performance is improved obviously, and guest
memory will not be wasted.

In addition, in order to support mergeable rx buffer in virtio-vsock,
we need to add a qemu patch to support parse feature.
---
v1 -> v2:
 * Addressed comments from Jason Wang.
 * Add performance test result independently.
 * Use Skb_page_frag_refill() which can use high order page and reduce
   the stress of page allocator.
 * Still use fixed size(PAGE_SIZE) to fill rx buffer, because too small
   size can't fill one full packet, we only 128 vq num now.
 * Use iovec to replace buf in struct virtio_vsock_pkt, keep tx and rx
   consistency.
 * Add virtio_transport ops to get max pkt len, in order to be compatible
   with old version.
---

Yiwen Jiang (5):
  VSOCK: support fill mergeable rx buffer in guest
  VSOCK: support fill data to mergeable rx buffer in host
  VSOCK: support receive mergeable rx buffer in guest
  VSOCK: increase send pkt len in mergeable mode to improve performance
  VSOCK: batch sending rx buffer to increase bandwidth

 drivers/vhost/vsock.c                   | 183 ++++++++++++++++++++-----
 include/linux/virtio_vsock.h            |  13 +-
 include/uapi/linux/virtio_vsock.h       |   5 +
 net/vmw_vsock/virtio_transport.c        | 229 +++++++++++++++++++++++++++-----
 net/vmw_vsock/virtio_transport_common.c |  66 ++++++---
 5 files changed, 411 insertions(+), 85 deletions(-)
```
#### [PATCH net V2 0/4] Fix various issue of vhost
##### From: Jason Wang <jasowang@redhat.com>

```c

Hi:

This series tries to fix various issues of vhost:

- Patch 1 adds a missing write barrier between used idx updating and
  logging.
- Patch 2-3 brings back the protection of device IOTLB through vq
  mutex, this fixes possible use after free in device IOTLB entries.
- Patch 4-7 fixes the diry page logging when device IOTLB is
  enabled. We should done through GPA instead of GIOVA, this was done
  through intorudce HVA->GPA reverse mapping and convert HVA to GPA
  during logging dirty pages.

Please consider them for -stable.

Thanks

Changes from V1:
- silent compiler warning for 32bit.
- use mutex_trylock() on slowpath instead of mutex_lock() even on fast
  path.

Jason Wang (4):
  vhost: make sure used idx is seen before log in vhost_add_used_n()
  vhost_net: switch to use mutex_trylock() in vhost_net_busy_poll()
  Revert "net: vhost: lock the vqs one by one"
  vhost: log dirty page correctly

 drivers/vhost/net.c   |  11 ++++-
 drivers/vhost/vhost.c | 102 ++++++++++++++++++++++++++++++++++--------
 drivers/vhost/vhost.h |   3 +-
 3 files changed, 95 insertions(+), 21 deletions(-)
```
#### [PATCH v2 0/2] x86/kvm/hyper-v: Direct Mode stimers fixes
##### From: Vitaly Kuznetsov <vkuznets@redhat.com>

```c

Changes in v2:
- PATCH2 added [Roman Kagan]

This is a follow-up to my "x86/kvm/hyper-v: direct mode for synthetic
timers" series. Roman identified a couple of issues with the patchset:
we don't check that the supplied APIC vector is valid and we care about
EOI for nothing. These can be merged with the original patch implementing
direct mode stimers or just put on top.

Vitaly Kuznetsov (2):
  x86/hyper-v: Stop caring about EOI for direct stimers
  x86/kvm/hyper-v: disallow setting illegal vectors for direct mode
    stimers

 arch/x86/kvm/hyperv.c | 41 ++++++++---------------------------------
 1 file changed, 8 insertions(+), 33 deletions(-)
```
