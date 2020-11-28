#### [PATCH 1/2] KVM: arm64: Correctly align nVHE percpu data
##### From: Marc Zyngier <maz@kernel.org>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Marc Zyngier <maz@kernel.org>
X-Patchwork-Id: 11935569
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-19.0 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED,USER_AGENT_GIT
	autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id CC8FDC8300B
	for <kvm@archiver.kernel.org>; Fri, 27 Nov 2020 11:21:38 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 737E72222A
	for <kvm@archiver.kernel.org>; Fri, 27 Nov 2020 11:21:38 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=kernel.org header.i=@kernel.org
 header.b="CSdQ4/Si"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729521AbgK0LVa (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Fri, 27 Nov 2020 06:21:30 -0500
Received: from mail.kernel.org ([198.145.29.99]:54890 "EHLO mail.kernel.org"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1729330AbgK0LVV (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 27 Nov 2020 06:21:21 -0500
Received: from disco-boy.misterjones.org (disco-boy.misterjones.org
 [51.254.78.96])
        (using TLSv1.2 with cipher ECDHE-RSA-AES256-GCM-SHA384 (256/256 bits))
        (No client certificate requested)
        by mail.kernel.org (Postfix) with ESMTPSA id 4B10A2222A;
        Fri, 27 Nov 2020 11:21:21 +0000 (UTC)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple; d=kernel.org;
        s=default; t=1606476081;
        bh=uSWDwx9Mf1mz4a4sUj9aoF18Ki8K132MbX4ipSnTuaA=;
        h=From:To:Cc:Subject:Date:In-Reply-To:References:From;
        b=CSdQ4/SiMbCkHZxxf4Xs9Ns/mlpYP1T71glovqQ0NVcxhqtksVhVYpdTLzXNhgxZv
         vxegoO+0yoZaQO+E1WUMzUy6gw3GLPoQWV/C2mTN1/jNxJWk44z60pdoSM8Y8O6IOi
         Clu/4rn5Cy8XBMNSox/QlksFtx2LpU1VnU5t6Xvg=
Received: from 78.163-31-62.static.virginmediabusiness.co.uk ([62.31.163.78]
 helo=why.lan)
        by disco-boy.misterjones.org with esmtpsa  (TLS1.3) tls
 TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384
        (Exim 4.94)
        (envelope-from <maz@kernel.org>)
        id 1kiboV-00E2fR-EV; Fri, 27 Nov 2020 11:21:19 +0000
From: Marc Zyngier <maz@kernel.org>
To: Paolo Bonzini <pbonzini@redhat.com>
Cc: David Brazdil <dbrazdil@google.com>,
        Eric Auger <eric.auger@redhat.com>,
        Jamie Iles <jamie@nuviainc.com>,
        Keqian Zhu <zhukeqian1@huawei.com>,
        Will Deacon <will@kernel.org>,
        Zenghui Yu <yuzenghui@huawei.com>,
        James Morse <james.morse@arm.com>,
        Julien Thierry <julien.thierry.kdev@gmail.com>,
        Suzuki K Poulose <suzuki.poulose@arm.com>,
        kernel-team@android.com, linux-arm-kernel@lists.infradead.org,
        kvmarm@lists.cs.columbia.edu, kvm@vger.kernel.org
Subject: [PATCH 1/2] KVM: arm64: Correctly align nVHE percpu data
Date: Fri, 27 Nov 2020 11:21:00 +0000
Message-Id: <20201127112101.658224-2-maz@kernel.org>
X-Mailer: git-send-email 2.28.0
In-Reply-To: <20201127112101.658224-1-maz@kernel.org>
References: <20201127112101.658224-1-maz@kernel.org>
MIME-Version: 1.0
X-SA-Exim-Connect-IP: 62.31.163.78
X-SA-Exim-Rcpt-To: pbonzini@redhat.com, dbrazdil@google.com,
 eric.auger@redhat.com, jamie@nuviainc.com, zhukeqian1@huawei.com,
 will@kernel.org, yuzenghui@huawei.com, james.morse@arm.com,
 julien.thierry.kdev@gmail.com, suzuki.poulose@arm.com,
 kernel-team@android.com, linux-arm-kernel@lists.infradead.org,
 kvmarm@lists.cs.columbia.edu, kvm@vger.kernel.org
X-SA-Exim-Mail-From: maz@kernel.org
X-SA-Exim-Scanned: No (on disco-boy.misterjones.org);
 SAEximRunCond expanded to false
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Jamie Iles <jamie@nuviainc.com>

The nVHE percpu data is partially linked but the nVHE linker script did
not align the percpu section.  The PERCPU_INPUT macro would then align
the data to a page boundary:

  #define PERCPU_INPUT(cacheline)					\
  	__per_cpu_start = .;						\
  	*(.data..percpu..first)						\
  	. = ALIGN(PAGE_SIZE);						\
  	*(.data..percpu..page_aligned)					\
  	. = ALIGN(cacheline);						\
  	*(.data..percpu..read_mostly)					\
  	. = ALIGN(cacheline);						\
  	*(.data..percpu)						\
  	*(.data..percpu..shared_aligned)				\
  	PERCPU_DECRYPTED_SECTION					\
  	__per_cpu_end = .;

but then when the final vmlinux linking happens the hypervisor percpu
data is included after page alignment and so the offsets potentially
don't match.  On my build I saw that the .hyp.data..percpu section was
at address 0x20 and then the percpu data would begin at 0x1000 (because
of the page alignment in PERCPU_INPUT), but when linked into vmlinux,
everything would be shifted down by 0x20 bytes.

This manifests as one of the CPUs getting lost when running
kvm-unit-tests or starting any VM and subsequent soft lockup on a Cortex
A72 device.

Fixes: 30c953911c43 ("kvm: arm64: Set up hyp percpu data for nVHE")
Signed-off-by: Jamie Iles <jamie@nuviainc.com>
Signed-off-by: Marc Zyngier <maz@kernel.org>
Acked-by: David Brazdil <dbrazdil@google.com>
Cc: David Brazdil <dbrazdil@google.com>
Cc: Marc Zyngier <maz@kernel.org>
Cc: Will Deacon <will@kernel.org>
Link: https://lore.kernel.org/r/20201113150406.14314-1-jamie@nuviainc.com
---
 arch/arm64/kvm/hyp/nvhe/hyp.lds.S | 5 +++++
 1 file changed, 5 insertions(+)

```
#### [PATCH v7 01/17] drm/exynos: Stop using frame_vector helpers
##### From: Daniel Vetter <daniel.vetter@ffwll.ch>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 8bit
X-Patchwork-Submitter: Daniel Vetter <daniel.vetter@ffwll.ch>
X-Patchwork-Id: 11936825
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-18.7 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,
	INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED,
	USER_AGENT_GIT autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 4C4F6C82486
	for <kvm@archiver.kernel.org>; Fri, 27 Nov 2020 16:43:54 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 1095A206D8
	for <kvm@archiver.kernel.org>; Fri, 27 Nov 2020 16:43:54 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=ffwll.ch header.i=@ffwll.ch
 header.b="ZUgYtuqu"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1731405AbgK0QmA (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Fri, 27 Nov 2020 11:42:00 -0500
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:54012 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1731524AbgK0QmA (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 27 Nov 2020 11:42:00 -0500
Received: from mail-wr1-x443.google.com (mail-wr1-x443.google.com
 [IPv6:2a00:1450:4864:20::443])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id B7B72C061A04
        for <kvm@vger.kernel.org>; Fri, 27 Nov 2020 08:41:59 -0800 (PST)
Received: by mail-wr1-x443.google.com with SMTP id u12so6230917wrt.0
        for <kvm@vger.kernel.org>; Fri, 27 Nov 2020 08:41:59 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=ffwll.ch; s=google;
        h=from:to:cc:subject:date:message-id:in-reply-to:references
         :mime-version:content-transfer-encoding;
        bh=/sh5bs9TsYHYjvxKHF7f8Ku58Ybt71LSBBC/IzYD81Y=;
        b=ZUgYtuqulcoekyn4/DmS1kFLLSpaYhGwPtaiS4etvDJ4hqCcKQ9cof4OsFdlK+OZwX
         /ER9XnkoUa8V6V6Qw8vMOYFotLZdmZyietIl3Zsl8wbRwbLmxfViSl5mIrxb8X/uTceC
         yaR+5hwHDEsE+H9iZ92RvTlkLr27AxXM+Atr4=
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:in-reply-to
         :references:mime-version:content-transfer-encoding;
        bh=/sh5bs9TsYHYjvxKHF7f8Ku58Ybt71LSBBC/IzYD81Y=;
        b=skBPGXoTxutItzLxSQfFEiFRyP1D8y1YiJfzrZTEhtX+PGiIbuxRn5vW9HJycAaksY
         vrIi8l0bJoCJozfNiW+g6NP/USyf9hiqpHeis7HhssYn5cCq+oouo2gbWZ60o/5UAHjr
         MKg29KMOW1dX0r8A3De+rHIItmvVzA8P2BU3K6lNlM7BvdCAz8ujGZBjdaDZdDEF5vhD
         KZrsbR6g6cd6AZczQ0Pe9vZF9IRxMmcdDK/iJms8i5d0Ld/SgeoraVpWTt0kIpxxwLch
         pW6wmlPOns0CGstjgcGILpyLs7Gtd45yBbcMqEnGdIFXdtzh6Wgthv3hIXhm7RJxtuoU
         zWeA==
X-Gm-Message-State: AOAM533uy3k+1SJoo4MF0FQoLHyHWAbfT4zfraDCLVKcnW66o6zszFya
        1qoYUQsBfm/htRyA24A7ohVpKQ==
X-Google-Smtp-Source: 
 ABdhPJxrHFLYiVOKd4LtxuEtdsZyIsxVIgBM9ROp4FnD1+Tfa5L6neNEaRf8jGsJWtkGxmbFQqkP0g==
X-Received: by 2002:adf:e54f:: with SMTP id
 z15mr12003413wrm.159.1606495318430;
        Fri, 27 Nov 2020 08:41:58 -0800 (PST)
Received: from phenom.ffwll.local ([2a02:168:57f4:0:efd0:b9e5:5ae6:c2fa])
        by smtp.gmail.com with ESMTPSA id
 q12sm14859078wrx.86.2020.11.27.08.41.57
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Fri, 27 Nov 2020 08:41:57 -0800 (PST)
From: Daniel Vetter <daniel.vetter@ffwll.ch>
To: DRI Development <dri-devel@lists.freedesktop.org>,
        LKML <linux-kernel@vger.kernel.org>
Cc: kvm@vger.kernel.org, linux-mm@kvack.org,
 linux-arm-kernel@lists.infradead.org, linux-samsung-soc@vger.kernel.org,
 linux-media@vger.kernel.org, Daniel Vetter <daniel.vetter@ffwll.ch>,
 John Hubbard <jhubbard@nvidia.com>, Daniel Vetter <daniel.vetter@intel.com>,
 Jason Gunthorpe <jgg@ziepe.ca>, Inki Dae <inki.dae@samsung.com>,
 Joonyoung Shim <jy0922.shim@samsung.com>,
 Seung-Woo Kim <sw0312.kim@samsung.com>,
 Kyungmin Park <kyungmin.park@samsung.com>, Kukjin Kim <kgene@kernel.org>,
 Krzysztof Kozlowski <krzk@kernel.org>,
 Andrew Morton <akpm@linux-foundation.org>,
 Christoph Hellwig <hch@infradead.org>,
 =?utf-8?b?SsOpcsO0bWUgR2xpc3Nl?= <jglisse@redhat.com>,
 Jan Kara <jack@suse.cz>, Dan Williams <dan.j.williams@intel.com>
Subject: [PATCH v7 01/17] drm/exynos: Stop using frame_vector helpers
Date: Fri, 27 Nov 2020 17:41:15 +0100
Message-Id: <20201127164131.2244124-2-daniel.vetter@ffwll.ch>
X-Mailer: git-send-email 2.29.2
In-Reply-To: <20201127164131.2244124-1-daniel.vetter@ffwll.ch>
References: <20201127164131.2244124-1-daniel.vetter@ffwll.ch>
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

All we need are a pages array, pin_user_pages_fast can give us that
directly. Plus this avoids the entire raw pfn side of get_vaddr_frames.

Note that pin_user_pages_fast is a safe replacement despite the
seeming lack of checking for vma->vm_flasg & (VM_IO | VM_PFNMAP). Such
ptes are marked with pte_mkspecial (which pup_fast rejects in the
fastpath), and only architectures supporting that support the
pin_user_pages_fast fastpath.

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
Cc: Christoph Hellwig <hch@infradead.org>
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
v6: Explain why pup_fast is safe, after discussions with John and
Christoph.
---
 drivers/gpu/drm/exynos/Kconfig          |  1 -
 drivers/gpu/drm/exynos/exynos_drm_g2d.c | 47 +++++++++++--------------
 2 files changed, 20 insertions(+), 28 deletions(-)

```
#### [GIT PULL] KVM/arm64 fixes for 5.10, take #4
##### From: Marc Zyngier <maz@kernel.org>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Marc Zyngier <maz@kernel.org>
X-Patchwork-Id: 11935563
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-24.0 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,INCLUDES_PATCH,INCLUDES_PULL_REQUEST,
	MAILING_LIST_MULTI,MENTIONS_GIT_HOSTING,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT
	autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id EAE40C64E7C
	for <kvm@archiver.kernel.org>; Fri, 27 Nov 2020 11:21:36 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 9861120B80
	for <kvm@archiver.kernel.org>; Fri, 27 Nov 2020 11:21:36 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=kernel.org header.i=@kernel.org
 header.b="kCn5yoOc"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729229AbgK0LVX (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Fri, 27 Nov 2020 06:21:23 -0500
Received: from mail.kernel.org ([198.145.29.99]:54866 "EHLO mail.kernel.org"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1729265AbgK0LVW (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 27 Nov 2020 06:21:22 -0500
Received: from disco-boy.misterjones.org (disco-boy.misterjones.org
 [51.254.78.96])
        (using TLSv1.2 with cipher ECDHE-RSA-AES256-GCM-SHA384 (256/256 bits))
        (No client certificate requested)
        by mail.kernel.org (Postfix) with ESMTPSA id 0DF2420B80;
        Fri, 27 Nov 2020 11:21:21 +0000 (UTC)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple; d=kernel.org;
        s=default; t=1606476081;
        bh=fS6mF1IDPaTZHP4+FiQm7nj4O1emt6KtMrKo/Vv9QOc=;
        h=From:To:Cc:Subject:Date:From;
        b=kCn5yoOc6ucB2MaxXimiA11mtBW5b7w5jKlVWS+s12qCYG6LSHjmiqy+k2ejZBkv3
         XElrP4//E0eXdoRXTavH98gI/PnZRvEgzpQ4Y/ln8xpg4QBUKyoGXnql/wf9OLMk/+
         zBphLzrdbtGS3HJvO13T9ICBUY2NsoWmCV/Fr1Ro=
Received: from 78.163-31-62.static.virginmediabusiness.co.uk ([62.31.163.78]
 helo=why.lan)
        by disco-boy.misterjones.org with esmtpsa  (TLS1.3) tls
 TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384
        (Exim 4.94)
        (envelope-from <maz@kernel.org>)
        id 1kiboU-00E2fR-Nq; Fri, 27 Nov 2020 11:21:18 +0000
From: Marc Zyngier <maz@kernel.org>
To: Paolo Bonzini <pbonzini@redhat.com>
Cc: David Brazdil <dbrazdil@google.com>,
        Eric Auger <eric.auger@redhat.com>,
        Jamie Iles <jamie@nuviainc.com>,
        Keqian Zhu <zhukeqian1@huawei.com>,
        Will Deacon <will@kernel.org>,
        Zenghui Yu <yuzenghui@huawei.com>,
        James Morse <james.morse@arm.com>,
        Julien Thierry <julien.thierry.kdev@gmail.com>,
        Suzuki K Poulose <suzuki.poulose@arm.com>,
        kernel-team@android.com, linux-arm-kernel@lists.infradead.org,
        kvmarm@lists.cs.columbia.edu, kvm@vger.kernel.org
Subject: [GIT PULL] KVM/arm64 fixes for 5.10, take #4
Date: Fri, 27 Nov 2020 11:20:59 +0000
Message-Id: <20201127112101.658224-1-maz@kernel.org>
X-Mailer: git-send-email 2.28.0
MIME-Version: 1.0
X-SA-Exim-Connect-IP: 62.31.163.78
X-SA-Exim-Rcpt-To: pbonzini@redhat.com, dbrazdil@google.com,
 eric.auger@redhat.com, jamie@nuviainc.com, zhukeqian1@huawei.com,
 will@kernel.org, yuzenghui@huawei.com, james.morse@arm.com,
 julien.thierry.kdev@gmail.com, suzuki.poulose@arm.com,
 kernel-team@android.com, linux-arm-kernel@lists.infradead.org,
 kvmarm@lists.cs.columbia.edu, kvm@vger.kernel.org
X-SA-Exim-Mail-From: maz@kernel.org
X-SA-Exim-Scanned: No (on disco-boy.misterjones.org);
 SAEximRunCond expanded to false
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Hi Paolo,

This is hopefully the last set of fixes for 5.10. We have a linker
script fix addressing the alignment requirement for the way we now
build the EL2 code, and a fix for a long standing bug affecting
userspace access to the GICR_TYPER registers.

Please pull,

	M.

The following changes since commit ed4ffaf49bf9ce1002b516d8c6aa04937b7950bc:

  KVM: arm64: Handle SCXTNUM_ELx traps (2020-11-12 21:22:46 +0000)

are available in the Git repository at:

  git://git.kernel.org/pub/scm/linux/kernel/git/kvmarm/kvmarm.git tags/kvmarm-fixes-5.10-4

for you to fetch changes up to 23bde34771f1ea92fb5e6682c0d8c04304d34b3b:

  KVM: arm64: vgic-v3: Drop the reporting of GICR_TYPER.Last for userspace (2020-11-17 18:51:09 +0000)

----------------------------------------------------------------
KVM/arm64 fixes for v5.10, take #4

- Fix alignment of the new HYP sections
- Fix GICR_TYPER access from userspace

----------------------------------------------------------------
Jamie Iles (1):
      KVM: arm64: Correctly align nVHE percpu data

Zenghui Yu (1):
      KVM: arm64: vgic-v3: Drop the reporting of GICR_TYPER.Last for userspace

 arch/arm64/kvm/hyp/nvhe/hyp.lds.S  |  5 +++++
 arch/arm64/kvm/vgic/vgic-mmio-v3.c | 22 ++++++++++++++++++++--
 2 files changed, 25 insertions(+), 2 deletions(-)

From patchwork Fri Nov 27 11:21:01 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Marc Zyngier <maz@kernel.org>
X-Patchwork-Id: 11935565
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-19.0 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED,USER_AGENT_GIT
	autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 70ECDC64E8A
	for <kvm@archiver.kernel.org>; Fri, 27 Nov 2020 11:21:37 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 174A820B80
	for <kvm@archiver.kernel.org>; Fri, 27 Nov 2020 11:21:37 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=kernel.org header.i=@kernel.org
 header.b="H63Vu6qu"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729506AbgK0LVZ (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Fri, 27 Nov 2020 06:21:25 -0500
Received: from mail.kernel.org ([198.145.29.99]:54932 "EHLO mail.kernel.org"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1729416AbgK0LVX (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 27 Nov 2020 06:21:23 -0500
Received: from disco-boy.misterjones.org (disco-boy.misterjones.org
 [51.254.78.96])
        (using TLSv1.2 with cipher ECDHE-RSA-AES256-GCM-SHA384 (256/256 bits))
        (No client certificate requested)
        by mail.kernel.org (Postfix) with ESMTPSA id EAE8521973;
        Fri, 27 Nov 2020 11:21:21 +0000 (UTC)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple; d=kernel.org;
        s=default; t=1606476082;
        bh=PewcZ0rzrlxCPatqpFVI8s3T+tQgk8XqSu8BrcC/ilQ=;
        h=From:To:Cc:Subject:Date:In-Reply-To:References:From;
        b=H63Vu6qusRwErPgOfLpBLFRWoEte988yFNickgfvXC+IYjUnhqYu7DvOU2urmnqNK
         nlFK/wdYkQg1aHaZ2dWReYE/eN+BYg/v9r+vZdxIPv57goM4FM/HSaAbi6XBBwct25
         OIloVfJMIjMAvooAdKZUsIqBbdIEFPg06MnWpeOA=
Received: from 78.163-31-62.static.virginmediabusiness.co.uk ([62.31.163.78]
 helo=why.lan)
        by disco-boy.misterjones.org with esmtpsa  (TLS1.3) tls
 TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384
        (Exim 4.94)
        (envelope-from <maz@kernel.org>)
        id 1kiboW-00E2fR-4z; Fri, 27 Nov 2020 11:21:20 +0000
From: Marc Zyngier <maz@kernel.org>
To: Paolo Bonzini <pbonzini@redhat.com>
Cc: David Brazdil <dbrazdil@google.com>,
        Eric Auger <eric.auger@redhat.com>,
        Jamie Iles <jamie@nuviainc.com>,
        Keqian Zhu <zhukeqian1@huawei.com>,
        Will Deacon <will@kernel.org>,
        Zenghui Yu <yuzenghui@huawei.com>,
        James Morse <james.morse@arm.com>,
        Julien Thierry <julien.thierry.kdev@gmail.com>,
        Suzuki K Poulose <suzuki.poulose@arm.com>,
        kernel-team@android.com, linux-arm-kernel@lists.infradead.org,
        kvmarm@lists.cs.columbia.edu, kvm@vger.kernel.org,
        stable@vger.kernel.org
Subject: [PATCH 2/2] KVM: arm64: vgic-v3: Drop the reporting of
 GICR_TYPER.Last for userspace
Date: Fri, 27 Nov 2020 11:21:01 +0000
Message-Id: <20201127112101.658224-3-maz@kernel.org>
X-Mailer: git-send-email 2.28.0
In-Reply-To: <20201127112101.658224-1-maz@kernel.org>
References: <20201127112101.658224-1-maz@kernel.org>
MIME-Version: 1.0
X-SA-Exim-Connect-IP: 62.31.163.78
X-SA-Exim-Rcpt-To: pbonzini@redhat.com, dbrazdil@google.com,
 eric.auger@redhat.com, jamie@nuviainc.com, zhukeqian1@huawei.com,
 will@kernel.org, yuzenghui@huawei.com, james.morse@arm.com,
 julien.thierry.kdev@gmail.com, suzuki.poulose@arm.com,
 kernel-team@android.com, linux-arm-kernel@lists.infradead.org,
 kvmarm@lists.cs.columbia.edu, kvm@vger.kernel.org, stable@vger.kernel.org
X-SA-Exim-Mail-From: maz@kernel.org
X-SA-Exim-Scanned: No (on disco-boy.misterjones.org);
 SAEximRunCond expanded to false
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Zenghui Yu <yuzenghui@huawei.com>

It was recently reported that if GICR_TYPER is accessed before the RD base
address is set, we'll suffer from the unset @rdreg dereferencing. Oops...

	gpa_t last_rdist_typer = rdreg->base + GICR_TYPER +
			(rdreg->free_index - 1) * KVM_VGIC_V3_REDIST_SIZE;

It's "expected" that users will access registers in the redistributor if
the RD has been properly configured (e.g., the RD base address is set). But
it hasn't yet been covered by the existing documentation.

Per discussion on the list [1], the reporting of the GICR_TYPER.Last bit
for userspace never actually worked. And it's difficult for us to emulate
it correctly given that userspace has the flexibility to access it any
time. Let's just drop the reporting of the Last bit for userspace for now
(userspace should have full knowledge about it anyway) and it at least
prevents kernel from panic ;-)

[1] https://lore.kernel.org/kvmarm/c20865a267e44d1e2c0d52ce4e012263@kernel.org/

Fixes: ba7b3f1275fd ("KVM: arm/arm64: Revisit Redistributor TYPER last bit computation")
Reported-by: Keqian Zhu <zhukeqian1@huawei.com>
Signed-off-by: Zenghui Yu <yuzenghui@huawei.com>
Signed-off-by: Marc Zyngier <maz@kernel.org>
Reviewed-by: Eric Auger <eric.auger@redhat.com>
Link: https://lore.kernel.org/r/20201117151629.1738-1-yuzenghui@huawei.com
Cc: stable@vger.kernel.org
---
 arch/arm64/kvm/vgic/vgic-mmio-v3.c | 22 ++++++++++++++++++++--
 1 file changed, 20 insertions(+), 2 deletions(-)

```
#### [GIT PULL] KVM changes for 5.10-rc6
##### From: Paolo Bonzini <pbonzini@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Paolo Bonzini <pbonzini@redhat.com>
X-Patchwork-Id: 11936647
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-20.8 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_PATCH,INCLUDES_PULL_REQUEST,MAILING_LIST_MULTI,MENTIONS_GIT_HOSTING,
	SPF_HELO_NONE,SPF_PASS autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 6D1DFC3E8C5
	for <kvm@archiver.kernel.org>; Fri, 27 Nov 2020 16:39:10 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 25C3422240
	for <kvm@archiver.kernel.org>; Fri, 27 Nov 2020 16:39:10 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="NttPPvHS"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1731311AbgK0Qiy (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Fri, 27 Nov 2020 11:38:54 -0500
Received: from us-smtp-delivery-124.mimecast.com ([216.205.24.124]:24317 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1727936AbgK0Qix (ORCPT
        <rfc822;kvm@vger.kernel.org>); Fri, 27 Nov 2020 11:38:53 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1606495132;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=SAZDDMrXNdQFAZBn+CKA9ZaDVCs9UUciZaI7AEvpNhE=;
        b=NttPPvHSLEYIlINkC/eflL+H2JcL8vDFriUv33Zo6OsBngyngES+YPeJDR/ntm5OStyza+
        vJ/i9w2rqiVY7rPB+kGFxqnY2E3ByHWX2zPTe8JRKrL4P1wNpC9jvlDAqXFE2/9ALT1zLs
        1jVm1uWe1wWqZFZoA2Uxt+r6HSn0qZ8=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-233-r38OCtYUNZGUMrxkJBLcwQ-1; Fri, 27 Nov 2020 11:38:48 -0500
X-MC-Unique: r38OCtYUNZGUMrxkJBLcwQ-1
Received: from smtp.corp.redhat.com (int-mx07.intmail.prod.int.phx2.redhat.com
 [10.5.11.22])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 0DDEC8049C3;
        Fri, 27 Nov 2020 16:38:47 +0000 (UTC)
Received: from virtlab701.virt.lab.eng.bos.redhat.com
 (virtlab701.virt.lab.eng.bos.redhat.com [10.19.152.228])
        by smtp.corp.redhat.com (Postfix) with ESMTP id AEB9D10021B3;
        Fri, 27 Nov 2020 16:38:46 +0000 (UTC)
From: Paolo Bonzini <pbonzini@redhat.com>
To: torvalds@linux-foundation.org
Cc: linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Subject: [GIT PULL] KVM changes for 5.10-rc6
Date: Fri, 27 Nov 2020 11:38:46 -0500
Message-Id: <20201127163846.3233976-1-pbonzini@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.84 on 10.5.11.22
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Linus,

The following changes since commit c887c9b9ca62c051d339b1c7b796edf2724029ed:

  kvm: mmu: fix is_tdp_mmu_check when the TDP MMU is not in use (2020-11-15 08:55:43 -0500)

are available in the Git repository at:

  https://git.kernel.org/pub/scm/virt/kvm/kvm.git tags/for-linus

for you to fetch changes up to 9a2a0d3ca163fc645991804b8b032f7d59326bb5:

  kvm: x86/mmu: Fix get_mmio_spte() on CPUs supporting 5-level PT (2020-11-27 11:14:27 -0500)

----------------------------------------------------------------
ARM:
- Fix alignment of the new HYP sections
- Fix GICR_TYPER access from userspace

S390:
- do not reset the global diag318 data for per-cpu reset
- do not mark memory as protected too early
- fix for destroy page ultravisor call

x86:
- fix for SEV debugging
- fix incorrect return code
- fix for "noapic" with PIC in userspace and LAPIC in kernel
- fix for 5-level paging

----------------------------------------------------------------
Ashish Kalra (1):
      KVM: SVM: Fix offset computation bug in __sev_dbg_decrypt().

Chen Zhou (1):
      KVM: SVM: fix error return code in svm_create_vcpu()

Christian Borntraeger (2):
      s390/uv: handle destroy page legacy interface
      MAINTAINERS: add uv.c also to KVM/s390

Collin Walling (1):
      KVM: s390: remove diag318 reset code

Jamie Iles (1):
      KVM: arm64: Correctly align nVHE percpu data

Janosch Frank (1):
      KVM: s390: pv: Mark mm as protected after the set secure parameters and improve cleanup

Paolo Bonzini (5):
      Merge tag 'kvm-s390-master-5.10-1' of git://git.kernel.org/.../kvms390/linux into kvm-master
      Merge tag 'kvm-s390-master-5.10-2' of git://git.kernel.org/.../kvms390/linux into kvm-master
      Merge tag 'kvmarm-fixes-5.10-4' of git://git.kernel.org/.../kvmarm/kvmarm into kvm-master
      KVM: x86: handle !lapic_in_kernel case in kvm_cpu_*_extint
      KVM: x86: Fix split-irqchip vs interrupt injection window request

Sean Christopherson (1):
      MAINTAINERS: Update email address for Sean Christopherson

Vitaly Kuznetsov (1):
      kvm: x86/mmu: Fix get_mmio_spte() on CPUs supporting 5-level PT

Zenghui Yu (1):
      KVM: arm64: vgic-v3: Drop the reporting of GICR_TYPER.Last for userspace

 .mailmap                           |  1 +
 MAINTAINERS                        |  1 +
 arch/arm64/kvm/hyp/nvhe/hyp.lds.S  |  5 +++
 arch/arm64/kvm/vgic/vgic-mmio-v3.c | 22 +++++++++-
 arch/s390/kernel/uv.c              |  9 +++-
 arch/s390/kvm/kvm-s390.c           |  4 +-
 arch/s390/kvm/pv.c                 |  3 +-
 arch/s390/mm/gmap.c                |  2 +
 arch/x86/include/asm/kvm_host.h    |  1 +
 arch/x86/kvm/irq.c                 | 85 +++++++++++++++-----------------------
 arch/x86/kvm/lapic.c               |  2 +-
 arch/x86/kvm/mmu/mmu.c             |  2 +-
 arch/x86/kvm/svm/sev.c             |  2 +-
 arch/x86/kvm/svm/svm.c             |  4 +-
 arch/x86/kvm/x86.c                 | 18 ++++----
 15 files changed, 91 insertions(+), 70 deletions(-)
```
#### [PATCH 1/2] KVM: x86: handle !lapic_in_kernel case in kvm_cpu_*_extint
##### From: Paolo Bonzini <pbonzini@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Paolo Bonzini <pbonzini@redhat.com>
X-Patchwork-Id: 11935567
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-15.8 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_CR_TRAILER,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS
	autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 4EA4FC63777
	for <kvm@archiver.kernel.org>; Fri, 27 Nov 2020 11:21:38 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id E806121973
	for <kvm@archiver.kernel.org>; Fri, 27 Nov 2020 11:21:37 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="M9rAbe9H"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729407AbgK0LVW (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Fri, 27 Nov 2020 06:21:22 -0500
Received: from us-smtp-delivery-124.mimecast.com ([216.205.24.124]:39810 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1725989AbgK0LVV (ORCPT
        <rfc822;kvm@vger.kernel.org>); Fri, 27 Nov 2020 06:21:21 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1606476079;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding:
         in-reply-to:in-reply-to:references:references;
        bh=GqbMRtCxZruoTwvbzdE4OugS/OPSg+DpVVIb/+sTqfY=;
        b=M9rAbe9HAZR3w4WPnF2BTEc0azwLcC8UaRZD+p6AeMgFMBK/EVCOvOV5xm7YP6LMeZew3g
        AQySiICDspmeS5zjEhlx78GWqlGUfgYjjKgJiUe/hocJ+2QP1QjaOhV2rmU5uo9XLbpAgS
        wgMw+DdvWiL20Vy+i0E6u+1AzNNIRTQ=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-531-mLjARqwuNTyi9lA--OwecQ-1; Fri, 27 Nov 2020 06:21:17 -0500
X-MC-Unique: mLjARqwuNTyi9lA--OwecQ-1
Received: from smtp.corp.redhat.com (int-mx05.intmail.prod.int.phx2.redhat.com
 [10.5.11.15])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id A3F551006C97;
        Fri, 27 Nov 2020 11:21:15 +0000 (UTC)
Received: from virtlab701.virt.lab.eng.bos.redhat.com
 (virtlab701.virt.lab.eng.bos.redhat.com [10.19.152.228])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 2D5E75D6D1;
        Fri, 27 Nov 2020 11:21:15 +0000 (UTC)
From: Paolo Bonzini <pbonzini@redhat.com>
To: linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Cc: seanjc@google.com, Filippo Sironi <sironi@amazon.de>,
        stable@vger.kernel.org
Subject: [PATCH 1/2] KVM: x86: handle !lapic_in_kernel case in
 kvm_cpu_*_extint
Date: Fri, 27 Nov 2020 06:21:13 -0500
Message-Id: <20201127112114.3219360-2-pbonzini@redhat.com>
In-Reply-To: <20201127112114.3219360-1-pbonzini@redhat.com>
References: <20201127112114.3219360-1-pbonzini@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.15
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Centralize handling of interrupts from the userspace APIC
in kvm_cpu_has_extint and kvm_cpu_get_extint, since
userspace APIC interrupts are handled more or less the
same as ExtINTs are with split irqchip.  This removes
duplicated code from kvm_cpu_has_injectable_intr and
kvm_cpu_has_interrupt, and makes the code more similar
between kvm_cpu_has_{extint,interrupt} on one side
and kvm_cpu_get_{extint,interrupt} on the other.

Cc: stable@vger.kernel.org
Signed-off-by: Paolo Bonzini <pbonzini@redhat.com>
Reviewed-by: Filippo Sironi <sironi@amazon.de>
---
 arch/x86/kvm/irq.c   | 85 ++++++++++++++++++--------------------------
 arch/x86/kvm/lapic.c |  2 +-
 2 files changed, 35 insertions(+), 52 deletions(-)

```
#### [kvm-unit-tests PATCH v2 1/7] s390x: Add test_bit to library
##### From: Janosch Frank <frankja@linux.ibm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Janosch Frank <frankja@linux.ibm.com>
X-Patchwork-Id: 11936289
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.8 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT autolearn=ham
	autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 70E8FC64E8A
	for <kvm@archiver.kernel.org>; Fri, 27 Nov 2020 13:09:17 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 3546E22248
	for <kvm@archiver.kernel.org>; Fri, 27 Nov 2020 13:09:17 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=ibm.com header.i=@ibm.com
 header.b="QV8EeyFG"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1730148AbgK0NJK (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Fri, 27 Nov 2020 08:09:10 -0500
Received: from mx0b-001b2d01.pphosted.com ([148.163.158.5]:65496 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S1730066AbgK0NJK (ORCPT
        <rfc822;kvm@vger.kernel.org>); Fri, 27 Nov 2020 08:09:10 -0500
Received: from pps.filterd (m0098420.ppops.net [127.0.0.1])
        by mx0b-001b2d01.pphosted.com (8.16.0.42/8.16.0.42) with SMTP id
 0ARCVY6M187796;
        Fri, 27 Nov 2020 08:09:09 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=ibm.com;
 h=from : to : cc : subject
 : date : message-id : in-reply-to : references : mime-version :
 content-transfer-encoding; s=pp1;
 bh=7PLA+wHiCZwtzEzklzXSMkA9+LdthVygMLRoFoRGCeM=;
 b=QV8EeyFGapY7OtJk/21AsjJKk5FBhveHtQ9f2KYGBRy4s/2iotjnMnZFSzF7sRHN5862
 FEBFSYZn8jj1P2D+UFwmOj5hgBFFlWFVvVo7S2+XOqlbUCqi8o5O7y8qIpA7WI+gPcdv
 Ix8Ews7RDitrC1gFG0xw8CMPsq5Mhg4bxb1jwrC8u/i8xtoNBelvc3iG/oxNWNjzvQnd
 BnpnV14WP6KYoGGQqFOovL7qv3MEv2QGtO2sSpRfQBvLu4Hw6IRbuG8UiGlvtkF4nRZq
 Ti8ZEaOKFWZpfuY8/9SYN/0lUFKf2r+TQGfJXAKJEOGPTgGCec2CRpNsN+DCZxugpVlZ Eg==
Received: from pps.reinject (localhost [127.0.0.1])
        by mx0b-001b2d01.pphosted.com with ESMTP id 352we6r3fm-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Fri, 27 Nov 2020 08:09:09 -0500
Received: from m0098420.ppops.net (m0098420.ppops.net [127.0.0.1])
        by pps.reinject (8.16.0.36/8.16.0.36) with SMTP id 0ARCVnHt189080;
        Fri, 27 Nov 2020 08:09:08 -0500
Received: from ppma03fra.de.ibm.com (6b.4a.5195.ip4.static.sl-reverse.com
 [149.81.74.107])
        by mx0b-001b2d01.pphosted.com with ESMTP id 352we6r3f3-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Fri, 27 Nov 2020 08:09:08 -0500
Received: from pps.filterd (ppma03fra.de.ibm.com [127.0.0.1])
        by ppma03fra.de.ibm.com (8.16.0.42/8.16.0.42) with SMTP id
 0ARCSREc024095;
        Fri, 27 Nov 2020 13:09:07 GMT
Received: from b06cxnps4074.portsmouth.uk.ibm.com
 (d06relay11.portsmouth.uk.ibm.com [9.149.109.196])
        by ppma03fra.de.ibm.com with ESMTP id 352jgsh05b-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Fri, 27 Nov 2020 13:09:06 +0000
Received: from d06av22.portsmouth.uk.ibm.com (d06av22.portsmouth.uk.ibm.com
 [9.149.105.58])
        by b06cxnps4074.portsmouth.uk.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id 0ARD6YlR58655066
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Fri, 27 Nov 2020 13:06:34 GMT
Received: from d06av22.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 0F3B54C071;
        Fri, 27 Nov 2020 13:06:34 +0000 (GMT)
Received: from d06av22.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 4B53C4C046;
        Fri, 27 Nov 2020 13:06:33 +0000 (GMT)
Received: from linux01.pok.stglabs.ibm.com (unknown [9.114.17.81])
        by d06av22.portsmouth.uk.ibm.com (Postfix) with ESMTP;
        Fri, 27 Nov 2020 13:06:33 +0000 (GMT)
From: Janosch Frank <frankja@linux.ibm.com>
To: kvm@vger.kernel.org
Cc: thuth@redhat.com, david@redhat.com, borntraeger@de.ibm.com,
        imbrenda@linux.ibm.com, cohuck@redhat.com,
        linux-s390@vger.kernel.org
Subject: [kvm-unit-tests PATCH v2 1/7] s390x: Add test_bit to library
Date: Fri, 27 Nov 2020 08:06:23 -0500
Message-Id: <20201127130629.120469-2-frankja@linux.ibm.com>
X-Mailer: git-send-email 2.25.1
In-Reply-To: <20201127130629.120469-1-frankja@linux.ibm.com>
References: <20201127130629.120469-1-frankja@linux.ibm.com>
MIME-Version: 1.0
X-TM-AS-GCONF: 00
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.312,18.0.737
 definitions=2020-11-27_05:2020-11-26,2020-11-27 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 priorityscore=1501
 adultscore=0 bulkscore=0 mlxlogscore=999 lowpriorityscore=0 malwarescore=0
 clxscore=1015 suspectscore=1 mlxscore=0 spamscore=0 phishscore=0
 impostorscore=0 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.12.0-2009150000 definitions=main-2011270076
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Query/feature bits are commonly tested via MSB bit numbers on
s390. Let's add test bit functions, so we don't need to copy code to
test query bits.

The test_bit code has been taken from the kernel since most s390x KVM unit
test developers are used to them.

Signed-off-by: Janosch Frank <frankja@linux.ibm.com>
Reviewed-by: Cornelia Huck <cohuck@redhat.com>
Reviewed-by: Thomas Huth <thuth@redhat.com>
---
 lib/s390x/asm/bitops.h   | 26 ++++++++++++++++++++++++++
 lib/s390x/asm/facility.h |  3 ++-
 2 files changed, 28 insertions(+), 1 deletion(-)

```
#### [PATCH v3] drivers/virt: vmgenid: add vm generation id driver
##### From: "Catangiu, Adrian Costin" <acatan@amazon.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 8bit
X-Patchwork-Submitter: "Catangiu, Adrian Costin" <acatan@amazon.com>
X-Patchwork-Id: 11937077
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-17.2 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_CR_TRAILER,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,
	URIBL_BLOCKED,USER_AGENT_SANE_1 autolearn=ham autolearn_force=no
 version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 92A58C3E8C5
	for <kvm@archiver.kernel.org>; Fri, 27 Nov 2020 18:26:51 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 485E221D7A
	for <kvm@archiver.kernel.org>; Fri, 27 Nov 2020 18:26:51 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=amazon.com header.i=@amazon.com
 header.b="VVFVzGNZ"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1731617AbgK0S0f (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Fri, 27 Nov 2020 13:26:35 -0500
Received: from smtp-fw-33001.amazon.com ([207.171.190.10]:24854 "EHLO
        smtp-fw-33001.amazon.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726250AbgK0S0f (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 27 Nov 2020 13:26:35 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
  d=amazon.com; i=@amazon.com; q=dns/txt; s=amazon201209;
  t=1606501590; x=1638037590;
  h=to:cc:references:from:subject:message-id:date:
   mime-version:in-reply-to:content-transfer-encoding;
  bh=ym1a40cA3sfFACqjWbKa8VG9le0R+UXnWig063o8dgU=;
  b=VVFVzGNZrrs2NPV/BhHpmpdZbnLovY4b4nmPbKdl8HwLAb89krfZXYQw
   l27Mi07q+fjulDoieV2mo7uC955gtojA7mA0RI++yVmdO3Gyrs6UwLf4c
   AapQmWUcd6qozbQKy6uiL7d4UqrYqcNe69Ze7VYmYa1HRFbKE49mdm4Yh
   U=;
X-IronPort-AV: E=Sophos;i="5.78,375,1599523200";
   d="scan'208";a="98545117"
Received: from sea32-co-svc-lb4-vlan3.sea.corp.amazon.com (HELO
 email-inbound-relay-2b-baacba05.us-west-2.amazon.com) ([10.47.23.38])
  by smtp-border-fw-out-33001.sea14.amazon.com with ESMTP;
 27 Nov 2020 18:26:23 +0000
Received: from EX13D08EUB004.ant.amazon.com
 (pdx1-ws-svc-p6-lb9-vlan2.pdx.amazon.com [10.236.137.194])
        by email-inbound-relay-2b-baacba05.us-west-2.amazon.com (Postfix) with
 ESMTPS id 7D6D9A1DD5;
        Fri, 27 Nov 2020 18:26:20 +0000 (UTC)
Received: from 4c32759f87cf.ant.amazon.com (10.43.162.53) by
 EX13D08EUB004.ant.amazon.com (10.43.166.158) with Microsoft SMTP Server (TLS)
 id 15.0.1497.2; Fri, 27 Nov 2020 18:26:06 +0000
To: Dmitry Safonov <0x7f454c46@gmail.com>,
        Alexander Graf <graf@amazon.de>
CC: Mike Rapoport <rppt@kernel.org>,
        Christian Borntraeger <borntraeger@de.ibm.com>,
        "Jason A. Donenfeld" <Jason@zx2c4.com>,
        Jann Horn <jannh@google.com>, Willy Tarreau <w@1wt.eu>,
        "MacCarthaigh, Colm" <colmmacc@amazon.com>,
        Andy Lutomirski <luto@kernel.org>,
        "Theodore Y. Ts'o" <tytso@mit.edu>,
        Eric Biggers <ebiggers@kernel.org>,
        "open list:DOCUMENTATION" <linux-doc@vger.kernel.org>,
        kernel list <linux-kernel@vger.kernel.org>,
        "Woodhouse, David" <dwmw@amazon.co.uk>,
        "bonzini@gnu.org" <bonzini@gnu.org>,
        "Singh, Balbir" <sblbir@amazon.com>,
        "Weiss, Radu" <raduweis@amazon.com>,
        "oridgar@gmail.com" <oridgar@gmail.com>,
        "ghammer@redhat.com" <ghammer@redhat.com>,
        Jonathan Corbet <corbet@lwn.net>,
        Greg Kroah-Hartman <gregkh@linuxfoundation.org>,
        "Michael S. Tsirkin" <mst@redhat.com>,
        Qemu Developers <qemu-devel@nongnu.org>,
        KVM list <kvm@vger.kernel.org>,
        Michal Hocko <mhocko@kernel.org>,
        "Rafael J. Wysocki" <rafael@kernel.org>,
        Pavel Machek <pavel@ucw.cz>,
        Linux API <linux-api@vger.kernel.org>,
        "mpe@ellerman.id.au" <mpe@ellerman.id.au>,
        linux-s390 <linux-s390@vger.kernel.org>,
        "areber@redhat.com" <areber@redhat.com>,
        Pavel Emelyanov <ovzxemul@gmail.com>,
        Andrey Vagin <avagin@gmail.com>,
        Pavel Tikhomirov <ptikhomirov@virtuozzo.com>,
        "gil@azul.com" <gil@azul.com>,
        "asmehra@redhat.com" <asmehra@redhat.com>,
        "dgunigun@redhat.com" <dgunigun@redhat.com>,
        "vijaysun@ca.ibm.com" <vijaysun@ca.ibm.com>,
        "Eric W. Biederman" <ebiederm@xmission.com>
References: <3E05451B-A9CD-4719-99D0-72750A304044@amazon.com>
 <300d4404-3efe-880e-ef30-692eabbff5f7@de.ibm.com>
 <da1a1fa7-a1de-d0e6-755b-dd587687765e@amazon.de>
 <20201119173800.GD8537@kernel.org>
 <1cdb6fac-0d50-3399-74a6-24c119ebbaa5@amazon.de>
 <106f56ca-49bc-7cad-480f-4b26656e90ce@gmail.com>
From: "Catangiu, Adrian Costin" <acatan@amazon.com>
Subject: [PATCH v3] drivers/virt: vmgenid: add vm generation id driver
Message-ID: <96625ce2-66c6-34b8-ef81-7c17c05b4c7a@amazon.com>
Date: Fri, 27 Nov 2020 20:26:02 +0200
User-Agent: Mozilla/5.0 (Macintosh; Intel Mac OS X 10.14; rv:78.0)
 Gecko/20100101 Thunderbird/78.4.3
MIME-Version: 1.0
In-Reply-To: <106f56ca-49bc-7cad-480f-4b26656e90ce@gmail.com>
Content-Language: en-US
X-Originating-IP: [10.43.162.53]
X-ClientProxiedBy: EX13d09UWA003.ant.amazon.com (10.43.160.227) To
 EX13D08EUB004.ant.amazon.com (10.43.166.158)
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

- Background

The VM Generation ID is a feature defined by Microsoft (paper:
http://go.microsoft.com/fwlink/?LinkId=260709) and supported by
multiple hypervisor vendors.

The feature is required in virtualized environments by apps that work
with local copies/caches of world-unique data such as random values,
uuids, monotonically increasing counters, etc.
Such apps can be negatively affected by VM snapshotting when the VM
is either cloned or returned to an earlier point in time.

The VM Generation ID is a simple concept meant to alleviate the issue
by providing a unique ID that changes each time the VM is restored
from a snapshot. The hw provided UUID value can be used to
differentiate between VMs or different generations of the same VM.

- Problem

The VM Generation ID is exposed through an ACPI device by multiple
hypervisor vendors but neither the vendors or upstream Linux have no
default driver for it leaving users to fend for themselves.

Furthermore, simply finding out about a VM generation change is only
the starting point of a process to renew internal states of possibly
multiple applications across the system. This process could benefit
from a driver that provides an interface through which orchestration
can be easily done.

- Solution

This patch is a driver that exposes a monotonic incremental Virtual
Machine Generation u32 counter via a char-dev FS interface. The FS
interface provides sync and async VmGen counter updates notifications.
It also provides VmGen counter retrieval and confirmation mechanisms.

The generation counter and the interface through which it is exposed
are available even when there is no acpi device present.

When the device is present, the hw provided UUID is not exposed to
userspace, it is internally used by the driver to keep accounting for
the exposed VmGen counter. The counter starts from zero when the
driver is initialized and monotonically increments every time the hw
UUID changes (the VM generation changes).
On each hw UUID change, the new hypervisor-provided UUID is also fed
to the kernel RNG.

If there is no acpi vmgenid device present, the generation changes are
not driven by hw vmgenid events but can be driven by software through
a dedicated driver ioctl.

This patch builds on top of Or Idgar <oridgar@gmail.com>'s proposal
https://lkml.org/lkml/2018/3/1/498

- Future improvements

Ideally we would want the driver to register itself based on devices'
_CID and not _HID, but unfortunately I couldn't find a way to do that.
The problem is that ACPI device matching is done by
'__acpi_match_device()' which exclusively looks at
'acpi_hardware_id *hwid'.

There is a path for platform devices to match on _CID when _HID is
'PRP0001' - but this is not the case for the Qemu vmgenid device.

Guidance and help here would be greatly appreciated.

Signed-off-by: Adrian Catangiu <acatan@amazon.com>
---

v1 -> v2:

  - expose to userspace a monotonically increasing u32 Vm Gen Counter
    instead of the hw VmGen UUID
  - since the hw/hypervisor-provided 128-bit UUID is not public
    anymore, add it to the kernel RNG as device randomness
  - insert driver page containing Vm Gen Counter in the user vma in
    the driver's mmap handler instead of using a fault handler
  - turn driver into a misc device driver to auto-create /dev/vmgenid
  - change ioctl arg to avoid leaking kernel structs to userspace
  - update documentation
  - various nits
  - rebase on top of linus latest

v2 -> v3:

  - separate the core driver logic and interface, from the ACPI device.
    The ACPI vmgenid device is now one possible backend.
  - fix issue when timeout=0 in VMGENID_WAIT_WATCHERS
  - add locking to avoid races between fs ops handlers and hw irq
    driven generation updates
  - change VMGENID_WAIT_WATCHERS ioctl so if the current caller is
    outdated or a generation change happens while waiting (thus making
    current caller outdated), the ioctl returns -EINTR to signal the
    user to handle event and retry. Fixes blocking on oneself.
  - add VMGENID_FORCE_GEN_UPDATE ioctl conditioned by
    CAP_CHECKPOINT_RESTORE capability, through which software can force
    generation bump.
---
 Documentation/virt/vmgenid.rst | 240 +++++++++++++++++++++++
 drivers/virt/Kconfig           |  17 ++
 drivers/virt/Makefile          |   1 +
 drivers/virt/vmgenid.c         | 435
+++++++++++++++++++++++++++++++++++++++++
 include/uapi/linux/vmgenid.h   |  14 ++
 5 files changed, 707 insertions(+)
 create mode 100644 Documentation/virt/vmgenid.rst
 create mode 100644 drivers/virt/vmgenid.c
 create mode 100644 include/uapi/linux/vmgenid.h

diff --git a/Documentation/virt/vmgenid.rst b/Documentation/virt/vmgenid.rst
new file mode 100644
index 0000000..b6a9f8d
--- /dev/null
+++ b/Documentation/virt/vmgenid.rst
@@ -0,0 +1,240 @@
+.. SPDX-License-Identifier: GPL-2.0
+
+============
+VMGENID
+============
+
+The VM Generation ID is a feature defined by Microsoft (paper:
+http://go.microsoft.com/fwlink/?LinkId=260709) and supported by
+multiple hypervisor vendors.
+
+The feature is required in virtualized environments by apps that work
+with local copies/caches of world-unique data such as random values,
+uuids, monotonically increasing counters, etc.
+Such apps can be negatively affected by VM snapshotting when the VM
+is either cloned or returned to an earlier point in time.
+
+The VM Generation ID is a simple concept meant to alleviate the issue
+by providing a unique ID that changes each time the VM is restored
+from a snapshot. The hw provided UUID value can be used to
+differentiate between VMs or different generations of the same VM.
+
+The VM Generation ID is exposed through an ACPI device by multiple
+hypervisor vendors. The driver for it lives at
+``drivers/virt/vmgenid.c``
+
+The ``vmgenid`` driver exposes a monotonic incremental Virtual
+Machine Generation u32 counter via a char-dev FS interface that
+provides sync and async VmGen counter updates notifications. It also
+provides VmGen counter retrieval and confirmation mechanisms.
+
+This counter and the interface through which it is exposed are
+available even when there is no acpi device present.
+
+When the device is present, the hw provided UUID is not exposed to
+userspace, it is internally used by the driver to keep accounting for
+the exposed VmGen counter. The counter starts from zero when the
+driver is initialized and monotonically increments every time the hw
+UUID changes (the VM generation changes).
+On each hw UUID change, the new UUID is also fed to the kernel RNG.
+
+If there is no acpi vmgenid device present, the generation changes are
+not driven by hw vmgenid events and thus should be driven by software
+through a dedicated driver ioctl.
+
+Driver interface:
+
+``open()``:
+  When the device is opened, a copy of the current Vm-Gen-Id (counter)
+  is associated with the open file descriptor. The driver now tracks
+  this file as an independent *watcher*. The driver tracks how many
+  watchers are aware of the latest Vm-Gen-Id counter and how many of
+  them are *outdated*; outdated being those that have lived through
+  a Vm-Gen-Id change but not yet confirmed the new generation counter.
+
+``read()``:
+  Read is meant to provide the *new* VM generation counter when a
+  generation change takes place. The read operation blocks until the
+  associated counter is no longer up to date - until HW vm gen id
+  changes - at which point the new counter is provided/returned.
+  Nonblocking ``read()`` uses ``EAGAIN`` to signal that there is no
+  *new* counter value available. The generation counter is considered
+  *new* for each open file descriptor that hasn't confirmed the new
+  value, following a generation change. Therefore, once a generation
+  change takes place, all ``read()`` calls will immediately return the
+  new generation counter and will continue to do so until the
+  new value is confirmed back to the driver through ``write()``.
+  Partial reads are not allowed - read buffer needs to be at least
+  ``sizeof(unsigned)`` in size.
+
+``write()``:
+  Write is used to confirm the up-to-date Vm Gen counter back to the
+  driver.
+  Following a VM generation change, all existing watchers are marked
+  as *outdated*. Each file descriptor will maintain the *outdated*
+  status until a ``write()`` confirms the up-to-date counter back to
+  the driver.
+  Partial writes are not allowed - write buffer should be exactly
+  ``sizeof(unsigned)`` in size.
+
+``poll()``:
+  Poll is implemented to allow polling for generation counter updates.
+  Such updates result in ``EPOLLIN`` polling status until the new
+  up-to-date counter is confirmed back to the driver through a
+  ``write()``.
+
+``ioctl()``:
+  The driver also adds support for tracking count of open file
+  descriptors that haven't acknowledged a generation counter update.
+  This is exposed through two IOCTLs:
+
+  - VMGENID_GET_OUTDATED_WATCHERS: immediately returns the number of
+    *outdated* watchers - number of file descriptors that were open
+    during a VM generation change, and which have not yet confirmed the
+    new generation counter.
+  - VMGENID_WAIT_WATCHERS: blocks until there are no more *outdated*
+    watchers, or if a ``timeout`` argument is provided, until the
+    timeout expires.
+    If the current caller is *outdated* or a generation change happens
+    while waiting (thus making current caller *outdated*), the ioctl
+    returns ``-EINTR`` to signal the user to handle event and retry.
+  - VMGENID_FORCE_GEN_UPDATE: forces a generation counter bump. Can only
+    be used by processes with CAP_CHECKPOINT_RESTORE or CAP_SYS_ADMIN
+    capabilities.
+
+``mmap()``:
+  The driver supports ``PROT_READ, MAP_SHARED`` mmaps of a single page
+  in size. The first 4 bytes of the mapped page will contain an
+  up-to-date copy of the VM generation counter.
+  The mapped memory can be used as a low-latency generation counter
+  probe mechanism in critical sections - see examples.
+
+``close()``:
+  Removes the file descriptor as a Vm generation counter watcher.
+
+Example application workflows
+-----------------------------
+
+1) Watchdog thread simplified example::
+
+    void watchdog_thread_handler(int *thread_active)
+    {
+        unsigned genid;
+        int fd = open("/dev/vmgenid", O_RDWR | O_CLOEXEC, S_IRUSR |
S_IWUSR);
+
+        do {
+            // read new gen ID - blocks until VM generation changes
+            read(fd, &genid, sizeof(genid));
+
+            // because of VM generation change, we need to rebuild world
+            reseed_app_env();
+
+            // confirm we're done handling gen ID update
+            write(fd, &genid, sizeof(genid));
+        } while (atomic_read(thread_active));
+
+        close(fd);
+    }
+
+2) ASYNC simplified example::
+
+    void handle_io_on_vmgenfd(int vmgenfd)
+    {
+        unsigned genid;
+
+        // read new gen ID - we need it to confirm we've handled update
+        read(fd, &genid, sizeof(genid));
+
+        // because of VM generation change, we need to rebuild world
+        reseed_app_env();
+
+        // confirm we're done handling the gen ID update
+        write(fd, &genid, sizeof(genid));
+    }
+
+    int main() {
+        int epfd, vmgenfd;
+        struct epoll_event ev;
+
+        epfd = epoll_create(EPOLL_QUEUE_LEN);
+
+        vmgenfd = open("/dev/vmgenid",
+                       O_RDWR | O_CLOEXEC | O_NONBLOCK,
+                       S_IRUSR | S_IWUSR);
+
+        // register vmgenid for polling
+        ev.events = EPOLLIN;
+        ev.data.fd = vmgenfd;
+        epoll_ctl(epfd, EPOLL_CTL_ADD, vmgenfd, &ev);
+
+        // register other parts of your app for polling
+        // ...
+
+        while (1) {
+            // wait for something to do...
+            int nfds = epoll_wait(epfd, events,
+                MAX_EPOLL_EVENTS_PER_RUN,
+                EPOLL_RUN_TIMEOUT);
+            if (nfds < 0) die("Error in epoll_wait!");
+
+            // for each ready fd
+            for(int i = 0; i < nfds; i++) {
+                int fd = events[i].data.fd;
+
+                if (fd == vmgenfd)
+                    handle_io_on_vmgenfd(vmgenfd);
+                else
+                    handle_some_other_part_of_the_app(fd);
+            }
+        }
+
+        return 0;
+    }
+
+3) Mapped memory polling simplified example::
+
+    /*
+     * app/library function that provides cached secrets
+     */
+    char * safe_cached_secret(app_data_t *app)
+    {
+        char *secret;
+        volatile unsigned *const genid_ptr = get_vmgenid_mapping(app);
+    again:
+        secret = __cached_secret(app);
+
+        if (unlikely(*genid_ptr != app->cached_genid)) {
+            // rebuild world then confirm the genid update (thru write)
+            rebuild_caches(app);
+
+            app->cached_genid = *genid_ptr;
+            ack_vmgenid_update(app);
+
+            goto again;
+        }
+
+        return secret;
+    }
+
+4) Orchestrator simplified example::
+
+    /*
+     * orchestrator - manages multiple apps and libraries used by a service
+     * and tries to make sure all sensitive components gracefully handle
+     * VM generation changes.
+     * Following function is called on detection of a VM generation change.
+     */
+    int handle_vmgen_update(int vmgen_fd, unsigned new_gen_id)
+    {
+        // pause until all components have handled event
+        pause_service();
+
+        // confirm *this* watcher as up-to-date
+        write(vmgen_fd, &new_gen_id, sizeof(unsigned));
+
+        // wait for all *others* for at most 5 seconds.
+        ioctl(vmgen_fd, VMGENID_WAIT_WATCHERS, 5000);
+
+        // all apps on the system have rebuilt worlds
+        resume_service();
+    }
```
