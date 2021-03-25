#### [RFC Part1 PATCH 01/13] x86/cpufeatures: Add SEV-SNP CPU feature
##### From: Brijesh Singh <brijesh.singh@amd.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Brijesh Singh <brijesh.singh@amd.com>
X-Patchwork-Id: 12161687
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
	by smtp.lore.kernel.org (Postfix) with ESMTP id A63AAC433E2
	for <kvm@archiver.kernel.org>; Wed, 24 Mar 2021 16:45:29 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 6825361A0E
	for <kvm@archiver.kernel.org>; Wed, 24 Mar 2021 16:45:29 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S236610AbhCXQo6 (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Wed, 24 Mar 2021 12:44:58 -0400
Received: from mail-bn8nam12on2055.outbound.protection.outlook.com
 ([40.107.237.55]:61165
        "EHLO NAM12-BN8-obe.outbound.protection.outlook.com"
        rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org with ESMTP
        id S236512AbhCXQoo (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 24 Mar 2021 12:44:44 -0400
ARC-Seal: i=1; a=rsa-sha256; s=arcselector9901; d=microsoft.com; cv=none;
 b=BPG66eJktK8b5iPmyHLhuf/TOMbTkxOXlVWNrXDJWV39VPu0sSq6d+FkbaPtPeDhh8zBNWEUvFIAyturN+acU7UFJ9CEMuqLBu9UXH0Q9DT0SYFrSRWRsx5aAv6dlPtTAwyeGpQPmWouYYfK8D7shPJ9JxKWozfXt87G7NznaG+8LpbiJ8VA2++5h7j4fUjzSXPrk5L6WRaup/vRhOru5SGSP8nqjR2XNNNLbkULaYrHT8ci/vLCIIyqD3QC+gmdtJr6kxUJN99Rx8Ki7CUCAxBteTrfuVx3IapMu5vOuhDwMyq1buviiTGKJX5PRrAieeLG1/Qisvr1jTVNDB7YJQ==
ARC-Message-Signature: i=1; a=rsa-sha256; c=relaxed/relaxed; d=microsoft.com;
 s=arcselector9901;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=P1ZsLS3VYeU7Lc/sTMx0EH63IpRTYdy8IAEWThPE4yc=;
 b=QlPZoLcw9k/916SpEMq/6rqaozZPdQVPfPHHo1uEgcu9DG4s2VMOgyBp8b0SWiAamiOVnAC72r6cXoHaEPtFzGYcf4GIR1jnE0FxgYAzS+dkrE19AI1ehZy0sHD1QXvJOLbJ22UjMQFvaBQjdEkVaFd77fMwIxSZPEWCWlnAXqTyQrfRl+EomhFZy7xA6cAzy2av2GEy3+VP6UEqH5VMhD5TUyVCwlZaUNqgCkDIhZA40M/D6lgfoVkjl0vIfLtgosr1S0X831F1wo0ymptDApbo7/8uTj4ozynStJFyjAeeKQlcrOzvqOjFIOQ3ZXF3xL/p2mMu44gGlJM0FFEdHQ==
ARC-Authentication-Results: i=1; mx.microsoft.com 1; spf=pass
 smtp.mailfrom=amd.com; dmarc=pass action=none header.from=amd.com; dkim=pass
 header.d=amd.com; arc=none
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=amd.com; s=selector1;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=P1ZsLS3VYeU7Lc/sTMx0EH63IpRTYdy8IAEWThPE4yc=;
 b=hHH/SQVsCjtJUrQ3IcZSHKwSIy6ioPxYsm6xTvok+aaQxDL9+NdYeo94/78DdM1OBze+ObFTssA1H26VE/Na1C56vsUS5oHCkMsSbxtoyy7gww/DWuaCiCo9mssEk4wHVUcCuKD7rPj/Wqc+4R51wrNkuH9Bv0MQdu2w8WxwXnI=
Authentication-Results: vger.kernel.org; dkim=none (message not signed)
 header.d=none;vger.kernel.org; dmarc=none action=none header.from=amd.com;
Received: from SN6PR12MB2718.namprd12.prod.outlook.com (2603:10b6:805:6f::22)
 by SN1PR12MB2447.namprd12.prod.outlook.com (2603:10b6:802:27::22) with
 Microsoft SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.3955.18; Wed, 24 Mar
 2021 16:44:39 +0000
Received: from SN6PR12MB2718.namprd12.prod.outlook.com
 ([fe80::30fb:2d6c:a0bf:2f1d]) by SN6PR12MB2718.namprd12.prod.outlook.com
 ([fe80::30fb:2d6c:a0bf:2f1d%3]) with mapi id 15.20.3955.027; Wed, 24 Mar 2021
 16:44:39 +0000
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
Subject: [RFC Part1 PATCH 01/13] x86/cpufeatures: Add SEV-SNP CPU feature
Date: Wed, 24 Mar 2021 11:44:12 -0500
Message-Id: <20210324164424.28124-2-brijesh.singh@amd.com>
X-Mailer: git-send-email 2.17.1
In-Reply-To: <20210324164424.28124-1-brijesh.singh@amd.com>
References: <20210324164424.28124-1-brijesh.singh@amd.com>
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
 Transport; Wed, 24 Mar 2021 16:44:37 +0000
X-MS-PublicTrafficType: Email
X-MS-Office365-Filtering-HT: Tenant
X-MS-Office365-Filtering-Correlation-Id: a41b520e-8759-4794-8141-08d8eee41d37
X-MS-TrafficTypeDiagnostic: SN1PR12MB2447:
X-MS-Exchange-Transport-Forked: True
X-Microsoft-Antispam-PRVS: 
 <SN1PR12MB24477BDCA52DD3A802D614CDE5639@SN1PR12MB2447.namprd12.prod.outlook.com>
X-MS-Oob-TLC-OOBClassifiers: OLM:4941;
X-MS-Exchange-SenderADCheck: 1
X-Microsoft-Antispam: BCL:0;
X-Microsoft-Antispam-Message-Info: 
 v6rsIdyU9RbV9HW+vE2uoO3BTjFF45ATUm34+lr+TzBwZtd9mJvse+Jqv/C+CvfNhDkwkjWqGr/HVrTp+K7LFgwYR8sZnimapO9taUz2RIJaSSK8TR4KQEXGFe858GBa/0mnwf9KPo39ObUHh3qA1wkV49ikCCpLCiG0uhFfggmQEXDYgUvleWGSV/8AUBqbELXUxMHNx550g0OHsckZ5E1OeERahQZ7SBKvAdZgiUcJe+6sMnovsxqfBWpueGQEPMjwSY1WZEcY5nwgnoaG5GWro+tAZ3IFoldRE1JDp4UpG0zVVD+h5FkK4tA/ZWUZgOVBXgQVpmlHKI4W5X3mfUuVJddIelqLYYx0FGc6bjh8Iy/dAaBeChApOmGCjM+OYSQMmjLUkNlYQsowd9aZwx3Q5ohy2t/bB3XkTVWPMNm7JQFWDe+uZvXo8VRoN3BT9deAmQ9YEAWMykFhAX/AI5g2mYoTuh1PiqMjn8Zd3E1dWRkmWZnSUHoydXHKgZkh7eL4ODJfrkor9kulGQhwtm2Rx7kGVqKRoGerkWYgIHqK5g6vds70fJq/TXibWeOCiyuOruO0URb9mJ2jZaGN/l1onWvQMBUQpDTqVdL6Qep3ZFgYAdrg1QCY8krG/qlue0dndLWF0lDlKO1+7T3cUWkJMIMnLbEyLUNM8D6OgHU=
X-Forefront-Antispam-Report: 
 CIP:255.255.255.255;CTRY:;LANG:en;SCL:1;SRV:;IPV:NLI;SFV:NSPM;H:SN6PR12MB2718.namprd12.prod.outlook.com;PTR:;CAT:NONE;SFS:(4636009)(39860400002)(376002)(346002)(396003)(136003)(366004)(16526019)(38100700001)(5660300002)(26005)(44832011)(36756003)(1076003)(54906003)(8676002)(316002)(83380400001)(8936002)(4326008)(956004)(2906002)(186003)(6486002)(86362001)(7416002)(2616005)(66946007)(7696005)(478600001)(66556008)(66476007)(52116002)(6666004);DIR:OUT;SFP:1101;
X-MS-Exchange-AntiSpam-MessageData: 
 A4JvgWKerJE4pb8+bnjhCwe2EX+m9LRnjzUaQvI6Fq31hL6MHXFVTLiTIdukWzJ1fovvWodvp0DYcWSxzN1b3fQ7nh3nNV6hFj3VhTyjWCrmsMJUQ9M4fK4k+RqPuIBFXKzrk0Jb7KS+c15+rQT5GHxfw59/zmvlTv356gI+uI4T+KYlFCBiOlBF8NA7hKera8PseDfTinpnufGsml2Q4Yg2Ck4i7nr1E8FoqzVRIpFwvvQGiA4wxHIjUb5oE6S56jvWujOHrPQjlG3njMsE595mDm84ZgXl9Cmc9T28rCS00fUgT3Yw+rywdldZW2iujHEfutk5xzt7X25Usby2voaupZCc0aaP8p8XOQm1MZCBrJu9PQUsbKKZ7FsXaWqfbY1HLuhTnEi1r+fcSuPLhPybBcQUMC0NgEH5sc4+2VAM/FXVdmIGwE/Q8xgU8uXLnUcGunMQYuqDwavPnctawvpT/KaH9pyZcrHmCau1vt0TCjesbn9IJoEfJWZeGfMZ5THA2jFgbnJ4zK5NmkelVWsWS4w85v07WFLuncwks2J1VrRm9bNYRBpo6xODf/Au9DHklSdp/LI2n4RRzFqNg2JA7jltmpQTNJbIEfmDYmBKt9aM8/tu4Hq9nhOyONIMAbmeg48y5y8BIcivhoiYct3s/iomMVPTxF+TCK52MsFRGB/2J3BhGmW8yyAIOfC7zH3MSUwf6yHKY9odzIufaMdabKdYCd5Nd0VydYF8drgfKiI4xq6ANh/2P3WfhYz4IliJp5jHMV4i33S7Wakfhsxgy3wCqKgB7pR/L9SgQznb5w19VUzIKFkRKioj3wSbhF0t/R5kEt/YeVHzglV8DkkmcSw9Sis9Yvcm+l+D4/EhrvB/9VELqWHs66RDRgqhOog2g+ZkCKPFP0/YgKTSqonrCS7c7Q/B31t3Lfa8mHjdByP0tlZ9u2PbIb1psjpGaAJUR2ozTwWmZ35AMIO0kVv/2weEbGrNZBD+QylToS2A/KeLCRO7rZV7XLB4eKCqpJqvxsf2dnrUVy1v/1Rp1x2fcCnKMBjFolPEdL8X2xMA+ny06XCO8irYCAxmK6m8DBHu5puRz0ocGfU5J4IBYM5As2ltsaGDkBfn44onEoZcCzVSYN+d+wE3/F3/l5ANcYAPjV5Iui4AVxjlitTkKJ2MUXJV7UJG4zuxR/5OPVc8vtSWSSTFXmXFFuOLvGaO+lZxnS8RXbAtqPQZp9nNGALF63Z8CXIXOyUICvfoDqmF/9Z+E2Yy9on5cEW6yOP98JiCAvBb5qQogPkPoLLweyGOfT5tu/Bk1uCPkVwXS2BSG9k84gDP/QdTIIv467lt
X-OriginatorOrg: amd.com
X-MS-Exchange-CrossTenant-Network-Message-Id: 
 a41b520e-8759-4794-8141-08d8eee41d37
X-MS-Exchange-CrossTenant-AuthSource: SN6PR12MB2718.namprd12.prod.outlook.com
X-MS-Exchange-CrossTenant-AuthAs: Internal
X-MS-Exchange-CrossTenant-OriginalArrivalTime: 24 Mar 2021 16:44:38.5075
 (UTC)
X-MS-Exchange-CrossTenant-FromEntityHeader: Hosted
X-MS-Exchange-CrossTenant-Id: 3dd8961f-e488-4e60-8e11-a82d994e183d
X-MS-Exchange-CrossTenant-MailboxType: HOSTED
X-MS-Exchange-CrossTenant-UserPrincipalName: 
 ttnaftJOCDW5xmHuV2UKieGVvPCqqcnTffaJbDYpZrRd08jTEjK3pi8fnlwTWyf4lzIHBDBbcYcIoud4f99EUQ==
X-MS-Exchange-Transport-CrossTenantHeadersStamped: SN1PR12MB2447
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Add CPU feature detection for Secure Encrypted Virtualization with
Secure Nested Paging. This feature adds a strong memory integrity
protection to help prevent malicious hypervisor-based attacks like
data replay, memory re-mapping, and more.

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
Signed-off-by: Brijesh Singh <brijesh.singh@amd.com>
---
 arch/x86/include/asm/cpufeatures.h | 1 +
 arch/x86/kernel/cpu/amd.c          | 3 ++-
 arch/x86/kernel/cpu/scattered.c    | 1 +
 3 files changed, 4 insertions(+), 1 deletion(-)

```
#### [RFC Part2 PATCH 01/30] x86: Add the host SEV-SNP initialization support
##### From: Brijesh Singh <brijesh.singh@amd.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Brijesh Singh <brijesh.singh@amd.com>
X-Patchwork-Id: 12161803
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-18.7 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,
	INCLUDES_PATCH,MAILING_LIST_MULTI,MSGID_FROM_MTA_HEADER,SPF_HELO_NONE,
	SPF_PASS,URIBL_BLOCKED,USER_AGENT_GIT autolearn=unavailable
	autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 59202C433E4
	for <kvm@archiver.kernel.org>; Wed, 24 Mar 2021 17:05:56 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id EC35161A14
	for <kvm@archiver.kernel.org>; Wed, 24 Mar 2021 17:05:55 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S237093AbhCXRFX (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Wed, 24 Mar 2021 13:05:23 -0400
Received: from mail-bn8nam11on2078.outbound.protection.outlook.com
 ([40.107.236.78]:50401
        "EHLO NAM11-BN8-obe.outbound.protection.outlook.com"
        rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org with ESMTP
        id S236883AbhCXREy (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 24 Mar 2021 13:04:54 -0400
ARC-Seal: i=1; a=rsa-sha256; s=arcselector9901; d=microsoft.com; cv=none;
 b=IPML2SFD4jmHIR2PszDU3Vp4A2vxZ/RK3e4DiqliTfwC5J2g/+zVbf9+0zvV2eX+o8AsWcrZRp/3bFyryxjX7XfMlnGfTZYSO9OChZB1CG/4jB6wJUGUENF4q9fgUEOQCsRcS2ZUbuwhG/vRWKFfvMTrKjaGj62IumKeY6P4M7KPeUY+6liA7f7n8IsPSv/nbmUk1XgxC3GbBMYpEkyldtpKbqTA+eucOkykvPKrte3L97dmf9/HTqTnZWhMmjBYeKRkswI44EENJl1R6I5hB7GchV/WGKTqmSzamLwJ0UHCyuSCuqek+FuPXTullWddpexb5dzO4CEvZPnhej4dqA==
ARC-Message-Signature: i=1; a=rsa-sha256; c=relaxed/relaxed; d=microsoft.com;
 s=arcselector9901;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=FLIgnglfwxb6MRfi4trwa2szQhyt+oIcEfzRrEzx9fQ=;
 b=RVT1fFFFQyA4/NFjk3UNcL0Dadae+sjQNGl7SP4/TCd0Qsrm6X6Dwbe9IpV87rnXEfimeemYAeNVt40ed/Ft5oJhLEhHJ+Ss23HWek9B172H7Uu7A7SkMc3rHbtQIMVOMzxU26jo/+WnJaHmq+jN3m/SN5O5pwykeTZ72P6uuEvE7Tj3/Cr28Mi9YOchSWduWyS0CGGqvddLQ9XARUhx068UKAoWoa+htX6MlpNsutLNfoKYUBXyPXZ9NII3CbxRQh5n5GxIMgmCjvRWUxouvcP69bLw/NmUmiGli+jkRO+z1v1i9Jf6LPKHbcKqEdZs5IybyeKGhoQexfAqb9tgog==
ARC-Authentication-Results: i=1; mx.microsoft.com 1; spf=pass
 smtp.mailfrom=amd.com; dmarc=pass action=none header.from=amd.com; dkim=pass
 header.d=amd.com; arc=none
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=amd.com; s=selector1;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=FLIgnglfwxb6MRfi4trwa2szQhyt+oIcEfzRrEzx9fQ=;
 b=JDOVSJNvtvOZQWZXIZmkrxDEoj5IDIWz97x9IRW72oXxGeNdkQKVDjf/MXA7xTKgBmU9GWFKNHKGH52BUyu+eU7i2B8GNi7oNd6HEfF4tevfvPlLlxO5e7bDukFkT4uGzfIis6TvbxqjDOhLUcvEL3cs/sC8iXRIKL0ONqWrrCE=
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
Subject: [RFC Part2 PATCH 01/30] x86: Add the host SEV-SNP initialization
 support
Date: Wed, 24 Mar 2021 12:04:07 -0500
Message-Id: <20210324170436.31843-2-brijesh.singh@amd.com>
X-Mailer: git-send-email 2.17.1
In-Reply-To: <20210324170436.31843-1-brijesh.singh@amd.com>
References: <20210324170436.31843-1-brijesh.singh@amd.com>
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
 Transport; Wed, 24 Mar 2021 17:04:51 +0000
X-MS-PublicTrafficType: Email
X-MS-Office365-Filtering-HT: Tenant
X-MS-Office365-Filtering-Correlation-Id: 162c34f5-ead8-4fdd-de9e-08d8eee6f05d
X-MS-TrafficTypeDiagnostic: SA0PR12MB4557:
X-MS-Exchange-Transport-Forked: True
X-Microsoft-Antispam-PRVS: 
 <SA0PR12MB4557B2BC21D1BD788C1E119BE5639@SA0PR12MB4557.namprd12.prod.outlook.com>
X-MS-Oob-TLC-OOBClassifiers: OLM:8273;
X-MS-Exchange-SenderADCheck: 1
X-Microsoft-Antispam: BCL:0;
X-Microsoft-Antispam-Message-Info: 
 CwExjS+mMprWmh/f0+fKc3Py6iADibBOC/8LtqT5vLisXiEygkQ2X6UTeH58NnZE3VZj19hn2EC6UBdT7KiUQFNPXvVM98/46OI76l2EJXqfbbKePn12LvAVbJ1ukJQLApMfIF7PNoIm0Elxv4Vy/Uy9OH9A4r/7gBLpsC00uwOBr3Zv9PwdxQ5pNWbvqP7AF3I6DcwDjtRpmsIKDZglYP5+upG+3p0Sq6TtnM8Q//yu3P32zmCYG40pJGPVJdQyCqzAMxm8/ZVmIgQorQ9PGPy6AOOqBopGrzJl8xSjD33Wx8gPVk1z3Qy2jomqqp+EyTvar35Ey0IIkmYUEVytDrdgegGdrDDART5urLs6n8ceScu7sHSWG5iBQfhPJLS7NyWP9mbljJNL10CpS0rRN+SHPlro71KIb0JpXcprp614WAi1St9R7oulgdg0/gBBpbtfh9vIfoe+mWp/3RdHG0qFX6c2zSXOksdohXPNBtYWFs6UbpJL9vZhyeNr8JEJ7ptdxAp3EIktb7maT8L2+bTgAe6/ELfcW3f/UdWi35kbtyxz6YEgsf25T7z1mRy6kKwjUpBaX8Gz/AOy+XvTVSuh4+dRE2s3N9PXmcitUUUqpP6HOGsRyMofrHvxyUTBN4zwU6H+qwOSKVyeuEQpY1uBlhlvEC39esageNfhVZs=
X-Forefront-Antispam-Report: 
 CIP:255.255.255.255;CTRY:;LANG:en;SCL:1;SRV:;IPV:NLI;SFV:NSPM;H:SN6PR12MB2718.namprd12.prod.outlook.com;PTR:;CAT:NONE;SFS:(4636009)(366004)(376002)(396003)(346002)(136003)(39860400002)(86362001)(54906003)(186003)(44832011)(6666004)(4326008)(38100700001)(26005)(316002)(66476007)(8676002)(16526019)(1076003)(2616005)(83380400001)(5660300002)(6486002)(956004)(52116002)(8936002)(478600001)(7416002)(7696005)(66556008)(36756003)(66946007)(2906002);DIR:OUT;SFP:1101;
X-MS-Exchange-AntiSpam-MessageData: 
 W8uVOt1DE25xw+pyNgHzMQlxZY7ReZVVXDK2NJhLSY3mQVa/jnLCiHd1nlpsRExgzzy6mg23avkPkwUMteaSCqajJpyBzeC+guThCVe92HA3Wbogs7mE08LmF+4KLaqWZ0yDwemQ8UQw0zD+9JlOU2lxpvTeDm86SSzmuPIFuaHFg9rDk+DQqbsnhquLg2H5AcuCcWwcH7wpuNFL8iot6bfML5u7+ZHxwTzOvyTb/mjs1/40RGvn8askRl+Bl3tJItCLShgHn6JfFXH0NcwgUG576OVNVLvZQ0+nNFhlDr4bEB4uWofP0/HOTsxYDjXoRit3+w4N58ksKAC3v9nna32fCt3SV5wXApb0kEu6BYXVweQAPAOPkK+YMm2YTDIJ9c82OZNw7J5dSU0m5xmQAd/8I6haiP8SOAqA+KtXuOKYMDZmgHglyqdZ7quXr0jIbnMpQ8BYuKBkt3ujXL/8m4Ugmh66V+N8M8Dyzs0Jsj7/yKdDIThD8BojMnIO2VRiDXDrsDs2SvM0mLRXvdUeeP4njQYCFxk+2Gv6AKYq4MXWtZP8JNo1VZ0YD2Ov4pWCt/keGjCyAbGz6tPz+xPB2u/MfDgcep4S5mtPd52GOfhDHzdq7Gnxpy+CbDeigqV/pMJiIw0Nd8pVV7NmVRlgOq2vBrcl+XFf08FPfagvCqjghux6B++oiVP6RkoWXE8oO1JpXgReu89JgPZCmiyZUVAQBgyEL8SOrB80QOuykhfLk4EO6bfyTeYOaGaIL5oartjxzH7+qDDDr40yz5EnDjKV0x+KcPLwPz+z9B+pscAkAYMa0NT+YvrRji9rkcl7/qwIbQE4kkb1IRv3eBwd1p+81tdRK6O3y8guAlKxjgCLBEmNMeYr1w5pFWsNJCK9Ik5GrcfSsPHoeR0BFnc8XkMDftb5q0mDmA+GvQJDm7ARqUYE8xpiodMjBATSBIKIrPUAUf1FGuXf/sqdzCFMPMDtQphAHobFSUELVYUpGRQN6u7w4/OUmYbIvK63mli9bkahVB+j7mr+zbWt2jGyPlYPftMWtTxsoui22vmPXQoa90UYmkDiwqa/Vz7vv4z1y667CcO76C9j5kmI+k0QrcpU2crwycbxj99SewgYRJ2hVjD7TpdBJbc+pyFeMbq9mT8ldsm3cIhv+KZTPWhH8kY7J8vfNFF5N8ZOJzPIkF6IqHmZyuBiqfb04WyMGFTBlm7dLmLXJT+0S77Fe7A3NYe3P9mxNgPTI5x6daHfBokEiZeR8XLUjDE9AmzHLTA3iBSCkb69LRQRi7ZtK/B62CegJ8SAu7TvYjjCjwZYH6gruExd91Yxyp318TZ7Tfke
X-OriginatorOrg: amd.com
X-MS-Exchange-CrossTenant-Network-Message-Id: 
 162c34f5-ead8-4fdd-de9e-08d8eee6f05d
X-MS-Exchange-CrossTenant-AuthSource: SN6PR12MB2718.namprd12.prod.outlook.com
X-MS-Exchange-CrossTenant-AuthAs: Internal
X-MS-Exchange-CrossTenant-OriginalArrivalTime: 24 Mar 2021 17:04:51.7106
 (UTC)
X-MS-Exchange-CrossTenant-FromEntityHeader: Hosted
X-MS-Exchange-CrossTenant-Id: 3dd8961f-e488-4e60-8e11-a82d994e183d
X-MS-Exchange-CrossTenant-MailboxType: HOSTED
X-MS-Exchange-CrossTenant-UserPrincipalName: 
 v1yTp8jp+rHmSMO1vLLLnzu3woTZbmGKoQnR9tvu7jZWnyfLZ3am0As+35DSLVShq8xY44xyRY5udvgxGRYo5g==
X-MS-Exchange-Transport-CrossTenantHeadersStamped: SA0PR12MB4557
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The memory integrity guarantees of SEV-SNP are enforced through a new
structure called the Reverse Map Table (RMP). The RMP is a single data
structure shared across the system that contains one entry for every 4K
page of DRAM that may be used by SEV-SNP VMs. The goal of RMP is to
track the owner of each page of memory. Pages of memory can be owned by
the hypervisor, owned by a specific VM or owned by the AMD-SP. See APM2
section 15.36.3 for more detail on RMP.

The RMP table is used to enforce access control to memory. The table itself
is not directly writable by the software. New CPU instructions (RMPUPDATE,
PVALIDATE, RMPADJUST) are used to manipulate the RMP entries.

Based on the platform configuration, the BIOS reserves the memory used
for the RMP table. The start and end address of the RMP table can be
queried by reading the RMP_BASE and RMP_END MSRs. If the RMP_BASE and
RMP_END are not set then we disable the SEV-SNP feature.

The SEV-SNP feature is enabled only after the RMP table is successfully
initialized.

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
Signed-off-by: Brijesh Singh <brijesh.singh@amd.com>
---
 arch/x86/include/asm/msr-index.h |  6 +++
 arch/x86/include/asm/sev-snp.h   | 10 ++++
 arch/x86/mm/mem_encrypt.c        | 84 ++++++++++++++++++++++++++++++++
 3 files changed, 100 insertions(+)

```
#### [kvm-unit-tests PATCH 1/3] arm/arm64: Avoid wildcard in the arm_clean recipe of the Makefile
##### From: Nikos Nikoleris <nikos.nikoleris@arm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Nikos Nikoleris <nikos.nikoleris@arm.com>
X-Patchwork-Id: 12161867
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.8 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED,USER_AGENT_GIT
	autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 12CF9C433DB
	for <kvm@archiver.kernel.org>; Wed, 24 Mar 2021 17:15:04 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id E251261A1A
	for <kvm@archiver.kernel.org>; Wed, 24 Mar 2021 17:15:03 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S237051AbhCXROb (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Wed, 24 Mar 2021 13:14:31 -0400
Received: from foss.arm.com ([217.140.110.172]:36886 "EHLO foss.arm.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S236702AbhCXROQ (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 24 Mar 2021 13:14:16 -0400
Received: from usa-sjc-imap-foss1.foss.arm.com (unknown [10.121.207.14])
        by usa-sjc-mx-foss1.foss.arm.com (Postfix) with ESMTP id 1FFFC106F;
        Wed, 24 Mar 2021 10:14:16 -0700 (PDT)
Received: from localhost.localdomain (unknown [172.31.20.19])
        by usa-sjc-imap-foss1.foss.arm.com (Postfix) with ESMTPSA id
 49A363F7D7;
        Wed, 24 Mar 2021 10:14:15 -0700 (PDT)
From: Nikos Nikoleris <nikos.nikoleris@arm.com>
To: kvm@vger.kernel.org
Cc: pbonzini@redhat.com, drjones@redhat.com, alexandru.elisei@arm.com,
        Nikos Nikoleris <nikos.nikoleris@arm.com>
Subject: [kvm-unit-tests PATCH 1/3] arm/arm64: Avoid wildcard in the arm_clean
 recipe of the Makefile
Date: Wed, 24 Mar 2021 17:14:00 +0000
Message-Id: <20210324171402.371744-2-nikos.nikoleris@arm.com>
X-Mailer: git-send-email 2.25.1
In-Reply-To: <20210324171402.371744-1-nikos.nikoleris@arm.com>
References: <20210324171402.371744-1-nikos.nikoleris@arm.com>
MIME-Version: 1.0
X-ARM-No-Footer: FoSSMail
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This change adds recipes to discover the generated .o and .d files and
removes assumptions about their locations in the arm_clean recipe.

Signed-off-by: Nikos Nikoleris <nikos.nikoleris@arm.com>
---
 arm/Makefile.common | 7 +++++--
 1 file changed, 5 insertions(+), 2 deletions(-)

```
#### [PATCH] KVM: make: Fix out-of-source module builds
##### From: Siddharth Chandrasekaran <sidcha@amazon.de>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Siddharth Chandrasekaran <sidcha@amazon.de>
X-Patchwork-Id: 12161027
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-19.0 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_CR_TRAILER,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,
	USER_AGENT_GIT autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id A64E8C433C1
	for <kvm@archiver.kernel.org>; Wed, 24 Mar 2021 12:45:26 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 4FA3961A16
	for <kvm@archiver.kernel.org>; Wed, 24 Mar 2021 12:45:26 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S234393AbhCXMov (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Wed, 24 Mar 2021 08:44:51 -0400
Received: from smtp-fw-6001.amazon.com ([52.95.48.154]:42073 "EHLO
        smtp-fw-6001.amazon.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S232650AbhCXMoh (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 24 Mar 2021 08:44:37 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
  d=amazon.de; i=@amazon.de; q=dns/txt; s=amazon201209;
  t=1616589877; x=1648125877;
  h=from:to:cc:subject:date:message-id:mime-version;
  bh=QzTU51+vaXrdoMGEPdFqskhuNqgMoN2SMvPmnKALCTY=;
  b=j16HJQxas8ieqh8JvkIs7spHcYsjUSi7NPR/SkemHRQD88vQdyvKC8TT
   iN3yKHNvulZufxC2PXU+GaqP/KhKp/DqZnKTf2HD09YRiIZkSvtxXMCjn
   jM7MQHHmMxlTlr2dpWDSdw5KhA2l7AMjS8ECKASlludv3ZgG+7U5BBPth
   8=;
X-IronPort-AV: E=Sophos;i="5.81,274,1610409600";
   d="scan'208";a="101696263"
Received: from iad12-co-svc-p1-lb1-vlan2.amazon.com (HELO
 email-inbound-relay-2b-4e24fd92.us-west-2.amazon.com) ([10.43.8.2])
  by smtp-border-fw-out-6001.iad6.amazon.com with ESMTP;
 24 Mar 2021 12:44:28 +0000
Received: from EX13D28EUC003.ant.amazon.com
 (pdx1-ws-svc-p6-lb9-vlan2.pdx.amazon.com [10.236.137.194])
        by email-inbound-relay-2b-4e24fd92.us-west-2.amazon.com (Postfix) with
 ESMTPS id 94C02A2268;
        Wed, 24 Mar 2021 12:44:27 +0000 (UTC)
Received: from uc8bbc9586ea454.ant.amazon.com (10.43.162.104) by
 EX13D28EUC003.ant.amazon.com (10.43.164.43) with Microsoft SMTP Server (TLS)
 id 15.0.1497.2; Wed, 24 Mar 2021 12:44:21 +0000
From: Siddharth Chandrasekaran <sidcha@amazon.de>
To: Paolo Bonzini <pbonzini@redhat.com>,
        Sean Christopherson <seanjc@google.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>,
        Thomas Gleixner <tglx@linutronix.de>,
        Ingo Molnar <mingo@redhat.com>, Borislav Petkov <bp@alien8.de>,
        <x86@kernel.org>, "H. Peter Anvin" <hpa@zytor.com>
CC: Siddharth Chandrasekaran <sidcha@amazon.de>, <kvm@vger.kernel.org>,
        <linux-kernel@vger.kernel.org>
Subject: [PATCH] KVM: make: Fix out-of-source module builds
Date: Wed, 24 Mar 2021 13:43:47 +0100
Message-ID: <20210324124347.18336-1-sidcha@amazon.de>
X-Mailer: git-send-email 2.17.1
MIME-Version: 1.0
X-Originating-IP: [10.43.162.104]
X-ClientProxiedBy: EX13D21UWA002.ant.amazon.com (10.43.160.246) To
 EX13D28EUC003.ant.amazon.com (10.43.164.43)
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Building kvm module out-of-source with,

    make -C $SRC O=$BIN M=arch/x86/kvm

fails to find "irq.h" as the include dir passed to cflags-y does not
prefix the source dir. Fix this by prefixing $(srctree) to the include
dir path.

Signed-off-by: Siddharth Chandrasekaran <sidcha@amazon.de>
---
 arch/x86/kvm/Makefile | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
#### [PATCH 1/5 v4] KVM: SVM: Move IOPM_ALLOC_ORDER and MSRPM_ALLOC_ORDER #defines to svm.h
##### From: Krish Sadhukhan <krish.sadhukhan@oracle.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Krish Sadhukhan <krish.sadhukhan@oracle.com>
X-Patchwork-Id: 12162017
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-18.8 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,
	INCLUDES_PATCH,MAILING_LIST_MULTI,MSGID_FROM_MTA_HEADER,SPF_HELO_NONE,
	SPF_PASS,USER_AGENT_GIT autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 2AC47C43381
	for <kvm@archiver.kernel.org>; Wed, 24 Mar 2021 18:39:34 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 1341E61A26
	for <kvm@archiver.kernel.org>; Wed, 24 Mar 2021 18:39:34 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S237736AbhCXSjD (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Wed, 24 Mar 2021 14:39:03 -0400
Received: from aserp2120.oracle.com ([141.146.126.78]:49182 "EHLO
        aserp2120.oracle.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S237687AbhCXSis (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 24 Mar 2021 14:38:48 -0400
Received: from pps.filterd (aserp2120.oracle.com [127.0.0.1])
        by aserp2120.oracle.com (8.16.0.42/8.16.0.42) with SMTP id
 12OIPba9047435;
        Wed, 24 Mar 2021 18:38:44 GMT
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=oracle.com;
 h=from : to : cc :
 subject : date : message-id : in-reply-to : references :
 content-transfer-encoding : content-type : mime-version;
 s=corp-2020-01-29; bh=ovKKeLIITNnOyf7sYV7ejNLNQPh7Qh+PcU7ZNzLbbR4=;
 b=ROVeNDiMxBbMZPDtLIWfujOxX1OGdIwF+LaEaBerhAx55Dlq78M+5qXtSBSrVnkPMglP
 +BZFfkU8cHeS9WGXyzwii5r0blkXmohuwGRi6GLVEm9aocVDDWYXBYk4Ah2ER9Jxe3Oj
 SowmjDv8NamwzDyuB5XqbEmwgGvtosS1RUYXnP6DyVsBvR5YmA2QlH9Kjblfd3eKQk2l
 MiANHRxhHwxYgsv+FYFOUZ98HHDomJYqmgL4pDbApKcqpA2zDyM1hKxhBqcOFUThgagm
 D3VHtV/KmENqaLI7WEJlz2ck49yENApDhKwR2p9hDKJ4OsZZTbrlr3Z1HJIB6C8uh0oS 8A==
Received: from userp3020.oracle.com (userp3020.oracle.com [156.151.31.79])
        by aserp2120.oracle.com with ESMTP id 37d90mktnv-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Wed, 24 Mar 2021 18:38:44 +0000
Received: from pps.filterd (userp3020.oracle.com [127.0.0.1])
        by userp3020.oracle.com (8.16.0.42/8.16.0.42) with SMTP id
 12OIQFYJ167607;
        Wed, 24 Mar 2021 18:38:43 GMT
Received: from nam12-mw2-obe.outbound.protection.outlook.com
 (mail-mw2nam12lp2040.outbound.protection.outlook.com [104.47.66.40])
        by userp3020.oracle.com with ESMTP id 37dtttpj5x-2
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Wed, 24 Mar 2021 18:38:43 +0000
ARC-Seal: i=1; a=rsa-sha256; s=arcselector9901; d=microsoft.com; cv=none;
 b=kZVNV7PECT23hhKAItgpOLUZ+WczJ6Zgrt4wVpTRxU0cr5LUIRXY5PxWSKfZRTZACl8U5CQwTcxpan1PBLmhvRuaLDX6wI0ezuyTofuf6Kh4uD+UUNVQutqZsFA6uAk5LBY7lncIt542yTJWWFgl0sXyaV4wQ4LzEhaIz/yF17aPGCYbBQuZ85yo7gl7wmw0E71P2+B4ZzSJM3x8oWPINyW1pJNFr+E+GioTPJS+bjC5qQsg9D5MEun1hfgCXTTJudDTZPi5c7jqHybaGIrbJP/yurFxLuxcjtlBDoIoJSymUWdBrPS5OcDpigYr6/JLThv2AMVWPl0DyduV7Pex8A==
ARC-Message-Signature: i=1; a=rsa-sha256; c=relaxed/relaxed; d=microsoft.com;
 s=arcselector9901;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=ovKKeLIITNnOyf7sYV7ejNLNQPh7Qh+PcU7ZNzLbbR4=;
 b=hiEKPEBRe4Vhcikd1xI9NIAj8sO/BUUerrHDY0ijQkAYPaTeoqnCdVi/nC1cTuUvgQYb8x8UrhNTlXSP/vTjX+KqWdVqalrk4/nW/mZaz9lVpzIoc/Epoq73KIBArlr4NYtW8wP0NQ/ZRUWFFX8pau06feFeXKN4szi3JtHHTElOI4SdR8n4nShX40g7O/2hfAU5sSjr2bgJjT6mSU57/OlgA8cIPEZnsMsua0GR90CnZehcLNM949kikGejpAumKve3i6uFucASTsh32cBsNO8mLpKF7R2uEeZfYSJ11p16SJESMYOSd2zDD3aFEqR2iv0BK3k9/KPOWizRbY82vg==
ARC-Authentication-Results: i=1; mx.microsoft.com 1; spf=pass
 smtp.mailfrom=oracle.com; dmarc=pass action=none header.from=oracle.com;
 dkim=pass header.d=oracle.com; arc=none
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
 d=oracle.onmicrosoft.com; s=selector2-oracle-onmicrosoft-com;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=ovKKeLIITNnOyf7sYV7ejNLNQPh7Qh+PcU7ZNzLbbR4=;
 b=MZ+wIi3sNi0qbgFYYdFnRYljWfc922zvU1q6mU0QlXkmApXrVIVDAKJ8GVZAVj/b3KZRMpw6zQP6dkh/Y5NWOwrIDa8QBKrv6oIp7Uks/x9jqaLJUQpBUeVV5ZQc72K0IoJWFVHyJa7baEW0J4axIsYbc4um1gMzNBsvnhcnM70=
Authentication-Results: vger.kernel.org; dkim=none (message not signed)
 header.d=none;vger.kernel.org; dmarc=none action=none header.from=oracle.com;
Received: from SN6PR10MB3021.namprd10.prod.outlook.com (2603:10b6:805:cc::19)
 by SA2PR10MB4665.namprd10.prod.outlook.com (2603:10b6:806:fb::17) with
 Microsoft SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.3955.18; Wed, 24 Mar
 2021 18:38:42 +0000
Received: from SN6PR10MB3021.namprd10.prod.outlook.com
 ([fe80::1871:3741:cc17:bcf7]) by SN6PR10MB3021.namprd10.prod.outlook.com
 ([fe80::1871:3741:cc17:bcf7%7]) with mapi id 15.20.3955.025; Wed, 24 Mar 2021
 18:38:42 +0000
From: Krish Sadhukhan <krish.sadhukhan@oracle.com>
To: kvm@vger.kernel.org
Cc: pbonzini@redhat.com, jmattson@google.com, seanjc@google.com
Subject: [PATCH 1/5 v4] KVM: SVM: Move IOPM_ALLOC_ORDER and MSRPM_ALLOC_ORDER
 #defines to svm.h
Date: Wed, 24 Mar 2021 13:50:02 -0400
Message-Id: <20210324175006.75054-2-krish.sadhukhan@oracle.com>
X-Mailer: git-send-email 2.25.4
In-Reply-To: <20210324175006.75054-1-krish.sadhukhan@oracle.com>
References: <20210324175006.75054-1-krish.sadhukhan@oracle.com>
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
 Transport; Wed, 24 Mar 2021 18:38:41 +0000
X-MS-PublicTrafficType: Email
X-MS-Office365-Filtering-Correlation-Id: 6fe74b40-3715-4ee5-38aa-08d8eef40c54
X-MS-TrafficTypeDiagnostic: SA2PR10MB4665:
X-Microsoft-Antispam-PRVS: 
 <SA2PR10MB4665D614EB1AAE5160DFDA5981639@SA2PR10MB4665.namprd10.prod.outlook.com>
X-MS-Oob-TLC-OOBClassifiers: OLM:3513;
X-MS-Exchange-SenderADCheck: 1
X-Microsoft-Antispam: BCL:0;
X-Microsoft-Antispam-Message-Info: 
 f5VSKIaVyoOfClAgEn+jaf65a9qO/MC1aNoYrUiJiueG+WbFJ3xjaJtnfWA1VfsucmyFrW94JvbERcHN8ZezaXDPmK+AUL5I+CcARDGF0hyV0kBzvFr04vL45Al79dkK7QOcjdVv1arGU0uj3dknzmHBKdGQy1QbsuUEYBpT/X4QZjQWWKcmc4JW8yzdZkPYtEmOe/gN3+7MyMtOgETgdlIOnMVizzBUwdA3rTmEYusVp1ZKoIwmWJw/gmYFQWzWzD1vJ7Gaikkt7BUfXleKdXmculWIfPLk/iiwZETrUwm/rM4a3OThsEDrVoHu0AQvmUiptGKZSd3cFVg1XO+E6TXBrQYV5KNh/Nl9Eto5zxPGFVXeqULP4O5NcD+44QDS3Qu9wcF1KE+R+lbubUhSwWNkd/g1ZK2WmVE2C3K1djHcYOFVN4XMtMIOHHw9ORxXHxHqZpbDzWFA9Ufddb5F0M1oLN/SbtTDfzqz9HPZJHRY1jeK8EGA/HqD1n6wr+wkwmH/VnikK/7Su7lTeq8zl5MJ7SU4n+87rJI3drlEVhBfixt/LxnryCkCMX4gzlQku4T3ctmd+Ym9C7wt6Yh/6bmOHARq2X6r63yGgNuY3d5GtAo0Dqwsrah5Ihff1euKY4v0RyMuroAyLUQ7MM4qxw==
X-Forefront-Antispam-Report: 
 CIP:255.255.255.255;CTRY:;LANG:en;SCL:1;SRV:;IPV:NLI;SFV:NSPM;H:SN6PR10MB3021.namprd10.prod.outlook.com;PTR:;CAT:NONE;SFS:(376002)(346002)(396003)(366004)(39860400002)(136003)(66946007)(6486002)(36756003)(16526019)(186003)(478600001)(6666004)(956004)(1076003)(6916009)(2616005)(8676002)(38100700001)(4326008)(83380400001)(44832011)(316002)(66476007)(66556008)(5660300002)(2906002)(7696005)(52116002)(8936002)(86362001)(26005);DIR:OUT;SFP:1101;
X-MS-Exchange-AntiSpam-MessageData: 
 zrdPEycOCvUJ1M6TgcI+Rfn5vK3odD9tRwiexNUGMr/vg3kcyN6OfCqWuXL2E/Mmhwamad5oWpG2XAQ3WMecWgsNNZyhuUaa7azPDCk0Hx7Vujr4mj89Rc+8HRfFwcD65bXVngxzuPYDcWWTOTNYv1U4dtcpxC5LqDLiTXydj3fPt/ubBMClMF30mRvkXOHb7UPCWa/LonCfbroREBgbyuApJUIjbbXKtTOv/YTzw4LxTbxLVmqR0YzVuI4fjnq7GxJbmLRXt/FDFCxdZ/q8CqR1tIM0jgqAMwcVGhUswHhAl6Y2r5hzUPowauVJ3TKc7Rv9OJxG6bklZY8CNqeyU/3subvGuxnAhBwBm/YqTf9N2Lmvbl7cBFt6T5OHHjKuIT6vWJR2nSrcfJIdQbhu1cxwE5PGxMuzwAcNdoFwlthmX1q1vuH4RKV2+V20wn3szGnTbEd2nOV2Q/VyaBZ3/9vMAXMiRH9HwKE0m5LYnDFhOVwpuU8eZR7qqkagEg8XJquLwIpnEOz51ZCr99OCehtlG6z/F/qI4QrC/ncrdHZY+MCACFB42SKDtz/8RyZlJudTWD+KI3QuoUlKjQAAu34aT6Bkol6b0JJsIbWFRNum642Z2G62OACvrQiq/d0XadI4+3nhHhRDIiMmFjfHb8K2Zqj5JNcp8JJ9POCJy33kmbDlIRP4iYTxjXgH6gBdhIBk9oM6Yjtvx8bncv4wcSjGTuD7TsYOVsWHfF0UtGdANHRrSb4gTMID6aIpxkEYml/Iu1cweTJqwhKXyI2FS7aF4/sWYIVcaUzP/78OsfEcmdSphTzUzSJFtHQit8MmdG0Gpp1Rb+do3OlHvz9ANaKDnvDxc/c3Po57pLO+DnaIBzprHvVUkzrByXKwEKQUxJXAEWDxP9cQ38Ph9Hzdtopqamov/TcdXdnHcrzaqc1qwUET9m2IoCenutZLyfx0tvmGJiGylSu7vmTkGG2F+HraVOvoSdo8eeFu1EFAP+b+KLQNZ/RtEsSyuYgUJ/MeziQ4mFST2YrDmjtTzvh2ZaFTSMuKstRqEnddAOLeJcf1m26L82kh3tl2ckwkHeKLReUMxH+FFIIpNe8aFfyzEFsVZ89ZG98stCr5iNmxzPYm+71STyPMaFZ2LokJOlOZHzJXuyqQR9KHXzmUZFCAo7szob4vatukPs4iowiGBcqVhLubUlU8BT4oqkaYpNmNvMIEnwzDhAedLMm8iKbPJR2Fk2G3GBhlQbSojqd2NFyV+OAG6bMHcePXPYR1jCl1SXDZTg01L8XfeRTwwDSrSMBBMiq8UbGkPawZcWYC5GN5A9HEhH+0cxEdCy9lBufc
X-OriginatorOrg: oracle.com
X-MS-Exchange-CrossTenant-Network-Message-Id: 
 6fe74b40-3715-4ee5-38aa-08d8eef40c54
X-MS-Exchange-CrossTenant-AuthSource: SN6PR10MB3021.namprd10.prod.outlook.com
X-MS-Exchange-CrossTenant-AuthAs: Internal
X-MS-Exchange-CrossTenant-OriginalArrivalTime: 24 Mar 2021 18:38:42.0861
 (UTC)
X-MS-Exchange-CrossTenant-FromEntityHeader: Hosted
X-MS-Exchange-CrossTenant-Id: 4e2c6054-71cb-48f1-bd6c-3a9705aca71b
X-MS-Exchange-CrossTenant-MailboxType: HOSTED
X-MS-Exchange-CrossTenant-UserPrincipalName: 
 E1sItQcec1iiMDgZlSY0Xt4Kb3bkBbIgeIOEZhSVVsi2nDGy2pcN48LlGoszy5XS5Dgl8TvPRH1g9Sm9HCPtkM/zMoblmwItiJ1LsIsAbJQ=
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
X-Proofpoint-Spam-Details: rule=notspam policy=default score=0 adultscore=0
 malwarescore=0 mlxscore=0
 priorityscore=1501 bulkscore=0 impostorscore=0 lowpriorityscore=0
 phishscore=0 mlxlogscore=999 suspectscore=0 clxscore=1015 spamscore=0
 classifier=spam adjust=0 reason=mlx scancount=1 engine=8.12.0-2009150000
 definitions=main-2103240133
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

These #defines will be used by nested.c in the next patch. So move these to
svm.h.

Signed-off-by: Krish Sadhukhan <krish.sadhukhan@oracle.com>
---
 arch/x86/kvm/svm/svm.c | 3 ---
 arch/x86/kvm/svm/svm.h | 3 +++
 2 files changed, 3 insertions(+), 3 deletions(-)

```
#### [kvm-unit-tests PATCH] arm: pmu: Fix failing PMU test when no PMU is available
##### From: Marc Zyngier <maz@kernel.org>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Marc Zyngier <maz@kernel.org>
X-Patchwork-Id: 12161309
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No,
 score=-17.0 required=3.0 tests=BAYES_00,INCLUDES_CR_TRAILER,
	INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT
	autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 82DE3C433DB
	for <kvm@archiver.kernel.org>; Wed, 24 Mar 2021 14:39:46 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 5A66961A07
	for <kvm@archiver.kernel.org>; Wed, 24 Mar 2021 14:39:46 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S236277AbhCXOjO (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Wed, 24 Mar 2021 10:39:14 -0400
Received: from mail.kernel.org ([198.145.29.99]:40956 "EHLO mail.kernel.org"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S236251AbhCXOjD (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 24 Mar 2021 10:39:03 -0400
Received: from disco-boy.misterjones.org (disco-boy.misterjones.org
 [51.254.78.96])
        (using TLSv1.2 with cipher ECDHE-RSA-AES256-GCM-SHA384 (256/256 bits))
        (No client certificate requested)
        by mail.kernel.org (Postfix) with ESMTPSA id E825E61A02;
        Wed, 24 Mar 2021 14:39:02 +0000 (UTC)
Received: from 78.163-31-62.static.virginmediabusiness.co.uk ([62.31.163.78]
 helo=hot-poop.lan)
        by disco-boy.misterjones.org with esmtpsa  (TLS1.3) tls
 TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384
        (Exim 4.94)
        (envelope-from <maz@kernel.org>)
        id 1lP4ey-003XVd-Sy; Wed, 24 Mar 2021 14:39:01 +0000
From: Marc Zyngier <maz@kernel.org>
To: kvm@vger.kernel.org, kvmarm@lists.cs.columbia.edu
Cc: Paolo Bonzini <pbonzini@redhat.com>,
        Andrew Jones <drjones@redhat.com>,
        Eric Auger <eric.auger@redhat.com>,
        Alexandru Elisei <alexandru.elisei@arm.com>,
        qperret@google.com, kernel-team@android.com,
        Andrew Walbran <qwandor@google.com>
Subject: [kvm-unit-tests PATCH] arm: pmu: Fix failing PMU test when no PMU is
 available
Date: Wed, 24 Mar 2021 14:38:56 +0000
Message-Id: <20210324143856.2079220-1-maz@kernel.org>
X-Mailer: git-send-email 2.30.0
MIME-Version: 1.0
X-SA-Exim-Connect-IP: 62.31.163.78
X-SA-Exim-Rcpt-To: kvm@vger.kernel.org, kvmarm@lists.cs.columbia.edu,
 pbonzini@redhat.com, drjones@redhat.com, eric.auger@redhat.com,
 alexandru.elisei@arm.com, qperret@google.com, kernel-team@android.com,
 qwandor@google.com
X-SA-Exim-Mail-From: maz@kernel.org
X-SA-Exim-Scanned: No (on disco-boy.misterjones.org);
 SAEximRunCond expanded to false
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The PMU unit tests fail with an UNDEF exception when no PMU
is available (although KVM hasn't been totally consistent
with that in the past).

This is caused by PMCR_EL0 being read *before* ID_AA64DFR0_EL1
is checked for the PMU version.

Move the PMCR_EL0 access to a reasonable place, which allows the
test to soft-fail gracefully.

Fixes: 784ee933fa5f ("arm: pmu: Introduce defines for PMU versions")
Reported-by: Andrew Walbran <qwandor@google.com>
Signed-off-by: Marc Zyngier <maz@kernel.org>
---
 arm/pmu.c | 3 ++-
 1 file changed, 2 insertions(+), 1 deletion(-)

```
#### [RESEND] [PATCH] use pr_warn_ratelimited() for vq_err()
##### From: John Levon <john.levon@nutanix.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: John Levon <john.levon@nutanix.com>
X-Patchwork-Id: 12160843
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.8 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED,USER_AGENT_GIT
	autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 0BB35C433DB
	for <kvm@archiver.kernel.org>; Wed, 24 Mar 2021 12:02:47 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id C229C619FC
	for <kvm@archiver.kernel.org>; Wed, 24 Mar 2021 12:02:46 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S232107AbhCXMCP (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Wed, 24 Mar 2021 08:02:15 -0400
Received: from 88-98-93-30.dsl.in-addr.zen.co.uk ([88.98.93.30]:44218 "EHLO
        sent" rhost-flags-OK-FAIL-OK-FAIL) by vger.kernel.org with ESMTP
        id S231960AbhCXMB6 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 24 Mar 2021 08:01:58 -0400
Received: from jlevon by sent with local (Exim 4.93)
        (envelope-from <john.levon@nutanix.com>)
        id 1lP2Cv-004d0V-4d; Wed, 24 Mar 2021 12:01:53 +0000
From: John Levon <john.levon@nutanix.com>
To: john.levon@nutanix.com
Cc: jasowang@redhat.com, kvm@vger.kernel.org, levon@movementarian.org,
        mst@redhat.com, virtualization@lists.linux-foundation.org,
        David Edmondson <david.edmondson@oracle.com>
Subject: [RESEND] [PATCH] use pr_warn_ratelimited() for vq_err()
Date: Wed, 24 Mar 2021 12:01:29 +0000
Message-Id: <20210324120129.1103172-1-john.levon@nutanix.com>
X-Mailer: git-send-email 2.25.1
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

vq_err() is used to report various failure states in vhost code, but by
default uses pr_debug(), and as a result doesn't record anything unless
enabled via dynamic debug. We'll change this so we get something recorded
in the log in these failure cases. Guest VMs (and userspace) can trigger
some of these messages, so we want to use the pr_warn_ratelimited()
variant. However, on DEBUG kernels, we'd like to get everything, so we use
pr_warn() then.

Signed-off-by: John Levon <john.levon@nutanix.com>
Reviewed-by: David Edmondson <david.edmondson@oracle.com>
---
 drivers/vhost/vhost.h | 14 ++++++++++----
 1 file changed, 10 insertions(+), 4 deletions(-)

```
