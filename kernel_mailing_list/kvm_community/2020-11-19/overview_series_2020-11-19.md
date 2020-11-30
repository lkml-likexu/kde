#### [RFC PATCH 1/2] KVM: X86: Add support for the emulation of DR6_BUS_LOCK bit
##### From: Chenyi Qiang <chenyi.qiang@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Chenyi Qiang <chenyi.qiang@intel.com>
X-Patchwork-Id: 11916901
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.7 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED,USER_AGENT_GIT
	autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 22364C6369E
	for <kvm@archiver.kernel.org>; Thu, 19 Nov 2020 09:27:53 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id CEA7B2468D
	for <kvm@archiver.kernel.org>; Thu, 19 Nov 2020 09:27:52 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726666AbgKSJ1e (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Thu, 19 Nov 2020 04:27:34 -0500
Received: from mga04.intel.com ([192.55.52.120]:20996 "EHLO mga04.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726574AbgKSJ1d (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 19 Nov 2020 04:27:33 -0500
IronPort-SDR: 
 UO349H9U/89KrqdZCWmxXiPW0OA8ziyPaTJDJiVhMkGlbIbxGxDAac6ZKH4V3g7WMK6GMZdNBd
 vMkiUE95ACkQ==
X-IronPort-AV: E=McAfee;i="6000,8403,9809"; a="168688341"
X-IronPort-AV: E=Sophos;i="5.77,490,1596524400";
   d="scan'208";a="168688341"
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from orsmga005.jf.intel.com ([10.7.209.41])
  by fmsmga104.fm.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 19 Nov 2020 01:27:32 -0800
IronPort-SDR: 
 wf30peE+SOF/QYcS/nygh5jnvy6VW04yMiCwl03jQ2sJRqF4AdbyNJI73lyRl5+xzgl5JAwYJM
 849+mdTgtu1A==
X-IronPort-AV: E=Sophos;i="5.77,490,1596524400";
   d="scan'208";a="544939808"
Received: from chenyi-pc.sh.intel.com ([10.239.159.72])
  by orsmga005-auth.jf.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 19 Nov 2020 01:27:29 -0800
From: Chenyi Qiang <chenyi.qiang@intel.com>
To: Paolo Bonzini <pbonzini@redhat.com>,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>,
        Xiaoyao Li <xiaoyao.li@intel.com>
Cc: kvm@vger.kernel.org, linux-kernel@vger.kernel.org
Subject: [RFC PATCH 1/2] KVM: X86: Add support for the emulation of
 DR6_BUS_LOCK bit
Date: Thu, 19 Nov 2020 17:29:56 +0800
Message-Id: <20201119092957.16940-2-chenyi.qiang@intel.com>
X-Mailer: git-send-email 2.17.1
In-Reply-To: <20201119092957.16940-1-chenyi.qiang@intel.com>
References: <20201119092957.16940-1-chenyi.qiang@intel.com>
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

To avoid breaking the CPUs without bus lock detection, activate the
DR6_BUS_LOCK bit (bit 11) conditionally in DR6_FIXED_1 bits.

The set/clear of DR6_BUS_LOCK is similar to the DR6_RTM in DR6
register. The processor clears DR6_BUS_LOCK when bus lock debug
exception is generated. (For all other #DB the processor sets this bit
to 1.) Software #DB handler should set this bit before returning to the
interrupted task.

For VM exit caused by debug exception, bit 11 of the exit qualification
is set to indicate that a bus lock debug exception condition was
detected. The VMM should emulate the exception by clearing bit 11 of the
guest DR6.

Co-developed-by: Xiaoyao Li <xiaoyao.li@intel.com>
Signed-off-by: Xiaoyao Li <xiaoyao.li@intel.com>
Signed-off-by: Chenyi Qiang <chenyi.qiang@intel.com>
---
 arch/x86/include/asm/kvm_host.h |  5 +++--
 arch/x86/kvm/emulate.c          |  2 +-
 arch/x86/kvm/svm/svm.c          |  6 +++---
 arch/x86/kvm/vmx/nested.c       |  2 +-
 arch/x86/kvm/vmx/vmx.c          |  6 ++++--
 arch/x86/kvm/x86.c              | 28 +++++++++++++++++-----------
 6 files changed, 29 insertions(+), 20 deletions(-)

```
#### [PATCH v6 01/17] drm/exynos: Stop using frame_vector helpers
##### From: Daniel Vetter <daniel.vetter@ffwll.ch>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 8bit
X-Patchwork-Submitter: Daniel Vetter <daniel.vetter@ffwll.ch>
X-Patchwork-Id: 11917669
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-18.7 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,
	INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED,
	USER_AGENT_GIT autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 69F36C64E7D
	for <kvm@archiver.kernel.org>; Thu, 19 Nov 2020 14:42:17 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 24994246E1
	for <kvm@archiver.kernel.org>; Thu, 19 Nov 2020 14:42:17 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=ffwll.ch header.i=@ffwll.ch
 header.b="DXhtVpSO"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728210AbgKSOl6 (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Thu, 19 Nov 2020 09:41:58 -0500
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:37398 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1727214AbgKSOl5 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 19 Nov 2020 09:41:57 -0500
Received: from mail-wr1-x444.google.com (mail-wr1-x444.google.com
 [IPv6:2a00:1450:4864:20::444])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 59031C061A49
        for <kvm@vger.kernel.org>; Thu, 19 Nov 2020 06:41:55 -0800 (PST)
Received: by mail-wr1-x444.google.com with SMTP id s8so6650764wrw.10
        for <kvm@vger.kernel.org>; Thu, 19 Nov 2020 06:41:55 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=ffwll.ch; s=google;
        h=from:to:cc:subject:date:message-id:in-reply-to:references
         :mime-version:content-transfer-encoding;
        bh=Fht1x4F+T6VzCgf1NaDBhBKtnXLiUuYYVlRneo30QNs=;
        b=DXhtVpSOWcpXdJK21rs4Fp0d4l9+i/Ct+0QiVH10n6yOR0X9JUB+xG9QSShL8w70GM
         mZMkMLfElwUq/INcoJ86TlvtNHxIwENjs79UhOpfl/9mHTexirmlYytroBBaZSYJMZwS
         jKkzeL8RzGYzXxoAeA9jzB4tQ6PU2bVwzvvOo=
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:in-reply-to
         :references:mime-version:content-transfer-encoding;
        bh=Fht1x4F+T6VzCgf1NaDBhBKtnXLiUuYYVlRneo30QNs=;
        b=HVzFIyibhb2eiAuEiSLWHAoxDWORUstXtB229Ha5c1PyW0gDm8R9Afi9oCQmzkoduM
         /L1jrxaRTYJakC6xvYC2+6RYaCJ2j4T9qv5DK70Q5Pah0eSyD0+4sT6GqreuMaySB6NZ
         A0T512eCO7GPfgFIgXkQbGJ6hBhLoaemVI6ZhXJM4fJ3rqAY+y9NwROfVvDi4d/HMHZ1
         0qu4sZVuVkjB/y7pM9fcxIN6c32spyyakxouUrAw1EUGD+FBxM3sZLIFbm71ijmJ5IqN
         EUaAZ7qoLuFZuoUSxC7h5/oqg5nx5/weZzLuIm077RZxWZptlQMnYpdnpt9L/nT5dxm0
         d1yw==
X-Gm-Message-State: AOAM530ie2xhWg6jXUyy2yeA0TFdpDtVZe11Zaxq07lOCAAMx0rAq5J2
        8HhJJaX09+2Htw7NeHWMlewUgQ==
X-Google-Smtp-Source: 
 ABdhPJxiB+ezDWRaWhzc+QskvK1DMsG1qeGQGBIpdFBX6dPCu/5SVpmVjX6WvoZgtP8NAV6pSGqFHQ==
X-Received: by 2002:adf:f88c:: with SMTP id
 u12mr10421833wrp.209.1605796914108;
        Thu, 19 Nov 2020 06:41:54 -0800 (PST)
Received: from phenom.ffwll.local ([2a02:168:57f4:0:efd0:b9e5:5ae6:c2fa])
        by smtp.gmail.com with ESMTPSA id x63sm51292wmb.48.2020.11.19.06.41.52
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Thu, 19 Nov 2020 06:41:53 -0800 (PST)
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
Subject: [PATCH v6 01/17] drm/exynos: Stop using frame_vector helpers
Date: Thu, 19 Nov 2020 15:41:30 +0100
Message-Id: <20201119144146.1045202-2-daniel.vetter@ffwll.ch>
X-Mailer: git-send-email 2.29.2
In-Reply-To: <20201119144146.1045202-1-daniel.vetter@ffwll.ch>
References: <20201119144146.1045202-1-daniel.vetter@ffwll.ch>
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
#### [PATCH] MAINTAINERS: Update email address for Sean Christopherson
##### From: Sean Christopherson <sean.kvm@gmail.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 8bit
X-Patchwork-Submitter: Sean Christopherson <sean.kvm@gmail.com>
X-Patchwork-Id: 11918793
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-15.7 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,DKIM_VALID_AU,FREEMAIL_FORGED_FROMDOMAIN,FREEMAIL_FROM,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED,USER_AGENT_GIT
	autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 49B98C63697
	for <kvm@archiver.kernel.org>; Thu, 19 Nov 2020 18:37:33 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id D621922259
	for <kvm@archiver.kernel.org>; Thu, 19 Nov 2020 18:37:32 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=gmail.com header.i=@gmail.com
 header.b="Lyj6PPZ+"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729036AbgKSShL (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Thu, 19 Nov 2020 13:37:11 -0500
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:45798 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1728908AbgKSShL (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 19 Nov 2020 13:37:11 -0500
Received: from mail-pf1-x443.google.com (mail-pf1-x443.google.com
 [IPv6:2607:f8b0:4864:20::443])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 0B606C0613CF;
        Thu, 19 Nov 2020 10:37:11 -0800 (PST)
Received: by mail-pf1-x443.google.com with SMTP id a18so5325732pfl.3;
        Thu, 19 Nov 2020 10:37:11 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=from:to:cc:subject:date:message-id:reply-to:mime-version
         :content-transfer-encoding;
        bh=12as8FlhjKsw6Yc9OgHJwzJoKwzpusnZd9yPEeWisJQ=;
        b=Lyj6PPZ+l5+1QVqnlOl2S2tCrsnUcYjCnxX2HiO+FVlduBUJMlQ/c7bFIXhkGAgJa3
         FVvgvtizoEGxXXOfX89ypoMYaqah529fTGIYPkOj+Uxihi+9WcthTxqc1s6JvRd7vpo/
         rSx/obTYb3JtpUgcU5YtILoSpeOrOMESpxxo2Ldu6lptGGuVNoYxOhtbDmxMyLf8t6PR
         kx6PVmofW6Oc6+Rj648br0+b7uEkB90xdZitlR60665OinNi+hXrvCPKVaulHTqISSlv
         m7xluoxpDGV3XihfPOcfN5u05PadGe24hLteDQz0+agmi5FLiWdOb5nlMDlEm8Gh9Igg
         JY/w==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:reply-to
         :mime-version:content-transfer-encoding;
        bh=12as8FlhjKsw6Yc9OgHJwzJoKwzpusnZd9yPEeWisJQ=;
        b=pGP6Gm9VN2UBzfQhmOt7TQdaXwtg0dICn2hoea1h1czOiGpxp6LtLbFHmsU2z0XbMO
         BD3wUlbdqrJoB5q7QzclW1k6InrhMbEpDlOKdkHYtdqXc6r1dzSy9gMdy22oMSI7LidY
         RTk779V9QY00eJiTBaNirbgiuF6xzjc3u/tStlksW6koaLE0RZ1g3EdV8Jl/Rzlf/AcN
         oywXM1ezn3zbVsNGx8efmm/aqwUxwGxLHYugJKjwo7qn164jljHg53PsLQQx4e7M1lrm
         pYDdTwEC1puZucVYjr5+k6SEJOjwOaW2GZzBmcI1mBeH39F5uHz1LQnpGQI0hnP5eotW
         aD+g==
X-Gm-Message-State: AOAM531lbqr1CtlMXaQy3n4v0c619vn7TE+khVlGRtZjoHjjupaHt5eA
        gJ0PKSKOr0Pk2zGYPwWWGak=
X-Google-Smtp-Source: 
 ABdhPJw/X81bu2htCXilelR2XkX2DvhC/1T2NPfXTlJav8EixSzp7vT8vcqh2eogM3F80vCyd5iQxg==
X-Received: by 2002:a17:90a:b904:: with SMTP id
 p4mr5488997pjr.81.1605811030710;
        Thu, 19 Nov 2020 10:37:10 -0800 (PST)
Received: from seanjc-glaptop.roam.corp.google.com
 (c-71-238-67-106.hsd1.or.comcast.net. [71.238.67.106])
        by smtp.gmail.com with ESMTPSA id b3sm525758pfd.66.2020.11.19.10.37.09
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Thu, 19 Nov 2020 10:37:10 -0800 (PST)
From: Sean Christopherson <sean.kvm@gmail.com>
To: Paolo Bonzini <pbonzini@redhat.com>
Cc: linux-kernel@vger.kernel.org, Thomas Gleixner <tglx@linutronix.de>,
        Borislav Petkov <bp@alien8.de>,
        Jarkko Sakkinen <jarkko@kernel.org>,
        Dave Hansen <dave.hansen@linux.intel.com>,
        Andy Lutomirski <luto@kernel.org>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>, kvm@vger.kernel.org,
        Sean Christopherson <seanjc@google.com>
Subject: [PATCH] MAINTAINERS: Update email address for Sean Christopherson
Date: Thu, 19 Nov 2020 10:37:07 -0800
Message-Id: <20201119183707.291864-1-sean.kvm@gmail.com>
X-Mailer: git-send-email 2.29.2.299.gdc1121823c-goog
Reply-To: Sean Christopherson <seanjc@google.com>
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Sean Christopherson <seanjc@google.com>

Update my email address to one provided by my new benefactor.

Cc: Thomas Gleixner <tglx@linutronix.de>
Cc: Borislav Petkov <bp@alien8.de>
Cc: Jarkko Sakkinen <jarkko@kernel.org>
Cc: Dave Hansen <dave.hansen@linux.intel.com>
Cc: Andy Lutomirski <luto@kernel.org>
Cc: Vitaly Kuznetsov <vkuznets@redhat.com>
Cc: Wanpeng Li <wanpengli@tencent.com>
Cc: Jim Mattson <jmattson@google.com>
Cc: Joerg Roedel <joro@8bytes.org>
Cc: kvm@vger.kernel.org
Signed-off-by: Sean Christopherson <seanjc@google.com>
---
Resorted to sending this via a private dummy account as getting my corp
email to play nice with git-sendemail has been further delayed, and I
assume y'all are tired of getting bounces.

 .mailmap    | 1 +
 MAINTAINERS | 2 +-
 2 files changed, 2 insertions(+), 1 deletion(-)

```
#### [PATCH] samples: vfio-mdev: fix return value of error branch in mdpy_fb_probe()
##### From: Qinglang Miao <miaoqinglang@huawei.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Qinglang Miao <miaoqinglang@huawei.com>
X-Patchwork-Id: 11916581
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.7 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED,USER_AGENT_GIT
	autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id ED727C6379D
	for <kvm@archiver.kernel.org>; Thu, 19 Nov 2020 07:04:30 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id ADFF9246B8
	for <kvm@archiver.kernel.org>; Thu, 19 Nov 2020 07:04:30 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726145AbgKSHEJ (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Thu, 19 Nov 2020 02:04:09 -0500
Received: from szxga05-in.huawei.com ([45.249.212.191]:8115 "EHLO
        szxga05-in.huawei.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726117AbgKSHEI (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 19 Nov 2020 02:04:08 -0500
Received: from DGGEMS414-HUB.china.huawei.com (unknown [172.30.72.59])
        by szxga05-in.huawei.com (SkyGuard) with ESMTP id 4Cc9dG4jk7zLnZL;
        Thu, 19 Nov 2020 15:03:46 +0800 (CST)
Received: from localhost.localdomain.localdomain (10.175.113.25) by
 DGGEMS414-HUB.china.huawei.com (10.3.19.214) with Microsoft SMTP Server id
 14.3.487.0; Thu, 19 Nov 2020 15:04:00 +0800
From: Qinglang Miao <miaoqinglang@huawei.com>
To: Kirti Wankhede <kwankhede@nvidia.com>
CC: <kvm@vger.kernel.org>, <linux-kernel@vger.kernel.org>,
        Qinglang Miao <miaoqinglang@huawei.com>
Subject: [PATCH] samples: vfio-mdev: fix return value of error branch in
 mdpy_fb_probe()
Date: Thu, 19 Nov 2020 15:08:43 +0800
Message-ID: <20201119070843.1074-1-miaoqinglang@huawei.com>
X-Mailer: git-send-email 2.20.1
MIME-Version: 1.0
X-Originating-IP: [10.175.113.25]
X-CFilter-Loop: Reflected
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

pci_release_regions() should be called in these error branches, so
I set ret and use goto err_release_regions intead of simply return
-EINVAL.

Fixes: cacade1946a4 ("sample: vfio mdev display - guest driver")
Reported-by: Hulk Robot <hulkci@huawei.com>
Signed-off-by: Qinglang Miao <miaoqinglang@huawei.com>
---
 samples/vfio-mdev/mdpy-fb.c | 9 ++++++---
 1 file changed, 6 insertions(+), 3 deletions(-)

```
#### [PATCH v2 01/22] x86/fpu/xstate: Modify area init helper prototypes to access all the possible areas
##### From: "Chang S. Bae" <chang.seok.bae@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: "Chang S. Bae" <chang.seok.bae@intel.com>
X-Patchwork-Id: 11919221
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.7 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED,USER_AGENT_GIT
	autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id BC27FC388F9
	for <kvm@archiver.kernel.org>; Thu, 19 Nov 2020 23:38:11 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 781C5208FE
	for <kvm@archiver.kernel.org>; Thu, 19 Nov 2020 23:38:11 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726784AbgKSXhB (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Thu, 19 Nov 2020 18:37:01 -0500
Received: from mga03.intel.com ([134.134.136.65]:10765 "EHLO mga03.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726494AbgKSXhB (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 19 Nov 2020 18:37:01 -0500
IronPort-SDR: 
 WuOZs6RvB5nnMBhLJWpTObQQ3pgoVUhRuwrG6VAO/Z+hc6sO2kuvfLY9iYQ6Nr1DiplOXmQULC
 v+uhdXckqVnA==
X-IronPort-AV: E=McAfee;i="6000,8403,9810"; a="171481778"
X-IronPort-AV: E=Sophos;i="5.78,354,1599548400";
   d="scan'208";a="171481778"
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from fmsmga001.fm.intel.com ([10.253.24.23])
  by orsmga103.jf.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 19 Nov 2020 15:36:59 -0800
IronPort-SDR: 
 ESl+b9rggjpkQNWq+chDwRJjrviOXvUCj4KHSlE2lP/WXa2MnbTgBp2mB3BP0DEAu6vcrN7HaZ
 z+POcxQOzhuA==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.78,354,1599548400";
   d="scan'208";a="431392184"
Received: from chang-linux-3.sc.intel.com ([172.25.66.175])
  by fmsmga001.fm.intel.com with ESMTP; 19 Nov 2020 15:36:59 -0800
From: "Chang S. Bae" <chang.seok.bae@intel.com>
To: tglx@linutronix.de, mingo@kernel.org, bp@suse.de, luto@kernel.org,
        x86@kernel.org
Cc: len.brown@intel.com, dave.hansen@intel.com, jing2.liu@intel.com,
        ravi.v.shankar@intel.com, linux-kernel@vger.kernel.org,
        chang.seok.bae@intel.com, kvm@vger.kernel.org
Subject: [PATCH v2 01/22] x86/fpu/xstate: Modify area init helper prototypes
 to access all the possible areas
Date: Thu, 19 Nov 2020 15:32:36 -0800
Message-Id: <20201119233257.2939-2-chang.seok.bae@intel.com>
X-Mailer: git-send-email 2.17.1
In-Reply-To: <20201119233257.2939-1-chang.seok.bae@intel.com>
References: <20201119233257.2939-1-chang.seok.bae@intel.com>
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The xstate infrastructure is not flexible to support dynamic areas in
task->fpu. Change the fpstate_init() prototype to access task->fpu
directly. It treats a null pointer as indicating init_fpstate, as this
initial data does not belong to any task. For the compacted format,
fpstate_init_xstate() now accepts the state component bitmap to configure
XCOMP_BV.

No functional change.

Signed-off-by: Chang S. Bae <chang.seok.bae@intel.com>
Reviewed-by: Len Brown <len.brown@intel.com>
Cc: x86@kernel.org
Cc: linux-kernel@vger.kernel.org
Cc: kvm@vger.kernel.org
---
 arch/x86/include/asm/fpu/internal.h |  6 +++---
 arch/x86/kernel/fpu/core.c          | 14 +++++++++++---
 arch/x86/kernel/fpu/init.c          |  2 +-
 arch/x86/kernel/fpu/regset.c        |  2 +-
 arch/x86/kernel/fpu/xstate.c        |  3 +--
 arch/x86/kvm/x86.c                  |  2 +-
 6 files changed, 18 insertions(+), 11 deletions(-)

```
#### [PATCH] vfio iommu type1: Bypass the vma permission check in vfio_pin_pages_remote()
##### From: Jia He <justin.he@arm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Justin He <justin.he@arm.com>
X-Patchwork-Id: 11917591
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-21.7 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,MENTIONS_GIT_HOSTING,SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED,
	USER_AGENT_GIT autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id E3286C63697
	for <kvm@archiver.kernel.org>; Thu, 19 Nov 2020 14:28:17 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 9954C208D5
	for <kvm@archiver.kernel.org>; Thu, 19 Nov 2020 14:28:17 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727850AbgKSO1y (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Thu, 19 Nov 2020 09:27:54 -0500
Received: from foss.arm.com ([217.140.110.172]:58922 "EHLO foss.arm.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1727809AbgKSO1y (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 19 Nov 2020 09:27:54 -0500
Received: from usa-sjc-imap-foss1.foss.arm.com (unknown [10.121.207.14])
        by usa-sjc-mx-foss1.foss.arm.com (Postfix) with ESMTP id 7555D1042;
        Thu, 19 Nov 2020 06:27:53 -0800 (PST)
Received: from entos-ampere-02.shanghai.arm.com
 (entos-ampere-02.shanghai.arm.com [10.169.214.110])
        by usa-sjc-imap-foss1.foss.arm.com (Postfix) with ESMTPA id
 7E36E3F719;
        Thu, 19 Nov 2020 06:27:51 -0800 (PST)
From: Jia He <justin.he@arm.com>
To: Alex Williamson <alex.williamson@redhat.com>,
        Cornelia Huck <cohuck@redhat.com>
Cc: kvm@vger.kernel.org, linux-kernel@vger.kernel.org,
        Jia He <justin.he@arm.com>
Subject: [PATCH] vfio iommu type1: Bypass the vma permission check in
 vfio_pin_pages_remote()
Date: Thu, 19 Nov 2020 22:27:37 +0800
Message-Id: <20201119142737.17574-1-justin.he@arm.com>
X-Mailer: git-send-email 2.17.1
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The permission of vfio iommu is different and incompatible with vma
permission. If the iotlb->perm is IOMMU_NONE (e.g. qemu side), qemu will
simply call unmap ioctl() instead of mapping. Hence vfio_dma_map() can't
map a dma region with NONE permission.

This corner case will be exposed in coming virtio_fs cache_size
commit [1]
 - mmap(NULL, size, PROT_NONE, MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);
   memory_region_init_ram_ptr()
 - re-mmap the above area with read/write authority.
 - vfio_dma_map() will be invoked when vfio device is hotplug added.

qemu:
vfio_listener_region_add()
	vfio_dma_map(..., readonly=false)
		map.flags is set to VFIO_DMA_MAP_FLAG_READ|VFIO_..._WRITE
		ioctl(VFIO_IOMMU_MAP_DMA)

kernel:
vfio_dma_do_map()
	vfio_pin_map_dma()
		vfio_pin_pages_remote()
			vaddr_get_pfn()
			...
				check_vma_flags() failed! because
				vm_flags hasn't VM_WRITE && gup_flags
				has FOLL_WRITE

It will report error in qemu log when hotplug adding(vfio) a nvme disk
to qemu guest on an Ampere EMAG server:
"VFIO_MAP_DMA failed: Bad address"

[1] https://gitlab.com/virtio-fs/qemu/-/blob/virtio-fs-dev/hw/virtio/vhost-user-fs.c#L502

Signed-off-by: Jia He <justin.he@arm.com>
---
 drivers/vfio/vfio_iommu_type1.c | 3 ++-
 1 file changed, 2 insertions(+), 1 deletion(-)

```
