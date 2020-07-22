#### [PATCH 1/2] KVM: LAPIC: Prevent setting the tscdeadline timer if the lapic is hw disabled
##### From: Wanpeng Li <kernellwp@gmail.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Wanpeng Li <kernellwp@gmail.com>
X-Patchwork-Id: 11675253
Return-Path: <SRS0=uGOU=BA=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 7AD6E13A4
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 21 Jul 2020 09:24:43 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 638B620657
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 21 Jul 2020 09:24:43 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=gmail.com header.i=@gmail.com
 header.b="Q9qnbLp1"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728632AbgGUJYj (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 21 Jul 2020 05:24:39 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:35262 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726089AbgGUJYj (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 21 Jul 2020 05:24:39 -0400
Received: from mail-pg1-x543.google.com (mail-pg1-x543.google.com
 [IPv6:2607:f8b0:4864:20::543])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 51563C061794;
        Tue, 21 Jul 2020 02:24:39 -0700 (PDT)
Received: by mail-pg1-x543.google.com with SMTP id o13so11687968pgf.0;
        Tue, 21 Jul 2020 02:24:39 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=from:to:cc:subject:date:message-id;
        bh=4CU667nkvV00ipZaKMgd7BNRAsDjboapT6L5BW02bj8=;
        b=Q9qnbLp1dDGcoPGLtm89abpod6WY1ZGMxNJ2YnnwmafnEDB9+Ylou2LL6Sluy7IeAL
         seq4i+lgqzmj2CoSnRIYqG/QoMRbCd1oaaAkau5NxIkmWJr509ttZoK1IxhVznPA/T0U
         iR9weCEMN2EL/H6S+cyazSbUBMUaRhQe297qRWAGmTahQcsgFOPuDpXP0wpr0uB5zzyj
         Ki1c+fQwdlYFdvTm50XHCc0IJ1AjnmXj9EIvrPzUyp/6f7mz9i56QqWODsV+/VpMhdMY
         XdUGRwa2C3RbbJ+Ern5Nh0S7F/6m4WdAWRg5Xij/cESF/FfeMhmas+XmfKO+xqnPpRDe
         urqg==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id;
        bh=4CU667nkvV00ipZaKMgd7BNRAsDjboapT6L5BW02bj8=;
        b=gv60waYW88IKWITfujqsRkPog7aFO807NEbpGBpt+Qb0+9gVNPnYL6DRLl3ZFZzSD2
         U0q8u0dJjUGwgnx/cuRqfwbg0C5BT9xZOLdqxTB3IxPaoDCOWlVLLkkk5QZ4P/OuqgG3
         HvKr9768z5EE/BRDYFcimuJ2B2uMHRjbeR33zScqoWlR89HtoexuaxrWBIvL+HOXhByq
         eMpxL8iwd7ojXgfd6k4bVk/Fo9yO1pGC910XAv4wNnHqb0J9uZn0T9/gO2cQAYDok5dh
         MlaKX3eooo2V8DKPBI3YYEtZ6Wu3bR33ecHQouVljnxM37+CIWXYwOGLHkYAiCf2g/4y
         sAHA==
X-Gm-Message-State: AOAM531l0AIZDmxgitnXPe68atI/U4/R+tciRPIM0LkB0GPitJzdD7wn
        BYGXW42V4X917MmTvDSqkLf3Eewu
X-Google-Smtp-Source: 
 ABdhPJwQ7uwVn4YaUJ0trVo3VulSj443x0CxxyZZktIAxMWDWRRi/5o9YakQzf2hxB1OlDyRceOZOQ==
X-Received: by 2002:aa7:930b:: with SMTP id 11mr24277068pfj.320.1595323478678;
        Tue, 21 Jul 2020 02:24:38 -0700 (PDT)
Received: from localhost.localdomain ([103.7.29.6])
        by smtp.googlemail.com with ESMTPSA id
 l9sm2337685pjy.2.2020.07.21.02.24.36
        (version=TLS1_2 cipher=ECDHE-ECDSA-AES128-GCM-SHA256 bits=128/128);
        Tue, 21 Jul 2020 02:24:38 -0700 (PDT)
From: Wanpeng Li <kernellwp@gmail.com>
X-Google-Original-From: Wanpeng Li <wanpengli@tencent.com>
To: linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Cc: Paolo Bonzini <pbonzini@redhat.com>,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>
Subject: [PATCH 1/2] KVM: LAPIC: Prevent setting the tscdeadline timer if the
 lapic is hw disabled
Date: Tue, 21 Jul 2020 17:24:27 +0800
Message-Id: <1595323468-4380-1-git-send-email-wanpengli@tencent.com>
X-Mailer: git-send-email 2.7.4
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Wanpeng Li <wanpengli@tencent.com>

Prevent setting the tscdeadline timer if the lapic is hw disabled.

Signed-off-by: Wanpeng Li <wanpengli@tencent.com>
---
 arch/x86/kvm/lapic.c | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
#### [PATCH RFC v2 01/18] platform-msi: Introduce platform_msi_opsFrom: Dave Jiang <dave.jiang@intel.com>
##### From: Dave Jiang <dave.jiang@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Dave Jiang <dave.jiang@intel.com>
X-Patchwork-Id: 11675953
Return-Path: <SRS0=uGOU=BA=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 060581392
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 21 Jul 2020 16:02:29 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id E395A2077D
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 21 Jul 2020 16:02:28 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1730085AbgGUQCZ (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 21 Jul 2020 12:02:25 -0400
Received: from mga01.intel.com ([192.55.52.88]:47301 "EHLO mga01.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726919AbgGUQCY (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 21 Jul 2020 12:02:24 -0400
IronPort-SDR: 
 QWAXBytFfS23jUq3AZPabo7CCHI3HCBNcPGKgtVIwAfuSV8kp1OUuYgKJXSK9ghFrjd383Zq3l
 JAh59aoRU11Q==
X-IronPort-AV: E=McAfee;i="6000,8403,9689"; a="168306135"
X-IronPort-AV: E=Sophos;i="5.75,379,1589266800";
   d="scan'208";a="168306135"
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from fmsmga005.fm.intel.com ([10.253.24.32])
  by fmsmga101.fm.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 21 Jul 2020 09:02:23 -0700
IronPort-SDR: 
 oGDRW/XIcPpgjsIGuxrTgLnNDsN8b7K6pe/VoyFKNQGDe+1KJvKAGLUV3GkHwdmbNnj/KadSMi
 h1OWazEl1d7w==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.75,379,1589266800";
   d="scan'208";a="488133813"
Received: from djiang5-desk3.ch.intel.com ([143.182.136.137])
  by fmsmga005.fm.intel.com with ESMTP; 21 Jul 2020 09:02:21 -0700
Subject: [PATCH RFC v2 01/18] platform-msi: Introduce platform_msi_ops
From: Dave Jiang <dave.jiang@intel.com>
To: vkoul@kernel.org, megha.dey@intel.com, maz@kernel.org,
        bhelgaas@google.com, rafael@kernel.org, gregkh@linuxfoundation.org,
        tglx@linutronix.de, hpa@zytor.com, alex.williamson@redhat.com,
        jacob.jun.pan@intel.com, ashok.raj@intel.com, jgg@mellanox.com,
        yi.l.liu@intel.com, baolu.lu@intel.com, kevin.tian@intel.com,
        sanjay.k.kumar@intel.com, tony.luck@intel.com, jing.lin@intel.com,
        dan.j.williams@intel.com, kwankhede@nvidia.com,
        eric.auger@redhat.com, parav@mellanox.com, jgg@mellanox.com,
        rafael@kernel.org, dave.hansen@intel.com, netanelg@mellanox.com,
        shahafs@mellanox.com, yan.y.zhao@linux.intel.com,
        pbonzini@redhat.com, samuel.ortiz@intel.com, mona.hossain@intel.com
Cc: dmaengine@vger.kernel.org, linux-kernel@vger.kernel.org,
        x86@kernel.org, linux-pci@vger.kernel.org, kvm@vger.kernel.org
Date: Tue, 21 Jul 2020 09:02:21 -0700
Message-ID: 
 <159534734176.28840.13007887237870414700.stgit@djiang5-desk3.ch.intel.com>
In-Reply-To: 
 <159534667974.28840.2045034360240786644.stgit@djiang5-desk3.ch.intel.com>
References: 
 <159534667974.28840.2045034360240786644.stgit@djiang5-desk3.ch.intel.com>
User-Agent: StGit/unknown-version
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Megha Dey <megha.dey@intel.com>

platform-msi.c provides a generic way to handle non-PCI message
signaled interrupts. However, it assumes that only the message
needs to be customized. Given that an MSI is just a write
transaction, some devices may need custom callbacks to
mask/unmask their interrupts.

Hence, introduce a new structure platform_msi_ops, which would
provide device specific write function for now and introduce device
device specific callbacks (mask/unmask), in subsequent patches.

Devices may find more efficient ways to store addr/data pairs
than what is recommended by the PCI sig. (For e.g. the storage of
the vector might not be resident on the device. Consider GPGPU
for instance, where the vector could be part of the execution
context instead of being stored on the device.)

Reviewed-by: Dan Williams <dan.j.williams@intel.com>
Signed-off-by: Megha Dey <megha.dey@intel.com>
Signed-off-by: Dave Jiang <dave.jiang@intel.com>
---
 drivers/base/platform-msi.c          |   29 +++++++++++++++--------------
 drivers/dma/mv_xor_v2.c              |    6 +++++-
 drivers/dma/qcom/hidma.c             |    6 +++++-
 drivers/iommu/arm-smmu-v3.c          |    6 +++++-
 drivers/irqchip/irq-mbigen.c         |    8 ++++++--
 drivers/irqchip/irq-mvebu-icu.c      |    6 +++++-
 drivers/mailbox/bcm-flexrm-mailbox.c |    6 +++++-
 drivers/perf/arm_smmuv3_pmu.c        |    6 +++++-
 include/linux/msi.h                  |   20 ++++++++++++++------
 9 files changed, 65 insertions(+), 28 deletions(-)

```
#### [patch V4 01/15] seccomp: Provide stub for __secure_computing()References: <20200721105706.030914876@linutronix.de>
##### From: Thomas Gleixner <tglx@linutronix.de>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Thomas Gleixner <tglx@linutronix.de>
X-Patchwork-Id: 11675479
Return-Path: <SRS0=uGOU=BA=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 420D91392
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 21 Jul 2020 11:10:32 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 2AD7E2077D
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 21 Jul 2020 11:10:32 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=linutronix.de header.i=@linutronix.de
 header.b="OiWEO8cm";
	dkim=permerror (0-bit key) header.d=linutronix.de header.i=@linutronix.de
 header.b="gI2wYoRA"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729594AbgGULIj (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 21 Jul 2020 07:08:39 -0400
Received: from Galois.linutronix.de ([193.142.43.55]:37340 "EHLO
        galois.linutronix.de" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726415AbgGULIh (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 21 Jul 2020 07:08:37 -0400
Message-Id: <20200721110808.348199175@linutronix.de>
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=linutronix.de;
        s=2020; t=1595329715;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:content-type:content-type:
         content-transfer-encoding:content-transfer-encoding:
  references:references;
        bh=TYlK47Qp3PMG02GI6MwKMpJXQyCAbHFBFk8idNOPcBo=;
        b=OiWEO8cmytmWaDZikXjFg8QQUVuKKkFiaNJ3f4EuvuHC6sTkm8GHVWcSWByRIZIuontxfY
        TITrqRWo1E7ekAVG6sN1SjsHZ2BdJxU3kbiZYDmLW+q5rY/d4s2UosNIZehs2j3Vl0v0MI
        jMoN1HZEpWjeE5xsHiU02EZeuAq4DNDXmCwdU+726ZonmoleNmcUCrlkkEbksSlK8+s7yZ
        kmXz6k/KlvVGD3AyRSa2mqBhyMm7mYbiXNHm7ImmhfnWG41y+F19Evv9G/bYZFzbEGJ4ca
        vVp+uIakZd8S16IZRdq2KiY0yNLC405IY6Mc6pqOyQyxc4ARcq6T+MDzZjmIfw==
DKIM-Signature: v=1; a=ed25519-sha256; c=relaxed/relaxed; d=linutronix.de;
        s=2020e; t=1595329715;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:content-type:content-type:
         content-transfer-encoding:content-transfer-encoding:
  references:references;
        bh=TYlK47Qp3PMG02GI6MwKMpJXQyCAbHFBFk8idNOPcBo=;
        b=gI2wYoRArtCglw/JgOpwVZNFI0vQ0eSe2W5jKMcH4jTfnKulI3V/EqjNmbN/e0ef6INeAM
        lQb7a86qjiRoQUBA==
Date: Tue, 21 Jul 2020 12:57:07 +0200
From: Thomas Gleixner <tglx@linutronix.de>
To: LKML <linux-kernel@vger.kernel.org>
Cc: x86@kernel.org, linux-arch@vger.kernel.org,
        Will Deacon <will@kernel.org>, Arnd Bergmann <arnd@arndb.de>,
        Mark Rutland <mark.rutland@arm.com>,
        Kees Cook <keescook@chromium.org>,
        Keno Fischer <keno@juliacomputing.com>,
        Paolo Bonzini <pbonzini@redhat.com>, kvm@vger.kernel.org,
        Gabriel Krisman Bertazi <krisman@collabora.com>
Subject: [patch V4 01/15] seccomp: Provide stub for __secure_computing()
References: <20200721105706.030914876@linutronix.de>
MIME-Version: 1.0
Content-transfer-encoding: 8-bit
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

To avoid #ifdeffery in the upcoming generic syscall entry work code provide
a stub for __secure_computing() as this is preferred over
secure_computing() because the TIF flag is already evaluated.

Signed-off-by: Thomas Gleixner <tglx@linutronix.de>
Acked-by: Kees Cook <keescook@chromium.org>
---
V4: New patch
---
 include/linux/seccomp.h |    1 +
```
#### [PATCH v2 1/5] kvm: x86: refactor masterclock sync heuristics out of kvm_write_tsc
##### From: Oliver Upton <oupton@google.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Oliver Upton <oupton@google.com>
X-Patchwork-Id: 11676573
Return-Path: <SRS0=uGOU=BA=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 4DD0513B6
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 21 Jul 2020 20:18:26 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 2E9D020771
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 21 Jul 2020 20:18:26 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=google.com header.i=@google.com
 header.b="Q5CH8IBM"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1730470AbgGUUSX (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 21 Jul 2020 16:18:23 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:52326 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726658AbgGUUSW (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 21 Jul 2020 16:18:22 -0400
Received: from mail-pg1-x54a.google.com (mail-pg1-x54a.google.com
 [IPv6:2607:f8b0:4864:20::54a])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 1A157C0619DA
        for <kvm@vger.kernel.org>; Tue, 21 Jul 2020 13:18:22 -0700 (PDT)
Received: by mail-pg1-x54a.google.com with SMTP id i1so17062934pgn.13
        for <kvm@vger.kernel.org>; Tue, 21 Jul 2020 13:18:22 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=date:in-reply-to:message-id:mime-version:references:subject:from:to
         :cc;
        bh=QD4uV54IL68Del4fdGOvf6XTmyV/0hAZrgqJbqMObDM=;
        b=Q5CH8IBM95uJncMg5tBpzXhLrW40QO9BBs46QsH0ZTt7UZ30/+QEAICEuHlFMjj7in
         biP9ZMDO0EDUeC22w/ux7KABFfvj5fOXkQ5KdIjSxgBxjH2xgq2CfLxO5TOPZiBkwSYy
         WT+oaeWYe7BzVdWuclCAsYUz4/iWo6/zuuci9MvDzvIZE42F6r+7P6cUJLY2aJWD41El
         JYfnl6lWYL9fC+v6W7mT0Ye3p2UShdxU60NpFx4UmIgeZRiwLjGhB4Kmy6ELAO3uKI8o
         RF3cH+0dqeeu9a2PlZ24n6FLMK3KQkyDEehLxyULViv5ezfdOeo8oFXPu2DljarUH/mN
         wQ6w==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:date:in-reply-to:message-id:mime-version
         :references:subject:from:to:cc;
        bh=QD4uV54IL68Del4fdGOvf6XTmyV/0hAZrgqJbqMObDM=;
        b=eOvVt/xS4nuS3XdSg9ND6nuBLZjkwhKlTJdFv/i62kxp/3tUg2/j90XEKVQn3EXT65
         JvEcx2TwekyiyyqXycFJwGtkPIH2EBVbFbRjI/kxN9fgLwdk3GhIvoWxUsQgmDCI62Hs
         VM/rqfMrBEk4VJ3G5M8fxIHyrV/50PPMkJ7xe6gpRv3aZQyqbprXDfBpHjSroip5KG7l
         IFUwjggJSP34xvp1D7YnJl+om20RADB/bSB4EC6QYSXt3QmZV+aeCTFFWAIoc304g4f0
         ifQCQ6zcxCRRlyBShPc2moxpCdlxCf0FLaxXAPnlvyFJyqcq0uykneVEFkKkX0jTCkGE
         VkQg==
X-Gm-Message-State: AOAM533hiThapPdRoe4UN2YeQGIYWNt9gbzt6gbZLMrpzuCcaU/zBA55
        MHm2xUq+jHuvalewSTHMc3B3enQKiXSmU4tqWO149FZZfrIvyRtTw3OeVkT3xYw+HUje8MbpSNC
        gnjcV6mXoAJajvUNds9/ECTqZsguyfSlJNQQ6sNPDZLT8tePfh61yEa5HKg==
X-Google-Smtp-Source: 
 ABdhPJy05uK558uc7madzS1wDCualoB8i8Ui8Ny6Z2xk0olg2kaKQSD14M2WQ8+wESig5WvEFWd3+0AKggE=
X-Received: by 2002:a63:3fc2:: with SMTP id
 m185mr24863899pga.426.1595362701346;
 Tue, 21 Jul 2020 13:18:21 -0700 (PDT)
Date: Tue, 21 Jul 2020 20:18:10 +0000
In-Reply-To: <20200721201814.2340705-1-oupton@google.com>
Message-Id: <20200721201814.2340705-2-oupton@google.com>
Mime-Version: 1.0
References: <20200721201814.2340705-1-oupton@google.com>
X-Mailer: git-send-email 2.28.0.rc0.142.g3c755180ce-goog
Subject: [PATCH v2 1/5] kvm: x86: refactor masterclock sync heuristics out of
 kvm_write_tsc
From: Oliver Upton <oupton@google.com>
To: kvm@vger.kernel.org
Cc: Paolo Bonzini <pbonzini@redhat.com>,
        Peter Shier <pshier@google.com>,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        Peter Hornyack <peterhornyack@google.com>,
        Oliver Upton <oupton@google.com>,
        Jim Mattson <jmattson@google.com>
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

kvm_write_tsc() determines when the host or guest is attempting to
synchronize the TSCs and does some bookkeeping for tracking this. Retain
the existing sync checks (host is writing 0 or TSCs being written within
a second of one another) in kvm_write_tsc(), but split off the
bookkeeping and TSC offset write into a new function. This allows for a
new ioctl to be introduced, yielding control of the TSC offset field to
userspace in a manner that respects the existing masterclock heuristics.

Reviewed-by: Jim Mattson <jmattson@google.com>
Reviewed-by: Peter Shier <pshier@google.com>
Signed-off-by: Oliver Upton <oupton@google.com>
---
 arch/x86/kvm/x86.c | 98 +++++++++++++++++++++++++---------------------
 1 file changed, 54 insertions(+), 44 deletions(-)

```
#### [PATCH] KVM: Using macros instead of magic values
##### From: Haiwei Li <lihaiwei.kernel@gmail.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Haiwei Li <lihaiwei.kernel@gmail.com>
X-Patchwork-Id: 11675229
Return-Path: <SRS0=uGOU=BA=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 06F3914E3
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 21 Jul 2020 08:24:08 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id E3BCE20714
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 21 Jul 2020 08:24:07 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=gmail.com header.i=@gmail.com
 header.b="k7JJZ3Sk"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726803AbgGUIYD (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 21 Jul 2020 04:24:03 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:54136 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726089AbgGUIYD (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 21 Jul 2020 04:24:03 -0400
Received: from mail-pj1-x1043.google.com (mail-pj1-x1043.google.com
 [IPv6:2607:f8b0:4864:20::1043])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 4B0EEC061794;
        Tue, 21 Jul 2020 01:24:03 -0700 (PDT)
Received: by mail-pj1-x1043.google.com with SMTP id cv18so1112080pjb.1;
        Tue, 21 Jul 2020 01:24:03 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=to:cc:from:subject:message-id:date:user-agent:mime-version
         :content-language:content-transfer-encoding;
        bh=SCGoNX/Gx06PI0eqChSqx3NbjiK5be1SzuTiaG36KlM=;
        b=k7JJZ3SkykmDYq8ZsHa0/+BVnqjUEmIX0Vc/FeXqhPuHhvILnYCAwLMoOYuYCsKTmD
         IL6G6MWxIdPp96ntVwfE+xFSV4TRJlwnEqER6JrVlrIDNgtLumwZ7eCDRYIuoD4a/uuK
         7gsleRJW09qRkVdKRIItkFiTXezv+zGMiPnSajOT4/0QlarhbVS/RoPbX6VZFlgK9dUM
         YglOx7PIMp9T2EMuM7ihKApDj6bo1zBUEysxRE3p5YFbFQE3B+GmmwTmnT+nzscdh1KO
         OFp8anhxRvxbagspNBX7cnOayMDbMRUQVyz2gCEHBdwEg2fspVnIRZAgyINClUOrQmse
         XZvA==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:to:cc:from:subject:message-id:date:user-agent
         :mime-version:content-language:content-transfer-encoding;
        bh=SCGoNX/Gx06PI0eqChSqx3NbjiK5be1SzuTiaG36KlM=;
        b=tjQAWLeT+JYMZ602HEfV21gQ1UV4Th1zE6zmzq8Z461EleGTlcd7D+nroN0vItjANu
         eLoFbzo45sDoG5rE5MGVAid3MQyjYaLKVtocE5QKSx8uD+2kHMulkVPy62Qpq+34Np8e
         PhAFLrGE4IZE56sRSSFA0sMvEIxz871qEneRqrM731UDaNoP9zToHF9HcyIja3L+gNlR
         BQ5DMBb2W1oRa885n5HO/HjMmi8/w3MN5nWYtwsPOEbnkQUVzqGDti+ESWQ4Z0YYO47/
         iYo5KwQfB+0dpCFvTIth5V1B0Jio+SKfy7q/OWEGvKuHkEJtUt/PcxMKVpXu+kvmoY9S
         1H7w==
X-Gm-Message-State: AOAM533Y2dBbyeqPAnXLRMZMbSsGkXEGi6i2xFFYb02whotG5/8RBjd+
        oc+UGCQHy4N/u26tFUdtNXCFnu8=
X-Google-Smtp-Source: 
 ABdhPJxf5x6eCqDIUTuyjMpOsrP0TkNV1tWJzOzszqAD+uyC19rtvch+3o66OLWY35vA/J4CkakHFg==
X-Received: by 2002:a17:90b:3684:: with SMTP id
 mj4mr3763826pjb.66.1595319842817;
        Tue, 21 Jul 2020 01:24:02 -0700 (PDT)
Received: from [127.0.0.1] ([203.205.141.54])
        by smtp.gmail.com with ESMTPSA id
 y8sm2261197pju.49.2020.07.21.01.23.58
        (version=TLS1_3 cipher=TLS_AES_128_GCM_SHA256 bits=128/128);
        Tue, 21 Jul 2020 01:24:02 -0700 (PDT)
To: "linux-kernel@vger.kernel.org" <linux-kernel@vger.kernel.org>,
        "kvm@vger.kernel.org" <kvm@vger.kernel.org>,
        "x86@kernel.org" <x86@kernel.org>
Cc: "pbonzini@redhat.com" <pbonzini@redhat.com>,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        "wanpengli@tencent.com" <wanpengli@tencent.com>,
        "vkuznets@redhat.com" <vkuznets@redhat.com>,
        "jmattson@google.com" <jmattson@google.com>,
        "joro@8bytes.org" <joro@8bytes.org>,
        "tglx@linutronix.de" <tglx@linutronix.de>, mingo@redhat.com,
        "bp@alien8.de" <bp@alien8.de>, "hpa@zytor.com" <hpa@zytor.com>
From: Haiwei Li <lihaiwei.kernel@gmail.com>
Subject: [PATCH] KVM: Using macros instead of magic values
Message-ID: <4c072161-80dd-b7ed-7adb-02acccaa0701@gmail.com>
Date: Tue, 21 Jul 2020 16:23:54 +0800
User-Agent: Mozilla/5.0 (Macintosh; Intel Mac OS X 10.15; rv:68.0)
 Gecko/20100101 Thunderbird/68.10.0
MIME-Version: 1.0
Content-Language: en-US
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Haiwei Li <lihaiwei@tencent.com>

Instead of using magic values, use macros.

Signed-off-by: Haiwei Li <lihaiwei@tencent.com>
Reviewed-by: Vitaly Kuznetsov <vkuznets@redhat.com>
---
  arch/x86/kvm/lapic.c | 3 ++-
  1 file changed, 2 insertions(+), 1 deletion(-)

  		break;
--
1.8.3.1

```
#### [PATCH] PCI: pciehp: Fix AB-BA deadlock between reset_lock and device_lock
##### From: Lukas Wunner <lukas@wunner.de>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Lukas Wunner <lukas@wunner.de>
X-Patchwork-Id: 11675509
Return-Path: <SRS0=uGOU=BA=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 2CE7A13A4
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 21 Jul 2020 11:26:07 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 155B421702
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 21 Jul 2020 11:26:07 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729601AbgGUL0G (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 21 Jul 2020 07:26:06 -0400
Received: from bmailout3.hostsharing.net ([176.9.242.62]:49273 "EHLO
        bmailout3.hostsharing.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1728108AbgGUL0E (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 21 Jul 2020 07:26:04 -0400
X-Greylist: delayed 490 seconds by postgrey-1.27 at vger.kernel.org;
 Tue, 21 Jul 2020 07:26:02 EDT
Received: from h08.hostsharing.net (h08.hostsharing.net
 [IPv6:2a01:37:1000::53df:5f1c:0])
        (using TLSv1.2 with cipher ECDHE-RSA-AES256-GCM-SHA384 (256/256 bits))
        (Client CN "*.hostsharing.net",
 Issuer "COMODO RSA Domain Validation Secure Server CA" (not verified))
        by bmailout3.hostsharing.net (Postfix) with ESMTPS id 6CD1D1009FD55;
        Tue, 21 Jul 2020 13:17:51 +0200 (CEST)
Received: by h08.hostsharing.net (Postfix, from userid 100393)
        id 139D72304F; Tue, 21 Jul 2020 13:17:50 +0200 (CEST)
Message-Id: 
 <908047f7699d9de9ec2efd6b79aa752d73dab4b6.1595329748.git.lukas@wunner.de>
From: Lukas Wunner <lukas@wunner.de>
Date: Tue, 21 Jul 2020 13:17:50 +0200
Subject: [PATCH] PCI: pciehp: Fix AB-BA deadlock between reset_lock and
 device_lock
To: Bjorn Helgaas <bhelgaas@google.com>,
        Alex Williamson <alex.williamson@redhat.com>,
        Boris Ostrovsky <boris.ostrovsky@oracle.com>,
        Juergen Gross <jgross@suse.com>
Cc: Michael Haeuptle <michael.haeuptle@hpe.com>,
        Ian May <ian.may@canonical.com>,
        Keith Busch <kbusch@kernel.org>, linux-pci@vger.kernel.org,
        Cornelia Huck <cohuck@redhat.com>, kvm@vger.kernel.org,
        Rick Farrington <ricardo.farrington@cavium.com>,
        Derek Chickles <dchickles@marvell.com>,
        Satanand Burla <sburla@marvell.com>,
        Felix Manlunas <fmanlunas@marvell.com>,
        Stefano Stabellini <sstabellini@kernel.org>,
        xen-devel@lists.xenproject.org,
        Govinda Tatti <govinda.tatti@oracle.com>,
        "Konrad Rzeszutek Wilk" <konrad.wilk@oracle.com>
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Back in 2013, commits

  2e35afaefe64 ("PCI: pciehp: Add reset_slot() method")
  608c388122c7 ("PCI: Add slot reset option to pci_dev_reset()")

introduced the callback pciehp_reset_slot() to the PCIe hotplug driver
and amended __pci_dev_reset() (today __pci_reset_function_locked()) to
invoke it when resetting a hotplug port's child.  The callback performs
a Secondary Bus Reset and ensures that an ensuing link or presence flap
is ignored by pciehp.

However the commits did not perform any locking, in particular:

* No precautions were taken to prevent concurrent execution of the new
  callback with pciehp's IRQ handler or a sysfs request to bring the
  slot up or down.  These code paths may see flapping link or presence
  bits during a slot reset.

* pciehp is not prevented from unbinding while the new callback accesses
  its struct controller.  Commit 608c388122c7 did take a reference on
  pciehp's module, but that's not sufficient.  It only keeps pciehp's
  code in memory, but doesn't prevent unbinding.

* In pci_dev_reset_slot_function(), commit 608c388122c7 iterates over
  the devices on a bus without holding pci_bus_sem.

In 2018, commit

  5b3f7b7d062b ("PCI: pciehp: Avoid slot access during reset")

sought to address the first of these locking issues:  It introduced a
reset_lock which serializes a slot reset with other parts of pciehp.

But Michael Haeuptle reports that deadlocks now occur on simultaneous
hot-removal and reset of vfio devices because pciehp acquires the
reset_lock and the device_lock in a different order than
pci_try_reset_function():

pciehp_ist()                                    # down_read(reset_lock)
  pciehp_handle_presence_or_link_change()
    pciehp_disable_slot()
      __pciehp_disable_slot()
        remove_board()
          pciehp_unconfigure_device()
            pci_stop_and_remove_bus_device()
              pci_stop_bus_device()
                pci_stop_dev()
                  device_release_driver()
                    device_release_driver_internal()
                      __device_driver_lock()    # device_lock()

SYS_munmap()
  vfio_device_fops_release()
    vfio_pci_release()
      vfio_pci_disable()
        pci_try_reset_function()                # device_lock()
          __pci_reset_function_locked()
            pci_reset_hotplug_slot()
              pciehp_reset_slot()               # down_write(reset_lock)

Ian May reports the same deadlock on simultaneous hot-removal and AER
reset:

aer_recover_work_func()
  pcie_do_recovery()
    aer_root_reset()
      pci_bus_error_reset()
        pci_slot_reset()
          pci_slot_lock()                       # device_lock()
            pci_reset_hotplug_slot()
              pciehp_reset_slot()               # down_write(reset_lock)

Fix by pushing the reset_lock out of pciehp's struct controller and into
struct pci_slot such that it can be taken by the PCI core before taking
the device lock.

There's a catch though:  Some drivers call __pci_reset_function_locked()
directly and the function expects that all necessary locks, including
the reset_lock, have been acquired by the caller.  There are callers
which already hold the device_lock, so they can't acquire the reset_lock
without re-introducing the AB-BA deadlock:

* drivers/net/ethernet/cavium/liquidio/lio_main.c: octeon_pci_flr()
* drivers/xen/xen-pciback/pci_stub.c: pcistub_device_release()
* drivers/xen/xen-pciback/pci_stub.c: pcistub_init_device() (if called
  from pcistub_seize())

In the case of octeon_pci_flr(), the device is reset on driver unbind,
which is why the device_lock is already held.  A possible solution might
be to add a flag in struct pci_dev with which drivers tell the PCI core
that the device is handed back in an unclean state and needs a reset.
The PCI core would then perform the reset on behalf of the driver after
it has unbound and before any new driver is bound.

As for xen, this patch (which was never applied) explains that a reset
is performed on bind, unbind and on un-assigning a device from a guest:

  https://lore.kernel.org/patchwork/patch/848180/

The unbind code path could be solved by the same solution as for octeon
and it may also be possible to make it work on bind, though it's unclear
why a reset on bind is at all necessary.  The un-assigning code path is
fixed by the present commit I think.

For now, the three functions do not acquire the reset_lock.  I'm
inserting a lockdep_assert_held_write() so that a lockdep splat is shown
as a reminder that liquidio and xen require fixing.

Fixes: 5b3f7b7d062b ("PCI: pciehp: Avoid slot access during reset")
Link: https://lore.kernel.org/linux-pci/CS1PR8401MB0728FC6FDAB8A35C22BD90EC95F10@CS1PR8401MB0728.NAMPRD84.PROD.OUTLOOK.COM
Link: https://lore.kernel.org/linux-pci/20200615143250.438252-1-ian.may@canonical.com
Reported-and-tested-by: Michael Haeuptle <michael.haeuptle@hpe.com>
Reported-and-tested-by: Ian May <ian.may@canonical.com>
Signed-off-by: Lukas Wunner <lukas@wunner.de>
Cc: stable@vger.kernel.org # v4.19+
Cc: Alex Williamson <alex.williamson@redhat.com>
---
 drivers/pci/hotplug/pciehp.h          |  5 -----
 drivers/pci/hotplug/pciehp_core.c     |  4 ++--
 drivers/pci/hotplug/pciehp_hpc.c      | 12 ++++++------
 drivers/pci/pci.c                     | 17 +++++++++++++++++
 drivers/pci/slot.c                    |  2 ++
 drivers/vfio/pci/vfio_pci.c           | 19 +++++++++++++------
 drivers/xen/xen-pciback/passthrough.c | 14 ++++++++++++--
 drivers/xen/xen-pciback/pci_stub.c    |  6 ++++++
 drivers/xen/xen-pciback/vpci.c        | 14 ++++++++++++--
 include/linux/pci.h                   |  8 +++++++-
 10 files changed, 77 insertions(+), 24 deletions(-)

```
#### [PATCH v9 01/84] signal: export kill_pid_info()
##### From: =?utf-8?q?Adalbert_Laz=C4=83r?= <alazar@bitdefender.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 8bit
X-Patchwork-Submitter: =?utf-8?q?Adalbert_Laz=C4=83r?=
 <alazar@bitdefender.com>
X-Patchwork-Id: 11676667
Return-Path: <SRS0=uGOU=BA=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 90B35138A
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 21 Jul 2020 21:17:00 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 7FE0020729
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 21 Jul 2020 21:17:00 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1731372AbgGUVQ7 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 21 Jul 2020 17:16:59 -0400
Received: from mx01.bbu.dsd.mx.bitdefender.com ([91.199.104.161]:37860 "EHLO
        mx01.bbu.dsd.mx.bitdefender.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1731285AbgGUVQN (ORCPT
        <rfc822;kvm@vger.kernel.org>); Tue, 21 Jul 2020 17:16:13 -0400
Received: from smtp.bitdefender.com (smtp02.buh.bitdefender.net [10.17.80.76])
        by mx01.bbu.dsd.mx.bitdefender.com (Postfix) with ESMTPS id
 14180307C93D;
        Wed, 22 Jul 2020 00:09:19 +0300 (EEST)
Received: from localhost.localdomain (unknown [91.199.104.27])
        by smtp.bitdefender.com (Postfix) with ESMTPSA id EB1D5303EF1F;
        Wed, 22 Jul 2020 00:09:18 +0300 (EEST)
From: =?utf-8?q?Adalbert_Laz=C4=83r?= <alazar@bitdefender.com>
To: kvm@vger.kernel.org
Cc: virtualization@lists.linux-foundation.org,
 Paolo Bonzini <pbonzini@redhat.com>,
 Mathieu Tarral <mathieu.tarral@protonmail.com>, =?utf-8?q?Adalbert_Laz?=
	=?utf-8?q?=C4=83r?= <alazar@bitdefender.com>
Subject: [PATCH v9 01/84] signal: export kill_pid_info()
Date: Wed, 22 Jul 2020 00:07:59 +0300
Message-Id: <20200721210922.7646-2-alazar@bitdefender.com>
In-Reply-To: <20200721210922.7646-1-alazar@bitdefender.com>
References: <20200721210922.7646-1-alazar@bitdefender.com>
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Mathieu Tarral <mathieu.tarral@protonmail.com>

This function is used by VM introspection code to ungracefully shutdown
a guest at the request of the introspection tool.

A security application will use this as the last resort to stop the
spread of a malware from a guest.

Signed-off-by: Mathieu Tarral <mathieu.tarral@protonmail.com>
Signed-off-by: Adalbert Lazăr <alazar@bitdefender.com>
---
 kernel/signal.c | 1 +
 1 file changed, 1 insertion(+)

```
