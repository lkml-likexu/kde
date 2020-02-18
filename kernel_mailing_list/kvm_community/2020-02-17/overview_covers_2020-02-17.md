

#### [PATCH RESEND v23 00/10] Add ARMv8 RAS virtualization support in QEMU
##### From: Dongjiu Geng <gengdongjiu@huawei.com>

```c
From patchwork Mon Feb 17 01:27:27 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Dongjiu Geng <gengdongjiu@huawei.com>
X-Patchwork-Id: 11384871
Return-Path: <SRS0=fZmU=4F=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 4747817F0
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 17 Feb 2020 01:25:26 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 1AC40208C4
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 17 Feb 2020 01:25:25 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726269AbgBQBZZ (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Sun, 16 Feb 2020 20:25:25 -0500
Received: from szxga06-in.huawei.com ([45.249.212.32]:37292 "EHLO huawei.com"
        rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org with ESMTP
        id S1726240AbgBQBZY (ORCPT <rfc822;kvm@vger.kernel.org>);
        Sun, 16 Feb 2020 20:25:24 -0500
Received: from DGGEMS405-HUB.china.huawei.com (unknown [172.30.72.59])
        by Forcepoint Email with ESMTP id E514DCE63C4170F9DB0B;
        Mon, 17 Feb 2020 09:25:22 +0800 (CST)
Received: from huawei.com (10.151.151.243) by DGGEMS405-HUB.china.huawei.com
 (10.3.19.205) with Microsoft SMTP Server id 14.3.439.0; Mon, 17 Feb 2020
 09:25:15 +0800
From: Dongjiu Geng <gengdongjiu@huawei.com>
To: <mst@redhat.com>, <imammedo@redhat.com>,
        <xiaoguangrong.eric@gmail.com>, <shannon.zhaosl@gmail.com>,
        <peter.maydell@linaro.org>, <fam@euphon.net>, <rth@twiddle.net>,
        <ehabkost@redhat.com>, <mtosatti@redhat.com>,
        <qemu-devel@nongnu.org>, <kvm@vger.kernel.org>,
        <qemu-arm@nongnu.org>, <pbonzini@redhat.com>,
        <james.morse@arm.com>, <lersek@redhat.com>,
        <jonathan.cameron@huawei.com>,
        <shameerali.kolothum.thodi@huawei.com>
CC: <gengdongjiu@huawei.com>, <zhengxiang9@huawei.com>
Subject: [PATCH RESEND v23 00/10] Add ARMv8 RAS virtualization support in QEMU
Date: Mon, 17 Feb 2020 09:27:27 +0800
Message-ID: <20200217012737.30231-1-gengdongjiu@huawei.com>
X-Mailer: git-send-email 2.18.0.huawei.25
MIME-Version: 1.0
X-Originating-IP: [10.151.151.243]
X-CFilter-Loop: Reflected
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

In the ARMv8 platform, the CPU error types includes synchronous external abort(SEA)
and SError Interrupt (SEI). If exception happens in guest, host does not know the
detailed information of guest, so it is expected that guest can do the recovery.
For example, if an exception happens in a guest user-space application, host does
not know which application encounters errors, only guest knows it.

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
KVM model: ./qemu-system-aarch64 --enable-kvm -cpu host --bios QEMU_EFI.fd_new  -machine virt,gic-version=3,ras,kernel-irqchip=on  -smp 4 -nographic -kernel Image  -append "rdinit=/init console=ttyAMA0 mem=512M root=/dev/ram0" -initrd guestfs_new.cpio.gz
TCG model: ./qemu-system-aarch64 -cpu cortex-a57 --bios QEMU_EFI.fd_new  -machine virt,gic-version=3,ras,kernel-irqchip=on  -smp 4 -nographic -kernel Image  -append "rdinit=/init console=ttyAMA0 mem=512M root=/dev/ram0" -initrd guestfs_new.cpio.gz
---
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
 hw/acpi/generic_event_device.c         |  18 ++
 hw/acpi/ghes.c                         | 450 +++++++++++++++++++++++++++++++++
 hw/acpi/nvdimm.c                       |   8 +-
 hw/arm/virt-acpi-build.c               |  17 ++
 hw/arm/virt.c                          |  23 ++
 include/hw/acpi/aml-build.h            |   1 +
 include/hw/acpi/generic_event_device.h |   2 +
 include/hw/acpi/ghes.h                 |  74 ++++++
 include/hw/arm/virt.h                  |   1 +
 include/qemu/uuid.h                    |   5 +
 include/sysemu/kvm.h                   |   3 +-
 include/sysemu/kvm_int.h               |  12 +
 target/arm/cpu.h                       |   4 +
 target/arm/helper.c                    |   2 +-
 target/arm/internals.h                 |   5 +-
 target/arm/kvm64.c                     |  73 ++++++
 target/arm/tlb_helper.c                |   2 +-
 target/i386/cpu.h                      |   2 +
 target/i386/kvm.c                      |  36 ---
 27 files changed, 854 insertions(+), 48 deletions(-)
 create mode 100644 docs/specs/acpi_hest_ghes.rst
 create mode 100644 hw/acpi/ghes.c
 create mode 100644 include/hw/acpi/ghes.h
```
#### [PATCH v24 00/10] Add ARMv8 RAS virtualization support in QEMU
##### From: Dongjiu Geng <gengdongjiu@huawei.com>

```c
From patchwork Mon Feb 17 13:12:38 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Dongjiu Geng <gengdongjiu@huawei.com>
X-Patchwork-Id: 11386355
Return-Path: <SRS0=fZmU=4F=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 3F1BF139A
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 17 Feb 2020 13:11:33 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 163F42070B
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 17 Feb 2020 13:11:33 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728264AbgBQNLc (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 17 Feb 2020 08:11:32 -0500
Received: from szxga06-in.huawei.com ([45.249.212.32]:45192 "EHLO huawei.com"
        rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org with ESMTP
        id S1726710AbgBQNLc (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 17 Feb 2020 08:11:32 -0500
Received: from DGGEMS410-HUB.china.huawei.com (unknown [172.30.72.60])
        by Forcepoint Email with ESMTP id 1410B3FD86F5D69014DE;
        Mon, 17 Feb 2020 21:10:36 +0800 (CST)
Received: from huawei.com (10.151.151.243) by DGGEMS410-HUB.china.huawei.com
 (10.3.19.210) with Microsoft SMTP Server id 14.3.439.0; Mon, 17 Feb 2020
 21:10:27 +0800
From: Dongjiu Geng <gengdongjiu@huawei.com>
To: <mst@redhat.com>, <imammedo@redhat.com>,
        <xiaoguangrong.eric@gmail.com>, <shannon.zhaosl@gmail.com>,
        <peter.maydell@linaro.org>, <fam@euphon.net>, <rth@twiddle.net>,
        <ehabkost@redhat.com>, <mtosatti@redhat.com>,
        <qemu-devel@nongnu.org>, <kvm@vger.kernel.org>,
        <qemu-arm@nongnu.org>, <pbonzini@redhat.com>,
        <james.morse@arm.com>, <lersek@redhat.com>,
        <jonathan.cameron@huawei.com>,
        <shameerali.kolothum.thodi@huawei.com>
CC: <gengdongjiu@huawei.com>, <zhengxiang9@huawei.com>
Subject: [PATCH v24 00/10] Add ARMv8 RAS virtualization support in QEMU
Date: Mon, 17 Feb 2020 21:12:38 +0800
Message-ID: <20200217131248.28273-1-gengdongjiu@huawei.com>
X-Mailer: git-send-email 2.18.0.huawei.25
MIME-Version: 1.0
X-Originating-IP: [10.151.151.243]
X-CFilter-Loop: Reflected
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

In the ARMv8 platform, the CPU error types includes synchronous external abort(SEA) and SError Interrupt (SEI). If exception happens in guest, host does not know the detailed information of guest, so it is expected that guest can do the recovery.
For example, if an exception happens in a guest user-space application, host does
not know which application encounters errors, only guest knows it.

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
KVM model: ./qemu-system-aarch64 --enable-kvm -cpu host --bios QEMU_EFI.fd_new  -machine virt,gic-version=3,ras,kernel-irqchip=on  -smp 4 -nographic -kernel Image  -append "rdinit=/init console=ttyAMA0 mem=512M root=/dev/ram0" -initrd guestfs_new.cpio.gz
TCG model: ./qemu-system-aarch64 -cpu cortex-a57 --bios QEMU_EFI.fd_new  -machine virt,gic-version=3,ras,kernel-irqchip=on  -smp 4 -nographic -kernel Image  -append "rdinit=/init console=ttyAMA0 mem=512M root=/dev/ram0" -initrd guestfs_new.cpio.gz
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
 hw/acpi/generic_event_device.c         |  18 ++
 hw/acpi/ghes.c                         | 450 +++++++++++++++++++++++++++++++++
 hw/acpi/nvdimm.c                       |   8 +-
 hw/arm/virt-acpi-build.c               |  17 ++
 hw/arm/virt.c                          |  23 ++
 include/hw/acpi/aml-build.h            |   1 +
 include/hw/acpi/generic_event_device.h |   2 +
 include/hw/acpi/ghes.h                 |  74 ++++++
 include/hw/arm/virt.h                  |   1 +
 include/qemu/uuid.h                    |   5 +
 include/sysemu/kvm.h                   |   3 +-
 include/sysemu/kvm_int.h               |  12 +
 target/arm/cpu.h                       |   4 +
 target/arm/helper.c                    |   2 +-
 target/arm/internals.h                 |   5 +-
 target/arm/kvm64.c                     |  73 ++++++
 target/arm/tlb_helper.c                |   2 +-
 target/i386/cpu.h                      |   2 +
 target/i386/kvm.c                      |  36 ---
 27 files changed, 854 insertions(+), 48 deletions(-)
 create mode 100644 docs/specs/acpi_hest_ghes.rst
 create mode 100644 hw/acpi/ghes.c
 create mode 100644 include/hw/acpi/ghes.h
```
#### [PATCH 0/2] example changes
##### From: Christian Borntraeger <borntraeger@de.ibm.com>

```c
From patchwork Mon Feb 17 14:53:00 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Christian Borntraeger <borntraeger@de.ibm.com>
X-Patchwork-Id: 11386571
Return-Path: <SRS0=fZmU=4F=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 7710117E8
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 17 Feb 2020 14:53:09 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 6170420679
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 17 Feb 2020 14:53:09 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729296AbgBQOxI (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 17 Feb 2020 09:53:08 -0500
Received: from mx0a-001b2d01.pphosted.com ([148.163.156.1]:17894 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1728845AbgBQOxI (ORCPT
        <rfc822;kvm@vger.kernel.org>); Mon, 17 Feb 2020 09:53:08 -0500
Received: from pps.filterd (m0098399.ppops.net [127.0.0.1])
        by mx0a-001b2d01.pphosted.com (8.16.0.42/8.16.0.42) with SMTP id
 01HEnsmb037653;
        Mon, 17 Feb 2020 09:53:07 -0500
Received: from pps.reinject (localhost [127.0.0.1])
        by mx0a-001b2d01.pphosted.com with ESMTP id 2y6dp89fug-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Mon, 17 Feb 2020 09:53:07 -0500
Received: from m0098399.ppops.net (m0098399.ppops.net [127.0.0.1])
        by pps.reinject (8.16.0.36/8.16.0.36) with SMTP id 01HEovM0041590;
        Mon, 17 Feb 2020 09:53:06 -0500
Received: from ppma03dal.us.ibm.com (b.bd.3ea9.ip4.static.sl-reverse.com
 [169.62.189.11])
        by mx0a-001b2d01.pphosted.com with ESMTP id 2y6dp89fty-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Mon, 17 Feb 2020 09:53:06 -0500
Received: from pps.filterd (ppma03dal.us.ibm.com [127.0.0.1])
        by ppma03dal.us.ibm.com (8.16.0.27/8.16.0.27) with SMTP id
 01HEpQBa021225;
        Mon, 17 Feb 2020 14:53:05 GMT
Received: from b01cxnp22036.gho.pok.ibm.com (b01cxnp22036.gho.pok.ibm.com
 [9.57.198.26])
        by ppma03dal.us.ibm.com with ESMTP id 2y6896f2uy-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Mon, 17 Feb 2020 14:53:05 +0000
Received: from b01ledav005.gho.pok.ibm.com (b01ledav005.gho.pok.ibm.com
 [9.57.199.110])
        by b01cxnp22036.gho.pok.ibm.com (8.14.9/8.14.9/NCO v10.0) with ESMTP
 id 01HEr3Na34537884
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Mon, 17 Feb 2020 14:53:03 GMT
Received: from b01ledav005.gho.pok.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 8DA0CAE063;
        Mon, 17 Feb 2020 14:53:03 +0000 (GMT)
Received: from b01ledav005.gho.pok.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 75369AE05F;
        Mon, 17 Feb 2020 14:53:03 +0000 (GMT)
Received: from localhost.localdomain (unknown [9.114.17.106])
        by b01ledav005.gho.pok.ibm.com (Postfix) with ESMTP;
        Mon, 17 Feb 2020 14:53:03 +0000 (GMT)
From: Christian Borntraeger <borntraeger@de.ibm.com>
To: david@redhat.com
Cc: Ulrich.Weigand@de.ibm.com, borntraeger@de.ibm.com,
        cohuck@redhat.com, frankja@linux.ibm.com,
        frankja@linux.vnet.ibm.com, gor@linux.ibm.com,
        imbrenda@linux.ibm.com, kvm@vger.kernel.org,
        linux-s390@vger.kernel.org, mimu@linux.ibm.com, thuth@redhat.com
Subject: [PATCH 0/2] example changes
Date: Mon, 17 Feb 2020 09:53:00 -0500
Message-Id: <20200217145302.19085-1-borntraeger@de.ibm.com>
X-Mailer: git-send-email 2.25.0
In-Reply-To: <c77dbb1b-0f4b-e40a-52a4-7110aec75e32@redhat.com>
References: <c77dbb1b-0f4b-e40a-52a4-7110aec75e32@redhat.com>
MIME-Version: 1.0
X-TM-AS-GCONF: 00
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.138,18.0.572
 definitions=2020-02-17_08:2020-02-17,2020-02-17 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 malwarescore=0 phishscore=0
 mlxlogscore=577 suspectscore=1 adultscore=0 bulkscore=0 impostorscore=0
 clxscore=1015 spamscore=0 priorityscore=1501 mlxscore=0 lowpriorityscore=0
 classifier=spam adjust=0 reason=mlx scancount=1 engine=8.12.0-2001150001
 definitions=main-2002170123
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

I also need to rename the ioctls and do more testing,
but this is probably what you want?

Christian Borntraeger (2):
  lock changes
  merge vm/cpu create

 arch/s390/kvm/intercept.c |  6 +--
 arch/s390/kvm/interrupt.c | 35 ++++++++++-------
 arch/s390/kvm/kvm-s390.c  | 83 +++++++++++++++++++++++++--------------
 arch/s390/kvm/kvm-s390.h  | 18 ++++++---
 arch/s390/kvm/priv.c      |  4 +-
 5 files changed, 92 insertions(+), 54 deletions(-)
```
#### [PATCH 0/2] KVM: arm/arm64: Fixes for scheudling htimer of emulated
##### From: Tomasz Nowicki <tnowicki@marvell.com>

```c
From patchwork Mon Feb 17 14:54:36 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Tomasz Nowicki <tnowicki@marvell.com>
X-Patchwork-Id: 11386575
Return-Path: <SRS0=fZmU=4F=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id A3578924
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 17 Feb 2020 14:55:32 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 7793F20679
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 17 Feb 2020 14:55:32 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=marvell.com header.i=@marvell.com
 header.b="ZileLVsU";
	dkim=pass (1024-bit key) header.d=marvell.onmicrosoft.com
 header.i=@marvell.onmicrosoft.com header.b="IjsF9ubg"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729222AbgBQOzb (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 17 Feb 2020 09:55:31 -0500
Received: from mx0b-0016f401.pphosted.com ([67.231.156.173]:24496 "EHLO
        mx0b-0016f401.pphosted.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1728493AbgBQOzb (ORCPT
        <rfc822;kvm@vger.kernel.org>); Mon, 17 Feb 2020 09:55:31 -0500
Received: from pps.filterd (m0045851.ppops.net [127.0.0.1])
        by mx0b-0016f401.pphosted.com (8.16.0.42/8.16.0.42) with SMTP id
 01HEj2rm001185;
        Mon, 17 Feb 2020 06:55:22 -0800
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=marvell.com;
 h=from : to : cc :
 subject : date : message-id : content-type : mime-version; s=pfpt0818;
 bh=Icm/nTLE7WM0LljVbU4iGYBVV7o0LT/PgTM9tV5xYIc=;
 b=ZileLVsU3LFp/brwQNIHi8YN25LwIiXcBaULLzI2D0TQVCDFV3AtxPbs3a4YrZfcttLF
 T+cwBdviH0Ya+TFdA2DgeBF/R3XZmT6X1TK3D4zVuYeClpsH/QniT42Hd8aUDOppmbIq
 yvE4gubOpyGCl/Ym2QWwa2I3l9Wn5zbmtKZErPlbmyMva6m1hEUPj71HWJeMBP/owSUm
 1qtV8bA0W0RyVTaxGiLuag2VMYk7A1KjVp5xoK1m5hN8JCqHde710D5xBzZoVx2721o8
 +eWehVqNaSpsyPbhD/u1YBeKuh1VveBOQH8BU5TBCq0oTv+TO7epALBYEAN1ZZ8JyMmn SA==
Received: from sc-exch01.marvell.com ([199.233.58.181])
        by mx0b-0016f401.pphosted.com with ESMTP id 2y6h1sychh-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-SHA384 bits=256 verify=NOT);
        Mon, 17 Feb 2020 06:55:21 -0800
Received: from SC-EXCH01.marvell.com (10.93.176.81) by SC-EXCH01.marvell.com
 (10.93.176.81) with Microsoft SMTP Server (TLS) id 15.0.1497.2; Mon, 17 Feb
 2020 06:55:20 -0800
Received: from NAM11-BN8-obe.outbound.protection.outlook.com (104.47.58.174)
 by SC-EXCH01.marvell.com (10.93.176.81) with Microsoft SMTP Server (TLS) id
 15.0.1497.2 via Frontend Transport; Mon, 17 Feb 2020 06:55:20 -0800
ARC-Seal: i=1; a=rsa-sha256; s=arcselector9901; d=microsoft.com; cv=none;
 b=YXCCqiymTE2mWGVmLTBKGggd4GmTnQTHX+HKzmJWyaj7V1kyjBqGs/kaOEPbqu79sGJG6EEHGXiIP3zu3oGR8GMwYxy/xd8VSLox/SnDI8KS2KCT2TIt0kMgg4VxplCpiw3rXgbHPnBFNMI7t8WUdG3cPP/C2WLwvYaZQT7BH4tiT+8rR4h4ixZBjrO5QWo8aFdnHYOX46zPEmqPwDm+rq8nydYrC44vkdHSUB/7xKHDlTc6ZvkyrlxjF1BJ0UIlmSFZNhI++ePwH+hpeFyAEbu6vLQEIlQvI3NvNVvQnq/zbDNRHMSTmWvzDqXqyL2BIX6D6JTx/vmX8d+Bsb6gSQ==
ARC-Message-Signature: i=1; a=rsa-sha256; c=relaxed/relaxed; d=microsoft.com;
 s=arcselector9901;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=Icm/nTLE7WM0LljVbU4iGYBVV7o0LT/PgTM9tV5xYIc=;
 b=L8UZn+snPxCpz20CXew8RZeAabkBUEXatVtmj5Ttw5YycIwIxI7w4aBCSvX120OruEBlJg5hDZ2LMxFR0ArTjRwmVguYzWoreHg7IXyzfi6FzGryRKTvhGgMWKoGOdhHb9TbrJ2RpVsUPHcV/Xyz0nf7Og7rIJITJ8JB5QfmZcCnuN4yBA836wQxqpJChVkpbc/K+hiIzNOG714tsMJA7UpTdG2E3nReiheaLJatJYPVW1sODlq0PVqbRauiqFbqplX3Wac7iWHaKFA4eJntHkiG7Sdw/afGEW4O25QmjWTYE9bcysJGl9nE5WKPokhsR8g/YkVIbxNnKcC7zpYtJA==
ARC-Authentication-Results: i=1; mx.microsoft.com 1; spf=pass
 smtp.mailfrom=marvell.com; dmarc=pass action=none header.from=marvell.com;
 dkim=pass header.d=marvell.com; arc=none
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
 d=marvell.onmicrosoft.com; s=selector1-marvell-onmicrosoft-com;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=Icm/nTLE7WM0LljVbU4iGYBVV7o0LT/PgTM9tV5xYIc=;
 b=IjsF9ubgHAauezKwTnvg8Au1kXP/nqyaW6+Ixn7MWU0OzsV4+ZHE3y259YGp06LBn5bM1NeWUPSaawvZ51dOYPg3a9KQivCz3RtjFOZTpfe4Au6rzwG/iktKD9kbwXI2A1LriOUsEwJdoPInm0JLteYNXKiheurqKRsbttL+YSA=
Received: from DM6PR18MB2969.namprd18.prod.outlook.com (20.179.52.17) by
 DM6SPR01MB0045.namprd18.prod.outlook.com (20.176.120.140) with Microsoft SMTP
 Server (version=TLS1_2, cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id
 15.20.2729.22; Mon, 17 Feb 2020 14:55:17 +0000
Received: from DM6PR18MB2969.namprd18.prod.outlook.com
 ([fe80::d890:b3b7:629e:352c]) by DM6PR18MB2969.namprd18.prod.outlook.com
 ([fe80::d890:b3b7:629e:352c%6]) with mapi id 15.20.2729.031; Mon, 17 Feb 2020
 14:55:17 +0000
From: Tomasz Nowicki <tnowicki@marvell.com>
To: <kvmarm@lists.cs.columbia.edu>,
        <linux-arm-kernel@lists.infradead.org>
CC: <kvm@vger.kernel.org>, <christoffer.dall@arm.com>,
        <maz@kernel.org>, <james.morse@arm.com>,
        <julien.thierry.kdev@gmail.com>, <gkulkarni@marvell.com>,
        <rrichter@marvell.com>, Tomasz Nowicki <tnowicki@marvell.com>
Subject: [PATCH 0/2] KVM: arm/arm64: Fixes for scheudling htimer of emulated
 timers
Date: Mon, 17 Feb 2020 15:54:36 +0100
Message-ID: <20200217145438.23289-1-tnowicki@marvell.com>
X-Mailer: git-send-email 2.17.1
X-ClientProxiedBy: AM6P192CA0037.EURP192.PROD.OUTLOOK.COM
 (2603:10a6:209:82::14) To DM6PR18MB2969.namprd18.prod.outlook.com
 (2603:10b6:5:170::17)
MIME-Version: 1.0
Received: from localhost.localdomain (83.68.95.66) by
 AM6P192CA0037.EURP192.PROD.OUTLOOK.COM (2603:10a6:209:82::14) with Microsoft
 SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.2729.22 via Frontend
 Transport; Mon, 17 Feb 2020 14:55:15 +0000
X-Mailer: git-send-email 2.17.1
X-Originating-IP: [83.68.95.66]
X-MS-PublicTrafficType: Email
X-MS-Office365-Filtering-Correlation-Id: 04e52687-9463-476c-06c6-08d7b3b966b6
X-MS-TrafficTypeDiagnostic: DM6SPR01MB0045:
X-MS-Exchange-Transport-Forked: True
X-Microsoft-Antispam-PRVS: 
 <DM6SPR01MB004550F7C86687D575DB5CFFD2160@DM6SPR01MB0045.namprd18.prod.outlook.com>
X-MS-Oob-TLC-OOBClassifiers: OLM:7691;
X-Forefront-PRVS: 0316567485
X-Forefront-Antispam-Report: 
 SFV:NSPM;SFS:(10009020)(4636009)(136003)(39850400004)(366004)(376002)(346002)(396003)(189003)(199004)(69590400006)(4326008)(5660300002)(36756003)(26005)(4744005)(107886003)(478600001)(2906002)(16526019)(186003)(8936002)(52116002)(2616005)(81156014)(8676002)(81166006)(316002)(6666004)(6486002)(86362001)(956004)(66946007)(6512007)(1076003)(6506007)(66476007)(66556008);DIR:OUT;SFP:1101;SCL:1;SRVR:DM6SPR01MB0045;H:DM6PR18MB2969.namprd18.prod.outlook.com;FPR:;SPF:None;LANG:en;PTR:InfoNoRecords;MX:1;A:1;
Received-SPF: None (protection.outlook.com: marvell.com does not designate
 permitted sender hosts)
X-MS-Exchange-SenderADCheck: 1
X-Microsoft-Antispam: BCL:0;
X-Microsoft-Antispam-Message-Info: 
 4t615iIS5SXyqr+yOko5ESnzoah7X7Q0EKPk2mx3XFMocAbdRRgYs5z9J4WI2AcwvNb+8Hndyb+UBw5UD2QnHsTVHVz09OHXhgF4QV9X6WGTf6vb+lPIS0gkUdPVaS4kacmoX0SWl9Xsik236YALeQ+XStlXZCDTdk3hXhYBuV/iLxuo4AoBFWmWJHz/7vJxf1C/+9S6qspPhKwVLgsmPm87DLQhYWWRiSMTKaqm0p+Ya9ZLi9oEJliz2ielxhC7T+4isgtrqy2GFfm4VenRJc/5qr75CDsyUWCWNAhSalqF1hSKYVXbPjvO+gLC5rexdilyAQyTo2r4mjUm8le4yQtoSe3aW9RmCRZ4snfcmOtRc9RBBsvQm/vkpdMAmDnImInqlqaGGtp9I0J9SuPD7cBepTVpnaAkDRskBkx4EXHuv8onz8vjGnGtepScabplLq8A0dOgnDupROmelwaItZjA7pQyGYZQklW0t1owtSXE5pu6/RpxuHGNH80hlYPTUBirZq8og2zv0YyLQBeBWHq+kL0ufpQ3g0gN9I0UDg8=
X-MS-Exchange-AntiSpam-MessageData: 
 AxAZvssiNDQ9t8tljH0Kq9nooKPKgUUvX/O8jiW1Rh87JlH5zIFAsqgkSbZidYYFXLUvbax4CNtzOS6S4+L6jSRUd5KvxZ4ST9eGtrg69xggmNplQUf/74x8H5/rRiPA3+luYU2v1qKuOylq5v1Vyw==
X-MS-Exchange-CrossTenant-Network-Message-Id: 
 04e52687-9463-476c-06c6-08d7b3b966b6
X-MS-Exchange-CrossTenant-OriginalArrivalTime: 17 Feb 2020 14:55:17.2270
 (UTC)
X-MS-Exchange-CrossTenant-FromEntityHeader: Hosted
X-MS-Exchange-CrossTenant-Id: 70e1fb47-1155-421d-87fc-2e58f638b6e0
X-MS-Exchange-CrossTenant-MailboxType: HOSTED
X-MS-Exchange-CrossTenant-UserPrincipalName: 
 gKSdOS1P3gnDf+Famcd/M91iPn6eHAFZEu7WpZFUVxjrqdnMb5ciyO+kMOhSa0L68Sc9Z7epURX/6V3K9+kJWQ==
X-MS-Exchange-Transport-CrossTenantHeadersStamped: DM6SPR01MB0045
X-OriginatorOrg: marvell.com
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.138,18.0.572
 definitions=2020-02-17_08:2020-02-17,2020-02-17 signatures=0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This small series contains two fixes which were found while testing
Marc's ARM NV patch set, where we are going to have at most 4 timers
and the two are purely emulated.

First patch cancels hrtimer when the timer should fire and there is no
change in irq line level which suppresses timer interrupt storm when
guest enables interrupts.

Second patch makes sure that hrtimer is scheduled when timer irq line
goes down and there is still some time to expire.

Tomasz Nowicki (2):
  KVM: arm/arm64: Fix spurious htimer setup for emulated timer
  KVM: arm/arm64: Fix htimer setup for emulated timer when irq goes down

 virt/kvm/arm/arch_timer.c | 6 ++----
 1 file changed, 2 insertions(+), 4 deletions(-)
```
