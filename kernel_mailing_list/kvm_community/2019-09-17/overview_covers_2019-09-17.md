

#### [RFC v4 0/3] vhost: introduce mdev based hardware backend
##### From: Tiwei Bie <tiwei.bie@intel.com>

```c
From patchwork Tue Sep 17 01:02:01 2019
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Tiwei Bie <tiwei.bie@intel.com>
X-Patchwork-Id: 11147971
Return-Path: <SRS0=dK0e=XM=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id A851013BD
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 17 Sep 2019 01:05:17 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 86E12216C8
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 17 Sep 2019 01:05:17 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1733257AbfIQBE7 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 16 Sep 2019 21:04:59 -0400
Received: from mga04.intel.com ([192.55.52.120]:34819 "EHLO mga04.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1727996AbfIQBE7 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 16 Sep 2019 21:04:59 -0400
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from orsmga008.jf.intel.com ([10.7.209.65])
  by fmsmga104.fm.intel.com with ESMTP/TLS/DHE-RSA-AES256-GCM-SHA384;
 16 Sep 2019 18:04:58 -0700
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.64,514,1559545200";
   d="scan'208";a="180611926"
Received: from dpdk-virtio-tbie-2.sh.intel.com ([10.67.104.71])
  by orsmga008.jf.intel.com with ESMTP; 16 Sep 2019 18:04:55 -0700
From: Tiwei Bie <tiwei.bie@intel.com>
To: mst@redhat.com, jasowang@redhat.com, alex.williamson@redhat.com,
        maxime.coquelin@redhat.com
Cc: linux-kernel@vger.kernel.org, kvm@vger.kernel.org,
        virtualization@lists.linux-foundation.org, netdev@vger.kernel.org,
        dan.daly@intel.com, cunming.liang@intel.com,
        zhihong.wang@intel.com, lingshan.zhu@intel.com, tiwei.bie@intel.com
Subject: [RFC v4 0/3] vhost: introduce mdev based hardware backend
Date: Tue, 17 Sep 2019 09:02:01 +0800
Message-Id: <20190917010204.30376-1-tiwei.bie@intel.com>
X-Mailer: git-send-email 2.17.1
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This RFC is to demonstrate below ideas,

a) Build vhost-mdev on top of the same abstraction defined in
   the virtio-mdev series [1];

b) Introduce /dev/vhost-mdev to do vhost ioctls and support
   setting mdev device as backend;

Now the userspace API looks like this:

- Userspace generates a compatible mdev device;

- Userspace opens this mdev device with VFIO API (including
  doing IOMMU programming for this mdev device with VFIO's
  container/group based interface);

- Userspace opens /dev/vhost-mdev and gets vhost fd;

- Userspace uses vhost ioctls to setup vhost (userspace should
  do VHOST_MDEV_SET_BACKEND ioctl with VFIO group fd and device
  fd first before doing other vhost ioctls);

Only compile test has been done for this series for now.

RFCv3: https://patchwork.kernel.org/patch/11117785/

[1] https://lkml.org/lkml/2019/9/10/135

Tiwei Bie (3):
  vfio: support getting vfio device from device fd
  vfio: support checking vfio driver by device ops
  vhost: introduce mdev based hardware backend

 drivers/vfio/mdev/vfio_mdev.c    |   3 +-
 drivers/vfio/vfio.c              |  32 +++
 drivers/vhost/Kconfig            |   9 +
 drivers/vhost/Makefile           |   3 +
 drivers/vhost/mdev.c             | 462 +++++++++++++++++++++++++++++++
 drivers/vhost/vhost.c            |  39 ++-
 drivers/vhost/vhost.h            |   6 +
 include/linux/vfio.h             |  11 +
 include/uapi/linux/vhost.h       |  10 +
 include/uapi/linux/vhost_types.h |   5 +
 10 files changed, 573 insertions(+), 7 deletions(-)
 create mode 100644 drivers/vhost/mdev.c
```
#### [PATCH v5 0/9] Enable Sub-page Write Protection Support
##### From: Yang Weijiang <weijiang.yang@intel.com>

```c
From patchwork Tue Sep 17 08:52:55 2019
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Yang Weijiang <weijiang.yang@intel.com>
X-Patchwork-Id: 11148287
Return-Path: <SRS0=dK0e=XM=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 6FB9C912
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 17 Sep 2019 08:53:22 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 57C5D2189D
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 17 Sep 2019 08:53:22 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726178AbfIQIwv (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 17 Sep 2019 04:52:51 -0400
Received: from mga18.intel.com ([134.134.136.126]:37165 "EHLO mga18.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1725811AbfIQIw2 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 17 Sep 2019 04:52:28 -0400
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from fmsmga003.fm.intel.com ([10.253.24.29])
  by orsmga106.jf.intel.com with ESMTP/TLS/DHE-RSA-AES256-GCM-SHA384;
 17 Sep 2019 01:52:27 -0700
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.64,515,1559545200";
   d="scan'208";a="193695456"
Received: from unknown (HELO local-michael-cet-test.sh.intel.com)
 ([10.239.159.128])
  by FMSMGA003.fm.intel.com with ESMTP; 17 Sep 2019 01:52:25 -0700
From: Yang Weijiang <weijiang.yang@intel.com>
To: kvm@vger.kernel.org, linux-kernel@vger.kernel.org,
        pbonzini@redhat.com, sean.j.christopherson@intel.com
Cc: mst@redhat.com, rkrcmar@redhat.com, jmattson@google.com,
        yu.c.zhang@intel.com, alazar@bitdefender.com,
        Yang Weijiang <weijiang.yang@intel.com>
Subject: [PATCH v5 0/9] Enable Sub-page Write Protection Support
Date: Tue, 17 Sep 2019 16:52:55 +0800
Message-Id: <20190917085304.16987-1-weijiang.yang@intel.com>
X-Mailer: git-send-email 2.17.2
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

EPT-Based Sub-Page write Protection(SPP)is a HW capability which allows
Virtual Machine Monitor(VMM) to specify write-permission for guest
physical memory at a sub-page(128 byte) granularity. When this
capability is enabled, the CPU enforces write-access check for sub-pages
within a 4KB page.

The feature is targeted to provide fine-grained memory protection for
usages such as device virtualization, memory check-point and VM
introspection etc.

SPP is active when the "sub-page write protection" (bit 23) is 1 in
Secondary VM-Execution Controls. The feature is backed with a Sub-Page
Permission Table(SPPT), SPPT is referenced via a 64-bit control field
called Sub-Page Permission Table Pointer (SPPTP) which contains a
4K-aligned physical address.

To enable SPP for certain physical page, the gfn should be first mapped
to a 4KB entry, then set bit 61 of the corresponding EPT leaf entry. 
While HW walks EPT, if bit 61 is set, it traverses SPPT with the guset
physical address to find out the sub-page permissions at the leaf entry.
If the corresponding bit is set, write to sub-page is permitted,
otherwise, SPP induced EPT violation is generated.

This patch serial passed SPP function test and selftest on Ice-Lake platform.

Please refer to the SPP introduction document in this patch set and
Intel SDM for details:

Intel SDM:
https://software.intel.com/sites/default/files/managed/39/c5/325462-sdm-vol-1-2abcd-3abcd.pdf

SPP selftest patch:
https://lkml.org/lkml/2019/6/18/1197

Previous patch:
https://lkml.org/lkml/2019/8/14/97

Patch 1: Introduction to SPP.
Patch 2: Add SPP related flags and control bits.
Patch 3: Functions for SPPT setup.
Patch 4: Add SPP access bitmaps for memslots.
Patch 5: Introduce SPP {init,set,get} functions
Patch 6: Implement User space access IOCTLs.
Patch 7: Set up SPP paging table at vm-entry/exit.
Patch 8: Enable lazy mode SPPT setup.
Patch 9: Handle SPP protected pages when VM memory changes


Change logs:

V5 -> V4:
  1. Enable SPP support for Hugepage(1GB/2MB) to extend application.
  2. Make SPP miss vm-exit handler as the unified place to set up SPPT.
  3. If SPP protected pages are access-tracked or dirty-page-tracked,
     store SPP flag in reserved address bit, restore it in
     fast_page_fault() handler.
  4. Move SPP specific functions to vmx/spp.c and vmx/spp.h
  5. Rebased code to kernel v5.3
  6. Other change suggested by KVM community.
  
V3 -> V4:
  1. Modified documentation to make it consistent with patches.
  2. Allocated SPPT root page in init_spp() instead of vmx_set_cr3() to
     avoid SPPT miss error.
  3. Added back co-developers and sign-offs.

V2 -> V3:                                                                
  1. Rebased patches to kernel 5.1 release                                
  2. Deferred SPPT setup to EPT fault handler if the page is not
     available while set_subpage() is being called.
  3. Added init IOCTL to reduce extra cost if SPP is not used.
  4. Refactored patch structure, cleaned up cross referenced functions.
  5. Added code to deal with memory swapping/migration/shrinker cases.

V2 -> V1:
  1. Rebased to 4.20-rc1
  2. Move VMCS change to a separated patch.
  3. Code refine and Bug fix 


Yang Weijiang (9):
  Documentation: Introduce EPT based Subpage Protection
  vmx: spp: Add control flags for Sub-Page Protection(SPP)
  mmu: spp: Add SPP Table setup functions
  mmu: spp: Add functions to create/destroy SPP bitmap block
  mmu: spp: Introduce SPP {init,set,get} functions
  x86: spp: Introduce user-space SPP IOCTLs
  vmx: spp: Set up SPP paging table at vm-entry/exit
  mmu: spp: Enable Lazy mode SPP protection
  mmu: spp: Handle SPP protected pages when VM memory changes

 Documentation/virtual/kvm/spp_kvm.txt | 178 +++++++
 arch/x86/include/asm/cpufeatures.h    |   1 +
 arch/x86/include/asm/kvm_host.h       |  10 +-
 arch/x86/include/asm/vmx.h            |  10 +
 arch/x86/include/uapi/asm/vmx.h       |   2 +
 arch/x86/kernel/cpu/intel.c           |   4 +
 arch/x86/kvm/mmu.c                    |  78 ++-
 arch/x86/kvm/mmu.h                    |   2 +
 arch/x86/kvm/vmx/capabilities.h       |   5 +
 arch/x86/kvm/vmx/spp.c                | 651 ++++++++++++++++++++++++++
 arch/x86/kvm/vmx/spp.h                |  27 ++
 arch/x86/kvm/vmx/vmx.c                |  99 ++++
 arch/x86/kvm/x86.c                    |  51 ++
 include/uapi/linux/kvm.h              |  17 +
 14 files changed, 1133 insertions(+), 2 deletions(-)
 create mode 100644 Documentation/virtual/kvm/spp_kvm.txt
 create mode 100644 arch/x86/kvm/vmx/spp.c
 create mode 100644 arch/x86/kvm/vmx/spp.h
```
