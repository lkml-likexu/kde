#### [PATCH 1/1] KVM: x86: remove incorrect comment on active_mmu_pages
##### From: Dongli Zhang <dongli.zhang@oracle.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Dongli Zhang <dongli.zhang@oracle.com>
X-Patchwork-Id: 12100883
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-18.7 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,
	INCLUDES_PATCH,MAILING_LIST_MULTI,MSGID_FROM_MTA_HEADER,SPF_HELO_NONE,
	SPF_PASS,USER_AGENT_GIT autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 04522C433DB
	for <kvm@archiver.kernel.org>; Tue, 23 Feb 2021 20:39:12 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id B269F64EC1
	for <kvm@archiver.kernel.org>; Tue, 23 Feb 2021 20:39:11 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S233542AbhBWUjH (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 23 Feb 2021 15:39:07 -0500
Received: from userp2130.oracle.com ([156.151.31.86]:35152 "EHLO
        userp2130.oracle.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S232525AbhBWUi4 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 23 Feb 2021 15:38:56 -0500
Received: from pps.filterd (userp2130.oracle.com [127.0.0.1])
        by userp2130.oracle.com (8.16.0.42/8.16.0.42) with SMTP id
 11NKZfYZ025982;
        Tue, 23 Feb 2021 20:37:03 GMT
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=oracle.com;
 h=from : to : cc :
 subject : date : message-id : content-type : mime-version;
 s=corp-2020-01-29; bh=nCcdMOgHx+exsmG+se5QictMZ3B74JDcMoga/+8aTVQ=;
 b=wnzCX2JYMu4MHziwSzKhvdyHjitTnl3yp+OZunKk5GZXengDGQCJ0bA97YHFVcVxGUPi
 LWOZbciKT+Lcj0OtEgmI+U/CPy+zjWNpLAftyoNmIiNUCro2+bwXQzzE8lmSI2hMoTJb
 OSXkRnIqOgz6sNXBJBwiivoDPi6walPT7SmIJPEswaHf25TDzSCWTnJ8zTfSXnvYFoPW
 LXBVJ+y3RaoqO7Vw/Y228uyTWhNDogKtmgcJ1v9uzuImwo96bTMkSttlDybzZREEeMF7
 j9V4dcU/LmLND5rZwjtWVEqgd0Wvwi7hX/ZNg58bxWA3M86ehlDRGIyLfP0VnHxr/p+5 0Q==
Received: from userp3020.oracle.com (userp3020.oracle.com [156.151.31.79])
        by userp2130.oracle.com with ESMTP id 36tsur0t5e-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Tue, 23 Feb 2021 20:37:02 +0000
Received: from pps.filterd (userp3020.oracle.com [127.0.0.1])
        by userp3020.oracle.com (8.16.0.42/8.16.0.42) with SMTP id
 11NKa8Jg028329;
        Tue, 23 Feb 2021 20:37:02 GMT
Received: from nam10-dm6-obe.outbound.protection.outlook.com
 (mail-dm6nam10lp2100.outbound.protection.outlook.com [104.47.58.100])
        by userp3020.oracle.com with ESMTP id 36uc6s8h41-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Tue, 23 Feb 2021 20:37:02 +0000
ARC-Seal: i=1; a=rsa-sha256; s=arcselector9901; d=microsoft.com; cv=none;
 b=Pp5hB8ss0a5uwWG5x+MxT8Z46DUT6JtlFEgbQfvalJoBEvvNwYooQjm/2GQC66Gx0n3d/0OSbVgcfqd8waCc2fD8Oj/7jy4Cget9n1L0UNNSh6hJ9ByGAKFLWeSb2ZlkQIoocXj61Uf9Ocpz/zSOjpv0lqfoOruTdN+mwxw37nddXGIJqTOBMpolVJUN2g/o8wzllpSBddHRyLQVVhcDEaiYeBGqF0X/oKZ0ZLyDNAsHnCdSb76prmRkPEiceTSvjboePjUgM0XtN1fm4fVIWWHAC+V3ixiBELc3rAZaoxMz2bbv54AIJi9fFQm3vVVlUTEM7aYVYAvZEyZZxXQF4Q==
ARC-Message-Signature: i=1; a=rsa-sha256; c=relaxed/relaxed; d=microsoft.com;
 s=arcselector9901;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=nCcdMOgHx+exsmG+se5QictMZ3B74JDcMoga/+8aTVQ=;
 b=hL5MQxI2V4tz0Pq9e81/zs2euzTRTRwM+mnX3ph2GuBHDKvKUke5ozNNNm0qKuNZHysJPo0Yw5rbgDWCrlaFgKSjpH4PlrLvcT02tZdWwrHkc2N3L/0Np/WYbl7/YKavh7evWGc1JTdkid6wv2JKDViAfUiR3wJDhFNdAMFax8jkr35d5uvF+t4veU8Qefmjemek/0/Mr4Jt9vdJ1Tok+StypZCjPRefTbMojI36sHXkxSYA6BE6B1xhnifESPQAmk4Ss8ViUmTph0US3Ebzyd0mrNu4L3EZ2UamRmv3JknJT8z7KtIlvG9RzPLeS9ftTVowYivRuMBWvSHOl61hZw==
ARC-Authentication-Results: i=1; mx.microsoft.com 1; spf=pass
 smtp.mailfrom=oracle.com; dmarc=pass action=none header.from=oracle.com;
 dkim=pass header.d=oracle.com; arc=none
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
 d=oracle.onmicrosoft.com; s=selector2-oracle-onmicrosoft-com;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=nCcdMOgHx+exsmG+se5QictMZ3B74JDcMoga/+8aTVQ=;
 b=HR9YXnC8kWOHIqJ58jLL5puaXevKfbodadxD1QaC9b3XOY3FSn+DPzqSUAIdDgHGD5xFoAtPXrNccQX49tvYeitpyVg7HQzAhxwnBiM6SyPq4a3lwsyBtVJPHtBDOzdNPrU0gHsXrm9rKomZerQRi7qln7FMYe48tyFyj+nSQ/c=
Authentication-Results: kernel.org; dkim=none (message not signed)
 header.d=none;kernel.org; dmarc=none action=none header.from=oracle.com;
Received: from BYAPR10MB2663.namprd10.prod.outlook.com (2603:10b6:a02:a9::20)
 by BY5PR10MB4114.namprd10.prod.outlook.com (2603:10b6:a03:211::16) with
 Microsoft SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.3868.31; Tue, 23 Feb
 2021 20:37:00 +0000
Received: from BYAPR10MB2663.namprd10.prod.outlook.com
 ([fe80::b52e:bdd3:d193:4d14]) by BYAPR10MB2663.namprd10.prod.outlook.com
 ([fe80::b52e:bdd3:d193:4d14%7]) with mapi id 15.20.3846.041; Tue, 23 Feb 2021
 20:37:00 +0000
From: Dongli Zhang <dongli.zhang@oracle.com>
To: x86@kernel.org, kvm@vger.kernel.org
Cc: linux-kernel@vger.kernel.org, pbonzini@redhat.com,
        seanjc@google.com, vkuznets@redhat.com, wanpengli@tencent.com,
        jmattson@google.com, joro@8bytes.org, tglx@linutronix.de,
        mingo@redhat.com, bp@alien8.de, hpa@zytor.com
Subject: [PATCH 1/1] KVM: x86: remove incorrect comment on active_mmu_pages
Date: Tue, 23 Feb 2021 12:37:07 -0800
Message-Id: <20210223203707.1135-1-dongli.zhang@oracle.com>
X-Mailer: git-send-email 2.17.1
X-Originating-IP: [138.3.200.16]
X-ClientProxiedBy: BYAPR07CA0044.namprd07.prod.outlook.com
 (2603:10b6:a03:60::21) To BYAPR10MB2663.namprd10.prod.outlook.com
 (2603:10b6:a02:a9::20)
MIME-Version: 1.0
X-MS-Exchange-MessageSentRepresentingType: 1
Received: from localhost.localdomain (138.3.200.16) by
 BYAPR07CA0044.namprd07.prod.outlook.com (2603:10b6:a03:60::21) with Microsoft
 SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.3890.19 via Frontend
 Transport; Tue, 23 Feb 2021 20:37:00 +0000
X-MS-PublicTrafficType: Email
X-MS-Office365-Filtering-Correlation-Id: 479b1ce6-9873-46c8-c5bb-08d8d83ac550
X-MS-TrafficTypeDiagnostic: BY5PR10MB4114:
X-Microsoft-Antispam-PRVS: 
 <BY5PR10MB41145B1CA1E67EB59F320409F0809@BY5PR10MB4114.namprd10.prod.outlook.com>
X-MS-Oob-TLC-OOBClassifiers: OLM:605;
X-MS-Exchange-SenderADCheck: 1
X-Microsoft-Antispam: BCL:0;
X-Microsoft-Antispam-Message-Info: 
 wz8zyH88T5kx7HN/gqxtIVTs4W5oKdRHJIJFEpw/cfCfRhGKvbNujF2X3/g8NGTr67GWnQUkBkE7q4oV0nWPvfI3KRBOqDEmh4yut3mbo2w7+CKBy9zPeqlpUz1OVP2k4HYAPxqny6ktTLzsAvhjTkGUN2FzuAXOE1m4D7ewy+svfYGeOdnnr7JVvmBOHyYXfYCsoSGq0bTk50IRSL9dvDmhdMawAFM7+AP+qUfhwLFwoZu3rN/8NMwlYaDqS2Y0iBRRWzK11GebZ+Fmt6w1cKhNwpd0ocMyI+ur41l8CzepzzXPkLW8LETKb5EM1wMqNI4wAxphCQ+Vk+H/MVQWl2Sdd6x3xdq0rhokH19IOp6HXOBP1DUMSNTuetS8cNGs5cvorWnO88GtqMLGDVBzuY16j5/3mBqku8YplcB/Da6gwenHyJ3oSpgOFppfDwIa5Z2hWi++A8q9zAHav9FEmmYkd0jnzASefqAyOYP6NEcAdDD2ipA8hc9sKErU9Pb8MEe+15jHcPyGTsEkaUZzDGy3xkCRVkJN1FWH2oRuiApBOKMRaVZc8ux1eqrLVPmPhRMqBxGxZdbs/Ek0MxHLjg==
X-Forefront-Antispam-Report: 
 CIP:255.255.255.255;CTRY:;LANG:en;SCL:1;SRV:;IPV:NLI;SFV:NSPM;H:BYAPR10MB2663.namprd10.prod.outlook.com;PTR:;CAT:NONE;SFS:(136003)(376002)(366004)(396003)(346002)(39860400002)(66476007)(36756003)(2616005)(52116002)(956004)(44832011)(26005)(83380400001)(478600001)(66946007)(4744005)(66556008)(6506007)(1076003)(16526019)(86362001)(316002)(4326008)(7416002)(8676002)(6512007)(69590400012)(5660300002)(186003)(6486002)(8936002)(2906002);DIR:OUT;SFP:1101;
X-MS-Exchange-AntiSpam-MessageData: 
 hEPkpk8ApuoITbVlPawvZKhptdYRn1v87jNaWjtOByNlC3cHy70N41zSLlMRhyE/3b2greh5wZj1bdXw/XNF2SXbmZ0RqnI+en6zG5nQL4h2VETXKom6F/ocx2Zavxu4D39J9s0TM/+PT4P0H6sLbyKfPelToaDF9eftvC0p9SxRh95iN5DF5uQwSWSY9747bl7qOJ31rGkSjNJEylja8vMckBW4d4cIZBO+kZrzy5LAjfuKsfBBrEhe4OfqtPJ+/ea/uz+yto0DDs9i5J4Psj0hwxdGg0JI3yeNiZTAEALPncoookCDTpVdntmu433Xk3ODE63FN9DUYgPDHoXVMc3wZ6KYQ0T8UEixyJFyUBkoxGumUsQfLMmI14O7ZMC+m39iMZzBOBAfDpZiOWbB2OGt35AQOpCm8iA8BAGBKjOi8zu/mFP4G9twDfeuFN8mUld5auXHb2Ar1waNfvQKL7L5aTgz1WDYpEMvHtP3Diy8FHHH/qlnLJsfzlfxEtz5+WVhDrIiVoo08Ue5WUKqrAZdiqyUOlCf9PE3kKmgJsfomznGs8H0TTWxIiLnUNf+0ZRa0tdNd4JgDXkHrgR3r813rwK2wQhEpN2t/9fDk//dgtbCnn7aFHFcCqmSh0V5JYOIFnT/rCk3cpYt8e/0i1NYMfsXEPMv5kC9bdlTQ8+wFOppXt7KQ+yulN7rNvBt3i+nP7/+3GuYk5SNvhK23G+Y0ReIRZuTuYOi6OrOuQWkbpw3YUXxI89ukUoZzTGV6T25rjkPjNlKaq/KIEMtLg2NfiGI242W0zPHzcsc22EQpHLv4vDByDfwoMK1mpGOsZ0XRs/HMRYbbJuYyKBCDNYqMasGqaqEjgdC6KtZGFXMcWl3tUeEMwgh35l96fwQ3vNrR+mrDNutCZqtJ8wGI1MtIgn6bwkbAJT8QNRAvLOGfWeHimmNCP/PEED6VB64AP6RVFKHxo1Brg3UHfOsEC3ja6QmehKnUZgHRtqjtvCdL+leTG6yA8k1hypUgBFnGsB2tFT8ok1wOlUdzglPsHYdwcq7GouShzAbgUpxTdSgjHcE8K/S5XRgN66Jw1thLnmmMipSm9n/uhiZNh17lYJ2fi/rLJkEMJb5a127oZkH+sUd30NDOk2fZWLh8QUyrZ2alTcT2aKkcPAbif3R2jm331VAmwutUflC0o0qWVrGIHwz/boV6t5GirLUuwvxwS2cc+ucNp8/IhLyXIT0FD7UAXkawj5atUvM8PRTTBtY2+1uh1Um01POuvHx2HK1iMNywhaqXXLY3nG3tmvDV21fzyXx+sFGv3TgBoFW7O9mABMx6SuH9MD3Kvqrnbaj
X-OriginatorOrg: oracle.com
X-MS-Exchange-CrossTenant-Network-Message-Id: 
 479b1ce6-9873-46c8-c5bb-08d8d83ac550
X-MS-Exchange-CrossTenant-AuthSource: BYAPR10MB2663.namprd10.prod.outlook.com
X-MS-Exchange-CrossTenant-AuthAs: Internal
X-MS-Exchange-CrossTenant-OriginalArrivalTime: 23 Feb 2021 20:37:00.4412
 (UTC)
X-MS-Exchange-CrossTenant-FromEntityHeader: Hosted
X-MS-Exchange-CrossTenant-Id: 4e2c6054-71cb-48f1-bd6c-3a9705aca71b
X-MS-Exchange-CrossTenant-MailboxType: HOSTED
X-MS-Exchange-CrossTenant-UserPrincipalName: 
 I8Mbavn7ZASJ9mxD7pJtOLFoE9HGgDXFgv9CjU3+2WTT3RDJSXjWfHJFuiv4a6t66OixXfQ6Rkkt7uJODKDJTQ==
X-MS-Exchange-Transport-CrossTenantHeadersStamped: BY5PR10MB4114
X-Proofpoint-Virus-Version: vendor=nai engine=6200 definitions=9904
 signatures=668683
X-Proofpoint-Spam-Details: rule=notspam policy=default score=0 suspectscore=0
 mlxscore=0 spamscore=0
 mlxlogscore=999 adultscore=0 bulkscore=0 malwarescore=0 phishscore=0
 classifier=spam adjust=0 reason=mlx scancount=1 engine=8.12.0-2009150000
 definitions=main-2102230174
X-Proofpoint-Virus-Version: vendor=nai engine=6200 definitions=9904
 signatures=668683
X-Proofpoint-Spam-Details: rule=notspam policy=default score=0 suspectscore=0
 spamscore=0
 priorityscore=1501 impostorscore=0 bulkscore=0 mlxscore=0 malwarescore=0
 clxscore=1011 phishscore=0 mlxlogscore=999 lowpriorityscore=0 adultscore=0
 classifier=spam adjust=0 reason=mlx scancount=1 engine=8.12.0-2009150000
 definitions=main-2102230174
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The 'mmu_page_hash' is used as hash table while 'active_mmu_pages' is a
list. This patch removes the incorrect comment on active_mmu_pages.

Signed-off-by: Dongli Zhang <dongli.zhang@oracle.com>
---
 arch/x86/include/asm/kvm_host.h | 3 ---
 1 file changed, 3 deletions(-)

```
#### [PATCH 1/2] KVM: vmx/pmu: Fix dummy check if lbr_desc->event is created
##### From: Like Xu <like.xu@linux.intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Like Xu <like.xu@linux.intel.com>
X-Patchwork-Id: 12099715
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.7 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED,USER_AGENT_GIT
	autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 809C8C433DB
	for <kvm@archiver.kernel.org>; Tue, 23 Feb 2021 01:49:06 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 3EC5C64D5D
	for <kvm@archiver.kernel.org>; Tue, 23 Feb 2021 01:49:06 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S230248AbhBWBss (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Mon, 22 Feb 2021 20:48:48 -0500
Received: from mga01.intel.com ([192.55.52.88]:61186 "EHLO mga01.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S230099AbhBWBss (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 22 Feb 2021 20:48:48 -0500
IronPort-SDR: 
 7FhznoiHTqU5i/ixzuUKyErezaQgRbIjVK3/13WowIu1j9V2K6gFQLjj4w11wXNaU6YCyDUOHQ
 yA1o0NOvamGQ==
X-IronPort-AV: E=McAfee;i="6000,8403,9903"; a="204074435"
X-IronPort-AV: E=Sophos;i="5.81,198,1610438400";
   d="scan'208";a="204074435"
Received: from fmsmga004.fm.intel.com ([10.253.24.48])
  by fmsmga101.fm.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 22 Feb 2021 17:47:02 -0800
IronPort-SDR: 
 TnqcXWgI8AzeQoutJT/a0nG3o/Kg5Ru5L7vxJfg/4eMqupzJMgW45FmjKX22B5H/C6J3AOQRzV
 Cj9N5heluTNw==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.81,198,1610438400";
   d="scan'208";a="423349289"
Received: from clx-ap-likexu.sh.intel.com ([10.239.48.108])
  by fmsmga004.fm.intel.com with ESMTP; 22 Feb 2021 17:46:59 -0800
From: Like Xu <like.xu@linux.intel.com>
To: Paolo Bonzini <pbonzini@redhat.com>,
        Sean Christopherson <seanjc@google.com>
Cc: Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>, kvm@vger.kernel.org,
        x86@kernel.org, linux-kernel@vger.kernel.org
Subject: [PATCH 1/2] KVM: vmx/pmu: Fix dummy check if lbr_desc->event is
 created
Date: Tue, 23 Feb 2021 09:39:57 +0800
Message-Id: <20210223013958.1280444-1-like.xu@linux.intel.com>
X-Mailer: git-send-email 2.29.2
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

If lbr_desc->event is successfully created, the intel_pmu_create_
guest_lbr_event() will return 0, otherwise it will return -ENOENT,
and then jump to LBR msrs dummy handling.

Fixes: 1b5ac3226a1a ("KVM: vmx/pmu: Pass-through LBR msrs when the guest LBR event is ACTIVE")
Signed-off-by: Like Xu <like.xu@linux.intel.com>
---
 arch/x86/kvm/vmx/pmu_intel.c | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
#### [RFC v4 01/11] eventfd: Increase the recursion depth of eventfd_signal()
##### From: Xie Yongji <xieyongji@bytedance.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Xie Yongji <xieyongji@bytedance.com>
X-Patchwork-Id: 12100213
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.7 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED,USER_AGENT_GIT
	autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id A8DC6C433DB
	for <kvm@archiver.kernel.org>; Tue, 23 Feb 2021 11:53:47 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 5BA0B64E3F
	for <kvm@archiver.kernel.org>; Tue, 23 Feb 2021 11:53:47 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S232498AbhBWLxj (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 23 Feb 2021 06:53:39 -0500
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:51736 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S232471AbhBWLwf (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 23 Feb 2021 06:52:35 -0500
Received: from mail-pf1-x436.google.com (mail-pf1-x436.google.com
 [IPv6:2607:f8b0:4864:20::436])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id AB560C06178B
        for <kvm@vger.kernel.org>; Tue, 23 Feb 2021 03:51:49 -0800 (PST)
Received: by mail-pf1-x436.google.com with SMTP id w18so8615163pfu.9
        for <kvm@vger.kernel.org>; Tue, 23 Feb 2021 03:51:49 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=bytedance-com.20150623.gappssmtp.com; s=20150623;
        h=from:to:cc:subject:date:message-id:in-reply-to:references
         :mime-version:content-transfer-encoding;
        bh=c3yBROiXapYXwEB1EPrfm+Nn9EEmtLH7D5B0d4oZlD4=;
        b=yGAHM8CXAX/x224wjeWCQAdixy7fpHoGLdsZfgNfS/gc7Vsv1CMk83cLMhmqBbU78u
         F7/x93MGjcQvvo1ZeiDs4pZOazPlpnHThYBXANWVPpUvXakoz3duDUKs66lbYhshiqck
         Vl8s010niUh8rCEDp2+4PAEVavuqnqjQo5fwfVAqkPCKcXCfoYOWMwBs94oLtXS2kAnX
         CteuR3/gRPG/nabtf6uiiOqLZcNe/zTTa5iwfcz5k8mPtzr3BXzLXuKFt+85uzhTyDqq
         cg4ng/58CgyFL3HinNfWnwCG3wSdZevKQb4eaj6iaO9sd24moq/n/tOdZ9kiZmHHhIBb
         O5gA==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:in-reply-to
         :references:mime-version:content-transfer-encoding;
        bh=c3yBROiXapYXwEB1EPrfm+Nn9EEmtLH7D5B0d4oZlD4=;
        b=qhtSkq2LYzxqVfmEGUuDnHi7pbcOILmU4kdUtrHCKq4x2clkcwix6sIBqF/UR0WXOy
         vFgI4hNtNckm6+/sIesJh7YXE1SMzoVXEbG5xVsE4B4deXm/9GwK+Z7lA9ORT5vVAU8n
         FpKrrSqBJX28BOIkmx438WcSY+iqDx+bM3ZkqjAAMT9Rao7vqrTp3Ht8o+hbl39s5eIt
         FBWOpECZev8KNFYAh+MmcdjV9AnbeXEDFNfJrO4xh/psrMEfqd5f+GG8HwMjzFFdEqUM
         M/EhZ3NQn4+J3QHhqnxlckhjYAQh2NMGaBgkvH4WGJUGRlLrALvw6Rq5AFAxZ0n7JAj3
         8Uvg==
X-Gm-Message-State: AOAM531hJ4iNmpLIKlTEinzNtBsd3w944WtPhOGyhv1Ca7O+A1x/fbWz
        vj5/6BLAT2IAahEqPcJjUOje
X-Google-Smtp-Source: 
 ABdhPJwAHNMqoT+iE+s8fClzO6jv2nzIUjZdtdu3bpXHD3CThaZLgO4WvJzwBPfwmbfWQrMRm/TBkw==
X-Received: by 2002:a65:4947:: with SMTP id q7mr11508562pgs.83.1614081109248;
        Tue, 23 Feb 2021 03:51:49 -0800 (PST)
Received: from localhost ([139.177.225.253])
        by smtp.gmail.com with ESMTPSA id
 l15sm3001657pjq.9.2021.02.23.03.51.48
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Tue, 23 Feb 2021 03:51:48 -0800 (PST)
From: Xie Yongji <xieyongji@bytedance.com>
To: mst@redhat.com, jasowang@redhat.com, stefanha@redhat.com,
        sgarzare@redhat.com, parav@nvidia.com, bob.liu@oracle.com,
        hch@infradead.org, rdunlap@infradead.org, willy@infradead.org,
        viro@zeniv.linux.org.uk, axboe@kernel.dk, bcrl@kvack.org,
        corbet@lwn.net
Cc: virtualization@lists.linux-foundation.org, netdev@vger.kernel.org,
        kvm@vger.kernel.org, linux-aio@kvack.org,
        linux-fsdevel@vger.kernel.org
Subject: [RFC v4 01/11] eventfd: Increase the recursion depth of
 eventfd_signal()
Date: Tue, 23 Feb 2021 19:50:38 +0800
Message-Id: <20210223115048.435-2-xieyongji@bytedance.com>
X-Mailer: git-send-email 2.25.1
In-Reply-To: <20210223115048.435-1-xieyongji@bytedance.com>
References: <20210223115048.435-1-xieyongji@bytedance.com>
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Increase the recursion depth of eventfd_signal() to 1. This
is the maximum recursion depth we have found so far.

Signed-off-by: Xie Yongji <xieyongji@bytedance.com>
---
 fs/eventfd.c            | 2 +-
 include/linux/eventfd.h | 5 ++++-
 2 files changed, 5 insertions(+), 2 deletions(-)

```
#### [PATCH 1/4 v3] KVM: nSVM: Do not advance RIP following VMRUN completion if the latter is single-stepped
##### From: Krish Sadhukhan <krish.sadhukhan@oracle.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Krish Sadhukhan <krish.sadhukhan@oracle.com>
X-Patchwork-Id: 12100855
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-18.7 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,
	INCLUDES_PATCH,MAILING_LIST_MULTI,MSGID_FROM_MTA_HEADER,SPF_HELO_NONE,
	SPF_PASS,URIBL_BLOCKED,USER_AGENT_GIT autolearn=ham autolearn_force=no
	version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 46E3CC433DB
	for <kvm@archiver.kernel.org>; Tue, 23 Feb 2021 20:11:57 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 0E70A64E7A
	for <kvm@archiver.kernel.org>; Tue, 23 Feb 2021 20:11:57 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S234191AbhBWULu (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 23 Feb 2021 15:11:50 -0500
Received: from userp2120.oracle.com ([156.151.31.85]:39738 "EHLO
        userp2120.oracle.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S234177AbhBWUKE (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 23 Feb 2021 15:10:04 -0500
Received: from pps.filterd (userp2120.oracle.com [127.0.0.1])
        by userp2120.oracle.com (8.16.0.42/8.16.0.42) with SMTP id
 11NK4xJk023448;
        Tue, 23 Feb 2021 20:08:18 GMT
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=oracle.com;
 h=from : to : cc :
 subject : date : message-id : in-reply-to : references :
 content-transfer-encoding : content-type : mime-version;
 s=corp-2020-01-29; bh=Zu8rfJyHRcTfVFgb/PRcCVioUNaAej5CPTn06OpwxaI=;
 b=ANYPDjznlJLRPt86883JwK154JQHPr4pQmUSP2/+mDP2AZbHRR9uswpMFlX3FUW4070U
 PJgFM44CkIVWK3RalIoPaeicnxAYgDRyI0UT3zRfCOkdSEKbX+cewLaxMOg/MBjEs3ZI
 FKrCR0PYGUMj/kWndtk9BdLot1Nx+n0hBTcBhk8re21bH1IjlUXbEFZPsZS2hk7tfU4H
 CuolpUtZom8UgBcHtD4nQSkgauyBueLsyE/uyyhurQO0T4C2NNIwUrw6AzpelYlXyldC
 6eBXJ4WQfpg31F1b5ObLGPrttcfnVQK1v1GiyVg4seihJNf2kT94eBwMB5c2TB758u5h 0A==
Received: from userp3030.oracle.com (userp3030.oracle.com [156.151.31.80])
        by userp2120.oracle.com with ESMTP id 36ugq3fjet-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Tue, 23 Feb 2021 20:08:18 +0000
Received: from pps.filterd (userp3030.oracle.com [127.0.0.1])
        by userp3030.oracle.com (8.16.0.42/8.16.0.42) with SMTP id
 11NK6Vd8106920;
        Tue, 23 Feb 2021 20:08:17 GMT
Received: from nam12-bn8-obe.outbound.protection.outlook.com
 (mail-bn8nam12lp2175.outbound.protection.outlook.com [104.47.55.175])
        by userp3030.oracle.com with ESMTP id 36ucbxyc3h-2
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Tue, 23 Feb 2021 20:08:17 +0000
ARC-Seal: i=1; a=rsa-sha256; s=arcselector9901; d=microsoft.com; cv=none;
 b=jgjtjiZo7w+ij7pFJ//t9ZHTsWDjaHtc/2TPrRz5evSIGfRO8bmfS1Hnt4pGxW4EWLJ65BF9DbhMFs80thDQWwR0KMwBl+a9LF1CT6q1TDUak1MY2RBpYbLKwJnDuVbg74BgBCDr/sKX614RUMOtHWYCaNQRjiLX6XGPGp562/c0mXS50XuvPoSto6dw+O/NicUHOYR2tTIaP3CPsdpao2faHQtNsAdmyOVfVPDJIyfjMcMGNKNRTWByiMehq4RuNQK10Hwx6hGg4npG0iA75MNIkw1XC+A9K52BJlp7QAubXRXRQ8NV3Km7vDid8KiqL5EW7bT7M5lXok0LGQVJ/w==
ARC-Message-Signature: i=1; a=rsa-sha256; c=relaxed/relaxed; d=microsoft.com;
 s=arcselector9901;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=Zu8rfJyHRcTfVFgb/PRcCVioUNaAej5CPTn06OpwxaI=;
 b=ZFeZscCqPFdTWB8cfFJhIaDm2TlAyToJoPEr5B97nEhurY13mB8GwpWjdYgHoV1VefwYSBcs/eOOSLpUx0bfmGd3K3FJOvOazB0qpIRWe4uv78rZJScsSFFqWZoAHrWw4PnzB3Xv4FLhA2vuX+9Ef2fLYBnxVzqouo4uxYlNh4OA/7w/mYT3y5iO0/tGFJH4HdBRoFb3WOx4f3UdFiT6HoeEiLqWTJZDNz5vDuoYaa90Pk6TwNOe9SqzmLEVZtN85WiYKny3m4qJSINL79Gw2fTbJfQAstsMGN2JsoVoV/c2VnHCAPk4BwaUOIwnY9VmFD81PGSvv77vsybt6bNyQA==
ARC-Authentication-Results: i=1; mx.microsoft.com 1; spf=pass
 smtp.mailfrom=oracle.com; dmarc=pass action=none header.from=oracle.com;
 dkim=pass header.d=oracle.com; arc=none
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
 d=oracle.onmicrosoft.com; s=selector2-oracle-onmicrosoft-com;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=Zu8rfJyHRcTfVFgb/PRcCVioUNaAej5CPTn06OpwxaI=;
 b=ziyYwZpEU+OkqrWTt+fNkCxy3S3k9JFWeKhci1bZPIxLidjh5d91jfCtRI92fAjBmpqJDt5mJBd8JvZ8q80nqbgq7hqoB6nrOyXvJzbhI3P1BLNnMuwf0hvqD0hamq0c/E98pAVL9RZB1NhRBJ8NehEz4psOqpLA5YcwG1Oy59c=
Authentication-Results: vger.kernel.org; dkim=none (message not signed)
 header.d=none;vger.kernel.org; dmarc=none action=none header.from=oracle.com;
Received: from SN6PR10MB3021.namprd10.prod.outlook.com (2603:10b6:805:cc::19)
 by SN6PR10MB3022.namprd10.prod.outlook.com (2603:10b6:805:d8::25) with
 Microsoft SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.3868.27; Tue, 23 Feb
 2021 20:08:15 +0000
Received: from SN6PR10MB3021.namprd10.prod.outlook.com
 ([fe80::1871:3741:cc17:bcf7]) by SN6PR10MB3021.namprd10.prod.outlook.com
 ([fe80::1871:3741:cc17:bcf7%7]) with mapi id 15.20.3868.033; Tue, 23 Feb 2021
 20:08:15 +0000
From: Krish Sadhukhan <krish.sadhukhan@oracle.com>
To: kvm@vger.kernel.org
Cc: pbonzini@redhat.com, jmattson@google.com, seanjc@google.com
Subject: [PATCH 1/4 v3] KVM: nSVM: Do not advance RIP following VMRUN
 completion if the latter is single-stepped
Date: Tue, 23 Feb 2021 14:19:55 -0500
Message-Id: <20210223191958.24218-2-krish.sadhukhan@oracle.com>
X-Mailer: git-send-email 2.25.4
In-Reply-To: <20210223191958.24218-1-krish.sadhukhan@oracle.com>
References: <20210223191958.24218-1-krish.sadhukhan@oracle.com>
X-Originating-IP: [138.3.200.29]
X-ClientProxiedBy: BY3PR05CA0026.namprd05.prod.outlook.com
 (2603:10b6:a03:254::31) To SN6PR10MB3021.namprd10.prod.outlook.com
 (2603:10b6:805:cc::19)
MIME-Version: 1.0
X-MS-Exchange-MessageSentRepresentingType: 1
Received: from ban25x6uut29.us.oracle.com (138.3.200.29) by
 BY3PR05CA0026.namprd05.prod.outlook.com (2603:10b6:a03:254::31) with
 Microsoft SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.3890.10 via Frontend
 Transport; Tue, 23 Feb 2021 20:08:14 +0000
X-MS-PublicTrafficType: Email
X-MS-Office365-Filtering-Correlation-Id: db3ffe92-c370-4361-616c-08d8d836c106
X-MS-TrafficTypeDiagnostic: SN6PR10MB3022:
X-Microsoft-Antispam-PRVS: 
 <SN6PR10MB30222E30669C7853B388C24F81809@SN6PR10MB3022.namprd10.prod.outlook.com>
X-MS-Oob-TLC-OOBClassifiers: OLM:7691;
X-MS-Exchange-SenderADCheck: 1
X-Microsoft-Antispam: BCL:0;
X-Microsoft-Antispam-Message-Info: 
 A64eL3FuqI/pllC4pzUmuPnmuv5wW39/DtDeeWv04byg6UxALVmPqCf6noSuslpzgC7G10x38vjq7dGuAOHDnkkwUmBd2DpaeqjhqdBOB40rEgQ+TqzqMa53zIvGnn/sLCJ9Acf+Pc0GfGEwK6liFznxjAWF5UDA03T+Sw1AcEecxMUWlbJXkTbojcjE/S4BDa0lyha971JlPQ/fCPUCP8QBDRSzr3gUuVrx0EZc6N4KsrHyRtotZRtG2OzaE/H1yJvJL6wPzOj0WNWBhwAn10doNx0fQFBjZsCevNHFhujAqDCH4wSuMesgewy9hhFViX3y4SNHHkAnfU7o1mFMgtUYyH7NiPcyQ6HYeZ+/lYByhiFQ2Q5uu87T5snre5BGH0AvyGjnGl6IMTvSeEcCGra8cie/r6VqKeDQGoTVgtWgi/eSmthDMYtybXgfxlKL1uX9MdQadi2Bbx4LpIO9futYU0rL4dlULQ6OJqF8j9jztV1PdMw/zU1dCcI0REv+In9Gd9uFFj6ZQJDeiRwvEw==
X-Forefront-Antispam-Report: 
 CIP:255.255.255.255;CTRY:;LANG:en;SCL:1;SRV:;IPV:NLI;SFV:NSPM;H:SN6PR10MB3021.namprd10.prod.outlook.com;PTR:;CAT:NONE;SFS:(39860400002)(346002)(366004)(396003)(376002)(136003)(66946007)(26005)(86362001)(7696005)(66476007)(66556008)(52116002)(1076003)(186003)(44832011)(16526019)(36756003)(6666004)(316002)(956004)(2616005)(6916009)(5660300002)(6486002)(4326008)(83380400001)(2906002)(478600001)(8676002)(8936002);DIR:OUT;SFP:1101;
X-MS-Exchange-AntiSpam-MessageData: 
 gV8XunApVChU+Vezzb5bPLR/zsu+Ekb19/BVSqLAU3goX1mtPAhi0JMK9rdgcg2WjXdXa3K5rnriqGNib+HkeJTUL+XW8FOlXrEhls1y65370Y9US0JjxVkcw7VcbZhGW4H+r/gdZOLXz+nkEQOpQy5CXsk24sQgGJCcU2yeOzlvOlx22HQOsLkpmER1EVjJx1ehCzWX8gILrsBH8c/O2wy+jYRvY+GXgx0AQwPkP+0lGEL5fdkYgxxGm9PDC46xMUke+7nDQ441wdGzjykMpN9k1jCDppMd04WTFC1Ojniuj15zmQWleJQLj/OPdxa31AjK8hNIVfBdJOXAGPn27520zxQud0detEt6pN1oY/4r3kCOhj/RHf+TUItMBdFk0PWO1sTsayBspD6bUAOtoQfW4X8VtAmZbbv3ID0RBToqolW6fawIQhmE6HNxql4TpyjuDN9amZw5ODOiq70A91iSFAIdKKiCzdWWV+j+441ozbFk6hbedEMK1NiNKkN6Oih/8+6NECfMAzsq9xEUN97wgQF8R71+TlaljmFYAPgR5OTQ2fTurauePdWKTmKd543N1iYe4gWfxoeL1CW/wVTCeBA/R2sY/J3SsAzq9EkW0RiJj8CVdg7sJToO1A+yHrIY6zJZGihIXM0/mWcH+vOdpHxMEt/0sJZSo47EV6AdJ3S+f+FEB6nZjC+O2tcud4nYRBDP/kgv/CX99ETosXg3IiX+G1bNwYERNiYJvrLJga2wT7zaoUP1Ac4DEpuAmkGzRSFRCxxO2MpkyF1mrPGO/XVIQNSp0xZVg2CTo+voBgvwxp+8e0xZhEfaOqHs+8DZgTh9KCkNzSxaPFhv2UDLAqyNw/Jq7gwOhXU17a+vkGCCtzcEsjvzK24LmiGFbUtdM6e05boxWOmJaxpXW7VBiUOewhnkC/BZwWz59ZpmTuzyJVND0IonmjTCCLsu/p017PVBhW+3Ew4DFAHjbsAiCYU89pfdiaiLmT/uFJ+wWAej8RZJoyAddz8jBocnQO9PeR4y88YEoAkk46Woq+2QDgySKyXlyItZWEk1kp5cXyAplccxS7m5duC4iObjco/YGtIhFRz4G/UnEM1cRCHa+4XD7cW8VsiPRYVuqHKJtHNllUToUH65dmi9WJQtctFTI/m0kLjj9GwOdmZBALAUmTb6cn29iPl2l5pZndrLM0sUEwyNf74jZ/IS4GjM+reuLCO83S3+uPH4wbMdHn2JVqj7m9q0w6sgPI6wn0pXsuBcOrNS/yF/UqNry/7ozu5l3D5t89d46e28GATE2VghgeUbNZn5/wj7B2gPEEW8Vz/d+dkg+Vc7GZZKuwKC
X-OriginatorOrg: oracle.com
X-MS-Exchange-CrossTenant-Network-Message-Id: 
 db3ffe92-c370-4361-616c-08d8d836c106
X-MS-Exchange-CrossTenant-AuthSource: SN6PR10MB3021.namprd10.prod.outlook.com
X-MS-Exchange-CrossTenant-AuthAs: Internal
X-MS-Exchange-CrossTenant-OriginalArrivalTime: 23 Feb 2021 20:08:15.3528
 (UTC)
X-MS-Exchange-CrossTenant-FromEntityHeader: Hosted
X-MS-Exchange-CrossTenant-Id: 4e2c6054-71cb-48f1-bd6c-3a9705aca71b
X-MS-Exchange-CrossTenant-MailboxType: HOSTED
X-MS-Exchange-CrossTenant-UserPrincipalName: 
 2ysVrlQm7yeTPbQmTQGWdGLVL2+mPp2q7hT2YmD800NG+BbRYy8eOy/YPc3J1wXvNa3Qwo2t+rlGQfBQjpHadC/3YvT/xhKNs0KglEZU66s=
X-MS-Exchange-Transport-CrossTenantHeadersStamped: SN6PR10MB3022
X-Proofpoint-Virus-Version: vendor=nai engine=6200 definitions=9904
 signatures=668683
X-Proofpoint-Spam-Details: rule=notspam policy=default score=0 mlxlogscore=846
 adultscore=0
 phishscore=0 spamscore=0 suspectscore=0 bulkscore=0 malwarescore=0
 mlxscore=0 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.12.0-2009150000 definitions=main-2102230169
X-Proofpoint-Virus-Version: vendor=nai engine=6200 definitions=9904
 signatures=668683
X-Proofpoint-Spam-Details: rule=notspam policy=default score=0 adultscore=0
 phishscore=0
 malwarescore=0 spamscore=0 mlxscore=0 suspectscore=0 priorityscore=1501
 clxscore=1015 impostorscore=0 lowpriorityscore=0 mlxlogscore=999
 bulkscore=0 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.12.0-2009150000 definitions=main-2102230169
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Currently, svm_vcpu_run() advances the RIP following VMRUN completion when
control returns to host. This works fine if there is no trap flag set
on the VMRUN instruction i.e., if VMRUN is not single-stepped. But if
VMRUN is single-stepped, this advancement of the RIP leads to an incorrect
RIP in the #DB handler invoked for the single-step trap. Therefore, check
if the VMRUN instruction is single-stepped and if so, do not advance the RIP
when the #DB intercept #VMEXIT happens.

Signed-off-by: Krish Sadhukhan <krish.sadhukhan@oraacle.com>
---
 arch/x86/kvm/svm/svm.c | 12 +++++++++++-
 1 file changed, 11 insertions(+), 1 deletion(-)

```
#### [kvm-unit-tests PATCH v2 1/5] libcflat: add SZ_1M and SZ_2G
##### From: Claudio Imbrenda <imbrenda@linux.ibm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Claudio Imbrenda <imbrenda@linux.ibm.com>
X-Patchwork-Id: 12100381
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.8 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT
	autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id C5687C433DB
	for <kvm@archiver.kernel.org>; Tue, 23 Feb 2021 14:08:53 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id A101464E4D
	for <kvm@archiver.kernel.org>; Tue, 23 Feb 2021 14:08:53 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S231717AbhBWOIw (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 23 Feb 2021 09:08:52 -0500
Received: from mx0b-001b2d01.pphosted.com ([148.163.158.5]:61664 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S229996AbhBWOIr (ORCPT
        <rfc822;kvm@vger.kernel.org>); Tue, 23 Feb 2021 09:08:47 -0500
Received: from pps.filterd (m0098413.ppops.net [127.0.0.1])
        by mx0b-001b2d01.pphosted.com (8.16.0.43/8.16.0.43) with SMTP id
 11NE2ZEH155325;
        Tue, 23 Feb 2021 09:08:06 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=ibm.com;
 h=from : to : cc : subject
 : date : message-id : in-reply-to : references : mime-version :
 content-transfer-encoding; s=pp1;
 bh=G1PDUqDMpsNe0ntgFx4AwBRrGhhIiVEZj41qImbLcWc=;
 b=iYDnL5TytSZ66V7xK2m0fENph+8vO4rCwAqZZu+PNDiYwwBU/uNXte6sveregjDr8Xre
 aYONx2lQVEoYg4lZONJPd/uCF9lCxSUYfmqwgRc5MOEEliOuOZTRov9s8E3HdGxrXe5r
 1Nr3Jdr0GypeoQqyp08i+QEMjKyUJaV6SdzkMldhs7T9EFQjDGozDDUt1Rr9f7aXYzr3
 xVTNwNC+bQj5Lw86gGOnoXRAYhMoQfEEni3X8hSoa9bbdT1/mJXFnrUMEW4A5DZuRBaL
 HkfKghZqgeedLfQPpph9jv5YUoaR+/2rp4gvJm+L7suMzFKdRuvBXf8dNUYzHQhjfLpX Wg==
Received: from pps.reinject (localhost [127.0.0.1])
        by mx0b-001b2d01.pphosted.com with ESMTP id 36vkndqy3d-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Tue, 23 Feb 2021 09:08:06 -0500
Received: from m0098413.ppops.net (m0098413.ppops.net [127.0.0.1])
        by pps.reinject (8.16.0.43/8.16.0.43) with SMTP id 11NE34Bb157143;
        Tue, 23 Feb 2021 09:08:05 -0500
Received: from ppma06ams.nl.ibm.com (66.31.33a9.ip4.static.sl-reverse.com
 [169.51.49.102])
        by mx0b-001b2d01.pphosted.com with ESMTP id 36vkndqy2f-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Tue, 23 Feb 2021 09:08:05 -0500
Received: from pps.filterd (ppma06ams.nl.ibm.com [127.0.0.1])
        by ppma06ams.nl.ibm.com (8.16.0.42/8.16.0.42) with SMTP id
 11NE845P017814;
        Tue, 23 Feb 2021 14:08:04 GMT
Received: from b06avi18626390.portsmouth.uk.ibm.com
 (b06avi18626390.portsmouth.uk.ibm.com [9.149.26.192])
        by ppma06ams.nl.ibm.com with ESMTP id 36tsph2nuh-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Tue, 23 Feb 2021 14:08:04 +0000
Received: from b06wcsmtp001.portsmouth.uk.ibm.com
 (b06wcsmtp001.portsmouth.uk.ibm.com [9.149.105.160])
        by b06avi18626390.portsmouth.uk.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id 11NE7mKn30212438
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Tue, 23 Feb 2021 14:07:48 GMT
Received: from b06wcsmtp001.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 1BC40A407E;
        Tue, 23 Feb 2021 14:08:01 +0000 (GMT)
Received: from b06wcsmtp001.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id AA0E0A4081;
        Tue, 23 Feb 2021 14:08:00 +0000 (GMT)
Received: from ibm-vm.ibmuc.com (unknown [9.145.5.213])
        by b06wcsmtp001.portsmouth.uk.ibm.com (Postfix) with ESMTP;
        Tue, 23 Feb 2021 14:08:00 +0000 (GMT)
From: Claudio Imbrenda <imbrenda@linux.ibm.com>
To: kvm@vger.kernel.org
Cc: linux-s390@vger.kernel.org, david@redhat.com, thuth@redhat.com,
        frankja@linux.ibm.com, cohuck@redhat.com, pmorel@linux.ibm.com
Subject: [kvm-unit-tests PATCH v2 1/5] libcflat: add SZ_1M and SZ_2G
Date: Tue, 23 Feb 2021 15:07:55 +0100
Message-Id: <20210223140759.255670-2-imbrenda@linux.ibm.com>
X-Mailer: git-send-email 2.26.2
In-Reply-To: <20210223140759.255670-1-imbrenda@linux.ibm.com>
References: <20210223140759.255670-1-imbrenda@linux.ibm.com>
MIME-Version: 1.0
X-TM-AS-GCONF: 00
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.369,18.0.761
 definitions=2021-02-23_07:2021-02-23,2021-02-23 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 mlxscore=0 bulkscore=0
 mlxlogscore=999 impostorscore=0 lowpriorityscore=0 clxscore=1015
 phishscore=0 adultscore=0 priorityscore=1501 malwarescore=0 spamscore=0
 suspectscore=0 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.12.0-2009150000 definitions=main-2102230119
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Add SZ_1M and SZ_2G to libcflat.h

s390x needs those for large/huge pages

Signed-off-by: Claudio Imbrenda <imbrenda@linux.ibm.com>
Reviewed-by: Thomas Huth <thuth@redhat.com>
---
 lib/libcflat.h | 2 ++
 1 file changed, 2 insertions(+)

```
#### [PATCH v4 1/2] s390/kvm: extend kvm_s390_shadow_fault to return entry pointer
##### From: Claudio Imbrenda <imbrenda@linux.ibm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Claudio Imbrenda <imbrenda@linux.ibm.com>
X-Patchwork-Id: 12100777
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.8 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT
	autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 5C40AC433E0
	for <kvm@archiver.kernel.org>; Tue, 23 Feb 2021 19:15:21 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 2D6CF61606
	for <kvm@archiver.kernel.org>; Tue, 23 Feb 2021 19:15:21 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S233440AbhBWTOy (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 23 Feb 2021 14:14:54 -0500
Received: from mx0a-001b2d01.pphosted.com ([148.163.156.1]:8834 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S233187AbhBWTOs (ORCPT
        <rfc822;kvm@vger.kernel.org>); Tue, 23 Feb 2021 14:14:48 -0500
Received: from pps.filterd (m0098393.ppops.net [127.0.0.1])
        by mx0a-001b2d01.pphosted.com (8.16.0.43/8.16.0.43) with SMTP id
 11NJ3iS8079384;
        Tue, 23 Feb 2021 14:14:07 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=ibm.com;
 h=from : to : cc : subject
 : date : message-id : in-reply-to : references : mime-version :
 content-transfer-encoding; s=pp1;
 bh=ma/SkHeJDp9A11811w0KVELHmlL4klbE9bSZG4nLzrw=;
 b=Y6Ch+3eDadwbflo2wLqvErAv67VXXp7F1qMrByG39kzupa91OYLpv0rDlFvdjovZcsIq
 l4pSLhioN1VyfYSe8BrVIM6g1Q06W1sHIzkB4F/YuAbS5fjH8EWof2kBSfwnkfPt+Xh/
 PW3QFqUR5hI/51Zc3I9Z+rv8plGQtaf2P7+Nq/VMH6vlydqSMvfQGx9kH60DZDzgDrzF
 aaBN6FlB0liihfoNiYj0+TFExZk7si4k05Tybi6HtNAELilI0TFi1RRI4YyAJs10x20q
 IqVYpQ6lMKJJ5DqcrigLFdc17lxBa97J1wcZ5eGcR6Mf4JmbtbHiGRMKS4pd0LA914Yu TQ==
Received: from pps.reinject (localhost [127.0.0.1])
        by mx0a-001b2d01.pphosted.com with ESMTP id 36vkf8uan0-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Tue, 23 Feb 2021 14:14:07 -0500
Received: from m0098393.ppops.net (m0098393.ppops.net [127.0.0.1])
        by pps.reinject (8.16.0.43/8.16.0.43) with SMTP id 11NJ3pLL080078;
        Tue, 23 Feb 2021 14:14:06 -0500
Received: from ppma03fra.de.ibm.com (6b.4a.5195.ip4.static.sl-reverse.com
 [149.81.74.107])
        by mx0a-001b2d01.pphosted.com with ESMTP id 36vkf8uahk-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Tue, 23 Feb 2021 14:14:06 -0500
Received: from pps.filterd (ppma03fra.de.ibm.com [127.0.0.1])
        by ppma03fra.de.ibm.com (8.16.0.42/8.16.0.42) with SMTP id
 11NJDvaQ030691;
        Tue, 23 Feb 2021 19:13:57 GMT
Received: from b06cxnps3074.portsmouth.uk.ibm.com
 (d06relay09.portsmouth.uk.ibm.com [9.149.109.194])
        by ppma03fra.de.ibm.com with ESMTP id 36tt28sgwr-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Tue, 23 Feb 2021 19:13:57 +0000
Received: from d06av23.portsmouth.uk.ibm.com (d06av23.portsmouth.uk.ibm.com
 [9.149.105.59])
        by b06cxnps3074.portsmouth.uk.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id 11NJDslS35258676
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Tue, 23 Feb 2021 19:13:54 GMT
Received: from d06av23.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 560F7A4040;
        Tue, 23 Feb 2021 19:13:54 +0000 (GMT)
Received: from d06av23.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id DAA01A404D;
        Tue, 23 Feb 2021 19:13:53 +0000 (GMT)
Received: from ibm-vm.ibmuc.com (unknown [9.145.5.213])
        by d06av23.portsmouth.uk.ibm.com (Postfix) with ESMTP;
        Tue, 23 Feb 2021 19:13:53 +0000 (GMT)
From: Claudio Imbrenda <imbrenda@linux.ibm.com>
To: linux-kernel@vger.kernel.org
Cc: borntraeger@de.ibm.com, frankja@linux.ibm.com, david@redhat.com,
        cohuck@redhat.com, kvm@vger.kernel.org, linux-s390@vger.kernel.org,
        stable@vger.kernel.org, Janosch Frank <frankja@de.ibm.com>
Subject: [PATCH v4 1/2] s390/kvm: extend kvm_s390_shadow_fault to return entry
 pointer
Date: Tue, 23 Feb 2021 20:13:52 +0100
Message-Id: <20210223191353.267981-2-imbrenda@linux.ibm.com>
X-Mailer: git-send-email 2.26.2
In-Reply-To: <20210223191353.267981-1-imbrenda@linux.ibm.com>
References: <20210223191353.267981-1-imbrenda@linux.ibm.com>
MIME-Version: 1.0
X-TM-AS-GCONF: 00
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.369,18.0.761
 definitions=2021-02-23_08:2021-02-23,2021-02-23 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 bulkscore=0 malwarescore=0
 phishscore=0 adultscore=0 mlxscore=0 priorityscore=1501 clxscore=1015
 spamscore=0 lowpriorityscore=0 suspectscore=0 mlxlogscore=999
 impostorscore=0 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.12.0-2009150000 definitions=main-2102230158
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Extend kvm_s390_shadow_fault to return the pointer to the valid leaf
DAT table entry, or to the invalid entry.

Also return some flags in the lower bits of the address:
PEI_DAT_PROT: indicates that DAT protection applies because of the
              protection bit in the segment (or, if EDAT, region) tables.
PEI_NOT_PTE: indicates that the address of the DAT table entry returned
             does not refer to a PTE, but to a segment or region table.

Signed-off-by: Claudio Imbrenda <imbrenda@linux.ibm.com>
Cc: stable@vger.kernel.org
Reviewed-by: Janosch Frank <frankja@de.ibm.com>
Reviewed-by: David Hildenbrand <david@redhat.com>
---
 arch/s390/kvm/gaccess.c | 30 +++++++++++++++++++++++++-----
 arch/s390/kvm/gaccess.h |  6 +++++-
 arch/s390/kvm/vsie.c    |  8 ++++----
 3 files changed, 34 insertions(+), 10 deletions(-)

```
#### [kvm-unit-tests PATCH v2 1/2] s390x: introduce leave_pstate to leave userspace
##### From: Claudio Imbrenda <imbrenda@linux.ibm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Claudio Imbrenda <imbrenda@linux.ibm.com>
X-Patchwork-Id: 12100399
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.8 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT autolearn=ham
	autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 5251DC433DB
	for <kvm@archiver.kernel.org>; Tue, 23 Feb 2021 14:25:53 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 10D9C64E68
	for <kvm@archiver.kernel.org>; Tue, 23 Feb 2021 14:25:53 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S233022AbhBWOZk (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 23 Feb 2021 09:25:40 -0500
Received: from mx0a-001b2d01.pphosted.com ([148.163.156.1]:63514 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S233017AbhBWOZR (ORCPT
        <rfc822;kvm@vger.kernel.org>); Tue, 23 Feb 2021 09:25:17 -0500
Received: from pps.filterd (m0098396.ppops.net [127.0.0.1])
        by mx0a-001b2d01.pphosted.com (8.16.0.43/8.16.0.43) with SMTP id
 11NE46Bl036766
        for <kvm@vger.kernel.org>; Tue, 23 Feb 2021 09:24:37 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=ibm.com;
 h=from : to : cc : subject
 : date : message-id : in-reply-to : references : mime-version :
 content-transfer-encoding; s=pp1;
 bh=ihKgsX+Xvj1b+4CYCRnNF8GkOKWoFKmipY+GeYpJLS4=;
 b=G6Ml0enUTRuBpd5ZgDKlbcVOoh1rzWHpaL9O3rYxCY4K+uEvCgmz1Fk1amQk5SCrNnOw
 I68Q4+PemkW1wnY1c/xPupTc2SWv7WCb6JuFIZktmjlV10vZnCLx/F24e1Ri7dItlXMj
 401MYUTytBVfJhHlsdpVHkt9GdHVn1tjed+fhSOoF8OjlZgGnOTixgppMGyuf+v3B3Qq
 8yfNJrD1aPy2V8XHAEJXvX3B3nN4t/S5mAufrRpMFqX5c46G1dFmVHj1/fUinfaeMoF+
 LiXpXVBwwNCbwZbck+XayqqNdCpoQN7sZQs2A84fSCBVzTm44bfuNPIPCzj71OUwaEvu NQ==
Received: from pps.reinject (localhost [127.0.0.1])
        by mx0a-001b2d01.pphosted.com with ESMTP id 36vkfuasa5-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT)
        for <kvm@vger.kernel.org>; Tue, 23 Feb 2021 09:24:37 -0500
Received: from m0098396.ppops.net (m0098396.ppops.net [127.0.0.1])
        by pps.reinject (8.16.0.43/8.16.0.43) with SMTP id 11NEI2Vt083290
        for <kvm@vger.kernel.org>; Tue, 23 Feb 2021 09:24:36 -0500
Received: from ppma04fra.de.ibm.com (6a.4a.5195.ip4.static.sl-reverse.com
 [149.81.74.106])
        by mx0a-001b2d01.pphosted.com with ESMTP id 36vkfuas9g-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Tue, 23 Feb 2021 09:24:36 -0500
Received: from pps.filterd (ppma04fra.de.ibm.com [127.0.0.1])
        by ppma04fra.de.ibm.com (8.16.0.42/8.16.0.42) with SMTP id
 11NEMvC7014528;
        Tue, 23 Feb 2021 14:24:34 GMT
Received: from b06cxnps3075.portsmouth.uk.ibm.com
 (d06relay10.portsmouth.uk.ibm.com [9.149.109.195])
        by ppma04fra.de.ibm.com with ESMTP id 36tt289dcy-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Tue, 23 Feb 2021 14:24:34 +0000
Received: from d06av23.portsmouth.uk.ibm.com (d06av23.portsmouth.uk.ibm.com
 [9.149.105.59])
        by b06cxnps3075.portsmouth.uk.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id 11NEOVGT37487058
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Tue, 23 Feb 2021 14:24:31 GMT
Received: from d06av23.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 1FC54A404D;
        Tue, 23 Feb 2021 14:24:31 +0000 (GMT)
Received: from d06av23.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id B73A4A4053;
        Tue, 23 Feb 2021 14:24:30 +0000 (GMT)
Received: from ibm-vm.ibmuc.com (unknown [9.145.5.213])
        by d06av23.portsmouth.uk.ibm.com (Postfix) with ESMTP;
        Tue, 23 Feb 2021 14:24:30 +0000 (GMT)
From: Claudio Imbrenda <imbrenda@linux.ibm.com>
To: kvm@vger.kernel.org
Cc: david@redhat.com, thuth@redhat.com, frankja@linux.ibm.com,
        cohuck@redhat.com, pmorel@linux.ibm.com, borntraeger@de.ibm.com
Subject: [kvm-unit-tests PATCH v2 1/2] s390x: introduce leave_pstate to leave
 userspace
Date: Tue, 23 Feb 2021 15:24:28 +0100
Message-Id: <20210223142429.256420-2-imbrenda@linux.ibm.com>
X-Mailer: git-send-email 2.26.2
In-Reply-To: <20210223142429.256420-1-imbrenda@linux.ibm.com>
References: <20210223142429.256420-1-imbrenda@linux.ibm.com>
MIME-Version: 1.0
X-TM-AS-GCONF: 00
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.369,18.0.761
 definitions=2021-02-23_07:2021-02-23,2021-02-23 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 mlxscore=0 mlxlogscore=999
 phishscore=0 spamscore=0 impostorscore=0 malwarescore=0 bulkscore=0
 adultscore=0 suspectscore=0 priorityscore=1501 lowpriorityscore=0
 clxscore=1015 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.12.0-2009150000 definitions=main-2102230119
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

In most testcases, we enter problem state (userspace) just to test if a
privileged instruction causes a fault. In some cases, though, we need
to test if an instruction works properly in userspace. This means that
we do not expect a fault, and we need an orderly way to leave problem
state afterwards.

This patch introduces a simple system based on the SVC instruction.

Signed-off-by: Claudio Imbrenda <imbrenda@linux.ibm.com>
Acked-by: David Hildenbrand <david@redhat.com>
Reviewed-by: Cornelia Huck <cohuck@redhat.com>
Reviewed-by: Janosch Frank <frankja@linux.ibm.com>
---
 lib/s390x/asm/arch_def.h |  7 +++++++
 lib/s390x/interrupt.c    | 12 ++++++++++--
 2 files changed, 17 insertions(+), 2 deletions(-)

```
#### [PATCH v14 01/13] iommu: Introduce attach/detach_pasid_table API
##### From: Eric Auger <eric.auger@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Eric Auger <eric.auger@redhat.com>
X-Patchwork-Id: 12100893
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-15.8 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_CR_TRAILER,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,
	URIBL_BLOCKED autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id EAF14C433DB
	for <kvm@archiver.kernel.org>; Tue, 23 Feb 2021 20:58:34 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id A1F2264E7A
	for <kvm@archiver.kernel.org>; Tue, 23 Feb 2021 20:58:34 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S234002AbhBWU6a (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 23 Feb 2021 15:58:30 -0500
Received: from us-smtp-delivery-124.mimecast.com ([216.205.24.124]:54601 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S232161AbhBWU62 (ORCPT
        <rfc822;kvm@vger.kernel.org>); Tue, 23 Feb 2021 15:58:28 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1614113821;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding:
         in-reply-to:in-reply-to:references:references;
        bh=D+ZdO5GWOhsIz+y4lC/TipJ7Ly/JYy1VIwVzuFHqKAw=;
        b=PlfCBBcZKvD1hTWG7mE0u5zKyfXyspAJ9FGuWiB5KnZIcoGje6NtKg5+bZU+JP++GJqf1/
        2P3Ed2BzDgFlxut/Q70+Qt3YfjoG3MN5pk9bfm3WbIBET34RFMPC7fyftzEa1ObpI8RPa0
        g/IIUMuJJPyvVM0gj9XUyzXOnAAa83g=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-463-DYgyjrFtOYmZLsEzhuEIkw-1; Tue, 23 Feb 2021 15:56:57 -0500
X-MC-Unique: DYgyjrFtOYmZLsEzhuEIkw-1
Received: from smtp.corp.redhat.com (int-mx04.intmail.prod.int.phx2.redhat.com
 [10.5.11.14])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id D81CA801989;
        Tue, 23 Feb 2021 20:56:53 +0000 (UTC)
Received: from laptop.redhat.com (ovpn-114-34.ams2.redhat.com [10.36.114.34])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 889FA5D9D0;
        Tue, 23 Feb 2021 20:56:48 +0000 (UTC)
From: Eric Auger <eric.auger@redhat.com>
To: eric.auger.pro@gmail.com, eric.auger@redhat.com,
        iommu@lists.linux-foundation.org, linux-kernel@vger.kernel.org,
        kvm@vger.kernel.org, kvmarm@lists.cs.columbia.edu, will@kernel.org,
        maz@kernel.org, robin.murphy@arm.com, joro@8bytes.org,
        alex.williamson@redhat.com, tn@semihalf.com, zhukeqian1@huawei.com
Cc: jacob.jun.pan@linux.intel.com, yi.l.liu@intel.com,
        wangxingang5@huawei.com, jiangkunkun@huawei.com,
        jean-philippe@linaro.org, zhangfei.gao@linaro.org,
        zhangfei.gao@gmail.com, vivek.gautam@arm.com,
        shameerali.kolothum.thodi@huawei.com, yuzenghui@huawei.com,
        nicoleotsuka@gmail.com, lushenming@huawei.com, vsethi@nvidia.com
Subject: [PATCH v14 01/13] iommu: Introduce attach/detach_pasid_table API
Date: Tue, 23 Feb 2021 21:56:22 +0100
Message-Id: <20210223205634.604221-2-eric.auger@redhat.com>
In-Reply-To: <20210223205634.604221-1-eric.auger@redhat.com>
References: <20210223205634.604221-1-eric.auger@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.14
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

In virtualization use case, when a guest is assigned
a PCI host device, protected by a virtual IOMMU on the guest,
the physical IOMMU must be programmed to be consistent with
the guest mappings. If the physical IOMMU supports two
translation stages it makes sense to program guest mappings
onto the first stage/level (ARM/Intel terminology) while the host
owns the stage/level 2.

In that case, it is mandated to trap on guest configuration
settings and pass those to the physical iommu driver.

This patch adds a new API to the iommu subsystem that allows
to set/unset the pasid table information.

A generic iommu_pasid_table_config struct is introduced in
a new iommu.h uapi header. This is going to be used by the VFIO
user API.

Signed-off-by: Jean-Philippe Brucker <jean-philippe.brucker@arm.com>
Signed-off-by: Liu, Yi L <yi.l.liu@linux.intel.com>
Signed-off-by: Ashok Raj <ashok.raj@intel.com>
Signed-off-by: Jacob Pan <jacob.jun.pan@linux.intel.com>
Signed-off-by: Eric Auger <eric.auger@redhat.com>
---

v13 -> v14:
- export iommu_attach_pasid_table
- add dummy iommu_uapi_attach_pasid_table
- swap base_ptr and format in iommu_pasid_table_config

v12 -> v13:
- Fix config check

v11 -> v12:
- add argsz, name the union
---
 drivers/iommu/iommu.c      | 69 ++++++++++++++++++++++++++++++++++++++
 include/linux/iommu.h      | 27 +++++++++++++++
 include/uapi/linux/iommu.h | 54 +++++++++++++++++++++++++++++
 3 files changed, 150 insertions(+)

```
#### [PATCH v12 01/13] vfio: VFIO_IOMMU_SET_PASID_TABLE
##### From: Eric Auger <eric.auger@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Eric Auger <eric.auger@redhat.com>
X-Patchwork-Id: 12100925
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-15.8 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_CR_TRAILER,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,
	URIBL_BLOCKED autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id EA4A0C433E0
	for <kvm@archiver.kernel.org>; Tue, 23 Feb 2021 21:08:19 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id ACD6E64EC3
	for <kvm@archiver.kernel.org>; Tue, 23 Feb 2021 21:08:19 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S233117AbhBWVIQ (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 23 Feb 2021 16:08:16 -0500
Received: from us-smtp-delivery-124.mimecast.com ([63.128.21.124]:38311 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S229460AbhBWVIN (ORCPT
        <rfc822;kvm@vger.kernel.org>); Tue, 23 Feb 2021 16:08:13 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1614114406;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding:
         in-reply-to:in-reply-to:references:references;
        bh=CnOB9upSv3gmXiLbJB7XG4Tyob3YoikXOx0RnJ+CFUM=;
        b=V+Jl/rTrqxFYkOoYpKSiOINeFFZBH3gO5rXFr6a5MOaZrBe/vP0q4NeovXa2OXPbQn8mU+
        yvEhItGBHkc1tPD2rWcRKy75wwopN8KxRhzOJZ6Y8trVKAHT0DYiLwpTezYEC17NurANYN
        1Q/k0T/BWzJhpSDWgDzTwZVN8EfkD34=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-172-q7OeracxNimw3F203Asihg-1; Tue, 23 Feb 2021 16:06:42 -0500
X-MC-Unique: q7OeracxNimw3F203Asihg-1
Received: from smtp.corp.redhat.com (int-mx04.intmail.prod.int.phx2.redhat.com
 [10.5.11.14])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 788208030CC;
        Tue, 23 Feb 2021 21:06:39 +0000 (UTC)
Received: from laptop.redhat.com (ovpn-114-34.ams2.redhat.com [10.36.114.34])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 0F23E5D9D0;
        Tue, 23 Feb 2021 21:06:33 +0000 (UTC)
From: Eric Auger <eric.auger@redhat.com>
To: eric.auger.pro@gmail.com, eric.auger@redhat.com,
        iommu@lists.linux-foundation.org, linux-kernel@vger.kernel.org,
        kvm@vger.kernel.org, kvmarm@lists.cs.columbia.edu, will@kernel.org,
        maz@kernel.org, robin.murphy@arm.com, joro@8bytes.org,
        alex.williamson@redhat.com, tn@semihalf.com, zhukeqian1@huawei.com
Cc: jacob.jun.pan@linux.intel.com, yi.l.liu@intel.com,
        wangxingang5@huawei.com, jiangkunkun@huawei.com,
        jean-philippe@linaro.org, zhangfei.gao@linaro.org,
        zhangfei.gao@gmail.com, vivek.gautam@arm.com,
        shameerali.kolothum.thodi@huawei.com, yuzenghui@huawei.com,
        nicoleotsuka@gmail.com, lushenming@huawei.com, vsethi@nvidia.com
Subject: [PATCH v12 01/13] vfio: VFIO_IOMMU_SET_PASID_TABLE
Date: Tue, 23 Feb 2021 22:06:13 +0100
Message-Id: <20210223210625.604517-2-eric.auger@redhat.com>
In-Reply-To: <20210223210625.604517-1-eric.auger@redhat.com>
References: <20210223210625.604517-1-eric.auger@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.14
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: "Liu, Yi L" <yi.l.liu@linux.intel.com>

This patch adds an VFIO_IOMMU_SET_PASID_TABLE ioctl
which aims to pass the virtual iommu guest configuration
to the host. This latter takes the form of the so-called
PASID table.

Signed-off-by: Jacob Pan <jacob.jun.pan@linux.intel.com>
Signed-off-by: Liu, Yi L <yi.l.liu@linux.intel.com>
Signed-off-by: Eric Auger <eric.auger@redhat.com>
---
v11 -> v12:
- use iommu_uapi_set_pasid_table
- Rework the flags checks [Zenghui, Alex]
- use VFIO_BASE + 19 [Alex]
- rework the unwind in vfio_attach_pasid_table() [Alex]

v8 -> v9:
- Merge VFIO_IOMMU_ATTACH/DETACH_PASID_TABLE into a single
  VFIO_IOMMU_SET_PASID_TABLE ioctl.

v6 -> v7:
- add a comment related to VFIO_IOMMU_DETACH_PASID_TABLE

v3 -> v4:
- restore ATTACH/DETACH
- add unwind on failure

v2 -> v3:
- s/BIND_PASID_TABLE/SET_PASID_TABLE

v1 -> v2:
- s/BIND_GUEST_STAGE/BIND_PASID_TABLE
- remove the struct device arg
---
 drivers/vfio/vfio_iommu_type1.c | 58 +++++++++++++++++++++++++++++++++
 include/uapi/linux/vfio.h       | 19 +++++++++++
 2 files changed, 77 insertions(+)

```
#### [PATCH 1/3] vfio: IOMMU_API should be selected
##### From: Jason Gunthorpe <jgg@nvidia.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Jason Gunthorpe <jgg@nvidia.com>
X-Patchwork-Id: 12100801
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-15.7 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_CR_TRAILER,INCLUDES_PATCH,MAILING_LIST_MULTI,MSGID_FROM_MTA_HEADER,
	SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED autolearn=ham autolearn_force=no
	version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 5CC15C433E6
	for <kvm@archiver.kernel.org>; Tue, 23 Feb 2021 19:19:19 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 30CF064E09
	for <kvm@archiver.kernel.org>; Tue, 23 Feb 2021 19:19:19 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S233815AbhBWTSy (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 23 Feb 2021 14:18:54 -0500
Received: from hqnvemgate25.nvidia.com ([216.228.121.64]:14173 "EHLO
        hqnvemgate25.nvidia.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S233749AbhBWTSb (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 23 Feb 2021 14:18:31 -0500
Received: from hqmail.nvidia.com (Not Verified[216.228.121.13]) by
 hqnvemgate25.nvidia.com (using TLS: TLSv1.2, AES256-SHA)
        id <B603554df0000>; Tue, 23 Feb 2021 11:17:51 -0800
Received: from HQMAIL111.nvidia.com (172.20.187.18) by HQMAIL109.nvidia.com
 (172.20.187.15) with Microsoft SMTP Server (TLS) id 15.0.1497.2; Tue, 23 Feb
 2021 19:17:50 +0000
Received: from NAM10-DM6-obe.outbound.protection.outlook.com (104.47.58.105)
 by HQMAIL111.nvidia.com (172.20.187.18) with Microsoft SMTP Server (TLS) id
 15.0.1497.2 via Frontend Transport; Tue, 23 Feb 2021 19:17:50 +0000
ARC-Seal: i=1; a=rsa-sha256; s=arcselector9901; d=microsoft.com; cv=none;
 b=J758P+aYypEuvqZRIRM+dCOjZY5WdpAQ8XR2dJXdeTW1/I8jgU2wvjlRs+dcSv3BcE8qTUs7yWRO5SP1JE8s/h80rDWiysWe3VqVzEHMm0ig5XmM8r67pxjqUhJUi+ILpjaa54SYbDjuGdJgOeaijmxh8uN/fkK8/Drb80OsefnzepKvUH2zPjslchdbSWDP2nIC7w4xlkVim5qJlB4e1SEunZv0Ox3tx7081QLEmZr3yu5AmzaJn9ph85Lf/NgzRTBuOnBEq3/kKxAZPx9O4Dxv814jjQjcSqWS9ssqj87H/fHHk25wyyMq4vOH3YahwA10JpWh3hspmwG/9G49LQ==
ARC-Message-Signature: i=1; a=rsa-sha256; c=relaxed/relaxed; d=microsoft.com;
 s=arcselector9901;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=bQGfBhjILLOGDCYuCalfpYePJzUuN63E7RFskuTpOHY=;
 b=DSfimtwmSlE7h7lwdlg283VwZg6wuKj3/rKfOO2/JKQXNzcUToe5ZVKySIMHLeOKOOb8xdUo39iQOgagz74trmzrGwItg7WbOQowjl9erXhSAjtEFwT7p9MDhjW3vxo721Ai+pvUGh9o3ZjwP/+TglOQ6BSVR/aNejr/Gi6k8NWy245dNOaTcRy+wZ3bbPLXOpXP23JlFgkUN9bRhYHNVKEuGYbGivQ9BxJCN6lL3sYVGPEEYhfppFk7AZTWFqed3MnYl/CzOFF/uGSW/g2zPPoXyCflQ1Y3xGeKnvKgR0I37Q/Z8kW8ccekL6lLCBJ7Kv0Y5AekVq8mlEXi3lh86Q==
ARC-Authentication-Results: i=1; mx.microsoft.com 1; spf=pass
 smtp.mailfrom=nvidia.com; dmarc=pass action=none header.from=nvidia.com;
 dkim=pass header.d=nvidia.com; arc=none
Received: from DM6PR12MB3834.namprd12.prod.outlook.com (2603:10b6:5:14a::12)
 by DM6PR12MB4943.namprd12.prod.outlook.com (2603:10b6:5:1bc::21) with
 Microsoft SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.3868.32; Tue, 23 Feb
 2021 19:17:50 +0000
Received: from DM6PR12MB3834.namprd12.prod.outlook.com
 ([fe80::1c62:7fa3:617b:ab87]) by DM6PR12MB3834.namprd12.prod.outlook.com
 ([fe80::1c62:7fa3:617b:ab87%6]) with mapi id 15.20.3868.033; Tue, 23 Feb 2021
 19:17:49 +0000
From: Jason Gunthorpe <jgg@nvidia.com>
To: Cornelia Huck <cohuck@redhat.com>, <kvm@vger.kernel.org>
CC: Alex Williamson <alex.williamson@redhat.com>
Subject: [PATCH 1/3] vfio: IOMMU_API should be selected
Date: Tue, 23 Feb 2021 15:17:46 -0400
Message-ID: <1-v1-df057e0f92c3+91-vfio_arm_compile_test_jgg@nvidia.com>
In-Reply-To: <0-v1-df057e0f92c3+91-vfio_arm_compile_test_jgg@nvidia.com>
References: 
X-ClientProxiedBy: BL1PR13CA0034.namprd13.prod.outlook.com
 (2603:10b6:208:257::9) To DM6PR12MB3834.namprd12.prod.outlook.com
 (2603:10b6:5:14a::12)
MIME-Version: 1.0
X-MS-Exchange-MessageSentRepresentingType: 1
Received: from mlx.ziepe.ca (142.162.115.133) by
 BL1PR13CA0034.namprd13.prod.outlook.com (2603:10b6:208:257::9) with Microsoft
 SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.3890.8 via Frontend
 Transport; Tue, 23 Feb 2021 19:17:49 +0000
Received: from jgg by mlx with local (Exim 4.94)        (envelope-from
 <jgg@nvidia.com>)        id 1lEdBs-00FUTW-IX; Tue, 23 Feb 2021 15:17:48 -0400
X-Header: ProcessedBy-CMR-outbound
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=nvidia.com; s=n1;
        t=1614107871; bh=GM3lTqgSstKYkJKHJWcsUwmhCyLfTCLb50+37wERqgA=;
        h=ARC-Seal:ARC-Message-Signature:ARC-Authentication-Results:From:To:
         CC:Subject:Date:Message-ID:In-Reply-To:References:
         Content-Transfer-Encoding:Content-Type:X-ClientProxiedBy:
         MIME-Version:X-MS-Exchange-MessageSentRepresentingType:X-Header;
        b=NMnsYp+KcYrPrIRsV75imT7L0q0XwSvmPdQG3I7e9aL6SZLJ4Z1lnYfhV3Chw7qe+
         6s5VcrrhJOULWqw9Xm0NqPw479awtzoDzFrjNCeFdyIzrhrtVpBiUXRE5jRQsa7USF
         QiCMeYaCn5tdJf0nBES9J/yWLkNdwns6C6fylA3ZqtsSOiXNXhPtZJdijnMvlRJn/k
         YSay6pVlYX1UgTK7BYpvFgb/G0+9Tc13OclLwFwYBKgjG4r9vTGCULRy6ffOw4R/qM
         cXEU9WFo26E90RcxI9fmeivtQwYlBtEpVDlJmo4yw5s0P40sVabSknCesUqFC8In0y
         +OfbFaWMg15qA==
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

As IOMMU_API is a kconfig without a description (eg does not show in the
menu) the correct operator is select not 'depends on'. Using 'depends on'
for this kind of symbol means VFIO is not selectable unless some other
random kconfig has already enabled IOMMU_API for it.

Fixes: cba3345cc494 ("vfio: VFIO core")
Signed-off-by: Jason Gunthorpe <jgg@nvidia.com>
---
 drivers/vfio/Kconfig | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
#### [PATCH] x86/kvm: Fix broken irq restoration in kvm_wait
##### From: Wanpeng Li <kernellwp@gmail.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Wanpeng Li <kernellwp@gmail.com>
X-Patchwork-Id: 12099899
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-15.7 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,DKIM_VALID_AU,FREEMAIL_FORGED_FROMDOMAIN,FREEMAIL_FROM,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED,USER_AGENT_GIT
	autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 9F9C5C433DB
	for <kvm@archiver.kernel.org>; Tue, 23 Feb 2021 05:26:19 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 47AC364E3F
	for <kvm@archiver.kernel.org>; Tue, 23 Feb 2021 05:26:19 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S230079AbhBWF0C (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 23 Feb 2021 00:26:02 -0500
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:53826 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S229996AbhBWF0B (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 23 Feb 2021 00:26:01 -0500
Received: from mail-pj1-x102b.google.com (mail-pj1-x102b.google.com
 [IPv6:2607:f8b0:4864:20::102b])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id CE27FC061574;
        Mon, 22 Feb 2021 21:25:18 -0800 (PST)
Received: by mail-pj1-x102b.google.com with SMTP id t9so1047674pjl.5;
        Mon, 22 Feb 2021 21:25:18 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=from:to:cc:subject:date:message-id;
        bh=1Zd+6SGGzX9w5QvmKHBdsCtUaSK+dUjwE9j2QN/NjCI=;
        b=cDatUG1v1bsJMlsYVvsneG0Y6dVnQ7ceTxY8n9FT0acxQw9tbUFzBGKGENvgeBD8Ou
         ED7AwYOiZBbwF2oo4F6UaYNp/z6hd6tq1ryCox+E8EiOWWNB+KiR7fVT10Rmt8oBm86W
         rWT2JNB/lYCZSwQ9XWP8fSkmtQ4NjbqdawtMfCjm8/yxdINA95ImMDXrw/zZGNsZt7rA
         wEUDWHnkeJpYZ8Y0/tpbaZEm1f1wpCNnP0iXsX5U07H0K7FbqcySLTckeLl6ZnhNhxcp
         cCWczxFyF6NVt4XoF96cS7AJvFGFOYaaAOqWzNMEEqTvPgATiZ3kGFDC+1WFMtHqd18v
         vLDg==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id;
        bh=1Zd+6SGGzX9w5QvmKHBdsCtUaSK+dUjwE9j2QN/NjCI=;
        b=FRQOwboz8gD14TzdU1tleeeUUrpx30QSFte12kHvkkwz49NCgBgcQbkJXPngxxpfow
         Uq18RMGQ5jQ1QFpFl9BTpMGyrbcpIYIa8ZC5ypVwgqUGuWPVzlboAnKh1NXYpqJfESyp
         Iz4Xr0AUsaUZPVbnpxwHaEJg+rZF8ujjvNbks8zvQ2CcPbed7d/HzKvmX+hPf385GK/m
         cJP1/t9GCb5jJl8imZ53dmxJRcoD/Pmr6RrEdVWFxvMIT43h7u+pG/csiOTDCaEZ2DLd
         UPHSfY/4FT/dXzNfLdj/5dNAko7TVOxNhMFmk5oTy83iQXDVhHxRXRKmdY14w8+dffxy
         OfkA==
X-Gm-Message-State: AOAM5300yU3OT4fNFJDa62W6DeGlIHQXWoTHfawBerrSGRq+9fX1vRVl
        si3/+pUoGL1/0SNY987K9D4dHuWlIIA=
X-Google-Smtp-Source: 
 ABdhPJzp8HozZoDI1nlPJ7qr8dmKPjvlG5VZkSHHCSvKQj3GjJwkahCE8bk9/y4VTjngGfvAPwv75A==
X-Received: by 2002:a17:902:d901:b029:e3:8f73:e759 with SMTP id
 c1-20020a170902d901b02900e38f73e759mr26292655plz.63.1614057917985;
        Mon, 22 Feb 2021 21:25:17 -0800 (PST)
Received: from localhost.localdomain ([103.7.29.6])
        by smtp.googlemail.com with ESMTPSA id
 k69sm20869672pfd.4.2021.02.22.21.25.15
        (version=TLS1_2 cipher=ECDHE-ECDSA-AES128-GCM-SHA256 bits=128/128);
        Mon, 22 Feb 2021 21:25:17 -0800 (PST)
From: Wanpeng Li <kernellwp@gmail.com>
X-Google-Original-From: Wanpeng Li <wanpengli@tencent.com>
To: linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Cc: Paolo Bonzini <pbonzini@redhat.com>,
        Sean Christopherson <seanjc@google.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>,
        Mark Rutland <mark.rutland@arm.com>,
        Thomas Gleixner <tglx@linutronix.de>
Subject: [PATCH] x86/kvm: Fix broken irq restoration in kvm_wait
Date: Tue, 23 Feb 2021 13:25:02 +0800
Message-Id: <1614057902-23774-1-git-send-email-wanpengli@tencent.com>
X-Mailer: git-send-email 2.7.4
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Wanpeng Li <wanpengli@tencent.com>

After commit 997acaf6b4b59c (lockdep: report broken irq restoration), the guest 
splatting below during boot:

 raw_local_irq_restore() called with IRQs enabled
 WARNING: CPU: 1 PID: 169 at kernel/locking/irqflag-debug.c:10 warn_bogus_irq_restore+0x26/0x30
 Modules linked in: hid_generic usbhid hid
 CPU: 1 PID: 169 Comm: systemd-udevd Not tainted 5.11.0+ #25
 RIP: 0010:warn_bogus_irq_restore+0x26/0x30
 Call Trace:
  kvm_wait+0x76/0x90
  __pv_queued_spin_lock_slowpath+0x285/0x2e0
  do_raw_spin_lock+0xc9/0xd0
  _raw_spin_lock+0x59/0x70
  lockref_get_not_dead+0xf/0x50
  __legitimize_path+0x31/0x60
  legitimize_root+0x37/0x50
  try_to_unlazy_next+0x7f/0x1d0
  lookup_fast+0xb0/0x170
  path_openat+0x165/0x9b0
  do_filp_open+0x99/0x110
  do_sys_openat2+0x1f1/0x2e0
  do_sys_open+0x5c/0x80
  __x64_sys_open+0x21/0x30
  do_syscall_64+0x32/0x50
  entry_SYSCALL_64_after_hwframe+0x44/0xae

The irqflags handling in kvm_wait() which ends up doing:

	local_irq_save(flags);
	safe_halt();
	local_irq_restore(flags);

which triggered a new consistency checking, we generally expect 
local_irq_save() and local_irq_restore() to be pared and sanely 
nested, and so local_irq_restore() expects to be called with 
irqs disabled. 

This patch fixes it by adding a local_irq_disable() after safe_halt() 
to avoid this warning.

Cc: Mark Rutland <mark.rutland@arm.com>
Cc: Thomas Gleixner <tglx@linutronix.de>
Signed-off-by: Wanpeng Li <wanpengli@tencent.com>
---
 arch/x86/kernel/kvm.c | 4 +++-
 1 file changed, 3 insertions(+), 1 deletion(-)

```
