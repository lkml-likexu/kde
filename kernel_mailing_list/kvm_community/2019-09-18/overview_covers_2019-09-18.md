

#### [PATCH RESEND v4 0/2] x86: Enable user wait instructions
##### From: Tao Xu <tao3.xu@intel.com>

```c
From patchwork Wed Sep 18 07:23:27 2019
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 8bit
X-Patchwork-Submitter: Tao Xu <tao3.xu@intel.com>
X-Patchwork-Id: 11149719
Return-Path: <SRS0=6oZb=XN=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 35AEF16B1
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 18 Sep 2019 07:23:36 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 1E6B7218AF
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 18 Sep 2019 07:23:35 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728404AbfIRHXf (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 18 Sep 2019 03:23:35 -0400
Received: from mga07.intel.com ([134.134.136.100]:60890 "EHLO mga07.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726077AbfIRHXe (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 18 Sep 2019 03:23:34 -0400
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from fmsmga007.fm.intel.com ([10.253.24.52])
  by orsmga105.jf.intel.com with ESMTP/TLS/DHE-RSA-AES256-GCM-SHA384;
 18 Sep 2019 00:23:34 -0700
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.64,519,1559545200";
   d="scan'208";a="187694676"
Received: from tao-optiplex-7060.sh.intel.com ([10.239.159.36])
  by fmsmga007.fm.intel.com with ESMTP; 18 Sep 2019 00:23:32 -0700
From: Tao Xu <tao3.xu@intel.com>
To: pbonzini@redhat.com, rth@twiddle.net, ehabkost@redhat.com,
        mtosatti@redhat.com
Cc: qemu-devel@nongnu.org, kvm@vger.kernel.org, tao3.xu@intel.com,
        jingqi.liu@intel.com
Subject: [PATCH RESEND v4 0/2] x86: Enable user wait instructions
Date: Wed, 18 Sep 2019 15:23:27 +0800
Message-Id: <20190918072329.1911-1-tao3.xu@intel.com>
X-Mailer: git-send-email 2.20.1
MIME-Version: 1.0
Content-Type: text/plain; charset=UTF-8
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

UMONITOR, UMWAIT and TPAUSE are a set of user wait instructions.

UMONITOR arms address monitoring hardware using an address. A store
to an address within the specified address range triggers the
monitoring hardware to wake up the processor waiting in umwait.

UMWAIT instructs the processor to enter an implementation-dependent
optimized state while monitoring a range of addresses. The optimized
state may be either a light-weight power/performance optimized state
(c0.1 state) or an improved power/performance optimized state
(c0.2 state).

TPAUSE instructs the processor to enter an implementation-dependent
optimized state c0.1 or c0.2 state and wake up when time-stamp counter
reaches specified timeout.

Availability of the user wait instructions is indicated by the presence
of the CPUID feature flag WAITPKG CPUID.0x07.0x0:ECX[5].

The patches enable the umonitor, umwait and tpause features in KVM.
Because umwait and tpause can put a (psysical) CPU into a power saving
state, by default we dont't expose it in kvm and provide a capability to
enable it. Use kvm capability to enable UMONITOR, UMWAIT and TPAUSE when
QEMU use "-overcommit cpu-pm=on, a VM can use UMONITOR, UMWAIT and TPAUSE
instructions. If the instruction causes a delay, the amount of time
delayed is called here the physical delay. The physical delay is first
computed by determining the virtual delay (the time to delay relative to
the VM’s timestamp counter). Otherwise, UMONITOR, UMWAIT and TPAUSE cause
an invalid-opcode exception(#UD).

The dependency KVM patch link:
https://lkml.org/lkml/2019/7/16/58

The release document ref below link:
https://software.intel.com/sites/default/files/\
managed/39/c5/325462-sdm-vol-1-2abcd-3abcd.pdf

Changelog:
v4:
	Set IA32_UMWAIT_CONTROL 32bits
v3:
	Simplify the patches, expose user wait instructions when the guest
	has CPUID (Paolo)
v2:
	Separated from the series
	https://www.mail-archive.com/qemu-devel@nongnu.org/msg549526.html
	Use kvm capability to enable UMONITOR, UMWAIT and TPAUSE when
	QEMU use "-overcommit cpu-pm=on"	
v1:
	Sent out with MOVDIRI/MOVDIR64B instructions patches

Tao Xu (2):
  x86/cpu: Add support for UMONITOR/UMWAIT/TPAUSE
  target/i386: Add support for save/load IA32_UMWAIT_CONTROL MSR

 target/i386/cpu.c     |  3 ++-
 target/i386/cpu.h     |  3 +++
 target/i386/kvm.c     | 17 +++++++++++++++++
 target/i386/machine.c | 20 ++++++++++++++++++++
 4 files changed, 42 insertions(+), 1 deletion(-)
```
#### [RFC PATCH v3 0/6] Enable ptp_kvm for arm64
##### From: Jianyong Wu <jianyong.wu@arm.com>

```c
From patchwork Wed Sep 18 08:07:10 2019
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: "Jianyong Wu (Arm Technology China)"
 <jianyong.wu@arm.com>
X-Patchwork-Id: 11149815
Return-Path: <SRS0=6oZb=XN=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id C580514DB
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 18 Sep 2019 08:07:35 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id ACED121907
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 18 Sep 2019 08:07:35 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729484AbfIRIHb (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 18 Sep 2019 04:07:31 -0400
Received: from foss.arm.com ([217.140.110.172]:36748 "EHLO foss.arm.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1725298AbfIRIHb (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 18 Sep 2019 04:07:31 -0400
Received: from usa-sjc-imap-foss1.foss.arm.com (unknown [10.121.207.14])
        by usa-sjc-mx-foss1.foss.arm.com (Postfix) with ESMTP id AD95828;
        Wed, 18 Sep 2019 01:07:30 -0700 (PDT)
Received: from entos-d05.shanghai.arm.com (entos-d05.shanghai.arm.com
 [10.169.40.35])
        by usa-sjc-imap-foss1.foss.arm.com (Postfix) with ESMTPA id
 8EAE63F59C;
        Wed, 18 Sep 2019 01:07:25 -0700 (PDT)
From: Jianyong Wu <jianyong.wu@arm.com>
To: netdev@vger.kernel.org, yangbo.lu@nxp.com, john.stultz@linaro.org,
        tglx@linutronix.de, pbonzini@redhat.com,
        sean.j.christopherson@intel.com, maz@kernel.org,
        richardcochran@gmail.com, Mark.Rutland@arm.com,
        Will.Deacon@arm.com, suzuki.poulose@arm.com
Cc: linux-kernel@vger.kernel.org, kvm@vger.kernel.org,
        Steve.Capper@arm.com, Kaly.Xin@arm.com, justin.he@arm.com,
        jianyong.wu@arm.com, nd@arm.com,
        linux-arm-kernel@lists.infradead.org
Subject: [RFC PATCH v3 0/6] Enable ptp_kvm for arm64
Date: Wed, 18 Sep 2019 04:07:10 -0400
Message-Id: <20190918080716.64242-1-jianyong.wu@arm.com>
X-Mailer: git-send-email 2.17.1
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

kvm ptp targets to provide high precision time sync between guest
and host in virtualization environment. This patch enable kvm ptp
for arm64.
This patch set base on [1][2][3]

change log:
from v2 to v3:
        (1) fix some issues in commit log.
        (2) add some receivers in send list.
from v1 to v2:
        (1) move arch-specific code from arch/ to driver/ptp/
        (2) offer mechanism to inform userspace if ptp_kvm service is
available.
        (3) separate ptp_kvm code for arm64 into hypervisor part and
guest part.
        (4) add API to expose monotonic clock and counter value.
        (5) refine code: remove no necessary part and reconsitution.

[1]https://git.kernel.org/pub/scm/linux/kernel/git/will/linux.git/
commit/?h=kvm/hvc&id=125ea89e4a21e2fc5235410f966a996a1a7148bf
[2]https://git.kernel.org/pub/scm/linux/kernel/git/will/linux.git/
commit/?h=kvm/hvc&id=464f5a1741e5959c3e4d2be1966ae0093b4dce06
[3]https://git.kernel.org/pub/scm/linux/kernel/git/will/linux.git/
commit/?h=kvm/hvc&id=6597490e005d0eeca8ed8c1c1d7b4318ee014681

Jianyong Wu (6):
  psci: Export psci_ops.conduit symbol as modules will use it.
  ptp: Reorganize ptp_kvm modules to make it arch-independent.
  timekeeping: Expose API allowing retrival of current clocksource and
    counter value
  psci: Add hvc call service for ptp_kvm.
  ptp: arm64: Enable ptp_kvm for arm64
  kvm: arm64: Add capability check extension for ptp_kvm

 drivers/firmware/psci/psci.c         |  6 ++
 drivers/ptp/Kconfig                  |  2 +-
 drivers/ptp/Makefile                 |  1 +
 drivers/ptp/{ptp_kvm.c => kvm_ptp.c} | 77 ++++++------------------
 drivers/ptp/ptp_kvm_arm64.c          | 82 ++++++++++++++++++++++++++
 drivers/ptp/ptp_kvm_x86.c            | 87 ++++++++++++++++++++++++++++
 include/asm-generic/ptp_kvm.h        | 12 ++++
 include/linux/arm-smccc.h            | 14 ++++-
 include/linux/psci.h                 |  1 +
 include/linux/timekeeping.h          |  3 +
 include/uapi/linux/kvm.h             |  1 +
 kernel/time/timekeeping.c            | 13 +++++
 virt/kvm/arm/arm.c                   |  1 +
 virt/kvm/arm/psci.c                  | 17 ++++++
 14 files changed, 256 insertions(+), 61 deletions(-)
 rename drivers/ptp/{ptp_kvm.c => kvm_ptp.c} (63%)
 create mode 100644 drivers/ptp/ptp_kvm_arm64.c
 create mode 100644 drivers/ptp/ptp_kvm_x86.c
 create mode 100644 include/asm-generic/ptp_kvm.h
```
#### [PATCH v10 0/6] mm / virtio: Provide support for unused page
##### From: Alexander Duyck <alexander.duyck@gmail.com>

```c
From patchwork Wed Sep 18 17:52:25 2019
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Alexander Duyck <alexander.duyck@gmail.com>
X-Patchwork-Id: 11151057
Return-Path: <SRS0=6oZb=XN=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 5D95D196C
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 18 Sep 2019 17:52:33 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 32BE521907
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 18 Sep 2019 17:52:33 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=gmail.com header.i=@gmail.com
 header.b="qyqlBWw1"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727109AbfIRRw3 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 18 Sep 2019 13:52:29 -0400
Received: from mail-oi1-f195.google.com ([209.85.167.195]:44344 "EHLO
        mail-oi1-f195.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1725899AbfIRRw3 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 18 Sep 2019 13:52:29 -0400
Received: by mail-oi1-f195.google.com with SMTP id w6so311391oie.11;
        Wed, 18 Sep 2019 10:52:28 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=subject:from:to:cc:date:message-id:user-agent:mime-version
         :content-transfer-encoding;
        bh=mGxYN8fKLFN6z5avB+andfhVV4A+WX96NEccYZ4KSJ0=;
        b=qyqlBWw1TSg7WCQxN8G2wS400TI3RlB/WNNQy/BASpbQH7dai4KuaUPYwfRbQJqr83
         tymtB88GT+36Ujs21eCz4GigdJaiPddygAeTaQj1gzZJ+74zk4+UB0saoe9kz5DZz2M6
         G0BSXzcf3Q2OPAQHUYbpfqWO4wu8YWfOR9EIHVjmO3q4XxLsPDkl0HprogQDrFPkYkfP
         /lr+jzZfDtW7yiTnakt1uKvk8Ma3MPDNgQgzxsp30RXU8TY7OJjOFvZJ3qs41Q5uHrPA
         0InuSyusYyAZKzh4u57bf27Dr8GqXXXVKWk3VzKLHtEQr4qbjklhAn9g1vtqdMpKtLI3
         E6Gw==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:subject:from:to:cc:date:message-id:user-agent
         :mime-version:content-transfer-encoding;
        bh=mGxYN8fKLFN6z5avB+andfhVV4A+WX96NEccYZ4KSJ0=;
        b=X+lisZ+OG3i2tElSwm0EwFSASDhirJjWGsg8XIeFIuNPdDHsQVhzmV14wfLURPiOyy
         jz417QWhtyqttHmn30DY438fu8tt+wUrRXVYZgyMn2t8Dm2YO7AV2rjlpDDICiK16pu0
         5jVn/wFIOOjech5rQVuTAL7Y4QZOHypvj8co96OUdEIq4ogsYl3Q0OHUkNSDFnbXfB1W
         OYhJxgXxVZQFmYiMtKgmd+ys9tMI2e8ZHQ1UZ6bmwSXRCwl4pXNE9moDNoE1yH+5HTFb
         UnwNmd7KKYoKuAfoWXfEgy0LEuR5vTSkED7uFdG4QFE43CgSJ2nhqMN8PYssTk90Own3
         EfiQ==
X-Gm-Message-State: APjAAAXdGq+k5dsXO8VQeTpFzVWHEdBwoAVMTXPopHkfRIq8NRY5mNUI
        AKv9LZydGa15fOA7uZ2aCTw=
X-Google-Smtp-Source: 
 APXvYqx3VRfarQJCxejKo+vbLPE/nAA+u3uNVEGvbb5/nNYHkpfJs6nxS+UG8lCLMNOa7yifkgs3Cg==
X-Received: by 2002:a54:4f8a:: with SMTP id g10mr3314526oiy.147.1568829148372;
        Wed, 18 Sep 2019 10:52:28 -0700 (PDT)
Received: from localhost.localdomain ([2001:470:b:9c3:9e5c:8eff:fe4f:f2d0])
        by smtp.gmail.com with ESMTPSA id
 r7sm1994572oih.41.2019.09.18.10.52.26
        (version=TLS1_2 cipher=ECDHE-RSA-AES128-GCM-SHA256 bits=128/128);
        Wed, 18 Sep 2019 10:52:27 -0700 (PDT)
Subject: [PATCH v10 0/6] mm / virtio: Provide support for unused page
 reporting
From: Alexander Duyck <alexander.duyck@gmail.com>
To: virtio-dev@lists.oasis-open.org, kvm@vger.kernel.org,
        mst@redhat.com, david@redhat.com, dave.hansen@intel.com,
        linux-kernel@vger.kernel.org, willy@infradead.org,
        mhocko@kernel.org, linux-mm@kvack.org, vbabka@suse.cz,
        akpm@linux-foundation.org, mgorman@techsingularity.net,
        linux-arm-kernel@lists.infradead.org, osalvador@suse.de
Cc: yang.zhang.wz@gmail.com, pagupta@redhat.com,
        konrad.wilk@oracle.com, nitesh@redhat.com, riel@surriel.com,
        lcapitulino@redhat.com, wei.w.wang@intel.com, aarcange@redhat.com,
        pbonzini@redhat.com, dan.j.williams@intel.com,
        alexander.h.duyck@linux.intel.com
Date: Wed, 18 Sep 2019 10:52:25 -0700
Message-ID: <20190918175109.23474.67039.stgit@localhost.localdomain>
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
will not insert pages behind the reported_boundary.

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
---

Alexander Duyck (6):
      mm: Adjust shuffle code to allow for future coalescing
      mm: Use zone and order instead of free area in free_list manipulators
      mm: Introduce Reported pages
      mm: Add device side and notifier for unused page reporting
      virtio-balloon: Pull page poisoning config out of free page hinting
      virtio-balloon: Add support for providing unused page reports to host


 drivers/virtio/Kconfig              |    1 
 drivers/virtio/virtio_balloon.c     |   87 ++++++++-
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
 mm/page_reporting.h                 |  224 ++++++++++++++++++++++
 mm/shuffle.c                        |   12 +
 mm/shuffle.h                        |    6 +
 15 files changed, 893 insertions(+), 103 deletions(-)
 create mode 100644 include/linux/page_reporting.h
 create mode 100644 mm/page_reporting.c
 create mode 100644 mm/page_reporting.h

--
```
