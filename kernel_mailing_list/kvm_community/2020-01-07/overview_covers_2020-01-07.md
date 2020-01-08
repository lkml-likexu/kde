

#### [PATCH v4 00/12] vfio_pci: wrap pci device as a mediated device
##### From: Liu Yi L <yi.l.liu@intel.com>

```c
From patchwork Tue Jan  7 12:01:37 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Liu Yi L <yi.l.liu@intel.com>
X-Patchwork-Id: 11320861
Return-Path: <SRS0=92ZW=24=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 4DB27139A
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue,  7 Jan 2020 12:22:14 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 36F9A2081E
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue,  7 Jan 2020 12:22:14 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727965AbgAGMVE (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 7 Jan 2020 07:21:04 -0500
Received: from mga09.intel.com ([134.134.136.24]:13867 "EHLO mga09.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1727814AbgAGMVE (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 7 Jan 2020 07:21:04 -0500
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from fmsmga006.fm.intel.com ([10.253.24.20])
  by orsmga102.jf.intel.com with ESMTP/TLS/DHE-RSA-AES256-GCM-SHA384;
 07 Jan 2020 04:21:03 -0800
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.69,406,1571727600";
   d="scan'208";a="422475978"
Received: from iov2.bj.intel.com ([10.238.145.72])
  by fmsmga006.fm.intel.com with ESMTP; 07 Jan 2020 04:21:01 -0800
From: Liu Yi L <yi.l.liu@intel.com>
To: alex.williamson@redhat.com, kwankhede@nvidia.com
Cc: linux-kernel@vger.kernel.org, kvm@vger.kernel.org,
        kevin.tian@intel.com, joro@8bytes.org, peterx@redhat.com,
        baolu.lu@linux.intel.com
Subject: [PATCH v4 00/12] vfio_pci: wrap pci device as a mediated device
Date: Tue,  7 Jan 2020 20:01:37 +0800
Message-Id: <1578398509-26453-1-git-send-email-yi.l.liu@intel.com>
X-Mailer: git-send-email 2.7.4
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This patchset aims to add a vfio-pci-like meta driver as a demo
user of the vfio changes introduced in "vfio/mdev: IOMMU aware
mediated device" patchset from Baolu Lu. Besides the test purpose,
per Alex's comments, it could also be a good base driver for
experimenting with device specific mdev migration.

Specific interface tested in this proposal:
 *) int mdev_set_iommu_device(struct device *dev,
 				struct device *iommu_device)
    introduced in the patch as below:
    "[PATCH v5 6/8] vfio/mdev: Add iommu related member in mdev_device"

Patch Overview:
 *) patch 1 ~ 9: code refactor for existing vfio-pci module
                 move the common codes from vfio_pci.c to
                 vfio_pci_common.c
 *) patch 10: build vfio-pci-common.ko
 *) patch 11: add initial vfio-mdev-pci sample driver
 *) patch 12: refine the sample driver

Links:
 *) Link of "vfio/mdev: IOMMU aware mediated device"
         https://lwn.net/Articles/780522/
 *) Previous versions:
         Patch v3: https://lkml.org/lkml/2019/11/22/1558
         Patch v2: https://lkml.org/lkml/2019/9/6/115
         Patch v1: https://www.spinics.net/lists/kvm/msg188952.html
         RFC v3: https://lkml.org/lkml/2019/4/24/495
         RFC v2: https://lkml.org/lkml/2019/3/13/113
         RFC v1: https://lkml.org/lkml/2019/3/4/529
 *) may try it with the codes in below repo
    https://github.com/luxis1999/vfio-mdev-pci-sample-driver.git : v5.5-rc5-pci-mdev

Please feel free give your comments.

Thanks,
Yi Liu

Change log:
  patch v3 -> patch v4:
  - switched the sequence of
    "vfio_pci: move vfio_pci_is_vga/vfio_vga_disabled to header"
    and
    "vfio_pci: refine user config reference in vfio-pci module".
  - refined "vfio_pci: refine vfio_pci_driver reference in vfio_pci.c"
    per Alex's comments.
  - split the vfio_pci_private.h file to be two files.
  - Build vfio_pci_common.c to be vfio-pci-common.ko for code sharing
    outside of drivers/vfio/pci/.
  - moved vfio-mdev-pci driver to under samples/.
  - dropped "vfio/pci: protect cap/ecap_perm bits alloc/free" as new
    version builds vfio_pci_common.c to be a kernel module.

  patch v2 -> patch v3:
  - refresh the disable_idle_d3, disable_vga and nointxmask config
    according to user config in device open.
  - add a semaphore around the vfio-pci cap/ecap perm bits allocation/free
  - drop the non-singleton iommu group support to keep it simple as it's
    a sample driver for now.

  patch v1 -> patch v2:
  - the sample driver implementation refined
  - the sample driver can work on non-singleton iommu groups
  - the sample driver can work with vfio-pci, devices from a non-singleton
    group can either be bound to vfio-mdev-pci or vfio-pci, and the
    assignment of this group still follows current vfio assignment rule.

  RFC v3 -> patch v1:
  - split the patchset from 3 patches to 9 patches to better demonstrate
    the changes step by step

  rfc v2->v3:
  - use vfio-mdev-pci instead of vfio-pci-mdev
  - place the new driver under drivers/vfio/pci while define
    Kconfig in samples/Kconfig to clarify it is a sample driver

  rfc v1->v2:
  - instead of adding kernel option to existing vfio-pci
    module in v1, v2 follows Alex's suggestion to add a
    separate vfio-pci-mdev module.
  - new patchset subject: "vfio/pci: wrap pci device as a mediated device"

Alex Williamson (1):
  samples: refine vfio-mdev-pci driver

Liu Yi L (11):
  vfio_pci: refine user config reference in vfio-pci module
  vfio_pci: move vfio_pci_is_vga/vfio_vga_disabled to header file
  vfio_pci: refine vfio_pci_driver reference in vfio_pci.c
  vfio_pci: make common functions be extern
  vfio_pci: duplicate vfio_pci.c
  vfio_pci: shrink vfio_pci_common.c
  vfio_pci: shrink vfio_pci.c
  vfio_pci: duplicate vfio_pci_private.h to include/linux
  vfio: split vfio_pci_private.h into two files
  vfio: build vfio_pci_common.c into a kernel module
  samples: add vfio-mdev-pci driver

 drivers/vfio/pci/Kconfig              |    9 +-
 drivers/vfio/pci/Makefile             |   10 +-
 drivers/vfio/pci/vfio_pci.c           | 1477 +-------------------------------
 drivers/vfio/pci/vfio_pci_common.c    | 1512 +++++++++++++++++++++++++++++++++
 drivers/vfio/pci/vfio_pci_private.h   |   94 +-
 include/linux/vfio_pci_common.h       |  154 ++++
 samples/Kconfig                       |   10 +
 samples/Makefile                      |    1 +
 samples/vfio-mdev-pci/Makefile        |    4 +
 samples/vfio-mdev-pci/vfio_mdev_pci.c |  420 +++++++++
 10 files changed, 2128 insertions(+), 1563 deletions(-)
 create mode 100644 drivers/vfio/pci/vfio_pci_common.c
 create mode 100644 include/linux/vfio_pci_common.h
 create mode 100644 samples/vfio-mdev-pci/Makefile
 create mode 100644 samples/vfio-mdev-pci/vfio_mdev_pci.c
```
#### [PATCH 0/2] page hinting add passthrough support
##### From: weiqi <weiqi4@huawei.com>
From: wei qi <weiqi4@huawei.com>

```c
From patchwork Tue Jan  7 14:46:37 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: weiqi <weiqi4@huawei.com>
X-Patchwork-Id: 11320967
Return-Path: <SRS0=92ZW=24=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 1C62A1580
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue,  7 Jan 2020 14:47:08 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 046E12087F
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue,  7 Jan 2020 14:47:08 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728301AbgAGOrE (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 7 Jan 2020 09:47:04 -0500
Received: from szxga07-in.huawei.com ([45.249.212.35]:59600 "EHLO huawei.com"
        rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org with ESMTP
        id S1727975AbgAGOrE (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 7 Jan 2020 09:47:04 -0500
Received: from DGGEMS406-HUB.china.huawei.com (unknown [172.30.72.60])
        by Forcepoint Email with ESMTP id 3AE2830EE6EF2E3D4DC3;
        Tue,  7 Jan 2020 22:46:54 +0800 (CST)
Received: from localhost (10.177.98.84) by DGGEMS406-HUB.china.huawei.com
 (10.3.19.206) with Microsoft SMTP Server id 14.3.439.0; Tue, 7 Jan 2020
 22:46:46 +0800
From: weiqi <weiqi4@huawei.com>
To: <alexander.h.duyck@linux.intel.com>, <alex.williamson@redhat.com>
CC: <kvm@vger.kernel.org>, <linux-kernel@vger.kernel.org>,
        <pbonzini@redhat.com>, <x86@kernel.org>, wei qi <weiqi4@huawei.com>
Subject: [PATCH 0/2] page hinting add passthrough support
Date: Tue, 7 Jan 2020 22:46:37 +0800
Message-ID: <1578408399-20092-1-git-send-email-weiqi4@huawei.com>
X-Mailer: git-send-email 1.8.4.msysgit.0
MIME-Version: 1.0
X-Originating-IP: [10.177.98.84]
X-CFilter-Loop: Reflected
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: wei qi <weiqi4@huawei.com>


I just implemented dynamically updating the iommu table to support pass-through,
It seen to work fine.

Test:
start a 4G vm with 2M hugetlb and ixgbevf passthrough, 
    GuestOS: linux-5.2.6 + 	(mm / virtio: Provide support for free page reporting)
    HostOS: 5.5-rc4
    Host: Intel(R) Xeon(R) Gold 6161 CPU @ 2.20GHz 

after enable page hinting, free pages at GuestOS can be free at host. 


before,
 # cat /sys/devices/system/node/node*/hugepages/hugepages-2048kB/free_hugepages 
 5620
 5620
after start VM,
 # numastat -c qemu

 Per-node process memory usage (in MBs)
 PID              Node 0 Node 1 Total
 ---------------  ------ ------ -----
 24463 (qemu_hotr      6      6    12
 24479 (qemu_tls_      0      8     8
 70718 (qemu-syst     58    539   597
 ---------------  ------ ------ -----
 Total                64    553   616
 # cat /sys/devices/system/node/node*/hugepages/hugepages-2048kB/free_hugepages 
 5595
 5366

the modify at qemu,
 +int kvm_discard_range(struct kvm_discard_msg discard_msg)  
 +{
 +    return kvm_vm_ioctl(kvm_state, KVM_DISCARD_RANGE, &discard_msg);
 +}

 static void virtio_balloon_handle_report(VirtIODevice *vdev, VirtQueue *vq)
 {
            ..................
 +           discard_msg.in_addr = elem->in_addr[i];
 +           discard_msg.iov_len = elem->in_sg[i].iov_len;

            ram_block_discard_range(rb, ram_offset, size);
 +           kvm_discard_range(discard_msg);

then, further test network bandwidth, performance seem ok.
 
Is there any hidden problem in this implementation?
And, is there plan to support pass-throughyour?

wei qi (2):
  vfio: add mmap/munmap API for page hinting
  KVM: add support for page hinting

 arch/x86/kvm/mmu/mmu.c          |  79 ++++++++++++++++++++
 arch/x86/kvm/x86.c              |  96 ++++++++++++++++++++++++
 drivers/vfio/vfio.c             | 109 ++++++++++++++++++++++++++++
 drivers/vfio/vfio_iommu_type1.c | 157 +++++++++++++++++++++++++++++++++++++++-
 include/linux/kvm_host.h        |  41 +++++++++++
 include/linux/vfio.h            |  17 ++++-
 include/uapi/linux/kvm.h        |   7 ++
 virt/kvm/vfio.c                 |  11 ---
 8 files changed, 503 insertions(+), 14 deletions(-)
```
#### [PATCH v12 00/22] mm/gup: prereqs to track dma-pinned pages: FOLL_PIN
##### From: John Hubbard <jhubbard@nvidia.com>

```c
From patchwork Tue Jan  7 22:45:36 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: John Hubbard <jhubbard@nvidia.com>
X-Patchwork-Id: 11322269
Return-Path: <SRS0=92ZW=24=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 8E5E16C1
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue,  7 Jan 2020 22:49:13 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 5150B2075A
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue,  7 Jan 2020 22:49:13 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=nvidia.com header.i=@nvidia.com
 header.b="q07jqBkO"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728370AbgAGWsw (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 7 Jan 2020 17:48:52 -0500
Received: from hqnvemgate25.nvidia.com ([216.228.121.64]:5120 "EHLO
        hqnvemgate25.nvidia.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1727174AbgAGWqF (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 7 Jan 2020 17:46:05 -0500
Received: from hqpgpgate101.nvidia.com (Not Verified[216.228.121.13]) by
 hqnvemgate25.nvidia.com (using TLS: TLSv1.2, DES-CBC3-SHA)
        id <B5e150a160001>; Tue, 07 Jan 2020 14:45:42 -0800
Received: from hqmail.nvidia.com ([172.20.161.6])
  by hqpgpgate101.nvidia.com (PGP Universal service);
  Tue, 07 Jan 2020 14:46:00 -0800
X-PGP-Universal: processed;
        by hqpgpgate101.nvidia.com on Tue, 07 Jan 2020 14:46:00 -0800
Received: from HQMAIL105.nvidia.com (172.20.187.12) by HQMAIL101.nvidia.com
 (172.20.187.10) with Microsoft SMTP Server (TLS) id 15.0.1473.3; Tue, 7 Jan
 2020 22:45:59 +0000
Received: from hqnvemgw03.nvidia.com (10.124.88.68) by HQMAIL105.nvidia.com
 (172.20.187.12) with Microsoft SMTP Server (TLS) id 15.0.1473.3 via Frontend
 Transport; Tue, 7 Jan 2020 22:45:59 +0000
Received: from blueforge.nvidia.com (Not Verified[10.110.48.28]) by
 hqnvemgw03.nvidia.com with Trustwave SEG (v7,5,8,10121)
        id <B5e150a270002>; Tue, 07 Jan 2020 14:45:59 -0800
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
 "Kirill A . Shutemov" <kirill@shutemov.name>,
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
Subject: [PATCH v12 00/22] mm/gup: prereqs to track dma-pinned pages: FOLL_PIN
Date: Tue, 7 Jan 2020 14:45:36 -0800
Message-ID: <20200107224558.2362728-1-jhubbard@nvidia.com>
X-Mailer: git-send-email 2.24.1
MIME-Version: 1.0
X-NVConfidentiality: public
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=nvidia.com; s=n1;
        t=1578437143; bh=e35VbuH+5Gvq6hzdX1wkd7Gwo0Ev1/RydrM5ojZBtqQ=;
        h=X-PGP-Universal:From:To:CC:Subject:Date:Message-ID:X-Mailer:
         MIME-Version:X-NVConfidentiality:Content-Type:
         Content-Transfer-Encoding;
        b=q07jqBkOQ+8W+FWIGxHzDq9+K2aqK0l1baYh9tHJ5YgbVqzpzGrCVUbh8IIOz9ivr
         N8DeNKRxsksmaQmBj8DLUTfJNvVvliRP3A7UvdrQSBrUtqohAPvBbP6gW+d+uir7zj
         N71u+jUUFG3a29ne3zY3zxuWMeCOBJOlbx0/C+htFPSQNDX+WeFBXBUo/FQBTcKPK+
         fsKaVOXRA1UshywnsPhWCDuIhCymH6YPuMQwJ7/7x7UJimvasG4+G3pmoTyD3poYdy
         39n4NbY3ownCfiBLFE6x3ANsClgsjxgyIpUe1k8mz3p84SQo7eboSdCD6jky2z1c7L
         WmXHM0fQFkghw==
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Hi,

The "track FOLL_PIN pages" would have been the very next patch, but it is
not included here because I'm still debugging a bug report from Leon.
Let's get all of the prerequisite work (it's been reviewed) into the tree
so that future reviews are easier. It's clear that any fixes that are
required to the tracking patch, won't affect these patches here.

This implements an API naming change (put_user_page*() -->
unpin_user_page*()), and also adds FOLL_PIN page support, up to
*but not including* actually tracking FOLL_PIN pages. It extends
the FOLL_PIN support to a few select subsystems. More subsystems will
be added in follow up work.

Christoph Hellwig, a point of interest:

a) I've moved the bulk of the code out of the inline functions, as
   requested, for the devmap changes (patch 4: "mm: devmap: refactor
   1-based refcounting for ZONE_DEVICE pages").

Changes since v11: Fixes resulting from Kirill Shutemov's review, plus
a fix for a kbuild robot-reported warning.

* Only include the first 22 patches: up to, but not including, the "track
  FOLL_PIN pages" patch.

* Improved the efficiency of put_compound_head(), by avoiding get_page()
  entirely, and instead doing the mass subtraction on one less than
  refs, followed by a final put_page().

* Got rid of the forward declaration of __gup_longterm_locked(), by
  moving get_user_pages_remote() further down in gup.c

* Got rid of a redundant page_is_devmap_managed() call, and simplified
  put_devmap_managed_page() as part of that small cleanup.

* Changed put_devmap_managed_page() to do an early out if the page is
  not devmap managed. This saves an indentation level.

* Applied the same type of change to __unpin_devmap_managed_user_page(),
  which has the same checks.

* Changed release_pages() to handle the changed put_devmap_managed_page()
  API.

* Removed EXPORT_SYMBOL(free_devmap_managed_page), as it is not required,
  after the other refactoring.

* Fixed a kbuild robot sparse warning: added "static" to
  try_pin_compound_head()'s declaration.

There is a git repo and branch, for convenience:

    git@github.com:johnhubbard/linux.git pin_user_pages_tracking_v8

For the remaining list of "changes since version N", those are all in
v11, which is here:

  https://lore.kernel.org/r/20191216222537.491123-1-jhubbard@nvidia.com

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
    * infiniband: Ran rdma-core tests: rdma-core/build/bin/run_tests.py
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

John Hubbard (21):
  mm/gup: factor out duplicate code from four routines
  mm/gup: move try_get_compound_head() to top, fix minor issues
  mm: devmap: refactor 1-based refcounting for ZONE_DEVICE pages
  goldish_pipe: rename local pin_user_pages() routine
  mm: fix get_user_pages_remote()'s handling of FOLL_LONGTERM
  vfio: fix FOLL_LONGTERM use, simplify get_user_pages_remote() call
  mm/gup: allow FOLL_FORCE for get_user_pages_fast()
  IB/umem: use get_user_pages_fast() to pin DMA pages
  media/v4l2-core: set pages dirty upon releasing DMA buffers
  mm/gup: introduce pin_user_pages*() and FOLL_PIN
  goldish_pipe: convert to pin_user_pages() and put_user_page()
  IB/{core,hw,umem}: set FOLL_PIN via pin_user_pages*(), fix up ODP
  mm/process_vm_access: set FOLL_PIN via pin_user_pages_remote()
  drm/via: set FOLL_PIN via pin_user_pages_fast()
  fs/io_uring: set FOLL_PIN via pin_user_pages()
  net/xdp: set FOLL_PIN via pin_user_pages()
  media/v4l2-core: pin_user_pages (FOLL_PIN) and put_user_page()
    conversion
  vfio, mm: pin_user_pages (FOLL_PIN) and put_user_page() conversion
  powerpc: book3s64: convert to pin_user_pages() and put_user_page()
  mm/gup_benchmark: use proper FOLL_WRITE flags instead of hard-coding
    "1"
  mm, tree-wide: rename put_user_page*() to unpin_user_page*()

 Documentation/core-api/index.rst            |   1 +
 Documentation/core-api/pin_user_pages.rst   | 232 +++++++++
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
 include/linux/mm.h                          |  95 +++-
 mm/gup.c                                    | 495 ++++++++++++--------
 mm/gup_benchmark.c                          |   9 +-
 mm/memremap.c                               |  75 ++-
 mm/process_vm_access.c                      |  28 +-
 mm/swap.c                                   |  27 +-
 net/xdp/xdp_umem.c                          |   4 +-
 tools/testing/selftests/vm/gup_benchmark.c  |   6 +-
 25 files changed, 762 insertions(+), 380 deletions(-)
 create mode 100644 Documentation/core-api/pin_user_pages.rst
```
