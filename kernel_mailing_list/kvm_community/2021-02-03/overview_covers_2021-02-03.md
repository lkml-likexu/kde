

#### [PATCH 0/5 v3] KVM: nSVM: Check addresses of MSR bitmap and IO bitmap
##### From: Krish Sadhukhan <krish.sadhukhan@oracle.com>

```c
From patchwork Wed Feb  3 00:40:30 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Krish Sadhukhan <krish.sadhukhan@oracle.com>
X-Patchwork-Id: 12063175
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-13.7 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_PATCH,
	MAILING_LIST_MULTI,MSGID_FROM_MTA_HEADER,SPF_HELO_NONE,SPF_PASS,
	USER_AGENT_GIT autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 6E4BDC433E0
	for <kvm@archiver.kernel.org>; Wed,  3 Feb 2021 02:11:34 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 1447F64E3F
	for <kvm@archiver.kernel.org>; Wed,  3 Feb 2021 02:11:34 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S231273AbhBCCLR (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 2 Feb 2021 21:11:17 -0500
Received: from userp2120.oracle.com ([156.151.31.85]:54550 "EHLO
        userp2120.oracle.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S229624AbhBCCLQ (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 2 Feb 2021 21:11:16 -0500
X-Greylist: delayed 2512 seconds by postgrey-1.27 at vger.kernel.org;
 Tue, 02 Feb 2021 21:11:15 EST
Received: from pps.filterd (userp2120.oracle.com [127.0.0.1])
        by userp2120.oracle.com (8.16.0.42/8.16.0.42) with SMTP id
 1131Ov8o015765;
        Wed, 3 Feb 2021 01:28:38 GMT
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=oracle.com;
 h=from : to : cc :
 subject : date : message-id : content-transfer-encoding : content-type :
 mime-version; s=corp-2020-01-29;
 bh=ugCSFC1iVd4a2j339N6QLI0N07JAM3x2IumLR0xXfOY=;
 b=YSXAMq9FgYJgYO7emFWT5UPbwnKTnHj2gd6S96kAkk6vDcLIuVsdYPZh9cFyMyjhz14W
 SQ47bj1ic/wRwP56uMEs8Ku1KP0JtXSgB9/B8Q/k31oz762jR48liHw/+3zxxw0g21rH
 P4bcf+UrSrx+diMSAnMvPKg9GM6Q/KL7ewfwDH6M/0nPyK1pZlANjmubysRCSANEAfrh
 bNA1z8yg2YXP3Cc5J2PInk30nLYXp3op99tVFSg05Kkj2cLV6os3Gr4gxFenpRpzZdLL
 7gYayEB2WPuenh3L4a+Yxz20ynZsRJiJ6dmlDQNPnH/3pDMFfJgHACIkPVWzAlR95TVy Iw==
Received: from aserp3030.oracle.com (aserp3030.oracle.com [141.146.126.71])
        by userp2120.oracle.com with ESMTP id 36dn4wkg5n-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Wed, 03 Feb 2021 01:28:38 +0000
Received: from pps.filterd (aserp3030.oracle.com [127.0.0.1])
        by aserp3030.oracle.com (8.16.0.42/8.16.0.42) with SMTP id
 1131PVPI071745;
        Wed, 3 Feb 2021 01:28:37 GMT
Received: from nam12-dm6-obe.outbound.protection.outlook.com
 (mail-dm6nam12lp2173.outbound.protection.outlook.com [104.47.59.173])
        by aserp3030.oracle.com with ESMTP id 36dh1pxvu1-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Wed, 03 Feb 2021 01:28:37 +0000
ARC-Seal: i=1; a=rsa-sha256; s=arcselector9901; d=microsoft.com; cv=none;
 b=MfvEOdi0XukrcsYkODspwE6qh6fpE+Z2ARwa7SGHoou29bfYcid4+3R+4xo/fJ5+nHHXPCwZKBtvLWwPDbG1J7YmrZXOnBxF5TquKeigxaTz/66DY00QoPTDY4qCZqHZqrrHjxEf5dNXynTZwUOS2DBE9un4NQrB2LoreSNE8TJUXssMfFboNLoyfXpysgu5/4+tTimty4Yhd1ZCdU6X0jplNOXOXOIOccTQZ3uEz8QL60EnhB3XAKl7a2biKmZwPC6MfgIekYoz8R0TeuKShdL0o957L4QnHq3uNs2F/aYRs/yFBzznPfE5n7WCGhGlDyFAdiiTlJFppUFn9ICvMA==
ARC-Message-Signature: i=1; a=rsa-sha256; c=relaxed/relaxed; d=microsoft.com;
 s=arcselector9901;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=ugCSFC1iVd4a2j339N6QLI0N07JAM3x2IumLR0xXfOY=;
 b=m5oPyeYHbXOf7Ihg9zENfrGu7hjSCr89OLj96QamAcUYnbj1TWZRpRvr5nlpmeN0b/nnWoLop8lBgmYs4jTEqztPuqPNo+E/q+pVGNvksOgFVRVOJ8lSXBRahIXE5guHRRTdYlYbc52Rj1Xzo4VTYLJTLxLCcMtVC8RmVWjMs+MJ/gc7A3SC/cyM4PM8+uTxND04ISzqs4i6LJhmrdUkEiJmImC/ciI2yVg1njZh76sO6voH3I4AUgxLPOfawnKBDKgbiYuEKmc84YiQZ/TYbGPBMa7dNmT3nWGPEiCcAFDhpsmuIENYyl1uYXoB62Cncn+SXbqawJwCxJqX9syYWQ==
ARC-Authentication-Results: i=1; mx.microsoft.com 1; spf=pass
 smtp.mailfrom=oracle.com; dmarc=pass action=none header.from=oracle.com;
 dkim=pass header.d=oracle.com; arc=none
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
 d=oracle.onmicrosoft.com; s=selector2-oracle-onmicrosoft-com;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=ugCSFC1iVd4a2j339N6QLI0N07JAM3x2IumLR0xXfOY=;
 b=hDN3UILJ4TWcErcaGHXhkTLkjat9GP79RF9d39nS9+iwoqX5UHKSdkF5dDRkbcMdpNcme+2Tum//CSJZ2qdwekbdP5YTu3n++Ycs/zXD3uekXZWKThJEDSKeVXAIbmfdHhK4oGKsEVdYQNi4FE66hV9vGkauf7PL3R5fsU1Qh8I=
Authentication-Results: vger.kernel.org; dkim=none (message not signed)
 header.d=none;vger.kernel.org; dmarc=none action=none header.from=oracle.com;
Received: from DM6PR10MB3019.namprd10.prod.outlook.com (2603:10b6:5:6f::23) by
 DS7PR10MB4941.namprd10.prod.outlook.com (2603:10b6:5:38f::5) with Microsoft
 SMTP Server (version=TLS1_2, cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id
 15.20.3805.17; Wed, 3 Feb 2021 01:28:36 +0000
Received: from DM6PR10MB3019.namprd10.prod.outlook.com
 ([fe80::29f2:ddd5:36ac:dbba]) by DM6PR10MB3019.namprd10.prod.outlook.com
 ([fe80::29f2:ddd5:36ac:dbba%4]) with mapi id 15.20.3805.024; Wed, 3 Feb 2021
 01:28:36 +0000
From: Krish Sadhukhan <krish.sadhukhan@oracle.com>
To: kvm@vger.kernel.org
Cc: pbonzini@redhat.com, jmattson@google.com, seanjc@google.com
Subject: [PATCH 0/5 v3] KVM: nSVM: Check addresses of MSR bitmap and IO bitmap
 tables on vmrun of nested guests
Date: Tue,  2 Feb 2021 19:40:30 -0500
Message-Id: <20210203004035.101292-1-krish.sadhukhan@oracle.com>
X-Mailer: git-send-email 2.25.4
X-Originating-IP: [138.3.200.29]
X-ClientProxiedBy: SJ0PR05CA0073.namprd05.prod.outlook.com
 (2603:10b6:a03:332::18) To DM6PR10MB3019.namprd10.prod.outlook.com
 (2603:10b6:5:6f::23)
MIME-Version: 1.0
X-MS-Exchange-MessageSentRepresentingType: 1
Received: from ban25x6uut29.us.oracle.com (138.3.200.29) by
 SJ0PR05CA0073.namprd05.prod.outlook.com (2603:10b6:a03:332::18) with
 Microsoft SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.3825.15 via Frontend
 Transport; Wed, 3 Feb 2021 01:28:34 +0000
X-MS-PublicTrafficType: Email
X-MS-Office365-Filtering-Correlation-Id: bc03f38a-1ea8-424b-4476-08d8c7e30697
X-MS-TrafficTypeDiagnostic: DS7PR10MB4941:
X-Microsoft-Antispam-PRVS: 
 <DS7PR10MB4941F4234251A5C55275588B81B49@DS7PR10MB4941.namprd10.prod.outlook.com>
X-MS-Oob-TLC-OOBClassifiers: OLM:7691;
X-MS-Exchange-SenderADCheck: 1
X-Microsoft-Antispam: BCL:0;
X-Microsoft-Antispam-Message-Info: 
 e900Khiugn06Qc34vtzrtfXDBpoZxFWzx6QA06T2wPa/L7ceKoVoUdki+XWN9D6+D5pPdtrDynlbsfC0r6aC6WieduZB1xkOCwmn9Tn+CtoowywLnRgbHDrF4nHis1Kmr2xGEV/1l+2+qC04B6/oTocOwFPClim7QqCjsjonppQ5O33e1ist4jLbvtvut07k+oSV37zRGvhBnd0eb42rWktpqe99ZGvIM21zvLldeXY7693Cfw/b02OcJrvYMWdh47gEOQtHcx4UHxinWImkOIftkz4sjW9+Rdkn+fF7ewXtZsnH7FJt1bULbW5ZKYh4axIKtTJ+cMnrbW90eZH92sAuu4n0PqP6vPLmfk646TSA7wMaduAp8QrNg531jLwbDexC2IznpEPpcLSvtAvoRmefZOYZwf5xwr/cR+0uixqR4h3w06aI8hOaqhltmx3O5EwGkjov65XRNT4Z9kOatNsyhSOAGDj4juknHz5tFkoWrZWDKs+kQKhO0OP3KEmZr/IESfTqQC8+Tp4nznkZhg==
X-Forefront-Antispam-Report: 
 CIP:255.255.255.255;CTRY:;LANG:en;SCL:1;SRV:;IPV:NLI;SFV:NSPM;H:DM6PR10MB3019.namprd10.prod.outlook.com;PTR:;CAT:NONE;SFS:(136003)(366004)(376002)(346002)(39860400002)(396003)(316002)(36756003)(7696005)(6486002)(83380400001)(6666004)(2616005)(8936002)(1076003)(66946007)(2906002)(186003)(4326008)(5660300002)(86362001)(6916009)(66556008)(16526019)(44832011)(956004)(26005)(52116002)(66476007)(8676002)(478600001);DIR:OUT;SFP:1101;
X-MS-Exchange-AntiSpam-MessageData: 
 yjjw2ny4qV36YHFag04S+MwEIaeu0f4xz8RxZrdhOC/fhKudl2R0iqsyCIlGwc6xLfVExFYSFvwRnX+jdMl8Ug7fLgihtBeGnwY4w3eFRneddKt1zqEiIJ8Z1GBBAyXQ0syMs/8qwQWbJKbnpsxttUqPFaAO7cChBnJWy9jkx8EEy9N0OYgFcGgqLXJR2rMCrOevp82PSYWq6Xww00TkDfkfsopNSc6XJtZ8ZJP+Ig/D5kvzTFJ1yoBVSSKSLtFaYOdelJcIvVbvFJt7jTVuD+jR80rnEAPRlTYJXtDOR4DQuaNHRF9TbdR7oXGaqohBYCZl5dadet0TakxUtZbHF0CAU1r1DoO2bsQEDYFLeEGe57CN2W2KyxY0kthcXFPk4qXH7MA7YWVzAyHeUijulgXXdUwrVVqnNMx55FKRYx2ffu+8FevjvWE2gt9p8G2HX5SC36aAs7O85Q147IcXTFkkKwhl2+vgiI/1SFIV8epBXj3xvt+928SL4URK2vbbFgYtC0y4q5hkeCn4uJpwByfNiSbCWxJQ8M0432pSjBplAQN0Ail7R6t7I6F/dLMvwDFP8yPkGO2rqmB9ypfAtQrqLl/gpNj6ogIWGGZpqkKmoxjmguf3l8XoqVouCqmwGZHYoV9TjGB2AR7amaQ/aSDIQ6V7NAA7asgSZHTIF/XQiMtQgvj2iafrgLVHRUGGVuUyfrmQeAPa6uwu2e5o7CZ9/k/ShfzpcfFO6s89LiYK0vqHywt4CHgzqkt9dukaafzEkAV3pHAtlFv88gIWXMzLgbPdPa/2rJyaROzJcj0wAXFD73vJtoX2qXyOHQ7bFQduE3CQVGNdl6NEh7Dnw2WJ2JgX+gTHha98f5Yeg2Vp5TfKtrp7A5duUCk4ZNkdh2KHSvydFbwwUXIYM/zw9TFXHQzYjVeEDrMN9bJozKKC+hYy27n3kmR/YmXI47R/zHmKsoXAGLvahhnZpEqmTip5RZ6Sa0Qdo7aWnT4vyqVLv0rrPHVAum3UrRXwViHPb6Jrzdz5qN2iyE0uKAvxOmeBmCKbeNME/dGNe30HFMxBG53x294tfW7bSWGSFRPl
X-OriginatorOrg: oracle.com
X-MS-Exchange-CrossTenant-Network-Message-Id: 
 bc03f38a-1ea8-424b-4476-08d8c7e30697
X-MS-Exchange-CrossTenant-AuthSource: DM6PR10MB3019.namprd10.prod.outlook.com
X-MS-Exchange-CrossTenant-AuthAs: Internal
X-MS-Exchange-CrossTenant-OriginalArrivalTime: 03 Feb 2021 01:28:36.2351
 (UTC)
X-MS-Exchange-CrossTenant-FromEntityHeader: Hosted
X-MS-Exchange-CrossTenant-Id: 4e2c6054-71cb-48f1-bd6c-3a9705aca71b
X-MS-Exchange-CrossTenant-MailboxType: HOSTED
X-MS-Exchange-CrossTenant-UserPrincipalName: 
 cSDDoZVLfzVxeDnfRxozZX9whGdqBhonNbQqd1MOMk+5UlJ/IdWwQQ5rw0CmWiKgtt0RyeyHehxSXh5lgVuFy2MAoisP+cv3tZjbH8fASJA=
X-MS-Exchange-Transport-CrossTenantHeadersStamped: DS7PR10MB4941
X-Proofpoint-Virus-Version: vendor=nai engine=6200 definitions=9883
 signatures=668683
X-Proofpoint-Spam-Details: rule=notspam policy=default score=0 adultscore=0
 spamscore=0 phishscore=0
 suspectscore=0 mlxlogscore=792 bulkscore=0 mlxscore=0 malwarescore=0
 classifier=spam adjust=0 reason=mlx scancount=1 engine=8.12.0-2009150000
 definitions=main-2102030004
X-Proofpoint-Virus-Version: vendor=nai engine=6200 definitions=9883
 signatures=668683
X-Proofpoint-Spam-Details: rule=notspam policy=default score=0 impostorscore=0
 lowpriorityscore=0
 spamscore=0 priorityscore=1501 suspectscore=0 phishscore=0 mlxlogscore=972
 malwarescore=0 clxscore=1015 bulkscore=0 adultscore=0 mlxscore=0
 classifier=spam adjust=0 reason=mlx scancount=1 engine=8.12.0-2009150000
 definitions=main-2102030004
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

v2 -> v3:
	1. Moved the #defines for IOPM_ALLOC_ORDER and MSRPM_ALLOC_ORDER so
	   that they can be used by nested_vmcb_check_controls()
	2. Fixed the wrong check in nested_vmcb_check_controls() in patch# 2
	   (which was patch# 1 in v2).
	3. Added a clean-up patch for nested_svm_vmrun().


[PATCH 1/5 v3] KVM: SVM: Move IOPM_ALLOC_ORDER and MSRPM_ALLOC_ORDER
[PATCH 2/5 v3] nSVM: Check addresses of MSR and IO bitmap
[PATCH 3/5 v3] KVM: nSVM: Cleanup in nested_svm_vmrun()
[PATCH 4/5 v3] Test: nSVM: Test MSR and IO bitmap address
[PATCH 5/5 v3] Test: SVM: Use ALIGN macro when aligning 'io_bitmap_area'

 arch/x86/kvm/svm/nested.c | 63 +++++++++++++++++++++++++++--------------------
 arch/x86/kvm/svm/svm.c    |  3 ---
 arch/x86/kvm/svm/svm.h    |  3 +++
 3 files changed, 39 insertions(+), 30 deletions(-)

Krish Sadhukhan (3):
      KVM: SVM: Move IOPM_ALLOC_ORDER and MSRPM_ALLOC_ORDER #defines to svm.h
      nSVM: Check addresses of MSR and IO bitmap
      KVM: nSVM: Cleanup in nested_svm_vmrun()

 x86/svm.c       |  2 +-
 x86/svm_tests.c | 38 ++++++++++++++++++++++++++++++++++++++
 2 files changed, 39 insertions(+), 1 deletion(-)

Krish Sadhukhan (2):
      nSVM: Test MSR and IO bitmap address
      SVM: Use ALIGN macro when aligning 'io_bitmap_area'
```
#### [PATCH 0/3] nSVM: Test host RFLAGS.TF on VMRUN
##### From: Krish Sadhukhan <krish.sadhukhan@oracle.com>

```c
From patchwork Wed Feb  3 01:28:39 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Krish Sadhukhan <krish.sadhukhan@oracle.com>
X-Patchwork-Id: 12063199
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-13.7 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_PATCH,
	MAILING_LIST_MULTI,MSGID_FROM_MTA_HEADER,SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED,
	USER_AGENT_GIT autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 7C2B3C433DB
	for <kvm@archiver.kernel.org>; Wed,  3 Feb 2021 02:19:53 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 3022164F6A
	for <kvm@archiver.kernel.org>; Wed,  3 Feb 2021 02:19:53 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S231156AbhBCCTe (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 2 Feb 2021 21:19:34 -0500
Received: from aserp2130.oracle.com ([141.146.126.79]:55652 "EHLO
        aserp2130.oracle.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S230083AbhBCCTb (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 2 Feb 2021 21:19:31 -0500
Received: from pps.filterd (aserp2130.oracle.com [127.0.0.1])
        by aserp2130.oracle.com (8.16.0.42/8.16.0.42) with SMTP id
 1132Dn6i012542;
        Wed, 3 Feb 2021 02:18:47 GMT
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=oracle.com;
 h=from : to : cc :
 subject : date : message-id : content-transfer-encoding : content-type :
 mime-version; s=corp-2020-01-29;
 bh=ub+PU1DM2ZArPWFeODq7rhhOJtgYTCW5B+6fxPA4Lro=;
 b=cjOgk/ZGKdMdP6627D7ss6M5XDs8tv243B6yV0Y9d5aJ4s5JFVaYcqxee2ATjlCbmRMw
 PlWKm66oJIYmhH0S+A+9wxe9cyuIwceipq1vlAZn8kBCfqZmFabQXsckyzP2poJRByr0
 F7mLxt5LezYClZohDTaArvFnprQOD7NRfyliqD6r3ZXxwTkhtpcYdtSO3ltaHsLBD4Tm
 xtAxQFDh+WyYGmYwMlJj7BUb9Fdb70LzppHWn20R3KPcLgodK/1lc1ZQyxFbnhHgoaNl
 rs5KaL9+Q7s4beTk9Gh5crrdHtAoOReBtwIs2B9fTAjCJS2cAM9QIX9aiVWfElAZD7Cp Gg==
Received: from aserp3030.oracle.com (aserp3030.oracle.com [141.146.126.71])
        by aserp2130.oracle.com with ESMTP id 36cvyawwxy-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Wed, 03 Feb 2021 02:18:47 +0000
Received: from pps.filterd (aserp3030.oracle.com [127.0.0.1])
        by aserp3030.oracle.com (8.16.0.42/8.16.0.42) with SMTP id
 1132FWDo092784;
        Wed, 3 Feb 2021 02:16:47 GMT
Received: from nam10-bn7-obe.outbound.protection.outlook.com
 (mail-bn7nam10lp2102.outbound.protection.outlook.com [104.47.70.102])
        by aserp3030.oracle.com with ESMTP id 36dh1q06ax-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Wed, 03 Feb 2021 02:16:46 +0000
ARC-Seal: i=1; a=rsa-sha256; s=arcselector9901; d=microsoft.com; cv=none;
 b=lyhApyz1CRHv4m6D5EhucfETnUr2ahHh0FBQwDv2+AzztQufwvWS1vjtP4OR0gLlU1XF34UsrgqOrFRne2L7Uh5+Cf7upKjBZcm7NsW6bOReygMCF4lV4cPBAC9S1RoJI69KdbfOjNVF8hsjzjJuJBDBnbvhCW3w1xY7EY463drMhWiyJIi8jgVYrRVnCf5pQLg8jDi5ie6BEwwCDL8IxQGvZHJ7CHYsX86r6bH9gyRTibiYqhheCGXwJrqjdd1divmQk+WneW1mqLoFPBhGi0RpDu+Ebik8y1ar4YLtw6S27heFDRl1tD5f1pvpn03pvm9QJSxNtlUBGFjOSJPzfQ==
ARC-Message-Signature: i=1; a=rsa-sha256; c=relaxed/relaxed; d=microsoft.com;
 s=arcselector9901;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=ub+PU1DM2ZArPWFeODq7rhhOJtgYTCW5B+6fxPA4Lro=;
 b=FF7ViBcrWGGy/d4NVeTlcTO3/l3ONhk5GOc0g30bD7O+D4SHNQXA0JiZ5BZ7zFN9WrDaQ7cGuk0UAiMwYyHSQG2Kf8MoIJKwJjFq7Efaw+0jbaEcKELHZVPWj5HD79CL/UHXFzaEOMfKWUqExGwbkDk2FXqfJD0wXjo16pWeQ0GmQam4nrXKXXLKndaiW3B1uOzTRyVm9hFwV3aPh2My4DG+/T6vRCSF7eHZwZx+QI7/SKlM4RnA6Onty646+i8LlU3rMSZh0YJhdwnct1pJtvIHHD957ssNt0+XwdweTCtIHQLhRBtobMV3LPNE5WUfQ92kjrWWJL64PBhcTMCFmQ==
ARC-Authentication-Results: i=1; mx.microsoft.com 1; spf=pass
 smtp.mailfrom=oracle.com; dmarc=pass action=none header.from=oracle.com;
 dkim=pass header.d=oracle.com; arc=none
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
 d=oracle.onmicrosoft.com; s=selector2-oracle-onmicrosoft-com;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=ub+PU1DM2ZArPWFeODq7rhhOJtgYTCW5B+6fxPA4Lro=;
 b=yBRl5TmdiUIo054R2uru/4e/f1TQ80YN2s1KRrEYQLnCryHpPwQPtylCjKYZRvFcCeaySWun8lIYYpcyEhQSj72phbLPdsmcG/YMn8rF4+qwkUVUffcFjyNTV8qJsAAkVQxeLho34Mrz00M42RbjTCJ6w94YofDS2gUNivvCTSE=
Authentication-Results: vger.kernel.org; dkim=none (message not signed)
 header.d=none;vger.kernel.org; dmarc=none action=none header.from=oracle.com;
Received: from SN6PR10MB3021.namprd10.prod.outlook.com (2603:10b6:805:cc::19)
 by SA2PR10MB4793.namprd10.prod.outlook.com (2603:10b6:806:110::24) with
 Microsoft SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.3805.17; Wed, 3 Feb
 2021 02:16:45 +0000
Received: from SN6PR10MB3021.namprd10.prod.outlook.com
 ([fe80::1871:3741:cc17:bcf7]) by SN6PR10MB3021.namprd10.prod.outlook.com
 ([fe80::1871:3741:cc17:bcf7%7]) with mapi id 15.20.3825.020; Wed, 3 Feb 2021
 02:16:45 +0000
From: Krish Sadhukhan <krish.sadhukhan@oracle.com>
To: kvm@vger.kernel.org
Cc: pbonzini@redhat.com, jmattson@google.com, seanjc@google.com
Subject: [PATCH 0/3] nSVM: Test host RFLAGS.TF on VMRUN
Date: Tue,  2 Feb 2021 20:28:39 -0500
Message-Id: <20210203012842.101447-1-krish.sadhukhan@oracle.com>
X-Mailer: git-send-email 2.25.4
X-Originating-IP: [138.3.200.29]
X-ClientProxiedBy: SJ0PR03CA0096.namprd03.prod.outlook.com
 (2603:10b6:a03:333::11) To SN6PR10MB3021.namprd10.prod.outlook.com
 (2603:10b6:805:cc::19)
MIME-Version: 1.0
X-MS-Exchange-MessageSentRepresentingType: 1
Received: from ban25x6uut29.us.oracle.com (138.3.200.29) by
 SJ0PR03CA0096.namprd03.prod.outlook.com (2603:10b6:a03:333::11) with
 Microsoft SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.3825.19 via Frontend
 Transport; Wed, 3 Feb 2021 02:16:44 +0000
X-MS-PublicTrafficType: Email
X-MS-Office365-Filtering-Correlation-Id: 50976dc3-3d20-4999-5738-08d8c7e9c0ce
X-MS-TrafficTypeDiagnostic: SA2PR10MB4793:
X-Microsoft-Antispam-PRVS: 
 <SA2PR10MB479303C02D7DD3DDB14AF5D881B49@SA2PR10MB4793.namprd10.prod.outlook.com>
X-MS-Oob-TLC-OOBClassifiers: OLM:7691;
X-MS-Exchange-SenderADCheck: 1
X-Microsoft-Antispam: BCL:0;
X-Microsoft-Antispam-Message-Info: 
 Twal9vU4em3M60kholqB4uJUb2UaedhuB+wlN+38iAHPFCwKHZTXCBZA1ywBxJAuS89x1UD3xadvXsdgSimKqQyyZjT2UfI1aPwclvAqr4tLOHkUh92xRZ9fR9GBvfUfROC+AExx9FePpmgyzqJglKBBJG9mLwvrU3Veg8Z/LicLAGOIuA3OJPqGlbg08rGDzerJv6Ggi3uHdFhefyM/PJTtq4fOk5hv758BEiRqXAka2bbYpMPGTSe00Wly38SY7rt5zyAk21mc5vbbJxurKvsJTkiSjHNaJFzC8m7HgFfBKPE1BMqNh+UNqWBRXvhZU3x4SojyO9Rd43UkvMFFpetAVm4szPWL/wUsfAsW2KpQmzkQySMd4Zhvn+vdVxxhlPdr5MsFV9zUJrIVVIH939o2AyDnjR7eSPig/cVplcZ4wfMVKWjZsMBxbWLkFE7Ij3LF8VLiIbnj90iKIoLOnETVa+Af2Vjm1fuznC+LC7cig9xsrVm1sEsVXCjJGwNFJe09SPu8t4FR2jeqC/lHLQ==
X-Forefront-Antispam-Report: 
 CIP:255.255.255.255;CTRY:;LANG:en;SCL:1;SRV:;IPV:NLI;SFV:NSPM;H:SN6PR10MB3021.namprd10.prod.outlook.com;PTR:;CAT:NONE;SFS:(366004)(39860400002)(376002)(346002)(396003)(136003)(316002)(6666004)(36756003)(8676002)(66946007)(16526019)(66476007)(6486002)(7696005)(83380400001)(4326008)(6916009)(2906002)(86362001)(5660300002)(956004)(186003)(1076003)(44832011)(52116002)(8936002)(26005)(478600001)(2616005)(66556008);DIR:OUT;SFP:1101;
X-MS-Exchange-AntiSpam-MessageData: 
 W9LERX7u0JgO2bsQHR3ERU4BQVkWvDXWfnbePd1gqmdekxix/tUFfGkEklJYS5wmY4RmP8VRXfziqvFQki6lgSaX7/6t3mrfDFFfLIUXBdUQ4WvAFvhE2WOYGW7i1PdCgO9E+2VVJz8Y2KTX+er6gP2+wkih8+Xs+M3PuRDI/BQnIbpD6DAK3zE7U8R6PFx7uWEr/1gppk2MMtUFnLYFzBiRsZIaAbuP0pYzoqcsTtvTTtcKZKITQXQRK1w7JHpKrLfO2R2UKmXUueMGzkMFxTlyj+4cFXwmEtOHOFBO4zLOvBWLiVQDZHUTk7AqAz8QtIYsemX5orSyQHV8Nv4ZDRpwfkYSUBWN2yiree/Y8O4VjbWI5/GZHKpfWhele6FlMQ0pGf6hKzY4zH0kgTa7WCSY34pWN+5pLcEjIZkw/RWhHM/Njs82LzuzLepRNIybIzTEiXYDKRq2e6Jrot1wMf9oV3G73Gqy4YI/A0RS6fU4lCJKgowYGo5FweP9j8C3jjWkQ+9ggRN3X9A/d26DOEEHhO8WIMP21DT37D0YX9JSYGqomzQMqySKrIUGL9M2MvQIxcUa+9xZqQmM3AhT6otUD6rU4h26J8a6vTDbCLsLTm0vokrXggKcAHUTOK/uFpIZnE+xjEARaScdqhlLZstccMj8qNMB+bTAGQ2tAloEFTtyQdRpjayFATQ39ZLDwz0s77MPJ64zg1L/O/cVNOal+IRYPcYoYfVH0cOt/lBs8riC8d/+fDvvJ7Q3o2C8WK2OmMdlbZLXQbBbdzMK3rxTJqK7xuZ+FoQINm7spM7SXdUMj2p4ngnu5wPnxRuMNztbwH+OqHEIIxmSnKrt/s2pmkXlfb9Ti6RQ533LaoTCTf7nekruSkl2sfkohvOVNNRKzCQdbdKDUZsTzCI3hJU/21NMUHgqUswp4ubMJdBc5cjdCTXNDB3s72AfavLchyIe+8QvKTqoQYbecdkStSOfic67QNfqs0r+0TKOClboRkjnR8n4W2ACwiP5UVIEBaa2E2gL2G7nT0HTdDtxusdHkSbqgnB1N+MUtZV+B5Njq8TLngs/euqrpXLw17Wx
X-OriginatorOrg: oracle.com
X-MS-Exchange-CrossTenant-Network-Message-Id: 
 50976dc3-3d20-4999-5738-08d8c7e9c0ce
X-MS-Exchange-CrossTenant-AuthSource: SN6PR10MB3021.namprd10.prod.outlook.com
X-MS-Exchange-CrossTenant-AuthAs: Internal
X-MS-Exchange-CrossTenant-OriginalArrivalTime: 03 Feb 2021 02:16:45.1319
 (UTC)
X-MS-Exchange-CrossTenant-FromEntityHeader: Hosted
X-MS-Exchange-CrossTenant-Id: 4e2c6054-71cb-48f1-bd6c-3a9705aca71b
X-MS-Exchange-CrossTenant-MailboxType: HOSTED
X-MS-Exchange-CrossTenant-UserPrincipalName: 
 111vr6YQN1keKo0h30jGZPWZit8L/XAcIkTolmoRT/EGpMjsVECQV0ziU3GLeb9veKLVNmV5jiavxUEL5qBa+FqFzuH98R13Wz/F4VB8F1g=
X-MS-Exchange-Transport-CrossTenantHeadersStamped: SA2PR10MB4793
X-Proofpoint-Virus-Version: vendor=nai engine=6200 definitions=9883
 signatures=668683
X-Proofpoint-Spam-Details: rule=notspam policy=default score=0 adultscore=0
 spamscore=0 phishscore=0
 suspectscore=0 mlxlogscore=704 bulkscore=0 mlxscore=0 malwarescore=0
 classifier=spam adjust=0 reason=mlx scancount=1 engine=8.12.0-2009150000
 definitions=main-2102030007
X-Proofpoint-Virus-Version: vendor=nai engine=6200 definitions=9883
 signatures=668683
X-Proofpoint-Spam-Details: rule=notspam policy=default score=0 clxscore=1015
 impostorscore=0
 mlxscore=0 spamscore=0 bulkscore=0 priorityscore=1501 adultscore=0
 lowpriorityscore=0 malwarescore=0 phishscore=0 mlxlogscore=884
 suspectscore=0 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.12.0-2009150000 definitions=main-2102030007
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

According to section "VMRUN and TF/RF Bits in EFLAGS" in AMD APM vol 2,

    "From the host point of view, VMRUN acts like a single instruction,
     even though an arbitrary number of guest instructions may execute
     before a #VMEXIT effectively completes the VMRUN. As a single
     host instruction, VMRUN interacts with EFLAGS.TF like ordinary
     instructions. EFLAGS.TF causes a #DB trap after the VMRUN completes
     on the host side (i.e., after the #VMEXIT from the guest)."

Patch# 1 replaces a hard-coded value with a #define.
Patch# 2 modifies the assembly in svm_vmrun() so that a Single-Step breakpoint
can placed right before the VMRUN instruction. It also adds helper functions
for setting/un-setting that breakpoint.
Patch# 3 adds a test for the RFLAGS.TF on VMRUN.

[PATCH 1/3] KVM: SVM: Replace hard-coded value with #define
[PATCH 2/3] nVMX: Add helper functions to set/unset host RFLAGS.TF on
[PATCH 3/3] nSVM: Test effect of host RFLAGS.TF on VMRUN

 arch/x86/kvm/svm/svm.c | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

Krish Sadhukhan (1):
      KVM: SVM: Replace hard-coded value with #define

 x86/svm.c       | 24 +++++++++++++--
 x86/svm.h       |  3 ++
 x86/svm_tests.c | 94 ++++++++++++++++++++++++++++++++++++++++++++++++++++++++-
 3 files changed, 118 insertions(+), 3 deletions(-)

Krish Sadhukhan (2):
      nVMX: Add helper functions to set/unset host RFLAGS.TF on the VMRUN instruction
      nSVM: Test effect of host RFLAGS.TF on VMRUN
```
#### [PATCH v15 00/14] Introduce support for guest CET feature
##### From: Yang Weijiang <weijiang.yang@intel.com>

```c
From patchwork Wed Feb  3 11:34:07 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Yang Weijiang <weijiang.yang@intel.com>
X-Patchwork-Id: 12064035
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-11.8 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,
	SPF_PASS,URIBL_BLOCKED,USER_AGENT_GIT autolearn=unavailable
	autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 8E283C433E6
	for <kvm@archiver.kernel.org>; Wed,  3 Feb 2021 11:22:53 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 499A064F61
	for <kvm@archiver.kernel.org>; Wed,  3 Feb 2021 11:22:53 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S234057AbhBCLWr (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Wed, 3 Feb 2021 06:22:47 -0500
Received: from mga01.intel.com ([192.55.52.88]:28325 "EHLO mga01.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S233970AbhBCLWq (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 3 Feb 2021 06:22:46 -0500
IronPort-SDR: 
 nJYUJ1hUw0sE/6CINFu/oJyXBm/DjWXiGFwm+B4i5TwHEDIo8M6CLS5Z6V+QQuaC/hPi/N3XwZ
 hhtJ3DP/Ng7A==
X-IronPort-AV: E=McAfee;i="6000,8403,9883"; a="199981235"
X-IronPort-AV: E=Sophos;i="5.79,398,1602572400";
   d="scan'208";a="199981235"
Received: from fmsmga001.fm.intel.com ([10.253.24.23])
  by fmsmga101.fm.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 03 Feb 2021 03:22:06 -0800
IronPort-SDR: 
 4CwbJBiVuhCqSMw5YwctAc1JDpfNvzeY0EsZquY01+60QuHSBNKdG9QPE4NkimN5J3MVal+fiL
 mHZzIEH+bipA==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.79,398,1602572400";
   d="scan'208";a="480311057"
Received: from unknown (HELO local-michael-cet-test.sh.intel.com)
 ([10.239.159.166])
  by fmsmga001.fm.intel.com with ESMTP; 03 Feb 2021 03:22:04 -0800
From: Yang Weijiang <weijiang.yang@intel.com>
To: pbonzini@redhat.com, seanjc@google.com, jmattson@google.com,
        kvm@vger.kernel.org, linux-kernel@vger.kernel.org
Cc: yu.c.zhang@linux.intel.com, Yang Weijiang <weijiang.yang@intel.com>
Subject: [PATCH v15 00/14] Introduce support for guest CET feature
Date: Wed,  3 Feb 2021 19:34:07 +0800
Message-Id: <20210203113421.5759-1-weijiang.yang@intel.com>
X-Mailer: git-send-email 2.17.2
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Control-flow Enforcement Technology (CET) provides protection against
Return/Jump-Oriented Programming (ROP/JOP) attack. There're two CET
subfeatures: Shadow Stack (SHSTK) and Indirect Branch Tracking (IBT).
SHSTK is to prevent ROP and IBT is to prevent JOP.

Several parts in KVM have been updated to provide guest CET support, including:
CPUID/XSAVES settings, MSR passthrough, user-space MSR access interface, 
vmentry/vmexit config, nested VM etc. These patches are dependent on CET
kernel patches for XSAVES support and CET definitions, e.g., MSR and related
feature flags.

CET kernel patches: refer to [1], [2].

Previous CET KVM patches: refer to [3].

CET QEMU patches: refer to [4].

CET KVM unit-test patch: refer to [5].

[1]: CET Shadow Stack patches v18:
https://lkml.kernel.org/linux-api/20210127212524.10188-1-yu-cheng.yu@intel.com/

[2]: Indirect Branch Tracking patches v18:
https://lkml.kernel.org/linux-api/20210127213028.11362-1-yu-cheng.yu@intel.com/

[3]: CET KVM patches v14:
https://lkml.kernel.org/kvm/20201106011637.14289-1-weijiang.yang@intel.com/

[4]: CET QEMU patches:
https://patchwork.ozlabs.org/project/qemu-devel/patch/20201013051935.6052-2-weijiang.yang@intel.com/

[5]: CET KVM unit-test patch:
https://patchwork.kernel.org/project/kvm/patch/20200506082110.25441-12-weijiang.yang@intel.com/

Changes in v15:
- Changed patches per Paolo's review feedback on v14.
- Added a new patch for GUEST_SSP save/restore in guest SMM case.
- Fixed guest call-trace issue due to CET MSR interception.
- Removed unnecessary guest CET state cleanup in VMCS.
- Rebased patches to 5.11-rc6.


Sean Christopherson (2):
  KVM: x86: Report XSS as an MSR to be saved if there are supported
    features
  KVM: x86: Load guest fpu state when accessing MSRs managed by XSAVES

Yang Weijiang (12):
  KVM: x86: Refresh CPUID on writes to MSR_IA32_XSS
  KVM: x86: Add #CP support in guest exception dispatch
  KVM: VMX: Introduce CET VMCS fields and flags
  KVM: x86: Add fault checks for CR4.CET
  KVM: VMX: Emulate reads and writes to CET MSRs
  KVM: VMX: Add a synthetic MSR to allow userspace VMM to access
    GUEST_SSP
  KVM: x86: Report CET MSRs as to-be-saved if CET is supported
  KVM: x86: Enable CET virtualization for VMX and advertise CET to
    userspace
  KVM: VMX: Pass through CET MSRs to the guest when supported
  KVM: nVMX: Add helper to check the vmcs01 MSR bitmap for MSR
    pass-through
  KVM: nVMX: Enable CET support for nested VMX
  KVM: x86: Save/Restore GUEST_SSP to/from SMRAM

 arch/x86/include/asm/kvm_host.h      |   4 +-
 arch/x86/include/asm/vmx.h           |   8 ++
 arch/x86/include/uapi/asm/kvm.h      |   1 +
 arch/x86/include/uapi/asm/kvm_para.h |   1 +
 arch/x86/kvm/cpuid.c                 |  26 +++-
 arch/x86/kvm/emulate.c               |  11 ++
 arch/x86/kvm/vmx/capabilities.h      |   5 +
 arch/x86/kvm/vmx/nested.c            |  57 ++++++--
 arch/x86/kvm/vmx/vmcs12.c            |   6 +
 arch/x86/kvm/vmx/vmcs12.h            |  14 +-
 arch/x86/kvm/vmx/vmx.c               | 202 ++++++++++++++++++++++++++-
 arch/x86/kvm/x86.c                   |  67 ++++++++-
 arch/x86/kvm/x86.h                   |  10 +-
 13 files changed, 387 insertions(+), 25 deletions(-)
```
#### [PATCH v2 0/4] KVM: x86/pmu: Guest Architectural LBR Enabling
##### From: Like Xu <like.xu@linux.intel.com>

```c
From patchwork Wed Feb  3 13:57:10 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Like Xu <like.xu@linux.intel.com>
X-Patchwork-Id: 12064445
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-11.8 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,
	SPF_PASS,URIBL_BLOCKED,USER_AGENT_GIT autolearn=unavailable
	autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 04A8AC433E9
	for <kvm@archiver.kernel.org>; Wed,  3 Feb 2021 14:05:54 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id B049A64F8C
	for <kvm@archiver.kernel.org>; Wed,  3 Feb 2021 14:05:53 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S232320AbhBCOFe (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Wed, 3 Feb 2021 09:05:34 -0500
Received: from mga06.intel.com ([134.134.136.31]:50299 "EHLO mga06.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S231646AbhBCOFc (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 3 Feb 2021 09:05:32 -0500
IronPort-SDR: 
 J6RfAnz3w2KbZR6c6ww9bgFRo3skTRoUfvdP49C2Es3zwc300ejkBVIxWjhR/7nT8s+KMUmm5c
 CpR9+bJxHFTA==
X-IronPort-AV: E=McAfee;i="6000,8403,9883"; a="242555093"
X-IronPort-AV: E=Sophos;i="5.79,398,1602572400";
   d="scan'208";a="242555093"
Received: from fmsmga008.fm.intel.com ([10.253.24.58])
  by orsmga104.jf.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 03 Feb 2021 06:03:45 -0800
IronPort-SDR: 
 1MkfoKdoUismecvhxu1hC99BL3+koMNB4qoNTQZ0hV59SwN7IsNt5R2pa3IzQUm5fqa7/p3sOk
 0yqZMHs+8s1w==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.79,398,1602572400";
   d="scan'208";a="371490636"
Received: from clx-ap-likexu.sh.intel.com ([10.239.48.108])
  by fmsmga008.fm.intel.com with ESMTP; 03 Feb 2021 06:03:43 -0800
From: Like Xu <like.xu@linux.intel.com>
To: Paolo Bonzini <pbonzini@redhat.com>,
        Sean Christopherson <seanjc@google.com>
Cc: Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org
Subject: [PATCH v2 0/4] KVM: x86/pmu: Guest Architectural LBR Enabling
Date: Wed,  3 Feb 2021 21:57:10 +0800
Message-Id: <20210203135714.318356-1-like.xu@linux.intel.com>
X-Mailer: git-send-email 2.29.2
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Hi geniuses,

Please help review the new version of Arch LBR enabling on
KVM based on the latest kvm/queue tree.

The Architectural Last Branch Records (LBRs) is publiced
in the 319433-040 release of Intel Architecture Instruction
Set Extensions and Future Features Programming Reference[0].

The main advantages for the Arch LBR users are [1]:
- Faster context switching due to XSAVES support and faster reset of
  LBR MSRs via the new DEPTH MSR
- Faster LBR read for a non-PEBS event due to XSAVES support, which
  lowers the overhead of the NMI handler. (For a PEBS event, the LBR
  information is recorded in the PEBS records. There is no impact on
  the PEBS event.)
- Linux kernel can support the LBR features without knowing the model
  number of the current CPU.

Please check more details in each commit and feel free to comment.

[0] https://software.intel.com/content/www/us/en/develop/download/
intel-architecture-instruction-set-extensions-and-future-features-programming-reference.html
[1] https://lore.kernel.org/lkml/1593780569-62993-1-git-send-email-kan.liang@linux.intel.com/
---
v1->v2 Changelog:
- rebased on the latest kvm/queue tree;
- refine some comments for guest usage;

Previous:
https://lore.kernel.org/kvm/20200731074402.8879-1-like.xu@linux.intel.com/

Like Xu (4):
  KVM: vmx/pmu: Add MSR_ARCH_LBR_DEPTH emulation for Arch LBR
  KVM: vmx/pmu: Add MSR_ARCH_LBR_CTL emulation for Arch LBR
  KVM: vmx/pmu: Add Arch LBR emulation and its VMCS field
  KVM: x86: Expose Architectural LBR CPUID and its XSAVES bit

 arch/x86/include/asm/vmx.h      |  4 ++
 arch/x86/kvm/cpuid.c            | 23 ++++++++++
 arch/x86/kvm/vmx/capabilities.h | 25 +++++++----
 arch/x86/kvm/vmx/pmu_intel.c    | 74 +++++++++++++++++++++++++++++++--
 arch/x86/kvm/vmx/vmx.c          | 15 ++++++-
 arch/x86/kvm/vmx/vmx.h          |  3 ++
 arch/x86/kvm/x86.c              | 10 ++++-
 7 files changed, 140 insertions(+), 14 deletions(-)
```
#### [PATCH v6 00/19] KVM: Add minimal support for Xen HVM guests
##### From: David Woodhouse <dwmw2@infradead.org>

```c
From patchwork Wed Feb  3 15:00:55 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 8bit
X-Patchwork-Submitter: David Woodhouse <dwmw2@infradead.org>
X-Patchwork-Id: 12064549
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-18.8 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_PATCH,
	MAILING_LIST_MULTI,MENTIONS_GIT_HOSTING,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT
	autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 665A6C433E0
	for <kvm@archiver.kernel.org>; Wed,  3 Feb 2021 15:03:00 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 23D7B64E58
	for <kvm@archiver.kernel.org>; Wed,  3 Feb 2021 15:03:00 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S233519AbhBCPC5 (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Wed, 3 Feb 2021 10:02:57 -0500
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:34054 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S233500AbhBCPCy (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 3 Feb 2021 10:02:54 -0500
Received: from casper.infradead.org (casper.infradead.org
 [IPv6:2001:8b0:10b:1236::1])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id EFFF1C0612F2
        for <kvm@vger.kernel.org>; Wed,  3 Feb 2021 07:01:34 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; q=dns/txt; c=relaxed/relaxed;
        d=infradead.org; s=casper.20170209;
 h=Sender:Content-Transfer-Encoding:
        Content-Type:MIME-Version:Message-Id:Date:Subject:Cc:To:From:Reply-To:
        Content-ID:Content-Description:In-Reply-To:References;
        bh=x2sGKJUCkXfDUUSgDmA+bexsh4nUDvs8zRJ9h3uMecA=;
 b=Vyi4joLXS8RkyM4J+VgZbA3G7V
        8udkg8hTGWChC8ygLn0fgBBrrdn1deOPEKnV5JUxYyEoNC2uuKBtOChtIbYgR9erfTiE4OXspZmlJ
        n7H217zepui9j7cDAoB8mhestVjGQTecUQ0sJ+lFQ1rFzDVos3PaKL1Nu/Xw4FKA8ZwRJ/G/FTuVV
        2ZdD6BTJJz01tNbjgyBae0csK/ThA3KiF4OMEyPysoonC8kwInVqk8ZNKG79PIpmzQzFm3jixXskO
        c86CEYOJfEM6cSVoZ892lwl0sPPEseRmBgBAIAyEOfAM5DzYWm9FfAp7b6i4j8suMJGulSSo17A5C
        YvyH3H4g==;
Received: from i7.infradead.org ([2001:8b0:10b:1:21e:67ff:fecb:7a92])
        by casper.infradead.org with esmtpsa (Exim 4.94 #2 (Red Hat Linux))
        id 1l7Jef-00H3zF-Ef; Wed, 03 Feb 2021 15:01:20 +0000
Received: from dwoodhou by i7.infradead.org with local (Exim 4.94 #2 (Red Hat
 Linux))
        id 1l7Jef-003re8-0g; Wed, 03 Feb 2021 15:01:17 +0000
From: David Woodhouse <dwmw2@infradead.org>
To: kvm@vger.kernel.org
Cc: Paolo Bonzini <pbonzini@redhat.com>,
        Ankur Arora <ankur.a.arora@oracle.com>,
        Joao Martins <joao.m.martins@oracle.com>,
        Boris Ostrovsky <boris.ostrovsky@oracle.com>,
        Sean Christopherson <seanjc@google.com>, graf@amazon.com,
        iaslan@amazon.de, pdurrant@amazon.com, aagch@amazon.com,
        fandree@amazon.com, hch@infradead.org
Subject: [PATCH v6 00/19] KVM: Add minimal support for Xen HVM guests
Date: Wed,  3 Feb 2021 15:00:55 +0000
Message-Id: <20210203150114.920335-1-dwmw2@infradead.org>
X-Mailer: git-send-email 2.29.2
MIME-Version: 1.0
Sender: David Woodhouse <dwmw2@infradead.org>
X-SRS-Rewrite: SMTP reverse-path rewritten from <dwmw2@infradead.org> by
 casper.infradead.org. See http://www.infradead.org/rpr.html
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This patch set provides enough kernel support to allow hosting Xen HVM 
guests in KVM. It allows hypercalls to be trapped to userspace for 
handling, uses the existing KVM functions for writing system clock and 
pvclock information to Xen shared pages, and event channel upcall vector 
delivery.

It's based on the first section of a patch set that Joao posted as 
RFC last year^W^W in 2019:

https://lore.kernel.org/kvm/20190220201609.28290-1-joao.m.martins@oracle.com/

In v6 I've dropped the runstate support temporarily. It can come in the 
next round of patches, and I want to give it more thought. In particular 
Paul pointed out that we need to support VCPUOP_get_runstate_info — the 
runstate times aren't *only* exposed to a guest by putting them directly 
into the guest memory. So we'll need an ioctl to fetch them to userspace 
as well as to set them on live migration. I've expanded the padding in 
the newly added KVM_XEN_VCPU_[SG]ET_ATTR ioctls to make sure there's 
room.

I also want to double-check we're setting the runstates faithfully as 
Xen guests will expect in all circumstances. I think we may want a way 
for userspace to tell the kernel to set RUNSTATE_blocked and offline, 
and that can be set as a vCPU attr too.

Will work on that and post it along with the oft-promised second round,
but this part stands alone and should be ready to merge.

The rust-vmm support for this is starting to take shape at
https://github.com/alexandruag/vmm-reference/commits/xen

Change log for my postings:
v1:
 • Support for 32-bit guests
 • 64-bit second support in wallclock
 • Time counters for runnable/blocked states in runstate support
 • Self-tests
 • Fixed Viridian coexistence
 • No new KVM_CAP_XEN_xxx, just more bits returned by KVM_CAP_XEN_HVM

v2: 
 • Remember the RCU read-critical sections on using the shared info pages
 • Fix 32-bit build of compat structures (which we use there too)
 • Use RUNSTATE_blocked as initial state not RUNSTATE_runnable
 • Include documentation, add cosmetic KVM_XEN_HVM_CONFIG_HYPERCALL_MSR

v3:
 • Stop mapping the shared pages; use kvm_guest_write_cached() instead.
 • Use kvm_setup_pvclock_page() for Xen pvclock writes too.
 • Fix CPU numbering confusion and update documentation accordingly.
 • Support HVMIRQ_callback_vector delivery based on evtchn_upcall_pending.

v4:
 • Rebase on top of the KVM changes merged into 5.11-rc1.
 • Drop the kvm_{un,}map_gfn() cleanup as it isn't used since v2 anyway.
 • Trivial cosmetic cleanup (superfluous parens, remove declaration of a
   function removed in v3, etc.)

v5:
 • Rebased onto kvm/next as of 2021-01-08 (commit 872f36eb0b0f4).
 • Fix error handling for XEN_HVM_GET_ATTR.
 • Stop moving struct kvm_host_map definition; it's not used any more.
 • Add explicit padding to struct kvm_xen_hvm_attr to make it have
   identical layout on 32-bit vs. 64-bit machines.

v6:
 • Move per-vCPU attributes to KVM_XEN_VCPU_[SG]ET_ATTR ioctl.
 • Drop runstate support for now; that needs more work/thought.
 • Add static key for kvm_xen_enabled to eliminate overhead.
 • Fix pre-existing lack of __user tag in hypercall page setup.
 • Expand padding in attribute ioctl structs to 8 64-bit words.

 Documentation/virt/kvm/api.rst                     | 170 ++++++++-
 arch/x86/include/asm/kvm_host.h                    |  19 +
 arch/x86/include/asm/xen/interface.h               |   3 +
 arch/x86/kvm/Makefile                              |   2 +-
 arch/x86/kvm/hyperv.c                              |  40 +-
 arch/x86/kvm/irq.c                                 |   7 +
 arch/x86/kvm/trace.h                               |  36 ++
 arch/x86/kvm/x86.c                                 | 140 ++++---
 arch/x86/kvm/x86.h                                 |   1 +
 arch/x86/kvm/xen.c                                 | 411 +++++++++++++++++++++
 arch/x86/kvm/xen.h                                 |  77 ++++
 include/uapi/linux/kvm.h                           |  60 +++
 include/xen/interface/xen.h                        |   4 +-
 tools/testing/selftests/kvm/Makefile               |   3 +
 tools/testing/selftests/kvm/lib/kvm_util.c         |   1 +
 .../testing/selftests/kvm/x86_64/xen_shinfo_test.c | 197 ++++++++++
 .../testing/selftests/kvm/x86_64/xen_vmcall_test.c | 150 ++++++++
 17 files changed, 1251 insertions(+), 70 deletions(-)

David Woodhouse (10):
      KVM: x86/xen: Fix __user pointer handling for hypercall page installation
      KVM: x86/xen: Move KVM_XEN_HVM_CONFIG handling to xen.c
      KVM: x86/xen: Add kvm_xen_enabled static key
      KVM: x86/xen: latch long_mode when hypercall page is set up
      KVM: x86/xen: add definitions of compat_shared_info, compat_vcpu_info
      xen: add wc_sec_hi to struct shared_info
      KVM: x86/xen: Add KVM_XEN_VCPU_SET_ATTR/KVM_XEN_VCPU_GET_ATTR
      KVM: x86/xen: Add event channel interrupt vector upcall
      KVM: x86: declare Xen HVM shared info capability and add test case
      KVM: Add documentation for Xen hypercall and shared_info updates

Joao Martins (9):
      KVM: x86/xen: fix Xen hypercall page msr handling
      KVM: x86/xen: intercept xen hypercalls if enabled
      KVM: x86/xen: Fix coexistence of Xen and Hyper-V hypercalls
      KVM: x86/xen: add KVM_XEN_HVM_SET_ATTR/KVM_XEN_HVM_GET_ATTR
      KVM: x86/xen: register shared_info page
      KVM: x86/xen: update wallclock region
      KVM: x86/xen: register vcpu info
      KVM: x86/xen: setup pvclock updates
      KVM: x86/xen: register vcpu time info region
```
#### [PATCH 0/3] vfio/type1: batch page pinning
##### From: Daniel Jordan <daniel.m.jordan@oracle.com>

```c
From patchwork Wed Feb  3 20:47:53 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Daniel Jordan <daniel.m.jordan@oracle.com>
X-Patchwork-Id: 12065305
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-13.8 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_PATCH,
	MAILING_LIST_MULTI,MSGID_FROM_MTA_HEADER,SPF_HELO_NONE,SPF_PASS,
	USER_AGENT_GIT autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 0A2C3C433DB
	for <kvm@archiver.kernel.org>; Wed,  3 Feb 2021 20:50:18 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id C227764F58
	for <kvm@archiver.kernel.org>; Wed,  3 Feb 2021 20:50:17 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S232152AbhBCUuJ (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Wed, 3 Feb 2021 15:50:09 -0500
Received: from aserp2130.oracle.com ([141.146.126.79]:38946 "EHLO
        aserp2130.oracle.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S232346AbhBCUtc (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 3 Feb 2021 15:49:32 -0500
Received: from pps.filterd (aserp2130.oracle.com [127.0.0.1])
        by aserp2130.oracle.com (8.16.0.42/8.16.0.42) with SMTP id
 113Kdoln011008;
        Wed, 3 Feb 2021 20:48:15 GMT
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=oracle.com;
 h=from : to : cc :
 subject : date : message-id : content-transfer-encoding : content-type :
 mime-version; s=corp-2020-01-29;
 bh=MMAIGVidxAoUcHFDQVwPcGjXu3GebjAX1UdGntEwyM8=;
 b=h4IU900LhcefsDikO8hfpNGEAn/mBCVE/dYPBB4OwOE2W1qcI+EFVxUHekuxy+6HYy4t
 HC6wm3PSIxJrWVA2KaUf9XrFIPtH2EmdHlBbZVYP9DwhE6CPu94n1DNL9tL2G/XjrHCU
 7m8KB7NnOfh65RGNQbQY5D1ulIBGvBswhyOxnrrx7qf+YdFGwClBQMPiUYfKzCRTXeZh
 h+jJkwkZbTGQTVqbVBiJaHe2C7dZ8F5ExwbXqMg/DtbTyfID3+D7lVC26bfR8LbmjtUB
 IHreOkaxyCNAKcyEle/I8VDRLS5VUOkN+MZ9MXjCQ+zCpH7188rUv4cru2xw/81X6CNx FA==
Received: from aserp3020.oracle.com (aserp3020.oracle.com [141.146.126.70])
        by aserp2130.oracle.com with ESMTP id 36cvyb2btc-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Wed, 03 Feb 2021 20:48:14 +0000
Received: from pps.filterd (aserp3020.oracle.com [127.0.0.1])
        by aserp3020.oracle.com (8.16.0.42/8.16.0.42) with SMTP id
 113Kj3ib135633;
        Wed, 3 Feb 2021 20:48:14 GMT
Received: from nam04-bn8-obe.outbound.protection.outlook.com
 (mail-bn8nam08lp2044.outbound.protection.outlook.com [104.47.74.44])
        by aserp3020.oracle.com with ESMTP id 36dhc1qb23-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Wed, 03 Feb 2021 20:48:14 +0000
ARC-Seal: i=1; a=rsa-sha256; s=arcselector9901; d=microsoft.com; cv=none;
 b=AwSImoLETAhnSv5Cyd64OiVosNhEOaHvJOswl5N1/BozarU/TENjwThGQApvZD7zTyPW8neKEs+/2ojsEnhuMJixqrljNwd+6fepB/ryZaHm7GSOih6PjopsnXTDtRAaMvFLr9gO3GJ5O26GcE+YrfQK9bCwdw5bvNPOvHb3Bn8UvtKf7zjWNuDbzgPXpaAqjnDacVzA+lPaD2gLtlPDI1XSWB+xaDuEK7H8mJXEv/BcM5maTnPZmU4SXphUpjtvGCvtd7l8e2E9fjlgcSa932CpepSs4Ul1R4WxGC9VE5YNGtF1sw4km2qkXJtdw7tHSuYqUd/nN1ppJ8KeY5DoQQ==
ARC-Message-Signature: i=1; a=rsa-sha256; c=relaxed/relaxed; d=microsoft.com;
 s=arcselector9901;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=MMAIGVidxAoUcHFDQVwPcGjXu3GebjAX1UdGntEwyM8=;
 b=U+ilUR1f30dldmFskp4a+1reneH2G5oHlurHB8PP15juBxMPCPNqlWi0X5BIoNn/NwxKjV1uOE8oevEGnTDINKhO8gtcVK8QVMBsqLQciB1L3SfRNS20dNu4i0KD60SW+D9iuQoTzWNeVr15dQNeSKRsEq6LUZ/aFdb4U0CQ0d78cr0YfsKQzhIe6DKu6pFhlNwCUhSgh+lPA7CexeLI2hb2YQH1N0oOXPwabPq1maIa17asDEZh7DguptOffp6fNynq33mFk+s4yR0BpJRANxvMsn1tLt4xWD+12siPtUk4I90BpOArP5y88PKN/eCj9mjAUrw6QluYwmTifVu0XQ==
ARC-Authentication-Results: i=1; mx.microsoft.com 1; spf=pass
 smtp.mailfrom=oracle.com; dmarc=pass action=none header.from=oracle.com;
 dkim=pass header.d=oracle.com; arc=none
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
 d=oracle.onmicrosoft.com; s=selector2-oracle-onmicrosoft-com;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=MMAIGVidxAoUcHFDQVwPcGjXu3GebjAX1UdGntEwyM8=;
 b=SivXX1r1v2FGZI7JDeI/44jhuDzuvwf+3z1Ak8hlJHsNSBbVZC/quS0hn0NNyNf/QCgB/Kn2CouQH8rmxUjFxi9uVyETdT3BOtV+wQmAO2iUN5XwhUiV0aYJree99zkryyiTlOrvBhBs+nfy5TDRu6PK7LvvcKot28EzsnrmDrU=
Authentication-Results: redhat.com; dkim=none (message not signed)
 header.d=none;redhat.com; dmarc=none action=none header.from=oracle.com;
Received: from MWHPR10MB1774.namprd10.prod.outlook.com (2603:10b6:301:9::13)
 by CO1PR10MB4691.namprd10.prod.outlook.com (2603:10b6:303:92::19) with
 Microsoft SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.3825.17; Wed, 3 Feb
 2021 20:48:12 +0000
Received: from MWHPR10MB1774.namprd10.prod.outlook.com
 ([fe80::24eb:1300:dd70:4183]) by MWHPR10MB1774.namprd10.prod.outlook.com
 ([fe80::24eb:1300:dd70:4183%3]) with mapi id 15.20.3805.027; Wed, 3 Feb 2021
 20:48:12 +0000
From: Daniel Jordan <daniel.m.jordan@oracle.com>
To: Alex Williamson <alex.williamson@redhat.com>,
        Cornelia Huck <cohuck@redhat.com>
Cc: Jason Gunthorpe <jgg@nvidia.com>,
        Matthew Wilcox <willy@infradead.org>,
        Pavel Tatashin <pasha.tatashin@soleen.com>,
        Steven Sistare <steven.sistare@oracle.com>,
        kvm@vger.kernel.org, linux-kernel@vger.kernel.org,
        Daniel Jordan <daniel.m.jordan@oracle.com>
Subject: [PATCH 0/3] vfio/type1: batch page pinning
Date: Wed,  3 Feb 2021 15:47:53 -0500
Message-Id: <20210203204756.125734-1-daniel.m.jordan@oracle.com>
X-Mailer: git-send-email 2.30.0
X-Originating-IP: [98.229.125.203]
X-ClientProxiedBy: BL1PR13CA0215.namprd13.prod.outlook.com
 (2603:10b6:208:2bf::10) To MWHPR10MB1774.namprd10.prod.outlook.com
 (2603:10b6:301:9::13)
MIME-Version: 1.0
X-MS-Exchange-MessageSentRepresentingType: 1
Received: from localhost.localdomain (98.229.125.203) by
 BL1PR13CA0215.namprd13.prod.outlook.com (2603:10b6:208:2bf::10) with
 Microsoft SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.3825.15 via Frontend
 Transport; Wed, 3 Feb 2021 20:48:11 +0000
X-MS-PublicTrafficType: Email
X-MS-Office365-Filtering-Correlation-Id: b941c865-641c-4b62-ea56-08d8c885056c
X-MS-TrafficTypeDiagnostic: CO1PR10MB4691:
X-MS-Exchange-Transport-Forked: True
X-Microsoft-Antispam-PRVS: 
 <CO1PR10MB4691A36C636AF39F8AE2D1E4D9B49@CO1PR10MB4691.namprd10.prod.outlook.com>
X-MS-Oob-TLC-OOBClassifiers: OLM:3826;
X-MS-Exchange-SenderADCheck: 1
X-Microsoft-Antispam: BCL:0;
X-Microsoft-Antispam-Message-Info: 
 /d7HnNDxQNkYkE4P1L+IglWA4wlK1+MexfPHP6/jkJBJdz2Zjy7IxoqehqsLkWckcBlhxFyK2JvPX7m/XFS4nyULLa9pPOLjRnj7wzl4AisuEbz/g5V+xNXhmYNRT3aZM25+j1q9iH9xIQogsPlA0HE4Jw1UtKOz0ydHzva2KOw58zCtRvT8UnGd83nuMwEmZIkOzarIdmYyWaTRUYsClNPE6XaogcUqQczUxX7Alv/Bx0Mj+J5K8T/sLL0I+I3bo37n+pxXvvA7BU90dzRSnRrTh/NmdkpDb3Y9Bsqu6MSV6WzPJ+w49O4hXkYGRbF0g/AZ2y2l69EDOCHhf+1GCg5To85WZ1n0wslFFUbLzDRGrMhjsDz8BKf7c19uUNi/bNrPDJ/grkFBAdL1HY6umfFbh39gM8+IHyvujksXtbiSp0GWby9HES1+D9Zq6vTw29UOZmrc1bELXvZUftSbj3bJPu/uh4zpo1lbcuf7qSxQ0pKWWW3Jk8+nm7fd4OURws55aXxlpAXmvRMi8dKld20fPgaCWomfBBHxeIfQbzd3aa+vvVQImEqYgIxtEfm+N+HudYpPTHVXZ66KIpyUjA==
X-Forefront-Antispam-Report: 
 CIP:255.255.255.255;CTRY:;LANG:en;SCL:1;SRV:;IPV:NLI;SFV:NSPM;H:MWHPR10MB1774.namprd10.prod.outlook.com;PTR:;CAT:NONE;SFS:(396003)(39860400002)(376002)(366004)(136003)(346002)(103116003)(6486002)(478600001)(36756003)(107886003)(4326008)(66946007)(8936002)(1076003)(16526019)(5660300002)(110136005)(54906003)(26005)(186003)(6506007)(69590400011)(52116002)(8676002)(86362001)(83380400001)(316002)(2906002)(6512007)(956004)(66476007)(66556008)(2616005)(6666004);DIR:OUT;SFP:1101;
X-MS-Exchange-AntiSpam-MessageData: 
 aWu3+1Z3V9AVCUfRRd6DZ5Rk8CMIS0EVp6cyWgbkJtNQtUvKTOigd57IbJl1Amv5jUcLjpT6crrdsyeHZCBKJ3XqvnhJzxcKYizDUGZQ1xjQDsNO/6lWXUyhiwwRmlU6/oOPZB6XtNu14c5S8lX6mq60YvNjYbtekVcMmcsGkCJNYqTes3sf6RlZ2FMq2/84w4EsTiwxjVNwSFZh82t+ozz08VaLkEYy6hiSgsUMA5Vg6eDjg65QnChbq5lBv3vwkcioqHmard+d+0faSKvcdDAR/2HbZ61dMeBAak47pl+P4gxUnHmB8synmPLIUkFqr1sZ1Wu1ZeIwebvNtmUNqRs3XMRyc7hpVGlUfxQJ6yEBt7P/WI1Z4QSjUaPYdRJyH0Njg4OO7tsNDQWgeqeKx/YZSLDqoE1oPiiV5sxHhUk3qDbxvOKFmbUen+oiKsri8P9tqsSW7egoOGiwxJVVCMV4G3OgiJyY7+R4skfxkfXPoaHKLQlgAfOjg6V0BdOVA7bXsiBSaM7IoOnvNF/pGxxVGndtgARwZ4+sQGat7USfxzWPx9odDeMu7uK3CWHDzd80qYXLHLW4g51gmAtFCVf2XTbVOp0wHNNGCH9xjGOM06tLfCgrqr5a8O8t4/pw5+hxHEBBT7OSuWdMSVBZy/5hJhFMDMw6PW5E2bZxtDlQkXMFZyBSu96dr+TW1/iA25756I07F49fhUXKiyhKZnb5ZUYnoQAzOx/arz8DTacArHxEadX/PkvxEF7Eob6EF01IrpxDcIuBO/RJG+FQf1iKKcEDWsf99XChYOK9JWB+Qo21K5lYD9ZpEMpkLQCfvMPoW7MplofVxGpAEuD4hqIKmovaWZPPNdqredlfO+Pp1R+b9ta7eMBVmgRgvTc34QMMRsOyslZO95qZhAdNi8u8H7ziLRe+g9uJJBTr13nyS8bzJPPB5IUE63IryXzZUG599T1xHe/NShNhzkQUr/4a06M50ooOMJOmfujRbzAeoFbObNCweygLdEh8KG3M10JLBl5WCwTZdScJAslABumr6bi0XPLhosjaMIipanyUsvijcgEZpUaxahgnO2RlBDXC8uO8xEr71srEKXqHEmkdX1srHn/OowG9Q2BJSsoNoBUyG7LhSo77SOlRQOlMIdLfkTspLUxAX32BZgTc+Zzkbs9LPJt/X6JSoZEFk+umDGmsId1mjtkiTO7Tqa/Lxytpiub3PCvTKG6e5ILgamFBLJrZNP0lORC8G+JYJkM3udUiyeIzHRTqxj1Au32qSkU8i9siHbOYIZgyNkW/xnfglzW8ndpOSVkWG20jqloUfOyNYFQqXq6ZoPAQxEj7
X-OriginatorOrg: oracle.com
X-MS-Exchange-CrossTenant-Network-Message-Id: 
 b941c865-641c-4b62-ea56-08d8c885056c
X-MS-Exchange-CrossTenant-AuthSource: MWHPR10MB1774.namprd10.prod.outlook.com
X-MS-Exchange-CrossTenant-AuthAs: Internal
X-MS-Exchange-CrossTenant-OriginalArrivalTime: 03 Feb 2021 20:48:12.2693
 (UTC)
X-MS-Exchange-CrossTenant-FromEntityHeader: Hosted
X-MS-Exchange-CrossTenant-Id: 4e2c6054-71cb-48f1-bd6c-3a9705aca71b
X-MS-Exchange-CrossTenant-MailboxType: HOSTED
X-MS-Exchange-CrossTenant-UserPrincipalName: 
 t/IpXgvLJ7L6pLKSu14R5FJ+lli0MVXX6bJxHsmerNCB8l0eaWBDtjTv4BO0w96ZRAMfWshDsdils87AhAEdkzgD/xDmndIpz3I9OoQ7mr0=
X-MS-Exchange-Transport-CrossTenantHeadersStamped: CO1PR10MB4691
X-Proofpoint-Virus-Version: vendor=nai engine=6200 definitions=9884
 signatures=668683
X-Proofpoint-Spam-Details: rule=notspam policy=default score=0 bulkscore=0
 adultscore=0 suspectscore=0
 spamscore=0 mlxscore=0 malwarescore=0 mlxlogscore=999 phishscore=0
 classifier=spam adjust=0 reason=mlx scancount=1 engine=8.12.0-2009150000
 definitions=main-2102030124
X-Proofpoint-Virus-Version: vendor=nai engine=6200 definitions=9884
 signatures=668683
X-Proofpoint-Spam-Details: rule=notspam policy=default score=0 clxscore=1011
 impostorscore=0
 mlxscore=0 spamscore=0 bulkscore=0 priorityscore=1501 adultscore=0
 lowpriorityscore=0 malwarescore=0 phishscore=0 mlxlogscore=999
 suspectscore=0 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.12.0-2009150000 definitions=main-2102030123
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Hi,

The VFIO type1 driver is calling pin_user_pages_remote() once per 4k page, so
let's do it once per 512 4k pages to bring VFIO in line with other drivers such
as IB and vDPA.

qemu guests with at least 2G memory start about 8% faster on a Xeon server,
with more detailed results in the last changelog.

Thanks to Matthew, who first suggested the idea to me.

Daniel


Test Cases
----------

 1) qemu passthrough with IOMMU-capable PCI device

 2) standalone program to hit
        vfio_pin_map_dma() -> vfio_pin_pages_remote()

 3) standalone program to hit
        vfio_iommu_replay() -> vfio_pin_pages_remote()

Each was run...

 - with varying sizes
 - with/without disable_hugepages=1
 - with/without LOCKED_VM exceeded

I didn't test vfio_pin_page_external() because there was no readily available
hardware, but the changes there are pretty minimal.

Series based on v5.11-rc6.


Daniel Jordan (3):
  vfio/type1: change success value of vaddr_get_pfn()
  vfio/type1: prepare for batched pinning with struct vfio_batch
  vfio/type1: batch page pinning

 drivers/vfio/vfio_iommu_type1.c | 213 +++++++++++++++++++++++---------
 1 file changed, 154 insertions(+), 59 deletions(-)


base-commit: 1048ba83fb1c00cd24172e23e8263972f6b5d9ac
```
#### [PATCH 00/12] Introduce dev-msi and interrupt message store
##### From: Megha Dey <megha.dey@intel.com>

```c
From patchwork Wed Feb  3 20:56:33 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 8bit
X-Patchwork-Submitter: Megha Dey <megha.dey@intel.com>
X-Patchwork-Id: 12065329
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.8 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_PATCH,MAILING_LIST_MULTI,
	MENTIONS_GIT_HOSTING,SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED,USER_AGENT_GIT
	autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id BEF16C433DB
	for <kvm@archiver.kernel.org>; Wed,  3 Feb 2021 20:58:41 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 76C7664E31
	for <kvm@archiver.kernel.org>; Wed,  3 Feb 2021 20:58:41 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S232796AbhBCU6R (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Wed, 3 Feb 2021 15:58:17 -0500
Received: from mga01.intel.com ([192.55.52.88]:12600 "EHLO mga01.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S232418AbhBCU6J (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 3 Feb 2021 15:58:09 -0500
IronPort-SDR: 
 Ufhf3p2MP74m6bMrZcfqIaAS97kWCDINIBVYs9Mt0cUpdmunjBL6F/H44bHHyqoP6QxtoHwBY4
 6YSYHDcUFyKw==
X-IronPort-AV: E=McAfee;i="6000,8403,9884"; a="200084219"
X-IronPort-AV: E=Sophos;i="5.79,399,1602572400";
   d="scan'208";a="200084219"
Received: from orsmga002.jf.intel.com ([10.7.209.21])
  by fmsmga101.fm.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 03 Feb 2021 12:57:28 -0800
IronPort-SDR: 
 yMqLzRM8tQcXr+F3v3s6g/9oYesf6lNaMFrMbQVl3ch/g8Svfv0ksgiAXszPU9lnf2HW0dIW1q
 2MR208kK0L6Q==
X-IronPort-AV: E=Sophos;i="5.79,399,1602572400";
   d="scan'208";a="372510537"
Received: from megha-z97x-ud7-th.sc.intel.com ([143.183.85.154])
  by orsmga002-auth.jf.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-SHA;
 03 Feb 2021 12:57:27 -0800
From: Megha Dey <megha.dey@intel.com>
To: tglx@linutronix.de
Cc: linux-kernel@vger.kernel.org, dave.jiang@intel.com,
        ashok.raj@intel.com, kevin.tian@intel.com, dwmw@amazon.co.uk,
        x86@kernel.org, tony.luck@intel.com, dan.j.williams@intel.com,
        megha.dey@intel.com, jgg@mellanox.com, kvm@vger.kernel.org,
        iommu@lists.linux-foundation.org, alex.williamson@redhat.com,
        bhelgaas@google.com, maz@kernel.org, linux-pci@vger.kernel.org,
        baolu.lu@linux.intel.com, ravi.v.shankar@intel.com
Subject: [PATCH 00/12] Introduce dev-msi and interrupt message store
Date: Wed,  3 Feb 2021 12:56:33 -0800
Message-Id: <1612385805-3412-1-git-send-email-megha.dey@intel.com>
X-Mailer: git-send-email 2.7.4
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Provide support for device specific MSI implementations for devices which
have their own resource management and interrupt chip. These devices are
not related to PCI and contrary to platform MSI they do not share a
common resource and interrupt chip. They provide their own domain specific
resource management and interrupt chip.

On top of this, add support for Interrupt Message Store or IMS[1], which
is a scalable device specific interrupt mechanism to support devices which
may need more than 2048 interrupts. With IMS, there is theoretically no
upper bound on the number of interrupts a device can support. The normal
IMS use case is for guest usages but it can very well be used by host too.

Introduce a generic IMS irq chip and domain which stores the interrupt
messages as an array in device memory. Allocation and freeing of interrupts
happens via the generic msi_domain_alloc/free_irqs() interface. One only
needs to ensure the interrupt domain is stored in the underlying device struct.

These patches can be divided into following steps:

1. X86 specific preparation for device MSI
   x86/irq: Add DEV_MSI allocation type
   x86/msi: Rename and rework pci_msi_prepare() to cover non-PCI MSI

2. Generic device MSI infrastructure
   platform-msi: Provide default irq_chip:: Ack
   genirq/proc: Take buslock on affinity write
   genirq/msi: Provide and use msi_domain_set_default_info_flags()
   platform-msi: Add device MSI infrastructure
   irqdomain/msi: Provide msi_alloc/free_store() callbacks
   genirq: Set auxiliary data for an interrupt

3. Interrupt Message Store (IMS) irq domain/chip implementation for device array
   irqchip: Add IMS (Interrupt Message Store) driver
   iommu/vt-d: Add DEV-MSI support

4. Add platform check for subdevice irq domain
   iommu: Add capability IOMMU_CAP_VIOMMU
   platform-msi: Add platform check for subdevice irq domain

The device IMS (Interrupt Message Storage) should not be enabled in any
virtualization environments unless there is a HYPERCALL domain which
makes the changes in the message store monitored by the hypervisor.[2]
As the initial step, we allow the IMS to be enabled only if we are
running on the bare metal. It's easy to enable IMS in the virtualization
environments if above preconditions are met in the future.

These patches have been tested with the IDXD driver:
        https://github.com/intel/idxd-driver idxd-stage2.5
Most of these patches are originally by Thomas:
        https://lore.kernel.org/linux-hyperv/20200826111628.794979401@linutronix.de/
and are rebased on latest kernel

This patches series has undergone a lot of changes since first submitted as an RFC
in September 2019. I have divided the changes into 3 stages for better understanding

Stage 1: Standalone RFC IMS series[3]
-------------------------------------
https://lore.kernel.org/lkml/1568338328-22458-1-git-send-email-megha.dey@linux.intel.com/
V1:
1. Extend existing platform-msi to support IMS
2. platform_msi_domain_alloc_irqs_group is introduced to allocate IMS
   interrupts, tagged with a group ID.
3. To free vectors of a particular group, platform_msi_domain_free_irqs_group
   API in introduced

Stage 2: dev-msi/IMS merged with Dave Jiang's IDXD series[2]
------------------------------------------------------------
V1: (changes from stage 1):
1. Introduced a new list for platform-msi descriptors
2. Introduced dynamic allocation for IMS interrupts
3. shifted creation of ims domain from arch/x86 to drivers/
4. Removed arch specific callbacks
5. Introduced enum platform_msi_type
6. Added more technical details to the cover letter
7. Merge common code between platform-msi.c and ims-msi.c
8. Introduce new structures platform_msi_ops and platform_msi_funcs
9. Addressed Andriy Shevchenko's comments on RFC V1 patch series
10. Dropped the dynamic group allocation scheme.
11. Use RCU lock instead of mutex lock to protect the device list

V2:
1. IMS made dev-msi
2. With recommendations from Jason/Thomas/Dan on making IMS more generic
3. Pass a non-pci generic device(struct device) for IMS management instead of mdev
4. Remove all references to mdev and symbol_get/put
5. Remove all references to IMS in common code and replace with dev-msi
6. Remove dynamic allocation of platform-msi interrupts: no groups,no
   new msi list or list helpers
7. Create a generic dev-msi domain with and without interrupt remapping enabled.
8. Introduce dev_msi_domain_alloc_irqs and dev_msi_domain_free_irqs apis

V3:
1. No need to add support for 2 different dev-msi irq domains, a common
   once can be used for both the cases(with IR enabled/disabled)
2. Add arch specific function to specify additions to msi_prepare callback
   instead of making the callback a weak function
3. Call platform ops directly instead of a wrapper function
4. Make mask/unmask callbacks as void functions
5. dev->msi_domain should be updated at the device driver level before
   calling dev_msi_alloc_irqs()
6. dev_msi_alloc/free_irqs() cannot be used for PCI devices
7. Followed the generic layering scheme: infrastructure bits->arch bits->enabling bits

V4:
1. Make interrupt remapping code more readable
2. Add flush writes to unmask/write and reset ims slots
3. Interrupt Message Storm-> Interrupt Message Store
4. Merge in pasid programming code.

Stage 3: Standalone dev-msi and IMS driver series
-------------------------------------------------
V1:(Changes from Stage 2 V4)
1. Split dev-msi/IMS code from Dave Jiang’s IDXD patch series
2. Set the source-id of all dev-msi interrupt requests to the parent PCI device
3. Separated core irq code from IMS related code
4. Added missing set_desc ops to the IMS msi_domain_ops
5. Added more details in the commit message-test case for auxillary interrupt data
6. Updated the copyright year from 2020 to 2021
7. Updated cover letter
8. Add platform check for subdevice irq domain (Lu Baolu):
   V1->V2:
   - V1 patches:[4]
   - Rename probably_on_bare_metal() with on_bare_metal();
   - Some vendors might use the same name for both bare metal and virtual
     environment. Before we add vendor specific code to distinguish
     between them, let's return false in on_bare_metal(). This won't
     introduce any regression. The only impact is that the coming new
     platform msi feature won't be supported until the vendor specific code
     is provided.
   V2->V3:
   - V2 patches:[5]
   - Add all identified heuristics so far

[1]: https://software.intel.com/en-us/download/intel-scalable-io-virtualization-technical-specification
[2]: https://lore.kernel.org/dmaengine/160408357912.912050.17005584526266191420.stgit@djiang5-desk3.ch.intel.com/
[3]: https://lore.kernel.org/lkml/1568338328-22458-1-git-send-email-megha.dey@linux.intel.com/
[4]: https://lore.kernel.org/linux-pci/20201210004624.345282-1-baolu.lu@linux.intel.com/
[5]: https://lore.kernel.org/linux-pci/20210106022749.2769057-1-baolu.lu@linux.intel.com/

Lu Baolu (2):
  iommu: Add capability IOMMU_CAP_VIOMMU_HINT
  platform-msi: Add platform check for subdevice irq domain

Megha Dey (2):
  genirq: Set auxiliary data for an interrupt
  iommu/vt-d: Add DEV-MSI support

Thomas Gleixner (8):
  x86/irq: Add DEV_MSI allocation type
  x86/msi: Rename and rework pci_msi_prepare() to cover non-PCI MSI
  platform-msi: Provide default irq_chip:: Ack
  genirq/proc: Take buslock on affinity write
  genirq/msi: Provide and use msi_domain_set_default_info_flags()
  platform-msi: Add device MSI infrastructure
  irqdomain/msi: Provide msi_alloc/free_store() callbacks
  irqchip: Add IMS (Interrupt Message Store) driver

 arch/x86/include/asm/hw_irq.h       |   1 +
 arch/x86/include/asm/msi.h          |   4 +-
 arch/x86/kernel/apic/msi.c          |  27 +++--
 arch/x86/pci/common.c               |  74 +++++++++++++
 drivers/base/platform-msi.c         | 141 ++++++++++++++++++++++++
 drivers/iommu/amd/iommu.c           |   2 +
 drivers/iommu/intel/iommu.c         |  20 ++++
 drivers/iommu/intel/irq_remapping.c |   6 +-
 drivers/iommu/virtio-iommu.c        |   9 ++
 drivers/irqchip/Kconfig             |  14 +++
 drivers/irqchip/Makefile            |   1 +
 drivers/irqchip/irq-ims-msi.c       | 211 ++++++++++++++++++++++++++++++++++++
 drivers/pci/controller/pci-hyperv.c |   2 +-
 drivers/pci/msi.c                   |   7 +-
 include/linux/interrupt.h           |   2 +
 include/linux/iommu.h               |   2 +
 include/linux/irq.h                 |   4 +
 include/linux/irqchip/irq-ims-msi.h |  68 ++++++++++++
 include/linux/irqdomain.h           |   1 +
 include/linux/msi.h                 |  38 +++++++
 kernel/irq/Kconfig                  |   4 +
 kernel/irq/manage.c                 |  38 ++++++-
 kernel/irq/msi.c                    |  35 ++++++
 23 files changed, 692 insertions(+), 19 deletions(-)
 create mode 100644 drivers/irqchip/irq-ims-msi.c
 create mode 100644 include/linux/irqchip/irq-ims-msi.h
```
