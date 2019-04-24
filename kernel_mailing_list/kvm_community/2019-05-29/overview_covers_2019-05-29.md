

#### [PATCH v3 0/8] s390: virtio: support protected virtualization
##### From: Michael Mueller <mimu@linux.ibm.com>

```c

Enhanced virtualization protection technology may require the use of
bounce buffers for I/O. While support for this was built into the virtio
core, virtio-ccw wasn't changed accordingly.

Some background on technology (not part of this series) and the
terminology used.

* Protected Virtualization (PV):

Protected Virtualization guarantees, that non-shared memory of a  guest
that operates in PV mode private to that guest. I.e. any attempts by the
hypervisor or other guests to access it will result in an exception. If
supported by the environment (machine, KVM, guest VM) a guest can decide
to change into PV mode by doing the appropriate ultravisor calls.

* Ultravisor:

A hardware/firmware entity that manages PV guests, and polices access to
their memory. A PV guest prospect needs to interact with the ultravisor,
to enter PV mode, and potentially to share pages (for I/O which should
be encrypted by the guest). A guest interacts with the ultravisor via so
called ultravisor calls. A hypervisor needs to interact with the
ultravisor to facilitate interpretation, emulation and swapping. A
hypervisor  interacts with the ultravisor via ultravisor calls and via
the SIE state description. Generally the ultravisor sanitizes hypervisor
inputs so that the guest can not be corrupted (except for denial of
service.


What needs to be done
=====================

Thus what needs to be done to bring virtio-ccw up to speed with respect
to protected virtualization is:
* use some 'new' common virtio stuff
* make sure that virtio-ccw specific stuff uses shared memory when
  talking to the hypervisor (except control/communication blocks like ORB,
  these are handled by the ultravisor)
* make sure the DMA API does what is necessary to talk through shared
  memory if we are a protected virtualization guest.
* make sure the common IO layer plays along as well (airqs, sense).


Important notes
================

* This patch set is based on Martins features branch
 (git://git.kernel.org/pub/scm/linux/kernel/git/s390/linux.git branch
 'features').

* Documentation is still very sketchy. I'm committed to improving this,
  but I'm currently hampered by some dependencies currently.  

* The existing naming in the common infrastructure (kernel internal
  interfaces) is pretty much based on the AMD SEV terminology. Thus the
  names aren't always perfect. There might be merit to changing these
  names to more abstract ones. I did not put much thought into that at
  the current stage.

* Testing: Please use iommu_platform=on for any virtio devices you are
  going to test this code with (so virtio actually uses the DMA API).

Change log
==========

v2 --> v3:
* patch 2/8
    potential cio_dma_pool_init() returning NULL issue fixed
    potential cio_gp_dma_create() returning NULL issue fixed
    warning issues with doc type comments fixed
    unused define statement removed 
* patch 3/8
    potential cio_gp_dma_create() returning NULL issue fixed
    whitespace issue fixed
    warning issues with doc type comments fixed
* patch 8/8
    potential cio_dma_zalloc() returning NULL issue fixed

v1 --> v2:
* patch "virtio/s390: use vring_create_virtqueue" went already upstream
* patch "virtio/s390: DMA support for virtio-ccw" went already upstream
* patch "virtio/s390: enable packed ring" went already upstream
* Made dev.dma_mask point to dev.coherent_dma_mask for css, subchannel
  and ccw devices.
* While rebasing 's390/airq: use DMA memory for adapter interrupts' the
  newly introduced kmem_cache  was replaced with an equivalent dma_pool;
  the kalloc() allocations are now replaced with cio_dma_zalloc()
  allocations to avoid wasting almost a full page.
* Made virtio-ccw use the new AIRQ_IV_CACHELINE flag.
* fixed all remaining checkpatch issues

RFC --> v1:
* Fixed bugs found by Connie (may_reduce and handling reduced,  warning,
  split move -- thanks Connie!).
* Fixed console bug found by Sebastian (thanks Sebastian!).
* Removed the completely useless duplicate of dma-mapping.h spotted by
  Christoph (thanks Christoph!).
* Don't use the global DMA pool for subchannel and ccw device
  owned memory as requested by Sebastian. Consequences:
	* Both subchannel and ccw devices have their dma masks
	now (both specifying 31 bit addressable)
	* We require at least 2 DMA pages per ccw device now, most of
	this memory is wasted though.
	* DMA memory allocated by virtio is also 31 bit addressable now
        as virtio uses the parent (which is the ccw device).
* Enabled packed ring.
* Rebased onto Martins feature branch; using the actual uv (ultravisor)
  interface instead of TODO comments.
* Added some explanations to the cover letter (Connie, David).
* Squashed a couple of patches together and fixed some text stuff. 

Halil Pasic (8):
  s390/mm: force swiotlb for protected virtualization
  s390/cio: introduce DMA pools to cio
  s390/cio: add basic protected virtualization support
  s390/airq: use DMA memory for adapter interrupts
  virtio/s390: use cacheline aligned airq bit vectors
  virtio/s390: add indirection to indicators access
  virtio/s390: use DMA memory for ccw I/O and classic notifiers
  virtio/s390: make airq summary indicators DMA

 arch/s390/Kconfig                   |   5 +
 arch/s390/include/asm/airq.h        |   2 +
 arch/s390/include/asm/ccwdev.h      |   4 +
 arch/s390/include/asm/cio.h         |  11 ++
 arch/s390/include/asm/mem_encrypt.h |  18 +++
 arch/s390/mm/init.c                 |  47 +++++++
 drivers/s390/cio/airq.c             |  32 +++--
 drivers/s390/cio/ccwreq.c           |   9 +-
 drivers/s390/cio/cio.h              |   2 +
 drivers/s390/cio/css.c              | 121 +++++++++++++++++-
 drivers/s390/cio/device.c           |  67 ++++++++--
 drivers/s390/cio/device_fsm.c       |  49 ++++---
 drivers/s390/cio/device_id.c        |  20 +--
 drivers/s390/cio/device_ops.c       |  21 ++-
 drivers/s390/cio/device_pgid.c      |  22 ++--
 drivers/s390/cio/device_status.c    |  24 ++--
 drivers/s390/cio/io_sch.h           |  20 ++-
 drivers/s390/virtio/virtio_ccw.c    | 248 ++++++++++++++++++++----------------
 18 files changed, 523 insertions(+), 199 deletions(-)
 create mode 100644 arch/s390/include/asm/mem_encrypt.h
```
#### [PATCH 00/22] Some documentation fixes
##### From: Mauro Carvalho Chehab <mchehab+samsung@kernel.org>

```c

Fix several warnings and broken links.

This series was generated against linux-next, but was rebased to be applied at
docs-next. It should apply cleanly on either tree.

There's a git tree with all of them applied on the top of docs/docs-next
at:

https://git.linuxtv.org/mchehab/experimental.git/log/?h=fix_doc_links_v2


Mauro Carvalho Chehab (21):
  ABI: sysfs-devices-system-cpu: point to the right docs
  isdn: mISDN: remove a bogus reference to a non-existing doc
  dt: fix broken references to nand.txt
  docs: zh_CN: get rid of basic_profiling.txt
  doc: it_IT: fix reference to magic-number.rst
  docs: mm: numaperf.rst: get rid of a build warning
  docs: bpf: get rid of two warnings
  docs: mark orphan documents as such
  docs: amd-memory-encryption.rst get rid of warnings
  gpu: amdgpu: fix broken amdgpu_dma_buf.c references
  gpu: i915.rst: Fix references to renamed files
  docs: zh_CN: avoid duplicate citation references
  docs: vm: hmm.rst: fix some warnings
  docs: it: license-rules.rst: get rid of warnings
  docs: gpio: driver.rst: fix a bad tag
  docs: soundwire: locking: fix tags for a code-block
  docs: security: trusted-encrypted.rst: fix code-block tag
  docs: security: core.rst: Fix several warnings
  docs: net: dpio-driver.rst: fix two codeblock warnings
  docs: net: sja1105.rst: fix table format
  docs: fix broken documentation links

Otto Sabart (1):
  mfd: madera: Fix bad reference to pinctrl.txt file

 .../ABI/testing/sysfs-devices-system-cpu      |  3 +-
 Documentation/accelerators/ocxl.rst           |  2 +
 Documentation/acpi/dsd/leds.txt               |  2 +-
 .../admin-guide/kernel-parameters.rst         |  6 +-
 .../admin-guide/kernel-parameters.txt         | 16 ++---
 Documentation/admin-guide/mm/numaperf.rst     |  5 +-
 Documentation/admin-guide/ras.rst             |  2 +-
 Documentation/arm/stm32/overview.rst          |  2 +
 .../arm/stm32/stm32f429-overview.rst          |  2 +
 .../arm/stm32/stm32f746-overview.rst          |  2 +
 .../arm/stm32/stm32f769-overview.rst          |  2 +
 .../arm/stm32/stm32h743-overview.rst          |  2 +
 .../arm/stm32/stm32mp157-overview.rst         |  2 +
 Documentation/bpf/btf.rst                     |  2 +
 .../bindings/mtd/amlogic,meson-nand.txt       |  2 +-
 .../devicetree/bindings/mtd/gpmc-nand.txt     |  2 +-
 .../devicetree/bindings/mtd/marvell-nand.txt  |  2 +-
 .../devicetree/bindings/mtd/tango-nand.txt    |  2 +-
 .../devicetree/bindings/net/fsl-enetc.txt     |  7 +-
 .../bindings/pci/amlogic,meson-pcie.txt       |  2 +-
 .../regulator/qcom,rpmh-regulator.txt         |  2 +-
 .../devicetree/booting-without-of.txt         |  2 +-
 Documentation/driver-api/gpio/board.rst       |  2 +-
 Documentation/driver-api/gpio/consumer.rst    |  2 +-
 Documentation/driver-api/gpio/driver.rst      |  2 +-
 .../driver-api/soundwire/locking.rst          |  4 +-
 .../firmware-guide/acpi/enumeration.rst       |  2 +-
 .../firmware-guide/acpi/method-tracing.rst    |  2 +-
 Documentation/gpu/amdgpu.rst                  |  4 +-
 Documentation/gpu/i915.rst                    |  6 +-
 Documentation/gpu/msm-crash-dump.rst          |  2 +
 Documentation/i2c/instantiating-devices       |  2 +-
 Documentation/interconnect/interconnect.rst   |  2 +
 Documentation/laptops/lg-laptop.rst           |  2 +
 .../freescale/dpaa2/dpio-driver.rst           |  4 +-
 Documentation/networking/dsa/sja1105.rst      |  6 +-
 Documentation/powerpc/isa-versions.rst        |  2 +
 Documentation/security/keys/core.rst          | 16 +++--
 .../security/keys/trusted-encrypted.rst       |  4 +-
 Documentation/sysctl/kernel.txt               |  4 +-
 .../translations/it_IT/process/howto.rst      |  2 +-
 .../it_IT/process/license-rules.rst           | 28 ++++----
 .../it_IT/process/magic-number.rst            |  2 +-
 .../it_IT/process/stable-kernel-rules.rst     |  4 +-
 .../translations/zh_CN/basic_profiling.txt    | 71 -------------------
 .../translations/zh_CN/process/4.Coding.rst   |  2 +-
 .../zh_CN/process/management-style.rst        |  4 +-
 .../zh_CN/process/programming-language.rst    | 28 ++++----
 .../virtual/kvm/amd-memory-encryption.rst     |  5 ++
 Documentation/virtual/kvm/vcpu-requests.rst   |  2 +
 Documentation/vm/hmm.rst                      |  9 ++-
 Documentation/x86/x86_64/5level-paging.rst    |  2 +-
 Documentation/x86/x86_64/boot-options.rst     |  4 +-
 .../x86/x86_64/fake-numa-for-cpusets.rst      |  2 +-
 MAINTAINERS                                   |  6 +-
 arch/arm/Kconfig                              |  2 +-
 arch/arm64/kernel/kexec_image.c               |  2 +-
 arch/powerpc/Kconfig                          |  2 +-
 arch/x86/Kconfig                              | 16 ++---
 arch/x86/Kconfig.debug                        |  2 +-
 arch/x86/boot/header.S                        |  2 +-
 arch/x86/entry/entry_64.S                     |  2 +-
 arch/x86/include/asm/bootparam_utils.h        |  2 +-
 arch/x86/include/asm/page_64_types.h          |  2 +-
 arch/x86/include/asm/pgtable_64_types.h       |  2 +-
 arch/x86/kernel/cpu/microcode/amd.c           |  2 +-
 arch/x86/kernel/kexec-bzimage64.c             |  2 +-
 arch/x86/kernel/pci-dma.c                     |  2 +-
 arch/x86/mm/tlb.c                             |  2 +-
 arch/x86/platform/pvh/enlighten.c             |  2 +-
 drivers/acpi/Kconfig                          | 10 +--
 drivers/isdn/mISDN/dsp_core.c                 |  2 -
 drivers/net/ethernet/faraday/ftgmac100.c      |  2 +-
 .../fieldbus/Documentation/fieldbus_dev.txt   |  4 +-
 drivers/vhost/vhost.c                         |  2 +-
 include/acpi/acpi_drivers.h                   |  2 +-
 include/linux/fs_context.h                    |  2 +-
 include/linux/lsm_hooks.h                     |  2 +-
 include/linux/mfd/madera/pdata.h              |  3 +-
 mm/Kconfig                                    |  2 +-
 security/Kconfig                              |  2 +-
 tools/include/linux/err.h                     |  2 +-
 .../Documentation/stack-validation.txt        |  4 +-
 tools/testing/selftests/x86/protection_keys.c |  2 +-
 84 files changed, 183 insertions(+), 212 deletions(-)
 delete mode 100644 Documentation/translations/zh_CN/basic_profiling.txt
```
