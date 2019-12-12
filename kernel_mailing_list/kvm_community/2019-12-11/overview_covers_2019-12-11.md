

#### [PATCH v3 0/6] Use 1st-level for IOVA translation
##### From: Lu Baolu <baolu.lu@linux.intel.com>

```c
From patchwork Wed Dec 11 02:12:13 2019
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Lu Baolu <baolu.lu@linux.intel.com>
X-Patchwork-Id: 11283743
Return-Path: <SRS0=dbDR=2B=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id C21C1930
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 11 Dec 2019 02:13:19 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id A0AF2206EC
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 11 Dec 2019 02:13:19 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726739AbfLKCNP (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 10 Dec 2019 21:13:15 -0500
Received: from mga04.intel.com ([192.55.52.120]:52878 "EHLO mga04.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726062AbfLKCNP (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 10 Dec 2019 21:13:15 -0500
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from orsmga002.jf.intel.com ([10.7.209.21])
  by fmsmga104.fm.intel.com with ESMTP/TLS/DHE-RSA-AES256-GCM-SHA384;
 10 Dec 2019 18:13:15 -0800
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.69,301,1571727600";
   d="scan'208";a="225352973"
Received: from allen-box.sh.intel.com ([10.239.159.136])
  by orsmga002.jf.intel.com with ESMTP; 10 Dec 2019 18:13:12 -0800
From: Lu Baolu <baolu.lu@linux.intel.com>
To: Joerg Roedel <joro@8bytes.org>,
        David Woodhouse <dwmw2@infradead.org>,
        Alex Williamson <alex.williamson@redhat.com>
Cc: ashok.raj@intel.com, sanjay.k.kumar@intel.com,
        jacob.jun.pan@linux.intel.com, kevin.tian@intel.com,
        yi.l.liu@intel.com, yi.y.sun@intel.com,
        Peter Xu <peterx@redhat.com>, iommu@lists.linux-foundation.org,
        kvm@vger.kernel.org, linux-kernel@vger.kernel.org,
        Lu Baolu <baolu.lu@linux.intel.com>
Subject: [PATCH v3 0/6] Use 1st-level for IOVA translation
Date: Wed, 11 Dec 2019 10:12:13 +0800
Message-Id: <20191211021219.8997-1-baolu.lu@linux.intel.com>
X-Mailer: git-send-email 2.17.1
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Intel VT-d in scalable mode supports two types of page tables
for DMA translation: the first level page table and the second
level page table. The first level page table uses the same
format as the CPU page table, while the second level page table
keeps compatible with previous formats. The software is able
to choose any one of them for DMA remapping according to the use
case.

This patchset aims to move IOVA (I/O Virtual Address) translation
to 1st-level page table in scalable mode. This will simplify vIOMMU
(IOMMU simulated by VM hypervisor) design by using the two-stage
translation, a.k.a. nested mode translation.

As Intel VT-d architecture offers caching mode, guest IOVA (GIOVA)
support is currently implemented in a shadow page manner. The device
simulation software, like QEMU, has to figure out GIOVA->GPA mappings
and write them to a shadowed page table, which will be used by the
physical IOMMU. Each time when mappings are created or destroyed in
vIOMMU, the simulation software has to intervene. Hence, the changes
on GIOVA->GPA could be shadowed to host.


     .-----------.
     |  vIOMMU   |
     |-----------|                 .--------------------.
     |           |IOTLB flush trap |        QEMU        |
     .-----------. (map/unmap)     |--------------------|
     |GIOVA->GPA |---------------->|    .------------.  |
     '-----------'                 |    | GIOVA->HPA |  |
     |           |                 |    '------------'  |
     '-----------'                 |                    |
                                   |                    |
                                   '--------------------'
                                                |
            <------------------------------------
            |
            v VFIO/IOMMU API
      .-----------.
      |  pIOMMU   |
      |-----------|
      |           |
      .-----------.
      |GIOVA->HPA |
      '-----------'
      |           |
      '-----------'

In VT-d 3.0, scalable mode is introduced, which offers two-level
translation page tables and nested translation mode. Regards to
GIOVA support, it can be simplified by 1) moving the GIOVA support
over 1st-level page table to store GIOVA->GPA mapping in vIOMMU,
2) binding vIOMMU 1st level page table to the pIOMMU, 3) using pIOMMU
second level for GPA->HPA translation, and 4) enable nested (a.k.a.
dual-stage) translation in host. Compared with current shadow GIOVA
support, the new approach makes the vIOMMU design simpler and more
efficient as we only need to flush the pIOMMU IOTLB and possible
device-IOTLB when an IOVA mapping in vIOMMU is torn down.

     .-----------.
     |  vIOMMU   |
     |-----------|                 .-----------.
     |           |IOTLB flush trap |   QEMU    |
     .-----------.    (unmap)      |-----------|
     |GIOVA->GPA |---------------->|           |
     '-----------'                 '-----------'
     |           |                       |
     '-----------'                       |
           <------------------------------
           |      VFIO/IOMMU          
           |  cache invalidation and  
           | guest gpd bind interfaces
           v
     .-----------.
     |  pIOMMU   |
     |-----------|
     .-----------.
     |GIOVA->GPA |<---First level
     '-----------'
     | GPA->HPA  |<---Scond level
     '-----------'
     '-----------'

This patch applies the first level page table for IOVA translation
unless the DOMAIN_ATTR_NESTING domain attribution has been set.
Setting of this attribution means the second level will be used to
map gPA (guest physical address) to hPA (host physical address), and
the mappings between gVA (guest virtual address) and gPA will be
maintained by the guest with the page table address binding to host's
first level.

Based-on-idea-by: Ashok Raj <ashok.raj@intel.com>
Based-on-idea-by: Kevin Tian <kevin.tian@intel.com>
Based-on-idea-by: Liu Yi L <yi.l.liu@intel.com>
Based-on-idea-by: Jacob Pan <jacob.jun.pan@linux.intel.com>
Based-on-idea-by: Sanjay Kumar <sanjay.k.kumar@intel.com>
Based-on-idea-by: Lu Baolu <baolu.lu@linux.intel.com>

Change log:

v2->v3:
 - The previous version was posted here
   https://lkml.org/lkml/2019/11/27/1831
 - Accept Jacob's suggestion on merging two page tables.

 v1->v2
 - The first series was posted here
   https://lkml.org/lkml/2019/9/23/297
 - Use per domain page table ops to handle different page tables.
 - Use first level for DMA remapping by default on both bare metal
   and vm guest.
 - Code refine according to code review comments for v1.

Lu Baolu (6):
  iommu/vt-d: Identify domains using first level page table
  iommu/vt-d: Add set domain DOMAIN_ATTR_NESTING attr
  iommu/vt-d: Add PASID_FLAG_FL5LP for first-level pasid setup
  iommu/vt-d: Setup pasid entries for iova over first level
  iommu/vt-d: Flush PASID-based iotlb for iova over first level
  iommu/vt-d: Use iova over first level

 drivers/iommu/dmar.c        |  41 ++++++++
 drivers/iommu/intel-iommu.c | 185 ++++++++++++++++++++++++++++++++----
 drivers/iommu/intel-pasid.c |   7 +-
 drivers/iommu/intel-pasid.h |   6 ++
 drivers/iommu/intel-svm.c   |   8 +-
 include/linux/intel-iommu.h |  12 ++-
 6 files changed, 231 insertions(+), 28 deletions(-)
```
#### [PATCH v9 00/25] mm/gup: track dma-pinned pages: FOLL_PIN
##### From: John Hubbard <jhubbard@nvidia.com>

```c
From patchwork Wed Dec 11 02:52:53 2019
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: John Hubbard <jhubbard@nvidia.com>
X-Patchwork-Id: 11284197
Return-Path: <SRS0=dbDR=2B=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 44FAE15AB
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 11 Dec 2019 02:58:11 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 19D0D2173E
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 11 Dec 2019 02:58:11 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=nvidia.com header.i=@nvidia.com
 header.b="jvF78ikF"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727900AbfLKC6E (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 10 Dec 2019 21:58:04 -0500
Received: from hqnvemgate25.nvidia.com ([216.228.121.64]:2012 "EHLO
        hqnvemgate25.nvidia.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726974AbfLKCxZ (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 10 Dec 2019 21:53:25 -0500
Received: from hqpgpgate102.nvidia.com (Not Verified[216.228.121.13]) by
 hqnvemgate25.nvidia.com (using TLS: TLSv1.2, DES-CBC3-SHA)
        id <B5df05a1b0000>; Tue, 10 Dec 2019 18:53:15 -0800
Received: from hqmail.nvidia.com ([172.20.161.6])
  by hqpgpgate102.nvidia.com (PGP Universal service);
  Tue, 10 Dec 2019 18:53:22 -0800
X-PGP-Universal: processed;
        by hqpgpgate102.nvidia.com on Tue, 10 Dec 2019 18:53:22 -0800
Received: from HQMAIL105.nvidia.com (172.20.187.12) by HQMAIL105.nvidia.com
 (172.20.187.12) with Microsoft SMTP Server (TLS) id 15.0.1473.3; Wed, 11 Dec
 2019 02:53:21 +0000
Received: from rnnvemgw01.nvidia.com (10.128.109.123) by HQMAIL105.nvidia.com
 (172.20.187.12) with Microsoft SMTP Server (TLS) id 15.0.1473.3 via Frontend
 Transport; Wed, 11 Dec 2019 02:53:20 +0000
Received: from blueforge.nvidia.com (Not Verified[10.110.48.28]) by
 rnnvemgw01.nvidia.com with Trustwave SEG (v7,5,8,10121)
        id <B5df05a1f0001>; Tue, 10 Dec 2019 18:53:20 -0800
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
Subject: [PATCH v9 00/25] mm/gup: track dma-pinned pages: FOLL_PIN
Date: Tue, 10 Dec 2019 18:52:53 -0800
Message-ID: <20191211025318.457113-1-jhubbard@nvidia.com>
X-Mailer: git-send-email 2.24.0
MIME-Version: 1.0
X-NVConfidentiality: public
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=nvidia.com; s=n1;
        t=1576032796; bh=/WTOHnB7CdtD0f3PohhiCno24zNn42F7wC221pdIYa8=;
        h=X-PGP-Universal:From:To:CC:Subject:Date:Message-ID:X-Mailer:
         MIME-Version:X-NVConfidentiality:Content-Type:
         Content-Transfer-Encoding;
        b=jvF78ikFtZ+2LRb6zlzvhEFYdNllf3T6MCCl8UlevyvsbIciGEno8wF/kma4/WFif
         dQim8EanlpiHsyr9dogEGRSxTr7tYNQ+0HjzLSOGoD17EJ2t0C+8qAEVEKWuV/eN8p
         xNezGZi8gOvg08O1UKz4NNlfI5nTe9X8pTu+C8wzXyPqENZUQ/R5S8TZKutIiwrahw
         EeJKU8x8wI2WBWRbFGYJ4uhxKduqy3xOQqovjS2vHXgesmV7rdQ9CWb4p13vEioix2
         +ONu8pCLF5rf5eTew/56/JIMCv4YA+zc3jWOFdsnb8Bd8VQBJqWEZPj6ykYVbtCwyz
         oBuY0ZX4UHRVQ==
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Hi,

This implements an API naming change (put_user_page*() -->
unpin_user_page*()), and also implements tracking of FOLL_PIN pages. It
extends that tracking to a few select subsystems. More subsystems will
be added in follow up work.

Christoph Hellwig, a point of interest:

a) I've moved the bulk of the code out of the inline functions, as
   requested, for the devmap changes (patch 4: "mm: devmap: refactor
   1-based refcounting for ZONE_DEVICE pages").

Changes since v8:

* Merged the "mm/gup: pass flags arg to __gup_device_* functions" patch
  into the "mm/gup: track FOLL_PIN pages" patch, as requested by
  Christoph and Jan.

* Changed void grab_page() to bool try_grab_page(), and handled errors
  at the call sites. (From Jan's review comments.) try_grab_page()
  attempts to avoid page refcount overflows, even when counting up with
  GUP_PIN_COUNTING_BIAS increments.

* Fixed a bug that I'd introduced, when changing a BUG() to a WARN().

* Added Jan's reviewed-by tag to the " mm/gup: allow FOLL_FORCE for
  get_user_pages_fast()" patch.

* Documentation: pin_user_pages.rst: fixed an incorrect gup_benchmark
  invocation, left over from the pin_longterm days, spotted while preparing
  this version.

* Rebased onto today's linux.git (-rc1), and re-tested.

Changes since v7:

* Rebased onto Linux 5.5-rc1

* Reworked the grab_page() and try_grab_compound_head(), for API
  consistency and less diffs (thanks to Jan Kara's reviews).

* Added Leon Romanovsky's reviewed-by tags for two of the IB-related
  patches.

* patch 4 refactoring changes, as mentioned above.

There is a git repo and branch, for convenience:

    git@github.com:johnhubbard/linux.git pin_user_pages_tracking_v8

For the remaining list of "changes since version N", those are all in
v7, which is here:

  https://lore.kernel.org/r/20191121071354.456618-1-jhubbard@nvidia.com

============================================================
Overview:

This is a prerequisite to solving the problem of proper interactions
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
    unpin_user_page()

============================================================
Testing:

* I've done some overall kernel testing (LTP, and a few other goodies),
  and some directed testing to exercise some of the changes. And as you
  can see, gup_benchmark is enhanced to exercise this. Basically, I've
  been able to runtime test the core get_user_pages() and
  pin_user_pages() and related routines, but not so much on several of
  the call sites--but those are generally just a couple of lines
  changed, each.

  Not much of the kernel is actually using this, which on one hand
  reduces risk quite a lot. But on the other hand, testing coverage
  is low. So I'd love it if, in particular, the Infiniband and PowerPC
  folks could do a smoke test of this series for me.

  Runtime testing for the call sites so far is pretty light:

    * io_uring: Some directed tests from liburing exercise this, and
                they pass.
    * process_vm_access.c: A small directed test passes.
    * gup_benchmark: the enhanced version hits the new gup.c code, and
                     passes.
    * infiniband: ran "ib_write_bw", which exercises the umem.c changes,
                  but not the other changes.
    * VFIO: compiles (I'm vowing to set up a run time test soon, but it's
                      not ready just yet)
    * powerpc: it compiles...
    * drm/via: compiles...
    * goldfish: compiles...
    * net/xdp: compiles...
    * media/v4l2: compiles...

[1] Some slow progress on get_user_pages() (Apr 2, 2019): https://lwn.net/Articles/784574/
[2] DMA and get_user_pages() (LPC: Dec 12, 2018): https://lwn.net/Articles/774411/
[3] The trouble with get_user_pages() (Apr 30, 2018): https://lwn.net/Articles/753027/

Dan Williams (1):
  mm: Cleanup __put_devmap_managed_page() vs ->page_free()

John Hubbard (24):
  mm/gup: factor out duplicate code from four routines
  mm/gup: move try_get_compound_head() to top, fix minor issues
  mm: devmap: refactor 1-based refcounting for ZONE_DEVICE pages
  goldish_pipe: rename local pin_user_pages() routine
  mm: fix get_user_pages_remote()'s handling of FOLL_LONGTERM
  vfio: fix FOLL_LONGTERM use, simplify get_user_pages_remote() call
  mm/gup: allow FOLL_FORCE for get_user_pages_fast()
  IB/umem: use get_user_pages_fast() to pin DMA pages
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
  mm/gup: track FOLL_PIN pages
  mm/gup_benchmark: support pin_user_pages() and related calls
  selftests/vm: run_vmtests: invoke gup_benchmark with basic FOLL_PIN
    coverage

 Documentation/core-api/index.rst            |   1 +
 Documentation/core-api/pin_user_pages.rst   | 232 ++++++++
 arch/powerpc/mm/book3s64/iommu_api.c        |  10 +-
 drivers/gpu/drm/via/via_dmablit.c           |   6 +-
 drivers/infiniband/core/umem.c              |  19 +-
 drivers/infiniband/core/umem_odp.c          |  13 +-
 drivers/infiniband/hw/hfi1/user_pages.c     |   4 +-
 drivers/infiniband/hw/mthca/mthca_memfree.c |   8 +-
 drivers/infiniband/hw/qib/qib_user_pages.c  |   4 +-
 drivers/infiniband/hw/qib/qib_user_sdma.c   |   8 +-
 drivers/infiniband/hw/usnic/usnic_uiom.c    |   4 +-
 drivers/infiniband/sw/siw/siw_mem.c         |   4 +-
 drivers/media/v4l2-core/videobuf-dma-sg.c   |   8 +-
 drivers/nvdimm/pmem.c                       |   6 -
 drivers/platform/goldfish/goldfish_pipe.c   |  35 +-
 drivers/vfio/vfio_iommu_type1.c             |  35 +-
 fs/io_uring.c                               |   6 +-
 include/linux/mm.h                          | 149 ++++-
 include/linux/mmzone.h                      |   2 +
 include/linux/page_ref.h                    |  10 +
 mm/gup.c                                    | 598 +++++++++++++++-----
 mm/gup_benchmark.c                          |  74 ++-
 mm/huge_memory.c                            |  26 +-
 mm/hugetlb.c                                |  25 +-
 mm/memremap.c                               |  76 ++-
 mm/process_vm_access.c                      |  28 +-
 mm/swap.c                                   |  24 +
 mm/vmstat.c                                 |   2 +
 net/xdp/xdp_umem.c                          |   4 +-
 tools/testing/selftests/vm/gup_benchmark.c  |  21 +-
 tools/testing/selftests/vm/run_vmtests      |  22 +
 31 files changed, 1109 insertions(+), 355 deletions(-)
 create mode 100644 Documentation/core-api/pin_user_pages.rst
```
#### [PATCH 0/6] Fix various comment errors
##### From: linmiaohe <linmiaohe@huawei.com>
From: Miaohe Lin <linmiaohe@huawei.com>

```c
From patchwork Wed Dec 11 06:26:19 2019
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: linmiaohe <linmiaohe@huawei.com>
X-Patchwork-Id: 11284337
Return-Path: <SRS0=dbDR=2B=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id D10D21593
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 11 Dec 2019 06:26:49 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id B89A8222C4
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 11 Dec 2019 06:26:49 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727849AbfLKG0s (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 11 Dec 2019 01:26:48 -0500
Received: from szxga05-in.huawei.com ([45.249.212.191]:7215 "EHLO huawei.com"
        rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org with ESMTP
        id S1726676AbfLKG0s (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 11 Dec 2019 01:26:48 -0500
Received: from DGGEMS407-HUB.china.huawei.com (unknown [172.30.72.60])
        by Forcepoint Email with ESMTP id 52BEC7B47CD224B69C03;
        Wed, 11 Dec 2019 14:26:45 +0800 (CST)
Received: from huawei.com (10.175.105.18) by DGGEMS407-HUB.china.huawei.com
 (10.3.19.207) with Microsoft SMTP Server id 14.3.439.0; Wed, 11 Dec 2019
 14:26:38 +0800
From: linmiaohe <linmiaohe@huawei.com>
To: <pbonzini@redhat.com>, <rkrcmar@redhat.com>,
        <sean.j.christopherson@intel.com>, <vkuznets@redhat.com>,
        <wanpengli@tencent.com>, <jmattson@google.com>, <joro@8bytes.org>,
        <tglx@linutronix.de>, <mingo@redhat.com>, <bp@alien8.de>,
        <hpa@zytor.com>
CC: <linmiaohe@huawei.com>, <kvm@vger.kernel.org>,
        <linux-kernel@vger.kernel.org>, <x86@kernel.org>
Subject: [PATCH 0/6] Fix various comment errors
Date: Wed, 11 Dec 2019 14:26:19 +0800
Message-ID: <1576045585-8536-1-git-send-email-linmiaohe@huawei.com>
X-Mailer: git-send-email 1.8.3.1
MIME-Version: 1.0
X-Originating-IP: [10.175.105.18]
X-CFilter-Loop: Reflected
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Miaohe Lin <linmiaohe@huawei.com>

Fix various comment mistakes, such as typo, grammar mistake, out-dated
function name, writing error and so on. It is a bit tedious and many
thanks for review in advance.

Miaohe Lin (6):
  KVM: Fix some wrong function names in comment
  KVM: Fix some out-dated function names in comment
  KVM: Fix some comment typos and missing parentheses
  KVM: Fix some grammar mistakes
  KVM: hyperv: Fix some typos in vcpu unimpl info
  KVM: Fix some writing mistakes

 arch/x86/include/asm/kvm_host.h       | 2 +-
 arch/x86/kvm/hyperv.c                 | 6 +++---
 arch/x86/kvm/ioapic.c                 | 2 +-
 arch/x86/kvm/lapic.c                  | 4 ++--
 arch/x86/kvm/vmx/nested.c             | 2 +-
 arch/x86/kvm/vmx/vmcs_shadow_fields.h | 4 ++--
 arch/x86/kvm/vmx/vmx.c                | 8 ++++----
 virt/kvm/kvm_main.c                   | 6 +++---
 8 files changed, 17 insertions(+), 17 deletions(-)
```
#### [kvm-unit-tests PATCH 0/4] Improvements for the x86 tests
##### From: Thomas Huth <thuth@redhat.com>

```c
From patchwork Wed Dec 11 09:42:17 2019
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Thomas Huth <thuth@redhat.com>
X-Patchwork-Id: 11284585
Return-Path: <SRS0=dbDR=2B=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id A993B6C1
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 11 Dec 2019 09:42:30 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 87EAD214D8
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 11 Dec 2019 09:42:30 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="EY03U9PH"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728520AbfLKJm3 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 11 Dec 2019 04:42:29 -0500
Received: from us-smtp-2.mimecast.com ([207.211.31.81]:54718 "EHLO
        us-smtp-delivery-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S1728447AbfLKJm3 (ORCPT
        <rfc822;kvm@vger.kernel.org>); Wed, 11 Dec 2019 04:42:29 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1576057348;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:content-type:content-type:
         content-transfer-encoding:content-transfer-encoding;
        bh=yeeGoXVN9EsciEofZA0hvU6BC3U1cgy/S61t4Mc9KT4=;
        b=EY03U9PHL+4XaUa0PDlXCvbQQRONJcWopVRT/v7Lwo+T73QDoRq6CPZc0kjg+cum68vdB9
        Ignwj9zNr1/V/vGUJ/l9vxYVjZT/Ayw/tRaW0UqZdKX/yL166uXJW2GwB6ynWs0LLaGzgq
        2BuEWWpFGt6LKtTt8D8+DRSNY01jzXQ=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-229-3iJghz3zOa2j2L5H8YZ-TA-1; Wed, 11 Dec 2019 04:42:27 -0500
Received: from smtp.corp.redhat.com (int-mx05.intmail.prod.int.phx2.redhat.com
 [10.5.11.15])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 1BCBA107BA98
        for <kvm@vger.kernel.org>; Wed, 11 Dec 2019 09:42:26 +0000 (UTC)
Received: from thuth.com (ovpn-117-11.ams2.redhat.com [10.36.117.11])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 06CA16364A;
        Wed, 11 Dec 2019 09:42:24 +0000 (UTC)
From: Thomas Huth <thuth@redhat.com>
To: Paolo Bonzini <pbonzini@redhat.com>, kvm@vger.kernel.org
Cc: Drew Jones <drjones@redhat.com>
Subject: [kvm-unit-tests PATCH 0/4] Improvements for the x86 tests
Date: Wed, 11 Dec 2019 10:42:17 +0100
Message-Id: <20191211094221.7030-1-thuth@redhat.com>
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.15
X-MC-Unique: 3iJghz3zOa2j2L5H8YZ-TA-1
X-Mimecast-Spam-Score: 0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

QEMU recently changed the error message that it prints out when a
kernel could not be loaded, so we have to adjust our script in
kvm-unit-tests accordingly.
Once this is fixed, add two missing tests (setjmp and cmpxchg8b) to
the unittests.cfg and CI pipelines.

Thomas Huth (4):
  scripts: Fix premature_failure() check with newer versions of QEMU
  x86: Fix coding style in setjmp.c
  x86: Add the setjmp test to the CI
  x86: Add the cmpxchg8b test to the CI

 .gitlab-ci.yml       |  4 ++--
 .travis.yml          |  6 +++---
 scripts/runtime.bash |  2 +-
 x86/setjmp.c         | 22 ++++++++++------------
 x86/unittests.cfg    |  7 +++++++
 5 files changed, 23 insertions(+), 18 deletions(-)
```
#### [kvm-unit-tests PATCH 0/2] s390x: smp: Improve setup of additional
##### From: Janosch Frank <frankja@linux.ibm.com>

```c
From patchwork Wed Dec 11 11:59:21 2019
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Janosch Frank <frankja@linux.ibm.com>
X-Patchwork-Id: 11284791
Return-Path: <SRS0=dbDR=2B=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id ECCA26C1
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 11 Dec 2019 11:59:35 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id D5E7421556
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 11 Dec 2019 11:59:35 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729089AbfLKL7f (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 11 Dec 2019 06:59:35 -0500
Received: from mx0b-001b2d01.pphosted.com ([148.163.158.5]:50008 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S1727365AbfLKL7e (ORCPT
        <rfc822;kvm@vger.kernel.org>); Wed, 11 Dec 2019 06:59:34 -0500
Received: from pps.filterd (m0098417.ppops.net [127.0.0.1])
        by mx0a-001b2d01.pphosted.com (8.16.0.42/8.16.0.42) with SMTP id
 xBBBqIvS036381
        for <kvm@vger.kernel.org>; Wed, 11 Dec 2019 06:59:33 -0500
Received: from e06smtp05.uk.ibm.com (e06smtp05.uk.ibm.com [195.75.94.101])
        by mx0a-001b2d01.pphosted.com with ESMTP id 2wtf83ktbk-1
        (version=TLSv1.2 cipher=AES256-GCM-SHA384 bits=256 verify=NOT)
        for <kvm@vger.kernel.org>; Wed, 11 Dec 2019 06:59:33 -0500
Received: from localhost
        by e06smtp05.uk.ibm.com with IBM ESMTP SMTP Gateway: Authorized Use
 Only! Violators will be prosecuted
        for <kvm@vger.kernel.org> from <frankja@linux.ibm.com>;
        Wed, 11 Dec 2019 11:59:31 -0000
Received: from b06cxnps4074.portsmouth.uk.ibm.com (9.149.109.196)
        by e06smtp05.uk.ibm.com (192.168.101.135) with IBM ESMTP SMTP Gateway:
 Authorized Use Only! Violators will be prosecuted;
        (version=TLSv1/SSLv3 cipher=AES256-GCM-SHA384 bits=256/256)
        Wed, 11 Dec 2019 11:59:29 -0000
Received: from d06av24.portsmouth.uk.ibm.com (mk.ibm.com [9.149.105.60])
        by b06cxnps4074.portsmouth.uk.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id xBBBxT6K45023384
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Wed, 11 Dec 2019 11:59:29 GMT
Received: from d06av24.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id E305542042;
        Wed, 11 Dec 2019 11:59:28 +0000 (GMT)
Received: from d06av24.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 33B824203F;
        Wed, 11 Dec 2019 11:59:28 +0000 (GMT)
Received: from localhost.localdomain (unknown [9.152.224.149])
        by d06av24.portsmouth.uk.ibm.com (Postfix) with ESMTP;
        Wed, 11 Dec 2019 11:59:28 +0000 (GMT)
From: Janosch Frank <frankja@linux.ibm.com>
To: kvm@vger.kernel.org
Cc: thuth@redhat.com, david@redhat.com, linux-s390@vger.kernel.org
Subject: [kvm-unit-tests PATCH 0/2] s390x: smp: Improve setup of additional
 cpus
Date: Wed, 11 Dec 2019 06:59:21 -0500
X-Mailer: git-send-email 2.20.1
MIME-Version: 1.0
X-TM-AS-GCONF: 00
x-cbid: 19121111-0020-0000-0000-00000397205B
X-IBM-AV-DETECTION: SAVI=unused REMOTE=unused XFE=unused
x-cbparentid: 19121111-0021-0000-0000-000021EE242F
Message-Id: <20191211115923.9191-1-frankja@linux.ibm.com>
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.95,18.0.572
 definitions=2019-12-11_02:2019-12-11,2019-12-11 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 bulkscore=0 impostorscore=0
 spamscore=0 priorityscore=1501 suspectscore=1 mlxscore=0 adultscore=0
 clxscore=1015 lowpriorityscore=0 malwarescore=0 mlxlogscore=662
 phishscore=0 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.12.0-1910280000 definitions=main-1912110103
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Let's not use constants for the PSW mask and CRs, but set them from
input data or cpu 0.

Later on we could add functions that take a ptr for setting up CRs of
additional cpus, but for now using the CRs 0,1,7,13 from cpu 0 will at
least result in a working DAT environment.

Janosch Frank (2):
  s390x: smp: Use full PSW to bringup new cpu
  s390x: smp: Setup CRs from cpu 0

 lib/s390x/smp.c  | 7 ++++++-
 s390x/cstart64.S | 4 ++--
 2 files changed, 8 insertions(+), 3 deletions(-)
```
#### [kvm-unit-tests PATCH v4 0/9] s390x: Testing the Channel Subsystem
##### From: Pierre Morel <pmorel@linux.ibm.com>

```c
From patchwork Wed Dec 11 15:46:01 2019
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Pierre Morel <pmorel@linux.ibm.com>
X-Patchwork-Id: 11285511
Return-Path: <SRS0=dbDR=2B=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 86864109A
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 11 Dec 2019 15:46:37 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 6D2172073B
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 11 Dec 2019 15:46:37 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1732943AbfLKPqg (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 11 Dec 2019 10:46:36 -0500
Received: from mx0a-001b2d01.pphosted.com ([148.163.156.1]:9420 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1733214AbfLKPqS (ORCPT
        <rfc822;kvm@vger.kernel.org>); Wed, 11 Dec 2019 10:46:18 -0500
Received: from pps.filterd (m0098394.ppops.net [127.0.0.1])
        by mx0a-001b2d01.pphosted.com (8.16.0.42/8.16.0.42) with SMTP id
 xBBFhNIR119338
        for <kvm@vger.kernel.org>; Wed, 11 Dec 2019 10:46:17 -0500
Received: from e06smtp05.uk.ibm.com (e06smtp05.uk.ibm.com [195.75.94.101])
        by mx0a-001b2d01.pphosted.com with ESMTP id 2wsm2fqpcg-1
        (version=TLSv1.2 cipher=AES256-GCM-SHA384 bits=256 verify=NOT)
        for <kvm@vger.kernel.org>; Wed, 11 Dec 2019 10:46:17 -0500
Received: from localhost
        by e06smtp05.uk.ibm.com with IBM ESMTP SMTP Gateway: Authorized Use
 Only! Violators will be prosecuted
        for <kvm@vger.kernel.org> from <pmorel@linux.ibm.com>;
        Wed, 11 Dec 2019 15:46:15 -0000
Received: from b06cxnps3074.portsmouth.uk.ibm.com (9.149.109.194)
        by e06smtp05.uk.ibm.com (192.168.101.135) with IBM ESMTP SMTP Gateway:
 Authorized Use Only! Violators will be prosecuted;
        (version=TLSv1/SSLv3 cipher=AES256-GCM-SHA384 bits=256/256)
        Wed, 11 Dec 2019 15:46:11 -0000
Received: from d06av22.portsmouth.uk.ibm.com (d06av22.portsmouth.uk.ibm.com
 [9.149.105.58])
        by b06cxnps3074.portsmouth.uk.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id xBBFkBVG42336434
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Wed, 11 Dec 2019 15:46:11 GMT
Received: from d06av22.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 007DB4C059;
        Wed, 11 Dec 2019 15:46:10 +0000 (GMT)
Received: from d06av22.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id BB6CD4C058;
        Wed, 11 Dec 2019 15:46:10 +0000 (GMT)
Received: from oc3016276355.ibm.com (unknown [9.152.222.89])
        by d06av22.portsmouth.uk.ibm.com (Postfix) with ESMTP;
        Wed, 11 Dec 2019 15:46:10 +0000 (GMT)
From: Pierre Morel <pmorel@linux.ibm.com>
To: kvm@vger.kernel.org
Cc: linux-s390@vger.kernel.org, frankja@linux.ibm.com,
        david@redhat.com, thuth@redhat.com, cohuck@redhat.com
Subject: [kvm-unit-tests PATCH v4 0/9] s390x: Testing the Channel Subsystem
 I/O
Date: Wed, 11 Dec 2019 16:46:01 +0100
X-Mailer: git-send-email 1.8.3.1
X-TM-AS-GCONF: 00
x-cbid: 19121115-0020-0000-0000-000003973324
X-IBM-AV-DETECTION: SAVI=unused REMOTE=unused XFE=unused
x-cbparentid: 19121115-0021-0000-0000-000021EE381A
Message-Id: <1576079170-7244-1-git-send-email-pmorel@linux.ibm.com>
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.95,18.0.572
 definitions=2019-12-11_04:2019-12-11,2019-12-11 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 phishscore=0 mlxlogscore=912
 clxscore=1015 bulkscore=0 mlxscore=0 impostorscore=0 adultscore=0
 suspectscore=1 lowpriorityscore=0 priorityscore=1501 spamscore=0
 malwarescore=0 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.12.0-1910280000 definitions=main-1912110132
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Goal of the series is to have a framwork to test Channel-Subsystem I/O with
QEMU/KVM.
  
To be able to support interrupt for CSS I/O and for SCLP we need to modify
the interrupt framework to allow re-entrant interruptions.
  
We add a registration for IRQ callbacks to the test programm to define its own
interrupt handler. We need to do special work under interrupt like acknoledging
the interrupt.
  
Being working on PSW bits to allow I/O interrupt, we define new PSW bits
in arch_def.h and use __ASSEMBLER__ define to be able to include this header
in an assembler source file. 
 
This series presents four major tests:
- Enumeration:
        The CSS is enumerated using the STSCH instruction recursively on all
        potentially existing channels.
        Keeping the first channel found as a reference for future use.
        Checks STSCH
 
- Enable:
        If the enumeration succeeded the tests enables the reference
        channel with MSCH and verifies with STSCH that the channel is
        effectively enabled
        Checks MSCH 
 
- Sense:
        If the channel is enabled this test sends a SENSE_ID command
        to the reference channel, analysing the answer and expecting
        the Control unit type being 0xc0ca
        Checks SSCH(READ) and IO-IRQ

- ping-pong:
        If the reference channel leads to the PONG device (0xc0ca),
        the test exchanges a string containing a 9 digit number with
        the PONG device and expecting this number to be incremented
        by the PONG device.
        Checks SSCH(WRITE)


Pierre Morel (9):
  s390x: saving regs for interrupts
  s390x: Use PSW bits definitions in cstart
  s390x: interrupt registration
  s390x: export the clock get_clock_ms() utility
  s390x: Library resources for CSS tests
  s390x: css: stsch, enumeration test
  s390x: css: msch, enable test
  s390x: css: ssch/tsch with sense and interrupt
  s390x: css: ping pong

 lib/s390x/asm/arch_def.h |  16 +-
 lib/s390x/asm/time.h     |  26 +++
 lib/s390x/css.h          | 273 ++++++++++++++++++++++++++++
 lib/s390x/css_dump.c     | 157 ++++++++++++++++
 lib/s390x/interrupt.c    |  23 ++-
 lib/s390x/interrupt.h    |   7 +
 s390x/Makefile           |   2 +
 s390x/css.c              | 374 +++++++++++++++++++++++++++++++++++++++
 s390x/cstart64.S         |  40 ++++-
 s390x/intercept.c        |  11 +-
 s390x/unittests.cfg      |   4 +
 11 files changed, 909 insertions(+), 24 deletions(-)
 create mode 100644 lib/s390x/asm/time.h
 create mode 100644 lib/s390x/css.h
 create mode 100644 lib/s390x/css_dump.c
 create mode 100644 lib/s390x/interrupt.h
 create mode 100644 s390x/css.c
```
#### [PATCH 0/3] KVM: arm/arm64: user_mem_abort() assorted fixes
##### From: Marc Zyngier <maz@kernel.org>
X-SA-Exim-Mail-From: maz@kernel.org

```c
From patchwork Wed Dec 11 16:56:47 2019
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Marc Zyngier <maz@kernel.org>
X-Patchwork-Id: 11285741
Return-Path: <SRS0=dbDR=2B=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id A895A15AB
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 11 Dec 2019 16:57:10 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 7DA052464B
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 11 Dec 2019 16:57:10 +0000 (UTC)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple; d=kernel.org;
	s=default; t=1576083430;
	bh=oJarIOt6t8dqOaeavUDWnTVs/9uhcPVOmAtL+ftiFO0=;
	h=From:To:Cc:Subject:Date:List-ID:From;
	b=z3T4QTeW2PJnjjps26FIKXNAWwg100925mm+b4qLzDtTqI83xIb2wiGbSOMv6a/2B
	 K5HEeSyH1ALaBctg0UA4lBKGF6PhSd0UDfoGf6dKYuz5eMt9e2CYyFq66r8NMhgcwu
	 5z4NTICvAn4Z6rllpY6E4H9b9t6qifiodPqYLZD0=
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1730315AbfLKQ5I (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 11 Dec 2019 11:57:08 -0500
Received: from inca-roads.misterjones.org ([213.251.177.50]:58772 "EHLO
        inca-roads.misterjones.org" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1730107AbfLKQ5H (ORCPT
        <rfc822;kvm@vger.kernel.org>); Wed, 11 Dec 2019 11:57:07 -0500
Received: from 78.163-31-62.static.virginmediabusiness.co.uk ([62.31.163.78]
 helo=why.lan)
        by cheepnis.misterjones.org with esmtpsa
 (TLSv1.2:DHE-RSA-AES128-GCM-SHA256:128)
        (Exim 4.80)
        (envelope-from <maz@kernel.org>)
        id 1if5IN-00076q-Pr; Wed, 11 Dec 2019 17:57:04 +0100
From: Marc Zyngier <maz@kernel.org>
To: kvm@vger.kernel.org, kvmarm@lists.cs.columbia.edu,
        linux-arm-kernel@lists.infradead.org
Cc: James Morse <james.morse@arm.com>,
        Julien Thierry <julien.thierry.kdev@gmail.com>,
        Suzuki K Poulose <suzuki.poulose@arm.com>,
        Christoffer Dall <Christoffer.Dall@arm.com>,
        Alexandru Elisei <alexandru.elisei@arm.com>
Subject: [PATCH 0/3] KVM: arm/arm64: user_mem_abort() assorted fixes
Date: Wed, 11 Dec 2019 16:56:47 +0000
Message-Id: <20191211165651.7889-1-maz@kernel.org>
X-Mailer: git-send-email 2.20.1
MIME-Version: 1.0
X-SA-Exim-Connect-IP: 62.31.163.78
X-SA-Exim-Rcpt-To: kvm@vger.kernel.org, kvmarm@lists.cs.columbia.edu,
 linux-arm-kernel@lists.infradead.org, james.morse@arm.com,
 julien.thierry.kdev@gmail.com, suzuki.poulose@arm.com,
 Christoffer.Dall@arm.com, alexandru.elisei@arm.com
X-SA-Exim-Mail-From: maz@kernel.org
X-SA-Exim-Scanned: No (on cheepnis.misterjones.org);
 SAEximRunCond expanded to false
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Alexandru recently reported an interesting issue with our handling
of device mapping in user_mem_abort(), which is sligtly less than
correct. The first patch of the series address this issue, and
is a stable candidate.

While I was looking at this code, I spotted what I think is a potential
issue when handling a poisoned page, where we can race with a VMA
being removed. This second patch is mostly a RFC, as this is not
my area of expertise.

Finally, the last patch is a cleanup removing an unnecessary console
output.

Marc Zyngier (3):
  KVM: arm/arm64: Properly handle faulting of device mappings
  KVM: arm/arm64: Re-check VMA on detecting a poisoned page
  KVM: arm/arm64: Drop spurious message when faulting on a non-existent
    mapping

 virt/kvm/arm/mmu.c | 47 +++++++++++++++++++++++++++++++++++++++-------
 1 file changed, 40 insertions(+), 7 deletions(-)
```
#### [PATCH 0/2] KVM: x86: X86_FEATURE bit() cleanup
##### From: Sean Christopherson <sean.j.christopherson@intel.com>

```c
From patchwork Wed Dec 11 17:58:20 2019
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Sean Christopherson <sean.j.christopherson@intel.com>
X-Patchwork-Id: 11285897
Return-Path: <SRS0=dbDR=2B=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 9C734112B
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 11 Dec 2019 17:58:31 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 84C1B24653
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 11 Dec 2019 17:58:31 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729228AbfLKR6Y (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 11 Dec 2019 12:58:24 -0500
Received: from mga02.intel.com ([134.134.136.20]:29189 "EHLO mga02.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1730880AbfLKR6X (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 11 Dec 2019 12:58:23 -0500
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from orsmga007.jf.intel.com ([10.7.209.58])
  by orsmga101.jf.intel.com with ESMTP/TLS/DHE-RSA-AES256-GCM-SHA384;
 11 Dec 2019 09:58:22 -0800
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.69,302,1571727600";
   d="scan'208";a="203645149"
Received: from sjchrist-coffee.jf.intel.com ([10.54.74.202])
  by orsmga007.jf.intel.com with ESMTP; 11 Dec 2019 09:58:22 -0800
From: Sean Christopherson <sean.j.christopherson@intel.com>
To: Paolo Bonzini <pbonzini@redhat.com>
Cc: Sean Christopherson <sean.j.christopherson@intel.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org
Subject: [PATCH 0/2] KVM: x86: X86_FEATURE bit() cleanup
Date: Wed, 11 Dec 2019 09:58:20 -0800
Message-Id: <20191211175822.1925-1-sean.j.christopherson@intel.com>
X-Mailer: git-send-email 2.24.0
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Small series to add build-time protections on reverse CPUID lookup (and
other usages of bit()), and to rename the misleading-generic bit() helper
to something that better conveys its purpose.

Sean Christopherson (2):
  KVM: x86: Add build-time assertion on usage of bit()
  KVM: x86: Refactor and rename bit() to feature_bit() macro

 arch/x86/kvm/cpuid.c   |  2 +-
 arch/x86/kvm/cpuid.h   |  4 ++--
 arch/x86/kvm/emulate.c |  8 +++-----
 arch/x86/kvm/svm.c     |  4 ++--
 arch/x86/kvm/vmx/vmx.c | 42 +++++++++++++++++++++---------------------
 arch/x86/kvm/x86.h     | 24 ++++++++++++++++++++++--
 6 files changed, 51 insertions(+), 33 deletions(-)
```
#### [PATCH v2 00/13] KVM: x86: Extend Spectre-v1 mitigation
##### From: Marios Pomonis <pomonis@google.com>
From: Nick Finco <nifi@google.com>

```c
From patchwork Wed Dec 11 20:47:40 2019
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Marios Pomonis <pomonis@google.com>
X-Patchwork-Id: 11286343
Return-Path: <SRS0=dbDR=2B=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 0C47B112B
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 11 Dec 2019 20:48:20 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id E15F0222C4
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 11 Dec 2019 20:48:19 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=google.com header.i=@google.com
 header.b="QOXWFSPQ"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726771AbfLKUsT (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 11 Dec 2019 15:48:19 -0500
Received: from mail-pg1-f201.google.com ([209.85.215.201]:36387 "EHLO
        mail-pg1-f201.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726620AbfLKUsS (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 11 Dec 2019 15:48:18 -0500
Received: by mail-pg1-f201.google.com with SMTP id i8so50418pgs.3
        for <kvm@vger.kernel.org>; Wed, 11 Dec 2019 12:48:18 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=date:message-id:mime-version:subject:from:to:cc;
        bh=2gC640IyhH5dA8WbV5f5/xeewX2HczJxP4vBYhavCEY=;
        b=QOXWFSPQYjnuJDMP0a4El8Kh5ujIbG0XtwVP1iVHds8uiUZsbjpHgG5WPdWl96GsCo
         q7mpMlt3B9pzVIYZHTKFtDCCu4Cvr0XBTzrrkwca0VvGL/x98Agf/uml2HXIsWn03J/l
         WoO+n1BkNjMXj+5AkWjhI5FAQqE+nZbr7cOSbOohyp/aWnmAVnsqkkfHpvoi7r8vgBUH
         sH301tcL19NGm1CgMJX76L3AFHahIWAjDQj43FZ32PTFZktgX/o2GS8BxEahhUYaBGVK
         7rzzv81Tk+0hZarU6nZi777LGxgGHFMLeu7JUR5JgFrTckNSQF4iBL6hi9nBElJsQ6iE
         /HjA==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:date:message-id:mime-version:subject:from:to:cc;
        bh=2gC640IyhH5dA8WbV5f5/xeewX2HczJxP4vBYhavCEY=;
        b=H0iPTO1el2I/PeWu6K2xHuawx/neyPaT3OVtcaXawvIb22WHy4x7wEhEbrNghu4zKM
         vPH56zIFP3NcsMP19vtUkocTk4zqxXLAxRZZUVusgxV2FPLInwpF38UJFew0+hZwhnXc
         qlxuTQ5oBATqjGQ450ogBqRXg7cBDOTYFlbL9FAAlfYgH+3SWdQQzZ1in/WpyEf1FLVf
         /4qMZa8Di46D4+G7Exd/rUhkQ+XsgMjn+iknvyRHxb8QgfJ5E3RrzqGIpP0LKARohNSp
         LSm527TaV96fBjLvoJADr/HgNiuWh2icPTEJgljFvkpodjDUBKG+jRpCsgyUwGGcXOOm
         Ksrg==
X-Gm-Message-State: APjAAAVnoM/4YD0C5LQPUujpYieLdMhKhdlQPux9NDapMYSq5xk/Sxgy
        nWnk7AtDEtrPc+YEnqvLgXkmMJZgiA5U
X-Google-Smtp-Source: 
 APXvYqwOL7uivEwokJX5aYM9537r8vrIEKgGR7nmvHWO9lF7B4kYZsHBsBQwsuUkGzh4uQRzcSr4YlBVlX8t
X-Received: by 2002:a63:c804:: with SMTP id z4mr6386725pgg.440.1576097297767;
 Wed, 11 Dec 2019 12:48:17 -0800 (PST)
Date: Wed, 11 Dec 2019 12:47:40 -0800
Message-Id: <20191211204753.242298-1-pomonis@google.com>
Mime-Version: 1.0
X-Mailer: git-send-email 2.24.0.525.g8f36a354ae-goog
Subject: [PATCH v2 00/13] KVM: x86: Extend Spectre-v1 mitigation
From: Marios Pomonis <pomonis@google.com>
To: Paolo Bonzini <pbonzini@redhat.com>, rkrcmar@redhat.com,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>
Cc: Thomas Gleixner <tglx@linutronix.de>,
        Ingo Molnar <mingo@redhat.com>, Borislav Petkov <bp@alien8.de>,
        "H. Peter Anvin" <hpa@zytor.com>, x86@kernel.org,
        kvm@vger.kernel.org, linux-kernel@vger.kernel.org,
        Nick Finco <nifi@google.com>, Andrew Honig <ahonig@google.com>,
        Marios Pomonis <pomonis@google.com>
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Nick Finco <nifi@google.com>

This extends the Spectre-v1 mitigation introduced in
commit 75f139aaf896 ("KVM: x86: Add memory barrier on vmcs field lookup")
and commit 085331dfc6bb ("x86/kvm: Update spectre-v1 mitigation") in light
of the Spectre-v1/L1TF combination described here:
https://xenbits.xen.org/xsa/advisory-289.html

As reported in the link, an attacker can use the cache-load part of a
Spectre-v1 gadget to bring memory into the L1 cache, then use L1TF to
leak the loaded memory. Note that this attack is not fully mitigated by
core scheduling; firstly when "kvm-intel.vmentry_l1d_flush" is not set
to "always", an attacker could use L1TF on the same thread that loaded the
memory values in the cache on paths that do not flush the L1 cache on
VMEntry. Otherwise, an attacker could perform this attack using a
collusion of two sibling hyperthreads: one that loads memory values in
the cache during VMExit handling and another that performs L1TF to leak
them.

This patch uses array_index_nospec() to prevent index computations from
causing speculative loads into the L1 cache. These cases involve a
bounds check followed by a memory read using the index; this is more
common than the full Spectre-v1 pattern. In some cases, the index
computation can be eliminated entirely by small amounts of refactoring.

Marios Pomonis (13):
  KVM: x86: Protect x86_decode_insn from Spectre-v1/L1TF attacks
  KVM: x86: Protect kvm_hv_msr_[get|set]_crash_data() from
    Spectre-v1/L1TF attacks
  KVM: x86: Refactor picdev_write() to prevent Spectre-v1/L1TF attacks
  KVM: x86: Protect ioapic_read_indirect() from Spectre-v1/L1TF attacks
  KVM: x86: Protect ioapic_write_indirect() from Spectre-v1/L1TF attacks
  KVM: x86: Protect kvm_lapic_reg_write() from Spectre-v1/L1TF attacks
  KVM: x86: Protect MSR-based index computations in
    fixed_msr_to_seg_unit()
  KVM: x86: Protect MSR-based index computations in pmu.h
  KVM: x86: Protect MSR-based index computations from Spectre-v1/L1TF
    attacks in x86.c
  KVM: x86: Protect memory accesses from Spectre-v1/L1TF attacks in
    x86.c
  KVM: x86: Protect exit_reason from being used in Spectre-v1/L1TF
    attacks
  KVM: x86: Protect DR-based index computations from Spectre-v1/L1TF
    attacks
  KVM: x86: Protect pmu_intel.c from Spectre-v1/L1TF attacks

 arch/x86/kvm/emulate.c       | 11 ++++--
 arch/x86/kvm/hyperv.c        | 10 +++--
 arch/x86/kvm/i8259.c         |  6 ++-
 arch/x86/kvm/ioapic.c        | 15 +++++---
 arch/x86/kvm/lapic.c         | 13 +++++--
 arch/x86/kvm/mtrr.c          |  8 +++-
 arch/x86/kvm/pmu.h           | 18 +++++++--
 arch/x86/kvm/vmx/pmu_intel.c | 24 ++++++++----
 arch/x86/kvm/vmx/vmx.c       | 71 +++++++++++++++++++++---------------
 arch/x86/kvm/x86.c           | 18 +++++++--
 10 files changed, 129 insertions(+), 65 deletions(-)
```
#### [PATCH v4 0/2] kvm: Use huge pages for DAX-backed files
##### From: Barret Rhoden <brho@google.com>

```c
From patchwork Wed Dec 11 21:32:05 2019
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Barret Rhoden <brho@google.com>
X-Patchwork-Id: 11286479
Return-Path: <SRS0=dbDR=2B=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 73B3013B6
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 11 Dec 2019 21:32:33 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 52DC42054F
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 11 Dec 2019 21:32:33 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=google.com header.i=@google.com
 header.b="SkYtkuEt"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726676AbfLKVcV (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 11 Dec 2019 16:32:21 -0500
Received: from mail-pg1-f201.google.com ([209.85.215.201]:43469 "EHLO
        mail-pg1-f201.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726620AbfLKVcU (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 11 Dec 2019 16:32:20 -0500
Received: by mail-pg1-f201.google.com with SMTP id d9so106916pgd.10
        for <kvm@vger.kernel.org>; Wed, 11 Dec 2019 13:32:20 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=date:message-id:mime-version:subject:from:to:cc;
        bh=yOD0iLUDW76bcZvomrsQRH0nGqn37n8IrqSYFpzYwxo=;
        b=SkYtkuEt3uhSk0GqlAk4oucYFWLKir9gozR06v9/suCWs/JVSDqytCQWQ9LgaAQ2na
         PmOF+bMFyZX6yDg3n+Y3lq9ka6vzus1Yx1drthis6lI3K3+dNDjwq8TzRTCIy1BhVIIE
         8YyFCJU6quwTTAiMFY22MftPutzvhLyK65b5i18KFpIC0t8RK3OHJqcX/1Q1U0dLdMk+
         b/qD97l+2JOZReqFN252Il/j1KHxrLlQRWYJ7YefFfcWqCeAnQlW2oxdi/bAsI+HS93n
         o7eHSkSdR5VZMpEmI6I80LN1+CMxsTLZDVS0IUoIUejO9uJ/AKOE54dkjVuXyEUIAhas
         tn0Q==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:date:message-id:mime-version:subject:from:to:cc;
        bh=yOD0iLUDW76bcZvomrsQRH0nGqn37n8IrqSYFpzYwxo=;
        b=rqTUurcFGSDbY1tcP3tuX+ZNSuNTAe2IHuIBHCq5jkjsannL3U+cKAR7LliD7KLhWv
         McJbLfhKEdn1d7LhyFB4JJNR6hVVkPyPDZLCn2eDk4Y/6kYFAVEXyMQYXl3m+eEGza0P
         maujSdSxBVEE/qZe6G8dE4fgGsTA3e4S5PjmKVTrwSVCSjwNNMgNOx02l0KrgHOvB1m5
         PrGomvBUmtqlR12BZz5qoo91LMVSRVNODscBm+ybS1zgX+lYHMVDplTgjRahbopkOWCY
         QiY9I1v5w//bkVZp0OBWrA10yZRfXdC5gk0uQPoCtdRUw9HwGgnMp+q1X3AzE/e6JHa6
         iRSw==
X-Gm-Message-State: APjAAAUn2+ng8z3sG3AvkSO0KHz0TSuIonWXhvhIaDfssymOXDQu2xFq
        gUFR3LSHmBV551as6KZIEhEb+DHD
X-Google-Smtp-Source: 
 APXvYqwxN+9vk9zS22b7QST6+pxb5MgdnMTh4p7n/rktgqkeQdSuCaW1zb//I1NE9J50Us45XT1y4SFl
X-Received: by 2002:a63:ec0a:: with SMTP id j10mr6589163pgh.178.1576099940106;
 Wed, 11 Dec 2019 13:32:20 -0800 (PST)
Date: Wed, 11 Dec 2019 16:32:05 -0500
Message-Id: <20191211213207.215936-1-brho@google.com>
Mime-Version: 1.0
X-Mailer: git-send-email 2.24.0.525.g8f36a354ae-goog
Subject: [PATCH v4 0/2] kvm: Use huge pages for DAX-backed files
From: Barret Rhoden <brho@google.com>
To: Paolo Bonzini <pbonzini@redhat.com>,
        Dan Williams <dan.j.williams@intel.com>,
        David Hildenbrand <david@redhat.com>,
        Dave Jiang <dave.jiang@intel.com>,
        Alexander Duyck <alexander.h.duyck@linux.intel.com>
Cc: linux-nvdimm@lists.01.org, x86@kernel.org, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org, jason.zeng@intel.com
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This patchset allows KVM to map huge pages for DAX-backed files.

I held previous versions in limbo while people were sorting out whether
or not DAX pages were going to remain PageReserved and how that relates
to KVM.

Now that that is sorted out (DAX pages are PageReserved, but they are
not kvm_is_reserved_pfn(), and DAX pages are considered on a
case-by-case basis for KVM), I can repost this.

v3 -> v4:
v3: https://lore.kernel.org/lkml/20190404202345.133553-1-brho@google.com/
- Rebased onto linus/master

v2 -> v3:
v2: https://lore.kernel.org/lkml/20181114215155.259978-1-brho@google.com/
- Updated Acks/Reviewed-by
- Rebased onto linux-next

v1 -> v2:
https://lore.kernel.org/lkml/20181109203921.178363-1-brho@google.com/
- Updated Acks/Reviewed-by
- Minor touchups
- Added patch to remove redundant PageReserved() check
- Rebased onto linux-next

RFC/discussion thread:
https://lore.kernel.org/lkml/20181029210716.212159-1-brho@google.com/

Barret Rhoden (2):
  mm: make dev_pagemap_mapping_shift() externally visible
  kvm: Use huge pages for DAX-backed files

 arch/x86/kvm/mmu/mmu.c | 36 ++++++++++++++++++++++++++++++++----
 include/linux/mm.h     |  3 +++
 mm/memory-failure.c    | 38 +++-----------------------------------
 mm/util.c              | 34 ++++++++++++++++++++++++++++++++++
 4 files changed, 72 insertions(+), 39 deletions(-)
```
