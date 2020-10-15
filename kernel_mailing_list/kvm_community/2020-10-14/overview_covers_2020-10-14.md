

#### [RFC v2 0/7] KVM: PKS Virtualization support
##### From: Chenyi Qiang <chenyi.qiang@intel.com>

```c
From patchwork Wed Oct 14 02:11:49 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Chenyi Qiang <chenyi.qiang@intel.com>
X-Patchwork-Id: 11836633
Return-Path: <SRS0=7LGy=DV=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id B20C814B2
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 14 Oct 2020 02:09:55 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id A2034221FF
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 14 Oct 2020 02:09:55 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728262AbgJNCJr (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 13 Oct 2020 22:09:47 -0400
Received: from mga06.intel.com ([134.134.136.31]:51139 "EHLO mga06.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1725874AbgJNCJq (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 13 Oct 2020 22:09:46 -0400
IronPort-SDR: 
 uvOTCWmGsaZRZSrvd/jgPNy5wbzXN9FFIdG5TEfp2HnIs1OqMxzJutocORXl1QFy0wLfA3WewE
 4r9yuOWB3chg==
X-IronPort-AV: E=McAfee;i="6000,8403,9773"; a="227659782"
X-IronPort-AV: E=Sophos;i="5.77,373,1596524400";
   d="scan'208";a="227659782"
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from orsmga005.jf.intel.com ([10.7.209.41])
  by orsmga104.jf.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 13 Oct 2020 19:09:44 -0700
IronPort-SDR: 
 zNuSmsQyZC58CaJVJlolLCkNbfiDEJ/GctdvvPxHCgsClkX2fjDCVYPdUe+Q+h5m8zRaehjRib
 0obiY4OxgG4Q==
X-IronPort-AV: E=Sophos;i="5.77,373,1596524400";
   d="scan'208";a="530645086"
Received: from chenyi-pc.sh.intel.com ([10.239.159.72])
  by orsmga005-auth.jf.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 13 Oct 2020 19:09:42 -0700
From: Chenyi Qiang <chenyi.qiang@intel.com>
To: Paolo Bonzini <pbonzini@redhat.com>,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>,
        Xiaoyao Li <xiaoyao.li@intel.com>
Cc: kvm@vger.kernel.org, linux-kernel@vger.kernel.org
Subject: [RFC v2 0/7] KVM: PKS Virtualization support
Date: Wed, 14 Oct 2020 10:11:49 +0800
Message-Id: <20201014021157.18022-1-chenyi.qiang@intel.com>
X-Mailer: git-send-email 2.17.1
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Protection Keys for Supervisor Pages(PKS) is a feature that extends the
Protection Keys architecture to support thread-specific permission
restrictions on supervisor pages.

PKS works similar to an existing feature named PKU(protecting user pages).
They both perform an additional check after all legacy access
permissions checks are done. If violated, #PF occurs and PFEC.PK bit will
be set. PKS introduces MSR IA32_PKRS to manage supervisor protection key
rights. The MSR contains 16 pairs of ADi and WDi bits. Each pair
advertises on a group of pages with the same key which is set in the
leaf paging-structure entries(bits[62:59]). Currently, IA32_PKRS is not
supported by XSAVES architecture.

This patchset aims to add the virtualization of PKS in KVM. It
implemented PKS CPUID enumeration, vmentry/vmexit configuration, MSR
exposure, nested supported etc. Currently, PKS is not yet supported for
shadow paging. 

Detailed information about PKS can be found in the latest Intel 64 and
IA-32 Architectures Software Developer's Manual.
---

Changelogs:

v1->v2:
- rebase on the latest PKS kernel support:
  https://github.com/weiny2/linux-kernel/tree/pks-rfc-v3
- add a kvm-unit-tests for PKS
- add the check in kvm_init_msr_list for PKRS
- place the X86_CR4_PKS in mmu_role_bits in kvm_set_cr4
- add the support to expose VM_{ENTRY, EXIT}_LOAD_IA32_PKRS in nested
  VMX MSR
- RFC v1: https://lore.kernel.org/lkml/20200807084841.7112-1-chenyi.qiang@intel.com/

---

Chenyi Qiang (7):
  KVM: VMX: Introduce PKS VMCS fields
  KVM: VMX: Expose IA32_PKRS MSR
  KVM: MMU: Rename the pkru to pkr
  KVM: MMU: Refactor pkr_mask to cache condition
  KVM: MMU: Add support for PKS emulation
  KVM: X86: Expose PKS to guest and userspace
  KVM: VMX: Enable PKS for nested VM

 arch/x86/include/asm/kvm_host.h | 13 ++---
 arch/x86/include/asm/pkeys.h    |  1 +
 arch/x86/include/asm/vmx.h      |  6 +++
 arch/x86/kvm/cpuid.c            |  3 +-
 arch/x86/kvm/mmu.h              | 36 +++++++------
 arch/x86/kvm/mmu/mmu.c          | 78 +++++++++++++++-------------
 arch/x86/kvm/vmx/capabilities.h |  6 +++
 arch/x86/kvm/vmx/nested.c       | 38 +++++++++++++-
 arch/x86/kvm/vmx/vmcs.h         |  1 +
 arch/x86/kvm/vmx/vmcs12.c       |  2 +
 arch/x86/kvm/vmx/vmcs12.h       |  6 ++-
 arch/x86/kvm/vmx/vmx.c          | 91 +++++++++++++++++++++++++++++++--
 arch/x86/kvm/vmx/vmx.h          |  1 +
 arch/x86/kvm/x86.c              |  9 +++-
 arch/x86/kvm/x86.h              |  6 +++
 arch/x86/mm/pkeys.c             |  6 +++
 include/linux/pkeys.h           |  4 ++
 17 files changed, 239 insertions(+), 68 deletions(-)
```
#### [PATCH v2 00/20] Introduce the TDP MMU
##### From: Ben Gardon <bgardon@google.com>

```c
From patchwork Wed Oct 14 18:26:40 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Ben Gardon <bgardon@google.com>
X-Patchwork-Id: 11838125
Return-Path: <SRS0=7LGy=DV=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id B700314B2
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 14 Oct 2020 18:27:08 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 823482222C
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 14 Oct 2020 18:27:08 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=google.com header.i=@google.com
 header.b="lItDRVd5"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729837AbgJNS1F (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 14 Oct 2020 14:27:05 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:40032 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726830AbgJNS1E (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 14 Oct 2020 14:27:04 -0400
Received: from mail-pj1-x1049.google.com (mail-pj1-x1049.google.com
 [IPv6:2607:f8b0:4864:20::1049])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id BC5EBC061755
        for <kvm@vger.kernel.org>; Wed, 14 Oct 2020 11:27:04 -0700 (PDT)
Received: by mail-pj1-x1049.google.com with SMTP id y6so328719pjb.8
        for <kvm@vger.kernel.org>; Wed, 14 Oct 2020 11:27:04 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=sender:date:message-id:mime-version:subject:from:to:cc;
        bh=3OwPD9JNIkkg/66kUX7JOx+qvCAxBgpPWoZ4pxvez7k=;
        b=lItDRVd5cQ5IIEtTz6X1ie5+pL9ESgJLgeZyxVtNXHGYlK7jQeI+WmWLEJiItBVt9N
         mOQC3YlpDvNZHCAheoHcba6Kj7h8mRdkiUiJ5rNgUZyc41UW5Utx9JrRWD5nyrKNEJec
         FDXTijiSEuxPs1dpq2ousd0PkiGkEv0bHpdFtGA8djfZf+P33qiCVg+opBpIWsZuFCe3
         pudFBc1uJgz0sMppEWU/MxRLBbGS85adq9t7IhvNqRfmF2GRO1yLMHvdo7O3TO9T11HI
         Hr6NeNuBQAkEQPoJjqEB0E6XOWviYqGEJ3+qF+aWs7QQzDUGy/eM5luXM/yvekuAZds7
         NSOw==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:sender:date:message-id:mime-version:subject:from
         :to:cc;
        bh=3OwPD9JNIkkg/66kUX7JOx+qvCAxBgpPWoZ4pxvez7k=;
        b=YtYQgdsUvjts8NEjyW5eHWgeK751IPgyV9kus2fyUQPk2z9WFjroUAojAw+yhIUXdr
         RkZ/z6WfgDa5FvvvIqStsv7zJJ5OyjIxxHLYHBqu7xvS61XlC+rXj3w1rDXpfG/1e1qE
         BbaQnWYSOabLU7QuEuItGuVaChXGQ0TgkIptQKoiFWdftXh+YBSizquxTvMuLSAVVQ9O
         YKz8JmtrNxlWmtdhKoa7iRsARQ7Gn8BIhDQcYyffVVkoBXSyedts1YdAZlDPyDABxqq1
         lG6a/b+gQhj1iVtS4XGCjwrrL983V3Qw42iGx6KavPbcJ0SzNoQiBKHn758sVN22icGD
         nsCQ==
X-Gm-Message-State: AOAM533gGCMNVwveT/o5s8lA3LD5jfbieJCjc9EZeD75/zbm2mn56OXJ
        fp5w3z1qdO1ydSc3TQkFODlOAR5MSYF/
X-Google-Smtp-Source: 
 ABdhPJzmbjkLfxHv5DXV8PVqejr9VdMMeI+pdHIWv34F78h8VYGL0lGuDne+ScNCejcY+JQlskkT9jQRTEM2
Sender: "bgardon via sendgmr" <bgardon@bgardon.sea.corp.google.com>
X-Received: from bgardon.sea.corp.google.com
 ([2620:15c:100:202:f693:9fff:fef4:a293])
 (user=bgardon job=sendgmr) by 2002:aa7:8421:0:b029:155:3229:69cc with SMTP id
 q1-20020aa784210000b0290155322969ccmr567588pfn.36.1602700024177; Wed, 14 Oct
 2020 11:27:04 -0700 (PDT)
Date: Wed, 14 Oct 2020 11:26:40 -0700
Message-Id: <20201014182700.2888246-1-bgardon@google.com>
Mime-Version: 1.0
X-Mailer: git-send-email 2.28.0.1011.ga647a8990f-goog
Subject: [PATCH v2 00/20] Introduce the TDP MMU
From: Ben Gardon <bgardon@google.com>
To: linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Cc: Cannon Matthews <cannonmatthews@google.com>,
        Paolo Bonzini <pbonzini@redhat.com>,
        Peter Xu <peterx@redhat.com>,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        Peter Shier <pshier@google.com>,
        Peter Feiner <pfeiner@google.com>,
        Junaid Shahid <junaids@google.com>,
        Jim Mattson <jmattson@google.com>,
        Yulei Zhang <yulei.kernel@gmail.com>,
        Wanpeng Li <kernellwp@gmail.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Xiao Guangrong <xiaoguangrong.eric@gmail.com>,
        Ben Gardon <bgardon@google.com>
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Over the years, the needs for KVM's x86 MMU have grown from running small
guests to live migrating multi-terabyte VMs with hundreds of vCPUs. Where
we previously depended on shadow paging to run all guests, we now have
two dimensional paging (TDP). This patch set introduces a new
implementation of much of the KVM MMU, optimized for running guests with
TDP. We have re-implemented many of the MMU functions to take advantage of
the relative simplicity of TDP and eliminate the need for an rmap.
Building on this simplified implementation, a future patch set will change
the synchronization model for this "TDP MMU" to enable more parallelism
than the monolithic MMU lock. A TDP MMU is currently in use at Google
and has given us the performance necessary to live migrate our 416 vCPU,
12TiB m2-ultramem-416 VMs.

This work was motivated by the need to handle page faults in parallel for
very large VMs. When VMs have hundreds of vCPUs and terabytes of memory,
KVM's MMU lock suffers extreme contention, resulting in soft-lockups and
long latency on guest page faults. This contention can be easily seen
running the KVM selftests demand_paging_test with a couple hundred vCPUs.
Over a 1 second profile of the demand_paging_test, with 416 vCPUs and 4G
per vCPU, 98% of the time was spent waiting for the MMU lock. At Google,
the TDP MMU reduced the test duration by 89% and the execution was
dominated by get_user_pages and the user fault FD ioctl instead of the
MMU lock.

This series is the first of two. In this series we add a basic
implementation of the TDP MMU. In the next series we will improve the
performance of the TDP MMU and allow it to execute MMU operations
in parallel.

The overall purpose of the KVM MMU is to program paging structures
(CR3/EPT/NPT) to encode the mapping of guest addresses to host physical
addresses (HPA), and to provide utilities for other KVM features, for
example dirty logging. The definition of the L1 guest physical address
(GPA) to HPA mapping comes in two parts: KVM's memslots map GPA to HVA,
and the kernel MM/x86 host page tables map HVA -> HPA. Without TDP, the
MMU must program the x86 page tables to encode the full translation of
guest virtual addresses (GVA) to HPA. This requires "shadowing" the
guest's page tables to create a composite x86 paging structure. This
solution is complicated, requires separate paging structures for each
guest CR3, and requires emulating guest page table changes. The TDP case
is much simpler. In this case, KVM lets the guest control CR3 and programs
the EPT/NPT paging structures with the GPA -> HPA mapping. The guest has
no way to change this mapping and only one version of the paging structure
is needed per L1 paging mode. In this case the paging mode is some
combination of the number of levels in the paging structure, the address
space (normal execution or system management mode, on x86), and other
attributes. Most VMs only ever use 1 paging mode and so only ever need one
TDP structure.

This series implements a "TDP MMU" through alternative implementations of
MMU functions for running L1 guests with TDP. The TDP MMU falls back to
the existing shadow paging implementation when TDP is not available, and
interoperates with the existing shadow paging implementation for nesting.
The use of the TDP MMU can be controlled by a module parameter which is
snapshot on VM creation and follows the life of the VM. This snapshot
is used in many functions to decide whether or not to use TDP MMU handlers
for a given operation.

This series can also be viewed in Gerrit here:
https://linux-review.googlesource.com/c/virt/kvm/kvm/+/2538
(Thanks to Dmitry Vyukov <dvyukov@google.com> for setting up the
Gerrit instance)

Changes v1 -> v2:
  Big thanks to Paolo and Sean for your thorough reviews!
  - Moved some function definitions to mmu_internal.h instead of just
    declaring them there.
  - Dropped the commit to add an as_id field to memslots in favor of
    Peter Xu's which is part of the dirty ring patch set. I've included a
    copy of that patch from v13 of the patch set in this series.
  - Fixed comment style on SPDX license headers
  - Added a min_level to the tdp_iter and removed the tdp_iter_no_step_down
    function
  - Removed the tdp_mmu module parameter and defaulted the global to false
  - Unified more NX reclaim code
  - Added helper functions for setting SPTEs in the TDP MMU
  - Renamed tdp_iter macros to for clarity
  - Renamed kvm_tdp_mmu_page_fault to kvm_tdp_mmu_map and gave it the same
    signature as __direct_map
  - Converted some WARN_ONs to BUG_ONs or removed them
  - Changed dlog to dirty_log to match convention
  - Switched make_spte to return a return code and use a return parameter
    for the new SPTE
  - Refactored TDP MMU root allocation
  - Other misc cleanups and bug fixes

Ben Gardon (19):
  kvm: x86/mmu: Separate making SPTEs from set_spte
  kvm: x86/mmu: Introduce tdp_iter
  kvm: x86/mmu: Init / Uninit the TDP MMU
  kvm: x86/mmu: Allocate and free TDP MMU roots
  kvm: x86/mmu: Add functions to handle changed TDP SPTEs
  kvm: x86/mmu: Support zapping SPTEs in the TDP MMU
  kvm: x86/mmu: Separate making non-leaf sptes from link_shadow_page
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

Peter Xu (1):
  KVM: Cache as_id in kvm_memory_slot

 arch/x86/include/asm/kvm_host.h |   14 +
 arch/x86/kvm/Makefile           |    3 +-
 arch/x86/kvm/mmu/mmu.c          |  487 +++++++------
 arch/x86/kvm/mmu/mmu_internal.h |  242 +++++++
 arch/x86/kvm/mmu/paging_tmpl.h  |    3 +-
 arch/x86/kvm/mmu/tdp_iter.c     |  181 +++++
 arch/x86/kvm/mmu/tdp_iter.h     |   60 ++
 arch/x86/kvm/mmu/tdp_mmu.c      | 1154 +++++++++++++++++++++++++++++++
 arch/x86/kvm/mmu/tdp_mmu.h      |   48 ++
 include/linux/kvm_host.h        |    2 +
 virt/kvm/kvm_main.c             |   12 +-
 11 files changed, 1944 insertions(+), 262 deletions(-)
 create mode 100644 arch/x86/kvm/mmu/tdp_iter.c
 create mode 100644 arch/x86/kvm/mmu/tdp_iter.h
 create mode 100644 arch/x86/kvm/mmu/tdp_mmu.c
 create mode 100644 arch/x86/kvm/mmu/tdp_mmu.h
```
#### [PATCH kvm-unit-tests 0/3] A few miscellaneous fixes
##### From: Andrew Jones <drjones@redhat.com>

```c
From patchwork Wed Oct 14 19:14:41 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Andrew Jones <drjones@redhat.com>
X-Patchwork-Id: 11838197
Return-Path: <SRS0=7LGy=DV=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id EAE3E14B3
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 14 Oct 2020 19:14:51 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id B6CBD2222C
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 14 Oct 2020 19:14:51 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="iiuqpSww"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2390293AbgJNTOu (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 14 Oct 2020 15:14:50 -0400
Received: from us-smtp-delivery-124.mimecast.com ([216.205.24.124]:21071 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S2390270AbgJNTOu (ORCPT
        <rfc822;kvm@vger.kernel.org>); Wed, 14 Oct 2020 15:14:50 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1602702889;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=rI9Og6WXe8ERyQKhuGsm2wLNYwzxUYrIlHuAVicIZVM=;
        b=iiuqpSww7eg/76nFXVcJTzJNilQmw8cwwydAuopRhwjiVxEkC9EM3WGpGgzoO6FqYP8v34
        0JQhk0hL5y/Y8bpeiNi0uAAw08CHWOleB1uuyuGDwELMvmQoTd4X3sbMXLx9n5ZG+LKEEi
        4CXPdb/onE1f/CYMAvYCTMiQLiMY9R8=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-249-35vkk8vDMc6w7vEJoMY7sg-1; Wed, 14 Oct 2020 15:14:47 -0400
X-MC-Unique: 35vkk8vDMc6w7vEJoMY7sg-1
Received: from smtp.corp.redhat.com (int-mx05.intmail.prod.int.phx2.redhat.com
 [10.5.11.15])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id DAB83E9001
        for <kvm@vger.kernel.org>; Wed, 14 Oct 2020 19:14:46 +0000 (UTC)
Received: from kamzik.brq.redhat.com (unknown [10.40.195.61])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 9D27C5577C;
        Wed, 14 Oct 2020 19:14:45 +0000 (UTC)
From: Andrew Jones <drjones@redhat.com>
To: kvm@vger.kernel.org
Cc: pbonzini@redhat.com, thuth@redhat.com
Subject: [PATCH kvm-unit-tests 0/3] A few miscellaneous fixes
Date: Wed, 14 Oct 2020 21:14:41 +0200
Message-Id: <20201014191444.136782-1-drjones@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.15
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

While recently working on kvm-unit-tests I found a few bugs.
Posting the patches now since the series I'm working on may
not get merged for awhile.


Andrew Jones (3):
  lib/string: Fix getenv name matching
  scripts: Save rematch before calling out of for_each_unittest
  arm/arm64: Change dcache_line_size to ulong

 lib/arm/asm/processor.h   | 2 +-
 lib/arm/setup.c           | 2 +-
 lib/arm64/asm/processor.h | 2 +-
 lib/string.c              | 5 ++++-
 scripts/common.bash       | 4 +++-
 5 files changed, 10 insertions(+), 5 deletions(-)
```
