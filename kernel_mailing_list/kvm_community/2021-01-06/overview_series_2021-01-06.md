#### [PATCH v4 01/16] KVM: x86/xen: fix Xen hypercall page msr handling
##### From: David Woodhouse <dwmw2@infradead.org>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: David Woodhouse <dwmw2@infradead.org>
X-Patchwork-Id: 12000615
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-18.8 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,
	INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT
	autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 22A1CC433E0
	for <kvm@archiver.kernel.org>; Wed,  6 Jan 2021 00:25:40 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id D72AC22D74
	for <kvm@archiver.kernel.org>; Wed,  6 Jan 2021 00:25:39 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726567AbhAFAZi (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 5 Jan 2021 19:25:38 -0500
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:37522 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726328AbhAFAZi (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 5 Jan 2021 19:25:38 -0500
Received: from casper.infradead.org (casper.infradead.org
 [IPv6:2001:8b0:10b:1236::1])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 3D539C06179E
        for <kvm@vger.kernel.org>; Tue,  5 Jan 2021 16:24:58 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; q=dns/txt; c=relaxed/relaxed;
        d=infradead.org; s=casper.20170209;
 h=Sender:Content-Transfer-Encoding:
        MIME-Version:References:In-Reply-To:Message-Id:Date:Subject:Cc:To:From:
        Reply-To:Content-Type:Content-ID:Content-Description;
        bh=rNJwjPQ7Qc7Ainnec/slAm+3+N/HJjvYoiheRUN6QLg=;
 b=adf91Pk9fRFB2a8juCO2Yx47kB
        Z5D1EuzrSSaqC+lmkjGkMkYSlZdX9cYOo0PdruMpZq9FAj94HczGTZKX9eK6RxX5VdoV09sJDrWqH
        u6N5z4P73xA90ORtJklkVgZEuV1kqPeVGGUY/gYS34c45sMPU/aD8FmUfP34lWxdJz7XHkgoaz/JM
        9kmJhOTdxZS9FStc9Sr0lEEi0f5TsedLW5zkYLvUCoMlz3PwzsV8EmwdjjwwhRYdxqpd6NY/qrB/r
        dn9w5P1vbS4TjCJ1WxgoCfaPyX2f0CveJp9PQ0YZIEQXTvGAQe+BD65QbP7bUz/fuFhI97eJP8tYK
        vZqSTvzA==;
Received: from i7.infradead.org ([2001:8b0:10b:1:21e:67ff:fecb:7a92])
        by casper.infradead.org with esmtpsa (Exim 4.94 #2 (Red Hat Linux))
        id 1kwwbh-001pA4-LS; Wed, 06 Jan 2021 00:23:36 +0000
Received: from dwoodhou by i7.infradead.org with local (Exim 4.94 #2 (Red Hat
 Linux))
        id 1kwwbh-001Nin-9W; Wed, 06 Jan 2021 00:23:21 +0000
From: David Woodhouse <dwmw2@infradead.org>
To: kvm@vger.kernel.org
Cc: Paolo Bonzini <pbonzini@redhat.com>,
        Ankur Arora <ankur.a.arora@oracle.com>,
        Joao Martins <joao.m.martins@oracle.com>,
        Boris Ostrovsky <boris.ostrovsky@oracle.com>,
        Sean Christopherson <seanjc@google.com>, graf@amazon.com,
        iaslan@amazon.de, pdurrant@amazon.com, aagch@amazon.com,
        fandree@amazon.com, hch@infradead.org
Subject: [PATCH v4 01/16] KVM: x86/xen: fix Xen hypercall page msr handling
Date: Wed,  6 Jan 2021 00:22:59 +0000
Message-Id: <20210106002314.328380-2-dwmw2@infradead.org>
X-Mailer: git-send-email 2.29.2
In-Reply-To: <20210106002314.328380-1-dwmw2@infradead.org>
References: <20210106002314.328380-1-dwmw2@infradead.org>
MIME-Version: 1.0
Sender: David Woodhouse <dwmw2@infradead.org>
X-SRS-Rewrite: SMTP reverse-path rewritten from <dwmw2@infradead.org> by
 casper.infradead.org. See http://www.infradead.org/rpr.html
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Joao Martins <joao.m.martins@oracle.com>

Xen usually places its MSR at 0x40000000 or 0x40000200 depending on
whether it is running in viridian mode or not. Note that this is not
ABI guaranteed, so it is possible for Xen to advertise the MSR some
place else.

Given the way xen_hvm_config() is handled, if the former address is
selected, this will conflict with Hyper-V's MSR
(HV_X64_MSR_GUEST_OS_ID) which unconditionally uses the same address.

Given that the MSR location is arbitrary, move the xen_hvm_config()
handling to the top of kvm_set_msr_common() before falling through.

Signed-off-by: Joao Martins <joao.m.martins@oracle.com>
Signed-off-by: David Woodhouse <dwmw@amazon.co.uk>
---
 arch/x86/kvm/x86.c | 5 +++--
 1 file changed, 3 insertions(+), 2 deletions(-)

```
#### [PATCH 1/6] KVM: SVM: create svm_process_injected_event
##### From: Maxim Levitsky <mlevitsk@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Maxim Levitsky <mlevitsk@redhat.com>
X-Patchwork-Id: 12001335
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.0 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_CR_TRAILER,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS
	autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id D86E7C43381
	for <kvm@archiver.kernel.org>; Wed,  6 Jan 2021 10:52:12 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id BB1DC2310E
	for <kvm@archiver.kernel.org>; Wed,  6 Jan 2021 10:52:12 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726753AbhAFKvr (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Wed, 6 Jan 2021 05:51:47 -0500
Received: from us-smtp-delivery-124.mimecast.com ([216.205.24.124]:58558 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1726660AbhAFKvq (ORCPT
        <rfc822;kvm@vger.kernel.org>); Wed, 6 Jan 2021 05:51:46 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1609930219;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding:
         in-reply-to:in-reply-to:references:references;
        bh=uVVaAXkGgO4GgKOX11xqpYlF88SD+dCjinIgZUO1i3Y=;
        b=YuKI3QUdUHL9MCirEIPZT4ExPrzAsDPneK5BCClUXvbjnxo/O7BC5GsC72V1kFs5/1d5gq
        mtAKEPKCuY5f1RP8trMbP/eUhgq8QV+hD3Cf0LzRaMjALDZCKELEfyJgpzq88UkueHfD+Y
        /rTXzSZq3aa3tJz3ykaWbOxqHC8IjDU=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-419-dv_TR8n5OKudYvjPd54RuA-1; Wed, 06 Jan 2021 05:50:14 -0500
X-MC-Unique: dv_TR8n5OKudYvjPd54RuA-1
Received: from smtp.corp.redhat.com (int-mx05.intmail.prod.int.phx2.redhat.com
 [10.5.11.15])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 106E21005504;
        Wed,  6 Jan 2021 10:50:13 +0000 (UTC)
Received: from localhost.localdomain (unknown [10.35.206.196])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 8942537A0;
        Wed,  6 Jan 2021 10:50:09 +0000 (UTC)
From: Maxim Levitsky <mlevitsk@redhat.com>
To: kvm@vger.kernel.org
Cc: Ingo Molnar <mingo@redhat.com>,
        Thomas Gleixner <tglx@linutronix.de>,
        Paolo Bonzini <pbonzini@redhat.com>,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        linux-kernel@vger.kernel.org (open list:X86 ARCHITECTURE (32-BIT AND
        64-BIT)), Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>,
        x86@kernel.org (maintainer:X86 ARCHITECTURE (32-BIT AND 64-BIT)),
        Wanpeng Li <wanpengli@tencent.com>,
        "H. Peter Anvin" <hpa@zytor.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Borislav Petkov <bp@alien8.de>,
        Maxim Levitsky <mlevitsk@redhat.com>
Subject: [PATCH 1/6] KVM: SVM: create svm_process_injected_event
Date: Wed,  6 Jan 2021 12:49:56 +0200
Message-Id: <20210106105001.449974-2-mlevitsk@redhat.com>
In-Reply-To: <20210106105001.449974-1-mlevitsk@redhat.com>
References: <20210106105001.449974-1-mlevitsk@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.15
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Refactor the logic that is dealing with parsing of an injected event to a
separate function.

This will be used in the next patch to deal with the events that L1 wants to
inject to L2 in a way that survives migration.

Signed-off-by: Maxim Levitsky <mlevitsk@redhat.com>
---
 arch/x86/kvm/svm/svm.c | 58 ++++++++++++++++++++++++------------------
 arch/x86/kvm/svm/svm.h |  4 +++
 2 files changed, 37 insertions(+), 25 deletions(-)

```
#### [RFC PATCH 01/23] x86/sgx: Split out adding EPC page to free list to separate helper
##### From: Kai Huang <kai.huang@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Kai Huang <kai.huang@intel.com>
X-Patchwork-Id: 12000759
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.8 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED,USER_AGENT_GIT
	autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id DFBE9C433E0
	for <kvm@archiver.kernel.org>; Wed,  6 Jan 2021 01:56:18 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id A34C322D71
	for <kvm@archiver.kernel.org>; Wed,  6 Jan 2021 01:56:18 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726029AbhAFB4R (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 5 Jan 2021 20:56:17 -0500
Received: from mga04.intel.com ([192.55.52.120]:11750 "EHLO mga04.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1725991AbhAFB4P (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 5 Jan 2021 20:56:15 -0500
IronPort-SDR: 
 j8++Y5gcD8DhUouN2EkgvIsHKZBE9afid1cm66o3WAYs0pr7DlUox97pkL10dzM00+Uvf3SmPt
 dWN8hwFxSkaA==
X-IronPort-AV: E=McAfee;i="6000,8403,9855"; a="174636859"
X-IronPort-AV: E=Sophos;i="5.78,478,1599548400";
   d="scan'208";a="174636859"
Received: from orsmga001.jf.intel.com ([10.7.209.18])
  by fmsmga104.fm.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 05 Jan 2021 17:55:34 -0800
IronPort-SDR: 
 zzZHf8ZpO19nr6pSnmuXc4yIuSX7Vzd5U0z4IcFkqGWfumHItMf1gL4te+G8RkQ+YXKwHRsuO/
 mFtmXXZw07rA==
X-IronPort-AV: E=Sophos;i="5.78,478,1599548400";
   d="scan'208";a="421993126"
Received: from zhuoxuan-mobl.amr.corp.intel.com (HELO
 khuang2-desk.gar.corp.intel.com) ([10.251.29.237])
  by orsmga001-auth.jf.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 05 Jan 2021 17:55:30 -0800
From: Kai Huang <kai.huang@intel.com>
To: linux-sgx@vger.kernel.org, kvm@vger.kernel.org, x86@kernel.org
Cc: seanjc@google.com, jarkko@kernel.org, luto@kernel.org,
        dave.hansen@intel.com, haitao.huang@intel.com, pbonzini@redhat.com,
        bp@alien8.de, tglx@linutronix.de, mingo@redhat.com, hpa@zytor.com,
        Kai Huang <kai.huang@intel.com>
Subject: [RFC PATCH 01/23] x86/sgx: Split out adding EPC page to free list to
 separate helper
Date: Wed,  6 Jan 2021 14:55:18 +1300
Message-Id: 
 <3d50c2614ff8a46b44062a398fd8644bcda92132.1609890536.git.kai.huang@intel.com>
X-Mailer: git-send-email 2.29.2
In-Reply-To: <cover.1609890536.git.kai.huang@intel.com>
References: <cover.1609890536.git.kai.huang@intel.com>
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Sean Christopherson <sean.j.christopherson@intel.com>

SGX virtualization requires to allocate "raw" EPC and use it as virtual
EPC for SGX guest.  Unlike EPC used by SGX driver, virtual EPC doesn't
track how EPC pages are used in VM, e.g. (de)construction of enclaves,
so it cannot guarantee EREMOVE success, e.g. it doesn't have a priori
knowledge of which pages are SECS with non-zero child counts.

Split sgx_free_page() into two parts so that the "add to free list"
part can be used by virtual EPC without having to modify the EREMOVE
logic in sgx_free_page().

Signed-off-by: Sean Christopherson <sean.j.christopherson@intel.com>
Signed-off-by: Kai Huang <kai.huang@intel.com>
---
 arch/x86/kernel/cpu/sgx/main.c | 24 ++++++++++++++++++------
 arch/x86/kernel/cpu/sgx/sgx.h  |  1 +
 2 files changed, 19 insertions(+), 6 deletions(-)

```
#### [PATCH] MAINTAINERS: Really update email address for Sean Christopherson
##### From: Sean Christopherson <seanjc@google.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Sean Christopherson <seanjc@google.com>
X-Patchwork-Id: 12002069
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-26.6 required=3.0 tests=BAYES_00,DKIMWL_WL_MED,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_CR_TRAILER,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,
	URIBL_BLOCKED,USER_AGENT_GIT,USER_IN_DEF_DKIM_WL autolearn=unavailable
	autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id AF902C433E0
	for <kvm@archiver.kernel.org>; Wed,  6 Jan 2021 18:30:25 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 8A4E72312A
	for <kvm@archiver.kernel.org>; Wed,  6 Jan 2021 18:30:25 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726435AbhAFSaE (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Wed, 6 Jan 2021 13:30:04 -0500
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:38232 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726249AbhAFSaE (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 6 Jan 2021 13:30:04 -0500
Received: from mail-yb1-xb4a.google.com (mail-yb1-xb4a.google.com
 [IPv6:2607:f8b0:4864:20::b4a])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id F20D4C06134C
        for <kvm@vger.kernel.org>; Wed,  6 Jan 2021 10:29:23 -0800 (PST)
Received: by mail-yb1-xb4a.google.com with SMTP id b131so5512788ybc.3
        for <kvm@vger.kernel.org>; Wed, 06 Jan 2021 10:29:23 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=sender:reply-to:date:message-id:mime-version:subject:from:to:cc;
        bh=vqdOFJEXH8f+fWCwR3dVWB92iRCynRAkA1NtJxXRz/A=;
        b=YLTV+pfKZtX4PnvgyYfIm7AKkd+zJg6rQm0hn3UsJKVjIVUqVkobDIO4IiP3t3uAD3
         kZncdvXLNjVrvLkj9sin8sPSyAzP3XzgergppzkoKUIlymdw1zHGmWNCrF7qFJJ33ut7
         PBma0K+U9lS/Q6lVYkJBpgFKEBHPoJBLFVJsptKWGFw7r3Arac0hlvZvA9jgUZC7lg+c
         quaw6kejs2qmJhrvGePvuta/IjVaKQd2Z5f5/9fFEWCj1Xusvp+aVQkty6wC1f2iWUfB
         OMMbyazcLEzq6hHKPTYdBmdbQC7ImUf6URxaNyjNguX5oNwrzx1b6sJdB8ZFZ7hOdMnO
         gUkw==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:sender:reply-to:date:message-id:mime-version
         :subject:from:to:cc;
        bh=vqdOFJEXH8f+fWCwR3dVWB92iRCynRAkA1NtJxXRz/A=;
        b=KTxn9AJbvgCH+3AEhJflwYCq36+6/WVWE2tN02/d+rhT7QSk2Q5/s2nNyJMGJUMjmG
         42cUbN8/o9GyTgjpKw35jjb4+XTvtfsooWoTI/asOZrknOkHM1jF0EtqHdkkHV17s2Mx
         A8OPtY272pWuCrnRcOIDnuoO9KuwB6kHfwnzO/49A5j4S/CCA+fTAi8o8ZE+IMphjo9d
         RYNSQ02sVtnqbR2QiwKnTVy1oXxHiNIxRZl8kS8gy+VUXm93OkMQCMkrz6jE6xNAT75j
         ygLkD/jFYXnYFLOF1zi0h9hiIc9v//DT5Jo11zN+SWbhkSAeIYxBPgdxkA7XPONgMKvm
         ehGw==
X-Gm-Message-State: AOAM530Jx/79NnS5m89CBSseFG4FK2xnqXX+ZaEv9uPmxaz8sxMgVYW9
        ER5OWQgTJ5VflC7Vt0zd7jHjMgzi4K8=
X-Google-Smtp-Source: 
 ABdhPJy5Nk7Cr77AbZRfg3A9DCxnmvwiVFW2DlCrmtDO9UTWOO6MrKn3bHVaX4hQ2C/j3ZhAmWVRREMR2ac=
Sender: "seanjc via sendgmr" <seanjc@seanjc798194.pdx.corp.google.com>
X-Received: from seanjc798194.pdx.corp.google.com
 ([2620:15c:f:10:1ea0:b8ff:fe73:50f5])
 (user=seanjc job=sendgmr) by 2002:a25:6981:: with SMTP id
 e123mr8170015ybc.194.1609957763232;
 Wed, 06 Jan 2021 10:29:23 -0800 (PST)
Reply-To: Sean Christopherson <seanjc@google.com>
Date: Wed,  6 Jan 2021 10:29:16 -0800
Message-Id: <20210106182916.331743-1-seanjc@google.com>
Mime-Version: 1.0
X-Mailer: git-send-email 2.29.2.729.g45daf8777d-goog
Subject: [PATCH] MAINTAINERS: Really update email address for Sean
 Christopherson
From: Sean Christopherson <seanjc@google.com>
To: Paolo Bonzini <pbonzini@redhat.com>
Cc: linux-kernel@vger.kernel.org, kvm@vger.kernel.org,
        Nathan Chancellor <natechancellor@gmail.com>,
        Sean Christopherson <seanjc@google.com>
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Use my @google.com address in MAINTAINERS, somehow only the .mailmap
entry was added when the original update patch was applied.

Fixes: c2b1209d852f ("MAINTAINERS: Update email address for Sean Christopherson")
Cc: kvm@vger.kernel.org
Reported-by: Nathan Chancellor <natechancellor@gmail.com>
Signed-off-by: Sean Christopherson <seanjc@google.com>
---
 MAINTAINERS | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
#### [RFC PATCH v2 1/1] platform-msi: Add platform check for subdevice irq domain
##### From: Lu Baolu <baolu.lu@linux.intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Lu Baolu <baolu.lu@linux.intel.com>
X-Patchwork-Id: 12000841
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.8 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED,USER_AGENT_GIT
	autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 56048C433E0
	for <kvm@archiver.kernel.org>; Wed,  6 Jan 2021 02:38:05 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 1846822CB1
	for <kvm@archiver.kernel.org>; Wed,  6 Jan 2021 02:38:05 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726008AbhAFCho (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 5 Jan 2021 21:37:44 -0500
Received: from mga18.intel.com ([134.134.136.126]:55722 "EHLO mga18.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1725730AbhAFCho (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 5 Jan 2021 21:37:44 -0500
IronPort-SDR: 
 kjHKXhCRDBTJ6MEhdNrU8lgMsg5I8RiCtrMzPMId+nWQx4mD5VCSXUzv3k/bH/eOkNm66IZXzT
 geCa9kY+rvIQ==
X-IronPort-AV: E=McAfee;i="6000,8403,9855"; a="164916478"
X-IronPort-AV: E=Sophos;i="5.78,478,1599548400";
   d="scan'208";a="164916478"
Received: from fmsmga002.fm.intel.com ([10.253.24.26])
  by orsmga106.jf.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 05 Jan 2021 18:35:58 -0800
IronPort-SDR: 
 l8eZWSbUu3gwxGLlJVi+r6FoPsncy+NcV1PA5yxUi50xwIoJFgzmBu5gPx8BBeNYoGWRq8fPym
 bAJELIHMJ4RQ==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.78,478,1599548400";
   d="scan'208";a="398061314"
Received: from allen-box.sh.intel.com ([10.239.159.28])
  by fmsmga002.fm.intel.com with ESMTP; 05 Jan 2021 18:35:51 -0800
From: Lu Baolu <baolu.lu@linux.intel.com>
To: tglx@linutronix.de, ashok.raj@intel.com, kevin.tian@intel.com,
        dave.jiang@intel.com, megha.dey@intel.com, dwmw2@infradead.org
Cc: alex.williamson@redhat.com, bhelgaas@google.com,
        dan.j.williams@intel.com, dmaengine@vger.kernel.org,
        eric.auger@redhat.com, jacob.jun.pan@intel.com, jgg@mellanox.com,
        kvm@vger.kernel.org, kwankhede@nvidia.com,
        linux-kernel@vger.kernel.org, linux-pci@vger.kernel.org,
        maz@kernel.org, mona.hossain@intel.com, netanelg@mellanox.com,
        parav@mellanox.com, pbonzini@redhat.com, rafael@kernel.org,
        samuel.ortiz@intel.com, sanjay.k.kumar@intel.com,
        shahafs@mellanox.com, tony.luck@intel.com, vkoul@kernel.org,
        yan.y.zhao@linux.intel.com, yi.l.liu@intel.com,
        Lu Baolu <baolu.lu@linux.intel.com>
Subject: [RFC PATCH v2 1/1] platform-msi: Add platform check for subdevice irq
 domain
Date: Wed,  6 Jan 2021 10:27:49 +0800
Message-Id: <20210106022749.2769057-1-baolu.lu@linux.intel.com>
X-Mailer: git-send-email 2.25.1
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The pci_subdevice_msi_create_irq_domain() should fail if the underlying
platform is not able to support IMS (Interrupt Message Storage). Otherwise,
the isolation of interrupt is not guaranteed.

For x86, IMS is only supported on bare metal for now. We could enable it
in the virtualization environments in the future if interrupt HYPERCALL
domain is supported or the hardware has the capability of interrupt
isolation for subdevices.

Suggested-by: Thomas Gleixner <tglx@linutronix.de>
Link: https://lore.kernel.org/linux-pci/87pn4nk7nn.fsf@nanos.tec.linutronix.de/
Link: https://lore.kernel.org/linux-pci/877dqrnzr3.fsf@nanos.tec.linutronix.de/
Link: https://lore.kernel.org/linux-pci/877dqqmc2h.fsf@nanos.tec.linutronix.de/
Signed-off-by: Lu Baolu <baolu.lu@linux.intel.com>
---
 arch/x86/pci/common.c       | 47 +++++++++++++++++++++++++++++++++++++
 drivers/base/platform-msi.c |  8 +++++++
 include/linux/msi.h         |  1 +
 3 files changed, 56 insertions(+)


Background:
Learnt from the discussions in this thread:

https://lore.kernel.org/linux-pci/160408357912.912050.17005584526266191420.stgit@djiang5-desk3.ch.intel.com/

The device IMS (Interrupt Message Storage) should not be enabled in any
virtualization environments unless there is a HYPERCALL domain which
makes the changes in the message store managed by the hypervisor.

As the initial step, we allow the IMS to be enabled only if we are
running on the bare metal. It's easy to enable IMS in the virtualization
environments if above preconditions are met in the future.

We ever thought about moving on_bare_metal() to a generic file so that
it could be well maintained and used. But we need some suggestions about
where to put it. Your comments are very appreciated.

This patch is only for comments purpose. Please don't merge it. We will
include it in the Intel IMS implementation later once we reach a
consensus.

Change log:
v1->v2:
 - v1:
   https://lore.kernel.org/linux-pci/20201210004624.345282-1-baolu.lu@linux.intel.com/
 - Rename probably_on_bare_metal() with on_bare_metal();
 - Some vendors might use the same name for both bare metal and virtual
   environment. Before we add vendor specific code to distinguish
   between them, let's return false in on_bare_metal(). This won't
   introduce any regression. The only impact is that the coming new
   platform msi feature won't be supported until the vendor specific code
   is provided.

Best regards,
baolu

```
#### [PATCH 1/2] KVM: VMX: create vmx_process_injected_event
##### From: Maxim Levitsky <mlevitsk@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Maxim Levitsky <mlevitsk@redhat.com>
X-Patchwork-Id: 12001347
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.0 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_CR_TRAILER,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS
	autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id B769FC433E6
	for <kvm@archiver.kernel.org>; Wed,  6 Jan 2021 10:54:58 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 8217C2311C
	for <kvm@archiver.kernel.org>; Wed,  6 Jan 2021 10:54:58 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726125AbhAFKyr (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Wed, 6 Jan 2021 05:54:47 -0500
Received: from us-smtp-delivery-124.mimecast.com ([63.128.21.124]:41589 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1727214AbhAFKyq (ORCPT
        <rfc822;kvm@vger.kernel.org>); Wed, 6 Jan 2021 05:54:46 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1609930399;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding:
         in-reply-to:in-reply-to:references:references;
        bh=A4ueySyqGVeSAb89GWtUcgfgaOdq5moM0rQARjz9DME=;
        b=U9LSBARwezH1wyts7mSDSrlw/CzOcVc75t5f1uOzdiG8qxvXVxDHGAwNxqVSjyO+juDBa5
        AlYyCIoVA6DJIfV2potCCqw28eGi3/iqVS865BHsUa2Xta2zDsPVJErIvJsPfDTTUsVLuH
        X/6NMIaX+t6TO64LrCkAMTCSld8aEIA=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-566-7ffn7EJ9PRmCG3wWACufMQ-1; Wed, 06 Jan 2021 05:53:18 -0500
X-MC-Unique: 7ffn7EJ9PRmCG3wWACufMQ-1
Received: from smtp.corp.redhat.com (int-mx01.intmail.prod.int.phx2.redhat.com
 [10.5.11.11])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 4709D1926DA2;
        Wed,  6 Jan 2021 10:53:16 +0000 (UTC)
Received: from localhost.localdomain (unknown [10.35.206.196])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 998715B4A9;
        Wed,  6 Jan 2021 10:53:12 +0000 (UTC)
From: Maxim Levitsky <mlevitsk@redhat.com>
To: kvm@vger.kernel.org
Cc: Joerg Roedel <joro@8bytes.org>, Wanpeng Li <wanpengli@tencent.com>,
        linux-kernel@vger.kernel.org (open list:X86 ARCHITECTURE (32-BIT AND
        64-BIT)),
        x86@kernel.org (maintainer:X86 ARCHITECTURE (32-BIT AND 64-BIT)),
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        "H. Peter Anvin" <hpa@zytor.com>,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        Paolo Bonzini <pbonzini@redhat.com>,
        Ingo Molnar <mingo@redhat.com>, Borislav Petkov <bp@alien8.de>,
        Jim Mattson <jmattson@google.com>,
        Thomas Gleixner <tglx@linutronix.de>,
        Maxim Levitsky <mlevitsk@redhat.com>
Subject: [PATCH 1/2] KVM: VMX: create vmx_process_injected_event
Date: Wed,  6 Jan 2021 12:53:05 +0200
Message-Id: <20210106105306.450602-2-mlevitsk@redhat.com>
In-Reply-To: <20210106105306.450602-1-mlevitsk@redhat.com>
References: <20210106105306.450602-1-mlevitsk@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.11
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Refactor the logic that is dealing with parsing of an injected event to a
separate function.

This will be used in the next patch to deal with the events that L1 wants to
inject to L2 in a way that survives migration.

Signed-off-by: Maxim Levitsky <mlevitsk@redhat.com>
---
 arch/x86/kvm/vmx/vmx.c | 60 ++++++++++++++++++++++++++----------------
 arch/x86/kvm/vmx/vmx.h |  4 +++
 2 files changed, 41 insertions(+), 23 deletions(-)

```
#### [PATCH v2 1/2] KVM: x86/mmu: Ensure TDP MMU roots are freed after yield
##### From: Ben Gardon <bgardon@google.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Ben Gardon <bgardon@google.com>
X-Patchwork-Id: 12002105
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-26.6 required=3.0 tests=BAYES_00,DKIMWL_WL_MED,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_CR_TRAILER,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,
	USER_AGENT_GIT,USER_IN_DEF_DKIM_WL autolearn=unavailable autolearn_force=no
	version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 00F69C433DB
	for <kvm@archiver.kernel.org>; Wed,  6 Jan 2021 19:00:59 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id BF2E62312F
	for <kvm@archiver.kernel.org>; Wed,  6 Jan 2021 19:00:58 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726405AbhAFTAg (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Wed, 6 Jan 2021 14:00:36 -0500
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:43100 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1725803AbhAFTAf (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 6 Jan 2021 14:00:35 -0500
Received: from mail-pg1-x549.google.com (mail-pg1-x549.google.com
 [IPv6:2607:f8b0:4864:20::549])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id C98C9C061575
        for <kvm@vger.kernel.org>; Wed,  6 Jan 2021 10:59:55 -0800 (PST)
Received: by mail-pg1-x549.google.com with SMTP id 26so2594672pgl.2
        for <kvm@vger.kernel.org>; Wed, 06 Jan 2021 10:59:55 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=sender:date:message-id:mime-version:subject:from:to:cc;
        bh=VJVLSLdtxSjf51v52sLnCTCAPMVR3FicOzzHbZ1zDdk=;
        b=ZKYZc57KqCVwsRiFhOTTFLdKMqgTg5ofcjrSGRQ7puNhLXoQZpZg71cq/Ep5JpXzg9
         Mwpy3zp4bvNPoFoTfP8ExyqKtwCG3kn/DrZy6MTd7TQ3QZlmaqYhHxbal1WkVHE02bWw
         ROSDeUCD4XZX/oGYdQMM0aEcKfFog6yT5qQ8V4/P8W4SY1rnYSw2bN/4dKQgGlVu+OQ3
         SOxj7YLCPI5VarLLPN7D0Myvy6UgRUFAgpLSmO1mOTV8pLdoVkjZzPVLf4NTkfvfNMgB
         Cvf4ctTcL6+h/bFShidIfdDZ5o2/KGG8SZAhB+uUc1CUhWR4J1rf8otMP2nRxzz69rHJ
         hK/Q==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:sender:date:message-id:mime-version:subject:from
         :to:cc;
        bh=VJVLSLdtxSjf51v52sLnCTCAPMVR3FicOzzHbZ1zDdk=;
        b=N07iK2fTtVmaj3q8++nE1ld317jyQQRbznstMav7KJFVUu+jTKLRslPLJ/4npphxe0
         TWiBtOfAweQ9XdUeKn5QinXN0U10ZqERCS7Z25nxIIkeSA4K7T1hDJhQf0wyJp69WNU2
         V2HkPl809Nm7DTPy/iXUncecta3NIhMOlHDLyoGB2i4vdHbxwnJc2x4xxFt9Tp607wgh
         LiW9YGI30ZkWTbndd5ZTmvlwWsgn8AqUtVqROSu2UYxHgTEPBUAwsgQuyB+QbdsRAvQq
         qSJzt/N7Bm20L9+NzDnySnSh/FtFqBJNjHKvfGtW7szJWugN1IPj5t/RZgYLlSKjYQYA
         So5g==
X-Gm-Message-State: AOAM532/bIxeXTaZLpoakrnvMbHXhX5yB6ZMEWkdFlOjLjxg5DNljVSu
        fVJQVCuz+cH9arxSg14GlqNqPL9Glhjo
X-Google-Smtp-Source: 
 ABdhPJwbL9wte8oWAvJxfPktFTF95fs7X3SzrOa7dpHTxm2hGggMhjiaWmc70D9nzkQo9SR/+yCz4VxME/CR
Sender: "bgardon via sendgmr" <bgardon@bgardon.sea.corp.google.com>
X-Received: from bgardon.sea.corp.google.com
 ([2620:15c:100:202:f693:9fff:fef4:a293])
 (user=bgardon job=sendgmr) by 2002:a05:6a00:8c7:b029:19d:afa5:34e5 with SMTP
 id s7-20020a056a0008c7b029019dafa534e5mr5524385pfu.30.1609959595127; Wed, 06
 Jan 2021 10:59:55 -0800 (PST)
Date: Wed,  6 Jan 2021 10:59:50 -0800
Message-Id: <20210106185951.2966575-1-bgardon@google.com>
Mime-Version: 1.0
X-Mailer: git-send-email 2.29.2.729.g45daf8777d-goog
Subject: [PATCH v2 1/2] KVM: x86/mmu: Ensure TDP MMU roots are freed after
 yield
From: Ben Gardon <bgardon@google.com>
To: linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Cc: Paolo Bonzini <pbonzini@redhat.com>,
        Sean Christopherson <seanjc@google.com>,
        Peter Shier <pshier@google.com>,
        "Maciej S . Szmigiero" <maciej.szmigiero@oracle.com>,
        Leo Hou <leohou1402@gmail.com>, Ben Gardon <bgardon@google.com>
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Many TDP MMU functions which need to perform some action on all TDP MMU
roots hold a reference on that root so that they can safely drop the MMU
lock in order to yield to other threads. However, when releasing the
reference on the root, there is a bug: the root will not be freed even
if its reference count (root_count) is reduced to 0.

To simplify acquiring and releasing references on TDP MMU root pages, and
to ensure that these roots are properly freed, move the get/put operations
into the TDP MMU root iterator macro. Not all functions which use the macro
currently get and put a reference to the root, but adding this behavior is
harmless.

Moving the get/put operations into the iterator macro also helps
simplify control flow when a root does need to be freed. Note that using
the list_for_each_entry_unsafe macro would not have been appropriate in
this situation because it could keep a reference to the next root across
an MMU lock release + reacquire.

Reported-by: Maciej S. Szmigiero <maciej.szmigiero@oracle.com>
Suggested-by: Paolo Bonzini <pbonzini@redhat.com>
Fixes: faaf05b00aec ("kvm: x86/mmu: Support zapping SPTEs in the TDP MMU")
Fixes: 063afacd8730 ("kvm: x86/mmu: Support invalidate range MMU notifier for TDP MMU")
Fixes: a6a0b05da9f3 ("kvm: x86/mmu: Support dirty logging for the TDP MMU")
Fixes: 14881998566d ("kvm: x86/mmu: Support disabling dirty logging for the tdp MMU")
Signed-off-by: Ben Gardon <bgardon@google.com>
---
 arch/x86/kvm/mmu/tdp_mmu.c | 97 +++++++++++++++++---------------------
 1 file changed, 44 insertions(+), 53 deletions(-)

```
