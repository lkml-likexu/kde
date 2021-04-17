

#### [PATCH V3 0/3] vDPA/ifcvf: enables Intel C5000X-PL virtio-blk
##### From: Zhu Lingshan <lingshan.zhu@intel.com>

```c
From patchwork Fri Apr 16 07:16:25 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Zhu Lingshan <lingshan.zhu@intel.com>
X-Patchwork-Id: 12206801
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-11.8 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,
	SPF_PASS,USER_AGENT_GIT autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 1FE09C433B4
	for <kvm@archiver.kernel.org>; Fri, 16 Apr 2021 07:21:55 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id ED0A160238
	for <kvm@archiver.kernel.org>; Fri, 16 Apr 2021 07:21:54 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S239173AbhDPHWR (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Fri, 16 Apr 2021 03:22:17 -0400
Received: from mga14.intel.com ([192.55.52.115]:57485 "EHLO mga14.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S230466AbhDPHWQ (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 16 Apr 2021 03:22:16 -0400
IronPort-SDR: 
 z8daStGJ5qd75FSECTrJ5DEvNL1OKS+4gOP7WIpNJnkCTRISQSoQl/xFXIRVAJCwCN/B2lmsrg
 7x9oXwCecx6Q==
X-IronPort-AV: E=McAfee;i="6200,9189,9955"; a="194561047"
X-IronPort-AV: E=Sophos;i="5.82,226,1613462400";
   d="scan'208";a="194561047"
Received: from orsmga008.jf.intel.com ([10.7.209.65])
  by fmsmga103.fm.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 16 Apr 2021 00:21:51 -0700
IronPort-SDR: 
 H/KIcLRhf1m9Jvw4nc0FVMfzl2cgmwTDssmiA06Z1OvItZvPn5AgtrNaqhXxuHQHud5MN976Hg
 vL4++NAAmT1Q==
X-IronPort-AV: E=Sophos;i="5.82,226,1613462400";
   d="scan'208";a="425489727"
Received: from unknown (HELO localhost.localdomain.bj.intel.com)
 ([10.240.193.73])
  by orsmga008-auth.jf.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 16 Apr 2021 00:21:46 -0700
From: Zhu Lingshan <lingshan.zhu@intel.com>
To: jasowang@redhat.com, mst@redhat.com, lulu@redhat.com,
        sgarzare@redhat.com
Cc: virtualization@lists.linux-foundation.org, netdev@vger.kernel.org,
        kvm@vger.kernel.org, linux-kernel@vger.kernel.org,
        Zhu Lingshan <lingshan.zhu@intel.com>
Subject: [PATCH V3 0/3] vDPA/ifcvf: enables Intel C5000X-PL virtio-blk
Date: Fri, 16 Apr 2021 15:16:25 +0800
Message-Id: <20210416071628.4984-1-lingshan.zhu@intel.com>
X-Mailer: git-send-email 2.27.0
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This series enabled Intel FGPA SmartNIC C5000X-PL virtio-blk for vDPA.

This series requires:
Stefano's vdpa block patchset: https://lkml.org/lkml/2021/3/15/2113
my patchset to enable Intel FGPA SmartNIC C5000X-PL virtio-net for vDPA:
https://lkml.org/lkml/2021/3/17/432

changes from V2:
both get_features() and get_config_size() use switch code block
now(Stefano)

changes from V1:
(1)add comments to explain this driver drives virtio modern devices
and transitional devices in modern mode.(Jason)
(2)remove IFCVF_BLK_SUPPORTED_FEATURES, use hardware feature bits
directly(Jason)
(3)add error handling and message in get_config_size(Stefano)

Thanks!


Zhu Lingshan (3):
  vDPA/ifcvf: deduce VIRTIO device ID when probe
  vDPA/ifcvf: enable Intel C5000X-PL virtio-block for vDPA
  vDPA/ifcvf: get_config_size should return dev specific config size

 drivers/vdpa/ifcvf/ifcvf_base.h |  9 ++++-
 drivers/vdpa/ifcvf/ifcvf_main.c | 68 ++++++++++++++++++++++++++-------
 2 files changed, 62 insertions(+), 15 deletions(-)
```
#### [RFC PATCH v2 0/2] KVM: x86: Enable dirty logging lazily for huge
##### From: Keqian Zhu <zhukeqian1@huawei.com>

```c
From patchwork Fri Apr 16 08:25:09 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Keqian Zhu <zhukeqian1@huawei.com>
X-Patchwork-Id: 12206917
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-11.8 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,
	SPF_PASS,USER_AGENT_GIT autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 76668C433ED
	for <kvm@archiver.kernel.org>; Fri, 16 Apr 2021 08:25:25 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 5988761166
	for <kvm@archiver.kernel.org>; Fri, 16 Apr 2021 08:25:25 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S236787AbhDPIZs (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Fri, 16 Apr 2021 04:25:48 -0400
Received: from szxga06-in.huawei.com ([45.249.212.32]:17364 "EHLO
        szxga06-in.huawei.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S232022AbhDPIZr (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 16 Apr 2021 04:25:47 -0400
Received: from DGGEMS412-HUB.china.huawei.com (unknown [172.30.72.58])
        by szxga06-in.huawei.com (SkyGuard) with ESMTP id 4FM8Nv077CzlYCq;
        Fri, 16 Apr 2021 16:23:27 +0800 (CST)
Received: from DESKTOP-5IS4806.china.huawei.com (10.174.187.224) by
 DGGEMS412-HUB.china.huawei.com (10.3.19.212) with Microsoft SMTP Server id
 14.3.498.0; Fri, 16 Apr 2021 16:25:13 +0800
From: Keqian Zhu <zhukeqian1@huawei.com>
To: <linux-kernel@vger.kernel.org>, <kvm@vger.kernel.org>,
        Paolo Bonzini <pbonzini@redhat.com>,
        Sean Christopherson <seanjc@google.com>,
        Ben Gardon <bgardon@google.com>
CC: <wanghaibin.wang@huawei.com>
Subject: [RFC PATCH v2 0/2] KVM: x86: Enable dirty logging lazily for huge
 pages
Date: Fri, 16 Apr 2021 16:25:09 +0800
Message-ID: <20210416082511.2856-1-zhukeqian1@huawei.com>
X-Mailer: git-send-email 2.8.4.windows.1
MIME-Version: 1.0
X-Originating-IP: [10.174.187.224]
X-CFilter-Loop: Reflected
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Currently during start dirty logging, if we're with init-all-set,
we write protect huge pages and leave normal pages untouched, for
that we can enable dirty logging for these pages lazily.

Actually enable dirty logging lazily for huge pages is feasible
too, which not only reduces the time of start dirty logging, also
greatly reduces side-effect on guest when there is high dirty rate.

Thanks,
Keqian

Keqian Zhu (2):
  KVM: x86: Support write protect gfn with min_level
  KVM: x86: Not wr-protect huge page with init_all_set dirty log

 arch/x86/kvm/mmu/mmu.c          | 57 ++++++++++++++++++++++++++++-----
 arch/x86/kvm/mmu/mmu_internal.h |  3 +-
 arch/x86/kvm/mmu/page_track.c   |  2 +-
 arch/x86/kvm/mmu/tdp_mmu.c      | 16 ++++++---
 arch/x86/kvm/mmu/tdp_mmu.h      |  3 +-
 arch/x86/kvm/x86.c              | 37 ++++++---------------
 6 files changed, 76 insertions(+), 42 deletions(-)
```
#### [RFCv2 00/13] TDX and guest memory unmapping
##### From: "Kirill A. Shutemov" <kirill.shutemov@linux.intel.com>

```c
From patchwork Fri Apr 16 15:40:53 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: "Kirill A. Shutemov" <kirill.shutemov@linux.intel.com>
X-Patchwork-Id: 12207989
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.8 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_PATCH,MAILING_LIST_MULTI,
	MENTIONS_GIT_HOSTING,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT autolearn=ham
	autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id A434AC433B4
	for <kvm@archiver.kernel.org>; Fri, 16 Apr 2021 15:41:38 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 88119613B4
	for <kvm@archiver.kernel.org>; Fri, 16 Apr 2021 15:41:38 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S243493AbhDPPmC (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Fri, 16 Apr 2021 11:42:02 -0400
Received: from mga12.intel.com ([192.55.52.136]:63662 "EHLO mga12.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S235514AbhDPPmB (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 16 Apr 2021 11:42:01 -0400
IronPort-SDR: 
 qByucoM14H8DwyAFPGwMzh0MQkeoZi9DFopOlw9770N02taZSywMRoMGAmGr/eAfCv3+bicOfI
 Tnf4mo1kSRmw==
X-IronPort-AV: E=McAfee;i="6200,9189,9956"; a="174550435"
X-IronPort-AV: E=Sophos;i="5.82,226,1613462400";
   d="scan'208";a="174550435"
Received: from fmsmga002.fm.intel.com ([10.253.24.26])
  by fmsmga106.fm.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 16 Apr 2021 08:41:36 -0700
IronPort-SDR: 
 JHSnJpXle56RA6NOpktcidrINTGGvy+pVP+IY3njKrzX6L3ewV0BhUmmbMqeo9bSv6+cmm05xB
 WB9eJa8RjXkg==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.82,226,1613462400";
   d="scan'208";a="453378435"
Received: from black.fi.intel.com ([10.237.72.28])
  by fmsmga002.fm.intel.com with ESMTP; 16 Apr 2021 08:41:32 -0700
Received: by black.fi.intel.com (Postfix, from userid 1000)
        id C158A12A; Fri, 16 Apr 2021 18:41:49 +0300 (EEST)
From: "Kirill A. Shutemov" <kirill.shutemov@linux.intel.com>
To: Dave Hansen <dave.hansen@linux.intel.com>,
        Andy Lutomirski <luto@kernel.org>,
        Peter Zijlstra <peterz@infradead.org>,
        Sean Christopherson <seanjc@google.com>,
        Jim Mattson <jmattson@google.com>
Cc: David Rientjes <rientjes@google.com>,
        "Edgecombe, Rick P" <rick.p.edgecombe@intel.com>,
        "Kleen, Andi" <andi.kleen@intel.com>,
        "Yamahata, Isaku" <isaku.yamahata@intel.com>,
        Erdem Aktas <erdemaktas@google.com>,
        Steve Rutherford <srutherford@google.com>,
        Peter Gonda <pgonda@google.com>,
        David Hildenbrand <david@redhat.com>, x86@kernel.org,
        kvm@vger.kernel.org, linux-mm@kvack.org,
        linux-kernel@vger.kernel.org,
        "Kirill A. Shutemov" <kirill.shutemov@linux.intel.com>
Subject: [RFCv2 00/13] TDX and guest memory unmapping
Date: Fri, 16 Apr 2021 18:40:53 +0300
Message-Id: <20210416154106.23721-1-kirill.shutemov@linux.intel.com>
X-Mailer: git-send-email 2.30.2
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

TDX integrity check failures may lead to system shutdown host kernel must
not allow any writes to TD-private memory. This requirment clashes with
KVM design: KVM expects the guest memory to be mapped into host userspace
(e.g. QEMU).

This patchset aims to start discussion on how we can approach the issue.

The core of the change is in the last patch. Please see more detailed
description of the issue and proposoal of the solution there.

TODO:
  - THP support
  - Clarify semantics wrt. page cache

v2:
  - Unpoison page on free
  - Authorize access to the page: only the KVM that poisoned the page
    allows to touch it
  - FOLL_ALLOW_POISONED is implemented

The patchset can also be found here:

git://git.kernel.org/pub/scm/linux/kernel/git/kas/linux.git kvm-unmapped-poison

Kirill A. Shutemov (13):
  x86/mm: Move force_dma_unencrypted() to common code
  x86/kvm: Introduce KVM memory protection feature
  x86/kvm: Make DMA pages shared
  x86/kvm: Use bounce buffers for KVM memory protection
  x86/kvmclock: Share hvclock memory with the host
  x86/realmode: Share trampoline area if KVM memory protection enabled
  mm: Add hwpoison_entry_to_pfn() and hwpoison_entry_to_page()
  mm/gup: Add FOLL_ALLOW_POISONED
  shmem: Fail shmem_getpage_gfp() on poisoned pages
  mm: Keep page reference for hwpoison entries
  mm: Replace hwpoison entry with present PTE if page got unpoisoned
  KVM: passdown struct kvm to hva_to_pfn_slow()
  KVM: unmap guest memory using poisoned pages

 arch/powerpc/kvm/book3s_64_mmu_hv.c    |   2 +-
 arch/powerpc/kvm/book3s_64_mmu_radix.c |   2 +-
 arch/x86/Kconfig                       |   9 +-
 arch/x86/include/asm/cpufeatures.h     |   1 +
 arch/x86/include/asm/io.h              |   4 +-
 arch/x86/include/asm/kvm_para.h        |   5 +
 arch/x86/include/asm/mem_encrypt.h     |   7 +-
 arch/x86/include/uapi/asm/kvm_para.h   |   3 +-
 arch/x86/kernel/kvm.c                  |  19 +++
 arch/x86/kernel/kvmclock.c             |   2 +-
 arch/x86/kernel/pci-swiotlb.c          |   3 +-
 arch/x86/kvm/Kconfig                   |   1 +
 arch/x86/kvm/cpuid.c                   |   3 +-
 arch/x86/kvm/mmu/mmu.c                 |  20 ++-
 arch/x86/kvm/mmu/paging_tmpl.h         |  10 +-
 arch/x86/kvm/x86.c                     |   6 +
 arch/x86/mm/Makefile                   |   2 +
 arch/x86/mm/mem_encrypt.c              |  74 ---------
 arch/x86/mm/mem_encrypt_common.c       |  87 ++++++++++
 arch/x86/mm/pat/set_memory.c           |  10 ++
 arch/x86/realmode/init.c               |   7 +-
 include/linux/kvm_host.h               |  31 +++-
 include/linux/mm.h                     |   1 +
 include/linux/swapops.h                |  20 +++
 include/uapi/linux/kvm_para.h          |   5 +-
 mm/gup.c                               |  29 ++--
 mm/memory.c                            |  44 ++++-
 mm/page_alloc.c                        |   7 +
 mm/rmap.c                              |   2 +-
 mm/shmem.c                             |   7 +
 virt/Makefile                          |   2 +-
 virt/kvm/Kconfig                       |   4 +
 virt/kvm/Makefile                      |   1 +
 virt/kvm/kvm_main.c                    | 212 +++++++++++++++++++------
 virt/kvm/mem_protected.c               | 110 +++++++++++++
 35 files changed, 593 insertions(+), 159 deletions(-)
 create mode 100644 arch/x86/mm/mem_encrypt_common.c
 create mode 100644 virt/kvm/Makefile
 create mode 100644 virt/kvm/mem_protected.c
```
