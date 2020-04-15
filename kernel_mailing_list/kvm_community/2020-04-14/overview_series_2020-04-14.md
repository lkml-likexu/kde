#### [PATCH 1/2] kvm: nVMX: Pending debug exceptions trump expired VMX-preemption timer
##### From: Jim Mattson <jmattson@google.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Jim Mattson <jmattson@google.com>
X-Patchwork-Id: 11486475
Return-Path: <SRS0=cOhZ=56=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id E414F92C
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 14 Apr 2020 00:10:09 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id C20012072D
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 14 Apr 2020 00:10:09 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=google.com header.i=@google.com
 header.b="cnPYGmeR"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728581AbgDNAJx (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 13 Apr 2020 20:09:53 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:44674 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-FAIL-OK-FAIL)
        by vger.kernel.org with ESMTP id S1727878AbgDNAJw (ORCPT
        <rfc822;kvm@vger.kernel.org>); Mon, 13 Apr 2020 20:09:52 -0400
Received: from mail-pj1-x1049.google.com (mail-pj1-x1049.google.com
 [IPv6:2607:f8b0:4864:20::1049])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id E6C24C0A3BDC
        for <kvm@vger.kernel.org>; Mon, 13 Apr 2020 17:09:51 -0700 (PDT)
Received: by mail-pj1-x1049.google.com with SMTP id nk12so11486957pjb.0
        for <kvm@vger.kernel.org>; Mon, 13 Apr 2020 17:09:51 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=date:message-id:mime-version:subject:from:to:cc;
        bh=YMAMGjofNrizjMQg7853fdoEDjx8XPUx997J+0sDJxw=;
        b=cnPYGmeR+Wv3TAO/DK3N42nMq5aREZ/RY/NPt0TKXw1z77l7AHmPaMmTNwSer3g9Tq
         Rja+k8BVsALShQ8C/KXja75W/eUEVzUlA9l6Y5Dooh/HOHh42oAgcVxMtXQtW6VeREK5
         5RaXUZtPGI3ZSkxx3ZJWHWDlZDCcTTcJ7Dz15eEZd/lL8UYdmMWMvczSMHbek70ejLPb
         TUpJFYHSfPdCzVrh9n/WGJQEFMfWfZUb2YJao+s8cJ0q2GQ/uGUz66fNtpBE+hF/9ecO
         eOpOjRLsPaPc67hPnEuw19KSFrXhi9gAqWrMvChyrCu1pLKZFuZejYU2RoPzhRwJiOm/
         mweA==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:date:message-id:mime-version:subject:from:to:cc;
        bh=YMAMGjofNrizjMQg7853fdoEDjx8XPUx997J+0sDJxw=;
        b=bsmhoa5G65xu928yvE+iX+JDWH7DuEgUqOm7LXg+UxUAnC2eekIZQpKVi0AxPztBm9
         CWBYIFoP2PPaPGVjRRU4y4aSxnedutbfdkHrQ5/4G1d9W/mQc1Wq22TDJo9PuUBtQ5kG
         yGlVZ+1VG1YPsRzBzkX4nTk1/kXA7FBMT8PriIQJDv5/majLuO6zWV1gXi7tLPpLhw6o
         SJIfmjdBrV2Kss7MJwumRNiX1b0kbjxhaYxrTCZuW7yoc7I6Rz4H5l5KDowApzgeEaNU
         iWG8Ml2FRzmJXBNbkJYx0dNybB3/HyS1IEkQHi20utrZ5H+G9mzXyrHyDjQwwK29sgUn
         uVwA==
X-Gm-Message-State: AGi0PuZAGBrwoc1yd9nqX6UCgew8rR5U3FPOLBAGBWyZ7SkY8rzLrCsc
        rXT6QrfAXeG2US+ZahNA8V+yPPDAtGph2XMEaM7tGdDVOol9NHdUK8htIEZwBATOpYHB0SzEEJE
        EsMi/NC3qjcxiNBB7ZhwG85V8qErCSJ8BmGShtJapoA+IQPrZgH6iaT5uMiZfIgM=
X-Google-Smtp-Source: 
 APiQypKJitwlyTtBXJfhQXPBfulHK50aZiXWH/9tfItCw3vHHP7Ax6RbvcjpRDiLrC9ysvsNNYpH/QDZVjIQKg==
X-Received: by 2002:a17:90a:fa01:: with SMTP id
 cm1mr22776943pjb.113.1586822991264;
 Mon, 13 Apr 2020 17:09:51 -0700 (PDT)
Date: Mon, 13 Apr 2020 17:09:45 -0700
Message-Id: <20200414000946.47396-1-jmattson@google.com>
Mime-Version: 1.0
X-Mailer: git-send-email 2.26.0.110.g2183baf09c-goog
Subject: [PATCH 1/2] kvm: nVMX: Pending debug exceptions trump expired
 VMX-preemption timer
From: Jim Mattson <jmattson@google.com>
To: kvm@vger.kernel.org
Cc: Jim Mattson <jmattson@google.com>,
        Oliver Upton <oupton@google.com>,
        Peter Shier <pshier@google.com>
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Previously, if L1 launched vmcs12 with both pending debug exceptions
and an already-expired VMX-preemption timer, the pending debug
exceptions were lost due to a priority inversion between a pending #DB
exception and a "VMX-preemption timer expired" VM-exit from L2 to L1.

In this scenario, L0 constructs a vmcs02 that has both a zero-valued
VMX-preemption timer (assuming enable_preemption_timer is set) and
pending debug exceptions. When the vmcs02 is launched/resumed, the
hardware correctly prioritizes the pending debug exceptions. At this
point, L0 intercepts the resulting #DB trap and queues it up for
redelivery. However, when checking for nested events in software, L0
incorrectly prioritizes the "VMX-preemption timer expired" VM-exit
from L2 to L1.

Technically, nested events should probably be blocked at this
point. Hardware has already determined that the #DB trap is the next
event that should happen. L0 just got in the way because it was
concerned about infinite IDT vectoring loops.

Logically, the enqueued #DB trap is quite similar to a "reinjected"
event resulting from interrupted IDT-vectoring. Treating it as such
fixes the problem, since nested events are blocked when a reinjected
event is present. However, there are some ways in which the enqueued
interrupted IDT-vectoring. In particular, it should not be recorded in
the IDT-vectoring information field of the vmcs12 in the event of a
synthesized VM-exit from L2 to L1. I don't believe that path should
ever be taken, since the #DB trap should take priority over any
synthesized VM-exit from L2 to L1.

Recategorize both the reinjected #DB and #AC exceptions as
"reinjected" exceptions. For consistency, do the same thing for SVM,
even though it doesn't have a VMX-preemption timer equivalent.

Fixes: f4124500c2c13 ("KVM: nVMX: Fully emulate preemption timer")
Signed-off-by: Jim Mattson <jmattson@google.com>
Reviewed-by: Oliver Upton <oupton@google.com>
Reviewed-by: Peter Shier <pshier@google.com>
---
 arch/x86/kvm/svm/svm.c | 4 ++--
 arch/x86/kvm/vmx/vmx.c | 4 ++--
 2 files changed, 4 insertions(+), 4 deletions(-)

```
#### [PATCH v2 10/33] docs: fix broken references for ReST files that moved around
##### From: Mauro Carvalho Chehab <mchehab+huawei@kernel.org>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Mauro Carvalho Chehab <mchehab+huawei@kernel.org>
X-Patchwork-Id: 11488701
Return-Path: <SRS0=cOhZ=56=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 09CE2912
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 14 Apr 2020 16:57:34 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id E08312054F
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 14 Apr 2020 16:57:33 +0000 (UTC)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple; d=kernel.org;
	s=default; t=1586883453;
	bh=p4BaOts5XwS9tdFV4i/p0/J5e6kWOeDWMFxv85StaUU=;
	h=From:To:Cc:Subject:Date:In-Reply-To:References:List-ID:From;
	b=thBOimbUd7aftaVfW0Hq4jy0QwZnVhv7VwTVPnOyAr3PYZhjTU/e9pN0YO7p8KXO3
	 bauVu9cdI3382LprQg1sVpSlOaHddFn2OISnt035/Ny2MJIyF+FbaP6kd79ZxPgwmg
	 KZWtJkBefs4LSjJVv2k6o6x0EMTtv22LCcRvXcGQ=
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2391493AbgDNQ4C (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 14 Apr 2020 12:56:02 -0400
Received: from mail.kernel.org ([198.145.29.99]:55222 "EHLO mail.kernel.org"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S2405576AbgDNQtH (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 14 Apr 2020 12:49:07 -0400
Received: from mail.kernel.org (ip5f5ad4d8.dynamic.kabel-deutschland.de
 [95.90.212.216])
        (using TLSv1.2 with cipher ECDHE-RSA-AES256-GCM-SHA384 (256/256 bits))
        (No client certificate requested)
        by mail.kernel.org (Postfix) with ESMTPSA id A1EE5214D8;
        Tue, 14 Apr 2020 16:49:02 +0000 (UTC)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple; d=kernel.org;
        s=default; t=1586882942;
        bh=p4BaOts5XwS9tdFV4i/p0/J5e6kWOeDWMFxv85StaUU=;
        h=From:To:Cc:Subject:Date:In-Reply-To:References:From;
        b=p9qGMRIzAkvFnHhlQeLCMA/c/N9w9OOjuBKNanQ/VsCxW1/TRGrDKQv10ecEiZHYB
         janBLf1q+j2PSXdjOkI2q9dQ5TaT/BmqqA220JsuLo2qXKLrYmVfNaKv3Zn/lcmCCk
         xSyrLA5uUgzxoY6zim1b8II8HRYy6zzM+njq386o=
Received: from mchehab by mail.kernel.org with local (Exim 4.92.3)
        (envelope-from <mchehab@kernel.org>)
        id 1jOOk8-0068lh-RJ; Tue, 14 Apr 2020 18:49:00 +0200
From: Mauro Carvalho Chehab <mchehab+huawei@kernel.org>
To: Linux Doc Mailing List <linux-doc@vger.kernel.org>
Cc: Mauro Carvalho Chehab <mchehab+huawei@kernel.org>,
        linux-kernel@vger.kernel.org, Jonathan Corbet <corbet@lwn.net>,
        Paolo Bonzini <pbonzini@redhat.com>,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>,
        Thomas Gleixner <tglx@linutronix.de>,
        Ingo Molnar <mingo@redhat.com>, Borislav Petkov <bp@alien8.de>,
        x86@kernel.org, "H. Peter Anvin" <hpa@zytor.com>,
        Corentin Labbe <clabbe.montjoie@gmail.com>,
        Herbert Xu <herbert@gondor.apana.org.au>,
        "David S. Miller" <davem@davemloft.net>,
        Maxime Ripard <mripard@kernel.org>,
        Chen-Yu Tsai <wens@csie.org>, kvm@vger.kernel.org,
        linux-crypto@vger.kernel.org, linux-arm-kernel@lists.infradead.org
Subject: [PATCH v2 10/33] docs: fix broken references for ReST files that
 moved around
Date: Tue, 14 Apr 2020 18:48:36 +0200
Message-Id: 
 <64773a12b4410aaf3e3be89e3ec7e34de2484eea.1586881715.git.mchehab+huawei@kernel.org>
X-Mailer: git-send-email 2.25.2
In-Reply-To: <cover.1586881715.git.mchehab+huawei@kernel.org>
References: <cover.1586881715.git.mchehab+huawei@kernel.org>
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Some broken references happened due to shifting files around
and ReST renames. Those can't be auto-fixed by the script,
so let's fix them manually.

Signed-off-by: Mauro Carvalho Chehab <mchehab+huawei@kernel.org>
---
 Documentation/doc-guide/maintainer-profile.rst      | 2 +-
 Documentation/virt/kvm/mmu.rst                      | 2 +-
 Documentation/virt/kvm/review-checklist.rst         | 2 +-
 arch/x86/kvm/mmu/mmu.c                              | 2 +-
 drivers/crypto/allwinner/sun8i-ce/sun8i-ce-cipher.c | 2 +-
 drivers/crypto/allwinner/sun8i-ce/sun8i-ce-core.c   | 2 +-
 drivers/crypto/allwinner/sun8i-ss/sun8i-ss-cipher.c | 2 +-
 drivers/crypto/allwinner/sun8i-ss/sun8i-ss-core.c   | 2 +-
 drivers/media/v4l2-core/v4l2-fwnode.c               | 2 +-
 include/uapi/linux/kvm.h                            | 4 ++--
 tools/include/uapi/linux/kvm.h                      | 4 ++--
 11 files changed, 13 insertions(+), 13 deletions(-)

```
#### [GIT PULL] vhost: cleanups and fixes
##### From: "Michael S. Tsirkin" <mst@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 8bit
X-Patchwork-Submitter: "Michael S. Tsirkin" <mst@redhat.com>
X-Patchwork-Id: 11488567
Return-Path: <SRS0=cOhZ=56=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 4B2AD81
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 14 Apr 2020 16:36:58 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 2E3F920678
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 14 Apr 2020 16:36:58 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="dOWLE8Wq"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2391825AbgDNQgk (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 14 Apr 2020 12:36:40 -0400
Received: from us-smtp-delivery-1.mimecast.com ([207.211.31.120]:35680 "EHLO
        us-smtp-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org
        with ESMTP id S2391804AbgDNQg3 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 14 Apr 2020 12:36:29 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1586882187;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:content-type:content-type:
         content-transfer-encoding:content-transfer-encoding;
        bh=Bma9lzqspxl+HaX8bOFBirR9lSGp5CwUCJdb2i/e18Q=;
        b=dOWLE8WqA4A5HAxi0P3RPoJcrIXAXMmTkLygoAf3Yr4XpYwq+9GylDMk7kPD2Ehcahs316
        2O/OmkgH/FDc/Nq6cj9wV9egccg5EToRhqymPv7sU4WiKr5pt+9wt0CoheGtdJO2yjJtHY
        rOg8yf3kCeB1qnzDlbqbBgTFVISQDSY=
Received: from mail-qk1-f200.google.com (mail-qk1-f200.google.com
 [209.85.222.200]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-403-g0kLvAKbOjKW-waCc1_L1w-1; Tue, 14 Apr 2020 12:36:12 -0400
X-MC-Unique: g0kLvAKbOjKW-waCc1_L1w-1
Received: by mail-qk1-f200.google.com with SMTP id f187so10833972qkd.11
        for <kvm@vger.kernel.org>; Tue, 14 Apr 2020 09:36:12 -0700 (PDT)
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:date:from:to:cc:subject:message-id:mime-version
         :content-disposition:content-transfer-encoding;
        bh=Bma9lzqspxl+HaX8bOFBirR9lSGp5CwUCJdb2i/e18Q=;
        b=o+CwTHxpouBhTsY8KaoXRvesfyS1Gp9qTekIs1wP2RuaNg6l+PBqw+JQs+3JFTSVNh
         b/n68YRcyCrIfWoacKJEjPcFehC0RNthJp1bqpHBLP45OvaWQEtSSs8yfopDsKjM3BFK
         YXvJEgfQE1g923e1nhEtFBGJmwlpQqdOVi3bspzrsedTw6POHM+opYHTGkAKnf6IwWsl
         Sml5ngXoBBBguAAULsotIoC7FC01LQxo/xK07wQFzJVw+7TFB3x+3krGBM4C0oenUGKg
         k+UJRGZxMociTDVsDlqXtqwYYk4jtZ7/8mYttZwZuLYKAjNcPi8IFkQVvwO/+PoxtkTZ
         LRZw==
X-Gm-Message-State: AGi0PuaFvI+8oZV3WeP3jwLrlYRVjSX+qn91UdBrQ9OAlRyek4XCHSas
        5XKWp8vKb1JPbDUzqmZPizbB+G8mCCC/deu7k3rnBtvIK/5UdSPcytT25Mm5d5eHtEpvw3XGCvy
        8NveapOB7V/ar
X-Received: by 2002:aed:3968:: with SMTP id
 l95mr17285847qte.268.1586882172264;
        Tue, 14 Apr 2020 09:36:12 -0700 (PDT)
X-Google-Smtp-Source: 
 APiQypJmGmy3GlXUch/z8/x+Ns406G7xQ35JzF4VsBJ4waQC3oBq6dZNWOjBqM2wZ8BVLIAkuD0c8Q==
X-Received: by 2002:aed:3968:: with SMTP id
 l95mr17285823qte.268.1586882171965;
        Tue, 14 Apr 2020 09:36:11 -0700 (PDT)
Received: from redhat.com (bzq-79-183-51-3.red.bezeqint.net. [79.183.51.3])
        by smtp.gmail.com with ESMTPSA id
 u126sm10933237qkh.66.2020.04.14.09.36.07
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Tue, 14 Apr 2020 09:36:11 -0700 (PDT)
Date: Tue, 14 Apr 2020 12:36:06 -0400
From: "Michael S. Tsirkin" <mst@redhat.com>
To: Linus Torvalds <torvalds@linux-foundation.org>
Cc: kvm@vger.kernel.org, virtualization@lists.linux-foundation.org,
        netdev@vger.kernel.org, linux-kernel@vger.kernel.org,
        andy.shevchenko@gmail.com, arnd@arndb.de, ashutosh.dixit@intel.com,
        bjorn.andersson@linaro.org, elfring@users.sourceforge.net,
        eli@mellanox.com, eperezma@redhat.com, gustavo@embeddedor.com,
        hulkci@huawei.com, jasowang@redhat.com, matej.genci@nutanix.com,
        mst@redhat.com, sfr@canb.auug.org.au, yanaijie@huawei.com,
        yuehaibing@huawei.com
Subject: [GIT PULL] vhost: cleanups and fixes
Message-ID: <20200414123606-mutt-send-email-mst@kernel.org>
MIME-Version: 1.0
Content-Disposition: inline
X-Mutt-Fcc: =sent
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The following changes since commit 835a6a649d0dd1b1f46759eb60fff2f63ed253a7:

  virtio-balloon: Revert "virtio-balloon: Switch back to OOM handler for VIRTIO_BALLOON_F_DEFLATE_ON_OOM" (2020-04-07 05:44:57 -0400)

are available in the Git repository at:

  https://git.kernel.org/pub/scm/linux/kernel/git/mst/vhost.git tags/for_linus

for you to fetch changes up to d4a85c2ace895a58dcab687ff49c76719011f58d:

  vdpa: fix comment of vdpa_register_device() (2020-04-13 07:16:41 -0400)

----------------------------------------------------------------
virtio: fixes, cleanups

Some bug fixes.
Cleanup a couple of issues that surfaced meanwhile.

Signed-off-by: Michael S. Tsirkin <mst@redhat.com>

----------------------------------------------------------------
Eugenio Pérez (4):
      vhost: Create accessors for virtqueues private_data
      tools/virtio: Add --batch option
      tools/virtio: Add --batch=random option
      tools/virtio: Add --reset=random

Gustavo A. R. Silva (1):
      vhost: vdpa: remove unnecessary null check

Jason Wang (1):
      vdpa: fix comment of vdpa_register_device()

Jason Yan (1):
      vhost: remove set but not used variable 'status'

Markus Elfring (1):
      virtio-mmio: Delete an error message in vm_find_vqs()

Matej Genci (1):
      virtio: add VIRTIO_RING_NO_LEGACY

Michael S. Tsirkin (22):
      vdpa-sim: depend on HAS_DMA
      virtio/test: fix up after IOTLB changes
      vhost: drop vring dependency on iotlb
      tools/virtio: define aligned attribute
      tools/virtio: make asm/barrier.h self contained
      tools/virtio: define __KERNEL__
      virtgpu: pull in uaccess.h
      virtio-rng: pull in slab.h
      remoteproc: pull in slab.h
      virtio_input: pull in slab.h
      rpmsg: pull in slab.h
      remoteproc: pull in slab.h
      virtio: stop using legacy struct vring in kernel
      vhost: force spec specified alignment on types
      virtio: add legacy init/size APIs
      virtio_ring: switch to virtio_legacy_init/size
      tools/virtio: switch to virtio_legacy_init/size
      vop: switch to virtio_legacy_init/size
      remoteproc: switch to virtio_legacy_init/size
      mellanox: switch to virtio_legacy_init/size
      vdpa: allow a 32 bit vq alignment
      vdpa: make vhost, virtio depend on menu

Stephen Rothwell (1):
      drm/virtio: fix up for include file changes

YueHaibing (2):
      vdpa: remove unused variables 'ifcvf' and 'ifcvf_lm'
      vdpasim: Return status in vdpasim_get_status

 drivers/block/virtio_blk.c               |   1 +
 drivers/char/hw_random/virtio-rng.c      |   1 +
 drivers/gpu/drm/virtio/virtgpu_ioctl.c   |   1 +
 drivers/gpu/drm/virtio/virtgpu_kms.c     |   1 +
 drivers/misc/mic/vop/vop_main.c          |   5 +-
 drivers/misc/mic/vop/vop_vringh.c        |   8 ++-
 drivers/platform/mellanox/mlxbf-tmfifo.c |   6 +-
 drivers/remoteproc/remoteproc_core.c     |   2 +-
 drivers/remoteproc/remoteproc_sysfs.c    |   1 +
 drivers/remoteproc/remoteproc_virtio.c   |   2 +-
 drivers/remoteproc/stm32_rproc.c         |   1 +
 drivers/rpmsg/mtk_rpmsg.c                |   1 +
 drivers/vdpa/Kconfig                     |  19 +++---
 drivers/vdpa/ifcvf/ifcvf_base.c          |   2 -
 drivers/vdpa/ifcvf/ifcvf_main.c          |   4 +-
 drivers/vdpa/vdpa.c                      |   2 +-
 drivers/vdpa/vdpa_sim/vdpa_sim.c         |   4 +-
 drivers/vhost/Kconfig                    |   5 +-
 drivers/vhost/net.c                      |  28 +++++----
 drivers/vhost/scsi.c                     |  14 ++---
 drivers/vhost/test.c                     |  71 +++++++++++++++++++---
 drivers/vhost/test.h                     |   1 +
 drivers/vhost/vdpa.c                     |   5 --
 drivers/vhost/vhost.h                    |  33 +++++++++-
 drivers/vhost/vringh.c                   |   5 ++
 drivers/vhost/vsock.c                    |  14 ++---
 drivers/virtio/Kconfig                   |   2 +-
 drivers/virtio/virtio_input.c            |   1 +
 drivers/virtio/virtio_mmio.c             |   4 +-
 drivers/virtio/virtio_pci_modern.c       |   1 +
 drivers/virtio/virtio_ring.c             |  15 +++--
 include/linux/vdpa.h                     |   2 +-
 include/linux/virtio.h                   |   1 -
 include/linux/virtio_ring.h              |  46 ++++++++++++++
 include/linux/vringh.h                   |   7 +++
 include/uapi/linux/virtio_ring.h         |  30 ++++++---
 tools/virtio/Makefile                    |   5 +-
 tools/virtio/asm/barrier.h               |   1 +
 tools/virtio/generated/autoconf.h        |   0
 tools/virtio/linux/compiler.h            |   1 +
 tools/virtio/ringtest/virtio_ring_0_9.c  |   6 +-
 tools/virtio/virtio_test.c               | 101 ++++++++++++++++++++++++++-----
 tools/virtio/vringh_test.c               |  18 +++---
 43 files changed, 354 insertions(+), 124 deletions(-)
 create mode 100644 tools/virtio/generated/autoconf.h
```
#### [PATCH v8 1/4] kvm: x86: Emulate MSR IA32_CORE_CAPABILITIES
##### From: Xiaoyao Li <xiaoyao.li@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Xiaoyao Li <xiaoyao.li@intel.com>
X-Patchwork-Id: 11486853
Return-Path: <SRS0=cOhZ=56=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 37A66913
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 14 Apr 2020 06:50:29 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 2A2C42072D
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 14 Apr 2020 06:50:29 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2406119AbgDNGu1 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 14 Apr 2020 02:50:27 -0400
Received: from mga03.intel.com ([134.134.136.65]:58687 "EHLO mga03.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1728133AbgDNGuX (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 14 Apr 2020 02:50:23 -0400
IronPort-SDR: 
 9FJWmLoNwaFHndKdKQUeH1cKoVFQ2/lJsGTDBtWQFdWDjtJvvwpE+fJ++rSpLb2v8FuKxpha6k
 yfwaHWY0jfbw==
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from fmsmga004.fm.intel.com ([10.253.24.48])
  by orsmga103.jf.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 13 Apr 2020 23:50:23 -0700
IronPort-SDR: 
 DfWewV7MsffRgXIo+CGZQdPWQa7x8bBlpqYv7odtpjRFsrqjOUGwhjUKruSy4N/g/Pw02MIeET
 Kf77p1OmkvAg==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.72,381,1580803200";
   d="scan'208";a="277158345"
Received: from lxy-clx-4s.sh.intel.com ([10.239.43.132])
  by fmsmga004.fm.intel.com with ESMTP; 13 Apr 2020 23:50:18 -0700
From: Xiaoyao Li <xiaoyao.li@intel.com>
To: Paolo Bonzini <pbonzini@redhat.com>, kvm@vger.kernel.org,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        Thomas Gleixner <tglx@linutronix.de>
Cc: linux-kernel@vger.kernel.org, x86@kernel.org,
        Ingo Molnar <mingo@redhat.com>, Borislav Petkov <bp@alien8.de>,
        Andy Lutomirski <luto@kernel.org>,
        Peter Zijlstra <peterz@infradead.org>,
        Arvind Sankar <nivedita@alum.mit.edu>,
        Xiaoyao Li <xiaoyao.li@intel.com>
Subject: [PATCH v8 1/4] kvm: x86: Emulate MSR IA32_CORE_CAPABILITIES
Date: Tue, 14 Apr 2020 14:31:26 +0800
Message-Id: <20200414063129.133630-2-xiaoyao.li@intel.com>
X-Mailer: git-send-email 2.20.1
In-Reply-To: <20200414063129.133630-1-xiaoyao.li@intel.com>
References: <20200414063129.133630-1-xiaoyao.li@intel.com>
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Emulate MSR_IA32_CORE_CAPABILITIES in software and unconditionally
advertise its support to userspace. Like MSR_IA32_ARCH_CAPABILITIES, it
is a feature-enumerating MSR and can be fully emulated regardless of
hardware support.

Note, support for individual features enumerated via CORE_CAPABILITIES,
e.g., split lock detection, will be added in future patches.

Signed-off-by: Xiaoyao Li <xiaoyao.li@intel.com>
---
 arch/x86/include/asm/kvm_host.h |  1 +
 arch/x86/kvm/cpuid.c            |  3 ++-
 arch/x86/kvm/x86.c              | 22 ++++++++++++++++++++++
 3 files changed, 25 insertions(+), 1 deletion(-)

```
#### [PATCH 1/3] KVM: arm: vgic: Synchronize the whole guest on GIC{D,R}_I{S,C}ACTIVER read
##### From: Marc Zyngier <maz@kernel.org>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Marc Zyngier <maz@kernel.org>
X-Patchwork-Id: 11487237
Return-Path: <SRS0=cOhZ=56=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 7B62B913
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 14 Apr 2020 10:53:10 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 52D672072D
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 14 Apr 2020 10:53:10 +0000 (UTC)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple; d=kernel.org;
	s=default; t=1586861590;
	bh=mx5w7IRy6MQtK+OH3WOzp3WOyP3QnjfKcvz4euW+/wg=;
	h=From:To:Cc:Subject:Date:In-Reply-To:References:List-ID:From;
	b=nnKfgl28c6tNE0zUW9+lVnTLQUcsj2rm5SEfAMfWSogcGIene/TKaswSQjAxHiCBY
	 5DN4MxHIwC61e3ASEjBm5lWshR2KKtakLFXJoFuciGsiWmmr5WAkx/AlfiP2OMoV1q
	 OW5Oa3izS5Tr6rNUs/EnKC9hGpjlxiFRtudwHhZs=
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2438662AbgDNKxC (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 14 Apr 2020 06:53:02 -0400
Received: from mail.kernel.org ([198.145.29.99]:39546 "EHLO mail.kernel.org"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S2438455AbgDNKfq (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 14 Apr 2020 06:35:46 -0400
Received: from disco-boy.misterjones.org (disco-boy.misterjones.org
 [51.254.78.96])
        (using TLSv1.2 with cipher ECDHE-RSA-AES256-GCM-SHA384 (256/256 bits))
        (No client certificate requested)
        by mail.kernel.org (Postfix) with ESMTPSA id 78FFE2064A;
        Tue, 14 Apr 2020 10:35:44 +0000 (UTC)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple; d=kernel.org;
        s=default; t=1586860544;
        bh=mx5w7IRy6MQtK+OH3WOzp3WOyP3QnjfKcvz4euW+/wg=;
        h=From:To:Cc:Subject:Date:In-Reply-To:References:From;
        b=dM2+UElgXGzZHxXVrA6SkM6msBnlUkwAprNDi5Z8QHKAIat1sDVoEGEwbUnM5bav7
         oXaHwkYZ4DKBpuK7iwFmL8xPNgCWjgwk2lgrWJhjlsESGxSvYGgo7xfR/e1U0C+Zl2
         MWtrirLnbIwGYoLnypEYV9y+rH3e1UAMqEM0XGjU=
Received: from 78.163-31-62.static.virginmediabusiness.co.uk ([62.31.163.78]
 helo=why.lan)
        by disco-boy.misterjones.org with esmtpsa
 (TLS1.3:ECDHE_RSA_AES_256_GCM_SHA384:256)
        (Exim 4.92)
        (envelope-from <maz@kernel.org>)
        id 1jOIus-0036te-QM; Tue, 14 Apr 2020 11:35:42 +0100
From: Marc Zyngier <maz@kernel.org>
To: linux-arm-kernel@lists.infradead.org, kvmarm@lists.cs.columbia.edu,
        kvm@vger.kernel.org
Cc: Zenghui Yu <yuzenghui@huawei.com>,
        Eric Auger <eric.auger@redhat.com>,
        Andre Przywara <Andre.Przywara@arm.com>,
        Julien Grall <julien@xen.org>,
        James Morse <james.morse@arm.com>,
        Julien Thierry <julien.thierry.kdev@gmail.com>,
        Suzuki K Poulose <suzuki.poulose@arm.com>
Subject: [PATCH 1/3] KVM: arm: vgic: Synchronize the whole guest on
 GIC{D,R}_I{S,C}ACTIVER read
Date: Tue, 14 Apr 2020 11:35:15 +0100
Message-Id: <20200414103517.2824071-2-maz@kernel.org>
X-Mailer: git-send-email 2.25.1
In-Reply-To: <20200414103517.2824071-1-maz@kernel.org>
References: <20200414103517.2824071-1-maz@kernel.org>
MIME-Version: 1.0
X-SA-Exim-Connect-IP: 62.31.163.78
X-SA-Exim-Rcpt-To: linux-arm-kernel@lists.infradead.org,
 kvmarm@lists.cs.columbia.edu, kvm@vger.kernel.org, yuzenghui@huawei.com,
 eric.auger@redhat.com, Andre.Przywara@arm.com, julien@xen.org,
 james.morse@arm.com, julien.thierry.kdev@gmail.com, suzuki.poulose@arm.com
X-SA-Exim-Mail-From: maz@kernel.org
X-SA-Exim-Scanned: No (on disco-boy.misterjones.org);
 SAEximRunCond expanded to false
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

When a guest tries to read the active state of its interrupts,
we currently just return whatever state we have in memory. This
means that if such an interrupt lives in a List Register on another
CPU, we fail to obsertve the latest active state for this interrupt.

In order to remedy this, stop all the other vcpus so that they exit
and we can observe the most recent value for the state.

Reported-by: Julien Grall <julien@xen.org>
Signed-off-by: Marc Zyngier <maz@kernel.org>
---
 virt/kvm/arm/vgic/vgic-mmio-v2.c |   4 +-
 virt/kvm/arm/vgic/vgic-mmio-v3.c |   4 +-
 virt/kvm/arm/vgic/vgic-mmio.c    | 100 ++++++++++++++++++++-----------
 virt/kvm/arm/vgic/vgic-mmio.h    |   3 +
 4 files changed, 71 insertions(+), 40 deletions(-)

```
#### [PATCH] kvm: nVMX: match comment with return type for nested_vmx_exit_reflected
##### From: Oliver Upton <oupton@google.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Oliver Upton <oupton@google.com>
X-Patchwork-Id: 11489365
Return-Path: <SRS0=cOhZ=56=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id CF27E6CA
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 14 Apr 2020 22:12:54 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id B60E42076B
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 14 Apr 2020 22:12:54 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=google.com header.i=@google.com
 header.b="VNoDXdWQ"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2634292AbgDNWMu (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 14 Apr 2020 18:12:50 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:56792 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-FAIL-OK-FAIL)
        by vger.kernel.org with ESMTP id S1732548AbgDNWMq (ORCPT
        <rfc822;kvm@vger.kernel.org>); Tue, 14 Apr 2020 18:12:46 -0400
Received: from mail-ua1-x94a.google.com (mail-ua1-x94a.google.com
 [IPv6:2607:f8b0:4864:20::94a])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 31D9FC061A0C
        for <kvm@vger.kernel.org>; Tue, 14 Apr 2020 15:12:45 -0700 (PDT)
Received: by mail-ua1-x94a.google.com with SMTP id o24so894755uap.13
        for <kvm@vger.kernel.org>; Tue, 14 Apr 2020 15:12:45 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=date:message-id:mime-version:subject:from:to:cc;
        bh=RAayT8kRFP0BFo9zUWGRqbKZGPtkh0dg4G9PTqU2eyE=;
        b=VNoDXdWQ4hgDGmTNDZztX29k4ybyBKFOT69IVq8r9gQQUUFk9rFJhSsYSkT95mVZi5
         tbW92GOmjdEWj9NW/IZcNRgH0FB+33Oi1kSr8xSwcfVidA42k+tIS1jCmUTPVIIZmj8j
         G5Lgnk4Y3nJ4EF1ErYWCIU48YTn7je1ibaL4R360d7sWECbS55/9eI0txIsPSCZjOvMW
         yzVACLY3zMZP6yXbdR7IIiniCIf8hROMap1EohbaZ8G6WcCBOarhi3+L7HJ0FS/t3Ue5
         hpcJS5k4EtQ6vR3DixsXqI+CwFNB8Y14zIwN0CwUSknkMSeRZ9KsT+OvBDlKDaYbhMf9
         rLrA==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:date:message-id:mime-version:subject:from:to:cc;
        bh=RAayT8kRFP0BFo9zUWGRqbKZGPtkh0dg4G9PTqU2eyE=;
        b=QLV63xakIK0lqDuZptP280p8CZaCmhDJcTxGlYnWEK1rmESnGpJyN6LjwSRCOyXlfd
         sPQ2tcbV78RL1rvgknjWvk6AOLPWXXHFo9LcAZOSBz80wuPjfdmL+84gF69aGRtstl38
         WXSYDS4MupkxWHhYcY7EeAjBmFUgJH2DdqH0/OVhcVzWefgkN6lywLxpfo/vhkM4PI3p
         vLIqNOJhtRNxh3/LJkPquSbCvtA/hbFKmqJdb5ZixhKmZNH5f5WosjYxhR29lKY7/5IQ
         ma7+1QGgwqPkGlULR0bb07wz4YObI7Q4UjQbDFdl3ZNxu/NeDIapOqimnwUeObMTTt1+
         9UBg==
X-Gm-Message-State: AGi0PuZ5USpYBUU7DCXDd0Q4uWI0vuYaiHEfh3ufOlfP8iQi9k8m0ddf
        opk4qFf9TuOZQhjjXifm52zxc2QqOO42I2J9wUj/7aF4UbgDG7JxcN1/ANZbyXk28HQEun0HRt1
        AjYQOrPmPvqSEZE3lPACqu0zaE5sG8e58QR+Vyo/6YjaqoTsfxGYGfsGF1A==
X-Google-Smtp-Source: 
 APiQypKkwVomJTrVzd6NPA2wKmGmVbxUAHKF3gY2BAZFb8X0YzJv6npWFeCQItv3JmGK5gEzt612/Kx4JOM=
X-Received: by 2002:ab0:20d6:: with SMTP id z22mr2303061ual.121.1586902364143;
 Tue, 14 Apr 2020 15:12:44 -0700 (PDT)
Date: Tue, 14 Apr 2020 22:12:41 +0000
Message-Id: <20200414221241.134103-1-oupton@google.com>
Mime-Version: 1.0
X-Mailer: git-send-email 2.26.0.110.g2183baf09c-goog
Subject: [PATCH] kvm: nVMX: match comment with return type for
 nested_vmx_exit_reflected
From: Oliver Upton <oupton@google.com>
To: kvm@vger.kernel.org
Cc: Paolo Bonzini <pbonzini@redhat.com>,
        Oliver Upton <oupton@google.com>
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

nested_vmx_exit_reflected() returns a bool, not int. As such, refer to
the return values as true/false in the comment instead of 1/0.

Signed-off-by: Oliver Upton <oupton@google.com>
---
 arch/x86/kvm/vmx/nested.c | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
#### [PATCH] kvm: nVMX: reflect MTF VM-exits if injected by L1From: Oliver Upton <oupton@google.com>
##### From: Oliver Upton <oupton@google.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Oliver Upton <oupton@google.com>
X-Patchwork-Id: 11489347
Return-Path: <SRS0=cOhZ=56=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 4C2056CA
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 14 Apr 2020 21:55:00 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 347C1206A2
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 14 Apr 2020 21:55:00 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=google.com header.i=@google.com
 header.b="PJxiAuBs"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2391834AbgDNVy4 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 14 Apr 2020 17:54:56 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:53956 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-FAIL-OK-FAIL)
        by vger.kernel.org with ESMTP id S1732193AbgDNVyq (ORCPT
        <rfc822;kvm@vger.kernel.org>); Tue, 14 Apr 2020 17:54:46 -0400
Received: from mail-ua1-x94a.google.com (mail-ua1-x94a.google.com
 [IPv6:2607:f8b0:4864:20::94a])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 7B019C061A0C
        for <kvm@vger.kernel.org>; Tue, 14 Apr 2020 14:47:10 -0700 (PDT)
Received: by mail-ua1-x94a.google.com with SMTP id g12so841802uan.22
        for <kvm@vger.kernel.org>; Tue, 14 Apr 2020 14:47:10 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=date:message-id:mime-version:subject:from:to:cc;
        bh=IZmFXnLAEGBjvKAtlq8tf/GD5WNVE7Cu3UKUCseMIAA=;
        b=PJxiAuBsMJgNUx3/ZpgI+ihFX8N6d3rUuIl/Ub9+rbZMqDfz8nj0Bhuu3YnaPp5Nlg
         buBai79DSiSeaztIrT0yzARIH+lv4I4qT6YYX/8P25FCFncGPComsa3CoVVSBgMbKgi1
         8EbMHx99Wq/DW8rOxtA6W2RQPk0Jqi3hpYFh94F+vWcm1+Qk+u7/Bf0VgUBu+5EwUwjy
         H838617HRm7pz8btx3jZOYWDTjBMIPAVoM52oPlL8c/TMm1oJ/3FYYpwwGQAGTArkVKg
         Q78OLXsSO3XqXE4k4mn0yDdVbLlGuN1ttCEjaUmnNnlZe/1TyxWC0bmNDi3XlRmYp+/v
         ARGQ==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:date:message-id:mime-version:subject:from:to:cc;
        bh=IZmFXnLAEGBjvKAtlq8tf/GD5WNVE7Cu3UKUCseMIAA=;
        b=XfrC8IDZBbuiuXqF+ZQq8sRSE/w+hIY+18SgAgVps9r8DTweJxaWoNOcd5gsMtaUtI
         urzNbGo9dH1Oos7jJMga/cCPiZdiFXv6pkMfPOKRgmpFvtzt1uThRw49bDyEfXqMfn0u
         CsBxtZvmzNydIPg+wFbs4Ld3A+PA1/8AsSX08L9H0umGU/UJwpaORAmbMN314txkGYjS
         JL49ASHd1Axfl52G6uf0Cbz2AhCKJHSSl7ghk/o+vWfjbbEk0UCpMqKxvhXlL2iLNdbD
         mv4MwmMG/DEtLLj3RwJntVagDvS6+WBfJVtkTjhqD45mNS/bpj/9VRsLHjNALbYwA1pP
         Uo6A==
X-Gm-Message-State: AGi0PuaTEtTZWuLahHlzFboLfB+GhvQ61CxJQyI17NdlK+id/upi8W2y
        EgxegCzdTUhZb9SDzFvSVNDAXyowb38fBNVu91vUY9eOGwZeKC/elNA08Woq2opVJmTQa+2jtl1
        Jb0UcjtjP81XoF9JLEY1kuoEraUAVCkmEdVDhog7Kfaeo6Sp3Fq0b8lvB2g==
X-Google-Smtp-Source: 
 APiQypJIEr1XTtypyYJ3aCilDKTSScPOJaEl588n1OW/jJ7FGEeRt2qjvJ8CDRGlX/Ee7e8MOcCLwzG7j3E=
X-Received: by 2002:ab0:4e96:: with SMTP id l22mr2130594uah.88.1586900829324;
 Tue, 14 Apr 2020 14:47:09 -0700 (PDT)
Date: Tue, 14 Apr 2020 21:46:34 +0000
Message-Id: <20200414214634.126508-1-oupton@google.com>
Mime-Version: 1.0
X-Mailer: git-send-email 2.26.0.110.g2183baf09c-goog
Subject: [PATCH] kvm: nVMX: reflect MTF VM-exits if injected by L1
From: Oliver Upton <oupton@google.com>
To: kvm@vger.kernel.org
Cc: Paolo Bonzini <pbonzini@redhat.com>,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        Oliver Upton <oupton@google.com>,
        Peter Shier <pshier@google.com>,
        Jim Mattson <jmattson@google.com>
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

According to SDM 26.6.2, it is possible to inject an MTF VM-exit via the
VM-entry interruption-information field regardless of the 'monitor trap
flag' VM-execution control. KVM appropriately copies the VM-entry
interruption-information field from vmcs12 to vmcs02. However, if L1
has not set the 'monitor trap flag' VM-execution control, KVM fails to
reflect the subsequent MTF VM-exit into L1.

Fix this by consulting the VM-entry interruption-information field of
vmcs12 to determine if L1 has injected the MTF VM-exit. If so, reflect
the exit, regardless of the 'monitor trap flag' VM-execution control.

Link: https://bugzilla.kernel.org/show_bug.cgi?id=207177
Fixes: 5f3d45e7f282 ("kvm/x86: add support for MONITOR_TRAP_FLAG")
Signed-off-by: Oliver Upton <oupton@google.com>
Reviewed-by: Peter Shier <pshier@google.com>
Reviewed-by: Jim Mattson <jmattson@google.com>
---
 Parent commit: dbef2808af6c5 ("KVM: VMX: fix crash cleanup when KVM wasn't used")
 arch/x86/kvm/vmx/nested.c | 20 +++++++++++++++++++-
 1 file changed, 19 insertions(+), 1 deletion(-)

```
#### [PATCH] KVM: SVM: Do not mark svm_vcpu_run with STACK_FRAME_NON_STANDARD
##### From: Uros Bizjak <ubizjak@gmail.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Uros Bizjak <ubizjak@gmail.com>
X-Patchwork-Id: 11487285
Return-Path: <SRS0=cOhZ=56=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 03447912
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 14 Apr 2020 11:36:37 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id DE1052072D
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 14 Apr 2020 11:36:36 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=gmail.com header.i=@gmail.com
 header.b="PFdyJ2Ff"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2439359AbgDNLgd (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 14 Apr 2020 07:36:33 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:39704 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-FAIL-OK-FAIL)
        by vger.kernel.org with ESMTP id S2439354AbgDNLg3 (ORCPT
        <rfc822;kvm@vger.kernel.org>); Tue, 14 Apr 2020 07:36:29 -0400
Received: from mail-wm1-x342.google.com (mail-wm1-x342.google.com
 [IPv6:2a00:1450:4864:20::342])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id ADD48C061A0C
        for <kvm@vger.kernel.org>; Tue, 14 Apr 2020 04:36:28 -0700 (PDT)
Received: by mail-wm1-x342.google.com with SMTP id o81so7028914wmo.2
        for <kvm@vger.kernel.org>; Tue, 14 Apr 2020 04:36:28 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=from:to:cc:subject:date:message-id:mime-version
         :content-transfer-encoding;
        bh=abDDrXt9n4LOnvnvIGu8nDnT6fx9WYxogyMHMmUrooA=;
        b=PFdyJ2FfINhhxwNBW3a8Ixf4RvvY4apyDWTg2PEPa2AN/MPFA/Modurp4R9C3RJrQg
         cuzVxvEYEiDZ152R5gXK8U4yK5TE9Oi9EaNi1/iYPRjg/B8LCTu8MikPKiMDmhcpqtSl
         8PIkZuW8Gi+Th/9Hym58wpPGwbJhLoZ08fUpCnB6jmav9MhFJnCT3wPdojD+LlKS4OLs
         WwV0We751vSkoxv2zEUjkm6LltGo1WUlm4AaH482GbjDXi/jL6+QlKRoF3qt+bR7Kg2b
         DMF/AQFsSPcbjxSX2vs8aoFU0vwbW5gqRCQJmplzbFol5SibXwFs0oPDZS9INTzWo/9D
         P6qA==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:mime-version
         :content-transfer-encoding;
        bh=abDDrXt9n4LOnvnvIGu8nDnT6fx9WYxogyMHMmUrooA=;
        b=CHIhEmgO0Q/cbssGp0ca0G2kHKnRhXJ6BuoNSdkSkoMO/JiChGLIuA47ugWPmQTel9
         KeCVxXYSuNVbSmAaLs2ff/cF0iEw3PrvnRlmlon6wbChQ2BI0LzbFAllUAcAf11SZcyg
         nvbNksDxlZ2yhOMW+MDRVHD/KHUS0ZN4PriRCbAmeT5TWrryeFHfsdvopPNTrJPJ63Yq
         kr6caPJ6gy8qYMEoIkC9ZGNMfcCUsf82hrS/EPZjZu5XFGwoh/dSrsMEKjcaUAR2Epx9
         eNaWIcQ1AoAUR6tWRGOeIFgZ9fGll2WGGVHgeSkAByDC8RwoVV2UiMNl0KPj5XHC5A6N
         g22w==
X-Gm-Message-State: AGi0PuZRYZlrzPbc/1tUg5MgkjtZi9iS5UY0KEz/aomFrAWcDK8qu6pm
        KPx3DZtSSTNJc+cMbNLXKYOMhEYxGa4=
X-Google-Smtp-Source: 
 APiQypLjDMW60tt9hAYguUpg8UQo5ZdfJWfkIbWKC+3ZQt17nduxKb/Oi9fYxwL4DLWlozBpQD7oug==
X-Received: by 2002:a1c:2056:: with SMTP id
 g83mr23054286wmg.179.1586864187099;
        Tue, 14 Apr 2020 04:36:27 -0700 (PDT)
Received: from localhost.localdomain (93-103-18-160.static.t-2.net.
 [93.103.18.160])
        by smtp.gmail.com with ESMTPSA id
 x23sm10832097wmj.6.2020.04.14.04.36.25
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Tue, 14 Apr 2020 04:36:26 -0700 (PDT)
From: Uros Bizjak <ubizjak@gmail.com>
To: kvm@vger.kernel.org
Cc: Uros Bizjak <ubizjak@gmail.com>,
        Paolo Bonzini <pbonzini@redhat.com>
Subject: [PATCH] KVM: SVM: Do not mark svm_vcpu_run with
 STACK_FRAME_NON_STANDARD
Date: Tue, 14 Apr 2020 13:36:12 +0200
Message-Id: <20200414113612.104501-1-ubizjak@gmail.com>
X-Mailer: git-send-email 2.25.2
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

svm_vcpu_run does not change stack or frame pointer anymore.

Cc: Paolo Bonzini <pbonzini@redhat.com>
Signed-off-by: Uros Bizjak <ubizjak@gmail.com>
---
 arch/x86/kvm/svm/svm.c | 1 -
 1 file changed, 1 deletion(-)

```
#### [PATCH 1/2] KVM: SVM: Implement check_nested_events for NMI
##### From: Cathy Avery <cavery@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Cathy Avery <cavery@redhat.com>
X-Patchwork-Id: 11489151
Return-Path: <SRS0=cOhZ=56=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id DF8B3913
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 14 Apr 2020 20:11:37 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id C72122076B
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 14 Apr 2020 20:11:37 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="iEh+MOz5"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2632747AbgDNULg (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 14 Apr 2020 16:11:36 -0400
Received: from us-smtp-delivery-1.mimecast.com ([207.211.31.120]:47260 "EHLO
        us-smtp-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org
        with ESMTP id S2632740AbgDNULR (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 14 Apr 2020 16:11:17 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1586895075;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding:
         in-reply-to:in-reply-to:references:references;
        bh=t7aLyIzVIv8UgnZXzETONCOSTJxW/XfBuHyqu3EQW8M=;
        b=iEh+MOz5ExLjTeb4Bj9lorap/hZAUQkcNY6bgMjEWyYorWQJ2D1v6ewDVIB2d2JP/FOvl2
        OJYgbqVRmmg8j1dmPPCXBhLMR1Hyv6rYpo4UTRTo4yAPZ49YHN8bdtq23Ut/+xV+flsiMp
        2OCf5OSyAH1FaIbj1lnHgfQ3n/TWQYs=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-303-T-VB9X6nO8ODzdUku_1Fng-1; Tue, 14 Apr 2020 16:11:13 -0400
X-MC-Unique: T-VB9X6nO8ODzdUku_1Fng-1
Received: from smtp.corp.redhat.com (int-mx04.intmail.prod.int.phx2.redhat.com
 [10.5.11.14])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 4E5221088398;
        Tue, 14 Apr 2020 20:11:12 +0000 (UTC)
Received: from localhost.localdomain.com (ovpn-113-69.rdu2.redhat.com
 [10.10.113.69])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 883765DA66;
        Tue, 14 Apr 2020 20:11:11 +0000 (UTC)
From: Cathy Avery <cavery@redhat.com>
To: linux-kernel@vger.kernel.org, kvm@vger.kernel.org,
        pbonzini@redhat.com
Cc: vkuznets@redhat.com, wei.huang2@amd.com
Subject: [PATCH 1/2] KVM: SVM: Implement check_nested_events for NMI
Date: Tue, 14 Apr 2020 16:11:06 -0400
Message-Id: <20200414201107.22952-2-cavery@redhat.com>
In-Reply-To: <20200414201107.22952-1-cavery@redhat.com>
References: <20200414201107.22952-1-cavery@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.14
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Migrate nested guest NMI intercept processing
to new check_nested_events.

Signed-off-by: Cathy Avery <cavery@redhat.com>
---
 arch/x86/kvm/svm/nested.c | 21 +++++++++++++++++++++
 arch/x86/kvm/svm/svm.c    |  2 +-
 arch/x86/kvm/svm/svm.h    | 15 ---------------
 3 files changed, 22 insertions(+), 16 deletions(-)

```
#### [kvm-unit-tests PATCH 1/2] x86: nVMX: Add some corner-case VMX-preemption timer tests
##### From: Jim Mattson <jmattson@google.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Jim Mattson <jmattson@google.com>
X-Patchwork-Id: 11486479
Return-Path: <SRS0=cOhZ=56=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id AC9D91392
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 14 Apr 2020 00:10:34 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 8B9522072D
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 14 Apr 2020 00:10:34 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=google.com header.i=@google.com
 header.b="Dxqwa6hO"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728588AbgDNAKc (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 13 Apr 2020 20:10:32 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:44784 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-FAIL-OK-FAIL)
        by vger.kernel.org with ESMTP id S1727878AbgDNAKb (ORCPT
        <rfc822;kvm@vger.kernel.org>); Mon, 13 Apr 2020 20:10:31 -0400
Received: from mail-pf1-x449.google.com (mail-pf1-x449.google.com
 [IPv6:2607:f8b0:4864:20::449])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 0ACE7C0A3BDC
        for <kvm@vger.kernel.org>; Mon, 13 Apr 2020 17:10:31 -0700 (PDT)
Received: by mail-pf1-x449.google.com with SMTP id i128so1908086pfc.4
        for <kvm@vger.kernel.org>; Mon, 13 Apr 2020 17:10:31 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=date:message-id:mime-version:subject:from:to:cc;
        bh=YRE0bl+MbOZJemQI6/3rM1uBjjYWT+ZjbHxoUQ9wtoQ=;
        b=Dxqwa6hO3h2eMm0jA1G2oQJUpnCnCahrkI6Ohz7isGPExDLuwqXl4Qbt2nov2HzIio
         Pgh+u05iOAzol3TPtEsyKN59KeO6weSaIT0RQmiepTS79N6Qxp/CmXJU+1/mDxtQoMNZ
         8+hvBluchnkRkiBH3tdpoMrGHOg45+QInV2QXElQDLpiq860HePTu/kIihECKGpeNSLq
         PfWtAoavfZR4u9H5rRw3U7lVsPoKUHe83788sF8OfrwSJ2RkItNQgj5jOawBDk2j3WYN
         TNPzk59tEJ8QVY/MLePa/dheKw8Nd7vrBI1kLtrwcAymc8d7gGAppLjFbO/iEFLECcEq
         0gPA==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:date:message-id:mime-version:subject:from:to:cc;
        bh=YRE0bl+MbOZJemQI6/3rM1uBjjYWT+ZjbHxoUQ9wtoQ=;
        b=bldqcfAby/TwcFs+kldBc5mGYgg88Hxxbiu/AVoVG2/+kw1yKPp5tqdsj6ftac8+kx
         kFasignQUptzdhJYllbL7ulo2v9Wq1DIL4JtA6v/2UaGctR0kpBWbY3TsRtI2oxuWFVa
         wmt6B0QBXMn6PQJ62kT3QEzYy8iWe5DKgLZ1jPK9SXTMAoiZswtDeBdDezQZPHT8S+xr
         kr+UDHW/8uEqooBKU4PdoJSd2x9/q1o2uCFrppjn9+0ze45kM/btxlou3U6Ic0HE+bUk
         P3vriV5354yRxV89y74HYZKkDHopq513qa9kH48MgZhB8sWirCIO3SObGZ0dQT/vrCGq
         ZTOw==
X-Gm-Message-State: AGi0PubmSBUmN9wQ5FbAZg7nVwRy4nvOG6L0XheHLsMxgNKHNovn9rQO
        6M6Whp2wdg+Fl390u1GVrc5eLelq+jqi2VmXX6rWNIgNcuH38Qwqh6ocZmHQ2caicemd89gy7XE
        2Zi0rtyONTdJzE+aNDFAy6q/CkhLAFjpze2vvYcpomvg8gmRlapLKj8vTxtwR66w=
X-Google-Smtp-Source: 
 APiQypIDqlhIhVNgUbLZcXUU/8Q+TWQqbZIrN4XOzNxTArCp/mwyWyTlRLEQ1TYSQ2+eeTztkiWuDxFDI/mHsQ==
X-Received: by 2002:a17:90a:46cf:: with SMTP id
 x15mr24370313pjg.77.1586823030511;
 Mon, 13 Apr 2020 17:10:30 -0700 (PDT)
Date: Mon, 13 Apr 2020 17:10:25 -0700
Message-Id: <20200414001026.50051-1-jmattson@google.com>
Mime-Version: 1.0
X-Mailer: git-send-email 2.26.0.110.g2183baf09c-goog
Subject: [kvm-unit-tests PATCH 1/2] x86: nVMX: Add some corner-case
 VMX-preemption timer tests
From: Jim Mattson <jmattson@google.com>
To: kvm@vger.kernel.org
Cc: Jim Mattson <jmattson@google.com>,
        Oliver Upton <oupton@google.com>,
        Peter Shier <pshier@google.com>
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Verify that both injected events and debug traps that result from
pending debug exceptions take precedence over a "VMX-preemption timer
expired" VM-exit resulting from a zero-valued VMX-preemption timer.

Signed-off-by: Jim Mattson <jmattson@google.com>
Reviewed-by: Oliver Upton <oupton@google.com>
Reviewed-by: Peter Shier <pshier@google.com>
---
 x86/vmx_tests.c | 120 ++++++++++++++++++++++++++++++++++++++++++++++++
 1 file changed, 120 insertions(+)

```
#### [PATCH kvm-unit-tests] ioapic-split: fix hang, run with -smp 4
##### From: Paolo Bonzini <pbonzini@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Paolo Bonzini <pbonzini@redhat.com>
X-Patchwork-Id: 11487919
Return-Path: <SRS0=cOhZ=56=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id C8F48112C
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 14 Apr 2020 14:11:55 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id B05B820578
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 14 Apr 2020 14:11:55 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=fail reason="signature verification failed" (2048-bit key)
 header.d=gmail.com header.i=@gmail.com header.b="aBO2pfrB"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1733101AbgDNOLx (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 14 Apr 2020 10:11:53 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:35582 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1728876AbgDNOLv (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 14 Apr 2020 10:11:51 -0400
Received: from mail-wr1-x444.google.com (mail-wr1-x444.google.com
 [IPv6:2a00:1450:4864:20::444])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id CC341C061A0C
        for <kvm@vger.kernel.org>; Tue, 14 Apr 2020 07:11:50 -0700 (PDT)
Received: by mail-wr1-x444.google.com with SMTP id t14so1266547wrw.12
        for <kvm@vger.kernel.org>; Tue, 14 Apr 2020 07:11:50 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=sender:from:to:cc:subject:date:message-id:mime-version
         :content-transfer-encoding;
        bh=GvtAqeY4wcF5cHSJWbUUPZ/4lNBEU1p6u0M6rbzdBCc=;
        b=aBO2pfrBdvy7EYjt0lkrxav10RgDcxHeMPovyZwU8vw+g+8kWgsiPOk28G1QmJjYX7
         zAxHfl5TGy7nfEKlSWdxPmsv6+5bGcqj+i8sY4Jn4w79FkaVFP8HkzF7+fiDRl0359iH
         M10pW2HxIdbZcZif0EfNzEtLbwVh+c8PIB1KGVMpQ57GAoq2YTI1r9jUClWpiVZkLKwN
         sgAtqKhyxD9M+7bojsGtL7XFANgX6bcnUvIOs78H3YWdJUa4bjzd0SQA6KawoQzsAPj0
         K3xaCrLIir586+P4uNLYDQPgEndKzik6TTgi6zt+RYOURYhmKpZ8S6/+AMHJIIHUC25y
         UAJA==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:sender:from:to:cc:subject:date:message-id
         :mime-version:content-transfer-encoding;
        bh=GvtAqeY4wcF5cHSJWbUUPZ/4lNBEU1p6u0M6rbzdBCc=;
        b=fI1pG+Br89M2WFTDH5+f6XnloeL353ID6l3pVx90LNcBj7ReP9aGsrdbrLEwzPfQS0
         e2gK4udmTD5ijIRMt29ySMGMHqQfVW4TIONa9iNHijDkAk9egTRKi4vKsf5pxeS3BkCG
         bZ6teN/RWER6xPoaqKK4ZKV28YydOo8/HpsPkguwcjX0p9tSesv0Jypl3NSO/arPsl0E
         2XzBaLjG0jxSTisshgH63w6haMCiiU9gZ951p+oZGhl/LLGqHQ91mecuLq2EA3rS/G4w
         Hdf99Vi3Y7a4tjA9vii9iGO1yMozJGZHCngGWBtnKmfh5QtZYpzL0XGW4obxNiutYSB9
         4vrQ==
X-Gm-Message-State: AGi0PuZmmvgrYSnfOF+c1K81VjTJIg9lhu2GOe+zFC+72CB9qCuSi68F
        98xmlaYtyZlYXpYR+rmqmjMyPaFgEpQ=
X-Google-Smtp-Source: 
 APiQypLIIEgjLOaUzr0MvG/JAXrOODx6S+2PjlxwiDv8AqKupHULAcgatNm3qoaXjZh/6Os317/3RA==
X-Received: by 2002:a5d:6503:: with SMTP id x3mr17510221wru.153.1586873509292;
        Tue, 14 Apr 2020 07:11:49 -0700 (PDT)
Received: from donizetti.lan ([2001:b07:6468:f312:503c:7b97:e286:9d8e])
        by smtp.gmail.com with ESMTPSA id
 v1sm14637217wrv.19.2020.04.14.07.11.47
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Tue, 14 Apr 2020 07:11:48 -0700 (PDT)
From: Paolo Bonzini <pbonzini@redhat.com>
To: kvm@vger.kernel.org
Cc: vkuznets@redhat.com
Subject: [PATCH kvm-unit-tests] ioapic-split: fix hang, run with -smp 4
Date: Tue, 14 Apr 2020 16:11:47 +0200
Message-Id: <20200414141147.13028-1-pbonzini@redhat.com>
X-Mailer: git-send-email 2.24.1
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The test_ioapic_physical_destination_mode uses destination id 1, so it
cannot be run with only one processor.  Fixing that however shows that
the self-reconfiguration test is broken with split irqchip.  This should
be fixed in QEMU.

Signed-off-by: Paolo Bonzini <pbonzini@redhat.com>
---
 x86/ioapic.c      | 3 ++-
 x86/unittests.cfg | 3 ++-
 2 files changed, 4 insertions(+), 2 deletions(-)

```
#### [kvm-unit-tests PATCH] x86: nVMX: add new test for vmread/vmwrite flags preservation
##### From: Simon Smith <brigidsmith@google.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Simon Smith <brigidsmith@google.com>
X-Patchwork-Id: 11488897
Return-Path: <SRS0=cOhZ=56=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 5E4EE912
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 14 Apr 2020 18:00:26 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 3D6BD2076C
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 14 Apr 2020 18:00:26 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=google.com header.i=@google.com
 header.b="syOsEm8s"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2503163AbgDNSAY (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 14 Apr 2020 14:00:24 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:43262 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-FAIL-OK-FAIL)
        by vger.kernel.org with ESMTP id S1729303AbgDNSAT (ORCPT
        <rfc822;kvm@vger.kernel.org>); Tue, 14 Apr 2020 14:00:19 -0400
Received: from mail-vk1-xa4a.google.com (mail-vk1-xa4a.google.com
 [IPv6:2607:f8b0:4864:20::a4a])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id B7A85C061A0C
        for <kvm@vger.kernel.org>; Tue, 14 Apr 2020 11:00:17 -0700 (PDT)
Received: by mail-vk1-xa4a.google.com with SMTP id n7so514641vkf.9
        for <kvm@vger.kernel.org>; Tue, 14 Apr 2020 11:00:17 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=date:message-id:mime-version:subject:from:to:cc;
        bh=BMm6dGEKBlgf/q10PWtvycCciSc+yReyJKANE+LD6lA=;
        b=syOsEm8sjMKq4GreRebqgo5TLOe1guPJYXFxYFqGNePu0y3H6SmX8eyu+/sXyJdaVG
         MZ2mWII+HFMKLjZTtvnmo5UkF3JKtglPYWFGgMaW9cG2wrJ/Mk6Kk+gvaIpSvSiTLXAr
         Cv1YibImDH53RXmajM9WmUPeYnMVv/88gaHtDmy0u1QuAoSE0dDUIELllA9US2bIvZlh
         svGMX7C2wwQUjkpLkJW218wXHATrZPIb7t2m3b6KMRJNG/o8WrSpp8DAmBxIKc0kVli5
         z1i6sKGf70rXMSdVoDfcqepSY/6qlzJGHIUIrzxpWDWJjQkVLxSiIFEUgIwJjRXukuwJ
         gbRg==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:date:message-id:mime-version:subject:from:to:cc;
        bh=BMm6dGEKBlgf/q10PWtvycCciSc+yReyJKANE+LD6lA=;
        b=rgl+Ow3aK91/IUAVyQ06zCVuOyIokcmzvIxm+NteEzPA//4tiDVS34BC13i4U9mCEv
         zWHCRF7Lq3MaLN4Wrc0Zru7wYtOJdCYbSJSAaGdPptFrAtBeShWG4XRs8CxteJpXgbno
         jiUISeqIG+ZCUI/0Sks9f5ZSNrNei8YV8TE3UJPP8qfLIhzQ7asQFJaebVuKgXeRx+8d
         HZeLE/FeB0YcAZpVwtzJAeWHh7zwkhQyUI4RByrgzgZapsD/bP5ZPc5yUsoPMPyO3t7l
         QGHsY+CwqpKNJs2PgBIdZZyCvNbqOEobq5q7FK1HGZpXPbM0PX5+RPccobUAAirFPg/7
         WLTw==
X-Gm-Message-State: AGi0PubVfMDl4zeVTRKXaN+21LF4Ya0EFJG7m+M3wY37+3kuNMUhcYVJ
        DAs1G8oC5nluexEKJQ/BF+pD9XvD+4LxhqbuMQY8zCwmlXaHCnbKGvydgOxExcnkTfN2kkNZ2V9
        RKujuwhm4RAeo1Wo1oceAgdqbzoBnLoH+Z3p69MIB9eAH9fI1ZLvTEA3Ftbd8mFoZV09rDUI=
X-Google-Smtp-Source: 
 APiQypItApa9hKodEsxRQO9GhOePkUOBXgOCyS9b4W8kTBOrInCm/CWPUO555cqUWNMoOw7MdRXxPsHiWmcsi6Z2og==
X-Received: by 2002:ac5:cd83:: with SMTP id i3mr15918224vka.58.1586887216395;
 Tue, 14 Apr 2020 11:00:16 -0700 (PDT)
Date: Tue, 14 Apr 2020 10:59:59 -0700
Message-Id: <20200414175959.184053-1-brigidsmith@google.com>
Mime-Version: 1.0
X-Mailer: git-send-email 2.26.0.110.g2183baf09c-goog
Subject: [kvm-unit-tests PATCH] x86: nVMX: add new test for vmread/vmwrite
 flags preservation
From: Simon Smith <brigidsmith@google.com>
To: kvm@vger.kernel.org
Cc: pbonzini@redhat.com, Simon Smith <brigidsmith@google.com>,
        Jim Mattson <jmattson@google.com>,
        Peter Shier <pshier@google.com>,
        Krish Sadhukhan <krish.sadhukhan@oracle.com>
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This commit adds new unit tests for commit a4d956b93904 ("KVM: nVMX:
vmread should not set rflags to specify success in case of #PF")

The two new tests force a vmread and a vmwrite on an unmapped
address to cause a #PF and verify that the low byte of %rflags is
preserved and that %rip is not advanced.  The commit fixed a
bug in vmread, but we include a test for vmwrite as well for
completeness.

Before the aforementioned commit, the ALU flags would be incorrectly
cleared and %rip would be advanced (for vmread).

v1: https://www.spinics.net/lists/kvm/msg212817.html

Reviewed-by: Jim Mattson <jmattson@google.com>
Reviewed-by: Peter Shier <pshier@google.com>
Reviewed-by: Krish Sadhukhan <krish.sadhukhan@oracle.com>
Signed-off-by: Simon Smith <brigidsmith@google.com>
---
 x86/vmx.c | 121 ++++++++++++++++++++++++++++++++++++++++++++++++++++++
 1 file changed, 121 insertions(+)

```
#### [kvm-unit-tests PATCH] x86: VMX: test MTF VM-exit event injectionFrom: Oliver Upton <oupton@google.com>
##### From: Oliver Upton <oupton@google.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Oliver Upton <oupton@google.com>
X-Patchwork-Id: 11489345
Return-Path: <SRS0=cOhZ=56=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id F270D913
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 14 Apr 2020 21:50:04 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id DA0812076B
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 14 Apr 2020 21:50:04 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=google.com header.i=@google.com
 header.b="JdAueOO+"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1733042AbgDNVre (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 14 Apr 2020 17:47:34 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:52832 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-FAIL-OK-FAIL)
        by vger.kernel.org with ESMTP id S1728094AbgDNVre (ORCPT
        <rfc822;kvm@vger.kernel.org>); Tue, 14 Apr 2020 17:47:34 -0400
Received: from mail-vk1-xa4a.google.com (mail-vk1-xa4a.google.com
 [IPv6:2607:f8b0:4864:20::a4a])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id D35F3C061A0E
        for <kvm@vger.kernel.org>; Tue, 14 Apr 2020 14:47:33 -0700 (PDT)
Received: by mail-vk1-xa4a.google.com with SMTP id r141so832388vke.10
        for <kvm@vger.kernel.org>; Tue, 14 Apr 2020 14:47:33 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=date:in-reply-to:message-id:mime-version:references:subject:from:to
         :cc;
        bh=Q9VWneTARaSpEeqpvNS9sbRvLulbvH9sc0Nr1tReClA=;
        b=JdAueOO+3ZCjbFNV5v4z0SXow0yHMkMQ9rZP23u0W3w2VJnR/blzoMSvyhX0fVxj49
         HwFGtyUNnYn+lId93VNEb+IYi4NrUR07MD/aVl2i5TQMtQyoDVEfFupznKN8u7ayzfhq
         s40u0775XDOk9u7o3sf97qfWqrePu4+lWvI6lBwq9CAV7pSZ88P+FXgnimHJEIjMmpxy
         JpzKJmHXJwSmtvWUYWw+seK7xNWFojJlvElWZE2tN/hIZL3ESKrbaC9JfXm1bW04dJx6
         MxgvAcfsO1Vozzr6fyf4ZNC5TFyLwC/C1PmBAKMTxWexkHF5CJUrxweYcfUXtjqO0VYg
         Barg==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:date:in-reply-to:message-id:mime-version
         :references:subject:from:to:cc;
        bh=Q9VWneTARaSpEeqpvNS9sbRvLulbvH9sc0Nr1tReClA=;
        b=qYoZJ3eZQMzX3cRhMHncASoEbg+yba1urNgrbKrtsJEv3pUo8WPfdJpj91TOOwdFOc
         AE1JRVy92CX8UKh8jOCcOVxpD4LOFu6hGXV8hlR6/Gn5FAb7k2r6hU+VSBRUqlPvZb2n
         pH/7Kz6nUsonuz5tZjR/qA14rUm/08i4c0zsjOi+HSiIK6H8zQmnajtmc1D/8ejOCbHx
         uPUDNJ/saDYH0DZaAA09ze++TlAyEJPr7TN/rsyJhZz4TTIHH6OOqnV0FzxsU7binDza
         jDdmaWybHhjXVveAiglg9cuZC1c7qCspDsCrkJkBAMD2kfVr+wGZ5o+9iczgGeMATZgT
         cq5A==
X-Gm-Message-State: AGi0PuZByAVVxXJ2yT+owVdKA67xndDYV0Ksu5tBAsktm9NPQj1/eyYQ
        HuZpq8T5b9OH/1X6HMD59w/Beyw94NFYRpAyosb5+bXjyjfzN+PVXZKdPslhmy9Xrmd64d0FTAj
        ELs16yv0fixaF/a5f89Hh+40LE2OaL0I85eMUkWAGIIzI0b7uNF/7L+h3Cw==
X-Google-Smtp-Source: 
 APiQypL1GZh5+2OZI5rfeBPrqiyXR586irZyd8E2Ni/4ecOto9JhHaJNrKVkPqtmpf5FtM0UxrjLd53U/+s=
X-Received: by 2002:a67:1107:: with SMTP id 7mr2103723vsr.144.1586900852895;
 Tue, 14 Apr 2020 14:47:32 -0700 (PDT)
Date: Tue, 14 Apr 2020 21:46:36 +0000
In-Reply-To: <20200414214634.126508-1-oupton@google.com>
Message-Id: <20200414214634.126508-2-oupton@google.com>
Mime-Version: 1.0
References: <20200414214634.126508-1-oupton@google.com>
X-Mailer: git-send-email 2.26.0.110.g2183baf09c-goog
Subject: [kvm-unit-tests PATCH] x86: VMX: test MTF VM-exit event injection
From: Oliver Upton <oupton@google.com>
To: kvm@vger.kernel.org
Cc: Paolo Bonzini <pbonzini@redhat.com>,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        Oliver Upton <oupton@google.com>,
        Jim Mattson <jmattson@google.com>
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

SDM 26.6.2 describes how the VM-entry interruption-information field
may be configured to inject an MTF VM-exit upon VM-entry. Ensure that an
MTF VM-exit occurs when the VM-entry interruption-information field is
configured appropriately by the host.

Signed-off-by: Oliver Upton <oupton@google.com>
Reviewed-by: Jim Mattson <jmattson@google.com>
Reviewed-by: Peter Shier<pshier@google.com>
---
 Parent commit: b16df9e ("arch-run: Add reserved variables to the default environ")
 x86/vmx_tests.c | 13 +++++++++++--
 1 file changed, 11 insertions(+), 2 deletions(-)

```
#### [PATCH] KVM: VMX: Enable machine check support for 32bit targets
##### From: Uros Bizjak <ubizjak@gmail.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Uros Bizjak <ubizjak@gmail.com>
X-Patchwork-Id: 11486913
Return-Path: <SRS0=cOhZ=56=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id B744913B2
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 14 Apr 2020 07:14:27 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 9E59B20767
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 14 Apr 2020 07:14:27 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=gmail.com header.i=@gmail.com
 header.b="sD8tioZT"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2406465AbgDNHOZ (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 14 Apr 2020 03:14:25 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:55570 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1728832AbgDNHOX (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 14 Apr 2020 03:14:23 -0400
Received: from mail-wr1-x443.google.com (mail-wr1-x443.google.com
 [IPv6:2a00:1450:4864:20::443])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 70D41C0A3BDC;
        Tue, 14 Apr 2020 00:14:23 -0700 (PDT)
Received: by mail-wr1-x443.google.com with SMTP id j2so13057307wrs.9;
        Tue, 14 Apr 2020 00:14:23 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=from:to:cc:subject:date:message-id:mime-version
         :content-transfer-encoding;
        bh=x3FALfbpRb/mq4e1FIFz0r4wYE516t5tOEUNmJGwv9Y=;
        b=sD8tioZTnhBcjH6L2+rSL824M7aZG9iTtB5irZ6xDl5XUn0TxsVCKoCocslJY9qk1D
         QUMK04ZbdzUmNcQzoOtjLIdr79Bl1NcrqAZKv0HGiiqk59o38mgIGikN1kyXzj9LGvUG
         trJwgn+POJ8cKzgV6MMcliH/+ppSqxW3VBTz7odbRm/Mz5/H6XJr11OACjSqYq0N/EUe
         +5Rz2nkXbFapvHFeLDujZZa1dG0p8nTphlDyR5lN5iNjBIwh+UONburm4Z9sy0FoE7ao
         mqlIxgyHkAwmwoKnQ+Lqujb3TGd1Ztk8Usm+HTO42iI5sUojF+m4gtHKeCRfRpFXhaRM
         IkTA==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:mime-version
         :content-transfer-encoding;
        bh=x3FALfbpRb/mq4e1FIFz0r4wYE516t5tOEUNmJGwv9Y=;
        b=j+djeNDNXyOLwVOEmiaX9WzAVdNDSeaQ7HARkbmGxzkphFeHsMoj+R0CPTPYvzKOC6
         pi1/S55HNtkeG0OuQPnis98M5grvHC6COE+Jq9w1lby8UPRQFybuRx3HO0nLoMKQE7QG
         87sDlnsVlKskUdhmm+5PT3lxLejcAzmHw8dqnCKu2Juwp/mRMTKqEWtTjjuWmi5c2wt3
         gFG+88elbEpEMHldQBgGScwGwg8BqLw1kf4FWfUnnGSWVnjhfGqR+h0pWBAb//rkfuDU
         6VvIRh/BETIh1jIRTs9SAqy6q2WRPfMSoN884ifiSgghr6mO+uIjMES7H/uCHMMX3MNb
         h/uw==
X-Gm-Message-State: AGi0PuYh+/OqnDRh60ZxgcrL7mLmp2J3iq3Dcb6yNykNDcZi7zrOA3cz
        esQzqXd15IcojhWUc9SuhAQf9m3HX7w=
X-Google-Smtp-Source: 
 APiQypLn3az45GzTgOtTi63CeNHJIlthS9496tL4dDm8jAxQNFlA0cvcDp1+Tt4vp5eZTg2jK1RKDg==
X-Received: by 2002:a5d:6885:: with SMTP id h5mr10120554wru.151.1586848461794;
        Tue, 14 Apr 2020 00:14:21 -0700 (PDT)
Received: from localhost.localdomain (93-103-18-160.static.t-2.net.
 [93.103.18.160])
        by smtp.gmail.com with ESMTPSA id
 a67sm18325900wmc.30.2020.04.14.00.14.20
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Tue, 14 Apr 2020 00:14:21 -0700 (PDT)
From: Uros Bizjak <ubizjak@gmail.com>
To: kvm@vger.kernel.org
Cc: Uros Bizjak <ubizjak@gmail.com>,
        Paolo Bonzini <pbonzini@redhat.com>,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        stable@vger.kernel.org
Subject: [PATCH] KVM: VMX: Enable machine check support for 32bit targets
Date: Tue, 14 Apr 2020 09:14:14 +0200
Message-Id: <20200414071414.45636-1-ubizjak@gmail.com>
X-Mailer: git-send-email 2.25.2
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

There is no reason to limit the use of do_machine_check
to 64bit targets. MCE handling works for both target familes.

Cc: Paolo Bonzini <pbonzini@redhat.com>
Cc: Sean Christopherson <sean.j.christopherson@intel.com>
Cc: stable@vger.kernel.org
Fixes: a0861c02a981 ("KVM: Add VT-x machine check support")
Signed-off-by: Uros Bizjak <ubizjak@gmail.com>
---
 arch/x86/kvm/vmx/vmx.c | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
#### [PATCH v11 01/13] iommu: Introduce attach/detach_pasid_table API
##### From: Eric Auger <eric.auger@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Eric Auger <eric.auger@redhat.com>
X-Patchwork-Id: 11488161
Return-Path: <SRS0=cOhZ=56=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 30FBC913
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 14 Apr 2020 15:06:54 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 140A920768
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 14 Apr 2020 15:06:54 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="fSdRE4Bz"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2407305AbgDNPGw (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 14 Apr 2020 11:06:52 -0400
Received: from us-smtp-1.mimecast.com ([205.139.110.61]:32885 "EHLO
        us-smtp-delivery-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S2407280AbgDNPGs (ORCPT
        <rfc822;kvm@vger.kernel.org>); Tue, 14 Apr 2020 11:06:48 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1586876805;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding:
         in-reply-to:in-reply-to:references:references;
        bh=nXEIy1AaCe7k9Zzu1LjEW9kCRY7hQocKepX00033FfY=;
        b=fSdRE4BzNvQ8Gg43HekUoaKI8s7gl4GlCzFmsZ35k9/mN1X5891uX7Yoorrg7P3N4RK46f
        4ZxA04A978uXmfDl0y4lZWxSEdMZcC3+K45exYLHH7unq/X4PYCzzGc5vxpHj7kK2ENiGM
        AZtzeVHt45mBL0kXCSR0LpXtuiUpDYo=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-434-zomV_ajINsiNIT1iLw1pIA-1; Tue, 14 Apr 2020 11:06:41 -0400
X-MC-Unique: zomV_ajINsiNIT1iLw1pIA-1
Received: from smtp.corp.redhat.com (int-mx08.intmail.prod.int.phx2.redhat.com
 [10.5.11.23])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 395C2107ACC9;
        Tue, 14 Apr 2020 15:06:39 +0000 (UTC)
Received: from laptop.redhat.com (ovpn-115-53.ams2.redhat.com [10.36.115.53])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 9DD6019C69;
        Tue, 14 Apr 2020 15:06:34 +0000 (UTC)
From: Eric Auger <eric.auger@redhat.com>
To: eric.auger.pro@gmail.com, eric.auger@redhat.com,
        iommu@lists.linux-foundation.org, linux-kernel@vger.kernel.org,
        kvm@vger.kernel.org, kvmarm@lists.cs.columbia.edu, will@kernel.org,
        joro@8bytes.org, maz@kernel.org, robin.murphy@arm.com
Cc: jean-philippe@linaro.org, zhangfei.gao@linaro.org,
        shameerali.kolothum.thodi@huawei.com, alex.williamson@redhat.com,
        jacob.jun.pan@linux.intel.com, yi.l.liu@intel.com,
        peter.maydell@linaro.org, zhangfei.gao@gmail.com, tn@semihalf.com,
        zhangfei.gao@foxmail.com, bbhushan2@marvell.com
Subject: [PATCH v11 01/13] iommu: Introduce attach/detach_pasid_table API
Date: Tue, 14 Apr 2020 17:05:55 +0200
Message-Id: <20200414150607.28488-2-eric.auger@redhat.com>
In-Reply-To: <20200414150607.28488-1-eric.auger@redhat.com>
References: <20200414150607.28488-1-eric.auger@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.84 on 10.5.11.23
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Jacob Pan <jacob.jun.pan@linux.intel.com>

In virtualization use case, when a guest is assigned
a PCI host device, protected by a virtual IOMMU on the guest,
the physical IOMMU must be programmed to be consistent with
the guest mappings. If the physical IOMMU supports two
translation stages it makes sense to program guest mappings
onto the first stage/level (ARM/Intel terminology) while the host
owns the stage/level 2.

In that case, it is mandated to trap on guest configuration
settings and pass those to the physical iommu driver.

This patch adds a new API to the iommu subsystem that allows
to set/unset the pasid table information.

A generic iommu_pasid_table_config struct is introduced in
a new iommu.h uapi header. This is going to be used by the VFIO
user API.

Signed-off-by: Jean-Philippe Brucker <jean-philippe.brucker@arm.com>
Signed-off-by: Liu, Yi L <yi.l.liu@linux.intel.com>
Signed-off-by: Ashok Raj <ashok.raj@intel.com>
Signed-off-by: Jacob Pan <jacob.jun.pan@linux.intel.com>
Signed-off-by: Eric Auger <eric.auger@redhat.com>
Reviewed-by: Jean-Philippe Brucker <jean-philippe.brucker@arm.com>
---
 drivers/iommu/iommu.c      | 19 ++++++++++++++
 include/linux/iommu.h      | 18 ++++++++++++++
 include/uapi/linux/iommu.h | 51 ++++++++++++++++++++++++++++++++++++++
 3 files changed, 88 insertions(+)

```
#### [PATCH v2] kvm_host: unify VM_STAT and VCPU_STAT definitions in a single place
##### From: Emanuele Giuseppe Esposito <eesposit@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Emanuele Giuseppe Esposito <eesposit@redhat.com>
X-Patchwork-Id: 11488455
Return-Path: <SRS0=cOhZ=56=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 97E3015AB
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 14 Apr 2020 15:57:05 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 615C12076B
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 14 Apr 2020 15:57:05 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="PsXsgq/l"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1732329AbgDNP5D (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 14 Apr 2020 11:57:03 -0400
Received: from us-smtp-1.mimecast.com ([205.139.110.61]:20895 "EHLO
        us-smtp-delivery-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S1732341AbgDNP5A (ORCPT
        <rfc822;kvm@vger.kernel.org>); Tue, 14 Apr 2020 11:57:00 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1586879817;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=oe08nHT0YFTUNv7T5Bw/0FcNuC5hFqGnfJa7ybBFgpg=;
        b=PsXsgq/lCa2Iyke6/8LR53WKZ6TAlDADHh5XpCGMfk0qWvvNGh4jPT6of97HiCKmewPayS
        Bkd1MjRLw+nwx8pnTfyypBY1P6pvN6EvSFfPoZv5racdCj0HWuvZFOydFl6fFditlS59Zn
        NTexpF2ELkukFlloDD0sGYXfgl3Nr7I=
Received: from mail-wr1-f72.google.com (mail-wr1-f72.google.com
 [209.85.221.72]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-380-6SDrwwLzMn69On-eEAmIwg-1; Tue, 14 Apr 2020 11:56:55 -0400
X-MC-Unique: 6SDrwwLzMn69On-eEAmIwg-1
Received: by mail-wr1-f72.google.com with SMTP id s11so4057181wru.6
        for <kvm@vger.kernel.org>; Tue, 14 Apr 2020 08:56:55 -0700 (PDT)
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:mime-version
         :content-transfer-encoding;
        bh=oe08nHT0YFTUNv7T5Bw/0FcNuC5hFqGnfJa7ybBFgpg=;
        b=OrT0oMCVdxf21GcFanmDVueKv9PF6IgmW3bAqngHVQGlBhUNuYgsKFOjhtIDvXBqDH
         k63zTPPueiIHj0FhPyqTZa1cQ22lhtt36stUelLoldV1aaZS+Lsj5JCrxhL1XC5coVTg
         inqo4LVSgpzybSENGv7o4TXXNHly51DVvxE6Zvb218l233GI7Naw4GZSBERW0oGOwf0G
         fb+1CH/NOt0HPgyl0jcf8+H2r7GQ7oRYsRq7izhpStWoTOsLhEjUnqTUJKbrNXkSVPd3
         jgxEkFnUX1hlfDf6fNSZQ4PJrxwX7IcwTOlyGUSUVHKR/xEpS0ADWSHlcpIC2qg2aPOp
         joyA==
X-Gm-Message-State: AGi0PuaEt5oMKCEPnOGlcvIAAVz1LNjNquCOwQKKKbI74sGiZoxf1jZ+
        c8OhiL48CFtvkA04G0Hu0IP+kv4S/FQsfrm1VYWPD6WXin4U73lu1wSaBEAJWY/sfuVyz7kOBUs
        frhFHAzjXWcxY
X-Received: by 2002:a7b:c250:: with SMTP id b16mr570088wmj.100.1586879813625;
        Tue, 14 Apr 2020 08:56:53 -0700 (PDT)
X-Google-Smtp-Source: 
 APiQypIIJFGhe7FS7TJ0jpwjeqAGVSQCIjinsBY1w0yUfN55I6RH8qf8Nj6ETgGZBVwtCZSrRz/M/w==
X-Received: by 2002:a7b:c250:: with SMTP id b16mr570035wmj.100.1586879813227;
        Tue, 14 Apr 2020 08:56:53 -0700 (PDT)
Received: from localhost.localdomain.com ([194.230.155.210])
        by smtp.gmail.com with ESMTPSA id
 s6sm18865345wmh.17.2020.04.14.08.56.51
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Tue, 14 Apr 2020 08:56:52 -0700 (PDT)
From: Emanuele Giuseppe Esposito <eesposit@redhat.com>
To: kvm@vger.kernel.org
Cc: =?utf-8?q?Philippe_Mathieu-Daud=C3=A9?= <f4bug@amsat.org>,
 Marc Zyngier <maz@kernel.org>, James Morse <james.morse@arm.com>,
 Julien Thierry <julien.thierry.kdev@gmail.com>,
 Suzuki K Poulose <suzuki.poulose@arm.com>,
 Paul Mackerras <paulus@ozlabs.org>,
 Christian Borntraeger <borntraeger@de.ibm.com>,
 Janosch Frank <frankja@linux.ibm.com>, David Hildenbrand <david@redhat.com>,
 Cornelia Huck <cohuck@redhat.com>, Paolo Bonzini <pbonzini@redhat.com>,
 Sean Christopherson <sean.j.christopherson@intel.com>,
 Vitaly Kuznetsov <vkuznets@redhat.com>, Wanpeng Li <wanpengli@tencent.com>,
 Jim Mattson <jmattson@google.com>, Joerg Roedel <joro@8bytes.org>,
 linux-arm-kernel@lists.infradead.org, kvmarm@lists.cs.columbia.edu,
 linux-kernel@vger.kernel.org, linux-mips@vger.kernel.org,
 kvm-ppc@vger.kernel.org, linux-s390@vger.kernel.org,
 Emanuele Giuseppe Esposito <eesposit@redhat.com>
Subject: [PATCH v2] kvm_host: unify VM_STAT and VCPU_STAT definitions in a
 single place
Date: Tue, 14 Apr 2020 17:56:25 +0200
Message-Id: <20200414155625.20559-1-eesposit@redhat.com>
X-Mailer: git-send-email 2.25.2
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The macros VM_STAT and VCPU_STAT are redundantly implemented in multiple
files, each used by a different architecure to initialize the debugfs
entries for statistics. Since they all have the same purpose, they can be
unified in a single common definition in include/linux/kvm_host.h

Signed-off-by: Emanuele Giuseppe Esposito <eesposit@redhat.com>
---
 arch/arm64/kvm/guest.c    |  23 ++---
 arch/mips/kvm/mips.c      |  61 ++++++------
 arch/powerpc/kvm/book3s.c |  61 ++++++------
 arch/powerpc/kvm/booke.c  |  41 ++++----
 arch/s390/kvm/kvm-s390.c  | 203 +++++++++++++++++++-------------------
 arch/x86/kvm/x86.c        |  80 +++++++--------
 include/linux/kvm_host.h  |   5 +
 7 files changed, 231 insertions(+), 243 deletions(-)

```
#### [PATCH v2] kvm: nVMX: reflect MTF VM-exits if injected by L1From: Oliver Upton <oupton@google.com>
##### From: Oliver Upton <oupton@google.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Oliver Upton <oupton@google.com>
X-Patchwork-Id: 11489373
Return-Path: <SRS0=cOhZ=56=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id E25661392
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 14 Apr 2020 22:48:10 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id BFC0720775
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 14 Apr 2020 22:48:10 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=google.com header.i=@google.com
 header.b="dV6tEKoK"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2633620AbgDNWsI (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 14 Apr 2020 18:48:08 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:34090 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-FAIL-OK-FAIL)
        by vger.kernel.org with ESMTP id S1729551AbgDNWsH (ORCPT
        <rfc822;kvm@vger.kernel.org>); Tue, 14 Apr 2020 18:48:07 -0400
Received: from mail-vk1-xa49.google.com (mail-vk1-xa49.google.com
 [IPv6:2607:f8b0:4864:20::a49])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id ABA36C061A0C
        for <kvm@vger.kernel.org>; Tue, 14 Apr 2020 15:48:05 -0700 (PDT)
Received: by mail-vk1-xa49.google.com with SMTP id c139so892215vke.5
        for <kvm@vger.kernel.org>; Tue, 14 Apr 2020 15:48:05 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=date:message-id:mime-version:subject:from:to:cc;
        bh=O140dz1UM5P9qq9rzXqnDmO1pLCKTxlVE6xQq25XpnA=;
        b=dV6tEKoK/TbFqoV0FugtBkLa5SUTVSPbeaUZgSTk77Cb92gAz+B2KjYl4dwQ3yeB6D
         4JnZyJLBFfWj8KHWnXzvomTV5p5Yhgi85TQZtb7gtk0XnsrzTd5UNbwi+WBgzQ8I1cdn
         ddliptXti2uhpdn8woxWAqXncCW2gm77tSMeyrFCpvV64E+O1QMdc3Ldo2UUqqWs8dbN
         LWtgCaO3y9D6qqxoyM5kdu/xhUAu3i4oCn2LYkEQdLAKXfSJXITy/FCqqmqp86IDjBAS
         xKfOy00vsGpdWGwYkjb24USYHoDrv9GykgXCqJwMh7dGOiS/r4Wd8ugyUEZLilYJRcf5
         mFug==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:date:message-id:mime-version:subject:from:to:cc;
        bh=O140dz1UM5P9qq9rzXqnDmO1pLCKTxlVE6xQq25XpnA=;
        b=Sc+rknkxfCUltDaxiULJBFwlZ2SxHmRwsq/JrTXgm9ICUjlIEF3z1umz5BUJJUxWQJ
         4UOMidhkpEg8NLHFC1/51Bov9IZQmFcPEz5Z5qwAIcERomVg583FDx6pXU7LtU7KKace
         Nt+Pm8S3LQvpFO/o0ZY/+Y8O2OqNolhD9MiE7IrQldg2nI928wRKQv5GMnDGhCmd/vv+
         mbg2HTosP0l85bujFOEWJitAltBoGgWTINA1Op1uYR9btLUcKmSzO6tesZiLGPuKPMwh
         KihJ5zVBpcuc2gL3K899jL2R/BolKGsU1VMaZCIIryhpSHDgwtrlraxW2sZYzgiGmW87
         59vQ==
X-Gm-Message-State: AGi0PuZvJMAQVbZsI6d2wtvF1LsVA01if/OC4a1/A+nc2hDX04eFxxu1
        sW8BbaDCqZUQjwUoi8Yuf4LJeEad1/Nb0TKRZ9eqpQ+iohr9EcCbU1SWxBE9/awC1rqIe95UQMd
        gb0eewpTQlG4cQdaBkaREjFlXh5Tv6U2m91ZdsvgD+EWKvmsMl73kM7U90Q==
X-Google-Smtp-Source: 
 APiQypIkMMqQAECOPkW/5WX4ViVLxfT7fkabSUggSOVD3Hy+iHpPaMwoyJ8YQWdXoene1XGtNX+CrAqoJug=
X-Received: by 2002:ac5:c3ce:: with SMTP id t14mr7320325vkk.60.1586904484376;
 Tue, 14 Apr 2020 15:48:04 -0700 (PDT)
Date: Tue, 14 Apr 2020 22:47:45 +0000
Message-Id: <20200414224746.240324-1-oupton@google.com>
Mime-Version: 1.0
X-Mailer: git-send-email 2.26.0.110.g2183baf09c-goog
Subject: [PATCH v2] kvm: nVMX: reflect MTF VM-exits if injected by L1
From: Oliver Upton <oupton@google.com>
To: kvm@vger.kernel.org
Cc: Paolo Bonzini <pbonzini@redhat.com>,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        Oliver Upton <oupton@google.com>,
        Peter Shier <pshier@google.com>,
        Jim Mattson <jmattson@google.com>
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

According to SDM 26.6.2, it is possible to inject an MTF VM-exit via the
VM-entry interruption-information field regardless of the 'monitor trap
flag' VM-execution control. KVM appropriately copies the VM-entry
interruption-information field from vmcs12 to vmcs02. However, if L1
has not set the 'monitor trap flag' VM-execution control, KVM fails to
reflect the subsequent MTF VM-exit into L1.

Fix this by consulting the VM-entry interruption-information field of
vmcs12 to determine if L1 has injected the MTF VM-exit. If so, reflect
the exit, regardless of the 'monitor trap flag' VM-execution control.

Fixes: 5f3d45e7f282 ("kvm/x86: add support for MONITOR_TRAP_FLAG")
Signed-off-by: Oliver Upton <oupton@google.com>
Reviewed-by: Peter Shier <pshier@google.com>
Reviewed-by: Jim Mattson <jmattson@google.com>
---
 Parent commit: dbef2808af6c5 ("KVM: VMX: fix crash cleanup when KVM wasn't used")

 v1 => v2:
 - removed unused 'struct kvm_vcpu *vcpu' from the signature of helper
   function

 arch/x86/kvm/vmx/nested.c | 19 ++++++++++++++++++-
 1 file changed, 18 insertions(+), 1 deletion(-)

```
#### [PATCH kvmtool 01/18] Makefile: Use correct objcopy binary when cross-compiling for x86_64
##### From: Alexandru Elisei <alexandru.elisei@arm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Alexandru Elisei <alexandru.elisei@arm.com>
X-Patchwork-Id: 11487933
Return-Path: <SRS0=cOhZ=56=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 31E3D112C
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 14 Apr 2020 14:40:05 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 2361A2064A
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 14 Apr 2020 14:40:05 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2391042AbgDNOkC (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 14 Apr 2020 10:40:02 -0400
Received: from foss.arm.com ([217.140.110.172]:57102 "EHLO foss.arm.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S2391034AbgDNOj7 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 14 Apr 2020 10:39:59 -0400
Received: from usa-sjc-imap-foss1.foss.arm.com (unknown [10.121.207.14])
        by usa-sjc-mx-foss1.foss.arm.com (Postfix) with ESMTP id A51C831B;
        Tue, 14 Apr 2020 07:39:58 -0700 (PDT)
Received: from e123195-lin.cambridge.arm.com (e123195-lin.cambridge.arm.com
 [10.1.196.63])
        by usa-sjc-imap-foss1.foss.arm.com (Postfix) with ESMTPA id
 B5FCB3F73D;
        Tue, 14 Apr 2020 07:39:57 -0700 (PDT)
From: Alexandru Elisei <alexandru.elisei@arm.com>
To: kvm@vger.kernel.org
Cc: will@kernel.org, julien.thierry.kdev@gmail.com,
        andre.przywara@arm.com, sami.mujawar@arm.com,
        lorenzo.pieralisi@arm.com
Subject: [PATCH kvmtool 01/18] Makefile: Use correct objcopy binary when
 cross-compiling for x86_64
Date: Tue, 14 Apr 2020 15:39:29 +0100
Message-Id: <20200414143946.1521-2-alexandru.elisei@arm.com>
X-Mailer: git-send-email 2.20.1
In-Reply-To: <20200414143946.1521-1-alexandru.elisei@arm.com>
References: <20200414143946.1521-1-alexandru.elisei@arm.com>
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Use the compiler toolchain version of objcopy instead of the native one
when cross-compiling for the x86_64 architecture.

Reviewed-by: Andre Przywara <andre.przywara@arm.com>
Tested-by: Andre Przywara <andre.przywara@arm.com>
Signed-off-by: Alexandru Elisei <alexandru.elisei@arm.com>
---
 Makefile | 3 ++-
 1 file changed, 2 insertions(+), 1 deletion(-)

```
#### [PATCH] vhost: do not enable VHOST_MENU by default
##### From: Jason Wang <jasowang@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Jason Wang <jasowang@redhat.com>
X-Patchwork-Id: 11486553
Return-Path: <SRS0=cOhZ=56=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 505A8174A
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 14 Apr 2020 02:45:03 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 25A2820768
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 14 Apr 2020 02:45:03 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="dKcNSACj"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2404202AbgDNCo6 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 13 Apr 2020 22:44:58 -0400
Received: from us-smtp-delivery-1.mimecast.com ([207.211.31.120]:51197 "EHLO
        us-smtp-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org
        with ESMTP id S2404195AbgDNCo6 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 13 Apr 2020 22:44:58 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1586832296;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=1JQT2Xm0ZoYwsGUbbr9yEBymLjUdcqLv7hF40ghU85w=;
        b=dKcNSACjNqwLq6SxdH4RGRTN9SCauDFEtOCNqdf9pebrbcAUDQQC+bFh8surPtxjuKYpuw
        HR3ZSxpHdwChNY6XtVcZj6phK1nHnshAd5Eb2BseEDF8x1Yylgx8XZ6TzF5yaB4WZnVVVN
        WZHH5gEOoV1yxP5V22ppkKiwpVEVzOk=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-223-DsspG1W7MT6P3LkdYibTNg-1; Mon, 13 Apr 2020 22:44:52 -0400
X-MC-Unique: DsspG1W7MT6P3LkdYibTNg-1
Received: from smtp.corp.redhat.com (int-mx02.intmail.prod.int.phx2.redhat.com
 [10.5.11.12])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 359E6107ACC4;
        Tue, 14 Apr 2020 02:44:49 +0000 (UTC)
Received: from jason-ThinkPad-X1-Carbon-6th.redhat.com
 (ovpn-13-119.pek2.redhat.com [10.72.13.119])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 199AB60BE1;
        Tue, 14 Apr 2020 02:44:40 +0000 (UTC)
From: Jason Wang <jasowang@redhat.com>
To: mst@redhat.com, jasowang@redhat.com
Cc: linux-mips@vger.kernel.org, linux-kernel@vger.kernel.org,
        linuxppc-dev@lists.ozlabs.org, linux-s390@vger.kernel.org,
        kvm@vger.kernel.org, virtualization@lists.linux-foundation.org,
        netdev@vger.kernel.org, geert@linux-m68k.org,
        Thomas Bogendoerfer <tsbogend@alpha.franken.de>,
        Benjamin Herrenschmidt <benh@kernel.crashing.org>,
        Paul Mackerras <paulus@samba.org>,
        Michael Ellerman <mpe@ellerman.id.au>,
        Heiko Carstens <heiko.carstens@de.ibm.com>,
        Vasily Gorbik <gor@linux.ibm.com>,
        Christian Borntraeger <borntraeger@de.ibm.com>
Subject: [PATCH] vhost: do not enable VHOST_MENU by default
Date: Tue, 14 Apr 2020 10:44:38 +0800
Message-Id: <20200414024438.19103-1-jasowang@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.12
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

We try to keep the defconfig untouched after decoupling CONFIG_VHOST
out of CONFIG_VIRTUALIZATION in commit 20c384f1ea1a
("vhost: refine vhost and vringh kconfig") by enabling VHOST_MENU by
default. Then the defconfigs can keep enabling CONFIG_VHOST_NET
without the caring of CONFIG_VHOST.

But this will leave a "CONFIG_VHOST_MENU=y" in all defconfigs and even
for the ones that doesn't want vhost. So it actually shifts the
burdens to the maintainers of all other to add "CONFIG_VHOST_MENU is
not set". So this patch tries to enable CONFIG_VHOST explicitly in
defconfigs that enables CONFIG_VHOST_NET and CONFIG_VHOST_VSOCK.

Cc: Thomas Bogendoerfer <tsbogend@alpha.franken.de>
Cc: Benjamin Herrenschmidt <benh@kernel.crashing.org>
Cc: Paul Mackerras <paulus@samba.org>
Cc: Michael Ellerman <mpe@ellerman.id.au>
Cc: Heiko Carstens <heiko.carstens@de.ibm.com>
Cc: Vasily Gorbik <gor@linux.ibm.com>
Cc: Christian Borntraeger <borntraeger@de.ibm.com>
Reported-by: Geert Uytterhoeven <geert@linux-m68k.org>
Signed-off-by: Jason Wang <jasowang@redhat.com>
Acked-by: Michael Ellerman <mpe@ellerman.id.au> (powerpc)
Acked-by: Christian Borntraeger <borntraeger@de.ibm.com>
Acked-by: Thomas Bogendoerfer <tsbogend@alpha.franken.de>
Reported-by: kbuild test robot <lkp@intel.com>
---
 arch/mips/configs/malta_kvm_defconfig  |  1 +
 arch/powerpc/configs/powernv_defconfig |  1 +
 arch/powerpc/configs/ppc64_defconfig   |  1 +
 arch/powerpc/configs/pseries_defconfig |  1 +
 arch/s390/configs/debug_defconfig      |  1 +
 arch/s390/configs/defconfig            |  1 +
 drivers/vhost/Kconfig                  | 18 +++++-------------
 7 files changed, 11 insertions(+), 13 deletions(-)

```
