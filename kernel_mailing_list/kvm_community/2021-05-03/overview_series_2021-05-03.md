#### [PATCH] doc/kvm: Fix wrong entry for KVM_CAP_X86_MSR_FILTER
##### From: Siddharth Chandrasekaran <sidcha@amazon.de>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Siddharth Chandrasekaran <sidcha@amazon.de>
X-Patchwork-Id: 12236005
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-19.4 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_CR_TRAILER,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,
	USER_AGENT_GIT autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id EC71CC43460
	for <kvm@archiver.kernel.org>; Mon,  3 May 2021 12:02:12 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id BCED3613CB
	for <kvm@archiver.kernel.org>; Mon,  3 May 2021 12:02:12 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S234186AbhECMDE (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Mon, 3 May 2021 08:03:04 -0400
Received: from smtp-fw-6001.amazon.com ([52.95.48.154]:33992 "EHLO
        smtp-fw-6001.amazon.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S234127AbhECMCU (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 3 May 2021 08:02:20 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
  d=amazon.de; i=@amazon.de; q=dns/txt; s=amazon201209;
  t=1620043287; x=1651579287;
  h=from:to:cc:subject:date:message-id:mime-version;
  bh=9GGmmooWNh5b/DhW7CcR7eCoOpA7l9skAR5JujeFSO8=;
  b=i9DBpAm+FjYrw4Qd3ZTP1rhQKGjGuPkpMzDy0QlNZnDIHf3PiB6zniEf
   SCuxEik7ZRFhS20BPhRDYuUHBE9Kg6MUL7j0kXPvDN+4rgpsIo1cOr0UW
   Mjj8g8mtf27S8/9HWCQ7U6qWheD/+MEZ9yIbVDu+26OtpOfHzXFXdypAA
   Y=;
X-IronPort-AV: E=Sophos;i="5.82,270,1613433600";
   d="scan'208";a="111192371"
Received: from iad12-co-svc-p1-lb1-vlan3.amazon.com (HELO
 email-inbound-relay-2c-2225282c.us-west-2.amazon.com) ([10.43.8.6])
  by smtp-border-fw-6001.iad6.amazon.com with ESMTP;
 03 May 2021 12:01:20 +0000
Received: from EX13D28EUC003.ant.amazon.com
 (pdx1-ws-svc-p6-lb9-vlan3.pdx.amazon.com [10.236.137.198])
        by email-inbound-relay-2c-2225282c.us-west-2.amazon.com (Postfix) with
 ESMTPS id 70AECA1CF5;
        Mon,  3 May 2021 12:01:19 +0000 (UTC)
Received: from uc8bbc9586ea454.ant.amazon.com (10.43.160.119) by
 EX13D28EUC003.ant.amazon.com (10.43.164.43) with Microsoft SMTP Server (TLS)
 id 15.0.1497.2; Mon, 3 May 2021 12:01:15 +0000
From: Siddharth Chandrasekaran <sidcha@amazon.de>
To: Paolo Bonzini <pbonzini@redhat.com>,
        Jonathan Corbet <corbet@lwn.net>,
        Alexander Graf <graf@amazon.com>
CC: Siddharth Chandrasekaran <sidcha@amazon.de>,
        Alexander Graf <graf@amazon.de>, <kvm@vger.kernel.org>,
        <linux-doc@vger.kernel.org>, <linux-kernel@vger.kernel.org>
Subject: [PATCH] doc/kvm: Fix wrong entry for KVM_CAP_X86_MSR_FILTER
Date: Mon, 3 May 2021 14:00:58 +0200
Message-ID: <20210503120059.9283-1-sidcha@amazon.de>
X-Mailer: git-send-email 2.17.1
MIME-Version: 1.0
X-Originating-IP: [10.43.160.119]
X-ClientProxiedBy: EX13D22UWC002.ant.amazon.com (10.43.162.29) To
 EX13D28EUC003.ant.amazon.com (10.43.164.43)
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The capability that exposes new ioctl KVM_X86_SET_MSR_FILTER to
userspace is specified incorrectly as the ioctl itself (instead of
KVM_CAP_X86_MSR_FILTER). This patch fixes it.

Fixes: 1a155254ff93 ("KVM: x86: Introduce MSR filtering")
Cc: Alexander Graf <graf@amazon.de>
Signed-off-by: Siddharth Chandrasekaran <sidcha@amazon.de>
Reviewed-by: Alexander Graf <graf@amazon.com>
---
 Documentation/virt/kvm/api.rst | 4 ++--
 1 file changed, 2 insertions(+), 2 deletions(-)

```
#### [PATCH 1/5] KVM: nSVM: fix a typo in svm_leave_nested
##### From: Maxim Levitsky <mlevitsk@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Maxim Levitsky <mlevitsk@redhat.com>
X-Patchwork-Id: 12236021
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.4 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_CR_TRAILER,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS
	autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 4828CC433B4
	for <kvm@archiver.kernel.org>; Mon,  3 May 2021 12:55:09 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 01D7F61090
	for <kvm@archiver.kernel.org>; Mon,  3 May 2021 12:55:08 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S233943AbhECM4A (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Mon, 3 May 2021 08:56:00 -0400
Received: from us-smtp-delivery-124.mimecast.com ([170.10.133.124]:36429 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S233915AbhECMzz (ORCPT
        <rfc822;kvm@vger.kernel.org>); Mon, 3 May 2021 08:55:55 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1620046501;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding:
         in-reply-to:in-reply-to:references:references;
        bh=mIEpsQd6XZSOwmDS5jk+XOTkhwLc0GrdWpfAAXyyA/g=;
        b=IYhNmoMO2WW1sjYF1Hf+tg192o0fAuZQByuptRLVTDvxbMVhnBGVCcTjKXQjIBLIsez6T8
        eh6lRzrP4t+zbJpCRqSoFC/6FZ5pVbYTI14Z6f3vo5vE88diG/F0fjjxbGDlHwXYEQHFiA
        FX2/iKjsT0hsLF4apCItjmi0903rC+k=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-8-7kkZE34_Pb6zu7pHlgclHw-1; Mon, 03 May 2021 08:54:58 -0400
X-MC-Unique: 7kkZE34_Pb6zu7pHlgclHw-1
Received: from smtp.corp.redhat.com (int-mx02.intmail.prod.int.phx2.redhat.com
 [10.5.11.12])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id DD33E80ED96;
        Mon,  3 May 2021 12:54:56 +0000 (UTC)
Received: from localhost.localdomain (unknown [10.40.193.27])
        by smtp.corp.redhat.com (Postfix) with ESMTP id C3F7CBA6F;
        Mon,  3 May 2021 12:54:52 +0000 (UTC)
From: Maxim Levitsky <mlevitsk@redhat.com>
To: kvm@vger.kernel.org
Cc: Wanpeng Li <wanpengli@tencent.com>,
        Thomas Gleixner <tglx@linutronix.de>,
        linux-kernel@vger.kernel.org (open list:X86 ARCHITECTURE (32-BIT AND
        64-BIT)), Jim Mattson <jmattson@google.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Paolo Bonzini <pbonzini@redhat.com>,
        "H. Peter Anvin" <hpa@zytor.com>, Borislav Petkov <bp@alien8.de>,
        Joerg Roedel <joro@8bytes.org>, Ingo Molnar <mingo@redhat.com>,
        x86@kernel.org (maintainer:X86 ARCHITECTURE (32-BIT AND 64-BIT)),
        Sean Christopherson <seanjc@google.com>,
        Cathy Avery <cavery@redhat.com>,
        Maxim Levitsky <mlevitsk@redhat.com>
Subject: [PATCH 1/5] KVM: nSVM: fix a typo in svm_leave_nested
Date: Mon,  3 May 2021 15:54:42 +0300
Message-Id: <20210503125446.1353307-2-mlevitsk@redhat.com>
In-Reply-To: <20210503125446.1353307-1-mlevitsk@redhat.com>
References: <20210503125446.1353307-1-mlevitsk@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.12
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

When forcibly leaving the nested mode, we should switch to vmcb01

Fixes: 4995a3685f1b ("KVM: SVM: Use a separate vmcb for the nested L2 guest")

Signed-off-by: Maxim Levitsky <mlevitsk@redhat.com>
---
 arch/x86/kvm/svm/nested.c | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
#### [PATCH 1/4] KVM: nVMX: Always make an attempt to map eVMCS after migration
##### From: Vitaly Kuznetsov <vkuznets@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Vitaly Kuznetsov <vkuznets@redhat.com>
X-Patchwork-Id: 12236197
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.4 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_CR_TRAILER,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS
	autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 12D0EC433B4
	for <kvm@archiver.kernel.org>; Mon,  3 May 2021 15:09:13 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id D485961166
	for <kvm@archiver.kernel.org>; Mon,  3 May 2021 15:09:12 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S230186AbhECPKC (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Mon, 3 May 2021 11:10:02 -0400
Received: from us-smtp-delivery-124.mimecast.com ([170.10.133.124]:55437 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S229748AbhECPJ6 (ORCPT
        <rfc822;kvm@vger.kernel.org>); Mon, 3 May 2021 11:09:58 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1620054544;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding:
         in-reply-to:in-reply-to:references:references;
        bh=cEI+4Ic9HJh3gaK26jg1vQpajvtZerh1XHWV7dRvuiw=;
        b=F16A7w4hYPQ23vSPOZ6J5NE4sSkgVX9DtWhuUojZZ0V/sXjpGVe2qNkmTEvNr0BcrPpoHG
        vYHjtYq0C83bIX8qQCNwebe8y6Pa8BBMBNuQOLhgq1w93xE3A5o2uh9f2BV+dpJXJycgwI
        zCnBtbc6SnUOOeCKWPTk42CZaHjWVTQ=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-450-N2C7m98fPEO26AKZEzTm1w-1; Mon, 03 May 2021 11:09:02 -0400
X-MC-Unique: N2C7m98fPEO26AKZEzTm1w-1
Received: from smtp.corp.redhat.com (int-mx08.intmail.prod.int.phx2.redhat.com
 [10.5.11.23])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 8E94D107ACC7;
        Mon,  3 May 2021 15:09:00 +0000 (UTC)
Received: from vitty.brq.redhat.com (unknown [10.40.194.168])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 7C2D719C45;
        Mon,  3 May 2021 15:08:58 +0000 (UTC)
From: Vitaly Kuznetsov <vkuznets@redhat.com>
To: kvm@vger.kernel.org, Paolo Bonzini <pbonzini@redhat.com>
Cc: Sean Christopherson <seanjc@google.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Maxim Levitsky <mlevitsk@redhat.com>,
        linux-kernel@vger.kernel.org
Subject: [PATCH 1/4] KVM: nVMX: Always make an attempt to map eVMCS after
 migration
Date: Mon,  3 May 2021 17:08:51 +0200
Message-Id: <20210503150854.1144255-2-vkuznets@redhat.com>
In-Reply-To: <20210503150854.1144255-1-vkuznets@redhat.com>
References: <20210503150854.1144255-1-vkuznets@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.84 on 10.5.11.23
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

When enlightened VMCS is in use and nested state is migrated with
vmx_get_nested_state()/vmx_set_nested_state() KVM can't map evmcs
page right away: evmcs gpa is not 'struct kvm_vmx_nested_state_hdr'
and we can't read it from VP assist page because userspace may decide
to restore HV_X64_MSR_VP_ASSIST_PAGE after restoring nested state
(and QEMU, for example, does exactly that). To make sure eVMCS is
mapped /vmx_set_nested_state() raises KVM_REQ_GET_NESTED_STATE_PAGES
request.

Commit f2c7ef3ba955 ("KVM: nSVM: cancel KVM_REQ_GET_NESTED_STATE_PAGES
on nested vmexit") added KVM_REQ_GET_NESTED_STATE_PAGES clearing to
nested_vmx_vmexit() to make sure MSR permission bitmap is not switched
when an immediate exit from L2 to L1 happens right after migration (caused
by a pending event, for example). Unfortunately, in the exact same
situation we still need to have eVMCS mapped so
nested_sync_vmcs12_to_shadow() reflects changes in VMCS12 to eVMCS.

As a band-aid, restore nested_get_evmcs_page() when clearing
KVM_REQ_GET_NESTED_STATE_PAGES in nested_vmx_vmexit(). The 'fix' is far
from being ideal as we can't easily propagate possible failures and even if
we could, this is most likely already too late to do so. The whole
'KVM_REQ_GET_NESTED_STATE_PAGES' idea for mapping eVMCS after migration
seems to be fragile as we diverge too much from the 'native' path when
vmptr loading happens on vmx_set_nested_state().

Fixes: f2c7ef3ba955 ("KVM: nSVM: cancel KVM_REQ_GET_NESTED_STATE_PAGES on nested vmexit")
Signed-off-by: Vitaly Kuznetsov <vkuznets@redhat.com>
---
 arch/x86/kvm/vmx/nested.c | 29 +++++++++++++++++++----------
 1 file changed, 19 insertions(+), 10 deletions(-)

```
#### [kvm-unit-tests PATCH] s390x: Fix vector stfle checks
##### From: Janosch Frank <frankja@linux.ibm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Janosch Frank <frankja@linux.ibm.com>
X-Patchwork-Id: 12236015
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.8 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT autolearn=ham
	autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 0C864C433B4
	for <kvm@archiver.kernel.org>; Mon,  3 May 2021 12:47:25 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id ADE1D611EE
	for <kvm@archiver.kernel.org>; Mon,  3 May 2021 12:47:24 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S233723AbhECMsQ (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Mon, 3 May 2021 08:48:16 -0400
Received: from mx0a-001b2d01.pphosted.com ([148.163.156.1]:58724 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S233158AbhECMsQ (ORCPT
        <rfc822;kvm@vger.kernel.org>); Mon, 3 May 2021 08:48:16 -0400
Received: from pps.filterd (m0098394.ppops.net [127.0.0.1])
        by mx0a-001b2d01.pphosted.com (8.16.0.43/8.16.0.43) with SMTP id
 143Chlhu111578
        for <kvm@vger.kernel.org>; Mon, 3 May 2021 08:47:23 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=ibm.com;
 h=from : to : cc : subject
 : date : message-id : mime-version : content-transfer-encoding; s=pp1;
 bh=G2JlGtX2ozq2IpnKeki6I70Y+RDTEp02vJMVP5vsifY=;
 b=lRAiHEKyDCOC1veWRuHxc2x7jUD7YcjdykljC8qAeAbBY76HSLiWjiOslNXcBkILcwbp
 KOoEHa2ZdCV0Lsr0bVDR8RTI7ioLbP6z//zO2YAEQbqrcXUioJWyG0gdf7RaRwWikMnj
 GRlmibzb9JTHMpD+BUz4nixQVGiCBj0XYHrenqPMaby2D6baG3lRZpmOVbXlRde8my3N
 nfHCK6JQcnrQa8gR/AVF2jXSbbCKIRH6S/hXy3WrtJ8TsLpBjsl5g7e+HgYb+bVpo9qf
 p+kIYzX4iJfeLRF7kbzoe/tQgai+o60oBo2ujGDqOns3Ib/M15LBNRWKQK08MOMrsFIn RA==
Received: from pps.reinject (localhost [127.0.0.1])
        by mx0a-001b2d01.pphosted.com with ESMTP id 38ahe803ct-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT)
        for <kvm@vger.kernel.org>; Mon, 03 May 2021 08:47:23 -0400
Received: from m0098394.ppops.net (m0098394.ppops.net [127.0.0.1])
        by pps.reinject (8.16.0.43/8.16.0.43) with SMTP id 143Cj4us118937
        for <kvm@vger.kernel.org>; Mon, 3 May 2021 08:47:22 -0400
Received: from ppma03ams.nl.ibm.com (62.31.33a9.ip4.static.sl-reverse.com
 [169.51.49.98])
        by mx0a-001b2d01.pphosted.com with ESMTP id 38ahe803c1-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Mon, 03 May 2021 08:47:22 -0400
Received: from pps.filterd (ppma03ams.nl.ibm.com [127.0.0.1])
        by ppma03ams.nl.ibm.com (8.16.0.43/8.16.0.43) with SMTP id
 143CVjNf014629;
        Mon, 3 May 2021 12:47:20 GMT
Received: from b06cxnps3074.portsmouth.uk.ibm.com
 (d06relay09.portsmouth.uk.ibm.com [9.149.109.194])
        by ppma03ams.nl.ibm.com with ESMTP id 388xm8gq4f-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Mon, 03 May 2021 12:47:20 +0000
Received: from b06wcsmtp001.portsmouth.uk.ibm.com
 (b06wcsmtp001.portsmouth.uk.ibm.com [9.149.105.160])
        by b06cxnps3074.portsmouth.uk.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id 143ClIow34275684
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Mon, 3 May 2021 12:47:18 GMT
Received: from b06wcsmtp001.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 216CAA4060;
        Mon,  3 May 2021 12:47:18 +0000 (GMT)
Received: from b06wcsmtp001.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id F2DC6A4067;
        Mon,  3 May 2021 12:47:16 +0000 (GMT)
Received: from localhost.localdomain (unknown [9.145.164.58])
        by b06wcsmtp001.portsmouth.uk.ibm.com (Postfix) with ESMTP;
        Mon,  3 May 2021 12:47:16 +0000 (GMT)
From: Janosch Frank <frankja@linux.ibm.com>
To: kvm@vger.kernel.org
Cc: david@redhat.com, thuth@redhat.com, imbrenda@linux.ibm.com,
        cohuck@redhat.com
Subject: [kvm-unit-tests PATCH] s390x: Fix vector stfle checks
Date: Mon,  3 May 2021 12:47:13 +0000
Message-Id: <20210503124713.68975-1-frankja@linux.ibm.com>
X-Mailer: git-send-email 2.27.0
MIME-Version: 1.0
X-TM-AS-GCONF: 00
X-Proofpoint-GUID: G8Fh_NmeRkGTb2GQWQmL_D3j7TkJoRqH
X-Proofpoint-ORIG-GUID: T2oXPk0E59_wCUWwUq2fzKhs7-xA2Oee
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.391,18.0.761
 definitions=2021-05-03_07:2021-05-03,2021-05-03 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 priorityscore=1501
 clxscore=1015 bulkscore=0 phishscore=0 mlxlogscore=999 impostorscore=0
 malwarescore=0 spamscore=0 suspectscore=0 lowpriorityscore=0 mlxscore=0
 adultscore=0 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.12.0-2104060000 definitions=main-2105030087
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

134 is for bcd
135 is for the vector enhancements

Not the other way around...

Signed-off-by: Janosch Frank <frankja@linux.ibm.com>
Suggested-by: David Hildenbrand <david@redhat.com>
Reviewed-by: David Hildenbrand <david@redhat.com>
Reviewed-by: Cornelia Huck <cohuck@redhat.com>
Reviewed-by: Claudio Imbrenda <imbrenda@linux.ibm.com>
---
 s390x/vector.c | 4 ++--
 1 file changed, 2 insertions(+), 2 deletions(-)

```
#### [PATCH] KVM: x86: Hoist input checks in kvm_add_msr_filter()
##### From: Siddharth Chandrasekaran <sidcha@amazon.de>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Siddharth Chandrasekaran <sidcha@amazon.de>
X-Patchwork-Id: 12236009
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-19.4 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_CR_TRAILER,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,
	USER_AGENT_GIT autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 45E75C433ED
	for <kvm@archiver.kernel.org>; Mon,  3 May 2021 12:21:48 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 06222611CE
	for <kvm@archiver.kernel.org>; Mon,  3 May 2021 12:21:47 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S232548AbhECMWk (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Mon, 3 May 2021 08:22:40 -0400
Received: from smtp-fw-9102.amazon.com ([207.171.184.29]:29375 "EHLO
        smtp-fw-9102.amazon.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S230414AbhECMWj (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 3 May 2021 08:22:39 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
  d=amazon.de; i=@amazon.de; q=dns/txt; s=amazon201209;
  t=1620044506; x=1651580506;
  h=from:to:cc:subject:date:message-id:mime-version;
  bh=at0cHJEgodCI3tI7LMoEAMYJODv2kVfd48UoqDPk8F8=;
  b=m2dUjPKc8zrBDVaBR5Mx8HWKvyuGjgmILwJ+oahhcKE9eIbKG2anQkYj
   0J3TGCqOL291i1vbQNPuM1S8TYHW6GBQ8aHczIwrWMTqQrJ8x6i7f19QO
   dSO4crE2FdE+rRfH8C3WfRYNqTgo8WKiLlJ3i4WLnF/MiuUTvg616XH8l
   k=;
X-IronPort-AV: E=Sophos;i="5.82,270,1613433600";
   d="scan'208";a="132584766"
Received: from pdx4-co-svc-p1-lb2-vlan2.amazon.com (HELO
 email-inbound-relay-2b-4ff6265a.us-west-2.amazon.com) ([10.25.36.210])
  by smtp-border-fw-9102.sea19.amazon.com with ESMTP;
 03 May 2021 12:21:39 +0000
Received: from EX13D28EUC003.ant.amazon.com
 (pdx1-ws-svc-p6-lb9-vlan3.pdx.amazon.com [10.236.137.198])
        by email-inbound-relay-2b-4ff6265a.us-west-2.amazon.com (Postfix) with
 ESMTPS id 70C30A216C;
        Mon,  3 May 2021 12:21:35 +0000 (UTC)
Received: from uc8bbc9586ea454.ant.amazon.com (10.43.161.224) by
 EX13D28EUC003.ant.amazon.com (10.43.164.43) with Microsoft SMTP Server (TLS)
 id 15.0.1497.2; Mon, 3 May 2021 12:21:29 +0000
From: Siddharth Chandrasekaran <sidcha@amazon.de>
To: Paolo Bonzini <pbonzini@redhat.com>,
        Sean Christopherson <seanjc@google.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>,
        Thomas Gleixner <tglx@linutronix.de>,
        Ingo Molnar <mingo@redhat.com>, Borislav Petkov <bp@alien8.de>,
        <x86@kernel.org>, "H. Peter Anvin" <hpa@zytor.com>
CC: Siddharth Chandrasekaran <sidcha@amazon.de>, <kvm@vger.kernel.org>,
        <linux-kernel@vger.kernel.org>
Subject: [PATCH] KVM: x86: Hoist input checks in kvm_add_msr_filter()
Date: Mon, 3 May 2021 14:21:11 +0200
Message-ID: <20210503122111.13775-1-sidcha@amazon.de>
X-Mailer: git-send-email 2.17.1
MIME-Version: 1.0
X-Originating-IP: [10.43.161.224]
X-ClientProxiedBy: EX13D21UWB004.ant.amazon.com (10.43.161.221) To
 EX13D28EUC003.ant.amazon.com (10.43.164.43)
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

In ioctl KVM_X86_SET_MSR_FILTER, input from user space is validated
after a memdup_user(). For invalid inputs we'd memdup and then call
kfree unnecessarily. Hoist input validation to avoid kfree altogether.

Signed-off-by: Siddharth Chandrasekaran <sidcha@amazon.de>
Reviewed-by: Sean Christopherson <seanjc@google.com>
---
 arch/x86/kvm/x86.c | 21 ++++++---------------
 1 file changed, 6 insertions(+), 15 deletions(-)

```
#### [PATCH] KVM: x86/mmu: Fix kdoc of __handle_changed_spte
##### From: Kai Huang <kai.huang@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Kai Huang <kai.huang@intel.com>
X-Patchwork-Id: 12235655
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.8 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED,USER_AGENT_GIT
	autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 91895C433ED
	for <kvm@archiver.kernel.org>; Mon,  3 May 2021 04:24:57 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 5F75661362
	for <kvm@archiver.kernel.org>; Mon,  3 May 2021 04:24:57 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S229499AbhECEZs (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Mon, 3 May 2021 00:25:48 -0400
Received: from mga11.intel.com ([192.55.52.93]:48931 "EHLO mga11.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S229457AbhECEZs (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 3 May 2021 00:25:48 -0400
IronPort-SDR: 
 xiururXPWFozdSoxHiLg3zKgqbKxxtKIpRbbB+vMvsa4vR5iB4vhOiKE8gyZqsEJBm8mxsQVTI
 V5vsmvWOf+vw==
X-IronPort-AV: E=McAfee;i="6200,9189,9972"; a="194518684"
X-IronPort-AV: E=Sophos;i="5.82,268,1613462400";
   d="scan'208";a="194518684"
Received: from orsmga008.jf.intel.com ([10.7.209.65])
  by fmsmga102.fm.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 02 May 2021 21:24:55 -0700
IronPort-SDR: 
 KIJH8VpNWhrENTHmKsHK58xrxeY39KQE4QYn/+G/CtU/nR5k0ycc01QLEkgwsnFg76rBzDYw5X
 JOi0thy+gKwQ==
X-IronPort-AV: E=Sophos;i="5.82,268,1613462400";
   d="scan'208";a="432522639"
Received: from jsarvent-desk.amr.corp.intel.com (HELO
 khuang2-desk.gar.corp.intel.com) ([10.212.135.231])
  by orsmga008-auth.jf.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 02 May 2021 21:24:53 -0700
From: Kai Huang <kai.huang@intel.com>
To: kvm@vger.kernel.org
Cc: pbonzini@redhat.com, bgardon@google.com, seanjc@google.com,
        vkuznets@redhat.com, wanpengli@tencent.com, jmattson@google.com,
        joro@8bytes.org, Kai Huang <kai.huang@intel.com>
Subject: [PATCH] KVM: x86/mmu: Fix kdoc of __handle_changed_spte
Date: Mon,  3 May 2021 16:24:46 +1200
Message-Id: <20210503042446.154695-1-kai.huang@intel.com>
X-Mailer: git-send-email 2.31.1
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The function name of kdoc of __handle_changed_spte() should be itself,
rather than handle_changed_spte().  Fix the typo.

Signed-off-by: Kai Huang <kai.huang@intel.com>
---
 arch/x86/kvm/mmu/tdp_mmu.c | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
