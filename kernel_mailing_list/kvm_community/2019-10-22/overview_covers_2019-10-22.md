

#### [PATCH v2 00/15] KVM: Dynamically size memslot arrays
##### From: Sean Christopherson <sean.j.christopherson@intel.com>

```c
From patchwork Tue Oct 22 00:35:22 2019
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Sean Christopherson <sean.j.christopherson@intel.com>
X-Patchwork-Id: 11203323
Return-Path: <SRS0=lBCn=YP=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id CF05F112B
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 22 Oct 2019 00:37:07 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id B81C0214B2
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 22 Oct 2019 00:37:07 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1730379AbfJVAfk (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 21 Oct 2019 20:35:40 -0400
Received: from mga07.intel.com ([134.134.136.100]:35281 "EHLO mga07.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1727953AbfJVAfk (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 21 Oct 2019 20:35:40 -0400
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from orsmga004.jf.intel.com ([10.7.209.38])
  by orsmga105.jf.intel.com with ESMTP/TLS/DHE-RSA-AES256-GCM-SHA384;
 21 Oct 2019 17:35:38 -0700
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.67,325,1566889200";
   d="scan'208";a="348897196"
Received: from sjchrist-coffee.jf.intel.com ([10.54.74.41])
  by orsmga004.jf.intel.com with ESMTP; 21 Oct 2019 17:35:38 -0700
From: Sean Christopherson <sean.j.christopherson@intel.com>
To: James Hogan <jhogan@kernel.org>, Paul Mackerras <paulus@ozlabs.org>,
 Christian Borntraeger <borntraeger@de.ibm.com>,
 Janosch Frank <frankja@linux.ibm.com>, Paolo Bonzini <pbonzini@redhat.com>,
	=?utf-8?b?UmFkaW0gS3LEjW3DocWZ?= <rkrcmar@redhat.com>,
 Marc Zyngier <maz@kernel.org>
Cc: David Hildenbrand <david@redhat.com>,
        Cornelia Huck <cohuck@redhat.com>,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>,
        James Morse <james.morse@arm.com>,
        Julien Thierry <julien.thierry.kdev@gmail.com>,
        Suzuki K Poulose <suzuki.poulose@arm.com>,
        linux-mips@vger.kernel.org, kvm-ppc@vger.kernel.org,
        kvm@vger.kernel.org, linux-arm-kernel@lists.infradead.org,
        kvmarm@lists.cs.columbia.edu, linux-kernel@vger.kernel.org
Subject: [PATCH v2 00/15] KVM: Dynamically size memslot arrays
Date: Mon, 21 Oct 2019 17:35:22 -0700
Message-Id: <20191022003537.13013-1-sean.j.christopherson@intel.com>
X-Mailer: git-send-email 2.22.0
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The end goal of this series is to dynamically size the memslot array so
that KVM allocates memory based on the number of memslots in use, as
opposed to unconditionally allocating memory for the maximum number of
memslots.  On x86, each memslot consumes 88 bytes, and so with 2 address
spaces of 512 memslots, each VM consumes ~90k bytes for the memslots.
E.g. given a VM that uses a total of 30 memslots, dynamic sizing reduces
the memory footprint from 90k to ~2.6k bytes.

The changes required to support dynamic sizing are relatively small,
e.g. are essentially contained in patches 12/13 and 13/13.  Patches 1-11
clean up the memslot code, which has gotten quite crusy, especially
__kvm_set_memory_region().  The clean up is likely not strictly necessary
to switch to dynamic sizing, but I didn't have a remotely reasonable
level of confidence in the correctness of the dynamic sizing without first
doing the clean up.

Testing, especially non-x86 platforms, would be greatly appreciated.  The
non-x86 changes are for all intents and purposes untested, e.g. I compile
tested pieces of the code by copying them into x86, but that's it.  In
theory, the vast majority of the functional changes are arch agnostic, in
theory...

v2:
  - Split "Drop kvm_arch_create_memslot()" into three patches to move
    minor functional changes to standalone patches [Janosch].
  - Rebase to latest kvm/queue (f0574a1cea5b, "KVM: x86: fix ...")
  - Collect an Acked-by and a Reviewed-by

Sean Christopherson (15):
  KVM: Reinstall old memslots if arch preparation fails
  KVM: Don't free new memslot if allocation of said memslot fails
  KVM: PPC: Move memslot memory allocation into prepare_memory_region()
  KVM: x86: Allocate memslot resources during prepare_memory_region()
  KVM: Drop kvm_arch_create_memslot()
  KVM: Explicitly free allocated-but-unused dirty bitmap
  KVM: Refactor error handling for setting memory region
  KVM: Move setting of memslot into helper routine
  KVM: Move memslot deletion to helper function
  KVM: Simplify kvm_free_memslot() and all its descendents
  KVM: Clean up local variable usage in __kvm_set_memory_region()
  KVM: Provide common implementation for generic dirty log functions
  KVM: Ensure validity of memslot with respect to kvm_get_dirty_log()
  KVM: Terminate memslot walks via used_slots
  KVM: Dynamically size memslot array based on number of used slots

 arch/mips/include/asm/kvm_host.h      |   2 +-
 arch/mips/kvm/mips.c                  |  68 +---
 arch/powerpc/include/asm/kvm_ppc.h    |  14 +-
 arch/powerpc/kvm/book3s.c             |  22 +-
 arch/powerpc/kvm/book3s_hv.c          |  36 +-
 arch/powerpc/kvm/book3s_pr.c          |  20 +-
 arch/powerpc/kvm/booke.c              |  17 +-
 arch/powerpc/kvm/powerpc.c            |  13 +-
 arch/s390/include/asm/kvm_host.h      |   2 +-
 arch/s390/kvm/kvm-s390.c              |  21 +-
 arch/x86/include/asm/kvm_page_track.h |   3 +-
 arch/x86/kvm/page_track.c             |  15 +-
 arch/x86/kvm/x86.c                    | 100 ++---
 include/linux/kvm_host.h              |  48 +--
 virt/kvm/arm/arm.c                    |  47 +--
 virt/kvm/arm/mmu.c                    |  18 +-
 virt/kvm/kvm_main.c                   | 546 ++++++++++++++++----------
 17 files changed, 467 insertions(+), 525 deletions(-)
```
#### [PATCH 00/45] KVM: Refactor vCPU creation
##### From: Sean Christopherson <sean.j.christopherson@intel.com>

```c
From patchwork Tue Oct 22 01:58:40 2019
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Sean Christopherson <sean.j.christopherson@intel.com>
X-Patchwork-Id: 11203587
Return-Path: <SRS0=lBCn=YP=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 938C91895
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 22 Oct 2019 02:04:03 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 721812084C
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 22 Oct 2019 02:04:03 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1730717AbfJVB7c (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 21 Oct 2019 21:59:32 -0400
Received: from mga14.intel.com ([192.55.52.115]:61583 "EHLO mga14.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1727953AbfJVB7c (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 21 Oct 2019 21:59:32 -0400
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from fmsmga008.fm.intel.com ([10.253.24.58])
  by fmsmga103.fm.intel.com with ESMTP/TLS/DHE-RSA-AES256-GCM-SHA384;
 21 Oct 2019 18:59:31 -0700
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.67,325,1566889200";
   d="scan'208";a="196293739"
Received: from sjchrist-coffee.jf.intel.com ([10.54.74.41])
  by fmsmga008.fm.intel.com with ESMTP; 21 Oct 2019 18:59:30 -0700
From: Sean Christopherson <sean.j.christopherson@intel.com>
To: Marc Zyngier <maz@kernel.org>, James Hogan <jhogan@kernel.org>,
 Paul Mackerras <paulus@ozlabs.org>,
 Christian Borntraeger <borntraeger@de.ibm.com>,
 Janosch Frank <frankja@linux.ibm.com>, Paolo Bonzini <pbonzini@redhat.com>,
	=?utf-8?b?UmFkaW0gS3LEjW3DocWZ?= <rkrcmar@redhat.com>
Cc: James Morse <james.morse@arm.com>,
        Julien Thierry <julien.thierry.kdev@gmail.com>,
        Suzuki K Poulose <suzuki.poulose@arm.com>,
        David Hildenbrand <david@redhat.com>,
        Cornelia Huck <cohuck@redhat.com>,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>,
        linux-arm-kernel@lists.infradead.org, kvmarm@lists.cs.columbia.edu,
        linux-mips@vger.kernel.org, kvm-ppc@vger.kernel.org,
        kvm@vger.kernel.org, linux-kernel@vger.kernel.org
Subject: [PATCH 00/45] KVM: Refactor vCPU creation
Date: Mon, 21 Oct 2019 18:58:40 -0700
Message-Id: <20191022015925.31916-1-sean.j.christopherson@intel.com>
X-Mailer: git-send-email 2.22.0
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

*************************** DISCLAIMER **********************************
The non-x86 arch specific patches are completely untested.  Although the
changes are conceptually straightforward, I'm not remotely confident that
the patches are bug free, e.g. checkpatch caught several blatant typos
that would break compilation.
*************************************************************************

The end goal of this series is to strip down the interface between common
KVM code and arch specific code so that there is precisely one arch hook
for creating a vCPU and one hook for destroying a vCPU.  In addition to
cleaning up the code base, simplifying the interface gives architectures
more freedom to organize their vCPU creation code.

KVM's vCPU creation code is comically messy.  kvm_vm_ioctl_create_vcpu()
calls three separate arch hooks: init(), create() and setup().  The init()
call is especially nasty as it's hidden away in a common KVM function,
kvm_init_vcpu(), that for all intents and purposes must be immediately
invoked after the vcpu object is allocated.

Not to be outdone, vCPU destruction also has three arch hooks: uninit(),
destroy() and free(), the latter of which isn't actually invoked by common
KVM code, but the hook declaration still exists because architectures are
relying on its forward declaration.

Eliminating the extra arch hooks is relatively straightforward, just
tedious.  For the most part, there is no fundamental constraint that
necessitated the proliferation of arch hooks, rather they crept in over
time, usually when x86-centric code was moved out of generic KVM and into
x86 code.

E.g. kvm_arch_vcpu_setup() was added to allow x86 to do vcpu_load(), which
can only be done after preempt_notifier initialization, but adding setup()
overlooked the fact that the preempt_notifier was only initialized after
kvm_arch_vcpu_create() because preemption support was added when x86's MMU
setup (the vcpu_load() user) was called from common KVM code.

For all intents and purposes, there is no true functional change in this
series.  The order of some allocations will change, and a few memory leaks
are fixed, but the actual functionality of a guest should be unaffected.

Patches 01-03 are bug fixes in error handling paths that were found by
inspection when refactoring the associated code.

Patches 04-43 refactor each arch implementation so that the unwanted arch
hooks can be dropped without a functional change, e.g. move code out of
kvm_arch_vcpu_setup() so that all implementations are empty, then drop the
functions and caller.

Patches 44-45 are minor clean up to eliminate kvm_vcpu_uninit().


The net result is to go from this:

        vcpu = kvm_arch_vcpu_create(kvm, id);
               |
               |-> kvm_vcpu_init()
                   |
                   |-> kvm_arch_vcpu_init()

        if (IS_ERR(vcpu)) {
                r = PTR_ERR(vcpu);
                goto vcpu_decrement;
        }

        preempt_notifier_init(&vcpu->preempt_notifier, &kvm_preempt_ops);

        r = kvm_arch_vcpu_setup(vcpu);
        if (r)
                goto vcpu_destroy;

to this:

        r = kvm_arch_vcpu_precreate(kvm, id);
        if (r)
                goto vcpu_decrement;

        vcpu = kmem_cache_zalloc(kvm_vcpu_cache, GFP_KERNEL);
        if (!vcpu) {
                r = -ENOMEM;
                goto vcpu_decrement;
        }

        page = alloc_page(GFP_KERNEL | __GFP_ZERO);
        if (!page) {
                r = -ENOMEM;
                goto vcpu_free;
        }
        vcpu->run = page_address(page);

        kvm_vcpu_init(vcpu, kvm, id);

        r = kvm_arch_vcpu_create(vcpu);
        if (r)
                goto vcpu_free_run_page;


Sean Christopherson (45):
  KVM: PPC: Book3S HV: Uninit vCPU if vcore creation fails
  KVM: PPC: Book3S PR: Free shared page if mmu initialization fails
  KVM: x86: Free wbinvd_dirty_mask if vCPU creation fails
  KVM: VMX: Allocate VPID after initializing VCPU
  KVM: VMX: Use direct vcpu pointer during vCPU create/free
  KVM: SVM: Use direct vcpu pointer during vCPU create/free
  KVM: x86: Allocate vcpu struct in common x86 code
  KVM: x86: Move FPU allocation to common x86 code
  KVM: x86: Move allocation of pio_data page down a few lines
  KVM: x86: Move kvm_vcpu_init() invocation to common code
  KVM: PPC: e500mc: Add build-time assert that vcpu is at offset 0
  KVM: PPC: Allocate vcpu struct in common PPC code
  KVM: PPC: Book3S PR: Allocate book3s and shadow vcpu after common init
  KVM: PPC: e500mc: Move reset of oldpir below call to kvm_vcpu_init()
  KVM: PPC: Move kvm_vcpu_init() invocation to common code
  KVM: MIPS: Use kvm_vcpu_cache to allocate vCPUs
  KVM: MIPS: Drop kvm_arch_vcpu_free()
  KVM: PPC: Drop kvm_arch_vcpu_free()
  KVM: arm: Drop kvm_arch_vcpu_free()
  KVM: x86: Remove spurious kvm_mmu_unload() from vcpu destruction path
  KVM: x86: Remove spurious clearing of async #PF MSR
  KVM: x86: Drop kvm_arch_vcpu_free()
  KVM: Remove kvm_arch_vcpu_free() declaration
  KVM: Add kvm_arch_vcpu_precreate() to handle pre-allocation issues
  KVM: s390: Move guts of kvm_arch_vcpu_init() into
    kvm_arch_vcpu_create()
  KVM: s390: Invoke kvm_vcpu_init() before allocating sie_page
  KVM: MIPS: Invoke kvm_vcpu_uninit() immediately prior to freeing vcpu
  KVM: x86: Invoke kvm_vcpu_uninit() immediately prior to freeing vcpu
  KVM: Introduce kvm_vcpu_destroy()
  KVM: Move vcpu alloc and init invocation to common code
  KVM: Unexport kvm_vcpu_cache and kvm_{un}init_vcpu()
  KVM: Move initialization of preempt notifier to kvm_vcpu_init()
  KVM: x86: Move guts of kvm_arch_vcpu_setup() into
    kvm_arch_vcpu_create()
  KVM: MIPS: Move .vcpu_setup() call to kvm_arch_vcpu_create()
  KVM: s390: Manually invoke vcpu setup during kvm_arch_vcpu_create()
  KVM: PPC: BookE: Setup vcpu during kvmppc_core_vcpu_create()
  KVM: Drop kvm_arch_vcpu_setup()
  KVM: x86: Move all vcpu init code into kvm_arch_vcpu_create()
  KVM: MIPS: Move all vcpu init code into kvm_arch_vcpu_create()
  KVM: ARM: Move all vcpu init code into kvm_arch_vcpu_create()
  KVM: PPC: Move all vcpu init code into kvm_arch_vcpu_create()
  KVM: arm64: Free sve_state via arm specific hook
  KVM: Drop kvm_arch_vcpu_init() and kvm_arch_vcpu_uninit()
  KVM: Move putting of vcpu->pid to kvm_vcpu_destroy()
  KVM: Move vcpu->run page allocation out of kvm_vcpu_init()

 arch/arm/include/asm/kvm_host.h    |   2 +-
 arch/arm/kvm/guest.c               |   5 -
 arch/arm64/include/asm/kvm_host.h  |   2 +-
 arch/arm64/kvm/guest.c             |   5 -
 arch/arm64/kvm/reset.c             |   2 +-
 arch/mips/kvm/mips.c               |  84 ++++-------
 arch/powerpc/include/asm/kvm_ppc.h |   6 +-
 arch/powerpc/kvm/book3s.c          |   9 +-
 arch/powerpc/kvm/book3s_hv.c       |  27 +---
 arch/powerpc/kvm/book3s_pr.c       |  33 ++---
 arch/powerpc/kvm/booke.c           |  65 ++++----
 arch/powerpc/kvm/e500.c            |  34 +----
 arch/powerpc/kvm/e500mc.c          |  32 ++--
 arch/powerpc/kvm/powerpc.c         |  70 ++++-----
 arch/s390/include/asm/kvm_host.h   |   1 -
 arch/s390/kvm/kvm-s390.c           | 110 +++++++-------
 arch/x86/include/asm/kvm_host.h    |   2 +-
 arch/x86/kvm/svm.c                 |  52 +------
 arch/x86/kvm/vmx/vmx.c             |  72 +++------
 arch/x86/kvm/x86.c                 | 230 ++++++++++++++---------------
 include/linux/kvm_host.h           |  13 +-
 virt/kvm/arm/arm.c                 |  76 ++++------
 virt/kvm/kvm_main.c                |  71 +++++----
 23 files changed, 387 insertions(+), 616 deletions(-)
```
#### [kvm-unit-tests PATCH v1 0/5] s390x: SCLP Unit test
##### From: Claudio Imbrenda <imbrenda@linux.ibm.com>

```c
From patchwork Tue Oct 22 10:52:59 2019
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Claudio Imbrenda <imbrenda@linux.ibm.com>
X-Patchwork-Id: 11204251
Return-Path: <SRS0=lBCn=YP=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 0472E14ED
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 22 Oct 2019 10:53:18 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id E24F321872
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 22 Oct 2019 10:53:17 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1730345AbfJVKxQ (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 22 Oct 2019 06:53:16 -0400
Received: from mx0a-001b2d01.pphosted.com ([148.163.156.1]:24334 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1730331AbfJVKxM (ORCPT
        <rfc822;kvm@vger.kernel.org>); Tue, 22 Oct 2019 06:53:12 -0400
Received: from pps.filterd (m0098410.ppops.net [127.0.0.1])
        by mx0a-001b2d01.pphosted.com (8.16.0.27/8.16.0.27) with SMTP id
 x9MAladA136731
        for <kvm@vger.kernel.org>; Tue, 22 Oct 2019 06:53:12 -0400
Received: from e06smtp01.uk.ibm.com (e06smtp01.uk.ibm.com [195.75.94.97])
        by mx0a-001b2d01.pphosted.com with ESMTP id 2vsyux979n-1
        (version=TLSv1.2 cipher=AES256-GCM-SHA384 bits=256 verify=NOT)
        for <kvm@vger.kernel.org>; Tue, 22 Oct 2019 06:53:11 -0400
Received: from localhost
        by e06smtp01.uk.ibm.com with IBM ESMTP SMTP Gateway: Authorized Use
 Only! Violators will be prosecuted
        for <kvm@vger.kernel.org> from <imbrenda@linux.ibm.com>;
        Tue, 22 Oct 2019 11:53:09 +0100
Received: from b06cxnps4075.portsmouth.uk.ibm.com (9.149.109.197)
        by e06smtp01.uk.ibm.com (192.168.101.131) with IBM ESMTP SMTP Gateway:
 Authorized Use Only! Violators will be prosecuted;
        (version=TLSv1/SSLv3 cipher=AES256-GCM-SHA384 bits=256/256)
        Tue, 22 Oct 2019 11:53:06 +0100
Received: from d06av21.portsmouth.uk.ibm.com (d06av21.portsmouth.uk.ibm.com
 [9.149.105.232])
        by b06cxnps4075.portsmouth.uk.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id x9MAr58D54067386
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Tue, 22 Oct 2019 10:53:05 GMT
Received: from d06av21.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 0158752050;
        Tue, 22 Oct 2019 10:53:05 +0000 (GMT)
Received: from p-imbrenda.boeblingen.de.ibm.com (unknown [9.152.224.39])
        by d06av21.portsmouth.uk.ibm.com (Postfix) with ESMTPS id BB4CD5204F;
        Tue, 22 Oct 2019 10:53:04 +0000 (GMT)
From: Claudio Imbrenda <imbrenda@linux.ibm.com>
To: kvm@vger.kernel.org
Cc: linux-s390@vger.kernel.org, thuth@redhat.com, david@redhat.com,
        borntraeger@de.ibm.com, frankja@linux.ibm.com
Subject: [kvm-unit-tests PATCH v1 0/5] s390x: SCLP Unit test
Date: Tue, 22 Oct 2019 12:52:59 +0200
X-Mailer: git-send-email 2.7.4
X-TM-AS-GCONF: 00
x-cbid: 19102210-4275-0000-0000-000003757597
X-IBM-AV-DETECTION: SAVI=unused REMOTE=unused XFE=unused
x-cbparentid: 19102210-4276-0000-0000-0000388898FB
Message-Id: <1571741584-17621-1-git-send-email-imbrenda@linux.ibm.com>
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:,,
 definitions=2019-10-22_03:,,
 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 priorityscore=1501
 malwarescore=0 suspectscore=1 phishscore=0 bulkscore=0 spamscore=0
 clxscore=1015 lowpriorityscore=0 mlxscore=0 impostorscore=0
 mlxlogscore=370 adultscore=0 classifier=spam adjust=0 reason=mlx
 scancount=1 engine=8.0.1-1908290000 definitions=main-1910220098
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This patchset contains some minor cleanup, some preparatory work and
then the SCLP unit test itself.

The unit test checks the following:
    
    * Correctly ignoring instruction bits that should be ignored
    * Privileged instruction check
    * Check for addressing exceptions
    * Specification exceptions:
      - SCCB size less than 8
      - SCCB unaligned
      - SCCB overlaps prefix or lowcore
      - SCCB address higher than 2GB
    * Return codes for
      - Invalid command
      - SCCB too short (but at least 8)
      - SCCB page boundary violation

Claudio Imbrenda (5):
  s390x: remove redundant defines
  s390x: improve error reporting for interrupts
  s390x: sclp: expose ram_size and max_ram_size
  s390x: sclp: add service call instruction wrapper
  s390x: SCLP unit test

 s390x/Makefile           |   1 +
 lib/s390x/asm/arch_def.h |  13 ++
 lib/s390x/sclp.h         |   4 +-
 lib/s390x/interrupt.c    |   4 +-
 lib/s390x/sclp.c         |  16 +-
 s390x/sclp.c             | 373 +++++++++++++++++++++++++++++++++++++++++++++++
 s390x/unittests.cfg      |   3 +
 7 files changed, 404 insertions(+), 10 deletions(-)
 create mode 100644 s390x/sclp.c
```
#### [PATCH kvm-unit-tests 0/4] x86: hyperv_stimer: test direct mode
##### From: Vitaly Kuznetsov <vkuznets@redhat.com>

```c
From patchwork Tue Oct 22 15:56:04 2019
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Vitaly Kuznetsov <vkuznets@redhat.com>
X-Patchwork-Id: 11204743
Return-Path: <SRS0=lBCn=YP=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 9237B913
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 22 Oct 2019 15:56:18 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 71C3D214E0
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 22 Oct 2019 15:56:18 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="hdqNF5Jw"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2388106AbfJVP4R (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 22 Oct 2019 11:56:17 -0400
Received: from us-smtp-1.mimecast.com ([205.139.110.61]:58158 "EHLO
        us-smtp-delivery-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S1731061AbfJVP4R (ORCPT
        <rfc822;kvm@vger.kernel.org>); Tue, 22 Oct 2019 11:56:17 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1571759776;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:content-type:content-type:
         content-transfer-encoding:content-transfer-encoding;
        bh=syfYLZ69n6ZvR2Wxg/DomdMV5PVywHfQ/vJiuX+xZw0=;
        b=hdqNF5Jwp6GhDSkgoOy6l16uYzQ9nPJZzcKL9Co5fb3TEjSA4vVUIS0um//qRVrXXSbcsy
        mZDs6dbGdpWUE0aCLAnJ1hoxvmR+v3/am/j2gSfGKH8Ra40CrvxJJf63cgIL91t1P+f2wY
        6blDivGu+TuW0F2jhZhjoFMRh+LH+hE=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-290-s7q-IpU4MSSmufE_YLR0TA-1; Tue, 22 Oct 2019 11:56:13 -0400
Received: from smtp.corp.redhat.com (int-mx05.intmail.prod.int.phx2.redhat.com
 [10.5.11.15])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 27D34107AD31;
        Tue, 22 Oct 2019 15:56:12 +0000 (UTC)
Received: from vitty.brq.redhat.com (unknown [10.43.2.155])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 963155D6A9;
        Tue, 22 Oct 2019 15:56:09 +0000 (UTC)
From: Vitaly Kuznetsov <vkuznets@redhat.com>
To: kvm@vger.kernel.org
Cc: Paolo Bonzini <pbonzini@redhat.com>,
        Roman Kagan <rkagan@virtuozzo.com>
Subject: [PATCH kvm-unit-tests 0/4] x86: hyperv_stimer: test direct mode
Date: Tue, 22 Oct 2019 17:56:04 +0200
Message-Id: <20191022155608.8001-1-vkuznets@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.15
X-MC-Unique: s7q-IpU4MSSmufE_YLR0TA-1
X-Mimecast-Spam-Score: 0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

I should've done that when QEMU patche for 'hv_stimer_direct' landed but
better late than never, right?

Testing 'direct' mode requires us to add 'hv_stimer_direct' CPU flag to
QEMU, create a new entry in unittests.cfg to not lose the ability to test
stimers in 'message' mode with older QEMUs/kernels. Unfortunately, a
failure with './run_tests' will still be visible.

Vitaly Kuznetsov (4):
  x86: hyperv_stimer: keep SINT number parameter in 'struct stimer'
  x86: hyperv_stimer: define union hv_stimer_config
  x86: hyperv_stimer: don't require hyperv-testdev
  x86: hyperv_stimer: add direct mode tests

 x86/hyperv.h        |  29 +++++++--
 x86/hyperv_stimer.c | 152 ++++++++++++++++++++++++++++++++++----------
 x86/unittests.cfg   |   8 ++-
 3 files changed, 150 insertions(+), 39 deletions(-)
```
#### [PATCH 0/3] kcov: collect coverage from usb and vhost
##### From: Andrey Konovalov <andreyknvl@google.com>

```c
From patchwork Tue Oct 22 16:46:30 2019
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Andrey Konovalov <andreyknvl@google.com>
X-Patchwork-Id: 11204867
Return-Path: <SRS0=lBCn=YP=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 983B114E5
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 22 Oct 2019 16:46:42 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 75C1A21BE5
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 22 Oct 2019 16:46:42 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=google.com header.i=@google.com
 header.b="bwG8FsZz"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2389520AbfJVQql (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 22 Oct 2019 12:46:41 -0400
Received: from mail-wr1-f73.google.com ([209.85.221.73]:52138 "EHLO
        mail-wr1-f73.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S2389061AbfJVQql (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 22 Oct 2019 12:46:41 -0400
Received: by mail-wr1-f73.google.com with SMTP id 67so9416486wrm.18
        for <kvm@vger.kernel.org>; Tue, 22 Oct 2019 09:46:38 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=date:message-id:mime-version:subject:from:to:cc;
        bh=FxzIQyDunHtVBZCVK6ttUg3oB9s0DEBjz5E3R+aCqJU=;
        b=bwG8FsZzFAPaLXF+EeN/hUCP9Ctc2PqOreWk2uXXPC1rx7igFgoYTwQmMPUoum8kN2
         BCDHyY+9Y3k4GDqLnxZX4DJeS4dHVZz2+0dRswv3cdpUzr/TwgGbwwFH8QyCXUgUjuhZ
         Nks82aX0zUMLehsuEDOPYo2bHPgtiRFXEe4h7LU+Z1NBLKnIwZRQ2yBDEq33H4IQb/8R
         eNidmD5c9kaZE2RILTyQvcpk2qanv245jpGAsz/TPPZSFFwDGPHmUQKp1M3LWnrLJXq7
         NuTimyO/udpVPVqtAL1NOviEG57gds0FKsZoYgaXz6fcekzuyx53kphtB0HI5IqkuVvQ
         aoDw==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:date:message-id:mime-version:subject:from:to:cc;
        bh=FxzIQyDunHtVBZCVK6ttUg3oB9s0DEBjz5E3R+aCqJU=;
        b=grgNhh1J/VVDOESAQAn59oAxVUBgKOXesUKBgy7Eyn+KRY4V3qMZCCRx+oa8fzsZVp
         tcIAVRkAgr5lMdL2GqPX25u0SCDMybEO01Fk1AHgAtprETDmnqZvZ1iLPTf7IN81SgnO
         hudquLtkGBOOdORr/sijTKVMtlHldhQTB3uhhBkCYrcI7ucXLa8jrUI3jPBQ/vwqk2U0
         mkxdoZgSNcm0g4jMnoOPqZwBeI7ZohL7DOJXNhD0j1ywjuNVFjthQ8Z56/iZuoKs51Py
         /+4VPLb9/NpOcT7TmDsYxXfUnGO1LiNFNKyIy+Yn9lkS5Bwy06NDqH5yKGSpXiYZKKS5
         EVaw==
X-Gm-Message-State: APjAAAXlsU4KkEZ7NE0uApCHc0v/w3kmAiXmAEMAsF0Vj5y3WEJ2Vi5Y
        BPQU2gBg+m5X56y8F/A3TehuHsVhAsPbNu4c
X-Google-Smtp-Source: 
 APXvYqzw4xdCDUIijFFJk3ia1kfm+QpMoPGMUaeGlY+KJBFhy0thno5gFZaPKu1JXCicdUguQwe6wX+B/HIHHpRY
X-Received: by 2002:a5d:4644:: with SMTP id j4mr944846wrs.355.1571762797288;
 Tue, 22 Oct 2019 09:46:37 -0700 (PDT)
Date: Tue, 22 Oct 2019 18:46:30 +0200
Message-Id: <cover.1571762488.git.andreyknvl@google.com>
Mime-Version: 1.0
X-Mailer: git-send-email 2.23.0.866.gb869b98d4c-goog
Subject: [PATCH 0/3] kcov: collect coverage from usb and vhost
From: Andrey Konovalov <andreyknvl@google.com>
To: linux-usb@vger.kernel.org, kvm@vger.kernel.org,
        virtualization@lists.linux-foundation.org, netdev@vger.kernel.org,
        linux-kernel@vger.kernel.org, Dmitry Vyukov <dvyukov@google.com>,
        Greg Kroah-Hartman <gregkh@linuxfoundation.org>,
        Alan Stern <stern@rowland.harvard.edu>,
        "Michael S . Tsirkin" <mst@redhat.com>,
        Jason Wang <jasowang@redhat.com>
Cc: Andrew Morton <akpm@linux-foundation.org>,
        Arnd Bergmann <arnd@arndb.de>,
        Steven Rostedt <rostedt@goodmis.org>,
        David Windsor <dwindsor@gmail.com>,
        Elena Reshetova <elena.reshetova@intel.com>,
        Anders Roxell <anders.roxell@linaro.org>,
        Andrey Konovalov <andreyknvl@google.com>
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This patchset extends kcov to allow collecting coverage from the USB
subsystem and vhost workers. See the first patch description for details
about the kcov extension. The other two patches apply this kcov extension
to USB and vhost.

These patches have been used to enable coverage-guided USB fuzzing with
syzkaller for the last few years, see the details here:

https://github.com/google/syzkaller/blob/master/docs/linux/external_fuzzing_usb.md

This patchset has been pushed to the public Linux kernel Gerrit instance:

https://linux-review.googlesource.com/c/linux/kernel/git/torvalds/linux/+/1524

Changes from RFC v1:
- Remove unnecessary #ifdef's from drivers/vhost/vhost.c.
- Reset t->kcov when area allocation fails in kcov_remote_start().
- Use struct_size to calculate array size in kcov_ioctl().
- Add a limit on area_size in kcov_remote_arg.
- Added kcov_disable() helper.
- Changed encoding of kcov remote handle ids, see the documentation.
- Added a comment reference for kcov_sequence task_struct field.
- Change common_handle type to u32.
- Add checks for handle validity into kcov_ioctl_locked() and
    kcov_remote_start().
- Updated documentation to reflect the changes.

Andrey Konovalov (3):
  kcov: remote coverage support
  usb, kcov: collect coverage from hub_event
  vhost, kcov: collect coverage from vhost_worker

 Documentation/dev-tools/kcov.rst | 120 ++++++++
 drivers/usb/core/hub.c           |   5 +
 drivers/vhost/vhost.c            |   6 +
 drivers/vhost/vhost.h            |   1 +
 include/linux/kcov.h             |   6 +
 include/linux/sched.h            |   6 +
 include/uapi/linux/kcov.h        |  20 ++
 kernel/kcov.c                    | 464 ++++++++++++++++++++++++++++---
 8 files changed, 593 insertions(+), 35 deletions(-)
```
#### [PATCH v12 0/6] mm / virtio: Provide support for unused page
##### From: Alexander Duyck <alexander.duyck@gmail.com>

```c
From patchwork Tue Oct 22 22:27:52 2019
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Alexander Duyck <alexander.duyck@gmail.com>
X-Patchwork-Id: 11205403
Return-Path: <SRS0=lBCn=YP=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 789B1913
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 22 Oct 2019 22:28:01 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 4E74E207FC
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 22 Oct 2019 22:28:01 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=gmail.com header.i=@gmail.com
 header.b="kf9SehCN"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2388287AbfJVW14 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 22 Oct 2019 18:27:56 -0400
Received: from mail-pg1-f193.google.com ([209.85.215.193]:42516 "EHLO
        mail-pg1-f193.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S2388172AbfJVW1z (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 22 Oct 2019 18:27:55 -0400
Received: by mail-pg1-f193.google.com with SMTP id f14so10800523pgi.9;
        Tue, 22 Oct 2019 15:27:54 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=subject:from:to:cc:date:message-id:user-agent:mime-version
         :content-transfer-encoding;
        bh=J0Cde3YCRyKb7sVda9AuSr3SUq1DFyMrFHgfTQRevNg=;
        b=kf9SehCNiEcM+GfhpzKh3NyW4ANcI4Qdoy/zWsrS/DaZYbQEvhhtjhO5o55SoORHVz
         kSiuvyY8pV6mlTEHPalaOwwbRqM0mBd2Drmym4mBY7jVdS4C0PSddXT9sePiecgGvYUE
         JVI1qNOYbEO0iOiOQETNouy/sRKJ/czZqmabrurDDThDhkLiBuj1+3o5c3LwXcFTAtxo
         zjumP+IQlO/rDNVbhKHSlpcYKWBes7iePihLor2Nr6QdefABT76ujZbKFE7TfNyAe68e
         84blhV53Q9HSAUfH72G4PO/cAqAjqbDo7slsDOGzq4P0drmRP/c+0FSDlgWpLM7Nhf8u
         xi8g==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:subject:from:to:cc:date:message-id:user-agent
         :mime-version:content-transfer-encoding;
        bh=J0Cde3YCRyKb7sVda9AuSr3SUq1DFyMrFHgfTQRevNg=;
        b=EfdnMSy95i8jqNvlX5Ip+p0WnprYI9JORIzGwD9mWPyYYhrdJ/kKLiZBSHFtR+CRV6
         wjf/VPfOzhlVBWg+AaoNGfy5eBnkatBTr72DLAxI97Bk4wxSh0PXZOZPcENMm6fsG7u7
         33iNalFToYwIOEeMp8SSFzpdP0LnZxCBRnsHJIR66l2PfTKJN24jYcOcio3jIvWcr/Ox
         n71hfB/o11zyJo/nfvqApRIKz7gSv1IJrAUupP1+gsPsPX612eXPfh5C7JdtkoszodSx
         elzyC4nHrYwt+mKqH56WpuLy2y66IW2WPsutTS8Ce5UqQmobs0R5fJV+Q4MC/NNx1I6E
         sYUw==
X-Gm-Message-State: APjAAAVqaSdoB4jFZpHC1yB9nTBi+2c1g38sAweF3zhQ7GilWD/qahfE
        Qxgq84C+WrCoA7DaonAfNQU=
X-Google-Smtp-Source: 
 APXvYqxUpZCIgjB/RhowJmJMcKSaevo7BJq4WvFJyIaGUi8Z6RPUU8dpXpcsYruoZJ6BMwX+j5xojA==
X-Received: by 2002:aa7:9715:: with SMTP id a21mr6913876pfg.144.1571783274147;
        Tue, 22 Oct 2019 15:27:54 -0700 (PDT)
Received: from localhost.localdomain ([2001:470:b:9c3:9e5c:8eff:fe4f:f2d0])
        by smtp.gmail.com with ESMTPSA id
 y15sm29621200pfp.111.2019.10.22.15.27.52
        (version=TLS1_2 cipher=ECDHE-RSA-AES128-GCM-SHA256 bits=128/128);
        Tue, 22 Oct 2019 15:27:53 -0700 (PDT)
Subject: [PATCH v12 0/6] mm / virtio: Provide support for unused page
 reporting
From: Alexander Duyck <alexander.duyck@gmail.com>
To: kvm@vger.kernel.org, mst@redhat.com, linux-kernel@vger.kernel.org,
        willy@infradead.org, mhocko@kernel.org, linux-mm@kvack.org,
        akpm@linux-foundation.org, mgorman@techsingularity.net,
        vbabka@suse.cz
Cc: yang.zhang.wz@gmail.com, nitesh@redhat.com, konrad.wilk@oracle.com,
        david@redhat.com, pagupta@redhat.com, riel@surriel.com,
        lcapitulino@redhat.com, dave.hansen@intel.com,
        wei.w.wang@intel.com, aarcange@redhat.com, pbonzini@redhat.com,
        dan.j.williams@intel.com, alexander.h.duyck@linux.intel.com,
        osalvador@suse.de
Date: Tue, 22 Oct 2019 15:27:52 -0700
Message-ID: <20191022221223.17338.5860.stgit@localhost.localdomain>
User-Agent: StGit/0.17.1-dirty
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This series provides an asynchronous means of reporting unused guest
pages to a hypervisor so that the memory associated with those pages can
be dropped and reused by other processes and/or guests.

When enabled it will allocate a set of statistics to track the number of
reported pages. When the nr_free for a given free_area is greater than
this by the high water mark we will schedule a worker to begin allocating
the non-reported memory and to provide it to the reporting interface via a
scatterlist.

Currently this is only in use by virtio-balloon however there is the hope
that at some point in the future other hypervisors might be able to make
use of it. In the virtio-balloon/QEMU implementation the hypervisor is
currently using MADV_DONTNEED to indicate to the host kernel that the page
is currently unused. It will be faulted back into the guest the next time
the page is accessed.

To track if a page is reported or not the Uptodate flag was repurposed and
used as a Reported flag for Buddy pages. While we are processing the pages
in a given zone we have a set of pointers we track called
reported_boundary that is used to keep our processing time to a minimum.
Without these we would have to iterate through all of the reported pages
which would become a significant burden. I measured as much as a 20%
performance degradation without using the boundary pointers. In the event
of something like compaction needing to process the zone at the same time
it currently resorts to resetting the boundary if it is rearranging the
list. However in the future it could choose to delay processing the zone
if a flag is set indicating that a zone is being actively processed.

Below are the results from various benchmarks. I primarily focused on two
tests. The first is the will-it-scale/page_fault2 test, and the other is
a modified version of will-it-scale/page_fault1 that was enabled to use
THP. I did this as it allows for better visibility into different parts
of the memory subsystem. The guest is running on one node of a E5-2630 v3
CPU with 48G of RAM that I split up into two logical nodes in the guest
in order to test with NUMA as well.

Test		    page_fault1 (THP)     page_fault2
Baseline	 1  1256106.33  +/-0.09%   482202.67  +/-0.46%
                16  8864441.67  +/-0.09%  3734692.00  +/-1.23%

Patches applied  1  1257096.00  +/-0.06%   477436.00  +/-0.16%
                16  8864677.33  +/-0.06%  3800037.00  +/-0.19%

Patches enabled	 1  1258420.00  +/-0.04%   480080.00  +/-0.07%
 MADV disabled  16  8753840.00  +/-1.27%  3782764.00  +/-0.37%

Patches enabled	 1  1267916.33  +/-0.08%   472075.67  +/-0.39%
                16  8287050.33  +/-0.67%  3774500.33  +/-0.11%

The results above are for a baseline with a linux-next-20191021 kernel,
that kernel with this patch set applied but page reporting disabled in
virtio-balloon, patches applied but the madvise disabled by direct
assigning a device, and the patches applied and page reporting fully
enabled.  These results include the deviation seen between the average
value reported here versus the high and/or low value. I observed that
during the test the memory usage for the first three tests never dropped
whereas with the patches fully enabled the VM would drop to using only a
few GB of the host's memory when switching from memhog to page fault tests.

Most of the overhead seen with this patch set fully enabled is due to the
fact that accessing the reported pages will cause a page fault and the host
will have to zero the page before giving it back to the guest. The overall
guest size is kept fairly small to only a few GB while the test is running.
This overhead is much more visible when using THP than with standard 4K
pages. As such for the case where the host memory is not oversubscribed
this results in a performance regression, however if the host memory were
oversubscribed this patch set should result in a performance improvement
as swapping memory from the host can be avoided.

There is currently an alternative patch set[1] that has been under work
for some time however the v12 version of that patch set could not be
tested as it triggered a kernel panic when I attempted to test it. It
requires multiple modifications to get up and running with performance
comparable to this patch set. A follow-on set has yet to be posted. As
such I have not included results from that patch set, and I would
appreciate it if we could keep this patch set the focus of any discussion
on this thread.

For info on earlier versions you will need to follow the links provided
with the respective versions.

[1]: https://lore.kernel.org/lkml/20190812131235.27244-1-nitesh@redhat.com/

Changes from v10:
https://lore.kernel.org/lkml/20190918175109.23474.67039.stgit@localhost.localdomain/
Rebased on "Add linux-next specific files for 20190930"
Added page_is_reported() macro to prevent unneeded testing of PageReported bit
Fixed several spots where comments referred to older aeration naming
Set upper limit for phdev->capacity to page reporting high water mark
Updated virtio page poison detection logic to also cover init_on_free
Tweaked page_reporting_notify_free to reduce code size
Removed dead code in non-reporting path

Changes from v11:
https://lore.kernel.org/lkml/20191001152441.27008.99285.stgit@localhost.localdomain/
Removed unnecessary whitespace change from patch 2
Minor tweak to get_unreported_page to avoid excess writes to boundary
Rewrote cover page to lay out additional performance info.
---

Alexander Duyck (6):
      mm: Adjust shuffle code to allow for future coalescing
      mm: Use zone and order instead of free area in free_list manipulators
      mm: Introduce Reported pages
      mm: Add device side and notifier for unused page reporting
      virtio-balloon: Pull page poisoning config out of free page hinting
      virtio-balloon: Add support for providing unused page reports to host


 drivers/virtio/Kconfig              |    1 
 drivers/virtio/virtio_balloon.c     |   88 ++++++++-
 include/linux/mmzone.h              |   60 ++----
 include/linux/page-flags.h          |   11 +
 include/linux/page_reporting.h      |   31 +++
 include/uapi/linux/virtio_balloon.h |    1 
 mm/Kconfig                          |   11 +
 mm/Makefile                         |    1 
 mm/compaction.c                     |    5 
 mm/memory_hotplug.c                 |    2 
 mm/page_alloc.c                     |  194 +++++++++++++++----
 mm/page_reporting.c                 |  353 +++++++++++++++++++++++++++++++++++
 mm/page_reporting.h                 |  225 ++++++++++++++++++++++
 mm/shuffle.c                        |   12 +
 mm/shuffle.h                        |    6 +
 15 files changed, 899 insertions(+), 102 deletions(-)
 create mode 100644 include/linux/page_reporting.h
 create mode 100644 mm/page_reporting.c
 create mode 100644 mm/page_reporting.h

--
```
