#### [PATCH v12 01/13] KVM: Cache as_id in kvm_memory_slot
##### From: Peter Xu <peterx@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Peter Xu <peterx@redhat.com>
X-Patchwork-Id: 11810299
Return-Path: <SRS0=sA+7=DH=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 8482B112E
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 30 Sep 2020 21:50:08 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 69BE820C09
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 30 Sep 2020 21:50:08 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="CQtJ2ers"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1731107AbgI3VuH (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 30 Sep 2020 17:50:07 -0400
Received: from us-smtp-delivery-124.mimecast.com ([216.205.24.124]:47161 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1731043AbgI3Vt7 (ORCPT
        <rfc822;kvm@vger.kernel.org>); Wed, 30 Sep 2020 17:49:59 -0400
Dkim-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1601502598;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding:
         in-reply-to:in-reply-to:references:references;
        bh=nSk3L+lLkvPp2zEMzy7lJYZ9nOSi7WB6jupEA1yhNZY=;
        b=CQtJ2ersi3Lh6L47V5iH9XEgZ1Q5sIW2i6AMtzx0J5Kfn5CAwcA0FKJ1Pt6vvuTVVFROyo
        BHFcukcoBWBPXn56jy5IvkIpx1OUvyGhRjucb5kPf2Xq62S5IR2iKD4ORqb1MKH3ey6uI2
        Y3eoybYGgx+2nMq7mzkRi/eqXUVb7Ak=
Received: from mail-qt1-f200.google.com (mail-qt1-f200.google.com
 [209.85.160.200]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-555-4A61YYKzPJeYXBhxrlat5w-1; Wed, 30 Sep 2020 17:49:53 -0400
X-MC-Unique: 4A61YYKzPJeYXBhxrlat5w-1
Received: by mail-qt1-f200.google.com with SMTP id l5so2190586qtu.20
        for <kvm@vger.kernel.org>; Wed, 30 Sep 2020 14:49:53 -0700 (PDT)
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:in-reply-to
         :references:mime-version:content-transfer-encoding;
        bh=nSk3L+lLkvPp2zEMzy7lJYZ9nOSi7WB6jupEA1yhNZY=;
        b=ONqK+1vM5gHKxGa4pWpHImH9K2KcMR/E5E+Uz/5WM7rMwY816EeqvkGPJNeJTqIQFB
         KOd1HB/dyqVeX8NxtjxeuZjgdZmvQDryy4q0z/tB+xdaV3T2VXrQNWGZ6nbDsUaux2ro
         CuxjsG+W4uxAX69IRg/4Z+qgiNybyafol4m3VxJ+DOP0JG1/iF3ld64CQOWqXsW49sPi
         RrppLUGUut3J+oJWQ8HKRQL3b1BeRp3pCTkVTMk0287ps1OvXPheP2MDOUJ1AcuYe6a9
         YZ2lTNJq4b7P2qDWIO/nhcEdkVUsHQuRGk5KxBmiMAaJ8S1Q/daUDQ8sMD9lZ+NR0hKV
         NoQQ==
X-Gm-Message-State: AOAM533TcLzxVT+75zIGXhmoBgouMgBRqSV/HYJ2uBJ9A7zoEb5BrrUM
        2HEqME/BSyscIqmwAV13B/Zg5Bx3I3MFMs6SkVE5NIpNEa+OA+Nr+NO8BXJFBws/uJFDBBqfUHF
        tt5Es9QgqzXWO
X-Received: by 2002:a05:620a:159b:: with SMTP id
 d27mr4736272qkk.28.1601502592577;
        Wed, 30 Sep 2020 14:49:52 -0700 (PDT)
X-Google-Smtp-Source: 
 ABdhPJx6fbIGQaF1ah2COu5uu8NtppdFGpVXdoA4I6mTDTmKqVzv97JX+7YzZ+hePeH4V5AzWCYw9g==
X-Received: by 2002:a05:620a:159b:: with SMTP id
 d27mr4736253qkk.28.1601502592365;
        Wed, 30 Sep 2020 14:49:52 -0700 (PDT)
Received: from xz-x1.redhat.com
 (toroon474qw-lp130-09-184-147-14-204.dsl.bell.ca. [184.147.14.204])
        by smtp.gmail.com with ESMTPSA id
 j88sm3786165qte.96.2020.09.30.14.49.50
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Wed, 30 Sep 2020 14:49:51 -0700 (PDT)
From: Peter Xu <peterx@redhat.com>
To: linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Cc: "Dr . David Alan Gilbert" <dgilbert@redhat.com>, peterx@redhat.com,
        Andrew Jones <drjones@redhat.com>,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        Paolo Bonzini <pbonzini@redhat.com>
Subject: [PATCH v12 01/13] KVM: Cache as_id in kvm_memory_slot
Date: Wed, 30 Sep 2020 17:49:36 -0400
Message-Id: <20200930214948.47225-2-peterx@redhat.com>
X-Mailer: git-send-email 2.26.2
In-Reply-To: <20200930214948.47225-1-peterx@redhat.com>
References: <20200930214948.47225-1-peterx@redhat.com>
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Cache the address space ID just like the slot ID.  It will be used in
order to fill in the dirty ring entries.

Suggested-by: Paolo Bonzini <pbonzini@redhat.com>
Suggested-by: Sean Christopherson <sean.j.christopherson@intel.com>
Reviewed-by: Sean Christopherson <sean.j.christopherson@intel.com>
Signed-off-by: Peter Xu <peterx@redhat.com>
---
 include/linux/kvm_host.h | 1 +
 virt/kvm/kvm_main.c      | 6 ++++++
 2 files changed, 7 insertions(+)

```
#### [kvm-unit-tests PATCH] x86: Add one-off test to verify setting LA57 fails when it's unsupported
##### From: Sean Christopherson <sean.j.christopherson@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Sean Christopherson <sean.j.christopherson@intel.com>
X-Patchwork-Id: 11807863
Return-Path: <SRS0=sA+7=DH=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 32ACC92C
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 30 Sep 2020 04:36:18 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 235112075A
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 30 Sep 2020 04:36:18 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1725497AbgI3Eep (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 30 Sep 2020 00:34:45 -0400
Received: from mga18.intel.com ([134.134.136.126]:62136 "EHLO mga18.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1725320AbgI3Eep (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 30 Sep 2020 00:34:45 -0400
IronPort-SDR: 
 4Q29jt/rxga4o+qNpiIm/HZxMdOBttS4QfFMYe5/smxpCK9l4VbEckMjiPicBTLc1KAIlCfSj4
 VMqKrOM/1cpA==
X-IronPort-AV: E=McAfee;i="6000,8403,9759"; a="150139301"
X-IronPort-AV: E=Sophos;i="5.77,321,1596524400";
   d="scan'208";a="150139301"
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from fmsmga004.fm.intel.com ([10.253.24.48])
  by orsmga106.jf.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 29 Sep 2020 21:34:38 -0700
IronPort-SDR: 
 HRN2pWgZ8qN0KdZ3U1ggSlM8pWjto+E30PZZRbC2imRsfI2rb0FmcU1m9pNRI8p6eEA9Fuk9Nm
 7yMj5uOsLdIA==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.77,321,1596524400";
   d="scan'208";a="338932499"
Received: from sjchrist-coffee.jf.intel.com ([10.54.74.160])
  by fmsmga004.fm.intel.com with ESMTP; 29 Sep 2020 21:34:37 -0700
From: Sean Christopherson <sean.j.christopherson@intel.com>
To: Paolo Bonzini <pbonzini@redhat.com>
Cc: kvm@vger.kernel.org,
        Sean Christopherson <sean.j.christopherson@intel.com>
Subject: [kvm-unit-tests PATCH] x86: Add one-off test to verify setting LA57
 fails when it's unsupported
Date: Tue, 29 Sep 2020 21:34:36 -0700
Message-Id: <20200930043436.29270-1-sean.j.christopherson@intel.com>
X-Mailer: git-send-email 2.28.0
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Add an i386-only test to check that setting CR4.LA57 fails when 5-level
paging is not exposed to the guest.  Old versions of KVM don't intercept
LA57 by default on VMX, which means a clever guest could set LA57
without it being detected by KVM.

This test is i386-only because toggling CR4.LA57 in long mode is
illegal, i.e. won't verify the desired KVM behavior.

Signed-off-by: Sean Christopherson <sean.j.christopherson@intel.com>
---
 x86/Makefile.i386 |  2 +-
 x86/la57.c        | 13 +++++++++++++
 x86/unittests.cfg |  4 ++++
 3 files changed, 18 insertions(+), 1 deletion(-)
 create mode 100644 x86/la57.c

```
#### [PATCH 1/5] KVM: x86: Intercept LA57 to inject #GP fault when it's reserved
##### From: Sean Christopherson <sean.j.christopherson@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Sean Christopherson <sean.j.christopherson@intel.com>
X-Patchwork-Id: 11807807
Return-Path: <SRS0=sA+7=DH=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 07FE613B2
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 30 Sep 2020 04:17:13 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id E1F5D20872
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 30 Sep 2020 04:17:12 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1725854AbgI3ERG (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 30 Sep 2020 00:17:06 -0400
Received: from mga18.intel.com ([134.134.136.126]:60796 "EHLO mga18.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1725830AbgI3ERE (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 30 Sep 2020 00:17:04 -0400
IronPort-SDR: 
 NhirzcgCtt3yLoyC2phvf9aQ7JgZwNVy57GTL7AEVDcXgpRT46mL8uoWU1a7pLkiReuMelpSqP
 NecUSJBmwNnA==
X-IronPort-AV: E=McAfee;i="6000,8403,9759"; a="150137439"
X-IronPort-AV: E=Sophos;i="5.77,321,1596524400";
   d="scan'208";a="150137439"
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from fmsmga001.fm.intel.com ([10.253.24.23])
  by orsmga106.jf.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 29 Sep 2020 21:17:02 -0700
IronPort-SDR: 
 RiVJiE8GxJ20RKMyGdjkRfqB3WEkixlcftzJ0kc9o1LUMjELbXdo0vtrzz5A2hzp8tasMPmlbL
 R4kicpeSOsRA==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.77,321,1596524400";
   d="scan'208";a="415607856"
Received: from sjchrist-coffee.jf.intel.com ([10.54.74.160])
  by fmsmga001.fm.intel.com with ESMTP; 29 Sep 2020 21:17:01 -0700
From: Sean Christopherson <sean.j.christopherson@intel.com>
To: Paolo Bonzini <pbonzini@redhat.com>
Cc: Sean Christopherson <sean.j.christopherson@intel.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org,
        Lai Jiangshan <jiangshanlai@gmail.com>,
        Lai Jiangshan <laijs@linux.alibaba.com>
Subject: [PATCH 1/5] KVM: x86: Intercept LA57 to inject #GP fault when it's
 reserved
Date: Tue, 29 Sep 2020 21:16:55 -0700
Message-Id: <20200930041659.28181-2-sean.j.christopherson@intel.com>
X-Mailer: git-send-email 2.28.0
In-Reply-To: <20200930041659.28181-1-sean.j.christopherson@intel.com>
References: <20200930041659.28181-1-sean.j.christopherson@intel.com>
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Lai Jiangshan <laijs@linux.alibaba.com>

Unconditionally intercept changes to CR4.LA57 so that KVM correctly
injects a #GP fault if the guest attempts to set CR4.LA57 when it's
supported in hardware but not exposed to the guest.

Long term, KVM needs to properly handle CR4 bits that can be under guest
control but also may be reserved from the guest's perspective.  But, KVM
currently sets the CR4 guest/host mask only during vCPU creation, and
reworking flows to change that will take a bit of elbow grease.

Even if/when generic support for intercepting reserved bits exists, it's
probably not worth letting the guest set CR4.LA57 directly.  LA57 can't
be toggled while long mode is enabled, thus it's all but guaranteed to
be set once (maybe twice, e.g. by BIOS and kernel) during boot and never
touched again.  On the flip side, letting the guest own CR4.LA57 may
incur extra VMREADs.  In other words, this temporary "hack" is probably
also the right long term fix.

Fixes: fd8cb433734e ("KVM: MMU: Expose the LA57 feature to VM.")
Cc: stable@vger.kernel.org
Cc: Lai Jiangshan <jiangshanlai@gmail.com>
Signed-off-by: Lai Jiangshan <laijs@linux.alibaba.com>
[sean: rewrote changelog]
Signed-off-by: Sean Christopherson <sean.j.christopherson@intel.com>
---
 arch/x86/kvm/kvm_cache_regs.h | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
#### [PATCH 1/3 v4] KVM: nVMX: KVM needs to unset "unrestricted guest" VM-execution control in vmcs02 if vmcs12 doesn't set it
##### From: Krish Sadhukhan <krish.sadhukhan@oracle.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Krish Sadhukhan <krish.sadhukhan@oracle.com>
X-Patchwork-Id: 11810295
Return-Path: <SRS0=sA+7=DH=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 4F0F8112C
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 30 Sep 2020 21:47:40 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 250EF20C09
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 30 Sep 2020 21:47:39 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=oracle.com header.i=@oracle.com
 header.b="aFHlg9sw"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1730528AbgI3Vrj (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 30 Sep 2020 17:47:39 -0400
Received: from userp2120.oracle.com ([156.151.31.85]:43142 "EHLO
        userp2120.oracle.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1729912AbgI3Vri (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 30 Sep 2020 17:47:38 -0400
Received: from pps.filterd (userp2120.oracle.com [127.0.0.1])
        by userp2120.oracle.com (8.16.0.42/8.16.0.42) with SMTP id
 08ULjI7u196161;
        Wed, 30 Sep 2020 21:47:33 GMT
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=oracle.com;
 h=from : to : cc :
 subject : date : message-id : in-reply-to : references; s=corp-2020-01-29;
 bh=9P1BqW5eEbN0sm2+B7OnQjLwAserdN/C+elcGXIC7Lo=;
 b=aFHlg9swA+hz8DWzc/KEMFGPtF8qvlit7uqAX0w1BUgDPEPLElO0hZxHrqc/L2AsEgxR
 AbQ+5/THDnTBVLwdfVhJTPSNLqI/ckU53/5iGLSx6uBA4USosIvhJI6+W2LuUwgtfJq0
 De3FjwS1ecJrzMzwj8e95uc9h6kEQfuXAeZ5ri81a7f/nbtdDo35MyWKCskeIIYDUKdp
 vkJ98qSwSu75By+K5qWcLHA1ga5BtD9FUGEjYp4FtDno6G10/xDufsbR1W1sbagY1jID
 bTpnGMEDuMORQO6UaOuvwkp+X+AAMrD6ZLRoITJ4qao3ZCa2FLaZlUEqMCcW8mokwdnm nA==
Received: from userp3020.oracle.com (userp3020.oracle.com [156.151.31.79])
        by userp2120.oracle.com with ESMTP id 33sx9navpx-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=FAIL);
        Wed, 30 Sep 2020 21:47:33 +0000
Received: from pps.filterd (userp3020.oracle.com [127.0.0.1])
        by userp3020.oracle.com (8.16.0.42/8.16.0.42) with SMTP id
 08ULingG165112;
        Wed, 30 Sep 2020 21:45:33 GMT
Received: from userv0122.oracle.com (userv0122.oracle.com [156.151.31.75])
        by userp3020.oracle.com with ESMTP id 33tfdunhqh-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Wed, 30 Sep 2020 21:45:33 +0000
Received: from abhmp0005.oracle.com (abhmp0005.oracle.com [141.146.116.11])
        by userv0122.oracle.com (8.14.4/8.14.4) with ESMTP id 08ULjWGL005611;
        Wed, 30 Sep 2020 21:45:32 GMT
Received: from sadhukhan-nvmx.osdevelopmeniad.oraclevcn.com (/100.100.230.226)
        by default (Oracle Beehive Gateway v4.0)
        with ESMTP ; Wed, 30 Sep 2020 14:45:32 -0700
From: Krish Sadhukhan <krish.sadhukhan@oracle.com>
To: kvm@vger.kernel.org
Cc: pbonzini@redhat.com, jmattson@google.com,
        sean.j.christopherson@intel.com
Subject: [PATCH 1/3 v4] KVM: nVMX: KVM needs to unset "unrestricted guest"
 VM-execution control in vmcs02 if vmcs12 doesn't set it
Date: Wed, 30 Sep 2020 21:45:14 +0000
Message-Id: <20200930214516.20926-2-krish.sadhukhan@oracle.com>
X-Mailer: git-send-email 2.18.4
In-Reply-To: <20200930214516.20926-1-krish.sadhukhan@oracle.com>
References: <20200930214516.20926-1-krish.sadhukhan@oracle.com>
X-Proofpoint-Virus-Version: vendor=nai engine=6000 definitions=9760
 signatures=668680
X-Proofpoint-Spam-Details: rule=notspam policy=default score=0 mlxlogscore=999
 phishscore=0
 adultscore=0 malwarescore=0 spamscore=0 mlxscore=0 bulkscore=0
 suspectscore=1 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.12.0-2006250000 definitions=main-2009300175
X-Proofpoint-Virus-Version: vendor=nai engine=6000 definitions=9760
 signatures=668680
X-Proofpoint-Spam-Details: rule=notspam policy=default score=0 mlxlogscore=999
 suspectscore=1
 phishscore=0 mlxscore=0 lowpriorityscore=0 adultscore=0 clxscore=1015
 spamscore=0 impostorscore=0 malwarescore=0 bulkscore=0 priorityscore=1501
 classifier=spam adjust=0 reason=mlx scancount=1 engine=8.12.0-2006250000
 definitions=main-2009300175
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Currently, prepare_vmcs02_early() does not check if the "unrestricted guest"
VM-execution control in vmcs12 is turned off and leaves the corresponding
bit on in vmcs02. Due to this setting, vmentry checks which are supposed to
render the nested guest state as invalid when this VM-execution control is
not set, are passing in hardware.

This patch turns off the "unrestricted guest" VM-execution control in vmcs02
if vmcs12 has turned it off.

Suggested-by: Jim Mattson <jmattson@google.com>
Suggested-by: Sean Christopherson <sean.j.christopherson@intel.com>
Signed-off-by: Krish Sadhukhan <krish.sadhukhan@oracle.com>
---
 arch/x86/kvm/vmx/nested.c |  3 +++
 arch/x86/kvm/vmx/vmx.c    | 17 +++++++++--------
 arch/x86/kvm/vmx/vmx.h    |  7 +++++++
 3 files changed, 19 insertions(+), 8 deletions(-)

```
