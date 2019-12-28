

#### [PATCH v9 0/7] Introduce support for guest CET feature
##### From: Yang Weijiang <weijiang.yang@intel.com>

```c
From patchwork Fri Dec 27 02:11:26 2019
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Yang Weijiang <weijiang.yang@intel.com>
X-Patchwork-Id: 11310825
Return-Path: <SRS0=HBlZ=2R=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id DEB8C6C1
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 27 Dec 2019 02:08:02 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id C753C2176D
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 27 Dec 2019 02:08:02 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727000AbfL0CH0 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 26 Dec 2019 21:07:26 -0500
Received: from mga17.intel.com ([192.55.52.151]:38918 "EHLO mga17.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726115AbfL0CH0 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 26 Dec 2019 21:07:26 -0500
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from fmsmga001.fm.intel.com ([10.253.24.23])
  by fmsmga107.fm.intel.com with ESMTP/TLS/DHE-RSA-AES256-GCM-SHA384;
 26 Dec 2019 18:07:26 -0800
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.69,361,1571727600";
   d="scan'208";a="223675006"
Received: from unknown (HELO local-michael-cet-test.sh.intel.com)
 ([10.239.159.128])
  by fmsmga001.fm.intel.com with ESMTP; 26 Dec 2019 18:07:24 -0800
From: Yang Weijiang <weijiang.yang@intel.com>
To: kvm@vger.kernel.org, linux-kernel@vger.kernel.org,
        pbonzini@redhat.com, jmattson@google.com,
        sean.j.christopherson@intel.com
Cc: yu.c.zhang@linux.intel.com, Yang Weijiang <weijiang.yang@intel.com>
Subject: [PATCH v9 0/7] Introduce support for guest CET feature
Date: Fri, 27 Dec 2019 10:11:26 +0800
Message-Id: <20191227021133.11993-1-weijiang.yang@intel.com>
X-Mailer: git-send-email 2.17.2
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Control-flow Enforcement Technology (CET) provides protection against
Return/Jump-Oriented Programming (ROP/JOP) attack. It includes two
sub-features: Shadow Stack (SHSTK) and Indirect Branch Tracking (IBT).

KVM change is required to support guest CET feature.
This patch serial implemented CET related CPUID/XSAVES enumeration, MSRs
and vmentry/vmexit configuration etc.so that guest kernel can setup CET
runtime infrastructure based on them. Some CET MSRs and related feature
flags used reference the definitions in kernel patchset.

CET kernel patches is here:
https://lkml.org/lkml/2019/8/13/1110
https://lkml.org/lkml/2019/8/13/1109
Note: CET hasn't been supported for nested case now, since CR4.CET
is fixed to 0 in FIXED1 MSR, actually nested VM cannot enable CET.

v8 -> v9:
- Refactored msr-check functions per Sean's feedback.
- Fixed a few issues per Sean's suggestion.
- Rebased patch to kernel-v5.4.
- Moved CET CPUID feature bits and CR4.CET to last patch.

v7 -> v8:
- Addressed Jim and Sean's feedback on: 1) CPUID(0xD,i) enumeration. 2)
  sanity check when configure guest CET. 3) function improvement.
- Added more sanity check functions.
- Set host vmexit default status so that guest won't leak CET status to
  host when vmexit.
- Added CR0.WP vs. CR4.CET mutual constrains.

v6 -> v7:
- Rebased patch to kernel v5.3
- Sean suggested to change CPUID(0xd, n) enumeration code as alined with
  existing one, and I think it's better to make the fix as an independent patch 
  since XSS MSR are being used widely on X86 platforms.
- Check more host and guest status before configure guest CET
  per Sean's feedback.
- Add error-check before guest accesses CET MSRs per Sean's feedback.
- Other minor fixes suggested by Sean.

v5 -> v6:
- Rebase patch to kernel v5.2.
- Move CPUID(0xD, n>=1) helper to a seperate patch.
- Merge xsave size fix with other patch.
- Other minor fixes per community feedback.

v4 -> v5:
- Rebase patch to kernel v5.1.
- Wrap CPUID(0xD, n>=1) code to a helper function.
- Pass through MSR_IA32_PL1_SSP and MSR_IA32_PL2_SSP to Guest.
- Add Co-developed-by expression in patch description.
- Refine patch description.

v3 -> v4:
- Add Sean's patch for loading Guest fpu state before access XSAVES
  managed CET MSRs.
- Melt down CET bits setting into CPUID configuration patch.
- Add VMX interface to query Host XSS.
- Check Host and Guest XSS support bits before set Guest XSS.
- Make Guest SHSTK and IBT feature enabling independent.
- Do not report CET support to Guest when Host CET feature is Disabled.

v2 -> v3:
- Modified patches to make Guest CET independent to Host enabling.
- Added patch 8 to add user space access for Guest CET MSR access.
- Modified code comments and patch description to reflect changes.

v1 -> v2:
- Re-ordered patch sequence, combined one patch.
- Added more description for CET related VMCS fields.
- Added Host CET capability check while enabling Guest CET loading bit.
- Added Host CET capability check while reporting Guest CPUID(EAX=7, EXC=0).
- Modified code in reporting Guest CPUID(EAX=D,ECX>=1), make it clearer.
- Added Host and Guest XSS mask check while setting bits for Guest XSS.


PATCH 1    : Fix CPUID(0xD, n) enumeration to support XSS MSR.
PATCH 2    : Define CET VMCS fields and bits.
PATCH 3    : Pass through CET MSRs to guest.
PATCH 4    : Load guest/host CET states on vmentry/vmexit.
PATCH 5    : Enable update to IA32_XSS for guest.
PATCH 6    : Load Guest FPU states for XSAVES managed MSRs.
PATCH 7    : Add user-space CET MSR access interface.




Sean Christopherson (1):
  KVM: X86: Load guest fpu state when accessing MSRs managed by XSAVES

Yang Weijiang (6):
  KVM: CPUID: Fix IA32_XSS support in CPUID(0xd,i) enumeration
  KVM: VMX: Define CET VMCS fields and #CP flag
  KVM: VMX: Pass through CET related MSRs
  KVM: VMX: Load CET states on vmentry/vmexit
  KVM: X86: Enable CET bits update in IA32_XSS
  KVM: X86: Add user-space access interface for CET MSRs

 arch/x86/include/asm/kvm_host.h |   6 +-
 arch/x86/include/asm/vmx.h      |   8 +
 arch/x86/include/uapi/asm/kvm.h |   1 +
 arch/x86/kvm/cpuid.c            | 122 ++++++++++-----
 arch/x86/kvm/cpuid.h            |   2 +
 arch/x86/kvm/svm.c              |   7 +
 arch/x86/kvm/vmx/capabilities.h |  10 ++
 arch/x86/kvm/vmx/vmx.c          | 256 +++++++++++++++++++++++++++++++-
 arch/x86/kvm/x86.c              |  36 ++++-
 arch/x86/kvm/x86.h              |  10 +-
 10 files changed, 412 insertions(+), 46 deletions(-)
```
