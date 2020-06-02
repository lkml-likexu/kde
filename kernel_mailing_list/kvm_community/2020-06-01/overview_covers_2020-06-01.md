

#### [PATCH v2 0/2] vhost, docs: convert to pin_user_pages(), new "case 5"
##### From: John Hubbard <jhubbard@nvidia.com>

```c
From patchwork Mon Jun  1 05:26:31 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: John Hubbard <jhubbard@nvidia.com>
X-Patchwork-Id: 11581271
Return-Path: <SRS0=ZHpL=7O=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id CA4A11391
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon,  1 Jun 2020 05:27:01 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id AA6CA2076B
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon,  1 Jun 2020 05:27:01 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=nvidia.com header.i=@nvidia.com
 header.b="njQ2XrKf"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726022AbgFAF0j (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 1 Jun 2020 01:26:39 -0400
Received: from hqnvemgate26.nvidia.com ([216.228.121.65]:19602 "EHLO
        hqnvemgate26.nvidia.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1725283AbgFAF0i (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 1 Jun 2020 01:26:38 -0400
Received: from hqpgpgate101.nvidia.com (Not Verified[216.228.121.13]) by
 hqnvemgate26.nvidia.com (using TLS: TLSv1.2, DES-CBC3-SHA)
        id <B5ed491820001>; Sun, 31 May 2020 22:26:26 -0700
Received: from hqmail.nvidia.com ([172.20.161.6])
  by hqpgpgate101.nvidia.com (PGP Universal service);
  Sun, 31 May 2020 22:26:38 -0700
X-PGP-Universal: processed;
        by hqpgpgate101.nvidia.com on Sun, 31 May 2020 22:26:38 -0700
Received: from HQMAIL109.nvidia.com (172.20.187.15) by HQMAIL107.nvidia.com
 (172.20.187.13) with Microsoft SMTP Server (TLS) id 15.0.1473.3; Mon, 1 Jun
 2020 05:26:38 +0000
Received: from rnnvemgw01.nvidia.com (10.128.109.123) by HQMAIL109.nvidia.com
 (172.20.187.15) with Microsoft SMTP Server (TLS) id 15.0.1473.3 via Frontend
 Transport; Mon, 1 Jun 2020 05:26:37 +0000
Received: from sandstorm.nvidia.com (Not Verified[10.2.56.10]) by
 rnnvemgw01.nvidia.com with Trustwave SEG (v7,5,8,10121)
        id <B5ed4918c0004>; Sun, 31 May 2020 22:26:37 -0700
From: John Hubbard <jhubbard@nvidia.com>
To: Andrew Morton <akpm@linux-foundation.org>
CC: "Michael S . Tsirkin" <mst@redhat.com>, Jason Wang <jasowang@redhat.com>,
 Vlastimil Babka <vbabka@suse.cz>,
 =?utf-8?b?SsOpcsO0bWUgR2xpc3Nl?= <jglisse@redhat.com>,
 Jan Kara <jack@suse.cz>, Dave Chinner <david@fromorbit.com>,
 Souptick Joarder <jrdr.linux@gmail.com>, Jonathan Corbet <corbet@lwn.net>,
 <linux-doc@vger.kernel.org>, <linux-fsdevel@vger.kernel.org>,
 <kvm@vger.kernel.org>, <virtualization@lists.linux-foundation.org>,
 <netdev@vger.kernel.org>, LKML <linux-kernel@vger.kernel.org>,
 <linux-mm@kvack.org>, John Hubbard <jhubbard@nvidia.com>
Subject: [PATCH v2 0/2] vhost, docs: convert to pin_user_pages(), new "case 5"
Date: Sun, 31 May 2020 22:26:31 -0700
Message-ID: <20200601052633.853874-1-jhubbard@nvidia.com>
X-Mailer: git-send-email 2.26.2
MIME-Version: 1.0
X-NVConfidentiality: public
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=nvidia.com; s=n1;
        t=1590989186; bh=oWhDekDqxx6fP3u/Pk90DFNTa0Jiv5OSfwybT44Pq1M=;
        h=X-PGP-Universal:From:To:CC:Subject:Date:Message-ID:X-Mailer:
         MIME-Version:X-NVConfidentiality:Content-Type:
         Content-Transfer-Encoding;
        b=njQ2XrKfA5W2d6S2irff3GXFlkhESnmMzdRVd0Q/6B60AxagwtZSbLa4o+uUZPcEC
         U9b4toQeqtCH2JLxeEdlYli0rRsWaLGGgu7lNzOE4A3V9yIjpiUmL++Z39WzDX8gm2
         Y+SEzR/8oWDaFDEpzI6OOPvRCeV1MdbdreDatwd//9coer0YaPfJARKz6KpKuJNuki
         i9df1soJa3Ku0wAC2kh8rE6HVP5UIGoO2FLioKhbkYmm1zpPOCFOrf+L8Fzx/m1u67
         U87MTtgDiMhF3FWGCf9o8p0f0Fzq6zhQsQoCWpyZ5HjHySh/7RDgDY46C0swvVZLfy
         +vVIjKS1sWtVQ==
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This is based on Linux 5.7, plus one prerequisite patch:
   "mm/gup: update pin_user_pages.rst for "case 3" (mmu notifiers)" [1]

Changes since v1: removed references to set_page_dirty*(), in response to
Souptick Joarder's review (thanks!).

Cover letter for v1, edited/updated slightly:

It recently became clear to me that there are some get_user_pages*()
callers that don't fit neatly into any of the four cases that are so
far listed in pin_user_pages.rst. vhost.c is one of those.

Add a Case 5 to the documentation, and refer to that when converting
vhost.c.

Thanks to Jan Kara for helping me (again) in understanding the
interaction between get_user_pages() and page writeback [2].

Note that I have only compile-tested the vhost.c patch, although that
does also include cross-compiling for a few other arches. Any run-time
testing would be greatly appreciated.

[1] https://lore.kernel.org/r/20200527194953.11130-1-jhubbard@nvidia.com
[2] https://lore.kernel.org/r/20200529070343.GL14550@quack2.suse.cz

John Hubbard (2):
  docs: mm/gup: pin_user_pages.rst: add a "case 5"
  vhost: convert get_user_pages() --> pin_user_pages()

 Documentation/core-api/pin_user_pages.rst | 18 ++++++++++++++++++
 drivers/vhost/vhost.c                     |  5 ++---
 2 files changed, 20 insertions(+), 3 deletions(-)


base-commit: 3d77e6a8804abcc0504c904bd6e5cdf3a5cf8162
```
#### [PATCH v10 00/14] KVM: Dirty ring interface
##### From: Peter Xu <peterx@redhat.com>

```c
From patchwork Mon Jun  1 11:59:43 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Peter Xu <peterx@redhat.com>
X-Patchwork-Id: 11581905
Return-Path: <SRS0=ZHpL=7O=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 0AAED139A
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon,  1 Jun 2020 12:00:12 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id DB8D52074B
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon,  1 Jun 2020 12:00:11 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="MZnEoCNc"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726218AbgFAMAK (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 1 Jun 2020 08:00:10 -0400
Received: from us-smtp-1.mimecast.com ([207.211.31.81]:50634 "EHLO
        us-smtp-delivery-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S1726017AbgFAMAJ (ORCPT
        <rfc822;kvm@vger.kernel.org>); Mon, 1 Jun 2020 08:00:09 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1591012807;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=b4s9WcgqlVxtr+9EizXh9/KmNnkbCqzI2Fd20X5rtec=;
        b=MZnEoCNcj00RUy0ZtGc5IXM4mMOVAF8JVWPoc/2yAeDrcxtkh9l9ZTq5r7/VCXklpGL9qq
        DaULUnGt+7SW6yeWIQsHtkJlpq6rlp5Ted9U7uKOlnsbcUQgiHW+ryUofJVShNZt4BDIQY
        gH2APV529wIyt8pMWj8Sh4lmGJppmpE=
Received: from mail-qk1-f200.google.com (mail-qk1-f200.google.com
 [209.85.222.200]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-195-GIPqQqtwMKi0jO-5o4n-lw-1; Mon, 01 Jun 2020 08:00:02 -0400
X-MC-Unique: GIPqQqtwMKi0jO-5o4n-lw-1
Received: by mail-qk1-f200.google.com with SMTP id c197so3899448qke.10
        for <kvm@vger.kernel.org>; Mon, 01 Jun 2020 05:00:02 -0700 (PDT)
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:mime-version
         :content-transfer-encoding;
        bh=b4s9WcgqlVxtr+9EizXh9/KmNnkbCqzI2Fd20X5rtec=;
        b=P5MmqHTo+z0ikIC/dl5d9mmh8Pk5P5CWZRJ/WJ5fcMXammN/y2YZyDW15NSagc8/1l
         1UXSXqm2itKXirSG6TSaJEpJavJJTS12+oORp1m2lsOPecPS7YJ9bn7bUVjbhpGCIahA
         AYufIz+IgiHzzK+LElNtJQYQNkr5PQxRAhutYCBfCkdrmxXnNFdmV+ftaeQGZHng1z4p
         tVTOt5OwTi9uf6e2F7X/lDRDd8tGl/I6tFpLUDhGNkqvf8G5P8kmd0qFz1Zq/ma7BjOp
         OQwquXLpC1mCbLGGWYOlfTWAUt1srXWMhhIfErRUq06YIdInarh2mKSIbmjzhrqTsw77
         B1HQ==
X-Gm-Message-State: AOAM5336rsxd+Z++yNuvkjJ0YapWvOJSa2d68UU2zRuz6/7A3zIPXKyW
        Z0iF8QBK5ojuPjuHp2VX1rBhm7y2CbqVix6vm8JMG6iPUSWzn4Uayr4cPm2n3RB3pQYliGiLBKC
        HU7tSnGqE5MRf
X-Received: by 2002:a0c:83a6:: with SMTP id
 k35mr20592083qva.251.1591012801709;
        Mon, 01 Jun 2020 05:00:01 -0700 (PDT)
X-Google-Smtp-Source: 
 ABdhPJxYHGa+3xkcUnrLNND3SShHOHA9YhMl/arSqtVWMF5nPsi24AE2ZzB/PLX4748dqxh9lXeNdg==
X-Received: by 2002:a0c:83a6:: with SMTP id
 k35mr20592052qva.251.1591012801332;
        Mon, 01 Jun 2020 05:00:01 -0700 (PDT)
Received: from xz-x1.redhat.com ([2607:9880:19c0:32::2])
        by smtp.gmail.com with ESMTPSA id
 l9sm14474185qki.90.2020.06.01.04.59.58
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Mon, 01 Jun 2020 05:00:00 -0700 (PDT)
From: Peter Xu <peterx@redhat.com>
To: kvm@vger.kernel.org, linux-kernel@vger.kernel.org
Cc: "Dr . David Alan Gilbert" <dgilbert@redhat.com>,
        Andrew Jones <drjones@redhat.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Paolo Bonzini <pbonzini@redhat.com>,
        "Michael S . Tsirkin" <mst@redhat.com>,
        Jason Wang <jasowang@redhat.com>, peterx@redhat.com,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        Kevin Tian <kevin.tian@intel.com>
Subject: [PATCH v10 00/14] KVM: Dirty ring interface
Date: Mon,  1 Jun 2020 07:59:43 -0400
Message-Id: <20200601115957.1581250-1-peterx@redhat.com>
X-Mailer: git-send-email 2.26.2
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

KVM branch:
  https://github.com/xzpeter/linux/tree/kvm-dirty-ring

QEMU branch for testing:
  https://github.com/xzpeter/qemu/tree/kvm-dirty-ring

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

v8:
- rebase to kvm/next
- fix test bisection issues [Drew]
- reword comment for __x86_set_memory_region [Sean]
- document fixup on "mutual exclusive", etc. [Sean]

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
  KVM: X86: Change parameter for fast_page_fault tracepoint
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

 Documentation/virt/kvm/api.rst                | 123 +++++
 arch/x86/include/asm/kvm_host.h               |   6 +-
 arch/x86/include/uapi/asm/kvm.h               |   1 +
 arch/x86/kvm/Makefile                         |   3 +-
 arch/x86/kvm/mmu/mmu.c                        |  10 +-
 arch/x86/kvm/mmutrace.h                       |   9 +-
 arch/x86/kvm/svm/avic.c                       |  11 +-
 arch/x86/kvm/vmx/vmx.c                        |  92 ++--
 arch/x86/kvm/x86.c                            |  53 +-
 include/linux/kvm_dirty_ring.h                | 103 ++++
 include/linux/kvm_host.h                      |  19 +
 include/trace/events/kvm.h                    |  78 +++
 include/uapi/linux/kvm.h                      |  53 ++
 tools/include/uapi/linux/kvm.h                |  53 ++
 tools/testing/selftests/kvm/Makefile          |   2 -
 .../selftests/kvm/clear_dirty_log_test.c      |   6 -
 tools/testing/selftests/kvm/dirty_log_test.c  | 505 ++++++++++++++++--
 .../testing/selftests/kvm/include/kvm_util.h  |   4 +
 tools/testing/selftests/kvm/lib/kvm_util.c    |  68 +++
 .../selftests/kvm/lib/kvm_util_internal.h     |   4 +
 virt/kvm/dirty_ring.c                         | 197 +++++++
 virt/kvm/kvm_main.c                           | 163 +++++-
 22 files changed, 1423 insertions(+), 140 deletions(-)
 create mode 100644 include/linux/kvm_dirty_ring.h
 delete mode 100644 tools/testing/selftests/kvm/clear_dirty_log_test.c
 create mode 100644 virt/kvm/dirty_ring.c
```
#### [PATCH v3 0/4] Add logical CPU to KVM_EXIT_FAIL_ENTRY info
##### From: Jim Mattson <jmattson@google.com>

```c
From patchwork Mon Jun  1 22:24:12 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Jim Mattson <jmattson@google.com>
X-Patchwork-Id: 11582763
Return-Path: <SRS0=ZHpL=7O=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id D24C1912
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon,  1 Jun 2020 22:24:23 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id BB31F2068D
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon,  1 Jun 2020 22:24:23 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=google.com header.i=@google.com
 header.b="Pt/xGBDn"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728428AbgFAWYW (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 1 Jun 2020 18:24:22 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:50712 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1728216AbgFAWYW (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 1 Jun 2020 18:24:22 -0400
Received: from mail-yb1-xb4a.google.com (mail-yb1-xb4a.google.com
 [IPv6:2607:f8b0:4864:20::b4a])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id C25F6C061A0E
        for <kvm@vger.kernel.org>; Mon,  1 Jun 2020 15:24:21 -0700 (PDT)
Received: by mail-yb1-xb4a.google.com with SMTP id e192so12762554ybf.17
        for <kvm@vger.kernel.org>; Mon, 01 Jun 2020 15:24:21 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=date:message-id:mime-version:subject:from:to:cc;
        bh=Ye6V+VSMQvB/FIQh5FZ01Cn8NyhcIOXA1Edk2Rr6mbY=;
        b=Pt/xGBDn0hxL0F+ixV9e9vHUk+xSRevJbeOVlvessSErPIQJrU3aGGITJYzkck0l42
         uS3HfpvPCSMSUo8yl5RH9QYzED8SFerWM0RqnVqcKgbruuSLtczcgL97i9ihcMEVZ4CG
         1aYbrkwXzB5sx4sVOucRg065kbLJ5WvqJ3a7DTC2r1Szrr0EhNDLnWgDo5fBb0AdyEsw
         XytNQ90mN8LFlXq2bpwdIlszr4MQS1GrN/vj4N0glkOpu9maHpOB4i6XFyJcIxLRlbR6
         XaVqwgxvgMm16Fqji1pOrEyWaJ7ql9GR0gVz+Var+CLqef9L3/ICy9hB5kFZaDE2DxmV
         PfZA==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:date:message-id:mime-version:subject:from:to:cc;
        bh=Ye6V+VSMQvB/FIQh5FZ01Cn8NyhcIOXA1Edk2Rr6mbY=;
        b=hHdbLCOZai6g9RPvic3h90qeP4BIt3m2xKBWvE/alBP5nUE3532pAcB3ta/fBmenbn
         KhjVHoDv7y3e+SgY3/jYr5r0avNdtkhPwklrijiJh5QpXvQ4cmQCgz8nzQgfXyVgoFti
         WOrcy8uqeIwhARh11l3C8Qhi9lR8gNoMveksfYaCMGGIG3UlCrP7tgMpUEduFYfzrMaT
         y/W3pQbgc5pemv2jINhuBpCUnXQGkkhg9UR4gJCe4Y+2B1z0yeh71eFUNrUOuJRXHF2j
         GGo2PjOUf8tSiZHI6tSAUSEO5zoIOWlCCRKV9OmS4zELIYwGqgDDmb0m61TrvbAGkjAi
         TRMA==
X-Gm-Message-State: AOAM530DPiwQR9aucaYvwy1BDqIsQe/+y8b1stLAmNkHq66Qh1VSHoHl
        XKiTOfagkmbeftlJt0ZJOdqBL9NSdmQDsr9hJ5pk9EIYZo5kFzXiPOOpYsyk3fbTeK9sRDrejTp
        5AcYMUYV9q0eSpOF5ANod8CvCljRSpO4ocRoEtDhwNXjFyaxT/vB3JOmkl+LEIig=
X-Google-Smtp-Source: 
 ABdhPJx5P1exhMFaoXrN/utbnODDyX3+7HjSG5R4PS9kA/jvoPQTYI89wGznPer/ds4Hhf/p+H08XJtVA2NJpQ==
X-Received: by 2002:a25:eb05:: with SMTP id d5mr16241511ybs.12.1591050260926;
 Mon, 01 Jun 2020 15:24:20 -0700 (PDT)
Date: Mon,  1 Jun 2020 15:24:12 -0700
Message-Id: <20200601222416.71303-1-jmattson@google.com>
Mime-Version: 1.0
X-Mailer: git-send-email 2.27.0.rc2.251.g90737beb825-goog
Subject: [PATCH v3 0/4] Add logical CPU to KVM_EXIT_FAIL_ENTRY info
From: Jim Mattson <jmattson@google.com>
To: kvm@vger.kernel.org, Paolo Bonzini <pbonzini@redhat.com>
Cc: Liran Alon <liran.alon@oracle.com>,
        Oliver Upton <oupton@google.com>,
        Peter Shier <pshier@google.com>,
        Jim Mattson <jmattson@google.com>
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

It's been about 6 months since v2. Sorry for the delay. Initially, this
was a single patch to add information to KVM_EXIT_FAIL_ENTRY to help
identify a defective CPU. It has gotten a little more complicated,
since Peter Shier pointed out that the vCPU thread may have migrated
between the time of failure and the KVM exit. Fortunately, the SEV folks
started to make the necessary information available with "last_cpu," but
only on AMD and only with SEV. The current version expands upon that by
making "last_cpu" available in all configurations on AMD and Intel.

v2: Use vcpu->cpu rather than raw_smp_processor_id() (Liran).
v3: Record the last logical processor to run the vCPU thread (Peter).
    Add the "last CPU" information to KVM_EXIT_INTERNAL_ERROR exits as
    well as KVM_EXIT_FAIL_ENTRY [except for "EMULATION" errors].
    (Liran & Paolo).

Jim Mattson (4):
  kvm: svm: Prefer vcpu->cpu to raw_smp_processor_id()
  kvm: svm: Always set svm->last_cpu on VMRUN
  kvm: vmx: Add last_cpu to struct vcpu_vmx
  kvm: x86: Add "last CPU" to some KVM_EXIT information

 Documentation/virt/kvm/api.rst |  1 +
 arch/x86/kvm/svm/sev.c         |  1 -
 arch/x86/kvm/svm/svm.c         | 14 +++++++-------
 arch/x86/kvm/vmx/vmx.c         | 11 +++++++++--
 arch/x86/kvm/vmx/vmx.h         |  3 +++
 arch/x86/kvm/x86.c             |  1 +
 include/uapi/linux/kvm.h       |  2 ++
 7 files changed, 23 insertions(+), 10 deletions(-)
```
