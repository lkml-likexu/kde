

#### [PATCH v8 0/4] KVM: Add virtualization support of split lock
##### From: Xiaoyao Li <xiaoyao.li@intel.com>

```c
From patchwork Tue Apr 14 06:31:25 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Xiaoyao Li <xiaoyao.li@intel.com>
X-Patchwork-Id: 11486851
Return-Path: <SRS0=cOhZ=56=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 15B99913
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 14 Apr 2020 06:50:25 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 078662072D
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 14 Apr 2020 06:50:24 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2406108AbgDNGuU (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 14 Apr 2020 02:50:20 -0400
Received: from mga03.intel.com ([134.134.136.65]:58687 "EHLO mga03.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1728133AbgDNGuT (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 14 Apr 2020 02:50:19 -0400
IronPort-SDR: 
 OjmaLZZPHFzXUYE/kU+BQmnaIqwoO2JcFKOOOI+Lz5FuDhS08SlMtQRUHJABWsOCTMVuGZsN49
 3UCviNb4ac7w==
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from fmsmga004.fm.intel.com ([10.253.24.48])
  by orsmga103.jf.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 13 Apr 2020 23:50:18 -0700
IronPort-SDR: 
 wgRVshwsFChPpE0xUr6eMwqj/GGvkxPTReoUOG0k+ja+18dP5qIgyYiK100cEjZX5dAyGM1L+m
 J88BRrCVCLzw==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.72,381,1580803200";
   d="scan'208";a="277158309"
Received: from lxy-clx-4s.sh.intel.com ([10.239.43.132])
  by fmsmga004.fm.intel.com with ESMTP; 13 Apr 2020 23:50:13 -0700
From: Xiaoyao Li <xiaoyao.li@intel.com>
To: Paolo Bonzini <pbonzini@redhat.com>, kvm@vger.kernel.org,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        Thomas Gleixner <tglx@linutronix.de>
Cc: linux-kernel@vger.kernel.org, x86@kernel.org,
        Ingo Molnar <mingo@redhat.com>, Borislav Petkov <bp@alien8.de>,
        Andy Lutomirski <luto@kernel.org>,
        Peter Zijlstra <peterz@infradead.org>,
        Arvind Sankar <nivedita@alum.mit.edu>,
        Xiaoyao Li <xiaoyao.li@intel.com>
Subject: [PATCH v8 0/4] KVM: Add virtualization support of split lock
 detection
Date: Tue, 14 Apr 2020 14:31:25 +0800
Message-Id: <20200414063129.133630-1-xiaoyao.li@intel.com>
X-Mailer: git-send-email 2.20.1
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This series aims to add the virtualization of split lock detection in
KVM.

Due to the fact MSR TEST_CTRL is per-core scope, feature split lock
detection can be exposed to guest only when SMT is disabled/unsupported.

Changes in v8:
 - rebase to v5.7-rc1.
 - basic enabling of split lock detection already merged.
 - When host is sld_warn and nosmt, load guest's sld bit when in KVM
   context, i.e., between vmx_prepare_switch_to_guest() and before
   vmx_prepare_switch_to_host(), KVM uses guest sld setting.  

Changes in v7:
https://lkml.kernel.org/r/20200325030924.132881-1-xiaoyao.li@intel.com
 - only pick patch 1 and patch 2, and hold all the left.
 - Update SLD bit on each processor based on sld_state.

Changes in v6:
https://lkml.kernel.org/r/20200324151859.31068-1-xiaoyao.li@intel.com
 - Drop the sld_not_exist flag and use X86_FEATURE_SPLIT_LOCK_DETECT to
   check whether need to init split lock detection. [tglx]
 - Use tglx's method to verify the existence of split lock detectoin.
 - small optimization of sld_update_msr() that the default value of
   msr_test_ctrl_cache has split_lock_detect bit cleared.
 - Drop the patch3 in v5 that introducing kvm_only option. [tglx]
 - Rebase patch4-8 to kvm/queue.
 - use the new kvm-cpu-cap to expose X86_FEATURE_CORE_CAPABILITIES in
   Patch 6.

Changes in v5:
https://lkml.kernel.org/r/20200315050517.127446-1-xiaoyao.li@intel.com
 - Use X86_FEATURE_SPLIT_LOCK_DETECT flag in kvm to ensure split lock
   detection is really supported.
 - Add and export sld related helper functions in their related usecase 
   kvm patches.

Xiaoyao Li (4):
  kvm: x86: Emulate MSR IA32_CORE_CAPABILITIES
  kvm: vmx: Enable MSR TEST_CTRL for guest
  x86/split_lock: Export sld_update_msr() and sld_state
  kvm: vmx: virtualize split lock detection

 arch/x86/include/asm/cpu.h      | 12 +++++
 arch/x86/include/asm/kvm_host.h |  1 +
 arch/x86/kernel/cpu/intel.c     | 13 ++----
 arch/x86/kvm/cpuid.c            |  3 +-
 arch/x86/kvm/vmx/vmx.c          | 83 ++++++++++++++++++++++++++++++---
 arch/x86/kvm/vmx/vmx.h          |  2 +
 arch/x86/kvm/x86.c              | 35 +++++++++++++-
 7 files changed, 132 insertions(+), 17 deletions(-)
```
#### [PATCH 0/3] KVM: arm: vgic fixes for 5.7
##### From: Marc Zyngier <maz@kernel.org>
X-SA-Exim-Mail-From: maz@kernel.org

```c
From patchwork Tue Apr 14 10:35:14 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Marc Zyngier <maz@kernel.org>
X-Patchwork-Id: 11487239
Return-Path: <SRS0=cOhZ=56=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 05EFF913
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 14 Apr 2020 10:54:25 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id E21EE2072D
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 14 Apr 2020 10:54:24 +0000 (UTC)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple; d=kernel.org;
	s=default; t=1586861664;
	bh=HTu//z0XJEwQHak8IhhTICmq+Sn+E6x+AwgA/JSk24U=;
	h=From:To:Cc:Subject:Date:List-ID:From;
	b=zYZzeqJ1e0bN/k+2WM+y3zuqqHAQoUGGoZ/KRMdw79Sun1eWN9tbbU5xtLRcxCS+z
	 cx5woHQfMDmhxZyx8rmnwE2OZ9gMgDQZ8rrpZe4A5vYUujsrrT5wz/6Im3E/t2h6sX
	 2RKh6rzSZked7psodD2V412FT32WfBf7PMZ8gi08=
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2438672AbgDNKxu (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 14 Apr 2020 06:53:50 -0400
Received: from mail.kernel.org ([198.145.29.99]:39498 "EHLO mail.kernel.org"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S2438454AbgDNKfo (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 14 Apr 2020 06:35:44 -0400
Received: from disco-boy.misterjones.org (disco-boy.misterjones.org
 [51.254.78.96])
        (using TLSv1.2 with cipher ECDHE-RSA-AES256-GCM-SHA384 (256/256 bits))
        (No client certificate requested)
        by mail.kernel.org (Postfix) with ESMTPSA id CB11320644;
        Tue, 14 Apr 2020 10:35:43 +0000 (UTC)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple; d=kernel.org;
        s=default; t=1586860543;
        bh=HTu//z0XJEwQHak8IhhTICmq+Sn+E6x+AwgA/JSk24U=;
        h=From:To:Cc:Subject:Date:From;
        b=GdDDuxOITRb32SG16cxJkfmqBTuSmracfzbNyUVwKew4s1O3QM+NM/R98myCM3cPx
         XTaXr0KwHIvinwf+MvYrsrRu/IweRRydVlcpKzNHYCuUZRrCw65GWADQUEzGaUhFUy
         n4Jq5dPPrVyFsFsg0UbzF/nKfLscOIXq69XcLrI4=
Received: from 78.163-31-62.static.virginmediabusiness.co.uk ([62.31.163.78]
 helo=why.lan)
        by disco-boy.misterjones.org with esmtpsa
 (TLS1.3:ECDHE_RSA_AES_256_GCM_SHA384:256)
        (Exim 4.92)
        (envelope-from <maz@kernel.org>)
        id 1jOIus-0036te-6Q; Tue, 14 Apr 2020 11:35:42 +0100
From: Marc Zyngier <maz@kernel.org>
To: linux-arm-kernel@lists.infradead.org, kvmarm@lists.cs.columbia.edu,
        kvm@vger.kernel.org
Cc: Zenghui Yu <yuzenghui@huawei.com>,
        Eric Auger <eric.auger@redhat.com>,
        Andre Przywara <Andre.Przywara@arm.com>,
        Julien Grall <julien@xen.org>,
        James Morse <james.morse@arm.com>,
        Julien Thierry <julien.thierry.kdev@gmail.com>,
        Suzuki K Poulose <suzuki.poulose@arm.com>
Subject: [PATCH 0/3] KVM: arm: vgic fixes for 5.7
Date: Tue, 14 Apr 2020 11:35:14 +0100
Message-Id: <20200414103517.2824071-1-maz@kernel.org>
X-Mailer: git-send-email 2.25.1
MIME-Version: 1.0
X-SA-Exim-Connect-IP: 62.31.163.78
X-SA-Exim-Rcpt-To: linux-arm-kernel@lists.infradead.org,
 kvmarm@lists.cs.columbia.edu, kvm@vger.kernel.org, yuzenghui@huawei.com,
 eric.auger@redhat.com, Andre.Przywara@arm.com, julien@xen.org,
 james.morse@arm.com, julien.thierry.kdev@gmail.com, suzuki.poulose@arm.com
X-SA-Exim-Mail-From: maz@kernel.org
X-SA-Exim-Scanned: No (on disco-boy.misterjones.org);
 SAEximRunCond expanded to false
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Here's a few fixes I've been piling on during the merge window.

The first patch improves the handling of the ACTIVE registers, which
we never synchronise on the read side (the distributor state can only
be updated when the vcpu exits). Let's fix it the same way we do it on
the write side (stop-the-world, read, restart). Yes, this is
expensive.

The last two patches deal with an issue where we consider the HW state
of an interrupt when responding to a userspace access. We should never
do this, as the guest shouldn't be running at this stage and if it is,
it is absolutely fine to return random bits to userspace. It could
also be that there is no active guest context at this stage, and you
end up with an Oops, which nobody really enjoys.

Marc Zyngier (3):
  KVM: arm: vgic: Synchronize the whole guest on GIC{D,R}_I{S,C}ACTIVER
    read
  KVM: arm: vgic: Only use the virtual state when userspace accesses
    enable bits
  KVM: arm: vgic-v2: Only use the virtual state when userspace accesses
    pending bits

 virt/kvm/arm/vgic/vgic-mmio-v2.c |  16 ++-
 virt/kvm/arm/vgic/vgic-mmio-v3.c |  20 ++--
 virt/kvm/arm/vgic/vgic-mmio.c    | 183 +++++++++++++++++++++++++------
 virt/kvm/arm/vgic/vgic-mmio.h    |  19 ++++
 4 files changed, 188 insertions(+), 50 deletions(-)
```
#### [PATCH kvmtool 00/18] Various fixes
##### From: Alexandru Elisei <alexandru.elisei@arm.com>

```c
From patchwork Tue Apr 14 14:39:28 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Alexandru Elisei <alexandru.elisei@arm.com>
X-Patchwork-Id: 11487967
Return-Path: <SRS0=cOhZ=56=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 7565492C
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 14 Apr 2020 14:44:13 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 6730420CC7
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 14 Apr 2020 14:44:13 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2391039AbgDNOkB (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 14 Apr 2020 10:40:01 -0400
Received: from foss.arm.com ([217.140.110.172]:57094 "EHLO foss.arm.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S2391025AbgDNOj6 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 14 Apr 2020 10:39:58 -0400
Received: from usa-sjc-imap-foss1.foss.arm.com (unknown [10.121.207.14])
        by usa-sjc-mx-foss1.foss.arm.com (Postfix) with ESMTP id 7F2F630E;
        Tue, 14 Apr 2020 07:39:57 -0700 (PDT)
Received: from e123195-lin.cambridge.arm.com (e123195-lin.cambridge.arm.com
 [10.1.196.63])
        by usa-sjc-imap-foss1.foss.arm.com (Postfix) with ESMTPA id
 95A8D3F73D;
        Tue, 14 Apr 2020 07:39:56 -0700 (PDT)
From: Alexandru Elisei <alexandru.elisei@arm.com>
To: kvm@vger.kernel.org
Cc: will@kernel.org, julien.thierry.kdev@gmail.com,
        andre.przywara@arm.com, sami.mujawar@arm.com,
        lorenzo.pieralisi@arm.com
Subject: [PATCH kvmtool 00/18] Various fixes
Date: Tue, 14 Apr 2020 15:39:28 +0100
Message-Id: <20200414143946.1521-1-alexandru.elisei@arm.com>
X-Mailer: git-send-email 2.20.1
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

I've taken the fixes from my reassignable BARs and PCIE support series [1]
and created this series because 1. they can be taken independently and 2.
rebasing a 32 patch series was getting very tedious.

Changes from the original series:

* Gathered Reviewed-by tags. Only patch #14 "virtio: Don't ignore
  initialization failures" doesn't have one.
* The virtio net device now frees the allocated devices and the ops copy on
  failure in patch #14.

[1] https://www.spinics.net/lists/kvm/msg211272.html

Alexandru Elisei (14):
  Makefile: Use correct objcopy binary when cross-compiling for x86_64
  hw/i8042: Compile only for x86
  Remove pci-shmem device
  Check that a PCI device's memory size is power of two
  arm/pci: Advertise only PCI bus 0 in the DT
  vfio/pci: Allocate correct size for MSIX table and PBA BARs
  vfio/pci: Don't assume that only even numbered BARs are 64bit
  vfio/pci: Ignore expansion ROM BAR writes
  vfio/pci: Don't access unallocated regions
  virtio: Don't ignore initialization failures
  Don't ignore errors registering a device, ioport or mmio emulation
  hw/vesa: Don't ignore fatal errors
  hw/vesa: Set the size for BAR 0
  ioport: Fail when registering overlapping ports

Julien Thierry (3):
  ioport: pci: Move port allocations to PCI devices
  pci: Fix ioport allocation size
  virtio/pci: Make memory and IO BARs independent

Sami Mujawar (1):
  pci: Fix BAR resource sizing arbitration

 Makefile                       |   6 +-
 arm/ioport.c                   |   3 +-
 arm/pci.c                      |   2 +-
 builtin-run.c                  |   5 -
 hw/i8042.c                     |  14 +-
 hw/pci-shmem.c                 | 400 ---------------------------------
 hw/vesa.c                      |  34 ++-
 include/kvm/devices.h          |   3 +-
 include/kvm/ioport.h           |  10 +-
 include/kvm/kvm.h              |   7 +-
 include/kvm/pci-shmem.h        |  32 ---
 include/kvm/pci.h              |   4 +-
 include/kvm/util.h             |   2 +
 include/kvm/vesa.h             |   6 +-
 include/kvm/virtio.h           |   7 +-
 include/linux/compiler.h       |   2 +-
 ioport.c                       |  50 ++---
 mips/kvm.c                     |   3 +-
 pci.c                          |  59 ++++-
 powerpc/include/kvm/kvm-arch.h |   2 +-
 powerpc/ioport.c               |   3 +-
 vfio/core.c                    |   6 +-
 vfio/pci.c                     |  87 +++++--
 virtio/9p.c                    |   9 +-
 virtio/balloon.c               |  10 +-
 virtio/blk.c                   |  14 +-
 virtio/console.c               |  11 +-
 virtio/core.c                  |   9 +-
 virtio/mmio.c                  |  13 +-
 virtio/net.c                   |  45 ++--
 virtio/pci.c                   |  78 ++++---
 virtio/scsi.c                  |  14 +-
 x86/include/kvm/kvm-arch.h     |   2 +-
 x86/ioport.c                   |  66 ++++--
 34 files changed, 384 insertions(+), 634 deletions(-)
 delete mode 100644 hw/pci-shmem.c
 delete mode 100644 include/kvm/pci-shmem.h
```
#### [PATCH v11 00/13] SMMUv3 Nested Stage Setup (IOMMU part)
##### From: Eric Auger <eric.auger@redhat.com>

```c
From patchwork Tue Apr 14 15:05:54 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Eric Auger <eric.auger@redhat.com>
X-Patchwork-Id: 11488201
Return-Path: <SRS0=cOhZ=56=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 07E6192C
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 14 Apr 2020 15:16:08 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id DDD1A2076D
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 14 Apr 2020 15:16:07 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="Z/lndZOZ"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2437995AbgDNPQE (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 14 Apr 2020 11:16:04 -0400
Received: from us-smtp-2.mimecast.com ([205.139.110.61]:23505 "EHLO
        us-smtp-delivery-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S2407288AbgDNPGo (ORCPT
        <rfc822;kvm@vger.kernel.org>); Tue, 14 Apr 2020 11:06:44 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1586876802;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=gD722PN6ndX2Ky7HUW8f5x6XQX7yxgYbbOC6l5hh6w8=;
        b=Z/lndZOZDXPNxHWq52ZvVy9GjGXP/++Pt2LQkCTNPsHkV9d0obiAH23lyYAiNJhP3Npa3A
        GI7mq0L0eb+ASlUiFjZSg7QNVNfVH8YGRWhwEcGlbxmNnJXFv5fKqyIDYsTCxr5ubFJzCo
        +guGe5PUlto+Lni8W/o9dlgGBQk4hHA=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-412-CkgRZL-OMimvAKL0BDNpJA-1; Tue, 14 Apr 2020 11:06:37 -0400
X-MC-Unique: CkgRZL-OMimvAKL0BDNpJA-1
Received: from smtp.corp.redhat.com (int-mx08.intmail.prod.int.phx2.redhat.com
 [10.5.11.23])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 459CD800D5C;
        Tue, 14 Apr 2020 15:06:34 +0000 (UTC)
Received: from laptop.redhat.com (ovpn-115-53.ams2.redhat.com [10.36.115.53])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 9CADD19C69;
        Tue, 14 Apr 2020 15:06:23 +0000 (UTC)
From: Eric Auger <eric.auger@redhat.com>
To: eric.auger.pro@gmail.com, eric.auger@redhat.com,
        iommu@lists.linux-foundation.org, linux-kernel@vger.kernel.org,
        kvm@vger.kernel.org, kvmarm@lists.cs.columbia.edu, will@kernel.org,
        joro@8bytes.org, maz@kernel.org, robin.murphy@arm.com
Cc: jean-philippe@linaro.org, zhangfei.gao@linaro.org,
        shameerali.kolothum.thodi@huawei.com, alex.williamson@redhat.com,
        jacob.jun.pan@linux.intel.com, yi.l.liu@intel.com,
        peter.maydell@linaro.org, zhangfei.gao@gmail.com, tn@semihalf.com,
        zhangfei.gao@foxmail.com, bbhushan2@marvell.com
Subject: [PATCH v11 00/13] SMMUv3 Nested Stage Setup (IOMMU part)
Date: Tue, 14 Apr 2020 17:05:54 +0200
Message-Id: <20200414150607.28488-1-eric.auger@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.84 on 10.5.11.23
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This version fixes an issue observed by Shameer on an SMMU 3.2,
when moving from dual stage config to stage 1 only config.
The 2 high 64b of the STE now get reset. Otherwise, leaving the
S2TTB set may cause a C_BAD_STE error.

This series can be found at:
https://github.com/eauger/linux/tree/v5.6-2stage-v11_10.1
(including the VFIO part)
The QEMU fellow series still can be found at:
https://github.com/eauger/qemu/tree/v4.2.0-2stage-rfcv6

Users have expressed interest in that work and tested v9/v10:
- https://patchwork.kernel.org/cover/11039995/#23012381
- https://patchwork.kernel.org/cover/11039995/#23197235

Background:

This series brings the IOMMU part of HW nested paging support
in the SMMUv3. The VFIO part is submitted separately.

The IOMMU API is extended to support 2 new API functionalities:
1) pass the guest stage 1 configuration
2) pass stage 1 MSI bindings

Then those capabilities gets implemented in the SMMUv3 driver.

The virtualizer passes information through the VFIO user API
which cascades them to the iommu subsystem. This allows the guest
to own stage 1 tables and context descriptors (so-called PASID
table) while the host owns stage 2 tables and main configuration
structures (STE).

Best Regards

Eric


History:

v10 -> v11:
- S2TTB reset when S2 is off
- fix compil issue when CONFIG_IOMMU_DMA is not set

v9 -> v10:
- rebase on top of 5.6.0-rc3

v8 -> v9:
- rebase on 5.3
- split iommu/vfio parts

v6 -> v8:
- Implement VFIO-PCI device specific interrupt framework

v7 -> v8:
- rebase on top of v5.2-rc1 and especially
  8be39a1a04c1  iommu/arm-smmu-v3: Add a master->domain pointer
- dynamic alloc of s1_cfg/s2_cfg
- __arm_smmu_tlb_inv_asid/s1_range_nosync
- check there is no HW MSI regions
- asid invalidation using pasid extended struct (change in the uapi)
- add s1_live/s2_live checks
- move check about support of nested stages in domain finalise
- fixes in error reporting according to the discussion with Robin
- reordered the patches to have first iommu/smmuv3 patches and then
  VFIO patches

v6 -> v7:
- removed device handle from bind/unbind_guest_msi
- added "iommu/smmuv3: Nested mode single MSI doorbell per domain
  enforcement"
- added few uapi comments as suggested by Jean, Jacop and Alex

v5 -> v6:
- Fix compilation issue when CONFIG_IOMMU_API is unset

v4 -> v5:
- fix bug reported by Vincent: fault handler unregistration now happens in
  vfio_pci_release
- IOMMU_FAULT_PERM_* moved outside of struct definition + small
  uapi changes suggested by Kean-Philippe (except fetch_addr)
- iommu: introduce device fault report API: removed the PRI part.
- see individual logs for more details
- reset the ste abort flag on detach

v3 -> v4:
- took into account Alex, jean-Philippe and Robin's comments on v3
- rework of the smmuv3 driver integration
- add tear down ops for msi binding and PASID table binding
- fix S1 fault propagation
- put fault reporting patches at the beginning of the series following
  Jean-Philippe's request
- update of the cache invalidate and fault API uapis
- VFIO fault reporting rework with 2 separate regions and one mmappable
  segment for the fault queue
- moved to PATCH

v2 -> v3:
- When registering the S1 MSI binding we now store the device handle. This
  addresses Robin's comment about discimination of devices beonging to
  different S1 groups and using different physical MSI doorbells.
- Change the fault reporting API: use VFIO_PCI_DMA_FAULT_IRQ_INDEX to
  set the eventfd and expose the faults through an mmappable fault region

v1 -> v2:
- Added the fault reporting capability
- asid properly passed on invalidation (fix assignment of multiple
  devices)
- see individual change logs for more info

Eric Auger (11):
  iommu: Introduce bind/unbind_guest_msi
  iommu/smmuv3: Dynamically allocate s1_cfg and s2_cfg
  iommu/smmuv3: Get prepared for nested stage support
  iommu/smmuv3: Implement attach/detach_pasid_table
  iommu/smmuv3: Allow stage 1 invalidation with unmanaged ASIDs
  iommu/smmuv3: Implement cache_invalidate
  dma-iommu: Implement NESTED_MSI cookie
  iommu/smmuv3: Nested mode single MSI doorbell per domain enforcement
  iommu/smmuv3: Enforce incompatibility between nested mode and HW MSI
    regions
  iommu/smmuv3: Implement bind/unbind_guest_msi
  iommu/smmuv3: Report non recoverable faults

Jacob Pan (1):
  iommu: Introduce attach/detach_pasid_table API

Jean-Philippe Brucker (1):
  iommu/arm-smmu-v3: Maintain a SID->device structure

 drivers/iommu/arm-smmu-v3.c | 744 ++++++++++++++++++++++++++++++++----
 drivers/iommu/dma-iommu.c   | 142 ++++++-
 drivers/iommu/iommu.c       |  56 +++
 include/linux/dma-iommu.h   |  16 +
 include/linux/iommu.h       |  38 ++
 include/uapi/linux/iommu.h  |  51 +++
 6 files changed, 975 insertions(+), 72 deletions(-)
```
#### [PATCH v2 00/33] Documentation fixes for Kernel 5.8
##### From: Mauro Carvalho Chehab <mchehab+huawei@kernel.org>

```c
From patchwork Tue Apr 14 16:48:26 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Mauro Carvalho Chehab <mchehab+huawei@kernel.org>
X-Patchwork-Id: 11488685
Return-Path: <SRS0=cOhZ=56=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 67055174A
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 14 Apr 2020 16:55:55 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 4DEFF2074D
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 14 Apr 2020 16:55:55 +0000 (UTC)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple; d=kernel.org;
	s=default; t=1586883355;
	bh=hpU3ilpDhIBh1EkpHoT8CRglKxDNGuySrswIRHuRmXU=;
	h=From:To:Cc:Subject:Date:List-ID:From;
	b=jzGKCByLRH3OZ7BcIaCQAy54Ywkemln+VD1p6O2hE2Nw9XG7xplqqGY1Ma8ZCCkNP
	 ermHwYSGGPTFlHWri4klrzyAWKq4WW7vOykGe9lpLzH9WUZFi7ngli2M2Im6h59T7l
	 NmpcibggHnaAiU1hpgpd2XqNafMXpTUcVKe6h+XM=
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2391913AbgDNQz0 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 14 Apr 2020 12:55:26 -0400
Received: from mail.kernel.org ([198.145.29.99]:55194 "EHLO mail.kernel.org"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S2440299AbgDNQtI (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 14 Apr 2020 12:49:08 -0400
Received: from mail.kernel.org (ip5f5ad4d8.dynamic.kabel-deutschland.de
 [95.90.212.216])
        (using TLSv1.2 with cipher ECDHE-RSA-AES256-GCM-SHA384 (256/256 bits))
        (No client certificate requested)
        by mail.kernel.org (Postfix) with ESMTPSA id 64BDD20787;
        Tue, 14 Apr 2020 16:49:02 +0000 (UTC)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple; d=kernel.org;
        s=default; t=1586882942;
        bh=hpU3ilpDhIBh1EkpHoT8CRglKxDNGuySrswIRHuRmXU=;
        h=From:To:Cc:Subject:Date:From;
        b=qP/fh2JuBrTWMBDU0Po9QgHcYacrRlFhnHwEY8en7h953JH1K2J6xRWgtWi+ouXIY
         3gGiDenojv2rrUzJ4Wxk3whARW64aaikv0MOeHbofi1sPuRVe5IZT8BpzPaRPNxcO+
         07Ps8XSWU9UmRtIfijlblMPlQG+5+iBYwuA7KjAY=
Received: from mchehab by mail.kernel.org with local (Exim 4.92.3)
        (envelope-from <mchehab@kernel.org>)
        id 1jOOk8-0068kv-FR; Tue, 14 Apr 2020 18:49:00 +0200
From: Mauro Carvalho Chehab <mchehab+huawei@kernel.org>
To: Linux Doc Mailing List <linux-doc@vger.kernel.org>
Cc: Mauro Carvalho Chehab <mchehab+huawei@kernel.org>,
        linux-kernel@vger.kernel.org, Jonathan Corbet <corbet@lwn.net>,
        Rob Herring <robh@kernel.org>,
        Maxime Ripard <maxime@cerno.tech>,
        Linus Walleij <linus.walleij@linaro.org>,
        Sudeep Holla <sudeep.holla@arm.com>,
        Kishon Vijay Abraham I <kishon@ti.com>,
        Yuti Amonkar <yamonkar@cadence.com>,
        devicetree@vger.kernel.org, linux-arch@vger.kernel.org,
        kvm@vger.kernel.org, kvm-ppc@vger.kernel.org,
        linuxppc-dev@lists.ozlabs.org, dri-devel@lists.freedesktop.org,
        linux-arm-kernel@lists.infradead.org,
        linux-fsdevel@vger.kernel.org, linux-unionfs@vger.kernel.org,
        linux-mm@kvack.org, linux-rdma@vger.kernel.org,
        kvmarm@lists.cs.columbia.edu, linux-crypto@vger.kernel.org,
        linux-media@vger.kernel.org, linux-arm-msm@vger.kernel.org,
        freedreno@lists.freedesktop.org, linux-afs@lists.infradead.org,
        ecryptfs@vger.kernel.org, linux-ntfs-dev@lists.sourceforge.net,
        ocfs2-devel@oss.oracle.com, linux-pci@vger.kernel.org,
        linux-edac@vger.kernel.org, linux-spi@vger.kernel.org,
        Sandeep Maheswaram <sanm@codeaurora.org>,
        Stephen Boyd <swboyd@chromium.org>,
        Matthias Kaehlcke <mka@chromium.org>,
        linux-usb@vger.kernel.org,
        Geert Uytterhoeven <geert+renesas@glider.be>,
        Matthias Brugger <mbrugger@suse.com>, netdev@vger.kernel.org,
        linux-i2c@vger.kernel.org, linux-rockchip@lists.infradead.org,
        linux-ide@vger.kernel.org, linux1394-devel@lists.sourceforge.net
Subject: [PATCH v2 00/33] Documentation fixes for Kernel 5.8
Date: Tue, 14 Apr 2020 18:48:26 +0200
Message-Id: <cover.1586881715.git.mchehab+huawei@kernel.org>
X-Mailer: git-send-email 2.25.2
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Patches 1 to 5 contain changes to the documentation toolset:

- The first 3 patches help to reduce a lot the number of reported
  kernel-doc issues, by making the tool more smart.

- Patches 4 and 5 are meant to partially address the PDF
  build, with now requires Sphinx version 2.4 or upper.

The remaining patches fix broken references detected by
this tool:

        ./scripts/documentation-file-ref-check

and address other random errors due to tags being mis-interpreted
or mis-used.

They are independent each other, but some may depend on
the kernel-doc improvements.

PS.: Due to the large number of C/C, I opted to keep a smaller
set of C/C at this first e-mail (only e-mails with "L:" tag from
MAINTAINERS file).

Jon,

Those patches should apply cleanly at docs-next, once you
pull from v5.7-rc1.


-

v2:

- patches re-ordered;
- added reviewed/acked-by tags;
- rebased on the top of docs-next + v5.7-rc1.


Mauro Carvalho Chehab (33):
  scripts: kernel-doc: proper handle @foo->bar()
  scripts: kernel-doc: accept negation like !@var
  scripts: kernel-doc: accept blank lines on parameter description
  docs: update recommended Sphinx version to 2.4.4
  docs: LaTeX/PDF: drop list of documents
  MAINTAINERS: dt: update display/allwinner file entry
  MAINTAINERS: dt: fix pointers for ARM Integrator, Versatile and
    RealView
  docs: dt: fix broken reference to phy-cadence-torrent.yaml
  docs: fix broken references to text files
  docs: fix broken references for ReST files that moved around
  docs: filesystems: fix renamed references
  docs: amu: supress some Sphinx warnings
  docs: arm64: booting.rst: get rid of some warnings
  docs: pci: boot-interrupts.rst: improve html output
  docs: ras: get rid of some warnings
  docs: ras: don't need to repeat twice the same thing
  docs: infiniband: verbs.c: fix some documentation warnings
  docs: spi: spi.h: fix a doc building warning
  docs: drivers: fix some warnings at base/platform.c when building docs
  docs: mm: userfaultfd.rst: use ``foo`` for literals
  docs: mm: userfaultfd.rst: use a cross-reference for a section
  docs: vm: index.rst: add an orphan doc to the building system
  docs: dt: qcom,dwc3.txt: fix cross-reference for a converted file
  docs: dt: fix a broken reference for a file converted to json
  docs: powerpc: cxl.rst: mark two section titles as such
  docs: i2c: rename i2c.svg to i2c_bus.svg
  docs: Makefile: place final pdf docs on a separate dir
  docs: dt: rockchip,dwc3.txt: fix a pointer to a renamed file
  ata: libata-core: fix a doc warning
  firewire: firewire-cdev.hL get rid of a docs warning
  fs: inode.c: get rid of docs warnings
  futex: get rid of a kernel-docs build warning
  lib: bitmap.c: get rid of some doc warnings

 Documentation/ABI/stable/sysfs-devices-node   |   2 +-
 Documentation/ABI/testing/procfs-smaps_rollup |   2 +-
 Documentation/Makefile                        |   6 +-
 Documentation/PCI/boot-interrupts.rst         |  34 +--
 Documentation/admin-guide/cpu-load.rst        |   2 +-
 Documentation/admin-guide/mm/userfaultfd.rst  | 209 +++++++++---------
 Documentation/admin-guide/nfs/nfsroot.rst     |   2 +-
 Documentation/admin-guide/ras.rst             |  18 +-
 Documentation/arm64/amu.rst                   |   5 +
 Documentation/arm64/booting.rst               |  36 +--
 Documentation/conf.py                         |  38 ----
 .../bindings/net/qualcomm-bluetooth.txt       |   2 +-
 .../bindings/phy/ti,phy-j721e-wiz.yaml        |   2 +-
 .../devicetree/bindings/usb/qcom,dwc3.txt     |   4 +-
 .../devicetree/bindings/usb/rockchip,dwc3.txt |   2 +-
 .../doc-guide/maintainer-profile.rst          |   2 +-
 .../driver-api/driver-model/device.rst        |   4 +-
 .../driver-api/driver-model/overview.rst      |   2 +-
 Documentation/filesystems/dax.txt             |   2 +-
 Documentation/filesystems/dnotify.txt         |   2 +-
 .../filesystems/ramfs-rootfs-initramfs.rst    |   2 +-
 Documentation/filesystems/sysfs.rst           |   2 +-
 Documentation/i2c/{i2c.svg => i2c_bus.svg}    |   2 +-
 Documentation/i2c/summary.rst                 |   2 +-
 Documentation/memory-barriers.txt             |   2 +-
 Documentation/powerpc/cxl.rst                 |   2 +
 .../powerpc/firmware-assisted-dump.rst        |   2 +-
 Documentation/process/adding-syscalls.rst     |   2 +-
 Documentation/process/submit-checklist.rst    |   2 +-
 Documentation/sphinx/requirements.txt         |   2 +-
 .../it_IT/process/adding-syscalls.rst         |   2 +-
 .../it_IT/process/submit-checklist.rst        |   2 +-
 .../translations/ko_KR/memory-barriers.txt    |   2 +-
 .../translations/zh_CN/filesystems/sysfs.txt  |   8 +-
 .../zh_CN/process/submit-checklist.rst        |   2 +-
 Documentation/virt/kvm/arm/pvtime.rst         |   2 +-
 Documentation/virt/kvm/devices/vcpu.rst       |   2 +-
 Documentation/virt/kvm/hypercalls.rst         |   4 +-
 Documentation/virt/kvm/mmu.rst                |   2 +-
 Documentation/virt/kvm/review-checklist.rst   |   2 +-
 Documentation/vm/index.rst                    |   1 +
 MAINTAINERS                                   |   7 +-
 arch/powerpc/include/uapi/asm/kvm_para.h      |   2 +-
 arch/x86/kvm/mmu/mmu.c                        |   2 +-
 drivers/ata/libata-core.c                     |   2 +-
 drivers/base/core.c                           |   2 +-
 drivers/base/platform.c                       |   6 +-
 .../allwinner/sun8i-ce/sun8i-ce-cipher.c      |   2 +-
 .../crypto/allwinner/sun8i-ce/sun8i-ce-core.c |   2 +-
 .../allwinner/sun8i-ss/sun8i-ss-cipher.c      |   2 +-
 .../crypto/allwinner/sun8i-ss/sun8i-ss-core.c |   2 +-
 drivers/gpu/drm/Kconfig                       |   2 +-
 drivers/gpu/drm/drm_ioctl.c                   |   2 +-
 drivers/gpu/drm/msm/disp/dpu1/dpu_kms.h       |   2 +-
 drivers/hwtracing/coresight/Kconfig           |   2 +-
 drivers/infiniband/core/verbs.c               |   7 +-
 drivers/media/v4l2-core/v4l2-fwnode.c         |   2 +-
 fs/Kconfig                                    |   2 +-
 fs/Kconfig.binfmt                             |   2 +-
 fs/adfs/Kconfig                               |   2 +-
 fs/affs/Kconfig                               |   2 +-
 fs/afs/Kconfig                                |   6 +-
 fs/bfs/Kconfig                                |   2 +-
 fs/cramfs/Kconfig                             |   2 +-
 fs/ecryptfs/Kconfig                           |   2 +-
 fs/fat/Kconfig                                |   8 +-
 fs/fuse/Kconfig                               |   2 +-
 fs/fuse/dev.c                                 |   2 +-
 fs/hfs/Kconfig                                |   2 +-
 fs/hpfs/Kconfig                               |   2 +-
 fs/inode.c                                    |   6 +-
 fs/isofs/Kconfig                              |   2 +-
 fs/namespace.c                                |   2 +-
 fs/notify/inotify/Kconfig                     |   2 +-
 fs/ntfs/Kconfig                               |   2 +-
 fs/ocfs2/Kconfig                              |   2 +-
 fs/overlayfs/Kconfig                          |   6 +-
 fs/proc/Kconfig                               |   4 +-
 fs/romfs/Kconfig                              |   2 +-
 fs/sysfs/dir.c                                |   2 +-
 fs/sysfs/file.c                               |   2 +-
 fs/sysfs/mount.c                              |   2 +-
 fs/sysfs/symlink.c                            |   2 +-
 fs/sysv/Kconfig                               |   2 +-
 fs/udf/Kconfig                                |   2 +-
 include/linux/kobject.h                       |   2 +-
 include/linux/kobject_ns.h                    |   2 +-
 include/linux/mm.h                            |   4 +-
 include/linux/relay.h                         |   2 +-
 include/linux/spi/spi.h                       |   1 +
 include/linux/sysfs.h                         |   2 +-
 include/uapi/linux/ethtool_netlink.h          |   2 +-
 include/uapi/linux/firewire-cdev.h            |   2 +-
 include/uapi/linux/kvm.h                      |   4 +-
 include/uapi/rdma/rdma_user_ioctl_cmds.h      |   2 +-
 kernel/futex.c                                |   3 +
 kernel/relay.c                                |   2 +-
 lib/bitmap.c                                  |  27 +--
 lib/kobject.c                                 |   4 +-
 mm/gup.c                                      |  12 +-
 scripts/kernel-doc                            |  41 ++--
 tools/include/uapi/linux/kvm.h                |   4 +-
 virt/kvm/arm/vgic/vgic-mmio-v3.c              |   2 +-
 virt/kvm/arm/vgic/vgic.h                      |   4 +-
 104 files changed, 343 insertions(+), 326 deletions(-)
 rename Documentation/i2c/{i2c.svg => i2c_bus.svg} (99%)
```
#### [PATCH 0/2] KVM: SVM: Implement check_nested_events for NMI 
##### From: Cathy Avery <cavery@redhat.com>

```c
From patchwork Tue Apr 14 20:11:05 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Cathy Avery <cavery@redhat.com>
X-Patchwork-Id: 11489153
Return-Path: <SRS0=cOhZ=56=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 3410481
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 14 Apr 2020 20:11:45 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 115972076B
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 14 Apr 2020 20:11:45 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="dz/boa2k"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1731089AbgDNULl (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 14 Apr 2020 16:11:41 -0400
Received: from us-smtp-2.mimecast.com ([205.139.110.61]:54399 "EHLO
        us-smtp-delivery-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S2632743AbgDNULR (ORCPT
        <rfc822;kvm@vger.kernel.org>); Tue, 14 Apr 2020 16:11:17 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1586895076;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=xeep/J8xI+LK6UPyUtnwUk8kuNhohlFBWm/FMlc2jnk=;
        b=dz/boa2knLQWYLytWrVwWQubQVYsEJPHnRRHZx1yc+r00n7yA5Hy2H9knvbD8SF2Jayon2
        RQzRiMCm/4TQhmtQ6fxYzYsaKtcMe2a7WGawYhP34a8yw41fwh0XLGjTI8GuhO9WBt9Qva
        wp9iIi9prRTtc20Vb7ehimL9JK5vMDw=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-134-SJqVODYlPQ-l1RXsl6frEg-1; Tue, 14 Apr 2020 16:11:12 -0400
X-MC-Unique: SJqVODYlPQ-l1RXsl6frEg-1
Received: from smtp.corp.redhat.com (int-mx04.intmail.prod.int.phx2.redhat.com
 [10.5.11.14])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 6395D18C8C0F;
        Tue, 14 Apr 2020 20:11:11 +0000 (UTC)
Received: from localhost.localdomain.com (ovpn-113-69.rdu2.redhat.com
 [10.10.113.69])
        by smtp.corp.redhat.com (Postfix) with ESMTP id CDC3C5DA66;
        Tue, 14 Apr 2020 20:11:07 +0000 (UTC)
From: Cathy Avery <cavery@redhat.com>
To: linux-kernel@vger.kernel.org, kvm@vger.kernel.org,
        pbonzini@redhat.com
Cc: vkuznets@redhat.com, wei.huang2@amd.com
Subject: [PATCH 0/2] KVM: SVM: Implement check_nested_events for NMI 
Date: Tue, 14 Apr 2020 16:11:05 -0400
Message-Id: <20200414201107.22952-1-cavery@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.14
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Moved nested NMI exit to new check_nested_events.
The second patch fixes the NMI pending race condition that now occurs.

Cathy Avery (2):
  KVM: SVM: Implement check_nested_events for NMI
  KVM: x86: check_nested_events if there is an injectable NMI

 arch/x86/kvm/svm/nested.c | 21 +++++++++++++++++++++
 arch/x86/kvm/svm/svm.c    |  2 +-
 arch/x86/kvm/svm/svm.h    | 15 ---------------
 arch/x86/kvm/x86.c        | 15 +++++++++++----
 4 files changed, 33 insertions(+), 20 deletions(-)
```
