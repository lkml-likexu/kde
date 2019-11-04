

#### [PATCH v2 00/18] mm/gup: track dma-pinned pages: FOLL_PIN,
##### From: John Hubbard <jhubbard@nvidia.com>

```c
From patchwork Sun Nov  3 21:17:55 2019
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 8bit
X-Patchwork-Submitter: John Hubbard <jhubbard@nvidia.com>
X-Patchwork-Id: 11224551
Return-Path: <SRS0=CZz/=Y3=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 1BE4013BD
	for <patchwork-kvm@patchwork.kernel.org>;
 Sun,  3 Nov 2019 21:19:10 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id E586821A4A
	for <patchwork-kvm@patchwork.kernel.org>;
 Sun,  3 Nov 2019 21:19:09 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=nvidia.com header.i=@nvidia.com
 header.b="QFdybeXk"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728747AbfKCVSx (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Sun, 3 Nov 2019 16:18:53 -0500
Received: from hqemgate15.nvidia.com ([216.228.121.64]:17587 "EHLO
        hqemgate15.nvidia.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1728564AbfKCVS0 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Sun, 3 Nov 2019 16:18:26 -0500
Received: from hqpgpgate101.nvidia.com (Not Verified[216.228.121.13]) by
 hqemgate15.nvidia.com (using TLS: TLSv1.2, DES-CBC3-SHA)
        id <B5dbf441c0000>; Sun, 03 Nov 2019 13:18:20 -0800
Received: from hqmail.nvidia.com ([172.20.161.6])
  by hqpgpgate101.nvidia.com (PGP Universal service);
  Sun, 03 Nov 2019 13:18:15 -0800
X-PGP-Universal: processed;
        by hqpgpgate101.nvidia.com on Sun, 03 Nov 2019 13:18:15 -0800
Received: from HQMAIL107.nvidia.com (172.20.187.13) by HQMAIL111.nvidia.com
 (172.20.187.18) with Microsoft SMTP Server (TLS) id 15.0.1473.3; Sun, 3 Nov
 2019 21:18:14 +0000
Received: from hqnvemgw01.nvidia.com (172.20.150.20) by HQMAIL107.nvidia.com
 (172.20.187.13) with Microsoft SMTP Server (TLS) id 15.0.1473.3 via Frontend
 Transport; Sun, 3 Nov 2019 21:18:14 +0000
Received: from blueforge.nvidia.com (Not Verified[10.110.48.28]) by
 hqnvemgw01.nvidia.com with Trustwave SEG (v7,5,8,10121)
        id <B5dbf44160001>; Sun, 03 Nov 2019 13:18:14 -0800
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
Subject: [PATCH v2 00/18] mm/gup: track dma-pinned pages: FOLL_PIN,
 FOLL_LONGTERM
Date: Sun, 3 Nov 2019 13:17:55 -0800
Message-ID: <20191103211813.213227-1-jhubbard@nvidia.com>
X-Mailer: git-send-email 2.23.0
MIME-Version: 1.0
X-NVConfidentiality: public
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=nvidia.com; s=n1;
        t=1572815900; bh=GBV3ojpDDK4OBFB22u5Rnbzd8rZTGnaPAeFzYUht8Sk=;
        h=X-PGP-Universal:From:To:CC:Subject:Date:Message-ID:X-Mailer:
         MIME-Version:X-NVConfidentiality:Content-Type:
         Content-Transfer-Encoding;
        b=QFdybeXkgDaSikqJK8ut4Q3VaoLQPZvaXrOil25JjZA2drY+qH3mlg/JBBJj9CUkO
         FnWKh3HSWK12fVcCDfgZO3gj/PnKbOvnlx3cF6Te3oPgt64K0ScQSZlilcWgNVErRp
         sBQIZRfXIN70b0dwEGF4SAgE3WxBXUjfhgUu/ST459bfzdU7/J3Tc57sm0hCck2WzM
         Bl+CFxB3+DoOCzmMTNIsqpCr4cDD8LlzCDt9L0jqubkzo4mR4fOaGh5xqUeGuMOfU2
         OjOwLPsBvhDoaFgYYO+pfhwHgHAniOj+t7ll1ShzRTew8tOKK1v2qpbIc7QX9UbfSG
         iajQXzs4Buv0A==
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Hi,

Changes since v1:

* Changed the function signature of __huge_pt_done() from int to void.
* Renamed __remove_refs_from_head() to put_compound_head().
* Improved the comment documentation in mm.h and gup.c
* Merged Documentation/vm/pin_user_pages.rst into the "introduce
  FOLL_PIN" patch.
* Fixed Documentation/vm/pin_user_pages.rst:
     * Fixed up a TODO about DAX.
     * 31, not 32 bits total are available for counting
* Deleted some stale comments from the commit description of the
  VFIO patch.
* Added Reviewed-by tags from Ira Weiny and Jens Axboe, and Acked-by
  from Björn Töpel.

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

* Patches 1-4: refactoring and preparatory cleanup, independent fixes
    (Patch 4: V4L2-core bug fix (can be separately applied))

* Patch 5: introduce pin_user_pages(), FOLL_PIN, but no functional
           changes yet
* Patches 6-11: Convert existing put_user_page() callers, to use the
                new pin*()
* Patch 12: Activate tracking of FOLL_PIN pages.
* Patches 13-15: convert FOLL_LONGTERM callers
* Patches: 16-17: gup_benchmark and run_vmtests support
* Patch 18: enforce FOLL_LONGTERM as a gup-internal (only) flag

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

John Hubbard (18):
  mm/gup: pass flags arg to __gup_device_* functions
  mm/gup: factor out duplicate code from four routines
  goldish_pipe: rename local pin_user_pages() routine
  media/v4l2-core: set pages dirty upon releasing DMA buffers
  mm/gup: introduce pin_user_pages*() and FOLL_PIN
  goldish_pipe: convert to pin_user_pages() and put_user_page()
  infiniband: set FOLL_PIN, FOLL_LONGTERM via pin_longterm_pages*()
  mm/process_vm_access: set FOLL_PIN via pin_user_pages_remote()
  drm/via: set FOLL_PIN via pin_user_pages_fast()
  fs/io_uring: set FOLL_PIN via pin_user_pages()
  net/xdp: set FOLL_PIN via pin_user_pages()
  mm/gup: track FOLL_PIN pages
  media/v4l2-core: pin_longterm_pages (FOLL_PIN) and put_user_page()
    conversion
  vfio, mm: pin_longterm_pages (FOLL_PIN) and put_user_page() conversion
  powerpc: book3s64: convert to pin_longterm_pages() and put_user_page()
  mm/gup_benchmark: support pin_user_pages() and related calls
  selftests/vm: run_vmtests: invoke gup_benchmark with basic FOLL_PIN
    coverage
  mm/gup: remove support for gup(FOLL_LONGTERM)

 Documentation/vm/index.rst                  |   1 +
 Documentation/vm/pin_user_pages.rst         | 212 +++++++
 arch/powerpc/mm/book3s64/iommu_api.c        |  15 +-
 drivers/gpu/drm/via/via_dmablit.c           |   2 +-
 drivers/infiniband/core/umem.c              |   5 +-
 drivers/infiniband/core/umem_odp.c          |  10 +-
 drivers/infiniband/hw/hfi1/user_pages.c     |   4 +-
 drivers/infiniband/hw/mthca/mthca_memfree.c |   3 +-
 drivers/infiniband/hw/qib/qib_user_pages.c  |   8 +-
 drivers/infiniband/hw/qib/qib_user_sdma.c   |   2 +-
 drivers/infiniband/hw/usnic/usnic_uiom.c    |   9 +-
 drivers/infiniband/sw/siw/siw_mem.c         |   5 +-
 drivers/media/v4l2-core/videobuf-dma-sg.c   |  10 +-
 drivers/platform/goldfish/goldfish_pipe.c   |  35 +-
 drivers/vfio/vfio_iommu_type1.c             |  15 +-
 fs/io_uring.c                               |   5 +-
 include/linux/mm.h                          | 142 ++++-
 include/linux/mmzone.h                      |   2 +
 include/linux/page_ref.h                    |  10 +
 mm/gup.c                                    | 594 ++++++++++++++++----
 mm/gup_benchmark.c                          |  81 ++-
 mm/huge_memory.c                            |  32 +-
 mm/hugetlb.c                                |  28 +-
 mm/memremap.c                               |   4 +-
 mm/process_vm_access.c                      |  28 +-
 mm/vmstat.c                                 |   2 +
 net/xdp/xdp_umem.c                          |   4 +-
 tools/testing/selftests/vm/gup_benchmark.c  |  28 +-
 tools/testing/selftests/vm/run_vmtests      |  22 +
 29 files changed, 1054 insertions(+), 264 deletions(-)
 create mode 100644 Documentation/vm/pin_user_pages.rst
```
