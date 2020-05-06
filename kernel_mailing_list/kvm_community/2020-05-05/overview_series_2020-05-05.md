#### [PATCH v8 01/18] KVM: SVM: Add KVM_SEV SEND_START command
##### From: Ashish Kalra <Ashish.Kalra@amd.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 8bit
X-Patchwork-Submitter: Ashish Kalra <Ashish.Kalra@amd.com>
X-Patchwork-Id: 11529917
Return-Path: <SRS0=tDSI=6T=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 4D2CB1392
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue,  5 May 2020 21:14:57 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 29791206B8
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue,  5 May 2020 21:14:57 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=amdcloud.onmicrosoft.com
 header.i=@amdcloud.onmicrosoft.com header.b="rjp5I1Tz"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729312AbgEEVO4 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 5 May 2020 17:14:56 -0400
Received: from mail-bn7nam10on2087.outbound.protection.outlook.com
 ([40.107.92.87]:6075
        "EHLO NAM10-BN7-obe.outbound.protection.outlook.com"
        rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org with ESMTP
        id S1728569AbgEEVOz (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 5 May 2020 17:14:55 -0400
ARC-Seal: i=1; a=rsa-sha256; s=arcselector9901; d=microsoft.com; cv=none;
 b=B9FpM6g/rRwk3sVqXhwRn7zdSMoumI1GWw2A/n6/O6ifSkbI+nmZxBNOaxt6aYXuhpcUVGWSK4EGw7OmGcKGOLmN2bCLTpwaSGEmDYEUfQKlfniwJ6WKYwBUFrgOzHMhvwrb7lnDiW+Vvvnvi/y9F8IyeAdscv5qxB7ziY9a4op/U6TpRzE77qBMbGsYOIbqnuYsI5yrOS4VtR2EE9aT6Kayw1+14kaxFYgd1uZP7ZiibbagYrEqJ6N+Ip4oQsbjGF7b7w7VCgepNwdEbMFB4DxCp32NRpSIZaUWibmJmx8PvOrwuqCtjFytKUEkhaIbf1PcC/ywd0ba7v3ieocpJA==
ARC-Message-Signature: i=1; a=rsa-sha256; c=relaxed/relaxed; d=microsoft.com;
 s=arcselector9901;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=PDgfuQklGju4Gg05clXYxpilK8eFCAieFKUU9qqubCY=;
 b=gjRFnCR3xqVdg47wg9E4cvxZyDcL9asVJ1ATI077ivNdBtJLHkAahfVxoPa3BgAbTvSFVPFHvQgklCVoKaafLIf6SdfIarjOO9h7wAGimVGQEicMiHDgctDtx6+C8Qih2Et/9jFirCAwITTm+4Dd2rV9vbq38Q8OEhXAbn1gXsd5vUuT4f3KzKUlj8tt4EaTL81GkXMPZD6o69dksJGo1ZdN9211NJB7UItxoC7XOmx0yituEDIOTecPrxJ9qkVoaKdw3CYXtV8x5RO+3osK5zAXeASTfJwcKbubiUx0nKFZtrBUUxadrdYC1JYy7qqcFZsYftajD+IAO/4j/8hGaA==
ARC-Authentication-Results: i=1; mx.microsoft.com 1; spf=pass
 smtp.mailfrom=amd.com; dmarc=pass action=none header.from=amd.com; dkim=pass
 header.d=amd.com; arc=none
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
 d=amdcloud.onmicrosoft.com; s=selector2-amdcloud-onmicrosoft-com;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=PDgfuQklGju4Gg05clXYxpilK8eFCAieFKUU9qqubCY=;
 b=rjp5I1TzxdWXXhWmDlLDeJwVv+fxZYX+xaNrsn9/NV1pPHZkt3ybzcNznvHgA0QbjEwAYgij/sGpafjTin/3YOCBIGqJLiQM3CN25ZpYLwRnJa5yP8a/sW9v2oQW51DsYy7tQywsYmTt6Q3bAGTAVnRPV7qDzCfzIPldJhe9fvA=
Authentication-Results: redhat.com; dkim=none (message not signed)
 header.d=none;redhat.com; dmarc=none action=none header.from=amd.com;
Received: from DM5PR12MB1386.namprd12.prod.outlook.com (2603:10b6:3:77::9) by
 DM5PR12MB2518.namprd12.prod.outlook.com (2603:10b6:4:b0::33) with Microsoft
 SMTP Server (version=TLS1_2, cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id
 15.20.2958.20; Tue, 5 May 2020 21:14:49 +0000
Received: from DM5PR12MB1386.namprd12.prod.outlook.com
 ([fe80::6962:a808:3fd5:7adb]) by DM5PR12MB1386.namprd12.prod.outlook.com
 ([fe80::6962:a808:3fd5:7adb%3]) with mapi id 15.20.2958.030; Tue, 5 May 2020
 21:14:49 +0000
From: Ashish Kalra <Ashish.Kalra@amd.com>
To: pbonzini@redhat.com
Cc: tglx@linutronix.de, mingo@redhat.com, hpa@zytor.com,
        joro@8bytes.org, bp@suse.de, Thomas.Lendacky@amd.com,
        x86@kernel.org, kvm@vger.kernel.org, linux-kernel@vger.kernel.org,
        srutherford@google.com, rientjes@google.com,
        venu.busireddy@oracle.com, brijesh.singh@amd.com
Subject: [PATCH v8 01/18] KVM: SVM: Add KVM_SEV SEND_START command
Date: Tue,  5 May 2020 21:14:39 +0000
Message-Id: 
 <58e0fb4c4d207028ec3b13cc3c20503224c95b86.1588711355.git.ashish.kalra@amd.com>
X-Mailer: git-send-email 2.17.1
In-Reply-To: <cover.1588711355.git.ashish.kalra@amd.com>
References: <cover.1588711355.git.ashish.kalra@amd.com>
X-ClientProxiedBy: DM5PR16CA0024.namprd16.prod.outlook.com
 (2603:10b6:3:c0::34) To DM5PR12MB1386.namprd12.prod.outlook.com
 (2603:10b6:3:77::9)
MIME-Version: 1.0
X-MS-Exchange-MessageSentRepresentingType: 1
Received: from ashkalra_ubuntu_server.amd.com (165.204.77.1) by
 DM5PR16CA0024.namprd16.prod.outlook.com (2603:10b6:3:c0::34) with Microsoft
 SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.2979.27 via Frontend
 Transport; Tue, 5 May 2020 21:14:48 +0000
X-Mailer: git-send-email 2.17.1
X-Originating-IP: [165.204.77.1]
X-MS-PublicTrafficType: Email
X-MS-Office365-Filtering-HT: Tenant
X-MS-Office365-Filtering-Correlation-Id: 01520af0-e10f-4e37-65c2-08d7f1395827
X-MS-TrafficTypeDiagnostic: DM5PR12MB2518:|DM5PR12MB2518:
X-MS-Exchange-Transport-Forked: True
X-Microsoft-Antispam-PRVS: 
 <DM5PR12MB25187474BD0D35C70EF2B8398EA70@DM5PR12MB2518.namprd12.prod.outlook.com>
X-MS-Oob-TLC-OOBClassifiers: OLM:6108;
X-Forefront-PRVS: 0394259C80
X-MS-Exchange-SenderADCheck: 1
X-Microsoft-Antispam: BCL:0;
X-Microsoft-Antispam-Message-Info: 
 a5qzEWZXhMAHEa7UdKaM5lL/1aCLrVc8ntehAqrYWMX6jwzOShsO2+wTb+P/+df4ZpGApCdIwB0m/MN1wWvBC+LCRiEc6S6Zpvdbdj8q6CUHbc1ShgqTy3CrDle6xsjRPq14GgKK1XOwXZA9LayyrMInqtbHkE/y9C2N09hXQOGxZ/bwwxZ0KzBeAYcX0I8rv39CbcKd8S2p48LzrQs8YYOD/k8iPo3fM7p3FJmfIQUT0MogGfDd1vy7dkj9aMrpbXcXupAvmZfNyaADFaUnmmykg+46cAVO0mX/EnrQ9ndsSgSBRGezBHiFfKb0QxTGbXOD8OYtl0nPDSHrmqC7Kdr98B7M5nMB27evgsZmowzbQoLVuY5M2Ec89kncjUZ8NnmBYP8f0GJveyzWB7AehHhgsfS2TIzcifUp4QwicWHrgSNtQS0qNAcm3SsycfBP5IdiJoShaCbOVc+hL8zJxwwVwwEeJaHGfqhHpkqDu1RxtCv8hrYbKjwIC6tjiVyc1+TP+FPBov9yqHdBZ47rqZR4E5se3aGReNZafzs+KwpFKonP5s37ARr68ajGeKxi
X-Forefront-Antispam-Report: 
 CIP:255.255.255.255;CTRY:;LANG:en;SCL:1;SRV:;IPV:NLI;SFV:NSPM;H:DM5PR12MB1386.namprd12.prod.outlook.com;PTR:;CAT:NONE;SFTY:;SFS:(4636009)(396003)(366004)(136003)(39860400002)(346002)(376002)(33430700001)(6916009)(26005)(36756003)(956004)(16526019)(478600001)(6486002)(2906002)(5660300002)(6666004)(2616005)(66574013)(186003)(66476007)(7416002)(52116002)(8936002)(86362001)(7696005)(8676002)(66556008)(66946007)(4326008)(33440700001)(316002)(136400200001);DIR:OUT;SFP:1101;
X-MS-Exchange-AntiSpam-MessageData: 
 uKY+IUi2QMDMTfdLkZAabxByr9M0k0AJpSScir1ZA82S7FwLYRsQd4gt2fHiFIIhiHuwZ2QvUVsqV9n8Y020PFXwotNUxrrowAAjjlLXtYX/bWG1Utpa2P6m7sj0ClhcJqaDXHN+kZkloxgQhkpf9D1Cz/NSeu+SZ9izx82uWHKYKyB5U8p7HTAXGfOFh1hS5jTjTN6ZWLQXLEUnETZhi/iWcWbyAGv+JoKYDIif8z9yS5HN4laSzYIYrL45omROHAR//J5wNc+iyMX0lPJabuumBuRtiep96McnjKQPU0zyqx4ZVSoYwXH9SnOWAUHflT5qa5YecBIGBDEhg210s9pUz2PFy1gGeuhih876cmfG4nFkhUWTi94Cog3M4ZSaGMrgjYV8oG2ijugLlP1JUTLNO1zjt0qBNqBKLpeIZnQeeltbkp1pfMqqY+SB4lahXHiewJD67WXXgKxMr93pBG6urZCxywYOz24hay6qb/7FTkhdWMFxpbQamoYkudY83GxZFkMhbfvEdVGpxp4o2UUzDnNyoUVVtjsk5KGwDNne4vF28RQ/pHrj99I4IjGCO4vN/5wBosmZHHlz2QWeTannuALz0xiUmf6FVMa82BzGJ4wmR7ST1EcdHF+6Vl87eGqly7hvaLK0yhRgHQUPUMm547YdNl/No1blPmP813+2VcqAwhql1p886MW83MtLriKdgdAlkXoTu+KdghzcegSKbpd6bdZ+gredLm1B9pVIZmjTejwYXaRzQemQsLONJsnczS29S8L3XJDixy038gCymFcc2m+bjJtSMaBZTT0=
X-OriginatorOrg: amd.com
X-MS-Exchange-CrossTenant-Network-Message-Id: 
 01520af0-e10f-4e37-65c2-08d7f1395827
X-MS-Exchange-CrossTenant-OriginalArrivalTime: 05 May 2020 21:14:49.5169
 (UTC)
X-MS-Exchange-CrossTenant-FromEntityHeader: Hosted
X-MS-Exchange-CrossTenant-Id: 3dd8961f-e488-4e60-8e11-a82d994e183d
X-MS-Exchange-CrossTenant-MailboxType: HOSTED
X-MS-Exchange-CrossTenant-UserPrincipalName: 
 2P10ktXDd9SRJANM5lX6ZVaDu0PsPjHHKpvmhCmdl58jk3nBx4ljkrRH1RlCgzPcwp5NY1UVx+WzWjg9e2aDnQ==
X-MS-Exchange-Transport-CrossTenantHeadersStamped: DM5PR12MB2518
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Brijesh Singh <Brijesh.Singh@amd.com>

The command is used to create an outgoing SEV guest encryption context.

Cc: Thomas Gleixner <tglx@linutronix.de>
Cc: Ingo Molnar <mingo@redhat.com>
Cc: "H. Peter Anvin" <hpa@zytor.com>
Cc: Paolo Bonzini <pbonzini@redhat.com>
Cc: "Radim Krčmář" <rkrcmar@redhat.com>
Cc: Joerg Roedel <joro@8bytes.org>
Cc: Borislav Petkov <bp@suse.de>
Cc: Tom Lendacky <thomas.lendacky@amd.com>
Cc: x86@kernel.org
Cc: kvm@vger.kernel.org
Cc: linux-kernel@vger.kernel.org
Reviewed-by: Steve Rutherford <srutherford@google.com>
Reviewed-by: Venu Busireddy <venu.busireddy@oracle.com>
Signed-off-by: Brijesh Singh <brijesh.singh@amd.com>
Signed-off-by: Ashish Kalra <ashish.kalra@amd.com>
---
 .../virt/kvm/amd-memory-encryption.rst        |  27 ++++
 arch/x86/kvm/svm/sev.c                        | 125 ++++++++++++++++++
 include/linux/psp-sev.h                       |   8 +-
 include/uapi/linux/kvm.h                      |  12 ++
 4 files changed, 168 insertions(+), 4 deletions(-)

```
#### [PATCH] KVM: s390: Remove false WARN_ON_ONCE for the PQAP instruction
##### From: Christian Borntraeger <borntraeger@de.ibm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Christian Borntraeger <borntraeger@de.ibm.com>
X-Patchwork-Id: 11528343
Return-Path: <SRS0=tDSI=6T=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id BBB1792A
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue,  5 May 2020 07:35:34 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id AD6B1206B9
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue,  5 May 2020 07:35:34 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728490AbgEEHfe (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 5 May 2020 03:35:34 -0400
Received: from mx0b-001b2d01.pphosted.com ([148.163.158.5]:12048 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S1725320AbgEEHfd (ORCPT
        <rfc822;kvm@vger.kernel.org>); Tue, 5 May 2020 03:35:33 -0400
Received: from pps.filterd (m0098413.ppops.net [127.0.0.1])
        by mx0b-001b2d01.pphosted.com (8.16.0.42/8.16.0.42) with SMTP id
 0457EuV6193034;
        Tue, 5 May 2020 03:35:32 -0400
Received: from pps.reinject (localhost [127.0.0.1])
        by mx0b-001b2d01.pphosted.com with ESMTP id 30s317mpe6-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Tue, 05 May 2020 03:35:32 -0400
Received: from m0098413.ppops.net (m0098413.ppops.net [127.0.0.1])
        by pps.reinject (8.16.0.36/8.16.0.36) with SMTP id 0457M1te008769;
        Tue, 5 May 2020 03:35:32 -0400
Received: from ppma03ams.nl.ibm.com (62.31.33a9.ip4.static.sl-reverse.com
 [169.51.49.98])
        by mx0b-001b2d01.pphosted.com with ESMTP id 30s317mpdf-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Tue, 05 May 2020 03:35:32 -0400
Received: from pps.filterd (ppma03ams.nl.ibm.com [127.0.0.1])
        by ppma03ams.nl.ibm.com (8.16.0.27/8.16.0.27) with SMTP id
 0457ZOmK008010;
        Tue, 5 May 2020 07:35:30 GMT
Received: from b06cxnps3075.portsmouth.uk.ibm.com
 (d06relay10.portsmouth.uk.ibm.com [9.149.109.195])
        by ppma03ams.nl.ibm.com with ESMTP id 30s0g5pexf-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Tue, 05 May 2020 07:35:30 +0000
Received: from d06av26.portsmouth.uk.ibm.com (d06av26.portsmouth.uk.ibm.com
 [9.149.105.62])
        by b06cxnps3075.portsmouth.uk.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id 0457ZRUn57278706
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Tue, 5 May 2020 07:35:27 GMT
Received: from d06av26.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 43FB6AE057;
        Tue,  5 May 2020 07:35:27 +0000 (GMT)
Received: from d06av26.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 3B2A2AE056;
        Tue,  5 May 2020 07:35:27 +0000 (GMT)
Received: from tuxmaker.boeblingen.de.ibm.com (unknown [9.152.85.9])
        by d06av26.portsmouth.uk.ibm.com (Postfix) with ESMTPS;
        Tue,  5 May 2020 07:35:27 +0000 (GMT)
Received: by tuxmaker.boeblingen.de.ibm.com (Postfix, from userid 25651)
        id 971E5E0605; Tue,  5 May 2020 09:35:26 +0200 (CEST)
From: Christian Borntraeger <borntraeger@de.ibm.com>
To: Janosch Frank <frankja@linux.vnet.ibm.com>
Cc: KVM <kvm@vger.kernel.org>, Cornelia Huck <cohuck@redhat.com>,
        Christian Borntraeger <borntraeger@de.ibm.com>,
        David Hildenbrand <david@redhat.com>,
        linux-s390 <linux-s390@vger.kernel.org>,
        Qian Cai <cailca@icloud.com>,
        Pierre Morel <pmorel@linux.ibm.com>,
        Tony Krowiak <akrowiak@linux.ibm.com>
Subject: [PATCH] KVM: s390: Remove false WARN_ON_ONCE for the PQAP instruction
Date: Tue,  5 May 2020 09:35:25 +0200
Message-Id: <20200505073525.2287-1-borntraeger@de.ibm.com>
X-Mailer: git-send-email 2.25.4
MIME-Version: 1.0
X-TM-AS-GCONF: 00
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.138,18.0.676
 definitions=2020-05-05_02:2020-05-04,2020-05-05 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 impostorscore=0 phishscore=0
 priorityscore=1501 lowpriorityscore=0 suspectscore=0 mlxscore=0
 spamscore=0 malwarescore=0 mlxlogscore=949 adultscore=0 bulkscore=0
 clxscore=1015 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.12.0-2003020000 definitions=main-2005050053
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

In LPAR we will only get an intercept for FC==3 for the PQAP
instruction. Running nested under z/VM can result in other intercepts as
well, for example PQAP(QCI). So the WARN_ON_ONCE is not right. Let
us simply remove it.

Cc: Pierre Morel <pmorel@linux.ibm.com>
Cc: Tony Krowiak <akrowiak@linux.ibm.com>
Reported-by: Qian Cai <cailca@icloud.com>
Signed-off-by: Christian Borntraeger <borntraeger@de.ibm.com>
Reviewed-by: David Hildenbrand <david@redhat.com>
Reviewed-by: Cornelia Huck <cohuck@redhat.com>
---
 arch/s390/kvm/priv.c | 4 +++-
 1 file changed, 3 insertions(+), 1 deletion(-)

```
#### [PATCH kvm-unit-tests] KVM: VMX: add test for NMI delivery during HLT
##### From: Paolo Bonzini <pbonzini@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Paolo Bonzini <pbonzini@redhat.com>
X-Patchwork-Id: 11529575
Return-Path: <SRS0=tDSI=6T=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 532521392
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue,  5 May 2020 16:05:18 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 3967D206A4
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue,  5 May 2020 16:05:18 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="CI+NFQ2l"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729129AbgEEQFR (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 5 May 2020 12:05:17 -0400
Received: from us-smtp-2.mimecast.com ([205.139.110.61]:45486 "EHLO
        us-smtp-delivery-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S1727857AbgEEQFQ (ORCPT
        <rfc822;kvm@vger.kernel.org>); Tue, 5 May 2020 12:05:16 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1588694716;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc; bh=1P0XjrMx5eDbaL/X8oZDAXirrwhtoaVOjEod/dPnNfY=;
        b=CI+NFQ2l/zJKVkd2DsiX7u1UFdSmuCdGfqtmXS2nIAukGz5Tnk/vPMIa1DK+5XI1IIlJs7
        V7tLWc8eCyKu3ExSODPGdFPdLI46tWrQe8zC0DlqY4WtezIPrCuTPJ22AuSesyW6DIm0Vt
        y4zukZCtrdvKzg3HqJZrta7RbqjQqyg=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-32-XAMvVEqzMvK6tBHc4aA89w-1; Tue, 05 May 2020 12:05:14 -0400
X-MC-Unique: XAMvVEqzMvK6tBHc4aA89w-1
Received: from smtp.corp.redhat.com (int-mx05.intmail.prod.int.phx2.redhat.com
 [10.5.11.15])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 8C39780183C
        for <kvm@vger.kernel.org>; Tue,  5 May 2020 16:05:13 +0000 (UTC)
Received: from virtlab701.virt.lab.eng.bos.redhat.com
 (virtlab701.virt.lab.eng.bos.redhat.com [10.19.152.228])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 4581662482;
        Tue,  5 May 2020 16:05:13 +0000 (UTC)
From: Paolo Bonzini <pbonzini@redhat.com>
To: kvm@vger.kernel.org
Cc: Cathy Avery <cavery@redhat.com>
Subject: [PATCH kvm-unit-tests] KVM: VMX: add test for NMI delivery during HLT
Date: Tue,  5 May 2020 12:05:12 -0400
Message-Id: <20200505160512.22845-1-pbonzini@redhat.com>
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.15
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Cathy Avery <cavery@redhat.com>

Signed-off-by: Cathy Avery <cavery@redhat.com>
Signed-off-by: Paolo Bonzini <pbonzini@redhat.com>
---
 x86/vmx_tests.c | 120 ++++++++++++++++++++++++++++++++++++++++++++++++
 1 file changed, 120 insertions(+)

```
#### [PATCH] KVM: X86: Declare KVM_CAP_SET_GUEST_DEBUG properly
##### From: Peter Xu <peterx@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Peter Xu <peterx@redhat.com>
X-Patchwork-Id: 11529565
Return-Path: <SRS0=tDSI=6T=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 6B8F115AB
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue,  5 May 2020 15:48:00 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 53B722078D
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue,  5 May 2020 15:48:00 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="G/NxtHkz"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1730169AbgEEPr7 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 5 May 2020 11:47:59 -0400
Received: from us-smtp-delivery-1.mimecast.com ([205.139.110.120]:54860 "EHLO
        us-smtp-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org
        with ESMTP id S1729569AbgEEPr6 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 5 May 2020 11:47:58 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1588693677;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=EQ23tM5kMyn811fS97lNvm/DAC1rh32RC7gp61B/0ws=;
        b=G/NxtHkzBV4UitB7b8BupWaK+oJ4B+tvYn71++9gYEKYuT4yvfdpTWB+4/JVqv4uB0XL7u
        /m/6ViANMTy3z0HSJzJspeWX8yP0lJHEFNLM7Wnfr0CQXZeaG6DSqD8LrlHEri/DDKBg2O
        dfUlk3I4ioORLfEIR/7rizOj+HHnHug=
Received: from mail-qt1-f197.google.com (mail-qt1-f197.google.com
 [209.85.160.197]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-206-ekGlSkOgPRm2NexKPgRNDw-1; Tue, 05 May 2020 11:47:53 -0400
X-MC-Unique: ekGlSkOgPRm2NexKPgRNDw-1
Received: by mail-qt1-f197.google.com with SMTP id q43so2114054qtj.11
        for <kvm@vger.kernel.org>; Tue, 05 May 2020 08:47:53 -0700 (PDT)
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:mime-version
         :content-transfer-encoding;
        bh=EQ23tM5kMyn811fS97lNvm/DAC1rh32RC7gp61B/0ws=;
        b=KwLCTfjcvcopc34KHghMGC2GB8oF62NoE5rnHozwRoSYigtOWViY+qiIuxcYPly8nK
         j64ufjKw/qbG4d+aoY54xKjf0P+enHRBL3pAUVJ/JCdSohDWjqRGYKHsZ3h0oLhpZz0I
         v1Bl1uMlR+an223DrF2hAlZosiUFOmvvxGofjcy8yeyzn5MbsFCUuKlX7r+nU94gzx9H
         qHU5wf+WcT6ClXy0l8l4XugV+eixyZfHmyY3qJtJPcv3oNAp2pC7wtpkhBXymPlpUBjo
         GvuE1TXT4WuWHLyqCnDCgUuTKvD56vxzqGcgNMppWZj9OkKWB2+H8Nbtc56m8bHZ7LOz
         3kzg==
X-Gm-Message-State: AGi0PubzXcnqU1PpOEG9FkBXhtST7sZZLD2G3K57waGPZtC12KmxiWEs
        IoHLs4IHBu6EAga/sfQ3Za2yaBFaL10GFJRiZpnLHbEhoSLKfUezLKu2RMJp5OI0IKVPvZ+4zaK
        KSQLL2dfROlFt
X-Received: by 2002:a37:af05:: with SMTP id y5mr4261809qke.471.1588693672989;
        Tue, 05 May 2020 08:47:52 -0700 (PDT)
X-Google-Smtp-Source: 
 APiQypLoIwGDPk77az/a2DrITfutNeyY8xsNdsMX2fUvJgFNvtmn7qg0F/iELQj44ngrT8/uGNZ7sg==
X-Received: by 2002:a37:af05:: with SMTP id y5mr4261783qke.471.1588693672668;
        Tue, 05 May 2020 08:47:52 -0700 (PDT)
Received: from xz-x1.redhat.com ([2607:9880:19c0:32::2])
        by smtp.gmail.com with ESMTPSA id
 u5sm2081443qkm.116.2020.05.05.08.47.51
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Tue, 05 May 2020 08:47:52 -0700 (PDT)
From: Peter Xu <peterx@redhat.com>
To: kvm@vger.kernel.org, linux-kernel@vger.kernel.org
Cc: Paolo Bonzini <pbonzini@redhat.com>, peterx@redhat.com,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>
Subject: [PATCH] KVM: X86: Declare KVM_CAP_SET_GUEST_DEBUG properly
Date: Tue,  5 May 2020 11:47:50 -0400
Message-Id: <20200505154750.126300-1-peterx@redhat.com>
X-Mailer: git-send-email 2.26.2
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

KVM_CAP_SET_GUEST_DEBUG should be supported for x86 however it's not declared
as supported.  My wild guess is that userspaces like QEMU are using "#ifdef
KVM_CAP_SET_GUEST_DEBUG" to check for the capability instead, but that could be
wrong because the compilation host may not be the runtime host.

The userspace might still want to keep the old "#ifdef" though to not break the
guest debug on old kernels.

Signed-off-by: Peter Xu <peterx@redhat.com>
---

I also think both ppc and s390 may need similar thing, but I didn't touch them
yet because of not confident enough to cover all cases.
---
 arch/x86/kvm/x86.c | 1 +
 1 file changed, 1 insertion(+)

```
#### [PATCH] KVM: x86: fix DR6 delivery for emulated hardware breakpoint
##### From: Paolo Bonzini <pbonzini@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Paolo Bonzini <pbonzini@redhat.com>
X-Patchwork-Id: 11528829
Return-Path: <SRS0=tDSI=6T=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 8E2A381
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue,  5 May 2020 11:34:58 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 7684620735
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue,  5 May 2020 11:34:58 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="PFoA7c2R"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728655AbgEELe5 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 5 May 2020 07:34:57 -0400
Received: from us-smtp-delivery-1.mimecast.com ([207.211.31.120]:49260 "EHLO
        us-smtp-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org
        with ESMTP id S1728233AbgEELe5 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 5 May 2020 07:34:57 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1588678496;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc; bh=kf2bz/b6u5ATikbzlOoZD3Be2rrM+5Ro0erR1f3eNfM=;
        b=PFoA7c2Rxj+KRXe4vYUs8AjTZOg6wpMChDdlK2cMueELWtqqaVV7tv02msat7TDp4vurTy
        wLifBTSywS7wiCq5zj4uoQsV89c6fX/dhthptG6r3sKWnAbL0/eyXiTk5M6icB4UCMeVwg
        aqkiqXed6Kx+F8dsaEkJvzUx3qQJhXo=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-339-TiiQpC0sMOaoVXL-Jk0a2Q-1; Tue, 05 May 2020 07:34:54 -0400
X-MC-Unique: TiiQpC0sMOaoVXL-Jk0a2Q-1
Received: from smtp.corp.redhat.com (int-mx06.intmail.prod.int.phx2.redhat.com
 [10.5.11.16])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 98682835B40;
        Tue,  5 May 2020 11:34:53 +0000 (UTC)
Received: from virtlab701.virt.lab.eng.bos.redhat.com
 (virtlab701.virt.lab.eng.bos.redhat.com [10.19.152.228])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 5930A5C1B2;
        Tue,  5 May 2020 11:34:50 +0000 (UTC)
From: Paolo Bonzini <pbonzini@redhat.com>
To: linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Cc: jmattson@google.com, peterx@redhat.com
Subject: [PATCH] KVM: x86: fix DR6 delivery for emulated hardware breakpoint
Date: Tue,  5 May 2020 07:34:49 -0400
Message-Id: <20200505113449.18478-1-pbonzini@redhat.com>
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.16
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Go through kvm_queue_exception_p so that the payload is correctly delivered
through the exit qualification, and add a kvm_update_dr6 call to
kvm_deliver_exception_payload that is needed on AMD.

Signed-off-by: Paolo Bonzini <pbonzini@redhat.com>
Reviewed-by: Peter Xu <peterx@redhat.com>
---
 arch/x86/kvm/x86.c | 5 ++---
 1 file changed, 2 insertions(+), 3 deletions(-)

```
#### [PATCH 1/3] KVM: X86: Set RTM for DB_VECTOR too for KVM_EXIT_DEBUG
##### From: Peter Xu <peterx@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Peter Xu <peterx@redhat.com>
X-Patchwork-Id: 11529873
Return-Path: <SRS0=tDSI=6T=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id D715115E6
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue,  5 May 2020 20:50:09 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id BCB3C20735
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue,  5 May 2020 20:50:09 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="bgsy7smi"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729224AbgEEUuI (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 5 May 2020 16:50:08 -0400
Received: from us-smtp-1.mimecast.com ([207.211.31.81]:41102 "EHLO
        us-smtp-delivery-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S1729194AbgEEUuI (ORCPT
        <rfc822;kvm@vger.kernel.org>); Tue, 5 May 2020 16:50:08 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1588711807;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding:
         in-reply-to:in-reply-to:references:references;
        bh=y5fyKyck3cIU7DcvHTGzyMWNl4dUwB0H2Ul/b+bN2co=;
        b=bgsy7smivUCohNb0VZ9RyAAn09/wbXmp09VCksd36uz9Q4Vp3oqUw//bTfzTjEZVSILFXQ
        6sECyTHw8ES4T2niXhR3YIeBWiRIsUneRVIpev86AgzJ1QkFhG8nvRwRoxr2ylNrquQdjd
        WxFgRQxlo99aOu4WKRuveZ/yxZrZ+8Q=
Received: from mail-qv1-f70.google.com (mail-qv1-f70.google.com
 [209.85.219.70]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-245-JyQxmu5xOdyd8lcPcWZ5mg-1; Tue, 05 May 2020 16:50:05 -0400
X-MC-Unique: JyQxmu5xOdyd8lcPcWZ5mg-1
Received: by mail-qv1-f70.google.com with SMTP id ev8so3501117qvb.7
        for <kvm@vger.kernel.org>; Tue, 05 May 2020 13:50:05 -0700 (PDT)
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:in-reply-to
         :references:mime-version:content-transfer-encoding;
        bh=y5fyKyck3cIU7DcvHTGzyMWNl4dUwB0H2Ul/b+bN2co=;
        b=AtBIm26NB5dX8FA65z2Lb3orTXq9uM9Ya94nZ3qMMxbfTpjUNXnhaPt5zG80/0F8Q2
         OtJ6bBJoSFS3IkczXfXeZH8R1jrnpBiZ1Fxn9pZcxBfao01mcyEh6qjgf+0C8UUCX4lQ
         H9RW73gtXgPxeqQSn8823bq+oN0cfpIghMtTmOjRVg1caVaNisUaiwSHT69SEobWctM0
         lUKaOdYmAORAXhusLvTr5/CkTihFc+dv2BwiJe4ArkzLTT3lePiuRAkYO/TCFJurRqRW
         4To9IgrwUpy1RyWsmYIjsdarH4UKOFtdqIObsVkC7Zp+AyAqm7BXIO3iHfWMiLQaaJyu
         vwqA==
X-Gm-Message-State: AGi0PuZJdBCjJLVssSGW9Egrc5OCdApfYDCCBtZTsNs/AGphkxiqWaJN
        NMalOIipGAsUudTurcjQyi2x+TLDySI3C5xANraUB2WiguCyzhpG+lqf0lblvk0hsTH+QC/bC/a
        J7iHpUSUynX68
X-Received: by 2002:ac8:3f6d:: with SMTP id w42mr4732571qtk.171.1588711804403;
        Tue, 05 May 2020 13:50:04 -0700 (PDT)
X-Google-Smtp-Source: 
 APiQypLOTQWzwWYM8fE/nDb/teAnnAv0eA3zDhbPGnwIcj7jk9BsG2W3T+3JWJxBw9ko1tMQ6r44Lw==
X-Received: by 2002:ac8:3f6d:: with SMTP id w42mr4732555qtk.171.1588711804173;
        Tue, 05 May 2020 13:50:04 -0700 (PDT)
Received: from xz-x1.redhat.com ([2607:9880:19c0:32::2])
        by smtp.gmail.com with ESMTPSA id 193sm19380qkl.42.2020.05.05.13.50.02
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Tue, 05 May 2020 13:50:03 -0700 (PDT)
From: Peter Xu <peterx@redhat.com>
To: linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Cc: Vitaly Kuznetsov <vkuznets@redhat.com>,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        peterx@redhat.com, Paolo Bonzini <pbonzini@redhat.com>
Subject: [PATCH 1/3] KVM: X86: Set RTM for DB_VECTOR too for KVM_EXIT_DEBUG
Date: Tue,  5 May 2020 16:49:58 -0400
Message-Id: <20200505205000.188252-2-peterx@redhat.com>
X-Mailer: git-send-email 2.26.2
In-Reply-To: <20200505205000.188252-1-peterx@redhat.com>
References: <20200505205000.188252-1-peterx@redhat.com>
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

RTM should always been set even with KVM_EXIT_DEBUG on #DB.

Signed-off-by: Peter Xu <peterx@redhat.com>
---
 arch/x86/kvm/vmx/vmx.c | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
#### [PATCH v3 24/25] samples: vfio-mdev/mbochs: fix common struct sg_table related issues
##### From: Marek Szyprowski <m.szyprowski@samsung.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Marek Szyprowski <m.szyprowski@samsung.com>
X-Patchwork-Id: 11528469
Return-Path: <SRS0=tDSI=6T=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 68ACD14C0
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue,  5 May 2020 08:47:02 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 4A40221775
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue,  5 May 2020 08:47:02 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=samsung.com header.i=@samsung.com
 header.b="omkg7R3W"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728775AbgEEIqy (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 5 May 2020 04:46:54 -0400
Received: from mailout2.w1.samsung.com ([210.118.77.12]:52056 "EHLO
        mailout2.w1.samsung.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1728726AbgEEIql (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 5 May 2020 04:46:41 -0400
Received: from eucas1p2.samsung.com (unknown [182.198.249.207])
        by mailout2.w1.samsung.com (KnoxPortal) with ESMTP id
 20200505084639euoutp02edcb88b0f49e06356f74b8af501ccd58~MFX3qheiD2627826278euoutp02z
        for <kvm@vger.kernel.org>; Tue,  5 May 2020 08:46:39 +0000 (GMT)
DKIM-Filter: OpenDKIM Filter v2.11.0 mailout2.w1.samsung.com
 20200505084639euoutp02edcb88b0f49e06356f74b8af501ccd58~MFX3qheiD2627826278euoutp02z
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=samsung.com;
        s=mail20170921; t=1588668399;
        bh=TxE/6G1g28mmKh7hooUAC2aT+D+6azanETRBOwRYElg=;
        h=From:To:Cc:Subject:Date:In-Reply-To:References:From;
        b=omkg7R3W/3Q2Bl+cb32xRIYW7VX/up76W1blrssWmzK4/YV9vkZmGlUAHrftdH/ky
         sBm3jWLZP1zBzJJT1oktuawgrGb+xZ++K3Cust+asUCXnN8sc9seby6u1Iz1mdAPcQ
         6J8uGx4WXNmvPiCCXkEoHiF7i93T48TUIMuyi/8U=
Received: from eusmges2new.samsung.com (unknown [203.254.199.244]) by
        eucas1p1.samsung.com (KnoxPortal) with ESMTP id
        20200505084638eucas1p14d6b13af09eff6253e2019c1163d2ea3~MFX3YaiQa2425224252eucas1p1F;
        Tue,  5 May 2020 08:46:38 +0000 (GMT)
Received: from eucas1p1.samsung.com ( [182.198.249.206]) by
        eusmges2new.samsung.com (EUCPMTA) with SMTP id 54.42.60679.EE721BE5;
 Tue,  5
        May 2020 09:46:38 +0100 (BST)
Received: from eusmtrp1.samsung.com (unknown [182.198.249.138]) by
        eucas1p2.samsung.com (KnoxPortal) with ESMTPA id
        20200505084638eucas1p24f356b441a3589e9528d239c0b9ac666~MFX28WU0-1948219482eucas1p2b;
        Tue,  5 May 2020 08:46:38 +0000 (GMT)
Received: from eusmgms1.samsung.com (unknown [182.198.249.179]) by
        eusmtrp1.samsung.com (KnoxPortal) with ESMTP id
        20200505084638eusmtrp186bd6d7ec444ca0de6918ea0b42f52cb~MFX27rb8P0969409694eusmtrp1G;
        Tue,  5 May 2020 08:46:38 +0000 (GMT)
X-AuditID: cbfec7f4-0e5ff7000001ed07-58-5eb127ee86c4
Received: from eusmtip1.samsung.com ( [203.254.199.221]) by
        eusmgms1.samsung.com (EUCPMTA) with SMTP id A1.24.08375.EE721BE5;
 Tue,  5
        May 2020 09:46:38 +0100 (BST)
Received: from AMDC2765.digital.local (unknown [106.120.51.73]) by
        eusmtip1.samsung.com (KnoxPortal) with ESMTPA id
        20200505084637eusmtip174e6b9fe26a7b71a38ddfeb81a667898~MFX2aZfgP0580805808eusmtip1C;
        Tue,  5 May 2020 08:46:37 +0000 (GMT)
From: Marek Szyprowski <m.szyprowski@samsung.com>
To: dri-devel@lists.freedesktop.org, iommu@lists.linux-foundation.org,
        linaro-mm-sig@lists.linaro.org, linux-kernel@vger.kernel.org
Cc: Marek Szyprowski <m.szyprowski@samsung.com>,
        Christoph Hellwig <hch@lst.de>,
        Robin Murphy <robin.murphy@arm.com>,
        Bartlomiej Zolnierkiewicz <b.zolnierkie@samsung.com>,
        linux-arm-kernel@lists.infradead.org,
        David Airlie <airlied@linux.ie>,
        Daniel Vetter <daniel@ffwll.ch>,
        Kirti Wankhede <kwankhede@nvidia.com>, kvm@vger.kernel.org
Subject: [PATCH v3 24/25] samples: vfio-mdev/mbochs: fix common struct
 sg_table related issues
Date: Tue,  5 May 2020 10:46:13 +0200
Message-Id: <20200505084614.30424-24-m.szyprowski@samsung.com>
X-Mailer: git-send-email 2.17.1
In-Reply-To: <20200505084614.30424-1-m.szyprowski@samsung.com>
X-Brightmail-Tracker: 
 H4sIAAAAAAAAA0VSa0hTYRjmO7edTSenafhhkTDIMEjTJA4YZuCPE4hFEYaVecqDl9y0zVku
        SmkosZx4KROvQzKvc9PUeSHU5TVBRMW0LJP5J2tecomZaZsH699ze9/n5eMjUUkb7kUmyFM5
        hZxNkhIirH3w19iJ5WPN0ScLKvxp3dgIQjcXG3F6tz0fpad+rhB0XcMAQut7gumy53fp1tFy
        QNunFhC6xTqN05NdZQRt6P8koPtWF/FQMdNY0QiYNxt6jDFvfMGZ+adDCPP6ZQbzcceKMoUz
        NYDpns0kGJ1mmWByW+sBs95y5KJLlOhMLJeUkMYp/ENiRPGzVVlYitnt/nDZWzwT5LhqgZCE
        VBDMqm4mtEBESqhaADs2DbjTkFB2ALsqhbyxDuBW+ziyP/H5R72AN2oAzLUaMJ44JpqWnhHO
        FEEFQK1Nu4c9qCwAh3WuzhBKTSPQ9md5r8OdioH2ueo9jFFHoeZ3EebEYioEduvacL7OGzaY
        elEnFjp068Tc3rGQGhTAfsuM4w7SQcJg7bKKz7vDpaFWAY8Pw9HCHIzPawBcGDMIeJID4OTj
        YsCnguHc2BbhXIRSvtDY5c/L56B2Y5Lg97vBGdsBp4w6YEH7C5SXxfBJtoRP+8CSoaZ/tX3j
        EyiPGdihK0f4BxoA8FvnNp4HvEv+l+kBqAeenEopi+OUgXLunp+SlSlV8ji/28myFuD4TKM7
        Q/YO0LV9ywIoEkhdxVfXjdESnE1TpsssAJKo1EP8atMULRHHsulqTpF8U6FK4pQWcIjEpJ7i
        U1Vfb0ioODaVu8NxKZxi30VIoVcmuD59xdOXuyDUtLi72gK9Dk7YXUJDdksLY2cNlS+ljfLz
        a8YPrCg/rzCMLE3vaauJnI84PZzNvFttCnp4afOyLUKv3vierk40g7pJtQaPmusuD/fpdFs0
        XRsxv1eZM4rid1WayhnfLWO1XZIYzvaeHX2wsiZzMyVK4aOiyEgppoxnA46jCiX7Fz5EzGxI
        AwAA
X-Brightmail-Tracker: 
 H4sIAAAAAAAAA+NgFprOIsWRmVeSWpSXmKPExsVy+t/xu7rv1DfGGey5L2jRe+4kk8XGGetZ
        Lf5vm8hsceXrezaLlauPMlks2G9tMWdqocWW03MZLb5cechksenxNVaLy7vmsFmsPXKX3eLg
        hyesDrwea+atYfTY+20Bi8f2bw9YPe53H2fy2Lyk3uP2v8fMHpNvLGf02H2zgc2jt/kdm0ff
        llWMHp83yQVwR+nZFOWXlqQqZOQXl9gqRRtaGOkZWlroGZlY6hkam8daGZkq6dvZpKTmZJal
        FunbJehl3FzUylKwna/ixJzDrA2MPTxdjJwcEgImEvc+rWLvYuTiEBJYyiix//ouFoiEjMTJ
        aQ2sELawxJ9rXWwQRZ8YJR6f/whWxCZgKNH1FiIhItDJKDGt+yM7SIJZ4B6TxN51fiC2sECc
        xNrNcxlBbBYBVYnm39PAmnkF7CR2926F2iAvsXrDAWYQmxMo/vjSHTYQW0igUOLD+e+sExj5
        FjAyrGIUSS0tzk3PLTbUK07MLS7NS9dLzs/dxAiMlG3Hfm7ewXhpY/AhRgEORiUe3ojP6+OE
        WBPLiitzDzFKcDArifAu+7EhTog3JbGyKrUoP76oNCe1+BCjKdBRE5mlRJPzgVGcVxJvaGpo
        bmFpaG5sbmxmoSTO2yFwMEZIID2xJDU7NbUgtQimj4mDU6qB0WDZBFGvy0efej3/vNFwUvnq
        7Y+P9t25sOyPjaDdzg/1fZuuaMVvUF+4KkRLeLIi5+sLf9/O2pJYzcG2yXqzaPG561YH8sIS
        NuxL+OLNGrR760KPOes3HzKO4fEpKTeN2Za65cTOG4vi7GYL2K1Yv7u5N4dpuUzs+Y6jqd9f
        fjj96Kcd58uVivOUWIozEg21mIuKEwHQUyHvqgIAAA==
X-CMS-MailID: 20200505084638eucas1p24f356b441a3589e9528d239c0b9ac666
X-Msg-Generator: CA
X-RootMTR: 20200505084638eucas1p24f356b441a3589e9528d239c0b9ac666
X-EPHeader: CA
CMS-TYPE: 201P
X-CMS-RootMailID: 20200505084638eucas1p24f356b441a3589e9528d239c0b9ac666
References: <20200505083926.28503-1-m.szyprowski@samsung.com>
        <20200505084614.30424-1-m.szyprowski@samsung.com>
        <CGME20200505084638eucas1p24f356b441a3589e9528d239c0b9ac666@eucas1p2.samsung.com>
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The Documentation/DMA-API-HOWTO.txt states that dma_map_sg returns the
numer of the created entries in the DMA address space. However the
subsequent calls to dma_sync_sg_for_{device,cpu} and dma_unmap_sg must be
called with the original number of the entries passed to dma_map_sg. The
sg_table->nents in turn holds the result of the dma_map_sg call as stated
in include/linux/scatterlist.h. A common mistake was to ignore a result
of the dma_map_sg function and don't use the sg_table->orig_nents at all.

To avoid such issues, lets use common dma-mapping wrappers operating
directly on the struct sg_table objects and adjust references to the
nents and orig_nents respectively.

While touching this code, also add missing call to dma_unmap_sgtable.

Signed-off-by: Marek Szyprowski <m.szyprowski@samsung.com>
---
For more information, see '[PATCH v3 00/25] DRM: fix struct sg_table nents
vs. orig_nents misuse' thread: https://lkml.org/lkml/2020/5/5/187
---
 samples/vfio-mdev/mbochs.c | 3 ++-
 1 file changed, 2 insertions(+), 1 deletion(-)

```
#### [PATCH v4 2/8] vfio-ccw: Register a chp_event callback for vfio-ccw
##### From: Eric Farman <farman@linux.ibm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Eric Farman <farman@linux.ibm.com>
X-Patchwork-Id: 11528905
Return-Path: <SRS0=tDSI=6T=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id E98E31668
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue,  5 May 2020 12:27:52 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id DB212206B8
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue,  5 May 2020 12:27:52 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728802AbgEEM1w (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 5 May 2020 08:27:52 -0400
Received: from mx0b-001b2d01.pphosted.com ([148.163.158.5]:7292 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S1727090AbgEEM1v (ORCPT
        <rfc822;kvm@vger.kernel.org>); Tue, 5 May 2020 08:27:51 -0400
Received: from pps.filterd (m0098419.ppops.net [127.0.0.1])
        by mx0b-001b2d01.pphosted.com (8.16.0.42/8.16.0.42) with SMTP id
 045CRKtL098218;
        Tue, 5 May 2020 08:27:50 -0400
Received: from pps.reinject (localhost [127.0.0.1])
        by mx0b-001b2d01.pphosted.com with ESMTP id 30s1swv7fc-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Tue, 05 May 2020 08:27:50 -0400
Received: from m0098419.ppops.net (m0098419.ppops.net [127.0.0.1])
        by pps.reinject (8.16.0.36/8.16.0.36) with SMTP id 045CRoHI100467;
        Tue, 5 May 2020 08:27:50 -0400
Received: from ppma04ams.nl.ibm.com (63.31.33a9.ip4.static.sl-reverse.com
 [169.51.49.99])
        by mx0b-001b2d01.pphosted.com with ESMTP id 30s1swv7ea-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Tue, 05 May 2020 08:27:49 -0400
Received: from pps.filterd (ppma04ams.nl.ibm.com [127.0.0.1])
        by ppma04ams.nl.ibm.com (8.16.0.27/8.16.0.27) with SMTP id
 045CQKrh023113;
        Tue, 5 May 2020 12:27:48 GMT
Received: from b06avi18626390.portsmouth.uk.ibm.com
 (b06avi18626390.portsmouth.uk.ibm.com [9.149.26.192])
        by ppma04ams.nl.ibm.com with ESMTP id 30s0g5pwks-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Tue, 05 May 2020 12:27:48 +0000
Received: from b06wcsmtp001.portsmouth.uk.ibm.com
 (b06wcsmtp001.portsmouth.uk.ibm.com [9.149.105.160])
        by b06avi18626390.portsmouth.uk.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id 045CQZ5X57344370
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Tue, 5 May 2020 12:26:35 GMT
Received: from b06wcsmtp001.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 6EA6CA405F;
        Tue,  5 May 2020 12:27:45 +0000 (GMT)
Received: from b06wcsmtp001.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 5D638A405B;
        Tue,  5 May 2020 12:27:45 +0000 (GMT)
Received: from tuxmaker.boeblingen.de.ibm.com (unknown [9.152.85.9])
        by b06wcsmtp001.portsmouth.uk.ibm.com (Postfix) with ESMTPS;
        Tue,  5 May 2020 12:27:45 +0000 (GMT)
Received: by tuxmaker.boeblingen.de.ibm.com (Postfix, from userid 4958)
        id 1B1A3E065C; Tue,  5 May 2020 14:27:45 +0200 (CEST)
From: Eric Farman <farman@linux.ibm.com>
To: linux-s390@vger.kernel.org, kvm@vger.kernel.org
Cc: Cornelia Huck <cohuck@redhat.com>,
        Halil Pasic <pasic@linux.ibm.com>,
        Jason Herne <jjherne@linux.ibm.com>,
        Jared Rossi <jrossi@linux.ibm.com>,
        Eric Farman <farman@linux.ibm.com>
Subject: [PATCH v4 2/8] vfio-ccw: Register a chp_event callback for vfio-ccw
Date: Tue,  5 May 2020 14:27:39 +0200
Message-Id: <20200505122745.53208-3-farman@linux.ibm.com>
X-Mailer: git-send-email 2.17.1
In-Reply-To: <20200505122745.53208-1-farman@linux.ibm.com>
References: <20200505122745.53208-1-farman@linux.ibm.com>
X-TM-AS-GCONF: 00
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.138,18.0.676
 definitions=2020-05-05_06:2020-05-04,2020-05-05 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 priorityscore=1501
 lowpriorityscore=0 malwarescore=0 phishscore=0 adultscore=0
 impostorscore=0 mlxlogscore=999 bulkscore=0 clxscore=1015 suspectscore=0
 mlxscore=0 spamscore=0 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.12.0-2003020000 definitions=main-2005050093
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Farhan Ali <alifm@linux.ibm.com>

Register the chp_event callback to receive channel path related
events for the subchannels managed by vfio-ccw.

Signed-off-by: Farhan Ali <alifm@linux.ibm.com>
Signed-off-by: Eric Farman <farman@linux.ibm.com>
---

Notes:
    v3->v4:
     - Check schib.lpum before calling cio_cancel_halt_clear [CH]
    
    v2->v3:
     - Add a call to cio_cancel_halt_clear() for CHP_VARY_OFF [CH]
    
    v1->v2:
     - Move s390dbf before cio_update_schib() call [CH]
    
    v0->v1: [EF]
     - Add s390dbf trace

 drivers/s390/cio/vfio_ccw_drv.c | 47 +++++++++++++++++++++++++++++++++
 1 file changed, 47 insertions(+)

```
#### [PATCH v2] KVM: s390: Remove false WARN_ON_ONCE for the PQAP instruction
##### From: Christian Borntraeger <borntraeger@de.ibm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Christian Borntraeger <borntraeger@de.ibm.com>
X-Patchwork-Id: 11528419
Return-Path: <SRS0=tDSI=6T=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id B2B6D912
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue,  5 May 2020 08:35:23 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id A4728206B9
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue,  5 May 2020 08:35:23 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728114AbgEEIfW (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 5 May 2020 04:35:22 -0400
Received: from mx0a-001b2d01.pphosted.com ([148.163.156.1]:48750 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1725320AbgEEIfW (ORCPT
        <rfc822;kvm@vger.kernel.org>); Tue, 5 May 2020 04:35:22 -0400
Received: from pps.filterd (m0098394.ppops.net [127.0.0.1])
        by mx0a-001b2d01.pphosted.com (8.16.0.42/8.16.0.42) with SMTP id
 0458XNOJ105030;
        Tue, 5 May 2020 04:35:21 -0400
Received: from pps.reinject (localhost [127.0.0.1])
        by mx0a-001b2d01.pphosted.com with ESMTP id 30twhwtw7p-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Tue, 05 May 2020 04:35:21 -0400
Received: from m0098394.ppops.net (m0098394.ppops.net [127.0.0.1])
        by pps.reinject (8.16.0.36/8.16.0.36) with SMTP id 0458Z9PF116172;
        Tue, 5 May 2020 04:35:21 -0400
Received: from ppma04fra.de.ibm.com (6a.4a.5195.ip4.static.sl-reverse.com
 [149.81.74.106])
        by mx0a-001b2d01.pphosted.com with ESMTP id 30twhwtw6p-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Tue, 05 May 2020 04:35:21 -0400
Received: from pps.filterd (ppma04fra.de.ibm.com [127.0.0.1])
        by ppma04fra.de.ibm.com (8.16.0.27/8.16.0.27) with SMTP id
 0458UVQO007078;
        Tue, 5 May 2020 08:35:19 GMT
Received: from b06cxnps4075.portsmouth.uk.ibm.com
 (d06relay12.portsmouth.uk.ibm.com [9.149.109.197])
        by ppma04fra.de.ibm.com with ESMTP id 30s0g62mqn-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Tue, 05 May 2020 08:35:18 +0000
Received: from d06av22.portsmouth.uk.ibm.com (d06av22.portsmouth.uk.ibm.com
 [9.149.105.58])
        by b06cxnps4075.portsmouth.uk.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id 0458ZG9r25166036
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Tue, 5 May 2020 08:35:16 GMT
Received: from d06av22.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 3A84A4C04E;
        Tue,  5 May 2020 08:35:16 +0000 (GMT)
Received: from d06av22.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 32C6F4C046;
        Tue,  5 May 2020 08:35:16 +0000 (GMT)
Received: from tuxmaker.boeblingen.de.ibm.com (unknown [9.152.85.9])
        by d06av22.portsmouth.uk.ibm.com (Postfix) with ESMTPS;
        Tue,  5 May 2020 08:35:16 +0000 (GMT)
Received: by tuxmaker.boeblingen.de.ibm.com (Postfix, from userid 25651)
        id BE122E0605; Tue,  5 May 2020 10:35:15 +0200 (CEST)
From: Christian Borntraeger <borntraeger@de.ibm.com>
To: Janosch Frank <frankja@linux.vnet.ibm.com>
Cc: KVM <kvm@vger.kernel.org>, Cornelia Huck <cohuck@redhat.com>,
        Christian Borntraeger <borntraeger@de.ibm.com>,
        David Hildenbrand <david@redhat.com>,
        linux-s390 <linux-s390@vger.kernel.org>,
        Qian Cai <cailca@icloud.com>,
        Pierre Morel <pmorel@linux.ibm.com>,
        Tony Krowiak <akrowiak@linux.ibm.com>
Subject: [PATCH v2] KVM: s390: Remove false WARN_ON_ONCE for the PQAP
 instruction
Date: Tue,  5 May 2020 10:35:15 +0200
Message-Id: <20200505083515.2720-1-borntraeger@de.ibm.com>
X-Mailer: git-send-email 2.25.4
MIME-Version: 1.0
X-TM-AS-GCONF: 00
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.138,18.0.676
 definitions=2020-05-05_04:2020-05-04,2020-05-05 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 mlxlogscore=999
 priorityscore=1501 lowpriorityscore=0 bulkscore=0 spamscore=0 phishscore=0
 malwarescore=0 impostorscore=0 suspectscore=0 mlxscore=0 clxscore=1015
 adultscore=0 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.12.0-2003020000 definitions=main-2005050069
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

In LPAR we will only get an intercept for FC==3 for the PQAP
instruction. Running nested under z/VM can result in other intercepts as
well as ECA_APIE is an effective bit: If one hypervisor layer has
turned this bit off, the end result will be that we will get intercepts for
all function codes. Usually the first one will be a query like PQAP(QCI).
So the WARN_ON_ONCE is not right. Let us simply remove it.

Cc: Pierre Morel <pmorel@linux.ibm.com>
Cc: Tony Krowiak <akrowiak@linux.ibm.com>
Cc: stable@vger.kernel.org
Link: https://lore.kernel.org/kvm/20200505073525.2287-1-borntraeger@de.ibm.com
Reported-by: Qian Cai <cailca@icloud.com>
Signed-off-by: Christian Borntraeger <borntraeger@de.ibm.com>
Reviewed-by: David Hildenbrand <david@redhat.com>
Reviewed-by: Cornelia Huck <cohuck@redhat.com>
---
 arch/s390/kvm/priv.c | 4 +++-
 1 file changed, 3 insertions(+), 1 deletion(-)

```
#### [PATCH v2] vfio-pci: Mask cap zeroFrom: Alex Williamson <alex.williamson@redhat.com>
##### From: Alex Williamson <alex.williamson@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Alex Williamson <alex.williamson@redhat.com>
X-Patchwork-Id: 11530013
Return-Path: <SRS0=tDSI=6T=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id A1EBB15AB
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue,  5 May 2020 22:27:13 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 88DC8206B8
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue,  5 May 2020 22:27:13 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="cxX7Wsqa"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729348AbgEEW1K (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 5 May 2020 18:27:10 -0400
Received: from us-smtp-delivery-1.mimecast.com ([207.211.31.120]:60907 "EHLO
        us-smtp-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org
        with ESMTP id S1727895AbgEEW1J (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 5 May 2020 18:27:09 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1588717628;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:content-type:content-type:
         content-transfer-encoding:content-transfer-encoding;
        bh=m7nBhUhZbP+Z+qbn0o5hwDg4WpYxThNrJoLfGxtRcL8=;
        b=cxX7WsqafQqUlT+pbsJ7NKkChxXcSYSCstoHfH4yQDxBCy+OjHkveFrpF5wbOuDTPqJ7XS
        GS5LccRFemKEKNAv7S1JyLoCicrepswEgdaES7Cofd23pUK0gXUS1yUZKJCl17c9yMmLo3
        u8Hs5LSU0Dqv5jNrYhqO5jT74xj1YqM=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-167-CkLO7d3-OJqY9olCe8Tm5A-1; Tue, 05 May 2020 18:27:06 -0400
X-MC-Unique: CkLO7d3-OJqY9olCe8Tm5A-1
Received: from smtp.corp.redhat.com (int-mx04.intmail.prod.int.phx2.redhat.com
 [10.5.11.14])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 3DD56100A8EA;
        Tue,  5 May 2020 22:27:05 +0000 (UTC)
Received: from gimli.home (ovpn-113-95.phx2.redhat.com [10.3.113.95])
        by smtp.corp.redhat.com (Postfix) with ESMTP id D88355D9DA;
        Tue,  5 May 2020 22:27:01 +0000 (UTC)
Subject: [PATCH v2] vfio-pci: Mask cap zero
From: Alex Williamson <alex.williamson@redhat.com>
To: kvm@vger.kernel.org
Cc: linux-kernel@vger.kernel.org, cohuck@redhat.com, cjia@nvidia.com
Date: Tue, 05 May 2020 16:27:01 -0600
Message-ID: <158871758778.17183.9778359960687348692.stgit@gimli.home>
User-Agent: StGit/0.19-dirty
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.14
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The PCI Code and ID Assignment Specification changed capability ID 0
from reserved to a NULL capability in the v1.1 revision.  The NULL
capability is defined to include only the 16-bit capability header,
ie. only the ID and next pointer.  Unfortunately vfio-pci creates a
map of config space, where ID 0 is used to reserve the standard type
0 header.  Finding an actual capability with this ID therefore results
in a bogus range marked in that map and conflicts with subsequent
capabilities.  As this seems to be a dummy capability anyway and we
already support dropping capabilities, let's hide this one rather than
delving into the potentially subtle dependencies within our map.

Seen on an NVIDIA Tesla T4.

Signed-off-by: Alex Williamson <alex.williamson@redhat.com>
---
 drivers/vfio/pci/vfio_pci_config.c |    7 ++++++-
 1 file changed, 6 insertions(+), 1 deletion(-)

```
#### [PATCH v3] docs/virt/kvm: Document configuring and running nested guests
##### From: Kashyap Chamarthy <kchamart@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 8bit
X-Patchwork-Submitter: Kashyap Chamarthy <kchamart@redhat.com>
X-Patchwork-Id: 11528827
Return-Path: <SRS0=tDSI=6T=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id D917F139F
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue,  5 May 2020 11:28:54 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id B4C6D206B9
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue,  5 May 2020 11:28:54 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="S60OcNZZ"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728514AbgEEL2x (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 5 May 2020 07:28:53 -0400
Received: from us-smtp-2.mimecast.com ([205.139.110.61]:45930 "EHLO
        us-smtp-delivery-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S1725766AbgEEL2x (ORCPT
        <rfc822;kvm@vger.kernel.org>); Tue, 5 May 2020 07:28:53 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1588678130;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:content-type:content-type:
         content-transfer-encoding:content-transfer-encoding;
        bh=pH5v8lnkymv75dSfzGEf3HUvcOnzC2qJ7vr+cN2+9sQ=;
        b=S60OcNZZkVJ7OLXyCQOIxwC+f+oYL5IR4Z4lJsGbnXk89r1488dJ8g/LOjU6On5yFt8sAE
        2gNZbpIIoKIt6I7M8GQHfcQ5EC9DRF63Cy1Ctu2l3Y+JD6UubIftHZQ9cjRbNAvZzkEO9H
        sxxlme1YUFSE9NJ5yJM0fgUnfCTDCVo=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-218-3iuswwebPdyJJlS2QcFZpQ-1; Tue, 05 May 2020 07:28:46 -0400
X-MC-Unique: 3iuswwebPdyJJlS2QcFZpQ-1
Received: from smtp.corp.redhat.com (int-mx02.intmail.prod.int.phx2.redhat.com
 [10.5.11.12])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 3027510766DB
        for <kvm@vger.kernel.org>; Tue,  5 May 2020 11:28:45 +0000 (UTC)
Received: from paraplu.localdomain (unknown [10.36.110.17])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 5112D60BEC;
        Tue,  5 May 2020 11:28:43 +0000 (UTC)
From: Kashyap Chamarthy <kchamart@redhat.com>
To: kvm@vger.kernel.org
Cc: pbonzini@redhat.com, dgilbert@redhat.com, cohuck@redhat.com,
        vkuznets@redhat.com, Kashyap Chamarthy <kchamart@redhat.com>
Subject: [PATCH v3] docs/virt/kvm: Document configuring and running nested
 guests
Date: Tue,  5 May 2020 13:28:39 +0200
Message-Id: <20200505112839.30534-1-kchamart@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.12
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This is a rewrite of this[1] Wiki page with further enhancements.  The
doc also includes a section on debugging problems in nested
environments, among other improvements.

[1] https://www.linux-kvm.org/page/Nested_Guests

Signed-off-by: Kashyap Chamarthy <kchamart@redhat.com>
---
- In v3:
  - Address feedback from Paolo and Cornelia from v2:
    https://marc.info/?t=158738155500003&r=1&w=2

- In v2:
  - Address Cornelia's feedback v1:
    https://marc.info/?l=kvm&m=158109042605606&w=2
  - Address Dave's feedback from v1:
    https://marc.info/?l=kvm&m=158109134905930&w=2

- v1 is here: https://marc.info/?l=kvm&m=158108941605311&w=2
---
 .../virt/kvm/running-nested-guests.rst        | 287 ++++++++++++++++++
 1 file changed, 287 insertions(+)
 create mode 100644 Documentation/virt/kvm/running-nested-guests.rst

diff --git a/Documentation/virt/kvm/running-nested-guests.rst b/Documentation/virt/kvm/running-nested-guests.rst
new file mode 100644
index 0000000000000000000000000000000000000000..72b5a9bc7b456c28ea5c45f2289ff4ba0211db6f
--- /dev/null
+++ b/Documentation/virt/kvm/running-nested-guests.rst
@@ -0,0 +1,287 @@
+==============================
+Running nested guests with KVM
+==============================
+
+A nested guest is the ability to run a guest inside another guest (it
+can be KVM-based or a different hypervisor).  The straightforward
+example is a KVM guest that in turn runs on a KVM guest (the rest of
+this document is built on this example)::
+
+              .----------------.  .----------------.
+              |                |  |                |
+              |      L2        |  |      L2        |
+              | (Nested Guest) |  | (Nested Guest) |
+              |                |  |                |
+              |----------------'--'----------------|
+              |                                    |
+              |       L1 (Guest Hypervisor)        |
+              |          KVM (/dev/kvm)            |
+              |                                    |
+      .------------------------------------------------------.
+      |                 L0 (Host Hypervisor)                 |
+      |                    KVM (/dev/kvm)                    |
+      |------------------------------------------------------|
+      |        Hardware (with virtualization extensions)     |
+      '------------------------------------------------------'
+
+Terminology:
+
+- L0 – level-0; the bare metal host, running KVM
+
+- L1 – level-1 guest; a VM running on L0; also called the "guest
+  hypervisor", as it itself is capable of running KVM.
+
+- L2 – level-2 guest; a VM running on L1, this is the "nested guest"
+
+.. note:: The above diagram is modelled after the x86 architecture;
+          s390x, ppc64 and other architectures are likely to have
+          a different design for nesting.
+
+          For example, s390x always has an LPAR (LogicalPARtition)
+          hypervisor running on bare metal, adding another layer and
+          resulting in at least four levels in a nested setup — L0 (bare
+          metal, running the LPAR hypervisor), L1 (host hypervisor), L2
+          (guest hypervisor), L3 (nested guest).
+
+          This document will stick with the three-level terminology (L0,
+          L1, and L2) for all architectures; and will largely focus on
+          x86.
+
+
+Use Cases
+---------
+
+There are several scenarios where nested KVM can be useful, to name a
+few:
+
+- As a developer, you want to test your software on different operating
+  systems (OSes).  Instead of renting multiple VMs from a Cloud
+  Provider, using nested KVM lets you rent a large enough "guest
+  hypervisor" (level-1 guest).  This in turn allows you to create
+  multiple nested guests (level-2 guests), running different OSes, on
+  which you can develop and test your software.
+
+- Live migration of "guest hypervisors" and their nested guests, for
+  load balancing, disaster recovery, etc.
+
+- VM image creation tools (e.g. ``virt-install``,  etc) often run
+  their own VM, and users expect these to work inside a VM.
+
+- Some OSes use virtualization internally for security (e.g. to let
+  applications run safely in isolation).
+
+
+Enabling "nested" (x86)
+-----------------------
+
+From Linux kernel v4.19 onwards, the ``nested`` KVM parameter is enabled
+by default for Intel and AMD.  (Though your Linux distribution might
+override this default.)
+
+In case you are running a Linux kernel older than v4.19, to enable
+nesting, set the ``nested`` KVM module parameter to ``Y`` or ``1``.  To
+persist this setting across reboots, you can add it in a config file, as
+shown below:
+
+1. On the bare metal host (L0), list the kernel modules and ensure that
+   the KVM modules::
+
+    $ lsmod | grep -i kvm
+    kvm_intel             133627  0
+    kvm                   435079  1 kvm_intel
+
+2. Show information for ``kvm_intel`` module::
+
+    $ modinfo kvm_intel | grep -i nested
+    parm:           nested:boolkvm                   435079  1 kvm_intel
+
+3. For the nested KVM configuration to persist across reboots, place the
+   below in ``/etc/modprobed/kvm_intel.conf`` (create the file if it
+   doesn't exist)::
+
+    $ cat /etc/modprobe.d/kvm_intel.conf
+    options kvm-intel nested=y
+
+4. Unload and re-load the KVM Intel module::
+
+    $ sudo rmmod kvm-intel
+    $ sudo modprobe kvm-intel
+
+5. Verify if the ``nested`` parameter for KVM is enabled::
+
+    $ cat /sys/module/kvm_intel/parameters/nested
+    Y
+
+For AMD hosts, the process is the same as above, except that the module
+name is ``kvm-amd``.
+
+
+Additional nested-related kernel parameters (x86)
+-------------------------------------------------
+
+If your hardware is sufficiently advanced (Intel Haswell processor or
+higher, which has newer hardware virt extensions), the following
+additional features will also be enabled by default: "Shadow VMCS
+(Virtual Machine Control Structure)", APIC Virtualization on your bare
+metal host (L0).  Parameters for Intel hosts::
+
+    $ cat /sys/module/kvm_intel/parameters/enable_shadow_vmcs
+    Y
+
+    $ cat /sys/module/kvm_intel/parameters/enable_apicv
+    Y
+
+    $ cat /sys/module/kvm_intel/parameters/ept
+    Y
+
+.. note:: If you suspect your L2 (i.e. nested guest) is running slower,
+          ensure the above are enabled (particularly
+          ``enable_shadow_vmcs`` and ``ept``).
+
+
+Starting a nested guest (x86)
+-----------------------------
+
+Once your bare metal host (L0) is configured for nesting, you should be
+able to start an L1 guest with::
+
+    $ qemu-kvm -cpu host [...]
+
+The above will pass through the host CPU's capabilities as-is to the
+gues); or for better live migration compatibility, use a named CPU
+model supported by QEMU. e.g.::
+
+    $ qemu-kvm -cpu Haswell-noTSX-IBRS,vmx=on
+
+then the guest hypervisor will subsequently be capable of running a
+nested guest with accelerated KVM.
+
+
+Enabling "nested" (s390x)
+-------------------------
+
+1. On the host hypervisor (L0), enable the ``nested`` parameter on
+   s390x::
+
+    $ rmmod kvm
+    $ modprobe kvm nested=1
+
+.. note:: On s390x, the kernel parameter ``hpage`` is mutually exclusive
+          with the ``nested`` paramter — i.e. to be able to enable
+          ``nested``, the ``hpage`` parameter *must* be disabled.
+
+2. The guest hypervisor (L1) must be provided with the ``sie`` CPU
+   feature — with QEMU, this can be done by using "host passthrough"
+   (via the command-line ``-cpu host``).
+
+3. Now the KVM module can be loaded in the L1 (guest hypervisor)::
+
+    $ modprobe kvm
+
+
+Live migration with nested KVM
+------------------------------
+
+The below live migration scenarios should work as of Linux kernel 5.3
+and QEMU 4.2.0 for x86; for s390x, even older versions might work.
+In all the below cases, L1 exposes ``/dev/kvm`` in it, i.e. the L2 guest
+is a "KVM-accelerated guest", not a "plain emulated guest" (as done by
+QEMU's TCG).
+
+- Migrating a nested guest (L2) to another L1 guest on the *same* bare
+  metal host.
+
+- Migrating a nested guest (L2) to another L1 guest on a *different*
+  bare metal host.
+
+- Migrating an L1 guest, with an *offline* nested guest in it, to
+  another bare metal host.
+
+- Migrating an L1 guest, with a  *live* nested guest in it, to another
+  bare metal host.
+
+Limitations on Linux kernel versions older than 5.3 (x86)
+---------------------------------------------------------
+
+On Linux kernel versions older than 5.3, once an L1 guest has started an
+L2 guest, the L1 guest would no longer capable of being migrated, saved,
+or loaded (refer to QEMU documentation on "save"/"load") until the L2
+guest shuts down.
+
+Attempting to migrate or save-and-load an L1 guest while an L2 guest is
+running will result in undefined behavior.  You might see a ``kernel
+BUG!`` entry in ``dmesg``, a kernel 'oops', or an outright kernel panic.
+Such a migrated or loaded L1 guest can no longer be considered stable or
+secure, and must be restarted.
+
+Migrating an L1 guest merely configured to support nesting, while not
+actually running L2 guests, is expected to function normally.
+Live-migrating an L2 guest from one L1 guest to another is also expected
+to succeed.
+
+Reporting bugs from nested setups
+-----------------------------------
+
+Debugging "nested" problems can involve sifting through log files across
+L0, L1 and L2; this can result in tedious back-n-forth between the bug
+reporter and the bug fixer.
+
+- Mention that you are in a "nested" setup.  If you are running any kind
+  of "nesting" at all, say so.  Unfortunately, this needs to be called
+  out because when reporting bugs, people tend to forget to even
+  *mention* that they're using nested virtualization.
+
+- Ensure you are actually running KVM on KVM.  Sometimes people do not
+  have KVM enabled for their guest hypervisor (L1), which results in
+  them running with pure emulation or what QEMU calls it as "TCG", but
+  they think they're running nested KVM.  Thus confusing "nested Virt"
+  (which could also mean, QEMU on KVM) with "nested KVM" (KVM on KVM).
+
+Information to collect (generic)
+~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
+
+The following is not an exhaustive list, but a very good starting point:
+
+  - Kernel, libvirt, and QEMU version from L0
+
+  - Kernel, libvirt and QEMU version from L1
+
+  - QEMU command-line of L1 -- when using libvirt, you'll find it here:
+    ``/var/log/libvirt/qemu/instance.log``
+
+  - QEMU command-line of L2 -- as above, when using libvirt, get the
+    complete libvirt-generated QEMU command-line
+
+  - ``cat /sys/cpuinfo`` from L0
+
+  - ``cat /sys/cpuinfo`` from L1
+
+  - ``lscpu`` from L0
+
+  - ``lscpu`` from L1
+
+  - Full ``dmesg`` output from L0
+
+  - Full ``dmesg`` output from L1
+
+x86-specific info to collect
+~~~~~~~~~~~~~~~~~~~~~~~~~~~~
+
+Both the below commands, ``x86info`` and ``dmidecode``, should be
+available on most Linux distributions with the same name:
+
+  - Output of: ``x86info -a`` from L0
+
+  - Output of: ``x86info -a`` from L1
+
+  - Output of: ``dmidecode`` from L0
+
+  - Output of: ``dmidecode`` from L1
+
+s390x-specific info to collect
+~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
+
+Along with the earlier mentioned generic details, the below is
+also recommended:
+
+  - ``/proc/sysinfo`` from L1; this will also include the info from L0
```
#### [PATCH v3] KVM: nVMX: Skip IBPB when switching between vmcs01 and vmcs02
##### From: Sean Christopherson <sean.j.christopherson@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Sean Christopherson <sean.j.christopherson@intel.com>
X-Patchwork-Id: 11528193
Return-Path: <SRS0=tDSI=6T=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 38CCF92A
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue,  5 May 2020 04:46:49 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 2ABDC206B8
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue,  5 May 2020 04:46:49 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726638AbgEEEqq (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 5 May 2020 00:46:46 -0400
Received: from mga06.intel.com ([134.134.136.31]:7601 "EHLO mga06.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1725298AbgEEEqq (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 5 May 2020 00:46:46 -0400
IronPort-SDR: 
 leSQzBa6urcowRP8QAIIvwb4jo1+IcbQJcnP5aIjTVCwcQKNpT6gurwE1oeJBePs0Avryq8ZhI
 fHOH8jmZmIcA==
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from fmsmga001.fm.intel.com ([10.253.24.23])
  by orsmga104.jf.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 04 May 2020 21:46:45 -0700
IronPort-SDR: 
 wXCpqmVPfLx0GyKFbxYYM5IXnFBMDbSAwZ++Mtx93Kpb+zm7tKcl9CElJQ4sRfjtcNmtEJFpaT
 YmW548qCFYGA==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.73,354,1583222400";
   d="scan'208";a="369300834"
Received: from sjchrist-coffee.jf.intel.com ([10.54.74.152])
  by fmsmga001.fm.intel.com with ESMTP; 04 May 2020 21:46:45 -0700
From: Sean Christopherson <sean.j.christopherson@intel.com>
To: Paolo Bonzini <pbonzini@redhat.com>
Cc: Sean Christopherson <sean.j.christopherson@intel.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org, Alexander Graf <graf@amazon.com>,
        KarimAllah Raslan <karahmed@amazon.de>
Subject: [PATCH v3] KVM: nVMX: Skip IBPB when switching between vmcs01 and
 vmcs02
Date: Mon,  4 May 2020 21:46:44 -0700
Message-Id: <20200505044644.16563-1-sean.j.christopherson@intel.com>
X-Mailer: git-send-email 2.26.0
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Skip the Indirect Branch Prediction Barrier that is triggered on a VMCS
switch when running with spectre_v2_user=on/auto if the switch is
guaranteed to be between two VMCSes in the same guest, i.e. between
vmcs01 and vmcs02.  The IBPB is intended to prevent one guest from
attacking another, which is unnecessary in the nested case as it's the
same guest from KVM's perspective.

This all but eliminates the overhead observed for nested VMX transitions
when running with CONFIG_RETPOLINE=y and spectre_v2_user=on/auto, which
can be significant, e.g. roughly 3x on current systems.

Reported-by: Alexander Graf <graf@amazon.com>
Cc: KarimAllah Raslan <karahmed@amazon.de>
Cc: stable@vger.kernel.org
Fixes: 15d45071523d ("KVM/x86: Add IBPB support")
Signed-off-by: Sean Christopherson <sean.j.christopherson@intel.com>
---

v3: Switch back to passing 'struct loaded_vmcs buddy', but keep the WARN
    if the buddy VMCS isn't already loaded as well as the comment as to
    why skipping IBPB in the nested case is ok. [Paolo]

v2: Pass a boolean to indicate a nested VMCS switch and instead WARN if
    the buddy VMCS is not already loaded.  [Alex]

 arch/x86/kvm/vmx/nested.c |  2 +-
 arch/x86/kvm/vmx/vmx.c    | 18 ++++++++++++++----
 arch/x86/kvm/vmx/vmx.h    |  3 ++-
 3 files changed, 17 insertions(+), 6 deletions(-)

```
#### [PATCH v4 1/8] vfio-ccw: Introduce new helper functions to free/destroy regions
##### From: Eric Farman <farman@linux.ibm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Eric Farman <farman@linux.ibm.com>
X-Patchwork-Id: 11528903
Return-Path: <SRS0=tDSI=6T=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id D48721392
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue,  5 May 2020 12:27:52 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id C638E206B9
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue,  5 May 2020 12:27:52 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728770AbgEEM1w (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 5 May 2020 08:27:52 -0400
Received: from mx0a-001b2d01.pphosted.com ([148.163.156.1]:39604 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1728660AbgEEM1v (ORCPT
        <rfc822;kvm@vger.kernel.org>); Tue, 5 May 2020 08:27:51 -0400
Received: from pps.filterd (m0098399.ppops.net [127.0.0.1])
        by mx0a-001b2d01.pphosted.com (8.16.0.42/8.16.0.42) with SMTP id
 045CROX6066484;
        Tue, 5 May 2020 08:27:51 -0400
Received: from pps.reinject (localhost [127.0.0.1])
        by mx0a-001b2d01.pphosted.com with ESMTP id 30s510sh54-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Tue, 05 May 2020 08:27:51 -0400
Received: from m0098399.ppops.net (m0098399.ppops.net [127.0.0.1])
        by pps.reinject (8.16.0.36/8.16.0.36) with SMTP id 045CRijF067869;
        Tue, 5 May 2020 08:27:50 -0400
Received: from ppma01fra.de.ibm.com (46.49.7a9f.ip4.static.sl-reverse.com
 [159.122.73.70])
        by mx0a-001b2d01.pphosted.com with ESMTP id 30s510sh3k-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Tue, 05 May 2020 08:27:50 -0400
Received: from pps.filterd (ppma01fra.de.ibm.com [127.0.0.1])
        by ppma01fra.de.ibm.com (8.16.0.27/8.16.0.27) with SMTP id
 045CQ97x025436;
        Tue, 5 May 2020 12:27:48 GMT
Received: from b06cxnps4076.portsmouth.uk.ibm.com
 (d06relay13.portsmouth.uk.ibm.com [9.149.109.198])
        by ppma01fra.de.ibm.com with ESMTP id 30s0g5atx2-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Tue, 05 May 2020 12:27:48 +0000
Received: from d06av26.portsmouth.uk.ibm.com (d06av26.portsmouth.uk.ibm.com
 [9.149.105.62])
        by b06cxnps4076.portsmouth.uk.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id 045CRjP843843798
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Tue, 5 May 2020 12:27:45 GMT
Received: from d06av26.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 71E5FAE055;
        Tue,  5 May 2020 12:27:45 +0000 (GMT)
Received: from d06av26.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 5FD51AE045;
        Tue,  5 May 2020 12:27:45 +0000 (GMT)
Received: from tuxmaker.boeblingen.de.ibm.com (unknown [9.152.85.9])
        by d06av26.portsmouth.uk.ibm.com (Postfix) with ESMTPS;
        Tue,  5 May 2020 12:27:45 +0000 (GMT)
Received: by tuxmaker.boeblingen.de.ibm.com (Postfix, from userid 4958)
        id 18794E02BA; Tue,  5 May 2020 14:27:45 +0200 (CEST)
From: Eric Farman <farman@linux.ibm.com>
To: linux-s390@vger.kernel.org, kvm@vger.kernel.org
Cc: Cornelia Huck <cohuck@redhat.com>,
        Halil Pasic <pasic@linux.ibm.com>,
        Jason Herne <jjherne@linux.ibm.com>,
        Jared Rossi <jrossi@linux.ibm.com>,
        Eric Farman <farman@linux.ibm.com>
Subject: [PATCH v4 1/8] vfio-ccw: Introduce new helper functions to
 free/destroy regions
Date: Tue,  5 May 2020 14:27:38 +0200
Message-Id: <20200505122745.53208-2-farman@linux.ibm.com>
X-Mailer: git-send-email 2.17.1
In-Reply-To: <20200505122745.53208-1-farman@linux.ibm.com>
References: <20200505122745.53208-1-farman@linux.ibm.com>
X-TM-AS-GCONF: 00
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.138,18.0.676
 definitions=2020-05-05_07:2020-05-04,2020-05-05 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 bulkscore=0 malwarescore=0
 clxscore=1015 suspectscore=2 mlxlogscore=854 priorityscore=1501
 impostorscore=0 lowpriorityscore=0 mlxscore=0 adultscore=0 phishscore=0
 spamscore=0 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.12.0-2003020000 definitions=main-2005050098
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Farhan Ali <alifm@linux.ibm.com>

Consolidate some of the cleanup code for the regions, so that
as more are added we reduce code duplication.

Signed-off-by: Farhan Ali <alifm@linux.ibm.com>
Signed-off-by: Eric Farman <farman@linux.ibm.com>
Reviewed-by: Cornelia Huck <cohuck@redhat.com>
---

Notes:
    v1->v2:
     - Add Conny's r-b
    
    v0->v1: [EF]
     - Commit message

 drivers/s390/cio/vfio_ccw_drv.c | 28 ++++++++++++++++++----------
 1 file changed, 18 insertions(+), 10 deletions(-)

```
#### [PATCH v2 1/3] vfio/type1: Support faulting PFNMAP vmasFrom: Alex Williamson <alex.williamson@redhat.com>
##### From: Alex Williamson <alex.williamson@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Alex Williamson <alex.williamson@redhat.com>
X-Patchwork-Id: 11529999
Return-Path: <SRS0=tDSI=6T=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 393621668
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue,  5 May 2020 21:54:55 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 21B7C20752
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue,  5 May 2020 21:54:55 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="RDVi3KLo"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729270AbgEEVyx (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 5 May 2020 17:54:53 -0400
Received: from us-smtp-1.mimecast.com ([207.211.31.81]:59818 "EHLO
        us-smtp-delivery-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S1727785AbgEEVyw (ORCPT
        <rfc822;kvm@vger.kernel.org>); Tue, 5 May 2020 17:54:52 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1588715691;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:content-type:content-type:
         content-transfer-encoding:content-transfer-encoding:
         in-reply-to:in-reply-to:references:references;
        bh=Eckl6hH0AbgL49kEhmxA8Bwx9T7n/rxh8xbcvWxSc1I=;
        b=RDVi3KLoJDB3txgzful5l9K85EzNXSk8ZqHzCD5oV3Q4kJyi6ZJV1BmAVIx7rAO2hvY5Rt
        qtytD7h2/qfIzGtlssmkZMZE1BaC62CQk+Q3qC99O8gy5hx3p61KqstIh4VSbh34YUMVMY
        cX7Zk38HCvA5AOpaWQ9WkI3O5px+01Q=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-295-VOYbBK-OMSGNzfOZspF_2Q-1; Tue, 05 May 2020 17:54:49 -0400
X-MC-Unique: VOYbBK-OMSGNzfOZspF_2Q-1
Received: from smtp.corp.redhat.com (int-mx03.intmail.prod.int.phx2.redhat.com
 [10.5.11.13])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id ADDE2107ACCA;
        Tue,  5 May 2020 21:54:48 +0000 (UTC)
Received: from gimli.home (ovpn-113-95.phx2.redhat.com [10.3.113.95])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 3C52770538;
        Tue,  5 May 2020 21:54:45 +0000 (UTC)
Subject: [PATCH v2 1/3] vfio/type1: Support faulting PFNMAP vmas
From: Alex Williamson <alex.williamson@redhat.com>
To: kvm@vger.kernel.org
Cc: linux-kernel@vger.kernel.org, cohuck@redhat.com, jgg@ziepe.ca
Date: Tue, 05 May 2020 15:54:44 -0600
Message-ID: <158871568480.15589.17339878308143043906.stgit@gimli.home>
In-Reply-To: <158871401328.15589.17598154478222071285.stgit@gimli.home>
References: <158871401328.15589.17598154478222071285.stgit@gimli.home>
User-Agent: StGit/0.19-dirty
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.13
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

With conversion to follow_pfn(), DMA mapping a PFNMAP range depends on
the range being faulted into the vma.  Add support to manually provide
that, in the same way as done on KVM with hva_to_pfn_remapped().

Signed-off-by: Alex Williamson <alex.williamson@redhat.com>
---
 drivers/vfio/vfio_iommu_type1.c |   36 +++++++++++++++++++++++++++++++++---
 1 file changed, 33 insertions(+), 3 deletions(-)

```
