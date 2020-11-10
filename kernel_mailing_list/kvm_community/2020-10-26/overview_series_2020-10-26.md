#### [PATCH v4 06/15] media: videobuf2: Move frame_vector into media subsystem
##### From: Daniel Vetter <daniel.vetter@ffwll.ch>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 8bit
X-Patchwork-Submitter: Daniel Vetter <daniel.vetter@ffwll.ch>
X-Patchwork-Id: 11856501
Return-Path: <SRS0=RIF0=EB=vger.kernel.org=kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-12.8 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SIGNED_OFF_BY,SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED,
	USER_AGENT_GIT autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 7F541C4363A
	for <kvm@archiver.kernel.org>; Mon, 26 Oct 2020 10:58:40 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 398082242B
	for <kvm@archiver.kernel.org>; Mon, 26 Oct 2020 10:58:40 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=ffwll.ch header.i=@ffwll.ch
 header.b="MsS9QgRr"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1772790AbgJZK6i (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Mon, 26 Oct 2020 06:58:38 -0400
Received: from mail-wm1-f68.google.com ([209.85.128.68]:35860 "EHLO
        mail-wm1-f68.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1772599AbgJZK6h (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 26 Oct 2020 06:58:37 -0400
Received: by mail-wm1-f68.google.com with SMTP id e2so11985372wme.1
        for <kvm@vger.kernel.org>; Mon, 26 Oct 2020 03:58:34 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=ffwll.ch; s=google;
        h=from:to:cc:subject:date:message-id:in-reply-to:references
         :mime-version:content-transfer-encoding;
        bh=6WV52rOTICG5gX8Y1zv7jCBKQNXPiDy4YHeczZNq5R8=;
        b=MsS9QgRruwtj0Widu0UU53POHQhBX+El62ASHwLLGjvh0KmgSWdUAbgaQCn/b3XM8Z
         dq0wX4vWB/XmX5sU9MzvzcEpGxVIn1beiCnuhkFdRUfR1pSIZWd8aaFDG5HqKKjhHTtz
         Zz3x5Si5yORMNqpF745f9YMH0KJoUco3SjYMs=
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:in-reply-to
         :references:mime-version:content-transfer-encoding;
        bh=6WV52rOTICG5gX8Y1zv7jCBKQNXPiDy4YHeczZNq5R8=;
        b=PaOiuaSh9kHf/pw5y96TtBy91mEeA5aK7eqYnqqWMu3+oYmhuBk7Kcxhx11UIu1zTr
         s2sxGvImGhNrMNHDmZGiMlolYQfAXnfp2+DzU5UVlBYq0iKH/AkgjnnMQ6FBBKIDNET1
         3F057RVSdhU3ErKAVaK4RuMhhMqgGKdt6bF1FoHqFgCdF6OituAduIeKzG7Rt00hHaFX
         fl3oMIlzvUwsunSXblDK1AKnar4cAJ6NebgJtkBLNX/E2yusc6oLC/N6nhM7ZKdigR/z
         hZqJfHE0GxZlTI3k2YI4XmaygnO38FnPpNy6EG2LO6PF/ohKUCzK5DSZO51l5ceTSOMY
         vqyA==
X-Gm-Message-State: AOAM531tDHpHuiyKqImHbzSpMiH6LN1zM3JKsKwbWvrj9fH2CFVDcfKA
        DXULAm7LpesnYhm5jVpZpmTvTA==
X-Google-Smtp-Source: 
 ABdhPJzVBsxwLZIMYGLD3DYWXu1bp4LaH7S6HY6WbjQnf7B+QAB79jbRqX/pwaaSVhOsBfxmWuo57g==
X-Received: by 2002:a1c:59c3:: with SMTP id
 n186mr15451298wmb.32.1603709914185;
        Mon, 26 Oct 2020 03:58:34 -0700 (PDT)
Received: from phenom.ffwll.local ([2a02:168:57f4:0:efd0:b9e5:5ae6:c2fa])
        by smtp.gmail.com with ESMTPSA id
 w83sm21165156wmg.48.2020.10.26.03.58.32
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Mon, 26 Oct 2020 03:58:33 -0700 (PDT)
From: Daniel Vetter <daniel.vetter@ffwll.ch>
To: DRI Development <dri-devel@lists.freedesktop.org>,
        LKML <linux-kernel@vger.kernel.org>
Cc: kvm@vger.kernel.org, linux-mm@kvack.org,
 linux-arm-kernel@lists.infradead.org, linux-samsung-soc@vger.kernel.org,
 linux-media@vger.kernel.org, linux-s390@vger.kernel.org,
 Daniel Vetter <daniel.vetter@ffwll.ch>, John Hubbard <jhubbard@nvidia.com>,
 Mauro Carvalho Chehab <mchehab+huawei@kernel.org>,
 Daniel Vetter <daniel.vetter@intel.com>, Jason Gunthorpe <jgg@ziepe.ca>,
 Pawel Osciak <pawel@osciak.com>, Marek Szyprowski <m.szyprowski@samsung.com>,
 Kyungmin Park <kyungmin.park@samsung.com>, Tomasz Figa <tfiga@chromium.org>,
 Mauro Carvalho Chehab <mchehab@kernel.org>,
 Andrew Morton <akpm@linux-foundation.org>,
 =?utf-8?b?SsOpcsO0bWUgR2xpc3Nl?= <jglisse@redhat.com>,
 Jan Kara <jack@suse.cz>, Dan Williams <dan.j.williams@intel.com>
Subject: [PATCH v4 06/15] media: videobuf2: Move frame_vector into media
 subsystem
Date: Mon, 26 Oct 2020 11:58:09 +0100
Message-Id: <20201026105818.2585306-7-daniel.vetter@ffwll.ch>
X-Mailer: git-send-email 2.28.0
In-Reply-To: <20201026105818.2585306-1-daniel.vetter@ffwll.ch>
References: <20201026105818.2585306-1-daniel.vetter@ffwll.ch>
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

It's the only user. This also garbage collects the CONFIG_FRAME_VECTOR
symbol from all over the tree (well just one place, somehow omap media
driver still had this in its Kconfig, despite not using it).

Reviewed-by: John Hubbard <jhubbard@nvidia.com>
Acked-by: Mauro Carvalho Chehab <mchehab+huawei@kernel.org>
Signed-off-by: Daniel Vetter <daniel.vetter@intel.com>
Cc: Jason Gunthorpe <jgg@ziepe.ca>
Cc: Pawel Osciak <pawel@osciak.com>
Cc: Marek Szyprowski <m.szyprowski@samsung.com>
Cc: Kyungmin Park <kyungmin.park@samsung.com>
Cc: Tomasz Figa <tfiga@chromium.org>
Cc: Mauro Carvalho Chehab <mchehab@kernel.org>
Cc: Andrew Morton <akpm@linux-foundation.org>
Cc: John Hubbard <jhubbard@nvidia.com>
Cc: Jérôme Glisse <jglisse@redhat.com>
Cc: Jan Kara <jack@suse.cz>
Cc: Dan Williams <dan.j.williams@intel.com>
Cc: linux-mm@kvack.org
Cc: linux-arm-kernel@lists.infradead.org
Cc: linux-samsung-soc@vger.kernel.org
Cc: linux-media@vger.kernel.org
Cc: Daniel Vetter <daniel.vetter@ffwll.ch>
Signed-off-by: Daniel Vetter <daniel.vetter@ffwll.ch>
Acked-by: Tomasz Figa <tfiga@chromium.org>
---
v3:
- Create a new frame_vector.h header for this (Mauro)
---
 drivers/media/common/videobuf2/Kconfig        |  1 -
 drivers/media/common/videobuf2/Makefile       |  1 +
 .../media/common/videobuf2}/frame_vector.c    |  2 +
 drivers/media/platform/omap/Kconfig           |  1 -
 include/linux/mm.h                            | 42 -----------------
 include/media/frame_vector.h                  | 47 +++++++++++++++++++
 include/media/videobuf2-core.h                |  1 +
 mm/Kconfig                                    |  3 --
 mm/Makefile                                   |  1 -
 9 files changed, 51 insertions(+), 48 deletions(-)
 rename {mm => drivers/media/common/videobuf2}/frame_vector.c (99%)
 create mode 100644 include/media/frame_vector.h

```
#### [PATCH v4 04/15] misc/habana: Use FOLL_LONGTERM for userptr
##### From: Daniel Vetter <daniel.vetter@ffwll.ch>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 8bit
X-Patchwork-Submitter: Daniel Vetter <daniel.vetter@ffwll.ch>
X-Patchwork-Id: 11856503
Return-Path: <SRS0=RIF0=EB=vger.kernel.org=kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-12.8 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SIGNED_OFF_BY,SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED,
	USER_AGENT_GIT autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 44469C6379F
	for <kvm@archiver.kernel.org>; Mon, 26 Oct 2020 10:58:38 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id DDB7C223EA
	for <kvm@archiver.kernel.org>; Mon, 26 Oct 2020 10:58:37 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=ffwll.ch header.i=@ffwll.ch
 header.b="WDXic3xE"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1772756AbgJZK6g (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Mon, 26 Oct 2020 06:58:36 -0400
Received: from mail-wr1-f68.google.com ([209.85.221.68]:43019 "EHLO
        mail-wr1-f68.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1772585AbgJZK6e (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 26 Oct 2020 06:58:34 -0400
Received: by mail-wr1-f68.google.com with SMTP id g12so11870374wrp.10
        for <kvm@vger.kernel.org>; Mon, 26 Oct 2020 03:58:32 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=ffwll.ch; s=google;
        h=from:to:cc:subject:date:message-id:in-reply-to:references
         :mime-version:content-transfer-encoding;
        bh=fm+L1OZ5vnKeOGH1XwjpH65CAXQE2qGCwQHeV0BfCbo=;
        b=WDXic3xEelIUmmKBuCaAQhWAocM+J6l4Fj4ebPaY2TA7KjqktouI6kx1cuzB8y9UHb
         BFENQYpFYRrnf8V4M8FMdw5d3WVXp99ZQMaG9LdvbhHrDb1RPzEBMwS3mFEVGyKOFx19
         gvYOzFywjU6mguxvCAHNCjVghPiiwoY0kNQWY=
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:in-reply-to
         :references:mime-version:content-transfer-encoding;
        bh=fm+L1OZ5vnKeOGH1XwjpH65CAXQE2qGCwQHeV0BfCbo=;
        b=Hc4IWDa2a+e5jynK5lh4KfNJ571UQn9Cd9x4vFV+ABnJ63y30/Zy/LymF7ozXZ1ofu
         5ISSL3u9DW36RdDhkts44yZAUy+awv7eVpadnJTjqFE1n8eDrTNhDQY11FjgGP6V4/Gr
         juwMMpNjP2syvzGPY5rj/yq4FY6Ki37xavt6QuRjge5EduiNA71NaUbN1bWySYX+KMpD
         ecvwvzYDdFm/exKJj9W5PR1B7j7J0LZ8f+ga0OPUzYouCfr3nED4Q1HaEx9qr2NYazUO
         eY/DIspovnCYa6mobwwZYAdgJKRaEiGHXk4caUgh+i7MI4vlhGhVQrVJtirYPpgfVnde
         E2eA==
X-Gm-Message-State: AOAM5319+nLd/pGjvUclHxwf5QIJpB8oR0Smwqj7WBN2JDYsxilAYKkh
        nSRyrZwG5Z1f5+VdzzsMmmHYNQ==
X-Google-Smtp-Source: 
 ABdhPJweUKS7rePvehoYbUjnZ9k8M/DdLl55bpzabm8YcXT6EbKByVlIbEgXWPVVGpbtM3F7y6c03w==
X-Received: by 2002:adf:fa0e:: with SMTP id
 m14mr16288559wrr.134.1603709911230;
        Mon, 26 Oct 2020 03:58:31 -0700 (PDT)
Received: from phenom.ffwll.local ([2a02:168:57f4:0:efd0:b9e5:5ae6:c2fa])
        by smtp.gmail.com with ESMTPSA id
 w83sm21165156wmg.48.2020.10.26.03.58.29
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Mon, 26 Oct 2020 03:58:30 -0700 (PDT)
From: Daniel Vetter <daniel.vetter@ffwll.ch>
To: DRI Development <dri-devel@lists.freedesktop.org>,
        LKML <linux-kernel@vger.kernel.org>
Cc: kvm@vger.kernel.org, linux-mm@kvack.org,
 linux-arm-kernel@lists.infradead.org, linux-samsung-soc@vger.kernel.org,
 linux-media@vger.kernel.org, linux-s390@vger.kernel.org,
 Daniel Vetter <daniel.vetter@ffwll.ch>,
 Daniel Vetter <daniel.vetter@intel.com>, Jason Gunthorpe <jgg@ziepe.ca>,
 Andrew Morton <akpm@linux-foundation.org>,
 John Hubbard <jhubbard@nvidia.com>,
 =?utf-8?b?SsOpcsO0bWUgR2xpc3Nl?= <jglisse@redhat.com>,
 Jan Kara <jack@suse.cz>, Dan Williams <dan.j.williams@intel.com>,
 Oded Gabbay <oded.gabbay@gmail.com>, Omer Shpigelman <oshpigelman@habana.ai>,
 Ofir Bitton <obitton@habana.ai>, Tomer Tayar <ttayar@habana.ai>,
 Moti Haimovski <mhaimovski@habana.ai>,
 Greg Kroah-Hartman <gregkh@linuxfoundation.org>,
 Pawel Piskorski <ppiskorski@habana.ai>
Subject: [PATCH v4 04/15] misc/habana: Use FOLL_LONGTERM for userptr
Date: Mon, 26 Oct 2020 11:58:07 +0100
Message-Id: <20201026105818.2585306-5-daniel.vetter@ffwll.ch>
X-Mailer: git-send-email 2.28.0
In-Reply-To: <20201026105818.2585306-1-daniel.vetter@ffwll.ch>
References: <20201026105818.2585306-1-daniel.vetter@ffwll.ch>
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

These are persistent, not just for the duration of a dma operation.

Signed-off-by: Daniel Vetter <daniel.vetter@intel.com>
Cc: Jason Gunthorpe <jgg@ziepe.ca>
Cc: Andrew Morton <akpm@linux-foundation.org>
Cc: John Hubbard <jhubbard@nvidia.com>
Cc: Jérôme Glisse <jglisse@redhat.com>
Cc: Jan Kara <jack@suse.cz>
Cc: Dan Williams <dan.j.williams@intel.com>
Cc: linux-mm@kvack.org
Cc: linux-arm-kernel@lists.infradead.org
Cc: linux-samsung-soc@vger.kernel.org
Cc: linux-media@vger.kernel.org
Cc: Oded Gabbay <oded.gabbay@gmail.com>
Cc: Omer Shpigelman <oshpigelman@habana.ai>
Cc: Ofir Bitton <obitton@habana.ai>
Cc: Tomer Tayar <ttayar@habana.ai>
Cc: Moti Haimovski <mhaimovski@habana.ai>
Cc: Daniel Vetter <daniel.vetter@ffwll.ch>
Cc: Greg Kroah-Hartman <gregkh@linuxfoundation.org>
Cc: Pawel Piskorski <ppiskorski@habana.ai>
Signed-off-by: Daniel Vetter <daniel.vetter@ffwll.ch>
---
 drivers/misc/habanalabs/common/memory.c | 3 ++-
 1 file changed, 2 insertions(+), 1 deletion(-)

```
#### [PATCH v4 08/15] mm: Add unsafe_follow_pfn
##### From: Daniel Vetter <daniel.vetter@ffwll.ch>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 8bit
X-Patchwork-Submitter: Daniel Vetter <daniel.vetter@ffwll.ch>
X-Patchwork-Id: 11856505
Return-Path: <SRS0=RIF0=EB=vger.kernel.org=kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-12.8 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SIGNED_OFF_BY,SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED,
	USER_AGENT_GIT autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id E6941C5DF9D
	for <kvm@archiver.kernel.org>; Mon, 26 Oct 2020 10:58:45 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id AD6F422460
	for <kvm@archiver.kernel.org>; Mon, 26 Oct 2020 10:58:45 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=ffwll.ch header.i=@ffwll.ch
 header.b="LeOH7Nu7"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1772832AbgJZK6o (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Mon, 26 Oct 2020 06:58:44 -0400
Received: from mail-wm1-f68.google.com ([209.85.128.68]:55657 "EHLO
        mail-wm1-f68.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1772793AbgJZK6l (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 26 Oct 2020 06:58:41 -0400
Received: by mail-wm1-f68.google.com with SMTP id a72so11153852wme.5
        for <kvm@vger.kernel.org>; Mon, 26 Oct 2020 03:58:37 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=ffwll.ch; s=google;
        h=from:to:cc:subject:date:message-id:in-reply-to:references
         :mime-version:content-transfer-encoding;
        bh=Jw8O4zHShCAt4bi/mdSwE8pqaQ/Ci7nnAmM3jj6tKas=;
        b=LeOH7Nu7nYyzs6z+/KfV+foE7RZUakypEXEfU/vXenF6NA90yn3buwHE0Uu6W+NU5m
         Hi0AM14GFSueByuFTd94ZbnLe28erHjzsMvKFy0Os9VwT8Ga/ABZUV2quSB96oh4ck2n
         HGBn3CIltcz0TR3fcsi6KP6WJJBm9e95NWE9o=
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:in-reply-to
         :references:mime-version:content-transfer-encoding;
        bh=Jw8O4zHShCAt4bi/mdSwE8pqaQ/Ci7nnAmM3jj6tKas=;
        b=qmtQezvMn4l3LWN7QGNn19RWg585t9sV97NVjKnzrsOTzF6N5PB5V1PYqzcOJI3JH2
         fOVMvEgsmGRNh/6yHltgvL/iJlugY0iWeVKoSdhjHuSsY1cDoOwFTUgKC9oVzp+r59Hv
         RxaRJ+dLxc7kIUPdXaoifNVcv/yNh/aH3NtepCuOp3VEeGfUvste6/ZtOft5NZW6Q6ey
         9JrhpBwEGyUvWdhDW/lH9MiIwEAyVSHDHATZZoe6K9/TWFRS2WzcvrPXa3ZobJFcoG3B
         Ma7WUQ5jmOYmC2DExE6d742dMowy2Wi22rXvy9+n7d9iT4t5Qiyh/WMzeIrZvFC3qvlM
         GB0g==
X-Gm-Message-State: AOAM531fiG+EjGj6adR7lN/2wG2q0EcnfgRTU4hmyiUISgY1xz4TjyRU
        pvqSdQTHVb+m2dmBdmYTLDEybw==
X-Google-Smtp-Source: 
 ABdhPJwBkNEqxu0ChR0X2FBJPl4+XpnvlFPrjyvJkxjB1QLwg8t+SYJeWTboLEwPxYM+uDVWyRzgsA==
X-Received: by 2002:a1c:6643:: with SMTP id
 a64mr15848860wmc.142.1603709916809;
        Mon, 26 Oct 2020 03:58:36 -0700 (PDT)
Received: from phenom.ffwll.local ([2a02:168:57f4:0:efd0:b9e5:5ae6:c2fa])
        by smtp.gmail.com with ESMTPSA id
 w83sm21165156wmg.48.2020.10.26.03.58.35
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Mon, 26 Oct 2020 03:58:36 -0700 (PDT)
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
 Jan Kara <jack@suse.cz>
Subject: [PATCH v4 08/15] mm: Add unsafe_follow_pfn
Date: Mon, 26 Oct 2020 11:58:11 +0100
Message-Id: <20201026105818.2585306-9-daniel.vetter@ffwll.ch>
X-Mailer: git-send-email 2.28.0
In-Reply-To: <20201026105818.2585306-1-daniel.vetter@ffwll.ch>
References: <20201026105818.2585306-1-daniel.vetter@ffwll.ch>
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Way back it was a reasonable assumptions that iomem mappings never
change the pfn range they point at. But this has changed:

- gpu drivers dynamically manage their memory nowadays, invalidating
ptes with unmap_mapping_range when buffers get moved

- contiguous dma allocations have moved from dedicated carvetouts to
cma regions. This means if we miss the unmap the pfn might contain
pagecache or anon memory (well anything allocated with GFP_MOVEABLE)

- even /dev/mem now invalidates mappings when the kernel requests that
iomem region when CONFIG_IO_STRICT_DEVMEM is set, see 3234ac664a87
("/dev/mem: Revoke mappings when a driver claims the region")

Accessing pfns obtained from ptes without holding all the locks is
therefore no longer a good idea.

Unfortunately there's some users where this is not fixable (like v4l
userptr of iomem mappings) or involves a pile of work (vfio type1
iommu). For now annotate these as unsafe and splat appropriately.

This patch adds an unsafe_follow_pfn, which later patches will then
roll out to all appropriate places.

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
Cc: kvm@vger.kernel.org
Signed-off-by: Daniel Vetter <daniel.vetter@ffwll.ch>
---
 include/linux/mm.h |  2 ++
 mm/memory.c        | 32 +++++++++++++++++++++++++++++++-
 mm/nommu.c         | 17 +++++++++++++++++
 security/Kconfig   | 13 +++++++++++++
 4 files changed, 63 insertions(+), 1 deletion(-)

```
#### [PATCH v4 01/15] drm/exynos: Stop using frame_vector helpers
##### From: Daniel Vetter <daniel.vetter@ffwll.ch>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 8bit
X-Patchwork-Submitter: Daniel Vetter <daniel.vetter@ffwll.ch>
X-Patchwork-Id: 11856499
Return-Path: <SRS0=RIF0=EB=vger.kernel.org=kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-12.8 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SIGNED_OFF_BY,SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED,
	USER_AGENT_GIT autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id AC385C4363A
	for <kvm@archiver.kernel.org>; Mon, 26 Oct 2020 10:58:32 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 5F18A21BE5
	for <kvm@archiver.kernel.org>; Mon, 26 Oct 2020 10:58:32 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=ffwll.ch header.i=@ffwll.ch
 header.b="UlPNDMGy"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1772498AbgJZK6b (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Mon, 26 Oct 2020 06:58:31 -0400
Received: from mail-wm1-f67.google.com ([209.85.128.67]:35002 "EHLO
        mail-wm1-f67.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1772364AbgJZK6a (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 26 Oct 2020 06:58:30 -0400
Received: by mail-wm1-f67.google.com with SMTP id h22so878747wmb.0
        for <kvm@vger.kernel.org>; Mon, 26 Oct 2020 03:58:27 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=ffwll.ch; s=google;
        h=from:to:cc:subject:date:message-id:in-reply-to:references
         :mime-version:content-transfer-encoding;
        bh=5HSDx6z2iUpxgLk7STJ2LBrJWLho+Vrj3pPui9pXoI8=;
        b=UlPNDMGyixYlC+gPNujgEL2rDmgBnacLev+zB09AcN9jWsIhwDD/rSZ38jOBVqq8xO
         iKAMMw2Dn+O1sn5M45MuUANko75LMiByct+0sTK4Y1zG/mkhWRt6wfXXCeYyMZpxuDFP
         ohoyHxlTs9ukBeuTT1XZ/1TieNop7LHOqq+kU=
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:in-reply-to
         :references:mime-version:content-transfer-encoding;
        bh=5HSDx6z2iUpxgLk7STJ2LBrJWLho+Vrj3pPui9pXoI8=;
        b=nBIdfKXaCRclG+ImbWXLrWAjPtJ3/AnYj9FUWdirultfAE0open7FZ+wsYlxwaCW/e
         AOvFipcF3+PYovxH2YrYvv8zcxd2AclPYI95ecX76as8ZjLMoJeui51ssIFGubDy7NA4
         Jfu6W25/RLmP0KlDaLHRIKHWFnBPznPE/t4aW4ywff0eyNEpsfWa63JvwNq4EWWbdG7o
         g5VqNbD4vBVip0TDxFvsX9ZQr3CdXuOQ2g/p5T2cEd3bwVQd4+peDgrha/PA/7Ef5IPT
         32es97KpsCbRMf9n8pMHoc0nOcofZS8bAMf9FsvaCQJe2Y012GsR33QzqKHw2yKCD3Ly
         BNjw==
X-Gm-Message-State: AOAM532eyVJWxF4teGbWQBHRVtXZpauR+3YdumxcmNePkH1H4M7iWgwF
        8B04BiIj363Ry+Uy/m9P0qQzIQ==
X-Google-Smtp-Source: 
 ABdhPJwk+WyO7L+7DmDEv6NKzv9NT0FNUGzlLjoe/puysIw3cSVvPS9bRY2rLzmA6270BRM/TeV4wg==
X-Received: by 2002:a05:600c:25a:: with SMTP id
 26mr14956631wmj.39.1603709906608;
        Mon, 26 Oct 2020 03:58:26 -0700 (PDT)
Received: from phenom.ffwll.local ([2a02:168:57f4:0:efd0:b9e5:5ae6:c2fa])
        by smtp.gmail.com with ESMTPSA id
 w83sm21165156wmg.48.2020.10.26.03.58.25
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Mon, 26 Oct 2020 03:58:25 -0700 (PDT)
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
 Jan Kara <jack@suse.cz>, Dan Williams <dan.j.williams@intel.com>
Subject: [PATCH v4 01/15] drm/exynos: Stop using frame_vector helpers
Date: Mon, 26 Oct 2020 11:58:04 +0100
Message-Id: <20201026105818.2585306-2-daniel.vetter@ffwll.ch>
X-Mailer: git-send-email 2.28.0
In-Reply-To: <20201026105818.2585306-1-daniel.vetter@ffwll.ch>
References: <20201026105818.2585306-1-daniel.vetter@ffwll.ch>
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
Signed-off-by: Daniel Vetter <daniel.vetter@ffwll.ch>
---
v2: Use unpin_user_pages_dirty_lock (John)
---
 drivers/gpu/drm/exynos/Kconfig          |  1 -
 drivers/gpu/drm/exynos/exynos_drm_g2d.c | 47 +++++++++++--------------
 2 files changed, 20 insertions(+), 28 deletions(-)

```
#### [PATCH 1/8] KVM: arm64: Don't corrupt tpidr_el2 on failed HVC call
##### From: Marc Zyngier <maz@kernel.org>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Marc Zyngier <maz@kernel.org>
X-Patchwork-Id: 11856223
Return-Path: <SRS0=RIF0=EB=vger.kernel.org=kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-13.1 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,INCLUDES_PATCH,MAILING_LIST_MULTI,
	SIGNED_OFF_BY,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT autolearn=ham
	autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 13E73C2D0A3
	for <kvm@archiver.kernel.org>; Mon, 26 Oct 2020 09:51:49 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id CCBED223AC
	for <kvm@archiver.kernel.org>; Mon, 26 Oct 2020 09:51:48 +0000 (UTC)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple; d=kernel.org;
	s=default; t=1603705908;
	bh=M9e70BEFvF5FajpDUL4748IzzfhwguzKhvy5dXrsgVY=;
	h=From:To:Cc:Subject:Date:In-Reply-To:References:List-ID:From;
	b=HuV0j0yEm2avGpMfz48H+Ik6NSYjDI8ijKkGBJanrwsd6wM6UVVixRWF5aRFnQHjj
	 YWYcyB0Tv0kmzfrml9B69Bvx+J58gvjmLu+avBCeVXErHCjZD+7HIwRjloUA7Zxysx
	 exYibOl9igQFsX4VJigLU6HpVqBPaZDinRQiwfIY=
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1768646AbgJZJvs (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Mon, 26 Oct 2020 05:51:48 -0400
Received: from mail.kernel.org ([198.145.29.99]:44100 "EHLO mail.kernel.org"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1737069AbgJZJvc (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 26 Oct 2020 05:51:32 -0400
Received: from disco-boy.misterjones.org (disco-boy.misterjones.org
 [51.254.78.96])
        (using TLSv1.2 with cipher ECDHE-RSA-AES256-GCM-SHA384 (256/256 bits))
        (No client certificate requested)
        by mail.kernel.org (Postfix) with ESMTPSA id 9AB82222EC;
        Mon, 26 Oct 2020 09:51:31 +0000 (UTC)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple; d=kernel.org;
        s=default; t=1603705891;
        bh=M9e70BEFvF5FajpDUL4748IzzfhwguzKhvy5dXrsgVY=;
        h=From:To:Cc:Subject:Date:In-Reply-To:References:From;
        b=vROdnfbQxI4Ju2iB6xoCt7CemBetIOumxE1d+KQqxDvEdVsJnhGCsSIb2cfp+IrKt
         4asYcTyiMm1cYQIk95FWa4uF7WlLY8FflURgUu+ArxLtXpX68VgL5n65f4aZ2VSVim
         NhcyLDWCyx2LKy2f+gKC3uOIDnTuflgQBp3P5A2w=
Received: from 78.163-31-62.static.virginmediabusiness.co.uk ([62.31.163.78]
 helo=why.lan)
        by disco-boy.misterjones.org with esmtpsa  (TLS1.3) tls
 TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384
        (Exim 4.94)
        (envelope-from <maz@kernel.org>)
        id 1kWzA1-004HZn-Qc; Mon, 26 Oct 2020 09:51:29 +0000
From: Marc Zyngier <maz@kernel.org>
To: linux-arm-kernel@lists.infradead.org, kvmarm@lists.cs.columbia.edu,
        kvm@vger.kernel.org
Cc: James Morse <james.morse@arm.com>,
        Julien Thierry <julien.thierry.kdev@gmail.com>,
        Suzuki K Poulose <suzuki.poulose@arm.com>,
        Andrew Scull <ascull@google.com>,
        Will Deacon <will@kernel.org>,
        Quentin Perret <qperret@google.com>, kernel-team@android.com
Subject: [PATCH 1/8] KVM: arm64: Don't corrupt tpidr_el2 on failed HVC call
Date: Mon, 26 Oct 2020 09:51:09 +0000
Message-Id: <20201026095116.72051-2-maz@kernel.org>
X-Mailer: git-send-email 2.28.0
In-Reply-To: <20201026095116.72051-1-maz@kernel.org>
References: <20201026095116.72051-1-maz@kernel.org>
MIME-Version: 1.0
X-SA-Exim-Connect-IP: 62.31.163.78
X-SA-Exim-Rcpt-To: linux-arm-kernel@lists.infradead.org,
 kvmarm@lists.cs.columbia.edu, kvm@vger.kernel.org, james.morse@arm.com,
 julien.thierry.kdev@gmail.com, suzuki.poulose@arm.com, ascull@google.com,
 will@kernel.org, qperret@google.com, kernel-team@android.com
X-SA-Exim-Mail-From: maz@kernel.org
X-SA-Exim-Scanned: No (on disco-boy.misterjones.org);
 SAEximRunCond expanded to false
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The hyp-init code starts by stashing a register in TPIDR_EL2
in in order to free a register. This happens no matter if the
HVC call is legal or not.

Although nothing wrong seems to come out of it, it feels odd
to alter the EL2 state for something that eventually returns
an error.

Instead, use the fact that we know exactly which bits of the
__kvm_hyp_init call are non-zero to perform the check with
a series of EOR/ROR instructions, combined with a build-time
check that the value is the one we expect.

Signed-off-by: Marc Zyngier <maz@kernel.org>
---
 arch/arm64/kvm/hyp/nvhe/hyp-init.S | 23 ++++++++++++++++-------
 1 file changed, 16 insertions(+), 7 deletions(-)

```
#### [PATCH 01/11] KVM: arm64: Don't adjust PC on SError during SMC trap
##### From: Marc Zyngier <maz@kernel.org>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Marc Zyngier <maz@kernel.org>
X-Patchwork-Id: 11857157
Return-Path: <SRS0=RIF0=EB=vger.kernel.org=kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-13.1 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,INCLUDES_PATCH,MAILING_LIST_MULTI,
	SIGNED_OFF_BY,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT autolearn=ham
	autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 4EE1FC55178
	for <kvm@archiver.kernel.org>; Mon, 26 Oct 2020 13:35:06 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 0A8E32466D
	for <kvm@archiver.kernel.org>; Mon, 26 Oct 2020 13:35:06 +0000 (UTC)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple; d=kernel.org;
	s=default; t=1603719306;
	bh=TIdQZHOLY3CZDa6jwupO4ZWOOWoZjjI2rodoMOV6gYg=;
	h=From:To:Cc:Subject:Date:In-Reply-To:References:List-ID:From;
	b=quB6/cHFTPz8i5c5Lm9NDs4GwHxvqeRdIxt+yWZC4b8O/nOVDgOgXB2AGQv7syToX
	 USwfLCm3M7KJxggzzVxXEbFDRZ6UFXql0UmPCj8fH6nKgLGoEKyX/gVZyztIlmOeDS
	 a1MQZsygg2n25/dm1l8zfNC6RlRxqKPsBGfiC/4k=
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1780172AbgJZNfE (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Mon, 26 Oct 2020 09:35:04 -0400
Received: from mail.kernel.org ([198.145.29.99]:37660 "EHLO mail.kernel.org"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1769829AbgJZNfD (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 26 Oct 2020 09:35:03 -0400
Received: from disco-boy.misterjones.org (disco-boy.misterjones.org
 [51.254.78.96])
        (using TLSv1.2 with cipher ECDHE-RSA-AES256-GCM-SHA384 (256/256 bits))
        (No client certificate requested)
        by mail.kernel.org (Postfix) with ESMTPSA id 3A0A2206DD;
        Mon, 26 Oct 2020 13:35:02 +0000 (UTC)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple; d=kernel.org;
        s=default; t=1603719302;
        bh=TIdQZHOLY3CZDa6jwupO4ZWOOWoZjjI2rodoMOV6gYg=;
        h=From:To:Cc:Subject:Date:In-Reply-To:References:From;
        b=0XiQc1YaawD3KrbpMjJOofZIyB46pXzYDX++ofOiNKX+sAaSaz0CpNd8Z5B5pUYo5
         +rssYtwUHObh3rBUnRmERNFhFlmnhhFx1TeK3X1VOMihBHDCFIlVtHARXv7PT/Ya1r
         HxGZYG2pa/o9sExl5SWkLR9VJsp9oNWBPx6gU7t4=
Received: from 78.163-31-62.static.virginmediabusiness.co.uk ([62.31.163.78]
 helo=why.lan)
        by disco-boy.misterjones.org with esmtpsa  (TLS1.3) tls
 TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384
        (Exim 4.94)
        (envelope-from <maz@kernel.org>)
        id 1kX2eK-004Kjh-En; Mon, 26 Oct 2020 13:35:00 +0000
From: Marc Zyngier <maz@kernel.org>
To: linux-arm-kernel@lists.infradead.org, kvmarm@lists.cs.columbia.edu,
        kvm@vger.kernel.org
Cc: James Morse <james.morse@arm.com>,
        Julien Thierry <julien.thierry.kdev@gmail.com>,
        Suzuki K Poulose <suzuki.poulose@arm.com>,
        Andrew Scull <ascull@google.com>,
        Will Deacon <will@kernel.org>,
        Quentin Perret <qperret@google.com>,
        David Brazdil <dbrazdil@google.com>, kernel-team@android.com
Subject: [PATCH 01/11] KVM: arm64: Don't adjust PC on SError during SMC trap
Date: Mon, 26 Oct 2020 13:34:40 +0000
Message-Id: <20201026133450.73304-2-maz@kernel.org>
X-Mailer: git-send-email 2.28.0
In-Reply-To: <20201026133450.73304-1-maz@kernel.org>
References: <20201026133450.73304-1-maz@kernel.org>
MIME-Version: 1.0
X-SA-Exim-Connect-IP: 62.31.163.78
X-SA-Exim-Rcpt-To: linux-arm-kernel@lists.infradead.org,
 kvmarm@lists.cs.columbia.edu, kvm@vger.kernel.org, james.morse@arm.com,
 julien.thierry.kdev@gmail.com, suzuki.poulose@arm.com, ascull@google.com,
 will@kernel.org, qperret@google.com, dbrazdil@google.com,
 kernel-team@android.com
X-SA-Exim-Mail-From: maz@kernel.org
X-SA-Exim-Scanned: No (on disco-boy.misterjones.org);
 SAEximRunCond expanded to false
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

On SMC trap, the prefered return address is set to that of the SMC
instruction itself. It is thus wrong to tyr and roll it back when
an SError occurs while trapping on SMC. It is still necessary on
HVC though, as HVC doesn't cause a trap, and sets ELR to returning
*after* the HVC.

It also became apparent that the is 16bit encoding for an AArch32
HVC instruction, meaning that the displacement is always 4 bytes,
no matter what the ISA is. Take this opportunity to simplify it.

Signed-off-by: Marc Zyngier <maz@kernel.org>
Acked-by: Mark Rutland <mark.rutland@arm.com>
---
 arch/arm64/kvm/handle_exit.c | 16 ++++++++--------
 1 file changed, 8 insertions(+), 8 deletions(-)

```
#### [PATCH] KVM: selftests: test behavior of unmapped L2 APIC-access address
##### From: Jim Mattson <jmattson@google.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Jim Mattson <jmattson@google.com>
X-Patchwork-Id: 11858113
Return-Path: <SRS0=RIF0=EB=vger.kernel.org=kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-20.4 required=3.0 tests=BAYES_00,DKIMWL_WL_MED,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_PATCH,MAILING_LIST_MULTI,SIGNED_OFF_BY,SPF_HELO_NONE,SPF_PASS,
	USER_AGENT_GIT,USER_IN_DEF_DKIM_WL autolearn=ham autolearn_force=no
	version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 189BEC2D0A3
	for <kvm@archiver.kernel.org>; Mon, 26 Oct 2020 18:09:35 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id AFDF320829
	for <kvm@archiver.kernel.org>; Mon, 26 Oct 2020 18:09:34 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=google.com header.i=@google.com
 header.b="FfTY0xzW"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1789232AbgJZSJd (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Mon, 26 Oct 2020 14:09:33 -0400
Received: from mail-pl1-f202.google.com ([209.85.214.202]:49127 "EHLO
        mail-pl1-f202.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1783424AbgJZSJc (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 26 Oct 2020 14:09:32 -0400
Received: by mail-pl1-f202.google.com with SMTP id w16so6651317ply.15
        for <kvm@vger.kernel.org>; Mon, 26 Oct 2020 11:09:31 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=sender:date:message-id:mime-version:subject:from:to:cc;
        bh=zYeU5E36ZI2chRmPSnZCOPYqmRd6q1YSpnXrtYp1BPQ=;
        b=FfTY0xzW4VWKnPUk3ml3P0e/U422vUS761R0MrlqUp5J6+E2RV8HoktdgbqHTbkR/h
         wAaGXSjrhZeOxYWxhWfyQpo2BGTSL5NZSd1So77+Pa7dP4Lg7nenTl3xbepMKwBr9qNO
         Nxru9qTyMUdJxRHcAn2TZzNm4vzOB+w9I+9/BsE/w24I2d/HFuFaSLZJmTet/6s2IA7z
         TfQLZMG61Uzvqj+knwGlDz5WZk3VP6eHxm4Y334OH089HS+GU1X/m/+vyzuOy3sDXHeq
         4fVKErKC93IOV2mPHm6tBuWNsOIJy6+RS/xf613gY5wxMwBTfv373qlVgQkeGhOsLQCD
         TL8Q==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:sender:date:message-id:mime-version:subject:from
         :to:cc;
        bh=zYeU5E36ZI2chRmPSnZCOPYqmRd6q1YSpnXrtYp1BPQ=;
        b=ILlNvrnHyxQKXp2cywAOfDTg/iCMF3AkTO+qsmHLd1ynKsrCdnsj+Yq081IXLw6McM
         Yc86U5pob3+YBrovzGUiB8VvgZhRBLumQ34PDl0cGR1/dLK2ze0pLULssqB8vMH3hrXU
         O3/6ZaD4QQ0CWaLjw/yWc9bdiQj6zL0kbEIgfbWxSAOM5x40cKF9U47EhYOC4m2a19v7
         3sxY9z7MTmX4GW2lBeecaFD7K7yC80bgjan7azoWg/aqrxWgzrUiWKu5YANehQXZkOOz
         VeTLQUAg14E7si/cLnW2ZvAq4EnrgJgw4462RCN5e2l1xBb0thkir/8CZ2e7Lm1AYdlK
         AgWw==
X-Gm-Message-State: AOAM531usVl3dhGIeEVHm+qJjqE26J4cWqLv+6LmPsnLUhIuy6qIh7BS
        Y2iJcMKRMfon2F6FZMZdiJcLxIIT+2rvCw6yH3QS6X0+MArym4BNHCELPdAv3Zn8OnTgUIqc6dg
        4wFwFjgo/LKUf9sWvPYQgawp1gLlw+pY15nmIucHS8sSBExt6DfSdjk4dR8aruhM=
X-Google-Smtp-Source: 
 ABdhPJztKiTo01sBU3Q1QZvRSsc9TBaR/pfQTRtRcUNeY63pjYAQfs42JQhKBHW9FMyDGZ3F5L2iuTWU+sVIMQ==
Sender: "jmattson via sendgmr" <jmattson@turtle.sea.corp.google.com>
X-Received: from turtle.sea.corp.google.com
 ([2620:15c:100:202:725a:fff:fe43:64b1])
 (user=jmattson job=sendgmr) by 2002:a17:90a:d590:: with SMTP id
 v16mr17946741pju.88.1603735771282; Mon, 26 Oct 2020 11:09:31 -0700 (PDT)
Date: Mon, 26 Oct 2020 11:09:22 -0700
Message-Id: <20201026180922.3120555-1-jmattson@google.com>
Mime-Version: 1.0
X-Mailer: git-send-email 2.29.0.rc1.297.gfa9743e501-goog
Subject: [PATCH] KVM: selftests: test behavior of unmapped L2 APIC-access
 address
From: Jim Mattson <jmattson@google.com>
To: kvm@vger.kernel.org, Paolo Bonzini <pbonzini@redhat.com>
Cc: Jim Mattson <jmattson@google.com>,
        Ricardo Koller <ricarkol@google.com>,
        Peter Shier <pshier@google.com>
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Add a regression test for commit 671ddc700fd0 ("KVM: nVMX: Don't leak
L1 MMIO regions to L2").

First, check to see that an L2 guest can be launched with a valid
APIC-access address that is backed by a page of L1 physical memory.

Next, set the APIC-access address to a (valid) L1 physical address
that is not backed by memory. KVM can't handle this situation, so
resuming L2 should result in a KVM exit for internal error
(emulation).

Signed-off-by: Jim Mattson <jmattson@google.com>
Reviewed-by: Ricardo Koller <ricarkol@google.com>
Reviewed-by: Peter Shier <pshier@google.com>
---
 tools/testing/selftests/kvm/.gitignore        |   1 +
 tools/testing/selftests/kvm/Makefile          |   1 +
 .../selftests/kvm/include/x86_64/vmx.h        |   6 +
 tools/testing/selftests/kvm/lib/x86_64/vmx.c  |   9 ++
 .../kvm/x86_64/vmx_apic_access_test.c         | 142 ++++++++++++++++++
 5 files changed, 159 insertions(+)
 create mode 100644 tools/testing/selftests/kvm/x86_64/vmx_apic_access_test.c

```
#### [PATCH 7/8] KVM: arm64: Simplify __kvm_enable_ssbs()
##### From: Marc Zyngier <maz@kernel.org>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Marc Zyngier <maz@kernel.org>
X-Patchwork-Id: 11856229
Return-Path: <SRS0=RIF0=EB=vger.kernel.org=kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-13.1 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,INCLUDES_PATCH,MAILING_LIST_MULTI,
	SIGNED_OFF_BY,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT autolearn=unavailable
	autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 08037C388F9
	for <kvm@archiver.kernel.org>; Mon, 26 Oct 2020 09:51:48 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id B023B20874
	for <kvm@archiver.kernel.org>; Mon, 26 Oct 2020 09:51:47 +0000 (UTC)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple; d=kernel.org;
	s=default; t=1603705907;
	bh=iXV3E2z/slo20WC0V3cblfjeTSEIcPapQ/Yewe0mKc0=;
	h=From:To:Cc:Subject:Date:In-Reply-To:References:List-ID:From;
	b=ky9cweqUJ4tvUGNgrzbefOf72HbnMj+ZvNftUDqQYFfzE9i5tXs5GAmU0ztJrzWmh
	 Ep/gg+tueL3/THTZcZMbOgzgiN8BsGwgwGnkRoo+u63bLhIVNgdEy3rAqjknDP8RBl
	 c/ha1jqEhlfupM57eZZKhaer7J4gRC0IkzMNZHQ8=
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1768642AbgJZJvq (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Mon, 26 Oct 2020 05:51:46 -0400
Received: from mail.kernel.org ([198.145.29.99]:44312 "EHLO mail.kernel.org"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1744058AbgJZJvf (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 26 Oct 2020 05:51:35 -0400
Received: from disco-boy.misterjones.org (disco-boy.misterjones.org
 [51.254.78.96])
        (using TLSv1.2 with cipher ECDHE-RSA-AES256-GCM-SHA384 (256/256 bits))
        (No client certificate requested)
        by mail.kernel.org (Postfix) with ESMTPSA id B4FCD20704;
        Mon, 26 Oct 2020 09:51:34 +0000 (UTC)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple; d=kernel.org;
        s=default; t=1603705894;
        bh=iXV3E2z/slo20WC0V3cblfjeTSEIcPapQ/Yewe0mKc0=;
        h=From:To:Cc:Subject:Date:In-Reply-To:References:From;
        b=1G82dADv4qiv/PlTgluqvce2lhYajgrRhWQfxWhD26+qkPtCqwzh33Cc73ZH+YCj6
         1icoLD+Ym80cOYWI/1IrHzk+r7JImXTptGXnCWZH87gG4f3PpTYhtQqv9J6p2IcDn4
         HtCxe2n1WbXOemW4Zcm4kbI7w0PHNTRm45zUjsZA=
Received: from 78.163-31-62.static.virginmediabusiness.co.uk ([62.31.163.78]
 helo=why.lan)
        by disco-boy.misterjones.org with esmtpsa  (TLS1.3) tls
 TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384
        (Exim 4.94)
        (envelope-from <maz@kernel.org>)
        id 1kWzA4-004HZn-UP; Mon, 26 Oct 2020 09:51:33 +0000
From: Marc Zyngier <maz@kernel.org>
To: linux-arm-kernel@lists.infradead.org, kvmarm@lists.cs.columbia.edu,
        kvm@vger.kernel.org
Cc: James Morse <james.morse@arm.com>,
        Julien Thierry <julien.thierry.kdev@gmail.com>,
        Suzuki K Poulose <suzuki.poulose@arm.com>,
        Andrew Scull <ascull@google.com>,
        Will Deacon <will@kernel.org>,
        Quentin Perret <qperret@google.com>, kernel-team@android.com
Subject: [PATCH 7/8] KVM: arm64: Simplify __kvm_enable_ssbs()
Date: Mon, 26 Oct 2020 09:51:15 +0000
Message-Id: <20201026095116.72051-8-maz@kernel.org>
X-Mailer: git-send-email 2.28.0
In-Reply-To: <20201026095116.72051-1-maz@kernel.org>
References: <20201026095116.72051-1-maz@kernel.org>
MIME-Version: 1.0
X-SA-Exim-Connect-IP: 62.31.163.78
X-SA-Exim-Rcpt-To: linux-arm-kernel@lists.infradead.org,
 kvmarm@lists.cs.columbia.edu, kvm@vger.kernel.org, james.morse@arm.com,
 julien.thierry.kdev@gmail.com, suzuki.poulose@arm.com, ascull@google.com,
 will@kernel.org, qperret@google.com, kernel-team@android.com
X-SA-Exim-Mail-From: maz@kernel.org
X-SA-Exim-Scanned: No (on disco-boy.misterjones.org);
 SAEximRunCond expanded to false
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Move the setting of SSBS directly into the HVC handler, using
the C helpers rather than the inline asssembly code.

Signed-off-by: Marc Zyngier <maz@kernel.org>
Reviewed-by: Alexandru Elisei <alexandru.elisei@arm.com>
---
 arch/arm64/include/asm/kvm_asm.h    |  2 --
 arch/arm64/include/asm/sysreg.h     |  1 +
 arch/arm64/kvm/hyp/nvhe/hyp-main.c  |  6 +++++-
 arch/arm64/kvm/hyp/nvhe/sysreg-sr.c | 11 -----------
 4 files changed, 6 insertions(+), 14 deletions(-)

```
#### [RFC PATCH 1/2] sched/wait: Add add_wait_queue_priority()
##### From: David Woodhouse <dwmw2@infradead.org>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: David Woodhouse <dwmw2@infradead.org>
X-Patchwork-Id: 11857995
Return-Path: <SRS0=RIF0=EB=vger.kernel.org=kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-12.9 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SIGNED_OFF_BY,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT
	autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 970A1C388F9
	for <kvm@archiver.kernel.org>; Mon, 26 Oct 2020 17:53:45 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 5023E22281
	for <kvm@archiver.kernel.org>; Mon, 26 Oct 2020 17:53:45 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=infradead.org header.i=@infradead.org
 header.b="OOi9IhPP"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1788609AbgJZRxl (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Mon, 26 Oct 2020 13:53:41 -0400
Received: from casper.infradead.org ([90.155.50.34]:46426 "EHLO
        casper.infradead.org" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1781494AbgJZRxl (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 26 Oct 2020 13:53:41 -0400
DKIM-Signature: v=1; a=rsa-sha256; q=dns/txt; c=relaxed/relaxed;
        d=infradead.org; s=casper.20170209;
 h=Sender:Content-Transfer-Encoding:
        MIME-Version:Message-Id:Date:Subject:To:From:Reply-To:Cc:Content-Type:
        Content-ID:Content-Description:In-Reply-To:References;
        bh=FBYzkNP+Cx2t2+3fMBPbsAF59I/mFG4FBtQVNq5FELU=;
 b=OOi9IhPPOXxjSjoIy5MiTJk6Zk
        3x3IjQEqzm0akf8SgC6HRY7vPt354oCO5ldxZDm7wddxMLSxc/06+SWeIfqeFjR7YZ/GvzdaTqLjO
        D4SOc3xGC94d8GQtMsKBjt3GvrIxgo/RuTORS5H+24MfdUd3yePkQbFfntv0AgRR942Z8cC/EWrza
        JmFm3I7Rrc+y8uBWe/nVAqfh27Ho1ScOTfkzNwJVGWozsi4skFFQOgoTGDP1UCx7ZEQTGlsI8hoLm
        sKgSQbmrSsX5O+qzHWG9ENThF5W7P1BsEgLTOHd/I5Oe0ZjuFwu1Hw+4cP38ZpKthir9fUflqH79r
        udE24Rww==;
Received: from i7.infradead.org ([2001:8b0:10b:1:21e:67ff:fecb:7a92])
        by casper.infradead.org with esmtpsa (Exim 4.92.3 #3 (Red Hat Linux))
        id 1kX6gQ-0008Em-C8; Mon, 26 Oct 2020 17:53:27 +0000
Received: from dwoodhou by i7.infradead.org with local (Exim 4.93 #3 (Red Hat
 Linux))
        id 1kX6gP-002SMG-Um; Mon, 26 Oct 2020 17:53:25 +0000
From: David Woodhouse <dwmw2@infradead.org>
To: Ingo Molnar <mingo@redhat.com>,
        Peter Zijlstra <peterz@infradead.org>,
        Juri Lelli <juri.lelli@redhat.com>,
        Vincent Guittot <vincent.guittot@linaro.org>,
        Dietmar Eggemann <dietmar.eggemann@arm.com>,
        Steven Rostedt <rostedt@goodmis.org>,
        Ben Segall <bsegall@google.com>, Mel Gorman <mgorman@suse.de>,
        Daniel Bristot de Oliveira <bristot@redhat.com>,
        Paolo Bonzini <pbonzini@redhat.com>,
        linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Subject: [RFC PATCH 1/2] sched/wait: Add add_wait_queue_priority()
Date: Mon, 26 Oct 2020 17:53:24 +0000
Message-Id: <20201026175325.585623-1-dwmw2@infradead.org>
X-Mailer: git-send-email 2.26.2
MIME-Version: 1.0
Sender: David Woodhouse <dwmw2@infradead.org>
X-SRS-Rewrite: SMTP reverse-path rewritten from <dwmw2@infradead.org> by
 casper.infradead.org. See http://www.infradead.org/rpr.html
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: David Woodhouse <dwmw@amazon.co.uk>

This allows an exclusive wait_queue_entry to be added at the head of the
queue, instead of the tail as normal. Thus, it gets to consume events
first.

The problem I'm trying to solve here is interrupt remapping invalidation
vs. MSI interrupts from VFIO. I'd really like KVM IRQFD to be able to
consume events before (and indeed instead of) userspace.

When the remapped MSI target in the KVM routing table is invalidated,
the VMM needs to *deassociate* the IRQFD and fall back to handling the
next IRQ in userspace, so it can be retranslated and a fault reported
if appropriate.

It's possible to do that by constantly registering and deregistering the
fd in the userspace poll loop, but it gets ugly especially because the
fallback handler isn't really local to the core MSI handling.

It's much nicer if the userspace handler can just remain registered all
the time, and it just doesn't get any events when KVM steals them first.
Which is precisely what happens with posted interrupts, and this makes
it consistent. (Unless I'm missing something that prevents posted
interrupts from working when there's another listener on the eventfd?)

Signed-off-by: David Woodhouse <dwmw@amazon.co.uk>
---
 include/linux/wait.h | 12 +++++++++++-
 kernel/sched/wait.c  | 11 +++++++++++
 2 files changed, 22 insertions(+), 1 deletion(-)

```
#### [PATCH 01/13] update-linux-headers: Add vfio_zdev.h
##### From: Matthew Rosato <mjrosato@linux.ibm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Matthew Rosato <mjrosato@linux.ibm.com>
X-Patchwork-Id: 11857601
Return-Path: <SRS0=RIF0=EB=vger.kernel.org=kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-12.8 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_PATCH,MAILING_LIST_MULTI,
	SIGNED_OFF_BY,SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED,USER_AGENT_GIT
	autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 8219BC4363A
	for <kvm@archiver.kernel.org>; Mon, 26 Oct 2020 15:36:19 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 2E56222404
	for <kvm@archiver.kernel.org>; Mon, 26 Oct 2020 15:36:19 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=ibm.com header.i=@ibm.com
 header.b="PEAizcp4"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1784001AbgJZPgR (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Mon, 26 Oct 2020 11:36:17 -0400
Received: from mx0b-001b2d01.pphosted.com ([148.163.158.5]:40322 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S1783972AbgJZPgQ (ORCPT
        <rfc822;kvm@vger.kernel.org>); Mon, 26 Oct 2020 11:36:16 -0400
Received: from pps.filterd (m0098413.ppops.net [127.0.0.1])
        by mx0b-001b2d01.pphosted.com (8.16.0.42/8.16.0.42) with SMTP id
 09QFYdZd149857;
        Mon, 26 Oct 2020 11:36:10 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=ibm.com;
 h=from : to : cc : subject
 : date : message-id : in-reply-to : references; s=pp1;
 bh=AI6G3uU93CU8bLdSMBhPGAx8YLkIta1L8iMvDrv9MmY=;
 b=PEAizcp4+5x8BBlBiDFRVOkfGcdWUneWth4hcJaXT8cpa4KPStpdkhmQ+rG23VK3OtDz
 +atw4n9/CuABm/J05o6eGE4zuCG7MlbdDgr46cFelxnVkHm37ZLus3CmSmPZWK9AfHI+
 NUHpLss3ojQ9FUgrxJfAfX7LlzyWGEjRfap62/Pi6BJq+5oxiUAuM9B9nKUjZfVPV54L
 XW6f0yfb48+gNitH0EANfg7aC1KutWyPbgUGdzUL7dofBS8sf7Ih2E6FGC4G00MhHfOF
 5fID+3N1qUGG2aJ7xIx8Nl96/XZjB3T3V8E1Iz76dXmQ5Y4S7lY2ZFAuHsd6zFfALIiu xA==
Received: from pps.reinject (localhost [127.0.0.1])
        by mx0b-001b2d01.pphosted.com with ESMTP id 34dbg5m8wt-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Mon, 26 Oct 2020 11:36:10 -0400
Received: from m0098413.ppops.net (m0098413.ppops.net [127.0.0.1])
        by pps.reinject (8.16.0.36/8.16.0.36) with SMTP id 09QFZQQE153158;
        Mon, 26 Oct 2020 11:36:10 -0400
Received: from ppma03dal.us.ibm.com (b.bd.3ea9.ip4.static.sl-reverse.com
 [169.62.189.11])
        by mx0b-001b2d01.pphosted.com with ESMTP id 34dbg5m8we-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Mon, 26 Oct 2020 11:36:10 -0400
Received: from pps.filterd (ppma03dal.us.ibm.com [127.0.0.1])
        by ppma03dal.us.ibm.com (8.16.0.42/8.16.0.42) with SMTP id
 09QFIHoR023423;
        Mon, 26 Oct 2020 15:36:09 GMT
Received: from b01cxnp22034.gho.pok.ibm.com (b01cxnp22034.gho.pok.ibm.com
 [9.57.198.24])
        by ppma03dal.us.ibm.com with ESMTP id 34cbw8vtan-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Mon, 26 Oct 2020 15:36:09 +0000
Received: from b01ledav004.gho.pok.ibm.com (b01ledav004.gho.pok.ibm.com
 [9.57.199.109])
        by b01cxnp22034.gho.pok.ibm.com (8.14.9/8.14.9/NCO v10.0) with ESMTP
 id 09QFYr2G20447508
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Mon, 26 Oct 2020 15:34:54 GMT
Received: from b01ledav004.gho.pok.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id D802F112065;
        Mon, 26 Oct 2020 15:34:53 +0000 (GMT)
Received: from b01ledav004.gho.pok.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id D1A45112062;
        Mon, 26 Oct 2020 15:34:49 +0000 (GMT)
Received: from oc4221205838.ibm.com (unknown [9.163.49.29])
        by b01ledav004.gho.pok.ibm.com (Postfix) with ESMTP;
        Mon, 26 Oct 2020 15:34:49 +0000 (GMT)
From: Matthew Rosato <mjrosato@linux.ibm.com>
To: cohuck@redhat.com, thuth@redhat.com
Cc: pmorel@linux.ibm.com, schnelle@linux.ibm.com, rth@twiddle.net,
        david@redhat.com, pasic@linux.ibm.com, borntraeger@de.ibm.com,
        mst@redhat.com, pbonzini@redhat.com, alex.williamson@redhat.com,
        philmd@redhat.com, qemu-s390x@nongnu.org, qemu-devel@nongnu.org,
        kvm@vger.kernel.org
Subject: [PATCH 01/13] update-linux-headers: Add vfio_zdev.h
Date: Mon, 26 Oct 2020 11:34:29 -0400
Message-Id: <1603726481-31824-2-git-send-email-mjrosato@linux.ibm.com>
X-Mailer: git-send-email 1.8.3.1
In-Reply-To: <1603726481-31824-1-git-send-email-mjrosato@linux.ibm.com>
References: <1603726481-31824-1-git-send-email-mjrosato@linux.ibm.com>
X-TM-AS-GCONF: 00
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.235,18.0.737
 definitions=2020-10-26_08:2020-10-26,2020-10-26 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 suspectscore=0 phishscore=0
 priorityscore=1501 lowpriorityscore=0 bulkscore=0 adultscore=0
 impostorscore=0 mlxlogscore=999 mlxscore=0 spamscore=0 clxscore=1015
 malwarescore=0 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.12.0-2009150000 definitions=main-2010260107
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

vfio_zdev.h is used by s390x zPCI support to pass device-specific
CLP information between host and userspace.

Signed-off-by: Matthew Rosato <mjrosato@linux.ibm.com>
Acked-by: Cornelia Huck <cohuck@redhat.com>
---
 scripts/update-linux-headers.sh | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
#### [PATCH v2 1/1] KVM: arm64: Correctly handle the mmio faulting
##### From: Santosh Shukla <sashukla@nvidia.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Santosh Shukla <sashukla@nvidia.com>
X-Patchwork-Id: 11856897
Return-Path: <SRS0=RIF0=EB=vger.kernel.org=kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-12.9 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_PATCH,MAILING_LIST_MULTI,SIGNED_OFF_BY,SPF_HELO_NONE,SPF_PASS,
	URIBL_BLOCKED,USER_AGENT_GIT autolearn=unavailable autolearn_force=no
	version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 6E4D6C4363A
	for <kvm@archiver.kernel.org>; Mon, 26 Oct 2020 11:25:28 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 259CA2465A
	for <kvm@archiver.kernel.org>; Mon, 26 Oct 2020 11:25:28 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=nvidia.com header.i=@nvidia.com
 header.b="XHOm2+pI"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1773768AbgJZLZY (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Mon, 26 Oct 2020 07:25:24 -0400
Received: from hqnvemgate24.nvidia.com ([216.228.121.143]:19654 "EHLO
        hqnvemgate24.nvidia.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1773761AbgJZLZY (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 26 Oct 2020 07:25:24 -0400
Received: from hqmail.nvidia.com (Not Verified[216.228.121.13]) by
 hqnvemgate24.nvidia.com (using TLS: TLSv1.2, AES256-SHA)
        id <B5f96b22a0001>; Mon, 26 Oct 2020 04:25:30 -0700
Received: from HQMAIL107.nvidia.com (172.20.187.13) by HQMAIL101.nvidia.com
 (172.20.187.10) with Microsoft SMTP Server (TLS) id 15.0.1473.3; Mon, 26 Oct
 2020 11:25:19 +0000
Received: from santosh-System-Product-Name.nvidia.com (172.20.13.39) by
 mail.nvidia.com (172.20.187.13) with Microsoft SMTP Server (TLS) id
 15.0.1473.3 via Frontend Transport; Mon, 26 Oct 2020 11:25:15 +0000
From: Santosh Shukla <sashukla@nvidia.com>
To: <maz@kernel.org>, <kvm@vger.kernel.org>,
        <kvmarm@lists.cs.columbia.edu>, <linux-kernel@vger.kernel.org>
CC: <james.morse@arm.com>, <julien.thierry.kdev@gmail.com>,
        <suzuki.poulose@arm.com>, <will@kernel.org>,
        <linux-arm-kernel@lists.infradead.org>, <cjia@nvidia.com>,
        <kwankhede@nvidia.com>, <mcrossley@nvidia.com>,
        Santosh Shukla <sashukla@nvidia.com>
Subject: [PATCH v2 1/1] KVM: arm64: Correctly handle the mmio faulting
Date: Mon, 26 Oct 2020 16:54:07 +0530
Message-ID: <1603711447-11998-2-git-send-email-sashukla@nvidia.com>
X-Mailer: git-send-email 2.7.4
In-Reply-To: <1603711447-11998-1-git-send-email-sashukla@nvidia.com>
References: <1603711447-11998-1-git-send-email-sashukla@nvidia.com>
X-NVConfidentiality: public
MIME-Version: 1.0
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=nvidia.com; s=n1;
        t=1603711530; bh=yL8eU53Ye6VwNxBHiLcoNd9MJdU5fRUmThif3Tv1W5E=;
        h=From:To:CC:Subject:Date:Message-ID:X-Mailer:In-Reply-To:
         References:X-NVConfidentiality:MIME-Version:Content-Type;
        b=XHOm2+pIlpG4E5U3euIlDKC7pqJpjQrTdWZNwMuV5fK+D1fWDqg43ADwB1Xu2LbtP
         PcSt2zKuF67PMIt8PVUe4QY9jz3IYwOK5R9XN6PhKvscGRc7gZQ6HV1uC8cL4mPw2e
         aNGvp8U0Rf1SZtD/z4U0yyCgu5t+LPHp3tTMpGow64ZDGzDaKeW/d1r2iFvV24yyix
         R4xkNTgwHRaebjq57PGGqXjk+dH6XGfqgDwvUS6N+btaS4brB8qtNnqEb9c3vwS9Kg
         hQh1BPVujC4zSGWjH88B/aN9riXCJRJC2T6wD+KgCWgepHGZq2YgJ+op77gQmWCuEh
         6X2VPFK4B7yJA==
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

The proposition is to set force_pte=true if kvm_is_device_pfn is true.

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
Linux-5.10-rc1 tip: 3650b228

Fixes: 6d674e28 ("KVM: arm/arm64: Properly handle faulting of device mappings")
Suggested-by: Marc Zyngier <maz@kernel.org>
Signed-off-by: Santosh Shukla <sashukla@nvidia.com>
Reviewed-by: Gavin Shan <gshan@redhat.com>
---
v2:
- Per Marc's suggestion - setting force_pte=true.
- Rebased and tested for 5.10-rc1 commit: 3650b228

v1: https://lkml.org/lkml/2020/10/21/460

arch/arm64/kvm/mmu.c | 1 +
 1 file changed, 1 insertion(+)

```
#### [PATCH v3 1/2] KVM: SVM: Track asid from vcpu_svm
##### From: Cathy Avery <cavery@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Cathy Avery <cavery@redhat.com>
X-Patchwork-Id: 11857961
Return-Path: <SRS0=RIF0=EB=vger.kernel.org=kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-9.9 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_PATCH,MAILING_LIST_MULTI,SIGNED_OFF_BY,SPF_HELO_NONE,SPF_PASS
	autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 75DC4C4363A
	for <kvm@archiver.kernel.org>; Mon, 26 Oct 2020 17:42:36 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 248BB20747
	for <kvm@archiver.kernel.org>; Mon, 26 Oct 2020 17:42:36 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="Zoi+rLHF"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1788160AbgJZRmf (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Mon, 26 Oct 2020 13:42:35 -0400
Received: from us-smtp-delivery-124.mimecast.com ([63.128.21.124]:53562 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1788134AbgJZRma (ORCPT
        <rfc822;kvm@vger.kernel.org>); Mon, 26 Oct 2020 13:42:30 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1603734149;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding:
         in-reply-to:in-reply-to:references:references;
        bh=GRAf8EjuLOHrdC1dVgSQl9YALtlT6bu//tBLi7Rkrj8=;
        b=Zoi+rLHFeIYM33jEjOubmwyIosdFUaTKOZe7P8N0SstMz1q6zT3cNf5CjUn46eXt+hBn0E
        P7tiRu856XOJRJkZ8taOrlrP+rH6WcCqAFrnC8Kgr68X5lDm9mf2NhkMxuiM/d/PmdFT54
        TKF8euSuDpTiQipPa8dEL7hZC4Ki/1U=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-470-r_sdJvPXP9G8BP6hFMK2Cw-1; Mon, 26 Oct 2020 13:42:25 -0400
X-MC-Unique: r_sdJvPXP9G8BP6hFMK2Cw-1
Received: from smtp.corp.redhat.com (int-mx05.intmail.prod.int.phx2.redhat.com
 [10.5.11.15])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 48928803637;
        Mon, 26 Oct 2020 17:42:24 +0000 (UTC)
Received: from virtlab710.virt.lab.eng.bos.redhat.com
 (virtlab710.virt.lab.eng.bos.redhat.com [10.19.152.252])
        by smtp.corp.redhat.com (Postfix) with ESMTP id A221E62A0B;
        Mon, 26 Oct 2020 17:42:23 +0000 (UTC)
From: Cathy Avery <cavery@redhat.com>
To: linux-kernel@vger.kernel.org, kvm@vger.kernel.org,
        pbonzini@redhat.com
Cc: vkuznets@redhat.com, wei.huang2@amd.com, mlevitsk@redhat.com,
        sean.j.christopherson@intel.com
Subject: [PATCH v3 1/2] KVM: SVM: Track asid from vcpu_svm
Date: Mon, 26 Oct 2020 13:42:21 -0400
Message-Id: <20201026174222.21811-2-cavery@redhat.com>
In-Reply-To: <20201026174222.21811-1-cavery@redhat.com>
References: <20201026174222.21811-1-cavery@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.15
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Track asid from svm->asid to allow for vmcb assignment
without regard to which level guest is running.

Suggested-by: Paolo Bonzini <pbonzini@redhat.com>
Signed-off-by: Cathy Avery <cavery@redhat.com>
---
 arch/x86/kvm/svm/svm.c | 16 ++++++++++++++--
 arch/x86/kvm/svm/svm.h |  2 ++
 2 files changed, 16 insertions(+), 2 deletions(-)

```
#### [PATCH v4 1/2] KVM: x86: hyper-v: allow KVM_GET_SUPPORTED_HV_CPUID as a system ioctl
##### From: Vitaly Kuznetsov <vkuznets@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Vitaly Kuznetsov <vkuznets@redhat.com>
X-Patchwork-Id: 11857783
Return-Path: <SRS0=RIF0=EB=vger.kernel.org=kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-9.9 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_PATCH,MAILING_LIST_MULTI,SIGNED_OFF_BY,SPF_HELO_NONE,SPF_PASS
	autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 67635C4363A
	for <kvm@archiver.kernel.org>; Mon, 26 Oct 2020 16:30:29 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id E5D8822284
	for <kvm@archiver.kernel.org>; Mon, 26 Oct 2020 16:30:28 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="OTxyosKf"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1785983AbgJZQa1 (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Mon, 26 Oct 2020 12:30:27 -0400
Received: from us-smtp-delivery-124.mimecast.com ([216.205.24.124]:41672 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1785967AbgJZQa0 (ORCPT
        <rfc822;kvm@vger.kernel.org>); Mon, 26 Oct 2020 12:30:26 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1603729824;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding:
         in-reply-to:in-reply-to:references:references;
        bh=YM3DGBatbMBsD5WFvyXJEWEdneXT/kk5d3A5T6bzj+U=;
        b=OTxyosKfpsO4t+o4a+K9Wb9xDvXERdWF7QdWVbOw/CPSQG0AqQgOx+SCmWBGBuM7RDCuep
        q9w+akwDdx/ck4FqYVC3zdLnRm9H7sd4c3I5mMC2XrsjhhlduAqMTDlh+3S2EvYipf+LfO
        fSelbJHJ1TVHnfkHf6PPduW4msi99HI=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-265-Uwa4WyhQPRymCddIAclYIg-1; Mon, 26 Oct 2020 12:30:20 -0400
X-MC-Unique: Uwa4WyhQPRymCddIAclYIg-1
Received: from smtp.corp.redhat.com (int-mx01.intmail.prod.int.phx2.redhat.com
 [10.5.11.11])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 024911018F79;
        Mon, 26 Oct 2020 16:30:19 +0000 (UTC)
Received: from vitty.brq.redhat.com (unknown [10.40.195.8])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 193AA5B4AC;
        Mon, 26 Oct 2020 16:30:16 +0000 (UTC)
From: Vitaly Kuznetsov <vkuznets@redhat.com>
To: kvm@vger.kernel.org, Paolo Bonzini <pbonzini@redhat.com>
Cc: Sean Christopherson <sean.j.christopherson@intel.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Eduardo Habkost <ehabkost@redhat.com>,
        Jon Doron <arilou@gmail.com>, linux-kernel@vger.kernel.org
Subject: [PATCH v4 1/2] KVM: x86: hyper-v: allow KVM_GET_SUPPORTED_HV_CPUID as
 a system ioctl
Date: Mon, 26 Oct 2020 17:30:12 +0100
Message-Id: <20201026163013.3164236-2-vkuznets@redhat.com>
In-Reply-To: <20201026163013.3164236-1-vkuznets@redhat.com>
References: <20201026163013.3164236-1-vkuznets@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.11
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

KVM_GET_SUPPORTED_HV_CPUID is a vCPU ioctl but its output is now
independent from vCPU and in some cases VMMs may want to use it as a system
ioctl instead. In particular, QEMU doesn CPU feature expansion before any
vCPU gets created so KVM_GET_SUPPORTED_HV_CPUID can't be used.

Convert KVM_GET_SUPPORTED_HV_CPUID to 'dual' system/vCPU ioctl with the
same meaning.

Signed-off-by: Vitaly Kuznetsov <vkuznets@redhat.com>
---
 Documentation/virt/kvm/api.rst | 16 ++++++++----
 arch/x86/kvm/hyperv.c          |  6 ++---
 arch/x86/kvm/hyperv.h          |  4 +--
 arch/x86/kvm/vmx/evmcs.c       |  3 +--
 arch/x86/kvm/x86.c             | 45 ++++++++++++++++++++--------------
 include/uapi/linux/kvm.h       |  3 ++-
 6 files changed, 46 insertions(+), 31 deletions(-)

```
#### [PATCH] vfio/fsl-mc: Make vfio_fsl_mc_irqs_allocate static
##### From: Diana Craciun <diana.craciun@oss.nxp.com>

```c
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Fixed compiler warning:
drivers/vfio/fsl-mc/vfio_fsl_mc_intr.c:16:5: warning: no previous
prototype for function 'vfio_fsl_mc_irqs_allocate' [-Wmissing-prototypes]
       ^
drivers/vfio/fsl-mc/vfio_fsl_mc_intr.c:16:1: note: declare 'static'
if the function is not intended to be used outside of this translation unit
int vfio_fsl_mc_irqs_allocate(struct vfio_fsl_mc_device *vdev)

Reported-by: kernel test robot <lkp@intel.com>
Signed-off-by: Diana Craciun <diana.craciun@oss.nxp.com>
---
 drivers/vfio/fsl-mc/vfio_fsl_mc_intr.c | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
#### [PATCH] x86: kvm: avoid -Wshadow warning in header
##### From: Arnd Bergmann <arnd@kernel.org>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Arnd Bergmann <arnd@kernel.org>
X-Patchwork-Id: 11857725
Return-Path: <SRS0=RIF0=EB=vger.kernel.org=kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-13.1 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,INCLUDES_PATCH,MAILING_LIST_MULTI,
	SIGNED_OFF_BY,SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED,USER_AGENT_GIT
	autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 11908C2D0A3
	for <kvm@archiver.kernel.org>; Mon, 26 Oct 2020 16:15:27 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id CE9DE24650
	for <kvm@archiver.kernel.org>; Mon, 26 Oct 2020 16:15:26 +0000 (UTC)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple; d=kernel.org;
	s=default; t=1603728926;
	bh=nbBpHbfA4qH/qtIRd76VIwnFW4gaPJYu7Nh39c3s29s=;
	h=From:To:Cc:Subject:Date:List-ID:From;
	b=mOLbMG2hCXXWwSPrGNeEzOndpDIloRr+ElLX0uwuu2/pSbC23axIsh0US3xXm9g0d
	 hHIELGba+rjX8/4Y2Wbsn0DxZDo9YLTlbKVDC8PFgm1TQqRAKQn9gw8h0ZKygq5sNk
	 BT+JcjGjYI5BWQd0VWwZGAnyncf/Si2zZGws3Q+s=
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1775147AbgJZQPX (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Mon, 26 Oct 2020 12:15:23 -0400
Received: from mail.kernel.org ([198.145.29.99]:59610 "EHLO mail.kernel.org"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1774780AbgJZQPX (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 26 Oct 2020 12:15:23 -0400
Received: from localhost.localdomain (unknown [192.30.34.233])
        (using TLSv1.2 with cipher ECDHE-RSA-AES128-GCM-SHA256 (128/128 bits))
        (No client certificate requested)
        by mail.kernel.org (Postfix) with ESMTPSA id 6F7CD22284;
        Mon, 26 Oct 2020 16:15:18 +0000 (UTC)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple; d=kernel.org;
        s=default; t=1603728922;
        bh=nbBpHbfA4qH/qtIRd76VIwnFW4gaPJYu7Nh39c3s29s=;
        h=From:To:Cc:Subject:Date:From;
        b=epxjmRJIXYZ5egvmm5CwGR1oa9AubDEWpLXol6zfnu8pAQolFoer1vyTqvCNbczE2
         iB9/4vORMo0jDTHM58OyIty1eQ59sQSo2kZdysLRXSzFbYtMK3IHCZKP1iTyWTXleb
         hoegApx41bOmszF9bd5CIuI0Ru+xqOJr4iS5wHKg=
From: Arnd Bergmann <arnd@kernel.org>
To: Paolo Bonzini <pbonzini@redhat.com>,
        Thomas Gleixner <tglx@linutronix.de>,
        Ingo Molnar <mingo@redhat.com>, Borislav Petkov <bp@alien8.de>,
        x86@kernel.org
Cc: Arnd Bergmann <arnd@arndb.de>, Gleb Natapov <gleb@redhat.com>,
        Avi Kivity <avi@redhat.com>, Ingo Molnar <mingo@elte.hu>,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>,
        "H. Peter Anvin" <hpa@zytor.com>, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org
Subject: [PATCH] x86: kvm: avoid -Wshadow warning in header
Date: Mon, 26 Oct 2020 17:14:39 +0100
Message-Id: <20201026161512.3708919-1-arnd@kernel.org>
X-Mailer: git-send-email 2.27.0
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Arnd Bergmann <arnd@arndb.de>

There are hundreds of warnings in a W=2 build about a local
variable shadowing the global 'apic' definition:

arch/x86/kvm/lapic.h:149:65: warning: declaration of 'apic' shadows a global declaration [-Wshadow]

Avoid this by renaming the local in the kvm/lapic.h header

Fixes: c48f14966cc4 ("KVM: inline kvm_apic_present() and kvm_lapic_enabled()")
Fixes: c8d46cf06dc2 ("x86: rename 'genapic' to 'apic'")
Signed-off-by: Arnd Bergmann <arnd@arndb.de>
---
 arch/x86/kvm/lapic.h | 38 +++++++++++++++++++-------------------
 1 file changed, 19 insertions(+), 19 deletions(-)

```
