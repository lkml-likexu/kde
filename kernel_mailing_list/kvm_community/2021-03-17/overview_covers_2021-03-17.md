

#### [PATCH V5 0/7] vDPA/ifcvf: enables Intel C5000X-PL virtio-net
##### From: Zhu Lingshan <lingshan.zhu@intel.com>

```c
From patchwork Wed Mar 17 09:49:26 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Zhu Lingshan <lingshan.zhu@intel.com>
X-Patchwork-Id: 12145335
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-11.8 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,
	SPF_PASS,USER_AGENT_GIT autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 6252CC433E6
	for <kvm@archiver.kernel.org>; Wed, 17 Mar 2021 09:55:27 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 3845064F5E
	for <kvm@archiver.kernel.org>; Wed, 17 Mar 2021 09:55:27 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S229884AbhCQJyx (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Wed, 17 Mar 2021 05:54:53 -0400
Received: from mga04.intel.com ([192.55.52.120]:59767 "EHLO mga04.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S229586AbhCQJyl (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 17 Mar 2021 05:54:41 -0400
IronPort-SDR: 
 deuPt+obzUFVz3XhYm6O11mneqHvhUTNPFzQu2ANkvDNVr9KKGrATXS+/hOLD5uxwRR54uIU4L
 jG74pNZ7gcQA==
X-IronPort-AV: E=McAfee;i="6000,8403,9925"; a="187058661"
X-IronPort-AV: E=Sophos;i="5.81,255,1610438400";
   d="scan'208";a="187058661"
Received: from fmsmga008.fm.intel.com ([10.253.24.58])
  by fmsmga104.fm.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 17 Mar 2021 02:54:41 -0700
IronPort-SDR: 
 5UD5xcdaGjl4HxotJBd33KN+iGROrob9MWZhprZA1dFfqmWZPfKEP6yr/4wClSzymoKktofD17
 xfDTy1y84wiw==
X-IronPort-AV: E=Sophos;i="5.81,255,1610438400";
   d="scan'208";a="405873165"
Received: from unknown (HELO localhost.localdomain.bj.intel.com)
 ([10.240.193.73])
  by fmsmga008-auth.fm.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 17 Mar 2021 02:54:39 -0700
From: Zhu Lingshan <lingshan.zhu@intel.com>
To: jasowang@redhat.com, mst@redhat.com, lulu@redhat.com,
        leonro@nvidia.com
Cc: virtualization@lists.linux-foundation.org, netdev@vger.kernel.org,
        kvm@vger.kernel.org, linux-kernel@vger.kernel.org,
        Zhu Lingshan <lingshan.zhu@intel.com>
Subject: [PATCH V5 0/7] vDPA/ifcvf: enables Intel C5000X-PL virtio-net
Date: Wed, 17 Mar 2021 17:49:26 +0800
Message-Id: <20210317094933.16417-1-lingshan.zhu@intel.com>
X-Mailer: git-send-email 2.27.0
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This series enabled Intel FGPA SmartNIC C5000X-PL virtio-net for vDPA.

vDPA requires VIRTIO_F_ACCESS_PLATFORM as a must,
this series verify this feature bit when set features.

Changes from V4:
deduce VIRTIO device ID from pdev device id or subsystem
device id(Jason)

Changes from V3:
checks features to set in verify_min_features(Jason)
deduce VIRTIO device ID from pdev ids in get_device_id(Jason)

Changes from V2:
verify VIRTIO_F_ACCESS_PLATFORM when set features(Jason)

Changes from V1:
remove version number string(Leon)
add new device ids and remove original device ids
in separate patches(Jason)

Zhu Lingshan (7):
  vDPA/ifcvf: get_vendor_id returns a device specific vendor id
  vDPA/ifcvf: enable Intel C5000X-PL virtio-net for vDPA
  vDPA/ifcvf: rename original IFCVF dev ids to N3000 ids
  vDPA/ifcvf: remove the version number string
  vDPA/ifcvf: fetch device feature bits when probe
  vDPA/ifcvf: verify mandatory feature bits for vDPA
  vDPA/ifcvf: deduce VIRTIO device ID from pdev ids

 drivers/vdpa/ifcvf/ifcvf_base.c | 24 +++++++++++++++++--
 drivers/vdpa/ifcvf/ifcvf_base.h | 17 ++++++++++----
 drivers/vdpa/ifcvf/ifcvf_main.c | 41 ++++++++++++++++++++++++++-------
 3 files changed, 68 insertions(+), 14 deletions(-)
```