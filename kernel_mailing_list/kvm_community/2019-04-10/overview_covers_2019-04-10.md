

#### [PATCH v5 0/6] virtio pmem driver 
##### From: Pankaj Gupta <pagupta@redhat.com>

```c

This patch series has implementation for "virtio pmem". 
 "virtio pmem" is fake persistent memory(nvdimm) in guest 
 which allows to bypass the guest page cache. This also
 implements a VIRTIO based asynchronous flush mechanism.  
 
 Sharing guest kernel driver in this patchset with the 
 changes suggested in v4. Tested with Qemu side device 
 emulation [6] for virtio-pmem. 

 We have incorporated all the suggestions in V4. Documented 
 the impact of possible page cache side channel attacks with 
 suggested countermeasures.
 
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

Changes from PATCH v4: [1]
- Factor out MAP_SYNC supported functionality to a common helper
				[Dave, Darrick, Jan]
- Comment, indentation and virtqueue_kick failure handle - Yuval Shaia

Changes from PATCH v3: [2]
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
- request leak, correct sizeof req- Stefan
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

[1] https://lkml.org/lkml/2019/4/3/394
[2] https://lkml.org/lkml/2019/1/9/471
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
 drivers/md/dm.c                  |    2 
 drivers/nvdimm/claim.c           |    6 +
 drivers/nvdimm/nd.h              |    1 
 drivers/nvdimm/pmem.c            |   17 +++--
 drivers/nvdimm/region_devs.c     |   45 +++++++++++++-
 drivers/nvdimm/virtio_pmem.c     |   88 +++++++++++++++++++++++++++
 drivers/virtio/Kconfig           |   10 +++
 drivers/virtio/Makefile          |    1 
 drivers/virtio/pmem.c            |  124 +++++++++++++++++++++++++++++++++++++++
 fs/ext4/file.c                   |   11 +--
 fs/xfs/xfs_file.c                |   10 +--
 include/linux/dax.h              |   32 +++++++++-
 include/linux/libnvdimm.h        |    9 ++
 include/linux/virtio_pmem.h      |   60 ++++++++++++++++++
 include/uapi/linux/virtio_ids.h  |    1 
 include/uapi/linux/virtio_pmem.h |   10 +++
 19 files changed, 419 insertions(+), 27 deletions(-)
```
#### [PATCH v5 00/16] KVM: PPC: Book3S HV: add XIVE native exploitation
##### From: =?utf-8?q?C=C3=A9dric_Le_Goater?= <clg@kaod.org>

```c

Hello,

On the POWER9 processor, the XIVE interrupt controller can control
interrupt sources using MMIOs to trigger events, to EOI or to turn off
the sources. Priority management and interrupt acknowledgment is also
controlled by MMIO in the CPU presenter sub-engine.

PowerNV/baremetal Linux runs natively under XIVE but sPAPR guests need
special support from the hypervisor to do the same. This is called the
XIVE native exploitation mode and today, it can be activated under the
PowerPC Hypervisor, pHyp. However, Linux/KVM lacks XIVE native support
and still offers the old interrupt mode interface using a KVM device
implementing the XICS hcalls over XIVE.

The following series is proposal to add the same support under KVM.

A new KVM device is introduced for the XIVE native exploitation
mode. It reuses most of the XICS-over-XIVE glue implementation
structures which are internal to KVM but has a completely different
interface. A set of KVM device ioctls provide support for the
hypervisor calls, all handled in QEMU, to configure the sources and
the event queues. From there, all interrupt control is transferred to
the guest which can use MMIOs.

These MMIO regions (ESB and TIMA) are exposed to guests in QEMU,
similarly to VFIO, and the associated VMAs are populated dynamically
with the appropriate pages using a fault handler. These are now
implemented using mmap()s of the KVM device fd.

Migration has its own specific needs regarding memory. The patchset
provides a specific control to quiesce XIVE before capturing the
memory. The save and restore of the internal state is based on the
same ioctls used for the hcalls.

On a POWER9 sPAPR machine, the Client Architecture Support (CAS)
negotiation process determines whether the guest operates with a
interrupt controller using the XICS legacy model, as found on POWER8,
or in XIVE exploitation mode. Which means that the KVM interrupt
device should be created at run-time, after the machine has started.
This requires extra support from KVM to destroy KVM devices. It is
introduced at the end of the patchset and requires some attention.

This is based on Linux 5.1-rc4 and is a candidate for 5.2. The OPAL
patches have been merged now.


GitHub trees available here :
 
QEMU sPAPR:

  https://github.com/legoater/qemu/commits/xive-next
  
Linux/KVM:

  https://github.com/legoater/linux/commits/xive-5.1

Thanks,

C.

Caveats :

 - We should introduce a set of definitions common to XIVE and XICS
 - The XICS-over-XIVE device file book3s_xive.c could be renamed to
   book3s_xics_on_xive.c or book3s_xics_p9.c
 - The XICS-over-XIVE device still has locking issues in the setup.
 - xc->valid is not useful
 - xc->xive is not very useful either

Changes since v4:

 - add check on EQ page alignment
 - add requirement on KVM_XIVE_EQ_ALWAYS_NOTIFY
 - add documentation in Documentation/virtual/kvm/api.txt
 - remove 'destroy' method
 - introduce a 'release' device operation called when device fd is
   closed.
 - introduce a 'xive_devices' array under the VM to store kvmppc_xive
   objects until VM is destroyed.
 
Changes since v3:

 - removed a couple of useless includes
 - fix the test ont the initial setting of the EQ toggle bit : 0 -> 1
 - renamed qsize to qshift
 - renamed qpage to qaddr
 - checked host page size
 - limited flags to KVM_XIVE_EQ_ALWAYS_NOTIFY to fit sPAPR specs
 - Fixed xive_timaval description in documentation

Changes since v2:

 - removed extra OPAL call definitions
 - removed ->q_order setting. Only useful in the XICS-on-XIVE KVM
   device which allocates the EQs on behalf of the guest.
 - returned -ENXIO when VP base is invalid
 - made use of the xive_vp() macro to compute VP identifiers
 - reworked locking in kvmppc_xive_native_connect_vcpu() to fix races 
 - stop advertising KVM_CAP_PPC_IRQ_XIVE as support is not fully
   available yet
 - fixed comment on XIVE IRQ number space
 - removed usage of the __x_* macros
 - fixed locking on source block
 - fixed comments on the KVM device attribute definitions
 - handled MASKED EAS configuration
 - fixed check on supported EQ size to restrict to 64K pages
 - checked kvm_eq.flags that need to be zero
 - removed the OPAL call when EQ qtoggle bit and index are zero. 
 - reduced the size of kvmppc_one_reg timaval attribute to two u64s
 - stopped returning of the OS CAM line value
 
Changes since v1:

 - Better documentation (was missing)
 - Nested support. XIVE not advertised on non PowerNV platforms. This
   is a good way to test the fallback on QEMU emulated devices.
 - ESB and TIMA special mapping done using the KVM device fd
 - All hcalls moved to QEMU. Dropped the patch moving the hcall flags.
 - Reworked of the KVM device ioctl controls to support hcalls and
   migration needs to capture/save states
 - Merged the control syncing XIVE and marking the EQ page dirty
 - Fixed passthrough support using the KVM device file address_space
   to clear the ESB pages from the mapping
 - Misc enhancements and fixes 

Cédric Le Goater (16):
  powerpc/xive: add OPAL extensions for the XIVE native exploitation
    support
  KVM: PPC: Book3S HV: add a new KVM device for the XIVE native
    exploitation mode
  KVM: PPC: Book3S HV: XIVE: introduce a new capability
    KVM_CAP_PPC_IRQ_XIVE
  KVM: PPC: Book3S HV: XIVE: add a control to initialize a source
  KVM: PPC: Book3S HV: XIVE: add a control to configure a source
  KVM: PPC: Book3S HV: XIVE: add controls for the EQ configuration
  KVM: PPC: Book3S HV: XIVE: add a global reset control
  KVM: PPC: Book3S HV: XIVE: add a control to sync the sources
  KVM: PPC: Book3S HV: XIVE: add a control to dirty the XIVE EQ pages
  KVM: PPC: Book3S HV: XIVE: add get/set accessors for the VP XIVE state
  KVM: introduce a 'mmap' method for KVM devices
  KVM: PPC: Book3S HV: XIVE: add a TIMA mapping
  KVM: PPC: Book3S HV: XIVE: add a mapping for the source ESB pages
  KVM: PPC: Book3S HV: XIVE: add passthrough support
  KVM: PPC: Book3S HV: XIVE: activate XIVE exploitation mode
  KVM: PPC: Book3S HV: XIVE: introduce a 'release' device operation

 arch/powerpc/include/asm/kvm_host.h        |    3 +
 arch/powerpc/include/asm/kvm_ppc.h         |   32 +
 arch/powerpc/include/asm/opal-api.h        |    7 +-
 arch/powerpc/include/asm/opal.h            |    7 +
 arch/powerpc/include/asm/xive.h            |   17 +
 arch/powerpc/include/uapi/asm/kvm.h        |   46 +
 arch/powerpc/kvm/book3s_xive.h             |   37 +
 include/linux/kvm_host.h                   |    2 +
 include/uapi/linux/kvm.h                   |    3 +
 arch/powerpc/kvm/book3s.c                  |   31 +-
 arch/powerpc/kvm/book3s_xive.c             |  230 +++-
 arch/powerpc/kvm/book3s_xive_native.c      | 1243 ++++++++++++++++++++
 arch/powerpc/kvm/powerpc.c                 |   37 +
 arch/powerpc/platforms/powernv/opal-call.c |    3 +
 arch/powerpc/sysdev/xive/native.c          |  110 ++
 virt/kvm/kvm_main.c                        |   24 +
 Documentation/virtual/kvm/api.txt          |   10 +
 Documentation/virtual/kvm/devices/xive.txt |  197 ++++
 arch/powerpc/kvm/Makefile                  |    2 +-
 19 files changed, 1980 insertions(+), 61 deletions(-)
 create mode 100644 arch/powerpc/kvm/book3s_xive_native.c
 create mode 100644 Documentation/virtual/kvm/devices/xive.txt
```
