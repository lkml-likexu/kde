#### [PATCH 1/2] arch/x86: Rename config X86_INTEL_MEMORY_PROTECTION_KEYS to generic x86
##### From: Babu Moger <babu.moger@amd.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 8bit
X-Patchwork-Submitter: Babu Moger <babu.moger@amd.com>
X-Patchwork-Id: 11531957
Return-Path: <SRS0=qN9b=6U=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 1C5BA912
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed,  6 May 2020 22:02:29 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id EE575207DD
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed,  6 May 2020 22:02:28 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=amdcloud.onmicrosoft.com
 header.i=@amdcloud.onmicrosoft.com header.b="FPCX8/S9"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1730021AbgEFWCZ (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 6 May 2020 18:02:25 -0400
Received: from mail-dm6nam10on2050.outbound.protection.outlook.com
 ([40.107.93.50]:2410
        "EHLO NAM10-DM6-obe.outbound.protection.outlook.com"
        rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org with ESMTP
        id S1726927AbgEFWCY (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 6 May 2020 18:02:24 -0400
ARC-Seal: i=1; a=rsa-sha256; s=arcselector9901; d=microsoft.com; cv=none;
 b=EoM3avegf8yf5wmHJh6XjBkVBW0O4txcs1SNMjaGWXAKvcNx6gY80BOuoMXC5MFTEJZFr6R0KWcTN19yf+jlRdXBnrk7tYFuoqXC9lu10P6PWP55Wr8sXQl7EaqeF8f7KGrpMzwE0NYLaxMQfBQinzD1loiyx9MOneoqy2w8Em9bz2JzwF1ygX9ThsWtY8w2Bxxd58kVhMBvj4tkPFOIKiFY/NcJvdJT3EUXAPt/ZnD1lzfOh1RqErkBq/1aDoUDx2B3ePnLwue2IIHunEaQF65LA7AsK/79OGtfZ3wJw99pNhKPBobKxOH1oYbrVHvQvasrJE7oRMvfY+CtaCMN/w==
ARC-Message-Signature: i=1; a=rsa-sha256; c=relaxed/relaxed; d=microsoft.com;
 s=arcselector9901;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=Im2ZioGTRQ6gMRIV58xu9Q5CWI54e5aABgZ+EgMKyrs=;
 b=Ij27kEc+zidR+s+YtPdVciVIWr8nPq2FsZyK9sTX/RYqtUZjqdAZBScry9E6QKWB9cCa9UKIqKnjSxn1Dlc+YXUh2IxvJ0bnWQyjZf0cxU6R+KK6ijTO1PkZ/MDD6Qiht96eF6qN4FTa//IshCLkW7aLr0uO+cb5AdO47DKqDOHHXYdIrBpymMPPISK0VF4lEZJ5GNq6bz0qj1MFhk38x6b0nMI6lumCnrZBmdCInHhZiBlJptqrCW8uplkOeaTZe++BiWsrK8sfTv+UNEnaZyDOqWtweOaRi2p802V+H6FKaKurebtaHq2dVIdGkB7n7X8jSlEWGCAvj6gMjWfa5Q==
ARC-Authentication-Results: i=1; mx.microsoft.com 1; spf=pass
 smtp.mailfrom=amd.com; dmarc=pass action=none header.from=amd.com; dkim=pass
 header.d=amd.com; arc=none
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
 d=amdcloud.onmicrosoft.com; s=selector2-amdcloud-onmicrosoft-com;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=Im2ZioGTRQ6gMRIV58xu9Q5CWI54e5aABgZ+EgMKyrs=;
 b=FPCX8/S9bypHRhpRLKuRp3sFvmU5bq18Mj2SGXKxZ8UGgDvrYvsdRenuIKKPYeUh7emZlBRM83EV/ED52aL552tfyHw51eXO4O5HyoGxx0l0j6WjDAp5Q/gNqBDW8hULIdE/2TTgsYhiLMzeylAU1amzILXV0AHILg0JoIpDBDE=
Authentication-Results: tencent.com; dkim=none (message not signed)
 header.d=none;tencent.com; dmarc=none action=none header.from=amd.com;
Received: from SN1PR12MB2560.namprd12.prod.outlook.com (2603:10b6:802:26::19)
 by SN1PR12MB2512.namprd12.prod.outlook.com (2603:10b6:802:31::14) with
 Microsoft SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.2979.26; Wed, 6 May
 2020 22:02:16 +0000
Received: from SN1PR12MB2560.namprd12.prod.outlook.com
 ([fe80::c0f:2938:784f:ed8d]) by SN1PR12MB2560.namprd12.prod.outlook.com
 ([fe80::c0f:2938:784f:ed8d%7]) with mapi id 15.20.2979.028; Wed, 6 May 2020
 22:02:16 +0000
Subject: [PATCH 1/2] arch/x86: Rename config
 X86_INTEL_MEMORY_PROTECTION_KEYS to generic x86
From: Babu Moger <babu.moger@amd.com>
To: corbet@lwn.net, tglx@linutronix.de, mingo@redhat.com, bp@alien8.de,
        hpa@zytor.com, pbonzini@redhat.com, sean.j.christopherson@intel.com
Cc: x86@kernel.org, vkuznets@redhat.com, wanpengli@tencent.com,
        jmattson@google.com, joro@8bytes.org, dave.hansen@linux.intel.com,
        luto@kernel.org, peterz@infradead.org, mchehab+samsung@kernel.org,
        babu.moger@amd.com, changbin.du@intel.com, namit@vmware.com,
        bigeasy@linutronix.de, yang.shi@linux.alibaba.com,
        asteinhauser@google.com, anshuman.khandual@arm.com,
        jan.kiszka@siemens.com, akpm@linux-foundation.org,
        steven.price@arm.com, rppt@linux.vnet.ibm.com, peterx@redhat.com,
        dan.j.williams@intel.com, arjunroy@google.com, logang@deltatee.com,
        thellstrom@vmware.com, aarcange@redhat.com, justin.he@arm.com,
        robin.murphy@arm.com, ira.weiny@intel.com, keescook@chromium.org,
        jgross@suse.com, andrew.cooper3@citrix.com,
        pawan.kumar.gupta@linux.intel.com, fenghua.yu@intel.com,
        vineela.tummalapalli@intel.com, yamada.masahiro@socionext.com,
        sam@ravnborg.org, acme@redhat.com, linux-doc@vger.kernel.org,
        linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Date: Wed, 06 May 2020 17:02:13 -0500
Message-ID: <158880253347.11615.8499618616856685179.stgit@naples-babu.amd.com>
In-Reply-To: 
 <158880240546.11615.2219410169137148044.stgit@naples-babu.amd.com>
References: <158880240546.11615.2219410169137148044.stgit@naples-babu.amd.com>
User-Agent: StGit/unknown-version
X-ClientProxiedBy: SN2PR01CA0077.prod.exchangelabs.com (2603:10b6:800::45) To
 SN1PR12MB2560.namprd12.prod.outlook.com (2603:10b6:802:26::19)
MIME-Version: 1.0
X-MS-Exchange-MessageSentRepresentingType: 1
Received: from naples-babu.amd.com (165.204.78.2) by
 SN2PR01CA0077.prod.exchangelabs.com (2603:10b6:800::45) with Microsoft SMTP
 Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.2979.26 via Frontend
 Transport; Wed, 6 May 2020 22:02:14 +0000
X-Originating-IP: [165.204.78.2]
X-MS-PublicTrafficType: Email
X-MS-Office365-Filtering-HT: Tenant
X-MS-Office365-Filtering-Correlation-Id: 5a95c6b5-b59a-4d18-1195-08d7f2092326
X-MS-TrafficTypeDiagnostic: SN1PR12MB2512:|SN1PR12MB2512:
X-MS-Exchange-Transport-Forked: True
X-Microsoft-Antispam-PRVS: 
 <SN1PR12MB25123676C5B17A768271D1AE95A40@SN1PR12MB2512.namprd12.prod.outlook.com>
X-MS-Oob-TLC-OOBClassifiers: OLM:8882;
X-Forefront-PRVS: 03950F25EC
X-MS-Exchange-SenderADCheck: 1
X-Microsoft-Antispam: BCL:0;
X-Microsoft-Antispam-Message-Info: 
 6Tffop7PmK37AhzDH/JCB7jUiPWIGvMTE/hQrKarlKGNsnrPHvwfIBn5GNCuBGozWWx5/AJTaLsMqc5hW7G2uQgxd7sdLEZ1THOYhF5ATABjAuVfKtPDe2MMeLziqNOaEqPEVo6MuAf1KLN4C5LF+WTbdU5LaxDwfY5Rc4/FX56Y9GGAs7RJg98zKYmo6aL3xqCaRyjxhKkHTSXbHJdMOW7r69v/U5drNEVM7Zfive+YwXIFMzCadTpO7WZ5xuKqZfw9IWDzLM2icRIHZQi5qLwYqCCovIE47b+jpaNeRPd540UqyXqCzUlslwiU5kS4thgUWlWUFVp9kNa+3HPnlNLoTK641Egf80zDX9GGKEpRCBbsPzRXNmo0ZOuMcVrdqjF6ZHO0AgW0kXpjdAzYaDoaNSY1q4Txuk+GDgkHXv1bMMymwaQGtrISFF1InKm1uNa1AJy2zpUBsMRQdqUBcSqfQEMwwFI+8AtG1Qjs3+SQFmVVdqbhSBRhdP0GEyQSYkyRktxQa5lIn5AyoDMN/EzN9ExK3KqSRNUlinZNxog=
X-Forefront-Antispam-Report: 
 CIP:255.255.255.255;CTRY:;LANG:en;SCL:1;SRV:;IPV:NLI;SFV:NSPM;H:SN1PR12MB2560.namprd12.prod.outlook.com;PTR:;CAT:NONE;SFTY:;SFS:(4636009)(346002)(376002)(136003)(39860400002)(396003)(366004)(33430700001)(26005)(52116002)(7696005)(4326008)(2906002)(8936002)(33440700001)(66476007)(66556008)(8676002)(16526019)(478600001)(55016002)(186003)(103116003)(316002)(86362001)(956004)(66946007)(7416002)(7406005)(5660300002)(44832011)(41533002);DIR:OUT;SFP:1101;
X-MS-Exchange-AntiSpam-MessageData: 
 f4CMaHxi7kDIyngqTux3ekK/qzy2GnxiJvQsCkZDgsR8B+9boEwckCmZbSSUKVbtDab5u1Bi8GcX5kCQmVbeFKk9bhxnCFsWGsr8nZ3qrLDJUHyVygO/U9V8hz19nVywgaDaW5+SVW+AnFUaCW1DGCycqBNTygKK3xCOvydY92yGVNv/t300667OKk8cp0m7elKiOYB/BaoeEpB716rXRONE9h+Ex3DI9R9GNqKWIiUXWPwO9p0W6xjVtZpjCCSa1DskhPPLh+c8U7RMsXSZ5aE2zXxNc73LHYfecWVIbtatcCCJPz1Z5tPiiw2yKjv2T6d5vfYHtNXuulpQVh5Q0wwDaAOYfSNCLI78MsDS2qh/UzZsEIMltNGHuj7G4KEdNVb9Y4+W0KoM4P5c4i8QmRuH4vcbrXKQuFOZa187/Ra3dTl/vEg/pJRzbrNE8rU9aPSwS5xnz2M6XfkRi+9dbbTHhtmsoQkecXtOKECvZi0CT6OFUwxVUtQzxTzB8BsRpIkps70Lw7hRAVVJAt5ydlgWQwfhO801MqrdCSRQzvl3zXGFGEFqO4EnWf/WjEjaVU6ShcWOluQqnxXvS88gJ4wIC29SJVK237Rme/c6wUhFD2Q3TJLg4X9daocVZpMiXYjo921nMPLwEfNnX9SFGDMuo+mI+EVusyUCGFQXKcqCTarX9nP6a824MOgVXlwM6JgExZAdh2msXjJhN8N30hvEqMNH3G0JK+0AydBmQepoqJh6hdAfWZs34IBT4hPBTc3c3nRA1VJlmP4ou38oC0/rfzB2v00ipOom+w+d3qk=
X-OriginatorOrg: amd.com
X-MS-Exchange-CrossTenant-Network-Message-Id: 
 5a95c6b5-b59a-4d18-1195-08d7f2092326
X-MS-Exchange-CrossTenant-OriginalArrivalTime: 06 May 2020 22:02:15.8497
 (UTC)
X-MS-Exchange-CrossTenant-FromEntityHeader: Hosted
X-MS-Exchange-CrossTenant-Id: 3dd8961f-e488-4e60-8e11-a82d994e183d
X-MS-Exchange-CrossTenant-MailboxType: HOSTED
X-MS-Exchange-CrossTenant-UserPrincipalName: 
 QpeMg6jbiHnTSrQcD1LRC5/uCjkHQsxlvoT+Scl7YHLwZ9Fb8BptOtIRVTT/heWw
X-MS-Exchange-Transport-CrossTenantHeadersStamped: SN1PR12MB2512
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

AMD's next generation of EPYC processors support the MPK (Memory
Protection Keys) feature.

So, rename X86_INTEL_MEMORY_PROTECTION_KEYS to X86_MEMORY_PROTECTION_KEYS.

No functional changes.

Signed-off-by: Babu Moger <babu.moger@amd.com>
---
 Documentation/core-api/protection-keys.rst     |    3 ++-
 arch/x86/Kconfig                               |    6 +++---
 arch/x86/include/asm/disabled-features.h       |    4 ++--
 arch/x86/include/asm/mmu.h                     |    2 +-
 arch/x86/include/asm/mmu_context.h             |    4 ++--
 arch/x86/include/asm/pgtable.h                 |    4 ++--
 arch/x86/include/asm/pgtable_types.h           |    2 +-
 arch/x86/include/asm/special_insns.h           |    2 +-
 arch/x86/include/uapi/asm/mman.h               |    2 +-
 arch/x86/kernel/cpu/common.c                   |    2 +-
 arch/x86/mm/Makefile                           |    2 +-
 arch/x86/mm/pkeys.c                            |    2 +-
 scripts/headers_install.sh                     |    2 +-
 tools/arch/x86/include/asm/disabled-features.h |    4 ++--
 14 files changed, 21 insertions(+), 20 deletions(-)

```
#### [GIT PULL 1/1] KVM: s390: Remove false WARN_ON_ONCE for the PQAP instruction
##### From: Christian Borntraeger <borntraeger@de.ibm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Christian Borntraeger <borntraeger@de.ibm.com>
X-Patchwork-Id: 11531095
Return-Path: <SRS0=qN9b=6U=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id C8B7414B4
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed,  6 May 2020 11:59:55 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id B9F702073A
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed,  6 May 2020 11:59:55 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728018AbgEFL7z (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 6 May 2020 07:59:55 -0400
Received: from mx0b-001b2d01.pphosted.com ([148.163.158.5]:61932 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S1727994AbgEFL7y (ORCPT
        <rfc822;kvm@vger.kernel.org>); Wed, 6 May 2020 07:59:54 -0400
Received: from pps.filterd (m0098420.ppops.net [127.0.0.1])
        by mx0b-001b2d01.pphosted.com (8.16.0.42/8.16.0.42) with SMTP id
 046BhZG0113419;
        Wed, 6 May 2020 07:59:53 -0400
Received: from pps.reinject (localhost [127.0.0.1])
        by mx0b-001b2d01.pphosted.com with ESMTP id 30uvm90eba-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Wed, 06 May 2020 07:59:53 -0400
Received: from m0098420.ppops.net (m0098420.ppops.net [127.0.0.1])
        by pps.reinject (8.16.0.36/8.16.0.36) with SMTP id 046BjDxF117461;
        Wed, 6 May 2020 07:59:52 -0400
Received: from ppma03ams.nl.ibm.com (62.31.33a9.ip4.static.sl-reverse.com
 [169.51.49.98])
        by mx0b-001b2d01.pphosted.com with ESMTP id 30uvm90eah-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Wed, 06 May 2020 07:59:52 -0400
Received: from pps.filterd (ppma03ams.nl.ibm.com [127.0.0.1])
        by ppma03ams.nl.ibm.com (8.16.0.27/8.16.0.27) with SMTP id
 046BoK2n021410;
        Wed, 6 May 2020 11:59:50 GMT
Received: from b06avi18878370.portsmouth.uk.ibm.com
 (b06avi18878370.portsmouth.uk.ibm.com [9.149.26.194])
        by ppma03ams.nl.ibm.com with ESMTP id 30s0g5s4ct-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Wed, 06 May 2020 11:59:50 +0000
Received: from d06av26.portsmouth.uk.ibm.com (d06av26.portsmouth.uk.ibm.com
 [9.149.105.62])
        by b06avi18878370.portsmouth.uk.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id 046BxlFY62325060
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Wed, 6 May 2020 11:59:47 GMT
Received: from d06av26.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id A0052AE051;
        Wed,  6 May 2020 11:59:47 +0000 (GMT)
Received: from d06av26.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 8D41BAE04D;
        Wed,  6 May 2020 11:59:47 +0000 (GMT)
Received: from tuxmaker.boeblingen.de.ibm.com (unknown [9.152.85.9])
        by d06av26.portsmouth.uk.ibm.com (Postfix) with ESMTPS;
        Wed,  6 May 2020 11:59:47 +0000 (GMT)
Received: by tuxmaker.boeblingen.de.ibm.com (Postfix, from userid 25651)
        id 460F6E0554; Wed,  6 May 2020 13:59:47 +0200 (CEST)
From: Christian Borntraeger <borntraeger@de.ibm.com>
To: Paolo Bonzini <pbonzini@redhat.com>
Cc: KVM <kvm@vger.kernel.org>,
        Janosch Frank <frankja@linux.vnet.ibm.com>,
        David Hildenbrand <david@redhat.com>,
        Cornelia Huck <cohuck@redhat.com>,
        linux-s390 <linux-s390@vger.kernel.org>,
        Christian Borntraeger <borntraeger@de.ibm.com>,
        Claudio Imbrenda <imbrenda@linux.ibm.com>,
        Tony Krowiak <akrowiak@linux.ibm.com>,
        Pierre Morel <pmorel@linux.ibm.com>,
        Qian Cai <cailca@icloud.com>
Subject: [GIT PULL 1/1] KVM: s390: Remove false WARN_ON_ONCE for the PQAP
 instruction
Date: Wed,  6 May 2020 13:59:45 +0200
Message-Id: <20200506115945.13132-2-borntraeger@de.ibm.com>
X-Mailer: git-send-email 2.25.4
In-Reply-To: <20200506115945.13132-1-borntraeger@de.ibm.com>
References: <20200506115945.13132-1-borntraeger@de.ibm.com>
MIME-Version: 1.0
X-TM-AS-GCONF: 00
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.138,18.0.676
 definitions=2020-05-06_04:2020-05-05,2020-05-06 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 impostorscore=0 mlxscore=0
 suspectscore=0 clxscore=1015 adultscore=0 bulkscore=0 malwarescore=0
 phishscore=0 mlxlogscore=999 lowpriorityscore=0 spamscore=0
 priorityscore=1501 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.12.0-2003020000 definitions=main-2005060088
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
Cc: stable@vger.kernel.org # v5.3+
Fixes: e5282de93105 ("s390: ap: kvm: add PQAP interception for AQIC")
Link: https://lore.kernel.org/kvm/20200505083515.2720-1-borntraeger@de.ibm.com
Reported-by: Qian Cai <cailca@icloud.com>
Signed-off-by: Christian Borntraeger <borntraeger@de.ibm.com>
Reviewed-by: David Hildenbrand <david@redhat.com>
Reviewed-by: Cornelia Huck <cohuck@redhat.com>
Signed-off-by: Christian Borntraeger <borntraeger@de.ibm.com>
---
 arch/s390/kvm/priv.c | 4 +++-
 1 file changed, 3 insertions(+), 1 deletion(-)

```
#### [PATCH v12 01/10] KVM: VMX: Introduce CET VMCS fields and flags
##### From: Yang Weijiang <weijiang.yang@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Yang Weijiang <weijiang.yang@intel.com>
X-Patchwork-Id: 11530671
Return-Path: <SRS0=qN9b=6U=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id A147114B4
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed,  6 May 2020 08:19:38 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 932FB20714
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed,  6 May 2020 08:19:38 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728573AbgEFITf (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 6 May 2020 04:19:35 -0400
Received: from mga12.intel.com ([192.55.52.136]:35417 "EHLO mga12.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1727956AbgEFITe (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 6 May 2020 04:19:34 -0400
IronPort-SDR: 
 wntHLFj6rg0wg0HqOk2jDwPkZOLL3MqNXsEDYhgQB9X4wlAj45cSXpneSdFfF89T2FcBaJtLmL
 AvXTKYwNobXQ==
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from orsmga003.jf.intel.com ([10.7.209.27])
  by fmsmga106.fm.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 06 May 2020 01:19:33 -0700
IronPort-SDR: 
 R0C9Sc5VvEfUbYBxqCRzJrxaZDUKqjptSRqN2RcQq7g2BYiXDU4po4bD/6AHc2YIoDZ/jVQA/B
 fbFVy7OA8Unw==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.73,358,1583222400";
   d="scan'208";a="260030066"
Received: from unknown (HELO local-michael-cet-test.sh.intel.com)
 ([10.239.159.128])
  by orsmga003.jf.intel.com with ESMTP; 06 May 2020 01:19:31 -0700
From: Yang Weijiang <weijiang.yang@intel.com>
To: kvm@vger.kernel.org, linux-kernel@vger.kernel.org,
        pbonzini@redhat.com, sean.j.christopherson@intel.com,
        jmattson@google.com
Cc: yu.c.zhang@linux.intel.com, Yang Weijiang <weijiang.yang@intel.com>
Subject: [PATCH v12 01/10] KVM: VMX: Introduce CET VMCS fields and flags
Date: Wed,  6 May 2020 16:21:00 +0800
Message-Id: <20200506082110.25441-2-weijiang.yang@intel.com>
X-Mailer: git-send-email 2.17.2
In-Reply-To: <20200506082110.25441-1-weijiang.yang@intel.com>
References: <20200506082110.25441-1-weijiang.yang@intel.com>
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

CET(Control-flow Enforcement Technology) is a CPU feature used to prevent
Return/Jump-Oriented Programming(ROP/JOP) attacks. It provides the following
sub-features to defend against ROP/JOP style control-flow subversion attacks:

Shadow Stack (SHSTK):
  A second stack for program which is used exclusively for control transfer
  operations.

Indirect Branch Tracking (IBT):
  Code branching protection to defend against jump/call oriented programming.

Several new CET MSRs are defined in kernel to support CET:
  MSR_IA32_{U,S}_CET: Controls the CET settings for user mode and kernel mode
  respectively.

  MSR_IA32_PL{0,1,2,3}_SSP: Stores shadow stack pointers for CPL-0,1,2,3
  protection respectively.

  MSR_IA32_INT_SSP_TAB: Stores base address of shadow stack pointer table.

Two XSAVES state bits are introduced for CET:
  IA32_XSS:[bit 11]: Control saving/restoring user mode CET states
  IA32_XSS:[bit 12]: Control saving/restoring kernel mode CET states.

Six VMCS fields are introduced for CET:
  {HOST,GUEST}_S_CET: Stores CET settings for kernel mode.
  {HOST,GUEST}_SSP: Stores shadow stack pointer of current task/thread.
  {HOST,GUEST}_INTR_SSP_TABLE: Stores base address of shadow stack pointer
  table.

If VM_EXIT_LOAD_HOST_CET_STATE = 1, the host CET states are restored from below
VMCS fields at VM-Exit:
  HOST_S_CET
  HOST_SSP
  HOST_INTR_SSP_TABLE

If VM_ENTRY_LOAD_GUEST_CET_STATE = 1, the guest CET states are loaded from below
VMCS fields at VM-Entry:
  GUEST_S_CET
  GUEST_SSP
  GUEST_INTR_SSP_TABLE

Co-developed-by: Zhang Yi Z <yi.z.zhang@linux.intel.com>
Signed-off-by: Zhang Yi Z <yi.z.zhang@linux.intel.com>
Signed-off-by: Yang Weijiang <weijiang.yang@intel.com>
---
 arch/x86/include/asm/vmx.h | 8 ++++++++
 1 file changed, 8 insertions(+)

```
#### [PATCH] KVM: nVMX: Remove unused 'ops' param from nested_vmx_hardware_setup()
##### From: Sean Christopherson <sean.j.christopherson@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Sean Christopherson <sean.j.christopherson@intel.com>
X-Patchwork-Id: 11531825
Return-Path: <SRS0=qN9b=6U=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 7659A14C0
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed,  6 May 2020 20:46:59 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 68F6D2070B
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed,  6 May 2020 20:46:59 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729122AbgEFUqz (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 6 May 2020 16:46:55 -0400
Received: from mga14.intel.com ([192.55.52.115]:10412 "EHLO mga14.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1727984AbgEFUqz (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 6 May 2020 16:46:55 -0400
IronPort-SDR: 
 eLwSlkkeD9bgYUVZyJvrf1CXZFoe2lrRmqJC1y2RgPsOEwAsB/SyiB8uGxPhx399j0fnoMqozf
 Fmt7KXzHNi6A==
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from orsmga008.jf.intel.com ([10.7.209.65])
  by fmsmga103.fm.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 06 May 2020 13:46:54 -0700
IronPort-SDR: 
 ADWdu/2AJnNYrEuYmusZKmq5/Bt1ju1DiUUzsmwbVmNR23iLMYujA9nPwIo2TisLcL0KDhewdB
 Sge3yu8LYtEQ==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.73,360,1583222400";
   d="scan'208";a="296304662"
Received: from sjchrist-coffee.jf.intel.com ([10.54.74.152])
  by orsmga008.jf.intel.com with ESMTP; 06 May 2020 13:46:54 -0700
From: Sean Christopherson <sean.j.christopherson@intel.com>
To: Paolo Bonzini <pbonzini@redhat.com>
Cc: Sean Christopherson <sean.j.christopherson@intel.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org
Subject: [PATCH] KVM: nVMX: Remove unused 'ops' param from
 nested_vmx_hardware_setup()
Date: Wed,  6 May 2020 13:46:53 -0700
Message-Id: <20200506204653.14683-1-sean.j.christopherson@intel.com>
X-Mailer: git-send-email 2.26.0
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Remove a 'struct kvm_x86_ops' param that got left behind when the nested
ops were moved to their own struct.

Fixes: 33b22172452f0 ("KVM: x86: move nested-related kvm_x86_ops to a separate struct")
Signed-off-by: Sean Christopherson <sean.j.christopherson@intel.com>
Reviewed-by: Jim Mattson <jmattson@google.com>
---
 arch/x86/kvm/vmx/nested.c | 3 +--
 arch/x86/kvm/vmx/nested.h | 3 +--
 arch/x86/kvm/vmx/vmx.c    | 3 +--
 3 files changed, 3 insertions(+), 6 deletions(-)

```
#### [PATCH 1/9] KVM: X86: Declare KVM_CAP_SET_GUEST_DEBUG properly
##### From: Paolo Bonzini <pbonzini@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Paolo Bonzini <pbonzini@redhat.com>
X-Patchwork-Id: 11531033
Return-Path: <SRS0=qN9b=6U=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id DD294913
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed,  6 May 2020 11:10:48 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id C57FD206D5
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed,  6 May 2020 11:10:48 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="RhZZGMMv"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728171AbgEFLKp (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 6 May 2020 07:10:45 -0400
Received: from us-smtp-delivery-1.mimecast.com ([205.139.110.120]:49006 "EHLO
        us-smtp-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org
        with ESMTP id S1728138AbgEFLKo (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 6 May 2020 07:10:44 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1588763443;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:in-reply-to:in-reply-to:references:references;
        bh=h2l3KOMDutolAkEtGy6K6Owvl6fNHONxFxSaO2J+VP4=;
        b=RhZZGMMvxB7a/AGEmWk4o5cSsfwn46lxZRCMZ5ZnrgrML9SSDf3/UKvtbv67N1MlwxWkpm
        gfIpFcEbBSVzwr0OFLqtcTRmY+vr2j0F6wRJJ0es/Aw4xnAK09z2BRjH5CSJxDEZYVcYyJ
        R5gCcZnGARi0KbLlrRjxdCE85WRBR3Q=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-24-Q1s40J2yNQGl_e7U6ioYcQ-1; Wed, 06 May 2020 07:10:41 -0400
X-MC-Unique: Q1s40J2yNQGl_e7U6ioYcQ-1
Received: from smtp.corp.redhat.com (int-mx06.intmail.prod.int.phx2.redhat.com
 [10.5.11.16])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 962AC107ACCA;
        Wed,  6 May 2020 11:10:40 +0000 (UTC)
Received: from virtlab701.virt.lab.eng.bos.redhat.com
 (virtlab701.virt.lab.eng.bos.redhat.com [10.19.152.228])
        by smtp.corp.redhat.com (Postfix) with ESMTP id E107C5C1D4;
        Wed,  6 May 2020 11:10:37 +0000 (UTC)
From: Paolo Bonzini <pbonzini@redhat.com>
To: linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Cc: peterx@redhat.com,
        Sean Christopherson <sean.j.christopherson@intel.com>
Subject: [PATCH 1/9] KVM: X86: Declare KVM_CAP_SET_GUEST_DEBUG properly
Date: Wed,  6 May 2020 07:10:26 -0400
Message-Id: <20200506111034.11756-2-pbonzini@redhat.com>
In-Reply-To: <20200506111034.11756-1-pbonzini@redhat.com>
References: <20200506111034.11756-1-pbonzini@redhat.com>
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.16
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Peter Xu <peterx@redhat.com>

KVM_CAP_SET_GUEST_DEBUG should be supported for x86 however it's not declared
as supported.  My wild guess is that userspaces like QEMU are using "#ifdef
KVM_CAP_SET_GUEST_DEBUG" to check for the capability instead, but that could be
wrong because the compilation host may not be the runtime host.

The userspace might still want to keep the old "#ifdef" though to not break the
guest debug on old kernels.

Signed-off-by: Peter Xu <peterx@redhat.com>
Message-Id: <20200505154750.126300-1-peterx@redhat.com>
[Do the same for PPC and s390. - Paolo]
Signed-off-by: Paolo Bonzini <pbonzini@redhat.com>
---
 arch/powerpc/kvm/powerpc.c | 1 +
 arch/s390/kvm/kvm-s390.c   | 1 +
 arch/x86/kvm/x86.c         | 1 +
 3 files changed, 3 insertions(+)

```
#### [PATCH 1/4] KVM: Introduce kvm_make_all_cpus_request_except()
##### From: Suravee Suthikulpanit <suravee.suthikulpanit@amd.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Suravee Suthikulpanit <Suravee.Suthikulpanit@amd.com>
X-Patchwork-Id: 11531203
Return-Path: <SRS0=qN9b=6U=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id CD9AD1392
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed,  6 May 2020 13:18:36 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id B096120757
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed,  6 May 2020 13:18:36 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=amdcloud.onmicrosoft.com
 header.i=@amdcloud.onmicrosoft.com header.b="r5/BXOgj"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728524AbgEFNSY (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 6 May 2020 09:18:24 -0400
Received: from mail-eopbgr760078.outbound.protection.outlook.com
 ([40.107.76.78]:6525
        "EHLO NAM02-CY1-obe.outbound.protection.outlook.com"
        rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org with ESMTP
        id S1728357AbgEFNSW (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 6 May 2020 09:18:22 -0400
ARC-Seal: i=1; a=rsa-sha256; s=arcselector9901; d=microsoft.com; cv=none;
 b=BIdghRBr9ZuajBWHpu8nvyBuf++5g6pIwrKlVGf74DOsYvtIAVBsFiKcfBE8ZrJ+0b8Osqo6UgpjlFfkVv111OufWgkq0y40kZd7PQe90zQn7JomZj7F/N6YciZtDBPWdQhe8/Xbaknh0Vk/QV+RZUEAudQA+izCu55kOCCqid6wI37rF9205GaagMf5miZ3f96Lz+vkSIQxwj9MmcuMLIkEsaPVpY2w6hP9RSw+kPyR+sbLIzfgA8lh5GkgrvdsvVC1yZ9vTjPtkIIXJDT59ucXrPe+mP4SnsWqxXLhJob3WXgiS9f703rChmcrAXcvKAXMpwdw0+Sy4Fbbn6Mgcw==
ARC-Message-Signature: i=1; a=rsa-sha256; c=relaxed/relaxed; d=microsoft.com;
 s=arcselector9901;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=3v7wsourL4SXYCDRkuXB0Pt4sYYRiDKwervsLaPKlF0=;
 b=YYjxcE0PhDw8hi2bj0K9fJP3QSluO30idBKw5cSYkXbNwYYaLCP2XokPrEMyODpGAd+0MJ7jZ8OqpsBhLjHJtQygJ+Z9n857g//PKXtlHIrwtHgOazF9xS78aId7KKI6vc7TvvY0tr+ZqOMd48o1+wpZSahVeLjt56U3rq28HJrDhYH6D8jRPC1yGcMrqNIyfrzUtxGwMRvd+5BwuqZmMNYdW7zOJU+KyTph/FoFOZLOlq4h8Ze1U7jTPLZvW9AamhxQZ17bBltJwCPv7Kjjp9nQrRccZ7l/ENfVHDZyXHxk+wNJU5iaeHzQ/98El+E/MgzCqFvGS9YEuoAkps3fTA==
ARC-Authentication-Results: i=1; mx.microsoft.com 1; spf=pass
 smtp.mailfrom=amd.com; dmarc=pass action=none header.from=amd.com; dkim=pass
 header.d=amd.com; arc=none
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
 d=amdcloud.onmicrosoft.com; s=selector2-amdcloud-onmicrosoft-com;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=3v7wsourL4SXYCDRkuXB0Pt4sYYRiDKwervsLaPKlF0=;
 b=r5/BXOgjOmw6tk+UuqZujtrw/q3DGq3PxFKahiVy8SNZc6HKLEACVYRfOpCx8qXbi1iQ5kpRgRfkp9RBhO4JKuv2UQ2IEttUDOWthWueJACkcsNPQt+KqDQIxBYmNZeKJOVEQ8Q9CTghPU7KjvcCjmyx2z1tCm23TGHYOH0z1F8=
Authentication-Results: vger.kernel.org; dkim=none (message not signed)
 header.d=none;vger.kernel.org; dmarc=none action=none header.from=amd.com;
Received: from DM5PR12MB1163.namprd12.prod.outlook.com (2603:10b6:3:7a::18) by
 DM5PR12MB1258.namprd12.prod.outlook.com (2603:10b6:3:79::14) with Microsoft
 SMTP Server (version=TLS1_2, cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id
 15.20.2958.29; Wed, 6 May 2020 13:18:14 +0000
Received: from DM5PR12MB1163.namprd12.prod.outlook.com
 ([fe80::d061:4c5:954e:4744]) by DM5PR12MB1163.namprd12.prod.outlook.com
 ([fe80::d061:4c5:954e:4744%4]) with mapi id 15.20.2958.030; Wed, 6 May 2020
 13:18:14 +0000
From: Suravee Suthikulpanit <suravee.suthikulpanit@amd.com>
To: linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Cc: pbonzini@redhat.com, joro@8bytes.org, jon.grimm@amd.com,
        mlevitsk@redhat.com,
        Suravee Suthikulpanit <suravee.suthikulpanit@amd.com>
Subject: [PATCH 1/4] KVM: Introduce kvm_make_all_cpus_request_except()
Date: Wed,  6 May 2020 08:17:53 -0500
Message-Id: <1588771076-73790-2-git-send-email-suravee.suthikulpanit@amd.com>
X-Mailer: git-send-email 1.8.3.1
In-Reply-To: <1588771076-73790-1-git-send-email-suravee.suthikulpanit@amd.com>
References: <1588771076-73790-1-git-send-email-suravee.suthikulpanit@amd.com>
X-ClientProxiedBy: DM5PR12CA0071.namprd12.prod.outlook.com
 (2603:10b6:3:103::33) To DM5PR12MB1163.namprd12.prod.outlook.com
 (2603:10b6:3:7a::18)
MIME-Version: 1.0
X-MS-Exchange-MessageSentRepresentingType: 1
Received: from ssuthiku-rhel7-ssp.amd.com (165.204.78.2) by
 DM5PR12CA0071.namprd12.prod.outlook.com (2603:10b6:3:103::33) with Microsoft
 SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.2979.28 via Frontend
 Transport; Wed, 6 May 2020 13:18:14 +0000
X-Mailer: git-send-email 1.8.3.1
X-Originating-IP: [165.204.78.2]
X-MS-PublicTrafficType: Email
X-MS-Office365-Filtering-HT: Tenant
X-MS-Office365-Filtering-Correlation-Id: d439415a-5ec6-4af4-2410-08d7f1bfeee6
X-MS-TrafficTypeDiagnostic: DM5PR12MB1258:|DM5PR12MB1258:
X-MS-Exchange-Transport-Forked: True
X-Microsoft-Antispam-PRVS: 
 <DM5PR12MB125857A1D2F9684D88046FA4F3A40@DM5PR12MB1258.namprd12.prod.outlook.com>
X-MS-Oob-TLC-OOBClassifiers: OLM:2733;
X-Forefront-PRVS: 03950F25EC
X-MS-Exchange-SenderADCheck: 1
X-Microsoft-Antispam: BCL:0;
X-Microsoft-Antispam-Message-Info: 
 UCWBIHNxhEqMxq3Q+rrcZ7caL70sDhj+LcQ1IfO8HakqconFW9ENzvEd7gMZJbossg78QiGrxDB179C0Ag7cDksqTWturACV9dpLvX71useMBAK6mB+W+UDPe0XcLA6EUnHctS9IxoVxteEzqvFsL5VvP8OWYnAKnrTU5pTqViZmXDaWgqde3DgWKh/kuGUj8NoEWKZAZtO5BwzVNLLgvoqv3lnde3WKvgnOJP1WzArSuRdCpw/MzEScvh5dMgqoAMPRZVxtkvkzSZmV3FgrmGd4wsOynBOOAp0SbiR3uFQJdf3pjFUtmLdmNwMkPuahkJ8ZhnsZ3oXUuRuj938tNOLpLtOLV7R7IkpBysJS4rUu75K8vdaE2MYcf66jLxt6vYJ2PXoZus3tBQrvSlukYGuYCm+eF06UD26NMK2m2XmGAz53DNDJjCn1d+KQpdDbOJlogHs8JmatITNq/25vDFMrLbX/OH0zKyam05yPbgtZsGYCdXsqP0r2PrnHDHy2Znt8KiqZ+vD8lSXOVlhqeg==
X-Forefront-Antispam-Report: 
 CIP:255.255.255.255;CTRY:;LANG:en;SCL:1;SRV:;IPV:NLI;SFV:NSPM;H:DM5PR12MB1163.namprd12.prod.outlook.com;PTR:;CAT:NONE;SFTY:;SFS:(4636009)(366004)(39860400002)(376002)(136003)(396003)(346002)(33430700001)(5660300002)(66556008)(66476007)(66946007)(7696005)(52116002)(8676002)(478600001)(8936002)(44832011)(6666004)(2906002)(2616005)(956004)(6486002)(86362001)(316002)(33440700001)(26005)(16526019)(186003)(36756003)(4326008);DIR:OUT;SFP:1101;
X-MS-Exchange-AntiSpam-MessageData: 
 Dj84rSuQcEpK3guW7MCxl90u3L4dJv2KsaRt0K8N2ZqH0b/r0SYzs9ZOur49RMFdSLEeC00DcpIBn+PcI5Vg4YrP/IV6bj2xNPy3gK9kFxHMjS1Xq1z8fFT8ziIGdY2fVBysE4NCJtj649TU2iPOm1+QRRViyMrHgSHFSv/zcekthUhPH+9u4d7Yi3WeXhrSgUboraG2Ta6sQPIA40ZPtRnDez4Dau+cIfKKCBLkl2SYJkLJzzw1q/3XFPrrVXQ8c7ff0X4s77KtuytEEM4b2b3NVKRsxC+tB45I0Km+iyqtnfYJ57WCZwZ0Meh+saGqRSN6NXYfwgekhRgLFLYUKfRwQJ1fmQIEuxQ0X+ifd7/sxInLlC1kd1SHj0NkXb7h79sTkNKiqY1/wgWc2kdXm/4rOnVAlW9LV3bALhVLcrijGAWeKunuqanx+39m0UHBoDqrTFHQwPIQ0ZM3DmsNZJGdqTEFw0DiF7jn6RYb94S9+U19leIDMEQq/sUMtfLNFKknI26+LwRL56NdKzobMF1XA3geVwWiqDBzOFF2O4OHEgpcfC1qhGC0sNE3g32KDMBVsF9/to2nt64QIvycFROMYRWcD5s8ap6Wfs+Qz85oOlFizOLunW6CAyB2PeWZ3O0c/HTWxMXR0e4bgb+gnSd9RqKOhqFeHEEs51q0rqNFeOu1x9mj2Oh9D0ZSSIILLdzOVvLpPfXr0RvdheTTMYDCCK+y4W7ORn6Q2/VPbLnbPfgz56wv501heq04W1B5HK/9y6B7SeLWbYh4IyWkaRYCKDpm0QyaNgy6wuRFjlc=
X-OriginatorOrg: amd.com
X-MS-Exchange-CrossTenant-Network-Message-Id: 
 d439415a-5ec6-4af4-2410-08d7f1bfeee6
X-MS-Exchange-CrossTenant-OriginalArrivalTime: 06 May 2020 13:18:14.7800
 (UTC)
X-MS-Exchange-CrossTenant-FromEntityHeader: Hosted
X-MS-Exchange-CrossTenant-Id: 3dd8961f-e488-4e60-8e11-a82d994e183d
X-MS-Exchange-CrossTenant-MailboxType: HOSTED
X-MS-Exchange-CrossTenant-UserPrincipalName: 
 n8yOQl8garQ6ELp4eeQLbrXqH0KRat9lf/OVmacn7EtkcWyaoU+5RAhZh6zhslHkTcvcZzH3zuVfWTeMGmDpdA==
X-MS-Exchange-Transport-CrossTenantHeadersStamped: DM5PR12MB1258
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This allows making request to all other vcpus except the one
specified in the parameter.

Signed-off-by: Suravee Suthikulpanit <suravee.suthikulpanit@amd.com>
---
 arch/x86/kvm/hyperv.c    |  2 +-
 arch/x86/kvm/x86.c       |  2 +-
 include/linux/kvm_host.h |  3 +++
 virt/kvm/kvm_main.c      | 14 +++++++++++---
 4 files changed, 16 insertions(+), 5 deletions(-)

```
#### [kvm-unit-tests RFC] s390x: Add Protected VM support
##### From: Marc Hartmayer <mhartmay@linux.ibm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Marc Hartmayer <mhartmay@linux.ibm.com>
X-Patchwork-Id: 11531173
Return-Path: <SRS0=qN9b=6U=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id CE23D139F
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed,  6 May 2020 12:47:16 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id B896120757
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed,  6 May 2020 12:47:16 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728298AbgEFMrQ (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 6 May 2020 08:47:16 -0400
Received: from mx0b-001b2d01.pphosted.com ([148.163.158.5]:18436 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S1727953AbgEFMrP (ORCPT
        <rfc822;kvm@vger.kernel.org>); Wed, 6 May 2020 08:47:15 -0400
Received: from pps.filterd (m0098416.ppops.net [127.0.0.1])
        by mx0b-001b2d01.pphosted.com (8.16.0.42/8.16.0.42) with SMTP id
 046CVVWT031516;
        Wed, 6 May 2020 08:47:13 -0400
Received: from pps.reinject (localhost [127.0.0.1])
        by mx0b-001b2d01.pphosted.com with ESMTP id 30s2g42r5f-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Wed, 06 May 2020 08:47:13 -0400
Received: from m0098416.ppops.net (m0098416.ppops.net [127.0.0.1])
        by pps.reinject (8.16.0.36/8.16.0.36) with SMTP id 046CVhcp032916;
        Wed, 6 May 2020 08:47:13 -0400
Received: from ppma04ams.nl.ibm.com (63.31.33a9.ip4.static.sl-reverse.com
 [169.51.49.99])
        by mx0b-001b2d01.pphosted.com with ESMTP id 30s2g42r4q-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Wed, 06 May 2020 08:47:13 -0400
Received: from pps.filterd (ppma04ams.nl.ibm.com [127.0.0.1])
        by ppma04ams.nl.ibm.com (8.16.0.27/8.16.0.27) with SMTP id
 046CjRPC027100;
        Wed, 6 May 2020 12:47:11 GMT
Received: from b06cxnps4076.portsmouth.uk.ibm.com
 (d06relay13.portsmouth.uk.ibm.com [9.149.109.198])
        by ppma04ams.nl.ibm.com with ESMTP id 30s0g5s5g9-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Wed, 06 May 2020 12:47:11 +0000
Received: from d06av24.portsmouth.uk.ibm.com (mk.ibm.com [9.149.105.60])
        by b06cxnps4076.portsmouth.uk.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id 046Cl83243647108
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Wed, 6 May 2020 12:47:08 GMT
Received: from d06av24.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id B1FFB42047;
        Wed,  6 May 2020 12:47:08 +0000 (GMT)
Received: from d06av24.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 4AD8942042;
        Wed,  6 May 2020 12:47:08 +0000 (GMT)
Received: from marcibm.ibmuc.com (unknown [9.145.158.168])
        by d06av24.portsmouth.uk.ibm.com (Postfix) with ESMTP;
        Wed,  6 May 2020 12:47:08 +0000 (GMT)
From: Marc Hartmayer <mhartmay@linux.ibm.com>
To: <kvm@vger.kernel.org>
Cc: Thomas Huth <thuth@redhat.com>,
        David Hildenbrand <david@redhat.com>,
        Janosch Frank <frankja@linux.ibm.com>,
        Cornelia Huck <cohuck@redhat.com>,
        Andrew Jones <drjones@redhat.com>,
        Paolo Bonzini <pbonzini@redhat.com>,
        Christian Borntraeger <borntraeger@de.ibm.com>,
        linux-s390@vger.kernel.org
Subject: [kvm-unit-tests RFC] s390x: Add Protected VM support
Date: Wed,  6 May 2020 14:46:36 +0200
Message-Id: <20200506124636.21876-1-mhartmay@linux.ibm.com>
X-Mailer: git-send-email 2.25.4
MIME-Version: 1.0
X-TM-AS-GCONF: 00
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.138,18.0.676
 definitions=2020-05-06_05:2020-05-05,2020-05-06 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 mlxscore=0 malwarescore=0
 suspectscore=1 bulkscore=0 priorityscore=1501 spamscore=0
 lowpriorityscore=0 adultscore=0 phishscore=0 mlxlogscore=999 clxscore=1011
 impostorscore=0 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.12.0-2003020000 definitions=main-2005060095
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Add support for Protected Virtual Machine (PVM) tests. For starting a
PVM guest we must be able to generate a PVM image by using the
`genprotimg` tool from the s390-tools collection. This requires the
ability to pass a machine-specific host-key document, so the option
`--host-key-document` is added to the configure script.

Signed-off-by: Marc Hartmayer <mhartmay@linux.ibm.com>
---
 .gitignore          |  1 +
 configure           |  8 ++++++++
 s390x/Makefile      | 16 +++++++++++++---
 s390x/unittests.cfg | 20 ++++++++++++++++++++
 scripts/common.bash | 30 +++++++++++++++++++++++++++++-
 5 files changed, 71 insertions(+), 4 deletions(-)

```
#### [kvm-unit-tests PATCH v2] x86: Add test cases for user-mode CET validation
##### From: Yang Weijiang <weijiang.yang@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Yang Weijiang <weijiang.yang@intel.com>
X-Patchwork-Id: 11530677
Return-Path: <SRS0=qN9b=6U=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 5F11E1392
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed,  6 May 2020 08:20:09 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 437B020735
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed,  6 May 2020 08:20:09 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728863AbgEFIUI (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 6 May 2020 04:20:08 -0400
Received: from mga12.intel.com ([192.55.52.136]:35429 "EHLO mga12.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1728858AbgEFITz (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 6 May 2020 04:19:55 -0400
IronPort-SDR: 
 VqJKZEEzcdj1YgKSpINlDgDJJq2b3p91DsXx7MFsjzKuz2T8/jpkWIKB/ocVHJhoxD6IA8YKj+
 2T75cRtCPCOA==
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from orsmga003.jf.intel.com ([10.7.209.27])
  by fmsmga106.fm.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 06 May 2020 01:19:54 -0700
IronPort-SDR: 
 yli7e7APvdlvEK0vLCZxya489KoOSZC+VfTXK7gDuEQWGG7ScvFsgcaEI6a3yXTdty0DygbAF2
 ImdOjSbG6S8w==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.73,358,1583222400";
   d="scan'208";a="260030142"
Received: from unknown (HELO local-michael-cet-test.sh.intel.com)
 ([10.239.159.128])
  by orsmga003.jf.intel.com with ESMTP; 06 May 2020 01:19:52 -0700
From: Yang Weijiang <weijiang.yang@intel.com>
To: kvm@vger.kernel.org, linux-kernel@vger.kernel.org,
        pbonzini@redhat.com, sean.j.christopherson@intel.com,
        jmattson@google.com
Cc: yu.c.zhang@linux.intel.com, Yang Weijiang <weijiang.yang@intel.com>
Subject: [kvm-unit-tests PATCH v2] x86: Add test cases for user-mode CET
 validation
Date: Wed,  6 May 2020 16:21:10 +0800
Message-Id: <20200506082110.25441-12-weijiang.yang@intel.com>
X-Mailer: git-send-email 2.17.2
In-Reply-To: <20200506082110.25441-1-weijiang.yang@intel.com>
References: <20200506082110.25441-1-weijiang.yang@intel.com>
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This unit test is intended to test user-mode CET support of KVM,
it's tested on Intel new platform. Two CET features: Shadow Stack
Protection(SHSTK) and Indirect-Branch Tracking(IBT) are enclosed.

In SHSTK test, if the function return-address in normal stack is
tampered with a value not equal to the one on shadow-stack, #CP
(Control Protection Exception)will generated on function returning.
This feature is supported by processor itself, no compiler/link
option is required.

However, to enabled IBT, we need to add -fcf-protection=full in
compiler options, this makes the compiler insert endbr64 at the
very beginning of each jmp/call target given the binary is for
x86_64.

To get PASS results, the following conditions must be met:
1) The processor is powered with CET feature.
2) The kernel is patched with the latest CET kernel patches.
3) The KVM and QEMU are patched with the latest CET patches.
4) Use CET-enabled gcc to compile the test app.

v2:
- Removed extra dependency on test framework for user/kernel mode switch.
- Directly set #CP handler instead of through TSS.

Signed-off-by: Yang Weijiang <weijiang.yang@intel.com>
---
 lib/x86/desc.c      |   2 +
 lib/x86/msr.h       |   2 +
 lib/x86/processor.h |   3 +
 x86/Makefile.common |   3 +-
 x86/Makefile.x86_64 |   3 +-
 x86/cet.c           | 205 ++++++++++++++++++++++++++++++++++++++++++++
 x86/unittests.cfg   |   6 ++
 7 files changed, 222 insertions(+), 2 deletions(-)
 create mode 100644 x86/cet.c

```
#### [PATCH] KVM: VMX: Explicitly clear RFLAGS.CF and RFLAGS.ZF in VM-Exit RSB path
##### From: Sean Christopherson <sean.j.christopherson@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Sean Christopherson <sean.j.christopherson@intel.com>
X-Patchwork-Id: 11530185
Return-Path: <SRS0=qN9b=6U=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 38C1915AB
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed,  6 May 2020 03:54:04 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 2565C2075E
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed,  6 May 2020 03:54:04 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726744AbgEFDyB (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 5 May 2020 23:54:01 -0400
Received: from mga09.intel.com ([134.134.136.24]:58810 "EHLO mga09.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726495AbgEFDyB (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 5 May 2020 23:54:01 -0400
IronPort-SDR: 
 Ii4BPnUjy6z8kDg9x5kQNoyGAQqpetxcqGgTuhEZRxCJ+rGjwW2dnR1pjJ7obW0HfGR46w2jum
 Ob6u1Fbm4adg==
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from fmsmga005.fm.intel.com ([10.253.24.32])
  by orsmga102.jf.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 05 May 2020 20:53:56 -0700
IronPort-SDR: 
 RnY/CkTVHGDllTWl3vsALQBX8FyOb9RmSDv/9J4Oj1pJg9ax+A6NZxcyLyU93gQX7ft9fjdsk6
 jV1WhhTCDb9A==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.73,357,1583222400";
   d="scan'208";a="461286084"
Received: from sjchrist-coffee.jf.intel.com ([10.54.74.152])
  by fmsmga005.fm.intel.com with ESMTP; 05 May 2020 20:53:56 -0700
From: Sean Christopherson <sean.j.christopherson@intel.com>
To: Paolo Bonzini <pbonzini@redhat.com>
Cc: Sean Christopherson <sean.j.christopherson@intel.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org, Qian Cai <cai@lca.pw>,
        Rick Edgecombe <rick.p.edgecombe@intel.com>,
        Peter Zijlstra <peterz@infradead.org>,
        Josh Poimboeuf <jpoimboe@redhat.com>
Subject: [PATCH] KVM: VMX: Explicitly clear RFLAGS.CF and RFLAGS.ZF in VM-Exit
 RSB path
Date: Tue,  5 May 2020 20:53:55 -0700
Message-Id: <20200506035355.2242-1-sean.j.christopherson@intel.com>
X-Mailer: git-send-email 2.26.0
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Clear CF and ZF in the VM-Exit path after doing __FILL_RETURN_BUFFER so
that KVM doesn't interpret clobbered RFLAGS as a VM-Fail.  Filling the
RSB has always clobbered RFLAGS, its current incarnation just happens
clear CF and ZF in the processs.  Relying on the macro to clear CF and
ZF is extremely fragile, e.g. commit 089dd8e53126e ("x86/speculation:
Change FILL_RETURN_BUFFER to work with objtool") tweaks the loop such
that the ZF flag is always set.

Reported-by: Qian Cai <cai@lca.pw>
Cc: Rick Edgecombe <rick.p.edgecombe@intel.com>
Cc: Peter Zijlstra (Intel) <peterz@infradead.org>
Cc: Josh Poimboeuf <jpoimboe@redhat.com>
Cc: stable@vger.kernel.org
Fixes: f2fde6a5bcfcf ("KVM: VMX: Move RSB stuffing to before the first RET after VM-Exit")
Signed-off-by: Sean Christopherson <sean.j.christopherson@intel.com>
---
 arch/x86/kvm/vmx/vmenter.S | 3 +++
 1 file changed, 3 insertions(+)

```
#### [PATCH 1/7] KVM: VMX: Introduce generic fastpath handler
##### From: Paolo Bonzini <pbonzini@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Paolo Bonzini <pbonzini@redhat.com>
X-Patchwork-Id: 11531487
Return-Path: <SRS0=qN9b=6U=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id C111B1392
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed,  6 May 2020 16:11:35 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id A896120936
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed,  6 May 2020 16:11:35 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="f1zstsF2"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1730092AbgEFQK6 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 6 May 2020 12:10:58 -0400
Received: from us-smtp-2.mimecast.com ([205.139.110.61]:27730 "EHLO
        us-smtp-delivery-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S1729688AbgEFQK5 (ORCPT
        <rfc822;kvm@vger.kernel.org>); Wed, 6 May 2020 12:10:57 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1588781455;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:in-reply-to:in-reply-to:references:references;
        bh=kZPPxriWZX6GKqib57CUR0KHurjWMqJXVQoLVEPp5t4=;
        b=f1zstsF2BwvoIVYFb+z+mQqgKv0mbca5HQ4uU7U5WS8cQ+tjqPxBm9Ap/XjWhbnlvo2WN6
        habu9FoIJf3zomYkByzK9JLuy70p4stMiZIXznWXCqJZC8JvTlinlGf/Z9CHhCue4+IR57
        4CQoEb4Q6DHxC/H2pSgMnZMSlaS1mXk=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-470-Pk5GFsTpPHCClfx87srNYQ-1; Wed, 06 May 2020 12:10:53 -0400
X-MC-Unique: Pk5GFsTpPHCClfx87srNYQ-1
Received: from smtp.corp.redhat.com (int-mx08.intmail.prod.int.phx2.redhat.com
 [10.5.11.23])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id CFB2880058A;
        Wed,  6 May 2020 16:10:51 +0000 (UTC)
Received: from virtlab701.virt.lab.eng.bos.redhat.com
 (virtlab701.virt.lab.eng.bos.redhat.com [10.19.152.228])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 81A2527C39;
        Wed,  6 May 2020 16:10:50 +0000 (UTC)
From: Paolo Bonzini <pbonzini@redhat.com>
To: linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Cc: wanpengli@tencent.com, linxl3@wangsu.com,
        Haiwei Li <lihaiwei@tencent.com>
Subject: [PATCH 1/7] KVM: VMX: Introduce generic fastpath handler
Date: Wed,  6 May 2020 12:10:42 -0400
Message-Id: <20200506161048.28840-2-pbonzini@redhat.com>
In-Reply-To: <20200506161048.28840-1-pbonzini@redhat.com>
References: <20200506161048.28840-1-pbonzini@redhat.com>
X-Scanned-By: MIMEDefang 2.84 on 10.5.11.23
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Wanpeng Li <wanpengli@tencent.com>

Introduce generic fastpath handler to handle MSR fastpath, VMX-preemption
timer fastpath etc; move it after vmx_complete_interrupts() in order to
catch events delivered to the guest, and abort the fast path in later
patches.  While at it, move the kvm_exit tracepoint so that it is printed
for fastpath vmexits as well.

There is no observed performance effect for the IPI fastpath after this patch.

Tested-by: Haiwei Li <lihaiwei@tencent.com>
Cc: Haiwei Li <lihaiwei@tencent.com>
Signed-off-by: Wanpeng Li <wanpengli@tencent.com>
Suggested-by: Sean Christopherson <sean.j.christopherson@intel.com>
Message-Id: <1588055009-12677-2-git-send-email-wanpengli@tencent.com>
Reviewed-by: Vitaly Kuznetsov <vkuznets@redhat.com>
Signed-off-by: Paolo Bonzini <pbonzini@redhat.com>
---
 arch/x86/kvm/vmx/vmx.c | 23 ++++++++++++++++-------
 1 file changed, 16 insertions(+), 7 deletions(-)

```
#### [PATCH] KVM: x86: pass correct DR6 for GD userspace exit
##### From: Paolo Bonzini <pbonzini@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Paolo Bonzini <pbonzini@redhat.com>
X-Patchwork-Id: 11530969
Return-Path: <SRS0=qN9b=6U=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 309FB913
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed,  6 May 2020 10:00:25 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 190732075A
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed,  6 May 2020 10:00:25 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="GFrtjBBR"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728537AbgEFKAY (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 6 May 2020 06:00:24 -0400
Received: from us-smtp-delivery-1.mimecast.com ([205.139.110.120]:22983 "EHLO
        us-smtp-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org
        with ESMTP id S1728180AbgEFKAY (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 6 May 2020 06:00:24 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1588759223;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc; bh=V+s+EVTjLJSoyQgVEndJ36QCIydluEdbqn+8ObHr7LM=;
        b=GFrtjBBRSw0u6LrYQ9k7W3tMskFqCOQm9SHi4hclcoR5U6/QnWdijZmj54pcQD+T9DgM6f
        LMIk+WdzGoRfa/mBawYCgWP3LrSVfRmoNtq9bXBfKJRaHUrsomdbwCEdSqY0jo4SWpV+AW
        XEvkTWaP0ERlhRW7I+oxXWzbzZTKoeA=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-358-FuhPtV1tOs20XK-JbOdIAQ-1; Wed, 06 May 2020 06:00:18 -0400
X-MC-Unique: FuhPtV1tOs20XK-JbOdIAQ-1
Received: from smtp.corp.redhat.com (int-mx05.intmail.prod.int.phx2.redhat.com
 [10.5.11.15])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id F0B9B106B242;
        Wed,  6 May 2020 10:00:17 +0000 (UTC)
Received: from virtlab701.virt.lab.eng.bos.redhat.com
 (virtlab701.virt.lab.eng.bos.redhat.com [10.19.152.228])
        by smtp.corp.redhat.com (Postfix) with ESMTP id B92446294E;
        Wed,  6 May 2020 10:00:14 +0000 (UTC)
From: Paolo Bonzini <pbonzini@redhat.com>
To: linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Cc: peterx@redhat.com
Subject: [PATCH] KVM: x86: pass correct DR6 for GD userspace exit
Date: Wed,  6 May 2020 06:00:14 -0400
Message-Id: <20200506100014.7451-1-pbonzini@redhat.com>
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.15
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

When KVM_EXIT_DEBUG is raised for the disabled-breakpoints case (DR7.GD),
DR6 was incorrectly copied from the value in the VM.  Instead,
DR6.BD should be set in order to catch this case.

Signed-off-by: Paolo Bonzini <pbonzini@redhat.com>
---
 arch/x86/kvm/vmx/vmx.c                        |  2 +-
 .../testing/selftests/kvm/x86_64/debug_regs.c | 24 ++++++++++++++++++-
 2 files changed, 24 insertions(+), 2 deletions(-)

```
#### [PATCH] kvm: x86: Use KVM CPU capabilities to determine CR4 reserved bits
##### From: Paolo Bonzini <pbonzini@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Paolo Bonzini <pbonzini@redhat.com>
X-Patchwork-Id: 11530889
Return-Path: <SRS0=qN9b=6U=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 03EA481
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed,  6 May 2020 09:44:44 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id E10AF2070B
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed,  6 May 2020 09:44:43 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="hTiu3o+P"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729232AbgEFJom (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 6 May 2020 05:44:42 -0400
Received: from us-smtp-delivery-1.mimecast.com ([207.211.31.120]:55502 "EHLO
        us-smtp-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org
        with ESMTP id S1729164AbgEFJol (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 6 May 2020 05:44:41 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1588758280;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc; bh=U3jHrb3ElqPyuqAafMEzJZ29hoRVGrLR/TI1FtwisFA=;
        b=hTiu3o+PYiHmj/8AAUn5tAeGLDNQlPlnzj5jv4jmcGQ08bBK5sqh9XDHhGSO4lHbxu4onO
        8TYSUXbjERorOsTeCGwbTFUd/FtLBShymSKyDPYl5GepnJOPv40BwlJ8vXkfPNJwBw3/s7
        ARxZEo0Mc+RM/o0s9f09hYx96+iNzSo=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-437-b6TwxCKoNd2qSp1btsNAgg-1; Wed, 06 May 2020 05:44:38 -0400
X-MC-Unique: b6TwxCKoNd2qSp1btsNAgg-1
Received: from smtp.corp.redhat.com (int-mx02.intmail.prod.int.phx2.redhat.com
 [10.5.11.12])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 918001005510;
        Wed,  6 May 2020 09:44:37 +0000 (UTC)
Received: from virtlab701.virt.lab.eng.bos.redhat.com
 (virtlab701.virt.lab.eng.bos.redhat.com [10.19.152.228])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 0C24060C18;
        Wed,  6 May 2020 09:44:36 +0000 (UTC)
From: Paolo Bonzini <pbonzini@redhat.com>
To: linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Cc: jmattson@google.com,
        Sean Christopherson <sean.j.christopherson@intel.com>
Subject: [PATCH] kvm: x86: Use KVM CPU capabilities to determine CR4 reserved
 bits
Date: Wed,  6 May 2020 05:44:36 -0400
Message-Id: <20200506094436.3202-1-pbonzini@redhat.com>
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.12
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Using CPUID data can be useful for the processor compatibility
check, but that's it.  Using it to compute guest-reserved bits
can have both false positives (such as LA57 and UMIP which we
are already handling) and false negatives: in particular, with
this patch we don't allow anymore a KVM guest to set CR4.PKE
when CR4.PKE is clear on the host.

Fixes: b9dd21e104bc ("KVM: x86: simplify handling of PKRU")
Reported-by: Jim Mattson <jmattson@google.com>
Tested-by: Jim Mattson <jmattson@google.com>
Signed-off-by: Paolo Bonzini <pbonzini@redhat.com>
---
 arch/x86/kvm/x86.c | 20 +++++---------------
 1 file changed, 5 insertions(+), 15 deletions(-)

```
#### [PATCH v2 06/20] mips: Add MIPS32 Release 5 support
##### From: <Sergey.Semin@baikalelectronics.ru>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Serge Semin <Sergey.Semin@baikalelectronics.ru>
X-Patchwork-Id: 11531665
Return-Path: <SRS0=qN9b=6U=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id AE44B17EF
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed,  6 May 2020 17:49:44 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 80748214D8
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed,  6 May 2020 17:49:44 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729755AbgEFRtn (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 6 May 2020 13:49:43 -0400
Received: from mail.baikalelectronics.com ([87.245.175.226]:33064 "EHLO
        mail.baikalelectronics.ru" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1729895AbgEFRtn (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 6 May 2020 13:49:43 -0400
X-Greylist: delayed 344 seconds by postgrey-1.27 at vger.kernel.org;
 Wed, 06 May 2020 13:49:34 EDT
Received: from localhost (unknown [127.0.0.1])
        by mail.baikalelectronics.ru (Postfix) with ESMTP id 5742E8030808;
        Wed,  6 May 2020 17:43:49 +0000 (UTC)
X-Virus-Scanned: amavisd-new at baikalelectronics.ru
Received: from mail.baikalelectronics.ru ([127.0.0.1])
        by localhost (mail.baikalelectronics.ru [127.0.0.1]) (amavisd-new,
 port 10024)
        with ESMTP id EMj4x1RkBeIT; Wed,  6 May 2020 20:43:47 +0300 (MSK)
From: <Sergey.Semin@baikalelectronics.ru>
To: Thomas Bogendoerfer <tsbogend@alpha.franken.de>
CC: Serge Semin <Sergey.Semin@baikalelectronics.ru>,
 Serge Semin <fancer.lancer@gmail.com>,
 Alexey Malahov <Alexey.Malahov@baikalelectronics.ru>,
 Paul Burton <paulburton@kernel.org>, Ralf Baechle <ralf@linux-mips.org>,
 Arnd Bergmann <arnd@arndb.de>, Rob Herring <robh+dt@kernel.org>,
 <linux-pm@vger.kernel.org>, <devicetree@vger.kernel.org>,
 Thomas Bogendoerfer <tbogendoerfer@suse.de>,
 Jiaxun Yang <jiaxun.yang@flygoat.com>, Huacai Chen <chenhc@lemote.com>,
 Alexander Lobakin <alobakin@dlink.ru>, Daniel Silsby <dansilsby@gmail.com>,
	=?utf-8?q?Ren=C3=A9_van_Dorst?= <opensource@vdorst.com>,
 Cedric Hombourger <Cedric_Hombourger@mentor.com>,
 Ard Biesheuvel <ardb@kernel.org>, Thomas Gleixner <tglx@linutronix.de>,
 Sebastian Andrzej Siewior <bigeasy@linutronix.de>,
 Ingo Molnar <mingo@kernel.org>,
 =?utf-8?q?Philippe_Mathieu-Daud=C3=A9?= <f4bug@amsat.org>,
 Guenter Roeck <linux@roeck-us.net>, Paul Cercueil <paul@crapouillou.net>,
 Masahiro Yamada <masahiroy@kernel.org>,
 Greg Kroah-Hartman <gregkh@linuxfoundation.org>,
 Allison Randal <allison@lohutok.net>,
 "Peter Zijlstra (Intel)" <peterz@infradead.org>,
 Jessica Yu <jeyu@kernel.org>, Zhou Yanjie <zhouyanjie@zoho.com>,
	=?utf-8?b?5ZGo55Cw5p2wIChaaG91IFlhbmppZSk=?=  <zhouyanjie@wanyeetech.com>,
 Kamal Dasu <kdasu.kdev@gmail.com>, Oleksij Rempel <linux@rempel-privat.de>,
 <linux-mips@vger.kernel.org>, <linux-kernel@vger.kernel.org>,
 <kvm@vger.kernel.org>
Subject: [PATCH v2 06/20] mips: Add MIPS32 Release 5 support
Date: Wed, 6 May 2020 20:42:24 +0300
Message-ID: <20200506174238.15385-7-Sergey.Semin@baikalelectronics.ru>
In-Reply-To: <20200506174238.15385-1-Sergey.Semin@baikalelectronics.ru>
References: <20200306124807.3596F80307C2@mail.baikalelectronics.ru>
 <20200506174238.15385-1-Sergey.Semin@baikalelectronics.ru>
MIME-Version: 1.0
X-ClientProxiedBy: MAIL.baikal.int (192.168.51.25) To mail (192.168.51.25)
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Serge Semin <Sergey.Semin@baikalelectronics.ru>

There are five MIPS32/64 architecture releases currently available:
from 1 to 6 except fourth one, which was intentionally skipped.
Three of them can be called as major: 1st, 2nd and 6th, that not only
have some system level alterations, but also introduced significant
core/ISA level updates. The rest of the MIPS architecture releases are
minor.

Even though they don't have as much ISA/system/core level changes
as the major ones with respect to the previous releases, they still
provide a set of updates (I'd say they were intended to be the
intermediate releases before a major one) that might be useful for the
kernel and user-level code, when activated by the kernel or compiler.
In particular the following features were introduced or ended up being
available at/after MIPS32 Release 5 architecture:
+ the last release of the misaligned memory access instructions,
+ virtualisation - VZ ASE - is optional component of the arch,
+ SIMD - MSA ASE - is optional component of the arch,
+ DSP ASE is optional component of the arch,
+ CP0.Status.FR=1 for CP1.FIR.F64=1 (pure 64-bit FPU general registers)
  must be available if FPU is implemented,
+ CP1.FIR.Has2008 support is required so CP1.FCSR.{ABS2008,NAN2008} bits
  are available.
+ UFR/UNFR aliases to access CP0.Status.FR from user-space by means of
  ctc1/cfc1 instructions (enabled by CP0.Config5.UFR),
+ CP0.COnfig5.LLB=1 and eretnc instruction are implemented to without
  accidentally clearing LL-bit when returning from an interrupt,
  exception, or error trap,
+ XPA feature together with extended versions of CPx registers is
  introduced, which needs to have mfhc0/mthc0 instructions available.

So due to these changes GNU GCC provides an extended instructions set
support for MIPS32 Release 5 by default like eretnc/mfhc0/mthc0. Even
though the architecture alteration isn't that big, it still worth to be
taken into account by the kernel software. Finally we can't deny that
some optimization/limitations might be found in future and implemented
on some level in kernel or compiler. In this case having even
intermediate MIPS architecture releases support would be more than
useful.

So the most of the changes provided by this commit can be split into
either compile- or runtime configs related. The compile-time related
changes are caused by adding the new CONFIG_CPU_MIPS32_R5/CONFIG_CPU_MIPSR5
configs and concern the code activating MIPSR2 or MIPSR6 already
implemented features (like eretnc/LLbit, mthc0/mfhc0). In addition
CPU_HAS_MSA can be now freely enabled for MIPS32 release 5 based
platforms as this is done for CPU_MIPS32_R6 CPUs. The runtime changes
concerns the features which are handled with respect to the MIPS ISA
revision detected at run-time by means of CP0.Config.{AT,AR} bits. Alas
these fields can be used to detect either r1 or r2 or r6 releases.
But since we know which CPUs in fact support the R5 arch, we can manually
set MIPS_CPU_ISA_M32R5 bit of c->isa_level and then use cpu_has_mips32_r5
where it's appropriate.

Since XPA/EVA provide too complex alterationss and to have them used with
MIPS32 Release 2 charged kernels (for compatibility with current platform
configs) they are left to be setup as a separate kernel configs.

Co-developed-by: Alexey Malahov <Alexey.Malahov@baikalelectronics.ru>
Signed-off-by: Alexey Malahov <Alexey.Malahov@baikalelectronics.ru>
Signed-off-by: Serge Semin <Sergey.Semin@baikalelectronics.ru>
Cc: Thomas Bogendoerfer <tsbogend@alpha.franken.de>
Cc: Paul Burton <paulburton@kernel.org>
Cc: Ralf Baechle <ralf@linux-mips.org>
Cc: Arnd Bergmann <arnd@arndb.de>
Cc: Rob Herring <robh+dt@kernel.org>
Cc: linux-pm@vger.kernel.org
Cc: devicetree@vger.kernel.org
---
Even without this patch the code contains too many patterns like:
+#if defined(CONFIG_MIPS32R2) || defined(CONFIG_MIPS32R6)
What about switching it to a simpler
+#if CONFIG_TARGET_ISA_REV >= 2 ?
Though I'd prefer this config to be named like CONFIG_CPU_MIPS_REV.
What do you think?

Similarly the pattern like:
(MIPS_CPU_ISA_M32R1 | MIPS_CPU_ISA_M64R1 |
 MIPS_CPU_ISA_M32R2 | MIPS_CPU_ISA_M64R2 |
 MIPS_CPU_ISA_M32R5 |
 MIPS_CPU_ISA_M32R6 | MIPS_CPU_ISA_M64R6)
could be replaced with simpler one:
(MIPS_CPU_ISA_M32 | MIPS_CPU_ISA_M64)
if corresponding macro were available. What do think about adding such?

We also could add CPU_MIPS64_R5 config support here, but I don't think
it's necessary at the moment seeing there is no any real chip ever
produced with that arch. Right?
---
 arch/mips/Kconfig                    | 34 ++++++++++++++++++++++++----
 arch/mips/Makefile                   |  1 +
 arch/mips/include/asm/asmmacro.h     | 18 ++++++++-------
 arch/mips/include/asm/compiler.h     |  5 ++++
 arch/mips/include/asm/cpu-features.h | 20 +++++++++++-----
 arch/mips/include/asm/cpu-info.h     |  2 +-
 arch/mips/include/asm/cpu-type.h     |  6 ++++-
 arch/mips/include/asm/cpu.h          |  7 +++---
 arch/mips/include/asm/fpu.h          |  4 ++--
 arch/mips/include/asm/hazards.h      |  8 ++++---
 arch/mips/include/asm/stackframe.h   |  2 +-
 arch/mips/include/asm/switch_to.h    |  8 +++----
 arch/mips/include/asm/vermagic.h     |  2 ++
 arch/mips/kernel/cpu-probe.c         | 12 ++++++++++
 arch/mips/kernel/entry.S             |  6 ++---
 arch/mips/kernel/proc.c              |  2 ++
 arch/mips/kernel/r4k_fpu.S           | 14 ++++++------
 arch/mips/kvm/vz.c                   |  6 ++---
 arch/mips/lib/csum_partial.S         |  6 +++--
 arch/mips/mm/c-r4k.c                 |  7 +++---
 arch/mips/mm/sc-mips.c               |  7 +++---
 21 files changed, 123 insertions(+), 54 deletions(-)

```
#### [PATCH v2] KVM: x86: fix DR6 delivery for various cases of #DB injection
##### From: Paolo Bonzini <pbonzini@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Paolo Bonzini <pbonzini@redhat.com>
X-Patchwork-Id: 11530779
Return-Path: <SRS0=qN9b=6U=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 235221392
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed,  6 May 2020 09:22:35 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 0A97E2073A
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed,  6 May 2020 09:22:35 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="MElx+Mzy"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728887AbgEFJWb (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 6 May 2020 05:22:31 -0400
Received: from us-smtp-2.mimecast.com ([205.139.110.61]:38088 "EHLO
        us-smtp-delivery-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S1728857AbgEFJWb (ORCPT
        <rfc822;kvm@vger.kernel.org>); Wed, 6 May 2020 05:22:31 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1588756950;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc; bh=CBdTHlgR58fqrVhQa11e/qboBcj6G8ntplKxPy2GBxU=;
        b=MElx+MzyDkY8Q38uCP2mANKG+TIM4AtFd+ao4K9JUq7xInl1Gm9hlHlEr5CdiyyOrPG6Lh
        BogQeWcJSZXjvHoqxmLtra7niwN6uW0WY2CBQv68fR4JMqIy3fuImfb8RG1GTukpd4nmck
        BfguvQxvpyTZhHWIIazPn8sri/9QvQ4=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-508-AJeojHx0OeioLnMVoERQNA-1; Wed, 06 May 2020 05:22:28 -0400
X-MC-Unique: AJeojHx0OeioLnMVoERQNA-1
Received: from smtp.corp.redhat.com (int-mx08.intmail.prod.int.phx2.redhat.com
 [10.5.11.23])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 8BC4E107ACCD;
        Wed,  6 May 2020 09:22:27 +0000 (UTC)
Received: from virtlab701.virt.lab.eng.bos.redhat.com
 (virtlab701.virt.lab.eng.bos.redhat.com [10.19.152.228])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 434C8261A1;
        Wed,  6 May 2020 09:22:27 +0000 (UTC)
From: Paolo Bonzini <pbonzini@redhat.com>
To: linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Subject: [PATCH v2] KVM: x86: fix DR6 delivery for various cases of #DB
 injection
Date: Wed,  6 May 2020 05:22:26 -0400
Message-Id: <20200506092226.26394-1-pbonzini@redhat.com>
X-Scanned-By: MIMEDefang 2.84 on 10.5.11.23
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Go through kvm_queue_exception_p so that the payload is correctly delivered
through the exit qualification, and add a kvm_update_dr6 call to
kvm_deliver_exception_payload that is needed on AMD.

Reported-by: Peter Xu <peterx@redhat.com>
Signed-off-by: Paolo Bonzini <pbonzini@redhat.com>
---
 arch/x86/kvm/vmx/vmx.c | 6 ++----
 arch/x86/kvm/x86.c     | 6 +++---
 2 files changed, 5 insertions(+), 7 deletions(-)

```
#### [PATCH v3] KVM: x86: fix DR6 delivery for various cases of #DB injection
##### From: Paolo Bonzini <pbonzini@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Paolo Bonzini <pbonzini@redhat.com>
X-Patchwork-Id: 11530781
Return-Path: <SRS0=qN9b=6U=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 947E914C0
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed,  6 May 2020 09:24:05 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 7BEB120714
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed,  6 May 2020 09:24:05 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="JycxjTwA"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729050AbgEFJYE (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 6 May 2020 05:24:04 -0400
Received: from us-smtp-delivery-1.mimecast.com ([205.139.110.120]:24325 "EHLO
        us-smtp-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org
        with ESMTP id S1728559AbgEFJYE (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 6 May 2020 05:24:04 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1588757043;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc; bh=sZqM58Ec3WZKbAvwY/cBh3RDnWev4QH4nWVhzFDl5Zo=;
        b=JycxjTwAHGMj/nI3BBxYwICFt0smVhXZajPP0mlTQHx5+lKh/Hr7pEW396AnPURsnf3LyD
        AEtx4blXc4tGE1Kt4cYC7evSCLbupCbenUH8S8KYt0B51/6nwaU2bcXotsr1L4PZQzTXq2
        CX2ksXTnCiP3zEq4YC1euZFNNuwfmJU=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-434-r5NlPNRMPC6HpDHTJCbI2Q-1; Wed, 06 May 2020 05:24:01 -0400
X-MC-Unique: r5NlPNRMPC6HpDHTJCbI2Q-1
Received: from smtp.corp.redhat.com (int-mx04.intmail.prod.int.phx2.redhat.com
 [10.5.11.14])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 74A001800D4A;
        Wed,  6 May 2020 09:24:00 +0000 (UTC)
Received: from virtlab701.virt.lab.eng.bos.redhat.com
 (virtlab701.virt.lab.eng.bos.redhat.com [10.19.152.228])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 180365D9C5;
        Wed,  6 May 2020 09:24:00 +0000 (UTC)
From: Paolo Bonzini <pbonzini@redhat.com>
To: linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Subject: [PATCH v3] KVM: x86: fix DR6 delivery for various cases of #DB
 injection
Date: Wed,  6 May 2020 05:23:59 -0400
Message-Id: <20200506092359.26797-1-pbonzini@redhat.com>
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.14
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Go through kvm_queue_exception_p so that the payload is correctly delivered
through the exit qualification, and add a kvm_update_dr6 call to
kvm_deliver_exception_payload that is needed on AMD.

Reported-by: Peter Xu <peterx@redhat.com>
Signed-off-by: Paolo Bonzini <pbonzini@redhat.com>
---
 arch/x86/kvm/vmx/vmx.c | 8 ++------
 arch/x86/kvm/x86.c     | 6 +++---
 2 files changed, 5 insertions(+), 9 deletions(-)

```
#### [PATCH] [v4] KVM: X86: support APERF/MPERF registers
##### From: Li RongQing <lirongqing@baidu.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Li RongQing <lirongqing@baidu.com>
X-Patchwork-Id: 11530783
Return-Path: <SRS0=qN9b=6U=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 1F41514C0
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed,  6 May 2020 09:25:33 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 0C46D2075A
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed,  6 May 2020 09:25:33 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729054AbgEFJZa (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 6 May 2020 05:25:30 -0400
Received: from mx60.baidu.com ([61.135.168.60]:56333 "EHLO
        tc-sys-mailedm05.tc.baidu.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S1728712AbgEFJZ3 (ORCPT
        <rfc822;kvm@vger.kernel.org>); Wed, 6 May 2020 05:25:29 -0400
Received: from localhost (cp01-cos-dev01.cp01.baidu.com [10.92.119.46])
        by tc-sys-mailedm05.tc.baidu.com (Postfix) with ESMTP id 4AC571EBA00E;
        Wed,  6 May 2020 17:25:15 +0800 (CST)
From: Li RongQing <lirongqing@baidu.com>
To: linux-kernel@vger.kernel.org, kvm@vger.kernel.org, x86@kernel.org,
        hpa@zytor.com, bp@alien8.de, mingo@redhat.com, tglx@linutronix.de,
        jmattson@google.com, wanpengli@tencent.com, vkuznets@redhat.com,
        sean.j.christopherson@intel.com, pbonzini@redhat.com,
        xiaoyao.li@intel.com, wei.huang2@amd.com, lirongqing@baidu.com
Subject: [PATCH] [v4] KVM: X86: support APERF/MPERF registers
Date: Wed,  6 May 2020 17:25:15 +0800
Message-Id: <1588757115-19754-1-git-send-email-lirongqing@baidu.com>
X-Mailer: git-send-email 1.7.1
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Guest kernel reports a fixed cpu frequency in /proc/cpuinfo,
this is confused to user when turbo is enable, and aperf/mperf
can be used to show current cpu frequency after 7d5905dc14a
"(x86 / CPU: Always show current CPU frequency in /proc/cpuinfo)"
so guest should support aperf/mperf capability

This patch implements aperf/mperf by three mode: none, software
emulation, and pass-through

none: default mode, guest does not support aperf/mperf

software emulation: the period of aperf/mperf in guest mode are
accumulated as emulated value

pass-though: it is only suitable for KVM_HINTS_REALTIME, Because
that hint guarantees we have a 1:1 vCPU:CPU binding and guaranteed
no over-commit.

and a per-VM capability is added to configure aperfmperf mode

Signed-off-by: Li RongQing <lirongqing@baidu.com>
Signed-off-by: Chai Wen <chaiwen@baidu.com>
Signed-off-by: Jia Lina <jialina01@baidu.com>

diff v3:
fix interception of MSR_IA32_MPERF/APERF in svm

diff v2:
support aperfmperf pass though
move common codes to kvm_get_msr_common

diff v1:
1. support AMD, but not test
2. support per-vm capability to enable

 Documentation/virt/kvm/api.rst  | 10 ++++++++++
 arch/x86/include/asm/kvm_host.h | 11 +++++++++++
 arch/x86/kvm/cpuid.c            | 13 ++++++++++++-
 arch/x86/kvm/svm/svm.c          |  8 ++++++++
 arch/x86/kvm/vmx/vmx.c          |  6 ++++++
 arch/x86/kvm/x86.c              | 42 +++++++++++++++++++++++++++++++++++++++++
 arch/x86/kvm/x86.h              | 15 +++++++++++++++
 include/uapi/linux/kvm.h        |  1 +
 8 files changed, 105 insertions(+), 1 deletion(-)

```
#### [PATCH v3 1/1] vfio-ccw: Enable transparent CCW IPL from DASD
##### From: Jared Rossi <jrossi@linux.ibm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Jared Rossi <jrossi@linux.ibm.com>
X-Patchwork-Id: 11530091
Return-Path: <SRS0=qN9b=6U=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 2BD071392
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed,  6 May 2020 00:13:22 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 152C920752
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed,  6 May 2020 00:13:22 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729586AbgEFANT (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 5 May 2020 20:13:19 -0400
Received: from mx0a-001b2d01.pphosted.com ([148.163.156.1]:42182 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1728642AbgEFANR (ORCPT
        <rfc822;kvm@vger.kernel.org>); Tue, 5 May 2020 20:13:17 -0400
Received: from pps.filterd (m0187473.ppops.net [127.0.0.1])
        by mx0a-001b2d01.pphosted.com (8.16.0.42/8.16.0.42) with SMTP id
 04603NPp178229;
        Tue, 5 May 2020 20:13:16 -0400
Received: from pps.reinject (localhost [127.0.0.1])
        by mx0a-001b2d01.pphosted.com with ESMTP id 30s4gvfsgy-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Tue, 05 May 2020 20:13:16 -0400
Received: from m0187473.ppops.net (m0187473.ppops.net [127.0.0.1])
        by pps.reinject (8.16.0.36/8.16.0.36) with SMTP id 04603cUa178845;
        Tue, 5 May 2020 20:13:16 -0400
Received: from ppma04dal.us.ibm.com (7a.29.35a9.ip4.static.sl-reverse.com
 [169.53.41.122])
        by mx0a-001b2d01.pphosted.com with ESMTP id 30s4gvfsgp-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Tue, 05 May 2020 20:13:16 -0400
Received: from pps.filterd (ppma04dal.us.ibm.com [127.0.0.1])
        by ppma04dal.us.ibm.com (8.16.0.27/8.16.0.27) with SMTP id
 0460AKUr017832;
        Wed, 6 May 2020 00:13:15 GMT
Received: from b03cxnp07029.gho.boulder.ibm.com
 (b03cxnp07029.gho.boulder.ibm.com [9.17.130.16])
        by ppma04dal.us.ibm.com with ESMTP id 30s0g6v4es-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Wed, 06 May 2020 00:13:15 +0000
Received: from b03ledav004.gho.boulder.ibm.com
 (b03ledav004.gho.boulder.ibm.com [9.17.130.235])
        by b03cxnp07029.gho.boulder.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id 0460DD6F45154626
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Wed, 6 May 2020 00:13:13 GMT
Received: from b03ledav004.gho.boulder.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 68D3078064;
        Wed,  6 May 2020 00:13:13 +0000 (GMT)
Received: from b03ledav004.gho.boulder.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id A22CC7805E;
        Wed,  6 May 2020 00:13:12 +0000 (GMT)
Received: from localhost.localdomain.com (unknown [9.85.145.129])
        by b03ledav004.gho.boulder.ibm.com (Postfix) with ESMTP;
        Wed,  6 May 2020 00:13:12 +0000 (GMT)
From: Jared Rossi <jrossi@linux.ibm.com>
To: Eric Farman <farman@linux.ibm.com>,
        Cornelia Huck <cohuck@redhat.com>,
        Halil Pasic <pasic@linux.ibm.com>
Cc: linux-s390@vger.kernel.org, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org
Subject: [PATCH v3 1/1] vfio-ccw: Enable transparent CCW IPL from DASD
Date: Tue,  5 May 2020 20:15:44 -0400
Message-Id: <20200506001544.16213-2-jrossi@linux.ibm.com>
X-Mailer: git-send-email 2.21.1
In-Reply-To: <20200506001544.16213-1-jrossi@linux.ibm.com>
References: <20200506001544.16213-1-jrossi@linux.ibm.com>
MIME-Version: 1.0
X-TM-AS-GCONF: 00
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.138,18.0.676
 definitions=2020-05-05_11:2020-05-04,2020-05-05 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 adultscore=0
 lowpriorityscore=0 mlxlogscore=999 clxscore=1015 bulkscore=0 mlxscore=0
 priorityscore=1501 malwarescore=0 phishscore=0 spamscore=0 impostorscore=0
 suspectscore=0 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.12.0-2003020000 definitions=main-2005050182
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Remove the explicit prefetch check when using vfio-ccw devices.
This check does not trigger in practice as all Linux channel programs
are intended to use prefetch.

It is expected that all ORBs issued by Linux will request prefetch.
Although non-prefetching ORBs are not rejected, they will prefetch
nonetheless. A warning is issued up to once per 5 seconds when a
forced prefetch occurs.

A non-prefetch ORB does not necessarily result in an error, however
frequent encounters with non-prefetch ORBs indicate that channel
programs are being executed in a way that is inconsistent with what
the guest is requesting. While there is currently no known case of an
error caused by forced prefetch, it is possible in theory that forced
prefetch could result in an error if applied to a channel program that
is dependent on non-prefetch.

Signed-off-by: Jared Rossi <jrossi@linux.ibm.com>
---
 Documentation/s390/vfio-ccw.rst |  6 ++++++
 drivers/s390/cio/vfio_ccw_cp.c  | 19 ++++++++++++-------
 2 files changed, 18 insertions(+), 7 deletions(-)

```
#### [PATCH v4 1/1] vfio-ccw: Enable transparent CCW IPL from DASD
##### From: Jared Rossi <jrossi@linux.ibm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Jared Rossi <jrossi@linux.ibm.com>
X-Patchwork-Id: 11531903
Return-Path: <SRS0=qN9b=6U=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 003E115E6
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed,  6 May 2020 21:22:15 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id E05302075A
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed,  6 May 2020 21:22:14 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1730144AbgEFVWO (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 6 May 2020 17:22:14 -0400
Received: from mx0a-001b2d01.pphosted.com ([148.163.156.1]:14016 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1729925AbgEFVWN (ORCPT
        <rfc822;kvm@vger.kernel.org>); Wed, 6 May 2020 17:22:13 -0400
Received: from pps.filterd (m0098399.ppops.net [127.0.0.1])
        by mx0a-001b2d01.pphosted.com (8.16.0.42/8.16.0.42) with SMTP id
 046L2fQ9143886;
        Wed, 6 May 2020 17:22:12 -0400
Received: from pps.reinject (localhost [127.0.0.1])
        by mx0a-001b2d01.pphosted.com with ESMTP id 30u8srveff-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Wed, 06 May 2020 17:22:12 -0400
Received: from m0098399.ppops.net (m0098399.ppops.net [127.0.0.1])
        by pps.reinject (8.16.0.36/8.16.0.36) with SMTP id 046L2kZa144679;
        Wed, 6 May 2020 17:22:12 -0400
Received: from ppma04dal.us.ibm.com (7a.29.35a9.ip4.static.sl-reverse.com
 [169.53.41.122])
        by mx0a-001b2d01.pphosted.com with ESMTP id 30u8srveex-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Wed, 06 May 2020 17:22:12 -0400
Received: from pps.filterd (ppma04dal.us.ibm.com [127.0.0.1])
        by ppma04dal.us.ibm.com (8.16.0.27/8.16.0.27) with SMTP id
 046LKkBQ004196;
        Wed, 6 May 2020 21:22:11 GMT
Received: from b03cxnp08026.gho.boulder.ibm.com
 (b03cxnp08026.gho.boulder.ibm.com [9.17.130.18])
        by ppma04dal.us.ibm.com with ESMTP id 30s0g75hmb-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Wed, 06 May 2020 21:22:11 +0000
Received: from b03ledav005.gho.boulder.ibm.com
 (b03ledav005.gho.boulder.ibm.com [9.17.130.236])
        by b03cxnp08026.gho.boulder.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id 046LM9pi27132196
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Wed, 6 May 2020 21:22:09 GMT
Received: from b03ledav005.gho.boulder.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id A752EBE056;
        Wed,  6 May 2020 21:22:09 +0000 (GMT)
Received: from b03ledav005.gho.boulder.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id C4851BE051;
        Wed,  6 May 2020 21:22:08 +0000 (GMT)
Received: from localhost.localdomain.com (unknown [9.85.180.129])
        by b03ledav005.gho.boulder.ibm.com (Postfix) with ESMTP;
        Wed,  6 May 2020 21:22:08 +0000 (GMT)
From: Jared Rossi <jrossi@linux.ibm.com>
To: Eric Farman <farman@linux.ibm.com>,
        Cornelia Huck <cohuck@redhat.com>,
        Halil Pasic <pasic@linux.ibm.com>
Cc: linux-s390@vger.kernel.org, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org
Subject: [PATCH v4 1/1] vfio-ccw: Enable transparent CCW IPL from DASD
Date: Wed,  6 May 2020 17:24:40 -0400
Message-Id: <20200506212440.31323-2-jrossi@linux.ibm.com>
X-Mailer: git-send-email 2.21.1
In-Reply-To: <20200506212440.31323-1-jrossi@linux.ibm.com>
References: <20200506212440.31323-1-jrossi@linux.ibm.com>
MIME-Version: 1.0
X-TM-AS-GCONF: 00
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.216,18.0.676
 definitions=2020-05-06_09:2020-05-05,2020-05-06 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 priorityscore=1501
 bulkscore=0 spamscore=0 lowpriorityscore=0 clxscore=1015 mlxscore=0
 mlxlogscore=999 impostorscore=0 adultscore=0 suspectscore=0 phishscore=0
 malwarescore=0 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.12.0-2003020000 definitions=main-2005060170
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Remove the explicit prefetch check when using vfio-ccw devices.
This check does not trigger in practice as all Linux channel programs
are intended to use prefetch.

It is expected that all ORBs issued by Linux will request prefetch.
Although non-prefetching ORBs are not rejected, they will prefetch
nonetheless. A warning is issued up to once per 5 seconds when a
forced prefetch occurs.

A non-prefetch ORB does not necessarily result in an error, however
frequent encounters with non-prefetch ORBs indicate that channel
programs are being executed in a way that is inconsistent with what
the guest is requesting. While there is currently no known case of an
error caused by forced prefetch, it is possible in theory that forced
prefetch could result in an error if applied to a channel program that
is dependent on non-prefetch.

Signed-off-by: Jared Rossi <jrossi@linux.ibm.com>
---
 Documentation/s390/vfio-ccw.rst |  6 ++++++
 drivers/s390/cio/vfio_ccw_cp.c  | 19 ++++++++++++-------
 2 files changed, 18 insertions(+), 7 deletions(-)

```
#### [PATCH v1 01/17] exec: Introduce ram_block_discard_set_(unreliable|required)()
##### From: David Hildenbrand <david@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: David Hildenbrand <david@redhat.com>
X-Patchwork-Id: 11530891
Return-Path: <SRS0=qN9b=6U=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id C25D081
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed,  6 May 2020 09:50:10 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 9AF652070B
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed,  6 May 2020 09:50:10 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="PEybXLPz"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729051AbgEFJuJ (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 6 May 2020 05:50:09 -0400
Received: from us-smtp-delivery-1.mimecast.com ([207.211.31.120]:41292 "EHLO
        us-smtp-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org
        with ESMTP id S1726935AbgEFJuJ (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 6 May 2020 05:50:09 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1588758608;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding:
         in-reply-to:in-reply-to:references:references;
        bh=1b7WzEdOr0opnS44tYvGmSayhyE3oXt+X3RgB8uyQ/4=;
        b=PEybXLPzyCAXbc0VPHNSmX4nyPKA9AIDQDyvs+FYMXf8oLwjU3hmQ5nnxuzlHYhMfjGnUo
        oPIFlxXn12O2P5lQ7GvMxly7eJEVKGhNSfc0P0hcn0nOb3H5wnzB0cz6gTdNTTPdUz7lOu
        RPZ8MxhsWZN4BLOVyY67FFmvgxAw6UU=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-287-tQp4UaSBNF61XvzTMO_hOA-1; Wed, 06 May 2020 05:50:06 -0400
X-MC-Unique: tQp4UaSBNF61XvzTMO_hOA-1
Received: from smtp.corp.redhat.com (int-mx06.intmail.prod.int.phx2.redhat.com
 [10.5.11.16])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 99C2C835B44;
        Wed,  6 May 2020 09:50:05 +0000 (UTC)
Received: from t480s.redhat.com (ovpn-113-17.ams2.redhat.com [10.36.113.17])
        by smtp.corp.redhat.com (Postfix) with ESMTP id D68BA5C1D4;
        Wed,  6 May 2020 09:50:01 +0000 (UTC)
From: David Hildenbrand <david@redhat.com>
To: qemu-devel@nongnu.org
Cc: kvm@vger.kernel.org, qemu-s390x@nongnu.org,
        Richard Henderson <rth@twiddle.net>,
        Paolo Bonzini <pbonzini@redhat.com>,
        "Dr . David Alan Gilbert" <dgilbert@redhat.com>,
        Eduardo Habkost <ehabkost@redhat.com>,
        "Michael S . Tsirkin" <mst@redhat.com>,
        David Hildenbrand <david@redhat.com>
Subject: [PATCH v1 01/17] exec: Introduce
 ram_block_discard_set_(unreliable|required)()
Date: Wed,  6 May 2020 11:49:32 +0200
Message-Id: <20200506094948.76388-2-david@redhat.com>
In-Reply-To: <20200506094948.76388-1-david@redhat.com>
References: <20200506094948.76388-1-david@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.16
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

We want to replace qemu_balloon_inhibit() by something more generic.
Especially, we want to make sure that technologies that really rely on
RAM block discards to work reliably to run mutual exclusive with
technologies that break it.

E.g., vfio will usually pin all guest memory, turning the virtio-balloon
basically useless and make the VM consume more memory than reported via
the balloon. While the balloon is special already (=> no guarantees, same
behavior possible afer reboots and with huge pages), this will be
different, especially, with virtio-mem.

Let's implement a way such that we can make both types of technology run
mutually exclusive. We'll convert existing balloon inhibitors in successive
patches and add some new ones. Add the check to
qemu_balloon_is_inhibited() for now. We might want to make
virtio-balloon an acutal inhibitor in the future - however, that
requires more thought to not break existing setups.

Cc: "Michael S. Tsirkin" <mst@redhat.com>
Cc: Richard Henderson <rth@twiddle.net>
Cc: Paolo Bonzini <pbonzini@redhat.com>
Signed-off-by: David Hildenbrand <david@redhat.com>
---
 balloon.c             |  3 ++-
 exec.c                | 48 +++++++++++++++++++++++++++++++++++++++++++
 include/exec/memory.h | 41 ++++++++++++++++++++++++++++++++++++
 3 files changed, 91 insertions(+), 1 deletion(-)

```
