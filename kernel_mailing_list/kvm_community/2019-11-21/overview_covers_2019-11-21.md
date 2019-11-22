

#### [PATCH 0/5] vfio/spapr: Handle changes of master irq chip for VFIO
##### From: David Gibson <david@gibson.dropbear.id.au>

```c
From patchwork Thu Nov 21 00:56:02 2019
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: David Gibson <david@gibson.dropbear.id.au>
X-Patchwork-Id: 11255099
Return-Path: <SRS0=EBfH=ZN=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id D97FE14DB
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 21 Nov 2019 00:58:49 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id B077020885
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 21 Nov 2019 00:58:49 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=gibson.dropbear.id.au
 header.i=@gibson.dropbear.id.au header.b="EyVBCYXM"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726573AbfKUA6r (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 20 Nov 2019 19:58:47 -0500
Received: from ozlabs.org ([203.11.71.1]:60897 "EHLO ozlabs.org"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726202AbfKUA6q (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 20 Nov 2019 19:58:46 -0500
Received: by ozlabs.org (Postfix, from userid 1007)
        id 47JLm40WNcz9sPL; Thu, 21 Nov 2019 11:58:43 +1100 (AEDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple;
        d=gibson.dropbear.id.au; s=201602; t=1574297924;
        bh=tCEjjjB7GWqDoKkmTHHtPfHvbR0elnZvywA0y/9MLo0=;
        h=From:To:Cc:Subject:Date:From;
        b=EyVBCYXMbgL/PZAgLOTtz0gX0pXijPuX9pUZJRgcHWhLB/w4oLX2BSi4I/VPlBnOC
         q0FYGB73r6i3IDHdz26veT6iTYIPVJLENM+xVShNbLHYT6ymE19SLFyXyQA/XjtblG
         dqtn6WBoa1baAQuibNkZrG2Ez5v4xLF3w4mfR4fA=
From: David Gibson <david@gibson.dropbear.id.au>
To: Alex Williamson <alex.williamson@redhat.com>, clg@kaod.org
Cc: groug@kaod.org, philmd@redhat.com, qemu-ppc@nongnu.org,
 Paolo Bonzini <pbonzini@redhat.com>, Jason Wang <jasowang@redhat.com>,
 Laurent Vivier <laurent@vivier.eu>,
 David Gibson <david@gibson.dropbear.id.au>, kvm@vger.kernel.org,
 qemu-devel@nongnu.org, Riku Voipio <riku.voipio@iki.fi>, =?utf-8?q?Marc-And?=
	=?utf-8?q?r=C3=A9_Lureau?= <marcandre.lureau@redhat.com>
Subject: [PATCH 0/5] vfio/spapr: Handle changes of master irq chip for VFIO
 devices
Date: Thu, 21 Nov 2019 11:56:02 +1100
Message-Id: <20191121005607.274347-1-david@gibson.dropbear.id.au>
X-Mailer: git-send-email 2.23.0
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Due to the way feature negotiation works in PAPR (which is a
paravirtualized platform), we can end up changing the global irq chip
at runtime, including it's KVM accelerate model.  That causes
complications for VFIO devices with INTx, which wire themselves up
directly to the KVM irqchip for performance.

This series introduces a new notifier to let VFIO devices (and
anything else that needs to in the future) know about changes to the
master irqchip.  It modifies VFIO to respond to the notifier,
reconnecting itself to the new KVM irqchip as necessary.

In particular this removes a misleading (though not wholly inaccurate)
warning that occurs when using VFIO devices on a pseries machine type
guest.

Open question: should this go into qemu-4.2 or wait until 5.0?  It's
has medium complexity / intrusiveness, but it *is* a bugfix that I
can't see a simpler way to fix.  It's effectively a regression from
qemu-4.0 to qemu-4.1 (because that introduced XIVE support by
default), although not from 4.1 to 4.2.

Changes since RFC:
 * Fixed some incorrect error paths pointed by aw in 3/5
 * 5/5 had some problems previously, but they have been obsoleted by
   other changes merged in the meantime

David Gibson (5):
  kvm: Introduce KVM irqchip change notifier
  vfio/pci: Split vfio_intx_update()
  vfio/pci: Respond to KVM irqchip change notifier
  spapr: Handle irq backend changes with VFIO PCI devices
  spapr: Work around spurious warnings from vfio INTx initialization

 accel/kvm/kvm-all.c    | 18 ++++++++++++
 accel/stubs/kvm-stub.c | 12 ++++++++
 hw/ppc/spapr_irq.c     | 17 +++++++++++-
 hw/vfio/pci.c          | 62 +++++++++++++++++++++++++++---------------
 hw/vfio/pci.h          |  1 +
 include/sysemu/kvm.h   |  5 ++++
 6 files changed, 92 insertions(+), 23 deletions(-)
```
#### [PATCH v7 00/24] mm/gup: track dma-pinned pages: FOLL_PIN
##### From: John Hubbard <jhubbard@nvidia.com>

```c
From patchwork Thu Nov 21 07:13:30 2019
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: John Hubbard <jhubbard@nvidia.com>
X-Patchwork-Id: 11255633
Return-Path: <SRS0=EBfH=ZN=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 76876112B
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 21 Nov 2019 07:16:23 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 39B10208A1
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 21 Nov 2019 07:16:23 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=nvidia.com header.i=@nvidia.com
 header.b="q1DInNto"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727738AbfKUHQL (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 21 Nov 2019 02:16:11 -0500
Received: from hqemgate16.nvidia.com ([216.228.121.65]:4374 "EHLO
        hqemgate16.nvidia.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1727296AbfKUHOH (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 21 Nov 2019 02:14:07 -0500
Received: from hqpgpgate102.nvidia.com (Not Verified[216.228.121.13]) by
 hqemgate16.nvidia.com (using TLS: TLSv1.2, DES-CBC3-SHA)
        id <B5dd639350000>; Wed, 20 Nov 2019 23:13:57 -0800
Received: from hqmail.nvidia.com ([172.20.161.6])
  by hqpgpgate102.nvidia.com (PGP Universal service);
  Wed, 20 Nov 2019 23:13:56 -0800
X-PGP-Universal: processed;
        by hqpgpgate102.nvidia.com on Wed, 20 Nov 2019 23:13:56 -0800
Received: from HQMAIL109.nvidia.com (172.20.187.15) by HQMAIL105.nvidia.com
 (172.20.187.12) with Microsoft SMTP Server (TLS) id 15.0.1473.3; Thu, 21 Nov
 2019 07:13:55 +0000
Received: from HQMAIL109.nvidia.com (172.20.187.15) by HQMAIL109.nvidia.com
 (172.20.187.15) with Microsoft SMTP Server (TLS) id 15.0.1473.3; Thu, 21 Nov
 2019 07:13:55 +0000
Received: from hqnvemgw03.nvidia.com (10.124.88.68) by HQMAIL109.nvidia.com
 (172.20.187.15) with Microsoft SMTP Server (TLS) id 15.0.1473.3 via Frontend
 Transport; Thu, 21 Nov 2019 07:13:55 +0000
Received: from blueforge.nvidia.com (Not Verified[10.110.48.28]) by
 hqnvemgw03.nvidia.com with Trustwave SEG (v7,5,8,10121)
        id <B5dd639330001>; Wed, 20 Nov 2019 23:13:55 -0800
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
 "Mauro Carvalho Chehab" <mchehab@kernel.org>,
 Michael Ellerman <mpe@ellerman.id.au>, Michal Hocko <mhocko@suse.com>,
 Mike Kravetz <mike.kravetz@oracle.com>, "Paul Mackerras" <paulus@samba.org>,
 Shuah Khan <shuah@kernel.org>, Vlastimil Babka <vbabka@suse.cz>,
 <bpf@vger.kernel.org>, <dri-devel@lists.freedesktop.org>,
 <kvm@vger.kernel.org>, <linux-block@vger.kernel.org>,
 <linux-doc@vger.kernel.org>, <linux-fsdevel@vger.kernel.org>,
 <linux-kselftest@vger.kernel.org>, <linux-media@vger.kernel.org>,
 <linux-rdma@vger.kernel.org>, <linuxppc-dev@lists.ozlabs.org>,
 <netdev@vger.kernel.org>, <linux-mm@kvack.org>,
 LKML <linux-kernel@vger.kernel.org>, John Hubbard <jhubbard@nvidia.com>
Subject: [PATCH v7 00/24] mm/gup: track dma-pinned pages: FOLL_PIN
Date: Wed, 20 Nov 2019 23:13:30 -0800
Message-ID: <20191121071354.456618-1-jhubbard@nvidia.com>
X-Mailer: git-send-email 2.24.0
MIME-Version: 1.0
X-NVConfidentiality: public
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=nvidia.com; s=n1;
        t=1574320437; bh=3vIO3cYgsoEdiLgYCT6X61QBYt/SSnIougEaG5v/idU=;
        h=X-PGP-Universal:From:To:CC:Subject:Date:Message-ID:X-Mailer:
         MIME-Version:X-NVConfidentiality:Content-Type:
         Content-Transfer-Encoding;
        b=q1DInNto4lmZqG/v0XlNOhrbq9XNwwO9QrWZrznVzzDAbE5jj+qZm6D/9oS/1gXWM
         t7oOEw8Off1/Lkj+kNf/2ivso1R1LZl9jJmzIzMB1k6Co4/mH7O669EYutbMkl9qxQ
         kEzcTQdJXKuUV+67ySP4gcV0NB3KOJXMu4ekwenXSZymifelYahMIJICSbqXztE6Pe
         YvHxGnxpWWd6yPSt9NymCJBYl0g9oG6JOP00maBoBDEExPbFBuQF4UDQLvR0dHCkl3
         7jRV8BiaouJ4DLeHFwMwEZimhytbli9U4cxHPylmHD39b/eC6KwyHXwwtDLh6s30iw
         b6CDWfgkmmfog==
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Hi,

OK, here is v7, maybe this is the last one. The corresponding git repo
and branch is:

    git@github.com:johnhubbard/linux.git pin_user_pages_tracking_v7

Ira, you reviewed the gup_benchmark patches a bit earlier, but I
removed one or two of those review-by tags, due to invasive changes
I made after your review (in response to further reviews).
So could you please reply to any patches you'd like to have
reviewed-by's restoredto, if any? Mainly I'm thinking of
"mm/gup_benchmark: support pin_user_pages() and related calls". Also
various FOLL_LONGTERM vs pin_longterm*() patches.

The following blurb from the v6 cover letter is still applicable, and
I'll repeat it here so it doesn't get lost in the patch blizzard:

Christoph Hellwig has a preference to do things a little differently,
for the devmap cleanup in patch 5 ("mm: devmap: refactor 1-based
refcounting for ZONE_DEVICE pages"). That came up in a different
review thread, because the patch is out for review in two locations.
Here's that review thread:

    https://lore.kernel.org/r/20191118070826.GB3099@infradead.org

...and I'm hoping that we can defer that request, because otherwise
it derails this series, which is starting to otherwise look like
it could be ready for 5.5.


Changes since v6:

* Renamed a couple of routines, to get rid of unnecessary leading
  underscores:

    __pin_compound_head() --> grab_compound_head()
    __record_subpages()   --> record_subpages()

* Fixed the error fallback (put_compound_head()) so as to match the fix
  in the previous version: need to put back N * GUP_PIN_COUNTING_BIAS
  pages, for FOLL_PIN cases.

* Factored out yet another common chunk of code, into a new grab_page()
  routine.

* Added a missing compound_head() call to put_compound_head().

* [Re-]added Jens Axboe's reviewed-by tag to the fs/io_uring patch.

* Added more reviewed-by's from Jan Kara.


Changes since v5:

* Fixed the refcounting for huge pages: in most cases, it was
  only taking one GUP_PIN_COUNTING_BIAS's worth of refs, when it
  should have been taking one GUP_PIN_COUNTING_BIAS for each subpage.

  (Much thanks to Jan Kara for spotting that one!)

* Renamed user_page_ref_inc() to try_pin_page(), and added a new
  try_pin_compound_head(). This definitely improves readability.

* Factored out some more duplication in the FOLL_PIN and FOLL_GET
  cases, in gup.c.

* Fixed up some straggling "get_" --> "pin_" references in the comments.

* Added reviewed-by tags.

Changes since v4:

* Renamed put_user_page*() --> unpin_user_page().

* Removed all pin_longterm_pages*() calls. We will use FOLL_LONGTERM
  at the call sites. (FOLL_PIN, however, remains an internal gup flag).

  This is very nice: many patches just change three characters now:
  get_user_pages --> pin_user_pages. I think we've found the right
  balance of wrapper calls and gup flags, for the call sites.

* Updated a lot of documentation and commit logs to match the above
  two large changes.

* Changed gup_benchmark tests and run_vmtests, to adapt to one less
  use case: there is no pin_longterm_pages() call anymore.

* This includes a new devmap cleanup patch from Dan Williams, along
  with a rebased follow-up: patches 4 and 5, already mentioned above.

* Fixed patch 10 ("mm/gup: introduce pin_user_pages*() and FOLL_PIN"),
  so as to make pin_user_pages*() calls act as placeholders for the
  corresponding get_user_pages*() calls, until a later patch fully
  implements the DMA-pinning functionality.

  Thanks to Jan Kara for noticing that.

* Fixed the implementation of pin_user_pages_remote().

* Further tweaked patch 2 ("mm/gup: factor out duplicate code from four
  routines"), in response to Jan Kara's feedback.

* Dropped a few reviewed-by tags  due to changes that invalidated
  them.


Changes since v3:

* VFIO fix (patch 8): applied further cleanup: removed a pre-existing,
  unnecessary release and reacquire of mmap_sem. Moved the DAX vma
  checks from the vfio call site, to gup internals, and added comments
  (and commit log) to clarify.

* Due to the above, made a corresponding fix to the
  pin_longterm_pages_remote(), which was actually calling the wrong
  gup internal function.

* Changed put_user_page() comments, to refer to pin*() APIs, rather than
  get_user_pages*() APIs.

* Reverted an accidental whitespace-only change in the IB ODP code.

* Added a few more reviewed-by tags.


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

* Patches 1-9: refactoring and preparatory cleanup, independent fixes

* Patch 10: introduce pin_user_pages(), FOLL_PIN, but no functional
           changes yet
* Patches 11-16: Convert existing put_user_page() callers, to use the
                 new pin*()
* Patch 17: Activate tracking of FOLL_PIN pages.
* Patches 18-20: convert various callers
* Patches: 21-23: gup_benchmark and run_vmtests support
* Patch 24: rename put_user_page*() --> unpin_user_page*()

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

Dan Williams (1):
  mm: Cleanup __put_devmap_managed_page() vs ->page_free()

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
  IB/{core,hw,umem}: set FOLL_PIN via pin_user_pages*(), fix up ODP
  mm/process_vm_access: set FOLL_PIN via pin_user_pages_remote()
  drm/via: set FOLL_PIN via pin_user_pages_fast()
  fs/io_uring: set FOLL_PIN via pin_user_pages()
  net/xdp: set FOLL_PIN via pin_user_pages()
  mm/gup: track FOLL_PIN pages
  media/v4l2-core: pin_user_pages (FOLL_PIN) and put_user_page()
    conversion
  vfio, mm: pin_user_pages (FOLL_PIN) and put_user_page() conversion
  powerpc: book3s64: convert to pin_user_pages() and put_user_page()
  mm/gup_benchmark: use proper FOLL_WRITE flags instead of hard-coding
    "1"
  mm/gup_benchmark: support pin_user_pages() and related calls
  selftests/vm: run_vmtests: invoke gup_benchmark with basic FOLL_PIN
    coverage
  mm, tree-wide: rename put_user_page*() to unpin_user_page*()

 Documentation/core-api/index.rst            |   1 +
 Documentation/core-api/pin_user_pages.rst   | 233 +++++++++
 arch/powerpc/mm/book3s64/iommu_api.c        |  12 +-
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
 include/linux/mm.h                          | 195 ++++++-
 include/linux/mmzone.h                      |   2 +
 include/linux/page_ref.h                    |  10 +
 mm/gup.c                                    | 553 +++++++++++++++-----
 mm/gup_benchmark.c                          |  74 ++-
 mm/huge_memory.c                            |  44 +-
 mm/hugetlb.c                                |  36 +-
 mm/memremap.c                               |  76 ++-
 mm/process_vm_access.c                      |  28 +-
 mm/vmstat.c                                 |   2 +
 net/xdp/xdp_umem.c                          |   4 +-
 tools/testing/selftests/vm/gup_benchmark.c  |  21 +-
 tools/testing/selftests/vm/run_vmtests      |  22 +
 30 files changed, 1121 insertions(+), 352 deletions(-)
 create mode 100644 Documentation/core-api/pin_user_pages.rst
```
#### [PATCH V1 0/2] Intel IFC VF driver for VDPA
##### From: Zhu Lingshan <lingshan.zhu@intel.com>

```c
From patchwork Thu Nov 21 13:34:35 2019
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Zhu Lingshan <lingshan.zhu@intel.com>
X-Patchwork-Id: 11256239
Return-Path: <SRS0=EBfH=ZN=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id B63F0138C
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 21 Nov 2019 13:36:58 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id A0EFB20715
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 21 Nov 2019 13:36:58 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726792AbfKUNgx (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 21 Nov 2019 08:36:53 -0500
Received: from mga12.intel.com ([192.55.52.136]:28493 "EHLO mga12.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726574AbfKUNgx (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 21 Nov 2019 08:36:53 -0500
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from fmsmga002.fm.intel.com ([10.253.24.26])
  by fmsmga106.fm.intel.com with ESMTP/TLS/DHE-RSA-AES256-GCM-SHA384;
 21 Nov 2019 05:36:53 -0800
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.69,226,1571727600";
   d="scan'208";a="238178517"
Received: from unknown (HELO localhost.localdomain.bj.intel.com)
 ([10.240.193.79])
  by fmsmga002.fm.intel.com with ESMTP; 21 Nov 2019 05:36:50 -0800
From: Zhu Lingshan <lingshan.zhu@intel.com>
To: mst@redhat.com, jasowang@redhat.com, alex.williamson@redhat.com
Cc: linux-kernel@vger.kernel.org,
        virtualization@lists.linux-foundation.org, kvm@vger.kernel.org,
        netdev@vger.kernel.org, dan.daly@intel.com,
        cunming.liang@intel.com, tiwei.bie@intel.com, jason.zeng@intel.com,
        zhiyuan.lv@intel.com, Zhu Lingshan <lingshan.zhu@intel.com>
Subject: [PATCH V1 0/2] Intel IFC VF driver for VDPA
Date: Thu, 21 Nov 2019 21:34:35 +0800
Message-Id: <1574343277-8835-1-git-send-email-lingshan.zhu@intel.com>
X-Mailer: git-send-email 1.8.3.1
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Hi all,

This series intends to implement driver module for Intel IFC VF NIC,
which can do Vhost Data Plane Acceleration(VDPA) by offloading
dataplane traffic to hardware.

This series depends on and complies to:
virtio_mdev V13 https://lkml.org/lkml/2019/11/18/261
vhost_mdev V7 https://lkml.org/lkml/2019/11/18/1068

There comes mainly two parts of the code:
(1) ifcvf_main layer handles probe / remove / mdev operations,
implemented struct mdev_virtio_ops to support virtio_mdev
and vhost_mdev, and other supportive functions.

(2) ifcvf_base layer talks directly to the hardware, which support
the ifcvf_main layer.


Zhu Lingshan (2):
  IFC VF initialization functions
  This commit adds functions to support virtio_mdev and vhost_mdev

 drivers/vhost/Kconfig            |  12 +
 drivers/vhost/Makefile           |   3 +-
 drivers/vhost/ifcvf/Makefile     |   2 +
 drivers/vhost/ifcvf/ifcvf_base.c | 328 +++++++++++++++++++++++
 drivers/vhost/ifcvf/ifcvf_base.h | 126 +++++++++
 drivers/vhost/ifcvf/ifcvf_main.c | 557 +++++++++++++++++++++++++++++++++++++++
 6 files changed, 1027 insertions(+), 1 deletion(-)
 create mode 100644 drivers/vhost/ifcvf/Makefile
 create mode 100644 drivers/vhost/ifcvf/ifcvf_base.c
 create mode 100644 drivers/vhost/ifcvf/ifcvf_base.h
 create mode 100644 drivers/vhost/ifcvf/ifcvf_main.c
```
#### [PATCH 0/2] Limit memory encryption cpuid pass through
##### From: Peter Gonda <pgonda@google.com>

```c
From patchwork Thu Nov 21 20:33:42 2019
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Peter Gonda <pgonda@google.com>
X-Patchwork-Id: 11256887
Return-Path: <SRS0=EBfH=ZN=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id C24A0913
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 21 Nov 2019 20:34:25 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 92B98206CC
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 21 Nov 2019 20:34:25 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=google.com header.i=@google.com
 header.b="D0HtL5M8"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726574AbfKUUeY (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 21 Nov 2019 15:34:24 -0500
Received: from mail-pf1-f202.google.com ([209.85.210.202]:35135 "EHLO
        mail-pf1-f202.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726293AbfKUUeY (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 21 Nov 2019 15:34:24 -0500
Received: by mail-pf1-f202.google.com with SMTP id x3so2838847pfr.2
        for <kvm@vger.kernel.org>; Thu, 21 Nov 2019 12:34:24 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=date:message-id:mime-version:subject:from:to:cc;
        bh=OdnAgYVZPnAd48x7oEygPbtJpfpk8LTS6oFm8dIEa10=;
        b=D0HtL5M8pwn3H1chHic7xgm/BAaQvnEX6QevihD+9jQ6mV5W0FKK5GnTuao5oM6n8a
         yH3siAyyJORnYmdr5NHHw/h7swYylsPUBKL+6Wq5lsJORb1aggC13YUuDp/Yz5j+jTEk
         FLUL4qPqr7ZMc3LcS54VmdZ4pHL2iOTczGGc/2f0Rq/kRLIY4kg7UUKvgXBa5Hfu+2sY
         B0a3kacBgeoH7g6WCe7pKYs6FCNZXii5FDxgVmuHDq+g/U/xxOkxGLGN6vDVgkIOwmCF
         7TijKkAfhfY3An2viFWPfvtsg0MIqY92+GSTvcGLw6nAtef0MQ2MWciDo70cWCWbg2R8
         RHtg==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:date:message-id:mime-version:subject:from:to:cc;
        bh=OdnAgYVZPnAd48x7oEygPbtJpfpk8LTS6oFm8dIEa10=;
        b=ErexdQqTH+BfSXhDoUNKZ8mqs29knTLbJHIrumVJKYwl3oeLS6TweUbl0WFX7SOOLY
         A80TCWQKRed4Nl8sAIpfGWBCcXnW/n6M00622UrBmr8XU2Z4FcPIjMBFdN2w5S3NnZA8
         RX3xfutMqVsY5dkIhrW/sIftGr0pj8or+G+RCHYHo8YODmye0xO/GFl87Z7IwPdfkmMl
         F4PVblbiEwDSL+1y1+wmzW20foT9SN9a+jtCcJrul3eKYpLJxS4uEMd5lIRcGu8h7NaC
         qh8kw5nu62AMrvkZf1/OUfNKpXO/GNSqPUga3Re2EE+wqKIVDDLB/iQTWygvXhTeMkFh
         Iyqw==
X-Gm-Message-State: APjAAAVuIwZTYHRT5bSMZuUNIZWsqtdmz9PRh96oPZkmiDK7UASZw+Eh
        Yvr5K/xFnroehZp6deA+wdIsjoEQxFs=
X-Google-Smtp-Source: 
 APXvYqxV+WDp0EZRJJQb55WQBxo3rCIdnIhG5+ijkXveOJJ24zEtSTvhqAvfyG+tCFKtGtbrHjXoBQDV46w=
X-Received: by 2002:a63:ca06:: with SMTP id n6mr11483439pgi.81.1574368463460;
 Thu, 21 Nov 2019 12:34:23 -0800 (PST)
Date: Thu, 21 Nov 2019 12:33:42 -0800
Message-Id: <20191121203344.156835-1-pgonda@google.com>
Mime-Version: 1.0
X-Mailer: git-send-email 2.24.0.432.g9d3f5f5b63-goog
Subject: [PATCH 0/2] Limit memory encryption cpuid pass through
From: Peter Gonda <pgonda@google.com>
To: Paolo Bonzini <pbonzini@redhat.com>, kvm@vger.kernel.org
Cc: Jim Mattson <jmattson@google.com>,
        Brijesh Singh <brijesh.singh@amd.com>,
        Tom Lendacky <thomas.lendacky@amd.com>,
        Peter Gonda <pgonda@google.com>,
        Sean Christopherson <sean.j.christopherson@intel.com>
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

KVM_GET_SUPPORTED_CPUID for 0x8000001F currently passes through all data if
X86_FEATURE_SEV is enabled. Guests only need the SEV bit and Cbit location
to work correctly. This series moves handing of this cpuid function out of
svm.c to the general x86 function and masks out host data.

Peter Gonda (2):
  KVM x86: Move kvm cpuid support out of svm
  KVM x86: Mask memory encryption guest cpuid

 arch/x86/kvm/cpuid.c | 11 +++++++++++
 arch/x86/kvm/svm.c   |  7 -------
 2 files changed, 11 insertions(+), 7 deletions(-)
```
