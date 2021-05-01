

#### [PATCH Part1 RFC v2 00/20] Add AMD Secure Nested Paging (SEV-SNP)
##### From: Brijesh Singh <brijesh.singh@amd.com>

```c
From patchwork Fri Apr 30 12:15:56 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Brijesh Singh <brijesh.singh@amd.com>
X-Patchwork-Id: 12233167
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-13.7 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_PATCH,
	MAILING_LIST_MULTI,MSGID_FROM_MTA_HEADER,SPF_HELO_NONE,SPF_PASS,
	USER_AGENT_GIT autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 7F643C433B4
	for <kvm@archiver.kernel.org>; Fri, 30 Apr 2021 12:16:55 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 437E5613EF
	for <kvm@archiver.kernel.org>; Fri, 30 Apr 2021 12:16:55 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S231909AbhD3MRm (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Fri, 30 Apr 2021 08:17:42 -0400
Received: from mail-dm6nam12on2089.outbound.protection.outlook.com
 ([40.107.243.89]:57920
        "EHLO NAM12-DM6-obe.outbound.protection.outlook.com"
        rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org with ESMTP
        id S229911AbhD3MRl (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 30 Apr 2021 08:17:41 -0400
ARC-Seal: i=1; a=rsa-sha256; s=arcselector9901; d=microsoft.com; cv=none;
 b=Vf1iF3bUvoL9RQvmsLkvgE5JAfREZZ83eK75W9IETqLImnc0pj+v/MzIFO1Oeub125nBm6BI5MLIO/y6oSvZEX0kNfq4s8P2Lcc8YsdUAELgJdKyf7gkjFaR0dE5nhcewxyNg2C7MOc2fZmFShx8ZAU5LxCUYlLLErAMcVqJLxc06OFLovOqo6YwMp6Udz7Lgnk8169SCyRytpAEBwCI8ATGukgRgWc6ZTXPIjjKK3mgD/FhC0lMzex06Vug2I9o9XQP970vtePyF703NcCuNc5OcMazgMVw4CAVYP9Tr1gi0GRyZ6cJr7d+5o+S7wYqdiHAePjQxNDAASf3LLcP8w==
ARC-Message-Signature: i=1; a=rsa-sha256; c=relaxed/relaxed; d=microsoft.com;
 s=arcselector9901;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=cVhGq3NXPwqn3tmVSPQArJ+y5WMyJz65MrvTf4IlK7Q=;
 b=M1L/cVuu22UeOp5OIOadmpKFJPDFiyzT2W7NTe3LukAjLh82TsjgQfpgITyvoTEHLtkGoN0fUonUohF9T2MmvGlZm8NQeY6gjw1cg2sQzjlu5d56lkaqr/3Re9HCddhWb3h9W45H0fv2om3VgpsC9hZELAg2FgR24OIieB9tG0dzNJPD6gyisplwBq6p/F0TGZtf2ZcPtVIu2rVdqB77QWtsBAt0U0Qov1D46jeg6vrSb/zpQbToB1csnRoMCyUu+s+wlYNhOJluH17IYGD8/bpo/pTe5I7gat1N2sVdxNfsA7ylxfK3LpG0MLpLuFKeg1RJy1S+hIQ4jxfvyUojmw==
ARC-Authentication-Results: i=1; mx.microsoft.com 1; spf=pass
 smtp.mailfrom=amd.com; dmarc=pass action=none header.from=amd.com; dkim=pass
 header.d=amd.com; arc=none
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=amd.com; s=selector1;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=cVhGq3NXPwqn3tmVSPQArJ+y5WMyJz65MrvTf4IlK7Q=;
 b=nIqoRSAFqnitwf5kWdOkpdRmp5+ZyXXWp7SCv2VneSiFhpSlXb8zsWgtMfD6roOy6905M3WCBmGlCJ1ZL2hhmRUrYLUuirFfWwAsb9fkhcPHQg9P9UmwNZ/AtTeKLrtzWnnpbcxou4rtlNwNfbCvClpFWB0LVWLBfPXoMejKmLQ=
Authentication-Results: kernel.org; dkim=none (message not signed)
 header.d=none;kernel.org; dmarc=none action=none header.from=amd.com;
Received: from SN6PR12MB2718.namprd12.prod.outlook.com (2603:10b6:805:6f::22)
 by SA0PR12MB4431.namprd12.prod.outlook.com (2603:10b6:806:95::11) with
 Microsoft SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.4065.26; Fri, 30 Apr
 2021 12:16:48 +0000
Received: from SN6PR12MB2718.namprd12.prod.outlook.com
 ([fe80::9898:5b48:a062:db94]) by SN6PR12MB2718.namprd12.prod.outlook.com
 ([fe80::9898:5b48:a062:db94%6]) with mapi id 15.20.4065.027; Fri, 30 Apr 2021
 12:16:47 +0000
From: Brijesh Singh <brijesh.singh@amd.com>
To: x86@kernel.org, linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Cc: tglx@linutronix.de, bp@alien8.de, jroedel@suse.de,
        thomas.lendacky@amd.com, pbonzini@redhat.com, mingo@redhat.com,
        dave.hansen@intel.com, rientjes@google.com, seanjc@google.com,
        peterz@infradead.org, hpa@zytor.com, tony.luck@intel.com,
        Brijesh Singh <brijesh.singh@amd.com>
Subject: [PATCH Part1 RFC v2 00/20] Add AMD Secure Nested Paging (SEV-SNP)
 Guest Support
Date: Fri, 30 Apr 2021 07:15:56 -0500
Message-Id: <20210430121616.2295-1-brijesh.singh@amd.com>
X-Mailer: git-send-email 2.17.1
X-Originating-IP: [165.204.77.1]
X-ClientProxiedBy: SN4PR0401CA0021.namprd04.prod.outlook.com
 (2603:10b6:803:21::31) To SN6PR12MB2718.namprd12.prod.outlook.com
 (2603:10b6:805:6f::22)
MIME-Version: 1.0
X-MS-Exchange-MessageSentRepresentingType: 1
Received: from sbrijesh-desktop.amd.com (165.204.77.1) by
 SN4PR0401CA0021.namprd04.prod.outlook.com (2603:10b6:803:21::31) with
 Microsoft SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.4087.27 via Frontend
 Transport; Fri, 30 Apr 2021 12:16:47 +0000
X-MS-PublicTrafficType: Email
X-MS-Office365-Filtering-Correlation-Id: 2fc7e962-4636-4cbd-c7fb-08d90bd1d3a0
X-MS-TrafficTypeDiagnostic: SA0PR12MB4431:
X-MS-Exchange-Transport-Forked: True
X-Microsoft-Antispam-PRVS: 
 <SA0PR12MB4431F0E741B16D86721E4FBEE55E9@SA0PR12MB4431.namprd12.prod.outlook.com>
X-MS-Oob-TLC-OOBClassifiers: OLM:4125;
X-MS-Exchange-SenderADCheck: 1
X-Microsoft-Antispam: BCL:0;
X-Microsoft-Antispam-Message-Info: 
 5FSEmP5msp8LRxby4fb6AAeiGEDYQd3d6wupTpiC6QA+uR1rCu4Gxwt/qu8M8Z9y8rws6rhHcQtm4vmaXDIW9IPGiAulZen/+3AO6Pal+swXTcMdp8h/UH3NdDRCvZYXaNKYyQlFFWZ6KRyWHXoKUOvF2TZylg9Z02Z3a1eoChpREbXK5lmcN/gi1vEtPOYo7vdkfgVr/91lW9c1+/cRZPqNcrtRH7JFqrlV9zHVT+Nc0qOcCcJByOsCjab4jRO32vs+R+BnzjaDgf6hbzs8S2dnokF9AC+kK71T6jorDjHb63TYzZHybgzWw+9b2V+npGVcZsUAtlfe0k4LFVO+WoVHVPICp7LmqBn+dS2ujIVtHotkiIw0hEnJFRcviCjAVsuunKWhuwvx2F/5x9zQPocQQyr6A/tCiHFKYK3i4jPO1+xfSxXzsiIOO/3qWxwkEE3cFFllH8kHZb6q17DsDXzKIyTUeP4cKj5yiM0eecWvnT6DCMvTIj2ssyeHu3BsUeXQBp4MIvE8RG1Vw0AbEnzD23i9wnsCsxDcofSG3ru9G90/R7SbZvOu0ad3BZ1c7eHlufqV4uCzUlnWpF0ByM7hzwCmlOiqWSA9jO7ZhScYTylVTKDBdnDGJUsFlK3Umu0VzzAgBb+hPs9/N/rF8upx+lqZEHsSJLE4+Rd7bJrVzLyyhXRbVv9F0YLH0QzJstMWFNyLz0wb/bq+LhbZtaBpbXH+70IwHEiZXmW1Ux9dSg93ldzAIFx5Hye9xNKwXp5jQQGP0e5wQ5Rox9awmw==
X-Forefront-Antispam-Report: 
 CIP:255.255.255.255;CTRY:;LANG:en;SCL:1;SRV:;IPV:NLI;SFV:NSPM;H:SN6PR12MB2718.namprd12.prod.outlook.com;PTR:;CAT:NONE;SFS:(4636009)(136003)(376002)(346002)(366004)(39860400002)(396003)(6666004)(2906002)(38100700002)(8936002)(316002)(966005)(5660300002)(38350700002)(478600001)(1076003)(16526019)(26005)(7696005)(7416002)(186003)(8676002)(52116002)(4326008)(36756003)(956004)(6486002)(2616005)(66946007)(66476007)(66556008)(86362001)(83380400001)(44832011)(6606295002);DIR:OUT;SFP:1101;
X-MS-Exchange-AntiSpam-MessageData: =?utf-8?q?5RhTren80QRq2yD3WL63Ef0JGoistX?=
	=?utf-8?q?yDPDMe7UF1R2vj1E1eKCxtpMfFwOVxbYap+1T3gKGftYGkM638fpVnoUTtzAQitz9?=
	=?utf-8?q?FPYkRYQWlfxuB4A6+g1qqeLVzwUQLCQWeaR955fJB+PMbyYLmQjysbwiv+kC7g1vy?=
	=?utf-8?q?y0iAcW9kRB2IyUOkujk8UjuNBS4FLzM6u92H5tD7Wp+w4j08J1BRDf6EHjVsEQsq7?=
	=?utf-8?q?+u7NZDC5HHi922+QU9vNATKIHg1CIVUPWvn0P+2rUx86EEuKjKtXyOy7C1mcV7yJz?=
	=?utf-8?q?wuty3ycYYalmRZaY7kae4HvUgUUO+A7+uj1+hv5S/LVRxlugA7AwUOedqNpzJYo7k?=
	=?utf-8?q?0WbWHzZF+UyhdqQHnYZQytUcfRF3gZFNveeYSQM0nfRISQN3SJeuxce/IDjXNQP6R?=
	=?utf-8?q?sMK1IlV2QIoSKpVzZPk2EjZaI5hgy/ro1r0XmmHA4FoLBo0bN0MfwdhSoRxn4CoPA?=
	=?utf-8?q?O8pS0pDGMmsnyXQEWUF5x8HaoD0MHoKRJb/7r6iAndqjVyxa+sBSOQyEl9BKdouhE?=
	=?utf-8?q?gNYLm3EGuqfIByYqmuYr+HbARPTsZIVpRxZI/VjVO8gct6GqSQ34k8uqHV/GO/fTm?=
	=?utf-8?q?20FOKjdI2uQkWO/vgEsDKK0xOjjnlaF0r7k37PF1N8eNexbWCzJfN8MG2XPWa79Dm?=
	=?utf-8?q?PyYqs96/rwFIwiRlQ2FE2Sfz+Mo2yxsiR1QkhiHaTFyfqGajvRzjW5qGH9HAgEtxH?=
	=?utf-8?q?5HvZX8CrPITRI8J+8DFP5YTyGaD0mYmNt7E0v1dh+uaQslilDPDLNRBdbAvVyfekU?=
	=?utf-8?q?/tBLD1OhUELgnAhugMZLmHdQ4mOLH0MOglwMpn41MB09+04LVG/gW36I9bzg7A2NF?=
	=?utf-8?q?EgmfdGd+3LxY41rcFmsDdZztgiEIDLtG9vpwuVHXFXQAkOdS7H9B0nF2vZoK02dLL?=
	=?utf-8?q?6vwy4RbnHZJ22rLZIIYQops35r+rQkImK4EiDhtS0fvKTWo8GtvdxUd6LqEmXJkH2?=
	=?utf-8?q?iwhbqDfRJiN5IM8h5eXDYaEa/mzDuzao9e1m4Z40EvjVGZxyd1S18Rh2j+JpRtsQG?=
	=?utf-8?q?T2wsTLmFLt/H5uZqCwTYzjxVIV6qrvS2KdJxoImBAGyHg5B4LdKmQ/puJrdqKKAwe?=
	=?utf-8?q?0Yw3q5+VI1gjqbTcC2BIjueJeWKHqZSm3QXmHuW945uHIaSjw7hQxxzYih7D426qK?=
	=?utf-8?q?n+Nj/tRnRoIo79kpfvFHP/oTlP1V5Oussf25KEAMDL9I5ivsdAe8roY3Q5klR7MGF?=
	=?utf-8?q?e5yh79ej9IYNBJ/Ks83gpUAi15YeAptDVzH7MsZEFQCYDmR7jQGJ5yyi7FWpO3feF?=
	=?utf-8?q?hp3AHK3WK4up7B?=
X-OriginatorOrg: amd.com
X-MS-Exchange-CrossTenant-Network-Message-Id: 
 2fc7e962-4636-4cbd-c7fb-08d90bd1d3a0
X-MS-Exchange-CrossTenant-AuthSource: SN6PR12MB2718.namprd12.prod.outlook.com
X-MS-Exchange-CrossTenant-AuthAs: Internal
X-MS-Exchange-CrossTenant-OriginalArrivalTime: 30 Apr 2021 12:16:47.7734
 (UTC)
X-MS-Exchange-CrossTenant-FromEntityHeader: Hosted
X-MS-Exchange-CrossTenant-Id: 3dd8961f-e488-4e60-8e11-a82d994e183d
X-MS-Exchange-CrossTenant-MailboxType: HOSTED
X-MS-Exchange-CrossTenant-UserPrincipalName: 
 1/dxgieVgxMPm6rxbd2xQK3u1EHuP+EfsCQSFb5jAcIjO/MVXS5F1ZNAgV2UoK+u0Ss/VoicgdD9n2VY/yNStw==
X-MS-Exchange-Transport-CrossTenantHeadersStamped: SA0PR12MB4431
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

* Extended Guest request
* CPUID filtering
* AP bring up using the new SEV-SNP NAE
* Lazy validation
* Interrupt security

The series is based on tip/master commit
 - 24b57391e410 (origin/master, origin/HEAD) Merge branch 'core/rcu'
 - plus, cleanup series https://marc.info/?l=kvm&m=161952223830444&w=2

Additional resources
---------------------
SEV-SNP whitepaper
https://www.amd.com/system/files/TechDocs/SEV-SNP-strengthening-vm-isolation-with-integrity-protection-and-more.pdf
 
APM 2: https://www.amd.com/system/files/TechDocs/24593.pdf
(section 15.36)

GHCB spec:
https://developer.amd.com/wp-content/resources/56421.pdf

SEV-SNP firmware specification:
https://developer.amd.com/sev/

Change since v1:
 * Integerate the SNP support in sev.{ch}.
 * Add support to query the hypervisor feature and detect whether SNP is supported.
 * Define Linux specific reason code for the SNP guest termination.
 * Extend the setup_header provide a way for hypervisor to pass secret and cpuid page.
 * Add support to create a platform device and driver to query the attestation report
   and the derive a key.
 * Multiple cleanup and fixes to address Boris's review fedback.

Brijesh Singh (20):
  x86/sev: Define the GHCB MSR protocol for AP reset hold
  x86/sev: Save the negotiated GHCB version
  x86/sev: Add support for hypervisor feature VMGEXIT
  x86/sev: Increase the GHCB protocol version
  x86/sev: Define SNP Page State Change VMGEXIT structure
  x86/sev: Define SNP guest request NAE events
  x86/sev: Define error codes for reason set 1.
  x86/mm: Add sev_snp_active() helper
  x86/sev: check SEV-SNP features support
  x86/sev: Add a helper for the PVALIDATE instruction
  x86/compressed: Add helper for validating pages in the decompression
    stage
  x86/compressed: Register GHCB memory when SEV-SNP is active
  x86/sev: Register GHCB memory when SEV-SNP is active
  x86/sev: Add helper for validating pages in early enc attribute
    changes
  x86/kernel: Make the bss.decrypted section shared in RMP table
  x86/kernel: Validate rom memory before accessing when SEV-SNP is
    active
  x86/mm: Add support to validate memory when changing C-bit
  x86/boot: Add Confidential Computing address to setup_header
  x86/sev: Register SNP guest request platform device
  virt: Add SEV-SNP guest driver

 Documentation/x86/boot.rst              |  26 ++
 arch/x86/boot/compressed/ident_map_64.c |  17 +
 arch/x86/boot/compressed/sev.c          |  81 ++++-
 arch/x86/boot/compressed/sev.h          |  25 ++
 arch/x86/boot/header.S                  |   7 +-
 arch/x86/include/asm/mem_encrypt.h      |   2 +
 arch/x86/include/asm/msr-index.h        |   2 +
 arch/x86/include/asm/sev-common.h       |  86 +++++
 arch/x86/include/asm/sev.h              |  47 ++-
 arch/x86/include/uapi/asm/bootparam.h   |   1 +
 arch/x86/include/uapi/asm/svm.h         |   8 +
 arch/x86/kernel/head64.c                |   7 +
 arch/x86/kernel/probe_roms.c            |  13 +-
 arch/x86/kernel/sev-shared.c            |  72 +++-
 arch/x86/kernel/sev.c                   | 354 +++++++++++++++++-
 arch/x86/mm/mem_encrypt.c               |  52 ++-
 arch/x86/mm/pat/set_memory.c            |  15 +
 arch/x86/platform/efi/efi.c             |   2 +
 drivers/virt/Kconfig                    |   3 +
 drivers/virt/Makefile                   |   1 +
 drivers/virt/snp-guest/Kconfig          |  10 +
 drivers/virt/snp-guest/Makefile         |   2 +
 drivers/virt/snp-guest/snp-guest.c      | 455 ++++++++++++++++++++++++
 include/linux/efi.h                     |   1 +
 include/linux/snp-guest.h               | 124 +++++++
 include/uapi/linux/snp-guest.h          |  50 +++
 26 files changed, 1446 insertions(+), 17 deletions(-)
 create mode 100644 arch/x86/boot/compressed/sev.h
 create mode 100644 drivers/virt/snp-guest/Kconfig
 create mode 100644 drivers/virt/snp-guest/Makefile
 create mode 100644 drivers/virt/snp-guest/snp-guest.c
 create mode 100644 include/linux/snp-guest.h
 create mode 100644 include/uapi/linux/snp-guest.h
```
#### [PATCH Part2 RFC v2 00/37] Add AMD Secure Nested Paging (SEV-SNP)
##### From: Brijesh Singh <brijesh.singh@amd.com>

```c
From patchwork Fri Apr 30 12:37:45 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Brijesh Singh <brijesh.singh@amd.com>
X-Patchwork-Id: 12233283
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-13.7 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_PATCH,
	MAILING_LIST_MULTI,MSGID_FROM_MTA_HEADER,SPF_HELO_NONE,SPF_PASS,
	USER_AGENT_GIT autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id DE8C9C433B4
	for <kvm@archiver.kernel.org>; Fri, 30 Apr 2021 12:39:05 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id AF07D61482
	for <kvm@archiver.kernel.org>; Fri, 30 Apr 2021 12:39:05 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S232382AbhD3Mjr (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Fri, 30 Apr 2021 08:39:47 -0400
Received: from mail-dm6nam10on2058.outbound.protection.outlook.com
 ([40.107.93.58]:15105
        "EHLO NAM10-DM6-obe.outbound.protection.outlook.com"
        rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org with ESMTP
        id S231936AbhD3Mjp (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 30 Apr 2021 08:39:45 -0400
ARC-Seal: i=1; a=rsa-sha256; s=arcselector9901; d=microsoft.com; cv=none;
 b=Z2NxnDHRlcmX6hfUH1a3nyZ4NrsYnSm/otwkUYZ1YeCryhqL0fwp8WLLCVXQZnc08GZcSFyRZuAGYv7FIfZMoGSXXi/tsjiAPF9hjA/c14mDsG5UZAPE+nNqW/EyEZ1ExcI+20mJJdWsrG71LGynIoiQ24/oqsM2+qyQ21ZKiId66GDR9Jz+RYHeDqpE+g/Nz6RT/jUOfV3M+wDIMmYcKQVyWOSAHq6KQCDRyq3e/vdd6gbz+CqxlYuJIYh+XJVnudaF551Z/nabgBG5Ymd3xpin5WyhqwiZ2XF2RVYdqd1VolYs0gVNKcNyqbCGjZ7PDkm9WpVeA4xbZl16L0LAvQ==
ARC-Message-Signature: i=1; a=rsa-sha256; c=relaxed/relaxed; d=microsoft.com;
 s=arcselector9901;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=kEy3noc9TJ2juUdBem469NqB23jPpLN6Qy2bYVZAThU=;
 b=cjRgwlk0S2+e8cO8jIW0tB9Vio+a34XISXPqkRzzPgTMLqYQo/MXXNV6s1dXyCDPJV7u5mJqQh0sp2dZP0TQ9KNXD9Hi+J/ym3dfML0b4zRNhUwMgN/P8HNZwp/TZ8cMpzeg39FgafaKLqvPuFyEfVlBQGlqn730fHQGaBgZ41BR3hXopYzqmxrDw0DPKLEnUeAM11Z6pUr/LUqhJf5DMQblGMOBK5p3fSD0DLS1RM9WgLYgKxsl8gUm6GBHRGhYFee9BhEuxc7LadIefKQBG6PAPOSD/wVuW77AELZ1UX5lVzBe9ZZqbQms89Ggdi7ONw0FeZ2xUgj2dIrSyNIuLw==
ARC-Authentication-Results: i=1; mx.microsoft.com 1; spf=pass
 smtp.mailfrom=amd.com; dmarc=pass action=none header.from=amd.com; dkim=pass
 header.d=amd.com; arc=none
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=amd.com; s=selector1;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=kEy3noc9TJ2juUdBem469NqB23jPpLN6Qy2bYVZAThU=;
 b=Eu65HG+m9DjoBRpf5tToMk8+QmNoIMTwnocxrQALKcEOBwTdl9OZAgBzL2fzlMjl/MbEKLHF2QBUS8/S/hHno2w+Alk2WKHwbvz2csHusLrxYVfU/Wsh3UQj/UfTpQbnE7YGksoLPNJptDQcbTQIH31o1sy1/kPS1wV8hKj0kBg=
Authentication-Results: kernel.org; dkim=none (message not signed)
 header.d=none;kernel.org; dmarc=none action=none header.from=amd.com;
Received: from SN6PR12MB2718.namprd12.prod.outlook.com (2603:10b6:805:6f::22)
 by SA0PR12MB4511.namprd12.prod.outlook.com (2603:10b6:806:95::9) with
 Microsoft SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.4065.26; Fri, 30 Apr
 2021 12:38:54 +0000
Received: from SN6PR12MB2718.namprd12.prod.outlook.com
 ([fe80::9898:5b48:a062:db94]) by SN6PR12MB2718.namprd12.prod.outlook.com
 ([fe80::9898:5b48:a062:db94%6]) with mapi id 15.20.4065.027; Fri, 30 Apr 2021
 12:38:53 +0000
From: Brijesh Singh <brijesh.singh@amd.com>
To: x86@kernel.org, linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Cc: tglx@linutronix.de, bp@alien8.de, jroedel@suse.de,
        thomas.lendacky@amd.com, pbonzini@redhat.com, mingo@redhat.com,
        dave.hansen@intel.com, rientjes@google.com, seanjc@google.com,
        peterz@infradead.org, hpa@zytor.com, tony.luck@intel.com,
        Brijesh Singh <brijesh.singh@amd.com>
Subject: [PATCH Part2 RFC v2 00/37] Add AMD Secure Nested Paging (SEV-SNP)
 Hypervisor Support
Date: Fri, 30 Apr 2021 07:37:45 -0500
Message-Id: <20210430123822.13825-1-brijesh.singh@amd.com>
X-Mailer: git-send-email 2.17.1
X-Originating-IP: [165.204.77.1]
X-ClientProxiedBy: SN4PR0501CA0089.namprd05.prod.outlook.com
 (2603:10b6:803:22::27) To SN6PR12MB2718.namprd12.prod.outlook.com
 (2603:10b6:805:6f::22)
MIME-Version: 1.0
X-MS-Exchange-MessageSentRepresentingType: 1
Received: from sbrijesh-desktop.amd.com (165.204.77.1) by
 SN4PR0501CA0089.namprd05.prod.outlook.com (2603:10b6:803:22::27) with
 Microsoft SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.4108.8 via Frontend
 Transport; Fri, 30 Apr 2021 12:38:53 +0000
X-MS-PublicTrafficType: Email
X-MS-Office365-Filtering-Correlation-Id: 5bb143a0-f1de-44ba-52b5-08d90bd4ea04
X-MS-TrafficTypeDiagnostic: SA0PR12MB4511:
X-MS-Exchange-Transport-Forked: True
X-Microsoft-Antispam-PRVS: 
 <SA0PR12MB4511F5B30656881348556E94E55E9@SA0PR12MB4511.namprd12.prod.outlook.com>
X-MS-Oob-TLC-OOBClassifiers: OLM:1751;
X-MS-Exchange-SenderADCheck: 1
X-Microsoft-Antispam: BCL:0;
X-Microsoft-Antispam-Message-Info: 
 MikdWGIy5e9IW9P2uktl7CT7I57hI/huVT3D8L0ZOFQ++MP0Tc2kNx4dsbzxF0ufnfJaBZ1Dcsncp8MiYO2/2l0Z43trEAK0XRsPndeboPbYNcYBle4v8uCtGbZ6M07YKKHh5uRRk0IgNwWZmlZvZy1OzgrC1fQjiCXupzwjOXPPf6oJZHwhEuehOMQpGeL9Gbr3UdrdskzdW3H7KkMo4pyCzh+HNxdleHji+ED1iYoAr77HVjlvnACmGnJGSv9RGlWRXF+KMUkX719oW38Xhpa9RYyTS/MJfjD/BewnnhUDUJfueaFWa5JebRr21kjAW8lO4WJ/cY+DzUpSSm42VJYbFcNKxm2bKNboVsYW/9tNN6pC63cm2LZTgGCdKxpaOpTULkOsiAmrIbL1zJy35vBVMqYxwKPS0cYFYyfvy7ex4k2sJJbKwYHx9cGi6ZHtmhhww3F0qnNhmWQpqQn5Q2HOVvLQSBvOH+LICMGTUVSJokpNzkSd2FlSL5J9GkpEBy+s4GUip0TbYJaDEyrUCOKJN8XY5k+0lEmvyt45Nv/H9Xcv1AA+qk+rkjQgsc5mCKKoHvBocIhNdJUlkAJW2snC/BOQLALdcqk8KersdQ6mTlxgQCKDYNNys1ZYvRVXdzISk7GdAftoiP6zXYIH29JoYNuzz0h43YhXNPhA54xxZko3zjK3vBeO4XIuZLHo4soVCg8CyRAMloQL4b8pgX+74F8WH5+7igsIcSZcuAJ/GHSpOD6xQoynSrpiIQr0/F189kASb4a5MT3oXxaf7g==
X-Forefront-Antispam-Report: 
 CIP:255.255.255.255;CTRY:;LANG:en;SCL:1;SRV:;IPV:NLI;SFV:NSPM;H:SN6PR12MB2718.namprd12.prod.outlook.com;PTR:;CAT:NONE;SFS:(4636009)(346002)(39860400002)(136003)(366004)(376002)(396003)(83380400001)(36756003)(8936002)(86362001)(966005)(66476007)(956004)(186003)(38350700002)(16526019)(6666004)(6486002)(44832011)(52116002)(5660300002)(38100700002)(7416002)(66556008)(2616005)(26005)(478600001)(4326008)(66946007)(316002)(2906002)(8676002)(7696005)(1076003)(6606295002);DIR:OUT;SFP:1101;
X-MS-Exchange-AntiSpam-MessageData: 
 77cxu7s40lplpjlLrUygEUrcYI7ke85FPQSyPrUPuFmmJLBhWuf9E8uQi/TDqlbqcyDoAu1jX0+yEVqZri9q9SfNMr6X8ZmVcAKngW+BPTVYGXK6DDShh+5d6lmOnes16TcsSgjZRwbeaGnf0kqkpy6Ae45Vi/EonTZ7+mtqwVqk+4SC5Liq0yhuCIyG9QbyYiPp1T3ffzPkqYa9/9ypPhk4DT683IdOa57BcsDdPldMeGzLpYeFYtWVvQJYZbFLpHWxomlV7HfyE+Xxh1A7GoyBUeMIzY1O6ZSw0bskdcrWkorFRyPQ9dMQt9RMAuWu4ok6c6oahFe9C7PfgLoC4YKWi5NKAdj34iEMONkt+t3W1kM1krXZLPaPfLiEZD5VTaPpcWnchW4QId3NU13D98YD2p32C/U7dJ3Edyws1XWlICHthcmOQvDqO8hItX1izKcOw2gNhD8+gMttVtU2w67YId/+10mlWH7ZID58LeCXnzXr+F7PUsdC77AniiTR/9FnYXMis1lx4+VDj+AvICNShds/+6mjtdDBzMO/ed6XMby3wclGAi/GeFS5JaTtSR8fA3XEzMK4ZsBAoX3LLYHI9ucdr+2FAnfg+KVb+pJLPaMAi5/Tl2AADTMtJz6UmvatvdvI4eNqc8YGiok7iXCgC84GhmrcmrZYS4KUFEFF10NTa7ZP5EfL2HZ9Vvm2pY1gnoOs/j63ExodvVXepU11T1cIHOBwcxBbVgCuyWFzn+zOZdHDVVtIoTjkKbwcp0tehrt7UzPzKXiegPRt9rSFUF17xQZH+c/64vs0aESVzu+pMljx1khPX4hjX1kki5HC6llwu5uSL3edOX1dRpsKfDyypqMRcXNRAsr5sq+jedHZUcIYzT/5t88Sl6q6X6KKaXau+BuERBT0UiBkMhPQzhefLeypeIPAg/ulpseB5OQ24TB77rGTRaih5qPVyvsUIeT1xKPXrhX5fvIGgnOD8HjH7aiUTaL/b9G2TcSsblFwO1hX+CknwdviGFmuPUiSQTh+UCZTP5wEThYEmBT+dKbUHrC9cezDmX78z3mlbSwNFXhj83EdS6LNjKyTrMRFcd+ZEk3lWl+a6EzJ/9GYI+BgjoKglxzRsW4GtW7Z+VNk7pCJD5uA8EpHq0ua0H+CNciLfdlRU/N0Ko/jwlDQsx8gmGyT/XULITvpwwv1LcAkKjiKvKeCSkIz3aMks3lp8WKkJCDAi5w2XccaeHjrsLVZwKr/nwE5As2JATz+tkkjl+6cX79wNsuwFIizKWhTIAh1SgPwG6fR020ByWjQnbp4kYYiTPFdSb0fz+pK/EFFOOCVSAEJRHVJo8m5
X-OriginatorOrg: amd.com
X-MS-Exchange-CrossTenant-Network-Message-Id: 
 5bb143a0-f1de-44ba-52b5-08d90bd4ea04
X-MS-Exchange-CrossTenant-AuthSource: SN6PR12MB2718.namprd12.prod.outlook.com
X-MS-Exchange-CrossTenant-AuthAs: Internal
X-MS-Exchange-CrossTenant-OriginalArrivalTime: 30 Apr 2021 12:38:53.8039
 (UTC)
X-MS-Exchange-CrossTenant-FromEntityHeader: Hosted
X-MS-Exchange-CrossTenant-Id: 3dd8961f-e488-4e60-8e11-a82d994e183d
X-MS-Exchange-CrossTenant-MailboxType: HOSTED
X-MS-Exchange-CrossTenant-UserPrincipalName: 
 D3/mLmi0Kubi1TWmiPoN7IwC3+SlygREY/pxGKVeWa6bg6BvO75f0MHWfoMRzqu0SyrQvJl5oxZFC8T2FgqGIQ==
X-MS-Exchange-Transport-CrossTenantHeadersStamped: SA0PR12MB4511
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This part of the Secure Encrypted Paging (SEV-SNP) series focuses on the
changes required in a host OS for SEV-SNP support. The series builds upon
SEV-SNP Part-1 https://marc.info/?l=kvm&m=161978500619624&w=2 .

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
- Hypevisor feature
- Guest message request

The RMP check is enforced as soon as SEV-SNP is enabled. Not every memory
access requires an RMP check. In particular, the read accesses from the
hypervisor do not require RMP checks because the data confidentiality is
already protected via memory encryption. When hardware encounters an RMP
checks failure, it raises a page-fault exception. If RMP check failure
is due to the page-size mismatch, then split the large page to resolve
the fault.

The series does not provide support for the following SEV-SNP specific
NAE's yet:

* Extended guest request
* AP bring up
* Interrupt security

The series is based on the commit:
 3bf0fcd75434 (tag: kvm-5.13-1, origin/next, next) KVM: selftests: Speed up set_memory_region_test

Changes since v1:
 * Add AP reset MSR protocol VMGEXIT NAE.
 * Add Hypervisor features VMGEXIT NAE.
 * Move the RMP table initialization and RMPUPDATE/PSMASH helper in
   arch/x86/kernel/sev.c.
 * Add support to map/unmap SEV legacy command buffer to firmware state when
   SNP is active.
 * Enhance PSP driver to provide helper to allocate/free memory used for the
   firmware context page.
 * Add support to handle RMP fault for the kernel address.
 * Add support to handle GUEST_REQUEST NAE event for attestation.
 * Rename RMP table lookup helper.
 * Drop typedef from rmpentry struct definition.
 * Drop SNP static key and use cpu_feature_enabled() to check whether SEV-SNP
   is active.
 * Multiple cleanup/fixes to address Boris review feedback.

Brijesh Singh (36):
  KVM: SVM: Provide the Hypervisor Feature support VMGEXIT
  KVM: SVM: Increase the GHCB protocol version
  x86/cpufeatures: Add SEV-SNP CPU feature
  x86/sev: Add the host SEV-SNP initialization support
  x86/sev: Add RMP entry lookup helpers
  x86/sev: Add helper functions for RMPUPDATE and PSMASH instruction
  x86/sev: Split the physmap when adding the page in RMP table
  x86/traps: Define RMP violation #PF error code
  x86/fault: Add support to handle the RMP fault for kernel address
  x86/fault: Add support to handle the RMP fault for user address
  crypto:ccp: Define the SEV-SNP commands
  crypto: ccp: Add support to initialize the AMD-SP for SEV-SNP
  crypto: ccp: Shutdown SNP firmware on kexec
  crypto:ccp: Provide APIs to issue SEV-SNP commands
  crypto: ccp: Handle the legacy TMR allocation when SNP is enabled
  crypto: ccp: Handle the legacy SEV command when SNP is enabled
  KVM: SVM: make AVIC backing, VMSA and VMCB memory allocation SNP safe
  KVM: SVM: Add initial SEV-SNP support
  KVM: SVM: define new SEV_FEATURES field in the VMCB Save State Area
  KVM: SVM: Add KVM_SNP_INIT command
  KVM: SVM: Add KVM_SEV_SNP_LAUNCH_START command
  KVM: SVM: Add KVM_SEV_SNP_LAUNCH_UPDATE command
  KVM: SVM: Reclaim the guest pages when SEV-SNP VM terminates
  KVM: SVM: Add KVM_SEV_SNP_LAUNCH_FINISH command
  KVM: X86: Add kvm_x86_ops to get the max page level for the TDP
  KVM: X86: Introduce kvm_mmu_map_tdp_page() for use by SEV
  KVM: X86: Introduce kvm_mmu_get_tdp_walk() for SEV-SNP use
  KVM: X86: Define new RMP check related #NPF error bits
  KVM: X86: update page-fault trace to log the 64-bit error code
  KVM: SVM: Add support to handle GHCB GPA register VMGEXIT
  KVM: SVM: Add support to handle MSR based Page State Change VMGEXIT
  KVM: SVM: Add support to handle Page State Change VMGEXIT
  KVM: X86: Export the kvm_zap_gfn_range() for the SNP use
  KVM: SVM: Add support to handle the RMP nested page fault
  KVM: SVM: Provide support for SNP_GUEST_REQUEST NAE event
  KVM: SVM: Advertise the SEV-SNP feature support

Tom Lendacky (1):
  KVM: SVM: Add support to handle AP reset MSR protocol

 arch/x86/include/asm/cpufeatures.h       |   1 +
 arch/x86/include/asm/disabled-features.h |   8 +-
 arch/x86/include/asm/kvm_host.h          |  14 +
 arch/x86/include/asm/msr-index.h         |   6 +
 arch/x86/include/asm/sev.h               |   5 +-
 arch/x86/include/asm/svm.h               |  15 +-
 arch/x86/include/asm/trap_pf.h           |  18 +-
 arch/x86/kernel/cpu/amd.c                |   3 +-
 arch/x86/kernel/sev.c                    | 167 ++++
 arch/x86/kvm/lapic.c                     |   5 +-
 arch/x86/kvm/mmu.h                       |   5 +-
 arch/x86/kvm/mmu/mmu.c                   |  76 +-
 arch/x86/kvm/svm/sev.c                   | 961 ++++++++++++++++++++++-
 arch/x86/kvm/svm/svm.c                   |  22 +-
 arch/x86/kvm/svm/svm.h                   |  31 +-
 arch/x86/kvm/trace.h                     |   6 +-
 arch/x86/kvm/vmx/vmx.c                   |   8 +
 arch/x86/mm/fault.c                      | 207 +++++
 drivers/crypto/ccp/sev-dev.c             | 647 ++++++++++++++-
 drivers/crypto/ccp/sev-dev.h             |  14 +
 drivers/crypto/ccp/sp-pci.c              |  12 +
 include/linux/mm.h                       |   6 +-
 include/linux/psp-sev.h                  | 323 ++++++++
 include/linux/sev.h                      |  81 ++
 include/uapi/linux/kvm.h                 |  43 +
 include/uapi/linux/psp-sev.h             |  44 ++
 mm/memory.c                              |  13 +
 tools/arch/x86/include/asm/cpufeatures.h |   1 +
 28 files changed, 2664 insertions(+), 78 deletions(-)
 create mode 100644 include/linux/sev.h
```
#### [PATCH v5 0/2] fallback for emulation errors
##### From: Aaron Lewis <aaronlewis@google.com>

```c
From patchwork Fri Apr 30 14:37:49 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Aaron Lewis <aaronlewis@google.com>
X-Patchwork-Id: 12233567
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-21.3 required=3.0 tests=BAYES_00,DKIMWL_WL_MED,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT,
	USER_IN_DEF_DKIM_WL autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id A529EC433ED
	for <kvm@archiver.kernel.org>; Fri, 30 Apr 2021 14:37:56 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 69664613D9
	for <kvm@archiver.kernel.org>; Fri, 30 Apr 2021 14:37:56 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S230379AbhD3Oin (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Fri, 30 Apr 2021 10:38:43 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:49140 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S230297AbhD3Oim (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 30 Apr 2021 10:38:42 -0400
Received: from mail-pl1-x649.google.com (mail-pl1-x649.google.com
 [IPv6:2607:f8b0:4864:20::649])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id AC7D9C06174A
        for <kvm@vger.kernel.org>; Fri, 30 Apr 2021 07:37:54 -0700 (PDT)
Received: by mail-pl1-x649.google.com with SMTP id
 m10-20020a170902f20ab02900ed7e32ff42so3716260plc.19
        for <kvm@vger.kernel.org>; Fri, 30 Apr 2021 07:37:54 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=date:message-id:mime-version:subject:from:to:cc;
        bh=v5lYu1w+irOCEZJQl/ANzvss1KKbzTlcUMWMr3wEwIU=;
        b=hLsvwn8xKe2dyxS2t6qKV/Q5tQNoF5Y92f3eXV85RZYbprYcxDuoixMIirnaU19+Pi
         yxN6SbDbHnyJGrriQBg0ozX//CtWauQqON9Xk0LZj8V7/TaFOCV7Kcl+ElSf3XFdDZPw
         Q5qF9Qc2H/Z3m1Sn+HRsAI4N3H66VEHQdWsfbAHg6hryDlRXeM2CJy3ceo0qi2I5H1vs
         e12eLUE7BpEX4C/ZYeXheUA8N6/qzt+lQxFhtbMnU+jVUfMvcXQSEpw/rBvSnQo1YB4R
         KnBAYHDU2XDG98RlzRvz3FGcfA+nEvp35M7scYViD9BZGyTUTdd7de6BShISlmr7V4yJ
         R2cA==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:date:message-id:mime-version:subject:from:to:cc;
        bh=v5lYu1w+irOCEZJQl/ANzvss1KKbzTlcUMWMr3wEwIU=;
        b=O/ixPkF8BNu5TOn8A6lK1/u/8zv2PkIv+cXC+rx4wwAADZbHUzaIkrPU4/jqDbMB5T
         d6hT+kESAfK+z1gGFlWWPmx7CmoPnpcfg1svDZN1Chj+7LPFuuFmHKsXNsgi39JepoJj
         nDSM8uAvrWFYZYnbqZ832yxBvvELWLrgkBT4KDdfhacTj6dj4LJTUsHEPumOLy+6RPay
         kZgAuFTH/Zkc1JlB3uX6+X7+f/UC4gA6aKqUsa85jP52UALmsRnWCwBKhIeN+SeiiAdy
         LbQ1+KeCBPgdpHrSzhBscAATwK+B7XHmcEhGdrLVgFtc6NUs1lmyuOUJUh7glfdWuwXY
         xjOg==
X-Gm-Message-State: AOAM533Dh9nFjcmdrjemofBqTcNSS+XW/qGMXMIss1xafMHOX9CelBXJ
        jiHEEh+qNpd6nZ/tGt5SdH6af/kyXlZNjZDn
X-Google-Smtp-Source: 
 ABdhPJzVyxCwumdlhXSDRDRuTJTfZ+CAdxm11+hy0w667BUJnxcocTjfduwCPFou+asw+4qL+IEq9wDv0xHGVjBg
X-Received: from aaronlewis1.sea.corp.google.com
 ([2620:15c:100:202:250e:2425:2e40:acc])
 (user=aaronlewis job=sendgmr) by 2002:a17:902:ec84:b029:ea:b28d:e53e with
 SMTP id x4-20020a170902ec84b02900eab28de53emr5327690plg.77.1619793474194;
 Fri, 30 Apr 2021 07:37:54 -0700 (PDT)
Date: Fri, 30 Apr 2021 07:37:49 -0700
Message-Id: <20210430143751.1693253-1-aaronlewis@google.com>
Mime-Version: 1.0
X-Mailer: git-send-email 2.31.1.527.g47e6f16901-goog
Subject: [PATCH v5 0/2] fallback for emulation errors
From: Aaron Lewis <aaronlewis@google.com>
To: david.edmondson@oracle.com, seanjc@google.com, jmattson@google.com
Cc: kvm@vger.kernel.org, Aaron Lewis <aaronlewis@google.com>
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This patchset allows userspace to be a fallback for handling emulation errors.

v1 -> v2:

 - Added additional documentation for KVM_CAP_EXIT_ON_EMULATION_FAILURE.
 - In prepare_emulation_failure_exit():
   - Created a local variable for vcpu->run.
   - Cleared the flags, emulation_failure.flags.
   - Or'd the instruction bytes flag on to emulation_failure.flags.
 - Updated the comment for KVM_INTERNAL_ERROR_EMULATION flags on how they are
   to be used.
 - Updated the comment for struct emulation_failure.

v2 -> v3:

 - Update documentation for KVM_CAP_EXIT_ON_EMULATION_FAILURE.
 - Fix spacing in prepare_emulation_failure_exit().

v3 -> v4:

 - In prepare_emulation_failure_exit():
   - Clear instruction bytes to 0x90.
   - Copy over insn_size bytes rather than sizeof(ctxt->fetch.data).
 - set_page_table_entry() takes a pte rather than mask.
 - In _vm_get_page_table_entry():
   - Removed check for page aligned addresses only.
   - Added canonical check.
   - Added a check to make sure no reserved bits are set along the walk except
     for the final pte (the pte cannot have the reserved bits checked otherwise
     the test would fail).
   - Added check to ensure superpage bits are clear.
 - Added check in test for 'allow_smaller_maxphyaddr' module parameter.
 - If the is_flds() check fails, only look at the first byte.
 - Don't use labels to increment the RIP.  Decode the instruction well enough to
   ensure it is only 2-bytes.

v4 -> v5:

 - Switch 'insn_size' to u32.
 - Add documentation for how the flags are used.
 - Remove 'max_insn_size' and use 'sizeof(run->emulation_failure.insn_bytes)' instead.
 - Fix typos.
 - Fix canonical check.
 - Add reserved check for bit-7 of PML4E.
 - Add reserved check for bit-63 of all page table levels if EFER.NXE = 0.
 - Remove opcode check (it might be a prefix).
 - Remove labels.
 - Remove detritus (rogue cpuid entry in the test).

Aaron Lewis (2):
  kvm: x86: Allow userspace to handle emulation errors
  selftests: kvm: Allows userspace to handle emulation errors.

 Documentation/virt/kvm/api.rst                |  21 ++
 arch/x86/include/asm/kvm_host.h               |   6 +
 arch/x86/kvm/x86.c                            |  37 ++-
 include/uapi/linux/kvm.h                      |  23 ++
 tools/include/uapi/linux/kvm.h                |  23 ++
 tools/testing/selftests/kvm/.gitignore        |   1 +
 tools/testing/selftests/kvm/Makefile          |   1 +
 .../selftests/kvm/include/x86_64/processor.h  |   4 +
 .../selftests/kvm/lib/x86_64/processor.c      |  94 ++++++++
 .../kvm/x86_64/emulator_error_test.c          | 219 ++++++++++++++++++
 10 files changed, 425 insertions(+), 4 deletions(-)
 create mode 100644 tools/testing/selftests/kvm/x86_64/emulator_error_test.c
```
