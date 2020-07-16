

#### [PATCH 0/7] KVM: nVMX: Bug fixes and cleanup
##### From: Sean Christopherson <sean.j.christopherson@intel.com>

```c
From patchwork Wed Jul 15 04:05:50 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Sean Christopherson <sean.j.christopherson@intel.com>
X-Patchwork-Id: 11664113
Return-Path: <SRS0=KTGQ=A2=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 0ACDE14E3
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 15 Jul 2020 04:06:43 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id E5B3A206F5
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 15 Jul 2020 04:06:42 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1725867AbgGOEGC (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 15 Jul 2020 00:06:02 -0400
Received: from mga17.intel.com ([192.55.52.151]:16670 "EHLO mga17.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1725770AbgGOEGB (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 15 Jul 2020 00:06:01 -0400
IronPort-SDR: 
 keFLI2pZFftDHBMkkaHIc3kzVRpmz8P2NqsA0yi9/+K9R5lvaJ1qIrsZWX4vD6Zdt4CmF/oj4Y
 XNLcJuyamPkQ==
X-IronPort-AV: E=McAfee;i="6000,8403,9682"; a="129167478"
X-IronPort-AV: E=Sophos;i="5.75,353,1589266800";
   d="scan'208";a="129167478"
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from fmsmga006.fm.intel.com ([10.253.24.20])
  by fmsmga107.fm.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 14 Jul 2020 21:06:01 -0700
IronPort-SDR: 
 oLkwvnypvmrjiOV2yo8kXfycM+VsPm00teLTHWLLxxVaKBlwcl9+ijgnqqc48T1EM0ZxqhjFZ6
 k/LDhNNQntRw==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.75,353,1589266800";
   d="scan'208";a="485587000"
Received: from sjchrist-coffee.jf.intel.com ([10.54.74.152])
  by fmsmga006.fm.intel.com with ESMTP; 14 Jul 2020 21:06:00 -0700
From: Sean Christopherson <sean.j.christopherson@intel.com>
To: Paolo Bonzini <pbonzini@redhat.com>
Cc: Sean Christopherson <sean.j.christopherson@intel.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org, Dan Cross <dcross@google.com>,
        Peter Shier <pshier@google.com>
Subject: [PATCH 0/7] KVM: nVMX: Bug fixes and cleanup
Date: Tue, 14 Jul 2020 21:05:50 -0700
Message-Id: <20200715040557.5889-1-sean.j.christopherson@intel.com>
X-Mailer: git-send-email 2.26.0
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Fix for a brutal segment caching bug that manifested as random nested
VM-Enter failures when running with unrestricted guest disabled.  A few
more bug fixes and cleanups for stuff found by inspection when hunting
down the caching issue.

Sean Christopherson (7):
  KVM: nVMX: Reset the segment cache when stuffing guest segs
  KVM: nVMX: Reload vmcs01 if getting vmcs12's pages fails
  KVM: nVMX: Explicitly check for valid guest state for !unrestricted
    guest
  KVM: nVMX: Move free_nested() below vmx_switch_vmcs()
  KVM: nVMX: Ensure vmcs01 is the loaded VMCS when freeing nested state
  KVM: nVMX: Drop redundant VMCS switch and free_nested() call
  KVM: nVMX: WARN on attempt to switch the currently loaded VMCS

 arch/x86/kvm/vmx/nested.c | 103 ++++++++++++++++++++------------------
 arch/x86/kvm/vmx/vmx.c    |   8 +--
 arch/x86/kvm/vmx/vmx.h    |  10 ++++
 3 files changed, 66 insertions(+), 55 deletions(-)
```
#### [PATCH 0/8] KVM: x86/mmu: ITLB multi-hit workaround fixes
##### From: Sean Christopherson <sean.j.christopherson@intel.com>

```c
From patchwork Wed Jul 15 04:27:17 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Sean Christopherson <sean.j.christopherson@intel.com>
X-Patchwork-Id: 11664177
Return-Path: <SRS0=KTGQ=A2=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id BDF0C913
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 15 Jul 2020 04:28:12 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id A247B206F4
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 15 Jul 2020 04:28:12 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726440AbgGOE11 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 15 Jul 2020 00:27:27 -0400
Received: from mga05.intel.com ([192.55.52.43]:59539 "EHLO mga05.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1725770AbgGOE11 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 15 Jul 2020 00:27:27 -0400
IronPort-SDR: 
 1myXmjA3WpzCTn8bKX2UnmSqPQiJCt6TAvHd7WUOrDOrFcW4hLBCC1rVAQPJ+oMU2UtSk+jXVl
 6UWHSSe7wLeA==
X-IronPort-AV: E=McAfee;i="6000,8403,9682"; a="233936293"
X-IronPort-AV: E=Sophos;i="5.75,354,1589266800";
   d="scan'208";a="233936293"
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from fmsmga004.fm.intel.com ([10.253.24.48])
  by fmsmga105.fm.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 14 Jul 2020 21:27:26 -0700
IronPort-SDR: 
 yYi6MGSXlFAUgYHAavn7DNXJz8sblz4eHr1QSjSPTnAAwL+UU2MJqDmHiBsBLaw30xLzyHH2CO
 dZJlNyRonj2Q==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.75,354,1589266800";
   d="scan'208";a="308118773"
Received: from sjchrist-coffee.jf.intel.com ([10.54.74.152])
  by fmsmga004.fm.intel.com with ESMTP; 14 Jul 2020 21:27:26 -0700
From: Sean Christopherson <sean.j.christopherson@intel.com>
To: Paolo Bonzini <pbonzini@redhat.com>
Cc: Sean Christopherson <sean.j.christopherson@intel.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org, Junaid Shahid <junaids@google.com>
Subject: [PATCH 0/8] KVM: x86/mmu: ITLB multi-hit workaround fixes
Date: Tue, 14 Jul 2020 21:27:17 -0700
Message-Id: <20200715042725.10961-1-sean.j.christopherson@intel.com>
X-Mailer: git-send-email 2.26.0
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Patch 1 is a minor fix for a very theoretical bug where KVM could skip
the final "commit zap" when recovering shadow pages for the NX huge
page mitigation.

Patch 2 is cleanup that's made possible by patch 1.

Patches 3-5 are the main course and fix bugs in the NX huge page
accounting where shadow pages are incorrectly added to the list of
disallowed huge pages.  KVM doesn't actually check to see if the page
could actually have been a large page when adding to the disallowed list.
This result in what are effectively spurious zaps.  The biggest issue is
likely with shadow pages in the upper levels, i.e. levels 3 and 4, as they
are either unlikely to be huge (1gb) or flat out can't be huge (512tb).
And because of the way KVM zaps, the upper levels will be zapped first,
i.e. KVM is likely zapping and rebuilding a decent number of its shadow
pages for zero benefit.

Ideally, patches 3-5 would be a single patch to ease backporting.  In the
end, I decided the change is probably not suitable for stable as at worst
it creates an infrequent performance spike (assuming the admin isn't going
crazy with the recovery frequency), and it's far from straightforward or
risk free.  Cramming everything into a single patch was a mess.

Patches 6-8 are cleanups in related code.  The 'hlevel' name in particular
has been on my todo list for a while.

Sean Christopherson (8):
  KVM: x86/mmu: Commit zap of remaining invalid pages when recovering
    lpages
  KVM: x86/mmu: Refactor the zap loop for recovering NX lpages
  KVM: x86/mmu: Move "huge page disallowed" calculation into mapping
    helpers
  KVM: x86/mmu: Capture requested page level before NX huge page
    workaround
  KVM: x86/mmu: Account NX huge page disallowed iff huge page was
    requested
  KVM: x86/mmu: Rename 'hlevel' to 'level' in FNAME(fetch)
  KVM: x86/mmu: Hoist ITLB multi-hit workaround check up a level
  KVM: x86/mmu: Track write/user faults using bools

 arch/x86/kvm/mmu/mmu.c         | 58 +++++++++++++++++++++-------------
 arch/x86/kvm/mmu/paging_tmpl.h | 39 ++++++++++++-----------
 2 files changed, 57 insertions(+), 40 deletions(-)
```
#### [PATCH v7 0/2] s390: virtio: let arch validate VIRTIO features
##### From: Pierre Morel <pmorel@linux.ibm.com>

```c
From patchwork Wed Jul 15 08:31:07 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Pierre Morel <pmorel@linux.ibm.com>
X-Patchwork-Id: 11664421
Return-Path: <SRS0=KTGQ=A2=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id B8AC1913
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 15 Jul 2020 08:31:31 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id A91CF20672
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 15 Jul 2020 08:31:31 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729834AbgGOIbb (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 15 Jul 2020 04:31:31 -0400
Received: from mx0b-001b2d01.pphosted.com ([148.163.158.5]:57786 "EHLO
        mx0b-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1728505AbgGOIbZ (ORCPT
        <rfc822;kvm@vger.kernel.org>); Wed, 15 Jul 2020 04:31:25 -0400
Received: from pps.filterd (m0098417.ppops.net [127.0.0.1])
        by mx0a-001b2d01.pphosted.com (8.16.0.42/8.16.0.42) with SMTP id
 06F84baI176448;
        Wed, 15 Jul 2020 04:31:16 -0400
Received: from pps.reinject (localhost [127.0.0.1])
        by mx0a-001b2d01.pphosted.com with ESMTP id 3298wve0vf-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Wed, 15 Jul 2020 04:31:16 -0400
Received: from m0098417.ppops.net (m0098417.ppops.net [127.0.0.1])
        by pps.reinject (8.16.0.36/8.16.0.36) with SMTP id 06F85vDk183395;
        Wed, 15 Jul 2020 04:31:16 -0400
Received: from ppma06ams.nl.ibm.com (66.31.33a9.ip4.static.sl-reverse.com
 [169.51.49.102])
        by mx0a-001b2d01.pphosted.com with ESMTP id 3298wve0ur-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Wed, 15 Jul 2020 04:31:16 -0400
Received: from pps.filterd (ppma06ams.nl.ibm.com [127.0.0.1])
        by ppma06ams.nl.ibm.com (8.16.0.42/8.16.0.42) with SMTP id
 06F8RNAM018243;
        Wed, 15 Jul 2020 08:31:14 GMT
Received: from b06cxnps3074.portsmouth.uk.ibm.com
 (d06relay09.portsmouth.uk.ibm.com [9.149.109.194])
        by ppma06ams.nl.ibm.com with ESMTP id 3274pgv3au-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Wed, 15 Jul 2020 08:31:14 +0000
Received: from d06av21.portsmouth.uk.ibm.com (d06av21.portsmouth.uk.ibm.com
 [9.149.105.232])
        by b06cxnps3074.portsmouth.uk.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id 06F8VBC924576290
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Wed, 15 Jul 2020 08:31:11 GMT
Received: from d06av21.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 090035204F;
        Wed, 15 Jul 2020 08:31:11 +0000 (GMT)
Received: from oc3016276355.ibm.com (unknown [9.145.79.52])
        by d06av21.portsmouth.uk.ibm.com (Postfix) with ESMTP id 276C052051;
        Wed, 15 Jul 2020 08:31:10 +0000 (GMT)
From: Pierre Morel <pmorel@linux.ibm.com>
To: linux-kernel@vger.kernel.org
Cc: pasic@linux.ibm.com, borntraeger@de.ibm.com, frankja@linux.ibm.com,
        mst@redhat.com, jasowang@redhat.com, cohuck@redhat.com,
        kvm@vger.kernel.org, linux-s390@vger.kernel.org,
        virtualization@lists.linux-foundation.org, thomas.lendacky@amd.com,
        david@gibson.dropbear.id.au, linuxram@us.ibm.com,
        hca@linux.ibm.com, gor@linux.ibm.com
Subject: [PATCH v7 0/2] s390: virtio: let arch validate VIRTIO features
Date: Wed, 15 Jul 2020 10:31:07 +0200
Message-Id: <1594801869-13365-1-git-send-email-pmorel@linux.ibm.com>
X-Mailer: git-send-email 1.8.3.1
X-TM-AS-GCONF: 00
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.235,18.0.687
 definitions=2020-07-15_05:2020-07-15,2020-07-15 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 bulkscore=0
 priorityscore=1501 lowpriorityscore=0 suspectscore=1 adultscore=0
 impostorscore=0 spamscore=0 phishscore=0 malwarescore=0 mlxscore=0
 mlxlogscore=999 clxscore=1015 classifier=spam adjust=0 reason=mlx
 scancount=1 engine=8.12.0-2006250000 definitions=main-2007150068
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Hi all,

The goal of the series is to give a chance to the architecture
to validate VIRTIO device features.

in this respin:

1) I kept removed the ack from Jason as I reworked the patch
   @Jason, the nature and goal of the patch did not really changed
           please can I get back your acked-by with these changes?

2) Rewording for warning messages

Regards,
Pierre

Pierre Morel (2):
  virtio: let arch validate VIRTIO features
  s390: virtio: PV needs VIRTIO I/O device protection

 arch/s390/mm/init.c           | 28 ++++++++++++++++++++++++++++
 drivers/virtio/virtio.c       | 19 +++++++++++++++++++
 include/linux/virtio_config.h |  1 +
 3 files changed, 48 insertions(+)
Acked-by: Jason Wang <jasowang@redhat.com>
```
#### [PATCH v5 00/18] Add support for Nitro Enclaves
##### From: Andra Paraschiv <andraprs@amazon.com>

```c
From patchwork Wed Jul 15 19:45:22 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Andra Paraschiv <andraprs@amazon.com>
X-Patchwork-Id: 11666125
Return-Path: <SRS0=KTGQ=A2=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 320EE13A4
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 15 Jul 2020 19:46:06 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 0376320657
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 15 Jul 2020 19:46:06 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=amazon.com header.i=@amazon.com
 header.b="Uj9FeJ9Y"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726932AbgGOTqB (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 15 Jul 2020 15:46:01 -0400
Received: from smtp-fw-33001.amazon.com ([207.171.190.10]:54807 "EHLO
        smtp-fw-33001.amazon.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726661AbgGOTqA (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 15 Jul 2020 15:46:00 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
  d=amazon.com; i=@amazon.com; q=dns/txt; s=amazon201209;
  t=1594842360; x=1626378360;
  h=from:to:cc:subject:date:message-id:mime-version:
   content-transfer-encoding;
  bh=07ZiHsSJNDyPfOvpZkEmwAGWdhDd52BASM8p6D09UtE=;
  b=Uj9FeJ9YvPAofU/XH9a9oeNz68jep07n0ALYYrJCnuJs3XbkefTQnIQa
   VVUCQvPY97qST+oSZMTWO2YX+2pOGRtlyRuLb+kHU+hr2g2DNQyz/ECKy
   3bzPP7TMHq9RR7Bvr3SDdS2F+sxtRRFDknvpVUPAgHASs3iCUOGKRPHUA
   I=;
IronPort-SDR: 
 m0FYBS1y8EPqixIZ3YB7F4fCUkllhYZ4p53vgtEm/8Lyndake2gOPVevlm0oFKIsow/+PrT+ZJ
 4fK+gMGx78qw==
X-IronPort-AV: E=Sophos;i="5.75,356,1589241600";
   d="scan'208";a="58896902"
Received: from sea32-co-svc-lb4-vlan3.sea.corp.amazon.com (HELO
 email-inbound-relay-2b-c300ac87.us-west-2.amazon.com) ([10.47.23.38])
  by smtp-border-fw-out-33001.sea14.amazon.com with ESMTP;
 15 Jul 2020 19:45:57 +0000
Received: from EX13MTAUEA002.ant.amazon.com
 (pdx4-ws-svc-p6-lb7-vlan2.pdx.amazon.com [10.170.41.162])
        by email-inbound-relay-2b-c300ac87.us-west-2.amazon.com (Postfix) with
 ESMTPS id 30B69A25AA;
        Wed, 15 Jul 2020 19:45:57 +0000 (UTC)
Received: from EX13D16EUB001.ant.amazon.com (10.43.166.28) by
 EX13MTAUEA002.ant.amazon.com (10.43.61.77) with Microsoft SMTP Server (TLS)
 id 15.0.1497.2; Wed, 15 Jul 2020 19:45:56 +0000
Received: from 38f9d34ed3b1.ant.amazon.com (10.43.161.214) by
 EX13D16EUB001.ant.amazon.com (10.43.166.28) with Microsoft SMTP Server (TLS)
 id 15.0.1497.2; Wed, 15 Jul 2020 19:45:46 +0000
From: Andra Paraschiv <andraprs@amazon.com>
To: <linux-kernel@vger.kernel.org>
CC: Anthony Liguori <aliguori@amazon.com>,
        Benjamin Herrenschmidt <benh@kernel.crashing.org>,
        Colm MacCarthaigh <colmmacc@amazon.com>,
        "David Duncan" <davdunc@amazon.com>,
        Bjoern Doebel <doebel@amazon.de>,
        "David Woodhouse" <dwmw@amazon.co.uk>,
        Frank van der Linden <fllinden@amazon.com>,
        Alexander Graf <graf@amazon.de>,
        Greg KH <gregkh@linuxfoundation.org>,
        "Karen Noel" <knoel@redhat.com>,
        Martin Pohlack <mpohlack@amazon.de>,
        Matt Wilson <msw@amazon.com>,
        Paolo Bonzini <pbonzini@redhat.com>,
        Balbir Singh <sblbir@amazon.com>,
        Stefano Garzarella <sgarzare@redhat.com>,
        "Stefan Hajnoczi" <stefanha@redhat.com>,
        Stewart Smith <trawets@amazon.com>,
        "Uwe Dannowski" <uwed@amazon.de>,
        Vitaly Kuznetsov <vkuznets@redhat.com>, <kvm@vger.kernel.org>,
        <ne-devel-upstream@amazon.com>,
        Andra Paraschiv <andraprs@amazon.com>
Subject: [PATCH v5 00/18] Add support for Nitro Enclaves
Date: Wed, 15 Jul 2020 22:45:22 +0300
Message-ID: <20200715194540.45532-1-andraprs@amazon.com>
X-Mailer: git-send-email 2.20.1 (Apple Git-117)
MIME-Version: 1.0
X-Originating-IP: [10.43.161.214]
X-ClientProxiedBy: EX13D46UWB002.ant.amazon.com (10.43.161.70) To
 EX13D16EUB001.ant.amazon.com (10.43.166.28)
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Nitro Enclaves (NE) is a new Amazon Elastic Compute Cloud (EC2) capability
that allows customers to carve out isolated compute environments within EC2
instances [1].

For example, an application that processes sensitive data and runs in a VM,
can be separated from other applications running in the same VM. This
application then runs in a separate VM than the primary VM, namely an enclave.

An enclave runs alongside the VM that spawned it. This setup matches low latency
applications needs. The resources that are allocated for the enclave, such as
memory and CPUs, are carved out of the primary VM. Each enclave is mapped to a
process running in the primary VM, that communicates with the NE driver via an
ioctl interface.

In this sense, there are two components:

1. An enclave abstraction process - a user space process running in the primary
VM guest that uses the provided ioctl interface of the NE driver to spawn an
enclave VM (that's 2 below).

There is a NE emulated PCI device exposed to the primary VM. The driver for this
new PCI device is included in the NE driver.

The ioctl logic is mapped to PCI device commands e.g. the NE_START_ENCLAVE ioctl
maps to an enclave start PCI command. The PCI device commands are then
translated into  actions taken on the hypervisor side; that's the Nitro
hypervisor running on the host where the primary VM is running. The Nitro
hypervisor is based on core KVM technology.

2. The enclave itself - a VM running on the same host as the primary VM that
spawned it. Memory and CPUs are carved out of the primary VM and are dedicated
for the enclave VM. An enclave does not have persistent storage attached.

The memory regions carved out of the primary VM and given to an enclave need to
be aligned 2 MiB / 1 GiB physically contiguous memory regions (or multiple of
this size e.g. 8 MiB). The memory can be allocated e.g. by using hugetlbfs from
user space [2][3]. The memory size for an enclave needs to be at least 64 MiB.
The enclave memory and CPUs need to be from the same NUMA node.

An enclave runs on dedicated cores. CPU 0 and its CPU siblings need to remain
available for the primary VM. A CPU pool has to be set for NE purposes by an
user with admin capability. See the cpu list section from the kernel
documentation [4] for how a CPU pool format looks.

An enclave communicates with the primary VM via a local communication channel,
using virtio-vsock [5]. The primary VM has virtio-pci vsock emulated device,
while the enclave VM has a virtio-mmio vsock emulated device. The vsock device
uses eventfd for signaling. The enclave VM sees the usual interfaces - local
APIC and IOAPIC - to get interrupts from virtio-vsock device. The virtio-mmio
device is placed in memory below the typical 4 GiB.

The application that runs in the enclave needs to be packaged in an enclave
image together with the OS ( e.g. kernel, ramdisk, init ) that will run in the
enclave VM. The enclave VM has its own kernel and follows the standard Linux
boot protocol.

The kernel bzImage, the kernel command line, the ramdisk(s) are part of the
Enclave Image Format (EIF); plus an EIF header including metadata such as magic
number, eif version, image size and CRC.

Hash values are computed for the entire enclave image (EIF), the kernel and
ramdisk(s). That's used, for example, to check that the enclave image that is
loaded in the enclave VM is the one that was intended to be run.

These crypto measurements are included in a signed attestation document
generated by the Nitro Hypervisor and further used to prove the identity of the
enclave; KMS is an example of service that NE is integrated with and that checks
the attestation doc.

The enclave image (EIF) is loaded in the enclave memory at offset 8 MiB. The
init process in the enclave connects to the vsock CID of the primary VM and a
predefined port - 9000 - to send a heartbeat value - 0xb7. This mechanism is
used to check in the primary VM that the enclave has booted.

If the enclave VM crashes or gracefully exits, an interrupt event is received by
the NE driver. This event is sent further to the user space enclave process
running in the primary VM via a poll notification mechanism. Then the user space
enclave process can exit.

Thank you.

Andra

[1] https://aws.amazon.com/ec2/nitro/nitro-enclaves/
[2] https://www.kernel.org/doc/Documentation/vm/hugetlbpage.txt
[3] https://lwn.net/Articles/807108/
[4] https://www.kernel.org/doc/html/latest/admin-guide/kernel-parameters.html
[5] https://man7.org/linux/man-pages/man7/vsock.7.html
---

Patch Series Changelog

The patch series is built on top of v5.8-rc5.

v4 -> v5

* Rebase on top of v5.8-rc5.
* Add more details about the ioctl calls usage e.g. error codes.
* Update the ioctl to set an enclave vCPU to not return a fd.
* Add specific NE error codes.
* Split the NE CPU pool in CPU cores cpumasks.
* Remove log on copy_from_user() / copy_to_user() failure.
* Release the reference to the NE PCI device on failure paths.
* Close enclave fd on copy_to_user() failure.
* Set empty string in case of invalid NE CPU pool sysfs value.
* Early exit on NE CPU pool setup if enclave(s) already running.
* Add more sanity checks for provided vCPUs e.g. maximum possible value.
* Split logic for checking if a vCPU is in pool / getting a vCPU from pool.
* Exit without unpinning the pages on NE PCI dev request failure.
* Add check for the memory region user space address alignment.
* Update the logic to set memory region to not have a hardcoded check for 2 MiB.
* Add arch dependency for Arm / x86.
* v4: https://lore.kernel.org/lkml/20200622200329.52996-1-andraprs@amazon.com/

v3 -> v4

* Rebase on top of v5.8-rc2.
* Add NE API version and the corresponding ioctl call.
* Add enclave / image load flags options.
* Decouple NE ioctl interface from KVM API.
* Remove the "packed" attribute and include padding in the NE data structures.
* Update documentation based on the changes from v4.
* Update sample to match the updates in v4.
* Remove the NE CPU pool init during NE kernel module loading.
* Setup the NE CPU pool at runtime via a sysfs file for the kernel parameter.
* Check if the enclave memory and CPUs are from the same NUMA node.
* Add minimum enclave memory size definition.
* v3: https://lore.kernel.org/lkml/20200525221334.62966-1-andraprs@amazon.com/ 

v2 -> v3

* Rebase on top of v5.7-rc7.
* Add changelog to each patch in the series.
* Remove "ratelimited" from the logs that are not in the ioctl call paths.
* Update static calls sanity checks.
* Remove file ops that do nothing for now.
* Remove GPL additional wording as SPDX-License-Identifier is already in place.
* v2: https://lore.kernel.org/lkml/20200522062946.28973-1-andraprs@amazon.com/

v1 -> v2

* Rebase on top of v5.7-rc6.
* Adapt codebase based on feedback from v1.
* Update ioctl number definition - major and minor.
* Add sample / documentation for the ioctl interface basic flow usage.
* Update cover letter to include more context on the NE overall.
* Add fix for the enclave / vcpu fd creation error cleanup path.
* Add fix reported by kbuild test robot <lkp@intel.com>.
* v1: https://lore.kernel.org/lkml/20200421184150.68011-1-andraprs@amazon.com/

---

Andra Paraschiv (18):
  nitro_enclaves: Add ioctl interface definition
  nitro_enclaves: Define the PCI device interface
  nitro_enclaves: Define enclave info for internal bookkeeping
  nitro_enclaves: Init PCI device driver
  nitro_enclaves: Handle PCI device command requests
  nitro_enclaves: Handle out-of-band PCI device events
  nitro_enclaves: Init misc device providing the ioctl interface
  nitro_enclaves: Add logic for creating an enclave VM
  nitro_enclaves: Add logic for setting an enclave vCPU
  nitro_enclaves: Add logic for getting the enclave image load info
  nitro_enclaves: Add logic for setting an enclave memory region
  nitro_enclaves: Add logic for starting an enclave
  nitro_enclaves: Add logic for terminating an enclave
  nitro_enclaves: Add Kconfig for the Nitro Enclaves driver
  nitro_enclaves: Add Makefile for the Nitro Enclaves driver
  nitro_enclaves: Add sample for ioctl interface usage
  nitro_enclaves: Add overview documentation
  MAINTAINERS: Add entry for the Nitro Enclaves driver

 Documentation/nitro_enclaves/ne_overview.rst  |   87 ++
 .../userspace-api/ioctl/ioctl-number.rst      |    5 +-
 MAINTAINERS                                   |   13 +
 drivers/virt/Kconfig                          |    2 +
 drivers/virt/Makefile                         |    2 +
 drivers/virt/nitro_enclaves/Kconfig           |   16 +
 drivers/virt/nitro_enclaves/Makefile          |   11 +
 drivers/virt/nitro_enclaves/ne_misc_dev.c     | 1385 +++++++++++++++++
 drivers/virt/nitro_enclaves/ne_misc_dev.h     |  106 ++
 drivers/virt/nitro_enclaves/ne_pci_dev.c      |  565 +++++++
 drivers/virt/nitro_enclaves/ne_pci_dev.h      |  265 ++++
 include/linux/nitro_enclaves.h                |   11 +
 include/uapi/linux/nitro_enclaves.h           |  244 +++
 samples/nitro_enclaves/.gitignore             |    2 +
 samples/nitro_enclaves/Makefile               |   16 +
 samples/nitro_enclaves/ne_ioctl_sample.c      |  628 ++++++++
 16 files changed, 3357 insertions(+), 1 deletion(-)
 create mode 100644 Documentation/nitro_enclaves/ne_overview.rst
 create mode 100644 drivers/virt/nitro_enclaves/Kconfig
 create mode 100644 drivers/virt/nitro_enclaves/Makefile
 create mode 100644 drivers/virt/nitro_enclaves/ne_misc_dev.c
 create mode 100644 drivers/virt/nitro_enclaves/ne_misc_dev.h
 create mode 100644 drivers/virt/nitro_enclaves/ne_pci_dev.c
 create mode 100644 drivers/virt/nitro_enclaves/ne_pci_dev.h
 create mode 100644 include/linux/nitro_enclaves.h
 create mode 100644 include/uapi/linux/nitro_enclaves.h
 create mode 100644 samples/nitro_enclaves/.gitignore
 create mode 100644 samples/nitro_enclaves/Makefile
 create mode 100644 samples/nitro_enclaves/ne_ioctl_sample.c
```
