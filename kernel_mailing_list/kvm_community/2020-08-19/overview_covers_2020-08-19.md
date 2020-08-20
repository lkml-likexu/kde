

#### [PATCH v10 0/9] KVM: Add virtualization support of split lock
##### From: Xiaoyao Li <xiaoyao.li@intel.com>

```c
From patchwork Wed Aug 19 06:46:58 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Xiaoyao Li <xiaoyao.li@intel.com>
X-Patchwork-Id: 11722629
Return-Path: <SRS0=Yqqy=B5=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id A85AE913
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 19 Aug 2020 06:47:17 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 9A61D2063A
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 19 Aug 2020 06:47:17 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726971AbgHSGrQ (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 19 Aug 2020 02:47:16 -0400
Received: from mga02.intel.com ([134.134.136.20]:36074 "EHLO mga02.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726858AbgHSGrN (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 19 Aug 2020 02:47:13 -0400
IronPort-SDR: 
 0kSZqH/6hMfKVukG6QBU+89wFGahWNJTPnN+2lhKGureZ5B9+9auAHeafK4v6bSVfOeX7MDbAv
 Su/kqQiV2YSg==
X-IronPort-AV: E=McAfee;i="6000,8403,9717"; a="142873154"
X-IronPort-AV: E=Sophos;i="5.76,330,1592895600";
   d="scan'208";a="142873154"
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from orsmga002.jf.intel.com ([10.7.209.21])
  by orsmga101.jf.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 18 Aug 2020 23:47:12 -0700
IronPort-SDR: 
 DALWZK1vz4iWx0uSD7Bzuv9+EeAMOBmBT6Y4cSh1vRKwOQt1tcPfGcKBf8R4cZQBddE5tpgJ63
 NRBznJtgsoPQ==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.76,330,1592895600";
   d="scan'208";a="310679238"
Received: from lxy-dell.sh.intel.com ([10.239.159.21])
  by orsmga002.jf.intel.com with ESMTP; 18 Aug 2020 23:47:09 -0700
From: Xiaoyao Li <xiaoyao.li@intel.com>
To: Thomas Gleixner <tglx@linutronix.de>,
        Paolo Bonzini <pbonzini@redhat.com>,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        kvm@vger.kernel.org
Cc: linux-kernel@vger.kernel.org, x86@kernel.org,
        Ingo Molnar <mingo@redhat.com>, Borislav Petkov <bp@alien8.de>,
        Andy Lutomirski <luto@kernel.org>, peterz@infradead.org,
        Arvind Sankar <nivedita@alum.mit.edu>,
        Tony Luck <tony.luck@intel.com>,
        Fenghua Yu <fenghua.yu@intel.com>,
        Xiaoyao Li <xiaoyao.li@intel.com>
Subject: [PATCH v10 0/9] KVM: Add virtualization support of split lock
 detection
Date: Wed, 19 Aug 2020 14:46:58 +0800
Message-Id: <20200819064707.1033569-1-xiaoyao.li@intel.com>
X-Mailer: git-send-email 2.18.4
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Hi maintainers,

Please help review this new version and give comments. There is only one
minor change from previous v9, i.e., adding patch 8.
---

This series aims to add the virtualization of split lock detection in
KVM.

Due to the fact that split lock detection is tightly coupled with CPU
model and CPU model is configurable by host VMM, we elect to use
paravirt method to expose and enumerate it for guest.

Changes in v10
 - rebase to v5.9-rc1;
 - Add one patch to move the initialization of cpu_model_supports_sld to
   split_lock_setup();

Changes in v9
https://lkml.kernel.org/r/20200509110542.8159-1-xiaoyao.li@intel.com
 - rebase to v5.7-rc4
 - Add one patch to rename TIF_SLD to TIF_SLD_DISABLED;
 - Add one patch to remove bogus case in handle_guest_split_lock;
 - Introduce flag X86_FEATURE_SPLIT_LOCK_DETECT_FATAL and thus drop
   sld_state;
 - Use X86_FEATURE_SPLIT_LOCK_DETECT and X86_FEATURE_SPLIT_LOCK_DETECT_FATAL
   to determine the SLD state of host;
 - Introduce split_lock_virt_switch() and two wrappers for KVM instead
   of sld_update_to(); 
 - Use paravirt to expose and enumerate split lock detection for guest;
 - Split lock detection can be exposed to guest when host is sld_fatal,
   even though host is SMT available. 

Changes in v8:
https://lkml.kernel.org/r/20200414063129.133630-1-xiaoyao.li@intel.com
 - rebase to v5.7-rc1.
 - basic enabling of split lock detection already merged.
 - When host is sld_warn and nosmt, load guest's sld bit when in KVM
   context, i.e., between vmx_prepare_switch_to_guest() and before
   vmx_prepare_switch_to_host(), KVM uses guest sld setting.  

Changes in v7:
https://lkml.kernel.org/r/20200325030924.132881-1-xiaoyao.li@intel.com
 - only pick patch 1 and patch 2, and hold all the left.
 - Update SLD bit on each processor based on sld_state.

Changes in v6:
https://lkml.kernel.org/r/20200324151859.31068-1-xiaoyao.li@intel.com
 - Drop the sld_not_exist flag and use X86_FEATURE_SPLIT_LOCK_DETECT to
   check whether need to init split lock detection. [tglx]
 - Use tglx's method to verify the existence of split lock detectoin.
 - small optimization of sld_update_msr() that the default value of
   msr_test_ctrl_cache has split_lock_detect bit cleared.
 - Drop the patch3 in v5 that introducing kvm_only option. [tglx]
 - Rebase patch4-8 to kvm/queue.
 - use the new kvm-cpu-cap to expose X86_FEATURE_CORE_CAPABILITIES in
   Patch 6.

Changes in v5:
https://lkml.kernel.org/r/20200315050517.127446-1-xiaoyao.li@intel.com
 - Use X86_FEATURE_SPLIT_LOCK_DETECT flag in kvm to ensure split lock
   detection is really supported.
 - Add and export sld related helper functions in their related usecase 
   kvm patches.

Xiaoyao Li (9):
  x86/split_lock: Rename TIF_SLD to TIF_SLD_DISABLED
  x86/split_lock: Remove bogus case in handle_guest_split_lock()
  x86/split_lock: Introduce flag X86_FEATURE_SLD_FATAL and drop
    sld_state
  x86/split_lock: Introduce split_lock_virt_switch() and two wrappers
  x86/kvm: Introduce paravirt split lock detection enumeration
  KVM: VMX: Enable MSR TEST_CTRL for guest
  KVM: VMX: virtualize split lock detection
  x86/split_lock: Set cpu_model_supports_sld to true after the existence
    of split lock detection is verified BSP
  x86/split_lock: Enable split lock detection initialization when
    running as a guest on KVM

 Documentation/virt/kvm/cpuid.rst     | 29 +++++++----
 arch/x86/include/asm/cpu.h           | 36 ++++++++++++++
 arch/x86/include/asm/cpufeatures.h   |  1 +
 arch/x86/include/asm/thread_info.h   |  6 +--
 arch/x86/include/uapi/asm/kvm_para.h |  8 ++--
 arch/x86/kernel/cpu/intel.c          | 61 +++++++++++++++--------
 arch/x86/kernel/kvm.c                |  3 ++
 arch/x86/kernel/process.c            |  2 +-
 arch/x86/kvm/cpuid.c                 |  6 +++
 arch/x86/kvm/vmx/vmx.c               | 72 +++++++++++++++++++++++++---
 arch/x86/kvm/vmx/vmx.h               |  3 ++
 arch/x86/kvm/x86.c                   |  6 ++-
 arch/x86/kvm/x86.h                   | 16 +++++++
 13 files changed, 207 insertions(+), 42 deletions(-)
```
#### [Patch v2 0/4] Defer page pinning for SEV guests until guest pages
##### From: eric van tassell <Eric.VanTassell@amd.com>

```c
From patchwork Wed Aug 19 15:17:38 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: eric van tassell <Eric.VanTassell@amd.com>
X-Patchwork-Id: 11724407
Return-Path: <SRS0=Yqqy=B5=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id D11771575
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 19 Aug 2020 15:17:07 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id B2DBF20885
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 19 Aug 2020 15:17:07 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=amdcloud.onmicrosoft.com
 header.i=@amdcloud.onmicrosoft.com header.b="m/ZSuiRA"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728572AbgHSPRG (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 19 Aug 2020 11:17:06 -0400
Received: from mail-bn7nam10on2044.outbound.protection.outlook.com
 ([40.107.92.44]:48186
        "EHLO NAM10-BN7-obe.outbound.protection.outlook.com"
        rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org with ESMTP
        id S1728446AbgHSPRB (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 19 Aug 2020 11:17:01 -0400
ARC-Seal: i=1; a=rsa-sha256; s=arcselector9901; d=microsoft.com; cv=none;
 b=RaMGN2BFVY1sqUMLpMYpOOsMQPuRMI2/MKxKwMj+lNXIFZ6IEh/j1UvMmITCiPFGTeGFREpOgX7xyNXyWlXpBkiANYPWGblzSof8WZqoH9crzKPxu1X0L18AKEYHeSpeS7tNLMYBqPjSJ7591nZdttGEeTtMPJaTT5Z5fUe1E4Ban0NeEvpBcBRlxfukZ5fJV8Ir3UAdR7bd0visQtA7Xoezupk2zUWRg1C52YTfPvqYVAGbolyRvJaja1yLVAl70nuSa5akokbG0QjqjSu+BuLyCSk84zin+1M1RrXyZnUOwAVimfzcC/aPkIOu1HCfe04scrqW1O20QtZbTTUTvw==
ARC-Message-Signature: i=1; a=rsa-sha256; c=relaxed/relaxed; d=microsoft.com;
 s=arcselector9901;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=KaBwUVdU7124MaD/VHK1/mH0hgRrU5eEtfB/WJUuFHc=;
 b=hmxiex7//xOr1IvbL5fUTv71RqALp/9TsQ/D5JZOBD5Afhtt+ryM5dD1AUznBtAYRXpu1W1T30MrK0yFAHhtiMCPNXN1nbf2i1VOcFg2pMV8w7YZZnVGcMjqahIqAT98yXFJ45AXoto7NGzQ42/buf/oG+PjQvvQE1el/mong5jtnk5EteG1H9kUlvK7uUdhMsANWNknxE+fJJ4U+JI6UEH01fe8O/8uEVygLBr1Y5BHQzsNO2Zy0MgXdsEo+0m4a3ITmtLsGOnRVinbOhzD1ZdE/fL0BZWAua1cfMRuEwiksyQD13Ib508FqsHsLf8OSoRY77FbhAzb/jU+Cpw+sQ==
ARC-Authentication-Results: i=1; mx.microsoft.com 1; spf=pass
 smtp.mailfrom=amd.com; dmarc=pass action=none header.from=amd.com; dkim=pass
 header.d=amd.com; arc=none
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
 d=amdcloud.onmicrosoft.com; s=selector2-amdcloud-onmicrosoft-com;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=KaBwUVdU7124MaD/VHK1/mH0hgRrU5eEtfB/WJUuFHc=;
 b=m/ZSuiRACzEUwrPhyiQRX5eWLbKqOOKSdfZ0NZCPErsA9nq5YCKxoDSqhnhfSeJ+mG5ysDzP7056oA879JahnC1xdu+9CQPXD2Gb8DPwCbYaOIrUoAeUcREzZBGI05+aDCJL+/Qy5NapR+PEDldpSw1i0iAsd2T9jqNFZhCSaFc=
Authentication-Results: vger.kernel.org; dkim=none (message not signed)
 header.d=none;vger.kernel.org; dmarc=none action=none header.from=amd.com;
Received: from DM5PR12MB1307.namprd12.prod.outlook.com (2603:10b6:3:79::21) by
 DM6PR12MB3227.namprd12.prod.outlook.com (2603:10b6:5:18d::14) with Microsoft
 SMTP Server (version=TLS1_2, cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id
 15.20.3305.24; Wed, 19 Aug 2020 15:16:56 +0000
Received: from DM5PR12MB1307.namprd12.prod.outlook.com
 ([fe80::15d7:c2da:d92a:2162]) by DM5PR12MB1307.namprd12.prod.outlook.com
 ([fe80::15d7:c2da:d92a:2162%11]) with mapi id 15.20.3283.028; Wed, 19 Aug
 2020 15:16:56 +0000
From: eric van tassell <Eric.VanTassell@amd.com>
To: kvm@vger.kernel.org
Cc: linux-kernel@vger.kernel.org, bp@alien8.de, hpa@zytor.com,
        mingo@redhat.com, jmattson@google.com, joro@8bytes.org,
        pbonzini@redhat.com, sean.j.christopherson@intel.com,
        tglx@linutronix.de, vkuznets@redhat.com, wanpengli@tencent.com,
        x86@kernel.org, rientjes@google.com, junaids@google.com,
        evantass@amd.com
Subject: [Patch v2 0/4] Defer page pinning for SEV guests until guest pages
 touched
Date: Wed, 19 Aug 2020 10:17:38 -0500
Message-Id: <20200819151742.7892-1-Eric.VanTassell@amd.com>
X-Mailer: git-send-email 2.17.1
X-ClientProxiedBy: DM5PR19CA0045.namprd19.prod.outlook.com
 (2603:10b6:3:9a::31) To DM5PR12MB1307.namprd12.prod.outlook.com
 (2603:10b6:3:79::21)
MIME-Version: 1.0
X-MS-Exchange-MessageSentRepresentingType: 1
Received: from evt-speedway-83bc.amd.com (165.204.78.2) by
 DM5PR19CA0045.namprd19.prod.outlook.com (2603:10b6:3:9a::31) with Microsoft
 SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.3305.24 via Frontend
 Transport; Wed, 19 Aug 2020 15:16:55 +0000
X-Mailer: git-send-email 2.17.1
X-Originating-IP: [165.204.78.2]
X-MS-PublicTrafficType: Email
X-MS-Office365-Filtering-HT: Tenant
X-MS-Office365-Filtering-Correlation-Id: 2713e4a5-dca6-4693-e030-08d84452e929
X-MS-TrafficTypeDiagnostic: DM6PR12MB3227:
X-MS-Exchange-Transport-Forked: True
X-Microsoft-Antispam-PRVS: 
 <DM6PR12MB3227D1D7E32342BD8CB6B644E75D0@DM6PR12MB3227.namprd12.prod.outlook.com>
X-MS-Oob-TLC-OOBClassifiers: OLM:2201;
X-MS-Exchange-SenderADCheck: 1
X-Microsoft-Antispam: BCL:0;
X-Microsoft-Antispam-Message-Info: 
 7ai97bf3FBBu3ri67OmUy/cdg5X5fTaGlLi016T+mDCKseA59wgCuZ7x5Vbn8cpi8+RAkVqObf8zfdptnEgiZoCXHzea0v/jTtGu2YsDv3/S3tsOtlSbiKN9EmP0VeZRzigQUnQEd7lLaK0uX+P/CWrtSpdyOvE5g1eBkDqEFtyCqChEGdcv7WTAfH9cTT/etam3Dill0QlXJcq1qf8bNGyzZYMoqDbxEF1UQQB0NOepVXB+6h+EckGFmgQjwWcu6kDfrQ+qXgvHzYuWiDIPmLx5yt4un9B04TuJmIyaqdRGZVGSEg2trwvAm3h5H+/iRla3p2LAtiZz7pUaJyYnVw==
X-Forefront-Antispam-Report: 
 CIP:255.255.255.255;CTRY:;LANG:en;SCL:1;SRV:;IPV:NLI;SFV:NSPM;H:DM5PR12MB1307.namprd12.prod.outlook.com;PTR:;CAT:NONE;SFS:(4636009)(346002)(376002)(136003)(396003)(366004)(39860400002)(66556008)(66476007)(8676002)(66946007)(26005)(86362001)(1076003)(5660300002)(478600001)(6486002)(36756003)(316002)(83380400001)(6666004)(7416002)(2906002)(8936002)(6916009)(4326008)(2616005)(7696005)(16526019)(52116002)(186003)(956004);DIR:OUT;SFP:1101;
X-MS-Exchange-AntiSpam-MessageData: 
 Kk+cJ4CKqf536MX6HlQEVwzkHUVgTcUycFx0FDEFUk5yRSfeyAjv7rv4mftbTEJcU7/wphbOKhdW3e/X7m5HH/9FnNWjpSoMIhrYA/n3FsVMYCVs9/a6VYD/QxnOpcAgt1A0pzJh/WxsIPTlDQZrLrxiRJTzeaCKeB64dalXAH1/1pM3zdHgzRh8X8u8QiPRSJbMknfmH0OT9ATE7NG9HppbbjAvOweeYg4ihZTVJJ/qmed5Vc5d1BYoSgwviZQ9+Pn0l7TkZK8u6/fWidD3H7IEb0tJj7pxX16DIOObb/5URd6lpFD8wr7ATX/2tDxfrPgjS4mZZaFGGUJ+ZUb8AmEt8bIgl1GJywUqlYRgJaYVqS2c01uDlmkRzY7zYKsn7t7xwNx0ItZxlqJ33iuyeuXaGb3m+wTMJ2JU46v+/wz+hTyFP8wPCerxBO/5cgozj0wkFC6v9SvNpngOw3MFhfYLR87jU4lRCYqXxkzi7cz2Zl85XzYnsiL7Vw9dqoBEnpb5BbGtfWqIrDJjlstR4yr5rcCdlH9FywUgOZghBOdYirkLa2xs6VmfS4tA6KGVm4XceN5W0N7rrN89woSSMMMYl4o6So7GI/8ToUgwf4frg+XUkjsPpTGJhfKeNKo+0n5Bm2iYXZXdqzUYrQTGVA==
X-OriginatorOrg: amd.com
X-MS-Exchange-CrossTenant-Network-Message-Id: 
 2713e4a5-dca6-4693-e030-08d84452e929
X-MS-Exchange-CrossTenant-AuthSource: DM5PR12MB1307.namprd12.prod.outlook.com
X-MS-Exchange-CrossTenant-AuthAs: Internal
X-MS-Exchange-CrossTenant-OriginalArrivalTime: 19 Aug 2020 15:16:56.5056
 (UTC)
X-MS-Exchange-CrossTenant-FromEntityHeader: Hosted
X-MS-Exchange-CrossTenant-Id: 3dd8961f-e488-4e60-8e11-a82d994e183d
X-MS-Exchange-CrossTenant-MailboxType: HOSTED
X-MS-Exchange-CrossTenant-UserPrincipalName: 
 yseAXuQq4HyJDqE98IaSFKSjBcs5gK7jSMYcGFb6/zHrX66qVTNayqkply1qEhYC+FxaObN5NHVrOfB8AMQj0w==
X-MS-Exchange-Transport-CrossTenantHeadersStamped: DM6PR12MB3227
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Overview
========
	Defer pinning of the guest's pages until nested page faults occur
	to improve startup time and reduce memory pressure for SEV guests.

	Cease paying the computational cost of pinning all pages when an
	encrypted region is registered, before it is known if they will be accessed.

	Cease creating the memory pressure due to  pinning all pages when an
	encrypted region is registered before, it is known if they will be accessed.

Timing Results
==========
All timings are done by hand with and Android stopwatch app

SEV guest size(GiB)  	     |  4 |  8 | 16 | 32 | 60 |
without patch series(sec)    |  2 |  3 |  4 |  8 | 14 |
with patch series (sec)      |  1 |  1 |  1 |  1 |  1 |

Patch Series Changelog
==============
	1 -> 2:
		* mmio checks move from sev_pin_page() to caller and the
		  set_spte_notify* symbols are renamed to pin_page().

		* sev_get_page() warns on failures which should not happen.
		
		* kvm->srcu is used to avoid any possibility of a race in
		  sev_launch_update_data()
Applies To:
===========
	This patch applies top of this commit from the <next> branch of
	the kvm tree:
	    c34b26b98cac   Tianjia Zhang : KVM: MIPS: clean up redundant 'kvm_run' parameters

eric van tassell (4):
  KVM:MMU: Introduce the pin_page() callback
  KVM:SVM: Implement pin_page support
  KVM:SVM: Pin sev_launch_update_data() pages via sev_get_page()
  KVM:SVM: Remove struct enc_region and associated pinned page tracking.

 arch/x86/include/asm/kvm_host.h |   3 +
 arch/x86/kvm/mmu/mmu.c          |  30 +++-
 arch/x86/kvm/mmu/paging_tmpl.h  |  27 ++--
 arch/x86/kvm/svm/sev.c          | 238 +++++++++++++++++---------------
 arch/x86/kvm/svm/svm.c          |   2 +
 arch/x86/kvm/svm/svm.h          |   4 +-
 6 files changed, 174 insertions(+), 130 deletions(-)
```
#### [PATCH v9 0/2] s390: virtio: let arch validate VIRTIO features
##### From: Pierre Morel <pmorel@linux.ibm.com>

```c
From patchwork Wed Aug 19 16:23:16 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Pierre Morel <pmorel@linux.ibm.com>
X-Patchwork-Id: 11724587
Return-Path: <SRS0=Yqqy=B5=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id A326D138C
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 19 Aug 2020 16:23:39 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 8ABF720882
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 19 Aug 2020 16:23:39 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=ibm.com header.i=@ibm.com
 header.b="bZSlKJ1k"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726858AbgHSQXf (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 19 Aug 2020 12:23:35 -0400
Received: from mx0a-001b2d01.pphosted.com ([148.163.156.1]:43236 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1725275AbgHSQXe (ORCPT
        <rfc822;kvm@vger.kernel.org>); Wed, 19 Aug 2020 12:23:34 -0400
Received: from pps.filterd (m0098393.ppops.net [127.0.0.1])
        by mx0a-001b2d01.pphosted.com (8.16.0.42/8.16.0.42) with SMTP id
 07JG3O8D054851;
        Wed, 19 Aug 2020 12:23:27 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=ibm.com;
 h=from : to : cc : subject
 : date : message-id; s=pp1;
 bh=uu1KxyVc4kHFi1gkZn4wAfBW3iiu2CMXNeV7oFLjvfs=;
 b=bZSlKJ1kFW8HKwqlHAJBbQgIcEjCElwmEjtpwguNFyrHo3ZLLF0CQcf0EUnDLjFUGBP3
 dVk97udHXG/OqxGbouKupRxWpmn2rdlo/F8kr246fBH8MmwEoIt/ZipI3DOq3AGI3DHR
 kOw+npFgyCw7j9BOUSiotmCelbiQgS9xCQjP/twKDjdE4p7IYT8lgev7wFYn9ZxyxaEr
 VGRL6cyvW0ors62iqW2pz0zPrYbEco/Y7XRUF0RlbgXRfT4Kgd6cZ37WoK5J9orhCDkG
 B+kGvhmpmWHn+80D1AtWt00w8dKb4vh7JyidXzS8osHpusX036CvMIIosFNKvhecobfF MQ==
Received: from pps.reinject (localhost [127.0.0.1])
        by mx0a-001b2d01.pphosted.com with ESMTP id 3313kxrvqb-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Wed, 19 Aug 2020 12:23:27 -0400
Received: from m0098393.ppops.net (m0098393.ppops.net [127.0.0.1])
        by pps.reinject (8.16.0.36/8.16.0.36) with SMTP id 07JG3l9T057245;
        Wed, 19 Aug 2020 12:23:26 -0400
Received: from ppma06ams.nl.ibm.com (66.31.33a9.ip4.static.sl-reverse.com
 [169.51.49.102])
        by mx0a-001b2d01.pphosted.com with ESMTP id 3313kxrvp1-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Wed, 19 Aug 2020 12:23:26 -0400
Received: from pps.filterd (ppma06ams.nl.ibm.com [127.0.0.1])
        by ppma06ams.nl.ibm.com (8.16.0.42/8.16.0.42) with SMTP id
 07JGMOd3003321;
        Wed, 19 Aug 2020 16:23:23 GMT
Received: from b06cxnps3075.portsmouth.uk.ibm.com
 (d06relay10.portsmouth.uk.ibm.com [9.149.109.195])
        by ppma06ams.nl.ibm.com with ESMTP id 330tbvrt3y-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Wed, 19 Aug 2020 16:23:23 +0000
Received: from d06av21.portsmouth.uk.ibm.com (d06av21.portsmouth.uk.ibm.com
 [9.149.105.232])
        by b06cxnps3075.portsmouth.uk.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id 07JGNKYJ29688272
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Wed, 19 Aug 2020 16:23:20 GMT
Received: from d06av21.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 6A57D5204F;
        Wed, 19 Aug 2020 16:23:20 +0000 (GMT)
Received: from oc3016276355.ibm.com (unknown [9.145.33.131])
        by d06av21.portsmouth.uk.ibm.com (Postfix) with ESMTP id D6EED52051;
        Wed, 19 Aug 2020 16:23:19 +0000 (GMT)
From: Pierre Morel <pmorel@linux.ibm.com>
To: linux-kernel@vger.kernel.org
Cc: pasic@linux.ibm.com, borntraeger@de.ibm.com, frankja@linux.ibm.com,
        mst@redhat.com, jasowang@redhat.com, cohuck@redhat.com,
        kvm@vger.kernel.org, linux-s390@vger.kernel.org,
        virtualization@lists.linux-foundation.org, thomas.lendacky@amd.com,
        david@gibson.dropbear.id.au, linuxram@us.ibm.com,
        hca@linux.ibm.com, gor@linux.ibm.com
Subject: [PATCH v9 0/2] s390: virtio: let arch validate VIRTIO features
Date: Wed, 19 Aug 2020 18:23:16 +0200
Message-Id: <1597854198-2871-1-git-send-email-pmorel@linux.ibm.com>
X-Mailer: git-send-email 1.8.3.1
X-TM-AS-GCONF: 00
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.235,18.0.687
 definitions=2020-08-19_09:2020-08-19,2020-08-19 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 spamscore=0
 priorityscore=1501 impostorscore=0 adultscore=0 bulkscore=0 clxscore=1015
 mlxlogscore=956 malwarescore=0 suspectscore=1 phishscore=0 mlxscore=0
 lowpriorityscore=0 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.12.0-2006250000 definitions=main-2008190133
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Hi all,

The goal of the series is to give a chance to the architecture
to validate VIRTIO device features.

in this respin:

The tests are back to virtio_finalize_features.

No more argument for the architecture callback which only reports
if the architecture needs guest memory access restrictions for
VIRTIO.


I renamed the callback to arch_has_restricted_virtio_memory_access,
and the config option to ARCH_HAS_RESTRICTED_VIRTIO_MEMORY_ACCESS.

Regards,
Pierre

Pierre Morel (2):
  virtio: let arch advertise guest's memory access restrictions
  s390: virtio: PV needs VIRTIO I/O device protection

 arch/s390/Kconfig             |  1 +
 arch/s390/mm/init.c           | 11 +++++++++++
 drivers/virtio/Kconfig        |  6 ++++++
 drivers/virtio/virtio.c       | 15 +++++++++++++++
 include/linux/virtio_config.h |  9 +++++++++
 5 files changed, 42 insertions(+)
```
