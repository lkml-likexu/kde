

#### [PATCH v3 00/17] KVM: arm64: Preliminary NV patches
##### From: Marc Zyngier <maz@kernel.org>
X-SA-Exim-Mail-From: maz@kernel.org

```c
From patchwork Mon Jul  6 12:54:08 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Marc Zyngier <maz@kernel.org>
X-Patchwork-Id: 11645657
Return-Path: <SRS0=fXy1=AR=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id BF91B1398
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon,  6 Jul 2020 12:54:54 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id A354920890
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon,  6 Jul 2020 12:54:54 +0000 (UTC)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple; d=kernel.org;
	s=default; t=1594040094;
	bh=yca9xk6P8snhKJUm0y6TqWUwjotGciKCUrrvMHIpCLU=;
	h=From:To:Cc:Subject:Date:List-ID:From;
	b=ceJJCkAkBiuAg2bfSG8u6QWfEDM9hr7PCcXjXodjy+a03XQIbKW/266iL3r2L/wYm
	 ilrc2qjmCRlyLlcmol1W3JQmOa0REUabAZjIHKF9LT4jUsV8NvD3Hyv8xnB58RuTiX
	 2kAexrFvgPuwR/WG3JioY4ne+lFgZjcM6GDz/7ZU=
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729056AbgGFMyx (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 6 Jul 2020 08:54:53 -0400
Received: from mail.kernel.org ([198.145.29.99]:40522 "EHLO mail.kernel.org"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1728940AbgGFMyx (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 6 Jul 2020 08:54:53 -0400
Received: from disco-boy.misterjones.org (disco-boy.misterjones.org
 [51.254.78.96])
        (using TLSv1.2 with cipher ECDHE-RSA-AES256-GCM-SHA384 (256/256 bits))
        (No client certificate requested)
        by mail.kernel.org (Postfix) with ESMTPSA id 4ED1320722;
        Mon,  6 Jul 2020 12:54:52 +0000 (UTC)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple; d=kernel.org;
        s=default; t=1594040092;
        bh=yca9xk6P8snhKJUm0y6TqWUwjotGciKCUrrvMHIpCLU=;
        h=From:To:Cc:Subject:Date:From;
        b=zzZPZE2fKFaDHraTQ909PkhnQCUsVhnxYMgngAt/F/2OXIjsZdmoRy27hOMe0pGyZ
         KiteWoz/gKYG1cP/bx7L0aHPLozZnkNMby50U9bTig9cWis/NQc4TazuM44pdz7JZo
         z2gr+NDFGMBvx2gYGLpAx9kxkfjC8alAJS68zNho=
Received: from 78.163-31-62.static.virginmediabusiness.co.uk ([62.31.163.78]
 helo=why.lan)
        by disco-boy.misterjones.org with esmtpsa
 (TLS1.3:ECDHE_RSA_AES_256_GCM_SHA384:256)
        (Exim 4.92)
        (envelope-from <maz@kernel.org>)
        id 1jsQe2-009SCo-KK; Mon, 06 Jul 2020 13:54:50 +0100
From: Marc Zyngier <maz@kernel.org>
To: Catalin Marinas <catalin.marinas@arm.com>,
        linux-arm-kernel@lists.infradead.org, kvmarm@lists.cs.columbia.edu,
        kvm@vger.kernel.org
Cc: Andre Przywara <andre.przywara@arm.com>,
        Christoffer Dall <christoffer.dall@arm.com>,
        Dave Martin <Dave.Martin@arm.com>,
        Jintack Lim <jintack@cs.columbia.edu>,
        Alexandru Elisei <alexandru.elisei@arm.com>,
        George Cherian <gcherian@marvell.com>,
        "Zengtao (B)" <prime.zeng@hisilicon.com>,
        Andrew Scull <ascull@google.com>,
        Will Deacon <will@kernel.org>,
        Mark Rutland <mark.rutland@arm.com>,
        James Morse <james.morse@arm.com>,
        Julien Thierry <julien.thierry.kdev@gmail.com>,
        Suzuki K Poulose <suzuki.poulose@arm.com>,
        kernel-team@android.com
Subject: [PATCH v3 00/17] KVM: arm64: Preliminary NV patches
Date: Mon,  6 Jul 2020 13:54:08 +0100
Message-Id: <20200706125425.1671020-1-maz@kernel.org>
X-Mailer: git-send-email 2.27.0
MIME-Version: 1.0
X-SA-Exim-Connect-IP: 62.31.163.78
X-SA-Exim-Rcpt-To: catalin.marinas@arm.com,
 linux-arm-kernel@lists.infradead.org, kvmarm@lists.cs.columbia.edu,
 kvm@vger.kernel.org, andre.przywara@arm.com, christoffer.dall@arm.com,
 Dave.Martin@arm.com, jintack@cs.columbia.edu, alexandru.elisei@arm.com,
 gcherian@marvell.com, prime.zeng@hisilicon.com, ascull@google.com,
 will@kernel.org, mark.rutland@arm.com, james.morse@arm.com,
 julien.thierry.kdev@gmail.com, suzuki.poulose@arm.com,
 kernel-team@android.com
X-SA-Exim-Mail-From: maz@kernel.org
X-SA-Exim-Scanned: No (on disco-boy.misterjones.org);
 SAEximRunCond expanded to false
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Hi all,

In order not to repeat the 90+ patch series that resulted in a
deafening silence last time, I've extracted a smaller set of patches
that form the required dependencies that allow the rest of the 65 NV
patches to be added on top. Yes, it is that bad.

The one real feature here is support for the ARMv8.4-TTL extension at
Stage-2 only. The reason to support it is that it helps the hypervisor
a lot when it comes to finding out how much to invalidate. It is thus
always "supported" with NV.

The rest doesn't contain any functionality change. Most of it reworks
existing data structures and adds new accessors for the things that
get moved around. The reason for this is that:

- With NV, we end-up with multiple Stage-2 MMU contexts per VM instead
  of a single one. This requires we divorce struct kvm from the S2 MMU
  configuration. Of course, we stick with a single MMU context for now.

- With ARMv8.4-NV, a number of system register accesses are turned
  into memory accesses into the so-called VNCR page. It is thus
  convenient to make this VNCR page part of the vcpu context and avoid
  copying data back and forth. For this to work, we need to make sure
  that all the VNCR-aware sysregs are moved into our per-vcpu sys_regs
  array instead of leaving in other data structures (the timers, for
  example). The VNCR page itself isn't introduced with these patches.

- As some of these data structures change, we need a way to isolate
  the userspace ABI from such change.

There is also a number of cleanups that were in the full fat series
that I decided to move early to get them out of the way.

The whole this is a bit of a mix of vaguely unrelated "stuff", but it
all comes together if you look at the final series. This applies on
top of David Brazdil's series splitting the VHE and nVHE objects.

I plan on taking this early into v5.9, and I really mean it this time!

Catalin: How do you want to proceed for patches 2, 3, and 4? I could
make a stable branch that gets you pull into the arm64 tree, or the
other way around. Just let me know.

Thanks,

	M.

* From v2:
  - Rebased on top of David's el2-obj series
  - Fixed the terrible __kvm_tlb_flush_local_vmid bug
  - Renamed TLBI_TTL_PS_* to TLBI_TTL_TG_* (Alex)
  - Fixed a misleading comment in mmu.c (Alex)
  - Fixed the debug patch commit log
  - Collected Alex's RBs, with thanks.

* From v1:
  - A bunch of patches have been merged. These are the current leftovers.
  - Rebased on top of v5.8-rc1, and it wasn't fun.

Christoffer Dall (1):
  KVM: arm64: Factor out stage 2 page table data from struct kvm

Marc Zyngier (16):
  arm64: Detect the ARMv8.4 TTL feature
  arm64: Document SW reserved PTE/PMD bits in Stage-2 descriptors
  arm64: Add level-hinted TLB invalidation helper
  KVM: arm64: Use TTL hint in when invalidating stage-2 translations
  KVM: arm64: Introduce accessor for ctxt->sys_reg
  KVM: arm64: hyp: Use ctxt_sys_reg/__vcpu_sys_reg instead of raw
    sys_regs access
  KVM: arm64: sve: Use __vcpu_sys_reg() instead of raw sys_regs access
  KVM: arm64: pauth: Use ctxt_sys_reg() instead of raw sys_regs access
  KVM: arm64: debug: Drop useless vpcu parameter
  KVM: arm64: Make struct kvm_regs userspace-only
  KVM: arm64: Move ELR_EL1 to the system register array
  KVM: arm64: Move SP_EL1 to the system register array
  KVM: arm64: Disintegrate SPSR array
  KVM: arm64: Move SPSR_EL1 to the system register array
  KVM: arm64: timers: Rename kvm_timer_sync_hwstate to
    kvm_timer_sync_user
  KVM: arm64: timers: Move timer registers to the sys_regs file

 arch/arm64/include/asm/cpucaps.h           |   3 +-
 arch/arm64/include/asm/kvm_asm.h           |   8 +-
 arch/arm64/include/asm/kvm_emulate.h       |  37 +--
 arch/arm64/include/asm/kvm_host.h          |  71 ++++--
 arch/arm64/include/asm/kvm_mmu.h           |  16 +-
 arch/arm64/include/asm/pgtable-hwdef.h     |   2 +
 arch/arm64/include/asm/stage2_pgtable.h    |   9 +
 arch/arm64/include/asm/sysreg.h            |   1 +
 arch/arm64/include/asm/tlbflush.h          |  45 ++++
 arch/arm64/kernel/asm-offsets.c            |   3 +-
 arch/arm64/kernel/cpufeature.c             |  11 +
 arch/arm64/kvm/arch_timer.c                | 157 +++++++++---
 arch/arm64/kvm/arm.c                       |  40 +--
 arch/arm64/kvm/fpsimd.c                    |   6 +-
 arch/arm64/kvm/guest.c                     |  79 +++++-
 arch/arm64/kvm/hyp/entry.S                 |   3 +-
 arch/arm64/kvm/hyp/include/hyp/debug-sr.h  |  22 +-
 arch/arm64/kvm/hyp/include/hyp/switch.h    |  38 +--
 arch/arm64/kvm/hyp/include/hyp/sysreg-sr.h | 152 ++++++-----
 arch/arm64/kvm/hyp/nvhe/switch.c           |   6 +-
 arch/arm64/kvm/hyp/nvhe/tlb.c              |  36 +--
 arch/arm64/kvm/hyp/vhe/switch.c            |   2 +-
 arch/arm64/kvm/hyp/vhe/tlb.c               |  29 ++-
 arch/arm64/kvm/inject_fault.c              |   2 +-
 arch/arm64/kvm/mmu.c                       | 281 ++++++++++++---------
 arch/arm64/kvm/regmap.c                    |  37 ++-
 arch/arm64/kvm/reset.c                     |   2 +-
 arch/arm64/kvm/sys_regs.c                  |   2 +
 arch/arm64/kvm/trace_arm.h                 |   8 +-
 include/kvm/arm_arch_timer.h               |  13 +-
 30 files changed, 696 insertions(+), 425 deletions(-)
```
#### [PATCH v3 0/9] vfio/fsl-mc: VFIO support for FSL-MC devices
##### From: Diana Craciun <diana.craciun@oss.nxp.com>

```c
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

DPAA2 (Data Path Acceleration Architecture) consists in
mechanisms for processing Ethernet packets, queue management,
accelerators, etc.

The Management Complex (mc) is a hardware entity that manages the DPAA2
hardware resources. It provides an object-based abstraction for software
drivers to use the DPAA2 hardware. The MC mediates operations such as
create, discover, destroy of DPAA2 objects.
The MC provides memory-mapped I/O command interfaces (MC portals) which
DPAA2 software drivers use to operate on DPAA2 objects.

A DPRC is a container object that holds other types of DPAA2 objects.
Each object in the DPRC is a Linux device and bound to a driver.
The MC-bus driver is a platform driver (different from PCI or platform
bus). The DPRC driver does runtime management of a bus instance. It
performs the initial scan of the DPRC and handles changes in the DPRC
configuration (adding/removing objects).

All objects inside a container share the same hardware isolation
context, meaning that only an entire DPRC can be assigned to
a virtual machine.
When a container is assigned to a virtual machine, all the objects
within that container are assigned to that virtual machine.
The DPRC container assigned to the virtual machine is not allowed
to change contents (add/remove objects) by the guest. The restriction
is set by the host and enforced by the mc hardware.

The DPAA2 objects can be directly assigned to the guest. However
the MC portals (the memory mapped command interface to the MC) need
to be emulated because there are commands that configure the
interrupts and the isolation IDs which are virtual in the guest.

Example:
echo vfio-fsl-mc > /sys/bus/fsl-mc/devices/dprc.2/driver_override
echo dprc.2 > /sys/bus/fsl-mc/drivers/vfio-fsl-mc/bind

The dprc.2 is bound to the VFIO driver and all the objects within
dprc.2 are going to be bound to the VFIO driver.

More details about the DPAA2 objects can be found here:
Documentation/networking/device_drivers/freescale/dpaa2/overview.rst

The patches are dependent on some changes in the mc-bus (bus/fsl-mc)
driver. The changes were needed in order to re-use code and to export
some more functions that are needed by the VFIO driver.
Currenlty the mc-bus patches are under review:
https://www.spinics.net/lists/kernel/msg3578910.html

v2 --> v3
- There is no need to align region size to page size
- read/write implemented for all DPAA2 objects
- review fixes

v1 --> v2
- Fixed the container reset, a new flag added to the firmware command
- Implement a bus notifier for setting driver_override

Bharat Bhushan (1):
  vfio/fsl-mc: Add VFIO framework skeleton for fsl-mc devices

Diana Craciun (8):
  vfio/fsl-mc: Scan DPRC objects on vfio-fsl-mc driver bind
  vfio/fsl-mc: Implement VFIO_DEVICE_GET_INFO ioctl
  vfio/fsl-mc: Implement VFIO_DEVICE_GET_REGION_INFO ioctl call
  vfio/fsl-mc: Allow userspace to MMAP fsl-mc device MMIO regions
  vfio/fsl-mc: Added lock support in preparation for interrupt handling
  vfio/fsl-mc: Add irq infrastructure for fsl-mc devices
  vfio/fsl-mc: trigger an interrupt via eventfd
  vfio/fsl-mc: Add read/write support for fsl-mc devices

 MAINTAINERS                               |   6 +
 drivers/vfio/Kconfig                      |   1 +
 drivers/vfio/Makefile                     |   1 +
 drivers/vfio/fsl-mc/Kconfig               |   9 +
 drivers/vfio/fsl-mc/Makefile              |   4 +
 drivers/vfio/fsl-mc/vfio_fsl_mc.c         | 687 ++++++++++++++++++++++
 drivers/vfio/fsl-mc/vfio_fsl_mc_intr.c    | 221 +++++++
 drivers/vfio/fsl-mc/vfio_fsl_mc_private.h |  55 ++
 include/uapi/linux/vfio.h                 |   1 +
 9 files changed, 985 insertions(+)
 create mode 100644 drivers/vfio/fsl-mc/Kconfig
 create mode 100644 drivers/vfio/fsl-mc/Makefile
 create mode 100644 drivers/vfio/fsl-mc/vfio_fsl_mc.c
 create mode 100644 drivers/vfio/fsl-mc/vfio_fsl_mc_intr.c
 create mode 100644 drivers/vfio/fsl-mc/vfio_fsl_mc_private.h
```
#### [kvm-unit-tests PATCH v2 0/4] More lib/alloc cleanup and a minor
##### From: Claudio Imbrenda <imbrenda@linux.ibm.com>

```c
From patchwork Mon Jul  6 16:43:20 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Claudio Imbrenda <imbrenda@linux.ibm.com>
X-Patchwork-Id: 11646127
Return-Path: <SRS0=fXy1=AR=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 76C5213B4
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon,  6 Jul 2020 16:43:34 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 6745C206CD
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon,  6 Jul 2020 16:43:34 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729658AbgGFQnd (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 6 Jul 2020 12:43:33 -0400
Received: from mx0a-001b2d01.pphosted.com ([148.163.156.1]:27236 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1729386AbgGFQna (ORCPT
        <rfc822;kvm@vger.kernel.org>); Mon, 6 Jul 2020 12:43:30 -0400
Received: from pps.filterd (m0098409.ppops.net [127.0.0.1])
        by mx0a-001b2d01.pphosted.com (8.16.0.42/8.16.0.42) with SMTP id
 066GY9BB150928
        for <kvm@vger.kernel.org>; Mon, 6 Jul 2020 12:43:30 -0400
Received: from pps.reinject (localhost [127.0.0.1])
        by mx0a-001b2d01.pphosted.com with ESMTP id 322n2rjr86-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT)
        for <kvm@vger.kernel.org>; Mon, 06 Jul 2020 12:43:30 -0400
Received: from m0098409.ppops.net (m0098409.ppops.net [127.0.0.1])
        by pps.reinject (8.16.0.36/8.16.0.36) with SMTP id 066GYO0B152299
        for <kvm@vger.kernel.org>; Mon, 6 Jul 2020 12:43:30 -0400
Received: from ppma05fra.de.ibm.com (6c.4a.5195.ip4.static.sl-reverse.com
 [149.81.74.108])
        by mx0a-001b2d01.pphosted.com with ESMTP id 322n2rjr72-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Mon, 06 Jul 2020 12:43:29 -0400
Received: from pps.filterd (ppma05fra.de.ibm.com [127.0.0.1])
        by ppma05fra.de.ibm.com (8.16.0.42/8.16.0.42) with SMTP id
 066GQEDM009876;
        Mon, 6 Jul 2020 16:43:27 GMT
Received: from b06cxnps4076.portsmouth.uk.ibm.com
 (d06relay13.portsmouth.uk.ibm.com [9.149.109.198])
        by ppma05fra.de.ibm.com with ESMTP id 322hd8191y-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Mon, 06 Jul 2020 16:43:27 +0000
Received: from d06av25.portsmouth.uk.ibm.com (d06av25.portsmouth.uk.ibm.com
 [9.149.105.61])
        by b06cxnps4076.portsmouth.uk.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id 066GhP8W45154366
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Mon, 6 Jul 2020 16:43:25 GMT
Received: from d06av25.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id ECA5611C05B;
        Mon,  6 Jul 2020 16:43:24 +0000 (GMT)
Received: from d06av25.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 7DA3A11C054;
        Mon,  6 Jul 2020 16:43:24 +0000 (GMT)
Received: from ibm-vm.ibmuc.com (unknown [9.145.9.164])
        by d06av25.portsmouth.uk.ibm.com (Postfix) with ESMTP;
        Mon,  6 Jul 2020 16:43:24 +0000 (GMT)
From: Claudio Imbrenda <imbrenda@linux.ibm.com>
To: kvm@vger.kernel.org, pbonzini@redhat.com
Cc: frankja@linux.ibm.com, thuth@redhat.com, david@redhat.com,
        drjones@redhat.com
Subject: [kvm-unit-tests PATCH v2 0/4] More lib/alloc cleanup and a minor
 improvement
Date: Mon,  6 Jul 2020 18:43:20 +0200
Message-Id: <20200706164324.81123-1-imbrenda@linux.ibm.com>
X-Mailer: git-send-email 2.26.2
MIME-Version: 1.0
X-TM-AS-GCONF: 00
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.235,18.0.687
 definitions=2020-07-06_15:2020-07-06,2020-07-06 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 mlxscore=0 spamscore=0
 clxscore=1015 adultscore=0 phishscore=0 priorityscore=1501
 cotscore=-2147483648 impostorscore=0 bulkscore=0 suspectscore=0
 lowpriorityscore=0 mlxlogscore=975 malwarescore=0 classifier=spam adjust=0
 reason=mlx scancount=1 engine=8.12.0-2004280000
 definitions=main-2007060120
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Some more cleanup of lib/alloc in light of upcoming changes

The first real feature: allow aligned virtual allocations with
alignment greater than one page.

Also export a function for allocating aligned non-backed virtual pages.

v1->v2
* rename helper function to alloc_vpages_aligned, call it directly
* alloc_vpages_aligned now expects a page order as alignment

Claudio Imbrenda (4):
  lib/vmalloc: fix pages count local variable to be size_t
  lib/alloc_page: change some parameter types
  lib/alloc_page: move get_order and is_power_of_2 to a bitops.h
  lib/vmalloc: allow vm_memalign with alignment > PAGE_SIZE

 lib/alloc_page.h |  7 +++----
 lib/bitops.h     | 10 ++++++++++
 lib/libcflat.h   |  5 -----
 lib/vmalloc.h    |  3 +++
 lib/alloc.c      |  1 +
 lib/alloc_page.c | 13 ++++---------
 lib/vmalloc.c    | 37 ++++++++++++++++++++++++++++---------
 7 files changed, 49 insertions(+), 27 deletions(-)
```
