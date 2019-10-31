#### [PATCH V6 1/6] mdev: class id support
##### From: Jason Wang <jasowang@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Jason Wang <jasowang@redhat.com>
X-Patchwork-Id: 11219035
Return-Path: <SRS0=Bujf=YX=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 49AE3139A
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 30 Oct 2019 06:46:02 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 148952087F
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 30 Oct 2019 06:46:02 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="dJCuWacs"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727296AbfJ3Gp7 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 30 Oct 2019 02:45:59 -0400
Received: from us-smtp-delivery-1.mimecast.com ([207.211.31.120]:50876 "EHLO
        us-smtp-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org
        with ESMTP id S1726555AbfJ3Gp7 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 30 Oct 2019 02:45:59 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1572417957;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:content-type:content-type:
         content-transfer-encoding:content-transfer-encoding:
         in-reply-to:in-reply-to:references:references;
        bh=P919cs9kLqhOLxjmVpL/0WVat63lfGNnCbk/tFscCiY=;
        b=dJCuWacsQByhYXC0I80O/pavFElsy1qApNmPFu4fmaGqHB/TkxUkCY94vn6YpzvcLFFXqG
        NklRK8M0jpM8rtdstEE9a9PoIkOsfwhH0//G2cYQ9gvRrf1r1wXkcV0y5p4RD0GTpHqmh6
        D+eT2mBKy5IVhx5OS4kJw8aKnA7chec=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-31-WNU8rwzpM5ajq7bmmPQLKw-1; Wed, 30 Oct 2019 02:45:55 -0400
Received: from smtp.corp.redhat.com (int-mx04.intmail.prod.int.phx2.redhat.com
 [10.5.11.14])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 7A23B107AD28;
        Wed, 30 Oct 2019 06:45:51 +0000 (UTC)
Received: from jason-ThinkPad-X1-Carbon-6th.redhat.com
 (ovpn-12-223.pek2.redhat.com [10.72.12.223])
        by smtp.corp.redhat.com (Postfix) with ESMTP id DE8905D9C3;
        Wed, 30 Oct 2019 06:45:20 +0000 (UTC)
From: Jason Wang <jasowang@redhat.com>
To: kvm@vger.kernel.org, linux-s390@vger.kernel.org,
        linux-kernel@vger.kernel.org, dri-devel@lists.freedesktop.org,
        intel-gfx@lists.freedesktop.org,
        intel-gvt-dev@lists.freedesktop.org, kwankhede@nvidia.com,
        alex.williamson@redhat.com, mst@redhat.com, tiwei.bie@intel.com
Cc: virtualization@lists.linux-foundation.org, netdev@vger.kernel.org,
        cohuck@redhat.com, maxime.coquelin@redhat.com,
        cunming.liang@intel.com, zhihong.wang@intel.com,
        rob.miller@broadcom.com, xiao.w.wang@intel.com,
        haotian.wang@sifive.com, zhenyuw@linux.intel.com,
        zhi.a.wang@intel.com, jani.nikula@linux.intel.com,
        joonas.lahtinen@linux.intel.com, rodrigo.vivi@intel.com,
        airlied@linux.ie, daniel@ffwll.ch, farman@linux.ibm.com,
        pasic@linux.ibm.com, sebott@linux.ibm.com, oberpar@linux.ibm.com,
        heiko.carstens@de.ibm.com, gor@linux.ibm.com,
        borntraeger@de.ibm.com, akrowiak@linux.ibm.com,
        freude@linux.ibm.com, lingshan.zhu@intel.com, idos@mellanox.com,
        eperezma@redhat.com, lulu@redhat.com, parav@mellanox.com,
        christophe.de.dinechin@gmail.com, kevin.tian@intel.com,
        stefanha@redhat.com, Jason Wang <jasowang@redhat.com>
Subject: [PATCH V6 1/6] mdev: class id support
Date: Wed, 30 Oct 2019 14:44:39 +0800
Message-Id: <20191030064444.21166-2-jasowang@redhat.com>
In-Reply-To: <20191030064444.21166-1-jasowang@redhat.com>
References: <20191030064444.21166-1-jasowang@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.14
X-MC-Unique: WNU8rwzpM5ajq7bmmPQLKw-1
X-Mimecast-Spam-Score: 0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Mdev bus only supports vfio driver right now, so it doesn't implement
match method. But in the future, we may add drivers other than vfio,
the first driver could be virtio-mdev. This means we need to add
device class id support in bus match method to pair the mdev device
and mdev driver correctly.

So this patch adds id_table to mdev_driver and class_id for mdev
device with the match method for mdev bus.

Signed-off-by: Jason Wang <jasowang@redhat.com>
---
 .../driver-api/vfio-mediated-device.rst       |  5 ++++
 drivers/gpu/drm/i915/gvt/kvmgt.c              |  1 +
 drivers/s390/cio/vfio_ccw_ops.c               |  1 +
 drivers/s390/crypto/vfio_ap_ops.c             |  1 +
 drivers/vfio/mdev/mdev_core.c                 | 16 ++++++++++++
 drivers/vfio/mdev/mdev_driver.c               | 25 +++++++++++++++++++
 drivers/vfio/mdev/mdev_private.h              |  1 +
 drivers/vfio/mdev/vfio_mdev.c                 |  6 +++++
 include/linux/mdev.h                          |  8 ++++++
 include/linux/mod_devicetable.h               |  8 ++++++
 samples/vfio-mdev/mbochs.c                    |  1 +
 samples/vfio-mdev/mdpy.c                      |  1 +
 samples/vfio-mdev/mtty.c                      |  1 +
 13 files changed, 75 insertions(+)

```
#### [PATCH 01/19] mm/gup: pass flags arg to __gup_device_* functions
##### From: John Hubbard <jhubbard@nvidia.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: John Hubbard <jhubbard@nvidia.com>
X-Patchwork-Id: 11220435
Return-Path: <SRS0=Bujf=YX=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id B34F314DB
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 30 Oct 2019 22:53:02 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 86F5B2087F
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 30 Oct 2019 22:53:02 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=nvidia.com header.i=@nvidia.com
 header.b="LHZ6lU3b"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727595AbfJ3Wto (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 30 Oct 2019 18:49:44 -0400
Received: from hqemgate16.nvidia.com ([216.228.121.65]:10796 "EHLO
        hqemgate16.nvidia.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1727165AbfJ3Wtn (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 30 Oct 2019 18:49:43 -0400
Received: from hqpgpgate102.nvidia.com (Not Verified[216.228.121.13]) by
 hqemgate16.nvidia.com (using TLS: TLSv1.2, DES-CBC3-SHA)
        id <B5dba13850000>; Wed, 30 Oct 2019 15:49:41 -0700
Received: from hqmail.nvidia.com ([172.20.161.6])
  by hqpgpgate102.nvidia.com (PGP Universal service);
  Wed, 30 Oct 2019 15:49:35 -0700
X-PGP-Universal: processed;
        by hqpgpgate102.nvidia.com on Wed, 30 Oct 2019 15:49:35 -0700
Received: from HQMAIL111.nvidia.com (172.20.187.18) by HQMAIL105.nvidia.com
 (172.20.187.12) with Microsoft SMTP Server (TLS) id 15.0.1473.3; Wed, 30 Oct
 2019 22:49:35 +0000
Received: from rnnvemgw01.nvidia.com (10.128.109.123) by HQMAIL111.nvidia.com
 (172.20.187.18) with Microsoft SMTP Server (TLS) id 15.0.1473.3 via Frontend
 Transport; Wed, 30 Oct 2019 22:49:34 +0000
Received: from blueforge.nvidia.com (Not Verified[10.110.48.28]) by
 rnnvemgw01.nvidia.com with Trustwave SEG (v7,5,8,10121)
        id <B5dba137d0001>; Wed, 30 Oct 2019 15:49:34 -0700
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
 LKML <linux-kernel@vger.kernel.org>, John Hubbard <jhubbard@nvidia.com>,
 "Kirill A . Shutemov" <kirill.shutemov@linux.intel.com>
Subject: [PATCH 01/19] mm/gup: pass flags arg to __gup_device_* functions
Date: Wed, 30 Oct 2019 15:49:12 -0700
Message-ID: <20191030224930.3990755-2-jhubbard@nvidia.com>
X-Mailer: git-send-email 2.23.0
In-Reply-To: <20191030224930.3990755-1-jhubbard@nvidia.com>
References: <20191030224930.3990755-1-jhubbard@nvidia.com>
MIME-Version: 1.0
X-NVConfidentiality: public
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=nvidia.com; s=n1;
        t=1572475781; bh=d7EUGpQRTMvoYc+6+aLdOHouLAD5TlAUer68L/VNpoI=;
        h=X-PGP-Universal:From:To:CC:Subject:Date:Message-ID:X-Mailer:
         In-Reply-To:References:MIME-Version:X-NVConfidentiality:
         Content-Transfer-Encoding:Content-Type;
        b=LHZ6lU3b+Rmuxt6ntgTWgWPO1DjlyJfgSFkeATOM45bmCiGsVgXIRtuRcHVay2m7y
         QkorONll+8JNtmmEP2Ct98iMV9oni8t13QTqaMFchuXeLDFzTcNhK19kYx95+C5Au9
         ze2QMsU3TEAUahyq5IgliLnkeuV5Me50VDXXYGrkbu6XyUmKt/wogCCFoTKEEA1z7c
         c3/5zdaDb9u8RFGw3NMmUBcQNRtDGOl+4IErI5FymIoWyPpeQwvVnUcl9RiCCbNOQE
         /CaCRNf9WNtGpnCVwW6i7NQfkRAktZTVjBFJUZO66X8K050+YYMC6fvZ5jriiMtRSE
         +LYcxSYecvZcg==
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

A subsequent patch requires access to gup flags, so
pass the flags argument through to the __gup_device_*
functions.

Also placate checkpatch.pl by shortening a nearby line.

Cc: Kirill A. Shutemov <kirill.shutemov@linux.intel.com>
Signed-off-by: John Hubbard <jhubbard@nvidia.com>
---
 mm/gup.c | 28 ++++++++++++++++++----------
 1 file changed, 18 insertions(+), 10 deletions(-)

```
#### [kvm-unit-tests PATCH v3 1/6] x86: emulator: use "SSE2" for the target
##### From: Bill Wendling <morbo@google.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Bill Wendling <morbo@google.com>
X-Patchwork-Id: 11220059
Return-Path: <SRS0=Bujf=YX=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 464DC913
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 30 Oct 2019 21:04:31 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 1C11520862
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 30 Oct 2019 21:04:31 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=google.com header.i=@google.com
 header.b="gXb60jE9"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727054AbfJ3VEa (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 30 Oct 2019 17:04:30 -0400
Received: from mail-pf1-f201.google.com ([209.85.210.201]:39253 "EHLO
        mail-pf1-f201.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726749AbfJ3VEa (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 30 Oct 2019 17:04:30 -0400
Received: by mail-pf1-f201.google.com with SMTP id l20so2696506pff.6
        for <kvm@vger.kernel.org>; Wed, 30 Oct 2019 14:04:29 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=date:in-reply-to:message-id:mime-version:references:subject:from:to
         :cc;
        bh=upjAEuFJdt1TLpNgpgQupJ9CCvCrQ2wU04Vj0IjMAHs=;
        b=gXb60jE9rGGecCIJUp0YW459p0D2wHyP/rhiOgFm1XwVu9qHHVDofMQ3kAvjwZGojt
         133ZLoNs5EhAuq7l3t9SumssAKOLIBkUNTjsplliseIog+g5BAF7/oJfQy1uDiBVyI6V
         53tEBdpjDOFEsH5qvu/EyW2lXtWWaedAX8wqDwZPbjQsKhFIlw7M/kby5cyTcr4VC0Wy
         KFUShzJVp3GdRkOKpGgzgl3jha8A7Jtr8fAN5LVrHu+VEZWXn5+yT3V1tdrGkR2wykCd
         22Zm13a8sSTpzLoYSrTYkXNPmoISoY5jtIn9GCb3aBfM4cU3N8KW0GJ6BqWgLffIunVK
         yO/g==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:date:in-reply-to:message-id:mime-version
         :references:subject:from:to:cc;
        bh=upjAEuFJdt1TLpNgpgQupJ9CCvCrQ2wU04Vj0IjMAHs=;
        b=luPHG9HHe/zX5DogU3Mh6H9cHUpe5Ph2w6PRFEFeEY98lAfKVjTqNGxvasBuQBXLyt
         +FM5E2aRX0oMfRoF6QJkOBlnixyInwgDCjENZ/ltExd2kAmsvqvH5rzDFBfhQP0I5gmf
         R5O46V+NHOSw9HFNdvqw7Tk8mMjQcyA+qGrFO1wyroPM4jc+zsAQFc8otOkkyVZVgvjj
         T8yOWTTHzZBWUW4CFr/ptoX1ocNEw/qiD2VTaI3N2pnYARmMVv7QeI0V5W2KqxFIQId7
         gJIOHYwtRsWR+5SACQTm5SqkOXZfQx22XR743CjGMTJyDVDNqJdiMBYUo9MYHkTWmvEi
         leHQ==
X-Gm-Message-State: APjAAAVxjR+G1iAcyKtfwJhhkFen4Gj93cp0P122FQzGlY3Nbf9lrdGo
        hVf5EZ0O1n/aEONrf3bjk78DrSR1gRQtY55HC7i+vvsXN3obNkUZK3XI1RjmhlEgaBWdhKVzJxT
        gcHoGiaH2WsX7gbah2AgCBbf+qjeCiC6MQ6lcSOBk8Mk9gbRdrm8jXQ==
X-Google-Smtp-Source: 
 APXvYqz6psyX3VnEaTeKsc1C9it70gfs7BJaF/5WPERV1ZPXP7aD1wIeieT5JBHtPkGK8fDvKQMfwM3QkA==
X-Received: by 2002:a65:554e:: with SMTP id t14mr1606165pgr.370.1572469468375;
 Wed, 30 Oct 2019 14:04:28 -0700 (PDT)
Date: Wed, 30 Oct 2019 14:04:14 -0700
In-Reply-To: <20191030210419.213407-1-morbo@google.com>
Message-Id: <20191030210419.213407-2-morbo@google.com>
Mime-Version: 1.0
References: <20191015000411.59740-1-morbo@google.com>
 <20191030210419.213407-1-morbo@google.com>
X-Mailer: git-send-email 2.24.0.rc1.363.gb1bccd3e3d-goog
Subject: [kvm-unit-tests PATCH v3 1/6] x86: emulator: use "SSE2" for the
 target
From: Bill Wendling <morbo@google.com>
To: kvm@vger.kernel.org, pbonzini@redhat.com, thuth@redhat.com
Cc: jmattson@google.com, sean.j.christopherson@intel.com,
        Bill Wendling <morbo@google.com>
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The movdqu and movapd instructions are SSE2 instructions. Clang
interprets the __attribute__((target("sse"))) as allowing SSE only
instructions. Using SSE2 instructions cause an error.

Signed-off-by: Bill Wendling <morbo@google.com>
---
 x86/emulator.c | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
#### [PATCH] VFIO: PCI: eliminate unnecessary overhead in vfio_pci_reflck_find
##### From: linmiaohe <linmiaohe@huawei.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: linmiaohe <linmiaohe@huawei.com>
X-Patchwork-Id: 11219457
Return-Path: <SRS0=Bujf=YX=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id A498D1390
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 30 Oct 2019 10:56:53 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 8CDF22087E
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 30 Oct 2019 10:56:53 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726969AbfJ3K4t (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 30 Oct 2019 06:56:49 -0400
Received: from szxga07-in.huawei.com ([45.249.212.35]:59254 "EHLO huawei.com"
        rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org with ESMTP
        id S1726761AbfJ3K4s (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 30 Oct 2019 06:56:48 -0400
Received: from DGGEMS401-HUB.china.huawei.com (unknown [172.30.72.59])
        by Forcepoint Email with ESMTP id AD30DCE6CB8B683BAC3B;
        Wed, 30 Oct 2019 18:56:45 +0800 (CST)
Received: from huawei.com (10.175.105.18) by DGGEMS401-HUB.china.huawei.com
 (10.3.19.201) with Microsoft SMTP Server id 14.3.439.0; Wed, 30 Oct 2019
 18:56:39 +0800
From: linmiaohe <linmiaohe@huawei.com>
To: <alex.williamson@redhat.com>, <cohuck@redhat.com>,
        <eric.auger@redhat.com>, <aik@ozlabs.ru>, <mpe@ellerman.id.au>,
        <bhelgaas@google.com>, <tglx@linutronix.de>, <hexin.op@gmail.com>
CC: <linmiaohe@huawei.com>, <kvm@vger.kernel.org>,
        <linux-kernel@vger.kernel.org>
Subject: [PATCH] VFIO: PCI: eliminate unnecessary overhead in
 vfio_pci_reflck_find
Date: Wed, 30 Oct 2019 18:57:10 +0800
Message-ID: <1572433030-6267-1-git-send-email-linmiaohe@huawei.com>
X-Mailer: git-send-email 1.8.3.1
MIME-Version: 1.0
X-Originating-IP: [10.175.105.18]
X-CFilter-Loop: Reflected
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Miaohe Lin <linmiaohe@huawei.com>

The driver of the pci device may not equal to vfio_pci_driver,
but we fetch vfio_device from pci_dev unconditionally in func
vfio_pci_reflck_find. This overhead, such as the competition
of vfio.group_lock, can be eliminated by check pci_dev_driver
with vfio_pci_driver first.

Signed-off-by: Miaohe Lin <linmiaohe@huawei.com>
---
 drivers/vfio/pci/vfio_pci.c | 9 ++++-----
 1 file changed, 4 insertions(+), 5 deletions(-)

```
