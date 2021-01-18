#### [PATCH 1/3] vfio-pci: rename vfio_pci.c to vfio_pci_core.c
##### From: Max Gurtovoy <mgurtovoy@nvidia.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Max Gurtovoy <mgurtovoy@nvidia.com>
X-Patchwork-Id: 12025611
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-18.9 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_CR_TRAILER,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,
	USER_AGENT_GIT autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 02A10C433E6
	for <kvm@archiver.kernel.org>; Sun, 17 Jan 2021 18:16:42 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id B94242250F
	for <kvm@archiver.kernel.org>; Sun, 17 Jan 2021 18:16:41 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729914AbhAQSQe (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Sun, 17 Jan 2021 13:16:34 -0500
Received: from hqnvemgate26.nvidia.com ([216.228.121.65]:15749 "EHLO
        hqnvemgate26.nvidia.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1729632AbhAQSQY (ORCPT <rfc822;kvm@vger.kernel.org>);
        Sun, 17 Jan 2021 13:16:24 -0500
Received: from hqmail.nvidia.com (Not Verified[216.228.121.13]) by
 hqnvemgate26.nvidia.com (using TLS: TLSv1.2, AES256-SHA)
        id <B60047ed00000>; Sun, 17 Jan 2021 10:15:44 -0800
Received: from HQMAIL107.nvidia.com (172.20.187.13) by HQMAIL111.nvidia.com
 (172.20.187.18) with Microsoft SMTP Server (TLS) id 15.0.1473.3; Sun, 17 Jan
 2021 18:15:44 +0000
Received: from r-nvmx02.mtr.labs.mlnx (172.20.145.6) by mail.nvidia.com
 (172.20.187.13) with Microsoft SMTP Server id 15.0.1473.3 via Frontend
 Transport; Sun, 17 Jan 2021 18:15:39 +0000
From: Max Gurtovoy <mgurtovoy@nvidia.com>
To: <alex.williamson@redhat.com>, <cohuck@redhat.com>,
        <kvm@vger.kernel.org>, <linux-kernel@vger.kernel.org>
CC: <jgg@nvidia.com>, <liranl@nvidia.com>, <oren@nvidia.com>,
        <tzahio@nvidia.com>, <leonro@nvidia.com>, <yarong@nvidia.com>,
        <aviadye@nvidia.com>, <shahafs@nvidia.com>, <artemp@nvidia.com>,
        <kwankhede@nvidia.com>, <ACurrid@nvidia.com>, <gmataev@nvidia.com>,
        <cjia@nvidia.com>, Max Gurtovoy <mgurtovoy@nvidia.com>
Subject: [PATCH 1/3] vfio-pci: rename vfio_pci.c to vfio_pci_core.c
Date: Sun, 17 Jan 2021 18:15:32 +0000
Message-ID: <20210117181534.65724-2-mgurtovoy@nvidia.com>
X-Mailer: git-send-email 2.25.4
In-Reply-To: <20210117181534.65724-1-mgurtovoy@nvidia.com>
References: <20210117181534.65724-1-mgurtovoy@nvidia.com>
MIME-Version: 1.0
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=nvidia.com; s=n1;
        t=1610907344; bh=cD5IrQ+dWwGI6zYP21oJURgsVtNrdqC+pW+2KPZxPk0=;
        h=From:To:CC:Subject:Date:Message-ID:X-Mailer:In-Reply-To:
         References:MIME-Version:Content-Transfer-Encoding:Content-Type;
        b=O5keQLljnSCDfuYVscBGzc+8i6IiKyH7RKqG1DrJzkHWDP+6szGVd0S+ViCCUI6qW
         5GExHcid9awFF/b+6mcczz9AOMut6aJ4yytxx+qtZgxfEGiMNTEr8haKiwdMGQs70b
         gOdV2fSh5LZBax1sBmAGvyLvznlDJSlo2+B/6mxN7T9PcTwd2rZwUbTNJ10Iaedwlq
         Q5XnL2264yUI4u8si+ehQDbWJo1Niqsx2t5nWTrzO3vDQMQSdt+si5xSvx2O3z95+4
         SA8wHck2Jmt//eDFxgupmdza2n8gX4zR7BpQv3akM2LzrqHHJ5RkuWSLWbWvlhasIB
         DzkQ0VMS8LMeg==
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This is a preparation patch for separating the vfio_pci driver to a
subsystem driver and a generic pci driver. This patch doesn't change any
logic.

Signed-off-by: Max Gurtovoy <mgurtovoy@nvidia.com>
---
 drivers/vfio/pci/Makefile                        | 2 +-
 drivers/vfio/pci/{vfio_pci.c => vfio_pci_core.c} | 0
 2 files changed, 1 insertion(+), 1 deletion(-)
 rename drivers/vfio/pci/{vfio_pci.c => vfio_pci_core.c} (100%)

```
