#### [PATCH v12 01/11] perf/x86: Fix variable types for LBR registers
##### From: Like Xu <like.xu@linux.intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Like Xu <like.xu@linux.intel.com>
X-Patchwork-Id: 11602585
Return-Path: <SRS0=SoHH=72=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id A10121667
	for <patchwork-kvm@patchwork.kernel.org>;
 Sat, 13 Jun 2020 08:11:28 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 845C420739
	for <patchwork-kvm@patchwork.kernel.org>;
 Sat, 13 Jun 2020 08:11:28 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726453AbgFMILK (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Sat, 13 Jun 2020 04:11:10 -0400
Received: from mga06.intel.com ([134.134.136.31]:50458 "EHLO mga06.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726451AbgFMILH (ORCPT <rfc822;kvm@vger.kernel.org>);
        Sat, 13 Jun 2020 04:11:07 -0400
IronPort-SDR: 
 yGPZ1Z7M8oabm0aXoy6aGGKQ/+6/sSPe/D74sp0BcJ56FmQJbC1CnxNH4fQnnVFcERa9AGfi3z
 HfbAxgCi6MWg==
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from fmsmga006.fm.intel.com ([10.253.24.20])
  by orsmga104.jf.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 13 Jun 2020 01:11:03 -0700
IronPort-SDR: 
 fM8V1pKNSOdeOzjezraxISaiMrF/G1Qs6okKN6PURfaF5grCqmvCOyouy5RjcG/U1dl+ECKQj+
 IT2yY/R8U0lg==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.73,506,1583222400";
   d="scan'208";a="474467309"
Received: from sqa-gate.sh.intel.com (HELO clx-ap-likexu.tsp.org)
 ([10.239.48.212])
  by fmsmga006.fm.intel.com with ESMTP; 13 Jun 2020 01:10:57 -0700
From: Like Xu <like.xu@linux.intel.com>
To: Paolo Bonzini <pbonzini@redhat.com>
Cc: Peter Zijlstra <peterz@infradead.org>,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>, ak@linux.intel.com,
        wei.w.wang@intel.com, linux-kernel@vger.kernel.org,
        kvm@vger.kernel.org
Subject: [PATCH v12 01/11] perf/x86: Fix variable types for LBR registers
Date: Sat, 13 Jun 2020 16:09:46 +0800
Message-Id: <20200613080958.132489-2-like.xu@linux.intel.com>
X-Mailer: git-send-email 2.21.3
In-Reply-To: <20200613080958.132489-1-like.xu@linux.intel.com>
References: <20200613080958.132489-1-like.xu@linux.intel.com>
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Wei Wang <wei.w.wang@intel.com>

The MSR variable type can be 'unsigned int', which uses less memory than
the longer 'unsigned long'. Fix 'struct x86_pmu' for that. The lbr_nr won't
be a negative number, so make it 'unsigned int' as well.

Suggested-by: Peter Zijlstra (Intel) <peterz@infradead.org>
Signed-off-by: Wei Wang <wei.w.wang@intel.com>
---
 arch/x86/events/perf_event.h | 4 ++--
 1 file changed, 2 insertions(+), 2 deletions(-)

```
#### [Qemu-devel] [PATCH 2/2] target/i386: add -cpu,lbr=true support to enable guest LBR
##### From: Like Xu <like.xu@linux.intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Like Xu <like.xu@linux.intel.com>
X-Patchwork-Id: 11602591
Return-Path: <SRS0=SoHH=72=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id ED28260D
	for <patchwork-kvm@patchwork.kernel.org>;
 Sat, 13 Jun 2020 08:11:52 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id DAAEA20836
	for <patchwork-kvm@patchwork.kernel.org>;
 Sat, 13 Jun 2020 08:11:52 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726625AbgFMILv (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Sat, 13 Jun 2020 04:11:51 -0400
Received: from mga07.intel.com ([134.134.136.100]:64611 "EHLO mga07.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726607AbgFMILq (ORCPT <rfc822;kvm@vger.kernel.org>);
        Sat, 13 Jun 2020 04:11:46 -0400
IronPort-SDR: 
 lQwCqyn4kQwcLC+TU9yj/VMROTP5o0MRNprS+/xWCXOD0ebQaYQ+qd3+5Kd5N+2P0viY0g122v
 KYBCuUG4oPsw==
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from fmsmga006.fm.intel.com ([10.253.24.20])
  by orsmga105.jf.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 13 Jun 2020 01:11:45 -0700
IronPort-SDR: 
 AK6qlJLtROluxcMsH4ncP5Bzl2ypOMmN2KFrcBhDfVHb8eHrTJd83OdsFQD10TmzWoJ06oh5md
 h891sxQCa/SQ==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.73,506,1583222400";
   d="scan'208";a="474467502"
Received: from sqa-gate.sh.intel.com (HELO clx-ap-likexu.tsp.org)
 ([10.239.48.212])
  by fmsmga006.fm.intel.com with ESMTP; 13 Jun 2020 01:11:41 -0700
From: Like Xu <like.xu@linux.intel.com>
To: Paolo Bonzini <pbonzini@redhat.com>
Cc: Peter Zijlstra <peterz@infradead.org>,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>, ak@linux.intel.com,
        wei.w.wang@intel.com, linux-kernel@vger.kernel.org,
        kvm@vger.kernel.org, Like Xu <like.xu@linux.intel.com>,
        Richard Henderson <rth@twiddle.net>,
        Eduardo Habkost <ehabkost@redhat.com>,
        "Michael S. Tsirkin" <mst@redhat.com>,
        Marcel Apfelbaum <marcel.apfelbaum@gmail.com>,
        Marcelo Tosatti <mtosatti@redhat.com>, qemu-devel@nongnu.org
Subject: [Qemu-devel] [PATCH 2/2] target/i386: add -cpu,lbr=true support to
 enable guest LBR
Date: Sat, 13 Jun 2020 16:09:58 +0800
Message-Id: <20200613080958.132489-14-like.xu@linux.intel.com>
X-Mailer: git-send-email 2.21.3
In-Reply-To: <20200613080958.132489-1-like.xu@linux.intel.com>
References: <20200613080958.132489-1-like.xu@linux.intel.com>
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The LBR feature would be enabled on the guest if:
- the KVM is enabled and the PMU is enabled and,
- the msr-based-feature IA32_PERF_CAPABILITIES is supporterd and,
- the supported returned value for lbr_fmt from this msr is not zero.

The LBR feature would be disabled on the guest if:
- the msr-based-feature IA32_PERF_CAPABILITIES is unsupporterd OR,
- qemu set the IA32_PERF_CAPABILITIES msr feature without lbr_fmt values OR,
- the requested guest vcpu model doesn't support PDCM.

Cc: Paolo Bonzini <pbonzini@redhat.com>
Cc: Richard Henderson <rth@twiddle.net>
Cc: Eduardo Habkost <ehabkost@redhat.com>
Cc: "Michael S. Tsirkin" <mst@redhat.com>
Cc: Marcel Apfelbaum <marcel.apfelbaum@gmail.com>
Cc: Marcelo Tosatti <mtosatti@redhat.com>
Cc: qemu-devel@nongnu.org
Signed-off-by: Like Xu <like.xu@linux.intel.com>
---
 hw/i386/pc.c      |  1 +
 target/i386/cpu.c | 25 +++++++++++++++++++++++--
 target/i386/cpu.h |  2 ++
 target/i386/kvm.c |  7 ++++++-
 4 files changed, 32 insertions(+), 3 deletions(-)

```
#### [Qemu-devel] [PATCH 1/2] target/i386: define a new MSR based feature word - FEAT_PERF_CAPABILITIES
##### From: Like Xu <like.xu@linux.intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Like Xu <like.xu@linux.intel.com>
X-Patchwork-Id: 11602589
Return-Path: <SRS0=SoHH=72=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 1BDC560D
	for <patchwork-kvm@patchwork.kernel.org>;
 Sat, 13 Jun 2020 08:11:49 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 0D23420739
	for <patchwork-kvm@patchwork.kernel.org>;
 Sat, 13 Jun 2020 08:11:48 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726577AbgFMILq (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Sat, 13 Jun 2020 04:11:46 -0400
Received: from mga07.intel.com ([134.134.136.100]:64611 "EHLO mga07.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726589AbgFMILm (ORCPT <rfc822;kvm@vger.kernel.org>);
        Sat, 13 Jun 2020 04:11:42 -0400
IronPort-SDR: 
 i7rtusce3IP1GoV5ICSzqfdXkngpl8/m0JNB/DCVsmpVPR6ErtqQG9u+mfE/2pKCv8kV+vZh/K
 QPR4oPLYv6mw==
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from fmsmga006.fm.intel.com ([10.253.24.20])
  by orsmga105.jf.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 13 Jun 2020 01:11:41 -0700
IronPort-SDR: 
 4vOTELTGn2dSvfowlnqEBt9ut7pIiGuwW5OmvT4fXwdkjrSbhzsz4ePuNTILeW23eJuOYGrqTD
 f+g//eJ5sKIQ==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.73,506,1583222400";
   d="scan'208";a="474467482"
Received: from sqa-gate.sh.intel.com (HELO clx-ap-likexu.tsp.org)
 ([10.239.48.212])
  by fmsmga006.fm.intel.com with ESMTP; 13 Jun 2020 01:11:37 -0700
From: Like Xu <like.xu@linux.intel.com>
To: Paolo Bonzini <pbonzini@redhat.com>
Cc: Peter Zijlstra <peterz@infradead.org>,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>, ak@linux.intel.com,
        wei.w.wang@intel.com, linux-kernel@vger.kernel.org,
        kvm@vger.kernel.org, Like Xu <like.xu@linux.intel.com>,
        Richard Henderson <rth@twiddle.net>,
        Eduardo Habkost <ehabkost@redhat.com>,
        Marcelo Tosatti <mtosatti@redhat.com>, qemu-devel@nongnu.org
Subject: [Qemu-devel] [PATCH 1/2] target/i386: define a new MSR based feature
 word - FEAT_PERF_CAPABILITIES
Date: Sat, 13 Jun 2020 16:09:57 +0800
Message-Id: <20200613080958.132489-13-like.xu@linux.intel.com>
X-Mailer: git-send-email 2.21.3
In-Reply-To: <20200613080958.132489-1-like.xu@linux.intel.com>
References: <20200613080958.132489-1-like.xu@linux.intel.com>
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The Perfmon and Debug Capability MSR named IA32_PERF_CAPABILITIES is
a feature-enumerating MSR, which only enumerates the feature full-width
write (via bit 13) by now which indicates the processor supports IA32_A_PMCx
interface for updating bits 32 and above of IA32_PMCx.

The existence of MSR IA32_PERF_CAPABILITIES is enumerated by CPUID.1:ECX[15].

Cc: Paolo Bonzini <pbonzini@redhat.com>
Cc: Richard Henderson <rth@twiddle.net>
Cc: Eduardo Habkost <ehabkost@redhat.com>
Cc: Marcelo Tosatti <mtosatti@redhat.com>
Cc: qemu-devel@nongnu.org
Signed-off-by: Like Xu <like.xu@linux.intel.com>
Message-Id: <20200529074347.124619-5-like.xu@linux.intel.com>
Signed-off-by: Paolo Bonzini <pbonzini@redhat.com>
---
 target/i386/cpu.c | 23 +++++++++++++++++++++++
 target/i386/cpu.h |  3 +++
 target/i386/kvm.c | 20 ++++++++++++++++++++
 3 files changed, 46 insertions(+)

```
