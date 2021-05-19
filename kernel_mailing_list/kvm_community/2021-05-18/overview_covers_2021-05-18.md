

#### [PATCH v2 0/5] KVM: x86: hyper-v: Conditionally allow SynIC with
##### From: Vitaly Kuznetsov <vkuznets@redhat.com>

```c
From patchwork Tue May 18 14:43:34 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Vitaly Kuznetsov <vkuznets@redhat.com>
X-Patchwork-Id: 12264941
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-11.1 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS autolearn=ham
	autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 26936C43460
	for <kvm@archiver.kernel.org>; Tue, 18 May 2021 14:43:49 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 08D50610A8
	for <kvm@archiver.kernel.org>; Tue, 18 May 2021 14:43:49 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S236482AbhEROpG (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 18 May 2021 10:45:06 -0400
Received: from us-smtp-delivery-124.mimecast.com ([216.205.24.124]:29000 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S236137AbhEROpF (ORCPT
        <rfc822;kvm@vger.kernel.org>); Tue, 18 May 2021 10:45:05 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1621349027;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=SnOgIuG0QI+D7+cp//iQj6D3t7PXPlfIr3EDmLUD8cw=;
        b=WNsxYLOrvagJF5/1NSYAbRwqFEKmLT4o6qT4fAKFEQo6Qa5/SyPcmG7CEtzPNT9XMNOATW
        DpSEaTAfXScUxAwYNj27LqEpfFdVwbvvnMZ00Hc2mV6jrMAZAGe5DNw/I7AlbSGbyK5dm7
        g6n4IBNQBUxgJrIm9hx2dNKNZD3jKs4=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-333-WW7pL-ltMkez6h8FlYudqw-1; Tue, 18 May 2021 10:43:44 -0400
X-MC-Unique: WW7pL-ltMkez6h8FlYudqw-1
Received: from smtp.corp.redhat.com (int-mx01.intmail.prod.int.phx2.redhat.com
 [10.5.11.11])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 327C9188E3C1;
        Tue, 18 May 2021 14:43:43 +0000 (UTC)
Received: from vitty.brq.redhat.com (unknown [10.40.193.194])
        by smtp.corp.redhat.com (Postfix) with ESMTP id B22671349A;
        Tue, 18 May 2021 14:43:40 +0000 (UTC)
From: Vitaly Kuznetsov <vkuznets@redhat.com>
To: kvm@vger.kernel.org, Paolo Bonzini <pbonzini@redhat.com>
Cc: Sean Christopherson <seanjc@google.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Maxim Levitsky <mlevitsk@redhat.com>,
        Kechen Lu <kechenl@nvidia.com>, linux-kernel@vger.kernel.org
Subject: [PATCH v2 0/5] KVM: x86: hyper-v: Conditionally allow SynIC with
 APICv/AVIC
Date: Tue, 18 May 2021 16:43:34 +0200
Message-Id: <20210518144339.1987982-1-vkuznets@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.11
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Changes since v1 (Sean):
- Use common 'enable_apicv' variable for both APICv and AVIC instead of 
 adding a new hook to 'struct kvm_x86_ops'.
- Drop unneded CONFIG_X86_LOCAL_APIC checks from VMX/SVM code along the
 way.

Original description:

APICV_INHIBIT_REASON_HYPERV is currently unconditionally forced upon
SynIC activation as SynIC's AutoEOI is incompatible with APICv/AVIC. It is,
however, possible to track whether the feature was actually used by the
guest and only inhibit APICv/AVIC when needed.

The feature can be tested with QEMU's 'hv-passthrough' debug mode.

Note, 'avic' kvm-amd module parameter is '0' by default and thus needs to
be explicitly enabled.

Vitaly Kuznetsov (5):
  KVM: SVM: Drop unneeded CONFIG_X86_LOCAL_APIC check for AVIC
  KVM: VMX: Drop unneeded CONFIG_X86_LOCAL_APIC check from
    cpu_has_vmx_posted_intr()
  KVM: x86: Use common 'enable_apicv' variable for both APICv and AVIC
  KVM: x86: Invert APICv/AVIC enablement check
  KVM: x86: hyper-v: Deactivate APICv only when AutoEOI feature is in
    use

 arch/x86/include/asm/kvm_host.h |  5 ++++-
 arch/x86/kvm/hyperv.c           | 27 +++++++++++++++++++++------
 arch/x86/kvm/svm/avic.c         | 16 +++++-----------
 arch/x86/kvm/svm/svm.c          | 24 +++++++++++++-----------
 arch/x86/kvm/svm/svm.h          |  2 --
 arch/x86/kvm/vmx/capabilities.h |  4 +---
 arch/x86/kvm/vmx/vmx.c          |  2 --
 arch/x86/kvm/x86.c              |  9 ++++++---
 8 files changed, 50 insertions(+), 39 deletions(-)
```
#### [PATCH v5 0/7] Lazily allocate memslot rmaps
##### From: Ben Gardon <bgardon@google.com>

```c
From patchwork Tue May 18 17:34:07 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Ben Gardon <bgardon@google.com>
X-Patchwork-Id: 12265235
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-21.3 required=3.0 tests=BAYES_00,DKIMWL_WL_MED,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT,
	USER_IN_DEF_DKIM_WL autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 5083EC433B4
	for <kvm@archiver.kernel.org>; Tue, 18 May 2021 17:34:26 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 30465611AC
	for <kvm@archiver.kernel.org>; Tue, 18 May 2021 17:34:26 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1351163AbhERRfn (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 18 May 2021 13:35:43 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:40978 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1346491AbhERRfj (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 18 May 2021 13:35:39 -0400
Received: from mail-pj1-x104a.google.com (mail-pj1-x104a.google.com
 [IPv6:2607:f8b0:4864:20::104a])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id E5965C06175F
        for <kvm@vger.kernel.org>; Tue, 18 May 2021 10:34:18 -0700 (PDT)
Received: by mail-pj1-x104a.google.com with SMTP id
 em20-20020a17090b0154b029015d6b612e97so2206454pjb.3
        for <kvm@vger.kernel.org>; Tue, 18 May 2021 10:34:18 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=date:message-id:mime-version:subject:from:to:cc;
        bh=DXZ5TJfbcJBrlmnD1QhFY5JORCd7o8ZDmjjRDdrnQQ4=;
        b=fITe5PKZVFB3hTUkaiMHz50JHcFawCTY/nRNzHlm4ICLkX/hPhHQGjnvGFXfrAP9FT
         PnSzzhxOGBWcUCFTClTphe4IU48lVMM4UlBFsDN3PzKwWMfFUi7fwlcAjUPT/xfdNv3y
         sqgYDyBZJX5vOyk9mCL2FF0gMZi34YQ0a6X2IoZBfz62LdY0pm87i0C0s3I7kh2lQ5P/
         8F1Mt7UbdEN3uI2tQ5Hu6YzMYk+h0q//e6o1NM+lEykfGgnxXncz5ZQNaxXEh0BTJlZb
         GkdmtLjSUkQTwHlKsaSMn/yu+CXcgJEXeam7WlbRcu8N840lbh/YT0tifYtJBU3GJnMk
         Cu8A==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:date:message-id:mime-version:subject:from:to:cc;
        bh=DXZ5TJfbcJBrlmnD1QhFY5JORCd7o8ZDmjjRDdrnQQ4=;
        b=oMxPFEj6TwEivziD2V1Z0pEM4SUOk2iBqrkfca/jOVjG9nhEwAAk7ZQIdY0rSnOfSG
         iQMlDmxg6XoyROBH25mFW8Eu5kn6DKEGCNliVtg0toho+8CRqXkTek3ZufDN7Phapphc
         SZi5mWfbYaxlbNAqTaDsSkfatXgJZminU8W21p6a9zcxLlqtdYN8ZCJ6kCEMKwXlWLET
         xUgrwrcz4iLYIegthTdH4hzhtPi++lhiQVFM9fviN2GiBYYf43UT0wvBLzpyNqCi3Zaa
         dmMV9VijD7zLKykW5N5Ucz+RqNfZW5U9md8mQ0fGhBP2wUevxOunIG6k3PqAtJcTUJYI
         xmeQ==
X-Gm-Message-State: AOAM5315tuIDbgIchOrzVqFuDeAm2r8BM9KVHkH+RAT1abihWbrB0A6M
        owUKptkxjlQVVhTETwUwctrqJ44iTnYi
X-Google-Smtp-Source: 
 ABdhPJxH/9tG/t86LHHAa4/hAgCVq/qgoHyGjHoR5nIyyfVZPiukffsaMKMgU4PaB8wt5NJZXBdDg7nHZ4uJ
X-Received: from bgardon.sea.corp.google.com
 ([2620:15c:100:202:2715:2de:868e:9db7])
 (user=bgardon job=sendgmr) by 2002:a17:90a:4487:: with SMTP id
 t7mr611698pjg.1.1621359257711; Tue, 18 May 2021 10:34:17 -0700 (PDT)
Date: Tue, 18 May 2021 10:34:07 -0700
Message-Id: <20210518173414.450044-1-bgardon@google.com>
Mime-Version: 1.0
X-Mailer: git-send-email 2.31.1.751.gd2f1c929bd-goog
Subject: [PATCH v5 0/7] Lazily allocate memslot rmaps
From: Ben Gardon <bgardon@google.com>
To: linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Cc: Paolo Bonzini <pbonzini@redhat.com>, Peter Xu <peterx@redhat.com>,
        Sean Christopherson <seanjc@google.com>,
        Peter Shier <pshier@google.com>,
        Yulei Zhang <yulei.kernel@gmail.com>,
        Wanpeng Li <kernellwp@gmail.com>,
        Xiao Guangrong <xiaoguangrong.eric@gmail.com>,
        Kai Huang <kai.huang@intel.com>,
        Keqian Zhu <zhukeqian1@huawei.com>,
        David Hildenbrand <david@redhat.com>,
        Ben Gardon <bgardon@google.com>
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This series enables KVM to save memory when using the TDP MMU by waiting
to allocate memslot rmaps until they are needed. To do this, KVM tracks
whether or not a shadow root has been allocated. In order to get away
with not allocating the rmaps, KVM must also be sure to skip operations
which iterate over the rmaps. If the TDP MMU is in use and we have not
allocated a shadow root, these operations would essentially be op-ops
anyway. Skipping the rmap operations has a secondary benefit of avoiding
acquiring the MMU lock in write mode in many cases, substantially
reducing MMU lock contention.

This series was tested on an Intel Skylake machine. With the TDP MMU off
and on, this introduced no new failures on kvm-unit-tests or KVM selftests.

Changelog:
v2:
	Incorporated feedback from Paolo and Sean
	Replaced the memslot_assignment_lock with slots_arch_lock, which
	has a larger critical section.

v3:
	Removed shadow_mmu_active as suggested by Sean
	Removed everything except adding a return value to
	kvm_mmu_init_tdp_mmu from patch 1 of v2
	Added RCU protection and better memory ordering for installing the
	memslot rmaps as suggested by Paolo
	Reordered most of the patches

v4:
	Renamed functions to allocate and free memslots based on feedback
	from David.
	Eliminated the goto in memslot_rmap_alloc, as David suggested.
	Eliminated kvm_memslots_have_rmaps and updated comments on uses of
	memslots_have_rmaps. Suggested by Paolo.
	Changed the description on patch 7 to one Paolo suggested.
	Collected Reviewed-by tags from David.
	Dropped the patch to add RCU notations to rmap accesses.

v5:
	Responding to comments from Sean.
	Improved comments
	Swapped args to kvm_copy_memslots to match memcpy
	Fixed some line wrap and declaration style issues
	No longer check if memslots have rmaps before operations which
	iterate through active_mmu_pages
	Re-added the kvm_memslots_have_rmaps helper
	Fixed a couple missing unlocks for the slots_arch_lock

Ben Gardon (7):
  KVM: x86/mmu: Deduplicate rmap freeing
  KVM: x86/mmu: Factor out allocating memslot rmap
  KVM: mmu: Refactor memslot copy
  KVM: mmu: Add slots_arch_lock for memslot arch fields
  KVM: x86/mmu: Add a field to control memslot rmap allocation
  KVM: x86/mmu: Skip rmap operations if rmaps not allocated
  KVM: x86/mmu: Lazily allocate memslot rmaps

 arch/x86/include/asm/kvm_host.h |   8 ++
 arch/x86/kvm/mmu.h              |  10 +++
 arch/x86/kvm/mmu/mmu.c          | 125 ++++++++++++++++++++------------
 arch/x86/kvm/mmu/tdp_mmu.c      |   6 +-
 arch/x86/kvm/mmu/tdp_mmu.h      |   4 +-
 arch/x86/kvm/x86.c              | 109 +++++++++++++++++++++++-----
 include/linux/kvm_host.h        |   9 +++
 virt/kvm/kvm_main.c             |  77 ++++++++++++++++----
 8 files changed, 263 insertions(+), 85 deletions(-)
```
