#### [PATCH] kvm: lapic: add module parameters for LAPIC_TIMER_ADVANCE_ADJUST_MAX/MIN
##### From: lihaiwei.kernel@gmail.com

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Haiwei Li <lihaiwei.kernel@gmail.com>
X-Patchwork-Id: 12113131
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
	by smtp.lore.kernel.org (Postfix) with ESMTP id 61169C433DB
	for <kvm@archiver.kernel.org>; Wed,  3 Mar 2021 07:24:37 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 15CD464EE1
	for <kvm@archiver.kernel.org>; Wed,  3 Mar 2021 07:24:37 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1449369AbhCCHUB (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Wed, 3 Mar 2021 02:20:01 -0500
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:47292 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S238045AbhCCCLA (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 2 Mar 2021 21:11:00 -0500
Received: from mail-pj1-x1033.google.com (mail-pj1-x1033.google.com
 [IPv6:2607:f8b0:4864:20::1033])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 546B1C061224;
        Tue,  2 Mar 2021 18:09:58 -0800 (PST)
Received: by mail-pj1-x1033.google.com with SMTP id e9so3371051pjj.0;
        Tue, 02 Mar 2021 18:09:58 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=from:to:cc:subject:date:message-id:mime-version
         :content-transfer-encoding;
        bh=Y4CDZC0XRtdxRyUu6upw3DY8PzyuYgSy6jHykMMCFTY=;
        b=M+m8+IeTn56qvibEzZaBaLzICwpFnGw1QTeozL3il7ZPPhlofSUc32Pqvf9KvcU4Co
         1ksSTP9mOLQXpmxuFfe5B09ISx2/2c/OngpINTk7OQwqJa1uM2INoScqO7W+suxk4wUk
         Dnf3XfWuePpDh1JhqHSdaqT7pvw2FBEc3DgiyoI3eWW0Uwc/qAZw7OeSX8si9cTtjm4H
         GJXE4NeRLSFyXODVCe1WuRWokDjwtp1eKeEQ8AL5q6hxdP2Rc32Zpns9eWBXIey91Xev
         A1kRVKb5KOiaCEi8ZmsmmtLmon/o8vAHRBnh3k3E0tVbnI9zTZa8vXSOp15y+PMHolJX
         FgaQ==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:mime-version
         :content-transfer-encoding;
        bh=Y4CDZC0XRtdxRyUu6upw3DY8PzyuYgSy6jHykMMCFTY=;
        b=a2oiwdicy+VnrOBNxqEg8JyYkKc2h5cjvjff+zPwnzOsO4xCyUoiouzPJux9BbCm4+
         KFnUeNZvejO2foRCDWqpXKqbbo9lrnkrW6aM7K3zifT8C2tVUwfiQnXJvkmhXKkiulOk
         bTkrF2YbmXQbplNsjJn8q+xps+zV3qdKDDww6g0TIUZvASyjwlUrSQNWooVuvyUuC1rx
         tx83zzEdPEtBc95i4bV7zyAqpz/RcGMi7/vOHhjP8zdx9DPQ6YlU0dyqbv0Rcr9iBX32
         Qn2HlK0gvPLYM0oVjE7AM4bcl+3ujvW991I7IKXBnHsJFHAlYXJKbaa9hQFos7035Af0
         Ebsw==
X-Gm-Message-State: AOAM5319bW+TbCC+4h+68G2dRcXPR4mDWeon1T3gB21yFM65DxxRyf8u
        Bw2TxSXKFcRsHcrNL9ThBQx5n9CyHg==
X-Google-Smtp-Source: 
 ABdhPJyJ/vLG5EM+mwDq6WrvjKVvipezABEQ4XAsfkBAlmEkSCpxAjE03uaEyDFwX9tlOqQIXfIKjg==
X-Received: by 2002:a17:90a:7344:: with SMTP id
 j4mr7575058pjs.216.1614737397602;
        Tue, 02 Mar 2021 18:09:57 -0800 (PST)
Received: from localhost.localdomain ([203.205.141.39])
        by smtp.gmail.com with ESMTPSA id
 f20sm280415pfa.10.2021.03.02.18.09.55
        (version=TLS1_2 cipher=ECDHE-ECDSA-AES128-GCM-SHA256 bits=128/128);
        Tue, 02 Mar 2021 18:09:57 -0800 (PST)
From: lihaiwei.kernel@gmail.com
To: linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Cc: pbonzini@redhat.com, seanjc@google.com, vkuznets@redhat.com,
        wanpengli@tencent.com, jmattson@google.com, joro@8bytes.org,
        Haiwei Li <lihaiwei@tencent.com>
Subject: [PATCH] kvm: lapic: add module parameters for
 LAPIC_TIMER_ADVANCE_ADJUST_MAX/MIN
Date: Wed,  3 Mar 2021 10:09:46 +0800
Message-Id: <20210303020946.26083-1-lihaiwei.kernel@gmail.com>
X-Mailer: git-send-email 2.28.0
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Haiwei Li <lihaiwei@tencent.com>

In my test environment, advance_expire_delta is frequently greater than
the fixed LAPIC_TIMER_ADVANCE_ADJUST_MAX. And this will hinder the
adjustment.

Adding module parameters for LAPIC_TIMER_ADVANCE_ADJUST_MAX/MIN, so they
can be dynamically adjusted.

Signed-off-by: Haiwei Li <lihaiwei@tencent.com>
---
 arch/x86/kvm/lapic.c | 6 ++----
 arch/x86/kvm/x86.c   | 8 ++++++++
 arch/x86/kvm/x86.h   | 3 +++
 3 files changed, 13 insertions(+), 4 deletions(-)

```
