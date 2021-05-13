

#### [PATCH 0/3] KVM: nVMX: Add more statistics to KVM debugfs
##### From: Krish Sadhukhan <krish.sadhukhan@oracle.com>

```c
From patchwork Wed May 12 01:47:56 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Krish Sadhukhan <krish.sadhukhan@oracle.com>
X-Patchwork-Id: 12252611
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-13.8 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_PATCH,
	MAILING_LIST_MULTI,MSGID_FROM_MTA_HEADER,SPF_HELO_NONE,SPF_PASS,
	USER_AGENT_GIT autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 89451C433ED
	for <kvm@archiver.kernel.org>; Wed, 12 May 2021 03:24:59 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 5B7BD61370
	for <kvm@archiver.kernel.org>; Wed, 12 May 2021 03:24:59 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S229954AbhELD0F (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 11 May 2021 23:26:05 -0400
Received: from aserp2130.oracle.com ([141.146.126.79]:40840 "EHLO
        aserp2130.oracle.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S229952AbhELD0F (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 11 May 2021 23:26:05 -0400
Received: from pps.filterd (aserp2130.oracle.com [127.0.0.1])
        by aserp2130.oracle.com (8.16.0.42/8.16.0.42) with SMTP id
 14C2XxdX028871;
        Wed, 12 May 2021 02:37:12 GMT
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=oracle.com;
 h=from : to : cc :
 subject : date : message-id : content-transfer-encoding : content-type :
 mime-version; s=corp-2020-01-29;
 bh=e2OgJs9zkD3bdfBUJOGrX6JlstCQGxu71rDiqyS9tWE=;
 b=j51ExzRv9shmTFIMoyKH7MTj36o5mhk/2tCov0MiVFaTTLFR6eX3JBwGHJGy246+roUj
 +VLZdm4/T1GAH8cRWdXbWxcDQXgUei4nXy4SVuPA4IHsrJBY0Gju7YBaCr5HjBEBK5cs
 VFbkRamXqMMkcRnmbHTzt4Xb0wK08fXX+pcEVzT1aqvxN5nEHP1228hCEZl9LukZ35lU
 UmXWB/3c2m8Qt2lY816rPSL9olGWxf2VyGveb6g//L1LBSawO1tPL3Yo3bkhWrfhG2O0
 LxDXld+FcsSqxa9JaDUIAdQEJ9H82IcB3tvXABeEbHmix+ppBJrsjg5itpCDsip6iMh2 JQ==
Received: from aserp3020.oracle.com (aserp3020.oracle.com [141.146.126.70])
        by aserp2130.oracle.com with ESMTP id 38dg5bgrn4-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Wed, 12 May 2021 02:37:12 +0000
Received: from pps.filterd (aserp3020.oracle.com [127.0.0.1])
        by aserp3020.oracle.com (8.16.0.42/8.16.0.42) with SMTP id
 14C2YgI3168780;
        Wed, 12 May 2021 02:37:12 GMT
Received: from nam12-bn8-obe.outbound.protection.outlook.com
 (mail-bn8nam12lp2176.outbound.protection.outlook.com [104.47.55.176])
        by aserp3020.oracle.com with ESMTP id 38djfadpax-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Wed, 12 May 2021 02:37:12 +0000
ARC-Seal: i=1; a=rsa-sha256; s=arcselector9901; d=microsoft.com; cv=none;
 b=g0EqiXrVlgh47+RKwXoZflKgZQnnDbG9qeKnwWHF80P39P057c5uKe7+XQAaSf9gelEXBY+3U73LYijXrAfH0TQQMj2a96OPiBtX/eTCVe2ADh/TAoFAYtunJglOVr4T5JJ8ZVhBm4NYUxrRrQyZzndP3P+dH+XpQNUz8RWF7ADWn3w55js4HNLFjaatOY9dmKCPygL/SIjcB2ihVTwB/WWg2uFgiirjwp13r0TAxlIHcbHWzuCPTfCP8xEterSimuZIVhRAWGoesR0dYMYZJerPIUOuV3drhA24xMopmI5jR/6QscO4fy7wvtR6tsBMhCtf5vJy1zzx/zCES9EJwA==
ARC-Message-Signature: i=1; a=rsa-sha256; c=relaxed/relaxed; d=microsoft.com;
 s=arcselector9901;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=e2OgJs9zkD3bdfBUJOGrX6JlstCQGxu71rDiqyS9tWE=;
 b=aACWvvO5dsQQ9TRLdVhDbYjFWSUVyjRqQE/jeC50dYHAea/HD4DF4/8QxQZxXJWua77qcaaj5M+xAeQtkVd4n5O0KMPwk54jlcyFidz4XuMbSeXGg/FHsJgC+9Cudue6JIpy/Bwpp+Rob9Yq1KHzzer8NtfMjMqYYr8M+i5rruBwuEje8KCTzcyqbeW2kApYWLemEFB3W2bCDg4+6IgB6DWKJbesgdhW6uCh9GWVSD5CSOvwfIXJPtlccL7tOWBLfd3HNJGiBJcuUWn5mbn+AD4PUKemxhjJse8uR4V31NjWeOsQcNUFvZioE/VZmiVVUc30hCsONVeQ2pt/pEopxA==
ARC-Authentication-Results: i=1; mx.microsoft.com 1; spf=pass
 smtp.mailfrom=oracle.com; dmarc=pass action=none header.from=oracle.com;
 dkim=pass header.d=oracle.com; arc=none
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
 d=oracle.onmicrosoft.com; s=selector2-oracle-onmicrosoft-com;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=e2OgJs9zkD3bdfBUJOGrX6JlstCQGxu71rDiqyS9tWE=;
 b=y+BzEAj/1+fTkhKv/Dqq4oFOiSITBntFwqhPG+pu9OIz+3PZKQuIEdLs7NdXtk01OJ1fnjA+Vu2TX7HDWogV+JHBaQ6qbFdEZJyh4mEV5ZHud6V9k9RfKo0oKLPKgUOCDrxc7NEEywuRi+ZI+GRGz22NKxuzUDIYe3Pq+baO84E=
Authentication-Results: vger.kernel.org; dkim=none (message not signed)
 header.d=none;vger.kernel.org; dmarc=none action=none header.from=oracle.com;
Received: from SN6PR10MB3021.namprd10.prod.outlook.com (2603:10b6:805:cc::19)
 by SA2PR10MB4425.namprd10.prod.outlook.com (2603:10b6:806:11b::9) with
 Microsoft SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.4129.26; Wed, 12 May
 2021 02:37:10 +0000
Received: from SN6PR10MB3021.namprd10.prod.outlook.com
 ([fe80::5911:9489:e05c:2d44]) by SN6PR10MB3021.namprd10.prod.outlook.com
 ([fe80::5911:9489:e05c:2d44%5]) with mapi id 15.20.4108.031; Wed, 12 May 2021
 02:37:10 +0000
From: Krish Sadhukhan <krish.sadhukhan@oracle.com>
To: kvm@vger.kernel.org
Cc: pbonzini@redhat.com, jmattson@google.com, seanjc@google.com
Subject: [PATCH 0/3] KVM: nVMX: Add more statistics to KVM debugfs
Date: Tue, 11 May 2021 21:47:56 -0400
Message-Id: <20210512014759.55556-1-krish.sadhukhan@oracle.com>
X-Mailer: git-send-email 2.25.4
X-Originating-IP: [138.3.201.29]
X-ClientProxiedBy: BY5PR03CA0016.namprd03.prod.outlook.com
 (2603:10b6:a03:1e0::26) To SN6PR10MB3021.namprd10.prod.outlook.com
 (2603:10b6:805:cc::19)
MIME-Version: 1.0
X-MS-Exchange-MessageSentRepresentingType: 1
Received: from ban25x6uut29.us.oracle.com (138.3.201.29) by
 BY5PR03CA0016.namprd03.prod.outlook.com (2603:10b6:a03:1e0::26) with
 Microsoft SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.4108.25 via Frontend
 Transport; Wed, 12 May 2021 02:37:09 +0000
X-MS-PublicTrafficType: Email
X-MS-Office365-Filtering-Correlation-Id: 08c9dec8-62f3-4aae-6552-08d914eed771
X-MS-TrafficTypeDiagnostic: SA2PR10MB4425:
X-Microsoft-Antispam-PRVS: 
 <SA2PR10MB4425BB03574F1EDD307DCBD181529@SA2PR10MB4425.namprd10.prod.outlook.com>
X-MS-Oob-TLC-OOBClassifiers: OLM:5516;
X-MS-Exchange-SenderADCheck: 1
X-Microsoft-Antispam: BCL:0;
X-Microsoft-Antispam-Message-Info: 
 XG9L1sbBSS2An126nBGzdNXuHvAbczb4Fj+pPPJdnwR3Np84SXIEhxfL+mqKMr3kLLAPUxVM4FrsJvCAVootItheIFvP8DdfPmOmpEfQI51vocFKhSwLZUDtmF0EfUkzF33hD2SB04b3agPUAAGuhfzQR84FtkeOEx/t4RAq7Ce5YuPOumZekPZSdGnFQE/HOHuHJHGDkbnVmCGYCyI3m4wjczIas0Y+OYYViop/R6cTD7PHjyoi7HiVm/M+d0D3bhge038UTie5bunfAP1CAsucmBqQy8ZdbZOOWCtHq5y115PSfWE9kdAko+Icv1kOWsJ0/DAaAb8se4q3Bt+O4nt5+Iafa+4Vi3hc5aPZaii6j3IBuWWTXWKVqslbViODbHjASKsfdhP0m/gUSSqvilQU3YX3pkAwS94vaAkE5b4pE7RA0QoXZFO6jlzmAh01XEFWPmKO8CFlEsYde3OAkP5b/fsYAiz1226wNHGT+a1KF5E04JH2x+wlmlKhZGQyvuqBxQC+zr3RPm3sonRVraFuMAlnVU7CN0tLcMol7uttljY07YANFDaZdGcwxZCf72ZY8q4A8bgRRPG3+Gr1XHrWHbNbr75HCIzst9MP3OBQqw2xpYjVF3vu9BFbleLxQ9ecH/GgD6IT6LbbcWeSoA==
X-Forefront-Antispam-Report: 
 CIP:255.255.255.255;CTRY:;LANG:en;SCL:1;SRV:;IPV:NLI;SFV:NSPM;H:SN6PR10MB3021.namprd10.prod.outlook.com;PTR:;CAT:NONE;SFS:(346002)(136003)(39860400002)(366004)(396003)(376002)(66946007)(8936002)(66556008)(478600001)(6486002)(2906002)(1076003)(36756003)(5660300002)(4744005)(83380400001)(186003)(16526019)(66476007)(316002)(86362001)(6666004)(52116002)(38100700002)(8676002)(26005)(4326008)(38350700002)(6916009)(2616005)(44832011)(7696005)(956004);DIR:OUT;SFP:1101;
X-MS-Exchange-AntiSpam-MessageData: 
 eSB6PsYAY/25ZIlu+iSOgxaXgOgUWPWCYQw4COBhjFkN6L4FuKax2vF4jLo245XMRJG5HbPX0z8CW60Ym0YgrDVbJz/Lwr8AjmXhRhTyu5Vkty6PAR8JKUz1k006RnlT+DJ8TQEhhyA3fY80dk93xrVl3djZvOxiKvRgrrJDiWOaY4CpUenFRIge11UrAQs/CnfeOwGOoI4x/pNomlaWf2GMaPmwxJnYTbna5MlHxEF61H48CtkExCdt0Ln2U1PFjyXh7sLduai6SMI/Aocln023WLm8Ye/JaCMHFaDYTuiaiJb1dzthFbaxO4NFJRwFXTA8d66+jSU7MrYksTZDwJA1yTy8xR9fy9/PrxPh5pG/Fnwzl4n0DgKlh0DQF5csUTh1FcDxYZqKUl3n3IpgANbHGWwKzMRtpWjDoxH6/dywb8z3qGh+2JBNjsN/r6XufUklLVJXEfx1I6+6SEfl3BgfaNvUkAkO4tCS1ndhVvNYQ8fxfUi8AAfd3qlv9nlhwcrmSQ7w31kj2cWG4jwcJTxopa+sCVltXfxNaagBEoC5/DzLqlSn5WRTLD7NBZYsY9XCZTuRapyhirKKAE48Jz1o3PNo+yZQDuWAP2YnQfYvvtIIW+QlCcEuMN3nRv2t4ZPW7NsdhyIGMeYR0hkoQsWru29GcHh3U8ZsY/Ijo5+aFwdJbTgibWOk6qPQ4RPHmw7U1MoPgHgDhZ7MLUYuouraaXqBIbucybELbUt+gudiAyonZfrdsnkLZ+F8TNjE1DMVj8hRj7bS+dQunYIrLbLh8tmj3MBs9ApmTkyE6frP7yYtLw1kSVIsJEu9M4rQCrb0hyP8/rBYFAviryF44MOPtqBc3eQwFYwkyes39U/Os9DNPDRQB2f9TfhJajwKRfgybnTZduYDY/q3rYZh978WH0/JWtAKRUVp5fkPQsZVIvs8lVFk60EPBwPOxh/e/FHefyy6IAoyjCvGA+nSRNfSAop7draDeiQPfXIEHaXCXo/ZWCA5eS0MFWM/qj8yKkMdoeTui7fZx9yfiNs4YSmE66tPAHjb04i2+S5a32Dye0O3JvnfP8AiybdNJTMYAXo7ImF+Gwk/dpDaXMGTAP5KTj2752eJDiCCUj8sRAy5M/OBbM1pIWqAdBo2DK6O/N0JqprWhbhfD+GOW2RD5CLJwb11CFi4zVXPTGHffg52qPnHy7aIuDCj7m+c/4hKaHp8eHVDi5gfMDDNe7Prji1/zPC1JsvTRI/4B4shf1MDkxLmW95tMJTky/jf4A12NBu3Qiewa8Sc80997UofOKP7WxR7anDsV2FD62RnsgTypr43/z4Td9Qi7cRy1EHq
X-OriginatorOrg: oracle.com
X-MS-Exchange-CrossTenant-Network-Message-Id: 
 08c9dec8-62f3-4aae-6552-08d914eed771
X-MS-Exchange-CrossTenant-AuthSource: SN6PR10MB3021.namprd10.prod.outlook.com
X-MS-Exchange-CrossTenant-AuthAs: Internal
X-MS-Exchange-CrossTenant-OriginalArrivalTime: 12 May 2021 02:37:10.1629
 (UTC)
X-MS-Exchange-CrossTenant-FromEntityHeader: Hosted
X-MS-Exchange-CrossTenant-Id: 4e2c6054-71cb-48f1-bd6c-3a9705aca71b
X-MS-Exchange-CrossTenant-MailboxType: HOSTED
X-MS-Exchange-CrossTenant-UserPrincipalName: 
 QUZReBoFmZV0VPBig1Y7NVNgj8BGcA2XyPLXhwEzxO+tndIFi0QD16rsrnKT0fW/g017phAF0PAjD9uaHN5ivUWxyfjB19TuS6gxXaz32xk=
X-MS-Exchange-Transport-CrossTenantHeadersStamped: SA2PR10MB4425
X-Proofpoint-Virus-Version: vendor=nai engine=6200 definitions=9981
 signatures=668683
X-Proofpoint-Spam-Details: rule=notspam policy=default score=0 bulkscore=0
 spamscore=0 mlxlogscore=773
 adultscore=0 phishscore=0 mlxscore=0 suspectscore=0 malwarescore=0
 classifier=spam adjust=0 reason=mlx scancount=1 engine=8.12.0-2104190000
 definitions=main-2105120018
X-Proofpoint-GUID: 0WtNSddFNVaYI3KA_96f_Oi6IbWaRzOI
X-Proofpoint-ORIG-GUID: 0WtNSddFNVaYI3KA_96f_Oi6IbWaRzOI
X-Proofpoint-Virus-Version: vendor=nai engine=6200 definitions=9981
 signatures=668683
X-Proofpoint-Spam-Details: rule=notspam policy=default score=0
 lowpriorityscore=0 malwarescore=0
 bulkscore=0 spamscore=0 clxscore=1015 priorityscore=1501 adultscore=0
 mlxlogscore=962 mlxscore=0 suspectscore=0 impostorscore=0 phishscore=0
 classifier=spam adjust=0 reason=mlx scancount=1 engine=8.12.0-2104190000
 definitions=main-2105120018
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Patch# 1: Renames 'nested_run' statistic and increments it from a more
	  fine-grained location.
Patch# 2: Adds a new statistic to show if a VCPU is running a nested guest.
Patch# 3: Adds a new statistic to show number of VCPUs created in a given VM.


[PATCH 1/3] KVM: nVMX: Move 'nested_run' counter to
[PATCH 2/3] KVM: nVMX: Add a new VCPU statistic to show if VCPU is
[PATCH 3/3] KVM: x86: Add a new VM statistic to show number of VCPUs

 arch/x86/include/asm/kvm_host.h |  4 +++-
 arch/x86/kvm/debugfs.c          | 11 +++++++++++
 arch/x86/kvm/kvm_cache_regs.h   |  4 ++++
 arch/x86/kvm/svm/nested.c       |  2 --
 arch/x86/kvm/vmx/nested.c       |  2 --
 arch/x86/kvm/x86.c              |  4 +++-
 virt/kvm/kvm_main.c             |  2 ++
 7 files changed, 23 insertions(+), 6 deletions(-)

Krish Sadhukhan (3):
      KVM: nVMX: Move 'nested_run' counter to enter_guest_mode()
      KVM: nVMX: Add a new VCPU statistic to show if VCPU is running nested guest
      KVM: x86: Add a new VM statistic to show number of VCPUs created in a given VM
```
#### [PATCH 0/6] x86/sev-es: Fixes for SEV-ES guest support
##### From: Joerg Roedel <joro@8bytes.org>
From: Joerg Roedel <jroedel@suse.de>

```c
From patchwork Wed May 12 07:54:39 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Joerg Roedel <joro@8bytes.org>
X-Patchwork-Id: 12252955
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-11.8 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,
	SPF_PASS,USER_AGENT_GIT autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 3799DC433B4
	for <kvm@archiver.kernel.org>; Wed, 12 May 2021 07:55:14 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id EF837613BF
	for <kvm@archiver.kernel.org>; Wed, 12 May 2021 07:55:13 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S230135AbhELH4U (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Wed, 12 May 2021 03:56:20 -0400
Received: from 8bytes.org ([81.169.241.247]:38532 "EHLO theia.8bytes.org"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S230026AbhELH4R (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 12 May 2021 03:56:17 -0400
Received: from cap.home.8bytes.org (p549ad305.dip0.t-ipconnect.de
 [84.154.211.5])
        (using TLSv1.3 with cipher TLS_AES_256_GCM_SHA384 (256/256 bits))
        (No client certificate requested)
        by theia.8bytes.org (Postfix) with ESMTPSA id 4BF4D90;
        Wed, 12 May 2021 09:55:07 +0200 (CEST)
From: Joerg Roedel <joro@8bytes.org>
To: x86@kernel.org, Hyunwook Baek <baekhw@google.com>
Cc: Joerg Roedel <joro@8bytes.org>, Joerg Roedel <jroedel@suse.de>,
        hpa@zytor.com, Andy Lutomirski <luto@kernel.org>,
        Dave Hansen <dave.hansen@linux.intel.com>,
        Peter Zijlstra <peterz@infradead.org>,
        Jiri Slaby <jslaby@suse.cz>,
        Dan Williams <dan.j.williams@intel.com>,
        Tom Lendacky <thomas.lendacky@amd.com>,
        Juergen Gross <jgross@suse.com>,
        Kees Cook <keescook@chromium.org>,
        David Rientjes <rientjes@google.com>,
        Cfir Cohen <cfir@google.com>,
        Erdem Aktas <erdemaktas@google.com>,
        Masami Hiramatsu <mhiramat@kernel.org>,
        Mike Stunes <mstunes@vmware.com>,
        Sean Christopherson <seanjc@google.com>,
        Martin Radev <martin.b.radev@gmail.com>,
        Arvind Sankar <nivedita@alum.mit.edu>,
        linux-coco@lists.linux.dev, linux-kernel@vger.kernel.org,
        kvm@vger.kernel.org, virtualization@lists.linux-foundation.org
Subject: [PATCH 0/6] x86/sev-es: Fixes for SEV-ES guest support
Date: Wed, 12 May 2021 09:54:39 +0200
Message-Id: <20210512075445.18935-1-joro@8bytes.org>
X-Mailer: git-send-email 2.31.1
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Joerg Roedel <jroedel@suse.de>

Hi,

here is a collection of fixes for the SEV-ES guest support. They fix
simple and more severe issues and are all targeted for v5.13. The most
important fixes are the revert of 7024f60d6552 which just doesn't work
in any context the #VC handler could run and the fix to forward #PF
exceptions caused during emulation. The issue that 7024f60d6552
intended to fix should be fixed correctly with these patches too.

Please review and test.

Regards,

	Joerg

Joerg Roedel (6):
  x86/sev-es: Don't return NULL from sev_es_get_ghcb()
  x86/sev-es: Forward page-faults which happen during emulation
  x86/sev-es: Use __put_user()/__get_user
  Revert "x86/sev-es: Handle string port IO to kernel memory properly"
  x86/sev-es: Fix error message in runtime #VC handler
  x86/sev-es: Leave NMI-mode before sending signals

 arch/x86/kernel/sev.c | 76 +++++++++++++++++++++----------------------
 1 file changed, 38 insertions(+), 38 deletions(-)


base-commit: 059e5c321a65657877924256ea8ad9c0df257b45
```
#### [PATCH v3 0/5] KVM: x86/pmu: Add support to enable guest PEBS via PT
##### From: Like Xu <like.xu@linux.intel.com>

```c
From patchwork Wed May 12 08:44:41 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Like Xu <like.xu@linux.intel.com>
X-Patchwork-Id: 12253081
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-11.8 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,
	SPF_PASS,USER_AGENT_GIT autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 14899C433B4
	for <kvm@archiver.kernel.org>; Wed, 12 May 2021 08:45:47 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id CE69B613DE
	for <kvm@archiver.kernel.org>; Wed, 12 May 2021 08:45:44 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S230480AbhELIqt (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Wed, 12 May 2021 04:46:49 -0400
Received: from mga17.intel.com ([192.55.52.151]:10038 "EHLO mga17.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S230096AbhELIqo (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 12 May 2021 04:46:44 -0400
IronPort-SDR: 
 LSPaUHYaGhsNU8uJ1bUhVEY69gRLFXuXgsxGQEwW3dUuG+vmX8s95GpkR1z6kGf+xpnFqoJATM
 n5Qse1oZzkVw==
X-IronPort-AV: E=McAfee;i="6200,9189,9981"; a="179918813"
X-IronPort-AV: E=Sophos;i="5.82,293,1613462400";
   d="scan'208";a="179918813"
Received: from orsmga006.jf.intel.com ([10.7.209.51])
  by fmsmga107.fm.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 12 May 2021 01:45:30 -0700
IronPort-SDR: 
 pHQzv+7oLzuQtAKTkxu+wL+dlxGMt8rujpMGlq2NM3gsNLyfA1tgmEv22+x537LeLaKPIAmgIy
 THXPmhhRCBMQ==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.82,293,1613462400";
   d="scan'208";a="392636309"
Received: from clx-ap-likexu.sh.intel.com ([10.239.48.108])
  by orsmga006.jf.intel.com with ESMTP; 12 May 2021 01:45:26 -0700
From: Like Xu <like.xu@linux.intel.com>
To: Paolo Bonzini <pbonzini@redhat.com>, peterz@infradead.org
Cc: Sean Christopherson <seanjc@google.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>, weijiang.yang@intel.com,
        eranian@google.com, wei.w.wang@intel.com, kvm@vger.kernel.org,
        x86@kernel.org, linux-kernel@vger.kernel.org,
        Like Xu <like.xu@linux.intel.com>
Subject: [PATCH v3 0/5] KVM: x86/pmu: Add support to enable guest PEBS via PT
Date: Wed, 12 May 2021 16:44:41 +0800
Message-Id: <20210512084446.342526-1-like.xu@linux.intel.com>
X-Mailer: git-send-email 2.31.1
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

I recently noticed that some developers particularly like the PT feature.
So please help review this version since a new kernel cycle has begun .

Intel new hardware (Atom processors based on the Tremont microarchitecture)
introduces some Processor Event-Based Sampling (PEBS) extensions that output
the PEBS record to Intel PT stream instead of DS area. The PEBS record will
be packaged in a specific format when outputting to Intel PT buffer.

To use PEBS-via-PT, the guest driver will firstly check the basic support
for PEBS-via-DS, so this patch set is based on the PEBS-via-DS enabling
patch set [1].

We can use PEBS-via-PT feature on the Linux guest like native:
(you may need modprobe kvm-intel.ko with pt_mode=1)

Recording is selected by using the aux-output config term e.g.
$ perf record -c 10000 -e '{intel_pt/branch=0/,cycles/aux-output/ppp}' uname
Warning:
Intel Processor Trace: TSC not available
Linux
[ perf record: Woken up 1 times to write data ]
[ perf record: Captured and wrote 0.028 MB perf.data ]

To display PEBS events from the Intel PT trace, use the itrace 'o' option e.g.
$ perf script --itrace=oe
uname   853   113.230292:      10000 cycles/aux-output/ppp:  ffffffff8125dcd9 perf_output_begin+0x29 ([kernel.kallsyms])
uname   853   113.230443:      10000 cycles/aux-output/ppp:  ffffffff8106de86 native_write_msr+0x6 ([kernel.kallsyms])
uname   853   113.230444:      10000 cycles/aux-output/ppp:  ffffffff81bd035b exc_nmi+0x10b ([kernel.kallsyms])
uname   853   113.230567:      10000 cycles/aux-output/ppp:  ffffffff8106de86 native_write_msr+0x6 ([kernel.kallsyms])
uname   853   113.230567:      10000 cycles/aux-output/ppp:  ffffffff8125dce0 perf_output_begin+0x30 ([kernel.kallsyms])
uname   853   113.230688:      10000 cycles/aux-output/ppp:  ffffffff8106de86 native_write_msr+0x6 ([kernel.kallsyms])
uname   853   113.230689:      10000 cycles/aux-output/ppp:  ffffffff81005da7 perf_event_nmi_handler+0x7 ([kernel.kallsyms])
uname   853   113.230816:      10000 cycles/aux-output/ppp:  ffffffff8106de86 native_write_msr+0x6 ([kernel.kallsyms])

Please check more details in each commit and feel free to comment.

V2 -> V3 Changelog:
- Add x86_pmu.pebs_vmx to ATOM_TREMONT and support PDIR counter;
- Rewrite get_gp_pmc() and get_fixed_pmc() based on PERF_CAP_PEBS_OUTPUT_PT;
- Check and add counter reload registers in the intel_guest_get_msrs();
- Expose this capability in the vmx_get_perf_capabilities();
 
Previous:
https://lore.kernel.org/kvm/1584628430-23220-1-git-send-email-luwei.kang@intel.com/
[1] https://lore.kernel.org/kvm/20210511024214.280733-1-like.xu@linux.intel.com/

Like Xu (4):
  KVM: x86/pmu: Add pebs_vmx support for ATOM_TREMONT
  KVM: x86/pmu: Add counter reload MSR emulation for all counters
  KVM: x86/pmu: Add counter reload registers to the MSR-load list
  KVM: x86/pmu: Expose PEBS-via-PT in the KVM supported capabilities

Luwei Kang (1):
  KVM: x86/pmu: Add the base address parameter for get_fixed_pmc()

 arch/x86/events/intel/core.c     | 28 +++++++++++++++++++++++++
 arch/x86/events/perf_event.h     |  5 -----
 arch/x86/include/asm/kvm_host.h  |  1 +
 arch/x86/include/asm/msr-index.h |  6 ++++++
 arch/x86/kvm/pmu.c               |  5 ++---
 arch/x86/kvm/pmu.h               | 11 ++++++++--
 arch/x86/kvm/vmx/capabilities.h  |  5 ++++-
 arch/x86/kvm/vmx/pmu_intel.c     | 35 ++++++++++++++++++++++++++------
 arch/x86/kvm/vmx/vmx.h           |  2 +-
 9 files changed, 80 insertions(+), 18 deletions(-)
```
#### [PATCH v2 kvm-unit-tests 0/2] fix long division routines for ARM eabi
##### From: Paolo Bonzini <pbonzini@redhat.com>

```c
From patchwork Wed May 12 10:54:38 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Paolo Bonzini <pbonzini@redhat.com>
X-Patchwork-Id: 12253337
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-11.8 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_PATCH,MAILING_LIST_MULTI,
	SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT autolearn=ham autolearn_force=no
	version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 65781C433B4
	for <kvm@archiver.kernel.org>; Wed, 12 May 2021 10:54:49 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 31CB6613FC
	for <kvm@archiver.kernel.org>; Wed, 12 May 2021 10:54:49 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S230217AbhELKzz (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Wed, 12 May 2021 06:55:55 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:41996 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S230236AbhELKzx (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 12 May 2021 06:55:53 -0400
Received: from mail-ed1-x532.google.com (mail-ed1-x532.google.com
 [IPv6:2a00:1450:4864:20::532])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id A3919C06174A
        for <kvm@vger.kernel.org>; Wed, 12 May 2021 03:54:43 -0700 (PDT)
Received: by mail-ed1-x532.google.com with SMTP id di13so26526092edb.2
        for <kvm@vger.kernel.org>; Wed, 12 May 2021 03:54:43 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=sender:from:to:cc:subject:date:message-id:mime-version
         :content-transfer-encoding;
        bh=9AyQNFRVaqZBkCum64ac2+NglKRSTSG7tKAIz1f0VSU=;
        b=TwZ2PNgQ6ijB4H5qDp02wNhKbmobbFG4WokNqwDWqfLgXrLBfgsl9zhYCyb8getMv6
         j5ut8iN1DOHv7M9tu7E1aA5J7dc6EK2hw0fwJ/4IW4p7iyfzN6SRHh2gppVvDRGhBMVg
         FgSQ9FGoIlRO5f/eacfeDrxoLJkP7Zvtmx+INFQTe23KDk/0/7Csrj4ZTTCGYPdvjLN+
         oTtZAygHpsyRZ62OFurrlHfq6oxIIwISYF1XejQRHbaXPWhsPJ/YtVww5fx2qLJrYluQ
         vkk/YkLg9k/qn3WiGxW8+nE8EVVv25uSPqZBB3QX2tVj4nkz24IqdS+bJpTFuvvsKf6v
         owOg==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:sender:from:to:cc:subject:date:message-id
         :mime-version:content-transfer-encoding;
        bh=9AyQNFRVaqZBkCum64ac2+NglKRSTSG7tKAIz1f0VSU=;
        b=i+mghMc7+SOWXogDaKbJJ7XbjGd3Oz16u70TY7+pWY25iy/PkExhWN8wB3rXdp4nlT
         2fMLwx1M64cBmBAlAPj2SRIFtVkKjkFjBdp0rkcr5uba8YAjTOpPJPMwMXQtNk/VCHVz
         zTkefqPIs2wTt4T21YCEEGw7DSpn/di4ctjaE2qdxP8gE7ZgoafOV5/eRC2/UKcSq3YM
         j7B7QpBfu4NmXaiTqXp6uVvIKqIZZ+8BRZXsnv9790U2Ohf16l+cM5TB8WA1T0aSDu5w
         pdkhGcfrMmO1VCHrsgcfBRLev3Y4i7IwfkSnHxIg1IA0gLxnO4ZWK/K/It/zs/n2PU9l
         OXBA==
X-Gm-Message-State: AOAM530nG/lK7W6wgp1eZlBtvfXQxrGUO7Cn3aIXAlsNR0a4+qVdlKhs
        3vbEMxY8Hd9DPA7HVkjd5yNGW3f/+Vw=
X-Google-Smtp-Source: 
 ABdhPJwhefcaEZSk4CzEzFI3pWa0vvw3XVp89SQUFD1Knw6bzz/ouYu4c4NHqvytRBVu64y6+qvolA==
X-Received: by 2002:a50:fe04:: with SMTP id f4mr42236651edt.29.1620816882383;
        Wed, 12 May 2021 03:54:42 -0700 (PDT)
Received: from avogadro.lan ([2001:b07:6468:f312:c8dd:75d4:99ab:290a])
        by smtp.gmail.com with ESMTPSA id
 b19sm16829624edd.66.2021.05.12.03.54.41
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Wed, 12 May 2021 03:54:41 -0700 (PDT)
Sender: Paolo Bonzini <paolo.bonzini@gmail.com>
From: Paolo Bonzini <pbonzini@redhat.com>
To: kvm@vger.kernel.org
Cc: Alexandru Elisei <alexandru.elisei@arm.com>
Subject: [PATCH v2 kvm-unit-tests 0/2] fix long division routines for ARM eabi
Date: Wed, 12 May 2021 12:54:38 +0200
Message-Id: <20210512105440.748153-1-pbonzini@redhat.com>
X-Mailer: git-send-email 2.31.1
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

As reported by Alexandru, ARM follows a different convention than
x86 so it needs __aeabi_ldivmod and __aeabi_uldivmod.  Because
it does not use __divdi3 and __moddi3, it also needs __divmoddi4
to build the eabi function upon.

Paolo

v1->v2: fix __divmoddi4, make sure -DTEST covers it

Paolo Bonzini (2):
  libcflat: clean up and complete long division routines
  arm: add eabi version of 64-bit division functions

 arm/Makefile.arm  |  1 +
 lib/arm/ldivmod.S | 32 ++++++++++++++++++++++++++++++++
 lib/ldiv32.c      | 40 ++++++++++++++++++++++++----------------
 3 files changed, 57 insertions(+), 16 deletions(-)
 create mode 100644 lib/arm/ldivmod.S
Tested-by: Alexandru Elisei <alexandru.elisei@arm.com>
```
#### [PATCH v2 00/40] Use ASCII subset instead of UTF-8 alternate symbols
##### From: Mauro Carvalho Chehab <mchehab+huawei@kernel.org>

```c
From patchwork Wed May 12 12:50:04 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 8bit
X-Patchwork-Submitter: Mauro Carvalho Chehab <mchehab+huawei@kernel.org>
X-Patchwork-Id: 12253473
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-14.7 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,INCLUDES_PATCH,MAILING_LIST_MULTI,
	SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT autolearn=unavailable
	autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 9031AC43600
	for <kvm@archiver.kernel.org>; Wed, 12 May 2021 12:52:03 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 4FA1A61104
	for <kvm@archiver.kernel.org>; Wed, 12 May 2021 12:52:03 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S231910AbhELMxJ (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Wed, 12 May 2021 08:53:09 -0400
Received: from mail.kernel.org ([198.145.29.99]:52778 "EHLO mail.kernel.org"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S231388AbhELMw4 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 12 May 2021 08:52:56 -0400
Received: by mail.kernel.org (Postfix) with ESMTPSA id 2B11D61175;
        Wed, 12 May 2021 12:51:42 +0000 (UTC)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple; d=kernel.org;
        s=k20201202; t=1620823902;
        bh=L+E/N8mtA2/+iSqhjhIyKk7M7RrC5qMfkQmRh4SXqOM=;
        h=From:To:Cc:Subject:Date:From;
        b=ucNSAhXYlF3Szz7W2irBTsvcIq33u1CrsW3ughaZJQqP+LrxpB0KjDChNaWylRCiA
         8uidMvIFPObFZ6akJiKIQ1n/loNfn6hx8yVucw2xWZ73EfgNRibzOSlugYBt51kwpz
         sdmRPA3LdwD45uYQTpj7XZoENUjgUxwJTlI1qlwGCNWZNWI+BkaJBNQJYsI68pIF0d
         fXOa2Wzs1nudr171bvqR7b67LC1CF/NPtlR0c90fFeyu9TgllD9P44UMzmzYncl5FJ
         KVeCETjMQ0hlqHZjf6TbTaK//D282G036gFoleiqqZjAOauHQnBlpoCUvLp2Ls+ug5
         bNkKFQYHSRskA==
Received: by mail.kernel.org with local (Exim 4.94.2)
        (envelope-from <mchehab@kernel.org>)
        id 1lgoKy-0018go-1r; Wed, 12 May 2021 14:51:40 +0200
From: Mauro Carvalho Chehab <mchehab+huawei@kernel.org>
To: Linux Doc Mailing List <linux-doc@vger.kernel.org>
Cc: Mauro Carvalho Chehab <mchehab+huawei@kernel.org>,
        linux-kernel@vger.kernel.org, Jonathan Corbet <corbet@lwn.net>,
        Mali DP Maintainers <malidp@foss.arm.com>,
        alsa-devel@alsa-project.org, coresight@lists.linaro.org,
        dri-devel@lists.freedesktop.org, intel-gfx@lists.freedesktop.org,
        intel-wired-lan@lists.osuosl.org, keyrings@vger.kernel.org,
        kvm@vger.kernel.org, linux-acpi@vger.kernel.org,
        linux-arm-kernel@lists.infradead.org, linux-edac@vger.kernel.org,
        linux-ext4@vger.kernel.org, linux-f2fs-devel@lists.sourceforge.net,
        linux-hwmon@vger.kernel.org, linux-iio@vger.kernel.org,
        linux-input@vger.kernel.org, linux-integrity@vger.kernel.org,
        linux-media@vger.kernel.org, linux-pci@vger.kernel.org,
        linux-pm@vger.kernel.org, linux-rdma@vger.kernel.org,
        linux-sgx@vger.kernel.org, linux-usb@vger.kernel.org,
        mjpeg-users@lists.sourceforge.net, netdev@vger.kernel.org,
        rcu@vger.kernel.org
Subject: [PATCH v2 00/40] Use ASCII subset instead of UTF-8 alternate symbols
Date: Wed, 12 May 2021 14:50:04 +0200
Message-Id: <cover.1620823573.git.mchehab+huawei@kernel.org>
X-Mailer: git-send-email 2.30.2
MIME-Version: 1.0
Sender: Mauro Carvalho Chehab <mchehab@kernel.org>
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This series contain basically a cleanup from all those years of converting
files to ReST.

During the conversion period, several tools like LaTeX, pandoc, DocBook
and some specially-written scripts were used in order to convert
existing documents.

Such conversion tools - plus some text editor like LibreOffice  or similar  - have
a set of rules that turns some typed ASCII characters into UTF-8 alternatives,
for instance converting commas into curly commas and adding non-breakable
spaces. All of those are meant to produce better results when the text is
displayed in HTML or PDF formats.

While it is perfectly fine to use UTF-8 characters in Linux, and specially at
the documentation,  it is better to  stick to the ASCII subset  on such
particular case,  due to a couple of reasons:

1. it makes life easier for tools like grep;
2. they easier to edit with the some commonly used text/source
   code editors.
    
Also, Sphinx already do such conversion automatically outside 
literal blocks, as described at:

       https://docutils.sourceforge.io/docs/user/smartquotes.html

In this series, the following UTF-8 symbols are replaced:

            - U+00a0 (' '): NO-BREAK SPACE
            - U+00ad ('­'): SOFT HYPHEN
            - U+00b4 ('´'): ACUTE ACCENT
            - U+00d7 ('×'): MULTIPLICATION SIGN
            - U+2010 ('‐'): HYPHEN
            - U+2018 ('‘'): LEFT SINGLE QUOTATION MARK
            - U+2019 ('’'): RIGHT SINGLE QUOTATION MARK
            - U+201c ('“'): LEFT DOUBLE QUOTATION MARK
            - U+201d ('”'): RIGHT DOUBLE QUOTATION MARK
            - U+2212 ('−'): MINUS SIGN
            - U+2217 ('∗'): ASTERISK OPERATOR
            - U+feff ('﻿'): ZERO WIDTH NO-BREAK SPACE (BOM)
---

v2:
- removed EM/EN DASH conversion from this patchset;
- removed a few fixes, as those were addressed on a separate series.
 
PS.:
   The first version of this series was posted with a different name:

	https://lore.kernel.org/lkml/cover.1620641727.git.mchehab+huawei@kernel.org/

   I also changed the patch texts, in order to better describe the patches goals.

Mauro Carvalho Chehab (40):
  docs: hwmon: Use ASCII subset instead of UTF-8 alternate symbols
  docs: admin-guide: Use ASCII subset instead of UTF-8 alternate symbols
  docs: admin-guide: media: ipu3.rst: Use ASCII subset instead of UTF-8
    alternate symbols
  docs: admin-guide: perf: imx-ddr.rst: Use ASCII subset instead of
    UTF-8 alternate symbols
  docs: admin-guide: pm: Use ASCII subset instead of UTF-8 alternate
    symbols
  docs: trace: coresight: coresight-etm4x-reference.rst: Use ASCII
    subset instead of UTF-8 alternate symbols
  docs: driver-api: ioctl.rst: Use ASCII subset instead of UTF-8
    alternate symbols
  docs: driver-api: thermal: Use ASCII subset instead of UTF-8 alternate
    symbols
  docs: driver-api: media: drivers: Use ASCII subset instead of UTF-8
    alternate symbols
  docs: driver-api: firmware: other_interfaces.rst: Use ASCII subset
    instead of UTF-8 alternate symbols
  docs: fault-injection: nvme-fault-injection.rst: Use ASCII subset
    instead of UTF-8 alternate symbols
  docs: usb: Use ASCII subset instead of UTF-8 alternate symbols
  docs: process: code-of-conduct.rst: Use ASCII subset instead of UTF-8
    alternate symbols
  docs: userspace-api: media: fdl-appendix.rst: Use ASCII subset instead
    of UTF-8 alternate symbols
  docs: userspace-api: media: v4l: Use ASCII subset instead of UTF-8
    alternate symbols
  docs: userspace-api: media: dvb: Use ASCII subset instead of UTF-8
    alternate symbols
  docs: vm: zswap.rst: Use ASCII subset instead of UTF-8 alternate
    symbols
  docs: filesystems: f2fs.rst: Use ASCII subset instead of UTF-8
    alternate symbols
  docs: filesystems: ext4: Use ASCII subset instead of UTF-8 alternate
    symbols
  docs: kernel-hacking: Use ASCII subset instead of UTF-8 alternate
    symbols
  docs: hid: Use ASCII subset instead of UTF-8 alternate symbols
  docs: security: tpm: tpm_event_log.rst: Use ASCII subset instead of
    UTF-8 alternate symbols
  docs: security: keys: trusted-encrypted.rst: Use ASCII subset instead
    of UTF-8 alternate symbols
  docs: networking: scaling.rst: Use ASCII subset instead of UTF-8
    alternate symbols
  docs: networking: devlink: devlink-dpipe.rst: Use ASCII subset instead
    of UTF-8 alternate symbols
  docs: networking: device_drivers: Use ASCII subset instead of UTF-8
    alternate symbols
  docs: x86: Use ASCII subset instead of UTF-8 alternate symbols
  docs: scheduler: sched-deadline.rst: Use ASCII subset instead of UTF-8
    alternate symbols
  docs: power: powercap: powercap.rst: Use ASCII subset instead of UTF-8
    alternate symbols
  docs: ABI: Use ASCII subset instead of UTF-8 alternate symbols
  docs: PCI: acpi-info.rst: Use ASCII subset instead of UTF-8 alternate
    symbols
  docs: gpu: Use ASCII subset instead of UTF-8 alternate symbols
  docs: sound: kernel-api: writing-an-alsa-driver.rst: Use ASCII subset
    instead of UTF-8 alternate symbols
  docs: arm64: arm-acpi.rst: Use ASCII subset instead of UTF-8 alternate
    symbols
  docs: infiniband: tag_matching.rst: Use ASCII subset instead of UTF-8
    alternate symbols
  docs: misc-devices: ibmvmc.rst: Use ASCII subset instead of UTF-8
    alternate symbols
  docs: firmware-guide: acpi: lpit.rst: Use ASCII subset instead of
    UTF-8 alternate symbols
  docs: firmware-guide: acpi: dsd: graph.rst: Use ASCII subset instead
    of UTF-8 alternate symbols
  docs: virt: kvm: api.rst: Use ASCII subset instead of UTF-8 alternate
    symbols
  docs: RCU: Use ASCII subset instead of UTF-8 alternate symbols

 ...sfs-class-chromeos-driver-cros-ec-lightbar |   2 +-
 .../ABI/testing/sysfs-devices-platform-ipmi   |   2 +-
 .../testing/sysfs-devices-platform-trackpoint |   2 +-
 Documentation/ABI/testing/sysfs-devices-soc   |   4 +-
 Documentation/PCI/acpi-info.rst               |  22 +-
 .../Data-Structures/Data-Structures.rst       |  52 ++--
 .../Expedited-Grace-Periods.rst               |  40 +--
 .../Tree-RCU-Memory-Ordering.rst              |  10 +-
 .../RCU/Design/Requirements/Requirements.rst  | 122 ++++-----
 Documentation/admin-guide/media/ipu3.rst      |   2 +-
 Documentation/admin-guide/perf/imx-ddr.rst    |   2 +-
 Documentation/admin-guide/pm/intel_idle.rst   |   4 +-
 Documentation/admin-guide/pm/intel_pstate.rst |   4 +-
 Documentation/admin-guide/ras.rst             |  86 +++---
 .../admin-guide/reporting-issues.rst          |   2 +-
 Documentation/arm64/arm-acpi.rst              |   8 +-
 .../driver-api/firmware/other_interfaces.rst  |   2 +-
 Documentation/driver-api/ioctl.rst            |   8 +-
 .../media/drivers/sh_mobile_ceu_camera.rst    |   8 +-
 .../driver-api/media/drivers/zoran.rst        |   2 +-
 .../driver-api/thermal/cpu-idle-cooling.rst   |  14 +-
 .../driver-api/thermal/intel_powerclamp.rst   |   6 +-
 .../thermal/x86_pkg_temperature_thermal.rst   |   2 +-
 .../fault-injection/nvme-fault-injection.rst  |   2 +-
 Documentation/filesystems/ext4/attributes.rst |  20 +-
 Documentation/filesystems/ext4/bigalloc.rst   |   6 +-
 Documentation/filesystems/ext4/blockgroup.rst |   8 +-
 Documentation/filesystems/ext4/blocks.rst     |   2 +-
 Documentation/filesystems/ext4/directory.rst  |  16 +-
 Documentation/filesystems/ext4/eainode.rst    |   2 +-
 Documentation/filesystems/ext4/inlinedata.rst |   6 +-
 Documentation/filesystems/ext4/inodes.rst     |   6 +-
 Documentation/filesystems/ext4/journal.rst    |   8 +-
 Documentation/filesystems/ext4/mmp.rst        |   2 +-
 .../filesystems/ext4/special_inodes.rst       |   4 +-
 Documentation/filesystems/ext4/super.rst      |  10 +-
 Documentation/filesystems/f2fs.rst            |   4 +-
 .../firmware-guide/acpi/dsd/graph.rst         |   2 +-
 Documentation/firmware-guide/acpi/lpit.rst    |   2 +-
 Documentation/gpu/i915.rst                    |   2 +-
 Documentation/gpu/komeda-kms.rst              |   2 +-
 Documentation/hid/hid-sensor.rst              |  70 ++---
 Documentation/hid/intel-ish-hid.rst           | 246 +++++++++---------
 Documentation/hwmon/ir36021.rst               |   2 +-
 Documentation/hwmon/ltc2992.rst               |   2 +-
 Documentation/hwmon/pm6764tr.rst              |   2 +-
 Documentation/infiniband/tag_matching.rst     |   4 +-
 Documentation/kernel-hacking/hacking.rst      |   2 +-
 Documentation/kernel-hacking/locking.rst      |   2 +-
 Documentation/misc-devices/ibmvmc.rst         |   8 +-
 .../device_drivers/ethernet/intel/i40e.rst    |   8 +-
 .../device_drivers/ethernet/intel/iavf.rst    |   4 +-
 .../device_drivers/ethernet/netronome/nfp.rst |  12 +-
 .../networking/devlink/devlink-dpipe.rst      |   2 +-
 Documentation/networking/scaling.rst          |  18 +-
 Documentation/power/powercap/powercap.rst     | 210 +++++++--------
 Documentation/process/code-of-conduct.rst     |   2 +-
 Documentation/scheduler/sched-deadline.rst    |   2 +-
 .../security/keys/trusted-encrypted.rst       |   4 +-
 Documentation/security/tpm/tpm_event_log.rst  |   2 +-
 .../kernel-api/writing-an-alsa-driver.rst     |  68 ++---
 .../coresight/coresight-etm4x-reference.rst   |  16 +-
 Documentation/usb/ehci.rst                    |   2 +-
 Documentation/usb/gadget_printer.rst          |   2 +-
 Documentation/usb/mass-storage.rst            |  36 +--
 .../media/dvb/audio-set-bypass-mode.rst       |   2 +-
 .../userspace-api/media/dvb/audio.rst         |   2 +-
 .../userspace-api/media/dvb/dmx-fopen.rst     |   2 +-
 .../userspace-api/media/dvb/dmx-fread.rst     |   2 +-
 .../media/dvb/dmx-set-filter.rst              |   2 +-
 .../userspace-api/media/dvb/intro.rst         |   6 +-
 .../userspace-api/media/dvb/video.rst         |   2 +-
 .../userspace-api/media/fdl-appendix.rst      |  64 ++---
 .../userspace-api/media/v4l/crop.rst          |  16 +-
 .../userspace-api/media/v4l/dev-decoder.rst   |   6 +-
 .../userspace-api/media/v4l/diff-v4l.rst      |   2 +-
 .../userspace-api/media/v4l/open.rst          |   2 +-
 .../media/v4l/vidioc-cropcap.rst              |   4 +-
 Documentation/virt/kvm/api.rst                |  28 +-
 Documentation/vm/zswap.rst                    |   4 +-
 Documentation/x86/resctrl.rst                 |   2 +-
 Documentation/x86/sgx.rst                     |   4 +-
 82 files changed, 693 insertions(+), 693 deletions(-)
```
#### [PATCH v2 00/10] KVM: Implement nested TSC scaling
##### From: Ilias Stamatis <ilstam@amazon.com>

```c
From patchwork Wed May 12 15:09:35 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Ilias Stamatis <ilstam@amazon.com>
X-Patchwork-Id: 12254077
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-14.4 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT
	autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 90F16C43460
	for <kvm@archiver.kernel.org>; Wed, 12 May 2021 15:16:05 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 5803E6197E
	for <kvm@archiver.kernel.org>; Wed, 12 May 2021 15:16:04 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S232148AbhELPRH (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Wed, 12 May 2021 11:17:07 -0400
Received: from smtp-fw-6002.amazon.com ([52.95.49.90]:48577 "EHLO
        smtp-fw-6002.amazon.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S233381AbhELPMq (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 12 May 2021 11:12:46 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
  d=amazon.com; i=@amazon.com; q=dns/txt; s=amazon201209;
  t=1620832299; x=1652368299;
  h=from:to:cc:subject:date:message-id:mime-version;
  bh=HKr3J8IhS0dTtfoFa0Dujjg1idj5c2M2ekOtri5Eo0A=;
  b=tbCPyRd4dLXIVPbrObtI2l5kCXm8YwcJyqCXMyYk5pPrjjuFIZ7TVvfE
   tUlrfLeSTSN5cPNVfBBe6Crgo1UegGlgAoEq8bSEx1aejtUwK5TAjNHUZ
   psvPHZSm9gsWKAbCPWsjU/dgOm2t17DyGnQZbpKc76LwssxWi6TCIC6dr
   o=;
X-IronPort-AV: E=Sophos;i="5.82,293,1613433600";
   d="scan'208";a="111783246"
Received: from iad12-co-svc-p1-lb1-vlan2.amazon.com (HELO
 email-inbound-relay-1a-e34f1ddc.us-east-1.amazon.com) ([10.43.8.2])
  by smtp-border-fw-6002.iad6.amazon.com with ESMTP;
 12 May 2021 15:11:31 +0000
Received: from EX13MTAUEB001.ant.amazon.com
 (iad12-ws-svc-p26-lb9-vlan2.iad.amazon.com [10.40.163.34])
        by email-inbound-relay-1a-e34f1ddc.us-east-1.amazon.com (Postfix) with
 ESMTPS id 5B57FA1C13;
        Wed, 12 May 2021 15:11:27 +0000 (UTC)
Received: from EX13D08UEB003.ant.amazon.com (10.43.60.11) by
 EX13MTAUEB001.ant.amazon.com (10.43.60.129) with Microsoft SMTP Server (TLS)
 id 15.0.1497.2; Wed, 12 May 2021 15:11:26 +0000
Received: from EX13MTAUEB002.ant.amazon.com (10.43.60.12) by
 EX13D08UEB003.ant.amazon.com (10.43.60.11) with Microsoft SMTP Server (TLS)
 id 15.0.1497.2; Wed, 12 May 2021 15:11:26 +0000
Received: from uae075a0dfd4c51.ant.amazon.com (10.106.82.24) by
 mail-relay.amazon.com (10.43.60.234) with Microsoft SMTP Server id
 15.0.1497.2 via Frontend Transport; Wed, 12 May 2021 15:11:24 +0000
From: Ilias Stamatis <ilstam@amazon.com>
To: <kvm@vger.kernel.org>, <linux-kernel@vger.kernel.org>,
        <pbonzini@redhat.com>
CC: <mlevitsk@redhat.com>, <seanjc@google.com>, <vkuznets@redhat.com>,
        <wanpengli@tencent.com>, <jmattson@google.com>, <joro@8bytes.org>,
        <zamsden@gmail.com>, <mtosatti@redhat.com>, <dwmw@amazon.co.uk>,
        <ilstam@amazon.com>
Subject: [PATCH v2 00/10] KVM: Implement nested TSC scaling
Date: Wed, 12 May 2021 16:09:35 +0100
Message-ID: <20210512150945.4591-1-ilstam@amazon.com>
X-Mailer: git-send-email 2.17.1
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

KVM currently supports hardware-assisted TSC scaling but only for L1;
the feature is not exposed to nested guests. This patch series adds
support for nested TSC scaling and allows both L1 and L2 to be scaled
with different scaling factors. That is achieved by "merging" the 01 and
02 values together.

Most of the logic in this series is implemented in common code (by doing
the necessary restructurings), however the patches add support for VMX
only. Adding support for SVM should be easy at this point and Maxim
Levitsky has volunteered to do this (thanks!).

Changelog:
v2:
  - Applied most (all?) of Maxim's feedback
  - Added a mul_s64_u64_shr function in math64.h
  - Added a separate kvm_scale_tsc_l1 function instead of passing an
    argument to kvm_scale_tsc
  - Implemented the 02 fields calculations in common code
  - Moved all of write_l1_tsc_offset's logic to common code
  - Added a check for whether the TSC is stable in patch 10
  - Used a random L1 factor and a negative offset in patch 10

Ilias Stamatis (10):
  math64.h: Add mul_s64_u64_shr()
  KVM: X86: Store L1's TSC scaling ratio in 'struct kvm_vcpu_arch'
  KVM: X86: Add kvm_scale_tsc_l1() and kvm_compute_tsc_offset_l1()
  KVM: VMX: Add a TSC multiplier field in VMCS12
  KVM: X86: Add functions for retrieving L2 TSC fields from common code
  KVM: X86: Add functions that calculate the 02 TSC offset and
    multiplier
  KVM: X86: Move write_l1_tsc_offset() logic to common code and rename
    it
  KVM: VMX: Set the TSC offset and multiplier on nested entry and exit
  KVM: VMX: Expose TSC scaling to L2
  KVM: selftests: x86: Add vmx_nested_tsc_scaling_test

 arch/x86/include/asm/kvm-x86-ops.h            |   4 +-
 arch/x86/include/asm/kvm_host.h               |  13 +-
 arch/x86/kvm/svm/svm.c                        |  29 ++-
 arch/x86/kvm/vmx/nested.c                     |  19 +-
 arch/x86/kvm/vmx/vmcs12.c                     |   1 +
 arch/x86/kvm/vmx/vmcs12.h                     |   4 +-
 arch/x86/kvm/vmx/vmx.c                        |  42 +--
 arch/x86/kvm/x86.c                            |  93 +++++--
 include/linux/math64.h                        |  19 ++
 tools/testing/selftests/kvm/.gitignore        |   1 +
 tools/testing/selftests/kvm/Makefile          |   1 +
 .../kvm/x86_64/vmx_nested_tsc_scaling_test.c  | 242 ++++++++++++++++++
 12 files changed, 409 insertions(+), 59 deletions(-)
 create mode 100644 tools/testing/selftests/kvm/x86_64/vmx_nested_tsc_scaling_test.c
```
