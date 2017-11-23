

#### [RFC PATCH 0/7] A General Accelerator Framework, WarpDrive
##### From: Kenneth Lee <nek.in.cn@gmail.com>
From: Kenneth Lee <liguozhu@hisilicon.com>

```c

From: Kenneth Lee <liguozhu@hisilicon.com>

WarpDrive is an accelerator framework to expose the hardware capabilities
directly to the user space. It makes use of the exist vfio and vfio-mdev
facilities. So the user application can send request and DMA to the
hardware without interaction with the kernel. This remove the latency
of syscall and context switch.

The patchset contains documents for the detail. Please refer to it for more
information.

This patchset is intended to be used with Jean Philippe Brucker's SVA
patch [1] (Which is also in RFC stage). But it is not mandatory. This
patchset is tested in the latest mainline kernel without the SVA patches.
So it support only one process for each accelerator.

With SVA support, WarpDrive can support multi-process in the same
accelerator device.  We tested it in our SoC integrated Accelerator (board
ID: D06, Chip ID: HIP08). A reference work tree can be found here: [2].

We have noticed the IOMMU aware mdev RFC announced recently [3].

The IOMMU aware mdev has similar idea but different intention comparing to
WarpDrive. It intends to dedicate part of the hardware resource to a VM.
And the design is supposed to be used with Scalable I/O Virtualization.
While spimdev is intended to share the hardware resource with a big amount
of processes.  It just requires the hardware supporting address
translation per process (PCIE's PASID or ARM SMMU's substream ID).

But we don't see serious confliction on both design. We believe they can be
normalized as one.

The patch 1 is document. The patch 2 and 3 add spimdev support. The patch
4, 5 and 6 is drivers for Hislicon's ZIP Accelerator which is registered to
both crypto and warpdrive(spimdev) and can be used from kernel or user
space at the same time. The patch 7 is a user space sample demonstrating
how WarpDrive works.

Refernces:
[1] https://www.spinics.net/lists/kernel/msg2651481.html
[2] https://github.com/Kenneth-Lee/linux-kernel-warpdrive/tree/warpdrive-sva-v0.5
[3] https://lkml.org/lkml/2018/7/22/34

Best Regards
Kenneth Lee

Kenneth Lee (7):
  vfio/spimdev: Add documents for WarpDrive framework
  iommu: Add share domain interface in iommu for spimdev
  vfio: add spimdev support
  crypto: add hisilicon Queue Manager driver
  crypto: Add Hisilicon Zip driver
  crypto: add spimdev support to Hisilicon QM
  vfio/spimdev: add user sample for spimdev

 Documentation/00-INDEX                    |    2 +
 Documentation/warpdrive/warpdrive.rst     |  153 ++++
 Documentation/warpdrive/wd-arch.svg       |  732 +++++++++++++++
 Documentation/warpdrive/wd.svg            |  526 +++++++++++
 drivers/crypto/Kconfig                    |    2 +
 drivers/crypto/Makefile                   |    1 +
 drivers/crypto/hisilicon/Kconfig          |   15 +
 drivers/crypto/hisilicon/Makefile         |    2 +
 drivers/crypto/hisilicon/qm.c             | 1005 +++++++++++++++++++++
 drivers/crypto/hisilicon/qm.h             |  123 +++
 drivers/crypto/hisilicon/zip/Makefile     |    2 +
 drivers/crypto/hisilicon/zip/zip.h        |   55 ++
 drivers/crypto/hisilicon/zip/zip_crypto.c |  358 ++++++++
 drivers/crypto/hisilicon/zip/zip_crypto.h |   18 +
 drivers/crypto/hisilicon/zip/zip_main.c   |  182 ++++
 drivers/iommu/iommu.c                     |   28 +-
 drivers/vfio/Kconfig                      |    1 +
 drivers/vfio/Makefile                     |    1 +
 drivers/vfio/spimdev/Kconfig              |   10 +
 drivers/vfio/spimdev/Makefile             |    3 +
 drivers/vfio/spimdev/vfio_spimdev.c       |  421 +++++++++
 drivers/vfio/vfio_iommu_type1.c           |  136 ++-
 include/linux/iommu.h                     |    2 +
 include/linux/vfio_spimdev.h              |   95 ++
 include/uapi/linux/vfio_spimdev.h         |   28 +
 samples/warpdrive/AUTHORS                 |    2 +
 samples/warpdrive/ChangeLog               |    1 +
 samples/warpdrive/Makefile.am             |    9 +
 samples/warpdrive/NEWS                    |    1 +
 samples/warpdrive/README                  |   32 +
 samples/warpdrive/autogen.sh              |    3 +
 samples/warpdrive/cleanup.sh              |   13 +
 samples/warpdrive/configure.ac            |   52 ++
 samples/warpdrive/drv/hisi_qm_udrv.c      |  223 +++++
 samples/warpdrive/drv/hisi_qm_udrv.h      |   53 ++
 samples/warpdrive/test/Makefile.am        |    7 +
 samples/warpdrive/test/comp_hw.h          |   23 +
 samples/warpdrive/test/test_hisi_zip.c    |  204 +++++
 samples/warpdrive/wd.c                    |  325 +++++++
 samples/warpdrive/wd.h                    |  153 ++++
 samples/warpdrive/wd_adapter.c            |   74 ++
 samples/warpdrive/wd_adapter.h            |   43 +
 42 files changed, 5112 insertions(+), 7 deletions(-)
 create mode 100644 Documentation/warpdrive/warpdrive.rst
 create mode 100644 Documentation/warpdrive/wd-arch.svg
 create mode 100644 Documentation/warpdrive/wd.svg
 create mode 100644 drivers/crypto/hisilicon/Kconfig
 create mode 100644 drivers/crypto/hisilicon/Makefile
 create mode 100644 drivers/crypto/hisilicon/qm.c
 create mode 100644 drivers/crypto/hisilicon/qm.h
 create mode 100644 drivers/crypto/hisilicon/zip/Makefile
 create mode 100644 drivers/crypto/hisilicon/zip/zip.h
 create mode 100644 drivers/crypto/hisilicon/zip/zip_crypto.c
 create mode 100644 drivers/crypto/hisilicon/zip/zip_crypto.h
 create mode 100644 drivers/crypto/hisilicon/zip/zip_main.c
 create mode 100644 drivers/vfio/spimdev/Kconfig
 create mode 100644 drivers/vfio/spimdev/Makefile
 create mode 100644 drivers/vfio/spimdev/vfio_spimdev.c
 create mode 100644 include/linux/vfio_spimdev.h
 create mode 100644 include/uapi/linux/vfio_spimdev.h
 create mode 100644 samples/warpdrive/AUTHORS
 create mode 100644 samples/warpdrive/ChangeLog
 create mode 100644 samples/warpdrive/Makefile.am
 create mode 100644 samples/warpdrive/NEWS
 create mode 100644 samples/warpdrive/README
 create mode 100755 samples/warpdrive/autogen.sh
 create mode 100755 samples/warpdrive/cleanup.sh
 create mode 100644 samples/warpdrive/configure.ac
 create mode 100644 samples/warpdrive/drv/hisi_qm_udrv.c
 create mode 100644 samples/warpdrive/drv/hisi_qm_udrv.h
 create mode 100644 samples/warpdrive/test/Makefile.am
 create mode 100644 samples/warpdrive/test/comp_hw.h
 create mode 100644 samples/warpdrive/test/test_hisi_zip.c
 create mode 100644 samples/warpdrive/wd.c
 create mode 100644 samples/warpdrive/wd.h
 create mode 100644 samples/warpdrive/wd_adapter.c
 create mode 100644 samples/warpdrive/wd_adapter.h
```
