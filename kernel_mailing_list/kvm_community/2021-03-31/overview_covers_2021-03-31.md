

#### [PATCH 0/2] KVM: x86/mmu: TDP MMU fixes/cleanups
##### From: Sean Christopherson <seanjc@google.com>

```c
From patchwork Wed Mar 31 00:49:40 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Sean Christopherson <seanjc@google.com>
X-Patchwork-Id: 12174037
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-21.3 required=3.0 tests=BAYES_00,DKIMWL_WL_MED,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT,
	USER_IN_DEF_DKIM_WL autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 63FA9C433C1
	for <kvm@archiver.kernel.org>; Wed, 31 Mar 2021 00:50:36 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 23DB7619CA
	for <kvm@archiver.kernel.org>; Wed, 31 Mar 2021 00:50:36 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S232644AbhCaAuA (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 30 Mar 2021 20:50:00 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:38394 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S230145AbhCaAtq (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 30 Mar 2021 20:49:46 -0400
Received: from mail-yb1-xb49.google.com (mail-yb1-xb49.google.com
 [IPv6:2607:f8b0:4864:20::b49])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 63507C061574
        for <kvm@vger.kernel.org>; Tue, 30 Mar 2021 17:49:46 -0700 (PDT)
Received: by mail-yb1-xb49.google.com with SMTP id k189so457217ybb.17
        for <kvm@vger.kernel.org>; Tue, 30 Mar 2021 17:49:46 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=reply-to:date:message-id:mime-version:subject:from:to:cc;
        bh=Ip90cd5DdBRO62D8M6ZdfnlkzPDNszJ/oEbwkGCs1tg=;
        b=ZSiT5suIbZXzuUXW/ufGTEQldjuDOY+jEb5yoim4jvJqVl3cIhyTMFcRguKnCrpyMI
         HVhT8iLmAIiJ5q+4LBIDFKH0JGVFKRzHlgl+uGrFFJ/n2TQMGVMLDkDmUrcF7Rp9Lq7o
         i784pm7VONI/3PDPav0rW1nBRJS5y+ztBxfY4l8GSx0pXM570e132nE+GpkVJGB/NzOX
         LJJEfIyYUpAvhIt5pAbjweYLLaMWUDBInsPKEqCzzGKUDIvsmqiG1Xv1kfPv6/LuAELS
         /09TjUNlHVio3ystjVBncTZr2wlGv/QDqxdz69RIWmwNNy7t8elqVzultOkOX1hWRkE/
         pQmQ==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:reply-to:date:message-id:mime-version:subject
         :from:to:cc;
        bh=Ip90cd5DdBRO62D8M6ZdfnlkzPDNszJ/oEbwkGCs1tg=;
        b=TJE4SBeLAwUc8GU8qYWi0fAeZrhAzwjENbaUAq63hAEyTsSvdZe7Qlq8xQGuUApyOI
         pfR3Btc/BfQRR+g3ymnZ/sElAkuvzt71pOohXWXaiKYJHhxH3rUB719dLS4zqpnAdUrN
         VUl1TVMt6LtnuTlBg/JdApGl2xywWUDMpeT+Fm31+qtBszn1Ze9ZEc0TBr3kDx25yDxG
         cUCj66EWxGwr+NPwvAzTJvq7kPDLJmKhKuPmlJzyhuv4W3M2q1eF+rbPWpVkCzYsBcQv
         rH1UCwajvB295IDTm2n6x8waivFET8A0bpgP4lgH8pPiU777LijNs+bGOeRSwzskEQRi
         WcIA==
X-Gm-Message-State: AOAM530kbEqq4jh8+FA8qvAzgA7aaCLMuZa/vobOI7CjbL5kwkIOGoMI
        g367/P/os7Xj9ElhWaXwoDjFmmlAcD8=
X-Google-Smtp-Source: 
 ABdhPJwCFwgSSFL1i7mtqQeLTyQ0J7GlYsbA2OnjWvAxXWS3Y/mD7bH8msEh6JThZU0ztBb03MLhIKtrMcA=
X-Received: from seanjc798194.pdx.corp.google.com
 ([2620:15c:f:10:6c6b:5d63:9b3b:4a77])
 (user=seanjc job=sendgmr) by 2002:a25:483:: with SMTP id
 125mr1180394ybe.368.1617151785514;
 Tue, 30 Mar 2021 17:49:45 -0700 (PDT)
Reply-To: Sean Christopherson <seanjc@google.com>
Date: Tue, 30 Mar 2021 17:49:40 -0700
Message-Id: <20210331004942.2444916-1-seanjc@google.com>
Mime-Version: 1.0
X-Mailer: git-send-email 2.31.0.291.g576ba9dcdaf-goog
Subject: [PATCH 0/2] KVM: x86/mmu: TDP MMU fixes/cleanups
From: Sean Christopherson <seanjc@google.com>
To: Paolo Bonzini <pbonzini@redhat.com>
Cc: Sean Christopherson <seanjc@google.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org, Ben Gardon <bgardon@google.com>
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Two minor fixes/cleanups for the TDP MMU, found by inspection.

Sean Christopherson (2):
  KVM: x86/mmu: Remove spurious clearing of dirty bit from TDP MMU SPTE
  KVM: x86/mmu: Simplify code for aging SPTEs in TDP MMU

 arch/x86/kvm/mmu/tdp_mmu.c | 6 ++----
 1 file changed, 2 insertions(+), 4 deletions(-)
```
#### [PATCH 0/2] KVM: Fix missing GFP_KERNEL_ACCOUNT usage
##### From: Sean Christopherson <seanjc@google.com>

```c
From patchwork Wed Mar 31 02:30:23 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Sean Christopherson <seanjc@google.com>
X-Patchwork-Id: 12174153
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-21.3 required=3.0 tests=BAYES_00,DKIMWL_WL_MED,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT,
	USER_IN_DEF_DKIM_WL autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id BAA2BC433C1
	for <kvm@archiver.kernel.org>; Wed, 31 Mar 2021 02:31:34 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 8D2B3619C1
	for <kvm@archiver.kernel.org>; Wed, 31 Mar 2021 02:31:34 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S233117AbhCaCbB (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 30 Mar 2021 22:31:01 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:59894 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S230284AbhCaCa3 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 30 Mar 2021 22:30:29 -0400
Received: from mail-yb1-xb4a.google.com (mail-yb1-xb4a.google.com
 [IPv6:2607:f8b0:4864:20::b4a])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 5D4FEC061574
        for <kvm@vger.kernel.org>; Tue, 30 Mar 2021 19:30:29 -0700 (PDT)
Received: by mail-yb1-xb4a.google.com with SMTP id d1so679547ybj.15
        for <kvm@vger.kernel.org>; Tue, 30 Mar 2021 19:30:29 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=reply-to:date:message-id:mime-version:subject:from:to:cc;
        bh=gQCuwGLAfsbw/UNMTMJ5GJMFsizewCkNOypdYowqK48=;
        b=wSryiJNO0/HtB5GXTbVL00PPqna6O7GlK+7E34vVtFEfl/ee5FOWHf36YgIP+5Kthy
         pcea+iq0lPtzOiZN1WlKxV81tK+ZNbYmP5nv2I6GpglqgMLax8hw7w0M6lLKSAXSVFZb
         Tv13wHHoE5JHQ3mUOnZRugmnalesT78gxOj/lkw0Amx4xiVXUSzHNaJ2XTEpFmk3+oqL
         S5cBspBO1WxvwGZnZS+WTiR7kCQR0a0SXT9N/RCNQIwnW9d0mWn0nvXrh6AvFhPkcLZd
         NaS1qsXm02OE9DfD3en6WKSs6Gqh0Syj+o8cTsw5AuKSaP5Oroc7NQORIsb047C4z0NL
         lItg==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:reply-to:date:message-id:mime-version:subject
         :from:to:cc;
        bh=gQCuwGLAfsbw/UNMTMJ5GJMFsizewCkNOypdYowqK48=;
        b=loSwDBnq3s25smJfYby/mQMdCe0Z2UmV6+JQ08hc2OJNM3AZw0DYhWY88QUzxNMbGG
         TBKyv5iZlPa3BzU8pyKu/16ICiIAGdp5f0M8Jgwl5R830kNdZjvzmIfhm9mYo3Fu0WUT
         DiE/CP49RrTA9UMPzo6sdAbH+ZFZmwEtuCFyXttqWhHUwDSqOAPDorCMLxArTku+scJU
         No3u62Z+uGrk5sZpkTdDHek7ZbdN5Fursxjocp+o4SMuu4JfIFgfcvfa7EW+4BAmbUZQ
         1mp+mqrUfz89UlZvHPkEAz/9lB63lkXuvLLbVbqJ8TEQ4Ogy6W2PGvOiULJoM7UF/qfT
         kQiQ==
X-Gm-Message-State: AOAM532FBe0TwxAzqplGGNyKPCnBATOHU2A9Qx/G/wHJ5SWRDIdtL6ha
        ZRLIrX3aX+/URDMsUDCv2qLa/T1DX/k=
X-Google-Smtp-Source: 
 ABdhPJzIBEctIXJVpThNi6OlflzTn7FgBN15h3E04Il0jjJ+PmqaPLPHYW1WqIwC6phByJXcquT8AMP5OvE=
X-Received: from seanjc798194.pdx.corp.google.com
 ([2620:15c:f:10:6c6b:5d63:9b3b:4a77])
 (user=seanjc job=sendgmr) by 2002:a25:ce13:: with SMTP id
 x19mr1522852ybe.235.1617157828611;
 Tue, 30 Mar 2021 19:30:28 -0700 (PDT)
Reply-To: Sean Christopherson <seanjc@google.com>
Date: Tue, 30 Mar 2021 19:30:23 -0700
Message-Id: <20210331023025.2485960-1-seanjc@google.com>
Mime-Version: 1.0
X-Mailer: git-send-email 2.31.0.291.g576ba9dcdaf-goog
Subject: [PATCH 0/2] KVM: Fix missing GFP_KERNEL_ACCOUNT usage
From: Sean Christopherson <seanjc@google.com>
To: Paolo Bonzini <pbonzini@redhat.com>
Cc: Sean Christopherson <seanjc@google.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Fix (almost) all cases in KVM x86 where allocations that are tied to a           
task/VM are not correctly accounted.                                            
                                                                                
There are a handful of allocations in SEV code that I intentionally didn't
fix in this series.  I'm 95% certain those allocations can be eliminated
completely, changing them in this series only to delete them seemed
pointless.

The allocations in questions are for structs that are used to communicate
 with the PSP; they are temporary (freed in the same function that does
the allocation) and small (some are _tiny_, e.g. 4 bytes).   AFAICT, the
sole reason they are dynamically allocated is because the CCP driver uses
__pa() to retrieve the physical address that is passed to the PSP, and
__pa() does not work for vmalloc'd memory, which is in play when running
with CONFIG_VMAP_STACKS=y.  

I have functional code that uses a scratch buffer as a bounce buffer to
cleanly handle vmalloc'd memory in the CCP driver.  I'll hopefully get
that posted tomorrow.

Sean Christopherson (2):
  KVM: Account memory allocations for 'struct kvm_vcpu'
  KVM: x86: Account a variety of miscellaneous allocations

 arch/x86/kvm/svm/nested.c | 4 ++--
 arch/x86/kvm/svm/sev.c    | 6 +++---
 arch/x86/kvm/vmx/vmx.c    | 2 +-
 virt/kvm/kvm_main.c       | 2 +-
 4 files changed, 7 insertions(+), 7 deletions(-)
```
#### [PATCH 0/3] KVM: SVM: SEV{-ES} bug fixes
##### From: Sean Christopherson <seanjc@google.com>

```c
From patchwork Wed Mar 31 03:19:33 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Sean Christopherson <seanjc@google.com>
X-Patchwork-Id: 12174259
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-21.3 required=3.0 tests=BAYES_00,DKIMWL_WL_MED,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT,
	USER_IN_DEF_DKIM_WL autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id AC67BC433C1
	for <kvm@archiver.kernel.org>; Wed, 31 Mar 2021 03:20:19 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 63310619A7
	for <kvm@archiver.kernel.org>; Wed, 31 Mar 2021 03:20:19 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S233067AbhCaDTs (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 30 Mar 2021 23:19:48 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:42326 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S233305AbhCaDTo (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 30 Mar 2021 23:19:44 -0400
Received: from mail-qt1-x84a.google.com (mail-qt1-x84a.google.com
 [IPv6:2607:f8b0:4864:20::84a])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 87A3AC061574
        for <kvm@vger.kernel.org>; Tue, 30 Mar 2021 20:19:43 -0700 (PDT)
Received: by mail-qt1-x84a.google.com with SMTP id c20so393212qtw.9
        for <kvm@vger.kernel.org>; Tue, 30 Mar 2021 20:19:43 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=reply-to:date:message-id:mime-version:subject:from:to:cc;
        bh=sOb7NEJl+AeolkpzxTyofNZTvUzELB1nvc8i4lV36jE=;
        b=Zqz0CV+RXQXP0rMDlz3xJUcyTKSY1zFb9tXpomz40KtHRTkLeBkZVgwftostW065T7
         pooHfG4ZqWULR3W+CVG+y3i+Dar99SHYWQ80D9CjKZDArcuVduSZe8nQxWUtzCSoid1l
         x4Bn0G8xXyYA7Dj6D1cIeA8CfDiBE2Le80GmG76I+RUSoHXupjZhP8RmtabpOY7K9BVh
         OnRAxvs5NivcMBNjNDCqWS/l6x3c1aV9OG4HCkbHFGlTqaiQedolTVpG8bdD+MCYcDfh
         XG7I/yLHfw36ZrJADjl2cOe5NZhehs2d/wx9XXCDgYicJ8mpBsK/Yvu7afXKorV/DPfv
         eDyg==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:reply-to:date:message-id:mime-version:subject
         :from:to:cc;
        bh=sOb7NEJl+AeolkpzxTyofNZTvUzELB1nvc8i4lV36jE=;
        b=XZWXwBmZXdp2zuKLwBfDLklEiDGwoRTD/VG0iX/BHI7XDZDduJwFtD85wwL0PwJzip
         nTM/r6+RKavAC+M+RaqhvC1F+6o4cPWsbypa0wng6BL7yjrZXiwjpYrH7CfUOhXiluyx
         xiD9zkvn/TUh6whisEVi4Td0fTrUqOlO/AgpUksXc/z524A9nL4UieQHhnNPMf7wKNMA
         dQ9DvlQUhegOd9FXEtBHE6ylg5eoWcbxI6ZQ3sW/D6RtFguf6s0a/EyPDZIXoaoQCtwE
         Cf/TuJIWEP1l82l8/eLEzVXBudL7qGZIr/AsVa8NPxReQtc+LPK21eq4CwG1tTzhyOdf
         yayg==
X-Gm-Message-State: AOAM5336iAfvvG+UPVuyC+NRHeE5q0x/i/5c6OZ+pjJZPQpcFgfzewGE
        xhQrKSvuUZFFLl5JVIxnjPoagKJr2ps=
X-Google-Smtp-Source: 
 ABdhPJzE5U8A8ThHZ+AOEEXZHsflheOnyjBhFkAVDOvh8sw/PKf8FDxFaU8+8WBEldeAhey6VoOuVnLoxnE=
X-Received: from seanjc798194.pdx.corp.google.com
 ([2620:15c:f:10:6c6b:5d63:9b3b:4a77])
 (user=seanjc job=sendgmr) by 2002:a0c:9e0f:: with SMTP id
 p15mr1222038qve.27.1617160782533;
 Tue, 30 Mar 2021 20:19:42 -0700 (PDT)
Reply-To: Sean Christopherson <seanjc@google.com>
Date: Tue, 30 Mar 2021 20:19:33 -0700
Message-Id: <20210331031936.2495277-1-seanjc@google.com>
Mime-Version: 1.0
X-Mailer: git-send-email 2.31.0.291.g576ba9dcdaf-goog
Subject: [PATCH 0/3] KVM: SVM: SEV{-ES} bug fixes
From: Sean Christopherson <seanjc@google.com>
To: Paolo Bonzini <pbonzini@redhat.com>
Cc: Sean Christopherson <seanjc@google.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org,
        Brijesh Singh <brijesh.singh@amd.com>,
        Tom Lendacky <thomas.lendacky@amd.com>
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Misc bug fixes in SEV/SEV-ES to protect against a malicious userspace.
All found by inspection, I didn't actually crash the host to to prove that
userspace could hose the kernel in any of these cases.  Boot tested an SEV
guest, though the SEV-ES side of patch 2 is essentially untested as I
don't have an SEV-ES setup at this time.

Sean Christopherson (3):
  KVM: SVM: Use online_vcpus, not created_vcpus, to iterate over vCPUs
  KVM: SVM: Do not set sev->es_active until KVM_SEV_ES_INIT completes
  KVM: SVM: Do not allow SEV/SEV-ES initialization after vCPUs are
    created

 arch/x86/kvm/svm/sev.c | 37 ++++++++++++++++++-------------------
 1 file changed, 18 insertions(+), 19 deletions(-)
```
#### [PATCH v6 00/10] Introduce VDUSE - vDPA Device in Userspace
##### From: Xie Yongji <xieyongji@bytedance.com>

```c
From patchwork Wed Mar 31 08:05:09 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Yongji Xie <xieyongji@bytedance.com>
X-Patchwork-Id: 12174633
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.8 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_PATCH,MAILING_LIST_MULTI,
	MENTIONS_GIT_HOSTING,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT
	autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 8A174C433DB
	for <kvm@archiver.kernel.org>; Wed, 31 Mar 2021 08:07:24 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 4BF73619D6
	for <kvm@archiver.kernel.org>; Wed, 31 Mar 2021 08:07:24 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S234282AbhCaIGs (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Wed, 31 Mar 2021 04:06:48 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:47338 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S233838AbhCaIGS (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 31 Mar 2021 04:06:18 -0400
Received: from mail-pj1-x102a.google.com (mail-pj1-x102a.google.com
 [IPv6:2607:f8b0:4864:20::102a])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 393A8C061574
        for <kvm@vger.kernel.org>; Wed, 31 Mar 2021 01:06:18 -0700 (PDT)
Received: by mail-pj1-x102a.google.com with SMTP id
 ot17-20020a17090b3b51b0290109c9ac3c34so749552pjb.4
        for <kvm@vger.kernel.org>; Wed, 31 Mar 2021 01:06:18 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=bytedance-com.20150623.gappssmtp.com; s=20150623;
        h=from:to:cc:subject:date:message-id:mime-version
         :content-transfer-encoding;
        bh=4N6n75HqbevIF9P31f/wL6cRPYdbdVgQRyq4EjDa+KI=;
        b=tCWBRhkJ+EMcbHANy2T6J/ODxrDT3eHPzebAt+W99iL0z7gvXjr48gyg9qUrY139C2
         5eDG6B4sUzPt56VJiOE+FaH1N17gORJp/oo5tKe3M7lzZFYVw/t7wciBddhPOnZOQWtC
         LAZWYSlVDKcL6rvBWxeTUjWw+l09aCIfcgzIqJ0TBjD7cNcXivLhdHyDcmIlDCB1GjYO
         L6CbDMLkz6QhZGZm3/4LTAWxrsNh6fb9y7Rmhvs5IDPTPwG+yBt6moLP2iWKVgLoDZSd
         EX0FqybXvVmaUAKcJcLct764h//QocjnI69D5oC1ZIUUcEwQcL0uGvx2/WZlUQ7zucjQ
         JNJw==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:mime-version
         :content-transfer-encoding;
        bh=4N6n75HqbevIF9P31f/wL6cRPYdbdVgQRyq4EjDa+KI=;
        b=CgvqK8+PSsNM0nZR16JA0PTp3rckM4JX4o5/T81G1edvpYDMGGlP4mpzsuN9NX6P80
         z7kRb9dQLVKhE6EKAg3fmsIlAwxCYPzvhuMLFpVMmH9BczOASu67SxO9ArQuyiMRDh/G
         5oqtNnbVPDcDImaW+PFreFxGa+P37hAZtUmunAyLB+7ukt9ESn2QVu8KfA0H9mlkQFoG
         e8a0bMnc8W35k3tHqpZ2ApHLv50I9Rp0c1x4Ge/izzhqMLriuk1MSqwLF8LOU3CDaZiu
         PsBP+JO6JmMLRj6KrBLDjhZqlGz+I6j++7CwJEo0kx/Uoh+9+5YSBWM2O+SINKxri01f
         GM4w==
X-Gm-Message-State: AOAM531WuS9KQVztEz3+UEkjPhP1QFxjQ6Apv6SpNO0xOCfqhbuSf52M
        e0TT65h6YFb/gKU/ctjIpeS+
X-Google-Smtp-Source: 
 ABdhPJwXQhHmzbJYidBqa/tnGY3/zsxMlrVA/10Pbl0dBxMOuwslgXGwHsV1vdv1saXvtLPHhYcpmQ==
X-Received: by 2002:a17:903:22c1:b029:e7:1f29:b848 with SMTP id
 y1-20020a17090322c1b02900e71f29b848mr2100012plg.53.1617177977718;
        Wed, 31 Mar 2021 01:06:17 -0700 (PDT)
Received: from localhost ([139.177.225.243])
        by smtp.gmail.com with ESMTPSA id
 a22sm1731081pgw.52.2021.03.31.01.06.16
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Wed, 31 Mar 2021 01:06:17 -0700 (PDT)
From: Xie Yongji <xieyongji@bytedance.com>
To: mst@redhat.com, jasowang@redhat.com, stefanha@redhat.com,
        sgarzare@redhat.com, parav@nvidia.com, hch@infradead.org,
        christian.brauner@canonical.com, rdunlap@infradead.org,
        willy@infradead.org, viro@zeniv.linux.org.uk, axboe@kernel.dk,
        bcrl@kvack.org, corbet@lwn.net, mika.penttila@nextfour.com,
        dan.carpenter@oracle.com
Cc: virtualization@lists.linux-foundation.org, netdev@vger.kernel.org,
        kvm@vger.kernel.org, linux-fsdevel@vger.kernel.org
Subject: [PATCH v6 00/10] Introduce VDUSE - vDPA Device in Userspace
Date: Wed, 31 Mar 2021 16:05:09 +0800
Message-Id: <20210331080519.172-1-xieyongji@bytedance.com>
X-Mailer: git-send-email 2.25.1
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This series introduces a framework, which can be used to implement
vDPA Devices in a userspace program. The work consist of two parts:
control path forwarding and data path offloading.

In the control path, the VDUSE driver will make use of message
mechnism to forward the config operation from vdpa bus driver
to userspace. Userspace can use read()/write() to receive/reply
those control messages.

In the data path, the core is mapping dma buffer into VDUSE
daemon's address space, which can be implemented in different ways
depending on the vdpa bus to which the vDPA device is attached.

In virtio-vdpa case, we implements a MMU-based on-chip IOMMU driver with
bounce-buffering mechanism to achieve that. And in vhost-vdpa case, the dma
buffer is reside in a userspace memory region which can be shared to the
VDUSE userspace processs via transferring the shmfd.

The details and our user case is shown below:

------------------------    -------------------------   ----------------------------------------------
|            Container |    |              QEMU(VM) |   |                               VDUSE daemon |
|       ---------      |    |  -------------------  |   | ------------------------- ---------------- |
|       |dev/vdx|      |    |  |/dev/vhost-vdpa-x|  |   | | vDPA device emulation | | block driver | |
------------+-----------     -----------+------------   -------------+----------------------+---------
            |                           |                            |                      |
            |                           |                            |                      |
------------+---------------------------+----------------------------+----------------------+---------
|    | block device |           |  vhost device |            | vduse driver |          | TCP/IP |    |
|    -------+--------           --------+--------            -------+--------          -----+----    |
|           |                           |                           |                       |        |
| ----------+----------       ----------+-----------         -------+-------                |        |
| | virtio-blk driver |       |  vhost-vdpa driver |         | vdpa device |                |        |
| ----------+----------       ----------+-----------         -------+-------                |        |
|           |      virtio bus           |                           |                       |        |
|   --------+----+-----------           |                           |                       |        |
|                |                      |                           |                       |        |
|      ----------+----------            |                           |                       |        |
|      | virtio-blk device |            |                           |                       |        |
|      ----------+----------            |                           |                       |        |
|                |                      |                           |                       |        |
|     -----------+-----------           |                           |                       |        |
|     |  virtio-vdpa driver |           |                           |                       |        |
|     -----------+-----------           |                           |                       |        |
|                |                      |                           |    vdpa bus           |        |
|     -----------+----------------------+---------------------------+------------           |        |
|                                                                                        ---+---     |
-----------------------------------------------------------------------------------------| NIC |------
                                                                                         ---+---
                                                                                            |
                                                                                   ---------+---------
                                                                                   | Remote Storages |
                                                                                   -------------------

We make use of it to implement a block device connecting to
our distributed storage, which can be used both in containers and
VMs. Thus, we can have an unified technology stack in this two cases.

To test it with null-blk:

  $ qemu-storage-daemon \
      --chardev socket,id=charmonitor,path=/tmp/qmp.sock,server,nowait \
      --monitor chardev=charmonitor \
      --blockdev driver=host_device,cache.direct=on,aio=native,filename=/dev/nullb0,node-name=disk0 \
      --export type=vduse-blk,id=test,node-name=disk0,writable=on,name=vduse-null,num-queues=16,queue-size=128

The qemu-storage-daemon can be found at https://github.com/bytedance/qemu/tree/vduse

Future work:
  - Improve performance
  - Userspace library (find a way to reuse device emulation code in qemu/rust-vmm)

V5 to V6:
- Export receive_fd() instead of __receive_fd()
- Factor out the unmapping logic of pa and va separatedly
- Remove the logic of bounce page allocation in page fault handler
- Use PAGE_SIZE as IOVA allocation granule
- Add EPOLLOUT support
- Enable setting API version in userspace
- Fix some bugs

V4 to V5:
- Remove the patch for irq binding
- Use a single IOTLB for all types of mapping
- Factor out vhost_vdpa_pa_map()
- Add some sample codes in document
- Use receice_fd_user() to pass file descriptor
- Fix some bugs

V3 to V4:
- Rebase to vhost.git
- Split some patches
- Add some documents
- Use ioctl to inject interrupt rather than eventfd
- Enable config interrupt support
- Support binding irq to the specified cpu
- Add two module parameter to limit bounce/iova size
- Create char device rather than anon inode per vduse
- Reuse vhost IOTLB for iova domain
- Rework the message mechnism in control path

V2 to V3:
- Rework the MMU-based IOMMU driver
- Use the iova domain as iova allocator instead of genpool
- Support transferring vma->vm_file in vhost-vdpa
- Add SVA support in vhost-vdpa
- Remove the patches on bounce pages reclaim

V1 to V2:
- Add vhost-vdpa support
- Add some documents
- Based on the vdpa management tool
- Introduce a workqueue for irq injection
- Replace interval tree with array map to store the iova_map

Xie Yongji (10):
  file: Export receive_fd() to modules
  eventfd: Increase the recursion depth of eventfd_signal()
  vhost-vdpa: protect concurrent access to vhost device iotlb
  vhost-iotlb: Add an opaque pointer for vhost IOTLB
  vdpa: Add an opaque pointer for vdpa_config_ops.dma_map()
  vdpa: factor out vhost_vdpa_pa_map() and vhost_vdpa_pa_unmap()
  vdpa: Support transferring virtual addressing during DMA mapping
  vduse: Implement an MMU-based IOMMU driver
  vduse: Introduce VDUSE - vDPA Device in Userspace
  Documentation: Add documentation for VDUSE

 Documentation/userspace-api/index.rst              |    1 +
 Documentation/userspace-api/ioctl/ioctl-number.rst |    1 +
 Documentation/userspace-api/vduse.rst              |  212 +++
 drivers/vdpa/Kconfig                               |   10 +
 drivers/vdpa/Makefile                              |    1 +
 drivers/vdpa/ifcvf/ifcvf_main.c                    |    2 +-
 drivers/vdpa/mlx5/net/mlx5_vnet.c                  |    2 +-
 drivers/vdpa/vdpa.c                                |    9 +-
 drivers/vdpa/vdpa_sim/vdpa_sim.c                   |    8 +-
 drivers/vdpa/vdpa_user/Makefile                    |    5 +
 drivers/vdpa/vdpa_user/iova_domain.c               |  521 ++++++++
 drivers/vdpa/vdpa_user/iova_domain.h               |   70 +
 drivers/vdpa/vdpa_user/vduse_dev.c                 | 1362 ++++++++++++++++++++
 drivers/vdpa/virtio_pci/vp_vdpa.c                  |    2 +-
 drivers/vhost/iotlb.c                              |   20 +-
 drivers/vhost/vdpa.c                               |  154 ++-
 fs/eventfd.c                                       |    2 +-
 fs/file.c                                          |    6 +
 include/linux/eventfd.h                            |    5 +-
 include/linux/file.h                               |    7 +-
 include/linux/vdpa.h                               |   21 +-
 include/linux/vhost_iotlb.h                        |    3 +
 include/uapi/linux/vduse.h                         |  175 +++
 23 files changed, 2548 insertions(+), 51 deletions(-)
 create mode 100644 Documentation/userspace-api/vduse.rst
 create mode 100644 drivers/vdpa/vdpa_user/Makefile
 create mode 100644 drivers/vdpa/vdpa_user/iova_domain.c
 create mode 100644 drivers/vdpa/vdpa_user/iova_domain.h
 create mode 100644 drivers/vdpa/vdpa_user/vduse_dev.c
 create mode 100644 include/uapi/linux/vduse.h
```
#### [PATCH 0/4] kvm: cpuid: fix cpuid nent field
##### From: Emanuele Giuseppe Esposito <eesposit@redhat.com>

```c
From patchwork Wed Mar 31 12:26:45 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Emanuele Giuseppe Esposito <eesposit@redhat.com>
X-Patchwork-Id: 12175409
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-15.8 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_CR_TRAILER,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS
	autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 90D96C43462
	for <kvm@archiver.kernel.org>; Wed, 31 Mar 2021 12:34:15 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 7B3BC619CA
	for <kvm@archiver.kernel.org>; Wed, 31 Mar 2021 12:27:41 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S235427AbhCaM1K (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Wed, 31 Mar 2021 08:27:10 -0400
Received: from us-smtp-delivery-124.mimecast.com ([63.128.21.124]:49902 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S235544AbhCaM1C (ORCPT
        <rfc822;kvm@vger.kernel.org>); Wed, 31 Mar 2021 08:27:02 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1617193621;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=w05Yiprz2DAkrl/VfB1KsTtz5xzVGlEVY+yQ28kxkrM=;
        b=SIY+dSUAvGt0j89PWIWggTmaD1IvkQel7beacsv5iwhu6Uf+Qjp2+qxsm1HzTFNBXydSyu
        2EXBKgJCzOzJMGjML7+sCIuxUE0mJLNj2Lqawourzkez/MDrMqj8F9uj34yNLkDzmTQZPA
        MGrd/c0gNtdfCoe3Qa2lulGTyhI1Uxc=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-492-jZzSQNsxMoaIKLo1-3Tg7A-1; Wed, 31 Mar 2021 08:26:59 -0400
X-MC-Unique: jZzSQNsxMoaIKLo1-3Tg7A-1
Received: from smtp.corp.redhat.com (int-mx02.intmail.prod.int.phx2.redhat.com
 [10.5.11.12])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 8B5191018F7D;
        Wed, 31 Mar 2021 12:26:57 +0000 (UTC)
Received: from localhost.localdomain.com (ovpn-114-218.ams2.redhat.com
 [10.36.114.218])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 3C04FB23E1;
        Wed, 31 Mar 2021 12:26:52 +0000 (UTC)
From: Emanuele Giuseppe Esposito <eesposit@redhat.com>
To: kvm@vger.kernel.org
Cc: Paolo Bonzini <pbonzini@redhat.com>,
        Jonathan Corbet <corbet@lwn.net>,
        Sean Christopherson <seanjc@google.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Jim Mattson <jmattson@google.com>,
        Ingo Molnar <mingo@redhat.com>, Borislav Petkov <bp@alien8.de>,
        "H. Peter Anvin" <hpa@zytor.com>, Shuah Khan <shuah@kernel.org>,
        Alexander Graf <graf@amazon.com>,
        Andrew Jones <drjones@redhat.com>, linux-doc@vger.kernel.org,
        linux-kernel@vger.kernel.org, linux-kselftest@vger.kernel.org
Subject: [PATCH 0/4] kvm: cpuid: fix cpuid nent field
Date: Wed, 31 Mar 2021 14:26:45 +0200
Message-Id: <20210331122649.38323-1-eesposit@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.12
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This series aims to clarify the behavior of 
KVM_GET_EMULATED_CPUID and KVM_GET_SUPPORTED
ioctls, and fix a corner case where the nent field of the
struct kvm_cpuid2 is matching the amount of entries that kvm returns.

Patch 1 proposes the nent field fix to cpuid.c,
patch 2 updates the ioctl documentation accordingly and 
patches 3 and 4 provide a selftest to check KVM_GET_EMULATED_CPUID
accordingly.

Signed-off-by: Emanuele Giuseppe Esposito <eesposit@redhat.com>
---
v2:
- better fix in cpuid.c, perform the nent check after the switch statement 
- fix bug in get_emulated_cpuid.c selftest, each entry needs to have at least
  the padding zeroed otherwise it fails.

Emanuele Giuseppe Esposito (4):
  kvm: cpuid: adjust the returned nent field of kvm_cpuid2 for
    KVM_GET_SUPPORTED_CPUID and KVM_GET_EMULATED_CPUID
  Documentation: kvm: update KVM_GET_EMULATED_CPUID ioctl description
  selftests: add kvm_get_emulated_cpuid
  selftests: kvm: add get_emulated_cpuid test

 Documentation/virt/kvm/api.rst                |  10 +-
 arch/x86/kvm/cpuid.c                          |  35 ++--
 tools/testing/selftests/kvm/.gitignore        |   1 +
 tools/testing/selftests/kvm/Makefile          |   1 +
 .../selftests/kvm/include/x86_64/processor.h  |   1 +
 .../selftests/kvm/lib/x86_64/processor.c      |  33 +++
 .../selftests/kvm/x86_64/get_emulated_cpuid.c | 198 ++++++++++++++++++
 7 files changed, 256 insertions(+), 23 deletions(-)
 create mode 100644 tools/testing/selftests/kvm/x86_64/get_emulated_cpuid.c
```
#### [PATCH v3 0/2] KVM: x86: hyper-v: Fix TSC page update after
##### From: Vitaly Kuznetsov <vkuznets@redhat.com>

```c
From patchwork Wed Mar 31 12:41:28 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Vitaly Kuznetsov <vkuznets@redhat.com>
X-Patchwork-Id: 12175417
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-10.8 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS autolearn=ham
	autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 80A86C433B4
	for <kvm@archiver.kernel.org>; Wed, 31 Mar 2021 12:42:14 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 301726191D
	for <kvm@archiver.kernel.org>; Wed, 31 Mar 2021 12:42:14 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S235595AbhCaMll (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Wed, 31 Mar 2021 08:41:41 -0400
Received: from us-smtp-delivery-124.mimecast.com ([63.128.21.124]:59744 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S235607AbhCaMlj (ORCPT
        <rfc822;kvm@vger.kernel.org>); Wed, 31 Mar 2021 08:41:39 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1617194499;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=IdSm0cCmMirXzthvLuhUlAlHbcDycfb8nBgHo5E0Cf8=;
        b=YMekVIpMuaZdSQbHi7WlfpZvDnyIbzaiC+hctC+X2WLd2LUPLaEtXlxcoIESoTSGw7xDai
        SwGhp/yLEvy+B+rrAZmDpkFtANqE3FczRNnlwcSBnpz3MoE3Ee6W4rHFss0vFHgUTTFfMp
        v6KOxRfm0sI75Er/fOyY5/Q9wNMLvPc=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-502--Y7f6qVWM6mOYwQULFFmgQ-1; Wed, 31 Mar 2021 08:41:36 -0400
X-MC-Unique: -Y7f6qVWM6mOYwQULFFmgQ-1
Received: from smtp.corp.redhat.com (int-mx03.intmail.prod.int.phx2.redhat.com
 [10.5.11.13])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 069DE807907;
        Wed, 31 Mar 2021 12:41:35 +0000 (UTC)
Received: from vitty.brq.redhat.com (unknown [10.40.193.13])
        by smtp.corp.redhat.com (Postfix) with ESMTP id EBC0D60861;
        Wed, 31 Mar 2021 12:41:31 +0000 (UTC)
From: Vitaly Kuznetsov <vkuznets@redhat.com>
To: kvm@vger.kernel.org, Paolo Bonzini <pbonzini@redhat.com>
Cc: Sean Christopherson <seanjc@google.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Marcelo Tosatti <mtosatti@redhat.com>,
        linux-kernel@vger.kernel.org
Subject: [PATCH v3 0/2] KVM: x86: hyper-v: Fix TSC page update after
 KVM_SET_CLOCK(0) call
Date: Wed, 31 Mar 2021 14:41:28 +0200
Message-Id: <20210331124130.337992-1-vkuznets@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.13
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Changes since v2:
- Fix the issue by using master_kernel_ns/get_kvmclock_base_ns() instead of
 get_kvmclock_ns() when handling KVM_SET_CLOCK.
- Rebase on Paolo's "KVM: x86: fix lockdep splat due to Xen runstate
 update" series and use spin_lock_irq()/spin_unlock_irq() [Paolo]

Original description:

I discovered that after KVM_SET_CLOCK(0) TSC page value in the guest can
go through the roof and apparently we have a signedness issue when the
update is performed. Fix the issue and add a selftest.

Vitaly Kuznetsov (2):
  KVM: x86: Prevent 'hv_clock->system_time' from going negative in
    kvm_guest_time_update()
  selftests: kvm: Check that TSC page value is small after
    KVM_SET_CLOCK(0)

 arch/x86/kvm/x86.c                            | 19 +++++++++++++++++--
 .../selftests/kvm/x86_64/hyperv_clock.c       | 13 +++++++++++--
 2 files changed, 28 insertions(+), 4 deletions(-)
```
#### [PATCH v14 00/13] s390/vfio-ap: dynamic configuration support
##### From: Tony Krowiak <akrowiak@linux.ibm.com>

```c
From patchwork Wed Mar 31 15:22:43 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Tony Krowiak <akrowiak@linux.ibm.com>
X-Patchwork-Id: 12175585
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-11.8 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_PATCH,MAILING_LIST_MULTI,
	SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT autolearn=unavailable
	autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 81987C43462
	for <kvm@archiver.kernel.org>; Wed, 31 Mar 2021 15:23:59 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 4D6D660725
	for <kvm@archiver.kernel.org>; Wed, 31 Mar 2021 15:23:59 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S236270AbhCaPX0 (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Wed, 31 Mar 2021 11:23:26 -0400
Received: from mx0a-001b2d01.pphosted.com ([148.163.156.1]:2746 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S236182AbhCaPXQ (ORCPT
        <rfc822;kvm@vger.kernel.org>); Wed, 31 Mar 2021 11:23:16 -0400
Received: from pps.filterd (m0098394.ppops.net [127.0.0.1])
        by mx0a-001b2d01.pphosted.com (8.16.0.43/8.16.0.43) with SMTP id
 12VF3Qqp144821;
        Wed, 31 Mar 2021 11:23:15 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=ibm.com;
 h=from : to : cc : subject
 : date : message-id : mime-version : content-transfer-encoding; s=pp1;
 bh=HtmuzxrwlZ83u5Vawet621tqV2Rao0tpoYaAiGsG2Qg=;
 b=Xtl82l4LP8lEI92bZ7OEbD8p2VUMRHMoyyQOT25eSSBxLXbIBcuSgmnCIWqiHopUeo3J
 t3xAKi9Ta30o+5+dfTWg9ymCvs2H3Yf4GcwXodoFt2RYOO6zrL/QbqRHX8896YbTWwDx
 G5t39ZCZlzeML9tPQ6JiJMkFiOqp0r8Gdy/MvcO2LPKh+GGu3sxAS65+X0JXN0qVUHWy
 HmKqPqGz8thyYpQNPL9m540G2WJ2ChFcG7Ix/7WgiOaN82gP75YSH6wySb3/JTXGe0EV
 5L19GnqtXBNU/ddaH7y4HcX2eTGIpVby0TUFF54V5fzE1kTRnfALd8478pTqNesr89ns 1A==
Received: from pps.reinject (localhost [127.0.0.1])
        by mx0a-001b2d01.pphosted.com with ESMTP id 37mn0nvut9-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Wed, 31 Mar 2021 11:23:15 -0400
Received: from m0098394.ppops.net (m0098394.ppops.net [127.0.0.1])
        by pps.reinject (8.16.0.43/8.16.0.43) with SMTP id 12VFF8O3192469;
        Wed, 31 Mar 2021 11:23:14 -0400
Received: from ppma04wdc.us.ibm.com (1a.90.2fa9.ip4.static.sl-reverse.com
 [169.47.144.26])
        by mx0a-001b2d01.pphosted.com with ESMTP id 37mn0nvuss-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Wed, 31 Mar 2021 11:23:14 -0400
Received: from pps.filterd (ppma04wdc.us.ibm.com [127.0.0.1])
        by ppma04wdc.us.ibm.com (8.16.0.43/8.16.0.43) with SMTP id
 12VFMv4b031132;
        Wed, 31 Mar 2021 15:23:13 GMT
Received: from b03cxnp07028.gho.boulder.ibm.com
 (b03cxnp07028.gho.boulder.ibm.com [9.17.130.15])
        by ppma04wdc.us.ibm.com with ESMTP id 37max15rwy-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Wed, 31 Mar 2021 15:23:13 +0000
Received: from b03ledav001.gho.boulder.ibm.com
 (b03ledav001.gho.boulder.ibm.com [9.17.130.232])
        by b03cxnp07028.gho.boulder.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id 12VFNAP728443004
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Wed, 31 Mar 2021 15:23:10 GMT
Received: from b03ledav001.gho.boulder.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 526E86E050;
        Wed, 31 Mar 2021 15:23:10 +0000 (GMT)
Received: from b03ledav001.gho.boulder.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 7AA7B6E04E;
        Wed, 31 Mar 2021 15:23:08 +0000 (GMT)
Received: from cpe-66-24-58-13.stny.res.rr.com.com (unknown [9.85.146.149])
        by b03ledav001.gho.boulder.ibm.com (Postfix) with ESMTP;
        Wed, 31 Mar 2021 15:23:08 +0000 (GMT)
From: Tony Krowiak <akrowiak@linux.ibm.com>
To: linux-s390@vger.kernel.org, linux-kernel@vger.kernel.org,
        kvm@vger.kernel.org
Cc: jjherne@linux.ibm.com, freude@linux.ibm.com,
        borntraeger@de.ibm.com, cohuck@redhat.com, mjrosato@linux.ibm.com,
        pasic@linux.ibm.com, alex.williamson@redhat.com,
        kwankhede@nvidia.com, fiuczy@linux.ibm.com, frankja@linux.ibm.com,
        david@redhat.com, hca@linux.ibm.com, gor@linux.ibm.com,
        Tony Krowiak <akrowiak@linux.ibm.com>
Subject: [PATCH v14 00/13] s390/vfio-ap: dynamic configuration support
Date: Wed, 31 Mar 2021 11:22:43 -0400
Message-Id: <20210331152256.28129-1-akrowiak@linux.ibm.com>
X-Mailer: git-send-email 2.21.3
MIME-Version: 1.0
X-TM-AS-GCONF: 00
X-Proofpoint-GUID: w0ToRZeRDjijpOkTW_2ZyiVlomBzzBr9
X-Proofpoint-ORIG-GUID: yATfdkLPDojo0GfcT4E6q3Y4USJ4J1sl
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.369,18.0.761
 definitions=2021-03-31_06:2021-03-31,2021-03-31 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 adultscore=0 spamscore=0
 mlxlogscore=999 priorityscore=1501 mlxscore=0 malwarescore=0
 suspectscore=0 phishscore=0 clxscore=1015 bulkscore=0 lowpriorityscore=0
 impostorscore=0 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.12.0-2103300000 definitions=main-2103310107
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Note: Patch 1, "s390/vfio-ap: fix circular lockdep when setting/clearing
      crypto masks" does not belong to this series. It is currently
      being merged and is included here because it is a pre-req for
      this series.

      Ignore checkpatch warnings regarding unknown commit IDs, those
      appears to be made in error.

The current design for AP pass-through does not support making dynamic
changes to the AP matrix of a running guest resulting in a few
deficiencies this patch series is intended to mitigate:

1. Adapters, domains and control domains can not be added to or removed
   from a running guest. In order to modify a guest's AP configuration,
   the guest must be terminated; only then can AP resources be assigned
   to or unassigned from the guest's matrix mdev. The new AP
   configuration becomes available to the guest when it is subsequently
   restarted.

2. The AP bus's /sys/bus/ap/apmask and /sys/bus/ap/aqmask interfaces can
   be modified by a root user without any restrictions. A change to
   either mask can result in AP queue devices being unbound from the
   vfio_ap device driver and bound to a zcrypt device driver even if a
   guest is using the queues, thus giving the host access to the guest's
   private crypto data and vice versa.

3. The APQNs derived from the Cartesian product of the APIDs of the
   adapters and APQIs of the domains assigned to a matrix mdev must
   reference an AP queue device bound to the vfio_ap device driver. The
   AP architecture allows assignment of AP resources that are not
   available to the system, so this artificial restriction is not
   compliant with the architecture.

4. The AP configuration profile can be dynamically changed for the linux
   host after a KVM guest is started. For example, a new domain can be
   dynamically added to the configuration profile via the SE or an HMC
   connected to a DPM enabled lpar. Likewise, AP adapters can be
   dynamically configured (online state) and deconfigured (standby state)
   using the SE, an SCLP command or an HMC connected to a DPM enabled
   lpar. This can result in inadvertent sharing of AP queues between the
   guest and host.

5. A root user can manually unbind an AP queue device representing a
   queue in use by a KVM guest via the vfio_ap device driver's sysfs
   unbind attribute. In this case, the guest will be using a queue that
   is not bound to the driver which violates the device model.

This patch series introduces the following changes to the current design
to alleviate the shortcomings described above as well as to implement
more of the AP architecture:

1. A root user will be prevented from making edits to the AP bus's
   /sys/bus/ap/apmask or /sys/bus/ap/aqmask if the change would transfer
   ownership of an APQN from the vfio_ap device driver to a zcrypt driver
   while the APQN is assigned to a matrix mdev.

2. Allow a root user to hot plug/unplug AP adapters, domains and control
   domains for a KVM guest using the matrix mdev via its sysfs
   assign/unassign attributes.

4. Allow assignment of an AP adapter or domain to a matrix mdev even if
   it results in assignment of an APQN that does not reference an AP
   queue device bound to the vfio_ap device driver, as long as the APQN
   is not reserved for use by the default zcrypt drivers (also known as
   over-provisioning of AP resources). Allowing over-provisioning of AP
   resources better models the architecture which does not preclude
   assigning AP resources that are not yet available in the system. Such
   APQNs, however, will not be assigned to the guest using the matrix
   mdev; only APQNs referencing AP queue devices bound to the vfio_ap
   device driver will actually get assigned to the guest.

5. Handle dynamic changes to the AP device model.

1. Rationale for changes to AP bus's apmask/aqmask interfaces:
----------------------------------------------------------
Due to the extremely sensitive nature of cryptographic data, it is
imperative that great care be taken to ensure that such data is secured.
Allowing a root user, either inadvertently or maliciously, to configure
these masks such that a queue is shared between the host and a guest is
not only avoidable, it is advisable. It was suggested that this scenario
is better handled in user space with management software, but that does
not preclude a malicious administrator from using the sysfs interfaces
to gain access to a guest's crypto data. It was also suggested that this
scenario could be avoided by taking access to the adapter away from the
guest and zeroing out the queues prior to the vfio_ap driver releasing the
device; however, stealing an adapter in use from a guest as a by-product
of an operation is bad and will likely cause problems for the guest
unnecessarily. It was decided that the most effective solution with the
least number of negative side effects is to prevent the situation at the
source.

2. Rationale for hot plug/unplug using matrix mdev sysfs interfaces:
----------------------------------------------------------------
Allowing a user to hot plug/unplug AP resources using the matrix mdev
sysfs interfaces circumvents the need to terminate the guest in order to
modify its AP configuration. Allowing dynamic configuration makes
reconfiguring a guest's AP matrix much less disruptive.

3. Rationale for allowing over-provisioning of AP resources:
-----------------------------------------------------------
Allowing assignment of AP resources to a matrix mdev and ultimately to a
guest better models the AP architecture. The architecture does not
preclude assignment of unavailable AP resources. If a queue subsequently
becomes available while a guest using the matrix mdev to which its APQN
is assigned, the guest will be given access to it. If an APQN
is dynamically unassigned from the underlying host system, it will
automatically become unavailable to the guest.

Change log v13-v14:
------------------
* Removed patch "s390/vfio-ap: clean up vfio_ap resources when KVM pointer
  invalidated". The patch is not necessary because that is handled
  with patch 1 of this series (currently being merged) and
  commit f21916ec4826 ("s390/vfio-ap: clean up vfio_ap resources when KVM pointer invalidated")

* Removed patch "s390/vfio-ap: No need to disable IRQ after queue reset",
  that has already been merged with
  commit 6c12a6384e0c ("s390/vfio-ap: No need to disable IRQ after queue reset").

* Initialize the vfio_ap_queue object before setting the drvdata in
  the probe callback

* Change return code from mdev assignment interfaces to -EAGAIN when
  mutex_trylock fails for the mdev lock.

* Restored missing hunk from v12 in the group notifier callback, but
  had to restore it to the vfio_ap_mdev_set_kvm() function due to
  changes made via merged commits noted above.

* Reordered patch "s390/vfio-ap: sysfs attribute to display the
  guest's matrix" to follow the patches that modify the shadow
  APCB.

* Remove queue from APCB before resetting it in the remove
  callback.

* Split the vfio_ap_mdev_unlink_queue() function into two
  functions: one to remove the link from the matrix mdev to
  the queue; and, one to remove the link from the queue to the matrix
  mdev.

* Removed the QCI call and the shadow_apcb memcpy from the
  vfio_ap_mdev_filter_apcb() function.

* Do not clear shadow_apcb when there are not adapters or domains
  assigned.

* Moved filtering code from "s390/vfio-ap: allow hot plug/unplug of
  AP resources using mdev device" into its own patch.

* Squashed the two patches comprising the handling of changes to
  the AP configuration into one patch.

* Added code to delay hot plug during probe until the AP bus scan
  is complete if the APID of the queue is in the bitmap of adapters
  currently being added to the AP configuration.

Change log v12-v13:
------------------
* Combined patches 12/13 from previous series into one patch

* Moved all changes for linking queues and mdevs into a single patch

* Re-ordered some patches to aid in review

* Using mutex_trylock() function in adapter/domain assignment functions
  to avoid potential deadlock condition with in_use callback

* Using filtering function for refreshing the guest's APCB for all events
  that change the APCB: assign/unassign adapters, domains, control domains;
  bind/unbind of queue devices; and, changes to the host AP configuration.

Change log v11-v12:
------------------
* Moved matrix device lock to protect group notifier callback

* Split the 'No need to disable IRQ after queue reset' patch into
  multiple patches for easier review (move probe/remove callback
  functions and remove disable IRQ after queue reset)

* Added code to decrement reference count for KVM in group notifier
  callback

* Using mutex_trylock() in functions implementing the sysfs assign_adapter
  and assign_domain as well as the in_use callback to avoid deadlock
  between the AP bus's ap_perms mutex and the matrix device lock used by
  vfio_ap driver.

* The sysfs guest_matrix attribute of the vfio_ap mdev will now display
  the shadow APCB regardless of whether a guest is using the mdev or not

* Replaced vfio_ap mdev filtering function with a function that initializes
  the guest's APCB by filtering the vfio_ap mdev by APID.

* No longer using filtering function during adapter/domain assignment
  to/from the vfio_ap mdev; replaced with new hot plug/unplug
  adapter/domain functions.

* No longer using filtering function during bind/unbind; replaced with
  hot plug/unplug queue functions.

* No longer using filtering function for bulk assignment of new adapters
  and domains in on_scan_complete callback; replaced with new hot plug
  functions.


Change log v10-v11:
------------------
* The matrix mdev's configuration is not filtered by APID so that if any
  APQN assigned to the mdev is not bound to the vfio_ap device driver,
  the adapter will not get plugged into the KVM guest on startup, or when
  a new adapter is assigned to the mdev.

* Replaced patch 8 by squashing patches 8 (filtering patch) and 15 (handle
  probe/remove).

* Added a patch 1 to remove disable IRQ after a reset because the reset
  already disables a queue.

* Now using filtering code to update the KVM guest's matrix when
  notified that AP bus scan has completed.

* Fixed issue with probe/remove not inititiated by a configuration change
  occurring within a config change.


Change log v9-v10:
-----------------
* Updated the documentation in vfio-ap.rst to include information about the
  AP dynamic configuration support

Change log v8-v9:
----------------
* Fixed errors flagged by the kernel test robot

* Fixed issue with guest losing queues when a new queue is probed due to
  manual bind operation.

Change log v7-v8:
----------------
* Now logging a message when an attempt to reserve APQNs for the zcrypt
  drivers will result in taking a queue away from a KVM guest to provide
  the sysadmin a way to ascertain why the sysfs operation failed.

* Created locked and unlocked versions of the ap_parse_mask_str() function.

* Now using new interface provided by an AP bus patch -
  s390/ap: introduce new ap function ap_get_qdev() - to retrieve
  struct ap_queue representing an AP queue device. This patch is not a
  part of this series but is a prerequisite for this series.

Change log v6-v7:
----------------
* Added callbacks to AP bus:
  - on_config_changed: Notifies implementing drivers that
    the AP configuration has changed since last AP device scan.
  - on_scan_complete: Notifies implementing drivers that the device scan
    has completed.
  - implemented on_config_changed and on_scan_complete callbacks for
    vfio_ap device driver.
  - updated vfio_ap device driver's probe and remove callbacks to handle
    dynamic changes to the AP device model.
* Added code to filter APQNs when assigning AP resources to a KVM guest's
  CRYCB

Change log v5-v6:
----------------
* Fixed a bug in ap_bus.c introduced with patch 2/7 of the v5
  series. Harald Freudenberer pointed out that the mutex lock
  for ap_perms_mutex in the apmask_store and aqmask_store functions
  was not being freed.

* Removed patch 6/7 which added logging to the vfio_ap driver
  to expedite acceptance of this series. The logging will be introduced
  with a separate patch series to allow more time to explore options
  such as DBF logging vs. tracepoints.

* Added 3 patches related to ensuring that APQNs that do not reference
  AP queue devices bound to the vfio_ap device driver are not assigned
  to the guest CRYCB:

  Patch 4: Filter CRYCB bits for unavailable queue devices
  Patch 5: sysfs attribute to display the guest CRYCB
  Patch 6: update guest CRYCB in vfio_ap probe and remove callbacks

* Added a patch (Patch 9) to version the vfio_ap module.

* Reshuffled patches to allow the in_use callback implementation to
  invoke the vfio_ap_mdev_verify_no_sharing() function introduced in
  patch 2.

Change log v4-v5:
----------------
* Added a patch to provide kernel s390dbf debug logs for VFIO AP

Change log v3->v4:
-----------------
* Restored patches preventing root user from changing ownership of
  APQNs from zcrypt drivers to the vfio_ap driver if the APQN is
  assigned to an mdev.

* No longer enforcing requirement restricting guest access to
  queues represented by a queue device bound to the vfio_ap
  device driver.

* Removed shadow CRYCB and now directly updating the guest CRYCB
  from the matrix mdev's matrix.

* Rebased the patch series on top of 'vfio: ap: AP Queue Interrupt
  Control' patches.

* Disabled bind/unbind sysfs interfaces for vfio_ap driver

Change log v2->v3:
-----------------
* Allow guest access to an AP queue only if the queue is bound to
  the vfio_ap device driver.

* Removed the patch to test CRYCB masks before taking the vCPUs
  out of SIE. Now checking the shadow CRYCB in the vfio_ap driver.

Change log v1->v2:
-----------------
* Removed patches preventing root user from unbinding AP queues from
  the vfio_ap device driver
* Introduced a shadow CRYCB in the vfio_ap driver to manage dynamic
  changes to the AP guest configuration due to root user interventions
  or hardware anomalies.

Tony Krowiak (13):
  s390/vfio-ap: fix circular lockdep when setting/clearing crypto masks
  s390/vfio-ap: use new AP bus interface to search for queue devices
  s390/vfio-ap: move probe and remove callbacks to vfio_ap_ops.c
  s390/vfio-ap: manage link between queue struct and matrix mdev
  s390/vfio-ap: introduce shadow APCB
  s390/vfio-ap: refresh guest's APCB by filtering APQNs assigned to mdev
  s390/vfio-ap: allow assignment of unavailable AP queues to mdev device
  s390/vfio-ap: allow hot plug/unplug of AP resources using mdev device
  s390/zcrypt: driver callback to indicate resource in use
  s390/vfio-ap: implement in-use callback for vfio_ap driver
  s390/vfio-ap: sysfs attribute to display the guest's matrix
  s390/zcrypt: notify drivers on config changed and scan complete
    callbacks
  s390/vfio-ap: update docs to include dynamic config support

 Documentation/s390/vfio-ap.rst        |  383 ++++++---
 drivers/s390/crypto/ap_bus.c          |  249 +++++-
 drivers/s390/crypto/ap_bus.h          |   16 +
 drivers/s390/crypto/vfio_ap_drv.c     |   46 +-
 drivers/s390/crypto/vfio_ap_ops.c     | 1090 ++++++++++++++++++-------
 drivers/s390/crypto/vfio_ap_private.h |   29 +-
 6 files changed, 1347 insertions(+), 466 deletions(-)
---
2.21.3
```
#### [PATCH 00/13] More parallel operations for the TDP MMU
##### From: Ben Gardon <bgardon@google.com>

```c
From patchwork Wed Mar 31 21:08:28 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Ben Gardon <bgardon@google.com>
X-Patchwork-Id: 12176327
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-21.3 required=3.0 tests=BAYES_00,DKIMWL_WL_MED,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT,
	USER_IN_DEF_DKIM_WL autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id B7BD1C433ED
	for <kvm@archiver.kernel.org>; Wed, 31 Mar 2021 21:09:53 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 78AB161056
	for <kvm@archiver.kernel.org>; Wed, 31 Mar 2021 21:09:53 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S232623AbhCaVJZ (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Wed, 31 Mar 2021 17:09:25 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:47562 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S232690AbhCaVJB (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 31 Mar 2021 17:09:01 -0400
Received: from mail-pf1-x449.google.com (mail-pf1-x449.google.com
 [IPv6:2607:f8b0:4864:20::449])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id CFDCAC061574
        for <kvm@vger.kernel.org>; Wed, 31 Mar 2021 14:09:00 -0700 (PDT)
Received: by mail-pf1-x449.google.com with SMTP id b21so2103308pfo.0
        for <kvm@vger.kernel.org>; Wed, 31 Mar 2021 14:09:00 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=date:message-id:mime-version:subject:from:to:cc;
        bh=wLumlh5Twi+XjlHspQtyQXk/t5XvCvCZtQfxC02BzcM=;
        b=XcVvRJvwhGeau31q8amFrhNk8W8SIy2xH0x+zgzIDA3DdYwUJBHv3CKmLmSVvRKCze
         LSksJUIL7SOY+dbFVf3fo4IDFoIBAr0HX+g9SitK6yFo3y17bJYRQixckb04GjwMnPeL
         WPL5vTt+3P8pDbdfg+urKM6GMzARftZpTe6FbZ4o+luN7dYO5dsboLzaV+wIjQJXlZUB
         HzVUyc/4Eio/O4Okmhb7HbGEPsWYZDjFSNt7XZ5x3IAZXh2t4CRN2FJVp7evUAAThc1C
         GUo24QwF7/F+0ku47iAqEYbxB6feoZizXOPovkRyC0EitPRCjUAiUc5EQ4Y0WzN09xQ/
         Cbjg==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:date:message-id:mime-version:subject:from:to:cc;
        bh=wLumlh5Twi+XjlHspQtyQXk/t5XvCvCZtQfxC02BzcM=;
        b=Z8rbLif5sDTA62yB2JddQt7hgrL5N4irjfmIT7Xl8xQrZBYxB2oX1jxaWBa8X0fw3h
         2JirZOJojHEX0PEJyTdzD6bUOLWeN6PJonu9c1v71Gxsy5hSBqJ7MptBjmNpTKkcUUQI
         hh+AKW5onvmf/KZb80fMvs7DTyQBMOiRpRrdWJkp92f2IXV7jW/P30ZocqYngjdMWoAT
         wMEHUp6Ysb3AmEsXeSJDpN/t8Z3pUToO8ukqJbkGlWVEEicMD8mKsc6x9PtmZmPJ2c+P
         u/CpJ2MBthDvWn3tXccjhn2P5i2gXeu1XBiksPU/EuP+ab90i/mhH7OigEw6OYu6AHiC
         1JaA==
X-Gm-Message-State: AOAM530V4UDb5IvlPPQEpY0fmyK/qqFInCbX3Y7vyp9KBlbHug4x53oi
        0+T38NRZe8rXZ7WBm90iSUzsyDC8q6L0
X-Google-Smtp-Source: 
 ABdhPJyWi3SISzllHSTMvnXWzcmmmiOdVrrxftg5HVbq7bPgSzl3537aes3L7GYo9c9PqTPpvuvi5UmzzfEB
X-Received: from bgardon.sea.corp.google.com
 ([2620:15c:100:202:8026:6888:3d55:3842])
 (user=bgardon job=sendgmr) by 2002:a17:90a:3ec3:: with SMTP id
 k61mr5190861pjc.125.1617224940296; Wed, 31 Mar 2021 14:09:00 -0700 (PDT)
Date: Wed, 31 Mar 2021 14:08:28 -0700
Message-Id: <20210331210841.3996155-1-bgardon@google.com>
Mime-Version: 1.0
X-Mailer: git-send-email 2.31.0.291.g576ba9dcdaf-goog
Subject: [PATCH 00/13] More parallel operations for the TDP MMU
From: Ben Gardon <bgardon@google.com>
To: linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Cc: Paolo Bonzini <pbonzini@redhat.com>, Peter Xu <peterx@redhat.com>,
        Sean Christopherson <seanjc@google.com>,
        Peter Shier <pshier@google.com>,
        Peter Feiner <pfeiner@google.com>,
        Junaid Shahid <junaids@google.com>,
        Jim Mattson <jmattson@google.com>,
        Yulei Zhang <yulei.kernel@gmail.com>,
        Wanpeng Li <kernellwp@gmail.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Xiao Guangrong <xiaoguangrong.eric@gmail.com>,
        Ben Gardon <bgardon@google.com>
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Now that the TDP MMU is able to handle page faults in parallel, it's a
relatively small change to expand to other operations. This series allows
zapping a range of GFNs, reclaiming collapsible SPTEs (when disabling
dirty logging), and enabling dirty logging to all happen under the MMU
lock in read mode.

This is partly a cleanup + rewrite of the last few patches of the parallel
page faults series. I've incorporated feedback from Sean and Paolo, but
the patches have changed so much that I'm sending this as a separate
series.

Ran kvm-unit-tests + selftests on an SMP kernel + Intel Skylake, with the
TDP MMU enabled and disabled. This series introduces no new failures or
warnings.

I know this will conflict horribly with the patches from Sean's series
which were just queued, and I'll send a v2 to fix those conflicts +
address any feedback on this v1.

Ben Gardon (13):
  KVM: x86/mmu: Re-add const qualifier in
    kvm_tdp_mmu_zap_collapsible_sptes
  KVM: x86/mmu: Move kvm_mmu_(get|put)_root to TDP MMU
  KVM: x86/mmu: use tdp_mmu_free_sp to free roots
  KVM: x86/mmu: Merge TDP MMU put and free root
  KVM: x86/mmu: comment for_each_tdp_mmu_root requires MMU write lock
  KVM: x86/mmu: Refactor yield safe root iterator
  KVM: x86/mmu: Make TDP MMU root refcount atomic
  KVM: x86/mmu: Protect the tdp_mmu_roots list with RCU
  KVM: x86/mmu: Allow zap gfn range to operate under the mmu read lock
  KVM: x86/mmu: Allow zapping collapsible SPTEs to use MMU read lock
  KVM: x86/mmu: Allow enabling / disabling dirty logging under MMU read
    lock
  KVM: x86/mmu: Fast invalidation for TDP MMU
  KVM: x86/mmu: Tear down roots in fast invalidation thread

 arch/x86/kvm/mmu/mmu.c          |  70 +++---
 arch/x86/kvm/mmu/mmu_internal.h |  27 +--
 arch/x86/kvm/mmu/tdp_mmu.c      | 383 ++++++++++++++++++++++++--------
 arch/x86/kvm/mmu/tdp_mmu.h      |  21 +-
 include/linux/kvm_host.h        |   2 +-
 5 files changed, 357 insertions(+), 146 deletions(-)
```
