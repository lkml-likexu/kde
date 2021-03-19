#### [kvm-unit-tests PATCH v2 1/4] lib/string: Add strnlen, strrchr and strtoul
##### From: Nikos Nikoleris <nikos.nikoleris@arm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Nikos Nikoleris <nikos.nikoleris@arm.com>
X-Patchwork-Id: 12148953
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.8 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED,USER_AGENT_GIT
	autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 5A6DCC433E9
	for <kvm@archiver.kernel.org>; Thu, 18 Mar 2021 18:08:46 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 2911964D74
	for <kvm@archiver.kernel.org>; Thu, 18 Mar 2021 18:08:46 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S232474AbhCRSIM (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Thu, 18 Mar 2021 14:08:12 -0400
Received: from foss.arm.com ([217.140.110.172]:45654 "EHLO foss.arm.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S230365AbhCRSIE (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 18 Mar 2021 14:08:04 -0400
Received: from usa-sjc-imap-foss1.foss.arm.com (unknown [10.121.207.14])
        by usa-sjc-mx-foss1.foss.arm.com (Postfix) with ESMTP id DB220101E;
        Thu, 18 Mar 2021 11:08:03 -0700 (PDT)
Received: from localhost.localdomain (unknown [172.31.20.19])
        by usa-sjc-imap-foss1.foss.arm.com (Postfix) with ESMTPSA id
 3736B3F70D;
        Thu, 18 Mar 2021 11:08:02 -0700 (PDT)
From: Nikos Nikoleris <nikos.nikoleris@arm.com>
To: kvm@vger.kernel.org
Cc: pbonzini@redhat.com, drjones@redhat.com, alexandru.elisei@arm.com,
        andre.przywara@arm.com, Nikos Nikoleris <nikos.nikoleris@arm.com>
Subject: [kvm-unit-tests PATCH v2 1/4] lib/string: Add strnlen,
 strrchr and strtoul
Date: Thu, 18 Mar 2021 18:07:24 +0000
Message-Id: <20210318180727.116004-2-nikos.nikoleris@arm.com>
X-Mailer: git-send-email 2.25.1
In-Reply-To: <20210318180727.116004-1-nikos.nikoleris@arm.com>
References: <20210318180727.116004-1-nikos.nikoleris@arm.com>
MIME-Version: 1.0
X-ARM-No-Footer: FoSSMail
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This change adds two functions from <string.h> and one from <stdlib.h>
in preparation for an update in libfdt.

Signed-off-by: Nikos Nikoleris <nikos.nikoleris@arm.com>
---
 lib/stdlib.h | 12 +++++++++
 lib/string.h |  4 ++-
 lib/string.c | 70 ++++++++++++++++++++++++++++++++++++++++++++++------
 3 files changed, 77 insertions(+), 9 deletions(-)
 create mode 100644 lib/stdlib.h

diff --git a/lib/stdlib.h b/lib/stdlib.h
new file mode 100644
index 0000000..e8abe75
--- /dev/null
+++ b/lib/stdlib.h
@@ -0,0 +1,12 @@
+/*
+ * Header for libc stdlib functions
+ *
+ * This code is free software; you can redistribute it and/or modify it
+ * under the terms of the GNU Library General Public License version 2.
+ */
+#ifndef _STDLIB_H_
+#define _STDLIB_H_
+
+unsigned long int strtoul(const char *nptr, char **endptr, int base);
+
+#endif /* _STDLIB_H_ */
```
#### [GIT PULL] VFIO fixes for v5.12-rc4
##### From: Alex Williamson <alex.williamson@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Alex Williamson <alex.williamson@redhat.com>
X-Patchwork-Id: 12149071
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-21.0 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_PATCH,INCLUDES_PULL_REQUEST,MAILING_LIST_MULTI,MENTIONS_GIT_HOSTING,
	SPF_HELO_NONE,SPF_PASS autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id D72B4C433E6
	for <kvm@archiver.kernel.org>; Thu, 18 Mar 2021 19:16:32 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 745FF64F11
	for <kvm@archiver.kernel.org>; Thu, 18 Mar 2021 19:16:32 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S232774AbhCRTP7 (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Thu, 18 Mar 2021 15:15:59 -0400
Received: from us-smtp-delivery-124.mimecast.com ([216.205.24.124]:44278 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S232728AbhCRTPq (ORCPT
        <rfc822;kvm@vger.kernel.org>); Thu, 18 Mar 2021 15:15:46 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1616094945;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:content-type:content-type:
         content-transfer-encoding:content-transfer-encoding;
        bh=UrN6I/K64VfQCttfF8qXoz5SoRAyjeSvtF00DW1eR4I=;
        b=KunJ3BS6ddKULC7PI8y+mTiQ3DFKpdQtYicC9jFs4jTKMOJgxLkTAxlgdljnym/Foqg7UE
        60egEGQBMuA8GboAy6xg+LmZ/WxuqtqQEc/LNK3pDErznSx8ovpQgPLW7fbkiKPer+cz7u
        Yf8igH+arbD5dI/Mzm0B8mXgh7y14ds=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-361-3LcEhTwLPCSXOj0Z9u-Bog-1; Thu, 18 Mar 2021 15:15:41 -0400
X-MC-Unique: 3LcEhTwLPCSXOj0Z9u-Bog-1
Received: from smtp.corp.redhat.com (int-mx04.intmail.prod.int.phx2.redhat.com
 [10.5.11.14])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 2EC1018C89C4;
        Thu, 18 Mar 2021 19:15:40 +0000 (UTC)
Received: from omen.home.shazbot.org (ovpn-112-255.phx2.redhat.com
 [10.3.112.255])
        by smtp.corp.redhat.com (Postfix) with ESMTP id A60215D9C6;
        Thu, 18 Mar 2021 19:15:39 +0000 (UTC)
Date: Thu, 18 Mar 2021 13:15:39 -0600
From: Alex Williamson <alex.williamson@redhat.com>
To: Linus Torvalds <torvalds@linux-foundation.org>
Cc: <linux-kernel@vger.kernel.org>,
        "kvm@vger.kernel.org" <kvm@vger.kernel.org>,
        steven.sistare@oracle.com, jgg@nvidia.com,
        daniel.m.jordan@oracle.com
Subject: [GIT PULL] VFIO fixes for v5.12-rc4
Message-ID: <20210318131539.1c66212d@omen.home.shazbot.org>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.14
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Hi Linus,

The following changes since commit 1e28eed17697bcf343c6743f0028cc3b5dd88bf0:

  Linux 5.12-rc3 (2021-03-14 14:41:02 -0700)

are available in the Git repository at:

  git://github.com/awilliam/linux-vfio.git tags/vfio-v5.12-rc4

for you to fetch changes up to 4ab4fcfce5b540227d80eb32f1db45ab615f7c92:

  vfio/type1: fix vaddr_get_pfns() return in vfio_pin_page_external() (2021-03-16 10:39:29 -0600)

----------------------------------------------------------------
VFIO fixes for v5.12-rc4

 - Fix 32-bit issue with new unmap-all flag (Steve Sistare)

 - Various Kconfig changes for better coverage (Jason Gunthorpe)

 - Fix to batch pinning support (Daniel Jordan)

----------------------------------------------------------------
Daniel Jordan (1):
      vfio/type1: fix vaddr_get_pfns() return in vfio_pin_page_external()

Jason Gunthorpe (4):
      vfio: IOMMU_API should be selected
      vfio-platform: Add COMPILE_TEST to VFIO_PLATFORM
      ARM: amba: Allow some ARM_AMBA users to compile with COMPILE_TEST
      vfio: Depend on MMU

Steve Sistare (1):
      vfio/type1: fix unmap all on ILP32

 drivers/vfio/Kconfig            |  4 ++--
 drivers/vfio/platform/Kconfig   |  4 ++--
 drivers/vfio/vfio_iommu_type1.c | 20 ++++++++++++--------
 include/linux/amba/bus.h        | 11 +++++++++++
 4 files changed, 27 insertions(+), 12 deletions(-)
```
#### [GIT PULL] vhost: cleanups and fixes
##### From: "Michael S. Tsirkin" <mst@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: "Michael S. Tsirkin" <mst@redhat.com>
X-Patchwork-Id: 12148963
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-26.0 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_CR_TRAILER,INCLUDES_PATCH,INCLUDES_PULL_REQUEST,MAILING_LIST_MULTI,
	MENTIONS_GIT_HOSTING,SPF_HELO_NONE,SPF_PASS autolearn=ham autolearn_force=no
	version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 7A339C433DB
	for <kvm@archiver.kernel.org>; Thu, 18 Mar 2021 18:12:30 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 2F29C64F1D
	for <kvm@archiver.kernel.org>; Thu, 18 Mar 2021 18:12:30 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S232479AbhCRSL6 (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Thu, 18 Mar 2021 14:11:58 -0400
Received: from us-smtp-delivery-124.mimecast.com ([63.128.21.124]:38215 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S232465AbhCRSLw (ORCPT
        <rfc822;kvm@vger.kernel.org>); Thu, 18 Mar 2021 14:11:52 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1616091103;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:content-type:content-type;
        bh=WP7PnNSr4BR9a1LVBwXMPx5QETfjMgS7zmkwK2xedWo=;
        b=NzuKqqOgrrUtipYBhPeU5Q2FEHhzzOLJUkwgSvy7fVhSymfgrNFNZeW8yX7s6zdwVRKp0t
        SXS1DfZMqHjO8P0DjYeW+UyV//InAzIxZE47n97mSfIxDl/Pt+7N7uua+tPubwTafqJm80
        s8r7cTQuv8yF3GUxHbl3txA9rC4Kp+g=
Received: from mail-wr1-f72.google.com (mail-wr1-f72.google.com
 [209.85.221.72]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-308-MyzttdWPPuCOaeZlG7BoCg-1; Thu, 18 Mar 2021 14:11:41 -0400
X-MC-Unique: MyzttdWPPuCOaeZlG7BoCg-1
Received: by mail-wr1-f72.google.com with SMTP id i5so20485233wrp.8
        for <kvm@vger.kernel.org>; Thu, 18 Mar 2021 11:11:40 -0700 (PDT)
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:date:from:to:cc:subject:message-id:mime-version
         :content-disposition;
        bh=WP7PnNSr4BR9a1LVBwXMPx5QETfjMgS7zmkwK2xedWo=;
        b=P+Ex3tx3u8JwXM5o08qKQPKdyzezz2db6izOFQyMc0l63nb5SyG3VBEqB/g7hQ2Tm8
         lCaTS4AUju1rMmZAgZwkqqwWqcfP4pXP+iTNWwd6vw6O/ZKr4BCic/t6pGWXJqa7z9Oi
         0nv5MNhFLuhYb9zeqqOn+C+X4xCMoLjDmFA9Ur1OVM1DxgGzsmURESeNnTC6PRD9sIbp
         q1RfCH3WTqCJo0nHGPXKalv63rxJeBZWjn9GgsvEo3H6hxVzNa38aXof/twlBx7iL/yR
         AmRJVuD1NA3g3TWSRJQ4tQ0I0DztiVpDIiApDSmV3wNpqmSPW+JugzwWe//1Y/bY4vJj
         84qg==
X-Gm-Message-State: AOAM531HHYef7xs8IwhulpYAjrsUhowSu/HD5+EWGTAiuWd1aXfgDDdG
        ufTpNWwgqNzZEy/ypSnnVwk7I37XcmCtOAQIdLS+okx8wYg6O/FUDd+jvWwQk5RyT9kYy3M91TR
        yCQ78zNvg0oFW
X-Received: by 2002:a5d:6810:: with SMTP id w16mr510492wru.333.1616091099217;
        Thu, 18 Mar 2021 11:11:39 -0700 (PDT)
X-Google-Smtp-Source: 
 ABdhPJwFTfjChgFyUXnBDg4awB1ZFX0fIcyN9S9XgyGks/aa0h+c9tuWlTuolWTJOqxYehca3p6+ug==
X-Received: by 2002:a5d:6810:: with SMTP id w16mr510479wru.333.1616091099081;
        Thu, 18 Mar 2021 11:11:39 -0700 (PDT)
Received: from redhat.com (bzq-79-180-2-31.red.bezeqint.net. [79.180.2.31])
        by smtp.gmail.com with ESMTPSA id
 s8sm3686155wrn.97.2021.03.18.11.11.36
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Thu, 18 Mar 2021 11:11:38 -0700 (PDT)
Date: Thu, 18 Mar 2021 14:11:35 -0400
From: "Michael S. Tsirkin" <mst@redhat.com>
To: Linus Torvalds <torvalds@linux-foundation.org>
Cc: kvm@vger.kernel.org, virtualization@lists.linux-foundation.org,
        netdev@vger.kernel.org, linux-kernel@vger.kernel.org,
        gdawar.xilinx@gmail.com, jasowang@redhat.com,
        lingshan.zhu@intel.com, lvivier@redhat.com, mst@redhat.com,
        parav@nvidia.com, sgarzare@redhat.com, stable@vger.kernel.org,
        tangbin@cmss.chinamobile.com, xianting_tian@126.com
Subject: [GIT PULL] vhost: cleanups and fixes
Message-ID: <20210318141135-mutt-send-email-mst@kernel.org>
MIME-Version: 1.0
Content-Disposition: inline
X-Mutt-Fcc: =sent
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The following changes since commit 16c10bede8b3d8594279752bf53153491f3f944f:

  virtio-input: add multi-touch support (2021-02-23 07:52:59 -0500)

are available in the Git repository at:

  https://git.kernel.org/pub/scm/linux/kernel/git/mst/vhost.git tags/for_linus

for you to fetch changes up to 0bde59c1723a29e294765c96dbe5c7fb639c2f96:

  vhost-vdpa: set v->config_ctx to NULL if eventfd_ctx_fdget() fails (2021-03-14 18:10:07 -0400)

----------------------------------------------------------------
virtio: fixes, cleanups

Some fixes and cleanups all over the place.

Signed-off-by: Michael S. Tsirkin <mst@redhat.com>

----------------------------------------------------------------
Gautam Dawar (1):
      vhost_vdpa: fix the missing irq_bypass_unregister_producer() invocation

Jason Wang (1):
      vdpa: set the virtqueue num during register

Laurent Vivier (1):
      vhost: Fix vhost_vq_reset()

Parav Pandit (1):
      vdpa_sim: Skip typecasting from void*

Stefano Garzarella (2):
      vhost-vdpa: fix use-after-free of v->config_ctx
      vhost-vdpa: set v->config_ctx to NULL if eventfd_ctx_fdget() fails

Tang Bin (1):
      virtio-mmio: Use to_virtio_mmio_device() to simply code

Xianting Tian (1):
      virtio: remove export for virtio_config_{enable, disable}

 drivers/vdpa/ifcvf/ifcvf_main.c      |  5 ++---
 drivers/vdpa/mlx5/net/mlx5_vnet.c    |  4 ++--
 drivers/vdpa/vdpa.c                  | 18 ++++++++++--------
 drivers/vdpa/vdpa_sim/vdpa_sim.c     |  2 +-
 drivers/vdpa/vdpa_sim/vdpa_sim_net.c |  5 ++---
 drivers/vhost/vdpa.c                 | 20 +++++++++++---------
 drivers/vhost/vhost.c                |  2 +-
 drivers/virtio/virtio.c              |  6 ++----
 drivers/virtio/virtio_mmio.c         |  3 +--
 include/linux/vdpa.h                 | 10 +++++-----
 include/linux/virtio.h               |  2 --
 11 files changed, 37 insertions(+), 40 deletions(-)
```
#### [PATCH v2 01/11] KVM: arm64: Provide KVM's own save/restore SVE primitives
##### From: Marc Zyngier <maz@kernel.org>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Marc Zyngier <maz@kernel.org>
X-Patchwork-Id: 12148057
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No,
 score=-17.0 required=3.0 tests=BAYES_00,INCLUDES_CR_TRAILER,
	INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED,
	USER_AGENT_GIT autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id B5494C433E0
	for <kvm@archiver.kernel.org>; Thu, 18 Mar 2021 12:26:59 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 7AA8E64F69
	for <kvm@archiver.kernel.org>; Thu, 18 Mar 2021 12:26:59 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S230473AbhCRM0V (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Thu, 18 Mar 2021 08:26:21 -0400
Received: from mail.kernel.org ([198.145.29.99]:45298 "EHLO mail.kernel.org"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S229747AbhCRMZp (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 18 Mar 2021 08:25:45 -0400
Received: from disco-boy.misterjones.org (disco-boy.misterjones.org
 [51.254.78.96])
        (using TLSv1.2 with cipher ECDHE-RSA-AES256-GCM-SHA384 (256/256 bits))
        (No client certificate requested)
        by mail.kernel.org (Postfix) with ESMTPSA id 2B7A464F53;
        Thu, 18 Mar 2021 12:25:45 +0000 (UTC)
Received: from 78.163-31-62.static.virginmediabusiness.co.uk ([62.31.163.78]
 helo=why.lan)
        by disco-boy.misterjones.org with esmtpsa  (TLS1.3) tls
 TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384
        (Exim 4.94)
        (envelope-from <maz@kernel.org>)
        id 1lMrih-002OZW-E6; Thu, 18 Mar 2021 12:25:43 +0000
From: Marc Zyngier <maz@kernel.org>
To: kvmarm@lists.cs.columbia.edu, linux-arm-kernel@lists.infradead.org,
        kvm@vger.kernel.org
Cc: dave.martin@arm.com, daniel.kiss@arm.com,
        Will Deacon <will@kernel.org>,
        Catalin Marinas <catalin.marinas@arm.com>,
        James Morse <james.morse@arm.com>,
        Julien Thierry <julien.thierry.kdev@gmail.com>,
        Suzuki K Poulose <suzuki.poulose@arm.com>,
        broonie@kernel.org, ascull@google.com, qperret@google.com,
        kernel-team@android.com
Subject: [PATCH v2 01/11] KVM: arm64: Provide KVM's own save/restore SVE
 primitives
Date: Thu, 18 Mar 2021 12:25:22 +0000
Message-Id: <20210318122532.505263-2-maz@kernel.org>
X-Mailer: git-send-email 2.29.2
In-Reply-To: <20210318122532.505263-1-maz@kernel.org>
References: <20210318122532.505263-1-maz@kernel.org>
MIME-Version: 1.0
X-SA-Exim-Connect-IP: 62.31.163.78
X-SA-Exim-Rcpt-To: kvmarm@lists.cs.columbia.edu,
 linux-arm-kernel@lists.infradead.org, kvm@vger.kernel.org,
 dave.martin@arm.com, daniel.kiss@arm.com, will@kernel.org,
 catalin.marinas@arm.com, james.morse@arm.com, julien.thierry.kdev@gmail.com,
 suzuki.poulose@arm.com, broonie@kernel.org, ascull@google.com,
 qperret@google.com, kernel-team@android.com
X-SA-Exim-Mail-From: maz@kernel.org
X-SA-Exim-Scanned: No (on disco-boy.misterjones.org);
 SAEximRunCond expanded to false
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

as we are about to change the way KVM deals with SVE, provide
KVM with its own save/restore SVE primitives.

No functional change intended.

Acked-by: Will Deacon <will@kernel.org>
Signed-off-by: Marc Zyngier <maz@kernel.org>
---
 arch/arm64/include/asm/fpsimdmacros.h   |  2 ++
 arch/arm64/include/asm/kvm_hyp.h        |  2 ++
 arch/arm64/kvm/hyp/fpsimd.S             | 10 ++++++++++
 arch/arm64/kvm/hyp/include/hyp/switch.h | 10 +++++-----
 4 files changed, 19 insertions(+), 5 deletions(-)

```
#### [kvm-unit-tests PATCH v2] configure: arm/arm64: Add --earlycon option to set UART type and address
##### From: Alexandru Elisei <alexandru.elisei@arm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Alexandru Elisei <alexandru.elisei@arm.com>
X-Patchwork-Id: 12148541
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.8 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED,USER_AGENT_GIT
	autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id DF072C433E6
	for <kvm@archiver.kernel.org>; Thu, 18 Mar 2021 16:20:53 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 96A6A64F4D
	for <kvm@archiver.kernel.org>; Thu, 18 Mar 2021 16:20:53 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S232009AbhCRQUT (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Thu, 18 Mar 2021 12:20:19 -0400
Received: from foss.arm.com ([217.140.110.172]:44310 "EHLO foss.arm.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S232065AbhCRQUC (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 18 Mar 2021 12:20:02 -0400
Received: from usa-sjc-imap-foss1.foss.arm.com (unknown [10.121.207.14])
        by usa-sjc-mx-foss1.foss.arm.com (Postfix) with ESMTP id 918EE31B;
        Thu, 18 Mar 2021 09:20:01 -0700 (PDT)
Received: from monolith.localdoman (unknown [172.31.20.19])
        by usa-sjc-imap-foss1.foss.arm.com (Postfix) with ESMTPSA id
 D207B3F792;
        Thu, 18 Mar 2021 09:20:00 -0700 (PDT)
From: Alexandru Elisei <alexandru.elisei@arm.com>
To: drjones@redhat.com, kvm@vger.kernel.org,
        kvmarm@lists.cs.columbia.edu
Cc: pbonzini@redhat.com
Subject: [kvm-unit-tests PATCH v2] configure: arm/arm64: Add --earlycon option
 to set UART type and address
Date: Thu, 18 Mar 2021 16:20:22 +0000
Message-Id: <20210318162022.84482-1-alexandru.elisei@arm.com>
X-Mailer: git-send-email 2.30.2
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Currently, the UART early address is set indirectly with the --vmm option
and there are only two possible values: if the VMM is qemu (the default),
then the UART address is set to 0x09000000; if the VMM is kvmtool, then the
UART address is set to 0x3f8.

The upstream kvmtool commit 45b4968e0de1 ("hw/serial: ARM/arm64: Use MMIO
at higher addresses") changed the UART address to 0x1000000, and
kvm-unit-tests so far hasn't had mechanism to let the user set a specific
address, which means that for recent versions of kvmtool the early UART
won't be available.

This situation will only become worse as kvm-unit-tests gains support to
run as an EFI app, as each platform will have their own UART type and
address.

To address both issues, a new configure option is added, --earlycon. The
syntax and semantics are identical to the kernel parameter with the same
name. For example, for kvmtool, --earlycon=uart,mmio,0x1000000 will set the
correct UART address. Specifying this option will overwrite the UART
address set by --vmm.

At the moment, the UART type and register width parameters are ignored
since both qemu's and kvmtool's UART emulation use the same offset for the
TX register and no other registers are used by kvm-unit-tests, but the
parameters will become relevant once EFI support is added.

Signed-off-by: Alexandru Elisei <alexandru.elisei@arm.com>
---
Besides working with current versions of kvmtool, this will also make early
console work if the user specifies a custom memory layout [1] (patches are
old, but I plan to pick them up at some point in the future).

Changes in v2:
* kvmtool patches were merged, so I reworked the commit message to point to
  the corresponding kvmtool commit.
* Restricted pl011 register size to 32 bits, as per Arm Base System
  Architecture 1.0 (DEN0094A), and to match Linux.
* Reworked the way the fields are extracted to make it more precise
  (without the -s argument, the entire string is echo'ed when no delimiter
  is found).
* The changes are not trivial, so I dropped Drew's Reviewed-by.

[1] https://lore.kernel.org/kvm/1569245722-23375-1-git-send-email-alexandru.elisei@arm.com/

 configure | 61 +++++++++++++++++++++++++++++++++++++++++++++++++++++++
 1 file changed, 61 insertions(+)

```
#### [PATCH v5 1/5] KVM: x86: dump_vmcs should not assume GUEST_IA32_EFER is valid
##### From: David Edmondson <david.edmondson@oracle.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: David Edmondson <david.edmondson@oracle.com>
X-Patchwork-Id: 12148021
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.8 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,UNPARSEABLE_RELAY,USER_AGENT_GIT
	autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 1FA97C4332B
	for <kvm@archiver.kernel.org>; Thu, 18 Mar 2021 12:17:07 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id E46D864F40
	for <kvm@archiver.kernel.org>; Thu, 18 Mar 2021 12:17:06 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S231137AbhCRMQf (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Thu, 18 Mar 2021 08:16:35 -0400
Received: from wforward4-smtp.messagingengine.com ([64.147.123.34]:60899 "EHLO
        wforward4-smtp.messagingengine.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S230408AbhCRMP7 (ORCPT
        <rfc822;kvm@vger.kernel.org>); Thu, 18 Mar 2021 08:15:59 -0400
Received: from compute2.internal (compute2.nyi.internal [10.202.2.42])
        by mailforward.west.internal (Postfix) with ESMTP id 700C4FE1;
        Thu, 18 Mar 2021 08:08:47 -0400 (EDT)
Received: from mailfrontend2 ([10.202.2.163])
  by compute2.internal (MEProxy); Thu, 18 Mar 2021 08:08:48 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=
        messagingengine.com; h=cc:content-transfer-encoding:date:from
        :in-reply-to:message-id:mime-version:references:subject:to
        :x-me-proxy:x-me-proxy:x-me-sender:x-me-sender:x-sasl-enc; s=
        fm2; bh=96PabhJDlstmRC7dsrIRYNFjrVdwNrnjmP8hw9NXnxQ=; b=gzroBiHF
        qtKZ/V+qgg6VQWfsiGz3OwmJk+/mhZXRjAL+iE/lPyCYea4CEojkDHc6h0V3mBPp
        lMtQ+qtnX+l/d9AVVoLLFp46EHrDmse48kZplwapjKSbswhT/WU87JjnOkPZxu7B
        03giZCHs7LJu47ufOfE7iH75AVAZbSp142j2sSngZbNe/U5Tirxlu2cE1rk/J71e
        z37uHxoB6BBxOYAxWcwz95WC1jQmLo1E78WFNF7aNxZzAj6UsuhL+rV58eEGf/Iz
        CKosx45COMf/yWb+12mh729xSSKIZqexuAd7ZW+MSwaTmRuzUbzBB0CjGA8OBORP
        t5/NeT3ajAx+rQ==
X-ME-Sender: <xms:zUJTYEF62at7RsElDYuQ-v8aZ3bxLWwGrcsIwxpgT4_c73zgYTFCJQ>
    <xme:zUJTYLBab6pO21IkejnAIGNg81ArA23T-LtnxXUJm4QrxlFtlCX1LzAGJ-n_hojkx
    pYiM4G2id3iYMO2nI4>
X-ME-Proxy-Cause: 
 gggruggvucftvghtrhhoucdtuddrgeduledrudefiedgfeekucetufdoteggodetrfdotf
    fvucfrrhhofhhilhgvmecuhfgrshhtofgrihhlpdfqfgfvpdfurfetoffkrfgpnffqhgen
    uceurghilhhouhhtmecufedttdenucesvcftvggtihhpihgvnhhtshculddquddttddmne
    cujfgurhephffvufffkffojghfggfgsedtkeertdertddtnecuhfhrohhmpeffrghvihgu
    ucfgughmohhnughsohhnuceouggrvhhiugdrvggumhhonhgushhonhesohhrrggtlhgvrd
    gtohhmqeenucggtffrrghtthgvrhhnpedufeetjefgfefhtdejhfehtdfftefhteekhefg
    leehfffhiefhgeelgfejtdehkeenucfkphepkedurddukeejrddviedrvdefkeenucevlh
    hushhtvghrufhiiigvpedtnecurfgrrhgrmhepmhgrihhlfhhrohhmpegurghvihgurdgv
    ughmohhnughsohhnsehorhgrtghlvgdrtghomh
X-ME-Proxy: <xmx:zUJTYP6mliqJOinKMipiE7m_5D2MwN8YeCLWIXz0cJVNTq9kJqB9yg>
    <xmx:zUJTYCkHwS3NblqAHrGF-_SmZ_z_tNRTdC-PVpPP9GN3J5eTWzXxKw>
    <xmx:zUJTYA55xs_xBk49O8mtdy6VBV2XsM-ZINool5QjXkMNPs8ZOOo5Xw>
    <xmx:z0JTYDzgkDSCbvUuj4unM-9eBhEl6YfpxG58Gv3omuFCZOjCcdhj9OJ3E1oTRJ8V>
Received: from disaster-area.hh.sledj.net (disaster-area.hh.sledj.net
 [81.187.26.238])
        by mail.messagingengine.com (Postfix) with ESMTPA id 0B23B108005F;
        Thu, 18 Mar 2021 08:08:43 -0400 (EDT)
Received: from localhost (disaster-area.hh.sledj.net [local])
        by disaster-area.hh.sledj.net (OpenSMTPD) with ESMTPA id 08d61faf;
        Thu, 18 Mar 2021 12:08:41 +0000 (UTC)
From: David Edmondson <david.edmondson@oracle.com>
To: linux-kernel@vger.kernel.org
Cc: Ingo Molnar <mingo@redhat.com>, Joerg Roedel <joro@8bytes.org>,
        "H. Peter Anvin" <hpa@zytor.com>,
        Paolo Bonzini <pbonzini@redhat.com>, kvm@vger.kernel.org,
        Wanpeng Li <wanpengli@tencent.com>, x86@kernel.org,
        Borislav Petkov <bp@alien8.de>,
        Thomas Gleixner <tglx@linutronix.de>,
        Sean Christopherson <seanjc@google.com>,
        Jim Mattson <jmattson@google.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        David Edmondson <david.edmondson@oracle.com>
Subject: [PATCH v5 1/5] KVM: x86: dump_vmcs should not assume GUEST_IA32_EFER
 is valid
Date: Thu, 18 Mar 2021 12:08:37 +0000
Message-Id: <20210318120841.133123-2-david.edmondson@oracle.com>
X-Mailer: git-send-email 2.30.2
In-Reply-To: <20210318120841.133123-1-david.edmondson@oracle.com>
References: <20210318120841.133123-1-david.edmondson@oracle.com>
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

If the VM entry/exit controls for loading/saving MSR_EFER are either
not available (an older processor or explicitly disabled) or not
used (host and guest values are the same), reading GUEST_IA32_EFER
from the VMCS returns an inaccurate value.

Because of this, in dump_vmcs() don't use GUEST_IA32_EFER to decide
whether to print the PDPTRs - always do so if the fields exist.

Fixes: 4eb64dce8d0a ("KVM: x86: dump VMCS on invalid entry")
Signed-off-by: David Edmondson <david.edmondson@oracle.com>
---
 arch/x86/kvm/vmx/vmx.c | 9 +++------
 1 file changed, 3 insertions(+), 6 deletions(-)

```
#### [PATCH] KVM: x86/mmu: Rename the special lm_root to pml4_rootFrom: Sean Christopherson <seanjc@google.com>
##### From: Sean Christopherson <seanjc@google.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Sean Christopherson <seanjc@google.com>
X-Patchwork-Id: 12149169
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-26.3 required=3.0 tests=BAYES_00,DKIMWL_WL_MED,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_CR_TRAILER,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,
	USER_AGENT_GIT,USER_IN_DEF_DKIM_WL autolearn=unavailable autolearn_force=no
	version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id E3F4AC433DB
	for <kvm@archiver.kernel.org>; Thu, 18 Mar 2021 20:12:18 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id A102B64EFC
	for <kvm@archiver.kernel.org>; Thu, 18 Mar 2021 20:12:18 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S232974AbhCRULr (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Thu, 18 Mar 2021 16:11:47 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:44814 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S229958AbhCRULf (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 18 Mar 2021 16:11:35 -0400
Received: from mail-qk1-x74a.google.com (mail-qk1-x74a.google.com
 [IPv6:2607:f8b0:4864:20::74a])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 4E285C06174A
        for <kvm@vger.kernel.org>; Thu, 18 Mar 2021 13:11:35 -0700 (PDT)
Received: by mail-qk1-x74a.google.com with SMTP id h21so32481702qkl.12
        for <kvm@vger.kernel.org>; Thu, 18 Mar 2021 13:11:35 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=reply-to:date:message-id:mime-version:subject:from:to:cc;
        bh=UrlGHrWQC65GrWtCnUbevQPCG8mhT0b6JNNJOYVBIxs=;
        b=T8ylBXUHFqADelPsYQknCRt7iu1DV9VleqMiWHdlxNvv6zWntILaYo8dmGiPseOo31
         /L1K2u8ZUe/M1+SP3vegO+tZb+PNXNuZ6PhfhtrpKkFF/TrRTVEyXifiyNCb6m4O/rNq
         vzIoudaysQfuvF4jnqcYgCDHj8mlJmbX/pPK/e2AjMyLokwirdogC07oscMMwyGv3v9q
         Nyzi1juCNzyARaLLl9Fn7Ogl2BwvQqGuIAT/vyqJBil9cQXRBtRgvP6ZPiWU4sntzAmI
         YMiVelHw6sTcpYMKoL7vmumvF7YXriyZkctuKHFq8vHSb075Dz/U/9+k+MLhkq28SYHM
         omxA==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:reply-to:date:message-id:mime-version:subject
         :from:to:cc;
        bh=UrlGHrWQC65GrWtCnUbevQPCG8mhT0b6JNNJOYVBIxs=;
        b=NjeGX3hbInnt0ie5ey8Oa4ZAmSyw2qq38mJN6Vwbq0/SCSHCIn7qvE7FhM1UIdjSgT
         +Br4muBnlzvRmNhnwflF9JdVDDLJ/6xx9meGmLtSqhqbNYG6jqMBF7ItHTEyxhAgjtc9
         x/1khFhWvs1OJ1OozBF5uMyfaLGnAKneJLjdgKzkvC2WG5SpXKyLQr3lrhfQPnv/YxL1
         YO2XGiEgnxzCzQ/qmn79Ih3SFtSf9zcFpLFLP0fnPCjEWaiG0X5bqsh4qHOgT2Fbiveq
         +Q2Y6pQHR91yhr4tByBfPGg/ZKdJM2yzyWeYUaEl/a7XfBkPxLsp+S7PdD1+kjuLsWrS
         63YA==
X-Gm-Message-State: AOAM532lsvEdFsAff5C4r8Qla54yD+h91LVgeCeMEdo2SGk6vG3xQ3b7
        EjCJXvkdkzmhZeOJUY+r6oUfuUR7m+c=
X-Google-Smtp-Source: 
 ABdhPJxnCPZBmyndEzpObEGYQRzkibgrsSxHoCxeFFY16c0rsTVGGvY5epzx5nJcp2tNEBPtv12BZ7kN7Ig=
X-Received: from seanjc798194.pdx.corp.google.com
 ([2620:15c:f:10:25e0:6b8b:f878:23d1])
 (user=seanjc job=sendgmr) by 2002:ad4:44ef:: with SMTP id
 p15mr6169905qvt.25.1616098294483;
 Thu, 18 Mar 2021 13:11:34 -0700 (PDT)
Reply-To: Sean Christopherson <seanjc@google.com>
Date: Thu, 18 Mar 2021 13:11:31 -0700
Message-Id: <20210318201131.3242619-1-seanjc@google.com>
Mime-Version: 1.0
X-Mailer: git-send-email 2.31.0.rc2.261.g7f71774620-goog
Subject: [PATCH] KVM: x86/mmu: Rename the special lm_root to pml4_root
From: Sean Christopherson <seanjc@google.com>
To: Paolo Bonzini <pbonzini@redhat.com>
Cc: Sean Christopherson <seanjc@google.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Rename the lm_root pointer, which is used when shadowing 32-bit L1 NPT
with 64-bit L0 NPT, to pml4_root.  KVM uses dedicated logic to configure
the levels that do not exist in L1's page tables, and to bypass them when
walking the shadow page tables.  That dedicated logic assumes 4-level
paging and will need to be updated if AMD ever gains 5-level paging.

No functional change intended.

Suggested-by: Paolo Bonzini <pbonzini@redhat.com>
Signed-off-by: Sean Christopherson <seanjc@google.com>
---
 arch/x86/include/asm/kvm_host.h |  2 +-
 arch/x86/kvm/mmu/mmu.c          | 20 ++++++++++----------
 2 files changed, 11 insertions(+), 11 deletions(-)

```
#### [PATCH v2 1/4] KVM: x86: Protect userspace MSR filter with SRCU, and set atomically-ish
##### From: Sean Christopherson <seanjc@google.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Sean Christopherson <seanjc@google.com>
X-Patchwork-Id: 12149351
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-26.3 required=3.0 tests=BAYES_00,DKIMWL_WL_MED,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_CR_TRAILER,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,
	USER_AGENT_GIT,USER_IN_DEF_DKIM_WL autolearn=ham autolearn_force=no
	version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id C4A0AC433E0
	for <kvm@archiver.kernel.org>; Thu, 18 Mar 2021 22:44:25 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 97A3E64F30
	for <kvm@archiver.kernel.org>; Thu, 18 Mar 2021 22:44:25 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S232676AbhCRWnx (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Thu, 18 Mar 2021 18:43:53 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:49398 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S231327AbhCRWnQ (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 18 Mar 2021 18:43:16 -0400
Received: from mail-qv1-xf49.google.com (mail-qv1-xf49.google.com
 [IPv6:2607:f8b0:4864:20::f49])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 6D286C061761
        for <kvm@vger.kernel.org>; Thu, 18 Mar 2021 15:43:16 -0700 (PDT)
Received: by mail-qv1-xf49.google.com with SMTP id k92so27319899qva.20
        for <kvm@vger.kernel.org>; Thu, 18 Mar 2021 15:43:16 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=reply-to:date:in-reply-to:message-id:mime-version:references
         :subject:from:to:cc;
        bh=LHYEZM9eJX+3KRVU4MESjmSMC7YXVpqZMPFe9FopAas=;
        b=NuBjfZphhg+t0yUNouMJZqezRqwHvm1NbPplza1EC1QohvNXzwb8Weo6fXxKwDlB4d
         kKJOquCaOv+sp/AMSBtYaq4uk0g8bVI+rgZN7AFl34BcwecUAEDBBHNVNdaFGMP4+2qi
         fCtsSr8ogszr9PKuFp04/AX13x9dbJajYoVZJ7sJEVs81YPKjiZuaUcGZjSi4LNUEm/b
         63r0tB41uAegtWhvA0Z3mlmjPT70Ume6SWVZKGkarEsIAR6RW5CpvH6mQVGJd1k3yhLk
         0hP84WDJTAPDVxaAmvbfSr4QXjNWdiz2NE6Pco4BEtgENhti/EP7bgwBz8z94RjnWXEE
         iRtQ==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:reply-to:date:in-reply-to:message-id
         :mime-version:references:subject:from:to:cc;
        bh=LHYEZM9eJX+3KRVU4MESjmSMC7YXVpqZMPFe9FopAas=;
        b=UVcAafv2VV3qlZ5IpBZYQNS85A/d16ul38G8TEnA6MNTmteTio6Dc7Yitn31BGLiT0
         f9PA0ykjzKKjQ/92gHprT5QSEmm4SYYJXVLHszJbfijaUpmAMb2Nt/eYNogAK8BgcU8o
         bGNP3XD4jis1414q+QPaeFZ91QGs1vv0C49WmMhqhl2pxNUZGPuEJe/FZSJ+HbGQ18Vw
         b5TG/xR4HdU8P8EDvyp0Uy034+y9lZqa/Hz8pWFo6dIL7M4P0s2NPRdnE3lW5CH0xNee
         DCw3cr++XC8ynBMQIWG+rm5WfFqnJEYT9cA4r5ZfvLMYanpaG8FvS82PIR1dZMuoteF9
         6/wA==
X-Gm-Message-State: AOAM532yoQasWw9/1z3plL/wYGiElWS0FxUAytB+U+mcayHB9JhEQDPL
        V6/nqZiRO+GJZ2t5aNYHbYYqt12j4ms=
X-Google-Smtp-Source: 
 ABdhPJzozdNPA/jYPGhKTFdmEoV5slQMriUqp5y8REWuVDg5t6zuWNkiWVruLeFy4F1O0fOf2lFzyqFLHVo=
X-Received: from seanjc798194.pdx.corp.google.com
 ([2620:15c:f:10:25e0:6b8b:f878:23d1])
 (user=seanjc job=sendgmr) by 2002:a0c:b59f:: with SMTP id
 g31mr6567486qve.28.1616107395569;
 Thu, 18 Mar 2021 15:43:15 -0700 (PDT)
Reply-To: Sean Christopherson <seanjc@google.com>
Date: Thu, 18 Mar 2021 15:43:07 -0700
In-Reply-To: <20210318224310.3274160-1-seanjc@google.com>
Message-Id: <20210318224310.3274160-2-seanjc@google.com>
Mime-Version: 1.0
References: <20210318224310.3274160-1-seanjc@google.com>
X-Mailer: git-send-email 2.31.0.rc2.261.g7f71774620-goog
Subject: [PATCH v2 1/4] KVM: x86: Protect userspace MSR filter with SRCU, and
 set atomically-ish
From: Sean Christopherson <seanjc@google.com>
To: Paolo Bonzini <pbonzini@redhat.com>
Cc: Sean Christopherson <seanjc@google.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org, Alexander Graf <graf@amazon.com>,
        Yuan Yao <yaoyuan0329os@gmail.com>
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Fix a plethora of issues with MSR filtering by installing the resulting
filter as an atomic bundle instead of updating the live filter one range
at a time.  The KVM_X86_SET_MSR_FILTER ioctl() isn't truly atomic, as
the hardware MSR bitmaps won't be updated until the next VM-Enter, but
the relevant software struct is atomically updated, which is what KVM
really needs.

Similar to the approach used for modifying memslots, make arch.msr_filter
a SRCU-protected pointer, do all the work configuring the new filter
outside of kvm->lock, and then acquire kvm->lock only when the new filter
has been vetted and created.  That way vCPU readers either see the old
filter or the new filter in their entirety, not some half-baked state.

Yuan Yao pointed out a use-after-free in ksm_msr_allowed() due to a
TOCTOU bug, but that's just the tip of the iceberg...

  - Nothing is __rcu annotated, making it nigh impossible to audit the
    code for correctness.
  - kvm_add_msr_filter() has an unpaired smp_wmb().  Violation of kernel
    coding style aside, the lack of a smb_rmb() anywhere casts all code
    into doubt.
  - kvm_clear_msr_filter() has a double free TOCTOU bug, as it grabs
    count before taking the lock.
  - kvm_clear_msr_filter() also has memory leak due to the same TOCTOU bug.

The entire approach of updating the live filter is also flawed.  While
installing a new filter is inherently racy if vCPUs are running, fixing
the above issues also makes it trivial to ensure certain behavior is
deterministic, e.g. KVM can provide deterministic behavior for MSRs with
identical settings in the old and new filters.  An atomic update of the
filter also prevents KVM from getting into a half-baked state, e.g. if
installing a filter fails, the existing approach would leave the filter
in a half-baked state, having already committed whatever bits of the
filter were already processed.

[*] https://lkml.kernel.org/r/20210312083157.25403-1-yaoyuan0329os@gmail.com

Fixes: 1a155254ff93 ("KVM: x86: Introduce MSR filtering")
Cc: stable@vger.kernel.org
Reviewed-by: Paolo Bonzini <pbonzini@redhat.com>
Reviewed-by: Alexander Graf <graf@amazon.com>
Reported-by: Yuan Yao <yaoyuan0329os@gmail.com>
Signed-off-by: Sean Christopherson <seanjc@google.com>
---
 Documentation/virt/kvm/api.rst  |   6 +-
 arch/x86/include/asm/kvm_host.h |  17 ++---
 arch/x86/kvm/x86.c              | 109 +++++++++++++++++++-------------
 3 files changed, 78 insertions(+), 54 deletions(-)

```
#### [kvm-unit-tests RFC 1/2] scripts: Check kvm availability by asking qemu
##### From: Janosch Frank <frankja@linux.ibm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Janosch Frank <frankja@linux.ibm.com>
X-Patchwork-Id: 12148135
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.8 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT autolearn=ham
	autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id CB753C433E0
	for <kvm@archiver.kernel.org>; Thu, 18 Mar 2021 12:45:59 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 8519D64F6D
	for <kvm@archiver.kernel.org>; Thu, 18 Mar 2021 12:45:59 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S231372AbhCRMp3 (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Thu, 18 Mar 2021 08:45:29 -0400
Received: from mx0b-001b2d01.pphosted.com ([148.163.158.5]:36756 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S231288AbhCRMpS (ORCPT
        <rfc822;kvm@vger.kernel.org>); Thu, 18 Mar 2021 08:45:18 -0400
Received: from pps.filterd (m0098416.ppops.net [127.0.0.1])
        by mx0b-001b2d01.pphosted.com (8.16.0.43/8.16.0.43) with SMTP id
 12ICXgeO181150
        for <kvm@vger.kernel.org>; Thu, 18 Mar 2021 08:45:18 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=ibm.com;
 h=from : to : cc : subject
 : date : message-id : in-reply-to : references : mime-version :
 content-transfer-encoding; s=pp1;
 bh=iokZsD+ZIMIwe/b1kJBsFdMzqpZQBgb9PIpdseOdxx0=;
 b=Ww4i8WCzTmnN+ub4AIIenB18rUJcB27wtPb7TfNpA40lXvZal4AVyqFYeRD1wYTSxbVj
 9Qozs/XxXzunk6jR5KxNUC04V5mhC001vgHM2hzFEUtF74FQGHOXJRM4gJTM7EUJl4LE
 bdWFFPzA/veb2DE9jggpAY8qYrDY8hG16rzHZPdn98GUgxcHJpn438fnhepOwJhyER6r
 Tw9Sk6RAywu6AZ9bIwLAO7C5pRZGJOMKe6YM7LkwoWTkqV/nHO9vzTT/wETnGcV54gYa
 IyQXBYmVVyt7TA9mwn4UpSXRHO5M6OA8YhfBkc2f+8PCYXW5k60pFep0BuLcYF/WSTVW wQ==
Received: from pps.reinject (localhost [127.0.0.1])
        by mx0b-001b2d01.pphosted.com with ESMTP id 37c10fjtvr-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT)
        for <kvm@vger.kernel.org>; Thu, 18 Mar 2021 08:45:17 -0400
Received: from m0098416.ppops.net (m0098416.ppops.net [127.0.0.1])
        by pps.reinject (8.16.0.43/8.16.0.43) with SMTP id 12ICXwXr182858
        for <kvm@vger.kernel.org>; Thu, 18 Mar 2021 08:45:17 -0400
Received: from ppma04ams.nl.ibm.com (63.31.33a9.ip4.static.sl-reverse.com
 [169.51.49.99])
        by mx0b-001b2d01.pphosted.com with ESMTP id 37c10fjtv1-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Thu, 18 Mar 2021 08:45:17 -0400
Received: from pps.filterd (ppma04ams.nl.ibm.com [127.0.0.1])
        by ppma04ams.nl.ibm.com (8.16.0.43/8.16.0.43) with SMTP id
 12ICRliA004910;
        Thu, 18 Mar 2021 12:45:15 GMT
Received: from b06cxnps3074.portsmouth.uk.ibm.com
 (d06relay09.portsmouth.uk.ibm.com [9.149.109.194])
        by ppma04ams.nl.ibm.com with ESMTP id 378n18ms7p-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Thu, 18 Mar 2021 12:45:14 +0000
Received: from d06av24.portsmouth.uk.ibm.com (d06av24.portsmouth.uk.ibm.com
 [9.149.105.60])
        by b06cxnps3074.portsmouth.uk.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id 12ICjCO411338030
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Thu, 18 Mar 2021 12:45:12 GMT
Received: from d06av24.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 8D8F942045;
        Thu, 18 Mar 2021 12:45:12 +0000 (GMT)
Received: from d06av24.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 3A0A242057;
        Thu, 18 Mar 2021 12:45:11 +0000 (GMT)
Received: from localhost.localdomain (unknown [9.145.24.61])
        by d06av24.portsmouth.uk.ibm.com (Postfix) with ESMTP;
        Thu, 18 Mar 2021 12:45:11 +0000 (GMT)
From: Janosch Frank <frankja@linux.ibm.com>
To: kvm@vger.kernel.org
Cc: lvivier@redhat.com, thuth@redhat.com, david@redhat.com,
        drjones@redhat.com, pbonzini@redhat.com, cohuck@redhat.com
Subject: [kvm-unit-tests RFC 1/2] scripts: Check kvm availability by asking
 qemu
Date: Thu, 18 Mar 2021 12:44:59 +0000
Message-Id: <20210318124500.45447-2-frankja@linux.ibm.com>
X-Mailer: git-send-email 2.27.0
In-Reply-To: <20210318124500.45447-1-frankja@linux.ibm.com>
References: <20210318124500.45447-1-frankja@linux.ibm.com>
MIME-Version: 1.0
X-TM-AS-GCONF: 00
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.369,18.0.761
 definitions=2021-03-18_07:2021-03-17,2021-03-18 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 priorityscore=1501 mlxscore=0
 malwarescore=0 bulkscore=0 clxscore=1015 suspectscore=0 mlxlogscore=994
 adultscore=0 phishscore=0 lowpriorityscore=0 impostorscore=0 spamscore=0
 classifier=spam adjust=0 reason=mlx scancount=1 engine=8.12.0-2009150000
 definitions=main-2103180095
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The existence of the /dev/kvm character device doesn't imply that the
kvm module is part of the kernel or that it's always magically loaded
when needed.

Signed-off-by: Janosch Frank <frankja@linux.ibm.com>
---
 arm/run               | 4 ++--
 powerpc/run           | 4 ++--
 s390x/run             | 4 ++--
 scripts/arch-run.bash | 7 +++++--
 x86/run               | 4 ++--
 5 files changed, 13 insertions(+), 10 deletions(-)

```
#### [kvm-unit-tests PATCH 1/3] s390x: Don't run PV testcases under tcg
##### From: Janosch Frank <frankja@linux.ibm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Janosch Frank <frankja@linux.ibm.com>
X-Patchwork-Id: 12148161
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.8 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT
	autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 03536C433E6
	for <kvm@archiver.kernel.org>; Thu, 18 Mar 2021 12:51:24 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id BEC0B64F04
	for <kvm@archiver.kernel.org>; Thu, 18 Mar 2021 12:51:23 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S231268AbhCRMux (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Thu, 18 Mar 2021 08:50:53 -0400
Received: from mx0b-001b2d01.pphosted.com ([148.163.158.5]:27296 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S230171AbhCRMub (ORCPT
        <rfc822;kvm@vger.kernel.org>); Thu, 18 Mar 2021 08:50:31 -0400
Received: from pps.filterd (m0098416.ppops.net [127.0.0.1])
        by mx0b-001b2d01.pphosted.com (8.16.0.43/8.16.0.43) with SMTP id
 12ICXhV1181244;
        Thu, 18 Mar 2021 08:50:31 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=ibm.com;
 h=from : to : cc : subject
 : date : message-id : in-reply-to : references : mime-version :
 content-transfer-encoding; s=pp1;
 bh=c+JX4EYxm/DmDeTHW1yOCsH+/b0JTmv2rfWQ1weXN2I=;
 b=QLrr2ssBN/gxVQLI/DhSlfz9fxyAc8kRCxEn0AaZyYgrSVjW7Lyzsl30WchGHbhFOhdt
 xovvsT+rL2hEKErOfcAshF7dolDCDdLfKZHx4etVWMQ4yven5AqyLau/wOzchmE3l2bU
 9PvPtqp9DyllyJs02UUwQKANZlR31WXN+yEm0vWHxzwCQ0eqnvKVt9s71BRthh9T3Lkc
 WEWincWZ9RZWXP47PkCiMMXyF86w7QaQuGyAT9aVPWNZSCmaDI5h3Y1J/77o7JkYBHbM
 3uS2ZnvoNzT7gmdRq/InRM94ZYBvj6j9Y2/8NQazqVPRZaiCiEW8AJbHaHFepJ9yN+RX eA==
Received: from pps.reinject (localhost [127.0.0.1])
        by mx0b-001b2d01.pphosted.com with ESMTP id 37c10fk097-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Thu, 18 Mar 2021 08:50:30 -0400
Received: from m0098416.ppops.net (m0098416.ppops.net [127.0.0.1])
        by pps.reinject (8.16.0.43/8.16.0.43) with SMTP id 12ICXwXw182858;
        Thu, 18 Mar 2021 08:50:30 -0400
Received: from ppma04fra.de.ibm.com (6a.4a.5195.ip4.static.sl-reverse.com
 [149.81.74.106])
        by mx0b-001b2d01.pphosted.com with ESMTP id 37c10fk08m-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Thu, 18 Mar 2021 08:50:30 -0400
Received: from pps.filterd (ppma04fra.de.ibm.com [127.0.0.1])
        by ppma04fra.de.ibm.com (8.16.0.43/8.16.0.43) with SMTP id
 12ICknpk002596;
        Thu, 18 Mar 2021 12:50:28 GMT
Received: from b06cxnps4076.portsmouth.uk.ibm.com
 (d06relay13.portsmouth.uk.ibm.com [9.149.109.198])
        by ppma04fra.de.ibm.com with ESMTP id 37b6xjgsdm-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Thu, 18 Mar 2021 12:50:28 +0000
Received: from d06av23.portsmouth.uk.ibm.com (d06av23.portsmouth.uk.ibm.com
 [9.149.105.59])
        by b06cxnps4076.portsmouth.uk.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id 12ICoQdA7668042
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Thu, 18 Mar 2021 12:50:26 GMT
Received: from d06av23.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id D5D9AA4055;
        Thu, 18 Mar 2021 12:50:25 +0000 (GMT)
Received: from d06av23.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id D546FA4053;
        Thu, 18 Mar 2021 12:50:24 +0000 (GMT)
Received: from localhost.localdomain (unknown [9.145.24.61])
        by d06av23.portsmouth.uk.ibm.com (Postfix) with ESMTP;
        Thu, 18 Mar 2021 12:50:24 +0000 (GMT)
From: Janosch Frank <frankja@linux.ibm.com>
To: kvm@vger.kernel.org
Cc: thuth@redhat.com, david@redhat.com, cohuck@redhat.com,
        linux-s390@vger.kernel.org
Subject: [kvm-unit-tests PATCH 1/3] s390x: Don't run PV testcases under tcg
Date: Thu, 18 Mar 2021 12:50:13 +0000
Message-Id: <20210318125015.45502-2-frankja@linux.ibm.com>
X-Mailer: git-send-email 2.27.0
In-Reply-To: <20210318125015.45502-1-frankja@linux.ibm.com>
References: <20210318125015.45502-1-frankja@linux.ibm.com>
MIME-Version: 1.0
X-TM-AS-GCONF: 00
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.369,18.0.761
 definitions=2021-03-18_07:2021-03-17,2021-03-18 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 priorityscore=1501 mlxscore=0
 malwarescore=0 bulkscore=0 clxscore=1015 suspectscore=0 mlxlogscore=999
 adultscore=0 phishscore=0 lowpriorityscore=0 impostorscore=0 spamscore=0
 classifier=spam adjust=0 reason=mlx scancount=1 engine=8.12.0-2009150000
 definitions=main-2103180095
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The UV call facility is only available on hardware.

Signed-off-by: Janosch Frank <frankja@linux.ibm.com>
---
 scripts/s390x/func.bash | 3 +++
 1 file changed, 3 insertions(+)

```
#### [PATCH] selftests/kvm: add get_msr_index_features
##### From: Emanuele Giuseppe Esposito <eesposit@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Emanuele Giuseppe Esposito <eesposit@redhat.com>
X-Patchwork-Id: 12148383
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.0 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_CR_TRAILER,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS
	autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 529EDC43381
	for <kvm@archiver.kernel.org>; Thu, 18 Mar 2021 14:57:31 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 2208664F4D
	for <kvm@archiver.kernel.org>; Thu, 18 Mar 2021 14:57:31 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S231571AbhCRO47 (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Thu, 18 Mar 2021 10:56:59 -0400
Received: from us-smtp-delivery-124.mimecast.com ([216.205.24.124]:57168 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S231607AbhCRO4m (ORCPT
        <rfc822;kvm@vger.kernel.org>); Thu, 18 Mar 2021 10:56:42 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1616079402;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=vycDvWIx98YURJumqaeP3+39S6/ZzC3CsHvLvl/koYE=;
        b=PTVx/DkQPBQCfGc47DRU1qDwkb45itmvqkm1zTV8KMTxVXVpNKSRqTdp0y6+GXdsGEIN54
        P/0DmKjmpJ7XwBumln5Jcyfqbj7AjRbArblOrkzrZ5oK93MdUGjIvgK5l3hDtMyMPdzR4h
        74VMge8pssweLAVdYXJRAgiLOBmmnHU=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-253-TfMLu21ZMzG2H15U9OY67A-1; Thu, 18 Mar 2021 10:56:37 -0400
X-MC-Unique: TfMLu21ZMzG2H15U9OY67A-1
Received: from smtp.corp.redhat.com (int-mx07.intmail.prod.int.phx2.redhat.com
 [10.5.11.22])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 7851D100E426;
        Thu, 18 Mar 2021 14:56:36 +0000 (UTC)
Received: from localhost.localdomain.com (ovpn-113-156.ams2.redhat.com
 [10.36.113.156])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 8226E1001B2C;
        Thu, 18 Mar 2021 14:56:34 +0000 (UTC)
From: Emanuele Giuseppe Esposito <eesposit@redhat.com>
To: linux-kselftest@vger.kernel.org
Cc: Paolo Bonzini <pbonzini@redhat.com>, Shuah Khan <shuah@kernel.org>,
        Vitaly Kuznetsov <vkuznets@redhat.com>, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org
Subject: [PATCH] selftests/kvm: add get_msr_index_features
Date: Thu, 18 Mar 2021 15:56:29 +0100
Message-Id: <20210318145629.486450-1-eesposit@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.84 on 10.5.11.22
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Test the KVM_GET_MSR_FEATURE_INDEX_LIST
and KVM_GET_MSR_INDEX_LIST ioctls.

Signed-off-by: Emanuele Giuseppe Esposito <eesposit@redhat.com>
---
 tools/testing/selftests/kvm/.gitignore        |   1 +
 tools/testing/selftests/kvm/Makefile          |   1 +
 .../kvm/x86_64/get_msr_index_features.c       | 124 ++++++++++++++++++
 3 files changed, 126 insertions(+)
 create mode 100644 tools/testing/selftests/kvm/x86_64/get_msr_index_features.c

```
#### [kvm-unit-tests PATCH v1 1/6] s390x: lib: css: disabling a subchannel
##### From: Pierre Morel <pmorel@linux.ibm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Pierre Morel <pmorel@linux.ibm.com>
X-Patchwork-Id: 12148243
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.8 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT autolearn=ham
	autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 2686BC433E6
	for <kvm@archiver.kernel.org>; Thu, 18 Mar 2021 13:27:10 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id EC2CE64F11
	for <kvm@archiver.kernel.org>; Thu, 18 Mar 2021 13:27:09 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S230476AbhCRN0i (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Thu, 18 Mar 2021 09:26:38 -0400
Received: from mx0b-001b2d01.pphosted.com ([148.163.158.5]:39890 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S230285AbhCRN0g (ORCPT
        <rfc822;kvm@vger.kernel.org>); Thu, 18 Mar 2021 09:26:36 -0400
Received: from pps.filterd (m0098414.ppops.net [127.0.0.1])
        by mx0b-001b2d01.pphosted.com (8.16.0.43/8.16.0.43) with SMTP id
 12ID39Fw158235
        for <kvm@vger.kernel.org>; Thu, 18 Mar 2021 09:26:35 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=ibm.com;
 h=from : to : cc : subject
 : date : message-id : in-reply-to : references; s=pp1;
 bh=M8xLTkL9j6ngiKlwIMFE9zEapnX+WxzRfGWNXgxUC3g=;
 b=l/l4IfQnh9Ru8jQOo9gfYKk1dRJ5aMtZQsxoX4IeKRfQ7z0F98BoyP0wZmO08ewDmqhC
 LPSTfMCnGlPDrgtq+ZvXBo1Vq6QDG3uVn+6NIuauYNSw8uKDqzyLe442nuBcuYdAn4Oo
 p0EIakA1tO6xT9NSinRJzjJ6sOmhceISp+MGnepT/xfmaNu+cLU+v0TZvRV01Yax2L6T
 ySeJcsrRz6KuCBLLy3FAdZy3SUk0dDSWjBTtaIereVzTIqwTd0eU5gKmFtkoad3Fj9nb
 FN2FHSwbTqWuPO2xVMdscqqvH1FdPYgIlL7d6oWcgGGeW48pe1So2CbqXMZ/imAQa1dG fw==
Received: from pps.reinject (localhost [127.0.0.1])
        by mx0b-001b2d01.pphosted.com with ESMTP id 37byr3dkhy-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT)
        for <kvm@vger.kernel.org>; Thu, 18 Mar 2021 09:26:35 -0400
Received: from m0098414.ppops.net (m0098414.ppops.net [127.0.0.1])
        by pps.reinject (8.16.0.43/8.16.0.43) with SMTP id 12ID5RkZ167523
        for <kvm@vger.kernel.org>; Thu, 18 Mar 2021 09:26:35 -0400
Received: from ppma06fra.de.ibm.com (48.49.7a9f.ip4.static.sl-reverse.com
 [159.122.73.72])
        by mx0b-001b2d01.pphosted.com with ESMTP id 37byr3dkhe-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Thu, 18 Mar 2021 09:26:35 -0400
Received: from pps.filterd (ppma06fra.de.ibm.com [127.0.0.1])
        by ppma06fra.de.ibm.com (8.16.0.43/8.16.0.43) with SMTP id
 12IDNWeD030235;
        Thu, 18 Mar 2021 13:26:33 GMT
Received: from b06avi18626390.portsmouth.uk.ibm.com
 (b06avi18626390.portsmouth.uk.ibm.com [9.149.26.192])
        by ppma06fra.de.ibm.com with ESMTP id 378mnhahsa-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Thu, 18 Mar 2021 13:26:33 +0000
Received: from d06av22.portsmouth.uk.ibm.com (d06av22.portsmouth.uk.ibm.com
 [9.149.105.58])
        by b06avi18626390.portsmouth.uk.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id 12IDQDS021496122
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Thu, 18 Mar 2021 13:26:13 GMT
Received: from d06av22.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 43C2E4C05C;
        Thu, 18 Mar 2021 13:26:30 +0000 (GMT)
Received: from d06av22.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id F387F4C052;
        Thu, 18 Mar 2021 13:26:29 +0000 (GMT)
Received: from oc3016276355.ibm.com (unknown [9.145.64.4])
        by d06av22.portsmouth.uk.ibm.com (Postfix) with ESMTP;
        Thu, 18 Mar 2021 13:26:29 +0000 (GMT)
From: Pierre Morel <pmorel@linux.ibm.com>
To: kvm@vger.kernel.org
Cc: frankja@linux.ibm.com, david@redhat.com, thuth@redhat.com,
        cohuck@redhat.com, imbrenda@linux.ibm.com
Subject: [kvm-unit-tests PATCH v1 1/6] s390x: lib: css: disabling a subchannel
Date: Thu, 18 Mar 2021 14:26:23 +0100
Message-Id: <1616073988-10381-2-git-send-email-pmorel@linux.ibm.com>
X-Mailer: git-send-email 1.8.3.1
In-Reply-To: <1616073988-10381-1-git-send-email-pmorel@linux.ibm.com>
References: <1616073988-10381-1-git-send-email-pmorel@linux.ibm.com>
X-TM-AS-GCONF: 00
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.369,18.0.761
 definitions=2021-03-18_07:2021-03-17,2021-03-18 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 clxscore=1015 suspectscore=0
 priorityscore=1501 impostorscore=0 mlxscore=0 phishscore=0 mlxlogscore=999
 malwarescore=0 bulkscore=0 adultscore=0 spamscore=0 lowpriorityscore=0
 classifier=spam adjust=0 reason=mlx scancount=1 engine=8.12.0-2009150000
 definitions=main-2103180097
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Some tests require to disable a subchannel.
Let's implement the css_disable() function.

Signed-off-by: Pierre Morel <pmorel@linux.ibm.com>
---
 lib/s390x/css.h     |  1 +
 lib/s390x/css_lib.c | 69 +++++++++++++++++++++++++++++++++++++++++++++
 2 files changed, 70 insertions(+)

```
#### [PATCH v2 1/2] kvm/kvm_util: add _vm_ioctl
##### From: Emanuele Giuseppe Esposito <eesposit@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Emanuele Giuseppe Esposito <eesposit@redhat.com>
X-Patchwork-Id: 12148421
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.0 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_CR_TRAILER,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS
	autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 8941AC433E6
	for <kvm@archiver.kernel.org>; Thu, 18 Mar 2021 15:17:27 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 6590A64F40
	for <kvm@archiver.kernel.org>; Thu, 18 Mar 2021 15:17:27 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S231596AbhCRPQ4 (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Thu, 18 Mar 2021 11:16:56 -0400
Received: from us-smtp-delivery-124.mimecast.com ([216.205.24.124]:27789 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S231693AbhCRPQg (ORCPT
        <rfc822;kvm@vger.kernel.org>); Thu, 18 Mar 2021 11:16:36 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1616080595;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=vE1dYwm/OYVGmvG6Nwn7AfjNErBRScb3qhVkqFMoRok=;
        b=Wx1WGfewscAVa3dh/+HidK85wjXdeyw1Z1vgcBbIvqhAD7y/Y7ZL2v348hgK4b6/qNN4qp
        OZDAziRXKYIUvG0pg/rbgYidTucu6vs0jMcRJxTyFieyP+DzXH2wRPg2WB8Glzggy+V4GY
        pl2WIljjeX3c80gm+idsvC4Ng/00bOc=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-123-Bf9FYAKJNnq8jDgJ8HOAnQ-1; Thu, 18 Mar 2021 11:16:33 -0400
X-MC-Unique: Bf9FYAKJNnq8jDgJ8HOAnQ-1
Received: from smtp.corp.redhat.com (int-mx07.intmail.prod.int.phx2.redhat.com
 [10.5.11.22])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 821E0593A3;
        Thu, 18 Mar 2021 15:16:32 +0000 (UTC)
Received: from localhost.localdomain.com (ovpn-113-156.ams2.redhat.com
 [10.36.113.156])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 996731001B2C;
        Thu, 18 Mar 2021 15:16:25 +0000 (UTC)
From: Emanuele Giuseppe Esposito <eesposit@redhat.com>
To: linux-kselftest@vger.kernel.org
Cc: Paolo Bonzini <pbonzini@redhat.com>, Shuah Khan <shuah@kernel.org>,
        Andrew Jones <drjones@redhat.com>,
        Peter Xu <peterx@redhat.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Subject: [PATCH v2 1/2] kvm/kvm_util: add _vm_ioctl
Date: Thu, 18 Mar 2021 16:16:23 +0100
Message-Id: <20210318151624.490861-1-eesposit@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.84 on 10.5.11.22
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

As in kvm_ioctl and _kvm_ioctl, add
the respective _vm_ioctl for vm_ioctl.

_vm_ioctl invokes an ioctl using the vm fd,
leaving the caller to test the result.

Signed-off-by: Emanuele Giuseppe Esposito <eesposit@redhat.com>
Reviewed-by: Andrew Jones <drjones@redhat.com>
---
 tools/testing/selftests/kvm/include/kvm_util.h | 1 +
 tools/testing/selftests/kvm/lib/kvm_util.c     | 7 ++++++-
 2 files changed, 7 insertions(+), 1 deletion(-)

```
#### [PATCH] X86: __set_clr_pte_enc() miscalculates physical address
##### From: Isaku Yamahata <isaku.yamahata@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Isaku Yamahata <isaku.yamahata@intel.com>
X-Patchwork-Id: 12149225
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.8 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED,USER_AGENT_GIT
	autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 480BAC433E6
	for <kvm@archiver.kernel.org>; Thu, 18 Mar 2021 20:30:11 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 11DB164F2A
	for <kvm@archiver.kernel.org>; Thu, 18 Mar 2021 20:30:11 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S231210AbhCRU3g (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Thu, 18 Mar 2021 16:29:36 -0400
Received: from mga04.intel.com ([192.55.52.120]:4540 "EHLO mga04.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S230495AbhCRU3S (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 18 Mar 2021 16:29:18 -0400
IronPort-SDR: 
 M4v4oLC0Q2PZdrAAgXc1VKnEnNFD43o/WM0Ji65ly/baar/XmGj82SOmFK5RIk2zdM4ngogvDL
 xqrHRmj78Y4w==
X-IronPort-AV: E=McAfee;i="6000,8403,9927"; a="187405824"
X-IronPort-AV: E=Sophos;i="5.81,259,1610438400";
   d="scan'208";a="187405824"
Received: from fmsmga006.fm.intel.com ([10.253.24.20])
  by fmsmga104.fm.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 18 Mar 2021 13:29:17 -0700
IronPort-SDR: 
 /duqs8LGb1pcam6TOOuo19fqDJYUwNc3hTdWoFo9woYvJCgHvkQNd2dWAyB9/xu0nlbiViaHpk
 Q4MW+VaaU5iA==
X-IronPort-AV: E=Sophos;i="5.81,259,1610438400";
   d="scan'208";a="602864941"
Received: from ls.sc.intel.com (HELO localhost) ([143.183.96.54])
  by fmsmga006-auth.fm.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 18 Mar 2021 13:29:17 -0700
From: Isaku Yamahata <isaku.yamahata@intel.com>
To: linux-kernel@vger.kernel.org, stable@vger.kernel.org,
        x86@kernel.org, kvm@vger.kernel.org
Cc: brijesh.singh@amd.com, tglx@linutronix.de, bp@alien8.de,
        isaku.yamahata@gmail.com, thomas.lendacky@amd.com,
        Isaku Yamahata <isaku.yamahata@intel.com>,
        "Kirill A . Shutemov" <kirill.shutemov@linux.intel.com>
Subject: [PATCH] X86: __set_clr_pte_enc() miscalculates physical address
Date: Thu, 18 Mar 2021 13:26:57 -0700
Message-Id: 
 <81abbae1657053eccc535c16151f63cd049dcb97.1616098294.git.isaku.yamahata@intel.com>
X-Mailer: git-send-email 2.25.1
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

__set_clr_pte_enc() miscalculates physical address to operate.
pfn is in unit of PG_LEVEL_4K, not PGL_LEVEL_{2M, 1G}.
Shift size to get physical address should be PAGE_SHIFT,
not page_level_shift().

Fixes: dfaaec9033b8 ("x86: Add support for changing memory encryption attribute in early boot")
Reviewed-by: Kirill A. Shutemov <kirill.shutemov@linux.intel.com>
Signed-off-by: Isaku Yamahata <isaku.yamahata@intel.com>
---
 arch/x86/mm/mem_encrypt.c | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
