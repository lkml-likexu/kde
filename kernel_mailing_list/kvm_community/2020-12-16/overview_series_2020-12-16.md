#### [Bug 210695] error: kvm run failed Invalid argument
##### From: bugzilla-daemon@bugzilla.kernel.org

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: bugzilla-daemon@bugzilla.kernel.org
X-Patchwork-Id: 11976251
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-9.0 required=3.0 tests=BAYES_00,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS autolearn=ham autolearn_force=no
	version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 3ACEEC4361B
	for <kvm@archiver.kernel.org>; Wed, 16 Dec 2020 02:29:07 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 0D32122E03
	for <kvm@archiver.kernel.org>; Wed, 16 Dec 2020 02:29:07 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1725927AbgLPC3G convert rfc822-to-8bit (ORCPT
        <rfc822;kvm@archiver.kernel.org>); Tue, 15 Dec 2020 21:29:06 -0500
Received: from mail.kernel.org ([198.145.29.99]:46788 "EHLO mail.kernel.org"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1725601AbgLPC3G (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 15 Dec 2020 21:29:06 -0500
From: bugzilla-daemon@bugzilla.kernel.org
Authentication-Results: mail.kernel.org;
 dkim=permerror (bad message/signature format)
To: kvm@vger.kernel.org
Subject: [Bug 210695] error: kvm run failed Invalid argument
Date: Wed, 16 Dec 2020 02:28:25 +0000
X-Bugzilla-Reason: None
X-Bugzilla-Type: changed
X-Bugzilla-Watch-Reason: AssignedTo virtualization_kvm@kernel-bugs.osdl.org
X-Bugzilla-Product: Virtualization
X-Bugzilla-Component: kvm
X-Bugzilla-Version: unspecified
X-Bugzilla-Keywords: 
X-Bugzilla-Severity: normal
X-Bugzilla-Who: rherbert@sympatico.ca
X-Bugzilla-Status: NEW
X-Bugzilla-Resolution: 
X-Bugzilla-Priority: P1
X-Bugzilla-Assigned-To: virtualization_kvm@kernel-bugs.osdl.org
X-Bugzilla-Flags: 
X-Bugzilla-Changed-Fields: 
Message-ID: <bug-210695-28872-b4D0Lqj7rJ@https.bugzilla.kernel.org/>
In-Reply-To: <bug-210695-28872@https.bugzilla.kernel.org/>
References: <bug-210695-28872@https.bugzilla.kernel.org/>
X-Bugzilla-URL: https://bugzilla.kernel.org/
Auto-Submitted: auto-generated
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

https://bugzilla.kernel.org/show_bug.cgi?id=210695

--- Comment #2 from Richard Herbert (rherbert@sympatico.ca) ---
Hi, Sean.  I'm no programmer, unfortunately, but when kernel 5.10-rc4 was
released, this was the patch that I suspected had fixed the problem.  I don't
find this code is 5.10.1, so it must have been reverted or moved.

```
#### [Bug 210695] error: kvm run failed Invalid argument
##### From: bugzilla-daemon@bugzilla.kernel.org

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: bugzilla-daemon@bugzilla.kernel.org
X-Patchwork-Id: 11978601
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-9.0 required=3.0 tests=BAYES_00,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS autolearn=ham autolearn_force=no
	version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 02CADC4361B
	for <kvm@archiver.kernel.org>; Wed, 16 Dec 2020 20:50:32 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id B010223441
	for <kvm@archiver.kernel.org>; Wed, 16 Dec 2020 20:50:31 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729083AbgLPUub convert rfc822-to-8bit (ORCPT
        <rfc822;kvm@archiver.kernel.org>); Wed, 16 Dec 2020 15:50:31 -0500
Received: from mail.kernel.org ([198.145.29.99]:46602 "EHLO mail.kernel.org"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1729080AbgLPUua (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 16 Dec 2020 15:50:30 -0500
From: bugzilla-daemon@bugzilla.kernel.org
Authentication-Results: mail.kernel.org;
 dkim=permerror (bad message/signature format)
To: kvm@vger.kernel.org
Subject: [Bug 210695] error: kvm run failed Invalid argument
Date: Wed, 16 Dec 2020 20:49:49 +0000
X-Bugzilla-Reason: None
X-Bugzilla-Type: changed
X-Bugzilla-Watch-Reason: AssignedTo virtualization_kvm@kernel-bugs.osdl.org
X-Bugzilla-Product: Virtualization
X-Bugzilla-Component: kvm
X-Bugzilla-Version: unspecified
X-Bugzilla-Keywords: 
X-Bugzilla-Severity: normal
X-Bugzilla-Who: seanjc@google.com
X-Bugzilla-Status: NEW
X-Bugzilla-Resolution: 
X-Bugzilla-Priority: P1
X-Bugzilla-Assigned-To: virtualization_kvm@kernel-bugs.osdl.org
X-Bugzilla-Flags: 
X-Bugzilla-Changed-Fields: 
Message-ID: <bug-210695-28872-EwxlIyQfIA@https.bugzilla.kernel.org/>
In-Reply-To: <bug-210695-28872@https.bugzilla.kernel.org/>
References: <bug-210695-28872@https.bugzilla.kernel.org/>
X-Bugzilla-URL: https://bugzilla.kernel.org/
Auto-Submitted: auto-generated
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

https://bugzilla.kernel.org/show_bug.cgi?id=210695

--- Comment #4 from Sean Christopherson (seanjc@google.com) ---
Aha!  I haven't reproduce the bug (mostly because I'm pretty sure my guests
aren't doing emulated MMIO accesses with paging disabled), but I'm pretty sure
I know what's going on, and why -rc4 may have worked.

Your guest has paging disabled, in which case mmu->root_level will be '0' and
mmu->shadow_root_level will be '3'.  If the shadow walk in get_walk() bails
without ever entering the loop (due to an invalid PAE root), the returned leaf
will be '0' because get_walk() uses mmu->root level instead of mmu->shadow_root
level.  In get_mmio_spte(), this causes the check for reserved bits to check
uninitialized/stale stack memory and return a bogus SPTE.

Pre rc6, both get_mmio_spte() and get_walk() used the bad mmu->root_level,
which meant that the reserved bits check would get skipped in the above
scenario.  But, get_mmio_spte() would still return a stale/bogus SPTE, so it's
not at all surprising that things failed.  Actually, it's surprising that any
5.10-rc* work.  Best guess is that there is a mostly unrelated change that
cause things to work by sheer dumb luck.

In rc6, the get_mmio_spte() half of the bug was fixed by commit 9a2a0d3ca163
("kvm: x86/mmu: Fix get_mmio_spte() on CPUs supporting 5-level PT").  This
cause get_mmio_spte() to resume the reserved bits check, which all but
guaranteed an explosion, i.e. ensured a 100% failure rate on your end.

TL;DR: Can you try this patch?  I'll also try to reproduce the original bug on
my end now that I have a smoking gun.

```
#### [PATCH 01/21] vhost: move the backend feature bits to vhost_types.h
##### From: Jason Wang <jasowang@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Jason Wang <jasowang@redhat.com>
X-Patchwork-Id: 11976717
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-15.8 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_CR_TRAILER,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS
	autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id A63D0C2BBCF
	for <kvm@archiver.kernel.org>; Wed, 16 Dec 2020 06:50:19 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 81A5523370
	for <kvm@archiver.kernel.org>; Wed, 16 Dec 2020 06:50:19 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1725937AbgLPGuG (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Wed, 16 Dec 2020 01:50:06 -0500
Received: from us-smtp-delivery-124.mimecast.com ([216.205.24.124]:37315 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1725910AbgLPGuE (ORCPT
        <rfc822;kvm@vger.kernel.org>); Wed, 16 Dec 2020 01:50:04 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1608101318;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding:
         in-reply-to:in-reply-to:references:references;
        bh=LgtoOZuqafOK0nq8AHmeG/YV/K0PmtXlvUknLye9+3I=;
        b=CJ+7nKbg516RTvN3+3/3wy5XL3kZn6Aa7Bvr4P4Xyz2zh5pekIHln4NPwNCQ1igt7dVZFw
        NxdPplxwPk2RS/KvHrmcVKe3lsXcoNijAoiybmzaIFIqW/32Ge83FxzFlDJ8S4Pi4cX75F
        QWdmA8ELTS67hJFGStspxEY3/flZKrI=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-109-9E4wkYGZMxiWY1xhbYWvrg-1; Wed, 16 Dec 2020 01:48:36 -0500
X-MC-Unique: 9E4wkYGZMxiWY1xhbYWvrg-1
Received: from smtp.corp.redhat.com (int-mx07.intmail.prod.int.phx2.redhat.com
 [10.5.11.22])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 370BE1005513;
        Wed, 16 Dec 2020 06:48:35 +0000 (UTC)
Received: from jason-ThinkPad-X1-Carbon-6th.redhat.com
 (ovpn-12-210.pek2.redhat.com [10.72.12.210])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 2A77110013C1;
        Wed, 16 Dec 2020 06:48:30 +0000 (UTC)
From: Jason Wang <jasowang@redhat.com>
To: mst@redhat.com, jasowang@redhat.com
Cc: eperezma@redhat.com, kvm@vger.kernel.org,
        virtualization@lists.linux-foundation.org, netdev@vger.kernel.org,
        linux-kernel@vger.kernel.org, lulu@redhat.com, eli@mellanox.com,
        lingshan.zhu@intel.com, rob.miller@broadcom.com,
        stefanha@redhat.com, sgarzare@redhat.com
Subject: [PATCH 01/21] vhost: move the backend feature bits to vhost_types.h
Date: Wed, 16 Dec 2020 14:47:58 +0800
Message-Id: <20201216064818.48239-2-jasowang@redhat.com>
In-Reply-To: <20201216064818.48239-1-jasowang@redhat.com>
References: <20201216064818.48239-1-jasowang@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.84 on 10.5.11.22
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

We should store feature bits in vhost_types.h as what has been done
for e.g VHOST_F_LOG_ALL.

Signed-off-by: Jason Wang <jasowang@redhat.com>
---
 include/uapi/linux/vhost.h       | 5 -----
 include/uapi/linux/vhost_types.h | 5 +++++
 2 files changed, 5 insertions(+), 5 deletions(-)

```
#### [PATCH 1/2] Enumerate AVX Vector Neural Network instructions
##### From: Yang Zhong <yang.zhong@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Yang Zhong <yang.zhong@intel.com>
X-Patchwork-Id: 11976291
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.8 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED,USER_AGENT_GIT
	autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 84448C2BBCA
	for <kvm@archiver.kernel.org>; Wed, 16 Dec 2020 02:56:58 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 39A872311A
	for <kvm@archiver.kernel.org>; Wed, 16 Dec 2020 02:56:58 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1725791AbgLPC4l (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 15 Dec 2020 21:56:41 -0500
Received: from mga03.intel.com ([134.134.136.65]:9465 "EHLO mga03.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1725710AbgLPC4l (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 15 Dec 2020 21:56:41 -0500
IronPort-SDR: 
 pIgCqA8wiZgqFEtTeH2T98oJDsISJo47uB3gwPfy1ruwNXGgfED1fJeQZZitC2O9GSj4OH410g
 1LVt4iV1Ek4Q==
X-IronPort-AV: E=McAfee;i="6000,8403,9836"; a="175099201"
X-IronPort-AV: E=Sophos;i="5.78,423,1599548400";
   d="scan'208";a="175099201"
Received: from fmsmga001.fm.intel.com ([10.253.24.23])
  by orsmga103.jf.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 15 Dec 2020 18:55:58 -0800
IronPort-SDR: 
 3f0utlsZ8lRjxpiCRmW8Um+I1ILiWoUiHQ5AyI7mZR7q5dsW8Yyv8jrqsfxQbLDDLN6QMqQe0y
 DF0Z4MDMJeGw==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.78,423,1599548400";
   d="scan'208";a="451538791"
Received: from icx-2s.bj.intel.com ([10.240.192.119])
  by fmsmga001.fm.intel.com with ESMTP; 15 Dec 2020 18:55:54 -0800
From: Yang Zhong <yang.zhong@intel.com>
To: linux-kernel@vger.kernel.org, x86@kernel.org, kvm@vger.kernel.org
Cc: tglx@linutronix.de, mingo@redhat.com, bp@alien8.de, hpa@zytor.com,
        tony.luck@intel.com, pbonzini@redhat.com, seanjc@google.com,
        vkuznets@redhat.com, wanpengli@tencent.com, jmattson@google.com,
        joro@8bytes.org, kyung.min.park@intel.com, yang.zhong@intel.com
Subject: [PATCH 1/2] Enumerate AVX Vector Neural Network instructions
Date: Wed, 16 Dec 2020 10:01:28 +0800
Message-Id: <20201216020129.19875-2-yang.zhong@intel.com>
X-Mailer: git-send-email 2.29.2.334.gfaefdd61ec
In-Reply-To: <20201216020129.19875-1-yang.zhong@intel.com>
References: <20201216020129.19875-1-yang.zhong@intel.com>
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Kyung Min Park <kyung.min.park@intel.com>

Add AVX version of the Vector Neural Network (VNNI) Instructions.

A processor supports AVX VNNI instructions if CPUID.0x07.0x1:EAX[4] is
present. The following instructions are available when this feature is
present.
  1. VPDPBUS: Multiply and Add Unsigned and Signed Bytes
  2. VPDPBUSDS: Multiply and Add Unsigned and Signed Bytes with Saturation
  3. VPDPWSSD: Multiply and Add Signed Word Integers
  4. VPDPWSSDS: Multiply and Add Signed Integers with Saturation

The only in-kernel usage of this is kvm passthrough. The CPU feature
flag is shown as "avx_vnni" in /proc/cpuinfo.

This instruction is currently documented in the latest "extensions"
manual (ISE). It will appear in the "main" manual (SDM) in the future.

Signed-off-by: Kyung Min Park <kyung.min.park@intel.com>
Signed-off-by: Yang Zhong <yang.zhong@intel.com>
Reviewed-by: Tony Luck <tony.luck@intel.com>
---
 arch/x86/include/asm/cpufeatures.h | 1 +
 1 file changed, 1 insertion(+)

```
#### [kvm-unit-tests PATCH v1 01/12] lib/x86: fix page.h to include the generic header
##### From: Claudio Imbrenda <imbrenda@linux.ibm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Claudio Imbrenda <imbrenda@linux.ibm.com>
X-Patchwork-Id: 11978529
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.8 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT autolearn=ham
	autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 642F6C0018C
	for <kvm@archiver.kernel.org>; Wed, 16 Dec 2020 20:14:33 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 35C3923730
	for <kvm@archiver.kernel.org>; Wed, 16 Dec 2020 20:14:33 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728749AbgLPUOV (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Wed, 16 Dec 2020 15:14:21 -0500
Received: from mx0b-001b2d01.pphosted.com ([148.163.158.5]:14022 "EHLO
        mx0b-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1728746AbgLPUOV (ORCPT
        <rfc822;kvm@vger.kernel.org>); Wed, 16 Dec 2020 15:14:21 -0500
Received: from pps.filterd (m0127361.ppops.net [127.0.0.1])
        by mx0a-001b2d01.pphosted.com (8.16.0.42/8.16.0.42) with SMTP id
 0BGK2vxe181265
        for <kvm@vger.kernel.org>; Wed, 16 Dec 2020 15:13:39 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=ibm.com;
 h=from : to : cc : subject
 : date : message-id : in-reply-to : references : mime-version :
 content-transfer-encoding; s=pp1;
 bh=g+6NcmY2CMN3pnInIKAxRv/N64gV3ATfEKs3aWONZF0=;
 b=Lq/TgipjRP2cImS1xRkgE5VBhO7SrXOquZJXIZhJ+KHnIC9y9eJcQPLpzLet3gf9Mpa1
 wxNk+/3qSufJQMzt6PkDxFglt110fAodQqIVBh5cJhVFZSUatjU8b3mCbimAopk7cJ2x
 Gm+bWb8lC53iCFlCBYSBwUlojdAEq5GmllYN5dgH3nO1L64pysZjNdqioKMUDHaa7J08
 NdjSU3vvH4fU6Z2eAYm7RUAPxMYArIpZCCMNIPsUjtC2ZTocgxgHfKTJrCWI8cwWP3sT
 bu0Sms6OGja+T4fa/BqhLWOveg1x2HBU9vfgd1Wv33HcEzpc0IfJTu+LGpiXD/bmyxRB Cw==
Received: from pps.reinject (localhost [127.0.0.1])
        by mx0a-001b2d01.pphosted.com with ESMTP id 35frs78gek-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT)
        for <kvm@vger.kernel.org>; Wed, 16 Dec 2020 15:13:39 -0500
Received: from m0127361.ppops.net (m0127361.ppops.net [127.0.0.1])
        by pps.reinject (8.16.0.36/8.16.0.36) with SMTP id 0BGK36tG181632
        for <kvm@vger.kernel.org>; Wed, 16 Dec 2020 15:13:39 -0500
Received: from ppma03fra.de.ibm.com (6b.4a.5195.ip4.static.sl-reverse.com
 [149.81.74.107])
        by mx0a-001b2d01.pphosted.com with ESMTP id 35frs78ge2-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Wed, 16 Dec 2020 15:13:39 -0500
Received: from pps.filterd (ppma03fra.de.ibm.com [127.0.0.1])
        by ppma03fra.de.ibm.com (8.16.0.42/8.16.0.42) with SMTP id
 0BGK7ZA1021512;
        Wed, 16 Dec 2020 20:13:37 GMT
Received: from b06cxnps4074.portsmouth.uk.ibm.com
 (d06relay11.portsmouth.uk.ibm.com [9.149.109.196])
        by ppma03fra.de.ibm.com with ESMTP id 35cng8evkk-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Wed, 16 Dec 2020 20:13:37 +0000
Received: from d06av24.portsmouth.uk.ibm.com (d06av24.portsmouth.uk.ibm.com
 [9.149.105.60])
        by b06cxnps4074.portsmouth.uk.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id 0BGKCK5933489186
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Wed, 16 Dec 2020 20:12:20 GMT
Received: from d06av24.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 6DFB442042;
        Wed, 16 Dec 2020 20:12:20 +0000 (GMT)
Received: from d06av24.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 008BB4204B;
        Wed, 16 Dec 2020 20:12:20 +0000 (GMT)
Received: from ibm-vm.ibmuc.com (unknown [9.145.10.74])
        by d06av24.portsmouth.uk.ibm.com (Postfix) with ESMTP;
        Wed, 16 Dec 2020 20:12:19 +0000 (GMT)
From: Claudio Imbrenda <imbrenda@linux.ibm.com>
To: kvm@vger.kernel.org
Cc: frankja@linux.ibm.com, david@redhat.com, thuth@redhat.com,
        pbonzini@redhat.com, cohuck@redhat.com, lvivier@redhat.com,
        nadav.amit@gmail.com
Subject: [kvm-unit-tests PATCH v1 01/12] lib/x86: fix page.h to include the
 generic header
Date: Wed, 16 Dec 2020 21:11:49 +0100
Message-Id: <20201216201200.255172-2-imbrenda@linux.ibm.com>
X-Mailer: git-send-email 2.26.2
In-Reply-To: <20201216201200.255172-1-imbrenda@linux.ibm.com>
References: <20201216201200.255172-1-imbrenda@linux.ibm.com>
MIME-Version: 1.0
X-TM-AS-GCONF: 00
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.343,18.0.737
 definitions=2020-12-16_08:2020-12-15,2020-12-16 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 lowpriorityscore=0
 malwarescore=0 bulkscore=0 phishscore=0 mlxlogscore=934 mlxscore=0
 spamscore=0 suspectscore=0 adultscore=0 clxscore=1015 impostorscore=0
 priorityscore=1501 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.12.0-2009150000 definitions=main-2012160124
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Bring x86 in line with the other architectures and include the generic header
at asm-generic/page.h .
This provides the macros PAGE_SHIFT, PAGE_SIZE, PAGE_MASK, virt_to_pfn, and
pfn_to_virt.

Signed-off-by: Claudio Imbrenda <imbrenda@linux.ibm.com>
---
 lib/x86/asm/page.h | 4 +---
 1 file changed, 1 insertion(+), 3 deletions(-)

```
#### [GIT PULL] VFIO updates for v5.11-rc1
##### From: Alex Williamson <alex.williamson@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Alex Williamson <alex.williamson@redhat.com>
X-Patchwork-Id: 11978501
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-20.8 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_PATCH,INCLUDES_PULL_REQUEST,MAILING_LIST_MULTI,MENTIONS_GIT_HOSTING,
	SPF_HELO_NONE,SPF_PASS autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 7FD7AC4361B
	for <kvm@archiver.kernel.org>; Wed, 16 Dec 2020 19:38:39 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 3DE9D22573
	for <kvm@archiver.kernel.org>; Wed, 16 Dec 2020 19:38:39 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728525AbgLPTii (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Wed, 16 Dec 2020 14:38:38 -0500
Received: from us-smtp-delivery-124.mimecast.com ([63.128.21.124]:25011 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1727349AbgLPTii (ORCPT
        <rfc822;kvm@vger.kernel.org>); Wed, 16 Dec 2020 14:38:38 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1608147431;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:content-type:content-type:
         content-transfer-encoding:content-transfer-encoding;
        bh=YSOn/k1Hw3PBV10RiB9kjk1aQ7QyRB3qI+j4unC73oI=;
        b=XmwrndeU3pBY4WoT0oCKwaLkau8Wg1V20NOgcgw57braFsmvJD3lPDEENJB1XAp8ircIbB
        7i41UCqwjlzibq3z7FN7l1nElBBStFDvDsK7WzYD4iHpTNzANiQrwZctzhiHoFdgxz9UIL
        3uy/WnZARnaEPDgxKASDqQkYtrUaRy0=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-230-p0hO15rhNR-TlnjQbwOxFA-1; Wed, 16 Dec 2020 14:37:07 -0500
X-MC-Unique: p0hO15rhNR-TlnjQbwOxFA-1
Received: from smtp.corp.redhat.com (int-mx06.intmail.prod.int.phx2.redhat.com
 [10.5.11.16])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 64071180A086;
        Wed, 16 Dec 2020 19:37:06 +0000 (UTC)
Received: from omen.home (ovpn-112-193.phx2.redhat.com [10.3.112.193])
        by smtp.corp.redhat.com (Postfix) with ESMTP id B1817177F8;
        Wed, 16 Dec 2020 19:37:01 +0000 (UTC)
Date: Wed, 16 Dec 2020 12:37:01 -0700
From: Alex Williamson <alex.williamson@redhat.com>
To: Linus Torvalds <torvalds@linux-foundation.org>
Cc: <linux-kernel@vger.kernel.org>,
        "kvm@vger.kernel.org" <kvm@vger.kernel.org>, eric.auger@redhat.com,
        jgg@nvidia.com, aik@ozlabs.ru, farman@linux.ibm.com,
        baolu.lu@linux.intel.com
Subject: [GIT PULL] VFIO updates for v5.11-rc1
Message-ID: <20201216123701.00517b52@omen.home>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.16
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Hi Linus,

The following changes since commit b65054597872ce3aefbc6a666385eabdf9e288da:

  Linux 5.10-rc6 (2020-11-29 15:50:50 -0800)

are available in the Git repository at:

  git://github.com/awilliam/linux-vfio.git tags/vfio-v5.11-rc1

for you to fetch changes up to bdfae1c9a913930eae5ea506733aa7c285e12a06:

  vfio/type1: Add vfio_group_iommu_domain() (2020-12-10 14:47:56 -0700)

----------------------------------------------------------------
VFIO updates for v5.11-rc1

 - Fix uninitialized list walk in error path (Eric Auger)

 - Use io_remap_pfn_range() (Jason Gunthorpe)

 - Allow fallback support for NVLink on POWER8 (Alexey Kardashevskiy)

 - Enable mdev request interrupt with CCW support (Eric Farman)

 - Enable interface to iommu_domain from vfio_group (Lu Baolu)

----------------------------------------------------------------
Alexey Kardashevskiy (1):
      vfio/pci/nvlink2: Do not attempt NPU2 setup on POWER8NVL NPU

Eric Auger (1):
      vfio/pci: Move dummy_resources_list init in vfio_pci_probe()

Eric Farman (2):
      vfio-mdev: Wire in a request handler for mdev parent
      vfio-ccw: Wire in the request callback

Jason Gunthorpe (1):
      vfio-pci: Use io_remap_pfn_range() for PCI IO memory

Lu Baolu (1):
      vfio/type1: Add vfio_group_iommu_domain()

 drivers/s390/cio/vfio_ccw_ops.c     | 26 ++++++++++++++++++++++++++
 drivers/s390/cio/vfio_ccw_private.h |  4 ++++
 drivers/vfio/mdev/mdev_core.c       |  4 ++++
 drivers/vfio/mdev/vfio_mdev.c       | 13 +++++++++++++
 drivers/vfio/pci/vfio_pci.c         |  7 +++----
 drivers/vfio/pci/vfio_pci_nvlink2.c |  7 +++++--
 drivers/vfio/vfio.c                 | 18 ++++++++++++++++++
 drivers/vfio/vfio_iommu_type1.c     | 24 ++++++++++++++++++++++++
 include/linux/mdev.h                |  4 ++++
 include/linux/vfio.h                |  4 ++++
 include/uapi/linux/vfio.h           |  1 +
 11 files changed, 106 insertions(+), 6 deletions(-)
```
#### [PATCH] jump_label: Fix usage in module __init
##### From: Peter Zijlstra <peterz@infradead.org>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Peter Zijlstra <peterz@infradead.org>
X-Patchwork-Id: 11977641
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-15.8 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,
	INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED
	autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 85A1FC2BBCA
	for <kvm@archiver.kernel.org>; Wed, 16 Dec 2020 13:55:43 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 4C14A2311F
	for <kvm@archiver.kernel.org>; Wed, 16 Dec 2020 13:55:43 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726408AbgLPNz0 (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Wed, 16 Dec 2020 08:55:26 -0500
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:34884 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726242AbgLPNz0 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 16 Dec 2020 08:55:26 -0500
Received: from merlin.infradead.org (merlin.infradead.org
 [IPv6:2001:8b0:10b:1231::1])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 2716BC061794;
        Wed, 16 Dec 2020 05:54:45 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; q=dns/txt; c=relaxed/relaxed;
        d=infradead.org; s=merlin.20170209;
 h=In-Reply-To:Content-Type:MIME-Version:
        References:Message-ID:Subject:Cc:To:From:Date:Sender:Reply-To:
        Content-Transfer-Encoding:Content-ID:Content-Description;
        bh=VcjIrN5FyTZolDv+Rn4aJudbB/mo6LJSIs57tLjGV9E=;
 b=rSJh99DceSgMq5jxGxn6SzKncN
        PF80gFlqTd2qHds0K4vMiVwur9ao4Gs3fQ4ryLjfz5d6MsjtduZL8ylq7LhxfdC+r3FSvD9p45tsI
        yKuBCxGc8hN/IF7V3WVmU6A79qB1sPXiJh4LAFpaLIKkhR6BLDo4IXfmKOM90CriOPwuZmGzyghD5
        4ARJeUI+ZvsEQo3pM7vqy/5+RFqUv7Dz7hy2hJU/3j9Ab2C3REcXpjoWISfNY+73uhGgPWmeqpXdn
        0EDSRNx6QPAJOFDdC+4icm5vOezUUvMiekOErU1tQhTUOcLU1tFNNZaiSvabdk4U2Y4lpFEimIyf7
        Fb1nAipA==;
Received: from j217100.upc-j.chello.nl ([24.132.217.100]
 helo=noisy.programming.kicks-ass.net)
        by merlin.infradead.org with esmtpsa (Exim 4.92.3 #3 (Red Hat Linux))
        id 1kpXGJ-0004vH-Oz; Wed, 16 Dec 2020 13:54:39 +0000
Received: from hirez.programming.kicks-ass.net
 (hirez.programming.kicks-ass.net [192.168.1.225])
        (using TLSv1.2 with cipher ECDHE-RSA-AES256-GCM-SHA384 (256/256 bits))
        (Client did not present a certificate)
        by noisy.programming.kicks-ass.net (Postfix) with ESMTPS id
 DD348304D28;
        Wed, 16 Dec 2020 14:54:35 +0100 (CET)
Received: by hirez.programming.kicks-ass.net (Postfix, from userid 1000)
        id C7551203EE86D; Wed, 16 Dec 2020 14:54:35 +0100 (CET)
Date: Wed, 16 Dec 2020 14:54:35 +0100
From: Peter Zijlstra <peterz@infradead.org>
To: Dexuan Cui <decui@microsoft.com>
Cc: Ingo Molnar <mingo@kernel.org>,
        Daniel Bristot de Oliveira <bristot@redhat.com>,
        "kvm@vger.kernel.org" <kvm@vger.kernel.org>,
        "linux-kernel@vger.kernel.org" <linux-kernel@vger.kernel.org>,
        jeyu@kernel.org, Josh Poimboeuf <jpoimboe@redhat.com>,
        ardb@kernel.org
Subject: [PATCH] jump_label: Fix usage in module __init
Message-ID: <20201216135435.GV3092@hirez.programming.kicks-ass.net>
References: 
 <MW4PR21MB1857CC85A6844C89183C93E9BFC59@MW4PR21MB1857.namprd21.prod.outlook.com>
 <20201216092649.GM3040@hirez.programming.kicks-ass.net>
 <20201216105926.GS3092@hirez.programming.kicks-ass.net>
MIME-Version: 1.0
Content-Disposition: inline
In-Reply-To: <20201216105926.GS3092@hirez.programming.kicks-ass.net>
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Final patch looks like this.
Acked-by: Josh Poimboeuf <jpoimboe@redhat.com>
---
Subject: jump_label: Fix usage in module __init
From: Peter Zijlstra <peterz@infradead.org>
Date: Wed Dec 16 12:21:36 CET 2020

When the static_key is part of the module, and the module calls
static_key_inc/enable() from it's __init section *AND* has a
static_branch_*() user in that very same __init section, things go
wobbly.

If the static_key lives outside the module, jump_label_add_module()
would append this module's sites to the key and jump_label_update()
would take the static_key_linked() branch and all would be fine.

If all the sites are outside of __init, then everything will be fine
too.

However, when all is aligned just as described above,
jump_label_update() calls __jump_label_update(.init = false) and we'll
not update sites in __init text.

Fixes: 19483677684b ("jump_label: Annotate entries that operate on __init code earlier")
Reported-by: Dexuan Cui <decui@microsoft.com>
Signed-off-by: Peter Zijlstra (Intel) <peterz@infradead.org>
Tested-by: Jessica Yu <jeyu@kernel.org>
---
 kernel/jump_label.c |    8 +++++---
```
#### [PATCH v3 1/4] KVM: PPC: Allow nested guest creation when L0 hv_guest_state > L1
##### From: Ravi Bangoria <ravi.bangoria@linux.ibm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Ravi Bangoria <ravi.bangoria@linux.ibm.com>
X-Patchwork-Id: 11977247
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.8 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT
	autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 58FD3C4361B
	for <kvm@archiver.kernel.org>; Wed, 16 Dec 2020 11:01:42 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 05F7223124
	for <kvm@archiver.kernel.org>; Wed, 16 Dec 2020 11:01:41 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1725820AbgLPLBQ (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Wed, 16 Dec 2020 06:01:16 -0500
Received: from mx0a-001b2d01.pphosted.com ([148.163.156.1]:59370 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1725283AbgLPLBP (ORCPT
        <rfc822;kvm@vger.kernel.org>); Wed, 16 Dec 2020 06:01:15 -0500
Received: from pps.filterd (m0098393.ppops.net [127.0.0.1])
        by mx0a-001b2d01.pphosted.com (8.16.0.42/8.16.0.42) with SMTP id
 0BGAgrtC079946;
        Wed, 16 Dec 2020 05:44:35 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=ibm.com;
 h=from : to : cc : subject
 : date : message-id : in-reply-to : references : mime-version :
 content-transfer-encoding; s=pp1;
 bh=YhDFzmQUoC8UQuz1UgKN1pr7/sypnPEqm7ZijMJFeYY=;
 b=KdPLmPhUS8+MCjjJt4vEI7D+2gdz800Dxzcttti7myx0jaFCHZxoW4bpOgZF5+nYbBEN
 t1Sm5NXSt0bzKht11HySAynpOOKlkC7RYvF73mu7V9X6reshAP5lAmsdbZGZa566E0Pm
 +6TRjoG+pm7wpD6RHiP7Qk4sZk0NteGwirV7ZqvuR+bFM3YDe/FYVkp9Hal1Jg3kx8v+
 jBZ0leeShSa5aRJ+slI+lABKQgtG0sodtcqto+zed6CeNXNK8SUpKtBHLvoPkXZA8HQE
 sMU0OF/SGHedUhzbVw8Gf64bBS4rbrVUKO9mlZuwBATgcs02BWeiMcGq/06wQEJVNdwx tQ==
Received: from pps.reinject (localhost [127.0.0.1])
        by mx0a-001b2d01.pphosted.com with ESMTP id 35fgqr812w-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Wed, 16 Dec 2020 05:44:35 -0500
Received: from m0098393.ppops.net (m0098393.ppops.net [127.0.0.1])
        by pps.reinject (8.16.0.36/8.16.0.36) with SMTP id 0BGAiYCh083723;
        Wed, 16 Dec 2020 05:44:35 -0500
Received: from ppma03fra.de.ibm.com (6b.4a.5195.ip4.static.sl-reverse.com
 [149.81.74.107])
        by mx0a-001b2d01.pphosted.com with ESMTP id 35fgqr8123-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Wed, 16 Dec 2020 05:44:34 -0500
Received: from pps.filterd (ppma03fra.de.ibm.com [127.0.0.1])
        by ppma03fra.de.ibm.com (8.16.0.42/8.16.0.42) with SMTP id
 0BGAhECE012676;
        Wed, 16 Dec 2020 10:44:32 GMT
Received: from b06cxnps4076.portsmouth.uk.ibm.com
 (d06relay13.portsmouth.uk.ibm.com [9.149.109.198])
        by ppma03fra.de.ibm.com with ESMTP id 35cng8e78n-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Wed, 16 Dec 2020 10:44:32 +0000
Received: from d06av25.portsmouth.uk.ibm.com (d06av25.portsmouth.uk.ibm.com
 [9.149.105.61])
        by b06cxnps4076.portsmouth.uk.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id 0BGAhFlJ30015750
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Wed, 16 Dec 2020 10:43:15 GMT
Received: from d06av25.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 42A2011C05C;
        Wed, 16 Dec 2020 10:43:15 +0000 (GMT)
Received: from d06av25.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id F1A2511C04C;
        Wed, 16 Dec 2020 10:43:11 +0000 (GMT)
Received: from bangoria.ibmuc.com (unknown [9.199.41.249])
        by d06av25.portsmouth.uk.ibm.com (Postfix) with ESMTP;
        Wed, 16 Dec 2020 10:43:11 +0000 (GMT)
From: Ravi Bangoria <ravi.bangoria@linux.ibm.com>
To: mpe@ellerman.id.au, paulus@samba.org
Cc: ravi.bangoria@linux.ibm.com, mikey@neuling.org, npiggin@gmail.com,
        leobras.c@gmail.com, pbonzini@redhat.com, christophe.leroy@c-s.fr,
        jniethe5@gmail.com, kvm@vger.kernel.org, kvm-ppc@vger.kernel.org,
        linux-kernel@vger.kernel.org, linuxppc-dev@lists.ozlabs.org
Subject: [PATCH v3 1/4] KVM: PPC: Allow nested guest creation when L0
 hv_guest_state > L1
Date: Wed, 16 Dec 2020 16:12:16 +0530
Message-Id: <20201216104219.458713-2-ravi.bangoria@linux.ibm.com>
X-Mailer: git-send-email 2.29.2
In-Reply-To: <20201216104219.458713-1-ravi.bangoria@linux.ibm.com>
References: <20201216104219.458713-1-ravi.bangoria@linux.ibm.com>
MIME-Version: 1.0
X-TM-AS-GCONF: 00
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.343,18.0.737
 definitions=2020-12-16_04:2020-12-15,2020-12-16 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 mlxscore=0 suspectscore=0
 clxscore=1015 spamscore=0 priorityscore=1501 impostorscore=0 bulkscore=0
 adultscore=0 phishscore=0 malwarescore=0 mlxlogscore=999
 lowpriorityscore=0 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.12.0-2009150000 definitions=main-2012160063
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

On powerpc, L1 hypervisor takes help of L0 using H_ENTER_NESTED
hcall to load L2 guest state in cpu. L1 hypervisor prepares the
L2 state in struct hv_guest_state and passes a pointer to it via
hcall. Using that pointer, L0 reads/writes that state directly
from/to L1 memory. Thus L0 must be aware of hv_guest_state layout
of L1. Currently it uses version field to achieve this. i.e. If
L0 hv_guest_state.version != L1 hv_guest_state.version, L0 won't
allow nested kvm guest.

This restriction can be loosen up a bit. L0 can be taught to
understand older layout of hv_guest_state, if we restrict the
new member to be added only at the end. i.e. we can allow
nested guest even when L0 hv_guest_state.version > L1
hv_guest_state.version. Though, the other way around is not
possible.

Signed-off-by: Ravi Bangoria <ravi.bangoria@linux.ibm.com>
Reviewed-by: Fabiano Rosas <farosas@linux.ibm.com>
---
 arch/powerpc/include/asm/hvcall.h   | 17 +++++++--
 arch/powerpc/kvm/book3s_hv_nested.c | 55 +++++++++++++++++++++++------
 2 files changed, 60 insertions(+), 12 deletions(-)

```
#### [PATCH] KVM: SVM: fix 32-bit compilation
##### From: Paolo Bonzini <pbonzini@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Paolo Bonzini <pbonzini@redhat.com>
X-Patchwork-Id: 11978191
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-15.8 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_CR_TRAILER,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS
	autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 5699CC2BBCA
	for <kvm@archiver.kernel.org>; Wed, 16 Dec 2020 18:10:21 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 18B97259C4
	for <kvm@archiver.kernel.org>; Wed, 16 Dec 2020 18:10:21 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729453AbgLPSKE (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Wed, 16 Dec 2020 13:10:04 -0500
Received: from us-smtp-delivery-124.mimecast.com ([63.128.21.124]:26744 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1729193AbgLPSKE (ORCPT
        <rfc822;kvm@vger.kernel.org>); Wed, 16 Dec 2020 13:10:04 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1608142118;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=mamO1/NlN2O4Takc5K2x/wvpBK6RpZ5yuQxG16/89wI=;
        b=OIdKkCKbFdOH+dHu+n+NbGvVBHwX1Rtabaw35AXcLtXkZuBzG0mHzW1HoQ2qOn5Hze4wVS
        l6SOd+EUhb9HJENZjRBmwdiuBv1AGrHBP8HCkMfx3EJL4qS5/G2OZOu3rW/wQkPPyl3X9I
        XxMnShdZgdC29pHCBcl6ae9Z7pTumws=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-356-wsnpYp6oP0Gt_w03dLWVEg-1; Wed, 16 Dec 2020 13:08:36 -0500
X-MC-Unique: wsnpYp6oP0Gt_w03dLWVEg-1
Received: from smtp.corp.redhat.com (int-mx04.intmail.prod.int.phx2.redhat.com
 [10.5.11.14])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id A5253873233;
        Wed, 16 Dec 2020 18:08:35 +0000 (UTC)
Received: from virtlab701.virt.lab.eng.bos.redhat.com
 (virtlab701.virt.lab.eng.bos.redhat.com [10.19.152.228])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 52CF45D9EF;
        Wed, 16 Dec 2020 18:08:35 +0000 (UTC)
From: Paolo Bonzini <pbonzini@redhat.com>
To: linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Cc: thomas.lendacky@amd.com
Subject: [PATCH] KVM: SVM: fix 32-bit compilation
Date: Wed, 16 Dec 2020 13:08:34 -0500
Message-Id: <20201216180834.1466389-1-pbonzini@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.14
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

VCPU_REGS_R8...VCPU_REGS_R15 are not defined on 32-bit x86,
so cull them from the synchronization of the VMSA.

Signed-off-by: Paolo Bonzini <pbonzini@redhat.com>
---
 arch/x86/kvm/svm/sev.c | 2 ++
 1 file changed, 2 insertions(+)

```
#### [RFC][PATCH] jump_label/static_call: Add MAINTAINERS
##### From: Peter Zijlstra <peterz@infradead.org>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Peter Zijlstra <peterz@infradead.org>
X-Patchwork-Id: 11977589
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-15.8 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,
	INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED
	autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id C71B1C2BBCA
	for <kvm@archiver.kernel.org>; Wed, 16 Dec 2020 13:31:24 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 70728233A0
	for <kvm@archiver.kernel.org>; Wed, 16 Dec 2020 13:31:24 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726280AbgLPNbI (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Wed, 16 Dec 2020 08:31:08 -0500
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:59366 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726160AbgLPNbH (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 16 Dec 2020 08:31:07 -0500
Received: from merlin.infradead.org (merlin.infradead.org
 [IPv6:2001:8b0:10b:1231::1])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 4B86DC0617A6;
        Wed, 16 Dec 2020 05:30:27 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; q=dns/txt; c=relaxed/relaxed;
        d=infradead.org; s=merlin.20170209;
 h=In-Reply-To:Content-Type:MIME-Version:
        References:Message-ID:Subject:Cc:To:From:Date:Sender:Reply-To:
        Content-Transfer-Encoding:Content-ID:Content-Description;
        bh=PccmPCCzsl5AXd2yr/SDspnaIQTIwIgNAjEsRYyVJ6Q=;
 b=Fanh4/Ub9cv2qTRs549wIA/XFm
        nsFkkxhxJF9oOyXkZ6Y5Nw6lmYjcYsGH+6UQWQGXjq0If4X3+asMbh6CyjAoW+0L/+rEt89U4s84l
        hJ/E3BpZ0ess6UXAxvif2OTr2cUHHuQe3E79lqU1hApR0Hlq1rUuuffCwtma5QjE/nLnm8QikTm2d
        UpYluT770mBUaoqvr5gTbLR/QlTyg7suE6dGhQlp25NkvQzfSswipXoFm90n0ZHgF+vUd4XcFgQy6
        79nmDNTuCAXfS75zU9OaOJF/DQT+g9wP26sQurerPypVq1cynGofXrSwGRtbIqP6ON+eWEiq9M9S8
        zl0sP8aA==;
Received: from j217100.upc-j.chello.nl ([24.132.217.100]
 helo=noisy.programming.kicks-ass.net)
        by merlin.infradead.org with esmtpsa (Exim 4.92.3 #3 (Red Hat Linux))
        id 1kpWsh-000281-Tu; Wed, 16 Dec 2020 13:30:16 +0000
Received: from hirez.programming.kicks-ass.net
 (hirez.programming.kicks-ass.net [192.168.1.225])
        (using TLSv1.2 with cipher ECDHE-RSA-AES256-GCM-SHA384 (256/256 bits))
        (Client did not present a certificate)
        by noisy.programming.kicks-ass.net (Postfix) with ESMTPS id
 51D58304D58;
        Wed, 16 Dec 2020 14:30:14 +0100 (CET)
Received: by hirez.programming.kicks-ass.net (Postfix, from userid 1000)
        id 2B8B121ADB49F; Wed, 16 Dec 2020 14:30:14 +0100 (CET)
Date: Wed, 16 Dec 2020 14:30:14 +0100
From: Peter Zijlstra <peterz@infradead.org>
To: Dexuan Cui <decui@microsoft.com>
Cc: Ingo Molnar <mingo@kernel.org>,
        Daniel Bristot de Oliveira <bristot@redhat.com>,
        "kvm@vger.kernel.org" <kvm@vger.kernel.org>,
        "linux-kernel@vger.kernel.org" <linux-kernel@vger.kernel.org>,
        jeyu@kernel.org, Josh Poimboeuf <jpoimboe@redhat.com>,
        ardb@kernel.org, Steven Rostedt <rostedt@goodmis.org>,
        Jason Baron <jbaron@akamai.com>
Subject: [RFC][PATCH] jump_label/static_call: Add MAINTAINERS
Message-ID: <20201216133014.GT3092@hirez.programming.kicks-ass.net>
References: 
 <MW4PR21MB1857CC85A6844C89183C93E9BFC59@MW4PR21MB1857.namprd21.prod.outlook.com>
 <20201216092649.GM3040@hirez.programming.kicks-ass.net>
 <20201216105926.GS3092@hirez.programming.kicks-ass.net>
MIME-Version: 1.0
Content-Disposition: inline
In-Reply-To: <20201216105926.GS3092@hirez.programming.kicks-ass.net>
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

FWIW, I recently noticed we're not being Cc'ed on patches for this
stuff, so how about we do something like the below?

Anybody holler if they don't agree with the letter assigned, or if they
feel they've been left out entirely and want in on the 'fun' :-)
Acked-by: Steven Rostedt (VMware) <rostedt@goodmis.org>
Acked-by: Josh Poimboeuf <jpoimboe@redhat.com>
Acked-by: Ard Biesheuvel <ardb@kernel.org>
Acked-by: Jason Baron <jbaron@akamai.com>
---
Subject: jump_label/static_call: Add MAINTAINERS
From: Peter Zijlstra <peterz@infradead.org>

These files don't appear to have a MAINTAINERS entry and as such
patches miss being seen by people who know this code.

Signed-off-by: Peter Zijlstra (Intel) <peterz@infradead.org>
---
 MAINTAINERS |   12 ++++++++++++
```
#### [PATCH v2 2/3] locking/atomic/x86: Introduce arch_try_cmpxchg64()
##### From: Uros Bizjak <ubizjak@gmail.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Uros Bizjak <ubizjak@gmail.com>
X-Patchwork-Id: 11976933
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-15.7 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,DKIM_VALID_AU,FREEMAIL_FORGED_FROMDOMAIN,FREEMAIL_FROM,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED,USER_AGENT_GIT
	autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 890F5C2BBCA
	for <kvm@archiver.kernel.org>; Wed, 16 Dec 2020 08:07:39 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 3DFFF23356
	for <kvm@archiver.kernel.org>; Wed, 16 Dec 2020 08:07:39 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1725807AbgLPIHW (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Wed, 16 Dec 2020 03:07:22 -0500
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:37638 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1725287AbgLPIHW (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 16 Dec 2020 03:07:22 -0500
Received: from mail-ed1-x531.google.com (mail-ed1-x531.google.com
 [IPv6:2a00:1450:4864:20::531])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id B794FC0613D6;
        Wed, 16 Dec 2020 00:06:41 -0800 (PST)
Received: by mail-ed1-x531.google.com with SMTP id r5so23794418eda.12;
        Wed, 16 Dec 2020 00:06:41 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=from:to:cc:subject:date:message-id:mime-version
         :content-transfer-encoding;
        bh=WiqtPjd/js6CZTuGoiZofY3uvp09PMvJ3JUNNxlan84=;
        b=DE5oaqJ3vyS4oiPOJTQmR4NOm/RfY6ZOo4/k5OSR+TR3vDapVHTtEEKisb22SxNTW2
         kKIpcqg7LyLqX72kqPkzH9VkToRm96OYXwmG5Nq8kgf5Am0xZ90Z1zwzlzX2Rpy7OVJa
         feWeYroF2A2IgO9uamM585WQV4BHqJkGRDFYOh1K9yVn5WmTqSne6vx8kLZw8nS2pd46
         sV+8HOO763HfsMK75SQtKObkP/GsawUNdvcln8bL8O/s6WNoA28/o4F4RWDQlbC3jory
         5aeh6/VnRxlQRiZlJt9sfJgwIf6z8xwKOsseYtdnoAIie1UDVzqar/YymWQzXCdvc3+Q
         o38w==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:mime-version
         :content-transfer-encoding;
        bh=WiqtPjd/js6CZTuGoiZofY3uvp09PMvJ3JUNNxlan84=;
        b=C6afoAyNY5xg5sY/C8zrQz6DuWR91zsn+g/Yv/J9e/QMyst+IQPLIzSo7deyiBzC22
         It/FaW+mskRJFJTq1AW8ZTrs97RidWIF/sJIMdlaTW9D8Aocjf9F5eWnqoyBUpJb9yH5
         iKzexre1dinTpBPF0VQIecWdfipdKLtn5SBcnqPThApbUU0cfgtkNHcrzwLkB/MTqvVE
         wj0v7XiREoMxZT8KawSL2+1yzdv0lbmoDbiiukczK27bav77fKkMcM0hGkhCFHYAu0mD
         sQ6QZY1rF8QX5O2xB6a17mpdOXf6madCO26RjGNbjyi6xla641IMxauac7xrOTEie2ff
         iAxA==
X-Gm-Message-State: AOAM5331wg/dYc68qWuxC1E4x5FfZyyYyJfBp4EQ1Y41K42JegXcf1jy
        FOJQ5KCa8RZDsQ4RakA3lbeut5VefNyLJ1Bd
X-Google-Smtp-Source: 
 ABdhPJy2j30t7eDxmfIN066lb8awYMuxtPbkAxdnh5WYjjy5dQDkvCXPcYhas6GNsQ01BdaNpwosgg==
X-Received: by 2002:a05:6402:404:: with SMTP id
 q4mr33389998edv.295.1608106000499;
        Wed, 16 Dec 2020 00:06:40 -0800 (PST)
Received: from localhost.localdomain (93-103-18-160.static.t-2.net.
 [93.103.18.160])
        by smtp.gmail.com with ESMTPSA id
 n20sm798334ejo.83.2020.12.16.00.06.39
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Wed, 16 Dec 2020 00:06:39 -0800 (PST)
From: Uros Bizjak <ubizjak@gmail.com>
To: x86@kernel.org, kvm@vger.kernel.org, linux-kernel@vger.kernel.org
Cc: Uros Bizjak <ubizjak@gmail.com>,
        Thomas Gleixner <tglx@linutronix.de>,
        Ingo Molnar <mingo@redhat.com>, Borislav Petkov <bp@alien8.de>,
        "H. Peter Anvin" <hpa@zytor.com>
Subject: [PATCH v2 2/3] locking/atomic/x86: Introduce arch_try_cmpxchg64()
Date: Wed, 16 Dec 2020 09:05:20 +0100
Message-Id: <20201216080519.55600-1-ubizjak@gmail.com>
X-Mailer: git-send-email 2.26.2
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Add arch_try_cmpxchg64(), similar to arch_try_cmpxchg(), that
operates with 64 bit operands. This function provides the same
interface for 32 bit and 64 bit targets.

v2: Use correct #ifdef.

Signed-off-by: Uros Bizjak <ubizjak@gmail.com>
Cc: Thomas Gleixner <tglx@linutronix.de>
Cc: Ingo Molnar <mingo@redhat.com>
Cc: Borislav Petkov <bp@alien8.de>
Cc: "H. Peter Anvin" <hpa@zytor.com>
---
 arch/x86/include/asm/cmpxchg_32.h | 64 ++++++++++++++++++++++++++-----
 arch/x86/include/asm/cmpxchg_64.h |  6 +++
 2 files changed, 60 insertions(+), 10 deletions(-)

```
