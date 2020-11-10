

#### [PATCH 0/8] slab: provide and use krealloc_array()
##### From: Bartosz Golaszewski <brgl@bgdev.pl>
From: Bartosz Golaszewski <bgolaszewski@baylibre.com>

```c
From patchwork Tue Oct 27 12:17:17 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Bartosz Golaszewski <brgl@bgdev.pl>
X-Patchwork-Id: 11860225
Return-Path: <SRS0=+pC+=EC=vger.kernel.org=kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-6.8 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,HEADER_FROM_DIFFERENT_DOMAINS,MAILING_LIST_MULTI,SPF_HELO_NONE,
	SPF_PASS,URIBL_BLOCKED,USER_AGENT_GIT autolearn=no autolearn_force=no
	version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id CE33DC5DF9D
	for <kvm@archiver.kernel.org>; Tue, 27 Oct 2020 12:18:55 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 7641922264
	for <kvm@archiver.kernel.org>; Tue, 27 Oct 2020 12:18:55 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=bgdev-pl.20150623.gappssmtp.com
 header.i=@bgdev-pl.20150623.gappssmtp.com header.b="P+3tCIHO"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2899641AbgJ0MRk (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 27 Oct 2020 08:17:40 -0400
Received: from mail-wm1-f65.google.com ([209.85.128.65]:35596 "EHLO
        mail-wm1-f65.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S2408777AbgJ0MRi (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 27 Oct 2020 08:17:38 -0400
Received: by mail-wm1-f65.google.com with SMTP id h22so1204769wmb.0
        for <kvm@vger.kernel.org>; Tue, 27 Oct 2020 05:17:36 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=bgdev-pl.20150623.gappssmtp.com; s=20150623;
        h=from:to:cc:subject:date:message-id:mime-version
         :content-transfer-encoding;
        bh=LJP6zUa9eBmdV8bx1jdaWyKmaK9MsWkK16il5Qo0OrM=;
        b=P+3tCIHOjCZAx0wmilW2GDFvIGyFUKkJ6kMCnuzTaqTK/WVy0FTiGFvqMSEeEaTSDi
         lidtNcACGQa4FsZTJSv/WM+PJAWcMBZ84eqrsFS5cBt5SmJFi36Zt8P8jQqLDmjkvqeW
         khRH3E+peGeaQTCIY3Vt2p8gYCX0QOu5toB/kJmHKtw/28SJ6BKumTSSq2MJytdIAdgp
         oJxR5uAJUIN5EhwIO49GT3ZmC5B5ob3NU85YWSk0gy8yt2me9ot389ODzNeNzE1g7isf
         BjKSBXgUK2OMn2MduiDvTrDfwsn8XX/eMtY9lahl6HLlIYN8j7wdAJNYVoPtfuaoSs+h
         PRUQ==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:mime-version
         :content-transfer-encoding;
        bh=LJP6zUa9eBmdV8bx1jdaWyKmaK9MsWkK16il5Qo0OrM=;
        b=C1fSO2uCPiqLXXSjjqryCasF1TZPbJhAXJmKgNIrMTpN5q7zx/rQXUkI317ocOrB6O
         4LFbe4AFx5aTnsL7zfFi/G60ydfZJdFJITiOeNgLPKyZR7DZF+Y3HnDW6NaDfSDp32o7
         Gibiv8syo3visN5X3gcwusgvPUKaqm/lVZ0HSFylW1QWXuoRv0g1MCyTq73fy2jzfU2a
         SehsxXO6kviKtnba2ac7D0cc9OhJ68hHrYO++MJjETvLZrUW69BdTf4BavywShArnUOo
         0iJ+ehLxFE2adyQlBYPOYjhov58OFjaxnnkGhKhzUUhxWQG4HcwuNfJC5FEaByF8Wayd
         fc8A==
X-Gm-Message-State: AOAM530tuLyssAN/cTKAzUoCE8JphujD2ZjdM9PL/NslUO7aZM3vGEa0
        ozsugGGKNqCyYt7phitMLsZwYg==
X-Google-Smtp-Source: 
 ABdhPJxUDPfM7/G4w39/lM3kfVBbiG37Et7vUzW73qIzYGjUaK5vAjNfvCioGZotPrXrgX+P7fvBjA==
X-Received: by 2002:a1c:8087:: with SMTP id b129mr2477389wmd.10.1603801056147;
        Tue, 27 Oct 2020 05:17:36 -0700 (PDT)
Received: from debian-brgl.home (amarseille-656-1-4-167.w90-8.abo.wanadoo.fr.
 [90.8.158.167])
        by smtp.gmail.com with ESMTPSA id
 a2sm1731908wrs.55.2020.10.27.05.17.34
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Tue, 27 Oct 2020 05:17:35 -0700 (PDT)
From: Bartosz Golaszewski <brgl@bgdev.pl>
To: Andy Shevchenko <andriy.shevchenko@linux.intel.com>,
 Sumit Semwal <sumit.semwal@linaro.org>,
 Gustavo Padovan <gustavo@padovan.org>,
 =?utf-8?q?Christian_K=C3=B6nig?= <christian.koenig@amd.com>,
 Mauro Carvalho Chehab <mchehab@kernel.org>, Borislav Petkov <bp@alien8.de>,
 Tony Luck <tony.luck@intel.com>, James Morse <james.morse@arm.com>,
 Robert Richter <rric@kernel.org>,
 Maarten Lankhorst <maarten.lankhorst@linux.intel.com>,
 Maxime Ripard <mripard@kernel.org>, Thomas Zimmermann <tzimmermann@suse.de>,
 David Airlie <airlied@linux.ie>, Daniel Vetter <daniel@ffwll.ch>,
 Alexander Shishkin <alexander.shishkin@linux.intel.com>,
 Linus Walleij <linus.walleij@linaro.org>,
 "Michael S . Tsirkin" <mst@redhat.com>, Jason Wang <jasowang@redhat.com>,
 Christoph Lameter <cl@linux.com>, Pekka Enberg <penberg@kernel.org>,
 David Rientjes <rientjes@google.com>, Joonsoo Kim <iamjoonsoo.kim@lge.com>,
 Andrew Morton <akpm@linux-foundation.org>, Jaroslav Kysela <perex@perex.cz>,
 Takashi Iwai <tiwai@suse.com>
Cc: linux-media@vger.kernel.org, dri-devel@lists.freedesktop.org,
        linaro-mm-sig@lists.linaro.org, linux-kernel@vger.kernel.org,
        linux-edac@vger.kernel.org, linux-gpio@vger.kernel.org,
        kvm@vger.kernel.org, virtualization@lists.linux-foundation.org,
        netdev@vger.kernel.org, linux-mm@kvack.org,
        alsa-devel@alsa-project.org,
        Bartosz Golaszewski <bgolaszewski@baylibre.com>
Subject: [PATCH 0/8] slab: provide and use krealloc_array()
Date: Tue, 27 Oct 2020 13:17:17 +0100
Message-Id: <20201027121725.24660-1-brgl@bgdev.pl>
X-Mailer: git-send-email 2.29.1
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Bartosz Golaszewski <bgolaszewski@baylibre.com>

Andy brought to my attention the fact that users allocating an array of
equally sized elements should check if the size multiplication doesn't
overflow. This is why we have helpers like kmalloc_array().

However we don't have krealloc_array() equivalent and there are many
users who do their own multiplication when calling krealloc() for arrays.

This series provides krealloc_array() and uses it in a couple places.

A separate series will follow adding devm_krealloc_array() which is
needed in the xilinx adc driver.

Bartosz Golaszewski (8):
  mm: slab: provide krealloc_array()
  ALSA: pcm: use krealloc_array()
  vhost: vringh: use krealloc_array()
  pinctrl: use krealloc_array()
  edac: ghes: use krealloc_array()
  drm: atomic: use krealloc_array()
  hwtracing: intel: use krealloc_array()
  dma-buf: use krealloc_array()

 drivers/dma-buf/sync_file.c      |  4 ++--
 drivers/edac/ghes_edac.c         |  4 ++--
 drivers/gpu/drm/drm_atomic.c     |  3 ++-
 drivers/hwtracing/intel_th/msu.c |  2 +-
 drivers/pinctrl/pinctrl-utils.c  |  2 +-
 drivers/vhost/vringh.c           |  3 ++-
 include/linux/slab.h             | 11 +++++++++++
 sound/core/pcm_lib.c             |  4 ++--
 8 files changed, 23 insertions(+), 10 deletions(-)
Acked-by: Linus Walleij <linus.walleij@linaro.org>
```
#### [PATCH 0/3] Allow in-kernel consumers to drain events from eventfd
##### From: David Woodhouse <dwmw2@infradead.org>

```c
From patchwork Tue Oct 27 13:55:20 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: David Woodhouse <dwmw2@infradead.org>
X-Patchwork-Id: 11860507
Return-Path: <SRS0=+pC+=EC=vger.kernel.org=kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-6.9 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,MAILING_LIST_MULTI,
	SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT autolearn=no autolearn_force=no
	version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 26841C388F9
	for <kvm@archiver.kernel.org>; Tue, 27 Oct 2020 13:55:38 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id B390A218AC
	for <kvm@archiver.kernel.org>; Tue, 27 Oct 2020 13:55:37 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=infradead.org header.i=@infradead.org
 header.b="2KemxEIJ"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S367997AbgJ0Nze (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 27 Oct 2020 09:55:34 -0400
Received: from merlin.infradead.org ([205.233.59.134]:39130 "EHLO
        merlin.infradead.org" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S2438386AbgJ0Nzd (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 27 Oct 2020 09:55:33 -0400
DKIM-Signature: v=1; a=rsa-sha256; q=dns/txt; c=relaxed/relaxed;
        d=infradead.org; s=merlin.20170209;
 h=Sender:Content-Transfer-Encoding:
        MIME-Version:References:In-Reply-To:Message-Id:Date:Subject:Cc:To:From:
        Reply-To:Content-Type:Content-ID:Content-Description;
        bh=zDE5jb9uxhVI9C4jlM6oDJI3APbjGF+q9+SWA/XVKeI=;
 b=2KemxEIJQODswF6tNzklkYfkjJ
        QQsUcrSXbVfL0tK+ihfcobzBVTVFg606C1qriUbY54A5Q5dcls5dJITJEyA944Ri74Bpwe4vdnFnH
        uImLAucbMEk9s5iV3n0WWOYFGZGDdevASSJOT7J+a70EK1RrlNjFfRLHwPfdRCvFwV6PCymq1cYze
        nCLYaH3laExlXMK7uO/adSWD8Zc9hJz6LKkSn545yYoGZR9hTCzzlM+3w7pULZs6/4Bu0GwggmBE+
        eVY2cqNAukipGfhJl04U/JvR2waVkO5t1pGdhVEOnCTywhcT8GLQf3xVnbbsyE4EAfLD+/LDv41ul
        rD4wBrgQ==;
Received: from i7.infradead.org ([2001:8b0:10b:1:21e:67ff:fecb:7a92])
        by merlin.infradead.org with esmtpsa (Exim 4.92.3 #3 (Red Hat Linux))
        id 1kXPRe-00005c-KS; Tue, 27 Oct 2020 13:55:26 +0000
Received: from dwoodhou by i7.infradead.org with local (Exim 4.93 #3 (Red Hat
 Linux))
        id 1kXPRd-002iLY-JP; Tue, 27 Oct 2020 13:55:25 +0000
From: David Woodhouse <dwmw2@infradead.org>
To: bonzini@redhat.com
Cc: Alex Williamson <alex.williamson@redhat.com>,
        Cornelia Huck <cohuck@redhat.com>,
        Alexander Viro <viro@zeniv.linux.org.uk>,
        Jens Axboe <axboe@kernel.dk>, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org, linux-fsdevel@vger.kernel.org
Subject: [PATCH 0/3] Allow in-kernel consumers to drain events from eventfd
Date: Tue, 27 Oct 2020 13:55:20 +0000
Message-Id: <20201027135523.646811-1-dwmw2@infradead.org>
X-Mailer: git-send-email 2.26.2
In-Reply-To: <1faa5405-3640-f4ad-5cd9-89a9e5e834e9@redhat.com>
References: <1faa5405-3640-f4ad-5cd9-89a9e5e834e9@redhat.com>
MIME-Version: 1.0
Sender: David Woodhouse <dwmw2@infradead.org>
X-SRS-Rewrite: SMTP reverse-path rewritten from <dwmw2@infradead.org> by
 merlin.infradead.org. See http://www.infradead.org/rpr.html
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Paolo pointed out that the KVM eventfd doesn't drain the events from the
irqfd as it handles them, and just lets them accumulate. This is also
true for the VFIO virqfd used for handling acks for level-triggered IRQs.

Export eventfd_ctx_do_read() and make the wakeup functions call it as they
handle their respective events.

David Woodhouse (3):
      eventfd: Export eventfd_ctx_do_read()
      vfio/virqfd: Drain events from eventfd in virqfd_wakeup()
      kvm/eventfd: Drain events from eventfd in irqfd_wakeup()

 drivers/vfio/virqfd.c   | 3 +++
 fs/eventfd.c            | 5 ++++-
 include/linux/eventfd.h | 6 ++++++
 virt/kvm/eventfd.c      | 3 +++
 4 files changed, 16 insertions(+), 1 deletion(-)
```
#### [PATCH v2 0/2] Allow KVM IRQFD to consistently intercept events
##### From: David Woodhouse <dwmw2@infradead.org>

```c
From patchwork Tue Oct 27 14:39:42 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 8bit
X-Patchwork-Submitter: David Woodhouse <dwmw2@infradead.org>
X-Patchwork-Id: 11860643
Return-Path: <SRS0=+pC+=EC=vger.kernel.org=kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-6.9 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,MAILING_LIST_MULTI,
	SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT autolearn=no autolearn_force=no
	version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 6B9D5C64E90
	for <kvm@archiver.kernel.org>; Tue, 27 Oct 2020 14:40:49 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 0FC112225E
	for <kvm@archiver.kernel.org>; Tue, 27 Oct 2020 14:40:49 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=infradead.org header.i=@infradead.org
 header.b="u19M+t1b"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2899168AbgJ0Oko (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 27 Oct 2020 10:40:44 -0400
Received: from merlin.infradead.org ([205.233.59.134]:52100 "EHLO
        merlin.infradead.org" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S368410AbgJ0Ojs (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 27 Oct 2020 10:39:48 -0400
DKIM-Signature: v=1; a=rsa-sha256; q=dns/txt; c=relaxed/relaxed;
        d=infradead.org; s=merlin.20170209;
 h=Sender:Content-Transfer-Encoding:
        Content-Type:MIME-Version:References:In-Reply-To:Message-Id:Date:Subject:Cc:
        To:From:Reply-To:Content-ID:Content-Description;
        bh=riMlzuoiOwtXb9I5iFqaHvZGEHPZQcMx6cCtaeKRBNE=;
 b=u19M+t1bEapEPy3W0cEebkIA2d
        kaHsPHlZs82IGon33mgFlwwE1ezk+LhT8ZdnHS3N6MsQZVCJl0rSpGPNnjIREn3KqUGCiptVubZxF
        lR5It3MxUkUyFqKhccGg6MSfwrbI0zoi0msSVkQyP1gfeboYOvC2/IbEcO1H068s5ufXIngVkkT0p
        07MnqTR5pDT5qG6shE0eTkT1KB26GVonAYPf8+bYVqb/qsoYvixM+ztl+g9w2r0ver1alwK8yfxOE
        oQhHqZ83FaWRUSuyYVcKoGo/eegaGlwz0cRKhiszMiz3osAQqYfYQ235uSacZPkE4OEu/nsomfeNv
        EyTYWGzw==;
Received: from i7.infradead.org ([2001:8b0:10b:1:21e:67ff:fecb:7a92])
        by merlin.infradead.org with esmtpsa (Exim 4.92.3 #3 (Red Hat Linux))
        id 1kXQ8Z-0000bX-Fy; Tue, 27 Oct 2020 14:39:47 +0000
Received: from dwoodhou by i7.infradead.org with local (Exim 4.93 #3 (Red Hat
 Linux))
        id 1kXQ8Y-002iqc-Dq; Tue, 27 Oct 2020 14:39:46 +0000
From: David Woodhouse <dwmw2@infradead.org>
To: linux-kernel@vger.kernel.org
Cc: Ingo Molnar <mingo@redhat.com>,
        Peter Zijlstra <peterz@infradead.org>,
        Juri Lelli <juri.lelli@redhat.com>,
        Vincent Guittot <vincent.guittot@linaro.org>,
        Dietmar Eggemann <dietmar.eggemann@arm.com>,
        Steven Rostedt <rostedt@goodmis.org>,
        Ben Segall <bsegall@google.com>, Mel Gorman <mgorman@suse.de>,
        Daniel Bristot de Oliveira <bristot@redhat.com>,
        Paolo Bonzini <pbonzini@redhat.com>, kvm@vger.kernel.org
Subject: [PATCH v2 0/2] Allow KVM IRQFD to consistently intercept events
Date: Tue, 27 Oct 2020 14:39:42 +0000
Message-Id: <20201027143944.648769-1-dwmw2@infradead.org>
X-Mailer: git-send-email 2.26.2
In-Reply-To: <20201026175325.585623-1-dwmw2@infradead.org>
References: <20201026175325.585623-1-dwmw2@infradead.org>
MIME-Version: 1.0
Sender: David Woodhouse <dwmw2@infradead.org>
X-SRS-Rewrite: SMTP reverse-path rewritten from <dwmw2@infradead.org> by
 merlin.infradead.org. See http://www.infradead.org/rpr.html
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

When posted interrupts are in use, KVM fully bypasses the eventfd and
delivers events directly to the appropriate vCPU. Without posted
interrupts, it still uses the eventfd but it doesn't actually stop
userspace from receiving the events too. This leaves userspace having
to carefully avoid seeing the same events and injecting duplicate
interrupts to the guest.

Fix it by adding a 'priority' mode for exclusive waiters which puts them 
at the head of the list, where they can consume events before the 
non-exclusive waiters are woken.

v2: 
 • Drop [RFC]. This seems to be working nicely, and userspace is a lot
   cleaner without having to mess around with adding/removing the eventfd
   to its poll set. And nobody yelled at me. Yet.
 • Reword commit comments, update comment above __wake_up_common()
 • Rebase to be applied after the (only vaguely related) fix to make
   irqfd actually consume the eventfd counter too.

David Woodhouse (2):
      sched/wait: Add add_wait_queue_priority()
      kvm/eventfd: Use priority waitqueue to catch events before userspace

 include/linux/wait.h | 12 +++++++++++-
 kernel/sched/wait.c  | 17 ++++++++++++++++-
 virt/kvm/eventfd.c   |  6 ++++--
```
#### [kvm-unit-tests RFC PATCH v2 0/5] arm64: Statistical Profiling
##### From: Alexandru Elisei <alexandru.elisei@arm.com>

```c
From patchwork Tue Oct 27 17:19:39 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Alexandru Elisei <alexandru.elisei@arm.com>
X-Patchwork-Id: 11861123
Return-Path: <SRS0=+pC+=EC=vger.kernel.org=kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-6.8 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,
	URIBL_BLOCKED,USER_AGENT_GIT autolearn=no autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 9FAABC4363A
	for <kvm@archiver.kernel.org>; Tue, 27 Oct 2020 17:18:49 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 65B3420657
	for <kvm@archiver.kernel.org>; Tue, 27 Oct 2020 17:18:49 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1818283AbgJ0RSs (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 27 Oct 2020 13:18:48 -0400
Received: from foss.arm.com ([217.140.110.172]:47638 "EHLO foss.arm.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1818277AbgJ0RSr (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 27 Oct 2020 13:18:47 -0400
Received: from usa-sjc-imap-foss1.foss.arm.com (unknown [10.121.207.14])
        by usa-sjc-mx-foss1.foss.arm.com (Postfix) with ESMTP id 42D05139F;
        Tue, 27 Oct 2020 10:18:46 -0700 (PDT)
Received: from monolith.localdoman (unknown [172.31.20.19])
        by usa-sjc-imap-foss1.foss.arm.com (Postfix) with ESMTPSA id
 EEE5C3F719;
        Tue, 27 Oct 2020 10:18:43 -0700 (PDT)
From: Alexandru Elisei <alexandru.elisei@arm.com>
To: kvm@vger.kernel.org, kvmarm@lists.cs.columbia.edu
Cc: drjones@redhat.com, pbonzini@redhat.com
Subject: [kvm-unit-tests RFC PATCH v2 0/5] arm64: Statistical Profiling
 Extension Tests
Date: Tue, 27 Oct 2020 17:19:39 +0000
Message-Id: <20201027171944.13933-1-alexandru.elisei@arm.com>
X-Mailer: git-send-email 2.29.1
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This series implements two basic tests for KVM SPE: one that checks that
the reported features match what is specified in the architecture,
implemented in patch #3 ("arm64: spe: Add introspection test"), and another
test that checks that the buffer management interrupt is asserted
correctly, implemented in patch #5 ("am64: spe: Add buffer test"). The rest
of the patches are either preparatory patches, or a fix, in the case of
patch #2 ("lib/{bitops,alloc_page}.h: Add missing headers").

This series builds on Eric's initial version [1], to which I've added the
buffer tests that I used while developing SPE support for KVM.

KVM SPE support is current in RFC phase, hence why this series is also sent
as RFC. The KVM patches needed for the tests to work can be found at [2].
Userspace support is also necessary, which I've implemented for kvmtool;
this can be found at [3]. This series is also available in a repo [4] to make
testing easier.

[1] https://www.spinics.net/lists/kvm/msg223792.html
[2] https://gitlab.arm.com/linux-arm/linux-ae/-/tree/kvm-spe-v3
[3] https://gitlab.arm.com/linux-arm/kvmtool-ae/-/tree/kvm-spe-v3
[4] https://gitlab.arm.com/linux-arm/kvm-unit-tests-ae/-/tree/kvm-spe-v2

Alexandru Elisei (3):
  lib/{bitops,alloc_page}.h: Add missing headers
  lib: arm/arm64: Add function to unmap a page
  am64: spe: Add buffer test

Eric Auger (2):
  arm64: Move get_id_aa64dfr0() in processor.h
  arm64: spe: Add introspection test

 arm/Makefile.arm64        |   1 +
 lib/arm/asm/mmu-api.h     |   1 +
 lib/arm64/asm/processor.h |   5 +
 lib/alloc_page.h          |   2 +
 lib/bitops.h              |   2 +
 lib/libcflat.h            |   1 +
 lib/arm/mmu.c             |  32 +++
 arm/pmu.c                 |   1 -
 arm/spe.c                 | 506 ++++++++++++++++++++++++++++++++++++++
 arm/unittests.cfg         |  15 ++
 10 files changed, 565 insertions(+), 1 deletion(-)
 create mode 100644 arm/spe.c
```
#### [RFC PATCH kvmtool v3 0/3] SPE support
##### From: Alexandru Elisei <alexandru.elisei@arm.com>

```c
From patchwork Tue Oct 27 17:17:32 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Alexandru Elisei <alexandru.elisei@arm.com>
X-Patchwork-Id: 11861137
Return-Path: <SRS0=+pC+=EC=vger.kernel.org=kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-6.8 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,
	URIBL_BLOCKED,USER_AGENT_GIT autolearn=no autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id AF5A6C55179
	for <kvm@archiver.kernel.org>; Tue, 27 Oct 2020 17:21:44 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 71DF020809
	for <kvm@archiver.kernel.org>; Tue, 27 Oct 2020 17:21:44 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1817988AbgJ0RQp (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 27 Oct 2020 13:16:45 -0400
Received: from foss.arm.com ([217.140.110.172]:47464 "EHLO foss.arm.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1817973AbgJ0RQf (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 27 Oct 2020 13:16:35 -0400
Received: from usa-sjc-imap-foss1.foss.arm.com (unknown [10.121.207.14])
        by usa-sjc-mx-foss1.foss.arm.com (Postfix) with ESMTP id CC422139F;
        Tue, 27 Oct 2020 10:16:33 -0700 (PDT)
Received: from monolith.localdoman (unknown [172.31.20.19])
        by usa-sjc-imap-foss1.foss.arm.com (Postfix) with ESMTPSA id
 236773F719;
        Tue, 27 Oct 2020 10:16:30 -0700 (PDT)
From: Alexandru Elisei <alexandru.elisei@arm.com>
To: kvmarm@lists.cs.columbia.edu, kvm@vger.kernel.org
Cc: will@kernel.org, julien.thierry.kdev@gmail.com
Subject: [RFC PATCH kvmtool v3 0/3] SPE support
Date: Tue, 27 Oct 2020 17:17:32 +0000
Message-Id: <20201027171735.13638-1-alexandru.elisei@arm.com>
X-Mailer: git-send-email 2.29.1
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This series adds userspace support for creating a guest which can use SPE.
It requires KVM SPE support which is in the RFC phase, hence why this
series is also RFC. The kvmtool patches can also be found at [1], and the
KVM SPE patches can be found at [2].

To create a guest with SPE support the following steps must be executed:

1. Set the SPE virtual interrupt ID and then initialize the features on
every VCPU.

2. After the guest memory memslots have been created, kvmtool must mlock()
the VMAs backing the memslots.

3. After everything has been copied to the guest's memory, kvmtool must
execute the KVM_ARM_VM_SPE_CTRL(KVM_ARM_VM_SPE_FINALIZE) on the VM fd.

The first patch is a simple update to the Linux headers; the second patch
add a new init list that executes last which is necessary to make sure the
gest memory will not be touched after that; and the third patch contains
the actual SPE support.

[1] https://gitlab.arm.com/linux-arm/kvmtool-ae/-/tree/kvm-spe-v3
[2] https://gitlab.arm.com/linux-arm/linux-ae/-/tree/kvm-spe-v3

Alexandru Elisei (1):
  init: Add last_{init, exit} list macros

Sudeep Holla (2):
  update_headers: Sync kvm UAPI headers with linux 5.10-rc1
  arm64: Add SPE support

 Makefile                                  |   2 +-
 arm/aarch64/arm-cpu.c                     |   2 +
 arm/aarch64/include/asm/kvm.h             |  53 +++++++-
 arm/aarch64/include/kvm/kvm-config-arch.h |   2 +
 arm/aarch64/include/kvm/kvm-cpu-arch.h    |   3 +-
 arm/aarch64/kvm-cpu.c                     |   5 +
 arm/include/arm-common/kvm-config-arch.h  |   1 +
 arm/include/arm-common/spe.h              |   7 +
 arm/spe.c                                 | 154 ++++++++++++++++++++++
 include/kvm/util-init.h                   |   6 +-
 include/linux/kvm.h                       | 117 +++++++++++++++-
 powerpc/include/asm/kvm.h                 |   8 ++
 x86/include/asm/kvm.h                     |  42 +++++-
 13 files changed, 387 insertions(+), 15 deletions(-)
 create mode 100644 arm/include/arm-common/spe.h
 create mode 100644 arm/spe.c
```
#### [PATCH v3 00/11] KVM: VMX: Clean up Hyper-V PV TLB flush
##### From: Sean Christopherson <sean.j.christopherson@intel.com>

```c
From patchwork Tue Oct 27 21:23:35 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Sean Christopherson <sean.j.christopherson@intel.com>
X-Patchwork-Id: 11861911
Return-Path: <SRS0=+pC+=EC=vger.kernel.org=kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-6.8 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,
	USER_AGENT_GIT autolearn=no autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 4C9F8C4363A
	for <kvm@archiver.kernel.org>; Tue, 27 Oct 2020 21:25:17 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id ED2D722283
	for <kvm@archiver.kernel.org>; Tue, 27 Oct 2020 21:25:16 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S373775AbgJ0VXw (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 27 Oct 2020 17:23:52 -0400
Received: from mga02.intel.com ([134.134.136.20]:56181 "EHLO mga02.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S373764AbgJ0VXv (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 27 Oct 2020 17:23:51 -0400
IronPort-SDR: 
 mm42A7NBYWv2Xzhp4YMkm6L1GrrN+XED0/Q9qnxPDgGBpitaE3zVLjjxAwnSEo/fSn7hRcGuvt
 yPKBc+RsiFIA==
X-IronPort-AV: E=McAfee;i="6000,8403,9787"; a="155133697"
X-IronPort-AV: E=Sophos;i="5.77,424,1596524400";
   d="scan'208";a="155133697"
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from fmsmga006.fm.intel.com ([10.253.24.20])
  by orsmga101.jf.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 27 Oct 2020 14:23:50 -0700
IronPort-SDR: 
 wAVat0Mh0B7MCeJOzTOZ1b2tBkCUoIzYgffFSRKrmNkkPqBwRMplUWMpcW6Ax+thT4qbW2FPTC
 FQC6YwdZ96lQ==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.77,424,1596524400";
   d="scan'208";a="524886372"
Received: from sjchrist-coffee.jf.intel.com ([10.54.74.160])
  by fmsmga006.fm.intel.com with ESMTP; 27 Oct 2020 14:23:50 -0700
From: Sean Christopherson <sean.j.christopherson@intel.com>
To: Paolo Bonzini <pbonzini@redhat.com>
Cc: Sean Christopherson <sean.j.christopherson@intel.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org
Subject: [PATCH v3 00/11] KVM: VMX: Clean up Hyper-V PV TLB flush
Date: Tue, 27 Oct 2020 14:23:35 -0700
Message-Id: <20201027212346.23409-1-sean.j.christopherson@intel.com>
X-Mailer: git-send-email 2.28.0
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Clean up KVM's PV TLB flushing when running with EPT on Hyper-V, i.e. as
a nested VMM.  No real goal in mind other than the sole patch in v1, which
is a minor change to avoid a future mixup when TDX also wants to define
.remote_flush_tlb.  Everything else is opportunistic clean up.

Patch 1 legitimately tested on VMX (no SVM), everything else effectively
build tested only.

v3:
  - Add a patch to pass the root_hpa instead of pgd to vmx_load_mmu_pgd()
    and retrieve the active PCID only when necessary.  [Vitaly]
  - Selectively collects reviews (skipped a few due to changes). [Vitaly]
  - Explicitly invalidate hv_tlb_eptp instead of leaving it valid when
    the mismatch tracker "knows" it's invalid. [Vitaly]
  - Change the last patch to use "hv_root_ept" instead of "hv_tlb_pgd"
    to better reflect what is actually being tracked.

v2: Rewrite everything.
 
Sean Christopherson (11):
  KVM: x86: Get active PCID only when writing a CR3 value
  KVM: VMX: Track common EPTP for Hyper-V's paravirt TLB flush
  KVM: VMX: Stash kvm_vmx in a local variable for Hyper-V paravirt TLB
    flush
  KVM: VMX: Fold Hyper-V EPTP checking into it's only caller
  KVM: VMX: Do Hyper-V TLB flush iff vCPU's EPTP hasn't been flushed
  KVM: VMX: Invalidate hv_tlb_eptp to denote an EPTP mismatch
  KVM: VMX: Don't invalidate hv_tlb_eptp if the new EPTP matches
  KVM: VMX: Explicitly check for hv_remote_flush_tlb when loading pgd
  KVM: VMX: Define Hyper-V paravirt TLB flush fields iff Hyper-V is
    enabled
  KVM: VMX: Skip additional Hyper-V TLB EPTP flushes if one fails
  KVM: VMX: Track root HPA instead of EPTP for paravirt Hyper-V TLB
    flush

 arch/x86/include/asm/kvm_host.h |   4 +-
 arch/x86/kvm/mmu.h              |   2 +-
 arch/x86/kvm/svm/svm.c          |   4 +-
 arch/x86/kvm/vmx/vmx.c          | 134 ++++++++++++++++++--------------
 arch/x86/kvm/vmx/vmx.h          |  19 ++---
 5 files changed, 87 insertions(+), 76 deletions(-)
```
#### [PATCH 0/3] KVM: x86/mmu: Add macro for hugepage GFN mask
##### From: Sean Christopherson <sean.j.christopherson@intel.com>

```c
From patchwork Tue Oct 27 21:42:57 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Sean Christopherson <sean.j.christopherson@intel.com>
X-Patchwork-Id: 11861939
Return-Path: <SRS0=+pC+=EC=vger.kernel.org=kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-6.8 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,
	USER_AGENT_GIT autolearn=no autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 6CF7BC4363A
	for <kvm@archiver.kernel.org>; Tue, 27 Oct 2020 21:43:37 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 1B2972223C
	for <kvm@archiver.kernel.org>; Tue, 27 Oct 2020 21:43:37 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S374261AbgJ0VnC (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 27 Oct 2020 17:43:02 -0400
Received: from mga11.intel.com ([192.55.52.93]:17169 "EHLO mga11.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S374255AbgJ0VnC (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 27 Oct 2020 17:43:02 -0400
IronPort-SDR: 
 jhBCm9qfTYj7cDTBCGQE3rafoavo71X0dvxRFhcKbDNxMe+TsYQwaY68C78srn84FkhJh55GHJ
 uZbymX0/fN2g==
X-IronPort-AV: E=McAfee;i="6000,8403,9787"; a="164667230"
X-IronPort-AV: E=Sophos;i="5.77,424,1596524400";
   d="scan'208";a="164667230"
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from orsmga002.jf.intel.com ([10.7.209.21])
  by fmsmga102.fm.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 27 Oct 2020 14:43:01 -0700
IronPort-SDR: 
 pBWXmGg2hoMlOZK03fXrXVykvhvHWMqpc14Ocyp6ZoqiswJy47qT2/VV+/ub4fZUz+Jv8muNnH
 S2Vc9/xB0A9g==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.77,424,1596524400";
   d="scan'208";a="334537302"
Received: from sjchrist-coffee.jf.intel.com ([10.54.74.160])
  by orsmga002.jf.intel.com with ESMTP; 27 Oct 2020 14:43:01 -0700
From: Sean Christopherson <sean.j.christopherson@intel.com>
To: Paolo Bonzini <pbonzini@redhat.com>
Cc: Sean Christopherson <sean.j.christopherson@intel.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org, Ben Gardon <bgardon@google.com>
Subject: [PATCH 0/3] KVM: x86/mmu: Add macro for hugepage GFN mask
Date: Tue, 27 Oct 2020 14:42:57 -0700
Message-Id: <20201027214300.1342-1-sean.j.christopherson@intel.com>
X-Mailer: git-send-email 2.28.0
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Add a macro, which is probably long overdue, to replace open coded
variants of "~(KVM_PAGES_PER_HPAGE(level) - 1)".  The straw that broke the
camel's back is the TDP MMU's round_gfn_for_level(), which goes straight
for the optimized approach of using NEG instead of SUB+NOT (gcc uses NEG
for both).  The use of '-(...)' made me do a double take (more like a
quadrupal take) when reading the TDP MMU code as my eyes/brain have been
heavily trained to look for the more common '~(... - 1)'.

Sean Christopherson (3):
  KVM: x86/mmu: Add helper macro for computing hugepage GFN mask
  KVM: x86/mmu: Open code GFN "rounding" in TDP MMU
  KVM: x86/mmu: Use hugepage GFN mask to compute GFN offset mask

 arch/x86/include/asm/kvm_host.h |  1 +
 arch/x86/kvm/mmu/mmu.c          |  4 ++--
 arch/x86/kvm/mmu/mmutrace.h     |  2 +-
 arch/x86/kvm/mmu/paging_tmpl.h  |  4 ++--
 arch/x86/kvm/mmu/tdp_iter.c     | 11 +++--------
 arch/x86/kvm/mmu/tdp_mmu.c      |  2 +-
 arch/x86/kvm/x86.c              |  6 +++---
 7 files changed, 13 insertions(+), 17 deletions(-)
```
#### [PATCH 0/5] Add a dirty logging performance test
##### From: Ben Gardon <bgardon@google.com>

```c
From patchwork Tue Oct 27 23:37:28 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Ben Gardon <bgardon@google.com>
X-Patchwork-Id: 11862329
Return-Path: <SRS0=Fh8n=ED=vger.kernel.org=kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-14.4 required=3.0 tests=BAYES_00,DKIMWL_WL_MED,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT,USER_IN_DEF_DKIM_WL
	autolearn=no autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 31AC8C388F9
	for <kvm@archiver.kernel.org>; Wed, 28 Oct 2020 01:48:44 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id D26B322258
	for <kvm@archiver.kernel.org>; Wed, 28 Oct 2020 01:48:43 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=google.com header.i=@google.com
 header.b="N/DzRsM2"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1725894AbgJ1BiU (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 27 Oct 2020 21:38:20 -0400
Received: from mail-qt1-f201.google.com ([209.85.160.201]:32867 "EHLO
        mail-qt1-f201.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1833028AbgJ0Xhi (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 27 Oct 2020 19:37:38 -0400
Received: by mail-qt1-f201.google.com with SMTP id d22so1830227qtn.0
        for <kvm@vger.kernel.org>; Tue, 27 Oct 2020 16:37:37 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=sender:date:message-id:mime-version:subject:from:to:cc;
        bh=6Ug1lZtYrMX0hCX8/6f/DPUAAEkbtDYFeA5DkZlPqkc=;
        b=N/DzRsM28GY4x8CL71pjPGO3OSYCLyWIfrd1PuG4H2reL0PZccSPqVKIPqcokadAHH
         87rBHn3QDGRQVvW/Acuawsefr3+ORuHfUTjkkzZ/RmLMfpg47YhCPgv/TuSrQa5pbbyY
         FEkgZ4zZskh+o7+pYgWEWwW+6GUT787ftFXvG31zpkZBFTykq48XevHS6tjmLt7AkD4H
         ZgPWGZxGWmqVdpjJSCwM+zJv4FqJNi75ltZhN4mfOPo5ReM3QesZ7avjZmuz+V2qtVQb
         M0lKEZoLJ1Rhicw7meOHPruMttaqTDxLByWmxaSf/GKmHioobmSLuVD1AAY5A9UPonF+
         Vgqg==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:sender:date:message-id:mime-version:subject:from
         :to:cc;
        bh=6Ug1lZtYrMX0hCX8/6f/DPUAAEkbtDYFeA5DkZlPqkc=;
        b=qIoFQ3M74s7bkcZzWf67f+knMAj4CCk3S2uMOGcyyFTzYAmc/GWve0F0MgJJ/hAOsx
         cyd80qOPwt4HOSR9kn4128SlWIJgdQnTjJEIlNJU6pTx0RB0I0yYd50KHiJzG8XYAtUE
         1Reiw9JeMA+buTBM8ozxgP8kTeOFDAFhkky6SRvKtk3wecFzxBx+W0C3NIPIrxVa0YYR
         L46cs1ppGpPUFPXA+boYDlTgnda8RUaJtP55HtwQRuP/K8peJ0tu9q3sMcKJ2eXja5i8
         duy/J57tIXSeE4JL2fP969lFSCK5ICj56aTGj8h8FQK7w7MUaLy38isiiCaJkrmG418p
         55Ug==
X-Gm-Message-State: AOAM5336+UtYE1B4wvSMRRoAKYV16d31+IQDzeb5A24Us5fti6eQ5ebG
        Xt8n1LRx1K4Op4CvVpbVbb8KnM6o7Zpf
X-Google-Smtp-Source: 
 ABdhPJzgmw/OsHwejrlvXN9zgTn2DaC0Cj6MaccnzISVSAYnhjrxqVck1OnPb87+0mr+urAsDflzv3ecUEb2
Sender: "bgardon via sendgmr" <bgardon@bgardon.sea.corp.google.com>
X-Received: from bgardon.sea.corp.google.com
 ([2620:15c:100:202:f693:9fff:fef4:a293])
 (user=bgardon job=sendgmr) by 2002:a05:6214:136f:: with SMTP id
 c15mr4922924qvw.57.1603841856812; Tue, 27 Oct 2020 16:37:36 -0700 (PDT)
Date: Tue, 27 Oct 2020 16:37:28 -0700
Message-Id: <20201027233733.1484855-1-bgardon@google.com>
Mime-Version: 1.0
X-Mailer: git-send-email 2.29.0.rc2.309.g374f81d7ae-goog
Subject: [PATCH 0/5] Add a dirty logging performance test
From: Ben Gardon <bgardon@google.com>
To: linux-kernel@vger.kernel.org, kvm@vger.kernel.org,
        linux-kselftest@vger.kernel.org
Cc: Paolo Bonzini <pbonzini@redhat.com>, Peter Xu <peterx@redhat.com>,
        Andrew Jones <drjones@redhat.com>,
        Peter Shier <pshier@google.com>,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        Thomas Huth <thuth@redhat.com>,
        Peter Feiner <pfeiner@google.com>,
        Ben Gardon <bgardon@google.com>
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Currently KVM lacks a simple, userspace agnostic, performance benchmark for
dirty logging. Such a benchmark will be beneficial for ensuring that dirty
logging performance does not regress, and to give a common baseline for
validating performance improvements. The dirty log perf test introduced in
this series builds on aspects of the existing demand paging perf test and
provides time-based performance metrics for enabling and disabling dirty
logging, getting the dirty log, and dirtying memory.

While the test currently only has a build target for x86, I expect it will
work on, or be easily modified to support other architectures.

Ben Gardon (5):
  KVM: selftests: Factor code out of demand_paging_test
  KVM: selftests: Remove address rounding in guest code
  KVM: selftests: Simplify demand_paging_test with timespec_diff_now
  KVM: selftests: Add wrfract to common guest code
  KVM: selftests: Introduce the dirty log perf test

 tools/testing/selftests/kvm/.gitignore        |   1 +
 tools/testing/selftests/kvm/Makefile          |   1 +
 .../selftests/kvm/demand_paging_test.c        | 230 ++---------
 .../selftests/kvm/dirty_log_perf_test.c       | 382 ++++++++++++++++++
 .../selftests/kvm/include/perf_test_util.h    | 192 +++++++++
 .../testing/selftests/kvm/include/test_util.h |   2 +
 tools/testing/selftests/kvm/lib/test_util.c   |  22 +-
 7 files changed, 635 insertions(+), 195 deletions(-)
 create mode 100644 tools/testing/selftests/kvm/dirty_log_perf_test.c
 create mode 100644 tools/testing/selftests/kvm/include/perf_test_util.h
```
#### [PATCH 0/6] Some fixes and a test for KVM_CAP_ENFORCE_PV_CPUID
##### From: Oliver Upton <oupton@google.com>

```c
From patchwork Tue Oct 27 23:10:38 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Oliver Upton <oupton@google.com>
X-Patchwork-Id: 11862343
Return-Path: <SRS0=Fh8n=ED=vger.kernel.org=kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-14.4 required=3.0 tests=BAYES_00,DKIMWL_WL_MED,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT,USER_IN_DEF_DKIM_WL
	autolearn=no autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 43699C388F9
	for <kvm@archiver.kernel.org>; Wed, 28 Oct 2020 01:49:57 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 0AAE822258
	for <kvm@archiver.kernel.org>; Wed, 28 Oct 2020 01:49:57 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=google.com header.i=@google.com
 header.b="JRHJXLuB"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1725783AbgJ1BiR (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 27 Oct 2020 21:38:17 -0400
Received: from mail-qt1-f202.google.com ([209.85.160.202]:45255 "EHLO
        mail-qt1-f202.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1832968AbgJ0XKu (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 27 Oct 2020 19:10:50 -0400
Received: by mail-qt1-f202.google.com with SMTP id d1so1786917qtq.12
        for <kvm@vger.kernel.org>; Tue, 27 Oct 2020 16:10:49 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=sender:date:message-id:mime-version:subject:from:to:cc;
        bh=uVAAxKGJ44GQm3v30eEW5qbX5guH3UCpsLTIfZxxtQY=;
        b=JRHJXLuBj+LDLo6Q2/72KrMf25WUa/E7TLphQprRGfUPBe8sWa700mwqtq4VS7CQbt
         aFeV3o7ZdZxxKwnemWG1gFtqSo0OvKvdW4yeAsvdb4lYHROMaCkQc/eFDHiHTK9gXXOh
         V374M7ALafSs95G70oV2/5LMdpx7m1Ww6T5dquiuxBEJWEdrunpCL4G0Xf9tagr4o1LV
         ALLGIxTRV03sCuSkV6HJTZHbLbP+ucgPoN2mYTEdQpgbHmQEzge/OFDdQmU4Q1kGMaWL
         qr+wW9OaZeF30c4lfF1yq7gGKLNZvErNHhxf80qQsGPNB47GZefraObQ+pgdbQQBVzR0
         RP0A==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:sender:date:message-id:mime-version:subject:from
         :to:cc;
        bh=uVAAxKGJ44GQm3v30eEW5qbX5guH3UCpsLTIfZxxtQY=;
        b=nKHXiPJX3i74sLDt73ntCp/o/2tydYWDTAfUweMoDcNli5S/wjWuwOGsMEom35+hML
         vA97k8zlwwLzuYwr8XBo37E6M5oZlZAdODRCr3jG1SzkVCO1jRgpU6/3wIYY5JO6biAJ
         6drsExVgJPdpVZta46roQ0Vr1ST88EzL7MZLns5q2X3IhciCq054SYsloyixz4xXl5Hx
         n5dcQ948LXVFschwRvUKJj+iV5lGRfd0Up8NEpq1wXHCuGMjUESU3J7jqARd3yowrOau
         Y4eGpvxgbO2wimIvpkQ6jUikW9NiXwu7vwzLDUS2pQwEt3bOjfIoY7n2asVIqt+Cn3U0
         vb7w==
X-Gm-Message-State: AOAM531fXSYUKfGwrkf7Kh3wDBd+Xsc6YdrtyAyf+P+njdL/hJysLd19
        WpCQ7PmtZv7gE/uJKyjJxwj9SccLJvJsB80VrV+LaBgMUPlnySAJtDl97YR7dQp2x+e+KSrf/YM
        UmW1S9gmHUlj6AnOco4SpLMYEfT1B06md6ButPsiBtmFFknwr7dODBrlawQ==
X-Google-Smtp-Source: 
 ABdhPJwPzKC+hfIYYBnir3+51Cmml4y9HuMtFMH9mI9B/RyTufG7gwNGJX/UpKausFhYMPU7ih3WhxMCN3E=
Sender: "oupton via sendgmr" <oupton@oupton.sea.corp.google.com>
X-Received: from oupton.sea.corp.google.com
 ([2620:15c:100:202:f693:9fff:fef5:7be1])
 (user=oupton job=sendgmr) by 2002:a0c:c612:: with SMTP id
 v18mr4719294qvi.61.1603840248708;
 Tue, 27 Oct 2020 16:10:48 -0700 (PDT)
Date: Tue, 27 Oct 2020 16:10:38 -0700
Message-Id: <20201027231044.655110-1-oupton@google.com>
Mime-Version: 1.0
X-Mailer: git-send-email 2.29.0.rc2.309.g374f81d7ae-goog
Subject: [PATCH 0/6] Some fixes and a test for KVM_CAP_ENFORCE_PV_CPUID
From: Oliver Upton <oupton@google.com>
To: kvm@vger.kernel.org
Cc: Paolo Bonzini <pbonzini@redhat.com>,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        Oliver Upton <oupton@google.com>
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Patches 1-2 address some small issues with documentation and the kvm selftests,
unrelated to the overall intent of this series.

Patch 3 applies the same PV MSR filtering mechanism to guest reads of KVM
paravirt msrs.

Patch 4 makes enabling KVM_CAP_ENFORCE_PV_FEATURE_CPUID idempotent with regards
to when userspace sets the guest's CPUID, ensuring that the cached copy of
KVM_CPUID_FEATURES.EAX is always current.

Patch 5 fixes a regression introduced with KVM_CAP_ENFORCE_PV_CPUID, wherein
the kvm masterclock isn't updated every time the guest uses a different system
time msr than before.

Lastly, Patch 6 introduces a test for the overall paravirtual restriction
mechanism, verifying that guests GP when touching MSRs they shouldn't and
get -KVM_ENOSYS when using restricted kvm hypercalls. Please note that this test
is dependent upon patches 1-3 of Aaron's userspace MSR test, which add support
for guest handling of the IDT in KVM selftests [1].

This series (along with Aaron's aforementioned changes) applies to
commit 77377064c3a9 ("KVM: ioapic: break infinite recursion on lazy
EOI").

[1] http://lore.kernel.org/r/20201012194716.3950330-1-aaronlewis@google.com

Oliver Upton (6):
  selftests: kvm: add tsc_msrs_test binary to gitignore
  Documentation: kvm: fix ordering of msr filter, pv documentation
  kvm: x86: reads of restricted pv msrs should also result in #GP
  kvm: x86: ensure pv_cpuid.features is initialized when enabling cap
  kvm: x86: request masterclock update any time guest uses different msr
  selftests: kvm: test enforcement of paravirtual cpuid features

 Documentation/virt/kvm/api.rst                |   4 +-
 arch/x86/kvm/cpuid.c                          |  23 +-
 arch/x86/kvm/cpuid.h                          |   1 +
 arch/x86/kvm/x86.c                            |  38 ++-
 tools/testing/selftests/kvm/.gitignore        |   2 +
 tools/testing/selftests/kvm/Makefile          |   1 +
 .../testing/selftests/kvm/include/kvm_util.h  |   2 +
 .../selftests/kvm/include/x86_64/processor.h  |  12 +
 tools/testing/selftests/kvm/lib/kvm_util.c    |  28 +++
 .../selftests/kvm/lib/x86_64/processor.c      |  29 +++
 .../selftests/kvm/x86_64/kvm_pv_test.c        | 234 ++++++++++++++++++
 11 files changed, 364 insertions(+), 10 deletions(-)
 create mode 100644 tools/testing/selftests/kvm/x86_64/kvm_pv_test.c
```
