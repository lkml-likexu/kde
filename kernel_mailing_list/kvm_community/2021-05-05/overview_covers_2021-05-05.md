

#### [PATCH v4 0/8] KVM: Fix tick-based accounting for x86 guests
##### From: Sean Christopherson <seanjc@google.com>

```c
From patchwork Wed May  5 00:27:27 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Sean Christopherson <seanjc@google.com>
X-Patchwork-Id: 12238689
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-21.3 required=3.0 tests=BAYES_00,DKIMWL_WL_MED,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT,
	USER_IN_DEF_DKIM_WL autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 348FAC433B4
	for <kvm@archiver.kernel.org>; Wed,  5 May 2021 00:27:48 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 04046613CB
	for <kvm@archiver.kernel.org>; Wed,  5 May 2021 00:27:47 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S231355AbhEEA2m (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 4 May 2021 20:28:42 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:50334 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S231160AbhEEA2l (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 4 May 2021 20:28:41 -0400
Received: from mail-yb1-xb49.google.com (mail-yb1-xb49.google.com
 [IPv6:2607:f8b0:4864:20::b49])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 10943C06174A
        for <kvm@vger.kernel.org>; Tue,  4 May 2021 17:27:46 -0700 (PDT)
Received: by mail-yb1-xb49.google.com with SMTP id
 a3-20020a2580430000b02904f7a1a09012so484904ybn.3
        for <kvm@vger.kernel.org>; Tue, 04 May 2021 17:27:46 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=reply-to:date:message-id:mime-version:subject:from:to:cc;
        bh=VKgVRByPslcwTvLjOdYrGp82XaC2KrJ5pPY9xex0Ink=;
        b=RZJ5s5vgHmlGIa5GRi9aBd1ACKmDRhWI1rFQ8DWxOR+x8CwUwwgOGzgTAd8Af0z/TD
         QVA/g9wiHqDQ+UkkRiUMGXVzYQbv/cDCfaErKFOga/u+10X9DVW7yG3Pdu22fqrjPflG
         aQKvZF2huCCbeUddmJeikoZAHwS4qi+VgqYZ+vhdBd2EeDbNfd/WPZd1Q6uIEXXneA0B
         l8iO9Z9mweUvuGwF1kdknf07tKK7AvO+7p4gCcfcD9KqNYCKUGDvQjiEi0y3Bzhey4my
         CnbFozb3ZOqAb7ZPND7BRSObRAFTfK8LgUJ5PQxMTmk+5BkrqPVN7iaF52NIDUsBdzJz
         U3hg==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:reply-to:date:message-id:mime-version:subject
         :from:to:cc;
        bh=VKgVRByPslcwTvLjOdYrGp82XaC2KrJ5pPY9xex0Ink=;
        b=pNS1zQRyzmbVzQe3cDVUs4Fl5P14gh++hoh8mA0WekiBIqwxJkBU+iOjHo/9rGcdCl
         w3lcz4A4M7tcEigErK4tCcGSwUocfQr2JJ0tWswLaB7udTf8Oby0bfvdohlepTlEwiRD
         fCAIYG6yM+sLsPmHHbBkjkDYdeHUxsoSTaRXutErAi/GgwQQAoLLTFkWSb60MsPujfwZ
         8eihaf9X8504usN9fswc/8Ztc2C3PdMmPkQUn/jtzkjM8fSXWBkqI9ZTflfdlM6DWZLT
         Y9KqU+qbZFEJupYAXPkdiAuaotCG2zk8QADb+e+JPk0DxWmFeE0rwq4ee68qHu9PCWJR
         bbww==
X-Gm-Message-State: AOAM532bB8Y9tuXjVmXzhggfsRVQfQv3i3i47GvsN185e6wSUExucYNS
        1GryqRVM588zzXaDXFu7G0ORauq4IyI=
X-Google-Smtp-Source: 
 ABdhPJwV3cL8E3VbRB9iH5Ir/bfVm4wFsBBev6rxSscrx4ENE8zNzsNhqOGUZkwj5qcHec+NcEyrbDLhZrk=
X-Received: from seanjc798194.pdx.corp.google.com
 ([2620:15c:f:10:df57:48cb:ea33:a156])
 (user=seanjc job=sendgmr) by 2002:a25:880c:: with SMTP id
 c12mr38649622ybl.399.1620174465152;
 Tue, 04 May 2021 17:27:45 -0700 (PDT)
Reply-To: Sean Christopherson <seanjc@google.com>
Date: Tue,  4 May 2021 17:27:27 -0700
Message-Id: <20210505002735.1684165-1-seanjc@google.com>
Mime-Version: 1.0
X-Mailer: git-send-email 2.31.1.527.g47e6f16901-goog
Subject: [PATCH v4 0/8] KVM: Fix tick-based accounting for x86 guests
From: Sean Christopherson <seanjc@google.com>
To: Paolo Bonzini <pbonzini@redhat.com>
Cc: Sean Christopherson <seanjc@google.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org, Thomas Gleixner <tglx@linutronix.de>,
        Michael Tokarev <mjt@tls.msk.ru>,
        Christian Borntraeger <borntraeger@de.ibm.com>,
        Frederic Weisbecker <frederic@kernel.org>
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Fix tick-based accounting for x86 guests, and do additional cleanups to
further disentangle guest time accounting and to deduplicate code.

v4:
  - Add R-b's (dropped one due to code change). [Christian]
  - Drop instrumentation annotation shuffling since s390 may be gaining
    support. [Christian].
  - Drop "irqs_off" from context_tracking_guest_exit(). [Frederic]
  - Account guest time after enabling IRQs, even when using context
    tracking to precisely account time. [Frederic]

v3 (delta from Wanpeng's v2):
  - https://lkml.kernel.org/r/20210415222106.1643837-1-seanjc@google.com
  - s/context_guest/context_tracking_guest, purely to match the existing
    functions.  I have no strong opinion either way.
  - Split only the "exit" functions.
  - Partially open code vcpu_account_guest_exit() and
    __vtime_account_guest_exit() in x86 to avoid churn when segueing into
    my cleanups (see above).

older:
  - https://lkml.kernel.org/r/1618298169-3831-1-git-send-email-wanpengli@tencent.com
  - https://lkml.kernel.org/r/20210413182933.1046389-1-seanjc@google.com


Sean Christopherson (5):
  sched/vtime: Move vtime accounting external declarations above inlines
  sched/vtime: Move guest enter/exit vtime accounting to vtime.h
  context_tracking: Consolidate guest enter/exit wrappers
  context_tracking: KVM: Move guest enter/exit wrappers to KVM's domain
  KVM: x86: Consolidate guest enter/exit logic to common helpers

Wanpeng Li (3):
  context_tracking: Move guest exit context tracking to separate helpers
  context_tracking: Move guest exit vtime accounting to separate helpers
  KVM: x86: Defer vtime accounting 'til after IRQ handling

 arch/x86/kvm/svm/svm.c           |  39 +--------
 arch/x86/kvm/vmx/vmx.c           |  39 +--------
 arch/x86/kvm/x86.c               |   9 ++
 arch/x86/kvm/x86.h               |  45 ++++++++++
 include/linux/context_tracking.h |  92 ++++-----------------
 include/linux/kvm_host.h         |  45 ++++++++++
 include/linux/vtime.h            | 138 +++++++++++++++++++------------
 7 files changed, 205 insertions(+), 202 deletions(-)
```
#### [PATCH 0/3] TDP MMU: several minor fixes or improvements
##### From: Kai Huang <kai.huang@intel.com>

```c
From patchwork Wed May  5 09:37:56 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Kai Huang <kai.huang@intel.com>
X-Patchwork-Id: 12239509
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-11.8 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,
	SPF_PASS,USER_AGENT_GIT autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 97044C433B4
	for <kvm@archiver.kernel.org>; Wed,  5 May 2021 09:38:19 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 4FF33613EB
	for <kvm@archiver.kernel.org>; Wed,  5 May 2021 09:38:19 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S231993AbhEEJjO (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Wed, 5 May 2021 05:39:14 -0400
Received: from mga12.intel.com ([192.55.52.136]:56202 "EHLO mga12.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S231494AbhEEJjO (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 5 May 2021 05:39:14 -0400
IronPort-SDR: 
 Ee4wyqgNQe3bqH3kLzSR+ElVq6q+637LSLREVrb9LcIwkd92+5Ya0YciWrVf0DTw3bh0vnamhE
 amfcIXJn6Z9Q==
X-IronPort-AV: E=McAfee;i="6200,9189,9974"; a="177724141"
X-IronPort-AV: E=Sophos;i="5.82,274,1613462400";
   d="scan'208";a="177724141"
Received: from orsmga008.jf.intel.com ([10.7.209.65])
  by fmsmga106.fm.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 05 May 2021 02:38:17 -0700
IronPort-SDR: 
 tV5+Re0ZerwtUBbloPtWPSD2k40DfDWmV8IsHVVjTQ9PqSirM4RCnfv0yNftH6z4f110YodKc6
 X3RWo06KdP3A==
X-IronPort-AV: E=Sophos;i="5.82,274,1613462400";
   d="scan'208";a="433728443"
Received: from smorlan-mobl.amr.corp.intel.com (HELO
 khuang2-desk.gar.corp.intel.com) ([10.212.190.185])
  by orsmga008-auth.jf.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 05 May 2021 02:38:14 -0700
From: Kai Huang <kai.huang@intel.com>
To: kvm@vger.kernel.org
Cc: pbonzini@redhat.com, bgardon@google.com, seanjc@google.com,
        vkuznets@redhat.com, wanpengli@tencent.com, jmattson@google.com,
        joro@8bytes.org, Kai Huang <kai.huang@intel.com>
Subject: [PATCH 0/3] TDP MMU: several minor fixes or improvements
Date: Wed,  5 May 2021 21:37:56 +1200
Message-Id: <cover.1620200410.git.kai.huang@intel.com>
X-Mailer: git-send-email 2.31.1
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Pathc 1 and 2 are basically v2 of below patch, after discussion with Ben:

https://lore.kernel.org/kvm/b6d23d9fd8e526e5c7c1a968e2018d13c5433547.camel@intel.com/T/#t

Patch 3 is a new one.

I didn't do lots of tests, especially I didn't do stress test, but only tested
by creating couple of VMs (16 vcpus, 4G memory) and killing them, and everything
seems fine.

Kai Huang (3):
  KVM: x86/mmu: Fix return value in tdp_mmu_map_handle_target_level()
  KVM: x86/mmu: Fix pf_fixed count in tdp_mmu_map_handle_target_level()
  KVM: x86/mmu: Fix TDP MMU page table level

 arch/x86/kvm/mmu/tdp_mmu.c | 12 ++++++------
 1 file changed, 6 insertions(+), 6 deletions(-)
```
#### [PATCH 0/6] sched,delayacct: Some cleanups
##### From: Peter Zijlstra <peterz@infradead.org>

```c
From patchwork Wed May  5 10:59:40 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Peter Zijlstra <peterz@infradead.org>
X-Patchwork-Id: 12239757
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-5.8 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,MAILING_LIST_MULTI,
	SPF_HELO_NONE,SPF_PASS autolearn=no autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 8206AC433ED
	for <kvm@archiver.kernel.org>; Wed,  5 May 2021 11:18:44 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 540F9613C7
	for <kvm@archiver.kernel.org>; Wed,  5 May 2021 11:18:44 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S232915AbhEELTh (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Wed, 5 May 2021 07:19:37 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:51490 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S232854AbhEELTh (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 5 May 2021 07:19:37 -0400
Received: from desiato.infradead.org (desiato.infradead.org
 [IPv6:2001:8b0:10b:1:d65d:64ff:fe57:4e05])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id C2F02C061761;
        Wed,  5 May 2021 04:18:40 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; q=dns/txt; c=relaxed/relaxed;
        d=infradead.org; s=desiato.20200630;
 h=Subject:Cc:To:From:Date:Message-ID:
        Sender:Reply-To:MIME-Version:Content-Type:Content-Transfer-Encoding:
        Content-ID:Content-Description:In-Reply-To:References;
        bh=0MrMsSt2tV5B1WSdY54KIILEtmSIA0/QggdrXISHTE4=;
 b=MZs32ecLkErof+HJRhHK+/aqxT
        ABfhxmvOpw0njH5gPfHjW2lHrGvcc3kv+mUEPPbY2F+HheZNlWu0kRIwiBoW7RwYhGmLLpRMXqRzR
        cPxxG085d3SZd00ECa/kuDGbPSWircI2xECvYqh8NtdO2aQX40TwmNjPE4H++aiIkCjlgPFqn6mPL
        mqG28eb7eJ7oxu/1aJKVZOfr/h7H1ovEZ4JJbkOtud4KAIlYwkRYKf31mRdcsKgtn7a154ZqFZc4F
        9q4ORLsAsLSqDUH8o3IaEGIpXo74LmvZrQsOyBuA41Z8ksDb+mqmCanAtSaTsStcewOYuzt046lLE
        0cYcxxCw==;
Received: from j217100.upc-j.chello.nl ([24.132.217.100]
 helo=noisy.programming.kicks-ass.net)
        by desiato.infradead.org with esmtpsa (Exim 4.94 #2 (Red Hat Linux))
        id 1leFXl-0014WF-Hv; Wed, 05 May 2021 11:18:19 +0000
Received: from hirez.programming.kicks-ass.net
 (hirez.programming.kicks-ass.net [192.168.1.225])
        (using TLSv1.3 with cipher TLS_AES_256_GCM_SHA384 (256/256 bits)
         key-exchange X25519 server-signature RSA-PSS (2048 bits))
        (Client did not present a certificate)
        by noisy.programming.kicks-ass.net (Postfix) with ESMTPS id
 2B2FE300233;
        Wed,  5 May 2021 13:18:14 +0200 (CEST)
Received: by hirez.programming.kicks-ass.net (Postfix, from userid 0)
        id DBCEF299E9863; Wed,  5 May 2021 13:18:14 +0200 (CEST)
Message-ID: <20210505105940.190490250@infradead.org>
User-Agent: quilt/0.66
Date: Wed, 05 May 2021 12:59:40 +0200
From: Peter Zijlstra <peterz@infradead.org>
To: tglx@linutronix.de, mingo@kernel.org, juri.lelli@redhat.com,
        vincent.guittot@linaro.org, dietmar.eggemann@arm.com,
        rostedt@goodmis.org, bsegall@google.com, mgorman@suse.de,
        bristot@redhat.com, bsingharora@gmail.com, pbonzini@redhat.com,
        maz@kernel.org
Cc: linux-kernel@vger.kernel.org, kvm@vger.kernel.org,
        peterz@infradead.org, riel@surriel.com, hannes@cmpxchg.org
Subject: [PATCH 0/6] sched,delayacct: Some cleanups
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Hi,

Due to:

  https://lkml.kernel.org/r/0000000000001d43ac05c0f5c6a0@google.com

and general principle, delayacct really shouldn't be using ktime (pvclock also
really shouldn't be doing what it does, but that's another story). This lead me
to looking at the SCHED_INFO, SCHEDSTATS, DELAYACCT (and PSI) accounting hell.

The rest of the patches are an attempt at simplifying all that a little. All
that crud is enabled by default for distros which is leading to a death by a
thousand cuts.

The last patch is an attempt at default disabling DELAYACCT, because I don't
think anybody actually uses that much, but what do I know, there were no ill
effects on my testbox. Perhaps we should mirror
/proc/sys/kernel/sched_schedstats and provide a delayacct sysctl for runtime
frobbing.
```
#### [PATCH 0/3] KVM: selftests: evmcs_test: Check issues induced by late
##### From: Vitaly Kuznetsov <vkuznets@redhat.com>

```c
From patchwork Wed May  5 15:18:20 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Vitaly Kuznetsov <vkuznets@redhat.com>
X-Patchwork-Id: 12240159
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-11.4 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS autolearn=ham
	autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 4F666C433B4
	for <kvm@archiver.kernel.org>; Wed,  5 May 2021 15:18:31 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 2EB6B60200
	for <kvm@archiver.kernel.org>; Wed,  5 May 2021 15:18:31 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S233451AbhEEPT0 (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Wed, 5 May 2021 11:19:26 -0400
Received: from us-smtp-delivery-124.mimecast.com ([170.10.133.124]:25149 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S231995AbhEEPTZ (ORCPT
        <rfc822;kvm@vger.kernel.org>); Wed, 5 May 2021 11:19:25 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1620227908;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=uQ+znxrQIRFv+05hyI+fCjT9uFUvKbWwa+xMdmXjPWA=;
        b=co3kng0zEO7JhmNf7Snri0PIb1ffW5MM3Lii52C9/192Q3ysRkgRLJwSta13Ia6Tb7p0lC
        V5rDGFNnIMEDW5FKwQybgUlWM9s4TXe1/wqVQLx6h0QVbKGgETVVruxqxyydcu+4eIBB7O
        ZAZplkT3wLDuviKKvTWKXbgz8LXkONI=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-584-1lfl42_XPj25mMG3K0TfdQ-1; Wed, 05 May 2021 11:18:27 -0400
X-MC-Unique: 1lfl42_XPj25mMG3K0TfdQ-1
Received: from smtp.corp.redhat.com (int-mx06.intmail.prod.int.phx2.redhat.com
 [10.5.11.16])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 0D10B824FAB;
        Wed,  5 May 2021 15:18:26 +0000 (UTC)
Received: from vitty.brq.redhat.com (unknown [10.40.194.168])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 43D235C1A3;
        Wed,  5 May 2021 15:18:24 +0000 (UTC)
From: Vitaly Kuznetsov <vkuznets@redhat.com>
To: kvm@vger.kernel.org, Paolo Bonzini <pbonzini@redhat.com>
Cc: Sean Christopherson <seanjc@google.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Maxim Levitsky <mlevitsk@redhat.com>,
        linux-kernel@vger.kernel.org
Subject: [PATCH 0/3] KVM: selftests: evmcs_test: Check issues induced by late
 eVMCS mapping upon restore
Date: Wed,  5 May 2021 17:18:20 +0200
Message-Id: <20210505151823.1341678-1-vkuznets@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.16
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

A regression was introduced by commit f2c7ef3ba955
("KVM: nSVM: cancel KVM_REQ_GET_NESTED_STATE_PAGES on nested vmexit"). When
L2->L1 exit is forced immediately after restoring nested state, 
KVM_REQ_GET_NESTED_STATE_PAGES request is cleared and VMCS12 changes (e.g.
fresh RIP) are not reflected to eVMCS. The consequent nested vCPU run gets
broken. Add a test for the condition (PATCH2). PATCH1 is a preparatory
change, PATCH3 adds a test for a situation when KVM_GET_NESTED_STATE is 
requested right after KVM_SET_NESTED_STATE, this is still broken in KVM
(so the patch is not to be committed).

Vitaly Kuznetsov (3):
  KVM: selftests: evmcs_test: Check that VMLAUNCH with bogus EVMPTR is
    causing #UD
  KVM: selftests: evmcs_test: Check that VMCS12 is alway properly synced
    to eVMCS after restore
  KVM: selftests: evmcs_test: Test that KVM_STATE_NESTED_EVMCS is never
    lost

 .../testing/selftests/kvm/x86_64/evmcs_test.c | 150 +++++++++++++-----
 1 file changed, 108 insertions(+), 42 deletions(-)
```
