

#### [RESEND PATCH 00/13] KVM: x86: Remove emulation_result enums
##### From: Sean Christopherson <sean.j.christopherson@intel.com>

```c
From patchwork Fri Aug 23 01:06:56 2019
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Sean Christopherson <sean.j.christopherson@intel.com>
X-Patchwork-Id: 11110331
Return-Path: <SRS0=ITOr=WT=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id C0F4D14DB
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 23 Aug 2019 01:08:22 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id AB39423404
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 23 Aug 2019 01:08:22 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1732637AbfHWBHL (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 22 Aug 2019 21:07:11 -0400
Received: from mga01.intel.com ([192.55.52.88]:37991 "EHLO mga01.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1732535AbfHWBHL (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 22 Aug 2019 21:07:11 -0400
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from fmsmga003.fm.intel.com ([10.253.24.29])
  by fmsmga101.fm.intel.com with ESMTP/TLS/DHE-RSA-AES256-GCM-SHA384;
 22 Aug 2019 18:07:10 -0700
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.64,419,1559545200";
   d="scan'208";a="186733483"
Received: from sjchrist-coffee.jf.intel.com ([10.54.74.41])
  by FMSMGA003.fm.intel.com with ESMTP; 22 Aug 2019 18:07:10 -0700
From: Sean Christopherson <sean.j.christopherson@intel.com>
To: Paolo Bonzini <pbonzini@redhat.com>,
 =?utf-8?b?UmFkaW0gS3LEjW3DocWZ?= <rkrcmar@redhat.com>
Cc: Sean Christopherson <sean.j.christopherson@intel.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org
Subject: [RESEND PATCH 00/13] KVM: x86: Remove emulation_result enums
Date: Thu, 22 Aug 2019 18:06:56 -0700
Message-Id: <20190823010709.24879-1-sean.j.christopherson@intel.com>
X-Mailer: git-send-email 2.22.0
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Rework the emulator and its users to handle failure scenarios entirely
within the emulator.

{x86,kvm}_emulate_instruction() currently return a tri-state value to
indicate success/continue, userspace exit needed, and failure.  The
intent of returning EMULATE_FAIL is to let the caller handle failure in
a manner that is appropriate for the current context.  In practice,
the emulator has ended up with a mixture of failure handling, i.e.
whether or not the emulator takes action on failure is dependent on the
specific flavor of emulation.

The mixed handling has proven to be rather fragile, e.g. many flows
incorrectly assume their specific flavor of emulation cannot fail or
that the emulator sets state to report the failure back to userspace.

Move everything inside the emulator, piece by piece, so that the
emulation routines can return '0' for exit to userspace and '1' for
resume the guest, just like every other VM-Exit handler.

Paolo/Radim/Vitaly, apologies for the resend, forgot to cc kvm, lkml
and reviewers.

Sean Christopherson (13):
  KVM: x86: Relocate MMIO exit stats counting
  KVM: x86: Clean up handle_emulation_failure()
  KVM: x86: Refactor kvm_vcpu_do_singlestep() to remove out param
  KVM: x86: Drop EMULTYPE_NO_UD_ON_FAIL as a standalone type
  KVM: x86: Don't attempt VMWare emulation on #GP with non-zero error
    code
  KVM: x86: Move #GP injection for VMware into x86_emulate_instruction()
  KVM: x86: Add explicit flag for forced emulation on #UD
  KVM: x86: Move #UD injection for failed emulation into emulation code
  KVM: x86: Exit to userspace on emulation skip failure
  KVM: x86: Handle emulation failure directly in kvm_task_switch()
  KVM: x86: Move triple fault request into RM int injection
  KVM: VMX: Remove EMULATE_FAIL handling in handle_invalid_guest_state()
  KVM: x86: Remove emulation_result enums, EMULATE_{DONE,FAIL,USER_EXIT}

 arch/x86/include/asm/kvm_host.h |  10 +--
 arch/x86/kvm/mmu.c              |  16 +---
 arch/x86/kvm/svm.c              |  41 ++++-------
 arch/x86/kvm/vmx/vmx.c          |  92 +++++++++--------------
 arch/x86/kvm/x86.c              | 127 +++++++++++++++++---------------
 arch/x86/kvm/x86.h              |   2 +-
 6 files changed, 121 insertions(+), 167 deletions(-)
```
