

#### [PATCH v2 0/3] KVM: VMX: Fix for kexec VMCLEAR and VMXON cleanup
##### From: Sean Christopherson <sean.j.christopherson@intel.com>

```c
From patchwork Sat Mar 21 19:37:48 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Sean Christopherson <sean.j.christopherson@intel.com>
X-Patchwork-Id: 11451325
Return-Path: <SRS0=9K6R=5G=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 65CF413B1
	for <patchwork-kvm@patchwork.kernel.org>;
 Sat, 21 Mar 2020 19:38:09 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 4F3B42077D
	for <patchwork-kvm@patchwork.kernel.org>;
 Sat, 21 Mar 2020 19:38:09 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728091AbgCUTiF (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Sat, 21 Mar 2020 15:38:05 -0400
Received: from mga11.intel.com ([192.55.52.93]:55983 "EHLO mga11.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1727028AbgCUThz (ORCPT <rfc822;kvm@vger.kernel.org>);
        Sat, 21 Mar 2020 15:37:55 -0400
IronPort-SDR: 
 +Rx1ZYW07g0Ptr3eTy5pTl/0VFKi5XxeGN/1roJVNf32H7zeMrc4a2WpQARhhWP33u4enAmQH0
 jxK197J7eBYw==
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from fmsmga005.fm.intel.com ([10.253.24.32])
  by fmsmga102.fm.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 21 Mar 2020 12:37:53 -0700
IronPort-SDR: 
 WXb3xou5Qmr5WW8ex0hNZM+Ew9D7J/HSFYceqXfQGAiXC65lJSoEKuSP40uZ6LHZkD582big0+
 tsz1jHfT/rrg==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.72,289,1580803200";
   d="scan'208";a="445353676"
Received: from sjchrist-coffee.jf.intel.com ([10.54.74.202])
  by fmsmga005.fm.intel.com with ESMTP; 21 Mar 2020 12:37:52 -0700
From: Sean Christopherson <sean.j.christopherson@intel.com>
To: Paolo Bonzini <pbonzini@redhat.com>
Cc: Sean Christopherson <sean.j.christopherson@intel.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org
Subject: [PATCH v2 0/3] KVM: VMX: Fix for kexec VMCLEAR and VMXON cleanup
Date: Sat, 21 Mar 2020 12:37:48 -0700
Message-Id: <20200321193751.24985-1-sean.j.christopherson@intel.com>
X-Mailer: git-send-email 2.24.1
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Patch 1 fixes a a theoretical bug where a crashdump NMI that arrives
while KVM is messing with the percpu VMCS list would result in one or more
VMCSes not being cleared, potentially causing memory corruption in the new
kexec'd kernel.

Patch 2 is cleanup that's made possible by patch 1.

Patch 3 isn't directly related, but it conflicts with the crash cleanup
changes, both from a code and a semantics perspective.  Without the crash
cleanup, IMO hardware_enable() should do crash_disable_local_vmclear()
if VMXON fails, i.e. clean up after itself.  But hardware_disable()
doesn't even do crash_disable_local_vmclear() (which is what got me
looking at that code in the first place).  Basing the VMXON change on top
of the crash cleanup avoids the debate entirely.

v2:
  - Inverted the code flow, i.e. move code from loaded_vmcs_init() to
    __loaded_vmcs_clear().  Trying to share loaded_vmcs_init() with
    alloc_loaded_vmcs() was taking more code than it saved. [Paolo]


Gory details on the crashdump bug:

I verified my analysis of the NMI bug by simulating what would happen if
an NMI arrived in the middle of list_add() and list_del().  The below
output matches expectations, e.g. nothing hangs, the entry being added
doesn't show up, and the entry being deleted _does_ show up.

[    8.205898] KVM: testing NMI in list_add()
[    8.205898] KVM: testing NMI in list_del()
[    8.205899] KVM: found e3
[    8.205899] KVM: found e2
[    8.205899] KVM: found e1
[    8.205900] KVM: found e3
[    8.205900] KVM: found e1

static void vmx_test_list(struct list_head *list, struct list_head *e1,
                          struct list_head *e2, struct list_head *e3)
{
        struct list_head *tmp;

        list_for_each(tmp, list) {
                if (tmp == e1)
                        pr_warn("KVM: found e1\n");
                else if (tmp == e2)
                        pr_warn("KVM: found e2\n");
                else if (tmp == e3)
                        pr_warn("KVM: found e3\n");
                else
                        pr_warn("KVM: kaboom\n");
        }
}

static int __init vmx_init(void)
{
        LIST_HEAD(list);
        LIST_HEAD(e1);
        LIST_HEAD(e2);
        LIST_HEAD(e3);

        pr_warn("KVM: testing NMI in list_add()\n");

        list.next->prev = &e1;
        vmx_test_list(&list, &e1, &e2, &e3);

        e1.next = list.next;
        vmx_test_list(&list, &e1, &e2, &e3);

        e1.prev = &list;
        vmx_test_list(&list, &e1, &e2, &e3);

        INIT_LIST_HEAD(&list);
        INIT_LIST_HEAD(&e1);

        list_add(&e1, &list);
        list_add(&e2, &list);
        list_add(&e3, &list);

        pr_warn("KVM: testing NMI in list_del()\n");

        e3.prev = &e1;
        vmx_test_list(&list, &e1, &e2, &e3);

        list_del(&e2);
        list.prev = &e1;
        vmx_test_list(&list, &e1, &e2, &e3);
}

Sean Christopherson (3):
  KVM: VMX: Always VMCLEAR in-use VMCSes during crash with kexec support
  KVM: VMX: Fold loaded_vmcs_init() into alloc_loaded_vmcs()
  KVM: VMX: Gracefully handle faults on VMXON

 arch/x86/kvm/vmx/vmx.c | 103 ++++++++++++++++-------------------------
 arch/x86/kvm/vmx/vmx.h |   1 -
 2 files changed, 40 insertions(+), 64 deletions(-)
```
#### [PATCH v3 0/9]  KVM: Move x86 init ops to separate struct
##### From: Sean Christopherson <sean.j.christopherson@intel.com>

```c
From patchwork Sat Mar 21 20:25:54 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Sean Christopherson <sean.j.christopherson@intel.com>
X-Patchwork-Id: 11451337
Return-Path: <SRS0=9K6R=5G=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 5A20213B1
	for <patchwork-kvm@patchwork.kernel.org>;
 Sat, 21 Mar 2020 20:26:10 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 423802078B
	for <patchwork-kvm@patchwork.kernel.org>;
 Sat, 21 Mar 2020 20:26:10 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728059AbgCUU0I (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Sat, 21 Mar 2020 16:26:08 -0400
Received: from mga03.intel.com ([134.134.136.65]:8930 "EHLO mga03.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726846AbgCUU0I (ORCPT <rfc822;kvm@vger.kernel.org>);
        Sat, 21 Mar 2020 16:26:08 -0400
IronPort-SDR: 
 eFWtV/jdffBkXM4rVldq+kUR+7v4P0+e/PQZsWhjoIrgawmXlglnv9YqdZJV0qwWbLz5tsLmT4
 fl1VvdtnfLeQ==
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from fmsmga002.fm.intel.com ([10.253.24.26])
  by orsmga103.jf.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 21 Mar 2020 13:26:05 -0700
IronPort-SDR: 
 wc7DG86xh4vPeKd3LZfA/TbWv8x9O/HuKQW/jGF3O4aUFN/qKwYCQ8SRM7iJWo2KoQnsDSJboM
 NHtSa3M5ZLog==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.72,289,1580803200";
   d="scan'208";a="280773532"
Received: from sjchrist-coffee.jf.intel.com ([10.54.74.202])
  by fmsmga002.fm.intel.com with ESMTP; 21 Mar 2020 13:26:04 -0700
From: Sean Christopherson <sean.j.christopherson@intel.com>
To: Paolo Bonzini <pbonzini@redhat.com>
Cc: Paul Mackerras <paulus@ozlabs.org>,
        Christian Borntraeger <borntraeger@de.ibm.com>,
        Janosch Frank <frankja@linux.ibm.com>,
        David Hildenbrand <david@redhat.com>,
        Cornelia Huck <cohuck@redhat.com>,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>, Marc Zyngier <maz@kernel.org>,
        James Morse <james.morse@arm.com>,
        Julien Thierry <julien.thierry.kdev@gmail.com>,
        Suzuki K Poulose <suzuki.poulose@arm.com>,
        linux-mips@vger.kernel.org, kvm@vger.kernel.org,
        kvm-ppc@vger.kernel.org, linux-arm-kernel@lists.infradead.org,
        kvmarm@lists.cs.columbia.edu, linux-kernel@vger.kernel.org
Subject: [PATCH v3 0/9]  KVM: Move x86 init ops to separate struct
Date: Sat, 21 Mar 2020 13:25:54 -0700
Message-Id: <20200321202603.19355-1-sean.j.christopherson@intel.com>
X-Mailer: git-send-email 2.24.1
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The non-x86 part of this series is wholly contained in patch 01.  Compared
to other recent kvm-wide changes, this one is very straightforward (famous
last words).

Like a few other architectures, e.g. PPC, x86 uses a set of global hooks
to call back into vendor code on demand.  A handlful of the x86 hooks are
used only within the scope of kvm_init().  This series moves the init-only
hooks to a separate struct, partly to clean up the code a bit, but mainly
so that the runtime hooks can be made available only after the x86 vendor
has completed its ->hardware_setup().  While working on a different series
I spent a fair bit of time scratching my as to why a kvm_x86_ops wasn't
working, and eventually realized VMX's callback wasn't "ready" because the
vmcs_config hadn't yet been populated.

Due to lack of a cross-compiling setup, the non-x86 changes in patch 01
are untested.

v3:
 - Rebase to kvm/queue, d55c9d4009c7 ("KVM: nSVM: check for EFER ... ").
   Conflicts galore, but all mechanical in nature.
 - Drop an SVM patch that was obsoleted by kvm/queue.
 - Collect an ack. [Marc]

v2:
  - Rebase to kvm/queue, 2c2787938512 ("KVM: selftests: Stop ...")
  - Collect tags. [Cornelia]
  - Add a patch to make kvm_x86_ops its own instance and copy
    {vmx,svm}_x86_ops by value, which saves a memory access on every
    invocation of a kvm_x86_ops hook. [Paolo]
  - Add patches to tag {vmx,svm}_x86_ops as __initdata after they're
    copied by value.


Sean Christopherson (9):
  KVM: Pass kvm_init()'s opaque param to additional arch funcs
  KVM: x86: Move init-only kvm_x86_ops to separate struct
  KVM: VMX: Move hardware_setup() definition below vmx_x86_ops
  KVM: VMX: Configure runtime hooks using vmx_x86_ops
  KVM: x86: Set kvm_x86_ops only after ->hardware_setup() completes
  KVM: x86: Copy kvm_x86_ops by value to eliminate layer of indirection
  KVM: x86: Drop __exit from kvm_x86_ops' hardware_unsetup()
  KVM: VMX: Annotate vmx_x86_ops as __initdata
  KVM: SVM: Annotate svm_x86_ops as __initdata

 arch/mips/kvm/mips.c            |   4 +-
 arch/powerpc/kvm/powerpc.c      |   4 +-
 arch/s390/kvm/kvm-s390.c        |   4 +-
 arch/x86/include/asm/kvm_host.h |  33 +--
 arch/x86/kvm/cpuid.c            |   4 +-
 arch/x86/kvm/hyperv.c           |   8 +-
 arch/x86/kvm/kvm_cache_regs.h   |  10 +-
 arch/x86/kvm/lapic.c            |  30 +--
 arch/x86/kvm/mmu.h              |   8 +-
 arch/x86/kvm/mmu/mmu.c          |  32 +--
 arch/x86/kvm/pmu.c              |  30 +--
 arch/x86/kvm/pmu.h              |   2 +-
 arch/x86/kvm/svm.c              |  19 +-
 arch/x86/kvm/trace.h            |   4 +-
 arch/x86/kvm/vmx/nested.c       |  17 +-
 arch/x86/kvm/vmx/nested.h       |   3 +-
 arch/x86/kvm/vmx/vmx.c          | 371 ++++++++++++++++----------------
 arch/x86/kvm/x86.c              | 370 +++++++++++++++----------------
 arch/x86/kvm/x86.h              |   4 +-
 include/linux/kvm_host.h        |   4 +-
 virt/kvm/arm/arm.c              |   4 +-
 virt/kvm/kvm_main.c             |  18 +-
 22 files changed, 507 insertions(+), 476 deletions(-)
```
