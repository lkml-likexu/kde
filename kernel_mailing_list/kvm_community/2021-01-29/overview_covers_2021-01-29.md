

#### [kvm-unit-tests PATCH v2 0/2] x86: SPEC_CTRL tests
##### From: Babu Moger <babu.moger@amd.com>

```c
From patchwork Fri Jan 29 00:36:10 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Babu Moger <babu.moger@amd.com>
X-Patchwork-Id: 12054803
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-10.7 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_PATCH,
	MAILING_LIST_MULTI,MSGID_FROM_MTA_HEADER,SPF_HELO_NONE,SPF_PASS autolearn=ham
	autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 1C4D6C433E0
	for <kvm@archiver.kernel.org>; Fri, 29 Jan 2021 00:37:46 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id D38AE64D7F
	for <kvm@archiver.kernel.org>; Fri, 29 Jan 2021 00:37:45 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S231474AbhA2Ahk (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Thu, 28 Jan 2021 19:37:40 -0500
Received: from mail-bn8nam12on2070.outbound.protection.outlook.com
 ([40.107.237.70]:21985
        "EHLO NAM12-BN8-obe.outbound.protection.outlook.com"
        rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org with ESMTP
        id S231224AbhA2AhH (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 28 Jan 2021 19:37:07 -0500
ARC-Seal: i=1; a=rsa-sha256; s=arcselector9901; d=microsoft.com; cv=none;
 b=OI+3tnVGtcdTbhopAoZ6ule685svDMKVqoH0pLPSKAMp5dKVcEwCtYD+401Yz0zgYItqDAC87/3fwP5+j9xWU/qSS1Hqstb9oGCZMoyYFA328cSIkxhJ8Jj8/QZQRWUNf3WcGlWCZQcnvqP/uWNafqRD/KaZDNa5mtUwjoYhJ9suF5kHLLu3UB3SN+CIJIR54ueRvTDBq/DIHaqBnOgaDSniJ1U1xbmwq0HljoULVTm+l1t7jN+gq+4j7OPqJDOk14jzd3kg6DleQ/Mfeb9/2K2hEg6Ov0xBdAB0s+133fWye5jOkR7ZInFHLGYgQqsy6w3iinAADzcD7t9CHZxsEg==
ARC-Message-Signature: i=1; a=rsa-sha256; c=relaxed/relaxed; d=microsoft.com;
 s=arcselector9901;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=AruFte91wRB3UbNqyw/AX12Rp8NizpbMwBa1k3aBqnE=;
 b=TZTbiBJXXnQ3t9z6/EVTAOFgvwYH5QO3ZuFS3EoZrVdjP58BSIZhWjmqRnlrPQ/5v1BBQ2UBTrd5qwcPWnmPHyF5tbdvStVfTQRhrPrrQh9NxJm6ABIdkMgDZpwRqEJHT5kvg20qwWQ8GYZ5x21c4s80U5dC2UhwOmxYAAeA7DWM8Io+Cs/wFzSyjlnXaO8QGKdhDGyFg6tWiZ01Hv+f9JHec22xCraf12dNDGnhLonkGInTSiMHkmyKD4vHJbonh0iXXQTCo2flRI09L0WuVYAAtNeC48ZjOckKqw/o77bNFRCBZv89pXd+Het8Ff6/AL1iGbvAQrWH7AxFwVURQg==
ARC-Authentication-Results: i=1; mx.microsoft.com 1; spf=pass
 smtp.mailfrom=amd.com; dmarc=pass action=none header.from=amd.com; dkim=pass
 header.d=amd.com; arc=none
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=amd.com; s=selector1;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=AruFte91wRB3UbNqyw/AX12Rp8NizpbMwBa1k3aBqnE=;
 b=tr+VRiL2ebnHaMBq2iZOtseMCn2WqqE6ne28WhzQLKU5Dr4rFpGBVfPDzWkr2OFcemWfU8RC1VSsbsMUOPE/4KmXZdUIwY15U5ApkE1uaPkFe2lov/v7HX/730xTSdewEqzRENInis7Ds7DyUHqBJLdkmXz6ltwpYxbsxuL5nus=
Authentication-Results: amd.com; dkim=none (message not signed)
 header.d=none;amd.com; dmarc=none action=none header.from=amd.com;
Received: from SN1PR12MB2560.namprd12.prod.outlook.com (2603:10b6:802:26::19)
 by SN1PR12MB2525.namprd12.prod.outlook.com (2603:10b6:802:29::28) with
 Microsoft SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.3805.17; Fri, 29 Jan
 2021 00:36:13 +0000
Received: from SN1PR12MB2560.namprd12.prod.outlook.com
 ([fe80::8c0e:9a64:673b:4fff]) by SN1PR12MB2560.namprd12.prod.outlook.com
 ([fe80::8c0e:9a64:673b:4fff%5]) with mapi id 15.20.3805.019; Fri, 29 Jan 2021
 00:36:13 +0000
Subject: [kvm-unit-tests PATCH v2 0/2] x86: SPEC_CTRL tests
From: Babu Moger <babu.moger@amd.com>
Cc: kvm@vger.kernel.org
Date: Thu, 28 Jan 2021 18:36:10 -0600
Message-ID: <161188044937.28708.9182196001493811398.stgit@bmoger-ubuntu>
User-Agent: StGit/0.17.1-dirty
X-Originating-IP: [165.204.77.1]
X-ClientProxiedBy: SN7PR04CA0291.namprd04.prod.outlook.com
 (2603:10b6:806:123::26) To SN1PR12MB2560.namprd12.prod.outlook.com
 (2603:10b6:802:26::19)
MIME-Version: 1.0
X-MS-Exchange-MessageSentRepresentingType: 1
Received: from [127.0.1.1] (165.204.77.1) by
 SN7PR04CA0291.namprd04.prod.outlook.com (2603:10b6:806:123::26) with
 Microsoft SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.3805.16 via Frontend
 Transport; Fri, 29 Jan 2021 00:36:11 +0000
X-MS-PublicTrafficType: Email
X-MS-Office365-Filtering-HT: Tenant
X-MS-Office365-Filtering-Correlation-Id: 041bbfad-c033-40ef-933c-08d8c3ede060
X-MS-TrafficTypeDiagnostic: SN1PR12MB2525:
X-MS-Exchange-Transport-Forked: True
X-Microsoft-Antispam-PRVS: 
 <SN1PR12MB252588D9DADA067AB4475A2995B99@SN1PR12MB2525.namprd12.prod.outlook.com>
X-MS-Oob-TLC-OOBClassifiers: OLM:1728;
X-MS-Exchange-SenderADCheck: 1
X-Microsoft-Antispam: BCL:0;
X-Microsoft-Antispam-Message-Info: 
 Vg4zCzTeVA28k9+kc4lINKRQHeu5D9v2OC6vDDBLYetzbjvWCGJtMD8cX4kXl70hiVtIIa3fby8N2k/n0lhvLMP0q8H+iurYSTiECYZLMizS3tOrIAnvQki92wVc9whhjOvDCjowODLfxQImqpnOnuS2VUCAfjRb+44xlOEu4364mGyLyW61Gn3xhJUwyMszweTCTMAQoN/+mJDCwBseu1EUfavqF0ubnWED+WKZTLW98O3L8cCw3BGIkcq/OjCAbj3JRjY4+XfsoKHt/vk5EkKNGnxHacslKSCrjKPAKrCiHLa3yzslvgn+v7iL6o+Fx9u0+8RbJLaM7rPluC/YRKhFiUkTxdz4CDH4yjuS3XKd9MTRlym6iO0QG9nYQEcIOI0yQBEqI6ckOem1t9xKJd1GXFSfYBOKcFbM/uXG/lvQnHHPwKLIP3U8lUuvwCHeCUwwywWtdgWtLVB3D8bB51/Othh/MAaaob/Nvea9Q4CM4xHgoGZ9pT1eqCcZxvhlJFL8gTMVooWg4LVkaF9EOuxgWiJccul/LXKOTAgzQGykHRvOjko4jwcs+kA2wqOSutmH3+9sKIxC08XaU51qdTlvKi8Rjh6p+iwq5a5aTcY=
X-Forefront-Antispam-Report: 
 CIP:255.255.255.255;CTRY:;LANG:en;SCL:1;SRV:;IPV:NLI;SFV:NSPM;H:SN1PR12MB2560.namprd12.prod.outlook.com;PTR:;CAT:NONE;SFS:(4636009)(7916004)(396003)(346002)(39860400002)(366004)(136003)(376002)(83380400001)(2906002)(103116003)(66946007)(8936002)(8676002)(52116002)(4326008)(86362001)(66476007)(66556008)(109986005)(966005)(186003)(6486002)(478600001)(16526019)(26005)(5660300002)(4744005)(33716001)(44832011)(316002)(16576012)(9686003)(956004);DIR:OUT;SFP:1101;
X-MS-Exchange-AntiSpam-MessageData: =?utf-8?q?oaQz4RVIVDsaLWiXUcXFb3W2JXrTBN?=
	=?utf-8?q?ZyD5trCz01MpII9Nj5/YKKbDMxGOwRGkpB3298TKP5DpDWUR9llKBXi49FvCaZnUn?=
	=?utf-8?q?AROuEf3IS8koKxXvyplSWSvuDaTE1EU91jJIR7iTmtPgW7k34xrCgHOeIINOezVLL?=
	=?utf-8?q?YXUj96d+xoass/qdLv1HyYHLzYK3WuaI4FBtvByfMfcFiDsDevsGU8UpWkvdq92ID?=
	=?utf-8?q?Cyf3+0oFJN3G7pY3yPIti26c7bREFLsLzoRZP8Jh9eRKAlRT19r0GBht+Hu/uR/iu?=
	=?utf-8?q?92O5DL+3f1fk3drf29Y6jGmYnm4baB6XtxSibrO8jjeT0eVxXG+De8CPtmfKXxMcD?=
	=?utf-8?q?HuXtnF5CLfz8r+hKNB5JC+PQHOilPaI13yht9HaftviQ0EjZerzFTvvJoYjXGT4l8?=
	=?utf-8?q?dn8kaaGDz6CZoefKClIOUIGC0FWfDpQbTNs/LZcMLkn8+9uG/ioRvbazd0NMLiI0K?=
	=?utf-8?q?vVlPiNAjvkBrpKMHoPAQF1zi2/kUnN6uVIzH5UWIEPnf4rJf8mMNNbXeahl5gyUYc?=
	=?utf-8?q?eGtjeUk0WQoZ/mmsHlbhW84g2Q0cG4YNLdnSwpXGhOhgg1EDCO0bhlBMLcaPCYBl6?=
	=?utf-8?q?yYWK7i6Dr5k22PZRBFCmYoMnSUKjY5TKG5dwWmi3mvoumRY3wUcpZa14yOxyLP2Q4?=
	=?utf-8?q?2ONSVU5yQI/GJXoq/qc54i/ayJ2NiU/6jQLjX8AL6IFTcADrCTtWOaf5yH/SLxr1x?=
	=?utf-8?q?w9O9udpnQ3czsggClzedHF2ncvCM0EY/GbrqkoUoqGRw2AlZa/+bUPAgEsuOFplAl?=
	=?utf-8?q?q/YmO/wvlVhnBYnClQEepwdZLLUIBAExkrJvksMd6PNXkEwtNeASktbjHmuiD2jDz?=
	=?utf-8?q?pz1dq20C8grA1Nfc1Pdj45eMufA1nECC0cy57nEqg9lzGMOvhsjw+onlkycyTLeII?=
	=?utf-8?q?ysmksGi5VNWK9R8U/SHEnedWzqzbnWsbZ/ZtX4M4YW+pDooE2a2uLv2XcJI2AYPhP?=
	=?utf-8?q?R4YocQwO/crlRfJpUnB0/K1Gz0ez0SFaHT0TCUg+jGyW0Ywgfbm1wqg0CjX6jwZmp?=
	=?utf-8?q?sXPMndFmHBdmiLPu/P?=
X-OriginatorOrg: amd.com
X-MS-Exchange-CrossTenant-Network-Message-Id: 
 041bbfad-c033-40ef-933c-08d8c3ede060
X-MS-Exchange-CrossTenant-AuthSource: SN1PR12MB2560.namprd12.prod.outlook.com
X-MS-Exchange-CrossTenant-AuthAs: Internal
X-MS-Exchange-CrossTenant-OriginalArrivalTime: 29 Jan 2021 00:36:13.2574
 (UTC)
X-MS-Exchange-CrossTenant-FromEntityHeader: Hosted
X-MS-Exchange-CrossTenant-Id: 3dd8961f-e488-4e60-8e11-a82d994e183d
X-MS-Exchange-CrossTenant-MailboxType: HOSTED
X-MS-Exchange-CrossTenant-UserPrincipalName: 
 WFEwliMHljL2QOlUqdhpBE13H5GxpFqXCroeVr71Ej/CgDltJuQIuRvkEmYmnYaj
X-MS-Exchange-Transport-CrossTenantHeadersStamped: SN1PR12MB2525
To: unlisted-recipients:; (no To-header on input)
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Add SPEC_CTRL detection and verification tests.
---
v2:
   Added svm SPEC_CTRL verification tests.
   Changed few texts.

v1: https://lore.kernel.org/kvm/160865324865.19910.5159218511905134908.stgit@bmoger-ubuntu/

Babu Moger (2):
      x86: Add SPEC CTRL detection tests
      x86: svm: Add SPEC_CTRL feature test


 lib/x86/processor.h |    5 +++++
 x86/Makefile.x86_64 |    1 +
 x86/spec_ctrl.c     |   30 +++++++++++++++++++++++++++++
 x86/svm_tests.c     |   52 +++++++++++++++++++++++++++++++++++++++++++++++++++
 x86/unittests.cfg   |    5 +++++
 5 files changed, 93 insertions(+)
 create mode 100644 x86/spec_ctrl.c

--
```
#### [PATCH v4 0/2] x86: Add the feature Virtual SPEC_CTRL
##### From: Babu Moger <babu.moger@amd.com>

```c
From patchwork Fri Jan 29 00:43:16 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Babu Moger <babu.moger@amd.com>
X-Patchwork-Id: 12054809
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-10.7 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_PATCH,
	MAILING_LIST_MULTI,MSGID_FROM_MTA_HEADER,SPF_HELO_NONE,SPF_PASS autolearn=ham
	autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 7F1F0C433DB
	for <kvm@archiver.kernel.org>; Fri, 29 Jan 2021 00:45:40 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 3555D64D99
	for <kvm@archiver.kernel.org>; Fri, 29 Jan 2021 00:45:40 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S231650AbhA2ApM (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Thu, 28 Jan 2021 19:45:12 -0500
Received: from mail-dm6nam08on2058.outbound.protection.outlook.com
 ([40.107.102.58]:18528
        "EHLO NAM04-DM6-obe.outbound.protection.outlook.com"
        rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org with ESMTP
        id S231444AbhA2AoL (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 28 Jan 2021 19:44:11 -0500
ARC-Seal: i=1; a=rsa-sha256; s=arcselector9901; d=microsoft.com; cv=none;
 b=GDwu4WxI9kECLFkQg22VTsOTxgKfsHQoM/talrVLxoER3/ir1qm1F5krjpMrUxs6H/mBOUvhVeyu/xo40eJejdP+02t6cut9KoSg9/zfMc9PZPVjEOxciI4XuOFFUku+/bkY3HWLLqxsKxwHczdVZ5ef29Wnv5hjBVFCJSJ9mND+Fu0dH96a1GcSbjdZ2ePUX2rCx/36hPzPmxDWiB4EeLx6rHe0yyXFb9DnEjcmmqM82TUNyVcWEUgq1MEsNqmrW4GABrK9G7gQ1DAqjUn/710+GKReNfEf3h3GAlLbae0EG+LLoLjddXvF5bbGSf8MKloc1990G7kFwi/qQEUJQA==
ARC-Message-Signature: i=1; a=rsa-sha256; c=relaxed/relaxed; d=microsoft.com;
 s=arcselector9901;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=u0wlbu+rGSGyJtV82TTyePIZ+f3cfD9tyoTp4dGGUeo=;
 b=AZfcy3nvY+QPk2hT6tCtmOJQDUOgYc6GXSgVQf52hcUyAXsMmh0SdDu+8F9zUNQW77hx880oHtuH8UDaarf97slznjIgNpvXSq7Q2yQjHJag7MFGGAyXugdCfY84W/oUqMrRLFrH3MjbfwysYDCVL6ySLZCvxmuOQRyp1Lac5I9uUrWLCKGgOAjMVZHvBTB95Sigvc8DGey8TRXNPWPAvdlF9s35/rOPE1RGvlhpqCY0qNawuqxb16XwuPxWxLBqRzzVHPA8o3m7inIqAea8SsC/Iux4IMCrTCic3GR42zxsOe1mR/TxkMMuEvEU7k8n8n0Li39dpRpVRANJZBrrSg==
ARC-Authentication-Results: i=1; mx.microsoft.com 1; spf=pass
 smtp.mailfrom=amd.com; dmarc=pass action=none header.from=amd.com; dkim=pass
 header.d=amd.com; arc=none
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=amd.com; s=selector1;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=u0wlbu+rGSGyJtV82TTyePIZ+f3cfD9tyoTp4dGGUeo=;
 b=HJ4aOVoin8ZbTlKjqFWo+ScuzFFWqMi2vVCh1N1DsITZyj1mqwc1muacfEduoNII5x9O56hKTnuQqOxam56ulmBKW5qigNoA5PEkUEJcT/ItfEaa6m0hrPj0xMEieM714Qezl5YPsoFxAF3x+qktaUpyQbfOo5CSH1XT3yaTn3s=
Authentication-Results: tencent.com; dkim=none (message not signed)
 header.d=none;tencent.com; dmarc=none action=none header.from=amd.com;
Received: from SN1PR12MB2560.namprd12.prod.outlook.com (2603:10b6:802:26::19)
 by SN1PR12MB2560.namprd12.prod.outlook.com (2603:10b6:802:26::19) with
 Microsoft SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.3805.17; Fri, 29 Jan
 2021 00:43:17 +0000
Received: from SN1PR12MB2560.namprd12.prod.outlook.com
 ([fe80::8c0e:9a64:673b:4fff]) by SN1PR12MB2560.namprd12.prod.outlook.com
 ([fe80::8c0e:9a64:673b:4fff%5]) with mapi id 15.20.3805.019; Fri, 29 Jan 2021
 00:43:17 +0000
Subject: [PATCH v4 0/2] x86: Add the feature Virtual SPEC_CTRL
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
Date: Thu, 28 Jan 2021 18:43:16 -0600
Message-ID: <161188083424.28787.9510741752032213167.stgit@bmoger-ubuntu>
User-Agent: StGit/0.17.1-dirty
X-Originating-IP: [165.204.77.1]
X-ClientProxiedBy: SN7PR04CA0107.namprd04.prod.outlook.com
 (2603:10b6:806:122::22) To SN1PR12MB2560.namprd12.prod.outlook.com
 (2603:10b6:802:26::19)
MIME-Version: 1.0
X-MS-Exchange-MessageSentRepresentingType: 1
Received: from [127.0.1.1] (165.204.77.1) by
 SN7PR04CA0107.namprd04.prod.outlook.com (2603:10b6:806:122::22) with
 Microsoft SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.3805.17 via Frontend
 Transport; Fri, 29 Jan 2021 00:43:16 +0000
X-MS-PublicTrafficType: Email
X-MS-Office365-Filtering-HT: Tenant
X-MS-Office365-Filtering-Correlation-Id: 60361f35-5746-4c87-6fc2-08d8c3eede62
X-MS-TrafficTypeDiagnostic: SN1PR12MB2560:
X-MS-Exchange-Transport-Forked: True
X-Microsoft-Antispam-PRVS: 
 <SN1PR12MB2560F2879D5B7FEF19313AEF95B99@SN1PR12MB2560.namprd12.prod.outlook.com>
X-MS-Oob-TLC-OOBClassifiers: OLM:8273;
X-MS-Exchange-SenderADCheck: 1
X-Microsoft-Antispam: BCL:0;
X-Microsoft-Antispam-Message-Info: 
 AU6Ynwm8ZILj39g8BC+OVmKCeiduD6FfHlExKYDkxilUBtY/N7I5/nmfVBSySQpxu7YyD7Wtft6EEen1oEjCZaAh6x2cBSUTBtK5JiYbO7mzWQvmltW6VAW0dGrJoPm/klaD8nnJnC5yGA7bYXJhzO4PNswEQw538e1gDqzIXQQwy/tYk7WFN83XU8vQqaJTY3ye5pXHM68LExX4leY/mKB/Z4bIAKRp4SAvIo1y04agYePRa/952QTXWDfXUxNwgv+WNmzZi1D2hHwpkg8Ek5urhYib6hgn83XDxpZYH2JPLh5Mo5aUuJr+JhR5F7+TH+mlRnNZPPoHd6My5xzuEA+9Gb2L6+msRfafYlC7XZt+AVzSL7I7ntocisSxz5uopay6xwQ4WBX8Y4i/2tKPUNJxLi+3MMVBkLDwbVvYjovndrvpehf7K/j+mwEMh3pQ0KaLSGfW79f2XBqkEMI8NQrz9RTbMI2MGRFGpcSJNrSwgIbp9JS3DYf2kIw+85uSuuYm0ynbTQGzKQYBdgMWYTpARhLWRwcRx4+pIkMkb22L8nNtlLwEpgBH4GW/z1aDU3PPh6nI/E6DfpOQdwuNpf6eBx7nVk7jNroCn/opJlk=
X-Forefront-Antispam-Report: 
 CIP:255.255.255.255;CTRY:;LANG:en;SCL:1;SRV:;IPV:NLI;SFV:NSPM;H:SN1PR12MB2560.namprd12.prod.outlook.com;PTR:;CAT:NONE;SFS:(4636009)(7916004)(396003)(39860400002)(136003)(366004)(346002)(376002)(956004)(16576012)(52116002)(7416002)(8936002)(8676002)(316002)(86362001)(83380400001)(103116003)(44832011)(16526019)(186003)(33716001)(966005)(4326008)(478600001)(6486002)(9686003)(66476007)(66556008)(5660300002)(26005)(2906002)(66946007);DIR:OUT;SFP:1101;
X-MS-Exchange-AntiSpam-MessageData: =?utf-8?q?YUXaFMbFNkg2HQ9+3lzUvD6XoYryJg?=
	=?utf-8?q?+mf1593IfswCKdVLwuDruByUXdGe6J/J6MhRFCiX+wLGkeubXloz5FA05ex5f7+k9?=
	=?utf-8?q?oq+/MOxloTVi59N2G+A49w98KBzU+na6/fyGSImLA+ZrdkuFQgF2Ky4zLQvu7MAkI?=
	=?utf-8?q?L/yInk91JvdD3hvVAHQhkUvPvOmevR33ZPwzJYErCFQwdj6AsKH86Ci50uXuBoi9M?=
	=?utf-8?q?BXFYytZgFEmMa9Z7mOsNv/rhkeWl/5V4OftQA7p8G6hPbo5FXEHEgiYnIyjY+NXgm?=
	=?utf-8?q?0n2srzESoUDo2vqVlQnnTwfdsgPOFZVWUA16kPQaENq6qzUIdfbesQP8PBRm5j2Hy?=
	=?utf-8?q?nfTo5fNH9bNZllYzaMgXPZakSsK1rB137JaFXT7IgXkJ0P123e/5UGkzdfQPnYMht?=
	=?utf-8?q?vUkop3R0FUDcIOi9L4yPk747LwnUxW/agxxNZKO+LFGaByzQYDY4Zhm0y/H2lguUL?=
	=?utf-8?q?LfF6o8J/G3n3BuLbiV/qRTfhbvJ62eFgHzn0mqPkghMbsVwjCsCUJn8OQCoqGLj3h?=
	=?utf-8?q?gsNI086Aw0sdQuuyzXVT98Z1PprijnSUu5pX6G44Q+NK1AL83OnAcnqQwOPExcwQV?=
	=?utf-8?q?5vNvpAgF0nSyHMqZ7ZrLSscY9aoDkY5vFxn/VUwArrCQ0XJ0kXBytYPaAXclUYmyh?=
	=?utf-8?q?5G34GTbDuJuItpGNtFBgUMiJMqorkng2i33K9xwpDOowu6NEgfQ+HC3kjh48Fk6f6?=
	=?utf-8?q?GwhTpABKL9lJeCV938m3ExKwQcfO1+kZ7G7yuCSoi5JoaR+iwmIm2be40TzX+gBbT?=
	=?utf-8?q?5WEUNDbrqN2OInC0KfhogcykqKflxivmM/EQICVHXl2B0jbFSAVgK6p09W+ZqVnsN?=
	=?utf-8?q?OCD5dLWlkWnnR6Dmo8cgh89+U4FTbjnJ5qbxwWirf3asc44WcHx1a2JDhYFqylemS?=
	=?utf-8?q?JLfOA0PSAJ2G/MUDqxNmGcCvRet6evv0gszobf5+NbURu0NWMpdqXa/dN+dTDRmtW?=
	=?utf-8?q?Xo5a911e9QBb2pj6pY9nlBqBZbOlKb2IAAlPTmHdOKAFd9iimWZT6bBXP+ZLZGGIx?=
	=?utf-8?q?StSw2g/3PP8rHRhW4N?=
X-OriginatorOrg: amd.com
X-MS-Exchange-CrossTenant-Network-Message-Id: 
 60361f35-5746-4c87-6fc2-08d8c3eede62
X-MS-Exchange-CrossTenant-AuthSource: SN1PR12MB2560.namprd12.prod.outlook.com
X-MS-Exchange-CrossTenant-AuthAs: Internal
X-MS-Exchange-CrossTenant-OriginalArrivalTime: 29 Jan 2021 00:43:17.5240
 (UTC)
X-MS-Exchange-CrossTenant-FromEntityHeader: Hosted
X-MS-Exchange-CrossTenant-Id: 3dd8961f-e488-4e60-8e11-a82d994e183d
X-MS-Exchange-CrossTenant-MailboxType: HOSTED
X-MS-Exchange-CrossTenant-UserPrincipalName: 
 1tNBKMZwh0nJYQqRF9NtATWL+7Elc7S8D7nlAMqt+yg1XKfNkUCoYV2PkwstKuIH
X-MS-Exchange-Transport-CrossTenantHeadersStamped: SN1PR12MB2560
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Newer AMD processors have a feature to virtualize the use of the
SPEC_CTRL MSR on the guest. The series adds the feature support
and enables the feature on SVM.
---
v4:
  1. Taken care of comments from Sean Christopherson.
     a. Updated svm_set_msr/svm_get_msr to read/write the spec_ctrl value
        directly from save spec_ctrl.
     b. Disabled the msr_interception in init_vmcb when V_SPEC_CTRL is
        present.
     c. Added the save restore for nested vm. Also tested to make sure
        the nested SPEC_CTRL settings properly saved and restored between
        L2 and L1 guests.
  2. Added the kvm-unit-tests to verify that. Sent those patches separately.

v3:
  1. Taken care of recent changes in vmcb_save_area. Needed to adjust the save
     area spec_ctrl definition.
  2. Taken care of few comments from Tom.
     a. Initialised the save area spec_ctrl in case of SEV-ES.
     b. Removed the changes in svm_get_msr/svm_set_msr.
     c. Reverted the changes to disable the msr interception to avoid compatibility
        issue.
  3. Updated the patch #1 with Acked-by from Boris.
  
v2:
  NOTE: This is not final yet. Sending out the patches to make
  sure I captured all the comments correctly.

  1. Most of the changes are related to Jim and Sean's feedback.
  2. Improved the description of patch #2.
  3. Updated the vmcb save area's guest spec_ctrl value(offset 0x2E0)
     properly. Initialized during init_vmcb and svm_set_msr and
     returned the value from save area for svm_get_msr.
  4. As Jim commented, transferred the value into the VMCB prior
     to VMRUN and out of the VMCB after #VMEXIT.
  5. Added kvm-unit-test to detect the SPEC CTRL feature.
     https://lore.kernel.org/kvm/160865324865.19910.5159218511905134908.stgit@bmoger-ubuntu/
  6. Sean mantioned of renaming MSR_AMD64_VIRT_SPEC_CTRL. But, it might
     create even more confusion, so dropped the idea for now.

v3: https://lore.kernel.org/kvm/161073115461.13848.18035972823733547803.stgit@bmoger-ubuntu/
v2: https://lore.kernel.org/kvm/160867624053.3471.7106539070175910424.stgit@bmoger-ubuntu/
v1: https://lore.kernel.org/kvm/160738054169.28590.5171339079028237631.stgit@bmoger-ubuntu/

Babu Moger (2):
      x86/cpufeatures: Add the Virtual SPEC_CTRL feature
      KVM: SVM: Add support for Virtual SPEC_CTRL


 arch/x86/include/asm/cpufeatures.h |    1 +
 arch/x86/include/asm/svm.h         |    4 +++-
 arch/x86/kvm/svm/nested.c          |    2 ++
 arch/x86/kvm/svm/svm.c             |   27 ++++++++++++++++++++++-----
 4 files changed, 28 insertions(+), 6 deletions(-)

--
```
#### [kvm-unit-tests PATCH v3 00/11] GIC fixes and improvements
##### From: Alexandru Elisei <alexandru.elisei@arm.com>

```c
From patchwork Fri Jan 29 16:36:36 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Alexandru Elisei <alexandru.elisei@arm.com>
X-Patchwork-Id: 12056023
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-11.8 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,
	SPF_PASS,URIBL_BLOCKED,USER_AGENT_GIT autolearn=unavailable
	autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 594AEC433E0
	for <kvm@archiver.kernel.org>; Fri, 29 Jan 2021 16:38:09 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 3752964DFB
	for <kvm@archiver.kernel.org>; Fri, 29 Jan 2021 16:38:09 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S231256AbhA2QiH (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Fri, 29 Jan 2021 11:38:07 -0500
Received: from foss.arm.com ([217.140.110.172]:51056 "EHLO foss.arm.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S229825AbhA2Qhz (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 29 Jan 2021 11:37:55 -0500
Received: from usa-sjc-imap-foss1.foss.arm.com (unknown [10.121.207.14])
        by usa-sjc-mx-foss1.foss.arm.com (Postfix) with ESMTP id 2109913D5;
        Fri, 29 Jan 2021 08:37:09 -0800 (PST)
Received: from monolith.localdoman (unknown [172.31.20.19])
        by usa-sjc-imap-foss1.foss.arm.com (Postfix) with ESMTPSA id
 47F063F71B;
        Fri, 29 Jan 2021 08:37:07 -0800 (PST)
From: Alexandru Elisei <alexandru.elisei@arm.com>
To: drjones@redhat.com, kvm@vger.kernel.org,
        kvmarm@lists.cs.columbia.edu
Cc: andre.przywara@arm.com
Subject: [kvm-unit-tests PATCH v3 00/11] GIC fixes and improvements
Date: Fri, 29 Jan 2021 16:36:36 +0000
Message-Id: <20210129163647.91564-1-alexandru.elisei@arm.com>
X-Mailer: git-send-email 2.30.0
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

What started this series is Andre's SPI and group interrupts tests [1],
which prompted me to attempt to rewrite check_acked() so it's more flexible
and not so complicated to review. When I was doing that I noticed that the
message passing pattern for accesses to the acked, bad_irq and bad_sender
arrays didn't look quite right, and that turned into the first 7 patches of
the series. Even though the diffs are relatively small, they are not
trivial and the reviewer can skip them for the more palatable patches that
follow. I would still appreciate someone having a look at the memory
ordering fixes.

Patch #8 ("Split check_acked() into two functions") is where check_acked()
is reworked with an eye towards supporting different timeout values or
silent reporting without adding too many arguments to check_acked().

After changing the IPI tests, I turned my attention to the LPI tests, which
followed the same memory synchronization patterns, but invented their own
interrupt handler and testing functions. Instead of redoing the work that I
did for the IPI tests, I decided to convert the LPI tests to use the same
infrastructure.

For v2, I ran tests on the following machines and didn't see any issues:

- Ampere EMAG: all arm64 tests 10,000+ times (combined) under qemu and
  kvmtool.

- rockpro64: the arm GICv2 and GICv3 tests 10,000+ times under kvmtool (I
  chose kvmtool because it's faster than qemu); the arm64 gic tests (GICv2
  and GICv3) 5000+ times with qemu (didn't realize that ./run_tests.sh -g
  gic doesn't include the its tests); the arm64 GICv2 and GICv3 and ITS
  tests under kvmtool 13,000+ times.

For v3, because the changes weren't too big, I ran ./run_tests.sh for arm
and arm64 with qemu TCG on the my x86 machine; ran ./run_tests.sh for arm64
on rockpro64; and ran all the gic tests for arm and arm64 under kvmtool on
the rockpro64.

Changes in v3:

* Gathered Reviewed-by tags, thank you for the feedback!

* Reworked patch #2 and renamed it to "lib: arm/arm64: gicv2: Document
  existing barriers when sending IPIs". The necessary barriers were already in
  place in writel/readl. Dropped the R-b tag.

* Removed the GICv2 smp_rmb() barrier in #4 ("arm/arm64: gic: Remove unnecessary
  synchronization with stats_reset") because of the rmb() already present in
  readl() and reworded the commit message accordingly. Dropped the R-b tag.

* Commented the extra delay in wait_for_interrupts() for patch #8
  ("arm/arm64: gic: Split check_acked() into two functions").

* Minor change to the commit message for #10 ("arm64: gic: its-trigger:
  Don't trigger the LPI while it is pending") as per Andre's suggestion.

* Dropped patch #11 ("lib: arm64: gic-v3-its: Add wmb() barrier before INT
  command") because the wmb() was already present in __its_send_int() ->
  its_send_single_command() -> its_post_commands() -> writeq().

Changes in v2:

* Gathered Reviewed-by tags, thank you for the feedback!

* Modified code comments in #1 ("lib: arm/arm64: gicv3: Add missing barrier
  when sending IPIs") as per review suggestions.

* Moved the barrier() in gicv2_ipi_send_self() from #3 ("arm/arm64: gic:
  Remove memory synchronization from ipi_clear_active_handler()") to #2
  ("lib: arm/arm64: gicv2: Add missing barrier when sending IPIs").

* Renamed #3, changed "[..] Remove memory synchronization [..]" to
  "[..] Remove SMP synchronization [..]".

* Moved the removal of smp_rmb() from check_spurious() from #5 ("arm/arm64:
  gic: Use correct memory ordering for the IPI test") to patch #7
  ("arm/arm64: gic: Wait for writes to acked or spurious to complete").

* Fixed typos in #8 ("arm/arm64: gic: Split check_acked() into two
  functions").

* Patch #10 ("arm64: gic: its-trigger: Don't trigger the LPI while it is
  pending") is new. It was added to fix an issue found in v1 [2].

* Patch #11 ("lib: arm64: gic-v3-its: Add wmb() barrier before INT
  command") is also new; it was split from #12 ("arm64: gic: Use IPI test
  checking for the LPI tests") following review comments.

* Removed the now redundant call to stats_reset() from its_prerequisites()
  in #12 ("arm64: gic: Use IPI test checking for the LPI tests").

[1] https://lists.cs.columbia.edu/pipermail/kvmarm/2019-November/037853.html
[2] https://www.spinics.net/lists/kvm-arm/msg43628.html

Alexandru Elisei (11):
  lib: arm/arm64: gicv3: Add missing barrier when sending IPIs
  lib: arm/arm64: gicv2: Document existing barriers when sending IPIs
  arm/arm64: gic: Remove SMP synchronization from
    ipi_clear_active_handler()
  arm/arm64: gic: Remove unnecessary synchronization with stats_reset()
  arm/arm64: gic: Use correct memory ordering for the IPI test
  arm/arm64: gic: Check spurious and bad_sender in the active test
  arm/arm64: gic: Wait for writes to acked or spurious to complete
  arm/arm64: gic: Split check_acked() into two functions
  arm/arm64: gic: Make check_acked() more generic
  arm64: gic: its-trigger: Don't trigger the LPI while it is pending
  arm64: gic: Use IPI test checking for the LPI tests

 lib/arm/gic-v2.c |   6 +
 lib/arm/gic-v3.c |   6 +
 arm/gic.c        | 338 +++++++++++++++++++++++++----------------------
 3 files changed, 190 insertions(+), 160 deletions(-)
```
#### [PATCH V3 0/9] vfio virtual address update
##### From: Steve Sistare <steven.sistare@oracle.com>

```c
From patchwork Fri Jan 29 16:54:03 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Steven Sistare <steven.sistare@oracle.com>
X-Patchwork-Id: 12056191
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-14.0 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,UNPARSEABLE_RELAY,
	USER_AGENT_GIT autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id AA184C433E0
	for <kvm@archiver.kernel.org>; Fri, 29 Jan 2021 17:23:21 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 80F7564E02
	for <kvm@archiver.kernel.org>; Fri, 29 Jan 2021 17:23:21 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S232267AbhA2RXU (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Fri, 29 Jan 2021 12:23:20 -0500
Received: from aserp2130.oracle.com ([141.146.126.79]:43214 "EHLO
        aserp2130.oracle.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S229953AbhA2RXG (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 29 Jan 2021 12:23:06 -0500
Received: from pps.filterd (aserp2130.oracle.com [127.0.0.1])
        by aserp2130.oracle.com (8.16.0.42/8.16.0.42) with SMTP id
 10THAU2Z084667;
        Fri, 29 Jan 2021 17:22:23 GMT
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=oracle.com;
 h=from : to : cc :
 subject : date : message-id; s=corp-2020-01-29;
 bh=qNS/ux2mvp4CbiboRHQeseZysbcuTCPocxxY/OI6R0Q=;
 b=vAMr0svoOw+xCEb+PJEhCk2jmFIpzpj8/tldM9xx3owHEBG1D4zXfbfflMBVwi+yHMz9
 uu7U+EmyuOViinmZz5N9FCqqPiFW32T6y0HOuBK5oTZLJp+6nhKbINRieO/YcKFZFe6a
 csxOPny/Hbw5laN7006R5FnV5m/Adj97GTdKsObdWtdK2ksO+dvsoArvMZ1uumVSsROn
 kjl/97NdMljWWFkO5xjW9/Ig9f2RTT5zq1cK/cqQAF/GHeK7dd4K30HmN9iu+jRRhM4J
 IbvyWHVjhJpEsjtpTbVLlMoWuYK0R/1lMkGjk8bez4YnwOWBIw+hvqrp9wjv3+gwT/xo MA==
Received: from userp3030.oracle.com (userp3030.oracle.com [156.151.31.80])
        by aserp2130.oracle.com with ESMTP id 3689ab2kff-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Fri, 29 Jan 2021 17:22:22 +0000
Received: from pps.filterd (userp3030.oracle.com [127.0.0.1])
        by userp3030.oracle.com (8.16.0.42/8.16.0.42) with SMTP id
 10TH6KIc192628;
        Fri, 29 Jan 2021 17:22:20 GMT
Received: from aserv0121.oracle.com (aserv0121.oracle.com [141.146.126.235])
        by userp3030.oracle.com with ESMTP id 368wr26wpv-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Fri, 29 Jan 2021 17:22:20 +0000
Received: from abhmp0014.oracle.com (abhmp0014.oracle.com [141.146.116.20])
        by aserv0121.oracle.com (8.14.4/8.13.8) with ESMTP id 10THMJwf019124;
        Fri, 29 Jan 2021 17:22:19 GMT
Received: from ca-dev63.us.oracle.com (/10.211.8.221)
        by default (Oracle Beehive Gateway v4.0)
        with ESMTP ; Fri, 29 Jan 2021 09:22:19 -0800
From: Steve Sistare <steven.sistare@oracle.com>
To: kvm@vger.kernel.org
Cc: Alex Williamson <alex.williamson@redhat.com>,
        Cornelia Huck <cohuck@redhat.com>,
        Kirti Wankhede <kwankhede@nvidia.com>,
        Steve Sistare <steven.sistare@oracle.com>
Subject: [PATCH V3 0/9] vfio virtual address update
Date: Fri, 29 Jan 2021 08:54:03 -0800
Message-Id: <1611939252-7240-1-git-send-email-steven.sistare@oracle.com>
X-Mailer: git-send-email 1.8.3.1
X-Proofpoint-IMR: 1
X-Proofpoint-Virus-Version: vendor=nai engine=6200 definitions=9879
 signatures=668683
X-Proofpoint-Spam-Details: rule=notspam policy=default score=0 mlxscore=0
 spamscore=0 phishscore=0
 adultscore=0 mlxlogscore=999 malwarescore=0 suspectscore=0 bulkscore=0
 classifier=spam adjust=0 reason=mlx scancount=1 engine=8.12.0-2009150000
 definitions=main-2101290084
X-Proofpoint-Virus-Version: vendor=nai engine=6200 definitions=9879
 signatures=668683
X-Proofpoint-Spam-Details: rule=notspam policy=default score=0 malwarescore=0
 adultscore=0
 lowpriorityscore=0 mlxlogscore=999 clxscore=1015 phishscore=0 bulkscore=0
 spamscore=0 priorityscore=1501 mlxscore=0 suspectscore=0 impostorscore=0
 classifier=spam adjust=0 reason=mlx scancount=1 engine=8.12.0-2009150000
 definitions=main-2101290084
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Add interfaces that allow the underlying memory object of an iova range
to be mapped to a new virtual address in the host process:

  - VFIO_DMA_UNMAP_FLAG_VADDR for VFIO_IOMMU_UNMAP_DMA
  - VFIO_DMA_MAP_FLAG_VADDR flag for VFIO_IOMMU_MAP_DMA
  - VFIO_UPDATE_VADDR for VFIO_CHECK_EXTENSION
  - VFIO_DMA_UNMAP_FLAG_ALL for VFIO_IOMMU_UNMAP_DMA
  - VFIO_UNMAP_ALL for VFIO_CHECK_EXTENSION

Unmap-vaddr invalidates the host virtual address in an iova range and blocks
vfio translation of host virtual addresses, but DMA to already-mapped pages
continues.  Map-vaddr updates the base VA and resumes translation.  The
implementation supports iommu type1 and mediated devices.  Unmap-all allows
all ranges to be unmapped or invalidated in a single ioctl, which simplifies
userland code.

This functionality is necessary for live update, in which a host process
such as qemu exec's an updated version of itself, while preserving its
guest and vfio devices.  The process blocks vfio VA translation, exec's
its new self, mmap's the memory object(s) underlying vfio object, updates
the VA, and unblocks translation.  For a working example that uses these
new interfaces, see the QEMU patch series "[PATCH V2] Live Update" at
https://lore.kernel.org/qemu-devel/1609861330-129855-1-git-send-email-steven.sistare@oracle.com

Patches 1-3 define and implement the flag to unmap all ranges.
Patches 4-6 define and implement the flags to update vaddr.
Patches 7-9 add blocking to complete the implementation.

Changes in V2:
 - define a flag for unmap all instead of special range values
 - define the VFIO_UNMAP_ALL extension
 - forbid the combination of unmap-all and get-dirty-bitmap
 - unwind in unmap on vaddr error
 - add a new function to find first dma in a range instead of modifying
   an existing function
 - change names of update flags
 - fix concurrency bugs due to iommu lock being dropped
 - call down from from vfio to a new backend interface instead of up from
   driver to detect container close
 - use wait/wake instead of sleep and polling
 - refine the uapi specification
 - split patches into vfio vs type1

Changes in V3:
 - add vaddr_invalid_count to fix pin_pages race with unmap
 - refactor the wait helper functions
 - traverse dma entries more efficiently in unmap
 - check unmap flag conflicts more explicitly
 - rename some local variables and functions

Steve Sistare (9):
  vfio: option to unmap all
  vfio/type1: unmap cleanup
  vfio/type1: implement unmap all
  vfio: interfaces to update vaddr
  vfio/type1: massage unmap iteration
  vfio/type1: implement interfaces to update vaddr
  vfio: iommu driver notify callback
  vfio/type1: implement notify callback
  vfio/type1: block on invalid vaddr

 drivers/vfio/vfio.c             |   5 +
 drivers/vfio/vfio_iommu_type1.c | 251 +++++++++++++++++++++++++++++++++++-----
 include/linux/vfio.h            |   5 +
 include/uapi/linux/vfio.h       |  27 +++++
 4 files changed, 256 insertions(+), 32 deletions(-)
```
#### [RFC v4 0/3] msi support for platform devices
##### From: Vikas Gupta <vikas.gupta@broadcom.com>

```c
From patchwork Fri Jan 29 17:24:18 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Vikas Gupta <vikas.gupta@broadcom.com>
X-Patchwork-Id: 12056211
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-13.9 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_PATCH,MAILING_LIST_MULTI,MIME_HEADER_CTYPE_ONLY,SPF_HELO_NONE,
	SPF_PASS,T_TVD_MIME_NO_HEADERS,USER_AGENT_GIT autolearn=ham
	autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 6C362C433E0
	for <kvm@archiver.kernel.org>; Fri, 29 Jan 2021 17:25:34 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 2692F64E04
	for <kvm@archiver.kernel.org>; Fri, 29 Jan 2021 17:25:34 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S232465AbhA2RZc (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Fri, 29 Jan 2021 12:25:32 -0500
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:50320 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S232434AbhA2RZQ (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 29 Jan 2021 12:25:16 -0500
Received: from mail-pg1-x542.google.com (mail-pg1-x542.google.com
 [IPv6:2607:f8b0:4864:20::542])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 56344C061574
        for <kvm@vger.kernel.org>; Fri, 29 Jan 2021 09:24:36 -0800 (PST)
Received: by mail-pg1-x542.google.com with SMTP id s23so5875873pgh.11
        for <kvm@vger.kernel.org>; Fri, 29 Jan 2021 09:24:36 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=broadcom.com; s=google;
        h=from:to:cc:subject:date:message-id:in-reply-to:references;
        bh=Y56L5ESqbKSgsZmorDYY4Tp7as6euyhMPar5gxkc4hg=;
        b=hCfvh0h1zrb3T4WFjc0JDqyhC1kEobVL3oYwVl2ghkHv4fXbRTfI6pwbsjhjtq9gz2
         igH2ARLP553DrX3lFpHmlsoLwFpoVKmZcg20gocy1qXzh1TjdS1FOnupH+8jXtMQLFB+
         BWQkbXSGwsGskOp7FM7fOcva/ZzP0KmDmELzM=
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:in-reply-to
         :references;
        bh=Y56L5ESqbKSgsZmorDYY4Tp7as6euyhMPar5gxkc4hg=;
        b=aK4hAvWg677PViS8PupT8tf+kWm3BR0IKYV2uJfB3D3M1HSF5IlIF/vSAaViO6sdq9
         V57j/eYXX/1iqg5f4pkh+B34B8DmZtgv16ozIk0KIgBAmEGfbjxBgLwhqaDhWC6YQT/p
         yu2Oac2WPfodDKV4fywCmnWZHkfcmwmbZpQN/wIESVpD3u0F/3mxmKx6urRHuuzfYuHA
         30dXuVMXwGbjva9gKz2ATYitd/6xf0Nlh8eCa7Ouh4iKyCQJv87ezQnQK8Boe9yAlgpz
         5sw2ByvcTTf2158mjDS/M8eG9HRQtKhrwkGOF+0tAQ7PBykyeOZmwVBJxCLay8DhWMSx
         VC1Q==
X-Gm-Message-State: AOAM533Ul+e5/E8lfhIPnxZjdgj4LR80TcmkN97WCHiiEhiQrwCwmz3j
        GtIHJjVQfu2wCXl0s7qS5bdDOw==
X-Google-Smtp-Source: 
 ABdhPJxGcUHp0g3vRP7FsgsDMBLioX2pUt+Y0LlJQcxVnMyRdxObo/5BohnQhuQV7zWhWySokqpCWg==
X-Received: by 2002:a63:4c10:: with SMTP id z16mr5968276pga.274.1611941075585;
        Fri, 29 Jan 2021 09:24:35 -0800 (PST)
Received: from rahul_yocto_ubuntu18.ibn.broadcom.net ([192.19.234.250])
        by smtp.gmail.com with ESMTPSA id
 w11sm9739016pge.28.2021.01.29.09.24.29
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Fri, 29 Jan 2021 09:24:33 -0800 (PST)
From: Vikas Gupta <vikas.gupta@broadcom.com>
To: eric.auger@redhat.com, alex.williamson@redhat.com,
        cohuck@redhat.com, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org
Cc: vikram.prakash@broadcom.com, srinath.mannam@broadcom.com,
        ashwin.kamath@broadcom.com, zachary.schroff@broadcom.com,
        manish.kurup@broadcom.com, Vikas Gupta <vikas.gupta@broadcom.com>
Subject: [RFC v4 0/3] msi support for platform devices
Date: Fri, 29 Jan 2021 22:54:18 +0530
Message-Id: <20210129172421.43299-1-vikas.gupta@broadcom.com>
X-Mailer: git-send-email 2.17.1
In-Reply-To: <20201214174514.22006-1-vikas.gupta@broadcom.com>
References: <20201214174514.22006-1-vikas.gupta@broadcom.com>
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This RFC adds support for MSI for platform devices.
MSI block is added as an ext irq along with the existing
wired interrupt implementation. The patchset exports two
caps for MSI and related data to configure MSI source device.

Changes from:
-------------
 v3 to v4:
	1) Removed the 'cap' for exporting MSI info to userspace and
	   restored into vedor specific module.
	2) Enable GENERIC_MSI_IRQ_DOMAIN in Kconfig.
	3) Removed the vendor specific, Broadcom, 'msi' module and 
	   integrated the MSI relates ops into the 'reset' module for
	   MSI support.  

 v2 to v3:
	1) Restored the vendor specific module to get max number
	   of MSIs supported and .count value initialized.
	2) Comments from Eric addressed.

 v1 to v2:
	1) IRQ allocation has been implemented as below:
	       ----------------------------
	       |IRQ-0|IRQ-1|....|IRQ-n|MSI|
       	       ----------------------------
		MSI block has msi contexts and its implemneted
		as ext irq.

	2) Removed vendor specific module for msi handling so
	   previously patch2 and patch3 are not required.

	3) MSI related data is exported to userspace using 'caps'.
	 Please note VFIO_IRQ_INFO_CAP_TYPE in include/uapi/linux/vfio.h implementation
	is taken from the Eric`s patch
        https://patchwork.kernel.org/project/kvm/patch/20201116110030.32335-8-eric.auger@redhat.com/


 v0 to v1:
   i)  Removed MSI device flag VFIO_DEVICE_FLAGS_MSI.
   ii) Add MSI(s) at the end of the irq list of platform IRQs.
       MSI(s) with first entry of MSI block has count and flag
       information.
       IRQ list: Allocation for IRQs + MSIs are allocated as below
       Example: if there are 'n' IRQs and 'k' MSIs
       -------------------------------------------------------
       |IRQ-0|IRQ-1|....|IRQ-n|MSI-0|MSI-1|MSI-2|......|MSI-k|
       -------------------------------------------------------
       MSI-0 will have count=k set and flags set accordingly.


Vikas Gupta (3):
  vfio/platform: add support for msi
  vfio/platform: change cleanup order
  vfio: platform: reset: add msi support

 drivers/vfio/platform/Kconfig                 |   1 +
 .../platform/reset/vfio_platform_bcmflexrm.c  |  72 ++++-
 drivers/vfio/platform/vfio_platform_common.c  |  97 +++++--
 drivers/vfio/platform/vfio_platform_irq.c     | 253 ++++++++++++++++--
 drivers/vfio/platform/vfio_platform_private.h |  29 ++
 include/uapi/linux/vfio.h                     |  24 ++
 6 files changed, 444 insertions(+), 32 deletions(-)
```
