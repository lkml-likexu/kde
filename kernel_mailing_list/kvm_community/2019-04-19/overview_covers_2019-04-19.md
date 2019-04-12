

#### [PATCH 0/2] introduction of version attribute for VFIO live migration
##### From: Yan Zhao <yan.y.zhao@intel.com>

```c

This patchset introduces a version attribute under sysfs of VFIO Mediated
devices.

This version attribute is used by user space software like libvirt to
determine whether two mdev devices are compatible for live migration
before starting live migration.

Patch 1 defines version attribute as mandatory for VFIO live migration. It
means if version attribute is missing or it returns errno, the
corresponding mdev device is regarded as not supporting live migration.
samples for vfio-mdev are modified to demonstrate it.

Patch 2 uses GVT as an example to show how to expose version attribute and
check device compatibility in vendor driver.


Yan Zhao (2):
  vfio/mdev: add version field as mandatory attribute for mdev device
  drm/i915/gvt: export mdev device version to sysfs for Intel vGPU

 Documentation/vfio-mediated-device.txt    | 36 +++++++++
 drivers/gpu/drm/i915/gvt/Makefile         |  2 +-
 drivers/gpu/drm/i915/gvt/device_version.c | 94 +++++++++++++++++++++++
 drivers/gpu/drm/i915/gvt/gvt.c            | 55 +++++++++++++
 drivers/gpu/drm/i915/gvt/gvt.h            |  6 ++
 samples/vfio-mdev/mbochs.c                | 17 ++++
 samples/vfio-mdev/mdpy.c                  | 16 ++++
 samples/vfio-mdev/mtty.c                  | 16 ++++
 8 files changed, 241 insertions(+), 1 deletion(-)
 create mode 100644 drivers/gpu/drm/i915/gvt/device_version.c
```
