#### [RFC PATCH v6 1/7] arm/arm64: smccc/psci: add arm_smccc_1_1_get_conduit()
##### From: Jianyong Wu <jianyong.wu@arm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Jianyong Wu <jianyong.wu@arm.com>
X-Patchwork-Id: 11208957
Return-Path: <SRS0=LVJf=YR=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id C833813BD
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 24 Oct 2019 11:02:49 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id AEB2021872
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 24 Oct 2019 11:02:49 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2393379AbfJXLCo (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 24 Oct 2019 07:02:44 -0400
Received: from foss.arm.com ([217.140.110.172]:47418 "EHLO foss.arm.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S2389995AbfJXLCo (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 24 Oct 2019 07:02:44 -0400
Received: from usa-sjc-imap-foss1.foss.arm.com (unknown [10.121.207.14])
        by usa-sjc-mx-foss1.foss.arm.com (Postfix) with ESMTP id 1F28C4A7;
        Thu, 24 Oct 2019 04:02:29 -0700 (PDT)
Received: from entos-d05.shanghai.arm.com (entos-d05.shanghai.arm.com
 [10.169.40.35])
        by usa-sjc-imap-foss1.foss.arm.com (Postfix) with ESMTPA id
 C5A9C3F71A;
        Thu, 24 Oct 2019 04:02:23 -0700 (PDT)
From: Jianyong Wu <jianyong.wu@arm.com>
To: netdev@vger.kernel.org, yangbo.lu@nxp.com, john.stultz@linaro.org,
        tglx@linutronix.de, pbonzini@redhat.com,
        sean.j.christopherson@intel.com, maz@kernel.org,
        richardcochran@gmail.com, Mark.Rutland@arm.com, will@kernel.org,
        suzuki.poulose@arm.com
Cc: linux-kernel@vger.kernel.org, linux-arm-kernel@lists.infradead.org,
        kvmarm@lists.cs.columbia.edu, kvm@vger.kernel.org,
        Steve.Capper@arm.com, Kaly.Xin@arm.com, justin.he@arm.com,
        jianyong.wu@arm.com, nd@arm.com,
        Mark Rutland <mark.rutland@arm.com>,
        Catalin Marinas <catalin.marinas@arm.com>
Subject: [RFC PATCH v6 1/7] arm/arm64: smccc/psci: add
 arm_smccc_1_1_get_conduit()
Date: Thu, 24 Oct 2019 19:02:03 +0800
Message-Id: <20191024110209.21328-2-jianyong.wu@arm.com>
X-Mailer: git-send-email 2.17.1
In-Reply-To: <20191024110209.21328-1-jianyong.wu@arm.com>
References: <20191024110209.21328-1-jianyong.wu@arm.com>
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Mark Rutland <mark.rutland@arm.com>

SMCCC callers are currently amassing a collection of enums for the SMCCC
conduit, and are having to dig into the PSCI driver's internals in order
to figure out what to do.

Let's clean this up, with common SMCCC_CONDUIT_* definitions, and an
arm_smccc_1_1_get_conduit() helper that abstracts the PSCI driver's
internal state.

We can kill off the PSCI_CONDUIT_* definitions once we've migrated users
over to the new interface.

Signed-off-by: Mark Rutland <mark.rutland@arm.com>
Acked-by: Lorenzo Pieralisi <lorenzo.pieralisi@arm.com>
Acked-by: Will Deacon <will.deacon@arm.com>
Signed-off-by: Catalin Marinas <catalin.marinas@arm.com>
---
 drivers/firmware/psci/psci.c | 15 +++++++++++++++
 include/linux/arm-smccc.h    | 16 ++++++++++++++++
 2 files changed, 31 insertions(+)

```
#### [RFC v2 01/22] update-linux-headers: Import iommu.h
##### From: Liu Yi L <yi.l.liu@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Liu Yi L <yi.l.liu@intel.com>
X-Patchwork-Id: 11209463
Return-Path: <SRS0=LVJf=YR=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 0177A913
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 24 Oct 2019 13:01:14 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id D3E7321925
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 24 Oct 2019 13:01:13 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2502253AbfJXNBN (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 24 Oct 2019 09:01:13 -0400
Received: from mga04.intel.com ([192.55.52.120]:5155 "EHLO mga04.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726484AbfJXNBM (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 24 Oct 2019 09:01:12 -0400
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from fmsmga001.fm.intel.com ([10.253.24.23])
  by fmsmga104.fm.intel.com with ESMTP/TLS/DHE-RSA-AES256-GCM-SHA384;
 24 Oct 2019 06:01:12 -0700
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.68,224,1569308400";
   d="scan'208";a="210156148"
Received: from iov.bj.intel.com ([10.238.145.67])
  by fmsmga001.fm.intel.com with ESMTP; 24 Oct 2019 06:01:09 -0700
From: Liu Yi L <yi.l.liu@intel.com>
To: qemu-devel@nongnu.org, mst@redhat.com, pbonzini@redhat.com,
        alex.williamson@redhat.com, peterx@redhat.com
Cc: eric.auger@redhat.com, david@gibson.dropbear.id.au,
        tianyu.lan@intel.com, kevin.tian@intel.com, yi.l.liu@intel.com,
        jun.j.tian@intel.com, yi.y.sun@intel.com,
        jacob.jun.pan@linux.intel.com, kvm@vger.kernel.org,
        Yi Sun <yi.y.sun@linux.intel.com>
Subject: [RFC v2 01/22] update-linux-headers: Import iommu.h
Date: Thu, 24 Oct 2019 08:34:22 -0400
Message-Id: <1571920483-3382-2-git-send-email-yi.l.liu@intel.com>
X-Mailer: git-send-email 2.7.4
In-Reply-To: <1571920483-3382-1-git-send-email-yi.l.liu@intel.com>
References: <1571920483-3382-1-git-send-email-yi.l.liu@intel.com>
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Eric Auger <eric.auger@redhat.com>

Update the script to import the new iommu.h uapi header.

Cc: Kevin Tian <kevin.tian@intel.com>
Cc: Jacob Pan <jacob.jun.pan@linux.intel.com>
Cc: Peter Xu <peterx@redhat.com>
Cc: Yi Sun <yi.y.sun@linux.intel.com>
Signed-off-by: Eric Auger <eric.auger@redhat.com>
---
 scripts/update-linux-headers.sh | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
#### [PATCH v3 1/3] kvm: Don't clear reference count on kvm_create_vm() error path
##### From: Jim Mattson <jmattson@google.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Jim Mattson <jmattson@google.com>
X-Patchwork-Id: 11211053
Return-Path: <SRS0=LVJf=YR=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 03F9914ED
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 24 Oct 2019 23:03:46 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id D76DD21A4C
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 24 Oct 2019 23:03:45 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=google.com header.i=@google.com
 header.b="mVOmSWgm"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1733191AbfJXXDp (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 24 Oct 2019 19:03:45 -0400
Received: from mail-pf1-f202.google.com ([209.85.210.202]:54296 "EHLO
        mail-pf1-f202.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726175AbfJXXDo (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 24 Oct 2019 19:03:44 -0400
Received: by mail-pf1-f202.google.com with SMTP id 2so334095pfv.21
        for <kvm@vger.kernel.org>; Thu, 24 Oct 2019 16:03:44 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=date:in-reply-to:message-id:mime-version:references:subject:from:to
         :cc;
        bh=ZvUs3prfac8nMA+DjbJb3Eq53kw+EBDussXq7EoWCTQ=;
        b=mVOmSWgmDo0egTO90mOaE4VXzmf3Bq6O7o3NZvERc/MGcS6+uvLJMZ920I5g9KWx58
         XZc55Extb5ex2bRzZIjvTuzgaUZGXsC2iI4N5ZmQRtpmpSV/F33ZSJXKkSsISO4xEEZ8
         6w8aM9JHrPm0XCV+wZoTrTsv0D3YiIepzQJE1PbNP9oUwXmUGXdv1gxoEdrTSN/n4dno
         FdXs7UNTheUp0tNxp/KY4btiffb20ebFTFBfgQJRTBhxMG80SpZjkYZMZ6EZeOjIbMcj
         psoo0VoLjoWQEiZ9o+bpRiff67LnkHk1WB00KsuJhOX9aBWKTbIyqwfQS3lgmRG3nsFY
         LX4w==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:date:in-reply-to:message-id:mime-version
         :references:subject:from:to:cc;
        bh=ZvUs3prfac8nMA+DjbJb3Eq53kw+EBDussXq7EoWCTQ=;
        b=cPvzciJG769C3Hc4G8+xAjq7HjPghwQae5MHHDzdn2S7CmaLWc0av05pJwAnqn4vBS
         bmciJEzWiOcVTkiEh3tUGCR0wHVODXQxXr8NDxEaxUzRviUYLtl+1SnAT1r0iDRAUA8K
         B9V0nw7ppgmeS1XOUqaIsA67mBVFfjE+DeqsYsFho3WduQetXsH9aTp1nIoRbktUnaxR
         W9MvaGUcfyNLehsCdA4DJKLZ5ozEYpmmB7rLMWxtueH5870DYkCz3YpKt2tltIWriXJh
         55fsVGilQj5m/o8mf69CYrBFVY8L/m7lYMITsxdlH91cYtdmvoH5LVnHzwkEpgadWDY4
         +uJw==
X-Gm-Message-State: APjAAAUYx1rwA7QYFcEGTo40OmUKmtAY2FyjXcRMUJdrwIUwnBmBeXtH
        F3+KvsXYCri3xd5B8YeuYwQM6Y059j4QMytKX9MyiHU49TI/z7XvfmUmDT1hqW5VUDdz5wCdVMh
        9d6JJorVTbAqKtQSa+fIdHCnCrB0DC/CP/AEnc0Ss7Y0BdK+CgTIc4VGcq/nJoWE=
X-Google-Smtp-Source: 
 APXvYqwMZOA/EZw6RnhifiGMxU/lx0Ye19kKB++dqwgcMu7FkCg+tIUYfuOZdrDAmi9Q3cdzb673eRPo/wrzZw==
X-Received: by 2002:a63:778f:: with SMTP id s137mr532709pgc.147.1571958223448;
 Thu, 24 Oct 2019 16:03:43 -0700 (PDT)
Date: Thu, 24 Oct 2019 16:03:25 -0700
In-Reply-To: <20191024230327.140935-1-jmattson@google.com>
Message-Id: <20191024230327.140935-2-jmattson@google.com>
Mime-Version: 1.0
References: <20191024230327.140935-1-jmattson@google.com>
X-Mailer: git-send-email 2.24.0.rc0.303.g954a862665-goog
Subject: [PATCH v3 1/3] kvm: Don't clear reference count on kvm_create_vm()
 error path
From: Jim Mattson <jmattson@google.com>
To: kvm@vger.kernel.org, Paolo Bonzini <pbonzini@redhat.com>,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        John Sperbeck <jsperbeck@google.com>,
        Junaid Shahid <junaids@google.com>
Cc: Jim Mattson <jmattson@google.com>
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Defer setting the reference count, kvm->users_count, until the VM is
guaranteed to be created, so that the reference count need not be
cleared on the error path.

Suggested-by: Sean Christopherson <sean.j.christopherson@intel.com>
Signed-off-by: Jim Mattson <jmattson@google.com>
Reviewed-by: Junaid Shahid <junaids@google.com>
---
 virt/kvm/kvm_main.c | 8 ++++++--
 1 file changed, 6 insertions(+), 2 deletions(-)

```
#### [RFC 01/37] DOCUMENTATION: protvirt: Protected virtual machine introduction
##### From: Janosch Frank <frankja@linux.ibm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Janosch Frank <frankja@linux.ibm.com>
X-Patchwork-Id: 11209087
Return-Path: <SRS0=LVJf=YR=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 8E513112B
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 24 Oct 2019 11:41:54 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 767602166E
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 24 Oct 2019 11:41:54 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2407227AbfJXLlx (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 24 Oct 2019 07:41:53 -0400
Received: from mx0a-001b2d01.pphosted.com ([148.163.156.1]:26538 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S2436528AbfJXLlx (ORCPT
        <rfc822;kvm@vger.kernel.org>); Thu, 24 Oct 2019 07:41:53 -0400
Received: from pps.filterd (m0098399.ppops.net [127.0.0.1])
        by mx0a-001b2d01.pphosted.com (8.16.0.27/8.16.0.27) with SMTP id
 x9OBb8sN137772
        for <kvm@vger.kernel.org>; Thu, 24 Oct 2019 07:41:52 -0400
Received: from e06smtp07.uk.ibm.com (e06smtp07.uk.ibm.com [195.75.94.103])
        by mx0a-001b2d01.pphosted.com with ESMTP id 2vub4qge90-1
        (version=TLSv1.2 cipher=AES256-GCM-SHA384 bits=256 verify=NOT)
        for <kvm@vger.kernel.org>; Thu, 24 Oct 2019 07:41:51 -0400
Received: from localhost
        by e06smtp07.uk.ibm.com with IBM ESMTP SMTP Gateway: Authorized Use
 Only! Violators will be prosecuted
        for <kvm@vger.kernel.org> from <frankja@linux.ibm.com>;
        Thu, 24 Oct 2019 12:41:49 +0100
Received: from b06cxnps3074.portsmouth.uk.ibm.com (9.149.109.194)
        by e06smtp07.uk.ibm.com (192.168.101.137) with IBM ESMTP SMTP Gateway:
 Authorized Use Only! Violators will be prosecuted;
        (version=TLSv1/SSLv3 cipher=AES256-GCM-SHA384 bits=256/256)
        Thu, 24 Oct 2019 12:41:47 +0100
Received: from d06av21.portsmouth.uk.ibm.com (d06av21.portsmouth.uk.ibm.com
 [9.149.105.232])
        by b06cxnps3074.portsmouth.uk.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id x9OBfjak23658550
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Thu, 24 Oct 2019 11:41:45 GMT
Received: from d06av21.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id A37635204F;
        Thu, 24 Oct 2019 11:41:45 +0000 (GMT)
Received: from localhost.localdomain (unknown [9.152.224.131])
        by d06av21.portsmouth.uk.ibm.com (Postfix) with ESMTP id 16ADA52059;
        Thu, 24 Oct 2019 11:41:43 +0000 (GMT)
From: Janosch Frank <frankja@linux.ibm.com>
To: kvm@vger.kernel.org
Cc: linux-s390@vger.kernel.org, thuth@redhat.com, david@redhat.com,
        borntraeger@de.ibm.com, imbrenda@linux.ibm.com,
        mihajlov@linux.ibm.com, mimu@linux.ibm.com, cohuck@redhat.com,
        gor@linux.ibm.com, frankja@linux.ibm.com
Subject: [RFC 01/37] DOCUMENTATION: protvirt: Protected virtual machine
 introduction
Date: Thu, 24 Oct 2019 07:40:23 -0400
X-Mailer: git-send-email 2.20.1
In-Reply-To: <20191024114059.102802-1-frankja@linux.ibm.com>
References: <20191024114059.102802-1-frankja@linux.ibm.com>
MIME-Version: 1.0
X-TM-AS-GCONF: 00
x-cbid: 19102411-0028-0000-0000-000003AEC50B
X-IBM-AV-DETECTION: SAVI=unused REMOTE=unused XFE=unused
x-cbparentid: 19102411-0029-0000-0000-00002470F700
Message-Id: <20191024114059.102802-2-frankja@linux.ibm.com>
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:,,
 definitions=2019-10-24_08:,,
 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 priorityscore=1501
 malwarescore=0 suspectscore=1 phishscore=0 bulkscore=0 spamscore=0
 clxscore=1015 lowpriorityscore=0 mlxscore=0 impostorscore=0
 mlxlogscore=609 adultscore=0 classifier=spam adjust=0 reason=mlx
 scancount=1 engine=8.0.1-1908290000 definitions=main-1910240115
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Introduction to Protected VMs.

Signed-off-by: Janosch Frank <frankja@linux.ibm.com>
---
 Documentation/virtual/kvm/s390-pv.txt | 23 +++++++++++++++++++++++
 1 file changed, 23 insertions(+)
 create mode 100644 Documentation/virtual/kvm/s390-pv.txt

diff --git a/Documentation/virtual/kvm/s390-pv.txt b/Documentation/virtual/kvm/s390-pv.txt
new file mode 100644
index 000000000000..86ed95f36759
--- /dev/null
+++ b/Documentation/virtual/kvm/s390-pv.txt
@@ -0,0 +1,23 @@
+Ultravisor and Protected VMs
+===========================
+
+Summary:
+
+Protected VMs (PVM) are KVM VMs, where KVM can't access the VM's state
+like guest memory and guest registers anymore. Instead the PVMs are
+mostly managed by a new entity called Ultravisor (UV), which provides
+an API, so KVM and the PVM can request management actions.
+
+Each guest starts in the non-protected mode and then transitions into
+protected mode. On transition KVM registers the guest and its VCPUs
+with the Ultravisor and prepares everything for running it.
+
+The Ultravisor will secure and decrypt the guest's boot memory
+(i.e. kernel/initrd). It will safeguard state changes like VCPU
+starts/stops and injected interrupts while the guest is running.
+
+As access to the guest's state, like the SIE state description is
+normally needed to be able to run a VM, some changes have been made in
+SIE behavior and fields have different meaning for a PVM. SIE exits
+are minimized as much as possible to improve speed and reduce exposed
+guest state.

From patchwork Thu Oct 24 11:40:24 2019
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Janosch Frank <frankja@linux.ibm.com>
X-Patchwork-Id: 11209089
Return-Path: <SRS0=LVJf=YR=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 64BE31515
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 24 Oct 2019 11:41:56 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 3E0D921906
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 24 Oct 2019 11:41:56 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2439090AbfJXLlz (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 24 Oct 2019 07:41:55 -0400
Received: from mx0a-001b2d01.pphosted.com ([148.163.156.1]:7532 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S2407237AbfJXLly (ORCPT
        <rfc822;kvm@vger.kernel.org>); Thu, 24 Oct 2019 07:41:54 -0400
Received: from pps.filterd (m0098399.ppops.net [127.0.0.1])
        by mx0a-001b2d01.pphosted.com (8.16.0.27/8.16.0.27) with SMTP id
 x9OBb9sl137855
        for <kvm@vger.kernel.org>; Thu, 24 Oct 2019 07:41:53 -0400
Received: from e06smtp05.uk.ibm.com (e06smtp05.uk.ibm.com [195.75.94.101])
        by mx0a-001b2d01.pphosted.com with ESMTP id 2vub4qgea2-1
        (version=TLSv1.2 cipher=AES256-GCM-SHA384 bits=256 verify=NOT)
        for <kvm@vger.kernel.org>; Thu, 24 Oct 2019 07:41:53 -0400
Received: from localhost
        by e06smtp05.uk.ibm.com with IBM ESMTP SMTP Gateway: Authorized Use
 Only! Violators will be prosecuted
        for <kvm@vger.kernel.org> from <frankja@linux.ibm.com>;
        Thu, 24 Oct 2019 12:41:51 +0100
Received: from b06cxnps4076.portsmouth.uk.ibm.com (9.149.109.198)
        by e06smtp05.uk.ibm.com (192.168.101.135) with IBM ESMTP SMTP Gateway:
 Authorized Use Only! Violators will be prosecuted;
        (version=TLSv1/SSLv3 cipher=AES256-GCM-SHA384 bits=256/256)
        Thu, 24 Oct 2019 12:41:49 +0100
Received: from d06av21.portsmouth.uk.ibm.com (d06av21.portsmouth.uk.ibm.com
 [9.149.105.232])
        by b06cxnps4076.portsmouth.uk.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id x9OBflAx52560072
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Thu, 24 Oct 2019 11:41:47 GMT
Received: from d06av21.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 6853C5204F;
        Thu, 24 Oct 2019 11:41:47 +0000 (GMT)
Received: from localhost.localdomain (unknown [9.152.224.131])
        by d06av21.portsmouth.uk.ibm.com (Postfix) with ESMTP id D204152050;
        Thu, 24 Oct 2019 11:41:45 +0000 (GMT)
From: Janosch Frank <frankja@linux.ibm.com>
To: kvm@vger.kernel.org
Cc: linux-s390@vger.kernel.org, thuth@redhat.com, david@redhat.com,
        borntraeger@de.ibm.com, imbrenda@linux.ibm.com,
        mihajlov@linux.ibm.com, mimu@linux.ibm.com, cohuck@redhat.com,
        gor@linux.ibm.com, frankja@linux.ibm.com
Subject: [RFC 02/37] s390/protvirt: introduce host side setup
Date: Thu, 24 Oct 2019 07:40:24 -0400
X-Mailer: git-send-email 2.20.1
In-Reply-To: <20191024114059.102802-1-frankja@linux.ibm.com>
References: <20191024114059.102802-1-frankja@linux.ibm.com>
MIME-Version: 1.0
X-TM-AS-GCONF: 00
x-cbid: 19102411-0020-0000-0000-0000037DCE7C
X-IBM-AV-DETECTION: SAVI=unused REMOTE=unused XFE=unused
x-cbparentid: 19102411-0021-0000-0000-000021D414E1
Message-Id: <20191024114059.102802-3-frankja@linux.ibm.com>
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:,,
 definitions=2019-10-24_08:,,
 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 priorityscore=1501
 malwarescore=0 suspectscore=1 phishscore=0 bulkscore=0 spamscore=0
 clxscore=1015 lowpriorityscore=0 mlxscore=0 impostorscore=0
 mlxlogscore=999 adultscore=0 classifier=spam adjust=0 reason=mlx
 scancount=1 engine=8.0.1-1908290000 definitions=main-1910240115
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Vasily Gorbik <gor@linux.ibm.com>

Introduce KVM_S390_PROTECTED_VIRTUALIZATION_HOST kbuild option for
protected virtual machines hosting support code.

Add "prot_virt" command line option which controls if the kernel
protected VMs support is enabled at runtime.

Extend ultravisor info definitions and expose it via uv_info struct
filled in during startup.

Signed-off-by: Vasily Gorbik <gor@linux.ibm.com>
---
 .../admin-guide/kernel-parameters.txt         |  5 ++
 arch/s390/boot/Makefile                       |  2 +-
 arch/s390/boot/uv.c                           | 20 +++++++-
 arch/s390/include/asm/uv.h                    | 46 ++++++++++++++++--
 arch/s390/kernel/Makefile                     |  1 +
 arch/s390/kernel/setup.c                      |  4 --
 arch/s390/kernel/uv.c                         | 48 +++++++++++++++++++
 arch/s390/kvm/Kconfig                         |  9 ++++
 8 files changed, 126 insertions(+), 9 deletions(-)
 create mode 100644 arch/s390/kernel/uv.c

```
#### [PATCH] KVM: x86: return length in KVM_GET_CPUID2.
##### From: Matt Delco <delco@chromium.org>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Matt Delco <delco@chromium.org>
X-Patchwork-Id: 11208313
Return-Path: <SRS0=LVJf=YR=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 78A791515
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 24 Oct 2019 05:29:34 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 5703621872
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 24 Oct 2019 05:29:34 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=chromium.org header.i=@chromium.org
 header.b="ahC/OJwg"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2406766AbfJXF3d (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 24 Oct 2019 01:29:33 -0400
Received: from mail-pl1-f195.google.com ([209.85.214.195]:37266 "EHLO
        mail-pl1-f195.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S2404071AbfJXF3d (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 24 Oct 2019 01:29:33 -0400
Received: by mail-pl1-f195.google.com with SMTP id p13so37006pll.4
        for <kvm@vger.kernel.org>; Wed, 23 Oct 2019 22:29:33 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=chromium.org; s=google;
        h=from:to:cc:subject:date:message-id:mime-version
         :content-transfer-encoding;
        bh=MePgjdi/Ed9y573bxV4jUy7lIcKKe70AG165bjiiX1k=;
        b=ahC/OJwgE1PgJ1qiAk9afmQHhtoAHR7R2WcyYbYckM9pt/LuRx8EYKvyTQhdj/snUd
         e06jNlIcf3AqkY2U3oGo0cNTxgDAx3yN+lkOHOJBMHUN5vU5x6JodQPq1bCC2JYaEJRt
         8pTfmW0wr0YTXTBii9CYct252hl0oS78EwqBY=
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:mime-version
         :content-transfer-encoding;
        bh=MePgjdi/Ed9y573bxV4jUy7lIcKKe70AG165bjiiX1k=;
        b=GC5unEfHPCTEZ0e16S1dOiTfJ+8qYC1ktXhGinavbD93qTie6YYW5RsNw6j8iIcRQV
         Dl3u/Yif1rOT+NGVzIAqiEmBO+Na4N5XKCu/PwaR4ECtgkv538vmThpA9qtCllkzh8MN
         91aKnavDctJEVD4UBr/cdC0HvdhQJK3vdH8nnKEhTNHqesV6RtYIAqUcv09cMtdKDQFF
         /9YHMYKm4JjHvykgEGxOnXuchGr4J9Co9vlgpV0/tG8t7YxQgGUEjYCvbLlbCwUcmkX2
         f/8GsPyosz1dVh1hfKaRgqZ1jLjrMeKB5gKh3PfHRzEaCjcgkrCO3+F1aPiXUzR2mJx8
         wbqw==
X-Gm-Message-State: APjAAAU/TpAj8iLko2PPK4tIq6PlGPRM39vhkNPnHFsfHtzBdi68iHFt
        /sjajJ4IgnuTPM/nPJAdypglSN9Z798=
X-Google-Smtp-Source: 
 APXvYqxL10Pw/zaVUwgC6Nbc/IXk/HSCieVNPHD0W/L0t7bMoGTzhj2/TB9vNI5bkE7vGJ9C//4R2A==
X-Received: by 2002:a17:902:be0f:: with SMTP id
 r15mr354746pls.72.1571894972396;
        Wed, 23 Oct 2019 22:29:32 -0700 (PDT)
Received: from localhost ([2620:0:1002:19:d6d5:8aa1:4314:d1e6])
        by smtp.gmail.com with ESMTPSA id
 o123sm14765923pfg.161.2019.10.23.22.29.30
        (version=TLS1_3 cipher=TLS_AES_128_GCM_SHA256 bits=128/128);
        Wed, 23 Oct 2019 22:29:31 -0700 (PDT)
From: Matt Delco <delco@chromium.org>
To: kvm@vger.kernel.org
Cc: Matt Delco <delco@chromium.org>
Subject: [PATCH] KVM: x86: return length in KVM_GET_CPUID2.
Date: Wed, 23 Oct 2019 22:29:18 -0700
Message-Id: <20191024052918.140750-1-delco@chromium.org>
X-Mailer: git-send-email 2.23.0.866.gb869b98d4c-goog
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

KVM_GET_CPUID2 never indicates the array length it populates. If an app
passes in an array that's too short then kvm_vcpu_ioctl_get_cpuid2() populates
the required array length and returns -E2BIG.  However, its caller then just
bails to "goto out", thus bypassing the copy_to_user(). If an app
passes in an array that's not too short, then
kvm_vcpu_ioctl_get_cpuid2() doesn't populate the array length. Its
caller will then call copy_to_user(), which is pointless since no data
values have been changed.

This change attempts to have KVM_GET_CPUID2 populate the array length on
both success and failure, and still indicate -E2BIG when a provided
array is too short.  I'm not sure if this type of change is considered
an API breakage and thus we need a KVM_GET_CPUID3.

Fixes: 0771671749b59 ("KVM: Enhance guest cpuid management", 2007-11-21)
Signed-off-by: Matt Delco <delco@chromium.org>
---
 arch/x86/kvm/cpuid.c | 1 +
 arch/x86/kvm/x86.c   | 7 ++++---
 2 files changed, 5 insertions(+), 3 deletions(-)

```
#### [PATCH net-next] vringh: fix copy direction of vringh_iov_push_kern()
##### From: Jason Wang <jasowang@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Jason Wang <jasowang@redhat.com>
X-Patchwork-Id: 11208263
Return-Path: <SRS0=LVJf=YR=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 951C313B1
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 24 Oct 2019 03:57:37 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 7264D20856
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 24 Oct 2019 03:57:37 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="cqA8xzS5"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2406724AbfJXD5c (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 23 Oct 2019 23:57:32 -0400
Received: from us-smtp-delivery-1.mimecast.com ([205.139.110.120]:53709 "EHLO
        us-smtp-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org
        with ESMTP id S2403853AbfJXD5b (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 23 Oct 2019 23:57:31 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1571889450;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:mime-version:mime-version:content-type:content-type:
         content-transfer-encoding:content-transfer-encoding;
        bh=IZ65iw36f6SbPMgVjFDkBT75rtV4HHm0X8KMpBrB9ZU=;
        b=cqA8xzS5j82Xuykb5++Sqwr81Bm3Ioe1cXR479wTiSci9BGmZxxoQ+pVssmzN0TLZFGyMT
        zfTeefeKkoz8GZQ5v8zaSwISu2b8Ksz6mAf0XIvR/2n9AfdmzowqNxXrL4bdhlhrUaGGbS
        6ax4iRdnGIeqs7eCD+fT73OkH17vPVA=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-170-v8dqu3FQOUWtVHUfozJ8CQ-1; Wed, 23 Oct 2019 23:57:27 -0400
Received: from smtp.corp.redhat.com (int-mx02.intmail.prod.int.phx2.redhat.com
 [10.5.11.12])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 4B29F80183D;
        Thu, 24 Oct 2019 03:57:26 +0000 (UTC)
Received: from jason-ThinkPad-X1-Carbon-6th.redhat.com
 (ovpn-12-199.pek2.redhat.com [10.72.12.199])
        by smtp.corp.redhat.com (Postfix) with ESMTP id CA82B60BF1;
        Thu, 24 Oct 2019 03:57:20 +0000 (UTC)
From: Jason Wang <jasowang@redhat.com>
To: mst@redhat.com, jasowang@redhat.com, kvm@vger.kernel.org,
        virtualization@lists.linux-foundation.org, netdev@vger.kernel.org,
        linux-kernel@vger.kernel.org
Subject: [PATCH net-next] vringh: fix copy direction of vringh_iov_push_kern()
Date: Thu, 24 Oct 2019 11:57:18 +0800
Message-Id: <20191024035718.7690-1-jasowang@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.12
X-MC-Unique: v8dqu3FQOUWtVHUfozJ8CQ-1
X-Mimecast-Spam-Score: 0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

We want to copy from iov to buf, so the direction was wrong.

Note: no real user for the helper, but it will be used by future
features.

Signed-off-by: Jason Wang <jasowang@redhat.com>
---
 drivers/vhost/vringh.c | 8 +++++++-
 1 file changed, 7 insertions(+), 1 deletion(-)

```
#### [PULL 01/10] arm: gic: check_acked: add test description
##### From: Andrew Jones <drjones@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Andrew Jones <drjones@redhat.com>
X-Patchwork-Id: 11209523
Return-Path: <SRS0=LVJf=YR=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id D61391864
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 24 Oct 2019 13:07:15 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id B493C20663
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 24 Oct 2019 13:07:15 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="PqkQRrWH"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2393537AbfJXNHP (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 24 Oct 2019 09:07:15 -0400
Received: from us-smtp-delivery-1.mimecast.com ([205.139.110.120]:39928 "EHLO
        us-smtp-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org
        with ESMTP id S2393528AbfJXNHO (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 24 Oct 2019 09:07:14 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1571922433;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:content-type:content-type:
         content-transfer-encoding:content-transfer-encoding:
         in-reply-to:in-reply-to:references:references;
        bh=mx2vnlJNR1H+BwVBhLpFkf4hbUqMBk6qNpXvPCTht54=;
        b=PqkQRrWHlg9djbi9XdY6ZmcAPFnjimUf8xbItOVa+a6LjK/UYwZkb7ISeuHjItEC9unEvP
        7FBtkdgEh3zXhdQjLNS4kTSKWfrWq0SxaN1JuSdHMUo1+cnToCakP6XAGf82rxeNiuKFzc
        cVwuvK5HeCLxefu1rVDY3KEd8JADPow=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-154-WZ_bPr6_Og2X583XrRUEzQ-1; Thu, 24 Oct 2019 09:07:06 -0400
Received: from smtp.corp.redhat.com (int-mx05.intmail.prod.int.phx2.redhat.com
 [10.5.11.15])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 997031800E00;
        Thu, 24 Oct 2019 13:07:05 +0000 (UTC)
Received: from kamzik.brq.redhat.com (unknown [10.43.2.160])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 9237354560;
        Thu, 24 Oct 2019 13:07:04 +0000 (UTC)
From: Andrew Jones <drjones@redhat.com>
To: kvm@vger.kernel.org
Cc: pbonzini@redhat.com, Andre Przywara <andre.przywara@arm.com>
Subject: [PULL 01/10] arm: gic: check_acked: add test description
Date: Thu, 24 Oct 2019 15:06:52 +0200
Message-Id: <20191024130701.31238-2-drjones@redhat.com>
In-Reply-To: <20191024130701.31238-1-drjones@redhat.com>
References: <20191024130701.31238-1-drjones@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.15
X-MC-Unique: WZ_bPr6_Og2X583XrRUEzQ-1
X-Mimecast-Spam-Score: 0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Andre Przywara <andre.przywara@arm.com>

At the moment the check_acked() IRQ helper function just prints a
generic "Completed" or "Timed out" message, without given a more
detailed test description.

To be able to tell the different IRQ tests apart, and also to allow
re-using it more easily, add a "description" parameter string,
which is prefixing the output line. This gives more information on what
exactly was tested.

This also splits the variable output part of the line (duration of IRQ
delivery) into a separate INFO: line, to not confuse testing frameworks.

Signed-off-by: Andre Przywara <andre.przywara@arm.com>
Reviewed-by: Andrew Jones <drjones@redhat.com>
Signed-off-by: Andrew Jones <drjones@redhat.com>
---
 arm/gic.c | 17 ++++++++++-------
 1 file changed, 10 insertions(+), 7 deletions(-)

```
#### [PATCH v2] kvm: x86: Add cr3 to struct kvm_debug_exit_archFrom: Jim Mattson <jmattson@google.com>
##### From: Jim Mattson <jmattson@google.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Jim Mattson <jmattson@google.com>
X-Patchwork-Id: 11210659
Return-Path: <SRS0=LVJf=YR=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 25D69913
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 24 Oct 2019 19:54:40 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 04E9721929
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 24 Oct 2019 19:54:40 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=google.com header.i=@google.com
 header.b="fXPWLXN6"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2406693AbfJXTyj (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 24 Oct 2019 15:54:39 -0400
Received: from mail-pf1-f202.google.com ([209.85.210.202]:42449 "EHLO
        mail-pf1-f202.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S2390431AbfJXTyi (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 24 Oct 2019 15:54:38 -0400
Received: by mail-pf1-f202.google.com with SMTP id w16so9668pfj.9
        for <kvm@vger.kernel.org>; Thu, 24 Oct 2019 12:54:38 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=date:message-id:mime-version:subject:from:to:cc;
        bh=haioOoskBRBydFeA6DvXJpqQ02xkMHKkeUpYLf3y49E=;
        b=fXPWLXN627Q7gWb6DoS6HKE29fuTMr1aTKmoYNV461mC2ZGBYMccc55lnm8YkRRQzH
         ftPGt/7KH++pWn7UT6KXAcQ7aaqARS5Tu0J6pKgOrJm0CwKInNwrwJ2OQY1cUqfdGiKp
         AnJuWJy+ANtjIpoiRm078wPrxmypvC8aNok8U3XhO+i4cwDFTUrn0xF3BnuQnX4245jW
         4uRai5bx5drZFYolaEtPBMcydBcwdf6/H9PyEANrCu/UJF6+50uf0/y+Ht0715NYMNX7
         43KcC5rWdN0kpBXVzieO0JkZtfVDy0wlw3BzsGZubQ5jy+WuBJ4I0cbs3/7qi3poeyXD
         7PeQ==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:date:message-id:mime-version:subject:from:to:cc;
        bh=haioOoskBRBydFeA6DvXJpqQ02xkMHKkeUpYLf3y49E=;
        b=FfPQMMtebECObpt9Kx1gOyUqzAYWSk3rbKdsfmb/t2Ehy91nakehiZMSrFBMfV25L3
         tP1TQChlP5D3dgw8N9M1V2al6PoZbCzat+MkTr25cgNWEYxEM8wVKfx0kFj7IjAOIzf5
         b6ksPHYAkx1lq8+p7OFvC0oh7hUKyF9i27Ez1+tOahiXtidjctEcGkVmTBSmHI4ucQld
         Tgyw3uTILeaWIIM7D5P/Krd5sMlbJBIu9j2apH8hBe4a4sDQsWBtGLhq9E69qZ3aKL7X
         Y7BaGkQl8Dclq3yczKYuMmCRZRt2b6GpCsk3qZ8R7W11CbvQ/dzZM7YkPdZnujy8PGY+
         DA7g==
X-Gm-Message-State: APjAAAXj9yCfjDlTv1XgW5a/IHulExb1R+TLa22p/mpMOdrdTRvjW0LX
        rzwgYhZklHMpz2fvCJRVD3akk0GkDn6b/L6Dzxlbg1eBMGdesmTIlalv5ZkA+PyypdHJPSLtZRm
        K3qdnaZFyD/vZdpsTvBVVMmGsZsexQ0ss12rh50LrXUdG8d9lLZYMz0n51wzZb1g=
X-Google-Smtp-Source: 
 APXvYqznf4QumgFLEDXHFFc5+Sm9/m/6dbDTp+S/bXlj9PS3/Axu98W9jxM6rAxNcNTWVBjOophFN/mmw+dX7g==
X-Received: by 2002:a63:1e04:: with SMTP id e4mr11451964pge.4.1571946877360;
 Thu, 24 Oct 2019 12:54:37 -0700 (PDT)
Date: Thu, 24 Oct 2019 12:54:31 -0700
Message-Id: <20191024195431.183667-1-jmattson@google.com>
Mime-Version: 1.0
X-Mailer: git-send-email 2.24.0.rc0.303.g954a862665-goog
Subject: [PATCH v2] kvm: x86: Add cr3 to struct kvm_debug_exit_arch
From: Jim Mattson <jmattson@google.com>
To: kvm@vger.kernel.org, Paolo Bonzini <pbonzini@redhat.com>
Cc: Ken Hofsass <hofsass@google.com>,
        Jim Mattson <jmattson@google.com>,
        Peter Shier <pshier@google.com>
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Ken Hofsass <hofsass@google.com>

A userspace agent can use cr3 to quickly determine whether a
KVM_EXIT_DEBUG is associated with a guest process of interest.

KVM_CAP_DEBUG_EVENT_PDBR indicates support for the extension.

Signed-off-by: Ken Hofsass <hofsass@google.com>
Signed-off-by: Jim Mattson <jmattson@google.com>
Cc: Peter Shier <pshier@google.com>
---
v1 -> v2: Changed KVM_CAP_DEBUG_EVENT_PG_BASE_ADDR to KVM_CAP_DEBUG_EVENT_PDBR
          Set debug.arch.cr3 in kvm_vcpu_do_singlestep and
	                        kvm_vcpu_check_breakpoint
          Added svm support
	  
 arch/x86/include/uapi/asm/kvm.h | 1 +
 arch/x86/kvm/svm.c              | 3 +++
 arch/x86/kvm/vmx/vmx.c          | 2 ++
 arch/x86/kvm/x86.c              | 3 +++
 include/uapi/linux/kvm.h        | 1 +
 5 files changed, 10 insertions(+)

```
#### [PATCH v2] KVM: x86: return length in KVM_GET_CPUID2.
##### From: Matt Delco <delco@chromium.org>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Matt Delco <delco@chromium.org>
X-Patchwork-Id: 11208493
Return-Path: <SRS0=LVJf=YR=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 12BCE112C
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 24 Oct 2019 08:25:12 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id E549D21928
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 24 Oct 2019 08:25:11 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=chromium.org header.i=@chromium.org
 header.b="U9u8BEdr"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2438163AbfJXIZL (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 24 Oct 2019 04:25:11 -0400
Received: from mail-pf1-f195.google.com ([209.85.210.195]:41308 "EHLO
        mail-pf1-f195.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1725947AbfJXIZK (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 24 Oct 2019 04:25:10 -0400
Received: by mail-pf1-f195.google.com with SMTP id q7so14654619pfh.8
        for <kvm@vger.kernel.org>; Thu, 24 Oct 2019 01:25:10 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=chromium.org; s=google;
        h=from:to:cc:subject:date:message-id:in-reply-to:references
         :mime-version:content-transfer-encoding;
        bh=hU4CSfYQ63kVLgy0WVaQhgAkxDVhbStNM/XZwCb+pGQ=;
        b=U9u8BEdrLTYHLxCVdyQ0V3Y9WN+h7BAw+8VyGXYlT9ZP3asAjaEXBACXCqMN4KXHYe
         uLywqbK455jhL6IPGKnE6y0j70ntK1RebrLODaHdhATZ2DD0pa0VwmRM5BodqYFaS5vI
         eSrq1ykqx9GRBRlJNYTQdiJy4dnbKU8jI8ZlM=
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:in-reply-to
         :references:mime-version:content-transfer-encoding;
        bh=hU4CSfYQ63kVLgy0WVaQhgAkxDVhbStNM/XZwCb+pGQ=;
        b=YazfgeUmpx/5GTAlJDYzH/L1tA3AkeofcZx/DY0rIE/aGvoEKSNHoEVoB3viXkEnU8
         62JN744hBoIneCxiLgYrTDo75rsSWY2nQnOPC4pbj5Fn09aqG0hf4dFQahxBld8d33Je
         wIw4+hGJ3MXpECn1bte6FZ+hgeDfBOnXe8dJ6jZlBa3XMUwpzTNdkvKalTQ81Z5ofxrD
         FOKH4gUEqNMo2zSWhZtXbWshFm0/FZMX1ropytbM/KyhkvHzMjb8lJfjjy2p8S3bjazS
         pM4Ki1tJJDaaA1WWCmAxJq0mEkEawWEuQRBwHnwX8OjwpZudB5qLUqrzqUpaNJ1KqM2r
         YK8Q==
X-Gm-Message-State: APjAAAW29V+75kqFILLm9p46J+dURmt0Q4T1W22ui6tpJ+XXdywK7RGy
        3wIcd1ghV9ZgEfEbAo7I5nHFXKm4Sdo=
X-Google-Smtp-Source: 
 APXvYqxYgKGNKdKEdxny+mlNOsqHTeUjdWWBTF7j0sC5yb+u8cuCSfcI6+ysPtBlh7uvWJTi2z+Anw==
X-Received: by 2002:a62:2643:: with SMTP id
 m64mr15526339pfm.232.1571905509576;
        Thu, 24 Oct 2019 01:25:09 -0700 (PDT)
Received: from localhost ([2620:0:1002:19:d6d5:8aa1:4314:d1e6])
        by smtp.gmail.com with ESMTPSA id
 b18sm25951736pfi.157.2019.10.24.01.25.08
        (version=TLS1_3 cipher=TLS_AES_128_GCM_SHA256 bits=128/128);
        Thu, 24 Oct 2019 01:25:08 -0700 (PDT)
From: Matt Delco <delco@chromium.org>
To: kvm@vger.kernel.org
Cc: Matt Delco <delco@chromium.org>
Subject: [PATCH v2] KVM: x86: return length in KVM_GET_CPUID2.
Date: Thu, 24 Oct 2019 01:24:52 -0700
Message-Id: <20191024082452.165627-1-delco@chromium.org>
X-Mailer: git-send-email 2.23.0.866.gb869b98d4c-goog
In-Reply-To: <20191024052918.140750-1-delco@chromium.org>
References: <20191024052918.140750-1-delco@chromium.org>
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

KVM_GET_CPUID2 never indicates the array length it populates. If an app
passes in an array that's too short then kvm_vcpu_ioctl_get_cpuid2() populates
the required array length and returns -E2BIG.  However, its caller then just
bails to "goto out", thus bypassing the copy_to_user(). If an app
passes in an array that's not too short, then
kvm_vcpu_ioctl_get_cpuid2() doesn't populate the array length. Its
caller will then call copy_to_user(), which is pointless since no data
values have been changed.

This change attempts to have KVM_GET_CPUID2 populate the array length on
both success and failure, and still indicate -E2BIG when a provided
array is too short.  I'm not sure if this type of change is considered
an API breakage and thus we need a KVM_GET_CPUID3.

Fixes: 0771671749b59 ("KVM: Enhance guest cpuid management", 2007-11-21)
Signed-off-by: Matt Delco <delco@chromium.org>
---
 arch/x86/kvm/cpuid.c | 1 +
 arch/x86/kvm/x86.c   | 8 ++++----
 2 files changed, 5 insertions(+), 4 deletions(-)

```
#### [PATCH 1/6] vfio/mdev: Add new "aggregate" parameter for mdev create
##### From: Zhenyu Wang <zhenyuw@linux.intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Zhenyu Wang <zhenyuw@linux.intel.com>
X-Patchwork-Id: 11208281
Return-Path: <SRS0=LVJf=YR=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 99E2C14E5
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 24 Oct 2019 05:08:37 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 834302166E
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 24 Oct 2019 05:08:37 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2437455AbfJXFIg (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 24 Oct 2019 01:08:36 -0400
Received: from mga11.intel.com ([192.55.52.93]:7748 "EHLO mga11.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1725298AbfJXFIg (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 24 Oct 2019 01:08:36 -0400
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from fmsmga007.fm.intel.com ([10.253.24.52])
  by fmsmga102.fm.intel.com with ESMTP/TLS/DHE-RSA-AES256-GCM-SHA384;
 23 Oct 2019 22:08:35 -0700
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.68,223,1569308400";
   d="scan'208";a="197627634"
Received: from debian-nuc.sh.intel.com ([10.239.160.133])
  by fmsmga007.fm.intel.com with ESMTP; 23 Oct 2019 22:08:34 -0700
From: Zhenyu Wang <zhenyuw@linux.intel.com>
To: kvm@vger.kernel.org
Cc: alex.williamson@redhat.com, kwankhede@nvidia.com,
        kevin.tian@intel.com, cohuck@redhat.com
Subject: [PATCH 1/6] vfio/mdev: Add new "aggregate" parameter for mdev create
Date: Thu, 24 Oct 2019 13:08:24 +0800
Message-Id: <20191024050829.4517-2-zhenyuw@linux.intel.com>
X-Mailer: git-send-email 2.24.0.rc0
In-Reply-To: <20191024050829.4517-1-zhenyuw@linux.intel.com>
References: <20191024050829.4517-1-zhenyuw@linux.intel.com>
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

For special mdev type which can aggregate instances for mdev device,
this extends mdev create interface by allowing extra "aggregate=xxx"
parameter, which is passed to mdev device model to be able to create
bundled number of instances for target mdev device.

Cc: Kirti Wankhede <kwankhede@nvidia.com>
Cc: Alex Williamson <alex.williamson@redhat.com>
Cc: Kevin Tian <kevin.tian@intel.com>
Cc: Cornelia Huck <cohuck@redhat.com>
Signed-off-by: Zhenyu Wang <zhenyuw@linux.intel.com>
---
v2: create new create_with_instances operator for vendor driver
v3:
- Change parameter name as "aggregate="
- Fix new interface comments.
- Parameter checking for new option, pass UUID string only to
  parse and properly end parameter for kstrtouint() conversion.
v4:
- rebase
- just call create_with_instances if exists, otherwise call create

 drivers/vfio/mdev/mdev_core.c    | 17 +++++++++++++++--
 drivers/vfio/mdev/mdev_private.h |  4 +++-
 drivers/vfio/mdev/mdev_sysfs.c   | 27 +++++++++++++++++++++++----
 include/linux/mdev.h             | 11 +++++++++++
 4 files changed, 52 insertions(+), 7 deletions(-)

```
#### [RFC v2 1/3] vfio: VFIO_IOMMU_CACHE_INVALIDATE
##### From: Liu Yi L <yi.l.liu@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Liu Yi L <yi.l.liu@intel.com>
X-Patchwork-Id: 11209427
Return-Path: <SRS0=LVJf=YR=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 4A04514E5
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 24 Oct 2019 12:52:55 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 344BC21872
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 24 Oct 2019 12:52:55 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2502184AbfJXMwy (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 24 Oct 2019 08:52:54 -0400
Received: from mga02.intel.com ([134.134.136.20]:11532 "EHLO mga02.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1731315AbfJXMwx (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 24 Oct 2019 08:52:53 -0400
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from orsmga003.jf.intel.com ([10.7.209.27])
  by orsmga101.jf.intel.com with ESMTP/TLS/DHE-RSA-AES256-GCM-SHA384;
 24 Oct 2019 05:52:53 -0700
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.68,224,1569308400";
   d="scan'208";a="201464806"
Received: from iov.bj.intel.com ([10.238.145.67])
  by orsmga003.jf.intel.com with ESMTP; 24 Oct 2019 05:52:50 -0700
From: Liu Yi L <yi.l.liu@intel.com>
To: alex.williamson@redhat.com, eric.auger@redhat.com
Cc: kevin.tian@intel.com, jacob.jun.pan@linux.intel.com,
        joro@8bytes.org, ashok.raj@intel.com, yi.l.liu@intel.com,
        jun.j.tian@intel.com, yi.y.sun@intel.com,
        jean-philippe.brucker@arm.com, peterx@redhat.com,
        iommu@lists.linux-foundation.org, kvm@vger.kernel.org
Subject: [RFC v2 1/3] vfio: VFIO_IOMMU_CACHE_INVALIDATE
Date: Thu, 24 Oct 2019 08:26:21 -0400
Message-Id: <1571919983-3231-2-git-send-email-yi.l.liu@intel.com>
X-Mailer: git-send-email 2.7.4
In-Reply-To: <1571919983-3231-1-git-send-email-yi.l.liu@intel.com>
References: <1571919983-3231-1-git-send-email-yi.l.liu@intel.com>
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Liu Yi L <yi.l.liu@linux.intel.com>

When the guest "owns" the stage 1 translation structures,  the host
IOMMU driver has no knowledge of caching structure updates unless
the guest invalidation requests are trapped and passed down to the
host.

This patch adds the VFIO_IOMMU_CACHE_INVALIDATE ioctl with aims
at propagating guest stage1 IOMMU cache invalidations to the host.

Cc: Kevin Tian <kevin.tian@intel.com>
Signed-off-by: Liu Yi L <yi.l.liu@linux.intel.com>
Signed-off-by: Eric Auger <eric.auger@redhat.com>
Signed-off-by: Jacob Pan <jacob.jun.pan@linux.intel.com>
---
 drivers/vfio/vfio_iommu_type1.c | 55 +++++++++++++++++++++++++++++++++++++++++
 include/uapi/linux/vfio.h       | 13 ++++++++++
 2 files changed, 68 insertions(+)

```
#### [PATCH] x86: Fix the register order to match struct regsFrom: Aaron Lewis <aaronlewis@google.com>
##### From: Aaron Lewis <aaronlewis@google.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Aaron Lewis <aaronlewis@google.com>
X-Patchwork-Id: 11210993
Return-Path: <SRS0=LVJf=YR=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 8C24613B1
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 24 Oct 2019 22:28:09 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 65AAB21929
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 24 Oct 2019 22:28:09 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=google.com header.i=@google.com
 header.b="QgIbbNPz"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1731543AbfJXW2I (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 24 Oct 2019 18:28:08 -0400
Received: from mail-ua1-f73.google.com ([209.85.222.73]:35112 "EHLO
        mail-ua1-f73.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1727635AbfJXW2I (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 24 Oct 2019 18:28:08 -0400
Received: by mail-ua1-f73.google.com with SMTP id z5so95091uae.2
        for <kvm@vger.kernel.org>; Thu, 24 Oct 2019 15:28:07 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=date:message-id:mime-version:subject:from:to:cc;
        bh=a6D0LvDSWvcPBISgGIo9u1LrVZKZJkW1is0FU9Md0OY=;
        b=QgIbbNPzQRq8lf+1LZBbxpjdewMwplI2ZoV9XkzgGYuAhNQyKZ1vHAPEiMbi7u04Gz
         KqWNHCK1iD6mvnvff7f92kfMTMraxWFI5RMWoo8z7PQjgeH722jU5nrjQ+GgSn+WCgDW
         0SG1fU3JnR9i3Ja4jYW1xVWDwRp034JHajPpa6sdU48Jt0pHAsfan3z5znxHJvxF8wIB
         KKprUAHaz7qtACM0xK4KpKhD/0vphO2PWh0so/wb04Z2pkkJuIuLcE4L4jOk/1ymxtAk
         kvbl1VbDxa70e2FgdW5ezpXQ7euebv7Ekn8RxST4yBiVWdGG9tBS0qJPShHxZUMiDpQm
         SSlQ==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:date:message-id:mime-version:subject:from:to:cc;
        bh=a6D0LvDSWvcPBISgGIo9u1LrVZKZJkW1is0FU9Md0OY=;
        b=YXebimbvNbIjE5JSLePaDSM/ZC0dlb2VQq8sL16+aO+kMKtyvjbhBI9v2kACCV54PQ
         8i7b4vl61jCElVSH6ROTCRtbObss789MXrZ6NV7qQb5p3Zcyzn50tvdNSotv9NKqJXSq
         h2tmWW2noTPjNBLqX+P6btLOGVJhWOLiamXpg9ZKMu/K4KYU2/OUBzevMRruvTbHXlER
         +zvZgg0azLXQMiCfRs3yUN9TKF8DyKYn6Aj+/ktTVPOhmcEv3ur/ZGpvBq1iE+7zuuDJ
         nVqCNYv5qGYq1iz8Um2tPrjnpNCE3hW5yC7xzilJXZDtH3nFAR7uBk75zs9Cj5n+sYeQ
         5pdQ==
X-Gm-Message-State: APjAAAVij1yqwU3aO4jNh4Yr7b3poks45ATR4VH9AiJgQDW8Zvm51mvh
        kJi5Oekyd+HE0AHi/kokZ18e8lB2jFsmOuLPgbxb8NhuYSUIZQ5ki5Xg+J8K8zOt79ooq6cEJ7i
        N73Pw+9hDS5mMPY7e4Qg8EUTfUAbLF1cjbNkqJT7KNNg8E81ZkkvfM3NSuatPAcSbXPPV
X-Google-Smtp-Source: 
 APXvYqwrgkNXBSU0aSof+GA/FUiQFEnHAHvhzyeU3r+6GzVla+fja8N0iBVoMaF6B4paXluH4IHotiNN/1VQegH3
X-Received: by 2002:a1f:b202:: with SMTP id b2mr453354vkf.59.1571956087093;
 Thu, 24 Oct 2019 15:28:07 -0700 (PDT)
Date: Thu, 24 Oct 2019 15:27:26 -0700
Message-Id: <20191024222725.160835-1-aaronlewis@google.com>
Mime-Version: 1.0
X-Mailer: git-send-email 2.24.0.rc0.303.g954a862665-goog
Subject: [PATCH] x86: Fix the register order to match struct regs
From: Aaron Lewis <aaronlewis@google.com>
To: kvm@vger.kernel.org
Cc: Aaron Lewis <aaronlewis@google.com>,
        Jim Mattson <jmattson@google.com>
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Fix the order the registers show up in SAVE_GPR and SAVE_GPR_C to ensure
the correct registers get the correct values.  Previously, the registers
were being written to (and read from) the wrong fields.

Reviewed-by: Jim Mattson <jmattson@google.com>
Signed-off-by: Aaron Lewis <aaronlewis@google.com>
---
 x86/vmx.h | 12 ++++++------
 1 file changed, 6 insertions(+), 6 deletions(-)

```
