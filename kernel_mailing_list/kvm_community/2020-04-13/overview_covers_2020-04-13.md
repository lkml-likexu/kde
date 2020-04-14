

#### [PATCH v5 0/4] introduction of migration_version attribute for VFIO
##### From: Yan Zhao <yan.y.zhao@intel.com>

```c
From patchwork Mon Apr 13 05:52:01 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Yan Zhao <yan.y.zhao@intel.com>
X-Patchwork-Id: 11485047
Return-Path: <SRS0=d7i1=55=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 7C8A0913
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 13 Apr 2020 06:02:22 +0000 (UTC)
Received: from vger.kernel.org (unknown [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 544F920731
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 13 Apr 2020 06:02:22 +0000 (UTC)
DMARC-Filter: OpenDMARC Filter v1.3.2 mail.kernel.org 544F920731
Authentication-Results: mail.kernel.org;
 dmarc=fail (p=none dis=none) header.from=intel.com
Authentication-Results: mail.kernel.org;
 spf=none smtp.mailfrom=kvm-owner@vger.kernel.org
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727009AbgDMGCB (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 13 Apr 2020 02:02:01 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.18]:46164 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726967AbgDMGCA (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 13 Apr 2020 02:02:00 -0400
Received: from mga18.intel.com (mga18.intel.com [134.134.136.126])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 34661C0A3BE0;
        Sun, 12 Apr 2020 23:02:00 -0700 (PDT)
IronPort-SDR: 
 J+h/MBje8AxqNUX6hmRuU4GVAaqWr2uoKhQKt/uhcPmiklveoPpVrJyaVGOpVr+nKwH9OXIx2f
 HYUziwvH9OIQ==
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from fmsmga005.fm.intel.com ([10.253.24.32])
  by orsmga106.jf.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 12 Apr 2020 23:01:59 -0700
IronPort-SDR: 
 O5wdGuyQlc7bo5KmVytTBytv4gIaY33RmF0q8WDMiPNVI4GCYyrC5X6Yd4Ae+HQAXSFb7BKflg
 896Qwv3gpldQ==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.72,377,1580803200";
   d="scan'208";a="453054045"
Received: from joy-optiplex-7040.sh.intel.com ([10.239.13.16])
  by fmsmga005.fm.intel.com with ESMTP; 12 Apr 2020 23:01:52 -0700
From: Yan Zhao <yan.y.zhao@intel.com>
To: intel-gvt-dev@lists.freedesktop.org
Cc: libvir-list@redhat.com, kvm@vger.kernel.org,
        linux-doc@vger.kernel.org, linux-kernel@vger.kernel.org,
        aik@ozlabs.ru, Zhengxiao.zx@alibaba-inc.com,
        shuangtai.tst@alibaba-inc.com, qemu-devel@nongnu.org,
        eauger@redhat.com, yi.l.liu@intel.com, xin.zeng@intel.com,
        ziye.yang@intel.com, mlevitsk@redhat.com, pasic@linux.ibm.com,
        felipe@nutanix.com, changpeng.liu@intel.com, Ken.Xue@amd.com,
        jonathan.davies@nutanix.com, shaopeng.he@intel.com,
        alex.williamson@redhat.com, eskultet@redhat.com,
        dgilbert@redhat.com, cohuck@redhat.com, kevin.tian@intel.com,
        zhenyuw@linux.intel.com, zhi.a.wang@intel.com, cjia@nvidia.com,
        kwankhede@nvidia.com, berrange@redhat.com, dinechin@redhat.com,
        corbet@lwn.net, Yan Zhao <yan.y.zhao@intel.com>
Subject: [PATCH v5 0/4] introduction of migration_version attribute for VFIO
 live migration
Date: Mon, 13 Apr 2020 01:52:01 -0400
Message-Id: <20200413055201.27053-1-yan.y.zhao@intel.com>
X-Mailer: git-send-email 2.17.1
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This patchset introduces a migration_version attribute under sysfs of VFIO
Mediated devices.

This migration_version attribute is used to check migration compatibility
between two mdev devices.

Currently, it has two locations:
(1) under mdev_type node,
    which can be used even before device creation, but only for mdev
    devices of the same mdev type.
(2) under mdev device node,
    which can only be used after the mdev devices are created, but the src
    and target mdev devices are not necessarily be of the same mdev type
(The second location is newly added in v5, in order to keep consistent
with the migration_version node for migratable pass-though devices)

Patch 1 defines migration_version attribute for the first location in
Documentation/vfio-mediated-device.txt

Patch 2 uses GVT as an example for patch 1 to show how to expose
migration_version attribute and check migration compatibility in vendor
driver.

Patch 3 defines migration_version attribute for the second location in
Documentation/vfio-mediated-device.txt

Patch 4 uses GVT as an example for patch 3 to show how to expose
migration_version attribute and check migration compatibility in vendor
driver.

(The previous "Reviewed-by" and "Acked-by" for patch 1 and patch 2 are
kept in v5, as there are only small changes to commit messages of the two
patches.)

v5:
added patch 2 and 4 for mdev device part of migration_version attribute.

v4:
1. fixed indentation/spell errors, reworded several error messages
2. added a missing memory free for error handling in patch 2

v3:
1. renamed version to migration_version
2. let errno to be freely defined by vendor driver
3. let checking mdev_type be prerequisite of migration compatibility check
4. reworded most part of patch 1
5. print detailed error log in patch 2 and generate migration_version
string at init time

v2:
1. renamed patched 1
2. made definition of device version string completely private to vendor
driver
3. reverted changes to sample mdev drivers
4. described intent and usage of version attribute more clearly.


Yan Zhao (4):
  vfio/mdev: add migration_version attribute for mdev (under mdev_type
    node)
  drm/i915/gvt: export migration_version to mdev sysfs (under mdev_type
    node)
  vfio/mdev: add migration_version attribute for mdev (under mdev device
    node)
  drm/i915/gvt: export migration_version to mdev sysfs (under mdev
    device node)

 .../driver-api/vfio-mediated-device.rst       | 183 ++++++++++++++++++
 drivers/gpu/drm/i915/gvt/Makefile             |   2 +-
 drivers/gpu/drm/i915/gvt/gvt.c                |  39 ++++
 drivers/gpu/drm/i915/gvt/gvt.h                |   7 +
 drivers/gpu/drm/i915/gvt/kvmgt.c              |  55 ++++++
 drivers/gpu/drm/i915/gvt/migration_version.c  | 170 ++++++++++++++++
 drivers/gpu/drm/i915/gvt/vgpu.c               |  13 +-
 7 files changed, 466 insertions(+), 3 deletions(-)
 create mode 100644 drivers/gpu/drm/i915/gvt/migration_version.c
```
#### [PATCH 0/15] KVM: MIPS: Add Loongson-3 support (Host Side)
##### From: Huacai Chen <chenhc@lemote.com>

```c
From patchwork Mon Apr 13 07:30:09 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Huacai Chen <chenhc@lemote.com>
X-Patchwork-Id: 11485137
Return-Path: <SRS0=d7i1=55=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 09726912
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 13 Apr 2020 07:21:54 +0000 (UTC)
Received: from vger.kernel.org (unknown [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id CFFEF2076B
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 13 Apr 2020 07:21:53 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=fail reason="signature verification failed" (2048-bit key)
 header.d=gmail.com header.i=@gmail.com header.b="k6qWBGXU"
DMARC-Filter: OpenDMARC Filter v1.3.2 mail.kernel.org CFFEF2076B
Authentication-Results: mail.kernel.org;
 dmarc=none (p=none dis=none) header.from=lemote.com
Authentication-Results: mail.kernel.org;
 spf=none smtp.mailfrom=kvm-owner@vger.kernel.org
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729198AbgDMHVw (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 13 Apr 2020 03:21:52 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.18]:59370 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1727654AbgDMHVw (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 13 Apr 2020 03:21:52 -0400
Received: from mail-pf1-x443.google.com (mail-pf1-x443.google.com
 [IPv6:2607:f8b0:4864:20::443])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 51518C008651;
        Mon, 13 Apr 2020 00:21:51 -0700 (PDT)
Received: by mail-pf1-x443.google.com with SMTP id v23so4168394pfm.1;
        Mon, 13 Apr 2020 00:21:51 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=sender:from:to:cc:subject:date:message-id;
        bh=t2sALsyCMMNQl+/8FmLCPuHasRrqoSojD5dypqshy1s=;
        b=k6qWBGXUMQGdG4L801yUD0CBa9KUZWJQCLwsgGPYl/I2VJjZ4q+nrmBR9MLWNt1Gjd
         1TiOACf0dKTBjQqemktNCtQ0HdOLjV0nbkeTWg7IDclXU8YvNE2UQazw14m6AGOUROyR
         RpXuV5GJz3e6PeImUS0fjZ5XTORTAzUqKUUAsvFY6JYby8LTKcdlASVGp91STYo1v8ct
         YLGaHQfy0JJx1n35AIKm3McnOH5Tyb2Q4r+qP+Vu5utdX2QOwPy1qOjZtqEVCIqkZUja
         Z8/b8qu/BwnvUeNTxUGrhOtbhZHcLPPKvPWgaaIFfLtZdxpQyA272eP4fSG4dK9cx04y
         DE8w==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:sender:from:to:cc:subject:date:message-id;
        bh=t2sALsyCMMNQl+/8FmLCPuHasRrqoSojD5dypqshy1s=;
        b=BooxOsO3Q3cTl3W+sp55V96DH5yYwno1X2oK/R0ndBAY28aCqC45UqgyLoPmjzxRQp
         vEixBnFzzAEL2X/ZuOxBjqzRCVIBDkHDm+SWXgLdMYIztu2wYXR5sTf93wGj+XPOleb9
         GA8C/smHuQoddJyohJdDKd1YV9K7vNYyXkcI0n3PGT6sdqBC5KrUFWo9s4aUFslOippW
         VoeuoSXHlFpGUkT7knej8yS0aoBNvSwd2IvwAuRnssVM9pV8crefq2nVy2NxtzsWOP7e
         /XiDVg3a/S0rqRhfpL6DWnGPF85tQHNFAJIt6gsY+mhU6PNqCRYOz59u+2DQPgWONCuZ
         yuGg==
X-Gm-Message-State: AGi0PuZmO7gJVVzblMWy+m5i1sRsZvUcD6bNvFMomabizsqYhjuxL9af
        eBQH9NYjLa2rbjEfvnLoozhTGUKVtDc=
X-Google-Smtp-Source: 
 APiQypLOMSAvZAOVmdTh3/xVhGIylyDIoCT43TP1W6oweKMcx07p6DU4u4BAs3R3Egz33M4rokbdUQ==
X-Received: by 2002:a63:c20:: with SMTP id b32mr164314pgl.75.1586762510767;
        Mon, 13 Apr 2020 00:21:50 -0700 (PDT)
Received: from software.domain.org (28.144.92.34.bc.googleusercontent.com.
 [34.92.144.28])
        by smtp.gmail.com with ESMTPSA id
 u8sm7241341pgl.19.2020.04.13.00.21.48
        (version=TLS1_2 cipher=ECDHE-ECDSA-AES128-GCM-SHA256 bits=128/128);
        Mon, 13 Apr 2020 00:21:50 -0700 (PDT)
From: Huacai Chen <chenhc@lemote.com>
To: Paolo Bonzini <pbonzini@redhat.com>,
        Thomas Bogendoerfer <tsbogend@alpha.franken.de>
Cc: kvm@vger.kernel.org, qemu-devel@nongnu.org,
        linux-mips@vger.kernel.org, Fuxin Zhang <zhangfx@lemote.com>,
        Huacai Chen <chenhuacai@gmail.com>,
        Jiaxun Yang <jiaxun.yang@flygoat.com>,
        Huacai Chen <chenhc@lemote.com>
Subject: [PATCH 0/15] KVM: MIPS: Add Loongson-3 support (Host Side)
Date: Mon, 13 Apr 2020 15:30:09 +0800
Message-Id: <1586763024-12197-1-git-send-email-chenhc@lemote.com>
X-Mailer: git-send-email 2.7.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

We are preparing to add KVM support for Loongson-3. VZ extension is
fully supported in Loongson-3A R4+, and we will not care about old CPUs
(at least now). We already have a full functional Linux kernel (based
on Linux-5.4.x LTS) and QEMU (based on 5.0.0-rc2) and their git
repositories are here:

QEMU: https://github.com/chenhuacai/qemu
Kernel: https://github.com/chenhuacai/linux

Of course these two repositories need to be rework and not suitable for
upstream (especially the commits need to be splitted). We show them here
is just to tell others what we have done, and how KVM/Loongson will look
like.

Our plan is make the KVM host side be upstream first, and after that,
we will make the KVM guest side and QEMU emulator be upstream.

Mike Rapoport(1):
 mips: define pud_index() regardless of page table folding

Xing Li(2):
 KVM: MIPS: Define KVM_ENTRYHI_ASID to cpu_asid_mask(&boot_cpu_data)
 KVM: MIPS: Fix VPN2_MASK definition for variable cpu_vmbits

Huacai Chen(12):
 KVM: MIPS: Increase KVM_MAX_VCPUS and KVM_USER_MEM_SLOTS to 16
 KVM: MIPS: Add EVENTFD support which is needed by VHOST
 KVM: MIPS: Use lddir/ldpte instructions to lookup gpa_mm.pgd
 KVM: MIPS: Introduce and use cpu_guest_has_ldpte
 KVM: MIPS: Use root tlb to control guest's CCA for Loongson-3
 KVM: MIPS: Let indexed cacheops cause guest exit on Loongson-3
 KVM: MIPS: Add more types of virtual interrupts
 KVM: MIPS: Add Loongson-3 Virtual IPI interrupt support
 KVM: MIPS: Add CPUCFG emulation for Loongson-3
 KVM: MIPS: Add CONFIG6 and DIAG registers emulation
 KVM: MIPS: Add more MMIO load/store instructions emulation
 KVM: MIPS: Enable KVM support for Loongson-3

Signed-off-by: Huacai Chen <chenhc@lemote.com>
---
 arch/mips/Kconfig                    |   1 +
 arch/mips/include/asm/cpu-features.h |   3 +
 arch/mips/include/asm/kvm_host.h     |  50 +++-
 arch/mips/include/asm/mipsregs.h     |   7 +
 arch/mips/include/asm/pgtable-64.h   |   4 +-
 arch/mips/include/uapi/asm/inst.h    |  11 +
 arch/mips/kernel/cpu-probe.c         |   2 +
 arch/mips/kvm/Kconfig                |   1 +
 arch/mips/kvm/Makefile               |   5 +-
 arch/mips/kvm/emulate.c              | 461 ++++++++++++++++++++++++++++++++++-
 arch/mips/kvm/entry.c                |  19 +-
 arch/mips/kvm/interrupt.c            |  93 +------
 arch/mips/kvm/interrupt.h            |  14 +-
 arch/mips/kvm/loongson_ipi.c         | 215 ++++++++++++++++
 arch/mips/kvm/mips.c                 |  49 +++-
 arch/mips/kvm/tlb.c                  |  39 +++
 arch/mips/kvm/trap_emul.c            |   3 +
 arch/mips/kvm/vz.c                   | 204 +++++++++++-----
 18 files changed, 1013 insertions(+), 168 deletions(-)
 create mode 100644 arch/mips/kvm/loongson_ipi.c
--
2.7.0
```
