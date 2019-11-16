

#### [RFC PATCH v1 00/10] s390/vfio-ccw: Channel Path Handling
##### From: Eric Farman <farman@linux.ibm.com>

```c
From patchwork Fri Nov 15 02:56:10 2019
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Eric Farman <farman@linux.ibm.com>
X-Patchwork-Id: 11244747
Return-Path: <SRS0=Hm6W=ZH=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id EC13C1393
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 15 Nov 2019 03:28:26 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id D622E20709
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 15 Nov 2019 03:28:26 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727134AbfKOD20 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 14 Nov 2019 22:28:26 -0500
Received: from mx0b-001b2d01.pphosted.com ([148.163.158.5]:57796 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S1727053AbfKOD2Z (ORCPT
        <rfc822;kvm@vger.kernel.org>); Thu, 14 Nov 2019 22:28:25 -0500
Received: from pps.filterd (m0098419.ppops.net [127.0.0.1])
        by mx0b-001b2d01.pphosted.com (8.16.0.42/8.16.0.42) with SMTP id
 xAF39WGJ057895
        for <kvm@vger.kernel.org>; Thu, 14 Nov 2019 22:28:24 -0500
Received: from e06smtp07.uk.ibm.com (e06smtp07.uk.ibm.com [195.75.94.103])
        by mx0b-001b2d01.pphosted.com with ESMTP id 2w9jtv6bre-1
        (version=TLSv1.2 cipher=AES256-GCM-SHA384 bits=256 verify=NOT)
        for <kvm@vger.kernel.org>; Thu, 14 Nov 2019 22:28:20 -0500
Received: from localhost
        by e06smtp07.uk.ibm.com with IBM ESMTP SMTP Gateway: Authorized Use
 Only! Violators will be prosecuted
        for <kvm@vger.kernel.org> from <farman@linux.ibm.com>;
        Fri, 15 Nov 2019 02:56:24 -0000
Received: from b06cxnps3074.portsmouth.uk.ibm.com (9.149.109.194)
        by e06smtp07.uk.ibm.com (192.168.101.137) with IBM ESMTP SMTP Gateway:
 Authorized Use Only! Violators will be prosecuted;
        (version=TLSv1/SSLv3 cipher=AES256-GCM-SHA384 bits=256/256)
        Fri, 15 Nov 2019 02:56:22 -0000
Received: from d06av25.portsmouth.uk.ibm.com (d06av25.portsmouth.uk.ibm.com
 [9.149.105.61])
        by b06cxnps3074.portsmouth.uk.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id xAF2uKrB53805276
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Fri, 15 Nov 2019 02:56:20 GMT
Received: from d06av25.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id CA5D211C050;
        Fri, 15 Nov 2019 02:56:20 +0000 (GMT)
Received: from d06av25.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id B6D8111C04A;
        Fri, 15 Nov 2019 02:56:20 +0000 (GMT)
Received: from tuxmaker.boeblingen.de.ibm.com (unknown [9.152.85.9])
        by d06av25.portsmouth.uk.ibm.com (Postfix) with ESMTPS;
        Fri, 15 Nov 2019 02:56:20 +0000 (GMT)
Received: by tuxmaker.boeblingen.de.ibm.com (Postfix, from userid 4958)
        id 4CF01E01C5; Fri, 15 Nov 2019 03:56:20 +0100 (CET)
From: Eric Farman <farman@linux.ibm.com>
To: kvm@vger.kernel.org, linux-s390@vger.kernel.org
Cc: Cornelia Huck <cohuck@redhat.com>,
        Jason Herne <jjherne@linux.ibm.com>,
        Jared Rossi <jrossi@linux.ibm.com>,
        Eric Farman <farman@linux.ibm.com>
Subject: [RFC PATCH v1 00/10] s390/vfio-ccw: Channel Path Handling
Date: Fri, 15 Nov 2019 03:56:10 +0100
X-Mailer: git-send-email 2.17.1
X-TM-AS-GCONF: 00
x-cbid: 19111502-0028-0000-0000-000003B7024B
X-IBM-AV-DETECTION: SAVI=unused REMOTE=unused XFE=unused
x-cbparentid: 19111502-0029-0000-0000-0000247A11BC
Message-Id: <20191115025620.19593-1-farman@linux.ibm.com>
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.95,18.0.572
 definitions=2019-11-14_07:2019-11-14,2019-11-14 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 malwarescore=0 suspectscore=2
 adultscore=0 clxscore=1015 impostorscore=0 bulkscore=0 spamscore=0
 mlxscore=0 lowpriorityscore=0 priorityscore=1501 mlxlogscore=629
 phishscore=0 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.12.0-1910280000 definitions=main-1911150027
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Here is a first pass at the channel-path handling code for vfio-ccw.
This was initially developed by Farhan Ali this past summer, and
picked up by me.  For my own benefit/sanity, I made a small changelog
in the commit message for each patch, describing the changes I've
made to his original code beyond just rebasing to master.

I did split a couple of his patches, to (hopefully) make them a little
more understandable.  The entire series is based on top of the trace
rework patches from a few weeks ago, which are currently pending.
But really, the only cause for overlap is the trace patch here.
The bulk of it is really self-contained.

With this, and the corresponding QEMU series (to be posted momentarily),
applied I am able to configure off/on a CHPID (for example, by issuing
"chchp -c 0/1 xx" on the host), and the guest is able to see both the
events and reflect the updated path masks in its structures.

For reasons that are hopefully obvious, issuing chchp within the guest
only works for the logical vary.  Configuring it off/on does not work,
which I think is fine.

Eric Farman (4):
  vfio-ccw: Refactor the unregister of the async regions
  vfio-ccw: Refactor IRQ handlers
  vfio-ccw: Add trace for CRW event
  vfio-ccw: Remove inline get_schid() routine

Farhan Ali (6):
  vfio-ccw: Introduce new helper functions to free/destroy regions
  vfio-ccw: Register a chp_event callback for vfio-ccw
  vfio-ccw: Use subchannel lpm in the orb
  vfio-ccw: Introduce a new schib region
  vfio-ccw: Introduce a new CRW region
  vfio-ccw: Wire up the CRW irq and CRW region

 drivers/s390/cio/Makefile           |   2 +-
 drivers/s390/cio/vfio_ccw_chp.c     | 128 +++++++++++++++++++++++++
 drivers/s390/cio/vfio_ccw_cp.c      |   4 +-
 drivers/s390/cio/vfio_ccw_drv.c     | 140 ++++++++++++++++++++++++++--
 drivers/s390/cio/vfio_ccw_fsm.c     |   8 +-
 drivers/s390/cio/vfio_ccw_ops.c     |  65 +++++++++----
 drivers/s390/cio/vfio_ccw_private.h |  11 +++
 drivers/s390/cio/vfio_ccw_trace.c   |   1 +
 drivers/s390/cio/vfio_ccw_trace.h   |  30 ++++++
 include/uapi/linux/vfio.h           |   3 +
 include/uapi/linux/vfio_ccw.h       |  10 ++
 11 files changed, 366 insertions(+), 36 deletions(-)
 create mode 100644 drivers/s390/cio/vfio_ccw_chp.c
```
#### [PATCH v5 00/24] mm/gup: track dma-pinned pages: FOLL_PIN
##### From: John Hubbard <jhubbard@nvidia.com>

```c
From patchwork Fri Nov 15 05:53:16 2019
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: John Hubbard <jhubbard@nvidia.com>
X-Patchwork-Id: 11245103
Return-Path: <SRS0=Hm6W=ZH=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id E0A2517E0
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 15 Nov 2019 05:56:46 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id AEFA12073B
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 15 Nov 2019 05:56:46 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=nvidia.com header.i=@nvidia.com
 header.b="rgXmOvqJ"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727881AbfKOF4i (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 15 Nov 2019 00:56:38 -0500
Received: from hqemgate16.nvidia.com ([216.228.121.65]:10678 "EHLO
        hqemgate16.nvidia.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1727239AbfKOFx4 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 15 Nov 2019 00:53:56 -0500
Received: from hqpgpgate101.nvidia.com (Not Verified[216.228.121.13]) by
 hqemgate16.nvidia.com (using TLS: TLSv1.2, DES-CBC3-SHA)
        id <B5dce3d680000>; Thu, 14 Nov 2019 21:53:44 -0800
Received: from hqmail.nvidia.com ([172.20.161.6])
  by hqpgpgate101.nvidia.com (PGP Universal service);
  Thu, 14 Nov 2019 21:53:44 -0800
X-PGP-Universal: processed;
        by hqpgpgate101.nvidia.com on Thu, 14 Nov 2019 21:53:44 -0800
Received: from HQMAIL109.nvidia.com (172.20.187.15) by HQMAIL107.nvidia.com
 (172.20.187.13) with Microsoft SMTP Server (TLS) id 15.0.1473.3; Fri, 15 Nov
 2019 05:53:43 +0000
Received: from HQMAIL105.nvidia.com (172.20.187.12) by HQMAIL109.nvidia.com
 (172.20.187.15) with Microsoft SMTP Server (TLS) id 15.0.1473.3; Fri, 15 Nov
 2019 05:53:43 +0000
Received: from hqnvemgw03.nvidia.com (10.124.88.68) by HQMAIL105.nvidia.com
 (172.20.187.12) with Microsoft SMTP Server (TLS) id 15.0.1473.3 via Frontend
 Transport; Fri, 15 Nov 2019 05:53:43 +0000
Received: from blueforge.nvidia.com (Not Verified[10.110.48.28]) by
 hqnvemgw03.nvidia.com with Trustwave SEG (v7,5,8,10121)
        id <B5dce3d670000>; Thu, 14 Nov 2019 21:53:43 -0800
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
Subject: [PATCH v5 00/24] mm/gup: track dma-pinned pages: FOLL_PIN
Date: Thu, 14 Nov 2019 21:53:16 -0800
Message-ID: <20191115055340.1825745-1-jhubbard@nvidia.com>
X-Mailer: git-send-email 2.24.0
MIME-Version: 1.0
X-NVConfidentiality: public
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=nvidia.com; s=n1;
        t=1573797224; bh=EIIdjw6QQ9kSONnEf59U1mlHiT9Q6HqodmatoE1cjqA=;
        h=X-PGP-Universal:From:To:CC:Subject:Date:Message-ID:X-Mailer:
         MIME-Version:X-NVConfidentiality:Content-Type:
         Content-Transfer-Encoding;
        b=rgXmOvqJLUo/ZNL6R7UkGzxvqCKE5WKHqMmP0+iUXVkRb9nVOvZtuUaXsxx+g0hvw
         USCml0g4Xj9gnMThzuGP0XooWuUgL3BZi8rN9HnLsSF/ZfKGE9JK9ODF+1j4xKGKKx
         Kjd8uP62IYmf+IaKtfXpbNOVkq4BJ50LTRBKNV1Ev1yyj4mYvamUtFK4O/EC89p79d
         kWkvXX5AzRiTRcobYhC67nR/ylU+VkX5dx/i83HqhrWpLHm+6AY5RXPlgFGHo27Z9Y
         kPbE6a2d0M0lCnv7dwu2CqvWyQ4S7nTXoE+6eNPxeKnYzuEwgwKV+QllT6GsMJ4wGz
         VafELb6SBcMhg==
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Hi,

Please note that two of these patches are also out for review
separately, and may go in earlier than this series. This series
requires those, so to ease review and testing, they are also
included here: patches 4 and 5, the devmap cleanups.

There is a git repo and branch, for convenience:

    git@github.com:johnhubbard/linux.git pin_user_pages_tracking_v5

Despite the large number of changes, it does feel like the review
comments are converging, btw.

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
 Documentation/core-api/pin_user_pages.rst   | 233 ++++++++
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
 include/linux/mm.h                          | 155 +++++-
 include/linux/mmzone.h                      |   2 +
 include/linux/page_ref.h                    |  10 +
 mm/gup.c                                    | 561 +++++++++++++++-----
 mm/gup_benchmark.c                          |  74 ++-
 mm/huge_memory.c                            |  54 +-
 mm/hugetlb.c                                |  39 +-
 mm/memremap.c                               |  76 ++-
 mm/process_vm_access.c                      |  28 +-
 mm/vmstat.c                                 |   2 +
 net/xdp/xdp_umem.c                          |   4 +-
 tools/testing/selftests/vm/gup_benchmark.c  |  21 +-
 tools/testing/selftests/vm/run_vmtests      |  22 +
 30 files changed, 1104 insertions(+), 350 deletions(-)
 create mode 100644 Documentation/core-api/pin_user_pages.rst
```
