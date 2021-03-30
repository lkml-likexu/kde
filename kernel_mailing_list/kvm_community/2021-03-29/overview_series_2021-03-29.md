#### [PATCH v2 1/2] KVM: x86: hyper-v: Properly divide maybe-negative 'hv_clock->system_time' in compute_tsc_page_parameters()
##### From: Vitaly Kuznetsov <vkuznets@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Vitaly Kuznetsov <vkuznets@redhat.com>
X-Patchwork-Id: 12169971
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.0 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_CR_TRAILER,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS
	autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id C23DAC433C1
	for <kvm@archiver.kernel.org>; Mon, 29 Mar 2021 11:49:01 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 8DA4261930
	for <kvm@archiver.kernel.org>; Mon, 29 Mar 2021 11:49:01 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S231295AbhC2Lsd (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Mon, 29 Mar 2021 07:48:33 -0400
Received: from us-smtp-delivery-124.mimecast.com ([63.128.21.124]:54031 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S231322AbhC2LsM (ORCPT
        <rfc822;kvm@vger.kernel.org>); Mon, 29 Mar 2021 07:48:12 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1617018492;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding:
         in-reply-to:in-reply-to:references:references;
        bh=DJNvcB1fUL2ck9v3qFq4z8Aij/Mol/eyuXm3sbGS/ac=;
        b=RTq/k/kau5uD0SvIzj64u/f/HrY0jmwQrdvlehKnRIVSOPV1VJ7EfFbO+/LxR9ernbc/fA
        QCPbROd3zIOs5W/QG6m2Hy64sk8UB74T19BASDOmyMb8RFTjJZAu2wVAgOfR6DjunhDplC
        +3C7faFSqK4Oq7McHNLdPafumhzMVQI=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-536-UasKfQbnOzaFv-fDGxFphg-1; Mon, 29 Mar 2021 07:48:10 -0400
X-MC-Unique: UasKfQbnOzaFv-fDGxFphg-1
Received: from smtp.corp.redhat.com (int-mx07.intmail.prod.int.phx2.redhat.com
 [10.5.11.22])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 1512E180FCA1;
        Mon, 29 Mar 2021 11:48:09 +0000 (UTC)
Received: from vitty.brq.redhat.com (unknown [10.40.195.155])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 2F7A0100239A;
        Mon, 29 Mar 2021 11:48:07 +0000 (UTC)
From: Vitaly Kuznetsov <vkuznets@redhat.com>
To: kvm@vger.kernel.org, Paolo Bonzini <pbonzini@redhat.com>
Cc: Sean Christopherson <seanjc@google.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Marcelo Tosatti <mtosatti@redhat.com>
Subject: [PATCH v2 1/2] KVM: x86: hyper-v: Properly divide maybe-negative
 'hv_clock->system_time' in compute_tsc_page_parameters()
Date: Mon, 29 Mar 2021 13:47:59 +0200
Message-Id: <20210329114800.164066-2-vkuznets@redhat.com>
In-Reply-To: <20210329114800.164066-1-vkuznets@redhat.com>
References: <20210329114800.164066-1-vkuznets@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.84 on 10.5.11.22
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

When guest time is reset with KVM_SET_CLOCK(0), it is possible for
hv_clock->system_time to become a small negative number. This happens
because in KVM_SET_CLOCK handling we set kvm->arch.kvmclock_offset based
on get_kvmclock_ns(kvm) but when KVM_REQ_CLOCK_UPDATE is handled,
kvm_guest_time_update() does

hv_clock.system_time = ka->master_kernel_ns + v->kvm->arch.kvmclock_offset;

And 'master_kernel_ns' represents the last time when masterclock
got updated, it can precede KVM_SET_CLOCK() call. Normally, this is not a
problem, the difference is very small, e.g. I'm observing
hv_clock.system_time = -70 ns. The issue comes from the fact that
'hv_clock.system_time' is stored as unsigned and 'system_time / 100' in
compute_tsc_page_parameters() becomes a very big number.

Use div_s64() to get the proper result when dividing maybe-negative
'hv_clock.system_time' by 100.

Signed-off-by: Vitaly Kuznetsov <vkuznets@redhat.com>
---
 arch/x86/kvm/hyperv.c | 9 ++++++---
 1 file changed, 6 insertions(+), 3 deletions(-)

```
#### [PATCH v4 01/16] perf/x86/intel: Add x86_pmu.pebs_vmx for Ice Lake Servers
##### From: Like Xu <like.xu@linux.intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Like Xu <like.xu@linux.intel.com>
X-Patchwork-Id: 12169539
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.8 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT
	autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 23AC5C433DB
	for <kvm@archiver.kernel.org>; Mon, 29 Mar 2021 05:50:14 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id F2B296196B
	for <kvm@archiver.kernel.org>; Mon, 29 Mar 2021 05:50:13 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S230305AbhC2Ftk (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Mon, 29 Mar 2021 01:49:40 -0400
Received: from mga07.intel.com ([134.134.136.100]:15632 "EHLO mga07.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S229468AbhC2Ft2 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 29 Mar 2021 01:49:28 -0400
IronPort-SDR: 
 0viyCxzUsbqQCWCHQkE4OKWt7i49TgllzZY08vquI8PVM3E2NPnTEftUBOvIDjH6FugfEMaV/L
 p1UuteD0K4YA==
X-IronPort-AV: E=McAfee;i="6000,8403,9937"; a="255478709"
X-IronPort-AV: E=Sophos;i="5.81,285,1610438400";
   d="scan'208";a="255478709"
Received: from orsmga008.jf.intel.com ([10.7.209.65])
  by orsmga105.jf.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 28 Mar 2021 22:49:27 -0700
IronPort-SDR: 
 5DGESYEAgWUbBzkfQlAiWkXU2FXzba3V1jdjOY+wT/G7KdHr25rKpbs9G9GMeGTtJhpFGvKvom
 uJ4sAb5ayHBw==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.81,285,1610438400";
   d="scan'208";a="417506679"
Received: from clx-ap-likexu.sh.intel.com ([10.239.48.108])
  by orsmga008.jf.intel.com with ESMTP; 28 Mar 2021 22:49:24 -0700
From: Like Xu <like.xu@linux.intel.com>
To: peterz@infradead.org, Sean Christopherson <seanjc@google.com>,
        Paolo Bonzini <pbonzini@redhat.com>
Cc: eranian@google.com, andi@firstfloor.org, kan.liang@linux.intel.com,
        wei.w.wang@intel.com, Wanpeng Li <wanpengli@tencent.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>, kvm@vger.kernel.org,
        x86@kernel.org, linux-kernel@vger.kernel.org,
        Like Xu <like.xu@linux.intel.com>
Subject: [PATCH v4 01/16] perf/x86/intel: Add x86_pmu.pebs_vmx for Ice Lake
 Servers
Date: Mon, 29 Mar 2021 13:41:22 +0800
Message-Id: <20210329054137.120994-2-like.xu@linux.intel.com>
X-Mailer: git-send-email 2.29.2
In-Reply-To: <20210329054137.120994-1-like.xu@linux.intel.com>
References: <20210329054137.120994-1-like.xu@linux.intel.com>
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The new hardware facility supporting guest PEBS is only available
on Intel Ice Lake Server platforms for now. KVM will check this field
through perf_get_x86_pmu_capability() instead of hard coding the cpu
models in the KVM code. If it is supported, the guest PBES capability
will be exposed to the guest.

Signed-off-by: Like Xu <like.xu@linux.intel.com>
---
 arch/x86/events/core.c            | 1 +
 arch/x86/events/intel/core.c      | 1 +
 arch/x86/events/perf_event.h      | 3 ++-
 arch/x86/include/asm/perf_event.h | 1 +
 4 files changed, 5 insertions(+), 1 deletion(-)

```
#### [PATCH] KVM: X86: Properly account for guest CPU time when considering context tracking
##### From: Wanpeng Li <kernellwp@gmail.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Wanpeng Li <kernellwp@gmail.com>
X-Patchwork-Id: 12169859
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-15.8 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,DKIM_VALID_AU,FREEMAIL_FORGED_FROMDOMAIN,FREEMAIL_FROM,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT
	autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 6C890C433DB
	for <kvm@archiver.kernel.org>; Mon, 29 Mar 2021 09:45:08 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 42A2361883
	for <kvm@archiver.kernel.org>; Mon, 29 Mar 2021 09:45:08 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S231862AbhC2Jog (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Mon, 29 Mar 2021 05:44:36 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:39116 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S231661AbhC2JoL (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 29 Mar 2021 05:44:11 -0400
Received: from mail-pj1-x102e.google.com (mail-pj1-x102e.google.com
 [IPv6:2607:f8b0:4864:20::102e])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 45760C061574;
        Mon, 29 Mar 2021 02:44:10 -0700 (PDT)
Received: by mail-pj1-x102e.google.com with SMTP id
 kr3-20020a17090b4903b02900c096fc01deso5646699pjb.4;
        Mon, 29 Mar 2021 02:44:10 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=from:to:cc:subject:date:message-id;
        bh=U5U4X+ZOhi4vgTgaFmTIVBDWOm8KVT4HEd/HA9LL9Zg=;
        b=DlatJVXkwqLPHmaVGR45p/BOWtcCxdavc35cLcf00aTgyWgqryDueTSl1vW8kxxBII
         QuBWhR7SRW/ojJsXogmNVx1sXCkbmilH1C7Kw4sZ/XHsrQt7eACRMgnY7/N9LH7b/Gam
         3y39+pTcse9g45vH7WegK0gdUgdofxWrQZ8w31NaI0AAhrLcZtOhD2iQ1/sb0HxUqygF
         wX/Mt/71CHLgpZVXVZeCA1SiC5Uir1FFLmJnZftO47eeF/doW9zKaLjzXaSis/fGKedR
         3jU+KXRZZtISrvHYdasYok5VHX5nxpr3ltxMAj/nzntl0nLGeWrkG4m9c07xdvIGyk8Z
         opFw==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id;
        bh=U5U4X+ZOhi4vgTgaFmTIVBDWOm8KVT4HEd/HA9LL9Zg=;
        b=mThAy4Y98c8YKTdeq1EHhXzJQJtmRQo6JEvlJ7ryKrgltJO9LXGUSjMm5wAvFEP9lv
         SLxGTNRaKVGAE4/XqSzetLXY3eqjjqQVjfXJSEOYQ13Nkyc2i4to7HSQoaSXA0MDSFUw
         Ici+P1w5E0WPNOMea/zzR/6IgzwgN1szyNvCOFPKhb0f1EootnWwiMkH2skbNde/js2j
         0HMwL+vZop8+WVgPsrEvOUiCo2zCi0lpXnNaxz8NPEJP68sSSRmgAArrOtrOLXmVsoEu
         tiIF9rE/kV9iq4O4/cgDdBrER06SNxB/cas2PY/ItN9byVaXNOwSYrkVaYvWuqsL2+h+
         nV/A==
X-Gm-Message-State: AOAM530NS28s6gfTPcUkOBuS3BvtdSoTcfCNIBJfc5+5fS3DZ0gToJ8e
        lzeVX8yfmOn7HU0+MZ63I9flyg5kl/k=
X-Google-Smtp-Source: 
 ABdhPJwzAifXMNB/rOR9vWitJtHt9JOBN4qz/C2AqKhgh6EHTSUfZ+yHjV8cBOJZo6E5k2AfGIrqTQ==
X-Received: by 2002:a17:902:e889:b029:e7:1490:9da5 with SMTP id
 w9-20020a170902e889b02900e714909da5mr22000247plg.20.1617011049985;
        Mon, 29 Mar 2021 02:44:09 -0700 (PDT)
Received: from localhost.localdomain ([103.7.29.6])
        by smtp.googlemail.com with ESMTPSA id
 f15sm15749610pgg.84.2021.03.29.02.44.07
        (version=TLS1_2 cipher=ECDHE-ECDSA-AES128-GCM-SHA256 bits=128/128);
        Mon, 29 Mar 2021 02:44:09 -0700 (PDT)
From: Wanpeng Li <kernellwp@gmail.com>
X-Google-Original-From: Wanpeng Li <wanpengli@tencent.com>
To: linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Cc: Paolo Bonzini <pbonzini@redhat.com>,
        Sean Christopherson <seanjc@google.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>
Subject: [PATCH] KVM: X86: Properly account for guest CPU time when
 considering context tracking
Date: Mon, 29 Mar 2021 17:43:56 +0800
Message-Id: <1617011036-11734-1-git-send-email-wanpengli@tencent.com>
X-Mailer: git-send-email 2.7.4
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Wanpeng Li <wanpengli@tencent.com>

The bugzilla https://bugzilla.kernel.org/show_bug.cgi?id=209831 
reported that the guest time remains 0 when running a while true 
loop in the guest.

The commit 87fa7f3e98a131 ("x86/kvm: Move context tracking where it 
belongs") moves guest_exit_irqoff() close to vmexit breaks the 
tick-based time accouting when the ticks that happen after IRQs are 
disabled are incorrectly accounted to the host/system time. This is 
because we exit the guest state too early.

vtime-based time accounting is tied to context tracking, keep the 
guest_exit_irqoff() around vmexit code when both vtime-based time 
accounting and specific cpu is context tracking mode active. 
Otherwise, leave guest_exit_irqoff() after handle_exit_irqoff() 
and explicit IRQ window for tick-based time accouting.

Fixes: 87fa7f3e98a131 ("x86/kvm: Move context tracking where it belongs")
Cc: Sean Christopherson <seanjc@google.com>
Signed-off-by: Wanpeng Li <wanpengli@tencent.com>
---
 arch/x86/kvm/svm/svm.c | 3 ++-
 arch/x86/kvm/vmx/vmx.c | 3 ++-
 arch/x86/kvm/x86.c     | 2 ++
 3 files changed, 6 insertions(+), 2 deletions(-)

```
#### [PATCH] KVM: x86/vPMU: Forbid reading from MSR_F15H_PERF MSRs when guest doesn't have X86_FEATURE_PERFCTR_CORE
##### From: Vitaly Kuznetsov <vkuznets@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Vitaly Kuznetsov <vkuznets@redhat.com>
X-Patchwork-Id: 12170061
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.0 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_CR_TRAILER,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS
	autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id C3836C433DB
	for <kvm@archiver.kernel.org>; Mon, 29 Mar 2021 12:48:51 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 86ED861874
	for <kvm@archiver.kernel.org>; Mon, 29 Mar 2021 12:48:51 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S231311AbhC2MsU (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Mon, 29 Mar 2021 08:48:20 -0400
Received: from us-smtp-delivery-124.mimecast.com ([63.128.21.124]:42124 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S231249AbhC2MsQ (ORCPT
        <rfc822;kvm@vger.kernel.org>); Mon, 29 Mar 2021 08:48:16 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1617022096;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=StRb7UVN5Yp/VEOKdrPoTELQdTs1f4wblUD2484mrPw=;
        b=UQJoXHai4wj6yoX5tj4sjSFmdrezsvYdwgFpr9lGqtdOWAwKNhXaecwjLIPvz2r2pwQ6JL
        S8wAOxqTsm/v7NfeysbtgBIxmblcvv+wTc8jiL7Sh8yeLZ6pbU84DMtueBnxc4FFJnsZhZ
        5m9lPQdLPJQZtHwAmJ6iSKNk3A04MY8=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-548-1cfcLZwAN1m63PTtdQ7PHQ-1; Mon, 29 Mar 2021 08:48:12 -0400
X-MC-Unique: 1cfcLZwAN1m63PTtdQ7PHQ-1
Received: from smtp.corp.redhat.com (int-mx08.intmail.prod.int.phx2.redhat.com
 [10.5.11.23])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 6593A1018F74;
        Mon, 29 Mar 2021 12:48:10 +0000 (UTC)
Received: from vitty.brq.redhat.com (unknown [10.40.195.155])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 9D58719C45;
        Mon, 29 Mar 2021 12:48:05 +0000 (UTC)
From: Vitaly Kuznetsov <vkuznets@redhat.com>
To: kvm@vger.kernel.org, Paolo Bonzini <pbonzini@redhat.com>
Cc: Sean Christopherson <seanjc@google.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Wei Huang <wei.huang2@amd.com>, Joerg Roedel <joro@8bytes.org>,
        Haiwei Li <lihaiwei.kernel@gmail.com>,
        linux-kernel@vger.kernel.org
Subject: [PATCH] KVM: x86/vPMU: Forbid reading from MSR_F15H_PERF MSRs when
 guest doesn't have X86_FEATURE_PERFCTR_CORE
Date: Mon, 29 Mar 2021 14:48:04 +0200
Message-Id: <20210329124804.170173-1-vkuznets@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.84 on 10.5.11.23
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

MSR_F15H_PERF_CTL0-5, MSR_F15H_PERF_CTR0-5 MSRs have a CPUID bit assigned
to them (X86_FEATURE_PERFCTR_CORE) and when it wasn't exposed to the guest
the correct behavior is to inject #GP an not just return zero.

Signed-off-by: Vitaly Kuznetsov <vkuznets@redhat.com>
---
 arch/x86/kvm/x86.c | 6 ++++++
 1 file changed, 6 insertions(+)

```
#### [PATCH v2 1/3] Linux headers: update from 5.12-rc3
##### From: Ravi Bangoria <ravi.bangoria@linux.ibm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Ravi Bangoria <ravi.bangoria@linux.ibm.com>
X-Patchwork-Id: 12169485
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.8 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT autolearn=ham
	autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 273A5C433DB
	for <kvm@archiver.kernel.org>; Mon, 29 Mar 2021 04:21:27 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id E55456195B
	for <kvm@archiver.kernel.org>; Mon, 29 Mar 2021 04:21:26 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S230143AbhC2EUz (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Mon, 29 Mar 2021 00:20:55 -0400
Received: from mx0a-001b2d01.pphosted.com ([148.163.156.1]:61904 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S229555AbhC2EUj (ORCPT
        <rfc822;kvm@vger.kernel.org>); Mon, 29 Mar 2021 00:20:39 -0400
Received: from pps.filterd (m0098396.ppops.net [127.0.0.1])
        by mx0a-001b2d01.pphosted.com (8.16.0.43/8.16.0.43) with SMTP id
 12T42ib4040679;
        Mon, 29 Mar 2021 00:20:05 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=ibm.com;
 h=from : to : cc : subject
 : date : message-id : in-reply-to : references : mime-version :
 content-transfer-encoding; s=pp1;
 bh=YEZuDOxWgq/0UQhu/+uZaF83miKU7XuYYuEv0GmFnYk=;
 b=GW2IckTfuCiMkJE16r1LuvzjWqV+cCKsX+gHkVqzyveUsf8RMcOiVesGC7wN9mMsjI04
 Hc5J1MjMtAVGo+IYaDsdhrycPMIhXNOzR3a8wKtJQTTiBa/RwEaRVbXkQwCSzGTaFLHb
 bdsSpkHx3xmJ29zXDKHFuU7/F1BGW/AIcD95YOXSXom1Rf2VR69vpf0UqQtZqLMR54S9
 z1p97e14W+VpjP2Ohtml3Gu6uSFp1bSqAqjznyg0olDZgwx5Q/bMxZfZM+UYiwH2r4zz
 AcHx50FBIRGyYHeNu3/ZPZZobJCVWotT0ah/GYG6T0OCSJSqHGvm+5+1C9BYEgZBVjgZ GA==
Received: from pps.reinject (localhost [127.0.0.1])
        by mx0a-001b2d01.pphosted.com with ESMTP id 37jhrtu6vs-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Mon, 29 Mar 2021 00:20:05 -0400
Received: from m0098396.ppops.net (m0098396.ppops.net [127.0.0.1])
        by pps.reinject (8.16.0.43/8.16.0.43) with SMTP id 12T44opt051280;
        Mon, 29 Mar 2021 00:20:05 -0400
Received: from ppma03fra.de.ibm.com (6b.4a.5195.ip4.static.sl-reverse.com
 [149.81.74.107])
        by mx0a-001b2d01.pphosted.com with ESMTP id 37jhrtu6uy-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Mon, 29 Mar 2021 00:20:04 -0400
Received: from pps.filterd (ppma03fra.de.ibm.com [127.0.0.1])
        by ppma03fra.de.ibm.com (8.16.0.43/8.16.0.43) with SMTP id
 12T4IBkR021987;
        Mon, 29 Mar 2021 04:20:02 GMT
Received: from b06cxnps3074.portsmouth.uk.ibm.com
 (d06relay09.portsmouth.uk.ibm.com [9.149.109.194])
        by ppma03fra.de.ibm.com with ESMTP id 37hvb80rqd-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Mon, 29 Mar 2021 04:20:02 +0000
Received: from d06av22.portsmouth.uk.ibm.com (d06av22.portsmouth.uk.ibm.com
 [9.149.105.58])
        by b06cxnps3074.portsmouth.uk.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id 12T4JxHN31981872
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Mon, 29 Mar 2021 04:20:00 GMT
Received: from d06av22.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id D0B994C040;
        Mon, 29 Mar 2021 04:19:59 +0000 (GMT)
Received: from d06av22.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id BD1A04C04A;
        Mon, 29 Mar 2021 04:19:56 +0000 (GMT)
Received: from bangoria.ibmuc.com (unknown [9.199.34.103])
        by d06av22.portsmouth.uk.ibm.com (Postfix) with ESMTP;
        Mon, 29 Mar 2021 04:19:56 +0000 (GMT)
From: Ravi Bangoria <ravi.bangoria@linux.ibm.com>
To: paulus@samba.org, david@gibson.dropbear.id.au
Cc: ravi.bangoria@linux.ibm.com, mpe@ellerman.id.au, mikey@neuling.org,
        pbonzini@redhat.com, mst@redhat.com, clg@kaod.org,
        qemu-ppc@nongnu.org, qemu-devel@nongnu.org, kvm@vger.kernel.org,
        cohuck@redhat.com
Subject: [PATCH v2 1/3] Linux headers: update from 5.12-rc3
Date: Mon, 29 Mar 2021 09:49:04 +0530
Message-Id: <20210329041906.213991-2-ravi.bangoria@linux.ibm.com>
X-Mailer: git-send-email 2.30.2
In-Reply-To: <20210329041906.213991-1-ravi.bangoria@linux.ibm.com>
References: <20210329041906.213991-1-ravi.bangoria@linux.ibm.com>
MIME-Version: 1.0
X-TM-AS-GCONF: 00
X-Proofpoint-GUID: Z-Jg92BeQT4k_GpsvrqPQbIt6PrHwfvN
X-Proofpoint-ORIG-GUID: 6r4HwkG0eFNpuj-SOPJnvG_F4F6OlFlq
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.369,18.0.761
 definitions=2021-03-29_02:2021-03-26,2021-03-29 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 mlxlogscore=999 mlxscore=0
 adultscore=0 lowpriorityscore=0 bulkscore=0 impostorscore=0 spamscore=0
 suspectscore=0 malwarescore=0 clxscore=1015 phishscore=0
 priorityscore=1501 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.12.0-2103250000 definitions=main-2103290029
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Update against Linux 5.12-rc3

Signed-off-by: Ravi Bangoria <ravi.bangoria@linux.ibm.com>
---
 include/standard-headers/drm/drm_fourcc.h      | 23 ++++++-
 include/standard-headers/linux/input.h         |  2 +-
 include/standard-headers/rdma/vmw_pvrdma-abi.h |  7 ++
 linux-headers/asm-generic/unistd.h             |  4 +-
 linux-headers/asm-mips/unistd_n32.h            |  1 +
 linux-headers/asm-mips/unistd_n64.h            |  1 +
 linux-headers/asm-mips/unistd_o32.h            |  1 +
 linux-headers/asm-powerpc/kvm.h                |  2 +
 linux-headers/asm-powerpc/unistd_32.h          |  1 +
 linux-headers/asm-powerpc/unistd_64.h          |  1 +
 linux-headers/asm-s390/unistd_32.h             |  1 +
 linux-headers/asm-s390/unistd_64.h             |  1 +
 linux-headers/asm-x86/kvm.h                    |  1 +
 linux-headers/asm-x86/unistd_32.h              |  1 +
 linux-headers/asm-x86/unistd_64.h              |  1 +
 linux-headers/asm-x86/unistd_x32.h             |  1 +
 linux-headers/linux/kvm.h                      | 89 ++++++++++++++++++++++++++
 linux-headers/linux/vfio.h                     | 27 ++++++++
 18 files changed, 161 insertions(+), 4 deletions(-)

```
#### [PATCH rc vfio] vfio/nvlink: Add missing SPAPR_TCE_IOMMU depends
##### From: Jason Gunthorpe <jgg@nvidia.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Jason Gunthorpe <jgg@nvidia.com>
X-Patchwork-Id: 12170831
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.0 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_CR_TRAILER,INCLUDES_PATCH,MAILING_LIST_MULTI,MSGID_FROM_MTA_HEADER,
	SPF_HELO_NONE,SPF_PASS autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 50842C433DB
	for <kvm@archiver.kernel.org>; Mon, 29 Mar 2021 19:01:04 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 1E7726191B
	for <kvm@archiver.kernel.org>; Mon, 29 Mar 2021 19:01:04 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S231451AbhC2TAc (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Mon, 29 Mar 2021 15:00:32 -0400
Received: from mail-bn8nam11on2064.outbound.protection.outlook.com
 ([40.107.236.64]:64065
        "EHLO NAM11-BN8-obe.outbound.protection.outlook.com"
        rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org with ESMTP
        id S230213AbhC2TAU (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 29 Mar 2021 15:00:20 -0400
ARC-Seal: i=1; a=rsa-sha256; s=arcselector9901; d=microsoft.com; cv=none;
 b=dDdCdOS0hyIWce3n0qtOCpgBnETSTuPiN+2D6q+LOtZDNgp0G8aP9MvOJCN+1i5aykjQAYMQjFdFIvE9yaP6w8bseBWTV9aro7uqMgmoetko5GpqfALFKXJm3h9RwzNYm/Z+vnzmZo9f9rp0b9YGBgrfr7D07ppgJzcD+4fpFzEMmYzNjDna823iPOViWFTUjQjHzqAibCjoMAz1fIHY9eMF1BLWPJf/kwbz+G9qtb5SquVq9lFh/EfNJVDnEtibx2wocakoaPCRhKbptF9FJcbhqXk2G5jOvGFXF54KA0QPxQG+0qW5w1DAy3sT/fntKWTAEI0dQvgKTVvZ54fPBA==
ARC-Message-Signature: i=1; a=rsa-sha256; c=relaxed/relaxed; d=microsoft.com;
 s=arcselector9901;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=e2n4EqVM+o4w5sAzXWAFiZ9Qolguc7yofag5xD+fTdU=;
 b=oTi/YvAqplYN+f+Z3RKhSCQr1N4EmbGEo+VTZe/jVBIydCLRU32S4jp7qaJoWoYRDO/bljloSL6X0P+l7rwyfxDL6tEoEf3gUcHykbgnfBdCS1havAmu+lBCzeGY21xSojENPugBIKRmqeE/LRpspYlV5LCVAhvY1sYVncT6bZC94AftAaa3LrC9Ib16WyxeE7kxqpKeUOKMzazV/Frz6MoxS6Ja7mcteCQLBE493Ki8q0/FvPUQ15pqWOIxZI4Ns/9Vo0oJnS40KE4YQKxOQuFZ+FQG3qcsshXv+XD+6x02ZERp6v1GRdnmeYIoFMCZUsFvsrp7SlDLRmEHNdqtZw==
ARC-Authentication-Results: i=1; mx.microsoft.com 1; spf=pass
 smtp.mailfrom=nvidia.com; dmarc=pass action=none header.from=nvidia.com;
 dkim=pass header.d=nvidia.com; arc=none
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=Nvidia.com;
 s=selector2;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=e2n4EqVM+o4w5sAzXWAFiZ9Qolguc7yofag5xD+fTdU=;
 b=h6LsqN6sFXUDGC32rALrkK6nZzeMR/06c4V2v6jCz8Y1JhZoahh2zwFrnqRVsRy7d+1D8W89AKwC0AaoCAruybeKT+amBgkUG0ExGA1ErdNdqp346jdTAk9bFkaJkHvlqDp+a9m5ov1bo11Kc++8A6ZViDRRDVCgGvpVIuXTQ8cwJVSEVhIxRyulB8C8iPVnzsfcZhpqSe9Z6hOwVaTLyOPwyghZpuMbzdRiQC1foG6hc4E2mu2fPKZs7cI7BT1jd0pvI6YdagxWLTpVbHV/Lqz6/CeZRZZQFCTuprCR/Ti6OYs8rjqNez6FHL0VZmZErcTyQ/+lXXITTroGMbTSOg==
Authentication-Results: redhat.com; dkim=none (message not signed)
 header.d=none;redhat.com; dmarc=none action=none header.from=nvidia.com;
Received: from DM6PR12MB3834.namprd12.prod.outlook.com (2603:10b6:5:14a::12)
 by DM6PR12MB2859.namprd12.prod.outlook.com (2603:10b6:5:15d::29) with
 Microsoft SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.3977.32; Mon, 29 Mar
 2021 19:00:18 +0000
Received: from DM6PR12MB3834.namprd12.prod.outlook.com
 ([fe80::1c62:7fa3:617b:ab87]) by DM6PR12MB3834.namprd12.prod.outlook.com
 ([fe80::1c62:7fa3:617b:ab87%6]) with mapi id 15.20.3977.033; Mon, 29 Mar 2021
 19:00:18 +0000
From: Jason Gunthorpe <jgg@nvidia.com>
To: Alex Williamson <alex.williamson@redhat.com>,
        Cornelia Huck <cohuck@redhat.com>, kvm@vger.kernel.org
Cc: Eric Auger <eric.auger@redhat.com>
Subject: [PATCH rc vfio] vfio/nvlink: Add missing SPAPR_TCE_IOMMU depends
Date: Mon, 29 Mar 2021 16:00:16 -0300
Message-Id: <0-v1-83dba9768fc3+419-vfio_nvlink2_kconfig_jgg@nvidia.com>
X-Originating-IP: [206.223.160.26]
X-ClientProxiedBy: CH2PR15CA0027.namprd15.prod.outlook.com
 (2603:10b6:610:51::37) To DM6PR12MB3834.namprd12.prod.outlook.com
 (2603:10b6:5:14a::12)
MIME-Version: 1.0
X-MS-Exchange-MessageSentRepresentingType: 1
Received: from mlx.ziepe.ca (206.223.160.26) by
 CH2PR15CA0027.namprd15.prod.outlook.com (2603:10b6:610:51::37) with Microsoft
 SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.3977.25 via Frontend
 Transport; Mon, 29 Mar 2021 19:00:17 +0000
Received: from jgg by mlx with local (Exim 4.94)        (envelope-from
 <jgg@nvidia.com>)        id 1lQx7Y-005byQ-CU; Mon, 29 Mar 2021 16:00:16 -0300
X-MS-PublicTrafficType: Email
X-MS-Office365-Filtering-Correlation-Id: 4a5eb1a3-3d85-4eb3-8bd7-08d8f2e4e4b4
X-MS-TrafficTypeDiagnostic: DM6PR12MB2859:
X-Microsoft-Antispam-PRVS: 
 <DM6PR12MB2859D4F55D0D7E3103FB431FC27E9@DM6PR12MB2859.namprd12.prod.outlook.com>
X-MS-Oob-TLC-OOBClassifiers: OLM:7691;
X-MS-Exchange-SenderADCheck: 1
X-Microsoft-Antispam: BCL:0;
X-Microsoft-Antispam-Message-Info: 
 cRvJMr6V9v2AFh2iMcJND+FCeEfFCTS/J4PSQTbon4yYrY9zV2HyvcpX1XzB6OzThBEbwjrjYYBdIkn0quD2m2I0Cc6jUjRKFLnjOl+RF1XpbotTh4lqgWBJWsdHs1uuVa+ybA/Zu3WgdXvv9XGSky9UMHTHm5vET6dtWPj/yBV/XN0cibP15QJZ0RhvSmMUzHz9b841LrD70WuBWMWqCAo8XY7Qyozk6liVivLxKBpeS+LFaGwyPzutARWAAqnNgUH1X6rdT/NrVkVryl6DzFbAPlLWF4cXknjRvbJF1u0aGnVe8cAV6zOwjV3//T0XJVsC3aOJcqYoF34eyosbrAIo8nalrMjLNHVy+RxOGpjhTW3/wZ282y0iHAjWMm5Zjh1tRbnP5rnsG6QRGOod6r9P45m//zXypUf8FBpLRrPGVhjYF/4xgWpMFCzH1IV/FQFHmjXMmKyFIoxNUUmm303meutjAYRdYxiYY1PwNr4l5G8VXJ774ZTMwdD7aW6tofgTCVYvDVu4V7MLkBIMmhJB6dcJySu83ESQ1G0gpLr1ojgXeFOKqZoP+tuApdHjaB+l2XbkletJyML+bUgZxGOXUbMcC0pGTNzm8/jJWn6mQnQVbRNfatCO4I1WTkT11EWjgMNf3whA1ycewOzA/ANc+CcuM3dM8H2QBAz07gr/i1JUiPtndTlIXP6RxvWR
X-Forefront-Antispam-Report: 
 CIP:255.255.255.255;CTRY:;LANG:en;SCL:1;SRV:;IPV:NLI;SFV:NSPM;H:DM6PR12MB3834.namprd12.prod.outlook.com;PTR:;CAT:NONE;SFS:(4636009)(346002)(376002)(366004)(39860400002)(136003)(396003)(26005)(4326008)(66476007)(186003)(9746002)(5660300002)(426003)(110136005)(9786002)(8676002)(38100700001)(2616005)(66556008)(83380400001)(86362001)(8936002)(36756003)(2906002)(66946007)(316002)(478600001)(4216001);DIR:OUT;SFP:1101;
X-MS-Exchange-AntiSpam-MessageData: 
 naJfLXEDOrca0MZw4kMvlQKI1BL3QW4zaLeZqYFsKGxVIeSHfN1z4/iZI7mWX0QrJUXbwkcgN5ASgmeqRTn0/mx8iDDhfge3SjOahOU6WnwOLQ9iRTehAAiZFXcs7RhzM1b+M3LtSf1dGk+9n008XsS6jDyiMrx+Q1/ZuHruhJZZrNwjasxdr9xai/DxFXLgxhFwArQpdRH2rM6PHT+jvuQjWTJDBnisCPAMFJUAmaUSeUjE8JJQDHi+X1AyLqVMQSbke6fV7GFpfRvjtCXL2w9IUhh482F0EOIdFSFOneByzQAbzTkelUagFrL+2r9ifo2yXbZNINinhM7xja7WjT0hNCLxqEOx/NFuDHOf6QEZtGVIi2rGeXt4gnuPExZ+vKBYEViA20g/FGh8eiGoTmLuiqXjfWHZFcQX2GxQciEHF5EdxfDoTzp3CBquwD+dU4Sprv+4gM8rlmu0/TAp0PuVVIf4RJ/WaJfrs2sfUzQ2odeO1eWIRMAqyvJvNVT0FYjiNlyqLLzkoKmjdLAS5TNGiYK/jpTbkqsjCkJDkgBk6iZijThPQWtGp3C2X3Kc1cY1Jlmd5aeicH6bMpcDTR1JBF9vmGqyb246tvOyC1yD3zM7GgLOLw7mOAcvge8fYoI5PWlk1Nh884dqCLRrssk+Mm3nzK/bG0cugAig82+f2AqDYMDrkgtX2MVarPdx80xGQLh6t8tv5Y69U1Xs5nt8UtrlcaP1GWMi5oDgbPKWMrX7Aqy9tkToevE3ba8linz5exQAeFiVWEMIrj8cHZXuy8UCCEkkH5QpDYA4LnHO4GPYgds80g2coikGWNwUGOd5OS0thvP15OSLOV4YXRI07npXl3v6jutxijU7InVKuFzsy6SxsD8nE/gbnnYhzxTwRoC0lRYZRHY5ExLYMNxGnXvbiqys7Rt1Z/1z5Cpj/NCmU/bW2y/RnkREZ4G5Gfbp7sms7CleEW+YkD4QM1qunnrQOsNwoiSZKMH1bEeVOcfxoUvtqJ2gHiRCuumtZ5ICim8OvsriMIawFyonwO7WSez7Rq8I0sXyyD3wgoT5DEua8UNJBr6dOLl8+Drl0RJUheOU+Iq/s1cLWaYdW+KTAClGld+yE4uZSOpU2IhwSth3CSqPKPseqKJUja9JZot3rEoNUw/DlaYs24zqXkHFkGW+4QK0bWye7qg4wmQYvVU2szgzWCLaJsZZBSHxRt5mpsmocvrw3WTq8QFU89bNRl3+ExKe5FXCPR1ecI4z43uif3wMT1B9LGKmaxv7IxUsRsPSampftS5WFnZiLP+pEylbu3bup0fMFLCEe7+iSR7D4fL74zUHl7eXWYnx
X-OriginatorOrg: Nvidia.com
X-MS-Exchange-CrossTenant-Network-Message-Id: 
 4a5eb1a3-3d85-4eb3-8bd7-08d8f2e4e4b4
X-MS-Exchange-CrossTenant-AuthSource: DM6PR12MB3834.namprd12.prod.outlook.com
X-MS-Exchange-CrossTenant-AuthAs: Internal
X-MS-Exchange-CrossTenant-OriginalArrivalTime: 29 Mar 2021 19:00:17.9726
 (UTC)
X-MS-Exchange-CrossTenant-FromEntityHeader: Hosted
X-MS-Exchange-CrossTenant-Id: 43083d15-7273-40c1-b7db-39efd9ccc17a
X-MS-Exchange-CrossTenant-MailboxType: HOSTED
X-MS-Exchange-CrossTenant-UserPrincipalName: 
 hQWmT7dTA5QD3OD/eZ6GfxiHygQLpdcgyLGhDXi7r8Ewuo+a82iIZfZaATmHJjgJ
X-MS-Exchange-Transport-CrossTenantHeadersStamped: DM6PR12MB2859
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Compiling the nvlink stuff relies on the SPAPR_TCE_IOMMU otherwise there
are compile errors:

 drivers/vfio/pci/vfio_pci_nvlink2.c:101:10: error: implicit declaration of function 'mm_iommu_put' [-Werror,-Wimplicit-function-declaration]
                            ret = mm_iommu_put(data->mm, data->mem);

As PPC only defines these functions when the config is set.

Previously this wasn't a problem by chance as SPAPR_TCE_IOMMU was the only
IOMMU that could have satisfied IOMMU_API on POWERNV.

Fixes: 179209fa1270 ("vfio: IOMMU_API should be selected")
Reported-by: kernel test robot <lkp@intel.com>
Signed-off-by: Jason Gunthorpe <jgg@nvidia.com>
---
 drivers/vfio/pci/Kconfig | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

Example .config builds OK after this.

```
