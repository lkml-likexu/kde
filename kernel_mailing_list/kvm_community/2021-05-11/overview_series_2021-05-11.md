#### [PATCH kvm-unit-tests 1/2] libcflat: clean up and complete long division routines
##### From: Paolo Bonzini <pbonzini@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Paolo Bonzini <pbonzini@redhat.com>
X-Patchwork-Id: 12251593
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.8 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED,USER_AGENT_GIT
	autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 66B05C433B4
	for <kvm@archiver.kernel.org>; Tue, 11 May 2021 17:41:12 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 22B7461378
	for <kvm@archiver.kernel.org>; Tue, 11 May 2021 17:41:12 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S231587AbhEKRmR (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 11 May 2021 13:42:17 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:36112 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S231454AbhEKRmR (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 11 May 2021 13:42:17 -0400
Received: from mail-ej1-x630.google.com (mail-ej1-x630.google.com
 [IPv6:2a00:1450:4864:20::630])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 7C416C06174A
        for <kvm@vger.kernel.org>; Tue, 11 May 2021 10:41:09 -0700 (PDT)
Received: by mail-ej1-x630.google.com with SMTP id b25so30948502eju.5
        for <kvm@vger.kernel.org>; Tue, 11 May 2021 10:41:09 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=sender:from:to:cc:subject:date:message-id:in-reply-to:references
         :mime-version:content-transfer-encoding;
        bh=QcFKWwsZQjmPduID1brcOmkZRMBIxn7KkXSMhmWfN84=;
        b=bnraoL6UQxTGs4ccEMEF6UJp8+3or2YhhuY9sJ66zaHkd+NSFHpVnfIm+YKpgHYp47
         3bRuYeZqAo4y6moDMtHfbd4voPJE0BgJlZmV6qxjEkBeT2gsw0EUCTixHOobrkIAcJdH
         beuoI1/oneZB8ZNK6w2wGnkDbrMTeJj0oBWDabaQ3JjH55ZkTRy35cq4tMEftXcicJ/A
         W2Xuuzj/lSJ+Usst8riFY4snpfv+rdpamWKfnQsJ9XkUtyPRVDymjp1ws7Y4HIt+fkAz
         YXwFrGM4GtWNUXE7fRq8GQrXzLtt/tAv22E0vDz26eBJB7P5xno79MHxejqfGms73+Cm
         bC7w==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:sender:from:to:cc:subject:date:message-id
         :in-reply-to:references:mime-version:content-transfer-encoding;
        bh=QcFKWwsZQjmPduID1brcOmkZRMBIxn7KkXSMhmWfN84=;
        b=bNIx6QIb1fc24xWv12n5Nlj18RlsouC9JpKrywUCYl2FE6l57Uzf0PtYijpePUqR2f
         HIhQ5KJ/kKGPlV2MMgvhNLFQQyeb/MStBkYxYCEk9WAf3Jjz7VHSo7kY/DX4vlnAU5Yg
         lP3Xryo/cr9AO0LRqDvI5Pf6QVXR3crWN/7jMGSxiMMHagGCk7GU2VwzvKD5OOG7j9Un
         DyGSWBvX7/ezuH2h8UsbiwPL3ilm2ge4GJ6UYLC3NLDtbr3pwEAoF1pxBltldQbtZyuM
         oN40Kc0f9KRIFCf6AY85RSWzDYnYQdydf7skdTMULahQyrWH/Ro3Z1xDoBnfGBQVH5RL
         skUw==
X-Gm-Message-State: AOAM533e3EHnTH3x19gpusfMvH+IupYTbcjPhWwTKp1vdueAcyf/9H76
        txe6QsoySOSlimZs6JGKowJbyfOsoPI=
X-Google-Smtp-Source: 
 ABdhPJyov//rnOwePuVhx2EJdtjgAHk2hf/dp+DSDTXoeSvudhZW0deiDLdm45SWhAeQSowrdo2WWA==
X-Received: by 2002:a17:906:3544:: with SMTP id
 s4mr33548521eja.73.1620754868231;
        Tue, 11 May 2021 10:41:08 -0700 (PDT)
Received: from avogadro.redhat.com ([2001:b07:6468:f312:c8dd:75d4:99ab:290a])
        by smtp.gmail.com with ESMTPSA id
 v23sm15239073eda.8.2021.05.11.10.41.07
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Tue, 11 May 2021 10:41:07 -0700 (PDT)
Sender: Paolo Bonzini <paolo.bonzini@gmail.com>
From: Paolo Bonzini <pbonzini@redhat.com>
To: kvm@vger.kernel.org
Cc: Alexandru Elisei <alexandru.elisei@arm.com>
Subject: [PATCH kvm-unit-tests 1/2] libcflat: clean up and complete long
 division routines
Date: Tue, 11 May 2021 19:41:05 +0200
Message-Id: <20210511174106.703235-2-pbonzini@redhat.com>
X-Mailer: git-send-email 2.31.1
In-Reply-To: <20210511174106.703235-1-pbonzini@redhat.com>
References: <20210511174106.703235-1-pbonzini@redhat.com>
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Avoid possible uninitialized variables on machines where
division by zero does not trap.  Add __divmoddi4, and
do not use 64-bit math unnecessarily in __moddi3 and __divdi3.

Reported-by: Alexandru Elisei <alexandru.elisei@arm.com>
Signed-off-by: Paolo Bonzini <pbonzini@redhat.com>
---
 lib/ldiv32.c | 28 +++++++++++++++++++++++++---
 1 file changed, 25 insertions(+), 3 deletions(-)

```
#### [PATCH 1/7] KVM: nVMX: Introduce nested_evmcs_is_used()
##### From: Vitaly Kuznetsov <vkuznets@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Vitaly Kuznetsov <vkuznets@redhat.com>
X-Patchwork-Id: 12250685
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.5 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_CR_TRAILER,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS
	autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 60D5CC433ED
	for <kvm@archiver.kernel.org>; Tue, 11 May 2021 11:20:18 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 38EF36193A
	for <kvm@archiver.kernel.org>; Tue, 11 May 2021 11:20:18 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S231424AbhEKLVW (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 11 May 2021 07:21:22 -0400
Received: from us-smtp-delivery-124.mimecast.com ([170.10.133.124]:39192 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S231426AbhEKLVU (ORCPT
        <rfc822;kvm@vger.kernel.org>); Tue, 11 May 2021 07:21:20 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1620732013;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding:
         in-reply-to:in-reply-to:references:references;
        bh=Y1h+GXoE1AglicQ5eVRu0sY2YtprSiqq8Kcm1LeP5rA=;
        b=XBdL9zZfEgafhtdXiVXuYjPgGtXbu8x+i9bk5F4SVfSNq09CSogWAGIGl4ss8s7prQwXhU
        gl4nBxttcVxCtdEPFjR/LBcweKBTWFka/r1CnvHQ+NRVPycbBuSmsEGqOUjWto0FB8FP/O
        VOGaGL6I7axAC8jxor5DC+WJswPPduY=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-600-d0NkOwW0MJeqmELthxzuxg-1; Tue, 11 May 2021 07:20:10 -0400
X-MC-Unique: d0NkOwW0MJeqmELthxzuxg-1
Received: from smtp.corp.redhat.com (int-mx06.intmail.prod.int.phx2.redhat.com
 [10.5.11.16])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 2E040801106;
        Tue, 11 May 2021 11:20:09 +0000 (UTC)
Received: from vitty.brq.redhat.com (unknown [10.40.193.2])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 2BB8663746;
        Tue, 11 May 2021 11:20:01 +0000 (UTC)
From: Vitaly Kuznetsov <vkuznets@redhat.com>
To: kvm@vger.kernel.org, Paolo Bonzini <pbonzini@redhat.com>
Cc: linux-kernel@vger.kernel.org,
        Sean Christopherson <seanjc@google.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Maxim Levitsky <mlevitsk@redhat.com>
Subject: [PATCH 1/7] KVM: nVMX: Introduce nested_evmcs_is_used()
Date: Tue, 11 May 2021 13:19:50 +0200
Message-Id: <20210511111956.1555830-2-vkuznets@redhat.com>
In-Reply-To: <20210511111956.1555830-1-vkuznets@redhat.com>
References: <20210511111956.1555830-1-vkuznets@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.16
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Unlike regular set_current_vmptr(), nested_vmx_handle_enlightened_vmptrld()
can not be called directly from vmx_set_nested_state() as KVM may not have
all the information yet (e.g. HV_X64_MSR_VP_ASSIST_PAGE MSR may not be
restored yet). Enlightened VMCS is mapped later while getting nested state
pages. In the meantime, vmx->nested.hv_evmcs remains NULL and using it
for various checks is incorrect. In particular, if KVM_GET_NESTED_STATE is
called right after KVM_SET_NESTED_STATE, KVM_STATE_NESTED_EVMCS flag in the
resulting state will be unset (and such state will later fail to load).

Introduce nested_evmcs_is_used() and use 'is_guest_mode(vcpu) &&
vmx->nested.current_vmptr == -1ull' check to detect not-yet-mapped eVMCS
after restore.

Signed-off-by: Vitaly Kuznetsov <vkuznets@redhat.com>
---
 arch/x86/kvm/vmx/nested.c | 31 ++++++++++++++++++++++++++-----
 1 file changed, 26 insertions(+), 5 deletions(-)

```
#### [PATCH] KVM: PPC: Book3S HV: Fix kvm_unmap_gfn_range_hv() for Hash MMU
##### From: Michael Ellerman <mpe@ellerman.id.au>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Michael Ellerman <mpe@ellerman.id.au>
X-Patchwork-Id: 12250659
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-18.8 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,
	INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED,
	USER_AGENT_GIT autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id DDF5BC433B4
	for <kvm@archiver.kernel.org>; Tue, 11 May 2021 10:55:11 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id A47C0613C8
	for <kvm@archiver.kernel.org>; Tue, 11 May 2021 10:55:11 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S230458AbhEKK4Q (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 11 May 2021 06:56:16 -0400
Received: from ozlabs.org ([203.11.71.1]:47903 "EHLO ozlabs.org"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S230382AbhEKK4Q (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 11 May 2021 06:56:16 -0400
Received: by ozlabs.org (Postfix, from userid 1034)
        id 4FfZZN4p2zz9t14; Tue, 11 May 2021 20:55:08 +1000 (AEST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple; d=ellerman.id.au;
        s=201909; t=1620730508;
        bh=B4zCMGOZBSo431ZwaVwZwLRLvWTkJgniLzw1qREC68g=;
        h=From:To:Cc:Subject:Date:From;
        b=IzYRfA1rL29TjC83Jdh94WPZjuw8ebS11J/kDt3f/CIMk1LS+yB8JZ9QnHBFHNh43
         rwaoq6Cbd369Cm4dxelycd/+AtWDp+v5P5UT4kOsLQ6bfYaf35mjB1IA+ki3+HxpVB
         hZN2/+aKdz/iN8zaRvoIopxRRplqJ9VISAYn0oqlD5mSSWmVvZyh12aAeWFXS4eT49
         F70lzjLVdvsLe7vBjpUC1YCus4FSkoi0P42bAEFN59KxQjtHqjhEcUFxdJpTnJSQz0
         F5skh3PDiZQhQ74ETQpOpsdN98Dk54EgL9MQAUL0Y95YXaW4cBFrCxBUMiOO3eVxUK
         pL3MD/9f4VA+A==
From: Michael Ellerman <mpe@ellerman.id.au>
To: linuxppc-dev@lists.ozlabs.org
Cc: npiggin@gmail.com, kvm@vger.kernel.org, kvm-ppc@vger.kernel.org,
        seanjc@google.com, pbonzini@redhat.com
Subject: [PATCH] KVM: PPC: Book3S HV: Fix kvm_unmap_gfn_range_hv() for Hash
 MMU
Date: Tue, 11 May 2021 20:54:59 +1000
Message-Id: <20210511105459.800788-1-mpe@ellerman.id.au>
X-Mailer: git-send-email 2.25.1
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Commit 32b48bf8514c ("KVM: PPC: Book3S HV: Fix conversion to gfn-based
MMU notifier callbacks") fixed kvm_unmap_gfn_range_hv() by adding a for
loop over each gfn in the range.

But for the Hash MMU it repeatedly calls kvm_unmap_rmapp() with the
first gfn of the range, rather than iterating through the range.

This exhibits as strange guest behaviour, sometimes crashing in firmare,
or booting and then guest userspace crashing unexpectedly.

Fix it by passing the iterator, gfn, to kvm_unmap_rmapp().

Fixes: 32b48bf8514c ("KVM: PPC: Book3S HV: Fix conversion to gfn-based MMU notifier callbacks")
Signed-off-by: Michael Ellerman <mpe@ellerman.id.au>
Reviewed-by: Sean Christopherson <seanjc@google.com>
---
 arch/powerpc/kvm/book3s_64_mmu_hv.c | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

I plan to take this via the powerpc fixes branch.

```
#### [kvm-unit-tests PATCH 1/2] x86: Do not assign values to unaligned pointer to 128 bits
##### From: Jacob Xu <jacobhxu@google.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Jacob Xu <jacobhxu@google.com>
X-Patchwork-Id: 12249467
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
	by smtp.lore.kernel.org (Postfix) with ESMTP id 1563FC433B4
	for <kvm@archiver.kernel.org>; Tue, 11 May 2021 01:50:23 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id DA4F1614A5
	for <kvm@archiver.kernel.org>; Tue, 11 May 2021 01:50:22 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S230407AbhEKBv1 (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Mon, 10 May 2021 21:51:27 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:47554 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S230218AbhEKBv1 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 10 May 2021 21:51:27 -0400
Received: from mail-yb1-xb4a.google.com (mail-yb1-xb4a.google.com
 [IPv6:2607:f8b0:4864:20::b4a])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id AC9B4C061574
        for <kvm@vger.kernel.org>; Mon, 10 May 2021 18:50:21 -0700 (PDT)
Received: by mail-yb1-xb4a.google.com with SMTP id
 s10-20020a252c0a0000b02904f8e566d0f2so5241598ybs.3
        for <kvm@vger.kernel.org>; Mon, 10 May 2021 18:50:21 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=date:message-id:mime-version:subject:from:to:cc;
        bh=wltQklr1vvKAD1oLJp4HCNiiDRXnJusVk0dhzmUFIDQ=;
        b=PXJV9Cy5DyeRd8DWpsO8uoCCVEQ7dn3NaEAeoMOfG3EGM3mb6YYfJrcBP/6GuZTaLL
         9z7EA5zeTWXZ9FCLDxqHmb+K73cd0G+qn6hXHpQukZdvoWlaUPvDLQ72d0IfI/9YL/0t
         AI+RdeRGF/ytQ17YQZJbBHFUlHG+LJ9rlK3mZpZhM0LZN6eBRkS4ZPk51o1704ZhfCtf
         JnqQhu8VQj08LEMd3hV328mTbqTHI6dECNzXftV/DoDkMcHm/HKkMY3DAjYKqoYFKUkq
         mDyu1ktlWDJdL0L30lDhf1NK9u0fX52v1FX6MscD1tNABdI821MBBbJ0ZEB2w27LDyuR
         TzSA==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:date:message-id:mime-version:subject:from:to:cc;
        bh=wltQklr1vvKAD1oLJp4HCNiiDRXnJusVk0dhzmUFIDQ=;
        b=Alma8NWn1DtKHCXPnfP3h8nzlFDQJ8/jtl7+Juftmf4nvj6ZyHYKYkBHxcT2QiEoPP
         M0ZXVQUpLyirvldOhwUeuDoZL4GvIaOQacLXhQFnivTEbZ9jKQsdDOV5y4ls92gmKShx
         EgfAsKyw7A40DlYwcTzMw4Jk8Iom0R7YBo3TVvjrJ8dEAxJx9G/ciKIr5xngexxyCZCr
         /PGHmOzlaooIm5XcWeU+W6TFYMpHN/1gLZQrp0uhJr2L2N1Afb1ubScj94pXAdht32P7
         6h9iAM21Etow8d7OjjRp8ALW/NV4lAeXDkqic3azXw729B7Lb7JbGEzsEytmnzrdG8qk
         2gzQ==
X-Gm-Message-State: AOAM530ZjE/klQTTirMa3P8b+KBsoaRUF/bzTK5jtiCJYMXBQsI59uR0
        pka6NEI31SLWEepCGxI7fQ4bxkczrfvWiw==
X-Google-Smtp-Source: 
 ABdhPJyev/Wm8x/2coUBl6gFqvJqrZEaQszS60FIOyiOxjROsDy5GpY1ZYnLjFU2BoxmyaVyfVRzEn20QF9L9A==
X-Received: from mhmmm.sea.corp.google.com
 ([2620:15c:100:202:da9d:6257:8f5f:1bcc])
 (user=jacobhxu job=sendgmr) by 2002:a25:cac7:: with SMTP id
 a190mr37045252ybg.144.1620697820410; Mon, 10 May 2021 18:50:20 -0700 (PDT)
Date: Mon, 10 May 2021 18:50:15 -0700
Message-Id: <20210511015016.815461-1-jacobhxu@google.com>
Mime-Version: 1.0
X-Mailer: git-send-email 2.31.1.607.g51e8a6a459-goog
Subject: [kvm-unit-tests PATCH 1/2] x86: Do not assign values to unaligned
 pointer to 128 bits
From: Jacob Xu <jacobhxu@google.com>
To: Paolo Bonzini <pbonzini@redhat.com>,
        Jim Mattson <jmattson@google.com>,
        Sean Christopherson <seanjc@google.com>
Cc: kvm@vger.kernel.org, Jacob Xu <jacobhxu@google.com>
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

When compiled with clang, the following statement gets converted into a
movaps instructions.
mem->u[0] = 5; mem->u[1] = 6; mem->u[2] = 7; mem->u[3] = 8;

Since mem is an unaligned pointer to sse_union, we get a GP when
running. Let's avoid using a pointer to sse_union at all, since doing so
implies that the pointer is aligned to 128 bits.

Fixes: e5e76263b5 ("x86: add additional test cases for sse exceptions to
emulator.c")

Signed-off-by: Jacob Xu <jacobhxu@google.com>
---
 x86/emulator.c | 67 +++++++++++++++++++++++++-------------------------
 1 file changed, 33 insertions(+), 34 deletions(-)

```
#### [kvm-unit-tests PATCH] x86: Convert vmx_tests.c comments to ASCIIFrom: Jim Mattson <jmattson@google.com>
##### From: Jim Mattson <jmattson@google.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 8bit
X-Patchwork-Submitter: Jim Mattson <jmattson@google.com>
X-Patchwork-Id: 12252251
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
	by smtp.lore.kernel.org (Postfix) with ESMTP id 9ADABC433B4
	for <kvm@archiver.kernel.org>; Tue, 11 May 2021 22:10:07 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 62A666191A
	for <kvm@archiver.kernel.org>; Tue, 11 May 2021 22:10:07 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S230009AbhEKWLN (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 11 May 2021 18:11:13 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:40648 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S229637AbhEKWLN (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 11 May 2021 18:11:13 -0400
Received: from mail-pl1-x649.google.com (mail-pl1-x649.google.com
 [IPv6:2607:f8b0:4864:20::649])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 4A238C061574
        for <kvm@vger.kernel.org>; Tue, 11 May 2021 15:10:05 -0700 (PDT)
Received: by mail-pl1-x649.google.com with SMTP id
 m10-20020a170902f20ab02900ed7e32ff42so8183977plc.19
        for <kvm@vger.kernel.org>; Tue, 11 May 2021 15:10:05 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=date:message-id:mime-version:subject:from:to:cc
         :content-transfer-encoding;
        bh=13xt/09p3n54kTsPIZnNmQLqQsy13uIdS7rJhB8C15Q=;
        b=pi9W/sfCZjmPScfx6I0ku6MpZrlLYMFTiAzsXMHhcv/fR/XEf+qt+YLy6+4XvpCMFA
         ru9JFmL2W2Q5Y8Et9inbzTKU1FKjyr7nadWr0wBWDpckQkNzHTaXaA5YNMLyGidbhxDY
         pSRDPe10193rG7lb8AkVaIShKbrJYDNR/F3cNnY93ltVsWPyhH4dVEBSJbN79nNKuqju
         5HU5KVAZrrbSKyPkUkR6Jzt0N7iHMb1A4zTziEHyjZRzNIA9HeuwdiJ2HTWQMC1aIljf
         mA4cZDjLjK2r33spzAe1UfAGVFGeZSJvOfKG3IINeW+RG159Xs99TcVu5aMc2JOxxKn4
         0k7g==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:date:message-id:mime-version:subject:from:to:cc
         :content-transfer-encoding;
        bh=13xt/09p3n54kTsPIZnNmQLqQsy13uIdS7rJhB8C15Q=;
        b=XBmKFn8n3ggN1zpgf/3gdHfYAyVj1i/cXlaNy32988kv3yfYuyc++Yrhhavozp9K/A
         y9Q2Rs2NNdGdBpQGB1VCD9xMhvuIdxCgsOCKCeFMwY5acxNXACDacAs+cdsQ1eJ8+gQ2
         gs5Q+gdHp3KfMHzkd3144a4vQ7+lUanu2gI+nUpO5Vx4gtIBVq8ZqWwxoSZYnaKZUhJw
         JyGVotm6vjtfZUAFgvRdxfpk29I3AfztwraKUUEjicaSaqv9v9s1Mr7JvYR7guThA5kM
         MOA38H3IhCvfC1dhZVP7Ysh7CuSZDnSQdZuzrKSOP+NLOeSxprs8RLCkCzCqYywgXtEQ
         orEA==
X-Gm-Message-State: AOAM531q9gvPJvZ65KSewAGsIy6rxhYBdlHTzTQITqdIWghVB1H8AQXD
        ot7U/3WFtiCMnYRSGxXyL2sbFNLoeICAqA==
X-Google-Smtp-Source: 
 ABdhPJyBsk58YHK/PF5rVmpWXRhXJI7AiVbtXSxPdhecd7QZZS3o5VrxYcaziJeOl2266byaHKmvEohkY8u55g==
X-Received: from tortoise.c.googlers.com
 ([fda3:e722:ac3:10:7f:e700:c0a8:1a0d])
 (user=jmattson job=sendgmr) by 2002:aa7:96ea:0:b029:28c:e131:f0f with SMTP id
 i10-20020aa796ea0000b029028ce1310f0fmr32910200pfq.11.1620771004724; Tue, 11
 May 2021 15:10:04 -0700 (PDT)
Date: Tue, 11 May 2021 15:09:49 -0700
Message-Id: <20210511220949.1019978-1-jmattson@google.com>
Mime-Version: 1.0
X-Mailer: git-send-email 2.31.1.607.g51e8a6a459-goog
Subject: [kvm-unit-tests PATCH] x86: Convert vmx_tests.c comments to ASCII
From: Jim Mattson <jmattson@google.com>
To: Paolo Bonzini <pbonzini@redhat.com>, kvm@vger.kernel.org
Cc: Jim Mattson <jmattson@google.com>
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Some strange characters snuck into this file. Convert them to ASCII
for better readability.

Signed-off-by: Jim Mattson <jmattson@google.com>
---
 x86/vmx_tests.c | 44 ++++++++++++++++++++++----------------------
 1 file changed, 22 insertions(+), 22 deletions(-)

```
#### [PATCH v6 01/16] perf/x86/intel: Add EPT-Friendly PEBS for Ice Lake Server
##### From: Like Xu <like.xu@linux.intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Like Xu <like.xu@linux.intel.com>
X-Patchwork-Id: 12249555
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.8 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED,USER_AGENT_GIT
	autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 91A1FC433B4
	for <kvm@archiver.kernel.org>; Tue, 11 May 2021 02:43:11 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 5F2AC6109F
	for <kvm@archiver.kernel.org>; Tue, 11 May 2021 02:43:11 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S230011AbhEKCoL (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Mon, 10 May 2021 22:44:11 -0400
Received: from mga03.intel.com ([134.134.136.65]:7532 "EHLO mga03.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S229736AbhEKCoI (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 10 May 2021 22:44:08 -0400
IronPort-SDR: 
 6qQcynzDX3TvTIyIX1vV4daM+qtL4XQl+DUaalGr3PEPVQyyFEGXrJJp484AdC/cqMEPMtcFJ+
 hvevsuQZ71Jg==
X-IronPort-AV: E=McAfee;i="6200,9189,9980"; a="199391169"
X-IronPort-AV: E=Sophos;i="5.82,290,1613462400";
   d="scan'208";a="199391169"
Received: from fmsmga002.fm.intel.com ([10.253.24.26])
  by orsmga103.jf.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 10 May 2021 19:43:02 -0700
IronPort-SDR: 
 cANaMB5eRdMayD4i2mA06SvvDqq8xbutLBgNJ8i2HhsOfrxMwbjYUa/7yG1PTIj8ad92zPfpUu
 Z9TQLANSXbkg==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.82,290,1613462400";
   d="scan'208";a="468591571"
Received: from clx-ap-likexu.sh.intel.com ([10.239.48.108])
  by fmsmga002.fm.intel.com with ESMTP; 10 May 2021 19:42:59 -0700
From: Like Xu <like.xu@linux.intel.com>
To: Peter Zijlstra <peterz@infradead.org>,
        Paolo Bonzini <pbonzini@redhat.com>
Cc: Borislav Petkov <bp@alien8.de>,
        Sean Christopherson <seanjc@google.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>, weijiang.yang@intel.com,
        Kan Liang <kan.liang@linux.intel.com>, ak@linux.intel.com,
        wei.w.wang@intel.com, eranian@google.com, liuxiangdong5@huawei.com,
        linux-kernel@vger.kernel.org, x86@kernel.org, kvm@vger.kernel.org,
        Like Xu <like.xu@linux.intel.com>
Subject: [PATCH v6 01/16] perf/x86/intel: Add EPT-Friendly PEBS for Ice Lake
 Server
Date: Tue, 11 May 2021 10:41:59 +0800
Message-Id: <20210511024214.280733-2-like.xu@linux.intel.com>
X-Mailer: git-send-email 2.31.1
In-Reply-To: <20210511024214.280733-1-like.xu@linux.intel.com>
References: <20210511024214.280733-1-like.xu@linux.intel.com>
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
#### [PATCH v4 1/7] KVM: x86/mmu: Deduplicate rmap freeingFrom: Ben Gardon <bgardon@google.com>
##### From: Ben Gardon <bgardon@google.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Ben Gardon <bgardon@google.com>
X-Patchwork-Id: 12251567
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
	by smtp.lore.kernel.org (Postfix) with ESMTP id 1879FC433B4
	for <kvm@archiver.kernel.org>; Tue, 11 May 2021 17:16:28 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id D34C5613C5
	for <kvm@archiver.kernel.org>; Tue, 11 May 2021 17:16:27 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S231963AbhEKRRc (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 11 May 2021 13:17:32 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:58698 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S231407AbhEKRR1 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 11 May 2021 13:17:27 -0400
Received: from mail-yb1-xb49.google.com (mail-yb1-xb49.google.com
 [IPv6:2607:f8b0:4864:20::b49])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 574C0C061574
        for <kvm@vger.kernel.org>; Tue, 11 May 2021 10:16:19 -0700 (PDT)
Received: by mail-yb1-xb49.google.com with SMTP id
 a7-20020a5b00070000b02904ed415d9d84so24395940ybp.0
        for <kvm@vger.kernel.org>; Tue, 11 May 2021 10:16:19 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=date:in-reply-to:message-id:mime-version:references:subject:from:to
         :cc;
        bh=vLNj1cIP+oKa6jMGIXslJ5VeKEsicN8EXBa0wVTEUbA=;
        b=JziDELrLzdPOVVFcZt2LMfBLwE9wYJJcgRtPq6LalRlVGfBlCaSSNjjpuJIqS5rTcu
         sLAB7kj4PyVss+KydeFzAeZnMpNz/V6TxaUCA+RxL5Sz+r3xoh06AWMEAGJAFF9KqacO
         jqLsqECetEMpiMlkqx/Hv4Qo8mOgv6wb5BqTycYEeQlAfBFWuO7MJzG3V3ZsTTSOC2Fv
         QNS3RPjEpYxd0zeEiBP0q476wg0dgxjtwASw9JIkp/5rzWVACO7gB5WRZuOBq9L1iJ6z
         iswhbKnSgZw6GLV/o5GXW4ehBFwvXDuxQuSexDPHvHngpExYnnzwoaOdGKQco3pnSeaG
         l9Tw==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:date:in-reply-to:message-id:mime-version
         :references:subject:from:to:cc;
        bh=vLNj1cIP+oKa6jMGIXslJ5VeKEsicN8EXBa0wVTEUbA=;
        b=tzixI5t6uxSi1KUR1PWpuHdXykEnsLftlLdCsfTT8wvfQVLHzPNnA8Z8P48eXXWb1Y
         3Ko7E/ZXifMoGz7CboKhaAj/m07AlPFh2s9gRxa3sIT2XqBqP9tr4/OXNZnKGf973K/U
         PiZ9Bs49xFovkkAkYIM5RhCC32uti+/RSIe/qGI8ijOg7U6Aq4O6Af6WUIHaGEYObgiR
         8XqvNOwqPMlUpNTcOqGCejJmKuZSDQmjMeImaKJH4LEtr3TxqF72oud6hImwLjOxEfXw
         +DG9m/YH5CzAQ57wu92UiC4PFt2QGXx9WuwtZ734tBiDtFNHmpvllVsEjbrRnU2ys8dJ
         StPg==
X-Gm-Message-State: AOAM5316IQQR3dv1fO1yDXbeBG1fEltoK3YEf0H3HyzUdvycXZ7EA5OV
        4Uhws61JcMz38SaxBshk1e3bdstOhl2S
X-Google-Smtp-Source: 
 ABdhPJxgNIAXOzKJ8wv3a2gXn/nIkxP7cWrxaAtVlTZnD/aTfsAIBISZGToEaZZ3Zw9x0odikRFmHGSjcm2m
X-Received: from bgardon.sea.corp.google.com
 ([2620:15c:100:202:e050:3342:9ea6:6859])
 (user=bgardon job=sendgmr) by 2002:a25:4c5:: with SMTP id
 188mr22654430ybe.299.1620753378555;
 Tue, 11 May 2021 10:16:18 -0700 (PDT)
Date: Tue, 11 May 2021 10:16:04 -0700
In-Reply-To: <20210511171610.170160-1-bgardon@google.com>
Message-Id: <20210511171610.170160-2-bgardon@google.com>
Mime-Version: 1.0
References: <20210511171610.170160-1-bgardon@google.com>
X-Mailer: git-send-email 2.31.1.607.g51e8a6a459-goog
Subject: [PATCH v4 1/7] KVM: x86/mmu: Deduplicate rmap freeing
From: Ben Gardon <bgardon@google.com>
To: linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Cc: Paolo Bonzini <pbonzini@redhat.com>, Peter Xu <peterx@redhat.com>,
        Sean Christopherson <seanjc@google.com>,
        Peter Shier <pshier@google.com>,
        Yulei Zhang <yulei.kernel@gmail.com>,
        Wanpeng Li <kernellwp@gmail.com>,
        Xiao Guangrong <xiaoguangrong.eric@gmail.com>,
        Kai Huang <kai.huang@intel.com>,
        Keqian Zhu <zhukeqian1@huawei.com>,
        David Hildenbrand <david@redhat.com>,
        Ben Gardon <bgardon@google.com>
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Small code deduplication. No functional change expected.

Reviewed-by: David Hildenbrand <david@redhat.com>
Signed-off-by: Ben Gardon <bgardon@google.com>
---
 arch/x86/kvm/x86.c | 19 +++++++++++--------
 1 file changed, 11 insertions(+), 8 deletions(-)

```
#### [PATCH v2] KVM: x86: use wrpkru directly in kvm_load_{guest|host}_xsave_state
##### From: Jon Kohler <jon@nutanix.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Jon Kohler <jon@nutanix.com>
X-Patchwork-Id: 12251441
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.6 required=3.0 tests=BAYES_00,DKIM_INVALID,
	DKIM_SIGNED,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,MSGID_FROM_MTA_HEADER,SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED,
	USER_AGENT_GIT autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id D1ABFC433B4
	for <kvm@archiver.kernel.org>; Tue, 11 May 2021 16:03:58 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 8B0E46191A
	for <kvm@archiver.kernel.org>; Tue, 11 May 2021 16:03:58 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S230484AbhEKQFD (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 11 May 2021 12:05:03 -0400
Received: from mx0b-002c1b01.pphosted.com ([148.163.155.12]:1240 "EHLO
        mx0b-002c1b01.pphosted.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S230382AbhEKQFC (ORCPT
        <rfc822;kvm@vger.kernel.org>); Tue, 11 May 2021 12:05:02 -0400
Received: from pps.filterd (m0127843.ppops.net [127.0.0.1])
        by mx0b-002c1b01.pphosted.com (8.16.0.43/8.16.0.43) with SMTP id
 14BFwOpC011519;
        Tue, 11 May 2021 09:00:06 -0700
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=nutanix.com;
 h=from : to : cc :
 subject : date : message-id : content-transfer-encoding : content-type :
 mime-version; s=proofpoint20171006;
 bh=gsE1XIklwGdRMGIZBrMbuldutWsMKTAO47dYHXtmBSs=;
 b=VJzPQfJZI7yDO3B/QftqdhRHP/MHdJ0ZB4rGFJcwbkwfLjeUeysGD9UjbZmWJX8OU7RJ
 nim9S55lGxk1d1t/Qe5aGdaOU0k3YRNxoezdE/md6N5itTZZt6qcvkyowPB/BK8vileZ
 1/tI5u/m/8PsZ8cOZTC9BUXU624vjAi+v9V6VIRwu0QDr/Z0cO7H9lQsI8yWXhUgg0Ux
 WDrLjzotCmghRWB+MucCqahvWyc9EqEtvhfJJGqieuwsQQNmPx76vQ/H3IclsMoqLNPY
 Yem7q+YAll2GKsGUKxNsKIsC7+zTstycWPne2xc+4d6XCXDnioZRZwbCvxzy+0Zibxf9 sw==
Received: from nam04-mw2-obe.outbound.protection.outlook.com
 (mail-mw2nam08lp2170.outbound.protection.outlook.com [104.47.73.170])
        by mx0b-002c1b01.pphosted.com with ESMTP id 38ey42unnb-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Tue, 11 May 2021 09:00:05 -0700
ARC-Seal: i=1; a=rsa-sha256; s=arcselector9901; d=microsoft.com; cv=none;
 b=ceWcNpNa4Jktc6MjJ3IFLUd3ghPRClvNY5g5OFKdsJGSFNYjPJJRJDrxAFAcUxSIZSjJ/2BpxLCPhwxL6m0Uzb5NVleu0FGNL0OTYfGPPhjrfBUYMf8t3fgWGUZIeIiPBZebQA3wSnp0Jxa17UNPWbcmocvGbxCJRWZxlqzS1pSI7CCf3OidbmtfpgZrHZoRBKQHOFrY0cIYMFEBPLzTOZStTnunSGkrZiuP+1hsGI4nq7lui+RTEOc/ENneGL7XkIoxdLDGqu5yd6J8uBZdomcNjdhbc3GR+dxP7KDmmp0u+KKoRCvvrc/0ZUdfQzniWvmvv/Kgvj8H+Wu6sdZvuw==
ARC-Message-Signature: i=1; a=rsa-sha256; c=relaxed/relaxed; d=microsoft.com;
 s=arcselector9901;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=gsE1XIklwGdRMGIZBrMbuldutWsMKTAO47dYHXtmBSs=;
 b=ExKO3vB/T3NjY48qMvR//ID6otvZJZSfO6BkhHkfrYmd0a3UWaz2J08Vs1Srd6Rr/7jImFcY1vMOwyMylonAwOczTIvNtitnsH39ynu2taLeebwkK8xt0lTOZ6O2pkZbFnGxR6GAn1vdEpxm1UTKRWBUXIxHqTCYHYDakXhQ7hpGpOZ/57ciV9dMvMibQRdDSP5WBrXSyJb4WukRrirqbrs1P5J50JN5D3jTO6qPoRTIaZ7OWbyxcqVkCP6HdywnkrX2ZoMLE0G/6cDXftAzsG9LQ5VFzQysdK/Au2yOS6Z9OBentljTIIAcMkT4s+j1+kGT2CR06rxPrBb61pLW9g==
ARC-Authentication-Results: i=1; mx.microsoft.com 1; spf=pass
 smtp.mailfrom=nutanix.com; dmarc=pass action=none header.from=nutanix.com;
 dkim=pass header.d=nutanix.com; arc=none
Authentication-Results: nutanix.com; dkim=none (message not signed)
 header.d=none;nutanix.com; dmarc=none action=none header.from=nutanix.com;
Received: from BL0PR02MB4579.namprd02.prod.outlook.com (2603:10b6:208:4b::10)
 by BL3PR02MB7922.namprd02.prod.outlook.com (2603:10b6:208:351::7) with
 Microsoft SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.4108.25; Tue, 11 May
 2021 16:00:03 +0000
Received: from BL0PR02MB4579.namprd02.prod.outlook.com
 ([fe80::75cf:5b99:f963:cc07]) by BL0PR02MB4579.namprd02.prod.outlook.com
 ([fe80::75cf:5b99:f963:cc07%5]) with mapi id 15.20.4108.031; Tue, 11 May 2021
 16:00:03 +0000
From: Jon Kohler <jon@nutanix.com>
Cc: Jon Kohler <jon@nutanix.com>, Babu Moger <babu.moger@amd.com>,
        Thomas Gleixner <tglx@linutronix.de>,
        Ingo Molnar <mingo@redhat.com>, Borislav Petkov <bp@alien8.de>,
        x86@kernel.org, "H. Peter Anvin" <hpa@zytor.com>,
        Paolo Bonzini <pbonzini@redhat.com>,
        Sean Christopherson <seanjc@google.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>,
        Dave Hansen <dave.hansen@intel.com>,
        Yu-cheng Yu <yu-cheng.yu@intel.com>,
        Fenghua Yu <fenghua.yu@intel.com>,
        Tony Luck <tony.luck@intel.com>,
        Petteri Aimonen <jpa@git.mail.kapsi.fi>,
        Kan Liang <kan.liang@linux.intel.com>,
        Uros Bizjak <ubizjak@gmail.com>,
        Andrew Morton <akpm@linux-foundation.org>,
        Mike Rapoport <rppt@kernel.org>,
        Benjamin Thiel <b.thiel@posteo.de>,
        Anshuman Khandual <anshuman.khandual@arm.com>,
        Juergen Gross <jgross@suse.com>,
        Fan Yang <Fan_Yang@sjtu.edu.cn>,
        Dave Jiang <dave.jiang@intel.com>,
        "Peter Zijlstra (Intel)" <peterz@infradead.org>,
        Ricardo Neri <ricardo.neri-calderon@linux.intel.com>,
        Arvind Sankar <nivedita@alum.mit.edu>,
        linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Subject: [PATCH v2] KVM: x86: use wrpkru directly in
 kvm_load_{guest|host}_xsave_state
Date: Tue, 11 May 2021 11:59:18 -0400
Message-Id: <20210511155922.36693-1-jon@nutanix.com>
X-Mailer: git-send-email 2.30.1 (Apple Git-130)
X-Originating-IP: [2601:19b:c501:64d0:68d9:a99b:e44a:d275]
X-ClientProxiedBy: BN6PR12CA0029.namprd12.prod.outlook.com
 (2603:10b6:405:70::15) To BL0PR02MB4579.namprd02.prod.outlook.com
 (2603:10b6:208:4b::10)
MIME-Version: 1.0
X-MS-Exchange-MessageSentRepresentingType: 1
Received: from C02F13YVQ05N.corp.nutanix.com
 (2601:19b:c501:64d0:68d9:a99b:e44a:d275) by
 BN6PR12CA0029.namprd12.prod.outlook.com (2603:10b6:405:70::15) with Microsoft
 SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.4108.25 via Frontend
 Transport; Tue, 11 May 2021 16:00:00 +0000
X-MS-PublicTrafficType: Email
X-MS-Office365-Filtering-Correlation-Id: e58effa2-ebcc-460a-3ad0-08d91495d680
X-MS-TrafficTypeDiagnostic: BL3PR02MB7922:
X-MS-Exchange-Transport-Forked: True
X-Microsoft-Antispam-PRVS: 
 <BL3PR02MB79228457E2F4A9B9CCDA4F5CAF539@BL3PR02MB7922.namprd02.prod.outlook.com>
x-proofpoint-crosstenant: true
X-MS-Oob-TLC-OOBClassifiers: OLM:9508;
X-MS-Exchange-SenderADCheck: 1
X-Microsoft-Antispam: BCL:0;
X-Microsoft-Antispam-Message-Info: 
 oihqoByFArySNFXMly6JjV+hIQUf0JQ60C2hHHT5wx5Tg0zQe+WQctYT8h6RJGTCh8JjnVLoC1IbRnHOll9AR7YCOEEfCcHfq4P98isFEppY65AKrdvXS4uUWOlJqBcCBCvTiaeQsHUaW4sBpslvAAiAx0co4wJuHktehHw6WKw2QKJCNyG5D8AqkeuIDUerzpzvApK2e2mEvrrNE/eLzzq/lCZVXvoiUDalvd9L0DL1NvV2txd/gP39WLyTaYi3Ht3ji+Bt+YUC2gTsJbh0hl4SIlxFEl76fQq50SzXY9hYsaSZUPlPNPaVGNQWOFJ39cXpUydFf1Ulv6xf0g08eal530D3J5LQP47oB+NoO2RdWklpwjf0UTStpL9q8IP0/g5xeFBBCWfqZgD1ap91/nXDI+1/pP//VWxfcTaY92MLFLK1UyuBSjru3Ysb60MxffABdHnnu9n6j8L9EJKelXzU4S1hszDWItQE3PNNGH9n3zumGcWcxYZggix40dsAYpsFniituF7nn8kzt+6sG8jB4gSuNFPTYAbQ1bXnMGjvePrCnioHuTSgPN2MLxBEqcvYQeyfJq+hdzjch/m8VyDs0oiX4/8eORLp8qe5/Zl7aDohR/glc7i3wX7ZmpLr4n4SqcXw1BwnI0ae4Je0dQ==
X-Forefront-Antispam-Report: 
 CIP:255.255.255.255;CTRY:;LANG:en;SCL:1;SRV:;IPV:NLI;SFV:NSPM;H:BL0PR02MB4579.namprd02.prod.outlook.com;PTR:;CAT:NONE;SFS:(39860400002)(366004)(136003)(376002)(396003)(346002)(66556008)(4326008)(6486002)(7406005)(109986005)(1076003)(2616005)(8936002)(7416002)(66946007)(5660300002)(36756003)(316002)(52116002)(7696005)(83380400001)(478600001)(8676002)(2906002)(86362001)(54906003)(186003)(38100700002)(6666004)(16526019)(66476007)(266003);DIR:OUT;SFP:1102;
X-MS-Exchange-AntiSpam-MessageData-ChunkCount: 1
X-MS-Exchange-AntiSpam-MessageData-0: 
 GKaBBA0luGHZSFgioqQEqokf6jOJh+w/05W2dbRc0NL17Mw79cTvcWk/R083B8G3g3IurvK0xXDPLuQmESjaE/50xaud2/lZ3ver7tC+7SvVUQPdwUk5UTpGZzQLiSVkshJueRTIA9vdKlvWu4UFhBrwP5CGJRN43UbUg/JrXddhrEPPyiInZiEJtk63vAt/I4JHY6aIYEWY8veUXw3zoe/EK8Xt5GVDbOB/NiQxhis2bFaswNcTEFHqpHBBK2VQ9rn7yXHV2FJ1rHCeUU12G+0bjDnazr4FRXvPRJhO0SZwYYOrnqwQlSgnk1h432psMRaUapbAq7EqLJmQKaJyVJw/lkg6vR6tdcziKOL7a9fwaEy71mmtLdNBwo/q+qJHOCJ8KonikQL5i9LWiD9xf8ROy0W6JZs09gmdK0hqPM/gI5IvYFrXFZKamX6m8jmGcFhnwCU6wOZOie4CxF7WvCAJ9X9Xh4llN/M8IlDbSdcpusMUu4JkSOgvSF1iBogtKA1odk4kFZZPv/HIOm/WZcGTHRoKcni7rQ5LJD5w3Z1Une+I/0LlIvboC1onRX1b0Isq7SQyf94ZErieJXDkfzNa6X3NUg7GfIRrFfR/I//IN7zhqVR1R9QFi4t6IJ/ZaHNwymdH/wrLRSajr5qycbEgoE+ZP3/q3MjTArVRga+7j9LBYgGqDBJDhJj+DIq0sPuxQ3PWK0jfhtEeiwQWzhtZqK777CMaeAZXlMqBJkz6xEtSpSyO8hO+YHwKSlPSpcvaE9mwyEyaQXgxUlqhjOtMjdRo3HEYUDUgtdyeedfJDdD1LSRm1M5CEbTIiyJmcNzBa03+TKmNfeWePwtc32gDZuX+7jDpZxH9pqwsPDmwpwuwkV7UuBBpympXge2y+s1BRHeEVLT+SyE1ej4Ilgfgmut/q0MdzjNf1lg+RuL7aeRt8nXooLq5bfgBuoTDdst6yTUSe4Y0Vdeywqrrux9+tvg66Sn07pwZLSykXGsrUXeS6HPSWkJeav7HmlC4AD+wV5qg+Ru5po8O96eRgC3USr0EYGOIP2nfm+HMtMo3+Gz5yRbdZh5YoTuEukph9hYltY8kHapFxeOeTHfW+KazTh+CS86tW4oNHqzmOLT7D31y9bE6FGk5FO/kaMBT2b6tLmdliT49E83axwLNzmqKjrN4y1CTgc4tIYgGzVYgl7aFFgYrQs7F6EdTwlAOyPT8rfXAafu//53ENgnxgGMH0aytuhC4mzawyXdwIqsY9FOZ6nadL1ypzmCGViminpSi6FYs28uybq11B/C0q/5f+F2sTI5BwxFDnDA3QRP4Ec5A+8BBUNI7FnfATtEJcCjVkcBWbhoeS2pfYJJQkKWEON6VNQCR76ra52Tt4JrfO7WWkIXzzIyyQLP2PjBk
X-OriginatorOrg: nutanix.com
X-MS-Exchange-CrossTenant-Network-Message-Id: 
 e58effa2-ebcc-460a-3ad0-08d91495d680
X-MS-Exchange-CrossTenant-AuthSource: BL0PR02MB4579.namprd02.prod.outlook.com
X-MS-Exchange-CrossTenant-AuthAs: Internal
X-MS-Exchange-CrossTenant-OriginalArrivalTime: 11 May 2021 16:00:03.3704
 (UTC)
X-MS-Exchange-CrossTenant-FromEntityHeader: Hosted
X-MS-Exchange-CrossTenant-Id: bb047546-786f-4de1-bd75-24e5b6f79043
X-MS-Exchange-CrossTenant-MailboxType: HOSTED
X-MS-Exchange-CrossTenant-UserPrincipalName: 
 3OQ6vbNaEsByObLfr4EZmWbhXKa0U/yJ42X6tbqzdz0KDlD7dyuC09AgVmkowZaXtt6+6EGTqM7zbqGCcQ8d0y3hsuMGYXMhCd48bv1i0bc=
X-MS-Exchange-Transport-CrossTenantHeadersStamped: BL3PR02MB7922
X-Proofpoint-ORIG-GUID: swhGi_z4gKmUCxTv_oW_rbX1YoL6rK7v
X-Proofpoint-GUID: swhGi_z4gKmUCxTv_oW_rbX1YoL6rK7v
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.391,18.0.761
 definitions=2021-05-11_04:2021-05-11,2021-05-11 signatures=0
X-Proofpoint-Spam-Reason: safe
To: unlisted-recipients:; (no To-header on input)
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

kvm_load_host_xsave_state handles xsave on vm exit, part of which is
managing memory protection key state. The latest arch.pkru is updated
with a rdpkru, and if that doesn't match the base host_pkru (which
about 70% of the time), we issue a __write_pkru.

__write_pkru issues another rdpkru internally to try to avoid the
wrpkru, so we're reading the same value back to back when we 100% of
the time know that we need to go directly to wrpkru. This is a 100%
branch miss and extra work that can be skipped.

To improve performance, use wrpkru directly in KVM code and simplify
the uses of __write_pkru such that it can be removed completely.

While we're in this section of code, optimize if condition ordering
prior to wrpkru in both kvm_load_{guest|host}_xsave_state.

For both functions, flip the ordering of the || condition so that
arch.xcr0 & XFEATURE_MASK_PKRU is checked first, which when
instrumented in our evironment appeared to be always true and less
overall work than kvm_read_cr4_bits.

For kvm_load_guest_xsave_state, hoist arch.pkru != host_pkru ahead
one position. When instrumented, I saw this be true roughly ~70% of
the time vs the other conditions which were almost always true.
With this change, we will avoid 3rd condition check ~30% of the time.

Cc: Babu Moger <babu.moger@amd.com>
Signed-off-by: Jon Kohler <jon@nutanix.com>
---
 arch/x86/include/asm/fpu/internal.h  | 10 +++++++++-
 arch/x86/include/asm/pgtable.h       |  2 +-
 arch/x86/include/asm/special_insns.h | 20 +++++---------------
 arch/x86/kvm/x86.c                   | 14 +++++++-------
 4 files changed, 22 insertions(+), 24 deletions(-)

```
#### [PATCH v3] KVM: x86: use wrpkru directly in kvm_load_{guest|host}_xsave_state
##### From: Jon Kohler <jon@nutanix.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Jon Kohler <jon@nutanix.com>
X-Patchwork-Id: 12251557
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.6 required=3.0 tests=BAYES_00,DKIM_INVALID,
	DKIM_SIGNED,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,MSGID_FROM_MTA_HEADER,SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED,
	USER_AGENT_GIT autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 9C4DEC433B4
	for <kvm@archiver.kernel.org>; Tue, 11 May 2021 17:06:59 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 65D746134F
	for <kvm@archiver.kernel.org>; Tue, 11 May 2021 17:06:59 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S231407AbhEKRIE (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 11 May 2021 13:08:04 -0400
Received: from mx0a-002c1b01.pphosted.com ([148.163.151.68]:62970 "EHLO
        mx0a-002c1b01.pphosted.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S230315AbhEKRIE (ORCPT
        <rfc822;kvm@vger.kernel.org>); Tue, 11 May 2021 13:08:04 -0400
Received: from pps.filterd (m0127839.ppops.net [127.0.0.1])
        by mx0a-002c1b01.pphosted.com (8.16.0.43/8.16.0.43) with SMTP id
 14BGqbaw022632;
        Tue, 11 May 2021 10:05:34 -0700
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=nutanix.com;
 h=from : to : cc :
 subject : date : message-id : content-transfer-encoding : content-type :
 mime-version; s=proofpoint20171006;
 bh=CkgOdCQY1f8ytYQzmvw55JD1HLRdCbY03ZsEjGklJ1M=;
 b=ZC09PS9oYpJ3285FCUOZ9GxjO9aFG2CFjJ2wQNnkGW3RV2a0gvxM5ZnnF+Kh83nhVLMS
 AdMRc98JbsFqRsKja91hm6VZMWFenhbVNfy8a0knj36h446klYncj/SXOq3cVPn6twmQ
 xsNSx+0K+fpqQd/c49ervXdQbKPxq12key7oc7NMrrEnbBtsaJhDqgYZKbgL8cCRb3UR
 TyvxHzwBZCtN82iEXli48GMwWKM/MX5RTPklR8b0ky0mp6XhZ9sDG2YWymvN+xrd2imj
 WqjzQ4CfnV8mZB9oSWYexk7ckxNVt+ctnzs/+0Ed0fydnoRNZek2dgE8SIHBPIoVxZdG og==
Received: from nam11-co1-obe.outbound.protection.outlook.com
 (mail-co1nam11lp2169.outbound.protection.outlook.com [104.47.56.169])
        by mx0a-002c1b01.pphosted.com with ESMTP id 38ewh3bxf4-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Tue, 11 May 2021 10:05:34 -0700
ARC-Seal: i=1; a=rsa-sha256; s=arcselector9901; d=microsoft.com; cv=none;
 b=OSb7oEhFsQtkKIb7j+6qeSOgDzuPB1IYxW2qTXvSX3mO+HosVoUAEP+5jivAiNtA/DGT2ZycMvslvv/cQZvlLZxEfqFieqDey0zO0JGdqI9iyFxxRda2kqEvjTl4qnCa1nqagTUIwcZBdsKK6IjL5IBNjzjV0uPWcjHVAq2PFHq/mfk9Jr7dBol9nd6zEBBMOyw1S+F0xfBNKZomb9jLzlV6us/+pZps7h1+pE/WLFVgky1y7ggOo/9S1OIwxeAxHwFw/96xOGs6OPb1E+oENPvITbmFttKgY+j8d8lEtOnN8CwmdAyZ+mnWtasMCPYuDDp8yxETPkgSfCwH3MZhIQ==
ARC-Message-Signature: i=1; a=rsa-sha256; c=relaxed/relaxed; d=microsoft.com;
 s=arcselector9901;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=CkgOdCQY1f8ytYQzmvw55JD1HLRdCbY03ZsEjGklJ1M=;
 b=j5s10fUHDH5d1UX10voFbQB7K1/T1SoQl9UXJc8hyCFAftRE06bBOgS4nazc0EPbdArBvEagd+kkjqwks0zS6TZk2icoTJrmiTOik7uHqOzIznwSh5Y9H6KlzMz5KO8SBV7LjJaloY1wmWzjMI9uxzN90jlbKd34aSoOq/XfNIbzVJIL2Dp5nBibE/hDxFuBm2AiPqtr+K2qkgANn20sweL+MYJ5JkGN4VlHGDPX9IlJozg9lxa0JaC1dweW7w7Vf1j8QARJNI3fO68eWQscNwvk7bbGUR3XzVZBkc0rgomAonkDrv0+007Vdfup+aKJ1fVQZlqEHf4rZxoG/Xl6UA==
ARC-Authentication-Results: i=1; mx.microsoft.com 1; spf=pass
 smtp.mailfrom=nutanix.com; dmarc=pass action=none header.from=nutanix.com;
 dkim=pass header.d=nutanix.com; arc=none
Authentication-Results: nutanix.com; dkim=none (message not signed)
 header.d=none;nutanix.com; dmarc=none action=none header.from=nutanix.com;
Received: from BL0PR02MB4579.namprd02.prod.outlook.com (2603:10b6:208:4b::10)
 by MN2PR02MB6893.namprd02.prod.outlook.com (2603:10b6:208:200::12) with
 Microsoft SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.4108.25; Tue, 11 May
 2021 17:05:29 +0000
Received: from BL0PR02MB4579.namprd02.prod.outlook.com
 ([fe80::75cf:5b99:f963:cc07]) by BL0PR02MB4579.namprd02.prod.outlook.com
 ([fe80::75cf:5b99:f963:cc07%5]) with mapi id 15.20.4108.031; Tue, 11 May 2021
 17:05:29 +0000
From: Jon Kohler <jon@nutanix.com>
Cc: Jon Kohler <jon@nutanix.com>, Babu Moger <babu.moger@amd.com>,
        Thomas Gleixner <tglx@linutronix.de>,
        Ingo Molnar <mingo@redhat.com>, Borislav Petkov <bp@alien8.de>,
        x86@kernel.org, "H. Peter Anvin" <hpa@zytor.com>,
        Paolo Bonzini <pbonzini@redhat.com>,
        Sean Christopherson <seanjc@google.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>,
        Dave Hansen <dave.hansen@intel.com>,
        Yu-cheng Yu <yu-cheng.yu@intel.com>,
        Fenghua Yu <fenghua.yu@intel.com>,
        Tony Luck <tony.luck@intel.com>,
        Uros Bizjak <ubizjak@gmail.com>,
        Petteri Aimonen <jpa@git.mail.kapsi.fi>,
        Al Viro <viro@zeniv.linux.org.uk>,
        Kan Liang <kan.liang@linux.intel.com>,
        Andrew Morton <akpm@linux-foundation.org>,
        Mike Rapoport <rppt@kernel.org>,
        Fan Yang <Fan_Yang@sjtu.edu.cn>,
        Juergen Gross <jgross@suse.com>,
        Benjamin Thiel <b.thiel@posteo.de>,
        Dave Jiang <dave.jiang@intel.com>,
        "Peter Zijlstra (Intel)" <peterz@infradead.org>,
        Ricardo Neri <ricardo.neri-calderon@linux.intel.com>,
        Arvind Sankar <nivedita@alum.mit.edu>,
        linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Subject: [PATCH v3] KVM: x86: use wrpkru directly in
 kvm_load_{guest|host}_xsave_state
Date: Tue, 11 May 2021 13:05:02 -0400
Message-Id: <20210511170508.40034-1-jon@nutanix.com>
X-Mailer: git-send-email 2.30.1 (Apple Git-130)
X-Originating-IP: [2601:19b:c501:64d0:68d9:a99b:e44a:d275]
X-ClientProxiedBy: BN6PR13CA0055.namprd13.prod.outlook.com
 (2603:10b6:404:11::17) To BL0PR02MB4579.namprd02.prod.outlook.com
 (2603:10b6:208:4b::10)
MIME-Version: 1.0
X-MS-Exchange-MessageSentRepresentingType: 1
Received: from C02F13YVQ05N.corp.nutanix.com
 (2601:19b:c501:64d0:68d9:a99b:e44a:d275) by
 BN6PR13CA0055.namprd13.prod.outlook.com (2603:10b6:404:11::17) with Microsoft
 SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.4129.20 via Frontend
 Transport; Tue, 11 May 2021 17:05:27 +0000
X-MS-PublicTrafficType: Email
X-MS-Office365-Filtering-Correlation-Id: 7edc6841-6bf8-4735-1b7f-08d9149efad4
X-MS-TrafficTypeDiagnostic: MN2PR02MB6893:
X-MS-Exchange-Transport-Forked: True
X-Microsoft-Antispam-PRVS: 
 <MN2PR02MB6893AA87345AA06CEDB081A0AF539@MN2PR02MB6893.namprd02.prod.outlook.com>
x-proofpoint-crosstenant: true
X-MS-Oob-TLC-OOBClassifiers: OLM:9508;
X-MS-Exchange-SenderADCheck: 1
X-Microsoft-Antispam: BCL:0;
X-Microsoft-Antispam-Message-Info: 
 y0g/80mlVVAB6uGBvGjcGZCADjIwaVX8c05QaQ4NHQ8NOL5y2cE9N41r2JRb5O88u9ZNAdB3Ao+Ut55YCO0JH2ZkRLXnbEzlHzLR//zfC1AuMLviBqgngXo7cPo6PhUw4ggneB/cbkaqih+VPwbXGgE8CYlo0b3RPdL6blMIP7cfDFFr9WlhGNZea0VQ5EMkq7LSKjrGL8GYxBeEfT4mA0QqF5e8sv7T7O/rt9nlHAvYNGz4q3qRqdJtjLxzxR6nUeGJDHRhLS8EtNDqSZJF8TWOJeVDEOmMoH3GBuqjqtVAGjLnEDaAq9XIkix6Pgho5TL1rQkcI0u5D0vMzRxoy+s2tPPdI0enjQCYG+vvTE7O8SBVEzK9UnfhBXuaX1G3MGf46eah6QrbuZ8f73N1Xvm24a9eK4IZRMWI85L6u0Nj4wYJEoHBo7qhpWHCZ4f+YG++vzCACkCDyrfntwAmSukLqfokEUcM9A2C8AmH5b5ns8MIDHGvDvg3m2JMgt/yVj4nmCiJXvQYn8KA8m9GcudqUbdezELA3T/PlLngGpqhlFa0B0CptO9bpLPomFEEngxyf+xMbtYfS7h48vre//375UN/ZewrNUPj1kyeVoeEstJRRm4O4n16oz0UKk54EgUCstRl34Y/w0irzGBY/g==
X-Forefront-Antispam-Report: 
 CIP:255.255.255.255;CTRY:;LANG:en;SCL:1;SRV:;IPV:NLI;SFV:NSPM;H:BL0PR02MB4579.namprd02.prod.outlook.com;PTR:;CAT:NONE;SFS:(39840400004)(376002)(346002)(136003)(396003)(366004)(38100700002)(66476007)(2616005)(109986005)(186003)(4326008)(16526019)(1076003)(6666004)(7406005)(7416002)(5660300002)(54906003)(2906002)(316002)(8676002)(83380400001)(7696005)(36756003)(478600001)(6486002)(66556008)(66946007)(52116002)(8936002)(86362001)(266003);DIR:OUT;SFP:1102;
X-MS-Exchange-AntiSpam-MessageData-ChunkCount: 1
X-MS-Exchange-AntiSpam-MessageData-0: 
 peq6mmhFgYQ89F6jsDVsNAamFMPs7NC1ki3xrIbns6KCTBntTisctok9EUuDlBGmjmcrHGJMlXSNMQJmGOI0/59o6s92DzIUG3xsahl7NaZaEPyylHwSI8/3iHJxlpT2bJuZ/w71+ZusjdxR46r1YtdyInGfP0iAR7TWMS4ZhyH+SSHPeGhGjvj50QiuVWWQ5X8Erhb8wXzWJ2FHT33wSGXFiNP4w6nJjkbIow4bSpTLLmMDSVHFUopdthXyFapECws3MpOmpuDBvHmoR4orgtt5n+Qhvl4WN19IfctmQiCEkOI+MgFjv2CA3tqFeWQCwNAx6GIhDT35lSGrgcVbiX+/XOlcsBeyVCRb2Uv9bmFewvPaD624brTeLik0RWoJkXuqckzWosFEE0jWTOiQfHOFpVJQ+weoyjsVcIe+ZxozyRqV3jiSUgKATSgAWWPIQNjDaI3GvzBMmfAja5XMkwY964iezMSCoVJmHEvqK+pViYTQYwiQwYbQavbZJy44WCH10IXYQGnbb081Bnrz4ZN1P6WP7aSjyCfbV3YZQbqbCkWesz+wzK+tejBrupZdK6xIZ0BRu9FoOVN/v0Yx37LHtl0i0P7XEwCkxDAUONkhs9W8Qyr6hppTnx3d3KeuYZkhGARbDCrRdCyq4ElTt0UcH87oPwY6pOOO4TjYieg3t6S5UnUsHDbL7fkiuCyGs7lF7Ibx4kRJwzA7O4afBCeA8w9Vqlwjyp4zYfJl93+/r9h3v660HCDstwpns3Jk+BIGFRSP+/vEEuK4MuKibfPtyx0zPFLyJHE1ETYcXLx28YMBKU5sA1rdhPyXq9TOq+v0fMZ7d4altPQANKDmX/NzpP1h1BuTpxUkvJ9vv9xw1NBgoaT56/WIC+A2QKQALdVdK9V6RT2ZGDQ4xR/c0blKxdsCPJodgFsYEwonePRn3B7QGCviakvo64N98Te0AFb2GVWVVl2as+J+fekpfs6RbSg8g0z2WpHeby7OxwtzoIa7MDFFUapggQwdfnWQJhqn5cbcrg3NdX+ug48ozObgqxQ8yZwlqMGVPXyh+otEMWM49fXIN2e2hO4/FU6pjFlZJ/P55K1zB0sLT6x+OWz2BnwUUDvgWXb67oKGIHVGcz57xgH7HKyyUuNPXcjcHFgu2YILVjzpo5aTjb1yN2UxR/SWkCWs0sy4ZZsYdodRg/JWO4KDn214Iq48sOh8E4A735M/CWPPE+LAKu+p1M1NgvoBX9p5rF2c9TaBLcnNYt9LNp73jEqBmQvLJE6zWeVfWHmyE45yi/6yfipmwCphdZT6dP2GqdXcLMFs0rSp0L+afLNjyP7Kht5If+pgvI8tDih6gUSfYoBpM8c2ntO5l3DnCFvsm6SJ+F8B7LHXTjda3nuCe7O4TWGyFFRU
X-OriginatorOrg: nutanix.com
X-MS-Exchange-CrossTenant-Network-Message-Id: 
 7edc6841-6bf8-4735-1b7f-08d9149efad4
X-MS-Exchange-CrossTenant-AuthSource: BL0PR02MB4579.namprd02.prod.outlook.com
X-MS-Exchange-CrossTenant-AuthAs: Internal
X-MS-Exchange-CrossTenant-OriginalArrivalTime: 11 May 2021 17:05:29.7897
 (UTC)
X-MS-Exchange-CrossTenant-FromEntityHeader: Hosted
X-MS-Exchange-CrossTenant-Id: bb047546-786f-4de1-bd75-24e5b6f79043
X-MS-Exchange-CrossTenant-MailboxType: HOSTED
X-MS-Exchange-CrossTenant-UserPrincipalName: 
 Nx+/e+WZiP4OTrmODgyqhtju8Z54323FY7jLCQEl1HLHgp/vkfIa1AxmgepJr7iCfv/BRDK65OZYj19R3Ou//29ZktHe35THmFotGjCn2zk=
X-MS-Exchange-Transport-CrossTenantHeadersStamped: MN2PR02MB6893
X-Proofpoint-ORIG-GUID: dzLPA6DVcDMPd36cBZGWkKA0EmkZDJDw
X-Proofpoint-GUID: dzLPA6DVcDMPd36cBZGWkKA0EmkZDJDw
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.391,18.0.761
 definitions=2021-05-11_04:2021-05-11,2021-05-11 signatures=0
X-Proofpoint-Spam-Reason: safe
To: unlisted-recipients:; (no To-header on input)
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

kvm_load_host_xsave_state handles xsave on vm exit, part of which is
managing memory protection key state. The latest arch.pkru is updated
with a rdpkru, and if that doesn't match the base host_pkru (which
about 70% of the time), we issue a __write_pkru.

__write_pkru issues another rdpkru internally to try to avoid the
wrpkru, so we're reading the same value back to back when we 100% of
the time know that we need to go directly to wrpkru. This is a 100%
branch miss and extra work that can be skipped.

To improve performance, use wrpkru directly in KVM code and simplify
the uses of __write_pkru such that it can be removed completely.

While we're in this section of code, optimize if condition ordering
prior to wrpkru in both kvm_load_{guest|host}_xsave_state.

For both functions, flip the ordering of the || condition so that
arch.xcr0 & XFEATURE_MASK_PKRU is checked first, which when
instrumented in our evironment appeared to be always true and less
overall work than kvm_read_cr4_bits.

For kvm_load_guest_xsave_state, hoist arch.pkru != host_pkru ahead
one position. When instrumented, I saw this be true roughly ~70% of
the time vs the other conditions which were almost always true.
With this change, we will avoid 3rd condition check ~30% of the time.

Cc: Babu Moger <babu.moger@amd.com>
Signed-off-by: Jon Kohler <jon@nutanix.com>
Acked-by: Dave Hansen <dave.hansen@intel.com>
---
v1 -> v2:
 - Addressed comments on approach from Paolo and Dave.
v2 -> v3:
 - fix return-too-soon in switch_fpu_finish, which would
   have sometimes accidentally skipped update_pasid().
 - make sure write_pkru() users do not regress by adding
   pkru == rdpkru() optimization prior to wrpkru() call.

 arch/x86/include/asm/fpu/internal.h  |  8 +++++++-
 arch/x86/include/asm/pgtable.h       |  9 ++++++++-
 arch/x86/include/asm/special_insns.h | 20 +++++---------------
 arch/x86/kvm/x86.c                   | 14 +++++++-------
 4 files changed, 27 insertions(+), 24 deletions(-)

--
2.30.1 (Apple Git-130)

```
#### [PATCH v4] KVM: selftests: Print a message if /dev/kvm is missingFrom: David Matlack <dmatlack@google.com>
##### From: David Matlack <dmatlack@google.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: David Matlack <dmatlack@google.com>
X-Patchwork-Id: 12252023
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
	by smtp.lore.kernel.org (Postfix) with ESMTP id 46B7FC433B4
	for <kvm@archiver.kernel.org>; Tue, 11 May 2021 20:21:28 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 178AE617ED
	for <kvm@archiver.kernel.org>; Tue, 11 May 2021 20:21:28 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S229736AbhEKUWd (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 11 May 2021 16:22:33 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:44520 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S229548AbhEKUWc (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 11 May 2021 16:22:32 -0400
Received: from mail-qt1-x849.google.com (mail-qt1-x849.google.com
 [IPv6:2607:f8b0:4864:20::849])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 0289AC061574
        for <kvm@vger.kernel.org>; Tue, 11 May 2021 13:21:23 -0700 (PDT)
Received: by mail-qt1-x849.google.com with SMTP id
 s11-20020ac85ecb0000b02901ded4f15245so4859269qtx.22
        for <kvm@vger.kernel.org>; Tue, 11 May 2021 13:21:23 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=date:message-id:mime-version:subject:from:to:cc;
        bh=ySDv4Th435kjZfIwnmzgb5838RmbvDKzzPxK4jBsLsU=;
        b=b7gxpOTiK36e4IlyOOUzvOAeiNVmA5WmK1+H6ao/ZTZG8c2WkDWXTelW6cRSbl+8J7
         NVirqQ5ogd3nZ6uao2SRAZWJmReY8THX8WCHk8KPFhYAQ+LaoqDE3guH9scWyZgCxJc7
         YK8xuVFNx3BVilaMk2xWtJMZJ40QsZqrxYdEQeAugDRhfhADOfdF/4zgBkXfocwZIdSP
         Zn7xaAIJ5RRNinW4wLhm+pmhUGDSyVvvnxrwn/sNyCOOY5uoOngMn7jT1KOZSad9Z9bb
         9IhAOMAt1nQFmkr0Rl0H6UWearQti+AtuwkDcwiQ9UuPg9xRiaearNFCG1ZPNayy+W7J
         ygKA==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:date:message-id:mime-version:subject:from:to:cc;
        bh=ySDv4Th435kjZfIwnmzgb5838RmbvDKzzPxK4jBsLsU=;
        b=YXaiwT74n1tneuUru1X8RsxBtv11KiHaubiFu10Acu8ayL91VEFg6tbWehcefrQPP5
         sfL3oI50vBt+qur8X2bH8RvZoo9ePC7MNrxw0YVuMfyalUbPsjALQG6mkG9OqNOzPnwv
         mCZlL+eyaZx3LxeCVuvoaf60PCn1MfZoxfvkfRlNLKxnnkBr4ahDnE3UqaLw8Y/WmqI6
         5GGth5Kl0IVLZblQuSNo91z4Y9OOQh42xf+UdZC36Jiy9JBuJnB/ok5oRLbkg81zGIFE
         F1WrHfHXNUmZlU3TxBQKkIPp1Da/iIOvxK01Rcjhj4L+fFa1N6+luhOGO8y4McicufTV
         RljA==
X-Gm-Message-State: AOAM531Pbxzb5iHuaz+mtgsoHrFSQmXGjRBq9/NUsFux0p0UlEoFZWty
        FMTfNaYvLUwkodRhnPFQWyE8GO2sq8aVgsOhH+huUdxlA1GC8KthPmLy0U0IPEPZqVZCtyE3tOj
        oALh01TgMqvgyXkExIZv1fHFEXDH+FGIlb7XKRdYTmlmhNtyddpqJVwCJPkEdyDI=
X-Google-Smtp-Source: 
 ABdhPJyvvvIenxzYMnKY4dpiQUWUd3D0rp+S8jZs1BeppjQ+zOgXJqyaFomIJEa14r57YQZUynMj3LBNAt5PRw==
X-Received: from dmatlack-heavy.c.googlers.com
 ([fda3:e722:ac3:10:7f:e700:c0a8:19cd])
 (user=dmatlack job=sendgmr) by 2002:a0c:f603:: with SMTP id
 r3mr31194684qvm.59.1620764483054; Tue, 11 May 2021 13:21:23 -0700 (PDT)
Date: Tue, 11 May 2021 20:21:20 +0000
Message-Id: <20210511202120.1371800-1-dmatlack@google.com>
Mime-Version: 1.0
X-Mailer: git-send-email 2.31.1.607.g51e8a6a459-goog
Subject: [PATCH v4] KVM: selftests: Print a message if /dev/kvm is missing
From: David Matlack <dmatlack@google.com>
To: kvm@vger.kernel.org
Cc: Paolo Bonzini <pbonzini@redhat.com>,
        Andrew Jones <drjones@redhat.com>,
        Aaron Lewis <aaronlewis@google.com>,
        David Matlack <dmatlack@google.com>
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

If a KVM selftest is run on a machine without /dev/kvm, it will exit
silently. Make it easy to tell what's happening by printing an error
message.

Opportunistically consolidate all codepaths that open /dev/kvm into a
single function so they all print the same message.

This slightly changes the semantics of vm_is_unrestricted_guest() by
changing a TEST_ASSERT() to exit(KSFT_SKIP). However
vm_is_unrestricted_guest() is only called in one place
(x86_64/mmio_warning_test.c) and that is to determine if the test should
be skipped or not.

Signed-off-by: David Matlack <dmatlack@google.com>
---
 .../testing/selftests/kvm/include/kvm_util.h  |  1 +
 tools/testing/selftests/kvm/lib/kvm_util.c    | 45 +++++++++++++------
 .../selftests/kvm/lib/x86_64/processor.c      | 16 ++-----
 .../kvm/x86_64/get_msr_index_features.c       |  8 +---
 4 files changed, 38 insertions(+), 32 deletions(-)

```
#### [PATCH v6 1/3] vfio-ccw: Check initialized flag in cp_init()
##### From: Eric Farman <farman@linux.ibm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Eric Farman <farman@linux.ibm.com>
X-Patchwork-Id: 12251993
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.8 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT
	autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 03FACC43462
	for <kvm@archiver.kernel.org>; Tue, 11 May 2021 19:56:46 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id D0CF3611C1
	for <kvm@archiver.kernel.org>; Tue, 11 May 2021 19:56:45 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S229973AbhEKT5v (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 11 May 2021 15:57:51 -0400
Received: from mx0a-001b2d01.pphosted.com ([148.163.156.1]:58282 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S229716AbhEKT5u (ORCPT
        <rfc822;kvm@vger.kernel.org>); Tue, 11 May 2021 15:57:50 -0400
Received: from pps.filterd (m0098409.ppops.net [127.0.0.1])
        by mx0a-001b2d01.pphosted.com (8.16.0.43/8.16.0.43) with SMTP id
 14BJX9WQ187435;
        Tue, 11 May 2021 15:56:43 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=ibm.com;
 h=from : to : cc : subject
 : date : message-id : in-reply-to : references : mime-version :
 content-transfer-encoding; s=pp1;
 bh=6Ji2N+g5BEfEKgFOPSitgWqnRCwc0MS0b5j0S+cgxRA=;
 b=nKZDvavjx0xkDejKD85V0i7DLKZWzCaqxPQOF0RG3/okgPSMzJjRIXV9XE1uMR13u8rs
 E5+TX4BJX5epoij2VSKgKnyUw5dPK2CwqYwUt24aV1c4dd4fnB393BNDxSoQBV2Uk3Ds
 sz+j2rRXukEPqqdMq4vM4BO/pz4toulSfloBc3lot/UIuIX07167bGbHUkXGzQDTj5r6
 x4XmTlO6WuqJ2pIaxzWsPMkOjSntNPDV2AqlaWq3vgwr77RHx7D5WWgRaPzSxdZUU3w4
 dbYfgryHf4T8IfpwCki8OxbnplDylJWnbDnQhf70dZNvnqp0IGhPq7np6JdtyQEIYFJk dw==
Received: from pps.reinject (localhost [127.0.0.1])
        by mx0a-001b2d01.pphosted.com with ESMTP id 38fyke9ewm-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Tue, 11 May 2021 15:56:43 -0400
Received: from m0098409.ppops.net (m0098409.ppops.net [127.0.0.1])
        by pps.reinject (8.16.0.43/8.16.0.43) with SMTP id 14BJmcGq065396;
        Tue, 11 May 2021 15:56:43 -0400
Received: from ppma06ams.nl.ibm.com (66.31.33a9.ip4.static.sl-reverse.com
 [169.51.49.102])
        by mx0a-001b2d01.pphosted.com with ESMTP id 38fyke9evh-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Tue, 11 May 2021 15:56:42 -0400
Received: from pps.filterd (ppma06ams.nl.ibm.com [127.0.0.1])
        by ppma06ams.nl.ibm.com (8.16.0.43/8.16.0.43) with SMTP id
 14BJmXMt011228;
        Tue, 11 May 2021 19:56:40 GMT
Received: from b06cxnps3074.portsmouth.uk.ibm.com
 (d06relay09.portsmouth.uk.ibm.com [9.149.109.194])
        by ppma06ams.nl.ibm.com with ESMTP id 38dhwh9ubg-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Tue, 11 May 2021 19:56:40 +0000
Received: from b06wcsmtp001.portsmouth.uk.ibm.com
 (b06wcsmtp001.portsmouth.uk.ibm.com [9.149.105.160])
        by b06cxnps3074.portsmouth.uk.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id 14BJub6926476904
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Tue, 11 May 2021 19:56:37 GMT
Received: from b06wcsmtp001.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id B470AA4064;
        Tue, 11 May 2021 19:56:37 +0000 (GMT)
Received: from b06wcsmtp001.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id A19D5A405F;
        Tue, 11 May 2021 19:56:37 +0000 (GMT)
Received: from tuxmaker.boeblingen.de.ibm.com (unknown [9.152.85.9])
        by b06wcsmtp001.portsmouth.uk.ibm.com (Postfix) with ESMTPS;
        Tue, 11 May 2021 19:56:37 +0000 (GMT)
Received: by tuxmaker.boeblingen.de.ibm.com (Postfix, from userid 4958)
        id 5CC1DE0369; Tue, 11 May 2021 21:56:32 +0200 (CEST)
From: Eric Farman <farman@linux.ibm.com>
To: Cornelia Huck <cohuck@redhat.com>,
        Matthew Rosato <mjrosato@linux.ibm.com>,
        Halil Pasic <pasic@linux.ibm.com>
Cc: Jared Rossi <jrossi@linux.ibm.com>, linux-s390@vger.kernel.org,
        kvm@vger.kernel.org, Eric Farman <farman@linux.ibm.com>
Subject: [PATCH v6 1/3] vfio-ccw: Check initialized flag in cp_init()
Date: Tue, 11 May 2021 21:56:29 +0200
Message-Id: <20210511195631.3995081-2-farman@linux.ibm.com>
X-Mailer: git-send-email 2.25.1
In-Reply-To: <20210511195631.3995081-1-farman@linux.ibm.com>
References: <20210511195631.3995081-1-farman@linux.ibm.com>
MIME-Version: 1.0
X-TM-AS-GCONF: 00
X-Proofpoint-ORIG-GUID: C8_8_6tvji8GkULHofeINhOCWr6zPq6q
X-Proofpoint-GUID: Qpivyg11w_ssSyxti82dlSJanEYrTAY8
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.391,18.0.761
 definitions=2021-05-11_04:2021-05-11,2021-05-11 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 priorityscore=1501
 suspectscore=0 lowpriorityscore=0 phishscore=0 malwarescore=0 adultscore=0
 impostorscore=0 mlxscore=0 spamscore=0 bulkscore=0 mlxlogscore=999
 clxscore=1015 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.12.0-2104190000 definitions=main-2105110130
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
Reviewed-by: Cornelia Huck <cohuck@redhat.com>
Acked-by: Matthew Rosato <mjrosato@linux.ibm.com>
---
 drivers/s390/cio/vfio_ccw_cp.c | 4 ++++
 1 file changed, 4 insertions(+)

```
