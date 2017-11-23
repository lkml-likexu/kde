

#### [RFC PATCH v2 00/10] vfio/mdev: IOMMU aware mediated device
##### From: Lu Baolu <baolu.lu@linux.intel.com>

```c

Hi,

The Mediate Device is a framework for fine-grained physical device
sharing across the isolated domains. Currently the mdev framework
is designed to be independent of the platform IOMMU support. As the
result, the DMA isolation relies on the mdev parent device in a
vendor specific way.

There are several cases where a mediated device could be protected
and isolated by the platform IOMMU. For example, Intel vt-d rev3.0
[1] introduces a new translation mode called 'scalable mode', which
enables PASID-granular translations. The vt-d scalable mode is the
key ingredient for Scalable I/O Virtualization [2] [3] which allows
sharing a device in minimal possible granularity (ADI - Assignable
Device Interface).

A mediated device backed by an ADI could be protected and isolated
by the IOMMU since 1) the parent device supports tagging an unique
PASID to all DMA traffic out of the mediated device; and 2) the DMA
translation unit (IOMMU) supports the PASID granular translation.
We can apply IOMMU protection and isolation to this kind of devices
just as what we are doing with an assignable PCI device.

In order to distinguish the IOMMU-capable mediated devices from those
which still need to rely on parent devices, this patch set adds a
domain type attribute to each mdev.

enum mdev_domain_type {
	DOMAIN_TYPE_NO_IOMMU,	/* Don't need any IOMMU support.
				 * All isolation and protection
				 * are handled by the parent
				 * device driver with a device
				 * specific mechanism.
				 */
	DOMAIN_TYPE_ATTACH_PARENT, /* IOMMU can isolate and protect
				    * the mdev, and the isolation
				    * domain should be attaced with
				    * the parent device.
				    */
};

The mdev parent device driver could opt-in whether an mdev is IOMMU
capable when the device is created by invoking below interface within
its @create callback:

int mdev_set_domain_type(struct device *dev,
                         enum mdev_domain_type type);

In the vfio_iommu_type1_attach_group(), a domain allocated through
iommu_domain_alloc() will be attached to the mdev parent device if
the domain types of mdev devices in group are of type ATTACH_PARENT;
Otherwise, the dummy external domain will be used and all the DMA
isolation and protection are routed to parent driver as the result.

On IOMMU side, a basic requirement is allowing to attach multiple
domains for a PCI device if the device advertises the capability
and the IOMMU hardware supports finer granularity translations than
the normal PCI Source ID based translation.

In order for the ease of discussion, we call "a domain in auxiliary
mode' or simply 'an auxiliary domain' when a domain is attached to
a device for finer granularity translations (than the Source ID based
one). But we need to keep in mind that this doesn't mean two types of
domains. A same domain could be bound to a device for Source ID based
translation, and bound to another device for finer granularity
translation at the same time.

Below APIs are introduced in the IOMMU glue for device drivers to use
the finer granularity translation.

* iommu_capable(IOMMU_CAP_AUX_DOMAIN)
  - Represents the ability for supporting multiple domains per device
    (a.k.a. finer granularity translations) of the IOMMU hardware.
    
* iommu_en(dis)able_aux_domain(struct device *dev)
  - Enable/disable the multiple domains capability for a device
    referenced by @dev.

* iommu_auxiliary_id(struct iommu_domain *domain)
  - Return the index value used for finer-granularity DMA translation.
    The specific device driver needs to feed the hardware with this
    value, so that hardware device could issue the DMA transaction with
    this value tagged.

This patch series extends both IOMMU and vfio components to support
mdev device passing through when it could be isolated and protected
by the IOMMU units. The first part of this series (PATCH 1/10 ~ 6/10)
adds the interfaces and implementation of the multiple domains per
device. The second part (PATCH 7/12 ~ 10/12) adds the domain type
attribute to each mdev, determines domain type according to the
attribute when attaching group in vfio type1 iommu module, and bind
an auxiliary domain for the group with all mediated devices which
requires its own domain.

This patch series depends on a patch set posted here [4] for discussion
which added the support for scalable mode in Intel IOMMU driver.

References:
[1] https://software.intel.com/en-us/download/intel-virtualization-technology-for-directed-io-architecture-specification
[2] https://software.intel.com/en-us/download/intel-scalable-io-virtualization-technical-specification
[3] https://schd.ws/hosted_files/lc32018/00/LC3-SIOV-final.pdf
[4] https://lkml.org/lkml/2018/8/30/27

Best regards,
Lu Baolu

Change log:
  v1->v2:
  - Rewrite the patches with the concept of auxiliary domains.

Lu Baolu (10):
  iommu: Add APIs for multiple domains per device
  iommu/vt-d: Add multiple domains per device query
  iommu/amd: Add default branch in amd_iommu_capable()
  iommu/vt-d: Enable/disable multiple domains per device
  iommu/vt-d: Attach/detach domains in auxiliary mode
  iommu/vt-d: Return ID associated with an auxiliary domain
  vfio/mdev: Add mediated device domain type
  vfio/type1: Add domain at(de)taching group helpers
  vfio/type1: Determine domain type of an mdev group
  vfio/type1: Attach domain for mdev group

 drivers/iommu/amd_iommu.c        |   2 +
 drivers/iommu/intel-iommu.c      | 208 ++++++++++++++++++++++++++++++-
 drivers/iommu/iommu.c            |  29 +++++
 drivers/vfio/mdev/mdev_core.c    |  36 ++++++
 drivers/vfio/mdev/mdev_private.h |   2 +
 drivers/vfio/vfio_iommu_type1.c  | 144 +++++++++++++++++++--
 include/linux/intel-iommu.h      |  11 ++
 include/linux/iommu.h            |  13 ++
 include/linux/mdev.h             |  26 ++++
 9 files changed, 455 insertions(+), 16 deletions(-)
```
#### [PATCH V5 0/4] introduce coalesced pio support
##### From: Peng Hao <peng.hao2@zte.com.cn>

```c

Coalesced pio is base on coalesced mmio and can be used for some port
like rtc port, pci-host config port, virtio-pci config port and so on.

Specially in case of rtc as coalesced pio, some versions of windows guest
access rtc frequently because of rtc as system tick. guest access rtc like
this: write register index to 0x70, then write or read data from 0x71.
writing 0x70 port is just as index and do nothing else. So we can use
coalesced pio to handle this scene to reduce VM-EXIT time.

When it starts and closes the virtual machine, it will access pci-host config
port or virtio-pci config port frequently. So setting these port as
coalesced pio can reduce startup and shutdown time. In qemu I just realize
piixfx's pci-host, it is convenient for other pci-host type implementations.

without my patch, get the vm-exit time of accessing rtc 0x70 and piix 0xcf8
using perf tools: (guest OS : windows 7 64bit)
IO Port Access  Samples Samples%  Time%  Min Time  Max Time  Avg time
0x70:POUT        86     30.99%    74.59%   9us      29us    10.75us (+- 3.41%)
0xcf8:POUT     1119     2.60%     2.12%   2.79us    56.83us 3.41us (+- 2.23%)

with my patch
IO Port Access  Samples Samples%  Time%   Min Time  Max Time   Avg time
0x70:POUT       106    32.02%    29.47%    0us      10us     1.57us (+- 7.38%)
0xcf8:POUT      1065    1.67%     0.28%   0.41us    65.44us   0.66us (+- 10.55%)

These are just qemu's patches, another patches are for kernel.

Changes v4 --> v5:
   update kvm header, improve compatibility.

Changes v3 --> v4
   modify coalesced_mmio_{add|del} to coalesced_io_{add|del}
   delete unnecessary macro define

Peng Hao (4):
  target-i386: introduce coalesced_pio kvm header update
  target-i386: add coalesced_pio API
  target-i386: add rtc 0x70 port as coalesced_pio
  target-i386: add i440fx 0xcf8 port as coalesced_pio

 accel/kvm/kvm-all.c       | 61 ++++++++++++++++++++++++++++++++++++++++++-----
 hw/pci-host/piix.c        |  4 ++++
 hw/timer/mc146818rtc.c    |  8 +++++++
 include/exec/memory.h     |  4 ++--
 linux-headers/linux/kvm.h | 11 +++++++--
 memory.c                  |  4 ++--
 6 files changed, 80 insertions(+), 12 deletions(-)
```
#### [PATCH V4 0/2] introduce coalesced pio support
##### From: Peng Hao <peng.hao2@zte.com.cn>

```c

Coalesced pio is base on coalesced mmio and can be used for some port
like rtc port, pci-host config port, virtio-pci config port and so on.

Specially in case of rtc as coalesced pio, some versions of windows guest
access rtc frequently because of rtc as system tick. guest access rtc like
this: write register index to 0x70, then write or read data from 0x71.
writing 0x70 port is just as index and do nothing else. So we can use
coalesced pio to handle this scene to reduce VM-EXIT time.

When it starts and closes the virtual machine, it will access pci-host config
port or virtio-pci config port frequently. So setting these port as
coalesced pio can reduce startup and shutdown time. In qemu I just realize
piixfx's pci-host, it is convenient for other pci-host type implementations.

without my patch, get the vm-exit time of accessing rtc 0x70 and piix 0xcf8
using perf tools: (guest OS : windows 7 64bit)
IO Port Access  Samples Samples%  Time%  Min Time  Max Time  Avg time
0x70:POUT        86     30.99%    74.59%   9us      29us    10.75us (+- 3.41%)
0xcf8:POUT     1119     2.60%     2.12%   2.79us    56.83us 3.41us (+- 2.23%)

with my patch
IO Port Access  Samples Samples%  Time%   Min Time  Max Time   Avg time
0x70:POUT       106    32.02%    29.47%    0us      10us     1.57us (+- 7.38%)
0xcf8:POUT      1065    1.67%     0.28%   0.41us    65.44us   0.66us (+- 10.55%)


Peng Hao (2):
  kvm/x86 : add coalesced pio support
  kvm/x86 : add document for coalesced pio

 Documentation/virtual/kvm/00-INDEX          |  2 ++
 Documentation/virtual/kvm/coalesced-pio.txt | 15 ++++++++++++++
 include/uapi/linux/kvm.h                    | 11 +++++++++--
 virt/kvm/coalesced_mmio.c                   | 12 +++++++++---
 virt/kvm/kvm_main.c                         |  2 ++
 5 files changed, 37 insertions(+), 5 deletions(-)
 create mode 100644 Documentation/virtual/kvm/coalesced-pio.txt
```
#### [PATCH kvm-unit-tests 0/2] Support micro operation measurement on
##### From: Andrew Jones <drjones@redhat.com>

```c

I dropped the version numbers, but this is v4 of Shih-Wei Li's series of
the same name, last posted in January. I took the liberty of
incorporating all the comments v3 had, plus making some other cleanup
tweaks. These tests are too nice to let them slip away, let's get them
reviewed and merged.

Thanks,
drew

Shih-Wei Li (2):
  arm/arm64: add GICD_IIDR definition
  arm64: add micro-bench

 arm/Makefile.arm64 |   1 +
 arm/micro-bench.c  | 213 +++++++++++++++++++++++++++++++++++++++++++++
 arm/unittests.cfg  |   8 ++
 lib/arm/asm/gic.h  |   1 +
 4 files changed, 223 insertions(+)
 create mode 100644 arm/micro-bench.c
```
