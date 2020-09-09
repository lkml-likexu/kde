

#### [PATCH 0/3] add VFIO mdev support for DFL devices
##### From: Xu Yilun <yilun.xu@intel.com>

```c
From patchwork Tue Sep  8 07:13:29 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Xu Yilun <yilun.xu@intel.com>
X-Patchwork-Id: 11762679
Return-Path: <SRS0=SnLg=CR=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 5AF8559D
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue,  8 Sep 2020 07:19:31 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 42DD621D6C
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue,  8 Sep 2020 07:19:31 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729251AbgIHHSC (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 8 Sep 2020 03:18:02 -0400
Received: from mga09.intel.com ([134.134.136.24]:30573 "EHLO mga09.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1728625AbgIHHR6 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 8 Sep 2020 03:17:58 -0400
IronPort-SDR: 
 Xk8CKzGo3Fs2RKo8r4urjeB0fVtMMi+aKgo1BSkcfOgYvGT1OB0YoaxAkXaCTMD52G1Jlrxvw7
 cexzOBhQadKQ==
X-IronPort-AV: E=McAfee;i="6000,8403,9737"; a="159058709"
X-IronPort-AV: E=Sophos;i="5.76,404,1592895600";
   d="scan'208";a="159058709"
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from orsmga004.jf.intel.com ([10.7.209.38])
  by orsmga102.jf.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 08 Sep 2020 00:17:57 -0700
IronPort-SDR: 
 k3dJR9sgxjeecLR+PyXWZPw2gWEd7XZnay9oDGqJ3JtZaj6AGpt3+5/pg0/IsDNr1vZ9ER/Wj0
 v3HV15uxN4Gw==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.76,404,1592895600";
   d="scan'208";a="448677676"
Received: from yilunxu-optiplex-7050.sh.intel.com ([10.239.159.141])
  by orsmga004.jf.intel.com with ESMTP; 08 Sep 2020 00:17:55 -0700
From: Xu Yilun <yilun.xu@intel.com>
To: mdf@kernel.org, alex.williamson@redhat.com, kwankhede@nvidia.com,
        linux-fpga@vger.kernel.org, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org
Cc: trix@redhat.com, lgoncalv@redhat.com, yilun.xu@intel.com
Subject: [PATCH 0/3] add VFIO mdev support for DFL devices
Date: Tue,  8 Sep 2020 15:13:29 +0800
Message-Id: <1599549212-24253-1-git-send-email-yilun.xu@intel.com>
X-Mailer: git-send-email 2.7.4
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

These patches depend on the patchset: "Modularization of DFL private
feature drivers" & "add dfl bus support to MODULE_DEVICE_TABLE()"

https://lore.kernel.org/linux-fpga/1599488581-16386-1-git-send-email-yilun.xu@intel.com/

This patchset provides an VFIO Mdev driver for dfl devices. It makes
possible for dfl devices be direct accessed from userspace.

Xu Yilun (3):
  fpga: dfl: add driver_override support
  fpga: dfl: VFIO mdev support for DFL devices
  Documentation: fpga: dfl: Add description for VFIO Mdev support

 Documentation/ABI/testing/sysfs-bus-dfl |  20 ++
 Documentation/fpga/dfl.rst              |  20 ++
 drivers/fpga/Kconfig                    |   9 +
 drivers/fpga/Makefile                   |   1 +
 drivers/fpga/dfl.c                      |  54 ++++-
 drivers/fpga/vfio-mdev-dfl.c            | 391 ++++++++++++++++++++++++++++++++
 include/linux/fpga/dfl-bus.h            |   2 +
 7 files changed, 496 insertions(+), 1 deletion(-)
 create mode 100644 drivers/fpga/vfio-mdev-dfl.c
```
#### [PATCH v3 0/5] KVM: arm64: Filtering PMU events
##### From: Marc Zyngier <maz@kernel.org>
X-SA-Exim-Mail-From: maz@kernel.org

```c
From patchwork Tue Sep  8 07:58:25 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Marc Zyngier <maz@kernel.org>
X-Patchwork-Id: 11762837
Return-Path: <SRS0=SnLg=CR=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 6120959D
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue,  8 Sep 2020 07:59:01 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 4862D21D47
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue,  8 Sep 2020 07:59:01 +0000 (UTC)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple; d=kernel.org;
	s=default; t=1599551941;
	bh=e6KbWIX9OGeN9VN1JOdQtcvcUKxjsb2qiPcRPoyCsHw=;
	h=From:To:Cc:Subject:Date:List-ID:From;
	b=q2zX3duBpeWbNiQD5vdlt8DWygchKJo9HfT5k8vrgAgwBlfqOjkWQibtZr3O54YVP
	 i9tMG0+7wp4h9Sg9+nBQsY24M1rMGO+fIk2/ijSsi1dq17M3ebCUAItEO1DG7vK5mG
	 vAo6dLA+YWmOxTm7RAHY7i8G0QOVWYAYglk+NMR8=
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729831AbgIHH67 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 8 Sep 2020 03:58:59 -0400
Received: from mail.kernel.org ([198.145.29.99]:38804 "EHLO mail.kernel.org"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1729552AbgIHH6r (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 8 Sep 2020 03:58:47 -0400
Received: from disco-boy.misterjones.org (disco-boy.misterjones.org
 [51.254.78.96])
        (using TLSv1.2 with cipher ECDHE-RSA-AES256-GCM-SHA384 (256/256 bits))
        (No client certificate requested)
        by mail.kernel.org (Postfix) with ESMTPSA id 7FE312177B;
        Tue,  8 Sep 2020 07:58:46 +0000 (UTC)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple; d=kernel.org;
        s=default; t=1599551926;
        bh=e6KbWIX9OGeN9VN1JOdQtcvcUKxjsb2qiPcRPoyCsHw=;
        h=From:To:Cc:Subject:Date:From;
        b=V1GMiEH9/wCXi86KUjxIxMq6EbokUbEMvdMoN9ec2AwdoITqXPXjibb9zdCyFJbRq
         cWd8wXlxr0/odYmPSOXIFyrc6431tYf+wYKYrSpmoS+O7G0gdPnF3kZp1HEUR11E5E
         2H/Pf4DZNNsvKJBvFrH6NuWqVf/Uvf9gSjxy5LbQ=
Received: from 78.163-31-62.static.virginmediabusiness.co.uk ([62.31.163.78]
 helo=why.lan)
        by disco-boy.misterjones.org with esmtpsa
 (TLS1.3:ECDHE_RSA_AES_256_GCM_SHA384:256)
        (Exim 4.92)
        (envelope-from <maz@kernel.org>)
        id 1kFYWa-009zhy-Jg; Tue, 08 Sep 2020 08:58:44 +0100
From: Marc Zyngier <maz@kernel.org>
To: linux-arm-kernel@lists.infradead.org, kvmarm@lists.cs.columbia.edu,
        kvm@vger.kernel.org
Cc: James Morse <james.morse@arm.com>,
        Julien Thierry <julien.thierry.kdev@gmail.com>,
        Suzuki K Poulose <suzuki.poulose@arm.com>,
        Robin Murphy <robin.murphy@arm.com>,
        Mark Rutland <mark.rutland@arm.com>,
        Eric Auger <eric.auger@redhat.com>, graf@amazon.com,
        kernel-team@android.com
Subject: [PATCH v3 0/5] KVM: arm64: Filtering PMU events
Date: Tue,  8 Sep 2020 08:58:25 +0100
Message-Id: <20200908075830.1161921-1-maz@kernel.org>
X-Mailer: git-send-email 2.28.0
MIME-Version: 1.0
X-SA-Exim-Connect-IP: 62.31.163.78
X-SA-Exim-Rcpt-To: linux-arm-kernel@lists.infradead.org,
 kvmarm@lists.cs.columbia.edu, kvm@vger.kernel.org, james.morse@arm.com,
 julien.thierry.kdev@gmail.com, suzuki.poulose@arm.com, robin.murphy@arm.com,
 mark.rutland@arm.com, eric.auger@redhat.com, graf@amazon.com,
 kernel-team@android.com
X-SA-Exim-Mail-From: maz@kernel.org
X-SA-Exim-Scanned: No (on disco-boy.misterjones.org);
 SAEximRunCond expanded to false
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

It is at times necessary to prevent a guest from being able to sample
certain events if multiple CPUs share resources such as a cache level. In
this case, it would be interesting if the VMM could simply prevent certain
events from being counted instead of hiding the PMU.

Given that most events are not architected, there is no easy way to
designate which events shouldn't be counted other than specifying the raw
event number.

Since I have no idea whether it is better to use an event whitelist or
blacklist, the proposed API takes a cue from the x86 version and allows
either allowing or denying counting of ranges of events. The event space
being pretty large (16bits on ARMv8.1), the default policy is set by the
first filter that gets installed (default deny if we first allow, default
allow if we first deny).

The filter state is global to the guest, despite the PMU being per CPU. I'm
not sure whether it would be worth it making it CPU-private.

As an example of what can be done in userspace, I have the corresponding
kvmtool hack here[1].

* From v2:
  - Split out the error handling refactor for clarity
  - Added a terrible hack to fish out the PMU version, because BL is great
  - Update the guest's view of PCMEID{0,1}_EL1
  - General tidying up

* From v1:
  - Cleaned up handling of the cycle counter
  - Documented restrictions on SW_INC, CHAIN and CPU_CYCLES events

[1] https://git.kernel.org/pub/scm/linux/kernel/git/maz/kvmtool.git/commit/?h=pmu-filter

Marc Zyngier (5):
  KVM: arm64: Refactor PMU attribute error handling
  KVM: arm64: Use event mask matching architecture revision
  KVM: arm64: Add PMU event filtering infrastructure
  KVM: arm64: Mask out filtered events in PCMEID{0,1}_EL1
  KVM: arm64: Document PMU filtering API

 Documentation/virt/kvm/devices/vcpu.rst |  46 ++++++
 arch/arm64/include/asm/kvm_host.h       |   7 +
 arch/arm64/include/uapi/asm/kvm.h       |  16 ++
 arch/arm64/kvm/arm.c                    |   2 +
 arch/arm64/kvm/pmu-emul.c               | 199 +++++++++++++++++++++---
 arch/arm64/kvm/sys_regs.c               |   5 +-
 include/kvm/arm_pmu.h                   |   5 +
 7 files changed, 254 insertions(+), 26 deletions(-)
```
#### [PATCH V4 0/2] vfio: optimized for hugetlbf pages when dma map/unmap
##### From: Ming Mao <maoming.maoming@huawei.com>

```c
From patchwork Tue Sep  8 13:32:02 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Ming Mao <maoming.maoming@huawei.com>
X-Patchwork-Id: 11763753
Return-Path: <SRS0=SnLg=CR=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 1FDCF618
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue,  8 Sep 2020 17:36:55 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 09D722076C
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue,  8 Sep 2020 17:36:54 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1731352AbgIHRgj (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 8 Sep 2020 13:36:39 -0400
Received: from szxga04-in.huawei.com ([45.249.212.190]:10849 "EHLO huawei.com"
        rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org with ESMTP
        id S1731778AbgIHRgI (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 8 Sep 2020 13:36:08 -0400
Received: from DGGEMS406-HUB.china.huawei.com (unknown [172.30.72.58])
        by Forcepoint Email with ESMTP id 9275A3EFE096A39CE752;
        Tue,  8 Sep 2020 21:32:17 +0800 (CST)
Received: from localhost (10.174.151.129) by DGGEMS406-HUB.china.huawei.com
 (10.3.19.206) with Microsoft SMTP Server id 14.3.487.0; Tue, 8 Sep 2020
 21:32:10 +0800
From: Ming Mao <maoming.maoming@huawei.com>
To: <linux-kernel@vger.kernel.org>, <kvm@vger.kernel.org>,
        <linux-mm@kvack.org>, <alex.williamson@redhat.com>,
        <akpm@linux-foundation.org>
CC: <cohuck@redhat.com>, <jianjay.zhou@huawei.com>,
        <weidong.huang@huawei.com>, <peterx@redhat.com>,
        <aarcange@redhat.com>, <wangyunjian@huawei.com>,
        Ming Mao <maoming.maoming@huawei.com>
Subject: [PATCH V4 0/2] vfio: optimized for hugetlbf pages when dma map/unmap
Date: Tue, 8 Sep 2020 21:32:02 +0800
Message-ID: <20200908133204.1338-1-maoming.maoming@huawei.com>
X-Mailer: git-send-email 2.26.2.windows.1
MIME-Version: 1.0
X-Originating-IP: [10.174.151.129]
X-CFilter-Loop: Reflected
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This series deletes the for loop in dma_map/unmap for hugetlb pages.
In the original process, the for loop could spend much time to check all
normal pages.If we use hugetlb pages, it is not necessary to do this.

Changes from v3
- add a new API unpin_user_hugetlb_pages_dirty_lock()
- use the new API to unpin hugetlb pages

Ming Mao (2):
  vfio dma_map/unmap: optimized for hugetlbfs pages
  vfio: optimized for unpinning pages

 drivers/vfio/vfio_iommu_type1.c | 373 ++++++++++++++++++++++++++++++--
 include/linux/mm.h              |   3 +
 mm/gup.c                        |  91 ++++++++
 3 files changed, 450 insertions(+), 17 deletions(-)
```
#### [PATCH v2 v4.14.y 0/3] vfio: Fix for CVE-2020-12888
##### From: Ajay Kaher <akaher@vmware.com>

```c
From patchwork Tue Sep  8 18:54:23 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Ajay Kaher <akaher@vmware.com>
X-Patchwork-Id: 11763965
Return-Path: <SRS0=SnLg=CR=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 0A4A1618
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue,  8 Sep 2020 18:59:55 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id E3F1F2087C
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue,  8 Sep 2020 18:59:54 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1730140AbgIHS6v (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 8 Sep 2020 14:58:51 -0400
Received: from ex13-edg-ou-001.vmware.com ([208.91.0.189]:51744 "EHLO
        EX13-EDG-OU-001.vmware.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1729014AbgIHS6j (ORCPT
        <rfc822;kvm@vger.kernel.org>); Tue, 8 Sep 2020 14:58:39 -0400
Received: from sc9-mailhost3.vmware.com (10.113.161.73) by
 EX13-EDG-OU-001.vmware.com (10.113.208.155) with Microsoft SMTP Server id
 15.0.1156.6; Tue, 8 Sep 2020 11:58:37 -0700
Received: from akaher-virtual-machine.eng.vmware.com (unknown
 [10.197.103.239])
        by sc9-mailhost3.vmware.com (Postfix) with ESMTP id C256E40B4F;
        Tue,  8 Sep 2020 11:58:38 -0700 (PDT)
From: Ajay Kaher <akaher@vmware.com>
To: <gregkh@linuxfoundation.org>, <sashal@kernel.org>
CC: <alex.williamson@redhat.com>, <cohuck@redhat.com>,
        <peterx@redhat.com>, <kvm@vger.kernel.org>,
        <linux-kernel@vger.kernel.org>, <stable@vger.kernel.org>,
        <srivatsab@vmware.com>, <srivatsa@csail.mit.edu>,
        <vsirnapalli@vmware.com>, <akaher@vmware.com>
Subject: [PATCH v2 v4.14.y 0/3] vfio: Fix for CVE-2020-12888
Date: Wed, 9 Sep 2020 00:24:23 +0530
Message-ID: <1599591263-46520-4-git-send-email-akaher@vmware.com>
X-Mailer: git-send-email 2.7.4
In-Reply-To: <1599591263-46520-1-git-send-email-akaher@vmware.com>
References: <1599591263-46520-1-git-send-email-akaher@vmware.com>
MIME-Version: 1.0
Received-SPF: None (EX13-EDG-OU-001.vmware.com: akaher@vmware.com does not
 designate permitted sender hosts)
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

CVE-2020-12888 Kernel: vfio: access to disabled MMIO space of some
devices may lead to DoS scenario
    
The VFIO modules allow users (guest VMs) to enable or disable access to the
devices' MMIO memory address spaces. If a user attempts to access (read/write)
the devices' MMIO address space when it is disabled, some h/w devices issue an
interrupt to the CPU to indicate a fatal error condition, crashing the system.
This flaw allows a guest user or process to crash the host system resulting in
a denial of service.
    
Patch 1/ is to force the user fault if PFNMAP vma might be DMA mapped
before user access.
    
Patch 2/ setup a vm_ops handler to support dynamic faulting instead of calling
remap_pfn_range(). Also provides a list of vmas actively mapping the area which
can later use to invalidate those mappings.
    
Patch 3/ block the user from accessing memory spaces which is disabled by using
new vma list support to zap, or invalidate, those memory mappings in order to
force them to be faulted back in on access.
    
Upstreamed patches link:
https://lore.kernel.org/kvm/158871401328.15589.17598154478222071285.stgit@gimli.home

Diff from v1:
Fixed build break problem.

[PATCH v2 v4.14.y 1/3]:
Backporting of upsream commit 41311242221e:
vfio/type1: Support faulting PFNMAP vmas
        
[PATCH v2 v4.14.y 2/3]:
Backporting of upsream commit 11c4cd07ba11:
vfio-pci: Fault mmaps to enable vma tracking
        
[PATCH v2 v4.14.y 3/3]:
Backporting of upsream commit abafbc551fdd:
vfio-pci: Invalidate mmaps and block MMIO access on disabled memory
```
#### [PATCH 0/2] x86/kvm: fix interrupts based APF mechanism
##### From: Vitaly Kuznetsov <vkuznets@redhat.com>

```c
From patchwork Tue Sep  8 13:53:48 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Vitaly Kuznetsov <vkuznets@redhat.com>
X-Patchwork-Id: 11764019
Return-Path: <SRS0=SnLg=CR=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 9218359D
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue,  8 Sep 2020 19:11:31 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 6DE6D2137B
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue,  8 Sep 2020 19:11:31 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="AA8RZ/lU"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1731717AbgIHTKv (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 8 Sep 2020 15:10:51 -0400
Received: from us-smtp-1.mimecast.com ([205.139.110.61]:49653 "EHLO
        us-smtp-delivery-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S1731224AbgIHQFX (ORCPT
        <rfc822;kvm@vger.kernel.org>); Tue, 8 Sep 2020 12:05:23 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1599581122;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=KJcoVDyKewg3G3aOBDZEKOnoV7moFsQCTbWTRI6UTAU=;
        b=AA8RZ/lU2h3Y8M6YLYzCQP01tD5i6cTJVsM0KRMjuAgsVZHNFYwBHOHtWAo1KYVKjN3CjX
        +FaJvKIWL++VBj29l9LJEAfLZSIBX4PAsAsEptnLRiXxJ7Lb7ge/YEh5GtJzMDtDNC5En7
        3j3plaAXDWI3c74z/MkoF/H3zSC8xeo=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-80-fQOSRBHaMYKFKVuipxgTTA-1; Tue, 08 Sep 2020 09:53:55 -0400
X-MC-Unique: fQOSRBHaMYKFKVuipxgTTA-1
Received: from smtp.corp.redhat.com (int-mx03.intmail.prod.int.phx2.redhat.com
 [10.5.11.13])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id D45F8801AE0;
        Tue,  8 Sep 2020 13:53:53 +0000 (UTC)
Received: from vitty.brq.redhat.com (unknown [10.40.194.93])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 90D7360DA0;
        Tue,  8 Sep 2020 13:53:51 +0000 (UTC)
From: Vitaly Kuznetsov <vkuznets@redhat.com>
To: kvm@vger.kernel.org, x86@kernel.org
Cc: Paolo Bonzini <pbonzini@redhat.com>,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        Thomas Gleixner <tglx@linutronix.de>,
        Ingo Molnar <mingo@redhat.com>, Borislav Petkov <bp@alien8.de>,
        Andy Lutomirski <luto@kernel.org>
Subject: [PATCH 0/2] x86/kvm: fix interrupts based APF mechanism
Date: Tue,  8 Sep 2020 15:53:48 +0200
Message-Id: <20200908135350.355053-1-vkuznets@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.13
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Linux-5.9 switched KVM guests to interrupt based APF mechanism for 'page
ready' events (instead of the previously used '#PF' exception) but a
collision with the newly introduced IDTENTRY magic happened and it wasn't
properly resolved. QEMU doesn't currently enable KVM_FEATURE_ASYNC_PF_INT
bit so the breakage is invisible but all KVM guests will hang as soon as
the bit will get exposed.

Vitaly Kuznetsov (2):
  x86/kvm: properly use DEFINE_IDTENTRY_SYSVEC() macro
  x86/kvm: don't forget to ACK async PF IRQ

 arch/x86/kernel/kvm.c | 4 +---
 1 file changed, 1 insertion(+), 3 deletions(-)
```
