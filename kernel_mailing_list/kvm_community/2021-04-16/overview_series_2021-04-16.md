#### [PATCH 1/2] kvm: x86: Allow userspace to handle emulation errorsFrom: Aaron Lewis <aaronlewis@google.com>
##### From: Aaron Lewis <aaronlewis@google.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Aaron Lewis <aaronlewis@google.com>
X-Patchwork-Id: 12207687
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
	by smtp.lore.kernel.org (Postfix) with ESMTP id 67785C433B4
	for <kvm@archiver.kernel.org>; Fri, 16 Apr 2021 13:19:04 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 2C8ED611AC
	for <kvm@archiver.kernel.org>; Fri, 16 Apr 2021 13:19:04 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S235707AbhDPNT1 (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Fri, 16 Apr 2021 09:19:27 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:55722 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S244154AbhDPNSs (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 16 Apr 2021 09:18:48 -0400
Received: from mail-pf1-x449.google.com (mail-pf1-x449.google.com
 [IPv6:2607:f8b0:4864:20::449])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 8F586C06138F
        for <kvm@vger.kernel.org>; Fri, 16 Apr 2021 06:18:23 -0700 (PDT)
Received: by mail-pf1-x449.google.com with SMTP id
 g12-20020a056a001a0cb0290249be0baf34so4339383pfv.16
        for <kvm@vger.kernel.org>; Fri, 16 Apr 2021 06:18:23 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=date:message-id:mime-version:subject:from:to:cc;
        bh=dRdITr/WAmVG+vGnM9+wlguJ2Mdi3htGhTv4Io0hgA8=;
        b=CZXAojx61Q/unYRZ5zqN2+IWMvwl2CU/NpA9fhYVkraHC9oASxluDjY/PTA3QGZms+
         zgakCmMPhuT17N1rWYHVAJcHoE4ZwWHYvajUnyda2dnS5SD8MftRzr2zaXFPf76EoAbl
         486S857tTSCQJks0hkkYuRIQTpw5RR1EKfEez3Li0wNbRzjww+BRuAVkeWLETjYjdr0H
         NahfCJEop043yTifJ+xj/UBBJsm+mrq7vlVSzrglGupq7Eynr/aYEE7q8tez6J6Wj9RX
         qpBU9a3Cw8N5npn/rAkvl48mHUAiAMEtw1dcVGU0o9/x+swhpixqnl+Hrg8Abel62kse
         elCg==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:date:message-id:mime-version:subject:from:to:cc;
        bh=dRdITr/WAmVG+vGnM9+wlguJ2Mdi3htGhTv4Io0hgA8=;
        b=fn+/djdfi3/MtFV8T4FVGKo8dJC0/DdhlTI3qPVPPsY0VOnGo/4xwuR2xyuuTy+3nH
         StyMVoXSMNC/QDWnhewe8aBcNoNMsAOjENeBYjIXJNZDNjN41qu1zjL3HAw48RDrIiIo
         x7ZA4No8Sad/6EdecUgIv9XxTxfgpJPG0EbnQU3Ssz/X4NENbePZHkRcIeWzBkLgG4Tb
         9WqjOu5TNL4O9mRSnSCdMvIu5t4HdToUP2+eyrKC3yeDEANs4HOn1ah5vZRniGtjngiU
         pplM8ZeYR9CzZvEed1TOuzcm/Pq5WQUqRB8ah+HT2J62ybu6psrtlt6qt6MfzRcXHX/n
         2z5Q==
X-Gm-Message-State: AOAM531S7tdcaE0/mi+MMn4FPZsHBKnHSm8ZvzIe4aLFWFhh7tXkFx7J
        K4ENb/uLUlqvVVgMsvpHXgzN1sBoEhJTP9Cf
X-Google-Smtp-Source: 
 ABdhPJyKo0cpr7DC5vTQCQ82ICNsJ2RqFNCBII1Zd4iplZUrouzgxBri9bJtFsgoI+9hzNnIomXrLg9miKXr7NCU
X-Received: from aaronlewis1.sea.corp.google.com
 ([2620:15c:100:202:d536:4bae:c7e2:ec6a])
 (user=aaronlewis job=sendgmr) by 2002:a17:903:3106:b029:e9:15e8:250e with
 SMTP id w6-20020a1709033106b02900e915e8250emr9686942plc.33.1618579103064;
 Fri, 16 Apr 2021 06:18:23 -0700 (PDT)
Date: Fri, 16 Apr 2021 06:18:19 -0700
Message-Id: <20210416131820.2566571-1-aaronlewis@google.com>
Mime-Version: 1.0
X-Mailer: git-send-email 2.31.1.368.gbe11c130af-goog
Subject: [PATCH 1/2] kvm: x86: Allow userspace to handle emulation errors
From: Aaron Lewis <aaronlewis@google.com>
To: david.edmondson@oracle.com
Cc: jmattson@google.com, seanjc@google.com, kvm@vger.kernel.org,
        Aaron Lewis <aaronlewis@google.com>
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Add a fallback mechanism to the in-kernel instruction emulator that
allows userspace the opportunity to process an instruction the emulator
was unable to.  When the in-kernel instruction emulator fails to process
an instruction it will either inject a #UD into the guest or exit to
userspace with exit reason KVM_INTERNAL_ERROR.  This is because it does
not know how to proceed in an appropriate manner.  This feature lets
userspace get involved to see if it can figure out a better path
forward.

Signed-off-by: Aaron Lewis <aaronlewis@google.com>
Change-Id: If9876bc73d26f6c3ff9a8bce177c2fc6f160e629
---
 Documentation/virt/kvm/api.rst  | 16 ++++++++++++++++
 arch/x86/include/asm/kvm_host.h |  6 ++++++
 arch/x86/kvm/x86.c              | 33 +++++++++++++++++++++++++++++----
 include/uapi/linux/kvm.h        | 20 ++++++++++++++++++++
 tools/include/uapi/linux/kvm.h  | 20 ++++++++++++++++++++
 5 files changed, 91 insertions(+), 4 deletions(-)

```
#### [PATCH] KVM: Boost vCPU candidiate in user mode which is delivering interrupt
##### From: Wanpeng Li <kernellwp@gmail.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Wanpeng Li <kernellwp@gmail.com>
X-Patchwork-Id: 12206613
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-15.8 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,DKIM_VALID_AU,FREEMAIL_FORGED_FROMDOMAIN,FREEMAIL_FROM,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT autolearn=ham
	autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 27878C433B4
	for <kvm@archiver.kernel.org>; Fri, 16 Apr 2021 03:08:33 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id E34EF6113D
	for <kvm@archiver.kernel.org>; Fri, 16 Apr 2021 03:08:32 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S235001AbhDPDIz (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Thu, 15 Apr 2021 23:08:55 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:34394 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S234903AbhDPDIw (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 15 Apr 2021 23:08:52 -0400
Received: from mail-pf1-x42a.google.com (mail-pf1-x42a.google.com
 [IPv6:2607:f8b0:4864:20::42a])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id D3288C061574;
        Thu, 15 Apr 2021 20:08:23 -0700 (PDT)
Received: by mail-pf1-x42a.google.com with SMTP id n38so17430067pfv.2;
        Thu, 15 Apr 2021 20:08:23 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=from:to:cc:subject:date:message-id;
        bh=uFKS1WFTegraebrT+gI7cJRe7sDUnuGWyUREin+ouco=;
        b=YkfygmwWDmCVEsZLunBUBrilsLiA7IDScQtDDzAj1O22eaBGUAhpgnVjJ0bPLP2DV8
         ABXF+F3OcIAaOOSmIBZjD5lHAQfWI7rXaceSqRgKG5X1PDlzYeoBg/xafuj3LjCrlPbG
         AAhmkmcgCP2q9NnjFZK++3AjbBI6/eKREP579HKQQvtgTA6ivrz2C0hSflYVX7q3g93W
         JxHKKEO3j7OVCYMBwgNK8FeBGqowy0bELkQW6ZC5M+Ge1sIvKOZ9kOJt9rLkCbR8rPYx
         k69yWUvo9XBnvaEtZRYMxs0OHY6L0TGhr6F8VTuOwdb4/CAQoohkMsNrprP0dG+EuDCs
         VAIw==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id;
        bh=uFKS1WFTegraebrT+gI7cJRe7sDUnuGWyUREin+ouco=;
        b=eye7gZm7ZBS/u9+fCKv1lw6eXO9ST7gJ7y/hJGkb5l2HaZOtKH/odfUoqy6PKbIWq1
         IJYvaiN05Im+SZmeDfygmyEjht5ZB/R72bjDqTM+eAHVkAYAOZEsFBcAONvi6JeQw7hZ
         nSzTB7hsEMc5AC9qhd/tRFCbzr4EulsBviWAHLff0Nh5aGamSlcZmPvPAT+C4S9GSvyu
         iM+y2sUPJsy7QFauOR2U/xJFQCXcZQfFtvl/lXwwtQQLg6aA5B1DLt3YIq0rTLw0b8hO
         qCG6juPjKhSWsrUzy6ogT24VMUgcYWM87wQgxCAZRo4320f/K6bRnwuLIJENk+eZYm/D
         yQXg==
X-Gm-Message-State: AOAM530rkO/AKe8xz5/1c/n0dzumQbu5hRlztZng+fZN264fACVrbstb
        JDUZw7gTSKVI4AoCONHhLzVNoFkpUuw=
X-Google-Smtp-Source: 
 ABdhPJxvnnkermnsBPvw4vDQQcMspMPBLn164mh+/HbqfeJn6OqJVYNt2NtPxYaMdKw34BrqNa7PsA==
X-Received: by 2002:a63:c111:: with SMTP id w17mr6101708pgf.127.1618542503102;
        Thu, 15 Apr 2021 20:08:23 -0700 (PDT)
Received: from localhost.localdomain ([103.7.29.6])
        by smtp.googlemail.com with ESMTPSA id
 r1sm3654698pfh.153.2021.04.15.20.08.20
        (version=TLS1_2 cipher=ECDHE-ECDSA-AES128-GCM-SHA256 bits=128/128);
        Thu, 15 Apr 2021 20:08:22 -0700 (PDT)
From: Wanpeng Li <kernellwp@gmail.com>
X-Google-Original-From: Wanpeng Li <wanpengli@tencent.com>
To: linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Cc: Paolo Bonzini <pbonzini@redhat.com>,
        Sean Christopherson <seanjc@google.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>
Subject: [PATCH] KVM: Boost vCPU candidiate in user mode which is delivering
 interrupt
Date: Fri, 16 Apr 2021 11:08:10 +0800
Message-Id: <1618542490-14756-1-git-send-email-wanpengli@tencent.com>
X-Mailer: git-send-email 2.7.4
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Wanpeng Li <wanpengli@tencent.com>

Both lock holder vCPU and IPI receiver that has halted are condidate for 
boost. However, the PLE handler was originally designed to deal with the 
lock holder preemption problem. The Intel PLE occurs when the spinlock 
waiter is in kernel mode. This assumption doesn't hold for IPI receiver, 
they can be in either kernel or user mode. the vCPU candidate in user mode 
will not be boosted even if they should respond to IPIs. Some benchmarks 
like pbzip2, swaptions etc do the TLB shootdown in kernel mode and most
of the time they are running in user mode. It can lead to a large number 
of continuous PLE events because the IPI sender causes PLE events 
repeatedly until the receiver is scheduled while the receiver is not 
candidate for a boost.

This patch boosts the vCPU candidiate in user mode which is delivery 
interrupt. We can observe the speed of pbzip2 improves 10% in 96 vCPUs 
VM in over-subscribe scenario (The host machine is 2 socket, 48 cores, 
96 HTs Intel CLX box). There is no performance regression for other 
benchmarks like Unixbench spawn (most of the time contend read/write 
lock in kernel mode), ebizzy (most of the time contend read/write sem 
and TLB shoodtdown in kernel mode).

Signed-off-by: Wanpeng Li <wanpengli@tencent.com>
---
 arch/x86/kvm/x86.c       | 8 ++++++++
 include/linux/kvm_host.h | 1 +
 virt/kvm/kvm_main.c      | 6 ++++++
 3 files changed, 15 insertions(+)

```
#### [RFC PATCH v2 1/2] KVM: x86: Support write protect gfn with min_level
##### From: Keqian Zhu <zhukeqian1@huawei.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Keqian Zhu <zhukeqian1@huawei.com>
X-Patchwork-Id: 12206921
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.8 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT autolearn=ham
	autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id DD1DFC433B4
	for <kvm@archiver.kernel.org>; Fri, 16 Apr 2021 08:25:28 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id C50136115B
	for <kvm@archiver.kernel.org>; Fri, 16 Apr 2021 08:25:28 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S240216AbhDPIZv (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Fri, 16 Apr 2021 04:25:51 -0400
Received: from szxga06-in.huawei.com ([45.249.212.32]:17365 "EHLO
        szxga06-in.huawei.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S239119AbhDPIZu (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 16 Apr 2021 04:25:50 -0400
Received: from DGGEMS412-HUB.china.huawei.com (unknown [172.30.72.60])
        by szxga06-in.huawei.com (SkyGuard) with ESMTP id 4FM8P00bVXzlYCv;
        Fri, 16 Apr 2021 16:23:32 +0800 (CST)
Received: from DESKTOP-5IS4806.china.huawei.com (10.174.187.224) by
 DGGEMS412-HUB.china.huawei.com (10.3.19.212) with Microsoft SMTP Server id
 14.3.498.0; Fri, 16 Apr 2021 16:25:14 +0800
From: Keqian Zhu <zhukeqian1@huawei.com>
To: <linux-kernel@vger.kernel.org>, <kvm@vger.kernel.org>,
        Paolo Bonzini <pbonzini@redhat.com>,
        Sean Christopherson <seanjc@google.com>,
        Ben Gardon <bgardon@google.com>
CC: <wanghaibin.wang@huawei.com>
Subject: [RFC PATCH v2 1/2] KVM: x86: Support write protect gfn with min_level
Date: Fri, 16 Apr 2021 16:25:10 +0800
Message-ID: <20210416082511.2856-2-zhukeqian1@huawei.com>
X-Mailer: git-send-email 2.8.4.windows.1
In-Reply-To: <20210416082511.2856-1-zhukeqian1@huawei.com>
References: <20210416082511.2856-1-zhukeqian1@huawei.com>
MIME-Version: 1.0
X-Originating-IP: [10.174.187.224]
X-CFilter-Loop: Reflected
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Under some circumstances, we just need to write protect large page
gfn. This gets prepared for write protecting large page lazily during
dirty log tracking.

None function and performance change expected.

Signed-off-by: Keqian Zhu <zhukeqian1@huawei.com>
---
 arch/x86/kvm/mmu/mmu.c          |  9 +++++----
 arch/x86/kvm/mmu/mmu_internal.h |  3 ++-
 arch/x86/kvm/mmu/page_track.c   |  2 +-
 arch/x86/kvm/mmu/tdp_mmu.c      | 16 ++++++++++++----
 arch/x86/kvm/mmu/tdp_mmu.h      |  3 ++-
 5 files changed, 22 insertions(+), 11 deletions(-)

```
#### [RFCv2 01/13] x86/mm: Move force_dma_unencrypted() to common code
##### From: "Kirill A. Shutemov" <kirill.shutemov@linux.intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: "Kirill A. Shutemov" <kirill.shutemov@linux.intel.com>
X-Patchwork-Id: 12207993
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.7 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED,USER_AGENT_GIT
	autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 6E3CDC43461
	for <kvm@archiver.kernel.org>; Fri, 16 Apr 2021 15:41:40 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 4746B613A9
	for <kvm@archiver.kernel.org>; Fri, 16 Apr 2021 15:41:40 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1343905AbhDPPmD (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Fri, 16 Apr 2021 11:42:03 -0400
Received: from mga04.intel.com ([192.55.52.120]:11046 "EHLO mga04.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S235551AbhDPPmB (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 16 Apr 2021 11:42:01 -0400
IronPort-SDR: 
 35tJIDHUOoUC+co8OdFG12X5kKl2dWd3dLemK635tu4gcajP2toI36zcqLX29FMz7sBz1LAjZ2
 j+zmWxAgpumg==
X-IronPort-AV: E=McAfee;i="6200,9189,9956"; a="192931129"
X-IronPort-AV: E=Sophos;i="5.82,226,1613462400";
   d="scan'208";a="192931129"
Received: from orsmga001.jf.intel.com ([10.7.209.18])
  by fmsmga104.fm.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 16 Apr 2021 08:41:36 -0700
IronPort-SDR: 
 6IctWwvMhRST79zs3UT7X2lmhiZ2l9BRZTh8PbQxjhQJynga4+YurvugLpc+mbLJQ/BneIdPz3
 BgBVQ2QiXENA==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.82,226,1613462400";
   d="scan'208";a="461998771"
Received: from black.fi.intel.com ([10.237.72.28])
  by orsmga001.jf.intel.com with ESMTP; 16 Apr 2021 08:41:32 -0700
Received: by black.fi.intel.com (Postfix, from userid 1000)
        id CAD0EBA; Fri, 16 Apr 2021 18:41:49 +0300 (EEST)
From: "Kirill A. Shutemov" <kirill.shutemov@linux.intel.com>
To: Dave Hansen <dave.hansen@linux.intel.com>,
        Andy Lutomirski <luto@kernel.org>,
        Peter Zijlstra <peterz@infradead.org>,
        Sean Christopherson <seanjc@google.com>,
        Jim Mattson <jmattson@google.com>
Cc: David Rientjes <rientjes@google.com>,
        "Edgecombe, Rick P" <rick.p.edgecombe@intel.com>,
        "Kleen, Andi" <andi.kleen@intel.com>,
        "Yamahata, Isaku" <isaku.yamahata@intel.com>,
        Erdem Aktas <erdemaktas@google.com>,
        Steve Rutherford <srutherford@google.com>,
        Peter Gonda <pgonda@google.com>,
        David Hildenbrand <david@redhat.com>, x86@kernel.org,
        kvm@vger.kernel.org, linux-mm@kvack.org,
        linux-kernel@vger.kernel.org,
        "Kirill A. Shutemov" <kirill.shutemov@linux.intel.com>
Subject: [RFCv2 01/13] x86/mm: Move force_dma_unencrypted() to common code
Date: Fri, 16 Apr 2021 18:40:54 +0300
Message-Id: <20210416154106.23721-2-kirill.shutemov@linux.intel.com>
X-Mailer: git-send-email 2.30.2
In-Reply-To: <20210416154106.23721-1-kirill.shutemov@linux.intel.com>
References: <20210416154106.23721-1-kirill.shutemov@linux.intel.com>
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
#### [PATCH v2] tools: do not include scripts/Kbuild.include
##### From: Masahiro Yamada <masahiroy@kernel.org>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Masahiro Yamada <masahiroy@kernel.org>
X-Patchwork-Id: 12207631
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-17.0 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,INCLUDES_CR_TRAILER,INCLUDES_PATCH,MAILING_LIST_MULTI,
	SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT autolearn=unavailable
	autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 10441C43462
	for <kvm@archiver.kernel.org>; Fri, 16 Apr 2021 13:03:57 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id D805561057
	for <kvm@archiver.kernel.org>; Fri, 16 Apr 2021 13:03:56 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S235608AbhDPNES (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Fri, 16 Apr 2021 09:04:18 -0400
Received: from conuserg-10.nifty.com ([210.131.2.77]:62731 "EHLO
        conuserg-10.nifty.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S234291AbhDPNEG (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 16 Apr 2021 09:04:06 -0400
Received: from localhost.localdomain (133-32-232-101.west.xps.vectant.ne.jp
 [133.32.232.101]) (authenticated)
        by conuserg-10.nifty.com with ESMTP id 13GD0vCC002141;
        Fri, 16 Apr 2021 22:00:57 +0900
DKIM-Filter: OpenDKIM Filter v2.10.3 conuserg-10.nifty.com 13GD0vCC002141
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=nifty.com;
        s=dec2015msa; t=1618578059;
        bh=Bj3vmQYuw6AVeyGMQICNThf6rcoOcN89RQenb/sBZqc=;
        h=From:To:Cc:Subject:Date:From;
        b=cohJ7HYOsMdZ1GxI+GPzxKdV6N29fjrZk2jG+NGNstD314tHgEbG1QBPeqxMrUsyr
         7++2XZI+7lWdwgeNa4be4MW81jDO6eWRJk3EhPU7BoQ2Q9u4UoAU1Na4K+ouH8aBwq
         r3bvf4X+WQ10oGdloNZbFLbtpcbX6iHUXuvbbfcH6til8Qc1zsKomaY8HoWwPcfR4o
         bDrOpsyGuwxcIwnHtNyaiZKvlc7CU1DMChm0gv/vpRVwRclMie2D0YSh3JvTEEg6rp
         muPa6be/33bZI1soC0khkf0soRvW3ohefQLjYRjiDLNIkcMn8UCpEPn6Z507ju6Ys7
         mMSBmrcjdC8Tw==
X-Nifty-SrcIP: [133.32.232.101]
From: Masahiro Yamada <masahiroy@kernel.org>
To: linux-kbuild@vger.kernel.org
Cc: Janosch Frank <frankja@linux.ibm.com>,
        Christian Borntraeger <borntraeger@de.ibm.com>,
        Masahiro Yamada <masahiroy@kernel.org>,
        Alexei Starovoitov <ast@kernel.org>,
        Andrii Nakryiko <andrii@kernel.org>,
        Benjamin Herrenschmidt <benh@kernel.crashing.org>,
        Daniel Borkmann <daniel@iogearbox.net>,
        John Fastabend <john.fastabend@gmail.com>,
        KP Singh <kpsingh@kernel.org>, Martin KaFai Lau <kafai@fb.com>,
        Michael Ellerman <mpe@ellerman.id.au>,
        Nathan Chancellor <nathan@kernel.org>,
        Nick Desaulniers <ndesaulniers@google.com>,
        Paolo Bonzini <pbonzini@redhat.com>,
        Paul Mackerras <paulus@samba.org>,
        Shuah Khan <shuah@kernel.org>,
        Song Liu <songliubraving@fb.com>, Yonghong Song <yhs@fb.com>,
        bpf@vger.kernel.org, clang-built-linux@googlegroups.com,
        kvm@vger.kernel.org, linux-kernel@vger.kernel.org,
        linux-kselftest@vger.kernel.org, linuxppc-dev@lists.ozlabs.org,
        netdev@vger.kernel.org
Subject: [PATCH v2] tools: do not include scripts/Kbuild.include
Date: Fri, 16 Apr 2021 22:00:51 +0900
Message-Id: <20210416130051.239782-1-masahiroy@kernel.org>
X-Mailer: git-send-email 2.27.0
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Since commit d9f4ff50d2aa ("kbuild: spilt cc-option and friends to
scripts/Makefile.compiler"), some kselftests fail to build.

The tools/ directory opted out Kbuild, and went in a different
direction. They copy any kind of files to the tools/ directory
in order to do whatever they want in their world.

tools/build/Build.include mimics scripts/Kbuild.include, but some
tool Makefiles included the Kbuild one to import a feature that is
missing in tools/build/Build.include:

 - Commit ec04aa3ae87b ("tools/thermal: tmon: use "-fstack-protector"
   only if supported") included scripts/Kbuild.include from
   tools/thermal/tmon/Makefile to import the cc-option macro.

 - Commit c2390f16fc5b ("selftests: kvm: fix for compilers that do
   not support -no-pie") included scripts/Kbuild.include from
   tools/testing/selftests/kvm/Makefile to import the try-run macro.

 - Commit 9cae4ace80ef ("selftests/bpf: do not ignore clang
   failures") included scripts/Kbuild.include from
   tools/testing/selftests/bpf/Makefile to import the .DELETE_ON_ERROR
   target.

 - Commit 0695f8bca93e ("selftests/powerpc: Handle Makefile for
   unrecognized option") included scripts/Kbuild.include from
   tools/testing/selftests/powerpc/pmu/ebb/Makefile to import the
   try-run macro.

Copy what they need into tools/build/Build.include, and make them
include it instead of scripts/Kbuild.include.

Link: https://lore.kernel.org/lkml/86dadf33-70f7-a5ac-cb8c-64966d2f45a1@linux.ibm.com/
Fixes: d9f4ff50d2aa ("kbuild: spilt cc-option and friends to scripts/Makefile.compiler")
Reported-by: Janosch Frank <frankja@linux.ibm.com>
Reported-by: Christian Borntraeger <borntraeger@de.ibm.com>
Signed-off-by: Masahiro Yamada <masahiroy@kernel.org>
Tested-by: Christian Borntraeger <borntraeger@de.ibm.com>
Acked-by: Yonghong Song <yhs@fb.com>
---

Changes in v2:
  - copy macros to tools/build/BUild.include

 tools/build/Build.include                     | 24 +++++++++++++++++++
 tools/testing/selftests/bpf/Makefile          |  2 +-
 tools/testing/selftests/kvm/Makefile          |  2 +-
 .../selftests/powerpc/pmu/ebb/Makefile        |  2 +-
 tools/thermal/tmon/Makefile                   |  2 +-
 5 files changed, 28 insertions(+), 4 deletions(-)

```
#### [PATCH V3 1/3] vDPA/ifcvf: deduce VIRTIO device ID when probe
##### From: Zhu Lingshan <lingshan.zhu@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Zhu Lingshan <lingshan.zhu@intel.com>
X-Patchwork-Id: 12206803
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.8 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT autolearn=ham
	autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 939C6C433B4
	for <kvm@archiver.kernel.org>; Fri, 16 Apr 2021 07:21:58 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 72E3561152
	for <kvm@archiver.kernel.org>; Fri, 16 Apr 2021 07:21:58 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S239397AbhDPHWU (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Fri, 16 Apr 2021 03:22:20 -0400
Received: from mga14.intel.com ([192.55.52.115]:57485 "EHLO mga14.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S239271AbhDPHWT (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 16 Apr 2021 03:22:19 -0400
IronPort-SDR: 
 Q8B0mcEvdamP3GM8JEItiRNr9+l1y29W0EofoNV4MaG9GG/VGBia7PIigR77wm94auoUUxd6WB
 AogCuaob85lw==
X-IronPort-AV: E=McAfee;i="6200,9189,9955"; a="194561079"
X-IronPort-AV: E=Sophos;i="5.82,226,1613462400";
   d="scan'208";a="194561079"
Received: from orsmga008.jf.intel.com ([10.7.209.65])
  by fmsmga103.fm.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 16 Apr 2021 00:21:54 -0700
IronPort-SDR: 
 YxBEh6f2rL3mPk8q3sL17v5+jSORbc1CvFcIZN+b3TxhkMs7s2tdxkY+p5MV/daZ1eh0gfkC+3
 Us8l6ew9kWfA==
X-IronPort-AV: E=Sophos;i="5.82,226,1613462400";
   d="scan'208";a="425489762"
Received: from unknown (HELO localhost.localdomain.bj.intel.com)
 ([10.240.193.73])
  by orsmga008-auth.jf.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 16 Apr 2021 00:21:49 -0700
From: Zhu Lingshan <lingshan.zhu@intel.com>
To: jasowang@redhat.com, mst@redhat.com, lulu@redhat.com,
        sgarzare@redhat.com
Cc: virtualization@lists.linux-foundation.org, netdev@vger.kernel.org,
        kvm@vger.kernel.org, linux-kernel@vger.kernel.org,
        Zhu Lingshan <lingshan.zhu@intel.com>
Subject: [PATCH V3 1/3] vDPA/ifcvf: deduce VIRTIO device ID when probe
Date: Fri, 16 Apr 2021 15:16:26 +0800
Message-Id: <20210416071628.4984-2-lingshan.zhu@intel.com>
X-Mailer: git-send-email 2.27.0
In-Reply-To: <20210416071628.4984-1-lingshan.zhu@intel.com>
References: <20210416071628.4984-1-lingshan.zhu@intel.com>
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This commit deduces VIRTIO device ID as device type when probe,
then ifcvf_vdpa_get_device_id() can simply return the ID.
ifcvf_vdpa_get_features() and ifcvf_vdpa_get_config_size()
can work properly based on the device ID.

Signed-off-by: Zhu Lingshan <lingshan.zhu@intel.com>
---
 drivers/vdpa/ifcvf/ifcvf_base.h |  1 +
 drivers/vdpa/ifcvf/ifcvf_main.c | 30 ++++++++++++++++++------------
 2 files changed, 19 insertions(+), 12 deletions(-)

```
