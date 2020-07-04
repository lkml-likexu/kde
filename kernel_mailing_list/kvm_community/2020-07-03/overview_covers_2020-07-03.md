

#### [PATCH v3 00/21] KVM: Cleanup and unify kvm_mmu_memory_cache usage
##### From: Sean Christopherson <sean.j.christopherson@intel.com>

```c
From patchwork Fri Jul  3 02:35:24 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Sean Christopherson <sean.j.christopherson@intel.com>
X-Patchwork-Id: 11640579
Return-Path: <SRS0=xch8=AO=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id F2DD813BD
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  3 Jul 2020 02:36:09 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id D38A3215A4
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  3 Jul 2020 02:36:09 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726147AbgGCCgG (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 2 Jul 2020 22:36:06 -0400
Received: from mga11.intel.com ([192.55.52.93]:52027 "EHLO mga11.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1725915AbgGCCgF (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 2 Jul 2020 22:36:05 -0400
IronPort-SDR: 
 T9V2w7ZbFRO40T3LLRpSOHxsZuBJ58XiXiy9R/Yl6xwsikJaW6bqJHuy6lKFwshGaAghMr9UW0
 mXu/VoZHx3Iw==
X-IronPort-AV: E=McAfee;i="6000,8403,9670"; a="145213957"
X-IronPort-AV: E=Sophos;i="5.75,306,1589266800";
   d="scan'208";a="145213957"
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from orsmga003.jf.intel.com ([10.7.209.27])
  by fmsmga102.fm.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 02 Jul 2020 19:36:04 -0700
IronPort-SDR: 
 T2DxoJ+6pDgQH7e5SIxXyTgQ9QkegMOBSCNjFHu7YUc0H8gIQqRN5KQHpGrfYlDlqtc8ESDZ15
 OICltGe0pc2w==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.75,306,1589266800";
   d="scan'208";a="278295716"
Received: from sjchrist-coffee.jf.intel.com ([10.54.74.152])
  by orsmga003.jf.intel.com with ESMTP; 02 Jul 2020 19:36:04 -0700
From: Sean Christopherson <sean.j.christopherson@intel.com>
To: Marc Zyngier <maz@kernel.org>, Paolo Bonzini <pbonzini@redhat.com>,
        Arnd Bergmann <arnd@arndb.de>
Cc: James Morse <james.morse@arm.com>,
        Julien Thierry <julien.thierry.kdev@gmail.com>,
        Suzuki K Poulose <suzuki.poulose@arm.com>,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>,
        linux-arm-kernel@lists.infradead.org, kvmarm@lists.cs.columbia.edu,
        linux-mips@vger.kernel.org, kvm@vger.kernel.org,
        linux-arch@vger.kernel.org, linux-kernel@vger.kernel.org,
        Ben Gardon <bgardon@google.com>,
        Peter Feiner <pfeiner@google.com>,
        Peter Shier <pshier@google.com>,
        Junaid Shahid <junaids@google.com>,
        Christoffer Dall <christoffer.dall@arm.com>
Subject: [PATCH v3 00/21] KVM: Cleanup and unify kvm_mmu_memory_cache usage
Date: Thu,  2 Jul 2020 19:35:24 -0700
Message-Id: <20200703023545.8771-1-sean.j.christopherson@intel.com>
X-Mailer: git-send-email 2.26.0
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The only interesting delta from v2 is that patch 18 is updated to handle
a conflict with arm64's p4d rework.  Resolution was straightforward
(famous last words).


This series resurrects Christoffer Dall's series[1] to provide a common
MMU memory cache implementation that can be shared by x86, arm64 and MIPS.

It also picks up a suggested change from Ben Gardon[2] to clear shadow
page tables during initial allocation so as to avoid clearing entire
pages while holding mmu_lock.

The front half of the patches do house cleaning on x86's memory cache
implementation in preparation for moving it to common code, along with a
fair bit of cleanup on the usage.  The middle chunk moves the patches to
common KVM, and the last two chunks convert arm64 and MIPS to the common
implementation.

Fully tested on x86 only.  Compile tested patches 14-21 on arm64, MIPS,
s390 and PowerPC.

v3:
  - Rebased to kvm/queue, commit a037ff353ba6 ("Merge ... into HEAD")
  - Collect more review tags. [Ben]

v2:
  - Rebase to kvm-5.8-2, commit 49b3deaad345 ("Merge tag ...").
  - Use an asm-generic kvm_types.h for s390 and PowerPC instead of an
    empty arch-specific file. [Marc]
  - Explicit document "GFP_PGTABLE_USER == GFP_KERNEL_ACCOUNT | GFP_ZERO"
    in the arm64 conversion patch. [Marc]
  - Collect review tags. [Ben]

Sean Christopherson (21):
  KVM: x86/mmu: Track the associated kmem_cache in the MMU caches
  KVM: x86/mmu: Consolidate "page" variant of memory cache helpers
  KVM: x86/mmu: Use consistent "mc" name for kvm_mmu_memory_cache locals
  KVM: x86/mmu: Remove superfluous gotos from mmu_topup_memory_caches()
  KVM: x86/mmu: Try to avoid crashing KVM if a MMU memory cache is empty
  KVM: x86/mmu: Move fast_page_fault() call above
    mmu_topup_memory_caches()
  KVM: x86/mmu: Topup memory caches after walking GVA->GPA
  KVM: x86/mmu: Clean up the gorilla math in mmu_topup_memory_caches()
  KVM: x86/mmu: Separate the memory caches for shadow pages and gfn
    arrays
  KVM: x86/mmu: Make __GFP_ZERO a property of the memory cache
  KVM: x86/mmu: Zero allocate shadow pages (outside of mmu_lock)
  KVM: x86/mmu: Skip filling the gfn cache for guaranteed direct MMU
    topups
  KVM: x86/mmu: Prepend "kvm_" to memory cache helpers that will be
    global
  KVM: Move x86's version of struct kvm_mmu_memory_cache to common code
  KVM: Move x86's MMU memory cache helpers to common KVM code
  KVM: arm64: Drop @max param from mmu_topup_memory_cache()
  KVM: arm64: Use common code's approach for __GFP_ZERO with memory
    caches
  KVM: arm64: Use common KVM implementation of MMU memory caches
  KVM: MIPS: Drop @max param from mmu_topup_memory_cache()
  KVM: MIPS: Account pages used for GPA page tables
  KVM: MIPS: Use common KVM implementation of MMU memory caches

 arch/arm64/include/asm/kvm_host.h  |  11 ---
 arch/arm64/include/asm/kvm_types.h |   8 ++
 arch/arm64/kvm/arm.c               |   2 +
 arch/arm64/kvm/mmu.c               |  56 +++----------
 arch/mips/include/asm/kvm_host.h   |  11 ---
 arch/mips/include/asm/kvm_types.h  |   7 ++
 arch/mips/kvm/mmu.c                |  44 ++--------
 arch/powerpc/include/asm/Kbuild    |   1 +
 arch/s390/include/asm/Kbuild       |   1 +
 arch/x86/include/asm/kvm_host.h    |  14 +---
 arch/x86/include/asm/kvm_types.h   |   7 ++
 arch/x86/kvm/mmu/mmu.c             | 129 +++++++++--------------------
 arch/x86/kvm/mmu/paging_tmpl.h     |  10 +--
 include/asm-generic/kvm_types.h    |   5 ++
 include/linux/kvm_host.h           |   7 ++
 include/linux/kvm_types.h          |  19 +++++
 virt/kvm/kvm_main.c                |  55 ++++++++++++
 17 files changed, 176 insertions(+), 211 deletions(-)
 create mode 100644 arch/arm64/include/asm/kvm_types.h
 create mode 100644 arch/mips/include/asm/kvm_types.h
 create mode 100644 arch/x86/include/asm/kvm_types.h
 create mode 100644 include/asm-generic/kvm_types.h
```
#### [PATCH 0/2] KVM: VMX: CR0/CR4 guest/host masks cleanup
##### From: Sean Christopherson <sean.j.christopherson@intel.com>

```c
From patchwork Fri Jul  3 04:04:20 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Sean Christopherson <sean.j.christopherson@intel.com>
X-Patchwork-Id: 11640789
Return-Path: <SRS0=xch8=AO=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 95232913
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  3 Jul 2020 04:04:39 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 87975208DB
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  3 Jul 2020 04:04:39 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726107AbgGCEEY (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 3 Jul 2020 00:04:24 -0400
Received: from mga06.intel.com ([134.134.136.31]:9178 "EHLO mga06.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1725949AbgGCEEY (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 3 Jul 2020 00:04:24 -0400
IronPort-SDR: 
 T0PMF1y7rpgIPB8g5nCfQQhdUGvPovYA8IFm4OjJcqbZISUENd8Zf2lypln2etoSyTDAJgUjs9
 HaOXllDbLKmw==
X-IronPort-AV: E=McAfee;i="6000,8403,9670"; a="208604063"
X-IronPort-AV: E=Sophos;i="5.75,306,1589266800";
   d="scan'208";a="208604063"
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from fmsmga001.fm.intel.com ([10.253.24.23])
  by orsmga104.jf.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 02 Jul 2020 21:04:23 -0700
IronPort-SDR: 
 fnx8n/5dfBVrfbLT24PWc42gDpm6Xk9Uw46kztNqKbJ6gFnmskAg2zxmCEqSASO0pUJAv/fmSi
 Wbsn0b/sJxpQ==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.75,306,1589266800";
   d="scan'208";a="387520208"
Received: from sjchrist-coffee.jf.intel.com ([10.54.74.152])
  by fmsmga001.fm.intel.com with ESMTP; 02 Jul 2020 21:04:22 -0700
From: Sean Christopherson <sean.j.christopherson@intel.com>
To: Paolo Bonzini <pbonzini@redhat.com>
Cc: Sean Christopherson <sean.j.christopherson@intel.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org
Subject: [PATCH 0/2] KVM: VMX: CR0/CR4 guest/host masks cleanup
Date: Thu,  2 Jul 2020 21:04:20 -0700
Message-Id: <20200703040422.31536-1-sean.j.christopherson@intel.com>
X-Mailer: git-send-email 2.26.0
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Fix a bug where CR4.TSD isn't correctly marked as being possibly owned by
the guest in the common x86 macro, then clean up the mess that made the
bug possible by throwing away VMX's mix of duplicate code and open coded
tweaks.  The lack of a define for the guest-owned CR0 bit has bugged me
for a long time, but adding another define always seemed ridiculous.

Sean Christopherson (2):
  KVM: x86: Mark CR4.TSD as being possibly owned by the guest
  KVM: VMX: Use KVM_POSSIBLE_CR*_GUEST_BITS to initialize guest/host
    masks

 arch/x86/kvm/kvm_cache_regs.h |  2 +-
 arch/x86/kvm/vmx/nested.c     |  4 ++--
 arch/x86/kvm/vmx/vmx.c        | 13 +++++--------
 3 files changed, 8 insertions(+), 11 deletions(-)
```
#### [kvm-unit-tests PATCH v1 0/4] More lib/alloc cleanup and a minor
##### From: Claudio Imbrenda <imbrenda@linux.ibm.com>

```c
From patchwork Fri Jul  3 11:51:05 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Claudio Imbrenda <imbrenda@linux.ibm.com>
X-Patchwork-Id: 11641749
Return-Path: <SRS0=xch8=AO=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 394A060D
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  3 Jul 2020 11:51:18 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 2B050206B6
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  3 Jul 2020 11:51:18 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726053AbgGCLvR (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 3 Jul 2020 07:51:17 -0400
Received: from mx0b-001b2d01.pphosted.com ([148.163.158.5]:27764 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S1725984AbgGCLvQ (ORCPT
        <rfc822;kvm@vger.kernel.org>); Fri, 3 Jul 2020 07:51:16 -0400
Received: from pps.filterd (m0098416.ppops.net [127.0.0.1])
        by mx0b-001b2d01.pphosted.com (8.16.0.42/8.16.0.42) with SMTP id
 063BWWTi182634
        for <kvm@vger.kernel.org>; Fri, 3 Jul 2020 07:51:15 -0400
Received: from pps.reinject (localhost [127.0.0.1])
        by mx0b-001b2d01.pphosted.com with ESMTP id 320t3heu0q-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT)
        for <kvm@vger.kernel.org>; Fri, 03 Jul 2020 07:51:15 -0400
Received: from m0098416.ppops.net (m0098416.ppops.net [127.0.0.1])
        by pps.reinject (8.16.0.36/8.16.0.36) with SMTP id 063BXBus184683
        for <kvm@vger.kernel.org>; Fri, 3 Jul 2020 07:51:15 -0400
Received: from ppma04ams.nl.ibm.com (63.31.33a9.ip4.static.sl-reverse.com
 [169.51.49.99])
        by mx0b-001b2d01.pphosted.com with ESMTP id 320t3heu07-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Fri, 03 Jul 2020 07:51:15 -0400
Received: from pps.filterd (ppma04ams.nl.ibm.com [127.0.0.1])
        by ppma04ams.nl.ibm.com (8.16.0.42/8.16.0.42) with SMTP id
 063BoJoF030209;
        Fri, 3 Jul 2020 11:51:13 GMT
Received: from b06cxnps3075.portsmouth.uk.ibm.com
 (d06relay10.portsmouth.uk.ibm.com [9.149.109.195])
        by ppma04ams.nl.ibm.com with ESMTP id 31wwr8f8d4-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Fri, 03 Jul 2020 11:51:13 +0000
Received: from d06av25.portsmouth.uk.ibm.com (d06av25.portsmouth.uk.ibm.com
 [9.149.105.61])
        by b06cxnps3075.portsmouth.uk.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id 063BpB7P54919382
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Fri, 3 Jul 2020 11:51:11 GMT
Received: from d06av25.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 2567411C04C;
        Fri,  3 Jul 2020 11:51:11 +0000 (GMT)
Received: from d06av25.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 7A4D511C04A;
        Fri,  3 Jul 2020 11:51:10 +0000 (GMT)
Received: from ibm-vm.ibmuc.com (unknown [9.145.9.164])
        by d06av25.portsmouth.uk.ibm.com (Postfix) with ESMTP;
        Fri,  3 Jul 2020 11:51:10 +0000 (GMT)
From: Claudio Imbrenda <imbrenda@linux.ibm.com>
To: kvm@vger.kernel.org, pbonzini@redhat.com
Cc: frankja@linux.ibm.com, thuth@redhat.com, david@redhat.com
Subject: [kvm-unit-tests PATCH v1 0/4] More lib/alloc cleanup and a minor
 improvement
Date: Fri,  3 Jul 2020 13:51:05 +0200
Message-Id: <20200703115109.39139-1-imbrenda@linux.ibm.com>
X-Mailer: git-send-email 2.26.2
MIME-Version: 1.0
X-TM-AS-GCONF: 00
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.235,18.0.687
 definitions=2020-07-03_06:2020-07-02,2020-07-03 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 lowpriorityscore=0
 malwarescore=0 impostorscore=0 mlxlogscore=964 bulkscore=0
 cotscore=-2147483648 adultscore=0 phishscore=0 clxscore=1015 mlxscore=0
 priorityscore=1501 spamscore=0 suspectscore=0 classifier=spam adjust=0
 reason=mlx scancount=1 engine=8.12.0-2004280000
 definitions=main-2007030078
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Some more cleanup of lib/alloc in light of upcoming changes

The first real feature: allow aligned virtual allocations with
alignment greater than one page.

Also export a function for allocating aligned non-backed virtual pages.

Claudio Imbrenda (4):
  lib/vmalloc: fix pages count local variable to be size_t
  lib/alloc_page: change some parameter types
  lib/alloc_page: move get_order and is_power_of_2 to a bitops.h
  lib/vmalloc: allow vm_memalign with alignment > PAGE_SIZE

 lib/alloc_page.h |  7 +++----
 lib/bitops.h     | 10 ++++++++++
 lib/libcflat.h   |  5 -----
 lib/vmalloc.h    |  3 +++
 lib/alloc.c      |  1 +
 lib/alloc_page.c | 13 ++++---------
 lib/vmalloc.c    | 42 +++++++++++++++++++++++++++++++++---------
 7 files changed, 54 insertions(+), 27 deletions(-)
Reviewed-by: Andrew Jones <drjones@redhat.com>
```
#### [PATCH 0/2] Documentation: virt: eliminate duplicated words
##### From: Randy Dunlap <rdunlap@infradead.org>

```c
From patchwork Fri Jul  3 21:29:04 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Randy Dunlap <rdunlap@infradead.org>
X-Patchwork-Id: 11642879
Return-Path: <SRS0=xch8=AO=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 6EF2F739
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  3 Jul 2020 21:29:18 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 53141208C7
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  3 Jul 2020 21:29:18 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=fail reason="signature verification failed" (2048-bit key)
 header.d=infradead.org header.i=@infradead.org header.b="nUmxfeQV"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726753AbgGCV3P (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 3 Jul 2020 17:29:15 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:51080 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726379AbgGCV3O (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 3 Jul 2020 17:29:14 -0400
Received: from merlin.infradead.org (merlin.infradead.org
 [IPv6:2001:8b0:10b:1231::1])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 7B8AFC061794;
        Fri,  3 Jul 2020 14:29:14 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; q=dns/txt; c=relaxed/relaxed;
        d=infradead.org; s=merlin.20170209;
 h=Content-Transfer-Encoding:MIME-Version:
        Message-Id:Date:Subject:Cc:To:From:Sender:Reply-To:Content-Type:Content-ID:
        Content-Description:In-Reply-To:References;
        bh=/7u1y2wkt8wxlyjfpGZrdn4AtvrSo84WKKJqoNgDn0k=;
 b=nUmxfeQV5k3Ubscn93XikvnOBc
        KLizXX2WRDer+wtVaxKXvUcXH7SWHQpWXK+M/L2aCbUpw/BeqWW6gd6XhXmKqJgJJX8hh1/75ls3J
        oGmrkgZJC/kSI1zxbY+IicVDxqAkANF7VXjGecUXKt6vs2Al3gZdcpluGHK7ZwCnLZ0fQpXm8jXbd
        lo2gFJHbFmrZ1nyt4QEmG4yRqFwf3gSFEhQbyBc8QxESVzCwUN5FFk3cP1ErtNBgtLvFRZvw1FuM/
        zko/+epNLWqqwM95pqzgbWQEEGBme1HwfXJ6nWhC9vqQu1DpyQRhjThI+3phyTBCuKZ0xdZXo2N0K
        rxjXjYtg==;
Received: from [2601:1c0:6280:3f0::19c2] (helo=smtpauth.infradead.org)
        by merlin.infradead.org with esmtpsa (Exim 4.92.3 #3 (Red Hat Linux))
        id 1jrTF9-0006KB-M3; Fri, 03 Jul 2020 21:29:12 +0000
From: Randy Dunlap <rdunlap@infradead.org>
To: linux-kernel@vger.kernel.org
Cc: Randy Dunlap <rdunlap@infradead.org>,
        Jonathan Corbet <corbet@lwn.net>, linux-doc@vger.kernel.org,
        Paolo Bonzini <pbonzini@redhat.com>, kvm@vger.kernel.org
Subject: [PATCH 0/2] Documentation: virt: eliminate duplicated words
Date: Fri,  3 Jul 2020 14:29:04 -0700
Message-Id: <20200703212906.30655-1-rdunlap@infradead.org>
X-Mailer: git-send-email 2.26.2
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Drop doubled words in Documentation/virt/kvm/.


Cc: Jonathan Corbet <corbet@lwn.net>
Cc: linux-doc@vger.kernel.org
Cc: Paolo Bonzini <pbonzini@redhat.com>
Cc: kvm@vger.kernel.org


 Documentation/virt/kvm/api.rst     |   16 ++++++++--------
 Documentation/virt/kvm/s390-pv.rst |    2 +-
 2 files changed, 9 insertions(+), 9 deletions(-)
```
