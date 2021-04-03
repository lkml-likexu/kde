#### [PATCH v2 01/10] KVM: Assert that notifier count is elevated in .change_pte()
##### From: Sean Christopherson <seanjc@google.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Sean Christopherson <seanjc@google.com>
X-Patchwork-Id: 12180125
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-26.3 required=3.0 tests=BAYES_00,DKIMWL_WL_MED,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_CR_TRAILER,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,
	USER_AGENT_GIT,USER_IN_DEF_DKIM_WL autolearn=unavailable autolearn_force=no
	version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id A6404C43461
	for <kvm@archiver.kernel.org>; Fri,  2 Apr 2021 00:57:09 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 78FE561139
	for <kvm@archiver.kernel.org>; Fri,  2 Apr 2021 00:57:09 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S234015AbhDBA5I (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Thu, 1 Apr 2021 20:57:08 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:40346 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S234023AbhDBA5F (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 1 Apr 2021 20:57:05 -0400
Received: from mail-yb1-xb4a.google.com (mail-yb1-xb4a.google.com
 [IPv6:2607:f8b0:4864:20::b4a])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 0C9BFC061793
        for <kvm@vger.kernel.org>; Thu,  1 Apr 2021 17:57:04 -0700 (PDT)
Received: by mail-yb1-xb4a.google.com with SMTP id v186so7617083ybe.5
        for <kvm@vger.kernel.org>; Thu, 01 Apr 2021 17:57:04 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=reply-to:date:in-reply-to:message-id:mime-version:references
         :subject:from:to:cc;
        bh=DA+Fdq2lOX/CZ+xUDvMaD5HbV7riu4wHkKUqD8IM4/k=;
        b=jEH+4lhN683scpuXyDyNcFSmirhDLEuGk0lJE37N6PVMAVFNUPQDsSlroxmScN5YO3
         IBCGvHhBjtc8BMlUOqXKu1gYXzYw4MZpMUA7myDRgmdzVC/ZR0PTr4HKxjo/4SCJHEih
         Y08yAAvk7+fWeRM2OJoXDnImvQy8YXKdFHJEsuWkAfDOWtaTi+0uKhWpi3Ie7p/zDjMP
         iq644k8yugcuqQZ9i1mkoun+uj7px8E1zhFnLvbBtwUp/G6IJhnB5biBIIFY7KsXYCJg
         jnmfpegvWrj9R8JFD2AZ/HKcezGw+adh+gF5gk/hNaz+UDc8nBr71LdSLSS+hgpp5xK2
         yJkg==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:reply-to:date:in-reply-to:message-id
         :mime-version:references:subject:from:to:cc;
        bh=DA+Fdq2lOX/CZ+xUDvMaD5HbV7riu4wHkKUqD8IM4/k=;
        b=ZOt6Dw6dEsJwcYInP1PVdZNli4U1F5Qnrmj6BQP3E2vY0DswPihWdufKlPyvuT1Ez4
         3fwJ6pGrDBv7Rzm357N/ZMDeFKBbgFVGzD5eLZc8Jys2yWM7b/5qKaFW/jz+zHpI2KA6
         zHrqrAeDAzakKAa6u4YRV7Ve+dIptDbRYPzlWRUGzCReLcb/mGJUqHwcPlEAFbXUGY0u
         gwxmwQOitvp4xp1wtksx4cLE5z3wK257UAGBcEicwudMPgPcEVn99ap8Ey6Sor8eSz73
         oRRBEvI+/m4LbUDUR9Cm69+85cujlT15ul4rqcE+n9P/l5z0ytC4hoCBz+V3zN7r89uF
         Rssw==
X-Gm-Message-State: AOAM531Q/hc9vphXwOgTWeaUcJHkvSqRW6SteAtCXYmwLEDhW+336UC5
        eNsfsNXmUGw0IcWUvon1Iq0FiorJwQo=
X-Google-Smtp-Source: 
 ABdhPJygeKAdy1Ue7ggQyWInnKM/181me24PPoeX8s/XsaZF77/exnxBmdxBDDEECxkfyMlEpqfXzJSZ32w=
X-Received: from seanjc798194.pdx.corp.google.com
 ([2620:15c:f:10:c0b4:8b8:bb34:6a56])
 (user=seanjc job=sendgmr) by 2002:a25:af05:: with SMTP id
 a5mr16043377ybh.86.1617325023277;
 Thu, 01 Apr 2021 17:57:03 -0700 (PDT)
Reply-To: Sean Christopherson <seanjc@google.com>
Date: Thu,  1 Apr 2021 17:56:49 -0700
In-Reply-To: <20210402005658.3024832-1-seanjc@google.com>
Message-Id: <20210402005658.3024832-2-seanjc@google.com>
Mime-Version: 1.0
References: <20210402005658.3024832-1-seanjc@google.com>
X-Mailer: git-send-email 2.31.0.208.g409f899ff0-goog
Subject: [PATCH v2 01/10] KVM: Assert that notifier count is elevated in
 .change_pte()
From: Sean Christopherson <seanjc@google.com>
To: Marc Zyngier <maz@kernel.org>, Huacai Chen <chenhuacai@kernel.org>,
        Aleksandar Markovic <aleksandar.qemu.devel@gmail.com>,
        Paul Mackerras <paulus@ozlabs.org>,
        Paolo Bonzini <pbonzini@redhat.com>
Cc: James Morse <james.morse@arm.com>,
        Julien Thierry <julien.thierry.kdev@gmail.com>,
        Suzuki K Poulose <suzuki.poulose@arm.com>,
        Sean Christopherson <seanjc@google.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>,
        linux-arm-kernel@lists.infradead.org, kvmarm@lists.cs.columbia.edu,
        linux-mips@vger.kernel.org, kvm@vger.kernel.org,
        kvm-ppc@vger.kernel.org, linux-kernel@vger.kernel.org,
        Ben Gardon <bgardon@google.com>
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

In KVM's .change_pte() notification callback, replace the notifier
sequence bump with a WARN_ON assertion that the notifier count is
elevated.  An elevated count provides stricter protections than bumping
the sequence, and the sequence is guarnateed to be bumped before the
count hits zero.

When .change_pte() was added by commit 828502d30073 ("ksm: add
mmu_notifier set_pte_at_notify()"), bumping the sequence was necessary
as .change_pte() would be invoked without any surrounding notifications.

However, since commit 6bdb913f0a70 ("mm: wrap calls to set_pte_at_notify
with invalidate_range_start and invalidate_range_end"), all calls to
.change_pte() are guaranteed to be bookended by start() and end(), and
so are guaranteed to run with an elevated notifier count.

Note, wrapping .change_pte() with .invalidate_range_{start,end}() is a
bug of sorts, as invalidating the secondary MMU's (KVM's) PTE defeats
the purpose of .change_pte().  Every arch's kvm_set_spte_hva() assumes
.change_pte() is called when the relevant SPTE is present in KVM's MMU,
as the original goal was to accelerate Kernel Samepage Merging (KSM) by
updating KVM's SPTEs without requiring a VM-Exit (due to invalidating
the SPTE).  I.e. it means that .change_pte() is effectively dead code
on _all_ architectures.

x86 and MIPS are clearcut nops if the old SPTE is not-present, and that
is guaranteed due to the prior invalidation.  PPC simply unmaps the SPTE,
which again should be a nop due to the invalidation.  arm64 is a bit
murky, but it's also likely a nop because kvm_pgtable_stage2_map() is
called without a cache pointer, which means it will map an entry if and
only if an existing PTE was found.

For now, take advantage of the bug to simplify future consolidation of
KVMs's MMU notifier code.   Doing so will not greatly complicate fixing
.change_pte(), assuming it's even worth fixing.  .change_pte() has been
broken for 8+ years and no one has complained.  Even if there are
KSM+KVM users that care deeply about its performance, the benefits of
avoiding VM-Exits via .change_pte() need to be reevaluated to justify
the added complexity and testing burden.  Ripping out .change_pte()
entirely would be a lot easier.

Signed-off-by: Sean Christopherson <seanjc@google.com>
---
 virt/kvm/kvm_main.c | 9 +++++++--
 1 file changed, 7 insertions(+), 2 deletions(-)

```
#### [PATCH 1/4] KVM: constify kvm_arch_flush_remote_tlbs_memslot
##### From: Paolo Bonzini <pbonzini@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Paolo Bonzini <pbonzini@redhat.com>
X-Patchwork-Id: 12181277
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.8 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT
	autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 6FFA4C43462
	for <kvm@archiver.kernel.org>; Fri,  2 Apr 2021 15:58:15 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 4E46761152
	for <kvm@archiver.kernel.org>; Fri,  2 Apr 2021 15:58:15 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S236316AbhDBP6P (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Fri, 2 Apr 2021 11:58:15 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:37132 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S235720AbhDBP6N (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 2 Apr 2021 11:58:13 -0400
Received: from mail-wm1-x32f.google.com (mail-wm1-x32f.google.com
 [IPv6:2a00:1450:4864:20::32f])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 9CFF1C0613E6;
        Fri,  2 Apr 2021 08:58:11 -0700 (PDT)
Received: by mail-wm1-x32f.google.com with SMTP id
 j20-20020a05600c1914b029010f31e15a7fso4517567wmq.1;
        Fri, 02 Apr 2021 08:58:11 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=sender:from:to:cc:subject:date:message-id:in-reply-to:references
         :mime-version:content-transfer-encoding;
        bh=Kre3cIsJUUiu6GfRt+z3UNvRKui0T9xc/PeVTTZr7ig=;
        b=ryhHc1JzRHdWPicwK8viSU3MOD5f0eQmm47r5hbvS+5+INAyYGM5jeUruCl/zWWXFv
         jIdoxhhJ1sZ/ijWxfQcTzuqTpapouUmlJlZtolrY1OqwmAMqf6agR6e+/YWyQlXeVCt6
         v3OtZXnYow7y0Mr9w4qsK0iTK8lSGIBMz7ZT9fW4mwxeIMwYcPTPmXRHDN3Kf/ST5XdK
         KWFpklbVNdKGx2q9Kd03pk/Z6mgiGmGexIvgr3VXf0lWDAaAgD+jFoLyCK7FygZxV3/s
         6HD/8pzAlRWBIpC8N/fIE2Vwgq5ZgXofjpB5HV385leTv90TPkPnPXyzIX50PomWFitr
         vOKg==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:sender:from:to:cc:subject:date:message-id
         :in-reply-to:references:mime-version:content-transfer-encoding;
        bh=Kre3cIsJUUiu6GfRt+z3UNvRKui0T9xc/PeVTTZr7ig=;
        b=WnywaZBVkOToXt1Fq2qPbHRyE/3sOeHnV1EQhs6hf6HkdiixIzHdmgb0lL3f81WLY8
         mik+G1lfUjeeo+2lGe0stDHTAeYq0hfo9r0X3Va+z1NRN5gcwUtdNqfFZ8g9uxi9d5Cr
         1yaY5kiFJtT8SaK0u1yuSiUg+jlXVpP1UwEEGU/6bkhlXz4MGEEPFdsNwiqzcvBE8HO6
         tPODEjvBvL/IpYcOXkxLdazwKhN7eGRfvdR9nRcwFY7g0qyNTmykHk1AXaZdYc8mQWCx
         4Uc9dul53K4nwbiidrBb1RxeW3JmbeHhv7ZAEuPgOYnHnABpJYd4Mhrj/HZUuneJAfYf
         fydA==
X-Gm-Message-State: AOAM531izZb5vrf/+5aSUmDbM5BA39tbCdTlyPaU9l4J9Ko/EELku9V0
        ulaAr64CXmflWW/k+f7jC45MSrKeMG0=
X-Google-Smtp-Source: 
 ABdhPJxkN/qm1HIJiGhdrsPZwOPx99MtS0WKuuR1c+cS3d4UmftRHekbQfkqHrzcI3HfVcNz5ZQ3bA==
X-Received: by 2002:a05:600c:1457:: with SMTP id
 h23mr2284614wmi.118.1617379090365;
        Fri, 02 Apr 2021 08:58:10 -0700 (PDT)
Received: from avogadro.lan ([2001:b07:6468:f312:c8dd:75d4:99ab:290a])
        by smtp.gmail.com with ESMTPSA id
 w11sm2293625wmb.35.2021.04.02.08.58.09
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Fri, 02 Apr 2021 08:58:10 -0700 (PDT)
Sender: Paolo Bonzini <paolo.bonzini@gmail.com>
From: Paolo Bonzini <pbonzini@redhat.com>
To: linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Cc: chenhuacai@kernel.org, aleksandar.qemu.devel@gmail.com,
        seanjc@google.com, linux-mips@vger.kernel.org
Subject: [PATCH 1/4] KVM: constify kvm_arch_flush_remote_tlbs_memslot
Date: Fri,  2 Apr 2021 17:58:04 +0200
Message-Id: <20210402155807.49976-2-pbonzini@redhat.com>
X-Mailer: git-send-email 2.30.1
In-Reply-To: <20210402155807.49976-1-pbonzini@redhat.com>
References: <20210402155807.49976-1-pbonzini@redhat.com>
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

memslots are stored in RCU and there should be no need to
change them.

Signed-off-by: Paolo Bonzini <pbonzini@redhat.com>
---
 arch/arm64/kvm/arm.c     | 2 +-
 arch/mips/kvm/mips.c     | 2 +-
 arch/x86/kvm/mmu/mmu.c   | 2 +-
 include/linux/kvm_host.h | 2 +-
 4 files changed, 4 insertions(+), 4 deletions(-)

```
#### [PATCH] KVM: MMU: protect TDP MMU pages only down to required level
##### From: Paolo Bonzini <pbonzini@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Paolo Bonzini <pbonzini@redhat.com>
X-Patchwork-Id: 12180805
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-15.8 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_CR_TRAILER,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS
	autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id F3F9BC433B4
	for <kvm@archiver.kernel.org>; Fri,  2 Apr 2021 12:17:10 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id BC93661106
	for <kvm@archiver.kernel.org>; Fri,  2 Apr 2021 12:17:10 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S235348AbhDBMRK (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Fri, 2 Apr 2021 08:17:10 -0400
Received: from us-smtp-delivery-124.mimecast.com ([63.128.21.124]:38202 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S229932AbhDBMRJ (ORCPT
        <rfc822;kvm@vger.kernel.org>); Fri, 2 Apr 2021 08:17:09 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1617365827;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=0jaEPxLaJfReD8pxSOXnANRrSayp5U1dcLmAQj7CP5E=;
        b=b65z4Meu9/5m1HOQO/UQiMMM7gPtxy3UWh7exg5CfXIuAesEM3NVB7DNEBuNxIb168z2RW
        Yec+slbZqeL0276a0rcPT0d0A+AegmLEpdiLHZG4CpLs0IcECG5RVGnQaselS5CLWbpdFe
        Io4ruO+zfcoNU1MWszirwqDdtt+pOo4=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-436-JItoow2QM461wIMIdOIiXQ-1; Fri, 02 Apr 2021 08:17:06 -0400
X-MC-Unique: JItoow2QM461wIMIdOIiXQ-1
Received: from smtp.corp.redhat.com (int-mx02.intmail.prod.int.phx2.redhat.com
 [10.5.11.12])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 70CAA1005D57;
        Fri,  2 Apr 2021 12:17:05 +0000 (UTC)
Received: from virtlab701.virt.lab.eng.bos.redhat.com
 (virtlab701.virt.lab.eng.bos.redhat.com [10.19.152.228])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 13D3F60BF1;
        Fri,  2 Apr 2021 12:17:05 +0000 (UTC)
From: Paolo Bonzini <pbonzini@redhat.com>
To: linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Cc: Ben Gardon <bgardon@google.com>
Subject: [PATCH] KVM: MMU: protect TDP MMU pages only down to required level
Date: Fri,  2 Apr 2021 08:17:04 -0400
Message-Id: <20210402121704.3424115-1-pbonzini@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.12
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

When using manual protection of dirty pages, it is not necessary
to protect nested page tables down to the 4K level; instead KVM
can protect only hugepages in order to split them lazily, and
delay write protection at 4K-granularity until KVM_CLEAR_DIRTY_LOG.
This was overlooked in the TDP MMU, so do it there as well.

Fixes: a6a0b05da9f37 ("kvm: x86/mmu: Support dirty logging for the TDP MMU")
Cc: Ben Gardon <bgardon@google.com>
Signed-off-by: Paolo Bonzini <pbonzini@redhat.com>
---
 arch/x86/kvm/mmu/mmu.c | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
#### [PATCH 1/5 v6] KVM: SVM: Define actual size of IOPM and MSRPM tables
##### From: Krish Sadhukhan <krish.sadhukhan@oracle.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Krish Sadhukhan <krish.sadhukhan@oracle.com>
X-Patchwork-Id: 12180181
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-18.8 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,
	INCLUDES_PATCH,MAILING_LIST_MULTI,MSGID_FROM_MTA_HEADER,SPF_HELO_NONE,
	SPF_PASS,USER_AGENT_GIT autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 29A6FC43462
	for <kvm@archiver.kernel.org>; Fri,  2 Apr 2021 01:33:06 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id EF2A461001
	for <kvm@archiver.kernel.org>; Fri,  2 Apr 2021 01:33:05 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S234153AbhDBBdD (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Thu, 1 Apr 2021 21:33:03 -0400
Received: from aserp2130.oracle.com ([141.146.126.79]:49780 "EHLO
        aserp2130.oracle.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S233677AbhDBBdA (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 1 Apr 2021 21:33:00 -0400
Received: from pps.filterd (aserp2130.oracle.com [127.0.0.1])
        by aserp2130.oracle.com (8.16.0.42/8.16.0.42) with SMTP id
 1321Wr5m063887;
        Fri, 2 Apr 2021 01:32:53 GMT
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=oracle.com;
 h=from : to : cc :
 subject : date : message-id : in-reply-to : references :
 content-transfer-encoding : content-type : mime-version;
 s=corp-2020-01-29; bh=OyfSkumGwoB6TlE1OOlaXy++iJqR4mB9HcHh/k8EHrE=;
 b=jNo5RH2ixc/1r/s8FKOu+QXCV96GW54FoZtBvowSP3s04vlu7idcXbuuHabJ9dt8+sCI
 7X9GAusT7Ees2hUWk0HtIduMoNP84ujFTwxJlInYcp6eQB6IetR5ZbS7iNYT8gwc7Kbm
 n80Y1zUNmeMRf0brFqwIgk3S6ArvIsajUJk6qQfyFbktiYVjJAu95H/m+JQxYZfOpWGJ
 0lPrC3WT6TSEjjfoVhPx/1SUYUSmq+xQN3+uuHU1Sc0juJmUFsy3ttP70ZCQL2WkoUwz
 vvZsF7J8DlqLr+/ykzo8yIJB8PXBFWbLc7bbqDiRoyUv/pZun23IHH82bFGI3aC0mYmp Ew==
Received: from aserp3020.oracle.com (aserp3020.oracle.com [141.146.126.70])
        by aserp2130.oracle.com with ESMTP id 37n33dugm2-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Fri, 02 Apr 2021 01:32:53 +0000
Received: from pps.filterd (aserp3020.oracle.com [127.0.0.1])
        by aserp3020.oracle.com (8.16.0.42/8.16.0.42) with SMTP id
 1321Uw7M018855;
        Fri, 2 Apr 2021 01:32:53 GMT
Received: from nam10-mw2-obe.outbound.protection.outlook.com
 (mail-mw2nam10lp2101.outbound.protection.outlook.com [104.47.55.101])
        by aserp3020.oracle.com with ESMTP id 37n2abyytf-2
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Fri, 02 Apr 2021 01:32:53 +0000
ARC-Seal: i=1; a=rsa-sha256; s=arcselector9901; d=microsoft.com; cv=none;
 b=PtVB0ILd9sc70XNDsTSuB5AWi30SB2QHc9JCI0is0v9/ArZtLO5v6dyGJbJ19VWnUZH86Vg81U3rW0brur976KdD4naHWFb3Puuf7VKujfgyTyzlUFWKsq8uk7hWRYY8NkawUWsmkgDXKfkHNkgjDBqZpViBoI/YTtKajQ41WG40VNkvO6a45oOf6BEdBjyzrza9jlRcXtNFneExyxqjiEAQKLXplvVWopkZvyaRPaBTfo1OfFDrQuHwTywhBrkbMxgWQMGoXEGSlaQlVk5SJ9qdzKf2myUmNZbpLFDPHfTPQKdTN+sUjF3xuTI0VusgJ5hDp5jfnH3v8VRhgwIudQ==
ARC-Message-Signature: i=1; a=rsa-sha256; c=relaxed/relaxed; d=microsoft.com;
 s=arcselector9901;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=OyfSkumGwoB6TlE1OOlaXy++iJqR4mB9HcHh/k8EHrE=;
 b=TAII1ryUxAd7qHOXiaV9mai9mVvBJncSiDWE1WgGBrpuZaSZ+qqFLeqOkb4cuAamZphG6o/3G1uBUstwWqjrHziXvNaAoZftSZ+uR46G1ASAabreswkLPGRcdDrGZS544iZFGg2vBKUlD6iY57zMAmc/oiCzYmNx0R7YZ0jFNxcwWX9zxnmAGLAfVXn7G+ngkkQKsnxc3pWbVorhG0D9wedMVodCYlwAjh1JLA/F7MyUab95olncWpRjgndB9TdsrRhroNx0RBbRm3myF4dr26eCrkjkCs3ut09FyYi0irViOty6k9mU+5zC674Hko4TkI9pOdcCmtqT3HCc33XREg==
ARC-Authentication-Results: i=1; mx.microsoft.com 1; spf=pass
 smtp.mailfrom=oracle.com; dmarc=pass action=none header.from=oracle.com;
 dkim=pass header.d=oracle.com; arc=none
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
 d=oracle.onmicrosoft.com; s=selector2-oracle-onmicrosoft-com;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=OyfSkumGwoB6TlE1OOlaXy++iJqR4mB9HcHh/k8EHrE=;
 b=vftsXn7U226XuwWUhlt4tcBQajz+UPm2+IgkEuJqzCjKXp/jTINCzslSwQhmOQ2Ns/PiWdz73fSTRJVdmTLA16UqsOwkrw+YhybLEyj39sTRED5KoLv6ykeJcjDCi8y68kwe1LQPbcZnE6Lo/U+tMk0XKEAkTCXxnPmicnYoisY=
Authentication-Results: vger.kernel.org; dkim=none (message not signed)
 header.d=none;vger.kernel.org; dmarc=none action=none header.from=oracle.com;
Received: from SN6PR10MB3021.namprd10.prod.outlook.com (2603:10b6:805:cc::19)
 by SA2PR10MB4795.namprd10.prod.outlook.com (2603:10b6:806:11d::14) with
 Microsoft SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.3999.28; Fri, 2 Apr
 2021 01:32:52 +0000
Received: from SN6PR10MB3021.namprd10.prod.outlook.com
 ([fe80::5911:9489:e05c:2d44]) by SN6PR10MB3021.namprd10.prod.outlook.com
 ([fe80::5911:9489:e05c:2d44%5]) with mapi id 15.20.3999.029; Fri, 2 Apr 2021
 01:32:52 +0000
From: Krish Sadhukhan <krish.sadhukhan@oracle.com>
To: kvm@vger.kernel.org
Cc: pbonzini@redhat.com, jmattson@google.com, seanjc@google.com
Subject: [PATCH 1/5 v6] KVM: SVM: Define actual size of IOPM and MSRPM tables
Date: Thu,  1 Apr 2021 20:43:27 -0400
Message-Id: <20210402004331.91658-2-krish.sadhukhan@oracle.com>
X-Mailer: git-send-email 2.25.4
In-Reply-To: <20210402004331.91658-1-krish.sadhukhan@oracle.com>
References: <20210402004331.91658-1-krish.sadhukhan@oracle.com>
X-Originating-IP: [138.3.201.29]
X-ClientProxiedBy: SJ0PR13CA0024.namprd13.prod.outlook.com
 (2603:10b6:a03:2c0::29) To SN6PR10MB3021.namprd10.prod.outlook.com
 (2603:10b6:805:cc::19)
MIME-Version: 1.0
X-MS-Exchange-MessageSentRepresentingType: 1
Received: from ban25x6uut29.us.oracle.com (138.3.201.29) by
 SJ0PR13CA0024.namprd13.prod.outlook.com (2603:10b6:a03:2c0::29) with
 Microsoft SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.4020.9 via Frontend
 Transport; Fri, 2 Apr 2021 01:32:50 +0000
X-MS-PublicTrafficType: Email
X-MS-Office365-Filtering-Correlation-Id: 36ed3ced-e2d7-41cf-4024-08d8f5773b3c
X-MS-TrafficTypeDiagnostic: SA2PR10MB4795:
X-Microsoft-Antispam-PRVS: 
 <SA2PR10MB4795EBA4073203C944324236817A9@SA2PR10MB4795.namprd10.prod.outlook.com>
X-MS-Oob-TLC-OOBClassifiers: OLM:6790;
X-MS-Exchange-SenderADCheck: 1
X-Microsoft-Antispam: BCL:0;
X-Microsoft-Antispam-Message-Info: 
 JuZLTw5P4O5/6qp/DVwwx664vdRnsZbkL/L7m8PSpAzL5zRd9DGvBALL7Rxl3S275xDvfqgsIB4bYJIxEzMU1qJvaf/qrTnmbMnJCzmZApopeXga6FEwSVfHe3gVuJypcKsmXDUYBXb2m4dE/+cofCC++GwEoyg9S8TBb3M1gvNwo2t+DrlRv0pPOitsmnSm7uX7yYoK6fH3+HqYwgZYbd6WjvR1d9LJv1AoeIhNw9UKsaaRXg6mLcBGqZ3vZHDfw56EtX39WopKf02iAKGrepf+9JZYBCEXJ/VwsF18lIGRhXJ3d5+Vyv3WY4Ttxa1D2VcH74a+NEvcKa53nCZ16CIuIR3oNN2UHyCxgVRpKgW8LcHedI85GpqiPB8owL/9Gu2mE1AweLoRXfF4zqX6MVPdA1oV5WgkirJe573TaVhVuuf8/uPoKpx1apz8ZFdpMu1CNzSDNXpJnVkWGqnzUx1ZeTpGnq3DQQEnDm4TYXlJkxrogvonVcqQqfDrtGlKHFbCabMlD77NE4XBXixvAnq5OGS7Qgz/CJoTeEgbiVDtqNqNz4qPuH3nlU4R/xGZlmwSFXBojw8nb9ibrgw70syJMW8BpUYMX9zyfPbDlvQZ3zNYvydJVeK6bfhoQpDqJYm01uFwmp4a9nQWfADN0L/CIg/X8d2Eg+SWoVeay54=
X-Forefront-Antispam-Report: 
 CIP:255.255.255.255;CTRY:;LANG:en;SCL:1;SRV:;IPV:NLI;SFV:NSPM;H:SN6PR10MB3021.namprd10.prod.outlook.com;PTR:;CAT:NONE;SFS:(376002)(366004)(346002)(396003)(39860400002)(136003)(6666004)(26005)(36756003)(316002)(83380400001)(1076003)(66556008)(5660300002)(16526019)(66476007)(186003)(7696005)(6486002)(2616005)(44832011)(52116002)(956004)(8936002)(38100700001)(8676002)(6916009)(2906002)(66946007)(86362001)(4326008)(478600001);DIR:OUT;SFP:1101;
X-MS-Exchange-AntiSpam-MessageData: 
 EVoIeqw780YxPZHTHElBFwW3Ppf4doLoFXQPuQ9Pd/N9Nsjtoq34t9asadjkK7F4gY2c5R1STvd+lhYVMCVz4CP3p7pAIped+PXFrr79bDJls1D1jN/Tg/4nETPyG5W+wRoOuP0Fgfej2ZUijpUQ3yls6BEbEZx8ySKb2qXSOUCrlcgpWSR3QPEwnA5paFkq69iibo12/lqIh5XvyNf6NYv4BDbpcb/uitvdRsjhwkENco+vN3ujxf2AcUvrQkxz6sDfOc53BmUe+fNqH11G9DqU6ff+WbI08Isawjcnu78o66CTCwAHpxAJf+MdlPbWW7Hi++WZOLucUxojnx50QCMyOXf2u92Ynaf7V9/F5o6ynb6/huawiL4sWg7e4iaAdw2wBvCiftySvrhmsQxZGecCIhCb0PpZMfrrn6hGJejFrfn34dnwdbK/smFNlGspSww7inh5VZ9TYNO8FAfdSiRlJDdMVWcpsTTlP9EHpLVkIopXnVDHmpnzoIoRSc9Rq6BKFVM6pgNB8mwpFnQxtLJmxJyHWVd0Vg7J0Y6NH8gP7DhcMMTpdYu80pNt/yeNYA/ZynKpfm1Qlb4sPCv6F1tRWattUukUbc2x0TczO7AaQT9sE5+kNrLwxLWZaIbSCbK/9l6AnHXg9dJmgHnpOUz3XNE2V3S1Zg9q6sU19zLTUIYpkMGGTNFCiRSPFuyr2sCNMUyse3NRPOaoqTVhcJX8oPysStz90TWesfUt0hR82He1C8JPLSmPYAMr+mmcOJMmALMpPyziHRucBOFznc+HKJJhNXAGB7bpOqUp5S/hKizvCTHNBqhprD5IaT/QO8+DMsn+phNJuKQPYJ/oPZG8gJZnUL5D7nEqoR2B71736dNURzhKAsZxG/1GSBGHnDixb06+8HCVmKWiOK4C1yEYngqh8YU8CtPPCPyyq6a5y+5palhn0H1LRs6PdCy8eGXlWJLWXhASzWNgbApW38z+KEKnlyQPnEk11onYKE4b1bYhuHBZOK96Gno62/AmzSJVvGb4Dl6py8FFyuU0W29h2Bo9D8HRe9td223Fo1heGPFIlIMugeURoLO5MqCC8hdKJXxherPXgA/EXs/a9Dw819ZblIfdipRuZ3217VRnWMQfgzepOSP1/2OjSdsmhkDkVfymewzslHgiD/1LmYMDSpc/CKkxWWv1Xz7smEn4fveTU/zA1KGvso6FGivbXadXgqi21X6w48dMPbWUUvEKNB+HxXfB9LWD2UtU2vMIxw9X0AMmX0QKem6kTy9cgWsT2eMyXXtqpGL+JJUQ8bjgBRJ4VMJotvPSoyAbEF/OOZ3CeLTiziKruTlm3c1V
X-OriginatorOrg: oracle.com
X-MS-Exchange-CrossTenant-Network-Message-Id: 
 36ed3ced-e2d7-41cf-4024-08d8f5773b3c
X-MS-Exchange-CrossTenant-AuthSource: SN6PR10MB3021.namprd10.prod.outlook.com
X-MS-Exchange-CrossTenant-AuthAs: Internal
X-MS-Exchange-CrossTenant-OriginalArrivalTime: 02 Apr 2021 01:32:51.9021
 (UTC)
X-MS-Exchange-CrossTenant-FromEntityHeader: Hosted
X-MS-Exchange-CrossTenant-Id: 4e2c6054-71cb-48f1-bd6c-3a9705aca71b
X-MS-Exchange-CrossTenant-MailboxType: HOSTED
X-MS-Exchange-CrossTenant-UserPrincipalName: 
 dZctJulZQT23TyRuYG3/xOxYJRf7aLKy7tlle0n+5pRzK/PAbszxOGDwPhTg2Nyl98IGATWKjnOxPiGNYpbzbI6mvjWpPzTxkz0WRRHH0Sg=
X-MS-Exchange-Transport-CrossTenantHeadersStamped: SA2PR10MB4795
X-Proofpoint-Virus-Version: vendor=nai engine=6200 definitions=9941
 signatures=668683
X-Proofpoint-Spam-Details: rule=notspam policy=default score=0 adultscore=0
 mlxscore=0 bulkscore=0
 suspectscore=0 phishscore=0 malwarescore=0 mlxlogscore=999 spamscore=0
 classifier=spam adjust=0 reason=mlx scancount=1 engine=8.12.0-2103310000
 definitions=main-2104020008
X-Proofpoint-GUID: 7V4m2zuqMf4Z2s3fZfv1AhJ3CokvQ8PL
X-Proofpoint-ORIG-GUID: 7V4m2zuqMf4Z2s3fZfv1AhJ3CokvQ8PL
X-Proofpoint-Virus-Version: vendor=nai engine=6200 definitions=9941
 signatures=668683
X-Proofpoint-Spam-Details: rule=notspam policy=default score=0 spamscore=0
 mlxlogscore=999 mlxscore=0
 lowpriorityscore=0 suspectscore=0 priorityscore=1501 phishscore=0
 clxscore=1015 impostorscore=0 malwarescore=0 bulkscore=0 adultscore=0
 classifier=spam adjust=0 reason=mlx scancount=1 engine=8.12.0-2103310000
 definitions=main-2104020008
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Define the actual size of the IOPM and MSRPM tables so that the actual size
can be used when initializing them and when checking the consistency of the
physical addresses. These #defines are placed in svm.h so that they can be
shared.

Suggested-by: Sean Christopherson <seanjc@google.com>
Signed-off-by: Krish Sadhukhan <krish.sadhukhan@oracle.com>
---
 arch/x86/kvm/svm/svm.c | 20 ++++++++++----------
 arch/x86/kvm/svm/svm.h |  3 +++
 2 files changed, 13 insertions(+), 10 deletions(-)

```
#### [PATCH 1/4] KVM: stats: Separate common stats from architecture specific ones
##### From: Jing Zhang <jingzhangos@google.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Jing Zhang <jingzhangos@google.com>
X-Patchwork-Id: 12181733
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-26.2 required=3.0 tests=BAYES_00,DKIMWL_WL_MED,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_CR_TRAILER,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,
	USER_AGENT_GIT,USER_IN_DEF_DKIM_WL autolearn=unavailable autolearn_force=no
	version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 84501C4360C
	for <kvm@archiver.kernel.org>; Fri,  2 Apr 2021 22:44:22 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 5B27061178
	for <kvm@archiver.kernel.org>; Fri,  2 Apr 2021 22:44:22 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S235788AbhDBWoW (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Fri, 2 Apr 2021 18:44:22 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:40428 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S235341AbhDBWoS (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 2 Apr 2021 18:44:18 -0400
Received: from mail-io1-xd4a.google.com (mail-io1-xd4a.google.com
 [IPv6:2607:f8b0:4864:20::d4a])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id BC80FC061797
        for <kvm@vger.kernel.org>; Fri,  2 Apr 2021 15:44:15 -0700 (PDT)
Received: by mail-io1-xd4a.google.com with SMTP id d12so6968608ioo.10
        for <kvm@vger.kernel.org>; Fri, 02 Apr 2021 15:44:15 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=date:in-reply-to:message-id:mime-version:references:subject:from:to
         :cc;
        bh=ojdKD4RuDtNbO2hpUpqkeTknwy0eCBzDpVd8A1N+KSY=;
        b=SwT+KebX2GA1CW+kLgaFzCDOZDciMhc44rwGUWq6uSadDcGS1Z7URToz4FJ7JWmmkx
         Enb3D1+Z19jSkT5OV/m7pRPnLL/yzmwJn8vVI5iUpghbQkdXntH30+HV4OoprNpqc2X4
         oaDsY6V+2UEiYnj0h1ltNhfkJ086OaR+TX4uceR4fyG8HPxpvrcZvhcpvQjs6yFZLADx
         if+9chUgyZug9XnTgm/Xt3zXsEvNbOAeUekgqKc4wbBsde2U171NWoKu+TyC3oQOQIE1
         Kz94BvU43ZU/E9xzFIsrzyBKat2a5Gqe7PeIEHem7KsxGX3egTgaIZBUXHYh05hQnKNc
         xkKg==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:date:in-reply-to:message-id:mime-version
         :references:subject:from:to:cc;
        bh=ojdKD4RuDtNbO2hpUpqkeTknwy0eCBzDpVd8A1N+KSY=;
        b=lwxI3PG47MbBz3Wun1SaoMYWjOOBPR3I2jo4vaI7JWG45WGrH7stnIImaSk3Hm00VA
         gjMn0oj5cV3tKLXUghlWvoxR7PkDZBKWLLRDhfUCkCL49F1szauLFcVq18rwITk0ETXf
         CPjC8CLqSMTxWHFItqLJ538IJj3Nhh7CukCHGESTeIk0Wie+Rq6wZX9aFQ/kirlvFo5v
         MTsUeWdUU1/NUaR4rBpmzv0Vcf3zT9M2SG5k/j+0haDY0pIHDvIk0+2YvWHedlphpWeX
         eFqvOXJqqSECaqT5+h0Qm/5iynGHDw333LIw6PHdynzeIwXj7bninm6mE/YQQT0fayoD
         YSng==
X-Gm-Message-State: AOAM532h27bSlWDwds++92S069ge/RsWVHSORmC2oEXC9pjDbuaB4pCf
        HXTaBDuDv/3D88viHDy8kRw+obAotdW7caY48G5fU9KshKLwvni1nEZAgAJ4RzwghobSHgI6JYa
        Dtwko9FqCvWqYmgJpkbIAFx2lyoqTGwlANuJLvicEqyb75zEJIn2Z6u6Qc+CFuNQjnycERKI=
X-Google-Smtp-Source: 
 ABdhPJzXmYpuF+ilX18hSK5e1VkCV/xuPmBpFif/W0prDmGXjPLd27ipoMoneBsrqlIicZhLwKQkkkzJuKr2LMYwbg==
X-Received: from jingzhangos.c.googlers.com
 ([fda3:e722:ac3:10:2b:ff92:c0a8:513])
 (user=jingzhangos job=sendgmr) by 2002:a05:6602:737:: with SMTP id
 g23mr12681753iox.130.1617403454399; Fri, 02 Apr 2021 15:44:14 -0700 (PDT)
Date: Fri,  2 Apr 2021 22:43:56 +0000
In-Reply-To: <20210402224359.2297157-1-jingzhangos@google.com>
Message-Id: <20210402224359.2297157-2-jingzhangos@google.com>
Mime-Version: 1.0
References: <20210402224359.2297157-1-jingzhangos@google.com>
X-Mailer: git-send-email 2.31.0.208.g409f899ff0-goog
Subject: [PATCH 1/4] KVM: stats: Separate common stats from architecture
 specific ones
From: Jing Zhang <jingzhangos@google.com>
To: KVM <kvm@vger.kernel.org>, KVMARM <kvmarm@lists.cs.columbia.edu>,
        LinuxMIPS <linux-mips@vger.kernel.org>,
        KVMPPC <kvm-ppc@vger.kernel.org>,
        LinuxS390 <linux-s390@vger.kernel.org>,
        Linuxkselftest <linux-kselftest@vger.kernel.org>,
        Paolo Bonzini <pbonzini@redhat.com>,
        Marc Zyngier <maz@kernel.org>,
        James Morse <james.morse@arm.com>,
        Julien Thierry <julien.thierry.kdev@gmail.com>,
        Suzuki K Poulose <suzuki.poulose@arm.com>,
        Will Deacon <will@kernel.org>,
        Huacai Chen <chenhuacai@kernel.org>,
        Aleksandar Markovic <aleksandar.qemu.devel@gmail.com>,
        Thomas Bogendoerfer <tsbogend@alpha.franken.de>,
        Paul Mackerras <paulus@ozlabs.org>,
        Christian Borntraeger <borntraeger@de.ibm.com>,
        Janosch Frank <frankja@linux.ibm.com>,
        David Hildenbrand <david@redhat.com>,
        Cornelia Huck <cohuck@redhat.com>,
        Claudio Imbrenda <imbrenda@linux.ibm.com>,
        Sean Christopherson <seanjc@google.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Jim Mattson <jmattson@google.com>,
        Peter Shier <pshier@google.com>,
        Oliver Upton <oupton@google.com>,
        David Rientjes <rientjes@google.com>,
        Emanuele Giuseppe Esposito <eesposit@redhat.com>
Cc: Jing Zhang <jingzhangos@google.com>
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Put all common statistics in a separate structure to ease
statistics handling for the incoming new statistics API.

No functional change intended.

Signed-off-by: Jing Zhang <jingzhangos@google.com>
---
 arch/arm64/include/asm/kvm_host.h   |  9 ++-------
 arch/arm64/kvm/guest.c              | 12 ++++++------
 arch/mips/include/asm/kvm_host.h    |  9 ++-------
 arch/mips/kvm/mips.c                | 12 ++++++------
 arch/powerpc/include/asm/kvm_host.h |  9 ++-------
 arch/powerpc/kvm/book3s.c           | 12 ++++++------
 arch/powerpc/kvm/book3s_hv.c        | 12 ++++++------
 arch/powerpc/kvm/book3s_pr.c        |  2 +-
 arch/powerpc/kvm/book3s_pr_papr.c   |  2 +-
 arch/powerpc/kvm/booke.c            | 14 +++++++-------
 arch/s390/include/asm/kvm_host.h    |  9 ++-------
 arch/s390/kvm/kvm-s390.c            | 12 ++++++------
 arch/x86/include/asm/kvm_host.h     |  9 ++-------
 arch/x86/kvm/x86.c                  | 14 +++++++-------
 include/linux/kvm_host.h            |  5 +++++
 include/linux/kvm_types.h           | 12 ++++++++++++
 virt/kvm/kvm_main.c                 | 14 +++++++-------
 17 files changed, 80 insertions(+), 88 deletions(-)

```
#### [PATCH] KVM: SVM: Add support for KVM_SEV_SEND_CANCEL commandFrom: Steve Rutherford <srutherford@google.com>
##### From: Steve Rutherford <srutherford@google.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Steve Rutherford <srutherford@google.com>
X-Patchwork-Id: 12180185
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
	by smtp.lore.kernel.org (Postfix) with ESMTP id AF627C433ED
	for <kvm@archiver.kernel.org>; Fri,  2 Apr 2021 01:45:41 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 835AA610CB
	for <kvm@archiver.kernel.org>; Fri,  2 Apr 2021 01:45:41 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S233901AbhDBBpk (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Thu, 1 Apr 2021 21:45:40 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:50906 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S231168AbhDBBpj (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 1 Apr 2021 21:45:39 -0400
Received: from mail-qk1-x749.google.com (mail-qk1-x749.google.com
 [IPv6:2607:f8b0:4864:20::749])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 92F3EC061788
        for <kvm@vger.kernel.org>; Thu,  1 Apr 2021 18:45:39 -0700 (PDT)
Received: by mail-qk1-x749.google.com with SMTP id c7so4949334qka.6
        for <kvm@vger.kernel.org>; Thu, 01 Apr 2021 18:45:39 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=date:message-id:mime-version:subject:from:to:cc;
        bh=B7WcpZ6OMWphpXj982R+9f98aP8oPdWyveFaKChJc9U=;
        b=ShvmTpFEutpHpZUiSFstp1N4vq7foUYvHyUdFzMRaF7EisCH49QrnqUAoMyvnhnA6e
         K5HKDMBtLDiR143ruaUn6/6D088D8A+RwRxGKLhSlG56lKFsw9Z9EzgB4Pozzcg1J6ev
         jXTLXTSRs+GKpp/V6YULuy/GKwhDUt2XwELt2bHJcMdbOEZU6HCggtHyXe0EcpxhmXcH
         ZHT596H618QJZEIZr5EoaJ+pCFaxkFxOSkgpsu68AW2Qn2d9DRurIpmYDgXwD/88WJS9
         YZJ8xGqsXZgPsGAraPgOSnGQwKMtUOFOYa3tN80QRrNqWyA3XOyzeYr5nd3/Wruao94t
         HRzw==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:date:message-id:mime-version:subject:from:to:cc;
        bh=B7WcpZ6OMWphpXj982R+9f98aP8oPdWyveFaKChJc9U=;
        b=o2Iv933rUNVINVQXLAGLMH2Wbw8R+0MleSnLt4BwrGvijNTl7SoOysdY5ZJIfiPO6L
         Nk9w4kiMRK/q1Jw9j7J99Kdaccp1/l1YdhS4WD+KImdgu9UWRu4PfBrQytjzcSO23Koi
         tptOIVvyGS6PZqylBo0tMeKUhBlZIX2XvK4c6IqdpgFYW7B9no+fOEzDL8mG+K6uCzNg
         wqRVY2C48ZIh9c3m5O92BtUjSb1dIzweYOML3+yEphWcTx4GLZwusXs65E9621SxDLQH
         S1haCyq3z6N+nd+r1rij+Uxb/TuXZInT2nhmAVJpm4uyMEwHXFKBJXHuesh4/FwH9+9H
         aerg==
X-Gm-Message-State: AOAM531kzHdAtxXZXcxUw5IAoWY3NgeWnTzqFt5gdNrMW2PEd5AWZa/N
        T952Hok3Jjl5ooa+a7mu9kC/bCDJ6uUnQ0wlcUBDxSKDBAumoiITFUOO826FtTWmXWQlrjomNWA
        ce3y3XRHx+avavVKQEXPHFzd7saBegGZVGWh+fmMq+T9QkUvPFE8fA9wMaICLUKXoYUB5+Gc=
X-Google-Smtp-Source: 
 ABdhPJw5qj6CWaSf0NeH4Vuwhk3KPzvrtiaesRG6UETXTQ2Z1/J4sPx9X350idkyGLf9t/JpnUmBYgHYpNO1kqOIxA==
X-Received: from riemann.sea.corp.google.com
 ([2620:15c:158:202:68ed:8390:2860:e44a])
 (user=srutherford job=sendgmr) by 2002:a0c:e409:: with SMTP id
 o9mr1023699qvl.31.1617327938539; Thu, 01 Apr 2021 18:45:38 -0700 (PDT)
Date: Thu,  1 Apr 2021 18:44:38 -0700
Message-Id: <20210402014438.1721086-1-srutherford@google.com>
Mime-Version: 1.0
X-Mailer: git-send-email 2.31.0.208.g409f899ff0-goog
Subject: [PATCH] KVM: SVM: Add support for KVM_SEV_SEND_CANCEL command
From: Steve Rutherford <srutherford@google.com>
To: kvm@vger.kernel.org
Cc: linux-kernel@vger.kernel.org, natet@google.com,
        Ashish.Kalra@amd.com, brijesh.singh@amd.com, pbonzini@redhat.com,
        Steve Rutherford <srutherford@google.com>
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

After completion of SEND_START, but before SEND_FINISH, the source VMM can
issue the SEND_CANCEL command to stop a migration. This is necessary so
that a cancelled migration can restart with a new target later.

Signed-off-by: Steve Rutherford <srutherford@google.com>
---
 .../virt/kvm/amd-memory-encryption.rst        |  9 +++++++
 arch/x86/kvm/svm/sev.c                        | 24 +++++++++++++++++++
 include/linux/psp-sev.h                       | 10 ++++++++
 include/uapi/linux/kvm.h                      |  2 ++
 4 files changed, 45 insertions(+)

```
#### [RFCv1 1/7] x86/mm: Move force_dma_unencrypted() to common code
##### From: "Kirill A. Shutemov" <kirill@shutemov.name>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: "Kirill A. Shutemov" <kirill@shutemov.name>
X-Patchwork-Id: 12181161
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.8 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT
	autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id BBA0AC433ED
	for <kvm@archiver.kernel.org>; Fri,  2 Apr 2021 15:27:05 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 8C3126115B
	for <kvm@archiver.kernel.org>; Fri,  2 Apr 2021 15:27:05 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S236067AbhDBP1F (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Fri, 2 Apr 2021 11:27:05 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:58506 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S235286AbhDBP1B (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 2 Apr 2021 11:27:01 -0400
Received: from mail-lj1-x232.google.com (mail-lj1-x232.google.com
 [IPv6:2a00:1450:4864:20::232])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 44B01C06178C
        for <kvm@vger.kernel.org>; Fri,  2 Apr 2021 08:27:00 -0700 (PDT)
Received: by mail-lj1-x232.google.com with SMTP id u20so5905823lja.13
        for <kvm@vger.kernel.org>; Fri, 02 Apr 2021 08:27:00 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=shutemov-name.20150623.gappssmtp.com; s=20150623;
        h=from:to:cc:subject:date:message-id:in-reply-to:references
         :mime-version:content-transfer-encoding;
        bh=WavDtTX6TrwFdeBmXF60wrPd9BJChmTHA9LJTzuJkoU=;
        b=d48Z14vtQeTBnmY3KjiBOkvoSzWnEnzKL51lW9dQ/pvruzLz/a1kIWWaJwVfs6kDZs
         YGsq19NufLNS7oWgqkvDcXDssbIfw5QE2wgM6Z8Xtyebjke6D3u0lD07g7N5QFnGS4KY
         fVIcDYJaHOHIexJOKjE6YqJeJoksxdr+/9dYAc7bzG0GsfjphMTzDWIIgW2IKZzJpw6B
         OJY7QQsDq4EPZgDVbNJGDJQC2pBkR9bhlitGvowGSfd9mGiQzse9TYr6jA6U/8lA/HEt
         HILjBm4R6sWJxEx5Rmjyc0Y7wsAQRlTLqHAd0nesluCwm5hu1H1t/x1Qgxl1mWcxYvmQ
         F2mA==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:in-reply-to
         :references:mime-version:content-transfer-encoding;
        bh=WavDtTX6TrwFdeBmXF60wrPd9BJChmTHA9LJTzuJkoU=;
        b=slFL/i/gpLrFyx9m3uHlTaPH5ZMbpeVj3AuuYZQTDhPZstLft5va0qzV6S0Wl3rZYg
         tYx25H+zEpM2lSEDozCqNkGRd/zRISLkEUcP0vNNl63SbpKBP3NPnz5CncnmddJExtYp
         QctGXqB9wVr4WAN2Af9gpd4Vn/PBKe6U1i6jxyWAOHH5tpswhf5AOLwvJiplrSAcGMta
         2s2y4hKu/gV4l1Xtb0LYkRyhfc9JrQPZVFoialJfR8FPON5XKloSvYssgLovfeaJGsO0
         kVX7Ng/2HI5pGWL2Wi3i5zFjNgefVSqNKeKRG9bc65chXIVqfHot2x3SA6TQosnbegeB
         rXwg==
X-Gm-Message-State: AOAM533Dnuq15DatAER2q9AsIs9ZWV9WjJtRNOERbJLsIqUD3rhu97ty
        zaIsQQXP3AK7pxnQM76fHUonpg==
X-Google-Smtp-Source: 
 ABdhPJyl7494iZYdytvBH3k7wfivOrumpFXeURKxUE8DWVLSKQoyXtMUpDn3OWXNrqBpjaPMpu1Dpg==
X-Received: by 2002:a2e:509:: with SMTP id 9mr8710143ljf.170.1617377218622;
        Fri, 02 Apr 2021 08:26:58 -0700 (PDT)
Received: from box.localdomain ([86.57.175.117])
        by smtp.gmail.com with ESMTPSA id
 o26sm952073ljc.138.2021.04.02.08.26.57
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Fri, 02 Apr 2021 08:26:57 -0700 (PDT)
From: "Kirill A. Shutemov" <kirill@shutemov.name>
X-Google-Original-From: "Kirill A. Shutemov" <kirill.shutemov@linux.intel.com>
Received: by box.localdomain (Postfix, from userid 1000)
        id 246AB100A38; Fri,  2 Apr 2021 18:26:59 +0300 (+03)
To: Dave Hansen <dave.hansen@linux.intel.com>,
        Andy Lutomirski <luto@kernel.org>,
        Peter Zijlstra <peterz@infradead.org>,
        Sean Christopherson <seanjc@google.com>,
        Jim Mattson <jmattson@google.com>
Cc: David Rientjes <rientjes@google.com>,
        "Edgecombe, Rick P" <rick.p.edgecombe@intel.com>,
        "Kleen, Andi" <andi.kleen@intel.com>,
        "Yamahata, Isaku" <isaku.yamahata@intel.com>, x86@kernel.org,
        kvm@vger.kernel.org, linux-mm@kvack.org,
        linux-kernel@vger.kernel.org,
        "Kirill A. Shutemov" <kirill.shutemov@linux.intel.com>
Subject: [RFCv1 1/7] x86/mm: Move force_dma_unencrypted() to common code
Date: Fri,  2 Apr 2021 18:26:39 +0300
Message-Id: <20210402152645.26680-2-kirill.shutemov@linux.intel.com>
X-Mailer: git-send-email 2.26.3
In-Reply-To: <20210402152645.26680-1-kirill.shutemov@linux.intel.com>
References: <20210402152645.26680-1-kirill.shutemov@linux.intel.com>
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

force_dma_unencrypted() has to return true for KVM guest with the memory
protected enabled. Move it out of AMD SME code.

Introduce new config option X86_MEM_ENCRYPT_COMMON that has to be
selected by all x86 memory encryption features.

This is preparation for the following patches.

Signed-off-by: Kirill A. Shutemov <kirill.shutemov@linux.intel.com>
---
 arch/x86/Kconfig                 |  7 +++++-
 arch/x86/include/asm/io.h        |  4 +++-
 arch/x86/mm/Makefile             |  2 ++
 arch/x86/mm/mem_encrypt.c        | 30 -------------------------
 arch/x86/mm/mem_encrypt_common.c | 38 ++++++++++++++++++++++++++++++++
 5 files changed, 49 insertions(+), 32 deletions(-)
 create mode 100644 arch/x86/mm/mem_encrypt_common.c

```
