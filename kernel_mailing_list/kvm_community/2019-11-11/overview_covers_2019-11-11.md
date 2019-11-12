

#### [RESEND PATCH v21 0/6] Add ARMv8 RAS virtualization support in QEMU
##### From: Xiang Zheng <zhengxiang9@huawei.com>

```c
From patchwork Mon Nov 11 01:40:42 2019
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Xiang Zheng <zhengxiang9@huawei.com>
X-Patchwork-Id: 11236413
Return-Path: <SRS0=QoBT=ZD=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 7235815AB
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 11 Nov 2019 01:44:29 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 48AED204EC
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 11 Nov 2019 01:44:29 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726878AbfKKBo2 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Sun, 10 Nov 2019 20:44:28 -0500
Received: from szxga07-in.huawei.com ([45.249.212.35]:55650 "EHLO huawei.com"
        rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org with ESMTP
        id S1726743AbfKKBo1 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Sun, 10 Nov 2019 20:44:27 -0500
Received: from DGGEMS403-HUB.china.huawei.com (unknown [172.30.72.59])
        by Forcepoint Email with ESMTP id F2411BF6390E13B54A24;
        Mon, 11 Nov 2019 09:44:20 +0800 (CST)
Received: from HGHY4Z004218071.china.huawei.com (10.133.224.57) by
 DGGEMS403-HUB.china.huawei.com (10.3.19.203) with Microsoft SMTP Server id
 14.3.439.0; Mon, 11 Nov 2019 09:44:13 +0800
From: Xiang Zheng <zhengxiang9@huawei.com>
To: <pbonzini@redhat.com>, <mst@redhat.com>, <imammedo@redhat.com>,
        <shannon.zhaosl@gmail.com>, <peter.maydell@linaro.org>,
        <lersek@redhat.com>, <james.morse@arm.com>,
        <gengdongjiu@huawei.com>, <mtosatti@redhat.com>, <rth@twiddle.net>,
        <ehabkost@redhat.com>, <jonathan.cameron@huawei.com>,
        <xuwei5@huawei.com>, <kvm@vger.kernel.org>,
        <qemu-devel@nongnu.org>, <qemu-arm@nongnu.org>,
        <linuxarm@huawei.com>
CC: <zhengxiang9@huawei.com>, <wanghaibin.wang@huawei.com>
Subject: [RESEND PATCH v21 0/6] Add ARMv8 RAS virtualization support in QEMU
Date: Mon, 11 Nov 2019 09:40:42 +0800
Message-ID: <20191111014048.21296-1-zhengxiang9@huawei.com>
X-Mailer: git-send-email 2.15.1.windows.2
MIME-Version: 1.0
X-Originating-IP: [10.133.224.57]
X-CFilter-Loop: Reflected
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

In the ARMv8 platform, the CPU error types are synchronous external abort(SEA)
and SError Interrupt (SEI). If exception happens in guest, sometimes it's better
for guest to perform the recovery, because host does not know the detailed
information of guest. For example, if an exception happens in a user-space
application within guest, host does not know which application encounters
errors.

For the ARMv8 SEA/SEI, KVM or host kernel delivers SIGBUS to notify userspace.
After user space gets the notification, it will record the CPER into guest GHES
buffer and inject an exception or IRQ into guest.

In the current implementation, if the type of SIGBUS is BUS_MCEERR_AR, we will
treat it as a synchronous exception, and notify guest with ARMv8 SEA
notification type after recording CPER into guest.

This series of patches are based on Qemu 4.1, which include two parts:
1. Generate APEI/GHES table.
2. Handle the SIGBUS signal, record the CPER in runtime and fill it into guest
   memory, then notify guest according to the type of SIGBUS.

The whole solution was suggested by James(james.morse@arm.com); The solution of
APEI section was suggested by Laszlo(lersek@redhat.com).
Show some discussions in [1].

This series of patches have already been tested on ARM64 platform with RAS
feature enabled:
Show the APEI part verification result in [2].
Show the BUS_MCEERR_AR SIGBUS handling verification result in [3].
---
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

Dongjiu Geng (6):
  hw/arm/virt: Introduce a RAS machine option
  docs: APEI GHES generation and CPER record description
  ACPI: Add APEI GHES table generation support
  KVM: Move hwpoison page related functions into kvm-all.c
  target-arm: kvm64: handle SIGBUS signal from kernel or KVM
  MAINTAINERS: Add APCI/APEI/GHES entries

 MAINTAINERS                     |   9 +
 accel/kvm/kvm-all.c             |  36 ++
 default-configs/arm-softmmu.mak |   1 +
 docs/specs/acpi_hest_ghes.rst   |  95 ++++++
 docs/specs/index.rst            |   1 +
 hw/acpi/Kconfig                 |   4 +
 hw/acpi/Makefile.objs           |   1 +
 hw/acpi/acpi_ghes.c             | 564 ++++++++++++++++++++++++++++++++
 hw/acpi/aml-build.c             |   2 +
 hw/arm/virt-acpi-build.c        |  12 +
 hw/arm/virt.c                   |  23 ++
 include/hw/acpi/acpi_ghes.h     |  60 ++++
 include/hw/acpi/aml-build.h     |   1 +
 include/hw/arm/virt.h           |   1 +
 include/sysemu/kvm.h            |   3 +-
 include/sysemu/kvm_int.h        |  12 +
 target/arm/cpu.h                |   4 +
 target/arm/helper.c             |   2 +-
 target/arm/internals.h          |   5 +-
 target/arm/kvm64.c              |  64 ++++
 target/arm/tlb_helper.c         |   2 +-
 target/i386/cpu.h               |   2 +
 target/i386/kvm.c               |  36 --
 23 files changed, 898 insertions(+), 42 deletions(-)
 create mode 100644 docs/specs/acpi_hest_ghes.rst
 create mode 100644 hw/acpi/acpi_ghes.c
 create mode 100644 include/hw/acpi/acpi_ghes.h
```
#### [PATCH 0/2]  KVM: x86: Fix userspace API regarding latched init
##### From: Liran Alon <liran.alon@oracle.com>

```c
From patchwork Mon Nov 11 09:16:38 2019
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Liran Alon <liran.alon@oracle.com>
X-Patchwork-Id: 11236717
Return-Path: <SRS0=QoBT=ZD=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id A3D071709
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 11 Nov 2019 09:17:09 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 81BE420818
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 11 Nov 2019 09:17:09 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=oracle.com header.i=@oracle.com
 header.b="cPX4W/3W"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726973AbfKKJRI (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 11 Nov 2019 04:17:08 -0500
Received: from userp2130.oracle.com ([156.151.31.86]:49692 "EHLO
        userp2130.oracle.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726768AbfKKJRI (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 11 Nov 2019 04:17:08 -0500
Received: from pps.filterd (userp2130.oracle.com [127.0.0.1])
        by userp2130.oracle.com (8.16.0.27/8.16.0.27) with SMTP id
 xAB9EKQd066873;
        Mon, 11 Nov 2019 09:17:01 GMT
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=oracle.com;
 h=from : to : cc :
 subject : date : message-id : mime-version : content-transfer-encoding;
 s=corp-2019-08-05; bh=03zTnro/aWw9SqBuIjuhI8TAe/31sLbeZimtP650p0c=;
 b=cPX4W/3W/cToXmXNYXm9VOxP3ahgWMAQ1s1RGewFcfBWNYhg4N7A7xByUCjzzs5cfrVL
 +AnrJbkKtHWO35vjX6295fZY6eMSmMN/rA8FAIJs0jlkG5ECe8FWWAKfILksVOpRCKUN
 e/4Euy22idfY64Xwsy8BS4ATXnycEY51vrGKZMZFzVnm74+Mls1pl8jyjnIe8Gzrud58
 3nmJlnDfdtIJjAGaMoSL3ehixSVFrZo0uwwLtisV2fSa3UH8e1z+RSYY5Qx4F96LJcQG
 Ug5fvbfPFPZB6cl1pRdSE5lD0OSy3TAmyWZBjgEUxZt2aCjs6iZYY8+xB7v8TKqWD49s PA==
Received: from aserp3030.oracle.com (aserp3030.oracle.com [141.146.126.71])
        by userp2130.oracle.com with ESMTP id 2w5mvtdtd3-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Mon, 11 Nov 2019 09:17:01 +0000
Received: from pps.filterd (aserp3030.oracle.com [127.0.0.1])
        by aserp3030.oracle.com (8.16.0.27/8.16.0.27) with SMTP id
 xAB9Dx7I025793;
        Mon, 11 Nov 2019 09:17:00 GMT
Received: from aserv0122.oracle.com (aserv0122.oracle.com [141.146.126.236])
        by aserp3030.oracle.com with ESMTP id 2w6r8j20jn-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Mon, 11 Nov 2019 09:17:00 +0000
Received: from abhmp0019.oracle.com (abhmp0019.oracle.com [141.146.116.25])
        by aserv0122.oracle.com (8.14.4/8.14.4) with ESMTP id xAB9Gxo6032360;
        Mon, 11 Nov 2019 09:17:00 GMT
Received: from localhost.localdomain (/77.139.185.199)
        by default (Oracle Beehive Gateway v4.0)
        with ESMTP ; Mon, 11 Nov 2019 01:16:59 -0800
From: Liran Alon <liran.alon@oracle.com>
To: pbonzini@redhat.com, rkrcmar@redhat.com, kvm@vger.kernel.org
Cc: sean.j.christopherson@intel.com, jmattson@google.com,
        vkuznets@redhat.com
Subject: [PATCH 0/2]  KVM: x86: Fix userspace API regarding latched init
Date: Mon, 11 Nov 2019 11:16:38 +0200
Message-Id: <20191111091640.92660-1-liran.alon@oracle.com>
X-Mailer: git-send-email 2.20.1
MIME-Version: 1.0
X-Proofpoint-Virus-Version: vendor=nai engine=6000 definitions=9437
 signatures=668685
X-Proofpoint-Spam-Details: rule=notspam policy=default score=0 suspectscore=0
 malwarescore=0
 phishscore=0 bulkscore=0 spamscore=0 mlxscore=0 mlxlogscore=826
 adultscore=0 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.0.1-1910280000 definitions=main-1911110091
X-Proofpoint-Virus-Version: vendor=nai engine=6000 definitions=9437
 signatures=668685
X-Proofpoint-Spam-Details: rule=notspam policy=default score=0
 priorityscore=1501 malwarescore=0
 suspectscore=0 phishscore=0 bulkscore=0 spamscore=0 clxscore=1015
 lowpriorityscore=0 mlxscore=0 impostorscore=0 mlxlogscore=893 adultscore=0
 classifier=spam adjust=0 reason=mlx scancount=1 engine=8.0.1-1910280000
 definitions=main-1911110092
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Hi,
This patch series aims to fix 2 issue in KVM userspace API regarding latched init.

1st patch makes sure that userspace can get/set latched_init state
regardless of if vCPU is in SMM state.

2nd patch prevents userspace from setting vCPU in INIT_RECEIVED/SIPI_RECEIVED
state in case vCPU is in a state that latch INIT signals.

For further information, refer to patches commit messages.

Regards,
-Liran
```
#### [PATCH 0/2] KVM: nVMX: Update vmcs01 TPR_THRESHOLD if L2 changed L1
##### From: Liran Alon <liran.alon@oracle.com>

```c
From patchwork Mon Nov 11 12:30:53 2019
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Liran Alon <liran.alon@oracle.com>
X-Patchwork-Id: 11236917
Return-Path: <SRS0=QoBT=ZD=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id A0EC71515
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 11 Nov 2019 12:31:13 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 7BC932190F
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 11 Nov 2019 12:31:13 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=oracle.com header.i=@oracle.com
 header.b="PInUh7g2"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726893AbfKKMbM (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 11 Nov 2019 07:31:12 -0500
Received: from userp2120.oracle.com ([156.151.31.85]:41868 "EHLO
        userp2120.oracle.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726832AbfKKMbM (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 11 Nov 2019 07:31:12 -0500
Received: from pps.filterd (userp2120.oracle.com [127.0.0.1])
        by userp2120.oracle.com (8.16.0.27/8.16.0.27) with SMTP id
 xABCTHP5001044;
        Mon, 11 Nov 2019 12:31:05 GMT
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=oracle.com;
 h=from : to : cc :
 subject : date : message-id : mime-version : content-transfer-encoding;
 s=corp-2019-08-05; bh=2fAdoIoqJPojVuvgsIc2vvLK2/vDwZuM4WTB/emdJC4=;
 b=PInUh7g2YmhD8ZQ63NdtteNvKNbX7qusnRJUfCNqml1xpKehXeNupYUm52eOr8E9Hp8k
 bYyq2+u/pEED5lKabEHd4i4XYsLNMfoUczsTDbISaC4iS0mzKmOzagi0yWcbyWuoPHAn
 /MMCH/2zFDZBCOAxXg5L9BfWCOwPoxJ57DcaGGeEfrqNuhBifcCYs+/BTdeHqMmz9e2d
 m6NZnDu/IuSjHwtfgfQEkSIriWjnW68nVwjxQx/A+sp5x/Da/I66asLtlHps5hD3D4tf
 BthoLN73cNO7vIiU6MnuwLEDc67wJcD68urx+/Y3HTYY6xDS6QsQv8YYQkPIT73SCwUq nQ==
Received: from userp3020.oracle.com (userp3020.oracle.com [156.151.31.79])
        by userp2120.oracle.com with ESMTP id 2w5p3qenc1-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Mon, 11 Nov 2019 12:31:05 +0000
Received: from pps.filterd (userp3020.oracle.com [127.0.0.1])
        by userp3020.oracle.com (8.16.0.27/8.16.0.27) with SMTP id
 xABCShqk069407;
        Mon, 11 Nov 2019 12:31:04 GMT
Received: from aserv0122.oracle.com (aserv0122.oracle.com [141.146.126.236])
        by userp3020.oracle.com with ESMTP id 2w67kkxfj5-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Mon, 11 Nov 2019 12:31:04 +0000
Received: from abhmp0015.oracle.com (abhmp0015.oracle.com [141.146.116.21])
        by aserv0122.oracle.com (8.14.4/8.14.4) with ESMTP id xABCV3CX019986;
        Mon, 11 Nov 2019 12:31:03 GMT
Received: from Lirans-MBP.Home (/79.182.207.213)
        by default (Oracle Beehive Gateway v4.0)
        with ESMTP ; Mon, 11 Nov 2019 04:31:03 -0800
From: Liran Alon <liran.alon@oracle.com>
To: pbonzini@redhat.com, rkrcmar@redhat.com, kvm@vger.kernel.org
Cc: sean.j.christopherson@intel.com, jmattson@google.com,
        vkuznets@redhat.com
Subject: [PATCH 0/2] KVM: nVMX: Update vmcs01 TPR_THRESHOLD if L2 changed L1
 TPR
Date: Mon, 11 Nov 2019 14:30:53 +0200
Message-Id: <20191111123055.93270-1-liran.alon@oracle.com>
X-Mailer: git-send-email 2.20.1
MIME-Version: 1.0
X-Proofpoint-Virus-Version: vendor=nai engine=6000 definitions=9437
 signatures=668685
X-Proofpoint-Spam-Details: rule=notspam policy=default score=0 suspectscore=0
 malwarescore=0
 phishscore=0 bulkscore=0 spamscore=0 mlxscore=0 mlxlogscore=993
 adultscore=0 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.0.1-1910280000 definitions=main-1911110119
X-Proofpoint-Virus-Version: vendor=nai engine=6000 definitions=9437
 signatures=668685
X-Proofpoint-Spam-Details: rule=notspam policy=default score=0
 priorityscore=1501 malwarescore=0
 suspectscore=0 phishscore=0 bulkscore=0 spamscore=0 clxscore=1015
 lowpriorityscore=0 mlxscore=0 impostorscore=0 mlxlogscore=999 adultscore=0
 classifier=spam adjust=0 reason=mlx scancount=1 engine=8.0.1-1910280000
 definitions=main-1911110119
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Hi,

This patch series aims to fix an issue in nVMX when host use TPR-Threshold (APICv disabled)
and L1 provides to L2 direct access to L1 TPR.

1st patch is just a simple refactoring patch which also simplifies next patch.
2nd is the issue fix. For futher information, see patch commit message.

A kvm-unit-test was written to simulate this issue and will be submitted seperately.

Regards,
-Liran
```
#### [PATCH 0/2] KVM: fix issues with kvm_create_vm failures
##### From: Paolo Bonzini <pbonzini@redhat.com>

```c
From patchwork Mon Nov 11 13:25:39 2019
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Paolo Bonzini <pbonzini@redhat.com>
X-Patchwork-Id: 11236987
Return-Path: <SRS0=QoBT=ZD=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 0E383159A
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 11 Nov 2019 13:25:59 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id D8C1221E6F
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 11 Nov 2019 13:25:58 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=fail reason="signature verification failed" (2048-bit key)
 header.d=gmail.com header.i=@gmail.com header.b="hYC+6N6M"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726924AbfKKNZq (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 11 Nov 2019 08:25:46 -0500
Received: from mail-wr1-f66.google.com ([209.85.221.66]:33847 "EHLO
        mail-wr1-f66.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726832AbfKKNZq (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 11 Nov 2019 08:25:46 -0500
Received: by mail-wr1-f66.google.com with SMTP id e6so14695008wrw.1;
        Mon, 11 Nov 2019 05:25:44 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=sender:from:to:cc:subject:date:message-id;
        bh=u3CoHNh7IQCIJE14gCTOqxD+2t322eDV5uttrHyFEEY=;
        b=hYC+6N6M3p+UrmV46pZp15EqE7ogI53gVUeIQYy5+mSy+6/NjQU8Wd22/93cgbSOX+
         g5r08+bZRKbZQKbh2ZDTJzDQBIC9jYw25vWe3jueG7uTr17CVlC4NApXErk79qe2Vk/t
         NJCQnXHzbEok6QExXsbv38gqrEnNN/pxwqStN+diUypV5+7nhucjXkD39Js4HdMBQdiB
         /k2lWTB+8Bqq8YtJHWeSZSlxliDhDZ3nJe08HUAt02DhJYvBO/HmdyZ/IVJAk52AmGVe
         sbsb9Vs74Ap20wnfTpYxP15LjIErAkEUzWK9YPtK3CnFrhq204CGYltrQzfAaPuTKIKy
         HA2A==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:sender:from:to:cc:subject:date:message-id;
        bh=u3CoHNh7IQCIJE14gCTOqxD+2t322eDV5uttrHyFEEY=;
        b=mzNP6LjSOPnHQnU47PuWDcgFsmF2gPrUlmZuIRUo5g+mfQQ5K6rPqcgfh+S+SeqB5E
         baoc/gUzwR06ERgrEu1n1skmQLKk6nGlHBuZ25PEVUsSu3+qWNXmVMw+0hKWh+ZfaznS
         UnDjAT8iUhfHJAtBhlEetn779Qe20aunFO/GR4zY25zJO9Tj3iW58PKM9ygjVcHQ9Gjq
         MAjtVhw822Jk0EvzThNA6/78Man4Xt5UFH0SE+QBWp7HKN80tEW4+xhCngLBHPBNj6SP
         UusVWWNtg0dEUD4ykZTzs9aan7RP7kEtIGnh9h+ISjPA/xg59dM2la7Qtzear3O4CMbN
         Hiew==
X-Gm-Message-State: APjAAAUUFaeHzzFXsovpTKPHoRDo1sDjfQbB0l1c0d5HDnRRva5XGFml
        NkmRKq6MuOJfOxcsQzdgmkZnEb46
X-Google-Smtp-Source: 
 APXvYqyYD5tlz0OKY7P7QPLnJdMFBRyGMNUxDmoYTOS3E5u1KN9QRFMlpwTiWRH2nTR0/eg7YzoM4Q==
X-Received: by 2002:adf:f547:: with SMTP id j7mr21725532wrp.69.1573478743660;
        Mon, 11 Nov 2019 05:25:43 -0800 (PST)
Received: from 640k.lan ([93.56.166.5])
        by smtp.gmail.com with ESMTPSA id
 p1sm7555131wmc.38.2019.11.11.05.25.42
        (version=TLS1_2 cipher=ECDHE-RSA-AES128-GCM-SHA256 bits=128/128);
        Mon, 11 Nov 2019 05:25:42 -0800 (PST)
From: Paolo Bonzini <pbonzini@redhat.com>
To: linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Cc: jmattson@google.com, wanpengli@tencent.com,
        Junaid Shahid <junaids@google.com>
Subject: [PATCH 0/2] KVM: fix issues with kvm_create_vm failures
Date: Mon, 11 Nov 2019 14:25:39 +0100
Message-Id: <1573478741-30959-1-git-send-email-pbonzini@redhat.com>
X-Mailer: git-send-email 1.8.3.1
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Fix problems with the recent introduction of kvm_arch_destroy_vm
on VM creation failure.  An updated version of the patches already
sent by Wanpeng.

Paolo

Paolo Bonzini (2):
  KVM: Fix NULL-ptr defer after kvm_create_vm fails
  KVM: fix placement of refcount initialization

 virt/kvm/kvm_main.c | 22 +++++++++++-----------
 1 file changed, 11 insertions(+), 11 deletions(-)
```
#### [kvm-unit-tests PATCH v2 0/3] s390x: Improve architectural compliance
##### From: Janosch Frank <frankja@linux.ibm.com>

```c
From patchwork Mon Nov 11 15:33:42 2019
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Janosch Frank <frankja@linux.ibm.com>
X-Patchwork-Id: 11237237
Return-Path: <SRS0=QoBT=ZD=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 775DD1390
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 11 Nov 2019 15:35:26 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 605DF21783
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 11 Nov 2019 15:35:26 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727025AbfKKPfZ (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 11 Nov 2019 10:35:25 -0500
Received: from mx0b-001b2d01.pphosted.com ([148.163.158.5]:44446 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S1726988AbfKKPfZ (ORCPT
        <rfc822;kvm@vger.kernel.org>); Mon, 11 Nov 2019 10:35:25 -0500
Received: from pps.filterd (m0098416.ppops.net [127.0.0.1])
        by mx0b-001b2d01.pphosted.com (8.16.0.27/8.16.0.27) with SMTP id
 xABFVoEm041358
        for <kvm@vger.kernel.org>; Mon, 11 Nov 2019 10:35:24 -0500
Received: from e06smtp02.uk.ibm.com (e06smtp02.uk.ibm.com [195.75.94.98])
        by mx0b-001b2d01.pphosted.com with ESMTP id 2w7a6qrsb0-1
        (version=TLSv1.2 cipher=AES256-GCM-SHA384 bits=256 verify=NOT)
        for <kvm@vger.kernel.org>; Mon, 11 Nov 2019 10:34:06 -0500
Received: from localhost
        by e06smtp02.uk.ibm.com with IBM ESMTP SMTP Gateway: Authorized Use
 Only! Violators will be prosecuted
        for <kvm@vger.kernel.org> from <frankja@linux.ibm.com>;
        Mon, 11 Nov 2019 15:33:55 -0000
Received: from b06cxnps4074.portsmouth.uk.ibm.com (9.149.109.196)
        by e06smtp02.uk.ibm.com (192.168.101.132) with IBM ESMTP SMTP Gateway:
 Authorized Use Only! Violators will be prosecuted;
        (version=TLSv1/SSLv3 cipher=AES256-GCM-SHA384 bits=256/256)
        Mon, 11 Nov 2019 15:33:52 -0000
Received: from d06av21.portsmouth.uk.ibm.com (d06av21.portsmouth.uk.ibm.com
 [9.149.105.232])
        by b06cxnps4074.portsmouth.uk.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id xABFXp6Q49873084
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Mon, 11 Nov 2019 15:33:51 GMT
Received: from d06av21.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 755DF52057;
        Mon, 11 Nov 2019 15:33:51 +0000 (GMT)
Received: from localhost.localdomain (unknown [9.145.179.89])
        by d06av21.portsmouth.uk.ibm.com (Postfix) with ESMTP id 53D235204F;
        Mon, 11 Nov 2019 15:33:50 +0000 (GMT)
From: Janosch Frank <frankja@linux.ibm.com>
To: kvm@vger.kernel.org
Cc: linux-s390@vger.kernel.org, david@redhat.com, thuth@redhat.com
Subject: [kvm-unit-tests PATCH v2 0/3] s390x: Improve architectural compliance
 for diag308
Date: Mon, 11 Nov 2019 10:33:42 -0500
X-Mailer: git-send-email 2.20.1
MIME-Version: 1.0
X-TM-AS-GCONF: 00
x-cbid: 19111115-0008-0000-0000-0000032E10C3
X-IBM-AV-DETECTION: SAVI=unused REMOTE=unused XFE=unused
x-cbparentid: 19111115-0009-0000-0000-00004A4D1193
Message-Id: <20191111153345.22505-1-frankja@linux.ibm.com>
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:,,
 definitions=2019-11-11_05:,,
 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 priorityscore=1501
 malwarescore=0 suspectscore=1 phishscore=0 bulkscore=0 spamscore=0
 clxscore=1015 lowpriorityscore=0 mlxscore=0 impostorscore=0
 mlxlogscore=487 adultscore=0 classifier=spam adjust=0 reason=mlx
 scancount=1 engine=8.0.1-1910280000 definitions=main-1911110142
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

When testing diag308 subcodes 0/1 on lpar with virtual mem set up, I
experienced spec PGMs and addressing PGMs due to the tests not setting
short psw bit 12 and leaving the DAT bit on. The problem was not found
under KVM/QEMU, because Qemu just ignores all cpu mask bits.

v1 -> v2:
   * Fixed comment in extra patch
   * Now using pre-defined reset psw
   * Fixed some comments

Janosch Frank (3):
  s390x: Fix initial cr0 load comments
  s390x: Add CR save area
  s390x: Load reset psw on diag308 reset

 lib/s390x/asm-offsets.c  |  3 ++-
 lib/s390x/asm/arch_def.h |  5 +++--
 lib/s390x/interrupt.c    |  4 ++--
 lib/s390x/smp.c          |  2 +-
 s390x/cstart64.S         | 38 ++++++++++++++++++++++++--------------
 5 files changed, 32 insertions(+), 20 deletions(-)
```
#### [kvm-unit-tests PATCH v3 0/2] s390x: SCLP Unit test
##### From: Claudio Imbrenda <imbrenda@linux.ibm.com>

```c
From patchwork Mon Nov 11 17:20:24 2019
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Claudio Imbrenda <imbrenda@linux.ibm.com>
X-Patchwork-Id: 11237373
Return-Path: <SRS0=QoBT=ZD=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 5769714ED
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 11 Nov 2019 17:20:36 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 3F9C62184C
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 11 Nov 2019 17:20:36 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726845AbfKKRUf (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 11 Nov 2019 12:20:35 -0500
Received: from mx0a-001b2d01.pphosted.com ([148.163.156.1]:43878 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1727058AbfKKRUe (ORCPT
        <rfc822;kvm@vger.kernel.org>); Mon, 11 Nov 2019 12:20:34 -0500
Received: from pps.filterd (m0098404.ppops.net [127.0.0.1])
        by mx0a-001b2d01.pphosted.com (8.16.0.27/8.16.0.27) with SMTP id
 xABHEJck073136
        for <kvm@vger.kernel.org>; Mon, 11 Nov 2019 12:20:33 -0500
Received: from e06smtp07.uk.ibm.com (e06smtp07.uk.ibm.com [195.75.94.103])
        by mx0a-001b2d01.pphosted.com with ESMTP id 2w7ac8mksv-1
        (version=TLSv1.2 cipher=AES256-GCM-SHA384 bits=256 verify=NOT)
        for <kvm@vger.kernel.org>; Mon, 11 Nov 2019 12:20:33 -0500
Received: from localhost
        by e06smtp07.uk.ibm.com with IBM ESMTP SMTP Gateway: Authorized Use
 Only! Violators will be prosecuted
        for <kvm@vger.kernel.org> from <imbrenda@linux.ibm.com>;
        Mon, 11 Nov 2019 17:20:31 -0000
Received: from b06avi18626390.portsmouth.uk.ibm.com (9.149.26.192)
        by e06smtp07.uk.ibm.com (192.168.101.137) with IBM ESMTP SMTP Gateway:
 Authorized Use Only! Violators will be prosecuted;
        (version=TLSv1/SSLv3 cipher=AES256-GCM-SHA384 bits=256/256)
        Mon, 11 Nov 2019 17:20:29 -0000
Received: from d06av21.portsmouth.uk.ibm.com (d06av21.portsmouth.uk.ibm.com
 [9.149.105.232])
        by b06avi18626390.portsmouth.uk.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id xABHJpFk15598014
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Mon, 11 Nov 2019 17:19:51 GMT
Received: from d06av21.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 87DC552065;
        Mon, 11 Nov 2019 17:20:27 +0000 (GMT)
Received: from p-imbrenda.boeblingen.de.ibm.com (unknown [9.152.224.39])
        by d06av21.portsmouth.uk.ibm.com (Postfix) with ESMTPS id 44BE752059;
        Mon, 11 Nov 2019 17:20:27 +0000 (GMT)
From: Claudio Imbrenda <imbrenda@linux.ibm.com>
To: kvm@vger.kernel.org
Cc: linux-s390@vger.kernel.org, thuth@redhat.com, david@redhat.com,
        borntraeger@de.ibm.com, frankja@linux.ibm.com
Subject: [kvm-unit-tests PATCH v3 0/2] s390x: SCLP Unit test
Date: Mon, 11 Nov 2019 18:20:24 +0100
X-Mailer: git-send-email 2.7.4
X-TM-AS-GCONF: 00
x-cbid: 19111117-0028-0000-0000-000003B4F96C
X-IBM-AV-DETECTION: SAVI=unused REMOTE=unused XFE=unused
x-cbparentid: 19111117-0029-0000-0000-000024780204
Message-Id: <1573492826-24589-1-git-send-email-imbrenda@linux.ibm.com>
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:,,
 definitions=2019-11-11_05:,,
 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 priorityscore=1501
 malwarescore=0 suspectscore=1 phishscore=0 bulkscore=0 spamscore=0
 clxscore=1015 lowpriorityscore=0 mlxscore=0 impostorscore=0
 mlxlogscore=693 adultscore=0 classifier=spam adjust=0 reason=mlx
 scancount=1 engine=8.0.1-1910280000 definitions=main-1911110155
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This patchset contains some minor cleanup, some preparatory work and
then the SCLP unit test itself.

The unit test checks the following:
    
    * Correctly ignoring instruction bits that should be ignored
    * Privileged instruction check
    * Check for addressing exceptions
    * Specification exceptions:
      - SCCB size less than 8
      - SCCB unaligned
      - SCCB overlaps prefix or lowcore
      - SCCB address higher than 2GB
    * Return codes for
      - Invalid command
      - SCCB too short (but at least 8)
      - SCCB page boundary violation

v2 -> v3
* generally improved the naming of variables
* added and fixed comments
* renamed test_one_run to test_one_simple
* added some const where needed
* addresed many more small comments received during review
v1 -> v2
* fix many small issues that came up during the first round of reviews
* add comments to each function
* use a static buffer for the SCCP template when used

Claudio Imbrenda (2):
  s390x: sclp: add service call instruction wrapper
  s390x: SCLP unit test

 s390x/Makefile           |   1 +
 lib/s390x/asm/arch_def.h |  13 ++
 lib/s390x/sclp.c         |   7 +-
 s390x/sclp.c             | 417 +++++++++++++++++++++++++++++++++++++++++++++++
 s390x/unittests.cfg      |   3 +
 5 files changed, 435 insertions(+), 6 deletions(-)
 create mode 100644 s390x/sclp.c
```
#### [PATCH v2 0/3] KVM: VMX: Posted Interrupts fixes
##### From: Joao Martins <joao.m.martins@oracle.com>

```c
From patchwork Mon Nov 11 17:20:09 2019
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Joao Martins <joao.m.martins@oracle.com>
X-Patchwork-Id: 11237385
Return-Path: <SRS0=QoBT=ZD=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 149FB14ED
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 11 Nov 2019 17:23:34 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id E644621925
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 11 Nov 2019 17:23:33 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=oracle.com header.i=@oracle.com
 header.b="Cu6DizQr"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727237AbfKKRXb (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 11 Nov 2019 12:23:31 -0500
Received: from aserp2120.oracle.com ([141.146.126.78]:60570 "EHLO
        aserp2120.oracle.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726962AbfKKRXa (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 11 Nov 2019 12:23:30 -0500
Received: from pps.filterd (aserp2120.oracle.com [127.0.0.1])
        by aserp2120.oracle.com (8.16.0.27/8.16.0.27) with SMTP id
 xABHMP3G063050;
        Mon, 11 Nov 2019 17:22:25 GMT
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=oracle.com;
 h=from : to : cc :
 subject : date : message-id; s=corp-2019-08-05;
 bh=7DYyc0HKUvhmhki/GKWIXwRXBdqmCRZi8t0JYXW172o=;
 b=Cu6DizQr7mrB2x9AYC2mbyI/B67FuRS3Pguz45JWuKT6w2yVbm1v30GR0ZWnBr1xbaOV
 ecBLrRhlf5oCc3ZWQyOhzb2G4rDO5Pf75kzFX7cogsEkT5aznvqhf9cpeAe1ajT2h+xr
 /duWA2Bdci0SYV6AywAuA/2+CuXhzzKi+A0vuaZOvoqMEp9A4ZqRL0q2qkQceI66hzpA
 y1sISo7Oy9AxK2Jsyac7zinrwL7O1iJ5r3+dWlFv84qMBmqfWTcq00AS1MOcxe0eLeJp
 5StJ0n6V7zxqA2nNueW2OEKaQ6Ugoe0tW9KtfOWxKhqjqABIaCicIGcgP0WV343iwMmA qA==
Received: from userp3020.oracle.com (userp3020.oracle.com [156.151.31.79])
        by aserp2120.oracle.com with ESMTP id 2w5ndq069x-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Mon, 11 Nov 2019 17:22:25 +0000
Received: from pps.filterd (userp3020.oracle.com [127.0.0.1])
        by userp3020.oracle.com (8.16.0.27/8.16.0.27) with SMTP id
 xABHEa9Z136831;
        Mon, 11 Nov 2019 17:20:24 GMT
Received: from aserv0122.oracle.com (aserv0122.oracle.com [141.146.126.236])
        by userp3020.oracle.com with ESMTP id 2w67kmc980-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Mon, 11 Nov 2019 17:20:24 +0000
Received: from abhmp0014.oracle.com (abhmp0014.oracle.com [141.146.116.20])
        by aserv0122.oracle.com (8.14.4/8.14.4) with ESMTP id xABHKNmS032343;
        Mon, 11 Nov 2019 17:20:23 GMT
Received: from paddy.uk.oracle.com (/10.175.169.52)
        by default (Oracle Beehive Gateway v4.0)
        with ESMTP ; Mon, 11 Nov 2019 09:20:22 -0800
From: Joao Martins <joao.m.martins@oracle.com>
To: kvm@vger.kernel.org
Cc: Joao Martins <joao.m.martins@oracle.com>, linux-kernel@vger.kernel.org,
 Paolo Bonzini <pbonzini@redhat.com>,
 =?utf-8?b?UmFkaW0gS3LEjW3DocWZ?= <rkrcmar@redhat.com>,
 Sean Christopherson <sean.j.christopherson@intel.com>,
 Vitaly Kuznetsov <vkuznets@redhat.com>, Wanpeng Li <wanpengli@tencent.com>,
 Jim Mattson <jmattson@google.com>, Joerg Roedel <joro@8bytes.org>,
 Liran Alon <liran.alon@oracle.com>, Jag Raman <jag.raman@oracle.com>
Subject: [PATCH v2 0/3] KVM: VMX: Posted Interrupts fixes
Date: Mon, 11 Nov 2019 17:20:09 +0000
Message-Id: <20191111172012.28356-1-joao.m.martins@oracle.com>
X-Mailer: git-send-email 2.11.0
X-Proofpoint-Virus-Version: vendor=nai engine=6000 definitions=9438
 signatures=668685
X-Proofpoint-Spam-Details: rule=notspam policy=default score=0 suspectscore=1
 malwarescore=0
 phishscore=0 bulkscore=0 spamscore=0 mlxscore=0 mlxlogscore=602
 adultscore=0 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.0.1-1910280000 definitions=main-1911110155
X-Proofpoint-Virus-Version: vendor=nai engine=6000 definitions=9438
 signatures=668685
X-Proofpoint-Spam-Details: rule=notspam policy=default score=0
 priorityscore=1501 malwarescore=0
 suspectscore=1 phishscore=0 bulkscore=0 spamscore=0 clxscore=1015
 lowpriorityscore=0 mlxscore=0 impostorscore=0 mlxlogscore=669 adultscore=0
 classifier=spam adjust=0 reason=mlx scancount=1 engine=8.0.1-1910280000
 definitions=main-1911110155
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Hey,

This mini-series addresses two bugs plus a small cleanup: 

 1) Considering PID.PIR as opposed to just PID.ON for pending interrupt checks
    in the direct yield code path;
 
 2) Not changing NDST in vmx_vcpu_pi_load(), which addresses a regression. 
    Prior to this, we would observe Win2K12 guests hanging momentarily.
 
 3) Small cleanup to streamline PIR checks with a common helper.

The cleanup is done last to simplify backports.

	Joao

v2:
* Fixed missing Tb/Rb tags;
* Fixed broken Sob chains (on first two patches)
* Only test PID.PIR if PID.SN=1 (third patch)

Joao Martins (3):
  KVM: VMX: Consider PID.PIR to determine if vCPU has pending interrupts
  KVM: VMX: Do not change PID.NDST when loading a blocked vCPU
  KVM: VMX: Introduce pi_is_pir_empty() helper

 arch/x86/kvm/vmx/vmx.c | 21 +++++++++++++++++++--
 arch/x86/kvm/vmx/vmx.h | 11 +++++++++++
 2 files changed, 30 insertions(+), 2 deletions(-)
```
#### [PATCH v2 0/3] KVM: MMU: Fix a refcount bug with ZONE_DEVICE pages
##### From: Sean Christopherson <sean.j.christopherson@intel.com>

```c
From patchwork Mon Nov 11 22:12:26 2019
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Sean Christopherson <sean.j.christopherson@intel.com>
X-Patchwork-Id: 11237939
Return-Path: <SRS0=QoBT=ZD=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 45FA113BD
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 11 Nov 2019 22:12:34 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 24A4E21925
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 11 Nov 2019 22:12:34 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727103AbfKKWMc (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 11 Nov 2019 17:12:32 -0500
Received: from mga03.intel.com ([134.134.136.65]:2932 "EHLO mga03.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726946AbfKKWMb (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 11 Nov 2019 17:12:31 -0500
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from orsmga001.jf.intel.com ([10.7.209.18])
  by orsmga103.jf.intel.com with ESMTP/TLS/DHE-RSA-AES256-GCM-SHA384;
 11 Nov 2019 14:12:30 -0800
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.68,294,1569308400";
   d="scan'208";a="287302340"
Received: from sjchrist-coffee.jf.intel.com ([10.54.74.41])
  by orsmga001.jf.intel.com with ESMTP; 11 Nov 2019 14:12:29 -0800
From: Sean Christopherson <sean.j.christopherson@intel.com>
To: Paolo Bonzini <pbonzini@redhat.com>,
 =?utf-8?b?UmFkaW0gS3LEjW3DocWZ?= <rkrcmar@redhat.com>
Cc: Sean Christopherson <sean.j.christopherson@intel.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org, Adam Borowski <kilobyte@angband.pl>,
        David Hildenbrand <david@redhat.com>,
        Dan Williams <dan.j.williams@intel.com>
Subject: [PATCH v2 0/3] KVM: MMU: Fix a refcount bug with ZONE_DEVICE pages
Date: Mon, 11 Nov 2019 14:12:26 -0800
Message-Id: <20191111221229.24732-1-sean.j.christopherson@intel.com>
X-Mailer: git-send-email 2.24.0
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This mini-series fixes a suspected, but technically unconfirmed, bug in
KVM related to ZONE_DEVICE pages.  The suspected issue is that KVM treats
ZONE_DEVICE pages as reserved PFNs, and so doesn't put references to such
pages when dropping references via KVM's generic kvm_release_pfn_clean().

David Hildenbrand uncovered the bug during a discussion about removing
PG_reserved from ZONE_DEVICE pages, after Dan Williams pointed out[1] that
there was a bug report from Adam Borowski[2] that was likely related to
KVM's interaction with PageReserved().

Patch 1/3 contains the actual fix, patches 2/3 and 3/3 are minor cleanup
that is mostly unrelated, but dependent and prompted by the fix itself.

v2:
  - Remove the kvm_is_zone_device_pfn(pfn) check from kvm_get_pfn().  It's
    not entirely clear whether or not the hva_to_pfn_remapped() case is
    actually broken, e.g. KVM's page fault handler is likely ok, whereas
    not calling get_page() willl definitely cause breakage as KVM would
    later call put_page() on the pfn/page. [Paolo]

  - WARN if kvm_is_zone_device_pfn() is called without the underlying
    page being pinned.  This won't necessarily catch all bugs, e.g. if
    the above hva_to_pfn_remapped case is indeed broken, but will
    prevent completely bogus usage. [Dan]

  - Remove the is_error_pfn() check from transparent_hugepage_adjust()
    instead of carrying it forward into the new kvm_is_hugepage_allowed()
    helper. [Paolo]

[1] http://lkml.kernel.org/r/20190919115547.GA17963@angband.pl
[2] https://lkml.kernel.org/r/01adb4cb-6092-638c-0bab-e61322be7cf5@redhat.com

Sean Christopherson (3):
  KVM: MMU: Do not treat ZONE_DEVICE pages as being reserved
  KVM: x86/mmu: Remove superfluous is_error_pfn() check from THP adjust
  KVM: x86/mmu: Add helper to consolidate huge page promotion

 arch/x86/kvm/mmu.c       | 15 +++++++++------
 include/linux/kvm_host.h |  1 +
 virt/kvm/kvm_main.c      | 26 +++++++++++++++++++++++---
 3 files changed, 33 insertions(+), 9 deletions(-)
```
