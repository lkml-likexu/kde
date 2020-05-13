

#### [PATCH v27 00/10] Add ARMv8 RAS virtualization support in QEMU
##### From: Dongjiu Geng <gengdongjiu@huawei.com>

```c
From patchwork Tue May 12 03:05:59 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Dongjiu Geng <gengdongjiu@huawei.com>
X-Patchwork-Id: 11541967
Return-Path: <SRS0=B8Dm=62=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 213C692A
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 12 May 2020 03:03:16 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 0F96D206D7
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 12 May 2020 03:03:16 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728632AbgELDDP (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 11 May 2020 23:03:15 -0400
Received: from szxga06-in.huawei.com ([45.249.212.32]:51668 "EHLO huawei.com"
        rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org with ESMTP
        id S1728115AbgELDDP (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 11 May 2020 23:03:15 -0400
Received: from DGGEMS413-HUB.china.huawei.com (unknown [172.30.72.60])
        by Forcepoint Email with ESMTP id 87F1E43E5DC3C5D1A88F;
        Tue, 12 May 2020 11:03:11 +0800 (CST)
Received: from huawei.com (10.151.151.243) by DGGEMS413-HUB.china.huawei.com
 (10.3.19.213) with Microsoft SMTP Server id 14.3.487.0; Tue, 12 May 2020
 11:03:03 +0800
From: Dongjiu Geng <gengdongjiu@huawei.com>
To: <imammedo@redhat.com>, <mst@redhat.com>,
        <xiaoguangrong.eric@gmail.com>, <peter.maydell@linaro.org>,
        <shannon.zhaosl@gmail.com>, <fam@euphon.net>, <rth@twiddle.net>,
        <ehabkost@redhat.com>, <mtosatti@redhat.com>,
        <qemu-devel@nongnu.org>, <kvm@vger.kernel.org>,
        <qemu-arm@nongnu.org>, <pbonzini@redhat.com>, <philmd@redhat.com>
CC: <gengdongjiu@huawei.com>, <zhengxiang9@huawei.com>,
        <Jonathan.Cameron@huawei.com>, <linuxarm@huawei.com>
Subject: [PATCH v27 00/10] Add ARMv8 RAS virtualization support in QEMU
Date: Tue, 12 May 2020 11:05:59 +0800
Message-ID: <20200512030609.19593-1-gengdongjiu@huawei.com>
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
#### [PATCH V4 00/14] KVM: MIPS: Add Loongson-3 support (Host Side)
##### From: Huacai Chen <chenhc@lemote.com>

```c
From patchwork Tue May 12 10:29:57 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Huacai Chen <chenhc@lemote.com>
X-Patchwork-Id: 11542837
Return-Path: <SRS0=B8Dm=62=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 4378E139F
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 12 May 2020 10:30:02 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 1A1A120722
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 12 May 2020 10:30:02 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=fail reason="signature verification failed" (2048-bit key)
 header.d=gmail.com header.i=@gmail.com header.b="NHgvoVjE"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729336AbgELKaB (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 12 May 2020 06:30:01 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:57218 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-FAIL-OK-FAIL)
        by vger.kernel.org with ESMTP id S1726193AbgELKaA (ORCPT
        <rfc822;kvm@vger.kernel.org>); Tue, 12 May 2020 06:30:00 -0400
Received: from mail-pj1-x1041.google.com (mail-pj1-x1041.google.com
 [IPv6:2607:f8b0:4864:20::1041])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id EE8B7C061A0C;
        Tue, 12 May 2020 03:29:59 -0700 (PDT)
Received: by mail-pj1-x1041.google.com with SMTP id t40so9163095pjb.3;
        Tue, 12 May 2020 03:29:59 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=sender:from:to:cc:subject:date:message-id;
        bh=mtUuXVwQma+6PI2bLTE3Br0qYTSiabzt8TWgTvym4EQ=;
        b=NHgvoVjEo8SsVplbPh8TTFnE09GZ0iJB9NtjF7ZDELCcKpjzEuUeseGnw5PRE1S9OV
         zeOFV+YRNkVbpHn6QzUNEXNz/We0xq9FFJgBwNTbRTeN5qU03md0dHdlirPTlJHPLxfO
         Pwo62Gn4GRKlmDVDw6tiB4xGT58hIuqpfVYm9bWieoBhJ1LpvHryXTX2/+veHN4SBKa2
         QBZWKTyxeXASl+Zwb0HbV8IZ9OIbdoUSg/GQY1h3gNGx+cy/2Z7ZSIQ2drnjJK53EL/g
         mtXbSm7Fw0RLQjTIQPikUzrqfY2jSLeyNTMac09Dr+f8FMTpmGyadMVDLNzoyGZg23OR
         xQRQ==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:sender:from:to:cc:subject:date:message-id;
        bh=mtUuXVwQma+6PI2bLTE3Br0qYTSiabzt8TWgTvym4EQ=;
        b=NQtBoWeemImgd/iFNMII7e5bITliaqN3YLEVUZevAx6BewYB8t09HwtVU5fVMDFTt7
         +fDt7YjsBxwVHczvAPMRLT6D2UKtytB8qvPKvWHtGT2WNvjEfY9hzxc7UmpRZn51ruZP
         eYUknb+BkbFD+PHO2Jsap4MBuQKWS113fGWtPv3mHjWEJDkj1ml0LBIqlOSms0lKbJVR
         wbvBipY1CJO3zur64aGP5GGeWQc+4NkqKGwE110KjFaLzRUyuiyrb9MwlxqjeDqz6C9W
         6qsuIGLYvj5EHBZlxby0TrjgqzSSwBzSAJwUGXAoN+iIkHKYA4Bc2qsoBcTLBjLoFPsk
         K5Pg==
X-Gm-Message-State: AGi0PuZjlc6Y7MLQ5wJXz11eG5dUIAMyEEcCagiVsOrkLavxr/ATIsvf
        lVYposYyiJoc6tPRc2dPFRU=
X-Google-Smtp-Source: 
 APiQypLz17pbTJ74ITq/0VOlVlPZ0mdiDP1MRZugjfxVbtqtOWQKvDG2DwRbR4bdzYATsWb0mBarEg==
X-Received: by 2002:a17:90a:8c3:: with SMTP id
 3mr27932241pjn.147.1589279399438;
        Tue, 12 May 2020 03:29:59 -0700 (PDT)
Received: from software.domain.org (28.144.92.34.bc.googleusercontent.com.
 [34.92.144.28])
        by smtp.gmail.com with ESMTPSA id
 z6sm11485660pfb.87.2020.05.12.03.29.56
        (version=TLS1_2 cipher=ECDHE-ECDSA-AES128-GCM-SHA256 bits=128/128);
        Tue, 12 May 2020 03:29:58 -0700 (PDT)
From: Huacai Chen <chenhc@lemote.com>
To: Paolo Bonzini <pbonzini@redhat.com>,
        Thomas Bogendoerfer <tsbogend@alpha.franken.de>,
        Aleksandar Markovic <aleksandar.qemu.devel@gmail.com>
Cc: kvm@vger.kernel.org, linux-mips@vger.kernel.org,
        Fuxin Zhang <zhangfx@lemote.com>,
        Huacai Chen <chenhuacai@gmail.com>,
        Jiaxun Yang <jiaxun.yang@flygoat.com>,
        Huacai Chen <chenhc@lemote.com>
Subject: [PATCH V4 00/14] KVM: MIPS: Add Loongson-3 support (Host Side)
Date: Tue, 12 May 2020 18:29:57 +0800
Message-Id: <1589279411-27643-1-git-send-email-chenhc@lemote.com>
X-Mailer: git-send-email 2.7.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

We are preparing to add KVM support for Loongson-3. VZ extension is
fully supported in Loongson-3A R4+, and we will not care about old CPUs
(at least now). We already have a full functional Linux kernel (based
on Linux-5.4.x LTS) and QEMU (based on 5.0.0-rc2) and their git
repositories are here:

QEMU: https://github.com/chenhuacai/qemu
Kernel: https://github.com/chenhuacai/linux

Of course these two repositories need to be rework and not suitable for
upstream (especially the commits need to be splitted). We show them here
is just to tell others what we have done, and how KVM/Loongson will look
like.

Our plan is make the KVM host side be upstream first, and after that,
we will make the KVM guest side and QEMU emulator be upstream.

V1 -> V2:
1, Remove "mips: define pud_index() regardless of page table folding"
   because it has been applied.
2, Make Loongson-specific code be guarded by CONFIG_CPU_LOONGSON64.

V2 -> V3:
1, Emulate a reduced feature list of CPUCFG.
2, Fix all possible checkpatch.pl errors and warnings.

V3 -> V4:
1, Emulate LOONGSON_CFG0/LOONGSON_CFG3 in CPUCFG correctly.
2, Update commit messages to explain Loongson-3 Virtual IPI.
3, Add Reviewed-by: Aleksandar Markovic <aleksandar.qemu.devel@gmail.com>.

Xing Li(2):
 KVM: MIPS: Define KVM_ENTRYHI_ASID to cpu_asid_mask(&boot_cpu_data)
 KVM: MIPS: Fix VPN2_MASK definition for variable cpu_vmbits

Huacai Chen(12):
 KVM: MIPS: Increase KVM_MAX_VCPUS and KVM_USER_MEM_SLOTS to 16
 KVM: MIPS: Add EVENTFD support which is needed by VHOST
 KVM: MIPS: Use lddir/ldpte instructions to lookup gpa_mm.pgd
 KVM: MIPS: Introduce and use cpu_guest_has_ldpte
 KVM: MIPS: Use root tlb to control guest's CCA for Loongson-3
 KVM: MIPS: Let indexed cacheops cause guest exit on Loongson-3
 KVM: MIPS: Add more types of virtual interrupts
 KVM: MIPS: Add Loongson-3 Virtual IPI interrupt support
 KVM: MIPS: Add CPUCFG emulation for Loongson-3
 KVM: MIPS: Add CONFIG6 and DIAG registers emulation
 KVM: MIPS: Add more MMIO load/store instructions emulation
 KVM: MIPS: Enable KVM support for Loongson-3

Signed-off-by: Huacai Chen <chenhc@lemote.com>
---
 arch/mips/Kconfig                    |   1 +
 arch/mips/include/asm/cpu-features.h |   3 +
 arch/mips/include/asm/kvm_host.h     |  52 +++-
 arch/mips/include/asm/mipsregs.h     |   7 +
 arch/mips/include/uapi/asm/inst.h    |  11 +
 arch/mips/kernel/cpu-probe.c         |   2 +
 arch/mips/kvm/Kconfig                |   1 +
 arch/mips/kvm/Makefile               |   5 +-
 arch/mips/kvm/emulate.c              | 503 ++++++++++++++++++++++++++++++++++-
 arch/mips/kvm/entry.c                |  19 +-
 arch/mips/kvm/interrupt.c            |  93 +------
 arch/mips/kvm/interrupt.h            |  14 +-
 arch/mips/kvm/loongson_ipi.c         | 214 +++++++++++++++
 arch/mips/kvm/mips.c                 |  49 +++-
 arch/mips/kvm/tlb.c                  |  41 +++
 arch/mips/kvm/trap_emul.c            |   3 +
 arch/mips/kvm/vz.c                   | 237 ++++++++++++-----
 17 files changed, 1089 insertions(+), 166 deletions(-)
 create mode 100644 arch/mips/kvm/loongson_ipi.c
--
2.7.0
```
#### [PATCH V4 00/14] KVM: MIPS: Add Loongson-3 support (Host Side)
##### From: Huacai Chen <chenhc@lemote.com>

```c
From patchwork Tue May 12 10:31:06 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Huacai Chen <chenhc@lemote.com>
X-Patchwork-Id: 11542841
Return-Path: <SRS0=B8Dm=62=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 1047315E6
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 12 May 2020 10:31:08 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id EAA2720722
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 12 May 2020 10:31:07 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=fail reason="signature verification failed" (2048-bit key)
 header.d=gmail.com header.i=@gmail.com header.b="dgYPNXV5"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729444AbgELKbH (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 12 May 2020 06:31:07 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:57408 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-FAIL-OK-FAIL)
        by vger.kernel.org with ESMTP id S1729349AbgELKbG (ORCPT
        <rfc822;kvm@vger.kernel.org>); Tue, 12 May 2020 06:31:06 -0400
Received: from mail-pg1-x541.google.com (mail-pg1-x541.google.com
 [IPv6:2607:f8b0:4864:20::541])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id D2CD5C061A0C;
        Tue, 12 May 2020 03:31:06 -0700 (PDT)
Received: by mail-pg1-x541.google.com with SMTP id u5so3349949pgn.5;
        Tue, 12 May 2020 03:31:06 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=sender:from:to:cc:subject:date:message-id;
        bh=mtUuXVwQma+6PI2bLTE3Br0qYTSiabzt8TWgTvym4EQ=;
        b=dgYPNXV5UokCHcJq6XaABDR4pZUQrYEeEqvN9qCio2jrP/JX9nlUHh3A6M7lCC3Hyv
         ZyWahPiqWwvCtOku8qlItu6+Z7RxOPadIft2qe1XXdf4axLQZz/niGARDls4Djw7gvfS
         eIVP8iApQPR52TzW5X23DGyCQ4mwO9IdAMC3wuaGEFUWa6DhFtI6KeKggcOFYBkBEaIn
         rVXyEuNY+x2ZvZfbpLuMglsBlrHBR8LIF+X5k/JfTE6o0/WCHlmJDSmdnm+kJlv0ORJp
         oQuRdOASDEEnUezV86h+Mep4cy1aeWZqtWeptlW1/ihd6tHYWYm5K6Ha55OODA9ewlyQ
         LE9Q==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:sender:from:to:cc:subject:date:message-id;
        bh=mtUuXVwQma+6PI2bLTE3Br0qYTSiabzt8TWgTvym4EQ=;
        b=hbq1YjPQAVKBy0W4TipVUNNjadmaSiDkBtkNd4kKwQRZPxszb/59XlEKbi/3IYRz6N
         Y4xqA23agLhs4I5Te4wTdxX0YsTdsr+QMvvwxOjiy7PF1smSfcLsauP2aisj2hBCeNEF
         IYVEWFlOJAvzc07Aw+YGUJ/RWCvjhadKq6L1JFmGm4k06r56nVtfQBR3WpWaixLZ94F/
         Y/6njZo8dafl/GIUZ28HDcnF+ddJPgjAlWI7R+e5e+Zz4JtGiuDi2rT7MWnjIslFmzva
         7lvIpufz5I53OQyDzedwGUZ5kRASyDsTP3XAdieFBloiEVgoNpY4rFelXuY14pdjtWrz
         Mpbg==
X-Gm-Message-State: AGi0Pua5iazvfMbv18ghkpUkf7yWb465nUoHWV1ek3fM7ZED5f+q2iYV
        XVNrw8K6/RNzt3QbuozbFs4=
X-Google-Smtp-Source: 
 APiQypJ3DPnseVksq94ieBdLBq2qbkjcwRw4e+44mQCPzGPkEx2OG/PAIC/MA9Y4x/8tvMR+aXshfA==
X-Received: by 2002:a63:ed50:: with SMTP id
 m16mr19919796pgk.271.1589279466330;
        Tue, 12 May 2020 03:31:06 -0700 (PDT)
Received: from software.domain.org (28.144.92.34.bc.googleusercontent.com.
 [34.92.144.28])
        by smtp.gmail.com with ESMTPSA id
 q11sm11617094pfl.97.2020.05.12.03.31.03
        (version=TLS1_2 cipher=ECDHE-ECDSA-AES128-GCM-SHA256 bits=128/128);
        Tue, 12 May 2020 03:31:05 -0700 (PDT)
From: Huacai Chen <chenhc@lemote.com>
To: Paolo Bonzini <pbonzini@redhat.com>,
        Thomas Bogendoerfer <tsbogend@alpha.franken.de>,
        Aleksandar Markovic <aleksandar.qemu.devel@gmail.com>
Cc: kvm@vger.kernel.org, linux-mips@vger.kernel.org,
        Fuxin Zhang <zhangfx@lemote.com>,
        Huacai Chen <chenhuacai@gmail.com>,
        Jiaxun Yang <jiaxun.yang@flygoat.com>,
        Huacai Chen <chenhc@lemote.com>
Subject: [PATCH V4 00/14] KVM: MIPS: Add Loongson-3 support (Host Side)
Date: Tue, 12 May 2020 18:31:06 +0800
Message-Id: <1589279480-27722-1-git-send-email-chenhc@lemote.com>
X-Mailer: git-send-email 2.7.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

We are preparing to add KVM support for Loongson-3. VZ extension is
fully supported in Loongson-3A R4+, and we will not care about old CPUs
(at least now). We already have a full functional Linux kernel (based
on Linux-5.4.x LTS) and QEMU (based on 5.0.0-rc2) and their git
repositories are here:

QEMU: https://github.com/chenhuacai/qemu
Kernel: https://github.com/chenhuacai/linux

Of course these two repositories need to be rework and not suitable for
upstream (especially the commits need to be splitted). We show them here
is just to tell others what we have done, and how KVM/Loongson will look
like.

Our plan is make the KVM host side be upstream first, and after that,
we will make the KVM guest side and QEMU emulator be upstream.

V1 -> V2:
1, Remove "mips: define pud_index() regardless of page table folding"
   because it has been applied.
2, Make Loongson-specific code be guarded by CONFIG_CPU_LOONGSON64.

V2 -> V3:
1, Emulate a reduced feature list of CPUCFG.
2, Fix all possible checkpatch.pl errors and warnings.

V3 -> V4:
1, Emulate LOONGSON_CFG0/LOONGSON_CFG3 in CPUCFG correctly.
2, Update commit messages to explain Loongson-3 Virtual IPI.
3, Add Reviewed-by: Aleksandar Markovic <aleksandar.qemu.devel@gmail.com>.

Xing Li(2):
 KVM: MIPS: Define KVM_ENTRYHI_ASID to cpu_asid_mask(&boot_cpu_data)
 KVM: MIPS: Fix VPN2_MASK definition for variable cpu_vmbits

Huacai Chen(12):
 KVM: MIPS: Increase KVM_MAX_VCPUS and KVM_USER_MEM_SLOTS to 16
 KVM: MIPS: Add EVENTFD support which is needed by VHOST
 KVM: MIPS: Use lddir/ldpte instructions to lookup gpa_mm.pgd
 KVM: MIPS: Introduce and use cpu_guest_has_ldpte
 KVM: MIPS: Use root tlb to control guest's CCA for Loongson-3
 KVM: MIPS: Let indexed cacheops cause guest exit on Loongson-3
 KVM: MIPS: Add more types of virtual interrupts
 KVM: MIPS: Add Loongson-3 Virtual IPI interrupt support
 KVM: MIPS: Add CPUCFG emulation for Loongson-3
 KVM: MIPS: Add CONFIG6 and DIAG registers emulation
 KVM: MIPS: Add more MMIO load/store instructions emulation
 KVM: MIPS: Enable KVM support for Loongson-3

Signed-off-by: Huacai Chen <chenhc@lemote.com>
---
 arch/mips/Kconfig                    |   1 +
 arch/mips/include/asm/cpu-features.h |   3 +
 arch/mips/include/asm/kvm_host.h     |  52 +++-
 arch/mips/include/asm/mipsregs.h     |   7 +
 arch/mips/include/uapi/asm/inst.h    |  11 +
 arch/mips/kernel/cpu-probe.c         |   2 +
 arch/mips/kvm/Kconfig                |   1 +
 arch/mips/kvm/Makefile               |   5 +-
 arch/mips/kvm/emulate.c              | 503 ++++++++++++++++++++++++++++++++++-
 arch/mips/kvm/entry.c                |  19 +-
 arch/mips/kvm/interrupt.c            |  93 +------
 arch/mips/kvm/interrupt.h            |  14 +-
 arch/mips/kvm/loongson_ipi.c         | 214 +++++++++++++++
 arch/mips/kvm/mips.c                 |  49 +++-
 arch/mips/kvm/tlb.c                  |  41 +++
 arch/mips/kvm/trap_emul.c            |   3 +
 arch/mips/kvm/vz.c                   | 237 ++++++++++++-----
 17 files changed, 1089 insertions(+), 166 deletions(-)
 create mode 100644 arch/mips/kvm/loongson_ipi.c
--
2.7.0
```
#### [PATCH v4 0/6] scripts: More Python fixes
##### From: =?utf-8?q?Philippe_Mathieu-Daud=C3=A9?= <philmd@redhat.com>

```c
From patchwork Tue May 12 10:32:32 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 8bit
X-Patchwork-Submitter: =?utf-8?q?Philippe_Mathieu-Daud=C3=A9?=
 <philmd@redhat.com>
X-Patchwork-Id: 11542871
Return-Path: <SRS0=B8Dm=62=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 1D72881
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 12 May 2020 10:32:46 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 047F120722
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 12 May 2020 10:32:45 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="gkdEYPlj"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729473AbgELKco (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 12 May 2020 06:32:44 -0400
Received: from us-smtp-delivery-1.mimecast.com ([207.211.31.120]:51715 "EHLO
        us-smtp-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org
        with ESMTP id S1726193AbgELKco (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 12 May 2020 06:32:44 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1589279563;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
  content-type:content-type:content-type:
         content-transfer-encoding:content-transfer-encoding;
        bh=D3s9LSGcZEYro7u0ScBs6UfFzzI5QWTXiQteI6q/kVs=;
        b=gkdEYPljLbIXjZB/mHM/jy/VOCCrIIx+EQunKCKmz2TdOSbu8dEL9+AXfQzyXolUrghG0S
        OMybZTnygD1fbsDvdAG4imduq0BQZ2iE1kotqoaYxo95kkDgJCkrzE/EcBxdPv4uBKWIqB
        NpkIQu1P7/1SQorDUMIst6as8hCB5tM=
Received: from mail-wr1-f70.google.com (mail-wr1-f70.google.com
 [209.85.221.70]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-357-_f5wCXaaMPGSQyguSSqBaw-1; Tue, 12 May 2020 06:32:41 -0400
X-MC-Unique: _f5wCXaaMPGSQyguSSqBaw-1
Received: by mail-wr1-f70.google.com with SMTP id g10so6724412wrr.10
        for <kvm@vger.kernel.org>; Tue, 12 May 2020 03:32:41 -0700 (PDT)
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:mime-version
         :content-transfer-encoding;
        bh=D3s9LSGcZEYro7u0ScBs6UfFzzI5QWTXiQteI6q/kVs=;
        b=abYUbWCnqIslqqmg7vqBYEsTzyHpJwWuqU43X26li4H9rqXjoc9sDbOccCdUlu1BSR
         YrYAG9ynGxN0jSWSFw+S0F7J3OuTZ2+OdAsUeCB1SbihPOePAR7YSSVcLGXUqvaVAsz6
         LvtuYZ5RzHlnQgPFpYPTSc6pdz9OFQ7VUVQmeKDD0O7jGWYejLrmTPxj0NDB2AaRd/0e
         JrRicIndewGF85cFcv1o2EJ9QqwgMHCP64+RfZggpsMWqA303297gkNQWQiWMhKTYWpE
         lhIWOWNfdd/ZxkaFgjG24MocDleiPDvRKkE8WZBILwRtzn92IOzbF5NCBMCckmwzYAC8
         h8EA==
X-Gm-Message-State: AGi0PuYtSi50HsyvivLwT/guFV+jD3WWnb2yuzrOYH+NCVa6u5dvg6hx
        rEB2SrQSAxoo6asGf9Tn/cw8/OrDGEt1WTL3VPxUU3XD0qkPF6aA/5ysnEJDnmB90vilpOZSRt3
        oERfp60+QlulC
X-Received: by 2002:a7b:c4da:: with SMTP id g26mr20748001wmk.3.1589279560327;
        Tue, 12 May 2020 03:32:40 -0700 (PDT)
X-Google-Smtp-Source: 
 APiQypI7UX/2eCYXEuygt24GZ0cIrBaT7G/B+iwW2cYEEuIZJysOnDbHZJBLcIIaLOSrWhvw7mpSHA==
X-Received: by 2002:a7b:c4da:: with SMTP id g26mr20747977wmk.3.1589279560089;
        Tue, 12 May 2020 03:32:40 -0700 (PDT)
Received: from x1w.redhat.com (17.red-88-21-202.staticip.rima-tde.net.
 [88.21.202.17])
        by smtp.gmail.com with ESMTPSA id
 x5sm23249077wro.12.2020.05.12.03.32.38
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Tue, 12 May 2020 03:32:39 -0700 (PDT)
From: =?utf-8?q?Philippe_Mathieu-Daud=C3=A9?= <philmd@redhat.com>
To: qemu-devel@nongnu.org
Cc: Markus Armbruster <armbru@redhat.com>, John Snow <jsnow@redhat.com>,
 Paolo Bonzini <pbonzini@redhat.com>, qemu-block@nongnu.org,
 qemu-trivial@nongnu.org,
 =?utf-8?q?Philippe_Mathieu-Daud=C3=A9?= <philmd@redhat.com>,
 Cleber Rosa <crosa@redhat.com>, kvm@vger.kernel.org,
 Eduardo Habkost <ehabkost@redhat.com>,
 =?utf-8?q?Alex_Benn=C3=A9e?= <alex.bennee@linaro.org>,
 Marcelo Tosatti <mtosatti@redhat.com>, Stefan Hajnoczi <stefanha@redhat.com>,
 Fam Zheng <fam@euphon.net>
Subject: [PATCH v4 0/6] scripts: More Python fixes
Date: Tue, 12 May 2020 12:32:32 +0200
Message-Id: <20200512103238.7078-1-philmd@redhat.com>
X-Mailer: git-send-email 2.21.3
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Trivial Python3 fixes, again...

Since v3:
- Fixed missing scripts/qemugdb/timers.py (kwolf)
- Cover more scripts
- Check for __main__ in few scripts

Since v2:
- Remove patch updating MAINTAINERS

Since v1:
- Added Alex Bennée A-b tags
- Addressed John Snow review comments
  - Use /usr/bin/env
  - Do not modify os.path (dropped last patch)

Philippe Mathieu-Daudé (6):
  scripts/qemugdb: Remove shebang header
  scripts/qemu-gdb: Use Python 3 interpreter
  scripts/qmp: Use Python 3 interpreter
  scripts/kvm/vmxcap: Use Python 3 interpreter and add pseudo-main()
  scripts/modules/module_block: Use Python 3 interpreter & add
    pseudo-main
  tests/migration/guestperf: Use Python 3 interpreter

 scripts/kvm/vmxcap                 |  7 ++++---
 scripts/modules/module_block.py    | 31 +++++++++++++++---------------
 scripts/qemu-gdb.py                |  4 ++--
 scripts/qemugdb/__init__.py        |  3 +--
 scripts/qemugdb/aio.py             |  3 +--
 scripts/qemugdb/coroutine.py       |  3 +--
 scripts/qemugdb/mtree.py           |  4 +---
 scripts/qemugdb/tcg.py             |  1 -
 scripts/qemugdb/timers.py          |  1 -
 scripts/qmp/qom-get                |  2 +-
 scripts/qmp/qom-list               |  2 +-
 scripts/qmp/qom-set                |  2 +-
 scripts/qmp/qom-tree               |  2 +-
 tests/migration/guestperf-batch.py |  2 +-
 tests/migration/guestperf-plot.py  |  2 +-
 tests/migration/guestperf.py       |  2 +-
 16 files changed, 33 insertions(+), 38 deletions(-)
Reviewed-by: Kevin Wolf <kwolf@redhat.com>
```
