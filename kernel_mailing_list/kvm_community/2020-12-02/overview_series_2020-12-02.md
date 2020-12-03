#### [GIT PULL] vdpa: last minute bugfixes
##### From: "Michael S. Tsirkin" <mst@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: "Michael S. Tsirkin" <mst@redhat.com>
X-Patchwork-Id: 11945749
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-27.2 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_CR_TRAILER,INCLUDES_PATCH,INCLUDES_PULL_REQUEST,MAILING_LIST_MULTI,
	MENTIONS_GIT_HOSTING,SPF_HELO_NONE,SPF_PASS autolearn=ham autolearn_force=no
	version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 7AAA1C64E7C
	for <kvm@archiver.kernel.org>; Wed,  2 Dec 2020 11:53:21 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 1A37B2086A
	for <kvm@archiver.kernel.org>; Wed,  2 Dec 2020 11:53:21 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729760AbgLBLxU (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Wed, 2 Dec 2020 06:53:20 -0500
Received: from us-smtp-delivery-124.mimecast.com ([216.205.24.124]:60974 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1726791AbgLBLxU (ORCPT
        <rfc822;kvm@vger.kernel.org>); Wed, 2 Dec 2020 06:53:20 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1606909913;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:content-type:content-type;
        bh=eZnLI0Wik0eaxTfaNNAVKLQ21xyT2CoTcJpXnx1wngM=;
        b=DYE1A+98W3tnn2+7c23MG14A46HKHLzE2JcPnrB1IW8NYOX7J7eNvmgx2NmXGjfkVQvf0z
        rHexVr8IHFOHwPcjEO5rzYKyq1XN5xBvqS9Yx3rn1jx5szxr/3/lY0xLcVTYzZe0pek1Fm
        Ni5YTJmJNLMoqg5mTcHn52KN7uRR53g=
Received: from mail-wr1-f71.google.com (mail-wr1-f71.google.com
 [209.85.221.71]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-41-jrN-og_hOMGzRBsal0RFvw-1; Wed, 02 Dec 2020 06:51:52 -0500
X-MC-Unique: jrN-og_hOMGzRBsal0RFvw-1
Received: by mail-wr1-f71.google.com with SMTP id n13so3488269wrs.10
        for <kvm@vger.kernel.org>; Wed, 02 Dec 2020 03:51:52 -0800 (PST)
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:date:from:to:cc:subject:message-id:mime-version
         :content-disposition;
        bh=eZnLI0Wik0eaxTfaNNAVKLQ21xyT2CoTcJpXnx1wngM=;
        b=ON0erLv/4UvznCguqdug2ghKBhMMdC2c+sVO7BWwWeIGV9Rz6VaTH902PLTxGte6Dc
         nl6XvWxKIt9GLFqvKw5fbfPnCOfhCY183SIPwdwnVPyUpptzBVPvPgopcU6z0+p1HeN5
         Xumo2gNYbY8vkjRHDZlMSCbnsjAE5o8cnAIo2TImXpKCH0EIPDJpxFtHlOFMSZt32Byd
         DpsANVG1esWpTkaI1MXUihMLXDntclLAeUsl12bR1LDYQbLc9zE/foL1HG/IghNV7Ox7
         JE/z3thChvY0nZAsFimcBXSuuijtzFI484junzutBlixZWRMA1wLs2htt+5xy1h7s+C8
         Y4/g==
X-Gm-Message-State: AOAM533TwMfVZ/JT5Gw0JPFb1TWcTO33NFndjPiT9r5I5pqweZSmabGv
        7120Krgp0VcPxT3NVDiqIZjcRVUsM66zos89IzYJIUL0TvU3SnToYwlfUZwFFlfa4koWNeGdFUP
        TE7CeiUl2mErM
X-Received: by 2002:a05:600c:2106:: with SMTP id
 u6mr1002271wml.4.1606909911245;
        Wed, 02 Dec 2020 03:51:51 -0800 (PST)
X-Google-Smtp-Source: 
 ABdhPJyDk/79fb5VUyBoaUX2SQVUTrvAjsll90UI65W+kVpuHWCvrrBFwGplb9GAKNlrMm4UMxEqKg==
X-Received: by 2002:a05:600c:2106:: with SMTP id
 u6mr1002258wml.4.1606909911075;
        Wed, 02 Dec 2020 03:51:51 -0800 (PST)
Received: from redhat.com (bzq-79-176-44-197.red.bezeqint.net.
 [79.176.44.197])
        by smtp.gmail.com with ESMTPSA id f7sm1766312wmc.1.2020.12.02.03.51.48
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Wed, 02 Dec 2020 03:51:50 -0800 (PST)
Date: Wed, 2 Dec 2020 06:51:47 -0500
From: "Michael S. Tsirkin" <mst@redhat.com>
To: Linus Torvalds <torvalds@linux-foundation.org>
Cc: kvm@vger.kernel.org, virtualization@lists.linux-foundation.org,
        netdev@vger.kernel.org, linux-kernel@vger.kernel.org,
        dan.carpenter@oracle.com, eli@mellanox.com, jasowang@redhat.com,
        leonro@nvidia.com, lkp@intel.com, mst@redhat.com,
        parav@mellanox.com, rdunlap@infradead.org, saeedm@nvidia.com
Subject: [GIT PULL] vdpa: last minute bugfixes
Message-ID: <20201202065147-mutt-send-email-mst@kernel.org>
MIME-Version: 1.0
Content-Disposition: inline
X-Mutt-Fcc: =sent
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

A couple of patches of the obviously correct variety.

The following changes since commit ad89653f79f1882d55d9df76c9b2b94f008c4e27:

  vhost-vdpa: fix page pinning leakage in error path (rework) (2020-11-25 04:29:07 -0500)

are available in the Git repository at:

  https://git.kernel.org/pub/scm/linux/kernel/git/mst/vhost.git tags/for_linus

for you to fetch changes up to 2c602741b51daa12f8457f222ce9ce9c4825d067:

  vhost_vdpa: return -EFAULT if copy_to_user() fails (2020-12-02 04:36:40 -0500)

----------------------------------------------------------------
vdpa: last minute bugfixes

A couple of fixes that surfaced at the last minute.

Signed-off-by: Michael S. Tsirkin <mst@redhat.com>

----------------------------------------------------------------
Dan Carpenter (1):
      vhost_vdpa: return -EFAULT if copy_to_user() fails

Randy Dunlap (1):
      vdpa: mlx5: fix vdpa/vhost dependencies

 drivers/Makefile     | 1 +
 drivers/vdpa/Kconfig | 1 +
 drivers/vhost/vdpa.c | 4 +++-
 3 files changed, 5 insertions(+), 1 deletion(-)
```
#### [PATCH] selftests: kvm/set_memory_region_test: Fix race in move region test
##### From: "Maciej S. Szmigiero" <mail@maciej.szmigiero.name>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: "Maciej S. Szmigiero" <mail@maciej.szmigiero.name>
X-Patchwork-Id: 11947173
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.8 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT
	autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id DDDB5C64E7B
	for <kvm@archiver.kernel.org>; Wed,  2 Dec 2020 21:04:38 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 807BA221F7
	for <kvm@archiver.kernel.org>; Wed,  2 Dec 2020 21:04:38 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2387412AbgLBVEW (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Wed, 2 Dec 2020 16:04:22 -0500
Received: from vps-vb.mhejs.net ([37.28.154.113]:44310 "EHLO vps-vb.mhejs.net"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1729373AbgLBVEW (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 2 Dec 2020 16:04:22 -0500
X-Greylist: delayed 1671 seconds by postgrey-1.27 at vger.kernel.org;
 Wed, 02 Dec 2020 16:04:20 EST
Received: from MUA
        by vps-vb.mhejs.net with esmtps
 (TLS1.2:ECDHE-RSA-AES256-GCM-SHA384:256)
        (Exim 4.93.0.4)
        (envelope-from <mail@maciej.szmigiero.name>)
        id 1kkYqj-0004aI-SE; Wed, 02 Dec 2020 21:35:41 +0100
From: "Maciej S. Szmigiero" <mail@maciej.szmigiero.name>
To: Paolo Bonzini <pbonzini@redhat.com>, Shuah Khan <shuah@kernel.org>
Cc: Sean Christopherson <seanjc@google.com>, kvm@vger.kernel.org,
        linux-kselftest@vger.kernel.org, linux-kernel@vger.kernel.org
Subject: [PATCH] selftests: kvm/set_memory_region_test: Fix race in move
 region test
Date: Wed,  2 Dec 2020 21:35:36 +0100
Message-Id: 
 <0fdddb94bb0e31b7da129a809a308d91c10c0b5e.1606941224.git.maciej.szmigiero@oracle.com>
X-Mailer: git-send-email 2.29.1
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: "Maciej S. Szmigiero" <maciej.szmigiero@oracle.com>

The current memory region move test correctly handles the situation that
the second (realigning) memslot move operation would temporarily trigger
MMIO until it completes, however it does not handle the case in which the
first (misaligning) move operation does this, too.
This results in false test assertions in case it does so.

Fix this by handling temporary MMIO from the first memslot move operation
in the test guest code, too.

Fixes: 8a0639fe9201 ("KVM: sefltests: Add explicit synchronization to move mem region test")
Signed-off-by: Maciej S. Szmigiero <maciej.szmigiero@oracle.com>
---
```
#### [PATCH 1/9] target/mips: Introduce ase_msa_available() helper
##### From: =?utf-8?q?Philippe_Mathieu-Daud=C3=A9?= <f4bug@amsat.org>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 8bit
X-Patchwork-Submitter: =?utf-8?q?Philippe_Mathieu-Daud=C3=A9?=
 <f4bug@amsat.org>
X-Patchwork-Id: 11946771
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.8 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT autolearn=ham
	autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 57F48C71155
	for <kvm@archiver.kernel.org>; Wed,  2 Dec 2020 18:45:06 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id ED6AC206D5
	for <kvm@archiver.kernel.org>; Wed,  2 Dec 2020 18:45:05 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2389552AbgLBSpF (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Wed, 2 Dec 2020 13:45:05 -0500
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:54318 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S2387884AbgLBSpE (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 2 Dec 2020 13:45:04 -0500
Received: from mail-ej1-x643.google.com (mail-ej1-x643.google.com
 [IPv6:2a00:1450:4864:20::643])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 6F23AC0617A6
        for <kvm@vger.kernel.org>; Wed,  2 Dec 2020 10:44:24 -0800 (PST)
Received: by mail-ej1-x643.google.com with SMTP id 7so5988372ejm.0
        for <kvm@vger.kernel.org>; Wed, 02 Dec 2020 10:44:24 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=sender:from:to:cc:subject:date:message-id:in-reply-to:references
         :mime-version:content-transfer-encoding;
        bh=xk/Zq1xXAUYu4vZ1FKZqQpHvoK7NrbyHrURbYsCyDoM=;
        b=FmswlJTao8Y2QdCEg1sJYydqulsPhnWQDxYz/to1zmq5YjEqi71b5YaHRpWojdP/pj
         E65O/5tgKwiq76nJ47IZVH7aFOu1LQlbyv20N3Xn9KFhvlz3DCFX2EytF0zx8i2aakFX
         QMDM15WQTKlX6W8yRsE7Ns42BAZeVDFkLSOHoHrCxYyTIB8UbKwuYFUQiXiSJhU09WRp
         Yfpf4RzTkHfMOtBsJRmWulnVRrm+NK/LG+R6Pu0V2j1DrSIaporPi+O+4OZOJeMDgxfp
         OfIuRiQfVo1nmg00KCLbWr9UMunQGGWMwZqmzKQZtHPjmK4QrJipVOpqwFpjbANs9/PJ
         5djA==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:sender:from:to:cc:subject:date:message-id
         :in-reply-to:references:mime-version:content-transfer-encoding;
        bh=xk/Zq1xXAUYu4vZ1FKZqQpHvoK7NrbyHrURbYsCyDoM=;
        b=UDNtupZs0V4Wv446q3Yo3W7fV16Suw9bdTFnX1QdVEI3RHIV/+g4QBCAOpoPKhpxlP
         Ico4VZYhMFKJik89f8frLZyifCmypZ9WebvNjaKZYDaYUCpnDjsYhBkMdgiW/UcVN9gP
         812Hdbm0Mqa8+7NJDGQepZc5p2RvvuO6to77kIN4iuGpnX7KLN4Fr8oj5dJkEe1lTOJc
         U91xmjauMHCxOOdKGVNgMOvpgh3yzQpvKPP/VdbyGlAkqA1K7szUaqUVXlTa8h+SArOP
         v4pvUCnKgRwFT55lnXa1UtAL3f50Wh46Ayy9on8z0KJhHC6qTBzt4w8MTGO94At98Bwc
         OG+Q==
X-Gm-Message-State: AOAM530U4gU3rarukZy8BEbZnTd+ebPKT7xIKaHayX0n7ZL06Nfhdey3
        0vsFmRb7oZbxfnSR0bJ5bJ8=
X-Google-Smtp-Source: 
 ABdhPJybp/7ChjWK/qvpZtRmgllgrpJg/wIciJFaxPkewzGyNulPMFf/2FW4ujzwwpuSx1b/+v1FNw==
X-Received: by 2002:a17:906:d10f:: with SMTP id
 b15mr1095121ejz.268.1606934663190;
        Wed, 02 Dec 2020 10:44:23 -0800 (PST)
Received: from x1w.redhat.com (111.red-88-21-205.staticip.rima-tde.net.
 [88.21.205.111])
        by smtp.gmail.com with ESMTPSA id
 t19sm440464eje.86.2020.12.02.10.44.21
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Wed, 02 Dec 2020 10:44:22 -0800 (PST)
Sender: =?utf-8?q?Philippe_Mathieu-Daud=C3=A9?=
  <philippe.mathieu.daude@gmail.com>
From: =?utf-8?q?Philippe_Mathieu-Daud=C3=A9?= <f4bug@amsat.org>
To: qemu-devel@nongnu.org
Cc: Jiaxun Yang <jiaxun.yang@flygoat.com>, Huacai Chen <chenhc@lemote.com>,
 Richard Henderson <richard.henderson@linaro.org>, kvm@vger.kernel.org,
 Aleksandar Rikalo <aleksandar.rikalo@syrmia.com>,
 Paolo Bonzini <pbonzini@redhat.com>, Aurelien Jarno <aurelien@aurel32.net>,
	=?utf-8?q?Philippe_Mathieu-Daud=C3=A9?= <f4bug@amsat.org>
Subject: [PATCH 1/9] target/mips: Introduce ase_msa_available() helper
Date: Wed,  2 Dec 2020 19:44:07 +0100
Message-Id: <20201202184415.1434484-2-f4bug@amsat.org>
X-Mailer: git-send-email 2.26.2
In-Reply-To: <20201202184415.1434484-1-f4bug@amsat.org>
References: <20201202184415.1434484-1-f4bug@amsat.org>
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Instead of accessing CP0_Config3 directly and checking
the 'MSA Present' bit, introduce an explicit helper,
making the code easier to read.

Signed-off-by: Philippe Mathieu-Daudé <f4bug@amsat.org>
---
 target/mips/internal.h  |  6 ++++++
 target/mips/kvm.c       | 12 ++++++------
 target/mips/translate.c |  8 +++-----
 3 files changed, 15 insertions(+), 11 deletions(-)

```
#### [PATCH v1] vfio/pci: Add support for opregion v2.0+
##### From: Fred Gao <fred.gao@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Fred Gao <fred.gao@intel.com>
X-Patchwork-Id: 11945339
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-14.8 required=3.0 tests=BAYES_00,
	DATE_IN_FUTURE_06_12,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,
	INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED,
	USER_AGENT_GIT autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 89DA6C83017
	for <kvm@archiver.kernel.org>; Wed,  2 Dec 2020 09:18:11 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 4F42222206
	for <kvm@archiver.kernel.org>; Wed,  2 Dec 2020 09:18:11 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2387972AbgLBJSF (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Wed, 2 Dec 2020 04:18:05 -0500
Received: from mga03.intel.com ([134.134.136.65]:4848 "EHLO mga03.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S2387658AbgLBJSF (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 2 Dec 2020 04:18:05 -0500
IronPort-SDR: 
 ClIbe/tXNcNINUlmnbTYoDSQDyqFewgGXtjJYgvhc8L2uYlf77ojbb5l23hFJDJbxREqeiUqB/
 BFvEfZZTmD7A==
X-IronPort-AV: E=McAfee;i="6000,8403,9822"; a="173082426"
X-IronPort-AV: E=Sophos;i="5.78,386,1599548400";
   d="scan'208";a="173082426"
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from fmsmga004.fm.intel.com ([10.253.24.48])
  by orsmga103.jf.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 02 Dec 2020 01:17:22 -0800
IronPort-SDR: 
 1PkSdBBPN4QhBoDrBUwcsM0XvfJYNIjRheEQurMBt/wBCoP0zIuEj19MI391l2UOXk24ITR4pA
 6Iu0R19cvrJQ==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.78,386,1599548400";
   d="scan'208";a="365205218"
Received: from cfl-host.sh.intel.com ([10.239.158.59])
  by fmsmga004.fm.intel.com with ESMTP; 02 Dec 2020 01:17:20 -0800
From: Fred Gao <fred.gao@intel.com>
To: kvm@vger.kernel.org, intel-gfx@lists.freedesktop.org
Cc: Fred Gao <fred.gao@intel.com>,
        Zhenyu Wang <zhenyuw@linux.intel.com>,
        Swee Yee Fonn <swee.yee.fonn@intel.com>
Subject: [PATCH v1] vfio/pci: Add support for opregion v2.0+
Date: Thu,  3 Dec 2020 01:12:49 +0800
Message-Id: <20201202171249.17083-1-fred.gao@intel.com>
X-Mailer: git-send-email 2.24.1.1.gb6d4d82bd5
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

When VBT data exceeds 6KB size and cannot be within mailbox #4 starting
from opregion v2.0+, Extended VBT region, next to opregion, is used to
hold the VBT data, so the total size will be opregion size plus
extended VBT region size.

For opregion 2.1+: since rvda is relative offset from opregion base,
rvda as extended VBT start offset should be same as opregion size.

For opregion 2.0: the only difference between opregion 2.0 and 2.1 is
rvda addressing mode besides the version. since rvda is physical host
VBT address and cannot be directly used in guest, it is faked into
opregion 2.1's relative offset.

Cc: Zhenyu Wang <zhenyuw@linux.intel.com>
Signed-off-by: Swee Yee Fonn <swee.yee.fonn@intel.com>
Signed-off-by: Fred Gao <fred.gao@intel.com>
---
 drivers/vfio/pci/vfio_pci_igd.c | 44 +++++++++++++++++++++++++++++++++
 1 file changed, 44 insertions(+)

```
#### [PATCH] vhost_vdpa: return -EFAULT if copy_to_user() fails
##### From: Dan Carpenter <dan.carpenter@oracle.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Dan Carpenter <dan.carpenter@oracle.com>
X-Patchwork-Id: 11944801
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-17.2 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_CR_TRAILER,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,
	UNPARSEABLE_RELAY autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 9C473C64E7C
	for <kvm@archiver.kernel.org>; Wed,  2 Dec 2020 06:45:52 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 442EF20C56
	for <kvm@archiver.kernel.org>; Wed,  2 Dec 2020 06:45:52 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728627AbgLBGpg (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Wed, 2 Dec 2020 01:45:36 -0500
Received: from aserp2130.oracle.com ([141.146.126.79]:39260 "EHLO
        aserp2130.oracle.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726716AbgLBGpf (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 2 Dec 2020 01:45:35 -0500
Received: from pps.filterd (aserp2130.oracle.com [127.0.0.1])
        by aserp2130.oracle.com (8.16.0.42/8.16.0.42) with SMTP id
 0B26P3xj143335;
        Wed, 2 Dec 2020 06:44:51 GMT
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=oracle.com;
 h=date : from : to : cc
 : subject : message-id : mime-version : content-type; s=corp-2020-01-29;
 bh=EQ5e48qxUz457ErMWHJa1v5YZ7dfBdW+/4iHFac2dJk=;
 b=F2lOXEXvsJ4bKaK7YorAUdplmflz4xaNofiHseI9GT2nYJvAXzONkjACQEpzDDIU/zZ2
 fEtZNtlMRxWpgyresjK9u5Swa61WLHs2Yb9KILtngo/0Uj8K4a1eKF1i7SobyxA9NjNa
 EwPoN7Uj+riIX8n0+aglQt4tVOoQkYgA5vKgRgchHg6THv9xakCaQl1UJoX4cE5JPP3h
 IX9yaId+s9CXkWOuBrwKeoJ9UBFlbBPLngqfuDGaOB3SD4kEoPyLrVy54yvdQ60Bu7hk
 PA2ae2cBidEZguzm0ogOmIDNhlwRmeEz7LWf4MI65lLpviWy2Ibhqm8rJO2M3s4jIjhx 0g==
Received: from aserp3030.oracle.com (aserp3030.oracle.com [141.146.126.71])
        by aserp2130.oracle.com with ESMTP id 353c2axn1j-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=FAIL);
        Wed, 02 Dec 2020 06:44:51 +0000
Received: from pps.filterd (aserp3030.oracle.com [127.0.0.1])
        by aserp3030.oracle.com (8.16.0.42/8.16.0.42) with SMTP id
 0B26QQeh006726;
        Wed, 2 Dec 2020 06:44:51 GMT
Received: from userv0121.oracle.com (userv0121.oracle.com [156.151.31.72])
        by aserp3030.oracle.com with ESMTP id 35404nvk2f-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Wed, 02 Dec 2020 06:44:51 +0000
Received: from abhmp0017.oracle.com (abhmp0017.oracle.com [141.146.116.23])
        by userv0121.oracle.com (8.14.4/8.13.8) with ESMTP id 0B26indX021012;
        Wed, 2 Dec 2020 06:44:50 GMT
Received: from mwanda (/102.36.221.92)
        by default (Oracle Beehive Gateway v4.0)
        with ESMTP ; Tue, 01 Dec 2020 22:44:49 -0800
Date: Wed, 2 Dec 2020 09:44:43 +0300
From: Dan Carpenter <dan.carpenter@oracle.com>
To: "Michael S. Tsirkin" <mst@redhat.com>,
        Jason Wang <jasowang@redhat.com>
Cc: kvm@vger.kernel.org, virtualization@lists.linux-foundation.org,
        kernel-janitors@vger.kernel.org
Subject: [PATCH] vhost_vdpa: return -EFAULT if copy_to_user() fails
Message-ID: <X8c32z5EtDsMyyIL@mwanda>
MIME-Version: 1.0
Content-Disposition: inline
X-Mailer: git-send-email haha only kidding
X-Proofpoint-Virus-Version: vendor=nai engine=6000 definitions=9822
 signatures=668682
X-Proofpoint-Spam-Details: rule=notspam policy=default score=0 suspectscore=0
 bulkscore=0
 malwarescore=0 mlxscore=0 mlxlogscore=999 phishscore=0 spamscore=0
 adultscore=0 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.12.0-2009150000 definitions=main-2012020039
X-Proofpoint-Virus-Version: vendor=nai engine=6000 definitions=9822
 signatures=668682
X-Proofpoint-Spam-Details: rule=notspam policy=default score=0 suspectscore=0
 lowpriorityscore=0
 clxscore=1015 bulkscore=0 mlxlogscore=999 phishscore=0 malwarescore=0
 spamscore=0 adultscore=0 mlxscore=0 priorityscore=1501 impostorscore=0
 classifier=spam adjust=0 reason=mlx scancount=1 engine=8.12.0-2009150000
 definitions=main-2012020039
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The copy_to_user() function returns the number of bytes remaining to be
copied but this should return -EFAULT to the user.

Fixes: 1b48dc03e575 ("vhost: vdpa: report iova range")
Signed-off-by: Dan Carpenter <dan.carpenter@oracle.com>
Acked-by: Jason Wang <jasowang@redhat.com>
Reviewed-by: Stefano Garzarella <sgarzare@redhat.com>
---
 drivers/vhost/vdpa.c | 4 +++-
 1 file changed, 3 insertions(+), 1 deletion(-)

```
