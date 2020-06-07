#### [RFC PATCH] KVM: x86: Fix APIC page invalidation race
##### From: Eiichi Tsukata <eiichi.tsukata@nutanix.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Eiichi Tsukata <eiichi.tsukata@nutanix.com>
X-Patchwork-Id: 11590973
Return-Path: <SRS0=6+TJ=7T=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 892A51391
	for <patchwork-kvm@patchwork.kernel.org>;
 Sat,  6 Jun 2020 04:36:43 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 70230206DC
	for <patchwork-kvm@patchwork.kernel.org>;
 Sat,  6 Jun 2020 04:36:43 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726203AbgFFEgj (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Sat, 6 Jun 2020 00:36:39 -0400
Received: from [192.146.154.243] ([192.146.154.243]:59784 "EHLO
        mcp01.nutanix.com" rhost-flags-FAIL-FAIL-OK-FAIL) by vger.kernel.org
        with ESMTP id S1725931AbgFFEgj (ORCPT <rfc822;kvm@vger.kernel.org>);
        Sat, 6 Jun 2020 00:36:39 -0400
X-Greylist: delayed 557 seconds by postgrey-1.27 at vger.kernel.org;
 Sat, 06 Jun 2020 00:36:39 EDT
Received: from C02Z20B5LVDL.corp.nutanix.com (unknown [10.150.245.9])
        by mcp01.nutanix.com (Postfix) with ESMTP id A26EB102CA91;
        Sat,  6 Jun 2020 04:27:18 +0000 (UTC)
From: Eiichi Tsukata <eiichi.tsukata@nutanix.com>
To: pbonzini@redhat.com, sean.j.christopherson@intel.com,
        vkuznets@redhat.com, wanpengli@tencent.com, jmattson@google.com,
        joro@8bytes.org, tglx@linutronix.de, mingo@redhat.com,
        bp@alien8.de, x86@kernel.org, hpa@zytor.com, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org
Cc: felipe.franciosi@nutanix.com, rkrcmar@redhat.com,
        Eiichi Tsukata <eiichi.tsukata@nutanix.com>
Subject: [RFC PATCH] KVM: x86: Fix APIC page invalidation race
Date: Sat,  6 Jun 2020 13:26:27 +0900
Message-Id: <20200606042627.61070-1-eiichi.tsukata@nutanix.com>
X-Mailer: git-send-email 2.25.0
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Commit b1394e745b94 ("KVM: x86: fix APIC page invalidation") tried to
fix inappropriate APIC page invalidation by re-introducing arch specific
kvm_arch_mmu_notifier_invalidate_range() and calling it from
kvm_mmu_notifier_invalidate_range_start. But threre could be the
following race because VMCS APIC address cache can be updated
*before* it is unmapped.

Race:
  (Invalidator) kvm_mmu_notifier_invalidate_range_start()
  (Invalidator) kvm_make_all_cpus_request(kvm, KVM_REQ_APIC_PAGE_RELOAD)
  (KVM VCPU) vcpu_enter_guest()
  (KVM VCPU) kvm_vcpu_reload_apic_access_page()
  (Invalidator) actually unmap page

Symptom:
  The above race can make Guest OS see already freed page and Guest OS
will see broken APIC register values. Especially, Windows OS checks
LAPIC modification so it can cause BSOD crash with BugCheck
CRITICAL_STRUCTURE_CORRUPTION (109). These symptoms are the same as we
previously saw in https://bugzilla.kernel.org/show_bug.cgi?id=197951 and
we are currently seeing in
https://bugzilla.redhat.com/show_bug.cgi?id=1751017.

To prevent Guest OS from accessing already freed page, this patch calls
kvm_arch_mmu_notifier_invalidate_range() from
kvm_mmu_notifier_invalidate_range() instead of ..._range_start().

Fixes: b1394e745b94 ("KVM: x86: fix APIC page invalidation")
Signed-off-by: Eiichi Tsukata <eiichi.tsukata@nutanix.com>
---
 arch/x86/kvm/x86.c       |  7 ++-----
 include/linux/kvm_host.h |  4 ++--
 virt/kvm/kvm_main.c      | 26 ++++++++++++++++----------
 3 files changed, 20 insertions(+), 17 deletions(-)

```
