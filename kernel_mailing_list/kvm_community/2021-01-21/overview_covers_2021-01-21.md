

#### [PATCH v2 0/4] Handle #GP for SVM execution instructions
##### From: Wei Huang <wei.huang2@amd.com>

```c
From patchwork Thu Jan 21 06:55:04 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Wei Huang <wei.huang2@amd.com>
X-Patchwork-Id: 12034907
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-13.8 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_PATCH,
	MAILING_LIST_MULTI,MSGID_FROM_MTA_HEADER,SPF_HELO_NONE,SPF_PASS,
	USER_AGENT_GIT autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id E6BAFC433DB
	for <kvm@archiver.kernel.org>; Thu, 21 Jan 2021 06:56:43 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 9B67E23975
	for <kvm@archiver.kernel.org>; Thu, 21 Jan 2021 06:56:43 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726110AbhAUG4X (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Thu, 21 Jan 2021 01:56:23 -0500
Received: from mail-eopbgr760075.outbound.protection.outlook.com
 ([40.107.76.75]:35598
        "EHLO NAM02-CY1-obe.outbound.protection.outlook.com"
        rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org with ESMTP
        id S1725967AbhAUG4W (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 21 Jan 2021 01:56:22 -0500
ARC-Seal: i=1; a=rsa-sha256; s=arcselector9901; d=microsoft.com; cv=none;
 b=YJxWnr4i9d4oGq4ekD41KdTaeilkgkRn8+YAWkqrKOjA28CSGSa6UTIPLe7J5TvPjq1se867XwH3iT9eEAaILjKiUZJJTzIYLdgkhLfN9k5yn8G8Xs0R14l9KPl+i6oLcywdjm6FYFgFv2GcSSln+verhGom1iQBGOdG6YHnM6k91ReLv2rfMYdJAOcpbFkKcGPEOdZLkLiujQ7FtGFJ7o29rKoBGW4NokBZVXoVrmoZFkQhEihg6E7SNEfgJBXkdUxtyY+hR3VDh5j489fG8GTfkOxKZOw5gaW7bpsnTDiD9vnwwFsRYmTurcanXku0MeuJRRDPSu1voHLvGQ/d2A==
ARC-Message-Signature: i=1; a=rsa-sha256; c=relaxed/relaxed; d=microsoft.com;
 s=arcselector9901;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=3w9P9wtnZrH5H5qTUACuyi+s+gu/4vNOIShL5/IiVTE=;
 b=mJZTfrvszw6Y5NMgD7J/QA3uxex5aw+SBnPL93PNWFBAJaoYl6kLWzWB92RffUxnI5hZoTuTzNh/4ukqJ98HXN2zPaC2dMAI5lcLn4zn54gOhbgtC4Zw58ueexW3WVeJCNxHGyk+KQgCPc/i+AbxDx//RZ0nhKZ8QHQUG9EajIhleZAx5FPNyG+9nTgO2eMYKywJEnoJ0yUGLCfaLcHe9SQ0fgsVzUStWUc1sR8BHgKLuDS9gVSjddEgpEv3SAWXKhlAnZ7zaLKZG7XvLM5z5Vcjmwoys6b5y/ESQ80tCRawsEMRAx4uQT9U/nRKlt7EPZjxLazKGcOA4q1vTkkgpQ==
ARC-Authentication-Results: i=1; mx.microsoft.com 1; spf=pass
 smtp.mailfrom=amd.com; dmarc=pass action=none header.from=amd.com; dkim=pass
 header.d=amd.com; arc=none
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=amd.com; s=selector1;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=3w9P9wtnZrH5H5qTUACuyi+s+gu/4vNOIShL5/IiVTE=;
 b=myUjXX/geOyATFMIOAAaxZJ44S6Tudg8JQfaJp+fG2AnA3vZOV+EuGzYaDaRsEmNfVZurGfjxysnzxliBHL58QdZvnbCQOeHBryjQdqhlX0AoUpujeXKaRxLeENtQwPYsR+GZO/+V+d6btkLYwcVRzHRqBwln+9UVTMfKZlIVK0=
Authentication-Results: vger.kernel.org; dkim=none (message not signed)
 header.d=none;vger.kernel.org; dmarc=none action=none header.from=amd.com;
Received: from MWHPR12MB1502.namprd12.prod.outlook.com (2603:10b6:301:10::20)
 by MW3PR12MB4441.namprd12.prod.outlook.com (2603:10b6:303:59::9) with
 Microsoft SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.3784.13; Thu, 21 Jan
 2021 06:55:34 +0000
Received: from MWHPR12MB1502.namprd12.prod.outlook.com
 ([fe80::d06d:c93c:539d:5460]) by MWHPR12MB1502.namprd12.prod.outlook.com
 ([fe80::d06d:c93c:539d:5460%10]) with mapi id 15.20.3784.013; Thu, 21 Jan
 2021 06:55:34 +0000
From: Wei Huang <wei.huang2@amd.com>
To: kvm@vger.kernel.org
Cc: linux-kernel@vger.kernel.org, pbonzini@redhat.com,
        vkuznets@redhat.com, mlevitsk@redhat.com, seanjc@google.com,
        joro@8bytes.org, bp@alien8.de, tglx@linutronix.de,
        mingo@redhat.com, x86@kernel.org, jmattson@google.com,
        wanpengli@tencent.com, bsd@redhat.com, dgilbert@redhat.com,
        luto@amacapital.net, wei.huang2@amd.com
Subject: [PATCH v2 0/4] Handle #GP for SVM execution instructions
Date: Thu, 21 Jan 2021 01:55:04 -0500
Message-Id: <20210121065508.1169585-1-wei.huang2@amd.com>
X-Mailer: git-send-email 2.27.0
X-Originating-IP: [66.187.233.206]
X-ClientProxiedBy: SG2PR02CA0022.apcprd02.prod.outlook.com
 (2603:1096:3:17::34) To MWHPR12MB1502.namprd12.prod.outlook.com
 (2603:10b6:301:10::20)
MIME-Version: 1.0
X-MS-Exchange-MessageSentRepresentingType: 1
Received: from amd-daytona-06.khw1.lab.eng.bos.redhat.com (66.187.233.206) by
 SG2PR02CA0022.apcprd02.prod.outlook.com (2603:1096:3:17::34) with Microsoft
 SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.3784.12 via Frontend
 Transport; Thu, 21 Jan 2021 06:55:25 +0000
X-MS-PublicTrafficType: Email
X-MS-Office365-Filtering-HT: Tenant
X-MS-Office365-Filtering-Correlation-Id: d7fe1543-0a81-4cd8-83ab-08d8bdd98c82
X-MS-TrafficTypeDiagnostic: MW3PR12MB4441:
X-MS-Exchange-Transport-Forked: True
X-Microsoft-Antispam-PRVS: 
 <MW3PR12MB44418465380901FF6394DFF9CFA19@MW3PR12MB4441.namprd12.prod.outlook.com>
X-MS-Oob-TLC-OOBClassifiers: OLM:8273;
X-MS-Exchange-SenderADCheck: 1
X-Microsoft-Antispam: BCL:0;
X-Microsoft-Antispam-Message-Info: 
 6tk+wu/XDb4G8t1pbaJ8kJp55cdr1AlBSmiYrqwOW5Bs0hhh+uV8furbG21l0Y27l8zP1LgcW9TSkw2nUm7jv9pdQ/t72IIJZ63AkuuNw4bt/zId+/SM7TOKb9lGPHwjp6Uhwvm9ubEuKYUVpqRbawsjtXgJNRig++Ynf1w02JrxRi0J5HP5jS+S0ApPdmxDE3M9+f2sRVjOCuRf3p7m2gMYDDdihlUsbL5mKvjmMvBdi8ZJ9yBxmO0dlgRecaTw3dIgpCWrrq6v7iT2WyYRKf9v2uclkPpE7KWGU95j8h/u35GwWsSPMwrVdSlDrpCow9nNSr18okBFXfxw9CQDoT2Rsu8gJEq+NQuKXU7FaBrORUfzMj3WKHIkrbxZMm3Drf9YIWFvN5TXpjsQkls5SA==
X-Forefront-Antispam-Report: 
 CIP:255.255.255.255;CTRY:;LANG:en;SCL:1;SRV:;IPV:NLI;SFV:NSPM;H:MWHPR12MB1502.namprd12.prod.outlook.com;PTR:;CAT:NONE;SFS:(4636009)(366004)(83380400001)(52116002)(8936002)(86362001)(6506007)(66476007)(6512007)(6916009)(2906002)(186003)(498600001)(4326008)(6486002)(16526019)(956004)(26005)(2616005)(36756003)(8676002)(1076003)(6666004)(7416002)(5660300002)(66946007)(66556008);DIR:OUT;SFP:1101;
X-MS-Exchange-AntiSpam-MessageData: 
 awcnsFrCi7DSM8htXUyjh3YNVr8TdEjwDCBFN5wXes/XEpt5wKKmvgpI0o9t9KMGAJWaJU3ZSxl4t/JD+k57Io6OVIcD5AC5cN0VMGy1kB+7NMnKAnmdomk8wbCW1GHNhH4b7RSKiyFq/d1Su3C05yuiJoJu/MtRq+RwFZi5grHrg89PC3BIUMT/cXo/ZT5EmGs9Px1RCPKIK5zCzg3wc93Ae//4wT6G9hQu2TeNWb9YvUPnUJd8PH0fjtDLqTkqDTpNosCTe0xSSTAj9CSF9ojAZAHe08eLSQP15XdtxJWTYkOKJSTre5wBaOkryb12+JCK3/yrBoHJfB461vmtvAcOac0wW5lBFs1FV3KBTnInTxyty26XDPSxITGiNhxIbWyUQfbsZF/ig0bybrCizUtPZjftb1AVl3YZHbWIx3NQI6IwS1OjiQmOedxV8gcI3Y9E39yLh/iWnTG7f271X/pK/O0I7mw+sHCsDoDkSavjbCQ7fY9BezLOoUNdlU1GNcerjIk+1hHSU4XHJ0N8rWO9QM/d0+9LGpcUcLdPXf1U09ApB+fZGnFnZ8+z53JsykM53wXbH7tuotVNPw97XjGVkZpQ6e2Lu4NCXcxzo+P0gnQe87IVmy3zkIz1BbbRnBPMWQvMM3c0gTEf3lhj8pkd1jcbE2T1ggua5HlxZ3MzMaKwEQEA83IN3mh06YuWwwvc4snG+xDJIPlddpTlVUWnKwyqbRPUqNCcwz7bB0qxpFkFc+AGUrHpcjkzq5jI2md+F9xCTfpJpnY5HlUDO0EauF0a+ROeno5LpNdv50sXBc90pLLwAR6nflvRfQn9xg/Ha2iWOO1o0hipuvjsCaHZG1DxPWYM4yLlaJTL+F82uwsVnaa2t0Yuv/8klDBzzKhYNiFRzZOMJ297riiBDfKs/Y6BUMNX67tAXctOmbx0MXp0qEHWm7CIediLoCKJN+p2gHWQ2KjhhhcIlnBHHWqmEw3oY+OQv8reDrVKMim9KAuoh0+0ulQm1Hv+1hqX
X-OriginatorOrg: amd.com
X-MS-Exchange-CrossTenant-Network-Message-Id: 
 d7fe1543-0a81-4cd8-83ab-08d8bdd98c82
X-MS-Exchange-CrossTenant-AuthSource: MWHPR12MB1502.namprd12.prod.outlook.com
X-MS-Exchange-CrossTenant-AuthAs: Internal
X-MS-Exchange-CrossTenant-OriginalArrivalTime: 21 Jan 2021 06:55:33.9560
 (UTC)
X-MS-Exchange-CrossTenant-FromEntityHeader: Hosted
X-MS-Exchange-CrossTenant-Id: 3dd8961f-e488-4e60-8e11-a82d994e183d
X-MS-Exchange-CrossTenant-MailboxType: HOSTED
X-MS-Exchange-CrossTenant-UserPrincipalName: 
 NzrthFgy8HV8wzoD+FXQfzDndE+PxMcPdeIK+b4HuVV/afFa1FRPVYEsyNSaEPWp
X-MS-Exchange-Transport-CrossTenantHeadersStamped: MW3PR12MB4441
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

While running SVM related instructions (VMRUN/VMSAVE/VMLOAD), some AMD
CPUs check EAX against reserved memory regions (e.g. SMM memory on host)
before checking VMCB's instruction intercept. If EAX falls into such
memory areas, #GP is triggered before #VMEXIT. This causes unexpected #GP
under nested virtualization. To solve this problem, this patchset makes
KVM trap #GP and emulate these SVM instuctions accordingly.

Also newer AMD CPUs will change this behavior by triggering #VMEXIT
before #GP. This change is indicated by CPUID_0x8000000A_EDX[28]. Under
this circumstance, #GP interception is not required. This patchset supports
the new feature.

This patchset has been verified with vmrun_errata_test and vmware_backdoors
tests of kvm_unit_test on the following configs:
  * Current CPU: nested, nested on nested
  * New CPU with X86_FEATURE_SVME_ADDR_CHK: nested, nested on nested

v1->v2:
  * Factor out instruction decode for sharing
  * Re-org gp_interception() handling for both #GP and vmware_backdoor
  * Use kvm_cpu_cap for X86_FEATURE_SVME_ADDR_CHK feature support
  * Add nested on nested support

Thanks,
-Wei

Wei Huang (4):
  KVM: x86: Factor out x86 instruction emulation with decoding
  KVM: SVM: Add emulation support for #GP triggered by SVM instructions
  KVM: SVM: Add support for VMCB address check change
  KVM: SVM: Support #GP handling for the case of nested on nested

 arch/x86/include/asm/cpufeatures.h |   1 +
 arch/x86/kvm/svm/svm.c             | 120 ++++++++++++++++++++++++-----
 arch/x86/kvm/x86.c                 |  63 +++++++++------
 arch/x86/kvm/x86.h                 |   2 +
 4 files changed, 145 insertions(+), 41 deletions(-)
```
#### [kvm-unit-tests PATCH v4 0/3] s390x: css: pv: css test adaptation for
##### From: Pierre Morel <pmorel@linux.ibm.com>

```c
From patchwork Thu Jan 21 09:13:09 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Pierre Morel <pmorel@linux.ibm.com>
X-Patchwork-Id: 12035339
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-11.8 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_PATCH,MAILING_LIST_MULTI,
	SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT autolearn=ham autolearn_force=no
	version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 31BE6C433E0
	for <kvm@archiver.kernel.org>; Thu, 21 Jan 2021 09:20:48 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id DC34D2395A
	for <kvm@archiver.kernel.org>; Thu, 21 Jan 2021 09:20:45 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728533AbhAUJUT (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Thu, 21 Jan 2021 04:20:19 -0500
Received: from mx0a-001b2d01.pphosted.com ([148.163.156.1]:30696 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1728502AbhAUJOO (ORCPT
        <rfc822;kvm@vger.kernel.org>); Thu, 21 Jan 2021 04:14:14 -0500
Received: from pps.filterd (m0187473.ppops.net [127.0.0.1])
        by mx0a-001b2d01.pphosted.com (8.16.0.42/8.16.0.42) with SMTP id
 10L91lM9055296;
        Thu, 21 Jan 2021 04:13:20 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=ibm.com;
 h=from : to : cc : subject
 : date : message-id; s=pp1;
 bh=FT6aVVT/EIDQ2qhbr6PLGxD5HMtkOfxnITx0veMWTeo=;
 b=dKJg0o79XyIdT4+MWY8oY6P4uulwkNK4f6xL61lJHAUIZZLORV4MRkCAbklUliLVMNJB
 wrjb4xhl1QFHnpLxcP7ij9P7SR3W/W9yd7XCEqGpsHxIeAtgCdfdXp0RpKalZB6jURNs
 rNstMyfpFM/W2qSrXPHy9Pbv0KUetiCvK/3D34YWfrXyiFeiPUCtKJuLVOEEUereirbP
 ZrhgUu2ptvMdCZKTWRWeqQiEXFDNAhuhXtoBpy2djpCTlXCoblXQVuihwq1zu+cxUnwH
 bOdQsWoJHElVjMRpLXvtGDXsexD8p5gUX1Du6pJvSzEUVJtU/h4LfZ8yxjCaLQOEwUEw Gw==
Received: from pps.reinject (localhost [127.0.0.1])
        by mx0a-001b2d01.pphosted.com with ESMTP id 3675ychcbb-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Thu, 21 Jan 2021 04:13:20 -0500
Received: from m0187473.ppops.net (m0187473.ppops.net [127.0.0.1])
        by pps.reinject (8.16.0.36/8.16.0.36) with SMTP id 10L91q4r055554;
        Thu, 21 Jan 2021 04:13:20 -0500
Received: from ppma03ams.nl.ibm.com (62.31.33a9.ip4.static.sl-reverse.com
 [169.51.49.98])
        by mx0a-001b2d01.pphosted.com with ESMTP id 3675ychca9-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Thu, 21 Jan 2021 04:13:19 -0500
Received: from pps.filterd (ppma03ams.nl.ibm.com [127.0.0.1])
        by ppma03ams.nl.ibm.com (8.16.0.42/8.16.0.42) with SMTP id
 10L984bG031640;
        Thu, 21 Jan 2021 09:13:17 GMT
Received: from b06cxnps3075.portsmouth.uk.ibm.com
 (d06relay10.portsmouth.uk.ibm.com [9.149.109.195])
        by ppma03ams.nl.ibm.com with ESMTP id 3668pasfu9-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Thu, 21 Jan 2021 09:13:17 +0000
Received: from d06av24.portsmouth.uk.ibm.com (mk.ibm.com [9.149.105.60])
        by b06cxnps3075.portsmouth.uk.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id 10L9DEO750528732
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Thu, 21 Jan 2021 09:13:14 GMT
Received: from d06av24.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 9FE984203F;
        Thu, 21 Jan 2021 09:13:14 +0000 (GMT)
Received: from d06av24.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 299A842047;
        Thu, 21 Jan 2021 09:13:14 +0000 (GMT)
Received: from oc3016276355.ibm.com (unknown [9.145.36.14])
        by d06av24.portsmouth.uk.ibm.com (Postfix) with ESMTP;
        Thu, 21 Jan 2021 09:13:14 +0000 (GMT)
From: Pierre Morel <pmorel@linux.ibm.com>
To: kvm@vger.kernel.org
Cc: linux-s390@vger.kernel.org, frankja@linux.ibm.com,
        david@redhat.com, thuth@redhat.com, cohuck@redhat.com,
        imbrenda@linux.ibm.com, drjones@redhat.com, pbonzini@redhat.com
Subject: [kvm-unit-tests PATCH v4 0/3] s390x: css: pv: css test adaptation for
 PV
Date: Thu, 21 Jan 2021 10:13:09 +0100
Message-Id: <1611220392-22628-1-git-send-email-pmorel@linux.ibm.com>
X-Mailer: git-send-email 1.8.3.1
X-TM-AS-GCONF: 00
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.343,18.0.737
 definitions=2021-01-21_03:2021-01-20,2021-01-21 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 spamscore=0 mlxlogscore=999
 adultscore=0 priorityscore=1501 bulkscore=0 impostorscore=0 suspectscore=0
 phishscore=0 lowpriorityscore=0 mlxscore=0 malwarescore=0 clxscore=1015
 classifier=spam adjust=0 reason=mlx scancount=1 engine=8.12.0-2009150000
 definitions=main-2101210045
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Hi all,

To adapt the CSS I/O tests to protected virtualisation we need
utilities to:

1- allocate the I/O buffers in a private page using (patch 2)
   It must be in a dedicated page to avoid exporting code or
   guest private data to the host.
   We accept a size in byte and flags and allocate page integral
   memory to handle the Protected Virtualization.

2- share the I/O buffers with the host (patch 1)
   This patch uses the page allocator reworked by Claudio.

The 2 first patches are the implementation of the tools,
patch 3 is the modification of the css.c test for PV.

The checkpatch always asked me to modify MAINTAINERS,
so I added me as reviewer to be in copy for CSS at least.
May be we could create a finer grain MAINTAINERS in the
future.

regards,
Pierre

Pierre Morel (3):
  s390x: pv: implement routine to share/unshare memory
  s390x: define UV compatible I/O allocation
  s390x: css: pv: css test adaptation for PV

 MAINTAINERS           |  1 +
 lib/s390x/asm/uv.h    | 38 +++++++++++++++++++++++
 lib/s390x/css.h       |  3 +-
 lib/s390x/css_lib.c   | 28 +++++------------
 lib/s390x/malloc_io.c | 70 +++++++++++++++++++++++++++++++++++++++++++
 lib/s390x/malloc_io.h | 45 ++++++++++++++++++++++++++++
 s390x/Makefile        |  1 +
 s390x/css.c           | 43 ++++++++++++++++++--------
 8 files changed, 195 insertions(+), 34 deletions(-)
 create mode 100644 lib/s390x/malloc_io.c
 create mode 100644 lib/s390x/malloc_io.h
```
#### [kvm-unit-tests PATCH v1 0/2] Fix smap and pku tests for new
##### From: Claudio Imbrenda <imbrenda@linux.ibm.com>

```c
From patchwork Thu Jan 21 11:18:06 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Claudio Imbrenda <imbrenda@linux.ibm.com>
X-Patchwork-Id: 12035759
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-11.8 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_PATCH,MAILING_LIST_MULTI,
	SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT autolearn=ham autolearn_force=no
	version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id D0990C433DB
	for <kvm@archiver.kernel.org>; Thu, 21 Jan 2021 11:59:44 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 89A2F2395B
	for <kvm@archiver.kernel.org>; Thu, 21 Jan 2021 11:59:44 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728760AbhAULUW (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Thu, 21 Jan 2021 06:20:22 -0500
Received: from mx0b-001b2d01.pphosted.com ([148.163.158.5]:39272 "EHLO
        mx0b-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1728116AbhAULTN (ORCPT
        <rfc822;kvm@vger.kernel.org>); Thu, 21 Jan 2021 06:19:13 -0500
Received: from pps.filterd (m0098417.ppops.net [127.0.0.1])
        by mx0a-001b2d01.pphosted.com (8.16.0.42/8.16.0.42) with SMTP id
 10LB2Tg1169325;
        Thu, 21 Jan 2021 06:18:25 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=ibm.com;
 h=from : to : cc : subject
 : date : message-id : mime-version : content-transfer-encoding; s=pp1;
 bh=n24oxlG++EA7+3fDUlpmfDXsrTtil7ul85RWh/Lqbes=;
 b=jfHwG8RhDz3gi2ACVrQErbr132BB1DdF02um3+72jNCQpXxJpmLGCZYewmCuG8UQoTy/
 Wj0TH5jFRem6GNJNNdXpk7sk93dIHVvG6hiImHEEmyKJh30IbYX4YqSIlLMwMPMElKCF
 BPTX6CpW9713u6lrETlGvS0XzGsX4HsA0PAIr0/uOrMDoESH4KXOgh3VDwCvGrilqy6Z
 3OjOMWzsMxDWQXExThJObWf4XT1tm1btlq/VW8SHNDMtXV8Jh1ltAtBR9bJ26PCyEf2V
 XLf6Nk2O0o7LEp2zTxpiQJZIihqeIZB9StmX0Jsg23JJ/0mAjB/UTT2hpQqf+OkyRApF Kg==
Received: from pps.reinject (localhost [127.0.0.1])
        by mx0a-001b2d01.pphosted.com with ESMTP id 3677nna12g-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Thu, 21 Jan 2021 06:18:24 -0500
Received: from m0098417.ppops.net (m0098417.ppops.net [127.0.0.1])
        by pps.reinject (8.16.0.36/8.16.0.36) with SMTP id 10LB5c2i183717;
        Thu, 21 Jan 2021 06:18:24 -0500
Received: from ppma04ams.nl.ibm.com (63.31.33a9.ip4.static.sl-reverse.com
 [169.51.49.99])
        by mx0a-001b2d01.pphosted.com with ESMTP id 3677nna11d-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Thu, 21 Jan 2021 06:18:24 -0500
Received: from pps.filterd (ppma04ams.nl.ibm.com [127.0.0.1])
        by ppma04ams.nl.ibm.com (8.16.0.42/8.16.0.42) with SMTP id
 10LBHadO013053;
        Thu, 21 Jan 2021 11:18:22 GMT
Received: from b06avi18626390.portsmouth.uk.ibm.com
 (b06avi18626390.portsmouth.uk.ibm.com [9.149.26.192])
        by ppma04ams.nl.ibm.com with ESMTP id 3668p0sk5f-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Thu, 21 Jan 2021 11:18:22 +0000
Received: from d06av26.portsmouth.uk.ibm.com (d06av26.portsmouth.uk.ibm.com
 [9.149.105.62])
        by b06avi18626390.portsmouth.uk.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id 10LBIDvE35389700
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Thu, 21 Jan 2021 11:18:13 GMT
Received: from d06av26.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id CADD2AE058;
        Thu, 21 Jan 2021 11:18:19 +0000 (GMT)
Received: from d06av26.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 4B316AE051;
        Thu, 21 Jan 2021 11:18:19 +0000 (GMT)
Received: from ibm-vm.ibmuc.com (unknown [9.145.4.167])
        by d06av26.portsmouth.uk.ibm.com (Postfix) with ESMTP;
        Thu, 21 Jan 2021 11:18:19 +0000 (GMT)
From: Claudio Imbrenda <imbrenda@linux.ibm.com>
To: kvm@vger.kernel.org
Cc: pbonzini@redhat.com, david@redhat.com, thuth@redhat.com,
        frankja@linux.ibm.com, cohuck@redhat.com, lvivier@redhat.com,
        nadav.amit@gmail.com, krish.sadhukhan@oracle.com,
        dmatlack@google.com, seanjc@google.com
Subject: [kvm-unit-tests PATCH v1 0/2] Fix smap and pku tests for new
 allocator
Date: Thu, 21 Jan 2021 12:18:06 +0100
Message-Id: <20210121111808.619347-1-imbrenda@linux.ibm.com>
X-Mailer: git-send-email 2.26.2
MIME-Version: 1.0
X-TM-AS-GCONF: 00
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.343,18.0.737
 definitions=2021-01-21_04:2021-01-21,2021-01-21 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 phishscore=0 mlxlogscore=999
 lowpriorityscore=0 priorityscore=1501 suspectscore=0 bulkscore=0
 malwarescore=0 adultscore=0 spamscore=0 clxscore=1015 mlxscore=0
 impostorscore=0 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.12.0-2009150000 definitions=main-2101210056
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The recent fixes to the page allocator broke the SMAP test.

The reason is that the test blindly took a chunk of memory and used it,
hoping that the page allocator would not touch it.

Unfortunately the memory area affected is exactly where the new
allocator puts the metadata information for the 16M-4G memory area.

This causes the SMAP test to fail.

The solution is to reserve the memory properly using the reserve_pages
function. To make things simpler, the memory area reserved is now
8M-16M instead of 16M-32M.

This issue was not found immediately, because the SMAP test needs
non-default qemu parameters in order not to be skipped.

I tested the patch and it seems to work.

While fixing the SMAP test, I also noticed that the PKU test was doing
the same thing, so I went ahead and fixed that test too in the same
way. Unfortunately I do not have the right hardware and therefore I
cannot test it.



I would really appreciate if someone who has the right hardware could
test the PKU test and see if it works.




Claudio Imbrenda (2):
  x86: smap: fix the test to work with new allocator
  x86: pku: fix the test to work with new allocator

 x86/pku.c  | 5 ++++-
 x86/smap.c | 9 ++++++---
 2 files changed, 10 insertions(+), 4 deletions(-)
```
#### [PATCH v2 0/2] s390: uv: small UV fixes
##### From: Janosch Frank <frankja@linux.ibm.com>

```c
From patchwork Thu Jan 21 15:14:33 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Janosch Frank <frankja@linux.ibm.com>
X-Patchwork-Id: 12036591
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-11.8 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_PATCH,MAILING_LIST_MULTI,
	SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT autolearn=ham autolearn_force=no
	version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 20968C433DB
	for <kvm@archiver.kernel.org>; Thu, 21 Jan 2021 15:18:38 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id D1F3F23A1E
	for <kvm@archiver.kernel.org>; Thu, 21 Jan 2021 15:18:37 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1732764AbhAUPSK (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Thu, 21 Jan 2021 10:18:10 -0500
Received: from mx0b-001b2d01.pphosted.com ([148.163.158.5]:21334 "EHLO
        mx0b-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1732666AbhAUPPr (ORCPT
        <rfc822;kvm@vger.kernel.org>); Thu, 21 Jan 2021 10:15:47 -0500
Received: from pps.filterd (m0098421.ppops.net [127.0.0.1])
        by mx0a-001b2d01.pphosted.com (8.16.0.42/8.16.0.42) with SMTP id
 10LFBfZX172422;
        Thu, 21 Jan 2021 10:15:03 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=ibm.com;
 h=from : to : cc : subject
 : date : message-id : mime-version : content-transfer-encoding; s=pp1;
 bh=ODDEjf45lSiu/+GG5Htm9GDO/8ZGKF2Y5B09yaOS7KY=;
 b=d2uRWzOJRIfI+5I6y1qFg+PyF1E3CxBis3XzXNIZhQiFW1nI4jwNXnImk5sPExFhCL3L
 1qqwz7jkspmLmErn1ClNrAnoaBqftpxZbW2S4zLiSjbRniRc3038XHZeTj3ivRHRU9d3
 jRnne1lYBoCtWMxGrC3fi6Wz3QsBm5GkTQ9qkpz263FFDOlT/UHf7ytOItMPXtP6JJ7Q
 g56XE1lyqN78iG+7FIoMTuaB9c86zf3DhIkaH9kgToEkOtdPpahfPVlivMBDrzGqP/U3
 UYJ1O0Hil9qkpLZul5O7MNwBB1l2d4VB+yEg4OKld8YlmVwsrYb3YtSEi1vdRxhgyFJT KA==
Received: from pps.reinject (localhost [127.0.0.1])
        by mx0a-001b2d01.pphosted.com with ESMTP id 367c1pr4h3-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Thu, 21 Jan 2021 10:15:03 -0500
Received: from m0098421.ppops.net (m0098421.ppops.net [127.0.0.1])
        by pps.reinject (8.16.0.36/8.16.0.36) with SMTP id 10LFBp3Q173000;
        Thu, 21 Jan 2021 10:15:03 -0500
Received: from ppma03ams.nl.ibm.com (62.31.33a9.ip4.static.sl-reverse.com
 [169.51.49.98])
        by mx0a-001b2d01.pphosted.com with ESMTP id 367c1pr4g7-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Thu, 21 Jan 2021 10:15:03 -0500
Received: from pps.filterd (ppma03ams.nl.ibm.com [127.0.0.1])
        by ppma03ams.nl.ibm.com (8.16.0.42/8.16.0.42) with SMTP id
 10LFDVOp002522;
        Thu, 21 Jan 2021 15:15:01 GMT
Received: from b06cxnps3075.portsmouth.uk.ibm.com
 (d06relay10.portsmouth.uk.ibm.com [9.149.109.195])
        by ppma03ams.nl.ibm.com with ESMTP id 3668pass62-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Thu, 21 Jan 2021 15:15:01 +0000
Received: from d06av25.portsmouth.uk.ibm.com (d06av25.portsmouth.uk.ibm.com
 [9.149.105.61])
        by b06cxnps3075.portsmouth.uk.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id 10LFEwdG47710466
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Thu, 21 Jan 2021 15:14:58 GMT
Received: from d06av25.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id A90F311C058;
        Thu, 21 Jan 2021 15:14:58 +0000 (GMT)
Received: from d06av25.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 8DBF411C050;
        Thu, 21 Jan 2021 15:14:57 +0000 (GMT)
Received: from linux01.pok.stglabs.ibm.com (unknown [9.114.17.81])
        by d06av25.portsmouth.uk.ibm.com (Postfix) with ESMTP;
        Thu, 21 Jan 2021 15:14:57 +0000 (GMT)
From: Janosch Frank <frankja@linux.ibm.com>
To: linux-kernel@vger.kernel.org
Cc: kvm@vger.kernel.org, thuth@redhat.com, david@redhat.com,
        borntraeger@de.ibm.com, imbrenda@linux.ibm.com, cohuck@redhat.com,
        linux-s390@vger.kernel.org, gor@linux.ibm.com, hca@linux.ibm.com,
        mihajlov@linux.ibm.com
Subject: [PATCH v2 0/2] s390: uv: small UV fixes
Date: Thu, 21 Jan 2021 10:14:33 -0500
Message-Id: <20210121151436.417240-1-frankja@linux.ibm.com>
X-Mailer: git-send-email 2.25.1
MIME-Version: 1.0
X-TM-AS-GCONF: 00
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.343,18.0.737
 definitions=2021-01-21_08:2021-01-21,2021-01-21 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 malwarescore=0
 impostorscore=0 phishscore=0 lowpriorityscore=0 adultscore=0
 mlxlogscore=860 suspectscore=0 priorityscore=1501 spamscore=0 bulkscore=0
 mlxscore=0 clxscore=1015 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.12.0-2009150000 definitions=main-2101210081
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Two small fixes:
    * Handle 3d PGMs where the address space id is not known
    * Clean up the UV query VCPU number field naming (it's N-1 not N as number in this context means ID)

v2:
	* Renamed the struct member from max_guest_cpu to max_guest_cpu_id
	* Improved a comment text

Janosch Frank (2):
  s390: uv: Fix sysfs max number of VCPUs reporting
  s390: mm: Fix secure storage access exception handling

 arch/s390/boot/uv.c        |  2 +-
 arch/s390/include/asm/uv.h |  4 ++--
 arch/s390/kernel/uv.c      |  2 +-
 arch/s390/mm/fault.c       | 14 ++++++++++++++
 4 files changed, 18 insertions(+), 4 deletions(-)
```
#### [PATCH 0/2] VMX: few tracing improvements
##### From: Maxim Levitsky <mlevitsk@redhat.com>

```c
From patchwork Thu Jan 21 17:10:41 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Maxim Levitsky <mlevitsk@redhat.com>
X-Patchwork-Id: 12037241
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-10.9 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS
	autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 2E996C433E9
	for <kvm@archiver.kernel.org>; Thu, 21 Jan 2021 17:28:35 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id DEB8B207C5
	for <kvm@archiver.kernel.org>; Thu, 21 Jan 2021 17:28:34 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2388574AbhAUROC (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Thu, 21 Jan 2021 12:14:02 -0500
Received: from us-smtp-delivery-124.mimecast.com ([216.205.24.124]:29120 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S2388531AbhAURMV (ORCPT
        <rfc822;kvm@vger.kernel.org>); Thu, 21 Jan 2021 12:12:21 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1611249055;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=gj145NXZKVxVx1ghR0FfUZ22hzpc5dsaWCMQogr6chs=;
        b=aYCm4P9R0XKY0cPZFeR8hfqPjhiQqqXdatZ8O/csKtKNNhVvRQj1lfsD8ecbhAeGDKMRg2
        byjwEOd036/3TEr4FJ6EBlrc7IWALomPbWfldR1VeMiS3skGYlBMmozalGtJUUk3UzRMC+
        N8sN8V+a8WB6DY4o63ND1MrCE9H0hrw=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-593-Dyxws2CMMhWBvLUgMr6g5Q-1; Thu, 21 Jan 2021 12:10:54 -0500
X-MC-Unique: Dyxws2CMMhWBvLUgMr6g5Q-1
Received: from smtp.corp.redhat.com (int-mx03.intmail.prod.int.phx2.redhat.com
 [10.5.11.13])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 624EC1005504;
        Thu, 21 Jan 2021 17:10:52 +0000 (UTC)
Received: from localhost.localdomain (unknown [10.35.206.32])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 28CB1648A8;
        Thu, 21 Jan 2021 17:10:44 +0000 (UTC)
From: Maxim Levitsky <mlevitsk@redhat.com>
To: kvm@vger.kernel.org
Cc: Borislav Petkov <bp@alien8.de>,
        Paolo Bonzini <pbonzini@redhat.com>, x86@kernel.org,
        Wanpeng Li <wanpengli@tencent.com>,
        linux-kernel@vger.kernel.org,
        Sean Christopherson <seanjc@google.com>,
        Jim Mattson <jmattson@google.com>,
        Thomas Gleixner <tglx@linutronix.de>,
        Ingo Molnar <mingo@redhat.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        "H. Peter Anvin" <hpa@zytor.com>, Joerg Roedel <joro@8bytes.org>,
        Maxim Levitsky <mlevitsk@redhat.com>
Subject: [PATCH 0/2] VMX: few tracing improvements
Date: Thu, 21 Jan 2021 19:10:41 +0200
Message-Id: <20210121171043.946761-1-mlevitsk@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.13
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Since the fix for the bug in nested migration on VMX is
already merged by Paulo, those are the remaining
patches in this series.

I added a new patch to trace SVM nested entries from
SMM and nested state load as well.

Best regards,
	Maxim Levitsky

Maxim Levitsky (2):
  KVM: nSVM: move nested vmrun tracepoint to enter_svm_guest_mode
  KVM: nVMX: trace nested vm entry

 arch/x86/kvm/svm/nested.c | 26 ++++++++++++++------------
 arch/x86/kvm/trace.h      | 30 ++++++++++++++++++++++++++++++
 arch/x86/kvm/vmx/nested.c |  5 +++++
 arch/x86/kvm/x86.c        |  3 ++-
 4 files changed, 51 insertions(+), 13 deletions(-)
```
