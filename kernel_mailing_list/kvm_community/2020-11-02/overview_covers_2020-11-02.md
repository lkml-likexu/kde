

#### [RFC v3 00/12] kvm: arm64: emulate ID registers
##### From: Peng Liang <liangpeng10@huawei.com>

```c
From patchwork Mon Nov  2 03:34:10 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Peng Liang <liangpeng10@huawei.com>
X-Patchwork-Id: 11872905
Return-Path: <SRS0=3TlJ=EI=vger.kernel.org=kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-6.8 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,
	USER_AGENT_GIT autolearn=no autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id CF9C7C388F2
	for <kvm@archiver.kernel.org>; Mon,  2 Nov 2020 03:37:14 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 69D62207BB
	for <kvm@archiver.kernel.org>; Mon,  2 Nov 2020 03:37:14 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727692AbgKBDhH (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Sun, 1 Nov 2020 22:37:07 -0500
Received: from szxga04-in.huawei.com ([45.249.212.190]:6722 "EHLO
        szxga04-in.huawei.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1727461AbgKBDhH (ORCPT <rfc822;kvm@vger.kernel.org>);
        Sun, 1 Nov 2020 22:37:07 -0500
Received: from DGGEMS413-HUB.china.huawei.com (unknown [172.30.72.58])
        by szxga04-in.huawei.com (SkyGuard) with ESMTP id 4CPdrZ712XzkdN2;
        Mon,  2 Nov 2020 11:37:02 +0800 (CST)
Received: from localhost.localdomain (10.175.124.27) by
 DGGEMS413-HUB.china.huawei.com (10.3.19.213) with Microsoft SMTP Server id
 14.3.487.0; Mon, 2 Nov 2020 11:36:58 +0800
From: Peng Liang <liangpeng10@huawei.com>
To: <kvmarm@lists.cs.columbia.edu>
CC: <kvm@vger.kernel.org>, <maz@kernel.org>, <will@kernel.org>,
        <drjones@redhat.com>, <zhang.zhanghailiang@huawei.com>,
        <xiexiangyou@huawei.com>, Peng Liang <liangpeng10@huawei.com>
Subject: [RFC v3 00/12] kvm: arm64: emulate ID registers
Date: Mon, 2 Nov 2020 11:34:10 +0800
Message-ID: <20201102033422.657391-1-liangpeng10@huawei.com>
X-Mailer: git-send-email 2.26.2
MIME-Version: 1.0
X-Originating-IP: [10.175.124.27]
X-CFilter-Loop: Reflected
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

In AArch64, guest will read the same values of the ID regsiters with
host.  Both of them read the values from arm64_ftr_regs.  This patch
series add support to emulate and configure ID registers so that we can
control the value of ID registers that guest read.

v2 -> v3:
 - remove check_user and split some set_user for some ID registers
 - check the consistency of ID registers of vCPUS
 - add more doc for the limits

v1 -> v2:
 - save the ID registers in sysreg file instead of a new struct
 - apply a checker before setting the value to the register
 - add doc for new KVM_CAP_ARM_CPU_FEATURE

Peng Liang (12):
  arm64: Add a helper function to traverse arm64_ftr_regs
  arm64: Introduce check_features
  kvm: arm64: Save ID registers to sys_regs file
  kvm: arm64: Make ID_AA64PFR0_EL1 configurable
  kvm: arm64: Make ID_AA64DFR0_EL1 configurable
  kvm: arm64: Make ID_AA64ISAR0_EL1 configurable
  kvm: arm64: Make ID_AA64ISAR1_EL1 configurable
  kvm: arm64: Make ID_DFR0_EL1 configurable
  kvm: arm64: Make MVFR1_EL1 configurable
  kvm: arm64: Make other ID registers configurable
  kvm: arm64: Check consistent of ID register
  kvm: arm64: add KVM_CAP_ARM_CPU_FEATURE extension

 Documentation/virt/kvm/api.rst      |  36 ++++
 arch/arm64/include/asm/cpufeature.h |   4 +
 arch/arm64/include/asm/kvm_coproc.h |   2 +
 arch/arm64/include/asm/kvm_host.h   |   9 +
 arch/arm64/kernel/cpufeature.c      |  36 ++++
 arch/arm64/kvm/arm.c                |  22 +++
 arch/arm64/kvm/sys_regs.c           | 272 ++++++++++++++++++++++++++--
 include/uapi/linux/kvm.h            |   1 +
 8 files changed, 365 insertions(+), 17 deletions(-)
```
#### [kvm-unit-tests PATCH 0/2] arm64: Add support for configuring the
##### From: Nikos Nikoleris <nikos.nikoleris@arm.com>

```c
From patchwork Mon Nov  2 11:34:42 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Nikos Nikoleris <nikos.nikoleris@arm.com>
X-Patchwork-Id: 11873657
Return-Path: <SRS0=3TlJ=EI=vger.kernel.org=kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-6.8 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,
	USER_AGENT_GIT autolearn=no autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 10A36C388F2
	for <kvm@archiver.kernel.org>; Mon,  2 Nov 2020 11:34:56 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id B506A222B9
	for <kvm@archiver.kernel.org>; Mon,  2 Nov 2020 11:34:52 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728615AbgKBLet (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Mon, 2 Nov 2020 06:34:49 -0500
Received: from foss.arm.com ([217.140.110.172]:58090 "EHLO foss.arm.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1728288AbgKBLet (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 2 Nov 2020 06:34:49 -0500
Received: from usa-sjc-imap-foss1.foss.arm.com (unknown [10.121.207.14])
        by usa-sjc-mx-foss1.foss.arm.com (Postfix) with ESMTP id 1D270101E;
        Mon,  2 Nov 2020 03:34:47 -0800 (PST)
Received: from camtx2.cambridge.arm.com (camtx2.cambridge.arm.com [10.1.7.22])
        by usa-sjc-imap-foss1.foss.arm.com (Postfix) with ESMTPSA id
 1C2D53F66E;
        Mon,  2 Nov 2020 03:34:46 -0800 (PST)
From: Nikos Nikoleris <nikos.nikoleris@arm.com>
To: kvm@vger.kernel.org
Cc: mark.rutland@arm.com, jade.alglave@arm.com, luc.maranget@inria.fr,
        andre.przywara@arm.com, alexandru.elisei@arm.com,
        drjones@redhat.com
Subject: [kvm-unit-tests PATCH 0/2] arm64: Add support for configuring the
 translation granule
Date: Mon,  2 Nov 2020 11:34:42 +0000
Message-Id: <20201102113444.103536-1-nikos.nikoleris@arm.com>
X-Mailer: git-send-email 2.17.1
X-ARM-No-Footer: FoSSMail
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Hi all,

This is an update to the patch that allows a user to change the
translation granule in arm64. Special thanks to Drew and Alex for
having a look at the code and their suggestions.

v1: https://lore.kernel.org/kvm/006a19c0-cdf7-e76c-8335-03034bea9c7e@arm.com/T

Changes in v2:
 - Change the configure option from page-shift to page-size
 - Check and warn if the configured granule is not supported

Thanks,

Nikos

Nikos Nikoleris (2):
  arm64: Add support for configuring the translation granule
  arm64: Check if the configured translation granule is supported

 configure                     | 26 +++++++++++++
 lib/arm/asm/page.h            |  4 ++
 lib/arm/asm/pgtable-hwdef.h   |  4 ++
 lib/arm/asm/pgtable.h         |  6 +++
 lib/arm/asm/thread_info.h     |  4 +-
 lib/arm64/asm/page.h          | 25 ++++++++++---
 lib/arm64/asm/pgtable-hwdef.h | 38 +++++++++++++------
 lib/arm64/asm/pgtable.h       | 69 +++++++++++++++++++++++++++++++++--
 lib/arm64/asm/processor.h     | 65 +++++++++++++++++++++++++++++++++
 lib/arm/mmu.c                 | 29 ++++++++++-----
 arm/cstart64.S                | 10 ++++-
 11 files changed, 248 insertions(+), 32 deletions(-)
```
#### [kvm-unit-tests PATCH 0/2] arm: MMU extentions to enable litmus7
##### From: Nikos Nikoleris <nikos.nikoleris@arm.com>

```c
From patchwork Mon Nov  2 11:53:09 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Nikos Nikoleris <nikos.nikoleris@arm.com>
X-Patchwork-Id: 11873757
Return-Path: <SRS0=3TlJ=EI=vger.kernel.org=kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-6.8 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,
	USER_AGENT_GIT autolearn=no autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 586F9C00A89
	for <kvm@archiver.kernel.org>; Mon,  2 Nov 2020 11:53:15 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 1149722226
	for <kvm@archiver.kernel.org>; Mon,  2 Nov 2020 11:53:15 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728561AbgKBLxO (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Mon, 2 Nov 2020 06:53:14 -0500
Received: from foss.arm.com ([217.140.110.172]:58352 "EHLO foss.arm.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1728297AbgKBLxO (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 2 Nov 2020 06:53:14 -0500
Received: from usa-sjc-imap-foss1.foss.arm.com (unknown [10.121.207.14])
        by usa-sjc-mx-foss1.foss.arm.com (Postfix) with ESMTP id C211930E;
        Mon,  2 Nov 2020 03:53:13 -0800 (PST)
Received: from camtx2.cambridge.arm.com (camtx2.cambridge.arm.com [10.1.7.22])
        by usa-sjc-imap-foss1.foss.arm.com (Postfix) with ESMTPSA id
 DBE1B3F66E;
        Mon,  2 Nov 2020 03:53:12 -0800 (PST)
From: Nikos Nikoleris <nikos.nikoleris@arm.com>
To: kvm@vger.kernel.org
Cc: mark.rutland@arm.com, jade.alglave@arm.com, luc.maranget@inria.fr,
        andre.przywara@arm.com, alexandru.elisei@arm.com
Subject: [kvm-unit-tests PATCH 0/2] arm: MMU extentions to enable litmus7
Date: Mon,  2 Nov 2020 11:53:09 +0000
Message-Id: <20201102115311.103750-1-nikos.nikoleris@arm.com>
X-Mailer: git-send-email 2.17.1
X-ARM-No-Footer: FoSSMail
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Hi all,

litmus7 [1][2], a tool that we develop and use to test the memory
model on hardware, is building on kvm-unit-tests to encapsulate full
system tests and control address translation. This series extends the
kvm-unit-tests arm MMU API and adds two memory attributes to MAIR_EL1
to make them available to the litmus tests.

[1]: http://diy.inria.fr/doc/litmus.html
[2]: https://community.arm.com/developer/ip-products/processors/b/processors-ip-blog/posts/expanding-memory-model-tools-system-level-architecture

Thanks,

Nikos


Luc Maranget (1):
  arm: Add mmu_get_pte() to the MMU API

Nikos Nikoleris (1):
  arm: Add support for the DEVICE_nGRE and NORMAL_WT memory types

 lib/arm/asm/mmu-api.h         |  1 +
 lib/arm64/asm/pgtable-hwdef.h |  2 ++
 lib/arm/mmu.c                 | 23 ++++++++++++++---------
 arm/cstart64.S                |  6 +++++-
 4 files changed, 22 insertions(+), 10 deletions(-)
```
#### [PATCH v2 0/8] slab: provide and use krealloc_array()
##### From: Bartosz Golaszewski <brgl@bgdev.pl>
From: Bartosz Golaszewski <bgolaszewski@baylibre.com>

```c
From patchwork Mon Nov  2 15:20:29 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Bartosz Golaszewski <brgl@bgdev.pl>
X-Patchwork-Id: 11874183
Return-Path: <SRS0=3TlJ=EI=vger.kernel.org=kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-6.8 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,HEADER_FROM_DIFFERENT_DOMAINS,MAILING_LIST_MULTI,SPF_HELO_NONE,
	SPF_PASS,USER_AGENT_GIT autolearn=no autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 574B0C4742C
	for <kvm@archiver.kernel.org>; Mon,  2 Nov 2020 15:20:44 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 24A9D22226
	for <kvm@archiver.kernel.org>; Mon,  2 Nov 2020 15:20:44 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=bgdev-pl.20150623.gappssmtp.com
 header.i=@bgdev-pl.20150623.gappssmtp.com header.b="Qx6XIDDk"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726027AbgKBPUn (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Mon, 2 Nov 2020 10:20:43 -0500
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:56676 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1725980AbgKBPUn (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 2 Nov 2020 10:20:43 -0500
Received: from mail-wm1-x342.google.com (mail-wm1-x342.google.com
 [IPv6:2a00:1450:4864:20::342])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id C0D10C061A04
        for <kvm@vger.kernel.org>; Mon,  2 Nov 2020 07:20:42 -0800 (PST)
Received: by mail-wm1-x342.google.com with SMTP id p19so1478436wmg.0
        for <kvm@vger.kernel.org>; Mon, 02 Nov 2020 07:20:42 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=bgdev-pl.20150623.gappssmtp.com; s=20150623;
        h=from:to:cc:subject:date:message-id:mime-version
         :content-transfer-encoding;
        bh=87j4CzgTjIznAlAGNVYlsLolKCjEqxgXtItxHQqBT+c=;
        b=Qx6XIDDkn/kgktIUkUO/8COUc5pZ7Xmrd4WIhOhtRKLqRH4jXfWsq4XQF+tviij2AS
         vQP1d5+o7im6WeNCxad2viztsEaWhYtaJWG1Vhj6E1J8UjnspJVoxf806Ry3jv4BdHop
         xwURD6IJS7yc8ElYCbGBoudPzERtKy2XkZUjWqe32YJYz8gF1KzLAhJg0Sgft+3IMCWa
         mV4JR08o+DnkkGEu+pVGUnHdRkfznAvaeW1sFyAveCP1kOZvsLyq+TKkJLfHFzK57TIm
         KW7GgBKwfAnVfidT0ZnlSAScho5vr6Rjk96VIp+X50g2am696JF1i4Ih5IAkrxiZq5BJ
         Pdug==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:mime-version
         :content-transfer-encoding;
        bh=87j4CzgTjIznAlAGNVYlsLolKCjEqxgXtItxHQqBT+c=;
        b=L84ewNftkWT96W6+XnynE0NbWTIlV8kQAMz9GheUKEFyyy4dhhJRCOHjTl9BsoQyUz
         DlbW8jJcVuL0qgKrGQhZhFgCZSIM2mJFu4LBQVBxsGg/R5xfQBru85M9v000dx6pTXyA
         u0O9XKaJqz9T36HPfrJzSqmu6P182woJbgyJlhV9SR/POdRejxcn2GpmEkWsyxENJP7j
         vuEGxLsScQ8Tzb/1yjmJg0PrMdNDro1J3tMdfKEuEWVvsM0pBzcwrMCRb3BJQFiz2B37
         Y58eJSIdZXHXJoxzCyLxnHY4RTfOOtx3ywoc9XkixG4kCgjoQkM2VZbLoCI5vevAwMu8
         DasA==
X-Gm-Message-State: AOAM531hSvMSNiylDaDtxceT7YtBIqCinf8WHC3LJ4vtr43Q1m5Kz5mq
        142rrLGixHbRhvg7j0vizIyyxQ==
X-Google-Smtp-Source: 
 ABdhPJyrNQzSj1QE+Qkm5CWvnTtBNZHgXZdYRD5QsBgAGl8HowPGK/ocdDyRBmSt205H50cLvofh/w==
X-Received: by 2002:a1c:9848:: with SMTP id
 a69mr18051505wme.158.1604330441469;
        Mon, 02 Nov 2020 07:20:41 -0800 (PST)
Received: from debian-brgl.home (amarseille-656-1-4-167.w90-8.abo.wanadoo.fr.
 [90.8.158.167])
        by smtp.gmail.com with ESMTPSA id
 b18sm15138014wmj.41.2020.11.02.07.20.39
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Mon, 02 Nov 2020 07:20:40 -0800 (PST)
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
Subject: [PATCH v2 0/8] slab: provide and use krealloc_array()
Date: Mon,  2 Nov 2020 16:20:29 +0100
Message-Id: <20201102152037.963-1-brgl@bgdev.pl>
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

v1 -> v2:
- added a kernel doc for krealloc_array()
- mentioned krealloc et al in the docs
- collected review tags

Bartosz Golaszewski (8):
  mm: slab: provide krealloc_array()
  ALSA: pcm: use krealloc_array()
  vhost: vringh: use krealloc_array()
  pinctrl: use krealloc_array()
  edac: ghes: use krealloc_array()
  drm: atomic: use krealloc_array()
  hwtracing: intel: use krealloc_array()
  dma-buf: use krealloc_array()

 Documentation/core-api/memory-allocation.rst |  4 ++++
 drivers/dma-buf/sync_file.c                  |  4 ++--
 drivers/edac/ghes_edac.c                     |  4 ++--
 drivers/gpu/drm/drm_atomic.c                 |  3 ++-
 drivers/hwtracing/intel_th/msu.c             |  2 +-
 drivers/pinctrl/pinctrl-utils.c              |  2 +-
 drivers/vhost/vringh.c                       |  3 ++-
 include/linux/slab.h                         | 18 ++++++++++++++++++
 sound/core/pcm_lib.c                         |  4 ++--
 9 files changed, 34 insertions(+), 10 deletions(-)
```
#### [PATCH v2 00/11] KVM: arm64: Move PC/ELR/SPSR/PSTATE updatess to EL2
##### From: Marc Zyngier <maz@kernel.org>
X-SA-Exim-Mail-From: maz@kernel.org

```c
From patchwork Mon Nov  2 16:40:34 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Marc Zyngier <maz@kernel.org>
X-Patchwork-Id: 11874463
Return-Path: <SRS0=3TlJ=EI=vger.kernel.org=kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-7.1 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,MAILING_LIST_MULTI,SPF_HELO_NONE,
	SPF_PASS,USER_AGENT_GIT autolearn=no autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 4CF61C388F2
	for <kvm@archiver.kernel.org>; Mon,  2 Nov 2020 16:41:10 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 0ACDD223BF
	for <kvm@archiver.kernel.org>; Mon,  2 Nov 2020 16:41:09 +0000 (UTC)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple; d=kernel.org;
	s=default; t=1604335270;
	bh=AKPTmBGR7HuRbCkpQNhVUn0IRnXZ4Ipp9VnCLd/kbeU=;
	h=From:To:Cc:Subject:Date:List-ID:From;
	b=tH1pVVS+VROvGU97XEEYpOqbQ/Ff/oyom5TxNwj3yRFRpZIhLF/YG7JmW68NXpueo
	 B6M9iDLIzEhDX7NmPDCqSXT2UaovDvS16b4M3F8WaCY4OhgiYIYA4sPwsV3oUDWcIf
	 aAXFebg99jy6KYsvYpOK94Z/3sDL0VzXr9FQQ8aY=
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727198AbgKBQlI (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Mon, 2 Nov 2020 11:41:08 -0500
Received: from mail.kernel.org ([198.145.29.99]:46676 "EHLO mail.kernel.org"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726817AbgKBQlH (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 2 Nov 2020 11:41:07 -0500
Received: from disco-boy.misterjones.org (disco-boy.misterjones.org
 [51.254.78.96])
        (using TLSv1.2 with cipher ECDHE-RSA-AES256-GCM-SHA384 (256/256 bits))
        (No client certificate requested)
        by mail.kernel.org (Postfix) with ESMTPSA id 17E3922268;
        Mon,  2 Nov 2020 16:41:06 +0000 (UTC)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple; d=kernel.org;
        s=default; t=1604335266;
        bh=AKPTmBGR7HuRbCkpQNhVUn0IRnXZ4Ipp9VnCLd/kbeU=;
        h=From:To:Cc:Subject:Date:From;
        b=Qj/OZTxAc30QiBiKK/EZhveb4AH0QEhPqr4AgVDoped/9mrL2fy4eoZIP9V1JWlJ0
         tD6uttPP/+96AoGx9aIKoD1voLp09oBoeBYbnSOiCW1j3xcJegIFOu90YQS6292v/t
         4Po2VAKF5dYsR7qgf1nOF1j3Mxdql6uEMpcHp4DM=
Received: from 78.163-31-62.static.virginmediabusiness.co.uk ([62.31.163.78]
 helo=why.lan)
        by disco-boy.misterjones.org with esmtpsa  (TLS1.3) tls
 TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384
        (Exim 4.94)
        (envelope-from <maz@kernel.org>)
        id 1kZctD-006jJf-VL; Mon, 02 Nov 2020 16:41:04 +0000
From: Marc Zyngier <maz@kernel.org>
To: linux-arm-kernel@lists.infradead.org, kvmarm@lists.cs.columbia.edu,
        kvm@vger.kernel.org
Cc: James Morse <james.morse@arm.com>,
        Julien Thierry <julien.thierry.kdev@gmail.com>,
        Suzuki K Poulose <suzuki.poulose@arm.com>,
        Andrew Scull <ascull@google.com>,
        Will Deacon <will@kernel.org>,
        Mark Rutland <mark.rutland@arm.com>,
        Quentin Perret <qperret@google.com>,
        David Brazdil <dbrazdil@google.com>, kernel-team@android.com
Subject: [PATCH v2 00/11] KVM: arm64: Move PC/ELR/SPSR/PSTATE updatess to EL2
Date: Mon,  2 Nov 2020 16:40:34 +0000
Message-Id: <20201102164045.264512-1-maz@kernel.org>
X-Mailer: git-send-email 2.28.0
MIME-Version: 1.0
X-SA-Exim-Connect-IP: 62.31.163.78
X-SA-Exim-Rcpt-To: linux-arm-kernel@lists.infradead.org,
 kvmarm@lists.cs.columbia.edu, kvm@vger.kernel.org, james.morse@arm.com,
 julien.thierry.kdev@gmail.com, suzuki.poulose@arm.com, ascull@google.com,
 will@kernel.org, mark.rutland@arm.com, qperret@google.com,
 dbrazdil@google.com, kernel-team@android.com
X-SA-Exim-Mail-From: maz@kernel.org
X-SA-Exim-Scanned: No (on disco-boy.misterjones.org);
 SAEximRunCond expanded to false
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

As we progress towards being able to keep the guest state private to
the nVHE hypervisor, this series aims at moving anything that touches
the registers involved into an exception to EL2.

The general idea is that any update to these registers is driven by a
set of flags passed from EL1 to EL2, and EL2 will deal with the
register update itself, removing the need for EL1 to see the guest
state. It also results in a bunch of cleanup, mostly in the 32bit
department (negative diffstat, yay!).

Of course, none of that has any real effect on security yet. It is
only once we start having a private VCPU structure at EL2 that we can
enforce the isolation. Similarly, there is no policy enforcement, and
a malicious EL1 can still inject exceptions at random points. It can
also give bogus ESR values to the guest. Baby steps.

        M.

* From v1 [1]
  - Fix __kvm_skip_instr() unexpected recursion
  - Fix HVC fixup updating the in-memory state instead of the guest's
  - Dropped facilities for IRQ/FIQ/SError exception injection
  - Simplified VHE/nVHE differences in exception injection
  - Moved AArch32 exception injection over to AArch64 sysregs
  - Use compat_lr_* instead of hardcoded registers
  - Schpelling fyxes

[1] https://lore.kernel.org/r/20201026133450.73304-1-maz@kernel.org

Marc Zyngier (11):
  KVM: arm64: Don't adjust PC on SError during SMC trap
  KVM: arm64: Move kvm_vcpu_trap_il_is32bit into kvm_skip_instr32()
  KVM: arm64: Make kvm_skip_instr() and co private to HYP
  KVM: arm64: Move PC rollback on SError to HYP
  KVM: arm64: Move VHE direct sysreg accessors into kvm_host.h
  KVM: arm64: Add basic hooks for injecting exceptions from EL2
  KVM: arm64: Inject AArch64 exceptions from HYP
  KVM: arm64: Inject AArch32 exceptions from HYP
  KVM: arm64: Remove SPSR manipulation primitives
  KVM: arm64: Consolidate exception injection
  KVM: arm64: Get rid of the AArch32 register mapping code

 arch/arm64/include/asm/kvm_emulate.h       |  70 +----
 arch/arm64/include/asm/kvm_host.h          | 118 +++++++-
 arch/arm64/kvm/Makefile                    |   4 +-
 arch/arm64/kvm/aarch32.c                   | 232 ---------------
 arch/arm64/kvm/guest.c                     |  28 +-
 arch/arm64/kvm/handle_exit.c               |  23 +-
 arch/arm64/kvm/hyp/aarch32.c               |   4 +-
 arch/arm64/kvm/hyp/exception.c             | 331 +++++++++++++++++++++
 arch/arm64/kvm/hyp/include/hyp/adjust_pc.h |  62 ++++
 arch/arm64/kvm/hyp/include/hyp/switch.h    |  17 ++
 arch/arm64/kvm/hyp/nvhe/Makefile           |   2 +-
 arch/arm64/kvm/hyp/nvhe/switch.c           |   3 +
 arch/arm64/kvm/hyp/vgic-v2-cpuif-proxy.c   |   2 +
 arch/arm64/kvm/hyp/vgic-v3-sr.c            |   2 +
 arch/arm64/kvm/hyp/vhe/Makefile            |   2 +-
 arch/arm64/kvm/hyp/vhe/switch.c            |   3 +
 arch/arm64/kvm/inject_fault.c              | 189 +++++-------
 arch/arm64/kvm/mmio.c                      |   2 +-
 arch/arm64/kvm/mmu.c                       |   2 +-
 arch/arm64/kvm/regmap.c                    | 224 --------------
 arch/arm64/kvm/sys_regs.c                  |  83 +-----
 21 files changed, 666 insertions(+), 737 deletions(-)
 delete mode 100644 arch/arm64/kvm/aarch32.c
 create mode 100644 arch/arm64/kvm/hyp/exception.c
 create mode 100644 arch/arm64/kvm/hyp/include/hyp/adjust_pc.h
 delete mode 100644 arch/arm64/kvm/regmap.c
```
#### [PATCH v2 0/3] KVM: selftests: Add get-reg-list regression test
##### From: Andrew Jones <drjones@redhat.com>

```c
From patchwork Mon Nov  2 19:02:50 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Andrew Jones <drjones@redhat.com>
X-Patchwork-Id: 11875007
Return-Path: <SRS0=3TlJ=EI=vger.kernel.org=kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-3.9 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS autolearn=no autolearn_force=no
	version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id EB921C00A89
	for <kvm@archiver.kernel.org>; Mon,  2 Nov 2020 19:03:08 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 8103B22268
	for <kvm@archiver.kernel.org>; Mon,  2 Nov 2020 19:03:08 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="In1U6I9S"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1725806AbgKBTDH (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Mon, 2 Nov 2020 14:03:07 -0500
Received: from us-smtp-delivery-124.mimecast.com ([63.128.21.124]:56522 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1725791AbgKBTDH (ORCPT
        <rfc822;kvm@vger.kernel.org>); Mon, 2 Nov 2020 14:03:07 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1604343786;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=NQdKNE9/zc9ZzBpRKz0xCeXBkuHXUMTgObFrN15l8CM=;
        b=In1U6I9SCtZ09XVws5lxOxSg19EHrxU8ndAtTsyTIEocJuUT2Lmk1s3YJJITNjC66q287e
        6F5WHPUmkNmS7ijxHjlCFTLNW97Kai0gytJ2CD9e2S2utKJZ4g9jhlo9NpKZO+kjSkjpx8
        o/gQqK3XAUk0ftvs3/7rL7Vc+KQnURA=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-344-pxQbgAu3OQSXlf2ZmlAbMA-1; Mon, 02 Nov 2020 14:03:04 -0500
X-MC-Unique: pxQbgAu3OQSXlf2ZmlAbMA-1
Received: from smtp.corp.redhat.com (int-mx01.intmail.prod.int.phx2.redhat.com
 [10.5.11.11])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 812A91099F75;
        Mon,  2 Nov 2020 19:03:03 +0000 (UTC)
Received: from kamzik.brq.redhat.com (unknown [10.40.193.222])
        by smtp.corp.redhat.com (Postfix) with ESMTP id AA50B5B4C4;
        Mon,  2 Nov 2020 19:02:54 +0000 (UTC)
From: Andrew Jones <drjones@redhat.com>
To: kvm@vger.kernel.org, kvmarm@lists.cs.columbia.edu
Cc: pbonzini@redhat.com, maz@kernel.org, Dave.Martin@arm.com,
        peter.maydell@linaro.org, eric.auger@redhat.com
Subject: [PATCH v2 0/3] KVM: selftests: Add get-reg-list regression test
Date: Mon,  2 Nov 2020 20:02:50 +0100
Message-Id: <20201102190253.50575-1-drjones@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.11
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This test was inspired by recent regression report about get-reg-list
losing a register between an old kernel version and a new one.

v2:
  - Added "... up to date with kernel version v5.10-rc2" comment
    to the blessed list [Marc]
  - Assert when an invalid command line argument is given rather
    than ignore it [drew]

Thanks,
drew


Andrew Jones (3):
  KVM: selftests: Add aarch64 get-reg-list test
  KVM: selftests: Update aarch64 get-reg-list blessed list
  KVM: selftests: Add blessed SVE registers to get-reg-list

 tools/testing/selftests/kvm/.gitignore        |   2 +
 tools/testing/selftests/kvm/Makefile          |   2 +
 .../selftests/kvm/aarch64/get-reg-list-sve.c  |   3 +
 .../selftests/kvm/aarch64/get-reg-list.c      | 843 ++++++++++++++++++
 .../testing/selftests/kvm/include/kvm_util.h  |   1 +
 tools/testing/selftests/kvm/lib/kvm_util.c    |  29 +
 6 files changed, 880 insertions(+)
 create mode 100644 tools/testing/selftests/kvm/aarch64/get-reg-list-sve.c
 create mode 100644 tools/testing/selftests/kvm/aarch64/get-reg-list.c
```
#### [PATCH 0/8] KVM: arm64: Kill the copro array
##### From: Marc Zyngier <maz@kernel.org>
X-SA-Exim-Mail-From: maz@kernel.org

```c
From patchwork Mon Nov  2 19:16:01 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Marc Zyngier <maz@kernel.org>
X-Patchwork-Id: 11875081
Return-Path: <SRS0=3TlJ=EI=vger.kernel.org=kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-7.1 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,MAILING_LIST_MULTI,SPF_HELO_NONE,
	SPF_PASS,USER_AGENT_GIT autolearn=no autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id AB680C388F9
	for <kvm@archiver.kernel.org>; Mon,  2 Nov 2020 19:16:18 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 5563A223FD
	for <kvm@archiver.kernel.org>; Mon,  2 Nov 2020 19:16:18 +0000 (UTC)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple; d=kernel.org;
	s=default; t=1604344578;
	bh=KaBxJjv3YFcRADE2Fb61WsHODS72mdq+Zd3tO6gwFuY=;
	h=From:To:Cc:Subject:Date:List-ID:From;
	b=1uZOo/W4sFztJoSCn7dPvGl7wy0Ci7Zn5U8Z/BLxYQ7cGgSET7S10kxaJEvQkj3NP
	 jm+e6duw65ZYj/qp2qX38i/lOQLENFbntHcTs3cA+LWRYLZ0nbJKh/0vcTH7dN2Nkk
	 LXiUW/C4lofIzbpDlsWQZvWmhjE2LRTwrjM0P2JA=
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726429AbgKBTQR (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Mon, 2 Nov 2020 14:16:17 -0500
Received: from mail.kernel.org ([198.145.29.99]:60354 "EHLO mail.kernel.org"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1725929AbgKBTQR (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 2 Nov 2020 14:16:17 -0500
Received: from disco-boy.misterjones.org (disco-boy.misterjones.org
 [51.254.78.96])
        (using TLSv1.2 with cipher ECDHE-RSA-AES256-GCM-SHA384 (256/256 bits))
        (No client certificate requested)
        by mail.kernel.org (Postfix) with ESMTPSA id 8853422280;
        Mon,  2 Nov 2020 19:16:16 +0000 (UTC)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple; d=kernel.org;
        s=default; t=1604344576;
        bh=KaBxJjv3YFcRADE2Fb61WsHODS72mdq+Zd3tO6gwFuY=;
        h=From:To:Cc:Subject:Date:From;
        b=F6G5LI7TVR4qwUpzdpSGCqSMwzpczvA+k2UyTbrKWn/WcKbBt3sCELDKAvVuQ32bD
         lFE/wIiB6Y9eKt3htBkEB+ex7jCuzDzQOSsupiyzo5K0Rghgg9vjcFbZ8dxmrp1+bK
         EQ8wn9YHhNsPfSWHoe8SvEUfyiEKrMWo0bAq9I5Y=
Received: from 78.163-31-62.static.virginmediabusiness.co.uk ([62.31.163.78]
 helo=why.lan)
        by disco-boy.misterjones.org with esmtpsa  (TLS1.3) tls
 TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384
        (Exim 4.94)
        (envelope-from <maz@kernel.org>)
        id 1kZfJN-006nxn-6F; Mon, 02 Nov 2020 19:16:13 +0000
From: Marc Zyngier <maz@kernel.org>
To: kvm@vger.kernel.org, kvmarm@lists.cs.columbia.edu,
        linux-arm-kernel@lists.infradead.org
Cc: James Morse <james.morse@arm.com>,
        Julien Thierry <julien.thierry.kdev@gmail.com>,
        Suzuki K Poulose <suzuki.poulose@arm.com>,
        kernel-team@android.com
Subject: [PATCH 0/8] KVM: arm64: Kill the copro array
Date: Mon,  2 Nov 2020 19:16:01 +0000
Message-Id: <20201102191609.265711-1-maz@kernel.org>
X-Mailer: git-send-email 2.28.0
MIME-Version: 1.0
X-SA-Exim-Connect-IP: 62.31.163.78
X-SA-Exim-Rcpt-To: kvm@vger.kernel.org, kvmarm@lists.cs.columbia.edu,
 linux-arm-kernel@lists.infradead.org, james.morse@arm.com,
 julien.thierry.kdev@gmail.com, suzuki.poulose@arm.com,
 kernel-team@android.com
X-SA-Exim-Mail-From: maz@kernel.org
X-SA-Exim-Scanned: No (on disco-boy.misterjones.org);
 SAEximRunCond expanded to false
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Since the very beginning of KVM/arm64, we represented the system
register file using a dual view: on one side the AArch64 state, on the
other a bizarre mapping of the AArch64 state onto the Aarch64
registers.

It was nice at the time as it allowed us to share some code with the
32bit port, and to come up with some creative bugs. But is was always
a hack, and we are now in a position to simplify the whole thing.

This series goes through the whole of the AArch32 cp14/15 register
file, and point each of them directly at their 64bit equivalent. For
the few cases where two 32bit registers share a 64bit counterpart, we
define which half of the register they map.

Finally, we drop a large number of definitions and state that have
become useless.

This series applies on top of the exception injection rework
previously posted [1].

	   M.

[1] https://lore.kernel.org/r/20201102164045.264512-1-maz@kernel.org

Marc Zyngier (8):
  KVM: arm64: Move AArch32 exceptions over to AArch64 sysregs
  KVM: arm64: Add AArch32 mapping annotation
  KVM: arm64: Map AArch32 cp15 register to AArch64 sysregs
  KVM: arm64: Map AArch32 cp14 register to AArch64 sysregs
  KVM: arm64: Drop is_32bit trap attribute
  KVM: arm64: Drop is_aarch32 trap attribute
  KVM: arm64: Drop legacy copro shadow register
  KVM: arm64: Drop kvm_coproc.h

 arch/arm64/include/asm/kvm_coproc.h |  38 -----
 arch/arm64/include/asm/kvm_host.h   |  73 +++------
 arch/arm64/kvm/arm.c                |   3 +-
 arch/arm64/kvm/guest.c              |   1 -
 arch/arm64/kvm/handle_exit.c        |   1 -
 arch/arm64/kvm/inject_fault.c       |  62 +++-----
 arch/arm64/kvm/reset.c              |   1 -
 arch/arm64/kvm/sys_regs.c           | 231 ++++++++++++----------------
 arch/arm64/kvm/sys_regs.h           |   9 +-
 arch/arm64/kvm/vgic-sys-reg-v3.c    |   4 -
 10 files changed, 146 insertions(+), 277 deletions(-)
 delete mode 100644 arch/arm64/include/asm/kvm_coproc.h
```
