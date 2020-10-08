#### [PATCH 1/5] x86/apic: Fix x2apic enablement without interrupt remapping
##### From: David Woodhouse <dwmw2@infradead.org>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: David Woodhouse <dwmw2@infradead.org>
X-Patchwork-Id: 11820541
Return-Path: <SRS0=rZqs=DO=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id DF932618
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed,  7 Oct 2020 12:21:07 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id BB1A02080A
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed,  7 Oct 2020 12:21:07 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=infradead.org header.i=@infradead.org
 header.b="u6zdo+KS"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728241AbgJGMU5 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 7 Oct 2020 08:20:57 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:39908 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1728198AbgJGMUu (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 7 Oct 2020 08:20:50 -0400
Received: from casper.infradead.org (casper.infradead.org
 [IPv6:2001:8b0:10b:1236::1])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id A9721C0613D4;
        Wed,  7 Oct 2020 05:20:49 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; q=dns/txt; c=relaxed/relaxed;
        d=infradead.org; s=casper.20170209;
 h=Sender:Content-Transfer-Encoding:
        MIME-Version:References:In-Reply-To:Message-Id:Date:Subject:Cc:To:From:
        Reply-To:Content-Type:Content-ID:Content-Description;
        bh=ZXCcrkFTyUnNhhIep8R+pz+tWqLs43q047DOUyhJ1Lk=;
 b=u6zdo+KSrb8nioH8uD2ma6xubX
        ucCpTZ8fjTVYNb/uNFIraAjwnro36cD7WdFngAmM3QGfJswDHZgvdncjP13onk5od47Bg+xVkX+BR
        UrgaO9gTWS/kS0TXNbobGMw5uXzsmhth/win1kMX5iOKd4L8KTjBEOEONKlL23Dm8nx59qD6Tv80g
        wpv113VU0ySeBHPE4BQ0XQ4KTgPgB6sT9B5FOwg5soguLjadPRHhjDgkGKVPXjdqoQbu48EE88SwP
        M1I19mjUdjw86dS113KnZju+DDz9HteGvAF463iYDSpqFTIzDJePCp5e4FITuQlKKR7uCgcLUCqdS
        y+W7ei/A==;
Received: from i7.infradead.org ([2001:8b0:10b:1:21e:67ff:fecb:7a92])
        by casper.infradead.org with esmtpsa (Exim 4.92.3 #3 (Red Hat Linux))
        id 1kQ8R5-0002Za-0y; Wed, 07 Oct 2020 12:20:47 +0000
Received: from dwoodhou by i7.infradead.org with local (Exim 4.93 #3 (Red Hat
 Linux))
        id 1kQ8R4-004fhe-HK; Wed, 07 Oct 2020 13:20:46 +0100
From: David Woodhouse <dwmw2@infradead.org>
To: x86@kernel.org
Cc: kvm <kvm@vger.kernel.org>, Thomas Gleixner <tglx@linutronix.de>,
        Paolo Bonzini <pbonzini@redhat.com>,
        linux-kernel <linux-kernel@vger.kernel.org>
Subject: [PATCH 1/5] x86/apic: Fix x2apic enablement without interrupt
 remapping
Date: Wed,  7 Oct 2020 13:20:42 +0100
Message-Id: <20201007122046.1113577-1-dwmw2@infradead.org>
X-Mailer: git-send-email 2.26.2
In-Reply-To: <803bb6b2212e65c568c84ff6882c2aa8a0ee03d5.camel@infradead.org>
References: <803bb6b2212e65c568c84ff6882c2aa8a0ee03d5.camel@infradead.org>
MIME-Version: 1.0
Sender: David Woodhouse <dwmw2@infradead.org>
X-SRS-Rewrite: SMTP reverse-path rewritten from <dwmw2@infradead.org> by
 casper.infradead.org. See http://www.infradead.org/rpr.html
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: David Woodhouse <dwmw@amazon.co.uk>

Currently, Linux as a hypervisor guest will enable x2apic only if there
are no CPUs present at boot time with an APIC ID above 255.

Hotplugging a CPU later with a higher APIC ID would result in a CPU
which cannot be targeted by external interrupts.

Add a filter in x2apic_apic_id_valid() which can be used to prevent
such CPUs from coming online, and allow x2apic to be enabled even if
they are present at boot time.

Fixes: ce69a784504 ("x86/apic: Enable x2APIC without interrupt remapping under KVM")
Signed-off-by: David Woodhouse <dwmw@amazon.co.uk>
---
 arch/x86/include/asm/apic.h        |  1 +
 arch/x86/kernel/apic/apic.c        | 14 ++++++++------
 arch/x86/kernel/apic/x2apic_phys.c |  9 +++++++++
 3 files changed, 18 insertions(+), 6 deletions(-)

```
#### [PATCH 01/13] drm/exynos: Stop using frame_vector helpers
##### From: Daniel Vetter <daniel.vetter@ffwll.ch>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 8bit
X-Patchwork-Submitter: Daniel Vetter <daniel.vetter@ffwll.ch>
X-Patchwork-Id: 11821209
Return-Path: <SRS0=rZqs=DO=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 6A89416C1
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed,  7 Oct 2020 16:46:15 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 41BC7215A4
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed,  7 Oct 2020 16:46:15 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=ffwll.ch header.i=@ffwll.ch
 header.b="iUxdpH9N"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727967AbgJGQqO (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 7 Oct 2020 12:46:14 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:52676 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1727903AbgJGQoh (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 7 Oct 2020 12:44:37 -0400
Received: from mail-wr1-x443.google.com (mail-wr1-x443.google.com
 [IPv6:2a00:1450:4864:20::443])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 8AE14C0613D2
        for <kvm@vger.kernel.org>; Wed,  7 Oct 2020 09:44:35 -0700 (PDT)
Received: by mail-wr1-x443.google.com with SMTP id j2so2980100wrx.7
        for <kvm@vger.kernel.org>; Wed, 07 Oct 2020 09:44:35 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=ffwll.ch; s=google;
        h=from:to:cc:subject:date:message-id:in-reply-to:references
         :mime-version:content-transfer-encoding;
        bh=AFbnT6+SQGOiYta6x0EmgGtFd4kjDjzMh837kXuim+8=;
        b=iUxdpH9NkrHO6H2sScw0dh1e+Tmrekq0lVn98gw/qps7+OgNiwwDWhafCTLofVhpUK
         /8kAvXp3kZ9Y0BGf4zlr0+Qb8yAKAV+Y80tyd0gxvJYfy/+pq/9bAPEuqS8R73VN5I/h
         UBWHCd03qVbZdlTB8hwjb9NuAdj+PLczeWQ5A=
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:in-reply-to
         :references:mime-version:content-transfer-encoding;
        bh=AFbnT6+SQGOiYta6x0EmgGtFd4kjDjzMh837kXuim+8=;
        b=LGKEznjOxgdck6DI6j5iut+Ti4lb1Svf1ZVt8gK8ioFryu7i/IuJyF5qxkSjLXdTeO
         qTx//1ayE/8ZAVEQdBkf+JxbL1ehoz8gX90fulZaj/TqxTMaSJfVhDiU34BgS6mXWUfR
         y4Bz5KtSkIH7JmAZQH3x/uNCQmcOu503dSwr3K6Z7fHjhm9hDUHqt8Vyn+HuJcppu1YQ
         Xf7Cn30VAubecd73Pkh0WuUttqPN2Ieq118+mXxnu+jcR7d1IYdsifAnjNs/lk637hfV
         iXu+Z+pY8c8aQMHeIA7kes9vasxVE8DFJRpla+PVHoJBb19Zvopq6CYvbLcYtXPF5iMz
         93IA==
X-Gm-Message-State: AOAM53347oJuUIbuQlo0QFJW0Hh2rhDtw6UP3QM/kF2diNpAuHZuamPI
        jlrChCLT3GrihJGjhMdYJjz1zg==
X-Google-Smtp-Source: 
 ABdhPJy5yBqszi+SQ3uxDFqYhfsjh+CWfY3vUKkTP4+ZFOvVBEvqPfIS3cscPbFU0YasWWmhFVcF8A==
X-Received: by 2002:adf:dc47:: with SMTP id m7mr4571340wrj.100.1602089074251;
        Wed, 07 Oct 2020 09:44:34 -0700 (PDT)
Received: from phenom.ffwll.local ([2a02:168:57f4:0:efd0:b9e5:5ae6:c2fa])
        by smtp.gmail.com with ESMTPSA id
 z191sm3332280wme.40.2020.10.07.09.44.32
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Wed, 07 Oct 2020 09:44:33 -0700 (PDT)
From: Daniel Vetter <daniel.vetter@ffwll.ch>
To: DRI Development <dri-devel@lists.freedesktop.org>,
        LKML <linux-kernel@vger.kernel.org>
Cc: kvm@vger.kernel.org, linux-mm@kvack.org,
 linux-arm-kernel@lists.infradead.org, linux-samsung-soc@vger.kernel.org,
 linux-media@vger.kernel.org, linux-s390@vger.kernel.org,
 Daniel Vetter <daniel.vetter@ffwll.ch>,
 Daniel Vetter <daniel.vetter@intel.com>, Jason Gunthorpe <jgg@ziepe.ca>,
 Inki Dae <inki.dae@samsung.com>, Joonyoung Shim <jy0922.shim@samsung.com>,
 Seung-Woo Kim <sw0312.kim@samsung.com>,
 Kyungmin Park <kyungmin.park@samsung.com>, Kukjin Kim <kgene@kernel.org>,
 Krzysztof Kozlowski <krzk@kernel.org>,
 Andrew Morton <akpm@linux-foundation.org>,
 John Hubbard <jhubbard@nvidia.com>,
 =?utf-8?b?SsOpcsO0bWUgR2xpc3Nl?= <jglisse@redhat.com>,
 Jan Kara <jack@suse.cz>, Dan Williams <dan.j.williams@intel.com>
Subject: [PATCH 01/13] drm/exynos: Stop using frame_vector helpers
Date: Wed,  7 Oct 2020 18:44:14 +0200
Message-Id: <20201007164426.1812530-2-daniel.vetter@ffwll.ch>
X-Mailer: git-send-email 2.28.0
In-Reply-To: <20201007164426.1812530-1-daniel.vetter@ffwll.ch>
References: <20201007164426.1812530-1-daniel.vetter@ffwll.ch>
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

All we need are a pages array, pin_user_pages_fast can give us that
directly. Plus this avoids the entire raw pfn side of get_vaddr_frames.

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
---
 drivers/gpu/drm/exynos/Kconfig          |  1 -
 drivers/gpu/drm/exynos/exynos_drm_g2d.c | 48 ++++++++++++-------------
 2 files changed, 22 insertions(+), 27 deletions(-)

```
#### [PATCH v14 01/14] KVM: Documentation: Update entry for KVM_X86_SET_MSR_FILTER
##### From: Peter Xu <peterx@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Peter Xu <peterx@redhat.com>
X-Patchwork-Id: 11821745
Return-Path: <SRS0=rZqs=DO=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 8762214D5
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed,  7 Oct 2020 20:53:50 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 689A32087D
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed,  7 Oct 2020 20:53:50 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="RW79OtBB"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728300AbgJGUxt (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 7 Oct 2020 16:53:49 -0400
Received: from us-smtp-delivery-124.mimecast.com ([63.128.21.124]:23205 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1728275AbgJGUxt (ORCPT
        <rfc822;kvm@vger.kernel.org>); Wed, 7 Oct 2020 16:53:49 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1602104028;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding:
         in-reply-to:in-reply-to:references:references;
        bh=kX1VG8a6zkuD/3E46MJcm8aBltfxr0Y3fuQzYvb2RnM=;
        b=RW79OtBBgNLIh8nFY2B1yJ9ZrdyaSOQwcmgPRncM/uNyHlqQ6gEyHrB9eX3FzJydwIOlD1
        5m6JCGkjTBJYOVTAlEMqRgDNlxdXcC1lIVbSImzBPv+FNfcgmHp4iF6BWUI7u9eUPtTxIz
        L81nuTw3n5KNK8uL1BXlWi9Vd1a1uT8=
Received: from mail-qv1-f70.google.com (mail-qv1-f70.google.com
 [209.85.219.70]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-572-m-0XymHlPRiEJBjJP_Wazg-1; Wed, 07 Oct 2020 16:53:46 -0400
X-MC-Unique: m-0XymHlPRiEJBjJP_Wazg-1
Received: by mail-qv1-f70.google.com with SMTP id 99so2218992qva.1
        for <kvm@vger.kernel.org>; Wed, 07 Oct 2020 13:53:46 -0700 (PDT)
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:in-reply-to
         :references:mime-version:content-transfer-encoding;
        bh=kX1VG8a6zkuD/3E46MJcm8aBltfxr0Y3fuQzYvb2RnM=;
        b=Cq3oArqF2TF2jsXnMWyDk3yPyE6XpnaSE4UmiBHTRwYZ2CopVklHrJCD5SPU7f9EUH
         G8UuynkdOyzne3szXVqUc595nQ5sxcETcog6qla06zf6mcRMI1FCBf34vG3ggoCkSrWk
         IWQBGMbDbQ7XEusWPTrOvi9DdnTgQdLIz/MvgJ00HzqcDmQud/CeUN0I3j68VCbQqTWE
         L+b63JDJ/u1Exu1BaMepIvA9V5SAZwCSqlMbXNWFQaxLR6Mj0zkKJ8DEoEjUk2StKaiJ
         H5h6UaPLLKf3R8kUoQl0gJ3/FdoPLKcCN8C1ctOmk6u6MYGnWbcNLHWH+uxCw+eXVkUD
         xM5g==
X-Gm-Message-State: AOAM532S3O98WTtnw8CAIEmCmF94eS4z3yKINg1OGfPpMzY+Ki1AvH4n
        7Lg5cRCj4C3vf7dCFruDITHyScvhXZKbDEdUzaN7bBQDrwru9ZX88CSwry0sOqhx1rIj1tPG4q7
        jU4PiKTBDrDCt
X-Received: by 2002:a37:a054:: with SMTP id j81mr4629826qke.23.1602104025800;
        Wed, 07 Oct 2020 13:53:45 -0700 (PDT)
X-Google-Smtp-Source: 
 ABdhPJyL2cVzMVNA9GlSWo/fbUOzV8IgbQ37ZjN4M5sK55UpooCzprJA1mGC9Vb1RztHEuEaHNw97g==
X-Received: by 2002:a37:a054:: with SMTP id j81mr4629812qke.23.1602104025619;
        Wed, 07 Oct 2020 13:53:45 -0700 (PDT)
Received: from xz-x1.redhat.com
 (toroon474qw-lp140-04-174-95-215-133.dsl.bell.ca. [174.95.215.133])
        by smtp.gmail.com with ESMTPSA id
 j24sm2390695qkg.107.2020.10.07.13.53.44
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Wed, 07 Oct 2020 13:53:45 -0700 (PDT)
From: Peter Xu <peterx@redhat.com>
To: kvm@vger.kernel.org, linux-kernel@vger.kernel.org
Cc: peterx@redhat.com, Paolo Bonzini <pbonzini@redhat.com>,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        Andrew Jones <drjones@redhat.com>,
        "Dr . David Alan Gilbert" <dgilbert@redhat.com>
Subject: [PATCH v14 01/14] KVM: Documentation: Update entry for
 KVM_X86_SET_MSR_FILTER
Date: Wed,  7 Oct 2020 16:53:29 -0400
Message-Id: <20201007205342.295402-2-peterx@redhat.com>
X-Mailer: git-send-email 2.26.2
In-Reply-To: <20201007205342.295402-1-peterx@redhat.com>
References: <20201007205342.295402-1-peterx@redhat.com>
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

It should be an accident when rebase, since we've already have section
8.25 (which is KVM_CAP_S390_DIAG318).  Fix the number.

Signed-off-by: Peter Xu <peterx@redhat.com>
---
 Documentation/virt/kvm/api.rst | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
#### [PATCH] KVM/nVMX: Move nested_vmx_check_vmentry_hw inline assembly to vmenter.S
##### From: Uros Bizjak <ubizjak@gmail.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Uros Bizjak <ubizjak@gmail.com>
X-Patchwork-Id: 11820753
Return-Path: <SRS0=rZqs=DO=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 2AC4A618
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed,  7 Oct 2020 14:43:24 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 00F2E21548
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed,  7 Oct 2020 14:43:23 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=gmail.com header.i=@gmail.com
 header.b="X98lGedU"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728675AbgJGOnW (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 7 Oct 2020 10:43:22 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:33842 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1728658AbgJGOnW (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 7 Oct 2020 10:43:22 -0400
Received: from mail-ed1-x543.google.com (mail-ed1-x543.google.com
 [IPv6:2a00:1450:4864:20::543])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 5655CC061755
        for <kvm@vger.kernel.org>; Wed,  7 Oct 2020 07:43:22 -0700 (PDT)
Received: by mail-ed1-x543.google.com with SMTP id i5so2450720edr.5
        for <kvm@vger.kernel.org>; Wed, 07 Oct 2020 07:43:22 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=from:to:cc:subject:date:message-id:mime-version
         :content-transfer-encoding;
        bh=qCIIRICP5BmlqsnVWzmVkgnL6wAkef7/AiOVTqohN0Y=;
        b=X98lGedUR8e4n8Ung1tsGM6cKOxNpJspLUSoFZ74ntHufrkdcvTMq2IhzCqdXnZKvQ
         cMKlGu3QUtXtFOBtgi6X8GRB7oHavtdY8fgpzeZOczuFXzhlJVEaOHprJL6fl6tm7rVi
         JghNORWau8WDEHq2/OjGuC3uaujSH2S7QEvLXmj3HOkhSnKISClfDc7OC515BWq+nUm4
         zXUw91t5uouB7HTsLOd/3WA6IlrsI3HXufo335+/+9YbRoHTMvfNuuB0NYt3bgSdhFq8
         Ewe84UA4K/Hlq79zwiVPkh+/6EBR4UxakV9dyCVMb01YthFEF/zLJXDPTvOdsN+cmtqU
         sRdA==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:mime-version
         :content-transfer-encoding;
        bh=qCIIRICP5BmlqsnVWzmVkgnL6wAkef7/AiOVTqohN0Y=;
        b=g5T6UuCWwl5W0VnOH2X2HyeDO4cgIYaMhkLI1BRGNAzCM3/9L+/EyL7DsC4nvZKbYr
         2zqO9Hb0zu/Q3IopRCCze59XAP8+/Rj9CN1k/IsOWHsZJ5VGN+MMUEBYxzGd6H4N01Nf
         z5ykf7zl+AYsKZoRhkpKIObtCmheLUl0NEkV/3D0+eZToJFP94U8CUJgQkxcNeaMQKDz
         iJOeavQ94RDjOrx1MNO6LxMuY2jrbKEhQ3eMStM0PBnFgvLJJvILZHfjbBaenyS05B3c
         ZfnC+g8UWX8jYc+436nmAA5nBvXM8f3e+6pNpncJ4EpKwJ+R+0HNQBQrkxLgu9FmxSgE
         kqpg==
X-Gm-Message-State: AOAM530PAgfYvdbLDdwknpYnPIJA2P8CMz+Z11p1jCHPGrPU60dNJBzZ
        FTJQM8RCKWswEaUq1zvfFV4kVgv/4OB5mQ==
X-Google-Smtp-Source: 
 ABdhPJyXRJu56wmEseZO5gAR6t1GJhlbHm1VJJ/BE0/MivhrUtp1b1U8+K7IpNTApC66pE+8luxCAQ==
X-Received: by 2002:aa7:dd01:: with SMTP id i1mr4083581edv.84.1602081800686;
        Wed, 07 Oct 2020 07:43:20 -0700 (PDT)
Received: from localhost.localdomain (93-103-18-160.static.t-2.net.
 [93.103.18.160])
        by smtp.gmail.com with ESMTPSA id
 w4sm1629570edr.72.2020.10.07.07.43.19
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Wed, 07 Oct 2020 07:43:20 -0700 (PDT)
From: Uros Bizjak <ubizjak@gmail.com>
To: kvm@vger.kernel.org
Cc: Uros Bizjak <ubizjak@gmail.com>,
        Paolo Bonzini <pbonzini@redhat.com>,
        Sean Christopherson <sean.j.christopherson@intel.com>
Subject: [PATCH] KVM/nVMX: Move nested_vmx_check_vmentry_hw inline assembly to
 vmenter.S
Date: Wed,  7 Oct 2020 16:43:12 +0200
Message-Id: <20201007144312.55203-1-ubizjak@gmail.com>
X-Mailer: git-send-email 2.26.2
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Move the big inline assembly block from nested_vmx_check_vmentry_hw
to vmenter.S assembly file, taking into account all ABI requirements.

The new function is modelled after __vmx_vcpu_run, and also calls
vmx_update_host_rsp instead of open-coding the function in assembly.

Cc: Paolo Bonzini <pbonzini@redhat.com>
Cc: Sean Christopherson <sean.j.christopherson@intel.com>
Signed-off-by: Uros Bizjak <ubizjak@gmail.com>
---
 arch/x86/kvm/vmx/nested.c  | 32 +++-----------------------------
 arch/x86/kvm/vmx/vmenter.S | 36 ++++++++++++++++++++++++++++++++++++
 2 files changed, 39 insertions(+), 29 deletions(-)

```
#### [PATCH 1/6] KVM: VMX: Drop guest CPUID check for VMXE in vmx_set_cr4()
##### From: Sean Christopherson <sean.j.christopherson@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Sean Christopherson <sean.j.christopherson@intel.com>
X-Patchwork-Id: 11819637
Return-Path: <SRS0=rZqs=DO=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 74CFD139F
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed,  7 Oct 2020 01:44:35 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 5FFFF20782
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed,  7 Oct 2020 01:44:35 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727351AbgJGBoV (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 6 Oct 2020 21:44:21 -0400
Received: from mga09.intel.com ([134.134.136.24]:7786 "EHLO mga09.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726323AbgJGBoT (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 6 Oct 2020 21:44:19 -0400
IronPort-SDR: 
 OQZzdcldT/AWS8dV55KTiw1kOjynNkACiTreEVQmX5tEUz4ZDympu1zekgdIk4WhVo1uIFSuHM
 J+w2u77omkpw==
X-IronPort-AV: E=McAfee;i="6000,8403,9766"; a="164914596"
X-IronPort-AV: E=Sophos;i="5.77,344,1596524400";
   d="scan'208";a="164914596"
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from fmsmga008.fm.intel.com ([10.253.24.58])
  by orsmga102.jf.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 06 Oct 2020 18:44:18 -0700
IronPort-SDR: 
 vdIVN1gcPV5l+C1riTE0uMgVqZRz19PP8fLkc8NyKxq/zSXAadMYnLp8a/oCbygAnVpLRS/dFO
 dIxG6y8AWqgw==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.77,344,1596524400";
   d="scan'208";a="297410297"
Received: from sjchrist-coffee.jf.intel.com ([10.54.74.160])
  by fmsmga008.fm.intel.com with ESMTP; 06 Oct 2020 18:44:18 -0700
From: Sean Christopherson <sean.j.christopherson@intel.com>
To: Paolo Bonzini <pbonzini@redhat.com>
Cc: Sean Christopherson <sean.j.christopherson@intel.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org,
        Stas Sergeev <stsp@users.sourceforge.net>
Subject: [PATCH 1/6] KVM: VMX: Drop guest CPUID check for VMXE in
 vmx_set_cr4()
Date: Tue,  6 Oct 2020 18:44:12 -0700
Message-Id: <20201007014417.29276-2-sean.j.christopherson@intel.com>
X-Mailer: git-send-email 2.28.0
In-Reply-To: <20201007014417.29276-1-sean.j.christopherson@intel.com>
References: <20201007014417.29276-1-sean.j.christopherson@intel.com>
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Drop vmx_set_cr4()'s somewhat hidden guest_cpuid_has() check on VMXE now
that common x86 handles the check by incorporating VMXE into the CR4
reserved bits, i.e. in cr4_guest_rsvd_bits.  This fixes a bug where KVM
incorrectly rejects KVM_SET_SREGS with CR4.VMXE=1 if it's executed
before KVM_SET_CPUID{,2}.

Fixes: 5e1746d6205d ("KVM: nVMX: Allow setting the VMXE bit in CR4")
Reported-by: Stas Sergeev <stsp@users.sourceforge.net>
Signed-off-by: Sean Christopherson <sean.j.christopherson@intel.com>
---
 arch/x86/kvm/vmx/vmx.c | 5 +++--
 1 file changed, 3 insertions(+), 2 deletions(-)

```
#### [PATCH v3 1/5] s390/pci: stash version in the zpci_dev
##### From: Matthew Rosato <mjrosato@linux.ibm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Matthew Rosato <mjrosato@linux.ibm.com>
X-Patchwork-Id: 11821609
Return-Path: <SRS0=rZqs=DO=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id EE09714D5
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed,  7 Oct 2020 18:56:58 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id C23A721775
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed,  7 Oct 2020 18:56:58 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=ibm.com header.i=@ibm.com
 header.b="Pfc+za0O"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728253AbgJGS4g (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 7 Oct 2020 14:56:36 -0400
Received: from mx0a-001b2d01.pphosted.com ([148.163.156.1]:2554 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1726111AbgJGS4e (ORCPT
        <rfc822;kvm@vger.kernel.org>); Wed, 7 Oct 2020 14:56:34 -0400
Received: from pps.filterd (m0098393.ppops.net [127.0.0.1])
        by mx0a-001b2d01.pphosted.com (8.16.0.42/8.16.0.42) with SMTP id
 097IlLVe111441;
        Wed, 7 Oct 2020 14:56:34 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=ibm.com;
 h=from : to : cc : subject
 : date : message-id : in-reply-to : references; s=pp1;
 bh=qwyKtTUgEZyoCRJjBqLKwxEQ4USWfunQbmB6tnOBH9k=;
 b=Pfc+za0OKoIS9Ejl2H8C1TOAS7EiC9xiZh+E9u1FJOgHP/EGiY7/sp6BN/n6g3kgmLL9
 L3jrnPMvXBV/GWimStzHsIEq1OfTdjwnZ5e1+wFYc3Uik/Vahw96sbLyup3co+vIYNTU
 kgOFaE5CN1TgL6kVDwERfz1QMN5j1DnQkey/Evdyk+rKub7S1AOgASrGs7xT1ICHIq1p
 ZGF98sWXxwUZt0WiMZYwnWunRrhbW0DfJJ8EB/uOLZWkyeirL0Va+J9H56EWZkrFmSzk
 GsRGPPPhms38267v5Gp1D3+bi7mm4zd5pgywpPcyTHWc7ZRjcayjkgzCuEWQrSUfBQDg LA==
Received: from pps.reinject (localhost [127.0.0.1])
        by mx0a-001b2d01.pphosted.com with ESMTP id 341k8u05e9-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Wed, 07 Oct 2020 14:56:33 -0400
Received: from m0098393.ppops.net (m0098393.ppops.net [127.0.0.1])
        by pps.reinject (8.16.0.36/8.16.0.36) with SMTP id 097IpbZP125129;
        Wed, 7 Oct 2020 14:56:33 -0400
Received: from ppma01dal.us.ibm.com (83.d6.3fa9.ip4.static.sl-reverse.com
 [169.63.214.131])
        by mx0a-001b2d01.pphosted.com with ESMTP id 341k8u05dx-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Wed, 07 Oct 2020 14:56:33 -0400
Received: from pps.filterd (ppma01dal.us.ibm.com [127.0.0.1])
        by ppma01dal.us.ibm.com (8.16.0.42/8.16.0.42) with SMTP id
 097IlVHD029818;
        Wed, 7 Oct 2020 18:56:32 GMT
Received: from b03cxnp08028.gho.boulder.ibm.com
 (b03cxnp08028.gho.boulder.ibm.com [9.17.130.20])
        by ppma01dal.us.ibm.com with ESMTP id 33xgx9sm0m-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Wed, 07 Oct 2020 18:56:32 +0000
Received: from b03ledav004.gho.boulder.ibm.com
 (b03ledav004.gho.boulder.ibm.com [9.17.130.235])
        by b03cxnp08028.gho.boulder.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id 097IuTfC1114660
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Wed, 7 Oct 2020 18:56:29 GMT
Received: from b03ledav004.gho.boulder.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 2150878066;
        Wed,  7 Oct 2020 18:56:29 +0000 (GMT)
Received: from b03ledav004.gho.boulder.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 03C2778064;
        Wed,  7 Oct 2020 18:56:28 +0000 (GMT)
Received: from oc4221205838.ibm.com (unknown [9.211.60.106])
        by b03ledav004.gho.boulder.ibm.com (Postfix) with ESMTP;
        Wed,  7 Oct 2020 18:56:27 +0000 (GMT)
From: Matthew Rosato <mjrosato@linux.ibm.com>
To: alex.williamson@redhat.com, cohuck@redhat.com,
        schnelle@linux.ibm.com
Cc: pmorel@linux.ibm.com, borntraeger@de.ibm.com, hca@linux.ibm.com,
        gor@linux.ibm.com, gerald.schaefer@linux.ibm.com,
        linux-s390@vger.kernel.org, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org
Subject: [PATCH v3 1/5] s390/pci: stash version in the zpci_dev
Date: Wed,  7 Oct 2020 14:56:20 -0400
Message-Id: <1602096984-13703-2-git-send-email-mjrosato@linux.ibm.com>
X-Mailer: git-send-email 1.8.3.1
In-Reply-To: <1602096984-13703-1-git-send-email-mjrosato@linux.ibm.com>
References: <1602096984-13703-1-git-send-email-mjrosato@linux.ibm.com>
X-TM-AS-GCONF: 00
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.235,18.0.687
 definitions=2020-10-07_10:2020-10-07,2020-10-07 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 suspectscore=0 phishscore=0
 priorityscore=1501 malwarescore=0 clxscore=1015 adultscore=0 bulkscore=0
 impostorscore=0 mlxlogscore=980 mlxscore=0 spamscore=0 lowpriorityscore=0
 classifier=spam adjust=0 reason=mlx scancount=1 engine=8.12.0-2006250000
 definitions=main-2010070116
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

In preparation for passing the info on to vfio-pci devices, stash the
supported PCI version for the target device in the zpci_dev.

Signed-off-by: Matthew Rosato <mjrosato@linux.ibm.com>
Acked-by: Niklas Schnelle <schnelle@linux.ibm.com>
Acked-by: Christian Borntraeger <borntraeger@de.ibm.com>
Acked-by: Cornelia Huck <cohuck@redhat.com>
---
 arch/s390/include/asm/pci.h | 1 +
 arch/s390/pci/pci_clp.c     | 1 +
 2 files changed, 2 insertions(+)

```
#### [PATCH v3 01/10] s390x/pci: Move header files to include/hw/s390x
##### From: Matthew Rosato <mjrosato@linux.ibm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Matthew Rosato <mjrosato@linux.ibm.com>
X-Patchwork-Id: 11821627
Return-Path: <SRS0=rZqs=DO=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id C3CC413B2
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed,  7 Oct 2020 19:04:45 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 9B7A921707
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed,  7 Oct 2020 19:04:45 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=ibm.com header.i=@ibm.com
 header.b="nBTcs0C2"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728289AbgJGTEo (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 7 Oct 2020 15:04:44 -0400
Received: from mx0b-001b2d01.pphosted.com ([148.163.158.5]:50754 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S1728268AbgJGTEo (ORCPT
        <rfc822;kvm@vger.kernel.org>); Wed, 7 Oct 2020 15:04:44 -0400
Received: from pps.filterd (m0098416.ppops.net [127.0.0.1])
        by mx0b-001b2d01.pphosted.com (8.16.0.42/8.16.0.42) with SMTP id
 097J2NTR035737;
        Wed, 7 Oct 2020 15:04:24 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=ibm.com;
 h=from : to : cc : subject
 : date : message-id : in-reply-to : references; s=pp1;
 bh=6S2PkKO16g+NTMVJmmUS50xG/Pjax80JpxCq2Qlgokw=;
 b=nBTcs0C2nGyF2FXtecnvxOuiUjS4RNpcdQ+aDgfSdqixT0GoaDmFmdQwVjmze3bGDC9B
 +u7GJffj4g0VSfLdijcEXVz+ZrrAjJmeX/jbXq0b/AEn/JOfp3D8v8MmX1S1EzQfl0dK
 mp71GVaXR1YL3zRruJ/FzxUsQfLmprFvPxPIyf5ztgDzTnjcOjkNllcS+NbIKKkXlSqt
 sNxQGPnFYiAa0Uxx+DnKmmrcb61fJYLiBfrbbfrc2j1U8x0VAnzXfEEkEcglvaPi5GHz
 OXbDTEnF7f/Bts+j6hbF7tZjOTnNqs8TBp/7ThYPX2bQrfG6puqMn9yQwkbU1wc8vhAi Rw==
Received: from pps.reinject (localhost [127.0.0.1])
        by mx0b-001b2d01.pphosted.com with ESMTP id 341jak25xg-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Wed, 07 Oct 2020 15:04:24 -0400
Received: from m0098416.ppops.net (m0098416.ppops.net [127.0.0.1])
        by pps.reinject (8.16.0.36/8.16.0.36) with SMTP id 097J2QXr036157;
        Wed, 7 Oct 2020 15:04:24 -0400
Received: from ppma04dal.us.ibm.com (7a.29.35a9.ip4.static.sl-reverse.com
 [169.53.41.122])
        by mx0b-001b2d01.pphosted.com with ESMTP id 341jak25x6-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Wed, 07 Oct 2020 15:04:24 -0400
Received: from pps.filterd (ppma04dal.us.ibm.com [127.0.0.1])
        by ppma04dal.us.ibm.com (8.16.0.42/8.16.0.42) with SMTP id
 097IllfS028843;
        Wed, 7 Oct 2020 19:04:23 GMT
Received: from b01cxnp22036.gho.pok.ibm.com (b01cxnp22036.gho.pok.ibm.com
 [9.57.198.26])
        by ppma04dal.us.ibm.com with ESMTP id 3411xd81wr-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Wed, 07 Oct 2020 19:04:23 +0000
Received: from b01ledav006.gho.pok.ibm.com (b01ledav006.gho.pok.ibm.com
 [9.57.199.111])
        by b01cxnp22036.gho.pok.ibm.com (8.14.9/8.14.9/NCO v10.0) with ESMTP
 id 097J4MC213435520
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Wed, 7 Oct 2020 19:04:22 GMT
Received: from b01ledav006.gho.pok.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 911CFAC05F;
        Wed,  7 Oct 2020 19:04:22 +0000 (GMT)
Received: from b01ledav006.gho.pok.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 259C8AC059;
        Wed,  7 Oct 2020 19:04:20 +0000 (GMT)
Received: from oc4221205838.ibm.com (unknown [9.211.60.106])
        by b01ledav006.gho.pok.ibm.com (Postfix) with ESMTP;
        Wed,  7 Oct 2020 19:04:19 +0000 (GMT)
From: Matthew Rosato <mjrosato@linux.ibm.com>
To: cohuck@redhat.com, thuth@redhat.com
Cc: pmorel@linux.ibm.com, schnelle@linux.ibm.com, rth@twiddle.net,
        david@redhat.com, pasic@linux.ibm.com, borntraeger@de.ibm.com,
        mst@redhat.com, pbonzini@redhat.com, alex.williamson@redhat.com,
        qemu-s390x@nongnu.org, qemu-devel@nongnu.org, kvm@vger.kernel.org
Subject: [PATCH v3 01/10] s390x/pci: Move header files to include/hw/s390x
Date: Wed,  7 Oct 2020 15:04:06 -0400
Message-Id: <1602097455-15658-2-git-send-email-mjrosato@linux.ibm.com>
X-Mailer: git-send-email 1.8.3.1
In-Reply-To: <1602097455-15658-1-git-send-email-mjrosato@linux.ibm.com>
References: <1602097455-15658-1-git-send-email-mjrosato@linux.ibm.com>
X-TM-AS-GCONF: 00
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.235,18.0.687
 definitions=2020-10-07_10:2020-10-07,2020-10-07 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 adultscore=0 impostorscore=0
 mlxlogscore=999 malwarescore=0 suspectscore=0 clxscore=1015 phishscore=0
 mlxscore=0 priorityscore=1501 bulkscore=0 spamscore=0 lowpriorityscore=0
 classifier=spam adjust=0 reason=mlx scancount=1 engine=8.12.0-2006250000
 definitions=main-2010070118
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Seems a more appropriate location for them.

Signed-off-by: Matthew Rosato <mjrosato@linux.ibm.com>
---
 MAINTAINERS                              | 1 +
 hw/s390x/s390-pci-bus.c                  | 4 ++--
 hw/s390x/s390-pci-inst.c                 | 4 ++--
 hw/s390x/s390-virtio-ccw.c               | 2 +-
 {hw => include/hw}/s390x/s390-pci-bus.h  | 0
 {hw => include/hw}/s390x/s390-pci-inst.h | 0
 6 files changed, 6 insertions(+), 5 deletions(-)
 rename {hw => include/hw}/s390x/s390-pci-bus.h (100%)
 rename {hw => include/hw}/s390x/s390-pci-inst.h (100%)

```
