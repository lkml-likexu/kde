#### [PATCH] vhost: new vhost_vdpa SET/GET_BACKEND_FEATURES handlers
##### From: Zhu Lingshan <lingshan.zhu@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Zhu Lingshan <lingshan.zhu@intel.com>
X-Patchwork-Id: 11764813
Return-Path: <SRS0=11Di=CS=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 23E44159A
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed,  9 Sep 2020 02:26:40 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 14AF52080C
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed,  9 Sep 2020 02:26:39 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726708AbgIIC0h (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 8 Sep 2020 22:26:37 -0400
Received: from mga09.intel.com ([134.134.136.24]:40167 "EHLO mga09.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1725997AbgIIC0f (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 8 Sep 2020 22:26:35 -0400
IronPort-SDR: 
 JqoNHJQkrgldhEPYOn1nUJ4GcrlrlXHA87Gh+99MgZQJeQ5wD3derW64pkW5SyxOQ68yyEJyOE
 YC9EHye41B4w==
X-IronPort-AV: E=McAfee;i="6000,8403,9738"; a="159223259"
X-IronPort-AV: E=Sophos;i="5.76,408,1592895600";
   d="scan'208";a="159223259"
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from orsmga007.jf.intel.com ([10.7.209.58])
  by orsmga102.jf.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 08 Sep 2020 19:26:34 -0700
IronPort-SDR: 
 GBf2UqYhYYp0JBGU6H3PM87EBjBkQQT77Sf9gref8cx5V8J9in/KyGydAqmqURh8KrQqWMZ3E3
 edzZkUVu5/+Q==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.76,408,1592895600";
   d="scan'208";a="343745815"
Received: from unknown (HELO localhost.localdomain.bj.intel.com)
 ([10.240.192.131])
  by orsmga007.jf.intel.com with ESMTP; 08 Sep 2020 19:26:32 -0700
From: Zhu Lingshan <lingshan.zhu@intel.com>
To: jasowang@redhat.com, mst@redhat.com
Cc: virtualization@lists.linux-foundation.org, netdev@vger.kernel.org,
        kvm@vger.kernel.org, Zhu Lingshan <lingshan.zhu@intel.com>
Subject: [PATCH] vhost: new vhost_vdpa SET/GET_BACKEND_FEATURES handlers
Date: Wed,  9 Sep 2020 10:22:33 +0800
Message-Id: <20200909022233.26559-1-lingshan.zhu@intel.com>
X-Mailer: git-send-email 2.18.4
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This commit introduced vhost_vdpa_set/get_backend_features() to
resolve these issues:
(1)In vhost_vdpa ioctl SET_BACKEND_FEATURES path, currect code
would try to acquire vhost dev mutex twice
(first shown in vhost_vdpa_unlocked_ioctl), which can lead
to a dead lock issue.
(2)SET_BACKEND_FEATURES was blindly added to vring ioctl instead
of vdpa device ioctl

To resolve these issues, this commit (1)removed mutex operations
in vhost_set_backend_features. (2)Handle ioctl
SET/GET_BACKEND_FEATURES in vdpa ioctl. (3)introduce a new
function vhost_net_set_backend_features() for vhost_net,
which is a wrap of vhost_set_backend_features() with
necessary mutex lockings.

Signed-off-by: Zhu Lingshan <lingshan.zhu@intel.com>
Reported-by: kernel test robot <lkp@intel.com>
Reported-by: Dan Carpenter <dan.carpenter@oracle.com>
---
 drivers/vhost/net.c   |  9 ++++++++-
 drivers/vhost/vdpa.c  | 47 ++++++++++++++++++++++++++++++-------------
 drivers/vhost/vhost.c |  2 --
 3 files changed, 41 insertions(+), 17 deletions(-)

```
