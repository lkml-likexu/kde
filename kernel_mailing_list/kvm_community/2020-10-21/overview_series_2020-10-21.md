#### [PATCH v3 10/16] media/videbuf1|2: Mark follow_pfn usage as unsafe
##### From: Daniel Vetter <daniel.vetter@ffwll.ch>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 8bit
X-Patchwork-Submitter: Daniel Vetter <daniel.vetter@ffwll.ch>
X-Patchwork-Id: 11848725
Return-Path: <SRS0=abDU=D4=vger.kernel.org=kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-12.8 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SIGNED_OFF_BY,SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED,
	USER_AGENT_GIT autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 57BA9C63798
	for <kvm@archiver.kernel.org>; Wed, 21 Oct 2020 08:57:37 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 031002227F
	for <kvm@archiver.kernel.org>; Wed, 21 Oct 2020 08:57:36 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=ffwll.ch header.i=@ffwll.ch
 header.b="K873XhCK"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2502395AbgJUI50 (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Wed, 21 Oct 2020 04:57:26 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:41446 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S2502349AbgJUI5T (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 21 Oct 2020 04:57:19 -0400
Received: from mail-wr1-x443.google.com (mail-wr1-x443.google.com
 [IPv6:2a00:1450:4864:20::443])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 64BEAC0613D4
        for <kvm@vger.kernel.org>; Wed, 21 Oct 2020 01:57:18 -0700 (PDT)
Received: by mail-wr1-x443.google.com with SMTP id x7so2156111wrl.3
        for <kvm@vger.kernel.org>; Wed, 21 Oct 2020 01:57:18 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=ffwll.ch; s=google;
        h=from:to:cc:subject:date:message-id:in-reply-to:references
         :mime-version:content-transfer-encoding;
        bh=62xo6Yc+okj8E3g2nExt24JkphJyecIdIYx1MX/KcgQ=;
        b=K873XhCKhky8xYu7l9PH0L4vvRQ8W4kOqwGB7em4FSZU/FH2w3o/Fs6+QECyRAghOu
         8q8OodzeuuFUxMzw/vVk1/yMCBxwVGl1BeYckPl4pNsKxDrGH6PmKMHuJ2X/ASVVgbzy
         2gMkhgZs8aQVpZ+fDa84ImMGzU1FdBr7OgsW4=
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:in-reply-to
         :references:mime-version:content-transfer-encoding;
        bh=62xo6Yc+okj8E3g2nExt24JkphJyecIdIYx1MX/KcgQ=;
        b=b1Kwyn3JBTxl7BpFCAmPG8ZKuyqOYnL+Jn+/RRNeUiW48vmfneVHshLbZOniebXIbJ
         /H7rVRS4hBR053Nmu5Rq30KwDxgr0cNZOPLH6tx6421HALXFFXRSbuq4R7CZJC8PgH01
         HYtbh7w5zCJAS4ATp2F7eOKaTdzb6SJy4IG0TV4y4S2cr3mLCBAHfWmKtwAENx+v/GbV
         09imGmpaMgxmDGZ0UBE1yIOyXw7Vlwx2dmp8sONZNu5YkegJw2mOWgWqM9iTvPMXf65y
         Fq5GaFGLFBxykaVEfmkRftXGMpJSfu2OGcUFQGgVpi+tI3U9/SxArjH5N6E3olyE8EwE
         epkw==
X-Gm-Message-State: AOAM533aN493cV9ddKVJODlf8ZPjY+tYyZMMx7JqsnSS4svM95nOqxgd
        1SPZpmvNVWq9CkogBqiiHQ4uGA==
X-Google-Smtp-Source: 
 ABdhPJxBj+/fddzStMvRlNb0kPGellflBixkVVFjchw9D6JBYyFT9T4kixhMP79NqV0iv84nhiR1VA==
X-Received: by 2002:a5d:480a:: with SMTP id l10mr3285006wrq.238.1603270637190;
        Wed, 21 Oct 2020 01:57:17 -0700 (PDT)
Received: from phenom.ffwll.local ([2a02:168:57f4:0:efd0:b9e5:5ae6:c2fa])
        by smtp.gmail.com with ESMTPSA id
 q8sm2675939wro.32.2020.10.21.01.57.15
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Wed, 21 Oct 2020 01:57:16 -0700 (PDT)
From: Daniel Vetter <daniel.vetter@ffwll.ch>
To: DRI Development <dri-devel@lists.freedesktop.org>,
        LKML <linux-kernel@vger.kernel.org>
Cc: kvm@vger.kernel.org, linux-mm@kvack.org,
 linux-arm-kernel@lists.infradead.org, linux-samsung-soc@vger.kernel.org,
 linux-media@vger.kernel.org, linux-s390@vger.kernel.org,
 Daniel Vetter <daniel.vetter@ffwll.ch>,
 Daniel Vetter <daniel.vetter@intel.com>, Jason Gunthorpe <jgg@ziepe.ca>,
 Kees Cook <keescook@chromium.org>, Dan Williams <dan.j.williams@intel.com>,
 Andrew Morton <akpm@linux-foundation.org>,
 John Hubbard <jhubbard@nvidia.com>,
 =?utf-8?b?SsOpcsO0bWUgR2xpc3Nl?= <jglisse@redhat.com>,
 Jan Kara <jack@suse.cz>, Pawel Osciak <pawel@osciak.com>,
 Marek Szyprowski <m.szyprowski@samsung.com>,
 Kyungmin Park <kyungmin.park@samsung.com>, Tomasz Figa <tfiga@chromium.org>,
 Laurent Dufour <ldufour@linux.ibm.com>, Vlastimil Babka <vbabka@suse.cz>,
 Daniel Jordan <daniel.m.jordan@oracle.com>,
 Michel Lespinasse <walken@google.com>,
 Daniel Vetter <daniel.vetter@ffwll.com>
Subject: [PATCH v3 10/16] media/videbuf1|2: Mark follow_pfn usage as unsafe
Date: Wed, 21 Oct 2020 10:56:49 +0200
Message-Id: <20201021085655.1192025-11-daniel.vetter@ffwll.ch>
X-Mailer: git-send-email 2.28.0
In-Reply-To: <20201021085655.1192025-1-daniel.vetter@ffwll.ch>
References: <20201021085655.1192025-1-daniel.vetter@ffwll.ch>
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The media model assumes that buffers are all preallocated, so that
when a media pipeline is running we never miss a deadline because the
buffers aren't allocated or available.

This means we cannot fix the v4l follow_pfn usage through
mmu_notifier, without breaking how this all works. The only real fix
is to deprecate userptr support for VM_IO | VM_PFNMAP mappings and
tell everyone to cut over to dma-buf memory sharing for zerocopy.

userptr for normal memory will keep working as-is, this only affects
the zerocopy userptr usage enabled in 50ac952d2263 ("[media]
videobuf2-dma-sg: Support io userptr operations on io memory").

Signed-off-by: Daniel Vetter <daniel.vetter@intel.com>
Cc: Jason Gunthorpe <jgg@ziepe.ca>
Cc: Kees Cook <keescook@chromium.org>
Cc: Dan Williams <dan.j.williams@intel.com>
Cc: Andrew Morton <akpm@linux-foundation.org>
Cc: John Hubbard <jhubbard@nvidia.com>
Cc: Jérôme Glisse <jglisse@redhat.com>
Cc: Jan Kara <jack@suse.cz>
Cc: Dan Williams <dan.j.williams@intel.com>
Cc: linux-mm@kvack.org
Cc: linux-arm-kernel@lists.infradead.org
Cc: linux-samsung-soc@vger.kernel.org
Cc: linux-media@vger.kernel.org
Cc: Pawel Osciak <pawel@osciak.com>
Cc: Marek Szyprowski <m.szyprowski@samsung.com>
Cc: Kyungmin Park <kyungmin.park@samsung.com>
Cc: Tomasz Figa <tfiga@chromium.org>
Cc: Laurent Dufour <ldufour@linux.ibm.com>
Cc: Vlastimil Babka <vbabka@suse.cz>
Cc: Daniel Jordan <daniel.m.jordan@oracle.com>
Cc: Michel Lespinasse <walken@google.com>
Signed-off-by: Daniel Vetter <daniel.vetter@ffwll.com>
---
v3:
- Reference the commit that enabled the zerocopy userptr use case to
  make it abundandtly clear that this patch only affects that, and not
  normal memory userptr. The old commit message already explained that
  normal memory userptr is unaffected, but I guess that was not clear
  enough.
---
 drivers/media/common/videobuf2/frame_vector.c | 2 +-
 drivers/media/v4l2-core/videobuf-dma-contig.c | 2 +-
 2 files changed, 2 insertions(+), 2 deletions(-)

```
#### [PATCH v3 01/16] drm/exynos: Stop using frame_vector helpers
##### From: Daniel Vetter <daniel.vetter@ffwll.ch>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 8bit
X-Patchwork-Submitter: Daniel Vetter <daniel.vetter@ffwll.ch>
X-Patchwork-Id: 11848773
Return-Path: <SRS0=abDU=D4=vger.kernel.org=kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-12.8 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SIGNED_OFF_BY,SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED,
	USER_AGENT_GIT autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id C6AC9C63699
	for <kvm@archiver.kernel.org>; Wed, 21 Oct 2020 08:59:11 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 69D302245F
	for <kvm@archiver.kernel.org>; Wed, 21 Oct 2020 08:59:11 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=ffwll.ch header.i=@ffwll.ch
 header.b="Hd5qr7pZ"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2502116AbgJUI5G (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Wed, 21 Oct 2020 04:57:06 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:41378 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S2441048AbgJUI5F (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 21 Oct 2020 04:57:05 -0400
Received: from mail-wr1-x442.google.com (mail-wr1-x442.google.com
 [IPv6:2a00:1450:4864:20::442])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 920A6C0613D6
        for <kvm@vger.kernel.org>; Wed, 21 Oct 2020 01:57:04 -0700 (PDT)
Received: by mail-wr1-x442.google.com with SMTP id n6so2010091wrm.13
        for <kvm@vger.kernel.org>; Wed, 21 Oct 2020 01:57:04 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=ffwll.ch; s=google;
        h=from:to:cc:subject:date:message-id:in-reply-to:references
         :mime-version:content-transfer-encoding;
        bh=K95D/JeFvwIRswqJ5AyZx2c3o+Go5rbi2d1Aft3apVY=;
        b=Hd5qr7pZZO1AF760IHt5p0pXKDL2hqdJ3sUJVr7XIGUMaqaAvNysYEec4f09iASZfR
         NNiTDBnpFl36ANaTjQP9R6ClT5cy809US9aIQXED4/OldrY173V7OBDkje/vz4pn3KvB
         rgWsXHgy+UPbTuurH+E1eCmRcP1XEOsN6bb/U=
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:in-reply-to
         :references:mime-version:content-transfer-encoding;
        bh=K95D/JeFvwIRswqJ5AyZx2c3o+Go5rbi2d1Aft3apVY=;
        b=AG6LLJGkjmJ8c+nMmsKPvriQ7pF8hCa0OW5voT9UQG0fjiM6S9EgEbt/jgMPIlTmkn
         eWy37FVd0fsFmcwZVX+QOOrpJwwWItCgBviqefxJUnQqrCb1DjWb+QjV2h+WKyx6e8t5
         1oxp0fH/OO3pwvkfNxn+19mp6dSJT3lVjm9v6YqX097wwkNSXA07yGPcXGFWcQhvWiiO
         IeV6Rp6pCDw5L+R7BO4+Tv1hnuHtAe8Qp5CqsgtniscJFe4CZfw9BsW97lR7SO3SgNq/
         9ESJ0TEbDsP/mpIwaxgAgBdEqPAHUI4r1neZuWrn+3OvifPyBuul4CGs1jMQIWOCf/7G
         URyA==
X-Gm-Message-State: AOAM530ezZkkbgIr4tO6Qab8p2K/p3NmLz9WuGJfUX4oDBXWNZB8J905
        K5yOca/f2Ftg2BnyjNlWFOumLg==
X-Google-Smtp-Source: 
 ABdhPJw2XMtVnZfoQx45xaQNDg3qnrf6WmNn/N8qNOBOueDi4hxOOcHlcdccOX48m/SzW3eHWMyAJw==
X-Received: by 2002:a5d:4dc1:: with SMTP id f1mr3452736wru.42.1603270623303;
        Wed, 21 Oct 2020 01:57:03 -0700 (PDT)
Received: from phenom.ffwll.local ([2a02:168:57f4:0:efd0:b9e5:5ae6:c2fa])
        by smtp.gmail.com with ESMTPSA id
 q8sm2675939wro.32.2020.10.21.01.57.01
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Wed, 21 Oct 2020 01:57:02 -0700 (PDT)
From: Daniel Vetter <daniel.vetter@ffwll.ch>
To: DRI Development <dri-devel@lists.freedesktop.org>,
        LKML <linux-kernel@vger.kernel.org>
Cc: kvm@vger.kernel.org, linux-mm@kvack.org,
 linux-arm-kernel@lists.infradead.org, linux-samsung-soc@vger.kernel.org,
 linux-media@vger.kernel.org, linux-s390@vger.kernel.org,
 Daniel Vetter <daniel.vetter@ffwll.ch>, John Hubbard <jhubbard@nvidia.com>,
 Daniel Vetter <daniel.vetter@intel.com>, Jason Gunthorpe <jgg@ziepe.ca>,
 Inki Dae <inki.dae@samsung.com>, Joonyoung Shim <jy0922.shim@samsung.com>,
 Seung-Woo Kim <sw0312.kim@samsung.com>,
 Kyungmin Park <kyungmin.park@samsung.com>, Kukjin Kim <kgene@kernel.org>,
 Krzysztof Kozlowski <krzk@kernel.org>,
 Andrew Morton <akpm@linux-foundation.org>,
 =?utf-8?b?SsOpcsO0bWUgR2xpc3Nl?= <jglisse@redhat.com>,
 Jan Kara <jack@suse.cz>, Dan Williams <dan.j.williams@intel.com>,
 Daniel Vetter <daniel.vetter@ffwll.com>
Subject: [PATCH v3 01/16] drm/exynos: Stop using frame_vector helpers
Date: Wed, 21 Oct 2020 10:56:40 +0200
Message-Id: <20201021085655.1192025-2-daniel.vetter@ffwll.ch>
X-Mailer: git-send-email 2.28.0
In-Reply-To: <20201021085655.1192025-1-daniel.vetter@ffwll.ch>
References: <20201021085655.1192025-1-daniel.vetter@ffwll.ch>
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

All we need are a pages array, pin_user_pages_fast can give us that
directly. Plus this avoids the entire raw pfn side of get_vaddr_frames.

Reviewed-by: John Hubbard <jhubbard@nvidia.com>
Signed-off-by: Daniel Vetter <daniel.vetter@intel.com>
Cc: Jason Gunthorpe <jgg@ziepe.ca>
Cc: Inki Dae <inki.dae@samsung.com>
Cc: Joonyoung Shim <jy0922.shim@samsung.com>
Cc: Seung-Woo Kim <sw0312.kim@samsung.com>
Cc: Kyungmin Park <kyungmin.park@samsung.com>
Cc: Kukjin Kim <kgene@kernel.org>
Cc: Krzysztof Kozlowski <krzk@kernel.org>
Cc: Andrew Morton <akpm@linux-foundation.org>
Cc: John Hubbard <jhubbard@nvidia.com>
Cc: Jérôme Glisse <jglisse@redhat.com>
Cc: Jan Kara <jack@suse.cz>
Cc: Dan Williams <dan.j.williams@intel.com>
Cc: linux-mm@kvack.org
Cc: linux-arm-kernel@lists.infradead.org
Cc: linux-samsung-soc@vger.kernel.org
Cc: linux-media@vger.kernel.org
Signed-off-by: Daniel Vetter <daniel.vetter@ffwll.com>
---
v2: Use unpin_user_pages_dirty_lock (John)
---
 drivers/gpu/drm/exynos/Kconfig          |  1 -
 drivers/gpu/drm/exynos/exynos_drm_g2d.c | 47 +++++++++++--------------
 2 files changed, 20 insertions(+), 28 deletions(-)

```
#### [PATCH] KVM: arm64: Correctly handle the mmio faulting
##### From: Santosh Shukla <sashukla@nvidia.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Santosh Shukla <sashukla@nvidia.com>
X-Patchwork-Id: 11849379
Return-Path: <SRS0=abDU=D4=vger.kernel.org=kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-12.8 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_PATCH,MAILING_LIST_MULTI,SIGNED_OFF_BY,SPF_HELO_NONE,SPF_PASS,
	URIBL_BLOCKED,USER_AGENT_GIT autolearn=unavailable autolearn_force=no
	version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 15AD3C55179
	for <kvm@archiver.kernel.org>; Wed, 21 Oct 2020 16:17:24 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id A553320665
	for <kvm@archiver.kernel.org>; Wed, 21 Oct 2020 16:17:23 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=nvidia.com header.i=@nvidia.com
 header.b="Ye4yQZfV"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2444399AbgJUQRU (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Wed, 21 Oct 2020 12:17:20 -0400
Received: from hqnvemgate25.nvidia.com ([216.228.121.64]:15283 "EHLO
        hqnvemgate25.nvidia.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S2408854AbgJUQRU (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 21 Oct 2020 12:17:20 -0400
Received: from hqmail.nvidia.com (Not Verified[216.228.121.13]) by
 hqnvemgate25.nvidia.com (using TLS: TLSv1.2, AES256-SHA)
        id <B5f905ee00001>; Wed, 21 Oct 2020 09:16:32 -0700
Received: from HQMAIL105.nvidia.com (172.20.187.12) by HQMAIL105.nvidia.com
 (172.20.187.12) with Microsoft SMTP Server (TLS) id 15.0.1473.3; Wed, 21 Oct
 2020 16:17:17 +0000
Received: from santosh-System-Product-Name.nvidia.com (10.124.1.5) by
 mail.nvidia.com (172.20.187.12) with Microsoft SMTP Server (TLS) id
 15.0.1473.3 via Frontend Transport; Wed, 21 Oct 2020 16:17:13 +0000
From: Santosh Shukla <sashukla@nvidia.com>
To: <maz@kernel.org>, <kvm@vger.kernel.org>,
        <kvmarm@lists.cs.columbia.edu>, <linux-kernel@vger.kernel.org>
CC: <james.morse@arm.com>, <julien.thierry.kdev@gmail.com>,
        <suzuki.poulose@arm.com>, <linux-arm-kernel@lists.infradead.org>,
        <cjia@nvidia.com>, Santosh Shukla <sashukla@nvidia.com>
Subject: [PATCH] KVM: arm64: Correctly handle the mmio faulting
Date: Wed, 21 Oct 2020 21:46:50 +0530
Message-ID: <1603297010-18787-1-git-send-email-sashukla@nvidia.com>
X-Mailer: git-send-email 2.7.4
MIME-Version: 1.0
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=nvidia.com; s=n1;
        t=1603296992; bh=/pCPC1opPh5gWz/GYqPevuPPTN8cDasp68thhdStyhk=;
        h=From:To:CC:Subject:Date:Message-ID:X-Mailer:MIME-Version:
         Content-Type;
        b=Ye4yQZfVInpCS04DCvMYTSXJpuahcba6/U6nidiQxMqNQssOMZ4g2VJEwQroKxvqQ
         Yf2nDIGV9EivhJ8ySh9oQj3ftFP1xLtMEkYltiFs0AcRGtmDVhXZhKMJGfYYKiJqC7
         QsFZY63fdcNO4HdLlWW8rlE7rZSbCrxpiLc90tb9jzWauzHT8lx4QIUFUzzddIbTvV
         5eywN+ChvIu7lfUACARqOxZhxyVlcGPpzJ7B/CG4lScZLgkDU8TS0aIWEqxhPrewLE
         01j7i219Z64zo7BaP7DM6krxjAm21dTya5l2q63zF2ur7l1K3VxIEeEIhe+4jn9tTT
         YWmH+jNo3/byw==
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The Commit:6d674e28 introduces a notion to detect and handle the
device mapping. The commit checks for the VM_PFNMAP flag is set
in vma->flags and if set then marks force_pte to true such that
if force_pte is true then ignore the THP function check
(/transparent_hugepage_adjust()).

There could be an issue with the VM_PFNMAP flag setting and checking.
For example consider a case where the mdev vendor driver register's
the vma_fault handler named vma_mmio_fault(), which maps the
host MMIO region in-turn calls remap_pfn_range() and maps
the MMIO's vma space. Where, remap_pfn_range implicitly sets
the VM_PFNMAP flag into vma->flags.

Now lets assume a mmio fault handing flow where guest first access
the MMIO region whose 2nd stage translation is not present.
So that results to arm64-kvm hypervisor executing guest abort handler,
like below:

kvm_handle_guest_abort() -->
 user_mem_abort()--> {

    ...
    0. checks the vma->flags for the VM_PFNMAP.
    1. Since VM_PFNMAP flag is not yet set so force_pte _is_ false;
    2. gfn_to_pfn_prot() -->
        __gfn_to_pfn_memslot() -->
            fixup_user_fault() -->
                handle_mm_fault()-->
                    __do_fault() -->
                       vma_mmio_fault() --> // vendor's mdev fault handler
                        remap_pfn_range()--> // Here sets the VM_PFNMAP
						flag into vma->flags.
    3. Now that force_pte is set to false in step-2),
       will execute transparent_hugepage_adjust() func and
       that lead to Oops [4].
 }

The proposition is to check is_iomap flag before executing the THP
function transparent_hugepage_adjust().

[4] THP Oops:
> pc: kvm_is_transparent_hugepage+0x18/0xb0
> ...
> ...
> user_mem_abort+0x340/0x9b8
> kvm_handle_guest_abort+0x248/0x468
> handle_exit+0x150/0x1b0
> kvm_arch_vcpu_ioctl_run+0x4d4/0x778
> kvm_vcpu_ioctl+0x3c0/0x858
> ksys_ioctl+0x84/0xb8
> __arm64_sys_ioctl+0x28/0x38

Tested on Huawei Kunpeng Taishan-200 arm64 server, Using VFIO-mdev device.
Linux tip: 583090b1

Fixes: 6d674e28 ("KVM: arm/arm64: Properly handle faulting of device mappings")
Signed-off-by: Santosh Shukla <sashukla@nvidia.com>
---
 arch/arm64/kvm/mmu.c | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
#### [PATCH] KVM: VMX: Forbid userspace MSR filters for x2APIC
##### From: Paolo Bonzini <pbonzini@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Paolo Bonzini <pbonzini@redhat.com>
X-Patchwork-Id: 11849823
Return-Path: <SRS0=abDU=D4=vger.kernel.org=kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-9.8 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_PATCH,MAILING_LIST_MULTI,SIGNED_OFF_BY,SPF_HELO_NONE,SPF_PASS,
	URIBL_BLOCKED autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id B18AAC56201
	for <kvm@archiver.kernel.org>; Wed, 21 Oct 2020 21:36:40 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 40EB6223C7
	for <kvm@archiver.kernel.org>; Wed, 21 Oct 2020 21:36:40 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="L+1el1S9"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2506273AbgJUVgg (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Wed, 21 Oct 2020 17:36:36 -0400
Received: from us-smtp-delivery-124.mimecast.com ([63.128.21.124]:29168 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S2506253AbgJUVge (ORCPT
        <rfc822;kvm@vger.kernel.org>); Wed, 21 Oct 2020 17:36:34 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1603316193;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=6+HPUwysBYP7wqKa1dhDe87/mU8XIlbid5TDmgjrd1s=;
        b=L+1el1S9XauRKvL9CObezS1Vb+MOAsbwuZNgN3LnulxlPgoOo07gO1S5c4Nig0Ogh4tMKR
        mIv1yDl+wmu4al7/RF30u0o3oKhnNsGnZ5U70lUbTwaR2Rt2x9tKW0DpsRw2AeyiMEKjD/
        S8zB1xzEz9LGQJy/Zkh3mN+ieC0Fp4c=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-416-qjbi3N9qNhuKPc2tx5Gljw-1; Wed, 21 Oct 2020 17:36:31 -0400
X-MC-Unique: qjbi3N9qNhuKPc2tx5Gljw-1
Received: from smtp.corp.redhat.com (int-mx01.intmail.prod.int.phx2.redhat.com
 [10.5.11.11])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id C50F1804024;
        Wed, 21 Oct 2020 21:36:29 +0000 (UTC)
Received: from virtlab701.virt.lab.eng.bos.redhat.com
 (virtlab701.virt.lab.eng.bos.redhat.com [10.19.152.228])
        by smtp.corp.redhat.com (Postfix) with ESMTP id B3C3F5B4A1;
        Wed, 21 Oct 2020 21:36:25 +0000 (UTC)
From: Paolo Bonzini <pbonzini@redhat.com>
To: linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Cc: graf@amazon.com, Aaron Lewis <aaronlewis@google.com>,
        Peter Xu <peterx@redhat.com>,
        Sean Christopherson <sean.j.christopherson@intel.com>
Subject: [PATCH] KVM: VMX: Forbid userspace MSR filters for x2APIC
Date: Wed, 21 Oct 2020 17:36:25 -0400
Message-Id: <20201021213625.2377378-1-pbonzini@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.11
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Allowing userspace to intercept reads to x2APIC MSRs when APICV is
fully enabled for the guest simply can't work.   But more in general,
the LAPIC could be set to in-kernel after the MSR filter is setup
and allowing accesses by userspace would be very confusing.

We could in principle allow userspace to intercept reads and writes to TPR,
and writes to EOI and SELF_IPI, but while that could be made it work, it
would still be silly.

Cc: Alexander Graf <graf@amazon.com>
Cc: Aaron Lewis <aaronlewis@google.com>
Cc: Peter Xu <peterx@redhat.com>
Cc: Sean Christopherson <sean.j.christopherson@intel.com>
Signed-off-by: Paolo Bonzini <pbonzini@redhat.com>
---
 Documentation/virt/kvm/api.rst | 18 ++++++++++--------
 arch/x86/kvm/x86.c             |  9 ++++++++-
 2 files changed, 18 insertions(+), 9 deletions(-)

```
#### [PATCH] KVM: VMX: Ignore userspace MSR filters for x2APIC
##### From: Paolo Bonzini <pbonzini@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Paolo Bonzini <pbonzini@redhat.com>
X-Patchwork-Id: 11849825
Return-Path: <SRS0=abDU=D4=vger.kernel.org=kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-9.8 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_PATCH,MAILING_LIST_MULTI,SIGNED_OFF_BY,SPF_HELO_NONE,SPF_PASS,
	URIBL_BLOCKED autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 569E9C4363A
	for <kvm@archiver.kernel.org>; Wed, 21 Oct 2020 21:36:32 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id D6B4624178
	for <kvm@archiver.kernel.org>; Wed, 21 Oct 2020 21:36:31 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="jNsbhiD/"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2506257AbgJUVga (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Wed, 21 Oct 2020 17:36:30 -0400
Received: from us-smtp-delivery-124.mimecast.com ([216.205.24.124]:25018 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S2506253AbgJUVga (ORCPT
        <rfc822;kvm@vger.kernel.org>); Wed, 21 Oct 2020 17:36:30 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1603316187;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=TjNvZMlAC1VHWvy6fPJdhxQ1pl47H3dCj3CRkqJSM6E=;
        b=jNsbhiD/Pw8nDoJsdssoq4OE9RF3xBmpBDVqxReQ0+nmxyPl3e9xfsTOc0KrcGhr2+/oCi
        kndCqIBrEKpZW1hSmYo4nCFii5+SXAwaptG0UQg1XWvEN1fjjZir/ng3KWszt52taGWvzs
        ALmgKBFJdrRGqtL8R7XkLKyh+prlkzk=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-505-NFCCwN2LO-mnO7dEk3WBkg-1; Wed, 21 Oct 2020 17:36:25 -0400
X-MC-Unique: NFCCwN2LO-mnO7dEk3WBkg-1
Received: from smtp.corp.redhat.com (int-mx08.intmail.prod.int.phx2.redhat.com
 [10.5.11.23])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 5266A18C5200;
        Wed, 21 Oct 2020 21:36:24 +0000 (UTC)
Received: from virtlab701.virt.lab.eng.bos.redhat.com
 (virtlab701.virt.lab.eng.bos.redhat.com [10.19.152.228])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 439C719C78;
        Wed, 21 Oct 2020 21:36:20 +0000 (UTC)
From: Paolo Bonzini <pbonzini@redhat.com>
To: linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Cc: graf@amazon.com,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        Aaron Lewis <aaronlewis@google.com>,
        Peter Xu <peterx@redhat.com>
Subject: [PATCH] KVM: VMX: Ignore userspace MSR filters for x2APIC
Date: Wed, 21 Oct 2020 17:36:19 -0400
Message-Id: <20201021213619.2377276-1-pbonzini@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.84 on 10.5.11.23
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Sean Christopherson <sean.j.christopherson@intel.com>

Rework the resetting of the MSR bitmap for x2APIC MSRs to ignore userspace
filtering.  Allowing userspace to intercept reads to x2APIC MSRs when
APICV is fully enabled for the guest simply can't work; the LAPIC and thus
virtual APIC is in-kernel and cannot be directly accessed by userspace.
To keep things simple we will in fact forbid intercepting x2APIC MSRs
altogether, independent of the default_allow setting.

Cc: Alexander Graf <graf@amazon.com>
Cc: Aaron Lewis <aaronlewis@google.com>
Cc: Peter Xu <peterx@redhat.com>
Signed-off-by: Sean Christopherson <sean.j.christopherson@intel.com>
Message-Id: <20201005195532.8674-3-sean.j.christopherson@intel.com>
[Modified to operate even if APICv is disabled, adjust documentation. - Paolo]
Signed-off-by: Paolo Bonzini <pbonzini@redhat.com>
---
 Documentation/virt/kvm/api.rst | 27 +++++++++++---------
 arch/x86/kvm/vmx/vmx.c         | 45 ++++++++++++++++++++++------------
 arch/x86/kvm/x86.c             |  4 +--
 3 files changed, 47 insertions(+), 29 deletions(-)

```
#### [PATCH v2 1/7] kvm: x86: Extract kvm_apic_base_update_cpuid() from kvm_update_cpuid_runtime()
##### From: Robert Hoo <robert.hu@linux.intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Robert Hoo <robert.hu@linux.intel.com>
X-Patchwork-Id: 11848823
Return-Path: <SRS0=abDU=D4=vger.kernel.org=kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-12.7 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_PATCH,MAILING_LIST_MULTI,SIGNED_OFF_BY,
	SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED,USER_AGENT_GIT autolearn=ham
	autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id F1A2EC561F8
	for <kvm@archiver.kernel.org>; Wed, 21 Oct 2020 09:10:32 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 85D7C22249
	for <kvm@archiver.kernel.org>; Wed, 21 Oct 2020 09:10:32 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2437390AbgJUJKb (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Wed, 21 Oct 2020 05:10:31 -0400
Received: from mga07.intel.com ([134.134.136.100]:58972 "EHLO mga07.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S2388839AbgJUJKb (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 21 Oct 2020 05:10:31 -0400
IronPort-SDR: 
 nR7oAk4RxekLulYMQ+2NpLAXEKnCAu5QVe05QmAgVlF+fzu/Gm9d6WsTfHz+H7VCEhE8rJw4Z8
 RmnExNyk2wSw==
X-IronPort-AV: E=McAfee;i="6000,8403,9780"; a="231530446"
X-IronPort-AV: E=Sophos;i="5.77,400,1596524400";
   d="scan'208";a="231530446"
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from fmsmga006.fm.intel.com ([10.253.24.20])
  by orsmga105.jf.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 21 Oct 2020 02:10:28 -0700
IronPort-SDR: 
 Qa3Rf/7Pyb8PPlbS/6TpCPDQaiA1mdcrIDZFSo+noH1r13fL/UT7OwFGtR2b8ATAxO8E6UZInj
 YV1q+2YcMq9g==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.77,400,1596524400";
   d="scan'208";a="522682410"
Received: from sqa-gate.sh.intel.com (HELO robert-ivt.tsp.org)
 ([10.239.48.212])
  by fmsmga006.fm.intel.com with ESMTP; 21 Oct 2020 02:10:26 -0700
From: Robert Hoo <robert.hu@linux.intel.com>
To: sean.j.christopherson@intel.com, pbonzini@redhat.com,
        xiaoyao.li@intel.com, vkuznets@redhat.com, wanpengli@tencent.com,
        jmattson@google.com, joro@8bytes.org
Cc: kvm@vger.kernel.org, robert.hu@intel.com,
        Robert Hoo <robert.hu@linux.intel.com>
Subject: [PATCH v2 1/7] kvm: x86: Extract kvm_apic_base_update_cpuid() from
 kvm_update_cpuid_runtime()
Date: Wed, 21 Oct 2020 17:10:04 +0800
Message-Id: <1603271410-71343-2-git-send-email-robert.hu@linux.intel.com>
X-Mailer: git-send-email 1.8.3.1
In-Reply-To: <1603271410-71343-1-git-send-email-robert.hu@linux.intel.com>
References: <1603271410-71343-1-git-send-email-robert.hu@linux.intel.com>
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

And let kvm_lapic_set_base() call kvm_apic_base_update_cpuid() instead of
whole kvm_update_cpuid_runtime().

Signed-off-by: Robert Hoo <robert.hu@linux.intel.com>
---
 arch/x86/kvm/cpuid.c | 14 ++++++++++++++
 arch/x86/kvm/cpuid.h |  1 +
 arch/x86/kvm/lapic.c |  2 +-
 3 files changed, 16 insertions(+), 1 deletion(-)

```
