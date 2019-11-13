

#### [PATCH v3 00/23] mm/gup: track dma-pinned pages: FOLL_PIN,
##### From: John Hubbard <jhubbard@nvidia.com>

```c
From patchwork Tue Nov 12 00:06:37 2019
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: John Hubbard <jhubbard@nvidia.com>
X-Patchwork-Id: 11238341
Return-Path: <SRS0=xhWs=ZE=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 9166916B1
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 12 Nov 2019 00:11:07 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 5C5082196E
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 12 Nov 2019 00:11:07 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=nvidia.com header.i=@nvidia.com
 header.b="o9SF4xl6"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727164AbfKLAHN (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 11 Nov 2019 19:07:13 -0500
Received: from hqemgate14.nvidia.com ([216.228.121.143]:10605 "EHLO
        hqemgate14.nvidia.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726949AbfKLAHN (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 11 Nov 2019 19:07:13 -0500
Received: from hqpgpgate101.nvidia.com (Not Verified[216.228.121.13]) by
 hqemgate14.nvidia.com (using TLS: TLSv1.2, DES-CBC3-SHA)
        id <B5dc9f7aa0001>; Mon, 11 Nov 2019 16:07:06 -0800
Received: from hqmail.nvidia.com ([172.20.161.6])
  by hqpgpgate101.nvidia.com (PGP Universal service);
  Mon, 11 Nov 2019 16:07:04 -0800
X-PGP-Universal: processed;
        by hqpgpgate101.nvidia.com on Mon, 11 Nov 2019 16:07:04 -0800
Received: from HQMAIL107.nvidia.com (172.20.187.13) by HQMAIL107.nvidia.com
 (172.20.187.13) with Microsoft SMTP Server (TLS) id 15.0.1473.3; Tue, 12 Nov
 2019 00:07:03 +0000
Received: from rnnvemgw01.nvidia.com (10.128.109.123) by HQMAIL107.nvidia.com
 (172.20.187.13) with Microsoft SMTP Server (TLS) id 15.0.1473.3 via Frontend
 Transport; Tue, 12 Nov 2019 00:07:02 +0000
Received: from blueforge.nvidia.com (Not Verified[10.110.48.28]) by
 rnnvemgw01.nvidia.com with Trustwave SEG (v7,5,8,10121)
        id <B5dc9f7a50005>; Mon, 11 Nov 2019 16:07:02 -0800
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
Subject: [PATCH v3 00/23] mm/gup: track dma-pinned pages: FOLL_PIN,
 FOLL_LONGTERM
Date: Mon, 11 Nov 2019 16:06:37 -0800
Message-ID: <20191112000700.3455038-1-jhubbard@nvidia.com>
X-Mailer: git-send-email 2.24.0
MIME-Version: 1.0
X-NVConfidentiality: public
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=nvidia.com; s=n1;
        t=1573517227; bh=JNzo7F9Uhd78yzMBde3KTfKR6QFKvOysu7c55VwbHak=;
        h=X-PGP-Universal:From:To:CC:Subject:Date:Message-ID:X-Mailer:
         MIME-Version:X-NVConfidentiality:Content-Type:
         Content-Transfer-Encoding;
        b=o9SF4xl64HRgEPHvkHoWRVd6NPoz/55me3p6LoD2kIji1LweghyUDktb6XSAQ3iJ3
         cfhFxMryHc9DJrJcCIFZ3iGqYwt2ssscfuhFFw/XpSbJT58EIt8L9y6LerhnrPSHE3
         EdEpFQ6NH4d8IOKai6LAR4Axw5mIKHuTnBygTtUlZdZPySg+d0A3Oy0fKaInMWyT9J
         SvANrkrJ9clhDPNVmeNO+XuHM5bjvqzzMZ/NiVknqIu7c9yXMCGlTlzlbPMzqDPBT5
         jrQ55E6H2Wxm3RXAN8Ep0kb7yVwABixc+8zsJQbE9QB8LK08Q0+uUWO2trTbA96gmB
         /2JmtFtig54FQ==
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Hi,

The cover letter is long, so the more important stuff is first:

* Jason, if you or someone could look at the the VFIO cleanup (patch 8)
  and conversion to FOLL_PIN (patch 18), to make sure it's use of
  remote and longterm gup matches what we discussed during the review
  of v2, I'd appreciate it.

* Also for Jason and IB: as noted below, in patch 11, I am (too?) boldly
  converting from put_user_pages() to release_pages().

* Jerome, I am going to take a look at doing your FOLL_GET change idea
  (some callers should set FOLL_GET) separately, because it blew up "a
  little bit" in my face. It's definitely a separate--tiny, but risky--project.
  It also looks more reasonable when applied on top of this series here
  (and it conflicts a lot), so I'm going to send it as a follow-up.

Changes since v2:

* Added a patch to convert IB/umem from normal gup, to gup_fast(). This
  is also posted separately, in order to hopefully get some runtime
  testing.

* Changed the page devmap code to be a little clearer,
  thanks to Jerome for that.

* Split out the page devmap changes into a separate patch (and moved
  Ira's Signed-off-by to that patch).

* Fixed my bug in IB: ODP code does not require pin_user_pages()
  semantics. Therefore, revert the put_user_page() calls to put_page(),
  and leave the get_user_pages() call as-is.

      * As part of the revert, I am proposing here a change directly
        from put_user_pages(), to release_pages(). I'd feel better if
        someone agrees that this is the best way. It uses the more
        efficient release_pages(), instead of put_page() in a loop,
        and keep the change to just a few character on one line,
        but OTOH it is not a pure revert.

* Loosened the FOLL_LONGTERM restrictions in the
  __get_user_pages_locked() implementation, and used that in order
  to fix up a VFIO bug. Thanks to Jason for that idea.

    * Note the use of release_pages() in IB: is that OK?

* Added a few more WARN's and clarifying comments nearby.

* Many documentation improvements in various comments.

* Moved the new pin_user_pages.rst from Documentation/vm/ to
  Documentation/core-api/ .

* Commit descriptions: added clarifying notes to the three patches
  (drm/via, fs/io_uring, net/xdp) that already had put_user_page()
  calls in place.

* Collected all pending Reviewed-by and Acked-by tags, from v1 and v2
  email threads.

* Lot of churn from v2 --> v3, so it's possible that new bugs
  sneaked in.

NOT DONE: separate patchset is required:

* __get_user_pages_locked(): stop compensating for
  buggy callers who failed to set FOLL_GET. Instead, assert
  that FOLL_GET is set (and fail if it's not).

======================================================================
Original cover letter (edited to fix up the patch description numbers)

This applies cleanly to linux-next and mmotm, and also to linux.git if
linux-next's commit 20cac10710c9 ("mm/gup_benchmark: fix MAP_HUGETLB
case") is first applied there.

This provides tracking of dma-pinned pages. This is a prerequisite to
solving the larger problem of proper interactions between file-backed
pages, and [R]DMA activities, as discussed in [1], [2], [3], and in
a remarkable number of email threads since about 2017. :)

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

============================================================
Patch summary:

* Patches 1-8: refactoring and preparatory cleanup, independent fixes

* Patch 9: introduce pin_user_pages(), FOLL_PIN, but no functional
           changes yet
* Patches 10-15: Convert existing put_user_page() callers, to use the
                new pin*()
* Patch 16: Activate tracking of FOLL_PIN pages.
* Patches 17-19: convert FOLL_LONGTERM callers
* Patches: 20-22: gup_benchmark and run_vmtests support
* Patch 23: enforce FOLL_LONGTERM as a gup-internal (only) flag

============================================================
Testing:

* I've done some overall kernel testing (LTP, and a few other goodies),
  and some directed testing to exercise some of the changes. And as you
  can see, gup_benchmark is enhanced to exercise this. Basically, I've been
  able to runtime test the core get_user_pages() and pin_user_pages() and
  related routines, but not so much on several of the call sites--but those
  are generally just a couple of lines changed, each.

  Not much of the kernel is actually using this, which on one hand
  reduces risk quite a lot. But on the other hand, testing coverage
  is low. So I'd love it if, in particular, the Infiniband and PowerPC
  folks could do a smoke test of this series for me.

  Also, my runtime testing for the call sites so far is very weak:

    * io_uring: Some directed tests from liburing exercise this, and they pass.
    * process_vm_access.c: A small directed test passes.
    * gup_benchmark: the enhanced version hits the new gup.c code, and passes.
    * infiniband (still only have crude "IB pingpong" working, on a
                  good day: it's not exercising my conversions at runtime...)
    * VFIO: compiles (I'm vowing to set up a run time test soon, but it's
                      not ready just yet)
    * powerpc: it compiles...
    * drm/via: compiles...
    * goldfish: compiles...
    * net/xdp: compiles...
    * media/v4l2: compiles...

============================================================
Next:

* Get the block/bio_vec sites converted to use pin_user_pages().

* Work with Ira and Dave Chinner to weave this together with the
  layout lease stuff.

============================================================

[1] Some slow progress on get_user_pages() (Apr 2, 2019): https://lwn.net/Articles/784574/
[2] DMA and get_user_pages() (LPC: Dec 12, 2018): https://lwn.net/Articles/774411/
[3] The trouble with get_user_pages() (Apr 30, 2018): https://lwn.net/Articles/753027/

John Hubbard (23):
  mm/gup: pass flags arg to __gup_device_* functions
  mm/gup: factor out duplicate code from four routines
  mm/gup: move try_get_compound_head() to top, fix minor issues
  mm: devmap: refactor 1-based refcounting for ZONE_DEVICE pages
  goldish_pipe: rename local pin_user_pages() routine
  IB/umem: use get_user_pages_fast() to pin DMA pages
  media/v4l2-core: set pages dirty upon releasing DMA buffers
  vfio, mm: fix get_user_pages_remote() and FOLL_LONGTERM
  mm/gup: introduce pin_user_pages*() and FOLL_PIN
  goldish_pipe: convert to pin_user_pages() and put_user_page()
  IB/{core,hw,umem}: set FOLL_PIN, FOLL_LONGTERM via
    pin_longterm_pages*()
  mm/process_vm_access: set FOLL_PIN via pin_user_pages_remote()
  drm/via: set FOLL_PIN via pin_user_pages_fast()
  fs/io_uring: set FOLL_PIN via pin_user_pages()
  net/xdp: set FOLL_PIN via pin_user_pages()
  mm/gup: track FOLL_PIN pages
  media/v4l2-core: pin_longterm_pages (FOLL_PIN) and put_user_page()
    conversion
  vfio, mm: pin_longterm_pages (FOLL_PIN) and put_user_page() conversion
  powerpc: book3s64: convert to pin_longterm_pages() and put_user_page()
  mm/gup_benchmark: use proper FOLL_WRITE flags instead of hard-coding
    "1"
  mm/gup_benchmark: support pin_user_pages() and related calls
  selftests/vm: run_vmtests: invoke gup_benchmark with basic FOLL_PIN
    coverage
  mm/gup: remove support for gup(FOLL_LONGTERM)

 Documentation/core-api/index.rst            |   1 +
 Documentation/core-api/pin_user_pages.rst   | 218 +++++++
 arch/powerpc/mm/book3s64/iommu_api.c        |  15 +-
 drivers/gpu/drm/via/via_dmablit.c           |   2 +-
 drivers/infiniband/core/umem.c              |  17 +-
 drivers/infiniband/core/umem_odp.c          |  24 +-
 drivers/infiniband/hw/hfi1/user_pages.c     |   4 +-
 drivers/infiniband/hw/mthca/mthca_memfree.c |   3 +-
 drivers/infiniband/hw/qib/qib_user_pages.c  |   8 +-
 drivers/infiniband/hw/qib/qib_user_sdma.c   |   2 +-
 drivers/infiniband/hw/usnic/usnic_uiom.c    |   9 +-
 drivers/infiniband/sw/siw/siw_mem.c         |   5 +-
 drivers/media/v4l2-core/videobuf-dma-sg.c   |  10 +-
 drivers/platform/goldfish/goldfish_pipe.c   |  35 +-
 drivers/vfio/vfio_iommu_type1.c             |  35 +-
 fs/io_uring.c                               |   5 +-
 include/linux/mm.h                          | 164 +++++-
 include/linux/mmzone.h                      |   2 +
 include/linux/page_ref.h                    |  10 +
 mm/gup.c                                    | 608 ++++++++++++++++----
 mm/gup_benchmark.c                          |  87 ++-
 mm/huge_memory.c                            |  54 +-
 mm/hugetlb.c                                |  39 +-
 mm/memremap.c                               |  67 +--
 mm/process_vm_access.c                      |  28 +-
 mm/vmstat.c                                 |   2 +
 net/xdp/xdp_umem.c                          |   4 +-
 tools/testing/selftests/vm/gup_benchmark.c  |  34 +-
 tools/testing/selftests/vm/run_vmtests      |  22 +
 29 files changed, 1180 insertions(+), 334 deletions(-)
 create mode 100644 Documentation/core-api/pin_user_pages.rst
```
#### [RFC V3 0/2] Intel IFC VF driver for VDPA
##### From: Zhu Lingshan <lingshan.zhu@intel.com>

```c
From patchwork Tue Nov 12 09:29:47 2019
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Zhu Lingshan <lingshan.zhu@intel.com>
X-Patchwork-Id: 11238949
Return-Path: <SRS0=xhWs=ZE=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id EBF3614E5
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 12 Nov 2019 09:32:08 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id D6EB121783
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 12 Nov 2019 09:32:08 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727113AbfKLJcE (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 12 Nov 2019 04:32:04 -0500
Received: from mga05.intel.com ([192.55.52.43]:56112 "EHLO mga05.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1725834AbfKLJcE (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 12 Nov 2019 04:32:04 -0500
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from orsmga008.jf.intel.com ([10.7.209.65])
  by fmsmga105.fm.intel.com with ESMTP/TLS/DHE-RSA-AES256-GCM-SHA384;
 12 Nov 2019 01:32:02 -0800
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.68,295,1569308400";
   d="scan'208";a="198017529"
Received: from unknown (HELO localhost.localdomain.bj.intel.com)
 ([10.240.193.79])
  by orsmga008.jf.intel.com with ESMTP; 12 Nov 2019 01:31:59 -0800
From: Zhu Lingshan <lingshan.zhu@intel.com>
To: mst@redhat.com, jasowang@redhat.com, alex.williamson@redhat.com
Cc: linux-kernel@vger.kernel.org,
        virtualization@lists.linux-foundation.org, kvm@vger.kernel.org,
        netdev@vger.kernel.org, dan.daly@intel.com,
        cunming.liang@intel.com, tiwei.bie@intel.com, jason.zeng@intel.com,
        zhiyuan.lv@intel.com, Zhu Lingshan <lingshan.zhu@intel.com>
Subject: [RFC V3 0/2] Intel IFC VF driver for VDPA
Date: Tue, 12 Nov 2019 17:29:47 +0800
Message-Id: <1573550989-40860-1-git-send-email-lingshan.zhu@intel.com>
X-Mailer: git-send-email 1.8.3.1
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Hi all:
  This series intends to introduce Intel IFC VF NIC driver for Vhost
Data Plane Acceleration(VDPA).

Here comes two main parts, one is ifcvf_base layer, which handles
hardware operations. The other is ifcvf_main layer handles VF
initialization, configuration and removal, which depends on
and complys to:
virtio_mdev https://lkml.org/lkml/2019/11/7/650
vhost_mdev https://lkml.org/lkml/2019/11/7/62

This patchset passed netperf tests.

This is RFC V3, plese help review.

Changes from V2:
removed some unnecessary code.
using a struct ifcvf_lm_cfg to address hw->lm_cfg and operations on it.
set CONFIG_S_FAILED  when ifcvf_start_hw() fail.
removed VIRTIO_NET_F_CTRL_VQ and VIRTIO_NET_F_STATUS
replace ifcvf_net_config with virtio_net_config.
minor changes

Changes from V1:
using le32_to_cpu() to convert PCI capabilities.
some set /get  operations will sync with the hardware, eg get_status
and get_generation.
remove feature bit VHOST_F_LOG_ALL, add VIRTIO_F_ORDERED_PLATFORM
add get/set_config functions.
split mdev type group into mdev_type_group_virtio and mdev_type_group_vhost
add ifcvf_mdev_get_mdev_features()
coding stype changes.

Zhu Lingshan (2):
  This commit introduced ifcvf_base layer, which handles hardware    
    operations and configurations.
  This commit introduced IFC operations for vdpa, which complys to    
    virtio_mdev and vhost_mdev interfaces, handles IFC VF    
    initialization, configuration and removal.

 drivers/vhost/ifcvf/ifcvf_base.c | 326 ++++++++++++++++++++++
 drivers/vhost/ifcvf/ifcvf_base.h | 129 +++++++++
 drivers/vhost/ifcvf/ifcvf_main.c | 579 +++++++++++++++++++++++++++++++++++++++
 3 files changed, 1034 insertions(+)
 create mode 100644 drivers/vhost/ifcvf/ifcvf_base.c
 create mode 100644 drivers/vhost/ifcvf/ifcvf_base.h
 create mode 100644 drivers/vhost/ifcvf/ifcvf_main.c
```
#### [PATCH v9 Kernel 0/5] Add KABIs to support migration for VFIO devices
##### From: Kirti Wankhede <kwankhede@nvidia.com>

```c
From patchwork Tue Nov 12 17:03:35 2019
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Kirti Wankhede <kwankhede@nvidia.com>
X-Patchwork-Id: 11239843
Return-Path: <SRS0=xhWs=ZE=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 55D5713BD
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 12 Nov 2019 17:32:48 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 35DC4214E0
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 12 Nov 2019 17:32:48 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=nvidia.com header.i=@nvidia.com
 header.b="hngEcYbi"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727020AbfKLRcr (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 12 Nov 2019 12:32:47 -0500
Received: from hqemgate16.nvidia.com ([216.228.121.65]:7538 "EHLO
        hqemgate16.nvidia.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726980AbfKLRcq (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 12 Nov 2019 12:32:46 -0500
Received: from hqpgpgate101.nvidia.com (Not Verified[216.228.121.13]) by
 hqemgate16.nvidia.com (using TLS: TLSv1.2, DES-CBC3-SHA)
        id <B5dcaec850000>; Tue, 12 Nov 2019 09:31:49 -0800
Received: from hqmail.nvidia.com ([172.20.161.6])
  by hqpgpgate101.nvidia.com (PGP Universal service);
  Tue, 12 Nov 2019 09:32:45 -0800
X-PGP-Universal: processed;
        by hqpgpgate101.nvidia.com on Tue, 12 Nov 2019 09:32:45 -0800
Received: from HQMAIL105.nvidia.com (172.20.187.12) by HQMAIL111.nvidia.com
 (172.20.187.18) with Microsoft SMTP Server (TLS) id 15.0.1473.3; Tue, 12 Nov
 2019 17:32:45 +0000
Received: from kwankhede-dev.nvidia.com (10.124.1.5) by HQMAIL105.nvidia.com
 (172.20.187.12) with Microsoft SMTP Server (TLS) id 15.0.1473.3 via Frontend
 Transport; Tue, 12 Nov 2019 17:32:38 +0000
From: Kirti Wankhede <kwankhede@nvidia.com>
To: <alex.williamson@redhat.com>, <cjia@nvidia.com>
CC: <kevin.tian@intel.com>, <ziye.yang@intel.com>,
        <changpeng.liu@intel.com>, <yi.l.liu@intel.com>,
        <mlevitsk@redhat.com>, <eskultet@redhat.com>, <cohuck@redhat.com>,
        <dgilbert@redhat.com>, <jonathan.davies@nutanix.com>,
        <eauger@redhat.com>, <aik@ozlabs.ru>, <pasic@linux.ibm.com>,
        <felipe@nutanix.com>, <Zhengxiao.zx@Alibaba-inc.com>,
        <shuangtai.tst@alibaba-inc.com>, <Ken.Xue@amd.com>,
        <zhi.a.wang@intel.com>, <yan.y.zhao@intel.com>,
        <qemu-devel@nongnu.org>, <kvm@vger.kernel.org>,
        "Kirti Wankhede" <kwankhede@nvidia.com>
Subject: [PATCH v9 Kernel 0/5] Add KABIs to support migration for VFIO devices
Date: Tue, 12 Nov 2019 22:33:35 +0530
Message-ID: <1573578220-7530-1-git-send-email-kwankhede@nvidia.com>
X-Mailer: git-send-email 2.7.0
X-NVConfidentiality: public
MIME-Version: 1.0
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=nvidia.com; s=n1;
        t=1573579909; bh=VwC/4UKhllpfCNBLQXoDqFAkQVIzZ3vwpVHFBclHKmQ=;
        h=X-PGP-Universal:From:To:CC:Subject:Date:Message-ID:X-Mailer:
         X-NVConfidentiality:MIME-Version:Content-Type;
        b=hngEcYbiELuMYGwLOY+aojWwkFwbIb88rEnqTaNdX8pKqsHhdtawuQ5Owkr/83lZd
         8w6d4hihyrv9NSLgpxsbJKvqrs2m10BaVI6f3Swqj7xHgLglW456B0isfaqHcyrBbi
         nqUUZqucInxHkPgktFJT+C2/tf3N1tL9KUejNR6dhDN/1jnY0OYXo7tQchEbvlY3Dc
         xUYTui9uTUTAJnYlvTY07EI/hj0iOuAr7QE464kYCvg490MjJ6LXmz9xz9oa4jYydQ
         cJe+qR8aWGih//SplUcHpCv2EjELQPEsflP21H3jWPINYWm8QfNRTD346RRAmfLK1o
         /yqJxG3uWVylQ==
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Hi Alex,

To keep kernel and QEMU patches in sync, keeping v9 version for this patch
set. Till v8 version, KABI was being discussed from QEMU patch series[1].
In earlier version mail and as per in person discussion at KVM forum, this
patch set adds:
* New IOCTL VFIO_IOMMU_GET_DIRTY_BITMAP to get dirty pages bitmap with
  respect to IOMMU container rather than per device. All pages pinned by
  vendor driver through vfio_pin_pages external API has to be marked as
  dirty during  migration.
  When there are CPU writes, CPU dirty page tracking can identify dirtied
  pages, but any page pinned by vendor driver can also be written by
  device. As of now there is no device which has hardware support for
  dirty page tracking. So all pages which are pinned by vendor driver
  should be considered as dirty.
* New IOCTL VFIO_IOMMU_UNMAP_DMA_GET_BITMAP to get dirty pages bitmap
  before unmapping IO virtual address range.
  With vIOMMU, during pre-copy phase of migration, while CPUs are still
  running, IO virtual address unmap can happen while device still keeping
  reference of guest pfns. Those pages should be reported as dirty before
  unmap, so that VFIO user space application can copy content of those
  pages from source to destination.

Yet TODO:
Since there is no device which has hardware support for system memmory
dirty bitmap tracking, right now there is no other API from vendor driver
to VFIO IOMMU module to report dirty pages. In future, when such hardware
support will be implemented, an API will be required such that vendor
driver could report dirty pages to VFIO module during migration phases.

[1] https://www.mail-archive.com/qemu-devel@nongnu.org/msg640400.html

Adding revision history from previous QEMU patch set to understand KABI
changes done till now

v8 -> v9:
- Split patch set in 2 sets, Kernel and QEMU.
- Dirty pages bitmap is queried from IOMMU container rather than from
  vendor driver for per device. Added 2 ioctls to achieve this.

v7 -> v8:
- Updated comments for KABI
- Added BAR address validation check during PCI device's config space load
  as suggested by Dr. David Alan Gilbert.
- Changed vfio_migration_set_state() to set or clear device state flags.
- Some nit fixes.

v6 -> v7:
- Fix build failures.

v5 -> v6:
- Fix build failure.

v4 -> v5:
- Added decriptive comment about the sequence of access of members of
  structure vfio_device_migration_info to be followed based on Alex's
  suggestion
- Updated get dirty pages sequence.
- As per Cornelia Huck's suggestion, added callbacks to VFIODeviceOps to
  get_object, save_config and load_config.
- Fixed multiple nit picks.
- Tested live migration with multiple vfio device assigned to a VM.

v3 -> v4:
- Added one more bit for _RESUMING flag to be set explicitly.
- data_offset field is read-only for user space application.
- data_size is read for every iteration before reading data from migration,
  that is removed assumption that data will be till end of migration
  region.
- If vendor driver supports mappable sparsed region, map those region
  during setup state of save/load, similarly unmap those from cleanup
  routines.
- Handles race condition that causes data corruption in migration region
  during save device state by adding mutex and serialiaing save_buffer and
  get_dirty_pages routines.
- Skip called get_dirty_pages routine for mapped MMIO region of device.
- Added trace events.
- Split into multiple functional patches.

v2 -> v3:
- Removed enum of VFIO device states. Defined VFIO device state with 2
  bits.
- Re-structured vfio_device_migration_info to keep it minimal and defined
  action on read and write access on its members.

v1 -> v2:
- Defined MIGRATION region type and sub-type which should be used with
  region type capability.
- Re-structured vfio_device_migration_info. This structure will be placed
  at 0th offset of migration region.
- Replaced ioctl with read/write for trapped part of migration region.
- Added both type of access support, trapped or mmapped, for data section
  of the region.
- Moved PCI device functions to pci file.
- Added iteration to get dirty page bitmap until bitmap for all requested
  pages are copied.

Thanks,
Kirti

Kirti Wankhede (5):
  vfio: KABI for migration interface for device state
  vfio iommu: Add ioctl defination to get dirty pages bitmap.
  vfio iommu: Add ioctl defination to unmap IOVA and return dirty bitmap
  vfio iommu: Implementation of ioctl to get dirty pages bitmap.
  vfio iommu: Implementation of ioctl to get dirty bitmap before unmap

 drivers/vfio/vfio_iommu_type1.c | 163 ++++++++++++++++++++++++++++++++++++++-
 include/uapi/linux/vfio.h       | 164 ++++++++++++++++++++++++++++++++++++++++
 2 files changed, 325 insertions(+), 2 deletions(-)
```
#### [FYI PATCH 0/7] Mitigation for CVE-2018-12207
##### From: Paolo Bonzini <pbonzini@redhat.com>

```c
From patchwork Tue Nov 12 21:21:30 2019
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Paolo Bonzini <pbonzini@redhat.com>
X-Patchwork-Id: 11240201
Return-Path: <SRS0=xhWs=ZE=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 7D91B15AB
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 12 Nov 2019 21:22:31 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 5D2E72196E
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 12 Nov 2019 21:22:31 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=fail reason="signature verification failed" (2048-bit key)
 header.d=gmail.com header.i=@gmail.com header.b="WNXrjKl+"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726983AbfKLVVm (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 12 Nov 2019 16:21:42 -0500
Received: from mail-wm1-f68.google.com ([209.85.128.68]:39793 "EHLO
        mail-wm1-f68.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726896AbfKLVVm (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 12 Nov 2019 16:21:42 -0500
Received: by mail-wm1-f68.google.com with SMTP id t26so4507908wmi.4;
        Tue, 12 Nov 2019 13:21:40 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=sender:from:to:subject:date:message-id;
        bh=dEhpPGqL2EnHvM+RMKgKzToY3FC78Q0MvKFrMXo/rVg=;
        b=WNXrjKl+NzL/krxGUzhS16CUd+Jmzist2kq/sBXSoMZtW6q7/qk0LYsrJUjp6RaDSF
         wU2j3rZDNhCBT5Hxma+ntzFVX9U/ojQsXSlFObe8jY2aANnAT7V30CUKIi9EC3x8StDO
         Jx6TtutddTKB6mI81DjwmmdqECeKojN7giKo6++9/yUISdjlezNNnzxgviegpvJiCpec
         WCrrFtrxJyoDbERz9Zmrl7kmOml5h30B+D+PDeXzbw2qa75qfKj0QwLMLduL8K4P129O
         x5h+XEQTiV4+US7m+IE6OwiDruA9TGuxPIsVrJf8wqP3licqss6d3+EaR/W99bssTB+L
         ggig==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:sender:from:to:subject:date:message-id;
        bh=dEhpPGqL2EnHvM+RMKgKzToY3FC78Q0MvKFrMXo/rVg=;
        b=p+C/kwHDv4lTvlfbT7fhAuZJ2ZtwvclkLHugsuxAbp640Z6sxqO3DncFKxHXWobuab
         1kQxSLhnLZqJV9mcMXBjVXrFkHf/PJ5MU1G9eOgpzc4riHEH6UalEcaAHETRhGhFjEJq
         noycLOJbTRGeLMKkIFmVX2lJZ1WMnSQmRZwzjDJ4iaBzHpJtgORgRsdF9zu/4pDuxbQH
         WiecM0k77ZF68tHBcxKh/cMEy84zRC38+bhp7gMExM5Gcj/rxdNEzntD99BjgPiPYEdJ
         uR8lesy1BVITJde09HfHgi0je2yBA36hxFNVuAYpcY906w1SFCB+665ysoJFhFqcQQ+h
         P+Dg==
X-Gm-Message-State: APjAAAUEmaiP9CHWDBVO4OkFcKHGkfmMu2N39uEMX/LXF+4alm1o4Cdg
        DZdVfJrUcgO5wwZHtq/7TOQwmoNt
X-Google-Smtp-Source: 
 APXvYqyfh0JsBntGXcUehgQXwZOjx5Mf9XThvqTdrcx0A/dP4zfs7gcKSkSjtoN8J+eidPue1VdIDQ==
X-Received: by 2002:a7b:cf35:: with SMTP id m21mr4156466wmg.141.1573593699205;
        Tue, 12 Nov 2019 13:21:39 -0800 (PST)
Received: from 640k.lan ([93.56.166.5])
        by smtp.gmail.com with ESMTPSA id q25sm198664wra.3.2019.11.12.13.21.38
        (version=TLS1_2 cipher=ECDHE-RSA-AES128-GCM-SHA256 bits=128/128);
        Tue, 12 Nov 2019 13:21:38 -0800 (PST)
From: Paolo Bonzini <pbonzini@redhat.com>
To: linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Subject: [FYI PATCH 0/7] Mitigation for CVE-2018-12207
Date: Tue, 12 Nov 2019 22:21:30 +0100
Message-Id: <1573593697-25061-1-git-send-email-pbonzini@redhat.com>
X-Mailer: git-send-email 1.8.3.1
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

CVE-2018-12207 is a microarchitectural implementation issue
that could allow an unprivileged local attacker to cause system wide
denial-of-service condition.

Privileged software may change the page size (ex. 4KB, 2MB, 1GB) in the
paging structures, without following such paging structure changes with
invalidation of the TLB entries corresponding to the changed pages. In
this case, the attacker could invoke instruction fetch, which will result
in the processor hitting multiple TLB entries, reporting a machine check
error exception, and ultimately hanging the system.

The attached patches mitigate the vulnerability by making huge pages
non-executable. The processor will not be able to execute an instruction
residing in a large page (ie. 2MB, 1GB, etc.) without causing a trap into
the host kernel/hypervisor; KVM will then break the large page into 4KB
pages and gives executable permission to 4KB pages.

Thanks to everyone that was involved in the development of these patches,
especially Junaid Shahid, who provided the first version of the code,
and Thomas Gleixner.

Paolo

Gomez Iglesias, Antonio (1):
  Documentation: Add ITLB_MULTIHIT documentation

Junaid Shahid (2):
  kvm: Add helper function for creating VM worker threads
  kvm: x86: mmu: Recovery of shattered NX large pages

Paolo Bonzini (1):
  kvm: mmu: ITLB_MULTIHIT mitigation

Pawan Gupta (1):
  x86/cpu: Add Tremont to the cpu vulnerability whitelist

Tyler Hicks (1):
  cpu/speculation: Uninline and export CPU mitigations helpers

Vineela Tummalapalli (1):
  x86/bugs: Add ITLB_MULTIHIT bug infrastructure

 Documentation/ABI/testing/sysfs-devices-system-cpu |   1 +
 Documentation/admin-guide/hw-vuln/index.rst        |   1 +
 Documentation/admin-guide/hw-vuln/multihit.rst     | 163 +++++++++++++
 Documentation/admin-guide/kernel-parameters.txt    |  25 ++
 arch/x86/include/asm/cpufeatures.h                 |   1 +
 arch/x86/include/asm/kvm_host.h                    |   6 +
 arch/x86/include/asm/msr-index.h                   |   7 +
 arch/x86/kernel/cpu/bugs.c                         |  24 ++
 arch/x86/kernel/cpu/common.c                       |  67 ++---
 arch/x86/kvm/mmu.c                                 | 270 ++++++++++++++++++++-
 arch/x86/kvm/mmu.h                                 |   4 +
 arch/x86/kvm/paging_tmpl.h                         |  29 ++-
 arch/x86/kvm/x86.c                                 |  20 ++
 drivers/base/cpu.c                                 |   8 +
 include/linux/cpu.h                                |  27 +--
 include/linux/kvm_host.h                           |   6 +
 kernel/cpu.c                                       |  27 ++-
 virt/kvm/kvm_main.c                                | 112 +++++++++
 18 files changed, 732 insertions(+), 66 deletions(-)
 create mode 100644 Documentation/admin-guide/hw-vuln/multihit.rst
```
