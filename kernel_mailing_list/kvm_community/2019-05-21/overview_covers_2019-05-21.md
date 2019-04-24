

#### [PATCH v10 0/7] virtio pmem driver 
##### From: Pankaj Gupta <pagupta@redhat.com>

```c

This patch series is ready to be merged via nvdimm tree
 as discussed with Dan. We have ack/review on XFS, EXT4 &
 VIRTIO patches. Need an ack on device mapper change in
 patch 4.

 Mike, Can you please review patch 4 which has change for
 dax with device mapper.

 Incorporated all the changes suggested in v9. This version
 has minor changes in patch 2(virtio) and does not change the 
 existing functionality, Kept all the existing reviews/ack.
 Jakob CCed also tested the v9 of patch series and confirmed 
 the working.

 ---

 This patch series has implementation for "virtio pmem". 
 "virtio pmem" is fake persistent memory(nvdimm) in guest 
 which allows to bypass the guest page cache. This also
 implements a VIRTIO based asynchronous flush mechanism.  
 
 Sharing guest kernel driver in this patchset with the 
 changes suggested in v4. Tested with Qemu side device 
 emulation [6] for virtio-pmem. Documented the impact of
 possible page cache side channel attacks with suggested
 countermeasures.

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

Changes from PATCH v9: [1] 
 - Kconfig help text add two spaces - Randy
 - Fixed libnvdimm 'bio' include warning - Dan
 - virtio-pmem, separate request/resp struct and 
   move to uapi file with updated license - DavidH
 - Use virtio32* type for req/resp endianess - DavidH
 - Added tested-by & ack-by of Jakob
 - Rebased to 5.2-rc1

Changes from PATCH v8: [2] 
 - Set device mapper synchronous if all target devices support - Dan
 - Move virtio_pmem.h to nvdimm directory  - Dan
 - Style, indentation & better error messages in patch 2 - DavidH
 - Added MST's ack in patch 2.

Changes from PATCH v7:
 - Corrected pending request queue logic (patch 2) - Jakub Staroń
 - Used unsigned long flags for passing DAXDEV_F_SYNC (patch 3) - Dan
 - Fixed typo =>  vma 'flag' to 'vm_flag' (patch 4)
 - Added rob in patch 6 & patch 2

Changes from PATCH v6: 
 - Corrected comment format in patch 5 & patch 6. [Dave]
 - Changed variable declaration indentation in patch 6 [Darrick]
 - Add Reviewed-by tag by 'Jan Kara' in patch 4 & patch 5

Changes from PATCH v5: 
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

Pankaj Gupta (7):
   libnvdimm: nd_region flush callback support
   virtio-pmem: Add virtio-pmem guest driver
   libnvdimm: add nd_region buffered dax_dev flag
   dax: check synchronous mapping is supported
   dm: dm: Enable synchronous dax
   ext4: disable map_sync for virtio pmem
   xfs: disable map_sync for virtio pmem

[1] https://lkml.org/lkml/2019/5/14/465
[2] https://lkml.org/lkml/2019/5/10/447
[3] https://www.spinics.net/lists/kvm/msg149761.html
[4] https://www.spinics.net/lists/kvm/msg153095.html  
[5] https://lkml.org/lkml/2018/8/31/413
[6] https://marc.info/?l=linux-kernel&m=153572228719237&w=2 
[7] https://marc.info/?l=qemu-devel&m=153555721901824&w=2
[8] https://lists.oasis-open.org/archives/virtio-dev/201903/msg00083.html
[9] https://lkml.org/lkml/2019/1/9/1191

 20 files changed, 468 insertions(+), 25 deletions(-)
 drivers/acpi/nfit/core.c         |    4 -
 drivers/dax/bus.c                |    2 
 drivers/dax/super.c              |   19 +++++
 drivers/md/dm-table.c            |   14 ++++
 drivers/md/dm.c                  |    3 
 drivers/nvdimm/Makefile          |    1 
 drivers/nvdimm/claim.c           |    6 +
 drivers/nvdimm/nd.h              |    1 
 drivers/nvdimm/nd_virtio.c       |  124 +++++++++++++++++++++++++++++++++++++++
 drivers/nvdimm/pmem.c            |   18 +++--
 drivers/nvdimm/region_devs.c     |   33 +++++++++-
 drivers/nvdimm/virtio_pmem.c     |  122 ++++++++++++++++++++++++++++++++++++++
 drivers/nvdimm/virtio_pmem.h     |   55 +++++++++++++++++
 drivers/virtio/Kconfig           |   11 +++
 fs/ext4/file.c                   |   10 +--
 fs/xfs/xfs_file.c                |    9 +-
 include/linux/dax.h              |   26 +++++++-
 include/linux/libnvdimm.h        |   10 ++-
 include/uapi/linux/virtio_ids.h  |    1 
 include/uapi/linux/virtio_pmem.h |   35 +++++++++++
 20 files changed, 479 insertions(+), 25 deletions(-)
```
#### [PATCH v9 0/4] vfio: ap: AP Queue Interrupt Control
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
  - saved NIB : to keep track of the pin page for unpining it
  - saved ISC : to unregister with the GIB interface
  - matrix_mdev: to retrieve the associate matrix, the mediated device
    and KVM

Specific handling bei keeping old values when re-registering is
needed because the guest could unregister interrupt in a invisble
manner bei issuing an un-interceptible RESET command.

Reset commands issued directly by the guest and indirectly when
removing the guest unpin the memory and deregister the ISC.

The vfio_ap_queue is associated to the ap_device during the probe
of the device and dissociated during the remove of the ap_device.

The vfio_ap_queue is associated to the matrix mediated device during
each interception of the AQIC command, so it does not need to be
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

4) Enabling and disabling the IRQ

When enabling the IRQ care is taken to unping the saved NIB.
When disabling IRQ care is taken to wait until the IRQ bit
of the queue status is cleared before unpining the NIB.

On RESET and before unpinning the NIB and unregistering the ISC
the IRQ is disabled using PQAP/AQIC even when a PQAP/APZQ have
been done.

5) Removing the AP device

Removing the AP device without having unassign it is clearly
discourage by the documentation.
The patch series does not check if the queue is used by a
guest. It only de-register the IRQ, unregister ISC and unpin
the NIB, then free the vfio_ap_queue.

6) Associated QEMU patch

There is a QEMU patch which is needed to enable the PQAP/AQIC
facility in the guest.

Posted in qemu-devel@nongnu.org as:
Message-Id: <1550146494-21085-1-git-send-email-pmorel@linux.ibm.com>

7) Compatibility with Dynamic configuration patches

Tony, I did not rebase this series above the dynamic configuration
patches because:
- This series do the work it needs to do without having to take
  care on the dynamic configuration.
- It is guarantied that interrupt will be shut off after removing
  the APQueue device
- The dynamic configuration series is not converging.

However Tony, the choice is your's, I won't be able to help
in a near future.


Pierre Morel (4):
  s390: ap: kvm: add PQAP interception for AQIC
  vfio: ap: register IOMMU VFIO notifier
  s390: ap: implement PAPQ AQIC interception in kernel
  s390: ap: kvm: Enable PQAP/AQIC facility for the guest

 arch/s390/include/asm/kvm_host.h      |   7 +
 arch/s390/kvm/priv.c                  |  86 ++++++++
 arch/s390/tools/gen_facilities.c      |   1 +
 drivers/s390/crypto/vfio_ap_drv.c     |  34 ++-
 drivers/s390/crypto/vfio_ap_ops.c     | 379 +++++++++++++++++++++++++++++++++-
 drivers/s390/crypto/vfio_ap_private.h |  15 ++
 6 files changed, 514 insertions(+), 8 deletions(-)
```
