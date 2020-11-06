#### [GIT PULL] VFIO fixes for v5.10-rc3
##### From: Alex Williamson <alex.williamson@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Alex Williamson <alex.williamson@redhat.com>
X-Patchwork-Id: 11885089
Return-Path: <SRS0=FTeU=EL=vger.kernel.org=kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-13.9 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_PULL_REQUEST,MAILING_LIST_MULTI,MENTIONS_GIT_HOSTING,SPF_HELO_NONE,
	SPF_PASS autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 3E839C388F7
	for <kvm@archiver.kernel.org>; Thu,  5 Nov 2020 20:52:03 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id CAB3B20724
	for <kvm@archiver.kernel.org>; Thu,  5 Nov 2020 20:52:02 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="YTVB0KHB"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1732043AbgKEUwB (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Thu, 5 Nov 2020 15:52:01 -0500
Received: from us-smtp-delivery-124.mimecast.com ([216.205.24.124]:56192 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1726996AbgKEUwB (ORCPT
        <rfc822;kvm@vger.kernel.org>); Thu, 5 Nov 2020 15:52:01 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1604609520;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:content-type:content-type:
         content-transfer-encoding:content-transfer-encoding;
        bh=1/9hAMj/ihEHlpI+S/GvjO7/yU7iXYK7gBElq3upyrE=;
        b=YTVB0KHBX3VPBgY3zgEk0lp+rf+VWWHU/66+NzWtLKYVzPQz1DkczMCLXzKshDI9BF2jDQ
        946z1E2uJ2J6e7ujQIJLGmqNfqPti94IMA22gKckwoadgkr4R/fRbdc4B0/jftYn3sote0
        Z6CdBAHwFZeQ1ZxDQHQfGKk+pjkxobE=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-165-yPmPi2XSMt-F5vdNMcLh-A-1; Thu, 05 Nov 2020 15:51:58 -0500
X-MC-Unique: yPmPi2XSMt-F5vdNMcLh-A-1
Received: from smtp.corp.redhat.com (int-mx06.intmail.prod.int.phx2.redhat.com
 [10.5.11.16])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id B36E58030A8;
        Thu,  5 Nov 2020 20:51:57 +0000 (UTC)
Received: from w520.home (ovpn-112-213.phx2.redhat.com [10.3.112.213])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 7B9F7508E8;
        Thu,  5 Nov 2020 20:51:57 +0000 (UTC)
Date: Thu, 5 Nov 2020 13:51:57 -0700
From: Alex Williamson <alex.williamson@redhat.com>
To: Linus Torvalds <torvalds@linux-foundation.org>
Cc: <linux-kernel@vger.kernel.org>,
        "kvm@vger.kernel.org" <kvm@vger.kernel.org>
Subject: [GIT PULL] VFIO fixes for v5.10-rc3
Message-ID: <20201105135157.72abcadb@w520.home>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.16
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Hi Linus,

The following changes since commit 3cea11cd5e3b00d91caf0b4730194039b45c5891:

  Linux 5.10-rc2 (2020-11-01 14:43:51 -0800)

are available in the Git repository at:

  git://github.com/awilliam/linux-vfio.git tags/vfio-v5.10-rc3

for you to fetch changes up to e4eccb853664de7bcf9518fb658f35e748bf1f68:

  vfio/pci: Bypass IGD init in case of -ENODEV (2020-11-03 11:07:40 -0700)

----------------------------------------------------------------
VFIO fixes for v5.10-rc3

 - Remove code by using existing helper (Zenghui Yu)

 - fsl-mc copy-user return and underflow fixes (Dan Carpenter)

 - fsl-mc static function declaration (Diana Craciun)

 - Fix ioeventfd sleeping under spinlock (Alex Williamson)

 - Fix pm reference count leak in vfio-platform (Zhang Qilong)

 - Allow opening IGD device w/o OpRegion support (Fred Gao)

----------------------------------------------------------------
Alex Williamson (1):
      vfio/pci: Implement ioeventfd thread handler for contended memory lock

Dan Carpenter (2):
      vfio/fsl-mc: return -EFAULT if copy_to_user() fails
      vfio/fsl-mc: prevent underflow in vfio_fsl_mc_mmap()

Diana Craciun (1):
      vfio/fsl-mc: Make vfio_fsl_mc_irqs_allocate static

Fred Gao (1):
      vfio/pci: Bypass IGD init in case of -ENODEV

Zenghui Yu (1):
      vfio/type1: Use the new helper to find vfio_group

Zhang Qilong (1):
      vfio: platform: fix reference leak in vfio_platform_open

 drivers/vfio/fsl-mc/vfio_fsl_mc.c            | 10 +++++--
 drivers/vfio/fsl-mc/vfio_fsl_mc_intr.c       |  2 +-
 drivers/vfio/pci/vfio_pci.c                  |  2 +-
 drivers/vfio/pci/vfio_pci_rdwr.c             | 43 ++++++++++++++++++++++------
 drivers/vfio/platform/vfio_platform_common.c |  3 +-
 drivers/vfio/vfio_iommu_type1.c              | 17 ++++-------
 6 files changed, 50 insertions(+), 27 deletions(-)
```
#### [RFC v3 1/7] KVM: VMX: Introduce PKS VMCS fields
##### From: Chenyi Qiang <chenyi.qiang@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Chenyi Qiang <chenyi.qiang@intel.com>
X-Patchwork-Id: 11883495
Return-Path: <SRS0=FTeU=EL=vger.kernel.org=kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-12.7 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_PATCH,MAILING_LIST_MULTI,SIGNED_OFF_BY,
	SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED,USER_AGENT_GIT autolearn=ham
	autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 940F1C4741F
	for <kvm@archiver.kernel.org>; Thu,  5 Nov 2020 08:15:47 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 3DB3B2168B
	for <kvm@archiver.kernel.org>; Thu,  5 Nov 2020 08:15:47 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729149AbgKEIPp (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Thu, 5 Nov 2020 03:15:45 -0500
Received: from mga04.intel.com ([192.55.52.120]:39805 "EHLO mga04.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1728784AbgKEIPp (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 5 Nov 2020 03:15:45 -0500
IronPort-SDR: 
 WzA2t1kToCn8EXjdOHDt6hQ87BfiIt5F14LSh3aIi4UOGofmgKorGe51/bTWIPYruVnCeH1zfC
 AM4hEzJsfnsQ==
X-IronPort-AV: E=McAfee;i="6000,8403,9795"; a="166755700"
X-IronPort-AV: E=Sophos;i="5.77,453,1596524400";
   d="scan'208";a="166755700"
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from orsmga005.jf.intel.com ([10.7.209.41])
  by fmsmga104.fm.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 05 Nov 2020 00:15:45 -0800
IronPort-SDR: 
 a+7VMwBg5/Hi4lYCK0z2W3WX6ayClmPWKsJbYmX4nwDlifarKeJ95H4kTt+dLsBgOajtyeITn4
 j6At3+Z/ivMw==
X-IronPort-AV: E=Sophos;i="5.77,453,1596524400";
   d="scan'208";a="539281387"
Received: from chenyi-pc.sh.intel.com ([10.239.159.72])
  by orsmga005-auth.jf.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 05 Nov 2020 00:15:42 -0800
From: Chenyi Qiang <chenyi.qiang@intel.com>
To: Paolo Bonzini <pbonzini@redhat.com>,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>,
        Xiaoyao Li <xiaoyao.li@intel.com>
Cc: kvm@vger.kernel.org, linux-kernel@vger.kernel.org
Subject: [RFC v3 1/7] KVM: VMX: Introduce PKS VMCS fields
Date: Thu,  5 Nov 2020 16:17:58 +0800
Message-Id: <20201105081805.5674-2-chenyi.qiang@intel.com>
X-Mailer: git-send-email 2.17.1
In-Reply-To: <20201105081805.5674-1-chenyi.qiang@intel.com>
References: <20201105081805.5674-1-chenyi.qiang@intel.com>
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

PKS(Protection Keys for Supervisor Pages) is a feature that extends the
Protection Key architecture to support thread-specific permission
restrictions on supervisor pages.

A new PKS MSR(PKRS) is defined in kernel to support PKS, which holds a
set of permissions associated with each protection domian.

Two VMCS fields {HOST,GUEST}_IA32_PKRS are introduced in
{host,guest}-state area to store the value of PKRS.

Every VM exit saves PKRS into guest-state area.
If VM_EXIT_LOAD_IA32_PKRS = 1, VM exit loads PKRS from the host-state
area.
If VM_ENTRY_LOAD_IA32_PKRS = 1, VM entry loads PKRS from the guest-state
area.

Signed-off-by: Chenyi Qiang <chenyi.qiang@intel.com>
Reviewed-by: Jim Mattson <jmattson@google.com>
---
 arch/x86/include/asm/vmx.h | 6 ++++++
 1 file changed, 6 insertions(+)

```
#### [PATCH] KVM: PPC: Book3S HV: XIVE: Fix possible oops when accessing ESB page
##### From: =?utf-8?q?C=C3=A9dric_Le_Goater?= <clg@kaod.org>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 8bit
X-Patchwork-Submitter: =?utf-8?q?C=C3=A9dric_Le_Goater?= <clg@kaod.org>
X-Patchwork-Id: 11884429
Return-Path: <SRS0=FTeU=EL=vger.kernel.org=kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-12.8 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_PATCH,MAILING_LIST_MULTI,SIGNED_OFF_BY,
	SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT autolearn=ham autolearn_force=no
	version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 24939C4741F
	for <kvm@archiver.kernel.org>; Thu,  5 Nov 2020 13:48:18 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id AA332206B6
	for <kvm@archiver.kernel.org>; Thu,  5 Nov 2020 13:48:17 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727275AbgKENsR convert rfc822-to-8bit (ORCPT
        <rfc822;kvm@archiver.kernel.org>); Thu, 5 Nov 2020 08:48:17 -0500
Received: from mx0a-001b2d01.pphosted.com ([148.163.156.1]:60550 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1725468AbgKENsQ (ORCPT
        <rfc822;kvm@vger.kernel.org>); Thu, 5 Nov 2020 08:48:16 -0500
Received: from pps.filterd (m0098404.ppops.net [127.0.0.1])
        by mx0a-001b2d01.pphosted.com (8.16.0.42/8.16.0.42) with SMTP id
 0A5DljqF176172;
        Thu, 5 Nov 2020 08:47:53 -0500
Received: from ppma04fra.de.ibm.com (6a.4a.5195.ip4.static.sl-reverse.com
 [149.81.74.106])
        by mx0a-001b2d01.pphosted.com with ESMTP id 34m5ftekvw-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Thu, 05 Nov 2020 08:47:52 -0500
Received: from pps.filterd (ppma04fra.de.ibm.com [127.0.0.1])
        by ppma04fra.de.ibm.com (8.16.0.42/8.16.0.42) with SMTP id
 0A5DiBvH006410;
        Thu, 5 Nov 2020 13:47:26 GMT
Received: from b06cxnps4074.portsmouth.uk.ibm.com
 (d06relay11.portsmouth.uk.ibm.com [9.149.109.196])
        by ppma04fra.de.ibm.com with ESMTP id 34h0f6tt1m-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Thu, 05 Nov 2020 13:47:26 +0000
Received: from b06wcsmtp001.portsmouth.uk.ibm.com
 (b06wcsmtp001.portsmouth.uk.ibm.com [9.149.105.160])
        by b06cxnps4074.portsmouth.uk.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id 0A5DlNMp64487700
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Thu, 5 Nov 2020 13:47:23 GMT
Received: from b06wcsmtp001.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id CDF76A4054;
        Thu,  5 Nov 2020 13:47:23 +0000 (GMT)
Received: from b06wcsmtp001.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 7CFFBA405B;
        Thu,  5 Nov 2020 13:47:23 +0000 (GMT)
Received: from smtp.tlslab.ibm.com (unknown [9.101.4.1])
        by b06wcsmtp001.portsmouth.uk.ibm.com (Postfix) with SMTP;
        Thu,  5 Nov 2020 13:47:23 +0000 (GMT)
Received: from yukon.ibmuc.com (sig-9-145-56-119.uk.ibm.com [9.145.56.119])
        by smtp.tlslab.ibm.com (Postfix) with ESMTP id 3776422006B;
        Thu,  5 Nov 2020 14:47:22 +0100 (CET)
From: =?utf-8?q?C=C3=A9dric_Le_Goater?= <clg@kaod.org>
To: Paul Mackerras <paulus@samba.org>
Cc: linuxppc-dev@lists.ozlabs.org, Michael Ellerman <mpe@ellerman.id.au>,
 kvm-ppc@vger.kernel.org, kvm@vger.kernel.org, Greg Kurz <groug@kaod.org>,
 Gustavo Romero <gromero@linux.ibm.com>,
 David Gibson <david@gibson.dropbear.id.au>,
 =?utf-8?q?C=C3=A9dric_Le_Goater?= <clg@kaod.org>
Subject: [PATCH] KVM: PPC: Book3S HV: XIVE: Fix possible oops when accessing
 ESB page
Date: Thu,  5 Nov 2020 14:47:13 +0100
Message-Id: <20201105134713.656160-1-clg@kaod.org>
X-Mailer: git-send-email 2.26.2
MIME-Version: 1.0
X-TM-AS-GCONF: 00
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.312,18.0.737
 definitions=2020-11-05_07:2020-11-05,2020-11-05 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 malwarescore=0 spamscore=0
 mlxscore=0 phishscore=0 suspectscore=0 clxscore=1034 bulkscore=0
 priorityscore=1501 mlxlogscore=648 adultscore=0 impostorscore=0
 lowpriorityscore=0 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.12.0-2009150000 definitions=main-2011050088
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

When accessing the ESB page of a source interrupt, the fault handler
will retrieve the page address from the XIVE interrupt 'xive_irq_data'
structure. If the associated KVM XIVE interrupt is not valid, that is
not allocated at the HW level for some reason, the fault handler will
dereference a NULL pointer leading to the oops below :

    WARNING: CPU: 40 PID: 59101 at arch/powerpc/kvm/book3s_xive_native.c:259 xive_native_esb_fault+0xe4/0x240 [kvm]
    CPU: 40 PID: 59101 Comm: qemu-system-ppc Kdump: loaded Tainted: G        W        --------- -  - 4.18.0-240.el8.ppc64le #1
    NIP:  c00800000e949fac LR: c00000000044b164 CTR: c00800000e949ec8
    REGS: c000001f69617840 TRAP: 0700   Tainted: G        W        --------- -  -  (4.18.0-240.el8.ppc64le)
    MSR:  9000000000029033 <SF,HV,EE,ME,IR,DR,RI,LE>  CR: 44044282  XER: 00000000
    CFAR: c00000000044b160 IRQMASK: 0
    GPR00: c00000000044b164 c000001f69617ac0 c00800000e96e000 c000001f69617c10
    GPR04: 05faa2b21e000080 0000000000000000 0000000000000005 ffffffffffffffff
    GPR08: 0000000000000000 0000000000000001 0000000000000000 0000000000000001
    GPR12: c00800000e949ec8 c000001ffffd3400 0000000000000000 0000000000000000
    GPR16: 0000000000000000 0000000000000000 0000000000000000 0000000000000000
    GPR20: 0000000000000000 0000000000000000 c000001f5c065160 c000000001c76f90
    GPR24: c000001f06f20000 c000001f5c065100 0000000000000008 c000001f0eb98c78
    GPR28: c000001dcab40000 c000001dcab403d8 c000001f69617c10 0000000000000011
    NIP [c00800000e949fac] xive_native_esb_fault+0xe4/0x240 [kvm]
    LR [c00000000044b164] __do_fault+0x64/0x220
    Call Trace:
    [c000001f69617ac0] [0000000137a5dc20] 0x137a5dc20 (unreliable)
    [c000001f69617b50] [c00000000044b164] __do_fault+0x64/0x220
    [c000001f69617b90] [c000000000453838] do_fault+0x218/0x930
    [c000001f69617bf0] [c000000000456f50] __handle_mm_fault+0x350/0xdf0
    [c000001f69617cd0] [c000000000457b1c] handle_mm_fault+0x12c/0x310
    [c000001f69617d10] [c00000000007ef44] __do_page_fault+0x264/0xbb0
    [c000001f69617df0] [c00000000007f8c8] do_page_fault+0x38/0xd0
    [c000001f69617e30] [c00000000000a714] handle_page_fault+0x18/0x38
    Instruction dump:
    40c2fff0 7c2004ac 2fa90000 409e0118 73e90001 41820080 e8bd0008 7c2004ac
    7ca90074 39400000 915c0000 7929d182 <0b090000> 2fa50000 419e0080 e89e0018
    ---[ end trace 66c6ff034c53f64f ]---
    xive-kvm: xive_native_esb_fault: accessing invalid ESB page for source 8 !

Fix that by checking the validity of the KVM XIVE interrupt structure.

Reported-by: Greg Kurz <groug@kaod.org>
Signed-off-by: Cédric Le Goater <clg@kaod.org>
Tested-by: Greg Kurz <groug@kaod.org>
---
 arch/powerpc/kvm/book3s_xive_native.c | 7 +++++++
 1 file changed, 7 insertions(+)

```
#### [PATCH] KVM: selftests: Test IPI to halted vCPU in xAPIC while backing page moves
##### From: Peter Shier <pshier@google.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Peter Shier <pshier@google.com>
X-Patchwork-Id: 11885413
Return-Path: <SRS0=FTeU=EL=vger.kernel.org=kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-20.4 required=3.0 tests=BAYES_00,DKIMWL_WL_MED,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_PATCH,MAILING_LIST_MULTI,SIGNED_OFF_BY,SPF_HELO_NONE,SPF_PASS,
	USER_AGENT_GIT,USER_IN_DEF_DKIM_WL autolearn=ham autolearn_force=no
	version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 47192C388F7
	for <kvm@archiver.kernel.org>; Thu,  5 Nov 2020 22:38:33 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id C2E7E2078E
	for <kvm@archiver.kernel.org>; Thu,  5 Nov 2020 22:38:32 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=google.com header.i=@google.com
 header.b="N76gIeYg"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1732250AbgKEWib (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Thu, 5 Nov 2020 17:38:31 -0500
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:36520 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1732035AbgKEWib (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 5 Nov 2020 17:38:31 -0500
Received: from mail-pf1-x44a.google.com (mail-pf1-x44a.google.com
 [IPv6:2607:f8b0:4864:20::44a])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 72945C0613CF
        for <kvm@vger.kernel.org>; Thu,  5 Nov 2020 14:38:31 -0800 (PST)
Received: by mail-pf1-x44a.google.com with SMTP id t10so2413448pfh.19
        for <kvm@vger.kernel.org>; Thu, 05 Nov 2020 14:38:31 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=sender:date:message-id:mime-version:subject:from:to:cc;
        bh=U8vK9QwD3Ttl2tmRLvzoELiGV+TYBcdGNosbACJ1xgA=;
        b=N76gIeYgwIEE/qGX/4iFlhYnvZmoYDmvfhegBwJJC+TJcuaZ1UK8hjsmI4ctLXxu1h
         +abyKqc7m/hDJcddSS7rjgqsC69WAPOEYsWBNQTG0kXSRnQJffm28qFeJ/TnBZqmmrTZ
         lVD6Ipag1kqvcKBhIcAQqKyYX7fkWnhIEsI9u9016oZxdzG3/crdS3ij4CK3oJbEVNrP
         p0F/HxiwDoyDZLf0lj2AU9gCo/qXRkWdrGp/hML45BLX7QkuF7WEsdLYH62TxP4Rgs9U
         wtw76yFPhkHhho0zpX+6TwOrl8PV94Emod6mMxYq6ZXfPM+tSmMcSbnYQQzECOXBcojp
         ylBg==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:sender:date:message-id:mime-version:subject:from
         :to:cc;
        bh=U8vK9QwD3Ttl2tmRLvzoELiGV+TYBcdGNosbACJ1xgA=;
        b=VmDtNQ6r6CopLopKEl2A3aj2/1aeQfTMxrh2zoFbWM0C1ZyRgWfKp3W6WsQ8aH2CX0
         oUEHZ5RiMdYk50w70asViNkCheX3X2d0aGjL4GZHES6vJnwrOJ1aNasTxJnwDuylWzwh
         HYRs2lXJ9lTMtXZDuJXqav+TgZVWl8W/2GpH6ewctuhJ7297lOixcTbEIIWYVsy7cC77
         uXop0vtRa3O3DhBIVfXohCThTxry3BjZLPApJa8c5NFYyjt2jwJwXg81p+ITWPIKpx2p
         a7GWVzD11i87NBGtdl9GXvXtbhAgAN3hS2dr35r25yiyPXQiqLUHP8P867W8o0G+f9ZZ
         tbEA==
X-Gm-Message-State: AOAM530ISTgsr6+Ub+Mu2n+W1XDaUM27HUd3CxVvZEEjhwz7loekiRMC
        dwHsmYs5BaTtlPVzkF/HrrqkeW5xaYIOqHHgvDsdePP0YlE7490tWJHl24xZsmuBpwXAcsmLq/T
        IJfv6G/blLRfT3ApcSemE8XQhhHRdNCg0mcFm16N9xCZFGDZiF8QbC4qYOw==
X-Google-Smtp-Source: 
 ABdhPJzXzevLebD+PpO4cI5hp7/vpEFFbXMn8TllH3A+inRPhW1Iq1ImPN7xWa10iEItQ6XiKcTObMlJ1ZE=
Sender: "pshier via sendgmr"
        <pshier@pshier-linuxworkstation.sea.corp.google.com>
X-Received: from pshier-linuxworkstation.sea.corp.google.com
 ([2620:15c:100:202:a28c:fdff:fee1:c360]) (user=pshier job=sendgmr) by
 2002:a17:90a:b63:: with SMTP id 90mr4760925pjq.154.1604615910926; Thu, 05 Nov
 2020 14:38:30 -0800 (PST)
Date: Thu,  5 Nov 2020 14:38:23 -0800
Message-Id: <20201105223823.850068-1-pshier@google.com>
Mime-Version: 1.0
X-Mailer: git-send-email 2.29.1.341.ge80a0c044ae-goog
Subject: [PATCH] KVM: selftests: Test IPI to halted vCPU in xAPIC while
 backing page moves
From: Peter Shier <pshier@google.com>
To: kvm@vger.kernel.org
Cc: pbonzini@redhat.com, drjones@redhat.com,
        Peter Shier <pshier@google.com>,
        Jim Mattson <jmattson@google.com>,
        Ricardo Koller <ricarkol@google.com>
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

When a guest is using xAPIC KVM allocates a backing page for the required
EPT entry for the APIC access address set in the VMCS. If mm decides to
move that page the KVM mmu notifier will update the VMCS with the new
HPA. This test induces a page move to test that APIC access continues to
work correctly. It is a directed test for
commit e649b3f0188f "KVM: x86: Fix APIC page invalidation race".

Tested: ran for 1 hour on a skylake, migrating backing page every 1ms

Depends on patch "selftests: kvm: Add exception handling to selftests"
from aaronlewis@google.com that has not yet been queued.

Signed-off-by: Peter Shier <pshier@google.com>
Reviewed-by: Jim Mattson <jmattson@google.com>
Reviewed-by: Ricardo Koller <ricarkol@google.com>
---
 tools/testing/selftests/kvm/.gitignore        |   1 +
 tools/testing/selftests/kvm/Makefile          |   1 +
 tools/testing/selftests/kvm/include/numaif.h  |  55 ++
 .../selftests/kvm/include/x86_64/processor.h  |  20 +
 .../selftests/kvm/x86_64/xapic_ipi_test.c     | 544 ++++++++++++++++++
 5 files changed, 621 insertions(+)
 create mode 100644 tools/testing/selftests/kvm/include/numaif.h
 create mode 100644 tools/testing/selftests/kvm/x86_64/xapic_ipi_test.c

--

```
#### [kvm-unit-tests PATCH] arm: Fix compilation errors
##### From: Alexandru Elisei <alexandru.elisei@arm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Alexandru Elisei <alexandru.elisei@arm.com>
X-Patchwork-Id: 11884471
Return-Path: <SRS0=FTeU=EL=vger.kernel.org=kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-12.7 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_PATCH,MAILING_LIST_MULTI,SIGNED_OFF_BY,
	SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED,USER_AGENT_GIT autolearn=ham
	autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 97CE3C4741F
	for <kvm@archiver.kernel.org>; Thu,  5 Nov 2020 13:58:31 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 502E221D81
	for <kvm@archiver.kernel.org>; Thu,  5 Nov 2020 13:58:31 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1730465AbgKEN6a (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Thu, 5 Nov 2020 08:58:30 -0500
Received: from foss.arm.com ([217.140.110.172]:33196 "EHLO foss.arm.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1727275AbgKEN63 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 5 Nov 2020 08:58:29 -0500
Received: from usa-sjc-imap-foss1.foss.arm.com (unknown [10.121.207.14])
        by usa-sjc-mx-foss1.foss.arm.com (Postfix) with ESMTP id 4025A14BF;
        Thu,  5 Nov 2020 05:58:28 -0800 (PST)
Received: from monolith.localdoman (unknown [172.31.20.19])
        by usa-sjc-imap-foss1.foss.arm.com (Postfix) with ESMTPSA id
 2E0C13F719;
        Thu,  5 Nov 2020 05:58:27 -0800 (PST)
From: Alexandru Elisei <alexandru.elisei@arm.com>
To: kvm@vger.kernel.org, kvmarm@lists.cs.columbia.edu
Cc: drjones@redhat.com, pbonzini@redhat.com,
        Eric Auger <eric.auger@redhat.com>,
        Alexander Graf <graf@amazon.com>,
        Andre Przywara <andre.przywara@arm.com>
Subject: [kvm-unit-tests PATCH] arm: Fix compilation errors
Date: Thu,  5 Nov 2020 13:59:36 +0000
Message-Id: <20201105135936.55088-1-alexandru.elisei@arm.com>
X-Mailer: git-send-email 2.29.2
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Using arm-none-eabi-gcc triggers the following compilation errors:

$ ./configure --arch=arm --cross-prefix=arm-none-eabi-
$ make clean
$ make -j8
[..]
arm/pmu.c: In function 'pmu_probe':
arm/pmu.c:1000:47: error: format '%c' expects argument of type 'int', but argument 3 has type 'long unsigned int' [-Werror=format=]
 1000 |  report_info("PMU implementer/ID code: %#x(\"%c\")/%#x",
      |                                              ~^
      |                                               |
      |                                               int
      |                                              %ld
 1001 |       (pmcr >> PMU_PMCR_IMP_SHIFT) & PMU_PMCR_IMP_MASK,
 1002 |       ((pmcr >> PMU_PMCR_IMP_SHIFT) & PMU_PMCR_IMP_MASK) ? : ' ',
      |       ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
      |                                                            |
      |                                                            long unsigned int
[..]
arm/gic.c: In function 'test_byte_access':
arm/gic.c:460:31: error: format '%x' expects argument of type 'unsigned int', but argument 2 has type 'u32' {aka 'long unsigned int'} [-Werror=format=]
  460 |   report_info("byte 1 of 0x%08x => 0x%02x", pattern & mask, reg);
      |                            ~~~^             ~~~~~~~~~~~~~~
      |                               |                     |
      |                               unsigned int          u32 {aka long unsigned int}
      |                            %08lx
[..]
arm/pl031.c: In function 'irq_handler':
arm/pl031.c:153:39: error: format '%d' expects argument of type 'int', but argument 2 has type 'u32' {aka 'long unsigned int'} [-Werror=format=]
  153 |   report_info("Unexpected interrupt: %d\n", irqnr);
      |                                      ~^     ~~~~~
      |                                       |     |
      |                                       int   u32 {aka long unsigned int}
      |                                      %ld

The errors were observed when using arm-none-eabi-gcc versions 10.2.0 and
9.2.0. No errors were found when using arm-linux-gnu-gcc version 10.2.1.

Replace the offending printf format specifiers with their PRIxxx
counterparts defined by C99 and available in libcflat.h. Also remove the
unnecessary call to get_pmcr() in pmu_probe(), as the pmcr value hasn't
changed since initialization.

Nu functional changes intended by this patch.

CC: Eric Auger <eric.auger@redhat.com>
CC: Alexander Graf <graf@amazon.com>
CC: Andre Przywara <andre.przywara@arm.com>
CC: Andrew Jones <drjones@redhat.com>
Signed-off-by: Alexandru Elisei <alexandru.elisei@arm.com>
---

Andre suggested that we drop using gcc's stdint.h and implement our own to avoid
such errors in the future. The distro that I'm using on my desktop doesn't have
the arm-linux-gnu toolchain in the default repos, so I figured I should send
this fix to get things compiling again.

I have no preference for, or against, implementing our own types.h header file.
I imagine it's not going to be easy to change the code to use it (possibly for
all architectures), and it should be worth it in the long run.

 arm/gic.c   | 14 +++++++-------
 arm/pl031.c | 10 +++++-----
 arm/pmu.c   |  7 ++++---
 3 files changed, 16 insertions(+), 15 deletions(-)

```
#### [kvm-unit-tests PATCH] x86: Add tests for PKS
##### From: Chenyi Qiang <chenyi.qiang@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Chenyi Qiang <chenyi.qiang@intel.com>
X-Patchwork-Id: 11883489
Return-Path: <SRS0=FTeU=EL=vger.kernel.org=kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-12.7 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_PATCH,MAILING_LIST_MULTI,SIGNED_OFF_BY,
	SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED,USER_AGENT_GIT autolearn=ham
	autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 86BBCC4741F
	for <kvm@archiver.kernel.org>; Thu,  5 Nov 2020 08:16:11 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 3B07821D7F
	for <kvm@archiver.kernel.org>; Thu,  5 Nov 2020 08:16:11 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1730666AbgKEIQH (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Thu, 5 Nov 2020 03:16:07 -0500
Received: from mga04.intel.com ([192.55.52.120]:39805 "EHLO mga04.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1730543AbgKEIQE (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 5 Nov 2020 03:16:04 -0500
IronPort-SDR: 
 mCkOL5x7k9jhsJRPvZBcBepVBT9xJXq0xCQt2y+IISg2IcPgOmtmOpBt+jSdC6W6HKRDfLbkkM
 Q4+e0/8FnnOw==
X-IronPort-AV: E=McAfee;i="6000,8403,9795"; a="166755749"
X-IronPort-AV: E=Sophos;i="5.77,453,1596524400";
   d="scan'208";a="166755749"
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from orsmga005.jf.intel.com ([10.7.209.41])
  by fmsmga104.fm.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 05 Nov 2020 00:16:03 -0800
IronPort-SDR: 
 05IwEy/VozTgYE7NroiL4avmOZ0AmLLlBB1AfnxpHEKV7Rbl5N5VPmInirU4uezqeSZc9PQEtf
 6RkImQi8SCog==
X-IronPort-AV: E=Sophos;i="5.77,453,1596524400";
   d="scan'208";a="539281547"
Received: from chenyi-pc.sh.intel.com ([10.239.159.72])
  by orsmga005-auth.jf.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 05 Nov 2020 00:16:01 -0800
From: Chenyi Qiang <chenyi.qiang@intel.com>
To: Paolo Bonzini <pbonzini@redhat.com>,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>,
        Xiaoyao Li <xiaoyao.li@intel.com>
Cc: kvm@vger.kernel.org, linux-kernel@vger.kernel.org
Subject: [kvm-unit-tests PATCH] x86: Add tests for PKS
Date: Thu,  5 Nov 2020 16:18:05 +0800
Message-Id: <20201105081805.5674-9-chenyi.qiang@intel.com>
X-Mailer: git-send-email 2.17.1
In-Reply-To: <20201105081805.5674-1-chenyi.qiang@intel.com>
References: <20201105081805.5674-1-chenyi.qiang@intel.com>
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This unit-test is intended to test the KVM support for Protection Keys
for Supervisor Pages (PKS). If CR4.PKS is set in long mode, supervisor
pkeys are checked in addition to normal paging protections and Access or
Write can be disabled via a MSR update without TLB flushes when
permissions change.

Signed-off-by: Chenyi Qiang <chenyi.qiang@intel.com>
---
 lib/x86/msr.h       |   1 +
 lib/x86/processor.h |   2 +
 x86/Makefile.x86_64 |   1 +
 x86/pks.c           | 146 ++++++++++++++++++++++++++++++++++++++++++++
 x86/unittests.cfg   |   5 ++
 5 files changed, 155 insertions(+)
 create mode 100644 x86/pks.c

```
#### [PATCH 1/2] KVM: x86: fix apic_accept_events vs check_nested_events
##### From: Paolo Bonzini <pbonzini@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Paolo Bonzini <pbonzini@redhat.com>
X-Patchwork-Id: 11884737
Return-Path: <SRS0=FTeU=EL=vger.kernel.org=kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-9.9 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_PATCH,MAILING_LIST_MULTI,SIGNED_OFF_BY,SPF_HELO_NONE,SPF_PASS
	autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id D7A9FC55179
	for <kvm@archiver.kernel.org>; Thu,  5 Nov 2020 17:15:39 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 7BDFA22201
	for <kvm@archiver.kernel.org>; Thu,  5 Nov 2020 17:15:39 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="XY6ig+zG"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1731722AbgKERPb (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Thu, 5 Nov 2020 12:15:31 -0500
Received: from us-smtp-delivery-124.mimecast.com ([216.205.24.124]:50732 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1731203AbgKERPb (ORCPT
        <rfc822;kvm@vger.kernel.org>); Thu, 5 Nov 2020 12:15:31 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1604596529;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding:
         in-reply-to:in-reply-to:references:references;
        bh=XlrP5n7QxEFVD/JR9/hAdOLwk4W0dChMzmUp+37EWd8=;
        b=XY6ig+zGHdv57GMO62N3dmYuKO2EZ+Vfb0PQMKMNIryMlbA8mXo4gCiIewKjudMueQLe0P
        gzY6FdUwXBo0oH6NqnrRPnRGEppM38Fa/BW8Qts1c/r17o67QkkSdKP5h2sW1P5US6Cclu
        kVqpVKJHq+OcXT92sud4azpyXS0QETY=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-197-GhFDIG70Ojqr3Dcriv9n6w-1; Thu, 05 Nov 2020 12:15:26 -0500
X-MC-Unique: GhFDIG70Ojqr3Dcriv9n6w-1
Received: from smtp.corp.redhat.com (int-mx02.intmail.prod.int.phx2.redhat.com
 [10.5.11.12])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id C4A821891E84;
        Thu,  5 Nov 2020 17:15:25 +0000 (UTC)
Received: from virtlab701.virt.lab.eng.bos.redhat.com
 (virtlab701.virt.lab.eng.bos.redhat.com [10.19.152.228])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 757296CE4F;
        Thu,  5 Nov 2020 17:15:25 +0000 (UTC)
From: Paolo Bonzini <pbonzini@redhat.com>
To: linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Cc: yadong.qi@intel.com
Subject: [PATCH 1/2] KVM: x86: fix apic_accept_events vs check_nested_events
Date: Thu,  5 Nov 2020 12:15:23 -0500
Message-Id: <20201105171524.650693-2-pbonzini@redhat.com>
In-Reply-To: <20201105171524.650693-1-pbonzini@redhat.com>
References: <20201105171524.650693-1-pbonzini@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.12
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

vmx_apic_init_signal_blocked is buggy in that it returns true
even in VMX non-root mode.  In non-root mode, however, INITs
are not latched, they just cause a vmexit.  Previously,
KVM was waiting for them to be processed when kvm_apic_accept_events
and in the meanwhile it ate the SIPIs that the processor received.

However, in order to implement the wait-for-SIPI activity state,
KVM will have to process KVM_APIC_SIPI in vmx_check_nested_events,
and it will not be possible anymore to disregard SIPIs in non-root
mode as the code is currently doing.

By calling kvm_x86_ops.nested_ops->check_events, we can force a vmexit
(with the side-effect of latching INITs) before incorrectly injecting
an INIT or SIPI in a guest, and therefore vmx_apic_init_signal_blocked
can do the right thing.

Signed-off-by: Paolo Bonzini <pbonzini@redhat.com>
---
 arch/x86/kvm/lapic.c   | 30 ++++++++++++++++++++++++++----
 arch/x86/kvm/vmx/vmx.c |  2 +-
 2 files changed, 27 insertions(+), 5 deletions(-)

```
#### [PATCH] KVM: x86: handle MSR_IA32_DEBUGCTLMSR with report_ignored_msrs
##### From: Pankaj Gupta <pankaj.gupta.linux@gmail.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Pankaj Gupta <pankaj.gupta.linux@gmail.com>
X-Patchwork-Id: 11884649
Return-Path: <SRS0=FTeU=EL=vger.kernel.org=kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-12.6 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,DKIM_VALID_AU,FREEMAIL_FORGED_FROMDOMAIN,FREEMAIL_FROM,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_PATCH,MAILING_LIST_MULTI,SIGNED_OFF_BY,
	SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT autolearn=ham autolearn_force=no
	version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 9F27DC4741F
	for <kvm@archiver.kernel.org>; Thu,  5 Nov 2020 15:40:03 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 2D52A20782
	for <kvm@archiver.kernel.org>; Thu,  5 Nov 2020 15:40:03 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=gmail.com header.i=@gmail.com
 header.b="pjFQ8QiK"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1731085AbgKEPkA (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Thu, 5 Nov 2020 10:40:00 -0500
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:55542 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1730721AbgKEPkA (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 5 Nov 2020 10:40:00 -0500
Received: from mail-ej1-x644.google.com (mail-ej1-x644.google.com
 [IPv6:2a00:1450:4864:20::644])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 34E28C0613CF
        for <kvm@vger.kernel.org>; Thu,  5 Nov 2020 07:40:00 -0800 (PST)
Received: by mail-ej1-x644.google.com with SMTP id o23so2283955ejn.11
        for <kvm@vger.kernel.org>; Thu, 05 Nov 2020 07:40:00 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=from:to:cc:subject:date:message-id:mime-version
         :content-transfer-encoding;
        bh=hKzXJuXdj/IoLTP+CpsVrEpWzHcfkNGl+YuHY/1Jvy8=;
        b=pjFQ8QiKJOgrwd2cGiIgLgb7mKVC4OxzunOl0Td8civHy1WMCLaDKZgcArKbUIgyEq
         2blMgWhVzGurwP4KsFwvigsa3q4P5wiM38UvIYBvDP6qs8l2mL47CO8lU3kyKNpDAusP
         4s3/MDTC9QUSUXgH25awNDYmqphXZIgNY+jjn8ns04KWR9ny25hEufvSV2coP7/Z5ARS
         zHwsYtODerieUgbuLuyAlKQoq4JnGIogMVKP99k0GM7BtOVfrLSdi1uT1ZuOHSGLDt0E
         Sxbf5VDlxNSFiT/FWr282NvSn8uToFhlnDqoC1CbZGa+ia8EgiC9nxeITNVCTK4aALAQ
         22YA==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:mime-version
         :content-transfer-encoding;
        bh=hKzXJuXdj/IoLTP+CpsVrEpWzHcfkNGl+YuHY/1Jvy8=;
        b=PYdJ9muhmYgeLAkQ0jPL/CLeOmiFgz8IWTHXwRwo1SbUZeahch/t7alod9hC4STZPj
         6hpITqykJL7BMOZCAkrDOyyo8MTJbtUFTmfRE507broeyX5uhA6yGrj/Vqeyc2V1/pkw
         ojzYw+fs+i4q/V9ETy5GijyHnU4zZ66oGsetWfH+srQa5qjaXJOim3ng/jZY1yvvPXxP
         F3bq+rbCcOzoyfg1evrl1fr/nSyNdUPuYLwnUFRfg8a5lxLfy559f6MN7GOg/XklzVgy
         AV8l9w2jR8gsJPC0E2csvzoRTkF9EmV8K7Q8b9+AbyYv4evUfuWzBOOtqF4Gg5nupJdO
         gS8A==
X-Gm-Message-State: AOAM530c7jwMWBGj5ro5rKagq/5K001eUGjO5u/EUUFzoxxi641cA7nh
        Cf7JJ8i3vYGGctsMDtn0pHwXVnLJZZk=
X-Google-Smtp-Source: 
 ABdhPJzyYoNJCSijbfTrV9Ypx3/c3I2yCSGAIGH0RUSZRyXg5DUh6CAuqE22gsP2e/abE+4p9DsVtA==
X-Received: by 2002:a17:906:7698:: with SMTP id
 o24mr2780041ejm.447.1604590798680;
        Thu, 05 Nov 2020 07:39:58 -0800 (PST)
Received: from lb01399.pb.local
 (p200300ca5719ac40c98ae5b6a31510db.dip0.t-ipconnect.de.
 [2003:ca:5719:ac40:c98a:e5b6:a315:10db])
        by smtp.gmail.com with ESMTPSA id
 b8sm1106481edv.20.2020.11.05.07.39.57
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Thu, 05 Nov 2020 07:39:58 -0800 (PST)
From: Pankaj Gupta <pankaj.gupta.linux@gmail.com>
To: kvm@vger.kernel.org
Cc: pbonzini@redhat.com, sean.j.christopherson@intel.com,
        vkuznets@redhat.com, wanpengli@tencent.com, jmattson@google.com,
        tglx@linutronix.de, oro@8bytes.org, mingo@redhat.com, bp@alien8.de,
        x86@kernel.org, hpa@zytor.com, pankaj.gupta.linux@gmail.com,
        Pankaj Gupta <pankaj.gupta@cloud.ionos.com>
Subject: [PATCH] KVM: x86: handle MSR_IA32_DEBUGCTLMSR with
 report_ignored_msrs
Date: Thu,  5 Nov 2020 16:39:32 +0100
Message-Id: <20201105153932.24316-1-pankaj.gupta.linux@gmail.com>
X-Mailer: git-send-email 2.20.1
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Pankaj Gupta <pankaj.gupta@cloud.ionos.com>

 Guest tries to enable LBR (last branch/interrupt/exception) repeatedly,
 thus spamming the host kernel logs. As MSR_IA32_DEBUGCTLMSR is not emulated by
 KVM, its better to add the error log only with "report_ignored_msrs".
 
Signed-off-by: Pankaj Gupta <pankaj.gupta@cloud.ionos.com>
---
 arch/x86/kvm/x86.c | 6 +++---
 1 file changed, 3 insertions(+), 3 deletions(-)

```
#### [RFC, v0 1/3] vfio/platform: add support for msi
##### From: Vikas Gupta <vikas.gupta@broadcom.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Vikas Gupta <vikas.gupta@broadcom.com>
X-Patchwork-Id: 11883361
Return-Path: <SRS0=FTeU=EL=vger.kernel.org=kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-12.7 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_PATCH,MAILING_LIST_MULTI,MIME_HEADER_CTYPE_ONLY,SIGNED_OFF_BY,
	SPF_HELO_NONE,SPF_PASS,T_TVD_MIME_NO_HEADERS,URIBL_BLOCKED,USER_AGENT_GIT
	autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 16DD8C388F9
	for <kvm@archiver.kernel.org>; Thu,  5 Nov 2020 06:05:47 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 98F6420825
	for <kvm@archiver.kernel.org>; Thu,  5 Nov 2020 06:05:46 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=broadcom.com header.i=@broadcom.com
 header.b="MoEr5yvJ"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729068AbgKEGF1 (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Thu, 5 Nov 2020 01:05:27 -0500
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:50154 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1728918AbgKEGDP (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 5 Nov 2020 01:03:15 -0500
Received: from mail-pg1-x535.google.com (mail-pg1-x535.google.com
 [IPv6:2607:f8b0:4864:20::535])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 19793C0613D1
        for <kvm@vger.kernel.org>; Wed,  4 Nov 2020 22:03:15 -0800 (PST)
Received: by mail-pg1-x535.google.com with SMTP id r186so608361pgr.0
        for <kvm@vger.kernel.org>; Wed, 04 Nov 2020 22:03:15 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=broadcom.com; s=google;
        h=from:to:cc:subject:date:message-id:in-reply-to:references;
        bh=C1hLlBH66SYZWDhetfl5PFNt6oqZFhWMvKxykrruRvs=;
        b=MoEr5yvJJ3QpziuIpXV7ZzzA12PYNVU/dNwOB9lYPAI1i73JsHoG6AYmsItSQYnw4z
         x8/D56D5Spq7v3PZ7rj8nfcP9EO4MXyExDUFiPiglUDQ9Cc+Gs4RGHutg4DDL3kdSJx/
         3bIXvzK6AEweRkaMEfrw3PId9T6zq9ggOlqnI=
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:in-reply-to
         :references;
        bh=C1hLlBH66SYZWDhetfl5PFNt6oqZFhWMvKxykrruRvs=;
        b=t1fHSWqijzmzNexC+BiEd4wq/0vaDcEaQCAYECiBq0/oaPIfb76zXMkZzp4uXDF00d
         Zs0yXguUOyP6zAAccZJo2Ggimn9YL99zKcgxtsRS+0T7vuQG+a/LC6aCSWehJ3y/dWWp
         szWLzWBe//lRwmGGQy4ftmvX6XQo2tzhZl7NsXZ2UauXreD8L/dYht99hAtIMASCf8W7
         EMghbxv6q7y/+XWIvQz0cvoYUMjY0L6ACAiw0+atgd0Pu4lQrO0VQeVip39PCQH1/KIC
         KyBFOsjFGq8ospqP3HfZcwMJICwuxG2P7oKCvGSEXM/JjwP7cVFtIKN/bMk5yvooDmCS
         Cfug==
X-Gm-Message-State: AOAM530V9Rq8YAUuo2HVHr6YzNy5Huy/9KIP21FN8cYHBIFeoRUe43f1
        gXhuApw2oXOIkRsxg9G9gFjLFg==
X-Google-Smtp-Source: 
 ABdhPJw9yqNW9YMgylEd/FZs8uTTT2x7YA1T1e0K1bA1Tc6m/Y4dl73g6THjRSad0LlQ0kzgsssf8A==
X-Received: by 2002:a17:90a:7c43:: with SMTP id
 e3mr901512pjl.124.1604556194431;
        Wed, 04 Nov 2020 22:03:14 -0800 (PST)
Received: from rahul_yocto_ubuntu18.ibn.broadcom.net ([192.19.234.250])
        by smtp.gmail.com with ESMTPSA id
 e201sm834241pfh.73.2020.11.04.22.03.11
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Wed, 04 Nov 2020 22:03:13 -0800 (PST)
From: Vikas Gupta <vikas.gupta@broadcom.com>
To: eric.auger@redhat.com, alex.williamson@redhat.com,
        cohuck@redhat.com, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org
Cc: vikram.prakash@broadcom.com, Vikas Gupta <vikas.gupta@broadcom.com>
Subject: [RFC, v0 1/3] vfio/platform: add support for msi
Date: Thu,  5 Nov 2020 11:32:55 +0530
Message-Id: <20201105060257.35269-2-vikas.gupta@broadcom.com>
X-Mailer: git-send-email 2.17.1
In-Reply-To: <20201105060257.35269-1-vikas.gupta@broadcom.com>
References: <20201105060257.35269-1-vikas.gupta@broadcom.com>
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

MSI support for platform devices.

Signed-off-by: Vikas Gupta <vikas.gupta@broadcom.com>
---
 drivers/vfio/platform/vfio_platform_common.c  |  84 ++++++-
 drivers/vfio/platform/vfio_platform_irq.c     | 235 +++++++++++++++++-
 drivers/vfio/platform/vfio_platform_private.h |  23 ++
 include/uapi/linux/vfio.h                     |   1 +
 4 files changed, 329 insertions(+), 14 deletions(-)

```
#### [PATCH] vfio-pci: Use io_remap_pfn_range() for PCI IO memory
##### From: Jason Gunthorpe <jgg@nvidia.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Jason Gunthorpe <jgg@nvidia.com>
X-Patchwork-Id: 11884711
Return-Path: <SRS0=FTeU=EL=vger.kernel.org=kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-9.8 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_PATCH,MAILING_LIST_MULTI,MSGID_FROM_MTA_HEADER,SIGNED_OFF_BY,
	SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED autolearn=ham autolearn_force=no
	version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 71FAEC5517A
	for <kvm@archiver.kernel.org>; Thu,  5 Nov 2020 16:35:11 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 0587A20715
	for <kvm@archiver.kernel.org>; Thu,  5 Nov 2020 16:35:10 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=nvidia.com header.i=@nvidia.com
 header.b="IjB7z+pV"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1730898AbgKEQfJ (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Thu, 5 Nov 2020 11:35:09 -0500
Received: from nat-hk.nvidia.com ([203.18.50.4]:60132 "EHLO nat-hk.nvidia.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726996AbgKEQfI (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 5 Nov 2020 11:35:08 -0500
Received: from HKMAIL103.nvidia.com (Not Verified[10.18.92.9]) by
 nat-hk.nvidia.com (using TLS: TLSv1.2, AES256-SHA)
        id <B5fa429bb0001>; Fri, 06 Nov 2020 00:35:07 +0800
Received: from HKMAIL103.nvidia.com (10.18.16.12) by HKMAIL103.nvidia.com
 (10.18.16.12) with Microsoft SMTP Server (TLS) id 15.0.1473.3; Thu, 5 Nov
 2020 16:35:04 +0000
Received: from NAM02-CY1-obe.outbound.protection.outlook.com (104.47.37.52) by
 HKMAIL103.nvidia.com (10.18.16.12) with Microsoft SMTP Server (TLS) id
 15.0.1473.3 via Frontend Transport; Thu, 5 Nov 2020 16:35:03 +0000
ARC-Seal: i=1; a=rsa-sha256; s=arcselector9901; d=microsoft.com; cv=none;
 b=bf1kMxXfh2Yy4t35nnp0T1OCvCqz9P+qc1GBpWd7jHbZF9+9Yn7LXYZxbrjcma+SeGxMU1tZUDMQxIYPT+pn4dBBoPrZJJOnelQQGQ3xjna/TnVfaCazT/WL6ZbhQYwKfnmGCmceOlE71GgVEH6vlrMwIJgb0qDdRAq8NJrryzUkgNo57BghvNmrUP7ChYVxv9f+rzsqV0LSjPzYxzStE1i15ivSzjBF4H79QoLxQzcZU3UdJkxDFXpg0Lcrp5nOEsTLFzaOVAN83vfNw8Q3I7msqLdczZk/isMRh6EnaPNr7wrnNviBTalbn2YygBNOQdMGnqr48nlRcRCmWZqOHg==
ARC-Message-Signature: i=1; a=rsa-sha256; c=relaxed/relaxed; d=microsoft.com;
 s=arcselector9901;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=19KNU0NlsVP11D30t0pYvdo1bGwqR8kLRleMcR1iEcQ=;
 b=ByN5RSjYw6ghExhMXsj1u8rrWmwMD3fog6jaTyNJVVFa/RPnFNsJ5sJqpdUm9rXqx/yc92+klKAN5uHwdb8z6Bbq3whjPIjf/6ry02tKtLFjm/1gbk9kUH+QPs0Wo6/01iCMkDqza6bujMt3ZAOf5IdLZ1g25ZI0qlETpIEP0lAuhkijY4cTcfLr0TyQ+9ak8mBpyQqn/Ho2MxjFMOq99xgWMZ7W/siYtD7gaX9RsUh0KI4WC/gCwkXVa3U/S7vX/uApCqnPuxH9XFT4moBX+idwtfujYydu7E1qvZSY8mO/tzHeZ8jSYZ6YGJWY5tfgT134jIPwSj1kV9/zNCgdHg==
ARC-Authentication-Results: i=1; mx.microsoft.com 1; spf=pass
 smtp.mailfrom=nvidia.com; dmarc=pass action=none header.from=nvidia.com;
 dkim=pass header.d=nvidia.com; arc=none
Received: from DM6PR12MB3834.namprd12.prod.outlook.com (2603:10b6:5:14a::12)
 by DM5PR1201MB2488.namprd12.prod.outlook.com (2603:10b6:3:e1::15) with
 Microsoft SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.3499.18; Thu, 5 Nov
 2020 16:35:00 +0000
Received: from DM6PR12MB3834.namprd12.prod.outlook.com
 ([fe80::cdbe:f274:ad65:9a78]) by DM6PR12MB3834.namprd12.prod.outlook.com
 ([fe80::cdbe:f274:ad65:9a78%7]) with mapi id 15.20.3499.032; Thu, 5 Nov 2020
 16:35:00 +0000
From: Jason Gunthorpe <jgg@nvidia.com>
To: Cornelia Huck <cohuck@redhat.com>, <kvm@vger.kernel.org>,
        Tom Lendacky <thomas.lendacky@amd.com>
CC: Alex Williamson <alex.williamson@redhat.com>,
        Peter Xu <peterx@redhat.com>
Subject: [PATCH] vfio-pci: Use io_remap_pfn_range() for PCI IO memory
Date: Thu, 5 Nov 2020 12:34:58 -0400
Message-ID: <0-v1-331b76591255+552-vfio_sme_jgg@nvidia.com>
X-ClientProxiedBy: BL0PR02CA0065.namprd02.prod.outlook.com
 (2603:10b6:207:3d::42) To DM6PR12MB3834.namprd12.prod.outlook.com
 (2603:10b6:5:14a::12)
MIME-Version: 1.0
X-MS-Exchange-MessageSentRepresentingType: 1
Received: from mlx.ziepe.ca (156.34.48.30) by
 BL0PR02CA0065.namprd02.prod.outlook.com (2603:10b6:207:3d::42) with Microsoft
 SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.3541.21 via Frontend
 Transport; Thu, 5 Nov 2020 16:34:59 +0000
Received: from jgg by mlx with local (Exim 4.94)        (envelope-from
 <jgg@nvidia.com>)        id 1kaiDy-0007Jy-HG; Thu, 05 Nov 2020 12:34:58 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=nvidia.com; s=n1;
        t=1604594107; bh=+zGzODOJ2QtI/XplZ/FtWd1GSBYZ5b8sbNAEsPsN/DE=;
        h=ARC-Seal:ARC-Message-Signature:ARC-Authentication-Results:From:To:
         CC:Subject:Date:Message-ID:Content-Transfer-Encoding:Content-Type:
         X-ClientProxiedBy:MIME-Version:
         X-MS-Exchange-MessageSentRepresentingType;
        b=IjB7z+pVH5X4Puv+tF9kLMeXs2fWGCg9+RC2YoApCH88V62QVLbeaZHi/1gm2XOuQ
         QySw6eX1LNqckupwGQLf9xFk9MUx03dcWbMeSd4TmTLof4SVMrA8CN4dNW1U5D+2Pi
         Gv9zCyXWWBbSWZp1Uhipp2Roc57AghHOBtnSsX8MZcBVlSNPK4tgyFVj0x844l9oOj
         JepoJbvpCLsUy+n2dewZgcxTeWqXOrdzOgvSQvDNhEaCuwTwFf08FOXdCTs/xj15D6
         XFCP85Ck4UhCCNnNDul774VOorjvT93w75xhmrrTkSGjURtDdsZc+fEnSjP8VLYh6H
         DqL8/CyoPWMwA==
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

commit f8f6ae5d077a ("mm: always have io_remap_pfn_range() set
pgprot_decrypted()") allows drivers using mmap to put PCI memory mapped
BAR space into userspace to work correctly on AMD SME systems that default
to all memory encrypted.

Since vfio_pci_mmap_fault() is working with PCI memory mapped BAR space it
should be calling io_remap_pfn_range() otherwise it will not work on SME
systems.

Fixes: 11c4cd07ba11 ("vfio-pci: Fault mmaps to enable vma tracking")
Signed-off-by: Jason Gunthorpe <jgg@nvidia.com>
---
 drivers/vfio/pci/vfio_pci.c | 4 ++--
 1 file changed, 2 insertions(+), 2 deletions(-)

The io_remap_pfn_range() commit is in Linus's tree and will be in rc3, but
there is no cross dependency here.

Tom says VFIO device assignment works OK with KVM, so I expect only things
like DPDK to be broken.

Don't have SME hardware, can't test.

```
#### 
##### 

```c
```
#### [PATCH] x86/kvm/hyper-v: Don't deactivate APICv unconditionally when Hyper-V SynIC enabled
##### From: junjiehua0xff@gmail.com

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: junjiehua0xff@gmail.com
X-Patchwork-Id: 11883727
Return-Path: <SRS0=FTeU=EL=vger.kernel.org=kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-12.6 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,DKIM_VALID_AU,FREEMAIL_FORGED_FROMDOMAIN,FREEMAIL_FROM,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_PATCH,MAILING_LIST_MULTI,SIGNED_OFF_BY,
	SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED,USER_AGENT_GIT autolearn=unavailable
	autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id E267DC00A89
	for <kvm@archiver.kernel.org>; Thu,  5 Nov 2020 09:13:35 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 85D102071A
	for <kvm@archiver.kernel.org>; Thu,  5 Nov 2020 09:13:35 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=gmail.com header.i=@gmail.com
 header.b="Aj4bInwy"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1730453AbgKEJNW (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Thu, 5 Nov 2020 04:13:22 -0500
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:51442 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1730511AbgKEJNR (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 5 Nov 2020 04:13:17 -0500
Received: from mail-pg1-x542.google.com (mail-pg1-x542.google.com
 [IPv6:2607:f8b0:4864:20::542])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 4BE87C0613CF;
        Thu,  5 Nov 2020 01:13:17 -0800 (PST)
Received: by mail-pg1-x542.google.com with SMTP id z24so979676pgk.3;
        Thu, 05 Nov 2020 01:13:17 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=from:to:cc:subject:date:message-id;
        bh=it/aUNucb+eS7C5uHmvXlw2AU+ivxXZX3tKWa1g129A=;
        b=Aj4bInwyaphGTX6fTa2ceBsFKzIuLADKM48JtK+GTW6s03bSUhcT6dBpMLVZp3iAvS
         XyTm/nYnhLFJ9H3vCEiwBGDg0QEhJE3dmKanNa8jF2yDP8QYHRIVB//qBO2WtLYDl8/w
         NcWFjqHQF3Rrch8TI5tHGDufElraqHO17JRm5Cphcy/m0a1n8R4FA6JQWHldJJtG3a/J
         2tlOWIM5wvEnF/akzKDvDFGt8Tyk63oubn2F+WN8OvugTYql/iI1ixpcvka6B709xdja
         yiA93bI4V/JAjE8ri1NcxzDezknNqhj/mdmsxh3XOJil2/AJwb3mbvX3+syCtFFYXU2f
         9iCw==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id;
        bh=it/aUNucb+eS7C5uHmvXlw2AU+ivxXZX3tKWa1g129A=;
        b=Pc/0Z6tAyOBP+vF593AVyhgx8laO8AeS4YajCrKmR3TdW1AnyqO25myQE42Lp/PEIH
         WOC21zxqTif/m0LATX/Axx0fTc6Lirpe1DvOAkCEW5gtJByQxv4K1x18FpWYC0epfzZY
         eKB+DVKX0DEtCBcPTDhzoLnLCaOEi2PdxJEyBqA183VocQ0d6wBDYVMnR66xKbSJXpzQ
         GhAtc52vOM3pK+w603arJAW4g2Iz6kGwfsPn9W/OVMXqRoJ/ICo3sKg8VmtFk/4NpGq1
         u6DlVuISe+WlBC14BS0BCDvmwh9xeNkXEGRC5prAyucbiHZXLIV4rbzdubOGtTMSytKE
         4k4g==
X-Gm-Message-State: AOAM531CikEP4s2Vyf4rdAc8P37qqSeKDmo/LOBWpWQMflo7R9tp1hZ3
        6Pw3RBe63jK1Jj7uAQ+WbDhURfg8RIWTVQ==
X-Google-Smtp-Source: 
 ABdhPJxOCFM30PXg4bz3cULiea6le6eGSaNWAP6cq6k9a4aWDii32DyXTILEprpgOQ63l8V3nwm7Xg==
X-Received: by 2002:a05:6a00:44:b029:155:18ee:a71e with SMTP id
 i4-20020a056a000044b029015518eea71emr1573317pfk.1.1604567596694;
        Thu, 05 Nov 2020 01:13:16 -0800 (PST)
Received: from VM-16-39-centos.localdomain ([124.156.183.47])
        by smtp.gmail.com with ESMTPSA id
 g3sm1551789pgl.55.2020.11.05.01.13.14
        (version=TLS1_2 cipher=ECDHE-ECDSA-AES128-GCM-SHA256 bits=128/128);
        Thu, 05 Nov 2020 01:13:15 -0800 (PST)
From: junjiehua0xff@gmail.com
X-Google-Original-From: junjiehua@tencent.com
To: kvm@vger.kernel.org, linux-kernel@vger.kernel.org
Cc: Paolo Bonzini <pbonzini@redhat.com>,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>,
        Andrey Smetanin <asmetanin@virtuozzo.com>,
        Junjie Hua <junjiehua@tencent.com>
Subject: [PATCH] x86/kvm/hyper-v: Don't deactivate APICv unconditionally when
 Hyper-V SynIC enabled
Date: Thu,  5 Nov 2020 17:12:17 +0800
Message-Id: <1604567537-909-1-git-send-email-junjiehua@tencent.com>
X-Mailer: git-send-email 1.8.3.1
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Junjie Hua <junjiehua@tencent.com>

The current implementation of Hyper-V SynIC[1] request to deactivate 
APICv when SynIC is enabled, since the AutoEOI feature of SynIC is not 
compatible with APICv[2].

Actually, windows doesn't use AutoEOI if deprecating AutoEOI bit is set 
(CPUID.40000004H:EAX[bit 9], HyperV-TLFS v6.0b section 2.4.5), we don't 
need to disable APICv in this case.

[1] commit 5c919412fe61 ("kvm/x86: Hyper-V synthetic interrupt controller")
[2] https://patchwork.kernel.org/patch/7486761/

Signed-off-by: Junjie Hua <junjiehua@tencent.com>
---
 arch/x86/kvm/hyperv.c | 18 +++++++++++++++++-
 arch/x86/kvm/lapic.c  |  3 +++
 2 files changed, 20 insertions(+), 1 deletion(-)

```
