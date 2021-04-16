

#### [PATCH v5 00/16] KVM: x86/pmu: Add basic support to enable guest PEBS
##### From: Like Xu <like.xu@linux.intel.com>

```c
From patchwork Thu Apr 15 03:20:00 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Like Xu <like.xu@linux.intel.com>
X-Patchwork-Id: 12204155
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-11.8 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,
	SPF_PASS,USER_AGENT_GIT autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 0ED80C433B4
	for <kvm@archiver.kernel.org>; Thu, 15 Apr 2021 03:20:25 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id B5EBB611F1
	for <kvm@archiver.kernel.org>; Thu, 15 Apr 2021 03:20:24 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S229743AbhDODUp (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Wed, 14 Apr 2021 23:20:45 -0400
Received: from mga11.intel.com ([192.55.52.93]:1119 "EHLO mga11.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S229729AbhDODUo (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 14 Apr 2021 23:20:44 -0400
IronPort-SDR: 
 MvtThNtlQbDIBqgp0OMkHAsK5PywN3eZ3bRp6GVDkbolpFm9AMcRf+DVXQU8otXgTojmwwrvuZ
 f9LTA9h4BaRg==
X-IronPort-AV: E=McAfee;i="6200,9189,9954"; a="191592800"
X-IronPort-AV: E=Sophos;i="5.82,223,1613462400";
   d="scan'208";a="191592800"
Received: from orsmga008.jf.intel.com ([10.7.209.65])
  by fmsmga102.fm.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 14 Apr 2021 20:20:22 -0700
IronPort-SDR: 
 rUVRvKC/Gm3Y4LS+iYj8dSpAzd5yzaHoxZL634jMBaF2PjGggWq3JduNDB7CQvIhw15ZY6uyU1
 Kmv8mFkj9MFA==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.82,223,1613462400";
   d="scan'208";a="425013845"
Received: from clx-ap-likexu.sh.intel.com ([10.239.48.108])
  by orsmga008.jf.intel.com with ESMTP; 14 Apr 2021 20:20:18 -0700
From: Like Xu <like.xu@linux.intel.com>
To: peterz@infradead.org, Paolo Bonzini <pbonzini@redhat.com>,
        Sean Christopherson <seanjc@google.com>
Cc: andi@firstfloor.org, kan.liang@linux.intel.com,
        wei.w.wang@intel.com, eranian@google.com, liuxiangdong5@huawei.com,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>, kvm@vger.kernel.org,
        x86@kernel.org, linux-kernel@vger.kernel.org,
        Like Xu <like.xu@linux.intel.com>
Subject: [PATCH v5 00/16] KVM: x86/pmu: Add basic support to enable guest PEBS
 via DS
Date: Thu, 15 Apr 2021 11:20:00 +0800
Message-Id: <20210415032016.166201-1-like.xu@linux.intel.com>
X-Mailer: git-send-email 2.30.2
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The guest Precise Event Based Sampling (PEBS) feature can provide
an architectural state of the instruction executed after the guest
instruction that exactly caused the event. It needs new hardware
facility only available on Intel Ice Lake Server platforms. This
patch set enables the basic PEBS feature for KVM guests on ICX.

We can use PEBS feature on the Linux guest like native:

  # perf record -e instructions:ppp ./br_instr a
  # perf record -c 100000 -e instructions:pp ./br_instr a

To emulate guest PEBS facility for the above perf usages,
we need to implement 2 code paths:

1) Fast path

This is when the host assigned physical PMC has an identical index as
the virtual PMC (e.g. using physical PMC0 to emulate virtual PMC0).
This path is used in most common use cases.

2) Slow path

This is when the host assigned physical PMC has a different index
from the virtual PMC (e.g. using physical PMC1 to emulate virtual PMC0)
In this case, KVM needs to rewrite the PEBS records to change the
applicable counter indexes to the virtual PMC indexes, which would
otherwise contain the physical counter index written by PEBS facility,
and switch the counter reset values to the offset corresponding to
the physical counter indexes in the DS data structure.

The previous version [0] enables both fast path and slow path, which
seems a bit more complex as the first step. In this patchset, we want
to start with the fast path to get the basic guest PEBS enabled while
keeping the slow path disabled. More focused discussion on the slow
path [1] is planned to be put to another patchset in the next step.

Compared to later versions in subsequent steps, the functionality
to support host-guest PEBS both enabled and the functionality to
emulate guest PEBS when the counter is cross-mapped are missing
in this patch set (neither of these are typical scenarios).

With the basic support, the guest can retrieve the correct PEBS
information from its own PEBS records on the Ice Lake servers.
And we expect it should work when migrating to another Ice Lake
and no regression about host perf is expected.

Here are the results of pebs test from guest/host for same workload:

perf report on guest:
# Samples: 2K of event 'instructions:ppp', # Event count (approx.): 1473377250
# Overhead  Command   Shared Object      Symbol
  57.74%  br_instr  br_instr           [.] lfsr_cond
  41.40%  br_instr  br_instr           [.] cmp_end
   0.21%  br_instr  [kernel.kallsyms]  [k] __lock_acquire

perf report on host:
# Samples: 2K of event 'instructions:ppp', # Event count (approx.): 1462721386
# Overhead  Command   Shared Object     Symbol
  57.90%  br_instr  br_instr          [.] lfsr_cond
  41.95%  br_instr  br_instr          [.] cmp_end
   0.05%  br_instr  [kernel.vmlinux]  [k] lock_acquire
   Conclusion: the profiling results on the guest are similar tothat on the host.

A minimum guest kernel version may be v5.4 or a backport version
support Icelake server PEBS.

Please check more details in each commit and feel free to comment.

Previous:
https://lore.kernel.org/kvm/20210329054137.120994-1-like.xu@linux.intel.com/

[0] https://lore.kernel.org/kvm/20210104131542.495413-1-like.xu@linux.intel.com/
[1] https://lore.kernel.org/kvm/20210115191113.nktlnmivc3edstiv@two.firstfloor.org/

v4->v5 Changelog:
- Rewrite intel_guest_get_msrs() to address Peter's comments;
- Fix coding style including indentation and {};
- Use __test_and_set_bit in the kvm_perf_overflow_intr();
- Return void for x86_pmu_handle_guest_pebs();
- Always drain pebs buffer on the host side;

Like Xu (16):
  perf/x86/intel: Add EPT-Friendly PEBS for Ice Lake Server
  perf/x86/intel: Handle guest PEBS overflow PMI for KVM guest
  perf/x86/core: Pass "struct kvm_pmu *" to determine the guest values
  KVM: x86/pmu: Set MSR_IA32_MISC_ENABLE_EMON bit when vPMU is enabled
  KVM: x86/pmu: Introduce the ctrl_mask value for fixed counter
  KVM: x86/pmu: Reprogram PEBS event to emulate guest PEBS counter
  KVM: x86/pmu: Add IA32_PEBS_ENABLE MSR emulation for extended PEBS
  KVM: x86/pmu: Add IA32_DS_AREA MSR emulation to support guest DS
  KVM: x86/pmu: Add PEBS_DATA_CFG MSR emulation to support adaptive PEBS
  KVM: x86: Set PEBS_UNAVAIL in IA32_MISC_ENABLE when PEBS is enabled
  KVM: x86/pmu: Adjust precise_ip to emulate Ice Lake guest PDIR counter
  KVM: x86/pmu: Move pmc_speculative_in_use() to arch/x86/kvm/pmu.h
  KVM: x86/pmu: Disable guest PEBS temporarily in two rare situations
  KVM: x86/pmu: Add kvm_pmu_cap to optimize perf_get_x86_pmu_capability
  KVM: x86/cpuid: Refactor host/guest CPU model consistency check
  KVM: x86/pmu: Expose CPUIDs feature bits PDCM, DS, DTES64

 arch/x86/events/core.c            |   5 +-
 arch/x86/events/intel/core.c      | 130 ++++++++++++++++++++++++------
 arch/x86/events/perf_event.h      |   5 +-
 arch/x86/include/asm/kvm_host.h   |  16 ++++
 arch/x86/include/asm/msr-index.h  |   6 ++
 arch/x86/include/asm/perf_event.h |   5 +-
 arch/x86/kvm/cpuid.c              |  24 ++----
 arch/x86/kvm/cpuid.h              |   5 ++
 arch/x86/kvm/pmu.c                |  50 +++++++++---
 arch/x86/kvm/pmu.h                |  38 +++++++++
 arch/x86/kvm/vmx/capabilities.h   |  26 ++++--
 arch/x86/kvm/vmx/pmu_intel.c      | 115 +++++++++++++++++++++-----
 arch/x86/kvm/vmx/vmx.c            |  24 +++++-
 arch/x86/kvm/vmx/vmx.h            |   2 +-
 arch/x86/kvm/x86.c                |  14 ++--
 15 files changed, 369 insertions(+), 96 deletions(-)
```
#### [PATCH V2 0/3] vDPA/ifcvf: enables Intel C5000X-PL virtio-blk
##### From: Zhu Lingshan <lingshan.zhu@intel.com>

```c
From patchwork Thu Apr 15 09:53:33 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Zhu Lingshan <lingshan.zhu@intel.com>
X-Patchwork-Id: 12204895
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-11.8 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,
	SPF_PASS,URIBL_BLOCKED,USER_AGENT_GIT autolearn=ham autolearn_force=no
	version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 95E62C433B4
	for <kvm@archiver.kernel.org>; Thu, 15 Apr 2021 09:58:59 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 66E65611AC
	for <kvm@archiver.kernel.org>; Thu, 15 Apr 2021 09:58:59 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S232142AbhDOJ7U (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Thu, 15 Apr 2021 05:59:20 -0400
Received: from mga12.intel.com ([192.55.52.136]:65315 "EHLO mga12.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S229457AbhDOJ7T (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 15 Apr 2021 05:59:19 -0400
IronPort-SDR: 
 Z+a5BHdyuOw9kXoLgxLf5dDheqs6L/XWCieqFwtV6lLHQroNN2ESPXNS3fp+heWrWhVLwsoJ7C
 tRHSwWBaBSmA==
X-IronPort-AV: E=McAfee;i="6200,9189,9954"; a="174321429"
X-IronPort-AV: E=Sophos;i="5.82,223,1613462400";
   d="scan'208";a="174321429"
Received: from orsmga008.jf.intel.com ([10.7.209.65])
  by fmsmga106.fm.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 15 Apr 2021 02:58:56 -0700
IronPort-SDR: 
 jFIvrl2mBHKk1u1E8zi7r3oVcQPKM0n00OAcUsbqGMuzeam9tumtafOOFqHz3+NpMQpkWDUfMz
 2cCMEZeWhSew==
X-IronPort-AV: E=Sophos;i="5.82,223,1613462400";
   d="scan'208";a="425123440"
Received: from unknown (HELO localhost.localdomain.bj.intel.com)
 ([10.240.193.73])
  by orsmga008-auth.jf.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 15 Apr 2021 02:58:52 -0700
From: Zhu Lingshan <lingshan.zhu@intel.com>
To: jasowang@redhat.com, mst@redhat.com, lulu@redhat.com,
        sgarzare@redhat.com
Cc: virtualization@lists.linux-foundation.org, netdev@vger.kernel.org,
        kvm@vger.kernel.org, linux-kernel@vger.kernel.org,
        Zhu Lingshan <lingshan.zhu@intel.com>
Subject: [PATCH V2 0/3] vDPA/ifcvf: enables Intel C5000X-PL virtio-blk
Date: Thu, 15 Apr 2021 17:53:33 +0800
Message-Id: <20210415095336.4792-1-lingshan.zhu@intel.com>
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
 drivers/vdpa/ifcvf/ifcvf_main.c | 58 +++++++++++++++++++++++++--------
 2 files changed, 52 insertions(+), 15 deletions(-)
```
#### [PATCH v5 0/6] KVM: arm64: Improve efficiency of stage2 page table
##### From: Yanan Wang <wangyanan55@huawei.com>

```c
From patchwork Thu Apr 15 11:50:26 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Yanan Wang <wangyanan55@huawei.com>
X-Patchwork-Id: 12205207
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-11.8 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,
	SPF_PASS,USER_AGENT_GIT autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 502CDC433ED
	for <kvm@archiver.kernel.org>; Thu, 15 Apr 2021 11:50:51 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 2A458613C3
	for <kvm@archiver.kernel.org>; Thu, 15 Apr 2021 11:50:51 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S232705AbhDOLvK (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Thu, 15 Apr 2021 07:51:10 -0400
Received: from szxga04-in.huawei.com ([45.249.212.190]:16123 "EHLO
        szxga04-in.huawei.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S232641AbhDOLvH (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 15 Apr 2021 07:51:07 -0400
Received: from DGGEMS407-HUB.china.huawei.com (unknown [172.30.72.60])
        by szxga04-in.huawei.com (SkyGuard) with ESMTP id 4FLcz764x4zpYXY;
        Thu, 15 Apr 2021 19:47:47 +0800 (CST)
Received: from DESKTOP-TMVL5KK.china.huawei.com (10.174.187.128) by
 DGGEMS407-HUB.china.huawei.com (10.3.19.207) with Microsoft SMTP Server id
 14.3.498.0; Thu, 15 Apr 2021 19:50:33 +0800
From: Yanan Wang <wangyanan55@huawei.com>
To: Marc Zyngier <maz@kernel.org>, Will Deacon <will@kernel.org>,
        "Quentin Perret" <qperret@google.com>,
        Alexandru Elisei <alexandru.elisei@arm.com>,
        <kvmarm@lists.cs.columbia.edu>,
        <linux-arm-kernel@lists.infradead.org>, <kvm@vger.kernel.org>,
        <linux-kernel@vger.kernel.org>
CC: Catalin Marinas <catalin.marinas@arm.com>,
        James Morse <james.morse@arm.com>,
        Julien Thierry <julien.thierry.kdev@gmail.com>,
        "Suzuki K Poulose" <suzuki.poulose@arm.com>,
        Gavin Shan <gshan@redhat.com>, <wanghaibin.wang@huawei.com>,
        <zhukeqian1@huawei.com>, <yuzenghui@huawei.com>,
        Yanan Wang <wangyanan55@huawei.com>
Subject: [PATCH v5 0/6] KVM: arm64: Improve efficiency of stage2 page table
Date: Thu, 15 Apr 2021 19:50:26 +0800
Message-ID: <20210415115032.35760-1-wangyanan55@huawei.com>
X-Mailer: git-send-email 2.8.4.windows.1
MIME-Version: 1.0
X-Originating-IP: [10.174.187.128]
X-CFilter-Loop: Reflected
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Hi,

This series makes some efficiency improvement of guest stage-2 page
table code, and there are some test results to quantify the benefit.
The code has been re-arranged based on the latest kvmarm/next tree.

Descriptions:
We currently uniformly permorm CMOs of D-cache and I-cache in function
user_mem_abort before calling the fault handlers. If we get concurrent
guest faults(e.g. translation faults, permission faults) or some really
unnecessary guest faults caused by BBM, CMOs for the first vcpu are
necessary while the others later are not.

By moving CMOs to the fault handlers, we can easily identify conditions
where they are really needed and avoid the unnecessary ones. As it's a
time consuming process to perform CMOs especially when flushing a block
range, so this solution reduces much load of kvm and improve efficiency
of the stage-2 page table code.

In this series, patch #1, #3, #4 make preparation for place movement
of CMOs (adapt to the latest stage-2 page table framework). And patch
#2, #5 move CMOs of D-cache and I-cache to the fault handlers. Patch
#6 introduces a new way to distinguish cases of memcache allocations.

The following are results in v3 to represent the benefit introduced
by movement of CMOs, and they were tested by [1] (kvm/selftest) that
I have posted recently.
[1] https://lore.kernel.org/lkml/20210302125751.19080-1-wangyanan55@huawei.com/

When there are muitiple vcpus concurrently accessing the same memory
region, we can test the execution time of KVM creating new mappings,
updating the permissions of old mappings from RO to RW, and the time
of re-creating the blocks after they have been split.

hardware platform: HiSilicon Kunpeng920 Server
host kernel: Linux mainline v5.12-rc2

cmdline: ./kvm_page_table_test -m 4 -s anonymous -b 1G -v 80
           (80 vcpus, 1G memory, page mappings(normal 4K))
KVM_CREATE_MAPPINGS: before 104.35s -> after  90.42s  +13.35%
KVM_UPDATE_MAPPINGS: before  78.64s -> after  75.45s  + 4.06%

cmdline: ./kvm_page_table_test -m 4 -s anonymous_thp -b 20G -v 40
           (40 vcpus, 20G memory, block mappings(THP 2M))
KVM_CREATE_MAPPINGS: before  15.66s -> after   6.92s  +55.80%
KVM_UPDATE_MAPPINGS: before 178.80s -> after 123.35s  +31.00%
KVM_REBUILD_BLOCKS:  before 187.34s -> after 131.76s  +30.65%

cmdline: ./kvm_page_table_test -m 4 -s anonymous_hugetlb_1gb -b 20G -v 40
           (40 vcpus, 20G memory, block mappings(HUGETLB 1G))
KVM_CREATE_MAPPINGS: before 104.54s -> after   3.70s  +96.46%
KVM_UPDATE_MAPPINGS: before 174.20s -> after 115.94s  +33.44%
KVM_REBUILD_BLOCKS:  before 103.95s -> after   2.96s  +97.15%
---

Changelogs:
v4->v5:
- rebased on the latest kvmarm/tree to adapt to the new stage-2 page-table code
- v4: https://lore.kernel.org/lkml/20210409033652.28316-1-wangyanan55@huawei.com/

v3->v4:
- perform D-cache flush if we are not mapping device memory
- rebased on top of mainline v5.12-rc6
- v3: https://lore.kernel.org/lkml/20210326031654.3716-1-wangyanan55@huawei.com/

v2->v3:
- drop patch #3 in v2
- retest v3 based on v5.12-rc2
- v2: https://lore.kernel.org/lkml/20210310094319.18760-1-wangyanan55@huawei.com/

v1->v2:
- rebased on top of mainline v5.12-rc2
- also move CMOs of I-cache to the fault handlers
- retest v2 based on v5.12-rc2
- v1: https://lore.kernel.org/lkml/20210208112250.163568-1-wangyanan55@huawei.com/

---

Yanan Wang (6):
  KVM: arm64: Introduce KVM_PGTABLE_S2_GUEST stage-2 flag
  KVM: arm64: Move D-cache flush to the fault handlers
  KVM: arm64: Add mm_ops member for structure stage2_attr_data
  KVM: arm64: Provide invalidate_icache_range at non-VHE EL2
  KVM: arm64: Move I-cache flush to the fault handlers
  KVM: arm64: Distinguish cases of memcache allocations completely

 arch/arm64/include/asm/kvm_mmu.h     | 31 -------------
 arch/arm64/include/asm/kvm_pgtable.h | 38 ++++++++++------
 arch/arm64/kvm/hyp/nvhe/cache.S      | 11 +++++
 arch/arm64/kvm/hyp/pgtable.c         | 65 +++++++++++++++++++++++-----
 arch/arm64/kvm/mmu.c                 | 51 ++++++++--------------
 5 files changed, 107 insertions(+), 89 deletions(-)
```
#### [PATCH v2 0/7] Hyper-V nested virt enlightenments for SVM
##### From: Vineeth Pillai <viremana@linux.microsoft.com>

```c
From patchwork Thu Apr 15 13:43:35 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Vineeth Pillai <viremana@linux.microsoft.com>
X-Patchwork-Id: 12205503
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-21.3 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT,USER_IN_DEF_DKIM_WL
	autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 31CDCC43460
	for <kvm@archiver.kernel.org>; Thu, 15 Apr 2021 13:44:00 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 0DA0E611F1
	for <kvm@archiver.kernel.org>; Thu, 15 Apr 2021 13:44:00 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S233398AbhDONoV (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Thu, 15 Apr 2021 09:44:21 -0400
Received: from linux.microsoft.com ([13.77.154.182]:41504 "EHLO
        linux.microsoft.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S233357AbhDONoS (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 15 Apr 2021 09:44:18 -0400
Received: from
 viremana-dev.fwjladdvyuiujdukmejncen4mf.xx.internal.cloudapp.net (unknown
 [13.66.132.26])
        by linux.microsoft.com (Postfix) with ESMTPSA id EB6D020B8001;
        Thu, 15 Apr 2021 06:43:54 -0700 (PDT)
DKIM-Filter: OpenDKIM Filter v2.11.0 linux.microsoft.com EB6D020B8001
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=linux.microsoft.com;
        s=default; t=1618494235;
        bh=f+72EpphKYDyWb2ni9IPH1kTpGV8sLOlwjys3mFfBxI=;
        h=From:To:Cc:Subject:Date:From;
        b=KkjRctg//cx736rviMBMko/DerhF/2bHx3YRxjgwH+KTq9v0c0jITUtNAKkvMbaHH
         I3Pp9qTlwLvjsXR53qZUFJlG4MIwku4JjZHaWDeXSYEM5e4Fsm59nhDU+XgK0/rflv
         eoFIjulbg0eh/ZZF/b+m7IuXBehE31DefmdLu4xA=
From: Vineeth Pillai <viremana@linux.microsoft.com>
To: Lan Tianyu <Tianyu.Lan@microsoft.com>,
        Michael Kelley <mikelley@microsoft.com>,
        Paolo Bonzini <pbonzini@redhat.com>,
        Sean Christopherson <seanjc@google.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>, Wei Liu <wei.liu@kernel.org>,
        Stephen Hemminger <sthemmin@microsoft.com>,
        Haiyang Zhang <haiyangz@microsoft.com>
Cc: Vineeth Pillai <viremana@linux.microsoft.com>,
        "H. Peter Anvin" <hpa@zytor.com>,
        Thomas Gleixner <tglx@linutronix.de>,
        Ingo Molnar <mingo@redhat.com>, Borislav Petkov <bp@alien8.de>,
        "K. Y. Srinivasan" <kys@microsoft.com>, x86@kernel.org,
        kvm@vger.kernel.org, linux-kernel@vger.kernel.org,
        linux-hyperv@vger.kernel.org
Subject: [PATCH v2 0/7] Hyper-V nested virt enlightenments for SVM
Date: Thu, 15 Apr 2021 13:43:35 +0000
Message-Id: <cover.1618492553.git.viremana@linux.microsoft.com>
X-Mailer: git-send-email 2.25.1
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This patch series enables the nested virtualization enlightenments for
SVM. This is very similar to the enlightenments for VMX except for the
fact that there is no enlightened VMCS. For SVM, VMCB is already an
architectural in-memory data structure.

The supported enlightenments are:

Enlightened TLB Flush: If this is enabled, ASID invalidations invalidate
only gva -> hpa entries. To flush entries derived from NPT, hyper-v
provided hypercalls (HvFlushGuestPhysicalAddressSpace or
HvFlushGuestPhysicalAddressList) should be used.

Enlightened MSR bitmap(TLFS 16.5.3): "When enabled, L0 hypervisor does
not monitor the MSR bitmaps for changes. Instead, the L1 hypervisor must
invalidate the corresponding clean field after making changes to one of
the MSR bitmaps."

Direct Virtual Flush(TLFS 16.8): The hypervisor exposes hypercalls
(HvFlushVirtualAddressSpace, HvFlushVirtualAddressSpaceEx,
HvFlushVirtualAddressList, and HvFlushVirtualAddressListEx) that allow
operating systems to more efficiently manage the virtual TLB. The L1
hypervisor can choose to allow its guest to use those hypercalls and
delegate the responsibility to handle them to the L0 hypervisor. This
requires the use of a partition assist page."

L2 Windows boot time was measured with and without the patch. Time was
measured from power on to the login screen and was averaged over a
consecutive 5 trials:
  Without the patch: 42 seconds
  With the patch: 29 seconds
---

Changes from v1:
- Move the remote TLB flush related fields from kvm_vcpu_hv and kvm_hv
  to kvm_vcpu_arch and kvm_arch.
- Modify the VMCB clean mask runtime based on whether L1 hypervisor
  is running on Hyper-V or not.
- Detect Hyper-V nested enlightenments based on
  HYPERV_CPUID_VENDOR_AND_MAX_FUNCTIONS.
- Address other minor review comments.
---

Vineeth Pillai (7):
  hyperv: Detect Nested virtualization support for SVM
  hyperv: SVM enlightened TLB flush support flag
  KVM: x86: hyper-v: Move the remote TLB flush logic out of vmx
  KVM: SVM: hyper-v: Nested enlightenments in VMCB
  KVM: SVM: hyper-v: Remote TLB flush for SVM
  KVM: SVM: hyper-v: Enlightened MSR-Bitmap support
  KVM: SVM: hyper-v: Direct Virtual Flush support

 arch/x86/include/asm/hyperv-tlfs.h |   9 +++
 arch/x86/include/asm/kvm_host.h    |  14 ++++
 arch/x86/include/asm/svm.h         |  24 +++++-
 arch/x86/kernel/cpu/mshyperv.c     |  10 ++-
 arch/x86/kvm/hyperv.c              |  87 +++++++++++++++++++++
 arch/x86/kvm/hyperv.h              |  20 +++++
 arch/x86/kvm/svm/svm.c             | 120 +++++++++++++++++++++++++++++
 arch/x86/kvm/svm/svm.h             |  30 +++++++-
 arch/x86/kvm/vmx/vmx.c             |  97 ++---------------------
 arch/x86/kvm/vmx/vmx.h             |  10 ---
 arch/x86/kvm/x86.c                 |   9 ++-
 11 files changed, 323 insertions(+), 107 deletions(-)
```
#### [PATCH v4 0/2] kvm/arm64: Try stage2 block mapping for host device
##### From: Keqian Zhu <zhukeqian1@huawei.com>

```c
From patchwork Thu Apr 15 14:03:26 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Keqian Zhu <zhukeqian1@huawei.com>
X-Patchwork-Id: 12205595
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-11.8 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,
	SPF_PASS,USER_AGENT_GIT autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 0B8C2C433ED
	for <kvm@archiver.kernel.org>; Thu, 15 Apr 2021 14:03:49 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id E354D613D8
	for <kvm@archiver.kernel.org>; Thu, 15 Apr 2021 14:03:48 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S233332AbhDOOEJ (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Thu, 15 Apr 2021 10:04:09 -0400
Received: from szxga06-in.huawei.com ([45.249.212.32]:16924 "EHLO
        szxga06-in.huawei.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S233238AbhDOOEI (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 15 Apr 2021 10:04:08 -0400
Received: from DGGEMS402-HUB.china.huawei.com (unknown [172.30.72.60])
        by szxga06-in.huawei.com (SkyGuard) with ESMTP id 4FLgxp6xd9zkjjr;
        Thu, 15 Apr 2021 22:01:50 +0800 (CST)
Received: from DESKTOP-5IS4806.china.huawei.com (10.174.187.224) by
 DGGEMS402-HUB.china.huawei.com (10.3.19.202) with Microsoft SMTP Server id
 14.3.498.0; Thu, 15 Apr 2021 22:03:33 +0800
From: Keqian Zhu <zhukeqian1@huawei.com>
To: <linux-kernel@vger.kernel.org>,
        <linux-arm-kernel@lists.infradead.org>, <kvm@vger.kernel.org>,
        <kvmarm@lists.cs.columbia.edu>, Marc Zyngier <maz@kernel.org>
CC: <wanghaibin.wang@huawei.com>
Subject: [PATCH v4 0/2] kvm/arm64: Try stage2 block mapping for host device
 MMIO
Date: Thu, 15 Apr 2021 22:03:26 +0800
Message-ID: <20210415140328.24200-1-zhukeqian1@huawei.com>
X-Mailer: git-send-email 2.8.4.windows.1
MIME-Version: 1.0
X-Originating-IP: [10.174.187.224]
X-CFilter-Loop: Reflected
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Hi,

We have two pathes to build stage2 mapping for MMIO regions.

Create time's path and stage2 fault path.

Patch#1 removes the creation time's mapping of MMIO regions
Patch#2 tries stage2 block mapping for host device MMIO at fault path

Changelog:

v4:
 - use get_vma_page_shift() handle all cases. (Marc)
 - get rid of force_pte for device mapping. (Marc)

v3:
 - Do not need to check memslot boundary in device_rough_page_shift(). (Marc)

Thanks,
Keqian


Keqian Zhu (2):
  kvm/arm64: Remove the creation time's mapping of MMIO regions
  kvm/arm64: Try stage2 block mapping for host device MMIO

 arch/arm64/kvm/mmu.c | 99 ++++++++++++++++++++++++--------------------
 1 file changed, 54 insertions(+), 45 deletions(-)
```
#### [PATCH v2 0/4] KVM statistics data fd-based binary interface
##### From: Jing Zhang <jingzhangos@google.com>

```c
From patchwork Thu Apr 15 15:17:37 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Jing Zhang <jingzhangos@google.com>
X-Patchwork-Id: 12205673
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-21.3 required=3.0 tests=BAYES_00,DKIMWL_WL_MED,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT,
	USER_IN_DEF_DKIM_WL autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id C1CC6C433ED
	for <kvm@archiver.kernel.org>; Thu, 15 Apr 2021 15:20:23 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 98C8561184
	for <kvm@archiver.kernel.org>; Thu, 15 Apr 2021 15:20:23 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S234204AbhDOPUm (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Thu, 15 Apr 2021 11:20:42 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:49184 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S236899AbhDOPUS (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 15 Apr 2021 11:20:18 -0400
Received: from mail-pf1-x449.google.com (mail-pf1-x449.google.com
 [IPv6:2607:f8b0:4864:20::449])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 10FFDC06138F
        for <kvm@vger.kernel.org>; Thu, 15 Apr 2021 08:17:45 -0700 (PDT)
Received: by mail-pf1-x449.google.com with SMTP id
 a16-20020aa786500000b0290257e9832af4so971321pfo.5
        for <kvm@vger.kernel.org>; Thu, 15 Apr 2021 08:17:45 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=date:message-id:mime-version:subject:from:to:cc;
        bh=rURblysS7kpTi9x8OxUlK9nhpB6vhBboGuvysGWXqRw=;
        b=qwVuZosddg0satSAHkPxr/aaneVDziK0pjqzjvPpzYyd+SSEXK6SULTE35ueUCjHrN
         l+w0Mh2h7+2aZC6eY1mOzHYVwWU+GhhFcFXsIJ5PxK6hhvMolFtcYb6teQ2ugZDS8yz/
         b0FHgvSS2lsZdAxl/Yfq6y6h/Hv9bD2bSAlnqTSzfATkOEqN1nl1h2l9tivwh7r9GE1f
         29Eb9eXira/eTJQmcRpROJZbiW9mxjYd8eF38EseaNoj67oiMWhelHbKRrskQ6g2fTWY
         +HikmUBXZeOGGfx12tmcLCf9lhN7jKRl6o/Ri3ag4QwxHLi/S6HtTbxqoSR0zGxQx9Nq
         24ZQ==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:date:message-id:mime-version:subject:from:to:cc;
        bh=rURblysS7kpTi9x8OxUlK9nhpB6vhBboGuvysGWXqRw=;
        b=f1Vdb4FDud4FSj4K1SL6ThM9jmhaYK4NNtWNwqTl3jxLAv6trpjzWp0LkwWzjPdkuM
         NZ2kN8IQnt7h96pX7OEYdVsvfGFnlfmXv5BpwcdQopZjqv2ej+ymhe7erTD+3hI1kzYh
         BlacIGWSC7fRYUCXLwJpY3T0lgMD5PELQ6Ixa0vvbGhncnDBC9UzMDi9X0z6fXz1deZD
         fzXHK+DihFS8LPQ4NA84ufSURsgDiWUXEGQjeKSO2CQuhQet2Wv/x6RsSWPTJlZHsfss
         mZRE8fob/YkFTaFdt2xOeWPrZO133mtcJlu9fc3NsFQuYdPIRzhEprWrH75ZfqlzY1bF
         llpA==
X-Gm-Message-State: AOAM53059xYKyqNxi0nAYgv7n14qc7vCfVSXMafCI763uqfHVxkJBcvo
        kMDdQvG5pRzreAXApinFaCBOkcSevH200AAMS+MM0ZpohDCx2HXrQDo51rwgv6H1LfU76BzKd1n
        WAzEaU+xy4kowXsgUm9vHc5h1vHryCH78ZaxYGgy6mu+rwvNn/nzxedUixsVQVrI8Tc9Ux3g=
X-Google-Smtp-Source: 
 ABdhPJyMwjuQSISfNP92ZO3vAT3rkA7W0fq6VXz1CTfac50JyTCuaWbGQONSE2dZOrNe3HMufpnoXv1hFXbgKqbE5w==
X-Received: from jgzg.c.googlers.com ([fda3:e722:ac3:10:7f:e700:c0a8:1acf])
 (user=jingzhangos job=sendgmr) by 2002:a05:6a00:1c67:b029:215:6f93:d220 with
 SMTP id s39-20020a056a001c67b02902156f93d220mr3521171pfw.36.1618499864440;
 Thu, 15 Apr 2021 08:17:44 -0700 (PDT)
Date: Thu, 15 Apr 2021 15:17:37 +0000
Message-Id: <20210415151741.1607806-1-jingzhangos@google.com>
Mime-Version: 1.0
X-Mailer: git-send-email 2.31.1.295.g9ea45b61b8-goog
Subject: [PATCH v2 0/4] KVM statistics data fd-based binary interface
From: Jing Zhang <jingzhangos@google.com>
To: KVM <kvm@vger.kernel.org>, KVMARM <kvmarm@lists.cs.columbia.edu>,
        LinuxMIPS <linux-mips@vger.kernel.org>,
        KVMPPC <kvm-ppc@vger.kernel.org>,
        LinuxS390 <linux-s390@vger.kernel.org>,
        Linuxkselftest <linux-kselftest@vger.kernel.org>,
        Paolo Bonzini <pbonzini@redhat.com>,
        Marc Zyngier <maz@kernel.org>,
        James Morse <james.morse@arm.com>,
        Julien Thierry <julien.thierry.kdev@gmail.com>,
        Suzuki K Poulose <suzuki.poulose@arm.com>,
        Will Deacon <will@kernel.org>,
        Huacai Chen <chenhuacai@kernel.org>,
        Aleksandar Markovic <aleksandar.qemu.devel@gmail.com>,
        Thomas Bogendoerfer <tsbogend@alpha.franken.de>,
        Paul Mackerras <paulus@ozlabs.org>,
        Christian Borntraeger <borntraeger@de.ibm.com>,
        Janosch Frank <frankja@linux.ibm.com>,
        David Hildenbrand <david@redhat.com>,
        Cornelia Huck <cohuck@redhat.com>,
        Claudio Imbrenda <imbrenda@linux.ibm.com>,
        Sean Christopherson <seanjc@google.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Jim Mattson <jmattson@google.com>,
        Peter Shier <pshier@google.com>,
        Oliver Upton <oupton@google.com>,
        David Rientjes <rientjes@google.com>,
        Emanuele Giuseppe Esposito <eesposit@redhat.com>
Cc: Jing Zhang <jingzhangos@google.com>
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This patchset provides a file descriptor for every VM and VCPU to read
KVM statistics data in binary format.
It is meant to provide a lightweight, flexible, scalable and efficient
lock-free solution for user space telemetry applications to pull the
statistics data periodically for large scale systems. The pulling
frequency could be as high as a few times per second.
In this patchset, every statistics data are treated to have some
attributes as below:
  * architecture dependent or common
  * VM statistics data or VCPU statistics data
  * type: cumulative, instantaneous,
  * unit: none for simple counter, nanosecond, microsecond,
    millisecond, second, Byte, KiByte, MiByte, GiByte. Clock Cycles
Since no lock/synchronization is used, the consistency between all
the statistics data is not guaranteed. That means not all statistics
data are read out at the exact same time, since the statistics date
are still being updated by KVM subsystems while they are read out.
---

* v1 -> v2
  - Use ARRAY_SIZE to count the number of stats descriptors
  - Fix missing `size` field initialization in macro STATS_DESC

[1] https://lore.kernel.org/kvm/20210402224359.2297157-1-jingzhangos@google.com

---

Jing Zhang (4):
  KVM: stats: Separate common stats from architecture specific ones
  KVM: stats: Add fd-based API to read binary stats data
  KVM: stats: Add documentation for statistics data binary interface
  KVM: selftests: Add selftest for KVM statistics data binary interface

 Documentation/virt/kvm/api.rst                | 169 ++++++++
 arch/arm64/include/asm/kvm_host.h             |   9 +-
 arch/arm64/kvm/guest.c                        |  42 +-
 arch/mips/include/asm/kvm_host.h              |   9 +-
 arch/mips/kvm/mips.c                          |  67 +++-
 arch/powerpc/include/asm/kvm_host.h           |   9 +-
 arch/powerpc/kvm/book3s.c                     |  68 +++-
 arch/powerpc/kvm/book3s_hv.c                  |  12 +-
 arch/powerpc/kvm/book3s_pr.c                  |   2 +-
 arch/powerpc/kvm/book3s_pr_papr.c             |   2 +-
 arch/powerpc/kvm/booke.c                      |  63 ++-
 arch/s390/include/asm/kvm_host.h              |   9 +-
 arch/s390/kvm/kvm-s390.c                      | 133 ++++++-
 arch/x86/include/asm/kvm_host.h               |   9 +-
 arch/x86/kvm/x86.c                            |  71 +++-
 include/linux/kvm_host.h                      | 132 ++++++-
 include/linux/kvm_types.h                     |  12 +
 include/uapi/linux/kvm.h                      |  48 +++
 tools/testing/selftests/kvm/.gitignore        |   1 +
 tools/testing/selftests/kvm/Makefile          |   3 +
 .../testing/selftests/kvm/include/kvm_util.h  |   3 +
 .../selftests/kvm/kvm_bin_form_stats.c        | 370 ++++++++++++++++++
 tools/testing/selftests/kvm/lib/kvm_util.c    |  11 +
 virt/kvm/kvm_main.c                           | 237 ++++++++++-
 24 files changed, 1401 insertions(+), 90 deletions(-)
 create mode 100644 tools/testing/selftests/kvm/kvm_bin_form_stats.c


base-commit: f96be2deac9bca3ef5a2b0b66b71fcef8bad586d
```
#### [PATCH v13 00/12] Add AMD SEV guest live migration support
##### From: Ashish Kalra <Ashish.Kalra@amd.com>
From: Ashish Kalra <ashish.kalra@amd.com>

```c
From patchwork Thu Apr 15 15:52:24 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Ashish Kalra <Ashish.Kalra@amd.com>
X-Patchwork-Id: 12205707
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-18.7 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_PATCH,
	MAILING_LIST_MULTI,MENTIONS_GIT_HOSTING,MSGID_FROM_MTA_HEADER,SPF_HELO_NONE,
	SPF_PASS,URIBL_BLOCKED,USER_AGENT_GIT autolearn=ham autolearn_force=no
	version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id BF830C433ED
	for <kvm@archiver.kernel.org>; Thu, 15 Apr 2021 15:52:41 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id A1A7E61184
	for <kvm@archiver.kernel.org>; Thu, 15 Apr 2021 15:52:41 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S233493AbhDOPxD (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Thu, 15 Apr 2021 11:53:03 -0400
Received: from mail-eopbgr680074.outbound.protection.outlook.com
 ([40.107.68.74]:19013
        "EHLO NAM04-BN3-obe.outbound.protection.outlook.com"
        rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org with ESMTP
        id S233052AbhDOPxC (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 15 Apr 2021 11:53:02 -0400
ARC-Seal: i=1; a=rsa-sha256; s=arcselector9901; d=microsoft.com; cv=none;
 b=Pl/yZryx3Rfs3uDcSSenwweh9ivoA2LSqZXzwJRrwsmMQR4Zh2z5n2gbAfdaaUQ/zrOfsO2bmpYzfBc0MD9eeeFdcoYN42CT+qY4MQ90pWXgoekPXdvfrZd1GRyPzhMxtUNmBGKYXb65soa41FhUtHJ+rxaC09iObMe/mBZ0CSBx6a+u8MqVoHqOLH0Y3mmd2H4D2iCjtzTVUKhKjsS8Y2APdtLL2by4tPe3rsFGZD0WBeApe+5oeEtshVuqq4xU6ChpWImoSKeMEZmPp3nAfhxsMhJ/4iRtaRcWx31+o0gS8V0qDZ8rL+SFBfuuHGsl+RTIzP8ds7H2YwaJ+VlF/g==
ARC-Message-Signature: i=1; a=rsa-sha256; c=relaxed/relaxed; d=microsoft.com;
 s=arcselector9901;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=rkPov7yNFIv2s1xvgHvt6gR5zuxPeuFMJ/UsJaWqFBI=;
 b=PdJqUHbDPiRy7EH60S027NVkBdHbGWquNouAQtJskHRcXL3P6JYp1zToNPMegtJe0NaFW8LGtjRlQQ/CNAollY7OuuPrtDWskM008lwfgWIMrpqKHeCt2GFzja4Kn72Pvlvo/5p/iJkiWHZYFsxVRx2UAqnrVx6bJBi/Fp1h0+GeuZMxjpnOaJih7RHwLTAbUc0BJ06pyMyJLTHPhSpmDM87hN9GbjmId58Os1Z1KeP3K5T1vb/oErvpPYMunhi0ew6L3MHaTzMKohLpPW+y8nz/7hBn8TwO0+UB85qt3AlEGaWEOAUqbXV2lRAXjxgoh/waOpuaHyCO41dml74XEQ==
ARC-Authentication-Results: i=1; mx.microsoft.com 1; spf=pass
 smtp.mailfrom=amd.com; dmarc=pass action=none header.from=amd.com; dkim=pass
 header.d=amd.com; arc=none
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=amd.com; s=selector1;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=rkPov7yNFIv2s1xvgHvt6gR5zuxPeuFMJ/UsJaWqFBI=;
 b=VjHJYAYXKy4+2LKbgd1zlOVpbkqBusffxR2eVUFiVdIi+uSQcKjDag8okWfJkp/rhmzDG9BFlOudbc99rbzLjtgKOJ125ERwjVQlUccZHsUByaszeCwhxKxRnq2SQKCyq3lgukuxgZabG0V3rCX4gI2oH+3BL29T3KkW3rzHvHQ=
Authentication-Results: redhat.com; dkim=none (message not signed)
 header.d=none;redhat.com; dmarc=none action=none header.from=amd.com;
Received: from SN6PR12MB2767.namprd12.prod.outlook.com (2603:10b6:805:75::23)
 by SN1PR12MB2366.namprd12.prod.outlook.com (2603:10b6:802:25::19) with
 Microsoft SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.4042.16; Thu, 15 Apr
 2021 15:52:37 +0000
Received: from SN6PR12MB2767.namprd12.prod.outlook.com
 ([fe80::1fb:7d59:2c24:615e]) by SN6PR12MB2767.namprd12.prod.outlook.com
 ([fe80::1fb:7d59:2c24:615e%6]) with mapi id 15.20.4042.018; Thu, 15 Apr 2021
 15:52:36 +0000
From: Ashish Kalra <Ashish.Kalra@amd.com>
To: pbonzini@redhat.com
Cc: tglx@linutronix.de, mingo@redhat.com, hpa@zytor.com,
        joro@8bytes.org, bp@suse.de, thomas.lendacky@amd.com,
        x86@kernel.org, kvm@vger.kernel.org, linux-kernel@vger.kernel.org,
        srutherford@google.com, seanjc@google.com,
        venu.busireddy@oracle.com, brijesh.singh@amd.com
Subject: [PATCH v13 00/12] Add AMD SEV guest live migration support
Date: Thu, 15 Apr 2021 15:52:24 +0000
Message-Id: <cover.1618498113.git.ashish.kalra@amd.com>
X-Mailer: git-send-email 2.17.1
X-Originating-IP: [165.204.77.1]
X-ClientProxiedBy: SN7PR04CA0210.namprd04.prod.outlook.com
 (2603:10b6:806:126::35) To SN6PR12MB2767.namprd12.prod.outlook.com
 (2603:10b6:805:75::23)
MIME-Version: 1.0
X-MS-Exchange-MessageSentRepresentingType: 1
Received: from ashkalra_ubuntu_server.amd.com (165.204.77.1) by
 SN7PR04CA0210.namprd04.prod.outlook.com (2603:10b6:806:126::35) with
 Microsoft SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.4042.18 via Frontend
 Transport; Thu, 15 Apr 2021 15:52:36 +0000
X-MS-PublicTrafficType: Email
X-MS-Office365-Filtering-Correlation-Id: e18c3092-f05f-46d4-f97f-08d900267d97
X-MS-TrafficTypeDiagnostic: SN1PR12MB2366:
X-MS-Exchange-Transport-Forked: True
X-Microsoft-Antispam-PRVS: 
 <SN1PR12MB2366EE3371E62374544310508E4D9@SN1PR12MB2366.namprd12.prod.outlook.com>
X-MS-Oob-TLC-OOBClassifiers: OLM:229;
X-MS-Exchange-SenderADCheck: 1
X-Microsoft-Antispam: BCL:0;
X-Microsoft-Antispam-Message-Info: 
 92bO5weH5i3Wlh+MFXbAGBPBPrXwwP+T9Ln0uKCyNskU6ur3sSHsXH2c146deR+m2yCvStgqyQ+ZVqGRCRqYJsHM1TlCJeZ2Pj8b+fjWL/P9mrj2i3eYQU7qSNSFwAJwuaimyDzGu6UiQBXxkSJgJL3dt1WBNCwyb1OexhH8OvKOLtPdzALY9z1O0j+l8VZiQZ6vUcIbCkJmZsdzHTZmIKV5onx52pkyV7on4K0Vhmr8ZIDTJ+s69HI4f/Ty0p6gadyFGaPZVUUwOX4Q4JSrol6vNy8643llbd8l4SnpCvBa4nITpBemWVijcx+oQaOezElzWZE3ao/yZ8cetI9vzEkiKKQQOKPoyUvYgQXyt5FMtgTauSYK82Ogy3ArIazAcDH9qV1P6ydY/u2RCwoDzGDU/K4akn24wfNB0MagytwcnZ8NkfU0kgx98SjEa50TysUDgsOKXNvBEBv6I/IbmVFOygAPXFVhCKGKI7agt8AkqzdsCQ9SRJkVg3lVnl1o+Bej+9+bKdHnmVhnIfu3cdAkeQ2awhBjMNLvir9947amLRsCnpuo4/BzRbHokw+N5Nrg26K0gcImrFDLIM548QT2ewVVCPC7tAeU6Vj+h+mW1NsPOHwlLpae8gcZZKYaP3r4kmkNf23ecPwFmiDDuhTxNcczDCaj1cKJsCrp/ZJSGDxQ3tWJr01RzXAic58a/UzFc9eFgVHduQs/ice/PX29D+Ej9v44Vsdv63osi28=
X-Forefront-Antispam-Report: 
 CIP:255.255.255.255;CTRY:;LANG:en;SCL:1;SRV:;IPV:NLI;SFV:NSPM;H:SN6PR12MB2767.namprd12.prod.outlook.com;PTR:;CAT:NONE;SFS:(4636009)(376002)(136003)(396003)(346002)(366004)(39860400002)(8936002)(16526019)(186003)(6916009)(6486002)(26005)(38350700002)(66946007)(38100700002)(966005)(8676002)(4326008)(5660300002)(2616005)(36756003)(956004)(316002)(83380400001)(478600001)(6666004)(2906002)(86362001)(52116002)(66556008)(7416002)(66476007)(7696005);DIR:OUT;SFP:1101;
X-MS-Exchange-AntiSpam-MessageData: =?utf-8?q?bOA8VQA4ZAcLT3jEPjYjNSstuZikKU?=
	=?utf-8?q?EMu/rJe0GAcPGZR9xPgFZQDppEturg2NxPKkTUNuBpSMdoDfwkV8XqULb+Y6jpptN?=
	=?utf-8?q?Y9++EGpqdsQ4qWzLbU20JjrnLmXcxVTvLAUEsrdxG8uZ95q3xSmKZO/jFXoTEm0fY?=
	=?utf-8?q?3NqBi0f6MERBwuWrVfxMT7JjEwngerVvINxRDMv1Kzzfeo3fUaoVqTBYpC4WA2/ub?=
	=?utf-8?q?qFRM6vE7soiFu+7JOEXPYpMTVbzPxmPmDHOS33GeLv8dZaA1jLwdQr4k3mQqnMSYS?=
	=?utf-8?q?cWGzXFjwFcrBNM6Z8AWRxppoo0k6Sw4jpqUqA2qM7iWKNdDyzsXZtp8+kczuGyj+M?=
	=?utf-8?q?UKTzWCQNTvBQPFwGd2uDPOzrGMA3FxpXkH9kd8w7qyJqzZVfoNSa2YisaZOd+lGRs?=
	=?utf-8?q?tUt4Dc8N+xt6lw9KnJ5yNLuo8tgVFV4c6bGzIY09JqnHgUSd3AD4a1WwS9CBKlc8+?=
	=?utf-8?q?V8JIZe6tiZT8y50DIOKmhpArlbcSY5AaKwbSI9BV3DeJt42oN5ch/pgWBYE/04hdX?=
	=?utf-8?q?DgtqnX30zH2JAzUn1rtzxxNQT5ow10qcU51J1Ww6qykylSRM0Yy0NLo+J8IvBDQvv?=
	=?utf-8?q?hh07msXFlpQCRGUHZ1KZyEZ0qDf3kVs/34YDpp7YiRD6OQLysyekxkfO37Dxp/eWb?=
	=?utf-8?q?BJ7HMgkE4QkgVmxgMSvdrmkM7NpyFeHHHM2znmgRfcljikZjcamPmZx+r3iJewITZ?=
	=?utf-8?q?KihQvLmFb9MPcy0qTNq6p2Qg2bj+CuwLkfGAYOvdx4PQ5AEeercjgngwAvLxxMvzT?=
	=?utf-8?q?Qw+upKemiFtUYpFDu+K/n8ZJaP7QfqCy6ba7OXMRw5d/UV6KbjJcPb1bKLS0pWtua?=
	=?utf-8?q?hi1k1kEwyiKYvOVehhIYZF9rLPUPDo/SO40V7nubPvsigdKN13QykqkDA56b7MWyp?=
	=?utf-8?q?CFvd54HTG1HfI0d5Pbjlv+HNDuJLQzHjCRZZUKEf0TI5uP3gJdiUwb2/fwtc++J2s?=
	=?utf-8?q?NDfrq1S2Z3I7+c7KQYfSlC8jhnWfOqHjV7ko1dGIl/5RRWopbwDvk7hSjXUPQBTrl?=
	=?utf-8?q?KYXZJWuGKiP3lo8NBkDFDEC3eZYDhMCftaZMAid63MDqISmYXTKKooPgoISyatVSp?=
	=?utf-8?q?NU+bgryr0iTxiqjInlaFk7d2I/Z2mf6g/vcW9k+MM7JD6zNJJj4nh+eVIKHieDEjx?=
	=?utf-8?q?7iqqbQjbgnzG6LiGPdPndXjlvQGz8SWV4SXtQ1MbDKcU7zuvG7hibqkW0FtPDIkAA?=
	=?utf-8?q?0IWcekIzZgRsx+g+mSIxgJyVqE/qjOOX2EUDVhk+Vo9WNjEOLBWWYFVnbWcWUED1J?=
	=?utf-8?q?HfK8MqJkbS4bNg?=
X-OriginatorOrg: amd.com
X-MS-Exchange-CrossTenant-Network-Message-Id: 
 e18c3092-f05f-46d4-f97f-08d900267d97
X-MS-Exchange-CrossTenant-AuthSource: SN6PR12MB2767.namprd12.prod.outlook.com
X-MS-Exchange-CrossTenant-AuthAs: Internal
X-MS-Exchange-CrossTenant-OriginalArrivalTime: 15 Apr 2021 15:52:36.7353
 (UTC)
X-MS-Exchange-CrossTenant-FromEntityHeader: Hosted
X-MS-Exchange-CrossTenant-Id: 3dd8961f-e488-4e60-8e11-a82d994e183d
X-MS-Exchange-CrossTenant-MailboxType: HOSTED
X-MS-Exchange-CrossTenant-UserPrincipalName: 
 xoVKtdaFjS5jZUXX6Tw6dHhdGAgGKLBqkCs0SJYCi3ROLVt90Pz1sW/6XirBLEZ26sgeOptxYYZhDtVn5NM40A==
X-MS-Exchange-Transport-CrossTenantHeadersStamped: SN1PR12MB2366
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Ashish Kalra <ashish.kalra@amd.com>

The series add support for AMD SEV guest live migration commands. To protect the
confidentiality of an SEV protected guest memory while in transit we need to
use the SEV commands defined in SEV API spec [1].

SEV guest VMs have the concept of private and shared memory. Private memory
is encrypted with the guest-specific key, while shared memory may be encrypted
with hypervisor key. The commands provided by the SEV FW are meant to be used
for the private memory only. The patch series introduces a new hypercall.
The guest OS can use this hypercall to notify the page encryption status.
If the page is encrypted with guest specific-key then we use SEV command during
the migration. If page is not encrypted then fallback to default.

The patch uses the KVM_EXIT_HYPERCALL exitcode and hypercall to
userspace exit functionality as a common interface from the guest back to the
VMM and passing on the guest shared/unencrypted page information to the
userspace VMM/Qemu. Qemu can consult this information during migration to know 
whether the page is encrypted.

This section descibes how the SEV live migration feature is negotiated
between the host and guest, the host indicates this feature support via 
KVM_FEATURE_CPUID. The guest firmware (OVMF) detects this feature and
sets a UEFI enviroment variable indicating OVMF support for live
migration, the guest kernel also detects the host support for this
feature via cpuid and in case of an EFI boot verifies if OVMF also
supports this feature by getting the UEFI enviroment variable and if it
set then enables live migration feature on host by writing to a custom
MSR, if not booted under EFI, then it simply enables the feature by
again writing to the custom MSR. The MSR is also handled by the
userspace VMM/Qemu.

A branch containing these patches is available here:
https://github.com/AMDESE/linux/tree/sev-migration-v13

[1] https://developer.amd.com/wp-content/resources/55766.PDF

Changes since v12:
- Reset page encryption status during early boot instead of just 
  before the kexec to avoid SMP races during kvm_pv_guest_cpu_reboot().
- Remove incorrect log message in case of non-EFI boot and implicit
  enabling of SEV live migration feature.

Changes since v11:
- Clean up and remove kvm_x86_ops callback for page_enc_status_hc and
  instead add a new per-VM flag to support/enable the page encryption
  status hypercall.
- Remove KVM_EXIT_DMA_SHARE/KVM_EXIT_DMA_UNSHARE exitcodes and instead
  use the KVM_EXIT_HYPERCALL exitcode for page encryption status
  hypercall to userspace functionality. 

Changes since v10:
- Adds new KVM_EXIT_DMA_SHARE/KVM_EXIT_DMA_UNSHARE hypercall to
  userspace exit functionality as a common interface from the guest back to the
  KVM and passing on the guest shared/unencrypted region information to the
  userspace VMM/Qemu. KVM/host kernel does not maintain the guest shared
  memory regions information anymore. 
- Remove implicit enabling of SEV live migration feature for an SEV
  guest, now this is explicitly in control of the userspace VMM/Qemu.
- Custom MSR handling is also now moved into userspace VMM/Qemu.
- As KVM does not maintain the guest shared memory region information
  anymore, sev_dbg_crypt() cannot bypass unencrypted guest memory
  regions without support from userspace VMM/Qemu.

Changes since v9:
- Transitioning from page encryption bitmap to the shared pages list
  to keep track of guest's shared/unencrypted memory regions.
- Move back to marking the complete _bss_decrypted section as 
  decrypted in the shared pages list.
- Invoke a new function check_kvm_sev_migration() via kvm_init_platform()
  for guest to query for host-side support for SEV live migration 
  and to enable the SEV live migration feature, to avoid
  #ifdefs in code 
- Rename MSR_KVM_SEV_LIVE_MIG_EN to MSR_KVM_SEV_LIVE_MIGRATION.
- Invoke a new function handle_unencrypted_region() from 
  sev_dbg_crypt() to bypass unencrypted guest memory regions.

Changes since v8:
- Rebasing to kvm next branch.
- Fixed and added comments as per review feedback on v8 patches.
- Removed implicitly enabling live migration for incoming VMs in
  in KVM_SET_PAGE_ENC_BITMAP, it is now done via KVM_SET_MSR ioctl.
- Adds support for bypassing unencrypted guest memory regions for
  DBG_DECRYPT API calls, guest memory region encryption status in
  sev_dbg_decrypt() is referenced using the page encryption bitmap.

Changes since v7:
- Removed the hypervisor specific hypercall/paravirt callback for
  SEV live migration and moved back to calling kvm_sev_hypercall3 
  directly.
- Fix build errors as
  Reported-by: kbuild test robot <lkp@intel.com>, specifically fixed
  build error when CONFIG_HYPERVISOR_GUEST=y and
  CONFIG_AMD_MEM_ENCRYPT=n.
- Implicitly enabled live migration for incoming VM(s) to handle 
  A->B->C->... VM migrations.
- Fixed Documentation as per comments on v6 patches.
- Fixed error return path in sev_send_update_data() as per comments 
  on v6 patches. 

Changes since v6:
- Rebasing to mainline and refactoring to the new split SVM
  infrastructre.
- Move to static allocation of the unified Page Encryption bitmap
  instead of the dynamic resizing of the bitmap, the static allocation
  is done implicitly by extending kvm_arch_commit_memory_region() callack
  to add svm specific x86_ops which can read the userspace provided memory
  region/memslots and calculate the amount of guest RAM managed by the KVM
  and grow the bitmap.
- Fixed KVM_SET_PAGE_ENC_BITMAP ioctl to set the whole bitmap instead
  of simply clearing specific bits.
- Removed KVM_PAGE_ENC_BITMAP_RESET ioctl, which is now performed using
  KVM_SET_PAGE_ENC_BITMAP.
- Extended guest support for enabling Live Migration feature by adding a
  check for UEFI environment variable indicating OVMF support for Live
  Migration feature and additionally checking for KVM capability for the
  same feature. If not booted under EFI, then we simply check for KVM
  capability.
- Add hypervisor specific hypercall for SEV live migration by adding
  a new paravirt callback as part of x86_hyper_runtime.
  (x86 hypervisor specific runtime callbacks)
- Moving MSR handling for MSR_KVM_SEV_LIVE_MIG_EN into svm/sev code 
  and adding check for SEV live migration enabled by guest in the 
  KVM_GET_PAGE_ENC_BITMAP ioctl.
- Instead of the complete __bss_decrypted section, only specific variables
  such as hv_clock_boot and wall_clock are marked as decrypted in the
  page encryption bitmap

Changes since v5:
- Fix build errors as
  Reported-by: kbuild test robot <lkp@intel.com>

Changes since v4:
- Host support has been added to extend KVM capabilities/feature bits to 
  include a new KVM_FEATURE_SEV_LIVE_MIGRATION, which the guest can
  query for host-side support for SEV live migration and a new custom MSR
  MSR_KVM_SEV_LIVE_MIG_EN is added for guest to enable the SEV live
  migration feature.
- Ensure that _bss_decrypted section is marked as decrypted in the
  page encryption bitmap.
- Fixing KVM_GET_PAGE_ENC_BITMAP ioctl to return the correct bitmap
  as per the number of pages being requested by the user. Ensure that
  we only copy bmap->num_pages bytes in the userspace buffer, if
  bmap->num_pages is not byte aligned we read the trailing bits
  from the userspace and copy those bits as is. This fixes guest
  page(s) corruption issues observed after migration completion.
- Add kexec support for SEV Live Migration to reset the host's
  page encryption bitmap related to kernel specific page encryption
  status settings before we load a new kernel by kexec. We cannot
  reset the complete page encryption bitmap here as we need to
  retain the UEFI/OVMF firmware specific settings.

Changes since v3:
- Rebasing to mainline and testing.
- Adding a new KVM_PAGE_ENC_BITMAP_RESET ioctl, which resets the 
  page encryption bitmap on a guest reboot event.
- Adding a more reliable sanity check for GPA range being passed to
  the hypercall to ensure that guest MMIO ranges are also marked
  in the page encryption bitmap.

Changes since v2:
 - reset the page encryption bitmap on vcpu reboot

Changes since v1:
 - Add support to share the page encryption between the source and target
   machine.
 - Fix review feedbacks from Tom Lendacky.
 - Add check to limit the session blob length.
 - Update KVM_GET_PAGE_ENC_BITMAP icotl to use the base_gfn instead of
   the memory slot when querying the bitmap.

Ashish Kalra (4):
  KVM: X86: Introduce KVM_HC_PAGE_ENC_STATUS hypercall
  KVM: x86: Introduce new KVM_FEATURE_SEV_LIVE_MIGRATION feature &
    Custom MSR.
  EFI: Introduce the new AMD Memory Encryption GUID.
  x86/kvm: Add guest support for detecting and enabling SEV Live
    Migration feature.

Brijesh Singh (8):
  KVM: SVM: Add KVM_SEV SEND_START command
  KVM: SVM: Add KVM_SEND_UPDATE_DATA command
  KVM: SVM: Add KVM_SEV_SEND_FINISH command
  KVM: SVM: Add support for KVM_SEV_RECEIVE_START command
  KVM: SVM: Add KVM_SEV_RECEIVE_UPDATE_DATA command
  KVM: SVM: Add KVM_SEV_RECEIVE_FINISH command
  KVM: x86: Add AMD SEV specific Hypercall3
  mm: x86: Invoke hypercall when page encryption status is changed

 .../virt/kvm/amd-memory-encryption.rst        | 120 +++++
 Documentation/virt/kvm/cpuid.rst              |   5 +
 Documentation/virt/kvm/hypercalls.rst         |  15 +
 Documentation/virt/kvm/msr.rst                |  12 +
 arch/x86/include/asm/kvm_host.h               |   2 +
 arch/x86/include/asm/kvm_para.h               |  12 +
 arch/x86/include/asm/mem_encrypt.h            |   8 +
 arch/x86/include/asm/paravirt.h               |  10 +
 arch/x86/include/asm/paravirt_types.h         |   2 +
 arch/x86/include/uapi/asm/kvm_para.h          |   4 +
 arch/x86/kernel/kvm.c                         |  55 +++
 arch/x86/kernel/paravirt.c                    |   1 +
 arch/x86/kvm/cpuid.c                          |   3 +-
 arch/x86/kvm/svm/sev.c                        | 454 ++++++++++++++++++
 arch/x86/kvm/x86.c                            |  29 ++
 arch/x86/mm/mem_encrypt.c                     | 121 ++++-
 arch/x86/mm/pat/set_memory.c                  |   7 +
 include/linux/efi.h                           |   1 +
 include/linux/psp-sev.h                       |   8 +-
 include/uapi/linux/kvm.h                      |  39 ++
 include/uapi/linux/kvm_para.h                 |   1 +
 21 files changed, 903 insertions(+), 6 deletions(-)
```
#### [PATCH v3 0/9] KVM: Fix tick-based accounting for x86 guests
##### From: Sean Christopherson <seanjc@google.com>

```c
From patchwork Thu Apr 15 22:20:57 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Sean Christopherson <seanjc@google.com>
X-Patchwork-Id: 12206181
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-21.3 required=3.0 tests=BAYES_00,DKIMWL_WL_MED,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT,
	USER_IN_DEF_DKIM_WL autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id E58BAC433B4
	for <kvm@archiver.kernel.org>; Thu, 15 Apr 2021 22:21:16 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id C188B610FB
	for <kvm@archiver.kernel.org>; Thu, 15 Apr 2021 22:21:16 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S236376AbhDOWVi (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Thu, 15 Apr 2021 18:21:38 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:57124 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S234969AbhDOWVi (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 15 Apr 2021 18:21:38 -0400
Received: from mail-qk1-x749.google.com (mail-qk1-x749.google.com
 [IPv6:2607:f8b0:4864:20::749])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id B4FC5C061574
        for <kvm@vger.kernel.org>; Thu, 15 Apr 2021 15:21:14 -0700 (PDT)
Received: by mail-qk1-x749.google.com with SMTP id g186so2474696qke.23
        for <kvm@vger.kernel.org>; Thu, 15 Apr 2021 15:21:14 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=reply-to:date:message-id:mime-version:subject:from:to:cc;
        bh=idyJBHB3aj+yzlWK6cDPev1Rpg8zeSoDNtXngbtjsz4=;
        b=AZh7zKKHUCfrzkZWZ/vE2t7RwQ1yja5O9PUCkcECAY1mEd/FGtO7mtGxl7i/Trs0me
         mNt4tcvic4/HAMsK9m1FuKs88rViIm6MWc4VeQKZMLlsGDDlslg5ZIa0/wMgHOo4/Ozf
         WIDfgqoHY0+CdRlDEz+xAJfUR76aPM4qEbT0LVK/7/Q/UrvBPkQiA0dnTPXUbbxUCTTL
         T+/U28uiY5qkFjV6G3tLJ7P74lu8kTqnMC9Mpb/Gbdxf6ZzR0loNJQIqIL0d6CzkGi8Z
         YkL9Q5Md/3j1vELZNuE+2vV98dK3eVc8yMKVGbAFStESq99YYHoMxLKJxZTn5UKQMcGG
         l6mg==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:reply-to:date:message-id:mime-version:subject
         :from:to:cc;
        bh=idyJBHB3aj+yzlWK6cDPev1Rpg8zeSoDNtXngbtjsz4=;
        b=kCIvPDQe7x8MrGvFYJ1esyBeYpwrFlA3GZ6WzkMjkn3y9D7Pf2EkA5AoS4DTqSTp1r
         PI7XjNjtSNFftXcgdOFNiq14gv3lvTkIvKw2itAYKwbBIXvbZpCO6HMQbXmYeBQFSA4M
         /HA8s3utRsJQTRacmgeEigATlv19T3XYqtLH2z+K1Dd4qQvlAledzn8NVMMW9+yIT+Kj
         JWtPN6OEzTv4wunJulr5aE5KDzQshqpm6w8yLCSjpF44dtyVHswWHqiymBhHk2FIOXiA
         6tfc6kZZ3Rb0udm5aXyNr5/X5vdzvfh4L1kzAwQ+JT0DTmcrkz1kKKFARu2DlLp1KkNS
         CC6A==
X-Gm-Message-State: AOAM532eBz97iknq+GvtlDLIVU1QV5zKx6eMSj42H5MV2lv+ClRKuWjm
        UiAnxx4U0UOHs7meHmYG2Ebpsnaquio=
X-Google-Smtp-Source: 
 ABdhPJyzq2DFbJV2Asv7A8wZh4pNHIG7vnTBd4k7SUprsKaon5I87ZlHqAwJcVNXzpddgQHCsOALUImGaec=
X-Received: from seanjc798194.pdx.corp.google.com
 ([2620:15c:f:10:6c93:ada0:6bbf:e7db])
 (user=seanjc job=sendgmr) by 2002:a0c:d605:: with SMTP id
 c5mr5279271qvj.25.1618525273925;
 Thu, 15 Apr 2021 15:21:13 -0700 (PDT)
Reply-To: Sean Christopherson <seanjc@google.com>
Date: Thu, 15 Apr 2021 15:20:57 -0700
Message-Id: <20210415222106.1643837-1-seanjc@google.com>
Mime-Version: 1.0
X-Mailer: git-send-email 2.31.1.368.gbe11c130af-goog
Subject: [PATCH v3 0/9] KVM: Fix tick-based accounting for x86 guests
From: Sean Christopherson <seanjc@google.com>
To: Paolo Bonzini <pbonzini@redhat.com>
Cc: Sean Christopherson <seanjc@google.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org, Thomas Gleixner <tglx@linutronix.de>,
        Michael Tokarev <mjt@tls.msk.ru>,
        Christian Borntraeger <borntraeger@de.ibm.com>
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This is a continuation of Wanpeng's series[1] to fix tick-based CPU time
accounting on x86, with my cleanups[2] bolted on top.  The core premise of
Wanpeng's patches are preserved, but they are heavily stripped down.
Specifically, only the "guest exit" paths are split, and no code is
consolidated.  The intent is to do as little as possible in the three
patches that need to be backported.  Keeping those changes as small as
possible also meant that my cleanups did not need to unwind much 
refactoring.

On x86, tested CONFIG_VIRT_CPU_ACCOUNTING_GEN =y and =n, and with
CONFIG_DEBUG_ENTRY=y && CONFIG_VALIDATE_STACKS=y.  Compile tested arm64,
MIPS, PPC, and s390, the latter with CONFIG_DEBUG_ENTRY=y for giggles.

One last note: I elected to use vtime_account_guest_exit() in the x86 code
instead of open coding these equivalents:

	if (vtime_accounting_enabled_this_cpu())
		vtime_guest_exit(current);
...
	if (!vtime_accounting_enabled_this_cpu())
		current->flags &= ~PF_VCPU;

With CONFIG_VIRT_CPU_ACCOUNTING_GEN=n, this is a complete non-issue, but
for the =y case it means context_tracking_enabled_this_cpu() is being
checked back-to-back.  The redundant checks bug me, but open coding the
gory details in x86 or providing funky variants in vtime.h felt worse.

Delta from Wanpeng's v2:

  - s/context_guest/context_tracking_guest, purely to match the existing
    functions.  I have no strong opinion either way.
  - Split only the "exit" functions.
  - Partially open code vcpu_account_guest_exit() and
    __vtime_account_guest_exit() in x86 to avoid churn when segueing into
    my cleanups (see above).

[1] https://lkml.kernel.org/r/1618298169-3831-1-git-send-email-wanpengli@tencent.com
[2] https://lkml.kernel.org/r/20210413182933.1046389-1-seanjc@google.com

Sean Christopherson (6):
  sched/vtime: Move vtime accounting external declarations above inlines
  sched/vtime: Move guest enter/exit vtime accounting to vtime.h
  context_tracking: Consolidate guest enter/exit wrappers
  context_tracking: KVM: Move guest enter/exit wrappers to KVM's domain
  KVM: x86: Consolidate guest enter/exit logic to common helpers
  KVM: Move instrumentation-safe annotations for enter/exit to x86 code

Wanpeng Li (3):
  context_tracking: Move guest exit context tracking to separate helpers
  context_tracking: Move guest exit vtime accounting to separate helpers
  KVM: x86: Defer tick-based accounting 'til after IRQ handling

 arch/x86/kvm/svm/svm.c           |  39 +--------
 arch/x86/kvm/vmx/vmx.c           |  39 +--------
 arch/x86/kvm/x86.c               |   8 ++
 arch/x86/kvm/x86.h               |  52 ++++++++++++
 include/linux/context_tracking.h |  92 ++++-----------------
 include/linux/kvm_host.h         |  38 +++++++++
 include/linux/vtime.h            | 138 +++++++++++++++++++------------
 7 files changed, 204 insertions(+), 202 deletions(-)
```
