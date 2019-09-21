#### [GIT PULL] VFIO updates for v5.4-rc1
##### From: Alex Williamson <alex.williamson@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Alex Williamson <alex.williamson@redhat.com>
X-Patchwork-Id: 11154851
Return-Path: <SRS0=H7Z2=XP=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 98F8F14DB
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 20 Sep 2019 21:12:31 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 816942080F
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 20 Sep 2019 21:12:31 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728368AbfITVM2 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 20 Sep 2019 17:12:28 -0400
Received: from mx1.redhat.com ([209.132.183.28]:44274 "EHLO mx1.redhat.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1725842AbfITVM1 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 20 Sep 2019 17:12:27 -0400
Received: from smtp.corp.redhat.com (int-mx04.intmail.prod.int.phx2.redhat.com
 [10.5.11.14])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mx1.redhat.com (Postfix) with ESMTPS id 5EE8518CB8FE;
        Fri, 20 Sep 2019 21:12:27 +0000 (UTC)
Received: from x1.home (ovpn-118-102.phx2.redhat.com [10.3.118.102])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 2067F5D9C3;
        Fri, 20 Sep 2019 21:12:27 +0000 (UTC)
Date: Fri, 20 Sep 2019 15:12:26 -0600
From: Alex Williamson <alex.williamson@redhat.com>
To: Linus Torvalds <torvalds@linux-foundation.org>
Cc: "linux-kernel@vger.kernel.org" <linux-kernel@vger.kernel.org>,
        "kvm@vger.kernel.org" <kvm@vger.kernel.org>
Subject: [GIT PULL] VFIO updates for v5.4-rc1
Message-ID: <20190920151226.541871fe@x1.home>
Organization: Red Hat
MIME-Version: 1.0
Content-Type: text/plain; charset=US-ASCII
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.14
X-Greylist: Sender IP whitelisted,
 not delayed by milter-greylist-4.6.2 (mx1.redhat.com [10.5.110.63]);
 Fri, 20 Sep 2019 21:12:27 +0000 (UTC)
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Hi Linus,

The following changes since commit e3fb13b7e47cd18b2bd067ea8a491020b4644baf:

  Merge tag 'modules-for-v5.3-rc6' of git://git.kernel.org/pub/scm/linux/kernel/git/jeyu/linux (2019-08-23 09:22:00 -0700)

are available in the Git repository at:

  git://github.com/awilliam/linux-vfio.git tags/vfio-v5.4-rc1

for you to fetch changes up to e6c5d727db0a86a3ff21aca6824aae87f3bc055f:

  Merge branches 'v5.4/vfio/alexey-tce-memory-free-v1', 'v5.4/vfio/connie-re-arrange-v2', 'v5.4/vfio/hexin-pci-reset-v3', 'v5.4/vfio/parav-mtty-uuid-v2' and 'v5.4/vfio/shameer-iova-list-v8' into v5.4/vfio/next (2019-08-23 11:26:24 -0600)

----------------------------------------------------------------
VFIO updates for v5.4-rc1

 - Fix spapr iommu error case case (Alexey Kardashevskiy)

 - Consolidate region type definitions (Cornelia Huck)

 - Restore saved original PCI state on release (hexin)

 - Simplify mtty sample driver interrupt path (Parav Pandit)

 - Support for reporting valid IOVA regions to user (Shameer Kolothum)

----------------------------------------------------------------
Alex Williamson (1):
      Merge branches 'v5.4/vfio/alexey-tce-memory-free-v1', 'v5.4/vfio/connie-re-arrange-v2', 'v5.4/vfio/hexin-pci-reset-v3', 'v5.4/vfio/parav-mtty-uuid-v2' and 'v5.4/vfio/shameer-iova-list-v8' into v5.4/vfio/next

Alexey Kardashevskiy (1):
      vfio/spapr_tce: Fix incorrect tce_iommu_group memory free

Cornelia Huck (1):
      vfio: re-arrange vfio region definitions

Parav Pandit (1):
      vfio-mdev/mtty: Simplify interrupt generation

Shameer Kolothum (6):
      vfio/type1: Introduce iova list and add iommu aperture validity check
      vfio/type1: Check reserved region conflict and update iova list
      vfio/type1: Update iova list on detach
      vfio/type1: check dma map request is within a valid iova range
      vfio/type1: Add IOVA range capability support
      vfio/type1: remove duplicate retrieval of reserved regions

hexin (1):
      vfio_pci: Restore original state on release

 drivers/vfio/pci/vfio_pci.c         |  17 +-
 drivers/vfio/vfio_iommu_spapr_tce.c |   9 +-
 drivers/vfio/vfio_iommu_type1.c     | 518 +++++++++++++++++++++++++++++++++++-
 include/uapi/linux/vfio.h           |  71 +++--
 samples/vfio-mdev/mtty.c            |  39 +--
 5 files changed, 583 insertions(+), 71 deletions(-)
```
#### [PATCH] KVM: LAPIC: micro-optimize fixed mode ipi delivery
##### From: Wanpeng Li <kernellwp@gmail.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Wanpeng Li <kernellwp@gmail.com>
X-Patchwork-Id: 11154191
Return-Path: <SRS0=H7Z2=XP=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 949AB14E5
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 20 Sep 2019 10:07:35 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 7247020B7C
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 20 Sep 2019 10:07:35 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=gmail.com header.i=@gmail.com
 header.b="vcxVVEjh"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2437967AbfITKHc (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 20 Sep 2019 06:07:32 -0400
Received: from mail-pf1-f193.google.com ([209.85.210.193]:44437 "EHLO
        mail-pf1-f193.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S2390997AbfITKHb (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 20 Sep 2019 06:07:31 -0400
Received: by mail-pf1-f193.google.com with SMTP id q21so4157352pfn.11;
        Fri, 20 Sep 2019 03:07:31 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=from:to:cc:subject:date:message-id;
        bh=jJNUGZzD6WYdW7WfV7c4VlXWYypeskgZBi3y5u2An+c=;
        b=vcxVVEjhhAnlFY+dIZQ4WK+YE01JpIpPV6Qi2Y2N4tPD7KDM5GlHoytVeiB6OJpXTo
         IACh3vdiysSwPoF+NDiBBb8Lumc0vP5opKJRRienBLlmZ98W9iCExr42WCivypqQQOXC
         S0XpLooJJqwzUKmM508Gr6pl7EI0tArdKNXqlRkUEbjVJ3FnpoTFb/ttp9VXv4bmemTc
         /3ZkTDN3Yc+xor35jyPzN4lsu1y+xDAuf3opERIsaZ+/7L1Vg/mVghPEuO+0IRkTN2jm
         HzP1ExW4J3HsrYrKtcyVSpFhM/OSoFcVlywf7iV3DZs82k59dV3kDLd4WuIxkgTrqqfx
         uOuA==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id;
        bh=jJNUGZzD6WYdW7WfV7c4VlXWYypeskgZBi3y5u2An+c=;
        b=hZ5LMMAsuxUAlKv6YM53dkh+ZIpf9lP1LViS8PUQma/V6xGMj6NgcIA/JAbPHPr2Dj
         UnxnZCJ26l80lVm0Qf5vBe/p1RjFKXqob4ViDFnuHXIGX14U3mqSEFw8+wiNvHUv0A1G
         zEvtOBVHS16Px+ef4tuRaR/hewEM0sPRaCHnOefAyNkWlsxOxfCIzeOrgRBvqUG10AGh
         VLFZU8SfCTu/ZSzKQJwNv6N+8kJizXYX3mMHZpCTTUnp8rE592x/kmxdWNWWfxTrGM4m
         ms6pTw+OxTFUnF7e+G/L7cEwXqjQxsTRlF3xS0hJ2Ba4gt2bVUF8g6+hZ0qAGuggusoU
         MRpw==
X-Gm-Message-State: APjAAAW8gWqNQVqORp4uq59+aGDiDWZKZU4IfNJTpQgTVWbMPsVZPZaV
        k0WYaPVzWIETqI9kZHD68Jd1ve6w
X-Google-Smtp-Source: 
 APXvYqx79uB+/pgIn5cFXBKIG+GHsHPmX87BRc+n28KQzU+g+ywrrhcAzHmZ2s2ssPMeUS3D/TPidQ==
X-Received: by 2002:a63:2a87:: with SMTP id
 q129mr14807014pgq.101.1568974050770;
        Fri, 20 Sep 2019 03:07:30 -0700 (PDT)
Received: from localhost.localdomain ([203.205.141.123])
        by smtp.googlemail.com with ESMTPSA id
 i10sm1417345pfa.70.2019.09.20.03.07.27
        (version=TLS1_2 cipher=ECDHE-RSA-AES128-SHA bits=128/128);
        Fri, 20 Sep 2019 03:07:29 -0700 (PDT)
From: Wanpeng Li <kernellwp@gmail.com>
X-Google-Original-From: Wanpeng Li <wanpengli@tencent.com>
To: linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Cc: Paolo Bonzini <pbonzini@redhat.com>,
 =?utf-8?b?UmFkaW0gS3LEjW3DocWZ?= <rkrcmar@redhat.com>,
 Sean Christopherson <sean.j.christopherson@intel.com>,
 Vitaly Kuznetsov <vkuznets@redhat.com>, Wanpeng Li <wanpengli@tencent.com>,
 Jim Mattson <jmattson@google.com>, Joerg Roedel <joro@8bytes.org>
Subject: [PATCH] KVM: LAPIC: micro-optimize fixed mode ipi delivery
Date: Fri, 20 Sep 2019 18:07:18 +0800
Message-Id: <1568974038-13750-1-git-send-email-wanpengli@tencent.com>
X-Mailer: git-send-email 2.7.4
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Wanpeng Li <wanpengli@tencent.com>

After disabling mwait/halt/pause vmexits, RESCHEDULE_VECTOR and 
CALL_FUNCTION_SINGLE_VECTOR etc IPI is one of the main remaining
cause of vmexits observed in product environment which can't be 
optimized by PV IPIs. This patch is the follow-up on commit 
0e6d242eccdb (KVM: LAPIC: Micro optimize IPI latency), to optimize 
redundancy logic before fixed mode ipi is delivered in the fast 
path.

- broadcast handling needs to go slow path, so the delivery mode repair 
  can be delayed to before slow path.
- self-IPI will not be intervened by hypervisor any more after APICv is 
  introduced and the boxes support APICv are popular now. In addition, 
  kvm_apic_map_get_dest_lapic() can handle the self-IPI, so there is no 
  need a shortcut for the non-APICv case.

Signed-off-by: Wanpeng Li <wanpengli@tencent.com>
---
 arch/x86/kvm/irq_comm.c | 6 +++---
 arch/x86/kvm/lapic.c    | 5 -----
 2 files changed, 3 insertions(+), 8 deletions(-)

```
#### [PATCH 01/17] x86: spec_ctrl: fix SPEC_CTRL initialization after kexec
##### From: Andrea Arcangeli <aarcange@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Andrea Arcangeli <aarcange@redhat.com>
X-Patchwork-Id: 11154887
Return-Path: <SRS0=H7Z2=XP=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id A89B615E6
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 20 Sep 2019 21:26:42 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 90E762086A
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 20 Sep 2019 21:26:42 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2387431AbfITVZM (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 20 Sep 2019 17:25:12 -0400
Received: from mx1.redhat.com ([209.132.183.28]:57976 "EHLO mx1.redhat.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1729784AbfITVZM (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 20 Sep 2019 17:25:12 -0400
Received: from smtp.corp.redhat.com (int-mx07.intmail.prod.int.phx2.redhat.com
 [10.5.11.22])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mx1.redhat.com (Postfix) with ESMTPS id 80B048980F5;
        Fri, 20 Sep 2019 21:25:12 +0000 (UTC)
Received: from mail (ovpn-120-159.rdu2.redhat.com [10.10.120.159])
        by smtp.corp.redhat.com (Postfix) with ESMTPS id 0833B10013D9;
        Fri, 20 Sep 2019 21:25:10 +0000 (UTC)
From: Andrea Arcangeli <aarcange@redhat.com>
To: Paolo Bonzini <pbonzini@redhat.com>
Cc: Vitaly Kuznetsov <vkuznets@redhat.com>,
        "Dr. David Alan Gilbert" <dgilbert@redhat.com>,
        Marcelo Tosatti <mtosatti@redhat.com>,
        Peter Xu <peterx@redhat.com>, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org
Subject: [PATCH 01/17] x86: spec_ctrl: fix SPEC_CTRL initialization after
 kexec
Date: Fri, 20 Sep 2019 17:24:53 -0400
Message-Id: <20190920212509.2578-2-aarcange@redhat.com>
In-Reply-To: <20190920212509.2578-1-aarcange@redhat.com>
References: <20190920212509.2578-1-aarcange@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.84 on 10.5.11.22
X-Greylist: Sender IP whitelisted,
 not delayed by milter-greylist-4.6.2 (mx1.redhat.com [10.5.110.67]);
 Fri, 20 Sep 2019 21:25:12 +0000 (UTC)
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

We can't assume the SPEC_CTRL msr is zero at boot because it could be
left enabled by a previous kernel booted with
spec_store_bypass_disable=on.

Without this fix a boot with spec_store_bypass_disable=on followed by
a kexec boot with spec_store_bypass_disable=off would erroneously and
unexpectedly leave bit 2 set in SPEC_CTRL.

Signed-off-by: Andrea Arcangeli <aarcange@redhat.com>
---
 arch/x86/include/asm/msr-index.h |  2 ++
 arch/x86/kernel/cpu/bugs.c       | 20 +++++++++++++++++++-
 2 files changed, 21 insertions(+), 1 deletion(-)

```
#### [kvm-unit-tests PATCH] s390x: Add linemode buffer to fix newline on every print
##### From: Janosch Frank <frankja@linux.ibm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Janosch Frank <frankja@linux.ibm.com>
X-Patchwork-Id: 11154237
Return-Path: <SRS0=H7Z2=XP=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id E30571747
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 20 Sep 2019 11:24:02 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id CA350208C3
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 20 Sep 2019 11:24:02 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2438172AbfITLYC (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 20 Sep 2019 07:24:02 -0400
Received: from mx0a-001b2d01.pphosted.com ([148.163.156.1]:41822 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S2438173AbfITLYB (ORCPT
        <rfc822;kvm@vger.kernel.org>); Fri, 20 Sep 2019 07:24:01 -0400
Received: from pps.filterd (m0098394.ppops.net [127.0.0.1])
        by mx0a-001b2d01.pphosted.com (8.16.0.27/8.16.0.27) with SMTP id
 x8KBLYLU135333
        for <kvm@vger.kernel.org>; Fri, 20 Sep 2019 07:24:00 -0400
Received: from e06smtp04.uk.ibm.com (e06smtp04.uk.ibm.com [195.75.94.100])
        by mx0a-001b2d01.pphosted.com with ESMTP id 2v4wes10rb-1
        (version=TLSv1.2 cipher=AES256-GCM-SHA384 bits=256 verify=NOT)
        for <kvm@vger.kernel.org>; Fri, 20 Sep 2019 07:24:00 -0400
Received: from localhost
        by e06smtp04.uk.ibm.com with IBM ESMTP SMTP Gateway: Authorized Use
 Only! Violators will be prosecuted
        for <kvm@vger.kernel.org> from <frankja@linux.ibm.com>;
        Fri, 20 Sep 2019 12:23:58 +0100
Received: from b06cxnps3074.portsmouth.uk.ibm.com (9.149.109.194)
        by e06smtp04.uk.ibm.com (192.168.101.134) with IBM ESMTP SMTP Gateway:
 Authorized Use Only! Violators will be prosecuted;
        (version=TLSv1/SSLv3 cipher=AES256-GCM-SHA384 bits=256/256)
        Fri, 20 Sep 2019 12:23:55 +0100
Received: from d06av23.portsmouth.uk.ibm.com (d06av23.portsmouth.uk.ibm.com
 [9.149.105.59])
        by b06cxnps3074.portsmouth.uk.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id x8KBNsCu51511386
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Fri, 20 Sep 2019 11:23:54 GMT
Received: from d06av23.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 2DDF7A4053;
        Fri, 20 Sep 2019 11:23:54 +0000 (GMT)
Received: from d06av23.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 09A37A405D;
        Fri, 20 Sep 2019 11:23:53 +0000 (GMT)
Received: from localhost.localdomain (unknown [9.145.165.207])
        by d06av23.portsmouth.uk.ibm.com (Postfix) with ESMTP;
        Fri, 20 Sep 2019 11:23:52 +0000 (GMT)
From: Janosch Frank <frankja@linux.ibm.com>
To: kvm@vger.kernel.org
Cc: linux-s390@vger.kernel.org, david@redhat.com, thuth@redhat.com
Subject: [kvm-unit-tests PATCH] s390x: Add linemode buffer to fix newline on
 every print
Date: Fri, 20 Sep 2019 13:23:45 +0200
X-Mailer: git-send-email 2.17.2
In-Reply-To: <43bb9ff6-4233-3f6f-8cdb-3a00d1662d4d@redhat.com>
References: <43bb9ff6-4233-3f6f-8cdb-3a00d1662d4d@redhat.com>
X-TM-AS-GCONF: 00
x-cbid: 19092011-0016-0000-0000-000002AE8588
X-IBM-AV-DETECTION: SAVI=unused REMOTE=unused XFE=unused
x-cbparentid: 19092011-0017-0000-0000-0000330F39D3
Message-Id: <20190920112345.2359-1-frankja@linux.ibm.com>
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:,,
 definitions=2019-09-20_03:,,
 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 priorityscore=1501
 malwarescore=0 suspectscore=1 phishscore=0 bulkscore=0 spamscore=0
 clxscore=1015 lowpriorityscore=0 mlxscore=0 impostorscore=0
 mlxlogscore=999 adultscore=0 classifier=spam adjust=0 reason=mlx
 scancount=1 engine=8.0.1-1908290000 definitions=main-1909200107
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Linemode seems to add a newline for each sent message which makes
reading rather hard. Hence we add a small buffer and only print if
it's full or a newline is encountered.

Signed-off-by: Janosch Frank <frankja@linux.ibm.com>
Reviewed-by: Thomas Huth <thuth@redhat.com>
Acked-by: David Hildenbrand <david@redhat.com>
---
 lib/s390x/sclp-console.c | 43 ++++++++++++++++++++++++++++++++++++----
 1 file changed, 39 insertions(+), 4 deletions(-)

```
#### [kvm-unit-tests PATCH] s390x: Fix stsi unaligned test and add selector tests
##### From: Janosch Frank <frankja@linux.ibm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Janosch Frank <frankja@linux.ibm.com>
X-Patchwork-Id: 11153865
Return-Path: <SRS0=H7Z2=XP=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 54A861745
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 20 Sep 2019 07:50:35 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 3338C20882
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 20 Sep 2019 07:50:35 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2404834AbfITHue (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 20 Sep 2019 03:50:34 -0400
Received: from mx0b-001b2d01.pphosted.com ([148.163.158.5]:11549 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S2404836AbfITHue (ORCPT
        <rfc822;kvm@vger.kernel.org>); Fri, 20 Sep 2019 03:50:34 -0400
Received: from pps.filterd (m0098413.ppops.net [127.0.0.1])
        by mx0b-001b2d01.pphosted.com (8.16.0.27/8.16.0.27) with SMTP id
 x8K7ccXx056682
        for <kvm@vger.kernel.org>; Fri, 20 Sep 2019 03:50:32 -0400
Received: from e06smtp07.uk.ibm.com (e06smtp07.uk.ibm.com [195.75.94.103])
        by mx0b-001b2d01.pphosted.com with ESMTP id 2v4r31w17d-1
        (version=TLSv1.2 cipher=AES256-GCM-SHA384 bits=256 verify=NOT)
        for <kvm@vger.kernel.org>; Fri, 20 Sep 2019 03:50:31 -0400
Received: from localhost
        by e06smtp07.uk.ibm.com with IBM ESMTP SMTP Gateway: Authorized Use
 Only! Violators will be prosecuted
        for <kvm@vger.kernel.org> from <frankja@linux.ibm.com>;
        Fri, 20 Sep 2019 08:50:30 +0100
Received: from b06cxnps4075.portsmouth.uk.ibm.com (9.149.109.197)
        by e06smtp07.uk.ibm.com (192.168.101.137) with IBM ESMTP SMTP Gateway:
 Authorized Use Only! Violators will be prosecuted;
        (version=TLSv1/SSLv3 cipher=AES256-GCM-SHA384 bits=256/256)
        Fri, 20 Sep 2019 08:50:29 +0100
Received: from d06av24.portsmouth.uk.ibm.com (d06av24.portsmouth.uk.ibm.com
 [9.149.105.60])
        by b06cxnps4075.portsmouth.uk.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id x8K7oSPj51970298
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Fri, 20 Sep 2019 07:50:28 GMT
Received: from d06av24.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 0D41342041;
        Fri, 20 Sep 2019 07:50:28 +0000 (GMT)
Received: from d06av24.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id DB5944203F;
        Fri, 20 Sep 2019 07:50:26 +0000 (GMT)
Received: from localhost.localdomain (unknown [9.145.165.207])
        by d06av24.portsmouth.uk.ibm.com (Postfix) with ESMTP;
        Fri, 20 Sep 2019 07:50:26 +0000 (GMT)
From: Janosch Frank <frankja@linux.ibm.com>
To: kvm@vger.kernel.org
Cc: linux-s390@vger.kernel.org, david@redhat.com, thuth@redhat.com
Subject: [kvm-unit-tests PATCH] s390x: Fix stsi unaligned test and add
 selector tests
Date: Fri, 20 Sep 2019 09:50:20 +0200
X-Mailer: git-send-email 2.17.2
X-TM-AS-GCONF: 00
x-cbid: 19092007-0028-0000-0000-000003A05D75
X-IBM-AV-DETECTION: SAVI=unused REMOTE=unused XFE=unused
x-cbparentid: 19092007-0029-0000-0000-000024626749
Message-Id: <20190920075020.1698-1-frankja@linux.ibm.com>
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:,,
 definitions=2019-09-20_02:,,
 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 priorityscore=1501
 malwarescore=0 suspectscore=1 phishscore=0 bulkscore=0 spamscore=0
 clxscore=1015 lowpriorityscore=0 mlxscore=0 impostorscore=0
 mlxlogscore=954 adultscore=0 classifier=spam adjust=0 reason=mlx
 scancount=1 engine=8.0.1-1908290000 definitions=main-1909200077
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Alignment and selectors test order is not specified and so, if you
have an unaligned address and invalid selectors it's up to the
hypervisor to decide which error is presented.

Let's add valid selectors to the unalignmnet test and add selector
tests.

Signed-off-by: Janosch Frank <frankja@linux.ibm.com>
Reviewed-by: Christian Borntraeger <borntraeger@de.ibm.com>
Acked-by: David Hildenbrand <david@redhat.com>
---
 s390x/stsi.c | 4 +++-
 1 file changed, 3 insertions(+), 1 deletion(-)

```
#### [kvm-unit-tests PATCH v6 1/2] x86: nvmx: fix bug in __enter_guest()From: Marc Orr <marcorr@google.com>
##### From: Marc Orr <marcorr@google.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Marc Orr <marcorr@google.com>
X-Patchwork-Id: 11154957
Return-Path: <SRS0=H7Z2=XP=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 27002912
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 20 Sep 2019 22:29:51 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id F119C206C2
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 20 Sep 2019 22:29:50 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=google.com header.i=@google.com
 header.b="tB0gVAh4"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2404299AbfITW3t (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 20 Sep 2019 18:29:49 -0400
Received: from mail-pl1-f202.google.com ([209.85.214.202]:46954 "EHLO
        mail-pl1-f202.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S2393819AbfITW3t (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 20 Sep 2019 18:29:49 -0400
Received: by mail-pl1-f202.google.com with SMTP id k9so5331670pls.13
        for <kvm@vger.kernel.org>; Fri, 20 Sep 2019 15:29:49 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=date:message-id:mime-version:subject:from:to:cc;
        bh=0CqcLhT+oLR+DR0w+CJZZE5EZQRtfGXdhud+TXHnaZ0=;
        b=tB0gVAh4bcuHLG1fKCO4616SZbwq0b9sNdILRB3GDxhxDBL7jsWQlfEUmRfxq8aS//
         biMBUZdD9xE3b2rPCoZxkx68eGJcQoCc5SSQ4hWxjqyjzwYC2vb73GVlj5iU+21FnTMh
         3hLphxqAj32XncZGUDv1Pb1aIXDnKsN48eptcqtXjxcibdS2EMSCqewizDEex/Utbl6p
         OA3+SZygoKeCRSfpk8xxb11V3VVURRKl6DFudPf6qC3vMW/I+2Nf9WmQQIJYMtfQRZ9j
         E0BQOzEr6Ri6VCK4z0ZSS3hcweE7ioACstnRvp0yQ4yJN44LLaaQ9K9YUSWkJSWv4dqM
         5B1Q==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:date:message-id:mime-version:subject:from:to:cc;
        bh=0CqcLhT+oLR+DR0w+CJZZE5EZQRtfGXdhud+TXHnaZ0=;
        b=iIiSt4ouKVkrd/H2N1sy465Q+NPgcMtSubnJXGdAieQH46HQ0CYezAeqr04ocJxl/W
         y7+7dfqabVX8VwtK9JT+lIrKOmY5tW8Y/bl+FNceIGfyQji9qMkslBZUKwpsXpXavZWX
         dl9Yc4Bb34sUl/k14w+3AKwLjc7Jy//AHxJYwVLn8W2Ov389hFI6syKYX8PcfezXaMoM
         CfQJL4RVA0M2JuGQbJWtiZvxwHVyptrPDMDp/7pPIMIyN6XxHbd3ck1R82tkofRDZl6L
         xHyajQz8igyxs1UabTl2J8OygdH24tPYmfYawD7YMIlQZMP905xHICwFnpafoszCuUeF
         QTJw==
X-Gm-Message-State: APjAAAURMhE8t4bb20Qd5I5SzmQP6zEb4zu0hiynE9i7YCBPqOopSaeU
        ubAdDYdCFs4saBQQTnarI6u+3sgH+VkkZhSoa52SVEQplL7B9IsBwKzVd0WVfzmHNNzaiHPNn7L
        iEBWNlx8qwR+4vIyka8dlSdcmHXG/Hqmg0LT7iWq9Ws0S2F2HG/PGrQ67D7zK
X-Google-Smtp-Source: 
 APXvYqyrpgx0g8Tl3W83GbmPvW4SN4TMLPl8YKx8uo67vB5nZkRZw/MpGbhrr2SuBWz2ZHFUWqf1DoZUjwAX
X-Received: by 2002:a63:b70a:: with SMTP id t10mr18152759pgf.25.1569018588397;
 Fri, 20 Sep 2019 15:29:48 -0700 (PDT)
Date: Fri, 20 Sep 2019 15:29:44 -0700
Message-Id: <20190920222945.235480-1-marcorr@google.com>
Mime-Version: 1.0
X-Mailer: git-send-email 2.23.0.351.gc4317032e6-goog
Subject: [kvm-unit-tests PATCH v6 1/2] x86: nvmx: fix bug in __enter_guest()
From: Marc Orr <marcorr@google.com>
To: kvm@vger.kernel.org, jmattson@google.com, pshier@google.com,
        sean.j.christopherson@intel.com, krish.sadhukhan@oracle.com,
        pbonzini@redhat.com, rkrcmar@redhat.com
Cc: Marc Orr <marcorr@google.com>
Content-Type: text/plain; charset="UTF-8"
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

__enter_guest() should only set the launched flag when a launch has
succeeded. Thus, don't set the launched flag when the VMX_ENTRY_FAILURE,
bit 31, is set in the VMCS exit reason.

Reviewed-by: Krish Sadhukhan <krish.sadhukhan@oracle.com>
Reviewed-by: Sean Christopherson <sean.j.christopherson@intel.com>
Signed-off-by: Marc Orr <marcorr@google.com>
---
v5 -> v6
* No changes.

 x86/vmx.c | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
#### [RFC 1/2] kvm: Mechanism to copy host timekeeping parameters into guest.
##### From: Suleiman Souhlal <suleiman@google.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Suleiman Souhlal <suleiman@google.com>
X-Patchwork-Id: 11153787
Return-Path: <SRS0=H7Z2=XP=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 42A4276
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 20 Sep 2019 06:27:37 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 16C6520882
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 20 Sep 2019 06:27:37 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=google.com header.i=@google.com
 header.b="NwItX0CD"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2394873AbfITG1f (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 20 Sep 2019 02:27:35 -0400
Received: from mail-ua1-f74.google.com ([209.85.222.74]:55008 "EHLO
        mail-ua1-f74.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S2393085AbfITG1f (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 20 Sep 2019 02:27:35 -0400
Received: by mail-ua1-f74.google.com with SMTP id t16so1208684uae.21
        for <kvm@vger.kernel.org>; Thu, 19 Sep 2019 23:27:32 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=date:in-reply-to:message-id:mime-version:references:subject:from:to
         :cc;
        bh=tCwobJ4sibSbRL27xRdckc8ojKP82LRYHZd+OSAZkFc=;
        b=NwItX0CDO8BWB79lwMnI/3DOOTIfkoSTBe9lNRVdjukKaRivMeIvDHkWK6yp5k8u63
         hEB341B4VTKGuk0Lvr27YGvMrtomaF+Hyrf1GkLEAbTbLOqrmZJ2DoKmskO2dalXC4LO
         VkvtJWhOvXAdrCPnilFMiGLU5d8z2c/EzKx73QIgZIZCj6ho3L2rns7kqDWcEOpZJ0S3
         I2rlk0NbDpwaXmpFVRfwpgPU9+6z/1Ikt+w1M0dnORZdINjQ7hJeksL1pHqC4JTK+93p
         MV6qrub4k3YpL665sq4WiT9lRI+/WzmAJNb0yculC6qO9xyPgphDfaa9D0uXUvuABYSU
         hb8A==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:date:in-reply-to:message-id:mime-version
         :references:subject:from:to:cc;
        bh=tCwobJ4sibSbRL27xRdckc8ojKP82LRYHZd+OSAZkFc=;
        b=YlGoO5ls7Wx81FZLhyIbpXwIsFVvDQ17tdLVK+GTHarSuyjS0xnK2gmZTZGLcgS0hg
         HeGT1gy5bmSHK+oPQ8XQaARsOVVf04yXJ+DZ9jTV/dWcKsk3IVGHCStVDmZOxPoPx4t+
         hNU5fEfP38L4c9etEcgPy55DpPSwTBuidXdBVSaGTvQkdVpq1psfSToxCbjEuHLiwGKB
         8FrDb0HNK3X7FNL1+9LkwiYtjzTO1iKVnx3rl6j3Kc+oXyEG6res/+3eleSsGzKPXY2e
         8TdBtddGismmeVayEl7txIZMuteoUpCO4P3d2aa5Z2NrqoOVgGU/IPK79pObzHUuO4JX
         dVSQ==
X-Gm-Message-State: APjAAAVn8gz95SnyOZA4gAeIL+qACye/OTuiSY7VD23W94M9R6oMRpde
        CkeQDII0OxhSB+VBvI6ds9r56LSo+bAs+g==
X-Google-Smtp-Source: 
 APXvYqwkpI1UTuytyD+va/BNDVesQIbTDdeVsObF4jwY61WcWFOHCDgl8oIjbxKI5sjw4aUWlO8ab6fCNgQ4rA==
X-Received: by 2002:ab0:5ac6:: with SMTP id x6mr8614021uae.7.1568960852015;
 Thu, 19 Sep 2019 23:27:32 -0700 (PDT)
Date: Fri, 20 Sep 2019 15:27:12 +0900
In-Reply-To: <20190920062713.78503-1-suleiman@google.com>
Message-Id: <20190920062713.78503-2-suleiman@google.com>
Mime-Version: 1.0
References: <20190920062713.78503-1-suleiman@google.com>
X-Mailer: git-send-email 2.23.0.351.gc4317032e6-goog
Subject: [RFC 1/2] kvm: Mechanism to copy host timekeeping parameters into
 guest.
From: Suleiman Souhlal <suleiman@google.com>
To: pbonzini@redhat.com, rkrcmar@redhat.com, tglx@linutronix.de
Cc: john.stultz@linaro.org, sboyd@kernel.org,
        linux-kernel@vger.kernel.org, kvm@vger.kernel.org,
        Suleiman Souhlal <suleiman@google.com>
Content-Type: text/plain; charset="UTF-8"
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This is used to synchronize time between host and guest.
The guest can request the (guest) physical address it wants the
data in through the MSR_KVM_TIMEKEEPER_EN MSR.

We maintain a shadow copy of the timekeeper that gets updated
whenever the timekeeper gets updated, and then copied into the
guest.

It currently assumes the host timekeeper is "tsc".

Signed-off-by: Suleiman Souhlal <suleiman@google.com>
---
 arch/x86/include/asm/kvm_host.h      |   3 +
 arch/x86/include/asm/pvclock-abi.h   |  27 ++++++
 arch/x86/include/uapi/asm/kvm_para.h |   1 +
 arch/x86/kvm/x86.c                   | 121 +++++++++++++++++++++++++++
 4 files changed, 152 insertions(+)

```
#### [RFC PATCH V2 1/6] mdev: class id support
##### From: Jason Wang <jasowang@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Jason Wang <jasowang@redhat.com>
X-Patchwork-Id: 11154005
Return-Path: <SRS0=H7Z2=XP=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 653CD14ED
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 20 Sep 2019 08:22:39 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 3A6DC21A4C
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 20 Sep 2019 08:22:39 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2437789AbfITIWf (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 20 Sep 2019 04:22:35 -0400
Received: from mx1.redhat.com ([209.132.183.28]:47384 "EHLO mx1.redhat.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S2395231AbfITIWe (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 20 Sep 2019 04:22:34 -0400
Received: from smtp.corp.redhat.com (int-mx07.intmail.prod.int.phx2.redhat.com
 [10.5.11.22])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mx1.redhat.com (Postfix) with ESMTPS id 698A1309BDBC;
        Fri, 20 Sep 2019 08:22:33 +0000 (UTC)
Received: from jason-ThinkPad-X1-Carbon-6th.redhat.com
 (ovpn-12-88.pek2.redhat.com [10.72.12.88])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 227911018A13;
        Fri, 20 Sep 2019 08:22:11 +0000 (UTC)
From: Jason Wang <jasowang@redhat.com>
To: kvm@vger.kernel.org, linux-s390@vger.kernel.org,
        linux-kernel@vger.kernel.org, dri-devel@lists.freedesktop.org,
        intel-gfx@lists.freedesktop.org,
        intel-gvt-dev@lists.freedesktop.org, kwankhede@nvidia.com,
        alex.williamson@redhat.com, mst@redhat.com, tiwei.bie@intel.com
Cc: virtualization@lists.linux-foundation.org, netdev@vger.kernel.org,
        cohuck@redhat.com, maxime.coquelin@redhat.com,
        cunming.liang@intel.com, zhihong.wang@intel.com,
        rob.miller@broadcom.com, xiao.w.wang@intel.com,
        haotian.wang@sifive.com, zhenyuw@linux.intel.com,
        zhi.a.wang@intel.com, jani.nikula@linux.intel.com,
        joonas.lahtinen@linux.intel.com, rodrigo.vivi@intel.com,
        airlied@linux.ie, daniel@ffwll.ch, farman@linux.ibm.com,
        pasic@linux.ibm.com, sebott@linux.ibm.com, oberpar@linux.ibm.com,
        heiko.carstens@de.ibm.com, gor@linux.ibm.com,
        borntraeger@de.ibm.com, akrowiak@linux.ibm.com,
        pmorel@linux.ibm.com, freude@linux.ibm.com, lingshan.zhu@intel.com,
        idos@mellanox.com, eperezma@redhat.com, lulu@redhat.com,
        Jason Wang <jasowang@redhat.com>
Subject: [RFC PATCH V2 1/6] mdev: class id support
Date: Fri, 20 Sep 2019 16:20:45 +0800
Message-Id: <20190920082050.19352-2-jasowang@redhat.com>
In-Reply-To: <20190920082050.19352-1-jasowang@redhat.com>
References: <20190920082050.19352-1-jasowang@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.84 on 10.5.11.22
X-Greylist: Sender IP whitelisted,
 not delayed by milter-greylist-4.5.16 (mx1.redhat.com [10.5.110.45]);
 Fri, 20 Sep 2019 08:22:33 +0000 (UTC)
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Mdev bus only support vfio driver right now, so it doesn't implement
match method. But in the future, we may add drivers other than vfio,
one example is virtio-mdev[1] driver. This means we need to add device
class id support in bus match method to pair the mdev device and mdev
driver correctly.

So this patch add id_table to mdev_driver and id for mdev parent, and
implement the match method for mdev bus.

Signed-off-by: Jason Wang <jasowang@redhat.com>
---
 Documentation/driver-api/vfio-mediated-device.rst |  7 +++++--
 drivers/gpu/drm/i915/gvt/kvmgt.c                  |  2 +-
 drivers/s390/cio/vfio_ccw_ops.c                   |  2 +-
 drivers/s390/crypto/vfio_ap_ops.c                 |  3 ++-
 drivers/vfio/mdev/mdev_core.c                     | 14 ++++++++++++--
 drivers/vfio/mdev/mdev_driver.c                   | 14 ++++++++++++++
 drivers/vfio/mdev/mdev_private.h                  |  1 +
 drivers/vfio/mdev/vfio_mdev.c                     |  6 ++++++
 include/linux/mdev.h                              |  6 +++++-
 include/linux/mod_devicetable.h                   |  8 ++++++++
 samples/vfio-mdev/mbochs.c                        |  2 +-
 samples/vfio-mdev/mdpy.c                          |  2 +-
 samples/vfio-mdev/mtty.c                          |  2 +-
 13 files changed, 58 insertions(+), 11 deletions(-)

```
#### [kvm-unit-tests PATCH v3 1/6] s390x: Use interrupts in SCLP and add locking
##### From: Janosch Frank <frankja@linux.ibm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Janosch Frank <frankja@linux.ibm.com>
X-Patchwork-Id: 11153973
Return-Path: <SRS0=H7Z2=XP=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id C0C051747
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 20 Sep 2019 08:04:20 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 9F36921D6C
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 20 Sep 2019 08:04:20 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2437725AbfITIET (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 20 Sep 2019 04:04:19 -0400
Received: from mx0b-001b2d01.pphosted.com ([148.163.158.5]:38008 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S2437718AbfITIET (ORCPT
        <rfc822;kvm@vger.kernel.org>); Fri, 20 Sep 2019 04:04:19 -0400
Received: from pps.filterd (m0098417.ppops.net [127.0.0.1])
        by mx0a-001b2d01.pphosted.com (8.16.0.27/8.16.0.27) with SMTP id
 x8K7cHoa122233
        for <kvm@vger.kernel.org>; Fri, 20 Sep 2019 04:04:18 -0400
Received: from e06smtp01.uk.ibm.com (e06smtp01.uk.ibm.com [195.75.94.97])
        by mx0a-001b2d01.pphosted.com with ESMTP id 2v4st1adfd-1
        (version=TLSv1.2 cipher=AES256-GCM-SHA384 bits=256 verify=NOT)
        for <kvm@vger.kernel.org>; Fri, 20 Sep 2019 04:04:17 -0400
Received: from localhost
        by e06smtp01.uk.ibm.com with IBM ESMTP SMTP Gateway: Authorized Use
 Only! Violators will be prosecuted
        for <kvm@vger.kernel.org> from <frankja@linux.ibm.com>;
        Fri, 20 Sep 2019 09:04:16 +0100
Received: from b06cxnps4074.portsmouth.uk.ibm.com (9.149.109.196)
        by e06smtp01.uk.ibm.com (192.168.101.131) with IBM ESMTP SMTP Gateway:
 Authorized Use Only! Violators will be prosecuted;
        (version=TLSv1/SSLv3 cipher=AES256-GCM-SHA384 bits=256/256)
        Fri, 20 Sep 2019 09:04:13 +0100
Received: from d06av24.portsmouth.uk.ibm.com (mk.ibm.com [9.149.105.60])
        by b06cxnps4074.portsmouth.uk.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id x8K84CMQ47644694
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Fri, 20 Sep 2019 08:04:12 GMT
Received: from d06av24.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id F0F8242042;
        Fri, 20 Sep 2019 08:04:11 +0000 (GMT)
Received: from d06av24.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 9B5A24203F;
        Fri, 20 Sep 2019 08:04:10 +0000 (GMT)
Received: from localhost.localdomain (unknown [9.145.165.207])
        by d06av24.portsmouth.uk.ibm.com (Postfix) with ESMTP;
        Fri, 20 Sep 2019 08:04:10 +0000 (GMT)
From: Janosch Frank <frankja@linux.ibm.com>
To: kvm@vger.kernel.org
Cc: linux-s390@vger.kernel.org, david@redhat.com, thuth@redhat.com
Subject: [kvm-unit-tests PATCH v3 1/6] s390x: Use interrupts in SCLP and add
 locking
Date: Fri, 20 Sep 2019 10:03:51 +0200
X-Mailer: git-send-email 2.17.2
In-Reply-To: <20190920080356.1948-1-frankja@linux.ibm.com>
References: <20190920080356.1948-1-frankja@linux.ibm.com>
X-TM-AS-GCONF: 00
x-cbid: 19092008-4275-0000-0000-00000368EB1E
X-IBM-AV-DETECTION: SAVI=unused REMOTE=unused XFE=unused
x-cbparentid: 19092008-4276-0000-0000-0000387B5979
Message-Id: <20190920080356.1948-2-frankja@linux.ibm.com>
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:,,
 definitions=2019-09-20_02:,,
 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 priorityscore=1501
 malwarescore=0 suspectscore=1 phishscore=0 bulkscore=0 spamscore=0
 clxscore=1015 lowpriorityscore=0 mlxscore=0 impostorscore=0
 mlxlogscore=999 adultscore=0 classifier=spam adjust=0 reason=mlx
 scancount=1 engine=8.0.1-1908290000 definitions=main-1909200077
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

We need to properly implement interrupt handling for SCLP, because on
z/VM and LPAR SCLP calls are not synchronous!

Also with smp CPUs have to compete for sclp. Let's add some locking,
so they execute sclp calls in an orderly fashion and don't compete for
the data buffer.

Signed-off-by: Janosch Frank <frankja@linux.ibm.com>
Reviewed-by: Thomas Huth <thuth@redhat.com>
Acked-by: David Hildenbrand <david@redhat.com>
---
 lib/s390x/asm/interrupt.h |  2 ++
 lib/s390x/interrupt.c     | 12 +++++++--
 lib/s390x/sclp-console.c  |  2 ++
 lib/s390x/sclp.c          | 55 +++++++++++++++++++++++++++++++++++++--
 lib/s390x/sclp.h          |  3 +++
 5 files changed, 70 insertions(+), 4 deletions(-)

```
