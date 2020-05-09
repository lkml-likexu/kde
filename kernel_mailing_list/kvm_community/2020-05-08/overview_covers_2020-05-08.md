

#### [PATCH RESEND v26 00/10] Add ARMv8 RAS virtualization support in QEMU
##### From: Dongjiu Geng <gengdongjiu@huawei.com>

```c
From patchwork Fri May  8 02:19:20 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Dongjiu Geng <gengdongjiu@huawei.com>
X-Patchwork-Id: 11535251
Return-Path: <SRS0=ySRk=6W=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id DB928159A
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  8 May 2020 02:17:45 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id C42CD2070B
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  8 May 2020 02:17:45 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726900AbgEHCRp (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 7 May 2020 22:17:45 -0400
Received: from szxga05-in.huawei.com ([45.249.212.191]:4286 "EHLO huawei.com"
        rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org with ESMTP
        id S1726811AbgEHCRo (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 7 May 2020 22:17:44 -0400
Received: from DGGEMS408-HUB.china.huawei.com (unknown [172.30.72.59])
        by Forcepoint Email with ESMTP id 16CFB4E8954DAC29E758;
        Fri,  8 May 2020 10:17:41 +0800 (CST)
Received: from huawei.com (10.151.151.243) by DGGEMS408-HUB.china.huawei.com
 (10.3.19.208) with Microsoft SMTP Server id 14.3.487.0; Fri, 8 May 2020
 10:17:35 +0800
From: Dongjiu Geng <gengdongjiu@huawei.com>
To: <imammedo@redhat.com>, <mst@redhat.com>,
        <xiaoguangrong.eric@gmail.com>, <peter.maydell@linaro.org>,
        <shannon.zhaosl@gmail.com>, <pbonzini@redhat.com>,
        <fam@euphon.net>, <rth@twiddle.net>, <ehabkost@redhat.com>,
        <mtosatti@redhat.com>, <qemu-devel@nongnu.org>,
        <kvm@vger.kernel.org>, <qemu-arm@nongnu.org>
CC: <gengdongjiu@huawei.com>, <zhengxiang9@huawei.com>,
        <Jonathan.Cameron@huawei.com>, <linuxarm@huawei.com>
Subject: [PATCH RESEND v26 00/10] Add ARMv8 RAS virtualization support in QEMU
Date: Fri, 8 May 2020 10:19:20 +0800
Message-ID: <20200508021930.37955-1-gengdongjiu@huawei.com>
X-Mailer: git-send-email 2.17.1
MIME-Version: 1.
X-Originating-IP: [10.151.151.243]
X-CFilter-Loop: Reflected
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

In the ARMv8 platform, the CPU error types includes synchronous external abort(SEA)
and SError Interrupt (SEI). If exception happens in guest, host does not know the detailed
information of guest, so it is expected that guest can do the recovery. For example, if an
exception happens in a guest user-space application, host does not know which application
encounters errors, only guest knows it.

For the ARMv8 SEA/SEI, KVM or host kernel delivers SIGBUS to notify userspace.
After user space gets the notification, it will record the CPER into guest GHES
buffer and inject an exception or IRQ to guest.

In the current implementation, if the type of SIGBUS is BUS_MCEERR_AR, we will
treat it as a synchronous exception, and notify guest with ARMv8 SEA
notification type after recording CPER into guest.

A) This series of patches are based on Qemu 4.2, which include two parts:
1. Generate APEI/GHES table.
2. Handle the SIGBUS signal, record the CPER in runtime and fill it into guest
   memory, then notify guest according to the type of SIGBUS.

B) The solution was suggested by James(james.morse@arm.com); The APEI part solution was suggested by Laszlo(lersek@redhat.com). Show some discussions in [1].

C) This series of patches have already been tested on ARM64 platform with RAS
feature enabled:
1. Show the APEI part verification result in [2].
2. Show the SIGBUS of BUS_MCEERR_AR handling verification result in [3].

D) Add 'ras' option in command Line to enable guest RAS error recovery feature, For example:
KVM model: ./qemu-system-aarch64 --enable-kvm -cpu host --bios QEMU_EFI.fd_new  -machine virt,gic-version=3,ras,kernel-irqchip=on
-smp 4 -nographic -kernel Image  -append "rdinit=/init console=ttyAMA0 mem=512M root=/dev/ram0" -initrd guestfs_new.cpio.gz
TCG model: ./qemu-system-aarch64 -cpu cortex-a57 --bios QEMU_EFI.fd_new  -machine virt,gic-version=3,ras,kernel-irqchip=on  -smp 4
-nographic -kernel Image  -append "rdinit=/init console=ttyAMA0 mem=512M root=/dev/ram0" -initrd guestfs_new.cpio.gz
---
Change since v23:
1. fix a warning for uuid

Change since v22:
1. Using 1 * KiB instead of 0x400 to define max size of one error block
2. Make the alignment to 8 bytes in bios_linker_loader_alloc()
3. Change "Copyright (c) 2019" to "Copyright (c) 2020" in file header
4. Fix some code style warnings/errors and add some comments in code
5. Address Jonathan's comments to easily support CCIX error injection
6. Add vmstate_ghes_state .subsections in vmstate_acpi_ged

Change since v21:
1. Make the user-facing 'ras' option description more clearly to address Peter's comments.
2. Update the doc description in "docs/specs/acpi_hest_ghes.rst"
3. Split HEST/GHES patches to more patches to make the review easily
4. Using source_id to index the location to save the CPER.
5. Optimize and simplify the logic to build HEST/GHES table to address Igor/Michael/Beata comments.
6. make ghes_addr_le a part of GED device.

Change since v20:
1. Move some implementation details from acpi_ghes.h to acpi_ghes.c
2. Add the reviewers for the ACPI/APEI/GHES part

Change since v19:
1. Fix clang compile error
2. Fix sphinx build error

Change since v18:
1. Fix some code-style and typo/grammar problems.
2. Remove no_ras in the VirtMachineClass struct.
3. Convert documentation to rst format.
4. Simplize the code and add comments for some magic value.
5. Move kvm_inject_arm_sea() function into the patch where it's used.
6. Register the reset handler(kvm_unpoison_all()) in the kvm_init() function.

Change since v17:
1. Improve some commit messages and comments.
2. Fix some code-style problems.
3. Add a *ras* machine option.
4. Move HEST/GHES related structures and macros into "hw/acpi/acpi_ghes.*".
5. Move HWPoison page functions into "include/sysemu/kvm_int.h".
6. Fix some bugs.
7. Improve the design document.

Change since v16:
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
5. Reuse something like https://github.com/imammedo/qemu/commit/3d2fd6d13a3ea298d2ee814835495ce6241d085c to build GAS
6. Remove much offsetof() in the function
7. Build independent tables first and only then build dependent tables passing to it pointers
   to previously build table if necessary.
8. Redefine macro GHES_ACPI_HEST_NOTIFY_RESERVED to ACPI_HEST_ERROR_SOURCE_COUNT to avoid confusion


Address Peter Maydell's comments
1. linux-headers is done as a patch of their own created using scripts/update-linux-headers.sh run against a mainline kernel tree
2. Tested whether this patchset builds OK on aarch32
3. Abstract Hwpoison page adding code  out properly into a cpu-independent source file from target/i386/kvm.c, such as kvm-all.c
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
    the error status data is 0x00000000785D0040
(4) the address of error source which is SEA notification type is 0x785d80b0
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
  acpi: nvdimm: change NVDIMM_UUID_LE to a common macro
  hw/arm/virt: Introduce a RAS machine option
  docs: APEI GHES generation and CPER record description
  ACPI: Build related register address fields via hardware error fw_cfg
    blob
  ACPI: Build Hardware Error Source Table
  ACPI: Record the Generic Error Status Block address
  KVM: Move hwpoison page related functions into kvm-all.c
  ACPI: Record Generic Error Status Block(GESB) table
  target-arm: kvm64: handle SIGBUS signal from kernel or KVM
  MAINTAINERS: Add ACPI/HEST/GHES entries

 MAINTAINERS                            |   9 +
 accel/kvm/kvm-all.c                    |  36 +++
 default-configs/arm-softmmu.mak        |   1 +
 docs/specs/acpi_hest_ghes.rst          | 110 ++++++++
 docs/specs/index.rst                   |   1 +
 hw/acpi/Kconfig                        |   4 +
 hw/acpi/Makefile.objs                  |   1 +
 hw/acpi/aml-build.c                    |   2 +
 hw/acpi/generic_event_device.c         |  19 ++
 hw/acpi/ghes.c                         | 448 +++++++++++++++++++++++++++++++++
 hw/acpi/nvdimm.c                       |  10 +-
 hw/arm/virt-acpi-build.c               |  15 ++
 hw/arm/virt.c                          |  23 ++
 include/hw/acpi/aml-build.h            |   1 +
 include/hw/acpi/generic_event_device.h |   2 +
 include/hw/acpi/ghes.h                 |  74 ++++++
 include/hw/arm/virt.h                  |   1 +
 include/qemu/uuid.h                    |  27 ++
 include/sysemu/kvm.h                   |   3 +-
 include/sysemu/kvm_int.h               |  12 +
 target/arm/cpu.h                       |   4 +
 target/arm/helper.c                    |   2 +-
 target/arm/internals.h                 |   5 +-
 target/arm/kvm64.c                     |  77 ++++++
 target/arm/tlb_helper.c                |   2 +-
 target/i386/cpu.h                      |   2 +
 target/i386/kvm.c                      |  36 ---
 27 files changed, 878 insertions(+), 49 deletions(-)
 create mode 100644 docs/specs/acpi_hest_ghes.rst
 create mode 100644 hw/acpi/ghes.c
 create mode 100644 include/hw/acpi/ghes.h
```
#### [PATCH v2 0/9] vfio/fsl-mc: VFIO support for FSL-MC devices
##### From: Diana Craciun <diana.craciun@oss.nxp.com>

```c
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

DPAA2 (Data Path Acceleration Architecture) consists in
mechanisms for processing Ethernet packets, queue management,
accelerators, etc.

The Management Complex (mc) is a hardware entity that manages the DPAA2
hardware resources. It provides an object-based abstraction for software
drivers to use the DPAA2 hardware. The MC mediates operations such as
create, discover, destroy of DPAA2 objects.
The MC provides memory-mapped I/O command interfaces (MC portals) which
DPAA2 software drivers use to operate on DPAA2 objects.

A DPRC is a container object that holds other types of DPAA2 objects.
Each object in the DPRC is a Linux device and bound to a driver.
The MC-bus driver is a platform driver (different from PCI or platform
bus). The DPRC driver does runtime management of a bus instance. It
performs the initial scan of the DPRC and handles changes in the DPRC
configuration (adding/removing objects).

All objects inside a container share the same hardware isolation
context, meaning that only an entire DPRC can be assigned to
a virtual machine.
When a container is assigned to a virtual machine, all the objects
within that container are assigned to that virtual machine.
The DPRC container assigned to the virtual machine is not allowed
to change contents (add/remove objects) by the guest. The restriction
is set by the host and enforced by the mc hardware.

The DPAA2 objects can be directly assigned to the guest. However
the MC portals (the memory mapped command interface to the MC) need
to be emulated because there are commands that configure the
interrupts and the isolation IDs which are virtual in the guest.

Example:
echo vfio-fsl-mc > /sys/bus/fsl-mc/devices/dprc.2/driver_override
echo dprc.2 > /sys/bus/fsl-mc/drivers/vfio-fsl-mc/bind

The dprc.2 is bound to the VFIO driver and all the objects within
dprc.2 are going to be bound to the VFIO driver.

More details about the DPAA2 objects can be found here:
Documentation/networking/device_drivers/freescale/dpaa2/overview.rst

The patches are dependent on some changes in the mc-bus (bus/fsl-mc)
driver. The changes were needed in order to re-use code and to export
some more functions that are needed by the VFIO driver.
Currenlty the mc-bus patches are under review:
https://www.spinics.net/lists/kernel/msg3505228.html

v1 --> v2
- Fixed the container reset, a new flag added to the firmware command
- Implement a bus notifier for setting driver_override

Bharat Bhushan (1):
  vfio/fsl-mc: Add VFIO framework skeleton for fsl-mc devices

Diana Craciun (8):
  vfio/fsl-mc: Scan DPRC objects on vfio-fsl-mc driver bind
  vfio/fsl-mc: Implement VFIO_DEVICE_GET_INFO ioctl
  vfio/fsl-mc: Implement VFIO_DEVICE_GET_REGION_INFO ioctl call
  vfio/fsl-mc: Allow userspace to MMAP fsl-mc device MMIO regions
  vfio/fsl-mc: Added lock support in preparation for interrupt handling
  vfio/fsl-mc: Add irq infrastructure for fsl-mc devices
  vfio/fsl-mc: trigger an interrupt via eventfd
  vfio/fsl-mc: Add read/write support for fsl-mc devices

 MAINTAINERS                               |   6 +
 drivers/vfio/Kconfig                      |   1 +
 drivers/vfio/Makefile                     |   1 +
 drivers/vfio/fsl-mc/Kconfig               |   9 +
 drivers/vfio/fsl-mc/Makefile              |   4 +
 drivers/vfio/fsl-mc/vfio_fsl_mc.c         | 695 ++++++++++++++++++++++
 drivers/vfio/fsl-mc/vfio_fsl_mc_intr.c    | 221 +++++++
 drivers/vfio/fsl-mc/vfio_fsl_mc_private.h |  57 ++
 include/uapi/linux/vfio.h                 |   1 +
 9 files changed, 995 insertions(+)
 create mode 100644 drivers/vfio/fsl-mc/Kconfig
 create mode 100644 drivers/vfio/fsl-mc/Makefile
 create mode 100644 drivers/vfio/fsl-mc/vfio_fsl_mc.c
 create mode 100644 drivers/vfio/fsl-mc/vfio_fsl_mc_intr.c
 create mode 100644 drivers/vfio/fsl-mc/vfio_fsl_mc_private.h
```
#### [PATCH 0/3] Pin the hrtimer used for VMX-preemption timer emulation
##### From: Jim Mattson <jmattson@google.com>

```c
From patchwork Fri May  8 20:36:40 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Jim Mattson <jmattson@google.com>
X-Patchwork-Id: 11537545
Return-Path: <SRS0=ySRk=6W=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 8401792A
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  8 May 2020 20:36:54 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 6B7A821775
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  8 May 2020 20:36:54 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=google.com header.i=@google.com
 header.b="g5ixACjY"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727082AbgEHUgx (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 8 May 2020 16:36:53 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:48988 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-FAIL-OK-FAIL)
        by vger.kernel.org with ESMTP id S1726811AbgEHUgw (ORCPT
        <rfc822;kvm@vger.kernel.org>); Fri, 8 May 2020 16:36:52 -0400
Received: from mail-qv1-xf49.google.com (mail-qv1-xf49.google.com
 [IPv6:2607:f8b0:4864:20::f49])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id CF7CBC061A0C
        for <kvm@vger.kernel.org>; Fri,  8 May 2020 13:36:52 -0700 (PDT)
Received: by mail-qv1-xf49.google.com with SMTP id fe18so2987012qvb.11
        for <kvm@vger.kernel.org>; Fri, 08 May 2020 13:36:52 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=date:message-id:mime-version:subject:from:to:cc;
        bh=17ywsygLyzXzKvE1o24FLCWQbEa2U3x3ZZW9XrMM+vc=;
        b=g5ixACjYin6jSZckRdyy/UzAYTUEz6SehoYl4Ntkn2M3cJddj7KsYxFr/2RxVUcg+H
         sxBgy6XgYSHjDbciASHMpGYmEUBWLlEcKQVLgS1ll8XNGRk7G4MjrvJ98LBmmjNO8ndt
         /tFxRZkeQs8AKjoMnsTFabqe59jYqw+coEL69Rez6gpg/jz1B/aOECROUkTL9zQFLGB1
         +LRzPp5UJsSxAbnNP5Qct20Ugtiy1Ryn+1KwdFAhvDNPK8x4vgxtaQQ7bHeHjZ9zqfn7
         7I0zXoe0Isz9+kFHjY0DLFiFITsGcCk87qC5LtyNx8qaUj9uPnQyEIoUOdjesOijudGR
         vWiw==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:date:message-id:mime-version:subject:from:to:cc;
        bh=17ywsygLyzXzKvE1o24FLCWQbEa2U3x3ZZW9XrMM+vc=;
        b=kEdSAK0VUyfOL9pZX8BTYdTXfccITXXxSC2lRM4taCtb7C7/btjkkKJaJjySSZuCy8
         MxdKF+Lf0t6DUOXANxeAqzXeHMoBVEd5K/IS/XR8BXrQZeBGEPzNdZcFJS46gdBSfCE7
         20YfaPhfnOVS86jhySd09b9FkCYVpqzQUEyQpMobMcPtM5HGFCsRXHgDeFP7TvttxTxc
         iHzS2HAm0m0VitXvbEh59alD/at47fLJBn9Mjv1jg6QZS9mA+SpEN8tL5UYddlE2P/ng
         Ok3GaH41pIFVEXkI5DT6OyGo23ckuyqajdkHuIza7pr75WSuqQEvWHOi24YF265VOTcx
         wO4Q==
X-Gm-Message-State: AGi0PuabB49suea1NqDfSxu0RghfzjoMBODzvvbivM6M4T2XceJ4rHQT
        OUrX4pyMnmWXKlhAZaMbgKg5e4eTkux3i8cv3mTdVfHpKCtv0ACJxl8baRtyHJf5OYe1Sbiz4lB
        VTI/phiP4CTR2ILaJFw9/eB4Wm0q+wOG0gl3NIzEitHS8JlQlbbiqcH1h1T7Xclo=
X-Google-Smtp-Source: 
 APiQypIyTWq2vo9sq7tOeCqr+X5NjHGVrME+s/YHsjIKqz0KK6gvojdgUTeA/UiM8dYqGakMqIaV9Sdjo9QK3w==
X-Received: by 2002:ad4:568a:: with SMTP id
 bc10mr4510760qvb.148.1588970211919;
 Fri, 08 May 2020 13:36:51 -0700 (PDT)
Date: Fri,  8 May 2020 13:36:40 -0700
Message-Id: <20200508203643.85477-1-jmattson@google.com>
Mime-Version: 1.0
X-Mailer: git-send-email 2.26.2.645.ge9eca65c58-goog
Subject: [PATCH 0/3] Pin the hrtimer used for VMX-preemption timer emulation
From: Jim Mattson <jmattson@google.com>
To: kvm@vger.kernel.org, Paolo Bonzini <pbonzini@redhat.com>
Cc: Jim Mattson <jmattson@google.com>
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

I'm still not entirely convinced that the Linux hrtimer can be used to
accurately emulate the VMX-preemption timer, but it definitely doesn't
work if the hrtimer is on a different logical processor from the vCPU
thread that needs to get kicked out of VMX non-root operation.

With these changes, the kvm-unit-test (sent separately) that verifies
that a guest can't actually observe a delayed VMX-preemption timer
VM-exit passes 99.999% of the time on a 2GHz Skylake system.

It might be possible to improve that pass rate even more by increasing
the scaling factor in the virtual IA32_VMX_MISC[4:0], but you'd have
to be even more of a stickler than I to go to that extreme.

By the way, what is the point of migrating the hrtimers for the APIC
and the PIT, since they aren't even pinned to begin with?

The subject line of the first patch was crafted for you, Sean. :-D

Jim Mattson (3):
  KVM: nVMX: Really make emulated nested preemption timer pinned
  KVM: nVMX: Change emulated VMX-preemption timer hrtimer to absolute
  KVM: nVMX: Migrate the VMX-preemption timer

 arch/x86/include/asm/kvm_host.h |  2 ++
 arch/x86/kvm/irq.c              |  2 ++
 arch/x86/kvm/vmx/nested.c       |  5 +++--
 arch/x86/kvm/vmx/vmx.c          | 11 +++++++++++
 4 files changed, 18 insertions(+), 2 deletions(-)
```
#### [PATCH v2 0/3] arch/x86: Enable MPK feature on AMD
##### From: Babu Moger <babu.moger@amd.com>

```c
From patchwork Fri May  8 21:09:40 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 8bit
X-Patchwork-Submitter: Babu Moger <babu.moger@amd.com>
X-Patchwork-Id: 11537601
Return-Path: <SRS0=ySRk=6W=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 2B0D1139F
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  8 May 2020 21:09:54 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 09D8321974
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  8 May 2020 21:09:53 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=amdcloud.onmicrosoft.com
 header.i=@amdcloud.onmicrosoft.com header.b="2octv/pb"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727924AbgEHVJv (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 8 May 2020 17:09:51 -0400
Received: from mail-bn7nam10on2075.outbound.protection.outlook.com
 ([40.107.92.75]:6097
        "EHLO NAM10-BN7-obe.outbound.protection.outlook.com"
        rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org with ESMTP
        id S1727088AbgEHVJu (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 8 May 2020 17:09:50 -0400
ARC-Seal: i=1; a=rsa-sha256; s=arcselector9901; d=microsoft.com; cv=none;
 b=DOzViDWIXpz9p50aSrQztQE8MEN5xiRNzFt98I2ZNl9azcUAtZqTkiu8iLloJWbQvHh0G18WymQGl5pNmEDbRi5DeniLtsRlHvJeH0xdA0I6wuC658VZFncEzrWTkoOfdztKE4g5COzM5LkVwWRmseqPD4iYU6cnu/ZTbh4I5end4YPgj6+4kNgS7J2K9M3nyW59a29V83seHsof9hgbPex1cm7lkOYDkeFb68Gh7l137pN9BwfsZJEnomKo2dG/bWhvuN9aBQnAiTweF1rxVcXR3RoznLGaG3ZxcTDsUWilYRylx2CRP17yx7VU++A067ghh00YzNimNlOjCKKc/w==
ARC-Message-Signature: i=1; a=rsa-sha256; c=relaxed/relaxed; d=microsoft.com;
 s=arcselector9901;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=55OWPmbFkE16QROd1bFJxGuXEuFYoAgCuzOyoubLayQ=;
 b=VOvFGGJj0J4Jat6HAvNFdszrzAX4QJMtdusksDCG97O0ar026EDG7ju8PLO6xIvTUKv9Oldq3DzNcBp6qCuBDBd+L0t7JU2irthK0i2545uRyAhb1hGYbUdXTkGm4lQOL2ok0RHxf2jzsJDPWtPDjOmxhi8+/Pu8ZmNEv/ELDKGr/09cQHtLurAWMqicdOKxh+FLl2dxcaWDzDW68DDH6uww+GEHQnNMqVBhC7IP985VwmTdXY/frrzK8OaOs2lGjg3oyAdVOHKLKxl3oxIpTHGWV2CaHANTF+rL2dO7pyTmjZV3LL2a76TIQgwH5pvbxgOd0fnbFJVBhkxpTJQQMg==
ARC-Authentication-Results: i=1; mx.microsoft.com 1; spf=pass
 smtp.mailfrom=amd.com; dmarc=pass action=none header.from=amd.com; dkim=pass
 header.d=amd.com; arc=none
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
 d=amdcloud.onmicrosoft.com; s=selector2-amdcloud-onmicrosoft-com;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=55OWPmbFkE16QROd1bFJxGuXEuFYoAgCuzOyoubLayQ=;
 b=2octv/pbT1rJsdruU23SYuXRuLlRyMXXwbi4W0W8bs/Hcot7sCrGgso9BXjYUk3r1OLwSfkEMh1mUKOjCN0nMcsb0bNX+NbSIFNmTDEuPfZK8UpyLhRIXTN73r8XgnBU9yY0V708wDoKUTcxbWfJCDK+COhpvb0GPxQCjWJXaL4=
Authentication-Results: tencent.com; dkim=none (message not signed)
 header.d=none;tencent.com; dmarc=none action=none header.from=amd.com;
Received: from SN1PR12MB2560.namprd12.prod.outlook.com (2603:10b6:802:26::19)
 by SN1PR12MB2591.namprd12.prod.outlook.com (2603:10b6:802:30::32) with
 Microsoft SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.2958.33; Fri, 8 May
 2020 21:09:43 +0000
Received: from SN1PR12MB2560.namprd12.prod.outlook.com
 ([fe80::c0f:2938:784f:ed8d]) by SN1PR12MB2560.namprd12.prod.outlook.com
 ([fe80::c0f:2938:784f:ed8d%7]) with mapi id 15.20.2979.028; Fri, 8 May 2020
 21:09:43 +0000
Subject: [PATCH v2 0/3] arch/x86: Enable MPK feature on AMD
From: Babu Moger <babu.moger@amd.com>
To: corbet@lwn.net, tglx@linutronix.de, mingo@redhat.com, bp@alien8.de,
        hpa@zytor.com, pbonzini@redhat.com, sean.j.christopherson@intel.com
Cc: x86@kernel.org, vkuznets@redhat.com, wanpengli@tencent.com,
        jmattson@google.com, joro@8bytes.org, dave.hansen@linux.intel.com,
        luto@kernel.org, peterz@infradead.org, mchehab+samsung@kernel.org,
        babu.moger@amd.com, changbin.du@intel.com, namit@vmware.com,
        bigeasy@linutronix.de, yang.shi@linux.alibaba.com,
        asteinhauser@google.com, anshuman.khandual@arm.com,
        jan.kiszka@siemens.com, akpm@linux-foundation.org,
        steven.price@arm.com, rppt@linux.vnet.ibm.com, peterx@redhat.com,
        dan.j.williams@intel.com, arjunroy@google.com, logang@deltatee.com,
        thellstrom@vmware.com, aarcange@redhat.com, justin.he@arm.com,
        robin.murphy@arm.com, ira.weiny@intel.com, keescook@chromium.org,
        jgross@suse.com, andrew.cooper3@citrix.com,
        pawan.kumar.gupta@linux.intel.com, fenghua.yu@intel.com,
        vineela.tummalapalli@intel.com, yamada.masahiro@socionext.com,
        sam@ravnborg.org, acme@redhat.com, linux-doc@vger.kernel.org,
        linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Date: Fri, 08 May 2020 16:09:40 -0500
Message-ID: <158897190718.22378.3974700869904223395.stgit@naples-babu.amd.com>
User-Agent: StGit/unknown-version
X-ClientProxiedBy: SN6PR01CA0001.prod.exchangelabs.com (2603:10b6:805:b6::14)
 To SN1PR12MB2560.namprd12.prod.outlook.com (2603:10b6:802:26::19)
MIME-Version: 1.0
X-MS-Exchange-MessageSentRepresentingType: 1
Received: from naples-babu.amd.com (165.204.78.2) by
 SN6PR01CA0001.prod.exchangelabs.com (2603:10b6:805:b6::14) with Microsoft
 SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.2979.26 via Frontend
 Transport; Fri, 8 May 2020 21:09:41 +0000
X-Originating-IP: [165.204.78.2]
X-MS-PublicTrafficType: Email
X-MS-Office365-Filtering-HT: Tenant
X-MS-Office365-Filtering-Correlation-Id: 325917d1-56a8-4602-d6dd-08d7f39420c8
X-MS-TrafficTypeDiagnostic: SN1PR12MB2591:|SN1PR12MB2591:
X-MS-Exchange-Transport-Forked: True
X-Microsoft-Antispam-PRVS: 
 <SN1PR12MB2591752BD22868BC6C57BC4195A20@SN1PR12MB2591.namprd12.prod.outlook.com>
X-MS-Oob-TLC-OOBClassifiers: OLM:8882;
X-Forefront-PRVS: 039735BC4E
X-MS-Exchange-SenderADCheck: 1
X-Microsoft-Antispam: BCL:0;
X-Microsoft-Antispam-Message-Info: 
 TDrFiE3TTxkh+t5k77ckEKFWJkoUsdjTH2LxxOI78+Nh8pMGl0gmv5hOmg7QZqXgn0iUHqJ0OJeAgZzuc9RF20h7mS0/k1ubS7VaKkSP5lY5M/LVvgZENN2ehKxYX+4az+pJ8By3IiQdTeLARS+6GFGWCFHsvAKPzpkM2kPV/mj/kyAWv2l/PxrUTeQRtFYFibnFNLTi1Hxqih4Bs0nXj4W7ZDV9FFaTRew2zhJQqWYtpQQTtpUmXxuPUpc4EIl1AivHIL1RWyVVbfnKDUY6hOS5t2R1bJFARw/bjF0pLQp1UGf0r2aGHcqkPpPDEWLuflur2TQLo+SCXFpMkuWIu5uikP7UJtSwtuPJIitf4ddt/6ZbpkJje3ebenNJivOJlr9nP7Dpj+3jfwUDptDzVYOZN155tdy+eK57MVRFT25C/yJYXlc/2ZDXHETpjYaLuuOEkh9AcLOkGr5VpF9DPpmtzxWwGObAXhPDkPt0ff1krbFBFYB2jnMm+4/ZUjf2EWH17WFslzX00gddTmScxFGvNSph2P6TklS05XaPk88FOrZBmACYG5rnXk2ZjFyhIEOz1k/+XR2Gq3RaaVxcGlsKmqLJYUQvGmNphI2etec=
X-Forefront-Antispam-Report: 
 CIP:255.255.255.255;CTRY:;LANG:en;SCL:1;SRV:;IPV:NLI;SFV:NSPM;H:SN1PR12MB2560.namprd12.prod.outlook.com;PTR:;CAT:NONE;SFTY:;SFS:(4636009)(39860400002)(376002)(346002)(136003)(396003)(366004)(33430700001)(7406005)(16526019)(4326008)(7696005)(7416002)(186003)(26005)(66556008)(8936002)(52116002)(316002)(66946007)(66476007)(33440700001)(2906002)(44832011)(956004)(478600001)(55016002)(966005)(5660300002)(8676002)(103116003)(86362001);DIR:OUT;SFP:1101;
X-MS-Exchange-AntiSpam-MessageData: 
 zmDu0/jvHkbocr7X85VYqRqBk4DsYJsMlJusIgtmQEDDSOpcuyAVtSzAlPKqxIXrdthP0+0ueRpJwYRH3YcMrt4Y2eIPfkXE/L98qZW5k/cl7vW5Hv0HkhesxvnIzUvzIYTuzaXGHdbETvDXu9xsnWCJohzKAPOzcXxZroXzK8q58nZeK7WNlxUwTXMKZCAylECJflsTHQTXa1H//SbSRZGJOlWyi68yfh1hxhbjU7wLXDuxDA6yi85sdBCHRJpJufvsLx6EL6mY4FpA7rWACm44SaVzd/slKvnHZRjYXNcTEJKDIDfXvUWS1e4+ipf6cLzaWl6WgWNUYgy9HigDwaiArIZZ71XmgqHSBH+aCdGOb7GOdnTwAK2/HiZ0vuxiUOMX7c6qZVYUpHCuOIDwzBRuiHJPbgMka2PY9Q/xpZq6RmMgGxiHuMzLmlOQQc/9Ca85mWhpHPCf28Ny+uKprAcCpemHx7P4ZjngF34vfLY=
X-OriginatorOrg: amd.com
X-MS-Exchange-CrossTenant-Network-Message-Id: 
 325917d1-56a8-4602-d6dd-08d7f39420c8
X-MS-Exchange-CrossTenant-OriginalArrivalTime: 08 May 2020 21:09:43.0065
 (UTC)
X-MS-Exchange-CrossTenant-FromEntityHeader: Hosted
X-MS-Exchange-CrossTenant-Id: 3dd8961f-e488-4e60-8e11-a82d994e183d
X-MS-Exchange-CrossTenant-MailboxType: HOSTED
X-MS-Exchange-CrossTenant-UserPrincipalName: 
 +bPueknMWfiVGiOpb7dReMa9fCFs8rR/SoTrigVaPaAK3UDfUck2tIZ39sAye6tN
X-MS-Exchange-Transport-CrossTenantHeadersStamped: SN1PR12MB2591
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

AMD's next generation of EPYC processors support the MPK (Memory
Protection Keys) feature.

AMD documentation for MPK feature is available at "AMD64 Architecture
Programmer’s Manual Volume 2: System Programming, Pub. 24593 Rev. 3.34,
Section 5.6.6 Memory Protection Keys (MPK) Bit".

The documentation can be obtained at the link below:
https://bugzilla.kernel.org/show_bug.cgi?id=206537

This series enables the feature on AMD and updates config parameters
to reflect the MPK support on generic x86 platforms.
---
v2:
  - Introduced intermediate config option X86_MEMORY_PROTECTION_KEYS to
    avoid user propmpts. Kept X86_INTEL_MEMORY_PROTECTION_KEYS as is.
    Eventually, we will be moving to X86_MEMORY_PROTECTION_KEYS after
    couple of kernel revisions. 
  - Moved pkru data structures to kvm_vcpu_arch. Moved save/restore pkru
    to kvm_load_host_xsave_state/kvm_load_guest_xsave_state.

v1:
  https://lore.kernel.org/lkml/158880240546.11615.2219410169137148044.stgit@naples-babu.amd.com/

Babu Moger (3):
      arch/x86: Rename config X86_INTEL_MEMORY_PROTECTION_KEYS to generic x86
      KVM: x86: Move pkru save/restore to x86.c
      KVM: SVM: Add support for MPK feature on AMD


 Documentation/core-api/protection-keys.rst     |    3 ++-
 arch/x86/Kconfig                               |   11 +++++++++--
 arch/x86/include/asm/disabled-features.h       |    4 ++--
 arch/x86/include/asm/kvm_host.h                |    1 +
 arch/x86/include/asm/mmu.h                     |    2 +-
 arch/x86/include/asm/mmu_context.h             |    4 ++--
 arch/x86/include/asm/pgtable.h                 |    4 ++--
 arch/x86/include/asm/pgtable_types.h           |    2 +-
 arch/x86/include/asm/special_insns.h           |    2 +-
 arch/x86/include/uapi/asm/mman.h               |    2 +-
 arch/x86/kernel/cpu/common.c                   |    2 +-
 arch/x86/kvm/svm/svm.c                         |    4 ++++
 arch/x86/kvm/vmx/vmx.c                         |   18 ------------------
 arch/x86/kvm/x86.c                             |   20 ++++++++++++++++++++
 arch/x86/mm/Makefile                           |    2 +-
 arch/x86/mm/pkeys.c                            |    2 +-
 scripts/headers_install.sh                     |    2 +-
 tools/arch/x86/include/asm/disabled-features.h |    4 ++--
 18 files changed, 52 insertions(+), 37 deletions(-)

--
```
