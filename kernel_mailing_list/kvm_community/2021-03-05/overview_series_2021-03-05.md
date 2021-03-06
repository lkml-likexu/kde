#### [PATCH 1/1] KVM: x86: to track if L1 is running L2 VM
##### From: Dongli Zhang <dongli.zhang@oracle.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Dongli Zhang <dongli.zhang@oracle.com>
X-Patchwork-Id: 12119521
Return-Path: <SRS0=d8nC=ID=vger.kernel.org=kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-18.8 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,
	INCLUDES_PATCH,MAILING_LIST_MULTI,MSGID_FROM_MTA_HEADER,SPF_HELO_NONE,
	SPF_PASS,USER_AGENT_GIT autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id A05C3C433DB
	for <kvm@archiver.kernel.org>; Fri,  5 Mar 2021 22:59:50 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 618A76509B
	for <kvm@archiver.kernel.org>; Fri,  5 Mar 2021 22:59:50 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S229960AbhCEW7T (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Fri, 5 Mar 2021 17:59:19 -0500
Received: from aserp2120.oracle.com ([141.146.126.78]:38982 "EHLO
        aserp2120.oracle.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S229592AbhCEW7Q (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 5 Mar 2021 17:59:16 -0500
Received: from pps.filterd (aserp2120.oracle.com [127.0.0.1])
        by aserp2120.oracle.com (8.16.0.42/8.16.0.42) with SMTP id
 125MsTL7009080;
        Fri, 5 Mar 2021 22:57:51 GMT
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=oracle.com;
 h=from : to : cc :
 subject : date : message-id : content-type : mime-version;
 s=corp-2020-01-29; bh=eG552gS+s8mTRpTUGVTwlYXu063UV1k981zm7veNB24=;
 b=a3Y+TSFvvA6elxXvwsLDbrapuFc4r2cjsfYk837yVGCHqr40sM/Tmcs75gZwro62u1dX
 bDkh0dG/P1TbGWpLE7D5qOq6Wgp4a2kDCRkK+lA6A/OmqxpmzpxH4tfsuQbderojvE9n
 p49ry4GVpG8oXb2PeZlmOcJWgx2Q55B6dkk2lzobMTX/rZaN3J7ZqGfB7kAa0o/AcnqV
 m8Co/R8euwhfv70P2tIJ6GYtB4LgTUMw5QqHURX8DVkVG2BOdLdwF/7bJ6g9/BKAa2Fy
 3OtKTsOTuzsMpyyJqnnn2GQiKhHWJcjcrLech0bSXBPczk1tbKgLENenK7JI2lWNIG2n Tg==
Received: from aserp3020.oracle.com (aserp3020.oracle.com [141.146.126.70])
        by aserp2120.oracle.com with ESMTP id 3726v7hhf8-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Fri, 05 Mar 2021 22:57:51 +0000
Received: from pps.filterd (aserp3020.oracle.com [127.0.0.1])
        by aserp3020.oracle.com (8.16.0.42/8.16.0.42) with SMTP id
 125MpF0Z025660;
        Fri, 5 Mar 2021 22:57:51 GMT
Received: from nam10-bn7-obe.outbound.protection.outlook.com
 (mail-bn7nam10lp2101.outbound.protection.outlook.com [104.47.70.101])
        by aserp3020.oracle.com with ESMTP id 370004jau1-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Fri, 05 Mar 2021 22:57:51 +0000
ARC-Seal: i=1; a=rsa-sha256; s=arcselector9901; d=microsoft.com; cv=none;
 b=MWGrTWEgGXmGTixtXiVDRJdphn51pLHqJqP/P7g2INAiN74SaiLVX8Vz4XfJF16Sj5F1LUhINudvNJ3566N37mpjTYh8Lbt8eVcbf7AHkYRE6QwLnTHXT25iTCTuJpStjlTaO5pj8p1U8uRQpzL4NB69CK9SjWRXCdg/YEaxpsMSmbIWQXYCre4Pqx4bRHZ7AlZAQUFlW9wkGecBIOJl+b6RHhfSKIWnoH01sA/YcD538qk8hv9JJrEf0GPUyAAXp/9k3mogm9R+664C1KOkQPd2VXZX+LfsLzayViDdDN2u28PSVf4YyN4KbFuHUPhkgZU6tuGnhy/pFGFfHQJgkQ==
ARC-Message-Signature: i=1; a=rsa-sha256; c=relaxed/relaxed; d=microsoft.com;
 s=arcselector9901;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=eG552gS+s8mTRpTUGVTwlYXu063UV1k981zm7veNB24=;
 b=UvfxMDJsOj5n+QzSdJE7LzybOLmzSV93H5mPJb1o1v5xF0ZLq9GODclFrORX3tlALdzeqMoX/XIP2aeKmTFTjMre5t57lEJ12GoHRojiEk0SjzcnwSuqBAg6ttI6RxvZ7X37UZC4iU2yX8oikfFao1So0KWBfxttQaA4MBVePVmzTcnquZiv6kZfI/oejwQW4bXs1ZEkYns+e8viZEvXcTqePa3Zo/sNSzGCcOkt/RhyetUQeEwqzFCg1TUtbchD5kMI7zpnK8NNGqnPJUFXZ8yxiKfI7UTDi7t2HIy+EhnnfHI8Z/LMkjFGivVbnpDBFezliorP4f6+u9dEiMIG/A==
ARC-Authentication-Results: i=1; mx.microsoft.com 1; spf=pass
 smtp.mailfrom=oracle.com; dmarc=pass action=none header.from=oracle.com;
 dkim=pass header.d=oracle.com; arc=none
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
 d=oracle.onmicrosoft.com; s=selector2-oracle-onmicrosoft-com;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=eG552gS+s8mTRpTUGVTwlYXu063UV1k981zm7veNB24=;
 b=WxWPMmFOewYwj6E+Xgq21ZFqb492ZrOYD+3Wwedwvt1SBYIP8O+HXHQ0gNN1LtMl5IO9+emfZksNrSQaXsLTlVim2pCVOzFASZ4JATdWsUDZKyc0RiLsuH2J32OAU6QYOGQ9tZCLy/uI9dHtbKmutYMyqWeJdI++Vad3H9FBHNw=
Authentication-Results: kernel.org; dkim=none (message not signed)
 header.d=none;kernel.org; dmarc=none action=none header.from=oracle.com;
Received: from BYAPR10MB2663.namprd10.prod.outlook.com (2603:10b6:a02:a9::20)
 by BYAPR10MB2742.namprd10.prod.outlook.com (2603:10b6:a02:b0::26) with
 Microsoft SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.3890.22; Fri, 5 Mar
 2021 22:57:49 +0000
Received: from BYAPR10MB2663.namprd10.prod.outlook.com
 ([fe80::b52e:bdd3:d193:4d14]) by BYAPR10MB2663.namprd10.prod.outlook.com
 ([fe80::b52e:bdd3:d193:4d14%7]) with mapi id 15.20.3846.041; Fri, 5 Mar 2021
 22:57:49 +0000
From: Dongli Zhang <dongli.zhang@oracle.com>
To: x86@kernel.org, kvm@vger.kernel.org
Cc: pbonzini@redhat.com, seanjc@google.com, vkuznets@redhat.com,
        wanpengli@tencent.com, jmattson@google.com, joro@8bytes.org,
        tglx@linutronix.de, mingo@redhat.com, bp@alien8.de, hpa@zytor.com,
        linux-kernel@vger.kernel.org, joe.jin@oracle.com
Subject: [PATCH 1/1] KVM: x86: to track if L1 is running L2 VM
Date: Fri,  5 Mar 2021 14:57:47 -0800
Message-Id: <20210305225747.7682-1-dongli.zhang@oracle.com>
X-Mailer: git-send-email 2.17.1
X-Originating-IP: [138.3.200.16]
X-ClientProxiedBy: SN4PR0701CA0024.namprd07.prod.outlook.com
 (2603:10b6:803:28::34) To BYAPR10MB2663.namprd10.prod.outlook.com
 (2603:10b6:a02:a9::20)
MIME-Version: 1.0
X-MS-Exchange-MessageSentRepresentingType: 1
Received: from localhost.localdomain (138.3.200.16) by
 SN4PR0701CA0024.namprd07.prod.outlook.com (2603:10b6:803:28::34) with
 Microsoft SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.3912.17 via Frontend
 Transport; Fri, 5 Mar 2021 22:57:47 +0000
X-MS-PublicTrafficType: Email
X-MS-Office365-Filtering-Correlation-Id: 894606b0-6729-4317-9436-08d8e02a1945
X-MS-TrafficTypeDiagnostic: BYAPR10MB2742:
X-MS-Exchange-Transport-Forked: True
X-Microsoft-Antispam-PRVS: 
 <BYAPR10MB274264D9DEB10303CCE5C0C0F0969@BYAPR10MB2742.namprd10.prod.outlook.com>
X-MS-Oob-TLC-OOBClassifiers: OLM:1186;
X-MS-Exchange-SenderADCheck: 1
X-Microsoft-Antispam: BCL:0;
X-Microsoft-Antispam-Message-Info: 
 E7CncNV9t2TppYZJZZrroOZhXQg/CNO6Tj78frrvPGKvLuYXd8LI7mGWWuk4nWO/hA4IAxvzcEDFRKeGI+ajv9PWvJrDTxPmpA7nHMuk84oBF73Ffqh2tjcK6PNxaA+bsXh6TDFZ/Nk9FfDEVukZ7l+NEcVJ3reWk8dwhpmCLHL4tn349WrobQuBRIml0s8y6ehwAJhaanmXMt2Zo7GMKrsG695MHWm9+mIyAu2ljpxLmwmejCJmNHNMot6RitMq5+6jUodoJnUL9oRD0fNE1nq3PPFKWVrWBNyEk2iO4wvWb9HSeya/8QgvNYB7wEYIYxbHOQyBXV5a3nbj+JL/oPQNERev9dNn35bYeo8ZpratRJOavXbSnoq2iXGpHfWcbbwIRxWisvFxe6Hoce/ktkLrPMSq2ocOz92v26NwqWjwtZKTqxm5kdLRp0oCm/8r0vIl6PNg/J3qL4LD0L1c8YmZ/TmDO5g34lM2f+ZdAI249U+4jz8eztrQAZDwvcgzbQzZ4//HmqQSlWSetiDZjYPxHo+UqO4RV9pU01ULMwv6x9E/wE58ra8ykTcWMkYGFN83qVkUGlUrxt6++yuwqA==
X-Forefront-Antispam-Report: 
 CIP:255.255.255.255;CTRY:;LANG:en;SCL:1;SRV:;IPV:NLI;SFV:NSPM;H:BYAPR10MB2663.namprd10.prod.outlook.com;PTR:;CAT:NONE;SFS:(396003)(376002)(366004)(346002)(136003)(39860400002)(52116002)(956004)(69590400012)(1076003)(16526019)(186003)(8936002)(36756003)(44832011)(4326008)(2616005)(26005)(2906002)(6512007)(6486002)(66946007)(478600001)(107886003)(7416002)(66476007)(66556008)(83380400001)(316002)(6506007)(5660300002)(86362001)(8676002);DIR:OUT;SFP:1101;
X-MS-Exchange-AntiSpam-MessageData: 
 39158CwicCRpdgUKM89az58mFfU/nkHBI1yncdxAd725vgqqnyZcbx855nZbj1d5/7EuiYYIwCE6xQ0Z2LihVIgl6GEf0sgpQkKJ5FrfBpO2nz48wxuE9vr6YHS88E5BhCWrqbF6/OFFeTf5gH5MKsIITL881KZkGLKFDa+FbFhhwwRoJLMDQ4XkiV72hMd7p1xjx+EbS5j/ndOq0SS7wWQp6umd4QMOVNPLeOMrh3osuFXF8/FU3T+/nRSpZhy4moMVbEF+sGaCFVuMGfmvztokJnP/Gv1BSzkeRC5JntQYtd4xkII/6DHUOGad9qWapv+/2B1uGzOnytmya6tY16T0YOhq0W5mYdqBveMAj6U2RuvVXHDzCbttOdlg9LUAU7ccwcz+B8oIBEHrhBVs8aNWq8yoplSCt7U/uoozgz8vYVIDnuJdPxBd+m7XR+4rGgSH1VHqbkj3mWKfAPhS16w4LV19Zchxgn5zgH5Ca2lNFVxPlxz74/d7qvApqVnNIhPqmt1PBF4Ejb93saamZLOFIHbpronsDIA7bvdKwLvjcLaE9w4yTyjUIpOzXYM9AlUsMCgq2ctFo4olJ0vt5QX4I8kqfTv+MubkwQphkypAd3QuOh+DdhOT8FpnYWkU2nNNcqhM1kwRpssNej6nvY7mEmL5OzHXYUGJCMaiFHPWb6pyxd81KH3DcBQMQ9LXn+0nAyUkL2afAkyL+8gzstg5MdjtnnFgf2MAIA53hboOizODQrtyiOfv3Jan3d3YM/aMwcEXmvC/hr36JFV9tao+ZPkba7cw4xYQpMfy0AwAWlS5fXdFGZxrcjzO7KQUlWgVDsaZoeuoVK3VJi5likqOUtX758lTrJZiYPz3aVECOB/LcdpbN+G0BvFk30C050RJxeNyIDtsQKt+P8hIt9BQPoECHtKFN7FiTcBJY6Hx9/bOyAiyu2BtxrLhXtPYVoB6krNyPpup1jRo7/CUwdQ9pKEbnEaBZiHGpNh+k7pnumB0ojzadlnB1Ddzjtv2KIVuyHs35qhnxkf8BlhCm+H2jsoxnIeAHlc17gSEI5BHqSygB3ajM3r2UmQtu984Jw1XLtFsT4YOqdqPpGki6uCHLQy7FHfgO4Uxcz5qQMpyLOdDQz6y5ws7kNVaJWCM5aZDaParc+OxCWQ1D2NTzTDuoRAFpNPio63hKTdoQE7sh/Bpp1Tv+kPA5Q3iQWhFLOiT7vK0wcCCMJUIc2Au+ud5j6uri7wwdPjMpxQG/e3b0a++DEiR95w2NXSN9gGlCS5Mx9WOfLJ5awdf4MKZCZxx9j0jGcIItRbTR7nYRY6Hjlh6IdMqfubq3Qr39GBB
X-OriginatorOrg: oracle.com
X-MS-Exchange-CrossTenant-Network-Message-Id: 
 894606b0-6729-4317-9436-08d8e02a1945
X-MS-Exchange-CrossTenant-AuthSource: BYAPR10MB2663.namprd10.prod.outlook.com
X-MS-Exchange-CrossTenant-AuthAs: Internal
X-MS-Exchange-CrossTenant-OriginalArrivalTime: 05 Mar 2021 22:57:49.1782
 (UTC)
X-MS-Exchange-CrossTenant-FromEntityHeader: Hosted
X-MS-Exchange-CrossTenant-Id: 4e2c6054-71cb-48f1-bd6c-3a9705aca71b
X-MS-Exchange-CrossTenant-MailboxType: HOSTED
X-MS-Exchange-CrossTenant-UserPrincipalName: 
 Lu/BGNv15W91dPugzB4miA43bbqQ4WF2Tv5maNov1/koXevhkwejudhMsJHu1Nb8Lp7RswK4odCq8xWqLxLivA==
X-MS-Exchange-Transport-CrossTenantHeadersStamped: BYAPR10MB2742
X-Proofpoint-Virus-Version: vendor=nai engine=6200 definitions=9914
 signatures=668683
X-Proofpoint-Spam-Details: rule=notspam policy=default score=0 adultscore=0
 mlxlogscore=999
 phishscore=0 bulkscore=0 mlxscore=0 spamscore=0 suspectscore=0
 malwarescore=0 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.12.0-2009150000 definitions=main-2103050117
X-Proofpoint-Virus-Version: vendor=nai engine=6200 definitions=9914
 signatures=668683
X-Proofpoint-Spam-Details: rule=notspam policy=default score=0 impostorscore=0
 phishscore=0 mlxscore=0
 suspectscore=0 adultscore=0 malwarescore=0 priorityscore=1501 bulkscore=0
 lowpriorityscore=0 spamscore=0 mlxlogscore=999 clxscore=1015
 classifier=spam adjust=0 reason=mlx scancount=1 engine=8.12.0-2009150000
 definitions=main-2103050117
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The new per-cpu stat 'nested_run' is introduced in order to track if L1 VM
is running or used to run L2 VM.

An example of the usage of 'nested_run' is to help the host administrator
to easily track if any L1 VM is used to run L2 VM. Suppose there is issue
that may happen with nested virtualization, the administrator will be able
to easily narrow down and confirm if the issue is due to nested
virtualization via 'nested_run'. For example, whether the fix like
commit 88dddc11a8d6 ("KVM: nVMX: do not use dangling shadow VMCS after
guest reset") is required.

Cc: Joe Jin <joe.jin@oracle.com>
Signed-off-by: Dongli Zhang <dongli.zhang@oracle.com>
---
 arch/x86/include/asm/kvm_host.h | 1 +
 arch/x86/kvm/svm/nested.c       | 2 ++
 arch/x86/kvm/vmx/nested.c       | 2 ++
 arch/x86/kvm/x86.c              | 1 +
 4 files changed, 6 insertions(+)

```
#### [PATCH 1/8] KVM: arm64: nvhe: Save the SPE context early
##### From: Marc Zyngier <maz@kernel.org>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Marc Zyngier <maz@kernel.org>
X-Patchwork-Id: 12119319
Return-Path: <SRS0=d8nC=ID=vger.kernel.org=kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No,
 score=-17.0 required=3.0 tests=BAYES_00,INCLUDES_CR_TRAILER,
	INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED,
	USER_AGENT_GIT autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 9DFF1C433E6
	for <kvm@archiver.kernel.org>; Fri,  5 Mar 2021 18:53:57 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 2BB7865090
	for <kvm@archiver.kernel.org>; Fri,  5 Mar 2021 18:53:57 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S229818AbhCESxZ (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Fri, 5 Mar 2021 13:53:25 -0500
Received: from mail.kernel.org ([198.145.29.99]:58190 "EHLO mail.kernel.org"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S229493AbhCESxB (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 5 Mar 2021 13:53:01 -0500
Received: from disco-boy.misterjones.org (disco-boy.misterjones.org
 [51.254.78.96])
        (using TLSv1.2 with cipher ECDHE-RSA-AES256-GCM-SHA384 (256/256 bits))
        (No client certificate requested)
        by mail.kernel.org (Postfix) with ESMTPSA id 055DF6509A;
        Fri,  5 Mar 2021 18:53:01 +0000 (UTC)
Received: from 78.163-31-62.static.virginmediabusiness.co.uk ([62.31.163.78]
 helo=why.lan)
        by disco-boy.misterjones.org with esmtpsa  (TLS1.3) tls
 TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384
        (Exim 4.94)
        (envelope-from <maz@kernel.org>)
        id 1lIFZL-00HYFA-9w; Fri, 05 Mar 2021 18:52:59 +0000
From: Marc Zyngier <maz@kernel.org>
To: Paolo Bonzini <pbonzini@redhat.com>
Cc: Alexandru Elisei <alexandru.elisei@arm.com>,
        Andre Przywara <andre.przywara@arm.com>,
        Andrew Scull <ascull@google.com>,
        Catalin Marinas <catalin.marinas@arm.com>,
        Christoffer Dall <christoffer.dall@arm.com>,
        Howard Zhang <Howard.Zhang@arm.com>,
        Jia He <justin.he@arm.com>,
        Mark Rutland <mark.rutland@arm.com>,
        Quentin Perret <qperret@google.com>,
        Shameerali Kolothum Thodi
        <shameerali.kolothum.thodi@huawei.com>,
        Suzuki K Poulose <suzuki.poulose@arm.com>,
        Will Deacon <will@kernel.org>,
        James Morse <james.morse@arm.com>,
        Julien Thierry <julien.thierry.kdev@gmail.com>,
        kernel-team@android.com, linux-arm-kernel@lists.infradead.org,
        kvmarm@lists.cs.columbia.edu, kvm@vger.kernel.org,
        stable@vger.kernel.org
Subject: [PATCH 1/8] KVM: arm64: nvhe: Save the SPE context early
Date: Fri,  5 Mar 2021 18:52:47 +0000
Message-Id: <20210305185254.3730990-2-maz@kernel.org>
X-Mailer: git-send-email 2.29.2
In-Reply-To: <20210305185254.3730990-1-maz@kernel.org>
References: <87eegtzbch.wl-maz@kernel.org>
 <20210305185254.3730990-1-maz@kernel.org>
MIME-Version: 1.0
X-SA-Exim-Connect-IP: 62.31.163.78
X-SA-Exim-Rcpt-To: pbonzini@redhat.com, alexandru.elisei@arm.com,
 andre.przywara@arm.com, ascull@google.com, catalin.marinas@arm.com,
 christoffer.dall@arm.com, Howard.Zhang@arm.com, justin.he@arm.com,
 mark.rutland@arm.com, qperret@google.com,
 shameerali.kolothum.thodi@huawei.com, suzuki.poulose@arm.com,
 will@kernel.org, james.morse@arm.com, julien.thierry.kdev@gmail.com,
 kernel-team@android.com, linux-arm-kernel@lists.infradead.org,
 kvmarm@lists.cs.columbia.edu, kvm@vger.kernel.org, stable@vger.kernel.org
X-SA-Exim-Mail-From: maz@kernel.org
X-SA-Exim-Scanned: No (on disco-boy.misterjones.org);
 SAEximRunCond expanded to false
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Suzuki K Poulose <suzuki.poulose@arm.com>

The nVHE KVM hyp drains and disables the SPE buffer, before
entering the guest, as the EL1&0 translation regime
is going to be loaded with that of the guest.

But this operation is performed way too late, because :
  - The owning translation regime of the SPE buffer
    is transferred to EL2. (MDCR_EL2_E2PB == 0)
  - The guest Stage1 is loaded.

Thus the flush could use the host EL1 virtual address,
but use the EL2 translations instead of host EL1, for writing
out any cached data.

Fix this by moving the SPE buffer handling early enough.
The restore path is doing the right thing.

Fixes: 014c4c77aad7 ("KVM: arm64: Improve debug register save/restore flow")
Cc: stable@vger.kernel.org
Cc: Christoffer Dall <christoffer.dall@arm.com>
Cc: Marc Zyngier <maz@kernel.org>
Cc: Will Deacon <will@kernel.org>
Cc: Catalin Marinas <catalin.marinas@arm.com>
Cc: Mark Rutland <mark.rutland@arm.com>
Cc: Alexandru Elisei <alexandru.elisei@arm.com>
Reviewed-by: Alexandru Elisei <alexandru.elisei@arm.com>
Signed-off-by: Suzuki K Poulose <suzuki.poulose@arm.com>
Signed-off-by: Marc Zyngier <maz@kernel.org>
Link: https://lore.kernel.org/r/20210302120345.3102874-1-suzuki.poulose@arm.com
---
 arch/arm64/include/asm/kvm_hyp.h   |  5 +++++
 arch/arm64/kvm/hyp/nvhe/debug-sr.c | 12 ++++++++++--
 arch/arm64/kvm/hyp/nvhe/switch.c   | 11 ++++++++++-
 3 files changed, 25 insertions(+), 3 deletions(-)

```
#### [PATCH v2 7/9] memory: introduce RAM_NORESERVE and wire it up in qemu_ram_mmap()
##### From: David Hildenbrand <david@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: David Hildenbrand <david@redhat.com>
X-Patchwork-Id: 12118261
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-15.8 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_CR_TRAILER,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,
	URIBL_BLOCKED autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 7699AC433DB
	for <kvm@archiver.kernel.org>; Fri,  5 Mar 2021 10:19:02 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 3F7E464EDF
	for <kvm@archiver.kernel.org>; Fri,  5 Mar 2021 10:19:02 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S229650AbhCEKS3 (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Fri, 5 Mar 2021 05:18:29 -0500
Received: from us-smtp-delivery-124.mimecast.com ([216.205.24.124]:60975 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S229604AbhCEKSG (ORCPT
        <rfc822;kvm@vger.kernel.org>); Fri, 5 Mar 2021 05:18:06 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1614939485;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding:
         in-reply-to:in-reply-to:references:references;
        bh=0w5JhCDF+sw1F+91O5Td776BOt0OpplL59R7NkVJgi0=;
        b=BU+znGjgORfMooxldmBZzwuT673w73kVusne5/SeqFwDm3BjugZZUUC4vFw/tsCejM8by5
        gD9pJj1zHytEFTGqMpA6xmGpIZZeh+LCN0XMKPwFXIf4/B0uxUSZKQj0bM5hRGHPAc0y8y
        k+SuqVke+nuccduQ/S0VPxvxS2GhE+o=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-485-8CQB5JkxP02930uk4h9sCA-1; Fri, 05 Mar 2021 05:18:01 -0500
X-MC-Unique: 8CQB5JkxP02930uk4h9sCA-1
Received: from smtp.corp.redhat.com (int-mx07.intmail.prod.int.phx2.redhat.com
 [10.5.11.22])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 30AD06409C;
        Fri,  5 Mar 2021 10:17:59 +0000 (UTC)
Received: from t480s.redhat.com (ovpn-112-194.ams2.redhat.com [10.36.112.194])
        by smtp.corp.redhat.com (Postfix) with ESMTP id EE277101E39C;
        Fri,  5 Mar 2021 10:17:54 +0000 (UTC)
From: David Hildenbrand <david@redhat.com>
To: qemu-devel@nongnu.org
Cc: David Hildenbrand <david@redhat.com>, Peter Xu <peterx@redhat.com>,
 "Michael S. Tsirkin" <mst@redhat.com>, Eduardo Habkost <ehabkost@redhat.com>,
 "Dr. David Alan Gilbert" <dgilbert@redhat.com>,
 Richard Henderson <richard.henderson@linaro.org>,
 Paolo Bonzini <pbonzini@redhat.com>, Igor Mammedov <imammedo@redhat.com>,
	=?utf-8?q?Philippe_Mathieu-Daud=C3=A9?= <philmd@redhat.com>,
 Stefan Hajnoczi <stefanha@redhat.com>,
 Murilo Opsfelder Araujo <muriloo@linux.ibm.com>, Greg Kurz <groug@kaod.org>,
 Liam Merwick <liam.merwick@oracle.com>,
 Christian Borntraeger <borntraeger@de.ibm.com>,
 Cornelia Huck <cohuck@redhat.com>, Halil Pasic <pasic@linux.ibm.com>,
 Igor Kotrasinski <i.kotrasinsk@partner.samsung.com>,
 Juan Quintela <quintela@redhat.com>, Stefan Weil <sw@weilnetz.de>,
 Thomas Huth <thuth@redhat.com>, kvm@vger.kernel.org, qemu-s390x@nongnu.org
Subject: [PATCH v2 7/9] memory: introduce RAM_NORESERVE and wire it up in
 qemu_ram_mmap()
Date: Fri,  5 Mar 2021 11:16:32 +0100
Message-Id: <20210305101634.10745-8-david@redhat.com>
In-Reply-To: <20210305101634.10745-1-david@redhat.com>
References: <20210305101634.10745-1-david@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.84 on 10.5.11.22
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Let's introduce RAM_NORESERVE, allowing mmap'ing with MAP_NORESERVE. The
new flag has the following semantics:

  RAM is mmap-ed with MAP_NORESERVE. When set, reserving swap space (or
  huge pages on Linux) is skipped: will bail out if not supported. When not
  set, the OS might reserve swap space (or huge pages on Linux), depending
  on OS support.

Allow passing it into:
- memory_region_init_ram_nomigrate()
- memory_region_init_resizeable_ram()
- memory_region_init_ram_from_file()

... and teach qemu_ram_mmap() and qemu_anon_ram_alloc() about the flag.
Bail out if the flag is not supported, which is the case right now for
both, POSIX and win32. We will add the POSIX mmap implementation next and
allow specifying RAM_NORESERVE via memory backends.

The target use case is virtio-mem, which dynamically exposes memory
inside a large, sparse memory area to the VM.

Cc: Juan Quintela <quintela@redhat.com>
Cc: Halil Pasic <pasic@linux.ibm.com>
Cc: Cornelia Huck <cohuck@redhat.com>
Cc: Christian Borntraeger <borntraeger@de.ibm.com>
Cc: Thomas Huth <thuth@redhat.com>
Cc: Stefan Weil <sw@weilnetz.de>
Cc: kvm@vger.kernel.org
Cc: qemu-s390x@nongnu.org
Signed-off-by: David Hildenbrand <david@redhat.com>
Reviewed-by: Peter Xu <peterx@redhat.com>
---
 include/exec/cpu-common.h |  1 +
 include/exec/memory.h     | 16 +++++++++++++---
 include/exec/ram_addr.h   |  3 ++-
 include/qemu/mmap-alloc.h |  2 ++
 include/qemu/osdep.h      |  3 ++-
 migration/ram.c           |  3 +--
 softmmu/physmem.c         | 16 +++++++++++-----
 util/mmap-alloc.c         |  7 +++++++
 util/oslib-posix.c        |  6 ++++--
 util/oslib-win32.c        | 13 ++++++++++++-
 10 files changed, 55 insertions(+), 15 deletions(-)

```
#### [GIT PULL] KVM/arm64 fixes for 5.12, take #1
##### From: Marc Zyngier <maz@kernel.org>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Marc Zyngier <maz@kernel.org>
X-Patchwork-Id: 12118867
Return-Path: <SRS0=d8nC=ID=vger.kernel.org=kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-22.0 required=3.0 tests=BAYES_00,INCLUDES_PATCH,
	INCLUDES_PULL_REQUEST,MAILING_LIST_MULTI,MENTIONS_GIT_HOSTING,SPF_HELO_NONE,
	SPF_PASS,USER_AGENT_GIT autolearn=unavailable autolearn_force=no
 version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id B6CB2C433DB
	for <kvm@archiver.kernel.org>; Fri,  5 Mar 2021 16:50:29 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 7731264F60
	for <kvm@archiver.kernel.org>; Fri,  5 Mar 2021 16:50:29 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S230130AbhCEQt5 (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Fri, 5 Mar 2021 11:49:57 -0500
Received: from mail.kernel.org ([198.145.29.99]:41998 "EHLO mail.kernel.org"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S229882AbhCEQt4 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 5 Mar 2021 11:49:56 -0500
Received: from disco-boy.misterjones.org (disco-boy.misterjones.org
 [51.254.78.96])
        (using TLSv1.2 with cipher ECDHE-RSA-AES256-GCM-SHA384 (256/256 bits))
        (No client certificate requested)
        by mail.kernel.org (Postfix) with ESMTPSA id A88946508B;
        Fri,  5 Mar 2021 16:49:55 +0000 (UTC)
Received: from 78.163-31-62.static.virginmediabusiness.co.uk ([62.31.163.78]
 helo=why.lan)
        by disco-boy.misterjones.org with esmtpsa  (TLS1.3) tls
 TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384
        (Exim 4.94)
        (envelope-from <maz@kernel.org>)
        id 1lIDeD-00HWzC-DC; Fri, 05 Mar 2021 16:49:53 +0000
From: Marc Zyngier <maz@kernel.org>
To: Paolo Bonzini <pbonzini@redhat.com>
Cc: Alexandru Elisei <alexandru.elisei@arm.com>,
        Andre Przywara <andre.przywara@arm.com>,
        Andrew Scull <ascull@google.com>,
        Catalin Marinas <catalin.marinas@arm.com>,
        Christoffer Dall <christoffer.dall@arm.com>,
        Howard Zhang <Howard.Zhang@arm.com>,
        Jia He <justin.he@arm.com>,
        Mark Rutland <mark.rutland@arm.com>,
        Quentin Perret <qperret@google.com>,
        Shameerali Kolothum Thodi
        <shameerali.kolothum.thodi@huawei.com>,
        Suzuki K Poulose <suzuki.poulose@arm.com>,
        Will Deacon <will@kernel.org>,
        James Morse <james.morse@arm.com>,
        Julien Thierry <julien.thierry.kdev@gmail.com>,
        kernel-team@android.com, linux-arm-kernel@lists.infradead.org,
        kvmarm@lists.cs.columbia.edu, kvm@vger.kernel.org
Subject: [GIT PULL] KVM/arm64 fixes for 5.12, take #1
Date: Fri,  5 Mar 2021 16:49:43 +0000
Message-Id: <20210305164944.3729910-1-maz@kernel.org>
X-Mailer: git-send-email 2.29.2
MIME-Version: 1.0
X-SA-Exim-Connect-IP: 62.31.163.78
X-SA-Exim-Rcpt-To: pbonzini@redhat.com, alexandru.elisei@arm.com,
 andre.przywara@arm.com, ascull@google.com, catalin.marinas@arm.com,
 christoffer.dall@arm.com, Howard.Zhang@arm.com, justin.he@arm.com,
 mark.rutland@arm.com, qperret@google.com,
 shameerali.kolothum.thodi@huawei.com, suzuki.poulose@arm.com,
 will@kernel.org, james.morse@arm.com, julien.thierry.kdev@gmail.com,
 kernel-team@android.com, linux-arm-kernel@lists.infradead.org,
 kvmarm@lists.cs.columbia.edu, kvm@vger.kernel.org
X-SA-Exim-Mail-From: maz@kernel.org
X-SA-Exim-Scanned: No (on disco-boy.misterjones.org);
 SAEximRunCond expanded to false
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Hi Paolo,

Here's the first batch of fixes for 5.12. We have a handful of low
level world-switch regressions, a page table walker fix, more PMU
tidying up, and a workaround for systems with creative firmware.

Note that this is based on -rc1 despite the breakage, as I didn't feel
like holding these patches until -rc2.

Please pull,

	M.

The following changes since commit fe07bfda2fb9cdef8a4d4008a409bb02f35f1bd8:

  Linux 5.12-rc1 (2021-02-28 16:05:19 -0800)

are available in the Git repository at:

  git://git.kernel.org/pub/scm/linux/kernel/git/kvmarm/kvmarm.git tags/kvmarm-fixes-5.12-1

for you to fetch changes up to e85583b3f1fe62c9b371a3100c1c91af94005ca9:

  KVM: arm64: Fix range alignment when walking page tables (2021-03-04 09:54:12 +0000)

----------------------------------------------------------------
KVM/arm64 fixes for 5.12, take #1

- Fix SPE context save/restore on nVHE
- Fix some subtle host context corruption on vcpu exit
- Fix panic handling on nVHE
- Prevent the hypervisor from accessing PMU registers when there is none
- Workaround broken firmwares advertising bogus GICv2 compatibility
- Fix Stage-2 unaligned range unmapping

----------------------------------------------------------------
Andrew Scull (1):
      KVM: arm64: Fix nVHE hyp panic host context restore

Jia He (1):
      KVM: arm64: Fix range alignment when walking page tables

Marc Zyngier (4):
      KVM: arm64: Turn kvm_arm_support_pmu_v3() into a static key
      KVM: arm64: Don't access PMSELR_EL0/PMUSERENR_EL0 when no PMU is available
      KVM: arm64: Rename __vgic_v3_get_ich_vtr_el2() to __vgic_v3_get_gic_config()
      KVM: arm64: Workaround firmware wrongly advertising GICv2-on-v3 compatibility

Suzuki K Poulose (1):
      KVM: arm64: nvhe: Save the SPE context early

Will Deacon (1):
      KVM: arm64: Avoid corrupting vCPU context register in guest exit

 arch/arm64/include/asm/kvm_asm.h        |  4 ++--
 arch/arm64/include/asm/kvm_hyp.h        |  8 ++++++-
 arch/arm64/kernel/image-vars.h          |  3 +++
 arch/arm64/kvm/hyp/entry.S              |  2 +-
 arch/arm64/kvm/hyp/include/hyp/switch.h |  9 +++++---
 arch/arm64/kvm/hyp/nvhe/debug-sr.c      | 12 ++++++++--
 arch/arm64/kvm/hyp/nvhe/host.S          | 15 +++++++------
 arch/arm64/kvm/hyp/nvhe/hyp-main.c      |  6 ++---
 arch/arm64/kvm/hyp/nvhe/switch.c        | 14 +++++++++---
 arch/arm64/kvm/hyp/pgtable.c            |  1 +
 arch/arm64/kvm/hyp/vgic-v3-sr.c         | 40 +++++++++++++++++++++++++++++++--
 arch/arm64/kvm/perf.c                   | 10 +++++++++
 arch/arm64/kvm/pmu-emul.c               | 10 ---------
 arch/arm64/kvm/vgic/vgic-v3.c           | 12 +++++++---
 include/kvm/arm_pmu.h                   |  9 ++++++--
 15 files changed, 116 insertions(+), 39 deletions(-)
```
#### [PATCH] KVM: SVM: Connect 'npt' module param to KVM's internal 'npt_enabled'
##### From: Sean Christopherson <seanjc@google.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Sean Christopherson <seanjc@google.com>
X-Patchwork-Id: 12117411
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-26.3 required=3.0 tests=BAYES_00,DKIMWL_WL_MED,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_CR_TRAILER,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,
	USER_AGENT_GIT,USER_IN_DEF_DKIM_WL autolearn=unavailable autolearn_force=no
	version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 6E811C433E0
	for <kvm@archiver.kernel.org>; Fri,  5 Mar 2021 02:16:43 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 3900565011
	for <kvm@archiver.kernel.org>; Fri,  5 Mar 2021 02:16:43 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S229818AbhCECQl (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Thu, 4 Mar 2021 21:16:41 -0500
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:46756 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S229503AbhCECQl (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 4 Mar 2021 21:16:41 -0500
Received: from mail-yb1-xb4a.google.com (mail-yb1-xb4a.google.com
 [IPv6:2607:f8b0:4864:20::b4a])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id E1161C061756
        for <kvm@vger.kernel.org>; Thu,  4 Mar 2021 18:16:40 -0800 (PST)
Received: by mail-yb1-xb4a.google.com with SMTP id a186so898306ybg.1
        for <kvm@vger.kernel.org>; Thu, 04 Mar 2021 18:16:40 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=sender:reply-to:date:message-id:mime-version:subject:from:to:cc;
        bh=XCuZlcex++tlORTWddHh341Mae7tA0syCjmGbmGPn9g=;
        b=qWBQmAwlMgMgF4FtEbl6VOjLqoWiCkJFNktt9fpqeco2hKyqjvgv9fgentVlBECwVy
         qwATzdmr4c7yY4EhBm4HboriqczFqV4Il+hRoYSxJn0FmVuvZUAn8RO/oJCAVx7/MuMs
         T5bvw+xjZnjoAKG0HwtUzo84urtfEO1d0PNPSqfyenZWbXhLayyU9y9dJ2hhdnTMBKSa
         BC69jOdx39bVmd4E3TVQodre8QBR0cutRcrNfzOZdZhAfGbyjOMlqBTS8xlj4ZvUyXDB
         H4hCm/0aM/uWQUlRd9Q3x/qM68r5m5dhxjxPyJXC4UZiGdXF4U7iGeWAAmzbMyCnxyJ8
         X+Pw==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:sender:reply-to:date:message-id:mime-version
         :subject:from:to:cc;
        bh=XCuZlcex++tlORTWddHh341Mae7tA0syCjmGbmGPn9g=;
        b=NvOk2plssF3Ew6lEysYGtpqCOYQrc61YVUyplUmdjgESgIvE3/TCnjnotzw9wL573p
         BFniQNmTiYY2Ow2kscjJCqcrT5L5Df7dnkFxSVA/vHA4c9s3B6VB9nPVWn3V3NCIGyop
         fhdtHblzzW4gLcJioIIIBplLbWA6VLUyuPUlavO6Xkv3DAwCuDXi3Z98fO9ey5WdfAKz
         uOdtzEQnkWU9md+vGoW4QE5u7XaLe0FYWvuk+BAyYojg9+dl69b3Yo6pY1ziA5nwyQJ1
         YVPUSRdCcKqpxPdS/NlgK/W1ZXAkx58BCzZhIWU5vdfv9AU8a0eHscoen395Mhb47lT+
         p13w==
X-Gm-Message-State: AOAM533lBEdx6RJrqyvmys+PSoi4rxXdFut6i69/M8gL5cEJcEIaXTcM
        FdzHQd/sUOd7NCPr2N3+KvVcsXl+b+A=
X-Google-Smtp-Source: 
 ABdhPJw6kqqgn6lrO6/hWAaUSPFDGUSNlB+6yvYlFi8u2jKAW9fWp2mYtsqAFS5R4iAcL7UPxV2InPNUHg8=
Sender: "seanjc via sendgmr" <seanjc@seanjc798194.pdx.corp.google.com>
X-Received: from seanjc798194.pdx.corp.google.com
 ([2620:15c:f:10:9857:be95:97a2:e91c])
 (user=seanjc job=sendgmr) by 2002:a25:9c02:: with SMTP id
 c2mr9890875ybo.402.1614910600122;
 Thu, 04 Mar 2021 18:16:40 -0800 (PST)
Reply-To: Sean Christopherson <seanjc@google.com>
Date: Thu,  4 Mar 2021 18:16:37 -0800
Message-Id: <20210305021637.3768573-1-seanjc@google.com>
Mime-Version: 1.0
X-Mailer: git-send-email 2.30.1.766.gb4fecdf3b7-goog
Subject: [PATCH] KVM: SVM: Connect 'npt' module param to KVM's internal
 'npt_enabled'
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

Directly connect the 'npt' param to the 'npt_enabled' variable so that
runtime adjustments to npt_enabled are reflected in sysfs.  Move the
!PAE restriction to a runtime check to ensure NPT is forced off if the
host is using 2-level paging, and add a comment explicitly stating why
NPT requires a 64-bit kernel or a kernel with PAE enabled.

Opportunistically switch the param to octal permissions.

Signed-off-by: Sean Christopherson <seanjc@google.com>
Reviewed-by: Vitaly Kuznetsov <vkuznets@redhat.com>
---
 arch/x86/kvm/svm/svm.c | 27 ++++++++++++++-------------
 1 file changed, 14 insertions(+), 13 deletions(-)

```
#### [PATCH v4 01/11] KVM: x86: Get active PCID only when writing a CR3 value
##### From: Sean Christopherson <seanjc@google.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Sean Christopherson <seanjc@google.com>
X-Patchwork-Id: 12119179
Return-Path: <SRS0=d8nC=ID=vger.kernel.org=kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-26.3 required=3.0 tests=BAYES_00,DKIMWL_WL_MED,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_CR_TRAILER,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,
	USER_AGENT_GIT,USER_IN_DEF_DKIM_WL autolearn=ham autolearn_force=no
	version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 869C3C433E9
	for <kvm@archiver.kernel.org>; Fri,  5 Mar 2021 18:32:21 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 4903D6509F
	for <kvm@archiver.kernel.org>; Fri,  5 Mar 2021 18:32:21 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S230002AbhCESbo (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Fri, 5 Mar 2021 13:31:44 -0500
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:58274 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S229446AbhCESbb (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 5 Mar 2021 13:31:31 -0500
Received: from mail-yb1-xb4a.google.com (mail-yb1-xb4a.google.com
 [IPv6:2607:f8b0:4864:20::b4a])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id B4603C061756
        for <kvm@vger.kernel.org>; Fri,  5 Mar 2021 10:31:31 -0800 (PST)
Received: by mail-yb1-xb4a.google.com with SMTP id p136so3366088ybc.21
        for <kvm@vger.kernel.org>; Fri, 05 Mar 2021 10:31:31 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=sender:reply-to:date:in-reply-to:message-id:mime-version:references
         :subject:from:to:cc;
        bh=Ez6kaNpvX5WDqy2a2Fkcncr/macPJ8v8cBzt3I2dkQE=;
        b=dfkixw7Hg7+i/kt8hB8quDhlBcEbqlneYKJ6B03h2Wx0CvZP4+Snl2WQetxtJNd0jX
         5gOhsLYc1pu+ulZlVbm3NLeNDAmJmqsQqYKmrOyTPy54SrI1n9vLdlbr6GOkpm0UM9gB
         nBwfuDJtq2pBBFr4SD4Q4l7PJdUQ5ftD3eUTNmfqsIGWwei32i62HMkMmibETTOzQzYf
         ZbeKu+JARUbN6rW0Eh4+3VVsb9Qfs4DDnlrXsU8e2MJQHB+D1YEZ0z8+ZeDH4PJY2xH7
         UwuOrejd7OFzcDiuDoBYV5AVbg+ximPGfQ5Quj6QKoq286j8ZCaNbDpyh4jWC0WAj/Y9
         U6bw==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:sender:reply-to:date:in-reply-to:message-id
         :mime-version:references:subject:from:to:cc;
        bh=Ez6kaNpvX5WDqy2a2Fkcncr/macPJ8v8cBzt3I2dkQE=;
        b=h7uNsEKkxZ4/gh5deHzUuIbm8dU1DjaG34LHnbccZsW2lwirPBA8zHuOzyxeG/QXaC
         TCs9fq3NwadCgGwvI5eK34LF2DnkbXJ2ymD8MJ3MFKHhdLvGRM+1NefGTaNRKSmtAPqJ
         nHb93XbtcFgiv3oYyFy2gdD2BmRw3ig30lto3/srWsvr46Vl73nxICUSKIAPNJDXrJJ4
         jp5XZIkOLZc2ydiMQzCV1uMbPsY9mrVgPIg7wq5vGv/lWa7DcpYyJuqB8ORHWmoETcPU
         q0H9sSrCiB19ECdT2XDVXaOwblu0P3+4KwlDtrDDe0KI7v2VZyC42QZx+KPrzK5Pn4hs
         RE3A==
X-Gm-Message-State: AOAM530xkeCPxsrCQtO9uuz+JZP6bwx42R5a2HrX0CpbQWJ8wmlNMzCY
        fMxi0la4WJ2XcxjmX2GtCdN452Pnsis=
X-Google-Smtp-Source: 
 ABdhPJwkLqyDK3iGSyjPchE/cUxSowy6gHbbUTDSoVntlUxbds3j6SZNNAXArYdWVUJrLeKFz/AcmKhqb6w=
Sender: "seanjc via sendgmr" <seanjc@seanjc798194.pdx.corp.google.com>
X-Received: from seanjc798194.pdx.corp.google.com
 ([2620:15c:f:10:9857:be95:97a2:e91c])
 (user=seanjc job=sendgmr) by 2002:a25:7613:: with SMTP id
 r19mr15575268ybc.212.1614969090998;
 Fri, 05 Mar 2021 10:31:30 -0800 (PST)
Reply-To: Sean Christopherson <seanjc@google.com>
Date: Fri,  5 Mar 2021 10:31:13 -0800
In-Reply-To: <20210305183123.3978098-1-seanjc@google.com>
Message-Id: <20210305183123.3978098-2-seanjc@google.com>
Mime-Version: 1.0
References: <20210305183123.3978098-1-seanjc@google.com>
X-Mailer: git-send-email 2.30.1.766.gb4fecdf3b7-goog
Subject: [PATCH v4 01/11] KVM: x86: Get active PCID only when writing a CR3
 value
From: Sean Christopherson <seanjc@google.com>
To: Paolo Bonzini <pbonzini@redhat.com>
Cc: Sean Christopherson <seanjc@google.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org,
        Sean Christopherson <sean.j.christopherson@intel.com>
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Sean Christopherson <sean.j.christopherson@intel.com>

Retrieve the active PCID only when writing a guest CR3 value, i.e. don't
get the PCID when using EPT or NPT.  The PCID is especially problematic
for EPT as the bits have different meaning, and so the PCID and must be
manually stripped, which is annoying and unnecessary.  And on VMX,
getting the active PCID also involves reading the guest's CR3 and
CR4.PCIDE, i.e. may add pointless VMREADs.

Opportunistically rename the pgd/pgd_level params to root_hpa and
root_level to better reflect their new roles.  Keep the function names,
as "load the guest PGD" is still accurate/correct.

Last, and probably least, pass root_hpa as a hpa_t/u64 instead of an
unsigned long.  The EPTP holds a 64-bit value, even in 32-bit mode, so
in theory EPT could support HIGHMEM for 32-bit KVM.  Never mind that
doing so would require changing the MMU page allocators and reworking
the MMU to use kmap().

Signed-off-by: Sean Christopherson <sean.j.christopherson@intel.com>
Signed-off-by: Sean Christopherson <seanjc@google.com>
---
 arch/x86/include/asm/kvm_host.h |  4 ++--
 arch/x86/kvm/mmu.h              |  4 ++--
 arch/x86/kvm/svm/svm.c          | 10 ++++++----
 arch/x86/kvm/vmx/vmx.c          | 13 ++++++-------
 arch/x86/kvm/vmx/vmx.h          |  3 +--
 5 files changed, 17 insertions(+), 17 deletions(-)

```
#### [PATCH] KVM: x86: Ensure deadline timer has truly expired before posting its IRQ
##### From: Sean Christopherson <seanjc@google.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Sean Christopherson <seanjc@google.com>
X-Patchwork-Id: 12117413
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
	by smtp.lore.kernel.org (Postfix) with ESMTP id 7A5EBC433E0
	for <kvm@archiver.kernel.org>; Fri,  5 Mar 2021 02:18:16 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 3CE8F6500F
	for <kvm@archiver.kernel.org>; Fri,  5 Mar 2021 02:18:16 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S229576AbhCECSP (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Thu, 4 Mar 2021 21:18:15 -0500
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:47094 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S229463AbhCECSP (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 4 Mar 2021 21:18:15 -0500
Received: from mail-qt1-x849.google.com (mail-qt1-x849.google.com
 [IPv6:2607:f8b0:4864:20::849])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 2B4ABC061574
        for <kvm@vger.kernel.org>; Thu,  4 Mar 2021 18:18:15 -0800 (PST)
Received: by mail-qt1-x849.google.com with SMTP id p32so380251qtd.14
        for <kvm@vger.kernel.org>; Thu, 04 Mar 2021 18:18:15 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=sender:reply-to:date:message-id:mime-version:subject:from:to:cc;
        bh=iFsu/EdgzPCi1WqYdYUBcFgRLZpgieXshXK9nnq/e2Q=;
        b=Dm7EqRrQGHwk4GNJMLxWsQTTtpmjMKr5XzzRltH4yF4XLUzdFFiyvsjnp1NTrFqAWD
         CjfRG3hCuW1YFGc6A9Y05LccX7aY94QO+wvrTna8ER7QCPvAqc9cTr+SDbDE7Ldpjw3t
         rgtktSM2aFRd0K33Dqco70ItekgC6OfWuwo0KQ+vkE9LIdkGuecrItyAYNY5IrqvtPnf
         IM5vybBlZZIJb6OQHKcf0RcSJiUJryCWGAhm5Qi0FNJWVncKswsoai/pll1Euh2JIGiA
         gbO6fIcNJdAVjAQtSPfOZWTgAaL5JAINvcWY30PuSr1We+YkowOrraGVXDfiXT9XhhEG
         nq9A==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:sender:reply-to:date:message-id:mime-version
         :subject:from:to:cc;
        bh=iFsu/EdgzPCi1WqYdYUBcFgRLZpgieXshXK9nnq/e2Q=;
        b=XZcRynh44y5qxDNyZXBkBUUa4mi/LzN0Na4dFgFBQfyFqKWQz7CM8CttjNOVikudqF
         JFef39+HDscx/NFx5uqcLq2q9zRlMTmQYABAJeNXBNC91mH2CDPuKZOX/yrQolIMrnNg
         uQ2sIE3r8Psjjxuvnz5dQLfeB2IMMDbeXeD4e+irZBPPWZdZbyKyAS94mrxTL+qudsMu
         Xspydyju9i/jT4t0nl/qZfzPHgK1BYE/lQ3a/h+YPlVjMEtetPctrsC7R9/Hrs2BRJaB
         1tPMl/mg6518VW/nWLau4BMJVhPN/fH1WUpHmhux022zU2e7SCj/WVFEaLDTNYS60Aye
         wKww==
X-Gm-Message-State: AOAM531xUqpeFiFWo07go7MPkuEKjOrt+Gvxypa4lkUqmMK2VtPEPh8P
        KyBHdx7b0lLIxdxebUc+A2bqTB7AEag=
X-Google-Smtp-Source: 
 ABdhPJyfHd60C/yt6/C0Ijkwk9RyVf8bjnYna4ppLSBzVsVQ7VGppNses7R6R1uiC2x3LrH3g3AER8JsCOo=
Sender: "seanjc via sendgmr" <seanjc@seanjc798194.pdx.corp.google.com>
X-Received: from seanjc798194.pdx.corp.google.com
 ([2620:15c:f:10:9857:be95:97a2:e91c])
 (user=seanjc job=sendgmr) by 2002:a0c:fec8:: with SMTP id
 z8mr7027044qvs.59.1614910691867;
 Thu, 04 Mar 2021 18:18:11 -0800 (PST)
Reply-To: Sean Christopherson <seanjc@google.com>
Date: Thu,  4 Mar 2021 18:18:08 -0800
Message-Id: <20210305021808.3769732-1-seanjc@google.com>
Mime-Version: 1.0
X-Mailer: git-send-email 2.30.1.766.gb4fecdf3b7-goog
Subject: [PATCH] KVM: x86: Ensure deadline timer has truly expired before
 posting its IRQ
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

When posting a deadline timer interrupt, open code the checks guarding
__kvm_wait_lapic_expire() in order to skip the lapic_timer_int_injected()
check in kvm_wait_lapic_expire().  The injection check will always fail
since the interrupt has not yet be injected.  Moving the call after
injection would also be wrong as that wouldn't actually delay delivery
of the IRQ if it is indeed sent via posted interrupt.

Fixes: 010fd37fddf6 ("KVM: LAPIC: Reduce world switch latency caused by timer_advance_ns")
Cc: stable@vger.kernel.org
Signed-off-by: Sean Christopherson <seanjc@google.com>
---
 arch/x86/kvm/lapic.c | 11 ++++++++++-
 1 file changed, 10 insertions(+), 1 deletion(-)

```
#### [PATCH v2 01/17] KVM: nSVM: Set the shadow root level to the TDP level for nested NPT
##### From: Sean Christopherson <seanjc@google.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Sean Christopherson <seanjc@google.com>
X-Patchwork-Id: 12117313
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
	by smtp.lore.kernel.org (Postfix) with ESMTP id 73BD1C433DB
	for <kvm@archiver.kernel.org>; Fri,  5 Mar 2021 01:11:11 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 3C29564F67
	for <kvm@archiver.kernel.org>; Fri,  5 Mar 2021 01:11:11 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S229648AbhCEBLK (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Thu, 4 Mar 2021 20:11:10 -0500
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:60830 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S229602AbhCEBLJ (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 4 Mar 2021 20:11:09 -0500
Received: from mail-yb1-xb49.google.com (mail-yb1-xb49.google.com
 [IPv6:2607:f8b0:4864:20::b49])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id EF790C061756
        for <kvm@vger.kernel.org>; Thu,  4 Mar 2021 17:11:07 -0800 (PST)
Received: by mail-yb1-xb49.google.com with SMTP id b127so662710ybc.13
        for <kvm@vger.kernel.org>; Thu, 04 Mar 2021 17:11:07 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=sender:reply-to:date:in-reply-to:message-id:mime-version:references
         :subject:from:to:cc;
        bh=YZHRewQoZy371sjGbfTjC6cuAY8+Z64Uwc7ykPHV30o=;
        b=lbtKupSNNVVnfGQzSlvQ+vTPFhg4zP425mwF5KftOrXADXrxW5MCkY9PdW6+OECVLi
         f7gV3Yd6yk9HuYcd9bdWv1hOqkHKEFHbq+1wcJfndCJtUGQV2uhXVaL5jxC05PzU+IiH
         vZy/QxLlzTQ+SsUMbVNaHztQNZ0z6CPanVisBzdLeHIMuCF52m9Ad1PoHiflsYduUBra
         X8oKSrNikGzi6cw5nBmyUDTIdrAo/GvoAwdZ6atuSc103Jz3Wio3cM7NLE92H1iRQrE6
         tEcpWLHfeJ87aekUvaTCOfkDbJ5cVQkEDsQNNGyBYFgWWIvVzx6r/kXgN0TQ4i12Dg67
         3iFA==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:sender:reply-to:date:in-reply-to:message-id
         :mime-version:references:subject:from:to:cc;
        bh=YZHRewQoZy371sjGbfTjC6cuAY8+Z64Uwc7ykPHV30o=;
        b=MsGqAkUXvn50yH0C5ifgrOyk2ADqjjsCpZKyB9kgR6nuHzHdxe6RWyxSuo6mXspwNJ
         0z7vBBp1CHrv1QJ4hYwGwdm6SkdLQl4501LoPRrKRJvmI1R2uZW6iPlF1uB5D9bxmTsi
         cSBfxbpkDEvMLljrruS/FHFc0S+pW1ExK7zJ/yOjVnVFaoQjFpaKG6E3NL29Dd7KAtJF
         yx7XRy7ey548R8K/HvUOYI58l0Ntmd9orZ13fBzJ1XXmwvUbIaK6lgXW5PAnihgPxNBo
         39Y2shJBXf3vMSzA08fp8vN3DVNfrXUjOQGH/mkf0K/tzly953y3nj1F4vxsdOAULbWv
         Ivjw==
X-Gm-Message-State: AOAM533KF6cWI/9bU4tXWQma6xZcyqSLJ6L1Cl2R6wh0eXnoAIc8v61e
        nSlrPczGct2jd+GfzttOS66/UfRdawM=
X-Google-Smtp-Source: 
 ABdhPJzNiol+uPbyiI3HEQZPgXCwVI/rb61MbgLwfLCGALveKCKrVdNcrvALevBAaHdUJicLhjlt8ns3F9s=
Sender: "seanjc via sendgmr" <seanjc@seanjc798194.pdx.corp.google.com>
X-Received: from seanjc798194.pdx.corp.google.com
 ([2620:15c:f:10:9857:be95:97a2:e91c])
 (user=seanjc job=sendgmr) by 2002:a25:76c3:: with SMTP id
 r186mr10611691ybc.365.1614906667218;
 Thu, 04 Mar 2021 17:11:07 -0800 (PST)
Reply-To: Sean Christopherson <seanjc@google.com>
Date: Thu,  4 Mar 2021 17:10:45 -0800
In-Reply-To: <20210305011101.3597423-1-seanjc@google.com>
Message-Id: <20210305011101.3597423-2-seanjc@google.com>
Mime-Version: 1.0
References: <20210305011101.3597423-1-seanjc@google.com>
X-Mailer: git-send-email 2.30.1.766.gb4fecdf3b7-goog
Subject: [PATCH v2 01/17] KVM: nSVM: Set the shadow root level to the TDP
 level for nested NPT
From: Sean Christopherson <seanjc@google.com>
To: Paolo Bonzini <pbonzini@redhat.com>
Cc: Sean Christopherson <seanjc@google.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org, Ben Gardon <bgardon@google.com>,
        Brijesh Singh <brijesh.singh@amd.com>,
        Tom Lendacky <thomas.lendacky@amd.com>
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Override the shadow root level in the MMU context when configuring
NPT for shadowing nested NPT.  The level is always tied to the TDP level
of the host, not whatever level the guest happens to be using.

Fixes: 096586fda522 ("KVM: nSVM: Correctly set the shadow NPT root level in its MMU role")
Cc: stable@vger.kernel.org
Signed-off-by: Sean Christopherson <seanjc@google.com>
---
 arch/x86/kvm/mmu/mmu.c | 11 ++++++++---
 1 file changed, 8 insertions(+), 3 deletions(-)

```
#### [PATCH 1/3] vDPA/ifcvf: get_vendor_id returns a device specific vendor id
##### From: Zhu Lingshan <lingshan.zhu@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Zhu Lingshan <lingshan.zhu@intel.com>
X-Patchwork-Id: 12118535
Return-Path: <SRS0=d8nC=ID=vger.kernel.org=kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.8 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT autolearn=ham
	autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id BF15EC433DB
	for <kvm@archiver.kernel.org>; Fri,  5 Mar 2021 14:26:11 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 7B9B56509C
	for <kvm@archiver.kernel.org>; Fri,  5 Mar 2021 14:26:11 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S231239AbhCEOZk (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Fri, 5 Mar 2021 09:25:40 -0500
Received: from mga17.intel.com ([192.55.52.151]:27033 "EHLO mga17.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S230412AbhCEOZ3 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 5 Mar 2021 09:25:29 -0500
IronPort-SDR: 
 RTfC759iLoxKC1cyrJHelMDhzJvQsMw7znutUcG5HLltLxSzQeC1uon0UFWNfTFMclwyuTWNu7
 eQ+moj4rKsoA==
X-IronPort-AV: E=McAfee;i="6000,8403,9914"; a="167555564"
X-IronPort-AV: E=Sophos;i="5.81,225,1610438400";
   d="scan'208";a="167555564"
Received: from orsmga008.jf.intel.com ([10.7.209.65])
  by fmsmga107.fm.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 05 Mar 2021 06:25:29 -0800
IronPort-SDR: 
 nckXKTnu4bFavss5OQj23qtOON7wZys2As4nZTPKLZ8KyOTjc+O5qwaRsMDuxuQ48l3adQderq
 DGbX27k7PY5w==
X-IronPort-AV: E=Sophos;i="5.81,225,1610438400";
   d="scan'208";a="408315642"
Received: from unknown (HELO localhost.localdomain.bj.intel.com)
 ([10.240.193.73])
  by orsmga008-auth.jf.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 05 Mar 2021 06:25:26 -0800
From: Zhu Lingshan <lingshan.zhu@intel.com>
To: jasowang@redhat.com, mst@redhat.com, lulu@redhat.com
Cc: virtualization@lists.linux-foundation.org, netdev@vger.kernel.org,
        kvm@vger.kernel.org, linux-kernel@vger.kernel.org,
        Zhu Lingshan <lingshan.zhu@intel.com>
Subject: [PATCH 1/3] vDPA/ifcvf: get_vendor_id returns a device specific
 vendor id
Date: Fri,  5 Mar 2021 22:19:58 +0800
Message-Id: <20210305142000.18521-2-lingshan.zhu@intel.com>
X-Mailer: git-send-email 2.27.0
In-Reply-To: <20210305142000.18521-1-lingshan.zhu@intel.com>
References: <20210305142000.18521-1-lingshan.zhu@intel.com>
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

In this commit, ifcvf_get_vendor_id() will return
a device specific vendor id of the probed pci device
than a hard code.

Signed-off-by: Zhu Lingshan <lingshan.zhu@intel.com>
---
 drivers/vdpa/ifcvf/ifcvf_main.c | 5 ++++-
 1 file changed, 4 insertions(+), 1 deletion(-)

```
#### [PATCH] vfio: Depend on MMU
##### From: Jason Gunthorpe <jgg@nvidia.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Jason Gunthorpe <jgg@nvidia.com>
X-Patchwork-Id: 12117351
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-15.8 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_CR_TRAILER,INCLUDES_PATCH,MAILING_LIST_MULTI,MSGID_FROM_MTA_HEADER,
	SPF_HELO_NONE,SPF_PASS autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 18357C433E6
	for <kvm@archiver.kernel.org>; Fri,  5 Mar 2021 01:30:08 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id D09F164FF0
	for <kvm@archiver.kernel.org>; Fri,  5 Mar 2021 01:30:07 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S229485AbhCEBaH (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Thu, 4 Mar 2021 20:30:07 -0500
Received: from hqnvemgate24.nvidia.com ([216.228.121.143]:18112 "EHLO
        hqnvemgate24.nvidia.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S229436AbhCEBaH (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 4 Mar 2021 20:30:07 -0500
Received: from hqmail.nvidia.com (Not Verified[216.228.121.13]) by
 hqnvemgate24.nvidia.com (using TLS: TLSv1.2, AES256-SHA)
        id <B6041899f0000>; Thu, 04 Mar 2021 17:30:07 -0800
Received: from HQMAIL101.nvidia.com (172.20.187.10) by HQMAIL105.nvidia.com
 (172.20.187.12) with Microsoft SMTP Server (TLS) id 15.0.1497.2; Fri, 5 Mar
 2021 01:30:06 +0000
Received: from NAM02-SN1-obe.outbound.protection.outlook.com (104.47.36.52) by
 HQMAIL101.nvidia.com (172.20.187.10) with Microsoft SMTP Server (TLS) id
 15.0.1497.2 via Frontend Transport; Fri, 5 Mar 2021 01:30:06 +0000
ARC-Seal: i=1; a=rsa-sha256; s=arcselector9901; d=microsoft.com; cv=none;
 b=Ac6ihfUy/biuNfmwDjXSVfCvM+Fe8JeYfDTnCl0MZDXL7k8N/WRclG3ImNFBnPJQHMn9ls/r1wn9z8duARBs3KpzA5sSh7v2WLatLQaCw2j3t71z0deeZh4zWRwbSrUh4jiKVfi5lVfKpS4FtpiJoxAU3yM2rmaNwh95d+Yzh8w78+Xjss+wbwvCKfok/IZ3tejJOPl/3wmj0fLGhrI7o1yCxzl4bCt94WmLriiZehE7TQc2BKVJMd5aSeGysk8JB/+4ywoAHso6HMAJeTSJilZ6v48fTIC3ufODN+G10g7EpAUhAlqvX0AWcAtPrUduPnvZ4J3+SSdRRl/Pda2ozw==
ARC-Message-Signature: i=1; a=rsa-sha256; c=relaxed/relaxed; d=microsoft.com;
 s=arcselector9901;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=R0HnrV8BhKqIOPMc7De7KpT+ejGhNiggopqlkuBAI10=;
 b=KoVBgGRIgD2I5uWLfeXdmP223dKwG/g2f5rhTkXZFmEKP9VP4BfZohXik4wWQ1fN+yGguDJaBJ8oYf4+rGXEeSybNlEyNzr1Uo5XfADvyqednBq91hGfbN15/lcjpheyRnBSFkDU0wJU4oHRVjwhU6VnIhFNLXaLjtm02Q6AtWapnmh7i8Ak1+4SExGPGCOWWng2mBOYfDOqRLcAxrd7WMNW9uj5MftSTH8mVT+5S5xECUQHaf4rWSkwAgJcm4Wfhk5QEq0k+Qi/jPL6knpjhgioDKEXfADYXVtDJncEYPs9TLzicd1XsqjnGR2cIqRj9q3fSsaKj6l/TZxMyIt6Dg==
ARC-Authentication-Results: i=1; mx.microsoft.com 1; spf=pass
 smtp.mailfrom=nvidia.com; dmarc=pass action=none header.from=nvidia.com;
 dkim=pass header.d=nvidia.com; arc=none
Received: from DM6PR12MB3834.namprd12.prod.outlook.com (2603:10b6:5:14a::12)
 by DM5PR12MB1244.namprd12.prod.outlook.com (2603:10b6:3:73::15) with
 Microsoft SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.3890.19; Fri, 5 Mar
 2021 01:30:04 +0000
Received: from DM6PR12MB3834.namprd12.prod.outlook.com
 ([fe80::1c62:7fa3:617b:ab87]) by DM6PR12MB3834.namprd12.prod.outlook.com
 ([fe80::1c62:7fa3:617b:ab87%6]) with mapi id 15.20.3912.017; Fri, 5 Mar 2021
 01:30:04 +0000
From: Jason Gunthorpe <jgg@nvidia.com>
To: Alex Williamson <alex.williamson@redhat.com>, <kvm@vger.kernel.org>
CC: Cornelia Huck <cohuck@redhat.com>
Subject: [PATCH] vfio: Depend on MMU
Date: Thu, 4 Mar 2021 21:30:03 -0400
Message-ID: <0-v1-02cb5500df6e+78-vfio_no_mmu_jgg@nvidia.com>
X-ClientProxiedBy: BL1PR13CA0117.namprd13.prod.outlook.com
 (2603:10b6:208:2b9::32) To DM6PR12MB3834.namprd12.prod.outlook.com
 (2603:10b6:5:14a::12)
MIME-Version: 1.0
X-MS-Exchange-MessageSentRepresentingType: 1
Received: from mlx.ziepe.ca (142.162.115.133) by
 BL1PR13CA0117.namprd13.prod.outlook.com (2603:10b6:208:2b9::32) with
 Microsoft SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.3912.9 via Frontend
 Transport; Fri, 5 Mar 2021 01:30:04 +0000
Received: from jgg by mlx with local (Exim 4.94)        (envelope-from
 <jgg@nvidia.com>)        id 1lHzI3-007fZC-7x; Thu, 04 Mar 2021 21:30:03 -0400
X-Header: ProcessedBy-CMR-outbound
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=nvidia.com; s=n1;
        t=1614907807; bh=94v8CiAQgCxpNFeI1+EuH7XU8W3yryiC8Ef1AwGRROo=;
        h=ARC-Seal:ARC-Message-Signature:ARC-Authentication-Results:From:To:
         CC:Subject:Date:Message-ID:Content-Transfer-Encoding:Content-Type:
         X-ClientProxiedBy:MIME-Version:
         X-MS-Exchange-MessageSentRepresentingType:X-Header;
        b=Zn8QLekN6zaKagG1OEf8dAhrc9RkxuyYCuzGE3rmCsaYyGXJXFflymqRb0F6vJ4uD
         iW4h+QfIJkLm6UNv6qhTZ7zFMHWk3DBcJvTaRLvIMrkeK/1UOjak2Y+L1dB7ijw3y7
         edNockL5AUvug+rfiMRmLI66XKCqpkrj9C6cSK9wPdlg1aioSADG3s1LdM9E0mAa+z
         03TgSiAA3+40Z27xfzopFCSN14HyBGIHQBlN8G72WjXSxKPvKeUvJ7MJmhBVgiJNo+
         L8EgdP8tostP+8q66Z2/0aexKJDlZPQJTHlZMtm0QHvWq11erlrZir10bfMIQd1H/u
         gE3FMESIJS6Qw==
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

VFIO_IOMMU_TYPE1 does not compile with !MMU:

../drivers/vfio/vfio_iommu_type1.c: In function 'follow_fault_pfn':
../drivers/vfio/vfio_iommu_type1.c:536:22: error: implicit declaration of function 'pte_write'; did you mean 'vfs_write'? [-Werror=implicit-function-declaration]

So require it.

Suggested-by: Cornelia Huck <cohuck@redhat.com>
Signed-off-by: Jason Gunthorpe <jgg@nvidia.com>
---
 drivers/vfio/Kconfig | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
#### [PATCH] x86/perf: Fix guest_get_msrs static call if there is no PMUFrom: Sean Christopherson <seanjc@google.com>
##### From: Sean Christopherson <seanjc@google.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Sean Christopherson <seanjc@google.com>
X-Patchwork-Id: 12119513
Return-Path: <SRS0=d8nC=ID=vger.kernel.org=kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-26.3 required=3.0 tests=BAYES_00,DKIMWL_WL_MED,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_CR_TRAILER,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,
	URIBL_BLOCKED,USER_AGENT_GIT,USER_IN_DEF_DKIM_WL autolearn=ham
	autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 52AB4C433DB
	for <kvm@archiver.kernel.org>; Fri,  5 Mar 2021 22:35:26 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 26D2A650AC
	for <kvm@archiver.kernel.org>; Fri,  5 Mar 2021 22:35:26 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S229679AbhCEWew (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Fri, 5 Mar 2021 17:34:52 -0500
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:54064 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S229592AbhCEWev (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 5 Mar 2021 17:34:51 -0500
Received: from mail-yb1-xb4a.google.com (mail-yb1-xb4a.google.com
 [IPv6:2607:f8b0:4864:20::b4a])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id ED2F9C06175F
        for <kvm@vger.kernel.org>; Fri,  5 Mar 2021 14:34:50 -0800 (PST)
Received: by mail-yb1-xb4a.google.com with SMTP id p136so4089653ybc.21
        for <kvm@vger.kernel.org>; Fri, 05 Mar 2021 14:34:50 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=sender:reply-to:date:message-id:mime-version:subject:from:to:cc;
        bh=sVxveq/IidC6Dcg/UZ54CWSyr4b2i4eGAQesD0hdFkc=;
        b=LRZoIR5yWsUk6WnZgHh7btUexV20WDm2A/1mUk7p+kzq+cOKMTlybMhdxBGQjG4iju
         ytP+lxSryqNRr5sap0oL6YuOcb2nbFYujBKFRDV+nulGq7eq1AJRQEY8Qx0Mqm9rpX4X
         WZ2fRI3IcOkbUvCCxJ0M4htnF94hCQwrMAH2pL/hSXW0EieVCSFC1gK1fqcaIsq7DSkL
         3Gh8MkUXVlTBLD1D6oZwFfhBQlKOh7iQcFiuwKhLFBPHm+NNQDKmGyGPWced1yoi/zIm
         wsSKmjlg3u77Lrqjo98iAo9/yZtAT8JBoZXMKnhUZSeX6zQDyxO7fUp1+uQs2xae1xws
         Qzuw==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:sender:reply-to:date:message-id:mime-version
         :subject:from:to:cc;
        bh=sVxveq/IidC6Dcg/UZ54CWSyr4b2i4eGAQesD0hdFkc=;
        b=LehggFU59EAReWxUFap1Z37FJvC/vcW77E0IGnsSuC4KhxFBj2w+OwClIUNq25AHym
         QQ7fKvU6xkAyjfapdrTmnE9+gDH3yv3FpmOkEjWeS4Tyh+gOYDW/M85H/O3Di58aRED+
         ZdmEQDtKxlxxxk2zVSB9ot8ugSRqmjt8FxVrFwqxVDjvXUJY0iPtJGhPDSblF3GH7ghO
         pCfaJu5aL/XuNxQYSuN/n2g7buypQ4F08sznQhU1Rt7461YTVNm58sqTz4m7M3WGDRQy
         jytViWegOjB7dvlzdgiQ7mOuee01qaJo9aexUD8gbfbRWIqB8o698Db52CWqMY5OdLXf
         +5aA==
X-Gm-Message-State: AOAM531ZBMVbULu7zjN2Zjv0G4qqOe8KU+22//rceIjGss+/W1NrXMSS
        tuTplRCY92XFwnQHr00xPjvejmOUCWg=
X-Google-Smtp-Source: 
 ABdhPJw3RQaY2hVP255sL6Sod8e/1piSX8ViPZaVrYSHDVS58LYHZPjCYhIgFyZ3p5QjKmztlFjECkzZvt8=
Sender: "seanjc via sendgmr" <seanjc@seanjc798194.pdx.corp.google.com>
X-Received: from seanjc798194.pdx.corp.google.com
 ([2620:15c:f:10:9857:be95:97a2:e91c])
 (user=seanjc job=sendgmr) by 2002:a25:ad5c:: with SMTP id
 l28mr15617451ybe.307.1614983689946;
 Fri, 05 Mar 2021 14:34:49 -0800 (PST)
Reply-To: Sean Christopherson <seanjc@google.com>
Date: Fri,  5 Mar 2021 14:33:31 -0800
Message-Id: <20210305223331.4173565-1-seanjc@google.com>
Mime-Version: 1.0
X-Mailer: git-send-email 2.30.1.766.gb4fecdf3b7-goog
Subject: [PATCH] x86/perf: Fix guest_get_msrs static call if there is no PMU
From: Sean Christopherson <seanjc@google.com>
To: Peter Zijlstra <peterz@infradead.org>,
        Ingo Molnar <mingo@redhat.com>,
        Arnaldo Carvalho de Melo <acme@kernel.org>,
        Thomas Gleixner <tglx@linutronix.de>,
        Borislav Petkov <bp@alien8.de>, x86@kernel.org
Cc: Mark Rutland <mark.rutland@arm.com>,
        Alexander Shishkin <alexander.shishkin@linux.intel.com>,
        Jiri Olsa <jolsa@redhat.com>,
        Namhyung Kim <namhyung@kernel.org>,
        "H. Peter Anvin" <hpa@zytor.com>, linux-kernel@vger.kernel.org,
        Like Xu <like.xu@linux.intel.com>,
        Paolo Bonzini <pbonzini@redhat.com>,
        Jim Mattson <jmattson@google.com>, kvm@vger.kernel.org,
        Dmitry Vyukov <dvyukov@google.com>,
        Sean Christopherson <seanjc@google.com>
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Handle a NULL x86_pmu.guest_get_msrs at invocation instead of patching
in perf_guest_get_msrs_nop() during setup.  If there is no PMU, setup
bails before updating the static calls, leaving x86_pmu.guest_get_msrs
NULL and thus a complete nop.  Ultimately, this causes VMX abort on
VM-Exit due to KVM putting random garbage from the stack into the MSR
load list.

Fixes: abd562df94d1 ("x86/perf: Use static_call for x86_pmu.guest_get_msrs")
Cc: Like Xu <like.xu@linux.intel.com>
Cc: Paolo Bonzini <pbonzini@redhat.com>
Cc: Jim Mattson <jmattson@google.com>
Cc: kvm@vger.kernel.org
Reported-by: Dmitry Vyukov <dvyukov@google.com>
Signed-off-by: Sean Christopherson <seanjc@google.com>
---
 arch/x86/events/core.c | 16 +++++-----------
 1 file changed, 5 insertions(+), 11 deletions(-)

```
