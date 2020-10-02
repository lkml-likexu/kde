

#### [PATCH v13 00/14] KVM: Dirty ring interface
##### From: Peter Xu <peterx@redhat.com>

```c
From patchwork Thu Oct  1 01:20:30 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Peter Xu <peterx@redhat.com>
X-Patchwork-Id: 11810663
Return-Path: <SRS0=iPdE=DI=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id D724C1580
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  1 Oct 2020 01:21:04 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id B58592072E
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  1 Oct 2020 01:21:04 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="NoZIPtdz"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1730211AbgJABU5 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 30 Sep 2020 21:20:57 -0400
Received: from us-smtp-delivery-124.mimecast.com ([63.128.21.124]:52137 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1725892AbgJABU4 (ORCPT
        <rfc822;kvm@vger.kernel.org>); Wed, 30 Sep 2020 21:20:56 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1601515254;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:content-type:content-type:
         content-transfer-encoding:content-transfer-encoding;
        bh=V8t9L7zpYIywUyRGOOdAwdt5unIz21ICpoec+6DE3z4=;
        b=NoZIPtdzIX46a6uT9L0bcjuiqzgRyj6Cl/6ptc+sepSpoP6qw4yQUla1sPgUvIgKeSljIX
        zB+lEABUYnw8zEgjMIamkafPYPvrM0/9tu9s1Drrc2RwWR5lfOvI2m5/TQjgr3RI1iruG7
        jvBMA6B5qKqGgTTdlnJXYsHXTNs4YOY=
Received: from mail-qk1-f197.google.com (mail-qk1-f197.google.com
 [209.85.222.197]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-142-re_TRbVxPeqCaSZX_6VOnA-1; Wed, 30 Sep 2020 21:20:50 -0400
X-MC-Unique: re_TRbVxPeqCaSZX_6VOnA-1
Received: by mail-qk1-f197.google.com with SMTP id j5so2103088qka.7
        for <kvm@vger.kernel.org>; Wed, 30 Sep 2020 18:20:50 -0700 (PDT)
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:mime-version
         :content-transfer-encoding;
        bh=V8t9L7zpYIywUyRGOOdAwdt5unIz21ICpoec+6DE3z4=;
        b=C29rhgrOgtBE2m9+w0fvg83oXvOUYozg9uZYjo5GKPmLrRFMdiUAveGwcH5h5PCjNL
         iifWc+djI/nhTkKi5Bjkso9X/ZnS2rtcglCnXhRqUjHFzX+iV8RQBh3d5bv3Vz5l3PTo
         RepMpni8/Y70UQjT23GXutnqNrZaul/1zeE0h9csl4Trh3R3slJE7QK42r18mKyFD4Sr
         CjQEP5no28blxuLTCtlROBHy2jfhSW8XpVCZIhBa2Cb7+63gn81ZMSrF64aE68cloDey
         F5Ibb0eow1hE04WcTzJiWJ5DS7pl3JZqFzAUgDKw8jZvSYcF8thUCfQX5bOLnTGbZ+uR
         5fIQ==
X-Gm-Message-State: AOAM532HNOI9iUQ9hP4G964+CuWjMAgwJUfsCpc7RPeRlyZlgpdDdYkG
        01qmmzcdmmrw5RD8pgS3xgdxEUC+koNdonhp5WK56KNTXxz6YAD4PMcPy2Siy1Y9lhrrsNRYkyE
        txqDWoBiXVukw
X-Received: by 2002:a37:a054:: with SMTP id j81mr5197831qke.23.1601515249463;
        Wed, 30 Sep 2020 18:20:49 -0700 (PDT)
X-Google-Smtp-Source: 
 ABdhPJy2WTmL41jsnkmz+AB247dto8LWz7tsH2NlMaQ6OGZNbM4G/70/KS1ZMZbL3cD1kFqRnyBJyg==
X-Received: by 2002:a37:a054:: with SMTP id j81mr5197803qke.23.1601515249053;
        Wed, 30 Sep 2020 18:20:49 -0700 (PDT)
Received: from localhost.localdomain
 (toroon474qw-lp130-09-184-147-14-204.dsl.bell.ca. [184.147.14.204])
        by smtp.gmail.com with ESMTPSA id
 y46sm4714478qtc.30.2020.09.30.18.20.47
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Wed, 30 Sep 2020 18:20:47 -0700 (PDT)
From: Peter Xu <peterx@redhat.com>
To: kvm@vger.kernel.org, linux-kernel@vger.kernel.org
Cc: peterx@redhat.com, "Dr . David Alan Gilbert" <dgilbert@redhat.com>,
        Andrew Jones <drjones@redhat.com>,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        Paolo Bonzini <pbonzini@redhat.com>
Subject: [PATCH v13 00/14] KVM: Dirty ring interface
Date: Wed, 30 Sep 2020 21:20:30 -0400
Message-Id: <20201001012044.5151-1-peterx@redhat.com>
X-Mailer: git-send-email 2.26.2
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

KVM branch:
  https://github.com/xzpeter/linux/tree/kvm-dirty-ring

QEMU branch for testing:
  https://github.com/xzpeter/qemu/tree/kvm-dirty-ring

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

v10:
- remove unused identity_map_pfn in init_rmode_identity_map [syzbot]
- add "static" to kvm_dirty_ring_full [syzbot]
- kvm_page_in_dirty_ring() use "#if" macros for KVM_DIRTY_LOG_PAGE_OFFSET to
  quiesce syzbot [syzbot]
- s/false/null/ in gfn_to_memslot_dirty_bitmap() [syzbot]

v9:
- patch 3: __x86_set_memory_region: squash another trivial change to return
  (0xdeadull << 48) always for slot removal [Sean]
- pick r-bs for Drew

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
  KVM: Cache as_id in kvm_memory_slot
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

 Documentation/virt/kvm/api.rst                | 126 ++++-
 arch/x86/include/asm/kvm_host.h               |   6 +-
 arch/x86/include/uapi/asm/kvm.h               |   1 +
 arch/x86/kvm/Makefile                         |   3 +-
 arch/x86/kvm/mmu/mmu.c                        |  10 +-
 arch/x86/kvm/svm/avic.c                       |   9 +-
 arch/x86/kvm/vmx/vmx.c                        |  96 ++--
 arch/x86/kvm/x86.c                            |  46 +-
 include/linux/kvm_dirty_ring.h                | 103 ++++
 include/linux/kvm_host.h                      |  19 +
 include/trace/events/kvm.h                    |  63 +++
 include/uapi/linux/kvm.h                      |  53 ++
 tools/include/uapi/linux/kvm.h                |  77 ++-
 tools/testing/selftests/kvm/Makefile          |   2 -
 .../selftests/kvm/clear_dirty_log_test.c      |   6 -
 tools/testing/selftests/kvm/dirty_log_test.c  | 505 ++++++++++++++++--
 .../testing/selftests/kvm/include/kvm_util.h  |   4 +
 tools/testing/selftests/kvm/lib/kvm_util.c    |  72 ++-
 .../selftests/kvm/lib/kvm_util_internal.h     |   4 +
 virt/kvm/dirty_ring.c                         | 197 +++++++
 virt/kvm/kvm_main.c                           | 168 +++++-
 21 files changed, 1432 insertions(+), 138 deletions(-)
 create mode 100644 include/linux/kvm_dirty_ring.h
 delete mode 100644 tools/testing/selftests/kvm/clear_dirty_log_test.c
 create mode 100644 virt/kvm/dirty_ring.c
```
#### [PATCH v2 0/7] Update travis CI
##### From: Thomas Huth <thuth@redhat.com>

```c
From patchwork Thu Oct  1 07:22:27 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Thomas Huth <thuth@redhat.com>
X-Patchwork-Id: 11811013
Return-Path: <SRS0=iPdE=DI=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 184D392C
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  1 Oct 2020 07:22:44 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id EC2FC21531
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  1 Oct 2020 07:22:43 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="Vu6PuRXI"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1731332AbgJAHWn (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 1 Oct 2020 03:22:43 -0400
Received: from us-smtp-delivery-124.mimecast.com ([63.128.21.124]:21196 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1725892AbgJAHWl (ORCPT
        <rfc822;kvm@vger.kernel.org>); Thu, 1 Oct 2020 03:22:41 -0400
Dkim-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1601536960;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc; bh=KqdZAW3ctfaEaauJwNsn/aYax9MeGE15O+1IM7VJsF0=;
        b=Vu6PuRXI3pnP3YcbWZpUtWJiqAZ7csB3//9U/tYLsHXWm56KQi34Ml7g04MdFxsFHxUiab
        kvE59BAf116JKpBWDHr3uNXrNME1x5F258D9yLrOgyF/WP6h9TXC2R2TFLDRM09Ql7CyGr
        MSQQp2liXWbmuEYdD89PCKM9wXSw6Jw=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-424-zPhDjnU8MPSL710JJ2hOPQ-1; Thu, 01 Oct 2020 03:22:39 -0400
X-MC-Unique: zPhDjnU8MPSL710JJ2hOPQ-1
Received: from smtp.corp.redhat.com (int-mx02.intmail.prod.int.phx2.redhat.com
 [10.5.11.12])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 286F51018F65
        for <kvm@vger.kernel.org>; Thu,  1 Oct 2020 07:22:38 +0000 (UTC)
Received: from thuth.com (ovpn-112-107.ams2.redhat.com [10.36.112.107])
        by smtp.corp.redhat.com (Postfix) with ESMTP id E3E35619B5;
        Thu,  1 Oct 2020 07:22:36 +0000 (UTC)
From: Thomas Huth <thuth@redhat.com>
To: kvm@vger.kernel.org
Cc: pbonzini@redhat.com, drjones@redhat.com, lvivier@redhat.com
Subject: [PATCH v2 0/7] Update travis CI
Date: Thu,  1 Oct 2020 09:22:27 +0200
Message-Id: <20201001072234.143703-1-thuth@redhat.com>
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.12
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Travis now features Ubuntu Focal containers, so we can update our
kvm-unit-tests CI to use it for getting a newer version of QEMU and
the compilers. Thanks to this QEMU update, we can now run more tests
with TCG here.

Additionally, this series switches the second aarch64 build job to
use the native builder - this way we can use the Clang compiler
there to get some additional test coverage. This indeed already helped
to discover some bogus register constraints in the aarch64 code.
(ppc64 and s390x are not using the native builders yet since there are
still some issues with Clang there that I haven't quite figured out ...
that's maybe something for later)

v2:
 - The patch that changed "bionic" into "focal" and the s390x patch
   are already merged, so they are not included here anymore
 - Fixed rebase conflicts in the x86 patches
 - Dropped the hyperv tests from the 32-bit builds (they are going
   to be marked as 64-bit only)

Thomas Huth (7):
  travis.yml: Rework the x86 64-bit tests
  travis.yml: Refresh the x86 32-bit test list
  travis.yml: Add the selftest-setup ppc64 test
  kbuild: fix asm-offset generation to work with clang
  arm/pmu: Fix inline assembly for Clang
  lib/arm64/spinlock: Fix inline assembly for Clang
  travis.yml: Rework the aarch64 jobs

 .travis.yml             | 63 +++++++++++++++++++++++------------------
 arm/pmu.c               | 10 ++++---
 lib/arm64/spinlock.c    |  2 +-
 lib/kbuild.h            |  6 ++--
 scripts/asm-offsets.mak |  5 ++--
 5 files changed, 48 insertions(+), 38 deletions(-)
```
#### [PATCH v7 0/4] KVM: nSVM: ondemand nested state allocation
##### From: Maxim Levitsky <mlevitsk@redhat.com>

```c
From patchwork Thu Oct  1 11:29:50 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Maxim Levitsky <mlevitsk@redhat.com>
X-Patchwork-Id: 11811337
Return-Path: <SRS0=iPdE=DI=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 5D507618
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  1 Oct 2020 11:30:53 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 422E42137B
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  1 Oct 2020 11:30:53 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="aBKQ+cak"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1731961AbgJALaP (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 1 Oct 2020 07:30:15 -0400
Received: from us-smtp-delivery-124.mimecast.com ([216.205.24.124]:46491 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1731846AbgJALaN (ORCPT
        <rfc822;kvm@vger.kernel.org>); Thu, 1 Oct 2020 07:30:13 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1601551812;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=lW3c3YcYcFwwbVYa8MVvOts8QufJEheVZBkFp2GjStc=;
        b=aBKQ+cakLy3Uv1z44mdlXYe5XfQCSyUULT2qwZ42byXeNPzC5NVQxI9q5kLe5pWg3vPBbe
        oi3wcrBs1cCrdt84jU7tZD4UUZkelJffnVZG/potywG/RKqW+DjZpXaEKYuQwtzimvvebG
        RY+pez2ewlTbt9L37/SU6DbNYcVeIo8=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-113-zYie6UEjNGSos4rTC9BJyw-1; Thu, 01 Oct 2020 07:30:11 -0400
X-MC-Unique: zYie6UEjNGSos4rTC9BJyw-1
Received: from smtp.corp.redhat.com (int-mx05.intmail.prod.int.phx2.redhat.com
 [10.5.11.15])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 006D71882FA1;
        Thu,  1 Oct 2020 11:30:09 +0000 (UTC)
Received: from localhost.localdomain (unknown [10.35.206.29])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 3C47275122;
        Thu,  1 Oct 2020 11:29:56 +0000 (UTC)
From: Maxim Levitsky <mlevitsk@redhat.com>
To: kvm@vger.kernel.org
Cc: Borislav Petkov <bp@alien8.de>,
        x86@kernel.org (maintainer:X86 ARCHITECTURE (32-BIT AND 64-BIT)),
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        Thomas Gleixner <tglx@linutronix.de>,
        "H. Peter Anvin" <hpa@zytor.com>,
        Paolo Bonzini <pbonzini@redhat.com>,
        Ingo Molnar <mingo@redhat.com>, linux-kernel@vger.kernel.org,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Joerg Roedel <joro@8bytes.org>,
        Maxim Levitsky <mlevitsk@redhat.com>
Subject: [PATCH v7 0/4] KVM: nSVM: ondemand nested state allocation
Date: Thu,  1 Oct 2020 14:29:50 +0300
Message-Id: <20201001112954.6258-1-mlevitsk@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.15
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This is the next version of this patch series.

In V5 I adopted Sean Christopherson's suggestion to make .set_efer return
a negative error (-ENOMEM in this case) which in most cases in kvm
propagates to the userspace.

I noticed though that wrmsr emulation code doesn't do this and instead
it injects #GP to the guest on _any_ error.

So I fixed the wrmsr code to behave in a similar way to the rest
of the kvm code.
(#GP only on a positive error value, and forward the negative error to
the userspace)

I had to adjust one wrmsr handler (xen_hvm_config) to stop it from returning
negative values	so that new WRMSR emulation behavior doesn't break it.
This patch was only compile tested.

The memory allocation failure was tested by always returning -ENOMEM
from svm_allocate_nested.

The nested allocation itself was tested by countless attempts to run
nested guests, do nested migration on both my AMD and Intel machines.
I wasn't able to break it.

Changes from V5: addressed Sean Christopherson's review feedback.
Changes from V6: rebased the code on latest kvm/queue

Best regards,
	Maxim Levitsky

Maxim Levitsky (4):
  KVM: x86: xen_hvm_config: cleanup return values
  KVM: x86: report negative values from wrmsr emulation to userspace
  KVM: x86: allow kvm_x86_ops.set_efer to return an error value
  KVM: nSVM: implement on demand allocation of the nested state

 arch/x86/include/asm/kvm_host.h |  2 +-
 arch/x86/kvm/emulate.c          |  4 +--
 arch/x86/kvm/svm/nested.c       | 42 ++++++++++++++++++++++
 arch/x86/kvm/svm/svm.c          | 64 ++++++++++++++++++---------------
 arch/x86/kvm/svm/svm.h          | 10 +++++-
 arch/x86/kvm/vmx/vmx.c          |  6 ++--
 arch/x86/kvm/x86.c              | 39 ++++++++++----------
 7 files changed, 114 insertions(+), 53 deletions(-)
```
#### [PATCH 0/3] KVM: x86: allow for more CPUID entries
##### From: Vitaly Kuznetsov <vkuznets@redhat.com>

```c
From patchwork Thu Oct  1 13:05:38 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Vitaly Kuznetsov <vkuznets@redhat.com>
X-Patchwork-Id: 11811429
Return-Path: <SRS0=iPdE=DI=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 4108D1668
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  1 Oct 2020 13:05:53 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 23C6420B1F
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  1 Oct 2020 13:05:53 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="avCjQAZb"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1732099AbgJANFv (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 1 Oct 2020 09:05:51 -0400
Received: from us-smtp-delivery-124.mimecast.com ([63.128.21.124]:20241 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1731952AbgJANFt (ORCPT
        <rfc822;kvm@vger.kernel.org>); Thu, 1 Oct 2020 09:05:49 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1601557548;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=1JG7ezNBqKZhBbCXdsZ165RW99M6aDw/GQyklFdmaXA=;
        b=avCjQAZbLxSXBADzfkLTzeTGE0x/IVO84lu8IEQpUffQRiEaTR289R1BKHmXph02H5OA5y
        iAHyx4yPtO9GdZELvk/GRN+zhOgmRQVfNg3AQhacP4aj4tmW6yKmPmhS9rehGt5J874XCY
        7lOdAImB3poijT2EctfPk0R45H4E2m8=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-528-JSH1ATewPmOR9i5Wag52aw-1; Thu, 01 Oct 2020 09:05:47 -0400
X-MC-Unique: JSH1ATewPmOR9i5Wag52aw-1
Received: from smtp.corp.redhat.com (int-mx06.intmail.prod.int.phx2.redhat.com
 [10.5.11.16])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 9266B802B67;
        Thu,  1 Oct 2020 13:05:45 +0000 (UTC)
Received: from vitty.brq.redhat.com (unknown [10.40.195.161])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 4E7295C1CF;
        Thu,  1 Oct 2020 13:05:43 +0000 (UTC)
From: Vitaly Kuznetsov <vkuznets@redhat.com>
To: kvm@vger.kernel.org, Paolo Bonzini <pbonzini@redhat.com>
Cc: Sean Christopherson <sean.j.christopherson@intel.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        "Dr . David Alan Gilbert" <dgilbert@redhat.com>,
        Wei Huang <whuang2@amd.com>, linux-kernel@vger.kernel.org
Subject: [PATCH 0/3] KVM: x86: allow for more CPUID entries
Date: Thu,  1 Oct 2020 15:05:38 +0200
Message-Id: <20201001130541.1398392-1-vkuznets@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.16
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Changes since RFC:
- "KVM: x86: disconnect kvm_check_cpuid() from vcpu->arch.cpuid_entries"
  added to allow running kvm_check_cpuid() before vcpu->arch.cpuid_entries/
  vcpu->arch.cpuid_nent are changed [Sean Christopherson]
- Shorten local variable names in kvm_vcpu_ioctl_set_cpuid[,2]
  [Sean Christopherson]
- Drop unneeded 'out' labels from kvm_vcpu_ioctl_set_cpuid[,2]
  and return directly whenever possible [Sean Christopherson]

Original description:

With QEMU and newer AMD CPUs (namely: Epyc 'Rome') the current limit for
KVM_MAX_CPUID_ENTRIES(80) is reported to be hit. Last time it was raised
from '40' in 2010. We can, of course, just bump it a little bit to fix
the immediate issue but the report made me wonder why we need to pre-
allocate vcpu->arch.cpuid_entries array instead of sizing it dynamically.
This RFC is intended to feed my curiosity.

Very mildly tested with selftests/kvm-unit-tests and nothing seems to
break. I also don't have access to the system where the original issue
was reported but chances we're fixing it are very good IMO as just the
second patch alone was reported to be sufficient.

Reported-by: Dr. David Alan Gilbert <dgilbert@redhat.com>

Vitaly Kuznetsov (3):
  KVM: x86: disconnect kvm_check_cpuid() from vcpu->arch.cpuid_entries
  KVM: x86: allocate vcpu->arch.cpuid_entries dynamically
  KVM: x86: bump KVM_MAX_CPUID_ENTRIES

 arch/x86/include/asm/kvm_host.h |   4 +-
 arch/x86/kvm/cpuid.c            | 123 +++++++++++++++++++-------------
 arch/x86/kvm/x86.c              |   1 +
 3 files changed, 75 insertions(+), 53 deletions(-)
```
