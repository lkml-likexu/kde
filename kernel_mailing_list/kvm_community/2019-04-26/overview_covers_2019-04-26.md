

#### [PATCH v7 0/6] virtio pmem driver 
##### From: Pankaj Gupta <pagupta@redhat.com>

```c

This patch series has implementation for "virtio pmem". 
 "virtio pmem" is fake persistent memory(nvdimm) in guest 
 which allows to bypass the guest page cache. This also
 implements a VIRTIO based asynchronous flush mechanism.  
 
 Sharing guest kernel driver in this patchset with the 
 changes suggested in v4. Tested with Qemu side device 
 emulation [6] for virtio-pmem. Documented the impact of
 possible page cache side channel attacks with suggested
 countermeasures.

 Incorporated all the review suggestions. 
 
 Details of project idea for 'virtio pmem' flushing interface 
 is shared [3] & [4].

 Implementation is divided into two parts:
 New virtio pmem guest driver and qemu code changes for new 
 virtio pmem paravirtualized device.

1. Guest virtio-pmem kernel driver
---------------------------------
   - Reads persistent memory range from paravirt device and 
     registers with 'nvdimm_bus'.  
   - 'nvdimm/pmem' driver uses this information to allocate 
     persistent memory region and setup filesystem operations 
     to the allocated memory. 
   - virtio pmem driver implements asynchronous flushing 
     interface to flush from guest to host.

2. Qemu virtio-pmem device
---------------------------------
   - Creates virtio pmem device and exposes a memory range to 
     KVM guest. 
   - At host side this is file backed memory which acts as 
     persistent memory. 
   - Qemu side flush uses aio thread pool API's and virtio 
     for asynchronous guest multi request handling. 

   David Hildenbrand CCed also posted a modified version[7] of 
   qemu virtio-pmem code based on updated Qemu memory device API. 

 Virtio-pmem security implications and countermeasures:
 -----------------------------------------------------

 In previous posting of kernel driver, there was discussion [9]
 on possible implications of page cache side channel attacks with 
 virtio pmem. After thorough analysis of details of known side 
 channel attacks, below are the suggestions:

 - Depends entirely on how host backing image file is mapped 
   into guest address space. 

 - virtio-pmem device emulation, by default shared mapping is used
   to map host backing file. It is recommended to use separate
   backing file at host side for every guest. This will prevent
   any possibility of executing common code from multiple guests
   and any chance of inferring guest local data based based on 
   execution time.

 - If backing file is required to be shared among multiple guests 
   it is recommended to don't support host page cache eviction 
   commands from the guest driver. This will avoid any possibility
   of inferring guest local data or host data from another guest. 

 - Proposed device specification [8] for virtio-pmem device with 
   details of possible security implications and suggested 
   countermeasures for device emulation.

 Virtio-pmem errors handling:
 ----------------------------------------
  Checked behaviour of virtio-pmem for below types of errors
  Need suggestions on expected behaviour for handling these errors?

  - Hardware Errors: Uncorrectable recoverable Errors: 
  a] virtio-pmem: 
    - As per current logic if error page belongs to Qemu process, 
      host MCE handler isolates(hwpoison) that page and send SIGBUS. 
      Qemu SIGBUS handler injects exception to KVM guest. 
    - KVM guest then isolates the page and send SIGBUS to guest 
      userspace process which has mapped the page. 
  
  b] Existing implementation for ACPI pmem driver: 
    - Handles such errors with MCE notifier and creates a list 
      of bad blocks. Read/direct access DAX operation return EIO 
      if accessed memory page fall in bad block list.
    - It also starts backgound scrubbing.  
    - Similar functionality can be reused in virtio-pmem with MCE 
      notifier but without scrubbing(no ACPI/ARS)? Need inputs to 
      confirm if this behaviour is ok or needs any change?

Changes from PATCH v6: [1]
 - Corrected comment format in patch 5 & patch 6. [Dave]
 - Changed variable declaration indentation in patch 6 [Darrick]
 - Add Reviewed-by tag by 'Jan Kara' in patch 4 & patch 5

Changes from PATCH v5: [2]
  Changes suggested in by - [Cornelia, Yuval]
- Remove assignment chaining in virtio driver
- Better error message and remove not required free
- Check nd_region before use

  Changes suggested by - [Jan Kara]
- dax_synchronous() for !CONFIG_DAX
- Correct 'daxdev_mapping_supported' comment and non-dax implementation

  Changes suggested by - [Dan Williams]
- Pass meaningful flag 'DAXDEV_F_SYNC' to alloc_dax
- Gate nvdimm_flush instead of additional async parameter
- Move block chaining logic to flush callback than common nvdimm_flush
- Use NULL flush callback for generic flush for better readability [Dan, Jan]

- Use virtio device id 27 from 25(already used) - [MST]

Changes from PATCH v4:
- Factor out MAP_SYNC supported functionality to a common helper
				[Dave, Darrick, Jan]
- Comment, indentation and virtqueue_kick failure handle - Yuval Shaia

Changes from PATCH v3: 
- Use generic dax_synchronous() helper to check for DAXDEV_SYNC 
  flag - [Dan, Darrick, Jan]
- Add 'is_nvdimm_async' function
- Document page cache side channel attacks implications & 
  countermeasures - [Dave Chinner, Michael]

Changes from PATCH v2: 
- Disable MAP_SYNC for ext4 & XFS filesystems - [Dan] 
- Use name 'virtio pmem' in place of 'fake dax' 

Changes from PATCH v1: 
- 0-day build test for build dependency on libnvdimm 

 Changes suggested by - [Dan Williams]
- Split the driver into two parts virtio & pmem  
- Move queuing of async block request to block layer
- Add "sync" parameter in nvdimm_flush function
- Use indirect call for nvdimm_flush
- Don’t move declarations to common global header e.g nd.h
- nvdimm_flush() return 0 or -EIO if it fails
- Teach nsio_rw_bytes() that the flush can fail
- Rename nvdimm_flush() to generic_nvdimm_flush()
- Use 'nd_region->provider_data' for long dereferencing
- Remove virtio_pmem_freeze/restore functions
- Remove BSD license text with SPDX license text

- Add might_sleep() in virtio_pmem_flush - [Luiz]
- Make spin_lock_irqsave() narrow

Changes from RFC v3
- Rebase to latest upstream - Luiz
- Call ndregion->flush in place of nvdimm_flush- Luiz
- kmalloc return check - Luiz
- virtqueue full handling - Stefan
- Don't map entire virtio_pmem_req to device - Stefan
- request leak, correct sizeof req - Stefan
- Move declaration to virtio_pmem.c

Changes from RFC v2:
- Add flush function in the nd_region in place of switching
  on a flag - Dan & Stefan
- Add flush completion function with proper locking and wait
  for host side flush completion - Stefan & Dan
- Keep userspace API in uapi header file - Stefan, MST
- Use LE fields & New device id - MST
- Indentation & spacing suggestions - MST & Eric
- Remove extra header files & add licensing - Stefan

Changes from RFC v1:
- Reuse existing 'pmem' code for registering persistent 
  memory and other operations instead of creating an entirely 
  new block driver.
- Use VIRTIO driver to register memory information with 
  nvdimm_bus and create region_type accordingly. 
- Call VIRTIO flush from existing pmem driver.

Pankaj Gupta (6):
   libnvdimm: nd_region flush callback support
   virtio-pmem: Add virtio-pmem guest driver
   libnvdimm: add nd_region buffered dax_dev flag
   dax: check synchronous mapping is supported
   ext4: disable map_sync for virtio pmem
   xfs: disable map_sync for virtio pmem

[1] https://lkml.org/lkml/2019/4/23/1092
[2] https://lkml.org/lkml/2019/4/10/3
[3] https://www.spinics.net/lists/kvm/msg149761.html
[4] https://www.spinics.net/lists/kvm/msg153095.html  
[5] https://lkml.org/lkml/2018/8/31/413
[6] https://marc.info/?l=linux-kernel&m=153572228719237&w=2 
[7] https://marc.info/?l=qemu-devel&m=153555721901824&w=2
[8] https://lists.oasis-open.org/archives/virtio-dev/201903/msg00083.html
[9] https://lkml.org/lkml/2019/1/9/1191

 drivers/acpi/nfit/core.c         |    4 -
 drivers/dax/bus.c                |    2 
 drivers/dax/super.c              |   13 +++-
 drivers/md/dm.c                  |    3 
 drivers/nvdimm/claim.c           |    6 +
 drivers/nvdimm/nd.h              |    1 
 drivers/nvdimm/pmem.c            |   16 +++--
 drivers/nvdimm/region_devs.c     |   33 ++++++++++
 drivers/nvdimm/virtio_pmem.c     |  114 +++++++++++++++++++++++++++++++++++++
 drivers/virtio/Kconfig           |   10 +++
 drivers/virtio/Makefile          |    1 
 drivers/virtio/pmem.c            |  118 +++++++++++++++++++++++++++++++++++++++
 fs/ext4/file.c                   |   10 +--
 fs/xfs/xfs_file.c                |    9 +-
 include/linux/dax.h              |   25 +++++++-
 include/linux/libnvdimm.h        |    9 ++
 include/linux/virtio_pmem.h      |   60 +++++++++++++++++++
 include/uapi/linux/virtio_ids.h  |    1 
 include/uapi/linux/virtio_pmem.h |   10 +++
 19 files changed, 420 insertions(+), 25 deletions(-)
```
#### [PATCH v7 0/4] vfio: ap: AP Queue Interrupt Control
##### From: Pierre Morel <pmorel@linux.ibm.com>

```c

This patch series implements PQAP/AQIC interception in KVM.

1) Data to handle GISA interrupt for AQIC

To implement this we need to add a new structure, vfio_ap_queue,
to be able to retrieve the mediated device associated with a queue
and specific values needed to register/unregister the interrupt
structures:
  - APQN: to be able to issue the commands and search for queue
    structures
  - NIB and old NIB : to unpin the NIB on clear IRQ
  - ISC and old ISC : to unregister with the GIB interface
  - matrix_mdev: to retrieve the associate matrix and mediated device

Specific handling bei keeping old values when re-registering is
needed because the guest could unregister interrupt in a invisble
manner bei issuing an un-interceptible RESET command.

Reset commands issued directly by the guest and indirectly when
removing the guest unpin the memory and deregister the ISC.

The vfio_ap_queue is associated to the ap_device during the probe
of the device and dissociated during the remove of the ap_device.

The vfio_ap_queue is associated to the matrix mediated device during
each interception of the AQIC command, so it do not need to be
dissociated until the guest is terminated.

The life of the vfio_ap_queue will be protected by the matrix_dev lock
to guaranty that no change can occur to the CRYCB or that devices can
not be removed when a vfio_ap_queue is in use.

2) KVM destroy race conditions

To make sure that KVM do not vanish and GISA is still available
when the VFIO_AP driver is in used we take a reference to KVM
during the opening of the mediated device and release it on
releasing the mediated device.

3) Interception of PQAP

The driver registers a hook structure to KVM providing:
- a pointer to a function implementing PQAP(AQIC) handling
- the reference to the module owner of the hook

On interception by KVM we do not change the behavior, returning
 -EOPNOTSUPP to the user in the case AP instructions are not
supported by the host or by the guest.
Otherwise we verify the exceptions cases before trying to call 
the vfio_ap hook.

In the case we do not find a hook we assume that the CRYCB has not
been setup for the guest and is empty.


4) Removing the AP device

Removing the AP device without having unassign it is clearly
discourage by the documentation.
The patch series does not check if the queue is used by a
guest and simply free the vfio_ap_queue.

5) Associated QEMU patch

There is a QEMU patch which is needed to enable the PQAP/AQIC
facility in the guest.

Posted in qemu-devel@nongnu.org as:
Message-Id: <1550146494-21085-1-git-send-email-pmorel@linux.ibm.com>


Pierre Morel (4):
  s390: ap: kvm: add PQAP interception for AQIC
  vfio: ap: register IOMMU VFIO notifier
  s390: ap: implement PAPQ AQIC interception in kernel
  s390: ap: kvm: Enable PQAP/AQIC facility for the guest

 arch/s390/include/asm/kvm_host.h      |   7 +
 arch/s390/kvm/priv.c                  |  86 +++++++++
 arch/s390/tools/gen_facilities.c      |   1 +
 drivers/s390/crypto/ap_bus.h          |   1 +
 drivers/s390/crypto/vfio_ap_drv.c     |  30 ++-
 drivers/s390/crypto/vfio_ap_ops.c     | 336 +++++++++++++++++++++++++++++++++-
 drivers/s390/crypto/vfio_ap_private.h |  15 ++
 7 files changed, 468 insertions(+), 8 deletions(-)
```
#### [PATCH 00/10] s390: virtio: support protected virtualization
##### From: Halil Pasic <pasic@linux.ibm.com>

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
to change into PV mode by doing the appropriate ultravisor calls. Unlike
some other enhanced virtualization protection technology, 

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

Looking forward to your review, or any other type of input.

Halil Pasic (10):
  virtio/s390: use vring_create_virtqueue
  virtio/s390: DMA support for virtio-ccw
  virtio/s390: enable packed ring
  s390/mm: force swiotlb for protected virtualization
  s390/cio: introduce DMA pools to cio
  s390/cio: add basic protected virtualization support
  s390/airq: use DMA memory for adapter interrupts
  virtio/s390: add indirection to indicators access
  virtio/s390: use DMA memory for ccw I/O and classic notifiers
  virtio/s390: make airq summary indicators DMA

 arch/s390/Kconfig                   |   5 +
 arch/s390/include/asm/airq.h        |   2 +
 arch/s390/include/asm/ccwdev.h      |   4 +
 arch/s390/include/asm/cio.h         |  11 ++
 arch/s390/include/asm/mem_encrypt.h |  18 +++
 arch/s390/mm/init.c                 |  50 +++++++
 drivers/s390/cio/airq.c             |  18 ++-
 drivers/s390/cio/ccwreq.c           |   8 +-
 drivers/s390/cio/cio.h              |   1 +
 drivers/s390/cio/css.c              | 101 +++++++++++++
 drivers/s390/cio/device.c           |  65 +++++++--
 drivers/s390/cio/device_fsm.c       |  40 +++---
 drivers/s390/cio/device_id.c        |  18 +--
 drivers/s390/cio/device_ops.c       |  21 ++-
 drivers/s390/cio/device_pgid.c      |  20 +--
 drivers/s390/cio/device_status.c    |  24 ++--
 drivers/s390/cio/io_sch.h           |  21 ++-
 drivers/s390/virtio/virtio_ccw.c    | 275 +++++++++++++++++++-----------------
 include/linux/virtio.h              |  17 ---
 19 files changed, 499 insertions(+), 220 deletions(-)
 create mode 100644 arch/s390/include/asm/mem_encrypt.h
```
