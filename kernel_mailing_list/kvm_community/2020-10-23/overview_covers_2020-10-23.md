

#### [PATCH 00/22] Introduce the TDP MMU
##### From: Paolo Bonzini <pbonzini@redhat.com>

```c
From patchwork Fri Oct 23 16:30:02 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Paolo Bonzini <pbonzini@redhat.com>
X-Patchwork-Id: 11853983
Return-Path: <SRS0=GVEW=D6=vger.kernel.org=kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-3.9 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS autolearn=no autolearn_force=no
	version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 3578CC4363A
	for <kvm@archiver.kernel.org>; Fri, 23 Oct 2020 16:30:31 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id B4CCB21D47
	for <kvm@archiver.kernel.org>; Fri, 23 Oct 2020 16:30:30 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="SCQw1gyj"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1750701AbgJWQa3 (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Fri, 23 Oct 2020 12:30:29 -0400
Received: from us-smtp-delivery-124.mimecast.com ([63.128.21.124]:54738 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1750673AbgJWQa3 (ORCPT
        <rfc822;kvm@vger.kernel.org>); Fri, 23 Oct 2020 12:30:29 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1603470628;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=nWSnZNE5AMsZ/SnxNthTx2FSlmT82qW0XTqjQ2uPf6k=;
        b=SCQw1gyjHlIIw+ORYcT9BjLC9cECIyadlZ20GmDT+HzknKrGs29n+9D23+2G98ZzkJHf1E
        01uQZrcL67XlePHbyjTVdhJL6uHbkcaecGz68IfbaS/JipwEpSJplybs/RolEjo0opywr8
        1VygyiM7ozt038zZFYi1YCrPcavRFjk=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-362-K6-NilGUNFiSFSA-qQXypQ-1; Fri, 23 Oct 2020 12:30:26 -0400
X-MC-Unique: K6-NilGUNFiSFSA-qQXypQ-1
Received: from smtp.corp.redhat.com (int-mx04.intmail.prod.int.phx2.redhat.com
 [10.5.11.14])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id D8ADB804B7E;
        Fri, 23 Oct 2020 16:30:24 +0000 (UTC)
Received: from virtlab701.virt.lab.eng.bos.redhat.com
 (virtlab701.virt.lab.eng.bos.redhat.com [10.19.152.228])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 722F25DA78;
        Fri, 23 Oct 2020 16:30:24 +0000 (UTC)
From: Paolo Bonzini <pbonzini@redhat.com>
To: linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Cc: bgardon@google.com
Subject: [PATCH 00/22] Introduce the TDP MMU
Date: Fri, 23 Oct 2020 12:30:02 -0400
Message-Id: <20201023163024.2765558-1-pbonzini@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.14
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

I will just leave a link to Ben's detailed explanation

https://lore.kernel.org/kvm/20201014182700.2888246-1-bgardon@google.com/>

This series puts together all the small changes that were pointed out
on list; the only additions on my part are tracepoints and the introduction
of two source files spte.c and spte.h for code common to mmu.c and tdp_mmu.c.

Ben Gardon (19):
  kvm: mmu: Separate making non-leaf sptes from link_shadow_page
  kvm: x86/mmu: Separate making SPTEs from set_spte
  kvm: x86/mmu: Introduce tdp_iter
  kvm: x86/mmu: Init / Uninit the TDP MMU
  kvm: x86/mmu: Allocate and free TDP MMU roots
  kvm: x86/mmu: Add functions to handle changed TDP SPTEs
  kvm: x86/mmu: Support zapping SPTEs in the TDP MMU
  kvm: x86/mmu: Remove disallowed_hugepage_adjust shadow_walk_iterator
    arg
  kvm: x86/mmu: Add TDP MMU PF handler
  kvm: x86/mmu: Allocate struct kvm_mmu_pages for all pages in TDP MMU
  kvm: x86/mmu: Support invalidate range MMU notifier for TDP MMU
  kvm: x86/mmu: Add access tracking for tdp_mmu
  kvm: x86/mmu: Support changed pte notifier in tdp MMU
  kvm: x86/mmu: Support dirty logging for the TDP MMU
  kvm: x86/mmu: Support disabling dirty logging for the tdp MMU
  kvm: x86/mmu: Support write protection for nesting in tdp MMU
  kvm: x86/mmu: Support MMIO in the TDP MMU
  kvm: x86/mmu: Don't clear write flooding count for direct roots
  kvm: x86/mmu: NX largepage recovery for TDP MMU

Paolo Bonzini (2):
  KVM: mmu: Separate updating a PTE from kvm_set_pte_rmapp
  KVM: mmu: extract spte.h and spte.c

Peter Xu (1):
  KVM: Cache as_id in kvm_memory_slot

 arch/x86/include/asm/kvm_host.h |   14 +
 arch/x86/kvm/Makefile           |    3 +-
 arch/x86/kvm/mmu/mmu.c          |  785 ++++++---------------
 arch/x86/kvm/mmu/mmu_internal.h |   88 ++-
 arch/x86/kvm/mmu/mmutrace.h     |    8 +-
 arch/x86/kvm/mmu/paging_tmpl.h  |    3 +-
 arch/x86/kvm/mmu/spte.c         |  318 +++++++++
 arch/x86/kvm/mmu/spte.h         |  252 +++++++
 arch/x86/kvm/mmu/tdp_iter.c     |  182 +++++
 arch/x86/kvm/mmu/tdp_iter.h     |   60 ++
 arch/x86/kvm/mmu/tdp_mmu.c      | 1157 +++++++++++++++++++++++++++++++
 arch/x86/kvm/mmu/tdp_mmu.h      |   48 ++
 include/linux/kvm_host.h        |    2 +
 virt/kvm/kvm_main.c             |   12 +-
 14 files changed, 2329 insertions(+), 603 deletions(-)
 create mode 100644 arch/x86/kvm/mmu/spte.c
 create mode 100644 arch/x86/kvm/mmu/spte.h
 create mode 100644 arch/x86/kvm/mmu/tdp_iter.c
 create mode 100644 arch/x86/kvm/mmu/tdp_iter.h
 create mode 100644 arch/x86/kvm/mmu/tdp_mmu.c
 create mode 100644 arch/x86/kvm/mmu/tdp_mmu.h
```
#### [PATCH v15 00/14] KVM: Dirty ring interface
##### From: Peter Xu <peterx@redhat.com>

```c
From patchwork Fri Oct 23 18:33:44 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Peter Xu <peterx@redhat.com>
X-Patchwork-Id: 11854397
Return-Path: <SRS0=GVEW=D6=vger.kernel.org=kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-11.8 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	MAILING_LIST_MULTI,MENTIONS_GIT_HOSTING,SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED,
	USER_AGENT_GIT autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 06E8CC55179
	for <kvm@archiver.kernel.org>; Fri, 23 Oct 2020 18:35:45 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id A25B620BED
	for <kvm@archiver.kernel.org>; Fri, 23 Oct 2020 18:35:44 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="YCeLU8sQ"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1754837AbgJWSeI (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Fri, 23 Oct 2020 14:34:08 -0400
Received: from us-smtp-delivery-124.mimecast.com ([216.205.24.124]:58508 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1754825AbgJWSeG (ORCPT
        <rfc822;kvm@vger.kernel.org>); Fri, 23 Oct 2020 14:34:06 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1603478044;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:content-type:content-type:
         content-transfer-encoding:content-transfer-encoding;
        bh=pL5izsDjQRsypIzAphsn/fSHZTMIi/wrQPFpeQ075jc=;
        b=YCeLU8sQRI7j/R3eR4Zsxj6WQHUPBpTEobeZdbajvxvYWSlUYG+Q7ABFK7ypET7tFY5Che
        Kz6Pl0RhWt2mfrA5J8mIq5HKA6w40UclnAQIXZ+bQYPugbYQlC/IjsNo7PXO4BTz2lw563
        soGmOs47uw+lNvoWj1773uE2lRfGYF4=
Received: from mail-qt1-f200.google.com (mail-qt1-f200.google.com
 [209.85.160.200]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-545-bpdKfgv9MIu679dyVeMNFQ-1; Fri, 23 Oct 2020 14:34:01 -0400
X-MC-Unique: bpdKfgv9MIu679dyVeMNFQ-1
Received: by mail-qt1-f200.google.com with SMTP id a8so1674107qtx.13
        for <kvm@vger.kernel.org>; Fri, 23 Oct 2020 11:34:01 -0700 (PDT)
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:mime-version
         :content-transfer-encoding;
        bh=pL5izsDjQRsypIzAphsn/fSHZTMIi/wrQPFpeQ075jc=;
        b=szjaEihftyd9UuM/Qz/ZauCkGtEMJgVrW6wY3/FWxdZBlw1ohxwv45VUMEjzmhfdeY
         y3tv62G+si63GHbSDLByXKjm1ZZl/kaB5KfTHV7/ALFappxc0jlG6IoABECfPwyqV6v1
         bn/KkW9HZJWfKU9OvtDd41HamLp+PuRSUHJwWL3udEdoqDY3xyhSxOxjzLky6d7LL9XZ
         t/8n8k7SfKGpt667fa6K7M2nMZm+DlCzeGxHBGYsCO7qfbEP4CDVCeajmShpvgjkMdT3
         jFJpT+ZclRzrIr4MMCRJz0cO7T50wbSxOHx3Gnr/FgOanHpfbEy+snRyJHbdg1dYoBB9
         T/rg==
X-Gm-Message-State: AOAM532IQDi+hmbCmcvKWz9VPtMgRCdD8W1gPixSoAjzYPWcjEymXSK4
        gJrMs2PKhh/G6XY/i/Fty6KVnpvzm7REiO45xGP+D1IyPulWn5Uo1hj90vMCJu5ma7+HlzI1Loz
        YgiWwEANad9Os
X-Received: by 2002:a05:620a:12a6:: with SMTP id
 x6mr3846076qki.189.1603478040897;
        Fri, 23 Oct 2020 11:34:00 -0700 (PDT)
X-Google-Smtp-Source: 
 ABdhPJyCQX1jtoxh1ViMa4LFhKfs/4Hk6xAW6w7MMX1Jb8GfVLG+w/bEYVQx/I2vqVV8zeS85EEhZw==
X-Received: by 2002:a05:620a:12a6:: with SMTP id
 x6mr3846044qki.189.1603478040477;
        Fri, 23 Oct 2020 11:34:00 -0700 (PDT)
Received: from xz-x1.redhat.com
 (toroon474qw-lp140-04-174-95-215-133.dsl.bell.ca. [174.95.215.133])
        by smtp.gmail.com with ESMTPSA id
 u11sm1490407qtk.61.2020.10.23.11.33.59
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Fri, 23 Oct 2020 11:33:59 -0700 (PDT)
From: Peter Xu <peterx@redhat.com>
To: kvm@vger.kernel.org, linux-kernel@vger.kernel.org
Cc: Sean Christopherson <sean.j.christopherson@intel.com>,
        peterx@redhat.com, Andrew Jones <drjones@redhat.com>,
        "Dr . David Alan Gilbert" <dgilbert@redhat.com>,
        Paolo Bonzini <pbonzini@redhat.com>
Subject: [PATCH v15 00/14] KVM: Dirty ring interface
Date: Fri, 23 Oct 2020 14:33:44 -0400
Message-Id: <20201023183358.50607-1-peterx@redhat.com>
X-Mailer: git-send-email 2.26.2
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Paolo:

I'm rebasing again to the next merge window branch of kvm, assuming it's
kvm-5.10-1/upstream tag.  I don't know whether you'd like to merge it for this
merge window.  Just in case you still would like to, so you'll have something
to pick up very easily based on the new tdp mmu changes.

I feel a bit sorry for disturbing reviewers on recent frequent repostings.
It's just a way to try move this forward a bit since I still think it's a quite
useful thing to have upstream for not yet another logging interface, but also a
chance to improve auto-converge and maybe it could be useful to solve some huge
vm issues.  Anyway, I guess this is the last attempt if I won't get more review
comments out of this series, and I'll hold until so.

In all cases, please consider to squash patch1/2 into corresponding patches in
kvm-next because the numbers are wrong in current tree.

Thanks.

----------

KVM branch:
  https://github.com/xzpeter/linux/tree/kvm-dirty-ring

QEMU branch for testing:
  https://github.com/xzpeter/qemu/tree/kvm-dirty-ring

v15:
- rebase to kvm tree tag kvm-5.10-1/for-upstream

v14:
- fix a testcase race reported by kernel test robot.  More can be found at:
  https://lore.kernel.org/kvm/20201007204525.GF6026@xz-x1/

v13:
- rebase to kvm/queue rather than 5.9-rc7.  I think, kvm/queue is broken.  I
  can only test the dirty ring after I revert 3eb900173c71 ("KVM: x86: VMX:
  Prevent MSR passthrough when MSR access is denied", 2020-09-28), otherwise
  the guest will hang on vcpu0 looping forever during boot Linux.
- added another trivial patch "KVM: Documentation: Update entry for
  KVM_X86_SET_MSR_FILTER".  It should be squashed into 1a155254ff93 ("KVM: x86:
  Introduce MSR filtering", 2020-09-28) directly.

v12:
- add r-bs for Sean
- rebase

v11:
- rebased to kvm/queue (seems the newest)
- removed kvm_dirty_ring_waitqueue() tracepoint since not used
- set memslot->as_id in kvm_delete_memslot() [Sean]
- let __copy_to_user() always return -EFAULT [Sean]
- rename 'r' in alloc_apic_access_page into 'hva' [Sean]

For previous versions, please refer to:

V1: https://lore.kernel.org/kvm/20191129213505.18472-1-peterx@redhat.com
V2: https://lore.kernel.org/kvm/20191221014938.58831-1-peterx@redhat.com
V3: https://lore.kernel.org/kvm/20200109145729.32898-1-peterx@redhat.com
V4: https://lore.kernel.org/kvm/20200205025105.367213-1-peterx@redhat.com
V5: https://lore.kernel.org/kvm/20200304174947.69595-1-peterx@redhat.com
V6: https://lore.kernel.org/kvm/20200309214424.330363-1-peterx@redhat.com
V7: https://lore.kernel.org/kvm/20200318163720.93929-1-peterx@redhat.com
V8: https://lore.kernel.org/kvm/20200331190000.659614-1-peterx@redhat.com
V9: https://lore.kernel.org/kvm/20200523225659.1027044-1-peterx@redhat.com
V10: https://lore.kernel.org/kvm/20200601115957.1581250-1-peterx@redhat.com/

Overview
============

This is a continued work from Lei Cao <lei.cao@stratus.com> and Paolo
Bonzini on the KVM dirty ring interface.

The new dirty ring interface is another way to collect dirty pages for
the virtual machines. It is different from the existing dirty logging
interface in a few ways, majorly:

  - Data format: The dirty data was in a ring format rather than a
    bitmap format, so dirty bits to sync for dirty logging does not
    depend on the size of guest memory any more, but speed of
    dirtying.  Also, the dirty ring is per-vcpu, while the dirty
    bitmap is per-vm.

  - Data copy: The sync of dirty pages does not need data copy any more,
    but instead the ring is shared between the userspace and kernel by
    page sharings (mmap() on vcpu fd)

  - Interface: Instead of using the old KVM_GET_DIRTY_LOG,
    KVM_CLEAR_DIRTY_LOG interfaces, the new ring uses the new
    KVM_RESET_DIRTY_RINGS ioctl when we want to reset the collected
    dirty pages to protected mode again (works like
    KVM_CLEAR_DIRTY_LOG, but ring based).  To collecting dirty bits,
    we only need to read the ring data, no ioctl is needed.

Ring Layout
===========

KVM dirty ring is per-vcpu.  Each ring is an array of kvm_dirty_gfn
defined as:

struct kvm_dirty_gfn {
        __u32 flags;
        __u32 slot; /* as_id | slot_id */
        __u64 offset;
};

Each GFN is a state machine itself.  The state is embeded in the flags
field, as defined in the uapi header:

/*
 * KVM dirty GFN flags, defined as:
 *
 * |---------------+---------------+--------------|
 * | bit 1 (reset) | bit 0 (dirty) | Status       |
 * |---------------+---------------+--------------|
 * |             0 |             0 | Invalid GFN  |
 * |             0 |             1 | Dirty GFN    |
 * |             1 |             X | GFN to reset |
 * |---------------+---------------+--------------|
 *
 * Lifecycle of a dirty GFN goes like:
 *
 *      dirtied         collected        reset
 * 00 -----------> 01 -------------> 1X -------+
 *  ^                                          |
 *  |                                          |
 *  +------------------------------------------+
 *
 * The userspace program is only responsible for the 01->1X state
 * conversion (to collect dirty bits).  Also, it must not skip any
 * dirty bits so that dirty bits are always collected in sequence.
 */

Testing
=======

This series provided both the implementation of the KVM dirty ring and
the test case.  Also I've implemented the QEMU counterpart that can
run with the new KVM, link can be found at the top of the cover
letter.  However that's still a very initial version which is prone to
change and future optimizations.

I did some measurement with the new method with 24G guest running some
dirty workload, I don't see any speedup so far, even in some heavy
dirty load it'll be slower (e.g., when 800MB/s random dirty rate, kvm
dirty ring takes average of ~73s to complete migration while dirty
logging only needs average of ~55s).  However that's understandable
because 24G guest means only 1M dirty bitmap, that's still a suitable
case for dirty logging.  Meanwhile heavier workload means worst case
for dirty ring.

More tests are welcomed if there's bigger host/guest, especially on
COLO-like workload.

Please review, thanks.

Peter Xu (14):
  KVM: Documentation: Update entry for KVM_X86_SET_MSR_FILTER
  KVM: Documentation: Update entry for KVM_CAP_ENFORCE_PV_CPUID
  KVM: X86: Don't track dirty for KVM_SET_[TSS_ADDR|IDENTITY_MAP_ADDR]
  KVM: Pass in kvm pointer into mark_page_dirty_in_slot()
  KVM: X86: Implement ring-based dirty memory tracking
  KVM: Make dirty ring exclusive to dirty bitmap log
  KVM: Don't allocate dirty bitmap if dirty ring is enabled
  KVM: selftests: Always clear dirty bitmap after iteration
  KVM: selftests: Sync uapi/linux/kvm.h to tools/
  KVM: selftests: Use a single binary for dirty/clear log test
  KVM: selftests: Introduce after_vcpu_run hook for dirty log test
  KVM: selftests: Add dirty ring buffer test
  KVM: selftests: Let dirty_log_test async for dirty ring test
  KVM: selftests: Add "-c" parameter to dirty log test

 Documentation/virt/kvm/api.rst                | 129 ++++-
 arch/x86/include/asm/kvm_host.h               |   6 +-
 arch/x86/include/uapi/asm/kvm.h               |   1 +
 arch/x86/kvm/Makefile                         |   3 +-
 arch/x86/kvm/mmu/mmu.c                        |  10 +-
 arch/x86/kvm/mmu/tdp_mmu.c                    |   2 +-
 arch/x86/kvm/svm/avic.c                       |   9 +-
 arch/x86/kvm/vmx/vmx.c                        |  96 ++--
 arch/x86/kvm/x86.c                            |  46 +-
 include/linux/kvm_dirty_ring.h                | 103 ++++
 include/linux/kvm_host.h                      |  21 +-
 include/trace/events/kvm.h                    |  63 +++
 include/uapi/linux/kvm.h                      |  53 ++
 tools/include/uapi/linux/kvm.h                |  78 ++-
 tools/testing/selftests/kvm/Makefile          |   2 -
 .../selftests/kvm/clear_dirty_log_test.c      |   6 -
 tools/testing/selftests/kvm/dirty_log_test.c  | 516 ++++++++++++++++--
 .../testing/selftests/kvm/include/kvm_util.h  |   4 +
 tools/testing/selftests/kvm/lib/kvm_util.c    |  72 ++-
 .../selftests/kvm/lib/kvm_util_internal.h     |   4 +
 virt/kvm/dirty_ring.c                         | 197 +++++++
 virt/kvm/kvm_main.c                           | 158 +++++-
 22 files changed, 1438 insertions(+), 141 deletions(-)
 create mode 100644 include/linux/kvm_dirty_ring.h
 delete mode 100644 tools/testing/selftests/kvm/clear_dirty_log_test.c
 create mode 100644 virt/kvm/dirty_ring.c
```
