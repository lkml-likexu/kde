#### [GIT PULL] VFIO updates for v5.6-rc1
##### From: Alex Williamson <alex.williamson@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Alex Williamson <alex.williamson@redhat.com>
X-Patchwork-Id: 11363405
Return-Path: <SRS0=qnBn=3X=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id E7B5192A
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon,  3 Feb 2020 20:40:46 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id C5E4C20721
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon,  3 Feb 2020 20:40:46 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="GNd73q3f"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727004AbgBCUkq (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 3 Feb 2020 15:40:46 -0500
Received: from us-smtp-delivery-1.mimecast.com ([205.139.110.120]:23122 "EHLO
        us-smtp-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org
        with ESMTP id S1726984AbgBCUko (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 3 Feb 2020 15:40:44 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1580762443;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:content-type:content-type:
         content-transfer-encoding:content-transfer-encoding;
        bh=pyvOKTyWkhnbfDDvx/t4H+37pFyaHZSbAEznQ9w1oyc=;
        b=GNd73q3fLGO/5C9mP9Wt1cWp6qlbH6J0SXqStMGaIAFRhTHAbxEC6XoaD+04da2K7unhLW
        TmPEpBiE2ihmxXv8p2Cft8Oaof0WMeaqOCOJfSWpy9xPetjbvgZNdcxDUCsxMDk2kTguH5
        pOzA+0Reh4Ago9pgqxyEJ8M+UwdNFAI=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-430-7l1xuXRFPdWWM4vbT9eVRQ-1; Mon, 03 Feb 2020 15:40:39 -0500
X-MC-Unique: 7l1xuXRFPdWWM4vbT9eVRQ-1
Received: from smtp.corp.redhat.com (int-mx03.intmail.prod.int.phx2.redhat.com
 [10.5.11.13])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 809C118C8C01;
        Mon,  3 Feb 2020 20:40:38 +0000 (UTC)
Received: from w520.home (ovpn-116-28.phx2.redhat.com [10.3.116.28])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 4853187B1D;
        Mon,  3 Feb 2020 20:40:38 +0000 (UTC)
Date: Mon, 3 Feb 2020 13:40:37 -0700
From: Alex Williamson <alex.williamson@redhat.com>
To: Linus Torvalds <torvalds@linux-foundation.org>
Cc: <linux-kernel@vger.kernel.org>,
        "kvm@vger.kernel.org" <kvm@vger.kernel.org>
Subject: [GIT PULL] VFIO updates for v5.6-rc1
Message-ID: <20200203134037.2fda624f@w520.home>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.13
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Hi Linus,

The following changes since commit c79f46a282390e0f5b306007bf7b11a46d529538:

  Linux 5.5-rc5 (2020-01-05 14:23:27 -0800)

are available in the Git repository at:

  git://github.com/awilliam/linux-vfio.git tags/vfio-v5.6-rc1

for you to fetch changes up to 7b5372ba04ca1caabed1470d4ec23001cde2eb91:

  vfio: platform: fix __iomem in vfio_platform_amdxgbe.c (2020-01-09 11:32:14 -0700)

----------------------------------------------------------------
VFIO updates for v5.6-rc1

 - Fix nvlink error path (Alexey Kardashevskiy)

 - Update nvlink and spapr to use mmgrab() (Julia Lawall)

 - Update static declaration (Ben Dooks)

 - Annotate __iomem to fix sparse warnings (Ben Dooks)

----------------------------------------------------------------
Alexey Kardashevskiy (1):
      vfio/spapr/nvlink2: Skip unpinning pages on error exit

Ben Dooks (Codethink) (2):
      vfio/mdev: make create attribute static
      vfio: platform: fix __iomem in vfio_platform_amdxgbe.c

Julia Lawall (2):
      vfio: vfio_pci_nvlink2: use mmgrab
      vfio/spapr_tce: use mmgrab

 drivers/vfio/mdev/mdev_sysfs.c                      | 2 +-
 drivers/vfio/pci/vfio_pci_nvlink2.c                 | 8 +++++---
 drivers/vfio/platform/reset/vfio_platform_amdxgbe.c | 4 ++--
 drivers/vfio/vfio_iommu_spapr_tce.c                 | 2 +-
 4 files changed, 9 insertions(+), 7 deletions(-)
```
#### [PATCH 1/2] KVM: MIPS: Fix a build error due to referencing not-yet-defined function
##### From: Sean Christopherson <sean.j.christopherson@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Sean Christopherson <sean.j.christopherson@intel.com>
X-Patchwork-Id: 11363299
Return-Path: <SRS0=qnBn=3X=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 4EE8E92A
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon,  3 Feb 2020 18:42:07 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 372E92087E
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon,  3 Feb 2020 18:42:07 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729581AbgBCSmD (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 3 Feb 2020 13:42:03 -0500
Received: from mga02.intel.com ([134.134.136.20]:49288 "EHLO mga02.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1729514AbgBCSmD (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 3 Feb 2020 13:42:03 -0500
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from orsmga001.jf.intel.com ([10.7.209.18])
  by orsmga101.jf.intel.com with ESMTP/TLS/DHE-RSA-AES256-GCM-SHA384;
 03 Feb 2020 10:42:01 -0800
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.70,398,1574150400";
   d="scan'208";a="310804551"
Received: from sjchrist-coffee.jf.intel.com ([10.54.74.202])
  by orsmga001.jf.intel.com with ESMTP; 03 Feb 2020 10:42:01 -0800
From: Sean Christopherson <sean.j.christopherson@intel.com>
To: Paolo Bonzini <pbonzini@redhat.com>
Cc: linux-mips@vger.kernel.org, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org, Davidlohr Bueso <dbueso@suse.de>
Subject: [PATCH 1/2] KVM: MIPS: Fix a build error due to referencing
 not-yet-defined function
Date: Mon,  3 Feb 2020 10:41:59 -0800
Message-Id: <20200203184200.23585-2-sean.j.christopherson@intel.com>
X-Mailer: git-send-email 2.24.1
In-Reply-To: <20200203184200.23585-1-sean.j.christopherson@intel.com>
References: <20200203184200.23585-1-sean.j.christopherson@intel.com>
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Hoist kvm_mips_comparecount_wakeup() above its only user,
kvm_arch_vcpu_create() to fix a compilation error due to referencing an
undefined function.

Fixes: d11dfed5d700 ("KVM: MIPS: Move all vcpu init code into kvm_arch_vcpu_create()")
Reported-by: kbuild test robot <lkp@intel.com>
Signed-off-by: Sean Christopherson <sean.j.christopherson@intel.com>
---
 arch/mips/kvm/mips.c | 42 +++++++++++++++++++++---------------------
 1 file changed, 21 insertions(+), 21 deletions(-)

```
#### [RFCv2 01/37] DOCUMENTATION: protvirt: Protected virtual machine introduction
##### From: Christian Borntraeger <borntraeger@de.ibm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Christian Borntraeger <borntraeger@de.ibm.com>
X-Patchwork-Id: 11362615
Return-Path: <SRS0=qnBn=3X=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id B6878138D
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon,  3 Feb 2020 13:20:06 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 94A662084E
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon,  3 Feb 2020 13:20:06 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728270AbgBCNUF (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 3 Feb 2020 08:20:05 -0500
Received: from mx0a-001b2d01.pphosted.com ([148.163.156.1]:56130 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1727201AbgBCNUE (ORCPT
        <rfc822;kvm@vger.kernel.org>); Mon, 3 Feb 2020 08:20:04 -0500
Received: from pps.filterd (m0098396.ppops.net [127.0.0.1])
        by mx0a-001b2d01.pphosted.com (8.16.0.42/8.16.0.42) with SMTP id
 013DEPSK066164
        for <kvm@vger.kernel.org>; Mon, 3 Feb 2020 08:20:01 -0500
Received: from pps.reinject (localhost [127.0.0.1])
        by mx0a-001b2d01.pphosted.com with ESMTP id 2xxgjwgps2-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT)
        for <kvm@vger.kernel.org>; Mon, 03 Feb 2020 08:20:01 -0500
Received: from m0098396.ppops.net (m0098396.ppops.net [127.0.0.1])
        by pps.reinject (8.16.0.36/8.16.0.36) with SMTP id 013DEVNk066809
        for <kvm@vger.kernel.org>; Mon, 3 Feb 2020 08:20:01 -0500
Received: from ppma04dal.us.ibm.com (7a.29.35a9.ip4.static.sl-reverse.com
 [169.53.41.122])
        by mx0a-001b2d01.pphosted.com with ESMTP id 2xxgjwgprk-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Mon, 03 Feb 2020 08:20:01 -0500
Received: from pps.filterd (ppma04dal.us.ibm.com [127.0.0.1])
        by ppma04dal.us.ibm.com (8.16.0.27/8.16.0.27) with SMTP id
 013DJ95a008188;
        Mon, 3 Feb 2020 13:20:00 GMT
Received: from b01cxnp22033.gho.pok.ibm.com (b01cxnp22033.gho.pok.ibm.com
 [9.57.198.23])
        by ppma04dal.us.ibm.com with ESMTP id 2xw0y6n91d-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Mon, 03 Feb 2020 13:20:00 +0000
Received: from b01ledav001.gho.pok.ibm.com (b01ledav001.gho.pok.ibm.com
 [9.57.199.106])
        by b01cxnp22033.gho.pok.ibm.com (8.14.9/8.14.9/NCO v10.0) with ESMTP
 id 013DJwem32113020
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Mon, 3 Feb 2020 13:19:58 GMT
Received: from b01ledav001.gho.pok.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 54DBB2805E;
        Mon,  3 Feb 2020 13:19:58 +0000 (GMT)
Received: from b01ledav001.gho.pok.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 512022806D;
        Mon,  3 Feb 2020 13:19:58 +0000 (GMT)
Received: from localhost.localdomain (unknown [9.114.17.106])
        by b01ledav001.gho.pok.ibm.com (Postfix) with ESMTP;
        Mon,  3 Feb 2020 13:19:58 +0000 (GMT)
From: Christian Borntraeger <borntraeger@de.ibm.com>
To: Christian Borntraeger <borntraeger@de.ibm.com>,
        Janosch Frank <frankja@linux.vnet.ibm.com>
Cc: KVM <kvm@vger.kernel.org>, Cornelia Huck <cohuck@redhat.com>,
        David Hildenbrand <david@redhat.com>,
        Thomas Huth <thuth@redhat.com>,
        Ulrich Weigand <Ulrich.Weigand@de.ibm.com>,
        Claudio Imbrenda <imbrenda@linux.ibm.com>,
        Andrea Arcangeli <aarcange@redhat.com>
Subject: [RFCv2 01/37] DOCUMENTATION: protvirt: Protected virtual machine
 introduction
Date: Mon,  3 Feb 2020 08:19:21 -0500
Message-Id: <20200203131957.383915-2-borntraeger@de.ibm.com>
X-Mailer: git-send-email 2.24.0
In-Reply-To: <20200203131957.383915-1-borntraeger@de.ibm.com>
References: <20200203131957.383915-1-borntraeger@de.ibm.com>
X-TM-AS-GCONF: 00
X-Proofpoint-UnRewURL: 0 URL was un-rewritten
MIME-Version: 1.0
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.138,18.0.572
 definitions=2020-02-03_04:2020-02-02,2020-02-03 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 bulkscore=0 mlxscore=0
 lowpriorityscore=0 malwarescore=0 suspectscore=0 spamscore=0
 mlxlogscore=999 adultscore=0 priorityscore=1501 impostorscore=0
 phishscore=0 clxscore=1015 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.12.0-1911200001 definitions=main-2002030099
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Janosch Frank <frankja@linux.ibm.com>

Add documentation about protected KVM guests.

Signed-off-by: Janosch Frank <frankja@linux.ibm.com>
---
 Documentation/virt/kvm/s390-pv.rst | 103 +++++++++++++++++++++++++++++
 MAINTAINERS                        |   1 +
 2 files changed, 104 insertions(+)
 create mode 100644 Documentation/virt/kvm/s390-pv.rst

diff --git a/Documentation/virt/kvm/s390-pv.rst b/Documentation/virt/kvm/s390-pv.rst
new file mode 100644
index 000000000000..5ef7e6cc2180
--- /dev/null
+++ b/Documentation/virt/kvm/s390-pv.rst
@@ -0,0 +1,103 @@
+.. SPDX-License-Identifier: GPL-2.0
+============================
+Ultravisor and Protected VMs
+============================
+
+Summary
+-------
+Protected virtual machines (PVM) are KVM VMs, where KVM can't access
+the VM's state like guest memory and guest registers anymore. Instead,
+the PVMs are mostly managed by a new entity called Ultravisor
+(UV). The UV provides an API that can be used by PVMs and KVM to
+request management actions.
+
+Each guest starts in the non-protected mode and then may make a
+request to transition into protected mode. On transition, KVM
+registers the guest and its VCPUs with the Ultravisor and prepares
+everything for running it.
+
+The Ultravisor will secure and decrypt the guest's boot memory
+(i.e. kernel/initrd). It will safeguard state changes like VCPU
+starts/stops and injected interrupts while the guest is running.
+
+As access to the guest's state, such as the SIE state description, is
+normally needed to be able to run a VM, some changes have been made in
+SIE behavior. A new format 4 state description has been introduced,
+where some fields have different meanings for a PVM. SIE exits are
+minimized as much as possible to improve speed and reduce exposed
+guest state.
+
+
+Interrupt injection
+-------------------
+Interrupt injection is safeguarded by the Ultravisor. As KVM doesn't
+have access to the VCPUs' lowcores, injection is handled via the
+format 4 state description.
+
+Machine check, external, IO and restart interruptions each can be
+injected on SIE entry via a bit in the interrupt injection control
+field (offset 0x54). If the guest cpu is not enabled for the interrupt
+at the time of injection, a validity interception is recognized. The
+format 4 state description contains fields in the interception data
+block where data associated with the interrupt can be transported.
+
+Program and Service Call exceptions have another layer of
+safeguarding; they can only be injected for instructions that have
+been intercepted into KVM. The exceptions need to be a valid outcome
+of an instruction emulation by KVM, e.g. we can never inject a
+addressing exception as they are reported by SIE since KVM has no
+access to the guest memory.
+
+
+Mask notification interceptions
+-------------------------------
+As a replacement for the lctl(g) and lpsw(e) instruction
+interceptions, two new interception codes have been introduced. One
+indicating that the contents of CRs 0, 6 or 14 have been changed. And
+one indicating PSW bit 13 changes.
+
+Instruction emulation
+---------------------
+With the format 4 state description for PVMs, the SIE instruction already
+interprets more instructions than it does with format 2. As it is not
+able to interpret every instruction, the SIE and the UV safeguard KVM's
+emulation inputs and outputs.
+
+Guest GRs and most of the instruction data, such as I/O data structures,
+are filtered. Instruction data is copied to and from the Secure
+Instruction Data Area. Guest GRs are put into / retrieved from the
+Interception-Data block.
+
+The Interception-Data block from the state description's offset 0x380
+contains GRs 0 - 16. Only GR values needed to emulate an instruction
+will be copied into this area.
+
+The Interception Parameters state description field still contains the
+the bytes of the instruction text, but with pre-set register values
+instead of the actual ones. I.e. each instruction always uses the same
+instruction text, in order not to leak guest instruction text.
+
+The Secure Instruction Data Area contains instruction storage
+data. Instruction data, i.e. data being referenced by an instruction
+like the SCCB for sclp, is moved over the SIDA When an instruction is
+intercepted, the SIE will only allow data and program interrupts for
+this instruction to be moved to the guest via the two data areas
+discussed before. Other data is either ignored or results in validity
+interceptions.
+
+
+Instruction emulation interceptions
+-----------------------------------
+There are two types of SIE secure instruction intercepts: the normal
+and the notification type. Normal secure instruction intercepts will
+make the guest pending for instruction completion of the intercepted
+instruction type, i.e. on SIE entry it is attempted to complete
+emulation of the instruction with the data provided by KVM. That might
+be a program exception or instruction completion.
+
+The notification type intercepts inform KVM about guest environment
+changes due to guest instruction interpretation. Such an interception
+is recognized for example for the store prefix instruction to provide
+the new lowcore location. On SIE reentry, any KVM data in the data
+areas is ignored, program exceptions are not injected and execution
+continues, as if no intercept had happened.
```
#### [PATCH v2 1/6] x86/split_lock: Add and export get_split_lock_detect_state()
##### From: Xiaoyao Li <xiaoyao.li@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Xiaoyao Li <xiaoyao.li@intel.com>
X-Patchwork-Id: 11362977
Return-Path: <SRS0=qnBn=3X=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 57C641395
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon,  3 Feb 2020 15:21:22 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 3E720217BA
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon,  3 Feb 2020 15:21:22 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728151AbgBCPVU (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 3 Feb 2020 10:21:20 -0500
Received: from mga02.intel.com ([134.134.136.20]:32939 "EHLO mga02.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726272AbgBCPVT (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 3 Feb 2020 10:21:19 -0500
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from fmsmga005.fm.intel.com ([10.253.24.32])
  by orsmga101.jf.intel.com with ESMTP/TLS/DHE-RSA-AES256-GCM-SHA384;
 03 Feb 2020 07:21:18 -0800
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.70,398,1574150400";
   d="scan'208";a="429473347"
Received: from lxy-dell.sh.intel.com ([10.239.13.109])
  by fmsmga005.fm.intel.com with ESMTP; 03 Feb 2020 07:21:17 -0800
From: Xiaoyao Li <xiaoyao.li@intel.com>
To: Paolo Bonzini <pbonzini@redhat.com>,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        Thomas Gleixner <tglx@linutronix.de>,
        Ingo Molnar <mingo@redhat.com>, Borislav Petkov <bp@alien8.de>,
        Andy Lutomirski <luto@amacapital.net>
Cc: x86@kernel.org, kvm@vger.kernel.org, linux-kernel@vger.kernel.org,
        David Laight <David.Laight@aculab.com>,
        Xiaoyao Li <xiaoyao.li@intel.com>
Subject: [PATCH v2 1/6] x86/split_lock: Add and export
 get_split_lock_detect_state()
Date: Mon,  3 Feb 2020 23:16:03 +0800
Message-Id: <20200203151608.28053-2-xiaoyao.li@intel.com>
X-Mailer: git-send-email 2.23.0
In-Reply-To: <20200203151608.28053-1-xiaoyao.li@intel.com>
References: <20200203151608.28053-1-xiaoyao.li@intel.com>
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

get_split_lock_detect_state() will be used by KVM module to get sld_state.

Signed-off-by: Xiaoyao Li <xiaoyao.li@intel.com>
---
 arch/x86/include/asm/cpu.h  | 12 ++++++++++++
 arch/x86/kernel/cpu/intel.c | 12 ++++++------
 2 files changed, 18 insertions(+), 6 deletions(-)

```
#### [PATCH v2 1/2] selftests: KVM: AMD Nested test infrastructure
##### From: Eric Auger <eric.auger@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Auger Eric <eric.auger@redhat.com>
X-Patchwork-Id: 11362233
Return-Path: <SRS0=qnBn=3X=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 70FBC138D
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon,  3 Feb 2020 09:09:40 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 3C8652082F
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon,  3 Feb 2020 09:09:40 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="bM6WHK1Z"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727896AbgBCJJa (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 3 Feb 2020 04:09:30 -0500
Received: from us-smtp-2.mimecast.com ([207.211.31.81]:45723 "EHLO
        us-smtp-delivery-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S1727577AbgBCJJa (ORCPT
        <rfc822;kvm@vger.kernel.org>); Mon, 3 Feb 2020 04:09:30 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1580720968;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding:
         in-reply-to:in-reply-to:references:references;
        bh=akqI3uT1a4bs/C9D8E72LRvHGUF4SgqiR/r6tQF9W/0=;
        b=bM6WHK1ZtRe8hZCGM4eTdQwV0xK580V9iMFGx64ZKVubvlI4orfHXsOH4KSLdHta2CwHQO
        1oSoqPSLKGiViTrFGgpmYeACfNibijmBtAmpEy94UPUgy8/3RGF+AIYqx7/TuIOqjjQk8B
        0/1iSaaUthNvHlD696nEUfYGEpqZqho=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-247-OunT8p1pNg2ikFyzpKgsKQ-1; Mon, 03 Feb 2020 04:09:26 -0500
X-MC-Unique: OunT8p1pNg2ikFyzpKgsKQ-1
Received: from smtp.corp.redhat.com (int-mx08.intmail.prod.int.phx2.redhat.com
 [10.5.11.23])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 569BA107ACC7;
        Mon,  3 Feb 2020 09:09:25 +0000 (UTC)
Received: from laptop.redhat.com (ovpn-116-37.ams2.redhat.com [10.36.116.37])
        by smtp.corp.redhat.com (Postfix) with ESMTP id F0F5F19C58;
        Mon,  3 Feb 2020 09:09:20 +0000 (UTC)
From: Eric Auger <eric.auger@redhat.com>
To: eric.auger.pro@gmail.com, eric.auger@redhat.com,
        linux-kernel@vger.kernel.org, kvm@vger.kernel.org,
        pbonzini@redhat.com, vkuznets@redhat.com
Cc: thuth@redhat.com, drjones@redhat.com, wei.huang2@amd.com
Subject: [PATCH v2 1/2] selftests: KVM: AMD Nested test infrastructure
Date: Mon,  3 Feb 2020 10:08:50 +0100
Message-Id: <20200203090851.19938-2-eric.auger@redhat.com>
In-Reply-To: <20200203090851.19938-1-eric.auger@redhat.com>
References: <20200203090851.19938-1-eric.auger@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.84 on 10.5.11.23
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Add the basic infrastructure needed to test AMD nested SVM.
This is largely copied from the KVM unit test infrastructure.

Signed-off-by: Eric Auger <eric.auger@redhat.com>
---
 tools/testing/selftests/kvm/Makefile          |   2 +-
 .../selftests/kvm/include/x86_64/processor.h  |  20 +
 .../selftests/kvm/include/x86_64/svm.h        | 355 ++++++++++++++++++
 tools/testing/selftests/kvm/lib/x86_64/svm.c  | 211 +++++++++++
 4 files changed, 587 insertions(+), 1 deletion(-)
 create mode 100644 tools/testing/selftests/kvm/include/x86_64/svm.h
 create mode 100644 tools/testing/selftests/kvm/lib/x86_64/svm.c

```
