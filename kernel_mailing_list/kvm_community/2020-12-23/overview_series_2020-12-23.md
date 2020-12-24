#### [PATCH kvm-unit-tests 1/4] libcflat: add a few more runtime functions
##### From: Paolo Bonzini <pbonzini@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Paolo Bonzini <pbonzini@redhat.com>
X-Patchwork-Id: 11987427
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.8 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT autolearn=ham
	autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 047A1C433E0
	for <kvm@archiver.kernel.org>; Wed, 23 Dec 2020 01:09:51 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id D540A225AC
	for <kvm@archiver.kernel.org>; Wed, 23 Dec 2020 01:09:50 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726408AbgLWBJf (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 22 Dec 2020 20:09:35 -0500
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:53350 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1725300AbgLWBJe (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 22 Dec 2020 20:09:34 -0500
Received: from mail-wr1-x42f.google.com (mail-wr1-x42f.google.com
 [IPv6:2a00:1450:4864:20::42f])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 61D9DC061793
        for <kvm@vger.kernel.org>; Tue, 22 Dec 2020 17:08:54 -0800 (PST)
Received: by mail-wr1-x42f.google.com with SMTP id 91so16938743wrj.7
        for <kvm@vger.kernel.org>; Tue, 22 Dec 2020 17:08:54 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=sender:from:to:cc:subject:date:message-id:in-reply-to:references
         :mime-version:content-transfer-encoding;
        bh=AELlSdlZPX/Uv45zWP6w9R8ftpPQUV4UnQSCu6+uF+8=;
        b=iJ5Lq6x5oXdPH/BMfQ4sZoNOlrdKRMJpI9JBsiIlij3bJheLzlzq/4kqbK/UYTYREN
         nPqFgiD6f7YUMY1+bpekRCna7wp2FTBNluFlRoMqGso6SV8RXKVK5+EsZifCaJTnsXH9
         o6zFYovJ6p4cGaf1K6ydfFX+y73ikQbNlMuq3xbmmoDWiQa6wstKW+i8Q/3b750iuapG
         Cx6Z9HMO6ttvjAGi1hY2sj0OkyBItKtFNavTuFrZuWtjAwZGwVG7B/13mJB9GRkxJi4W
         scMao0Krzku57Do854uSpeRK8gHIpxE5PcbTavk1EiFj+LiT2eTzOhplH28dXsWq2Anw
         68aw==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:sender:from:to:cc:subject:date:message-id
         :in-reply-to:references:mime-version:content-transfer-encoding;
        bh=AELlSdlZPX/Uv45zWP6w9R8ftpPQUV4UnQSCu6+uF+8=;
        b=KtaYgPhB9lEL4JM7PjBETxdY1ibjfgmuhY2kl76Du7HrDRzRdS4Mb6FxVHoaRhpwIC
         WoRgnuQG0QtQcsRkveAB6sEaBd7toAC7urecQflhLqc3e8nMJHIavu658yzAdS8rdlos
         eUnTmP7DG2Il7RTaMM+AlNL+8EJ/dxncOBenS3QU6tQK2zSgg55NeTogU79zhuEspr69
         O7aoEkZRdF0VNE4TEqPYt7YqJrEmb0zhfn/nfZXqM7BWGryRqhiLkmnstjDFpfCNt5QF
         eSQCn6HrdzO63YKmMCpMxuKcOmoD46K49OqbXJI/oHR2gAN4ClO5L8+R+SMB0x66vODe
         3iXA==
X-Gm-Message-State: AOAM530xn3D9gQkPhJMUtKnlHgF/t2RPaW2Dh3mTSbbxP3Kpyuvhxvv2
        +5J/PMVvuhWI+r6w3YD5OULaZOVcU80=
X-Google-Smtp-Source: 
 ABdhPJwP6r5DdIbENK4G0rivMdNV1Dxj2qYlxZH4ov4r14vc0sIodi+kIv5yNChc3aOOylLHD2YcBQ==
X-Received: by 2002:a5d:4641:: with SMTP id j1mr27013669wrs.94.1608685733191;
        Tue, 22 Dec 2020 17:08:53 -0800 (PST)
Received: from avogadro.lan ([2001:b07:6468:f312:5e2c:eb9a:a8b6:fd3e])
        by smtp.gmail.com with ESMTPSA id
 h83sm30995047wmf.9.2020.12.22.17.08.52
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Tue, 22 Dec 2020 17:08:52 -0800 (PST)
Sender: Paolo Bonzini <paolo.bonzini@gmail.com>
From: Paolo Bonzini <pbonzini@redhat.com>
To: kvm@vger.kernel.org
Cc: mlevitsk@redhat.com
Subject: [PATCH kvm-unit-tests 1/4] libcflat: add a few more runtime functions
Date: Wed, 23 Dec 2020 02:08:47 +0100
Message-Id: <20201223010850.111882-2-pbonzini@redhat.com>
X-Mailer: git-send-email 2.29.2
In-Reply-To: <20201223010850.111882-1-pbonzini@redhat.com>
References: <20201223010850.111882-1-pbonzini@redhat.com>
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

These functions will be used to parse the chaos test's command line.

Signed-off-by: Paolo Bonzini <pbonzini@redhat.com>
---
 lib/alloc.c    |  9 +++++++-
 lib/alloc.h    |  1 +
 lib/libcflat.h |  4 +++-
 lib/string.c   | 59 +++++++++++++++++++++++++++++++++++++++++++++++---
 lib/string.h   |  3 +++
 5 files changed, 71 insertions(+), 5 deletions(-)

```
#### [GIT PULL] virtio,vdpa: features, cleanups, fixes
##### From: "Michael S. Tsirkin" <mst@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: "Michael S. Tsirkin" <mst@redhat.com>
X-Patchwork-Id: 11988283
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-25.8 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_CR_TRAILER,INCLUDES_PATCH,INCLUDES_PULL_REQUEST,MAILING_LIST_MULTI,
	MENTIONS_GIT_HOSTING,SPF_HELO_NONE,SPF_PASS autolearn=unavailable
	autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 3DEECC433E6
	for <kvm@archiver.kernel.org>; Wed, 23 Dec 2020 12:26:30 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id E602E22473
	for <kvm@archiver.kernel.org>; Wed, 23 Dec 2020 12:26:29 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728518AbgLWM0Z (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Wed, 23 Dec 2020 07:26:25 -0500
Received: from us-smtp-delivery-124.mimecast.com ([216.205.24.124]:32392 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1726266AbgLWM0W (ORCPT
        <rfc822;kvm@vger.kernel.org>); Wed, 23 Dec 2020 07:26:22 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1608726295;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:content-type:content-type;
        bh=0UNmcgKiAU5Ao1EWHMSNYvqkNdmnpc0OSfrJWGti+po=;
        b=IMvFAIplD+9/ww8I4Sn0BBcHPG2FfLwLi9JKfObkZgNTje8HBy7yqraxJ9LUa2sMqPItEW
        Bf1S6XeWVnxko7TV6SpT266o187QpknzVkBCZET99SJKl+sZb3VVw9GJI4a+lTXf5H+6Zf
        IMsYbt+SAMaErZuALjzLCjT0KqvPFV0=
Received: from mail-wm1-f71.google.com (mail-wm1-f71.google.com
 [209.85.128.71]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-167-NOy3QOBwMyCsj6TKF-rshw-1; Wed, 23 Dec 2020 07:24:53 -0500
X-MC-Unique: NOy3QOBwMyCsj6TKF-rshw-1
Received: by mail-wm1-f71.google.com with SMTP id r5so3035516wma.2
        for <kvm@vger.kernel.org>; Wed, 23 Dec 2020 04:24:53 -0800 (PST)
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:date:from:to:cc:subject:message-id:mime-version
         :content-disposition;
        bh=0UNmcgKiAU5Ao1EWHMSNYvqkNdmnpc0OSfrJWGti+po=;
        b=rRCCVlNReyrnpXn5c3Vco/AjE8GRw9aNeqPLNsURQ7UbtkK5TyutJKMM40alByTrg9
         dIFX7RQUWWSb/efWRD0ct1E1fCXzNotuUR3WsGakZ9yYLdeJS8cVEqrkrWvv/172faq0
         UCCzyDs1uGptbjOvBoQ0Vj4viHbSuKgSQ6hkAg7m+CkOV3bxWlejxpxwELLi8pS7Nk8I
         9ipasGO7Z7/LZ14OZTvu66m8tiMu0WnTpDGBG5mwrSaLECejDT02adSYDOMTGoXy3uAM
         CnHPwwSqfa29AffWvnh+8tXX8LpQAW1bRxL1S2oOoyIa5Ak0b4++ve/rFTeEDuGEZaqG
         lfVA==
X-Gm-Message-State: AOAM531Gz2i1c/oEBzWfJkUIIxlyGMXvLTa1KzwmLo09p4CgqYqX1elH
        fExx2KEj4oEOGg50Rtat4mYjKXQ/F1Y/OLsoS9eWw4LJycjuo6ueDBYhC3ZMOCXg8g9X1FKS2jE
        kvPNrY84eQyxC
X-Received: by 2002:a5d:5181:: with SMTP id k1mr28572214wrv.226.1608726292504;
        Wed, 23 Dec 2020 04:24:52 -0800 (PST)
X-Google-Smtp-Source: 
 ABdhPJwnplIWRt16fzmwKMP8PwnlFgcdIWksMaeKxiGfFwfPmRzkFhUmLY7vWPm5sRt5yZ7jOcB35A==
X-Received: by 2002:a5d:5181:: with SMTP id k1mr28572175wrv.226.1608726292284;
        Wed, 23 Dec 2020 04:24:52 -0800 (PST)
Received: from redhat.com (bzq-79-178-32-166.red.bezeqint.net.
 [79.178.32.166])
        by smtp.gmail.com with ESMTPSA id
 z3sm36346271wrn.59.2020.12.23.04.24.49
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Wed, 23 Dec 2020 04:24:51 -0800 (PST)
Date: Wed, 23 Dec 2020 07:24:48 -0500
From: "Michael S. Tsirkin" <mst@redhat.com>
To: Linus Torvalds <torvalds@linux-foundation.org>
Cc: kvm@vger.kernel.org, virtualization@lists.linux-foundation.org,
        netdev@vger.kernel.org, linux-kernel@vger.kernel.org,
        akpm@linux-foundation.org, christophe.jaillet@wanadoo.fr,
        dan.carpenter@oracle.com, david@redhat.com, elic@nvidia.com,
        file@sect.tu-berlin.de, hulkci@huawei.com, info@metux.net,
        jasowang@redhat.com, mgurtovoy@nvidia.com, mhocko@kernel.org,
        mst@redhat.com, osalvador@suse.de, pankaj.gupta.linux@gmail.com,
        parav@nvidia.com, peng.fan@nxp.com,
        richard.weiyang@linux.alibaba.com, robert.buhren@sect.tu-berlin.de,
        sgarzare@redhat.com, tiantao6@hisilicon.com,
        zhangchangzhong@huawei.com
Subject: [GIT PULL] virtio,vdpa: features, cleanups, fixes
Message-ID: <20201223072448-mutt-send-email-mst@kernel.org>
MIME-Version: 1.0
Content-Disposition: inline
X-Mutt-Fcc: =sent
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The following changes since commit 2c85ebc57b3e1817b6ce1a6b703928e113a90442:

  Linux 5.10 (2020-12-13 14:41:30 -0800)

are available in the Git repository at:

  https://git.kernel.org/pub/scm/linux/kernel/git/mst/vhost.git tags/for_linus

for you to fetch changes up to 418eddef050d5f6393c303a94e3173847ab85466:

  vdpa: Use simpler version of ida allocation (2020-12-18 16:14:31 -0500)

----------------------------------------------------------------
virtio,vdpa: features, cleanups, fixes

vdpa sim refactoring
virtio mem  Big Block Mode support
misc cleanus, fixes

Signed-off-by: Michael S. Tsirkin <mst@redhat.com>

----------------------------------------------------------------
Christophe JAILLET (1):
      vdpa: ifcvf: Use dma_set_mask_and_coherent to simplify code

Dan Carpenter (3):
      virtio_ring: Cut and paste bugs in vring_create_virtqueue_packed()
      virtio_net: Fix error code in probe()
      virtio_ring: Fix two use after free bugs

David Hildenbrand (29):
      virtio-mem: determine nid only once using memory_add_physaddr_to_nid()
      virtio-mem: more precise calculation in virtio_mem_mb_state_prepare_next_mb()
      virtio-mem: simplify MAX_ORDER - 1 / pageblock_order handling
      virtio-mem: drop rc2 in virtio_mem_mb_plug_and_add()
      virtio-mem: use "unsigned long" for nr_pages when fake onlining/offlining
      virtio-mem: factor out calculation of the bit number within the subblock bitmap
      virtio-mem: print debug messages from virtio_mem_send_*_request()
      virtio-mem: factor out fake-offlining into virtio_mem_fake_offline()
      virtio-mem: factor out handling of fake-offline pages in memory notifier
      virtio-mem: retry fake-offlining via alloc_contig_range() on ZONE_MOVABLE
      virtio-mem: generalize check for added memory
      virtio-mem: generalize virtio_mem_owned_mb()
      virtio-mem: generalize virtio_mem_overlaps_range()
      virtio-mem: drop last_mb_id
      virtio-mem: don't always trigger the workqueue when offlining memory
      virtio-mem: generalize handling when memory is getting onlined deferred
      virito-mem: document Sub Block Mode (SBM)
      virtio-mem: memory block states are specific to Sub Block Mode (SBM)
      virito-mem: subblock states are specific to Sub Block Mode (SBM)
      virtio-mem: nb_sb_per_mb and subblock_size are specific to Sub Block Mode (SBM)
      virtio-mem: memory block ids are specific to Sub Block Mode (SBM)
      virito-mem: existing (un)plug functions are specific to Sub Block Mode (SBM)
      virtio-mem: memory notifier callbacks are specific to Sub Block Mode (SBM)
      virtio-mem: factor out adding/removing memory from Linux
      virtio-mem: Big Block Mode (BBM) memory hotplug
      virtio-mem: allow to force Big Block Mode (BBM) and set the big block size
      mm/memory_hotplug: extend offline_and_remove_memory() to handle more than one memory block
      virtio-mem: Big Block Mode (BBM) - basic memory hotunplug
      virtio-mem: Big Block Mode (BBM) - safe memory hotunplug

Eli Cohen (1):
      vdpa/mlx5: Use write memory barrier after updating CQ index

Enrico Weigelt, metux IT consult (2):
      uapi: virtio_ids.h: consistent indentions
      uapi: virtio_ids: add missing device type IDs from OASIS spec

Max Gurtovoy (2):
      vdpa_sim: remove hard-coded virtq count
      vdpa: split vdpasim to core and net modules

Parav Pandit (2):
      vdpa: Add missing comment for virtqueue count
      vdpa: Use simpler version of ida allocation

Peng Fan (3):
      tools/virtio: include asm/bug.h
      tools/virtio: add krealloc_array
      tools/virtio: add barrier for aarch64

Stefano Garzarella (16):
      vdpa: remove unnecessary 'default n' in Kconfig entries
      vdpa_sim: remove unnecessary headers inclusion
      vdpa_sim: make IOTLB entries limit configurable
      vdpa_sim: rename vdpasim_config_ops variables
      vdpa_sim: add struct vdpasim_dev_attr for device attributes
      vdpa_sim: add device id field in vdpasim_dev_attr
      vdpa_sim: add supported_features field in vdpasim_dev_attr
      vdpa_sim: add work_fn in vdpasim_dev_attr
      vdpa_sim: store parsed MAC address in a buffer
      vdpa_sim: make 'config' generic and usable for any device type
      vdpa_sim: add get_config callback in vdpasim_dev_attr
      vdpa_sim: add set_config callback in vdpasim_dev_attr
      vdpa_sim: set vringh notify callback
      vdpa_sim: use kvmalloc to allocate vdpasim->buffer
      vdpa_sim: make vdpasim->buffer size configurable
      vdpa_sim: split vdpasim_virtqueue's iov field in out_iov and in_iov

Tian Tao (1):
      vhost_vdpa: switch to vmemdup_user()

Zhang Changzhong (1):
      vhost scsi: fix error return code in vhost_scsi_set_endpoint()

 drivers/net/virtio_net.c             |    1 +
 drivers/vdpa/Kconfig                 |   18 +-
 drivers/vdpa/ifcvf/ifcvf_main.c      |   11 +-
 drivers/vdpa/mlx5/net/mlx5_vnet.c    |    5 +
 drivers/vdpa/vdpa.c                  |    2 +-
 drivers/vdpa/vdpa_sim/Makefile       |    1 +
 drivers/vdpa/vdpa_sim/vdpa_sim.c     |  298 ++----
 drivers/vdpa/vdpa_sim/vdpa_sim.h     |  105 ++
 drivers/vdpa/vdpa_sim/vdpa_sim_net.c |  177 ++++
 drivers/vhost/scsi.c                 |    3 +-
 drivers/vhost/vdpa.c                 |   10 +-
 drivers/virtio/virtio_mem.c          | 1835 ++++++++++++++++++++++++----------
 drivers/virtio/virtio_ring.c         |    8 +-
 include/linux/vdpa.h                 |    1 +
 include/uapi/linux/virtio_ids.h      |   44 +-
 mm/memory_hotplug.c                  |  109 +-
 tools/virtio/asm/barrier.h           |   10 +
 tools/virtio/linux/bug.h             |    2 +
 tools/virtio/linux/kernel.h          |   13 +-
 19 files changed, 1843 insertions(+), 810 deletions(-)
 create mode 100644 drivers/vdpa/vdpa_sim/vdpa_sim.h
 create mode 100644 drivers/vdpa/vdpa_sim/vdpa_sim_net.c
```
#### [PATCH] kvm: tracing: Fix unmatched kvm_entry and kvm_exit eventsFrom: Dario Faggioli <dfaggioli@suse.com>
##### From: Dario Faggioli <dfaggioli@suse.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Dario Faggioli <dfaggioli@suse.com>
X-Patchwork-Id: 11988413
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-13.7 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED autolearn=unavailable
	autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 90E98C433E0
	for <kvm@archiver.kernel.org>; Wed, 23 Dec 2020 14:46:10 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 589B9222B3
	for <kvm@archiver.kernel.org>; Wed, 23 Dec 2020 14:46:10 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726766AbgLWOpv (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Wed, 23 Dec 2020 09:45:51 -0500
Received: from mail-wr1-f41.google.com ([209.85.221.41]:43011 "EHLO
        mail-wr1-f41.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1725957AbgLWOpu (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 23 Dec 2020 09:45:50 -0500
Received: by mail-wr1-f41.google.com with SMTP id y17so18827568wrr.10;
        Wed, 23 Dec 2020 06:45:34 -0800 (PST)
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:subject:from:to:cc:date:message-id:user-agent
         :mime-version:content-transfer-encoding;
        bh=/RYWY/ozUzONgf/e8tkqi1F1m1XJVpNw0P3pUzv1ZE8=;
        b=X5+/Yo+mIvjsomxG9bItqm/LYiN44HTZO9dPshAARGhb2uaHn9Dj886EowJUeblVdO
         KyZ7r7j1VOdPEzfIlXofnyd9j+p+RNm4Ul/rrWV1On23LbCXoYsqXc71/3qh8+Ql5zZq
         2pIpVHRmanv4sCO3ezx05oYIA/5uTfN1pXrS9SLfcL+WXJuUrndEMs77ltqFSTxMhUoe
         KCiTKUzzav4Qd/OSqvE1ut7HO/NR2qgZxxTdLhvNpW3/ueLnUzRgdayfEmsYPvOCvb1U
         AtPqi6gTt9efY7myAbAwyhYvvCeMr/761eonzrBxf3piHMYJHquvhbLDZfE9Y+EG9rmH
         bYtA==
X-Gm-Message-State: AOAM533hKP7UfqqAwvcJlsuRN+4Fl/XgOVAPOxABhwVztAQ37SK5ngiv
        0jTt7X7gGc3KIKkQBtvFayc=
X-Google-Smtp-Source: 
 ABdhPJzooqwx43SF6qvhRQyu88Dxbeu+iMIJK0mMPr7+eYzTZFzd16bPD4io+4sIJ33XfsCrvRJk2A==
X-Received: by 2002:a5d:5385:: with SMTP id d5mr29641501wrv.384.1608734708673;
        Wed, 23 Dec 2020 06:45:08 -0800 (PST)
Received: from [127.0.1.1] (87.78.186.89.cust.ip.kpnqwest.it. [89.186.78.87])
        by smtp.gmail.com with ESMTPSA id h9sm46305wme.11.2020.12.23.06.45.07
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Wed, 23 Dec 2020 06:45:08 -0800 (PST)
Subject: [PATCH] kvm: tracing: Fix unmatched kvm_entry and kvm_exit events
From: Dario Faggioli <dfaggioli@suse.com>
To: linux-kernel@vger.kernel.org
Cc: Lorenzo Brescia <lorenzo.brescia@edu.unito.it>,
        Paolo Bonzini <pbonzini@redhat.com>,
        Sean Christopherson <seanjc@google.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>, kvm@vger.kernel.org,
        Lorenzo Brescia <lorenzo.brescia@edu.unito.it>
Date: Wed, 23 Dec 2020 14:45:07 +0000
Message-ID: <160873470698.11652.13483635328769030605.stgit@Wayrath>
User-Agent: StGit/0.23
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Lorenzo Brescia <lorenzo.brescia@edu.unito.it>

On VMX, if we exit and then re-enter immediately without leaving
the vmx_vcpu_run() function, the kvm_entry event is not logged.
That means we will see one (or more) kvm_exit, without its (their)
corresponding kvm_entry, as shown here:

 CPU-1979 [002] 89.871187: kvm_entry: vcpu 1
 CPU-1979 [002] 89.871218: kvm_exit:  reason MSR_WRITE
 CPU-1979 [002] 89.871259: kvm_exit:  reason MSR_WRITE

It also seems possible for a kvm_entry event to be logged, but then
we leave vmx_vcpu_run() right away (if vmx->emulation_required is
true). In this case, we will have a spurious kvm_entry event in the
trace.

Fix these situations by moving trace_kvm_entry() inside vmx_vcpu_run()
(where trace_kvm_exit() already is).

A trace obtained with this patch applied looks like this:

 CPU-14295 [000] 8388.395387: kvm_entry: vcpu 0
 CPU-14295 [000] 8388.395392: kvm_exit:  reason MSR_WRITE
 CPU-14295 [000] 8388.395393: kvm_entry: vcpu 0
 CPU-14295 [000] 8388.395503: kvm_exit:  reason EXTERNAL_INTERRUPT

Of course, not calling trace_kvm_entry() in common x86 code any
longer means that we need to adjust the SVM side of things too.

Signed-off-by: Lorenzo Brescia <lorenzo.brescia@edu.unito.it>
Signed-off-by: Dario Faggioli <dfaggioli@suse.com>
---
Cc: Paolo Bonzini <pbonzini@redhat.com>
Cc: Sean Christopherson <seanjc@google.com>
Cc: Vitaly Kuznetsov <vkuznets@redhat.com>
Cc: Wanpeng Li <wanpengli@tencent.com>
Cc: Jim Mattson <jmattson@google.com>
Cc: Joerg Roedel <joro@8bytes.org>
Cc: kvm@vger.kernel.org
Cc: Lorenzo Brescia <lorenzo.brescia@edu.unito.it>
Cc: Dario Faggioli <dfaggioli@suse.com>
---
 arch/x86/kvm/svm/svm.c |    2 ++
 arch/x86/kvm/vmx/vmx.c |    2 ++
 arch/x86/kvm/x86.c     |    3 +--
 3 files changed, 5 insertions(+), 2 deletions(-)

```
#### [PATCH v13 01/15] s390/vfio-ap: clean up vfio_ap resources when KVM pointer invalidated
##### From: Tony Krowiak <akrowiak@linux.ibm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Tony Krowiak <akrowiak@linux.ibm.com>
X-Patchwork-Id: 11987463
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.8 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT
	autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 28F8EC433E6
	for <kvm@archiver.kernel.org>; Wed, 23 Dec 2020 01:18:37 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 0027020C56
	for <kvm@archiver.kernel.org>; Wed, 23 Dec 2020 01:18:36 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727702AbgLWBSZ (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 22 Dec 2020 20:18:25 -0500
Received: from mx0a-001b2d01.pphosted.com ([148.163.156.1]:17034 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1726846AbgLWBRA (ORCPT
        <rfc822;kvm@vger.kernel.org>); Tue, 22 Dec 2020 20:17:00 -0500
Received: from pps.filterd (m0187473.ppops.net [127.0.0.1])
        by mx0a-001b2d01.pphosted.com (8.16.0.42/8.16.0.42) with SMTP id
 0BN11w6A121358;
        Tue, 22 Dec 2020 20:16:18 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=ibm.com;
 h=from : to : cc : subject
 : date : message-id : in-reply-to : references : mime-version :
 content-transfer-encoding; s=pp1;
 bh=D+EFG/gc3p78ZE8Oc9NsUtkZSWv2wrbRfIoTzSXMAds=;
 b=a7Ao4i4onqPbViwfp5UORPnP5j7hJqJhWigYonOr+WyvHJE+LMSoUs5crV9t86l263Vb
 sq/yj6v2/J+hgnRz4BWssKGOaIBzVvZF6Jm3iYkweOKxUWs+FOKAvehjIGMg59zuEIuD
 /LSdKO1tHOCPZ/qW8Z2XszuHZDh2WDgFIRyFZ1ESEMZLFElI4IGOZH3dL3sdx8bcXf7M
 JRs8c/z1ysMZcpVUFRx4iyilDerTcAenZ07+Vps+bQe+ux9JrxUNSKE197FGGd/DKBds
 YYHbRegGtxodLkDEwQur9S/4IjbTHkrrRqpPBN8PC8mJW9cRn/2J9F7GvnzXZphwNVMA yA==
Received: from pps.reinject (localhost [127.0.0.1])
        by mx0a-001b2d01.pphosted.com with ESMTP id 35kuk5rk71-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Tue, 22 Dec 2020 20:16:17 -0500
Received: from m0187473.ppops.net (m0187473.ppops.net [127.0.0.1])
        by pps.reinject (8.16.0.36/8.16.0.36) with SMTP id 0BN12A32121749;
        Tue, 22 Dec 2020 20:16:17 -0500
Received: from ppma05wdc.us.ibm.com (1b.90.2fa9.ip4.static.sl-reverse.com
 [169.47.144.27])
        by mx0a-001b2d01.pphosted.com with ESMTP id 35kuk5rk6q-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Tue, 22 Dec 2020 20:16:17 -0500
Received: from pps.filterd (ppma05wdc.us.ibm.com [127.0.0.1])
        by ppma05wdc.us.ibm.com (8.16.0.42/8.16.0.42) with SMTP id
 0BN1BP8U028172;
        Wed, 23 Dec 2020 01:16:16 GMT
Received: from b01cxnp23032.gho.pok.ibm.com (b01cxnp23032.gho.pok.ibm.com
 [9.57.198.27])
        by ppma05wdc.us.ibm.com with ESMTP id 35kfercjd9-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Wed, 23 Dec 2020 01:16:16 +0000
Received: from b01ledav004.gho.pok.ibm.com (b01ledav004.gho.pok.ibm.com
 [9.57.199.109])
        by b01cxnp23032.gho.pok.ibm.com (8.14.9/8.14.9/NCO v10.0) with ESMTP
 id 0BN1GElP11731450
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Wed, 23 Dec 2020 01:16:14 GMT
Received: from b01ledav004.gho.pok.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 3C0E7112067;
        Wed, 23 Dec 2020 01:16:14 +0000 (GMT)
Received: from b01ledav004.gho.pok.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 571DB112064;
        Wed, 23 Dec 2020 01:16:13 +0000 (GMT)
Received: from cpe-66-24-58-13.stny.res.rr.com.com (unknown [9.85.193.150])
        by b01ledav004.gho.pok.ibm.com (Postfix) with ESMTP;
        Wed, 23 Dec 2020 01:16:13 +0000 (GMT)
From: Tony Krowiak <akrowiak@linux.ibm.com>
To: linux-s390@vger.kernel.org, linux-kernel@vger.kernel.org,
        kvm@vger.kernel.org
Cc: freude@linux.ibm.com, borntraeger@de.ibm.com, cohuck@redhat.com,
        mjrosato@linux.ibm.com, pasic@linux.ibm.com,
        alex.williamson@redhat.com, kwankhede@nvidia.com,
        fiuczy@linux.ibm.com, frankja@linux.ibm.com, david@redhat.com,
        hca@linux.ibm.com, gor@linux.ibm.com,
        Tony Krowiak <akrowiak@linux.ibm.com>, stable@vger.kernel.org
Subject: [PATCH v13 01/15] s390/vfio-ap: clean up vfio_ap resources when KVM
 pointer invalidated
Date: Tue, 22 Dec 2020 20:15:52 -0500
Message-Id: <20201223011606.5265-2-akrowiak@linux.ibm.com>
X-Mailer: git-send-email 2.21.1
In-Reply-To: <20201223011606.5265-1-akrowiak@linux.ibm.com>
References: <20201223011606.5265-1-akrowiak@linux.ibm.com>
MIME-Version: 1.0
X-TM-AS-GCONF: 00
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.343,18.0.737
 definitions=2020-12-22_13:2020-12-21,2020-12-22 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 mlxscore=0 priorityscore=1501
 phishscore=0 suspectscore=0 adultscore=0 impostorscore=0 clxscore=1015
 bulkscore=0 malwarescore=0 mlxlogscore=999 spamscore=0 lowpriorityscore=0
 classifier=spam adjust=0 reason=mlx scancount=1 engine=8.12.0-2009150000
 definitions=main-2012230003
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The vfio_ap device driver registers a group notifier with VFIO when the
file descriptor for a VFIO mediated device for a KVM guest is opened to
receive notification that the KVM pointer is set (VFIO_GROUP_NOTIFY_SET_KVM
event). When the KVM pointer is set, the vfio_ap driver takes the
following actions:
1. Stashes the KVM pointer in the vfio_ap_mdev struct that holds the state
   of the mediated device.
2. Calls the kvm_get_kvm() function to increment its reference counter.
3. Sets the function pointer to the function that handles interception of
   the instruction that enables/disables interrupt processing.
4. Sets the masks in the KVM guest's CRYCB to pass AP resources through to
   the guest.

In order to avoid memory leaks, when the notifier is called to receive
notification that the KVM pointer has been set to NULL, the vfio_ap device
driver should reverse the actions taken when the KVM pointer was set.

Fixes: 258287c994de ("s390: vfio-ap: implement mediated device open callback")
Cc: stable@vger.kernel.org
Signed-off-by: Tony Krowiak <akrowiak@linux.ibm.com>
Reviewed-by: Halil Pasic <pasic@linux.ibm.com>
Reviewed-by: Cornelia Huck <cohuck@redhat.com>
---
 drivers/s390/crypto/vfio_ap_ops.c | 49 ++++++++++++++++++-------------
 1 file changed, 28 insertions(+), 21 deletions(-)

```
#### [PATCH v2] vhost/vsock: add IOTLB API support
##### From: Stefano Garzarella <sgarzare@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Stefano Garzarella <sgarzare@redhat.com>
X-Patchwork-Id: 11988405
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-15.8 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_CR_TRAILER,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,
	URIBL_BLOCKED autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 4B98AC433E6
	for <kvm@archiver.kernel.org>; Wed, 23 Dec 2020 14:38:36 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 0797622482
	for <kvm@archiver.kernel.org>; Wed, 23 Dec 2020 14:38:36 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727398AbgLWOiW (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Wed, 23 Dec 2020 09:38:22 -0500
Received: from us-smtp-delivery-124.mimecast.com ([63.128.21.124]:44354 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1727057AbgLWOiV (ORCPT
        <rfc822;kvm@vger.kernel.org>); Wed, 23 Dec 2020 09:38:21 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1608734214;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=dUU452tRqrvkfJMA+eezzExr3vkzl56EFOyXCB1EYnQ=;
        b=a1b1xHrxsAMK8QHX84bbO0Rm/rugtYM5L0++KkLEWxnRJQGevMDsqaSJWlYUqSWyp5oQHO
        b6TKsv7Azk50qmMcHT752t9abeCokTdGbGDt1NXd7ISr4xgKgT0Gxrf71HHHGaQn81Su3G
        E9yXAwrs8xdj4YwstOQh5kjTxw+5uHE=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-462--u0xtbG2N-2sRj1vrceUuw-1; Wed, 23 Dec 2020 09:36:49 -0500
X-MC-Unique: -u0xtbG2N-2sRj1vrceUuw-1
Received: from smtp.corp.redhat.com (int-mx03.intmail.prod.int.phx2.redhat.com
 [10.5.11.13])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 9091E180A097;
        Wed, 23 Dec 2020 14:36:48 +0000 (UTC)
Received: from steredhat.redhat.com (ovpn-112-247.ams2.redhat.com
 [10.36.112.247])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 89294614F5;
        Wed, 23 Dec 2020 14:36:39 +0000 (UTC)
From: Stefano Garzarella <sgarzare@redhat.com>
To: virtualization@lists.linux-foundation.org
Cc: netdev@vger.kernel.org, Jason Wang <jasowang@redhat.com>,
        "Michael S. Tsirkin" <mst@redhat.com>,
        Stefano Garzarella <sgarzare@redhat.com>,
        linux-kernel@vger.kernel.org, kvm@vger.kernel.org,
        Stefan Hajnoczi <stefanha@redhat.com>
Subject: [PATCH v2] vhost/vsock: add IOTLB API support
Date: Wed, 23 Dec 2020 15:36:38 +0100
Message-Id: <20201223143638.123417-1-sgarzare@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.13
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This patch enables the IOTLB API support for vhost-vsock devices,
allowing the userspace to emulate an IOMMU for the guest.

These changes were made following vhost-net, in details this patch:
- exposes VIRTIO_F_ACCESS_PLATFORM feature and inits the iotlb
  device if the feature is acked
- implements VHOST_GET_BACKEND_FEATURES and
  VHOST_SET_BACKEND_FEATURES ioctls
- calls vq_meta_prefetch() before vq processing to prefetch vq
  metadata address in IOTLB
- provides .read_iter, .write_iter, and .poll callbacks for the
  chardev; they are used by the userspace to exchange IOTLB messages

This patch was tested specifying "intel_iommu=strict" in the guest
kernel command line. I used QEMU with a patch applied [1] to fix a
simple issue (that patch was merged in QEMU v5.2.0):
    $ qemu -M q35,accel=kvm,kernel-irqchip=split \
           -drive file=fedora.qcow2,format=qcow2,if=virtio \
           -device intel-iommu,intremap=on,device-iotlb=on \
           -device vhost-vsock-pci,guest-cid=3,iommu_platform=on,ats=on

[1] https://lists.gnu.org/archive/html/qemu-devel/2020-10/msg09077.html

Reviewed-by: Stefan Hajnoczi <stefanha@redhat.com>
Signed-off-by: Stefano Garzarella <sgarzare@redhat.com>
---

The patch is the same of v1, but I re-tested it with:
- QEMU v5.2.0-551-ga05f8ecd88
- Linux 5.9.15 (host)
- Linux 5.9.15 and 5.10.0 (guest)
Now, enabling 'ats' it works well, there are just a few simple changes.

v1: https://www.spinics.net/lists/kernel/msg3716022.html
v2:
- updated commit message about QEMU version and string used to test
- rebased on mst/vhost branch

Thanks,
Stefano
---
 drivers/vhost/vsock.c | 68 +++++++++++++++++++++++++++++++++++++++++--
 1 file changed, 65 insertions(+), 3 deletions(-)

```
#### [PATCH v3 01/21] x86/fpu/xstate: Modify initialization helper to handle both static and dynamic buffers
##### From: "Chang S. Bae" <chang.seok.bae@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: "Chang S. Bae" <chang.seok.bae@intel.com>
X-Patchwork-Id: 11988643
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.7 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED,USER_AGENT_GIT
	autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id A6A12C433E0
	for <kvm@archiver.kernel.org>; Wed, 23 Dec 2020 16:03:03 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 760DD22202
	for <kvm@archiver.kernel.org>; Wed, 23 Dec 2020 16:03:03 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728288AbgLWQCV (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Wed, 23 Dec 2020 11:02:21 -0500
Received: from mga12.intel.com ([192.55.52.136]:48944 "EHLO mga12.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726530AbgLWQCV (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 23 Dec 2020 11:02:21 -0500
IronPort-SDR: 
 xwPoBGWUZg2XWyLc25EGuOL4XI1mAGujOo/cUeIlvQhhEUaGplyCUM9cgSC6Y5LFmvZ4ei1XhT
 6peyrNV/QeCw==
X-IronPort-AV: E=McAfee;i="6000,8403,9844"; a="155241856"
X-IronPort-AV: E=Sophos;i="5.78,441,1599548400";
   d="scan'208";a="155241856"
Received: from fmsmga001.fm.intel.com ([10.253.24.23])
  by fmsmga106.fm.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 23 Dec 2020 08:01:37 -0800
IronPort-SDR: 
 Mouh5E+8HOjAMqrxrMRKi6kf4ZFpIpLUSQU+JXkzXANvLmiTHpGqkgH9f076/94FMfNFRDwRBC
 1D0GMurdWzkw==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.78,441,1599548400";
   d="scan'208";a="458027907"
Received: from chang-linux-3.sc.intel.com ([172.25.66.175])
  by fmsmga001.fm.intel.com with ESMTP; 23 Dec 2020 08:01:36 -0800
From: "Chang S. Bae" <chang.seok.bae@intel.com>
To: bp@suse.de, luto@kernel.org, tglx@linutronix.de, mingo@kernel.org,
        x86@kernel.org
Cc: len.brown@intel.com, dave.hansen@intel.com, jing2.liu@intel.com,
        ravi.v.shankar@intel.com, linux-kernel@vger.kernel.org,
        chang.seok.bae@intel.com, kvm@vger.kernel.org
Subject: [PATCH v3 01/21] x86/fpu/xstate: Modify initialization helper to
 handle both static and dynamic buffers
Date: Wed, 23 Dec 2020 07:56:57 -0800
Message-Id: <20201223155717.19556-2-chang.seok.bae@intel.com>
X-Mailer: git-send-email 2.17.1
In-Reply-To: <20201223155717.19556-1-chang.seok.bae@intel.com>
References: <20201223155717.19556-1-chang.seok.bae@intel.com>
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

In preparation for dynamic xstate buffer expansion, update the buffer
initialization function parameters to equally handle static in-line xstate
buffer, as well as dynamically allocated xstate buffer.

init_fpstate is a special case, which is indicated by a null pointer
parameter to fpstate_init().

Also, fpstate_init_xstate() now accepts the state component bitmap to
configure XCOMP_BV for the compacted format.

No functional change.

Signed-off-by: Chang S. Bae <chang.seok.bae@intel.com>
Reviewed-by: Len Brown <len.brown@intel.com>
Cc: x86@kernel.org
Cc: linux-kernel@vger.kernel.org
Cc: kvm@vger.kernel.org
---
Changes from v2:
* Updated the changelog with task->fpu removed. (Boris Petkov)
---
 arch/x86/include/asm/fpu/internal.h |  6 +++---
 arch/x86/kernel/fpu/core.c          | 14 +++++++++++---
 arch/x86/kernel/fpu/init.c          |  2 +-
 arch/x86/kernel/fpu/regset.c        |  2 +-
 arch/x86/kernel/fpu/xstate.c        |  3 +--
 arch/x86/kvm/x86.c                  |  2 +-
 6 files changed, 18 insertions(+), 11 deletions(-)

```
#### [PATCH v5] s390/vfio-ap: clean up vfio_ap resources when KVM pointer invalidated
##### From: Tony Krowiak <akrowiak@linux.ibm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Tony Krowiak <akrowiak@linux.ibm.com>
X-Patchwork-Id: 11987467
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.8 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT
	autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id DBC79C433E0
	for <kvm@archiver.kernel.org>; Wed, 23 Dec 2020 01:21:27 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id AA3EE22287
	for <kvm@archiver.kernel.org>; Wed, 23 Dec 2020 01:21:27 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727211AbgLWBVI (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 22 Dec 2020 20:21:08 -0500
Received: from mx0a-001b2d01.pphosted.com ([148.163.156.1]:3644 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1726514AbgLWBVH (ORCPT
        <rfc822;kvm@vger.kernel.org>); Tue, 22 Dec 2020 20:21:07 -0500
Received: from pps.filterd (m0098404.ppops.net [127.0.0.1])
        by mx0a-001b2d01.pphosted.com (8.16.0.42/8.16.0.42) with SMTP id
 0BN13OVN186260;
        Tue, 22 Dec 2020 20:20:24 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=ibm.com;
 h=from : to : cc : subject
 : date : message-id : mime-version : content-transfer-encoding; s=pp1;
 bh=D+EFG/gc3p78ZE8Oc9NsUtkZSWv2wrbRfIoTzSXMAds=;
 b=oXmZhCspfvG0uyTwNozePbIlXP/eYeeyQrX5veLysnTffU4pL4EXA510xaRgpdEWTaR0
 yL8Lcu0TQH+a/X1xoirgn73PO4Vii40Ll15usmWjb0KXL/DUdmdkrnA0+ODqzNPVASid
 I24kdVovMP3/p6T8bhNYKRR8bDpFXVChuFCuYIc3QLNSkP60bmzUNYP6pp3N6uIIWGPd
 kprGitm1GTvW06UxNv6pJAlDGhBnF0GoDSrvzaLXhHAi0znS65+r8vu1i/fqIxI4288d
 aBkfYYhjAhhrDDDdXCce7y4JyiUizbwGtTBTPQ/aP9e2Dq0zVK16LL676pCwAXBzp1mt EQ==
Received: from pps.reinject (localhost [127.0.0.1])
        by mx0a-001b2d01.pphosted.com with ESMTP id 35ku7ts4qf-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Tue, 22 Dec 2020 20:20:24 -0500
Received: from m0098404.ppops.net (m0098404.ppops.net [127.0.0.1])
        by pps.reinject (8.16.0.36/8.16.0.36) with SMTP id 0BN1KEM4088148;
        Tue, 22 Dec 2020 20:20:24 -0500
Received: from ppma03dal.us.ibm.com (b.bd.3ea9.ip4.static.sl-reverse.com
 [169.62.189.11])
        by mx0a-001b2d01.pphosted.com with ESMTP id 35ku7ts4q8-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Tue, 22 Dec 2020 20:20:24 -0500
Received: from pps.filterd (ppma03dal.us.ibm.com [127.0.0.1])
        by ppma03dal.us.ibm.com (8.16.0.42/8.16.0.42) with SMTP id
 0BN1DETt000491;
        Wed, 23 Dec 2020 01:20:23 GMT
Received: from b03cxnp08026.gho.boulder.ibm.com
 (b03cxnp08026.gho.boulder.ibm.com [9.17.130.18])
        by ppma03dal.us.ibm.com with ESMTP id 35k02ev7r0-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Wed, 23 Dec 2020 01:20:23 +0000
Received: from b03ledav002.gho.boulder.ibm.com
 (b03ledav002.gho.boulder.ibm.com [9.17.130.233])
        by b03cxnp08026.gho.boulder.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id 0BN1KLkC22020606
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Wed, 23 Dec 2020 01:20:21 GMT
Received: from b03ledav002.gho.boulder.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 96F7E13604F;
        Wed, 23 Dec 2020 01:20:21 +0000 (GMT)
Received: from b03ledav002.gho.boulder.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 15424136051;
        Wed, 23 Dec 2020 01:20:19 +0000 (GMT)
Received: from cpe-66-24-58-13.stny.res.rr.com.com (unknown [9.85.193.150])
        by b03ledav002.gho.boulder.ibm.com (Postfix) with ESMTP;
        Wed, 23 Dec 2020 01:20:19 +0000 (GMT)
From: Tony Krowiak <akrowiak@linux.ibm.com>
To: linux-s390@vger.kernel.org, linux-kernel@vger.kernel.org,
        kvm@vger.kernel.org
Cc: stable@vger.kernel.org, borntraeger@de.ibm.com, cohuck@redhat.com,
        kwankhede@nvidia.com, pbonzini@redhat.com,
        alex.williamson@redhat.com, pasic@linux.vnet.ibm.com,
        Tony Krowiak <akrowiak@linux.ibm.com>,
        Halil Pasic <pasic@linux.ibm.com>
Subject: [PATCH v5] s390/vfio-ap: clean up vfio_ap resources when KVM pointer
 invalidated
Date: Tue, 22 Dec 2020 20:20:13 -0500
Message-Id: <20201223012013.5418-1-akrowiak@linux.ibm.com>
X-Mailer: git-send-email 2.21.1
MIME-Version: 1.0
X-TM-AS-GCONF: 00
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.343,18.0.737
 definitions=2020-12-22_13:2020-12-21,2020-12-22 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 malwarescore=0 bulkscore=0
 impostorscore=0 priorityscore=1501 mlxscore=0 phishscore=0 spamscore=0
 lowpriorityscore=0 suspectscore=0 clxscore=1015 mlxlogscore=999
 adultscore=0 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.12.0-2009150000 definitions=main-2012230007
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The vfio_ap device driver registers a group notifier with VFIO when the
file descriptor for a VFIO mediated device for a KVM guest is opened to
receive notification that the KVM pointer is set (VFIO_GROUP_NOTIFY_SET_KVM
event). When the KVM pointer is set, the vfio_ap driver takes the
following actions:
1. Stashes the KVM pointer in the vfio_ap_mdev struct that holds the state
   of the mediated device.
2. Calls the kvm_get_kvm() function to increment its reference counter.
3. Sets the function pointer to the function that handles interception of
   the instruction that enables/disables interrupt processing.
4. Sets the masks in the KVM guest's CRYCB to pass AP resources through to
   the guest.

In order to avoid memory leaks, when the notifier is called to receive
notification that the KVM pointer has been set to NULL, the vfio_ap device
driver should reverse the actions taken when the KVM pointer was set.

Fixes: 258287c994de ("s390: vfio-ap: implement mediated device open callback")
Cc: stable@vger.kernel.org
Signed-off-by: Tony Krowiak <akrowiak@linux.ibm.com>
Reviewed-by: Halil Pasic <pasic@linux.ibm.com>
Reviewed-by: Cornelia Huck <cohuck@redhat.com>
---
 drivers/s390/crypto/vfio_ap_ops.c | 49 ++++++++++++++++++-------------
 1 file changed, 28 insertions(+), 21 deletions(-)

```
