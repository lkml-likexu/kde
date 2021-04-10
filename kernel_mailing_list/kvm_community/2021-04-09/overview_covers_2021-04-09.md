

#### [PATCH v4 0/2] KVM: arm64: Improve efficiency of stage2 page table
##### From: Yanan Wang <wangyanan55@huawei.com>

```c
From patchwork Fri Apr  9 03:36:50 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: "wangyanan (Y)" <wangyanan55@huawei.com>
X-Patchwork-Id: 12192913
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-11.8 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,
	SPF_PASS,USER_AGENT_GIT autolearn=unavailable autolearn_force=no
 version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 39D9DC433ED
	for <kvm@archiver.kernel.org>; Fri,  9 Apr 2021 03:38:04 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 1C41561178
	for <kvm@archiver.kernel.org>; Fri,  9 Apr 2021 03:38:04 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S233241AbhDIDiO (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Thu, 8 Apr 2021 23:38:14 -0400
Received: from szxga07-in.huawei.com ([45.249.212.35]:16854 "EHLO
        szxga07-in.huawei.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S233180AbhDIDiL (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 8 Apr 2021 23:38:11 -0400
Received: from DGGEMS407-HUB.china.huawei.com (unknown [172.30.72.60])
        by szxga07-in.huawei.com (SkyGuard) with ESMTP id 4FGkK515WQz9xgL;
        Fri,  9 Apr 2021 11:34:49 +0800 (CST)
Received: from DESKTOP-TMVL5KK.china.huawei.com (10.174.187.128) by
 DGGEMS407-HUB.china.huawei.com (10.3.19.207) with Microsoft SMTP Server id
 14.3.498.0; Fri, 9 Apr 2021 11:36:54 +0800
From: Yanan Wang <wangyanan55@huawei.com>
To: Marc Zyngier <maz@kernel.org>, Will Deacon <will@kernel.org>,
        "Alexandru Elisei" <alexandru.elisei@arm.com>,
        Catalin Marinas <catalin.marinas@arm.com>,
        <kvmarm@lists.cs.columbia.edu>,
        <linux-arm-kernel@lists.infradead.org>, <kvm@vger.kernel.org>,
        <linux-kernel@vger.kernel.org>
CC: James Morse <james.morse@arm.com>,
        Julien Thierry <julien.thierry.kdev@gmail.com>,
        Suzuki K Poulose <suzuki.poulose@arm.com>,
        Gavin Shan <gshan@redhat.com>,
        Quentin Perret <qperret@google.com>,
        <wanghaibin.wang@huawei.com>, <zhukeqian1@huawei.com>,
        <yuzenghui@huawei.com>, Yanan Wang <wangyanan55@huawei.com>
Subject: [PATCH v4 0/2] KVM: arm64: Improve efficiency of stage2 page table
Date: Fri, 9 Apr 2021 11:36:50 +0800
Message-ID: <20210409033652.28316-1-wangyanan55@huawei.com>
X-Mailer: git-send-email 2.8.4.windows.1
MIME-Version: 1.0
X-Originating-IP: [10.174.187.128]
X-CFilter-Loop: Reflected
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Hi,

This series makes some efficiency improvement of stage2 page table code,
and there are some test results to quantify the benefit of each patch.

Changelogs:
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

About this v4 series:
Patch #1:
We currently uniformly permorm CMOs of D-cache and I-cache in function
user_mem_abort before calling the fault handlers. If we get concurrent
guest faults(e.g. translation faults, permission faults) or some really
unnecessary guest faults caused by BBM, CMOs for the first vcpu are
necessary while the others later are not.

By moving CMOs to the fault handlers, we can easily identify conditions
where they are really needed and avoid the unnecessary ones. As it's a
time consuming process to perform CMOs especially when flushing a block
range, so this solution reduces much load of kvm and improve efficiency
of the page table code.

So let's move both clean of D-cache and invalidation of I-cache to the
map path and move only invalidation of I-cache to the permission path.
Since the original APIs for CMOs in mmu.c are only called in function
user_mem_abort, we now also move them to pgtable.c.

After this patch, in function stage2_map_walker_try_leaf (map path),
we flush D-cache if we are not mapping device memory and invalidate
I-cache if we are adding executable permission. And in the function
stage2_attr_walker (permission path), we invalidate I-cache if we are
adding executable permission. The logic is consistent with current
code in user_mem_abort (without this patch).

The following results represent the benefit of patch #1 alone, and they
were tested by [1] (kvm/selftest) that I have posted recently.
[1] https://lore.kernel.org/lkml/20210302125751.19080-1-wangyanan55@huawei.com/

When there are muitiple vcpus concurrently accessing the same memory region,
we can test the execution time of KVM creating new mappings, updating the
permissions of old mappings from RO to RW, and rebuilding the blocks after
they have been split.

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

Patch #2:
A new method to distinguish cases of memcache allocations is introduced.
By comparing fault_granule and vma_pagesize, cases that require allocations
from memcache and cases that don't can be distinguished completely.

Yanan Wang (2):
  KVM: arm64: Move CMOs from user_mem_abort to the fault handlers
  KVM: arm64: Distinguish cases of memcache allocations completely

 arch/arm64/include/asm/kvm_mmu.h | 31 ---------------
 arch/arm64/kvm/hyp/pgtable.c     | 68 +++++++++++++++++++++++++-------
 arch/arm64/kvm/mmu.c             | 48 ++++++++--------------
 3 files changed, 69 insertions(+), 78 deletions(-)
```
#### [RFC PATCH v3 0/8] Add IOPF support for VFIO passthrough
##### From: Shenming Lu <lushenming@huawei.com>

```c
From patchwork Fri Apr  9 03:44:12 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Shenming Lu <lushenming@huawei.com>
X-Patchwork-Id: 12192931
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.8 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_PATCH,MAILING_LIST_MULTI,
	MENTIONS_GIT_HOSTING,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT
	autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id CE901C43462
	for <kvm@archiver.kernel.org>; Fri,  9 Apr 2021 03:44:46 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id A996E61042
	for <kvm@archiver.kernel.org>; Fri,  9 Apr 2021 03:44:46 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S233253AbhDIDo5 (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Thu, 8 Apr 2021 23:44:57 -0400
Received: from szxga04-in.huawei.com ([45.249.212.190]:15637 "EHLO
        szxga04-in.huawei.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S232662AbhDIDoz (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 8 Apr 2021 23:44:55 -0400
Received: from DGGEMS414-HUB.china.huawei.com (unknown [172.30.72.59])
        by szxga04-in.huawei.com (SkyGuard) with ESMTP id 4FGkTF20x7znZ7c;
        Fri,  9 Apr 2021 11:41:53 +0800 (CST)
Received: from DESKTOP-7FEPK9S.china.huawei.com (10.174.184.135) by
 DGGEMS414-HUB.china.huawei.com (10.3.19.214) with Microsoft SMTP Server id
 14.3.498.0; Fri, 9 Apr 2021 11:44:30 +0800
From: Shenming Lu <lushenming@huawei.com>
To: Alex Williamson <alex.williamson@redhat.com>,
        Cornelia Huck <cohuck@redhat.com>,
        Will Deacon <will@kernel.org>,
        Robin Murphy <robin.murphy@arm.com>,
        Joerg Roedel <joro@8bytes.org>,
        Jean-Philippe Brucker <jean-philippe@linaro.org>,
        Eric Auger <eric.auger@redhat.com>, <kvm@vger.kernel.org>,
        <linux-kernel@vger.kernel.org>,
        <linux-arm-kernel@lists.infradead.org>,
        <iommu@lists.linux-foundation.org>, <linux-api@vger.kernel.org>
CC: Kevin Tian <kevin.tian@intel.com>,
        Lu Baolu <baolu.lu@linux.intel.com>, <yi.l.liu@intel.com>,
        Christoph Hellwig <hch@infradead.org>,
        Jonathan Cameron <Jonathan.Cameron@huawei.com>,
        Barry Song <song.bao.hua@hisilicon.com>,
        <wanghaibin.wang@huawei.com>, <yuzenghui@huawei.com>,
        <lushenming@huawei.com>
Subject: [RFC PATCH v3 0/8] Add IOPF support for VFIO passthrough
Date: Fri, 9 Apr 2021 11:44:12 +0800
Message-ID: <20210409034420.1799-1-lushenming@huawei.com>
X-Mailer: git-send-email 2.27.0.windows.1
MIME-Version: 1.0
X-Originating-IP: [10.174.184.135]
X-CFilter-Loop: Reflected
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Hi,

Requesting for your comments and suggestions. :-)

The static pinning and mapping problem in VFIO and possible solutions
have been discussed a lot [1, 2]. One of the solutions is to add I/O
Page Fault support for VFIO devices. Different from those relatively
complicated software approaches such as presenting a vIOMMU that provides
the DMA buffer information (might include para-virtualized optimizations),
IOPF mainly depends on the hardware faulting capability, such as the PCIe
PRI extension or Arm SMMU stall model. What's more, the IOPF support in
the IOMMU driver has already been implemented in SVA [3]. So we add IOPF
support for VFIO passthrough based on the IOPF part of SVA in this series.

We have measured its performance with UADK [4] (passthrough an accelerator
to a VM(1U16G)) on Hisilicon Kunpeng920 board (and compared with host SVA):

Run hisi_sec_test...
 - with varying sending times and message lengths
 - with/without IOPF enabled (speed slowdown)

when msg_len = 1MB (and PREMAP_LEN (in Patch 4) = 1):
            slowdown (num of faults)
 times      VFIO IOPF      host SVA
 1          63.4% (518)    82.8% (512)
 100        22.9% (1058)   47.9% (1024)
 1000       2.6% (1071)    8.5% (1024)

when msg_len = 10MB (and PREMAP_LEN = 512):
            slowdown (num of faults)
 times      VFIO IOPF
 1          32.6% (13)
 100        3.5% (26)
 1000       1.6% (26)

History:

v2 -> v3
 - Nit fixes.
 - No reason to disable reporting the unrecoverable faults. (baolu)
 - Maintain a global IOPF enabled group list.
 - Split the pre-mapping optimization to be a separate patch.
 - Add selective faulting support (use vfio_pin_pages to indicate the
   non-faultable scope and add a new struct vfio_range to record it,
   untested). (Kevin)

v1 -> v2
 - Numerous improvements following the suggestions. Thanks a lot to all
   of you.

Note that PRI is not supported at the moment since there is no hardware.

Links:
[1] Lesokhin I, et al. Page Fault Support for Network Controllers. In ASPLOS,
    2016.
[2] Tian K, et al. coIOMMU: A Virtual IOMMU with Cooperative DMA Buffer Tracking
    for Efficient Memory Management in Direct I/O. In USENIX ATC, 2020.
[3] https://patchwork.kernel.org/project/linux-arm-kernel/cover/20210401154718.307519-1-jean-philippe@linaro.org/
[4] https://github.com/Linaro/uadk

Thanks,
Shenming


Shenming Lu (8):
  iommu: Evolve the device fault reporting framework
  vfio/type1: Add a page fault handler
  vfio/type1: Add an MMU notifier to avoid pinning
  vfio/type1: Pre-map more pages than requested in the IOPF handling
  vfio/type1: VFIO_IOMMU_ENABLE_IOPF
  vfio/type1: No need to statically pin and map if IOPF enabled
  vfio/type1: Add selective DMA faulting support
  vfio: Add nested IOPF support

 .../iommu/arm/arm-smmu-v3/arm-smmu-v3-sva.c   |    3 +-
 drivers/iommu/arm/arm-smmu-v3/arm-smmu-v3.c   |   18 +-
 drivers/iommu/iommu.c                         |   56 +-
 drivers/vfio/vfio.c                           |   85 +-
 drivers/vfio/vfio_iommu_type1.c               | 1000 ++++++++++++++++-
 include/linux/iommu.h                         |   19 +-
 include/linux/vfio.h                          |   13 +
 include/uapi/linux/iommu.h                    |    4 +
 include/uapi/linux/vfio.h                     |    6 +
 9 files changed, 1181 insertions(+), 23 deletions(-)
```
#### [PATCH v5 0/3] CET fix patches for nested guest
##### From: Yang Weijiang <weijiang.yang@intel.com>

```c
From patchwork Fri Apr  9 06:43:42 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Yang Weijiang <weijiang.yang@intel.com>
X-Patchwork-Id: 12193161
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-11.8 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,
	SPF_PASS,USER_AGENT_GIT autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id B4254C433ED
	for <kvm@archiver.kernel.org>; Fri,  9 Apr 2021 06:32:04 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 7DE4961181
	for <kvm@archiver.kernel.org>; Fri,  9 Apr 2021 06:32:04 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S233366AbhDIGcP (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Fri, 9 Apr 2021 02:32:15 -0400
Received: from mga12.intel.com ([192.55.52.136]:32002 "EHLO mga12.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S233251AbhDIGcO (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 9 Apr 2021 02:32:14 -0400
IronPort-SDR: 
 K9hmgSiJG3UCMeuVNaj38IMUFkf0fP5zVObG2vLppQ4yMgaUNbTWt8LuuAxXAZmuGu38Uq7Jr3
 2f/KbIgkAmHQ==
X-IronPort-AV: E=McAfee;i="6000,8403,9948"; a="173178630"
X-IronPort-AV: E=Sophos;i="5.82,208,1613462400";
   d="scan'208";a="173178630"
Received: from orsmga003.jf.intel.com ([10.7.209.27])
  by fmsmga106.fm.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 08 Apr 2021 23:31:26 -0700
IronPort-SDR: 
 fAkrdpAmdwbB1Sx8zIqGUC1wNNQz+1eg6lMSCb+qUp9KJDGD3opmVjFV9QPEfv5S4JjLk+QNEU
 bTIBTGdOUy+A==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.82,208,1613462400";
   d="scan'208";a="380538699"
Received: from local-michael-cet-test.sh.intel.com ([10.239.159.166])
  by orsmga003.jf.intel.com with ESMTP; 08 Apr 2021 23:31:24 -0700
From: Yang Weijiang <weijiang.yang@intel.com>
To: pbonzini@redhat.com, seanjc@google.com, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org
Cc: Yang Weijiang <weijiang.yang@intel.com>
Subject: [PATCH v5 0/3] CET fix patches for nested guest
Date: Fri,  9 Apr 2021 14:43:42 +0800
Message-Id: <20210409064345.31497-1-weijiang.yang@intel.com>
X-Mailer: git-send-email 2.17.2
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This patch series is to fix a few issues found during patch review and
testing on Linux, also including a patch to explictly disable CET support
in nested guest over Hyper-V(s).

change in v5:
- Changed condition to snapshot CET state to vmcs01 per Sean's feedback.
- Remove mixed fix code for MPX.


Yang Weijiang (3):
  KVM: nVMX: Sync L2 guest CET states between L1/L2
  KVM: nVMX: Set X86_CR4_CET in cr4_fixed1_bits if CET IBT is enabled
  KVM: nVMX: Add CET entry/exit load bits to evmcs unsupported list

 arch/x86/kvm/cpuid.c      |  1 -
 arch/x86/kvm/vmx/evmcs.c  |  4 ++--
 arch/x86/kvm/vmx/evmcs.h  |  6 ++++--
 arch/x86/kvm/vmx/nested.c | 30 ++++++++++++++++++++++++++++++
 arch/x86/kvm/vmx/vmx.c    |  1 +
 arch/x86/kvm/vmx/vmx.h    |  3 +++
 6 files changed, 40 insertions(+), 5 deletions(-)
```
#### [PATCH v3 0/8] Fix broken documentation file references
##### From: Mauro Carvalho Chehab <mchehab+huawei@kernel.org>

```c
From patchwork Fri Apr  9 12:47:44 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Mauro Carvalho Chehab <mchehab+huawei@kernel.org>
X-Patchwork-Id: 12194083
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-14.0 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,INCLUDES_PATCH,MAILING_LIST_MULTI,
	SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT autolearn=unavailable
	autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 969D9C43470
	for <kvm@archiver.kernel.org>; Fri,  9 Apr 2021 12:48:11 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 80884611AB
	for <kvm@archiver.kernel.org>; Fri,  9 Apr 2021 12:48:11 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S233902AbhDIMsW (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Fri, 9 Apr 2021 08:48:22 -0400
Received: from mail.kernel.org ([198.145.29.99]:41840 "EHLO mail.kernel.org"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S233712AbhDIMsP (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 9 Apr 2021 08:48:15 -0400
Received: by mail.kernel.org (Postfix) with ESMTPSA id 5DEB26113A;
        Fri,  9 Apr 2021 12:48:01 +0000 (UTC)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple; d=kernel.org;
        s=k20201202; t=1617972481;
        bh=KVB99uveFfZEtOFS+rw6+GuSTG0eUAu7eT5aXgN+A2I=;
        h=From:To:Cc:Subject:Date:From;
        b=HVeqO0LTdb6P34NPuz+kcIo3Rf749nd/WbbdJGxFgX+jaSQh3ut1YKoPYl1MgyRxh
         Q7kRjml+eMUN9cb6xXsqyy1LpRy94RSYcfiRD58M7/eXFD0KYEG5fV6LbU9gb6NNhs
         OKJrR0HItZx9dkSG0Rw4RaD0KWq57c5q3+CPTWH2cN7XJpYHQhm2OdH9T1q1mdIFOS
         qamXogV+8qqqQnkylXpoWSIOs+K54//txxScI0SkPXbR+BMNCVw9UukyZhMQi81Ybh
         U+G/5ZiQeDykJPDsU7gNFXuoH2Hs/Mon3ZPlABh5XFVA3MUkHq3gld+lw+RHLfRuKm
         yWvyZlhUcvMnA==
Received: by mail.kernel.org with local (Exim 4.94)
        (envelope-from <mchehab@kernel.org>)
        id 1lUqYE-001SLe-2j; Fri, 09 Apr 2021 14:47:54 +0200
From: Mauro Carvalho Chehab <mchehab+huawei@kernel.org>
To: Linux Doc Mailing List <linux-doc@vger.kernel.org>,
        "Jonathan Corbet" <corbet@lwn.net>
Cc: Mauro Carvalho Chehab <mchehab+huawei@kernel.org>,
        linux-kernel@vger.kernel.org,
        "Alexander A. Klimov" <grandmaster@al2klimov.de>,
        "Rafael J. Wysocki" <rafael.j.wysocki@intel.com>,
        Alex Shi <alexs@kernel.org>,
        Artur Rojek <contact@artur-rojek.eu>,
        Dmitry Torokhov <dmitry.torokhov@gmail.com>,
        Federico Vaga <federico.vaga@vaga.pv.it>,
        Greg Kroah-Hartman <gregkh@linuxfoundation.org>,
        Guenter Roeck <linux@roeck-us.net>,
        Hans de Goede <hdegoede@redhat.com>,
        Jean Delvare <jdelvare@suse.com>,
        Jiaxun Yang <jiaxun.yang@flygoat.com>,
        Jonathan Cameron <Jonathan.Cameron@huawei.com>,
        Jonathan Cameron <jic23@kernel.org>,
        Kir Kolyshkin <kolyshkin@gmail.com>,
        Lars-Peter Clausen <lars@metafoo.de>,
        Lee Jones <lee.jones@linaro.org>,
        Mark Pearson <markpearson@lenovo.com>,
        Maximilian Luz <luzmaximilian@gmail.com>,
        Paolo Bonzini <pbonzini@redhat.com>,
        Peter Meerwald-Stadler <pmeerw@pmeerw.net>,
        Peter Zijlstra <peterz@infradead.org>,
        Rob Herring <robh+dt@kernel.org>, Tejun Heo <tj@kernel.org>,
        Thorsten Leemhuis <linux@leemhuis.info>,
        Wu XiangCheng <bobwxc@email.cn>, devicetree@vger.kernel.org,
        kvm@vger.kernel.org, linux-hwmon@vger.kernel.org,
        linux-iio@vger.kernel.org, linux-input@vger.kernel.org
Subject: [PATCH v3 0/8] Fix broken documentation file references
Date: Fri,  9 Apr 2021 14:47:44 +0200
Message-Id: <cover.1617972339.git.mchehab+huawei@kernel.org>
X-Mailer: git-send-email 2.30.2
MIME-Version: 1.0
Sender: Mauro Carvalho Chehab <mchehab@kernel.org>
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Hi Jon,

As files keep being moved around and DT bindings are 
converted and renamed to yaml, their doc references get 
outdated, pointing to an invalid places.

This series address those. It is based on the top of docs-next tree,
and most patches here are independent from the other ones.

v3:
  - Dropped patches already applied at next-20210409 and
    changes that would cause conflicts there;
  - Added received acks.

v2:
  - Dropped patches that were already applied, Most of those
    will be following via Jonathan Cameron's iio tree;
  - Dropped patches that don't apply on the top of docs next.
  - Added some new patches fixing other breakages.

Mauro Carvalho Chehab (8):
  dt-bindings: don't use ../dir for doc references
  dt-bindings: fix references for iio-bindings.txt
  dt-bindings:iio:adc: update motorola,cpcap-adc.yaml reference
  docs: update sysfs-platform_profile.rst reference
  docs: vcpu-requests.rst: fix reference for atomic ops
  docs: replace transation references for reporting-bugs.rst
  docs: translations/zh_CN: fix a typo at 8.Conclusion.rst
  docs: sched-bwc.rst: fix a typo on a doc name

 .../devicetree/bindings/hwmon/ntc_thermistor.txt |  2 +-
 .../devicetree/bindings/iio/adc/ingenic,adc.yaml |  5 +++--
 .../devicetree/bindings/input/adc-joystick.yaml  |  4 +++-
 .../input/touchscreen/resistive-adc-touch.txt    |  5 ++++-
 Documentation/devicetree/bindings/mfd/ab8500.txt |  4 +++-
 .../devicetree/bindings/mfd/motorola-cpcap.txt   | 16 ++++++++--------
 Documentation/scheduler/sched-bwc.rst            |  2 +-
 .../translations/it_IT/process/howto.rst         |  2 +-
 Documentation/translations/ja_JP/howto.rst       |  2 +-
 Documentation/translations/zh_CN/SecurityBugs    |  2 +-
 .../zh_CN/admin-guide/reporting-issues.rst       |  4 ++--
 .../translations/zh_CN/process/8.Conclusion.rst  |  2 +-
 .../translations/zh_CN/process/howto.rst         |  2 +-
 Documentation/virt/kvm/vcpu-requests.rst         |  2 +-
 include/linux/platform_profile.h                 |  2 +-
 15 files changed, 32 insertions(+), 24 deletions(-)
```
#### [PATCH v5 0/4] KVM: cpuid: fix KVM_GET_EMULATED_CPUID implementation
##### From: Emanuele Giuseppe Esposito <eesposit@redhat.com>

```c
From patchwork Fri Apr  9 12:54:19 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Emanuele Giuseppe Esposito <eesposit@redhat.com>
X-Patchwork-Id: 12194125
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-15.8 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_CR_TRAILER,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS
	autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 67D01C43460
	for <kvm@archiver.kernel.org>; Fri,  9 Apr 2021 12:54:38 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 23EC0610FB
	for <kvm@archiver.kernel.org>; Fri,  9 Apr 2021 12:54:38 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S232615AbhDIMys (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Fri, 9 Apr 2021 08:54:48 -0400
Received: from us-smtp-delivery-124.mimecast.com ([216.205.24.124]:42243 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S231127AbhDIMyr (ORCPT
        <rfc822;kvm@vger.kernel.org>); Fri, 9 Apr 2021 08:54:47 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1617972873;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=t1x564ycJ2gyj0RLJZ2QQlV+6k3Blj33nf5guRDQz0g=;
        b=K8u28eslDeUMPRMvGBn2nlOazM2GYBCuBi3EJbNEHbpF7bub8oaPoIzGHklJzAHphdngb8
        0UUmYtkWbeelLYbG2+oqUS2Wfe4hF0G1VLS1o2f1UVRYdSS5AzLE3M1Wr9SEL7DcmNFk60
        UKgYPKLGqvblZ/Ufy9cHfoAvcaZWavQ=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-341-TDr1uGSDMkO_hGXeTkomAQ-1; Fri, 09 Apr 2021 08:54:31 -0400
X-MC-Unique: TDr1uGSDMkO_hGXeTkomAQ-1
Received: from smtp.corp.redhat.com (int-mx07.intmail.prod.int.phx2.redhat.com
 [10.5.11.22])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 8FB5910054F6;
        Fri,  9 Apr 2021 12:54:29 +0000 (UTC)
Received: from localhost.localdomain.com (ovpn-114-61.ams2.redhat.com
 [10.36.114.61])
        by smtp.corp.redhat.com (Postfix) with ESMTP id CE51E10013C1;
        Fri,  9 Apr 2021 12:54:24 +0000 (UTC)
From: Emanuele Giuseppe Esposito <eesposit@redhat.com>
To: kvm@vger.kernel.org
Cc: Paolo Bonzini <pbonzini@redhat.com>,
        Jonathan Corbet <corbet@lwn.net>,
        Sean Christopherson <seanjc@google.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Emanuele Giuseppe Esposito <eesposit@redhat.com>,
        Jim Mattson <jmattson@google.com>,
        Ingo Molnar <mingo@redhat.com>, Borislav Petkov <bp@alien8.de>,
        "H. Peter Anvin" <hpa@zytor.com>, Shuah Khan <shuah@kernel.org>,
        Alexander Graf <graf@amazon.com>,
        Andrew Jones <drjones@redhat.com>, linux-doc@vger.kernel.org,
        linux-kernel@vger.kernel.org, linux-kselftest@vger.kernel.org
Subject: [PATCH v5 0/4] KVM: cpuid: fix KVM_GET_EMULATED_CPUID implementation
Date: Fri,  9 Apr 2021 14:54:19 +0200
Message-Id: <20210409125423.26288-1-eesposit@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.84 on 10.5.11.22
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This series aims to clarify the behavior of the KVM_GET_EMULATED_CPUID
ioctl, and fix a corner case where -E2BIG is returned when
the nent field of struct kvm_cpuid2 is matching the amount of
emulated entries that kvm returns.

Patch 1 proposes the nent field fix to cpuid.c,
patch 2 updates the ioctl documentation accordingly and
patches 3 and 4 extend the x86_64/get_cpuid_test.c selftest to check
the intended behavior of KVM_GET_EMULATED_CPUID.

Signed-off-by: Emanuele Giuseppe Esposito <eesposit@redhat.com>
---
v5:
- Better comment in cpuid.c (patch 1)

Emanuele Giuseppe Esposito (4):
  KVM: x86: Fix a spurious -E2BIG in KVM_GET_EMULATED_CPUID
  Documentation: KVM: update KVM_GET_EMULATED_CPUID ioctl description
  selftests: add kvm_get_emulated_cpuid to processor.h
  selftests: KVM: extend get_cpuid_test to include
    KVM_GET_EMULATED_CPUID

 Documentation/virt/kvm/api.rst                | 10 +--
 arch/x86/kvm/cpuid.c                          | 33 ++++---
 .../selftests/kvm/include/x86_64/processor.h  |  1 +
 .../selftests/kvm/lib/x86_64/processor.c      | 33 +++++++
 .../selftests/kvm/x86_64/get_cpuid_test.c     | 90 ++++++++++++++++++-
 5 files changed, 142 insertions(+), 25 deletions(-)
```
