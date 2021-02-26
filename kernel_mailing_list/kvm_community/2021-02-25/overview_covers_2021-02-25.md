

#### [PATCH kvmtool v2 00/22] Unify I/O port and MMIO trap handling
##### From: Andre Przywara <andre.przywara@arm.com>

```c
From patchwork Thu Feb 25 00:58:53 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Andre Przywara <andre.przywara@arm.com>
X-Patchwork-Id: 12103013
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-11.8 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,
	SPF_PASS,USER_AGENT_GIT autolearn=unavailable autolearn_force=no
 version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id CC711C433DB
	for <kvm@archiver.kernel.org>; Thu, 25 Feb 2021 01:01:20 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 9D53D64EF1
	for <kvm@archiver.kernel.org>; Thu, 25 Feb 2021 01:01:20 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S236584AbhBYBBQ (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Wed, 24 Feb 2021 20:01:16 -0500
Received: from foss.arm.com ([217.140.110.172]:58240 "EHLO foss.arm.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S234345AbhBYBBM (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 24 Feb 2021 20:01:12 -0500
Received: from usa-sjc-imap-foss1.foss.arm.com (unknown [10.121.207.14])
        by usa-sjc-mx-foss1.foss.arm.com (Postfix) with ESMTP id 2D098ED1;
        Wed, 24 Feb 2021 17:00:26 -0800 (PST)
Received: from localhost.localdomain (unknown [172.31.20.19])
        by usa-sjc-imap-foss1.foss.arm.com (Postfix) with ESMTPSA id
 CF9053F73B;
        Wed, 24 Feb 2021 17:00:24 -0800 (PST)
From: Andre Przywara <andre.przywara@arm.com>
To: Will Deacon <will@kernel.org>,
        Julien Thierry <julien.thierry.kdev@gmail.com>
Cc: Alexandru Elisei <alexandru.elisei@arm.com>, kvm@vger.kernel.org,
        kvmarm@lists.cs.columbia.edu, Marc Zyngier <maz@kernel.org>,
        Sami Mujawar <sami.mujawar@arm.com>
Subject: [PATCH kvmtool v2 00/22] Unify I/O port and MMIO trap handling
Date: Thu, 25 Feb 2021 00:58:53 +0000
Message-Id: <20210225005915.26423-1-andre.przywara@arm.com>
X-Mailer: git-send-email 2.14.1
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Compared to v1 this has a few fixes, as suggested by Alex.
There is a new patch 20/22, which cleans up the ARM memory map
definition and adds some chart to make it more obvious what is going on.
For a changelog, see below.

==============

At the moment we use two separate code paths to handle exits for
KVM_EXIT_IO (ioport.c) and KVM_EXIT_MMIO (mmio.c), even though they
are semantically very similar. Because the trap handler callback routine
is different, devices need to decide on one conduit or need to provide
different handler functions for both of them.

This is not only unnecessary code duplication, but makes switching
devices from I/O port to MMIO a tedious task, even though there is no
real difference between the two, especially on ARM and PowerPC.

For ARM we aim at providing a flexible memory layout, and also have
trouble with the UART and RTC device overlapping with the PCI I/O area,
so it seems indicated to tackle this once and for all.

The first three patches do some cleanup, to simplify things later.

Patch 04/22 lays the groundwork, by extending mmio.c to be able to also
register I/O port trap handlers, using the same callback prototype as
we use for MMIO.

The next 14 patches then convert devices that use the I/O port
interface over to the new joint interface. This requires to rework
the trap handler routine to adhere to the same prototype as the existing
MMIO handlers. For most devices this is done in two steps: a first to
introduce the reworked handler routine, and a second to switch to the new
joint registration routine. For some devices the first step is trivial,
so it's done in one patch.

Patch 19/22 then retires the old I/O port interface, by removing ioport.c
and friends.
Patch 20/22 uses the opportunity to clean up the memory map description,
also declares a new region (from 16MB on), where the final two patches
switch the UART and the RTC device to. They are now registered
on the MMIO "bus", when running on ARM or arm64. This moves them away
from the first 64KB, so they are not in the PCI I/O area anymore.

Please have a look and comment!

Cheers,
Andre

Changelog v1 .. v2:
- rework memory map definition
- add explicit debug output for debug I/O port
- add explicit check for MMIO coalescing on I/O ports
- drop usage of ioport__{read,write}8() from serial
- drop explicit I/O port cleanup routine (to mimic MMIO operation)
- add comment for IOTRAP_BUS_MASK
- minor cleanups / formatting changes

Andre Przywara (22):
  ioport: Remove ioport__setup_arch()
  hw/serial: Use device abstraction for FDT generator function
  ioport: Retire .generate_fdt_node functionality
  mmio: Extend handling to include ioport emulation
  hw/i8042: Clean up data types
  hw/i8042: Refactor trap handler
  hw/i8042: Switch to new trap handlers
  x86/ioport: Refactor trap handlers
  x86/ioport: Switch to new trap handlers
  hw/rtc: Refactor trap handlers
  hw/rtc: Switch to new trap handler
  hw/vesa: Switch trap handling to use MMIO handler
  hw/serial: Refactor trap handler
  hw/serial: Switch to new trap handlers
  vfio: Refactor ioport trap handler
  vfio: Switch to new ioport trap handlers
  virtio: Switch trap handling to use MMIO handler
  pci: Switch trap handling to use MMIO handler
  Remove ioport specific routines
  arm: Reorganise and document memory map
  hw/serial: ARM/arm64: Use MMIO at higher addresses
  hw/rtc: ARM/arm64: Use MMIO at higher addresses

 Makefile                          |   1 -
 arm/include/arm-common/kvm-arch.h |  47 ++++--
 arm/ioport.c                      |   5 -
 hw/i8042.c                        |  94 +++++-------
 hw/rtc.c                          |  91 ++++++------
 hw/serial.c                       | 160 ++++++++++++--------
 hw/vesa.c                         |  19 +--
 include/kvm/i8042.h               |   1 -
 include/kvm/ioport.h              |  32 ----
 include/kvm/kvm.h                 |  49 ++++++-
 ioport.c                          | 235 ------------------------------
 mips/kvm.c                        |   5 -
 mmio.c                            |  65 +++++++--
 pci.c                             |  82 +++--------
 powerpc/ioport.c                  |   6 -
 vfio/core.c                       |  50 ++++---
 virtio/pci.c                      |  46 ++----
 x86/ioport.c                      | 107 +++++++-------
 18 files changed, 433 insertions(+), 662 deletions(-)
 delete mode 100644 ioport.c
```
#### [RFC PATCH v2 0/7] Some improvement and a new test for kvm page table
##### From: Yanan Wang <wangyanan55@huawei.com>

```c
From patchwork Thu Feb 25 05:59:33 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: "wangyanan (Y)" <wangyanan55@huawei.com>
X-Patchwork-Id: 12103323
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.8 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_PATCH,MAILING_LIST_MULTI,
	MENTIONS_GIT_HOSTING,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT
	autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 5A827C433E0
	for <kvm@archiver.kernel.org>; Thu, 25 Feb 2021 06:00:52 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 02C1764EBA
	for <kvm@archiver.kernel.org>; Thu, 25 Feb 2021 06:00:51 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S235048AbhBYGAe (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Thu, 25 Feb 2021 01:00:34 -0500
Received: from szxga04-in.huawei.com ([45.249.212.190]:12648 "EHLO
        szxga04-in.huawei.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S229954AbhBYGAc (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 25 Feb 2021 01:00:32 -0500
Received: from DGGEMS408-HUB.china.huawei.com (unknown [172.30.72.58])
        by szxga04-in.huawei.com (SkyGuard) with ESMTP id 4DmMXM71F5z16CZL;
        Thu, 25 Feb 2021 13:58:11 +0800 (CST)
Received: from DESKTOP-TMVL5KK.china.huawei.com (10.174.187.128) by
 DGGEMS408-HUB.china.huawei.com (10.3.19.208) with Microsoft SMTP Server id
 14.3.498.0; Thu, 25 Feb 2021 13:59:42 +0800
From: Yanan Wang <wangyanan55@huawei.com>
To: <kvm@vger.kernel.org>, <linux-kselftest@vger.kernel.org>,
        <linux-kernel@vger.kernel.org>
CC: Paolo Bonzini <pbonzini@redhat.com>,
        Ben Gardon <bgardon@google.com>,
        "Sean Christopherson" <seanjc@google.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Arnaldo Carvalho de Melo <acme@redhat.com>,
        Ingo Molnar <mingo@kernel.org>,
        Andrew Jones <drjones@redhat.com>,
        Peter Xu <peterx@redhat.com>, Marc Zyngier <maz@kernel.org>,
        <wanghaibin.wang@huawei.com>, <yuzenghui@huawei.com>,
        "Yanan Wang" <wangyanan55@huawei.com>
Subject: [RFC PATCH v2 0/7] Some improvement and a new test for kvm page table
Date: Thu, 25 Feb 2021 13:59:33 +0800
Message-ID: <20210225055940.18748-1-wangyanan55@huawei.com>
X-Mailer: git-send-email 2.8.4.windows.1
MIME-Version: 1.0
X-Originating-IP: [10.174.187.128]
X-CFilter-Loop: Reflected
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Hi,
This v2 series can mainly include two parts.
Based on kvm queue branch: https://git.kernel.org/pub/scm/virt/kvm/kvm.git/log/?h=queue
Links of v1: https://lore.kernel.org/lkml/20210208090841.333724-1-wangyanan55@huawei.com/

In the first part, all the known hugetlb backing src types specified
with different hugepage sizes are listed, so that we can specify use
of hugetlb source of the exact granularity that we want, instead of
the system default ones. And as all the known hugetlb page sizes are
listed, it's appropriate for all architectures. Besides, a helper that
can get granularity of different backing src types(anonumous/thp/hugetlb)
is added, so that we can use the accurate backing src granularity for
kinds of alignment or guest memory accessing of vcpus.

In the second part, a new test is added:
This test is added to serve as a performance tester and a bug reproducer
for kvm page table code (GPA->HPA mappings), it gives guidance for the
people trying to make some improvement for kvm. And the following explains
what we can exactly do through this test.

The function guest_code() can cover the conditions where a single vcpu or
multiple vcpus access guest pages within the same memory region, in three
VM stages(before dirty logging, during dirty logging, after dirty logging).
Besides, the backing src memory type(ANONYMOUS/THP/HUGETLB) of the tested
memory region can be specified by users, which means normal page mappings
or block mappings can be chosen by users to be created in the test.

If ANONYMOUS memory is specified, kvm will create normal page mappings
for the tested memory region before dirty logging, and update attributes
of the page mappings from RO to RW during dirty logging. If THP/HUGETLB
memory is specified, kvm will create block mappings for the tested memory
region before dirty logging, and split the blcok mappings into normal page
mappings during dirty logging, and coalesce the page mappings back into
block mappings after dirty logging is stopped.

So in summary, as a performance tester, this test can present the
performance of kvm creating/updating normal page mappings, or the
performance of kvm creating/splitting/recovering block mappings,
through execution time.

When we need to coalesce the page mappings back to block mappings after
dirty logging is stopped, we have to firstly invalidate *all* the TLB
entries for the page mappings right before installation of the block entry,
because a TLB conflict abort error could occur if we can't invalidate the
TLB entries fully. We have hit this TLB conflict twice on aarch64 software
implementation and fixed it. As this test can imulate process from dirty
logging enabled to dirty logging stopped of a VM with block mappings,
so it can also reproduce this TLB conflict abort due to inadequate TLB
invalidation when coalescing tables.

Links about the TLB conflict abort:
https://lore.kernel.org/lkml/20201201201034.116760-3-wangyanan55@huawei.com/

Yanan Wang (7):
  tools include: sync head files of mmap flag encodings about hugetlb
  KVM: selftests: Use flag CLOCK_MONOTONIC_RAW for timing
  KVM: selftests: Make a generic helper to get vm guest mode strings
  KVM: selftests: Add a helper to get system configured THP page size
  KVM: selftests: List all hugetlb src types specified with page sizes
  KVM: selftests: Adapt vm_userspace_mem_region_add to new helpers
  KVM: selftests: Add a test for kvm page table code

 tools/include/asm-generic/hugetlb_encode.h    |   3 +
 tools/testing/selftests/kvm/Makefile          |   3 +
 .../selftests/kvm/demand_paging_test.c        |   8 +-
 .../selftests/kvm/dirty_log_perf_test.c       |  14 +-
 .../testing/selftests/kvm/include/kvm_util.h  |   4 +-
 .../testing/selftests/kvm/include/test_util.h |  21 +-
 .../selftests/kvm/kvm_page_table_test.c       | 476 ++++++++++++++++++
 tools/testing/selftests/kvm/lib/kvm_util.c    |  58 +--
 tools/testing/selftests/kvm/lib/test_util.c   |  92 +++-
 tools/testing/selftests/kvm/steal_time.c      |   4 +-
 10 files changed, 623 insertions(+), 60 deletions(-)
 create mode 100644 tools/testing/selftests/kvm/kvm_page_table_test.c
```
#### [PATCH 0/4] RFC/WIP: KVM: separate injected and pending exception +
##### From: Maxim Levitsky <mlevitsk@redhat.com>

```c
From patchwork Thu Feb 25 15:41:31 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Maxim Levitsky <mlevitsk@redhat.com>
X-Patchwork-Id: 12104417
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-10.8 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS autolearn=ham
	autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 2FDA4C433E0
	for <kvm@archiver.kernel.org>; Thu, 25 Feb 2021 15:43:15 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id E4C1E64F18
	for <kvm@archiver.kernel.org>; Thu, 25 Feb 2021 15:43:14 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S232137AbhBYPnO (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Thu, 25 Feb 2021 10:43:14 -0500
Received: from us-smtp-delivery-124.mimecast.com ([216.205.24.124]:57962 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S229845AbhBYPnN (ORCPT
        <rfc822;kvm@vger.kernel.org>); Thu, 25 Feb 2021 10:43:13 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1614267707;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=s3cK62eP5ZGb6zqZ97C6c3P2QiYoHi/l4dd9rsUiLKg=;
        b=XRwZIY5xJQfI/V5Hrtn68LGqe8KVhVyqXBYLkagaaS2Qn492pPQ4AlY34oyjvcgh+MkcTI
        zsqhCbqRL/HDZx3gKAIs7Smfm2qmDNiTL1ybxa5/ABgZs5Zb+n/lmRH6t8Rl41RqOee4w0
        lGrQZ1+MnWv+tBkW15G8QSmw0aDhzBs=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-591-6Uv32vupNAyDs-gCC2l4TA-1; Thu, 25 Feb 2021 10:41:44 -0500
X-MC-Unique: 6Uv32vupNAyDs-gCC2l4TA-1
Received: from smtp.corp.redhat.com (int-mx01.intmail.prod.int.phx2.redhat.com
 [10.5.11.11])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 132B8107ACC7;
        Thu, 25 Feb 2021 15:41:41 +0000 (UTC)
Received: from localhost.localdomain (unknown [10.35.207.18])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 36D8A39A63;
        Thu, 25 Feb 2021 15:41:36 +0000 (UTC)
From: Maxim Levitsky <mlevitsk@redhat.com>
To: kvm@vger.kernel.org
Cc: Ingo Molnar <mingo@redhat.com>,
        linux-kernel@vger.kernel.org (open list:X86 ARCHITECTURE (32-BIT AND
        64-BIT)), Jim Mattson <jmattson@google.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        x86@kernel.org (maintainer:X86 ARCHITECTURE (32-BIT AND 64-BIT)),
        Joerg Roedel <joro@8bytes.org>, Borislav Petkov <bp@alien8.de>,
        Thomas Gleixner <tglx@linutronix.de>,
        Wanpeng Li <wanpengli@tencent.com>,
        Sean Christopherson <seanjc@google.com>,
        Paolo Bonzini <pbonzini@redhat.com>,
        "H. Peter Anvin" <hpa@zytor.com>,
        Maxim Levitsky <mlevitsk@redhat.com>
Subject: [PATCH 0/4] RFC/WIP: KVM: separate injected and pending exception +
 few more fixes
Date: Thu, 25 Feb 2021 17:41:31 +0200
Message-Id: <20210225154135.405125-1-mlevitsk@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.11
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

clone of "kernel-starship-5.11"

Maxim Levitsky (4):
  KVM: x86: determine if an exception has an error code only when
    injecting it.
  KVM: x86: mmu: initialize fault.async_page_fault in walk_addr_generic
  KVM: x86: pending exception must be be injected even with an injected
    event
  kvm: WIP separation of injected and pending exception

 arch/x86/include/asm/kvm_host.h |  23 +-
 arch/x86/include/uapi/asm/kvm.h |  14 +-
 arch/x86/kvm/mmu/paging_tmpl.h  |   1 +
 arch/x86/kvm/svm/nested.c       |  57 +++--
 arch/x86/kvm/svm/svm.c          |   8 +-
 arch/x86/kvm/vmx/nested.c       | 109 +++++----
 arch/x86/kvm/vmx/vmx.c          |  14 +-
 arch/x86/kvm/x86.c              | 377 +++++++++++++++++++-------------
 arch/x86/kvm/x86.h              |   6 +-
 include/uapi/linux/kvm.h        |   1 +
 10 files changed, 374 insertions(+), 236 deletions(-)
```
#### [PATCH 00/24] KVM: x86/mmu: Introduce MMU_PRESENT and fix bugs
##### From: Sean Christopherson <seanjc@google.com>

```c
From patchwork Thu Feb 25 20:47:25 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Sean Christopherson <seanjc@google.com>
X-Patchwork-Id: 12104929
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-21.3 required=3.0 tests=BAYES_00,DKIMWL_WL_MED,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT,
	USER_IN_DEF_DKIM_WL autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 62C78C433DB
	for <kvm@archiver.kernel.org>; Thu, 25 Feb 2021 20:48:40 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 26F0E64DE9
	for <kvm@archiver.kernel.org>; Thu, 25 Feb 2021 20:48:40 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S232403AbhBYUsi (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Thu, 25 Feb 2021 15:48:38 -0500
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:50392 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S231881AbhBYUsi (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 25 Feb 2021 15:48:38 -0500
Received: from mail-yb1-xb4a.google.com (mail-yb1-xb4a.google.com
 [IPv6:2607:f8b0:4864:20::b4a])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id C65DEC061574
        for <kvm@vger.kernel.org>; Thu, 25 Feb 2021 12:47:57 -0800 (PST)
Received: by mail-yb1-xb4a.google.com with SMTP id c12so7618495ybf.1
        for <kvm@vger.kernel.org>; Thu, 25 Feb 2021 12:47:57 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=sender:reply-to:date:message-id:mime-version:subject:from:to:cc;
        bh=om9uFHT7e8jzZ23sZL9XQVqb3sS0Fv61rG18CUdoIp0=;
        b=QeFBPAKjT+YjPCo9JcaoxsSX9JFFup0lEG3jQCx5yJI1ixHMZCsadFJ/NNf5RDZz5A
         3mKCO7izGPoz+pC/V9koHNS9jPbCJQCsp3R4idXXfZ4KBQPQRvUHDcH22Z8e7RqxsdD0
         TQI/pp0NvGSnCCLn9mWzdHlNVLkF3HHETi//tjnTvJFK6j0JabIsycg/LWUS6cyx37Ap
         yobJgLs0cG95IiS0twVjcdhZJpNiPfr6m1Sab4is3JSIELkxd+OEM5HWo4KGhIgqqTPR
         2XI0oPfzWzBpDA3wozCD3CX6w16Rq2h+B1cu6BkOCBxWG6J2ix1io6JLiNjdPwQsd8VM
         4aMA==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:sender:reply-to:date:message-id:mime-version
         :subject:from:to:cc;
        bh=om9uFHT7e8jzZ23sZL9XQVqb3sS0Fv61rG18CUdoIp0=;
        b=FZLJvnt8RiYBdEbghGZdAuqqbYESrO6cH+ELL0heQMODVObOceqKTFeMd1tUeyQ/Uc
         eNQFx/KdXMEjvHVKgjI81THRqF3XBWjJGW1TEhQqCRV0NPiejLU1Q8azXF7rKC8qUdwf
         MNI6wpJq5hI9QrAgbrUGRpgH+EIyluOGjAS7cgX6U8nBsW27dMAKGlNrdu+duNw5UOUK
         Pm02Pun0Mh2U4IfycqbJOu4N1c0z2dg9rTliJVo3HyHLP+zkLdYXR24Efx4q0MZfiJKS
         KrQKw2bVQybuIW1PjWSv2uUoizBbvmeVF6kpXal9woeNBsbhhr6Kcxhg9vgDHSh50vGq
         +LFQ==
X-Gm-Message-State: AOAM530ZWvAcyFSNqtPCDA0wowHsUou2gGchbpkJF92KPuXtb03IfRPI
        HIFRN62pwPSVhscX9z9z6R5gyKcQBP8=
X-Google-Smtp-Source: 
 ABdhPJzl2CHRSfum3VVu3pLelkQeo1yBDsqs7I/L+wQrUIIse1Xh/RGmrEbBFSjoFD2ZghbqTRgUPLXJKpA=
Sender: "seanjc via sendgmr" <seanjc@seanjc798194.pdx.corp.google.com>
X-Received: from seanjc798194.pdx.corp.google.com
 ([2620:15c:f:10:34c4:7c1d:f9ba:4576])
 (user=seanjc job=sendgmr) by 2002:a25:1184:: with SMTP id
 126mr6443848ybr.430.1614286077055;
 Thu, 25 Feb 2021 12:47:57 -0800 (PST)
Reply-To: Sean Christopherson <seanjc@google.com>
Date: Thu, 25 Feb 2021 12:47:25 -0800
Message-Id: <20210225204749.1512652-1-seanjc@google.com>
Mime-Version: 1.0
X-Mailer: git-send-email 2.30.1.766.gb4fecdf3b7-goog
Subject: [PATCH 00/24] KVM: x86/mmu: Introduce MMU_PRESENT and fix bugs
From: Sean Christopherson <seanjc@google.com>
To: Paolo Bonzini <pbonzini@redhat.com>
Cc: Sean Christopherson <seanjc@google.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org, Ben Gardon <bgardon@google.com>
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This series adds the simple idea of tagging shadow-present SPTEs with
a single bit, instead of looking for non-zero SPTEs that aren't MMIO and
aren't REMOVED.  Doing so reduces KVM's code footprint by 2k bytes on
x86-64, and presumably adds a tiny performance boost in related paths.

But, actually adding MMU_PRESENT without breaking one flow or another is
a bit of a debacle.  The main issue is that EPT doesn't have many low
available bits, and PAE doesn't have any high available bits.  And, the
existing MMU_WRITABLE and HOST_WRITABLE flags aren't optional, i.e. are
needed for all flavors of paging.  The solution I settled on is to let
make the *_WRITABLE bit configurable so that EPT can use high available
bits.

Of course, I forgot the above PAE restriction multiple times, and
journeyed down several dead ends.  The most notable failed idea was
using the AD_* masks in bits 52 and 53 to denote shadow-present SPTEs.
That would have been quite clever as it would provide the same benefits
without burning another available bit.

Along the many failed attempts, I collected a variety of bug fixes and
cleanups, mostly things found by inspection after doing a deep dive to
figure out what I broke.

Sean Christopherson (24):
  KVM: x86/mmu: Set SPTE_AD_WRPROT_ONLY_MASK if and only if PML is
    enabled
  KVM: x86/mmu: Check for shadow-present SPTE before querying A/D status
  KVM: x86/mmu: Bail from fast_page_fault() if SPTE is not
    shadow-present
  KVM: x86/mmu: Disable MMIO caching if MMIO value collides with L1TF
  KVM: x86/mmu: Retry page faults that hit an invalid memslot
  KVM: x86/mmu: Don't install bogus MMIO SPTEs if MMIO caching is
    disabled
  KVM: x86/mmu: Handle MMIO SPTEs directly in mmu_set_spte()
  KVM: x86/mmu: Drop redundant trace_kvm_mmu_set_spte() in the TDP MMU
  KVM: x86/mmu: Rename 'mask' to 'spte' in MMIO SPTE helpers
  KVM: x86/mmu: Stop using software available bits to denote MMIO SPTEs
  KVM: x86/mmu: Add module param to disable MMIO caching (for testing)
  KVM: x86/mmu: Rename and document A/D scheme for TDP SPTEs
  KVM: x86/mmu: Use MMIO SPTE bits 53 and 52 for the MMIO generation
  KVM: x86/mmu: Document dependency bewteen TDP A/D type and saved bits
  KVM: x86/mmu: Move initial kvm_mmu_set_mask_ptes() call into MMU
    proper
  KVM: x86/mmu: Co-locate code for setting various SPTE masks
  KVM: x86/mmu: Move logic for setting SPTE masks for EPT into the MMU
    proper
  KVM: x86/mmu: Make Host-writable and MMU-writable bit locations
    dynamic
  KVM: x86/mmu: Use high bits for host/mmu writable masks for EPT SPTEs
  KVM: x86/mmu: Use a dedicated bit to track shadow/MMU-present SPTEs
  KVM: x86/mmu: Tweak auditing WARN for A/D bits to !PRESENT (was MMIO)
  KVM: x86/mmu: Use is_removed_spte() instead of open coded equivalents
  KVM: x86/mmu: Use low available bits for removed SPTEs
  KVM: x86/mmu: Dump reserved bits if they're detected on non-MMIO SPTE

 Documentation/virt/kvm/locking.rst |  49 +++++----
 arch/x86/include/asm/kvm_host.h    |   3 -
 arch/x86/kvm/mmu.h                 |  15 +--
 arch/x86/kvm/mmu/mmu.c             |  87 +++++++---------
 arch/x86/kvm/mmu/mmu_internal.h    |  16 +--
 arch/x86/kvm/mmu/paging_tmpl.h     |   2 +-
 arch/x86/kvm/mmu/spte.c            | 157 ++++++++++++++++++++---------
 arch/x86/kvm/mmu/spte.h            | 135 +++++++++++++++++--------
 arch/x86/kvm/mmu/tdp_mmu.c         |  22 ++--
 arch/x86/kvm/svm/svm.c             |   2 +-
 arch/x86/kvm/vmx/vmx.c             |  24 +----
 arch/x86/kvm/x86.c                 |   3 -
 12 files changed, 290 insertions(+), 225 deletions(-)
```
