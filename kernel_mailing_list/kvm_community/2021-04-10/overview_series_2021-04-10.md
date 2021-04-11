#### [PATCH 5.10/5.11 1/9] KVM: x86/mmu: change TDP MMU yield function returns to match cond_resched
##### From: Paolo Bonzini <pbonzini@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Paolo Bonzini <pbonzini@redhat.com>
X-Patchwork-Id: 12195665
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-15.8 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_CR_TRAILER,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS
	autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 50738C43618
	for <kvm@archiver.kernel.org>; Sat, 10 Apr 2021 15:12:41 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 33332611CA
	for <kvm@archiver.kernel.org>; Sat, 10 Apr 2021 15:12:41 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S234886AbhDJPMy (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Sat, 10 Apr 2021 11:12:54 -0400
Received: from us-smtp-delivery-124.mimecast.com ([216.205.24.124]:24316 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S234816AbhDJPMv (ORCPT
        <rfc822;kvm@vger.kernel.org>); Sat, 10 Apr 2021 11:12:51 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1618067556;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding:
         in-reply-to:in-reply-to:references:references;
        bh=9VnaEyLiKlk+abqPIP972RBU+gLglyTb6uphMyujnCk=;
        b=JGMokxzlAl08tDOJvZRqp0VikbwPrcaTCBpYpbhetRgA3LekQ4xN04UTe1b8oN2sMKe6h/
        lKZ5FJoDSgAUkE99pwKZNTpHhMj367UZy6DkdoBm24hK14RA/1QlqpxXXIGGd1p1fGwLQe
        J4VIZHnu8UcuFSZTbASYhQhNOXeTpJw=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-485-iagYyFR0NayepOtaIbD-YA-1; Sat, 10 Apr 2021 11:12:31 -0400
X-MC-Unique: iagYyFR0NayepOtaIbD-YA-1
Received: from smtp.corp.redhat.com (int-mx04.intmail.prod.int.phx2.redhat.com
 [10.5.11.14])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id CA0191006701;
        Sat, 10 Apr 2021 15:12:30 +0000 (UTC)
Received: from virtlab701.virt.lab.eng.bos.redhat.com
 (virtlab701.virt.lab.eng.bos.redhat.com [10.19.152.228])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 789195D9D3;
        Sat, 10 Apr 2021 15:12:30 +0000 (UTC)
From: Paolo Bonzini <pbonzini@redhat.com>
To: stable@vger.kernel.org
Cc: kvm@vger.kernel.org, sasha@kernel.org
Subject: [PATCH 5.10/5.11 1/9] KVM: x86/mmu: change TDP MMU yield function
 returns to match cond_resched
Date: Sat, 10 Apr 2021 11:12:21 -0400
Message-Id: <20210410151229.4062930-2-pbonzini@redhat.com>
In-Reply-To: <20210410151229.4062930-1-pbonzini@redhat.com>
References: <20210410151229.4062930-1-pbonzini@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.14
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Ben Gardon <bgardon@google.com>

[ Upstream commit e28a436ca4f65384cceaf3f4da0e00aa74244e6a ]

Currently the TDP MMU yield / cond_resched functions either return
nothing or return true if the TLBs were not flushed. These are confusing
semantics, especially when making control flow decisions in calling
functions.

To clean things up, change both functions to have the same
return value semantics as cond_resched: true if the thread yielded,
false if it did not. If the function yielded in the _flush_ version,
then the TLBs will have been flushed.

Reviewed-by: Peter Feiner <pfeiner@google.com>
Acked-by: Paolo Bonzini <pbonzini@redhat.com>
Signed-off-by: Ben Gardon <bgardon@google.com>
Message-Id: <20210202185734.1680553-2-bgardon@google.com>
Signed-off-by: Paolo Bonzini <pbonzini@redhat.com>
---
 arch/x86/kvm/mmu/tdp_mmu.c | 39 ++++++++++++++++++++++++++++----------
 1 file changed, 29 insertions(+), 10 deletions(-)

```
#### [PATCH kvm-unit-tests] access: change CR0/CR4/EFER before TLB flushes
##### From: Paolo Bonzini <pbonzini@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Paolo Bonzini <pbonzini@redhat.com>
X-Patchwork-Id: 12195643
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.8 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT autolearn=ham
	autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id C4133C433B4
	for <kvm@archiver.kernel.org>; Sat, 10 Apr 2021 14:42:41 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 88736610CD
	for <kvm@archiver.kernel.org>; Sat, 10 Apr 2021 14:42:41 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S234757AbhDJOmz (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Sat, 10 Apr 2021 10:42:55 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:59420 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S234722AbhDJOmx (ORCPT <rfc822;kvm@vger.kernel.org>);
        Sat, 10 Apr 2021 10:42:53 -0400
Received: from mail-ed1-x532.google.com (mail-ed1-x532.google.com
 [IPv6:2a00:1450:4864:20::532])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 2EA92C06138B
        for <kvm@vger.kernel.org>; Sat, 10 Apr 2021 07:42:38 -0700 (PDT)
Received: by mail-ed1-x532.google.com with SMTP id r22so9799826edq.9
        for <kvm@vger.kernel.org>; Sat, 10 Apr 2021 07:42:38 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=sender:from:to:cc:subject:date:message-id:mime-version
         :content-transfer-encoding;
        bh=kTawFiL6YC0ek5PHB26XWuvo8LaNhKMkeOr4Du3g3zA=;
        b=JCcCeg0rQfZpHF7PhaQNGA3miaa7tggjS+utX6p12DI0sTb0ihsmqMgvvGsbxtDHCr
         KgoxghxA7da6cqteVtbnfdO5V/Pc97pVB/ZvZVnWPHB9wxtQxiJw8CRBdl+mbjT7FQEX
         1jxnAnJoT8pgL6emKLIsCAiabuxq45xMybI397PO1WX6fCN20mDAnGeLbOuRj+tslGID
         k7fLuauKxt18AHgRiTMJx3N8l/0z2pwcZE+4CWsQsuLtFzIlqjgCUuUwbYZ9wsAgg0Bi
         pfD0Ze0K6Y8gsSkfdsODcr1rRuva1eS7YeXt+og1VSY4EygWHqVoZ/J05B/xXUjB8aRB
         eatw==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:sender:from:to:cc:subject:date:message-id
         :mime-version:content-transfer-encoding;
        bh=kTawFiL6YC0ek5PHB26XWuvo8LaNhKMkeOr4Du3g3zA=;
        b=ODW/6dgrNSirnjUoQvNVPf04C17s+8NiXgzp/YP9RYxkA77gmTn8TbRDUX2mc/kaai
         QjRcHaDrWH8/UGmt844repkdds5d3BNrco6fqsV/z5KpjHrYhbIRKpTErmFz1XEeT9E/
         53yYzMZCSHTJK1mqzFuX+B2dYKuH1AlT3ycdyZjxUIx2lmueSbEKUyqFPx1rG0YJYL5e
         eRJQjVFb9naKcb2m7O0NmjABw3esj92bMyfSZFG3ATASXGpCOU19ieRjD/3j89KIbqkx
         P9q7Pim+RdC9mDTpUpwS9bh3zdiXbQGQqGtuJMPO0qvMod9Unb9M5sy6tGNklgcexK7y
         q1Yw==
X-Gm-Message-State: AOAM530wFd2LsRzW8ljt7IMZrK5LG44WIbzRcwlgBTDo2UvXpC3DaPu6
        ewGJWuzAs+8CuFnpqwsRVD6sOAqy1DM=
X-Google-Smtp-Source: 
 ABdhPJw76ssbtXK8h1CD4DJy4g5SmIyJB4j8fKnOjZbRV/ewnbsLEO1fsF1/x1o4JGKvUz5HJrCEUA==
X-Received: by 2002:a05:6402:34d5:: with SMTP id
 w21mr21863459edc.14.1618065756922;
        Sat, 10 Apr 2021 07:42:36 -0700 (PDT)
Received: from avogadro.redhat.com ([2001:b07:add:ec09:c399:bc87:7b6c:fb2a])
        by smtp.gmail.com with ESMTPSA id
 q18sm3171357edr.26.2021.04.10.07.42.36
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Sat, 10 Apr 2021 07:42:36 -0700 (PDT)
Sender: Paolo Bonzini <paolo.bonzini@gmail.com>
From: Paolo Bonzini <pbonzini@redhat.com>
To: kvm@vger.kernel.org
Cc: seanjc@google.com, Yang Weijiang <weijiang.yang@intel.com>
Subject: [PATCH kvm-unit-tests] access: change CR0/CR4/EFER before TLB flushes
Date: Sat, 10 Apr 2021 16:42:34 +0200
Message-Id: <20210410144234.32124-2-pbonzini@redhat.com>
X-Mailer: git-send-email 2.30.1
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

After CR0/CR4/EFER changes a stale TLB entry can be observed, because MOV
to CR4 only invalidates TLB entries if CR4.SMEP is changed from 0 to 1.

The TLB is already flushed in ac_set_expected_status,
but if kvm-unit-tests is migrated to another CPU and CR4 is
changed after the flush, a stale entry can be used.

Reported-by: Yang Weijiang <weijiang.yang@intel.com>
Signed-off-by: Paolo Bonzini <pbonzini@redhat.com>
---
 x86/access.c | 25 ++++++++++++-------------
 1 file changed, 12 insertions(+), 13 deletions(-)

```
#### [PATCH kvm-unit-tests] access: use write_cr4_checking to verify support for SMEP or PKE
##### From: Paolo Bonzini <pbonzini@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Paolo Bonzini <pbonzini@redhat.com>
X-Patchwork-Id: 12195641
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.8 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT autolearn=ham
	autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 851D1C433ED
	for <kvm@archiver.kernel.org>; Sat, 10 Apr 2021 14:42:40 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 4C681610F9
	for <kvm@archiver.kernel.org>; Sat, 10 Apr 2021 14:42:40 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S234751AbhDJOmx (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Sat, 10 Apr 2021 10:42:53 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:59416 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S234392AbhDJOmw (ORCPT <rfc822;kvm@vger.kernel.org>);
        Sat, 10 Apr 2021 10:42:52 -0400
Received: from mail-ed1-x52b.google.com (mail-ed1-x52b.google.com
 [IPv6:2a00:1450:4864:20::52b])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 7D02CC06138A
        for <kvm@vger.kernel.org>; Sat, 10 Apr 2021 07:42:37 -0700 (PDT)
Received: by mail-ed1-x52b.google.com with SMTP id z1so9830626edb.8
        for <kvm@vger.kernel.org>; Sat, 10 Apr 2021 07:42:37 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=sender:from:to:cc:subject:date:message-id:mime-version
         :content-transfer-encoding;
        bh=g+UooGIfoZx9slLMvWVUsqUczD4vwR4RMOgrCkknVVY=;
        b=Cd/si5A+qKreqoNG5e1vVMDtBMRVT5UOb9918ajRUwyAKr05S7cBVM3ot6OhI66Bl6
         7/jyVfzN3l3X7PxNq/GqnMd/znqwTEnr8UvWZl+9z+pIu80zVxwcXk9PtQvYYQ7jDhw3
         XzObbN41ntL7EGLeHDDvrUWiEJGx5RVqPtcahWg5tBBUlM9HsuXiKHK5HnWWIaQMxiCt
         Hkmb1b0VJ+12rZ/0HQnLhTX0l2IqHbbJjoSA+QUUd4nmaULsuHKi8k9wqXvh+oqDxwuR
         FMJu0vNAYrJ8Yc7e+zMmk0CYMfO8ynZ9l2Erzgsx1Jqt84yIcYG5Jm5qwJK59V7EUnS+
         gBvQ==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:sender:from:to:cc:subject:date:message-id
         :mime-version:content-transfer-encoding;
        bh=g+UooGIfoZx9slLMvWVUsqUczD4vwR4RMOgrCkknVVY=;
        b=Q/+JwWt6lFEDXEp+HxicybmfFQQ0oGaNaWJi0w00oRAOVcFFLzklkm7habQnKdaU/D
         zQMAASnxepBDoEOJJR+07MEhFk18FXCKWWFhSU16g51kC0qb3xpTRWUl50yCIfIHp7yS
         jiYoIWMgZtmbBIiTse+iQR2UGvOWeZbKZKPWm0otl8/vSlI3GhFqws6L3/PW9ulwnUt3
         k4NYbOf85i85fE5F5+02EFdPpN+yXPZk0trvs2tVR4vBzKMxmKKEgR1XbxLtQmKUVg8P
         E8ynpiNLVvHhzhUv7GlRYLsKLftboNhpLCDP2NZ2xVXUMpY6bLkGjUrWj1y+uh8WRggA
         Uuxg==
X-Gm-Message-State: AOAM532TNYvbZEiPl41rn81+BFskAKd4XCEhTS3p2BdaEg+gCqdUf13/
        FVM9iuj4yiTz6SxDzXLpbFmoD9Sl494=
X-Google-Smtp-Source: 
 ABdhPJxEAp41mgzi/n7ft0OmxVZyTsy4x07vrAsvH8sq6HSJRkWygJdmJv3oVTTdo+xkh+cMmAUwXg==
X-Received: by 2002:a05:6402:518b:: with SMTP id
 q11mr21767825edd.151.1618065756169;
        Sat, 10 Apr 2021 07:42:36 -0700 (PDT)
Received: from avogadro.redhat.com ([2001:b07:add:ec09:c399:bc87:7b6c:fb2a])
        by smtp.gmail.com with ESMTPSA id
 q18sm3171357edr.26.2021.04.10.07.42.35
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Sat, 10 Apr 2021 07:42:35 -0700 (PDT)
Sender: Paolo Bonzini <paolo.bonzini@gmail.com>
From: Paolo Bonzini <pbonzini@redhat.com>
To: kvm@vger.kernel.org
Cc: seanjc@google.com
Subject: [PATCH kvm-unit-tests] access: use write_cr4_checking to verify
 support for SMEP or PKE
Date: Sat, 10 Apr 2021 16:42:33 +0200
Message-Id: <20210410144234.32124-1-pbonzini@redhat.com>
X-Mailer: git-send-email 2.30.1
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Free set_cr4_smep from having to report failure to set CR4.SMEP,
so that it can report instead whether CR4 was changed.

Signed-off-by: Paolo Bonzini <pbonzini@redhat.com>
---
 x86/access.c | 19 ++++++++-----------
 1 file changed, 8 insertions(+), 11 deletions(-)

```
