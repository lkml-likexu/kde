

#### [PATCH 0/5] target/i386: introduce coalesced pio
##### From: Peng Hao <peng.hao2@zte.com.cn>

```c

Coalesced pio is base on coalesced mmio and can be used for some port
like rtc port, pci-host config port and so on.

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

Peng Hao (5):
  target-i386: add rtc 0x70 port as coalesced_pio
  target-i386: add i440fx 0xcf8 port as coalesced_pio
  target-i386: add q35 0xcf8 port as coalesced_pio
  target/i386: add coalesced pio support
  target-i386: add coalesced_pio API

 accel/kvm/kvm-all.c       | 60 +++++++++++++++++++++++++++++++++++++++++++----
 hw/pci-host/piix.c        |  4 ++++
 hw/pci-host/q35.c         |  4 ++++
 hw/timer/mc146818rtc.c    |  8 +++++++
 include/exec/memory.h     |  4 ++--
 linux-headers/linux/kvm.h |  9 ++++++-
 memory.c                  |  4 ++--
 7 files changed, 83 insertions(+), 10 deletions(-)
```
#### [PATCH v3 0/6] VFIO mdev aggregated resources handling
##### From: Zhenyu Wang <zhenyuw@linux.intel.com>

```c

Current mdev device create interface depends on fixed mdev type, which get uuid
from user to create instance of mdev device. If user wants to use customized
number of resource for mdev device, then only can create new mdev type for that
which may not be flexible. This requirement comes not only from to be able to
allocate flexible resources for KVMGT, but also from Intel scalable IO
virtualization which would use vfio/mdev to be able to allocate arbitrary
resources on mdev instance. More info on [1] [2] [3].

To allow to create user defined resources for mdev, it trys to extend mdev
create interface by adding new "aggregate=xxx" parameter following UUID, for
target mdev type if aggregation is supported, it can create new mdev device
which contains resources combined by number of instances, e.g

    echo "<uuid>,aggregate=10" > create

VM manager e.g libvirt can check mdev type with "aggregation" attribute which
can support this setting. If no "aggregation" attribute found for mdev type,
previous behavior is still kept for one instance allocation. And new sysfs
attribute "aggregated_instances" is created for each mdev device to show allocated number.

References:
[1] https://software.intel.com/en-us/download/intel-virtualization-technology-for-directed-io-architecture-specification
[2] https://software.intel.com/en-us/download/intel-scalable-io-virtualization-technical-specification  
[3] https://schd.ws/hosted_files/lc32018/00/LC3-SIOV-final.pdf

v2:
  - Add new create_with_instances driver hook
  - Update doc for new attributes

v3:
  - Rename parameter and attribute names from review
  - Make "aggregation" attribute to show maxium resource number
    for aggregation
  - Check driver hooks for attribute create validation
  - Update doc and ABI spec

Zhenyu Wang (6):
  vfio/mdev: Add new "aggregate" parameter for mdev create
  vfio/mdev: Add "aggregation" attribute for supported mdev type
  vfio/mdev: Add "aggregated_instances" attribute for supported mdev
    device
  Documentation/vfio-mediated-device.txt: Update for vfio/mdev
    aggregation support
  Documentation/ABI/testing/sysfs-bus-vfio-mdev: Update for vfio/mdev
    aggregation support
  drm/i915/gvt: Add new type with aggregation support

 Documentation/ABI/testing/sysfs-bus-vfio-mdev | 25 +++++++
 Documentation/vfio-mediated-device.txt        | 44 +++++++++--
 drivers/gpu/drm/i915/gvt/gvt.h                | 11 ++-
 drivers/gpu/drm/i915/gvt/kvmgt.c              | 53 ++++++++++++-
 drivers/gpu/drm/i915/gvt/vgpu.c               | 56 +++++++++++++-
 drivers/vfio/mdev/mdev_core.c                 | 40 +++++++++-
 drivers/vfio/mdev/mdev_private.h              |  6 +-
 drivers/vfio/mdev/mdev_sysfs.c                | 74 ++++++++++++++++++-
 include/linux/mdev.h                          | 19 +++++
 9 files changed, 305 insertions(+), 23 deletions(-)
```
