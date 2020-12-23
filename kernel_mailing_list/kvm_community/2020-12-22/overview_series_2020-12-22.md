#### [RFC v2 01/13] mm: export zap_page_range() for driver use
##### From: Xie Yongji <xieyongji@bytedance.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Xie Yongji <xieyongji@bytedance.com>
X-Patchwork-Id: 11986851
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.7 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED,USER_AGENT_GIT
	autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 6B6ABC433DB
	for <kvm@archiver.kernel.org>; Tue, 22 Dec 2020 14:54:08 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 460BB229CA
	for <kvm@archiver.kernel.org>; Tue, 22 Dec 2020 14:54:08 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727650AbgLVOxw (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 22 Dec 2020 09:53:52 -0500
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:43370 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1727094AbgLVOxv (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 22 Dec 2020 09:53:51 -0500
Received: from mail-pf1-x433.google.com (mail-pf1-x433.google.com
 [IPv6:2607:f8b0:4864:20::433])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id B5CB5C06179C
        for <kvm@vger.kernel.org>; Tue, 22 Dec 2020 06:53:11 -0800 (PST)
Received: by mail-pf1-x433.google.com with SMTP id d2so8593666pfq.5
        for <kvm@vger.kernel.org>; Tue, 22 Dec 2020 06:53:11 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=bytedance-com.20150623.gappssmtp.com; s=20150623;
        h=from:to:cc:subject:date:message-id:in-reply-to:references
         :mime-version:content-transfer-encoding;
        bh=VuS4MFGKOQ6wZmoJNuNdlFGLh2OpeJDnVRbM2jvzhBQ=;
        b=m4BAjxY/bQAuznhNdZPDHhxtD84Rnr52bsUNHZeWViOotIiiTQcYTFBGdhnZndjKLk
         OHw+OvpgKjX75tPYqSWtJWfbTAWdQQ/+lPFV0tb2pxQHf18C1jEL2rmD3GJOTJNJYw/r
         DfCFn95QHf56eVVAIb+nAOSxLi3jNYzogNHRvfiVvQJEPMO7nwk2+TZIV7gEvKeGxPHN
         0WWGOplq7NJVzbKmLM2RQs5OLK/X4a5JNAuoZ3Y9vW7v8dFfOxRwVQJzFHrg/vSKPVPa
         J3jnFdGx9AEYV1P1K+DxYo5Z2ZC7lJV5eYuCYuifIINKBww+dPW6mJzHxgD1lPM9W7c7
         lC+w==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:in-reply-to
         :references:mime-version:content-transfer-encoding;
        bh=VuS4MFGKOQ6wZmoJNuNdlFGLh2OpeJDnVRbM2jvzhBQ=;
        b=f48uIXQ9kUNK6VUfnKWSKNRulwoARhQ8uU/ehNZaN/REZvHys0ippFXqX9jJc1h13L
         /CrRMDsCu7xZO6ZwGx+LlgTpeVgTMB2316Jq6hP0IFU6fh8nhob7wuW7vIh78GkrbsKY
         3FvJpXVYv0oguTd1Ec0BO5X1y2uFe1ZsDxtghXg7FX5lvFcn37JnNtnFEO8k+zBbDgvJ
         z8WFjwcH2fpNkI/uv9t2ni9T399I+KB3Ai+TtJE5rEtWT9QHppnL+RrlrR3WDYGnhmLH
         PGPsABB0kGN4THKu6TDlDW6tAiz2TNXZ+CxmZfGGjHWm5zWPzL0FHuMYPVs04W7pR0EH
         Lixg==
X-Gm-Message-State: AOAM533hJb84IL4XRcAIJkGtO9I7uOqgyY7ueO2t2ovOfXFOyiIyWtsI
        WfJTf4PvhZTlw1qTBTetRvGK
X-Google-Smtp-Source: 
 ABdhPJwd0YzlNwNtksNu/va7c2CbgxXpbU4AvnZQJsZ90ddeykZ7FJJwEJpyVaPIxgF6wF8TuDIQsg==
X-Received: by 2002:a63:2406:: with SMTP id k6mr20214091pgk.453.1608648791343;
        Tue, 22 Dec 2020 06:53:11 -0800 (PST)
Received: from localhost ([139.177.225.248])
        by smtp.gmail.com with ESMTPSA id
 w63sm20402234pfc.20.2020.12.22.06.53.09
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Tue, 22 Dec 2020 06:53:10 -0800 (PST)
From: Xie Yongji <xieyongji@bytedance.com>
To: mst@redhat.com, jasowang@redhat.com, stefanha@redhat.com,
        sgarzare@redhat.com, parav@nvidia.com, akpm@linux-foundation.org,
        rdunlap@infradead.org, willy@infradead.org,
        viro@zeniv.linux.org.uk, axboe@kernel.dk, bcrl@kvack.org,
        corbet@lwn.net
Cc: virtualization@lists.linux-foundation.org, netdev@vger.kernel.org,
        kvm@vger.kernel.org, linux-aio@kvack.org,
        linux-fsdevel@vger.kernel.org, linux-mm@kvack.org
Subject: [RFC v2 01/13] mm: export zap_page_range() for driver use
Date: Tue, 22 Dec 2020 22:52:09 +0800
Message-Id: <20201222145221.711-2-xieyongji@bytedance.com>
X-Mailer: git-send-email 2.25.1
In-Reply-To: <20201222145221.711-1-xieyongji@bytedance.com>
References: <20201222145221.711-1-xieyongji@bytedance.com>
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Export zap_page_range() for use in VDUSE.

Signed-off-by: Xie Yongji <xieyongji@bytedance.com>
---
 mm/memory.c | 1 +
 1 file changed, 1 insertion(+)

```
#### [kvm-unit-tests PATCH] fix a arrayIndexOutOfBounds in function init_apic_map, online_cpus[i / 8] when i in 248...254.
##### X-Real-From: liuxp11@chinatelecom.cn

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Xinpeng Liu <liuxp11@chinatelecom.cn>
X-Patchwork-Id: 11986559
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.7 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED,USER_AGENT_GIT
	autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 7E824C433DB
	for <kvm@archiver.kernel.org>; Tue, 22 Dec 2020 13:15:17 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 4DD9A21D7F
	for <kvm@archiver.kernel.org>; Tue, 22 Dec 2020 13:15:17 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727138AbgLVNPQ (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 22 Dec 2020 08:15:16 -0500
Received: from prt-mail.chinatelecom.cn ([42.123.76.219]:36032 "EHLO
        chinatelecom.cn" rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org
        with ESMTP id S1727124AbgLVNPP (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 22 Dec 2020 08:15:15 -0500
X-Greylist: delayed 729 seconds by postgrey-1.27 at vger.kernel.org;
 Tue, 22 Dec 2020 08:15:14 EST
HMM_SOURCE_IP: 172.18.0.48:50097.1081722363
HMM_ATTACHE_NUM: 0000
HMM_SOURCE_TYPE: SMTP
Received: from clientip-223.223.190.99?logid-d47f15e47a804f34bc51bd0740602e91
 (unknown [172.18.0.48])
        by chinatelecom.cn (HERMES) with SMTP id 6EA06280096;
        Tue, 22 Dec 2020 21:00:57 +0800 (CST)
X-189-SAVE-TO-SEND: +liuxp11@chinatelecom.cn
Received: from  ([172.18.0.48])
        by App0024 with ESMTP id d47f15e47a804f34bc51bd0740602e91 for
 kvm@vger.kernel.org;
        Tue Dec 22 21:00:59 2020
X-Transaction-ID: d47f15e47a804f34bc51bd0740602e91
X-filter-score: filter<0>
X-Real-From: liuxp11@chinatelecom.cn
X-Receive-IP: 172.18.0.48
X-MEDUSA-Status: 0
Sender: liuxp11@chinatelecom.cn
From: Xinpeng Liu <liuxp11@chinatelecom.cn>
To: kvm@vger.kernel.org
Cc: liuxp11@chinatelecom.cn
Subject: [kvm-unit-tests PATCH] fix a arrayIndexOutOfBounds in function
 init_apic_map, online_cpus[i / 8] when i in 248...254.
Date: Tue, 22 Dec 2020 21:00:49 +0800
Message-Id: <1608642049-21007-1-git-send-email-liuxp11@chinatelecom.cn>
X-Mailer: git-send-email 1.8.3.1
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

refer to x86/cstart64.S:online_cpus:.fill (max_cpus + 7) / 8, 1, 0

Signed-off-by: Xinpeng Liu <liuxp11@chinatelecom.cn>
---
 lib/x86/apic.c | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
#### [kvm-unit-tests PATCH] x86: Add SPEC CTRL detection testsFrom: Babu Moger <babu.moger@amd.com>
##### From: Babu Moger <babu.moger@amd.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Babu Moger <babu.moger@amd.com>
X-Patchwork-Id: 11987017
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-13.7 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,MSGID_FROM_MTA_HEADER,SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED
	autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 09CC0C433E0
	for <kvm@archiver.kernel.org>; Tue, 22 Dec 2020 16:08:37 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id C11C523124
	for <kvm@archiver.kernel.org>; Tue, 22 Dec 2020 16:08:36 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727550AbgLVQIf (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 22 Dec 2020 11:08:35 -0500
Received: from mail-eopbgr750070.outbound.protection.outlook.com
 ([40.107.75.70]:60504
        "EHLO NAM02-BL2-obe.outbound.protection.outlook.com"
        rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org with ESMTP
        id S1727432AbgLVQIf (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 22 Dec 2020 11:08:35 -0500
ARC-Seal: i=1; a=rsa-sha256; s=arcselector9901; d=microsoft.com; cv=none;
 b=V5sjH5gkcZGKkJ2D5P2mQzFLXbvVr7/pR4YJBoSjh7QEHydSYEeECPSHy8HGF5mx2Z0cbh9xcuzWumKGzIN0v1qP2snoab4C3XPhFgOZpkrU3yfoVv+ofaZhiQ/zK2nWSCy2qv0AxJgMVUm7E3+jDRT4T+ltES5W9kOXmqlIdy4cf3E5NeD+PhmOt0Urxm2QuHULV4NAPlS2JQyRqGC8wG5ul33Td2Ia2EjmJm332BtN71Gfe1M7nI2IJfKB3v1TJLtg64d7aVJwiQ6Cu6mHMu79yiyOaVZEkjHXOJh79GwfNEVvCIxy4AJ3b+lnbD8DXgcs2MlvtOqWHo0hup84Bg==
ARC-Message-Signature: i=1; a=rsa-sha256; c=relaxed/relaxed; d=microsoft.com;
 s=arcselector9901;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=zXVFCMp6IppeZHkGkS/wZbDL80PAuWxZ69/MDR0wuak=;
 b=WQpZWD+Ok7HE/KF82RFavc/mHjkdSa1lEWGxvZIl4Y/zo3n9/SjhQ0ThA4FvG86SdSvagryBIbpYfqBxYwq1py7+rQKpVWThStri8DiR3AJFMKBi1GYi31DwIQZf6DFGggmotS8oRMCcGJZ5oxldln9KBVnLPqtpYRbc8iKUiPXHqlIaWB91aiodYZj9j9svdBXx449WBeCXMlzalRsxy6lG2acXlrYcrlKW7mMZc8wFpfAtmAcZbbsz/shSZ2AysU703odIpju4unxFQ4KAwvh75aotF8uOwPpNvWT2D4ZPdqUFPud8VyIlyrEfEY6ZwbkdaVp8kRncMwNSqr3kPw==
ARC-Authentication-Results: i=1; mx.microsoft.com 1; spf=pass
 smtp.mailfrom=amd.com; dmarc=pass action=none header.from=amd.com; dkim=pass
 header.d=amd.com; arc=none
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
 d=amdcloud.onmicrosoft.com; s=selector2-amdcloud-onmicrosoft-com;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=zXVFCMp6IppeZHkGkS/wZbDL80PAuWxZ69/MDR0wuak=;
 b=sDS+T5rCTmUIfKJrwzmFTcrT5IImR+hBYEf849sOXi2lTh82Zue/dPB86RPBc9pDfifOqdG5Diam1RuzKASDkJW3d1xWddDq6nx6ChFZ1tKAmejwBcbOxcjZed5wBZdRptX7UA7ca7C9EbWvocWflo2wWUcH/mVdFEwNiKhl2GU=
Authentication-Results: amd.com; dkim=none (message not signed)
 header.d=none;amd.com; dmarc=none action=none header.from=amd.com;
Received: from SN1PR12MB2560.namprd12.prod.outlook.com (2603:10b6:802:26::19)
 by SN1PR12MB2559.namprd12.prod.outlook.com (2603:10b6:802:29::30) with
 Microsoft SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.3676.29; Tue, 22 Dec
 2020 16:07:45 +0000
Received: from SN1PR12MB2560.namprd12.prod.outlook.com
 ([fe80::8c0e:9a64:673b:4fff]) by SN1PR12MB2560.namprd12.prod.outlook.com
 ([fe80::8c0e:9a64:673b:4fff%5]) with mapi id 15.20.3676.033; Tue, 22 Dec 2020
 16:07:45 +0000
Subject: [kvm-unit-tests PATCH] x86: Add SPEC CTRL detection tests
From: Babu Moger <babu.moger@amd.com>
To: kvm@vger.kernel.org
Cc: babu.moger@amd.com
Date: Tue, 22 Dec 2020 10:07:28 -0600
Message-ID: <160865324865.19910.5159218511905134908.stgit@bmoger-ubuntu>
User-Agent: StGit/0.17.1-dirty
X-Originating-IP: [165.204.77.1]
X-ClientProxiedBy: SA9PR11CA0022.namprd11.prod.outlook.com
 (2603:10b6:806:6e::27) To SN1PR12MB2560.namprd12.prod.outlook.com
 (2603:10b6:802:26::19)
MIME-Version: 1.0
X-MS-Exchange-MessageSentRepresentingType: 1
Received: from [127.0.1.1] (165.204.77.1) by
 SA9PR11CA0022.namprd11.prod.outlook.com (2603:10b6:806:6e::27) with Microsoft
 SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.3676.30 via Frontend
 Transport; Tue, 22 Dec 2020 16:07:44 +0000
X-MS-PublicTrafficType: Email
X-MS-Office365-Filtering-HT: Tenant
X-MS-Office365-Filtering-Correlation-Id: 9bbcfcfc-cefc-42a3-4e77-08d8a693b824
X-MS-TrafficTypeDiagnostic: SN1PR12MB2559:
X-MS-Exchange-Transport-Forked: True
X-Microsoft-Antispam-PRVS: 
 <SN1PR12MB25592C6C0163D26874E3175595DF0@SN1PR12MB2559.namprd12.prod.outlook.com>
X-MS-Oob-TLC-OOBClassifiers: OLM:1051;
X-MS-Exchange-SenderADCheck: 1
X-Microsoft-Antispam: BCL:0;
X-Microsoft-Antispam-Message-Info: 
 HhIUM5AUOGEkgeHXdFfpiqlRI/R7LuWO0fc+m9mjSB82HE+pB/lOGVxzo9cqsEHHckjjBjtihU08hxlWT9emE0XmP4SoG2UIud7sI4qN5kxkYSRyvn/SeOOI4vTjg7NFC2/XYTErRzB4neXBD/Y4q7NarnFLGKrnaJNbLMcwwEeQhQViT8dJfYZFaK6kxvifUcUgKv2gOVA6rFEiSNBrMkQEXG/3Ut1CgVuCl+SChB3Pqq1B+4IawOY1+HlHkyHw/0o4aOJjd5b7MOfiis6WmCNJ+K2dM97CAtgL+G+ZdkNohqkYyM/XIyrEyaePeID6ngEVImL0CwzXktgfOMf5VotOXIwLSiePaMqdYVQAgYWenJGr2jpEReeI39r9Sa98vCwHTLUMImUf7MdiQFJviw==
X-Forefront-Antispam-Report: 
 CIP:255.255.255.255;CTRY:;LANG:en;SCL:1;SRV:;IPV:NLI;SFV:NSPM;H:SN1PR12MB2560.namprd12.prod.outlook.com;PTR:;CAT:NONE;SFS:(7916004)(4636009)(376002)(366004)(396003)(39860400002)(346002)(136003)(52116002)(478600001)(33716001)(66946007)(6666004)(16576012)(86362001)(316002)(956004)(9686003)(8936002)(4326008)(8676002)(66476007)(6486002)(26005)(44832011)(5660300002)(2906002)(16526019)(6916009)(186003)(103116003)(66556008)(83380400001);DIR:OUT;SFP:1101;
X-MS-Exchange-AntiSpam-MessageData: =?utf-8?q?XrXanHMW1Rt1Wddd2eyOg6nNSddQXS?=
	=?utf-8?q?qD+yeDCElgZvs2a3byX7Y2nIBr42cqDA38GBETlaiChkpZC73jEHCrzCPFTLOBdbp?=
	=?utf-8?q?gEesTTxR47NOtQ73w6mlsZ1JH4/VyK2G0Es4vPmpIaP1R72B/nnJKv3knZplWFxHX?=
	=?utf-8?q?/DrpOpEI6fvzCC/lWIowj3suKWYJ0uWLk+Jx2lWMcr7rNarmTx7LPdnd2Ak23N1JH?=
	=?utf-8?q?vL7m9vCq3hCNMI4u6dect9RbpeLe/4GiPWx/qbV/JG2ZdFQ/Hy7by2Xgt4VeQDMqR?=
	=?utf-8?q?2aZid6yrcBDqvYLQLvSRECOYpBBoBC5aVo1XLIwjYKZH4o4kUkVwR0blUxTW0vsZS?=
	=?utf-8?q?X505GP8be0gb8t8wnhBrms7uACXJgXt/BQ3vKpfpQYEQxaNFJJXjz5KJ0wTFD1Al7?=
	=?utf-8?q?kUi5OLvbcxkG7KhClZ5lzzADflo3dJ7HsFy+OULd9GePfyjdhZ+KKma0l7GP5DV4l?=
	=?utf-8?q?DpgGOuR4c/OPwT5meUUllKVfG7KU8P7ABoNEWl9yPl0UEv+VRnxZ6CzT7xp6ImKv7?=
	=?utf-8?q?KZEeAhCGqMu/fYQOwcGxDNEajtCEsxZhbZeUXkCh6yyEGYyUwmvuBm/FsDoH47x/g?=
	=?utf-8?q?NfjsXX80ILsJsMsUpRebEQUEo6UUoc/EuGTXLj5taZVFewtyQprlMFad/k0LdsgFF?=
	=?utf-8?q?r+HRvS4nV8Q4WXZROSnAjecCMrOuwXBuR+C2tF9BrdY9+5bPANGoodPUGeuosiasI?=
	=?utf-8?q?g0BjkGBEjobArnhfjSyAU005hCU5DHJ+aimRiF6fNa9qRvS4AHhWIffNjoEuIXApW?=
	=?utf-8?q?cYyzNEA2GccAQ63B3WBcCP1QUXSwYz7b3qRccyMs3Hp3SQPMEH8kxZoJ3qs00AXIE?=
	=?utf-8?q?xT5cj3YibHnflOV5xkhEn5Vq4UcWytkMPZcThmWcmEAidQG5hO9TNzvD2SLJMa5uc?=
	=?utf-8?q?jSWH4hL0u8IwBBMQFrE7Oj1s5B9BNz2GM3q3pRAiWWZWUiamp7r28r78dCy6Y2aCR?=
	=?utf-8?q?+MwmdAWisJLiPi4rcW2?=
X-OriginatorOrg: amd.com
X-MS-Exchange-CrossTenant-AuthSource: SN1PR12MB2560.namprd12.prod.outlook.com
X-MS-Exchange-CrossTenant-AuthAs: Internal
X-MS-Exchange-CrossTenant-OriginalArrivalTime: 22 Dec 2020 16:07:45.2006
 (UTC)
X-MS-Exchange-CrossTenant-FromEntityHeader: Hosted
X-MS-Exchange-CrossTenant-Id: 3dd8961f-e488-4e60-8e11-a82d994e183d
X-MS-Exchange-CrossTenant-Network-Message-Id: 
 9bbcfcfc-cefc-42a3-4e77-08d8a693b824
X-MS-Exchange-CrossTenant-MailboxType: HOSTED
X-MS-Exchange-CrossTenant-UserPrincipalName: 
 2SQwuz7pLInCM1Mvo81a9LIsxAHN1bmwbucxxOBFNpanmNypIgtn0zR4+Qpkr+LW
X-MS-Exchange-Transport-CrossTenantHeadersStamped: SN1PR12MB2559
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Displays available SPEC CTRL settings on the host.

Signed-off-by: Babu Moger <babu.moger@amd.com>
---
 lib/x86/processor.h |    6 ++++++
 x86/Makefile.x86_64 |    1 +
 x86/spec_ctrl.c     |   32 ++++++++++++++++++++++++++++++++
 x86/unittests.cfg   |    5 +++++
 4 files changed, 44 insertions(+)
 create mode 100644 x86/spec_ctrl.c

```
#### [PATCH] KVM: x86: fix shift out of bounds reported by UBSAN
##### From: Paolo Bonzini <pbonzini@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Paolo Bonzini <pbonzini@redhat.com>
X-Patchwork-Id: 11986257
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-15.8 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_CR_TRAILER,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,
	URIBL_BLOCKED autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 502E3C433E0
	for <kvm@archiver.kernel.org>; Tue, 22 Dec 2020 10:23:05 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id F136723105
	for <kvm@archiver.kernel.org>; Tue, 22 Dec 2020 10:23:04 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726296AbgLVKXD (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 22 Dec 2020 05:23:03 -0500
Received: from us-smtp-delivery-124.mimecast.com ([63.128.21.124]:55902 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1726218AbgLVKXD (ORCPT
        <rfc822;kvm@vger.kernel.org>); Tue, 22 Dec 2020 05:23:03 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1608632497;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=+N230ZQEwlU/fhfKeKl8xLReA8ul9G84WY/PYPF4Snw=;
        b=HLd6pxb7Ml6Cmot3m+usNpPmc+5cBiisT1NDbXKn7XCdSfcBAq7hbUcNx/zH7JPNykmVGY
        EUmLa1g7COJzlyVaS/sJquvuYWkLZdaHVQdLFXUr6LzVs5zhgU+cUSWy0DcqwtTlKURD0w
        Rm3zNxgGLfmAlP26IOBoSX3Q/3WeKB8=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-440-i7jEHEeuPp2GfpaDgC8mRw-1; Tue, 22 Dec 2020 05:21:34 -0500
X-MC-Unique: i7jEHEeuPp2GfpaDgC8mRw-1
Received: from smtp.corp.redhat.com (int-mx03.intmail.prod.int.phx2.redhat.com
 [10.5.11.13])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id CC218800D55;
        Tue, 22 Dec 2020 10:21:33 +0000 (UTC)
Received: from virtlab701.virt.lab.eng.bos.redhat.com
 (virtlab701.virt.lab.eng.bos.redhat.com [10.19.152.228])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 5CC717A5CE;
        Tue, 22 Dec 2020 10:21:33 +0000 (UTC)
From: Paolo Bonzini <pbonzini@redhat.com>
To: linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Cc: syzbot+e87846c48bf72bc85311@syzkaller.appspotmail.com
Subject: [PATCH] KVM: x86: fix shift out of bounds reported by UBSAN
Date: Tue, 22 Dec 2020 05:21:32 -0500
Message-Id: <20201222102132.1920018-1-pbonzini@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.13
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Since we know that e >= s, we can reassociate the left shift,
changing the shifted number from 1 to 2 in exchange for
decreasing the right hand side by 1.

Reported-by: syzbot+e87846c48bf72bc85311@syzkaller.appspotmail.com
Signed-off-by: Paolo Bonzini <pbonzini@redhat.com>
---
 arch/x86/kvm/mmu.h | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
#### [PATCH v2 1/2] x86/cpufeatures: Add the Virtual SPEC_CTRL featureFrom: Babu Moger <babu.moger@amd.com>
##### From: Babu Moger <babu.moger@amd.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Babu Moger <babu.moger@amd.com>
X-Patchwork-Id: 11987375
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-13.7 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,MSGID_FROM_MTA_HEADER,SPF_HELO_NONE,SPF_PASS
	autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 88B81C433DB
	for <kvm@archiver.kernel.org>; Tue, 22 Dec 2020 22:33:01 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 5C68822573
	for <kvm@archiver.kernel.org>; Tue, 22 Dec 2020 22:33:01 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728533AbgLVWcp (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 22 Dec 2020 17:32:45 -0500
Received: from mail-bn8nam08on2053.outbound.protection.outlook.com
 ([40.107.100.53]:4961
        "EHLO NAM04-BN8-obe.outbound.protection.outlook.com"
        rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org with ESMTP
        id S1728429AbgLVWco (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 22 Dec 2020 17:32:44 -0500
ARC-Seal: i=1; a=rsa-sha256; s=arcselector9901; d=microsoft.com; cv=none;
 b=nCkKZmZlVlOBwmZ40/9r8t3ITT+pRF9saLVBF7FARLGFRdFm9cUKc1NnrOeJIzICCb+uQP+OYkcCgrf+iMoGNf4zFFGRQdiitTcRn5bRwTvwf4C43CPp9ypB95kJu9pkZg5f1v3H8tACplVOhsmddllCFou7snojC2dZ/4zpayugxgdC/WrYVvjRABGJdIaKuclJvPEcDcegAjVKIJRMostrxYz9/pDXHL8+sDKACBDOLt35yCd1ysWvHSniEDj2zSsgjI6rJgnzMgNeNI6rLHTK/PDgaMlgzwZ/+gy87wxXTjBPD/1SsYGWU56luLOcrlpW1TT1LSNdqJcOVm6yYA==
ARC-Message-Signature: i=1; a=rsa-sha256; c=relaxed/relaxed; d=microsoft.com;
 s=arcselector9901;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=nwQaj7nAVZme4C/obXrkq7w4+hAUSeuOa4iFC1vDl1I=;
 b=l5f4+8P5RBDoJCO+Jdwq76GVgtzLdbGduBuN9E8EKsSMzRNFgzuK1mEv2orjTrlnTu5BJl5f6N9nKxbbfZOTsNGf9gFzi5Y7ud4j+L9c4qsmbula+PAAiF4+M4IJSgk6cbZ+Zz0rqi+piM/aV8AqhLBzesb+UyBZmiufLp61rxoWw3QQ2vrI6ZyjRltSuTSH+HqV9U/KtE1SA7qqipojvtCdWrRRX7ULEgoqOB1W7ixdooBNE0rXIzh7bS67mRAQPY60Xm1W0ub7eapZhw9lR+O6vK2Z5DTsVtHUl6IfhDpA/FAR2mkPnnnnQybZCOxxOu6V3VRDf4fPd4G+X4dd9A==
ARC-Authentication-Results: i=1; mx.microsoft.com 1; spf=pass
 smtp.mailfrom=amd.com; dmarc=pass action=none header.from=amd.com; dkim=pass
 header.d=amd.com; arc=none
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
 d=amdcloud.onmicrosoft.com; s=selector2-amdcloud-onmicrosoft-com;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=nwQaj7nAVZme4C/obXrkq7w4+hAUSeuOa4iFC1vDl1I=;
 b=4TCkKPr5JV0JdzKctmH4MXAO4LqPxTT/mwqYX97bpJvrkULGd62qSoRn+2s797m5sJnOzN3W2CmHGDdPWRZejfX2qfipbWTRixjXu1+RzkWMM8MZOBfeYxt22xJFAU3hvvJK6x1DF/n9WvUOJ5QquQvcitQs4mcVCiRQzZvzkug=
Authentication-Results: tencent.com; dkim=none (message not signed)
 header.d=none;tencent.com; dmarc=none action=none header.from=amd.com;
Received: from SN1PR12MB2560.namprd12.prod.outlook.com (2603:10b6:802:26::19)
 by SN1PR12MB2381.namprd12.prod.outlook.com (2603:10b6:802:2f::13) with
 Microsoft SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.3676.33; Tue, 22 Dec
 2020 22:31:50 +0000
Received: from SN1PR12MB2560.namprd12.prod.outlook.com
 ([fe80::8c0e:9a64:673b:4fff]) by SN1PR12MB2560.namprd12.prod.outlook.com
 ([fe80::8c0e:9a64:673b:4fff%5]) with mapi id 15.20.3676.033; Tue, 22 Dec 2020
 22:31:50 +0000
Subject: [PATCH v2 1/2] x86/cpufeatures: Add the Virtual SPEC_CTRL feature
From: Babu Moger <babu.moger@amd.com>
To: pbonzini@redhat.com, tglx@linutronix.de, mingo@redhat.com,
        bp@alien8.de
Cc: fenghua.yu@intel.com, tony.luck@intel.com, wanpengli@tencent.com,
        kvm@vger.kernel.org, thomas.lendacky@amd.com, peterz@infradead.org,
        seanjc@google.com, joro@8bytes.org, x86@kernel.org,
        kyung.min.park@intel.com, linux-kernel@vger.kernel.org,
        krish.sadhukhan@oracle.com, hpa@zytor.com, mgross@linux.intel.com,
        vkuznets@redhat.com, kim.phillips@amd.com, wei.huang2@amd.com,
        jmattson@google.com
Date: Tue, 22 Dec 2020 16:31:32 -0600
Message-ID: <160867629293.3471.18225691185459839634.stgit@bmoger-ubuntu>
In-Reply-To: <160867624053.3471.7106539070175910424.stgit@bmoger-ubuntu>
References: <160867624053.3471.7106539070175910424.stgit@bmoger-ubuntu>
User-Agent: StGit/0.17.1-dirty
X-Originating-IP: [165.204.77.1]
X-ClientProxiedBy: SN4PR0501CA0134.namprd05.prod.outlook.com
 (2603:10b6:803:2c::12) To SN1PR12MB2560.namprd12.prod.outlook.com
 (2603:10b6:802:26::19)
MIME-Version: 1.0
X-MS-Exchange-MessageSentRepresentingType: 1
Received: from [127.0.1.1] (165.204.77.1) by
 SN4PR0501CA0134.namprd05.prod.outlook.com (2603:10b6:803:2c::12) with
 Microsoft SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.3700.19 via Frontend
 Transport; Tue, 22 Dec 2020 22:31:49 +0000
X-MS-PublicTrafficType: Email
X-MS-Office365-Filtering-HT: Tenant
X-MS-Office365-Filtering-Correlation-Id: fad5b82e-00a4-4dcf-9e60-08d8a6c95fe6
X-MS-TrafficTypeDiagnostic: SN1PR12MB2381:
X-MS-Exchange-Transport-Forked: True
X-Microsoft-Antispam-PRVS: 
 <SN1PR12MB23819947D5F4B01AAB33F1C395DF0@SN1PR12MB2381.namprd12.prod.outlook.com>
X-MS-Oob-TLC-OOBClassifiers: OLM:1388;
X-MS-Exchange-SenderADCheck: 1
X-Microsoft-Antispam: BCL:0;
X-Microsoft-Antispam-Message-Info: 
 ykkFARxMSmfgIqLvC5BWpOHHQirvHBIrsZdxnyBxR8Poapunjqmp0IJXqt2xGa0c2zIojMJLc8nTPcICU0W70P5PPsSPNNJkpjxp1PueOhF9/f6/06xq1//tmXE/X4DewmJ3ftw2SjhzrYXGOn0t/S1kwhpxc6alI3o0EZxHzjxylbF+RcIEXY5Dknjzigctvoa6UB4MTyZ4tj5/SmR2MvWVZbypmCEOqNNlV698LNmrWSmhSc+19mRC1Lq+ZshxzQjmGlntbk/EzNzzXo7Z85szTtn5hMXUon953iy1RMh2qV4AcwiaudkI0KDNuO8UKl0mhoqrkvV4Z/afuOYDxh80aYGDCv+Vaqp/6VlwhzLsWuNtt04CYajNPCoa6okRmI6x29NlP7m/+MAb/1mq/Q==
X-Forefront-Antispam-Report: 
 CIP:255.255.255.255;CTRY:;LANG:en;SCL:1;SRV:;IPV:NLI;SFV:NSPM;H:SN1PR12MB2560.namprd12.prod.outlook.com;PTR:;CAT:NONE;SFS:(4636009)(7916004)(346002)(39850400004)(376002)(136003)(396003)(366004)(16526019)(66476007)(26005)(186003)(66946007)(4326008)(103116003)(5660300002)(7416002)(9686003)(66556008)(478600001)(33716001)(956004)(8676002)(6666004)(6486002)(86362001)(316002)(2906002)(8936002)(52116002)(44832011)(16576012);DIR:OUT;SFP:1101;
X-MS-Exchange-AntiSpam-MessageData: =?utf-8?q?5GvVLYulGyMa0eK3PjKT+BUIFi4S3B?=
	=?utf-8?q?poGuCJzjbRtui9OKMa3g0nUt/xddYtATMXpWRj7dd5AihP93ucT9SCMHXRzLYVEzR?=
	=?utf-8?q?qr/kp6aS2fRwUSoKwxmqMMuZ8R1cDWRz10bjUYqbrTrxp3SapU+us6RaJSDvDsI71?=
	=?utf-8?q?uIPfBJXng/fu7cYAucZO3ru+syrhy0PbJJoo0bP8smKAhXPvMEXDBlzmbOBEokmYw?=
	=?utf-8?q?yykOV6H2JlvF4wm2HcHaGl0obTqa1t6MP5f8xlvfD8S4iDzgTBjFBDlw28MLSb++5?=
	=?utf-8?q?jdMNHXVIERFQjIgr5Yg+KURbObuKcbTeWgDkvKG3w13SVBR+9t4LH+FKkXZeJlP0b?=
	=?utf-8?q?EQ0ftP5bEdIQG5wGcBBMjXHtFP3PCLrDjtmh3ua8zmO9wO0giZ7S5GoaTXz727hgu?=
	=?utf-8?q?7R5+uDIC7fVxqNzj8jhEPmSHARWOT9o/0oFBQ8T+dTUVW0FazaGAnqybe6P6fV549?=
	=?utf-8?q?I9UtSjoun6foVDcQ7G+3+DsdcHBbWTch7Ya7xYz+nkRFgLh9oF0a1IqFD8WBWjvgJ?=
	=?utf-8?q?ISYpi33bmnX3YJl3vK28pFHjTVDYGQZEEi31qYjX3RpGI0fD/kjDKDZf8ggFKPbxG?=
	=?utf-8?q?D1bYGrbq6XbH0OX7Ns6pFFk0xeEcK+YCOqW9ZmvSJYZYSJDni0zDpY2eCIGfgXTQ+?=
	=?utf-8?q?J/SiLOW6eGjUvPDe12gCPtwJnZHhMnHTNlg/UKvf5Wvz4D62ZR6XbMqNN8bGd6266?=
	=?utf-8?q?Mj77FasDCxm3XWGdjzLe739DdrJWTavXJ6diH+j74NvjGiLUrhXjLMUakz+7uZ6fx?=
	=?utf-8?q?69+2DEAs6OaV0+aiYxS4r9SojTB+1VlSv6DS4KWEIbaHj6Op+FAH1M+z/qRaPdkjk?=
	=?utf-8?q?//x3G/QnEVYneCJ1+VhSPfgXsi+t51gZ9vkpbnbG6tLoEwQ9AB6sWavIqFBmC9AOO?=
	=?utf-8?q?hx6aXMLh3fPkHHRgOFmqcpjsvoGxbxmkgEECKhqhEzzIe1pV/oCYTS1dn9E/2WPu6?=
	=?utf-8?q?HZiF2dKwdx7V63DH+bh?=
X-OriginatorOrg: amd.com
X-MS-Exchange-CrossTenant-AuthSource: SN1PR12MB2560.namprd12.prod.outlook.com
X-MS-Exchange-CrossTenant-AuthAs: Internal
X-MS-Exchange-CrossTenant-OriginalArrivalTime: 22 Dec 2020 22:31:49.8722
 (UTC)
X-MS-Exchange-CrossTenant-FromEntityHeader: Hosted
X-MS-Exchange-CrossTenant-Id: 3dd8961f-e488-4e60-8e11-a82d994e183d
X-MS-Exchange-CrossTenant-Network-Message-Id: 
 fad5b82e-00a4-4dcf-9e60-08d8a6c95fe6
X-MS-Exchange-CrossTenant-MailboxType: HOSTED
X-MS-Exchange-CrossTenant-UserPrincipalName: 
 TmtQE7+FDsrpTpdV01m6IXrIncNDn19MdVy6KESMJfTKp8vTX2I6Yb69l0GiObgG
X-MS-Exchange-Transport-CrossTenantHeadersStamped: SN1PR12MB2381
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Newer AMD processors have a feature to virtualize the use of the
SPEC_CTRL MSR. Presence of this feature is indicated via CPUID
function 0x8000000A_EDX[20]: GuestSpecCtrl. When preset, the SPEC_CTRL
MSR is automatically virtualized.

Signed-off-by: Babu Moger <babu.moger@amd.com>
---
 arch/x86/include/asm/cpufeatures.h |    1 +
 1 file changed, 1 insertion(+)

```
