#### [PATCH v4 1/3] KVM: nVMX: Sync L2 guest CET states between L1/L2
##### From: Yang Weijiang <weijiang.yang@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Yang Weijiang <weijiang.yang@intel.com>
X-Patchwork-Id: 12138511
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.8 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT autolearn=ham
	autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 8E5FBC433E9
	for <kvm@archiver.kernel.org>; Mon, 15 Mar 2021 07:07:27 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 5A81364E83
	for <kvm@archiver.kernel.org>; Mon, 15 Mar 2021 07:07:27 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S230062AbhCOHGp (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Mon, 15 Mar 2021 03:06:45 -0400
Received: from mga18.intel.com ([134.134.136.126]:59702 "EHLO mga18.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S229679AbhCOHG0 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 15 Mar 2021 03:06:26 -0400
IronPort-SDR: 
 GPMsrYpQpKu7SdupJcctCf1X9yye/QBMA0jz8PSugieMOAAqJGkG+eEKwhsMbGT8R+ioMbAPAT
 pWS0jpskx3sQ==
X-IronPort-AV: E=McAfee;i="6000,8403,9923"; a="176640934"
X-IronPort-AV: E=Sophos;i="5.81,249,1610438400";
   d="scan'208";a="176640934"
Received: from fmsmga005.fm.intel.com ([10.253.24.32])
  by orsmga106.jf.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 15 Mar 2021 00:06:26 -0700
IronPort-SDR: 
 dlQhWXWFZPiwXGCgMkwz8ZsmHCPlJGFFDhDvDzqL/61KHOTP7RGhNna7+P2zF6Qaja89WvSfDN
 5sb9D8so6A3w==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.81,249,1610438400";
   d="scan'208";a="604749544"
Received: from local-michael-cet-test.sh.intel.com ([10.239.159.166])
  by fmsmga005.fm.intel.com with ESMTP; 15 Mar 2021 00:06:24 -0700
From: Yang Weijiang <weijiang.yang@intel.com>
To: pbonzini@redhat.com, seanjc@google.com, vkuznets@redhat.com,
        kvm@vger.kernel.org, linux-kernel@vger.kernel.org
Cc: Yang Weijiang <weijiang.yang@intel.com>
Subject: [PATCH v4 1/3] KVM: nVMX: Sync L2 guest CET states between L1/L2
Date: Mon, 15 Mar 2021 15:18:39 +0800
Message-Id: <20210315071841.7045-2-weijiang.yang@intel.com>
X-Mailer: git-send-email 2.17.2
In-Reply-To: <20210315071841.7045-1-weijiang.yang@intel.com>
References: <20210315071841.7045-1-weijiang.yang@intel.com>
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

These fields are rarely updated by L1 QEMU/KVM, sync them when L1 is trying to
read/write them and after they're changed. If CET guest entry-load bit is not
set by L1 guest, migrate them to L2 manaully.

Opportunistically remove one blank line and add minor fix for MPX.

Suggested-by: Sean Christopherson <seanjc@google.com>
Signed-off-by: Yang Weijiang <weijiang.yang@intel.com>
---
 arch/x86/kvm/cpuid.c      |  1 -
 arch/x86/kvm/vmx/nested.c | 35 +++++++++++++++++++++++++++++++++--
 arch/x86/kvm/vmx/vmx.h    |  3 +++
 3 files changed, 36 insertions(+), 3 deletions(-)

```
#### [PATCH v2 1/4] KVM: x86/mmu: Fix RCU usage in handle_removed_tdp_mmu_page
##### From: Ben Gardon <bgardon@google.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Ben Gardon <bgardon@google.com>
X-Patchwork-Id: 12140401
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
	by smtp.lore.kernel.org (Postfix) with ESMTP id 717F2C433E6
	for <kvm@archiver.kernel.org>; Mon, 15 Mar 2021 18:27:38 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 43DDD64F26
	for <kvm@archiver.kernel.org>; Mon, 15 Mar 2021 18:27:38 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S232013AbhCOS1G (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Mon, 15 Mar 2021 14:27:06 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:46762 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S232062AbhCOS0z (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 15 Mar 2021 14:26:55 -0400
Received: from mail-qk1-x74a.google.com (mail-qk1-x74a.google.com
 [IPv6:2607:f8b0:4864:20::74a])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id EA738C06174A
        for <kvm@vger.kernel.org>; Mon, 15 Mar 2021 11:26:54 -0700 (PDT)
Received: by mail-qk1-x74a.google.com with SMTP id v136so25131360qkb.9
        for <kvm@vger.kernel.org>; Mon, 15 Mar 2021 11:26:54 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=date:in-reply-to:message-id:mime-version:references:subject:from:to
         :cc;
        bh=kl2EVOBmn7oQV8DsVZaFdaHri6MWqYz7gtsahKZb1Es=;
        b=Rv6NWFBPwKRKkg6EwJMIts8fimw72c/OGbtenC6IXqCfA3n83O8Dkd5ROm6ba/dSPE
         SnZXXtvDLj0FCJzCP1AgccjPahos19OWax8j+79Erkty7snq8AbSnIlgukX6CQto5i1+
         EJIBv03ENC4fvoUMfBBR+bJTrOdakjsyxpp/E8bqr3RMeN9AjDZh/ERObS6wI8GpK6JZ
         eRMaWMyO2eBSnGh5pcQxmbbgvkB9DTs2g7BndSD3Se6Q56x3Hovz4VXDw9q2YdGr6cfb
         6UAMlHtgyWtYknHs4MaQ0gvnRy0CPwmd8jKGa0px/OwowLIYOEz+B2oguy6vWGdIzwB/
         LecA==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:date:in-reply-to:message-id:mime-version
         :references:subject:from:to:cc;
        bh=kl2EVOBmn7oQV8DsVZaFdaHri6MWqYz7gtsahKZb1Es=;
        b=uN8Y5if8lWmDTAJlR2UlsqWgBUzoPSCokGZTQLUlFd5dnUj9x3yZltZqOQAa4FTALI
         HYXLkDgXJHGDobgZ9X9MW1RkhSRuozKsBhvc9r3uXmXLczKyOdU0OxUA0Ty+EPKQrL6T
         mC/rdaMoffn0bpoP9wPKyTq381bK5hiqF7+LqH2Qob0nCx04ptgs/JhYbTEkjuHVJ/cQ
         3v6DRE2E/SXPA6M45R49lGMdzkfZrUsUFo+ugsO3SRyoh1pIaIoZ9pGCzA9YO6sYYNKh
         dcvOakKzJG6YIyzsTNhbRDpqLQKeXuSQV1zkfpWTAcSgTURoxp+LSuHg4KZpDO0PWw3u
         2k7w==
X-Gm-Message-State: AOAM531e4ymVgoQ0kikgoQx/PHoTR5ucJHxWvlI3u7lJMJhcrwVP0T0N
        BkhzlGLwr0lxsYcZnyjZVCbjacEkdQ2n
X-Google-Smtp-Source: 
 ABdhPJyz4NSvQIXVCAJ7bB7UPsQH3hv1JaZPjv7eMUgMv/o/R6Al3q67ItDwhcs0ZfqoPuTTjMqaimXw8NZ2
X-Received: from bgardon.sea.corp.google.com
 ([2620:15c:100:202:888a:4e22:67:844a])
 (user=bgardon job=sendgmr) by 2002:a05:6214:aa6:: with SMTP id
 ew6mr12058104qvb.2.1615832814124; Mon, 15 Mar 2021 11:26:54 -0700 (PDT)
Date: Mon, 15 Mar 2021 11:26:40 -0700
In-Reply-To: <20210315182643.2437374-1-bgardon@google.com>
Message-Id: <20210315182643.2437374-2-bgardon@google.com>
Mime-Version: 1.0
References: <20210315182643.2437374-1-bgardon@google.com>
X-Mailer: git-send-email 2.31.0.rc2.261.g7f71774620-goog
Subject: [PATCH v2 1/4] KVM: x86/mmu: Fix RCU usage in
 handle_removed_tdp_mmu_page
From: Ben Gardon <bgardon@google.com>
To: linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Cc: Paolo Bonzini <pbonzini@redhat.com>,
        Sean Christopherson <seanjc@google.com>,
        Peter Shier <pshier@google.com>,
        Jim Mattson <jmattson@google.com>,
        Ben Gardon <bgardon@google.com>,
        kernel test robot <lkp@intel.com>
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The pt passed into handle_removed_tdp_mmu_page does not need RCU
protection, as it is not at any risk of being freed by another thread at
that point. However, the implicit cast from tdp_sptep_t to u64 * dropped
the __rcu annotation without a proper rcu_derefrence. Fix this by
passing the pt as a tdp_ptep_t and then rcu_dereferencing it in
the function.

Suggested-by: Sean Christopherson <seanjc@google.com>
Reported-by: kernel test robot <lkp@intel.com>
Signed-off-by: Ben Gardon <bgardon@google.com>
---
 arch/x86/kvm/mmu/tdp_mmu.c | 11 ++++++++---
 1 file changed, 8 insertions(+), 3 deletions(-)

```
#### [PATCH v5 01/11] file: Export __receive_fd() to modules
##### From: Xie Yongji <xieyongji@bytedance.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Yongji Xie <xieyongji@bytedance.com>
X-Patchwork-Id: 12138313
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.8 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT
	autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id F198FC433E6
	for <kvm@archiver.kernel.org>; Mon, 15 Mar 2021 05:38:41 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id C740364E0F
	for <kvm@archiver.kernel.org>; Mon, 15 Mar 2021 05:38:41 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S230097AbhCOFiL (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Mon, 15 Mar 2021 01:38:11 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:49412 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S229925AbhCOFhy (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 15 Mar 2021 01:37:54 -0400
Received: from mail-pl1-x631.google.com (mail-pl1-x631.google.com
 [IPv6:2607:f8b0:4864:20::631])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 7BAC5C061762
        for <kvm@vger.kernel.org>; Sun, 14 Mar 2021 22:37:54 -0700 (PDT)
Received: by mail-pl1-x631.google.com with SMTP id w7so11231135pll.8
        for <kvm@vger.kernel.org>; Sun, 14 Mar 2021 22:37:54 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=bytedance-com.20150623.gappssmtp.com; s=20150623;
        h=from:to:cc:subject:date:message-id:in-reply-to:references
         :mime-version:content-transfer-encoding;
        bh=aYq0J+9b4tKDZXBHw2wOWvtavxgBRahDPr03liFECw0=;
        b=puwumHcKmr61wNYUFotpbK2IfHnTbHcpCnzievNuhMmjO4+Eo52l2U71CPjXORPQz0
         YWaZVO/rDFNIZGuUgdkCM/DYmhSJACrGuGbgZ96S0h8GYCQo6udNxn/gTu3jjeOrPW7W
         hVbFsIw4Q4NwTZtm31kC2rzC+rWg9rO4G5tG79ebQG6fU5JB9zEI0EEx75Cx+YFRO6IT
         As3HPa1UlB63m9oLqpFab0cmMrrodrVeOKP/AkxkFjU5tWMyxjzRvXIYkER++lr4Q7zv
         l/oDALFuxF6tADxCV5wqSCQc+zPtkKBdt0k5n/nVcBHSOyLMB23OQQcHkXC8zoumc/tL
         RIAQ==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:in-reply-to
         :references:mime-version:content-transfer-encoding;
        bh=aYq0J+9b4tKDZXBHw2wOWvtavxgBRahDPr03liFECw0=;
        b=W60rtSFgVo5B8merGTm0zCVq7kSyzEkHnEKt2uK+9prcn6hPZ1wpiZQ9CKwwHH3Rhn
         r3fgEMn5hDs6/t7JYJWolFW+A4ggJvCiDmED9pnCqMdHFZpIl67hgycNvH5yNCUYwrFD
         mgGfYplbDNRv6iVm5JybdHV38RrebdrEVWJu5siNCp/IWk8Ym+VC/t+2jFJAZOFUxMvh
         FtvmB3m64/5SQgXqnISYegLTmFpR8J2QLeK2YxPy8EzIlVQv2hCkEIbKgpD/BoKEgneo
         CYkw0CzaJvS+lz7su5pDb3gjIFVwnLTuhWutIHPB7yW8rY3Oe9VbWCEU2x4wVHAatdSf
         PBrg==
X-Gm-Message-State: AOAM5300RyNL8hZZvqjuV5O3TxOmKYLLtFjjUmXOgxf45IHybMOX+laS
        4BkxbzeBCytucjWuf25pNl/P
X-Google-Smtp-Source: 
 ABdhPJy4+A1RYkcNV8xwLGkTiZKllYZiilY4Bu0DGetxutWdy9edDqFjAl4qPO0fDEr21OfnR4xE2Q==
X-Received: by 2002:a17:902:ecc3:b029:e5:d7cc:2a20 with SMTP id
 a3-20020a170902ecc3b02900e5d7cc2a20mr9865008plh.11.1615786674068;
        Sun, 14 Mar 2021 22:37:54 -0700 (PDT)
Received: from localhost ([139.177.225.227])
        by smtp.gmail.com with ESMTPSA id
 h16sm8544215pfc.194.2021.03.14.22.37.53
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Sun, 14 Mar 2021 22:37:53 -0700 (PDT)
From: Xie Yongji <xieyongji@bytedance.com>
To: mst@redhat.com, jasowang@redhat.com, stefanha@redhat.com,
        sgarzare@redhat.com, parav@nvidia.com, bob.liu@oracle.com,
        hch@infradead.org, rdunlap@infradead.org, willy@infradead.org,
        viro@zeniv.linux.org.uk, axboe@kernel.dk, bcrl@kvack.org,
        corbet@lwn.net, mika.penttila@nextfour.com,
        dan.carpenter@oracle.com
Cc: virtualization@lists.linux-foundation.org, netdev@vger.kernel.org,
        kvm@vger.kernel.org, linux-fsdevel@vger.kernel.org
Subject: [PATCH v5 01/11] file: Export __receive_fd() to modules
Date: Mon, 15 Mar 2021 13:37:11 +0800
Message-Id: <20210315053721.189-2-xieyongji@bytedance.com>
X-Mailer: git-send-email 2.25.1
In-Reply-To: <20210315053721.189-1-xieyongji@bytedance.com>
References: <20210315053721.189-1-xieyongji@bytedance.com>
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Export __receive_fd() so that some modules can use
it to pass file descriptor between processes.

Signed-off-by: Xie Yongji <xieyongji@bytedance.com>
---
 fs/file.c | 1 +
 1 file changed, 1 insertion(+)

```
#### [PATCH 1/3] scripts/gdb: rework lx-symbols gdb script
##### From: Maxim Levitsky <mlevitsk@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Maxim Levitsky <mlevitsk@redhat.com>
X-Patchwork-Id: 12140757
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.0 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_CR_TRAILER,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS
	autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 189F2C4332B
	for <kvm@archiver.kernel.org>; Mon, 15 Mar 2021 22:11:14 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id E11D964F5F
	for <kvm@archiver.kernel.org>; Mon, 15 Mar 2021 22:11:13 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S232445AbhCOWKm (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Mon, 15 Mar 2021 18:10:42 -0400
Received: from us-smtp-delivery-124.mimecast.com ([63.128.21.124]:38779 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S232626AbhCOWKg (ORCPT
        <rfc822;kvm@vger.kernel.org>); Mon, 15 Mar 2021 18:10:36 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1615846235;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding:
         in-reply-to:in-reply-to:references:references;
        bh=xs80L4S7if4oQ7sYgkwvzm47LtF8hDXaNV9qxN93CWM=;
        b=b8mnflWXZcOn24vmjjM1zqqmAo1SEIpzz3IZPaVVUVsPqOmtAUjek0vRCR28aCpETAvShM
        HhAkyg5B7t3zCTqz/AsNFFzp0g9vrLc8OP8qZ3h08fTS7KlUDuHSmYtQl4LGmzqzrWzSDC
        6ylkUZbL+IcVAawzCudbYZHHl46Sbn8=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-474-3JeqLqiZM1GMdXfm4fr1Wg-1; Mon, 15 Mar 2021 18:10:33 -0400
X-MC-Unique: 3JeqLqiZM1GMdXfm4fr1Wg-1
Received: from smtp.corp.redhat.com (int-mx06.intmail.prod.int.phx2.redhat.com
 [10.5.11.16])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 997BC87A826;
        Mon, 15 Mar 2021 22:10:31 +0000 (UTC)
Received: from localhost.localdomain (unknown [10.35.207.30])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 416DA5E1A4;
        Mon, 15 Mar 2021 22:10:27 +0000 (UTC)
From: Maxim Levitsky <mlevitsk@redhat.com>
To: kvm@vger.kernel.org
Cc: Vitaly Kuznetsov <vkuznets@redhat.com>,
        linux-kernel@vger.kernel.org, Thomas Gleixner <tglx@linutronix.de>,
        Wanpeng Li <wanpengli@tencent.com>,
        Kieran Bingham <kbingham@kernel.org>,
        Jessica Yu <jeyu@kernel.org>,
        Jan Kiszka <jan.kiszka@siemens.com>,
        Andrew Morton <akpm@linux-foundation.org>,
        x86@kernel.org (maintainer:X86 ARCHITECTURE (32-BIT AND 64-BIT)),
        Joerg Roedel <joro@8bytes.org>,
        Sean Christopherson <seanjc@google.com>,
        Jim Mattson <jmattson@google.com>,
        Borislav Petkov <bp@alien8.de>,
        Stefano Garzarella <sgarzare@redhat.com>,
        Maxim Levitsky <mlevitsk@redhat.com>,
        "H. Peter Anvin" <hpa@zytor.com>,
        Paolo Bonzini <pbonzini@redhat.com>,
        Ingo Molnar <mingo@redhat.com>
Subject: [PATCH 1/3] scripts/gdb: rework lx-symbols gdb script
Date: Tue, 16 Mar 2021 00:10:18 +0200
Message-Id: <20210315221020.661693-2-mlevitsk@redhat.com>
In-Reply-To: <20210315221020.661693-1-mlevitsk@redhat.com>
References: <20210315221020.661693-1-mlevitsk@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.16
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Fix several issues that are present in lx-symbols script:

* Track module unloads by placing another software breakpoint at 'free_module'
  (force uninline this symbol just in case), and use remove-symbol-file
  gdb command to unload the symobls of the module that is unloading.

  That gives the gdb a chance to mark all software breakpoints from
  this module as pending again.
  Also remove the module from the 'known' module list once it is unloaded.

* Since we now track module unload, we don't need to reload all
  symbols anymore when 'known' module loaded again (that can't happen anymore).
  This allows reloading a module in the debugged kernel to finish much faster,
  while lx-symbols tracks module loads and unloads.

* Disable/enable all gdb breakpoints on both module load and unload breakpoint
  hits, and not only in 'load_all_symbols' as was done before.
  (load_all_symbols is no longer called on breakpoint hit)
  That allows gdb to avoid getting confused about the state of the (now two)
  internal breakpoints we place.

  Otherwise it will leave them in the kernel code segment, when continuing
  which triggers a guest kernel panic as soon as it skips over the 'int3'
  instruction and executes the garbage tail of the optcode on which
  the breakpoint was placed.

Signed-off-by: Maxim Levitsky <mlevitsk@redhat.com>
---
 kernel/module.c              |   8 ++-
 scripts/gdb/linux/symbols.py | 106 +++++++++++++++++++++++++----------
 2 files changed, 83 insertions(+), 31 deletions(-)

```
#### [PATCH 1/4] KVM: x86: hyper-v: Limit guest to writing zero to HV_X64_MSR_TSC_EMULATION_STATUS
##### From: Vitaly Kuznetsov <vkuznets@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Vitaly Kuznetsov <vkuznets@redhat.com>
X-Patchwork-Id: 12139669
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.0 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_CR_TRAILER,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS
	autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 85C41C41621
	for <kvm@archiver.kernel.org>; Mon, 15 Mar 2021 14:39:09 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 710D264F1A
	for <kvm@archiver.kernel.org>; Mon, 15 Mar 2021 14:39:09 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S233343AbhCOOih (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Mon, 15 Mar 2021 10:38:37 -0400
Received: from us-smtp-delivery-124.mimecast.com ([63.128.21.124]:57079 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S239526AbhCOOhS (ORCPT
        <rfc822;kvm@vger.kernel.org>); Mon, 15 Mar 2021 10:37:18 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1615819037;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding:
         in-reply-to:in-reply-to:references:references;
        bh=O5Co9d4ozrTngCdGCM1S57GEotFMyYjlIiNeBZ4sqxk=;
        b=h/y4RDRqbhVbyTehf8d12v62U+fddJGdoRUSxKRFm7qWekwNUpIdyPDTXy26tWVGLgWw3B
        Z3Rs63n9jLqJF9osvhWFH9pLjrUYgm5hQERoi4/9wxmCYvL0rFQtRQlCbmmckLogNSR1Oc
        78NAZZHqFtcuZfmwgXhzpZ4tJivnPxA=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-578-c6DaTcNyO3aTxQeaW05zmw-1; Mon, 15 Mar 2021 10:37:13 -0400
X-MC-Unique: c6DaTcNyO3aTxQeaW05zmw-1
Received: from smtp.corp.redhat.com (int-mx06.intmail.prod.int.phx2.redhat.com
 [10.5.11.16])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 5199C18460E1;
        Mon, 15 Mar 2021 14:37:12 +0000 (UTC)
Received: from vitty.brq.redhat.com (unknown [10.40.195.229])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 3FDAB5C3E6;
        Mon, 15 Mar 2021 14:37:10 +0000 (UTC)
From: Vitaly Kuznetsov <vkuznets@redhat.com>
To: kvm@vger.kernel.org, Paolo Bonzini <pbonzini@redhat.com>
Cc: Sean Christopherson <seanjc@google.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Marcelo Tosatti <mtosatti@redhat.com>
Subject: [PATCH 1/4] KVM: x86: hyper-v: Limit guest to writing zero to
 HV_X64_MSR_TSC_EMULATION_STATUS
Date: Mon, 15 Mar 2021 15:37:03 +0100
Message-Id: <20210315143706.859293-2-vkuznets@redhat.com>
In-Reply-To: <20210315143706.859293-1-vkuznets@redhat.com>
References: <20210315143706.859293-1-vkuznets@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.16
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

HV_X64_MSR_TSC_EMULATION_STATUS indicates whether TSC accesses are emulated
after migration (to accommodate for a different host TSC frequency when TSC
scaling is not supported; we don't implement this in KVM). Guest can use
the same MSR to stop TSC access emulation by writing zero. Writing anything
else is forbidden.

Signed-off-by: Vitaly Kuznetsov <vkuznets@redhat.com>
---
 arch/x86/kvm/hyperv.c | 3 +++
 1 file changed, 3 insertions(+)

```
#### [PATCH 1/2] KVM: x86: add guest_cpuid_is_intel
##### From: Maxim Levitsky <mlevitsk@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Maxim Levitsky <mlevitsk@redhat.com>
X-Patchwork-Id: 12140297
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.0 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_CR_TRAILER,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS
	autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id E852EC41621
	for <kvm@archiver.kernel.org>; Mon, 15 Mar 2021 17:56:39 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id ACDF264F19
	for <kvm@archiver.kernel.org>; Mon, 15 Mar 2021 17:56:39 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S230483AbhCOR4F (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Mon, 15 Mar 2021 13:56:05 -0400
Received: from us-smtp-delivery-124.mimecast.com ([63.128.21.124]:58746 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S233226AbhCORsk (ORCPT
        <rfc822;kvm@vger.kernel.org>); Mon, 15 Mar 2021 13:48:40 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1615830340;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding:
         in-reply-to:in-reply-to:references:references;
        bh=EX+ALS8Rj+snqWS2FtcSfbGlgufu6nW8i+0NGRRz9/Y=;
        b=LREaBbHlkjNYprHobWQhaP+8m6C11+6g6TJcqvtjxjbUeAcUgFyhxO7snRn+2IpV051YSb
        ygZIUS8V4j6Itm0lLseQx/NgENg/G0tbex4MrV6fensC+4+JVJHsOp95Wr1pmBmB1+9y+7
        jWXQK9ub3imAxrQRMO5DHzNakLvnlAM=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-371-Np11tximNTGdide50AUZXA-1; Mon, 15 Mar 2021 13:43:28 -0400
X-MC-Unique: Np11tximNTGdide50AUZXA-1
Received: from smtp.corp.redhat.com (int-mx05.intmail.prod.int.phx2.redhat.com
 [10.5.11.15])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id CAE02801817;
        Mon, 15 Mar 2021 17:43:25 +0000 (UTC)
Received: from localhost.localdomain (unknown [10.35.207.30])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 384145D745;
        Mon, 15 Mar 2021 17:43:22 +0000 (UTC)
From: Maxim Levitsky <mlevitsk@redhat.com>
To: kvm@vger.kernel.org
Cc: x86@kernel.org (maintainer:X86 ARCHITECTURE (32-BIT AND 64-BIT)),
        "H. Peter Anvin" <hpa@zytor.com>,
        Sean Christopherson <seanjc@google.com>,
        Ingo Molnar <mingo@redhat.com>,
        Jim Mattson <jmattson@google.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Joerg Roedel <joro@8bytes.org>,
        Paolo Bonzini <pbonzini@redhat.com>,
        Thomas Gleixner <tglx@linutronix.de>,
        linux-kernel@vger.kernel.org (open list:X86 ARCHITECTURE (32-BIT AND
        64-BIT)), Wanpeng Li <wanpengli@tencent.com>,
        Borislav Petkov <bp@alien8.de>,
        Maxim Levitsky <mlevitsk@redhat.com>
Subject: [PATCH 1/2] KVM: x86: add guest_cpuid_is_intel
Date: Mon, 15 Mar 2021 19:43:15 +0200
Message-Id: <20210315174316.477511-2-mlevitsk@redhat.com>
In-Reply-To: <20210315174316.477511-1-mlevitsk@redhat.com>
References: <20210315174316.477511-1-mlevitsk@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.15
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This is similar to existing 'guest_cpuid_is_amd_or_hygon'

Signed-off-by: Maxim Levitsky <mlevitsk@redhat.com>
---
 arch/x86/kvm/cpuid.h | 8 ++++++++
 1 file changed, 8 insertions(+)

```
#### [PATCH v2 1/2] x86/msr: run this test with intel vendor id
##### From: Maxim Levitsky <mlevitsk@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Maxim Levitsky <mlevitsk@redhat.com>
X-Patchwork-Id: 12140713
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.0 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_CR_TRAILER,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS
	autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id CDAECC433DB
	for <kvm@archiver.kernel.org>; Mon, 15 Mar 2021 21:10:24 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 7E85964F0F
	for <kvm@archiver.kernel.org>; Mon, 15 Mar 2021 21:10:24 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S233362AbhCOVJx (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Mon, 15 Mar 2021 17:09:53 -0400
Received: from us-smtp-delivery-124.mimecast.com ([216.205.24.124]:42421 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S234094AbhCOVJ2 (ORCPT
        <rfc822;kvm@vger.kernel.org>); Mon, 15 Mar 2021 17:09:28 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1615842567;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding:
         in-reply-to:in-reply-to:references:references;
        bh=Q6pYNXzlBUy6CQUTp7+4XJuVu3ymwKliQzSLa0SUmY8=;
        b=W0juX1kI87sZQWQLTnH0GIoyaBRc3X3/zylGljvVu9ro/+UK37ahki9J3y2QGF7+/kJyjm
        20CCiI7lnF6iy8mMEpZ2e0tGdum6MJrNi79jyRTkh8NOewAic19mHsiHfTC2Q8qrJgFRPU
        Sf+NkF/UbzK20x9HswgNqKoByT8MCo4=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-333-9dSY1uLMOseTgeBMeVdyMA-1; Mon, 15 Mar 2021 17:09:26 -0400
X-MC-Unique: 9dSY1uLMOseTgeBMeVdyMA-1
Received: from smtp.corp.redhat.com (int-mx02.intmail.prod.int.phx2.redhat.com
 [10.5.11.12])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id F00AE87A83C
        for <kvm@vger.kernel.org>; Mon, 15 Mar 2021 21:09:24 +0000 (UTC)
Received: from localhost.localdomain (unknown [10.35.207.30])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 2583460C0F;
        Mon, 15 Mar 2021 21:09:23 +0000 (UTC)
From: Maxim Levitsky <mlevitsk@redhat.com>
To: kvm@vger.kernel.org
Cc: Maxim Levitsky <mlevitsk@redhat.com>
Subject: [PATCH v2 1/2] x86/msr: run this test with intel vendor id
Date: Mon, 15 Mar 2021 23:09:20 +0200
Message-Id: <20210315210921.626351-2-mlevitsk@redhat.com>
In-Reply-To: <20210315210921.626351-1-mlevitsk@redhat.com>
References: <20210315210921.626351-1-mlevitsk@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.12
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Part of this test, tests that sysenter msrs are 64 bit wide
which is only true on Intel.

We emulate Intel variant of SYSENTER in KVM when
Intel's vendor ID is used to help with cross-vendor migration,
which includes extending SYSENTER msrs to 64 bit.

The later was done unconditionally which soon will be limited
to VMs which use Intel's vendor ID.

So run the test with Intel's vendor ID so it continues to pass.

Signed-off-by: Maxim Levitsky <mlevitsk@redhat.com>
---
 x86/unittests.cfg | 1 +
 1 file changed, 1 insertion(+)

```
#### [PATCH kvmtool v3 01/22] ioport: Remove ioport__setup_arch()
##### From: Andre Przywara <andre.przywara@arm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Andre Przywara <andre.przywara@arm.com>
X-Patchwork-Id: 12139823
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.8 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT
	autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id F0368C433E6
	for <kvm@archiver.kernel.org>; Mon, 15 Mar 2021 15:34:56 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id C2C8964E64
	for <kvm@archiver.kernel.org>; Mon, 15 Mar 2021 15:34:56 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S231145AbhCOPeX (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Mon, 15 Mar 2021 11:34:23 -0400
Received: from foss.arm.com ([217.140.110.172]:50618 "EHLO foss.arm.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S230242AbhCOPeN (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 15 Mar 2021 11:34:13 -0400
Received: from usa-sjc-imap-foss1.foss.arm.com (unknown [10.121.207.14])
        by usa-sjc-mx-foss1.foss.arm.com (Postfix) with ESMTP id C680ED6E;
        Mon, 15 Mar 2021 08:34:12 -0700 (PDT)
Received: from localhost.localdomain (unknown [172.31.20.19])
        by usa-sjc-imap-foss1.foss.arm.com (Postfix) with ESMTPSA id
 717D53F792;
        Mon, 15 Mar 2021 08:34:11 -0700 (PDT)
From: Andre Przywara <andre.przywara@arm.com>
To: Will Deacon <will@kernel.org>,
        Julien Thierry <julien.thierry.kdev@gmail.com>
Cc: Alexandru Elisei <alexandru.elisei@arm.com>, kvm@vger.kernel.org,
        kvmarm@lists.cs.columbia.edu, Marc Zyngier <maz@kernel.org>,
        Sami Mujawar <sami.mujawar@arm.com>
Subject: [PATCH kvmtool v3 01/22] ioport: Remove ioport__setup_arch()
Date: Mon, 15 Mar 2021 15:33:29 +0000
Message-Id: <20210315153350.19988-2-andre.przywara@arm.com>
X-Mailer: git-send-email 2.14.1
In-Reply-To: <20210315153350.19988-1-andre.przywara@arm.com>
References: <20210315153350.19988-1-andre.przywara@arm.com>
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Since x86 had a special need for registering tons of special I/O ports,
we had an ioport__setup_arch() callback, to allow each architecture
to do the same. As it turns out no one uses it beside x86, so we remove
that unnecessary abstraction.

The generic function was registered via a device_base_init() call, so
we just do the same for the x86 specific function only, and can remove
the unneeded ioport__setup_arch().

Signed-off-by: Andre Przywara <andre.przywara@arm.com>
Reviewed-by: Alexandru Elisei <alexandru.elisei@arm.com>
---
 arm/ioport.c         | 5 -----
 include/kvm/ioport.h | 1 -
 ioport.c             | 6 ------
 mips/kvm.c           | 5 -----
 powerpc/ioport.c     | 6 ------
 x86/ioport.c         | 3 ++-
 6 files changed, 2 insertions(+), 24 deletions(-)

```
#### [PATCH v3] x86/kvm: Fix broken irq restoration in kvm_wait
##### From: Wanpeng Li <kernellwp@gmail.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Wanpeng Li <kernellwp@gmail.com>
X-Patchwork-Id: 12138495
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
	by smtp.lore.kernel.org (Postfix) with ESMTP id 18196C433DB
	for <kvm@archiver.kernel.org>; Mon, 15 Mar 2021 06:56:21 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id D83E864E4A
	for <kvm@archiver.kernel.org>; Mon, 15 Mar 2021 06:56:20 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S230002AbhCOGzu (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Mon, 15 Mar 2021 02:55:50 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:37888 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S229607AbhCOGzk (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 15 Mar 2021 02:55:40 -0400
Received: from mail-pf1-x42f.google.com (mail-pf1-x42f.google.com
 [IPv6:2607:f8b0:4864:20::42f])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 02468C061574;
        Sun, 14 Mar 2021 23:55:40 -0700 (PDT)
Received: by mail-pf1-x42f.google.com with SMTP id s21so5976696pfm.1;
        Sun, 14 Mar 2021 23:55:39 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=from:to:cc:subject:date:message-id;
        bh=pNjaEjC60Q50gikxhUdZUYYiIOugeurKbAsBaEi4TgQ=;
        b=lwwxmO78ifaVyeZUWmN3XOkuZbwXbDBvkuTkkBOSMjIa3RcS4ZqRcq4Zv/f5zvAsWK
         rcI0F9ZuovKEDRMmOeKsWbRAQ3xhfA9Y6Gy251QVoTQk4wDodNLrBnfwC+TxG4HK3KZN
         iX7h5jrkvbU/X8xYERzsjm0NMMZHjZd3SDgoVMOmuuGT0nUtNt6j2970YWjFUiR5cFME
         azcYeTZg4yCTWYRslsIH+1m8Oc4N4ji6AZM1yZkBJtp9jeWa4xHtJPuIvPyATavGCL31
         SztSbTIYpJDyQk3aQiGFICbuGs2SHByfpuLaExh5YrrtzP2gobnA88FjxrfhQbsgs9Zx
         N0bA==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id;
        bh=pNjaEjC60Q50gikxhUdZUYYiIOugeurKbAsBaEi4TgQ=;
        b=t2bXHCLdbjw0bUw3pCzb4woHziXpTWYfrtdAy/QhsCsOXi2E4YJym/clRa5kgVGnMN
         MT2mjlmO4vChG3UgVmGps8pM3a/Kyv6KQLJ2e5vk5TsJY/Eslu9kFEtNVFUXcZ8uWGJT
         0n+VYbSb+g0fjNCIpAS68sEheY+zZaKEAy6WR8LJJ82iL1+2OPQfoVA6t88cykK+eh6B
         lDvTvWappHLYOHt39PFR25h0Q4ShUjq0ExsznGnCNTFku+uLM6dpTUvsiTNK2rjTx/62
         XIc7vMsoIjtsRSj0zpkMb/fhqSRHM+bvJtOVbt9lZrOzyVk0IM/pvSfLny7EXmGELuho
         tK3g==
X-Gm-Message-State: AOAM5337EK9LZ1wPrnt7OMxwsEmSJVxZDUqlBOCns35r3yYgztzXcYJF
        8HN3F1pJYbRcKizEzOwlCZqczxne37M=
X-Google-Smtp-Source: 
 ABdhPJx6nLjQ+jnlByTPf5t/X5LY01MFQoPvhbltV13isKRo0OzMMlhpJUIzSW+fXGK7Ka3e3zYkfw==
X-Received: by 2002:a63:5c23:: with SMTP id
 q35mr22171258pgb.418.1615791339092;
        Sun, 14 Mar 2021 23:55:39 -0700 (PDT)
Received: from localhost.localdomain ([103.7.29.6])
        by smtp.googlemail.com with ESMTPSA id
 y20sm12472413pfo.210.2021.03.14.23.55.36
        (version=TLS1_2 cipher=ECDHE-ECDSA-AES128-GCM-SHA256 bits=128/128);
        Sun, 14 Mar 2021 23:55:38 -0700 (PDT)
From: Wanpeng Li <kernellwp@gmail.com>
X-Google-Original-From: Wanpeng Li <wanpengli@tencent.com>
To: linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Cc: Paolo Bonzini <pbonzini@redhat.com>,
        Sean Christopherson <seanjc@google.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>,
        Mark Rutland <mark.rutland@arm.com>,
        Thomas Gleixner <tglx@linutronix.de>
Subject: [PATCH v3] x86/kvm: Fix broken irq restoration in kvm_wait
Date: Mon, 15 Mar 2021 14:55:28 +0800
Message-Id: <1615791328-2735-1-git-send-email-wanpengli@tencent.com>
X-Mailer: git-send-email 2.7.4
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Wanpeng Li <wanpengli@tencent.com>

After commit 997acaf6b4b59c (lockdep: report broken irq restoration), the guest 
splatting below during boot:

 raw_local_irq_restore() called with IRQs enabled
 WARNING: CPU: 1 PID: 169 at kernel/locking/irqflag-debug.c:10 warn_bogus_irq_restore+0x26/0x30
 Modules linked in: hid_generic usbhid hid
 CPU: 1 PID: 169 Comm: systemd-udevd Not tainted 5.11.0+ #25
 RIP: 0010:warn_bogus_irq_restore+0x26/0x30
 Call Trace:
  kvm_wait+0x76/0x90
  __pv_queued_spin_lock_slowpath+0x285/0x2e0
  do_raw_spin_lock+0xc9/0xd0
  _raw_spin_lock+0x59/0x70
  lockref_get_not_dead+0xf/0x50
  __legitimize_path+0x31/0x60
  legitimize_root+0x37/0x50
  try_to_unlazy_next+0x7f/0x1d0
  lookup_fast+0xb0/0x170
  path_openat+0x165/0x9b0
  do_filp_open+0x99/0x110
  do_sys_openat2+0x1f1/0x2e0
  do_sys_open+0x5c/0x80
  __x64_sys_open+0x21/0x30
  do_syscall_64+0x32/0x50
  entry_SYSCALL_64_after_hwframe+0x44/0xae

The irqflags handling in kvm_wait() which ends up doing:

	local_irq_save(flags);
	safe_halt();
	local_irq_restore(flags);

which triggered a new consistency checking, we generally expect 
local_irq_save() and local_irq_restore() to be pared and sanely 
nested, and so local_irq_restore() expects to be called with 
irqs disabled. 

This patch fixes it by playing local_irq_disable()/enable() directly.

Cc: Mark Rutland <mark.rutland@arm.com>
Cc: Thomas Gleixner <tglx@linutronix.de>
Signed-off-by: Wanpeng Li <wanpengli@tencent.com>
---
v2 -> v3:
 * per Sean's suggestion

 arch/x86/kernel/kvm.c | 23 ++++++++++-------------
 1 file changed, 10 insertions(+), 13 deletions(-)

```
#### [PATCH v4 01/14] vdpa_sim: use iova module to allocate IOVA addresses
##### From: Stefano Garzarella <sgarzare@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Stefano Garzarella <sgarzare@redhat.com>
X-Patchwork-Id: 12140005
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.0 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_CR_TRAILER,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS
	autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id D04E7C4332B
	for <kvm@archiver.kernel.org>; Mon, 15 Mar 2021 16:35:47 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id A5F4E64F2A
	for <kvm@archiver.kernel.org>; Mon, 15 Mar 2021 16:35:47 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S232386AbhCOQfQ (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Mon, 15 Mar 2021 12:35:16 -0400
Received: from us-smtp-delivery-124.mimecast.com ([63.128.21.124]:46231 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S232371AbhCOQfJ (ORCPT
        <rfc822;kvm@vger.kernel.org>); Mon, 15 Mar 2021 12:35:09 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1615826108;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding:
         in-reply-to:in-reply-to:references:references;
        bh=f8kPzMA8SARyFAt9L8z9nU43ZH3TNeJLbjn6RnMoeoU=;
        b=A5sZZzIlP3VjModfXlrK0ozBr/Nb0KtqVEPdTcN+Bvumm+bZcMtPy8JZQ7UDAZxLfuPLyU
        vgr83Q05aVar9KSqTTFKf3uLur+E7Qqw8cTt770P1/ztikYkawK8Zx7KmqHwQtEP8nd5mB
        98S9ncbFz/dlOkNxJnUM6DYEnlVBq1g=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-504-bItcXqIMOJ2H5IdAgXMv-g-1; Mon, 15 Mar 2021 12:35:04 -0400
X-MC-Unique: bItcXqIMOJ2H5IdAgXMv-g-1
Received: from smtp.corp.redhat.com (int-mx08.intmail.prod.int.phx2.redhat.com
 [10.5.11.23])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id AAB5E108BD06;
        Mon, 15 Mar 2021 16:35:02 +0000 (UTC)
Received: from steredhat.redhat.com (ovpn-114-1.ams2.redhat.com [10.36.114.1])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 3A40319D7C;
        Mon, 15 Mar 2021 16:35:00 +0000 (UTC)
From: Stefano Garzarella <sgarzare@redhat.com>
To: virtualization@lists.linux-foundation.org
Cc: netdev@vger.kernel.org, Xie Yongji <xieyongji@bytedance.com>,
        Laurent Vivier <lvivier@redhat.com>,
        Stefan Hajnoczi <stefanha@redhat.com>,
        linux-kernel@vger.kernel.org, Max Gurtovoy <mgurtovoy@nvidia.com>,
        Jason Wang <jasowang@redhat.com>,
        Parav Pandit <parav@nvidia.com>,
        "Michael S. Tsirkin" <mst@redhat.com>, kvm@vger.kernel.org
Subject: [PATCH v4 01/14] vdpa_sim: use iova module to allocate IOVA addresses
Date: Mon, 15 Mar 2021 17:34:37 +0100
Message-Id: <20210315163450.254396-2-sgarzare@redhat.com>
In-Reply-To: <20210315163450.254396-1-sgarzare@redhat.com>
References: <20210315163450.254396-1-sgarzare@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.84 on 10.5.11.23
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The identical mapping used until now created issues when mapping
different virtual pages with the same physical address.
To solve this issue, we can use the iova module, to handle the IOVA
allocation.
For simplicity we use an IOVA allocator with byte granularity.

We add two new functions, vdpasim_map_range() and vdpasim_unmap_range(),
to handle the IOVA allocation and the registration into the IOMMU/IOTLB.
These functions are used by dma_map_ops callbacks.

Acked-by: Jason Wang <jasowang@redhat.com>
Signed-off-by: Stefano Garzarella <sgarzare@redhat.com>
---
v2:
- used ULONG_MAX instead of ~0UL [Jason]
- fixed typos in comment and patch description [Jason]
---
 drivers/vdpa/vdpa_sim/vdpa_sim.h |   2 +
 drivers/vdpa/vdpa_sim/vdpa_sim.c | 108 +++++++++++++++++++------------
 drivers/vdpa/Kconfig             |   1 +
 3 files changed, 69 insertions(+), 42 deletions(-)

```
#### [PATCH V4 1/7] vDPA/ifcvf: get_vendor_id returns a device specific vendor id
##### From: Zhu Lingshan <lingshan.zhu@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Zhu Lingshan <lingshan.zhu@intel.com>
X-Patchwork-Id: 12138555
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.8 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT
	autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 3C369C2BA2B
	for <kvm@archiver.kernel.org>; Mon, 15 Mar 2021 07:51:12 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 2AB0A64E76
	for <kvm@archiver.kernel.org>; Mon, 15 Mar 2021 07:51:12 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S230332AbhCOHug (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Mon, 15 Mar 2021 03:50:36 -0400
Received: from mga09.intel.com ([134.134.136.24]:17801 "EHLO mga09.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S230263AbhCOHuR (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 15 Mar 2021 03:50:17 -0400
IronPort-SDR: 
 dcTXrqStajPaK9pWAqoISt5HSHd7B/wxyjEfL1gR5KxXqy3uy5hCOOhxVSG6t8BHICAINerrKu
 5PnOYM41+zTQ==
X-IronPort-AV: E=McAfee;i="6000,8403,9923"; a="189140886"
X-IronPort-AV: E=Sophos;i="5.81,249,1610438400";
   d="scan'208";a="189140886"
Received: from orsmga008.jf.intel.com ([10.7.209.65])
  by orsmga102.jf.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 15 Mar 2021 00:50:15 -0700
IronPort-SDR: 
 DikDOrUdN9B11I5m9Af3WpUmWBeBgZ0IV6X3lOJXE6MrvsViieDHAZSGh2qWNmIxPQRP55dTlQ
 ZOJO+twDptJQ==
X-IronPort-AV: E=Sophos;i="5.81,249,1610438400";
   d="scan'208";a="411752183"
Received: from unknown (HELO localhost.localdomain.bj.intel.com)
 ([10.240.193.73])
  by orsmga008-auth.jf.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 15 Mar 2021 00:50:12 -0700
From: Zhu Lingshan <lingshan.zhu@intel.com>
To: jasowang@redhat.com, mst@redhat.com, lulu@redhat.com,
        leonro@nvidia.com
Cc: virtualization@lists.linux-foundation.org, netdev@vger.kernel.org,
        kvm@vger.kernel.org, linux-kernel@vger.kernel.org,
        Zhu Lingshan <lingshan.zhu@intel.com>
Subject: [PATCH V4 1/7] vDPA/ifcvf: get_vendor_id returns a device specific
 vendor id
Date: Mon, 15 Mar 2021 15:44:55 +0800
Message-Id: <20210315074501.15868-2-lingshan.zhu@intel.com>
X-Mailer: git-send-email 2.27.0
In-Reply-To: <20210315074501.15868-1-lingshan.zhu@intel.com>
References: <20210315074501.15868-1-lingshan.zhu@intel.com>
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

In this commit, ifcvf_get_vendor_id() will return
a device specific vendor id of the probed pci device
than a hard code.

Signed-off-by: Zhu Lingshan <lingshan.zhu@intel.com>
---
 drivers/vdpa/ifcvf/ifcvf_main.c | 5 ++++-
 1 file changed, 4 insertions(+), 1 deletion(-)

```
#### [PATCH] vfio/pci: Remove an unnecessary blank line in vfio_pci_enable
##### From: Zhou Wang <wangzhou1@hisilicon.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Zhou Wang <wangzhou1@hisilicon.com>
X-Patchwork-Id: 12139023
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.8 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT autolearn=ham
	autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 37D05C433E6
	for <kvm@archiver.kernel.org>; Mon, 15 Mar 2021 11:47:05 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id EFE7864EB3
	for <kvm@archiver.kernel.org>; Mon, 15 Mar 2021 11:47:04 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S229559AbhCOLqc (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Mon, 15 Mar 2021 07:46:32 -0400
Received: from szxga07-in.huawei.com ([45.249.212.35]:14342 "EHLO
        szxga07-in.huawei.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S229985AbhCOLqb (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 15 Mar 2021 07:46:31 -0400
Received: from DGGEMS410-HUB.china.huawei.com (unknown [172.30.72.58])
        by szxga07-in.huawei.com (SkyGuard) with ESMTP id 4DzZMp0Wmmz8yZw;
        Mon, 15 Mar 2021 19:44:38 +0800 (CST)
Received: from localhost.localdomain (10.69.192.58) by
 DGGEMS410-HUB.china.huawei.com (10.3.19.210) with Microsoft SMTP Server id
 14.3.498.0; Mon, 15 Mar 2021 19:46:18 +0800
From: Zhou Wang <wangzhou1@hisilicon.com>
To: Alex Williamson <alex.williamson@redhat.com>,
        Cornelia Huck <cohuck@redhat.com>
CC: <kvm@vger.kernel.org>, Zhou Wang <wangzhou1@hisilicon.com>
Subject: [PATCH] vfio/pci: Remove an unnecessary blank line in vfio_pci_enable
Date: Mon, 15 Mar 2021 19:34:33 +0800
Message-ID: <1615808073-178604-1-git-send-email-wangzhou1@hisilicon.com>
X-Mailer: git-send-email 2.8.1
MIME-Version: 1.0
X-Originating-IP: [10.69.192.58]
X-CFilter-Loop: Reflected
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This blank line is unnecessary, so remove it.

Signed-off-by: Zhou Wang <wangzhou1@hisilicon.com>
---
 drivers/vfio/pci/vfio_pci.c | 1 -
 1 file changed, 1 deletion(-)

```
