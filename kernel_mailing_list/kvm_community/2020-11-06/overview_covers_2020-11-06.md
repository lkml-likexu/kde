

#### [PATCH v14 00/13] Introduce support for guest CET feature
##### From: Yang Weijiang <weijiang.yang@intel.com>

```c
From patchwork Fri Nov  6 01:16:24 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Yang Weijiang <weijiang.yang@intel.com>
X-Patchwork-Id: 11885643
Return-Path: <SRS0=V6CK=EM=vger.kernel.org=kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-11.7 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,MAILING_LIST_MULTI,MENTIONS_GIT_HOSTING,
	SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED,USER_AGENT_GIT autolearn=unavailable
	autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id B50E7C4742C
	for <kvm@archiver.kernel.org>; Fri,  6 Nov 2020 01:07:29 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 613022075A
	for <kvm@archiver.kernel.org>; Fri,  6 Nov 2020 01:07:29 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1732883AbgKFBGN (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Thu, 5 Nov 2020 20:06:13 -0500
Received: from mga18.intel.com ([134.134.136.126]:38177 "EHLO mga18.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1730895AbgKFBGN (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 5 Nov 2020 20:06:13 -0500
IronPort-SDR: 
 tVTr7HWDsB2bmdlXmnpEUMNPTmx2VuOXz5BPfstuk62cEkALvVT8yL+B0RLPSTeRjJNKoyiwKy
 Py3NN8QMyOcg==
X-IronPort-AV: E=McAfee;i="6000,8403,9796"; a="157264651"
X-IronPort-AV: E=Sophos;i="5.77,454,1596524400";
   d="scan'208";a="157264651"
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from orsmga004.jf.intel.com ([10.7.209.38])
  by orsmga106.jf.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 05 Nov 2020 17:06:12 -0800
IronPort-SDR: 
 vqQREbqCORB3hTM8wnJIwM+R0oUlaudb/EPPIxOBiBRcGwdo1F61s4KHR4XRyTK80TTHd8HQqp
 7Wz+PJukbWTg==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.77,454,1596524400";
   d="scan'208";a="471874422"
Received: from local-michael-cet-test.sh.intel.com ([10.239.159.156])
  by orsmga004.jf.intel.com with ESMTP; 05 Nov 2020 17:06:10 -0800
From: Yang Weijiang <weijiang.yang@intel.com>
To: kvm@vger.kernel.org, linux-kernel@vger.kernel.org,
        pbonzini@redhat.com, sean.j.christopherson@intel.com,
        jmattson@google.com
Cc: yu.c.zhang@linux.intel.com, Yang Weijiang <weijiang.yang@intel.com>
Subject: [PATCH v14 00/13] Introduce support for guest CET feature
Date: Fri,  6 Nov 2020 09:16:24 +0800
Message-Id: <20201106011637.14289-1-weijiang.yang@intel.com>
X-Mailer: git-send-email 2.17.2
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Control-flow Enforcement Technology (CET) provides protection against
Return/Jump-Oriented Programming (ROP/JOP) attack. There're two CET
sub-features: Shadow Stack (SHSTK) and Indirect Branch Tracking (IBT).
SHSTK is to prevent ROP programming and IBT is to prevent JOP programming.

Several parts in KVM have been updated to provide VM CET support, including:
CPUID/XSAVES config, MSR pass-through, user space MSR access interface, 
vmentry/vmexit config, nested VM etc. These patches have dependency on CET
kernel patches for xsaves support and CET definitions, e.g., MSR and related
feature flags.

CET kernel patches are here:
SHSTK: https://lkml.kernel.org/r/20201012153850.26996-1-yu-cheng.yu@intel.com/
IBT: https://lkml.kernel.org/r/20201012154530.28382-1-yu-cheng.yu@intel.com/

CET QEMU patch:
https://patchwork.ozlabs.org/project/qemu-devel/patch/20201013051935.6052-2-weijiang.yang@intel.com/
KVM Unit test:
https://patchwork.kernel.org/project/kvm/patch/20200506082110.25441-12-weijiang.yang@intel.com/

v14:
- Sean refactored v13 patchset then came out v14-rc1, this version is
  rebased on top of 5.10-rc1 and tested on TGL.
- Fixed a few minor issues found during test, such as nested CET broken,
  call-trace and guest reboot failure etc.
- Original v14-rc1 is here: https://github.com/sean-jc/linux/tree/vmx/cet.

v13:
- Added CET definitions as a separate patch to facilitate KVM test.
- Disabled CET support in KVM if unrestricted_guest is turned off since
  in this case CET related instructions/infrastructure cannot be emulated
  well.

v12:
- Fixed a few issues per Sean and Paolo's review feeback.
- Refactored patches to make them properly arranged.
- Removed unnecessary hard-coded CET states for host/guest.
- Added compile-time assertions for vmcs_field_to_offset_table to detect
  mismatch of the field type and field encoding number.
- Added a custom MSR MSR_KVM_GUEST_SSP for guest active SSP save/restore.
- Rebased patches to 5.7-rc3.

v11:
- Fixed a guest vmentry failure issue when guest reboots.
- Used vm_xxx_control_{set, clear}bit() to avoid side effect, it'll
  clear cached data instead of pure VMCS field bits.
- Added vcpu->arch.guest_supported_xss dedidated for guest runtime mask,
  this avoids supported_xss overwritten issue caused by an old qemu.
- Separated vmentry/vmexit state setting with CR0/CR4 dependency check
  to make the patch more clear.
- Added CET VMCS states in dump_vmcs() for debugging purpose.
- Other refactor based on testing.
- This patch serial is built on top of below branch and CET kernel patches
  for seeking xsaves support.

v10:
- Refactored code per Sean's review feedback.
- Added CET support for nested VM.
- Removed fix-patch for CPUID(0xd,N) enumeration as this part is done
  by Paolo and Sean.
- This new patchset is based on Paolo's queued cpu_caps branch.
- Modified patch per XSAVES related change.
- Consolidated KVM unit-test patch with KVM patches.

v9:
- Refactored msr-check functions per Sean's feedback.
- Fixed a few issues per Sean's suggestion.
- Rebased patch to kernel-v5.4.
- Moved CET CPUID feature bits and CR4.CET to last patch.

v8:
- Addressed Jim and Sean's feedback on: 1) CPUID(0xD,i) enumeration. 2)
  sanity check when configure guest CET. 3) function improvement.
- Added more sanity check functions.
- Set host vmexit default status so that guest won't leak CET status to
  host when vmexit.
- Added CR0.WP vs. CR4.CET mutual constrains.

v7:
- Rebased patch to kernel v5.3
- Sean suggested to change CPUID(0xd, n) enumeration code as alined with
  existing one, and I think it's better to make the fix as an independent patch 
  since XSS MSR are being used widely on X86 platforms.
- Check more host and guest status before configure guest CET
  per Sean's feedback.
- Add error-check before guest accesses CET MSRs per Sean's feedback.
- Other minor fixes suggested by Sean.

v6:
- Rebase patch to kernel v5.2.
- Move CPUID(0xD, n>=1) helper to a seperate patch.
- Merge xsave size fix with other patch.
- Other minor fixes per community feedback.

v5:
- Rebase patch to kernel v5.1.
- Wrap CPUID(0xD, n>=1) code to a helper function.
- Pass through MSR_IA32_PL1_SSP and MSR_IA32_PL2_SSP to Guest.
- Add Co-developed-by expression in patch description.
- Refine patch description.

v4:
- Add Sean's patch for loading Guest fpu state before access XSAVES
  managed CET MSRs.
- Melt down CET bits setting into CPUID configuration patch.
- Add VMX interface to query Host XSS.
- Check Host and Guest XSS support bits before set Guest XSS.
- Make Guest SHSTK and IBT feature enabling independent.
- Do not report CET support to Guest when Host CET feature is Disabled.

v3:
- Modified patches to make Guest CET independent to Host enabling.
- Added patch 8 to add user space access for Guest CET MSR access.
- Modified code comments and patch description to reflect changes.

v2:
- Re-ordered patch sequence, combined one patch.
- Added more description for CET related VMCS fields.
- Added Host CET capability check while enabling Guest CET loading bit.
- Added Host CET capability check while reporting Guest CPUID(EAX=7, EXC=0).
- Modified code in reporting Guest CPUID(EAX=D,ECX>=1), make it clearer.
- Added Host and Guest XSS mask check while setting bits for Guest XSS.


Sean Christopherson (2):
  KVM: x86: Report XSS as an MSR to be saved if there are supported features
  KVM: x86: Load guest fpu state when accessing MSRs managed by XSAVES

Yang Weijiang (11):
  KVM: x86: Refresh CPUID on writes to MSR_IA32_XSS
  KVM: x86: Add #CP support in guest exception dispatch
  KVM: VMX: Introduce CET VMCS fields and flags
  KVM: x86: Add fault checks for CR4.CET
  KVM: VMX: Emulate reads and writes to CET MSRs
  KVM: VMX: Add a synthetic MSR to allow userspace VMM to access GUEST_SSP
  KVM: x86: Report CET MSRs as to-be-saved if CET is supported
  KVM: x86: Enable CET virtualization for VMX and advertise CET to userspace
  KVM: VMX: Pass through CET MSRs to the guest when supported
  KVM: nVMX: Add helper to check the vmcs01 MSR bitmap for MSR pass-through
  KVM: nVMX: Enable CET support for nested VMX

 arch/x86/include/asm/kvm_host.h      |   4 +-
 arch/x86/include/asm/vmx.h           |   8 ++
 arch/x86/include/uapi/asm/kvm.h      |   1 +
 arch/x86/include/uapi/asm/kvm_para.h |   1 +
 arch/x86/kvm/cpuid.c                 |  26 +++-
 arch/x86/kvm/vmx/capabilities.h      |   5 +
 arch/x86/kvm/vmx/nested.c            |  57 ++++++--
 arch/x86/kvm/vmx/vmcs12.c            |   6 +
 arch/x86/kvm/vmx/vmcs12.h            |  14 +-
 arch/x86/kvm/vmx/vmx.c               | 207 ++++++++++++++++++++++++++-
 arch/x86/kvm/x86.c                   |  56 +++++++-
 arch/x86/kvm/x86.h                   |  10 +-
 12 files changed, 370 insertions(+), 25 deletions(-)
```
#### [PATCH v5 0/4] Add bus lock VM exit support
##### From: Chenyi Qiang <chenyi.qiang@intel.com>

```c
From patchwork Fri Nov  6 09:03:11 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Chenyi Qiang <chenyi.qiang@intel.com>
X-Patchwork-Id: 11886417
Return-Path: <SRS0=V6CK=EM=vger.kernel.org=kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-6.7 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,
	URIBL_BLOCKED,USER_AGENT_GIT autolearn=no autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 9DDBEC388F2
	for <kvm@archiver.kernel.org>; Fri,  6 Nov 2020 09:01:00 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 3F723216FD
	for <kvm@archiver.kernel.org>; Fri,  6 Nov 2020 09:01:00 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726295AbgKFJA5 (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Fri, 6 Nov 2020 04:00:57 -0500
Received: from mga09.intel.com ([134.134.136.24]:4550 "EHLO mga09.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1725835AbgKFJA4 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 6 Nov 2020 04:00:56 -0500
IronPort-SDR: 
 lsSwtWDvaGXhvgyFTk7sQb9GWdz72WMflXLwqsZX0qWv5YQlYU9HgRv0gbd4OhY4mEDE5o+f2v
 vZiW9UUsTWzQ==
X-IronPort-AV: E=McAfee;i="6000,8403,9796"; a="169670225"
X-IronPort-AV: E=Sophos;i="5.77,456,1596524400";
   d="scan'208";a="169670225"
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from orsmga004.jf.intel.com ([10.7.209.38])
  by orsmga102.jf.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 06 Nov 2020 01:00:55 -0800
IronPort-SDR: 
 t2MbEemj6vFM6wgVQZwHgK0M0sP+tvKKecZPtEXbbtpIgA5AI059nyVhiq15BeJmL0cyh14xGR
 CilcI/RY9vNA==
X-IronPort-AV: E=Sophos;i="5.77,456,1596524400";
   d="scan'208";a="472000251"
Received: from chenyi-pc.sh.intel.com ([10.239.159.72])
  by orsmga004-auth.jf.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 06 Nov 2020 01:00:52 -0800
From: Chenyi Qiang <chenyi.qiang@intel.com>
To: Paolo Bonzini <pbonzini@redhat.com>,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>,
        Xiaoyao Li <xiaoyao.li@intel.com>
Cc: kvm@vger.kernel.org, linux-kernel@vger.kernel.org
Subject: [PATCH v5 0/4] Add bus lock VM exit support
Date: Fri,  6 Nov 2020 17:03:11 +0800
Message-Id: <20201106090315.18606-1-chenyi.qiang@intel.com>
X-Mailer: git-send-email 2.17.1
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This patch series add the support for bus lock VM exit in KVM. It is a
sub-feature of bus lock detection. When it is enabled by the VMM, the
processor generates a "Bus Lock" VM exit following execution of an
instruction if the processor detects that one or more bus locks were
caused the instruction was being executed (due to either direct access
by the instruction or stuffed accesses like through A/D updates).

Bus lock VM exit will introduce a new modifier bit (bit 26) in
exit_reason field in VMCS which indicates bus lock VM exit is preempted
by a higher priority VM exit. The first patch is to apply Sean's
refactor for vcpu_vmx.exit_reason as a preparation patch for bus lock
VM exit support.

The second patch is the refactor for vcpu->run->flags. Bus lock VM exit
will introduce a new field in the flags to inform the userspace that
there's a bus lock detected in guest. It's also a preparation patch.

The third patch is the concrete enabling working for bus lock VM exit.
Add the support to set the capability to enable bus lock VM exit. The
current implementation is just exiting to userspace when handling the
bus lock detected in guest.

The detail of throttling policy in user space is still to be discussed.
We may enforce ratelimit on bus lock in guest, inject some sleep time,
or... We hope to get more ideas on this.

Document for Bus Lock Detection is now available at the latest "Intel
Architecture Instruction Set Extensions Programming Reference".

Document Link:
https://software.intel.com/content/www/us/en/develop/download/intel-architecture-instruction-set-extensions-programming-reference.html
---

Changelogs

v4->v5:
- rebase on top on v5.10-rc2
- add preparation patch that reset the vcpu->run->flags at the beginning
  of the vcpu_run.(Suggested by Sean)
- set the KVM_RUN_BUS_LOCK for all bus lock exit to avoid checking both
  exit_reason and run->flags
- add the document to introduce the new kvm capability
  (KVM_CAP_X86_BUS_LOCK_EXIT)
- v4:https://lore.kernel.org/lkml/20201012033542.4696-1-chenyi.qiang@intel.com/


v3->v4:
- rebase on top of v5.9
- some code cleanup.
- v3:https://lore.kernel.org/lkml/20200910083751.26686-1-chenyi.qiang@intel.com/

v2->v3:
- use a bitmap to get/set the capability of bus lock detection. we support
  exit and off mode currently.
- put the handle of exiting to userspace in vmx.c, thus no need to
  define a shadow to track vmx->exit_reason.bus_lock_detected.
- remove the vcpu->stats.bus_locks since every bus lock exits to userspace.
- v2:https://lore.kernel.org/lkml/20200817033604.5836-1-chenyi.qiang@intel.com/ 

v1->v2:
- resolve Vitaly's comment to introduce the KVM_EXIT_BUS_LOCK and a
  capability to enable it.
- add the support to exit to user space when handling bus locks.
- extend the vcpu->run->flags to indicate bus lock detected for other
  exit reasons when exiting to user space.
- v1:https://lore.kernel.org/lkml/20200628085341.5107-1-chenyi.qiang@intel.com/

---

Chenyi Qiang (3):
  KVM: X86: Reset the vcpu->run->flags at the beginning of vcpu_run
  KVM: VMX: Enable bus lock VM exit
  KVM: X86: Add the Document for KVM_CAP_X86_BUS_LOCK_EXIT

Sean Christopherson (1):
  KVM: VMX: Convert vcpu_vmx.exit_reason to a union

 Documentation/virt/kvm/api.rst     |  45 ++++++++++++-
 arch/x86/include/asm/kvm_host.h    |   7 ++
 arch/x86/include/asm/vmx.h         |   1 +
 arch/x86/include/asm/vmxfeatures.h |   1 +
 arch/x86/include/uapi/asm/kvm.h    |   1 +
 arch/x86/include/uapi/asm/vmx.h    |   4 +-
 arch/x86/kvm/vmx/capabilities.h    |   6 ++
 arch/x86/kvm/vmx/nested.c          |  42 +++++++-----
 arch/x86/kvm/vmx/vmx.c             | 105 +++++++++++++++++++----------
 arch/x86/kvm/vmx/vmx.h             |  25 ++++++-
 arch/x86/kvm/x86.c                 |  28 +++++++-
 include/uapi/linux/kvm.h           |   5 ++
 12 files changed, 214 insertions(+), 56 deletions(-)
```
