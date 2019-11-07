#### [PATCH v6 1/9] Documentation: Introduce EPT based Subpage Protection and related ioctls
##### From: Yang Weijiang <weijiang.yang@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Yang Weijiang <weijiang.yang@intel.com>
X-Patchwork-Id: 11229597
Return-Path: <SRS0=/jDW=Y6=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id C30D116B1
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed,  6 Nov 2019 07:43:26 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 91044217F5
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed,  6 Nov 2019 07:43:26 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1731299AbfKFHmo (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 6 Nov 2019 02:42:44 -0500
Received: from mga06.intel.com ([134.134.136.31]:15128 "EHLO mga06.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726772AbfKFHmn (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 6 Nov 2019 02:42:43 -0500
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from fmsmga002.fm.intel.com ([10.253.24.26])
  by orsmga104.jf.intel.com with ESMTP/TLS/DHE-RSA-AES256-GCM-SHA384;
 05 Nov 2019 23:42:43 -0800
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.68,274,1569308400";
   d="scan'208";a="232770685"
Received: from unknown (HELO local-michael-cet-test.sh.intel.com)
 ([10.239.159.128])
  by fmsmga002.fm.intel.com with ESMTP; 05 Nov 2019 23:42:41 -0800
From: Yang Weijiang <weijiang.yang@intel.com>
To: kvm@vger.kernel.org, linux-kernel@vger.kernel.org,
        pbonzini@redhat.com, jmattson@google.com,
        sean.j.christopherson@intel.com
Cc: yu.c.zhang@linux.intel.com, alazar@bitdefender.com,
        edwin.zhai@intel.com, Yang Weijiang <weijiang.yang@intel.com>
Subject: [PATCH v6 1/9] Documentation: Introduce EPT based Subpage Protection
 and related ioctls
Date: Wed,  6 Nov 2019 15:44:56 +0800
Message-Id: <20191106074504.14858-2-weijiang.yang@intel.com>
X-Mailer: git-send-email 2.17.2
In-Reply-To: <20191106074504.14858-1-weijiang.yang@intel.com>
References: <20191106074504.14858-1-weijiang.yang@intel.com>
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Co-developed-by: yi.z.zhang@linux.intel.com
Signed-off-by: yi.z.zhang@linux.intel.com
Signed-off-by: Yang Weijiang <weijiang.yang@intel.com>
---
 Documentation/virt/kvm/api.txt        |  46 +++++++
 Documentation/virtual/kvm/spp_kvm.txt | 180 ++++++++++++++++++++++++++
 2 files changed, 226 insertions(+)
 create mode 100644 Documentation/virtual/kvm/spp_kvm.txt

```
#### [Patch v1 1/2] KVM: remember position in kvm->vcpus array
##### From: Nitesh Narayan Lal <nitesh@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 8bit
X-Patchwork-Submitter: Nitesh Narayan Lal <nitesh@redhat.com>
X-Patchwork-Id: 11230343
Return-Path: <SRS0=/jDW=Y6=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id D697614E5
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed,  6 Nov 2019 13:37:07 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id B12472077C
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed,  6 Nov 2019 13:37:07 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="LarL3aVK"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1730685AbfKFNhG (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 6 Nov 2019 08:37:06 -0500
Received: from us-smtp-delivery-1.mimecast.com ([207.211.31.120]:29449 "EHLO
        us-smtp-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org
        with ESMTP id S1726673AbfKFNhF (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 6 Nov 2019 08:37:05 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1573047424;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:mime-version:mime-version:content-type:content-type:
         content-transfer-encoding:content-transfer-encoding:
         in-reply-to:in-reply-to:references:references;
        bh=M+2VUgyVn+wHIDKfhlYmKGK3URA7JW2uAVD8h9KQKwk=;
        b=LarL3aVKa3Em8JDoNT+nojsJ7FwToQHmwYwLMKNJs2CQThmpxNQtB+B0LK1SAdsVNsA7EY
        qlcaOk19GxSyDPsMc5IlyZCDZVXfHWLb/hKEupYvwFoyI4RDeyR/xU/bPKggavIaktBv51
        FcUtG035YFQ7SQZyDbmfvauprIy3iaQ=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-323-HRZ95NeXPB2DREV1Odzerw-1; Wed, 06 Nov 2019 08:37:01 -0500
Received: from smtp.corp.redhat.com (int-mx04.intmail.prod.int.phx2.redhat.com
 [10.5.11.14])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 3695C1800D6B;
        Wed,  6 Nov 2019 13:37:00 +0000 (UTC)
Received: from virtlab512.virt.lab.eng.bos.redhat.com
 (virtlab512.virt.lab.eng.bos.redhat.com [10.19.152.206])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 509C15DA70;
        Wed,  6 Nov 2019 13:36:58 +0000 (UTC)
From: Nitesh Narayan Lal <nitesh@redhat.com>
To: kvm@vger.kernel.org, linux-kernel@vger.kernel.org,
        pbonzini@redhat.com, mtosatti@redhat.com, rkrcmar@redhat.com,
        vkuznets@redhat.com, sean.j.christopherson@intel.com,
        wanpengli@tencent.com, jmattson@google.com, joro@8bytes.org
Subject: [Patch v1 1/2] KVM: remember position in kvm->vcpus array
Date: Wed,  6 Nov 2019 08:36:37 -0500
Message-Id: <1573047398-7665-2-git-send-email-nitesh@redhat.com>
In-Reply-To: <1573047398-7665-1-git-send-email-nitesh@redhat.com>
References: <1573047398-7665-1-git-send-email-nitesh@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.14
X-MC-Unique: HRZ95NeXPB2DREV1Odzerw-1
X-Mimecast-Spam-Score: 0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Radim Krčmář <rkrcmar@redhat.com>

Fetching an index for any vcpu in kvm->vcpus array by traversing
the entire array everytime is costly.
This patch remembers the position of each vcpu in kvm->vcpus array
by storing it in vcpus_idx under kvm_vcpu structure.

Signed-off-by: Radim Krčmář <rkrcmar@redhat.com>
Signed-off-by: Nitesh Narayan Lal <nitesh@redhat.com>
---
 include/linux/kvm_host.h | 11 +++--------
 virt/kvm/kvm_main.c      |  5 ++++-
 2 files changed, 7 insertions(+), 9 deletions(-)

```
#### [PATCH] kvm: Fix NULL dereference doing kvm_create_vm()
##### From: Dan Carpenter <dan.carpenter@oracle.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Dan Carpenter <dan.carpenter@oracle.com>
X-Patchwork-Id: 11229625
Return-Path: <SRS0=/jDW=Y6=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 3B4E81575
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed,  6 Nov 2019 08:27:05 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 1693A207FA
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed,  6 Nov 2019 08:27:05 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=oracle.com header.i=@oracle.com
 header.b="RhHmxNxy"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1730256AbfKFI1E (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 6 Nov 2019 03:27:04 -0500
Received: from userp2120.oracle.com ([156.151.31.85]:59064 "EHLO
        userp2120.oracle.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1729951AbfKFI1D (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 6 Nov 2019 03:27:03 -0500
Received: from pps.filterd (userp2120.oracle.com [127.0.0.1])
        by userp2120.oracle.com (8.16.0.27/8.16.0.27) with SMTP id
 xA68O1Ia053343;
        Wed, 6 Nov 2019 08:26:46 GMT
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=oracle.com;
 h=date : from : to : cc
 : subject : message-id : mime-version : content-type; s=corp-2019-08-05;
 bh=GFk4Eu9gAUGOFn6+W8/fSbeHy1Ds/V3T6NhIdP6+YpE=;
 b=RhHmxNxy+8XGCiW2QN8CyYWSoumDNQknM5k7OEl6k5P/VqGVYHmQ3X9kWTAQhvJ4IFUk
 0C7O30SzrH0kU5FmHLBkMOUnQrDvZhSoDqeQEXodIEEc7NCezUKFgvEsiz3/whrwoZqN
 rA/j4ZAJkJCWWpFGCBlwcVbWS832+YaqAKkaDDdElU3fvlfdWxfStMu0JqytaY+4R3wb
 2hjbxywlVEEFugssX1FTCQxlehK7mQyi0i1bOcfG55HkRLzsre8E825UzVK4LGxpsWw5
 DCdx34OV/9CkkTVQr6TguSViytC5Ve9O3y4WX3Lh2mROM7DDSdl6eqZlWaJgiMlKy/sl gA==
Received: from userp3030.oracle.com (userp3030.oracle.com [156.151.31.80])
        by userp2120.oracle.com with ESMTP id 2w12erc2kc-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Wed, 06 Nov 2019 08:26:46 +0000
Received: from pps.filterd (userp3030.oracle.com [127.0.0.1])
        by userp3030.oracle.com (8.16.0.27/8.16.0.27) with SMTP id
 xA68NSwK058423;
        Wed, 6 Nov 2019 08:26:46 GMT
Received: from aserv0122.oracle.com (aserv0122.oracle.com [141.146.126.236])
        by userp3030.oracle.com with ESMTP id 2w333wvb2h-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Wed, 06 Nov 2019 08:26:45 +0000
Received: from abhmp0020.oracle.com (abhmp0020.oracle.com [141.146.116.26])
        by aserv0122.oracle.com (8.14.4/8.14.4) with ESMTP id xA68QgTh013138;
        Wed, 6 Nov 2019 08:26:42 GMT
Received: from mwanda (/41.57.98.10)
        by default (Oracle Beehive Gateway v4.0)
        with ESMTP ; Wed, 06 Nov 2019 00:26:42 -0800
Date: Wed, 6 Nov 2019 11:26:36 +0300
From: Dan Carpenter <dan.carpenter@oracle.com>
To: Paolo Bonzini <pbonzini@redhat.com>,
        Jim Mattson <jmattson@google.com>
Cc: Radim =?utf-8?b?S3LEjW3DocWZ?= <rkrcmar@redhat.com>,
 Junaid Shahid <junaids@google.com>, kvm@vger.kernel.org,
 kernel-janitors@vger.kernel.org
Subject: [PATCH] kvm: Fix NULL dereference doing kvm_create_vm()
Message-ID: <20191106082636.GB31923@mwanda>
MIME-Version: 1.0
Content-Disposition: inline
X-Mailer: git-send-email haha only kidding
User-Agent: Mutt/1.10.1 (2018-07-13)
X-Proofpoint-Virus-Version: vendor=nai engine=6000 definitions=9432
 signatures=668685
X-Proofpoint-Spam-Details: rule=notspam policy=default score=0 suspectscore=0
 malwarescore=0
 phishscore=0 bulkscore=0 spamscore=0 mlxscore=0 mlxlogscore=999
 adultscore=0 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.0.1-1908290000 definitions=main-1911060088
X-Proofpoint-Virus-Version: vendor=nai engine=6000 definitions=9432
 signatures=668685
X-Proofpoint-Spam-Details: rule=notspam policy=default score=0
 priorityscore=1501 malwarescore=0
 suspectscore=0 phishscore=0 bulkscore=0 spamscore=0 clxscore=1011
 lowpriorityscore=0 mlxscore=0 impostorscore=0 mlxlogscore=999 adultscore=0
 classifier=spam adjust=0 reason=mlx scancount=1 engine=8.0.1-1908290000
 definitions=main-1911060088
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

If init_srcu_struct() or init_srcu_struct() fails then this function
returns ERR_PTR(0) which is NULL.  It leads to a NULL dereference in the
caller.

Fixes: 9121923c457d ("kvm: Allocate memslots and buses before calling kvm_arch_init_vm")
Signed-off-by: Dan Carpenter <dan.carpenter@oracle.com>
---
 virt/kvm/kvm_main.c | 1 +
 1 file changed, 1 insertion(+)

```
#### [PATCH 1/2] KVM: MMU: Do not treat ZONE_DEVICE pages as being reserved
##### From: Sean Christopherson <sean.j.christopherson@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Sean Christopherson <sean.j.christopherson@intel.com>
X-Patchwork-Id: 11230757
Return-Path: <SRS0=/jDW=Y6=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 202EB1709
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed,  6 Nov 2019 17:07:34 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 07FA421848
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed,  6 Nov 2019 17:07:34 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1732296AbfKFRHa (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 6 Nov 2019 12:07:30 -0500
Received: from mga06.intel.com ([134.134.136.31]:58093 "EHLO mga06.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1732280AbfKFRHa (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 6 Nov 2019 12:07:30 -0500
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from orsmga007.jf.intel.com ([10.7.209.58])
  by orsmga104.jf.intel.com with ESMTP/TLS/DHE-RSA-AES256-GCM-SHA384;
 06 Nov 2019 09:07:28 -0800
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.68,275,1569308400";
   d="scan'208";a="192528000"
Received: from sjchrist-coffee.jf.intel.com ([10.54.74.41])
  by orsmga007.jf.intel.com with ESMTP; 06 Nov 2019 09:07:28 -0800
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
Subject: [PATCH 1/2] KVM: MMU: Do not treat ZONE_DEVICE pages as being
 reserved
Date: Wed,  6 Nov 2019 09:07:26 -0800
Message-Id: <20191106170727.14457-2-sean.j.christopherson@intel.com>
X-Mailer: git-send-email 2.24.0
In-Reply-To: <20191106170727.14457-1-sean.j.christopherson@intel.com>
References: <20191106170727.14457-1-sean.j.christopherson@intel.com>
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Explicitly exempt ZONE_DEVICE pages from kvm_is_reserved_pfn() and
instead manually handle ZONE_DEVICE on a case-by-case basis.  For things
like page refcounts, KVM needs to treat ZONE_DEVICE pages like normal
pages, e.g. put pages grabbed via gup().  But KVM needs special handling
in other flows where ZONE_DEVICE pages lack the underlying machinery,
e.g. when setting accessed/dirty bits and shifting refcounts for
transparent huge pages.

This fixes a hang reported by Adam Borowski[*] in dev_pagemap_cleanup()
when running a KVM guest backed with /dev/dax memory, as KVM straight up
doesn't put any references to ZONE_DEVICE pages acquired by gup().

[*] http://lkml.kernel.org/r/20190919115547.GA17963@angband.pl

Reported-by: Adam Borowski <kilobyte@angband.pl>
Debugged-by: David Hildenbrand <david@redhat.com>
Cc: Dan Williams <dan.j.williams@intel.com>
Cc: stable@vger.kernel.org
Signed-off-by: Sean Christopherson <sean.j.christopherson@intel.com>
---
 arch/x86/kvm/mmu.c       |  8 ++++----
 include/linux/kvm_host.h |  1 +
 virt/kvm/kvm_main.c      | 19 +++++++++++++++----
 3 files changed, 20 insertions(+), 8 deletions(-)

```
#### [PATCH v1 1/3] KVM: VMX: Consider PID.PIR to determine if vCPU has pending interrupts
##### From: Joao Martins <joao.m.martins@oracle.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Joao Martins <joao.m.martins@oracle.com>
X-Patchwork-Id: 11230807
Return-Path: <SRS0=/jDW=Y6=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 2055214E5
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed,  6 Nov 2019 18:00:14 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id F1FDD217F4
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed,  6 Nov 2019 18:00:13 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=oracle.com header.i=@oracle.com
 header.b="EnvL+1BB"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1732499AbfKFSAK (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 6 Nov 2019 13:00:10 -0500
Received: from userp2120.oracle.com ([156.151.31.85]:38278 "EHLO
        userp2120.oracle.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1732176AbfKFSAK (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 6 Nov 2019 13:00:10 -0500
Received: from pps.filterd (userp2120.oracle.com [127.0.0.1])
        by userp2120.oracle.com (8.16.0.27/8.16.0.27) with SMTP id
 xA6HsOlM184712;
        Wed, 6 Nov 2019 17:58:29 GMT
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=oracle.com;
 h=from : to : cc :
 subject : date : message-id : in-reply-to : references : mime-version :
 content-type : content-transfer-encoding; s=corp-2019-08-05;
 bh=BWj5wteifYX6HnPR/tFjqG4VivjyAPJWMRU45ipFAE0=;
 b=EnvL+1BBy2GqhrtxpLJyTvmqK8sGYPQIM9ePxq8qxdSq9ZSnFr8ql1L0WCVDcL1ebG+n
 vkbdllI9vQYz56YirT8HXYy/xXw7nsJxcgjOFjDc0C7ALJQYSUrFDfkMh7yuJPPVV38H
 4CXA5nid2LL5zrmZhjgT7GYP8zYZ3VTgqQX5NBGSgzLshYNpczRCVLaqrHxmeVBvPlp/
 Dsfo434ULF/zg/ln1QhzqKsdp70m1eYgkrvIqm/E+gTZFGK1xHU0nan3Ull2Zb0Kqq23
 5Egc6tVFCqotX/v32fIYSzDr+NAAheIunvQlBRQbffpA7spQq1R3L7+2mDuW4jUuR3tc 4g==
Received: from aserp3020.oracle.com (aserp3020.oracle.com [141.146.126.70])
        by userp2120.oracle.com with ESMTP id 2w41w0rmba-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Wed, 06 Nov 2019 17:58:29 +0000
Received: from pps.filterd (aserp3020.oracle.com [127.0.0.1])
        by aserp3020.oracle.com (8.16.0.27/8.16.0.27) with SMTP id
 xA6HrmXl143146;
        Wed, 6 Nov 2019 17:56:28 GMT
Received: from userv0122.oracle.com (userv0122.oracle.com [156.151.31.75])
        by aserp3020.oracle.com with ESMTP id 2w41wds1by-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Wed, 06 Nov 2019 17:56:28 +0000
Received: from abhmp0012.oracle.com (abhmp0012.oracle.com [141.146.116.18])
        by userv0122.oracle.com (8.14.4/8.14.4) with ESMTP id xA6HuRZF003895;
        Wed, 6 Nov 2019 17:56:27 GMT
Received: from paddy.uk.oracle.com (/10.175.178.239)
        by default (Oracle Beehive Gateway v4.0)
        with ESMTP ; Wed, 06 Nov 2019 09:56:26 -0800
From: Joao Martins <joao.m.martins@oracle.com>
To: kvm@vger.kernel.org
Cc: Joao Martins <joao.m.martins@oracle.com>, linux-kernel@vger.kernel.org,
 Paolo Bonzini <pbonzini@redhat.com>,
 =?utf-8?b?UmFkaW0gS3LEjW3DocWZ?= <rkrcmar@redhat.com>,
 Sean Christopherson <sean.j.christopherson@intel.com>,
 Vitaly Kuznetsov <vkuznets@redhat.com>, Wanpeng Li <wanpengli@tencent.com>,
 Jim Mattson <jmattson@google.com>, Joerg Roedel <joro@8bytes.org>,
 Liran Alon <liran.alon@oracle.com>, Jag Raman <jag.raman@oracle.com>
Subject: [PATCH v1 1/3] KVM: VMX: Consider PID.PIR to determine if vCPU has
 pending interrupts
Date: Wed,  6 Nov 2019 17:56:00 +0000
Message-Id: <20191106175602.4515-2-joao.m.martins@oracle.com>
X-Mailer: git-send-email 2.11.0
In-Reply-To: <20191106175602.4515-1-joao.m.martins@oracle.com>
References: <20191106175602.4515-1-joao.m.martins@oracle.com>
MIME-Version: 1.0
X-Proofpoint-Virus-Version: vendor=nai engine=6000 definitions=9433
 signatures=668685
X-Proofpoint-Spam-Details: rule=notspam policy=default score=0 suspectscore=1
 malwarescore=0
 phishscore=0 bulkscore=0 spamscore=0 mlxscore=0 mlxlogscore=881
 adultscore=0 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.0.1-1910280000 definitions=main-1911060173
X-Proofpoint-Virus-Version: vendor=nai engine=6000 definitions=9433
 signatures=668685
X-Proofpoint-Spam-Details: rule=notspam policy=default score=0
 priorityscore=1501 malwarescore=0
 suspectscore=1 phishscore=0 bulkscore=0 spamscore=0 clxscore=1015
 lowpriorityscore=0 mlxscore=0 impostorscore=0 mlxlogscore=959 adultscore=0
 classifier=spam adjust=0 reason=mlx scancount=1 engine=8.0.1-1910280000
 definitions=main-1911060174
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Commit 17e433b54393 ("KVM: Fix leak vCPU's VMCS value into other pCPU")
introduced vmx_dy_apicv_has_pending_interrupt() in order to determine
if a vCPU have a pending posted interrupt. This routine is used by
kvm_vcpu_on_spin() when searching for a a new runnable vCPU to schedule
on pCPU instead of a vCPU doing busy loop.

vmx_dy_apicv_has_pending_interrupt() determines if a
vCPU has a pending posted interrupt solely based on PID.ON. However,
when a vCPU is preempted, vmx_vcpu_pi_put() sets PID.SN which cause
raised posted interrupts to only set bit in PID.PIR without setting
PID.ON (and without sending notification vector), as depicted in VT-d
manual section 5.2.3 "Interrupt-Posting Hardware Operation".

Therefore, checking PID.ON is insufficient to determine if a vCPU has
pending posted interrupts and instead we should also check if there is
some bit set on PID.PIR.

Fixes: 17e433b54393 ("KVM: Fix leak vCPU's VMCS value into other pCPU")
Signed-off-by: Joao Martins <joao.m.martins@oracle.com>
Signed-off-by: Liran Alon <liran.alon@oracle.com>
---
 arch/x86/kvm/vmx/vmx.c | 5 ++++-
 1 file changed, 4 insertions(+), 1 deletion(-)

```
#### [PATCH V9 1/6] mdev: class id support
##### From: Jason Wang <jasowang@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Jason Wang <jasowang@redhat.com>
X-Patchwork-Id: 11229527
Return-Path: <SRS0=/jDW=Y6=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id DFCD513BD
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed,  6 Nov 2019 07:09:02 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 9DD79217D7
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed,  6 Nov 2019 07:09:02 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="B04SKDM4"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1731387AbfKFHJA (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 6 Nov 2019 02:09:00 -0500
Received: from us-smtp-delivery-1.mimecast.com ([205.139.110.120]:56325 "EHLO
        us-smtp-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org
        with ESMTP id S1730844AbfKFHJA (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 6 Nov 2019 02:09:00 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1573024139;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:content-type:content-type:
         content-transfer-encoding:content-transfer-encoding:
         in-reply-to:in-reply-to:references:references;
        bh=ZjglcjJdfJ+rYNda606bWPhtmSxvctdSzvRhdUvjVro=;
        b=B04SKDM4ViRKTQF46J7vQYv2k96r1GpXgpLsCwVFlH+mR/+iHBrr5Kl9eFYoT9JXpKyWfb
        f67nbzUiQ5+bhoorTLL5pJYb3QvR//wtOqr2GIFvtAHqRKw1LyYys7yT1QthXu9UNGMp3m
        IvaRTKXLOsgxcFh6Tcnm9b4HCJCc2t8=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-108-AoaTpqSfNuSyDnTT12PNuw-1; Wed, 06 Nov 2019 02:08:55 -0500
Received: from smtp.corp.redhat.com (int-mx07.intmail.prod.int.phx2.redhat.com
 [10.5.11.22])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id B1B661005500;
        Wed,  6 Nov 2019 07:08:51 +0000 (UTC)
Received: from jason-ThinkPad-X1-Carbon-6th.redhat.com
 (ovpn-12-193.pek2.redhat.com [10.72.12.193])
        by smtp.corp.redhat.com (Postfix) with ESMTP id EEBAB1001B00;
        Wed,  6 Nov 2019 07:07:11 +0000 (UTC)
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
        freude@linux.ibm.com, lingshan.zhu@intel.com, idos@mellanox.com,
        eperezma@redhat.com, lulu@redhat.com, parav@mellanox.com,
        christophe.de.dinechin@gmail.com, kevin.tian@intel.com,
        stefanha@redhat.com, Jason Wang <jasowang@redhat.com>
Subject: [PATCH V9 1/6] mdev: class id support
Date: Wed,  6 Nov 2019 15:05:43 +0800
Message-Id: <20191106070548.18980-2-jasowang@redhat.com>
In-Reply-To: <20191106070548.18980-1-jasowang@redhat.com>
References: <20191106070548.18980-1-jasowang@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.84 on 10.5.11.22
X-MC-Unique: AoaTpqSfNuSyDnTT12PNuw-1
X-Mimecast-Spam-Score: 0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Mdev bus only supports vfio driver right now, so it doesn't implement
match method. But in the future, we may add drivers other than vfio,
the first driver could be virtio-mdev. This means we need to add
device class id support in bus match method to pair the mdev device
and mdev driver correctly.

So this patch adds id_table to mdev_driver and class_id for mdev
device with the match method for mdev bus.

Reviewed-by: Parav Pandit <parav@mellanox.com>
Reviewed-by: Cornelia Huck <cohuck@redhat.com>
Signed-off-by: Jason Wang <jasowang@redhat.com>
---
 .../driver-api/vfio-mediated-device.rst       |  5 ++++
 drivers/gpu/drm/i915/gvt/kvmgt.c              |  1 +
 drivers/s390/cio/vfio_ccw_ops.c               |  1 +
 drivers/s390/crypto/vfio_ap_ops.c             |  1 +
 drivers/vfio/mdev/mdev_core.c                 | 17 +++++++++++++
 drivers/vfio/mdev/mdev_driver.c               | 25 +++++++++++++++++++
 drivers/vfio/mdev/mdev_private.h              |  1 +
 drivers/vfio/mdev/vfio_mdev.c                 |  6 +++++
 include/linux/mdev.h                          |  8 ++++++
 include/linux/mod_devicetable.h               |  8 ++++++
 samples/vfio-mdev/mbochs.c                    |  1 +
 samples/vfio-mdev/mdpy.c                      |  1 +
 samples/vfio-mdev/mtty.c                      |  1 +
 13 files changed, 76 insertions(+)

```
#### [PATCH V10 1/6] mdev: class id support
##### From: Jason Wang <jasowang@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Jason Wang <jasowang@redhat.com>
X-Patchwork-Id: 11230359
Return-Path: <SRS0=/jDW=Y6=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 239B516B1
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed,  6 Nov 2019 13:38:34 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id DE6F721882
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed,  6 Nov 2019 13:38:33 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="aLI3n57w"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1731837AbfKFNic (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 6 Nov 2019 08:38:32 -0500
Received: from us-smtp-delivery-1.mimecast.com ([205.139.110.120]:33730 "EHLO
        us-smtp-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org
        with ESMTP id S1730487AbfKFNib (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 6 Nov 2019 08:38:31 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1573047509;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:content-type:content-type:
         content-transfer-encoding:content-transfer-encoding:
         in-reply-to:in-reply-to:references:references;
        bh=ZjglcjJdfJ+rYNda606bWPhtmSxvctdSzvRhdUvjVro=;
        b=aLI3n57wLFJ7tLZvLD4ie3gqiwpkM7BX3O+hWxen4jPeLGLFhGIJABJJriA4wBmdwfJDZC
        h2tIiKpHdAqCZ0bemXNCr/nt2XWsEUFmGVGMKXp2LTa+cussOCdjg6ZNVf7/r51QM+hTRF
        QF48/MBLNkI5U4pSBnCRLO84CXf4Hmk=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-50-aftLk9sJMIW6mxYuK06UeQ-1; Wed, 06 Nov 2019 08:38:26 -0500
Received: from smtp.corp.redhat.com (int-mx08.intmail.prod.int.phx2.redhat.com
 [10.5.11.23])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 1CEB81005500;
        Wed,  6 Nov 2019 13:38:22 +0000 (UTC)
Received: from jason-ThinkPad-X1-Carbon-6th.redhat.com
 (ovpn-12-193.pek2.redhat.com [10.72.12.193])
        by smtp.corp.redhat.com (Postfix) with ESMTP id A3E6E393B;
        Wed,  6 Nov 2019 13:37:23 +0000 (UTC)
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
        freude@linux.ibm.com, lingshan.zhu@intel.com, idos@mellanox.com,
        eperezma@redhat.com, lulu@redhat.com, parav@mellanox.com,
        christophe.de.dinechin@gmail.com, kevin.tian@intel.com,
        stefanha@redhat.com, Jason Wang <jasowang@redhat.com>
Subject: [PATCH V10 1/6] mdev: class id support
Date: Wed,  6 Nov 2019 21:35:26 +0800
Message-Id: <20191106133531.693-2-jasowang@redhat.com>
In-Reply-To: <20191106133531.693-1-jasowang@redhat.com>
References: <20191106133531.693-1-jasowang@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.84 on 10.5.11.23
X-MC-Unique: aftLk9sJMIW6mxYuK06UeQ-1
X-Mimecast-Spam-Score: 0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Mdev bus only supports vfio driver right now, so it doesn't implement
match method. But in the future, we may add drivers other than vfio,
the first driver could be virtio-mdev. This means we need to add
device class id support in bus match method to pair the mdev device
and mdev driver correctly.

So this patch adds id_table to mdev_driver and class_id for mdev
device with the match method for mdev bus.

Reviewed-by: Parav Pandit <parav@mellanox.com>
Reviewed-by: Cornelia Huck <cohuck@redhat.com>
Signed-off-by: Jason Wang <jasowang@redhat.com>
---
 .../driver-api/vfio-mediated-device.rst       |  5 ++++
 drivers/gpu/drm/i915/gvt/kvmgt.c              |  1 +
 drivers/s390/cio/vfio_ccw_ops.c               |  1 +
 drivers/s390/crypto/vfio_ap_ops.c             |  1 +
 drivers/vfio/mdev/mdev_core.c                 | 17 +++++++++++++
 drivers/vfio/mdev/mdev_driver.c               | 25 +++++++++++++++++++
 drivers/vfio/mdev/mdev_private.h              |  1 +
 drivers/vfio/mdev/vfio_mdev.c                 |  6 +++++
 include/linux/mdev.h                          |  8 ++++++
 include/linux/mod_devicetable.h               |  8 ++++++
 samples/vfio-mdev/mbochs.c                    |  1 +
 samples/vfio-mdev/mdpy.c                      |  1 +
 samples/vfio-mdev/mtty.c                      |  1 +
 13 files changed, 76 insertions(+)

```
#### [PATCH v2 1/4] cpuidle-haltpoll: ensure grow start value is nonzero
##### From: Zhenzhong Duan <zhenzhong.duan@oracle.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Zhenzhong Duan <zhenzhong.duan@oracle.com>
X-Patchwork-Id: 11229693
Return-Path: <SRS0=/jDW=Y6=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 6496C112B
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed,  6 Nov 2019 09:11:46 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 413622178F
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed,  6 Nov 2019 09:11:46 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=oracle.com header.i=@oracle.com
 header.b="L6Aemdo9"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1731528AbfKFJLn (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 6 Nov 2019 04:11:43 -0500
Received: from userp2130.oracle.com ([156.151.31.86]:45742 "EHLO
        userp2130.oracle.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1727041AbfKFJLm (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 6 Nov 2019 04:11:42 -0500
Received: from pps.filterd (userp2130.oracle.com [127.0.0.1])
        by userp2130.oracle.com (8.16.0.27/8.16.0.27) with SMTP id
 xA698wYd116234;
        Wed, 6 Nov 2019 09:11:25 GMT
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=oracle.com;
 h=from : to : cc :
 subject : date : message-id : in-reply-to : references; s=corp-2019-08-05;
 bh=EPKzfVRRWTGlG40d7rhnldMOWGwhBLJaJGkHe+80yiw=;
 b=L6Aemdo9fhglASfZz2I71e0bQ6RJFLKi23q2FFx8QEXB8h+shi2JmTu2aijSZBJNxag5
 FL8ciWvzZK2/qc2IWw0Gswr9Z9wm931bc3WonurMT9rl0zOVNf0wkNJ9vVdU2kzB1Ecj
 2gBv+Hkdq0t1s8Nn9q3SJLlsD3ownbR7HuQ00IGCPxhSa3Msgdmo3ioVM5RRVAefKNAe
 ST6/7q/FNwlpqE7Pe0zG8o9tJpdEm1kAcS/VpP4JzzcGQ0RztuB5CXkZ4gQt+e709AWQ
 OhmCYy5JrS56J8x+WBsYni3NYzpoGMnXV6uOtaccfnEPpRm865Yj1jwzOurwWnY7PrY0 Mw==
Received: from aserp3030.oracle.com (aserp3030.oracle.com [141.146.126.71])
        by userp2130.oracle.com with ESMTP id 2w117u4h0q-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Wed, 06 Nov 2019 09:11:25 +0000
Received: from pps.filterd (aserp3030.oracle.com [127.0.0.1])
        by aserp3030.oracle.com (8.16.0.27/8.16.0.27) with SMTP id
 xA6986Ah077631;
        Wed, 6 Nov 2019 09:09:24 GMT
Received: from aserv0121.oracle.com (aserv0121.oracle.com [141.146.126.235])
        by aserp3030.oracle.com with ESMTP id 2w35pqk36k-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Wed, 06 Nov 2019 09:09:24 +0000
Received: from abhmp0009.oracle.com (abhmp0009.oracle.com [141.146.116.15])
        by aserv0121.oracle.com (8.14.4/8.13.8) with ESMTP id xA699N3M001024;
        Wed, 6 Nov 2019 09:09:23 GMT
Received: from z2.cn.oracle.com (/10.182.71.218)
        by default (Oracle Beehive Gateway v4.0)
        with ESMTP ; Wed, 06 Nov 2019 01:09:23 -0800
From: Zhenzhong Duan <zhenzhong.duan@oracle.com>
To: linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Cc: pbonzini@redhat.com, rkrcmar@redhat.com,
        rafael.j.wysocki@intel.com, joao.m.martins@oracle.com,
        mtosatti@redhat.com, Zhenzhong Duan <zhenzhong.duan@oracle.com>
Subject: [PATCH v2 1/4] cpuidle-haltpoll: ensure grow start value is nonzero
Date: Wed,  6 Nov 2019 17:08:49 +0800
Message-Id: <1573031332-2121-2-git-send-email-zhenzhong.duan@oracle.com>
X-Mailer: git-send-email 1.8.3.1
In-Reply-To: <1573031332-2121-1-git-send-email-zhenzhong.duan@oracle.com>
References: <1573031332-2121-1-git-send-email-zhenzhong.duan@oracle.com>
X-Proofpoint-Virus-Version: vendor=nai engine=6000 definitions=9432
 signatures=668685
X-Proofpoint-Spam-Details: rule=notspam policy=default score=0 suspectscore=0
 malwarescore=0
 phishscore=0 bulkscore=0 spamscore=0 mlxscore=0 mlxlogscore=854
 adultscore=0 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.0.1-1908290000 definitions=main-1911060096
X-Proofpoint-Virus-Version: vendor=nai engine=6000 definitions=9432
 signatures=668685
X-Proofpoint-Spam-Details: rule=notspam policy=default score=0
 priorityscore=1501 malwarescore=0
 suspectscore=0 phishscore=0 bulkscore=0 spamscore=0 clxscore=1015
 lowpriorityscore=0 mlxscore=0 impostorscore=0 mlxlogscore=932 adultscore=0
 classifier=spam adjust=0 reason=mlx scancount=1 engine=8.0.1-1908290000
 definitions=main-1911060096
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

dev->poll_limit_ns could be zeroed in certain cases (e.g. by
guest_halt_poll_ns = 0). If guest_halt_poll_grow_start is zero,
dev->poll_limit_ns will never be bigger than zero.

Use param callback to avoid writing zero to guest_halt_poll_grow_start.

Signed-off-by: Zhenzhong Duan <zhenzhong.duan@oracle.com>
---
 drivers/cpuidle/governors/haltpoll.c | 22 +++++++++++++++++++++-
 1 file changed, 21 insertions(+), 1 deletion(-)

```
#### [PATCH RESEND v2 1/4] cpuidle-haltpoll: ensure grow start value is nonzero
##### From: Zhenzhong Duan <zhenzhong.duan@oracle.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Zhenzhong Duan <zhenzhong.duan@oracle.com>
X-Patchwork-Id: 11230105
Return-Path: <SRS0=/jDW=Y6=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 769AB13BD
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed,  6 Nov 2019 11:56:16 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 52B9C21848
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed,  6 Nov 2019 11:56:16 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=oracle.com header.i=@oracle.com
 header.b="moDcX+2w"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1730335AbfKFL4H (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 6 Nov 2019 06:56:07 -0500
Received: from aserp2120.oracle.com ([141.146.126.78]:40192 "EHLO
        aserp2120.oracle.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1725856AbfKFL4G (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 6 Nov 2019 06:56:06 -0500
Received: from pps.filterd (aserp2120.oracle.com [127.0.0.1])
        by aserp2120.oracle.com (8.16.0.27/8.16.0.27) with SMTP id
 xA6Bs8Ph049980;
        Wed, 6 Nov 2019 11:55:44 GMT
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=oracle.com;
 h=from : to : cc :
 subject : date : message-id : in-reply-to : references; s=corp-2019-08-05;
 bh=EPKzfVRRWTGlG40d7rhnldMOWGwhBLJaJGkHe+80yiw=;
 b=moDcX+2wcqRmyIvB8FKPWFflJ+KDihvj4whWqFyfE71UiGmuXEcGhGKPKz9FEVAUbH5x
 B8NYPal0fGdPgvfDBKNL4KoNIBWB8AEtJMFNz42PELtAui17slpTuYsQf8+n4KNDxUkJ
 Zom61tgP25VcZthq73P1v19qA5b1galtl0XPq1zc73QravPV9ZTtnkTE5Ghd+V0JLCv4
 vWf/9DK4tmPXPo35oLEfxdYPttPAW5yszxDrkHAIeY2uddzROD/Qb/+KFIDMP5XTisKo
 Itv9SGVp5JZ6a+oOi9sOiR+nNKxmSFlY5KfLLj7Llty49P8C2qEvmyy0zX7I2pVDd4Y/ Wg==
Received: from userp3020.oracle.com (userp3020.oracle.com [156.151.31.79])
        by aserp2120.oracle.com with ESMTP id 2w11rq5m5s-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Wed, 06 Nov 2019 11:55:43 +0000
Received: from pps.filterd (userp3020.oracle.com [127.0.0.1])
        by userp3020.oracle.com (8.16.0.27/8.16.0.27) with SMTP id
 xA6BsLeu051863;
        Wed, 6 Nov 2019 11:55:43 GMT
Received: from aserv0121.oracle.com (aserv0121.oracle.com [141.146.126.235])
        by userp3020.oracle.com with ESMTP id 2w31639sgh-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Wed, 06 Nov 2019 11:55:42 +0000
Received: from abhmp0015.oracle.com (abhmp0015.oracle.com [141.146.116.21])
        by aserv0121.oracle.com (8.14.4/8.13.8) with ESMTP id xA6BtffF022120;
        Wed, 6 Nov 2019 11:55:41 GMT
Received: from z2.cn.oracle.com (/10.182.71.218)
        by default (Oracle Beehive Gateway v4.0)
        with ESMTP ; Wed, 06 Nov 2019 03:55:41 -0800
From: Zhenzhong Duan <zhenzhong.duan@oracle.com>
To: linux-kernel@vger.kernel.org
Cc: pbonzini@redhat.com, rkrcmar@redhat.com,
        rafael.j.wysocki@intel.com, joao.m.martins@oracle.com,
        mtosatti@redhat.com, kvm@vger.kernel.org, linux-pm@vger.kernel.org,
        Zhenzhong Duan <zhenzhong.duan@oracle.com>
Subject: [PATCH RESEND v2 1/4] cpuidle-haltpoll: ensure grow start value is
 nonzero
Date: Wed,  6 Nov 2019 19:54:59 +0800
Message-Id: <1573041302-4904-2-git-send-email-zhenzhong.duan@oracle.com>
X-Mailer: git-send-email 1.8.3.1
In-Reply-To: <1573041302-4904-1-git-send-email-zhenzhong.duan@oracle.com>
References: <1573041302-4904-1-git-send-email-zhenzhong.duan@oracle.com>
X-Proofpoint-Virus-Version: vendor=nai engine=6000 definitions=9432
 signatures=668685
X-Proofpoint-Spam-Details: rule=notspam policy=default score=0 suspectscore=1
 malwarescore=0
 phishscore=0 bulkscore=0 spamscore=0 mlxscore=0 mlxlogscore=808
 adultscore=0 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.0.1-1908290000 definitions=main-1911060119
X-Proofpoint-Virus-Version: vendor=nai engine=6000 definitions=9432
 signatures=668685
X-Proofpoint-Spam-Details: rule=notspam policy=default score=0
 priorityscore=1501 malwarescore=0
 suspectscore=1 phishscore=0 bulkscore=0 spamscore=0 clxscore=1015
 lowpriorityscore=0 mlxscore=0 impostorscore=0 mlxlogscore=886 adultscore=0
 classifier=spam adjust=0 reason=mlx scancount=1 engine=8.0.1-1908290000
 definitions=main-1911060119
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

dev->poll_limit_ns could be zeroed in certain cases (e.g. by
guest_halt_poll_ns = 0). If guest_halt_poll_grow_start is zero,
dev->poll_limit_ns will never be bigger than zero.

Use param callback to avoid writing zero to guest_halt_poll_grow_start.

Signed-off-by: Zhenzhong Duan <zhenzhong.duan@oracle.com>
---
 drivers/cpuidle/governors/haltpoll.c | 22 +++++++++++++++++++++-
 1 file changed, 21 insertions(+), 1 deletion(-)

```
#### [PATCH v2] KVM: X86: Fix initialization of MSR lists(msrs_to_save[], emulated_msrs[] and msr_based_features[])
##### From: Chenyi Qiang <chenyi.qiang@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Chenyi Qiang <chenyi.qiang@intel.com>
X-Patchwork-Id: 11229371
Return-Path: <SRS0=/jDW=Y6=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id BED0F1747
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed,  6 Nov 2019 06:35:17 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 877FC2075C
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed,  6 Nov 2019 06:35:17 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729858AbfKFGfO (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 6 Nov 2019 01:35:14 -0500
Received: from mga01.intel.com ([192.55.52.88]:15587 "EHLO mga01.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1727795AbfKFGfO (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 6 Nov 2019 01:35:14 -0500
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from fmsmga002.fm.intel.com ([10.253.24.26])
  by fmsmga101.fm.intel.com with ESMTP/TLS/DHE-RSA-AES256-GCM-SHA384;
 05 Nov 2019 22:35:13 -0800
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.68,272,1569308400";
   d="scan'208";a="232754499"
Received: from chenyi-pc.sh.intel.com ([10.239.159.72])
  by fmsmga002.fm.intel.com with ESMTP; 05 Nov 2019 22:35:11 -0800
From: Chenyi Qiang <chenyi.qiang@intel.com>
To: Paolo Bonzini <pbonzini@redhat.com>,
 =?utf-8?b?UmFkaW0gS3LEjW3DocWZ?= <rkrcmar@redhat.com>,
 Sean Christopherson <sean.j.christopherson@intel.com>,
 Vitaly Kuznetsov <vkuznets@redhat.com>, Jim Mattson <jmattson@google.com>,
 Joerg Roedel <joro@8bytes.org>
Cc: Xiaoyao Li <xiaoyao.li@intel.com>, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org, stable@vger.kernel.org
Subject: [PATCH v2] KVM: X86: Fix initialization of MSR lists(msrs_to_save[],
 emulated_msrs[] and msr_based_features[])
Date: Wed,  6 Nov 2019 14:35:20 +0800
Message-Id: <20191106063520.1915-1-chenyi.qiang@intel.com>
X-Mailer: git-send-email 2.17.1
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The three MSR lists(msrs_to_save[], emulated_msrs[] and
msr_based_features[]) are global arrays of kvm.ko, which are
adjusted (copy supported MSRs forward to override the unsupported MSRs)
when insmod kvm-{intel,amd}.ko, but it doesn't reset these three arrays
to their initial value when rmmod kvm-{intel,amd}.ko. Thus, at the next
installation, kvm-{intel,amd}.ko will do operations on the modified
arrays with some MSRs lost and some MSRs duplicated.

So define three constant arrays to hold the initial MSR lists and
initialize msrs_to_save[], emulated_msrs[] and msr_based_features[]
based on the constant arrays.

Cc: stable@vger.kernel.org
Reviewed-by: Xiaoyao Li <xiaoyao.li@intel.com>
Signed-off-by: Chenyi Qiang <chenyi.qiang@intel.com>
---
Changes in v2:
 - define initial MSR lists with static const.
 - change the dynamic allocation of supported MSR lists to static allocation.

 arch/x86/kvm/x86.c | 51 +++++++++++++++++++++++++---------------------
 1 file changed, 28 insertions(+), 23 deletions(-)

```
#### [kvm-unit-tests Patch v1 1/2] x86: ioapic: Add the smp configuration to ioapic unittest
##### From: Nitesh Narayan Lal <nitesh@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Nitesh Narayan Lal <nitesh@redhat.com>
X-Patchwork-Id: 11230217
Return-Path: <SRS0=/jDW=Y6=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id BF14E1599
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed,  6 Nov 2019 12:47:33 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 8FB4721882
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed,  6 Nov 2019 12:47:33 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="VkkIKRl/"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1730622AbfKFMrc (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 6 Nov 2019 07:47:32 -0500
Received: from us-smtp-2.mimecast.com ([207.211.31.81]:21977 "EHLO
        us-smtp-delivery-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S1730392AbfKFMrc (ORCPT
        <rfc822;kvm@vger.kernel.org>); Wed, 6 Nov 2019 07:47:32 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1573044451;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:content-type:content-type:
         content-transfer-encoding:content-transfer-encoding:
         in-reply-to:in-reply-to:references:references;
        bh=2/QDEapR+pQoQB46goTREYq60QE/KAIKC9jcYxuCF9M=;
        b=VkkIKRl/xKvgfnhWb6KzsWhM6YVadIEaKUxe2hBz4AGNnet2/a2t/bY35folWe0AttZdyE
        ME4om8cVb0hmLRWVfMcFrnIDzqtgY/NEPYuLnLkVCVD7N4t3TycLkkokHCBzwlvPdgskAf
        QOKhpLvDwreFZk3KDLlK29sWn2vyFRc=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-315-6epujcizPnyPP0ZuD06fpw-1; Wed, 06 Nov 2019 07:47:30 -0500
Received: from smtp.corp.redhat.com (int-mx01.intmail.prod.int.phx2.redhat.com
 [10.5.11.11])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 463DC477
        for <kvm@vger.kernel.org>; Wed,  6 Nov 2019 12:47:29 +0000 (UTC)
Received: from virtlab512.virt.lab.eng.bos.redhat.com
 (virtlab512.virt.lab.eng.bos.redhat.com [10.19.152.206])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 8E5F36056B;
        Wed,  6 Nov 2019 12:47:24 +0000 (UTC)
From: Nitesh Narayan Lal <nitesh@redhat.com>
To: kvm@vger.kernel.org, pbonzini@redhat.com, thuth@redhat.com,
        mtosatti@redhat.com
Subject: [kvm-unit-tests Patch v1 1/2] x86: ioapic: Add the smp configuration
 to ioapic unittest
Date: Wed,  6 Nov 2019 07:47:08 -0500
Message-Id: <1573044429-7390-2-git-send-email-nitesh@redhat.com>
In-Reply-To: <1573044429-7390-1-git-send-email-nitesh@redhat.com>
References: <1573044429-7390-1-git-send-email-nitesh@redhat.com>
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.11
X-MC-Unique: 6epujcizPnyPP0ZuD06fpw-1
X-Mimecast-Spam-Score: 0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Adds -smp configuration for ioapic unittest. This is essentially
required to test IOAPIC Logical destination mode, where we send
an interrupt to more than one vcpus at the same time.

Signed-off-by: Nitesh Narayan Lal <nitesh@redhat.com>
---
 x86/unittests.cfg | 1 +
 1 file changed, 1 insertion(+)

```
