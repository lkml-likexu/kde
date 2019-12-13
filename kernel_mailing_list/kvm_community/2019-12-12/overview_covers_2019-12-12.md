

#### [PATCH 0/3] Standardize kvm exit reason field
##### From: Gavin Shan <gshan@redhat.com>

```c
From patchwork Thu Dec 12 02:45:09 2019
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Gavin Shan <gshan@redhat.com>
X-Patchwork-Id: 11286799
Return-Path: <SRS0=BLLP=2C=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 67760138C
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 12 Dec 2019 02:45:27 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 4453020836
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 12 Dec 2019 02:45:27 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="dx/UAx65"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727877AbfLLCp0 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 11 Dec 2019 21:45:26 -0500
Received: from us-smtp-1.mimecast.com ([207.211.31.81]:30812 "EHLO
        us-smtp-delivery-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S1727705AbfLLCp0 (ORCPT
        <rfc822;kvm@vger.kernel.org>); Wed, 11 Dec 2019 21:45:26 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1576118725;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=kn1ymEsIwqFhOaQmJJrBrdgBfZaZLt84rJ0YsSsfEE0=;
        b=dx/UAx652RMxAdp5Py9rL9mQ4ohV7rB/ivMhZGnRn8y42gL6ifAwLoOlIXAHVHk8p5CYr2
        sdnbIZiCF3bDxzu9IlFFH1XvMN8niPAHZA8FIqlmOpvacyWCQPifKj72iwfbMZ292b6Oq5
        IPfnfvN2IOrAkTSugIyNgy4h+ey3vDU=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-207-m7tiwnYoMNWSXDhCrk-rfw-1; Wed, 11 Dec 2019 21:45:24 -0500
X-MC-Unique: m7tiwnYoMNWSXDhCrk-rfw-1
Received: from smtp.corp.redhat.com (int-mx03.intmail.prod.int.phx2.redhat.com
 [10.5.11.13])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id F1F2E1800D63;
        Thu, 12 Dec 2019 02:45:22 +0000 (UTC)
Received: from localhost.localdomain.com (vpn2-54-40.bne.redhat.com
 [10.64.54.40])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 589426609A;
        Thu, 12 Dec 2019 02:45:17 +0000 (UTC)
From: Gavin Shan <gshan@redhat.com>
To: kvm@vger.kernel.org
Cc: pbonzini@redhat.com, rkrcmar@redhat.com, paulus@ozlabs.org,
        maz@kernel.org, jhogan@kernel.org, drjones@redhat.com,
        vkuznets@redhat.com, gshan@redhat.com
Subject: [PATCH 0/3] Standardize kvm exit reason field
Date: Thu, 12 Dec 2019 13:45:09 +1100
Message-Id: <20191212024512.39930-1-gshan@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.13
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Some utilities (e.g. kvm_stat) have the assumption that same filter
field "exit_reason" for kvm exit tracepoint. However, they're varied
on different architects. It can be fixed for the utilities to pick
different filter names, or standardize it to have unified name "exit_reason",
The series takes the second approach, suggested by Vitaly Kuznetsov.

I'm not sure which git tree this will go, so I have one separate patch
for each architect in case they are merged to different git tree.

Gavin Shan (3):
  kvm/mips: Standardize kvm exit reason field
  kvm/powerpc: Standardize kvm exit reason field
  kvm/aarch64: Standardize kvm exit reason field

 arch/mips/kvm/trace.h          | 10 +++++-----
 arch/powerpc/kvm/trace_booke.h | 10 +++++-----
 arch/powerpc/kvm/trace_pr.h    | 10 +++++-----
 virt/kvm/arm/trace.h           | 14 ++++++++------
 4 files changed, 23 insertions(+), 21 deletions(-)
```
#### [PATCH v10 00/25] mm/gup: track dma-pinned pages: FOLL_PIN
##### From: John Hubbard <jhubbard@nvidia.com>

```c
From patchwork Thu Dec 12 08:18:52 2019
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: John Hubbard <jhubbard@nvidia.com>
X-Patchwork-Id: 11287577
Return-Path: <SRS0=BLLP=2C=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 0257214B7
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 12 Dec 2019 08:24:04 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id C1464214D8
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 12 Dec 2019 08:24:03 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=nvidia.com header.i=@nvidia.com
 header.b="Y1R8hx3F"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728494AbfLLIYC (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 12 Dec 2019 03:24:02 -0500
Received: from hqnvemgate26.nvidia.com ([216.228.121.65]:3743 "EHLO
        hqnvemgate26.nvidia.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1728277AbfLLITU (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 12 Dec 2019 03:19:20 -0500
Received: from hqpgpgate102.nvidia.com (Not Verified[216.228.121.13]) by
 hqnvemgate26.nvidia.com (using TLS: TLSv1.2, DES-CBC3-SHA)
        id <B5df1f8000000>; Thu, 12 Dec 2019 00:19:12 -0800
Received: from hqmail.nvidia.com ([172.20.161.6])
  by hqpgpgate102.nvidia.com (PGP Universal service);
  Thu, 12 Dec 2019 00:19:19 -0800
X-PGP-Universal: processed;
        by hqpgpgate102.nvidia.com on Thu, 12 Dec 2019 00:19:19 -0800
Received: from HQMAIL105.nvidia.com (172.20.187.12) by HQMAIL101.nvidia.com
 (172.20.187.10) with Microsoft SMTP Server (TLS) id 15.0.1473.3; Thu, 12 Dec
 2019 08:19:18 +0000
Received: from hqnvemgw03.nvidia.com (10.124.88.68) by HQMAIL105.nvidia.com
 (172.20.187.12) with Microsoft SMTP Server (TLS) id 15.0.1473.3 via Frontend
 Transport; Thu, 12 Dec 2019 08:19:18 +0000
Received: from blueforge.nvidia.com (Not Verified[10.110.48.28]) by
 hqnvemgw03.nvidia.com with Trustwave SEG (v7,5,8,10121)
        id <B5df1f8060001>; Thu, 12 Dec 2019 00:19:18 -0800
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
Subject: [PATCH v10 00/25] mm/gup: track dma-pinned pages: FOLL_PIN
Date: Thu, 12 Dec 2019 00:18:52 -0800
Message-ID: <20191212081917.1264184-1-jhubbard@nvidia.com>
X-Mailer: git-send-email 2.24.0
MIME-Version: 1.0
X-NVConfidentiality: public
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=nvidia.com; s=n1;
        t=1576138752; bh=bbdNKbiq94zgFtAlPv1Fpk31g13QpEp24wIKMs3yr3M=;
        h=X-PGP-Universal:From:To:CC:Subject:Date:Message-ID:X-Mailer:
         MIME-Version:X-NVConfidentiality:Content-Type:
         Content-Transfer-Encoding;
        b=Y1R8hx3FJWSb27HdAzsGJjJpdnlEtl1cb0ueAaiH6SOlIouZsspbxG7ArktDIqiEr
         Br0EA4SeZmk76k65lxU0XhwiWOtj39vrLCz4Tk7KvbtAtjD6iKS78EbI/P/aRk0Wcr
         F/505JbjvlrSy16GkzIZZcghWqjJ1ItMfatoTwmulgZq0atyZONIj/xXnwzzMugmHa
         nsQ7SqaBF65k9d2TO2nv5PlfSBembIzQD/Bzvsz3gcdWMjcDVLL9MYa1oWREYAh+tm
         o5bm2AGo8Vr2PApUjLjMUQKW9TrOf/kOuUrWp+S2/FsL5AGIsQqr1L26fBA8N9ByKF
         lJHt+dnOK5rEw==
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

Changes since v9: Fixes resulting from Jan Kara's and Jonathan Corbet's
reviews:

* Removed reviewed-by tags from the "mm/gup: track FOLL_PIN pages" (those
  were improperly inherited from the much smaller refactoring patch that
  was merged into it).

* Made try_grab_compound_head() and try_grab_page() behavior similar in
  their behavior with flags, in order to avoid "gotchas" later.

* follow_trans_huge_pmd(): moved the try_grab_page() to earlier in the
  routine, in order to avoid having to undo mlock_vma_page().

* follow_hugetlb_page(): removed a refcount overflow check that is now
  extraneous (and weaker than what try_grab_page() provides a few lines
  further down).

* Fixed up two Documentation flaws, pointed out by Jonathan Corbet's
  review.

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
 mm/gup.c                                    | 626 +++++++++++++++-----
 mm/gup_benchmark.c                          |  74 ++-
 mm/huge_memory.c                            |  45 +-
 mm/hugetlb.c                                |  38 +-
 mm/memremap.c                               |  76 ++-
 mm/process_vm_access.c                      |  28 +-
 mm/swap.c                                   |  24 +
 mm/vmstat.c                                 |   2 +
 net/xdp/xdp_umem.c                          |   4 +-
 tools/testing/selftests/vm/gup_benchmark.c  |  21 +-
 tools/testing/selftests/vm/run_vmtests      |  22 +
 31 files changed, 1147 insertions(+), 377 deletions(-)
 create mode 100644 Documentation/core-api/pin_user_pages.rst
---
2.24.0
```
#### [PATCH v2 0/4] Fix various comment errors
##### From: linmiaohe <linmiaohe@huawei.com>
From: Miaohe Lin <linmiaohe@huawei.com>

```c
From patchwork Thu Dec 12 08:18:34 2019
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: linmiaohe <linmiaohe@huawei.com>
X-Patchwork-Id: 11287589
Return-Path: <SRS0=BLLP=2C=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 103CC14B7
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 12 Dec 2019 08:24:18 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id E51432173E
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 12 Dec 2019 08:24:17 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728271AbfLLITS (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 12 Dec 2019 03:19:18 -0500
Received: from szxga06-in.huawei.com ([45.249.212.32]:45294 "EHLO huawei.com"
        rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org with ESMTP
        id S1728209AbfLLITQ (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 12 Dec 2019 03:19:16 -0500
Received: from DGGEMS407-HUB.china.huawei.com (unknown [172.30.72.59])
        by Forcepoint Email with ESMTP id 3646C3A88C12610B275B;
        Thu, 12 Dec 2019 16:19:12 +0800 (CST)
Received: from huawei.com (10.175.105.18) by DGGEMS407-HUB.china.huawei.com
 (10.3.19.207) with Microsoft SMTP Server id 14.3.439.0; Thu, 12 Dec 2019
 16:19:02 +0800
From: linmiaohe <linmiaohe@huawei.com>
To: <pbonzini@redhat.com>, <rkrcmar@redhat.com>,
        <sean.j.christopherson@intel.com>, <vkuznets@redhat.com>,
        <wanpengli@tencent.com>, <jmattson@google.com>, <joro@8bytes.org>,
        <tglx@linutronix.de>, <mingo@redhat.com>, <bp@alien8.de>,
        <hpa@zytor.com>
CC: <linmiaohe@huawei.com>, <kvm@vger.kernel.org>,
        <linux-kernel@vger.kernel.org>, <x86@kernel.org>
Subject: [PATCH v2 0/4] Fix various comment errors
Date: Thu, 12 Dec 2019 16:18:34 +0800
Message-ID: <1576138718-32728-1-git-send-email-linmiaohe@huawei.com>
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
---
v2:
	Fix some comments according to Sean' advice and do the patch reorganizing.

Miaohe Lin (4):
  KVM: VMX: Fix some typos and out-dated function names in comments
  KVM: x86: Fix some comment typos and grammar mistakes
  KVM: Fix some writing mistakes and wrong function name in comments
  KVM: hyperv: Fix some typos in vcpu unimpl info

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
#### [PATCH RFC v4 00/13] virtio-mem: paravirtualized memory
##### From: David Hildenbrand <david@redhat.com>

```c
From patchwork Thu Dec 12 17:11:24 2019
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: David Hildenbrand <david@redhat.com>
X-Patchwork-Id: 11288697
Return-Path: <SRS0=BLLP=2C=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id BC4E4138D
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 12 Dec 2019 17:12:19 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 87750227BF
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 12 Dec 2019 17:12:19 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="TNjKAPlF"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1730116AbfLLRMS (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 12 Dec 2019 12:12:18 -0500
Received: from us-smtp-1.mimecast.com ([207.211.31.81]:55950 "EHLO
        us-smtp-delivery-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S1730023AbfLLRMP (ORCPT
        <rfc822;kvm@vger.kernel.org>); Thu, 12 Dec 2019 12:12:15 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1576170732;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=sLqlvPDHnKvsJe6HBuLHP8LjRn0E/JlW2y8ewQYTPYo=;
        b=TNjKAPlFqiPkeEwJx9zd4ssKTRJrhg6MDGWCtxLQz5tvrKA2xuEgnP7z8Uxpq+/LXTaAdm
        q/NVg86JQNItqPiZEUPRWj1Hs1LW5Ym+6SDa6RWaw3Ej3nKm4bgsLh+kXOB484gm5U4RQV
        hL6W1oL8UZ/bK3hIEfUP3Xa2Fd70LCQ=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-89-myxY3gn5MeaLS54kABs3UA-1; Thu, 12 Dec 2019 12:12:05 -0500
X-MC-Unique: myxY3gn5MeaLS54kABs3UA-1
Received: from smtp.corp.redhat.com (int-mx06.intmail.prod.int.phx2.redhat.com
 [10.5.11.16])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 6322F1005514;
        Thu, 12 Dec 2019 17:11:59 +0000 (UTC)
Received: from t480s.redhat.com (ovpn-117-65.ams2.redhat.com [10.36.117.65])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 5A7BB5C1C3;
        Thu, 12 Dec 2019 17:11:38 +0000 (UTC)
From: David Hildenbrand <david@redhat.com>
To: linux-kernel@vger.kernel.org
Cc: linux-mm@kvack.org, virtio-dev@lists.oasis-open.org,
        virtualization@lists.linux-foundation.org, kvm@vger.kernel.org,
        Michal Hocko <mhocko@kernel.org>,
        Andrew Morton <akpm@linux-foundation.org>,
        "Michael S . Tsirkin" <mst@redhat.com>,
        David Hildenbrand <david@redhat.com>,
        Sebastien Boeuf <sebastien.boeuf@intel.com>,
        Samuel Ortiz <samuel.ortiz@intel.com>,
        Robert Bradford <robert.bradford@intel.com>,
        Luiz Capitulino <lcapitulino@redhat.com>,
        Alexander Duyck <alexander.h.duyck@linux.intel.com>,
        Alexander Potapenko <glider@google.com>,
        Alexander Viro <viro@zeniv.linux.org.uk>,
        Anshuman Khandual <anshuman.khandual@arm.com>,
        Anthony Yznaga <anthony.yznaga@oracle.com>,
        Dan Williams <dan.j.williams@intel.com>,
        Dave Young <dyoung@redhat.com>,
        Igor Mammedov <imammedo@redhat.com>,
        Jason Wang <jasowang@redhat.com>,
        Johannes Weiner <hannes@cmpxchg.org>,
        Juergen Gross <jgross@suse.com>,
        Konrad Rzeszutek Wilk <konrad.wilk@oracle.com>,
        Len Brown <lenb@kernel.org>,
        Mel Gorman <mgorman@techsingularity.net>,
        Michal Hocko <mhocko@suse.com>,
        Mike Rapoport <rppt@linux.ibm.com>,
        Oscar Salvador <osalvador@suse.com>,
        Oscar Salvador <osalvador@suse.de>,
        Pavel Tatashin <pasha.tatashin@soleen.com>,
        Pavel Tatashin <pavel.tatashin@microsoft.com>,
        Pingfan Liu <kernelfans@gmail.com>, Qian Cai <cai@lca.pw>,
        "Rafael J. Wysocki" <rjw@rjwysocki.net>,
        Stefan Hajnoczi <stefanha@redhat.com>,
        Vlastimil Babka <vbabka@suse.cz>,
        Wei Yang <richard.weiyang@gmail.com>
Subject: [PATCH RFC v4 00/13] virtio-mem: paravirtualized memory
Date: Thu, 12 Dec 2019 18:11:24 +0100
Message-Id: <20191212171137.13872-1-david@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.16
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This series is based on latest linux-next. The patches are located at:
    https://github.com/davidhildenbrand/linux.git virtio-mem-rfc-v4

The basic idea of virtio-mem is to provide a flexible,
cross-architecture memory hot(un)plug solution that avoids many limitations
imposed by existing technologies, architectures, and interfaces. More
details can be found below and in linked material.

This RFC is limited to x86-64, however, should theoretically work on any
architecture that supports virtio and implements memory hot(un)plug under
Linux - like s390x, powerpc64 and arm64. On x86-64, it is currently
possible to add/remove memory to the system in >= 4MB granularity.
Memory hotplug works very reliably. For memory unplug, there are no
guarantees how much memory can actually get unplugged, it depends on the
setup (especially: fragmentation of (unmovable) memory). I have plans to
improve that in the future.

--------------------------------------------------------------------------
1. virtio-mem
--------------------------------------------------------------------------

The basic idea behind virtio-mem was presented at KVM Forum 2018. The
slides can be found at [1]. The previous RFC can be found at [2]. The
first RFC can be found at [3]. However, the concept evolved over time. The
KVM Forum slides roughly match the current design.

Patch #2 ("virtio-mem: Paravirtualized memory hotplug") contains quite some
information, especially in "include/uapi/linux/virtio_mem.h":

  Each virtio-mem device manages a dedicated region in physical address
  space. Each device can belong to a single NUMA node, multiple devices
  for a single NUMA node are possible. A virtio-mem device is like a
  "resizable DIMM" consisting of small memory blocks that can be plugged
  or unplugged. The device driver is responsible for (un)plugging memory
  blocks on demand.

  Virtio-mem devices can only operate on their assigned memory region in
  order to (un)plug memory. A device cannot (un)plug memory belonging to
  other devices.

  The "region_size" corresponds to the maximum amount of memory that can
  be provided by a device. The "size" corresponds to the amount of memory
  that is currently plugged. "requested_size" corresponds to a request
  from the device to the device driver to (un)plug blocks. The
  device driver should try to (un)plug blocks in order to reach the
  "requested_size". It is impossible to plug more memory than requested.

  The "usable_region_size" represents the memory region that can actually
  be used to (un)plug memory. It is always at least as big as the
  "requested_size" and will grow dynamically. It will only shrink when
  explicitly triggered (VIRTIO_MEM_REQ_UNPLUG).

  Memory in the usable region can usually be read, however, there are no
  guarantees. It can happen that the device cannot process a request,
  because it is busy. The device driver has to retry later.

  Usually, during system resets all memory will get unplugged, so the
  device driver can start with a clean state. However, in specific
  scenarios (if the device is busy) it can happen that the device still
  has memory plugged. The device driver can request to unplug all memory
  (VIRTIO_MEM_REQ_UNPLUG) - which might take a while to succeed if the
  device is busy.

--------------------------------------------------------------------------
2. Linux Implementation
--------------------------------------------------------------------------

This RFC reuses quite some existing MM infrastructure, however, has to
expose some additional functionality.

Memory blocks (e.g., 128MB) are added/removed on demand. Within these
memory blocks, subblocks (e.g., 4MB) are plugged/unplugged. The sizes
depend on the target architecture, MAX_ORDER + pageblock_order, and
the block size of a virtio-mem device.

add_memory()/try_remove_memory() is used to add/remove memory blocks.
virtio-mem will not online memory blocks itself. This has to be done by
user space, or configured into the kernel
(CONFIG_MEMORY_HOTPLUG_DEFAULT_ONLINE). virtio-mem will only unplug memory
that was online to the ZONE_NORMAL. Memory is suggested to be onlined to
the ZONE_NORMAL for now.

The memory hotplug notifier is used to properly synchronize against
onlining/offlining of memory blocks and to track the states of memory
blocks (including the zone memory blocks are onlined to).

The set_online_page() callback is used to keep unplugged subblocks
of a memory block fake-offline when onlining the memory block.
generic_online_page() is used to fake-online plugged subblocks. This
handling is similar to the Hyper-V balloon driver.

PG_offline is used to mark unplugged subblocks as offline, so e.g.,
dumping tools (makedumpfile) will skip these pages. This is similar to
other balloon drivers like virtio-balloon and Hyper-V.

Memory offlining code is extended to allow drivers to drop their reference
to PG_offline pages when MEM_GOING_OFFLINE, so these pages can be skipped
when offlining memory blocks. This allows to offline memory blocks that
have partially unplugged (allocated e.g., via alloc_contig_range())
subblocks - or are completely unplugged.

alloc_contig_range()/free_contig_range() [now exposed] is used to
unplug/plug subblocks of memory blocks the are already exposed to Linux.

offline_and_remove_memory() [new] is used to offline a fully unplugged
memory block and remove it from Linux.


A lot of additional information can be found in the separate patches and
as comments in the code itself.

--------------------------------------------------------------------------
3. Changes RFC v2 -> v3
--------------------------------------------------------------------------

A lot of things changed, especially also on the QEMU + virtio side. The
biggest changes on the Linux driver side are:
- Onlining/offlining of subblocks is now emulated on top of memory blocks.
  set_online_page()+alloc_contig_range()+free_contig_range() is now used
  for that. Core MM does not have to be modified and will continue to
  online/offline full memory blocks.
- Onlining/offlining of memory blocks is no longer performed by virtio-mem.
- Pg_offline is upstream and can be used. It is also used to allow
  offlining of partially unplugged memory blocks.
- Memory block states + subblocks are now tracked more space-efficient.
- Proper kexec(), kdump(), driver unload, driver reload, ZONE_MOVABLE, ...
  handling.

--------------------------------------------------------------------------
4. Changes RFC v3 -> RFC v4
--------------------------------------------------------------------------

Only minor things changed, especially nothing on the QEMU + virtio side.
Interresting changes on the Linux driver side are:
- "mm: Allow to offline unmovable PageOffline() pages via
   MEM_GOING_OFFLINE"
-- Rework to Michals suggestion (allow to isolate all PageOffline() pages
   by skipping all PageOffline() pages in has_unmovable_pages(). Fail
   offlining later if the pages cannot be offlined/migrated).
- "virtio-mem: Allow to offline partially unplugged memory blocks"
-- Adapt to Michals suggestion on core-mm part.
- "virtio-mem: Better retry handling"
-- Optimize retry intervals
- "virtio-mem: Drop slab objects when unplug continues to fail"
-- Call drop_slab()/drop_slab_node() when unplug keeps failing for a longer
   time.
- Multiple cleanups and fixes.

--------------------------------------------------------------------------
5. Future work
--------------------------------------------------------------------------

The separate patches contain a lot of future work items. One of the next
steps is to make memory unplug more likely to succeed - currently, there
are no guarantees on how much memory can get unplugged again. I have
various ideas on how to limit fragmentation of all memory blocks that
virtio-mem added.

Memory hotplug:
- Reduce the amount of memory resources if that turnes out to be an
  issue. Or try to speed up relevant code paths to deal with many
  resources.
- Allocate the vmemmap from the added memory. Makes hotplug more likely
  to succeed, the vmemmap is stored on the same NUMA node and that
  unmovable memory will later not hinder unplug.

Memory hotunplug:
- Performance improvements:
-- Sense (lockless) if it make sense to try alloc_contig_range() at all
   before directly trying to isolate and taking locks.
-- Try to unplug bigger chunks if possible first.
-- Identify free areas first, that don't have to be evacuated.
- Make unplug more likely to succeed:
-- There are various idea to limit fragmentation on memory block
   granularity. (e.g., ZONE_PREFER_MOVABLE and smart balancing)
-- Allocate memmap from added memory. This way, less unmovable data can
   end up on the memory blocks.
- OOM handling, e.g., via an OOM handler.
- Defragmentation
-- Will require a new virtio-mem CMD to exchange plugged<->unplugged blocks

--------------------------------------------------------------------------
6. Example Usage
--------------------------------------------------------------------------

A very basic QEMU prototype (kept updated) is available at:
    https://github.com/davidhildenbrand/qemu.git virtio-mem

It lacks various features, however, works to test the guest driver side:
- No support for resizable memory regions / memory backends yet
- No protection of unplugged memory (esp., userfaultfd-wp) yet
- No dump/migration/XXX optimizations to skip unplugged memory (and avoid
  touching it)

Start QEMU with two virtio-mem devices (one per NUMA node):
 $ qemu-system-x86_64 -m 4G,maxmem=20G \
  -smp sockets=2,cores=2 \
  -numa node,nodeid=0,cpus=0-1 -numa node,nodeid=1,cpus=2-3 \
  [...]
  -object memory-backend-ram,id=mem0,size=8G \
  -device virtio-mem-pci,id=vm0,memdev=mem0,node=0,requested-size=128M \
  -object memory-backend-ram,id=mem1,size=8G \
  -device virtio-mem-pci,id=vm1,memdev=mem1,node=1,requested-size=80M

Query the configuration:
 QEMU 4.1.95 monitor - type 'help' for more information
 (qemu) info memory-devices
 Memory device [virtio-mem]: "vm0"
   memaddr: 0x140000000
   node: 0
   requested-size: 134217728
   size: 134217728
   max-size: 8589934592
   block-size: 2097152
   memdev: /objects/mem0
 Memory device [virtio-mem]: "vm1"
   memaddr: 0x340000000
   node: 1
   requested-size: 83886080
   size: 83886080
   max-size: 8589934592
   block-size: 2097152
   memdev: /objects/mem1

Add some memory to node 1:
 QEMU 4.1.95 monitor - type 'help' for more information
 (qemu) qom-set vm1 requested-size 1G

Remove some memory from node 0:
 QEMU 4.1.95 monitor - type 'help' for more information
 (qemu) qom-set vm0 requested-size 64M

Query the configuration again:
 (qemu) info memory-devices
 Memory device [virtio-mem]: "vm0"
   memaddr: 0x140000000
   node: 0
   requested-size: 67108864
   size: 67108864
   max-size: 8589934592
   block-size: 2097152
   memdev: /objects/mem0
 Memory device [virtio-mem]: "vm1"
   memaddr: 0x340000000
   node: 1
   requested-size: 1073741824
   size: 1073741824
   max-size: 8589934592
   block-size: 2097152
   memdev: /objects/mem1

--------------------------------------------------------------------------
7. Q/A
--------------------------------------------------------------------------

Q: Why add/remove parts ("subblocks") of memory blocks/sections?
A: Flexibility (section size depends on the architecture) - e.g., some
   architectures have a section size of 2GB. Also, the memory block size
   is variable (e.g., on x86-64). I want to avoid any such restrictions.
   Some use cases want to add/remove memory in smaller granularities to a
   VM (e.g., the Hyper-V balloon also implements this) - especially smaller
   VMs like used for kata containers. Also, on memory unplug, it is more
   reliable to free-up and unplug multiple small chunks instead
   of one big chunk. E.g., if one page of a DIMM is either unmovable or
   pinned, the DIMM can't get unplugged. This approach is basically a
   compromise between DIMM-based memory hot(un)plug and balloon
   inflation/deflation, which works mostly on page granularity.

Q: Why care about memory blocks?
A: They are the way to tell user space about new memory. This way,
   memory can get onlined/offlined by user space. Also, e.g., kdump
   relies on udev events to reload kexec when memory blocks are
   onlined/offlined. Memory blocks are the "real" memory hot(un)plug
   granularity. Everything that's smaller has to be emulated "on top".

Q: Won't memory unplug of subblocks fragment memory?
A: Yes and no. Unplugging e.g., >=4MB subblocks on x86-64 will not really
   fragment memory like unplugging random pages like a balloon driver does.
   Buddy merging will not be limited. However, any allocation that requires
   bigger consecutive memory chunks (e.g., gigantic pages) might observe
   the fragmentation. Possible solutions: Allocate gigantic huge pages
   before unplugging memory, don't unplug memory, combine virtio-mem with
   DIMM based memory or bigger initial memory. Remember, a virtio-mem
   device will only unplug on the memory range it manages, not on other
   DIMMs. Unplug of single memory blocks will result in similar
   fragmentation in respect to gigantic huge pages. I ahve plans for a
   virtio-mem defragmentation feature in the future.

Q: How reliable is memory unplug?
A: There are no guarantees on how much memory can get unplugged
   again. However, it is more likely to find 4MB chunks to unplug than
   e.g., 128MB chunks. If memory is terribly fragmented, there is nothing
   we can do - for now. I consider memory hotplug the first primary use
   of virtio-mem. Memory unplug might usually work, but we want to improve
   the performance and the amount of memory we can actually unplug later.

Q: Why not unplug from the ZONE_MOVABLE?
A: Unplugged memory chunks are unmovable. Unmovable data must not end up
   on the ZONE_MOVABLE - similar to gigantic pages - they will never be
   allocated from ZONE_MOVABLE. virtio-mem added memory can be onlined
   to the ZONE_MOVABLE, but subblocks will not get unplugged from it.

Q: How big should the initial (!virtio-mem) memory of a VM be?
A: virtio-mem memory will not go to the DMA zones. So to avoid running out
   of DMA memory, I suggest something like 2-3GB on x86-64. But many
   VMs can most probably deal with less DMA memory - depends on the use
   case.

[1] https://events.linuxfoundation.org/wp-content/uploads/2017/12/virtio-mem-Paravirtualized-Memory-David-Hildenbrand-Red-Hat-1.pdf
[2] https://lkml.kernel.org/r/20190919142228.5483-1-david@redhat.com
[3] https://lkml.kernel.org/r/547865a9-d6c2-7140-47e2-5af01e7d761d@redhat.com

Cc: Sebastien Boeuf  <sebastien.boeuf@intel.com>
Cc: Samuel Ortiz <samuel.ortiz@intel.com>
Cc: Robert Bradford <robert.bradford@intel.com>
Cc: Luiz Capitulino <lcapitulino@redhat.com>

David Hildenbrand (13):
  ACPI: NUMA: export pxm_to_node
  virtio-mem: Paravirtualized memory hotplug
  virtio-mem: Paravirtualized memory hotunplug part 1
  mm: Export alloc_contig_range() / free_contig_range()
  virtio-mem: Paravirtualized memory hotunplug part 2
  mm: Allow to offline unmovable PageOffline() pages via
    MEM_GOING_OFFLINE
  virtio-mem: Allow to offline partially unplugged memory blocks
  mm/memory_hotplug: Introduce offline_and_remove_memory()
  virtio-mem: Offline and remove completely unplugged memory blocks
  virtio-mem: Better retry handling
  mm/vmscan: Move count_vm_event(DROP_SLAB) into drop_slab()
  mm/vmscan: Export drop_slab() and drop_slab_node()
  virtio-mem: Drop slab objects when unplug continues to fail

 drivers/acpi/numa/srat.c        |    1 +
 drivers/virtio/Kconfig          |   18 +
 drivers/virtio/Makefile         |    1 +
 drivers/virtio/virtio_mem.c     | 1939 +++++++++++++++++++++++++++++++
 fs/drop_caches.c                |    4 +-
 include/linux/memory_hotplug.h  |    1 +
 include/linux/mm.h              |    4 +-
 include/linux/page-flags.h      |   10 +
 include/uapi/linux/virtio_ids.h |    1 +
 include/uapi/linux/virtio_mem.h |  204 ++++
 mm/memory_hotplug.c             |   76 +-
 mm/page_alloc.c                 |   26 +
 mm/page_isolation.c             |    9 +
 mm/vmscan.c                     |    3 +
 14 files changed, 2282 insertions(+), 15 deletions(-)
 create mode 100644 drivers/virtio/virtio_mem.c
 create mode 100644 include/uapi/linux/virtio_mem.h
```
#### [PATCH v5 0/2] kvm: Use huge pages for DAX-backed files
##### From: Barret Rhoden <brho@google.com>

```c
From patchwork Thu Dec 12 18:22:36 2019
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Barret Rhoden <brho@google.com>
X-Patchwork-Id: 11289005
Return-Path: <SRS0=BLLP=2C=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id BC87614B7
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 12 Dec 2019 18:22:57 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 994B922527
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 12 Dec 2019 18:22:57 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=google.com header.i=@google.com
 header.b="wOmXzfFa"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1730346AbfLLSWy (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 12 Dec 2019 13:22:54 -0500
Received: from mail-qv1-f74.google.com ([209.85.219.74]:52070 "EHLO
        mail-qv1-f74.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1730110AbfLLSWy (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 12 Dec 2019 13:22:54 -0500
Received: by mail-qv1-f74.google.com with SMTP id x22so2004656qvc.18
        for <kvm@vger.kernel.org>; Thu, 12 Dec 2019 10:22:53 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=date:message-id:mime-version:subject:from:to:cc;
        bh=rEnziU9nLlHlYc/tf137lSRc7sdTqh5wg35Mf+C3wB0=;
        b=wOmXzfFazrugxZCYf410kz6njqqI2ZayPQ3Zp1rCCJAl61eXIHZJMLIXKd7ipcL41R
         Sm+Wcca2Q6JqgT++kdbvjzbjYq0FYVW/lmi7QB7yJwkVuo4MV424+x+d7yCwKx0ttep0
         Lptl32SFvhXt0TyRQZlvv9SqXlyRFpCG1TsG3O7/iQ2t4vkLUnHSfRpXrHshDh35/gFo
         c/KEVVI0neOaMUy1YUeklfjbepAMeO7ukOv7HLZ0ISIwDFMKd/GAqrrKh7r8JeBNqa+r
         SbafHPrcaqVH22AN6GG+pQawROsiZA4u3mp/RCCP/9BjFwd9lIMMNNZaOz5x++hHZB3m
         2fSg==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:date:message-id:mime-version:subject:from:to:cc;
        bh=rEnziU9nLlHlYc/tf137lSRc7sdTqh5wg35Mf+C3wB0=;
        b=Vac+jCaLPo+iIsWxTr0grRNKfD8qF8MEUOg0zXsCNuBGJPvxYSytDZj3Jed4pwOc+r
         /t/nBMZrFwx2RYvX6dY7x0rcQFAnNIjMEqn5D3nEVeR/mn6vrbpnclPvygulObmHpqu0
         8llTCramnZb12W7CIygkoG4u5ptbnME38lI1s8aOGewQpTVYA3jQrrLA7eQUbb2Gov3E
         LaR7kjS0nirhUI0ecMFU9zGVmbVpsS75+cpXab6WZQ+H3mVCessWIKTd8a3LZf01d7OT
         KNRh5gEt2RuB0ljRF58lAKUUrl4XsoEWXyEAiapq+W2Fu4UCH8qd3kCE/Fe60BKYauqL
         ZAZg==
X-Gm-Message-State: APjAAAXljZ5pNG31Re8XrZ+vI07HSLi9wwh7sx3CP0+GW5ayc9l3Rt4S
        s/PDEWgaEA4fOPGaHZl3aLw5UmVr
X-Google-Smtp-Source: 
 APXvYqzcW/ZghkfJqEYc4rFEK2YkEyqYYEYYl+bxHBfcPF4MTg+EIi+2m6XM7rKZ/g0d94tGM2bioMma
X-Received: by 2002:ac8:5308:: with SMTP id t8mr8677688qtn.51.1576174973189;
 Thu, 12 Dec 2019 10:22:53 -0800 (PST)
Date: Thu, 12 Dec 2019 13:22:36 -0500
Message-Id: <20191212182238.46535-1-brho@google.com>
Mime-Version: 1.0
X-Mailer: git-send-email 2.24.1.735.g03f4e72817-goog
Subject: [PATCH v5 0/2] kvm: Use huge pages for DAX-backed files
From: Barret Rhoden <brho@google.com>
To: Paolo Bonzini <pbonzini@redhat.com>,
        Dan Williams <dan.j.williams@intel.com>,
        David Hildenbrand <david@redhat.com>,
        Dave Jiang <dave.jiang@intel.com>,
        Alexander Duyck <alexander.h.duyck@linux.intel.com>,
        Sean Christopherson <sean.j.christopherson@intel.com>
Cc: linux-nvdimm@lists.01.org, x86@kernel.org, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org, jason.zeng@intel.com
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This patchset allows KVM to map huge pages for DAX-backed files.

v4 -> v5:
v4: https://lore.kernel.org/lkml/20191211213207.215936-1-brho@google.com/
- Rebased onto kvm/queue
- Removed the switch statement and fixed PUD_SIZE; just use
  dev_pagemap_mapping_shift() > PAGE_SHIFT
- Added explanation of parameter changes to patch 1's commit message

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

 arch/x86/kvm/mmu/mmu.c | 31 +++++++++++++++++++++++++++----
 include/linux/mm.h     |  3 +++
 mm/memory-failure.c    | 38 +++-----------------------------------
 mm/util.c              | 34 ++++++++++++++++++++++++++++++++++
 4 files changed, 67 insertions(+), 39 deletions(-)
```
