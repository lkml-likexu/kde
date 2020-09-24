#### [PATCH] irqchip/gic-v4.1: Optimize the wait for the completion of the analysis of the VPT
##### From: Shenming Lu <lushenming@huawei.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Shenming Lu <lushenming@huawei.com>
X-Patchwork-Id: 11794097
Return-Path: <SRS0=+e/I=DA=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 6012116BC
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 23 Sep 2020 06:36:50 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 503D9221F0
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 23 Sep 2020 06:36:50 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726723AbgIWGgq (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 23 Sep 2020 02:36:46 -0400
Received: from szxga06-in.huawei.com ([45.249.212.32]:42828 "EHLO huawei.com"
        rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org with ESMTP
        id S1726179AbgIWGgp (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 23 Sep 2020 02:36:45 -0400
Received: from DGGEMS409-HUB.china.huawei.com (unknown [172.30.72.60])
        by Forcepoint Email with ESMTP id 0E9B157AA3323F5A97F2;
        Wed, 23 Sep 2020 14:36:41 +0800 (CST)
Received: from DESKTOP-7FEPK9S.china.huawei.com (10.174.186.62) by
 DGGEMS409-HUB.china.huawei.com (10.3.19.209) with Microsoft SMTP Server id
 14.3.487.0; Wed, 23 Sep 2020 14:36:33 +0800
From: Shenming Lu <lushenming@huawei.com>
To: Thomas Gleixner <tglx@linutronix.de>,
        Jason Cooper <jason@lakedaemon.net>,
        Marc Zyngier <maz@kernel.org>, <linux-kernel@vger.kernel.org>,
        <linux-arm-kernel@lists.infradead.org>,
        <kvmarm@lists.cs.columbia.edu>, <kvm@vger.kernel.org>,
        James Morse <james.morse@arm.com>,
        Julien Thierry <julien.thierry.kdev@gmail.com>,
        Suzuki K Poulose <suzuki.poulose@arm.com>,
        Catalin Marinas <catalin.marinas@arm.com>,
        Will Deacon <will@kernel.org>,
        Eric Auger <eric.auger@redhat.com>,
        Christoffer Dall <christoffer.dall@arm.com>
CC: <wanghaibin.wang@huawei.com>, <yuzenghui@huawei.com>,
        <lushenming@huawei.com>
Subject: [PATCH] irqchip/gic-v4.1: Optimize the wait for the completion of the
 analysis of the VPT
Date: Wed, 23 Sep 2020 14:35:43 +0800
Message-ID: <20200923063543.1920-1-lushenming@huawei.com>
X-Mailer: git-send-email 2.27.0.windows.1
MIME-Version: 1.0
X-Originating-IP: [10.174.186.62]
X-CFilter-Loop: Reflected
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Right after a vPE is made resident, the code starts polling the
GICR_VPENDBASER.Dirty bit until it becomes 0, where the delay_us
is set to 10. But in our measurement, it takes only hundreds of
nanoseconds, or 1~2 microseconds, to finish parsing the VPT in most
cases. And we also measured the time from vcpu_load() (include it)
to __guest_enter() on Kunpeng 920. On average, it takes 2.55 microseconds
(not first run && the VPT is empty). So 10 microseconds delay might
really hurt performance.

To avoid this, we can set the delay_us to 1, which is more appropriate
in this situation and universal. Besides, we can delay the execution
of its_wait_vpt_parse_complete() (call it from kvm_vgic_flush_hwstate()
corresponding to vPE resident), giving the GIC a chance to work in
parallel with the CPU on the entry path.

Signed-off-by: Shenming Lu <lushenming@huawei.com>
---
 arch/arm64/kvm/vgic/vgic-v4.c      | 18 ++++++++++++++++++
 arch/arm64/kvm/vgic/vgic.c         |  2 ++
 drivers/irqchip/irq-gic-v3-its.c   | 14 +++++++++++---
 drivers/irqchip/irq-gic-v4.c       | 11 +++++++++++
 include/kvm/arm_vgic.h             |  3 +++
 include/linux/irqchip/arm-gic-v4.h |  4 ++++
 6 files changed, 49 insertions(+), 3 deletions(-)

```
#### [PATCH] KVM: Enable hardware before doing arch VM initialization
##### From: Sean Christopherson <sean.j.christopherson@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Sean Christopherson <sean.j.christopherson@intel.com>
X-Patchwork-Id: 11795527
Return-Path: <SRS0=+e/I=DA=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 04BF9112E
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 23 Sep 2020 18:58:07 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id E1987221EF
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 23 Sep 2020 18:58:06 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726820AbgIWS6D (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 23 Sep 2020 14:58:03 -0400
Received: from mga03.intel.com ([134.134.136.65]:49884 "EHLO mga03.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726703AbgIWS6D (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 23 Sep 2020 14:58:03 -0400
IronPort-SDR: 
 rmoKL4TAEmrTdEmJfp7uNXhbdy0Fk4yTAu6sdqA0tsRz1StnLsxi6hhA9vE/r/PERcPAcKvQ0j
 i1QvBR5AOL6g==
X-IronPort-AV: E=McAfee;i="6000,8403,9753"; a="161072561"
X-IronPort-AV: E=Sophos;i="5.77,293,1596524400";
   d="scan'208";a="161072561"
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from orsmga008.jf.intel.com ([10.7.209.65])
  by orsmga103.jf.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 23 Sep 2020 11:58:02 -0700
IronPort-SDR: 
 kz7/UhdqfQR7kPq/UutKfm67dCkSO0dRSAPU6xHrzv6Gh4iZ9RoV4ILoENHljI/FS+ll6XOVeH
 kxkn4Ig0AyyQ==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.77,293,1596524400";
   d="scan'208";a="338759550"
Received: from sjchrist-coffee.jf.intel.com ([10.54.74.160])
  by orsmga008.jf.intel.com with ESMTP; 23 Sep 2020 11:58:02 -0700
From: Sean Christopherson <sean.j.christopherson@intel.com>
To: Paolo Bonzini <pbonzini@redhat.com>
Cc: kvm@vger.kernel.org, linux-kernel@vger.kernel.org,
        Marc Zyngier <maz@kernel.org>,
        James Morse <james.morse@arm.com>,
        Julien Thierry <julien.thierry.kdev@gmail.com>,
        Suzuki K Poulose <suzuki.poulose@arm.com>,
        linux-arm-kernel@lists.infradead.org,
        Huacai Chen <chenhc@lemote.com>,
        Aleksandar Markovic <aleksandar.qemu.devel@gmail.com>,
        linux-mips@vger.kernel.org, Paul Mackerras <paulus@ozlabs.org>,
        kvm-ppc@vger.kernel.org,
        Christian Borntraeger <borntraeger@de.ibm.com>,
        Janosch Frank <frankja@linux.ibm.com>,
        David Hildenbrand <david@redhat.com>,
        Cornelia Huck <cohuck@redhat.com>,
        Claudio Imbrenda <imbrenda@linux.ibm.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>,
        Sean Christopherson <sean.j.christopherson@intel.com>
Subject: [PATCH] KVM: Enable hardware before doing arch VM initialization
Date: Wed, 23 Sep 2020 11:57:57 -0700
Message-Id: <20200923185757.1806-1-sean.j.christopherson@intel.com>
X-Mailer: git-send-email 2.28.0
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Swap the order of hardware_enable_all() and kvm_arch_init_vm() to
accommodate Intel's Trust Domain Extension (TDX), which needs VMX to be
fully enabled during VM init in order to make SEAMCALLs.

This also provides consistent ordering between kvm_create_vm() and
kvm_destroy_vm() with respect to calling kvm_arch_destroy_vm() and
hardware_disable_all().

Cc: Marc Zyngier <maz@kernel.org>
Cc: James Morse <james.morse@arm.com>
Cc: Julien Thierry <julien.thierry.kdev@gmail.com>
Cc: Suzuki K Poulose <suzuki.poulose@arm.com>
Cc: linux-arm-kernel@lists.infradead.org
Cc: Huacai Chen <chenhc@lemote.com>
Cc: Aleksandar Markovic <aleksandar.qemu.devel@gmail.com>
Cc: linux-mips@vger.kernel.org
Cc: Paul Mackerras <paulus@ozlabs.org>
Cc: kvm-ppc@vger.kernel.org
Cc: Christian Borntraeger <borntraeger@de.ibm.com>
Cc: Janosch Frank <frankja@linux.ibm.com>
Cc: David Hildenbrand <david@redhat.com>
Cc: Cornelia Huck <cohuck@redhat.com>
Cc: Claudio Imbrenda <imbrenda@linux.ibm.com>
Cc: Vitaly Kuznetsov <vkuznets@redhat.com>
Cc: Wanpeng Li <wanpengli@tencent.com>
Cc: Jim Mattson <jmattson@google.com>
Cc: Joerg Roedel <joro@8bytes.org>
Signed-off-by: Sean Christopherson <sean.j.christopherson@intel.com>
---

Obviously not required until the TDX series comes along, but IMO KVM
should be consistent with respect to enabling and disabling virt support
in hardware.

Tested only on Intel hardware.  Unless I missed something, this only
affects x86, Arm and MIPS as hardware enabling is a nop for s390 and PPC.
Arm looks safe (based on my mostly clueless reading of the code), but I
have no idea if this will cause problem for MIPS, which is doing all kinds
of things in hardware_enable() that I don't pretend to fully understand.

 virt/kvm/kvm_main.c | 16 ++++++++--------
 1 file changed, 8 insertions(+), 8 deletions(-)

```
#### [RFC PATCH 1/3] KVM: Export kvm_make_all_cpus_request() for use in marking VMs as bugged
##### From: Sean Christopherson <sean.j.christopherson@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Sean Christopherson <sean.j.christopherson@intel.com>
X-Patchwork-Id: 11795757
Return-Path: <SRS0=+e/I=DA=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 6905392C
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 23 Sep 2020 22:45:47 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 5062D2075B
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 23 Sep 2020 22:45:47 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726718AbgIWWpe (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 23 Sep 2020 18:45:34 -0400
Received: from mga02.intel.com ([134.134.136.20]:41185 "EHLO mga02.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726265AbgIWWpd (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 23 Sep 2020 18:45:33 -0400
IronPort-SDR: 
 1CLFeOuXlndzv/a71UJbQaxILER9dtcyZ1+LszpAHnc/NNLi7ehfQSYlMSDf0jlLh5sSENMyQa
 akbgWk+f4GwQ==
X-IronPort-AV: E=McAfee;i="6000,8403,9753"; a="148698558"
X-IronPort-AV: E=Sophos;i="5.77,295,1596524400";
   d="scan'208";a="148698558"
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from fmsmga004.fm.intel.com ([10.253.24.48])
  by orsmga101.jf.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 23 Sep 2020 15:45:32 -0700
IronPort-SDR: 
 u+HZL/FRvN5hFKQCaIsv/2670WJRfryOYunFtJVpVNRHMY+2OpH2Z6iXvqLoZlxPrdxJO4Oga5
 RBRJrIvxzjuQ==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.77,295,1596524400";
   d="scan'208";a="335660062"
Received: from sjchrist-coffee.jf.intel.com ([10.54.74.160])
  by fmsmga004.fm.intel.com with ESMTP; 23 Sep 2020 15:45:32 -0700
From: Sean Christopherson <sean.j.christopherson@intel.com>
To: Paolo Bonzini <pbonzini@redhat.com>
Cc: Sean Christopherson <sean.j.christopherson@intel.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org, Marc Zyngier <maz@kernel.org>,
        James Morse <james.morse@arm.com>,
        Julien Thierry <julien.thierry.kdev@gmail.com>,
        Suzuki K Poulose <suzuki.poulose@arm.com>,
        linux-arm-kernel@lists.infradead.org,
        Huacai Chen <chenhc@lemote.com>,
        Aleksandar Markovic <aleksandar.qemu.devel@gmail.com>,
        linux-mips@vger.kernel.org, Paul Mackerras <paulus@ozlabs.org>,
        kvm-ppc@vger.kernel.org,
        Christian Borntraeger <borntraeger@de.ibm.com>,
        Janosch Frank <frankja@linux.ibm.com>,
        David Hildenbrand <david@redhat.com>,
        Cornelia Huck <cohuck@redhat.com>,
        Claudio Imbrenda <imbrenda@linux.ibm.com>
Subject: [RFC PATCH 1/3] KVM: Export kvm_make_all_cpus_request() for use in
 marking VMs as bugged
Date: Wed, 23 Sep 2020 15:45:28 -0700
Message-Id: <20200923224530.17735-2-sean.j.christopherson@intel.com>
X-Mailer: git-send-email 2.28.0
In-Reply-To: <20200923224530.17735-1-sean.j.christopherson@intel.com>
References: <20200923224530.17735-1-sean.j.christopherson@intel.com>
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Export kvm_make_all_cpus_request() and hoist the request helper
declarations of request up to the KVM_REQ_* definitions in preparation
for adding a "VM bugged" framework.  The framework will add KVM_BUG()
and KVM_BUG_ON() as alternatives to full BUG()/BUG_ON() for cases where
KVM has definitely hit a bug (in itself or in silicon) and the VM is all
but guaranteed to be hosed.  Marking a VM bugged will trigger a request
to all vCPUs to allow arch code to forcefully evict each vCPU from its
run loop.

Signed-off-by: Sean Christopherson <sean.j.christopherson@intel.com>
---
 include/linux/kvm_host.h | 18 +++++++++---------
 virt/kvm/kvm_main.c      |  1 +
 2 files changed, 10 insertions(+), 9 deletions(-)

```
#### [PATCH v2 1/7] KVM: nVMX: Reset the segment cache when stuffing guest segs
##### From: Sean Christopherson <sean.j.christopherson@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Sean Christopherson <sean.j.christopherson@intel.com>
X-Patchwork-Id: 11795523
Return-Path: <SRS0=+e/I=DA=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 85B49618
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 23 Sep 2020 18:45:30 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 720A62053B
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 23 Sep 2020 18:45:30 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726992AbgIWSp1 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 23 Sep 2020 14:45:27 -0400
Received: from mga07.intel.com ([134.134.136.100]:14506 "EHLO mga07.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726487AbgIWSoy (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 23 Sep 2020 14:44:54 -0400
IronPort-SDR: 
 lYVYORvuiGnQpiGL6gJCW2XHjrIHWetwCYE2C9FnSzkKniUtGOUtF0UaFQlug2CS7H5WY6+VEA
 QoieX+LXRayA==
X-IronPort-AV: E=McAfee;i="6000,8403,9753"; a="225124471"
X-IronPort-AV: E=Sophos;i="5.77,293,1596524400";
   d="scan'208";a="225124471"
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from fmsmga003.fm.intel.com ([10.253.24.29])
  by orsmga105.jf.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 23 Sep 2020 11:44:53 -0700
IronPort-SDR: 
 raRX+UdgFpVe0RwVtA3YHBB4KtQmsIqt3dXRq+oX7WgMMhcnsZK0vmJbUXMCzfcheJY3kDUVsD
 MjTCj77I07qg==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.77,293,1596524400";
   d="scan'208";a="347457646"
Received: from sjchrist-coffee.jf.intel.com ([10.54.74.160])
  by FMSMGA003.fm.intel.com with ESMTP; 23 Sep 2020 11:44:53 -0700
From: Sean Christopherson <sean.j.christopherson@intel.com>
To: Paolo Bonzini <pbonzini@redhat.com>
Cc: Sean Christopherson <sean.j.christopherson@intel.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org, Dan Cross <dcross@google.com>,
        Peter Shier <pshier@google.com>
Subject: [PATCH v2 1/7] KVM: nVMX: Reset the segment cache when stuffing guest
 segs
Date: Wed, 23 Sep 2020 11:44:46 -0700
Message-Id: <20200923184452.980-2-sean.j.christopherson@intel.com>
X-Mailer: git-send-email 2.28.0
In-Reply-To: <20200923184452.980-1-sean.j.christopherson@intel.com>
References: <20200923184452.980-1-sean.j.christopherson@intel.com>
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Explicitly reset the segment cache after stuffing guest segment regs in
prepare_vmcs02_rare().  Although the cache is reset when switching to
vmcs02, there is nothing that prevents KVM from re-populating the cache
prior to writing vmcs02 with vmcs12's values.  E.g. if the vCPU is
preempted after switching to vmcs02 but before prepare_vmcs02_rare(),
kvm_arch_vcpu_put() will dereference GUEST_SS_AR_BYTES via .get_cpl()
and cache the stale vmcs02 value.  While the current code base only
caches stale data in the preemption case, it's theoretically possible
future code could read a segment register during the nested flow itself,
i.e. this isn't technically illegal behavior in kvm_arch_vcpu_put(),
although it did introduce the bug.

This manifests as an unexpected nested VM-Enter failure when running
with unrestricted guest disabled if the above preemption case coincides
with L1 switching L2's CPL, e.g. when switching from a L2 vCPU at CPL3
to to a L2 vCPU at CPL0.  stack_segment_valid() will see the new SS_SEL
but the old SS_AR_BYTES and incorrectly mark the guest state as invalid
due to SS.dpl != SS.rpl.

Don't bother updating the cache even though prepare_vmcs02_rare() writes
every segment.  With unrestricted guest, guest segments are almost never
read, let alone L2 guest segments.  On the other hand, populating the
cache requires a large number of memory writes, i.e. it's unlikely to be
a net win.  Updating the cache would be a win when unrestricted guest is
not supported, as guest_state_valid() will immediately cache all segment
registers.  But, nested virtualization without unrestricted guest is
dirt slow, saving some VMREADs won't change that, and every CPU
manufactured in the last decade supports unrestricted guest.  In other
words, the extra (minor) complexity isn't worth the trouble.

Note, kvm_arch_vcpu_put() may see stale data when querying guest CPL
depending on when preemption occurs.  This is "ok" in that the usage is
imperfect by nature, i.e. it's used heuristically to improve performance
but doesn't affect functionality.  kvm_arch_vcpu_put() could be "fixed"
by also disabling preemption while loading segments, but that's
pointless and misleading as reading state from kvm_sched_{in,out}() is
guaranteed to see stale data in one form or another.  E.g. even if all
the usage of regs_avail is fixed to call kvm_register_mark_available()
after the associated state is set, the individual state might still be
stale with respect to the overall vCPU state.  I.e. making functional
decisions in an asynchronous hook is doomed from the get go.  Thankfully
KVM doesn't do that.

Fixes: de63ad4cf4973 ("KVM: X86: implement the logic for spinlock optimization")
Cc: stable@vger.kernel.org
Signed-off-by: Sean Christopherson <sean.j.christopherson@intel.com>
---
 arch/x86/kvm/vmx/nested.c | 2 ++
 1 file changed, 2 insertions(+)

```
#### [PATCH] KVM: SEV: shorten comments around sev_clflush_pages
##### From: Paolo Bonzini <pbonzini@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Paolo Bonzini <pbonzini@redhat.com>
X-Patchwork-Id: 11795319
Return-Path: <SRS0=+e/I=DA=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 04F04112E
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 23 Sep 2020 17:34:09 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id D5FB32053B
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 23 Sep 2020 17:34:08 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="A/P9ypsa"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726723AbgIWReH (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 23 Sep 2020 13:34:07 -0400
Received: from us-smtp-delivery-124.mimecast.com ([63.128.21.124]:29075 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1726360AbgIWReH (ORCPT
        <rfc822;kvm@vger.kernel.org>); Wed, 23 Sep 2020 13:34:07 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1600882447;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=ldfka2JU/8jYBcA7GSDSVnVY22PnP+CZq+UK9hEXQUs=;
        b=A/P9ypsalSVVr7L7mTSqSfPCFiaoVl1tpzQ6uQu10CZbN0XfzpSYYA6y4XpC1CGOGp103l
        jKAAN/lpIcgsrJgEuGpYpQyMY6M9zKniTmnXAgXe6KhVDig2GmgsH6dJXmvtf/NCcY5fXB
        1yLyAWkIJzAbf0t3VAaFJsH/nVS/q/U=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-406--llZzXH6MFadSR-JdG7y4w-1; Wed, 23 Sep 2020 13:34:04 -0400
X-MC-Unique: -llZzXH6MFadSR-JdG7y4w-1
Received: from smtp.corp.redhat.com (int-mx06.intmail.prod.int.phx2.redhat.com
 [10.5.11.16])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 0BCDE1800D42;
        Wed, 23 Sep 2020 17:34:03 +0000 (UTC)
Received: from virtlab701.virt.lab.eng.bos.redhat.com
 (virtlab701.virt.lab.eng.bos.redhat.com [10.19.152.228])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 9D24D5C230;
        Wed, 23 Sep 2020 17:34:02 +0000 (UTC)
From: Paolo Bonzini <pbonzini@redhat.com>
To: linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Cc: Sean Christopherson <sean.j.christopherson@intel.com>
Subject: [PATCH] KVM: SEV: shorten comments around sev_clflush_pages
Date: Wed, 23 Sep 2020 13:34:01 -0400
Message-Id: <20200923173401.1632172-1-pbonzini@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.16
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Very similar content is present in four comments in sev.c.  Unfortunately
there are small differences that make it harder to place the comment
in sev_clflush_pages itself, but at least we can make it more concise.

Suggested-by: Sean Christopherson <sean.j.christopherson@intel.com>
Signed-off-by: Paolo Bonzini <pbonzini@redhat.com>
Reviewed-by: Sean Christopherson <sean.j.christopherson@intel.com>
---
 arch/x86/kvm/svm/sev.c | 19 +++++++------------
 1 file changed, 7 insertions(+), 12 deletions(-)

```
#### [PATCH] KVM: SVM: Add a dedicated INVD intercept routine
##### From: Tom Lendacky <thomas.lendacky@amd.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Tom Lendacky <thomas.lendacky@amd.com>
X-Patchwork-Id: 11795649
Return-Path: <SRS0=+e/I=DA=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 4EC27618
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 23 Sep 2020 20:28:12 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 0FFC620725
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 23 Sep 2020 20:28:12 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=amdcloud.onmicrosoft.com
 header.i=@amdcloud.onmicrosoft.com header.b="BH8WJGLl"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726694AbgIWU2J (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 23 Sep 2020 16:28:09 -0400
Received: from mail-dm6nam11on2045.outbound.protection.outlook.com
 ([40.107.223.45]:11872
        "EHLO NAM11-DM6-obe.outbound.protection.outlook.com"
        rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org with ESMTP
        id S1726199AbgIWU2H (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 23 Sep 2020 16:28:07 -0400
ARC-Seal: i=1; a=rsa-sha256; s=arcselector9901; d=microsoft.com; cv=none;
 b=iC6hEjYwES5xsXcfuOU4nDpXDY+uz0laV7XOsf4NIRywLbRxe+P/cYW6n8eL5odKKt9KChOIS+Ejxm41rfdZkKNvJ2GsHkS7ptPsRzfkuaVKyOm4q+5gHsAjLfDq9LsdaHoMuvul3f+280D5e9ZH0YuTNf9PqpuXGjc0c4K1PD8Pxx+YWWw+4Whdq6jP4sDwZzAp7up8ui/8vVpI12f2MN1UKgVGHB0tt+7+iSMV6NYCxnQUzDFUyUMD8hoELsRqIje7ZSNvgxcUCGE8frHzgw3sSu/pTF57ubG1nBa5n3PPiD270WRD93RdY62QH2wq+EQ84vs+laYAyoO9Lcv1pA==
ARC-Message-Signature: i=1; a=rsa-sha256; c=relaxed/relaxed; d=microsoft.com;
 s=arcselector9901;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=D4loEgnr+Ig69yh+8W4ZGfx8KH/CpACJ+X6rYNjh8s0=;
 b=Jg+oMX9sQ02PI1TehNNZqKI4c8CAQONY7ibi86wQvVbW13iV/4HOw+rVCi/DAVO3YyRsvu/H6inEws4qQFSLXfGaaElALuVm1kXaLf8LMeFVZTIezovOntH/ClLCYzJ1AQp/djBGuiOZLX9+I1Ve2eMUtcyxu2wPam6AS/BPd8LgJ1BYC3FaDjBZNS5P4AXVW91nhVJxgMFCcmRsqzKQuQ1sdl3AAlpYlmunU5f0zIyg8YR5ZH+RdCrVMwzAEHC21iK1OmkeXiSNSH33YrGTQm+Twcg8bH+Lh0r8mUeTp9keUsLofzVjsCtABpsLA7XjKALKLADCHXJjo2n3umN7jg==
ARC-Authentication-Results: i=1; mx.microsoft.com 1; spf=pass
 smtp.mailfrom=amd.com; dmarc=pass action=none header.from=amd.com; dkim=pass
 header.d=amd.com; arc=none
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
 d=amdcloud.onmicrosoft.com; s=selector2-amdcloud-onmicrosoft-com;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=D4loEgnr+Ig69yh+8W4ZGfx8KH/CpACJ+X6rYNjh8s0=;
 b=BH8WJGLlewOzkM46xgntAYexK2/sv0Pa/I660pBC9rOqX6lStR3fpovyiVDnmOAHu2ZHRypFefaTJuTyqgLxtkZDUkZY1VzejZM2Y50N8A0Pz1flAoRORKiFMhfDxB2TI8AFSlDjQbG62axmasxFHBT+i/DbMquanoztRmr5z1I=
Authentication-Results: vger.kernel.org; dkim=none (message not signed)
 header.d=none;vger.kernel.org; dmarc=none action=none header.from=amd.com;
Received: from DM5PR12MB1355.namprd12.prod.outlook.com (2603:10b6:3:6e::7) by
 DM5PR12MB1451.namprd12.prod.outlook.com (2603:10b6:4:d::12) with Microsoft
 SMTP Server (version=TLS1_2, cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id
 15.20.3412.20; Wed, 23 Sep 2020 20:28:05 +0000
Received: from DM5PR12MB1355.namprd12.prod.outlook.com
 ([fe80::299a:8ed2:23fc:6346]) by DM5PR12MB1355.namprd12.prod.outlook.com
 ([fe80::299a:8ed2:23fc:6346%3]) with mapi id 15.20.3391.024; Wed, 23 Sep 2020
 20:28:05 +0000
From: Tom Lendacky <thomas.lendacky@amd.com>
To: kvm@vger.kernel.org, x86@kernel.org, linux-kernel@vger.kernel.org
Cc: Paolo Bonzini <pbonzini@redhat.com>,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>,
        Brijesh Singh <brijesh.singh@amd.com>,
        Thomas Gleixner <tglx@linutronix.de>,
        Ingo Molnar <mingo@redhat.com>, Borislav Petkov <bp@alien8.de>,
        "H. Peter Anvin" <hpa@zytor.com>
Subject: [PATCH] KVM: SVM: Add a dedicated INVD intercept routine
Date: Wed, 23 Sep 2020 15:27:39 -0500
Message-Id: 
 <16f36f9a51608758211c54564cd17c8b909372f1.1600892859.git.thomas.lendacky@amd.com>
X-Mailer: git-send-email 2.28.0
X-ClientProxiedBy: SN4PR0501CA0066.namprd05.prod.outlook.com
 (2603:10b6:803:41::43) To DM5PR12MB1355.namprd12.prod.outlook.com
 (2603:10b6:3:6e::7)
MIME-Version: 1.0
X-MS-Exchange-MessageSentRepresentingType: 1
Received: from tlendack-t1.amd.com (165.204.77.1) by
 SN4PR0501CA0066.namprd05.prod.outlook.com (2603:10b6:803:41::43) with
 Microsoft SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.3412.15 via Frontend
 Transport; Wed, 23 Sep 2020 20:28:03 +0000
X-Mailer: git-send-email 2.28.0
X-Originating-IP: [165.204.77.1]
X-MS-PublicTrafficType: Email
X-MS-Office365-Filtering-HT: Tenant
X-MS-Office365-Filtering-Correlation-Id: d9389b83-25b2-407e-4a66-08d85fff2cdd
X-MS-TrafficTypeDiagnostic: DM5PR12MB1451:
X-MS-Exchange-Transport-Forked: True
X-Microsoft-Antispam-PRVS: 
 <DM5PR12MB1451B87A119CFD770A88665AEC380@DM5PR12MB1451.namprd12.prod.outlook.com>
X-MS-Oob-TLC-OOBClassifiers: OLM:6430;
X-MS-Exchange-SenderADCheck: 1
X-Microsoft-Antispam: BCL:0;
X-Microsoft-Antispam-Message-Info: 
 Eja95YJxMunuaKuLdzCc0Gvco/g7cu8YAln0UJWUYIiCtctvjR9XEK0Up717ibg8VK1mJY9nzWcFpHSNHIyVuqnMIRaI3426lXiAKOJbRbu0NxZKOtrxHxG6I1/aSh9izx6CVJF04Z9DwhVn0QKC8PUFD0o1Y506mNb2Wx68jEaHPn/GueChZdXHcQtY8avVKNI15viSn5UDqCnCy+/J1ILowOPQp4DT00U6qIY1wHL/1vo6SzHNB7RmK8N3W6lP6ykSovauiqmtXoukKI23SUNHEReOd8ku5kPuuYJLJMgm78MyJzNVcf01Bt1j+eFvOfYqq52EkpE3OAhrzOqMbUULsf5UevLt5XNXNp6MQesyoXw9E7CXqybmhUL+Kc68
X-Forefront-Antispam-Report: 
 CIP:255.255.255.255;CTRY:;LANG:en;SCL:1;SRV:;IPV:NLI;SFV:NSPM;H:DM5PR12MB1355.namprd12.prod.outlook.com;PTR:;CAT:NONE;SFS:(4636009)(366004)(396003)(346002)(39860400002)(136003)(376002)(16526019)(8676002)(2616005)(956004)(186003)(8936002)(7416002)(36756003)(4326008)(83380400001)(66556008)(6666004)(66946007)(2906002)(316002)(478600001)(5660300002)(66476007)(6486002)(54906003)(26005)(52116002)(7696005)(86362001);DIR:OUT;SFP:1101;
X-MS-Exchange-AntiSpam-MessageData: 
 L5MZLM8InWyqFXAOpAIuMfEwYm8n/mXUcRmBHOY5kxU3ii9nDcWO/p+5i96F7+Riu9bBa6z9eV/8ln2s7wI5NX8+z59MlEBZcSbwA11fDjkakTRuV+3vq9Q3M8HyRqtqJC98EYBPXHDzNy/2Tw8qnv1oABojKXlupejYGBSD3T6R2SjTr1NFpDtPJebIl3gBPLR3V9e+StWC/+x46qnopUrbiYZG2KLCUpnMzo1SSSxL2FO+hEjRpfXji53QZYZRfSjCp9ajwvRZi75z5OlRRtYA1vRvrRFqDMrI0hZZ/lOfp9Fpx06yYwZ39vSIjZeF/fWMYpXSo4gFJASywYgKRJZVPAUJlq/WEe6bcyKdOkwPnTrf08ZhxCOGOPTqf2JtTztSouub46XncU7RozqJGzVzIj4nQXhe9m+nT5y5Z1Z/pG7bHOuiuqT5Aei4xtMx2bfmnQDDuzDHZK6WVBJ/T+4gNjX+iNU96OhpEK5Zw6MV/LxJQSEFgwBpAA7n0/iIq+7V1VKdnIqmxdd8kzyTNbIsMUlIN2nG/GjLkE8dLohMP4re8sAFGGdvh2nF8gx1tsErcBovbl7kCCWTL0wCb5/JyhmEEWhxnasU/vG0MLp1Wt5YhNSjKTmNnW9sUBPEW/c5/9fdlJTxiODe6apevQ==
X-OriginatorOrg: amd.com
X-MS-Exchange-CrossTenant-Network-Message-Id: 
 d9389b83-25b2-407e-4a66-08d85fff2cdd
X-MS-Exchange-CrossTenant-AuthSource: DM5PR12MB1355.namprd12.prod.outlook.com
X-MS-Exchange-CrossTenant-AuthAs: Internal
X-MS-Exchange-CrossTenant-OriginalArrivalTime: 23 Sep 2020 20:28:04.9483
 (UTC)
X-MS-Exchange-CrossTenant-FromEntityHeader: Hosted
X-MS-Exchange-CrossTenant-Id: 3dd8961f-e488-4e60-8e11-a82d994e183d
X-MS-Exchange-CrossTenant-MailboxType: HOSTED
X-MS-Exchange-CrossTenant-UserPrincipalName: 
 x7l7PYWhxPtmMYcTtn9tIQTstl9c3lRy0GPPLTYg6kT6vomnPAVocjDiCLeCYcaj6mE+TY2XJ0y6miAmefBKww==
X-MS-Exchange-Transport-CrossTenantHeadersStamped: DM5PR12MB1451
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Tom Lendacky <thomas.lendacky@amd.com>

The INVD instruction intercept performs emulation. Emulation can't be done
on an SEV guest because the guest memory is encrypted.

Provide a dedicated intercept routine for the INVD intercept. Within this
intercept routine just skip the instruction for an SEV guest, since it is
emulated as a NOP anyway.

Fixes: 1654efcbc431 ("KVM: SVM: Add KVM_SEV_INIT command")
Signed-off-by: Tom Lendacky <thomas.lendacky@amd.com>
---
 arch/x86/kvm/svm/svm.c | 13 ++++++++++++-
 1 file changed, 12 insertions(+), 1 deletion(-)

```
#### [kvm-unit-tests PATCH] travis.yml: Fix the getopt problem
##### From: Thomas Huth <thuth@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Thomas Huth <thuth@redhat.com>
X-Patchwork-Id: 11794199
Return-Path: <SRS0=+e/I=DA=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id D3EA16CA
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 23 Sep 2020 07:39:43 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id B40E72371F
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 23 Sep 2020 07:39:43 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="G4zAV62e"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726738AbgIWHjm (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 23 Sep 2020 03:39:42 -0400
Received: from us-smtp-delivery-124.mimecast.com ([216.205.24.124]:29952 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1726550AbgIWHjm (ORCPT
        <rfc822;kvm@vger.kernel.org>); Wed, 23 Sep 2020 03:39:42 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1600846780;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc; bh=5Xq33sgqqTIEfb547wu5zp7B0KAssraA6l5ncbhoQQs=;
        b=G4zAV62eLJsOI1nTHnHywxXrc1GXJO3b5tbjDysr8VPvgjR3nhpVMhP/UMEfzTEeKA+uwa
        R3t5yRRogDnz4EN2DSgkb2jtkDEqNMxTIUxu982d8C0rlzWpMITB6dhNG4V4u+XdjlZ1Gp
        jBlt+tsW6MU/jCpbmPUzl2f9VZXhvDk=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-283-hOXyyT0SPd23OdsHCg5HCg-1; Wed, 23 Sep 2020 03:39:37 -0400
X-MC-Unique: hOXyyT0SPd23OdsHCg5HCg-1
Received: from smtp.corp.redhat.com (int-mx04.intmail.prod.int.phx2.redhat.com
 [10.5.11.14])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 1283480F058;
        Wed, 23 Sep 2020 07:39:36 +0000 (UTC)
Received: from thuth.com (ovpn-112-49.ams2.redhat.com [10.36.112.49])
        by smtp.corp.redhat.com (Postfix) with ESMTP id C42C11B5AE;
        Wed, 23 Sep 2020 07:39:33 +0000 (UTC)
From: Thomas Huth <thuth@redhat.com>
To: kvm@vger.kernel.org, Paolo Bonzini <pbonzini@redhat.com>
Cc: Roman Bolshakov <r.bolshakov@yadro.com>
Subject: [kvm-unit-tests PATCH] travis.yml: Fix the getopt problem
Date: Wed, 23 Sep 2020 09:39:31 +0200
Message-Id: <20200923073931.74769-1-thuth@redhat.com>
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.14
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The enhanced getopt is now not selected with a configure switch
anymore, but by setting the PATH to the right location.

Signed-off-by: Thomas Huth <thuth@redhat.com>
---
 This fixes the new macOS build jobs on Travis :
 https://travis-ci.com/github/huth/kvm-unit-tests/builds/186146708

 .travis.yml | 8 ++++----
 1 file changed, 4 insertions(+), 4 deletions(-)

```
#### [PATCH 1/4] KVM: VMX: Rename vmx_*_supported() helpers to cpu_has_vmx_*()
##### From: Sean Christopherson <sean.j.christopherson@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Sean Christopherson <sean.j.christopherson@intel.com>
X-Patchwork-Id: 11795281
Return-Path: <SRS0=+e/I=DA=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 8708B112C
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 23 Sep 2020 16:50:58 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 73F1420C56
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 23 Sep 2020 16:50:58 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726764AbgIWQuw (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 23 Sep 2020 12:50:52 -0400
Received: from mga06.intel.com ([134.134.136.31]:17994 "EHLO mga06.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726184AbgIWQuu (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 23 Sep 2020 12:50:50 -0400
IronPort-SDR: 
 HrFTGTDzdbzfJXxMreLXcdbjMyZ3x6VjWI+LbImyu+KANrcbshtLv1Aao3V+bxrNtXC5Uh57Q3
 3uzm9bsCxxJg==
X-IronPort-AV: E=McAfee;i="6000,8403,9753"; a="222529026"
X-IronPort-AV: E=Sophos;i="5.77,293,1596524400";
   d="scan'208";a="222529026"
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from orsmga004.jf.intel.com ([10.7.209.38])
  by orsmga104.jf.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 23 Sep 2020 09:50:48 -0700
IronPort-SDR: 
 AKGXHpbCoLRljd6qUPK1/on/+jfvjoGYcwvkOQ+ze+YV+UJuyoXjpItAY/xXecnN7FIT7dvhUO
 7bqeYRIzxJEg==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.77,293,1596524400";
   d="scan'208";a="454985296"
Received: from sjchrist-coffee.jf.intel.com ([10.54.74.160])
  by orsmga004.jf.intel.com with ESMTP; 23 Sep 2020 09:50:48 -0700
From: Sean Christopherson <sean.j.christopherson@intel.com>
To: Paolo Bonzini <pbonzini@redhat.com>
Cc: Sean Christopherson <sean.j.christopherson@intel.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org
Subject: [PATCH 1/4] KVM: VMX: Rename vmx_*_supported() helpers to
 cpu_has_vmx_*()
Date: Wed, 23 Sep 2020 09:50:45 -0700
Message-Id: <20200923165048.20486-2-sean.j.christopherson@intel.com>
X-Mailer: git-send-email 2.28.0
In-Reply-To: <20200923165048.20486-1-sean.j.christopherson@intel.com>
References: <20200923165048.20486-1-sean.j.christopherson@intel.com>
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Rename helpers for a few controls to conform to the more prevelant style
of cpu_has_vmx_<feature>().  Consistent names will allow adding macros
to consolidate the boilerplate code for adjusting secondary execution
controls.

No functional change intended.

Signed-off-by: Sean Christopherson <sean.j.christopherson@intel.com>
---
 arch/x86/kvm/vmx/capabilities.h |  8 ++++----
 arch/x86/kvm/vmx/vmx.c          | 14 +++++++-------
 2 files changed, 11 insertions(+), 11 deletions(-)

```
#### [PATCH v2 1/3] KVM: VMX: Use precomputed MAXPHYADDR for RTIT base MSR check
##### From: Sean Christopherson <sean.j.christopherson@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Sean Christopherson <sean.j.christopherson@intel.com>
X-Patchwork-Id: 11795261
Return-Path: <SRS0=+e/I=DA=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 8A9DA6CB
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 23 Sep 2020 16:36:48 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 7A38A20791
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 23 Sep 2020 16:36:48 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726674AbgIWQgb (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 23 Sep 2020 12:36:31 -0400
Received: from mga17.intel.com ([192.55.52.151]:7062 "EHLO mga17.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726342AbgIWQgb (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 23 Sep 2020 12:36:31 -0400
IronPort-SDR: 
 x4nAr6QDRA3ykt+5QQj+A9gKAz9ubDaQMJm1jJ43OKUdU0P9tz0/VcUh7RqUmwYtF1t/b09Lu2
 x1bisoY9EBTQ==
X-IronPort-AV: E=McAfee;i="6000,8403,9753"; a="140962212"
X-IronPort-AV: E=Sophos;i="5.77,293,1596524400";
   d="scan'208";a="140962212"
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from orsmga004.jf.intel.com ([10.7.209.38])
  by fmsmga107.fm.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 23 Sep 2020 09:36:31 -0700
IronPort-SDR: 
 ecqydRGQzLrf0pek4bm8J0e2eNjVebB2Nz7vNgePUFERV/O3wVrO+q33DofTy1BZGNvul8nZho
 wUrLfWWZSIUA==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.77,293,1596524400";
   d="scan'208";a="454981822"
Received: from sjchrist-coffee.jf.intel.com ([10.54.74.160])
  by orsmga004.jf.intel.com with ESMTP; 23 Sep 2020 09:36:30 -0700
From: Sean Christopherson <sean.j.christopherson@intel.com>
To: Paolo Bonzini <pbonzini@redhat.com>
Cc: Sean Christopherson <sean.j.christopherson@intel.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org
Subject: [PATCH v2 1/3] KVM: VMX: Use precomputed MAXPHYADDR for RTIT base MSR
 check
Date: Wed, 23 Sep 2020 09:36:27 -0700
Message-Id: <20200923163629.20168-2-sean.j.christopherson@intel.com>
X-Mailer: git-send-email 2.28.0
In-Reply-To: <20200923163629.20168-1-sean.j.christopherson@intel.com>
References: <20200923163629.20168-1-sean.j.christopherson@intel.com>
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Use cpuid_maxphyaddr() instead of cpuid_query_maxphyaddr() for the
RTIT base MSR check.  There is no reason to recompute MAXPHYADDR as the
precomputed version is synchronized with CPUID updates, and
MSR_IA32_RTIT_OUTPUT_BASE is not written between stuffing CPUID and
refreshing vcpu->arch.maxphyaddr.

Signed-off-by: Sean Christopherson <sean.j.christopherson@intel.com>
---
 arch/x86/kvm/vmx/vmx.c | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
#### [PATCH 2/2] KVM: VMX: Rename ops.h to vmx_ops.h
##### From: Sean Christopherson <sean.j.christopherson@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Sean Christopherson <sean.j.christopherson@intel.com>
X-Patchwork-Id: 11795473
Return-Path: <SRS0=+e/I=DA=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 7C84E618
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 23 Sep 2020 18:31:34 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 6A80C2193E
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 23 Sep 2020 18:31:34 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726701AbgIWSba (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 23 Sep 2020 14:31:30 -0400
Received: from mga01.intel.com ([192.55.52.88]:62459 "EHLO mga01.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726422AbgIWSba (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 23 Sep 2020 14:31:30 -0400
IronPort-SDR: 
 iZrxXMApBgqFbuvWmDVKZiqMPDFAnlh5+a7+jpV1JrchYcSYnx3tNRzkePZyi3LxSmqvBFahIp
 z6LLh8Orw6lw==
X-IronPort-AV: E=McAfee;i="6000,8403,9753"; a="179071090"
X-IronPort-AV: E=Sophos;i="5.77,293,1596524400";
   d="scan'208";a="179071090"
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from fmsmga001.fm.intel.com ([10.253.24.23])
  by fmsmga101.fm.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 23 Sep 2020 11:31:14 -0700
IronPort-SDR: 
 FwN5aNVGE1jN+tKOofPqtaoXgNPIoheYhQdfLjM9Mkoqc6ZsZ5SzC3Lgb+JHu404GRGskn9X7F
 vpvKB74ffcJw==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.77,293,1596524400";
   d="scan'208";a="413082168"
Received: from sjchrist-coffee.jf.intel.com ([10.54.74.160])
  by fmsmga001.fm.intel.com with ESMTP; 23 Sep 2020 11:31:13 -0700
From: Sean Christopherson <sean.j.christopherson@intel.com>
To: Paolo Bonzini <pbonzini@redhat.com>
Cc: Sean Christopherson <sean.j.christopherson@intel.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org, Xiaoyao Li <xiaoyao.li@intel.com>
Subject: [PATCH 2/2] KVM: VMX: Rename ops.h to vmx_ops.h
Date: Wed, 23 Sep 2020 11:31:12 -0700
Message-Id: <20200923183112.3030-3-sean.j.christopherson@intel.com>
X-Mailer: git-send-email 2.28.0
In-Reply-To: <20200923183112.3030-1-sean.j.christopherson@intel.com>
References: <20200923183112.3030-1-sean.j.christopherson@intel.com>
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Rename ops.h to vmx_ops.h to allow adding a tdx_ops.h in the future
without causing massive confusion.

Trust Domain Extensions (TDX) is built on VMX, but KVM cannot directly
access the VMCS(es) for a TDX guest, thus TDX will need its own "ops"
implementation for wrapping the low level operations.

Signed-off-by: Sean Christopherson <sean.j.christopherson@intel.com>
---
 arch/x86/kvm/vmx/vmx.c                | 1 -
 arch/x86/kvm/vmx/vmx.h                | 2 +-
 arch/x86/kvm/vmx/{ops.h => vmx_ops.h} | 0
 3 files changed, 1 insertion(+), 2 deletions(-)
 rename arch/x86/kvm/vmx/{ops.h => vmx_ops.h} (100%)

```
#### [PATCH v2 1/8] KVM: x86/mmu: Commit zap of remaining invalid pages when recovering lpages
##### From: Sean Christopherson <sean.j.christopherson@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Sean Christopherson <sean.j.christopherson@intel.com>
X-Patchwork-Id: 11795507
Return-Path: <SRS0=+e/I=DA=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 6749F139F
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 23 Sep 2020 18:43:09 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 50C8E221EF
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 23 Sep 2020 18:43:09 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726727AbgIWSmi (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 23 Sep 2020 14:42:38 -0400
Received: from mga14.intel.com ([192.55.52.115]:9838 "EHLO mga14.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726545AbgIWSmi (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 23 Sep 2020 14:42:38 -0400
IronPort-SDR: 
 v8pJFzpbi4C9nA4gR3RsFx8Rxvozla4Kwy3lTMKdaSE/XrZqyHMnB3bA28rieYf0oLkAY8oVW3
 D9qNg897GyxA==
X-IronPort-AV: E=McAfee;i="6000,8403,9753"; a="160276861"
X-IronPort-AV: E=Sophos;i="5.77,293,1596524400";
   d="scan'208";a="160276861"
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from orsmga005.jf.intel.com ([10.7.209.41])
  by fmsmga103.fm.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 23 Sep 2020 11:37:37 -0700
IronPort-SDR: 
 VMcmoaIlgkERQ1mH6uE/4KT7MQHddhXLk0+SqEYv2740mytxNvTuPLvWrBKKA1ShvrkhorD3+h
 +KRWsoIUQd8w==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.77,293,1596524400";
   d="scan'208";a="486561616"
Received: from sjchrist-coffee.jf.intel.com ([10.54.74.160])
  by orsmga005.jf.intel.com with ESMTP; 23 Sep 2020 11:37:37 -0700
From: Sean Christopherson <sean.j.christopherson@intel.com>
To: Paolo Bonzini <pbonzini@redhat.com>
Cc: Sean Christopherson <sean.j.christopherson@intel.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org, Junaid Shahid <junaids@google.com>
Subject: [PATCH v2 1/8] KVM: x86/mmu: Commit zap of remaining invalid pages
 when recovering lpages
Date: Wed, 23 Sep 2020 11:37:28 -0700
Message-Id: <20200923183735.584-2-sean.j.christopherson@intel.com>
X-Mailer: git-send-email 2.28.0
In-Reply-To: <20200923183735.584-1-sean.j.christopherson@intel.com>
References: <20200923183735.584-1-sean.j.christopherson@intel.com>
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Call kvm_mmu_commit_zap_page() after exiting the "prepare zap" loop in
kvm_recover_nx_lpages() to finish zapping pages in the unlikely event
that the loop exited due to lpage_disallowed_mmu_pages being empty.
Because the recovery thread drops mmu_lock() when rescheduling, it's
possible that lpage_disallowed_mmu_pages could be emptied by a different
thread without to_zap reaching zero despite to_zap being derived from
the number of disallowed lpages.

Fixes: 1aa9b9572b105 ("kvm: x86: mmu: Recovery of shattered NX large pages")
Cc: Junaid Shahid <junaids@google.com>
Cc: stable@vger.kernel.org
Signed-off-by: Sean Christopherson <sean.j.christopherson@intel.com>
---
 arch/x86/kvm/mmu/mmu.c | 1 +
 1 file changed, 1 insertion(+)

```
#### [PATCH] KVM: x86/mmu: Move individual kvm_mmu initialization into common helper
##### From: Sean Christopherson <sean.j.christopherson@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Sean Christopherson <sean.j.christopherson@intel.com>
X-Patchwork-Id: 11795255
Return-Path: <SRS0=+e/I=DA=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 9D51092C
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 23 Sep 2020 16:33:18 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 8BFC920719
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 23 Sep 2020 16:33:18 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726603AbgIWQdP (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 23 Sep 2020 12:33:15 -0400
Received: from mga12.intel.com ([192.55.52.136]:27783 "EHLO mga12.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726178AbgIWQdP (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 23 Sep 2020 12:33:15 -0400
IronPort-SDR: 
 vyjTp+K7jFAtj1NxaWM0ujy+bqotUWvunx88KoRjEZRQysh1O/OhMs4CK0LRNLYXmweeBnbPhV
 eFa1B/tJTp2Q==
X-IronPort-AV: E=McAfee;i="6000,8403,9753"; a="140413544"
X-IronPort-AV: E=Sophos;i="5.77,293,1596524400";
   d="scan'208";a="140413544"
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from orsmga007.jf.intel.com ([10.7.209.58])
  by fmsmga106.fm.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 23 Sep 2020 09:33:14 -0700
IronPort-SDR: 
 qAOAGD9cR6U9BamXE2pPCcOnr6pygIUmJ1axxJv3JnIoo+SX3OaBXZZcIPzNOLx0ImDAzhjAlO
 JqtGTlpPmC5Q==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.77,293,1596524400";
   d="scan'208";a="348938302"
Received: from sjchrist-coffee.jf.intel.com ([10.54.74.160])
  by orsmga007.jf.intel.com with ESMTP; 23 Sep 2020 09:33:14 -0700
From: Sean Christopherson <sean.j.christopherson@intel.com>
To: Paolo Bonzini <pbonzini@redhat.com>
Cc: Sean Christopherson <sean.j.christopherson@intel.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org
Subject: [PATCH] KVM: x86/mmu: Move individual kvm_mmu initialization into
 common helper
Date: Wed, 23 Sep 2020 09:33:14 -0700
Message-Id: <20200923163314.8181-1-sean.j.christopherson@intel.com>
X-Mailer: git-send-email 2.28.0
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Move initialization of 'struct kvm_mmu' fields into alloc_mmu_pages() to
consolidate code, and rename the helper to __kvm_mmu_create().

No functional change intended.

Signed-off-by: Sean Christopherson <sean.j.christopherson@intel.com>
---
 arch/x86/kvm/mmu/mmu.c | 25 +++++++++----------------
 1 file changed, 9 insertions(+), 16 deletions(-)

```
#### [PATCH 1/4] KVM: x86/mmu: Return -EIO if page fault returns RET_PF_INVALID
##### From: Sean Christopherson <sean.j.christopherson@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Sean Christopherson <sean.j.christopherson@intel.com>
X-Patchwork-Id: 11795669
Return-Path: <SRS0=+e/I=DA=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 75E416CA
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 23 Sep 2020 22:04:35 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 5A547235FD
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 23 Sep 2020 22:04:35 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726672AbgIWWE1 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 23 Sep 2020 18:04:27 -0400
Received: from mga11.intel.com ([192.55.52.93]:60138 "EHLO mga11.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726265AbgIWWE1 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 23 Sep 2020 18:04:27 -0400
IronPort-SDR: 
 Pxa2msn0HgXxbOjOSsLDpVb7w1Q1OTTMnVzQW+98LI/QqpP/no1l20/ya2g8XnzA99k2zCEdrj
 FUfl3GOx8pUw==
X-IronPort-AV: E=McAfee;i="6000,8403,9753"; a="158381352"
X-IronPort-AV: E=Sophos;i="5.77,295,1596524400";
   d="scan'208";a="158381352"
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from fmsmga004.fm.intel.com ([10.253.24.48])
  by fmsmga102.fm.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 23 Sep 2020 15:04:27 -0700
IronPort-SDR: 
 cXwlLqEh1bEo2PO09WKC4xrYeHG0+Hz9T19Ugysv9fhWb1+nEOoVF494RC+gQTNUEL3LKJL2Sg
 Iyjte0gvyB1g==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.77,295,1596524400";
   d="scan'208";a="335647638"
Received: from sjchrist-coffee.jf.intel.com ([10.54.74.160])
  by fmsmga004.fm.intel.com with ESMTP; 23 Sep 2020 15:04:26 -0700
From: Sean Christopherson <sean.j.christopherson@intel.com>
To: Paolo Bonzini <pbonzini@redhat.com>
Cc: Sean Christopherson <sean.j.christopherson@intel.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org, Kai Huang <kai.huang@intel.com>
Subject: [PATCH 1/4] KVM: x86/mmu: Return -EIO if page fault returns
 RET_PF_INVALID
Date: Wed, 23 Sep 2020 15:04:22 -0700
Message-Id: <20200923220425.18402-2-sean.j.christopherson@intel.com>
X-Mailer: git-send-email 2.28.0
In-Reply-To: <20200923220425.18402-1-sean.j.christopherson@intel.com>
References: <20200923220425.18402-1-sean.j.christopherson@intel.com>
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Exit to userspace with an error if the MMU is buggy and returns
RET_PF_INVALID when servicing a page fault.  This will allow a future
patch to invert the emulation path, i.e. emulate only on RET_PF_EMULATE
instead of emulating on anything but RET_PF_RETRY.  This technically
means that KVM will exit to userspace instead of emulating on
RET_PF_INVALID, but practically speaking it's a nop as the MMU never
returns RET_PF_INVALID.

Signed-off-by: Sean Christopherson <sean.j.christopherson@intel.com>
---
 arch/x86/kvm/mmu/mmu.c | 3 ++-
 1 file changed, 2 insertions(+), 1 deletion(-)

```
#### [PATCH] KVM: x86/mmu: Stash 'kvm' in a local variable in kvm_mmu_free_roots()
##### From: Sean Christopherson <sean.j.christopherson@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Sean Christopherson <sean.j.christopherson@intel.com>
X-Patchwork-Id: 11795533
Return-Path: <SRS0=+e/I=DA=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 2B6016CA
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 23 Sep 2020 19:12:11 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 1451A2145D
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 23 Sep 2020 19:12:11 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726638AbgIWTMH (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 23 Sep 2020 15:12:07 -0400
Received: from mga14.intel.com ([192.55.52.115]:12738 "EHLO mga14.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726515AbgIWTMG (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 23 Sep 2020 15:12:06 -0400
IronPort-SDR: 
 bQpuDFpeaUtbVXtIzXjyomjU6HSf44kNzG2S6wf2pFY2qgS6cmLIj+EX9BkC4aheDQpG6UN24D
 8yrjCukqmibw==
X-IronPort-AV: E=McAfee;i="6000,8403,9753"; a="160281225"
X-IronPort-AV: E=Sophos;i="5.77,293,1596524400";
   d="scan'208";a="160281225"
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from orsmga001.jf.intel.com ([10.7.209.18])
  by fmsmga103.fm.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 23 Sep 2020 12:12:06 -0700
IronPort-SDR: 
 UclwOekwO5FlzgPqU/RilPEY6TTNa3q+D2KirpX+ICPG7WI0atvKS5bbr7dg+bupcbOIdH8JHr
 rK1Z9PYNgdcQ==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.77,293,1596524400";
   d="scan'208";a="382788351"
Received: from sjchrist-coffee.jf.intel.com ([10.54.74.160])
  by orsmga001.jf.intel.com with ESMTP; 23 Sep 2020 12:12:05 -0700
From: Sean Christopherson <sean.j.christopherson@intel.com>
To: Paolo Bonzini <pbonzini@redhat.com>
Cc: Sean Christopherson <sean.j.christopherson@intel.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org
Subject: [PATCH] KVM: x86/mmu: Stash 'kvm' in a local variable in
 kvm_mmu_free_roots()
Date: Wed, 23 Sep 2020 12:12:04 -0700
Message-Id: <20200923191204.8410-1-sean.j.christopherson@intel.com>
X-Mailer: git-send-email 2.28.0
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

To make kvm_mmu_free_roots() a bit more readable, capture 'kvm' in a
local variable instead of doing vcpu->kvm over and over (and over).

No functional change intended.

Signed-off-by: Sean Christopherson <sean.j.christopherson@intel.com>
---
 arch/x86/kvm/mmu/mmu.c | 14 +++++++-------
 1 file changed, 7 insertions(+), 7 deletions(-)

```
#### [PATCH v3 1/2] KVM: x86/mmu: Move flush logic from mmu_page_zap_pte() to FNAME(invlpg)
##### From: Sean Christopherson <sean.j.christopherson@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Sean Christopherson <sean.j.christopherson@intel.com>
X-Patchwork-Id: 11795695
Return-Path: <SRS0=+e/I=DA=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 679F36CA
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 23 Sep 2020 22:14:16 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 52DE823787
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 23 Sep 2020 22:14:16 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726716AbgIWWOI (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 23 Sep 2020 18:14:08 -0400
Received: from mga11.intel.com ([192.55.52.93]:60899 "EHLO mga11.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726634AbgIWWOI (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 23 Sep 2020 18:14:08 -0400
IronPort-SDR: 
 30nJLBPhSviJN17fRQdmXWeLaGiiHtgETWseeN4Juymr5i51Pf9XbMGQXo3B/BdTb0Ge1oYYAZ
 QHYaYHoStVjQ==
X-IronPort-AV: E=McAfee;i="6000,8403,9753"; a="158382291"
X-IronPort-AV: E=Sophos;i="5.77,295,1596524400";
   d="scan'208";a="158382291"
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from fmsmga004.fm.intel.com ([10.253.24.48])
  by fmsmga102.fm.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 23 Sep 2020 15:14:07 -0700
IronPort-SDR: 
 cCTeeWFMolGsyhT8Q/AwiNXndCi7jkVxeU33R4MNLcOL/fa3dBRHcMlJhCHZtWRldZZ82fej6v
 JheR34ho4dTg==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.77,295,1596524400";
   d="scan'208";a="335651275"
Received: from sjchrist-coffee.jf.intel.com ([10.54.74.160])
  by fmsmga004.fm.intel.com with ESMTP; 23 Sep 2020 15:14:07 -0700
From: Sean Christopherson <sean.j.christopherson@intel.com>
To: Paolo Bonzini <pbonzini@redhat.com>
Cc: Sean Christopherson <sean.j.christopherson@intel.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org, Peter Shier <pshier@google.com>,
        Ben Gardon <bgardon@google.com>
Subject: [PATCH v3 1/2] KVM: x86/mmu: Move flush logic from mmu_page_zap_pte()
 to FNAME(invlpg)
Date: Wed, 23 Sep 2020 15:14:05 -0700
Message-Id: <20200923221406.16297-2-sean.j.christopherson@intel.com>
X-Mailer: git-send-email 2.28.0
In-Reply-To: <20200923221406.16297-1-sean.j.christopherson@intel.com>
References: <20200923221406.16297-1-sean.j.christopherson@intel.com>
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Move the logic that controls whether or not FNAME(invlpg) needs to flush
fully into FNAME(invlpg) so that mmu_page_zap_pte() doesn't return a
value.  This allows a future patch to redefine the return semantics for
mmu_page_zap_pte() so that it can recursively zap orphaned child shadow
pages for nested TDP MMUs.

No functional change intended.

Signed-off-by: Sean Christopherson <sean.j.christopherson@intel.com>
---
 arch/x86/kvm/mmu/mmu.c         | 10 +++-------
 arch/x86/kvm/mmu/paging_tmpl.h |  7 +++++--
 2 files changed, 8 insertions(+), 9 deletions(-)

```
#### [PATCH] KVM: x86: Reset MMU context if guest toggles CR4.SMAP or CR4.PKE
##### From: Sean Christopherson <sean.j.christopherson@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Sean Christopherson <sean.j.christopherson@intel.com>
X-Patchwork-Id: 11795661
Return-Path: <SRS0=+e/I=DA=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 9630B6CA
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 23 Sep 2020 21:53:56 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 867C723787
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 23 Sep 2020 21:53:56 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726621AbgIWVxx (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 23 Sep 2020 17:53:53 -0400
Received: from mga17.intel.com ([192.55.52.151]:36586 "EHLO mga17.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726199AbgIWVxx (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 23 Sep 2020 17:53:53 -0400
IronPort-SDR: 
 mIUDTGRSymmnYE56UqDrp3ysb3zWZ8dzw3+EjMmI/iOqT/3six//cTpABbIfwe8fjlAi/i5IDt
 4StO1k5Tuyhw==
X-IronPort-AV: E=McAfee;i="6000,8403,9753"; a="141037930"
X-IronPort-AV: E=Sophos;i="5.77,295,1596524400";
   d="scan'208";a="141037930"
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from orsmga004.jf.intel.com ([10.7.209.38])
  by fmsmga107.fm.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 23 Sep 2020 14:53:53 -0700
IronPort-SDR: 
 R8tPOzfBFwE35C1bIv0L7gPeceJWTkWVyRmhP0IgOBgtYibE1kjpJIRFNJGMnsKj3nb9ynqiWJ
 bWoyTp8rGWow==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.77,295,1596524400";
   d="scan'208";a="455085173"
Received: from sjchrist-coffee.jf.intel.com ([10.54.74.160])
  by orsmga004.jf.intel.com with ESMTP; 23 Sep 2020 14:53:52 -0700
From: Sean Christopherson <sean.j.christopherson@intel.com>
To: Paolo Bonzini <pbonzini@redhat.com>
Cc: Sean Christopherson <sean.j.christopherson@intel.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org, Peter Shier <pshier@google.com>,
        Oliver Upton <oupton@google.com>
Subject: [PATCH] KVM: x86: Reset MMU context if guest toggles CR4.SMAP or
 CR4.PKE
Date: Wed, 23 Sep 2020 14:53:52 -0700
Message-Id: <20200923215352.17756-1-sean.j.christopherson@intel.com>
X-Mailer: git-send-email 2.28.0
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Reset the MMU context during kvm_set_cr4() if SMAP or PKE is toggled.
Recent commits to (correctly) not reload PDPTRs when SMAP/PKE are
toggled inadvertantly skipped the MMU context reset due to the mask
of bits that triggers PDPTR loads also being used to trigger MMU context
resets.

Fixes: 427890aff855 ("kvm: x86: Toggling CR4.SMAP does not load PDPTEs in PAE mode")
Fixes: cb957adb4ea4 ("kvm: x86: Toggling CR4.PKE does not load PDPTEs in PAE mode")
Cc: Jim Mattson <jmattson@google.com>
Cc: Peter Shier <pshier@google.com>
Cc: Oliver Upton <oupton@google.com>
Signed-off-by: Sean Christopherson <sean.j.christopherson@intel.com>
---
 arch/x86/kvm/x86.c | 3 ++-
 1 file changed, 2 insertions(+), 1 deletion(-)

```
#### [PATCH v2 1/7] KVM: x86: Add RIP to the kvm_entry, i.e. VM-Enter, tracepoint
##### From: Sean Christopherson <sean.j.christopherson@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Sean Christopherson <sean.j.christopherson@intel.com>
X-Patchwork-Id: 11795639
Return-Path: <SRS0=+e/I=DA=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 3A91C618
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 23 Sep 2020 20:14:10 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 223812388A
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 23 Sep 2020 20:14:10 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726638AbgIWUNv (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 23 Sep 2020 16:13:51 -0400
Received: from mga12.intel.com ([192.55.52.136]:49295 "EHLO mga12.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726557AbgIWUNu (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 23 Sep 2020 16:13:50 -0400
IronPort-SDR: 
 /OBzYv/O9YrOj3CWG0trck4RZikROSRGaw+l96twlMsNdZhkBJE6swaGCJshRDKwvG6uHgK2Ab
 5nHsGBrJrJbA==
X-IronPort-AV: E=McAfee;i="6000,8403,9753"; a="140472232"
X-IronPort-AV: E=Sophos;i="5.77,293,1596524400";
   d="scan'208";a="140472232"
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from orsmga007.jf.intel.com ([10.7.209.58])
  by fmsmga106.fm.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 23 Sep 2020 13:13:50 -0700
IronPort-SDR: 
 90NV0U+DsvdbgCFbgCd0gNO1XvAW9VxnTaukmjX7XMMrMzwn3K3ypTYFi3omi6v3XCPP3hu4PG
 bqnCRJ0O9TXA==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.77,293,1596524400";
   d="scan'208";a="349004936"
Received: from sjchrist-coffee.jf.intel.com ([10.54.74.160])
  by orsmga007.jf.intel.com with ESMTP; 23 Sep 2020 13:13:50 -0700
From: Sean Christopherson <sean.j.christopherson@intel.com>
To: Paolo Bonzini <pbonzini@redhat.com>
Cc: Sean Christopherson <sean.j.christopherson@intel.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org
Subject: [PATCH v2 1/7] KVM: x86: Add RIP to the kvm_entry, i.e. VM-Enter,
 tracepoint
Date: Wed, 23 Sep 2020 13:13:43 -0700
Message-Id: <20200923201349.16097-2-sean.j.christopherson@intel.com>
X-Mailer: git-send-email 2.28.0
In-Reply-To: <20200923201349.16097-1-sean.j.christopherson@intel.com>
References: <20200923201349.16097-1-sean.j.christopherson@intel.com>
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Add RIP to the kvm_entry tracepoint to help debug if the kvm_exit
tracepoint is disabled or if VM-Enter fails, in which case the kvm_exit
tracepoint won't be hit.

Read RIP from within the tracepoint itself to avoid a potential VMREAD
and retpoline if the guest's RIP isn't available.

Signed-off-by: Sean Christopherson <sean.j.christopherson@intel.com>
---
 arch/x86/kvm/trace.h | 10 ++++++----
 arch/x86/kvm/x86.c   |  2 +-
 2 files changed, 7 insertions(+), 5 deletions(-)

```
#### [PATCH v2 01/15] KVM: x86: Rename "shared_msrs" to "user_return_msrs"
##### From: Sean Christopherson <sean.j.christopherson@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Sean Christopherson <sean.j.christopherson@intel.com>
X-Patchwork-Id: 11795415
Return-Path: <SRS0=+e/I=DA=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 515F0618
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 23 Sep 2020 18:04:52 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 3444920791
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 23 Sep 2020 18:04:52 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726865AbgIWSEn (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 23 Sep 2020 14:04:43 -0400
Received: from mga05.intel.com ([192.55.52.43]:39927 "EHLO mga05.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726515AbgIWSEY (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 23 Sep 2020 14:04:24 -0400
IronPort-SDR: 
 zP7eX/9Se86dAcKv8h1IG3FC5s+t6rb/t4saKPOQYaBWw2j+NW78YoiFfFjYcOFTgMYMiX1AsI
 vSBm1wnFlsDg==
X-IronPort-AV: E=McAfee;i="6000,8403,9753"; a="245808956"
X-IronPort-AV: E=Sophos;i="5.77,293,1596524400";
   d="scan'208";a="245808956"
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from orsmga002.jf.intel.com ([10.7.209.21])
  by fmsmga105.fm.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 23 Sep 2020 11:04:11 -0700
IronPort-SDR: 
 27B0YWWF4aasP/InJZi3PUsvQyRJANn/23ZxGkzPUHFWUStSBllW8vuoFQKP3v2QLxAMcFShtR
 ajjhmArjeuwg==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.77,293,1596524400";
   d="scan'208";a="322670256"
Received: from sjchrist-coffee.jf.intel.com ([10.54.74.160])
  by orsmga002.jf.intel.com with ESMTP; 23 Sep 2020 11:04:10 -0700
From: Sean Christopherson <sean.j.christopherson@intel.com>
To: Paolo Bonzini <pbonzini@redhat.com>
Cc: Sean Christopherson <sean.j.christopherson@intel.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org
Subject: [PATCH v2 01/15] KVM: x86: Rename "shared_msrs" to "user_return_msrs"
Date: Wed, 23 Sep 2020 11:03:55 -0700
Message-Id: <20200923180409.32255-2-sean.j.christopherson@intel.com>
X-Mailer: git-send-email 2.28.0
In-Reply-To: <20200923180409.32255-1-sean.j.christopherson@intel.com>
References: <20200923180409.32255-1-sean.j.christopherson@intel.com>
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Rename the "shared_msrs" mechanism, which is used to defer restoring
MSRs that are only consumed when running in userspace, to a more banal
but less likely to be confusing "user_return_msrs".

The "shared" nomenclature is confusing as it's not obvious who is
sharing what, e.g. reasonable interpretations are that the guest value
is shared by vCPUs in a VM, or that the MSR value is shared/common to
guest and host, both of which are wrong.

"shared" is also misleading as the MSR value (in hardware) is not
guaranteed to be shared/reused between VMs (if that's indeed the correct
interpretation of the name), as the ability to share values between VMs
is simply a side effect (albiet a very nice side effect) of deferring
restoration of the host value until returning from userspace.

"user_return" avoids the above confusion by describing the mechanism
itself instead of its effects.

Signed-off-by: Sean Christopherson <sean.j.christopherson@intel.com>
---
 arch/x86/include/asm/kvm_host.h |   4 +-
 arch/x86/kvm/vmx/vmx.c          |  11 ++--
 arch/x86/kvm/x86.c              | 101 +++++++++++++++++---------------
 3 files changed, 60 insertions(+), 56 deletions(-)

```
#### [PATCH kvm-unit-tests v2 1/4] common.bash: run `cmd` only if a test case was found
##### From: Marc Hartmayer <mhartmay@linux.ibm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Marc Hartmayer <mhartmay@linux.ibm.com>
X-Patchwork-Id: 11795087
Return-Path: <SRS0=+e/I=DA=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id EBA826CA
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 23 Sep 2020 13:48:15 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id C8E02221EB
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 23 Sep 2020 13:48:15 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=ibm.com header.i=@ibm.com
 header.b="SYszFwl8"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726526AbgIWNsO (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 23 Sep 2020 09:48:14 -0400
Received: from mx0a-001b2d01.pphosted.com ([148.163.156.1]:7640 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1726504AbgIWNsO (ORCPT
        <rfc822;kvm@vger.kernel.org>); Wed, 23 Sep 2020 09:48:14 -0400
Received: from pps.filterd (m0098396.ppops.net [127.0.0.1])
        by mx0a-001b2d01.pphosted.com (8.16.0.42/8.16.0.42) with SMTP id
 08NDXC84169216;
        Wed, 23 Sep 2020 09:48:13 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=ibm.com;
 h=from : to : cc : subject
 : date : message-id : in-reply-to : references : mime-version :
 content-transfer-encoding; s=pp1;
 bh=uFqSzS8d52K8BKRJGWGm9lEoGlzK7xsvYKmeKqlNQ4k=;
 b=SYszFwl8dBqhWHP/EG82THOLEqlwgqamfZEBCTIW/b2qB8vWccBf6lsNY7by4PBDoGH0
 w84mEIop/w3VwMKP7f3mH52YzAgEs/fccqAquZS5hOPmsopNSN6ZwDbjuLaEOl2Zrmct
 ursMCFNtOk2TjUk1jC6tmcD0hcXQokgZUpjytcom/BPfb8DWY3gjG0/sHGsJsw0gm1ed
 Lwxq5vxbnoQ96rfZcHCfg6/LR7HZvV2MuMR+3fJ4kclwHoZuYkcX/YP58yBY9H5diw2o
 lshjktH6+Wd1Kgt2CFDsw0gtubMj3oxLDRQT/ccnZNoa917qPH/6Ld+qZmRJyWEUxkJn FQ==
Received: from pps.reinject (localhost [127.0.0.1])
        by mx0a-001b2d01.pphosted.com with ESMTP id 33r5bnmx0u-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Wed, 23 Sep 2020 09:48:13 -0400
Received: from m0098396.ppops.net (m0098396.ppops.net [127.0.0.1])
        by pps.reinject (8.16.0.36/8.16.0.36) with SMTP id 08NDYESs173368;
        Wed, 23 Sep 2020 09:48:13 -0400
Received: from ppma04ams.nl.ibm.com (63.31.33a9.ip4.static.sl-reverse.com
 [169.51.49.99])
        by mx0a-001b2d01.pphosted.com with ESMTP id 33r5bnmwyq-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Wed, 23 Sep 2020 09:48:12 -0400
Received: from pps.filterd (ppma04ams.nl.ibm.com [127.0.0.1])
        by ppma04ams.nl.ibm.com (8.16.0.42/8.16.0.42) with SMTP id
 08NDgHBx029999;
        Wed, 23 Sep 2020 13:48:10 GMT
Received: from b06cxnps4075.portsmouth.uk.ibm.com
 (d06relay12.portsmouth.uk.ibm.com [9.149.109.197])
        by ppma04ams.nl.ibm.com with ESMTP id 33payuay7d-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Wed, 23 Sep 2020 13:48:10 +0000
Received: from d06av22.portsmouth.uk.ibm.com (d06av22.portsmouth.uk.ibm.com
 [9.149.105.58])
        by b06cxnps4075.portsmouth.uk.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id 08NDm8VY12190132
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Wed, 23 Sep 2020 13:48:08 GMT
Received: from d06av22.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 500074C04A;
        Wed, 23 Sep 2020 13:48:08 +0000 (GMT)
Received: from d06av22.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id F227C4C046;
        Wed, 23 Sep 2020 13:48:07 +0000 (GMT)
Received: from marcibm.ibmuc.com (unknown [9.145.64.218])
        by d06av22.portsmouth.uk.ibm.com (Postfix) with ESMTP;
        Wed, 23 Sep 2020 13:48:07 +0000 (GMT)
From: Marc Hartmayer <mhartmay@linux.ibm.com>
To: <kvm@vger.kernel.org>
Cc: Thomas Huth <thuth@redhat.com>,
        David Hildenbrand <david@redhat.com>,
        Janosch Frank <frankja@linux.ibm.com>,
        Cornelia Huck <cohuck@redhat.com>,
        Andrew Jones <drjones@redhat.com>,
        Paolo Bonzini <pbonzini@redhat.com>, linux-s390@vger.kernel.org
Subject: [PATCH kvm-unit-tests v2 1/4] common.bash: run `cmd` only if a test
 case was found
Date: Wed, 23 Sep 2020 15:47:55 +0200
Message-Id: <20200923134758.19354-2-mhartmay@linux.ibm.com>
X-Mailer: git-send-email 2.26.2
In-Reply-To: <20200923134758.19354-1-mhartmay@linux.ibm.com>
References: <20200923134758.19354-1-mhartmay@linux.ibm.com>
MIME-Version: 1.0
X-TM-AS-GCONF: 00
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.235,18.0.687
 definitions=2020-09-23_09:2020-09-23,2020-09-23 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 mlxlogscore=999 bulkscore=0
 adultscore=0 lowpriorityscore=0 mlxscore=0 spamscore=0 malwarescore=0
 phishscore=0 impostorscore=0 clxscore=1015 suspectscore=15
 priorityscore=1501 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.12.0-2006250000 definitions=main-2009230108
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

It's only useful to run `cmd` in `for_each_unittest` if a test case
was found. This change allows us to remove the guards from the
functions `run_task` and `mkstandalone`.

Reviewed-by: Andrew Jones <drjones@redhat.com>
Reviewed-by: Cornelia Huck <cohuck@redhat.com>
Reviewed-by: David Hildenbrand <david@redhat.com>
Signed-off-by: Marc Hartmayer <mhartmay@linux.ibm.com>
---
 run_tests.sh            | 3 ---
 scripts/common.bash     | 8 ++++++--
 scripts/mkstandalone.sh | 4 ----
 3 files changed, 6 insertions(+), 9 deletions(-)

```
#### [PATCH][v2] KVM: x86/mmu: fix counting of rmap entries in pte_list_add
##### From: Li RongQing <lirongqing@baidu.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Li RongQing <lirongqing@baidu.com>
X-Patchwork-Id: 11793853
Return-Path: <SRS0=+e/I=DA=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 29311618
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 23 Sep 2020 04:59:16 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 137352076B
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 23 Sep 2020 04:59:16 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726877AbgIWE7M (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 23 Sep 2020 00:59:12 -0400
Received: from mx52.baidu.com ([61.135.168.52]:25347 "EHLO
        tc-sys-mailedm04.tc.baidu.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S1726198AbgIWE7M (ORCPT
        <rfc822;kvm@vger.kernel.org>); Wed, 23 Sep 2020 00:59:12 -0400
Received: from localhost (cp01-cos-dev01.cp01.baidu.com [10.92.119.46])
        by tc-sys-mailedm04.tc.baidu.com (Postfix) with ESMTP id 28438236C005;
        Wed, 23 Sep 2020 12:58:55 +0800 (CST)
From: Li RongQing <lirongqing@baidu.com>
To: lirongqing@baidu.com, kvm@vger.kernel.org, x86@kernel.org,
        sean.j.christopherson@intel.com
Subject: [PATCH][v2] KVM: x86/mmu: fix counting of rmap entries in
 pte_list_add
Date: Wed, 23 Sep 2020 12:58:58 +0800
Message-Id: <1600837138-21110-1-git-send-email-lirongqing@baidu.com>
X-Mailer: git-send-email 1.7.1
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

counting of rmap entries was missed when desc->sptes is full
and desc->more is NULL

and merging two PTE_LIST_EXT-1 check as one, to avoids the
extra comparison to give slightly optimization

Suggested-by: Sean Christopherson <sean.j.christopherson@intel.com>
Signed-off-by: Li RongQing <lirongqing@baidu.com>

diff with v1: merge two check as one

 arch/x86/kvm/mmu/mmu.c | 12 +++++++-----
 1 file changed, 7 insertions(+), 5 deletions(-)

```
