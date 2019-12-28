#### [PATCH v9 2/7] KVM: VMX: Define CET VMCS fields and #CP flag
##### From: Yang Weijiang <weijiang.yang@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Yang Weijiang <weijiang.yang@intel.com>
X-Patchwork-Id: 11310813
Return-Path: <SRS0=HBlZ=2R=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 4440F6C1
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 27 Dec 2019 02:07:45 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 2BEBA20CC7
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 27 Dec 2019 02:07:45 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727134AbfL0CH3 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 26 Dec 2019 21:07:29 -0500
Received: from mga17.intel.com ([192.55.52.151]:38918 "EHLO mga17.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726115AbfL0CH3 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 26 Dec 2019 21:07:29 -0500
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from fmsmga001.fm.intel.com ([10.253.24.23])
  by fmsmga107.fm.intel.com with ESMTP/TLS/DHE-RSA-AES256-GCM-SHA384;
 26 Dec 2019 18:07:29 -0800
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.69,361,1571727600";
   d="scan'208";a="223675027"
Received: from unknown (HELO local-michael-cet-test.sh.intel.com)
 ([10.239.159.128])
  by fmsmga001.fm.intel.com with ESMTP; 26 Dec 2019 18:07:27 -0800
From: Yang Weijiang <weijiang.yang@intel.com>
To: kvm@vger.kernel.org, linux-kernel@vger.kernel.org,
        pbonzini@redhat.com, jmattson@google.com,
        sean.j.christopherson@intel.com
Cc: yu.c.zhang@linux.intel.com, Yang Weijiang <weijiang.yang@intel.com>
Subject: [PATCH v9 2/7] KVM: VMX: Define CET VMCS fields and #CP flag
Date: Fri, 27 Dec 2019 10:11:28 +0800
Message-Id: <20191227021133.11993-3-weijiang.yang@intel.com>
X-Mailer: git-send-email 2.17.2
In-Reply-To: <20191227021133.11993-1-weijiang.yang@intel.com>
References: <20191227021133.11993-1-weijiang.yang@intel.com>
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

CET(Control-flow Enforcement Technology) is an upcoming Intel(R)
processor feature that blocks Return/Jump-Oriented Programming(ROP)
attacks. It provides the following capabilities to defend
against ROP/JOP style control-flow subversion attacks:

Shadow Stack (SHSTK):
  A second stack for program which is used exclusively for
  control transfer operations.

Indirect Branch Tracking (IBT):
  Code branching protection to defend against jump/call oriented
  programming.

Several new CET MSRs are defined in kernel to support CET:
  MSR_IA32_{U,S}_CET: Controls the CET settings for user
                      mode and suervisor mode respectively.

  MSR_IA32_PL{0,1,2,3}_SSP: Stores shadow stack pointers for
                            CPL-0,1,2,3 level respectively.

  MSR_IA32_INT_SSP_TAB: Stores base address of shadow stack
                        pointer table.

Two XSAVES state bits are introduced for CET:
  IA32_XSS:[bit 11]: For saving/restoring user mode CET states
  IA32_XSS:[bit 12]: For saving/restoring supervisor mode CET states.

Six VMCS fields are introduced for CET:
  {HOST,GUEST}_S_CET: Stores CET settings for supervisor mode.
  {HOST,GUEST}_SSP: Stores shadow stack pointer for supervisor mode.
  {HOST,GUEST}_INTR_SSP_TABLE: Stores base address of shadow stack pointer
                               table.

If VM_EXIT_LOAD_HOST_CET_STATE = 1, the host's CET MSRs are restored
from below VMCS fields at VM-Exit:
  HOST_S_CET
  HOST_SSP
  HOST_INTR_SSP_TABLE

If VM_ENTRY_LOAD_GUEST_CET_STATE = 1, the guest's CET MSRs are loaded
from below VMCS fields at VM-Entry:
  GUEST_S_CET
  GUEST_SSP
  GUEST_INTR_SSP_TABLE

Co-developed-by: Zhang Yi Z <yi.z.zhang@linux.intel.com>
Signed-off-by: Zhang Yi Z <yi.z.zhang@linux.intel.com>
Signed-off-by: Yang Weijiang <weijiang.yang@intel.com>
---
 arch/x86/include/asm/vmx.h      | 8 ++++++++
 arch/x86/include/uapi/asm/kvm.h | 1 +
 arch/x86/kvm/x86.c              | 1 +
 arch/x86/kvm/x86.h              | 5 +++--
 4 files changed, 13 insertions(+), 2 deletions(-)

```
#### [kvm-unit-tests PATCH] devicetree: Fix the dt_for_each_cpu_node
##### From: Zeng Tao <prime.zeng@hisilicon.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Zeng Tao <prime.zeng@hisilicon.com>
X-Patchwork-Id: 11311125
Return-Path: <SRS0=HBlZ=2R=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 3CA386C1
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 27 Dec 2019 11:03:49 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 2493620CC7
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 27 Dec 2019 11:03:49 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726538AbfL0LDs (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 27 Dec 2019 06:03:48 -0500
Received: from szxga04-in.huawei.com ([45.249.212.190]:8631 "EHLO huawei.com"
        rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org with ESMTP
        id S1726053AbfL0LDs (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 27 Dec 2019 06:03:48 -0500
Received: from DGGEMS403-HUB.china.huawei.com (unknown [172.30.72.60])
        by Forcepoint Email with ESMTP id 515ADEBF5F34B339D376;
        Fri, 27 Dec 2019 19:03:45 +0800 (CST)
Received: from localhost.localdomain (10.69.192.56) by
 DGGEMS403-HUB.china.huawei.com (10.3.19.203) with Microsoft SMTP Server id
 14.3.439.0; Fri, 27 Dec 2019 19:03:37 +0800
From: Zeng Tao <prime.zeng@hisilicon.com>
To: <pbonzini@redhat.com>, <drjones@redhat.com>
CC: <kvm@vger.kernel.org>, <xuwei5@huawei.com>,
        <huangdaode@huawei.com>, <linuxarm@huawei.com>,
        Zeng Tao <prime.zeng@hisilicon.com>
Subject: [kvm-unit-tests PATCH] devicetree: Fix the dt_for_each_cpu_node
Date: Fri, 27 Dec 2019 19:03:35 +0800
Message-ID: <1577444615-26720-1-git-send-email-prime.zeng@hisilicon.com>
X-Mailer: git-send-email 2.7.4
MIME-Version: 1.0
X-Originating-IP: [10.69.192.56]
X-CFilter-Loop: Reflected
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

If the /cpus node contains nodes other than /cpus/cpu*, for example:
/cpus/cpu-map/. The test will issue an unexpected assert error as
follow:
[root@localhost]# ./arm-run arm/spinlock-test.flat
qemu-system-aarch64 -nodefaults -machine virt,gic-version=host,accel=kvm
 -cpu host -device virtio-serial-device -device virtconsole,chardev=ctd
-chardev testdev,id=ctd -device pci-testdev -display none -serial stdio
-kernel arm/spinlock-test.flat # -initrd /tmp/tmp.mwPLiF4EWm
lib/arm/setup.c:64: assert failed: ret == 0
        STACK:

In this patch, ignore the non-cpu subnodes instead of return an error.

Signed-off-by: Zeng Tao <prime.zeng@hisilicon.com>
---
 lib/devicetree.c | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
#### [PATCH v2] KVM: SVM: Override default MMIO mask if memory encryption is enabled
##### From: Tom Lendacky <thomas.lendacky@amd.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Tom Lendacky <thomas.lendacky@amd.com>
X-Patchwork-Id: 11311273
Return-Path: <SRS0=HBlZ=2R=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 22221138C
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 27 Dec 2019 15:58:30 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 603AD20882
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 27 Dec 2019 15:58:29 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=amdcloud.onmicrosoft.com
 header.i=@amdcloud.onmicrosoft.com header.b="aeeKxbr8"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726971AbfL0P6U (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 27 Dec 2019 10:58:20 -0500
Received: from mail-bn8nam12on2055.outbound.protection.outlook.com
 ([40.107.237.55]:6230
        "EHLO NAM12-BN8-obe.outbound.protection.outlook.com"
        rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org with ESMTP
        id S1726379AbfL0P6T (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 27 Dec 2019 10:58:19 -0500
ARC-Seal: i=1; a=rsa-sha256; s=arcselector9901; d=microsoft.com; cv=none;
 b=gOCj0L+MJkcE6PT0yMnecRNUUnNGXcndEidqrbDtA9C/AIH3kNzHj+9HpPHHVqwjOFQP8oNV/lPu2oMWIDy2aFtWbyDlRFkyvOGnxqrB6Au2GfGRkmNMFz5z4bB1YxZtf1/21mmRwqWq8kenKjwboVH5qgQX+LnS7ZqVpEIMrhlohCjxr42tRtu9f7JUTWNrAcnkv8fOMoORva26MlnYiBUlSeC+ZvGm8wfF1/uE2+zNQTgUMsdunGaUMNX08RWbJzCSjZ8k2f9NlfiOHTpHEcWn5KZ5VaALJW/wAa8RB90mKndDCTOX/XGDjmv9qKEmMcvK1y4v8uJzf0zpUKqfaQ==
ARC-Message-Signature: i=1; a=rsa-sha256; c=relaxed/relaxed; d=microsoft.com;
 s=arcselector9901;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=Wk8uak0Vil/mw6zN+A+wF6b0s7FpuAD4lfooSEVwZXg=;
 b=MwmytmLcYaSzAfXDDO27F8LQPRvCgQQ2w+1u4flDIT4j/HSZdTwn9jV+e0pAu1VdVm8RXpyMBqAPvka1/v24TeZqIIOgzx1A2sjCwd7DPCAcF/KDX9C1IIWw/ExBdAAeIEnIqcah96ZZLiPzrlhiy6TKFXZ+eXRk8jYS6x2EuSaCe9ZOOYWdrSV5AF/3H14bA2lEEmeUrp3/qHuox66qz9EsVh5oIski755HS/jYxOdbZRzWr1TawAOexXua+JfVGH5j+pLxZAp0+Z67Pm6ulpYDQk9LsTDbDTO6UYCDKNUu3WYUEzHd+2gbfJC5BuQ0dZ42Fia1hywIF5CFyo1T9A==
ARC-Authentication-Results: i=1; mx.microsoft.com 1; spf=pass
 smtp.mailfrom=amd.com; dmarc=pass action=none header.from=amd.com; dkim=pass
 header.d=amd.com; arc=none
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
 d=amdcloud.onmicrosoft.com; s=selector2-amdcloud-onmicrosoft-com;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=Wk8uak0Vil/mw6zN+A+wF6b0s7FpuAD4lfooSEVwZXg=;
 b=aeeKxbr8eDCJ2oOcCAhLHcMzG6WlQ8W9JlG0v0kWASeZrE1VnBbXshxUwUSJ8PtIra/GQfnNXY0DcJJvGhLxVsb666R1ypTx6tQPW1skcIhWzmB/IeKyNG9JsK2tjr1TouUtWi3CdmXSN/OXS8r12gI9eXLTvbpLqQ5qDWYLTQs=
Authentication-Results: spf=none (sender IP is )
 smtp.mailfrom=Thomas.Lendacky@amd.com;
Received: from DM6PR12MB3163.namprd12.prod.outlook.com (20.179.71.154) by
 DM6PR12MB3737.namprd12.prod.outlook.com (10.255.173.32) with Microsoft SMTP
 Server (version=TLS1_2, cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id
 15.20.2581.11; Fri, 27 Dec 2019 15:58:16 +0000
Received: from DM6PR12MB3163.namprd12.prod.outlook.com
 ([fe80::a0cd:463:f444:c270]) by DM6PR12MB3163.namprd12.prod.outlook.com
 ([fe80::a0cd:463:f444:c270%7]) with mapi id 15.20.2581.007; Fri, 27 Dec 2019
 15:58:16 +0000
From: Tom Lendacky <thomas.lendacky@amd.com>
To: kvm@vger.kernel.org, linux-kernel@vger.kernel.org
Cc: Paolo Bonzini <pbonzini@redhat.com>,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>,
        Brijesh Singh <brijesh.singh@amd.com>
Subject: [PATCH v2] KVM: SVM: Override default MMIO mask if memory encryption
 is enabled
Date: Fri, 27 Dec 2019 09:58:00 -0600
Message-Id: 
 <d741b3a58769749b7873fea703c027a68b8e2e3d.1577462279.git.thomas.lendacky@amd.com>
X-Mailer: git-send-email 2.17.1
X-ClientProxiedBy: SN1PR12CA0087.namprd12.prod.outlook.com
 (2603:10b6:802:21::22) To DM6PR12MB3163.namprd12.prod.outlook.com
 (2603:10b6:5:15e::26)
MIME-Version: 1.0
Received: from tlendack-t1.amd.com (165.204.77.1) by
 SN1PR12CA0087.namprd12.prod.outlook.com (2603:10b6:802:21::22) with Microsoft
 SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.2581.12 via Frontend
 Transport; Fri, 27 Dec 2019 15:58:15 +0000
X-Mailer: git-send-email 2.17.1
X-Originating-IP: [165.204.77.1]
X-MS-PublicTrafficType: Email
X-MS-Office365-Filtering-HT: Tenant
X-MS-Office365-Filtering-Correlation-Id: ad600a2b-c3fa-4b0a-029d-08d78ae595a6
X-MS-TrafficTypeDiagnostic: DM6PR12MB3737:|DM6PR12MB3737:
X-MS-Exchange-Transport-Forked: True
X-Microsoft-Antispam-PRVS: 
 <DM6PR12MB3737AA48068328244F4DCD3CEC2A0@DM6PR12MB3737.namprd12.prod.outlook.com>
X-MS-Oob-TLC-OOBClassifiers: OLM:8273;
X-Forefront-PRVS: 0264FEA5C3
X-Forefront-Antispam-Report: 
 SFV:NSPM;SFS:(10009020)(4636009)(136003)(346002)(376002)(396003)(39860400002)(366004)(189003)(199004)(81166006)(6666004)(8676002)(86362001)(478600001)(16526019)(4326008)(66946007)(52116002)(81156014)(6486002)(186003)(8936002)(7696005)(66476007)(26005)(66556008)(36756003)(956004)(2616005)(54906003)(5660300002)(2906002)(316002);DIR:OUT;SFP:1101;SCL:1;SRVR:DM6PR12MB3737;H:DM6PR12MB3163.namprd12.prod.outlook.com;FPR:;SPF:None;LANG:en;PTR:InfoNoRecords;MX:1;A:1;
Received-SPF: None (protection.outlook.com: amd.com does not designate
 permitted sender hosts)
X-MS-Exchange-SenderADCheck: 1
X-Microsoft-Antispam: BCL:0;
X-Microsoft-Antispam-Message-Info: 
 6l4wxQYBe0gYgd8OKZsJbgxNi+smx6xdqW9h3bJzP2AmZEr/g+2jEIMWEZh2y9mrYcix4P7aK4BxuAoLmzeaQxQfl1XqVvgDbMNwExVwM7qHLaZJb3ie71fpqoNlX4Rsu+zSJqejNlWJ9dNeBlhPHiseN25HozJ5xMYJ2HA0DDn1ggk6odrkvWty6qWG6T9Mg2xZTsaImSrGhBFTaKyWWCgSJfdAlk6eRYzWp7geGs5o7GGx2wWFNcZSByWePwsB/qxiG3QjcpOOOzfatDjP8gbc4ULH2RMuo+lRCTa+OMJaCbFsUcYuymGroc7DStoI3VkVf5V8Tifr07Jh929irEGwKTOtonJlmr5jnLRAl3Q4eHy0nC0vJHRp/tzxFkiIHejbGOKSHZXX8JZ5zySVriB323Fdjb2jkAvE6hBF19Tmn2WWQIZh4Z+wHiPvRULf
X-OriginatorOrg: amd.com
X-MS-Exchange-CrossTenant-Network-Message-Id: 
 ad600a2b-c3fa-4b0a-029d-08d78ae595a6
X-MS-Exchange-CrossTenant-OriginalArrivalTime: 27 Dec 2019 15:58:16.0702
 (UTC)
X-MS-Exchange-CrossTenant-FromEntityHeader: Hosted
X-MS-Exchange-CrossTenant-Id: 3dd8961f-e488-4e60-8e11-a82d994e183d
X-MS-Exchange-CrossTenant-MailboxType: HOSTED
X-MS-Exchange-CrossTenant-UserPrincipalName: 
 rE9L9PCzYfP9EGfAK67ALR2LuJF/hgjhU+Z9ycgqe1eFC2gDPtGpyx4LQn6YcTCD3G8yMUH9j/wxqmiGnoGsrA==
X-MS-Exchange-Transport-CrossTenantHeadersStamped: DM6PR12MB3737
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The KVM MMIO support uses bit 51 as the reserved bit to cause nested page
faults when a guest performs MMIO. The AMD memory encryption support uses
a CPUID function to define the encryption bit position. Given this, it is
possible that these bits can conflict.

Use svm_hardware_setup() to override the MMIO mask if memory encryption
support is enabled. When memory encryption support is enabled the physical
address width is reduced and the first bit after the last valid reduced
physical address bit will always be reserved. Use this bit as the MMIO
mask.

Fixes: 28a1f3ac1d0c ("kvm: x86: Set highest physical address bits in non-present/reserved SPTEs")
Suggested-by: Sean Christopherson <sean.j.christopherson@intel.com>
Signed-off-by: Tom Lendacky <thomas.lendacky@amd.com>
---
 arch/x86/kvm/svm.c | 26 ++++++++++++++++++++++++++
 1 file changed, 26 insertions(+)

```
#### [PATCH v9 1/7] KVM: CPUID: Fix IA32_XSS support in CPUID(0xd,i) enumeration
##### From: Yang Weijiang <weijiang.yang@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Yang Weijiang <weijiang.yang@intel.com>
X-Patchwork-Id: 11310811
Return-Path: <SRS0=HBlZ=2R=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 2A275139A
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 27 Dec 2019 02:07:45 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 00DE5208C4
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 27 Dec 2019 02:07:44 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727049AbfL0CH1 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 26 Dec 2019 21:07:27 -0500
Received: from mga17.intel.com ([192.55.52.151]:38918 "EHLO mga17.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726115AbfL0CH1 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 26 Dec 2019 21:07:27 -0500
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from fmsmga001.fm.intel.com ([10.253.24.23])
  by fmsmga107.fm.intel.com with ESMTP/TLS/DHE-RSA-AES256-GCM-SHA384;
 26 Dec 2019 18:07:27 -0800
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.69,361,1571727600";
   d="scan'208";a="223675021"
Received: from unknown (HELO local-michael-cet-test.sh.intel.com)
 ([10.239.159.128])
  by fmsmga001.fm.intel.com with ESMTP; 26 Dec 2019 18:07:26 -0800
From: Yang Weijiang <weijiang.yang@intel.com>
To: kvm@vger.kernel.org, linux-kernel@vger.kernel.org,
        pbonzini@redhat.com, jmattson@google.com,
        sean.j.christopherson@intel.com
Cc: yu.c.zhang@linux.intel.com, Yang Weijiang <weijiang.yang@intel.com>
Subject: [PATCH v9 1/7] KVM: CPUID: Fix IA32_XSS support in CPUID(0xd,i)
 enumeration
Date: Fri, 27 Dec 2019 10:11:27 +0800
Message-Id: <20191227021133.11993-2-weijiang.yang@intel.com>
X-Mailer: git-send-email 2.17.2
In-Reply-To: <20191227021133.11993-1-weijiang.yang@intel.com>
References: <20191227021133.11993-1-weijiang.yang@intel.com>
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The control bits in IA32_XSS MSR are being used for new features,
but current CPUID(0xd,i) enumeration code doesn't support them, so
fix existing code first.

The supervisor states in IA32_XSS haven't been used in public
KVM code, so set KVM_SUPPORTED_XSS to 0 now, anyone who's developing
IA32_XSS related feature may expand the macro to add the CPUID support,
otherwise, CPUID(0xd,i>1) always reports 0 of the subleaf to guest.

Extracted old code into a new filter and keep it same flavor as others.

This patch passed selftest on a few Intel platforms.

Suggested-by: Sean Christopherson <sean.j.christopherson@intel.com>
Signed-off-by: Yang Weijiang <weijiang.yang@intel.com>
---
 arch/x86/include/asm/kvm_host.h |   2 +
 arch/x86/kvm/cpuid.c            | 105 ++++++++++++++++++++++----------
 arch/x86/kvm/svm.c              |   7 +++
 arch/x86/kvm/vmx/vmx.c          |   8 +++
 arch/x86/kvm/x86.h              |   7 +++
 5 files changed, 97 insertions(+), 32 deletions(-)

```
