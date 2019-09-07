

#### [PATCH v4 0/4] KVM: X86: Some tracepoint enhancements
##### From: Peter Xu <peterx@redhat.com>

```c
From patchwork Fri Sep  6 02:17:18 2019
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Peter Xu <peterx@redhat.com>
X-Patchwork-Id: 11134247
Return-Path: <SRS0=9Awg=XB=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 645EE1398
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  6 Sep 2019 02:17:35 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 636D62082E
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  6 Sep 2019 02:17:35 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2387741AbfIFCRe (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 5 Sep 2019 22:17:34 -0400
Received: from mx1.redhat.com ([209.132.183.28]:55786 "EHLO mx1.redhat.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1728628AbfIFCRd (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 5 Sep 2019 22:17:33 -0400
Received: from mail-pf1-f199.google.com (mail-pf1-f199.google.com
 [209.85.210.199])
        (using TLSv1.2 with cipher ECDHE-RSA-AES128-GCM-SHA256 (128/128 bits))
        (No client certificate requested)
        by mx1.redhat.com (Postfix) with ESMTPS id 98B6B7FDFF
        for <kvm@vger.kernel.org>; Fri,  6 Sep 2019 02:17:33 +0000 (UTC)
Received: by mail-pf1-f199.google.com with SMTP id i187so3361357pfc.10
        for <kvm@vger.kernel.org>; Thu, 05 Sep 2019 19:17:33 -0700 (PDT)
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:mime-version
         :content-transfer-encoding;
        bh=aBUS+fgsamAUOZtSEp++jlkJB5YgKT1csWUc+zQUKS4=;
        b=SAK4GanL7UBxn5aJIEWoEdSWWjzycKKhl5Ts40P+9Ld5JDqxIujeBnn/DrVwRLwp5C
         odmeiM77Z/88n8sJBWN4fAoOvrRMGobpp9NP1IcWdJrn3AYs3MTOT+kKxo4HvUp54mz4
         UlGx5wWMljWpcO918Dsx72pZTHPuGzww8o8ALsaYIT53jpPwavW3a5vkrbAeM88USOjq
         juLRMLe7tn3vDzkxn/NfnkA3kl1KeIXl232Uas1BOruxi3pwBUkCxn5XQNAQrCKsO6iG
         t76LLqg8FZdcNCTAJLsfkOrhZnmg30xST3wYugvwlNPeKluUa06Chdy2ratUhhvk6HNX
         VpmA==
X-Gm-Message-State: APjAAAU0VzotCI0xi3M3oI2fbq4qcvIu+m9qrKxJcHgvqNOJYmYaUV8Y
        FzwFGpl+BdJ5lqOhHSs8tcBl3p/6tV0pckjCWbv4d77NDgX3BB3NQWqsB/kH1UoFZmmWeZiiIMS
        QmKfrdt9bzdNF
X-Received: by 2002:a62:e717:: with SMTP id s23mr7759987pfh.71.1567736253137;
        Thu, 05 Sep 2019 19:17:33 -0700 (PDT)
X-Google-Smtp-Source: 
 APXvYqzCQJM/WuwJ79nbWX4bQwimjvaO+Ug+0hsWoiE4Vf9iu3itMcfU3iYer2r464k1bCxIb1dlRA==
X-Received: by 2002:a62:e717:: with SMTP id s23mr7759963pfh.71.1567736252846;
        Thu, 05 Sep 2019 19:17:32 -0700 (PDT)
Received: from xz-x1.redhat.com ([209.132.188.80])
        by smtp.gmail.com with ESMTPSA id
 a11sm8212359pfg.94.2019.09.05.19.17.29
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Thu, 05 Sep 2019 19:17:32 -0700 (PDT)
From: Peter Xu <peterx@redhat.com>
To: linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Cc: Sean Christopherson <sean.j.christopherson@intel.com>,
        Paolo Bonzini <pbonzini@redhat.com>,
        Wanpeng Li <kernellwp@gmail.com>,
        Krish Sadhukhan <krish.sadhukhan@oracle.com>, peterx@redhat.com
Subject: [PATCH v4 0/4] KVM: X86: Some tracepoint enhancements
Date: Fri,  6 Sep 2019 10:17:18 +0800
Message-Id: <20190906021722.2095-1-peterx@redhat.com>
X-Mailer: git-send-email 2.21.0
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

v4:
- pick r-b
- swap the last two patches [Sean]

v3:
- use unsigned int for vcpu id [Sean]
- a new patch to fix ple_window type [Sean]

v2:
- fix commit messages, change format of ple window tracepoint [Sean]
- rebase [Wanpeng]

Each small patch explains itself.  I noticed them when I'm tracing
some IRQ paths and I found them helpful at least to me.

Please have a look.  Thanks,

Peter Xu (4):
  KVM: X86: Trace vcpu_id for vmexit
  KVM: X86: Remove tailing newline for tracepoints
  KVM: VMX: Change ple_window type to unsigned int
  KVM: X86: Tune PLE Window tracepoint

 arch/x86/kvm/svm.c     | 16 ++++++++--------
 arch/x86/kvm/trace.h   | 34 ++++++++++++++--------------------
 arch/x86/kvm/vmx/vmx.c | 18 ++++++++++--------
 arch/x86/kvm/vmx/vmx.h |  2 +-
 arch/x86/kvm/x86.c     |  2 +-
 5 files changed, 34 insertions(+), 38 deletions(-)
```
#### [PATCH v18 0/6] Add ARMv8 RAS virtualization support in QEMU
##### From: Xiang Zheng <zhengxiang9@huawei.com>

```c
From patchwork Fri Sep  6 08:31:46 2019
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Xiang Zheng <zhengxiang9@huawei.com>
X-Patchwork-Id: 11134763
Return-Path: <SRS0=9Awg=XB=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 9446F16B1
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  6 Sep 2019 08:33:20 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 63F5D2084F
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  6 Sep 2019 08:33:20 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2387975AbfIFIdT (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 6 Sep 2019 04:33:19 -0400
Received: from szxga07-in.huawei.com ([45.249.212.35]:46196 "EHLO huawei.com"
        rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org with ESMTP
        id S1732698AbfIFIdS (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 6 Sep 2019 04:33:18 -0400
Received: from DGGEMS403-HUB.china.huawei.com (unknown [172.30.72.58])
        by Forcepoint Email with ESMTP id A772C54CF12C87E94E54;
        Fri,  6 Sep 2019 16:33:15 +0800 (CST)
Received: from HGHY1z004218071.china.huawei.com (10.177.29.32) by
 DGGEMS403-HUB.china.huawei.com (10.3.19.203) with Microsoft SMTP Server id
 14.3.439.0; Fri, 6 Sep 2019 16:33:07 +0800
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
Subject: [PATCH v18 0/6] Add ARMv8 RAS virtualization support in QEMU
Date: Fri, 6 Sep 2019 16:31:46 +0800
Message-ID: <20190906083152.25716-1-zhengxiang9@huawei.com>
X-Mailer: git-send-email 2.15.1.windows.2
MIME-Version: 1.0
Content-Type: text/plain
X-Originating-IP: [10.177.29.32]
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

Since Dongjiu is too busy to do this work, I will finish the rest work on behalf
of him.

---
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
  hw/arm/virt: Introduce RAS platform version and RAS machine option
  docs: APEI GHES generation and CPER record description
  ACPI: Add APEI GHES table generation support
  KVM: Move hwpoison page related functions into
    include/sysemu/kvm_int.h
  target-arm: kvm64: inject synchronous External Abort
  target-arm: kvm64: handle SIGBUS signal from kernel or KVM

 accel/kvm/kvm-all.c             |  33 +++
 default-configs/arm-softmmu.mak |   1 +
 docs/specs/acpi_hest_ghes.txt   |  88 ++++++
 hw/acpi/Kconfig                 |   4 +
 hw/acpi/Makefile.objs           |   1 +
 hw/acpi/acpi_ghes.c             | 462 ++++++++++++++++++++++++++++++++
 hw/acpi/aml-build.c             |   2 +
 hw/arm/virt-acpi-build.c        |  12 +
 hw/arm/virt.c                   |  33 +++
 include/hw/acpi/acpi_ghes.h     | 143 ++++++++++
 include/hw/acpi/aml-build.h     |   1 +
 include/hw/arm/virt.h           |   2 +
 include/sysemu/kvm.h            |   2 +-
 include/sysemu/kvm_int.h        |  23 ++
 target/arm/helper.c             |   2 +-
 target/arm/internals.h          |   5 +-
 target/arm/kvm.c                |   3 +
 target/arm/kvm64.c              |  73 +++++
 target/arm/tlb_helper.c         |   2 +-
 target/i386/kvm.c               |  34 ---
 20 files changed, 887 insertions(+), 39 deletions(-)
 create mode 100644 docs/specs/acpi_hest_ghes.txt
 create mode 100644 hw/acpi/acpi_ghes.c
 create mode 100644 include/hw/acpi/acpi_ghes.h
```
#### [PATCH v8 0/7] mm / virtio: Provide support for unused page
##### From: Alexander Duyck <alexander.duyck@gmail.com>

```c
From patchwork Fri Sep  6 14:53:21 2019
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Alexander Duyck <alexander.duyck@gmail.com>
X-Patchwork-Id: 11135457
Return-Path: <SRS0=9Awg=XB=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 2C6911395
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  6 Sep 2019 14:53:28 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 0C72420842
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  6 Sep 2019 14:53:27 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=gmail.com header.i=@gmail.com
 header.b="vTKtJTgG"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2394658AbfIFOxY (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 6 Sep 2019 10:53:24 -0400
Received: from mail-pg1-f193.google.com ([209.85.215.193]:44929 "EHLO
        mail-pg1-f193.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S2390603AbfIFOxY (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 6 Sep 2019 10:53:24 -0400
Received: by mail-pg1-f193.google.com with SMTP id i18so3621327pgl.11;
        Fri, 06 Sep 2019 07:53:23 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=subject:from:to:cc:date:message-id:user-agent:mime-version
         :content-transfer-encoding;
        bh=rjoMQB+Mq/0ixcTPll/Yse8OkMaybjf8D43LT3d+qZU=;
        b=vTKtJTgGYzko+zxYP9jTUKCr0CEaCV8I9MWTE+JyW+0OCfmB3oALdTDUOnaXz9Boph
         sOrEhQLuUtARbbCrM9mbjLUDJDbymk9ylw4rQ5oSTpg+pb4XNuRhjzi3JpIfJ0SfDlx/
         Vj5hl15j1P7NiEXVuQvkc9qmTh6Az1uyepCMS6can8870ArD2s+d2XC8iAw8vwP4ko6c
         WEm5lyyrSpSn+T0JeRVy5bxIAsQtvmtN7J/b/A9dF+a96J5ZscVpOLhczqSESCpezWeH
         2FnbAhz/LvJkxEDAcVs9REOq5YfRrVUq0ubJpYaSeVS5tlbfNEhdUgXA0Mbp+J25IXZr
         Xp+A==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:subject:from:to:cc:date:message-id:user-agent
         :mime-version:content-transfer-encoding;
        bh=rjoMQB+Mq/0ixcTPll/Yse8OkMaybjf8D43LT3d+qZU=;
        b=UckbjvlBUx8FFEpJPZ9X4qXzqkATQnXqPa3fUxQhYfbEgOc3mbUxuZIeZKVrCNzoU4
         pmGDJyhKyTybbxfpXlkoftf7f+DrR9laNjYPfYONDqqA6ucevIo52Cla7lzZEVblD01s
         RgcLXUxliyv3zJfrs6hBdiqjtAoCHTqgEk+TdF3PYUneuA6wYjAH1H6KXNPvxcEzvosG
         ePbY0oplt5egd76V6doKH9EXwa7LrtJ/M1d9Dnc1F/ilkgU48YRGsYhAfXSPqp1SV5Ww
         iourUU8gzvnpz8PJlH8pOsjD33FpOU31N8hAOyXVrWC13GkVby9+HGjb+T4AQJ8/jUGR
         fUhA==
X-Gm-Message-State: APjAAAUjUvofoqu1pp05jKaEIMULZ8yxqP/HcGlh4QRelMKsNo9CeuJS
        BHHFQ27mwz7N1ckvnme+fjo=
X-Google-Smtp-Source: 
 APXvYqz/VYIeGaQ7/nloI3Gq0Su4n93sg05uXSyruDOcPtM8ukUWtB0e4mHXCeiQtVrowWPTWIhBaQ==
X-Received: by 2002:a62:ee0a:: with SMTP id
 e10mr11272952pfi.197.1567781602887;
        Fri, 06 Sep 2019 07:53:22 -0700 (PDT)
Received: from localhost.localdomain ([2001:470:b:9c3:9e5c:8eff:fe4f:f2d0])
        by smtp.gmail.com with ESMTPSA id
 c1sm7901978pfd.117.2019.09.06.07.53.21
        (version=TLS1_2 cipher=ECDHE-RSA-AES128-GCM-SHA256 bits=128/128);
        Fri, 06 Sep 2019 07:53:22 -0700 (PDT)
Subject: [PATCH v8 0/7] mm / virtio: Provide support for unused page
 reporting
From: Alexander Duyck <alexander.duyck@gmail.com>
To: nitesh@redhat.com, kvm@vger.kernel.org, mst@redhat.com,
        david@redhat.com, dave.hansen@intel.com,
        linux-kernel@vger.kernel.org, willy@infradead.org,
        mhocko@kernel.org, linux-mm@kvack.org, akpm@linux-foundation.org,
        virtio-dev@lists.oasis-open.org, osalvador@suse.de
Cc: yang.zhang.wz@gmail.com, pagupta@redhat.com, riel@surriel.com,
        konrad.wilk@oracle.com, lcapitulino@redhat.com,
        wei.w.wang@intel.com, aarcange@redhat.com, pbonzini@redhat.com,
        dan.j.williams@intel.com, alexander.h.duyck@linux.intel.com
Date: Fri, 06 Sep 2019 07:53:21 -0700
Message-ID: <20190906145213.32552.30160.stgit@localhost.localdomain>
User-Agent: StGit/0.17.1-dirty
MIME-Version: 1.0
Content-Type: text/plain; charset="utf-8"
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This series provides an asynchronous means of reporting to a hypervisor
that a guest page is no longer in use and can have the data associated
with it dropped. To do this I have implemented functionality that allows
for what I am referring to as unused page reporting

The functionality for this is fairly simple. When enabled it will allocate
statistics to track the number of reported pages in a given free area.
When the number of free pages exceeds this value plus a high water value,
currently 32, it will begin performing page reporting which consists of
pulling pages off of free list and placing them into a scatter list. The
scatterlist is then given to the page reporting device and it will perform
the required action to make the pages "reported", in the case of
virtio-balloon this results in the pages being madvised as MADV_DONTNEED
and as such they are forced out of the guest. After this they are placed
back on the free list, and an additional bit is added if they are not
merged indicating that they are a reported buddy page instead of a
standard buddy page. The cycle then repeats with additional non-reported
pages being pulled until the free areas all consist of reported pages.

I am leaving a number of things hard-coded such as limiting the lowest
order processed to PAGEBLOCK_ORDER, and have left it up to the guest to
determine what the limit is on how many pages it wants to allocate to
process the hints. The upper limit for this is based on the size of the
queue used to store the scattergather list.

My primary testing has just been to verify the memory is being freed after
allocation by running memhog 40g on a 40g guest and watching the total
free memory via /proc/meminfo on the host. With this I have verified most
of the memory is freed after each iteration. As far as performance I have
been mainly focusing on the will-it-scale/page_fault1 test running with
16 vcpus. I have modified it to use Transparent Huge Pages. With this I
see almost no difference, -0.08%, with the patches applied and the feature
disabled. I see a regression of -0.86% with the feature enabled, but the
madvise disabled in the hypervisor due to a device being assigned. With
the feature fully enabled I see a regression of -3.27% versus the baseline
without these patches applied. In my testing I found that most of the
overhead was due to the page zeroing that comes as a result of the pages
having to be faulted back into the guest.

One side effect of these patches is that the guest becomes much more
resilient in terms of NUMA locality. With the pages being freed and then
reallocated when used it allows for the pages to be much closer to the
active thread, and as a result there can be situations where this patch
set will out-perform the stock kernel when the guest memory is not local
to the guest vCPUs. To avoid that in my testing I set the affinity of all
the vCPUs and QEMU instance to the same node.

Changes from the RFC:
https://lore.kernel.org/lkml/20190530215223.13974.22445.stgit@localhost.localdomain/
Moved aeration requested flag out of aerator and into zone->flags.
Moved boundary out of free_area and into local variables for aeration.
Moved aeration cycle out of interrupt and into workqueue.
Left nr_free as total pages instead of splitting it between raw and aerated.
Combined size and physical address values in virtio ring into one 64b value.

Changes from v1:
https://lore.kernel.org/lkml/20190619222922.1231.27432.stgit@localhost.localdomain/
Dropped "waste page treatment" in favor of "page hinting"
Renamed files and functions from "aeration" to "page_hinting"
Moved from page->lru list to scatterlist
Replaced wait on refcnt in shutdown with RCU and cancel_delayed_work_sync
Virtio now uses scatterlist directly instead of intermediate array
Moved stats out of free_area, now in separate area and pointed to from zone
Merged patch 5 into patch 4 to improve review-ability
Updated various code comments throughout

Changes from v2:
https://lore.kernel.org/lkml/20190724165158.6685.87228.stgit@localhost.localdomain/
Dropped "page hinting" in favor of "page reporting"
Renamed files from "hinting" to "reporting"
Replaced "Hinted" page type with "Reported" page flag
Added support for page poisoning while hinting is active
Add QEMU patch that implements PAGE_POISON feature

Changes from v3:
https://lore.kernel.org/lkml/20190801222158.22190.96964.stgit@localhost.localdomain/
Added mutex lock around page reporting startup and shutdown
Fixed reference to "page aeration" in patch 2
Split page reporting function bit out into separate QEMU patch
Limited capacity of scatterlist to vq size - 1 instead of vq size
Added exception handling for case of virtio descriptor allocation failure

Changes from v4:
https://lore.kernel.org/lkml/20190807224037.6891.53512.stgit@localhost.localdomain/
Replaced spin_(un)lock with spin_(un)lock_irq in page_reporting_cycle()
Dropped if/continue for ternary operator in page_reporting_process()
Added checks for isolate and cma types to for_each_reporting_migratetype_order
Added virtio-dev, Michal Hocko, and Oscar Salvador to to:/cc:
Rebased on latest linux-next and QEMU git trees

Changes from v5:
https://lore.kernel.org/lkml/20190812213158.22097.30576.stgit@localhost.localdomain/
Replaced spin_(un)lock with spin_(un)lock_irq in page_reporting_startup()
Updated shuffle code to use "shuffle_pick_tail" and updated patch description
Dropped storage of order and migratettype while page is being reported
Used get_pfnblock_migratetype to determine migratetype of page
Renamed put_reported_page to free_reported_page, added order as argument
Dropped check for CMA type as I believe we should be reporting those
Added code to allow moving of reported pages into and out of isolation
Defined page reporting order as minimum of Huge Page size vs MAX_ORDER - 1
Cleaned up use of static branch usage for page_reporting_notify_enabled

Changes from v6:
https://lore.kernel.org/lkml/20190821145806.20926.22448.stgit@localhost.localdomain/
Rebased on linux-next for 20190903
Added jump label to __page_reporting_request so we release RCU read lock
Removed "- 1" from capacity limit based on virtio ring
Added code to verify capacity is non-zero or return error on startup

Changes from v7:
https://lore.kernel.org/lkml/20190904150920.13848.32271.stgit@localhost.localdomain/
Updated poison fixes to clear flag if "nosanity" is enabled in kernel config
Split shuffle per-cpu optimization into seperate patch
Moved check for !phdev->capacity into reporting patch where it belongs
Added Reviewed-by tags received for v7
---

Alexander Duyck (7):
      mm: Add per-cpu logic to page shuffling
      mm: Adjust shuffle code to allow for future coalescing
      mm: Move set/get_pcppage_migratetype to mmzone.h
      mm: Use zone and order instead of free area in free_list manipulators
      mm: Introduce Reported pages
      virtio-balloon: Pull page poisoning config out of free page hinting
      virtio-balloon: Add support for providing unused page reports to host


 drivers/virtio/Kconfig              |    1 
 drivers/virtio/virtio_balloon.c     |   87 ++++++++-
 include/linux/mmzone.h              |  124 ++++++++-----
 include/linux/page-flags.h          |   11 +
 include/linux/page_reporting.h      |  177 ++++++++++++++++++
 include/uapi/linux/virtio_balloon.h |    1 
 mm/Kconfig                          |    5 +
 mm/Makefile                         |    1 
 mm/internal.h                       |   18 ++
 mm/memory_hotplug.c                 |    1 
 mm/page_alloc.c                     |  216 ++++++++++++++++------
 mm/page_reporting.c                 |  340 +++++++++++++++++++++++++++++++++++
 mm/shuffle.c                        |   40 ++--
 mm/shuffle.h                        |   12 +
 14 files changed, 902 insertions(+), 132 deletions(-)
 create mode 100644 include/linux/page_reporting.h
 create mode 100644 mm/page_reporting.c

--
```
#### [kvm-unit-tests PATCH 0/3] x86: Cleanup max test CPUs
##### From: Sean Christopherson <sean.j.christopherson@intel.com>

```c
From patchwork Fri Sep  6 16:34:47 2019
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Sean Christopherson <sean.j.christopherson@intel.com>
X-Patchwork-Id: 11135683
Return-Path: <SRS0=9Awg=XB=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 6BEB41395
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  6 Sep 2019 16:34:52 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 52CC02082C
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  6 Sep 2019 16:34:52 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2390380AbfIFQev (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 6 Sep 2019 12:34:51 -0400
Received: from mga02.intel.com ([134.134.136.20]:9378 "EHLO mga02.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S2388260AbfIFQev (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 6 Sep 2019 12:34:51 -0400
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from orsmga007.jf.intel.com ([10.7.209.58])
  by orsmga101.jf.intel.com with ESMTP/TLS/DHE-RSA-AES256-GCM-SHA384;
 06 Sep 2019 09:34:50 -0700
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.64,473,1559545200";
   d="scan'208";a="174327224"
Received: from sjchrist-coffee.jf.intel.com ([10.54.74.41])
  by orsmga007.jf.intel.com with ESMTP; 06 Sep 2019 09:34:50 -0700
From: Sean Christopherson <sean.j.christopherson@intel.com>
To: Paolo Bonzini <pbonzini@redhat.com>,
 =?utf-8?b?UmFkaW0gS3LEjW3DocWZ?= <rkrcmar@redhat.com>
Cc: kvm@vger.kernel.org, Evgeny Yakovlev <wrfsh@yandex-team.ru>
Subject: [kvm-unit-tests PATCH 0/3] x86: Cleanup max test CPUs
Date: Fri,  6 Sep 2019 09:34:47 -0700
Message-Id: <20190906163450.30797-1-sean.j.christopherson@intel.com>
X-Mailer: git-send-email 2.22.0
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Fix a bug Evgeny reported where init_apic_map() can cause random
corruption due accessing random bytes far beyond the bounds of
online_cpus.  Take the opportunity to bump the max number of test CPUs
to a realistic maximum, i.e. what kvm-unit-tests can support without a
major rework.

Sean Christopherson (3):
  x86: Fix out of bounds access when processing online_cpus
  x86: Declare online_cpus based on MAX_TEST_CPUS
  x86: Bump max number of test CPUs to 255

 lib/x86/apic-defs.h | 2 +-
 lib/x86/apic.c      | 4 ++--
 lib/x86/smp.c       | 2 --
 x86/cstart.S        | 2 +-
 x86/cstart64.S      | 2 +-
 5 files changed, 5 insertions(+), 7 deletions(-)
```
#### [PATCH v4 0/9] KVM: VMX: Add full nested support for
##### From: Oliver Upton <oupton@google.com>

```c
From patchwork Fri Sep  6 21:03:04 2019
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Oliver Upton <oupton@google.com>
X-Patchwork-Id: 11136057
Return-Path: <SRS0=9Awg=XB=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id B70F41593
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  6 Sep 2019 21:03:23 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 9850421848
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  6 Sep 2019 21:03:23 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=google.com header.i=@google.com
 header.b="GI+HZU3F"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2388468AbfIFVDW (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 6 Sep 2019 17:03:22 -0400
Received: from mail-pf1-f202.google.com ([209.85.210.202]:41568 "EHLO
        mail-pf1-f202.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1725872AbfIFVDW (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 6 Sep 2019 17:03:22 -0400
Received: by mail-pf1-f202.google.com with SMTP id g15so5515057pfb.8
        for <kvm@vger.kernel.org>; Fri, 06 Sep 2019 14:03:21 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=date:message-id:mime-version:subject:from:to:cc;
        bh=X3p9IC5KMyfjhH2AJpSb8AsD49T286nJ6y+FEn+DgIo=;
        b=GI+HZU3FqRbK5SdtZUfHusMTRh1WpfgISUCBrFbWcaPpoZgJPX5Z7t3uBt5nLLgqK5
         aNBnENRONB9tv5WaQi88o21skDUjlyPVI0PxTF6MmhQP/LgQfLPBLvbJcQ890Qw+htRl
         11ESH4eCtSItC074pgr9PMNtTr5g3HjEwmSDffGLxeNnUgXkIhMPW90L176Md/O2rkvE
         Ziol6ves4U4EjCbAhdqWZPZ1lGdI+f7VbEVBczn2hwa312MpBsRmtlIeZRBvyZat6H7q
         nJ5+L5TQdVDBzAuNuS0e3z6YyPkrnJiiYUaMZcOPPQcVhTl7Fo6qgy4WheFq14P3y03F
         PCIw==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:date:message-id:mime-version:subject:from:to:cc;
        bh=X3p9IC5KMyfjhH2AJpSb8AsD49T286nJ6y+FEn+DgIo=;
        b=SMTme3F1/SYCrxxt53JJqtoRIqG2VTXvsb/pOQCbfq5fANSete66X+4zakkJrc4xAR
         xIRzQ5SpbO8j5oqhQiQL01ri8WpkSqo97CM6uQOZaYYhppNnC0Bs5Uz9qBwh30OURNab
         AEE14nnCQmjGSuzqjsjuBUfFp34TgqH0nqecEDOKVP2Sh/2NT4JzJ2xYQniYPXlimsd8
         GoSVUNPAJJeEatGifYP8s3y2Z9rQqzxsAZ0bsmyBeuPzgDM4eHK+YPbmuAFYv+EMhS98
         6RJh3gJcXyX86zrsorjH3gg9V7gLXW7SvmXr61ALXFFts1MTCTqP++irgbMfP7Iy/ehe
         TDPQ==
X-Gm-Message-State: APjAAAWcdaydO3ihYjtCLuZXk5yA3R4CkzWkQE2rnWaITHjw4D6m+Wrq
        uOCq8isSbW+9qpv8u3cBkmsdAPxcVeca8hL1AohLnjqaSY8aSKzqNfYx+ds3O4xapZqWT6gzEkw
        f+QuCcGz+JMD/H5TWXiOsoNU8db5axiwRfxNlAmdoLgsG3aoHNiyQY2yRQg==
X-Google-Smtp-Source: 
 APXvYqxNdG4S1T4ON0y0OCcJPNj355A2BQvW+t+xyIbLenbmjjeNG/CrY53WlrKas2Lf8IVcIQY0nUA5d3Y=
X-Received: by 2002:a63:5b52:: with SMTP id l18mr9683664pgm.21.1567803801063;
 Fri, 06 Sep 2019 14:03:21 -0700 (PDT)
Date: Fri,  6 Sep 2019 14:03:04 -0700
Message-Id: <20190906210313.128316-1-oupton@google.com>
Mime-Version: 1.0
X-Mailer: git-send-email 2.23.0.187.g17f5b7556c-goog
Subject: [PATCH v4 0/9] KVM: VMX: Add full nested support for
 IA32_PERF_GLOBAL_CTRL
From: Oliver Upton <oupton@google.com>
To: kvm@vger.kernel.org, Paolo Bonzini <pbonzini@redhat.com>, "
	=?utf-8?b?UmFkaW0gS3LEjW3DocWZ?= " <rkrcmar@redhat.com>
Cc: Jim Mattson <jmattson@google.com>, Peter Shier <pshier@google.com>,
        Krish Sadhukhan <krish.sadhukhan@oracle.com>,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        Oliver Upton <oupton@google.com>
Content-Type: text/plain; charset="UTF-8"
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

[v1] https://lore.kernel.org/r/20190828234134.132704-1-oupton@google.com
[v2] https://lore.kernel.org/r/20190903213044.168494-1-oupton@google.com
[v3] https://lore.kernel.org/r/20190903215801.183193-1-oupton@google.com

v1 => v2:
 - Add Krish's Co-developed-by and Signed-off-by tags.
 - Fix minor nit to kvm-unit-tests to use 'host' local variable
   throughout test_load_pgc()
 - Teach guest_state_test_main() to check guest state from within nested
   VM
 - Update proposed tests to use guest/host state checks, wherein the
   value is checked from MSR_CORE_PERF_GLOBAL_CTRL.
 - Changelog line wrapping

v2 => v3:
 - Remove the value unchanged condition from
   kvm_is_valid_perf_global_ctrl
 - Add line to changelog for patch 3/8

v3 => v4:
 - Allow tests to set the guest func multiple times
 - Style fixes throughout kvm-unit-tests patches, per Krish's review

This patchset exposes the "load IA32_PERF_GLOBAL_CTRL" to guests for nested
VM-entry and VM-exit. There already was some existing code that supported
the VM-exit ctrl, though it had an issue and was not exposed to the guest
anyway. These patches are based on the original set that Krish Sadhukhan
sent out earlier this year.

Purpose of each patch:

(1) Change the existing code that implemented the VM-exit functionality
    to use kvm_set_msr() to avoid being overwritten by
    atomic_perf_switch_msrs().
(2) Update prepare_vmcs02() to implement the VM-entry functionality,
    again using kvm_set_msr().
(3) Create a helper function for checking the validity of an
    IA32_PERF_GLOBAL_CTRL value against pmu->global_ctrl_mask.
(4) Check guest state on VM-entry as described in the SDM.
(5) Check host state on VM-entry as described in the SDM.
(6) Expose the "load IA32_PERF_GLOBAL_CTRL" VM-entry and VM-exit
    controls if IA32_PERF_GLOBAL_CTRL is a valid MSR.
(7) Modify guest_state_test_main() to check guest state MSRs
(8) Tests in kvm-unit-tests to check the VM-entry and VM-exit controls
    work properly

Oliver Upton (6):
  KVM: nVMX: Use kvm_set_msr to load IA32_PERF_GLOBAL_CTRL on vmexit
  KVM: nVMX: Load GUEST_IA32_PERF_GLOBAL_CTRL MSR on vm-entry
  KVM: VMX: Add helper to check reserved bits in IA32_PERF_GLOBAL_CTRL
  KVM: nVMX: check GUEST_IA32_PERF_GLOBAL_CTRL on VM-Entry
  KVM: nVMX: Check HOST_IA32_PERF_GLOBAL_CTRL on VM-entry
  KVM: nVMX: Expose load IA32_PERF_GLOBAL_CTRL vm control if supported

 arch/x86/kvm/pmu.h           |  6 ++++++
 arch/x86/kvm/vmx/nested.c    | 37 +++++++++++++++++++++++++++++++++---
 arch/x86/kvm/vmx/pmu_intel.c |  5 ++++-
 arch/x86/kvm/vmx/vmx.c       | 21 ++++++++++++++++++++
 arch/x86/kvm/vmx/vmx.h       |  1 +
 5 files changed, 66 insertions(+), 4 deletions(-)
```
