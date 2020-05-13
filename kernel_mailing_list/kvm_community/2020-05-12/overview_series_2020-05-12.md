#### [PATCH 1/2] KVM: x86/pmu: Tweak kvm_pmu_get_msr to pass 'struct msr_data' in
##### From: Like Xu <like.xu@linux.intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Like Xu <like.xu@linux.intel.com>
X-Patchwork-Id: 11542057
Return-Path: <SRS0=B8Dm=62=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 2285992A
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 12 May 2020 04:43:05 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 0EBD320733
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 12 May 2020 04:43:05 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726848AbgELEnB (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 12 May 2020 00:43:01 -0400
Received: from mga18.intel.com ([134.134.136.126]:51199 "EHLO mga18.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1725776AbgELEnB (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 12 May 2020 00:43:01 -0400
IronPort-SDR: 
 ZYFJW30tSSdvZtaPgYMmNmd47mZqX6Tm820cww46VwXOGlBkEKChPe/gULchVpk7JxVb3Uwba0
 iejp/mua0yfg==
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from orsmga003.jf.intel.com ([10.7.209.27])
  by orsmga106.jf.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 11 May 2020 21:43:00 -0700
IronPort-SDR: 
 MjMkHUNgp6gNHCPPO/kkCaXOUxUA2bH+ljPM0M9fNhULWt6qub9kjEz2PVh9VunXQpy9vwK1/7
 ZChJN7V097Ag==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.73,382,1583222400";
   d="scan'208";a="261995735"
Received: from sqa-gate.sh.intel.com (HELO clx-ap-likexu.tsp.org)
 ([10.239.48.212])
  by orsmga003.jf.intel.com with ESMTP; 11 May 2020 21:42:58 -0700
From: Like Xu <like.xu@linux.intel.com>
To: pbonzini@redhat.com
Cc: jmattson@google.com, joro@8bytes.org, kvm@vger.kernel.org,
        like.xu@linux.intel.com, linux-kernel@vger.kernel.org,
        sean.j.christopherson@intel.com, vkuznets@redhat.com,
        wanpengli@tencent.com, Wei Wang <wei.w.wang@intel.com>
Subject: [PATCH 1/2] KVM: x86/pmu: Tweak kvm_pmu_get_msr to pass 'struct
 msr_data' in
Date: Tue, 12 May 2020 12:42:44 +0800
Message-Id: <20200512044245.130220-1-like.xu@linux.intel.com>
X-Mailer: git-send-email 2.21.3
In-Reply-To: <f1c77c79-7ff8-c5f3-e011-9874a4336217@redhat.com>
References: <f1c77c79-7ff8-c5f3-e011-9874a4336217@redhat.com>
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Wei Wang <wei.w.wang@intel.com>

Change kvm_pmu_get_msr() to get the msr_data struct, as the host_initiated
field from the struct could be used by get_msr. This also makes this API
consistent with kvm_pmu_set_msr. No functional changes.

Signed-off-by: Wei Wang <wei.w.wang@intel.com>
---
 arch/x86/kvm/pmu.c           |  4 ++--
 arch/x86/kvm/pmu.h           |  4 ++--
 arch/x86/kvm/svm/pmu.c       |  7 ++++---
 arch/x86/kvm/vmx/pmu_intel.c | 19 +++++++++++--------
 arch/x86/kvm/x86.c           |  4 ++--
 5 files changed, 21 insertions(+), 17 deletions(-)

```
#### 
##### 

```c
```
#### [PATCH v27 03/10] docs: APEI GHES generation and CPER record description
##### From: Dongjiu Geng <gengdongjiu@huawei.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Dongjiu Geng <gengdongjiu@huawei.com>
X-Patchwork-Id: 11541965
Return-Path: <SRS0=B8Dm=62=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 0B3551668
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 12 May 2020 03:03:16 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id ED89C206D7
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 12 May 2020 03:03:15 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728622AbgELDDO (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 11 May 2020 23:03:14 -0400
Received: from szxga06-in.huawei.com ([45.249.212.32]:51786 "EHLO huawei.com"
        rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org with ESMTP
        id S1728610AbgELDDO (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 11 May 2020 23:03:14 -0400
Received: from DGGEMS413-HUB.china.huawei.com (unknown [172.30.72.60])
        by Forcepoint Email with ESMTP id 991D43B7C74E2B84C7B9;
        Tue, 12 May 2020 11:03:11 +0800 (CST)
Received: from huawei.com (10.151.151.243) by DGGEMS413-HUB.china.huawei.com
 (10.3.19.213) with Microsoft SMTP Server id 14.3.487.0; Tue, 12 May 2020
 11:03:05 +0800
From: Dongjiu Geng <gengdongjiu@huawei.com>
To: <imammedo@redhat.com>, <mst@redhat.com>,
        <xiaoguangrong.eric@gmail.com>, <peter.maydell@linaro.org>,
        <shannon.zhaosl@gmail.com>, <fam@euphon.net>, <rth@twiddle.net>,
        <ehabkost@redhat.com>, <mtosatti@redhat.com>,
        <qemu-devel@nongnu.org>, <kvm@vger.kernel.org>,
        <qemu-arm@nongnu.org>, <pbonzini@redhat.com>, <philmd@redhat.com>
CC: <gengdongjiu@huawei.com>, <zhengxiang9@huawei.com>,
        <Jonathan.Cameron@huawei.com>, <linuxarm@huawei.com>
Subject: [PATCH v27 03/10] docs: APEI GHES generation and CPER record
 description
Date: Tue, 12 May 2020 11:06:02 +0800
Message-ID: <20200512030609.19593-4-gengdongjiu@huawei.com>
X-Mailer: git-send-email 2.17.1
In-Reply-To: <20200512030609.19593-1-gengdongjiu@huawei.com>
References: <20200512030609.19593-1-gengdongjiu@huawei.com>
MIME-Version: 1.0
X-Originating-IP: [10.151.151.243]
X-CFilter-Loop: Reflected
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Add APEI/GHES detailed design document

Signed-off-by: Dongjiu Geng <gengdongjiu@huawei.com>
Signed-off-by: Xiang Zheng <zhengxiang9@huawei.com>
Reviewed-by: Michael S. Tsirkin <mst@redhat.com>
Reviewed-by: Igor Mammedov <imammedo@redhat.com>
---
 docs/specs/acpi_hest_ghes.rst | 110 ++++++++++++++++++++++++++++++++++++++++++
 docs/specs/index.rst          |   1 +
 2 files changed, 111 insertions(+)
 create mode 100644 docs/specs/acpi_hest_ghes.rst

diff --git a/docs/specs/acpi_hest_ghes.rst b/docs/specs/acpi_hest_ghes.rst
new file mode 100644
index 0000000..68f1fbe
--- /dev/null
+++ b/docs/specs/acpi_hest_ghes.rst
@@ -0,0 +1,110 @@
+APEI tables generating and CPER record
+======================================
+
+..
+   Copyright (c) 2020 HUAWEI TECHNOLOGIES CO., LTD.
+
+   This work is licensed under the terms of the GNU GPL, version 2 or later.
+   See the COPYING file in the top-level directory.
+
+Design Details
+--------------
+
+::
+
+         etc/acpi/tables                           etc/hardware_errors
+      ====================                   ===============================
+  + +--------------------------+            +----------------------------+
+  | | HEST                     | +--------->|    error_block_address1    |------+
+  | +--------------------------+ |          +----------------------------+      |
+  | | GHES1                    | | +------->|    error_block_address2    |------+-+
+  | +--------------------------+ | |        +----------------------------+      | |
+  | | .................        | | |        |      ..............        |      | |
+  | | error_status_address-----+-+ |        -----------------------------+      | |
+  | | .................        |   |   +--->|    error_block_addressN    |------+-+---+
+  | | read_ack_register--------+-+ |   |    +----------------------------+      | |   |
+  | | read_ack_preserve        | +-+---+--->|     read_ack_register1     |      | |   |
+  | | read_ack_write           |   |   |    +----------------------------+      | |   |
+  + +--------------------------+   | +-+--->|     read_ack_register2     |      | |   |
+  | | GHES2                    |   | | |    +----------------------------+      | |   |
+  + +--------------------------+   | | |    |       .............        |      | |   |
+  | | .................        |   | | |    +----------------------------+      | |   |
+  | | error_status_address-----+---+ | | +->|     read_ack_registerN     |      | |   |
+  | | .................        |     | | |  +----------------------------+      | |   |
+  | | read_ack_register--------+-----+ | |  |Generic Error Status Block 1|<-----+ |   |
+  | | read_ack_preserve        |       | |  |-+------------------------+-+        |   |
+  | | read_ack_write           |       | |  | |          CPER          | |        |   |
+  + +--------------------------|       | |  | |          CPER          | |        |   |
+  | | ...............          |       | |  | |          ....          | |        |   |
+  + +--------------------------+       | |  | |          CPER          | |        |   |
+  | | GHESN                    |       | |  |-+------------------------+-|        |   |
+  + +--------------------------+       | |  |Generic Error Status Block 2|<-------+   |
+  | | .................        |       | |  |-+------------------------+-+            |
+  | | error_status_address-----+-------+ |  | |           CPER         | |            |
+  | | .................        |         |  | |           CPER         | |            |
+  | | read_ack_register--------+---------+  | |           ....         | |            |
+  | | read_ack_preserve        |            | |           CPER         | |            |
+  | | read_ack_write           |            +-+------------------------+-+            |
+  + +--------------------------+            |         ..........         |            |
+                                            |----------------------------+            |
+                                            |Generic Error Status Block N |<----------+
+                                            |-+-------------------------+-+
+                                            | |          CPER           | |
+                                            | |          CPER           | |
+                                            | |          ....           | |
+                                            | |          CPER           | |
+                                            +-+-------------------------+-+
+
+
+(1) QEMU generates the ACPI HEST table. This table goes in the current
+    "etc/acpi/tables" fw_cfg blob. Each error source has different
+    notification types.
+
+(2) A new fw_cfg blob called "etc/hardware_errors" is introduced. QEMU
+    also needs to populate this blob. The "etc/hardware_errors" fw_cfg blob
+    contains an address registers table and an Error Status Data Block table.
+
+(3) The address registers table contains N Error Block Address entries
+    and N Read Ack Register entries. The size for each entry is 8-byte.
+    The Error Status Data Block table contains N Error Status Data Block
+    entries. The size for each entry is 4096(0x1000) bytes. The total size
+    for the "etc/hardware_errors" fw_cfg blob is (N * 8 * 2 + N * 4096) bytes.
+    N is the number of the kinds of hardware error sources.
+
+(4) QEMU generates the ACPI linker/loader script for the firmware. The
+    firmware pre-allocates memory for "etc/acpi/tables", "etc/hardware_errors"
+    and copies blob contents there.
+
+(5) QEMU generates N ADD_POINTER commands, which patch addresses in the
+    "error_status_address" fields of the HEST table with a pointer to the
+    corresponding "address registers" in the "etc/hardware_errors" blob.
+
+(6) QEMU generates N ADD_POINTER commands, which patch addresses in the
+    "read_ack_register" fields of the HEST table with a pointer to the
+    corresponding "read_ack_register" within the "etc/hardware_errors" blob.
+
+(7) QEMU generates N ADD_POINTER commands for the firmware, which patch
+    addresses in the "error_block_address" fields with a pointer to the
+    respective "Error Status Data Block" in the "etc/hardware_errors" blob.
+
+(8) QEMU defines a third and write-only fw_cfg blob which is called
+    "etc/hardware_errors_addr". Through that blob, the firmware can send back
+    the guest-side allocation addresses to QEMU. The "etc/hardware_errors_addr"
+    blob contains a 8-byte entry. QEMU generates a single WRITE_POINTER command
+    for the firmware. The firmware will write back the start address of
+    "etc/hardware_errors" blob to the fw_cfg file "etc/hardware_errors_addr".
+
+(9) When QEMU gets a SIGBUS from the kernel, QEMU writes CPER into corresponding
+    "Error Status Data Block", guest memory, and then injects platform specific
+    interrupt (in case of arm/virt machine it's Synchronous External Abort) as a
+    notification which is necessary for notifying the guest.
+
+(10) This notification (in virtual hardware) will be handled by the guest
+     kernel, on receiving notification, guest APEI driver could read the CPER error
+     and take appropriate action.
+
+(11) kvm_arch_on_sigbus_vcpu() uses source_id as index in "etc/hardware_errors" to
+     find out "Error Status Data Block" entry corresponding to error source. So supported
+     source_id values should be assigned here and not be changed afterwards to make sure
+     that guest will write error into expected "Error Status Data Block" even if guest was
+     migrated to a newer QEMU.
```
#### [PATCH] i386/kvm: fix a use-after-free when vcpu plug/unplug
##### From: Pan Nengyuan <pannengyuan@huawei.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 8bit
X-Patchwork-Submitter: Pan Nengyuan <pannengyuan@huawei.com>
X-Patchwork-Id: 11542211
Return-Path: <SRS0=B8Dm=62=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 1998A14C0
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 12 May 2020 07:15:55 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 0B37D2075E
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 12 May 2020 07:15:54 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726008AbgELHPx (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 12 May 2020 03:15:53 -0400
Received: from szxga05-in.huawei.com ([45.249.212.191]:4777 "EHLO huawei.com"
        rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org with ESMTP
        id S1725813AbgELHPx (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 12 May 2020 03:15:53 -0400
Received: from DGGEMS413-HUB.china.huawei.com (unknown [172.30.72.59])
        by Forcepoint Email with ESMTP id 3561BED1A72B48253AD3;
        Tue, 12 May 2020 15:15:43 +0800 (CST)
Received: from opensource.huawei.com (10.175.100.98) by
 DGGEMS413-HUB.china.huawei.com (10.3.19.213) with Microsoft SMTP Server id
 14.3.487.0; Tue, 12 May 2020 15:15:35 +0800
From: Pan Nengyuan <pannengyuan@huawei.com>
To: <pbonzini@redhat.com>, <rth@twiddle.net>, <ehabkost@redhat.com>,
        <mtosatti@redhat.com>
CC: <kvm@vger.kernel.org>, <qemu-devel@nongnu.org>,
        <zhang.zhanghailiang@huawei.com>, <euler.robot@huawei.com>,
        Pan Nengyuan <pannengyuan@huawei.com>
Subject: [PATCH] i386/kvm: fix a use-after-free when vcpu plug/unplug
Date: Tue, 12 May 2020 09:39:33 -0400
Message-ID: <20200512133933.8696-1-pannengyuan@huawei.com>
X-Mailer: git-send-email 2.18.2
MIME-Version: 1.0
X-Originating-IP: [10.175.100.98]
X-CFilter-Loop: Reflected
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

When we hotplug vcpus, cpu_update_state is added to vm_change_state_head
in kvm_arch_init_vcpu(). But it forgot to delete in kvm_arch_destroy_vcpu() after
unplug. Then it will cause a use-after-free access. This patch delete it in
kvm_arch_destroy_vcpu() to fix that.

Reproducer:
    virsh setvcpus vm1 4 --live
    virsh setvcpus vm1 2 --live
    virsh suspend vm1
    virsh resume vm1

The UAF stack:
==qemu-system-x86_64==28233==ERROR: AddressSanitizer: heap-use-after-free on address 0x62e00002e798 at pc 0x5573c6917d9e bp 0x7fff07139e50 sp 0x7fff07139e40
WRITE of size 1 at 0x62e00002e798 thread T0
    #0 0x5573c6917d9d in cpu_update_state /mnt/sdb/qemu/target/i386/kvm.c:742
    #1 0x5573c699121a in vm_state_notify /mnt/sdb/qemu/vl.c:1290
    #2 0x5573c636287e in vm_prepare_start /mnt/sdb/qemu/cpus.c:2144
    #3 0x5573c6362927 in vm_start /mnt/sdb/qemu/cpus.c:2150
    #4 0x5573c71e8304 in qmp_cont /mnt/sdb/qemu/monitor/qmp-cmds.c:173
    #5 0x5573c727cb1e in qmp_marshal_cont qapi/qapi-commands-misc.c:835
    #6 0x5573c7694c7a in do_qmp_dispatch /mnt/sdb/qemu/qapi/qmp-dispatch.c:132
    #7 0x5573c7694c7a in qmp_dispatch /mnt/sdb/qemu/qapi/qmp-dispatch.c:175
    #8 0x5573c71d9110 in monitor_qmp_dispatch /mnt/sdb/qemu/monitor/qmp.c:145
    #9 0x5573c71dad4f in monitor_qmp_bh_dispatcher /mnt/sdb/qemu/monitor/qmp.c:234

Reported-by: Euler Robot <euler.robot@huawei.com>
Signed-off-by: Pan Nengyuan <pannengyuan@huawei.com>
Reviewed-by: Philippe Mathieu-Daudé <philmd@redhat.com>
---
 target/i386/cpu.h | 1 +
 target/i386/kvm.c | 5 ++++-
 2 files changed, 5 insertions(+), 1 deletion(-)

```
#### 
##### 

```c
```
#### [PATCH V4 01/14] KVM: MIPS: Define KVM_ENTRYHI_ASID to cpu_asid_mask(&boot_cpu_data)
##### From: Huacai Chen <chenhc@lemote.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Huacai Chen <chenhc@lemote.com>
X-Patchwork-Id: 11542845
Return-Path: <SRS0=B8Dm=62=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 87006913
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 12 May 2020 10:31:20 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 6FDD520722
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 12 May 2020 10:31:20 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=fail reason="signature verification failed" (2048-bit key)
 header.d=gmail.com header.i=@gmail.com header.b="fEq7Sr4E"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729437AbgELKbU (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 12 May 2020 06:31:20 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:57444 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-FAIL-OK-FAIL)
        by vger.kernel.org with ESMTP id S1727783AbgELKbT (ORCPT
        <rfc822;kvm@vger.kernel.org>); Tue, 12 May 2020 06:31:19 -0400
Received: from mail-pf1-x444.google.com (mail-pf1-x444.google.com
 [IPv6:2607:f8b0:4864:20::444])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 73E13C061A0C;
        Tue, 12 May 2020 03:31:19 -0700 (PDT)
Received: by mail-pf1-x444.google.com with SMTP id 145so6146896pfw.13;
        Tue, 12 May 2020 03:31:19 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=sender:from:to:cc:subject:date:message-id:in-reply-to:references;
        bh=j/OSBdV9DXY2ETWsIc3eeYNxFXzAjwLns12YdEbp9AY=;
        b=fEq7Sr4EkplIF9pG8id32iWH/aPwuaVUqoIqACL9UNK7QQmjJ4n9IW2uMxLTcHPFxx
         H/eGKb/O4GgC6Fnv1QsiLRuswSiEI3P/Fyy700xI4YMZHO9YpjKJV9MWaSy6P7fKQ0Ob
         lrEJ+S+G24XaMXTDHwDtNlVRAP8qLPBmmvRi51hwlufs2Fk8eZxZC/JTWm6kLQaLYJN6
         vSd7lCgqMLQ5PEnl9TNLNfNvxd8HfpL3gKwcAg3r0fA/WYKyHC7e7BbTm6BvYFFxa1Qo
         Kdcolr/iQej3Vii30o3fWgc2KsGVREXXK5RYrTpuLvvr1OuNkoInPrfPaluvTYuvxJSa
         EDhg==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:sender:from:to:cc:subject:date:message-id
         :in-reply-to:references;
        bh=j/OSBdV9DXY2ETWsIc3eeYNxFXzAjwLns12YdEbp9AY=;
        b=PAi2o6Pyy7S43uoaN1FrSnhO18Jz/WmLNSo0TdbpQGfo23UksLcMSd0jsZ+mGy729U
         941D1a8xD9theryhxT8YYkf36Yi2ByGYNiFgZ2mW7sW+KTyDYtl/Cb9dADJY/w5/9hqh
         MDY0vSE0QSLKqspZdxxJ6xBxJGTqOF47IMR4rkIcQK5v3NEXyAKdwo9+pOxC3A+fADfh
         FYcgRrdMdjkNXiKZXy1wKVL5Tti5X9eslqp9hU3Jxe5U/xWAIjWWtnOx6uvYRKBSxQVv
         tt0Pq+vBpvifNa0QKUHp7iKWMk20RIMaHQ7Qkbej+gqTrAyG5+Pa1XDfs+NErSCj3GuS
         Xe7A==
X-Gm-Message-State: AOAM533UroBn0w8ywsB1BbmoJeCHmD9/SnK6AaTvsYbrt5oPqpMPaW5Z
        A+5onEMSNNMmOHXscrG4uD8=
X-Google-Smtp-Source: 
 ABdhPJxdMD9Ow/MbQA5IBOhG4NQb6JObw/P1+wDSKXEqd0lzf7a0RORVeuumSrXi6/C2J3J3mZsn6A==
X-Received: by 2002:aa7:8754:: with SMTP id g20mr15026pfo.236.1589279479065;
        Tue, 12 May 2020 03:31:19 -0700 (PDT)
Received: from software.domain.org (28.144.92.34.bc.googleusercontent.com.
 [34.92.144.28])
        by smtp.gmail.com with ESMTPSA id
 q11sm11617094pfl.97.2020.05.12.03.31.16
        (version=TLS1_2 cipher=ECDHE-ECDSA-AES128-GCM-SHA256 bits=128/128);
        Tue, 12 May 2020 03:31:18 -0700 (PDT)
From: Huacai Chen <chenhc@lemote.com>
To: Paolo Bonzini <pbonzini@redhat.com>,
        Thomas Bogendoerfer <tsbogend@alpha.franken.de>,
        Aleksandar Markovic <aleksandar.qemu.devel@gmail.com>
Cc: kvm@vger.kernel.org, linux-mips@vger.kernel.org,
        Fuxin Zhang <zhangfx@lemote.com>,
        Huacai Chen <chenhuacai@gmail.com>,
        Jiaxun Yang <jiaxun.yang@flygoat.com>,
        Xing Li <lixing@loongson.cn>, stable@vger.kernel.org,
        Huacai Chen <chenhc@lemote.com>
Subject: [PATCH V4 01/14] KVM: MIPS: Define KVM_ENTRYHI_ASID to
 cpu_asid_mask(&boot_cpu_data)
Date: Tue, 12 May 2020 18:31:07 +0800
Message-Id: <1589279480-27722-2-git-send-email-chenhc@lemote.com>
X-Mailer: git-send-email 2.7.0
In-Reply-To: <1589279480-27722-1-git-send-email-chenhc@lemote.com>
References: <1589279480-27722-1-git-send-email-chenhc@lemote.com>
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Xing Li <lixing@loongson.cn>

The code in decode_config4() of arch/mips/kernel/cpu-probe.c

        asid_mask = MIPS_ENTRYHI_ASID;
        if (config4 & MIPS_CONF4_AE)
                asid_mask |= MIPS_ENTRYHI_ASIDX;
        set_cpu_asid_mask(c, asid_mask);

set asid_mask to cpuinfo->asid_mask.

So in order to support variable ASID_MASK, KVM_ENTRYHI_ASID should also
be changed to cpu_asid_mask(&boot_cpu_data).

Cc: stable@vger.kernel.org
Reviewed-by: Aleksandar Markovic <aleksandar.qemu.devel@gmail.com>
Signed-off-by: Xing Li <lixing@loongson.cn>
[Huacai: Change current_cpu_data to boot_cpu_data for optimization]
Signed-off-by: Huacai Chen <chenhc@lemote.com>
---
 arch/mips/include/asm/kvm_host.h | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
#### [kvm-unit-tests PATCH] Always compile the kvm-unit-tests with -fno-common
##### From: Thomas Huth <thuth@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Thomas Huth <thuth@redhat.com>
X-Patchwork-Id: 11542803
Return-Path: <SRS0=B8Dm=62=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 0110515E6
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 12 May 2020 09:55:57 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id DC91220733
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 12 May 2020 09:55:56 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="hZyLH+Ko"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727859AbgELJzz (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 12 May 2020 05:55:55 -0400
Received: from us-smtp-1.mimecast.com ([205.139.110.61]:29122 "EHLO
        us-smtp-delivery-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S1725889AbgELJzz (ORCPT
        <rfc822;kvm@vger.kernel.org>); Tue, 12 May 2020 05:55:55 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1589277354;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc; bh=Cwzs7ZbyONiuQyNUGXZ9NLj8Z/LVym301E7C5sI+GWA=;
        b=hZyLH+KoyhhiIsFg64ibeehX3BypGlSo8lHqsLXAqJzKd1l0jyecPdKZ1dVTVy0ypf5Xt1
        WV+3iDHITwcwbQ2B6g7feTIs+xCMfBdI0MggAKcANX8EfDYcCicyZOB6MbofXUNr+esUUc
        aYh3sWYPWi6e8af+jQ/eeAkEZAC6SJ0=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-100-0WQcdyPhNnivVmvrAqqiqA-1; Tue, 12 May 2020 05:55:52 -0400
X-MC-Unique: 0WQcdyPhNnivVmvrAqqiqA-1
Received: from smtp.corp.redhat.com (int-mx06.intmail.prod.int.phx2.redhat.com
 [10.5.11.16])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id BD29318A076C
        for <kvm@vger.kernel.org>; Tue, 12 May 2020 09:55:51 +0000 (UTC)
Received: from thuth.com (ovpn-112-112.ams2.redhat.com [10.36.112.112])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 4EB6F5C1D3;
        Tue, 12 May 2020 09:55:49 +0000 (UTC)
From: Thomas Huth <thuth@redhat.com>
To: kvm@vger.kernel.org, Paolo Bonzini <pbonzini@redhat.com>
Cc: dgilbert@redhat.com
Subject: [kvm-unit-tests PATCH] Always compile the kvm-unit-tests with
 -fno-common
Date: Tue, 12 May 2020 11:55:46 +0200
Message-Id: <20200512095546.25602-1-thuth@redhat.com>
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.16
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The new GCC v10 uses -fno-common by default. To avoid that we commit
code that declares global variables twice and thus fails to link with
the latest version, we should also compile with -fno-common when using
older versions of the compiler.

Signed-off-by: Thomas Huth <thuth@redhat.com>
---
 Makefile | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
#### [kvm-unit-tests v3 PATCH] Fixes for the umip test
##### From: Thomas Huth <thuth@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 8bit
X-Patchwork-Submitter: Thomas Huth <thuth@redhat.com>
X-Patchwork-Id: 11542799
Return-Path: <SRS0=B8Dm=62=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id EAAD2912
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 12 May 2020 09:44:48 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id D2ED020661
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 12 May 2020 09:44:48 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="LINTnhq6"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728085AbgELJor (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 12 May 2020 05:44:47 -0400
Received: from us-smtp-1.mimecast.com ([205.139.110.61]:21344 "EHLO
        us-smtp-delivery-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S1726187AbgELJor (ORCPT
        <rfc822;kvm@vger.kernel.org>); Tue, 12 May 2020 05:44:47 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1589276686;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:content-type:content-type:
         content-transfer-encoding:content-transfer-encoding;
        bh=AlBBtiFsBQAYEIktUSByiopncaRspUIywvSAFY/TY4Q=;
        b=LINTnhq6nGu8SLJCHTR9ZubOZ8DSrL1XBNYl9+HaK9VW9/wv9ov53dtgkgD9RvnHfvXVi0
        m7OJ61NwZYLuywrQ9RdhbheUfohiLWQ6nYPnGXK0RRfNkvGaS35mjzYd6Ty4llxKdMqIxo
        Fttz7Y/GHKcENIlQYgG4uc1lo69xyGE=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-346-ZJtHkdEHOg2fPbSVxa7bZg-1; Tue, 12 May 2020 05:44:44 -0400
X-MC-Unique: ZJtHkdEHOg2fPbSVxa7bZg-1
Received: from smtp.corp.redhat.com (int-mx06.intmail.prod.int.phx2.redhat.com
 [10.5.11.16])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id DF051835B46
        for <kvm@vger.kernel.org>; Tue, 12 May 2020 09:44:43 +0000 (UTC)
Received: from thuth.com (ovpn-112-112.ams2.redhat.com [10.36.112.112])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 0B6625C1B5;
        Tue, 12 May 2020 09:44:41 +0000 (UTC)
From: Thomas Huth <thuth@redhat.com>
To: kvm@vger.kernel.org, Paolo Bonzini <pbonzini@redhat.com>
Cc: Vitaly Kuznetsov <vkuznets@redhat.com>
Subject: [kvm-unit-tests v3 PATCH] Fixes for the umip test
Date: Tue, 12 May 2020 11:44:38 +0200
Message-Id: <20200512094438.17998-1-thuth@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.16
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

When compiling umip.c with -O2 instead of -O1, there are currently
two problems. First, the compiler complains:

 x86/umip.c: In function ‘do_ring3’:
 x86/umip.c:162:37: error: array subscript 4096 is above array bounds of
    ‘unsigned char[4096]’ [-Werror=array-bounds]
       [user_stack_top]"m"(user_stack[sizeof user_stack]),
                           ~~~~~~~~~~^~~~~~~~~~~~~~~~~~~

This can be fixed by initializing the stack to point to one of the last
bytes of the array instead.

The second problem is that some tests are failing - and this is due
to the fact that the GP_ASM macro uses inline asm without the "volatile"
keyword - so that the compiler reorders this code in certain cases
where it should not. Fix it by adding "volatile" here.

Reviewed-by: Vitaly Kuznetsov <vkuznets@redhat.com>
Signed-off-by: Thomas Huth <thuth@redhat.com>
---
 v3: Use "sizeof(long)" instead of "2"

 x86/umip.c | 6 ++++--
 1 file changed, 4 insertions(+), 2 deletions(-)

```
#### [PATCH v4 36/38] samples: vfio-mdev/mbochs: fix common struct sg_table related issues
##### From: Marek Szyprowski <m.szyprowski@samsung.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Marek Szyprowski <m.szyprowski@samsung.com>
X-Patchwork-Id: 11542579
Return-Path: <SRS0=B8Dm=62=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id D5556139F
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 12 May 2020 09:01:35 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id B770C2082E
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 12 May 2020 09:01:35 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=samsung.com header.i=@samsung.com
 header.b="j++Gxhxx"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729652AbgELJBe (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 12 May 2020 05:01:34 -0400
Received: from mailout2.w1.samsung.com ([210.118.77.12]:40683 "EHLO
        mailout2.w1.samsung.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1729631AbgELJBd (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 12 May 2020 05:01:33 -0400
Received: from eucas1p1.samsung.com (unknown [182.198.249.206])
        by mailout2.w1.samsung.com (KnoxPortal) with ESMTP id
 20200512090129euoutp021913e343b17af44d4869a9edd6a87220~OPF1MbZnV0523105231euoutp02j
        for <kvm@vger.kernel.org>; Tue, 12 May 2020 09:01:29 +0000 (GMT)
DKIM-Filter: OpenDKIM Filter v2.11.0 mailout2.w1.samsung.com
 20200512090129euoutp021913e343b17af44d4869a9edd6a87220~OPF1MbZnV0523105231euoutp02j
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=samsung.com;
        s=mail20170921; t=1589274089;
        bh=E1NfBBxSojUDLapgMB8Y02kKeGolZNH/an6hkCuIGIw=;
        h=From:To:Cc:Subject:Date:In-Reply-To:References:From;
        b=j++GxhxxYfM+r97XJyq3crmV1wh9UHsrUuYP5jz3KXE0uNJs18EY/ymxDbrZHSJc0
         90/79NoA5mByXgeBL8Lc+TlVx5AFpjovZhhMJuC9QLjJvcQi3RxOQd9MtM6QdIBNS3
         Olx/BkrKLEOJHSiwyniJdAY5X4y1iMpUthxgjTx4=
Received: from eusmges1new.samsung.com (unknown [203.254.199.242]) by
        eucas1p2.samsung.com (KnoxPortal) with ESMTP id
        20200512090129eucas1p2e54bcc15c8de5a27e05eb20ec668d4ef~OPF06qyG02180321803eucas1p2C;
        Tue, 12 May 2020 09:01:29 +0000 (GMT)
Received: from eucas1p1.samsung.com ( [182.198.249.206]) by
        eusmges1new.samsung.com (EUCPMTA) with SMTP id 3F.67.61286.9E56ABE5;
 Tue, 12
        May 2020 10:01:29 +0100 (BST)
Received: from eusmtrp1.samsung.com (unknown [182.198.249.138]) by
        eucas1p2.samsung.com (KnoxPortal) with ESMTPA id
        20200512090129eucas1p2e67c8a9adafb202970a59c3412cd887a~OPF0orOhz2661826618eucas1p2n;
        Tue, 12 May 2020 09:01:29 +0000 (GMT)
Received: from eusmgms2.samsung.com (unknown [182.198.249.180]) by
        eusmtrp1.samsung.com (KnoxPortal) with ESMTP id
        20200512090129eusmtrp1cc27ec6d1a740863c5c174195c999886~OPF0n7TdP0188101881eusmtrp1f;
        Tue, 12 May 2020 09:01:29 +0000 (GMT)
X-AuditID: cbfec7f2-ef1ff7000001ef66-b4-5eba65e97ca9
Received: from eusmtip1.samsung.com ( [203.254.199.221]) by
        eusmgms2.samsung.com (EUCPMTA) with SMTP id AC.03.07950.9E56ABE5;
 Tue, 12
        May 2020 10:01:29 +0100 (BST)
Received: from AMDC2765.digital.local (unknown [106.120.51.73]) by
        eusmtip1.samsung.com (KnoxPortal) with ESMTPA id
        20200512090128eusmtip14ace71a0d963c54a40acb63ce54fcc29~OPF0Csyzt1181011810eusmtip1w;
        Tue, 12 May 2020 09:01:28 +0000 (GMT)
From: Marek Szyprowski <m.szyprowski@samsung.com>
To: dri-devel@lists.freedesktop.org, iommu@lists.linux-foundation.org,
        linaro-mm-sig@lists.linaro.org, linux-kernel@vger.kernel.org
Cc: Marek Szyprowski <m.szyprowski@samsung.com>,
        Christoph Hellwig <hch@lst.de>,
        Robin Murphy <robin.murphy@arm.com>,
        Bartlomiej Zolnierkiewicz <b.zolnierkie@samsung.com>,
        linux-arm-kernel@lists.infradead.org,
        David Airlie <airlied@linux.ie>,
        Daniel Vetter <daniel@ffwll.ch>,
        Kirti Wankhede <kwankhede@nvidia.com>, kvm@vger.kernel.org
Subject: [PATCH v4 36/38] samples: vfio-mdev/mbochs: fix common struct
 sg_table related issues
Date: Tue, 12 May 2020 11:00:56 +0200
Message-Id: <20200512090058.14910-36-m.szyprowski@samsung.com>
X-Mailer: git-send-email 2.17.1
In-Reply-To: <20200512090058.14910-1-m.szyprowski@samsung.com>
X-Brightmail-Tracker: 
 H4sIAAAAAAAAA+NgFtrCKsWRmVeSWpSXmKPExsWy7djPc7ovU3fFGXyerWTRe+4kk8XGGetZ
        Lf5vm8hsceXrezaLlauPMlks2G9tMWdqocWW03MZLb5cechksenxNVaLy7vmsFmsPXKX3eLg
        hyesDrwea+atYfTY+20Bi8f2bw9YPe53H2fy2Lyk3uP2v8fMHpNvLGf02H2zgc2jt/kdm0ff
        llWMHp83yQVwR3HZpKTmZJalFunbJXBlHGvkLLglVDG9o5+tgfEyfxcjJ4eEgInE3NVTWEBs
        IYEVjBIr7ll0MXIB2V8YJZaffcYO4XxmlHi9dCkTTMfMl/uhEssZJT6/fMIM13J0/RRGkCo2
        AUOJrrddbCC2iEAro8SJXh6QImaBa0wSb/++Y+1i5OAQFkiQWP+aG6SGRUBV4lnXNLBeXgE7
        idYFzewQ2+QlVm84wAxicwLF78//wwIyR0LgELvEm3MXmSGKXCRa1v6HOk9Y4tXxLVDNMhKn
        J/dANTQzSjw8t5YdwulhlLjcNIMRospa4s65X2wgFzELaEqs36UPEXaUeHvyKBNIWEKAT+LG
        W0GQMDOQOWnbdGaIMK9ER5sQRLWaxKzj6+DWHrxwCeo0D4lDX+axQQLoKKPEnrMvmCcwys9C
        WLaAkXEVo3hqaXFuemqxYV5quV5xYm5xaV66XnJ+7iZGYFo6/e/4px2MXy8lHWIU4GBU4uHt
        MNoZJ8SaWFZcmXuIUYKDWUmEtyUTKMSbklhZlVqUH19UmpNafIhRmoNFSZzXeNHLWCGB9MSS
        1OzU1ILUIpgsEwenVANj38EnC+87sVhn8htIVHO7zDLco1Jz2cp2+T0Z3wMPdG+deLL81INN
        DD9jVe26uD0FcmfNUOXVz8049rFQ+bpJ7dnPqsJcHoViXKFe5hMK1eO3hW3uilv528p9QmWO
        s+6LVSf3ty8+cOHMQp/Dh881aRzf80/EO/fO6SaOmrO6v38+nqnLy1ahxFKckWioxVxUnAgA
        Y96ihUcDAAA=
X-Brightmail-Tracker: 
 H4sIAAAAAAAAA+NgFprKIsWRmVeSWpSXmKPExsVy+t/xu7ovU3fFGazp5bfoPXeSyWLjjPWs
        Fv+3TWS2uPL1PZvFytVHmSwW7Le2mDO10GLL6bmMFl+uPGSy2PT4GqvF5V1z2CzWHrnLbnHw
        wxNWB16PNfPWMHrs/baAxWP7twesHve7jzN5bF5S73H732Nmj8k3ljN67L7ZwObR2/yOzaNv
        yypGj8+b5AK4o/RsivJLS1IVMvKLS2yVog0tjPQMLS30jEws9QyNzWOtjEyV9O1sUlJzMstS
        i/TtEvQyjjVyFtwSqpje0c/WwHiZv4uRk0NCwERi5sv97F2MXBxCAksZJf5P2ccOkZCRODmt
        gRXCFpb4c62LDcQWEvjEKLHmRiGIzSZgKNH1FiTOxSEi0MkoMa37I1gzs8A9Jom96/xAbGGB
        OIkT+1eBDWIRUJV41jWNEcTmFbCTaF3QDLVMXmL1hgPMIDYnUPz+/D8sEMsKJR5dfcsygZFv
        ASPDKkaR1NLi3PTcYiO94sTc4tK8dL3k/NxNjMAo2Xbs55YdjF3vgg8xCnAwKvHwdhjtjBNi
        TSwrrsw9xCjBwawkwtuSCRTiTUmsrEotyo8vKs1JLT7EaAp01ERmKdHkfGAE55XEG5oamltY
        GpobmxubWSiJ83YIHIwREkhPLEnNTk0tSC2C6WPi4JRqYJx4rCTj8sS0OqO3sY+XX356vPtV
        +PfVNmcmXtL+4rhp4V3D43yL8y6y1G/bs1vnzNRSkz7267tSP8g1fWK4dWlhyGLx5t981sGM
        RYLqTEdC1TJbFVyUGZXNnm8+Ncd8ue18Z9ddc9lOn/658dK6i/5+oT8fCPXtPdpQ/bN9f6rs
        KYuAJXZcakJKLMUZiYZazEXFiQCA1aSZqAIAAA==
X-CMS-MailID: 20200512090129eucas1p2e67c8a9adafb202970a59c3412cd887a
X-Msg-Generator: CA
X-RootMTR: 20200512090129eucas1p2e67c8a9adafb202970a59c3412cd887a
X-EPHeader: CA
CMS-TYPE: 201P
X-CMS-RootMailID: 20200512090129eucas1p2e67c8a9adafb202970a59c3412cd887a
References: <20200512085710.14688-1-m.szyprowski@samsung.com>
        <20200512090058.14910-1-m.szyprowski@samsung.com>
        <CGME20200512090129eucas1p2e67c8a9adafb202970a59c3412cd887a@eucas1p2.samsung.com>
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The Documentation/DMA-API-HOWTO.txt states that the dma_map_sg() function
returns the number of the created entries in the DMA address space.
However the subsequent calls to the dma_sync_sg_for_{device,cpu}() and
dma_unmap_sg must be called with the original number of the entries
passed to the dma_map_sg().

struct sg_table is a common structure used for describing a non-contiguous
memory buffer, used commonly in the DRM and graphics subsystems. It
consists of a scatterlist with memory pages and DMA addresses (sgl entry),
as well as the number of scatterlist entries: CPU pages (orig_nents entry)
and DMA mapped pages (nents entry).

It turned out that it was a common mistake to misuse nents and orig_nents
entries, calling DMA-mapping functions with a wrong number of entries or
ignoring the number of mapped entries returned by the dma_map_sg()
function.

To avoid such issues, lets use a common dma-mapping wrappers operating
directly on the struct sg_table objects and use scatterlist page
iterators where possible. This, almost always, hides references to the
nents and orig_nents entries, making the code robust, easier to follow
and copy/paste safe.

While touching this code, also add missing call to dma_unmap_sgtable.

Signed-off-by: Marek Szyprowski <m.szyprowski@samsung.com>
---
For more information, see '[PATCH v4 00/38] DRM: fix struct sg_table nents
vs. orig_nents misuse' thread:
https://lore.kernel.org/dri-devel/20200512085710.14688-1-m.szyprowski@samsung.com/T/
---
 samples/vfio-mdev/mbochs.c | 3 ++-
 1 file changed, 2 insertions(+), 1 deletion(-)

```
#### [PATCH v4 1/6] scripts/qemugdb: Remove shebang header
##### From: =?utf-8?q?Philippe_Mathieu-Daud=C3=A9?= <philmd@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 8bit
X-Patchwork-Submitter: =?utf-8?q?Philippe_Mathieu-Daud=C3=A9?=
 <philmd@redhat.com>
X-Patchwork-Id: 11542877
Return-Path: <SRS0=B8Dm=62=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id A38C381
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 12 May 2020 10:32:52 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 8BEB520731
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 12 May 2020 10:32:52 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="YTX1vGjc"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729529AbgELKcv (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 12 May 2020 06:32:51 -0400
Received: from us-smtp-delivery-1.mimecast.com ([207.211.31.120]:34903 "EHLO
        us-smtp-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org
        with ESMTP id S1729429AbgELKcu (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 12 May 2020 06:32:50 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1589279569;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
  content-type:content-type:content-type:
         content-transfer-encoding:content-transfer-encoding:
         in-reply-to:in-reply-to:references:references;
        bh=o+SFxNiQTSKSfzcy81S2xitOyf6spOQEd9fCWLhnCeY=;
        b=YTX1vGjcF6s24R7sSz0yGitSRFfWV6lJFWD7VA0ILNRdtZJVYnpcYAb63Bwpqe0ooJpjwJ
        9yFuWJ9lS4ywgqj+sV1msAbaTf/DsBqeI7M2evwYYWuWTQYrgNH7K5G/DTUoTjp0DYKVXj
        LTvCIQUWjsn/Icl4+tdjFI/4pAQbvuA=
Received: from mail-wm1-f71.google.com (mail-wm1-f71.google.com
 [209.85.128.71]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-239-MgccDOUEOceGvkulRkuBgg-1; Tue, 12 May 2020 06:32:48 -0400
X-MC-Unique: MgccDOUEOceGvkulRkuBgg-1
Received: by mail-wm1-f71.google.com with SMTP id e15so935652wme.1
        for <kvm@vger.kernel.org>; Tue, 12 May 2020 03:32:47 -0700 (PDT)
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:in-reply-to
         :references:mime-version:content-transfer-encoding;
        bh=o+SFxNiQTSKSfzcy81S2xitOyf6spOQEd9fCWLhnCeY=;
        b=gm/gYdwMAhiOyAP8GaPYC80pouJUjd51ZlV7iF9ot7Yvz9+hDQ7+4LaSUrG5yu3Qt/
         hrR3efkI9WjoPAI2XQc9bDeqIyfR1w7BZkrKTk2qAKzAoOvMKaCxE5c0XKfwISi/KdfH
         QoGA4TddStjCsNuVsEUBl2hQi/tpzNw2nRmicqTMb2DSvmnesQ5Qw0Ic5O98PEM6Dov/
         HVO1veenmRc9pRdEaMYP9KxbZRwYuV/WTno80mSeDWLKo5QrhPtBfXweNQD8e/CGUy8U
         0LWZVt8b9g/uhGquA6mxMrAUWAKNXFX64c9/cDsgrV9TLV+MSgt8Eacz2l3ctewIqOV5
         yHiA==
X-Gm-Message-State: AGi0PuYVdB/vbf+b0WTzPsCBkh+aNwNoIDNnGC8U0cQvwCCDmPcO9iJL
        dJND69jLCUCvoJrE3s3AuE7lpnMInhjWsvXSP9qUn1OXZJO3h3l/SGML37mpk4uXP+JGbTlNXoi
        PdAS0DLoQQ0tJ
X-Received: by 2002:adf:cc81:: with SMTP id p1mr23275929wrj.192.1589279565427;
        Tue, 12 May 2020 03:32:45 -0700 (PDT)
X-Google-Smtp-Source: 
 APiQypIdq6xklNhE6zF2ex6riiZ2WEeaRBZwdbLSVo8fxAyW06Ghhyjcwp0kiKh5i+SK1pgUYQQIhQ==
X-Received: by 2002:adf:cc81:: with SMTP id p1mr23275905wrj.192.1589279565172;
        Tue, 12 May 2020 03:32:45 -0700 (PDT)
Received: from x1w.redhat.com (17.red-88-21-202.staticip.rima-tde.net.
 [88.21.202.17])
        by smtp.gmail.com with ESMTPSA id
 u16sm21863464wrq.17.2020.05.12.03.32.43
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Tue, 12 May 2020 03:32:44 -0700 (PDT)
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
 Fam Zheng <fam@euphon.net>,
 =?utf-8?q?Philippe_Mathieu-Daud=C3=A9?= <f4bug@amsat.org>
Subject: [PATCH v4 1/6] scripts/qemugdb: Remove shebang header
Date: Tue, 12 May 2020 12:32:33 +0200
Message-Id: <20200512103238.7078-2-philmd@redhat.com>
X-Mailer: git-send-email 2.21.3
In-Reply-To: <20200512103238.7078-1-philmd@redhat.com>
References: <20200512103238.7078-1-philmd@redhat.com>
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Philippe Mathieu-Daudé <f4bug@amsat.org>

These scripts are loaded as plugin by GDB (and they don't
have any __main__ entry point). Remove the shebang header.

Acked-by: Alex Bennée <alex.bennee@linaro.org>
Signed-off-by: Philippe Mathieu-Daudé <f4bug@amsat.org>
---
 scripts/qemugdb/__init__.py  | 3 +--
 scripts/qemugdb/aio.py       | 3 +--
 scripts/qemugdb/coroutine.py | 3 +--
 scripts/qemugdb/mtree.py     | 4 +---
 scripts/qemugdb/tcg.py       | 1 -
 scripts/qemugdb/timers.py    | 1 -
 6 files changed, 4 insertions(+), 11 deletions(-)

```
#### [PATCH v27 01/10] acpi: nvdimm: change NVDIMM_UUID_LE to a common macro
##### From: Dongjiu Geng <gengdongjiu@huawei.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Dongjiu Geng <gengdongjiu@huawei.com>
X-Patchwork-Id: 11541979
Return-Path: <SRS0=B8Dm=62=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 94B3A912
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 12 May 2020 03:03:27 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 85DB120722
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 12 May 2020 03:03:27 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728697AbgELDDW (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 11 May 2020 23:03:22 -0400
Received: from szxga06-in.huawei.com ([45.249.212.32]:51866 "EHLO huawei.com"
        rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org with ESMTP
        id S1728633AbgELDDV (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 11 May 2020 23:03:21 -0400
Received: from DGGEMS413-HUB.china.huawei.com (unknown [172.30.72.60])
        by Forcepoint Email with ESMTP id A1BB893D52E1A0235995;
        Tue, 12 May 2020 11:03:11 +0800 (CST)
Received: from huawei.com (10.151.151.243) by DGGEMS413-HUB.china.huawei.com
 (10.3.19.213) with Microsoft SMTP Server id 14.3.487.0; Tue, 12 May 2020
 11:03:04 +0800
From: Dongjiu Geng <gengdongjiu@huawei.com>
To: <imammedo@redhat.com>, <mst@redhat.com>,
        <xiaoguangrong.eric@gmail.com>, <peter.maydell@linaro.org>,
        <shannon.zhaosl@gmail.com>, <fam@euphon.net>, <rth@twiddle.net>,
        <ehabkost@redhat.com>, <mtosatti@redhat.com>,
        <qemu-devel@nongnu.org>, <kvm@vger.kernel.org>,
        <qemu-arm@nongnu.org>, <pbonzini@redhat.com>, <philmd@redhat.com>
CC: <gengdongjiu@huawei.com>, <zhengxiang9@huawei.com>,
        <Jonathan.Cameron@huawei.com>, <linuxarm@huawei.com>
Subject: [PATCH v27 01/10] acpi: nvdimm: change NVDIMM_UUID_LE to a common
 macro
Date: Tue, 12 May 2020 11:06:00 +0800
Message-ID: <20200512030609.19593-2-gengdongjiu@huawei.com>
X-Mailer: git-send-email 2.17.1
In-Reply-To: <20200512030609.19593-1-gengdongjiu@huawei.com>
References: <20200512030609.19593-1-gengdongjiu@huawei.com>
MIME-Version: 1.0
X-Originating-IP: [10.151.151.243]
X-CFilter-Loop: Reflected
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The little end UUID is used in many places, so make
NVDIMM_UUID_LE to a common macro to convert the UUID
to a little end array.

Reviewed-by: Xiang Zheng <zhengxiang9@huawei.com>
Signed-off-by: Dongjiu Geng <gengdongjiu@huawei.com>
---
Change since v25:
1. Address Peter's comments to add a proper doc-comment comment for
   UUID_LE macros.
---
 hw/acpi/nvdimm.c    | 10 +++-------
 include/qemu/uuid.h | 27 +++++++++++++++++++++++++++
 2 files changed, 30 insertions(+), 7 deletions(-)

```
#### [PATCH V2] ifcvf: move IRQ request/free to status change handlers
##### From: Zhu Lingshan <lingshan.zhu@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Zhu Lingshan <lingshan.zhu@intel.com>
X-Patchwork-Id: 11542293
Return-Path: <SRS0=B8Dm=62=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 1E7921668
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 12 May 2020 08:04:33 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 1016820733
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 12 May 2020 08:04:33 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729172AbgELIE2 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 12 May 2020 04:04:28 -0400
Received: from mga09.intel.com ([134.134.136.24]:16642 "EHLO mga09.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1725889AbgELIE2 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 12 May 2020 04:04:28 -0400
IronPort-SDR: 
 R5SmQ3kmTPq6HPPgtP2oO9PIyWC4dIGuFOk5vjf2nlX7XbwizYxIMoY+5K0xXPqIa0tgMno0Pu
 y+fAsEzkExug==
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from fmsmga001.fm.intel.com ([10.253.24.23])
  by orsmga102.jf.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 12 May 2020 01:04:27 -0700
IronPort-SDR: 
 j2VzWrkRB3i7RK2vI6S/dogEsgbXubtrfoZ0GW9bCf5uuIeUBkwMutmeeCOX9hckYFWHZd8zvI
 tFt2Tv4mP3uA==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.73,383,1583222400";
   d="scan'208";a="371486433"
Received: from unknown (HELO localhost.localdomain.bj.intel.com)
 ([10.240.192.105])
  by fmsmga001.fm.intel.com with ESMTP; 12 May 2020 01:04:24 -0700
From: Zhu Lingshan <lingshan.zhu@intel.com>
To: mst@redhat.com, kvm@vger.kernel.org,
        virtualization@lists.linux-foundation.org,
        linux-kernel@vger.kernel.org, netdev@vger.kernel.org,
        jasowang@redhat.com
Cc: lulu@redhat.com, dan.daly@intel.com, cunming.liang@intel.com,
        Zhu Lingshan <lingshan.zhu@intel.com>
Subject: [PATCH V2] ifcvf: move IRQ request/free to status change handlers
Date: Tue, 12 May 2020 16:00:44 +0800
Message-Id: <1589270444-3669-1-git-send-email-lingshan.zhu@intel.com>
X-Mailer: git-send-email 1.8.3.1
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This commit move IRQ request and free operations from probe()
to VIRTIO status change handler to comply with VIRTIO spec.

VIRTIO spec 1.1, section 2.1.2 Device Requirements: Device Status Field
The device MUST NOT consume buffers or send any used buffer
notifications to the driver before DRIVER_OK.

Signed-off-by: Zhu Lingshan <lingshan.zhu@intel.com>
---
changes from V1:
remove ifcvf_stop_datapath() in status == 0 handler, we don't need to do this
twice; handle status == 0 after DRIVER_OK -> !DRIVER_OK handler (Jason Wang)

 drivers/vdpa/ifcvf/ifcvf_main.c | 120 ++++++++++++++++++++++++----------------
 1 file changed, 73 insertions(+), 47 deletions(-)

```
#### [PATCH v2] kvm/x86 : Remove redundant function implementThread-Topic: [PATCH v2] kvm/x86 : Remove redundant function implement
##### From: =?eucgb2312_cn?b?xe26xihSaWNoYXJkKQ==?= <richard.peng@oppo.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: =?utf-8?b?5b2t5rWpKFJpY2hhcmQp?=
 <richard.peng@oppo.com>
X-Patchwork-Id: 11542985
Return-Path: <SRS0=B8Dm=62=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 095C8912
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 12 May 2020 11:03:16 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id DF985206A3
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 12 May 2020 11:03:15 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=oppoglobal.onmicrosoft.com
 header.i=@oppoglobal.onmicrosoft.com header.b="HTGPSVnR"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729294AbgELLDE (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 12 May 2020 07:03:04 -0400
Received: from mail-eopbgr1300059.outbound.protection.outlook.com
 ([40.107.130.59]:9521
        "EHLO APC01-HK2-obe.outbound.protection.outlook.com"
        rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org with ESMTP
        id S1727783AbgELLDD (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 12 May 2020 07:03:03 -0400
ARC-Seal: i=1; a=rsa-sha256; s=arcselector9901; d=microsoft.com; cv=none;
 b=mlHoNdVWnv0Fa0r3A0utGCyROaMrURTIeuBJYNjvPNpXj30YbqpQj5JHNMIAsQEeOL7aDQ+yqRIAeGej3f7U08scFIbRuRNyZm17iYom2JWyNYg1QyVSEc8u0tFwmgidOFW6RXxsfN823ufYE0tABiIj4et2rq5JXCRZjGdUe/aTHZT58lo3a9Xk/B9qMFjdUwJPjz90lV+GeGYDmftWK9bw5/rm9FONo/Kl0XwlhbqIMrLOptisuNOR/+FEc40AAf+jAoGoIkOKMhX97lwD09k1SDpi4khXw45OHEJ/FKuychh3TwE+SjoXMaPcp+IDz8bv/ld005zEgvbLP/WvmA==
ARC-Message-Signature: i=1; a=rsa-sha256; c=relaxed/relaxed; d=microsoft.com;
 s=arcselector9901;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=9+mNRqUwfmUoId8N83J4eXXZQmVldvgJiRRQpdxSnTs=;
 b=XOsdcOjYeSKthB9EC+5pKpyjw+UrynggpSzrwD3ViRPXHAfGYBseQs40KWDyh7aaDESqiYK5O7zQsbIbf55KWl5DI0y5qDMonX9PjZaugQ/LuoRbnmiR9uVYN88h34Giidw1PQKDGVwJ2z2xeA31q44wYE9rLPUdg2l4BgkIFjSuxTIz7uS+lA6kz6fX5iJJbJt12BD8amUap8dRWdLK9KwDdw3kKMdyXr4fple5zoyN4gqte2B6a/u1wFp2ZPBbwU6lb5uN6LiY6qbuLT9XKWiV1kA3Y4uQjOUuL0hI4F9pB7tHwy8CLYYr5YxDnWfDXRVlZj7lcdpj8p26dejqNw==
ARC-Authentication-Results: i=1; mx.microsoft.com 1; spf=pass
 smtp.mailfrom=oppo.com; dmarc=pass action=none header.from=oppo.com;
 dkim=pass header.d=oppo.com; arc=none
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
 d=oppoglobal.onmicrosoft.com; s=selector1-oppoglobal-onmicrosoft-com;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=9+mNRqUwfmUoId8N83J4eXXZQmVldvgJiRRQpdxSnTs=;
 b=HTGPSVnRK4ltqTDGsckdueir87UBT1WVSBkgl9Qj+VF1SqUZGksoZDrw5XYowFaO2FW0auz/t6yHzixR97D/HExb8voBZF6kghfrgpv3grAynzpoJORZEZuc901tIh208OMNX8JsruMPPhXSHcFfyI6eBbuasdSLeZeZK9eZI2k=
Received: from HKAPR02MB4291.apcprd02.prod.outlook.com (2603:1096:203:d3::12)
 by HKAPR02MB4308.apcprd02.prod.outlook.com (2603:1096:203:dd::8) with
 Microsoft SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.2979.28; Tue, 12 May
 2020 11:02:58 +0000
Received: from HKAPR02MB4291.apcprd02.prod.outlook.com
 ([fe80::80ca:c698:988e:a999]) by HKAPR02MB4291.apcprd02.prod.outlook.com
 ([fe80::80ca:c698:988e:a999%5]) with mapi id 15.20.2979.033; Tue, 12 May 2020
 11:02:57 +0000
From: =?eucgb2312_cn?b?xe26xihSaWNoYXJkKQ==?= <richard.peng@oppo.com>
To: Paolo Bonzini <pbonzini@redhat.com>
CC: "linux-kernel@vger.kernel.org" <linux-kernel@vger.kernel.org>,
        "kvm@vger.kernel.org" <kvm@vger.kernel.org>
Subject: [PATCH v2] kvm/x86 : Remove redundant function implement
Thread-Topic: [PATCH v2] kvm/x86 : Remove redundant function implement
Thread-Index: AdYoTDpIz7AFtnDsRCiyAgzxuRMr2g==
Date: Tue, 12 May 2020 11:02:56 +0000
Message-ID: 
 <HKAPR02MB4291B0991BF57A5CCB1C7437E0BE0@HKAPR02MB4291.apcprd02.prod.outlook.com>
Accept-Language: zh-CN, en-US
Content-Language: zh-CN
X-MS-Has-Attach: 
X-MS-TNEF-Correlator: 
authentication-results: redhat.com; dkim=none (message not signed)
 header.d=none;redhat.com; dmarc=none action=none header.from=oppo.com;
x-originating-ip: [58.255.79.102]
x-ms-publictraffictype: Email
x-ms-office365-filtering-correlation-id: 6b97a50f-9945-4101-81ed-08d7f6640703
x-ms-traffictypediagnostic: HKAPR02MB4308:
x-microsoft-antispam-prvs: 
 <HKAPR02MB4308CA3DE6683B45FA521EB4E0BE0@HKAPR02MB4308.apcprd02.prod.outlook.com>
x-ms-oob-tlc-oobclassifiers: OLM:119;
x-forefront-prvs: 0401647B7F
x-ms-exchange-senderadcheck: 1
x-microsoft-antispam: BCL:0;
x-microsoft-antispam-message-info: 
 s1SLYJ7Twdo29kTyMCq+iIh4GSg7xZpjk13pu6gAte1fK5ZQd/CcZ+NLJfIlUNH+/qUzaJNhIW9PrAi5zNDof/cSzmQ99/+b3sIXNO4rCZoeBzzXu27r81K8BH1Tm5uVUZm8lUdTeMkgMS1BVbBBYZ9SnLTHUDYG0LjcSExEOEeOykL/OQjokKYHirC9XdD6r1s2ZZZeIshmjNLVmSfLXnU8Fie1T/H9l4b5LznqmlCZFZ6C+VjI/Vh/EYZ/tfj05GgGoBC6MAPgiP8dTee0Jlr92H8odxB0mbSnzT/6xnYrMoZe8ygtMPf6GuvXDIZOD0fpxgYDW+z7pIUDtoM2ej+lJFIDmN7U9YvYPvoU9PIgCki0YQ1aE1algEmldd1B7h2xKm1SBVpGVIFzhrESKK8gGiw5+TtBuok7v/g/NCLqlwRfm5+OBTQH48H6T+x5JbmFu8Lkn68mXlpQdR10BKz/SfOvcY5o6lJwb5QjueLKQVdOOhQAE5KmdSw8yBJutZuvBGupbqRHsdBenphGnq7djODH8JefmCVC8eHjfezsgbgsb1QQyX5fRG9IyfEM
x-forefront-antispam-report: 
 CIP:255.255.255.255;CTRY:;LANG:en;SCL:1;SRV:;IPV:NLI;SFV:NSPM;H:HKAPR02MB4291.apcprd02.prod.outlook.com;PTR:;CAT:NONE;SFTY:;SFS:(376002)(396003)(346002)(39860400002)(366004)(136003)(33430700001)(33440700001)(6506007)(55016002)(9686003)(52536014)(186003)(4326008)(508600001)(316002)(26005)(33656002)(7696005)(71200400001)(66946007)(86362001)(8676002)(85182001)(6916009)(64756008)(2906002)(66556008)(66476007)(8936002)(66446008)(54906003)(5660300002)(76116006)(11606004);DIR:OUT;SFP:1101;
x-ms-exchange-antispam-messagedata: 
 mVZ3ZLT+4R/tgCIaJrWWZtg4NU7TzRIPqylR66VmoYv+i0Y1N0wXTlwt3wdnmTaqiJ33x8xsUkpi/meFgF7TMVOHRmSnld+gLWKmKZT2P14xesroJm2HJ03dyBRzMtaIFk0QR5iD8KY/u2daFXmxYXe72NUUVJs6ZyN4dwYTS6Nawi4UHplEdw+TOz/iiBZxoHjzNQDenAYQ68OshLjLaMpXHHlPxO6R99nNLbcrdElwCaFUQDPGK+wvlauC9t2XR7qVlXboA7rLOdtK6+lJRrGMblwHno2mhSN1ZCXhQhKgYZwUgVbKpCcx/kmEEYJHIKCpo5kN+2hqi+Vp+zECtw7qUH5t3zeP2IBrqw5+Rc/JAi7LCGV+9QyPar4Aq6hmCooUQBZka1zQ+hBGN9fYR/ftJI30HO5Ilp3IQI+tAUSxTElW/jcWCVoXsJze7lfQoF+Jlr8PAHyOC2VqpGUN9kNi+pvnXLKDeysT9y6HVeY=
x-ms-exchange-transport-forked: True
MIME-Version: 1.0
X-OriginatorOrg: oppo.com
X-MS-Exchange-CrossTenant-Network-Message-Id: 
 6b97a50f-9945-4101-81ed-08d7f6640703
X-MS-Exchange-CrossTenant-originalarrivaltime: 12 May 2020 11:02:56.7084
 (UTC)
X-MS-Exchange-CrossTenant-fromentityheader: Hosted
X-MS-Exchange-CrossTenant-id: f1905eb1-c353-41c5-9516-62b4a54b5ee6
X-MS-Exchange-CrossTenant-mailboxtype: HOSTED
X-MS-Exchange-CrossTenant-userprincipalname: 
 4mlCwaxHDitAxkgUAFMsGxzUqrUvLtaM52pR6k9Bmt7wAKU44StF2TjtbaVj7x+XPoVf4/RJBwebUqXUKam7xA==
X-MS-Exchange-Transport-CrossTenantHeadersStamped: HKAPR02MB4308
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

pic_in_kernel(),ioapic_in_kernel() and irqchip_kernel() have the
same implementation.

Signed-off-by: Peng Hao <richard.peng@oppo.com>
---
 arch/x86/kvm/ioapic.h |  8 ++------
 arch/x86/kvm/irq.h    | 13 ++++---------
 2 files changed, 6 insertions(+), 15 deletions(-)

--
2.7.4

```
#### [PATCH] x86/hyperv: Properly suspend/resume reenlightenment notifications
##### From: Vitaly Kuznetsov <vkuznets@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Vitaly Kuznetsov <vkuznets@redhat.com>
X-Patchwork-Id: 11543491
Return-Path: <SRS0=B8Dm=62=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id B2CFE913
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 12 May 2020 16:02:03 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 9AD542054F
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 12 May 2020 16:02:03 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="FacGXlpV"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728485AbgELQCB (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 12 May 2020 12:02:01 -0400
Received: from us-smtp-1.mimecast.com ([205.139.110.61]:44281 "EHLO
        us-smtp-delivery-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S1726889AbgELQCB (ORCPT
        <rfc822;kvm@vger.kernel.org>); Tue, 12 May 2020 12:02:01 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1589299320;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=nL6n0gs44aSe+c4xP2RS6AmyhHuCE1lHHuLbFzSoNGo=;
        b=FacGXlpVTipMCzw5E65rtqe8Cs412aCVT9+1x6ZyhwGaeF4J+CDpxmQpYFhDUGd5KTAnmd
        M7lADnX1RG9DtF0el8rPIdqJ6xIDmLaye3K9L7AaQuFTHtEoR9Y3EeNM+RwP2D7za5xayx
        lvG2pcaNoGBCzswl7E6E9o+xGs4h2rk=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-428-yGbGbgOGNEWr2HXPNBc0CA-1; Tue, 12 May 2020 12:01:58 -0400
X-MC-Unique: yGbGbgOGNEWr2HXPNBc0CA-1
Received: from smtp.corp.redhat.com (int-mx02.intmail.prod.int.phx2.redhat.com
 [10.5.11.12])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 09855800687;
        Tue, 12 May 2020 16:01:57 +0000 (UTC)
Received: from vitty.brq.redhat.com (unknown [10.40.195.115])
        by smtp.corp.redhat.com (Postfix) with ESMTP id A42EE60C05;
        Tue, 12 May 2020 16:01:54 +0000 (UTC)
From: Vitaly Kuznetsov <vkuznets@redhat.com>
To: linux-hyperv@vger.kernel.org
Cc: Wei Liu <wei.liu@kernel.org>, x86@kernel.org,
        linux-kernel@vger.kernel.org, kvm@vger.kernel.org,
        Michael Kelley <mikelley@microsoft.com>,
        Dexuan Cui <decui@microsoft.com>,
        Tianyu Lan <Tianyu.Lan@microsoft.com>
Subject: [PATCH] x86/hyperv: Properly suspend/resume reenlightenment
 notifications
Date: Tue, 12 May 2020 18:01:53 +0200
Message-Id: <20200512160153.134467-1-vkuznets@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.12
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Errors during hibernation with reenlightenment notifications enabled were
reported:

 [   51.730435] PM: hibernation entry
 [   51.737435] PM: Syncing filesystems ...
 ...
 [   54.102216] Disabling non-boot CPUs ...
 [   54.106633] smpboot: CPU 1 is now offline
 [   54.110006] unchecked MSR access error: WRMSR to 0x40000106 (tried to
     write 0x47c72780000100ee) at rIP: 0xffffffff90062f24
     native_write_msr+0x4/0x20)
 [   54.110006] Call Trace:
 [   54.110006]  hv_cpu_die+0xd9/0xf0
 ...

Normally, hv_cpu_die() just reassigns reenlightenment notifications to some
other CPU when the CPU receiving them goes offline. Upon hibernation, there
is no other CPU which is still online so cpumask_any_but(cpu_online_mask)
returns >= nr_cpu_ids and using it as hv_vp_index index is incorrect.
Disable the feature when cpumask_any_but() fails.

Also, as we now disable reenlightenment notifications upon hibernation we
need to restore them on resume. Check if hv_reenlightenment_cb was
previously set and restore from hv_resume().

Signed-off-by: Vitaly Kuznetsov <vkuznets@redhat.com>
Reviewed-by: Dexuan Cui <decui@microsoft.com>
---
 arch/x86/hyperv/hv_init.c | 19 +++++++++++++++++--
 1 file changed, 17 insertions(+), 2 deletions(-)

```
