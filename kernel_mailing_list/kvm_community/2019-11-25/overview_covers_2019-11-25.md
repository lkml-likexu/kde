

#### [PATCH 00/19] pin_user_pages(): reduced-risk series for Linux 5.5
##### From: John Hubbard <jhubbard@nvidia.com>

```c
From patchwork Mon Nov 25 04:19:52 2019
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: John Hubbard <jhubbard@nvidia.com>
X-Patchwork-Id: 11259663
Return-Path: <SRS0=umKK=ZR=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id F214A930
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 25 Nov 2019 04:21:36 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id C83DF20835
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 25 Nov 2019 04:21:36 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=nvidia.com header.i=@nvidia.com
 header.b="AWa8smvs"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727573AbfKYEVZ (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Sun, 24 Nov 2019 23:21:25 -0500
Received: from hqemgate16.nvidia.com ([216.228.121.65]:9464 "EHLO
        hqemgate16.nvidia.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1727296AbfKYEUW (ORCPT <rfc822;kvm@vger.kernel.org>);
        Sun, 24 Nov 2019 23:20:22 -0500
Received: from hqpgpgate102.nvidia.com (Not Verified[216.228.121.13]) by
 hqemgate16.nvidia.com (using TLS: TLSv1.2, DES-CBC3-SHA)
        id <B5ddb567f0000>; Sun, 24 Nov 2019 20:20:15 -0800
Received: from hqmail.nvidia.com ([172.20.161.6])
  by hqpgpgate102.nvidia.com (PGP Universal service);
  Sun, 24 Nov 2019 20:20:13 -0800
X-PGP-Universal: processed;
        by hqpgpgate102.nvidia.com on Sun, 24 Nov 2019 20:20:13 -0800
Received: from HQMAIL111.nvidia.com (172.20.187.18) by HQMAIL107.nvidia.com
 (172.20.187.13) with Microsoft SMTP Server (TLS) id 15.0.1473.3; Mon, 25 Nov
 2019 04:20:13 +0000
Received: from hqnvemgw03.nvidia.com (10.124.88.68) by HQMAIL111.nvidia.com
 (172.20.187.18) with Microsoft SMTP Server (TLS) id 15.0.1473.3 via Frontend
 Transport; Mon, 25 Nov 2019 04:20:13 +0000
Received: from blueforge.nvidia.com (Not Verified[10.110.48.28]) by
 hqnvemgw03.nvidia.com with Trustwave SEG (v7,5,8,10121)
        id <B5ddb567c0004>; Sun, 24 Nov 2019 20:20:12 -0800
From: John Hubbard <jhubbard@nvidia.com>
To: Andrew Morton <akpm@linux-foundation.org>
CC: Al Viro <viro@zeniv.linux.org.uk>,
 Alex Williamson <alex.williamson@redhat.com>,
 Benjamin Herrenschmidt <benh@kernel.crashing.org>, =?utf-8?b?QmrDtnJuIFQ=?=
	=?utf-8?b?w7ZwZWw=?= <bjorn.topel@intel.com>,
 Christoph Hellwig <hch@infradead.org>,
 Dan Williams <dan.j.williams@intel.com>, Daniel Vetter <daniel@ffwll.ch>,
 Dave Chinner <david@fromorbit.com>, David Airlie <airlied@linux.ie>,
 "David S . Miller" <davem@davemloft.net>, Ira Weiny <ira.weiny@intel.com>,
 Jan Kara <jack@suse.cz>, Jason Gunthorpe <jgg@ziepe.ca>,
 Jens Axboe <axboe@kernel.dk>, Jonathan Corbet <corbet@lwn.net>,
	=?utf-8?b?SsOpcsO0bWUgR2xpc3Nl?= <jglisse@redhat.com>,
 Magnus Karlsson <magnus.karlsson@intel.com>,
 Mauro Carvalho Chehab <mchehab@kernel.org>,
 Michael Ellerman <mpe@ellerman.id.au>, Michal Hocko <mhocko@suse.com>,
 Mike Kravetz <mike.kravetz@oracle.com>, Paul Mackerras <paulus@samba.org>,
 Shuah Khan <shuah@kernel.org>, Vlastimil Babka <vbabka@suse.cz>,
 <bpf@vger.kernel.org>, <dri-devel@lists.freedesktop.org>,
 <kvm@vger.kernel.org>, <linux-block@vger.kernel.org>,
 <linux-doc@vger.kernel.org>, <linux-fsdevel@vger.kernel.org>,
 <linux-kselftest@vger.kernel.org>, <linux-media@vger.kernel.org>,
 <linux-rdma@vger.kernel.org>, <linuxppc-dev@lists.ozlabs.org>,
 <netdev@vger.kernel.org>, <linux-mm@kvack.org>,
 LKML <linux-kernel@vger.kernel.org>, John Hubbard <jhubbard@nvidia.com>
Subject: [PATCH 00/19] pin_user_pages(): reduced-risk series for Linux 5.5
Date: Sun, 24 Nov 2019 20:19:52 -0800
Message-ID: <20191125042011.3002372-1-jhubbard@nvidia.com>
X-Mailer: git-send-email 2.24.0
MIME-Version: 1.0
X-NVConfidentiality: public
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=nvidia.com; s=n1;
        t=1574655615; bh=Fa0GcWCGWaf6H8ghJjmadoVQ5H4DM60WuhiwHk9NYQE=;
        h=X-PGP-Universal:From:To:CC:Subject:Date:Message-ID:X-Mailer:
         MIME-Version:X-NVConfidentiality:Content-Type:
         Content-Transfer-Encoding;
        b=AWa8smvs+trFNp2hhl6PxcctFNiNkjEPFnL7k3PRf09kncIE/1QuOINHJt/Mcs+cL
         q46mTymRrWH5hIMQjSDcsL6l4MZjGcZ8rEBd95QdLk6OBQpItd8SHAKNmI2s8cgL9A
         TZQx79R+51iPaHlmCxHSrFK4tWN8+/SXha4vPWAk/KUrYtR0z/7ZhQ7IWXBFOwOoWY
         W0JiJYCm5y2Z/s4+iIPAmR7MUQyE8Vno4We33aI2zVWyTzl8693ZWHPydM0PHA73fx
         6y5VYOaw3hqt0dvEDHJk7maQ9GNpqGigBAeOy1HQoT6CNDjnaIYlNwCoCcMA/StzjT
         GubxucVjrnhAA==
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Hi,

Here is a set of well-reviewed (expect for one patch), lower-risk  items
that can go into Linux 5.5. The one patch that wasn't reviewed is the
powerpc conversion, and it's still at this point a no-op, because
tracking isn't yet activated.

This is based on linux-next: b9d3d01405061bb42358fe53f824e894a1922ced
("Add linux-next specific files for 20191122").

This is essentially a cut-down v8 of "mm/gup: track dma-pinned pages:
FOLL_PIN" [1], and with one of the VFIO patches split into two patches.
The idea here is to get this long list of "noise" checked into 5.5, so
that the actual, higher-risk "track FOLL_PIN pages" (which is deferred:
not part of this series) will be a much shorter patchset to review.

For the v4l2-core changes, I've left those here (instead of sending
them separately to the -media tree), in order to get the name change
done now (put_user_page --> unpin_user_page). However, I've added a Cc
stable, as recommended during the last round of reviews.

Here are the relevant notes from the original cover letter, edited to
match the current situation:

This is a prerequisite to tracking dma-pinned pages. That in turn is a
prerequisite to solving the larger problem of proper interactions
between file-backed pages, and [R]DMA activities, as discussed in [1],
[2], [3], and in a remarkable number of email threads since about
2017. :)

A new internal gup flag, FOLL_PIN is introduced, and thoroughly
documented in the last patch's Documentation/vm/pin_user_pages.rst.

I believe that this will provide a good starting point for doing the
layout lease work that Ira Weiny has been working on. That's because
these new wrapper functions provide a clean, constrained, systematically
named set of functionality that, again, is required in order to even
know if a page is "dma-pinned".

In contrast to earlier approaches, the page tracking can be
incrementally applied to the kernel call sites that, until now, have
been simply calling get_user_pages() ("gup"). In other words, opt-in by
changing from this:

    get_user_pages() (sets FOLL_GET)
    put_page()

to this:
    pin_user_pages() (sets FOLL_PIN)
    put_user_page()

Because there are interdependencies with FOLL_LONGTERM, a similar
conversion as for FOLL_PIN, was applied. The change was from this:

    get_user_pages(FOLL_LONGTERM) (also sets FOLL_GET)
    put_page()

to this:
    pin_longterm_pages() (sets FOLL_PIN | FOLL_LONGTERM)
    put_user_page()

[1] https://lore.kernel.org/r/20191121071354.456618-1-jhubbard@nvidia.com

thanks,
John Hubbard
NVIDIA


Dan Williams (1):
  mm: Cleanup __put_devmap_managed_page() vs ->page_free()

John Hubbard (18):
  mm/gup: factor out duplicate code from four routines
  mm/gup: move try_get_compound_head() to top, fix minor issues
  goldish_pipe: rename local pin_user_pages() routine
  mm: fix get_user_pages_remote()'s handling of FOLL_LONGTERM
  vfio: fix FOLL_LONGTERM use, simplify get_user_pages_remote() call
  mm/gup: introduce pin_user_pages*() and FOLL_PIN
  goldish_pipe: convert to pin_user_pages() and put_user_page()
  IB/{core,hw,umem}: set FOLL_PIN via pin_user_pages*(), fix up ODP
  mm/process_vm_access: set FOLL_PIN via pin_user_pages_remote()
  drm/via: set FOLL_PIN via pin_user_pages_fast()
  fs/io_uring: set FOLL_PIN via pin_user_pages()
  net/xdp: set FOLL_PIN via pin_user_pages()
  media/v4l2-core: set pages dirty upon releasing DMA buffers
  media/v4l2-core: pin_user_pages (FOLL_PIN) and put_user_page()
    conversion
  vfio, mm: pin_user_pages (FOLL_PIN) and put_user_page() conversion
  powerpc: book3s64: convert to pin_user_pages() and put_user_page()
  mm/gup_benchmark: use proper FOLL_WRITE flags instead of hard-coding
    "1"
  mm, tree-wide: rename put_user_page*() to unpin_user_page*()

 Documentation/core-api/index.rst            |   1 +
 Documentation/core-api/pin_user_pages.rst   | 233 ++++++++++++++
 arch/powerpc/mm/book3s64/iommu_api.c        |  12 +-
 drivers/gpu/drm/via/via_dmablit.c           |   6 +-
 drivers/infiniband/core/umem.c              |   4 +-
 drivers/infiniband/core/umem_odp.c          |  13 +-
 drivers/infiniband/hw/hfi1/user_pages.c     |   4 +-
 drivers/infiniband/hw/mthca/mthca_memfree.c |   8 +-
 drivers/infiniband/hw/qib/qib_user_pages.c  |   4 +-
 drivers/infiniband/hw/qib/qib_user_sdma.c   |   8 +-
 drivers/infiniband/hw/usnic/usnic_uiom.c    |   4 +-
 drivers/infiniband/sw/siw/siw_mem.c         |   4 +-
 drivers/media/v4l2-core/videobuf-dma-sg.c   |   8 +-
 drivers/nvdimm/pmem.c                       |   6 -
 drivers/platform/goldfish/goldfish_pipe.c   |  35 +--
 drivers/vfio/vfio_iommu_type1.c             |  35 +--
 fs/io_uring.c                               |   6 +-
 include/linux/mm.h                          |  77 +++--
 mm/gup.c                                    | 332 +++++++++++++-------
 mm/gup_benchmark.c                          |   9 +-
 mm/memremap.c                               |  80 ++---
 mm/process_vm_access.c                      |  28 +-
 net/xdp/xdp_umem.c                          |   4 +-
 tools/testing/selftests/vm/gup_benchmark.c  |   6 +-
 24 files changed, 642 insertions(+), 285 deletions(-)
 create mode 100644 Documentation/core-api/pin_user_pages.rst
```
#### [PATCH kvmtool 00/16] Add writable BARs and PCIE 1.1 support
##### From: Alexandru Elisei <alexandru.elisei@arm.com>

```c
From patchwork Mon Nov 25 10:30:17 2019
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Alexandru Elisei <alexandru.elisei@arm.com>
X-Patchwork-Id: 11260105
Return-Path: <SRS0=umKK=ZR=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id E9A66109A
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 25 Nov 2019 10:32:32 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id D33B12082F
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 25 Nov 2019 10:32:32 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727534AbfKYKcb (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 25 Nov 2019 05:32:31 -0500
Received: from foss.arm.com ([217.140.110.172]:47672 "EHLO foss.arm.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1727316AbfKYKca (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 25 Nov 2019 05:32:30 -0500
Received: from usa-sjc-imap-foss1.foss.arm.com (unknown [10.121.207.14])
        by usa-sjc-mx-foss1.foss.arm.com (Postfix) with ESMTP id 036A0328;
        Mon, 25 Nov 2019 02:32:30 -0800 (PST)
Received: from e123195-lin.cambridge.arm.com (e123195-lin.cambridge.arm.com
 [10.1.196.63])
        by usa-sjc-imap-foss1.foss.arm.com (Postfix) with ESMTPA id
 050C83F52E;
        Mon, 25 Nov 2019 02:32:28 -0800 (PST)
From: Alexandru Elisei <alexandru.elisei@arm.com>
To: kvm@vger.kernel.org
Cc: will@kernel.org, julien.thierry.kdev@gmail.com,
        andre.przywara@arm.com, sami.mujawar@arm.com,
        lorenzo.pieralisi@arm.com
Subject: [PATCH kvmtool 00/16] Add writable BARs and PCIE 1.1 support
Date: Mon, 25 Nov 2019 10:30:17 +0000
Message-Id: <20191125103033.22694-1-alexandru.elisei@arm.com>
X-Mailer: git-send-email 2.20.1
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

kvmtool uses the Linux-only dt property 'linux,pci-probe-only' to prevent
it from trying to reprogram the BARs. Let's make the BARs writable so we
can get rid of this band-aid.

Let's also extend the legacy PCI emulation, which came out in 1992, so we
can properly emulate the PCI Express version 1.1 protocol, which is
relatively newer, being published in 2005.

With these two changes, we are very close to running EDK2 as the firmware
for the virtual machine; the only thing that is missing is flash emulation
for storing firmware variables.

Summary of the patches:
* Patches 1-12 are fixes or enhancements needed to support reprogramable
  BARs.
* Patches 13-15 add support for reprogramable BARs and remove the dt
  property.
* Patch 16 adds support for PCIE 1.1.

Based on the series at [1].

[1] https://lists.cs.columbia.edu/pipermail/kvmarm/2019-March/034964.html

Alexandru Elisei (8):
  Makefile: Use correct objcopy binary when cross-compiling for x86_64
  Remove pci-shmem device
  Check that a PCI device's memory size is power of two
  arm: pci.c: Advertise only PCI bus 0 in the DT
  virtio/pci: Ignore MMIO and I/O accesses when they are disabled
  Use independent read/write locks for ioport and mmio
  virtio/pci: Add support for BAR configuration
  Add PCI Express 1.1 support

Julien Thierry (7):
  ioport: pci: Move port allocations to PCI devices
  pci: Fix ioport allocation size
  arm/pci: Fix PCI IO region
  arm/pci: Do not use first PCI IO space bytes for devices
  virtio/pci: Make memory and IO BARs independent
  vfio: Add support for BAR configuration
  arm/fdt: Remove 'linux,pci-probe-only' property

Sami Mujawar (1):
  pci: Fix BAR resource sizing arbitration

 Makefile                          |   4 +-
 arm/fdt.c                         |   1 -
 arm/include/arm-common/kvm-arch.h |   2 +-
 arm/include/arm-common/pci.h      |   1 +
 arm/kvm.c                         |   3 +
 arm/pci.c                         |  28 ++-
 builtin-run.c                     |   5 -
 hw/pci-shmem.c                    | 400 ------------------------------
 hw/vesa.c                         |  21 +-
 include/kvm/ioport.h              |   4 -
 include/kvm/pci-shmem.h           |  32 ---
 include/kvm/pci.h                 |  61 ++++-
 include/kvm/util.h                |   2 +
 include/kvm/vesa.h                |   6 +-
 include/kvm/virtio-pci.h          |   1 +
 ioport.c                          |  36 +--
 mmio.c                            |  26 +-
 pci.c                             |  64 ++++-
 powerpc/include/kvm/kvm-arch.h    |   2 +-
 vfio/core.c                       |   6 +-
 vfio/pci.c                        |  97 +++++++-
 virtio/pci.c                      | 355 ++++++++++++++++++++------
 x86/include/kvm/kvm-arch.h        |   2 +-
 23 files changed, 562 insertions(+), 597 deletions(-)
 delete mode 100644 hw/pci-shmem.c
 delete mode 100644 include/kvm/pci-shmem.h
```
#### [RFC PATCH v8 0/7] Enable ptp_kvm for arm64
##### From: Jianyong Wu <jianyong.wu@arm.com>

```c
From patchwork Mon Nov 25 10:44:58 2019
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Jianyong Wu <jianyong.wu@arm.com>
X-Patchwork-Id: 11260177
Return-Path: <SRS0=umKK=ZR=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 5EAED1390
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 25 Nov 2019 10:45:37 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 49A3E20740
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 25 Nov 2019 10:45:37 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727573AbfKYKpc (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 25 Nov 2019 05:45:32 -0500
Received: from foss.arm.com ([217.140.110.172]:47982 "EHLO foss.arm.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1727316AbfKYKpc (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 25 Nov 2019 05:45:32 -0500
Received: from usa-sjc-imap-foss1.foss.arm.com (unknown [10.121.207.14])
        by usa-sjc-mx-foss1.foss.arm.com (Postfix) with ESMTP id DF2FA328;
        Mon, 25 Nov 2019 02:45:31 -0800 (PST)
Received: from entos-d05.shanghai.arm.com (entos-d05.shanghai.arm.com
 [10.169.40.35])
        by usa-sjc-imap-foss1.foss.arm.com (Postfix) with ESMTPA id
 CEC5D3F52E;
        Mon, 25 Nov 2019 02:45:26 -0800 (PST)
From: Jianyong Wu <jianyong.wu@arm.com>
To: netdev@vger.kernel.org, yangbo.lu@nxp.com, john.stultz@linaro.org,
        tglx@linutronix.de, pbonzini@redhat.com,
        sean.j.christopherson@intel.com, maz@kernel.org,
        richardcochran@gmail.com, Mark.Rutland@arm.com, will@kernel.org,
        suzuki.poulose@arm.com
Cc: linux-kernel@vger.kernel.org, linux-arm-kernel@lists.infradead.org,
        kvmarm@lists.cs.columbia.edu, kvm@vger.kernel.org,
        Steve.Capper@arm.com, Kaly.Xin@arm.com, justin.he@arm.com,
        jianyong.wu@arm.com, nd@arm.com
Subject: [RFC PATCH v8 0/7] Enable ptp_kvm for arm64
Date: Mon, 25 Nov 2019 18:44:58 +0800
Message-Id: <20191125104506.36850-1-jianyong.wu@arm.com>
X-Mailer: git-send-email 2.17.1
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

kvm ptp targets to provide high precision time sync between guest
and host in virtualization environment. Here, we enable kvm ptp
for arm64.
This patch set base on [1][2][3]

change log:

from v7 to v8:
        (1) separate adding clocksource id for arm_arch_counter as a
single patch.
        (2) update commit message for patch 4/8.
        (3) refine patch 7/8 and patch 8/8 to make them more independent.

from v6 to v7:
        (1) include the omitted clocksource_id.h in last version.
        (2) reorder the header file in patch.
        (3) refine some words in commit message to make it more impersonal.

from v5 to v6:
        (1) apply Mark's patch[4] to get SMCCC conduit.
        (2) add mechanism to recognize current clocksource by add
clocksouce_id value into struct clocksource instead of method in patch-v5.
        (3) rename kvm_arch_ptp_get_clock_fn into
kvm_arch_ptp_get_crosststamp.

from v4 to v5:
        (1) remove hvc delay compensasion as it should leave to userspace.
        (2) check current clocksource in hvc call service.
        (3) expose current clocksource by adding it to
system_time_snapshot.
        (4) add helper to check if clocksource is arm_arch_counter.
        (5) rename kvm_ptp.c to ptp_kvm_common.c

from v3 to v4:
        (1) fix clocksource of ptp_kvm to arch_sys_counter.
        (2) move kvm_arch_ptp_get_clock_fn into arm_arch_timer.c
        (3) subtract cntvoff before return cycles from host.
        (4) use ktime_get_snapshot instead of getnstimeofday and
get_current_counterval to return time and counter value.
        (5) split ktime and counter into two 32-bit block respectively
to avoid Y2038-safe issue.
        (6) set time compensation to device time as half of the delay of
hvc call.
        (7) add ARM_ARCH_TIMER as dependency of ptp_kvm for
arm64.

from v2 to v3:
        (1) fix some issues in commit log.
        (2) add some receivers in send list.

from v1 to v2:
        (1) move arch-specific code from arch/ to driver/ptp/
        (2) offer mechanism to inform userspace if ptp_kvm service is
available.
        (3) separate ptp_kvm code for arm64 into hypervisor part and
guest part.
        (4) add API to expose monotonic clock and counter value.
        (5) refine code: remove no necessary part and reconsitution.

[1]https://git.kernel.org/pub/scm/linux/kernel/git/will/linux.git/
commit/?h=kvm/hvc&id=125ea89e4a21e2fc5235410f966a996a1a7148bf
[2]https://git.kernel.org/pub/scm/linux/kernel/git/will/linux.git/
commit/?h=kvm/hvc&id=464f5a1741e5959c3e4d2be1966ae0093b4dce06
[3]https://git.kernel.org/pub/scm/linux/kernel/git/will/linux.git/
commit/?h=kvm/hvc&id=6597490e005d0eeca8ed8c1c1d7b4318ee014681
[4]https://git.kernel.org/pub/scm/linux/kernel/git/arm64/linux.git/
commit/?h=for-next/smccc-conduit-cleanup&id=6b7fe77c334ae59fed9500140e08f4f896b36871

Jianyong Wu (6):
  psci: let arm_smccc_1_1_invoke available by modules
  ptp: Reorganize ptp_kvm modules to make it arch-independent.
  clocksource: Add clocksource id for arm arch counter
  psci: Add hvc call service for ptp_kvm.
  ptp: arm64: Enable ptp_kvm for arm64
  kvm: arm64: Add capability check extension for ptp_kvm

Mark Rutland (1):
  arm/arm64: smccc/psci: add arm_smccc_1_1_get_conduit()

Thomas Gleixner (1):
  time: Add mechanism to recognize clocksource in time_get_snapshot

 drivers/clocksource/arm_arch_timer.c        | 24 ++++++
 drivers/firmware/psci/psci.c                | 16 ++++
 drivers/ptp/Kconfig                         |  2 +-
 drivers/ptp/Makefile                        |  1 +
 drivers/ptp/ptp_kvm_arm64.c                 | 53 +++++++++++++
 drivers/ptp/{ptp_kvm.c => ptp_kvm_common.c} | 77 +++++-------------
 drivers/ptp/ptp_kvm_x86.c                   | 87 +++++++++++++++++++++
 include/asm-generic/ptp_kvm.h               | 12 +++
 include/linux/arm-smccc.h                   | 30 ++++++-
 include/linux/clocksource.h                 |  6 ++
 include/linux/clocksource_ids.h             | 13 +++
 include/linux/timekeeping.h                 | 12 +--
 include/uapi/linux/kvm.h                    |  1 +
 kernel/time/clocksource.c                   |  3 +
 kernel/time/timekeeping.c                   |  1 +
 virt/kvm/arm/arm.c                          |  1 +
 virt/kvm/arm/psci.c                         | 22 ++++++
 17 files changed, 295 insertions(+), 66 deletions(-)
 create mode 100644 drivers/ptp/ptp_kvm_arm64.c
 rename drivers/ptp/{ptp_kvm.c => ptp_kvm_common.c} (63%)
 create mode 100644 drivers/ptp/ptp_kvm_x86.c
 create mode 100644 include/asm-generic/ptp_kvm.h
 create mode 100644 include/linux/clocksource_ids.h
```
