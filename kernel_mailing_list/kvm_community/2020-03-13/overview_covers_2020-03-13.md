

#### [PATCH v9 00/10] Guest Last Branch Recording Enabling
##### From: Like Xu <like.xu@linux.intel.com>

```c
From patchwork Fri Mar 13 02:16:06 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Like Xu <like.xu@linux.intel.com>
X-Patchwork-Id: 11435833
Return-Path: <SRS0=i7x9=46=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id C50D66CA
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 13 Mar 2020 02:18:59 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id A3B8620716
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 13 Mar 2020 02:18:59 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726331AbgCMCSr (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 12 Mar 2020 22:18:47 -0400
Received: from mga14.intel.com ([192.55.52.115]:25868 "EHLO mga14.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726114AbgCMCSr (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 12 Mar 2020 22:18:47 -0400
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from orsmga002.jf.intel.com ([10.7.209.21])
  by fmsmga103.fm.intel.com with ESMTP/TLS/DHE-RSA-AES256-GCM-SHA384;
 12 Mar 2020 19:18:46 -0700
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.70,546,1574150400";
   d="scan'208";a="261743728"
Received: from sqa-gate.sh.intel.com (HELO clx-ap-likexu.tsp.org)
 ([10.239.48.212])
  by orsmga002.jf.intel.com with ESMTP; 12 Mar 2020 19:18:42 -0700
From: Like Xu <like.xu@linux.intel.com>
To: Paolo Bonzini <pbonzini@redhat.com>,
        Peter Zijlstra <peterz@infradead.org>, kvm@vger.kernel.org,
        Andi Kleen <ak@linux.intel.com>,
        Jim Mattson <jmattson@google.com>,
        Wanpeng Li <wanpengli@tencent.com>
Cc: Sean Christopherson <sean.j.christopherson@intel.com>,
        Joerg Roedel <joro@8bytes.org>,
        Liran Alon <liran.alon@oracle.com>,
        Thomas Gleixner <tglx@linutronix.de>,
        Ingo Molnar <mingo@redhat.com>,
        Arnaldo Carvalho de Melo <acme@kernel.org>,
        Liang Kan <kan.liang@linux.intel.com>,
        Wei Wang <wei.w.wang@intel.com>,
        Like Xu <like.xu@linux.intel.com>, linux-kernel@vger.kernel.org
Subject: [PATCH v9 00/10] Guest Last Branch Recording Enabling
Date: Fri, 13 Mar 2020 10:16:06 +0800
Message-Id: <20200313021616.112322-1-like.xu@linux.intel.com>
X-Mailer: git-send-email 2.21.1
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Hi all,

Please help review your interesting parts in this stable version,
e.g. the first four patches involve the perf event subsystem
and the fifth patch concerns the KVM userspace interface.
---

The last branch recording (LBR) is a performance monitor unit (PMU)
feature on Intel processors that records a running trace of the most
recent branches taken by the processor in the LBR stack. This patch
series is going to enable this feature for plenty of KVM guests.

The userspace could configure whether it's enabled or not for each
guest via vm_ioctl KVM_CAP_X86_GUEST_LBR. As a first step, a guest
could only enable LBR feature if its cpu model is the same as the
host since the LBR feature is still one of model specific features.
The record format defined in bits [0,5] of IA32_PERF_CAPABILITIES
and cpuid PDCM bit is also exposed to the guest when it's enabled.

If it's enabled on the guest, the guest LBR driver would accesses the
LBR MSR (including IA32_DEBUGCTLMSR and stack MSRs) as host does.
The first guest access on the LBR related MSRs is always interceptible.
The KVM trap would create a special LBR event (called guest LBR event)
which enables the callstack mode and none of hardware counter is bound.
The host perf would enable and schedule this event as usual. 

Guest's first access to a LBR-related msr gets trapped to KVM, which
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

You may check more details in each commit message.

---

LBR testcase:
echo 1 > /proc/sys/kernel/watchdog
echo 25 > /proc/sys/kernel/perf_cpu_time_max_percent
echo 5000 > /proc/sys/kernel/perf_event_max_sample_rate
echo 0 > /proc/sys/kernel/perf_cpu_time_max_percent
./perf record -b ./br_instr a

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

---

v8->v9 Changelog:
- using guest_lbr_constraint to create guest LBR event without hw counter;
  (please check perf changes in patch 0003)
- rename 'cpuc->vcpu_lbr' to 'cpuc->guest_lbr_enabled';
  (please check host LBR changes in patch 0004)
- replace 'pmu->lbr_used' mechanism with lazy release kvm_pmu_lbr_cleanup();
- refactor IA32_PERF_CAPABILITIES trap via get_perf_capabilities();
- refactor kvm_pmu_lbr_enable() with kvm_pmu_lbr_setup();
- simplify model-specific LBR functionality check;
- rename x86_perf_get_lbr_stack to x86_perf_get_lbr;
- rename intel_pmu_lbr_confirm() to kvm_pmu_availability_check(); 

Previous:
https://lore.kernel.org/lkml/1565075774-26671-1-git-send-email-wei.w.wang@intel.com/

Like Xu (7):
  perf/x86/lbr: Add interface to get basic information about LBR stack
  perf/x86: Add constraint to create guest LBR event without hw counter
  perf/x86: Keep LBR stack unchanged on the host for guest LBR event
  KVM: x86: Add KVM_CAP_X86_GUEST_LBR interface to dis/enable LBR
    feature
  KVM: x86/pmu: Add LBR feature emulation via guest LBR event
  KVM: x86/pmu: Release guest LBR event via vPMU lazy release mechanism
  KVM: x86: Expose MSR_IA32_PERF_CAPABILITIES to guest for LBR record
    format

Wei Wang (3):
  perf/x86: Fix msr variable type for the LBR msrs
  KVM: x86/pmu: Tweak kvm_pmu_get_msr to pass 'struct msr_data' in
  KVM: x86: Remove the common trap handler of the MSR_IA32_DEBUGCTLMSR

 Documentation/virt/kvm/api.rst    |  28 +++
 arch/x86/events/core.c            |   9 +-
 arch/x86/events/intel/core.c      |  29 +++
 arch/x86/events/intel/lbr.c       |  55 +++++-
 arch/x86/events/perf_event.h      |  21 ++-
 arch/x86/include/asm/kvm_host.h   |   7 +
 arch/x86/include/asm/perf_event.h |  24 ++-
 arch/x86/kvm/cpuid.c              |   3 +-
 arch/x86/kvm/pmu.c                |  28 ++-
 arch/x86/kvm/pmu.h                |  26 ++-
 arch/x86/kvm/pmu_amd.c            |   7 +-
 arch/x86/kvm/vmx/pmu_intel.c      | 291 ++++++++++++++++++++++++++++--
 arch/x86/kvm/vmx/vmx.c            |   4 +-
 arch/x86/kvm/vmx/vmx.h            |   2 +
 arch/x86/kvm/x86.c                |  42 +++--
 include/linux/perf_event.h        |   7 +
 include/uapi/linux/kvm.h          |   1 +
 kernel/events/core.c              |   7 -
 tools/include/uapi/linux/kvm.h    |   1 +
 19 files changed, 540 insertions(+), 52 deletions(-)
```
#### [PATCH v4 0/7] use vfio_dma_rw to read/write IOVAs from CPU side
##### From: Yan Zhao <yan.y.zhao@intel.com>

```c
From patchwork Fri Mar 13 03:05:48 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Yan Zhao <yan.y.zhao@intel.com>
X-Patchwork-Id: 11435889
Return-Path: <SRS0=i7x9=46=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id BD6A292A
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 13 Mar 2020 03:16:16 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 9E3402071C
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 13 Mar 2020 03:16:16 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726443AbgCMDQN (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 12 Mar 2020 23:16:13 -0400
Received: from mga11.intel.com ([192.55.52.93]:7288 "EHLO mga11.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726246AbgCMDQN (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 12 Mar 2020 23:16:13 -0400
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from orsmga007.jf.intel.com ([10.7.209.58])
  by fmsmga102.fm.intel.com with ESMTP/TLS/DHE-RSA-AES256-GCM-SHA384;
 12 Mar 2020 20:16:12 -0700
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.70,546,1574150400";
   d="scan'208";a="232279013"
Received: from joy-optiplex-7040.sh.intel.com ([10.239.13.16])
  by orsmga007.jf.intel.com with ESMTP; 12 Mar 2020 20:16:10 -0700
From: Yan Zhao <yan.y.zhao@intel.com>
To: intel-gvt-dev@lists.freedesktop.org, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org
Cc: alex.williamson@redhat.com, zhenyuw@linux.intel.com,
        pbonzini@redhat.com, kevin.tian@intel.com, peterx@redhat.com,
        Yan Zhao <yan.y.zhao@intel.com>
Subject: [PATCH v4 0/7] use vfio_dma_rw to read/write IOVAs from CPU side
Date: Thu, 12 Mar 2020 23:05:48 -0400
Message-Id: <20200313030548.7705-1-yan.y.zhao@intel.com>
X-Mailer: git-send-email 2.17.1
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

It is better for a device model to use IOVAs to read/write memory to
perform some sort of virtual DMA on behalf of the device.

patch 1 exports VFIO group to external user so that it can hold the group
reference until finishing using of it. It saves ~500 cycles that are spent
on VFIO group looking up, referencing and dereferencing. (this data is
measured with 1 VFIO user).

patch 2 introduces interface vfio_dma_rw().

patch 3 introduces interfaces vfio_group_pin_pages() and
vfio_group_unpin_pages() to get rid of VFIO group looking-up in
vfio_pin_pages() and vfio_unpin_pages().

patch 4-5 let kvmgt switch from calling kvm_read/write_guest() to calling
vfio_dma_rw to rw IOVAs.

patch 6 let kvmgt switch to use lighter version of vfio_pin/unpin_pages(),
i.e. vfio_group_pin/unpin_pages()

patch 7 enables kvmgt to read/write IOVAs of size larger than PAGE_SIZE.


Performance:

Comparison between vfio_dma_rw() and kvm_read/write_guest():

1. avergage CPU cycles of each interface measured with 1 running VM:
 --------------------------------------------------
|  rw       |          avg cycles of               |
|  size     | (vfio_dma_rw - kvm_read/write_guest) |
|---------- ---------------------------------------|
| <= 1 page |            +155 ~ +195               |        
|--------------------------------------------------|
| 5 pages   |                -530                  |
|--------------------------------------------------|
| 20 pages  |           -2005 ~ -2533              |
 --------------------------------------------------

2. average scores

base: base code before applying code in this series. use
kvm_read/write_pages() to rw IOVAs

base + this series: use vfio_dma_rw() to read IOVAs and use
vfio_group_pin/unpin_pages(), and kvmgt is able to rw several pages
at a time.

Scores of benchmarks running in 1 VM each:
 -----------------------------------------------------------------
|                    | glmark2 | lightsmark | openarena | heavens |
|-----------------------------------------------------------------|
|       base         |  1248   |  219.70    |  114.9    |   560   |
|-----------------------------------------------------------------|
|base + this series  |  1248   |  225.8     |   115     |   559   |
 -----------------------------------------------------------------

Sum of scores of two benchmark instances running in 2 VMs each:
 -------------------------------------------------------
|                    | glmark2 | lightsmark | openarena |
|-------------------------------------------------------|
|       base         |  812    |  211.46    |  115.3    |
|-------------------------------------------------------|
|base + this series  |  814    |  214.69    |  115.9    |
 -------------------------------------------------------


Changelogs:
v3 --> v4:
- rebased to 5.6.0-rc4+
- adjust wrap position for vfio_group_get_external_user_from_dev() in
  header file.(Alex)
- updated function description of vfio_group_get_external_user_from_dev()
  (Alex)
- fixed Error path group reference leaking in
  vfio_group_get_external_user_from_dev()  (Alex)
- reurn 0 for success or errno in vfio_dma_rw_chunk(). (Alex)
- renamed iova to user_iova in interface vfio_dam_rw().
- renamed vfio_pin_pages_from_group() and vfio_unpin_pages_from_group() to
  vfio_group_pin_pages() and vfio_group_unpin_pages()
- renamed user_pfn to user_iova_pfn in vfio_group_pin_pages() and
  vfio_group_unpin_pages()

v2 --> v3:
- add vfio_group_get_external_user_from_dev() to improve performance (Alex)
- add vfio_pin/unpin_pages_from_group() to avoid repeated looking up of
  VFIO group in vfio_pin/unpin_pages() (Alex)
- add a check for IOMMU_READ permission. (Alex)
- rename vfio_iommu_type1_rw_dma_nopin() to
  vfio_iommu_type1_dma_rw_chunk(). (Alex)
- in kvmgt, change "write ? vfio_dma_rw(...,true) :
  vfio_dma_rw(...,false)" to vfio_dma_rw(dev, gpa, buf, len, write)
  (Alex and Paolo)
- in kvmgt, instead of read/write context pages 1:1, combining the
  reads/writes of continuous IOVAs to take advantage of vfio_dma_rw() for
  faster crossing page boundary accesses.

v1 --> v2:
- rename vfio_iova_rw to vfio_dma_rw, vfio iommu driver ops .iova_rw
to .dma_rw. (Alex).
- change iova and len from unsigned long to dma_addr_t and size_t,
respectively. (Alex)
- fix possible overflow in dma->vaddr + iova - dma->iova + offset (Alex)
- split DMAs from on page boundary to on max available size to eliminate
  redundant searching of vfio_dma and switching mm. (Alex)
- add a check for IOMMU_WRITE permission.


Yan Zhao (7):
  vfio: allow external user to get vfio group from device
  vfio: introduce vfio_dma_rw to read/write a range of IOVAs
  vfio: avoid inefficient operations on VFIO group in
    vfio_pin/unpin_pages
  drm/i915/gvt: hold reference of VFIO group during opening of vgpu
  drm/i915/gvt: subsitute kvm_read/write_guest with vfio_dma_rw
  drm/i915/gvt: switch to user vfio_group_pin/upin_pages
  drm/i915/gvt: rw more pages a time for shadow context

 drivers/gpu/drm/i915/gvt/kvmgt.c     |  46 ++++---
 drivers/gpu/drm/i915/gvt/scheduler.c |  97 ++++++++++-----
 drivers/vfio/vfio.c                  | 180 +++++++++++++++++++++++++++
 drivers/vfio/vfio_iommu_type1.c      |  76 +++++++++++
 include/linux/vfio.h                 |  13 ++
 5 files changed, 360 insertions(+), 52 deletions(-)
```
#### [PATCH v11 00/20] KVM RISC-V Support
##### From: Anup Patel <anup.patel@wdc.com>

```c
From patchwork Fri Mar 13 07:51:11 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Anup Patel <Anup.Patel@wdc.com>
X-Patchwork-Id: 11436091
Return-Path: <SRS0=i7x9=46=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id AD11714B4
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 13 Mar 2020 07:52:16 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 7239620746
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 13 Mar 2020 07:52:16 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=fail reason="signature verification failed" (2048-bit key)
 header.d=wdc.com header.i=@wdc.com header.b="fKbmO1RR";
	dkim=pass (1024-bit key) header.d=sharedspace.onmicrosoft.com
 header.i=@sharedspace.onmicrosoft.com header.b="q2KR/vLy"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726377AbgCMHwM (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 13 Mar 2020 03:52:12 -0400
Received: from esa4.hgst.iphmx.com ([216.71.154.42]:9620 "EHLO
        esa4.hgst.iphmx.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726230AbgCMHwM (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 13 Mar 2020 03:52:12 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=simple/simple;
  d=wdc.com; i=@wdc.com; q=dns/txt; s=dkim.wdc.com;
  t=1584085931; x=1615621931;
  h=from:to:cc:subject:date:message-id:mime-version;
  bh=Teg9eEb5VJP+1Ss6lnd1Nc66hYDKd/EM9PavZThU0UU=;
  b=fKbmO1RRQa4KFLUczS+g6j19I3nXuY3KHS2qj18NQ3SEHD07Jeb1PVBA
   valW+9ibDyBpUWI2EK+7eV8jZO8pnO+TqbwjpZQEaI7W2HsU80kgdDZG8
   Y8fsuyWDi4zcyp8eWhDaXkqtA7wLbZocWs2x+JZRFN1IQIvswzn9iBWQm
   XcKZrwQ3N1h9CYuhsrQqodJYZ0oJLIkL7en4dGm3WJZWs9lazTt8bDd+v
   Lh1bBJWxeFjMFvJlDDxmjpzI4RfnsiUrbUdWbVcy1FQpub4EroMk7IN4n
   lCLXDYdG2FED4rFZU2g18is7DB69caw76leifA2+IRgmRdsM/bjDzBnPG
   g==;
IronPort-SDR: 
 VEV4J6w4MuFlWGNQKZK++0QKfFgUqVkbj3J2PN0eEI1viYCj6oR2woy6Vw5cWRtQSYfOaUhFNE
 o2I0mHiTBZTJ8fFGoFTvAVSKiJ1mG7q9QkdxzorrsNiWAJ4MCAmfGBjoPftPSG0GHkZUMVbZoY
 zkMdTQacN4cMESyUNhiBmHf9Wp+lVwfmF6mErpnISpMaCPq6CzqOjPu9nV+U5chJNUMmaQJz/O
 nk2GljfA6iRcbGQozuSrkpnqABB2etkF2Ggyw6VMpY2cd0qXu1oS6KsFdEk/1KGmxddta/LCOO
 HHY=
X-IronPort-AV: E=Sophos;i="5.70,547,1574092800";
   d="scan'208";a="132374480"
Received: from mail-bn8nam12lp2173.outbound.protection.outlook.com (HELO
 NAM12-BN8-obe.outbound.protection.outlook.com) ([104.47.55.173])
  by ob1.hgst.iphmx.com with ESMTP; 13 Mar 2020 15:52:10 +0800
ARC-Seal: i=1; a=rsa-sha256; s=arcselector9901; d=microsoft.com; cv=none;
 b=OBkbf8n8BW3Ymh3Di5aNzRO9US5uWW4Z8Uh8uchddPHvGs4MRucJhVtfd6/YsDg/CXCOI8CGquqhOhkW0mCYJx3v+j5I9mdtI50KakSm0ZDX0JgaM+ka84S1de6kj3GNhf5tNEGg6y149AyeMCLO9XUTdV1Jg6to7KVRLbnxcNXz3rKVPElFWg7/XMzBMdebgY1HFSZfga5TES8X7KUPRkdXzg7yWAVfJAPvR+5iiDyT+1d1PTnVsq0b+Uvaf9uE6ubkz6ry2UhvnQKDt+7oGs1xejwlkTRYoCn1Wm0+7/tK5f04K/1YQJ2NL13kqvqqDhv6r/e+FNJ0GWXKQOBhtA==
ARC-Message-Signature: i=1; a=rsa-sha256; c=relaxed/relaxed; d=microsoft.com;
 s=arcselector9901;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=MZXfq+B+WvVPCXXZGdErudd9I49gW2xsEXvUNBRIues=;
 b=YdB6YL4ZS/AntChaQFQg5GhaOKPgGc/hfyyBml7XU+xFdH99K2/ptv+0pgSf1dapVzzysZ2ZQbdxIjfRS4DCVOXC0bLjzydiv/DjMP3qAkyhrrABx6PWiTc1098PfwcfdWkIzVTONfUkc8BasP16tPkFm5upK/gVzU/h8tRgAEIpufBcFpLE8ubv0LkqPikxvMbksOk1urlOgYzksbB/CoBGoYI9IyEmmzsliQXpqTRHMaRMmYP3AFJZSaHJzQcNvBZBsFRNdCDWtwYCgG026Lf2ORLhWTe6NNRCY3N4pgs1pLkrE11pEV6Z64Hb21ON2gsPM/B79i1qr2aQoLXUDA==
ARC-Authentication-Results: i=1; mx.microsoft.com 1; spf=pass
 smtp.mailfrom=wdc.com; dmarc=pass action=none header.from=wdc.com; dkim=pass
 header.d=wdc.com; arc=none
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
 d=sharedspace.onmicrosoft.com; s=selector2-sharedspace-onmicrosoft-com;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=MZXfq+B+WvVPCXXZGdErudd9I49gW2xsEXvUNBRIues=;
 b=q2KR/vLyHzwrKSiWauVNDHoicxiANT/lgZ6rRNMQ0d/c+DcyM/jM5FNzaFq7Hnx9zKPhlb1/Z8dcPp4wbDozbGZzOjTGNdiYNb+WXm39XIvNFNBDS42O9DoojwSqORd7gS6VJwqeLNamXKPkHuwAfhDqJG0B0z6LemliHaak9bA=
Authentication-Results: spf=none (sender IP is )
 smtp.mailfrom=Anup.Patel@wdc.com;
Received: from MN2PR04MB6061.namprd04.prod.outlook.com (2603:10b6:208:d8::15)
 by MN2PR04MB6637.namprd04.prod.outlook.com (2603:10b6:208:1ef::14) with
 Microsoft SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.2793.16; Fri, 13 Mar
 2020 07:52:08 +0000
Received: from MN2PR04MB6061.namprd04.prod.outlook.com
 ([fe80::159d:10c9:f6df:64c8]) by MN2PR04MB6061.namprd04.prod.outlook.com
 ([fe80::159d:10c9:f6df:64c8%6]) with mapi id 15.20.2814.018; Fri, 13 Mar 2020
 07:52:08 +0000
From: Anup Patel <anup.patel@wdc.com>
To: Palmer Dabbelt <palmer@dabbelt.com>,
        Paul Walmsley <paul.walmsley@sifive.com>,
        Albert Ou <aou@eecs.berkeley.edu>,
        Paolo Bonzini <pbonzini@redhat.com>,
        Radim K <rkrcmar@redhat.com>
Cc: Alexander Graf <graf@amazon.com>,
        Atish Patra <atish.patra@wdc.com>,
        Alistair Francis <Alistair.Francis@wdc.com>,
        Damien Le Moal <damien.lemoal@wdc.com>,
        Christoph Hellwig <hch@lst.de>,
        Anup Patel <anup@brainfault.org>, kvm@vger.kernel.org,
        kvm-riscv@lists.infradead.org, linux-riscv@lists.infradead.org,
        linux-kernel@vger.kernel.org, Anup Patel <anup.patel@wdc.com>
Subject: [PATCH v11 00/20] KVM RISC-V Support
Date: Fri, 13 Mar 2020 13:21:11 +0530
Message-Id: <20200313075131.69837-1-anup.patel@wdc.com>
X-Mailer: git-send-email 2.17.1
X-ClientProxiedBy: MA1PR0101CA0057.INDPRD01.PROD.OUTLOOK.COM
 (2603:1096:a00:20::19) To MN2PR04MB6061.namprd04.prod.outlook.com
 (2603:10b6:208:d8::15)
MIME-Version: 1.0
X-MS-Exchange-MessageSentRepresentingType: 1
Received: from wdc.com (1.39.129.91) by
 MA1PR0101CA0057.INDPRD01.PROD.OUTLOOK.COM (2603:1096:a00:20::19) with
 Microsoft SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.2814.14 via Frontend
 Transport; Fri, 13 Mar 2020 07:51:52 +0000
X-Mailer: git-send-email 2.17.1
X-Originating-IP: [1.39.129.91]
X-MS-PublicTrafficType: Email
X-MS-Office365-Filtering-HT: Tenant
X-MS-Office365-Filtering-Correlation-Id: 6934446b-cb62-4f4f-1a41-08d7c7236dfe
X-MS-TrafficTypeDiagnostic: MN2PR04MB6637:
X-MS-Exchange-Transport-Forked: True
X-Microsoft-Antispam-PRVS: 
 <MN2PR04MB66379CD0FF47B58E584F6D1C8DFA0@MN2PR04MB6637.namprd04.prod.outlook.com>
WDCIPOUTBOUND: EOP-TRUE
X-MS-Oob-TLC-OOBClassifiers: OLM:277;
X-Forefront-PRVS: 034119E4F6
X-Forefront-Antispam-Report: 
 SFV:NSPM;SFS:(10019020)(4636009)(39860400002)(346002)(376002)(136003)(396003)(366004)(199004)(6666004)(1006002)(4326008)(8886007)(8676002)(81156014)(478600001)(7696005)(5660300002)(8936002)(36756003)(81166006)(52116002)(1076003)(44832011)(66476007)(26005)(316002)(66946007)(956004)(55016002)(186003)(2616005)(16526019)(966005)(54906003)(2906002)(7416002)(66556008)(86362001)(110136005)(36456003)(42580500001)(42976004);DIR:OUT;SFP:1102;SCL:1;SRVR:MN2PR04MB6637;H:MN2PR04MB6061.namprd04.prod.outlook.com;FPR:;SPF:None;LANG:en;PTR:InfoNoRecords;A:1;
X-MS-Exchange-SenderADCheck: 1
X-Microsoft-Antispam: BCL:0;
X-Microsoft-Antispam-Message-Info: 
 ONIGGv7VVDmDECE8HRYlxYmuJnlxtZWJ3BI9m4P0fkc/W0hbOG5w0IZAEGTKwbO3IlsxPJiqgseYdqSC6TrPwjc/xD+yWjKJ3SYZSh1mNtpAJclGSaO1jDlkFcikb8Rqv5Xo8uGJoE8IA+L5/W8t9Giqk6Q2f+zZqiTLak4v0PiJUFbbuPnxQP/cgQUVe8W/g2qUc9odQuHyWjLxUbd5TIAXjskKHokeZLCdiCx2nSYFt5VZwB7yvTTEFEjCAgnLaeJd6yDQCiogarhdKB4+KXcUUWggENO9CHjSlrUpLxsHAncd4T9OJfdQihXrQ0zwGljF9leTNNcowMinMpCfUcXE6conl7y713h6hVr4UfioUR+9f7v9+CkZXFU4N8Jt9MD7iPZNz3y7BMVzccL7If4h/EyOCEqJex1bDTQD/7ZGOfTYkmQ89lhnqHzvAwq6xgYDJxKC4Ay2NDDDTIiP9MWNF5vYJY8sCy//0bEtho7F+kpF9JjWmMpWaUFjn5+7TmIygLwbzMUGSyUVHxlgudGxD+sP1yhOFDQUaYaiqZ4VIyseokZ3mhLRV7q4vRrdd8Hm/Xl8DZh+gOQn8BM7mUVt5aSb1iA3Qc8Kuj8l6jwUPi6hhZQC3ksjquR2rm0X
X-MS-Exchange-AntiSpam-MessageData: 
 bGY4UbLm9HYLUIGw9IhZNflNFTNs0uXv2VUC5HMbBAw0PqkNyTyaxxo0+jcDIxCcVJWL0tPJBhKMDyw4cHPRLq6h5VCSS85NSDx9C+kST5MHYMHLWwgndUbXDhh7gSv9IURgHnsEuygHJqkANKjfVA==
X-OriginatorOrg: wdc.com
X-MS-Exchange-CrossTenant-Network-Message-Id: 
 6934446b-cb62-4f4f-1a41-08d7c7236dfe
X-MS-Exchange-CrossTenant-OriginalArrivalTime: 13 Mar 2020 07:52:08.6222
 (UTC)
X-MS-Exchange-CrossTenant-FromEntityHeader: Hosted
X-MS-Exchange-CrossTenant-Id: b61c8803-16f3-4c35-9b17-6f65f441df86
X-MS-Exchange-CrossTenant-MailboxType: HOSTED
X-MS-Exchange-CrossTenant-UserPrincipalName: 
 bvxb7ZMAYM4VlkFfNkXhOQRzBt8qZ+vU5vQmx5HlhQXxzz1AFJ/mxLJ2MfzBDMY/7NbkEeMTOzKl6/E83jHF8g==
X-MS-Exchange-Transport-CrossTenantHeadersStamped: MN2PR04MB6637
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This series adds initial KVM RISC-V support. Currently, we are able to boot
RISC-V 64bit Linux Guests with multiple VCPUs.

Few key aspects of KVM RISC-V added by this series are:
1. Minimal possible KVM world-switch which touches only GPRs and few CSRs.
2. Full Guest/VM switch is done via vcpu_get/vcpu_put infrastructure.
3. KVM ONE_REG interface for VCPU register access from user-space.
4. PLIC emulation is done in user-space.
5. Timer and IPI emuation is done in-kernel.
6. MMU notifiers supported.
7. FP lazy save/restore supported.
8. SBI v0.1 emulation for KVM Guest available.
9. Forward unhandled SBI calls to KVM userspace.
10. Hugepage support for Guest/VM

Here's a brief TODO list which we will work upon after this series:
1. SBI v0.2 emulation in-kernel
2. SBI v0.2 hart state management emulation in-kernel
3. In-kernel PLIC emulation
4. ..... and more .....

This series can be found in riscv_kvm_v11 branch at:
https//github.com/avpatel/linux.git

Our work-in-progress KVMTOOL RISC-V port can be found in riscv_v2 branch
at: https//github.com/avpatel/kvmtool.git

The QEMU RISC-V hypervisor emulation is done by Alistair and is available
in mainline/anup/riscv-hyp-ext-v0.5.3 branch at:
https://github.com/kvm-riscv/qemu.git

To play around with KVM RISC-V, refer KVM RISC-V wiki at:
https://github.com/kvm-riscv/howto/wiki
https://github.com/kvm-riscv/howto/wiki/KVM-RISCV64-on-QEMU

Changes since v10:
 - Rebased patches on Linux-5.6-rc5
 - Reduce RISCV_ISA_EXT_MAX from 256 to 64
 - Separate PATCH for removing N-extension related defines
 - Added comments as requested by Palmer
 - Fixed HIDELEG CSR programming

Changes since v9:
 - Squash PATCH19 and PATCH20 into PATCH5
 - Squash PATCH18 into PATCH11
 - Squash PATCH17 into PATCH16
 - Added ONE_REG interface for VCPU timer in PATCH13
 - Use HTIMEDELTA for VCPU timer in PATCH13
 - Updated KVM RISC-V mailing list in MAINTAINERS entry
 - Update KVM kconfig option to depend on RISCV_SBI and MMU
 - Check for SBI v0.2 and SBI v0.2 RFENCE extension at boot-time
 - Use SBI v0.2 RFENCE extension in VMID implementation
 - Use SBI v0.2 RFENCE extension in Stage2 MMU implementation
 - Use SBI v0.2 RFENCE extension in SBI implementation
 - Moved to RISC-V Hypervisor v0.5 draft spec
 - Updated Documentation/virt/kvm/api.txt for timer ONE_REG interface
 - Rebased patches on Linux-5.5-rc3

Changes since v8:
 - Rebased series on Linux-5.4-rc3 and Atish's SBI v0.2 patches
 - Use HRTIMER_MODE_REL instead of HRTIMER_MODE_ABS in timer emulation
 - Fixed kvm_riscv_stage2_map() to handle hugepages
 - Added patch to forward unhandled SBI calls to user-space
 - Added patch for iterative/recursive stage2 page table programming
 - Added patch to remove per-CPU vsip_shadow variable
 - Added patch to fix race-condition in kvm_riscv_vcpu_sync_interrupts()

Changes since v7:
- Rebased series on Linux-5.4-rc1 and Atish's SBI v0.2 patches
- Removed PATCH1, PATCH3, and PATCH20 because these already merged
- Use kernel doc style comments for ISA bitmap functions
- Don't parse X, Y, and Z extension in riscv_fill_hwcap() because it will
  be added in-future
- Mark KVM RISC-V kconfig option as EXPERIMENTAL
- Typo fix in commit description of PATCH6 of v7 series
- Use separate structs for CORE and CSR registers of ONE_REG interface
- Explicitly include asm/sbi.h in kvm/vcpu_sbi.c
- Removed implicit switch-case fall-through in kvm_riscv_vcpu_exit()
- No need to set VSSTATUS.MXR bit in kvm_riscv_vcpu_unpriv_read()
- Removed register for instruction length in kvm_riscv_vcpu_unpriv_read()
- Added defines for checking/decoding instruction length
- Added separate patch to forward unhandled SBI calls to userspace tool

Changes since v6:
- Rebased patches on Linux-5.3-rc7
- Added "return_handled" in struct kvm_mmio_decode to ensure that
  kvm_riscv_vcpu_mmio_return() updates SEPC only once
- Removed trap_stval parameter from kvm_riscv_vcpu_unpriv_read()
- Updated git repo URL in MAINTAINERS entry

Changes since v5:
- Renamed KVM_REG_RISCV_CONFIG_TIMEBASE register to
  KVM_REG_RISCV_CONFIG_TBFREQ register in ONE_REG interface
- Update SPEC in kvm_riscv_vcpu_mmio_return() for MMIO exits
- Use switch case instead of illegal instruction opcode table for simplicity
- Improve comments in stage2_remote_tlb_flush() for a potential remote TLB
  flush optimization
- Handle all unsupported SBI calls in default case of
  kvm_riscv_vcpu_sbi_ecall() function
- Fixed kvm_riscv_vcpu_sync_interrupts() for software interrupts
- Improved unprivilege reads to handle traps due to Guest stage1 page table
- Added separate patch to document RISC-V specific things in
  Documentation/virt/kvm/api.txt

Changes since v4:
- Rebased patches on Linux-5.3-rc5
- Added Paolo's Acked-by and Reviewed-by
- Updated mailing list in MAINTAINERS entry

Changes since v3:
- Moved patch for ISA bitmap from KVM prep series to this series
- Make vsip_shadow as run-time percpu variable instead of compile-time
- Flush Guest TLBs on all Host CPUs whenever we run-out of VMIDs

Changes since v2:
- Removed references of KVM_REQ_IRQ_PENDING from all patches
- Use kvm->srcu within in-kernel KVM run loop
- Added percpu vsip_shadow to track last value programmed in VSIP CSR
- Added comments about irqs_pending and irqs_pending_mask
- Used kvm_arch_vcpu_runnable() in-place-of kvm_riscv_vcpu_has_interrupt()
  in system_opcode_insn()
- Removed unwanted smp_wmb() in kvm_riscv_stage2_vmid_update()
- Use kvm_flush_remote_tlbs() in kvm_riscv_stage2_vmid_update()
- Use READ_ONCE() in kvm_riscv_stage2_update_hgatp() for vmid

Changes since v1:
- Fixed compile errors in building KVM RISC-V as module
- Removed unused kvm_riscv_halt_guest() and kvm_riscv_resume_guest()
- Set KVM_CAP_SYNC_MMU capability only after MMU notifiers are implemented
- Made vmid_version as unsigned long instead of atomic
- Renamed KVM_REQ_UPDATE_PGTBL to KVM_REQ_UPDATE_HGATP
- Renamed kvm_riscv_stage2_update_pgtbl() to kvm_riscv_stage2_update_hgatp()
- Configure HIDELEG and HEDELEG in kvm_arch_hardware_enable()
- Updated ONE_REG interface for CSR access to user-space
- Removed irqs_pending_lock and use atomic bitops instead
- Added separate patch for FP ONE_REG interface
- Added separate patch for updating MAINTAINERS file

Anup Patel (16):
  RISC-V: Export riscv_cpuid_to_hartid_mask() API
  RISC-V: Add bitmap reprensenting ISA features common across CPUs
  RISC-V: Remove N-extension related defines
  RISC-V: Add hypervisor extension related CSR defines
  RISC-V: Add initial skeletal KVM support
  RISC-V: KVM: Implement VCPU create, init and destroy functions
  RISC-V: KVM: Implement VCPU interrupts and requests handling
  RISC-V: KVM: Implement KVM_GET_ONE_REG/KVM_SET_ONE_REG ioctls
  RISC-V: KVM: Implement VCPU world-switch
  RISC-V: KVM: Handle MMIO exits for VCPU
  RISC-V: KVM: Handle WFI exits for VCPU
  RISC-V: KVM: Implement VMID allocator
  RISC-V: KVM: Implement stage2 page table programming
  RISC-V: KVM: Implement MMU notifiers
  RISC-V: KVM: Document RISC-V specific parts of KVM API
  RISC-V: KVM: Add MAINTAINERS entry

Atish Patra (4):
  RISC-V: KVM: Add timer functionality
  RISC-V: KVM: FP lazy save/restore
  RISC-V: KVM: Implement ONE REG interface for FP registers
  RISC-V: KVM: Add SBI v0.1 support

 Documentation/virt/kvm/api.rst          | 193 ++++-
 MAINTAINERS                             |  11 +
 arch/riscv/Kconfig                      |   2 +
 arch/riscv/Makefile                     |   2 +
 arch/riscv/include/asm/csr.h            |  78 +-
 arch/riscv/include/asm/hwcap.h          |  22 +
 arch/riscv/include/asm/kvm_host.h       | 264 +++++++
 arch/riscv/include/asm/kvm_vcpu_timer.h |  44 ++
 arch/riscv/include/asm/pgtable-bits.h   |   1 +
 arch/riscv/include/uapi/asm/kvm.h       | 127 +++
 arch/riscv/kernel/asm-offsets.c         | 148 ++++
 arch/riscv/kernel/cpufeature.c          |  83 +-
 arch/riscv/kernel/smp.c                 |   2 +
 arch/riscv/kvm/Kconfig                  |  34 +
 arch/riscv/kvm/Makefile                 |  14 +
 arch/riscv/kvm/main.c                   |  97 +++
 arch/riscv/kvm/mmu.c                    | 762 ++++++++++++++++++
 arch/riscv/kvm/tlb.S                    |  43 +
 arch/riscv/kvm/vcpu.c                   | 997 ++++++++++++++++++++++++
 arch/riscv/kvm/vcpu_exit.c              | 639 +++++++++++++++
 arch/riscv/kvm/vcpu_sbi.c               | 171 ++++
 arch/riscv/kvm/vcpu_switch.S            | 382 +++++++++
 arch/riscv/kvm/vcpu_timer.c             | 225 ++++++
 arch/riscv/kvm/vm.c                     |  86 ++
 arch/riscv/kvm/vmid.c                   | 120 +++
 drivers/clocksource/timer-riscv.c       |   8 +
 include/clocksource/timer-riscv.h       |  16 +
 include/uapi/linux/kvm.h                |   8 +
 28 files changed, 4564 insertions(+), 15 deletions(-)
 create mode 100644 arch/riscv/include/asm/kvm_host.h
 create mode 100644 arch/riscv/include/asm/kvm_vcpu_timer.h
 create mode 100644 arch/riscv/include/uapi/asm/kvm.h
 create mode 100644 arch/riscv/kvm/Kconfig
 create mode 100644 arch/riscv/kvm/Makefile
 create mode 100644 arch/riscv/kvm/main.c
 create mode 100644 arch/riscv/kvm/mmu.c
 create mode 100644 arch/riscv/kvm/tlb.S
 create mode 100644 arch/riscv/kvm/vcpu.c
 create mode 100644 arch/riscv/kvm/vcpu_exit.c
 create mode 100644 arch/riscv/kvm/vcpu_sbi.c
 create mode 100644 arch/riscv/kvm/vcpu_switch.S
 create mode 100644 arch/riscv/kvm/vcpu_timer.c
 create mode 100644 arch/riscv/kvm/vm.c
 create mode 100644 arch/riscv/kvm/vmid.c
 create mode 100644 include/clocksource/timer-riscv.h
```
#### [PATCH v5 0/5] x86/kvm/hyper-v: add support for synthetic debugger
##### From: Jon Doron <arilou@gmail.com>

```c
From patchwork Fri Mar 13 13:20:29 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Jon Doron <arilou@gmail.com>
X-Patchwork-Id: 11436917
Return-Path: <SRS0=i7x9=46=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id A488B92C
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 13 Mar 2020 13:20:57 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 83C2D206BE
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 13 Mar 2020 13:20:57 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=gmail.com header.i=@gmail.com
 header.b="JJqctYwY"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726591AbgCMNU5 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 13 Mar 2020 09:20:57 -0400
Received: from mail-wr1-f65.google.com ([209.85.221.65]:40813 "EHLO
        mail-wr1-f65.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726479AbgCMNU4 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 13 Mar 2020 09:20:56 -0400
Received: by mail-wr1-f65.google.com with SMTP id f3so5073864wrw.7;
        Fri, 13 Mar 2020 06:20:55 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=from:to:cc:subject:date:message-id:mime-version
         :content-transfer-encoding;
        bh=uwCiu2+wFwTgNtqnIu7f8w30xax2anlVmGhqQ2d23uI=;
        b=JJqctYwYpYLlkRXcaX+NqzFqPyV5AhCG9giq/MX7SCx0v1V1Lg/VU6idMdl32TRG24
         MPoS6r5ckEgPARi0LgtLgm6vP25doAlEKk+N3lSb6tr4oG3vug6UsjwRBN/AjY2tkPxW
         XRR7NpX5/jVtArwaOA0n8/LhiqG8IYJKOmBzEKm0uFIK82lflmDZOMa3K0voiGWgrR9g
         lBqw3jepyfxr4ijjCEZ8gGcJAS2Jv97v259M2rISiOM8viWyK/BPodyLqydsVsPHBDRD
         M0cVsoY6od7Ls8j09JPXytlmeVGliW7uqQQmdtZk0GoLg0PoOsUxCT7UQqSOC6pzMTCX
         P7sw==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:mime-version
         :content-transfer-encoding;
        bh=uwCiu2+wFwTgNtqnIu7f8w30xax2anlVmGhqQ2d23uI=;
        b=janNMJMNhpJNvaubtmi8xdALxkN8yW89p7xm7p6Z/O7FDyuepbxw6LcEvsWpie4JEH
         eI9gUZZy0y1OBRzQXCJkdU1mqDsjNRPMQWcE3Q1PpkzHyga0cYP5d7Xy66KJkJ7inhuf
         zlcqt7CiGXe4+qNLeL6M2sk+x7fV2XEclTpRaHot6PvQm1jtZ67+1aBtFrbmfLekBgSS
         UUoL6ObbXYH7DncPCCRR2chmVUxr8N7X/xbKBOQb9nX/oy9ydk0pHksO9kZJNlims9As
         OQN3G6B1qFjg3CvO6MhhTeWQHwx6Iyzy/y5Z6nm9cnr7J8RzHs1y2e5ZzakiGIvsQstt
         Qjyg==
X-Gm-Message-State: ANhLgQ0CzwL3YTPyYmCFSoqeB8dDbxmk2UcSVs037dDTjTP5FA01Z7DS
        JZ3PSbiFrm8P0Xb3yhiwJ6fM40BrpBU=
X-Google-Smtp-Source: 
 ADFU+vsveTEgaA9u+6b5flsmtaadZk8zvbxpPt83ExWqQmGeOxLfmJtW0NfRc5e2j7uJwXPZIB713Q==
X-Received: by 2002:a05:6000:12c6:: with SMTP id
 l6mr18691775wrx.217.1584105654145;
        Fri, 13 Mar 2020 06:20:54 -0700 (PDT)
Received: from jondnuc.lan (IGLD-84-229-155-229.inter.net.il.
 [84.229.155.229])
        by smtp.gmail.com with ESMTPSA id
 v8sm77112121wrw.2.2020.03.13.06.20.52
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Fri, 13 Mar 2020 06:20:53 -0700 (PDT)
From: Jon Doron <arilou@gmail.com>
To: kvm@vger.kernel.org, linux-hyperv@vger.kernel.org
Cc: vkuznets@redhat.com, Jon Doron <arilou@gmail.com>
Subject: [PATCH v5 0/5] x86/kvm/hyper-v: add support for synthetic debugger
Date: Fri, 13 Mar 2020 15:20:29 +0200
Message-Id: <20200313132034.132315-1-arilou@gmail.com>
X-Mailer: git-send-email 2.24.1
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Add support for the synthetic debugger interface of hyper-v, the
synthetic debugger has 2 modes.
1. Use a set of MSRs to send/recv information (undocumented so it's not
   going to the hyperv-tlfs.h)
2. Use hypercalls

The first mode is based the following MSRs:
1. Control/Status MSRs which either asks for a send/recv .
2. Send/Recv MSRs each holds GPA where the send/recv buffers are.
3. Pending MSR, holds a GPA to a PAGE that simply has a boolean that
   indicates if there is data pending to issue a recv VMEXIT.

The first mode implementation is to simply exit to user-space when
either the control MSR or the pending MSR are being set.
Then it's up-to userspace to implement the rest of the logic of sending/recving.

In the second mode instead of using MSRs KNet will simply issue
Hypercalls with the information to send/recv, in this mode the data
being transferred is UDP encapsulated, unlike in the previous mode in
which you get just the data to send.

The new hypercalls will exit to userspace which will be incharge of
re-encapsulating if needed the UDP packets to be sent.

There is an issue though in which KDNet does not respect the hypercall
page and simply issues vmcall/vmmcall instructions depending on the cpu
type expecting them to be handled as it a real hypercall was issued.

Jon Doron (5):
  x86/kvm/hyper-v: Explicitly align hcall param for kvm_hyperv_exit
  x86/hyper-v: Add synthetic debugger definitions
  x86/kvm/hyper-v: Add support for synthetic debugger capability
  x86/kvm/hyper-v: enable hypercalls regardless of hypercall page
  x86/kvm/hyper-v: Add support for synthetic debugger via hypercalls

 Documentation/virt/kvm/api.rst     |  18 ++++
 arch/x86/include/asm/hyperv-tlfs.h |   6 ++
 arch/x86/include/asm/kvm_host.h    |  13 +++
 arch/x86/kvm/hyperv.c              | 162 ++++++++++++++++++++++++++++-
 arch/x86/kvm/hyperv.h              |  27 +++++
 arch/x86/kvm/trace.h               |  51 +++++++++
 arch/x86/kvm/x86.c                 |   9 ++
 include/uapi/linux/kvm.h           |  13 +++
 8 files changed, 297 insertions(+), 2 deletions(-)
```
#### [PATCH 0/2] KVM: selftests: Introduce steal-time tests for x86_64 and
##### From: Andrew Jones <drjones@redhat.com>

```c
From patchwork Fri Mar 13 15:56:42 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Andrew Jones <drjones@redhat.com>
X-Patchwork-Id: 11437319
Return-Path: <SRS0=i7x9=46=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 323C21392
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 13 Mar 2020 15:56:55 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 10F642074C
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 13 Mar 2020 15:56:55 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="U+2zqxOZ"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726965AbgCMP4y (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 13 Mar 2020 11:56:54 -0400
Received: from us-smtp-1.mimecast.com ([205.139.110.61]:23672 "EHLO
        us-smtp-delivery-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S1726446AbgCMP4x (ORCPT
        <rfc822;kvm@vger.kernel.org>); Fri, 13 Mar 2020 11:56:53 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1584115012;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=nSUTvRWaOhf0z2idnkLURY3042WDleuJ2qFM+BOJcZk=;
        b=U+2zqxOZWlKHDVZRJyN4qmVB3u6+VkrBADnGw57idE0Vyt1wMWOopFPuL89dIG33jq5ixm
        AB4q8JaijxQ/WHt0movMQ9bgKGdscG8gfJ/hOERW7mUqLplX/fhsGnJrDcbhHja9jc6bsY
        7nI6U/ilz/kmS5q1csQkoxVumjwKSlk=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-364-XIVbZNo0NjGfp94PLpgu8w-1; Fri, 13 Mar 2020 11:56:50 -0400
X-MC-Unique: XIVbZNo0NjGfp94PLpgu8w-1
Received: from smtp.corp.redhat.com (int-mx05.intmail.prod.int.phx2.redhat.com
 [10.5.11.15])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id DA63D100726F
        for <kvm@vger.kernel.org>; Fri, 13 Mar 2020 15:56:49 +0000 (UTC)
Received: from kamzik.brq.redhat.com (unknown [10.43.2.160])
        by smtp.corp.redhat.com (Postfix) with ESMTP id C873993535;
        Fri, 13 Mar 2020 15:56:45 +0000 (UTC)
From: Andrew Jones <drjones@redhat.com>
To: kvm@vger.kernel.org
Cc: pbonzini@redhat.com
Subject: [PATCH 0/2] KVM: selftests: Introduce steal-time tests for x86_64 and
 AArch64
Date: Fri, 13 Mar 2020 16:56:42 +0100
Message-Id: <20200313155644.29779-1-drjones@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.15
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Test steal/stolen-time on x86 and AArch64 to make sure what gets
reported to the guest is consistent with run-delay.

The first patch of this series is just kvm selftests API cleanup. The
series is based on kvm/queue and some in-flight patches that are also
based on kvm/queue
 KVM: selftests: Share common API documentation
 KVM: selftests: Enable printf format warnings for TEST_ASSERT
 KVM: selftests: Use consistent message for test skipping
 KVM: selftests: s390x: Provide additional num-guest-pages adjustment

Thanks,
drew


Andrew Jones (2):
  KVM: selftests: virt_map should take npages, not size
  KVM: selftests: Introduce steal-time test

 tools/testing/selftests/kvm/.gitignore        |   2 +
 tools/testing/selftests/kvm/Makefile          |  12 +-
 .../selftests/kvm/demand_paging_test.c        |   3 +-
 tools/testing/selftests/kvm/dirty_log_test.c  |   3 +-
 .../testing/selftests/kvm/include/kvm_util.h  |   7 +-
 .../testing/selftests/kvm/include/test_util.h |   1 +
 tools/testing/selftests/kvm/lib/kvm_util.c    |  17 +-
 tools/testing/selftests/kvm/lib/test_util.c   |  15 +
 tools/testing/selftests/kvm/steal_time.c      | 352 ++++++++++++++++++
 .../kvm/x86_64/set_memory_region_test.c       |   2 +-
 .../selftests/kvm/x86_64/vmx_dirty_log_test.c |  11 +-
 11 files changed, 401 insertions(+), 24 deletions(-)
 create mode 100644 tools/testing/selftests/kvm/steal_time.c
```
