#### [GIT PULL 1/1] KVM: s390: fix guarded storage control register handling
##### From: Christian Borntraeger <borntraeger@de.ibm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Christian Borntraeger <borntraeger@de.ibm.com>
X-Patchwork-Id: 12209593
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.8 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT
	autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 5366DC433ED
	for <kvm@archiver.kernel.org>; Sat, 17 Apr 2021 07:28:15 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 3887B610FA
	for <kvm@archiver.kernel.org>; Sat, 17 Apr 2021 07:28:15 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S231397AbhDQH2k (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Sat, 17 Apr 2021 03:28:40 -0400
Received: from mx0b-001b2d01.pphosted.com ([148.163.158.5]:51916 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S231307AbhDQH2j (ORCPT
        <rfc822;kvm@vger.kernel.org>); Sat, 17 Apr 2021 03:28:39 -0400
Received: from pps.filterd (m0098413.ppops.net [127.0.0.1])
        by mx0b-001b2d01.pphosted.com (8.16.0.43/8.16.0.43) with SMTP id
 13H74J35051471;
        Sat, 17 Apr 2021 03:28:12 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=ibm.com;
 h=from : to : cc : subject
 : date : message-id : in-reply-to : references : content-transfer-encoding
 : mime-version; s=pp1; bh=h54VN17EHOvfXnD94JUkdReWXzy9t9r1CNOmd7GYj6A=;
 b=poIab2Ph1X8ThAClVx2zcvNIcz51vHHTqLwYZMhCx+b2VH63XGqDLfBWKx+CNLfmMTMW
 8k5HcyjXKxMYB11SO7vEiQFNbjODSs7EA0ibNNjZUvjV/R/X/mDLskMerVwLf5jh7uIQ
 cF9nYNa9VkdV9ceXfgtVqjQxfP7xd1TikC9PIEk9Nq91FN3ADMHb5MnLVnwktrbyNvD2
 fzRVHcbkhfCSTyusXWAfuEE0Wp6bhGV5LTvmLNhVImyVTaa4u5E5T7bM2uiGFJbM7UUt
 Krbhj+QKwn5emJwClLcBNMoOn+gDH1BdFBRpellLbvt9biEMgbqQGkF4EeR2rtNmwNxi iQ==
Received: from pps.reinject (localhost [127.0.0.1])
        by mx0b-001b2d01.pphosted.com with ESMTP id 37ystp1gmc-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Sat, 17 Apr 2021 03:28:12 -0400
Received: from m0098413.ppops.net (m0098413.ppops.net [127.0.0.1])
        by pps.reinject (8.16.0.43/8.16.0.43) with SMTP id 13H7SCqe122993;
        Sat, 17 Apr 2021 03:28:12 -0400
Received: from ppma05fra.de.ibm.com (6c.4a.5195.ip4.static.sl-reverse.com
 [149.81.74.108])
        by mx0b-001b2d01.pphosted.com with ESMTP id 37ystp1gky-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Sat, 17 Apr 2021 03:28:12 -0400
Received: from pps.filterd (ppma05fra.de.ibm.com [127.0.0.1])
        by ppma05fra.de.ibm.com (8.16.0.43/8.16.0.43) with SMTP id
 13H7N76r003677;
        Sat, 17 Apr 2021 07:28:10 GMT
Received: from b06avi18626390.portsmouth.uk.ibm.com
 (b06avi18626390.portsmouth.uk.ibm.com [9.149.26.192])
        by ppma05fra.de.ibm.com with ESMTP id 37yqa881kc-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Sat, 17 Apr 2021 07:28:10 +0000
Received: from b06wcsmtp001.portsmouth.uk.ibm.com
 (b06wcsmtp001.portsmouth.uk.ibm.com [9.149.105.160])
        by b06avi18626390.portsmouth.uk.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id 13H7Riwc31785340
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Sat, 17 Apr 2021 07:27:44 GMT
Received: from b06wcsmtp001.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 07E18A4060;
        Sat, 17 Apr 2021 07:28:07 +0000 (GMT)
Received: from b06wcsmtp001.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id E7A62A405B;
        Sat, 17 Apr 2021 07:28:06 +0000 (GMT)
Received: from tuxmaker.boeblingen.de.ibm.com (unknown [9.152.85.9])
        by b06wcsmtp001.portsmouth.uk.ibm.com (Postfix) with ESMTPS;
        Sat, 17 Apr 2021 07:28:06 +0000 (GMT)
Received: by tuxmaker.boeblingen.de.ibm.com (Postfix, from userid 25651)
        id A0A49E07C6; Sat, 17 Apr 2021 09:28:06 +0200 (CEST)
From: Christian Borntraeger <borntraeger@de.ibm.com>
To: Paolo Bonzini <pbonzini@redhat.com>
Cc: KVM <kvm@vger.kernel.org>, Janosch Frank <frankja@linux.ibm.com>,
        David Hildenbrand <david@redhat.com>,
        Cornelia Huck <cohuck@redhat.com>,
        linux-s390 <linux-s390@vger.kernel.org>,
        Christian Borntraeger <borntraeger@de.ibm.com>,
        Heiko Carstens <hca@linux.ibm.com>
Subject: [GIT PULL 1/1] KVM: s390: fix guarded storage control register
 handling
Date: Sat, 17 Apr 2021 09:28:05 +0200
Message-Id: <20210417072806.82517-2-borntraeger@de.ibm.com>
X-Mailer: git-send-email 2.30.2
In-Reply-To: <20210417072806.82517-1-borntraeger@de.ibm.com>
References: <20210417072806.82517-1-borntraeger@de.ibm.com>
X-TM-AS-GCONF: 00
X-Proofpoint-GUID: QYqFsye8pIx1dynmJbLH0seX4qMvxSk3
X-Proofpoint-ORIG-GUID: TEfuTJiXn1pLOjGJQ4d2NWPP1NID4p-k
X-Proofpoint-UnRewURL: 0 URL was un-rewritten
MIME-Version: 1.0
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.391,18.0.761
 definitions=2021-04-17_06:2021-04-16,2021-04-17 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 suspectscore=0
 priorityscore=1501 spamscore=0 malwarescore=0 clxscore=1015 adultscore=0
 lowpriorityscore=0 phishscore=0 mlxlogscore=667 impostorscore=0 mlxscore=0
 bulkscore=0 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.12.0-2104060000 definitions=main-2104170046
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Heiko Carstens <hca@linux.ibm.com>

store_regs_fmt2() has an ordering problem: first the guarded storage
facility is enabled on the local cpu, then preemption disabled, and
then the STGSC (store guarded storage controls) instruction is
executed.

If the process gets scheduled away between enabling the guarded
storage facility and before preemption is disabled, this might lead to
a special operation exception and therefore kernel crash as soon as
the process is scheduled back and the STGSC instruction is executed.

Fixes: 4e0b1ab72b8a ("KVM: s390: gs support for kvm guests")
Signed-off-by: Heiko Carstens <hca@linux.ibm.com>
Reviewed-by: Christian Borntraeger <borntraeger@de.ibm.com>
Reviewed-by: David Hildenbrand <david@redhat.com>
Reviewed-by: Janosch Frank <frankja@linux.ibm.com>
Reviewed-by: Cornelia Huck <cohuck@redhat.com>
Cc: <stable@vger.kernel.org> # 4.12
Link: https://lore.kernel.org/r/20210415080127.1061275-1-hca@linux.ibm.com
Signed-off-by: Christian Borntraeger <borntraeger@de.ibm.com>
---
 arch/s390/kvm/kvm-s390.c | 4 ++--
 1 file changed, 2 insertions(+), 2 deletions(-)

```
#### [PATCH] KVM: nSVM: Cleanup in arch/x86/kvm/svm/nested.c
##### From: Krish Sadhukhan <krish.sadhukhan@oracle.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Krish Sadhukhan <krish.sadhukhan@oracle.com>
X-Patchwork-Id: 12209513
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
	by smtp.lore.kernel.org (Postfix) with ESMTP id 6AB66C433B4
	for <kvm@archiver.kernel.org>; Sat, 17 Apr 2021 03:38:56 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 190DE6115B
	for <kvm@archiver.kernel.org>; Sat, 17 Apr 2021 03:38:56 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S235637AbhDQDjU (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Fri, 16 Apr 2021 23:39:20 -0400
Received: from userp2120.oracle.com ([156.151.31.85]:49716 "EHLO
        userp2120.oracle.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S235567AbhDQDjT (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 16 Apr 2021 23:39:19 -0400
Received: from pps.filterd (userp2120.oracle.com [127.0.0.1])
        by userp2120.oracle.com (8.16.0.42/8.16.0.42) with SMTP id
 13H3VWc8001207;
        Sat, 17 Apr 2021 03:38:50 GMT
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=oracle.com;
 h=from : to : cc :
 subject : date : message-id : in-reply-to : references :
 content-transfer-encoding : content-type : mime-version;
 s=corp-2020-01-29; bh=zWwO9PuoFih3JCbvBiYRVa7Al5PeZNWYhw0+o0jbAzI=;
 b=YQLCt0QvAUPFlIvGSpNoPbPTJyOUnol7L3p52I+P2Jke0bMMQrjBG2sgIchBDC4Qz8oc
 rMw3w3qo5l0PtucHKC3trb33qTTX5MllNwty4M7glPFLG7XK2Rv7N4dgJh1Olj2qH5WP
 r/NrqkNjagald/4xQYMy1YUii2uOiykdTBHc7zXd8ZVXNnyds4cbtiEt65z9DMITFY/o
 0JooIKzZ+iDtipx4jIhobq4AvRfwamIjKegfGJDgK42kOvYjw7wtrydGpGV7bKV+IRSH
 66yxHdW1pT2ISQyqWxKlAmHEuXWNFqgAp8aSOZqGwyzxjLRv0W0L5ND+zp8unQCF/nFE PA==
Received: from userp3020.oracle.com (userp3020.oracle.com [156.151.31.79])
        by userp2120.oracle.com with ESMTP id 37u4nntn11-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Sat, 17 Apr 2021 03:38:49 +0000
Received: from pps.filterd (userp3020.oracle.com [127.0.0.1])
        by userp3020.oracle.com (8.16.0.42/8.16.0.42) with SMTP id
 13H3PgKW190340;
        Sat, 17 Apr 2021 03:38:49 GMT
Received: from nam11-bn8-obe.outbound.protection.outlook.com
 (mail-bn8nam11lp2171.outbound.protection.outlook.com [104.47.58.171])
        by userp3020.oracle.com with ESMTP id 37yq0jsak2-2
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Sat, 17 Apr 2021 03:38:49 +0000
ARC-Seal: i=1; a=rsa-sha256; s=arcselector9901; d=microsoft.com; cv=none;
 b=Po7lIUS6W1Y3s+oTPF6ZcyPCxDLjQkxf6nNkBXlyngTS1EeiySIWfoEzo+SpME7r6Az8cYO1IcxG6zzek32CK2aJLaLgWBqpJ0pfVLf6TKqMFxfJTHO7MVxYoo4ihgctIcMkanHXYJJeO1kiYuxF85grDj/DDrNyi6P9zuqUx0sEJIC6+q8ssz02Tf6feSWfwN6MeFoWSx7RZ83coTd0XwaV0o2A1U/Miq1XOya/sbGkPgD4Cm+Kh4zlsm0/B5uqr/IV64QeJFfqBLIbJJsxe8OZEfJrWuzFFbmje7YveHtDb4owvjx3WBoH0WBCWCqhmR47JGHlJYA5A9y1L5nxmA==
ARC-Message-Signature: i=1; a=rsa-sha256; c=relaxed/relaxed; d=microsoft.com;
 s=arcselector9901;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=zWwO9PuoFih3JCbvBiYRVa7Al5PeZNWYhw0+o0jbAzI=;
 b=HDjmc4k8/J2/91ESf1vqB88NG3fW7TTD7Vneox27v+TjlgwV3xSilzk3uOBLibp+apdHFwtqJ9MKCnmJPoZRl+azZ5jrW1d9WQ05jmfplhloHTbWOcWuBK1corz1uOeGV6gTiZrU2lH4lYOgtD0j9WBOml62UZuWt7oRQDInb2/6kbUWRwDSAPQWbi/Es20R/GO1aeOlmqAbY9CgHjLbTwwi+3G9l0QLKQrjNUA1vjVqM4ax7yx/ko+AYQsPx+BXE/ghaSKfkCwxUMk9BsGFMZXCXgU2TYcTWohV5olS8OBE2XEfSJaRl6/gSD3lYa0ZwZrGlxMTuVoTkbzmiOB/oA==
ARC-Authentication-Results: i=1; mx.microsoft.com 1; spf=pass
 smtp.mailfrom=oracle.com; dmarc=pass action=none header.from=oracle.com;
 dkim=pass header.d=oracle.com; arc=none
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
 d=oracle.onmicrosoft.com; s=selector2-oracle-onmicrosoft-com;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=zWwO9PuoFih3JCbvBiYRVa7Al5PeZNWYhw0+o0jbAzI=;
 b=nq4+YdTQ5Kz5JuITuRdeI8hn41bJvy1uxxQZaJcQyAk/Fc5yOKQ1lMjy2+BvdNXy1naQyHvfMLllvhOE+Aw0Gq/wCTAEWGbN819JekG33yQqSs0DzDNRj9PSzUA0B1Nz3BFQfb6s9c/NYbQkE8wvw+2eGW8ebhkc7jwbbqdsnhY=
Authentication-Results: vger.kernel.org; dkim=none (message not signed)
 header.d=none;vger.kernel.org; dmarc=none action=none header.from=oracle.com;
Received: from SN6PR10MB3021.namprd10.prod.outlook.com (2603:10b6:805:cc::19)
 by SA2PR10MB4665.namprd10.prod.outlook.com (2603:10b6:806:fb::17) with
 Microsoft SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.4042.19; Sat, 17 Apr
 2021 03:38:47 +0000
Received: from SN6PR10MB3021.namprd10.prod.outlook.com
 ([fe80::5911:9489:e05c:2d44]) by SN6PR10MB3021.namprd10.prod.outlook.com
 ([fe80::5911:9489:e05c:2d44%5]) with mapi id 15.20.4042.018; Sat, 17 Apr 2021
 03:38:47 +0000
From: Krish Sadhukhan <krish.sadhukhan@oracle.com>
To: kvm@vger.kernel.org
Cc: pbonzini@redhat.com, jmattson@google.com, seanjc@google.com
Subject: [PATCH] KVM: nSVM: Cleanup in arch/x86/kvm/svm/nested.c
Date: Fri, 16 Apr 2021 22:49:55 -0400
Message-Id: <20210417024955.16465-2-krish.sadhukhan@oracle.com>
X-Mailer: git-send-email 2.25.4
In-Reply-To: <20210417024955.16465-1-krish.sadhukhan@oracle.com>
References: <20210417024955.16465-1-krish.sadhukhan@oracle.com>
X-Originating-IP: [138.3.201.29]
X-ClientProxiedBy: BYAPR05CA0044.namprd05.prod.outlook.com
 (2603:10b6:a03:74::21) To SN6PR10MB3021.namprd10.prod.outlook.com
 (2603:10b6:805:cc::19)
MIME-Version: 1.0
X-MS-Exchange-MessageSentRepresentingType: 1
Received: from ban25x6uut29.us.oracle.com (138.3.201.29) by
 BYAPR05CA0044.namprd05.prod.outlook.com (2603:10b6:a03:74::21) with Microsoft
 SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.4065.6 via Frontend
 Transport; Sat, 17 Apr 2021 03:38:46 +0000
X-MS-PublicTrafficType: Email
X-MS-Office365-Filtering-Correlation-Id: 8c1f9409-13ab-4692-cfb4-08d901524f02
X-MS-TrafficTypeDiagnostic: SA2PR10MB4665:
X-Microsoft-Antispam-PRVS: 
 <SA2PR10MB466531EB31DCE804B1467FFC814B9@SA2PR10MB4665.namprd10.prod.outlook.com>
X-MS-Oob-TLC-OOBClassifiers: OLM:6790;
X-MS-Exchange-SenderADCheck: 1
X-Microsoft-Antispam: BCL:0;
X-Microsoft-Antispam-Message-Info: 
 6jUzJwV4CRE64+UxeD1Nu/yoZZkQgIAfAZKWe7pWu+pi2mzXPjQU8XH91SkZVXABCyCKEhOhwtxRpVgJqx8vUpc/k1cTpP8CAWz0rmasRoZotIzmkKTn8vifHirxurTh1L6PVzMExwkCyRDW9cn5shUHv6h96ZJonTiVG5Cw0GWjKgcFX2JAqwrAkp8ArDV4Yfjy+df6Puo6IGFaJfFxpyTkaPb7yfY1jWG2LgI6RzuPUERx5j6gwht9c/Uv14zECHj/gs6QfiYftulpk61riwIvRpkJUzA59QC9ONeUqchHs3ZrefvWG6qmSyWQ26D7MbjiGdx+tWU2lBs8gYRwHIejpJsP5BDA/K8xNwYEw0Kb02hAohqzfO/Kq/Vqw7Hm2ZJ4c01DOlLfFpmAHUxtYjczraXyXp8ScAa1y8aEL4Tv9IOCnsnjkIIgtj3AoeNH6Q5RB6drgocEG8sJMkPVGBmwAUdbMt0+piwHpNKrqOkwLtnQTkVlT/355VS0IMly76tOAjelQ6J6+3LjWPDja2ZTpt+khHr34JL9PgFUSLWUgYLZXLdN9gmFjyRLvOyAQODj/LqNOZvqimHPq0XcbCz9fnsHqQKC/R58pBeS7SjDkE47rDKd7hntQUXKZR+PFRHc9yFcPWlwo+u32F9O0Q==
X-Forefront-Antispam-Report: 
 CIP:255.255.255.255;CTRY:;LANG:en;SCL:1;SRV:;IPV:NLI;SFV:NSPM;H:SN6PR10MB3021.namprd10.prod.outlook.com;PTR:;CAT:NONE;SFS:(39860400002)(376002)(396003)(366004)(346002)(136003)(30864003)(66556008)(6486002)(956004)(83380400001)(6916009)(8676002)(2906002)(2616005)(316002)(5660300002)(478600001)(66946007)(66476007)(86362001)(44832011)(8936002)(6666004)(38100700002)(4326008)(7696005)(1076003)(52116002)(26005)(38350700002)(36756003)(16526019)(186003);DIR:OUT;SFP:1101;
X-MS-Exchange-AntiSpam-MessageData: 
 HE4agCRANK8NcIMfc+6y5xGD4Kijyr5KzqvgCDOQRBBd0sMzJxdUIbrtT/8dP5N1gPb251iGiL47O007i6anYt0E/rpbHxN4mSvzM5vYh9YI7YLjza0Mqpcg/N7AHy7X9rXRNP/JRwL4XTT8gIOKE3UMLNDOQVSgKPWfQGkvBO8QxxiGS/3rArDV2APdSd/lPG3JT/8NqouKktnN6pORo/9Skgs0pijwdq3h4coF1hD81/SlBTeaEDL1YBXuwl3FPWdlePwGWrqKeqDOUhTYHo1jAr0EDd+gJbO/ALC2cBhOlQ+MESvvzA68SWV/vL3skxChBAaPL+3EFbuQTqCOERwgJ97QzYSBOafHwGk6y4vaFzFytEH9aYfLvuQHQWEhWBx+Nps3jUVNjPdM/t7pXJE/ZUa0BKj9i+xWJB+aFxuIduQAvJWsak/bNWkqGb4l+CdAkh3MMwCglI9LZm0oFsP8UaYcb5m+u9dN3obzlWZLdCNUf5JUBMzQNo7KXJoBJCmkKVyPcTQhxTfacY2RK54j43+Fr5g25NVbp5dRYfQw3rHSYLxyNS1VcXO0LaiyZNWmQaG+Ac2eoXeQu9O2DuE50HNabRoHMoR9e309G3zzGl22bWskUBckqdWUttoHD0a5wikNYhytQX4ZWguX4bVDVE8BKosiPYj6cHLFB5yDDh3hzxvB79fCZYgNzhJBOKlJfaDcmd/5rGn/R2bDhczMGxzAfx17XxFWaEFe6DL/RiBisMLhUvXkT/L4wHK5v8fZUCTz6uqAKNYRItEuZSpJ+50xXRMzdtWLC/3goqgFA92z+nYwOCHnxJmL2H3MrWM3a1E4XbYY1gNKwtVB/SNU+oeIQhDfGrcEYDLK3dKDTlYJMNQUjVeju+bYyH8DpZJz34hay96hxYziAra7xOb90XMNe+FFsrUtXjkFpifsQ8wFhzZFeXhCV4YKF3VNwO6c3cGxOt3rW57th8BCVbP5oPuGte7JryszyQDUB6mfs7hcK9lHrsqugE7Lqy+TvhuZSZRMSXzk1g8AXtwJjRmUhvikW3HvALhwuMt8+12RexxDW+5EudehtFa1uTIJFi4Ptdxb4ssidduK8bWIYsXGgw3c8pd1iEZlA/ubh1TvffUqYZCYdRK/pldRomR5iCLnCgfQys6D//J5r9aHi8JoByTIXWWwwLt9XNttbeoVot0E3z2D1cbm+hq6eHp7H+GUtnRiRCjM+9vBfSZS3TSm7treFpTuL1Spg+6DweT+kOjr4ZhsLqtPPtUVbri114Sgex24QviyemJZo109DFw1hc/+azvLkw/XB4ssahqiulodtZMIOJ+jQ6/2ynYc
X-OriginatorOrg: oracle.com
X-MS-Exchange-CrossTenant-Network-Message-Id: 
 8c1f9409-13ab-4692-cfb4-08d901524f02
X-MS-Exchange-CrossTenant-AuthSource: SN6PR10MB3021.namprd10.prod.outlook.com
X-MS-Exchange-CrossTenant-AuthAs: Internal
X-MS-Exchange-CrossTenant-OriginalArrivalTime: 17 Apr 2021 03:38:47.8143
 (UTC)
X-MS-Exchange-CrossTenant-FromEntityHeader: Hosted
X-MS-Exchange-CrossTenant-Id: 4e2c6054-71cb-48f1-bd6c-3a9705aca71b
X-MS-Exchange-CrossTenant-MailboxType: HOSTED
X-MS-Exchange-CrossTenant-UserPrincipalName: 
 JFvtQZK4R0Ez3oETWw6hcP2mvfAvIM3HZJj9RIFDsfIFHE3ehW9okTV7eE6ywFL9PSA4gyj0/XqqxaYM5XiX30ry6WfmwnpcSGwgJ2qUXSI=
X-MS-Exchange-Transport-CrossTenantHeadersStamped: SA2PR10MB4665
X-Proofpoint-Virus-Version: vendor=nai engine=6200 definitions=9956
 signatures=668683
X-Proofpoint-Spam-Details: rule=notspam policy=default score=0 adultscore=0
 malwarescore=0
 phishscore=0 mlxlogscore=999 bulkscore=0 mlxscore=0 suspectscore=0
 spamscore=0 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.12.0-2104060000 definitions=main-2104170022
X-Proofpoint-ORIG-GUID: Y9TAInCkwGAzNs3DsJ3SkEPpHjBE-Tah
X-Proofpoint-GUID: Y9TAInCkwGAzNs3DsJ3SkEPpHjBE-Tah
X-Proofpoint-Virus-Version: vendor=nai engine=6200 definitions=9956
 signatures=668683
X-Proofpoint-Spam-Details: rule=notspam policy=default score=0 adultscore=0
 malwarescore=0
 phishscore=0 suspectscore=0 mlxlogscore=999 priorityscore=1501
 clxscore=1015 lowpriorityscore=0 spamscore=0 impostorscore=0 bulkscore=0
 mlxscore=0 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.12.0-2104060000 definitions=main-2104170022
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Use local variables to derefence svm->vcpu, svm->vmcb and svm->vmcb01.ptr
to make the code tidier.

Suggested-by: Sean Christopherson <seanjc@google.com>
Signed-off-by: Krish Sadhukhan <krish.sadhukhan@oracle.com>
---
 arch/x86/kvm/svm/nested.c | 267 ++++++++++++++++++++------------------
 1 file changed, 141 insertions(+), 126 deletions(-)

```
#### [PATCH v3 1/2] KVM: selftests: Sync data verify of dirty logging with guest sync
##### From: Peter Xu <peterx@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Peter Xu <peterx@redhat.com>
X-Patchwork-Id: 12209839
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-18.8 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_CR_TRAILER,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,
	USER_AGENT_GIT autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 30A08C43460
	for <kvm@archiver.kernel.org>; Sat, 17 Apr 2021 14:36:11 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 08D13610CB
	for <kvm@archiver.kernel.org>; Sat, 17 Apr 2021 14:36:11 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S236529AbhDQOgg (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Sat, 17 Apr 2021 10:36:36 -0400
Received: from us-smtp-delivery-124.mimecast.com ([170.10.133.124]:49296 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S236519AbhDQOgf (ORCPT
        <rfc822;kvm@vger.kernel.org>); Sat, 17 Apr 2021 10:36:35 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1618670168;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding:
         in-reply-to:in-reply-to:references:references;
        bh=zMD5uGSCk8k8a6saeFDhVq8pp2UvLtXqYA1ImGN3qPM=;
        b=MFOrGFTu6nBwjA8EPq9r8+lYCf7dc0gmE8EL4D3Vb49NWxHguizb4TdLlsrqSoL8+MmWj0
        uBdxqnSqe6Xw2Uz9vpQgE+4URJHI5wvWSOfVGkYflJHKhCjCswOv0UDAViTejLwzc0jyx8
        YCTZV0vma2pm0cDsQJr0SlKiERpUC4g=
Received: from mail-qk1-f197.google.com (mail-qk1-f197.google.com
 [209.85.222.197]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-512-e0MqoX81Mu-ZNxV7Av1K0Q-1; Sat, 17 Apr 2021 10:36:06 -0400
X-MC-Unique: e0MqoX81Mu-ZNxV7Av1K0Q-1
Received: by mail-qk1-f197.google.com with SMTP id
 g196-20020a379dcd0000b02902e321640e6bso1143610qke.14
        for <kvm@vger.kernel.org>; Sat, 17 Apr 2021 07:36:06 -0700 (PDT)
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:in-reply-to
         :references:mime-version:content-transfer-encoding;
        bh=zMD5uGSCk8k8a6saeFDhVq8pp2UvLtXqYA1ImGN3qPM=;
        b=LTovEyI54vjjfY2xj1xn5rIfMTQQ/srxG60Hyk+nKJN59D8X466keelnAf4U584NmG
         uZG+5Rk3rzNFZXIaOYh8Rjzab8tcqeqMS5zVQV7eBt7W/KNbOh9bBMAp0vVM2DApim24
         PnOK1fC18Vg91VhG1jjkCDPlXAQM533wHpxYmeeo+gLxEvZcAqEVz7PvNJCkkBBhMJIJ
         Roy+0sFTjHjyeLLdyeUDPqHYe/tRkQbMI0Oi6EuoebzzetkwrNtOWX2CgO2gtkJqBAa3
         QzqnF1Jx1BA7ytAfMpuOGLQ0OwIEfuJH+n9s2PUpg1l+WeyaNecIFX84aTu0u7yg4ZAV
         0VKg==
X-Gm-Message-State: AOAM530T3HCvQ9/U8H7XrVQm8+onhOvOakxJsjgi+TDiYNLUTfsmreKe
        qcXlk9a1LJRXvZspfkgjmDOPvz6XEBW2MT/mzSfRG7YpEO+wIinygoHk5mOH3KE38gDJEgCSkos
        j2Te6VrSGv0Ox
X-Received: by 2002:a0c:f78e:: with SMTP id s14mr13259681qvn.46.1618670166261;
        Sat, 17 Apr 2021 07:36:06 -0700 (PDT)
X-Google-Smtp-Source: 
 ABdhPJxaMGRYZfWrhThCQE96g7Zw23elaCSUhp5bIAObw5ljE3E8zyV3AcmLUhmzwaC+2GB2g4TciQ==
X-Received: by 2002:a0c:f78e:: with SMTP id s14mr13259668qvn.46.1618670166029;
        Sat, 17 Apr 2021 07:36:06 -0700 (PDT)
Received: from xz-x1.redhat.com
 (bras-base-toroon474qw-grc-88-174-93-75-154.dsl.bell.ca. [174.93.75.154])
        by smtp.gmail.com with ESMTPSA id
 l12sm378159qtq.34.2021.04.17.07.36.04
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Sat, 17 Apr 2021 07:36:05 -0700 (PDT)
From: Peter Xu <peterx@redhat.com>
To: linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Cc: Andrew Jones <drjones@redhat.com>, peterx@redhat.com,
        Paolo Bonzini <pbonzini@redhat.com>,
        Sean Christopherson <seanjc@google.com>
Subject: [PATCH v3 1/2] KVM: selftests: Sync data verify of dirty logging with
 guest sync
Date: Sat, 17 Apr 2021 10:36:01 -0400
Message-Id: <20210417143602.215059-2-peterx@redhat.com>
X-Mailer: git-send-email 2.26.2
In-Reply-To: <20210417143602.215059-1-peterx@redhat.com>
References: <20210417143602.215059-1-peterx@redhat.com>
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This fixes a bug that can trigger with e.g. "taskset -c 0 ./dirty_log_test" or
when the testing host is very busy.

A similar previous attempt is done [1] but that is not enough, the reason is
stated in the reply [2].

As a summary (partly quotting from [2]):

The problem is I think one guest memory write operation (of this specific test)
contains a few micro-steps when page is during kvm dirty tracking (here I'm
only considering write-protect rather than pml but pml should be similar at
least when the log buffer is full):

  (1) Guest read 'iteration' number into register, prepare to write, page fault
  (2) Set dirty bit in either dirty bitmap or dirty ring
  (3) Return to guest, data written

When we verify the data, we assumed that all these steps are "atomic", say,
when (1) happened for this page, we assume (2) & (3) must have happened.  We
had some trick to workaround "un-atomicity" of above three steps, as previous
version of this patch wanted to fix atomicity of step (2)+(3) by explicitly
letting the main thread wait for at least one vmenter of vcpu thread, which
should work.  However what I overlooked is probably that we still have race
when (1) and (2) can be interrupted.

One example calltrace when it could happen that we read an old interation, got
interrupted before even setting the dirty bit and flushing data:

    __schedule+1742
    __cond_resched+52
    __get_user_pages+530
    get_user_pages_unlocked+197
    hva_to_pfn+206
    try_async_pf+132
    direct_page_fault+320
    kvm_mmu_page_fault+103
    vmx_handle_exit+288
    vcpu_enter_guest+2460
    kvm_arch_vcpu_ioctl_run+325
    kvm_vcpu_ioctl+526
    __x64_sys_ioctl+131
    do_syscall_64+51
    entry_SYSCALL_64_after_hwframe+68

It means iteration number cached in vcpu register can be very old when dirty
bit set and data flushed.

So far I don't see an easy way to guarantee all steps 1-3 atomicity but to sync
at the GUEST_SYNC() point of guest code when we do verification of the dirty
bits as what this patch does.

[1] https://lore.kernel.org/lkml/20210413213641.23742-1-peterx@redhat.com/
[2] https://lore.kernel.org/lkml/20210417140956.GV4440@xz-x1/

Cc: Paolo Bonzini <pbonzini@redhat.com>
Cc: Sean Christopherson <seanjc@google.com>
Cc: Andrew Jones <drjones@redhat.com>
Signed-off-by: Peter Xu <peterx@redhat.com>
---
 tools/testing/selftests/kvm/dirty_log_test.c | 60 ++++++++++++++++----
 1 file changed, 50 insertions(+), 10 deletions(-)

```
