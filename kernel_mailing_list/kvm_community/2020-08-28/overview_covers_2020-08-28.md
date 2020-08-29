

#### [PATCH 0/5] Fix nested VMX controls MSRs
##### From: Chenyi Qiang <chenyi.qiang@intel.com>

```c
From patchwork Fri Aug 28 08:56:17 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Chenyi Qiang <chenyi.qiang@intel.com>
X-Patchwork-Id: 11742411
Return-Path: <SRS0=/qcN=CG=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 9326F13A4
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 28 Aug 2020 08:54:20 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 82C27208D5
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 28 Aug 2020 08:54:20 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728627AbgH1IyQ (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 28 Aug 2020 04:54:16 -0400
Received: from mga17.intel.com ([192.55.52.151]:49188 "EHLO mga17.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1728357AbgH1IyP (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 28 Aug 2020 04:54:15 -0400
IronPort-SDR: 
 R4bqAzZeiDQ9wovcXGVwQWq0ojTAG6FuznRJ1hEa7A0W2e/c0lMak21syIrNDKEySCu68mucFU
 WGTeCLUxRduA==
X-IronPort-AV: E=McAfee;i="6000,8403,9726"; a="136697480"
X-IronPort-AV: E=Sophos;i="5.76,363,1592895600";
   d="scan'208";a="136697480"
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from fmsmga002.fm.intel.com ([10.253.24.26])
  by fmsmga107.fm.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 28 Aug 2020 01:54:15 -0700
IronPort-SDR: 
 LZE/KZPpjd2cGa1IAhn+L2N0biOQvd/G2yIcuYUE0ExINP7VUMP5/LqiDqgpw0J6AH0JcYbIRr
 WpV0EJW4NkmQ==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.76,363,1592895600";
   d="scan'208";a="332483483"
Received: from chenyi-pc.sh.intel.com ([10.239.159.72])
  by fmsmga002.fm.intel.com with ESMTP; 28 Aug 2020 01:54:13 -0700
From: Chenyi Qiang <chenyi.qiang@intel.com>
To: Paolo Bonzini <pbonzini@redhat.com>,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>,
        Xiaoyao Li <xiaoyao.li@intel.com>
Cc: kvm@vger.kernel.org, linux-kernel@vger.kernel.org
Subject: [PATCH 0/5] Fix nested VMX controls MSRs
Date: Fri, 28 Aug 2020 16:56:17 +0800
Message-Id: <20200828085622.8365-1-chenyi.qiang@intel.com>
X-Mailer: git-send-email 2.17.1
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The first three patches fix a issue for the nested VMX controls MSRs. The
issue happens when I use QEMU to run nested VM. The VM_{ENTRY,
EXIT}_LOAD_IA32_PERF_GLOBAL_CTRL and VM_{ENTRY_LOAD, EXIT_CLEAR}_BNDCFGS
in L1 MSR_IA32_VMX_TRUE_{ENTRY, EXIT}_CTLS MSR are always cleared
regardless of whether it supports in L1. This is because QEMU gets the
nested VMX MSRs from vmcs_config.nested_vmx_msrs which doesn't expose
these two fields. Then, when QEMU initializes the features MSRs after
SET_CPUID, it will override the nested VMX MSR values which has been
updated according to guest CPUID during SET_CPUID. This patch series
just expose the missing fields in nested VMX {ENTRY, EXIT} controls
MSR and adds the support to update nested VMX MSRs after set_vmx_msrs.

The last two patches are a minor fix and cleanup.

Chenyi Qiang (5):
  KVM: nVMX: Fix VMX controls MSRs setup when nested VMX enabled
  KVM: nVMX: Verify the VMX controls MSRs with the global capability
    when setting VMX MSRs
  KVM: nVMX: Update VMX controls MSR according to guest CPUID after
    setting VMX MSRs
  KVM: nVMX: Fix the update value of nested load IA32_PERF_GLOBAL_CTRL
    control
  KVM: nVMX: Simplify the initialization of nested_vmx_msrs

 arch/x86/kvm/vmx/nested.c | 79 +++++++++++++++++++++++++++------------
 arch/x86/kvm/vmx/vmx.c    |  9 +++--
 2 files changed, 62 insertions(+), 26 deletions(-)
```
