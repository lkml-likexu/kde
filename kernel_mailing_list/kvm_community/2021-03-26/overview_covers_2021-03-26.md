

#### [PATCH 00/18] KVM: Consolidate and optimize MMU notifiers
##### From: Sean Christopherson <seanjc@google.com>

```c
From patchwork Fri Mar 26 02:19:39 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Sean Christopherson <seanjc@google.com>
X-Patchwork-Id: 12165535
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-21.3 required=3.0 tests=BAYES_00,DKIMWL_WL_MED,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT,
	USER_IN_DEF_DKIM_WL autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id CCE11C433DB
	for <kvm@archiver.kernel.org>; Fri, 26 Mar 2021 02:20:46 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id A5A7A61A2B
	for <kvm@archiver.kernel.org>; Fri, 26 Mar 2021 02:20:46 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S230022AbhCZCUO (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Thu, 25 Mar 2021 22:20:14 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:35198 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S230158AbhCZCUL (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 25 Mar 2021 22:20:11 -0400
Received: from mail-yb1-xb49.google.com (mail-yb1-xb49.google.com
 [IPv6:2607:f8b0:4864:20::b49])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 08271C061761
        for <kvm@vger.kernel.org>; Thu, 25 Mar 2021 19:20:11 -0700 (PDT)
Received: by mail-yb1-xb49.google.com with SMTP id k189so8341052ybb.17
        for <kvm@vger.kernel.org>; Thu, 25 Mar 2021 19:20:11 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=reply-to:date:message-id:mime-version:subject:from:to:cc;
        bh=H54os4ygqofHn1WGMEZDcGVdM5o6qUhwH/wT9+rGWSk=;
        b=ecGB21RKe7x71J+6hRcQeYU5JJ7wFAYU9S5q0hjnh5cFdjsPshHHo+BbrBLobCCFKv
         NZKCDM+RhzB7lqPfAOQS3wauBG9Wt6dz84hgF6QN0gdxezNEhe2IHZ9vnbrRjrQZmatX
         aA6unphmRZB9N8MgD7gtQcsLImor+8acXPyEPXdyuDiz+MgeWawbq8OlTcav3Ozoecet
         jA89TWp1kJjZ1yiJ5iklCOGzc1mwEVvY5U1Bo/RoRvmKHnulFKlRQcuSDWeTploTW+Ib
         p9YcLsgB2yhWz6jRMLj6HbocX9JL7d0WI1vXfS58F6E5owlm0a29FNCvV5oX9+xsL/Wl
         SB1A==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:reply-to:date:message-id:mime-version:subject
         :from:to:cc;
        bh=H54os4ygqofHn1WGMEZDcGVdM5o6qUhwH/wT9+rGWSk=;
        b=gkw6qXbko09kipscMaDzEf3HN+6FDEiAFQYtGv5WbAdK0KD3jYJZIFPtmXZGd2KrOc
         AMhtpCD6xN8xUFawUpHKmyXxHq2EW6iWFxSg9MPvCuvO0Tjg+YxD3ySiJBa5TuFCVJyl
         K7k++aU1bTQ7MkNHGX2vhggtCWJfxOOR/XFV3IpJSpEwosSv7KjjQ850/etiawN/ytpI
         +pX5bvxvpTujegeMJk3BfxTMp/WSyPndzUGDaQWusI/DIEB5amfF2sR/KWeDWNY9GPns
         NC6KNPxTFtsCyouD629A3Fh8fK0cWmchdGWNbTZbh6jAOYcAaJP6ZpkUEF7XkR47m+WY
         AI+Q==
X-Gm-Message-State: AOAM5323zWkmX6jJImDgllL/IH6bHybOUbbDBm1clp24HfjfXRMB3wTt
        1WoidxQSWLZ/OOWNtq6NiAbi25vJE/Y=
X-Google-Smtp-Source: 
 ABdhPJyiUWYORNUHyA8HYU5z2Afa3KK2uvzs30OB8QjgL1a1U3zQY52m5lnijJTDVWnHZyILMRS2XSl6DRU=
X-Received: from seanjc798194.pdx.corp.google.com
 ([2620:15c:f:10:b1bb:fab2:7ef5:fc7d])
 (user=seanjc job=sendgmr) by 2002:a5b:18d:: with SMTP id
 r13mr17361673ybl.184.1616725210248;
 Thu, 25 Mar 2021 19:20:10 -0700 (PDT)
Reply-To: Sean Christopherson <seanjc@google.com>
Date: Thu, 25 Mar 2021 19:19:39 -0700
Message-Id: <20210326021957.1424875-1-seanjc@google.com>
Mime-Version: 1.0
X-Mailer: git-send-email 2.31.0.291.g576ba9dcdaf-goog
Subject: [PATCH 00/18] KVM: Consolidate and optimize MMU notifiers
From: Sean Christopherson <seanjc@google.com>
To: Marc Zyngier <maz@kernel.org>, Huacai Chen <chenhuacai@kernel.org>,
        Aleksandar Markovic <aleksandar.qemu.devel@gmail.com>,
        Paul Mackerras <paulus@ozlabs.org>,
        Paolo Bonzini <pbonzini@redhat.com>
Cc: James Morse <james.morse@arm.com>,
        Julien Thierry <julien.thierry.kdev@gmail.com>,
        Suzuki K Poulose <suzuki.poulose@arm.com>,
        Sean Christopherson <seanjc@google.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>,
        linux-arm-kernel@lists.infradead.org, kvmarm@lists.cs.columbia.edu,
        linux-mips@vger.kernel.org, kvm@vger.kernel.org,
        kvm-ppc@vger.kernel.org, linux-kernel@vger.kernel.org,
        Ben Gardon <bgardon@google.com>
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The end goal of this series is to optimize the MMU notifiers to take
mmu_lock if and only if the notification is relevant to KVM, i.e. the hva
range overlaps a memslot.   Large VMs (hundreds of vCPUs) are very
sensitive to mmu_lock being taken for write at inopportune times, and
such VMs also tend to be "static", e.g. backed by HugeTLB with minimal
page shenanigans.  The vast majority of notifications for these VMs will
be spurious (for KVM), and eliding mmu_lock for spurious notifications
avoids an otherwise unacceptable disruption to the guest.

To get there without potentially degrading performance, e.g. due to
multiple memslot lookups, especially on non-x86 where the use cases are
largely unknown (from my perspective), first consolidate the MMU notifier
logic by moving the hva->gfn lookups into common KVM.

Applies on my TDP MMU TLB flushing bug fixes[*], which conflict horribly
with the TDP MMU changes in this series.  That code applies on kvm/queue
(commit 4a98623d5d90, "KVM: x86/mmu: Mark the PAE roots as decrypted for
shadow paging").

Speaking of conflicts, Ben will soon be posting a series to convert a
bunch of TDP MMU flows to take mmu_lock only for read.  Presumably there
will be an absurd number of conflicts; Ben and I will sort out the
conflicts in whichever series loses the race.

Well tested on Intel and AMD.  Compile tested for arm64, MIPS, PPC,
PPC e500, and s390.  Absolutely needs to be tested for real on non-x86,
I give it even odds that I introduced an off-by-one bug somewhere.

[*] https://lkml.kernel.org/r/20210325200119.1359384-1-seanjc@google.com


Patches 1-7 are x86 specific prep patches to play nice with moving
the hva->gfn memslot lookups into common code.  There ended up being waaay
more of these than I expected/wanted, but I had a hell of a time getting
the flushing logic right when shuffling the memslot and address space
loops.  In the end, I was more confident I got things correct by batching
the flushes.

Patch 8 moves the existing API prototypes into common code.  It could
technically be dropped since the old APIs are gone in the end, but I
thought the switch to the new APIs would suck a bit less this way.

Patch 9 moves arm64's MMU notifier tracepoints into common code so that
they are not lost when arm64 is converted to the new APIs, and so that all
architectures can benefit.

Patch 10 moves x86's memslot walkers into common KVM.  I chose x86 purely
because I could actually test it.  All architectures use nearly identical
code, so I don't think it actually matters in the end.

Patches 11-13 move arm64, MIPS, and PPC to the new APIs.

Patch 14 yanks out the old APIs.

Patch 15 adds the mmu_lock elision, but only for unpaired notifications.

Patch 16 adds mmu_lock elision for paired .invalidate_range_{start,end}().
This is quite nasty and no small part of me thinks the patch should be
burned with fire (I won't spoil it any further), but it's also the most
problematic scenario for our particular use case.  :-/

Patches 17-18 are additional x86 cleanups.

Sean Christopherson (18):
  KVM: x86/mmu: Coalesce TDP MMU TLB flushes when zapping collapsible
    SPTEs
  KVM: x86/mmu: Move flushing for "slot" handlers to caller for legacy
    MMU
  KVM: x86/mmu: Coalesce TLB flushes when zapping collapsible SPTEs
  KVM: x86/mmu: Coalesce TLB flushes across address spaces for gfn range
    zap
  KVM: x86/mmu: Pass address space ID to __kvm_tdp_mmu_zap_gfn_range()
  KVM: x86/mmu: Pass address space ID to TDP MMU root walkers
  KVM: x86/mmu: Use leaf-only loop for walking TDP SPTEs when changing
    SPTE
  KVM: Move prototypes for MMU notifier callbacks to generic code
  KVM: Move arm64's MMU notifier trace events to generic code
  KVM: Move x86's MMU notifier memslot walkers to generic code
  KVM: arm64: Convert to the gfn-based MMU notifier callbacks
  KVM: MIPS/MMU: Convert to the gfn-based MMU notifier callbacks
  KVM: PPC: Convert to the gfn-based MMU notifier callbacks
  KVM: Kill off the old hva-based MMU notifier callbacks
  KVM: Take mmu_lock when handling MMU notifier iff the hva hits a
    memslot
  KVM: Don't take mmu_lock for range invalidation unless necessary
  KVM: x86/mmu: Allow yielding during MMU notifier unmap/zap, if
    possible
  KVM: x86/mmu: Drop trace_kvm_age_page() tracepoint

 arch/arm64/include/asm/kvm_host.h             |   5 -
 arch/arm64/kvm/mmu.c                          | 118 ++----
 arch/arm64/kvm/trace_arm.h                    |  66 ----
 arch/mips/include/asm/kvm_host.h              |   5 -
 arch/mips/kvm/mmu.c                           |  97 +----
 arch/powerpc/include/asm/kvm_book3s.h         |  12 +-
 arch/powerpc/include/asm/kvm_host.h           |   7 -
 arch/powerpc/include/asm/kvm_ppc.h            |   9 +-
 arch/powerpc/kvm/book3s.c                     |  18 +-
 arch/powerpc/kvm/book3s.h                     |  10 +-
 arch/powerpc/kvm/book3s_64_mmu_hv.c           |  98 ++---
 arch/powerpc/kvm/book3s_64_mmu_radix.c        |  25 +-
 arch/powerpc/kvm/book3s_hv.c                  |  12 +-
 arch/powerpc/kvm/book3s_pr.c                  |  56 +--
 arch/powerpc/kvm/e500_mmu_host.c              |  29 +-
 arch/powerpc/kvm/trace_booke.h                |  15 -
 arch/x86/include/asm/kvm_host.h               |   6 +-
 arch/x86/kvm/mmu/mmu.c                        | 180 ++++-----
 arch/x86/kvm/mmu/mmu_internal.h               |  10 +
 arch/x86/kvm/mmu/tdp_mmu.c                    | 344 +++++++-----------
 arch/x86/kvm/mmu/tdp_mmu.h                    |  31 +-
 include/linux/kvm_host.h                      |  22 +-
 include/trace/events/kvm.h                    |  90 +++--
 tools/testing/selftests/kvm/lib/kvm_util.c    |   4 -
 .../selftests/kvm/lib/x86_64/processor.c      |   2 +
 virt/kvm/kvm_main.c                           | 312 ++++++++++++----
 26 files changed, 697 insertions(+), 886 deletions(-)
```
#### [RFC PATCH v3 0/2] KVM: arm64: Improve efficiency of stage2 page
##### From: Yanan Wang <wangyanan55@huawei.com>

```c
From patchwork Fri Mar 26 03:16:52 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Yanan Wang <wangyanan55@huawei.com>
X-Patchwork-Id: 12165725
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-11.8 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,
	SPF_PASS,USER_AGENT_GIT autolearn=unavailable autolearn_force=no
 version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id A3B8EC433E0
	for <kvm@archiver.kernel.org>; Fri, 26 Mar 2021 03:18:40 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 4D94761A43
	for <kvm@archiver.kernel.org>; Fri, 26 Mar 2021 03:18:40 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S230487AbhCZDSM (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Thu, 25 Mar 2021 23:18:12 -0400
Received: from szxga05-in.huawei.com ([45.249.212.191]:14552 "EHLO
        szxga05-in.huawei.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S230273AbhCZDRg (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 25 Mar 2021 23:17:36 -0400
Received: from DGGEMS409-HUB.china.huawei.com (unknown [172.30.72.60])
        by szxga05-in.huawei.com (SkyGuard) with ESMTP id 4F66Xg5MWCzPmsB;
        Fri, 26 Mar 2021 11:14:59 +0800 (CST)
Received: from DESKTOP-TMVL5KK.china.huawei.com (10.174.187.128) by
 DGGEMS409-HUB.china.huawei.com (10.3.19.209) with Microsoft SMTP Server id
 14.3.498.0; Fri, 26 Mar 2021 11:17:25 +0800
From: Yanan Wang <wangyanan55@huawei.com>
To: Marc Zyngier <maz@kernel.org>, Will Deacon <will@kernel.org>,
        "Alexandru Elisei" <alexandru.elisei@arm.com>,
        Catalin Marinas <catalin.marinas@arm.com>,
        <kvmarm@lists.cs.columbia.edu>,
        <linux-arm-kernel@lists.infradead.org>, <kvm@vger.kernel.org>,
        <linux-kernel@vger.kernel.org>
CC: James Morse <james.morse@arm.com>,
        Julien Thierry <julien.thierry.kdev@gmail.com>,
        Suzuki K Poulose <suzuki.poulose@arm.com>,
        Gavin Shan <gshan@redhat.com>,
        Quentin Perret <qperret@google.com>,
        <wanghaibin.wang@huawei.com>, <zhukeqian1@huawei.com>,
        <yuzenghui@huawei.com>, Yanan Wang <wangyanan55@huawei.com>
Subject: [RFC PATCH v3 0/2] KVM: arm64: Improve efficiency of stage2 page
 table
Date: Fri, 26 Mar 2021 11:16:52 +0800
Message-ID: <20210326031654.3716-1-wangyanan55@huawei.com>
X-Mailer: git-send-email 2.8.4.windows.1
MIME-Version: 1.0
X-Originating-IP: [10.174.187.128]
X-CFilter-Loop: Reflected
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Hi,

This is a new version of the series [1] that I have posted before. It makes some
efficiency improvement of stage2 page table code and there are some test results
to quantify the benefit of each patch.
[1] v2: https://lore.kernel.org/lkml/20210310094319.18760-1-wangyanan55@huawei.com/

Although there hasn't been any feedback about v2, I am certain that there should
be a big change for the series after plenty of discussion with Alexandru Elisei.
A conclusion was drew that CMOs are still needed for the scenario of coalescing
tables, and as a result the benefit of patch #3 in v2 becomes rather little
judging from the test results. So drop this patch and keep the others which
still remain meaningful.

Changelogs:
v2->v3:
- drop patch #3 in v2
- retest v3 based on v5.12-rc2

v1->v2:
- rebased on top of mainline v5.12-rc2
- also move CMOs of I-cache to the fault handlers
- retest v2 based on v5.12-rc2
- v1: https://lore.kernel.org/lkml/20210208112250.163568-1-wangyanan55@huawei.com/

About this v3 series:
Patch #1:
We currently uniformly permorm CMOs of D-cache and I-cache in function
user_mem_abort before calling the fault handlers. If we get concurrent
guest faults(e.g. translation faults, permission faults) or some really
unnecessary guest faults caused by BBM, CMOs for the first vcpu are
necessary while the others later are not.

By moving CMOs to the fault handlers, we can easily identify conditions
where they are really needed and avoid the unnecessary ones. As it's a
time consuming process to perform CMOs especially when flushing a block
range, so this solution reduces much load of kvm and improve efficiency
of the page table code.

So let's move both clean of D-cache and invalidation of I-cache to the
map path and move only invalidation of I-cache to the permission path.
Since the original APIs for CMOs in mmu.c are only called in function
user_mem_abort, we now also move them to pgtable.c.

The following results represent the benefit of patch #1 alone, and they
were tested by [2] (kvm/selftest) that I have posted recently.
[2] https://lore.kernel.org/lkml/20210302125751.19080-1-wangyanan55@huawei.com/

When there are muitiple vcpus concurrently accessing the same memory region,
we can test the execution time of KVM creating new mappings, updating the
permissions of old mappings from RO to RW, and rebuilding the blocks after
they have been split.

hardware platform: HiSilicon Kunpeng920 Server
host kernel: Linux mainline v5.12-rc2

cmdline: ./kvm_page_table_test -m 4 -s anonymous -b 1G -v 80
           (80 vcpus, 1G memory, page mappings(normal 4K))
KVM_CREATE_MAPPINGS: before 104.35s -> after  90.42s  +13.35%
KVM_UPDATE_MAPPINGS: before  78.64s -> after  75.45s  + 4.06%

cmdline: ./kvm_page_table_test -m 4 -s anonymous_thp -b 20G -v 40
           (40 vcpus, 20G memory, block mappings(THP 2M))
KVM_CREATE_MAPPINGS: before  15.66s -> after   6.92s  +55.80%
KVM_UPDATE_MAPPINGS: before 178.80s -> after 123.35s  +31.00%
KVM_REBUILD_BLOCKS:  before 187.34s -> after 131.76s  +30.65%

cmdline: ./kvm_page_table_test -m 4 -s anonymous_hugetlb_1gb -b 20G -v 40
           (40 vcpus, 20G memory, block mappings(HUGETLB 1G))
KVM_CREATE_MAPPINGS: before 104.54s -> after   3.70s  +96.46%
KVM_UPDATE_MAPPINGS: before 174.20s -> after 115.94s  +33.44%
KVM_REBUILD_BLOCKS:  before 103.95s -> after   2.96s  +97.15%

Patch #2:
A new method to distinguish cases of memcache allocations is introduced.
By comparing fault_granule and vma_pagesize, cases that require allocations
from memcache and cases that don't can be distinguished completely.

Yanan Wang (2):
  KVM: arm64: Move CMOs from user_mem_abort to the fault handlers
  KVM: arm64: Distinguish cases of memcache allocations completely

 arch/arm64/include/asm/kvm_mmu.h | 31 ---------------
 arch/arm64/kvm/hyp/pgtable.c     | 68 +++++++++++++++++++++++++-------
 arch/arm64/kvm/mmu.c             | 48 ++++++++--------------
 3 files changed, 69 insertions(+), 78 deletions(-)
```
#### [PATCH 0/4] vfio: fix a couple of spelling mistakes detected by
##### From: Zhen Lei <thunder.leizhen@huawei.com>

```c
From patchwork Fri Mar 26 08:35:24 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Zhen Lei <thunder.leizhen@huawei.com>
X-Patchwork-Id: 12165991
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-11.8 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,
	SPF_PASS,USER_AGENT_GIT autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id EB3C4C433E5
	for <kvm@archiver.kernel.org>; Fri, 26 Mar 2021 08:37:57 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id D3F6D61477
	for <kvm@archiver.kernel.org>; Fri, 26 Mar 2021 08:37:57 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S230054AbhCZIhj (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Fri, 26 Mar 2021 04:37:39 -0400
Received: from szxga04-in.huawei.com ([45.249.212.190]:14614 "EHLO
        szxga04-in.huawei.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S230026AbhCZIhH (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 26 Mar 2021 04:37:07 -0400
Received: from DGGEMS413-HUB.china.huawei.com (unknown [172.30.72.60])
        by szxga04-in.huawei.com (SkyGuard) with ESMTP id 4F6Fdy0HxGz19JkV;
        Fri, 26 Mar 2021 16:35:02 +0800 (CST)
Received: from thunder-town.china.huawei.com (10.174.179.202) by
 DGGEMS413-HUB.china.huawei.com (10.3.19.213) with Microsoft SMTP Server id
 14.3.498.0; Fri, 26 Mar 2021 16:36:52 +0800
From: Zhen Lei <thunder.leizhen@huawei.com>
To: Alex Williamson <alex.williamson@redhat.com>,
        Cornelia Huck <cohuck@redhat.com>, kvm <kvm@vger.kernel.org>,
        Kirti Wankhede <kwankhede@nvidia.com>,
        Eric Auger <eric.auger@redhat.com>,
        linux-kernel <linux-kernel@vger.kernel.org>
CC: Zhen Lei <thunder.leizhen@huawei.com>
Subject: [PATCH 0/4] vfio: fix a couple of spelling mistakes detected by
 codespell tool
Date: Fri, 26 Mar 2021 16:35:24 +0800
Message-ID: <20210326083528.1329-1-thunder.leizhen@huawei.com>
X-Mailer: git-send-email 2.26.0.windows.1
MIME-Version: 1.0
X-Originating-IP: [10.174.179.202]
X-CFilter-Loop: Reflected
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This detection and correction covers the entire driver/vfio directory.

Zhen Lei (4):
  vfio/type1: fix a couple of spelling mistakes
  vfio/mdev: Fix spelling mistake "interal" -> "internal"
  vfio/pci: fix a couple of spelling mistakes
  vfio/platform: Fix spelling mistake "registe" -> "register"

 drivers/vfio/mdev/mdev_private.h                         | 2 +-
 drivers/vfio/pci/vfio_pci.c                              | 2 +-
 drivers/vfio/pci/vfio_pci_config.c                       | 2 +-
 drivers/vfio/pci/vfio_pci_nvlink2.c                      | 4 ++--
 drivers/vfio/platform/reset/vfio_platform_calxedaxgmac.c | 2 +-
 drivers/vfio/vfio_iommu_type1.c                          | 6 +++---
 6 files changed, 9 insertions(+), 9 deletions(-)
```
#### [PATCH 0/2] KVM: x86: hyper-v: Fix TSC page update after
##### From: Vitaly Kuznetsov <vkuznets@redhat.com>

```c
From patchwork Fri Mar 26 15:55:49 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Vitaly Kuznetsov <vkuznets@redhat.com>
X-Patchwork-Id: 12167055
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-11.0 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS autolearn=ham
	autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 8BB7DC433C1
	for <kvm@archiver.kernel.org>; Fri, 26 Mar 2021 15:57:29 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 56F5261A27
	for <kvm@archiver.kernel.org>; Fri, 26 Mar 2021 15:57:29 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S230114AbhCZP46 (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Fri, 26 Mar 2021 11:56:58 -0400
Received: from us-smtp-delivery-124.mimecast.com ([216.205.24.124]:53945 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S230236AbhCZP4Z (ORCPT
        <rfc822;kvm@vger.kernel.org>); Fri, 26 Mar 2021 11:56:25 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1616774184;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=jbG3A7L/3cWDWl80JmYOD1dysLKY5LW4YSuKOo3eZi0=;
        b=gRi1Z+obTu/lH8z65/PJBI+mftvjJYnPmzBblebAvyAXH32m2uyaWAIb7ivNqNx2vhKEIU
        eqqUa7q3SWoRbt0mS36KzWMSeF+DtMRIjQsoveIfCiwEjfaOwmxmAWpUQ0NmEYEQfi4Y6t
        egWF9R5EQ8glxFeZHfYhL6Cj0TmxIj4=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-129-mpzjHbavOoyYlUtopG2l6A-1; Fri, 26 Mar 2021 11:56:10 -0400
X-MC-Unique: mpzjHbavOoyYlUtopG2l6A-1
Received: from smtp.corp.redhat.com (int-mx04.intmail.prod.int.phx2.redhat.com
 [10.5.11.14])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id B265B100E43D;
        Fri, 26 Mar 2021 15:56:01 +0000 (UTC)
Received: from vitty.brq.redhat.com (unknown [10.40.195.148])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 490F45DEAD;
        Fri, 26 Mar 2021 15:55:53 +0000 (UTC)
From: Vitaly Kuznetsov <vkuznets@redhat.com>
To: kvm@vger.kernel.org, Paolo Bonzini <pbonzini@redhat.com>
Cc: Sean Christopherson <seanjc@google.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Marcelo Tosatti <mtosatti@redhat.com>
Subject: [PATCH 0/2] KVM: x86: hyper-v: Fix TSC page update after
 KVM_SET_CLOCK(0) call
Date: Fri, 26 Mar 2021 16:55:49 +0100
Message-Id: <20210326155551.17446-1-vkuznets@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.14
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

I discovered that after KVM_SET_CLOCK(0) TSC page value in the guest can
go through the roof and apparently we have a signedness issue when the
update is performed. Fix the issue and add a selftest.

Vitaly Kuznetsov (2):
  KVM: x86: hyper-v: Forbid unsigned hv_clock->system_time to go
    negative after KVM_REQ_CLOCK_UPDATE
  selftests: kvm: Check that TSC page value is small after
    KVM_SET_CLOCK(0)

 arch/x86/kvm/x86.c                                | 10 +++++++++-
 tools/testing/selftests/kvm/x86_64/hyperv_clock.c | 13 +++++++++++--
 2 files changed, 20 insertions(+), 3 deletions(-)
```
