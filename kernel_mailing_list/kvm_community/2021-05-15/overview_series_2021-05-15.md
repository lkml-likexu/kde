#### [PATCH 1/1] vfio/pci: Fix error return code in vfio_ecap_init()
##### From: Zhen Lei <thunder.leizhen@huawei.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Zhen Lei <thunder.leizhen@huawei.com>
X-Patchwork-Id: 12259351
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.8 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED,USER_AGENT_GIT
	autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 1B16BC433B4
	for <kvm@archiver.kernel.org>; Sat, 15 May 2021 02:05:18 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id DD42761350
	for <kvm@archiver.kernel.org>; Sat, 15 May 2021 02:05:17 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S231332AbhEOCG2 (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Fri, 14 May 2021 22:06:28 -0400
Received: from szxga05-in.huawei.com ([45.249.212.191]:2662 "EHLO
        szxga05-in.huawei.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S230146AbhEOCG2 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 14 May 2021 22:06:28 -0400
Received: from DGGEMS405-HUB.china.huawei.com (unknown [172.30.72.58])
        by szxga05-in.huawei.com (SkyGuard) with ESMTP id 4FhpY84lXMzPxd7;
        Sat, 15 May 2021 10:01:48 +0800 (CST)
Received: from thunder-town.china.huawei.com (10.174.177.72) by
 DGGEMS405-HUB.china.huawei.com (10.3.19.205) with Microsoft SMTP Server id
 14.3.498.0; Sat, 15 May 2021 10:05:05 +0800
From: Zhen Lei <thunder.leizhen@huawei.com>
To: Alex Williamson <alex.williamson@redhat.com>,
        Cornelia Huck <cohuck@redhat.com>, kvm <kvm@vger.kernel.org>
CC: Zhen Lei <thunder.leizhen@huawei.com>
Subject: [PATCH 1/1] vfio/pci: Fix error return code in vfio_ecap_init()
Date: Sat, 15 May 2021 10:04:58 +0800
Message-ID: <20210515020458.6771-1-thunder.leizhen@huawei.com>
X-Mailer: git-send-email 2.26.0.windows.1
MIME-Version: 1.0
X-Originating-IP: [10.174.177.72]
X-CFilter-Loop: Reflected
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The error code returned from vfio_ext_cap_len() is stored in 'len', not
in 'ret'.

Fixes: 89e1f7d4c66d ("vfio: Add PCI device driver")
Reported-by: Hulk Robot <hulkci@huawei.com>
Signed-off-by: Zhen Lei <thunder.leizhen@huawei.com>
---
 drivers/vfio/pci/vfio_pci_config.c | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```