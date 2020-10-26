#### [PATCH 1/2] KVM: selftests: Add get featured msrs test case
##### From: Peter Xu <peterx@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Peter Xu <peterx@redhat.com>
X-Patchwork-Id: 11855389
Return-Path: <SRS0=Ww7j=EA=vger.kernel.org=kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-12.9 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_PATCH,MAILING_LIST_MULTI,SIGNED_OFF_BY,SPF_HELO_NONE,SPF_PASS,
	USER_AGENT_GIT autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 219E7C55179
	for <kvm@archiver.kernel.org>; Sun, 25 Oct 2020 18:53:47 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id E185622260
	for <kvm@archiver.kernel.org>; Sun, 25 Oct 2020 18:53:46 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="iz/aBRtj"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1418331AbgJYSxq (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Sun, 25 Oct 2020 14:53:46 -0400
Received: from us-smtp-delivery-124.mimecast.com ([216.205.24.124]:42717 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1417005AbgJYSxn (ORCPT
        <rfc822;kvm@vger.kernel.org>); Sun, 25 Oct 2020 14:53:43 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1603652021;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding:
         in-reply-to:in-reply-to:references:references;
        bh=VrcnpBHn5t+Btl97z9jvdq3FNw8fdJ9uB7f9070VgDQ=;
        b=iz/aBRtjK3wqpXyHfpf7NLKR5wV72/y0d3tALSlVBGbBN08iZt4jplHgzq9mqq0XCdD/lQ
        L7wKNsm+ufLQDE9FhlyL4M1h3ZS+UKyU1mki5siJqJrkMEgZAyv2dK3aYUIBV7cJvexHkZ
        s+r6Hvk53NRi5S0wn8DsVkPyPgI969A=
Received: from mail-qt1-f197.google.com (mail-qt1-f197.google.com
 [209.85.160.197]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-195-eb5_13N4NKWNxc2ED6c69A-1; Sun, 25 Oct 2020 14:53:39 -0400
X-MC-Unique: eb5_13N4NKWNxc2ED6c69A-1
Received: by mail-qt1-f197.google.com with SMTP id d6so4938467qtp.2
        for <kvm@vger.kernel.org>; Sun, 25 Oct 2020 11:53:39 -0700 (PDT)
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:in-reply-to
         :references:mime-version:content-transfer-encoding;
        bh=VrcnpBHn5t+Btl97z9jvdq3FNw8fdJ9uB7f9070VgDQ=;
        b=d5IfzlCbt9/nbqZIyk3ZYG+siqteBf4iE8sRcj6g7phg3n86bB2wvSAyGpEkwtAg8h
         Wghc/5Kco/4Ac4F8b/xJ/fwcKdIbbMZWtbIVUUX7/daQ8CqjgK5KT4vvq24HlG5WLMOm
         LWyif7JXF32PqktIhSgR7+QfOfslKDGbYJjFjOwkuxYc1UnAihX1/FdGmbobEu0gSYtQ
         MbtDjNK7m8FZf87KilrLt/HvJ8la/OXC5lps8EhjOqna1a5mIBZXvM2klPxRGnBIEgsw
         Z/4FMOQS7HrqBEv4wAIlrry9lcI3WlA6+PhaMjQC9mqkcqBlLRKRR4w/BEplFKNnrYSO
         Z92w==
X-Gm-Message-State: AOAM530y75H8W95HjPPKbufaaPaqRctHY3mBbeXzXnEccEeunhHkzusM
        K6jXPv8Wqk1r9BBzL/cPF/0+l1SAo7sNHMSBLIlHeC1+XtK0zEXO4EXVbn8IOhSQE6pDMJ6BV42
        xWs9HNv4+jTtI
X-Received: by 2002:aed:2d62:: with SMTP id
 h89mr13213913qtd.108.1603652019219;
        Sun, 25 Oct 2020 11:53:39 -0700 (PDT)
X-Google-Smtp-Source: 
 ABdhPJxYDlptSJ6GU33UiUx9KGSnwRp59ERcPYRR25wYM2MrcjvAUTN1PTGqDdcwUWD4EpoaK/i3ig==
X-Received: by 2002:aed:2d62:: with SMTP id
 h89mr13213894qtd.108.1603652018972;
        Sun, 25 Oct 2020 11:53:38 -0700 (PDT)
Received: from xz-x1.redhat.com
 (toroon474qw-lp140-04-174-95-215-133.dsl.bell.ca. [174.95.215.133])
        by smtp.gmail.com with ESMTPSA id y3sm5305224qto.2.2020.10.25.11.53.37
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Sun, 25 Oct 2020 11:53:38 -0700 (PDT)
From: Peter Xu <peterx@redhat.com>
To: linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Cc: Vitaly Kuznetsov <vkuznets@redhat.com>, peterx@redhat.com,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        Paolo Bonzini <pbonzini@redhat.com>
Subject: [PATCH 1/2] KVM: selftests: Add get featured msrs test case
Date: Sun, 25 Oct 2020 14:53:33 -0400
Message-Id: <20201025185334.389061-2-peterx@redhat.com>
X-Mailer: git-send-email 2.26.2
In-Reply-To: <20201025185334.389061-1-peterx@redhat.com>
References: <20201025185334.389061-1-peterx@redhat.com>
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Try to fetch any supported featured msr.  Currently it won't fail, so at least
we can check against valid ones (which should be >0).

This reproduces [1] too by trying to fetch one invalid msr there.

[1] https://bugzilla.kernel.org/show_bug.cgi?id=209845

Signed-off-by: Peter Xu <peterx@redhat.com>
---
 .../testing/selftests/kvm/include/kvm_util.h  |  3 +
 tools/testing/selftests/kvm/lib/kvm_util.c    | 14 +++++
 .../testing/selftests/kvm/x86_64/state_test.c | 58 +++++++++++++++++++
 3 files changed, 75 insertions(+)

```
