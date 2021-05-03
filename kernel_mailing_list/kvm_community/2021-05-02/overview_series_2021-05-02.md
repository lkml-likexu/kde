#### [PATCH 1/1] virtio-net: don't allocate control_buf if not supported
##### From: Max Gurtovoy <mgurtovoy@nvidia.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Max Gurtovoy <mgurtovoy@nvidia.com>
X-Patchwork-Id: 12235117
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-19.4 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_CR_TRAILER,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,
	USER_AGENT_GIT autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 3EBC1C433ED
	for <kvm@archiver.kernel.org>; Sun,  2 May 2021 09:33:26 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 1128B613EA
	for <kvm@archiver.kernel.org>; Sun,  2 May 2021 09:33:26 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S229987AbhEBJeQ (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Sun, 2 May 2021 05:34:16 -0400
Received: from mail-co1nam11on2061.outbound.protection.outlook.com
 ([40.107.220.61]:5536
        "EHLO NAM11-CO1-obe.outbound.protection.outlook.com"
        rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org with ESMTP
        id S229754AbhEBJeO (ORCPT <rfc822;kvm@vger.kernel.org>);
        Sun, 2 May 2021 05:34:14 -0400
ARC-Seal: i=1; a=rsa-sha256; s=arcselector9901; d=microsoft.com; cv=none;
 b=KWhCjmFX6ktkUax4rjgQRyCmprKcfpXJp6OO8FlxvRKD9JsXCQ0EniRi4h3FQYHF6BmXurFDBBS1d19YbJ6T9azoOm/d6RtUznoDUiujABGTAN6zP8xN2Xab/GpujNj6gyg0kGTyplhpaLo+6krBPuTzoTYwKj4CPCNI8GY4IpxCVH++nQreU30rlm368I5z/3hncnbrsyt8ozvMaOOh+bS2SuDNFMQzl97kmTpsmJkqP/99ve2neEf/a81efqI4qy3o3ZCeL2uLBwQEiG2KDDARUzfa/CuPx/Ht/43JnB5HuL5s2+JUPKhQ8sDFPa4NWbOhhaddd4SW2wuRG2poMg==
ARC-Message-Signature: i=1; a=rsa-sha256; c=relaxed/relaxed; d=microsoft.com;
 s=arcselector9901;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=IXQDFJlF1fT/fEiinB/RTnlvv/90dNnWHm8fuCe3x7Y=;
 b=lpz7vq3sW36pTHgSfZoofxeREXVFGZ57/rsO4Ev7KD10WoAjTF1t/o1dVJeT/F789/HXd+rZVqfThgxgFqm3Dlm+Ih+irNMXC2Q+4YWcA9Adb6j2jqoMBNhWBSMNEglIdHDha3L/FHYA8DA+LsaoRdU+amc+tovlqeYib+L8JwFXO5BnTY7BywVjtwOU7q8r2UyRM/wXOzzgkKq+5VnuBv84GCgzWKMde/8K9ytwH9MmVl0LPmjmuOOKQUMLngW/pCW1UEhSu24O9ePIW1Io8xR6TDl+53mCOKSe5SbaSRHmlKFjx+LMEE27GG3vIo56ZmIPm8OGGzypqyDv88MsRQ==
ARC-Authentication-Results: i=1; mx.microsoft.com 1; spf=pass (sender ip is
 216.228.112.35) smtp.rcpttodomain=redhat.com smtp.mailfrom=nvidia.com;
 dmarc=pass (p=none sp=none pct=100) action=none header.from=nvidia.com;
 dkim=none (message not signed); arc=none
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=Nvidia.com;
 s=selector2;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=IXQDFJlF1fT/fEiinB/RTnlvv/90dNnWHm8fuCe3x7Y=;
 b=pSX7qPj0KhPfduKzGWkpjlQCBC6fVa9yeDLneIw2h2PY7QjolqimRg9d6pwH7MtnekgVG20BgmYXGdRPmLSBzM0ZfrliBtgd1HBOkfl2Q/gO+jB8Te8fvugVksGh+kBniLeMFxOAY25sAVf2jy62Ezwnv0BPhDoCLVnNp7aPHDeMMu34xUlE6Sk0rmFlq0vcoDfM0D7XBpy10+Gt2/dhI5K2e4KltBNjkl7rRKdhO8p7OLRozAL2RTyprPqmv8JBRIW7Y1S2INOa147mYz17w3/zpiLERApY1kgFQv+N6pmCq/ojy0G99D8TOD+FeSf7mtWxnQWbNlXewvCsE+hBxA==
Received: from DM6PR02CA0091.namprd02.prod.outlook.com (2603:10b6:5:1f4::32)
 by MN2PR12MB3616.namprd12.prod.outlook.com (2603:10b6:208:cc::25) with
 Microsoft SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.4065.25; Sun, 2 May
 2021 09:33:22 +0000
Received: from DM6NAM11FT034.eop-nam11.prod.protection.outlook.com
 (2603:10b6:5:1f4:cafe::30) by DM6PR02CA0091.outlook.office365.com
 (2603:10b6:5:1f4::32) with Microsoft SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.4087.27 via Frontend
 Transport; Sun, 2 May 2021 09:33:22 +0000
X-MS-Exchange-Authentication-Results: spf=pass (sender IP is 216.228.112.35)
 smtp.mailfrom=nvidia.com; redhat.com; dkim=none (message not signed)
 header.d=none;redhat.com; dmarc=pass action=none header.from=nvidia.com;
Received-SPF: Pass (protection.outlook.com: domain of nvidia.com designates
 216.228.112.35 as permitted sender) receiver=protection.outlook.com;
 client-ip=216.228.112.35; helo=mail.nvidia.com;
Received: from mail.nvidia.com (216.228.112.35) by
 DM6NAM11FT034.mail.protection.outlook.com (10.13.173.47) with Microsoft SMTP
 Server (version=TLS1_2, cipher=TLS_ECDHE_RSA_WITH_AES_256_CBC_SHA384) id
 15.20.4087.32 via Frontend Transport; Sun, 2 May 2021 09:33:22 +0000
Received: from HQMAIL109.nvidia.com (172.20.187.15) by HQMAIL111.nvidia.com
 (172.20.187.18) with Microsoft SMTP Server (TLS) id 15.0.1497.2; Sun, 2 May
 2021 09:33:21 +0000
Received: from r-arch-stor02.mtr.labs.mlnx (172.20.145.6) by mail.nvidia.com
 (172.20.187.15) with Microsoft SMTP Server id 15.0.1497.2 via Frontend
 Transport; Sun, 2 May 2021 02:33:19 -0700
From: Max Gurtovoy <mgurtovoy@nvidia.com>
To: <mst@redhat.com>, <kvm@vger.kernel.org>, <jasowang@redhat.com>,
        <virtualization@lists.linux-foundation.org>
CC: Max Gurtovoy <mgurtovoy@nvidia.com>
Subject: [PATCH 1/1] virtio-net: don't allocate control_buf if not supported
Date: Sun, 2 May 2021 12:33:19 +0300
Message-ID: <20210502093319.61313-1-mgurtovoy@nvidia.com>
X-Mailer: git-send-email 2.18.1
MIME-Version: 1.0
X-EOPAttributedMessage: 0
X-MS-PublicTrafficType: Email
X-MS-Office365-Filtering-Correlation-Id: 4db3f2a0-06a2-40fc-7050-08d90d4d53f9
X-MS-TrafficTypeDiagnostic: MN2PR12MB3616:
X-Microsoft-Antispam-PRVS: 
 <MN2PR12MB36166845161D6AF1F4BA703EDE5C9@MN2PR12MB3616.namprd12.prod.outlook.com>
X-MS-Oob-TLC-OOBClassifiers: OLM:854;
X-MS-Exchange-SenderADCheck: 1
X-Microsoft-Antispam: BCL:0;
X-Microsoft-Antispam-Message-Info: 
 TH1gG75zG5QSD6Jose7MzqQPJkjqK+2uiaJTZUtD4Eu1Qwnv/iZ0PEx6OTTa2tYrdFFJ5Le8gnAp0LodaHKQ0uGsVsNtT90fC0VtB0/trFuhN2R8QVTkjk04XobfWKT3I6NypJKAjm0RCU9R+/x++BQQR8w57Tm1d/ImMgVZie4sK8npLmIX8TzsRSGr33T2LGBirkwcU+QrWK3WOprfmHavSWEBhLbmNx5CEdEzOf/m64u8M96UZYMoa4fbPXKtbHQETYVlQFoAH4UdE7Ixtk/rp4UiNMjZY7GkHi9JD3fWkjZO0iSDLsTtVqZ+mDjf2Ykm91MjNF5Qs8UC2eSUVZTl0s3hYW+sgNju6k5bYUaAAhPddN0X6FS3Ux5m/1Sd6+HrjUJ6vE4xhl9cSemkxZ/6krJJnvjmlrH8EPMVbxEORM7QAyWbrsM7fc71CIX7SH5UDCD5AXGJ3brRRC/9nefiOFscO5/010S2j0rBqPp0dBkOvAbSYyu9IOwWKybtmnozTJ64oSWoPvEgxeZybk64j14adXupzGxZXWtc1ymzbco83zkiB4m+hF5GBpZpIWA73GOzLXq+ZV1Wu9UVlLLutimr7R4z+xd1vr8TEqv06Zu8fE+ug2Jg8K3wm7jghl46Oy1mQjtBzEXWYu4JjARxkXiE2Kqo1yLEs5uVVk4=
X-Forefront-Antispam-Report: 
 CIP:216.228.112.35;CTRY:US;LANG:en;SCL:1;SRV:;IPV:NLI;SFV:NSPM;H:mail.nvidia.com;PTR:schybrid04.nvidia.com;CAT:NONE;SFS:(4636009)(396003)(346002)(39860400002)(376002)(136003)(46966006)(36840700001)(70586007)(4744005)(2906002)(186003)(83380400001)(82740400003)(8936002)(336012)(316002)(356005)(36756003)(36906005)(70206006)(26005)(110136005)(36860700001)(86362001)(107886003)(1076003)(8676002)(478600001)(426003)(2616005)(4326008)(7636003)(82310400003)(5660300002)(47076005);DIR:OUT;SFP:1101;
X-OriginatorOrg: Nvidia.com
X-MS-Exchange-CrossTenant-OriginalArrivalTime: 02 May 2021 09:33:22.1035
 (UTC)
X-MS-Exchange-CrossTenant-Network-Message-Id: 
 4db3f2a0-06a2-40fc-7050-08d90d4d53f9
X-MS-Exchange-CrossTenant-Id: 43083d15-7273-40c1-b7db-39efd9ccc17a
X-MS-Exchange-CrossTenant-OriginalAttributedTenantConnectingIp: 
 TenantId=43083d15-7273-40c1-b7db-39efd9ccc17a;Ip=[216.228.112.35];Helo=[mail.nvidia.com]
X-MS-Exchange-CrossTenant-AuthSource: 
 DM6NAM11FT034.eop-nam11.prod.protection.outlook.com
X-MS-Exchange-CrossTenant-AuthAs: Anonymous
X-MS-Exchange-CrossTenant-FromEntityHeader: HybridOnPrem
X-MS-Exchange-Transport-CrossTenantHeadersStamped: MN2PR12MB3616
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Not all virtio_net devices support the ctrl queue feature. Thus, there
is no need to allocate unused resources.

Signed-off-by: Max Gurtovoy <mgurtovoy@nvidia.com>
---
 drivers/net/virtio_net.c | 10 +++++++---
 1 file changed, 7 insertions(+), 3 deletions(-)

```
