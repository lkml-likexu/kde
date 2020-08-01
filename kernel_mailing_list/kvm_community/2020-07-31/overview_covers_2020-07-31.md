

#### [RFC PATCH 0/9] Split kvm_update_cpuid_runtime()
##### From: Robert Hoo <robert.hu@linux.intel.com>

```c
From patchwork Fri Jul 31 02:42:18 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Robert Hoo <robert.hu@linux.intel.com>
X-Patchwork-Id: 11693905
Return-Path: <SRS0=JHnX=BK=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id C8F7F722
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 31 Jul 2020 02:42:34 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id B24E62083E
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 31 Jul 2020 02:42:34 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1731213AbgGaCmd (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 30 Jul 2020 22:42:33 -0400
Received: from mga12.intel.com ([192.55.52.136]:47518 "EHLO mga12.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1730820AbgGaCmd (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 30 Jul 2020 22:42:33 -0400
IronPort-SDR: 
 i3Q3I9Boz7JlfmrUoq2zzVtjHdxloIEZF88M8KWpzaGZKkf747cDQN7KAa/tvhoTtYwWdMjvDr
 yQiP98hfw8lg==
X-IronPort-AV: E=McAfee;i="6000,8403,9698"; a="131290112"
X-IronPort-AV: E=Sophos;i="5.75,416,1589266800";
   d="scan'208";a="131290112"
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from orsmga002.jf.intel.com ([10.7.209.21])
  by fmsmga106.fm.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 30 Jul 2020 19:42:32 -0700
IronPort-SDR: 
 sVhhZdSM92iN3sToa5g5SlDJ2nozC2SUtFZqoCKsMMZKTgavoioTCWWSKW8VsXya/sU/QHmjhZ
 baQq0NTi3Jvg==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.75,416,1589266800";
   d="scan'208";a="304805925"
Received: from sqa-gate.sh.intel.com (HELO robert-ivt.tsp.org)
 ([10.239.48.212])
  by orsmga002.jf.intel.com with ESMTP; 30 Jul 2020 19:42:29 -0700
From: Robert Hoo <robert.hu@linux.intel.com>
To: kvm@vger.kernel.org, pbonzini@redhat.com,
        sean.j.christopherson@intel.com, xiaoyao.li@intel.com,
        vkuznets@redhat.com, wanpengli@tencent.com, jmattson@google.com,
        joro@8bytes.org
Cc: robert.hu@intel.com, Robert Hoo <robert.hu@linux.intel.com>
Subject: [RFC PATCH 0/9] Split kvm_update_cpuid_runtime()
Date: Fri, 31 Jul 2020 10:42:18 +0800
Message-Id: <1596163347-18574-1-git-send-email-robert.hu@linux.intel.com>
X-Mailer: git-send-email 1.8.3.1
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

kvm_update_cpuid_runtime() is currently called by various functions for the
purpose of updating vCPU's cpuid entries, due to specific runtime changes, e.g.
CR4 bits changes, XCR0 bits changes, etc. Each of them actually just needs to
update 1 ~ 2 CPUID entries. But current kvm_update_cpuid_runtime() packages all.
Given finding a target CPUID entry need to go through all CPUID entries, calling
kvm_update_cpuid_runtime() is a waste for each cause.

This patch set splits kvm_update_cpuid_runtime() into pieces according to
different updating causes.
Then let various callers call their specific necessary kvm_xxx_update_cpuid().

This not only significantly saves each caller's time, but also eliminates
unnecessary couplings.

Robert Hoo (9):
  KVM:x86: Abstract sub functions from kvm_update_cpuid_runtime() and   
     kvm_vcpu_after_set_cpuid()
  KVM:x86: Substitute kvm_update_cpuid_runtime() with
    kvm_apic_base_update_cpuid() in     kvm_lapic_set_base()
  KVM:x86: Substitute kvm_update_cpuid_runtime() with
    kvm_xcr0_update_cpuid() in     __kvm_set_xcr()
  KVM:x86: Substitute kvm_update_cpuid_runtime() with
    kvm_{osxsave,pke}_update_cpuid() in     kvm_set_cr4()
  KVM:x86: Substitute kvm_update_cpuid_runtime() with
    kvm_mwait_update_cpuid() in     kvm_set_msr_common()
  KVM:x86: Substitute kvm_update_cpuid_runtime() with
    kvm_{osxsave,pke}_update_cpuid() in     enter_smm()
  KVM:x86: Substitute kvm_update_cpuid_runtime() with
    kvm_{osxsave,pke}_update_cpuid() in     __set_sregs()
  KVM:x86: Substitute kvm_vcpu_after_set_cpuid() with abstracted
    functions
  KVM:x86: Remove kvm_update_cpuid_runtime()

 arch/x86/kvm/cpuid.c | 118 ++++++++++++++++++++++++++++++++++-----------------
 arch/x86/kvm/cpuid.h |   7 ++-
 arch/x86/kvm/lapic.c |   2 +-
 arch/x86/kvm/x86.c   |  29 ++++++++-----
 4 files changed, 103 insertions(+), 53 deletions(-)
```
#### [PATCH V5 0/6] IRQ offloading for vDPA
##### From: Zhu Lingshan <lingshan.zhu@intel.com>

```c
From patchwork Fri Jul 31 06:55:27 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Zhu Lingshan <lingshan.zhu@intel.com>
X-Patchwork-Id: 11694221
Return-Path: <SRS0=JHnX=BK=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id E1B8E13B1
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 31 Jul 2020 06:59:37 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id D35B820829
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 31 Jul 2020 06:59:37 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1731508AbgGaG7f (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 31 Jul 2020 02:59:35 -0400
Received: from mga09.intel.com ([134.134.136.24]:18704 "EHLO mga09.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1731375AbgGaG7f (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 31 Jul 2020 02:59:35 -0400
IronPort-SDR: 
 w0SgzDtTbNskqQ4TIsFvDHAHay80U8YUNAOIW9yb1xeZq+TSrrX0idSl/bRfOeTFl/YbgZGqfO
 FGB3B59eNUrA==
X-IronPort-AV: E=McAfee;i="6000,8403,9698"; a="152949278"
X-IronPort-AV: E=Sophos;i="5.75,417,1589266800";
   d="scan'208";a="152949278"
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from fmsmga007.fm.intel.com ([10.253.24.52])
  by orsmga102.jf.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 30 Jul 2020 23:59:34 -0700
IronPort-SDR: 
 /4jyOjzC+FucbWMQ8EgA3wqXQDz8RVRD7usqeHG5g1EZ14NtkILCl3OfqskiCSfilK3u2i5TG9
 3ZliPQOHK0/Q==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.75,417,1589266800";
   d="scan'208";a="273136550"
Received: from unknown (HELO localhost.localdomain.bj.intel.com)
 ([10.240.192.131])
  by fmsmga007.fm.intel.com with ESMTP; 30 Jul 2020 23:59:31 -0700
From: Zhu Lingshan <lingshan.zhu@intel.com>
To: jasowang@redhat.com, alex.williamson@redhat.com, mst@redhat.com,
        pbonzini@redhat.com, sean.j.christopherson@intel.com,
        wanpengli@tencent.com
Cc: virtualization@lists.linux-foundation.org, netdev@vger.kernel.org,
        kvm@vger.kernel.org, eli@mellanox.com, shahafs@mellanox.com,
        parav@mellanox.com, Zhu Lingshan <lingshan.zhu@intel.com>
Subject: [PATCH V5 0/6] IRQ offloading for vDPA
Date: Fri, 31 Jul 2020 14:55:27 +0800
Message-Id: <20200731065533.4144-1-lingshan.zhu@intel.com>
X-Mailer: git-send-email 2.18.4
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This series intends to implement IRQ offloading for
vhost_vdpa.

By the feat of irq forwarding facilities like posted
interrupt on X86, irq bypass can  help deliver
interrupts to vCPU directly.

vDPA devices have dedicated hardware backends like VFIO
pass-throughed devices. So it would be possible to setup
irq offloading(irq bypass) for vDPA devices and gain
performance improvements.

In my testing, with this feature, we can save 0.1ms
in a ping between two VFs on average.
changes from V4:
(1)in vhost_vdpa, setup irq offloading after config_ops->set_status.
(2)minor improvements

changes from V3:
(1)removed vDPA irq allocate/free helpers in vDPA core.
(2)add a new function get_vq_irq() in struct vdpa_config_ops,
upper layer driver can use this function to: A. query the
irq numbner of a vq. B. detect whether a vq is enabled.
(3)implement get_vq_irq() in ifcvf driver.
(4)in vhost_vdpa, set_status() will setup irq offloading when
setting DRIVER_OK, and unsetup when receive !DRIVER_OK.
(5)minor improvements.

changes from V2:
(1)rename struct vhost_call_ctx to vhost_vring_call
(2)add kvm_arch_end_assignment() in del_producer()
code path
(3)rename vDPA helpers to vdpa_devm_request_irq()
and vdpa_devm_free_irq(). Add better comments
for them.
(4)better comments for setup_vq_irq() and
unsetup_vq_irq()
(5)In vDPA VHOST_SET_VRING_CALL, will call vhost_vdpa_update_vq_irq()
without checking producer.irq, move this check into
vhost_vdpa_update_vq_irq(), so that get advantage of the spinlock.
(6)Add a function vhost_vdpa_clean_irq(), this function will unregister
the producer of vqs when vhost_vdpa_release(). This is safe
for control vq.
(7) minor improvements

changes from V1:
(1)dropped vfio changes.
(3)removed KVM_HVAE_IRQ_BYPASS checks
(4)locking fixes
(5)simplified vhost_vdpa_updat

Zhu Lingshan (6):
  vhost: introduce vhost_vring_call
  kvm: detect assigned device via irqbypass manager
  vDPA: add get_vq_irq() in vdpa_config_ops
  vhost_vdpa: implement IRQ offloading in vhost_vdpa
  ifcvf: implement vdpa_config_ops.get_vq_irq()
  irqbypass: do not start cons/prod when failed connect

 arch/x86/kvm/x86.c              | 12 ++++-
 drivers/vdpa/ifcvf/ifcvf_main.c | 18 ++++++-
 drivers/vhost/Kconfig           |  1 +
 drivers/vhost/vdpa.c            | 83 +++++++++++++++++++++++++++++++--
 drivers/vhost/vhost.c           | 22 ++++++---
 drivers/vhost/vhost.h           |  9 +++-
 include/linux/vdpa.h            |  6 +++
 virt/lib/irqbypass.c            | 16 ++++---
 8 files changed, 147 insertions(+), 20 deletions(-)
```
#### [kvm-unit-tests PATCH v3 00/10] arm/arm64: Add IPI/LPI/vtimer latency
##### From: Jingyi Wang <wangjingyi11@huawei.com>

```c
From patchwork Fri Jul 31 07:42:34 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Jingyi Wang <wangjingyi11@huawei.com>
X-Patchwork-Id: 11694291
Return-Path: <SRS0=JHnX=BK=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id EBC3E912
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 31 Jul 2020 07:43:33 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id D31E320829
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 31 Jul 2020 07:43:33 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1731728AbgGaHnd (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 31 Jul 2020 03:43:33 -0400
Received: from szxga04-in.huawei.com ([45.249.212.190]:9303 "EHLO huawei.com"
        rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org with ESMTP
        id S1727851AbgGaHnd (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 31 Jul 2020 03:43:33 -0400
Received: from DGGEMS414-HUB.china.huawei.com (unknown [172.30.72.58])
        by Forcepoint Email with ESMTP id B11D2A499CBE004B7632;
        Fri, 31 Jul 2020 15:43:31 +0800 (CST)
Received: from DESKTOP-FPN2511.china.huawei.com (10.174.187.42) by
 DGGEMS414-HUB.china.huawei.com (10.3.19.214) with Microsoft SMTP Server id
 14.3.487.0; Fri, 31 Jul 2020 15:43:23 +0800
From: Jingyi Wang <wangjingyi11@huawei.com>
To: <drjones@redhat.com>, <kvm@vger.kernel.org>,
        <kvmarm@lists.cs.columbia.edu>
CC: <maz@kernel.org>, <wanghaibin.wang@huawei.com>,
        <yuzenghui@huawei.com>, <eric.auger@redhat.com>,
        <wangjingyi11@huawei.com>, <prime.zeng@hisilicon.com>
Subject: [kvm-unit-tests PATCH v3 00/10] arm/arm64: Add IPI/LPI/vtimer latency
 test
Date: Fri, 31 Jul 2020 15:42:34 +0800
Message-ID: <20200731074244.20432-1-wangjingyi11@huawei.com>
X-Mailer: git-send-email 2.14.1.windows.1
MIME-Version: 1.0
X-Originating-IP: [10.174.187.42]
X-CFilter-Loop: Reflected
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

With the development of arm gic architecture, we think it will be useful
to add some performance test in kut to measure the cost of interrupts.
In this series, we add GICv4.1 support for ipi latency test and
implement LPI/vtimer latency test.

This series of patches has been tested on GICv4.1 supported hardware.

Note:
Based on patch "arm/arm64: timer: Extract irqs at setup time",
https://www.spinics.net/lists/kvm-arm/msg41425.html

* From v2:
  - Code and commit message cleanup
  - Clear nr_ipi_received before ipi_exec() thanks for Tao Zeng's review
  - rebase the patch "Add vtimer latency test" on Andrew's patch
  - Add test->post() to get actual PPI latency

* From v1:
  - Fix spelling mistake
  - Use the existing interface to inject hw sgi to simply the logic
  - Add two separate patches to limit the running times and time cost
    of each individual micro-bench test

Jingyi Wang (10):
  arm64: microbench: get correct ipi received num
  arm64: microbench: Generalize ipi test names
  arm64: microbench: gic: Add ipi latency test for gicv4.1 support kvm
  arm64: its: Handle its command queue wrapping
  arm64: microbench: its: Add LPI latency test
  arm64: microbench: Allow each test to specify its running times
  arm64: microbench: Add time limit for each individual test
  arm64: microbench: Add vtimer latency test
  arm64: microbench: Add test->post() to further process test results
  arm64: microbench: Add timer_post() to get actual PPI latency

 arm/micro-bench.c          | 256 ++++++++++++++++++++++++++++++-------
 lib/arm/asm/gic-v3.h       |   3 +
 lib/arm/asm/gic.h          |   1 +
 lib/arm64/gic-v3-its-cmd.c |   3 +-
 4 files changed, 219 insertions(+), 44 deletions(-)
```
#### [PATCH 0/6] Guest Architectural LBR Enabling
##### From: Like Xu <like.xu@linux.intel.com>

```c
From patchwork Fri Jul 31 07:43:56 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 8bit
X-Patchwork-Submitter: Like Xu <like.xu@linux.intel.com>
X-Patchwork-Id: 11694313
Return-Path: <SRS0=JHnX=BK=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 2C659913
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 31 Jul 2020 07:46:12 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 1D407208E4
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 31 Jul 2020 07:46:12 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1731736AbgGaHqI (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 31 Jul 2020 03:46:08 -0400
Received: from mga11.intel.com ([192.55.52.93]:55461 "EHLO mga11.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1731670AbgGaHqI (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 31 Jul 2020 03:46:08 -0400
IronPort-SDR: 
 P0pTLrC5X5xLd5ERjA6tMkhJlgyVWn8dX9hAHM5E2bzNjcQyMkqjjtm4dBmLl4AfbvxSPxGbaO
 /7nx2oWJCxFQ==
X-IronPort-AV: E=McAfee;i="6000,8403,9698"; a="149570521"
X-IronPort-AV: E=Sophos;i="5.75,417,1589266800";
   d="scan'208";a="149570521"
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from fmsmga002.fm.intel.com ([10.253.24.26])
  by fmsmga102.fm.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 31 Jul 2020 00:46:08 -0700
IronPort-SDR: 
 UpyMh/lK9an/C14G0mcuFItCYfbx42J98CpGfhEs5WwhxLcoUUULVYX086lVu3do3W9g9gCw7V
 4WngttTE+nFw==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.75,417,1589266800";
   d="scan'208";a="323160568"
Received: from sqa-gate.sh.intel.com (HELO clx-ap-likexu.tsp.org)
 ([10.239.48.212])
  by fmsmga002.fm.intel.com with ESMTP; 31 Jul 2020 00:46:05 -0700
From: Like Xu <like.xu@linux.intel.com>
To: kvm@vger.kernel.org, Paolo Bonzini <pbonzini@redhat.com>,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>
Cc: Vitaly Kuznetsov <vkuznets@redhat.com>,
        Joerg Roedel <joro@8bytes.org>, wei.w.wang@intel.com,
        linux-kernel@vger.kernel.org, Like Xu <like.xu@linux.intel.com>
Subject: [PATCH 0/6] Guest Architectural LBR Enabling
Date: Fri, 31 Jul 2020 15:43:56 +0800
Message-Id: <20200731074402.8879-1-like.xu@linux.intel.com>
X-Mailer: git-send-email 2.21.3
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Hi All (especially developers who use perf in guest),

Please help review the ssuccessor pacthes to enable Arch LBR on KVM.
(The prerequisite v13 LBR patchset [2] seems more eager to get
the attention of reviewers and maintainer).

LBR (Last Branch Records) enables recording of software path history
by logging taken branches and other control flows within architectural
registers. Intel CPUs have had model-specific LBRs for quite some time
but this evolves them into an architectural feature now.

The Architectural Last Branch Records (LBRS) is already publiced
in the 319433-040 release of Intel® Architecture Instruction
Set Extensions and Future Features Programming Reference [0].

The main advantages for the Arch LBR users are [1]:
- Faster context switching due to XSAVES support and faster reset of
  LBR MSRs via the new DEPTH MSR
- Faster LBR read for a non-PEBS event due to XSAVES support, which
  lowers the overhead of the NMI handler. (For a PEBS event, the LBR
  information is recorded in the PEBS records. There is no impact on
  the PEBS event.)
- Linux kernel can support the LBR features without knowing the model
  number of the current CPU.

The Kernel 5.9 will enable Arch LBR on the host based on
tip/perf/core, so this patchset happens to enable it on KVM as well.

Before 'git am' this patchset, you may need merge the latest
tip/perf/core branch and the legacy LBR enabling patches
[PATCH v13 00/10] Guest Last Branch Recording Enabling [2].
or just wait for the above pacthes to be merged upstream.

[0] https://software.intel.com/content/www/us/en/develop/download/
intel-architecture-instruction-set-extensions-and-future-features-programming-reference.html
[1] https://lore.kernel.org/lkml/1593780569-62993-1-git-send-email-kan.liang@linux.intel.com/
[2] https://lore.kernel.org/kvm/20200726153229.27149-1-like.xu@linux.intel.com/

Please check more details in each commit and feel free to comment.

Like Xu (6):
  KVM: vmx/pmu: Add VMCS field check before exposing LBR_FMT
  perf/x86/lbr: Unify LBR_INFO registers exposure check condition
  KVM: vmx/pmu: Add MSR_ARCH_LBR_DEPTH emulation for Arch LBR
  KVM: vmx/pmu: Add MSR_ARCH_LBR_CTL emulation for Arch LBR
  KVM: vmx/pmu: Add Arch LBR emulation and its VMCS field
  KVM: x86: Expose Architectural LBR CPUID and its XSAVES bit

 arch/x86/events/intel/lbr.c     |  4 +-
 arch/x86/include/asm/vmx.h      |  4 ++
 arch/x86/kvm/cpuid.c            | 19 +++++++++
 arch/x86/kvm/vmx/capabilities.h | 16 ++++++-
 arch/x86/kvm/vmx/pmu_intel.c    | 74 +++++++++++++++++++++++++++++++--
 arch/x86/kvm/vmx/vmx.c          | 16 ++++++-
 arch/x86/kvm/vmx/vmx.h          |  3 ++
 arch/x86/kvm/x86.c              |  6 +++
 8 files changed, 133 insertions(+), 9 deletions(-)
```
#### [RFC PATCH 0/8] KVM: x86/mmu: Introduce pinned SPTEs framework
##### From: Sean Christopherson <sean.j.christopherson@intel.com>

```c
From patchwork Fri Jul 31 21:23:15 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Sean Christopherson <sean.j.christopherson@intel.com>
X-Patchwork-Id: 11695505
Return-Path: <SRS0=JHnX=BK=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id F1A781575
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 31 Jul 2020 21:24:12 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id E1E7021744
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 31 Jul 2020 21:24:12 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728249AbgGaVX1 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 31 Jul 2020 17:23:27 -0400
Received: from mga14.intel.com ([192.55.52.115]:50224 "EHLO mga14.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1728027AbgGaVX1 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 31 Jul 2020 17:23:27 -0400
IronPort-SDR: 
 ZBz6V6WaNrLKHT/hmbuXgNaSK7/2VwSs/i68D9Wjyyg0HIZA7nv/YKfhEM3PlbdXDmixlQJ2Cb
 mF7NAMcfHcBg==
X-IronPort-AV: E=McAfee;i="6000,8403,9699"; a="151075125"
X-IronPort-AV: E=Sophos;i="5.75,419,1589266800";
   d="scan'208";a="151075125"
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from orsmga007.jf.intel.com ([10.7.209.58])
  by fmsmga103.fm.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 31 Jul 2020 14:23:26 -0700
IronPort-SDR: 
 FQX8kvUq1WMuEMWxYH69vvjsYSSY8E6ZU5NQ1EKCGQbaqITJBedMOoRgSTlM9BFkp6HK/5790Z
 +s+XfyFzG7bg==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.75,419,1589266800";
   d="scan'208";a="331191293"
Received: from sjchrist-coffee.jf.intel.com ([10.54.74.160])
  by orsmga007.jf.intel.com with ESMTP; 31 Jul 2020 14:23:26 -0700
From: Sean Christopherson <sean.j.christopherson@intel.com>
To: Paolo Bonzini <pbonzini@redhat.com>
Cc: Sean Christopherson <sean.j.christopherson@intel.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org,
        eric van tassell <Eric.VanTassell@amd.com>,
        Tom Lendacky <thomas.lendacky@amd.com>
Subject: [RFC PATCH 0/8] KVM: x86/mmu: Introduce pinned SPTEs framework
Date: Fri, 31 Jul 2020 14:23:15 -0700
Message-Id: <20200731212323.21746-1-sean.j.christopherson@intel.com>
X-Mailer: git-send-email 2.28.0
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

SEV currently needs to pin guest memory as it doesn't support migrating
encrypted pages.  Introduce a framework in KVM's MMU to support pinning
pages on demand without requiring additional memory allocations, and with
(somewhat hazy) line of sight toward supporting more advanced features for
encrypted guest memory, e.g. host page migration.

The idea is to use a software available bit in the SPTE to track that a
page has been pinned.  The decision to pin a page and the actual pinning
managment is handled by vendor code via kvm_x86_ops hooks.  There are
intentionally two hooks (zap and unzap) introduced that are not needed for
SEV.  I included them to again show how the flag (probably renamed?) could
be used for more than just pin/unpin.

Bugs in the core implementation are pretty much guaranteed.  The basic
concept has been tested, but in a fairly different incarnation.  Most
notably, tagging PRESENT SPTEs as PINNED has not been tested, although
using the PINNED flag to track zapped (and known to be pinned) SPTEs has
been tested.  I cobbled this variation together fairly quickly to get the
code out there for discussion.

The last patch to pin SEV pages during sev_launch_update_data() is
incomplete; it's there to show how we might leverage MMU-based pinning to
support pinning pages before the guest is live.

Sean Christopherson (8):
  KVM: x86/mmu: Return old SPTE from mmu_spte_clear_track_bits()
  KVM: x86/mmu: Use bits 2:0 to check for present SPTEs
  KVM: x86/mmu: Refactor handling of not-present SPTEs in mmu_set_spte()
  KVM: x86/mmu: Add infrastructure for pinning PFNs on demand
  KVM: SVM: Use the KVM MMU SPTE pinning hooks to pin pages on demand
  KVM: x86/mmu: Move 'pfn' variable to caller of direct_page_fault()
  KVM: x86/mmu: Introduce kvm_mmu_map_tdp_page() for use by SEV
  KVM: SVM: Pin SEV pages in MMU during sev_launch_update_data()

 arch/x86/include/asm/kvm_host.h |   7 ++
 arch/x86/kvm/mmu.h              |   3 +
 arch/x86/kvm/mmu/mmu.c          | 186 +++++++++++++++++++++++++-------
 arch/x86/kvm/mmu/paging_tmpl.h  |   3 +-
 arch/x86/kvm/svm/sev.c          | 141 +++++++++++++++++++++++-
 arch/x86/kvm/svm/svm.c          |   3 +
 arch/x86/kvm/svm/svm.h          |   3 +
 7 files changed, 302 insertions(+), 44 deletions(-)
```
#### [PATCH v3 0/3] Allow user space to restrict and augment MSR emulation
##### From: Alexander Graf <graf@amazon.com>

```c
From patchwork Fri Jul 31 21:49:44 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Alexander Graf <graf@amazon.com>
X-Patchwork-Id: 11695531
Return-Path: <SRS0=JHnX=BK=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id EBA2A138C
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 31 Jul 2020 21:50:12 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id D4738208E4
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 31 Jul 2020 21:50:12 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=amazon.com header.i=@amazon.com
 header.b="nB3wO3EG"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727008AbgGaVuH (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 31 Jul 2020 17:50:07 -0400
Received: from smtp-fw-9101.amazon.com ([207.171.184.25]:19920 "EHLO
        smtp-fw-9101.amazon.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726881AbgGaVuG (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 31 Jul 2020 17:50:06 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
  d=amazon.com; i=@amazon.com; q=dns/txt; s=amazon201209;
  t=1596232206; x=1627768206;
  h=from:to:cc:subject:date:message-id:mime-version;
  bh=TCl662mUkal176BNY6VRMbOf0sBUN6kp6uCGLE85bLE=;
  b=nB3wO3EGTr7NQEKhWraOY5/Cf8kz/DhvIoHKKyNf2yhObAeLpYYcqfAB
   Y6uR8R9W60XqpD2oHr5AnW8/hchfMKgVKbz8Q4HK3wtjUQJZLgmQfMTIm
   y2byfiU/hbWBvzftEaedGboAsmX55SASj5bHAy5PMyfxPIy6dHX12YrYV
   8=;
IronPort-SDR: 
 oUPSmJGeLX2JoT+MfwiALEgEB86WPd23cJ0UzlfwclfAJLNTuYnXLpMRU7jlYkr6mN5h+jYvRa
 m5CMGeWGBxfQ==
X-IronPort-AV: E=Sophos;i="5.75,419,1589241600";
   d="scan'208";a="56451571"
Received: from sea32-co-svc-lb4-vlan3.sea.corp.amazon.com (HELO
 email-inbound-relay-1e-27fb8269.us-east-1.amazon.com) ([10.47.23.38])
  by smtp-border-fw-out-9101.sea19.amazon.com with ESMTP;
 31 Jul 2020 21:50:03 +0000
Received: from EX13MTAUWC001.ant.amazon.com
 (iad55-ws-svc-p15-lb9-vlan2.iad.amazon.com [10.40.159.162])
        by email-inbound-relay-1e-27fb8269.us-east-1.amazon.com (Postfix) with
 ESMTPS id D5063A2026;
        Fri, 31 Jul 2020 21:49:58 +0000 (UTC)
Received: from EX13D20UWC002.ant.amazon.com (10.43.162.163) by
 EX13MTAUWC001.ant.amazon.com (10.43.162.135) with Microsoft SMTP Server (TLS)
 id 15.0.1497.2; Fri, 31 Jul 2020 21:49:58 +0000
Received: from u79c5a0a55de558.ant.amazon.com (10.43.160.100) by
 EX13D20UWC002.ant.amazon.com (10.43.162.163) with Microsoft SMTP Server (TLS)
 id 15.0.1497.2; Fri, 31 Jul 2020 21:49:55 +0000
From: Alexander Graf <graf@amazon.com>
To: Paolo Bonzini <pbonzini@redhat.com>
CC: Jonathan Corbet <corbet@lwn.net>,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        "Joerg Roedel" <joro@8bytes.org>,
        KarimAllah Raslan <karahmed@amazon.de>,
        Aaron Lewis <aaronlewis@google.com>, <kvm@vger.kernel.org>,
        <linux-doc@vger.kernel.org>, <linux-kernel@vger.kernel.org>
Subject: [PATCH v3 0/3] Allow user space to restrict and augment MSR emulation
Date: Fri, 31 Jul 2020 23:49:44 +0200
Message-ID: <20200731214947.16885-1-graf@amazon.com>
X-Mailer: git-send-email 2.17.1
MIME-Version: 1.0
X-Originating-IP: [10.43.160.100]
X-ClientProxiedBy: EX13D48UWA001.ant.amazon.com (10.43.163.52) To
 EX13D20UWC002.ant.amazon.com (10.43.162.163)
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

While tying to add support for the MSR_CORE_THREAD_COUNT MSR in KVM,
I realized that we were still in a world where user space has no control
over what happens with MSR emulation in KVM.

That is bad for multiple reasons. In my case, I wanted to emulate the
MSR in user space, because it's a CPU specific register that does not
exist on older CPUs and that really only contains informational data that
is on the package level, so it's a natural fit for user space to provide
it.

However, it is also bad on a platform compatibility level. Currrently,
KVM has no way to expose different MSRs based on the selected target CPU
type.

This patch set introduces a way for user space to indicate to KVM which
MSRs should be handled in kernel space. With that, we can solve part of
the platform compatibility story. Or at least we can not handle AMD specific
MSRs on an Intel platform and vice versa.

In addition, it introduces a way for user space to get into the loop
when an MSR access would generate a #GP fault, such as when KVM finds an
MSR that is not handled by the in-kernel MSR emulation or when the guest
is trying to access reserved registers.

In combination with the allow list, the user space trapping allows us
to emulate arbitrary MSRs in user space, paving the way for target CPU
specific MSR implementations from user space.

v1 -> v2:

  - s/ETRAP_TO_USER_SPACE/ENOENT/g
  - deflect all #GP injection events to user space, not just unknown MSRs.
    That was we can also deflect allowlist errors later
  - fix emulator case
  - new patch: KVM: x86: Introduce allow list for MSR emulation
  - new patch: KVM: selftests: Add test for user space MSR handling

v2 -> v3:

  - return r if r == X86EMUL_IO_NEEDED
  - s/KVM_EXIT_RDMSR/KVM_EXIT_X86_RDMSR/g
  - s/KVM_EXIT_WRMSR/KVM_EXIT_X86_WRMSR/g
  - Use complete_userspace_io logic instead of reply field
  - Simplify trapping code
  - document flags for KVM_X86_ADD_MSR_ALLOWLIST
  - generalize exit path, always unlock when returning
  - s/KVM_CAP_ADD_MSR_ALLOWLIST/KVM_CAP_X86_MSR_ALLOWLIST/g
  - Add KVM_X86_CLEAR_MSR_ALLOWLIST
  - Add test to clear whitelist
  - Adjust to reply-less API
  - Fix asserts
  - Actually trap on MSR_IA32_POWER_CTL writes

Alexander Graf (3):
  KVM: x86: Deflect unknown MSR accesses to user space
  KVM: x86: Introduce allow list for MSR emulation
  KVM: selftests: Add test for user space MSR handling

 Documentation/virt/kvm/api.rst                | 153 +++++++++++
 arch/x86/include/asm/kvm_host.h               |  16 ++
 arch/x86/include/uapi/asm/kvm.h               |  15 ++
 arch/x86/kvm/emulate.c                        |  18 +-
 arch/x86/kvm/x86.c                            | 241 +++++++++++++++++-
 include/trace/events/kvm.h                    |   2 +-
 include/uapi/linux/kvm.h                      |  15 ++
 tools/testing/selftests/kvm/Makefile          |   1 +
 .../selftests/kvm/x86_64/user_msr_test.c      | 221 ++++++++++++++++
 9 files changed, 675 insertions(+), 7 deletions(-)
 create mode 100644 tools/testing/selftests/kvm/x86_64/user_msr_test.c
```
