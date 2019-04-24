

#### [PATCH v17 00/10] Add ARMv8 RAS virtualization support in QEMU
##### From: Dongjiu Geng <gengdongjiu@huawei.com>

```c

In the ARMv8 platform, the CPU error type are synchronous external
abort(SEA) and SError Interrupt (SEI). If exception happens to guest,
sometimes guest itself do the recovery is better, because host 
does not know guest's detailed information. For example, if a guest
user-space application happen exception, host does not which application
encounter errors.

For the ARMv8 SEA/SEI, KVM or host kernel delivers SIGBUS to notify user
space. After user space gets  the notification, it will record the CPER
to guest GHES buffer for guest and inject a exception or IRQ to guest.

In the current implement, if the SIGBUS is BUS_MCEERR_AR, we will
treat it as synchronous exception, and use ARMv8 SEA notification type
to notify guest after recording CPER for guest;

This series patches are based on Qemu 4.0, which have two parts:
1. Generate APEI/GHES table.
2. Handle the SIGBUS signal, record the CPER in runtime and fill into guest memory,
   then according to SIGBUS type to notify guest.

Whole solution was suggested by James(james.morse@arm.com); APEI part solution is suggested by
Laszlo(lersek@redhat.com). Shown some discussion in [1].


This series patches have already tested on ARM64 platform with RAS feature enabled:
Show the APEI part verification result in [2]
Show the BUS_MCEERR_AR SIGBUS handling verification result in [3]
---
change since v16:
1. check whether ACPI table is enabled when handling the memory error in the SIGBUS handler.

Change since v15:
1. Add a doc-comment in the proper format for 'include/exec/ram_addr.h'
2. Remove write_part_cpustate_to_list() because there is another bug fix patch
   has been merged "arm: Allow system registers for KVM guests to be changed by QEMU code"
3. Add some comments for kvm_inject_arm_sea() in 'target/arm/kvm64.c'
4. Compare the arm_current_el() return value to 0,1,2,3, not to PSTATE_MODE_* constants.
5. Change the RAS support wasn't introduced before 4.1 QEMU version.
6. Move the no_ras flag  patch to begin in this series

Change since v14:
1. Remove the BUS_MCEERR_AO handling logic because this asynchronous signal was masked by main thread 
2. Address some Igor Mammedov's comments(ACPI part)
   1) change the comments for the enum AcpiHestNotifyType definition and remove ditto in patch 1
   2) change some patch commit messages and separate "APEI GHES table generation" patch to more patches.
3. Address some peter's comments(arm64 Synchronous External Abort injection)
   1) change some code notes
   2) using arm_current_el() for current EL
   2) use the helper functions for those (syn_data_abort_*).

Change since v13:
1. Move the patches that set guest ESR and inject virtual SError out of this series
2. Clean and optimize the APEI part patches 
3. Update the commit messages and add some comments for the code

Change since v12:
1. Address Paolo's comments to move HWPoisonPage definition to accel/kvm/kvm-all.c
2. Only call kvm_cpu_synchronize_state() when get the BUS_MCEERR_AR signal
3. Only add and enable GPIO-Signal and ARMv8 SEA two hardware error sources
4. Address Michael's comments to not sync SPDX from Linux kernel header file 

Change since v11:
Address James's comments(james.morse@arm.com)
1. Check whether KVM has the capability to to set ESR instead of detecting host CPU RAS capability
2. For SIGBUS_MCEERR_AR SIGBUS, use Synchronous-External-Abort(SEA) notification type
   for SIGBUS_MCEERR_AO SIGBUS, use GPIO-Signal notification


Address Shannon's comments(for ACPI part):
1. Unify hest_ghes.c and hest_ghes.h license declaration
2. Remove unnecessary including "qmp-commands.h" in hest_ghes.c
3. Unconditionally add guest APEI table based on James's comments(james.morse@arm.com) 
4. Add a option to virt machine for migration compatibility. On new virt machine it's on
   by default while off for old ones, we enabled it since 2.12
5. Refer to the ACPI spec version which introduces Hardware Error Notification first time
6. Add ACPI_HEST_NOTIFY_RESERVED notification type

Address Igor's comments(for ACPI part):
1. Add doc patch first which will describe how it's supposed to work between QEMU/firmware/guest
   OS with expected flows.
2. Move APEI diagrams into doc/spec patch
3. Remove redundant g_malloc in ghes_record_cper()
4. Use build_append_int_noprefix() API to compose whole error status block and whole APEI table, 
   and try to get rid of most structures in patch 1, as they will be left unused after that
5. Reuse something like https://github.com/imammedo/qemu/commit/3d2fd6d13a3ea298d2ee814835495ce6241d085c
   to build GAS
6. Remove much offsetof() in the function
7. Build independent tables first and only then build dependent tables passing to it pointers
   to previously build table if necessary.
8. Redefine macro GHES_ACPI_HEST_NOTIFY_RESERVED to ACPI_HEST_ERROR_SOURCE_COUNT to avoid confusion


Address Peter Maydell's comments
1. linux-headers is done as a patch of their own created using scripts/update-linux-headers.sh run against a
   mainline kernel tree 
2. Tested whether this patchset builds OK on aarch32  
3. Abstract Hwpoison page adding code  out properly into a cpu-independent source file from target/i386/kvm.c,
   such as kvm-all.c
4. Add doc-comment formatted documentation comment for new globally-visible function prototype in a header

---
[1]:
https://lkml.org/lkml/2017/2/27/246
https://patchwork.kernel.org/patch/9633105/
https://patchwork.kernel.org/patch/9925227/

[2]:
Note: the UEFI(QEMU_EFI.fd) is needed if guest want to use ACPI table.

After guest boot up, dump the APEI table, then can see the initialized table
(1) # iasl -p ./HEST -d /sys/firmware/acpi/tables/HEST
(2) # cat HEST.dsl
    /*
     * Intel ACPI Component Architecture
     * AML/ASL+ Disassembler version 20170728 (64-bit version)
     * Copyright (c) 2000 - 2017 Intel Corporation
     *
     * Disassembly of /sys/firmware/acpi/tables/HEST, Mon Sep  5 07:59:17 2016
     *
     * ACPI Data Table [HEST]
     *
     * Format: [HexOffset DecimalOffset ByteLength]  FieldName : FieldValue
     */

    ..................................................................................
    [308h 0776   2]                Subtable Type : 000A [Generic Hardware Error Source V2]
    [30Ah 0778   2]                    Source Id : 0001
    [30Ch 0780   2]            Related Source Id : FFFF
    [30Eh 0782   1]                     Reserved : 00
    [30Fh 0783   1]                      Enabled : 01
    [310h 0784   4]       Records To Preallocate : 00000001
    [314h 0788   4]      Max Sections Per Record : 00000001
    [318h 0792   4]          Max Raw Data Length : 00001000

    [31Ch 0796  12]         Error Status Address : [Generic Address Structure]
    [31Ch 0796   1]                     Space ID : 00 [SystemMemory]
    [31Dh 0797   1]                    Bit Width : 40
    [31Eh 0798   1]                   Bit Offset : 00
    [31Fh 0799   1]         Encoded Access Width : 04 [QWord Access:64]
    [320h 0800   8]                      Address : 00000000785D0040

    [328h 0808  28]                       Notify : [Hardware Error Notification Structure]
    [328h 0808   1]                  Notify Type : 08 [SEA]
    [329h 0809   1]                Notify Length : 1C
    [32Ah 0810   2]   Configuration Write Enable : 0000
    [32Ch 0812   4]                 PollInterval : 00000000
    [330h 0816   4]                       Vector : 00000000
    [334h 0820   4]      Polling Threshold Value : 00000000
    [338h 0824   4]     Polling Threshold Window : 00000000
    [33Ch 0828   4]        Error Threshold Value : 00000000
    [340h 0832   4]       Error Threshold Window : 00000000

    [344h 0836   4]    Error Status Block Length : 00001000
    [348h 0840  12]            Read Ack Register : [Generic Address Structure]
    [348h 0840   1]                     Space ID : 00 [SystemMemory]
    [349h 0841   1]                    Bit Width : 40
    [34Ah 0842   1]                   Bit Offset : 00
    [34Bh 0843   1]         Encoded Access Width : 04 [QWord Access:64]
    [34Ch 0844   8]                      Address : 00000000785D0098

    [354h 0852   8]            Read Ack Preserve : 00000000FFFFFFFE
    [35Ch 0860   8]               Read Ack Write : 0000000000000001

    .....................................................................................

(3) After a synchronous external abort(SEA) happen, Qemu receive a SIGBUS and 
    filled the CPER into guest GHES memory.  For example, according to above table,
    the address that contains the physical address of a block of memory that holds
    the error status data for this abort is 0x00000000785D0040
(4) the address for SEA notification error source is 0x785d80b0
    (qemu) xp /1 0x00000000785D0040
    00000000785d0040: 0x785d80b0

(5) check the content of generic error status block and generic error data entry
    (qemu) xp /100x 0x785d80b0
    00000000785d80b0: 0x00000001 0x00000000 0x00000000 0x00000098
    00000000785d80c0: 0x00000000 0xa5bc1114 0x4ede6f64 0x833e63b8
    00000000785d80d0: 0xb1837ced 0x00000000 0x00000300 0x00000050
    00000000785d80e0: 0x00000000 0x00000000 0x00000000 0x00000000
    00000000785d80f0: 0x00000000 0x00000000 0x00000000 0x00000000
    00000000785d8100: 0x00000000 0x00000000 0x00000000 0x00004002
(6) check the OSPM's ACK value(for example SEA)
    /* Before OSPM acknowledges the error, check the ACK value */
    (qemu) xp /1 0x00000000785D0098
    00000000785d00f0: 0x00000000

    /* After OSPM acknowledges the error, check the ACK value, it change to 1 from 0 */
    (qemu) xp /1 0x00000000785D0098
    00000000785d00f0: 0x00000001

[3]: KVM deliver "BUS_MCEERR_AR" to Qemu, Qemu record the guest CPER and inject
    synchronous external abort to notify guest, then guest do the recovery.

[ 1552.516170] Synchronous External Abort: synchronous external abort (0x92000410) at 0x000000003751c6b4
[ 1553.074073] {1}[Hardware Error]: Hardware error from APEI Generic Hardware Error Source: 8
[ 1553.081654] {1}[Hardware Error]: event severity: recoverable
[ 1554.034191] {1}[Hardware Error]:  Error 0, type: recoverable
[ 1554.037934] {1}[Hardware Error]:   section_type: memory error
[ 1554.513261] {1}[Hardware Error]:   physical_address: 0x0000000040fa6000
[ 1554.513944] {1}[Hardware Error]:   error_type: 0, unknown
[ 1555.041451] Memory failure: 0x40fa6: Killing mca-recover:1296 due to hardware memory corruption
[ 1555.373116] Memory failure: 0x40fa6: recovery action for dirty LRU page: Recovered



Dongjiu Geng (10):
  hw/arm/virt: Add RAS platform version for migration
  ACPI: add some GHES structures and macros definition
  acpi: add build_append_ghes_notify() helper for Hardware Error
    Notification
  acpi: add build_append_ghes_generic_data() helper for Generic Error
    Data Entry
  acpi: add build_append_ghes_generic_status() helper for Generic Error
    Status Block
  docs: APEI GHES generation and CPER record description
  ACPI: Add APEI GHES table generation support
  KVM: Move related hwpoison page functions to accel/kvm/ folder
  target-arm: kvm64: inject synchronous External Abort
  target-arm: kvm64: handle SIGBUS signal from kernel or KVM

 accel/kvm/kvm-all.c             |  33 ++++
 default-configs/arm-softmmu.mak |   1 +
 docs/specs/acpi_hest_ghes.txt   |  97 +++++++++++
 hw/acpi/Kconfig                 |   4 +
 hw/acpi/Makefile.objs           |   1 +
 hw/acpi/acpi_ghes.c             | 348 ++++++++++++++++++++++++++++++++++++++++
 hw/acpi/aml-build.c             |  70 ++++++++
 hw/arm/virt-acpi-build.c        |  12 ++
 hw/arm/virt.c                   |   6 +
 include/exec/ram_addr.h         |  24 +++
 include/hw/acpi/acpi-defs.h     |  52 ++++++
 include/hw/acpi/acpi_ghes.h     |  83 ++++++++++
 include/hw/acpi/aml-build.h     |  21 +++
 include/hw/arm/virt.h           |   1 +
 include/sysemu/kvm.h            |   2 +-
 target/arm/internals.h          |   5 +-
 target/arm/kvm.c                |   3 +
 target/arm/kvm64.c              |  73 +++++++++
 target/arm/op_helper.c          |   2 +-
 target/i386/kvm.c               |  34 +---
 20 files changed, 835 insertions(+), 37 deletions(-)
 create mode 100644 docs/specs/acpi_hest_ghes.txt
 create mode 100644 hw/acpi/acpi_ghes.c
 create mode 100644 include/hw/acpi/acpi_ghes.h
```
#### [PATCH v9 0/7] virtio pmem driver 
##### From: Pankaj Gupta <pagupta@redhat.com>

```c

Hi Dan,

 Proposing the patch series to be merged via nvdimm tree
 as kindly agreed by you. We have ack/review on XFS, EXT4 &
 VIRTIO patches. 

 Incorporated all the changes suggested in v8. This version
 added a new patch 4 for dax for device mapper change and some
 minor style changes in patch 2. Kept all the reviews. Request
 to please merge the series.

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

Changes from PATCH v8: [1] 
 - Set device mapper synchronous if all target devices support - Dan
 - Move virtio_pmem.h to nvdimm directory  - Dan
 - Style, indentation & better error messages in patch 2 - DavidH
 - Added MST's ack in patch 2.

Changes from PATCH v7: [2]
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

[1] https://lkml.org/lkml/2019/5/10/447
[2] https://lkml.org/lkml/2019/4/26/36
[3] https://www.spinics.net/lists/kvm/msg149761.html
[4] https://www.spinics.net/lists/kvm/msg153095.html  
[5] https://lkml.org/lkml/2018/8/31/413
[6] https://marc.info/?l=linux-kernel&m=153572228719237&w=2 
[7] https://marc.info/?l=qemu-devel&m=153555721901824&w=2
[8] https://lists.oasis-open.org/archives/virtio-dev/201903/msg00083.html
[9] https://lkml.org/lkml/2019/1/9/1191

 drivers/acpi/nfit/core.c         |    4 -
 drivers/dax/bus.c                |    2 
 drivers/dax/super.c              |   19 +++++
 drivers/md/dm-table.c            |   14 ++++
 drivers/md/dm.c                  |    3 
 drivers/nvdimm/Makefile          |    1 
 drivers/nvdimm/claim.c           |    6 +
 drivers/nvdimm/nd.h              |    1 
 drivers/nvdimm/nd_virtio.c       |  126 +++++++++++++++++++++++++++++++++++++++
 drivers/nvdimm/pmem.c            |   18 +++--
 drivers/nvdimm/region_devs.c     |   33 +++++++++-
 drivers/nvdimm/virtio_pmem.c     |  122 +++++++++++++++++++++++++++++++++++++
 drivers/nvdimm/virtio_pmem.h     |   60 ++++++++++++++++++
 drivers/virtio/Kconfig           |   11 +++
 fs/ext4/file.c                   |   10 +--
 fs/xfs/xfs_file.c                |    9 +-
 include/linux/dax.h              |   26 +++++++-
 include/linux/libnvdimm.h        |    9 ++
 include/uapi/linux/virtio_ids.h  |    1 
 include/uapi/linux/virtio_pmem.h |   10 +++
 20 files changed, 460 insertions(+), 25 deletions(-)
```
