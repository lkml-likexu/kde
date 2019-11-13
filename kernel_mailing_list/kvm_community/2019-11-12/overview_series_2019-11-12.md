#### [PATCH v9 Kernel 1/5] vfio: KABI for migration interface for device state
##### From: Kirti Wankhede <kwankhede@nvidia.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Kirti Wankhede <kwankhede@nvidia.com>
X-Patchwork-Id: 11239845
Return-Path: <SRS0=xhWs=ZE=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id F19D013BD
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 12 Nov 2019 17:32:54 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id BF58D21872
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 12 Nov 2019 17:32:54 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=nvidia.com header.i=@nvidia.com
 header.b="YU7k3Srp"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727298AbfKLRcx (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 12 Nov 2019 12:32:53 -0500
Received: from hqemgate15.nvidia.com ([216.228.121.64]:15671 "EHLO
        hqemgate15.nvidia.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726932AbfKLRcx (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 12 Nov 2019 12:32:53 -0500
Received: from hqpgpgate101.nvidia.com (Not Verified[216.228.121.13]) by
 hqemgate15.nvidia.com (using TLS: TLSv1.2, DES-CBC3-SHA)
        id <B5dcaecc40000>; Tue, 12 Nov 2019 09:32:52 -0800
Received: from hqmail.nvidia.com ([172.20.161.6])
  by hqpgpgate101.nvidia.com (PGP Universal service);
  Tue, 12 Nov 2019 09:32:52 -0800
X-PGP-Universal: processed;
        by hqpgpgate101.nvidia.com on Tue, 12 Nov 2019 09:32:52 -0800
Received: from HQMAIL109.nvidia.com (172.20.187.15) by HQMAIL107.nvidia.com
 (172.20.187.13) with Microsoft SMTP Server (TLS) id 15.0.1473.3; Tue, 12 Nov
 2019 17:32:52 +0000
Received: from HQMAIL105.nvidia.com (172.20.187.12) by HQMAIL109.nvidia.com
 (172.20.187.15) with Microsoft SMTP Server (TLS) id 15.0.1473.3; Tue, 12 Nov
 2019 17:32:51 +0000
Received: from kwankhede-dev.nvidia.com (10.124.1.5) by HQMAIL105.nvidia.com
 (172.20.187.12) with Microsoft SMTP Server (TLS) id 15.0.1473.3 via Frontend
 Transport; Tue, 12 Nov 2019 17:32:45 +0000
From: Kirti Wankhede <kwankhede@nvidia.com>
To: <alex.williamson@redhat.com>, <cjia@nvidia.com>
CC: <kevin.tian@intel.com>, <ziye.yang@intel.com>,
        <changpeng.liu@intel.com>, <yi.l.liu@intel.com>,
        <mlevitsk@redhat.com>, <eskultet@redhat.com>, <cohuck@redhat.com>,
        <dgilbert@redhat.com>, <jonathan.davies@nutanix.com>,
        <eauger@redhat.com>, <aik@ozlabs.ru>, <pasic@linux.ibm.com>,
        <felipe@nutanix.com>, <Zhengxiao.zx@Alibaba-inc.com>,
        <shuangtai.tst@alibaba-inc.com>, <Ken.Xue@amd.com>,
        <zhi.a.wang@intel.com>, <yan.y.zhao@intel.com>,
        <qemu-devel@nongnu.org>, <kvm@vger.kernel.org>,
        Kirti Wankhede <kwankhede@nvidia.com>
Subject: [PATCH v9 Kernel 1/5] vfio: KABI for migration interface for device
 state
Date: Tue, 12 Nov 2019 22:33:36 +0530
Message-ID: <1573578220-7530-2-git-send-email-kwankhede@nvidia.com>
X-Mailer: git-send-email 2.7.0
In-Reply-To: <1573578220-7530-1-git-send-email-kwankhede@nvidia.com>
References: <1573578220-7530-1-git-send-email-kwankhede@nvidia.com>
X-NVConfidentiality: public
MIME-Version: 1.0
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=nvidia.com; s=n1;
        t=1573579972; bh=SJzWTVcCs3ugRMUC+MoFLwbA9yAA6M2044D6woFgoO0=;
        h=X-PGP-Universal:From:To:CC:Subject:Date:Message-ID:X-Mailer:
         In-Reply-To:References:X-NVConfidentiality:MIME-Version:
         Content-Type;
        b=YU7k3Srp1K/hH+rjNfxoUF2xwnLQxMLNUQAVjztljd3vw/UnWWU/Nd/BUTyoQlM2e
         JhzDe+ulELboXB1Hm/JUij4YqkttDnrTxPJDfxC2LXtWvCzZNDiEqA+HIqxxeK3DKM
         gcBJ3CTMOVK6hIT3n8Xf5aq7t7FQRSl8yarbNpmaBDC+GVw4xjVU9Y6FDMEXy512P6
         tnervQFfSHJrSb8utr/147E9g5mSEcwwe4URthoFDN61TblxznFPXfty5POTCQl/0H
         j8rhwJTrytRcAaWJMcTXKLdSQUHsooYYxad07gryUeylejGR7VFPGsoka1LIpN15X4
         2aAuF1fQ4oXRg==
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

- Defined MIGRATION region type and sub-type.
- Used 3 bits to define VFIO device states.
    Bit 0 => _RUNNING
    Bit 1 => _SAVING
    Bit 2 => _RESUMING
    Combination of these bits defines VFIO device's state during migration
    _RUNNING => Normal VFIO device running state. When its reset, it
		indicates _STOPPED state. when device is changed to
		_STOPPED, driver should stop device before write()
		returns.
    _SAVING | _RUNNING => vCPUs are running, VFIO device is running but
                          start saving state of device i.e. pre-copy state
    _SAVING  => vCPUs are stopped, VFIO device should be stopped, and
                save device state,i.e. stop-n-copy state
    _RESUMING => VFIO device resuming state.
    _SAVING | _RESUMING and _RUNNING | _RESUMING => Invalid states
    Bits 3 - 31 are reserved for future use. User should perform
    read-modify-write operation on this field.
- Defined vfio_device_migration_info structure which will be placed at 0th
  offset of migration region to get/set VFIO device related information.
  Defined members of structure and usage on read/write access:
    * device_state: (read/write)
        To convey VFIO device state to be transitioned to. Only 3 bits are
	used as of now, Bits 3 - 31 are reserved for future use.
    * pending bytes: (read only)
        To get pending bytes yet to be migrated for VFIO device.
    * data_offset: (read only)
        To get data offset in migration region from where data exist
	during _SAVING and from where data should be written by user space
	application during _RESUMING state.
    * data_size: (read/write)
        To get and set size in bytes of data copied in migration region
	during _SAVING and _RESUMING state.

Migration region looks like:
 ------------------------------------------------------------------
|vfio_device_migration_info|    data section                      |
|                          |     ///////////////////////////////  |
 ------------------------------------------------------------------
 ^                              ^
 offset 0-trapped part        data_offset

Structure vfio_device_migration_info is always followed by data section
in the region, so data_offset will always be non-0. Offset from where data
to be copied is decided by kernel driver, data section can be trapped or
mapped depending on how kernel driver defines data section.
Data section partition can be defined as mapped by sparse mmap capability.
If mmapped, then data_offset should be page aligned, where as initial
section which contain vfio_device_migration_info structure might not end
at offset which is page aligned.
Vendor driver should decide whether to partition data section and how to
partition the data section. Vendor driver should return data_offset
accordingly.

For user application, data is opaque. User should write data in the same
order as received.

Signed-off-by: Kirti Wankhede <kwankhede@nvidia.com>
Reviewed-by: Neo Jia <cjia@nvidia.com>
---
 include/uapi/linux/vfio.h | 108 ++++++++++++++++++++++++++++++++++++++++++++++
 1 file changed, 108 insertions(+)

```
#### [GIT PULL] KVM patches for Linux 5.4-rc8
##### From: Paolo Bonzini <pbonzini@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Paolo Bonzini <pbonzini@redhat.com>
X-Patchwork-Id: 11240159
Return-Path: <SRS0=xhWs=ZE=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 9C1001709
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 12 Nov 2019 21:10:47 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 7C84C222C2
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 12 Nov 2019 21:10:47 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=fail reason="signature verification failed" (2048-bit key)
 header.d=gmail.com header.i=@gmail.com header.b="PsrKIWwE"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727211AbfKLVKo (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 12 Nov 2019 16:10:44 -0500
Received: from mail-wm1-f68.google.com ([209.85.128.68]:37006 "EHLO
        mail-wm1-f68.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726645AbfKLVKk (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 12 Nov 2019 16:10:40 -0500
Received: by mail-wm1-f68.google.com with SMTP id b17so4502182wmj.2;
        Tue, 12 Nov 2019 13:10:38 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=sender:from:to:cc:subject:date:message-id;
        bh=ggJ1wueVMuwowaHeTZ0GC3WO2tlvDZKJl8chKJQFPkc=;
        b=PsrKIWwEywODV7XLDEwnDWYX0V4T9w2Mftx/GcjVlZAbot4zg+JZ5aENMi4bHATIWc
         K+4tnaZQ8IzUR5NJPcTKw8a7KyfsUckNE3cch77SeAEKeeUYN8lQwVoVNB2oDgtr88Ns
         kj/Oql8dFfClk1nJfV48ylRaj0VxCDPMhU1DUCCSyPW/8E8IHfgc7sN04kwkoGh412GV
         r4iJ6bT3p4SEXlnOPqlWigVDQifpMc0FZazQ10KGqcOcz1FbowtAZHtQzK93GsHE7/Ew
         3I2vF3dEDVDDb1VR7d1Dql87uwiAM7FMwZxJ1tbl5W6NeDBhmZaF6WkRpUp9x64SDujm
         kxSw==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:sender:from:to:cc:subject:date:message-id;
        bh=ggJ1wueVMuwowaHeTZ0GC3WO2tlvDZKJl8chKJQFPkc=;
        b=aT++p+N1IpURCVQoeHI9EvM8J78MAfOPyzOZc0TZ0cCpN78T+1A8fSftlpm9cgSjyA
         4a41P6FqBgXVd+J2Sl2LhztbH8UQVcFpDWgEZhYVkub9pr5D+O2t3X7sqYMYWoTVuQnJ
         pufrds2pGaj4gPRFjI05TVUz2OZXWmeR8ssy62cqnXgYiEoqT/R/X0zglmHhySd8lmBL
         LkwnEw2KZ/TX6jbZM+hmuvvjFgxukb68GDGOgqj/oL7MR5xMusadELbtQgoNek9/X34Q
         RVjoWRfjHTzhg2Y+J8shoCwhjPOninapvP8beoPRvXg5CJgaYOIj2qVr+5ca4UQoEr94
         mCqw==
X-Gm-Message-State: APjAAAW/n6/YlLi1E86rWjksYnCMA5KW0gCozZp6sRhA/Im2kvbAZUit
        pBPgTitXSCsUhUW+MPHaMY7Bf7eL
X-Google-Smtp-Source: 
 APXvYqy2aLhqqT/TL0rcyK1Ryn/w/sr+i15tLkfOG5tJp6IP8/oSH50xCw/il6DnUuQ16rUQ5Urj8Q==
X-Received: by 2002:a1c:9601:: with SMTP id y1mr5613615wmd.157.1573593037942;
        Tue, 12 Nov 2019 13:10:37 -0800 (PST)
Received: from 640k.lan ([93.56.166.5])
        by smtp.gmail.com with ESMTPSA id
 p25sm4132624wma.20.2019.11.12.13.10.36
        (version=TLS1_2 cipher=ECDHE-RSA-AES128-GCM-SHA256 bits=128/128);
        Tue, 12 Nov 2019 13:10:37 -0800 (PST)
From: Paolo Bonzini <pbonzini@redhat.com>
To: torvalds@linux-foundation.org
Cc: linux-kernel@vger.kernel.org, rkrcmar@redhat.com,
        kvm@vger.kernel.org
Subject: [GIT PULL] KVM patches for Linux 5.4-rc8
Date: Tue, 12 Nov 2019 22:10:36 +0100
Message-Id: <1573593036-23271-1-git-send-email-pbonzini@redhat.com>
X-Mailer: git-send-email 1.8.3.1
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Linus,

The following changes since commit 31f4f5b495a62c9a8b15b1c3581acd5efeb9af8c:

  Linux 5.4-rc7 (2019-11-10 16:17:15 -0800)

are available in the git repository at:

  https://git.kernel.org/pub/scm/virt/kvm/kvm.git tags/for-linus

for you to fetch changes up to a78986aae9b2988f8493f9f65a587ee433e83bc3:

  KVM: MMU: Do not treat ZONE_DEVICE pages as being reserved (2019-11-12 10:17:42 +0100)

----------------------------------------------------------------
Bugfixes: unwinding of KVM_CREATE_VM failure,
VT-d posted interrupts, DAX/ZONE_DEVICE,
module unload/reload.

----------------------------------------------------------------

I delayed sending this until today, because there is a conflict between
today's processor vulnerability mitigations and commit 8a44119a98be from
this pull request ("KVM: Fix NULL-ptr deref after kvm_create_vm fails"),
and I didn't want to mess up your processing of Thomas's pull request.
It's not a particularly hard conflict, but I'm including anyway a
resolution at the end of this email.

Paolo

Chenyi Qiang (1):
      KVM: X86: Fix initialization of MSR lists

Joao Martins (3):
      KVM: VMX: Consider PID.PIR to determine if vCPU has pending interrupts
      KVM: VMX: Do not change PID.NDST when loading a blocked vCPU
      KVM: VMX: Introduce pi_is_pir_empty() helper

Liran Alon (1):
      KVM: VMX: Fix comment to specify PID.ON instead of PIR.ON

Paolo Bonzini (2):
      KVM: Fix NULL-ptr deref after kvm_create_vm fails
      KVM: fix placement of refcount initialization

Sean Christopherson (1):
      KVM: MMU: Do not treat ZONE_DEVICE pages as being reserved

 arch/x86/kvm/mmu.c       |  8 +++----
 arch/x86/kvm/vmx/vmx.c   | 23 +++++++++++++++++---
 arch/x86/kvm/vmx/vmx.h   | 11 ++++++++++
 arch/x86/kvm/x86.c       | 56 ++++++++++++++++++++++--------------------------
 include/linux/kvm_host.h |  1 +
 virt/kvm/kvm_main.c      | 48 +++++++++++++++++++++++++++++------------
 6 files changed, 96 insertions(+), 51 deletions(-)



+++ b/virt/kvm/kvm_main.c
@@@ -715,15 -713,6 +735,11 @@@
  	return kvm;
  
  out_err:
 +#if defined(CONFIG_MMU_NOTIFIER) && defined(KVM_ARCH_WANT_MMU_NOTIFIER)
 +	if (kvm->mmu_notifier.ops)
 +		mmu_notifier_unregister(&kvm->mmu_notifier, current->mm);
 +#endif
 +out_err_no_mmu_notifier:
- 	cleanup_srcu_struct(&kvm->irq_srcu);
- out_err_no_irq_srcu:
- 	cleanup_srcu_struct(&kvm->srcu);
- out_err_no_srcu:
  	hardware_disable_all();
  out_err_no_disable:
  	kvm_arch_destroy_vm(kvm);

```
#### [RFC V3 1/2] This commit introduced ifcvf_base layer, which handles hardware operations and configurations.
##### From: Zhu Lingshan <lingshan.zhu@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Zhu Lingshan <lingshan.zhu@intel.com>
X-Patchwork-Id: 11238951
Return-Path: <SRS0=xhWs=ZE=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id A418E14E5
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 12 Nov 2019 09:32:13 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 7D0B220650
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 12 Nov 2019 09:32:13 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727222AbfKLJcI (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 12 Nov 2019 04:32:08 -0500
Received: from mga05.intel.com ([192.55.52.43]:56112 "EHLO mga05.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1725834AbfKLJcH (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 12 Nov 2019 04:32:07 -0500
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from orsmga008.jf.intel.com ([10.7.209.65])
  by fmsmga105.fm.intel.com with ESMTP/TLS/DHE-RSA-AES256-GCM-SHA384;
 12 Nov 2019 01:32:07 -0800
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.68,295,1569308400";
   d="scan'208";a="198017556"
Received: from unknown (HELO localhost.localdomain.bj.intel.com)
 ([10.240.193.79])
  by orsmga008.jf.intel.com with ESMTP; 12 Nov 2019 01:32:03 -0800
From: Zhu Lingshan <lingshan.zhu@intel.com>
To: mst@redhat.com, jasowang@redhat.com, alex.williamson@redhat.com
Cc: linux-kernel@vger.kernel.org,
        virtualization@lists.linux-foundation.org, kvm@vger.kernel.org,
        netdev@vger.kernel.org, dan.daly@intel.com,
        cunming.liang@intel.com, tiwei.bie@intel.com, jason.zeng@intel.com,
        zhiyuan.lv@intel.com, Zhu Lingshan <lingshan.zhu@intel.com>
Subject: [RFC V3 1/2] This commit introduced ifcvf_base layer,
 which handles hardware operations and configurations.
Date: Tue, 12 Nov 2019 17:29:48 +0800
Message-Id: <1573550989-40860-2-git-send-email-lingshan.zhu@intel.com>
X-Mailer: git-send-email 1.8.3.1
In-Reply-To: <1573550989-40860-1-git-send-email-lingshan.zhu@intel.com>
References: <1573550989-40860-1-git-send-email-lingshan.zhu@intel.com>
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Signed-off-by: Zhu Lingshan <lingshan.zhu@intel.com>
---
 drivers/vhost/ifcvf/ifcvf_base.c | 326 +++++++++++++++++++++++++++++++++++++++
 drivers/vhost/ifcvf/ifcvf_base.h | 129 ++++++++++++++++
 2 files changed, 455 insertions(+)
 create mode 100644 drivers/vhost/ifcvf/ifcvf_base.c
 create mode 100644 drivers/vhost/ifcvf/ifcvf_base.h

diff --git a/drivers/vhost/ifcvf/ifcvf_base.c b/drivers/vhost/ifcvf/ifcvf_base.c
new file mode 100644
index 0000000..6bf2ddd
--- /dev/null
+++ b/drivers/vhost/ifcvf/ifcvf_base.c
@@ -0,0 +1,326 @@
+// SPDX-License-Identifier: GPL-2.0-only
+/*
+ * Copyright (C) 2019 Intel Corporation.
+ */
+
+#include "ifcvf_base.h"
+
+static void *get_cap_addr(struct ifcvf_hw *hw, struct virtio_pci_cap *cap)
+{
+	struct ifcvf_adapter *ifcvf;
+	u32 length, offset;
+	u8 bar;
+
+	length = le32_to_cpu(cap->length);
+	offset = le32_to_cpu(cap->offset);
+	bar = le32_to_cpu(cap->bar);
+
+	ifcvf = container_of(hw, struct ifcvf_adapter, vf);
+
+	if (bar >= IFCVF_PCI_MAX_RESOURCE) {
+		IFC_DBG(ifcvf->dev,
+			"Invalid bar number %u to get capabilities\n", bar);
+		return NULL;
+	}
+
+	if (offset + length > hw->mem_resource[cap->bar].len) {
+		IFC_DBG(ifcvf->dev,
+			"offset(%u) + len(%u) overflows bar%u to get capabilities\n",
+			offset, length, bar);
+		return NULL;
+	}
+
+	return hw->mem_resource[bar].addr + offset;
+}
+
+int ifcvf_read_config_range(struct pci_dev *dev,
+			uint32_t *val, int size, int where)
+{
+	int ret, i;
+
+	for (i = 0; i < size; i += 4) {
+		ret = pci_read_config_dword(dev, where + i, val + i / 4);
+		if (ret < 0)
+			return ret;
+	}
+
+	return 0;
+}
+
+int ifcvf_init_hw(struct ifcvf_hw *hw, struct pci_dev *dev)
+{
+	struct virtio_pci_cap cap;
+	u16 notify_off;
+	int ret;
+	u8 pos;
+	u32 i;
+
+	ret = pci_read_config_byte(dev, PCI_CAPABILITY_LIST, &pos);
+
+	if (ret < 0) {
+		IFC_ERR(&dev->dev, "Failed to read PCI capability list\n");
+		return -EIO;
+	}
+
+	while (pos) {
+		ret = ifcvf_read_config_range(dev, (u32 *)&cap,
+					      sizeof(cap), pos);
+
+		if (ret < 0) {
+			IFC_ERR(&dev->dev, "Failed to get PCI capability at %x\n",
+				pos);
+			break;
+		}
+
+		if (cap.cap_vndr != PCI_CAP_ID_VNDR)
+			goto next;
+
+		IFC_DBG(&dev->dev, "read PCI config: config type: %u, PCI bar: %u, PCI bar offset: %u, PCI config len: %u\n",
+			cap.cfg_type, cap.bar, cap.offset, cap.length);
+
+		switch (cap.cfg_type) {
+		case VIRTIO_PCI_CAP_COMMON_CFG:
+			hw->common_cfg = get_cap_addr(hw, &cap);
+			IFC_DBG(&dev->dev, "hw->common_cfg = %p\n",
+				hw->common_cfg);
+			break;
+		case VIRTIO_PCI_CAP_NOTIFY_CFG:
+			pci_read_config_dword(dev, pos + sizeof(cap),
+					      &hw->notify_off_multiplier);
+			hw->notify_bar = cap.bar;
+			hw->notify_base = get_cap_addr(hw, &cap);
+			IFC_DBG(&dev->dev, "hw->notify_base = %p\n",
+				hw->notify_base);
+			break;
+		case VIRTIO_PCI_CAP_ISR_CFG:
+			hw->isr = get_cap_addr(hw, &cap);
+			IFC_DBG(&dev->dev, "hw->isr = %p\n", hw->isr);
+			break;
+		case VIRTIO_PCI_CAP_DEVICE_CFG:
+			hw->net_cfg = get_cap_addr(hw, &cap);
+			IFC_DBG(&dev->dev, "hw->net_cfg = %p\n", hw->net_cfg);
+			break;
+		}
+next:
+		pos = cap.cap_next;
+	}
+
+	if (hw->common_cfg == NULL || hw->notify_base == NULL ||
+	    hw->isr == NULL || hw->net_cfg == NULL) {
+		IFC_DBG(&dev->dev, "Incomplete PCI capabilities\n");
+		return -1;
+	}
+
+	for (i = 0; i < IFCVF_MAX_QUEUE_PAIRS * 2; i++) {
+		iowrite16(i, &hw->common_cfg->queue_select);
+		notify_off = ioread16(&hw->common_cfg->queue_notify_off);
+		hw->vring->notify_addr[i] = (void *)((u8 *)hw->notify_base +
+				     notify_off * hw->notify_off_multiplier);
+	}
+
+	hw->lm_cfg = hw->mem_resource[IFCVF_LM_BAR].addr;
+
+	IFC_DBG(&dev->dev, "PCI capability mapping: common cfg: %p, notify base: %p\n, isr cfg: %p, device cfg: %p, multiplier: %u\n",
+		hw->common_cfg, hw->notify_base, hw->isr,
+		hw->net_cfg, hw->notify_off_multiplier);
+
+	return 0;
+}
+
+u8 ifcvf_get_status(struct ifcvf_hw *hw)
+{
+	return ioread8(&hw->common_cfg->device_status);
+}
+
+void ifcvf_set_status(struct ifcvf_hw *hw, u8 status)
+{
+	iowrite8(status, &hw->common_cfg->device_status);
+}
+
+void ifcvf_reset(struct ifcvf_hw *hw)
+{
+	ifcvf_set_status(hw, 0);
+	ifcvf_get_status(hw);
+}
+
+static void ifcvf_add_status(struct ifcvf_hw *hw, u8 status)
+{
+	if (status != 0)
+		status |= ifcvf_get_status(hw);
+
+	ifcvf_set_status(hw, status);
+	ifcvf_get_status(hw);
+}
+
+u64 ifcvf_get_features(struct ifcvf_hw *hw)
+{
+	struct virtio_pci_common_cfg *cfg = hw->common_cfg;
+	u32 features_lo, features_hi;
+
+	iowrite32(0, &cfg->device_feature_select);
+	features_lo = ioread32(&cfg->device_feature);
+
+	iowrite32(1, &cfg->device_feature_select);
+	features_hi = ioread32(&cfg->device_feature);
+
+	return ((u64)features_hi << 32) | features_lo;
+}
+
+void ifcvf_read_net_config(struct ifcvf_hw *hw, u64 offset,
+		       void *dst, int length)
+{
+	u8 old_gen, new_gen, *p;
+	int i;
+
+	WARN_ON(offset + length > sizeof (struct virtio_net_config));
+
+	do {
+		old_gen = ioread8(&hw->common_cfg->config_generation);
+		p = dst;
+
+		for (i = 0; i < length; i++)
+			*p++ = ioread8((u8 *)hw->net_cfg + offset + i);
+
+		new_gen = ioread8(&hw->common_cfg->config_generation);
+	} while (old_gen != new_gen);
+}
+
+void ifcvf_write_net_config(struct ifcvf_hw *hw, u64 offset,
+			    const void *src, int length)
+{
+	const u8 *p;
+	int i;
+
+	p = src;
+	WARN_ON(offset + length > sizeof(struct virtio_net_config));
+
+	for (i = 0; i < length; i++)
+		iowrite8(*p++, (u8 *)hw->net_cfg + offset + i);
+}
+
+static void ifcvf_set_features(struct ifcvf_hw *hw, u64 features)
+{
+	struct virtio_pci_common_cfg *cfg = hw->common_cfg;
+
+	iowrite32(0, &cfg->guest_feature_select);
+	iowrite32((u32)features, &cfg->guest_feature);
+
+	iowrite32(1, &cfg->guest_feature_select);
+	iowrite32(features >> 32, &cfg->guest_feature);
+}
+
+static int ifcvf_config_features(struct ifcvf_hw *hw)
+{
+	struct ifcvf_adapter *ifcvf;
+
+	ifcvf = container_of(hw, struct ifcvf_adapter, vf);
+	ifcvf_set_features(hw, hw->req_features);
+	ifcvf_add_status(hw, VIRTIO_CONFIG_S_FEATURES_OK);
+
+	if (!(ifcvf_get_status(hw) & VIRTIO_CONFIG_S_FEATURES_OK)) {
+		IFC_ERR(ifcvf->dev, "Failed to set FEATURES_OK status\n");
+		return -EIO;
+	}
+
+	return 0;
+}
+
+void io_write64_twopart(u64 val, u32 *lo, u32 *hi)
+{
+	iowrite32(val & ((1ULL << 32) - 1), lo);
+	iowrite32(val >> 32, hi);
+}
+
+static int ifcvf_hw_enable(struct ifcvf_hw *hw)
+{
+	struct ifcvf_lm_cfg __iomem *ifcvf_lm;
+	struct virtio_pci_common_cfg *cfg;
+	struct ifcvf_adapter *ifcvf;
+	u32 __iomem* idx_addr;
+	u32 i, val;
+
+	ifcvf_lm = (struct ifcvf_lm_cfg*)hw->lm_cfg;
+	ifcvf = container_of(hw, struct ifcvf_adapter, vf);
+	cfg = hw->common_cfg;
+	iowrite16(IFCVF_MSI_CONFIG_OFF, &cfg->msix_config);
+
+	if (ioread16(&cfg->msix_config) == VIRTIO_MSI_NO_VECTOR) {
+		IFC_ERR(ifcvf->dev, "No msix vector for device config\n");
+		return -1;
+	}
+
+	for (i = 0; i < hw->nr_vring; i++) {
+		if (!hw->vring[i].ready)
+			break;
+
+		iowrite16(i, &cfg->queue_select);
+		io_write64_twopart(hw->vring[i].desc, &cfg->queue_desc_lo,
+				&cfg->queue_desc_hi);
+		io_write64_twopart(hw->vring[i].avail, &cfg->queue_avail_lo,
+				&cfg->queue_avail_hi);
+		io_write64_twopart(hw->vring[i].used, &cfg->queue_used_lo,
+				&cfg->queue_used_hi);
+		iowrite16(hw->vring[i].size, &cfg->queue_size);
+		idx_addr = &(ifcvf_lm->vring_lm_cfg[i/IFCVF_MAX_QUEUES].idx_addr[i%IFCVF_MAX_QUEUES]);
+		val = (u32)hw->vring[i].last_avail_idx |
+			((u32)hw->vring[i].last_used_idx << 16);
+		iowrite32(val, idx_addr);
+		iowrite16(i + IFCVF_MSI_QUEUE_OFF, &cfg->queue_msix_vector);
+
+		if (ioread16(&cfg->queue_msix_vector) ==
+		    VIRTIO_MSI_NO_VECTOR) {
+			IFC_ERR(ifcvf->dev,
+				"No msix vector for queue %u\n", i);
+			return -1;
+		}
+
+		iowrite16(1, &cfg->queue_enable);
+	}
+
+	return 0;
+}
+
+static void ifcvf_hw_disable(struct ifcvf_hw *hw)
+{
+	struct virtio_pci_common_cfg *cfg;
+	u32 i;
+
+	cfg = hw->common_cfg;
+	iowrite16(VIRTIO_MSI_NO_VECTOR, &cfg->msix_config);
+
+	for (i = 0; i < hw->nr_vring; i++) {
+		iowrite16(i, &cfg->queue_select);
+		iowrite16(0, &cfg->queue_enable);
+		iowrite16(VIRTIO_MSI_NO_VECTOR, &cfg->queue_msix_vector);
+	}
+
+	ioread16(&cfg->queue_msix_vector);
+}
+
+int ifcvf_start_hw(struct ifcvf_hw *hw)
+{
+	ifcvf_reset(hw);
+	ifcvf_add_status(hw, VIRTIO_CONFIG_S_ACKNOWLEDGE);
+	ifcvf_add_status(hw, VIRTIO_CONFIG_S_DRIVER);
+
+	if (ifcvf_config_features(hw) < 0)
+		return -1;
+
+	if (ifcvf_hw_enable(hw) < 0)
+		return -1;
+
+	ifcvf_add_status(hw, VIRTIO_CONFIG_S_DRIVER_OK);
+
+	return 0;
+}
+
+void ifcvf_stop_hw(struct ifcvf_hw *hw)
+{
+	ifcvf_hw_disable(hw);
+	ifcvf_reset(hw);
+}
+
+void ifcvf_notify_queue(struct ifcvf_hw *hw, u16 qid)
+{
+	iowrite16(qid, hw->vring->notify_addr[qid]);
+}
diff --git a/drivers/vhost/ifcvf/ifcvf_base.h b/drivers/vhost/ifcvf/ifcvf_base.h
new file mode 100644
index 0000000..587c114
--- /dev/null
+++ b/drivers/vhost/ifcvf/ifcvf_base.h
@@ -0,0 +1,129 @@
+// SPDX-License-Identifier: GPL-2.0-only
+/*
+ * Copyright (C) 2019 Intel Corporation.
+ */
+
+#ifndef _IFCVF_H_
+#define _IFCVF_H_
+
+#include <linux/mdev_virtio_ops.h>
+#include <linux/mdev.h>
+#include <linux/pci.h>
+#include <linux/pci_regs.h>
+#include <uapi/linux/virtio_net.h>
+#include <uapi/linux/virtio_config.h>
+#include <uapi/linux/virtio_pci.h>
+
+#define IFCVF_VENDOR_ID         0x1AF4
+#define IFCVF_DEVICE_ID         0x1041
+#define IFCVF_SUBSYS_VENDOR_ID  0x8086
+#define IFCVF_SUBSYS_DEVICE_ID  0x001A
+
+#define IFCVF_MDEV_LIMIT	1
+
+#define IFC_SUPPORTED_FEATURES \
+		((1ULL << VIRTIO_NET_F_MAC)			| \
+		 (1ULL << VIRTIO_F_ANY_LAYOUT)			| \
+		 (1ULL << VIRTIO_F_VERSION_1)			| \
+		 (1ULL << VIRTIO_F_ORDER_PLATFORM)		| \
+		 (1ULL << VIRTIO_NET_F_GUEST_ANNOUNCE)		| \
+		 (1ULL << VIRTIO_F_IOMMU_PLATFORM)		| \
+		 (1ULL << VIRTIO_NET_F_MRG_RXBUF)		| \
+
+/* Not support MQ, only one queue pair for now. */
+#define IFCVF_MAX_QUEUE_PAIRS		1
+#define IFCVF_MAX_QUEUES		2
+
+#define IFCVF_QUEUE_ALIGNMENT		PAGE_SIZE
+#define IFCVF_QUEUE_MAX		32 * 1024
+#define IFCVF_MSI_CONFIG_OFF	0
+#define IFCVF_MSI_QUEUE_OFF	1
+#define IFCVF_PCI_MAX_RESOURCE	6
+
+#define IFCVF_LM_CFG_SIZE		0x40
+#define IFCVF_LM_RING_STATE_OFFSET	0x20
+#define IFCVF_LM_BAR	4
+
+#define IFCVF_32_BIT_MASK		0xffffffff
+
+#define IFC_ERR(dev, fmt, ...)	dev_err(dev, fmt, ##__VA_ARGS__)
+#define IFC_DBG(dev, fmt, ...)	dev_dbg(dev, fmt, ##__VA_ARGS__)
+#define IFC_INFO(dev, fmt, ...)	dev_info(dev, fmt, ##__VA_ARGS__)
+
+#define IFC_PRIVATE_TO_VF(adapter) \
+	(&((struct ifcvf_adapter *)adapter)->vf)
+
+#define IFCVF_MAX_INTR (IFCVF_MAX_QUEUE_PAIRS * 2 + 1)
+
+struct ifcvf_pci_mem_resource {
+	/* Physical address, 0 if not resource. */
+	u64      phys_addr;
+	/* Length of the resource. */
+	u64      len;
+	/* Virtual address, NULL when not mapped. */
+	u8       *addr;
+};
+
+struct vring_info {
+	u64 desc;
+	u64 avail;
+	u64 used;
+	u16 size;
+	u16 last_avail_idx;
+	u16 last_used_idx;
+	bool ready;
+	char msix_name[256];
+	u16 __iomem *notify_addr[IFCVF_MAX_QUEUE_PAIRS * 2];
+	struct virtio_mdev_callback cb;
+};
+
+struct ifcvf_hw {
+	u8	*isr;
+	/* Bar to nofity the VF (queue) */
+	u8	notify_bar;
+	/* live migration */
+	u8	__iomem	*lm_cfg;
+	u8	nr_vring;
+	/* Notificaiton bar address*/
+	u16	*notify_base;
+	u32	notify_off_multiplier;
+	u64	req_features;
+	struct	virtio_pci_common_cfg __iomem	*common_cfg;
+	struct	virtio_net_config __iomem	*net_cfg;
+	struct	vring_info vring[IFCVF_MAX_QUEUE_PAIRS * 2];
+	struct	ifcvf_pci_mem_resource mem_resource[IFCVF_PCI_MAX_RESOURCE];
+};
+
+struct ifcvf_adapter {
+	struct	device *dev;
+	struct	mutex mdev_lock;
+	int	mdev_count;
+	int	vectors;
+	struct	ifcvf_hw vf;
+};
+
+struct ifcvf_vring_lm_cfg {
+	u32 idx_addr[2];
+	u8 reserved[IFCVF_LM_CFG_SIZE - 8];
+};
+
+struct ifcvf_lm_cfg {
+	u8 reserved[IFCVF_LM_RING_STATE_OFFSET];
+	struct ifcvf_vring_lm_cfg vring_lm_cfg[IFCVF_MAX_QUEUE_PAIRS];
+};
+
+int ifcvf_init_hw(struct ifcvf_hw *hw, struct pci_dev *dev);
+int ifcvf_start_hw(struct ifcvf_hw *hw);
+void ifcvf_stop_hw(struct ifcvf_hw *hw);
+void ifcvf_notify_queue(struct ifcvf_hw *hw, u16 qid);
+void ifcvf_read_net_config(struct ifcvf_hw *hw, u64 offset,
+			   void *dst, int length);
+void ifcvf_write_net_config(struct ifcvf_hw *hw, u64 offset,
+			    const void *src, int length);
+u8 ifcvf_get_status(struct ifcvf_hw *hw);
+void ifcvf_set_status(struct ifcvf_hw *hw, u8 status);
+void io_write64_twopart(u64 val, u32 *lo, u32 *hi);
+void ifcvf_reset(struct ifcvf_hw *hw);
+u64 ifcvf_get_features(struct ifcvf_hw *hw);
+
+#endif /* _IFCVF_H_ */

From patchwork Tue Nov 12 09:29:49 2019
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Zhu Lingshan <lingshan.zhu@intel.com>
X-Patchwork-Id: 11238953
Return-Path: <SRS0=xhWs=ZE=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id C887814E5
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 12 Nov 2019 09:32:18 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id A15F720650
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 12 Nov 2019 09:32:18 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727343AbfKLJcN (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 12 Nov 2019 04:32:13 -0500
Received: from mga05.intel.com ([192.55.52.43]:56112 "EHLO mga05.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1727319AbfKLJcL (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 12 Nov 2019 04:32:11 -0500
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from orsmga008.jf.intel.com ([10.7.209.65])
  by fmsmga105.fm.intel.com with ESMTP/TLS/DHE-RSA-AES256-GCM-SHA384;
 12 Nov 2019 01:32:10 -0800
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.68,295,1569308400";
   d="scan'208";a="198017577"
Received: from unknown (HELO localhost.localdomain.bj.intel.com)
 ([10.240.193.79])
  by orsmga008.jf.intel.com with ESMTP; 12 Nov 2019 01:32:08 -0800
From: Zhu Lingshan <lingshan.zhu@intel.com>
To: mst@redhat.com, jasowang@redhat.com, alex.williamson@redhat.com
Cc: linux-kernel@vger.kernel.org,
        virtualization@lists.linux-foundation.org, kvm@vger.kernel.org,
        netdev@vger.kernel.org, dan.daly@intel.com,
        cunming.liang@intel.com, tiwei.bie@intel.com, jason.zeng@intel.com,
        zhiyuan.lv@intel.com, Zhu Lingshan <lingshan.zhu@intel.com>
Subject: [RFC V3 2/2] This commit introduced IFC operations for vdpa,
 which complys to virtio_mdev and vhost_mdev interfaces,
 handles IFC VF initialization, configuration and removal.
Date: Tue, 12 Nov 2019 17:29:49 +0800
Message-Id: <1573550989-40860-3-git-send-email-lingshan.zhu@intel.com>
X-Mailer: git-send-email 1.8.3.1
In-Reply-To: <1573550989-40860-1-git-send-email-lingshan.zhu@intel.com>
References: <1573550989-40860-1-git-send-email-lingshan.zhu@intel.com>
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Signed-off-by: Zhu Lingshan <lingshan.zhu@intel.com>
---
 drivers/vhost/ifcvf/ifcvf_main.c | 579 +++++++++++++++++++++++++++++++++++++++
 1 file changed, 579 insertions(+)
 create mode 100644 drivers/vhost/ifcvf/ifcvf_main.c

diff --git a/drivers/vhost/ifcvf/ifcvf_main.c b/drivers/vhost/ifcvf/ifcvf_main.c
new file mode 100644
index 0000000..0b33410
--- /dev/null
+++ b/drivers/vhost/ifcvf/ifcvf_main.c
@@ -0,0 +1,579 @@
+// SPDX-License-Identifier: GPL-2.0-only
+/*
+ * Copyright (C) 2019 Intel Corporation.
+ */
+
+#include <linux/interrupt.h>
+#include <linux/module.h>
+#include <linux/mdev.h>
+#include <linux/pci.h>
+#include <linux/sysfs.h>
+#include "ifcvf_base.h"
+
+#define VERSION_STRING	"0.1"
+#define DRIVER_AUTHOR	"Intel Corporation"
+#define IFCVF_DRIVER_NAME	"ifcvf"
+
+static struct ifcvf_hw *mdev_to_vf(struct mdev_device *mdev)
+{
+	struct ifcvf_adapter *adapter = mdev_get_drvdata(mdev);
+	struct ifcvf_hw *vf = IFC_PRIVATE_TO_VF(adapter);
+
+	return vf;
+}
+
+static irqreturn_t ifcvf_intr_handler(int irq, void *arg)
+{
+	struct vring_info *vring = arg;
+
+	if (vring->cb.callback)
+		return vring->cb.callback(vring->cb.private);
+
+	return IRQ_HANDLED;
+}
+
+static u64 ifcvf_mdev_get_features(struct mdev_device *mdev)
+{
+	struct ifcvf_hw *vf = mdev_to_vf(mdev);
+
+	return ifcvf_get_features(vf);
+}
+
+static int ifcvf_mdev_set_features(struct mdev_device *mdev, u64 features)
+{
+	struct ifcvf_hw *vf = mdev_to_vf(mdev);
+
+	vf->req_features = features;
+
+	return 0;
+}
+
+static u64 ifcvf_mdev_get_vq_state(struct mdev_device *mdev, u16 qid)
+{
+	struct ifcvf_hw *vf = mdev_to_vf(mdev);
+	u16 last_avail_idx;
+	u16 __iomem *idx_addr;
+
+	idx_addr = (u16 __iomem*)(vf->lm_cfg + IFCVF_LM_RING_STATE_OFFSET +
+			(qid / 2) * IFCVF_LM_CFG_SIZE + (qid % 2) * 4);
+
+	last_avail_idx = ioread16(idx_addr);
+
+	return last_avail_idx;
+}
+
+static int ifcvf_mdev_set_vq_state(struct mdev_device *mdev, u16 qid, u64 num)
+{
+	struct ifcvf_hw *vf = mdev_to_vf(mdev);
+
+	vf->vring[qid].last_avail_idx = num;
+
+	return 0;
+}
+
+static int ifcvf_mdev_set_vq_address(struct mdev_device *mdev, u16 idx,
+				     u64 desc_area, u64 driver_area,
+				     u64 device_area)
+{
+	struct ifcvf_hw *vf = mdev_to_vf(mdev);
+
+	vf->vring[idx].desc = desc_area;
+	vf->vring[idx].avail = driver_area;
+	vf->vring[idx].used = device_area;
+
+	return 0;
+}
+
+static void ifcvf_mdev_set_vq_num(struct mdev_device *mdev, u16 qid, u32 num)
+{
+	struct ifcvf_hw *vf = mdev_to_vf(mdev);
+
+	vf->vring[qid].size = num;
+}
+
+static void ifcvf_mdev_set_vq_ready(struct mdev_device *mdev,
+				    u16 qid, bool ready)
+{
+	struct ifcvf_hw *vf = mdev_to_vf(mdev);
+
+	vf->vring[qid].ready = ready;
+}
+
+static bool ifcvf_mdev_get_vq_ready(struct mdev_device *mdev, u16 qid)
+{
+	struct ifcvf_hw *vf = mdev_to_vf(mdev);
+
+	return vf->vring[qid].ready;
+}
+
+static void ifcvf_mdev_set_vq_cb(struct mdev_device *mdev, u16 idx,
+				 struct virtio_mdev_callback *cb)
+{
+	struct ifcvf_hw *vf = mdev_to_vf(mdev);
+
+	vf->vring[idx].cb = *cb;
+}
+
+static void ifcvf_mdev_kick_vq(struct mdev_device *mdev, u16 idx)
+{
+	struct ifcvf_hw *vf = mdev_to_vf(mdev);
+
+	ifcvf_notify_queue(vf, idx);
+}
+
+static u8 ifcvf_mdev_get_status(struct mdev_device *mdev)
+{
+	struct ifcvf_hw *vf = mdev_to_vf(mdev);
+
+	return ifcvf_get_status(vf);
+}
+
+static u32 ifcvf_mdev_get_generation(struct mdev_device *mdev)
+{
+	struct ifcvf_hw *vf = mdev_to_vf(mdev);
+
+	return ioread8(&vf->common_cfg->config_generation);
+}
+
+static u32 ifcvf_mdev_get_device_id(struct mdev_device *mdev)
+{
+	return VIRTIO_ID_NET;
+}
+
+static u32 ifcvf_mdev_get_vendor_id(struct mdev_device *mdev)
+{
+	return IFCVF_VENDOR_ID;
+}
+
+static u16 ifcvf_mdev_get_vq_align(struct mdev_device *mdev)
+{
+	return IFCVF_QUEUE_ALIGNMENT;
+}
+
+static int ifcvf_start_datapath(void *private)
+{
+	struct ifcvf_hw *vf = IFC_PRIVATE_TO_VF(private);
+	struct ifcvf_adapter *ifcvf;
+	int ret = 0;
+	u8 status;
+
+	ifcvf = container_of(vf, struct ifcvf_adapter, vf);
+	vf->nr_vring = IFCVF_MAX_QUEUE_PAIRS * 2;
+	ret = ifcvf_start_hw(vf);
+
+	if (ret) {
+		status = ifcvf_get_status(vf);
+		status |= VIRTIO_CONFIG_S_FAILED;
+		ifcvf_set_status(vf, status);
+	}
+
+	return ret;
+}
+
+static int ifcvf_stop_datapath(void *private)
+{
+	struct ifcvf_hw *vf = IFC_PRIVATE_TO_VF(private);
+	int i;
+
+	for (i = 0; i < IFCVF_MAX_QUEUES; i++)
+		vf->vring[i].cb.callback = NULL;
+
+	ifcvf_stop_hw(vf);
+
+	return 0;
+}
+
+static void ifcvf_reset_vring(struct ifcvf_adapter *adapter)
+{
+	struct ifcvf_hw *vf = IFC_PRIVATE_TO_VF(adapter);
+	int i;
+
+	for (i = 0; i < IFCVF_MAX_QUEUE_PAIRS * 2; i++) {
+		vf->vring[i].last_used_idx = 0;
+		vf->vring[i].last_avail_idx = 0;
+		vf->vring[i].desc = 0;
+		vf->vring[i].avail = 0;
+		vf->vring[i].used = 0;
+		vf->vring[i].ready = 0;
+		vf->vring->cb.callback = NULL;
+		vf->vring->cb.private = NULL;
+
+	}
+
+	ifcvf_reset(vf);
+}
+
+static void ifcvf_mdev_set_status(struct mdev_device *mdev, u8 status)
+{
+	struct ifcvf_adapter *adapter = mdev_get_drvdata(mdev);
+	struct ifcvf_hw *vf = IFC_PRIVATE_TO_VF(adapter);
+	int ret = 0;
+
+	if (status == 0) {
+		ifcvf_stop_datapath(adapter);
+		ifcvf_reset_vring(adapter);
+		return;
+	}
+
+	if (status & VIRTIO_CONFIG_S_DRIVER_OK) {
+		ret = ifcvf_start_datapath(adapter);
+
+		if (ret)
+			IFC_ERR(adapter->dev, "Failed to set mdev status %u\n",
+				status);
+	}
+
+	ifcvf_set_status(vf, status);
+}
+
+static u16 ifcvf_mdev_get_vq_num_max(struct mdev_device *mdev)
+{
+
+	return (u16)IFCVF_QUEUE_MAX;
+}
+static void ifcvf_mdev_get_config(struct mdev_device *mdev, unsigned int offset,
+			     void *buf, unsigned int len)
+{
+	struct ifcvf_hw *vf = mdev_to_vf(mdev);
+
+	WARN_ON(offset + len > sizeof(struct virtio_net_config));
+	ifcvf_read_net_config(vf, offset, buf, len);
+}
+
+static void ifcvf_mdev_set_config(struct mdev_device *mdev, unsigned int offset,
+			     const void *buf, unsigned int len)
+{
+	struct ifcvf_hw *vf = mdev_to_vf(mdev);
+
+	WARN_ON(offset + len > sizeof(struct virtio_net_config));
+	ifcvf_write_net_config(vf, offset, buf, len);
+}
+
+static struct mdev_virtio_device_ops ifc_mdev_ops = {
+	.get_features  = ifcvf_mdev_get_features,
+	.set_features  = ifcvf_mdev_set_features,
+	.get_status    = ifcvf_mdev_get_status,
+	.set_status    = ifcvf_mdev_set_status,
+	.get_vq_num_max = ifcvf_mdev_get_vq_num_max,
+	.get_vq_state   = ifcvf_mdev_get_vq_state,
+	.set_vq_state   = ifcvf_mdev_set_vq_state,
+	.set_vq_cb      = ifcvf_mdev_set_vq_cb,
+	.set_vq_ready   = ifcvf_mdev_set_vq_ready,
+	.get_vq_ready	= ifcvf_mdev_get_vq_ready,
+	.set_vq_num     = ifcvf_mdev_set_vq_num,
+	.set_vq_address = ifcvf_mdev_set_vq_address,
+	.kick_vq        = ifcvf_mdev_kick_vq,
+	.get_generation	= ifcvf_mdev_get_generation,
+	.get_device_id	= ifcvf_mdev_get_device_id,
+	.get_vendor_id	= ifcvf_mdev_get_vendor_id,
+	.get_vq_align	= ifcvf_mdev_get_vq_align,
+	.get_config	= ifcvf_mdev_get_config,
+	.set_config	= ifcvf_mdev_set_config,
+};
+
+static int ifcvf_init_msix(struct ifcvf_adapter *adapter)
+{
+	struct pci_dev *pdev = to_pci_dev(adapter->dev);
+	struct ifcvf_hw *vf = &adapter->vf;
+	int vector, i, ret, irq;
+
+	ret = pci_alloc_irq_vectors(pdev, IFCVF_MAX_INTR,
+				    IFCVF_MAX_INTR, PCI_IRQ_MSIX);
+	if (ret < 0) {
+		IFC_ERR(adapter->dev, "Failed to alloc irq vectors\n");
+		return ret;
+	}
+
+	for (i = 0; i < IFCVF_MAX_QUEUE_PAIRS * 2; i++) {
+		vector = i + IFCVF_MSI_QUEUE_OFF;
+		irq = pci_irq_vector(pdev, vector);
+		ret = request_irq(irq, ifcvf_intr_handler, 0,
+				pci_name(pdev), &vf->vring[i]);
+		if (ret) {
+			IFC_ERR(adapter->dev,
+				"Failed to request irq for vq %d\n", i);
+			return ret;
+		}
+	}
+
+	return 0;
+}
+
+static void ifcvf_destroy_adapter(struct ifcvf_adapter *adapter)
+{
+	struct ifcvf_hw *vf = IFC_PRIVATE_TO_VF(adapter);
+	struct pci_dev *pdev = to_pci_dev(adapter->dev);
+	int i, vector, irq;
+
+	for (i = 0; i < IFCVF_MAX_QUEUE_PAIRS * 2; i++) {
+		vector = i + IFCVF_MSI_QUEUE_OFF;
+		irq = pci_irq_vector(pdev, vector);
+		free_irq(irq, &vf->vring[i]);
+	}
+}
+
+static ssize_t name_show(struct kobject *kobj, struct device *dev, char *buf)
+{
+	const char *name = "IFC VF virtio/vhost accelerator (virtio ring compatible)";
+
+	return sprintf(buf, "%s\n", name);
+}
+MDEV_TYPE_ATTR_RO(name);
+
+static ssize_t device_api_show(struct kobject *kobj, struct device *dev,
+			       char *buf)
+{
+	return sprintf(buf, "%s\n", VIRTIO_MDEV_DEVICE_API_STRING);
+}
+MDEV_TYPE_ATTR_RO(device_api);
+
+static ssize_t available_instances_show(struct kobject *kobj,
+					struct device *dev, char *buf)
+{
+	struct pci_dev *pdev;
+	struct ifcvf_adapter *adapter;
+
+	pdev = to_pci_dev(dev);
+	adapter = pci_get_drvdata(pdev);
+
+	return sprintf(buf, "%d\n", adapter->mdev_count);
+}
+
+MDEV_TYPE_ATTR_RO(available_instances);
+
+static ssize_t type_show(struct kobject *kobj,
+			struct device *dev, char *buf)
+{
+	return sprintf(buf, "%s\n", "net");
+}
+
+MDEV_TYPE_ATTR_RO(type);
+
+
+static struct attribute *mdev_types_attrs[] = {
+	&mdev_type_attr_name.attr,
+	&mdev_type_attr_device_api.attr,
+	&mdev_type_attr_available_instances.attr,
+	&mdev_type_attr_type.attr,
+	NULL,
+};
+
+static struct attribute_group mdev_type_group_virtio = {
+	.name  = "virtio_mdev",
+	.attrs = mdev_types_attrs,
+};
+
+static struct attribute_group mdev_type_group_vhost = {
+	.name  = "vhost_mdev",
+	.attrs = mdev_types_attrs,
+};
+
+static struct attribute_group *mdev_type_groups[] = {
+	&mdev_type_group_virtio,
+	&mdev_type_group_vhost,
+	NULL,
+};
+
+const struct attribute_group *mdev_dev_groups[] = {
+	NULL,
+};
+
+static int ifcvf_mdev_create(struct kobject *kobj, struct mdev_device *mdev)
+{
+	struct device *dev = mdev_parent_dev(mdev);
+	struct pci_dev *pdev = to_pci_dev(dev);
+	struct ifcvf_adapter *adapter = pci_get_drvdata(pdev);
+	int ret = 0;
+
+	mutex_lock(&adapter->mdev_lock);
+
+	if (adapter->mdev_count < IFCVF_MDEV_LIMIT) {
+		IFC_ERR(&pdev->dev,
+			"Can not create mdev, reached limitation %d\n",
+			IFCVF_MDEV_LIMIT);
+		ret = -EINVAL;
+		goto out;
+	}
+
+	if (!strcmp(kobj->name, "ifcvf-virtio_mdev"))
+		mdev_set_virtio_ops(mdev, &ifc_mdev_ops);
+
+	if (!strcmp(kobj->name, "ifcvf-vhost_mdev"))
+		mdev_set_vhost_ops(mdev, &ifc_mdev_ops);
+
+	mdev_set_drvdata(mdev, adapter);
+	mdev_set_iommu_device(mdev_dev(mdev), dev);
+	adapter->mdev_count--;
+
+out:
+	mutex_unlock(&adapter->mdev_lock);
+	return ret;
+}
+
+static int ifcvf_mdev_remove(struct mdev_device *mdev)
+{
+	struct device *dev = mdev_parent_dev(mdev);
+	struct pci_dev *pdev = to_pci_dev(dev);
+	struct ifcvf_adapter *adapter = pci_get_drvdata(pdev);
+
+	mutex_lock(&adapter->mdev_lock);
+	adapter->mdev_count++;
+	mutex_unlock(&adapter->mdev_lock);
+
+	return 0;
+}
+
+static struct mdev_parent_ops ifcvf_mdev_fops = {
+	.owner			= THIS_MODULE,
+	.supported_type_groups	= mdev_type_groups,
+	.mdev_attr_groups	= mdev_dev_groups,
+	.create			= ifcvf_mdev_create,
+	.remove			= ifcvf_mdev_remove,
+};
+
+static int ifcvf_probe(struct pci_dev *pdev, const struct pci_device_id *id)
+{
+	struct device *dev = &pdev->dev;
+	struct ifcvf_adapter *adapter;
+	struct ifcvf_hw *vf;
+	int ret, i;
+
+	adapter = kzalloc(sizeof(struct ifcvf_adapter), GFP_KERNEL);
+
+	if (adapter == NULL) {
+		ret = -ENOMEM;
+		goto fail;
+	}
+
+	mutex_init(&adapter->mdev_lock);
+	adapter->mdev_count = IFCVF_MDEV_LIMIT;
+	adapter->dev = dev;
+	pci_set_drvdata(pdev, adapter);
+	ret = pci_enable_device(pdev);
+
+	if (ret) {
+		IFC_ERR(adapter->dev, "Failed to enable device\n");
+		goto free_adapter;
+	}
+
+	ret = pci_request_regions(pdev, IFCVF_DRIVER_NAME);
+
+	if (ret) {
+		IFC_ERR(adapter->dev, "Failed to request MMIO region\n");
+		goto disable_device;
+	}
+
+	pci_set_master(pdev);
+	ret = ifcvf_init_msix(adapter);
+
+	if (ret) {
+		IFC_ERR(adapter->dev, "Failed to initialize MSI-X\n");
+		goto free_msix;
+	}
+
+	vf = &adapter->vf;
+	
+	for (i = 0; i < IFCVF_PCI_MAX_RESOURCE; i++) {
+		vf->mem_resource[i].phys_addr = pci_resource_start(pdev, i);
+		vf->mem_resource[i].len = pci_resource_len(pdev, i);
+		if (!vf->mem_resource[i].len) {
+			vf->mem_resource[i].addr = NULL;
+			continue;
+		}
+
+		vf->mem_resource[i].addr = pci_iomap_range(pdev, i, 0,
+				vf->mem_resource[i].len);
+		if (!vf->mem_resource[i].addr) {
+			IFC_ERR(adapter->dev, "Failed to map IO resource %d\n",
+				i);
+			ret = -1;
+			goto free_msix;
+		}
+	}
+
+	if (ifcvf_init_hw(vf, pdev) < 0) {
+		ret = -1;
+		goto destroy_adapter;
+	}
+
+	ret = mdev_register_device(dev, &ifcvf_mdev_fops);
+
+	if (ret) {
+		IFC_ERR(adapter->dev,  "Failed to register mdev device\n");
+		goto destroy_adapter;
+	}
+
+	return 0;
+
+destroy_adapter:
+	ifcvf_destroy_adapter(adapter);
+free_msix:
+	pci_free_irq_vectors(pdev);
+	pci_release_regions(pdev);
+disable_device:
+	pci_disable_device(pdev);
+free_adapter:
+	kfree(adapter);
+fail:
+	return ret;
+}
+
+static void ifcvf_remove(struct pci_dev *pdev)
+{
+	struct ifcvf_adapter *adapter = pci_get_drvdata(pdev);
+	struct device *dev = &pdev->dev;
+	struct ifcvf_hw *vf;
+	int i;
+
+	mdev_unregister_device(dev);
+
+	vf = &adapter->vf;
+	for (i = 0; i < IFCVF_PCI_MAX_RESOURCE; i++) {
+		if (vf->mem_resource[i].addr) {
+			pci_iounmap(pdev, vf->mem_resource[i].addr);
+			vf->mem_resource[i].addr = NULL;
+		}
+	}
+
+	ifcvf_destroy_adapter(adapter);
+	pci_free_irq_vectors(pdev);
+	pci_release_regions(pdev);
+	pci_disable_device(pdev);
+	kfree(adapter);
+}
+
+static struct pci_device_id ifcvf_pci_ids[] = {
+	{ PCI_DEVICE_SUB(IFCVF_VENDOR_ID,
+			IFCVF_DEVICE_ID,
+			IFCVF_SUBSYS_VENDOR_ID,
+			IFCVF_SUBSYS_DEVICE_ID) },
+	{ 0 },
+};
+MODULE_DEVICE_TABLE(pci, ifcvf_pci_ids);
+
+static struct pci_driver ifcvf_driver = {
+	.name     = IFCVF_DRIVER_NAME,
+	.id_table = ifcvf_pci_ids,
+	.probe    = ifcvf_probe,
+	.remove   = ifcvf_remove,
+};
+
+static int __init ifcvf_init_module(void)
+{
+	int ret;
+
+	ret = pci_register_driver(&ifcvf_driver);
+	return ret;
+}
+
+static void __exit ifcvf_exit_module(void)
+{
+	pci_unregister_driver(&ifcvf_driver);
+}
+
+module_init(ifcvf_init_module);
+module_exit(ifcvf_exit_module);
+
+MODULE_LICENSE("GPL v2");
+MODULE_VERSION(VERSION_STRING);
+MODULE_AUTHOR(DRIVER_AUTHOR);
```
#### [kvm-unit-tests PATCH v3] s390x: Load reset psw on diag308 reset
##### From: Janosch Frank <frankja@linux.ibm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Janosch Frank <frankja@linux.ibm.com>
X-Patchwork-Id: 11239313
Return-Path: <SRS0=xhWs=ZE=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 637CF13BD
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 12 Nov 2019 13:45:40 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 4CF4B2084F
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 12 Nov 2019 13:45:40 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727312AbfKLNpi (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 12 Nov 2019 08:45:38 -0500
Received: from mx0a-001b2d01.pphosted.com ([148.163.156.1]:34092 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1725919AbfKLNpi (ORCPT
        <rfc822;kvm@vger.kernel.org>); Tue, 12 Nov 2019 08:45:38 -0500
Received: from pps.filterd (m0098410.ppops.net [127.0.0.1])
        by mx0a-001b2d01.pphosted.com (8.16.0.27/8.16.0.27) with SMTP id
 xACDcKkM032457
        for <kvm@vger.kernel.org>; Tue, 12 Nov 2019 08:45:37 -0500
Received: from e06smtp02.uk.ibm.com (e06smtp02.uk.ibm.com [195.75.94.98])
        by mx0a-001b2d01.pphosted.com with ESMTP id 2w7w2jjd8h-1
        (version=TLSv1.2 cipher=AES256-GCM-SHA384 bits=256 verify=NOT)
        for <kvm@vger.kernel.org>; Tue, 12 Nov 2019 08:45:37 -0500
Received: from localhost
        by e06smtp02.uk.ibm.com with IBM ESMTP SMTP Gateway: Authorized Use
 Only! Violators will be prosecuted
        for <kvm@vger.kernel.org> from <frankja@linux.ibm.com>;
        Tue, 12 Nov 2019 13:45:33 -0000
Received: from b06avi18626390.portsmouth.uk.ibm.com (9.149.26.192)
        by e06smtp02.uk.ibm.com (192.168.101.132) with IBM ESMTP SMTP Gateway:
 Authorized Use Only! Violators will be prosecuted;
        (version=TLSv1/SSLv3 cipher=AES256-GCM-SHA384 bits=256/256)
        Tue, 12 Nov 2019 13:45:30 -0000
Received: from d06av26.portsmouth.uk.ibm.com (d06av26.portsmouth.uk.ibm.com
 [9.149.105.62])
        by b06avi18626390.portsmouth.uk.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id xACDirZn38666688
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Tue, 12 Nov 2019 13:44:53 GMT
Received: from d06av26.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 7AE66AE063;
        Tue, 12 Nov 2019 13:45:29 +0000 (GMT)
Received: from d06av26.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id C3076AE04D;
        Tue, 12 Nov 2019 13:45:28 +0000 (GMT)
Received: from localhost.localdomain (unknown [9.152.224.131])
        by d06av26.portsmouth.uk.ibm.com (Postfix) with ESMTP;
        Tue, 12 Nov 2019 13:45:28 +0000 (GMT)
From: Janosch Frank <frankja@linux.ibm.com>
To: kvm@vger.kernel.org
Cc: linux-s390@vger.kernel.org, david@redhat.com, thuth@redhat.com
Subject: [kvm-unit-tests PATCH v3] s390x: Load reset psw on diag308 reset
Date: Tue, 12 Nov 2019 08:45:26 -0500
X-Mailer: git-send-email 2.20.1
In-Reply-To: <7683adc7-2cd0-1103-d231-8a1577f1e673@redhat.com>
References: <7683adc7-2cd0-1103-d231-8a1577f1e673@redhat.com>
MIME-Version: 1.0
X-TM-AS-GCONF: 00
x-cbid: 19111213-0008-0000-0000-0000032E5D21
X-IBM-AV-DETECTION: SAVI=unused REMOTE=unused XFE=unused
x-cbparentid: 19111213-0009-0000-0000-00004A4D624F
Message-Id: <20191112134526.2106-1-frankja@linux.ibm.com>
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:,,
 definitions=2019-11-12_04:,,
 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 priorityscore=1501
 malwarescore=0 suspectscore=1 phishscore=0 bulkscore=0 spamscore=0
 clxscore=1015 lowpriorityscore=0 mlxscore=0 impostorscore=0
 mlxlogscore=999 adultscore=0 classifier=spam adjust=0 reason=mlx
 scancount=1 engine=8.0.1-1910280000 definitions=main-1911120123
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

On a diag308 subcode 0 CRs will be reset, so we need a PSW mask
without DAT. Also we need to set the short psw indication to be
compliant with the architecture.

Let's therefore define a reset PSW mask with 64 bit addressing and
short PSW indication that is compliant with architecture and use it.

Signed-off-by: Janosch Frank <frankja@linux.ibm.com>
---
 lib/s390x/asm-offsets.c  |  1 +
 lib/s390x/asm/arch_def.h |  3 ++-
 s390x/cstart64.S         | 24 +++++++++++++++++-------
 3 files changed, 20 insertions(+), 8 deletions(-)

```
#### [PATCH] KVM: x86: Optimization: Requst TLB flush in fast_cr3_switch() instead of do it directly
##### From: Liran Alon <liran.alon@oracle.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Liran Alon <liran.alon@oracle.com>
X-Patchwork-Id: 11239963
Return-Path: <SRS0=xhWs=ZE=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id DC4DB14E5
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 12 Nov 2019 18:33:18 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id BC1A520818
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 12 Nov 2019 18:33:18 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=oracle.com header.i=@oracle.com
 header.b="TuKPxAda"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726985AbfKLSdR (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 12 Nov 2019 13:33:17 -0500
Received: from userp2120.oracle.com ([156.151.31.85]:36876 "EHLO
        userp2120.oracle.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1725997AbfKLSdR (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 12 Nov 2019 13:33:17 -0500
Received: from pps.filterd (userp2120.oracle.com [127.0.0.1])
        by userp2120.oracle.com (8.16.0.27/8.16.0.27) with SMTP id
 xACIT7mx051885;
        Tue, 12 Nov 2019 18:33:08 GMT
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=oracle.com;
 h=from : to : cc :
 subject : date : message-id : mime-version : content-transfer-encoding;
 s=corp-2019-08-05; bh=wWQ+XXCF5YgQMrnaRY3fZBO2NMN3YdL3c3lbS2dt2/c=;
 b=TuKPxAdaxFY/A/1EKvGJ7enR9fp9iOLKjMPyLhyoX7SngmG6fpGNXtIqTyNNQ4+L0Fo2
 m8JcGXNvO28nuvvdMby+3omhKBd61dMV0wPWnrRXa1rGuLPK8DhDBx4m5BBiPKmI0kLa
 Ha6hedZPynXVgkgZvwSg56aS6NvWx91mIxSwcRGAIL9D+AivzuHB22tmI1p263FsrEzH
 /OXVkjS3+d/hQFNBmtEeSLVtQa9jYZo1/QsMIdspyFSOVcYPIh+5K7G4u6EKDNMAttNF
 YB/rjvT5SzI+oRyQEt1QEwbMrZt5UeaYgOTqdMa4b7mWjoO63t4rnLRoDOIOmF9WtB5D QA==
Received: from userp3020.oracle.com (userp3020.oracle.com [156.151.31.79])
        by userp2120.oracle.com with ESMTP id 2w5p3qpq6f-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Tue, 12 Nov 2019 18:33:08 +0000
Received: from pps.filterd (userp3020.oracle.com [127.0.0.1])
        by userp3020.oracle.com (8.16.0.27/8.16.0.27) with SMTP id
 xACINJTc091336;
        Tue, 12 Nov 2019 18:33:07 GMT
Received: from aserv0122.oracle.com (aserv0122.oracle.com [141.146.126.236])
        by userp3020.oracle.com with ESMTP id 2w7vbb94k4-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Tue, 12 Nov 2019 18:33:07 +0000
Received: from abhmp0005.oracle.com (abhmp0005.oracle.com [141.146.116.11])
        by aserv0122.oracle.com (8.14.4/8.14.4) with ESMTP id xACIX6oZ005435;
        Tue, 12 Nov 2019 18:33:06 GMT
Received: from Lirans-MBP.Home (/109.64.228.241)
        by default (Oracle Beehive Gateway v4.0)
        with ESMTP ; Tue, 12 Nov 2019 10:33:06 -0800
From: Liran Alon <liran.alon@oracle.com>
To: pbonzini@redhat.com, rkrcmar@redhat.com, kvm@vger.kernel.org
Cc: sean.j.christopherson@intel.com, jmattson@google.com,
        vkuznets@redhat.com, Liran Alon <liran.alon@oracle.com>,
        Bhavesh Davda <bhavesh.davda@oracle.com>
Subject: [PATCH] KVM: x86: Optimization: Requst TLB flush in fast_cr3_switch()
 instead of do it directly
Date: Tue, 12 Nov 2019 20:33:00 +0200
Message-Id: <20191112183300.6959-1-liran.alon@oracle.com>
X-Mailer: git-send-email 2.20.1
MIME-Version: 1.0
X-Proofpoint-Virus-Version: vendor=nai engine=6000 definitions=9439
 signatures=668685
X-Proofpoint-Spam-Details: rule=notspam policy=default score=0 suspectscore=0
 malwarescore=0
 phishscore=0 bulkscore=0 spamscore=0 mlxscore=0 mlxlogscore=999
 adultscore=0 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.0.1-1910280000 definitions=main-1911120158
X-Proofpoint-Virus-Version: vendor=nai engine=6000 definitions=9439
 signatures=668685
X-Proofpoint-Spam-Details: rule=notspam policy=default score=0
 priorityscore=1501 malwarescore=0
 suspectscore=0 phishscore=0 bulkscore=0 spamscore=0 clxscore=1015
 lowpriorityscore=0 mlxscore=0 impostorscore=0 mlxlogscore=999 adultscore=0
 classifier=spam adjust=0 reason=mlx scancount=1 engine=8.0.1-1910280000
 definitions=main-1911120159
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

When KVM emulates a nested VMEntry (L1->L2 VMEntry), it switches mmu root
page. If nEPT is used, this will happen from
kvm_init_shadow_ept_mmu()->__kvm_mmu_new_cr3() and otherwise it will
happpen from nested_vmx_load_cr3()->kvm_mmu_new_cr3(). Either case,
__kvm_mmu_new_cr3() will use fast_cr3_switch() in attempt to switch to a
previously cached root page.

In case fast_cr3_switch() finds a matching cached root page, it will
set it in mmu->root_hpa and request KVM_REQ_LOAD_CR3 such that on
next entry to guest, KVM will set root HPA in appropriate hardware
fields (e.g. vmcs->eptp). In addition, fast_cr3_switch() calls
kvm_x86_ops->tlb_flush() in order to flush TLB as MMU root page
was replaced.

This works as mmu->root_hpa, which vmx_flush_tlb() use, was
already replaced in cached_root_available(). However, this may
result in unnecessary INVEPT execution because a KVM_REQ_TLB_FLUSH
may have already been requested. For example, by prepare_vmcs02()
in case L1 don't use VPID.

Therefore, change fast_cr3_switch() to just request TLB flush on
next entry to guest.

Reviewed-by: Bhavesh Davda <bhavesh.davda@oracle.com>
Signed-off-by: Liran Alon <liran.alon@oracle.com>
Reviewed-by: Sean Christopherson <sean.j.christopherson@intel.com>
---
 arch/x86/kvm/mmu.c | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
#### linux-next: manual merge of the kvm-fixes tree with Linus' tree
##### From: Stephen Rothwell <sfr@canb.auug.org.au>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Stephen Rothwell <sfr@canb.auug.org.au>
X-Patchwork-Id: 11240153
Return-Path: <SRS0=xhWs=ZE=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 307AC13B1
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 12 Nov 2019 21:00:47 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 1030021A49
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 12 Nov 2019 21:00:47 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=canb.auug.org.au header.i=@canb.auug.org.au
 header.b="MVzlhpxs"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727069AbfKLVAo (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 12 Nov 2019 16:00:44 -0500
Received: from ozlabs.org ([203.11.71.1]:38799 "EHLO ozlabs.org"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726697AbfKLVAn (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 12 Nov 2019 16:00:43 -0500
Received: from authenticated.ozlabs.org (localhost [127.0.0.1])
        (using TLSv1.3 with cipher TLS_AES_256_GCM_SHA384 (256/256 bits)
         key-exchange ECDHE (P-256) server-signature RSA-PSS (4096 bits)
 server-digest SHA256)
        (No client certificate requested)
        by mail.ozlabs.org (Postfix) with ESMTPSA id 47CKs43JPvz9sNH;
        Wed, 13 Nov 2019 08:00:40 +1100 (AEDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple; d=canb.auug.org.au;
        s=201702; t=1573592440;
        bh=Fl+cnxImbUdxKiW7FdnzmPITLo/GSGUVAFEIaaL5eo0=;
        h=Date:From:To:Cc:Subject:From;
        b=MVzlhpxs4rSOX1QJUEOnQslPQrXJ1R279YUQO/nyPodUDCZYiQgnotS9Te1U5QlvE
         rkBkppTlI2//CHrmsMnZyhuchJkETC9pz1EtBF6vCJr09TOSpzKB3h9UCdb8rlAnZX
         8sGd9jeNw4qYY/99JoP4dz31tKgFJ6Rq5rfEJ1WVBLDVEpRnOHpQM4ZYBm4k8z1ezh
         Z6aMmYQEsScFndpTBk7mkS+sFoKFNQ99f+lWPkdPZnPj95A//O1LNW8MxMLH3eSAGZ
         h84WtvE3mGGKRePiV6gjsk5pDU+EN7qXwPbrn+q9ivxs5lBy89n14pEjVb86NM6/9U
         8q7daU8fIDbFQ==
Date: Wed, 13 Nov 2019 08:00:27 +1100
From: Stephen Rothwell <sfr@canb.auug.org.au>
To: Paolo Bonzini <pbonzini@redhat.com>,
 Radim =?utf-8?b?S3LEjW3DocWZ?= <rkrcmar@redhat.com>,
 KVM <kvm@vger.kernel.org>
Cc: Linux Next Mailing List <linux-next@vger.kernel.org>,
        Linux Kernel Mailing List <linux-kernel@vger.kernel.org>,
        Junaid Shahid <junaids@google.com>,
        Thomas Gleixner <tglx@linutronix.de>
Subject: linux-next: manual merge of the kvm-fixes tree with Linus' tree
Message-ID: <20191113080027.7f97187e@canb.auug.org.au>
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Hi all,

Today's linux-next merge of the kvm-fixes tree got a conflict in:

  virt/kvm/kvm_main.c

between commit:

  1aa9b9572b10 ("kvm: x86: mmu: Recovery of shattered NX large pages")

from Linus' tree and commit:

  8a44119a98be ("KVM: Fix NULL-ptr deref after kvm_create_vm fails")

from the kvm-fixes tree.

I fixed it up (see below) and can carry the fix as necessary. This
is now fixed as far as linux-next is concerned, but any non trivial
conflicts should be mentioned to your upstream maintainer when your tree
is submitted for merging.  You may also want to consider cooperating
with the maintainer of the conflicting tree to minimise any particularly
complex conflicts.

```
#### [PATCH 1/7] x86/bugs: Add ITLB_MULTIHIT bug infrastructure
##### From: Paolo Bonzini <pbonzini@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Paolo Bonzini <pbonzini@redhat.com>
X-Patchwork-Id: 11240199
Return-Path: <SRS0=xhWs=ZE=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 3FB6913BD
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 12 Nov 2019 21:22:30 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 129762196E
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 12 Nov 2019 21:22:30 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=fail reason="signature verification failed" (2048-bit key)
 header.d=gmail.com header.i=@gmail.com header.b="c6heNSUx"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727224AbfKLVWT (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 12 Nov 2019 16:22:19 -0500
Received: from mail-wm1-f65.google.com ([209.85.128.65]:40246 "EHLO
        mail-wm1-f65.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1727069AbfKLVVo (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 12 Nov 2019 16:21:44 -0500
Received: by mail-wm1-f65.google.com with SMTP id f3so4508810wmc.5;
        Tue, 12 Nov 2019 13:21:41 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=sender:from:to:subject:date:message-id:in-reply-to:references;
        bh=JnYn9uI3yxG6VZUb0pRxgCquzXyinIAZQISEMZhmypI=;
        b=c6heNSUxxH0oSCrrZxfbuO1+iBKrdMQPa1BgSH2jEDX7jL30fU/j2fySQZZC0bUpUG
         yurhMl/qRZbzE41t/pGuNSf1a/5mDIJ3F3eSS1CE5Ot5O/ytZcweG+wArghZ6CdhKVnu
         IAMfek98DzNDTKQOon6AYCm4CvPqf8dTaKtMibKJowETWqmxxHDVbvNVayirLLnkgTmV
         jOBJNttUDt5PH0Sn20pgeWsKF/NlTB8df7FpAK6C2p7N0cYO9RnePFrdEEzvNUwXfs7g
         DR7XSmN45gZs1HTCfVWrq1guTQXt3+ygY8rJOYZoLdPw+gbm0kjoZMEsLNFb7UkiS/T7
         Adxg==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:sender:from:to:subject:date:message-id
         :in-reply-to:references;
        bh=JnYn9uI3yxG6VZUb0pRxgCquzXyinIAZQISEMZhmypI=;
        b=UnMukUBbIKwf926K9c7X1prKzXb4GZ60LnwhoL0FnoQIuHmr9c5OEaUguBaLRQf6ex
         S8e4KOs+w5q+DYGtuuh8q3eaDZM4skFRCOu2JYWFZ7h091QKstOPUqooge1n/4Eq/YZR
         FmI+o8PILEbMyN1oc3bTw5fzzyQzLuPNzn6HfRt93+lbtACDQnF85yZ6C8Nhft4E2YKb
         355Y6g53sGgxvBE/HXwzKUXz1tTTw3xh7PEsP1oYQR5N5AgFveJtfR04E7xVGYS/YTqM
         MlD9w83i1kbQ8St28BY+9r6C3FVOUcPnxDHgxAlHxmB+GM/k6VUHSYEMLECCOrpvuEpo
         cn9g==
X-Gm-Message-State: APjAAAU8k36VLFrNwfQHXM+iBpSEVvuoEhgmIXTA7K63InfWiPxElxMk
        qMlpbl84E9AuFk3KVbnV7Xt7XXkw
X-Google-Smtp-Source: 
 APXvYqyflfP/bbvqcVZbOtkbkEMjU2ik2y3Bch5Qkw8SHzU2Rj4s0FcAH8rXTDMj2FRJY5Y+jNf82A==
X-Received: by 2002:a05:600c:299:: with SMTP id
 25mr6265599wmk.50.1573593699937;
        Tue, 12 Nov 2019 13:21:39 -0800 (PST)
Received: from 640k.lan ([93.56.166.5])
        by smtp.gmail.com with ESMTPSA id q25sm198664wra.3.2019.11.12.13.21.39
        (version=TLS1_2 cipher=ECDHE-RSA-AES128-GCM-SHA256 bits=128/128);
        Tue, 12 Nov 2019 13:21:39 -0800 (PST)
From: Paolo Bonzini <pbonzini@redhat.com>
To: linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Subject: [PATCH 1/7] x86/bugs: Add ITLB_MULTIHIT bug infrastructure
Date: Tue, 12 Nov 2019 22:21:31 +0100
Message-Id: <1573593697-25061-2-git-send-email-pbonzini@redhat.com>
X-Mailer: git-send-email 1.8.3.1
In-Reply-To: <1573593697-25061-1-git-send-email-pbonzini@redhat.com>
References: <1573593697-25061-1-git-send-email-pbonzini@redhat.com>
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Vineela Tummalapalli <vineela.tummalapalli@intel.com>

Some processors may incur a machine check error possibly resulting in an
unrecoverable CPU lockup when an instruction fetch encounters a TLB
multi-hit in the instruction TLB. This can occur when the page size is
changed along with either the physical address or cache type. The relevant
erratum can be found here:

   https://bugzilla.kernel.org/show_bug.cgi?id=205195

There are other processors affected for which the erratum does not fully
disclose the impact.

This issue affects both bare-metal x86 page tables and EPT.

It can be mitigated by either eliminating the use of large pages or by
using careful TLB invalidations when changing the page size in the page
tables.

Just like Spectre, Meltdown, L1TF and MDS, a new bit has been allocated in
MSR_IA32_ARCH_CAPABILITIES (PSCHANGE_MC_NO) and will be set on CPUs which
are mitigated against this issue.

Signed-off-by: Vineela Tummalapalli <vineela.tummalapalli@intel.com>
Co-developed-by: Pawan Gupta <pawan.kumar.gupta@linux.intel.com>
Signed-off-by: Pawan Gupta <pawan.kumar.gupta@linux.intel.com>
Signed-off-by: Paolo Bonzini <pbonzini@redhat.com>
Signed-off-by: Thomas Gleixner <tglx@linutronix.de>
---
 Documentation/ABI/testing/sysfs-devices-system-cpu |  1 +
 arch/x86/include/asm/cpufeatures.h                 |  1 +
 arch/x86/include/asm/msr-index.h                   |  7 +++
 arch/x86/kernel/cpu/bugs.c                         | 13 +++++
 arch/x86/kernel/cpu/common.c                       | 65 ++++++++++++----------
 drivers/base/cpu.c                                 |  8 +++
 include/linux/cpu.h                                |  2 +
 7 files changed, 67 insertions(+), 30 deletions(-)

```
#### [PATCH v3 01/23] mm/gup: pass flags arg to __gup_device_* functions
##### From: John Hubbard <jhubbard@nvidia.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 8bit
X-Patchwork-Submitter: John Hubbard <jhubbard@nvidia.com>
X-Patchwork-Id: 11238305
Return-Path: <SRS0=xhWs=ZE=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id B6E5B14E5
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 12 Nov 2019 00:10:31 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 8B88C21872
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 12 Nov 2019 00:10:31 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=nvidia.com header.i=@nvidia.com
 header.b="XgxPYsGD"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727716AbfKLAKX (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 11 Nov 2019 19:10:23 -0500
Received: from hqemgate14.nvidia.com ([216.228.121.143]:10648 "EHLO
        hqemgate14.nvidia.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1727321AbfKLAHR (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 11 Nov 2019 19:07:17 -0500
Received: from hqpgpgate101.nvidia.com (Not Verified[216.228.121.13]) by
 hqemgate14.nvidia.com (using TLS: TLSv1.2, DES-CBC3-SHA)
        id <B5dc9f7ab0001>; Mon, 11 Nov 2019 16:07:07 -0800
Received: from hqmail.nvidia.com ([172.20.161.6])
  by hqpgpgate101.nvidia.com (PGP Universal service);
  Mon, 11 Nov 2019 16:07:05 -0800
X-PGP-Universal: processed;
        by hqpgpgate101.nvidia.com on Mon, 11 Nov 2019 16:07:05 -0800
Received: from HQMAIL107.nvidia.com (172.20.187.13) by HQMAIL111.nvidia.com
 (172.20.187.18) with Microsoft SMTP Server (TLS) id 15.0.1473.3; Tue, 12 Nov
 2019 00:07:04 +0000
Received: from rnnvemgw01.nvidia.com (10.128.109.123) by HQMAIL107.nvidia.com
 (172.20.187.13) with Microsoft SMTP Server (TLS) id 15.0.1473.3 via Frontend
 Transport; Tue, 12 Nov 2019 00:07:03 +0000
Received: from blueforge.nvidia.com (Not Verified[10.110.48.28]) by
 rnnvemgw01.nvidia.com with Trustwave SEG (v7,5,8,10121)
        id <B5dc9f7a60006>; Mon, 11 Nov 2019 16:07:03 -0800
From: John Hubbard <jhubbard@nvidia.com>
To: Andrew Morton <akpm@linux-foundation.org>
CC: Al Viro <viro@zeniv.linux.org.uk>,
 Alex Williamson <alex.williamson@redhat.com>,
 Benjamin Herrenschmidt <benh@kernel.crashing.org>, =?utf-8?b?QmrDtnJuIFQ=?=
	=?utf-8?b?w7ZwZWw=?= <bjorn.topel@intel.com>,
 Christoph Hellwig <hch@infradead.org>,
 Dan Williams <dan.j.williams@intel.com>, Daniel Vetter <daniel@ffwll.ch>,
 Dave Chinner <david@fromorbit.com>, David Airlie <airlied@linux.ie>,
 "David S . Miller" <davem@davemloft.net>, Ira Weiny <ira.weiny@intel.com>,
 Jan Kara <jack@suse.cz>, Jason Gunthorpe <jgg@ziepe.ca>,
 Jens Axboe <axboe@kernel.dk>, Jonathan Corbet <corbet@lwn.net>,
	=?utf-8?b?SsOpcsO0bWUgR2xpc3Nl?= <jglisse@redhat.com>,
 Magnus Karlsson <magnus.karlsson@intel.com>,
 Mauro Carvalho Chehab <mchehab@kernel.org>,
 Michael Ellerman <mpe@ellerman.id.au>, Michal Hocko <mhocko@suse.com>,
 Mike Kravetz <mike.kravetz@oracle.com>, Paul Mackerras <paulus@samba.org>,
 Shuah Khan <shuah@kernel.org>, Vlastimil Babka <vbabka@suse.cz>,
 <bpf@vger.kernel.org>, <dri-devel@lists.freedesktop.org>,
 <kvm@vger.kernel.org>, <linux-block@vger.kernel.org>,
 <linux-doc@vger.kernel.org>, <linux-fsdevel@vger.kernel.org>,
 <linux-kselftest@vger.kernel.org>, <linux-media@vger.kernel.org>,
 <linux-rdma@vger.kernel.org>, <linuxppc-dev@lists.ozlabs.org>,
 <netdev@vger.kernel.org>, <linux-mm@kvack.org>,
 LKML <linux-kernel@vger.kernel.org>, John Hubbard <jhubbard@nvidia.com>,
 "Kirill A . Shutemov" <kirill.shutemov@linux.intel.com>
Subject: [PATCH v3 01/23] mm/gup: pass flags arg to __gup_device_* functions
Date: Mon, 11 Nov 2019 16:06:38 -0800
Message-ID: <20191112000700.3455038-2-jhubbard@nvidia.com>
X-Mailer: git-send-email 2.24.0
In-Reply-To: <20191112000700.3455038-1-jhubbard@nvidia.com>
References: <20191112000700.3455038-1-jhubbard@nvidia.com>
MIME-Version: 1.0
X-NVConfidentiality: public
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=nvidia.com; s=n1;
        t=1573517228; bh=/JjGbVZJ8qaDHiJyVc8rKJC41LC1ZjvKm126SlEIWtY=;
        h=X-PGP-Universal:From:To:CC:Subject:Date:Message-ID:X-Mailer:
         In-Reply-To:References:MIME-Version:X-NVConfidentiality:
         Content-Type:Content-Transfer-Encoding;
        b=XgxPYsGD5Cq3FBIJISLcRetCEazTGocWyf543MWJh0xxa/0V54dx42FHTdiMbtp9G
         bkhWUIOYRWPTqeAghnzLlcKq+4jG/ziNrBs8to4cFX5tjldntCGFxly2FDb/7dtuPB
         ofXOYWSWPiPo4pLPCp6sVUzJBklCoqa+pD5cMreZdifwGntgrWsOQZZezVmEDqPJnr
         WyAc41nboTdDAQA1l/f+ButLI0Guqa0dZMyR8Qo6jQgFrGI5VdU/2VYWZ9h0Rt7eWK
         V/9Hp3cxn3NKCsyExhyTjLc2HiWqAtDKfUPVARyab/T8fsXF3grzwRklGIWCTRClJw
         wkZJz9tcQbExw==
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

A subsequent patch requires access to gup flags, so
pass the flags argument through to the __gup_device_*
functions.

Also placate checkpatch.pl by shortening a nearby line.

Reviewed-by: Jérôme Glisse <jglisse@redhat.com>
Reviewed-by: Ira Weiny <ira.weiny@intel.com>
Cc: Kirill A. Shutemov <kirill.shutemov@linux.intel.com>
Signed-off-by: John Hubbard <jhubbard@nvidia.com>
---
 mm/gup.c | 28 ++++++++++++++++++----------
 1 file changed, 18 insertions(+), 10 deletions(-)

```
#### [PATCH] selftests: kvm: Simplify loop in kvm_create_max_vcpus test
##### From: Wainer dos Santos Moschetta <wainersm@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Wainer dos Santos Moschetta <wainersm@redhat.com>
X-Patchwork-Id: 11239425
Return-Path: <SRS0=xhWs=ZE=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 38B681747
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 12 Nov 2019 14:21:24 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 19FD0222C2
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 12 Nov 2019 14:21:24 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="ibxTOEjj"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727549AbfKLOVX (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 12 Nov 2019 09:21:23 -0500
Received: from us-smtp-1.mimecast.com ([205.139.110.61]:59353 "EHLO
        us-smtp-delivery-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S1727492AbfKLOVW (ORCPT
        <rfc822;kvm@vger.kernel.org>); Tue, 12 Nov 2019 09:21:22 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1573568479;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:content-type:content-type:
         content-transfer-encoding:content-transfer-encoding;
        bh=l888mZumwB9sUbXe+Otg+6BZArqn24A8WoDV+FXXsG4=;
        b=ibxTOEjjCaJNCpMAOjuBuL21ajRzX65QxQJXiSnGyL+Pg7S/iLzVemv/S8XF3hI+jzKJ45
        QILLP/YGWndotRXtvHQ2EI3uHQtsTtHRWmB27nUZQarflU/5+C1B59ymeYEf8i91eAJKr4
        yyp9LN7dxwwmRaT0EgvIRoUoHyP4Ys4=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-346-z3MrLAg7M_mdgQ6R2J2Pqg-1; Tue, 12 Nov 2019 09:21:16 -0500
Received: from smtp.corp.redhat.com (int-mx07.intmail.prod.int.phx2.redhat.com
 [10.5.11.22])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 30694107ACC4;
        Tue, 12 Nov 2019 14:21:15 +0000 (UTC)
Received: from virtlab501.virt.lab.eng.bos.redhat.com
 (virtlab501.virt.lab.eng.bos.redhat.com [10.19.152.162])
        by smtp.corp.redhat.com (Postfix) with ESMTP id D1EB0101E59D;
        Tue, 12 Nov 2019 14:21:11 +0000 (UTC)
From: Wainer dos Santos Moschetta <wainersm@redhat.com>
To: pbonzini@redhat.com, rkrcmar@redhat.com
Cc: shuah@kernel.org, kvm@vger.kernel.org,
        linux-kselftest@vger.kernel.org, linux-kernel@vger.kernel.org
Subject: [PATCH] selftests: kvm: Simplify loop in kvm_create_max_vcpus test
Date: Tue, 12 Nov 2019 09:21:11 -0500
Message-Id: <20191112142111.13528-1-wainersm@redhat.com>
X-Scanned-By: MIMEDefang 2.84 on 10.5.11.22
X-MC-Unique: z3MrLAg7M_mdgQ6R2J2Pqg-1
X-Mimecast-Spam-Score: 0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

On kvm_create_max_vcpus test remove unneeded local
variable in the loop that add vcpus to the VM.

Signed-off-by: Wainer dos Santos Moschetta <wainersm@redhat.com>
---
 tools/testing/selftests/kvm/kvm_create_max_vcpus.c | 7 ++-----
 1 file changed, 2 insertions(+), 5 deletions(-)

```
#### [PATCH V4] target/i386/kvm: Add Hyper-V direct tlb flush support
##### From: lantianyu1986@gmail.com

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Tianyu Lan <lantianyu1986@gmail.com>
X-Patchwork-Id: 11238507
Return-Path: <SRS0=xhWs=ZE=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 52D3B159A
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 12 Nov 2019 03:35:00 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 1BA29206C3
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 12 Nov 2019 03:35:00 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=gmail.com header.i=@gmail.com
 header.b="Ar5AXk2p"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726932AbfKLDez (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 11 Nov 2019 22:34:55 -0500
Received: from mail-pf1-f193.google.com ([209.85.210.193]:36192 "EHLO
        mail-pf1-f193.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726910AbfKLDez (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 11 Nov 2019 22:34:55 -0500
Received: by mail-pf1-f193.google.com with SMTP id b19so32067pfd.3
        for <kvm@vger.kernel.org>; Mon, 11 Nov 2019 19:34:54 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=from:to:cc:subject:date:message-id;
        bh=RjB3o0NjWZXINNESvPz4COiSojg7wROs/y6CgxKZ/Pw=;
        b=Ar5AXk2psvjukJXi6gdH+xtvXmPp9uIXKwTYX28+pv4edMenYVt2Q9cSx6Sir1B8To
         U/Mp7UNwz4u9P6dJcQtjMhdBxKtaekycaC+pbD1ure7q3xluNVB4AY694Wdw5hhbXVnj
         LCOw7QFIpSTm4GC9WPrTKXscJfsQ5h8EPGAgNsqrxdBSfO9qYez338FgkBWHcDsFytET
         4/fJcb2Qp8DPFg75MLd5Ed36cVo8VjZ3GhwtHY9VWQHzYNHgzp95trzk4oApjEOf1+Sv
         GdWYuiYl0LWZalpZUzwibW2heGA4Ks6Bn4tUENTyBrSlyKKZ4H+7oZX0er/id3Ug2alL
         KMqw==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id;
        bh=RjB3o0NjWZXINNESvPz4COiSojg7wROs/y6CgxKZ/Pw=;
        b=h4EHiGUUYiOyOK+E+krC5IS4F/Tb3fWcRiBvlz09zFAWeCGjov5PggVDoBYla0FtRv
         cWzGgRReXQDNt69Ahhr1HBIn7CsXGQkJeiu1Y6wXN3biFfYQqBEGgo/BjPsDyvhCAGXn
         quYLbseMm3x0ebxr35GHZCL2+VEUArvBg9IUJt+lLcDkx0+gNWAgrF9pqPUMcu/MfbaC
         8RX6ymjOcwvoNtv17JeLxzZa7pHYnCcbmqtT3MJP8yx1bPeCMGGB0Ku03I8/0Q1BGlx9
         EY2EkJ4/GEDCZGfw7c4csHib9KRIjiXBROqqLXydoLy4bBBcMGedDkK39ZBquZXRaEma
         tEqg==
X-Gm-Message-State: APjAAAXaJtXL7EyYE5ju/mdPqUd1khwcGW2M6jLR0w6k88N0H6KobVoF
        lsUgN4b9FSWaLRl81b/bdqk=
X-Google-Smtp-Source: 
 APXvYqxm3G75qyaUjRQQIkPwyZGO7sh/u2z8W5LqAbtVsVJkIsjXh8sN7kIATp92EqxAESEhDElMYQ==
X-Received: by 2002:a65:46c1:: with SMTP id n1mr11037437pgr.257.1573529693925;
        Mon, 11 Nov 2019 19:34:53 -0800 (PST)
Received: from localhost.corp.microsoft.com ([167.220.255.5])
        by smtp.googlemail.com with ESMTPSA id
 f5sm114018pjp.1.2019.11.11.19.34.50
        (version=TLS1_2 cipher=ECDHE-RSA-CHACHA20-POLY1305 bits=256/256);
        Mon, 11 Nov 2019 19:34:53 -0800 (PST)
From: lantianyu1986@gmail.com
X-Google-Original-From: Tianyu.Lan@microsoft.com
To: pbonzini@redhat.com, rth@twiddle.net, ehabkost@redhat.com,
        mtosatti@redhat.com, rkagan@virtuozzo.com, vkuznets@redhat.com
Cc: Tianyu Lan <Tianyu.Lan@microsoft.com>, qemu-devel@nongnu.org,
        kvm@vger.kernel.org
Subject: [PATCH V4] target/i386/kvm: Add Hyper-V direct tlb flush support
Date: Tue, 12 Nov 2019 11:34:27 +0800
Message-Id: <20191112033427.7204-1-Tianyu.Lan@microsoft.com>
X-Mailer: git-send-email 2.14.5
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Tianyu Lan <Tianyu.Lan@microsoft.com>

Hyper-V direct tlb flush targets KVM on Hyper-V guest.
Enable direct TLB flush for its guests meaning that TLB
flush hypercalls are handled by Level 0 hypervisor (Hyper-V)
bypassing KVM in Level 1. Due to the different ABI for hypercall
parameters between Hyper-V and KVM, KVM capabilities should be
hidden when enable Hyper-V direct tlb flush otherwise KVM
hypercalls may be intercepted by Hyper-V. Add new parameter
"hv-direct-tlbflush". Check expose_kvm and Hyper-V tlb flush
capability status before enabling the feature.

Signed-off-by: Tianyu Lan <Tianyu.Lan@microsoft.com>
Reviewed-by: Roman Kagan <rkagan@virtuozzo.com>
---
Change since v3:
       - Fix logic of Hyper-V passthrough mode with direct
       tlb flush.

Change sicne v2:
       - Update new feature description and name.
       - Change failure print log.

Change since v1:
       - Add direct tlb flush's Hyper-V property and use
       hv_cpuid_check_and_set() to check the dependency of tlbflush
       feature.
       - Make new feature work with Hyper-V passthrough mode.
---
 docs/hyperv.txt   | 10 ++++++++++
 target/i386/cpu.c |  2 ++
 target/i386/cpu.h |  1 +
 target/i386/kvm.c | 24 ++++++++++++++++++++++++
 4 files changed, 37 insertions(+)

```
