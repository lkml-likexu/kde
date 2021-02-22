#### [RFC v3 1/5] KVM: add initial support for KVM_SET_IOREGION
##### From: Elena Afanasova <eafanasova@gmail.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Elena Afanasova <eafanasova@gmail.com>
X-Patchwork-Id: 12097295
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
	by smtp.lore.kernel.org (Postfix) with ESMTP id D8434C433DB
	for <kvm@archiver.kernel.org>; Sun, 21 Feb 2021 12:12:04 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id A791864E4E
	for <kvm@archiver.kernel.org>; Sun, 21 Feb 2021 12:12:04 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S229918AbhBUMLh (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Sun, 21 Feb 2021 07:11:37 -0500
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:33192 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S229663AbhBUMLf (ORCPT <rfc822;kvm@vger.kernel.org>);
        Sun, 21 Feb 2021 07:11:35 -0500
Received: from mail-lj1-x230.google.com (mail-lj1-x230.google.com
 [IPv6:2a00:1450:4864:20::230])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id D38CCC061786
        for <kvm@vger.kernel.org>; Sun, 21 Feb 2021 04:10:54 -0800 (PST)
Received: by mail-lj1-x230.google.com with SMTP id e8so8398376ljj.5
        for <kvm@vger.kernel.org>; Sun, 21 Feb 2021 04:10:54 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=from:to:cc:subject:date:message-id:in-reply-to:references
         :mime-version:content-transfer-encoding;
        bh=zrgjYZbuj6EoVl0nOpsXCBS/JrXJCWU4RgXnmNNrQDU=;
        b=CaoPb27blDPylwNIjJTfDZK1v94vkToTS7N6Se6nkzKZvcRg2b2d7tYQkOWi6GzRNV
         sE9178SELH4mjIumvbrO8C7b3iHxBKvSvhWmRiCnIqkN+kaeCB+Wkd51089oY2w6Zvwf
         DTt+FN/CPVtGXqJ/KpT9tjQ0AMy1uFXBqmM1y1LyBvS50MhG12flFEBoPTq4pBeXhWGX
         zU6w5dO8G8rpSNZNEudu1Zzuc2LZt1QNvwqU77KPRP+Ie4tVWwshAoX2NHQNQoomb4XN
         CsE044D5ripZNvZITAISEJh2JeekurHUwbXdlBn3Bvogu+igcu/h6BtmIf3Gt0n1IHkq
         WH3Q==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:in-reply-to
         :references:mime-version:content-transfer-encoding;
        bh=zrgjYZbuj6EoVl0nOpsXCBS/JrXJCWU4RgXnmNNrQDU=;
        b=DQuffwqJevNM/Y/hMuXq8yWoIUQ698ITWQ1mrtRPPRHQCP10iBXlv0SKOPBwD+2vpH
         XRSQGhIPSBOKXJ3M0zw3Fmm7n0wP4of3IpbqWHzxeJ6v+6q4Ktvx58UTNq8JtFIKwqlZ
         1DiORJCcEqLSeqn4NeZceEIGiI5qV6+sGIVTx3wZdcmQcVOo3gw20bEnP6ZBK9tedeva
         1riTgTMHLQaSoe0LegHRM8xlLgwJyQ7/JK7KA6xxUxQJejh96hFxo7jU1OocRUpjD4Z7
         hIDAIs8m9xJXy5Eu/4VXAIUJ6OtTmMLJQyBVa68a4mxVICgHk4JXByvgTihhJFjhhIdY
         K00w==
X-Gm-Message-State: AOAM531N1miaGkUnywY5Y2eWQ8qKwvCo73sML7xExCrAdMdekc+QrZ1F
        Sz/E2Au5DM/FfuBIT+j0GEDhfCHTI8ek8Ba0
X-Google-Smtp-Source: 
 ABdhPJy+zPkmJAQgqWpSnbfFTFfBvwAhOQh6mBxGfYUz9bSZkeB50FBxp5B95DJQngQ1jJFjDIFS9A==
X-Received: by 2002:a05:651c:211b:: with SMTP id
 a27mr11037706ljq.433.1613909450332;
        Sun, 21 Feb 2021 04:10:50 -0800 (PST)
Received: from localhost.localdomain (37-145-186-126.broadband.corbina.ru.
 [37.145.186.126])
        by smtp.gmail.com with ESMTPSA id
 q6sm1547715lfn.23.2021.02.21.04.10.49
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Sun, 21 Feb 2021 04:10:49 -0800 (PST)
From: Elena Afanasova <eafanasova@gmail.com>
To: kvm@vger.kernel.org
Cc: stefanha@redhat.com, jag.raman@oracle.com,
        elena.ufimtseva@oracle.com, pbonzini@redhat.com,
        jasowang@redhat.com, mst@redhat.com, cohuck@redhat.com,
        john.levon@nutanix.com, Elena Afanasova <eafanasova@gmail.com>
Subject: [RFC v3 1/5] KVM: add initial support for KVM_SET_IOREGION
Date: Sun, 21 Feb 2021 15:04:37 +0300
Message-Id: 
 <f77bbc58289508b5b0633521cf8c03eb0303707a.1613828727.git.eafanasova@gmail.com>
X-Mailer: git-send-email 2.25.1
In-Reply-To: <cover.1613828726.git.eafanasova@gmail.com>
References: <cover.1613828726.git.eafanasova@gmail.com>
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This vm ioctl adds or removes an ioregionfd MMIO/PIO region. Guest
read and write accesses are dispatched through the given ioregionfd
instead of returning from ioctl(KVM_RUN).

Signed-off-by: Elena Afanasova <eafanasova@gmail.com>
---
v3:
 - add FAST_MMIO bus support
 - add KVM_IOREGION_DEASSIGN flag
 - rename kvm_ioregion read/write file descriptors

 arch/x86/kvm/Kconfig     |   1 +
 arch/x86/kvm/Makefile    |   1 +
 arch/x86/kvm/x86.c       |   1 +
 include/linux/kvm_host.h |  18 +++
 include/uapi/linux/kvm.h |  25 ++++
 virt/kvm/Kconfig         |   3 +
 virt/kvm/eventfd.c       |  25 ++++
 virt/kvm/eventfd.h       |  14 +++
 virt/kvm/ioregion.c      | 265 +++++++++++++++++++++++++++++++++++++++
 virt/kvm/ioregion.h      |  15 +++
 virt/kvm/kvm_main.c      |  11 ++
 11 files changed, 379 insertions(+)
 create mode 100644 virt/kvm/eventfd.h
 create mode 100644 virt/kvm/ioregion.c
 create mode 100644 virt/kvm/ioregion.h

```
#### [PATCH v4 01/22] x86/fpu/xstate: Modify the initialization helper to handle both static and dynamic buffers
##### From: "Chang S. Bae" <chang.seok.bae@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: "Chang S. Bae" <chang.seok.bae@intel.com>
X-Patchwork-Id: 12097595
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.8 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED,USER_AGENT_GIT
	autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 536B2C433E6
	for <kvm@archiver.kernel.org>; Sun, 21 Feb 2021 19:02:51 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 2875064ED6
	for <kvm@archiver.kernel.org>; Sun, 21 Feb 2021 19:02:51 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S230393AbhBUTC3 (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Sun, 21 Feb 2021 14:02:29 -0500
Received: from mga11.intel.com ([192.55.52.93]:31443 "EHLO mga11.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S230213AbhBUTCU (ORCPT <rfc822;kvm@vger.kernel.org>);
        Sun, 21 Feb 2021 14:02:20 -0500
IronPort-SDR: 
 IM7Dd/VkgPcfl97h4I2Kju/4GEAFAZ71fr7pvNHhNx8Pq1WhMJoarXRXMdKz8OhvrSKOCuDSEx
 1d+AVCrdJg7A==
X-IronPort-AV: E=McAfee;i="6000,8403,9902"; a="180813507"
X-IronPort-AV: E=Sophos;i="5.81,195,1610438400";
   d="scan'208";a="180813507"
Received: from fmsmga003.fm.intel.com ([10.253.24.29])
  by fmsmga102.fm.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 21 Feb 2021 11:01:26 -0800
IronPort-SDR: 
 dqtSDVN9tT4dWgA06J0lIKh9YuY8F6P+syXxOg+8RAKn8rSWNB9GxT6Xl7v2FhtNiCIAiwAiyY
 5MKFra0vo9iw==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.81,195,1610438400";
   d="scan'208";a="429792080"
Received: from chang-linux-3.sc.intel.com ([172.25.66.175])
  by FMSMGA003.fm.intel.com with ESMTP; 21 Feb 2021 11:01:25 -0800
From: "Chang S. Bae" <chang.seok.bae@intel.com>
To: bp@suse.de, luto@kernel.org, tglx@linutronix.de, mingo@kernel.org,
        x86@kernel.org
Cc: len.brown@intel.com, dave.hansen@intel.com, jing2.liu@intel.com,
        ravi.v.shankar@intel.com, linux-kernel@vger.kernel.org,
        chang.seok.bae@intel.com, kvm@vger.kernel.org
Subject: [PATCH v4 01/22] x86/fpu/xstate: Modify the initialization helper to
 handle both static and dynamic buffers
Date: Sun, 21 Feb 2021 10:56:16 -0800
Message-Id: <20210221185637.19281-2-chang.seok.bae@intel.com>
X-Mailer: git-send-email 2.17.1
In-Reply-To: <20210221185637.19281-1-chang.seok.bae@intel.com>
References: <20210221185637.19281-1-chang.seok.bae@intel.com>
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Have the function initializing the xstate buffer take a struct fpu *
pointer in preparation for dynamic state buffer support.

init_fpstate is a special case, which is indicated by a null pointer
parameter to fpstate_init().

Also, fpstate_init_xstate() now accepts the state component bitmap to
configure XCOMP_BV for the compacted format.

No functional change.

Signed-off-by: Chang S. Bae <chang.seok.bae@intel.com>
Reviewed-by: Len Brown <len.brown@intel.com>
Cc: x86@kernel.org
Cc: linux-kernel@vger.kernel.org
Cc: kvm@vger.kernel.org
---
Changes from v3:
* Updated the changelog. (Borislav Petkov)
* Updated the function comment to use kernel-doc style. (Borislav Petkov)

Changes from v2:
* Updated the changelog with task->fpu removed. (Borislav Petkov)
---
 arch/x86/include/asm/fpu/internal.h |  6 +++---
 arch/x86/kernel/fpu/core.c          | 16 +++++++++++++---
 arch/x86/kernel/fpu/init.c          |  2 +-
 arch/x86/kernel/fpu/regset.c        |  2 +-
 arch/x86/kernel/fpu/xstate.c        |  3 +--
 arch/x86/kvm/x86.c                  |  2 +-
 6 files changed, 20 insertions(+), 11 deletions(-)

```
