#### [PATCH 04/35] docs: fix broken references for ReST files that moved around
##### From: Mauro Carvalho Chehab <mchehab+huawei@kernel.org>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Mauro Carvalho Chehab <mchehab+huawei@kernel.org>
X-Patchwork-Id: 11480407
Return-Path: <SRS0=FdSL=5Y=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id F2035112C
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed,  8 Apr 2020 15:47:07 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id C95752076D
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed,  8 Apr 2020 15:47:07 +0000 (UTC)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple; d=kernel.org;
	s=default; t=1586360827;
	bh=p4BaOts5XwS9tdFV4i/p0/J5e6kWOeDWMFxv85StaUU=;
	h=From:To:Cc:Subject:Date:In-Reply-To:References:List-ID:From;
	b=yXyMdwQjRwdGWS45yr2JxfinfGHSo4+PTxkbY6E6cB3l66ZOwpIA24N279O3MKAos
	 3TmCmdHMmtHVGF8ySZ3hai2p5WKkn7jJ0CUPB9fJPz/I5oecQufCyuvP1g8KBJJWIb
	 jacCnLrZZ9JOeORy6ZCQvpTQu/9r3ydqpWukLfSk=
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729707AbgDHPqd (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 8 Apr 2020 11:46:33 -0400
Received: from mail.kernel.org ([198.145.29.99]:49016 "EHLO mail.kernel.org"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1729589AbgDHPqc (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 8 Apr 2020 11:46:32 -0400
Received: from mail.kernel.org (ip5f5ad4d8.dynamic.kabel-deutschland.de
 [95.90.212.216])
        (using TLSv1.2 with cipher ECDHE-RSA-AES256-GCM-SHA384 (256/256 bits))
        (No client certificate requested)
        by mail.kernel.org (Postfix) with ESMTPSA id 1778E20784;
        Wed,  8 Apr 2020 15:46:31 +0000 (UTC)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple; d=kernel.org;
        s=default; t=1586360791;
        bh=p4BaOts5XwS9tdFV4i/p0/J5e6kWOeDWMFxv85StaUU=;
        h=From:To:Cc:Subject:Date:In-Reply-To:References:From;
        b=NZ21Vyx8+OMKYPn8CBKZzq75zGPoZ3DMDP8oLRTpkpecR8WAQ2+J8Fj2VAHTR5wk0
         xDKmG5vsShl4z0Z80aO1JRL4hEypnfFvWF9tZ0gMaqVYbs4QpvzGLBsWeiPEMeQdvH
         pR/0VVfHJVOJNvrIxlVOVb9eI6+9VNUE+/BRTi8E=
Received: from mchehab by mail.kernel.org with local (Exim 4.92.3)
        (envelope-from <mchehab@kernel.org>)
        id 1jMCuL-000cAZ-6H; Wed, 08 Apr 2020 17:46:29 +0200
From: Mauro Carvalho Chehab <mchehab+huawei@kernel.org>
To: Linux Doc Mailing List <linux-doc@vger.kernel.org>
Cc: Mauro Carvalho Chehab <mchehab+huawei@kernel.org>,
        linux-kernel@vger.kernel.org, Jonathan Corbet <corbet@lwn.net>,
        Paolo Bonzini <pbonzini@redhat.com>,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>,
        Thomas Gleixner <tglx@linutronix.de>,
        Ingo Molnar <mingo@redhat.com>, Borislav Petkov <bp@alien8.de>,
        "H. Peter Anvin" <hpa@zytor.com>, x86@kernel.org,
        Corentin Labbe <clabbe.montjoie@gmail.com>,
        Herbert Xu <herbert@gondor.apana.org.au>,
        "David S. Miller" <davem@davemloft.net>,
        Maxime Ripard <mripard@kernel.org>,
        Chen-Yu Tsai <wens@csie.org>, kvm@vger.kernel.org,
        linux-crypto@vger.kernel.org, linux-arm-kernel@lists.infradead.org
Subject: [PATCH 04/35] docs: fix broken references for ReST files that moved
 around
Date: Wed,  8 Apr 2020 17:45:56 +0200
Message-Id: 
 <5beb8d40ae78e179ea5bafb38f0988c5f1a5fd18.1586359676.git.mchehab+huawei@kernel.org>
X-Mailer: git-send-email 2.25.2
In-Reply-To: <cover.1586359676.git.mchehab+huawei@kernel.org>
References: <cover.1586359676.git.mchehab+huawei@kernel.org>
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Some broken references happened due to shifting files around
and ReST renames. Those can't be auto-fixed by the script,
so let's fix them manually.

Signed-off-by: Mauro Carvalho Chehab <mchehab+huawei@kernel.org>
---
 Documentation/doc-guide/maintainer-profile.rst      | 2 +-
 Documentation/virt/kvm/mmu.rst                      | 2 +-
 Documentation/virt/kvm/review-checklist.rst         | 2 +-
 arch/x86/kvm/mmu/mmu.c                              | 2 +-
 drivers/crypto/allwinner/sun8i-ce/sun8i-ce-cipher.c | 2 +-
 drivers/crypto/allwinner/sun8i-ce/sun8i-ce-core.c   | 2 +-
 drivers/crypto/allwinner/sun8i-ss/sun8i-ss-cipher.c | 2 +-
 drivers/crypto/allwinner/sun8i-ss/sun8i-ss-core.c   | 2 +-
 drivers/media/v4l2-core/v4l2-fwnode.c               | 2 +-
 include/uapi/linux/kvm.h                            | 4 ++--
 tools/include/uapi/linux/kvm.h                      | 4 ++--
 11 files changed, 13 insertions(+), 13 deletions(-)

```
#### [PATCH 1/2] KVM: Check validity of resolved slot when searching memslots
##### From: Sean Christopherson <sean.j.christopherson@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Sean Christopherson <sean.j.christopherson@intel.com>
X-Patchwork-Id: 11479459
Return-Path: <SRS0=FdSL=5Y=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 4881B92C
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed,  8 Apr 2020 06:41:08 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 25FBD2072A
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed,  8 Apr 2020 06:41:08 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726605AbgDHGlB (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 8 Apr 2020 02:41:01 -0400
Received: from mga11.intel.com ([192.55.52.93]:58629 "EHLO mga11.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1725763AbgDHGlA (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 8 Apr 2020 02:41:00 -0400
IronPort-SDR: 
 hsczhdo64+ePuI3P9IvcPEUFAHM8AdfFwQcNPeyKNXKD96mw9Fo2SRih1kHhhuGxdU/+cuM9/o
 H5NatOmDDERA==
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from orsmga007.jf.intel.com ([10.7.209.58])
  by fmsmga102.fm.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 07 Apr 2020 23:41:00 -0700
IronPort-SDR: 
 kXTd4oDxUKWyEoclSVSNSkdaL7KhEVHfzJ6FUtRw0GL2tAO7pgYelG74re22M+/MIRlGlIw1Ha
 U+zWgrp/r1OQ==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.72,357,1580803200";
   d="scan'208";a="240207984"
Received: from sjchrist-coffee.jf.intel.com ([10.54.74.202])
  by orsmga007.jf.intel.com with ESMTP; 07 Apr 2020 23:40:59 -0700
From: Sean Christopherson <sean.j.christopherson@intel.com>
To: Christian Borntraeger <borntraeger@de.ibm.com>,
        Janosch Frank <frankja@linux.ibm.com>,
        Paolo Bonzini <pbonzini@redhat.com>
Cc: David Hildenbrand <david@redhat.com>,
        Cornelia Huck <cohuck@redhat.com>, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org,
        syzbot+d889b59b2bb87d4047a2@syzkaller.appspotmail.com
Subject: [PATCH 1/2] KVM: Check validity of resolved slot when searching
 memslots
Date: Tue,  7 Apr 2020 23:40:58 -0700
Message-Id: <20200408064059.8957-2-sean.j.christopherson@intel.com>
X-Mailer: git-send-email 2.24.1
In-Reply-To: <20200408064059.8957-1-sean.j.christopherson@intel.com>
References: <20200408064059.8957-1-sean.j.christopherson@intel.com>
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Check that the resolved slot (somewhat confusingly named 'start') is a
valid/allocated slot before doing the final comparison to see if the
specified gfn resides in the associated slot.  The resolved slot can be
invalid if the binary search loop terminated because the search index
was incremented beyond the number of used slots.

This bug has existed since the binary search algorithm was introduced,
but went unnoticed because KVM statically allocated memory for the max
number of slots, i.e. the access would only be truly out-of-bounds if
all possible slots were allocated and the specified gfn was less than
the base of the lowest memslot.  Commit 36947254e5f98 ("KVM: Dynamically
size memslot array based on number of used slots") eliminated the "all
possible slots allocated" condition and made the bug embarrasingly easy
to hit.

Fixes: 9c1a5d38780e6 ("kvm: optimize GFN to memslot lookup with large slots amount")
Reported-by: syzbot+d889b59b2bb87d4047a2@syzkaller.appspotmail.com
Cc: stable@vger.kernel.org
Signed-off-by: Sean Christopherson <sean.j.christopherson@intel.com>
Reviewed-by: Cornelia Huck <cohuck@redhat.com>
---
 include/linux/kvm_host.h | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
#### [PATCH] KVM: x86/pmu: Support full width counting
##### From: Like Xu <like.xu@linux.intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Like Xu <like.xu@linux.intel.com>
X-Patchwork-Id: 11480197
Return-Path: <SRS0=FdSL=5Y=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id E8AED912
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed,  8 Apr 2020 13:56:57 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id B5BAA20692
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed,  8 Apr 2020 13:56:57 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727226AbgDHN43 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 8 Apr 2020 09:56:29 -0400
Received: from mga12.intel.com ([192.55.52.136]:62331 "EHLO mga12.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726663AbgDHN43 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 8 Apr 2020 09:56:29 -0400
IronPort-SDR: 
 2dPekf3pj2q0oRwW18OJ941CZjHc/lmCDGCKs7YGDjveQteaQb3enmRC4UeC33S/M0NjG4LOHQ
 Y2TSekEZoe+A==
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from fmsmga008.fm.intel.com ([10.253.24.58])
  by fmsmga106.fm.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 08 Apr 2020 06:56:29 -0700
IronPort-SDR: 
 6T27AKxi9WqlYaZn+NUIyFxt0s1YdajtB3TlU333E1f8p+8NwQD2HREi3vlEwTCoIYInkl0giA
 FseFDgKw02+w==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.72,358,1580803200";
   d="scan'208";a="244043287"
Received: from sqa-gate.sh.intel.com (HELO clx-ap-likexu.tsp.org)
 ([10.239.48.212])
  by fmsmga008.fm.intel.com with ESMTP; 08 Apr 2020 06:56:26 -0700
From: Like Xu <like.xu@linux.intel.com>
To: Paolo Bonzini <pbonzini@redhat.com>,
        Andi Kleen <ak@linux.intel.com>
Cc: Sean Christopherson <sean.j.christopherson@intel.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org, Like Xu <like.xu@linux.intel.com>
Subject: [PATCH] KVM: x86/pmu: Support full width counting
Date: Wed,  8 Apr 2020 21:53:25 +0800
Message-Id: <20200408135325.3160-1-like.xu@linux.intel.com>
X-Mailer: git-send-email 2.21.1
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Intel CPUs have a new alternative MSR range (starting from MSR_IA32_PMC0)
for GP counters that allows writing the full counter width. Enable this
range from a new capability bit (IA32_PERF_CAPABILITIES.FW_WRITE[bit 13]).

The perf driver queries CPUID to get the counter width, and sign extends
the counter values as needed. The traditional MSRs always limit to 32bit,
even though the counter internally is larger (usually 48 bits).

When the new capability is set, use the alternative range which do not
have these restrictions. This lowers the overhead of perf stat slightly
because it has to do less interrupts to accumulate the counter value.

Signed-off-by: Like Xu <like.xu@linux.intel.com>
---
 arch/x86/include/asm/kvm_host.h |  1 +
 arch/x86/kvm/vmx/capabilities.h | 15 +++++++++++++
 arch/x86/kvm/vmx/pmu_intel.c    | 38 +++++++++++++++++++++++++++------
 arch/x86/kvm/vmx/vmx.c          |  2 ++
 4 files changed, 50 insertions(+), 6 deletions(-)

```
#### [RFC PATCH 01/26] x86/paravirt: Specify subsection in PVOP macros
##### From: Ankur Arora <ankur.a.arora@oracle.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Ankur Arora <ankur.a.arora@oracle.com>
X-Patchwork-Id: 11479357
Return-Path: <SRS0=FdSL=5Y=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 61D9F912
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed,  8 Apr 2020 05:06:42 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 36D5E20771
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed,  8 Apr 2020 05:06:42 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=oracle.com header.i=@oracle.com
 header.b="p4M4l8mn"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726690AbgDHFFe (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 8 Apr 2020 01:05:34 -0400
Received: from userp2130.oracle.com ([156.151.31.86]:52624 "EHLO
        userp2130.oracle.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726637AbgDHFFe (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 8 Apr 2020 01:05:34 -0400
Received: from pps.filterd (userp2130.oracle.com [127.0.0.1])
        by userp2130.oracle.com (8.16.0.42/8.16.0.42) with SMTP id
 03854BNo012923;
        Wed, 8 Apr 2020 05:04:59 GMT
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=oracle.com;
 h=from : to : cc :
 subject : date : message-id : in-reply-to : references : mime-version :
 content-transfer-encoding; s=corp-2020-01-29;
 bh=skSK5dc4HZd1ygvZWCZ0mvu5/IDpVFbzIohZL2fpedY=;
 b=p4M4l8mnkF/etgUggs6AvVrpqtHrBab+6kS2BRdp7uKb7mxGmfZxSjdhraVPNVIOBqW1
 9SsaF2ylBowJOGLHnPtacyQU8Iu1M2C729hNOxufFVU93m1m+cPlYGbixXwwcAptu91a
 Dn7Ljb7dgX5WW5iaPA9CEvwfhOV/51yb4VF9MJYDR7G5sIw8yzijv+pZP4rdMgdHm+uE
 Ul8vqHxMUpyE+BWirc2G54VFigebcGKqdiqjiSB/OQraTshP5IDeg1J9KANEDdF7e95c
 rQTAkrvuRgoaIPmCw1NiQKZoAdBT2OYIgd96D8d+7Iya26gRJrIFVYatZXQuwbpqUWnH dA==
Received: from aserp3030.oracle.com (aserp3030.oracle.com [141.146.126.71])
        by userp2130.oracle.com with ESMTP id 3091m390vy-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Wed, 08 Apr 2020 05:04:59 +0000
Received: from pps.filterd (aserp3030.oracle.com [127.0.0.1])
        by aserp3030.oracle.com (8.16.0.42/8.16.0.42) with SMTP id
 03852glC148201;
        Wed, 8 Apr 2020 05:04:58 GMT
Received: from userv0121.oracle.com (userv0121.oracle.com [156.151.31.72])
        by aserp3030.oracle.com with ESMTP id 3091kgj6ng-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Wed, 08 Apr 2020 05:04:58 +0000
Received: from abhmp0012.oracle.com (abhmp0012.oracle.com [141.146.116.18])
        by userv0121.oracle.com (8.14.4/8.13.8) with ESMTP id 03854tSP015092;
        Wed, 8 Apr 2020 05:04:56 GMT
Received: from monad.ca.oracle.com (/10.156.75.81)
        by default (Oracle Beehive Gateway v4.0)
        with ESMTP ; Tue, 07 Apr 2020 22:04:55 -0700
From: Ankur Arora <ankur.a.arora@oracle.com>
To: linux-kernel@vger.kernel.org, x86@kernel.org
Cc: peterz@infradead.org, hpa@zytor.com, jpoimboe@redhat.com,
        namit@vmware.com, mhiramat@kernel.org, jgross@suse.com,
        bp@alien8.de, vkuznets@redhat.com, pbonzini@redhat.com,
        boris.ostrovsky@oracle.com, mihai.carabas@oracle.com,
        kvm@vger.kernel.org, xen-devel@lists.xenproject.org,
        virtualization@lists.linux-foundation.org,
        Ankur Arora <ankur.a.arora@oracle.com>
Subject: [RFC PATCH 01/26] x86/paravirt: Specify subsection in PVOP macros
Date: Tue,  7 Apr 2020 22:02:58 -0700
Message-Id: <20200408050323.4237-2-ankur.a.arora@oracle.com>
X-Mailer: git-send-email 2.20.1
In-Reply-To: <20200408050323.4237-1-ankur.a.arora@oracle.com>
References: <20200408050323.4237-1-ankur.a.arora@oracle.com>
MIME-Version: 1.0
X-Proofpoint-Virus-Version: vendor=nai engine=6000 definitions=9584
 signatures=668685
X-Proofpoint-Spam-Details: rule=notspam policy=default score=0 mlxscore=0
 bulkscore=0 suspectscore=0
 spamscore=0 malwarescore=0 adultscore=0 phishscore=0 mlxlogscore=999
 classifier=spam adjust=0 reason=mlx scancount=1 engine=8.12.0-2003020000
 definitions=main-2004080037
X-Proofpoint-Virus-Version: vendor=nai engine=6000 definitions=9584
 signatures=668685
X-Proofpoint-Spam-Details: rule=notspam policy=default score=0 spamscore=0
 adultscore=0
 impostorscore=0 malwarescore=0 lowpriorityscore=0 mlxlogscore=999
 priorityscore=1501 clxscore=1015 bulkscore=0 phishscore=0 mlxscore=0
 suspectscore=0 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.12.0-2003020000 definitions=main-2004080037
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Allow PVOP macros to specify a subsection such that _paravirt_alt() can
optionally put sites in .parainstructions.*.

Signed-off-by: Ankur Arora <ankur.a.arora@oracle.com>
---
 arch/x86/include/asm/paravirt_types.h | 158 +++++++++++++++++---------
 1 file changed, 102 insertions(+), 56 deletions(-)

```
#### [PATCH v4 1/2] selftests: kvm: Add vm_get_fd() in kvm_util
##### From: Wainer dos Santos Moschetta <wainersm@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Wainer dos Santos Moschetta <wainersm@redhat.com>
X-Patchwork-Id: 11481019
Return-Path: <SRS0=FdSL=5Y=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 9A9C8112C
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed,  8 Apr 2020 22:08:40 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 765282078E
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed,  8 Apr 2020 22:08:40 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="hQ8jnXum"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726595AbgDHWIj (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 8 Apr 2020 18:08:39 -0400
Received: from us-smtp-2.mimecast.com ([205.139.110.61]:43339 "EHLO
        us-smtp-delivery-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S1726589AbgDHWIi (ORCPT
        <rfc822;kvm@vger.kernel.org>); Wed, 8 Apr 2020 18:08:38 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1586383717;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:in-reply-to:in-reply-to:references:references;
        bh=YBQ+zxeaLD0yw/RzmwmvvS9Gvxa0mxHzlEt+c4z9U6U=;
        b=hQ8jnXumJ6QOALq03bfUnFVS5Whnd0RqQJFY0Iih1xK1WHem74CuQ6D+O53cSmRRW0Oagn
        40Cs7A1Y6yNA/QAQ8QrFVmcZPExrpnvaJ5YNfoHGI7zSyOKK2Bn/Y/bWbWCh1ug7B6JUMT
        maFJbBIyOYYWCodoIcD2WCpsOo1jwrc=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-198-7EO6LfQqOSWiGnrI026uUQ-1; Wed, 08 Apr 2020 18:08:33 -0400
X-MC-Unique: 7EO6LfQqOSWiGnrI026uUQ-1
Received: from smtp.corp.redhat.com (int-mx01.intmail.prod.int.phx2.redhat.com
 [10.5.11.11])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id C490313FB;
        Wed,  8 Apr 2020 22:08:32 +0000 (UTC)
Received: from localhost.localdomain (ovpn-116-15.gru2.redhat.com
 [10.97.116.15])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 3FE88118F4A;
        Wed,  8 Apr 2020 22:08:26 +0000 (UTC)
From: Wainer dos Santos Moschetta <wainersm@redhat.com>
To: pbonzini@redhat.com, kvm@vger.kernel.org
Cc: drjones@redhat.com, david@redhat.com, linux-kernel@vger.kernel.org,
        linux-kselftest@vger.kernel.org
Subject: [PATCH v4 1/2] selftests: kvm: Add vm_get_fd() in kvm_util
Date: Wed,  8 Apr 2020 19:08:17 -0300
Message-Id: <20200408220818.4306-2-wainersm@redhat.com>
In-Reply-To: <20200408220818.4306-1-wainersm@redhat.com>
References: <20200408220818.4306-1-wainersm@redhat.com>
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.11
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Introduces the vm_get_fd() function in kvm_util which returns
the VM file descriptor.

Reviewed-by: Andrew Jones <drjones@redhat.com>
Signed-off-by: Wainer dos Santos Moschetta <wainersm@redhat.com>
---
 tools/testing/selftests/kvm/include/kvm_util.h | 1 +
 tools/testing/selftests/kvm/lib/kvm_util.c     | 5 +++++
 2 files changed, 6 insertions(+)

```
#### [PATCH v3 1/2] Documentation/driver-api/vfio-mediated-device.rst: update for aggregation support
##### From: Zhenyu Wang <zhenyuw@linux.intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Zhenyu Wang <zhenyuw@linux.intel.com>
X-Patchwork-Id: 11479441
Return-Path: <SRS0=FdSL=5Y=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 8175C112C
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed,  8 Apr 2020 05:58:31 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 60666206C0
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed,  8 Apr 2020 05:58:31 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726464AbgDHF63 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 8 Apr 2020 01:58:29 -0400
Received: from mga03.intel.com ([134.134.136.65]:43466 "EHLO mga03.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1725932AbgDHF63 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 8 Apr 2020 01:58:29 -0400
IronPort-SDR: 
 eQMh8CX4I8bzM8le9XYsNkJkduEnQQ1bIlcduR6phn32t1pprFmG8cBVFIn8ubw9Dx0o5Qjbir
 2sLWDlJ5t0BQ==
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from fmsmga002.fm.intel.com ([10.253.24.26])
  by orsmga103.jf.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 07 Apr 2020 22:58:28 -0700
IronPort-SDR: 
 nigPgWNZ4HNvtX3+5bC0TRUwPQav0GP4vhUeO2QxmnWEU0zKC8QvU3RwW2r3XytmLQrmZZvWtE
 cG7gw2j3TKXQ==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.72,357,1580803200";
   d="scan'208";a="286448333"
Received: from jianli5-mobl2.ccr.corp.intel.com (HELO
 dell-xps.ccr.corp.intel.com) ([10.249.173.130])
  by fmsmga002.fm.intel.com with ESMTP; 07 Apr 2020 22:58:27 -0700
From: Zhenyu Wang <zhenyuw@linux.intel.com>
To: alex.williamson@redhat.com
Cc: kevin.tian@intel.com, intel-gvt-dev@lists.freedesktop.org,
        kvm@vger.kernel.org, "Jiang, Dave" <dave.jiang@intel.com>
Subject: [PATCH v3 1/2] Documentation/driver-api/vfio-mediated-device.rst:
 update for aggregation support
Date: Wed,  8 Apr 2020 13:58:23 +0800
Message-Id: <20200408055824.2378-2-zhenyuw@linux.intel.com>
X-Mailer: git-send-email 2.25.1
In-Reply-To: <20200326054136.2543-1-zhenyuw@linux.intel.com>
References: <20200326054136.2543-1-zhenyuw@linux.intel.com>
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Update doc for mdev aggregation support. Describe mdev generic
parameter directory under mdev device directory.

Cc: Kevin Tian <kevin.tian@intel.com>
Cc: "Jiang, Dave" <dave.jiang@intel.com>
Signed-off-by: Zhenyu Wang <zhenyuw@linux.intel.com>
---
 .../driver-api/vfio-mediated-device.rst       | 22 +++++++++++++++++++
 1 file changed, 22 insertions(+)

```
#### [PATCH] vfio: avoid possible overflow in vfio_iommu_type1_pin_pages
##### From: Yan Zhao <yan.y.zhao@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Yan Zhao <yan.y.zhao@intel.com>
X-Patchwork-Id: 11479529
Return-Path: <SRS0=FdSL=5Y=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 95FFF15AB
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed,  8 Apr 2020 07:22:23 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 7D5BD2072A
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed,  8 Apr 2020 07:22:23 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726726AbgDHHWU (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 8 Apr 2020 03:22:20 -0400
Received: from mga02.intel.com ([134.134.136.20]:27549 "EHLO mga02.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1725932AbgDHHWU (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 8 Apr 2020 03:22:20 -0400
IronPort-SDR: 
 H9c326LfmrsaQTligFC2SotXFt32A0INV7w8DU2VynfiKmn4yK5d8eEWHvNHRNoKi68/PY7S3c
 3cg0LJPNDrNg==
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from orsmga004.jf.intel.com ([10.7.209.38])
  by orsmga101.jf.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 08 Apr 2020 00:22:19 -0700
IronPort-SDR: 
 gKnX5qseXmV3WmfIxHpupqPyGRM0UIDAt4K/RoSyYkt0udANyhV+gjvDAzcwGW9P0zbDktqEwH
 fQFaN9wLCMHQ==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.72,357,1580803200";
   d="scan'208";a="398121373"
Received: from joy-optiplex-7040.sh.intel.com ([10.239.13.16])
  by orsmga004.jf.intel.com with ESMTP; 08 Apr 2020 00:22:17 -0700
From: Yan Zhao <yan.y.zhao@intel.com>
To: alex.williamson@redhat.com, cohuck@redhat.com
Cc: kvm@vger.kernel.org, linux-kernel@vger.kernel.org,
        Yan Zhao <yan.y.zhao@intel.com>
Subject: [PATCH] vfio: avoid possible overflow in vfio_iommu_type1_pin_pages
Date: Wed,  8 Apr 2020 03:12:34 -0400
Message-Id: <20200408071234.25702-1-yan.y.zhao@intel.com>
X-Mailer: git-send-email 2.17.1
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

add parentheses to avoid possible vaddr overflow.

Fixes: a54eb55045ae ("vfio iommu type1: Add support for mediated devices")
Signed-off-by: Yan Zhao <yan.y.zhao@intel.com>
---
 drivers/vfio/vfio_iommu_type1.c | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
#### [PATCH] vfio: checking of validity of user vaddr in vfio_dma_rw
##### From: Yan Zhao <yan.y.zhao@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Yan Zhao <yan.y.zhao@intel.com>
X-Patchwork-Id: 11479523
Return-Path: <SRS0=FdSL=5Y=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id CC35214B4
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed,  8 Apr 2020 07:21:37 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id B480F2072A
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed,  8 Apr 2020 07:21:37 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726650AbgDHHVd (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 8 Apr 2020 03:21:33 -0400
Received: from mga01.intel.com ([192.55.52.88]:42828 "EHLO mga01.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1725763AbgDHHVd (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 8 Apr 2020 03:21:33 -0400
IronPort-SDR: 
 9qIDK1VANMo4fNW2iwJjwnAkj1z7jP6FOBMh6kWDgDY4jjZcy8eTKgE6LkMWXLKODx8tXrlzYz
 r0FJbG0w8c6Q==
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from orsmga006.jf.intel.com ([10.7.209.51])
  by fmsmga101.fm.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 08 Apr 2020 00:21:32 -0700
IronPort-SDR: 
 8DU0rS43X0+q9dh1hmnTkwwNvy5G+AJbotvfyHkVhAtAtrkAB6SWCe/akFWTK0FC7Hnr2U7p4W
 lJW241t73Enw==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.72,357,1580803200";
   d="scan'208";a="254713673"
Received: from joy-optiplex-7040.sh.intel.com ([10.239.13.16])
  by orsmga006.jf.intel.com with ESMTP; 08 Apr 2020 00:21:30 -0700
From: Yan Zhao <yan.y.zhao@intel.com>
To: alex.williamson@redhat.com, cohuck@redhat.com
Cc: kvm@vger.kernel.org, linux-kernel@vger.kernel.org,
        Yan Zhao <yan.y.zhao@intel.com>,
        Kees Cook <keescook@chromium.org>
Subject: [PATCH] vfio: checking of validity of user vaddr in vfio_dma_rw
Date: Wed,  8 Apr 2020 03:11:21 -0400
Message-Id: <20200408071121.25645-1-yan.y.zhao@intel.com>
X-Mailer: git-send-email 2.17.1
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

instead of calling __copy_to/from_user(), use copy_to_from_user() to
ensure vaddr range is a valid user address range before accessing them.

Cc: Kees Cook <keescook@chromium.org>

Fixes: 8d46c0cca5f4 ("vfio: introduce vfio_dma_rw to read/write a range of IOVAs")
Signed-off-by: Yan Zhao <yan.y.zhao@intel.com>
Reported-by: Kees Cook <keescook@chromium.org>
Reviewed-by: Kees Cook <keescook@chromium.org>
---
 drivers/vfio/vfio_iommu_type1.c | 4 ++--
 1 file changed, 2 insertions(+), 2 deletions(-)

```
#### 
##### 

```c
```
#### [PATCH v3 2/2] drm/i915/gvt: mdev aggregation type
##### From: Zhenyu Wang <zhenyuw@linux.intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Zhenyu Wang <zhenyuw@linux.intel.com>
X-Patchwork-Id: 11479445
Return-Path: <SRS0=FdSL=5Y=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 7EE7D112C
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed,  8 Apr 2020 05:58:35 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 49749206C0
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed,  8 Apr 2020 05:58:35 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726575AbgDHF6c (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 8 Apr 2020 01:58:32 -0400
Received: from mga03.intel.com ([134.134.136.65]:43466 "EHLO mga03.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726513AbgDHF6b (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 8 Apr 2020 01:58:31 -0400
IronPort-SDR: 
 jdG4erxKap0/unbRcofbkhd9CMkcwtdgvC2ysKWEzDSEv33or7/LDvUbRXi/Tlw5UywXB7Y0OM
 g1D4iGDFWBkw==
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from fmsmga002.fm.intel.com ([10.253.24.26])
  by orsmga103.jf.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 07 Apr 2020 22:58:31 -0700
IronPort-SDR: 
 9yABhBLRLyBVhcGv+fb+/ScrteIqQiFUy4lX1b1ZpxFm08fu1G9ZNjjjuWWLk/fIXDkLsR5//z
 N0sEfFw4hzzg==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.72,357,1580803200";
   d="scan'208";a="286448346"
Received: from jianli5-mobl2.ccr.corp.intel.com (HELO
 dell-xps.ccr.corp.intel.com) ([10.249.173.130])
  by fmsmga002.fm.intel.com with ESMTP; 07 Apr 2020 22:58:29 -0700
From: Zhenyu Wang <zhenyuw@linux.intel.com>
To: alex.williamson@redhat.com
Cc: kevin.tian@intel.com, intel-gvt-dev@lists.freedesktop.org,
        kvm@vger.kernel.org, "Jiang, Dave" <dave.jiang@intel.com>,
        "Yuan, Hang" <hang.yuan@intel.com>
Subject: [PATCH v3 2/2] drm/i915/gvt: mdev aggregation type
Date: Wed,  8 Apr 2020 13:58:24 +0800
Message-Id: <20200408055824.2378-3-zhenyuw@linux.intel.com>
X-Mailer: git-send-email 2.25.1
In-Reply-To: <20200326054136.2543-1-zhenyuw@linux.intel.com>
References: <20200326054136.2543-1-zhenyuw@linux.intel.com>
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

To increase the flexibility for resource allocation on mdev types,
this trys to add aggregation attribute for mdev type that can
aggregate gfx memory resources in GVT case.

Use sysfs method for this attribute, the most difference for GVT is
that the gfx resource allocation will be delayed until mdev open
instead of mdev create to allow aggregation setting before VM
start. Resource accounting would be handled before mdev open.

"max_aggregation" would show maxium instances for aggregation on
target vGPU instance. "aggregated_instances" shows current count of
aggregated instances. "max_aggregation" is read-only and user sets
needed account by write to "aggregated_instances".

Cc: Kevin Tian <kevin.tian@intel.com>
Cc: "Jiang, Dave" <dave.jiang@intel.com>
Cc: "Yuan, Hang" <hang.yuan@intel.com>
Signed-off-by: Zhenyu Wang <zhenyuw@linux.intel.com>
---
 drivers/gpu/drm/i915/gvt/aperture_gm.c |  44 +++++--
 drivers/gpu/drm/i915/gvt/gtt.c         |   9 +-
 drivers/gpu/drm/i915/gvt/gvt.c         |   7 +-
 drivers/gpu/drm/i915/gvt/gvt.h         |  42 ++++--
 drivers/gpu/drm/i915/gvt/kvmgt.c       | 115 ++++++++++++++++-
 drivers/gpu/drm/i915/gvt/vgpu.c        | 172 +++++++++++++++++--------
 6 files changed, 295 insertions(+), 94 deletions(-)

```
