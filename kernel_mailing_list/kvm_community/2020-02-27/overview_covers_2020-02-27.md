

#### [PATCH 0/5] KVM: Support guest MAXPHYADDR < host MAXPHYADDR
##### From: Mohammed Gamal <mgamal@redhat.com>

```c
From patchwork Thu Feb 27 17:23:01 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Mohammed Gamal <mgamal@redhat.com>
X-Patchwork-Id: 11409051
Return-Path: <SRS0=27T9=4P=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 3F8AA92A
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 27 Feb 2020 17:24:04 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 1FD27246A3
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 27 Feb 2020 17:24:04 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="MHBomGOo"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1730022AbgB0RXi (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 27 Feb 2020 12:23:38 -0500
Received: from us-smtp-delivery-1.mimecast.com ([207.211.31.120]:35084 "EHLO
        us-smtp-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org
        with ESMTP id S1728413AbgB0RXi (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 27 Feb 2020 12:23:38 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1582824216;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=Gjp4z4++70DlRdyoFwoW1wXA2SmQC4OgN2YnpC8FfY0=;
        b=MHBomGOoRD/7LgV8bXtFl/R7xjrs+mHM41goUid9xnXO5BJ7zAmRSpIQMG5ExCJsdAzF51
        2+lNohmhtf1NttgMNkCJQtZym/65ZuxgSG6/zKNHyjXrut4yuWUZOaXOz5QWteo5V4dCaM
        JQkPvyRYrGfOhWSEfPN2V87uEOrolxM=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-299-MIUn5VExOQGbEy_dwFFG-A-1; Thu, 27 Feb 2020 12:23:32 -0500
X-MC-Unique: MIUn5VExOQGbEy_dwFFG-A-1
Received: from smtp.corp.redhat.com (int-mx07.intmail.prod.int.phx2.redhat.com
 [10.5.11.22])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 73BA5800D54;
        Thu, 27 Feb 2020 17:23:30 +0000 (UTC)
Received: from millenium-falcon.redhat.com (unknown [10.36.118.42])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 6A13A1001B2C;
        Thu, 27 Feb 2020 17:23:23 +0000 (UTC)
From: Mohammed Gamal <mgamal@redhat.com>
To: kvm@vger.kernel.org, pbonzini@redhat.com
Cc: sean.j.christopherson@intel.com, vkuznets@redhat.com,
        wanpengli@tencent.com, jmattson@google.com, joro@8bytes.org,
        linux-kernel@vger.kernel.org, Mohammed Gamal <mgamal@redhat.com>
Subject: [PATCH 0/5] KVM: Support guest MAXPHYADDR < host MAXPHYADDR
Date: Thu, 27 Feb 2020 19:23:01 +0200
Message-Id: <20200227172306.21426-1-mgamal@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.84 on 10.5.11.22
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

When EPT/NPT is enabled, KVM does not really look at guest physical 
address size. Address bits above maximum physical memory size are reserved. 
Because KVM does not look at these guest physical addresses, it currently 
effectively supports guest physical address sizes equal to the host.

This can be problem when having a mixed setup of machines with 5-level page 
tables and machines with 4-level page tables, as live migration can change 
MAXPHYADDR while the guest runs, which can theoretically introduce bugs.

In this patch series we add checks on guest physical addresses in EPT 
violation/misconfig and NPF vmexits and if needed inject the proper 
page faults in the guest.

A more subtle issue is when the host MAXPHYADDR is larger than that of the
guest. Page faults caused by reserved bits on the guest won't cause an EPT
violation/NPF and hence we also check guest MAXPHYADDR and add PFERR_RSVD_MASK
error code to the page fault if needed.


Mohammed Gamal (5):
  KVM: x86: Add function to inject guest page fault with reserved bits
    set
  KVM: VMX: Add guest physical address check in EPT violation and
    misconfig
  KVM: SVM: Add guest physical address check in NPF interception
  KVM: x86: mmu: Move translate_gpa() to mmu.c
  KVM: x86: mmu: Add guest physical address check in translate_gpa()

 arch/x86/include/asm/kvm_host.h |  6 ------
 arch/x86/kvm/mmu/mmu.c          | 10 ++++++++++
 arch/x86/kvm/mmu/paging_tmpl.h  |  2 +-
 arch/x86/kvm/svm.c              |  7 +++++++
 arch/x86/kvm/vmx/vmx.c          | 13 +++++++++++++
 arch/x86/kvm/x86.c              | 14 ++++++++++++++
 arch/x86/kvm/x86.h              |  1 +
 7 files changed, 46 insertions(+), 7 deletions(-)
```
#### [PATCH 0/3] KVM: VMX: Fix for kexec VMCLEAR and VMXON cleanup
##### From: Sean Christopherson <sean.j.christopherson@intel.com>

```c
From patchwork Thu Feb 27 22:30:44 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Sean Christopherson <sean.j.christopherson@intel.com>
X-Patchwork-Id: 11411041
Return-Path: <SRS0=27T9=4P=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 72994138D
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 27 Feb 2020 22:31:09 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 5A63124650
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 27 Feb 2020 22:31:09 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1730117AbgB0Wav (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 27 Feb 2020 17:30:51 -0500
Received: from mga04.intel.com ([192.55.52.120]:35152 "EHLO mga04.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1729808AbgB0Wau (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 27 Feb 2020 17:30:50 -0500
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from orsmga004.jf.intel.com ([10.7.209.38])
  by fmsmga104.fm.intel.com with ESMTP/TLS/DHE-RSA-AES256-GCM-SHA384;
 27 Feb 2020 14:30:50 -0800
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.70,493,1574150400";
   d="scan'208";a="385312249"
Received: from sjchrist-coffee.jf.intel.com ([10.54.74.202])
  by orsmga004.jf.intel.com with ESMTP; 27 Feb 2020 14:30:49 -0800
From: Sean Christopherson <sean.j.christopherson@intel.com>
To: Paolo Bonzini <pbonzini@redhat.com>
Cc: Sean Christopherson <sean.j.christopherson@intel.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org
Subject: [PATCH 0/3] KVM: VMX: Fix for kexec VMCLEAR and VMXON cleanup
Date: Thu, 27 Feb 2020 14:30:44 -0800
Message-Id: <20200227223047.13125-1-sean.j.christopherson@intel.com>
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

Patch 2 isn't directly related, but it conflicts with the crash cleanup
changes, both from a code and a semantics perspective.  Without the crash
cleanup, IMO hardware_enable() should do crash_disable_local_vmclear()
if VMXON fails, i.e. clean up after itself.  But hardware_disable()
doesn't even do crash_disable_local_vmclear() (which is what got me
looking at that code in the first place).  Basing the VMXON change on top
of the crash cleanup avoids the debate entirely.

Patch 3 is a simple clean up (no functional change intended ;-) ).

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
  KVM: VMX: Gracefully handle faults on VMXON
  KVM: VMX: Make loaded_vmcs_init() a static function

 arch/x86/kvm/vmx/vmx.c | 101 +++++++++++++++++------------------------
 arch/x86/kvm/vmx/vmx.h |   1 -
 2 files changed, 41 insertions(+), 61 deletions(-)
```
