#### [PATCH v3 1/4] KVM: x86: Move FPU register accessors into fpu.h
##### From: Siddharth Chandrasekaran <sidcha@amazon.de>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Siddharth Chandrasekaran <sidcha@amazon.de>
X-Patchwork-Id: 12201477
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.0 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_CR_TRAILER,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,
	UNWANTED_LANGUAGE_BODY,USER_AGENT_GIT autolearn=unavailable
	autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 90DC8C433ED
	for <kvm@archiver.kernel.org>; Tue, 13 Apr 2021 21:51:48 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 6990F61222
	for <kvm@archiver.kernel.org>; Tue, 13 Apr 2021 21:51:48 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1348505AbhDMVwH (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 13 Apr 2021 17:52:07 -0400
Received: from smtp-fw-9102.amazon.com ([207.171.184.29]:51607 "EHLO
        smtp-fw-9102.amazon.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S230491AbhDMVwG (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 13 Apr 2021 17:52:06 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
  d=amazon.de; i=@amazon.de; q=dns/txt; s=amazon201209;
  t=1618350707; x=1649886707;
  h=from:to:cc:subject:date:message-id:in-reply-to:
   references:mime-version;
  bh=oRPtxgat/4J5V+eoHtGmgLp6qFUokLuBHjOnK7AYLZU=;
  b=I6TiGw7Fze+Kg06H993o/3xAUwkap7KYwBZMPbmuZHKIIY4cJXGfKiDE
   f1UwC0HaNHIXzKIRtONgP0/KyDdHIysi4nUe9hlLobn7k6IjLoCtyeQsN
   c1OHWyvWbHaGYmjtwqg9SlPhaDk2+b9byP39A0i7kH7ttvG5PxK2bi2QA
   4=;
X-IronPort-AV: E=Sophos;i="5.82,220,1613433600";
   d="scan'208";a="127407672"
Received: from pdx4-co-svc-p1-lb2-vlan3.amazon.com (HELO
 email-inbound-relay-2b-859fe132.us-west-2.amazon.com) ([10.25.36.214])
  by smtp-border-fw-out-9102.sea19.amazon.com with ESMTP;
 13 Apr 2021 21:51:40 +0000
Received: from EX13D28EUC003.ant.amazon.com
 (pdx1-ws-svc-p6-lb9-vlan2.pdx.amazon.com [10.236.137.194])
        by email-inbound-relay-2b-859fe132.us-west-2.amazon.com (Postfix) with
 ESMTPS id D2C02220BCB;
        Tue, 13 Apr 2021 21:51:38 +0000 (UTC)
Received: from uc8bbc9586ea454.ant.amazon.com (10.43.161.39) by
 EX13D28EUC003.ant.amazon.com (10.43.164.43) with Microsoft SMTP Server (TLS)
 id 15.0.1497.2; Tue, 13 Apr 2021 21:51:29 +0000
From: Siddharth Chandrasekaran <sidcha@amazon.de>
To: "K. Y. Srinivasan" <kys@microsoft.com>,
        Haiyang Zhang <haiyangz@microsoft.com>,
        Stephen Hemminger <sthemmin@microsoft.com>,
        Wei Liu <wei.liu@kernel.org>,
        Thomas Gleixner <tglx@linutronix.de>,
        Ingo Molnar <mingo@redhat.com>, Borislav Petkov <bp@alien8.de>,
        <x86@kernel.org>, "H. Peter Anvin" <hpa@zytor.com>,
        Paolo Bonzini <pbonzini@redhat.com>,
        "Sean Christopherson" <seanjc@google.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        "Joerg Roedel" <joro@8bytes.org>
CC: Siddharth Chandrasekaran <sidcha@amazon.de>,
        Alexander Graf <graf@amazon.com>,
        Evgeny Iakovlev <eyakovl@amazon.de>,
        Liran Alon <liran@amazon.com>,
        Ioannis Aslanidis <iaslan@amazon.de>,
        <linux-hyperv@vger.kernel.org>, <linux-kernel@vger.kernel.org>,
        <kvm@vger.kernel.org>
Subject: [PATCH v3 1/4] KVM: x86: Move FPU register accessors into fpu.h
Date: Tue, 13 Apr 2021 23:50:54 +0200
Message-ID: 
 <5905cb9f8585ac6d863bae4e3c22d5d1b682f10d.1618349671.git.sidcha@amazon.de>
X-Mailer: git-send-email 2.17.1
In-Reply-To: <cover.1618349671.git.sidcha@amazon.de>
References: <cover.1618349671.git.sidcha@amazon.de>
MIME-Version: 1.0
X-Originating-IP: [10.43.161.39]
X-ClientProxiedBy: EX13D30UWC002.ant.amazon.com (10.43.162.235) To
 EX13D28EUC003.ant.amazon.com (10.43.164.43)
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Hyper-v XMM fast hypercalls use XMM registers to pass input/output
parameters. To access these, hyperv.c can reuse some FPU register
accessors defined in emulator.c. Move them to a common location so both
can access them.

While at it, reorder the parameters of these accessor methods to make
them more readable.

Cc: Alexander Graf <graf@amazon.com>
Cc: Evgeny Iakovlev <eyakovl@amazon.de>
Signed-off-by: Siddharth Chandrasekaran <sidcha@amazon.de>
---
 arch/x86/kvm/emulate.c     | 137 +++++-------------------------------
 arch/x86/kvm/fpu.h         | 140 +++++++++++++++++++++++++++++++++++++
 arch/x86/kvm/kvm_emulate.h |   3 +-
 3 files changed, 158 insertions(+), 122 deletions(-)
 create mode 100644 arch/x86/kvm/fpu.h

```
#### [GIT PULL] KVM changes for 5.12-rc8 or final
##### From: Paolo Bonzini <pbonzini@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Paolo Bonzini <pbonzini@redhat.com>
X-Patchwork-Id: 12201505
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-20.8 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_PATCH,INCLUDES_PULL_REQUEST,MAILING_LIST_MULTI,MENTIONS_GIT_HOSTING,
	SPF_HELO_NONE,SPF_PASS autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 149C5C43460
	for <kvm@archiver.kernel.org>; Tue, 13 Apr 2021 22:40:09 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id E676E611CC
	for <kvm@archiver.kernel.org>; Tue, 13 Apr 2021 22:40:08 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1347514AbhDMWk0 (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 13 Apr 2021 18:40:26 -0400
Received: from us-smtp-delivery-124.mimecast.com ([216.205.24.124]:50337 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1347463AbhDMWkZ (ORCPT
        <rfc822;kvm@vger.kernel.org>); Tue, 13 Apr 2021 18:40:25 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1618353605;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=Se+bjf3UY2AKAwu4d1rz6KBu7BtAyVo+o4WxT9t65S8=;
        b=cIM7Dv2sMSNk9NqTrwIF0rQn47CDn8QWKQ3F4Kbf4fHlY74INEVSwK/W2V9AbvEgwamVC/
        K1xVVkBrzyFR/0c04xQ47M2XhNOpkD/bJpU8JFUsolQbkBhW+V0YmNS/w2wCuRH+68u1/8
        vPFmrJMyQh8xxetdg6F6RI/l25qibIA=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-215-F1oR74fOP22g-Rh33WhCQg-1; Tue, 13 Apr 2021 18:40:00 -0400
X-MC-Unique: F1oR74fOP22g-Rh33WhCQg-1
Received: from smtp.corp.redhat.com (int-mx03.intmail.prod.int.phx2.redhat.com
 [10.5.11.13])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id C6740107ACC7;
        Tue, 13 Apr 2021 22:39:59 +0000 (UTC)
Received: from virtlab701.virt.lab.eng.bos.redhat.com
 (virtlab701.virt.lab.eng.bos.redhat.com [10.19.152.228])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 77538614FA;
        Tue, 13 Apr 2021 22:39:59 +0000 (UTC)
From: Paolo Bonzini <pbonzini@redhat.com>
To: torvalds@linux-foundation.org
Cc: linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Subject: [GIT PULL] KVM changes for 5.12-rc8 or final
Date: Tue, 13 Apr 2021 18:39:58 -0400
Message-Id: <20210413223958.156145-1-pbonzini@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.13
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Linus,

The following changes since commit 315f02c60d9425b38eb8ad7f21b8a35e40db23f9:

  KVM: x86/mmu: preserve pending TLB flush across calls to kvm_tdp_mmu_zap_sp (2021-04-08 07:48:18 -0400)

are available in the Git repository at:

  https://git.kernel.org/pub/scm/virt/kvm/kvm.git tags/for-linus

for you to fetch changes up to 04c4f2ee3f68c9a4bf1653d15f1a9a435ae33f7a:

  KVM: VMX: Don't use vcpu->run->internal.ndata as an array index (2021-04-13 18:23:41 -0400)

----------------------------------------------------------------
Fix for a possible out-of-bounds access.

----------------------------------------------------------------
Reiji Watanabe (1):
      KVM: VMX: Don't use vcpu->run->internal.ndata as an array index

 arch/x86/kvm/vmx/vmx.c | 10 +++++-----
 1 file changed, 5 insertions(+), 5 deletions(-)
```
#### [RFC PATCH 1/7] sched/vtime: Move guest enter/exit vtime accounting to separate helpers
##### From: Sean Christopherson <seanjc@google.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Sean Christopherson <seanjc@google.com>
X-Patchwork-Id: 12201287
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-26.2 required=3.0 tests=BAYES_00,DKIMWL_WL_MED,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_CR_TRAILER,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,
	URIBL_BLOCKED,USER_AGENT_GIT,USER_IN_DEF_DKIM_WL autolearn=ham
	autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 0A7EBC43460
	for <kvm@archiver.kernel.org>; Tue, 13 Apr 2021 18:29:47 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id CFD06613BD
	for <kvm@archiver.kernel.org>; Tue, 13 Apr 2021 18:29:46 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1347764AbhDMSaF (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 13 Apr 2021 14:30:05 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:55344 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1347757AbhDMSaD (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 13 Apr 2021 14:30:03 -0400
Received: from mail-yb1-xb49.google.com (mail-yb1-xb49.google.com
 [IPv6:2607:f8b0:4864:20::b49])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 67938C06175F
        for <kvm@vger.kernel.org>; Tue, 13 Apr 2021 11:29:43 -0700 (PDT)
Received: by mail-yb1-xb49.google.com with SMTP id v2so14919059ybc.17
        for <kvm@vger.kernel.org>; Tue, 13 Apr 2021 11:29:43 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=reply-to:date:in-reply-to:message-id:mime-version:references
         :subject:from:to:cc;
        bh=DBgKpsy5j/P3hgAEc9fw7Y1G0+qqP32d1bF863cdlm4=;
        b=TMO4lZk/DQbX58V5PUc5wkHjNyjUGqKC+eUZ1OM7WF9rm8l+FfiCAEkg3MCT9Zb6D0
         LeRqBSimMGn7bZpyvLInauMaoq8e1Y+aT9xC9RAGn4INHwTzqrhLmO9ddRJ2SrUku42I
         gqKIBM7ycs/kOaMy9YRNA3fM/OZkGENEIl/vUManqirXHGPWtcDqCQOdO2DDxFC3wxpW
         5unGle02ljfxlxLq4PmG4kaYsWUUHGf41jnlz3dNiA4mDb7M/9siWZ4vHWpNraCEMqZG
         G3XJT646bH/U7BhLzNKJleVm9lm54fCaw4LQmaRd7ntZd9K+k7lmd+QwSjGTCxv+P9NS
         BWWA==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:reply-to:date:in-reply-to:message-id
         :mime-version:references:subject:from:to:cc;
        bh=DBgKpsy5j/P3hgAEc9fw7Y1G0+qqP32d1bF863cdlm4=;
        b=WkS1tFmacZIhaJQY/bvoYqPciiseup/SCNgpflkHUr+30ozKZIr1v2N8I9foJQdtaz
         iOa+4NHoqzXvDkuw4ovfqwHyIkbuMCkOf/e3DYuVaxeI9fnWr5BQZ4JYfIIOzrDwX6TV
         o78RT6epdqf0wWfuzqHf3/IBZlPJq5o5FkSAMgxugzc6w82TKiWzE1qUy+1j8s6tHrNJ
         UHTqgJpkPD3fjNGlBVQ25Za9+PiDtp+35C/N+y69JP3iZOBuRA0OPmqyYsLFVQXsBkOL
         DeGnlGbA7PS/ybk3gYca6yVnS/WbGPHrsiyvshfv8U4dJQb4rqUV8ygEGYDMFOtssfXt
         KYJw==
X-Gm-Message-State: AOAM530baLja9CS5xuuMqfBR3Q3A2Fa0gvJ7+DpsMrWQUFGab9xEUb5c
        LQ/ViQt/J5CIR279u5ZfJ6akBRVu8S8=
X-Google-Smtp-Source: 
 ABdhPJxyESESndmX5ChjYM7X/7wj39TKAIr9yH8AoLODme0G1B9J1nf+VUlLvnk+RaSnnO2UKE3J/uXgd9I=
X-Received: from seanjc798194.pdx.corp.google.com
 ([2620:15c:f:10:f031:9c1c:56c7:c3bf])
 (user=seanjc job=sendgmr) by 2002:a25:ce81:: with SMTP id
 x123mr17691277ybe.283.1618338582701;
 Tue, 13 Apr 2021 11:29:42 -0700 (PDT)
Reply-To: Sean Christopherson <seanjc@google.com>
Date: Tue, 13 Apr 2021 11:29:27 -0700
In-Reply-To: <20210413182933.1046389-1-seanjc@google.com>
Message-Id: <20210413182933.1046389-2-seanjc@google.com>
Mime-Version: 1.0
References: <20210413182933.1046389-1-seanjc@google.com>
X-Mailer: git-send-email 2.31.1.295.g9ea45b61b8-goog
Subject: [RFC PATCH 1/7] sched/vtime: Move guest enter/exit vtime accounting
 to separate helpers
From: Sean Christopherson <seanjc@google.com>
To: Paolo Bonzini <pbonzini@redhat.com>
Cc: Sean Christopherson <seanjc@google.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org, Thomas Gleixner <tglx@linutronix.de>,
        Christian Borntraeger <borntraeger@de.ibm.com>,
        Michael Tokarev <mjt@tls.msk.ru>
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Provide separate helpers for guest enter/exit vtime accounting instead of
open coding the logic within the context tracking code.  This will allow
KVM x86 to handle vtime accounting slightly differently when using tick-
based accounting.

Opportunstically delete the vtime_account_kernel() stub now that all
callers are wrapped with CONFIG_VIRT_CPU_ACCOUNTING_NATIVE=y.

No functional change intended.

Suggested-by: Thomas Gleixner <tglx@linutronix.de>
Cc: Christian Borntraeger <borntraeger@de.ibm.com>
Signed-off-by: Sean Christopherson <seanjc@google.com>
---
 include/linux/context_tracking.h | 17 +++---------
 include/linux/vtime.h            | 45 +++++++++++++++++++++++++++++---
 2 files changed, 45 insertions(+), 17 deletions(-)

```
#### [PATCH v2 1/3] context_tracking: Split guest_enter/exit_irqoff
##### From: Wanpeng Li <kernellwp@gmail.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Wanpeng Li <kernellwp@gmail.com>
X-Patchwork-Id: 12199501
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-15.7 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,DKIM_VALID_AU,FREEMAIL_FORGED_FROMDOMAIN,FREEMAIL_FROM,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED,USER_AGENT_GIT
	autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 3DAA1C433B4
	for <kvm@archiver.kernel.org>; Tue, 13 Apr 2021 07:16:34 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 21AC66120E
	for <kvm@archiver.kernel.org>; Tue, 13 Apr 2021 07:16:34 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S237770AbhDMHQu (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 13 Apr 2021 03:16:50 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:48446 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S237674AbhDMHQm (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 13 Apr 2021 03:16:42 -0400
Received: from mail-pg1-x52a.google.com (mail-pg1-x52a.google.com
 [IPv6:2607:f8b0:4864:20::52a])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id B9E68C061574;
        Tue, 13 Apr 2021 00:16:23 -0700 (PDT)
Received: by mail-pg1-x52a.google.com with SMTP id b17so11287185pgh.7;
        Tue, 13 Apr 2021 00:16:23 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=from:to:cc:subject:date:message-id:in-reply-to:references;
        bh=lEku+Nldal8skQz83jlsEXJCMsplj1mVF4FlMiQwdgc=;
        b=JAI3885dCP/Tr9ozd+eLPK7/87axdOXIeCxUAKh3AfMd6daXnaKe0cNkVKHEQu11Uz
         hx8MzT7UeMYkR94asHUkkvnMw3Y4OdF+xLQxo/2aZ8HZUrgu0rupDHzyPyQiVViBpV5T
         BuEEPJcrgtiprFqChHyqDFVeVWQwwF2P6naZEjL0842UM3BS2vmkmjh7Sh4rjkMZhLmj
         1XY94DeHhbcF0htJTL/MUdZHxIpsNuYXScrZDXPD5YYDFt7OL1uKLEQuIBB3+kM37cP1
         5Ql6TZZJ836ccOPOMtpat6jKnGZP1VEPnvVoe9D78HHsJY6SbWiF4JPb/oQjiXMAUV5A
         JJ+A==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:in-reply-to
         :references;
        bh=lEku+Nldal8skQz83jlsEXJCMsplj1mVF4FlMiQwdgc=;
        b=HGgldkf5vsThUGHqu9WciJ447EfLaRIJmmQBPJDXu1+wiVR0FKwibyCAI5TqiqYRde
         i3sZUDPaVCSz1/nQ/yQpMQRlTCfP0b7vQUznJ6dc6TQbKKtYW0VCE2RioQvPjzze5DHp
         uUjWnhvcI1yYaIjp+Nz3qBJydj77GqE90MZtDYqnrj0f+IvljVk1peGn5oRfQcgbDNuo
         XhQCsN2L1x5rLjutcoUJLoqdV4qIoipgVk9IwdVM+wgdOG7b24n/2d40Bz1IOCDaJUnG
         Ky8zGoaNtK1lnoatuSictRlLrqqmuhuWlgZvqHiXquGNcTbyurt4WS6KYirMxUfhqcMQ
         Aq/Q==
X-Gm-Message-State: AOAM532dhSjgr0ivn7HHQ/PSCUZQCH1zRvoi583c1lM6LUdUCA8sY6Jz
        Ce+cfo9/zxuJTNx0EDWzRhUTkzKG2uQ=
X-Google-Smtp-Source: 
 ABdhPJzLnFgeSQ05yCVeGcUCwoof/Fv9TY2evQJq2Kz2CsYLpNdbJPgrJJNvWckMMEUM4AGyNrZcOw==
X-Received: by 2002:a65:640b:: with SMTP id
 a11mr30715660pgv.357.1618298183022;
        Tue, 13 Apr 2021 00:16:23 -0700 (PDT)
Received: from localhost.localdomain ([103.7.29.6])
        by smtp.googlemail.com with ESMTPSA id
 i10sm2031088pjm.1.2021.04.13.00.16.20
        (version=TLS1_2 cipher=ECDHE-ECDSA-AES128-GCM-SHA256 bits=128/128);
        Tue, 13 Apr 2021 00:16:22 -0700 (PDT)
From: Wanpeng Li <kernellwp@gmail.com>
X-Google-Original-From: Wanpeng Li <wanpengli@tencent.com>
To: linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Cc: Paolo Bonzini <pbonzini@redhat.com>,
        Sean Christopherson <seanjc@google.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>,
        Thomas Gleixner <tglx@linutronix.de>,
        Michael Tokarev <mjt@tls.msk.ru>
Subject: [PATCH v2 1/3] context_tracking: Split guest_enter/exit_irqoff
Date: Tue, 13 Apr 2021 15:16:07 +0800
Message-Id: <1618298169-3831-2-git-send-email-wanpengli@tencent.com>
X-Mailer: git-send-email 2.7.4
In-Reply-To: <1618298169-3831-1-git-send-email-wanpengli@tencent.com>
References: <1618298169-3831-1-git-send-email-wanpengli@tencent.com>
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Wanpeng Li <wanpengli@tencent.com>

Split context_tracking part from guest_enter/exit_irqoff, it will be 
called separately in later patches.

Suggested-by: Thomas Gleixner <tglx@linutronix.de>
Cc: Thomas Gleixner <tglx@linutronix.de>
Cc: Sean Christopherson <seanjc@google.com>
Cc: Michael Tokarev <mjt@tls.msk.ru>
Signed-off-by: Wanpeng Li <wanpengli@tencent.com>
---
 include/linux/context_tracking.h | 42 +++++++++++++++++++++++++++++-----------
 1 file changed, 31 insertions(+), 11 deletions(-)

```
#### [PATCH v2 1/8] KVM: x86: Cache total page count to avoid traversing the memslot array
##### From: "Maciej S. Szmigiero" <mail@maciej.szmigiero.name>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: "Maciej S. Szmigiero" <mail@maciej.szmigiero.name>
X-Patchwork-Id: 12200739
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.8 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT
	autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 5A288C433B4
	for <kvm@archiver.kernel.org>; Tue, 13 Apr 2021 14:34:24 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 35270613AE
	for <kvm@archiver.kernel.org>; Tue, 13 Apr 2021 14:34:24 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S237468AbhDMOel (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 13 Apr 2021 10:34:41 -0400
Received: from vps-vb.mhejs.net ([37.28.154.113]:49746 "EHLO vps-vb.mhejs.net"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S231382AbhDMOd6 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 13 Apr 2021 10:33:58 -0400
Received: from MUA
        by vps-vb.mhejs.net with esmtps
 (TLS1.2:ECDHE-RSA-AES256-GCM-SHA384:256)
        (Exim 4.93.0.4)
        (envelope-from <mail@maciej.szmigiero.name>)
        id 1lWJkH-0003zD-73; Tue, 13 Apr 2021 16:10:25 +0200
From: "Maciej S. Szmigiero" <mail@maciej.szmigiero.name>
To: Paolo Bonzini <pbonzini@redhat.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>
Cc: Sean Christopherson <seanjc@google.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Igor Mammedov <imammedo@redhat.com>,
        Marc Zyngier <maz@kernel.org>,
        James Morse <james.morse@arm.com>,
        Julien Thierry <julien.thierry.kdev@gmail.com>,
        Suzuki K Poulose <suzuki.poulose@arm.com>,
        Huacai Chen <chenhuacai@kernel.org>,
        Aleksandar Markovic <aleksandar.qemu.devel@gmail.com>,
        Paul Mackerras <paulus@ozlabs.org>,
        Christian Borntraeger <borntraeger@de.ibm.com>,
        Janosch Frank <frankja@linux.ibm.com>,
        David Hildenbrand <david@redhat.com>,
        Cornelia Huck <cohuck@redhat.com>,
        Claudio Imbrenda <imbrenda@linux.ibm.com>,
        Joerg Roedel <joro@8bytes.org>, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org
Subject: [PATCH v2 1/8] KVM: x86: Cache total page count to avoid traversing
 the memslot array
Date: Tue, 13 Apr 2021 16:10:07 +0200
Message-Id: 
 <7a3e21252b29f6703efee5d68ed543376d65cd9a.1618322003.git.maciej.szmigiero@oracle.com>
X-Mailer: git-send-email 2.31.1
In-Reply-To: <cover.1618322001.git.maciej.szmigiero@oracle.com>
References: <cover.1618322001.git.maciej.szmigiero@oracle.com>
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: "Maciej S. Szmigiero" <maciej.szmigiero@oracle.com>

There is no point in recalculating from scratch the total number of pages
in all memslots each time a memslot is created or deleted.

Just cache the value and update it accordingly on each such operation so
the code doesn't need to traverse the whole memslot array each time.

Signed-off-by: Maciej S. Szmigiero <maciej.szmigiero@oracle.com>
---
 arch/x86/include/asm/kvm_host.h |  2 +-
 arch/x86/kvm/mmu/mmu.c          | 24 ------------------------
 arch/x86/kvm/x86.c              | 18 +++++++++++++++---
 3 files changed, 16 insertions(+), 28 deletions(-)

```
#### [PATCH] kvm/selftests: Fix race condition with dirty_log_test
##### From: Peter Xu <peterx@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Peter Xu <peterx@redhat.com>
X-Patchwork-Id: 12201469
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-18.8 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_CR_TRAILER,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,
	USER_AGENT_GIT autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 3CDF9C433ED
	for <kvm@archiver.kernel.org>; Tue, 13 Apr 2021 21:32:12 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 190B66120E
	for <kvm@archiver.kernel.org>; Tue, 13 Apr 2021 21:32:12 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S242133AbhDMVca (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 13 Apr 2021 17:32:30 -0400
Received: from us-smtp-delivery-124.mimecast.com ([170.10.133.124]:51097 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S232073AbhDMVc1 (ORCPT
        <rfc822;kvm@vger.kernel.org>); Tue, 13 Apr 2021 17:32:27 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1618349527;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=X9n1E547QdNccpSIMLIADrczPbqaZ7pVhiltEhbynkc=;
        b=XbfUbc5FT7EZuwwBKlpcjLoDq/gb0XmqbB49l3x4HGyRClQA0WwrQ+fCaDC1YREw+boDro
        tTKQNvffnSKPL71OfPnzAYADjjdszpwyv97skKwqq1Mn94Y4mvuyQs05Oc1AbAqIyw89BZ
        rLEFBXifWpDOxNenKBBzk2eru9HzCjg=
Received: from mail-qt1-f197.google.com (mail-qt1-f197.google.com
 [209.85.160.197]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-68-IvGZ20LvORKnTbZqMv9eNA-1; Tue, 13 Apr 2021 17:32:06 -0400
X-MC-Unique: IvGZ20LvORKnTbZqMv9eNA-1
Received: by mail-qt1-f197.google.com with SMTP id
 h4-20020ac858440000b029019d657b9f21so564179qth.9
        for <kvm@vger.kernel.org>; Tue, 13 Apr 2021 14:32:06 -0700 (PDT)
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:mime-version
         :content-transfer-encoding;
        bh=X9n1E547QdNccpSIMLIADrczPbqaZ7pVhiltEhbynkc=;
        b=OtjcnqAo9+aIzudSEsIUsoxDZWHUZZuCZS2c+NNAO7Ekr7Fuqnczuwycw761NJiuDe
         mTpuozE3GsbFqUdqkSau0c9AlIkHpqjz65WpYPopsvpRCnhaWyMzOiMpzXICDcXLp5gp
         DxGmGd8EQxqUURIS02DhmcyySwaHJVejWt5v1MELAulde1EiaoybzHnfBIuDQkdXooOi
         MmuvO6kvHarUb7ylLPIgOeMBsE03rOO5VwllvfqO2oKPGK7Us+DZ0QDyWZT8YNjh41go
         OxA/j0NY+1/4IPiEhAVEiUpt7TOfs7rYXtJNs06B3a/I9PWqyXKBHjDQFv5EbRjELQNl
         cvTg==
X-Gm-Message-State: AOAM531fTkJYuBavbJ9HNMwRnTEjsKVrFDv7WFdq1Ucj8II7DPEweUou
        z6eR4SEyc+f4/QDulB50/pyXs1aFO7bVyvBoaSWaEmkVryzs4jcklBn74DEd7xiVLkkgyjL8S81
        t3tNyMrnQH2xA6lw4e4n+gaOSFfUasVBhWpx+H1BjPo/VdC9Ptqv2iQfknjEdFA==
X-Received: by 2002:ac8:44d0:: with SMTP id
 b16mr31954838qto.217.1618349525088;
        Tue, 13 Apr 2021 14:32:05 -0700 (PDT)
X-Google-Smtp-Source: 
 ABdhPJznkq3rW5DaJa1Xdbc667bf5oyHfTaHrjWtksTxRiuG7nmFsesX3SMukmeDtdVuqt8keqbQqw==
X-Received: by 2002:ac8:44d0:: with SMTP id
 b16mr31954804qto.217.1618349524674;
        Tue, 13 Apr 2021 14:32:04 -0700 (PDT)
Received: from xz-x1.redhat.com
 (bras-base-toroon474qw-grc-88-174-93-75-154.dsl.bell.ca. [174.93.75.154])
        by smtp.gmail.com with ESMTPSA id
 u126sm7626604qkd.80.2021.04.13.14.32.03
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Tue, 13 Apr 2021 14:32:03 -0700 (PDT)
From: Peter Xu <peterx@redhat.com>
To: kvm@vger.kernel.org, linux-kernel@vger.kernel.org
Cc: peterx@redhat.com, Andrew Jones <drjones@redhat.com>,
        Paolo Bonzini <pbonzini@redhat.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Sean Christopherson <seanjc@google.com>
Subject: [PATCH] kvm/selftests: Fix race condition with dirty_log_test
Date: Tue, 13 Apr 2021 17:32:02 -0400
Message-Id: <20210413213202.22766-1-peterx@redhat.com>
X-Mailer: git-send-email 2.26.2
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This fixes a bug that can trigger with e.g. "taskset -c 0 ./dirty_log_test" or
when the testing host is very busy.

The issue is when the vcpu thread got the dirty bit set but got preempted by
other threads _before_ the data is written, we won't be able to see the latest
data only until the vcpu threads do VMENTER. IOW, the guest write operation and
dirty bit set cannot guarantee atomicity. The race could look like:

    main thread                            vcpu thread
    ===========                            ===========
    iteration=X
                                           *addr = X
                                           (so latest data is X)
    iteration=X+1
    ...
    iteration=X+N
                                           guest executes "*addr = X+N"
                                             reg=READ_ONCE(iteration)=X+N
                                             host page fault
                                               set dirty bit for page "addr"
                                             (_before_ VMENTER happens...
                                              so *addr is still X!)
                                           vcpu thread got preempted
    get dirty log
    verify data
      detected dirty bit set, data is X
      not X+N nor X+N-1, data too old!

This patch closes this race by allowing the main thread to give the vcpu thread
chance to do a VMENTER to complete that write operation.  It's done by adding a
vcpu loop counter (must be defined as volatile as main thread will do read
loop), then the main thread can guarantee the vcpu got at least another VMENTER
by making sure the guest_vcpu_loops increases by 2.

Dirty ring does not need this since dirty_ring_last_page would already help
avoid this specific race condition.

Cc: Andrew Jones <drjones@redhat.com>
Cc: Paolo Bonzini <pbonzini@redhat.com>
Cc: Vitaly Kuznetsov <vkuznets@redhat.com>
Cc: Sean Christopherson <seanjc@google.com>
Signed-off-by: Peter Xu <peterx@redhat.com>
---
 tools/testing/selftests/kvm/dirty_log_test.c | 54 +++++++++++++++++++-
 1 file changed, 53 insertions(+), 1 deletion(-)

```
#### [PATCH] KVM: VMX: Don't use vcpu->run->internal.ndata as an array index
##### From: Reiji Watanabe <reijiw@google.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Reiji Watanabe <reijiw@google.com>
X-Patchwork-Id: 12200853
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-26.3 required=3.0 tests=BAYES_00,DKIMWL_WL_MED,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_CR_TRAILER,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,
	USER_AGENT_GIT,USER_IN_DEF_DKIM_WL autolearn=ham autolearn_force=no
	version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 8A52BC433ED
	for <kvm@archiver.kernel.org>; Tue, 13 Apr 2021 15:48:54 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 6A13C61369
	for <kvm@archiver.kernel.org>; Tue, 13 Apr 2021 15:48:54 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1346094AbhDMPtN (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 13 Apr 2021 11:49:13 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:48746 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1345993AbhDMPtH (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 13 Apr 2021 11:49:07 -0400
Received: from mail-qk1-x74a.google.com (mail-qk1-x74a.google.com
 [IPv6:2607:f8b0:4864:20::74a])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 68370C061574
        for <kvm@vger.kernel.org>; Tue, 13 Apr 2021 08:48:47 -0700 (PDT)
Received: by mail-qk1-x74a.google.com with SMTP id 15so8671262qkv.16
        for <kvm@vger.kernel.org>; Tue, 13 Apr 2021 08:48:47 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=date:message-id:mime-version:subject:from:to:cc;
        bh=EYvFdtdmniOP0Ta43kxjqQJmZwEspknxzVV5/mYBlog=;
        b=m0xoCRoLT0iZ4P8XjVDhFfVoF1j2PxsxEBaD3bnVNEhvgEKw+yRZjJF/wK9wojc1rV
         MYxui5C+ivI2IZaD+dPP2S1xD3w6WCZcuuuptvPuhBLvNDSdBWB65SBiRmgFRIWav9j6
         ZYqXXWKu2FIlmxMPw4r9miz4uk6Wo5MXVdJZgXiiaj9KD9Pv002Gn+xy2P77DT3hYT5d
         NM2lZZzn+GoSEsQndtHKRB2Cy0aKVwjQeXGtuDv6exFSMfGbGfqNImjatq7uUjO3opGd
         jjn+cdOt2gadDjF6NcQJpFHfloB3yBOqs0Kv4LjmcCUIrpH8Jazpm0ShGy2hZL86Yz1Q
         Is8Q==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:date:message-id:mime-version:subject:from:to:cc;
        bh=EYvFdtdmniOP0Ta43kxjqQJmZwEspknxzVV5/mYBlog=;
        b=fWfL8YPhTctWMuZW+NkH0UhPtoR5gICU1sCWV1XfgkgBQaZn2e9Xd3dykPrbS7ecso
         8KW39JLl/VRg1XS26DTo/H4LkHANyaBZ/i7wQhh9DRTLXgdw1G3OquFoeGb7H9NSgTR6
         baUubQvhmXw+rcr6QFNi6ynnU8Ix8U8Y+nNDEcjs9N6b8USgtO1HaDaLKI0NLJlI/LYs
         XXACObW3Upry7S31U3cWCOj51+/D8DmcYLlt8dxizwWBRrotKNacmpj3SATeyzpED2YC
         mmZ9+GwZ6Pu6qYqsN1eYjOXlxtz+lkgMYgR+Yugw434NEKZjLG3DVW16b980AB7CWkdU
         PWjg==
X-Gm-Message-State: AOAM530dHOseOWWf7b5/EViJ41a8gt8GbYLZmmxieQgitBVKRSVbbErI
        01x1Y0zSxq5Np5LmjvA3P2P3VEWxF9Ik8szp3aK3ZRdyLIDmS9HUaftEgPQcEGm02mGt8VmPI3m
        TeoqGpRY3DP06st1tr74BMyrk58CSvhahcZuAg4LDBfoye9f6onrkmghSfw==
X-Google-Smtp-Source: 
 ABdhPJywB/NR5QM6336xCXTD26lcC3/uKRuJ1usxRQ70uM4FvOK/Rqm1zXEyReY3HsRtnLqYz+aW5r6BX1c=
X-Received: from reiji-vws.c.googlers.com
 ([fda3:e722:ac3:10:7f:e700:c0a8:15a3])
 (user=reijiw job=sendgmr) by 2002:a0c:f901:: with SMTP id
 v1mr25205488qvn.26.1618328926505;
 Tue, 13 Apr 2021 08:48:46 -0700 (PDT)
Date: Tue, 13 Apr 2021 15:47:40 +0000
Message-Id: <20210413154739.490299-1-reijiw@google.com>
Mime-Version: 1.0
X-Mailer: git-send-email 2.31.1.295.g9ea45b61b8-goog
Subject: [PATCH] KVM: VMX: Don't use vcpu->run->internal.ndata as an array
 index
From: Reiji Watanabe <reijiw@google.com>
To: kvm@vger.kernel.org, Paolo Bonzini <pbonzini@redhat.com>
Cc: Reiji Watanabe <reijiw@google.com>,
        Jim Mattson <jmattson@google.com>
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

__vmx_handle_exit() uses vcpu->run->internal.ndata as an index for
an array access.  Since vcpu->run is (can be) mapped to a user address
space with a writer permission, the 'ndata' could be updated by the
user process at anytime (the user process can set it to outside the
bounds of the array).
So, it is not safe that __vmx_handle_exit() uses the 'ndata' that way.

Fixes: 1aa561b1a4c0 ("kvm: x86: Add "last CPU" to some KVM_EXIT information")
Signed-off-by: Reiji Watanabe <reijiw@google.com>
Reviewed-by: Jim Mattson <jmattson@google.com>
---
 arch/x86/kvm/vmx/vmx.c | 10 +++++-----
 1 file changed, 5 insertions(+), 5 deletions(-)

```
#### [PATCH RFC 01/22] asm-generic/hyperv: add HV_STATUS_ACCESS_DENIED definition
##### From: Vitaly Kuznetsov <vkuznets@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Vitaly Kuznetsov <vkuznets@redhat.com>
X-Patchwork-Id: 12200375
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-15.8 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_CR_TRAILER,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS
	autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 1D052C43460
	for <kvm@archiver.kernel.org>; Tue, 13 Apr 2021 12:26:51 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id D292961278
	for <kvm@archiver.kernel.org>; Tue, 13 Apr 2021 12:26:50 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1345512AbhDMM1I (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 13 Apr 2021 08:27:08 -0400
Received: from us-smtp-delivery-124.mimecast.com ([216.205.24.124]:59174 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1345505AbhDMM1B (ORCPT
        <rfc822;kvm@vger.kernel.org>); Tue, 13 Apr 2021 08:27:01 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1618316801;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding:
         in-reply-to:in-reply-to:references:references;
        bh=PPZjB79IEIwq/PRCsOh+j7hnsKwi62omE4Ya7aReZls=;
        b=LlrlQ4q1S5ZBgKDn1KF38Frzc4HTW8XiBQg1bbyaCoVSFAxmj3qbmieZFukN7GglYQxRvL
        WW7ttJwzP+UElc1bvNi1QNNLmMOX7/S2z7YlZfifPY7uasBiOQfobINMQsB4+AMnNa5bIZ
        EQQKt8Pf3WC7JsgE5M5O7CjJRg88wPw=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-301-WXqNNjheOdWLlC4Ft6wxxQ-1; Tue, 13 Apr 2021 08:26:38 -0400
X-MC-Unique: WXqNNjheOdWLlC4Ft6wxxQ-1
Received: from smtp.corp.redhat.com (int-mx02.intmail.prod.int.phx2.redhat.com
 [10.5.11.12])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id AC61D1008062;
        Tue, 13 Apr 2021 12:26:36 +0000 (UTC)
Received: from vitty.brq.redhat.com (unknown [10.40.195.75])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 926D760C04;
        Tue, 13 Apr 2021 12:26:34 +0000 (UTC)
From: Vitaly Kuznetsov <vkuznets@redhat.com>
To: kvm@vger.kernel.org, Paolo Bonzini <pbonzini@redhat.com>
Cc: Sean Christopherson <seanjc@google.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Siddharth Chandrasekaran <sidcha@amazon.de>,
        linux-kernel@vger.kernel.org, linux-hyperv@vger.kernel.org
Subject: [PATCH RFC 01/22] asm-generic/hyperv: add HV_STATUS_ACCESS_DENIED
 definition
Date: Tue, 13 Apr 2021 14:26:09 +0200
Message-Id: <20210413122630.975617-2-vkuznets@redhat.com>
In-Reply-To: <20210413122630.975617-1-vkuznets@redhat.com>
References: <20210413122630.975617-1-vkuznets@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.12
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From TLFSv6.0b, this status means: "The caller did not possess sufficient
access rights to perform the requested operation."

Signed-off-by: Vitaly Kuznetsov <vkuznets@redhat.com>
---
 include/asm-generic/hyperv-tlfs.h | 1 +
 1 file changed, 1 insertion(+)

```
#### [PATCH v2 1/2] KVM: selftests: Keep track of memslots more efficiently
##### From: "Maciej S. Szmigiero" <mail@maciej.szmigiero.name>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: "Maciej S. Szmigiero" <mail@maciej.szmigiero.name>
X-Patchwork-Id: 12200685
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.8 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT
	autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 5B0DCC433B4
	for <kvm@archiver.kernel.org>; Tue, 13 Apr 2021 14:31:44 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 41FBF6135C
	for <kvm@archiver.kernel.org>; Tue, 13 Apr 2021 14:31:44 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1346464AbhDMOby (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 13 Apr 2021 10:31:54 -0400
Received: from vps-vb.mhejs.net ([37.28.154.113]:49572 "EHLO vps-vb.mhejs.net"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S245415AbhDMOal (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 13 Apr 2021 10:30:41 -0400
X-Greylist: delayed 1288 seconds by postgrey-1.27 at vger.kernel.org;
 Tue, 13 Apr 2021 10:30:40 EDT
Received: from MUA
        by vps-vb.mhejs.net with esmtps
 (TLS1.2:ECDHE-RSA-AES256-GCM-SHA384:256)
        (Exim 4.93.0.4)
        (envelope-from <mail@maciej.szmigiero.name>)
        id 1lWJiU-0003y5-Ib; Tue, 13 Apr 2021 16:08:34 +0200
From: "Maciej S. Szmigiero" <mail@maciej.szmigiero.name>
To: Paolo Bonzini <pbonzini@redhat.com>
Cc: Shuah Khan <shuah@kernel.org>,
        Sean Christopherson <seanjc@google.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Igor Mammedov <imammedo@redhat.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Andrew Jones <drjones@redhat.com>, kvm@vger.kernel.org,
        linux-kselftest@vger.kernel.org, linux-kernel@vger.kernel.org
Subject: [PATCH v2 1/2] KVM: selftests: Keep track of memslots more
 efficiently
Date: Tue, 13 Apr 2021 16:08:27 +0200
Message-Id: 
 <b12749d47ee860468240cf027412c91b76dbe3db.1618253574.git.maciej.szmigiero@oracle.com>
X-Mailer: git-send-email 2.31.1
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: "Maciej S. Szmigiero" <maciej.szmigiero@oracle.com>

The KVM selftest framework was using a simple list for keeping track of
the memslots currently in use.
This resulted in lookups and adding a single memslot being O(n), the
later due to linear scanning of the existing memslot set to check for
the presence of any conflicting entries.

Before this change, benchmarking high count of memslots was more or less
impossible as pretty much all the benchmark time was spent in the
selftest framework code.

We can simply use a rbtree for keeping track of both of gfn and hva.
We don't need an interval tree for hva here as we can't have overlapping
memslots because we allocate a completely new memory chunk for each new
memslot.

Signed-off-by: Maciej S. Szmigiero <maciej.szmigiero@oracle.com>
Reviewed-by: Andrew Jones <drjones@redhat.com>
---

Changes from v1:
* Add Andrew's Reviewed-by: tag

 tools/testing/selftests/kvm/Makefile          |   2 +-
 tools/testing/selftests/kvm/lib/kvm_util.c    | 141 ++++++++++++++----
 .../selftests/kvm/lib/kvm_util_internal.h     |  15 +-
 tools/testing/selftests/kvm/lib/rbtree.c      |   1 +
 4 files changed, 124 insertions(+), 35 deletions(-)
 create mode 100644 tools/testing/selftests/kvm/lib/rbtree.c

```
#### [PATCH v2] kvm/selftests: Fix race condition with dirty_log_test
##### From: Peter Xu <peterx@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Peter Xu <peterx@redhat.com>
X-Patchwork-Id: 12201471
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-18.8 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_CR_TRAILER,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,
	USER_AGENT_GIT autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id E9B72C433ED
	for <kvm@archiver.kernel.org>; Tue, 13 Apr 2021 21:36:48 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id BAC98600CD
	for <kvm@archiver.kernel.org>; Tue, 13 Apr 2021 21:36:48 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1343970AbhDMVhH (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 13 Apr 2021 17:37:07 -0400
Received: from us-smtp-delivery-124.mimecast.com ([170.10.133.124]:43071 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S232147AbhDMVhG (ORCPT
        <rfc822;kvm@vger.kernel.org>); Tue, 13 Apr 2021 17:37:06 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1618349805;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=XycHoA1nL8vAycQ/cqP0i1ZIVgjvhSm3zs7dfnDh6ic=;
        b=Fwk3ZpOS2D2ukAFjki80v7Rb1FVU7qDOo/LDqfRf7Hb/6FXj0P+1iOAai7uDFh+tPSd5Rg
        C36c0m7oFUfMWc+KKd8UoWajVn+wL6WOswxZoyUWn7kLJ/VOeBAbpzgr6+tPxIX+d+UXwA
        XwoGSztIJoNh2b5UXp13MisrpSrmEVg=
Received: from mail-qv1-f71.google.com (mail-qv1-f71.google.com
 [209.85.219.71]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-18-moc0qm-PO4SwqcEV-doPJQ-1; Tue, 13 Apr 2021 17:36:44 -0400
X-MC-Unique: moc0qm-PO4SwqcEV-doPJQ-1
Received: by mail-qv1-f71.google.com with SMTP id g9so6623119qvi.19
        for <kvm@vger.kernel.org>; Tue, 13 Apr 2021 14:36:44 -0700 (PDT)
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:mime-version
         :content-transfer-encoding;
        bh=XycHoA1nL8vAycQ/cqP0i1ZIVgjvhSm3zs7dfnDh6ic=;
        b=U+AI0wKT5lRu0t5f432Gzv4Q1jtCnr5DnpLSe30PEolC5IHmCNi1rRQ9LcLtK2oB6Z
         KiFtZPxnVnwvq5re+fUUl8llzQsUSS7RqG27S/hE8XTNVGJ+hcUZNQ3RTsykvXSU5ShK
         6TvuN98Og0YwhJceVKtXyiLRx4BIsEiI6REQg+FmqHsOBhtl3/l13maC9SgZY1Uw6Gik
         uCu4Mk0DmH3KMdthfq4oMscNYNMd8DK3+tqn5eAAmLl90hgFR5oCad5ikvkVtZy1v5xA
         kT80phVt7rTZE9kWziis5oQ9EFMrrF29HIPobUqXm8u+ZJG47c40H2uwht+4qGtIiNrs
         mBcQ==
X-Gm-Message-State: AOAM53125St4Ph3Yr/hNvOC6Rn/wdmUjnOr4AM8eOyUHki9ms5CRdhvT
        dycoB5qJ1hKvzUfdOGWEDr/4f2rv++QU7nMtc2r2uZ3YiDnm+pQIdFeJC/7OPVb848jCDEGsBia
        TIN7m7OkZ3EsQNHeWtcLoxlB/zj+GTWjFR5euxlMSgjmh7JZ99Wjv/JY5MJiolQ==
X-Received: by 2002:ae9:f719:: with SMTP id s25mr34512460qkg.42.1618349803789;
        Tue, 13 Apr 2021 14:36:43 -0700 (PDT)
X-Google-Smtp-Source: 
 ABdhPJwLEpeasSayGgW415t75h7+UXOGP3qXino9298zZjgJ7RCJAr3cBVoCtVcWn54NfLNGHB0teQ==
X-Received: by 2002:ae9:f719:: with SMTP id s25mr34512434qkg.42.1618349803507;
        Tue, 13 Apr 2021 14:36:43 -0700 (PDT)
Received: from xz-x1.redhat.com
 (bras-base-toroon474qw-grc-88-174-93-75-154.dsl.bell.ca. [174.93.75.154])
        by smtp.gmail.com with ESMTPSA id
 p10sm7206792qtl.17.2021.04.13.14.36.42
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Tue, 13 Apr 2021 14:36:42 -0700 (PDT)
From: Peter Xu <peterx@redhat.com>
To: kvm@vger.kernel.org, linux-kernel@vger.kernel.org
Cc: peterx@redhat.com, Andrew Jones <drjones@redhat.com>,
        Paolo Bonzini <pbonzini@redhat.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Sean Christopherson <seanjc@google.com>
Subject: [PATCH v2] kvm/selftests: Fix race condition with dirty_log_test
Date: Tue, 13 Apr 2021 17:36:41 -0400
Message-Id: <20210413213641.23742-1-peterx@redhat.com>
X-Mailer: git-send-email 2.26.2
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This fixes a bug that can trigger with e.g. "taskset -c 0 ./dirty_log_test" or
when the testing host is very busy.

The issue is when the vcpu thread got the dirty bit set but got preempted by
other threads _before_ the data is written, we won't be able to see the latest
data only until the vcpu threads do VMENTER. IOW, the guest write operation and
dirty bit set cannot guarantee atomicity. The race could look like:

    main thread                            vcpu thread
    ===========                            ===========
    iteration=X
                                           *addr = X
                                           (so latest data is X)
    iteration=X+1
    ...
    iteration=X+N
                                           guest executes "*addr = X+N"
                                             reg=READ_ONCE(iteration)=X+N
                                             host page fault
                                               set dirty bit for page "addr"
                                             (_before_ VMENTER happens...
                                              so *addr is still X!)
                                           vcpu thread got preempted
    get dirty log
    verify data
      detected dirty bit set, data is X
      not X+N nor X+N-1, data too old!

This patch closes this race by allowing the main thread to give the vcpu thread
chance to do a VMENTER to complete that write operation.  It's done by adding a
vcpu loop counter (must be defined as volatile as main thread will do read
loop), then the main thread can guarantee the vcpu got at least another VMENTER
by making sure the guest_vcpu_loops increases by 2.

Dirty ring does not need this since dirty_ring_last_page would already help
avoid this specific race condition.

Cc: Andrew Jones <drjones@redhat.com>
Cc: Paolo Bonzini <pbonzini@redhat.com>
Cc: Vitaly Kuznetsov <vkuznets@redhat.com>
Cc: Sean Christopherson <seanjc@google.com>
Signed-off-by: Peter Xu <peterx@redhat.com>
---
v2:
- drop one unnecessary check on "!matched"
---
 tools/testing/selftests/kvm/dirty_log_test.c | 53 +++++++++++++++++++-
 1 file changed, 52 insertions(+), 1 deletion(-)

```
#### [RFC PATCH v4 1/4] vfio-ccw: Check initialized flag in cp_init()
##### From: Eric Farman <farman@linux.ibm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Eric Farman <farman@linux.ibm.com>
X-Patchwork-Id: 12201275
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.8 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT
	autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 64512C43460
	for <kvm@archiver.kernel.org>; Tue, 13 Apr 2021 18:24:20 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 430B5613C3
	for <kvm@archiver.kernel.org>; Tue, 13 Apr 2021 18:24:20 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1347650AbhDMSYj (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 13 Apr 2021 14:24:39 -0400
Received: from mx0a-001b2d01.pphosted.com ([148.163.156.1]:59878 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1347643AbhDMSYi (ORCPT
        <rfc822;kvm@vger.kernel.org>); Tue, 13 Apr 2021 14:24:38 -0400
Received: from pps.filterd (m0098393.ppops.net [127.0.0.1])
        by mx0a-001b2d01.pphosted.com (8.16.0.43/8.16.0.43) with SMTP id
 13DI3MYB141482;
        Tue, 13 Apr 2021 14:24:18 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=ibm.com;
 h=from : to : cc : subject
 : date : message-id : in-reply-to : references : mime-version :
 content-transfer-encoding; s=pp1;
 bh=iVZvMMs/efkGygppdSTS1PcuDAYDe00R8Isl46tHuf0=;
 b=AjpSak88hNl6SWLyUIVYPZ79n+3x92zjBNRmaf0kaht9luEPRWaI1itrCzkuBQts4BrS
 OLT4movdH2ygoo0PllvLbzFVRJcrZPedtgK0BTqxkxRh++69Nr0oTYzx9CONJf/pG7hb
 vF3HKuiDTiGxUItRnrYpmE9b509B1XA4rYkoiqXao5/KKalSwBztcMXsKFsMQDuM7OlI
 g2WrWYa3RZpCh8LvoKfvRY65JlRjifZbPW87Bg+msiyziLG0Ttxkgmuxryjl435ehgQQ
 bO69OCy2rqSVi1gR1a/lcYzJleUd4P877b3gbARsnJXtK7voDMxu/JqNXRrbIbyJJEhO cQ==
Received: from pps.reinject (localhost [127.0.0.1])
        by mx0a-001b2d01.pphosted.com with ESMTP id 37vkpk1yxh-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Tue, 13 Apr 2021 14:24:18 -0400
Received: from m0098393.ppops.net (m0098393.ppops.net [127.0.0.1])
        by pps.reinject (8.16.0.43/8.16.0.43) with SMTP id 13DI3cHU142836;
        Tue, 13 Apr 2021 14:24:18 -0400
Received: from ppma04ams.nl.ibm.com (63.31.33a9.ip4.static.sl-reverse.com
 [169.51.49.99])
        by mx0a-001b2d01.pphosted.com with ESMTP id 37vkpk1ywn-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Tue, 13 Apr 2021 14:24:18 -0400
Received: from pps.filterd (ppma04ams.nl.ibm.com [127.0.0.1])
        by ppma04ams.nl.ibm.com (8.16.0.43/8.16.0.43) with SMTP id
 13DIMXMG002366;
        Tue, 13 Apr 2021 18:24:15 GMT
Received: from b06cxnps4074.portsmouth.uk.ibm.com
 (d06relay11.portsmouth.uk.ibm.com [9.149.109.196])
        by ppma04ams.nl.ibm.com with ESMTP id 37u3n8tueh-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Tue, 13 Apr 2021 18:24:15 +0000
Received: from d06av25.portsmouth.uk.ibm.com (d06av25.portsmouth.uk.ibm.com
 [9.149.105.61])
        by b06cxnps4074.portsmouth.uk.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id 13DIOCBX23724502
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Tue, 13 Apr 2021 18:24:13 GMT
Received: from d06av25.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id D90BD11C050;
        Tue, 13 Apr 2021 18:24:12 +0000 (GMT)
Received: from d06av25.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id C777211C04A;
        Tue, 13 Apr 2021 18:24:12 +0000 (GMT)
Received: from tuxmaker.boeblingen.de.ibm.com (unknown [9.152.85.9])
        by d06av25.portsmouth.uk.ibm.com (Postfix) with ESMTPS;
        Tue, 13 Apr 2021 18:24:12 +0000 (GMT)
Received: by tuxmaker.boeblingen.de.ibm.com (Postfix, from userid 4958)
        id 7BE81E047D; Tue, 13 Apr 2021 20:24:12 +0200 (CEST)
From: Eric Farman <farman@linux.ibm.com>
To: Cornelia Huck <cohuck@redhat.com>,
        Halil Pasic <pasic@linux.ibm.com>
Cc: Matthew Rosato <mjrosato@linux.ibm.com>,
        Jared Rossi <jrossi@linux.ibm.com>, linux-s390@vger.kernel.org,
        kvm@vger.kernel.org, Eric Farman <farman@linux.ibm.com>
Subject: [RFC PATCH v4 1/4] vfio-ccw: Check initialized flag in cp_init()
Date: Tue, 13 Apr 2021 20:24:07 +0200
Message-Id: <20210413182410.1396170-2-farman@linux.ibm.com>
X-Mailer: git-send-email 2.25.1
In-Reply-To: <20210413182410.1396170-1-farman@linux.ibm.com>
References: <20210413182410.1396170-1-farman@linux.ibm.com>
MIME-Version: 1.0
X-TM-AS-GCONF: 00
X-Proofpoint-GUID: pZGF1yLkdtTN5uVk2a90FKzpxvWor71P
X-Proofpoint-ORIG-GUID: V3XYCC8bXPrg0PiTPVs0pJRNcQvobB58
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.391,18.0.761
 definitions=2021-04-13_12:2021-04-13,2021-04-13 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 suspectscore=0 spamscore=0
 impostorscore=0 malwarescore=0 mlxlogscore=999 mlxscore=0
 lowpriorityscore=0 clxscore=1015 adultscore=0 phishscore=0
 priorityscore=1501 bulkscore=0 classifier=spam adjust=0 reason=mlx
 scancount=1 engine=8.12.0-2104060000 definitions=main-2104130122
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

We have a really nice flag in the channel_program struct that
indicates if it had been initialized by cp_init(), and use it
as a guard in the other cp accessor routines, but not for a
duplicate call into cp_init(). The possibility of this occurring
is low, because that flow is protected by the private->io_mutex
and FSM CP_PROCESSING state. But then why bother checking it
in (for example) cp_prefetch() then?

Let's just be consistent and check for that in cp_init() too.

Fixes: 71189f263f8a3 ("vfio-ccw: make it safe to access channel programs")
Signed-off-by: Eric Farman <farman@linux.ibm.com>
---
 drivers/s390/cio/vfio_ccw_cp.c | 4 ++++
 1 file changed, 4 insertions(+)

```
#### [PATCH 1/3] vfio/iommu_type1: Add HWDBM status maintanance
##### From: Keqian Zhu <zhukeqian1@huawei.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Keqian Zhu <zhukeqian1@huawei.com>
X-Patchwork-Id: 12199745
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.7 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED,USER_AGENT_GIT
	autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id ADD3AC433B4
	for <kvm@archiver.kernel.org>; Tue, 13 Apr 2021 09:15:20 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 89A33610CE
	for <kvm@archiver.kernel.org>; Tue, 13 Apr 2021 09:15:20 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S245440AbhDMJPh (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 13 Apr 2021 05:15:37 -0400
Received: from szxga05-in.huawei.com ([45.249.212.191]:16549 "EHLO
        szxga05-in.huawei.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S245281AbhDMJPc (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 13 Apr 2021 05:15:32 -0400
Received: from DGGEMS412-HUB.china.huawei.com (unknown [172.30.72.59])
        by szxga05-in.huawei.com (SkyGuard) with ESMTP id 4FKKcg0RjGzPqkx;
        Tue, 13 Apr 2021 17:12:19 +0800 (CST)
Received: from DESKTOP-5IS4806.china.huawei.com (10.174.187.224) by
 DGGEMS412-HUB.china.huawei.com (10.3.19.212) with Microsoft SMTP Server id
 14.3.498.0; Tue, 13 Apr 2021 17:15:02 +0800
From: Keqian Zhu <zhukeqian1@huawei.com>
To: <linux-kernel@vger.kernel.org>, <kvm@vger.kernel.org>,
        Alex Williamson <alex.williamson@redhat.com>,
        Kirti Wankhede <kwankhede@nvidia.com>,
        "Cornelia Huck" <cohuck@redhat.com>,
        Yi Sun <yi.y.sun@linux.intel.com>,
        Tian Kevin <kevin.tian@intel.com>
CC: Robin Murphy <robin.murphy@arm.com>, Will Deacon <will@kernel.org>,
        "Joerg Roedel" <joro@8bytes.org>,
        Jean-Philippe Brucker <jean-philippe@linaro.org>,
        Jonathan Cameron <Jonathan.Cameron@huawei.com>,
        Lu Baolu <baolu.lu@linux.intel.com>,
        <wanghaibin.wang@huawei.com>, <jiangkunkun@huawei.com>,
        <yuzenghui@huawei.com>, <lushenming@huawei.com>
Subject: [PATCH 1/3] vfio/iommu_type1: Add HWDBM status maintanance
Date: Tue, 13 Apr 2021 17:14:43 +0800
Message-ID: <20210413091445.7448-2-zhukeqian1@huawei.com>
X-Mailer: git-send-email 2.8.4.windows.1
In-Reply-To: <20210413091445.7448-1-zhukeqian1@huawei.com>
References: <20210413091445.7448-1-zhukeqian1@huawei.com>
MIME-Version: 1.0
X-Originating-IP: [10.174.187.224]
X-CFilter-Loop: Reflected
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Kunkun Jiang <jiangkunkun@huawei.com>

We are going to optimize dirty log tracking based on iommu
HWDBM feature, but the dirty log from iommu is useful only
when all iommu backed groups are with HWDBM feature.

This maintains a counter in vfio_iommu, which is used in
the policy of dirty bitmap population in next patch.

This also maintains a counter in vfio_domain, which is used
in the policy of switch dirty log in next patch.

Co-developed-by: Keqian Zhu <zhukeqian1@huawei.com>
Signed-off-by: Kunkun Jiang <jiangkunkun@huawei.com>
Reported-by: kernel test robot <lkp@intel.com>
---
 drivers/vfio/vfio_iommu_type1.c | 44 +++++++++++++++++++++++++++++++++
 1 file changed, 44 insertions(+)

```
#### [PATCH] vhost-vdpa: fix vm_flags for virtqueue doorbell mapping
##### From: Jason Wang <jasowang@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Jason Wang <jasowang@redhat.com>
X-Patchwork-Id: 12199749
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-15.8 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_CR_TRAILER,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS
	autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 97C9AC433B4
	for <kvm@archiver.kernel.org>; Tue, 13 Apr 2021 09:16:11 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 71D7E6124B
	for <kvm@archiver.kernel.org>; Tue, 13 Apr 2021 09:16:11 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S245527AbhDMJQ3 (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 13 Apr 2021 05:16:29 -0400
Received: from us-smtp-delivery-124.mimecast.com ([216.205.24.124]:41095 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S245464AbhDMJQ2 (ORCPT
        <rfc822;kvm@vger.kernel.org>); Tue, 13 Apr 2021 05:16:28 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1618305369;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=Nsxd662d4i8x3VCivCNK0fCVgM6UOW8+ULBoukCe2ZU=;
        b=XzHgYoeeOi/jORlKcDr3LeXl1Nh38GUr8j5IBeAp4zhYK5PkFzxxfbpNDpUkj3eMQWaC7a
        Hu+BLZd5IJ/j6IQ7JWlLMy6nBVcQOQKmNB8laQTdIZ8idGkvY3N+bQPndPlY5MUT1ZyMhd
        JdNMT5VOZuKn2xeoR6Zz8xGjUkKRgNs=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-71-x88dCRRUMHWcrN8rL8uRAw-1; Tue, 13 Apr 2021 05:16:07 -0400
X-MC-Unique: x88dCRRUMHWcrN8rL8uRAw-1
Received: from smtp.corp.redhat.com (int-mx02.intmail.prod.int.phx2.redhat.com
 [10.5.11.12])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id CD9BD107ACCA;
        Tue, 13 Apr 2021 09:16:05 +0000 (UTC)
Received: from localhost.localdomain (ovpn-13-128.pek2.redhat.com
 [10.72.13.128])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 55CC360C04;
        Tue, 13 Apr 2021 09:15:59 +0000 (UTC)
From: Jason Wang <jasowang@redhat.com>
To: mst@redhat.com, jasowang@redhat.com
Cc: kvm@vger.kernel.org, virtualization@lists.linux-foundation.org,
        netdev@vger.kernel.org, linux-kernel@vger.kernel.org,
        stable@vger.kernel.org
Subject: [PATCH] vhost-vdpa: fix vm_flags for virtqueue doorbell mapping
Date: Tue, 13 Apr 2021 17:15:57 +0800
Message-Id: <20210413091557.29008-1-jasowang@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.12
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The virtqueue doorbell is usually implemented via registeres but we
don't provide the necessary vma->flags like VM_PFNMAP. This may cause
several issues e.g when userspace tries to map the doorbell via vhost
IOTLB, kernel may panic due to the page is not backed by page
structure. This patch fixes this by setting the necessary
vm_flags. With this patch, try to map doorbell via IOTLB will fail
with bad address.

Cc: stable@vger.kernel.org
Fixes: ddd89d0a059d ("vhost_vdpa: support doorbell mapping via mmap")
Signed-off-by: Jason Wang <jasowang@redhat.com>
---
 drivers/vhost/vdpa.c | 1 +
 1 file changed, 1 insertion(+)

```
#### [RFC PATCH v8 01/19] af_vsock: update functions for connectible socket
##### From: Arseny Krasnov <arseny.krasnov@kaspersky.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Arseny Krasnov <arseny.krasnov@kaspersky.com>
X-Patchwork-Id: 12200439
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-18.8 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_CR_TRAILER,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,
	URIBL_BLOCKED,USER_AGENT_GIT autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 71898C433B4
	for <kvm@archiver.kernel.org>; Tue, 13 Apr 2021 12:42:31 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 4BBBB613B2
	for <kvm@archiver.kernel.org>; Tue, 13 Apr 2021 12:42:31 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S241583AbhDMMms (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 13 Apr 2021 08:42:48 -0400
Received: from mx13.kaspersky-labs.com ([91.103.66.164]:17970 "EHLO
        mx13.kaspersky-labs.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S230449AbhDMMmj (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 13 Apr 2021 08:42:39 -0400
Received: from relay13.kaspersky-labs.com (unknown [127.0.0.10])
        by relay13.kaspersky-labs.com (Postfix) with ESMTP id F1F90521AA6;
        Tue, 13 Apr 2021 15:42:11 +0300 (MSK)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=kaspersky.com;
        s=mail202102; t=1618317732;
        bh=7V0qJTfgvKn7DqBrci7B51rUAZRCsxVmFMp+iIHYzHo=;
        h=From:To:Subject:Date:Message-ID:MIME-Version:Content-Type;
        b=na13nWx8EVmQbRya4XhlegxC0gmDRxYHfMPoYPHJMtaoOptwx6G+WC0lygib5r6Yc
         U+Yni+FHuncY2xn3kxdR8wyGc7F9XIvHC+5IJG3DBEFI6xIOLffWJVFYFFVhk/z91c
         rn61ICR2PJ6dknLYUH825O2qvrKxQtnTS62noRdCaYEaNHxskDlE9GZ3I0sRo+G74L
         Esr9NwlcVpMowxnjTEn2wgzHSTEILzt153wKsOYimszMbMZke55MxeraLpkrx1ZA1j
         aPrrVdeQSuDBCohBZ6lzJXgtMyI6FaniK4+/Q2dJkSEkvOsoB+8l+T+nvT4gHXM8KZ
         MoMpnazIBrgAw==
Received: from mail-hq2.kaspersky.com (unknown [91.103.66.206])
        (using TLSv1.2 with cipher ECDHE-RSA-AES128-SHA256 (128/128 bits))
        (Client CN "mail-hq2.kaspersky.com",
 Issuer "Kaspersky MailRelays CA G3" (verified OK))
        by mailhub13.kaspersky-labs.com (Postfix) with ESMTPS id 9B113521AAC;
        Tue, 13 Apr 2021 15:42:11 +0300 (MSK)
Received: from arseniy-pc.avp.ru (10.64.68.128) by hqmailmbx3.avp.ru
 (10.64.67.243) with Microsoft SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_128_CBC_SHA256_P256) id 15.1.2176.2; Tue, 13
 Apr 2021 15:42:11 +0300
From: Arseny Krasnov <arseny.krasnov@kaspersky.com>
To: Stefan Hajnoczi <stefanha@redhat.com>,
        Stefano Garzarella <sgarzare@redhat.com>,
        "Michael S. Tsirkin" <mst@redhat.com>,
        Jason Wang <jasowang@redhat.com>,
        "David S. Miller" <davem@davemloft.net>,
        Jakub Kicinski <kuba@kernel.org>,
        Jorgen Hansen <jhansen@vmware.com>,
        Norbert Slusarek <nslusarek@gmx.net>,
        Andra Paraschiv <andraprs@amazon.com>,
        Colin Ian King <colin.king@canonical.com>,
        Jeff Vander Stoep <jeffv@google.com>,
        Alexander Popov <alex.popov@linux.com>
CC: <kvm@vger.kernel.org>, <virtualization@lists.linux-foundation.org>,
        <netdev@vger.kernel.org>, <linux-kernel@vger.kernel.org>,
        <stsp2@yandex.ru>, <arseny.krasnov@kaspersky.com>,
        <oxffffaa@gmail.com>
Subject: [RFC PATCH v8 01/19] af_vsock: update functions for connectible
 socket
Date: Tue, 13 Apr 2021 15:41:56 +0300
Message-ID: <20210413124159.3399062-1-arseny.krasnov@kaspersky.com>
X-Mailer: git-send-email 2.25.1
In-Reply-To: <20210413123954.3396314-1-arseny.krasnov@kaspersky.com>
References: <20210413123954.3396314-1-arseny.krasnov@kaspersky.com>
MIME-Version: 1.0
X-Originating-IP: [10.64.68.128]
X-ClientProxiedBy: hqmailmbx2.avp.ru (10.64.67.242) To hqmailmbx3.avp.ru
 (10.64.67.243)
X-KSE-ServerInfo: hqmailmbx3.avp.ru, 9
X-KSE-AntiSpam-Interceptor-Info: scan successful
X-KSE-AntiSpam-Version: 5.9.20, Database issued on: 04/13/2021 12:26:17
X-KSE-AntiSpam-Status: KAS_STATUS_NOT_DETECTED
X-KSE-AntiSpam-Method: none
X-KSE-AntiSpam-Rate: 10
X-KSE-AntiSpam-Info: Lua profiles 163057 [Apr 13 2021]
X-KSE-AntiSpam-Info: Version: 5.9.20.0
X-KSE-AntiSpam-Info: Envelope from: arseny.krasnov@kaspersky.com
X-KSE-AntiSpam-Info: LuaCore: 442 442 b985cb57763b61d2a20abb585d5d4cc10c315b09
X-KSE-AntiSpam-Info: {Prob_from_in_msgid}
X-KSE-AntiSpam-Info: {Tracking_from_domain_doesnt_match_to}
X-KSE-AntiSpam-Info: 
 d41d8cd98f00b204e9800998ecf8427e.com:7.1.1;arseniy-pc.avp.ru:7.1.1;127.0.0.199:7.1.2;kaspersky.com:7.1.1
X-KSE-AntiSpam-Info: Rate: 10
X-KSE-AntiSpam-Info: Status: not_detected
X-KSE-AntiSpam-Info: Method: none
X-KSE-Antiphishing-Info: Clean
X-KSE-Antiphishing-ScanningType: Deterministic
X-KSE-Antiphishing-Method: None
X-KSE-Antiphishing-Bases: 04/13/2021 12:28:00
X-KSE-AttachmentFiltering-Interceptor-Info: no applicable attachment filtering
 rules found
X-KSE-Antivirus-Interceptor-Info: scan successful
X-KSE-Antivirus-Info: Clean, bases: 13.04.2021 10:53:00
X-KSE-BulkMessagesFiltering-Scan-Result: InTheLimit
X-KSE-AttachmentFiltering-Interceptor-Info: no applicable attachment filtering
 rules found
X-KSE-BulkMessagesFiltering-Scan-Result: InTheLimit
X-KLMS-Rule-ID: 52
X-KLMS-Message-Action: clean
X-KLMS-AntiSpam-Status: not scanned, disabled by settings
X-KLMS-AntiSpam-Interceptor-Info: not scanned
X-KLMS-AntiPhishing: Clean, bases: 2021/04/13 07:05:00
X-KLMS-AntiVirus: Kaspersky Security for Linux Mail Server, version 8.0.3.30,
 bases: 2021/04/13 03:14:00 #16587160
X-KLMS-AntiVirus-Status: Clean, skipped
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This prepares af_vsock.c for SEQPACKET support: some functions such
as setsockopt(), getsockopt(), connect(), recvmsg(), sendmsg() are
shared between both types of sockets, so rename them in general
manner.

Signed-off-by: Arseny Krasnov <arseny.krasnov@kaspersky.com>
Reviewed-by: Stefano Garzarella <sgarzare@redhat.com>
---
 net/vmw_vsock/af_vsock.c | 64 +++++++++++++++++++++-------------------
 1 file changed, 34 insertions(+), 30 deletions(-)

```
