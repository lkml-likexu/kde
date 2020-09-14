#### [GIT PULL] KVM changes for Linux 5.9-rc5
##### From: Paolo Bonzini <pbonzini@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Paolo Bonzini <pbonzini@redhat.com>
X-Patchwork-Id: 11772231
Return-Path: <SRS0=7gxW=CW=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 55DC559D
	for <patchwork-kvm@patchwork.kernel.org>;
 Sun, 13 Sep 2020 08:11:47 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 318F12074B
	for <patchwork-kvm@patchwork.kernel.org>;
 Sun, 13 Sep 2020 08:11:47 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="eXzrvVzL"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1725955AbgIMILq (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Sun, 13 Sep 2020 04:11:46 -0400
Received: from us-smtp-delivery-124.mimecast.com ([216.205.24.124]:31510 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1725918AbgIMILi (ORCPT
        <rfc822;kvm@vger.kernel.org>); Sun, 13 Sep 2020 04:11:38 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1599984691;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=gBwOgxziVZ4w/s+1bIafcq1Xhk6ZHMrvZV2mu4yFom8=;
        b=eXzrvVzLkqk7uBevLIznwVBO5eEMLELnN3R73C8D+8ce7HuZmkg0DphX4ptTQ8+R+clu0F
        nPC0miJLJzeAg9zrcAYpA0oS6blej+OIaw7YApvA+AwNu260H8lH7Ab0BwvcazvkAFl9Le
        AT4nIcR0MEUKx2YzHBsXksCn2GBJ3wE=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-135-G3EbA4cxNBKxZcJyB-VFeA-1; Sun, 13 Sep 2020 04:11:27 -0400
X-MC-Unique: G3EbA4cxNBKxZcJyB-VFeA-1
Received: from smtp.corp.redhat.com (int-mx03.intmail.prod.int.phx2.redhat.com
 [10.5.11.13])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 307A810059A2;
        Sun, 13 Sep 2020 08:11:26 +0000 (UTC)
Received: from virtlab701.virt.lab.eng.bos.redhat.com
 (virtlab701.virt.lab.eng.bos.redhat.com [10.19.152.228])
        by smtp.corp.redhat.com (Postfix) with ESMTP id D3B107EB8F;
        Sun, 13 Sep 2020 08:11:25 +0000 (UTC)
From: Paolo Bonzini <pbonzini@redhat.com>
To: torvalds@linux-foundation.org
Cc: linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Subject: [GIT PULL] KVM changes for Linux 5.9-rc5
Date: Sun, 13 Sep 2020 04:11:25 -0400
Message-Id: <20200913081125.28980-1-pbonzini@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.13
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Linus,

The following changes since commit b5331379bc62611d1026173a09c73573384201d9:

  KVM: arm64: Only reschedule if MMU_NOTIFIER_RANGE_BLOCKABLE is not set (2020-08-21 18:06:43 -0400)

are available in the Git repository at:

  https://git.kernel.org/pub/scm/virt/kvm/kvm.git tags/for-linus

for you to fetch changes up to 37f66bbef0920429b8cb5eddba849ec4308a9f8e:

  KVM: emulator: more strict rsm checks. (2020-09-12 12:22:55 -0400)

A bit on the bigger side, mostly due to me being on vacation, then busy,
then on parental leave, but there's nothing worrisome.

----------------------------------------------------------------
ARM:
- Multiple stolen time fixes, with a new capability to match x86
- Fix for hugetlbfs mappings when PUD and PMD are the same level
- Fix for hugetlbfs mappings when PTE mappings are enforced
  (dirty logging, for example)
- Fix tracing output of 64bit values

x86:
- nSVM state restore fixes
- Async page fault fixes
- Lots of small fixes everywhere

----------------------------------------------------------------
Alexandru Elisei (1):
      KVM: arm64: Update page shift if stage 2 block mapping not supported

Andrew Jones (6):
      KVM: arm64: pvtime: steal-time is only supported when configured
      KVM: arm64: pvtime: Fix potential loss of stolen time
      KVM: arm64: Drop type input from kvm_put_guest
      KVM: arm64: pvtime: Fix stolen time accounting across migration
      KVM: Documentation: Minor fixups
      arm64/x86: KVM: Introduce steal-time cap

Chenyi Qiang (1):
      KVM: nVMX: Fix the update value of nested load IA32_PERF_GLOBAL_CTRL control

David Rientjes (1):
      KVM: SVM: Periodically schedule when unregistering regions on destroy

Haiwei Li (1):
      KVM: Check the allocation of pv cpu mask

Huacai Chen (1):
      KVM: MIPS: Change the definition of kvm type

Lai Jiangshan (1):
      kvm x86/mmu: use KVM_REQ_MMU_SYNC to sync when needed

Marc Zyngier (2):
      KVM: arm64: Do not try to map PUDs when they are folded into PMD
      KVM: arm64: Fix address truncation in traces

Maxim Levitsky (4):
      SVM: nSVM: correctly restore GIF on vmexit from nesting after migration
      SVM: nSVM: setup nested msr permission bitmap on nested state load
      KVM: nSVM: more strict SMM checks when returning to nested guest
      KVM: emulator: more strict rsm checks.

Paolo Bonzini (1):
      Merge tag 'kvmarm-fixes-5.9-1' of git://git.kernel.org/.../kvmarm/kvmarm into HEAD

Peter Shier (1):
      KVM: nVMX: Update VMCS02 when L2 PAE PDPTE updates detected

Rustam Kovhaev (1):
      KVM: fix memory leak in kvm_io_bus_unregister_dev()

Vitaly Kuznetsov (3):
      KVM: x86: always allow writing '0' to MSR_KVM_ASYNC_PF_EN
      x86/kvm: properly use DEFINE_IDTENTRY_SYSVEC() macro
      x86/kvm: don't forget to ACK async PF IRQ

Wanpeng Li (2):
      KVM: SVM: avoid emulation with stale next_rip
      KVM: VMX: Don't freeze guest when event delivery causes an APIC-access exit

 Documentation/virt/kvm/api.rst     | 22 ++++++++++++++++++----
 arch/arm64/include/asm/kvm_host.h  |  2 +-
 arch/arm64/kvm/arm.c               |  3 +++
 arch/arm64/kvm/mmu.c               |  8 +++++++-
 arch/arm64/kvm/pvtime.c            | 29 +++++++++++++----------------
 arch/arm64/kvm/trace_arm.h         | 16 ++++++++--------
 arch/arm64/kvm/trace_handle_exit.h |  6 +++---
 arch/mips/kvm/mips.c               |  2 ++
 arch/x86/kernel/kvm.c              | 26 ++++++++++++++++++++------
 arch/x86/kvm/emulate.c             | 22 +++++++++++++++++-----
 arch/x86/kvm/mmu/mmu.c             |  2 +-
 arch/x86/kvm/svm/nested.c          |  7 ++++++-
 arch/x86/kvm/svm/sev.c             |  1 +
 arch/x86/kvm/svm/svm.c             | 36 +++++++++++++++++++++---------------
 arch/x86/kvm/vmx/nested.c          | 10 +++++++++-
 arch/x86/kvm/vmx/vmx.c             |  5 +++--
 arch/x86/kvm/vmx/vmx.h             |  1 +
 arch/x86/kvm/x86.c                 |  5 ++++-
 include/linux/kvm_host.h           | 31 ++++++++++++++++++++++++++-----
 include/uapi/linux/kvm.h           |  6 ++++--
 virt/kvm/kvm_main.c                | 21 ++++++++++++---------
 21 files changed, 180 insertions(+), 81 deletions(-)
```
