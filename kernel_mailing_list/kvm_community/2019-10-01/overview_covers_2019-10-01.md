

#### [kvm-unit-tests RFC PATCH v2 00/19] arm64: Run at EL2
##### From: Alexandru Elisei <alexandru.elisei@arm.com>

```c
From patchwork Tue Oct  1 10:23:04 2019
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Alexandru Elisei <alexandru.elisei@arm.com>
X-Patchwork-Id: 11168397
Return-Path: <SRS0=7VF/=X2=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 1550A16B1
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue,  1 Oct 2019 10:23:40 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id EC18E21A4A
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue,  1 Oct 2019 10:23:39 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729153AbfJAKXi (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 1 Oct 2019 06:23:38 -0400
Received: from foss.arm.com ([217.140.110.172]:45838 "EHLO foss.arm.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726190AbfJAKXi (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 1 Oct 2019 06:23:38 -0400
Received: from usa-sjc-imap-foss1.foss.arm.com (unknown [10.121.207.14])
        by usa-sjc-mx-foss1.foss.arm.com (Postfix) with ESMTP id D3B9C1000;
        Tue,  1 Oct 2019 03:23:37 -0700 (PDT)
Received: from e123195-lin.cambridge.arm.com (e123195-lin.cambridge.arm.com
 [10.1.196.63])
        by usa-sjc-imap-foss1.foss.arm.com (Postfix) with ESMTPA id
 96C1C3F739;
        Tue,  1 Oct 2019 03:23:36 -0700 (PDT)
From: Alexandru Elisei <alexandru.elisei@arm.com>
To: kvm@vger.kernel.org, kvmarm@lists.cs.columbia.edu
Cc: drjones@redhat.com, pbonzini@redhat.com, rkrcmar@redhat.com,
        maz@kernel.org, vladimir.murzin@arm.com, andre.przywara@arm.com,
        mark.rutland@arm.com
Subject: [kvm-unit-tests RFC PATCH v2 00/19] arm64: Run at EL2
Date: Tue,  1 Oct 2019 11:23:04 +0100
Message-Id: <20191001102323.27628-1-alexandru.elisei@arm.com>
X-Mailer: git-send-email 2.20.1
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

ARMv8.3 added support for nested virtualization, which makes it possible
for a hypervisor to run another hypervisor as a guest. Support for nested
virtualization is being worked on in KVM [1].

This patch series aims to make it possible for kvm-unit-tests to run at EL2
under KVM. The focus has been on having all the infrastructure in place to
run at EL2, and not on adding comprehensive tests for this Exception Level.
All existing tests that fulfill KVM's requirements for a nested guest (the
architecture is arm64 and they use GICv3) will be able to be run at EL2.

To keep the changes minimal, kvm-unit-tests will run with VHE enabled when
it detects that has been booted at EL2. Functions for enabling and
disabling VHE have been added, with the aim to let the user specify to
disable VHE for a given test via command-line parameters. At the moment,
only the timer test has been modified to run with VHE disabled.

The series are firmly an RFC because:
* The patches that implement KVM nested support are themselves in the RFC
  phase.
* Some tests don't complete because of bugs in the current version of the
  KVM patches. Where appropriate, I will provide fixes to allow the tests
  to finish, however those fixes are my own have not been reviewed in any
  way. Use at your own risk.

To run the tests, one obviously needs KVM with nested virtualization
support from [2]. These patches have been tested from commit
78c66132035c ("arm64: KVM: nv: Allow userspace to request
KVM_ARM_VCPU_NESTED_VIRT"), on top of which the following patches have been
cherry-picked from upstream Linux:
* b4a1583abc83 ("KVM: arm/arm64: Fix emulated ptimer irq injection")
* 16e604a437c8 ("KVM: arm/arm64: vgic: Reevaluate level sensitive
  interrupts on enable")

Without those two patches some timer tests will fail.

A version of kvmtool that knows about nested virtualization is also
needed [3]. The kvmtool --nested parameter is required for releasing a
guest at EL2. For example, to run the newly added selftest-el2 test:

lkvm -f selftest.flat -c 2 -m 128 -p el2 --nested --console serial \
	--irqchip gicv3

Changes in v2:
* Gathered Reviewed-by tags.
* Implemented review comments (more details in the specific patches).
* Patch #1 was remove and I've added 4 new patches: #1 removes the obsolete
  CPU_OFF parameter; #4 implements a TODO from arm's flush_tlb_all; #10
  fixes asm_mmu_enable; #11 replaces an expensive and unnecessary TLBI with
  the correct one.

Summary of the patches:
* Patches 1-13 are various fixes or enhancements and can be merged without
  the rest of the series.
* Patches 14-16 add support for running at EL2. A basic selftest-el2 test
  is added that targets EL2.
* Patches 17-19 add support for disabling VHE. The timer and selftest-el2
  tests are modified to use this feature.

[1] https://www.spinics.net/lists/arm-kernel/msg736687.html
[2] git://git.kernel.org/pub/scm/linux/kernel/git/maz/arm-platforms.git kvm-arm64/nv-wip-5.2-rc5
[3] git://linux-arm.org/kvmtool.git nv/nv-wip-5.2-rc5

Alexandru Elisei (19):
  lib: arm/arm64: Remove unused CPU_OFF parameter
  arm/arm64: psci: Don't run C code without stack or vectors
  lib: arm/arm64: Add missing include for alloc_page.h in pgtable.h
  lib: arm: Implement flush_tlb_all
  arm/arm64: selftest: Add prefetch abort test
  arm64: timer: Write to ICENABLER to disable timer IRQ
  arm64: timer: EOIR the interrupt after masking the timer
  arm64: timer: Test behavior when timer disabled or masked
  lib: arm/arm64: Refuse to disable the MMU with non-identity stack
    pointer
  arm/arm64: Perform dcache clean + invalidate after turning MMU off
  arm/cstart64.S: Downgrade TLBI to non-shareable in asm_mmu_enable
  arm/arm64: Invalidate TLB before enabling MMU
  lib: Add _UL and _ULL definitions to linux/const.h
  lib: arm64: Run existing tests at EL2
  arm64: timer: Add test for EL2 timers
  arm64: selftest: Add basic test for EL2
  lib: arm64: Add support for disabling and re-enabling VHE
  arm64: selftest: Expand EL2 test to disable and re-enable VHE
  arm64: timer: Run tests with VHE disabled

 lib/linux/const.h             |   7 +-
 lib/arm/asm/gic-v3.h          |   1 +
 lib/arm/asm/gic.h             |   1 +
 lib/arm/asm/mmu.h             |   7 +-
 lib/arm/asm/pgtable.h         |   1 +
 lib/arm/asm/processor.h       |   6 +
 lib/arm/asm/psci.h            |   1 +
 lib/arm64/asm/esr.h           |   5 +
 lib/arm64/asm/mmu.h           |  11 +-
 lib/arm64/asm/pgtable-hwdef.h |  79 +++++---
 lib/arm64/asm/pgtable.h       |   1 +
 lib/arm64/asm/processor.h     |  34 ++++
 lib/arm64/asm/sysreg.h        |  28 +++
 lib/arm/mmu.c                 |   5 +-
 lib/arm/processor.c           |  10 +
 lib/arm/psci.c                |  47 ++++-
 lib/arm/setup.c               |   7 +
 lib/arm64/processor.c         |  54 +++++-
 arm/cstart.S                  |  33 ++++
 arm/cstart64.S                | 243 +++++++++++++++++++++++-
 arm/micro-bench.c             |  17 +-
 arm/psci.c                    |   5 +-
 arm/selftest.c                | 188 +++++++++++++++++--
 arm/timer.c                   | 340 ++++++++++++++++++++++++++++++----
 arm/unittests.cfg             |   8 +
 25 files changed, 1048 insertions(+), 91 deletions(-)
```
#### [PATCH v11 0/6] mm / virtio: Provide support for unused page
##### From: Alexander Duyck <alexander.duyck@gmail.com>

```c
From patchwork Tue Oct  1 15:29:14 2019
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Alexander Duyck <alexander.duyck@gmail.com>
X-Patchwork-Id: 11169049
Return-Path: <SRS0=7VF/=X2=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 233F21709
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue,  1 Oct 2019 15:29:22 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id E1F2A21872
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue,  1 Oct 2019 15:29:21 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=gmail.com header.i=@gmail.com
 header.b="iRXjxotr"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2389582AbfJAP3S (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 1 Oct 2019 11:29:18 -0400
Received: from mail-pf1-f195.google.com ([209.85.210.195]:35958 "EHLO
        mail-pf1-f195.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S2389528AbfJAP3S (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 1 Oct 2019 11:29:18 -0400
Received: by mail-pf1-f195.google.com with SMTP id y22so8255291pfr.3;
        Tue, 01 Oct 2019 08:29:17 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=subject:from:to:cc:date:message-id:user-agent:mime-version
         :content-transfer-encoding;
        bh=7IVtwir5rJCl/l+meHu5GdAZZYvG0EyeZNBbmna3l+s=;
        b=iRXjxotrgfUGFawrkMu5c5MHLo0jOWciV9xYLegj7/skijRl18LOSviHWG3D0kwwpq
         a7pf3LGFeK62QGv0NpnwVpbDj2sLhcjEKV/9QQkg+OcLGtTi44RrD6tvmBfc9NFNe1ZH
         2w0ZKJy1GpXdszfS7jqFersSuYcJCnjRVeTMxsjKoC9SSFpzy1GR/TR/W44A94i9Pf8l
         JyVt0GRy2BcdSX4fjVi1JXhelTVQN1+ER3S08n8zjQRMq/Mv3/A5S3BnEZxM3Aflwi2l
         R0GdZ1EetgjZYXenpxg7qyq9IXoCEWrVEt+dMu4fz/vw/hJ/nK4RYDOTtepQIi66TOV4
         omZw==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:subject:from:to:cc:date:message-id:user-agent
         :mime-version:content-transfer-encoding;
        bh=7IVtwir5rJCl/l+meHu5GdAZZYvG0EyeZNBbmna3l+s=;
        b=H2S6NDxy2s5cCdzydOct+6gzEYE6kCtvabHgS2Wc+6DD349XrCzne/NUgamyh3pT9L
         P4rqNkSzOx/usM0QgcyFjkUQ393/vU3UfcaER/MoPEYEqcaHK3IyduuDumj3hCEIcyCV
         VU8kbRGIjNb22w/oy8ag6s609UrTCdD7xpAqHXE13QnSA7FI+j63ZrKkZ5CTFnXiQOD7
         CaDnkHcTVkOJ6czrd0LeTAvW6djJWethLERw65EzRLQsAT91wgXESQwUdlNZujd8Zu1m
         ddXTTb/X6oe6otF7cFzfatBCIX9x89BpnLBIaGLzq01dcR22WbMtlvTldl9OoHhTYIV5
         BRSA==
X-Gm-Message-State: APjAAAWIFM9S52ZM01mY/PZqN82xHj1A3qjJ+ygPsf/Ho1ldA/ld2VGE
        y9mR2MOBXXFbqZaK7CyvFUk=
X-Google-Smtp-Source: 
 APXvYqw+igPOQgS5RyPXPG7xdSwHmMKAA0Hr0JZYWjNlVUght/lJ3ipL4t7XF++SFxirihSTMtDWqQ==
X-Received: by 2002:a65:68d3:: with SMTP id
 k19mr30947812pgt.149.1569943756735;
        Tue, 01 Oct 2019 08:29:16 -0700 (PDT)
Received: from localhost.localdomain ([2001:470:b:9c3:9e5c:8eff:fe4f:f2d0])
        by smtp.gmail.com with ESMTPSA id
 b5sm18552586pfp.38.2019.10.01.08.29.15
        (version=TLS1_2 cipher=ECDHE-RSA-AES128-GCM-SHA256 bits=128/128);
        Tue, 01 Oct 2019 08:29:15 -0700 (PDT)
Subject: [PATCH v11 0/6] mm / virtio: Provide support for unused page
 reporting
From: Alexander Duyck <alexander.duyck@gmail.com>
To: virtio-dev@lists.oasis-open.org, kvm@vger.kernel.org,
        mst@redhat.com, david@redhat.com, dave.hansen@intel.com,
        linux-kernel@vger.kernel.org, willy@infradead.org,
        mhocko@kernel.org, linux-mm@kvack.org, akpm@linux-foundation.org,
        mgorman@techsingularity.net, vbabka@suse.cz, osalvador@suse.de
Cc: yang.zhang.wz@gmail.com, pagupta@redhat.com,
        konrad.wilk@oracle.com, nitesh@redhat.com, riel@surriel.com,
        lcapitulino@redhat.com, wei.w.wang@intel.com, aarcange@redhat.com,
        pbonzini@redhat.com, dan.j.williams@intel.com,
        alexander.h.duyck@linux.intel.com
Date: Tue, 01 Oct 2019 08:29:14 -0700
Message-ID: <20191001152441.27008.99285.stgit@localhost.localdomain>
User-Agent: StGit/0.17.1-dirty
MIME-Version: 1.0
Content-Type: text/plain; charset="utf-8"
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This series provides an asynchronous means of reporting to a hypervisor
that a guest page is no longer in use and can have the data associated
with it dropped. To do this I have implemented functionality that allows
for what I am referring to as unused page reporting. The advantage of
unused page reporting is that we can support a significant amount of
memory over-commit with improved performance as we can avoid having to
write/read memory from swap as the VM will instead actively participate
in freeing unused memory so it doesn't have to be written.

The functionality for this is fairly simple. When enabled it will allocate
statistics to track the number of reported pages in a given free area.
When the number of free pages exceeds this value plus a high water value,
currently 32, it will begin performing page reporting which consists of
pulling non-reported pages off of the free lists of a given zone and
placing them into a scatterlist. The scatterlist is then given to the page
reporting device and it will perform the required action to make the pages
"reported", in the case of virtio-balloon this results in the pages being
madvised as MADV_DONTNEED. After this they are placed back on their
original free list. If they are not merged in freeing an additional bit is
set indicating that they are a "reported" buddy page instead of a standard
buddy page. The cycle then repeats with additional non-reported pages
being pulled until the free areas all consist of reported pages.

In order to try and keep the time needed to find a non-reported page to
a minimum we maintain a "reported_boundary" pointer. This pointer is used
by the get_unreported_pages iterator to determine at what point it should
resume searching for non-reported pages. In order to guarantee pages do
not get past the scan I have modified add_to_free_list_tail so that it
will not insert pages behind the reported_boundary. Doing this allows us
to keep the overhead to a minimum as re-walking the list without the
boundary will result in as much as 18% additional overhead on a 32G VM.

If another process needs to perform a massive manipulation of the free
list, such as compaction, it can either reset a given individual boundary
which will push the boundary back to the list_head, or it can clear the
bit indicating the zone is actively processing which will result in the
reporting process resetting all of the boundaries for a given zone.

I am leaving a number of things hard-coded such as limiting the lowest
order processed to pageblock_order, and have left it up to the guest to
determine what the limit is on how many pages it wants to allocate to
process the hints. The upper limit for this is based on the size of the
queue used to store the scatterlist.

I wanted to avoid gaming the performance testing for this. As far as
possible gain a significant performance improvement should be visible in
cases where guests are forced to write/read from swap. As such, testing
it would be more of a benchmark of copying a page from swap versus just
allocating a zero page. I have been verifying that the memory is being
freed using memhog to allocate all the memory on the guest, and then
watching /proc/meminfo to verify the host sees the memory returned after
the test completes.

As far as possible regressions I have focused on cases where performing
the hinting would be non-optimal, such as cases where the code isn't
needed as memory is not over-committed, or the functionality is not in
use. I have been using the will-it-scale/page_fault1 test running with 16
vcpus and have modified it to use Transparent Huge Pages. With this I see
almost no difference with the patches applied and the feature disabled.
Likewise I see almost no difference with the feature enabled, but the
madvise disabled in the hypervisor due to a device being assigned. With
the feature fully enabled in both guest and hypervisor I see a regression
between -1.86% and -8.84% versus the baseline. I found that most of the
overhead was due to the page faulting/zeroing that comes as a result of
the pages having been evicted from the guest.

For info on earlier versions you will need to follow the links provided
with the respective versions.

Changes from v9:
https://lore.kernel.org/lkml/20190907172225.10910.34302.stgit@localhost.localdomain/
Updated cover page
Dropped per-cpu page randomization entropy patch
Added "to_tail" boolean value to __free_one_page to improve readability
Renamed __shuffle_pick_tail to shuffle_pick_tail, avoiding extra inline function
Dropped arm64 HUGLE_TLB_ORDER movement patch since it is no longer needed
Significant rewrite of page reporting functionality
  Updated logic to support interruptions from compaction
  get_unreported_page will now walk through reported sections
  Moved free_list manipulators out of mmzone.h and into page_alloc.c
  Removed page_reporting.h include from mmzone.h
  Split page_reporting.h between include/linux/ and mm/
  Added #include <asm/pgtable.h>" to mm/page_reporting.h
  Renamed page_reporting_startup/shutdown to page_reporting_register/unregister
Updated comments related to virtio page poison tracking feature

Changes from v10:
https://lore.kernel.org/lkml/20190918175109.23474.67039.stgit@localhost.localdomain/
Rebased on "Add linux-next specific files for 20190930"
Added page_is_reported() macro to prevent unneeded testing of PageReported bit
Fixed several spots where comments referred to older aeration naming
Set upper limit for phdev->capacity to page reporting high water mark
Updated virtio page poison detection logic to also cover init_on_free
Tweaked page_reporting_notify_free to reduce code size
Removed dead code in non-reporting path
---

Alexander Duyck (6):
      mm: Adjust shuffle code to allow for future coalescing
      mm: Use zone and order instead of free area in free_list manipulators
      mm: Introduce Reported pages
      mm: Add device side and notifier for unused page reporting
      virtio-balloon: Pull page poisoning config out of free page hinting
      virtio-balloon: Add support for providing unused page reports to host


 drivers/virtio/Kconfig              |    1 
 drivers/virtio/virtio_balloon.c     |   88 ++++++++-
 include/linux/mmzone.h              |   60 ++----
 include/linux/page-flags.h          |   11 +
 include/linux/page_reporting.h      |   31 +++
 include/uapi/linux/virtio_balloon.h |    1 
 mm/Kconfig                          |   11 +
 mm/Makefile                         |    1 
 mm/compaction.c                     |    5 +
 mm/memory_hotplug.c                 |    2 
 mm/page_alloc.c                     |  194 +++++++++++++++----
 mm/page_reporting.c                 |  350 +++++++++++++++++++++++++++++++++++
 mm/page_reporting.h                 |  225 +++++++++++++++++++++++
 mm/shuffle.c                        |   12 +
 mm/shuffle.h                        |    6 +
 15 files changed, 896 insertions(+), 102 deletions(-)
 create mode 100644 include/linux/page_reporting.h
 create mode 100644 mm/page_reporting.c
 create mode 100644 mm/page_reporting.h

--
```
