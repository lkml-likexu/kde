#### [PATCH 1/3] virtio: update reset callback to return status
##### From: Max Gurtovoy <mgurtovoy@nvidia.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Max Gurtovoy <mgurtovoy@nvidia.com>
X-Patchwork-Id: 12187925
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-18.8 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_CR_TRAILER,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,
	URIBL_BLOCKED,USER_AGENT_GIT autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 8FB59C433ED
	for <kvm@archiver.kernel.org>; Wed,  7 Apr 2021 12:09:37 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 57001610FB
	for <kvm@archiver.kernel.org>; Wed,  7 Apr 2021 12:09:37 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S235259AbhDGMJn (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Wed, 7 Apr 2021 08:09:43 -0400
Received: from mail-dm6nam12on2042.outbound.protection.outlook.com
 ([40.107.243.42]:13795
        "EHLO NAM12-DM6-obe.outbound.protection.outlook.com"
        rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org with ESMTP
        id S234810AbhDGMJj (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 7 Apr 2021 08:09:39 -0400
ARC-Seal: i=1; a=rsa-sha256; s=arcselector9901; d=microsoft.com; cv=none;
 b=W+iSFKK/47tly0COdPOrxyRWNi1d9AbaYm47IUSVeg8hSqgH52bj+lLJXw/oAo6mEiTDK3TgXr9jkjmSo2ClDkpV771XTsukZDPadLB69J20Y6DueEmN4kKnGVTh9Y+oVcQiDYZgao8XfwEyUadUY9E2R77tIE1NdLMeCu4hLDxOmu7Nd+sCWMN+yypE/ma6SJjI/aa9Zwelf27Yxs5khdk0S1iuU/tckW+0jaB5HyFNbfG9LhgksB/pGlFwOn4Ips2f73sYVXoXyHI7wBfbmRSo/1j7tDFkd0F8ZjKPXYYFvIVlgv7b7rGoDjD9ATobY3lP5YR2pRjE28MLK3s4Og==
ARC-Message-Signature: i=1; a=rsa-sha256; c=relaxed/relaxed; d=microsoft.com;
 s=arcselector9901;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=yg4L4+RG827wx7kvUQi3gfqCTJEpv9Ob8nuvTmw4NVw=;
 b=VzFmWQLUopzTq0GjnrBsiCWc/qPC5ENl5XQY3wb/NzCGXXw+H/llL05c88pcC3V7CB8+cAjx753FoKhyLFzNuNghuUy8BZ9BnjvHGyRWJ+UhxWRhMqU/K1WdszqHTBltd3ATe18jGwUVdVX5by/Qm3wKezPQFcFoK1CesWIhlhbN9siOivCEPLsohV82QUOcVUUckUDJ932+HFpHKChIr3OVFLJHA9N69PWCxSchoZ2dgMJvTzGLCVXVR648hlEyzIasHx9xtl5SNICcvJ01J6qtaVqiu4+OqYnnOddr+4oSaptxuOpOgxHbhKQ59QgWfADGR0vOW4M8/aTgeNLsqg==
ARC-Authentication-Results: i=1; mx.microsoft.com 1; spf=pass (sender ip is
 216.228.112.35) smtp.rcpttodomain=lists.linux-foundation.org
 smtp.mailfrom=nvidia.com; dmarc=pass (p=none sp=none pct=100) action=none
 header.from=nvidia.com; dkim=none (message not signed); arc=none
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=Nvidia.com;
 s=selector2;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=yg4L4+RG827wx7kvUQi3gfqCTJEpv9Ob8nuvTmw4NVw=;
 b=dRbxa/raRtFPLgjIbwezOwso1kYOqNR+LXdxSX4meoRHo//A9tPkGUHR/mjccYL7Qr8ppbFIZ3n0GeZN1ptNxNULViswVz8JHiiOfBBoBnZg29viXIL5+OEKFO3BQvEMkVJJMOsLV3wGNsmPTcsS7HhaMMZMNdN4fCoaLmr2MRrOLE5/Ioi8KYx4222dfslOirUD559kdEK+LF9+kgLl+5PUSk8teXv+zDHKP4gmcpkETeKS56BAB7Ld5PcoTsc/50rgR3cmn/ekns8C+OVUJAtTzsQ7nd9Ror3J+w5KvDPWGu3a7JH2sZSqWae9nxEqaO37YZyWrPC/vqHy0l11oA==
Received: from DS7PR05CA0025.namprd05.prod.outlook.com (2603:10b6:5:3b9::30)
 by DM5PR12MB1530.namprd12.prod.outlook.com (2603:10b6:4:4::23) with Microsoft
 SMTP Server (version=TLS1_2, cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id
 15.20.3999.27; Wed, 7 Apr 2021 12:09:28 +0000
Received: from DM6NAM11FT037.eop-nam11.prod.protection.outlook.com
 (2603:10b6:5:3b9:cafe::34) by DS7PR05CA0025.outlook.office365.com
 (2603:10b6:5:3b9::30) with Microsoft SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.4020.9 via Frontend
 Transport; Wed, 7 Apr 2021 12:09:28 +0000
X-MS-Exchange-Authentication-Results: spf=pass (sender IP is 216.228.112.35)
 smtp.mailfrom=nvidia.com; lists.linux-foundation.org; dkim=none (message not
 signed) header.d=none;lists.linux-foundation.org; dmarc=pass action=none
 header.from=nvidia.com;
Received-SPF: Pass (protection.outlook.com: domain of nvidia.com designates
 216.228.112.35 as permitted sender) receiver=protection.outlook.com;
 client-ip=216.228.112.35; helo=mail.nvidia.com;
Received: from mail.nvidia.com (216.228.112.35) by
 DM6NAM11FT037.mail.protection.outlook.com (10.13.172.122) with Microsoft SMTP
 Server (version=TLS1_2, cipher=TLS_ECDHE_RSA_WITH_AES_256_CBC_SHA384) id
 15.20.4020.17 via Frontend Transport; Wed, 7 Apr 2021 12:09:27 +0000
Received: from HQMAIL101.nvidia.com (172.20.187.10) by HQMAIL111.nvidia.com
 (172.20.187.18) with Microsoft SMTP Server (TLS) id 15.0.1497.2; Wed, 7 Apr
 2021 12:09:27 +0000
Received: from r-nvmx02.mtr.labs.mlnx (172.20.145.6) by mail.nvidia.com
 (172.20.187.10) with Microsoft SMTP Server id 15.0.1497.2 via Frontend
 Transport; Wed, 7 Apr 2021 12:09:25 +0000
From: Max Gurtovoy <mgurtovoy@nvidia.com>
To: <mst@redhat.com>, <kvm@vger.kernel.org>,
        <virtualization@lists.linux-foundation.org>, <jasowang@redhat.com>
CC: <oren@nvidia.com>, <nitzanc@nvidia.com>,
        Max Gurtovoy <mgurtovoy@nvidia.com>
Subject: [PATCH 1/3] virtio: update reset callback to return status
Date: Wed, 7 Apr 2021 12:09:22 +0000
Message-ID: <20210407120924.133294-1-mgurtovoy@nvidia.com>
X-Mailer: git-send-email 2.25.4
MIME-Version: 1.0
X-EOPAttributedMessage: 0
X-MS-PublicTrafficType: Email
X-MS-Office365-Filtering-Correlation-Id: 8705d255-7db6-4be8-1a6d-08d8f9bdfde6
X-MS-TrafficTypeDiagnostic: DM5PR12MB1530:
X-Microsoft-Antispam-PRVS: 
 <DM5PR12MB1530541F95B1F4A8AAC8759DDE759@DM5PR12MB1530.namprd12.prod.outlook.com>
X-MS-Oob-TLC-OOBClassifiers: OLM:2043;
X-MS-Exchange-SenderADCheck: 1
X-Microsoft-Antispam: BCL:0;
X-Microsoft-Antispam-Message-Info: 
 YByB3DotBcRpeaMBOFVBkCvXL2G70bZlCpv9Mnuo4t6nB/TSRY+DNHc6XSFoMsyFS7DgDIl52kRUsgrE21HWsxrR+dQOvTbKMxgB0SsuXuSti8Oz0eChxPDzFcMEqcQlwG8tuUqjwu4C2htksD+Eys9JW8N/g1xu+tVObXAssCw/YLWAkDYtMWR+vbY6Ap9XlARiuLXVrc6e+HJpluL1NWoKrjNbXfoj7tyZ4n1CmUSKmw7Pjt+ddRQoSOITTUigwtGZitVSMRdZa9ulx9olfn0TemE5zOjFhQ+HY7autShb9c8S6UECt8HsM3TPMiDOmt51egqmJA0G0M84kgtOCfMhH+xVGQQpITqgqQtROsvpiWW3JzcDWxnt+mWam1pSpIWTlFfIC++N6YJyTTUcwnS7dO850JnauUiK02elzxVtIiMJvx7VOM3S/F+DE0pMEv7P5mMB/+Qpj35JmDPpeiGgvM2BFDyaLBHbkh8JnaU4Rang9no7eOEifj/lObE2fR8g7kc66i8fjc20H3TyWNomjWhliCJj7q3yeu1/JAafbpwVIzk1dKEGRf/dnqut9PzoIuNsWZbj/yPlIFpg8r7K6EWdthQzPD45QDI4+mhMJjs3wi2GdvbSUzXXIrHTs4x5l2soY9bsb9kvYrVV9x5ByaP2XOlxdcY5rrypCMs=
X-Forefront-Antispam-Report: 
 CIP:216.228.112.35;CTRY:US;LANG:en;SCL:1;SRV:;IPV:NLI;SFV:NSPM;H:mail.nvidia.com;PTR:schybrid02.nvidia.com;CAT:NONE;SFS:(4636009)(136003)(376002)(346002)(396003)(39860400002)(36840700001)(46966006)(316002)(6666004)(26005)(8936002)(2906002)(8676002)(36906005)(5660300002)(82740400003)(54906003)(110136005)(356005)(47076005)(36860700001)(86362001)(70206006)(83380400001)(70586007)(1076003)(478600001)(82310400003)(107886003)(7636003)(4326008)(36756003)(2616005)(336012)(186003)(426003);DIR:OUT;SFP:1101;
X-OriginatorOrg: Nvidia.com
X-MS-Exchange-CrossTenant-OriginalArrivalTime: 07 Apr 2021 12:09:27.5596
 (UTC)
X-MS-Exchange-CrossTenant-Network-Message-Id: 
 8705d255-7db6-4be8-1a6d-08d8f9bdfde6
X-MS-Exchange-CrossTenant-Id: 43083d15-7273-40c1-b7db-39efd9ccc17a
X-MS-Exchange-CrossTenant-OriginalAttributedTenantConnectingIp: 
 TenantId=43083d15-7273-40c1-b7db-39efd9ccc17a;Ip=[216.228.112.35];Helo=[mail.nvidia.com]
X-MS-Exchange-CrossTenant-AuthSource: 
 DM6NAM11FT037.eop-nam11.prod.protection.outlook.com
X-MS-Exchange-CrossTenant-AuthAs: Anonymous
X-MS-Exchange-CrossTenant-FromEntityHeader: HybridOnPrem
X-MS-Exchange-Transport-CrossTenantHeadersStamped: DM5PR12MB1530
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The reset device operation, usually is an operation that might fail from
various reasons. For example, the controller might be in a bad state and
can't answer to any request. Usually, the paravirt SW based virtio
devices always succeed in reset operation but this is not the case for
HW based virtio devices.

This commit is also a preparation for adding a timeout mechanism for
resetting virtio devices.

Signed-off-by: Max Gurtovoy <mgurtovoy@nvidia.com>
Reported-by: kernel test robot <lkp@intel.com>
---
 drivers/remoteproc/remoteproc_virtio.c |  3 ++-
 drivers/virtio/virtio.c                | 22 +++++++++++++++-------
 drivers/virtio/virtio_mmio.c           |  3 ++-
 drivers/virtio/virtio_pci_legacy.c     |  3 ++-
 drivers/virtio/virtio_pci_modern.c     |  3 ++-
 drivers/virtio/virtio_vdpa.c           |  3 ++-
 include/linux/virtio_config.h          |  5 +++--
 7 files changed, 28 insertions(+), 14 deletions(-)

```
#### [PATCH v2 16/19] docs: vcpu-requests.rst: fix reference for atomic ops
##### From: Mauro Carvalho Chehab <mchehab+huawei@kernel.org>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Mauro Carvalho Chehab <mchehab+huawei@kernel.org>
X-Patchwork-Id: 12187417
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-19.0 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED,USER_AGENT_GIT
	autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id CB7DEC43619
	for <kvm@archiver.kernel.org>; Wed,  7 Apr 2021 08:21:15 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id A9BE5613D2
	for <kvm@archiver.kernel.org>; Wed,  7 Apr 2021 08:21:15 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S237082AbhDGIVX (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Wed, 7 Apr 2021 04:21:23 -0400
Received: from mail.kernel.org ([198.145.29.99]:48638 "EHLO mail.kernel.org"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S240361AbhDGIVQ (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 7 Apr 2021 04:21:16 -0400
Received: by mail.kernel.org (Postfix) with ESMTPSA id AA0A8613E5;
        Wed,  7 Apr 2021 08:21:02 +0000 (UTC)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple; d=kernel.org;
        s=k20201202; t=1617783662;
        bh=01jspTSWm7bLXEJy5cH57gxxdERvRXGSivEgicYhRac=;
        h=From:To:Cc:Subject:Date:In-Reply-To:References:From;
        b=jXzc1b5Agkr/7HQxKILvoj1ZXg4WQ4JoGIL8aHE3xU+wUrgoH2CaqRIi8BsJ3m8/q
         L9TEVVmpKxnFQdouRV6ucHeyJyi4kkv0SH+DH4ECIEmLKIm2dnShkYx4yaMBZ5fXf2
         +ybd+3fl7i3eA3+pZ4RMV1zsKQc7CiGEPAPVN2Q6b+3WNwMD+dfH25DWa8cM3JBwON
         d0WPPrljMfeeD1IZiMHAVmE9Jh5ljNJZm0fomiA3mxlnpqgUcQOe6wFL/J9mIljX1Y
         BO38nXrNBFFs2UV6yByRTjRNQlG5Oz6xmv8FsLUAKPyum8RJvHWbL94HVTiM4jg/ud
         eApwM31XX4zBw==
Received: by mail.kernel.org with local (Exim 4.94)
        (envelope-from <mchehab@kernel.org>)
        id 1lU3Qq-005i2i-Rj; Wed, 07 Apr 2021 10:21:00 +0200
From: Mauro Carvalho Chehab <mchehab+huawei@kernel.org>
To: Linux Doc Mailing List <linux-doc@vger.kernel.org>
Cc: Mauro Carvalho Chehab <mchehab+huawei@kernel.org>,
        "Jonathan Corbet" <corbet@lwn.net>,
        Paolo Bonzini <pbonzini@redhat.com>,
        Peter Zijlstra <peterz@infradead.org>, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org
Subject: [PATCH v2 16/19] docs: vcpu-requests.rst: fix reference for atomic
 ops
Date: Wed,  7 Apr 2021 10:20:55 +0200
Message-Id: 
 <d6980818e862c08d13747b87054d92ab2b891112.1617783062.git.mchehab+huawei@kernel.org>
X-Mailer: git-send-email 2.30.2
In-Reply-To: <cover.1617783062.git.mchehab+huawei@kernel.org>
References: <cover.1617783062.git.mchehab+huawei@kernel.org>
MIME-Version: 1.0
Sender: Mauro Carvalho Chehab <mchehab@kernel.org>
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Changeset f0400a77ebdc ("atomic: Delete obsolete documentation")
got rid of atomic_ops.rst, pointing that this was superseded by
Documentation/atomic_*.txt.

Update its reference accordingly.

Fixes: f0400a77ebdc ("atomic: Delete obsolete documentation")
Signed-off-by: Mauro Carvalho Chehab <mchehab+huawei@kernel.org>
---
 Documentation/virt/kvm/vcpu-requests.rst | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
#### [PATCH] x86/kvm: Don't alloc __pv_cpu_mask when !CONFIG_SMP
##### From: Wanpeng Li <kernellwp@gmail.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Wanpeng Li <kernellwp@gmail.com>
X-Patchwork-Id: 12187517
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-15.7 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,DKIM_VALID_AU,FREEMAIL_FORGED_FROMDOMAIN,FREEMAIL_FROM,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED,USER_AGENT_GIT
	autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 989EFC433B4
	for <kvm@archiver.kernel.org>; Wed,  7 Apr 2021 09:03:12 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 624AF6113C
	for <kvm@archiver.kernel.org>; Wed,  7 Apr 2021 09:03:12 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1349872AbhDGJDU (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Wed, 7 Apr 2021 05:03:20 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:60600 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S239586AbhDGJDU (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 7 Apr 2021 05:03:20 -0400
Received: from mail-pg1-x532.google.com (mail-pg1-x532.google.com
 [IPv6:2607:f8b0:4864:20::532])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 04318C061765;
        Wed,  7 Apr 2021 01:53:21 -0700 (PDT)
Received: by mail-pg1-x532.google.com with SMTP id z16so5127708pga.1;
        Wed, 07 Apr 2021 01:53:20 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=from:to:cc:subject:date:message-id;
        bh=sve316YA3/Gg6zITdKEIncJFk6WzcN83zIbDa7bKqHE=;
        b=nvSdZk20UnMflAwIy/wtlKUZTmfSYz+WG7PdFA0b+/U/HYBQBOTo2JBbErV8fJJ2TB
         3yWzh8ZeMDAlQwLvDCWDMGglwBMnmA7j1BB9OS69TCgCEHtWWxCPTmuEUN/03aPla/2f
         83fclaGinm4KDopyIX6sJHuzHdDemQ7zcrjgQ5IXJGkb9mWa6QQU6BljBbzHK3j692Nk
         OYoFtIC2AinOa2Mryj9NhMO2ILlX1xuxyNN64rASIVlHVR9M+XhWhO+buXxKgCtva/na
         Nph+jlK8oh6BWw7yApTMk7qI0lKglFgjmkTHzhMnyWXwIl5gyY8TZx4SclfDl6mAmGQp
         SYqw==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id;
        bh=sve316YA3/Gg6zITdKEIncJFk6WzcN83zIbDa7bKqHE=;
        b=PgtBzSPkIZu7Oa+KZDL1xK6bl8Y5it4nSLKAbw1U3R2JnsjUCtvRjHchyP9vtgG+b9
         QTorjLAZtXHBG/cZK8x3Y/vU2OEoGuwzO0ElqU+/TcNyhzKjiI+N4h05B7OEDcaJ54xC
         tNPoZ6BW408GbcDdJvoUJ0X3zkGCI5GPn7hdPQSgFcz08zYeb5bVmMS2VtSgEHGotNhi
         lnH+Hz9vOR3RXDdyMCr1DCHrqBFYMoesELIjuoFRV3uPAEJMC9gIR5DfPhEPsDxM2YyF
         p4ORIIUjUrURrVQHCEPGhq99osj2XvfPuNyYN+PqM/9UPnNihQOXX+gMCv6EdkOq1J/p
         uEDg==
X-Gm-Message-State: AOAM5324G3YLG8ap09n0diKaOmagwPkly6lRf8yffq7MywZ7fAlAUmgY
        /6Zl3W552+6DOB6FFFjD3IsYUP0Dm8I=
X-Google-Smtp-Source: 
 ABdhPJwJ6I47VptavpkA9zoDC97IJGd5yPmb+cyb63C7EaqA65ofmauukiC80Iim138P76Q4cbBwaw==
X-Received: by 2002:a63:f303:: with SMTP id l3mr2333092pgh.263.1617785600231;
        Wed, 07 Apr 2021 01:53:20 -0700 (PDT)
Received: from localhost.localdomain ([103.7.29.6])
        by smtp.googlemail.com with ESMTPSA id
 l18sm4555017pjq.33.2021.04.07.01.53.17
        (version=TLS1_2 cipher=ECDHE-ECDSA-AES128-GCM-SHA256 bits=128/128);
        Wed, 07 Apr 2021 01:53:19 -0700 (PDT)
From: Wanpeng Li <kernellwp@gmail.com>
X-Google-Original-From: Wanpeng Li <wanpengli@tencent.com>
To: linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Cc: Paolo Bonzini <pbonzini@redhat.com>,
        Sean Christopherson <seanjc@google.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>
Subject: [PATCH] x86/kvm: Don't alloc __pv_cpu_mask when !CONFIG_SMP
Date: Wed,  7 Apr 2021 16:53:08 +0800
Message-Id: <1617785588-18722-1-git-send-email-wanpengli@tencent.com>
X-Mailer: git-send-email 2.7.4
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Wanpeng Li <wanpengli@tencent.com>

Enable PV TLB shootdown when !CONFIG_SMP doesn't make sense. Let's move 
it inside CONFIG_SMP. In addition, we can avoid alloc __pv_cpu_mask when 
!CONFIG_SMP and get rid of 'alloc' variable in kvm_alloc_cpumask.

Signed-off-by: Wanpeng Li <wanpengli@tencent.com>
---
 arch/x86/kernel/kvm.c | 79 +++++++++++++++++++++++++--------------------------
 1 file changed, 39 insertions(+), 40 deletions(-)

```
