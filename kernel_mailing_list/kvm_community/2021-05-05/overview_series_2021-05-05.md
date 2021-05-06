#### [GIT PULL] virtio,vhost,vdpa: features, fixes
##### From: "Michael S. Tsirkin" <mst@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: "Michael S. Tsirkin" <mst@redhat.com>
X-Patchwork-Id: 12240949
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-26.4 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_CR_TRAILER,INCLUDES_PATCH,INCLUDES_PULL_REQUEST,MAILING_LIST_MULTI,
	MENTIONS_GIT_HOSTING,SPF_HELO_NONE,SPF_PASS autolearn=ham autolearn_force=no
	version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 0B17CC433B4
	for <kvm@archiver.kernel.org>; Wed,  5 May 2021 20:11:44 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id CE99C61006
	for <kvm@archiver.kernel.org>; Wed,  5 May 2021 20:11:43 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S233891AbhEEUMj (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Wed, 5 May 2021 16:12:39 -0400
Received: from us-smtp-delivery-124.mimecast.com ([216.205.24.124]:21891 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S233852AbhEEUMi (ORCPT
        <rfc822;kvm@vger.kernel.org>); Wed, 5 May 2021 16:12:38 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1620245501;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:content-type:content-type;
        bh=trH/NfkKL9hdKsJ9LaR25jQCqSBLEA1C4zT+z7TQZuM=;
        b=c4vI6jhfDfjM342yyr+Z0P0gJxEilvydX/61teLkdkeZ8kyFJXTtp/NRkJD7dewnm+YZtf
        XNXdQ1kocmkGwMKnWh1Fzl42RCrCfts0RwmDNzZhC0dyKGnd5P3WG1uvrCDcWGNrEX2nD0
        uBXpUe3sZSwOtzQOmFMnniatLRAHXaQ=
Received: from mail-wm1-f71.google.com (mail-wm1-f71.google.com
 [209.85.128.71]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-447-IU2rogHhP9Sp7VUdGu7Mfw-1; Wed, 05 May 2021 16:11:39 -0400
X-MC-Unique: IU2rogHhP9Sp7VUdGu7Mfw-1
Received: by mail-wm1-f71.google.com with SMTP id
 h128-20020a1cb7860000b0290148da43c895so715623wmf.4
        for <kvm@vger.kernel.org>; Wed, 05 May 2021 13:11:39 -0700 (PDT)
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:date:from:to:cc:subject:message-id:mime-version
         :content-disposition;
        bh=trH/NfkKL9hdKsJ9LaR25jQCqSBLEA1C4zT+z7TQZuM=;
        b=BJhnoIXwAsLWe0PP/0ikf6P53Rf7loHq0mGZg8vIqtIA/RM6j1ytbtaaD7aF/r+e2Y
         jl2Cv9B1+0Sf0GhrP8snm9VjDgTvAmFoDujEjNsBLfhTFBUnF59ibhAqwfU01c8tGJY4
         1nBYDMgAwVt8BzfksV6UJze55W7l0Wtmr4nrDkSpW1jpzqlIQseBfawN/trUO0FpVE9I
         GksDmozGA56RsBO3hsaWvUuLBG33tUGD3kLEiquX5IPFHV72j7bP0cTq9bHGJ00qXn1W
         LK/m+L4dcX6N5xUutOQ4CdjKhCoUWreA61rbugOUmyxdwAklQKBTVFMtjhGNH4ugBvEg
         IZ+A==
X-Gm-Message-State: AOAM531EG9skW8cOBE2gmIfBTtH6GcPOhdFwuGErYboaKYJdZZbccPl8
        J7Z7f845TCWGXV2kHncxjlcT4f1mHyJx/yjdex2Kz8X9Im3OztoBDOoMytXjbPtYgvlJkRcI09P
        fTqJth5sDO/pa
X-Received: by 2002:a05:600c:190c:: with SMTP id
 j12mr11647203wmq.41.1620245498492;
        Wed, 05 May 2021 13:11:38 -0700 (PDT)
X-Google-Smtp-Source: 
 ABdhPJztjSMo+WrOGeWsi0rPU8vWa/2MQe6CfpFZS59vZKcAjfy+3i8GW0D8k1kGMxQrBXfQFIf4Ug==
X-Received: by 2002:a05:600c:190c:: with SMTP id
 j12mr11647184wmq.41.1620245498339;
        Wed, 05 May 2021 13:11:38 -0700 (PDT)
Received: from redhat.com ([2a10:800c:8fce:0:8e1b:40f0:6a74:513b])
        by smtp.gmail.com with ESMTPSA id m6sm533139wrp.29.2021.05.05.13.11.36
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Wed, 05 May 2021 13:11:38 -0700 (PDT)
Date: Wed, 5 May 2021 16:11:35 -0400
From: "Michael S. Tsirkin" <mst@redhat.com>
To: Linus Torvalds <torvalds@linux-foundation.org>
Cc: kvm@vger.kernel.org, virtualization@lists.linux-foundation.org,
        netdev@vger.kernel.org, linux-kernel@vger.kernel.org,
        elic@nvidia.com, jasowang@redhat.com, lingshan.zhu@intel.com,
        liu.xiang@zlingsmart.com, lkp@intel.com, mgurtovoy@nvidia.com,
        mst@redhat.com, parav@nvidia.com, sgarzare@redhat.com,
        stable@vger.kernel.org, xieyongji@bytedance.com
Subject: [GIT PULL] virtio,vhost,vdpa: features, fixes
Message-ID: <20210505161135-mutt-send-email-mst@kernel.org>
MIME-Version: 1.0
Content-Disposition: inline
X-Mutt-Fcc: =sent
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The following changes since commit 9f4ad9e425a1d3b6a34617b8ea226d56a119a717:

  Linux 5.12 (2021-04-25 13:49:08 -0700)

are available in the Git repository at:

  https://git.kernel.org/pub/scm/linux/kernel/git/mst/vhost.git tags/for_linus

for you to fetch changes up to d7bce85aa7b92b5de8f69b3bcedfe51d7b1aabe1:

  virtio_pci_modern: correct sparse tags for notify (2021-05-04 04:19:59 -0400)

----------------------------------------------------------------
virtio,vhost,vdpa: features, fixes

A bunch of new drivers including vdpa support for block
and virtio-vdpa. Beginning of vq kick (aka doorbell) mapping support.
Misc fixes.

Signed-off-by: Michael S. Tsirkin <mst@redhat.com>

----------------------------------------------------------------
Eli Cohen (1):
      vdpa/mlx5: Enable user to add/delete vdpa device

Jason Wang (9):
      vdpa: introduce virtio pci driver
      virtio_pci_modern: introduce helper to map vq notify area
      virtio-pci library: switch to use vp_modern_map_vq_notify()
      vp_vdpa: switch to use vp_modern_map_vq_notify()
      virtio_pci_modern: hide vp_modern_get_queue_notify_off()
      virito_pci libray: hide vp_modern_map_capability()
      virtio-pci library: report resource address
      vp_vdpa: report doorbell address
      vhost-vdpa: fix vm_flags for virtqueue doorbell mapping

Liu Xiang (1):
      virtio-balloon: fix a typo in comment of virtballoon_migratepage()

Max Gurtovoy (2):
      virtio-net: don't allocate control_buf if not supported
      vdpa: add vdpa simulator for block device

Michael S. Tsirkin (2):
      virtio_pci_modern: __force cast the notify mapping
      virtio_pci_modern: correct sparse tags for notify

Parav Pandit (2):
      vdpa: Follow kdoc comment style
      vdpa: Follow kdoc comment style

Stefano Garzarella (12):
      vdpa_sim: use iova module to allocate IOVA addresses
      vringh: add 'iotlb_lock' to synchronize iotlb accesses
      vringh: reset kiov 'consumed' field in __vringh_iov()
      vringh: explain more about cleaning riov and wiov
      vringh: implement vringh_kiov_advance()
      vringh: add vringh_kiov_length() helper
      vdpa_sim: cleanup kiovs in vdpasim_free()
      vdpa: add get_config_size callback in vdpa_config_ops
      vhost/vdpa: use get_config_size callback in vhost_vdpa_config_validate()
      vdpa_sim_blk: implement ramdisk behaviour
      vdpa_sim_blk: handle VIRTIO_BLK_T_GET_ID
      vdpa_sim_blk: add support for vdpa management tool

Xie Yongji (1):
      vhost/vdpa: Remove the restriction that only supports virtio-net devices

Zhu Lingshan (10):
      vDPA/ifcvf: get_vendor_id returns a device specific vendor id
      vDPA/ifcvf: enable Intel C5000X-PL virtio-net for vDPA
      vDPA/ifcvf: rename original IFCVF dev ids to N3000 ids
      vDPA/ifcvf: remove the version number string
      vDPA/ifcvf: fetch device feature bits when probe
      vDPA/ifcvf: verify mandatory feature bits for vDPA
      vDPA/ifcvf: deduce VIRTIO device ID from pdev ids
      vDPA/ifcvf: deduce VIRTIO device ID when probe
      vDPA/ifcvf: enable Intel C5000X-PL virtio-block for vDPA
      vDPA/ifcvf: get_config_size should return dev specific config size

 drivers/Makefile                       |   1 +
 drivers/net/virtio_net.c               |  10 +-
 drivers/vdpa/Kconfig                   |  15 +
 drivers/vdpa/Makefile                  |   1 +
 drivers/vdpa/ifcvf/ifcvf_base.c        |  24 +-
 drivers/vdpa/ifcvf/ifcvf_base.h        |  26 +-
 drivers/vdpa/ifcvf/ifcvf_main.c        |  86 +++++-
 drivers/vdpa/mlx5/net/mlx5_vnet.c      |  85 +++++-
 drivers/vdpa/vdpa.c                    |  12 +-
 drivers/vdpa/vdpa_sim/Makefile         |   1 +
 drivers/vdpa/vdpa_sim/vdpa_sim.c       | 127 ++++++---
 drivers/vdpa/vdpa_sim/vdpa_sim.h       |   2 +
 drivers/vdpa/vdpa_sim/vdpa_sim_blk.c   | 338 +++++++++++++++++++++++
 drivers/vdpa/virtio_pci/Makefile       |   2 +
 drivers/vdpa/virtio_pci/vp_vdpa.c      | 484 +++++++++++++++++++++++++++++++++
 drivers/vhost/vdpa.c                   |  16 +-
 drivers/vhost/vringh.c                 |  69 +++--
 drivers/virtio/virtio_balloon.c        |   2 +-
 drivers/virtio/virtio_pci_modern.c     |  27 +-
 drivers/virtio/virtio_pci_modern_dev.c |  67 ++++-
 include/linux/vdpa.h                   |  42 +--
 include/linux/virtio_pci_modern.h      |  11 +-
 include/linux/vringh.h                 |  19 +-
 23 files changed, 1295 insertions(+), 172 deletions(-)
 create mode 100644 drivers/vdpa/vdpa_sim/vdpa_sim_blk.c
 create mode 100644 drivers/vdpa/virtio_pci/Makefile
 create mode 100644 drivers/vdpa/virtio_pci/vp_vdpa.c
```
#### [PATCH v4 1/8] context_tracking: Move guest exit context tracking to separate helpers
##### From: Sean Christopherson <seanjc@google.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Sean Christopherson <seanjc@google.com>
X-Patchwork-Id: 12238691
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-26.3 required=3.0 tests=BAYES_00,DKIMWL_WL_MED,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_CR_TRAILER,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,
	URIBL_BLOCKED,USER_AGENT_GIT,USER_IN_DEF_DKIM_WL autolearn=ham
	autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 482C4C433ED
	for <kvm@archiver.kernel.org>; Wed,  5 May 2021 00:27:51 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 2515E613CB
	for <kvm@archiver.kernel.org>; Wed,  5 May 2021 00:27:51 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S231411AbhEEA2p (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 4 May 2021 20:28:45 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:50344 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S231134AbhEEA2n (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 4 May 2021 20:28:43 -0400
Received: from mail-qk1-x74a.google.com (mail-qk1-x74a.google.com
 [IPv6:2607:f8b0:4864:20::74a])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 4A2B6C061574
        for <kvm@vger.kernel.org>; Tue,  4 May 2021 17:27:48 -0700 (PDT)
Received: by mail-qk1-x74a.google.com with SMTP id
 m1-20020a05620a2201b02902e5493ba894so8733352qkh.17
        for <kvm@vger.kernel.org>; Tue, 04 May 2021 17:27:48 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=reply-to:date:in-reply-to:message-id:mime-version:references
         :subject:from:to:cc;
        bh=xZt4efxZ5O1fki+F06zzqnkjNwRMCCexS8Z/OWGzDKY=;
        b=RCPr67vEGY5CUjwXRYFJ17bNaPnTkB+YC/NFD/g6gSMqXJo1KpoKNbc8ioAry3aOo5
         wT+5bW4ukEcbzXmpBO6Nofhx0N2lf4tDuOdo5Q85UU/5Ac2aMBtx3lRG7ypI2J1Vg4sM
         bewxeC0g6/dJ3Puc+L9MGhCugukS6LvFPriOzSQOo4HuTnHPx6Gz5JmtM4BJxAEg75XU
         qmFX77Jq9Qtzaa3+3CniWDGR9P6Yo6lYxGZKAf9loV1nK5k10yCPOKBEUJDqeGL6L5dQ
         yWGkfNtzVRUdOoo1J91pz9qPhUVuTJ96FALUsSej1OTblQKUzoCHSuHJF1p4RBDmSbB2
         18FA==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:reply-to:date:in-reply-to:message-id
         :mime-version:references:subject:from:to:cc;
        bh=xZt4efxZ5O1fki+F06zzqnkjNwRMCCexS8Z/OWGzDKY=;
        b=PBVIYWsnCBdz3SLZK8e9xE6gafOxflyjXzO1I3vGNv2jTWBnyur/9IQ8Tgf7pGJkTc
         OfAQMtZv9pgiFZaCI3HxRpibPs7ybm8Yknj5rRImcrt3lLPFVS/prP4nQidHANAICDJ5
         sfsMe4k0aB+uSYsGGoc5TV52w06s7OqFr13L0aJaTGqLVBSpQ3tfRLucK2jehEnbj1k2
         nO0Ko3kO9Eh0fWufS8uslFXOeVHlmFJG+dZ7hkb2VuOqKPWZQA5XEhBaOFt80WjlqlxE
         G5fEK/hzRm9ueGOJtpId0zbkHTYDtgXWJ7nCsWxAcUC0UXd8X9AsRjIuJ3J4Y6VKZosH
         tGEA==
X-Gm-Message-State: AOAM5308qmZJKKsxenoffepoZ8JJRnzOCTceUm2mS/sYfQOln8KuMjMN
        Tkl1AglVrlEBl2E3wYbtytxyK8MaPpg=
X-Google-Smtp-Source: 
 ABdhPJy1pcjP5q/y8aPXnwQ3sVhGewgpWMslaYXIyaqZg7im31538j5Ml+LRQ3OlWvuxy8r5Vd7WnmuVGHo=
X-Received: from seanjc798194.pdx.corp.google.com
 ([2620:15c:f:10:df57:48cb:ea33:a156])
 (user=seanjc job=sendgmr) by 2002:a05:6214:176f:: with SMTP id
 et15mr28001756qvb.61.1620174467444; Tue, 04 May 2021 17:27:47 -0700 (PDT)
Reply-To: Sean Christopherson <seanjc@google.com>
Date: Tue,  4 May 2021 17:27:28 -0700
In-Reply-To: <20210505002735.1684165-1-seanjc@google.com>
Message-Id: <20210505002735.1684165-2-seanjc@google.com>
Mime-Version: 1.0
References: <20210505002735.1684165-1-seanjc@google.com>
X-Mailer: git-send-email 2.31.1.527.g47e6f16901-goog
Subject: [PATCH v4 1/8] context_tracking: Move guest exit context tracking to
 separate helpers
From: Sean Christopherson <seanjc@google.com>
To: Paolo Bonzini <pbonzini@redhat.com>
Cc: Sean Christopherson <seanjc@google.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org, Thomas Gleixner <tglx@linutronix.de>,
        Michael Tokarev <mjt@tls.msk.ru>,
        Christian Borntraeger <borntraeger@de.ibm.com>,
        Frederic Weisbecker <frederic@kernel.org>
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Wanpeng Li <wanpengli@tencent.com>

Provide separate context tracking helpers for guest exit, the standalone
helpers will be called separately by KVM x86 in later patches to fix
tick-based accounting.

Suggested-by: Thomas Gleixner <tglx@linutronix.de>
Cc: Thomas Gleixner <tglx@linutronix.de>
Cc: Michael Tokarev <mjt@tls.msk.ru>
Cc: Christian Borntraeger <borntraeger@de.ibm.com>
Cc: Frederic Weisbecker <frederic@kernel.org>
Signed-off-by: Wanpeng Li <wanpengli@tencent.com>
Co-developed-by: Sean Christopherson <seanjc@google.com>
Signed-off-by: Sean Christopherson <seanjc@google.com>
---
 include/linux/context_tracking.h | 9 ++++++++-
 1 file changed, 8 insertions(+), 1 deletion(-)

```
#### [PATCH] KVM: PPC: Book3S HV: Fix conversion to gfn-based MMU notifier callbacks
##### From: Nicholas Piggin <npiggin@gmail.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Nicholas Piggin <npiggin@gmail.com>
X-Patchwork-Id: 12239845
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-15.8 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,DKIM_VALID_AU,FREEMAIL_FORGED_FROMDOMAIN,FREEMAIL_FROM,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT
	autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 5E9D7C43461
	for <kvm@archiver.kernel.org>; Wed,  5 May 2021 12:17:37 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 30AB06139A
	for <kvm@archiver.kernel.org>; Wed,  5 May 2021 12:17:37 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S233395AbhEEMSc (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Wed, 5 May 2021 08:18:32 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:35504 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S233518AbhEEMRx (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 5 May 2021 08:17:53 -0400
Received: from mail-pj1-x1035.google.com (mail-pj1-x1035.google.com
 [IPv6:2607:f8b0:4864:20::1035])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id C1E31C06138F;
        Wed,  5 May 2021 05:15:26 -0700 (PDT)
Received: by mail-pj1-x1035.google.com with SMTP id p17so697332pjz.3;
        Wed, 05 May 2021 05:15:26 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=from:to:cc:subject:date:message-id:mime-version
         :content-transfer-encoding;
        bh=oyHwnIbZLLevfNDzdT6CM1DYrT1P/eF7j4L5Cf+qIR4=;
        b=SXSIIPseqld8EsKpB9fNO9vdeGXr/v8noETf6vr642IHwFrh+spYCo9atcasz023yS
         qVySb6P9Rie9BqVrrHATGQ9EatZvDd6J12fGDf944ukVwjuZXIWPZIvwkD0LC7kAM+03
         aTZBk6o02Zaxp5+pSZ471MByxYyjc3/h4fj6C1dO10L0Jk6e2zsID1tuuoIBvIgJrkk9
         9Tqok7EnUvdb0Kg4cj8GnzYuGcZ6il4/WoqmPmIADolprN+RSdPhML+S9G3SknGuVeZm
         crO5+UMTC5IW7UvqqR1KRd5ZaRUaIiIpBBzx0WaMxG7Ij91x1/Nw+8OcCNTLNhKrRHnB
         qD+Q==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:mime-version
         :content-transfer-encoding;
        bh=oyHwnIbZLLevfNDzdT6CM1DYrT1P/eF7j4L5Cf+qIR4=;
        b=j0XYQp1xlXSpUoRY3e/HuIf5AmkPOa28QHjjgvtejm/D2xEF7oTUTU9dZ82vvBmxW0
         kF7CiNcFL4+3GjerTRvVgKLgeiyFHEsPaKGs0sgNn3P/RGOIave7SkaFOFV/8c+p21k5
         UX7ObuvgklNrDrwvl1gwDo9Yn6hyZQ9dC7qe0GBNFQfg8jZ9xI1jRG5R1ZXIu4WDbkvQ
         L42LoUIgv0z8xLiZRh33XflzpIXv6O1DycY5fXgHRgnqlz4lB1FzpHKOMqrjuEW4QLKQ
         3cGPbfX7XrbR0zP7pyoGwg+PuvGQ9+pFlm+z2bHstBHsrLyd1RDPh7NxUJRuGigkIVOc
         s5jw==
X-Gm-Message-State: AOAM533F152lJlkxqE3RiENP+7gksnM1Ohc3xK4biqF1RFUPfTtxjEWF
        FZy0DXPfeGmB+6QK2KevEb9NsqiK7a4=
X-Google-Smtp-Source: 
 ABdhPJwqGY80yo9FMB+w8ED2zdJKVQ2H2OOCk9+HBaaFhnPzYsKRiWudVo7ZrYUfKFfCx45R6y5zTg==
X-Received: by 2002:a17:902:8b86:b029:e5:bef6:56b0 with SMTP id
 ay6-20020a1709028b86b02900e5bef656b0mr30448266plb.76.1620216926016;
        Wed, 05 May 2021 05:15:26 -0700 (PDT)
Received: from bobo.ozlabs.ibm.com ([61.68.127.20])
        by smtp.gmail.com with ESMTPSA id
 cv24sm14655694pjb.7.2021.05.05.05.15.22
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Wed, 05 May 2021 05:15:25 -0700 (PDT)
From: Nicholas Piggin <npiggin@gmail.com>
To: kvm-ppc@vger.kernel.org
Cc: Nicholas Piggin <npiggin@gmail.com>, kvm@vger.kernel.org,
        linuxppc-dev@lists.ozlabs.org,
        Sean Christopherson <seanjc@google.com>,
        "Aneesh Kumar K . V" <aneesh.kumar@linux.ibm.com>,
        Paolo Bonzini <pbonzini@redhat.com>,
        Bharata B Rao <bharata@linux.ibm.com>
Subject: [PATCH] KVM: PPC: Book3S HV: Fix conversion to gfn-based MMU notifier
 callbacks
Date: Wed,  5 May 2021 22:15:09 +1000
Message-Id: <20210505121509.1470207-1-npiggin@gmail.com>
X-Mailer: git-send-email 2.23.0
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Commit b1c5356e873c ("KVM: PPC: Convert to the gfn-based MMU notifier
callbacks") causes unmap_gfn_range and age_gfn callbacks to only work
on the first gfn in the range. It also makes the aging callbacks call
into both radix and hash aging functions for radix guests. Fix this.

Add warnings for the single-gfn calls that have been converted to range
callbacks, in case they ever receieve ranges greater than 1.

Fixes: b1c5356e873c ("KVM: PPC: Convert to the gfn-based MMU notifier callbacks")
Reported-by: Bharata B Rao <bharata@linux.ibm.com>
Tested-by: Bharata B Rao <bharata@linux.ibm.com>
Signed-off-by: Nicholas Piggin <npiggin@gmail.com>
---
The e500 change in that commit also looks suspicious, why is it okay
to remove kvm_flush_remote_tlbs() there? Also is the the change from
returning false to true intended?

Thanks,
Nick

 arch/powerpc/include/asm/kvm_book3s.h  |  2 +-
 arch/powerpc/kvm/book3s_64_mmu_hv.c    | 46 ++++++++++++++++++--------
 arch/powerpc/kvm/book3s_64_mmu_radix.c |  5 ++-
 3 files changed, 36 insertions(+), 17 deletions(-)

```
#### [PATCH 1/3] KVM: selftests: evmcs_test: Check that VMLAUNCH with bogus EVMPTR is causing #UD
##### From: Vitaly Kuznetsov <vkuznets@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Vitaly Kuznetsov <vkuznets@redhat.com>
X-Patchwork-Id: 12240161
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.4 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_CR_TRAILER,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS
	autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 404E3C433ED
	for <kvm@archiver.kernel.org>; Wed,  5 May 2021 15:18:39 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 1794560200
	for <kvm@archiver.kernel.org>; Wed,  5 May 2021 15:18:39 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S233534AbhEEPTc (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Wed, 5 May 2021 11:19:32 -0400
Received: from us-smtp-delivery-124.mimecast.com ([216.205.24.124]:59661 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S233476AbhEEPT1 (ORCPT
        <rfc822;kvm@vger.kernel.org>); Wed, 5 May 2021 11:19:27 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1620227910;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding:
         in-reply-to:in-reply-to:references:references;
        bh=jdEvneCWyil2ISxR35j5JgadXQtJ5dFEDKqIji5H1SA=;
        b=SFsBXIE62cY6U89EsrjzmHTPP7iLD/00rM9epQ/XOsP5tURQhsN6SwJJEjn0QSzbAzBJyV
        Nn52D6Q04v/3E63C6+EZ0aApGAqu+1VJofOJq/cAKtvCVKzEzIm3G7TTYhcpv2VxJUpo7j
        PYSiEbg70VVK8ctDSrVxkZGd82q0pSU=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-257-cDpTHzW_O46ZnPlXdcX3wg-1; Wed, 05 May 2021 11:18:29 -0400
X-MC-Unique: cDpTHzW_O46ZnPlXdcX3wg-1
Received: from smtp.corp.redhat.com (int-mx06.intmail.prod.int.phx2.redhat.com
 [10.5.11.16])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 221628189C3;
        Wed,  5 May 2021 15:18:28 +0000 (UTC)
Received: from vitty.brq.redhat.com (unknown [10.40.194.168])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 5C7265C1A3;
        Wed,  5 May 2021 15:18:26 +0000 (UTC)
From: Vitaly Kuznetsov <vkuznets@redhat.com>
To: kvm@vger.kernel.org, Paolo Bonzini <pbonzini@redhat.com>
Cc: Sean Christopherson <seanjc@google.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Maxim Levitsky <mlevitsk@redhat.com>,
        linux-kernel@vger.kernel.org
Subject: [PATCH 1/3] KVM: selftests: evmcs_test: Check that VMLAUNCH with
 bogus EVMPTR is causing #UD
Date: Wed,  5 May 2021 17:18:21 +0200
Message-Id: <20210505151823.1341678-2-vkuznets@redhat.com>
In-Reply-To: <20210505151823.1341678-1-vkuznets@redhat.com>
References: <20210505151823.1341678-1-vkuznets@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.16
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

'run->exit_reason == KVM_EXIT_SHUTDOWN' check is not ideal as we may be
getting some unexpected exception. Directly check for #UD instead.

Signed-off-by: Vitaly Kuznetsov <vkuznets@redhat.com>
---
 .../testing/selftests/kvm/x86_64/evmcs_test.c | 24 ++++++++++++-------
 1 file changed, 16 insertions(+), 8 deletions(-)

```
#### [kvm-unit-tests GIT PULL 1/9] s390x: mvpg: add checks for op_acc_id
##### From: Janosch Frank <frankja@linux.ibm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Janosch Frank <frankja@linux.ibm.com>
X-Patchwork-Id: 12239355
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.8 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT
	autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id A4ADDC4360C
	for <kvm@archiver.kernel.org>; Wed,  5 May 2021 08:43:38 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 74F6B6121F
	for <kvm@archiver.kernel.org>; Wed,  5 May 2021 08:43:38 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S232141AbhEEIod (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Wed, 5 May 2021 04:44:33 -0400
Received: from mx0b-001b2d01.pphosted.com ([148.163.158.5]:19732 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S231923AbhEEIoa (ORCPT
        <rfc822;kvm@vger.kernel.org>); Wed, 5 May 2021 04:44:30 -0400
Received: from pps.filterd (m0098419.ppops.net [127.0.0.1])
        by mx0b-001b2d01.pphosted.com (8.16.0.43/8.16.0.43) with SMTP id
 1458XhwE042809;
        Wed, 5 May 2021 04:43:33 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=ibm.com;
 h=from : to : cc : subject
 : date : message-id : in-reply-to : references : content-transfer-encoding
 : mime-version; s=pp1; bh=GdFoX1wU6DPtisMn3o8P172njLGjYpCBNdARkJ6xn1M=;
 b=l49g6YuJTh2/j4qYNOFJ6WXZkLcjX3HOa5oHM1jlhv3cHA4ArTnuccSGc/PxSDSHOCRd
 KZWa+JRewfAtjWfzKnG1wb03DsZ54UfXZ3u5TKiIFKcNPW02sPuT1xldZRpE2L4SJ5ua
 pPfVgEVTDCf3z+rS6MYZoVlbOCBBExlIXAR85x2Ne8nva3afSLqwg0Xx5cy0aef4vcI1
 d02X0WSf0dMpEs54lTuP3fYcar8FkTjc1VGzPBnQgq2hRhh+3xaNlkRO0OQvRpzKrySS
 9RhGMf2xJo1naLleByUOR4yavRjdxJpVYflwQUsTTREnGyROoFwMzrvhav4eboE3jz6r vg==
Received: from pps.reinject (localhost [127.0.0.1])
        by mx0b-001b2d01.pphosted.com with ESMTP id 38bpu1a200-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Wed, 05 May 2021 04:43:33 -0400
Received: from m0098419.ppops.net (m0098419.ppops.net [127.0.0.1])
        by pps.reinject (8.16.0.43/8.16.0.43) with SMTP id 1458aufk056054;
        Wed, 5 May 2021 04:43:33 -0400
Received: from ppma03fra.de.ibm.com (6b.4a.5195.ip4.static.sl-reverse.com
 [149.81.74.107])
        by mx0b-001b2d01.pphosted.com with ESMTP id 38bpu1a1yf-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Wed, 05 May 2021 04:43:32 -0400
Received: from pps.filterd (ppma03fra.de.ibm.com [127.0.0.1])
        by ppma03fra.de.ibm.com (8.16.0.43/8.16.0.43) with SMTP id
 1458h920026813;
        Wed, 5 May 2021 08:43:31 GMT
Received: from b06avi18878370.portsmouth.uk.ibm.com
 (b06avi18878370.portsmouth.uk.ibm.com [9.149.26.194])
        by ppma03fra.de.ibm.com with ESMTP id 38beebg3jg-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Wed, 05 May 2021 08:43:31 +0000
Received: from b06wcsmtp001.portsmouth.uk.ibm.com
 (b06wcsmtp001.portsmouth.uk.ibm.com [9.149.105.160])
        by b06avi18878370.portsmouth.uk.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id 1458h2m335979752
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Wed, 5 May 2021 08:43:02 GMT
Received: from b06wcsmtp001.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 212D8A405B;
        Wed,  5 May 2021 08:43:28 +0000 (GMT)
Received: from b06wcsmtp001.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 88241A405C;
        Wed,  5 May 2021 08:43:27 +0000 (GMT)
Received: from localhost.localdomain.com (unknown [9.145.65.32])
        by b06wcsmtp001.portsmouth.uk.ibm.com (Postfix) with ESMTP;
        Wed,  5 May 2021 08:43:27 +0000 (GMT)
From: Janosch Frank <frankja@linux.ibm.com>
To: pbonzini@redhat.com
Cc: kvm@vger.kernel.org, frankja@linux.ibm.com, david@redhat.com,
        borntraeger@de.ibm.com, cohuck@redhat.com,
        linux-s390@vger.kernel.org, imbrenda@linux.ibm.com,
        thuth@redhat.com
Subject: [kvm-unit-tests GIT PULL 1/9] s390x: mvpg: add checks for op_acc_id
Date: Wed,  5 May 2021 10:42:53 +0200
Message-Id: <20210505084301.17395-2-frankja@linux.ibm.com>
X-Mailer: git-send-email 2.30.2
In-Reply-To: <20210505084301.17395-1-frankja@linux.ibm.com>
References: <20210505084301.17395-1-frankja@linux.ibm.com>
X-TM-AS-GCONF: 00
X-Proofpoint-ORIG-GUID: yXDnp0xwnVDb5_kJCE1ilQ-58pgfDUe1
X-Proofpoint-GUID: jXUpoxw74SarxpXGnHPGL6M-UxtJ2360
X-Proofpoint-UnRewURL: 0 URL was un-rewritten
MIME-Version: 1.0
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.391,18.0.761
 definitions=2021-05-05_02:2021-05-05,2021-05-05 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 impostorscore=0 clxscore=1015
 bulkscore=0 mlxscore=0 spamscore=0 adultscore=0 malwarescore=0
 suspectscore=0 mlxlogscore=999 lowpriorityscore=0 priorityscore=1501
 phishscore=0 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.12.0-2104060000 definitions=main-2105050063
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Claudio Imbrenda <imbrenda@linux.ibm.com>

Check the operand access identification when MVPG causes a page fault.

Signed-off-by: Claudio Imbrenda <imbrenda@linux.ibm.com>
Reviewed-by: David Hildenbrand <david@redhat.com>
Reviewed-by: Thomas Huth <thuth@redhat.com>
Reviewed-by: Janosch Frank <frankja@linux.ibm.com>
Link: https://lore.kernel.org/kvm/20210427121608.157783-1-imbrenda@linux.ibm.com/
Signed-off-by: Janosch Frank <frankja@linux.ibm.com>
---
 s390x/mvpg.c | 28 ++++++++++++++++++++++++++--
 1 file changed, 26 insertions(+), 2 deletions(-)

```
#### [PATCH kvm-unit-tests] libcflat: provide long division routines
##### From: Paolo Bonzini <pbonzini@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Paolo Bonzini <pbonzini@redhat.com>
X-Patchwork-Id: 12239953
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.4 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_CR_TRAILER,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS
	autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id C5759C433ED
	for <kvm@archiver.kernel.org>; Wed,  5 May 2021 13:14:29 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 892C161222
	for <kvm@archiver.kernel.org>; Wed,  5 May 2021 13:14:29 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S233098AbhEENPY (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Wed, 5 May 2021 09:15:24 -0400
Received: from us-smtp-delivery-124.mimecast.com ([216.205.24.124]:42402 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S231459AbhEENPX (ORCPT
        <rfc822;kvm@vger.kernel.org>); Wed, 5 May 2021 09:15:23 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1620220465;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=NWINzhtlXjUQSxmPL8NL6Sy7IaVCAblycSDLmVTRkxA=;
        b=A0YwIemqxn+g17ZhShXIu2zbpg9DVVZVKjr3sMqxu6oSkiv/7Q3miJ9zt32PjK+ae7W1/F
        ORkGUSMJvTiHE1GwN5yWI3PSGTzHozJBRTf1p5k++9jv5nvrZg7t4OWqZRxlXcrlpkQiZf
        xgdTcARpHeiCIdowHsAeb2SwEh7oQG4=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-567-_BA_IGprNi6BOCtHSjuWEw-1; Wed, 05 May 2021 09:14:23 -0400
X-MC-Unique: _BA_IGprNi6BOCtHSjuWEw-1
Received: from smtp.corp.redhat.com (int-mx07.intmail.prod.int.phx2.redhat.com
 [10.5.11.22])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id F2BD310866D9;
        Wed,  5 May 2021 13:14:12 +0000 (UTC)
Received: from virtlab701.virt.lab.eng.bos.redhat.com
 (virtlab701.virt.lab.eng.bos.redhat.com [10.19.152.228])
        by smtp.corp.redhat.com (Postfix) with ESMTP id AA6D91064146;
        Wed,  5 May 2021 13:14:12 +0000 (UTC)
From: Paolo Bonzini <pbonzini@redhat.com>
To: kvm@vger.kernel.org
Cc: Bill Wendling <morbo@google.com>
Subject: [PATCH kvm-unit-tests] libcflat: provide long division routines
Date: Wed,  5 May 2021 09:14:12 -0400
Message-Id: <20210505131412.654238-1-pbonzini@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.84 on 10.5.11.22
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The -nostdlib flag disables the driver from adding libclang_rt.*.a
during linking. Adding a specific library to the command line such as
libgcc then causes the linker to report unresolved symbols, because the
libraries that resolve those symbols aren't automatically added.

libgcc however is only needed for long division (64-bit by 64-bit).
Instead of linking the whole of it, implement the routines that are
needed.

Reported-by: Bill Wendling <morbo@google.com>
Signed-off-by: Paolo Bonzini <pbonzini@redhat.com>
---
 arm/Makefile.arm  |   1 +
 lib/ldiv32.c      | 105 ++++++++++++++++++++++++++++++++++++++++++++++
 x86/Makefile.i386 |   2 +-
 3 files changed, 107 insertions(+), 1 deletion(-)
 create mode 100644 lib/ldiv32.c

```
#### KVM: x86: Cancel pvclock_gtod_work on module removal
##### From: Thomas Gleixner <tglx@linutronix.de>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Thomas Gleixner <tglx@linutronix.de>
X-Patchwork-Id: 12241257
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-13.6 required=3.0 tests=BAYES_00,DKIM_INVALID,
	DKIM_SIGNED,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED autolearn=ham
	autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 6D6B6C433ED
	for <kvm@archiver.kernel.org>; Wed,  5 May 2021 21:48:25 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 3CB1661164
	for <kvm@archiver.kernel.org>; Wed,  5 May 2021 21:48:25 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S230370AbhEEVtU (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Wed, 5 May 2021 17:49:20 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:51888 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S229968AbhEEVtS (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 5 May 2021 17:49:18 -0400
Received: from galois.linutronix.de (Galois.linutronix.de
 [IPv6:2a0a:51c0:0:12e:550::1])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 59B5BC061574;
        Wed,  5 May 2021 14:48:21 -0700 (PDT)
From: Thomas Gleixner <tglx@linutronix.de>
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=linutronix.de;
        s=2020; t=1620251297;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:content-type:content-type;
        bh=DwnDbRYPGOB6QSqiEY7AuTKE84++kwmlDEV1tcogAv0=;
        b=IcbSGt/aNAWDrw7qHp4Wt8BC0pn3AjDcHV/mHlqw2N2CyjBBYWo68W2MyuGT4p1O9zkz/f
        zbXaj21XFjY1WP1sUbezCn9QsRTJLfRG97KxkwF0kfZPgHFdnxOQGgRXEi52Bbnb1N168T
        WUNxiGfmhyuUkFmsJYh/sdTMSD+5+GfIOZ7BHfJrIQh0LbvxGTRThHscV+EseE1+AlHeJA
        3LAv4i1pkq4MiCT0Rms7FFIzNmxpPxjplHP4NDibsWxaN4vo8Vk5mr2vQ89k1561mMj34n
        7PRVnrNEk4c1Y/UGrlFkViwJ+Z3xFyKCqXqxXYRAMw3KCKE+vdF7X5gxLKabmg==
DKIM-Signature: v=1; a=ed25519-sha256; c=relaxed/relaxed; d=linutronix.de;
        s=2020e; t=1620251297;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:content-type:content-type;
        bh=DwnDbRYPGOB6QSqiEY7AuTKE84++kwmlDEV1tcogAv0=;
        b=DCbmaGOAWxbh7gginzBuFNGOZA2b1+9xNNptOuadeawYHzdDig1Ftb6TFP/0JRINV4+FZW
        bkJWphTAQQeN6NAg==
To: kvm@vger.kernel.org
Cc: Paolo Bonzini <pbonzini@redhat.com>,
        Sean Christopherson <seanjc@google.com>, x86@kernel.org,
        LKML <linux-kernel@vger.kernel.org>
Subject: KVM: x86: Cancel pvclock_gtod_work on module removal
Date: Wed, 05 May 2021 23:48:17 +0200
Message-ID: <87czu4onry.ffs@nanos.tec.linutronix.de>
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Nothing prevents the following:

  pvclock_gtod_notify()
    queue_work(system_long_wq, &pvclock_gtod_work);
  ...
  remove_module(kvm);
  ...
  work_queue_run()
    pvclock_gtod_work()	<- UAF

Ditto for any other operation on that workqueue list head which touches
pvclock_gtod_work after module removal.

Cancel the work in kvm_arch_exit() to prevent that.

Fixes: 16e8d74d2da9 ("KVM: x86: notifier for clocksource changes")
Signed-off-by: Thomas Gleixner <tglx@linutronix.de>
---
Found by inspection because of:
  https://lkml.kernel.org/r/0000000000001d43ac05c0f5c6a0@google.com
See also:
  https://lkml.kernel.org/r/20210505105940.190490250@infradead.org

TL;DR: Scheduling work with tk_core.seq write held is a bad idea.
---
 arch/x86/kvm/x86.c |    1 +
```
#### [PATCH 5/5] target/ppc/kvm: Replace alloca() by g_malloc()
##### From: =?utf-8?q?Philippe_Mathieu-Daud=C3=A9?= <philmd@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 8bit
X-Patchwork-Submitter: =?utf-8?q?Philippe_Mathieu-Daud=C3=A9?=
 <philmd@redhat.com>
X-Patchwork-Id: 12240679
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-19.4 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_CR_TRAILER,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,
	USER_AGENT_GIT autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 5907DC43461
	for <kvm@archiver.kernel.org>; Wed,  5 May 2021 17:27:14 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 304D46105A
	for <kvm@archiver.kernel.org>; Wed,  5 May 2021 17:27:14 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S237502AbhEER2J (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Wed, 5 May 2021 13:28:09 -0400
Received: from us-smtp-delivery-124.mimecast.com ([216.205.24.124]:41866 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S235915AbhEERCY (ORCPT
        <rfc822;kvm@vger.kernel.org>); Wed, 5 May 2021 13:02:24 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1620234084;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:content-type:content-type:
         content-transfer-encoding:content-transfer-encoding:
         in-reply-to:in-reply-to:references:references;
        bh=7g2k8F+O24ILX6i9wlywTWqxuX2ak4LnZOnLn8IJqNY=;
        b=I0Acs7JkAFBGnjbE8cg/Ed4v4TpGNX+hKW6gXg9rfrvLDEC5VUREMhdQjZ11yJ1YkugWBi
        PNs0IC4b/N6wY7U30ZRX7LqayFAnVQQUiNY6rxqw9Dg3UQVnedQp1IXEzV0VwIVEeeTGVY
        FhdC/d24D/bVmKtiwbVOhFWn6hH8/HU=
Received: from mail-wr1-f71.google.com (mail-wr1-f71.google.com
 [209.85.221.71]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-437-CCqmUhZyN6m7PTGLXZo43A-1; Wed, 05 May 2021 13:01:22 -0400
X-MC-Unique: CCqmUhZyN6m7PTGLXZo43A-1
Received: by mail-wr1-f71.google.com with SMTP id
 65-20020adf82c70000b0290107593a42c3so953910wrc.5
        for <kvm@vger.kernel.org>; Wed, 05 May 2021 10:01:22 -0700 (PDT)
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:in-reply-to
         :references:mime-version:content-transfer-encoding;
        bh=7g2k8F+O24ILX6i9wlywTWqxuX2ak4LnZOnLn8IJqNY=;
        b=ojetDUjuou6o9lx60fC+/CQrZmtqRndNolXN6C8fy+i71/p1UYESYX7otilo1UIB4k
         OBeWMyr7J2aFojfeBl85IOTHZFRccaSUsJxb9ulDiNkiKL9tHA4zeclv5CAMJh6PmEZ4
         bBocrHGsXwQo6AfvllJSVeRIMyv8u1YuTEjbYRjkSBvH8YInuMY0aAF2xWvRHZL2wjlq
         kIHe/YjZXErGM403ZebXqb0eaT42umKrutVtCMiPDjDDrREwwFUUK/YK1/RGX++QYFkI
         e7t4yqabFnEDTiLfS7IR1oSMofI4vlnR6pDDiww/4WfNG4PnPTo2ZUJdlJ0HtY0ns1Gn
         aiDQ==
X-Gm-Message-State: AOAM530qDDdY6nj1DEZs7kTwJ3+HgpMmrFe0R2bqr7mxV70d1qwziwKS
        2Gb9ziPh3up6kXRsXW34wy7A3ihmsqiWRcSF8FERDEex0lztPvfFkK1/IlK2RPEyPJulmHZiEZR
        ch2n/u96cZ2bX
X-Received: by 2002:a1c:1d50:: with SMTP id
 d77mr11295070wmd.114.1620234081690;
        Wed, 05 May 2021 10:01:21 -0700 (PDT)
X-Google-Smtp-Source: 
 ABdhPJzmgH4JwP3i9dHZjwwiWSGdQcazy8feE/fCrd6Xa/tz3JD28tBwB4MYsNyH0CmUS+lyRxh2hg==
X-Received: by 2002:a1c:1d50:: with SMTP id
 d77mr11295057wmd.114.1620234081584;
        Wed, 05 May 2021 10:01:21 -0700 (PDT)
Received: from x1w.redhat.com
 (astrasbourg-653-1-188-220.w90-13.abo.wanadoo.fr. [90.13.127.220])
        by smtp.gmail.com with ESMTPSA id
 q10sm15824317wre.92.2021.05.05.10.01.20
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Wed, 05 May 2021 10:01:21 -0700 (PDT)
From: =?utf-8?q?Philippe_Mathieu-Daud=C3=A9?= <philmd@redhat.com>
To: qemu-devel@nongnu.org
Cc: =?utf-8?q?Philippe_Mathieu-Daud=C3=A9?= <philmd@redhat.com>,
 David Gibson <david@gibson.dropbear.id.au>,
 Paolo Bonzini <pbonzini@redhat.com>, Warner Losh <imp@bsdimp.com>,
 Kyle Evans <kevans@freebsd.org>, Greg Kurz <groug@kaod.org>, =?utf-8?q?Alex?=
	=?utf-8?q?_Benn=C3=A9e?= <alex.bennee@linaro.org>,
 qemu-ppc@nongnu.org (open list:PowerPC TCG CPUs),
 kvm@vger.kernel.org (open list:Overall KVM CPUs)
Subject: [PATCH 5/5] target/ppc/kvm: Replace alloca() by g_malloc()
Date: Wed,  5 May 2021 19:00:55 +0200
Message-Id: <20210505170055.1415360-6-philmd@redhat.com>
X-Mailer: git-send-email 2.26.3
In-Reply-To: <20210505170055.1415360-1-philmd@redhat.com>
References: <20210505170055.1415360-1-philmd@redhat.com>
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The ALLOCA(3) man-page mentions its "use is discouraged".

Replace it by a g_malloc() call.

Signed-off-by: Philippe Mathieu-Daudé <philmd@redhat.com>
---
 target/ppc/kvm.c | 10 +++++-----
 1 file changed, 5 insertions(+), 5 deletions(-)

```
#### [PATCH 21/23] target/ppc/kvm: Avoid dynamic stack allocation
##### From: =?utf-8?q?Philippe_Mathieu-Daud=C3=A9?= <philmd@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 8bit
X-Patchwork-Submitter: =?utf-8?q?Philippe_Mathieu-Daud=C3=A9?=
 <philmd@redhat.com>
X-Patchwork-Id: 12241051
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-19.4 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_CR_TRAILER,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,
	USER_AGENT_GIT autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id E92E2C433ED
	for <kvm@archiver.kernel.org>; Wed,  5 May 2021 21:12:41 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id BCE4E613E9
	for <kvm@archiver.kernel.org>; Wed,  5 May 2021 21:12:41 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S233831AbhEEVNh (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Wed, 5 May 2021 17:13:37 -0400
Received: from us-smtp-delivery-124.mimecast.com ([216.205.24.124]:36271 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S233738AbhEEVNf (ORCPT
        <rfc822;kvm@vger.kernel.org>); Wed, 5 May 2021 17:13:35 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1620249158;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:content-type:content-type:
         content-transfer-encoding:content-transfer-encoding:
         in-reply-to:in-reply-to:references:references;
        bh=gqZEVFVeZ1PP5CqVjY9bmTR5zVRvOWsxXWPKEVWrRSk=;
        b=gY5Rx3Q7V55uJUS5JC2o2BYyF3eSr66pjB8CeBgzbPylsW4hGn1jpW3qbEzf7Mos+md85M
        U/rouloOmcIK1oJ8UMvPdSzKc5dNk27afIczwlA6p5oExFVclpFw0W+qgIMacFfvRPrc60
        mThiY77P2+9KyS+l762/oT5yQR7iem4=
Received: from mail-wm1-f70.google.com (mail-wm1-f70.google.com
 [209.85.128.70]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-453-9e9KUVFQMOqkQruZSyFzAw-1; Wed, 05 May 2021 17:12:36 -0400
X-MC-Unique: 9e9KUVFQMOqkQruZSyFzAw-1
Received: by mail-wm1-f70.google.com with SMTP id
 b16-20020a7bc2500000b029014587f5376dso1785829wmj.1
        for <kvm@vger.kernel.org>; Wed, 05 May 2021 14:12:36 -0700 (PDT)
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:in-reply-to
         :references:mime-version:content-transfer-encoding;
        bh=gqZEVFVeZ1PP5CqVjY9bmTR5zVRvOWsxXWPKEVWrRSk=;
        b=uVFJbzL75ETUrW77YOvh7NBcYLq6/Xavqw0+HwTta6HtRY6FhmTHwZlwKP4VY7Z8U8
         f9B5xCh12ijmQYmY74NO6aR3oPJdWoEB3r0WUFiJa648J+QqIzARZLol/jd9nMpD0Yba
         /o9PiknME+65v3rtYWeplmP8YJzeQFPTKmzU4JriDlFn8YxS6vedYWjNA63obTt18rkU
         LVpinsIKya/YrDXQIxOMiJothEXeo0on43Pi7yjWIM9n/2SgGA7ZeYPNN+hyTm686v4P
         LJxauIImMM5ewYfGX0ukJbTv59hp8G3bvSU+33yN/7+JAuVQda3zit/rBkk3HNyb5KmQ
         x8Mg==
X-Gm-Message-State: AOAM532gIHN4SYHqkbd9t5o9Eq9H9j8o6etG/Tl+wesrO0QlTroJVHs1
        lBhpC3zFGY3YuUyRuJ5T7qL1OuIRS/T2FJq9lWi2+9cS8F/RhbQ8xJwAenkkuM4HcxacTyKfJlZ
        QfRd5RSbBeylG
X-Received: by 2002:a5d:4351:: with SMTP id u17mr1030237wrr.47.1620249155513;
        Wed, 05 May 2021 14:12:35 -0700 (PDT)
X-Google-Smtp-Source: 
 ABdhPJxdfQQZsRtZ7nyL+DSHqlEkFdqu+Hv47j75LD54ri+lhlT8Xt5UqHtwkM5tFFazugNDQCPNDw==
X-Received: by 2002:a5d:4351:: with SMTP id u17mr1030222wrr.47.1620249155407;
        Wed, 05 May 2021 14:12:35 -0700 (PDT)
Received: from x1w.redhat.com
 (astrasbourg-653-1-188-220.w90-13.abo.wanadoo.fr. [90.13.127.220])
        by smtp.gmail.com with ESMTPSA id
 g129sm8432025wmg.27.2021.05.05.14.12.34
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Wed, 05 May 2021 14:12:35 -0700 (PDT)
From: =?utf-8?q?Philippe_Mathieu-Daud=C3=A9?= <philmd@redhat.com>
To: qemu-devel@nongnu.org
Cc: qemu-block@nongnu.org,
 =?utf-8?q?Daniel_P=2E_Berrang=C3=A9?= <berrange@redhat.com>,
 qemu-ppc@nongnu.org, Gerd Hoffmann <kraxel@redhat.com>, =?utf-8?q?Marc-Andr?=
	=?utf-8?q?=C3=A9_Lureau?= <marcandre.lureau@redhat.com>,
 Paolo Bonzini <pbonzini@redhat.com>,
 Richard Henderson <richard.henderson@linaro.org>, =?utf-8?q?Philippe_Mathie?=
	=?utf-8?q?u-Daud=C3=A9?= <philmd@redhat.com>,
 David Gibson <david@gibson.dropbear.id.au>, Greg Kurz <groug@kaod.org>,
 kvm@vger.kernel.org (open list:Overall KVM CPUs)
Subject: [PATCH 21/23] target/ppc/kvm: Avoid dynamic stack allocation
Date: Wed,  5 May 2021 23:10:45 +0200
Message-Id: <20210505211047.1496765-22-philmd@redhat.com>
X-Mailer: git-send-email 2.26.3
In-Reply-To: <20210505211047.1496765-1-philmd@redhat.com>
References: <20210505211047.1496765-1-philmd@redhat.com>
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Use autofree heap allocation instead of variable-length
array on the stack.

Signed-off-by: Philippe Mathieu-Daudé <philmd@redhat.com>
---
 target/ppc/kvm.c | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
#### [RFC][PATCH] vhost/vsock: Add vsock_list file to map cid with vhost tasks
##### From: Steven Rostedt <rostedt@goodmis.org>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Steven Rostedt <rostedt@goodmis.org>
X-Patchwork-Id: 12240993
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-15.2 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED,USER_AGENT_SANE_2
	autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 3AE81C43460
	for <kvm@archiver.kernel.org>; Wed,  5 May 2021 20:39:10 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 1F3E3613EA
	for <kvm@archiver.kernel.org>; Wed,  5 May 2021 20:39:10 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S234968AbhEEUkD (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Wed, 5 May 2021 16:40:03 -0400
Received: from mail.kernel.org ([198.145.29.99]:46990 "EHLO mail.kernel.org"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S234675AbhEEUkC (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 5 May 2021 16:40:02 -0400
Received: from gandalf.local.home (cpe-66-24-58-225.stny.res.rr.com
 [66.24.58.225])
        (using TLSv1.2 with cipher ECDHE-RSA-AES256-GCM-SHA384 (256/256 bits))
        (No client certificate requested)
        by mail.kernel.org (Postfix) with ESMTPSA id 37678613E3;
        Wed,  5 May 2021 20:39:04 +0000 (UTC)
Date: Wed, 5 May 2021 16:38:55 -0400
From: Steven Rostedt <rostedt@goodmis.org>
To: LKML <linux-kernel@vger.kernel.org>
Cc: Stefan Hajnoczi <stefanha@redhat.com>,
        Stefano Garzarella <sgarzare@redhat.com>,
        "Michael S. Tsirkin" <mst@redhat.com>,
        Jason Wang <jasowang@redhat.com>,
        "David S. Miller" <davem@davemloft.net>,
        Jakub Kicinski <kuba@kernel.org>, kvm@vger.kernel.org,
        virtualization@lists.linux-foundation.org, netdev@vger.kernel.org,
        Joel Fernandes <joelaf@google.com>,
        Linux Trace Devel <linux-trace-devel@vger.kernel.org>
Subject: [RFC][PATCH] vhost/vsock: Add vsock_list file to map cid with vhost
 tasks
Message-ID: <20210505163855.32dad8e7@gandalf.local.home>
X-Mailer: Claws Mail 3.17.8 (GTK+ 2.24.33; x86_64-pc-linux-gnu)
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The new trace-cmd 3.0 (which is almost ready to be released) allows for
tracing between host and guests with timestamp synchronization such that
the events on the host and the guest can be interleaved in the proper order
that they occur. KernelShark now has a plugin that visualizes this
interaction.

The implementation requires that the guest has a vsock CID assigned, and on
the guest a "trace-cmd agent" is running, that will listen on a port for
the CID. The on the host a "trace-cmd record -A guest@cid:port -e events"
can be called and the host will connect to the guest agent through the
cid/port pair and have the agent enable tracing on behalf of the host and
send the trace data back down to it.

The problem is that there is no sure fire way to find the CID for a guest.
Currently, the user must know the cid, or we have a hack that looks for the
qemu process and parses the --guest-cid parameter from it. But this is
prone to error and does not work on other implementation (was told that
crosvm does not use qemu).

As I can not find a way to discover CIDs assigned to guests via any kernel
interface, I decided to create this one. Note, I'm not attached to it. If
there's a better way to do this, I would love to have it. But since I'm not
an expert in the networking layer nor virtio, I decided to stick to what I
know and add a debugfs interface that simply lists all the registered CIDs
and the worker task that they are associated with. The worker task at
least has the PID of the task it represents.

Now I can find the cid / host process in charge of the guest pair:

  # cat /sys/kernel/debug/vsock_list
  3	vhost-1954:2002

  # ps aux | grep 1954
  qemu        1954  9.9 21.3 1629092 796148 ?      Sl   16:22   0:58  /usr/bin/qemu-kvm -name guest=Fedora21,debug-threads=on -S -object secret,id=masterKey0,format=raw,file=/var/lib/libvirt/qemu/domain-1-Fedora21/master-key.aes -machine pc-1.2,accel=kvm,usb=off,dump-guest-core=off -cpu qemu64 -m 1000 -overcommit mem-lock=off -smp 2,sockets=2,cores=1,threads=1 -uuid 1eefeeb0-3ac7-07c1-926e-236908313b4c -no-user-config -nodefaults -chardev socket,id=charmonitor,fd=32,server,nowait -mon chardev=charmonitor,id=monitor,mode=control -rtc base=utc -no-shutdown -boot strict=on -device piix3-usb-uhci,id=usb,bus=pci.0,addr=0x1.0x2 -device virtio-serial-pci,id=virtio-serial0,bus=pci.0,addr=0x6 -blockdev {"driver":"host_device","filename":"/dev/mapper/vg_bxtest-GuestFedora","node-name":"libvirt-1-storage","auto-read-only":true,"discard":"unmap"} -blockdev {"node-name":"libvirt-1-format","read-only":false,"driver":"raw","file":"libvirt-1-storage"} -device ide-hd,bus=ide.0,unit=0,drive=libvirt-1-
 format,id=ide0-0-0,bootindex=1 -netdev tap,fd=34,id=hostnet0 -device rtl8139,netdev=hostnet0,id=net0,mac=52:54:00:9f:e9:d5,bus=pci.0,addr=0x3 -netdev tap,fd=35,id=hostnet1 -device virtio-net-pci,netdev=hostnet1,id=net1,mac=52:54:00:ec:dc:6e,bus=pci.0,addr=0x5 -chardev pty,id=charserial0 -device isa-serial,chardev=charserial0,id=serial0 -chardev pipe,id=charchannel0,path=/var/lib/trace-cmd/virt/Fedora21/trace-pipe-cpu0 -device virtserialport,bus=virtio-serial0.0,nr=1,chardev=charchannel0,id=channel0,name=trace-pipe-cpu0 -chardev pipe,id=charchannel1,path=/var/lib/trace-cmd/virt/Fedora21/trace-pipe-cpu1 -device virtserialport,bus=virtio-serial0.0,nr=2,chardev=charchannel1,id=channel1,name=trace-pipe-cpu1 -vnc 127.0.0.1:0 -device cirrus-vga,id=video0,bus=pci.0,addr=0x2 -device virtio-balloon-pci,id=balloon0,bus=pci.0,addr=0x4 -sandbox on,obsolete=deny,elevateprivileges=deny,spawn=deny,resourcecontrol=deny -device vhost-vsock-pci,id=vsock0,guest-cid=3,vhostfd=16,bus=pci.0,addr=0x7 -msg 
 timestamp=on
  root        2000  0.0  0.0      0     0 ?        S    16:22   0:00 [kvm-pit/1954]
  root        2002  0.0  0.0      0     0 ?        S    16:22   0:00 [vhost-1954]


This is just an example of what I'm looking for. Just a way to find what
process is using what cid.

Signed-off-by: Steven Rostedt (VMware) <rostedt@goodmis.org>

```
#### [PATCH 1/6] delayacct: Use sched_clock()References: <20210505105940.190490250@infradead.org>
##### From: Peter Zijlstra <peterz@infradead.org>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Peter Zijlstra <peterz@infradead.org>
X-Patchwork-Id: 12239761
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-15.8 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,
	INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED
	autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 26654C433B4
	for <kvm@archiver.kernel.org>; Wed,  5 May 2021 11:21:23 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id D5A536121F
	for <kvm@archiver.kernel.org>; Wed,  5 May 2021 11:21:22 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S232893AbhEELWS (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Wed, 5 May 2021 07:22:18 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:52050 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S232967AbhEELV7 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 5 May 2021 07:21:59 -0400
Received: from casper.infradead.org (casper.infradead.org
 [IPv6:2001:8b0:10b:1236::1])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id AE6CAC061763;
        Wed,  5 May 2021 04:21:02 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; q=dns/txt; c=relaxed/relaxed;
        d=infradead.org; s=casper.20170209;
 h=Content-Type:MIME-Version:References:
        Subject:Cc:To:From:Date:Message-ID:Sender:Reply-To:Content-Transfer-Encoding:
        Content-ID:Content-Description:In-Reply-To;
        bh=knZbfT8+eIFIsMjLBY2UuSxf8ltNwAg+fgyQDo4qiWI=;
 b=Tit4GMyOzVVskqtUu9EAtmQXbl
        /D1ARDmeAKmr7l2NIk8XIHGRZ4wdLNAfefNyVscP6k482JFkRe712BpfWwcfqnBrjmcynugBq471O
        70D/wOWUfijEm7B9jggyY0mcZol0pL118qtQkLA0C1PuuM8fRujPVyUllMjnXIgqMH085YoSau4Oa
        JPbGGn0zLxFylMTndtS65jzu9h0ge9RiGqZzmBnplk8XbASOCWRkC8VVE2LbyUm8YFnMDjbuSTFgc
        tXCqvC9BOVSWxg0D5UtKe9BgI/93Irhei1TcIU6aKT35xIt2Z1faUlBNWDqLFX/rwybeud07FSM0O
        3ucWZRUA==;
Received: from j217100.upc-j.chello.nl ([24.132.217.100]
 helo=noisy.programming.kicks-ass.net)
        by casper.infradead.org with esmtpsa (Exim 4.94 #2 (Red Hat Linux))
        id 1leFXm-000FR8-02; Wed, 05 May 2021 11:18:44 +0000
Received: from hirez.programming.kicks-ass.net
 (hirez.programming.kicks-ass.net [192.168.1.225])
        (using TLSv1.3 with cipher TLS_AES_256_GCM_SHA384 (256/256 bits)
         key-exchange X25519 server-signature RSA-PSS (2048 bits))
        (Client did not present a certificate)
        by noisy.programming.kicks-ass.net (Postfix) with ESMTPS id
 2F9DA3002A8;
        Wed,  5 May 2021 13:18:15 +0200 (CEST)
Received: by hirez.programming.kicks-ass.net (Postfix, from userid 0)
        id E016D299E985D; Wed,  5 May 2021 13:18:14 +0200 (CEST)
Message-ID: <20210505111525.001031466@infradead.org>
User-Agent: quilt/0.66
Date: Wed, 05 May 2021 12:59:41 +0200
From: Peter Zijlstra <peterz@infradead.org>
To: tglx@linutronix.de, mingo@kernel.org, juri.lelli@redhat.com,
        vincent.guittot@linaro.org, dietmar.eggemann@arm.com,
        rostedt@goodmis.org, bsegall@google.com, mgorman@suse.de,
        bristot@redhat.com, bsingharora@gmail.com, pbonzini@redhat.com,
        maz@kernel.org
Cc: linux-kernel@vger.kernel.org, kvm@vger.kernel.org,
        peterz@infradead.org, riel@surriel.com, hannes@cmpxchg.org
Subject: [PATCH 1/6] delayacct: Use sched_clock()
References: <20210505105940.190490250@infradead.org>
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Like all scheduler statistics, use sched_clock() based time.

Signed-off-by: Peter Zijlstra (Intel) <peterz@infradead.org>
Reviewed-by: Rik van Riel <riel@surriel.com>
---
 kernel/delayacct.c |   22 ++++++++++------------
```
#### SRCU dereference check warning with SEV-ES
##### From: Tom Lendacky <thomas.lendacky@amd.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Tom Lendacky <thomas.lendacky@amd.com>
X-Patchwork-Id: 12240017
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-12.2 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_PATCH,
	MAILING_LIST_MULTI,MSGID_FROM_MTA_HEADER,SPF_HELO_NONE,SPF_PASS,
	USER_AGENT_SANE_1 autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id CCD64C433B4
	for <kvm@archiver.kernel.org>; Wed,  5 May 2021 14:01:33 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id A6FC8610A1
	for <kvm@archiver.kernel.org>; Wed,  5 May 2021 14:01:33 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S233517AbhEEOC2 (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Wed, 5 May 2021 10:02:28 -0400
Received: from mail-bn7nam10on2070.outbound.protection.outlook.com
 ([40.107.92.70]:38176
        "EHLO NAM10-BN7-obe.outbound.protection.outlook.com"
        rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org with ESMTP
        id S233464AbhEEOC0 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 5 May 2021 10:02:26 -0400
ARC-Seal: i=1; a=rsa-sha256; s=arcselector9901; d=microsoft.com; cv=none;
 b=f4WhZSSpPVQ5AxQ45kU4f6BZ474Pmusa12j2QCKrLOdRucfY4XVnTxi4Jqcv8Uh6gC06tf6BxT5uItkEsd1AzyOOrevNLbkbs85xwYAD/M/JTTjWUix5f4Fz3g2hxptdI+kmmzXxW0kcscahRohww9JPhqTiIz3Jr7ifRnzld4rUDbcVFhPQ9vLhK51wo/r4WpcmlO06PnwnchaxF2pTLyp0647AjJifgG2HCIswr5Z7Yv4kUXSMx4BaGk021MLlOZ47ilZUP+RR2gYJQVe7WZ1/AYo01WIjO3+FlnrvrZ/grhx2ftCx2OFVsnApKTQhc0Kh5mbY2je7kImK189A0w==
ARC-Message-Signature: i=1; a=rsa-sha256; c=relaxed/relaxed; d=microsoft.com;
 s=arcselector9901;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=/clkxc7KBa4+pcOjVaSBnql6Pi8DhHT+Hj5ky2/DKjY=;
 b=iW4KlZOsOhhmTgmKdUGpqwRT489pdQy3zOBXQfTsj/1SLdFFaOM0VoTEzpbXmJVySv++tbYMIPWCIstaC3HglNQFlEiFa7Gd/ZwEeKjr6Po2wOujIgNVqrXX9GlF6UjSqS/8wSoVmZ93W5ym4Oc6FcAknvYYqYyvnIqnY7PB2BrzsUeeSgz0+sSPt+X4bo5vp52L95TO2SJmUzrkifGaSmMHkigxlAvVaJeUr9A/jCWSYPbjedvxTK2oxRhC6dDllf8pY73Khp5X+fwmqVFjggDV0w4q8XcmYtyveIJEH6uNhYSqSed2KMcApP2YkveXEkQw2t5p0sztGuqBwJhfTg==
ARC-Authentication-Results: i=1; mx.microsoft.com 1; spf=pass
 smtp.mailfrom=amd.com; dmarc=pass action=none header.from=amd.com; dkim=pass
 header.d=amd.com; arc=none
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=amd.com; s=selector1;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=/clkxc7KBa4+pcOjVaSBnql6Pi8DhHT+Hj5ky2/DKjY=;
 b=BcwxCGt0l8wSPzq4kj+FYFZuV0ydS693bEJrvWdHhHtA0BwfrlchiawJbSNG11T+exv9Wg0aUZ04I1hKjHWrcodDQp8BySNZBxvx0Bvex3NLLoDtwV08cJcSSInn9U3csdS3bqWC1gTpUeWRgLPdNiDtiCJDXlQLNpZEfYT9wI4=
Authentication-Results: alien8.de; dkim=none (message not signed)
 header.d=none;alien8.de; dmarc=none action=none header.from=amd.com;
Received: from DM5PR12MB1355.namprd12.prod.outlook.com (2603:10b6:3:6e::7) by
 DM5PR12MB1163.namprd12.prod.outlook.com (2603:10b6:3:7a::18) with Microsoft
 SMTP Server (version=TLS1_2, cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id
 15.20.4087.35; Wed, 5 May 2021 14:01:28 +0000
Received: from DM5PR12MB1355.namprd12.prod.outlook.com
 ([fe80::b914:4704:ad6f:aba9]) by DM5PR12MB1355.namprd12.prod.outlook.com
 ([fe80::b914:4704:ad6f:aba9%12]) with mapi id 15.20.4087.044; Wed, 5 May 2021
 14:01:28 +0000
To: Paolo Bonzini <pbonzini@redhat.com>, kvm list <kvm@vger.kernel.org>
Cc: Borislav Petkov <bp@alien8.de>
From: Tom Lendacky <thomas.lendacky@amd.com>
Subject: SRCU dereference check warning with SEV-ES
Message-ID: <601f1278-17dd-7124-f328-b865447ca160@amd.com>
Date: Wed, 5 May 2021 09:01:26 -0500
User-Agent: Mozilla/5.0 (X11; Linux x86_64; rv:78.0) Gecko/20100101
 Thunderbird/78.7.1
Content-Language: en-US
X-Originating-IP: [165.204.77.1]
X-ClientProxiedBy: SN7PR04CA0002.namprd04.prod.outlook.com
 (2603:10b6:806:f2::7) To DM5PR12MB1355.namprd12.prod.outlook.com
 (2603:10b6:3:6e::7)
MIME-Version: 1.0
X-MS-Exchange-MessageSentRepresentingType: 1
Received: from [10.236.30.118] (165.204.77.1) by
 SN7PR04CA0002.namprd04.prod.outlook.com (2603:10b6:806:f2::7) with Microsoft
 SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.4108.25 via Frontend
 Transport; Wed, 5 May 2021 14:01:28 +0000
X-MS-PublicTrafficType: Email
X-MS-Office365-Filtering-Correlation-Id: 39e60ffa-9f0d-40c1-699b-08d90fce4740
X-MS-TrafficTypeDiagnostic: DM5PR12MB1163:
X-Microsoft-Antispam-PRVS: 
 <DM5PR12MB1163FAF109E88D74111A0ACFEC599@DM5PR12MB1163.namprd12.prod.outlook.com>
X-MS-Oob-TLC-OOBClassifiers: OLM:8273;
X-MS-Exchange-SenderADCheck: 1
X-Microsoft-Antispam: BCL:0;
X-Microsoft-Antispam-Message-Info: 
 lMHsaHS/EdfPATsRnZ33ITvmEfkc2nTU40Asp2C3Pljl+RJ59U8xmZT4FMkx81VflUZ4DOxykcCXHKabsl5oeu4q6NkMjxXzX0C52m8wkdY/NFJLFjjyxlnj4tSUOgXkzm9Ps24ZUZXjO2oZLSIU5NMjoWbHuNaXR6DhSlRU1XgnDdiJv5Zs8PmBQ8Q6Um1zNCq73IaGrXbxRZkCmzE5cMRtI7EXJr0V2hMn/ca68xgZIrooUz9egkfFuPFLaVneUe39677B4/0xx9WJJEq6OZIF757A37kutWmWIUbv5f3Jj12Ev4r7ea4eqZ9qEV2zeC9vrKT9J62ZyU3UKoazw/tMvTP9C1Q3Xk0N8T3qlH7pRt5q2s0zghzse5x0zi3zUlfYl+xviMLkhAjcWfpZvGJeShYIjHm1CkgfDBLqqOfBffCXWIvycwh2Mq0+MmyizOLXUW++gq2JbbfRdBD5vZZZLNvjZ6jI49j3vvlbzPcDJfgY5cKr8n+W5j19RVSj3ZTHhG5ZKR0MNOK3z+Nl6OO95oS4410pmfQWuab2jMXKS8E2tcDJSbMts1di5gF96PdAff5un3oiykGdirBaLF1lHKkeEddK3UCfYa3dIFK/oavHfNICSbg48tEcJ2qLJd/6xp3tTBtCGnz5gDfe4E87IT4iqA6b+8WDkroLHTmWUYdZhE9FtSGQIJnFseC/
X-Forefront-Antispam-Report: 
 CIP:255.255.255.255;CTRY:;LANG:en;SCL:1;SRV:;IPV:NLI;SFV:NSPM;H:DM5PR12MB1355.namprd12.prod.outlook.com;PTR:;CAT:NONE;SFS:(4636009)(396003)(39860400002)(346002)(376002)(136003)(366004)(956004)(478600001)(86362001)(26005)(31686004)(110136005)(16576012)(2616005)(2906002)(316002)(4326008)(66556008)(5660300002)(8676002)(6486002)(31696002)(38100700002)(83380400001)(66946007)(66476007)(8936002)(36756003)(186003)(16526019)(43740500002)(45980500001);DIR:OUT;SFP:1101;
X-MS-Exchange-AntiSpam-MessageData: =?utf-8?q?BhYJn7dlnO2qGTEXN2dhiMKmRRXW4w?=
	=?utf-8?q?3UCj22t3xIni+NFzLNn9zvOr1Y40AvihMByy8zVy1CDcKceu5k1jN4XFZtrRTIM6R?=
	=?utf-8?q?nAOGVutJOcZUxNavJmnNPzh/tMN0dh18/b3ttukSsCQoDgLNr+Gr5XG/y580+hwIm?=
	=?utf-8?q?rgffnadYTi604uRm9BN4bzoxtpfdAKlHJZGERGudSb+sWdgwXta4ACniLz3Njt5Ru?=
	=?utf-8?q?6pSYOvxIOA0Nqh3NCLwmrZmuuH928IcSq1S6eNNuXny/r3r9fa3JleYR5ui6DdckN?=
	=?utf-8?q?cd8vQPSL26uFCxm0dvKNGd5Rc+ttdBuLBZw2L2hwpoPTqTZOC4JdaO0JAgp9BZoyo?=
	=?utf-8?q?7Lraue2RuGUQMem6mzOsjaEHr0szdHRS4a4xkndYWlWRgG4ci4Ahcz6R36IAjIRDC?=
	=?utf-8?q?Ydbm2t/TeYcnW0VBtQjCxmYERpkKzAtAoBNtf1k5sWAL5DhKMplNr+yJlVFxhHUIp?=
	=?utf-8?q?O48fpB3Bvvy71zcGw9WKxd3gVvsSKUS5Onk+09lWICRfXX6vyvo9k4yHeDRL5MpxB?=
	=?utf-8?q?+SBeTLcW3TeBoyzDJup2CVikNiCW1d3b3zQQnmPPbZMqJhLQXdYoJh7bBu7QH1VnB?=
	=?utf-8?q?Z6lfNHSqswO9XUpuylNlsTePOWMw6fkJ73Ts51DXc1B47ljSqlGWi2XbDgnPgKi+l?=
	=?utf-8?q?I768IMvolg3MA94pIVIiMwjKVv/c70Es4jX2RKXd8/fTBgxBvJF3TvOBsNwQeL0pQ?=
	=?utf-8?q?/0n2wfFJEobp3vrwoMgpEyth40UUcqbSjRsboPT7LtX2sbVGre0LAg8hKr7/GiJz/?=
	=?utf-8?q?fj7nJleE1Jp3C2NGd8qGNekcuEE+qwxwZjj2Wt96hkAqCQsl4sh5B6OGh9Lamxx/b?=
	=?utf-8?q?oDkeQdwIwk89O6gQqJU6c+ULP+tLh3S/CH1LwZdA7yOKEtumLgoNYKPeqr7+gLEJp?=
	=?utf-8?q?m6XAT0m4kyHJrR+7rDk1w8rQkpTsjnvn7/+K/uNzjI0JyTmTV8OI0IZwChz/uybBY?=
	=?utf-8?q?NLueuzjn7VF/2bz06y73/OUc43zGnnOH/obMfG+moPrwYE+IhZwMqQuPFi+FWbQlE?=
	=?utf-8?q?YJL8nVdk2WrxI79c/SIoOi5762AY39iJuQYkxNpLa92z/CFBQb+fPxuG5Ko39rcpS?=
	=?utf-8?q?af6hXTBw83xa8LGx5923XpOGm77J4j7fcuguCAwdPwvZtMAMqWdJZPBeigGeLXRPG?=
	=?utf-8?q?CWiCkgI11HG9HxlidjBfgLAftt/FSXJoacsiryztWopb+eJgS8uRQp3cJTPoPM4m0?=
	=?utf-8?q?YhkmD7Hx6t/vH7MkgWFdbjaC/YJtQPkBmOvgtNTYGtH/liTgOKoBDev3htpGCeMev?=
	=?utf-8?q?BLWCj0cNZewWah?=
X-OriginatorOrg: amd.com
X-MS-Exchange-CrossTenant-Network-Message-Id: 
 39e60ffa-9f0d-40c1-699b-08d90fce4740
X-MS-Exchange-CrossTenant-AuthSource: DM5PR12MB1355.namprd12.prod.outlook.com
X-MS-Exchange-CrossTenant-AuthAs: Internal
X-MS-Exchange-CrossTenant-OriginalArrivalTime: 05 May 2021 14:01:28.3788
 (UTC)
X-MS-Exchange-CrossTenant-FromEntityHeader: Hosted
X-MS-Exchange-CrossTenant-Id: 3dd8961f-e488-4e60-8e11-a82d994e183d
X-MS-Exchange-CrossTenant-MailboxType: HOSTED
X-MS-Exchange-CrossTenant-UserPrincipalName: 
 GDrE7zL3iveI2SEqPyksIn+nHM4TMFU7CWGJTitc9YjfcgQX6RqMQcM3rmaVp+4Fgw4q8wQV89rg+aRYqDMc6w==
X-MS-Exchange-Transport-CrossTenantHeadersStamped: DM5PR12MB1163
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Boris noticed the below warning when running an SEV-ES guest with
CONFIG_PROVE_LOCKING=y.

The SRCU lock is released before invoking the vCPU run op where the SEV-ES
support will unmap the GHCB. Is the proper thing to do here to take the
SRCU lock around the call to kvm_vcpu_unmap() in this case? It does fix
the issue, but I just want to be sure that I shouldn't, instead, be taking
the memslot lock:

Thanks,
Tom 

[   97.455047] =============================
[   97.459150] WARNING: suspicious RCU usage
[   97.463259] 5.11.0 #1 Not tainted
[   97.466674] -----------------------------
[   97.470783] include/linux/kvm_host.h:641 suspicious rcu_dereference_check() usage!
[   97.478479] 
               other info that might help us debug this:

[   97.486606] 
               rcu_scheduler_active = 2, debug_locks = 1
[   97.493246] 1 lock held by qemu-system-x86/3793:
[   97.497967]  #0: ffff88810fe800c8 (&vcpu->mutex){+.+.}-{3:3}, at: kvm_vcpu_ioctl+0x6d/0x650 [kvm]
[   97.507059] 
               stack backtrace:
[   97.511515] CPU: 0 PID: 3793 Comm: qemu-system-x86 Not tainted 5.11.0 #1
[   97.518335] Hardware name: GIGABYTE MZ01-CE1-00/MZ01-CE1-00, BIOS F02 08/29/2018
[   97.525849] Call Trace:
[   97.528385]  dump_stack+0x77/0x97
[   97.531832]  kvm_vcpu_gfn_to_memslot+0x168/0x170 [kvm]
[   97.537172]  kvm_vcpu_unmap+0x28/0x60 [kvm]
[   97.541548]  pre_sev_run+0x122/0x250 [kvm_amd]
[   97.546132]  svm_vcpu_run+0x505/0x760 [kvm_amd]
[   97.550806]  kvm_arch_vcpu_ioctl_run+0xe03/0x1c20 [kvm]
[   97.556251]  ? kvm_arch_vcpu_ioctl_run+0xb9/0x1c20 [kvm]
[   97.561780]  ? __lock_acquire+0x38e/0x1c30
[   97.566031]  kvm_vcpu_ioctl+0x222/0x650 [kvm]
[   97.570585]  ? __fget_files+0xe3/0x190
[   97.574459]  ? __fget_files+0x5/0x190
[   97.578254]  __x64_sys_ioctl+0x98/0xd0
[   97.582130]  ? lockdep_hardirqs_on+0x88/0x120
[   97.586625]  do_syscall_64+0x34/0x50
[   97.590331]  entry_SYSCALL_64_after_hwframe+0x44/0xa9
[   97.595521] RIP: 0033:0x7f728ffeb457
[   97.599222] Code: 00 00 90 48 8b 05 39 7a 0c 00 64 c7 00 26 00 00 00 48 c7 c0 ff ff ff ff c3 66 2e 0f 1f 84 00 00 00 00 00 b8 10 00 00 00 0f 05 <48> 3d 01 f0 ff ff 73 01 c3 48 8b 0d 09 7a 0c 00 f7 d8 64 89 01 48
[   97.618277] RSP: 002b:00007f7287ffe7e8 EFLAGS: 00000246 ORIG_RAX: 0000000000000010
[   97.626029] RAX: ffffffffffffffda RBX: 000000000000ae80 RCX: 00007f728ffeb457
[   97.633315] RDX: 0000000000000000 RSI: 000000000000ae80 RDI: 0000000000000015
[   97.640595] RBP: 000055d927433480 R08: 000055d924adb278 R09: 00000000ffffffff
[   97.647877] R10: 0000000000000001 R11: 0000000000000246 R12: 0000000000000000
[   97.655156] R13: 00007f7290939004 R14: 0000000000000cf8 R15: 0000000000000000

```
#### [PATCH 1/3] KVM: x86/mmu: Fix return value in tdp_mmu_map_handle_target_level()
##### From: Kai Huang <kai.huang@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Kai Huang <kai.huang@intel.com>
X-Patchwork-Id: 12239511
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.8 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED,USER_AGENT_GIT
	autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 772F6C43460
	for <kvm@archiver.kernel.org>; Wed,  5 May 2021 09:38:21 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 37E1F613D6
	for <kvm@archiver.kernel.org>; Wed,  5 May 2021 09:38:21 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S232372AbhEEJjQ (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Wed, 5 May 2021 05:39:16 -0400
Received: from mga12.intel.com ([192.55.52.136]:56202 "EHLO mga12.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S231494AbhEEJjP (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 5 May 2021 05:39:15 -0400
IronPort-SDR: 
 bV6di5pOY2huMfh0nL7iclGGxzVZeR3LTEZrXxznpvRWEUOQ1LuY78iDhwGJkJ8LBz0c9v0+eI
 d4KabCtfxByQ==
X-IronPort-AV: E=McAfee;i="6200,9189,9974"; a="177724143"
X-IronPort-AV: E=Sophos;i="5.82,274,1613462400";
   d="scan'208";a="177724143"
Received: from orsmga008.jf.intel.com ([10.7.209.65])
  by fmsmga106.fm.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 05 May 2021 02:38:19 -0700
IronPort-SDR: 
 jqUUlVS1MbiRYMSZ4cmaSasKPLj5lDy8AaILmWrM5taSPSQZZaaTQTb215REkfHuC8qz8Xgux/
 58qh2qhQmRtg==
X-IronPort-AV: E=Sophos;i="5.82,274,1613462400";
   d="scan'208";a="433728455"
Received: from smorlan-mobl.amr.corp.intel.com (HELO
 khuang2-desk.gar.corp.intel.com) ([10.212.190.185])
  by orsmga008-auth.jf.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 05 May 2021 02:38:16 -0700
From: Kai Huang <kai.huang@intel.com>
To: kvm@vger.kernel.org
Cc: pbonzini@redhat.com, bgardon@google.com, seanjc@google.com,
        vkuznets@redhat.com, wanpengli@tencent.com, jmattson@google.com,
        joro@8bytes.org, Kai Huang <kai.huang@intel.com>
Subject: [PATCH 1/3] KVM: x86/mmu: Fix return value in
 tdp_mmu_map_handle_target_level()
Date: Wed,  5 May 2021 21:37:57 +1200
Message-Id: 
 <00875eb37d6b5cc9d19bb19e31db3130ac1d8730.1620200410.git.kai.huang@intel.com>
X-Mailer: git-send-email 2.31.1
In-Reply-To: <cover.1620200410.git.kai.huang@intel.com>
References: <cover.1620200410.git.kai.huang@intel.com>
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Currently tdp_mmu_map_handle_target_level() returns 0, which is
RET_PF_RETRY, when page fault is actually fixed.  This makes
kvm_tdp_mmu_map() also return RET_PF_RETRY in this case, instead of
RET_PF_FIXED.  Fix by initializing ret to RET_PF_FIXED.

Signed-off-by: Kai Huang <kai.huang@intel.com>
Reviewed-by: Sean Christopherson <seanjc@google.com> 
Reviewed-by: Ben Gardon <bgardon@google.com>
---
 arch/x86/kvm/mmu/tdp_mmu.c | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
#### [PATCH v2] KVM: x86: Prevent KVM SVM from loading on kernels with 5-level paging
##### From: Sean Christopherson <seanjc@google.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Sean Christopherson <seanjc@google.com>
X-Patchwork-Id: 12240995
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
	by smtp.lore.kernel.org (Postfix) with ESMTP id 6EC83C433B4
	for <kvm@archiver.kernel.org>; Wed,  5 May 2021 20:42:27 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 4507A60724
	for <kvm@archiver.kernel.org>; Wed,  5 May 2021 20:42:27 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S235131AbhEEUnW (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Wed, 5 May 2021 16:43:22 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:37142 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S233990AbhEEUnV (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 5 May 2021 16:43:21 -0400
Received: from mail-yb1-xb49.google.com (mail-yb1-xb49.google.com
 [IPv6:2607:f8b0:4864:20::b49])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 9E188C061574
        for <kvm@vger.kernel.org>; Wed,  5 May 2021 13:42:24 -0700 (PDT)
Received: by mail-yb1-xb49.google.com with SMTP id
 y5-20020a2586050000b02904ee36d3b170so3634222ybk.10
        for <kvm@vger.kernel.org>; Wed, 05 May 2021 13:42:24 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=reply-to:date:message-id:mime-version:subject:from:to:cc;
        bh=p4KYU6vAoyfFP2I+rWAeMqwqBN6gnusP1gZ9ljdBr6Y=;
        b=AjLwt9XuECLQRfJeY4C1g/NLMSd3Z/WcBVmKEAtlvoOnl0rUzczKpDXVnH6NK3LtKZ
         9ZZvjHHyMm+Wuc+YSHuZlEirzwFpM1scYyEVMew0zlJjE5ZB57ymqhQUmtjUtM5TmTqF
         hf7AVyJCbtf25Ym6BaID/QCGmVEtnymL5yzlbkMfH4oz5AeT88vFuQptzkMQ0rVqr0mA
         oWLd5LgtTGdBeEmVa/mGYT649ljN2e1e8rm6TC88NEpQaw0kXjxbZszaEDwKaJzyxQsE
         UN/4R85u1MsrwZy6MqIcTt1zAGMZrEsOo4tptC3JY7feT3p2Mz/56Eae2wvbs892dY8a
         udsg==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:reply-to:date:message-id:mime-version:subject
         :from:to:cc;
        bh=p4KYU6vAoyfFP2I+rWAeMqwqBN6gnusP1gZ9ljdBr6Y=;
        b=G7MVZz73oLfiWU/khx+x5TtpeiHGAspejKoWz4dQqkI6ASGhEGgWo+Rt8oFo6rKp3p
         y265zgFPuiq5B8OJgZB8rinEZYEs8N1LyeXtU9+eJmeCw0/SIN+LkIjP5cIdgESlhIdo
         d2MlzBncy9tHRW+nxE/dFKw11l6jjwSK9szW1Pxiq3tHh1NUYoQexzvk6Z5VSA2mtbqx
         cob93dSdH7+4QXstRGBqwbzQMMuwrd5LGa3sgcx7I1ZdIKhgnT5cyd39rhf6nfikdVKg
         OtBw8u6dEHZTOs1lMZcwgeVh8cnhYv/p4jQ7RChBuyCFRDxyn3qcJ82IQIF16eFwU8fe
         9/Mw==
X-Gm-Message-State: AOAM533ZtRuO9RAQUL6gpbzVUSyurOno1/bpqo3g/jiljaZpaWxQ7TmX
        VBZrvEsgUkSjDrUNXBMqbDWV0eGTHxI=
X-Google-Smtp-Source: 
 ABdhPJyhxsVq7IOOVFOBQ7XJ7A9Ak4ReXLqq9wnO5KfzeBNv+2Ch/rAhuQ9n1wP7zLmYmUm5Fr/DG+iz/Cg=
X-Received: from seanjc798194.pdx.corp.google.com
 ([2620:15c:f:10:820b:3fc:8d69:7035])
 (user=seanjc job=sendgmr) by 2002:a5b:f02:: with SMTP id
 x2mr892065ybr.99.1620247343885;
 Wed, 05 May 2021 13:42:23 -0700 (PDT)
Reply-To: Sean Christopherson <seanjc@google.com>
Date: Wed,  5 May 2021 13:42:21 -0700
Message-Id: <20210505204221.1934471-1-seanjc@google.com>
Mime-Version: 1.0
X-Mailer: git-send-email 2.31.1.527.g47e6f16901-goog
Subject: [PATCH v2] KVM: x86: Prevent KVM SVM from loading on kernels with
 5-level paging
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

Disallow loading KVM SVM if 5-level paging is supported.  In theory, NPT
for L1 should simply work, but there unknowns with respect to how the
guest's MAXPHYADDR will be handled by hardware.

Nested NPT is more problematic, as running an L1 VMM that is using
2-level page tables requires stacking single-entry PDP and PML4 tables in
KVM's NPT for L2, as there are no equivalent entries in L1's NPT to
shadow.  Barring hardware magic, for 5-level paging, KVM would need stack
another layer to handle PML5.

Opportunistically rename the lm_root pointer, which is used for the
aforementioned stacking when shadowing 2-level L1 NPT, to pml4_root to
call out that it's specifically for PML4.

Suggested-by: Paolo Bonzini <pbonzini@redhat.com>
Signed-off-by: Sean Christopherson <seanjc@google.com>
---
 arch/x86/include/asm/kvm_host.h |  2 +-
 arch/x86/kvm/mmu/mmu.c          | 20 ++++++++++----------
 arch/x86/kvm/svm/svm.c          |  5 +++++
 3 files changed, 16 insertions(+), 11 deletions(-)

```
