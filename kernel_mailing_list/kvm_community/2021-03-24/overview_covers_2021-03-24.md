

#### [RFC Part1 PATCH 00/13] Add AMD Secure Nested Paging (SEV-SNP) Guest
##### From: Brijesh Singh <brijesh.singh@amd.com>

```c
From patchwork Wed Mar 24 16:44:11 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Brijesh Singh <brijesh.singh@amd.com>
X-Patchwork-Id: 12161671
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-18.7 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_PATCH,
	MAILING_LIST_MULTI,MENTIONS_GIT_HOSTING,MSGID_FROM_MTA_HEADER,SPF_HELO_NONE,
	SPF_PASS,URIBL_BLOCKED,USER_AGENT_GIT autolearn=ham autolearn_force=no
	version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 5BC11C433C1
	for <kvm@archiver.kernel.org>; Wed, 24 Mar 2021 16:45:29 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 2B72361A0E
	for <kvm@archiver.kernel.org>; Wed, 24 Mar 2021 16:45:29 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S236585AbhCXQo4 (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Wed, 24 Mar 2021 12:44:56 -0400
Received: from mail-bn8nam12on2055.outbound.protection.outlook.com
 ([40.107.237.55]:61165
        "EHLO NAM12-BN8-obe.outbound.protection.outlook.com"
        rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org with ESMTP
        id S236503AbhCXQon (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 24 Mar 2021 12:44:43 -0400
ARC-Seal: i=1; a=rsa-sha256; s=arcselector9901; d=microsoft.com; cv=none;
 b=ENJbzcuqG8lgb5WwAAbtisWppmJPnIvV9PKxDDaYuDb5LBLlxjCvkNtv1nYZz43d0fgC3+DqJDBf0YnpvdPNxCi2b5+8xZQrjfhwKY5NczYeH6qHdIJUUIFOuZ13k8kqsLS4mduqBQ07ZK/g5105NFIg45wnjy883qBh+J+vR5a7xoAijmKRI653j00NJocxu8a7Q/YzfuexaRY1MaIV5PoLXhSRiL/V0ptlWp/vmFtZorWSCpYNE5Y2Ei25/Y4/WcmBcFsxyYwkhI43MchRZST20uX0v9e7b4ddVALuQ11UM3NzbhCarhosPv+bo2R+o32ZWzHEyYbPLWNRxGPD4A==
ARC-Message-Signature: i=1; a=rsa-sha256; c=relaxed/relaxed; d=microsoft.com;
 s=arcselector9901;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=LmOPv41Xu//5qztaF/8bpibaj+/vQJdXrN52m574vmg=;
 b=D0JrLCTvOF3UCvABbDaXuR/GlQaZRzM+UwqsjccV0ThDZtermmGutk5V0xqWgFpOf5Cfxos8iwj7wMlGTSmv2cVpKcwN940Yqirs9yJ7CUQXf2hKTNyADDeKDZp8a02S23gdfgRjioHN6Xfxy8GLS4kLC15gsVLGDpKUxTwsgrj0RUVT1FowT6u8/jdxYpC/kBuG36RHTG57p2vTXBFcG1ybNydzd5W7f/AirmCTPP7hGAEbVIS4mKcpzY2TSBKtwchiTfuweVhvUnsP3NX8xl5lYDG6hIMg1Cq/RvlSjIcGEQ4xahGzBYegWXN3XFLxpImxn+k4GH1WQ/yoPGAI5w==
ARC-Authentication-Results: i=1; mx.microsoft.com 1; spf=pass
 smtp.mailfrom=amd.com; dmarc=pass action=none header.from=amd.com; dkim=pass
 header.d=amd.com; arc=none
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=amd.com; s=selector1;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=LmOPv41Xu//5qztaF/8bpibaj+/vQJdXrN52m574vmg=;
 b=tlsBh9FhOrKvElFW0vgXwblGEID7Ef/bRxAVrIfeO3LdjAk+Gz2mcckXOBXz9JN801h1G13qjBZWPyPh6UDcPNJcGr3EuQhKlwTgcD5We2YEdb+VLrRqIqyzpO4WiVwNZKlixrd+DC4upkCGeeHiR6U0ZzCgY/u8rvEQOaBSI2Q=
Authentication-Results: vger.kernel.org; dkim=none (message not signed)
 header.d=none;vger.kernel.org; dmarc=none action=none header.from=amd.com;
Received: from SN6PR12MB2718.namprd12.prod.outlook.com (2603:10b6:805:6f::22)
 by SN1PR12MB2447.namprd12.prod.outlook.com (2603:10b6:802:27::22) with
 Microsoft SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.3955.18; Wed, 24 Mar
 2021 16:44:37 +0000
Received: from SN6PR12MB2718.namprd12.prod.outlook.com
 ([fe80::30fb:2d6c:a0bf:2f1d]) by SN6PR12MB2718.namprd12.prod.outlook.com
 ([fe80::30fb:2d6c:a0bf:2f1d%3]) with mapi id 15.20.3955.027; Wed, 24 Mar 2021
 16:44:37 +0000
From: Brijesh Singh <brijesh.singh@amd.com>
To: linux-kernel@vger.kernel.org, x86@kernel.org, kvm@vger.kernel.org
Cc: ak@linux.intel.com, Brijesh Singh <brijesh.singh@amd.com>,
        Thomas Gleixner <tglx@linutronix.de>,
        Ingo Molnar <mingo@redhat.com>, Borislav Petkov <bp@alien8.de>,
        Joerg Roedel <jroedel@suse.de>,
        "H. Peter Anvin" <hpa@zytor.com>, Tony Luck <tony.luck@intel.com>,
        Dave Hansen <dave.hansen@intel.com>,
        "Peter Zijlstra (Intel)" <peterz@infradead.org>,
        Paolo Bonzini <pbonzini@redhat.com>,
        Tom Lendacky <thomas.lendacky@amd.com>,
        David Rientjes <rientjes@google.com>,
        Sean Christopherson <seanjc@google.com>
Subject: [RFC Part1 PATCH 00/13] Add AMD Secure Nested Paging (SEV-SNP) Guest
 Support
Date: Wed, 24 Mar 2021 11:44:11 -0500
Message-Id: <20210324164424.28124-1-brijesh.singh@amd.com>
X-Mailer: git-send-email 2.17.1
X-Originating-IP: [165.204.77.1]
X-ClientProxiedBy: SA0PR11CA0010.namprd11.prod.outlook.com
 (2603:10b6:806:d3::15) To SN6PR12MB2718.namprd12.prod.outlook.com
 (2603:10b6:805:6f::22)
MIME-Version: 1.0
X-MS-Exchange-MessageSentRepresentingType: 1
Received: from sbrijesh-desktop.amd.com (165.204.77.1) by
 SA0PR11CA0010.namprd11.prod.outlook.com (2603:10b6:806:d3::15) with Microsoft
 SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.3977.24 via Frontend
 Transport; Wed, 24 Mar 2021 16:44:36 +0000
X-MS-PublicTrafficType: Email
X-MS-Office365-Filtering-HT: Tenant
X-MS-Office365-Filtering-Correlation-Id: cf56288d-8684-4ee8-1275-08d8eee41c63
X-MS-TrafficTypeDiagnostic: SN1PR12MB2447:
X-MS-Exchange-Transport-Forked: True
X-Microsoft-Antispam-PRVS: 
 <SN1PR12MB24478A3F7DD40216913784FCE5639@SN1PR12MB2447.namprd12.prod.outlook.com>
X-MS-Oob-TLC-OOBClassifiers: OLM:4125;
X-MS-Exchange-SenderADCheck: 1
X-Microsoft-Antispam: BCL:0;
X-Microsoft-Antispam-Message-Info: 
 gsz+Q82ToENxeb8+FLoSdHZBOFT+TtsQuktuaBwN1xqLp8fgll7tKTUnlH1BaQ1yEZoTiIOg6YDIN5v39zsTcPqRPkW3y40JAm6Pvz9lCKrDWc+8ebPxtkWwF06waNWxhtIK/m+ef2Mc+bDOZFZyBEsALjbdCrNGCO/L4fM5+foxKto4/J3HsHtDiTIgwFRldXNDuiXR1ULWdCLSa2szNyw1StwgunTicB4GPZuYfKx56P1CzUlp5PeFthTOWqMYgKstB6IVHygVBmvpF/YiFskg0tiKUpwGG+1PG4jVaSyikVA6oVIA3qzXu6eirLyckWKEkU42Erh7t/awlGwBabu1jlyRsBOupu3y2wAofGF1SrwNk5r4GQnXczeL91cNhhrks/cb03xgnGUcqlAR4JRCoOx/sM9/eN37QaiZdXsw2NvJJjV9CLMoe6dpFjibmBkxW51lvWIs+f/zE1nGaOYnTm7pDkrbPFOtabW5t7Bnb/aqxCf/jv2tLbL2IoiqcdLv1tQiMVxkd3azeNq/A+kVCCK0bsMOjIA82X2+GoSs5qlAYXvO9fbbvgr4OF1y/TZ4cEQzsy2tmLG2GZjMNJn+qO5HcXTsp0jEm7kvcdnrA4eIBU5bI+UzDbkhljzmP4wmAuj051R2Ct/BouxFXWnGrDV+Th26W4uTfDFU4UCTrDfcpEPVAqq2tZ3l9HAdIvSQ2oWCZm596PEm/9IFPXxaUTeAzFi8KIi8m4dMapY19nbKMpsdmxToQV8/jjSp
X-Forefront-Antispam-Report: 
 CIP:255.255.255.255;CTRY:;LANG:en;SCL:1;SRV:;IPV:NLI;SFV:NSPM;H:SN6PR12MB2718.namprd12.prod.outlook.com;PTR:;CAT:NONE;SFS:(4636009)(39860400002)(376002)(346002)(396003)(136003)(366004)(16526019)(38100700001)(5660300002)(26005)(44832011)(36756003)(1076003)(54906003)(8676002)(316002)(83380400001)(8936002)(4326008)(956004)(2906002)(186003)(6486002)(86362001)(7416002)(2616005)(966005)(66946007)(7696005)(478600001)(66556008)(66476007)(52116002)(6666004);DIR:OUT;SFP:1101;
X-MS-Exchange-AntiSpam-MessageData: =?utf-8?q?2bcafRUyJzzM+RcOFjrUp9ociEARec?=
	=?utf-8?q?1VKVup5V47YKugIwViHbomRnzVZ83UjvlR4ktUXUxkgrWBlqOkrlA+hDhqW6ds32I?=
	=?utf-8?q?2kXp+HS0xUHlC/C3bgmF8/b4TMP0u817PHYiHK9dzINikfdfCeGWujqzzpIX5gRk/?=
	=?utf-8?q?jq66/yHDebdkp2u1AK6f6GNNRgRs7iMF/q+28fsE2mXlg0L2S1xCgO2jd5OPx+2y/?=
	=?utf-8?q?a6WX7qHfmE7tB+UNo/1C1UqoBJsbEKLavndaitV2Fm5Z7uIphTi81f3D26RwQy4ee?=
	=?utf-8?q?bhu0SWoS8WQvMKcxl/oRJzzBu4nH5inKkFhdkif/42C4hotVkB1RnDFLRFdz4CTP+?=
	=?utf-8?q?iSF0dh2kXdLHyMwI/Qeq8a3yf5PZQpQUOTXoczYoLInpHQmT+IMXevuF7LjQl0mph?=
	=?utf-8?q?JMcSe3NYVk577ErQSsPjBZzMwXkgjVvON6NFosFvpoAYGJcYvcI1bvt+dNpembgLe?=
	=?utf-8?q?6o3ZivhCI/JkrXNat+73eqEwYAkL/94tcyd+icSMjieFzhjpYj9nGMVJt9JhuLTiV?=
	=?utf-8?q?uRhRyzFwC9EkH8swJke0hJuaTfX2VWWOw36h7N9DPw8UbEHYh1t3CmyGnpPEOg4wG?=
	=?utf-8?q?Q1aI6RpO8a5MBssjSALhtp8Gk3jVr3pVjmmsXfKrsx+3pILtfikV7WKgt1u0LMuyW?=
	=?utf-8?q?sEnDJWTMVoP3stdJTjw9erFQ5y+MGQ/VYiosXjecpEQDPh4FvzYIHbFVoWt2ug308?=
	=?utf-8?q?u1PAPMNFFdiu7eWsMzkmPt85RZkv/R24Cr1QhJterc1GYtvVITp+GHwRN3BlKpCQ8?=
	=?utf-8?q?GLDBKbbiiFFwH3ohLk/euks51u5Ijwd4VHnAFTkTURPfc7oV+NMhrnEBkUxXPFqlo?=
	=?utf-8?q?24NfrLY2JyanaBtN8pXhMwzhRnjyIMzaodQ8adzV+AP9hyk5zVxs1qBMarBZn3OOA?=
	=?utf-8?q?fZ+pNijUoikSbDw3Kz6ii9aOdmzwHhcLrJRtEl0V3CjcgTQA/pxRFVZOZs6Tdd7uB?=
	=?utf-8?q?6LxZf1KFV47gEazQGlicmEETAuMVyXT3rtmJC/NkW/Mcr6nR8gDRnXanomjZ9DpV3?=
	=?utf-8?q?R3pmYzvwIhwkzEQlmp3SXnDQQutL3BkhPxJ4p1TTi453qeR4lGIjySX1KQ46mw/aP?=
	=?utf-8?q?23hnFAaVrPf0Wl5m79j58PMakNmOrt6oGt5qQiLz77hcazAl0rCxx37pGGSav5rqY?=
	=?utf-8?q?EHflHG8yGWQZJxxsBzrYJarzOOyb7Amac+QjiU5lipV4OLDLlDE3lZgt5rgoKv48A?=
	=?utf-8?q?ynNEAvSo4ksuFqjZI6NZoDhnuQ93xFXDwYZrb3T6AEbWv2hEvxS/QtqBhEbgUTwRP?=
	=?utf-8?q?Ws9ILzhqpdPqF9?=
X-OriginatorOrg: amd.com
X-MS-Exchange-CrossTenant-Network-Message-Id: 
 cf56288d-8684-4ee8-1275-08d8eee41c63
X-MS-Exchange-CrossTenant-AuthSource: SN6PR12MB2718.namprd12.prod.outlook.com
X-MS-Exchange-CrossTenant-AuthAs: Internal
X-MS-Exchange-CrossTenant-OriginalArrivalTime: 24 Mar 2021 16:44:37.7389
 (UTC)
X-MS-Exchange-CrossTenant-FromEntityHeader: Hosted
X-MS-Exchange-CrossTenant-Id: 3dd8961f-e488-4e60-8e11-a82d994e183d
X-MS-Exchange-CrossTenant-MailboxType: HOSTED
X-MS-Exchange-CrossTenant-UserPrincipalName: 
 09bEbZtHhtkVMtQIG9hzFD96S7wSJgwTjL/WJ1+eF+hkkcW8h8jyecKby/S3D1MXnPP+geZu0jdLVvqZMvHo1g==
X-MS-Exchange-Transport-CrossTenantHeadersStamped: SN1PR12MB2447
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This part of Secure Encrypted Paging (SEV-SNP) series focuses on the changes
required in a guest OS for SEV-SNP support.

SEV-SNP builds upon existing SEV and SEV-ES functionality while adding
new hardware-based memory protections. SEV-SNP adds strong memory integrity
protection to help prevent malicious hypervisor-based attacks like data
replay, memory re-mapping and more in order to create an isolated memory
encryption environment.
 
This series provides the basic building blocks to support booting the SEV-SNP
VMs, it does not cover all the security enhancement introduced by the SEV-SNP
such as interrupt protection.

Many of the integrity guarantees of SEV-SNP are enforced through a new
structure called the Reverse Map Table (RMP). Adding a new page to SEV-SNP
VM requires a 2-step process. First, the hypervisor assigns a page to the
guest using the new RMPUPDATE instruction. This transitions the page to
guest-invalid. Second, the guest validates the page using the new PVALIDATE
instruction. The SEV-SNP VMs can use the new "Page State Change Request NAE"
defined in the GHCB specification to ask hypervisor to add or remove page
from the RMP table.
 
Each page assigned to the SEV-SNP VM can either be validated or unvalidated,
as indicated by the Validated flag in the page's RMP entry. There are two
approaches that can be taken for the page validation: Pre-validation and
Lazy Validation.
  
Under pre-validation, the pages are validated prior to first use. And under
lazy validation, pages are validated when first accessed. An access to a
unvalidated page results in a #VC exception, at which time the exception
handler may validate the page. Lazy validation requires careful tracking of
the validated pages to avoid validating the same GPA more than once. The
recently introduced "Unaccepted" memory type can be used to communicate the
unvalidated memory ranges to the Guest OS.

At this time we only sypport the pre-validation, the OVMF guest BIOS
validates the entire RAM before the control is handed over to the guest kernel.
The early_set_memory_{encrypt,decrypt} and set_memory_{encrypt,decrypt} are
enlightened to perform the page validation or invalidation while setting or
clearing the encryption attribute from the page table.

This series does not provide support for the following SEV-SNP features yet:

* CPUID filtering
* Driver to query attestation report
* AP bring up using the new SEV-SNP NAE
* Lazy validation
* Interrupt security

The series is based on kvm/master commit:
  87aa9ec939ec KVM: x86/mmu: Fix TDP MMU zap collapsible SPTEs

The complete source is available at
 https://github.com/AMDESE/linux/tree/sev-snp-part-1-rfc1

Cc: Thomas Gleixner <tglx@linutronix.de>
Cc: Ingo Molnar <mingo@redhat.com>
Cc: Borislav Petkov <bp@alien8.de>
Cc: Joerg Roedel <jroedel@suse.de>
Cc: "H. Peter Anvin" <hpa@zytor.com>
Cc: Tony Luck <tony.luck@intel.com>
Cc: Dave Hansen <dave.hansen@intel.com>
Cc: "Peter Zijlstra (Intel)" <peterz@infradead.org>
Cc: Paolo Bonzini <pbonzini@redhat.com>
Cc: Tom Lendacky <thomas.lendacky@amd.com>
Cc: David Rientjes <rientjes@google.com>
Cc: Sean Christopherson <seanjc@google.com>
Cc: x86@kernel.org
Cc: kvm@vger.kernel.org

Additional resources
---------------------
SEV-SNP whitepaper
https://www.amd.com/system/files/TechDocs/SEV-SNP-strengthening-vm-isolation-with-integrity-protection-and-more.pdf
 
APM 2: https://www.amd.com/system/files/TechDocs/24593.pdf
(section 15.36)

GHCB spec v2:
  The draft specification is posted on AMD-SEV-SNP mailing list:
   https://lists.suse.com/mailman/private/amd-sev-snp/

  Copy of draft spec is also available at 
  https://github.com/AMDESE/AMDSEV/blob/sev-snp-devel/docs/56421-Guest_Hypervisor_Communication_Block_Standardization.pdf

GHCB spec v1:
SEV-SNP firmware specification:
 https://developer.amd.com/sev/

Brijesh Singh (13):
  x86/cpufeatures: Add SEV-SNP CPU feature
  x86/mm: add sev_snp_active() helper
  x86: add a helper routine for the PVALIDATE instruction
  x86/sev-snp: define page state change VMGEXIT structure
  X86/sev-es: move few helper functions in common file
  x86/compressed: rescinds and validate the memory used for the GHCB
  x86/compressed: register GHCB memory when SNP is active
  x86/sev-es: register GHCB memory when SEV-SNP is active
  x86/kernel: add support to validate memory in early enc attribute
    change
  X86: kernel: make the bss.decrypted section shared in RMP table
  x86/kernel: validate rom memory before accessing when SEV-SNP is
    active
  x86/sev-es: make GHCB get and put helper accessible outside
  x86/kernel: add support to validate memory when changing C-bit

 arch/x86/boot/compressed/Makefile       |   1 +
 arch/x86/boot/compressed/ident_map_64.c |  18 ++
 arch/x86/boot/compressed/sev-common.c   |  32 +++
 arch/x86/boot/compressed/sev-es.c       |  26 +--
 arch/x86/boot/compressed/sev-snp.c      | 141 +++++++++++++
 arch/x86/boot/compressed/sev-snp.h      |  25 +++
 arch/x86/include/asm/cpufeatures.h      |   1 +
 arch/x86/include/asm/mem_encrypt.h      |   2 +
 arch/x86/include/asm/msr-index.h        |   2 +
 arch/x86/include/asm/sev-es.h           |  11 +
 arch/x86/include/asm/sev-snp.h          | 121 +++++++++++
 arch/x86/include/uapi/asm/svm.h         |   1 +
 arch/x86/kernel/Makefile                |   3 +
 arch/x86/kernel/cpu/amd.c               |   3 +-
 arch/x86/kernel/cpu/scattered.c         |   1 +
 arch/x86/kernel/head64.c                |  14 ++
 arch/x86/kernel/probe_roms.c            |  15 ++
 arch/x86/kernel/sev-common-shared.c     |  31 +++
 arch/x86/kernel/sev-es-shared.c         |  21 +-
 arch/x86/kernel/sev-es.c                |  32 ++-
 arch/x86/kernel/sev-snp.c               | 269 ++++++++++++++++++++++++
 arch/x86/mm/mem_encrypt.c               |  49 ++++-
 arch/x86/mm/pat/set_memory.c            |  19 ++
 23 files changed, 792 insertions(+), 46 deletions(-)
 create mode 100644 arch/x86/boot/compressed/sev-common.c
 create mode 100644 arch/x86/boot/compressed/sev-snp.c
 create mode 100644 arch/x86/boot/compressed/sev-snp.h
 create mode 100644 arch/x86/include/asm/sev-snp.h
 create mode 100644 arch/x86/kernel/sev-common-shared.c
 create mode 100644 arch/x86/kernel/sev-snp.c
```
#### [RFC Part2 PATCH 00/30] Add AMD Secure Nested Paging (SEV-SNP)
##### From: Brijesh Singh <brijesh.singh@amd.com>

```c
From patchwork Wed Mar 24 17:04:06 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Brijesh Singh <brijesh.singh@amd.com>
X-Patchwork-Id: 12161801
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-18.7 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_PATCH,
	MAILING_LIST_MULTI,MENTIONS_GIT_HOSTING,MSGID_FROM_MTA_HEADER,SPF_HELO_NONE,
	SPF_PASS,URIBL_BLOCKED,USER_AGENT_GIT autolearn=unavailable
	autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 3402EC433E1
	for <kvm@archiver.kernel.org>; Wed, 24 Mar 2021 17:05:55 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id DB02D61A14
	for <kvm@archiver.kernel.org>; Wed, 24 Mar 2021 17:05:54 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S237023AbhCXRFU (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Wed, 24 Mar 2021 13:05:20 -0400
Received: from mail-bn8nam11on2078.outbound.protection.outlook.com
 ([40.107.236.78]:50401
        "EHLO NAM11-BN8-obe.outbound.protection.outlook.com"
        rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org with ESMTP
        id S236851AbhCXREx (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 24 Mar 2021 13:04:53 -0400
ARC-Seal: i=1; a=rsa-sha256; s=arcselector9901; d=microsoft.com; cv=none;
 b=ZZvBDWexa5v1FU31308h2/zr4IFm86O3LJEqP8RBSlXFFMLUnrGh+afGguTsD7xsDYtykybN0R1HqLKkxhgwr4U1fTx/ByND+zxDeG3PDWW8dUetynpmpiICV9bDjlSJFRZbKGpVYlF3LuOaBwOvUH73Yubupm/Pnoat3UyzCfk6W/2dC3MvpfRE9koXqciBhoXyxeMd7y93h5xA/JBb0w78jgcwOAZ5r7aAcNU1gBAoZt7UffhDpETXRjHmKhI2BT+MXdLoYCVuqKef0RCe/xv2NfRG0/mzB9Pk6l5WcB/rUoYtq1dN7GCv7rri0j3wXZoIDYvsRMvf9jRoxQPgGg==
ARC-Message-Signature: i=1; a=rsa-sha256; c=relaxed/relaxed; d=microsoft.com;
 s=arcselector9901;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=xY4mybB65Bwr0RRpP4krujH7j0IBZK10R+a5m3zU3GI=;
 b=ROg2W7ebSLh18QpHv6RHGPCd7I39e363e75Iqbis58felpfkK3OxT+iXP8cOoYmzvKS6GhHhBgpeFM12y1ElIy/wESHd4aTNw8FcV5BAeik46+KdNgxWDL2nhSDkCg5VYHs3n8nG/O+hJEYloVoOwLZyG8JAgGG5nY4eVtKvyKwqIoYiCV+FeLVz2FuskhnZvRNzhza1PNJdeRKej1flGy5mNifaFUNDQFTR0Oy7SdIu9qiWzYMHpXSnKyZiTt8usxcZzCliD7oTBTw/+jy6eOOVVWnemrCmfSqzAOppa39/ncRNdwM5wS6SgHX5iW/VzF2w01MB6tnztPQJKMmiTA==
ARC-Authentication-Results: i=1; mx.microsoft.com 1; spf=pass
 smtp.mailfrom=amd.com; dmarc=pass action=none header.from=amd.com; dkim=pass
 header.d=amd.com; arc=none
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=amd.com; s=selector1;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=xY4mybB65Bwr0RRpP4krujH7j0IBZK10R+a5m3zU3GI=;
 b=NlVgVRfPfxbKUyu9e1CCRtSwhtqVhR6bHUQdZNKoModmH1YYHdovZ12/FRz8F0uZSBlmO8c1DCUbWc//hfDqKREYfTEVjSFcIokDYTXHUvHzlKYkHTIBEtPIppKTfPJSyzkWcGUHpWrEPx12WIqXJgQq7mLbXeUzjsiFj0x50xw=
Authentication-Results: vger.kernel.org; dkim=none (message not signed)
 header.d=none;vger.kernel.org; dmarc=none action=none header.from=amd.com;
Received: from SN6PR12MB2718.namprd12.prod.outlook.com (2603:10b6:805:6f::22)
 by SA0PR12MB4557.namprd12.prod.outlook.com (2603:10b6:806:9d::10) with
 Microsoft SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.3977.24; Wed, 24 Mar
 2021 17:04:51 +0000
Received: from SN6PR12MB2718.namprd12.prod.outlook.com
 ([fe80::30fb:2d6c:a0bf:2f1d]) by SN6PR12MB2718.namprd12.prod.outlook.com
 ([fe80::30fb:2d6c:a0bf:2f1d%3]) with mapi id 15.20.3955.027; Wed, 24 Mar 2021
 17:04:51 +0000
From: Brijesh Singh <brijesh.singh@amd.com>
To: linux-kernel@vger.kernel.org, x86@kernel.org, kvm@vger.kernel.org,
        linux-crypto@vger.kernel.org
Cc: ak@linux.intel.com, herbert@gondor.apana.org.au,
        Brijesh Singh <brijesh.singh@amd.com>,
        Thomas Gleixner <tglx@linutronix.de>,
        Ingo Molnar <mingo@redhat.com>, Borislav Petkov <bp@alien8.de>,
        Joerg Roedel <jroedel@suse.de>,
        "H. Peter Anvin" <hpa@zytor.com>, Tony Luck <tony.luck@intel.com>,
        Dave Hansen <dave.hansen@intel.com>,
        "Peter Zijlstra (Intel)" <peterz@infradead.org>,
        Paolo Bonzini <pbonzini@redhat.com>,
        Tom Lendacky <thomas.lendacky@amd.com>,
        David Rientjes <rientjes@google.com>,
        Sean Christopherson <seanjc@google.com>
Subject: [RFC Part2 PATCH 00/30] Add AMD Secure Nested Paging (SEV-SNP)
 Hypervisor Support
Date: Wed, 24 Mar 2021 12:04:06 -0500
Message-Id: <20210324170436.31843-1-brijesh.singh@amd.com>
X-Mailer: git-send-email 2.17.1
X-Originating-IP: [165.204.77.1]
X-ClientProxiedBy: SA0PR11CA0210.namprd11.prod.outlook.com
 (2603:10b6:806:1bc::35) To SN6PR12MB2718.namprd12.prod.outlook.com
 (2603:10b6:805:6f::22)
MIME-Version: 1.0
X-MS-Exchange-MessageSentRepresentingType: 1
Received: from sbrijesh-desktop.amd.com (165.204.77.1) by
 SA0PR11CA0210.namprd11.prod.outlook.com (2603:10b6:806:1bc::35) with
 Microsoft SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.3977.25 via Frontend
 Transport; Wed, 24 Mar 2021 17:04:50 +0000
X-MS-PublicTrafficType: Email
X-MS-Office365-Filtering-HT: Tenant
X-MS-Office365-Filtering-Correlation-Id: 7f2a4352-e107-44e8-86e6-08d8eee6eff0
X-MS-TrafficTypeDiagnostic: SA0PR12MB4557:
X-MS-Exchange-Transport-Forked: True
X-Microsoft-Antispam-PRVS: 
 <SA0PR12MB455728ADB70F9C869342AAA9E5639@SA0PR12MB4557.namprd12.prod.outlook.com>
X-MS-Oob-TLC-OOBClassifiers: OLM:2276;
X-MS-Exchange-SenderADCheck: 1
X-Microsoft-Antispam: BCL:0;
X-Microsoft-Antispam-Message-Info: 
 /D2zOBnvASUuAL8Fyu4j1MapxBrSAUmDsQDX/az7qPtt9EhWOAJQdHWopriOWQZ4caltD5k8OJR44MrP90Sqwr0BMppqFY306qKyNdhIv1lCOTKZqwKJFmCrwVp+fqLHotf00CHR7gzUOY+/aJgwZYcoMx8+u+TZ3kSsMk43GJIqWDzuLkom3AcbP3N2+LcvcglgeNIhNfDlu1WcSM93tJyUAnn3HPsuVKxMWOh4Rdngf0QjiprXmIx/E4/V0bhHvd/p9BEO33vKkUVPy0UZCySgILnr6cZMcs4+IML7Tqt+nFtKGIW2mzvllu+pffA2m2u/+fairrRnmEKvjGWEFiKuwoTwj3VrzsTecpmv0kXywdzRnh7okyFVUDt6+8leX80GxftHJto59WmSuNU62vUetR/6rbt8c9GrtA4uqPbPdUBiSNb/5NqkEMrZDpe7T1vY+KNwmLdxLJAL9XiBaFcDa1k6uXaUYlEljG+9RYaJWGxK26jzQyqsFE31GDrLUpcGFz9ZBRwBXNuHFnXfBhp+MQHljM20JELd8qnO+tq/i05qAB7XcPvWkHATqhuwU1J8/xwIAsVdboKXVc7o+UVHfQBetZ4llMjPh59JxiHHbVYtwnLpvfOw9zcQojjJl42hv0ucxCLA5uf3K2O6uHlNp3FnhfRk2eb+hG3C2Zp8KKt/zN5H+nMe+Boze7eaiFkNBz/pzKLk+aAP7V/W04Nw0r2MbdRMml5GwLblmzjDKQBNhLz+Keays7AmuBmTKByjwMENIt6FVxPOlEjzig==
X-Forefront-Antispam-Report: 
 CIP:255.255.255.255;CTRY:;LANG:en;SCL:1;SRV:;IPV:NLI;SFV:NSPM;H:SN6PR12MB2718.namprd12.prod.outlook.com;PTR:;CAT:NONE;SFS:(4636009)(366004)(376002)(396003)(346002)(136003)(39860400002)(86362001)(54906003)(186003)(44832011)(6666004)(4326008)(38100700001)(26005)(316002)(66476007)(8676002)(16526019)(1076003)(2616005)(83380400001)(5660300002)(6486002)(956004)(52116002)(8936002)(478600001)(7416002)(7696005)(66556008)(36756003)(966005)(66946007)(2906002)(6606295002);DIR:OUT;SFP:1101;
X-MS-Exchange-AntiSpam-MessageData: 
 8e71MTPzgYzIV2x7gBxkCPPPf8XHH9Zz5bPNL80hCJ5Ei9kA1nI0vg2zk+s3WUqCtBCUWTQpg7mQnoKee5JUs3uxCaa7mX1c0z9fC2DdUDb4uMVoGM4KQwdvbsKkux67Apu6o3oex5e+Muov6l/YDy2Nr2DXNTxH9ijTcKIavvTn803pTb4OnqZowLdX3fV/hyKhDm7mXRPi4aq2YKqVDUj7lJmWW02wJhFJqJC04qKhBNbR3ZlZ4RZgcPdMpEhCSOepFWt+CzVWOi9uRe01QNgpuVFws3frV1bRXnusV4u71HPbHGZnCZKp68sQcIAAhR10FQymSHAOTkS/C9YNUN+lGMcOMPbV5nNzDQDhUZ1eG60zUoE0a4e2hU2RNveKm7HYrHZB+Ka403o2nDddbLiGL7NXGemDt+Orce1T2rJ3vS7O43PQzdN9siGFRBIzE4PILVMrc6oz4hnaXFDy3j54yqMG2aZyFipMxSfpO+RqPsBTX5l2W9fNUXLnsnuNIv2H00/PXuMrBjkUBu63uki8aaNYlAYjcpEHYgeu/O/ybIO7Na2ySRxH+jw8Wy45o/T8OMG6/3ej331R4HvZXzMTkttVyKY1BVNbf2sCI+YMJqJ1ou1sfDlHWntNu5ZHhI7TOCDI/9omvyFlsbhU/UqrpuKsvUoJgmGsNeNpx+m+RM+IuH3f2WbYne5gNLzbi1iXKXaQML3nvHK2gpYfYY4CeNvFDvVB91rDNQZY+C8WwLyfh8S+KELSWbTxtb5CwH4hf5e7U7uwFrY8h898EqzHJXQvrS0cRpL8Hn6cltOudoLtkjynN5AAyJk1KOus10EaWHGITFDjVcGdS43xoFjfxtVC9NlRNy684Ek6wt+iAlJbBw0KPRooIJ29/29+RXgJFUn4ljmO8/GrbjHDTF3ki93uk1o2Ln5D12DOyocguy7imPcora0Rj/JamH7bJn3Gd1Jt1EMz0abbniabM1+zv3PTkw/1AUjwRvMwikVkrcv42OYvreWxIGsmz7UOCfqJrZSJ1U4w+GZfbl41jUqptnBZIncr9o+tcaJeHNaJWu4gfpUPK512M96g9rcxL2G1O8Y3v/5jxBNwevkdO/sn2quL037pK7JslkbGGzmGg+e2CjImgY5CKE30Ahc3Z/wQx+UNaKfBXO690VOU0nPytB92HJfPXXQ9ASUxvwvIeF84Hr60OJRSVuLZYyX7Z9WqJErSIQvkXJamZ62QX/jrp9Zl6pmDVHlC5rlOMJeWmynGvwKnwCWQ8ZrTHbt+69PS4C6WjvaDk0u1qpnnY0vOxfC3lXY+JcjCIF1BWl8XkIgJJdtdV5S09PJi2A3D
X-OriginatorOrg: amd.com
X-MS-Exchange-CrossTenant-Network-Message-Id: 
 7f2a4352-e107-44e8-86e6-08d8eee6eff0
X-MS-Exchange-CrossTenant-AuthSource: SN6PR12MB2718.namprd12.prod.outlook.com
X-MS-Exchange-CrossTenant-AuthAs: Internal
X-MS-Exchange-CrossTenant-OriginalArrivalTime: 24 Mar 2021 17:04:50.9561
 (UTC)
X-MS-Exchange-CrossTenant-FromEntityHeader: Hosted
X-MS-Exchange-CrossTenant-Id: 3dd8961f-e488-4e60-8e11-a82d994e183d
X-MS-Exchange-CrossTenant-MailboxType: HOSTED
X-MS-Exchange-CrossTenant-UserPrincipalName: 
 sJxiLDRGmqu+c+vG2H0NT6sBWU90ruqFajMn7XPm72JWhpP7c742NZcSW+yuj+hep5jKd+Mfo5JkCOEhNw2jOQ==
X-MS-Exchange-Transport-CrossTenantHeadersStamped: SA0PR12MB4557
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This part of the Secure Encrypted Paging (SEV-SNP) series focuses on the
changes required in a host OS for SEV-SNP support. The series builds upon
SEV-SNP Part-1 https://marc.info/?l=kvm&m=161660430125343&w=2 .

This series provides the basic building blocks to support booting the SEV-SNP
VMs, it does not cover all the security enhancement introduced by the SEV-SNP
such as interrupt protection.

The CCP driver is enhanced to provide new APIs that use the SEV-SNP
specific commands defined in the SEV-SNP firmware specification. The KVM
driver uses those APIs to create and managed the SEV-SNP guests.

The GHCB specification version 2 introduces new set of NAE's that is
used by the SEV-SNP guest to communicate with the hypervisor. The series
provides support to handle the following new NAE events:
- Register GHCB GPA
- Page State Change Request

The RMP check is enforced as soon as SEV-SNP is enabled. Not every memory
access requires an RMP check. In particular, the read accesses from the
hypervisor do not require RMP checks because the data confidentiality is
already protected via memory encryption. When hardware encounters an RMP
checks failure, it raises a page-fault exception. If RMP check failure
is due to the page-size mismatch, then split the large page to resolve
the fault. See patch 4 and 7 for further details.

The series does not provide support for the following SEV-SNP specific
NAE's yet:

* Query Attestation 
* AP bring up
* Interrupt security

The series is based on kvm/master commit:
  87aa9ec939ec KVM: x86/mmu: Fix TDP MMU zap collapsible SPTEs

The complete source is available at
https://github.com/AMDESE/linux/tree/sev-snp-part-2-rfc1

Cc: Thomas Gleixner <tglx@linutronix.de>
Cc: Ingo Molnar <mingo@redhat.com>
Cc: Borislav Petkov <bp@alien8.de>
Cc: Joerg Roedel <jroedel@suse.de>
Cc: "H. Peter Anvin" <hpa@zytor.com>
Cc: Tony Luck <tony.luck@intel.com>
Cc: Dave Hansen <dave.hansen@intel.com>
Cc: "Peter Zijlstra (Intel)" <peterz@infradead.org>
Cc: Paolo Bonzini <pbonzini@redhat.com>
Cc: Tom Lendacky <thomas.lendacky@amd.com>
Cc: David Rientjes <rientjes@google.com>
Cc: Sean Christopherson <seanjc@google.com>
Cc: x86@kernel.org
Cc: kvm@vger.kernel.org

Additional resources
---------------------
SEV-SNP whitepaper
https://www.amd.com/system/files/TechDocs/SEV-SNP-strengthening-vm-isolation-with-integrity-protection-and-more.pdf
 
APM 2: https://www.amd.com/system/files/TechDocs/24593.pdf
(section 15.36)

GHCB spec v2:
  The draft specification is posted on AMD-SEV-SNP mailing list:
   https://lists.suse.com/mailman/private/amd-sev-snp/

  Copy of draft spec is also available at 
  https://github.com/AMDESE/AMDSEV/blob/sev-snp-devel/docs/56421-Guest_Hypervisor_Communication_Block_Standardization.pdf

GHCB spec v1:
SEV-SNP firmware specification:
 https://developer.amd.com/sev/

Brijesh Singh (30):
  x86: Add the host SEV-SNP initialization support
  x86/sev-snp: add RMP entry lookup helpers
  x86: add helper functions for RMPUPDATE and PSMASH instruction
  x86/mm: split the physmap when adding the page in RMP table
  x86: define RMP violation #PF error code
  x86/fault: dump the RMP entry on #PF
  mm: add support to split the large THP based on RMP violation
  crypto:ccp: define the SEV-SNP commands
  crypto: ccp: Add support to initialize the AMD-SP for SEV-SNP
  crypto: ccp: shutdown SNP firmware on kexec
  crypto:ccp: provide APIs to issue SEV-SNP commands
  crypto ccp: handle the legacy SEV command when SNP is enabled
  KVM: SVM: add initial SEV-SNP support
  KVM: SVM: make AVIC backing, VMSA and VMCB memory allocation SNP safe
  KVM: SVM: define new SEV_FEATURES field in the VMCB Save State Area
  KVM: SVM: add KVM_SNP_INIT command
  KVM: SVM: add KVM_SEV_SNP_LAUNCH_START command
  KVM: SVM: add KVM_SEV_SNP_LAUNCH_UPDATE command
  KVM: SVM: Reclaim the guest pages when SEV-SNP VM terminates
  KVM: SVM: add KVM_SEV_SNP_LAUNCH_FINISH command
  KVM: X86: Add kvm_x86_ops to get the max page level for the TDP
  x86/mmu: Introduce kvm_mmu_map_tdp_page() for use by SEV
  KVM: X86: Introduce kvm_mmu_get_tdp_walk() for SEV-SNP use
  KVM: X86: define new RMP check related #NPF error bits
  KVM: X86: update page-fault trace to log the 64-bit error code
  KVM: SVM: add support to handle GHCB GPA register VMGEXIT
  KVM: SVM: add support to handle MSR based Page State Change VMGEXIT
  KVM: SVM: add support to handle Page State Change VMGEXIT
  KVM: X86: export the kvm_zap_gfn_range() for the SNP use
  KVM: X86: Add support to handle the RMP nested page fault

 arch/x86/include/asm/kvm_host.h  |  14 +
 arch/x86/include/asm/msr-index.h |   6 +
 arch/x86/include/asm/sev-snp.h   |  68 +++
 arch/x86/include/asm/svm.h       |  12 +-
 arch/x86/include/asm/trap_pf.h   |   2 +
 arch/x86/kvm/lapic.c             |   5 +-
 arch/x86/kvm/mmu.h               |   5 +-
 arch/x86/kvm/mmu/mmu.c           |  76 ++-
 arch/x86/kvm/svm/sev.c           | 925 ++++++++++++++++++++++++++++++-
 arch/x86/kvm/svm/svm.c           |  28 +-
 arch/x86/kvm/svm/svm.h           |  49 ++
 arch/x86/kvm/trace.h             |   6 +-
 arch/x86/kvm/vmx/vmx.c           |   8 +
 arch/x86/mm/fault.c              | 157 ++++++
 arch/x86/mm/mem_encrypt.c        | 163 ++++++
 drivers/crypto/ccp/sev-dev.c     | 312 ++++++++++-
 drivers/crypto/ccp/sev-dev.h     |   3 +
 drivers/crypto/ccp/sp-pci.c      |  12 +
 include/linux/mm.h               |   6 +-
 include/linux/psp-sev.h          | 311 +++++++++++
 include/uapi/linux/kvm.h         |  42 ++
 include/uapi/linux/psp-sev.h     |  27 +
 mm/memory.c                      |  11 +
 23 files changed, 2224 insertions(+), 24 deletions(-)
```
#### [kvm-unit-tests PATCH 0/3] Add support for external tests and litmus7
##### From: Nikos Nikoleris <nikos.nikoleris@arm.com>

```c
From patchwork Wed Mar 24 17:13:59 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Nikos Nikoleris <nikos.nikoleris@arm.com>
X-Patchwork-Id: 12161873
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.8 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_PATCH,MAILING_LIST_MULTI,
	MENTIONS_GIT_HOSTING,SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED,USER_AGENT_GIT
	autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 97C77C433E4
	for <kvm@archiver.kernel.org>; Wed, 24 Mar 2021 17:15:04 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 697C561A1E
	for <kvm@archiver.kernel.org>; Wed, 24 Mar 2021 17:15:04 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S237085AbhCXROc (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Wed, 24 Mar 2021 13:14:32 -0400
Received: from foss.arm.com ([217.140.110.172]:36880 "EHLO foss.arm.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S236630AbhCXROP (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 24 Mar 2021 13:14:15 -0400
Received: from usa-sjc-imap-foss1.foss.arm.com (unknown [10.121.207.14])
        by usa-sjc-mx-foss1.foss.arm.com (Postfix) with ESMTP id 164C9ED1;
        Wed, 24 Mar 2021 10:14:15 -0700 (PDT)
Received: from localhost.localdomain (unknown [172.31.20.19])
        by usa-sjc-imap-foss1.foss.arm.com (Postfix) with ESMTPSA id
 3E9B53F7D7;
        Wed, 24 Mar 2021 10:14:14 -0700 (PDT)
From: Nikos Nikoleris <nikos.nikoleris@arm.com>
To: kvm@vger.kernel.org
Cc: pbonzini@redhat.com, drjones@redhat.com, alexandru.elisei@arm.com,
        Nikos Nikoleris <nikos.nikoleris@arm.com>
Subject: [kvm-unit-tests PATCH 0/3] Add support for external tests and litmus7
 documentation
Date: Wed, 24 Mar 2021 17:13:59 +0000
Message-Id: <20210324171402.371744-1-nikos.nikoleris@arm.com>
X-Mailer: git-send-email 2.25.1
MIME-Version: 1.0
X-ARM-No-Footer: FoSSMail
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This set of patches makes small changes to the build system to allow
easy integration of tests not included in the repository. To this end,
it adds a parameter to the configuration script `--ext-dir=DIR` which
will instruct the build system to include the Makefile in
DIR/Makefile. The external Makefile can then add extra tests,
link object files and modify/extend flags.

In addition, to demonstrate how we can use this functionality, a
README file explains how to use litmus7 to generate the C code for
litmus tests and link with kvm-unit-tests to produce flat files.

Note that currently, litmus7 produces its own independent Makefile as
an intermediate step. Once this set of changes is committed, litmus7
will be modifed to make use hook to specify external tests and
leverage the build system to build the external tests
(https://github.com/relokin/herdtools7/commit/8f23eb39d25931c2c34f4effa096df58547a3bb4).

Nikos Nikoleris (3):
  arm/arm64: Avoid wildcard in the arm_clean recipe of the Makefile
  arm/arm64: Add a way to specify an external directory with tests
  README: Add a guide of how to run tests with litmus7

 configure           |   7 +++
 arm/Makefile.common |  11 +++-
 README.litmus7.md   | 125 ++++++++++++++++++++++++++++++++++++++++++++
 3 files changed, 141 insertions(+), 2 deletions(-)
 create mode 100644 README.litmus7.md
```
#### [PATCH 0/5 v4] KVM: nSVM: Check addresses of MSR bitmap and IO bitmap
##### From: Krish Sadhukhan <krish.sadhukhan@oracle.com>

```c
From patchwork Wed Mar 24 17:50:01 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Krish Sadhukhan <krish.sadhukhan@oracle.com>
X-Patchwork-Id: 12162007
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-13.8 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_PATCH,
	MAILING_LIST_MULTI,MSGID_FROM_MTA_HEADER,SPF_HELO_NONE,SPF_PASS,
	USER_AGENT_GIT autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 58E3FC433EA
	for <kvm@archiver.kernel.org>; Wed, 24 Mar 2021 18:39:33 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 401CB61A38
	for <kvm@archiver.kernel.org>; Wed, 24 Mar 2021 18:39:33 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S237640AbhCXSjA (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Wed, 24 Mar 2021 14:39:00 -0400
Received: from userp2130.oracle.com ([156.151.31.86]:37662 "EHLO
        userp2130.oracle.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S237684AbhCXSir (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 24 Mar 2021 14:38:47 -0400
Received: from pps.filterd (userp2130.oracle.com [127.0.0.1])
        by userp2130.oracle.com (8.16.0.42/8.16.0.42) with SMTP id
 12OIOjol126595;
        Wed, 24 Mar 2021 18:38:43 GMT
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=oracle.com;
 h=from : to : cc :
 subject : date : message-id : content-transfer-encoding : content-type :
 mime-version; s=corp-2020-01-29;
 bh=IMo7Fgw3qtmXAke320CyNWFw1aEuO2sYuhH1FVznZIc=;
 b=F0c2uKnj6ahefp3HrLPvDyrFMUbkpFlx21EEgZES5H63+cJDsIaPaEtr+MkPR6eF6wpL
 kQS9LHiGxVsp3Xohtms8QdNmsI91wiFv1Y+EB6ERb4neVQoTjqAeHDx9cp8q1U1+IR4O
 hJ5CWMF/zJNWeM7jedlER6uZkndrk8f4vgL8L1woSXREhqTa/PIocwfMZH46Pr9V85Ep
 FxMfjuOo+K4czDl2nHn6ijYEwHR515PaT6fjOH21sanRKsLDO7h9Qah3Ft3L3rJk10CG
 L0Ly0EV0HVpNzWlyDvaC4H7jIoE8gxI2MXVskQm+lK2wzp+h/Uf1mil0UsNwVrpOGoXt cg==
Received: from userp3020.oracle.com (userp3020.oracle.com [156.151.31.79])
        by userp2130.oracle.com with ESMTP id 37d8frbukq-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Wed, 24 Mar 2021 18:38:43 +0000
Received: from pps.filterd (userp3020.oracle.com [127.0.0.1])
        by userp3020.oracle.com (8.16.0.42/8.16.0.42) with SMTP id
 12OIQFYI167607;
        Wed, 24 Mar 2021 18:38:43 GMT
Received: from nam12-mw2-obe.outbound.protection.outlook.com
 (mail-mw2nam12lp2040.outbound.protection.outlook.com [104.47.66.40])
        by userp3020.oracle.com with ESMTP id 37dtttpj5x-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Wed, 24 Mar 2021 18:38:42 +0000
ARC-Seal: i=1; a=rsa-sha256; s=arcselector9901; d=microsoft.com; cv=none;
 b=IAvFRg7y3HPo9KORdWONSSPsTg12xf9XNGN8detSNNz5eE1VSmexDsVhyt6o4aa1uFiLRCeYz3XhvugqWjziwbyV/aMbQjjuyvpMD8Z4/+pCaLbnUVte+lX3/8sQtP5OBiZUvecAjI41BO61vCIRkYr5hstYORYKa2uY3a81cYN3YRgFvMKCdqzD5z5ClQee8PzZw0Z6YjzQjI3/30EQ/pso9W+LHhcP5bfZLcgkyqsZ6e/o7FjAGPsMPm3zCAoBIE/kqTev0Zdn+yfBDWj9wcDXN5VYYMakyskhG6ZI9KXTOTQ3T7MV959xMLkhEo+alnXUri0eswnEzAY7KXD2ag==
ARC-Message-Signature: i=1; a=rsa-sha256; c=relaxed/relaxed; d=microsoft.com;
 s=arcselector9901;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=IMo7Fgw3qtmXAke320CyNWFw1aEuO2sYuhH1FVznZIc=;
 b=VAGfA1CRtFVflibQQIRvrOuFNIxl2je5vXxfclLEHBHk98vhBu6m8FV13HxTOiZFDB7VTG2s/4zX33HNIWl51GxUzmAaTJzvYfzOVQ8GPRsx7L0b4h+ICxc2CP+d9UGyFEEnt3g0GKCku8lge3pnYhCvz+YkO+giyIF+88M2qyHNdwWojbvLCXbRnmblZE/lFL2w33Fg/HWg/yXC8cddRRYUOAq2cfRosqZ+BsbYd9256CU51TGUmk0fU8HohA+AeiwdRZTu1EGlpOHzlZetB7BTTfB1+FvP7xPDWRJoJ/3TvMixrzS49c7vWLuDmw6GbZFuJkudqfF0LPuKw3PfaA==
ARC-Authentication-Results: i=1; mx.microsoft.com 1; spf=pass
 smtp.mailfrom=oracle.com; dmarc=pass action=none header.from=oracle.com;
 dkim=pass header.d=oracle.com; arc=none
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
 d=oracle.onmicrosoft.com; s=selector2-oracle-onmicrosoft-com;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=IMo7Fgw3qtmXAke320CyNWFw1aEuO2sYuhH1FVznZIc=;
 b=p/rZHEpPBl2aRcSFvsx6ywQusFqYVkqVSFmKOwSiGKaW0P5KY6Pxjyx0t5hoi9WGCbp0GeQGpYMZP4Czirv09nbdLoeVaSdQBstHV2xMGA4wcl2tleD1Kov8W0ywhn1Zak7h2nZPL3uH8148osyw9EfE7SVZIvH7N6HS3IKCxHA=
Authentication-Results: vger.kernel.org; dkim=none (message not signed)
 header.d=none;vger.kernel.org; dmarc=none action=none header.from=oracle.com;
Received: from SN6PR10MB3021.namprd10.prod.outlook.com (2603:10b6:805:cc::19)
 by SA2PR10MB4665.namprd10.prod.outlook.com (2603:10b6:806:fb::17) with
 Microsoft SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.3955.18; Wed, 24 Mar
 2021 18:38:41 +0000
Received: from SN6PR10MB3021.namprd10.prod.outlook.com
 ([fe80::1871:3741:cc17:bcf7]) by SN6PR10MB3021.namprd10.prod.outlook.com
 ([fe80::1871:3741:cc17:bcf7%7]) with mapi id 15.20.3955.025; Wed, 24 Mar 2021
 18:38:40 +0000
From: Krish Sadhukhan <krish.sadhukhan@oracle.com>
To: kvm@vger.kernel.org
Cc: pbonzini@redhat.com, jmattson@google.com, seanjc@google.com
Subject: [PATCH 0/5 v4] KVM: nSVM: Check addresses of MSR bitmap and IO bitmap
 tables on vmrun of nested guests
Date: Wed, 24 Mar 2021 13:50:01 -0400
Message-Id: <20210324175006.75054-1-krish.sadhukhan@oracle.com>
X-Mailer: git-send-email 2.25.4
X-Originating-IP: [138.3.201.29]
X-ClientProxiedBy: BYAPR05CA0009.namprd05.prod.outlook.com
 (2603:10b6:a03:c0::22) To SN6PR10MB3021.namprd10.prod.outlook.com
 (2603:10b6:805:cc::19)
MIME-Version: 1.0
X-MS-Exchange-MessageSentRepresentingType: 1
Received: from ban25x6uut29.us.oracle.com (138.3.201.29) by
 BYAPR05CA0009.namprd05.prod.outlook.com (2603:10b6:a03:c0::22) with Microsoft
 SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.3977.10 via Frontend
 Transport; Wed, 24 Mar 2021 18:38:40 +0000
X-MS-PublicTrafficType: Email
X-MS-Office365-Filtering-Correlation-Id: ddb6df48-9078-4676-a4dc-08d8eef40ba1
X-MS-TrafficTypeDiagnostic: SA2PR10MB4665:
X-Microsoft-Antispam-PRVS: 
 <SA2PR10MB46657F659BA43E42C6C0141981639@SA2PR10MB4665.namprd10.prod.outlook.com>
X-MS-Oob-TLC-OOBClassifiers: OLM:7219;
X-MS-Exchange-SenderADCheck: 1
X-Microsoft-Antispam: BCL:0;
X-Microsoft-Antispam-Message-Info: 
 2s5Xd20oAqiQuq4Dgtaq2HgfzEQTjcReKVoI+LGyZb5UmuZlXxFssmOVR5OgH/yRx8i1GM0lIuSxZt8oB9A0OlwDdN8/SsHSj3qZb3F2BdfC8sVPJxrqRL3ujX7MFFcqdop9MUciIsxXB92KysLao/l7I+8DH+ArYF6PsUK3ToAxvCV/C+8H7/TX+9O++aLaaefpKPNe3l4XixLtV9XZx1I2PRO6l6GEk/ky7ZDBlBNoYUcZp8/7RmDAV3gE7kDeYrpdhj9anRr1h0wdenGc4qmAbBAIkuaM+pb3/1AIeq7xI9UtGQM+rFBa4fOQxk7cl71UC1Dc56lWJ1k2gWqHwi+bkN1yN5/OPMknJxfnhHTnIhbOgZ/cVBnN6sdxWIXoH4JYDafUKHmV0wJZVvroxlinnlha5jSO0dbH5Y9FCzUo5QSj5tmvdd7Nd3wRnEU5AVom498VDIuyqr7gimwlSdZBY5Rekq+VOF29nU25ZDcXBltfv6ztT/kOcumyHSiAr5FPMfPeQCbJXYoCrYCv8bybvmVdNvrbPTdy7ARYS0YAiuz1ebU5F3+us76jKnjGzwdc2E6o/WjVJOJ3+HzggAGcYIfEiAS//pgVScUC759Ye+LW9Op4dzcf42u9sJ+dL+Ejjb20fFTC0EL1ynJa7w==
X-Forefront-Antispam-Report: 
 CIP:255.255.255.255;CTRY:;LANG:en;SCL:1;SRV:;IPV:NLI;SFV:NSPM;H:SN6PR10MB3021.namprd10.prod.outlook.com;PTR:;CAT:NONE;SFS:(376002)(346002)(396003)(366004)(39860400002)(136003)(66946007)(6486002)(36756003)(16526019)(186003)(478600001)(6666004)(956004)(1076003)(6916009)(2616005)(8676002)(38100700001)(4326008)(83380400001)(44832011)(316002)(66476007)(66556008)(5660300002)(2906002)(7696005)(52116002)(8936002)(86362001)(26005);DIR:OUT;SFP:1101;
X-MS-Exchange-AntiSpam-MessageData: 
 70xdWpc+OqbvGevGQKpzD9y7hkeuulhU98iGiTDzjSbdn250/dDTs0fbqnjMy1QHe6niZMyQZQPYyFfDg7phUGEhdf93i4Mx+OBPcLmSYvlHM7qfSYaiiVvh6yZZQprggPDVarthFs4Vq7q3/8oDuWJJ+Ur3FWOC4PWaMxC3czTvfwT8mrdh3X+6VCK873cfH+yOHznEHWorY+eKVrSUW5B9owlVUIDtV9EK7ZbdEcVmS60hAQnCH2eQlI1jz1VssmirUNJUTJPyG5bPLxkOIXxhxNaNAhfnV8PgkIc3o9ey9GEYB811YTgpcQv3TeTYm5k1x5xkD65X3Lkt7NoawbZztqUyP2IZCzh1ZLASNIFXDemNGzycc+okhafvpui86ZdCtOIxrIPb/6zi8UJzSGXSEfRa6UqiBiEpQO+Ow+/41U4TrpFT9oHzxf2ibGW+CxMh9c1fIZhFeQNryuRMErXXsg4Jfoqx6am52fM6w9S0HKCmPY2jpeWLeQigZaafcwhpNgBpT5CUcwN5gba4w5KzUZ7Z3M1CE9RB7INhqud0i3lPu1QBwLZJFlSL2qjPQiqgwXo/GbD/qgVMstFH28dP3fhSt30zt89wlkj0LoBD78YXR2q2vq8BRHvSovLUYsf+/LaO3U2+vsPVhfNo08oD3BG6Zsysa24BE77chfnOqdGNqYxx2ouxuRpkzHMOgg+Entsyb6vTIQ4FUYwdYjAkv0Mhkm3mQlTObF3IuAZ2LfSpPma81IkGDOYYo1czMz1vBzBbXg3nDb5wJnvRJ3uy/FqkXWb/AF+/lVeaxF536H06zhWaLwR25wlSaZk+E43+TAR7T6k9tknWalybwgp+buKlT4OoIl5GhyrpwUZT4+B2DG4DiTWT6d1akSQnLcu5gf0XU/1vTirRFBNO7F9ApvLCCTsVCIOszhBSOZEoeEe97mvPsmzm/BtDvIL3q9B3OhjrQE32V8/3nFCilXz5oXq3HGszi4HLN/G1qkn/oxEmZVZJfrr4QduvwADN/btpLqE/z2thMyM+s9F1FBSVpC6YVeB4jzpTzq/0Ytb3CSj6NyizAmu7ImDa0t/8jFzviflN2Bk2Sk1yQguM7iP/hHLlBTbXPJEt/X7663mZzmouA6qnSfqgr+kPNI+LVA1CuUfpRnAqLpb+Vk6yPK/exJK1t/SMCEC/pCYqDZkq7GX3N0w8O1rn1Gn19HA9VWptx2RH7p8HMRB8BT7Y3MMl3dt3ES5ZedFpSz+3LO4Y98Abv0+T1cIL+nBJzVbZMPVEgcGAsBS2GBrChHVFi7Jy5unTBWPM2elTsCzszaKPF+HRc7x1g7vWsfeIEEAA
X-OriginatorOrg: oracle.com
X-MS-Exchange-CrossTenant-Network-Message-Id: 
 ddb6df48-9078-4676-a4dc-08d8eef40ba1
X-MS-Exchange-CrossTenant-AuthSource: SN6PR10MB3021.namprd10.prod.outlook.com
X-MS-Exchange-CrossTenant-AuthAs: Internal
X-MS-Exchange-CrossTenant-OriginalArrivalTime: 24 Mar 2021 18:38:40.9297
 (UTC)
X-MS-Exchange-CrossTenant-FromEntityHeader: Hosted
X-MS-Exchange-CrossTenant-Id: 4e2c6054-71cb-48f1-bd6c-3a9705aca71b
X-MS-Exchange-CrossTenant-MailboxType: HOSTED
X-MS-Exchange-CrossTenant-UserPrincipalName: 
 eLWTkzl05mgPPuim6L3NvNRvYVBqk5PEJaoLmC4LprX8yjaCHK/SDhQRmU+ZJnqicGFPWc8UKz49vBwLsIe0cVgj+B57wFEpKScS15bXU2Y=
X-MS-Exchange-Transport-CrossTenantHeadersStamped: SA2PR10MB4665
X-Proofpoint-Virus-Version: vendor=nai engine=6200 definitions=9933
 signatures=668683
X-Proofpoint-Spam-Details: rule=notspam policy=default score=0 adultscore=0
 malwarescore=0 spamscore=0
 mlxscore=0 phishscore=0 suspectscore=0 mlxlogscore=999 bulkscore=0
 classifier=spam adjust=0 reason=mlx scancount=1 engine=8.12.0-2009150000
 definitions=main-2103240133
X-Proofpoint-Virus-Version: vendor=nai engine=6200 definitions=9933
 signatures=668683
X-Proofpoint-Spam-Details: rule=notspam policy=default score=0
 lowpriorityscore=0 priorityscore=1501
 impostorscore=0 spamscore=0 mlxscore=0 suspectscore=0 mlxlogscore=999
 phishscore=0 bulkscore=0 adultscore=0 malwarescore=0 clxscore=1015
 classifier=spam adjust=0 reason=mlx scancount=1 engine=8.12.0-2009150000
 definitions=main-2103240133
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

v3 -> v4:
	1. There were some issues with the checks added in
	   nested_vmcb_check_controls() in patch# 2. Those are fixed. Also,
	   instead of using page_address_valid() for the checks, a new
	   function is now used. The new function doesn't check for alignment
	   of the addresses of intercept tables.
	2. In patch# 4, the tests for alignment of the addresses of intercept
	   tables, have been removed.


[PATCH 1/5 v4] KVM: SVM: Move IOPM_ALLOC_ORDER and MSRPM_ALLOC_ORDER
[PATCH 2/5 v4] KVM: nSVM: Check addresses of MSR and IO permission maps
[PATCH 3/5 v4] KVM: nSVM: Cleanup in nested_svm_vmrun()
[PATCH 4/5 v4] nSVM: Test addresses of MSR and IO permissions maps
[PATCH 5/5 v4] SVM: Use ALIGN macro when aligning 'io_bitmap_area'

 arch/x86/kvm/svm/nested.c | 59 +++++++++++++++++++++++++++++------------------
 arch/x86/kvm/svm/svm.c    |  3 ---
 arch/x86/kvm/svm/svm.h    |  3 +++
 3 files changed, 40 insertions(+), 25 deletions(-)

Krish Sadhukhan (3):
      KVM: SVM: Move IOPM_ALLOC_ORDER and MSRPM_ALLOC_ORDER #defines to svm.h
      nSVM: Check addresses of MSR and IO permission maps
      KVM: nSVM: Cleanup in nested_svm_vmrun()

 x86/svm.c       |  2 +-
 x86/svm_tests.c | 28 ++++++++++++++++++++++++++++
 2 files changed, 29 insertions(+), 1 deletion(-)

Krish Sadhukhan (2):
      nSVM: Test addresses of MSR and IO permissions maps
      SVM: Use ALIGN macro when aligning 'io_bitmap_area'
```
