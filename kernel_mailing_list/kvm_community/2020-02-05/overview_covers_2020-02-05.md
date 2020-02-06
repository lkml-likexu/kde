

#### [PATCH v4 00/14] KVM: Dirty ring interface
##### From: Peter Xu <peterx@redhat.com>

```c
From patchwork Wed Feb  5 02:50:51 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Peter Xu <peterx@redhat.com>
X-Patchwork-Id: 11365687
Return-Path: <SRS0=nIH0=3Z=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 67397921
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed,  5 Feb 2020 02:51:30 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 3BE20217F4
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed,  5 Feb 2020 02:51:30 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="Fe4L0RQX"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727928AbgBECvS (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 4 Feb 2020 21:51:18 -0500
Received: from us-smtp-1.mimecast.com ([207.211.31.81]:49549 "EHLO
        us-smtp-delivery-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S1727885AbgBECvQ (ORCPT
        <rfc822;kvm@vger.kernel.org>); Tue, 4 Feb 2020 21:51:16 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1580871074;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=DKtUKnKq1J1pqiJ5NWomQSmReHrjvPI4rlRqnUPkaxE=;
        b=Fe4L0RQXCA7yfBVWJAZ3wJnSwA6XJsVBSF+5ep0Rn2Yp4rwtOMmjhQHIF3/AFk9M47YPsz
        cPp2IoxxyLAoNpjBjUJILMSO8EmBJf+pMr7sDuStyV5WRx/sLk2BbAG/Pe99Xxmdc3A53j
        ZgL/FJlGued1cI4omGFMyYT4s5vYwxo=
Received: from mail-qk1-f200.google.com (mail-qk1-f200.google.com
 [209.85.222.200]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-227-b3FkV3fGNKW79aQ5KdbnQg-1; Tue, 04 Feb 2020 21:51:10 -0500
X-MC-Unique: b3FkV3fGNKW79aQ5KdbnQg-1
Received: by mail-qk1-f200.google.com with SMTP id i11so391187qki.12
        for <kvm@vger.kernel.org>; Tue, 04 Feb 2020 18:51:10 -0800 (PST)
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:mime-version
         :content-transfer-encoding;
        bh=DKtUKnKq1J1pqiJ5NWomQSmReHrjvPI4rlRqnUPkaxE=;
        b=pFsJKRSPhM1ztgxAhH3MkBrizuhFo0MxlM/bwljg3qZTsjs5fZhHkhFdwHD329T6kY
         9qDwFwjFDDfmY+CIFITxhIJ8gYORhwmIOSQppbNFDVDhx9RawTlZRRCAM1KkLEVWbqn6
         ZvgMGkpm8x8yXtyMSH2ebjMSB8tymAWKD5SWp4B+jB7lNKvgD+jeEneaZeCBsvUUxisY
         Bi3ziIyllt9/InuGqJKvFRRw2HSA+eTGxj+pDMkz7EkHCojCvGPJurfntWIrcxXJwI02
         VM3p48tDGSvnMuW6T1xJF+ziEqXKHMe5ChbrXXihcfkFL5v3EtjMsdlyHHGPPc9uH5FU
         rrqw==
X-Gm-Message-State: APjAAAXVSLjWVyBGXENPdGJtWJQpIzcsuYaEJnt2KRnKHeAdSGTtjMHI
        LdFigxlC9b64DtK+oqjz1IMK6aLMTjBIUBO+cegR4bFoBwSQxpyecKCdfp6D2W4/BIhHu9pcl4m
        1NnncBGYipkCd
X-Received: by 2002:a0c:f24a:: with SMTP id z10mr30929679qvl.33.1580871069826;
        Tue, 04 Feb 2020 18:51:09 -0800 (PST)
X-Google-Smtp-Source: 
 APXvYqx4Rzc4aPHLj7hhqYA+ZxPSLB6YJX/04N/lV5KKFxqu0yKbFNNIn/r3iiLYD2cYqAqGTafHFQ==
X-Received: by 2002:a0c:f24a:: with SMTP id z10mr30929647qvl.33.1580871069426;
        Tue, 04 Feb 2020 18:51:09 -0800 (PST)
Received: from xz-x1.redhat.com ([2607:9880:19c8:32::2])
        by smtp.gmail.com with ESMTPSA id
 b141sm12380923qkg.33.2020.02.04.18.51.06
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Tue, 04 Feb 2020 18:51:08 -0800 (PST)
From: Peter Xu <peterx@redhat.com>
To: kvm@vger.kernel.org, linux-kernel@vger.kernel.org
Cc: Christophe de Dinechin <dinechin@redhat.com>,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        Paolo Bonzini <pbonzini@redhat.com>,
        Jason Wang <jasowang@redhat.com>,
        Yan Zhao <yan.y.zhao@intel.com>,
        "Michael S . Tsirkin" <mst@redhat.com>, peterx@redhat.com,
        Kevin Tian <kevin.tian@intel.com>,
        Alex Williamson <alex.williamson@redhat.com>,
        "Dr . David Alan Gilbert" <dgilbert@redhat.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>
Subject: [PATCH v4 00/14] KVM: Dirty ring interface
Date: Tue,  4 Feb 2020 21:50:51 -0500
Message-Id: <20200205025105.367213-1-peterx@redhat.com>
X-Mailer: git-send-email 2.24.1
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

KVM branch:
  https://github.com/xzpeter/linux/tree/kvm-dirty-ring

QEMU branch for testing:
  https://github.com/xzpeter/qemu/tree/kvm-dirty-ring

v4 changelog:

- refactor ring layout: remove indices, use bit 0/1 in the gfn.flags
  field to encode GFN status (invalid, dirtied, collected) [Michael,
  Paolo]
- patch memslot_valid_for_gpte() too to check against memslot flags
  rather than dirty_bitmap pointer
- fix build on non-x86 arch [syzbot]
- fix comment for kvm_dirty_gfn [Michael]
- check against VM_EXEC, VM_SHARED for mmaps [Michael]
- fix "KVM: X86: Don't track dirty for
  KVM_SET_[TSS_ADDR|IDENTITY_MAP_ADDR]" to unbreak
  unrestricted_guest=N [Sean]
- some rework in the test code, e.g., more comments

For previous versions, please refer to:

V1: https://lore.kernel.org/kvm/20191129213505.18472-1-peterx@redhat.com
V2: https://lore.kernel.org/kvm/20191221014938.58831-1-peterx@redhat.com
V3: https://lore.kernel.org/kvm/20200109145729.32898-1-peterx@redhat.com

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

 Documentation/virt/kvm/api.txt                | 125 +++++
 arch/x86/include/asm/kvm_host.h               |   6 +-
 arch/x86/include/uapi/asm/kvm.h               |   1 +
 arch/x86/kvm/Makefile                         |   3 +-
 arch/x86/kvm/mmu/mmu.c                        |  10 +-
 arch/x86/kvm/mmutrace.h                       |   9 +-
 arch/x86/kvm/svm.c                            |   9 +-
 arch/x86/kvm/vmx/vmx.c                        |  85 ++--
 arch/x86/kvm/x86.c                            |  49 +-
 include/linux/kvm_dirty_ring.h                |  50 ++
 include/linux/kvm_host.h                      |  21 +
 include/trace/events/kvm.h                    |  78 ++++
 include/uapi/linux/kvm.h                      |  44 ++
 tools/include/uapi/linux/kvm.h                |  44 ++
 tools/testing/selftests/kvm/Makefile          |   2 -
 .../selftests/kvm/clear_dirty_log_test.c      |   2 -
 tools/testing/selftests/kvm/dirty_log_test.c  | 441 ++++++++++++++++--
 .../testing/selftests/kvm/include/kvm_util.h  |   4 +
 tools/testing/selftests/kvm/lib/kvm_util.c    |  76 +++
 .../selftests/kvm/lib/kvm_util_internal.h     |   4 +
 virt/kvm/dirty_ring.c                         | 176 +++++++
 virt/kvm/kvm_main.c                           | 225 ++++++++-
 22 files changed, 1347 insertions(+), 117 deletions(-)
 create mode 100644 include/linux/kvm_dirty_ring.h
 delete mode 100644 tools/testing/selftests/kvm/clear_dirty_log_test.c
 create mode 100644 virt/kvm/dirty_ring.c
```
#### [PATCH 0/3] x86/kvm/hyper-v: fix enlightened VMCS & QEMU4.2
##### From: Vitaly Kuznetsov <vkuznets@redhat.com>

```c
From patchwork Wed Feb  5 12:30:31 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Vitaly Kuznetsov <vkuznets@redhat.com>
X-Patchwork-Id: 11366235
Return-Path: <SRS0=nIH0=3Z=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 27845921
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed,  5 Feb 2020 12:30:58 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 0609A218AC
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed,  5 Feb 2020 12:30:58 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="BPC80VCM"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728018AbgBEMao (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 5 Feb 2020 07:30:44 -0500
Received: from us-smtp-delivery-1.mimecast.com ([207.211.31.120]:53418 "EHLO
        us-smtp-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org
        with ESMTP id S1727963AbgBEMan (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 5 Feb 2020 07:30:43 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1580905842;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=FZ3Fjj0BjzHheqix1bmWtGQyTCVbBm91zCQKiRJjeoc=;
        b=BPC80VCMg0sbdv86KZrDCm8HS8doLuNB3nmSjvc+qFAaU9+N6RIB0Ep3/FEu3AY8UKPniO
        QQonPk8pMm9zoY5S0AYIHHL6xQmp2XqBLlqJ/I0gOaCcQMgmk6X2P242nFHyyMhAmRV2HK
        nVxooeV/hU5u6eq10l5KOFodYyLG++Y=
Received: from mail-wm1-f72.google.com (mail-wm1-f72.google.com
 [209.85.128.72]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-273-XinBh8uIM7qBiEPxQGmciw-1; Wed, 05 Feb 2020 07:30:38 -0500
X-MC-Unique: XinBh8uIM7qBiEPxQGmciw-1
Received: by mail-wm1-f72.google.com with SMTP id o193so923474wme.8
        for <kvm@vger.kernel.org>; Wed, 05 Feb 2020 04:30:38 -0800 (PST)
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:mime-version
         :content-transfer-encoding;
        bh=FZ3Fjj0BjzHheqix1bmWtGQyTCVbBm91zCQKiRJjeoc=;
        b=nlbrhc/Q0h4xLBFd7B6CSD0zqFJySBdH1JlBOauAceiyZka7+iLfIrdm59PyhBOUfw
         jq5nS1YimO5ssHdd0PzDysKHBLeUm0W4l0Z3NUCjcAo8EYcq7Pfkj35jIaszno2iKV3A
         xcWN5BLnmC4qW+AsO6wjuiGKgcCgp/7RBXVG8qgppsRI6JA467M9OQ+Y2KP6RmvzBLk0
         yenzLDkVdEw2eX5nUDpNQCY0XhSulM7PuyG48FioWGCsx3qHPHqXmTUR04QZp0P7Mv8g
         HRa+19ey/OqRmkvKvhFYiX1vx0DdEAXkblN4ulwpSXlYDA2oNz9cre76Qw5o1Y41MPv4
         TE8w==
X-Gm-Message-State: APjAAAWbu784A9NHpgzCcRiTHPwzXFkcoNW//jj9GWQeTR3C02pkxk4a
        9iFqkl4DZZd0I52/wpy+85NQM9kfA2N0RdwY8Mrus8hUWM7OHkjetmOzUvFlskyTQ9LWnUdMwPU
        Aa5ovtW9Sj0KG
X-Received: by 2002:a5d:6802:: with SMTP id w2mr27773562wru.353.1580905837104;
        Wed, 05 Feb 2020 04:30:37 -0800 (PST)
X-Google-Smtp-Source: 
 APXvYqy6xei4lJJtlxIHzm0eIiTXbZ2RJ6mzDj5iTZMvHZSp+m6YI7Hhbrz63uThgLSRStvcrZPzPw==
X-Received: by 2002:a5d:6802:: with SMTP id w2mr27773549wru.353.1580905836907;
        Wed, 05 Feb 2020 04:30:36 -0800 (PST)
Received: from vitty.brq.redhat.com (nat-pool-brq-t.redhat.com.
 [213.175.37.10])
        by smtp.gmail.com with ESMTPSA id
 g7sm34227251wrq.21.2020.02.05.04.30.35
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Wed, 05 Feb 2020 04:30:36 -0800 (PST)
From: Vitaly Kuznetsov <vkuznets@redhat.com>
To: kvm@vger.kernel.org
Cc: Paolo Bonzini <pbonzini@redhat.com>,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        Jim Mattson <jmattson@google.com>,
        linux-kernel@vger.kernel.org, Liran Alon <liran.alon@oracle.com>,
        Roman Kagan <rkagan@virtuozzo.com>
Subject: [PATCH 0/3] x86/kvm/hyper-v: fix enlightened VMCS & QEMU4.2
Date: Wed,  5 Feb 2020 13:30:31 +0100
Message-Id: <20200205123034.630229-1-vkuznets@redhat.com>
X-Mailer: git-send-email 2.24.1
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

With fine grained VMX feature enablement QEMU>=4.2 tries to do KVM_SET_MSRS
with default (matching CPU model) values and in case eVMCS is also enabled,
fails. While the regression is in QEMU, it may still be preferable to
fix this in KVM.

It would be great if we could just omit the VMX feature filtering in KVM
and make this guest's responsibility: if it switches to using enlightened
vmcs it should be aware that not all hardware features are going to be
supported. Genuine Hyper-V, however, fails the test. It, for example,
enables SECONDARY_EXEC_VIRTUALIZE_APIC_ACCESSES and without
'apic_access_addr' field in eVMCS there's not much we can do in KVM.
Microsoft confirms the bug but it is unclear if it will ever get fixed
in the existing Hyper-V versions as genuine Hyper-V never exposes
these unsupported controls to L1.

Changes since 'RFC':
- Go with the bare minimum [Paolo]

KVM RFC:
https://lore.kernel.org/kvm/20200115171014.56405-1-vkuznets@redhat.com/

QEMU RFC@:
https://lists.nongnu.org/archive/html/qemu-devel/2020-01/msg00123.html

Vitaly Kuznetsov (3):
  x86/kvm/hyper-v: remove stale evmcs_already_enabled check from
    nested_enable_evmcs()
  x86/kvm/hyper-v: move VMX controls sanitization out of
    nested_enable_evmcs()
  x86/kvm/hyper-v: don't allow to turn on unsupported VMX controls for
    nested guests

 arch/x86/kvm/vmx/evmcs.c  | 90 ++++++++++++++++++++++++++++++++++-----
 arch/x86/kvm/vmx/evmcs.h  |  3 ++
 arch/x86/kvm/vmx/nested.c |  3 ++
 arch/x86/kvm/vmx/vmx.c    | 16 ++++++-
 4 files changed, 99 insertions(+), 13 deletions(-)
```
