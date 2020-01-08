#### [PATCH v12 01/22] mm/gup: factor out duplicate code from four routines
##### From: John Hubbard <jhubbard@nvidia.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 8bit
X-Patchwork-Submitter: John Hubbard <jhubbard@nvidia.com>
X-Patchwork-Id: 11322169
Return-Path: <SRS0=92ZW=24=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 1BB9E930
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue,  7 Jan 2020 22:47:59 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id DF2202081E
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue,  7 Jan 2020 22:47:58 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=nvidia.com header.i=@nvidia.com
 header.b="rh11n4oa"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727726AbgAGWqM (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 7 Jan 2020 17:46:12 -0500
Received: from hqnvemgate24.nvidia.com ([216.228.121.143]:11357 "EHLO
        hqnvemgate24.nvidia.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1727518AbgAGWqG (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 7 Jan 2020 17:46:06 -0500
Received: from hqpgpgate102.nvidia.com (Not Verified[216.228.121.13]) by
 hqnvemgate24.nvidia.com (using TLS: TLSv1.2, DES-CBC3-SHA)
        id <B5e1509f80001>; Tue, 07 Jan 2020 14:45:12 -0800
Received: from hqmail.nvidia.com ([172.20.161.6])
  by hqpgpgate102.nvidia.com (PGP Universal service);
  Tue, 07 Jan 2020 14:46:00 -0800
X-PGP-Universal: processed;
        by hqpgpgate102.nvidia.com on Tue, 07 Jan 2020 14:46:00 -0800
Received: from HQMAIL107.nvidia.com (172.20.187.13) by HQMAIL107.nvidia.com
 (172.20.187.13) with Microsoft SMTP Server (TLS) id 15.0.1473.3; Tue, 7 Jan
 2020 22:46:00 +0000
Received: from hqnvemgw03.nvidia.com (10.124.88.68) by HQMAIL107.nvidia.com
 (172.20.187.13) with Microsoft SMTP Server (TLS) id 15.0.1473.3 via Frontend
 Transport; Tue, 7 Jan 2020 22:46:00 +0000
Received: from blueforge.nvidia.com (Not Verified[10.110.48.28]) by
 hqnvemgw03.nvidia.com with Trustwave SEG (v7,5,8,10121)
        id <B5e150a270005>; Tue, 07 Jan 2020 14:45:59 -0800
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
 LKML <linux-kernel@vger.kernel.org>, John Hubbard <jhubbard@nvidia.com>,
 Christoph Hellwig <hch@lst.de>,
 "Aneesh Kumar K . V" <aneesh.kumar@linux.ibm.com>
Subject: [PATCH v12 01/22] mm/gup: factor out duplicate code from four
 routines
Date: Tue, 7 Jan 2020 14:45:37 -0800
Message-ID: <20200107224558.2362728-2-jhubbard@nvidia.com>
X-Mailer: git-send-email 2.24.1
In-Reply-To: <20200107224558.2362728-1-jhubbard@nvidia.com>
References: <20200107224558.2362728-1-jhubbard@nvidia.com>
MIME-Version: 1.0
X-NVConfidentiality: public
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=nvidia.com; s=n1;
        t=1578437112; bh=3UN+pZEMmKNfRZpugUWk2xqc0GntLXSHLik6fdzsQds=;
        h=X-PGP-Universal:From:To:CC:Subject:Date:Message-ID:X-Mailer:
         In-Reply-To:References:MIME-Version:X-NVConfidentiality:
         Content-Type:Content-Transfer-Encoding;
        b=rh11n4oaBxWFqT8lK+qes4B5xBWDrco6QyD2M2yDm+QCE+vBQ16klE+qS3zQfGzXq
         +qKyTBawgNO5qGQ7ZIXXKfnm4o4JYFvrI9UhRPq3mm7KLBpYIbTL8lzOpAFMxs5WZu
         gONM+uwb608m3ELiQ8GQLAxmAkxyvlQggWH8XGBLcI1kYFai16CTU1o7a5A084zOg3
         rrnPIrSCakAKg5jxbHBxvOTGHf5ZZi16qF4+V2nMym+rgt0MPHjAcqTlB2OnPTyKBP
         MQ1luy1XuSDr1oKu91qrUiCF1gb/vfw5L46WA/jsyc34Ll0oadvtnbj9JQWBIrH/6x
         G98kFBFiMKA2g==
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

There are four locations in gup.c that have a fair amount of code
duplication. This means that changing one requires making the same
changes in four places, not to mention reading the same code four
times, and wondering if there are subtle differences.

Factor out the common code into static functions, thus reducing the
overall line count and the code's complexity.

Also, take the opportunity to slightly improve the efficiency of the
error cases, by doing a mass subtraction of the refcount, surrounded
by get_page()/put_page().

Also, further simplify (slightly), by waiting until the the successful
end of each routine, to increment *nr.

Reviewed-by: Christoph Hellwig <hch@lst.de>
Reviewed-by: Jérôme Glisse <jglisse@redhat.com>
Reviewed-by: Jan Kara <jack@suse.cz>
Cc: Kirill A. Shutemov <kirill@shutemov.name>
Cc: Ira Weiny <ira.weiny@intel.com>
Cc: Christoph Hellwig <hch@lst.de>
Cc: Aneesh Kumar K.V <aneesh.kumar@linux.ibm.com>
Signed-off-by: John Hubbard <jhubbard@nvidia.com>
---
 mm/gup.c | 95 ++++++++++++++++++++++++--------------------------------
 1 file changed, 40 insertions(+), 55 deletions(-)

```
#### [PATCH 1/2] vfio: add mmap/munmap API for page hinting
##### From: weiqi <weiqi4@huawei.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 8bit
X-Patchwork-Submitter: weiqi <weiqi4@huawei.com>
X-Patchwork-Id: 11320969
Return-Path: <SRS0=92ZW=24=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 1BE8514BD
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue,  7 Jan 2020 14:47:11 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id EDF8E24679
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue,  7 Jan 2020 14:47:10 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728200AbgAGOrD (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 7 Jan 2020 09:47:03 -0500
Received: from szxga05-in.huawei.com ([45.249.212.191]:8235 "EHLO huawei.com"
        rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org with ESMTP
        id S1728118AbgAGOrC (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 7 Jan 2020 09:47:02 -0500
Received: from DGGEMS405-HUB.china.huawei.com (unknown [172.30.72.60])
        by Forcepoint Email with ESMTP id 76B47369D94C3378F945;
        Tue,  7 Jan 2020 22:46:59 +0800 (CST)
Received: from localhost (10.177.98.84) by DGGEMS405-HUB.china.huawei.com
 (10.3.19.205) with Microsoft SMTP Server id 14.3.439.0; Tue, 7 Jan 2020
 22:46:52 +0800
From: weiqi <weiqi4@huawei.com>
To: <alexander.h.duyck@linux.intel.com>, <alex.williamson@redhat.com>
CC: <kvm@vger.kernel.org>, <linux-kernel@vger.kernel.org>,
        <pbonzini@redhat.com>, <x86@kernel.org>, wei qi <weiqi4@huawei.com>
Subject: [PATCH 1/2] vfio: add mmap/munmap API for page hinting
Date: Tue, 7 Jan 2020 22:46:38 +0800
Message-ID: <1578408399-20092-2-git-send-email-weiqi4@huawei.com>
X-Mailer: git-send-email 1.8.4.msysgit.0
In-Reply-To: <1578408399-20092-1-git-send-email-weiqi4@huawei.com>
References: <1578408399-20092-1-git-send-email-weiqi4@huawei.com>
MIME-Version: 1.0
X-Originating-IP: [10.177.98.84]
X-CFilter-Loop: Reflected
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: wei qi <weiqi4@huawei.com>

add mmap/munmap API for page hinting.

Signed-off-by: wei qi <weiqi4@huawei.com>
---
 drivers/vfio/vfio.c             | 109 ++++++++++++++++++++++++++++
 drivers/vfio/vfio_iommu_type1.c | 157 +++++++++++++++++++++++++++++++++++++++-
 include/linux/vfio.h            |  17 ++++-
 3 files changed, 280 insertions(+), 3 deletions(-)

```
#### [PATCH v4 01/12] vfio_pci: refine user config reference in vfio-pci module
##### From: Liu Yi L <yi.l.liu@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Liu Yi L <yi.l.liu@intel.com>
X-Patchwork-Id: 11320859
Return-Path: <SRS0=92ZW=24=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 32E81139A
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue,  7 Jan 2020 12:22:10 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 1BDE02081E
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue,  7 Jan 2020 12:22:10 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728000AbgAGMVG (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 7 Jan 2020 07:21:06 -0500
Received: from mga09.intel.com ([134.134.136.24]:13867 "EHLO mga09.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1727814AbgAGMVG (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 7 Jan 2020 07:21:06 -0500
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from fmsmga006.fm.intel.com ([10.253.24.20])
  by orsmga102.jf.intel.com with ESMTP/TLS/DHE-RSA-AES256-GCM-SHA384;
 07 Jan 2020 04:21:05 -0800
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.69,406,1571727600";
   d="scan'208";a="422475991"
Received: from iov2.bj.intel.com ([10.238.145.72])
  by fmsmga006.fm.intel.com with ESMTP; 07 Jan 2020 04:21:03 -0800
From: Liu Yi L <yi.l.liu@intel.com>
To: alex.williamson@redhat.com, kwankhede@nvidia.com
Cc: linux-kernel@vger.kernel.org, kvm@vger.kernel.org,
        kevin.tian@intel.com, joro@8bytes.org, peterx@redhat.com,
        baolu.lu@linux.intel.com, Liu Yi L <yi.l.liu@intel.com>
Subject: [PATCH v4 01/12] vfio_pci: refine user config reference in vfio-pci
 module
Date: Tue,  7 Jan 2020 20:01:38 +0800
Message-Id: <1578398509-26453-2-git-send-email-yi.l.liu@intel.com>
X-Mailer: git-send-email 2.7.4
In-Reply-To: <1578398509-26453-1-git-send-email-yi.l.liu@intel.com>
References: <1578398509-26453-1-git-send-email-yi.l.liu@intel.com>
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This patch adds three fields in struct vfio_pci_device to pass the user
configurations of vfio-pci.ko module to some functions which could be
common in future usage. The values stored in struct vfio_pci_device will
be initiated in probe and refreshed in device open phase to allow runtime
modifications to parameters. e.g. disable_idle_d3 and nointxmask.

Cc: Kevin Tian <kevin.tian@intel.com>
Cc: Lu Baolu <baolu.lu@linux.intel.com>
Signed-off-by: Liu Yi L <yi.l.liu@intel.com>
---
 drivers/vfio/pci/vfio_pci.c         | 37 ++++++++++++++++++++++++++-----------
 drivers/vfio/pci/vfio_pci_private.h |  8 ++++++++
 2 files changed, 34 insertions(+), 11 deletions(-)

```
