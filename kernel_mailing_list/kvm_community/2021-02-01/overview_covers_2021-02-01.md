

#### [PATCH v14 00/11] KVM: x86/pmu: Guest Last Branch Recording Enabling
##### From: Like Xu <like.xu@linux.intel.com>

```c
From patchwork Mon Feb  1 05:10:28 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Like Xu <like.xu@linux.intel.com>
X-Patchwork-Id: 12058067
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-11.8 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,
	SPF_PASS,USER_AGENT_GIT autolearn=unavailable autolearn_force=no
 version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id C7568C433E0
	for <kvm@archiver.kernel.org>; Mon,  1 Feb 2021 05:20:20 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 8939B64E2A
	for <kvm@archiver.kernel.org>; Mon,  1 Feb 2021 05:20:20 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S229621AbhBAFS7 (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Mon, 1 Feb 2021 00:18:59 -0500
Received: from mga17.intel.com ([192.55.52.151]:9252 "EHLO mga17.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S229542AbhBAFSy (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 1 Feb 2021 00:18:54 -0500
IronPort-SDR: 
 /22J0W/X7AnvGjl7xJXZg+C2R/ruTftzSe7Z3psmdF4NBpsm2NGP8297b5Z3JmSPWlE848eMZO
 PIE2qw1pQUGg==
X-IronPort-AV: E=McAfee;i="6000,8403,9881"; a="160401823"
X-IronPort-AV: E=Sophos;i="5.79,391,1602572400";
   d="scan'208";a="160401823"
Received: from orsmga008.jf.intel.com ([10.7.209.65])
  by fmsmga107.fm.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 31 Jan 2021 21:17:08 -0800
IronPort-SDR: 
 Dd8+6vNNpkn8FCHCUllE9b5q2m+/PL4s4k/XiV6zG4y7jfOSoM7u8G+Ozc8yaFhoTsPq5g4+Z9
 D5FLk+bZZbwQ==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.79,391,1602572400";
   d="scan'208";a="390694252"
Received: from clx-ap-likexu.sh.intel.com ([10.239.48.108])
  by orsmga008.jf.intel.com with ESMTP; 31 Jan 2021 21:17:04 -0800
From: Like Xu <like.xu@linux.intel.com>
To: Paolo Bonzini <pbonzini@redhat.com>,
        Sean Christopherson <seanjc@google.com>
Cc: Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>, ak@linux.intel.com,
        wei.w.wang@intel.com, kan.liang@intel.com,
        alex.shi@linux.alibaba.com, kvm@vger.kernel.org, x86@kernel.org,
        linux-kernel@vger.kernel.org
Subject: [PATCH v14 00/11] KVM: x86/pmu: Guest Last Branch Recording Enabling
Date: Mon,  1 Feb 2021 13:10:28 +0800
Message-Id: <20210201051039.255478-1-like.xu@linux.intel.com>
X-Mailer: git-send-email 2.29.2
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Hi geniuses,

Please help review this new version which enables the guest LBR.

We already upstreamed the guest LBR support in the host perf, please
check more details in each commit and feel free to test and comment.

QEMU part: https://lore.kernel.org/qemu-devel/20210201045453.240258-1-like.xu@linux.intel.com
kvm-unit-tests: https://lore.kernel.org/kvm/20210201045751.243231-1-like.xu@linux.intel.com

v13-v14 Changelog:
- Rewrite crud about vcpu->arch.perf_capabilities;
- Add PERF_CAPABILITIES testcases to tools/testing/selftests/kvm;
- Add basic LBR testcases to the kvm-unit-tests (w/ QEMU patches);
- Apply rewritten commit log from Paolo;
- Queued the first patch "KVM: x86: Move common set/get handler ...";
- Rename 'already_passthrough' to 'msr_passthrough';
- Check the values of MSR_IA32_PERF_CAPABILITIES early;
- Call kvm_x86_ops.pmu_ops->cleanup() always and drop extra_cleanup;
- Use INTEL_PMC_IDX_FIXED_VLBR directly;
- Fix a bug in the vmx_get_perf_capabilities();

Previous:
https://lore.kernel.org/kvm/20210108013704.134985-1-like.xu@linux.intel.com/
---

The last branch recording (LBR) is a performance monitor unit (PMU)
feature on Intel processors that records a running trace of the most
recent branches taken by the processor in the LBR stack. This patch
series is going to enable this feature for plenty of KVM guests.

with this patch set, the following error will be gone forever and cloud
developers can better understand their programs with less profiling overhead:

  $ perf record -b lbr ${WORKLOAD}
  or $ perf record --call-graph lbr ${WORKLOAD}
  Error:
  cycles: PMU Hardware doesn't support sampling/overflow-interrupts. Try 'perf stat'

The user space could configure whether it's enabled or not for each
guest via MSR_IA32_PERF_CAPABILITIES msr. As a first step, a guest
could only enable LBR feature if its cpu model is the same as the
host since the LBR feature is still one of model specific features.

If it's enabled on the guest, the guest LBR driver would accesses the
LBR MSR (including IA32_DEBUGCTLMSR and records MSRs) as host does.
The first guest access on the LBR related MSRs is always interceptible.
The KVM trap would create a special LBR event (called guest LBR event)
which enables the callstack mode and none of hardware counter is assigned.
The host perf would enable and schedule this event as usual. 

Guest's first access to a LBR registers gets trapped to KVM, which
creates a guest LBR perf event. It's a regular LBR perf event which gets
the LBR facility assigned from the perf subsystem. Once that succeeds,
the LBR stack msrs are passed through to the guest for efficient accesses.
However, if another host LBR event comes in and takes over the LBR
facility, the LBR msrs will be made interceptible, and guest following
accesses to the LBR msrs will be trapped and meaningless. 

Because saving/restoring tens of LBR MSRs (e.g. 32 LBR stack entries) in
VMX transition brings too excessive overhead to frequent vmx transition
itself, the guest LBR event would help save/restore the LBR stack msrs
during the context switching with the help of native LBR event callstack
mechanism, including LBR_SELECT msr.

If the guest no longer accesses the LBR-related MSRs within a scheduling
time slice and the LBR enable bit is unset, vPMU would release its guest
LBR event as a normal event of a unused vPMC and the pass-through
state of the LBR stack msrs would be canceled.

---

LBR testcase:
echo 1 > /proc/sys/kernel/watchdog
echo 25 > /proc/sys/kernel/perf_cpu_time_max_percent
echo 5000 > /proc/sys/kernel/perf_event_max_sample_rate
echo 0 > /proc/sys/kernel/perf_cpu_time_max_percent
perf record -b ./br_instr a
(perf record --call-graph lbr ./br_instr a)

- Perf report on the host:
Samples: 72K of event 'cycles', Event count (approx.): 72512
Overhead  Command   Source Shared Object           Source Symbol                           Target Symbol                           Basic Block Cycles
  12.12%  br_instr  br_instr                       [.] cmp_end                             [.] lfsr_cond                           1
  11.05%  br_instr  br_instr                       [.] lfsr_cond                           [.] cmp_end                             5
   8.81%  br_instr  br_instr                       [.] lfsr_cond                           [.] cmp_end                             4
   5.04%  br_instr  br_instr                       [.] cmp_end                             [.] lfsr_cond                           20
   4.92%  br_instr  br_instr                       [.] lfsr_cond                           [.] cmp_end                             6
   4.88%  br_instr  br_instr                       [.] cmp_end                             [.] lfsr_cond                           6
   4.58%  br_instr  br_instr                       [.] cmp_end                             [.] lfsr_cond                           5

- Perf report on the guest:
Samples: 92K of event 'cycles', Event count (approx.): 92544
Overhead  Command   Source Shared Object  Source Symbol                                   Target Symbol                                   Basic Block Cycles
  12.03%  br_instr  br_instr              [.] cmp_end                                     [.] lfsr_cond                                   1
  11.09%  br_instr  br_instr              [.] lfsr_cond                                   [.] cmp_end                                     5
   8.57%  br_instr  br_instr              [.] lfsr_cond                                   [.] cmp_end                                     4
   5.08%  br_instr  br_instr              [.] lfsr_cond                                   [.] cmp_end                                     6
   5.06%  br_instr  br_instr              [.] cmp_end                                     [.] lfsr_cond                                   20
   4.87%  br_instr  br_instr              [.] cmp_end                                     [.] lfsr_cond                                   6
   4.70%  br_instr  br_instr              [.] cmp_end                                     [.] lfsr_cond                                   5

Conclusion: the profiling results on the guest are similar to that on the host.

Like Xu (11):
  KVM: x86/vmx: Make vmx_set_intercept_for_msr() non-static
  KVM: x86/pmu: Set up IA32_PERF_CAPABILITIES if PDCM bit is available
  KVM: vmx/pmu: Add PMU_CAP_LBR_FMT check when guest LBR is enabled
  KVM: vmx/pmu: Expose DEBUGCTLMSR_LBR in the MSR_IA32_DEBUGCTLMSR
  KVM: vmx/pmu: Create a guest LBR event when vcpu sets DEBUGCTLMSR_LBR
  KVM: vmx/pmu: Pass-through LBR msrs when the guest LBR event is ACTIVE
  KVM: vmx/pmu: Reduce the overhead of LBR pass-through or cancellation
  KVM: vmx/pmu: Emulate legacy freezing LBRs on virtual PMI
  KVM: vmx/pmu: Release guest LBR event via lazy release mechanism
  KVM: vmx/pmu: Expose LBR_FMT in the MSR_IA32_PERF_CAPABILITIES
  selftests: kvm/x86: add test for pmu msr MSR_IA32_PERF_CAPABILITIES

 arch/x86/kvm/pmu.c                            |   8 +-
 arch/x86/kvm/pmu.h                            |   2 +
 arch/x86/kvm/vmx/capabilities.h               |  19 +-
 arch/x86/kvm/vmx/pmu_intel.c                  | 281 +++++++++++++++++-
 arch/x86/kvm/vmx/vmx.c                        |  55 +++-
 arch/x86/kvm/vmx/vmx.h                        |  28 ++
 arch/x86/kvm/x86.c                            |   2 +-
 tools/testing/selftests/kvm/.gitignore        |   1 +
 tools/testing/selftests/kvm/Makefile          |   1 +
 .../selftests/kvm/x86_64/vmx_pmu_msrs_test.c  | 149 ++++++++++
 10 files changed, 524 insertions(+), 22 deletions(-)
 create mode 100644 tools/testing/selftests/kvm/x86_64/vmx_pmu_msrs_test.c
```
#### [PATCH v2 0/9] Introduce vfio-pci-core subsystem
##### From: Max Gurtovoy <mgurtovoy@nvidia.com>

```c
From patchwork Mon Feb  1 16:28:19 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Max Gurtovoy <mgurtovoy@nvidia.com>
X-Patchwork-Id: 12059453
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-19.1 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_PATCH,MAILING_LIST_MULTI,MENTIONS_GIT_HOSTING,SPF_HELO_NONE,SPF_PASS,
	URIBL_BLOCKED,USER_AGENT_GIT autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 07410C433DB
	for <kvm@archiver.kernel.org>; Mon,  1 Feb 2021 16:29:35 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id A92E464E9E
	for <kvm@archiver.kernel.org>; Mon,  1 Feb 2021 16:29:34 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S229567AbhBAQ3P (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Mon, 1 Feb 2021 11:29:15 -0500
Received: from hqnvemgate24.nvidia.com ([216.228.121.143]:18188 "EHLO
        hqnvemgate24.nvidia.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S229483AbhBAQ3O (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 1 Feb 2021 11:29:14 -0500
Received: from hqmail.nvidia.com (Not Verified[216.228.121.13]) by
 hqnvemgate24.nvidia.com (using TLS: TLSv1.2, AES256-SHA)
        id <B60182c320000>; Mon, 01 Feb 2021 08:28:34 -0800
Received: from HQMAIL111.nvidia.com (172.20.187.18) by HQMAIL111.nvidia.com
 (172.20.187.18) with Microsoft SMTP Server (TLS) id 15.0.1473.3; Mon, 1 Feb
 2021 16:28:33 +0000
Received: from r-nvmx02.mtr.labs.mlnx (172.20.145.6) by mail.nvidia.com
 (172.20.187.18) with Microsoft SMTP Server id 15.0.1473.3 via Frontend
 Transport; Mon, 1 Feb 2021 16:28:29 +0000
From: Max Gurtovoy <mgurtovoy@nvidia.com>
To: <jgg@nvidia.com>, <cohuck@redhat.com>, <kvm@vger.kernel.org>,
        <linux-kernel@vger.kernel.org>, <alex.williamson@redhat.com>
CC: <liranl@nvidia.com>, <oren@nvidia.com>, <tzahio@nvidia.com>,
        <leonro@nvidia.com>, <yarong@nvidia.com>, <aviadye@nvidia.com>,
        <shahafs@nvidia.com>, <artemp@nvidia.com>, <kwankhede@nvidia.com>,
        <ACurrid@nvidia.com>, <gmataev@nvidia.com>, <cjia@nvidia.com>,
        <mjrosato@linux.ibm.com>, <yishaih@nvidia.com>, <aik@ozlabs.ru>,
        Max Gurtovoy <mgurtovoy@nvidia.com>
Subject: [PATCH v2 0/9] Introduce vfio-pci-core subsystem
Date: Mon, 1 Feb 2021 16:28:19 +0000
Message-ID: <20210201162828.5938-1-mgurtovoy@nvidia.com>
X-Mailer: git-send-email 2.25.4
MIME-Version: 1.0
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=nvidia.com; s=n1;
        t=1612196914; bh=JOHUJGgZP4f+PKr2kMxm2+gk8j/D8K5EuMOq21uy3gE=;
        h=From:To:CC:Subject:Date:Message-ID:X-Mailer:MIME-Version:
         Content-Transfer-Encoding:Content-Type;
        b=qhv2ioT4bFxaVDLCNCtoM19721RK4XMYEpM7JJ6HQ961lwv4MIn/RYx8m7iqlrWL9
         0/1WpITpIFnrbsoqul4wt/pWyZhi92UCVh25DtsuN1SyezJ8ReEkp3lnLI5OvH2Sr/
         d59u+1+jF1drXjMHzzXgyIvt5Unfhfv2jjAdi5V/d7/6ZDUmmUvgyheM/wvvuMvDid
         9QsKRN6t7wAFrXYNomjwoiduCyd6TJ/uq/pKRmwc/SiRrJ0gsSSJeNpazpsF3rMdXu
         txrXAQxkLckx/zQei3q3bID6XPP9re4VwbnbPwvqluM3KU6Hu/PHQDeprtM1Dpx70q
         RHz/7k0PXumnw==
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Hi Alex and Cornelia,

This series split the vfio_pci driver into 2 parts: pci driver and a
subsystem driver that will also be library of code. The pci driver,
vfio_pci.ko will be used as before and it will bind to the subsystem
driver vfio_pci_core.ko to register to the VFIO subsystem. This patchset
if fully backward compatible. This is a typical Linux subsystem
framework behaviour. This framework can be also adopted by vfio_mdev
devices as we'll see in the below sketch.

This series is coming to solve the issues that were raised in the
previous attempt for extending vfio-pci for vendor specific
functionality: https://lkml.org/lkml/2020/5/17/376 by Yan Zhao.

This solution is also deterministic in a sense that when a user will
bind to a vendor specific vfio-pci driver, it will get all the special
goodies of the HW.
 
This subsystem framework will also ease on adding vendor specific
functionality to VFIO devices in the future by allowing another module
to provide the pci_driver that can setup number of details before
registering to VFIO subsystem (such as inject its own operations).

Below we can see the proposed changes (this patchset only deals with
VFIO_PCI subsystem but it can easily be extended to VFIO_MDEV subsystem
as well):

+------------------------------------------------------------------+
|                                                                  |
|                               VFIO                               |
|                                                                  |
+------------------------------------------------------------------+

+------------------------------+    +------------------------------+
|                              |    |                              |
|        VFIO_PCI_CORE         |    |         VFIO_MDEV_CORE       |
|                              |    |                              |
+------------------------------+    +------------------------------+

+--------------+ +-------------+    +-------------+ +--------------+
|              | |             |    |             | |              |
|              | |             |    |             | |              |
|   VFIO_PCI   | |MLX5_VFIO_PCI|    |  VFIO_MDEV  | |MLX5_VFIO_MDEV|
|              | |             |    |             | |              |
|              | |             |    |             | |              |
+--------------+ +-------------+    +-------------+ +--------------+

First 3 patches introduce the above changes for vfio_pci and
vfio_pci_core.

Patch (4/9) introduces a new mlx5 vfio-pci module that registers to VFIO
subsystem using vfio_pci_core. It also registers to Auxiliary bus for
binding to mlx5_core that is the parent of mlx5-vfio-pci devices. This
will allow extending mlx5-vfio-pci devices with HW specific features
such as Live Migration (mlx5_core patches are not part of this series
that comes for proposing the changes need for the vfio pci subsystem).

For our testing and development we used 2 VirtIO-BLK physical functions
based on NVIDIAs Bluefield-2 SNAP technology. These 2 PCI functions were
enumerated as 08:00.0 and 09:00.0 by the Hypervisor.

The Bluefield-2 device driver, mlx5_core, will create auxiliary devices
for each VirtIO-BLK SNAP PF (the "parent"/"manager" of each VirtIO-BLK PF
will actually issue auxiliary device creation).

These auxiliary devices will be seen on the Auxiliary bus as:
mlx5_core.vfio_pci.2048 -> ../../../devices/pci0000:00/0000:00:02.0/0000:05:00.0/0000:06:00.0/0000:07:00.0/mlx5_core.vfio_pci.2048
mlx5_core.vfio_pci.2304 -> ../../../devices/pci0000:00/0000:00:02.0/0000:05:00.0/0000:06:00.0/0000:07:00.1/mlx5_core.vfio_pci.2304

2048 represents BDF 08:00.0 (parent is 0000:07:00.0 Bluefield-2 p0) and
2304 represents BDF 09:00.0 (parent is 0000:07:00.1 Bluefield-2 p1) in
decimal view. In this manner, the administrator will be able to locate the
correct vfio-pci module it should bind the desired BDF to (by finding
the pointer to the module according to the Auxiliary driver of that BDF).

Note: The discovery mechanism we used for the RFC might need some
      improvements as mentioned in the TODO list.

In this way, we'll use the HW vendor driver core to manage the lifecycle
of these devices. This is reasonable since only the vendor driver knows
exactly about the status on its internal state and the capabilities of
its acceleratots, for example.

changes from v1:
 - Create a private and public vfio-pci structures (From Alex)
 - register to vfio core directly from vfio-pci-core (for now, expose
   minimal public funcionality to vfio pci drivers. This will remove the
   implicit behaviour from v1. More power to the drivers can be added in
   the future)
 - Add patch 3/9 to emphasize the needed extension for LM feature (From
   Cornelia)
 - take/release refcount for the pci module during core open/release
 - update nvlink, igd and zdev to PowerNV, X86 and s390 extensions for
   vfio-pci core
 - fix segfault bugs in current vfio-pci zdev code

TODOs:
1. Create subsystem module for VFIO_MDEV. This can be used for vendor
   specific scalable functions for example (SFs).
2. Add Live migration functionality for mlx5 SNAP devices
   (NVMe/Virtio-BLK).
3. Add Live migration functionality for mlx5 VFs
4. Add the needed functionality for mlx5_core
5. Improve userspace and discovery
6. move VGA stuff to x86 extension

I would like to thank the great team that was involved in this
development, design and internal review:
Oren, Liran, Jason, Leon, Aviad, Shahaf, Gary, Artem, Kirti, Neo, Andy
and others.

This series applies cleanly on top of kernel 5.11-rc5+ commit 13391c60da33:
"Merge branch 'linus' of git://git.kernel.org/pub/scm/linux/kernel/git/herbert/crypto-2.6"
from Linus.

Note: Live migration for MLX5 SNAP devices is WIP and can be the first
      example for adding vendor extension to vfio-pci devices. As the
      changes to the subsystem must be defined as a pre-condition for
      this work, we've decided to split the submission for now.

Max Gurtovoy (9):
  vfio-pci: rename vfio_pci.c to vfio_pci_core.c
  vfio-pci: introduce vfio_pci_core subsystem driver
  vfio-pci-core: export vfio_pci_register_dev_region function
  mlx5-vfio-pci: add new vfio_pci driver for mlx5 devices
  vfio-pci/zdev: remove unused vdev argument
  vfio-pci/zdev: fix possible segmentation fault issue
  vfio/pci: use s390 naming instead of zdev
  vfio/pci: use x86 naming instead of igd
  vfio/pci: use powernv naming instead of nvlink2

 drivers/vfio/pci/Kconfig                      |   57 +-
 drivers/vfio/pci/Makefile                     |   16 +-
 drivers/vfio/pci/mlx5_vfio_pci.c              |  253 ++
 drivers/vfio/pci/vfio_pci.c                   | 2384 +----------------
 drivers/vfio/pci/vfio_pci_config.c            |   56 +-
 drivers/vfio/pci/vfio_pci_core.c              | 2326 ++++++++++++++++
 drivers/vfio/pci/vfio_pci_core.h              |   73 +
 drivers/vfio/pci/vfio_pci_intrs.c             |   22 +-
 ...{vfio_pci_nvlink2.c => vfio_pci_powernv.c} |   47 +-
 drivers/vfio/pci/vfio_pci_private.h           |   44 +-
 drivers/vfio/pci/vfio_pci_rdwr.c              |   14 +-
 .../pci/{vfio_pci_zdev.c => vfio_pci_s390.c}  |   28 +-
 .../pci/{vfio_pci_igd.c => vfio_pci_x86.c}    |   18 +-
 include/linux/mlx5/vfio_pci.h                 |   36 +
 14 files changed, 2916 insertions(+), 2458 deletions(-)
 create mode 100644 drivers/vfio/pci/mlx5_vfio_pci.c
 create mode 100644 drivers/vfio/pci/vfio_pci_core.c
 create mode 100644 drivers/vfio/pci/vfio_pci_core.h
 rename drivers/vfio/pci/{vfio_pci_nvlink2.c => vfio_pci_powernv.c} (89%)
 rename drivers/vfio/pci/{vfio_pci_zdev.c => vfio_pci_s390.c} (80%)
 rename drivers/vfio/pci/{vfio_pci_igd.c => vfio_pci_x86.c} (89%)
 create mode 100644 include/linux/mlx5/vfio_pci.h
```
#### [PATCH v5 0/2] System Generation ID driver and VMGENID backend
##### From: Adrian Catangiu <acatan@amazon.com>

```c
From patchwork Mon Feb  1 17:24:52 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 8bit
X-Patchwork-Submitter: Adrian Catangiu <acatan@amazon.com>
X-Patchwork-Id: 12059509
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-14.1 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT
	autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 11993C433E9
	for <kvm@archiver.kernel.org>; Mon,  1 Feb 2021 17:26:27 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id D872964EAA
	for <kvm@archiver.kernel.org>; Mon,  1 Feb 2021 17:26:26 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S231294AbhBAR0U (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Mon, 1 Feb 2021 12:26:20 -0500
Received: from smtp-fw-2101.amazon.com ([72.21.196.25]:44464 "EHLO
        smtp-fw-2101.amazon.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S229692AbhBAR0Q (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 1 Feb 2021 12:26:16 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
  d=amazon.com; i=@amazon.com; q=dns/txt; s=amazon201209;
  t=1612200376; x=1643736376;
  h=from:to:cc:subject:date:message-id:mime-version:
   content-transfer-encoding;
  bh=4oHGTJN/orKtC2bgJVlWjuCAjE01eDUVrhYY9F6POR0=;
  b=f5w8PYXEKyXBFQ/SU0IEYRLqu7B8Cz7Rtay2q58ct6EyAcCWIN/PPBG5
   yrqFk5zOWxl03SULyAoz1j1Xn7PSmxDhhJCygCFE3hKe4j7P8M4JvGgA+
   XF8ruoM/ngAVDIVGG35hA2ob/lQwmtwuXZLdG1wOHf8JpX+JajT0sfrmR
   w=;
X-IronPort-AV: E=Sophos;i="5.79,393,1602547200";
   d="scan'208";a="78853071"
Received: from iad12-co-svc-p1-lb1-vlan3.amazon.com (HELO
 email-inbound-relay-2a-d0be17ee.us-west-2.amazon.com) ([10.43.8.6])
  by smtp-border-fw-out-2101.iad2.amazon.com with ESMTP;
 01 Feb 2021 17:25:27 +0000
Received: from EX13D08EUB004.ant.amazon.com
 (pdx1-ws-svc-p6-lb9-vlan3.pdx.amazon.com [10.236.137.198])
        by email-inbound-relay-2a-d0be17ee.us-west-2.amazon.com (Postfix) with
 ESMTPS id 85CDDA24D8;
        Mon,  1 Feb 2021 17:25:23 +0000 (UTC)
Received: from uf6ed9c851f4556.ant.amazon.com (10.43.161.253) by
 EX13D08EUB004.ant.amazon.com (10.43.166.158) with Microsoft SMTP Server (TLS)
 id 15.0.1497.2; Mon, 1 Feb 2021 17:25:08 +0000
From: Adrian Catangiu <acatan@amazon.com>
To: <linux-doc@vger.kernel.org>, <linux-kernel@vger.kernel.org>,
        <qemu-devel@nongnu.org>, <kvm@vger.kernel.org>,
        <linux-s390@vger.kernel.org>
CC: <gregkh@linuxfoundation.org>, <graf@amazon.com>,
        <rdunlap@infradead.org>, <arnd@arndb.de>, <ebiederm@xmission.com>,
        <rppt@kernel.org>, <0x7f454c46@gmail.com>,
        <borntraeger@de.ibm.com>, <Jason@zx2c4.com>, <jannh@google.com>,
        <w@1wt.eu>, <colmmacc@amazon.com>, <luto@kernel.org>,
        <tytso@mit.edu>, <ebiggers@kernel.org>, <dwmw@amazon.co.uk>,
        <bonzini@gnu.org>, <sblbir@amazon.com>, <raduweis@amazon.com>,
        <corbet@lwn.net>, <mst@redhat.com>, <mhocko@kernel.org>,
        <rafael@kernel.org>, <pavel@ucw.cz>, <mpe@ellerman.id.au>,
        <areber@redhat.com>, <ovzxemul@gmail.com>, <avagin@gmail.com>,
        <ptikhomirov@virtuozzo.com>, <gil@azul.com>, <asmehra@redhat.com>,
        <dgunigun@redhat.com>, <vijaysun@ca.ibm.com>, <oridgar@gmail.com>,
        <ghammer@redhat.com>, Adrian Catangiu <acatan@amazon.com>
Subject: [PATCH v5 0/2] System Generation ID driver and VMGENID backend
Date: Mon, 1 Feb 2021 19:24:52 +0200
Message-ID: <1612200294-17561-1-git-send-email-acatan@amazon.com>
X-Mailer: git-send-email 2.7.4
MIME-Version: 1.0
X-Originating-IP: [10.43.161.253]
X-ClientProxiedBy: EX13D24UWB002.ant.amazon.com (10.43.161.159) To
 EX13D08EUB004.ant.amazon.com (10.43.166.158)
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This feature is aimed at virtualized or containerized environments
where VM or container snapshotting duplicates memory state, which is a
challenge for applications that want to generate unique data such as
request IDs, UUIDs, and cryptographic nonces.

The patch set introduces a mechanism that provides a userspace
interface for applications and libraries to be made aware of uniqueness
breaking events such as VM or container snapshotting, and allow them to
react and adapt to such events.

Solving the uniqueness problem strongly enough for cryptographic
purposes requires a mechanism which can deterministically reseed
userspace PRNGs with new entropy at restore time. This mechanism must
also support the high-throughput and low-latency use-cases that led
programmers to pick a userspace PRNG in the first place; be usable by
both application code and libraries; allow transparent retrofitting
behind existing popular PRNG interfaces without changing application
code; it must be efficient, especially on snapshot restore; and be
simple enough for wide adoption.

The first patch in the set implements a device driver which exposes a
read-only device /dev/sysgenid to userspace, which contains a
monotonically increasing u32 generation counter. Libraries and
applications are expected to open() the device, and then call read()
which blocks until the SysGenId changes. Following an update, read()
calls no longer block until the application acknowledges the new
SysGenId by write()ing it back to the device. Non-blocking read() calls
return EAGAIN when there is no new SysGenId available. Alternatively,
libraries can mmap() the device to get a single shared page which
contains the latest SysGenId at offset 0.

SysGenId also supports a waiting mechanism exposed through a IOCTL on
the device. The SYSGENID_WAIT_WATCHERS IOCTL blocks until there are no
open file handles on the device which haven’t acknowledged the new id.
This waiting mechanism is intended for serverless and container control
planes, which want to confirm that all application code has detected
and reacted to the new SysGenId before sending an invoke to the
newly-restored sandbox.

The second patch in the set adds a VmGenId driver which makes use of
the ACPI vmgenid device to drive SysGenId and to reseed kernel entropy
on VM snapshots.
---

v4 -> v5:

  - sysgenid: generation changes are also exported through uevents
  - remove SYSGENID_GET_OUTDATED_WATCHERS ioctl
  - document sysgenid ioctl major/minor numbers
  - rebase on linus latest + various nits

v3 -> v4:

  - split functionality in two separate kernel modules: 
    1. drivers/misc/sysgenid.c which provides the generic userspace
       interface and mechanisms
    2. drivers/virt/vmgenid.c as VMGENID acpi device driver that seeds
       kernel entropy and acts as a driving backend for the generic
       sysgenid
  - renamed /dev/vmgenid -> /dev/sysgenid
  - renamed uapi header file vmgenid.h -> sysgenid.h
  - renamed ioctls VMGENID_* -> SYSGENID_*
  - added ‘min_gen’ parameter to SYSGENID_FORCE_GEN_UPDATE ioctl
  - fixed races in documentation examples
  - various style nits
  - rebased on top of linus latest

v2 -> v3:

  - separate the core driver logic and interface, from the ACPI device.
    The ACPI vmgenid device is now one possible backend.
  - fix issue when timeout=0 in VMGENID_WAIT_WATCHERS
  - add locking to avoid races between fs ops handlers and hw irq
    driven generation updates
  - change VMGENID_WAIT_WATCHERS ioctl so if the current caller is
    outdated or a generation change happens while waiting (thus making
    current caller outdated), the ioctl returns -EINTR to signal the
    user to handle event and retry. Fixes blocking on oneself.
  - add VMGENID_FORCE_GEN_UPDATE ioctl conditioned by
    CAP_CHECKPOINT_RESTORE capability, through which software can force
    generation bump.

v1 -> v2:

  - expose to userspace a monotonically increasing u32 Vm Gen Counter
    instead of the hw VmGen UUID
  - since the hw/hypervisor-provided 128-bit UUID is not public
    anymore, add it to the kernel RNG as device randomness
  - insert driver page containing Vm Gen Counter in the user vma in
    the driver's mmap handler instead of using a fault handler
  - turn driver into a misc device driver to auto-create /dev/vmgenid
  - change ioctl arg to avoid leaking kernel structs to userspace
  - update documentation
  - various nits
  - rebase on top of linus latest

Adrian Catangiu (2):
  drivers/misc: sysgenid: add system generation id driver
  drivers/virt: vmgenid: add vm generation id driver

 Documentation/misc-devices/sysgenid.rst            | 236 ++++++++++++++++
 Documentation/userspace-api/ioctl/ioctl-number.rst |   1 +
 Documentation/virt/vmgenid.rst                     |  34 +++
 MAINTAINERS                                        |  15 +
 drivers/misc/Kconfig                               |  16 ++
 drivers/misc/Makefile                              |   1 +
 drivers/misc/sysgenid.c                            | 307 +++++++++++++++++++++
 drivers/virt/Kconfig                               |  14 +
 drivers/virt/Makefile                              |   1 +
 drivers/virt/vmgenid.c                             | 153 ++++++++++
 include/uapi/linux/sysgenid.h                      |  17 ++
 11 files changed, 795 insertions(+)
 create mode 100644 Documentation/misc-devices/sysgenid.rst
 create mode 100644 Documentation/virt/vmgenid.rst
 create mode 100644 drivers/misc/sysgenid.c
 create mode 100644 drivers/virt/vmgenid.c
 create mode 100644 include/uapi/linux/sysgenid.h
```
