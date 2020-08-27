#### [PATCH v5 1/4] vhost: convert VHOST_VSOCK_SET_RUNNING to a generic ioctl
##### From: Guennadi Liakhovetski <guennadi.liakhovetski@linux.intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Guennadi Liakhovetski
 <guennadi.liakhovetski@linux.intel.com>
X-Patchwork-Id: 11739239
Return-Path: <SRS0=WeJu=CE=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 76C9A13B1
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 26 Aug 2020 17:46:46 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 5E67F20737
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 26 Aug 2020 17:46:46 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726770AbgHZRqo (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 26 Aug 2020 13:46:44 -0400
Received: from mga07.intel.com ([134.134.136.100]:49544 "EHLO mga07.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726187AbgHZRqn (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 26 Aug 2020 13:46:43 -0400
IronPort-SDR: 
 HVAgh0FkQOrkyF9q4+AtxC6Sn8iWd6sb9fnjKSZsYS4mQBCBMZuH8Cg/14PxkEFnI/nGWldMIv
 E1FIF5xh4/hg==
X-IronPort-AV: E=McAfee;i="6000,8403,9725"; a="220607116"
X-IronPort-AV: E=Sophos;i="5.76,356,1592895600";
   d="scan'208";a="220607116"
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from orsmga006.jf.intel.com ([10.7.209.51])
  by orsmga105.jf.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 26 Aug 2020 10:46:42 -0700
IronPort-SDR: 
 BQiKKnOcSRSPaRSBrEFoE26a95LFxpwrXQ9gJa8FIZFHaRtbdK0CxgvUZrY2oa/N2Iva9hB3gv
 ei7yIf9ZPTYA==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.76,356,1592895600";
   d="scan'208";a="299553464"
Received: from gliakhov-mobl2.ger.corp.intel.com (HELO
 ubuntu.ger.corp.intel.com) ([10.252.54.141])
  by orsmga006.jf.intel.com with ESMTP; 26 Aug 2020 10:46:40 -0700
From: Guennadi Liakhovetski <guennadi.liakhovetski@linux.intel.com>
To: kvm@vger.kernel.org
Cc: linux-remoteproc@vger.kernel.org,
        virtualization@lists.linux-foundation.org,
        sound-open-firmware@alsa-project.org,
        Pierre-Louis Bossart <pierre-louis.bossart@linux.intel.com>,
        Liam Girdwood <liam.r.girdwood@linux.intel.com>,
        "Michael S. Tsirkin" <mst@redhat.com>,
        Jason Wang <jasowang@redhat.com>,
        Ohad Ben-Cohen <ohad@wizery.com>,
        Bjorn Andersson <bjorn.andersson@linaro.org>,
        Mathieu Poirier <mathieu.poirier@linaro.org>,
        Vincent Whitchurch <vincent.whitchurch@axis.com>
Subject: [PATCH v5 1/4] vhost: convert VHOST_VSOCK_SET_RUNNING to a generic
 ioctl
Date: Wed, 26 Aug 2020 19:46:33 +0200
Message-Id: <20200826174636.23873-2-guennadi.liakhovetski@linux.intel.com>
X-Mailer: git-send-email 2.20.1
In-Reply-To: <20200826174636.23873-1-guennadi.liakhovetski@linux.intel.com>
References: <20200826174636.23873-1-guennadi.liakhovetski@linux.intel.com>
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

VHOST_VSOCK_SET_RUNNING is used by the vhost vsock driver to perform
crucial VirtQueue initialisation, like assigning .private fields and
calling vhost_vq_init_access(), and clean up. However, this ioctl is
actually extremely useful for any vhost driver, that doesn't have a
side channel to inform it of a status change, e.g. upon a guest
reboot. This patch makes that ioctl generic, while preserving its
numeric value and also keeping the original alias.

Signed-off-by: Guennadi Liakhovetski <guennadi.liakhovetski@linux.intel.com>
---
 include/uapi/linux/vhost.h | 4 +++-
 1 file changed, 3 insertions(+), 1 deletion(-)

```
#### [GIT PULL] virtio: bugfixes
##### From: "Michael S. Tsirkin" <mst@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: "Michael S. Tsirkin" <mst@redhat.com>
X-Patchwork-Id: 11738409
Return-Path: <SRS0=WeJu=CE=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 20B75913
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 26 Aug 2020 13:28:35 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 051CF21741
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 26 Aug 2020 13:28:35 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="Q4SObXwI"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1730259AbgHZN2c (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 26 Aug 2020 09:28:32 -0400
Received: from us-smtp-delivery-1.mimecast.com ([205.139.110.120]:53272 "EHLO
        us-smtp-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org
        with ESMTP id S1730217AbgHZN20 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 26 Aug 2020 09:28:26 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1598448502;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:content-type:content-type;
        bh=i67+aNF8QtmkXbZ+5JSUQwpOse6+0MGUqtdEKnlOGYo=;
        b=Q4SObXwIqXhBVDXo5ddCXC0ao/UUQJinuE+m/FsbGLI3qQ9NO3KPWnr+UxBSYRZFjuvx0K
        CEKj815+pBPfN0ZM0xRZB0cT7U2oACkXsfZPc4ACCZZVagm5/G2ZFYV/XnU1LXotHbzTUZ
        jtfJhKTkM72coH1njWVDRfX95WmHkGg=
Received: from mail-wm1-f72.google.com (mail-wm1-f72.google.com
 [209.85.128.72]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-222-jcu-5l0KNKe5wqq8ixzCoA-1; Wed, 26 Aug 2020 09:28:20 -0400
X-MC-Unique: jcu-5l0KNKe5wqq8ixzCoA-1
Received: by mail-wm1-f72.google.com with SMTP id c198so775985wme.5
        for <kvm@vger.kernel.org>; Wed, 26 Aug 2020 06:28:20 -0700 (PDT)
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:date:from:to:cc:subject:message-id:mime-version
         :content-disposition;
        bh=i67+aNF8QtmkXbZ+5JSUQwpOse6+0MGUqtdEKnlOGYo=;
        b=rCl+IdLI2WfYOmhxXU+tyPST82THT8vIvWGcCCs9eoJO7u77hiroTY2KDHpflfJ4v1
         i2Xp/NndAk+7D5gqTEIRCQK4aE4hbv/wXV4Ro8SXy94w9mfLPMmbNYLU79JDMN30tzuW
         95DgFPDGY6ZDm++W3zUwhgKObJLlI/rxT90Iu+tSRptZ5UVBhZ293tX8pfkPkEhY9xvO
         VHphoMQAn9GxPT68h6y/K/o3Yg8kE4qFWY08yREDU1Lp8vN8mE4RYxRzDzQ3jKAfH0YM
         QqgZo1qtWBZxt+f9yWaaN3R2pqN25wDn2pUKOO6aVUwt97yomURyiFxYCJ/O3xUlu0Mk
         hn6A==
X-Gm-Message-State: AOAM531TWB9wJC6FbOL7qhstJDvOaWCNuuu4MzOvBVIeDCjB133h+UZ/
        SYaZHv08dSy5kQMMAV+RWsKMKrGzQvVllxKUQAqST8Hq4l2ExCHNK6Wk/Zkvw34mLvjW9qayEue
        0fvkIV/mltfrl
X-Received: by 2002:a1c:105:: with SMTP id 5mr7557731wmb.83.1598448499405;
        Wed, 26 Aug 2020 06:28:19 -0700 (PDT)
X-Google-Smtp-Source: 
 ABdhPJzE5CXik9B/yf7SlhoMl9P+rB1tllMpEuE0RJnSmFjwzWrgc4RXpHi+O77/0mfTHMtg2dZEVQ==
X-Received: by 2002:a1c:105:: with SMTP id 5mr7557705wmb.83.1598448499198;
        Wed, 26 Aug 2020 06:28:19 -0700 (PDT)
Received: from redhat.com (bzq-109-67-46-169.red.bezeqint.net.
 [109.67.46.169])
        by smtp.gmail.com with ESMTPSA id
 g62sm5158616wmf.33.2020.08.26.06.27.52
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Wed, 26 Aug 2020 06:28:18 -0700 (PDT)
Date: Wed, 26 Aug 2020 09:27:31 -0400
From: "Michael S. Tsirkin" <mst@redhat.com>
To: Linus Torvalds <torvalds@linux-foundation.org>
Cc: kvm@vger.kernel.org, virtualization@lists.linux-foundation.org,
        netdev@vger.kernel.org, linux-kernel@vger.kernel.org,
        elic@nvidia.com, jasowang@redhat.com, lingshan.zhu@intel.com,
        maxime.coquelin@redhat.com, mst@redhat.com,
        natechancellor@gmail.com, rdunlap@infradead.org,
        sgarzare@redhat.com
Subject: [GIT PULL] virtio: bugfixes
Message-ID: <20200826092731-mutt-send-email-mst@kernel.org>
MIME-Version: 1.0
Content-Disposition: inline
X-Mutt-Fcc: =sent
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The following changes since commit d012a7190fc1fd72ed48911e77ca97ba4521bccd:

  Linux 5.9-rc2 (2020-08-23 14:08:43 -0700)

are available in the Git repository at:

  https://git.kernel.org/pub/scm/linux/kernel/git/mst/vhost.git tags/for_linus

for you to fetch changes up to cbb523594eb718944b726ba52bb43a1d66188a17:

  vdpa/mlx5: Avoid warnings about shifts on 32-bit platforms (2020-08-26 08:13:59 -0400)

----------------------------------------------------------------
virtio: bugfixes

A couple vdpa and vhost bugfixes

Signed-off-by: Michael S. Tsirkin <mst@redhat.com>

----------------------------------------------------------------
Jason Wang (2):
      vdpa: ifcvf: return err when fail to request config irq
      vdpa: ifcvf: free config irq in ifcvf_free_irq()

Nathan Chancellor (1):
      vdpa/mlx5: Avoid warnings about shifts on 32-bit platforms

Stefano Garzarella (1):
      vhost-iotlb: fix vhost_iotlb_itree_next() documentation

 drivers/vdpa/ifcvf/ifcvf_base.h   |  2 +-
 drivers/vdpa/ifcvf/ifcvf_main.c   |  9 +++++--
 drivers/vdpa/mlx5/net/mlx5_vnet.c | 50 +++++++++++++++++++--------------------
 drivers/vhost/iotlb.c             |  4 ++--
 4 files changed, 35 insertions(+), 30 deletions(-)
```
#### [PATCH v9 30/32] samples: vfio-mdev/mbochs: fix common struct sg_table related issues
##### From: Marek Szyprowski <m.szyprowski@samsung.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Marek Szyprowski <m.szyprowski@samsung.com>
X-Patchwork-Id: 11737331
Return-Path: <SRS0=WeJu=CE=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 1FB99913
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 26 Aug 2020 06:37:05 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 022A0207DF
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 26 Aug 2020 06:37:05 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=samsung.com header.i=@samsung.com
 header.b="MDWa/v2U"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727003AbgHZGg1 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 26 Aug 2020 02:36:27 -0400
Received: from mailout1.w1.samsung.com ([210.118.77.11]:38043 "EHLO
        mailout1.w1.samsung.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726934AbgHZGf4 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 26 Aug 2020 02:35:56 -0400
Received: from eucas1p1.samsung.com (unknown [182.198.249.206])
        by mailout1.w1.samsung.com (KnoxPortal) with ESMTP id
 20200826063546euoutp01adb9b3b28bd4ff76d48ebaac18d96acb~uve3MmoS42034920349euoutp01Y
        for <kvm@vger.kernel.org>; Wed, 26 Aug 2020 06:35:46 +0000 (GMT)
DKIM-Filter: OpenDKIM Filter v2.11.0 mailout1.w1.samsung.com
 20200826063546euoutp01adb9b3b28bd4ff76d48ebaac18d96acb~uve3MmoS42034920349euoutp01Y
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=samsung.com;
        s=mail20170921; t=1598423746;
        bh=i9tfBl9XK1ZIcmVNmOj760Z4Av4MmZkmEeWSykU107Y=;
        h=From:To:Cc:Subject:Date:In-Reply-To:References:From;
        b=MDWa/v2UN64kd/Pdh2+Eqeqoqxov2kLfJNAWiAuYfPUDZdGsjK6rzp0jDh/Ieviln
         FTtvqfiaz8SXSMsHICUOsl47/oAzIj4oVOeTnycj3hrxaX9nk4J4vuowAU11CNovOv
         MRLIevFWqldfH/vPZ87AN+jaPiLfdmm0deNKsdu8=
Received: from eusmges2new.samsung.com (unknown [203.254.199.244]) by
        eucas1p2.samsung.com (KnoxPortal) with ESMTP id
        20200826063546eucas1p248e3327a2574966e6260f8ea4243a18c~uve27uU5X0403504035eucas1p2_;
        Wed, 26 Aug 2020 06:35:46 +0000 (GMT)
Received: from eucas1p2.samsung.com ( [182.198.249.207]) by
        eusmges2new.samsung.com (EUCPMTA) with SMTP id 59.BD.05997.2C2064F5;
 Wed, 26
        Aug 2020 07:35:46 +0100 (BST)
Received: from eusmtrp1.samsung.com (unknown [182.198.249.138]) by
        eucas1p2.samsung.com (KnoxPortal) with ESMTPA id
        20200826063546eucas1p268558dcd08ac9b43843f9f5e23da227d~uve2fzbFv0398703987eucas1p2r;
        Wed, 26 Aug 2020 06:35:46 +0000 (GMT)
Received: from eusmgms1.samsung.com (unknown [182.198.249.179]) by
        eusmtrp1.samsung.com (KnoxPortal) with ESMTP id
        20200826063546eusmtrp1324e39600c0b1709cb7b91c674f0a758~uve2fFvRB1167511675eusmtrp1M;
        Wed, 26 Aug 2020 06:35:46 +0000 (GMT)
X-AuditID: cbfec7f4-65dff7000000176d-ed-5f4602c23e0d
Received: from eusmtip2.samsung.com ( [203.254.199.222]) by
        eusmgms1.samsung.com (EUCPMTA) with SMTP id B0.E0.06314.1C2064F5;
 Wed, 26
        Aug 2020 07:35:45 +0100 (BST)
Received: from AMDC2765.digital.local (unknown [106.120.51.73]) by
        eusmtip2.samsung.com (KnoxPortal) with ESMTPA id
        20200826063545eusmtip2148831d8e511c634dd22bec68983ea60~uve14XvZb0092300923eusmtip2U;
        Wed, 26 Aug 2020 06:35:45 +0000 (GMT)
From: Marek Szyprowski <m.szyprowski@samsung.com>
To: dri-devel@lists.freedesktop.org, iommu@lists.linux-foundation.org,
        linaro-mm-sig@lists.linaro.org, linux-kernel@vger.kernel.org
Cc: Marek Szyprowski <m.szyprowski@samsung.com>,
        Christoph Hellwig <hch@lst.de>,
        Robin Murphy <robin.murphy@arm.com>,
        Bartlomiej Zolnierkiewicz <b.zolnierkie@samsung.com>,
        linux-arm-kernel@lists.infradead.org,
        David Airlie <airlied@linux.ie>,
        Daniel Vetter <daniel@ffwll.ch>,
        Kirti Wankhede <kwankhede@nvidia.com>, kvm@vger.kernel.org
Subject: [PATCH v9 30/32] samples: vfio-mdev/mbochs: fix common struct
 sg_table related issues
Date: Wed, 26 Aug 2020 08:33:14 +0200
Message-Id: <20200826063316.23486-31-m.szyprowski@samsung.com>
X-Mailer: git-send-email 2.17.1
In-Reply-To: <20200826063316.23486-1-m.szyprowski@samsung.com>
X-Brightmail-Tracker: 
 H4sIAAAAAAAAA+NgFtrMKsWRmVeSWpSXmKPExsWy7djP87qHmNziDT68kLXoPXeSyWLjjPWs
        Fv+3TWS2uPL1PZvFytVHmSwW7Le2mDO10GLL6bmMFl+uPGSy2PT4GqvF5V1z2CzWHrnLbnHw
        wxNWB16PNfPWMHrs/baAxWP7twesHve7jzN5bF5S73H732Nmj8k3ljN67L7ZwObR2/yOzaNv
        yypGj8+b5AK4o7hsUlJzMstSi/TtErgyfm/bxF6wRLDi1o78BsaNfF2MnBwSAiYSbe2XGbsY
        uTiEBFYwSnx/tZYFwvnCKHHnxE4WkCohgc+MEp++x8N0rO9bDdWxnFGid9d0JriOM1fmMoNU
        sQkYSnS97WIDsUUEWhklTvTygBQxC1xjknj79x1rFyMHh7BAgsSnV6kgNSwCqhLPph8C6+UV
        sJOY1/qIDWKbvMTqDQfA4pxA8ePd/VDxfewSO4/EQNguEnfetjFC2MISr45vYYewZSROT+4B
        e0dCoJlR4uG5tewQTg+jxOWmGVAd1hJ3zv1iAzmIWUBTYv0ufYiwo0T3uknMIGEJAT6JG28F
        QcLMQOakbdOhwrwSHW1CENVqErOOr4Nbe/DCJWYI20Oie+N5Nkj4TGSUeDP9IfMERvlZCMsW
        MDKuYhRPLS3OTU8tNspLLdcrTswtLs1L10vOz93ECExKp/8d/7KDcdefpEOMAhyMSjy8C9hc
        44VYE8uKK3MPMUpwMCuJ8DqdPR0nxJuSWFmVWpQfX1Sak1p8iFGag0VJnNd40ctYIYH0xJLU
        7NTUgtQimCwTB6dUA+OU74IBMS0vucr3ZHVH7+uVTr/jXntVNFgm02oxx793fImpnqG6U+9d
        nXLmWK0Cd1/XLLNPN7RVfHZLvj188cKthwerP+04vObfls4Xz0yyUwraz23gsP6T2K9V7Vjt
        vNJp3+8+s5yO9+F+rHIymgFcyzy1tIv/Fb07a1S6v2N+wExW7m2BHEosxRmJhlrMRcWJAKtM
        O5tGAwAA
X-Brightmail-Tracker: 
 H4sIAAAAAAAAA+NgFprGIsWRmVeSWpSXmKPExsVy+t/xe7oHmdziDb6vtbToPXeSyWLjjPWs
        Fv+3TWS2uPL1PZvFytVHmSwW7Le2mDO10GLL6bmMFl+uPGSy2PT4GqvF5V1z2CzWHrnLbnHw
        wxNWB16PNfPWMHrs/baAxWP7twesHve7jzN5bF5S73H732Nmj8k3ljN67L7ZwObR2/yOzaNv
        yypGj8+b5AK4o/RsivJLS1IVMvKLS2yVog0tjPQMLS30jEws9QyNzWOtjEyV9O1sUlJzMstS
        i/TtEvQyfm/bxF6wRLDi1o78BsaNfF2MnBwSAiYS6/tWM3YxcnEICSxllPj5aSIrREJG4uS0
        BihbWOLPtS42iKJPjBKHf19jB0mwCRhKdL2FSIgIdDJKTOv+CJZgFrjHJLF3nR+ILSwQJ/Gi
        /ysbiM0ioCrxbPohZhCbV8BOYl7rIzaIDfISqzccAItzAsWPd/eDxYUEbCVOr53BPIGRbwEj
        wypGkdTS4tz03GJDveLE3OLSvHS95PzcTYzAONl27OfmHYyXNgYfYhTgYFTi4V3A5hovxJpY
        VlyZe4hRgoNZSYTX6ezpOCHelMTKqtSi/Pii0pzU4kOMpkBHTWSWEk3OB8ZwXkm8oamhuYWl
        obmxubGZhZI4b4fAwRghgfTEktTs1NSC1CKYPiYOTqkGRsu2U4X6kaYfvvde3DRTdfW1pKJj
        l2V3bww7cEX3+YmKl0rMtrNUezkDopax21noP7DjmaHGtro+5aG64EVHpZfTQtITnsZH2mzy
        DCqQmsTD6HZt0cTgpAtaNzdGlxSt3+reNuf2Y8MfLVczbF8tnp4c8cMk0EhskYlH7ZJPbQdC
        XHfadyrdVWIpzkg01GIuKk4EAOSPyuupAgAA
X-CMS-MailID: 20200826063546eucas1p268558dcd08ac9b43843f9f5e23da227d
X-Msg-Generator: CA
X-RootMTR: 20200826063546eucas1p268558dcd08ac9b43843f9f5e23da227d
X-EPHeader: CA
CMS-TYPE: 201P
X-CMS-RootMailID: 20200826063546eucas1p268558dcd08ac9b43843f9f5e23da227d
References: <20200826063316.23486-1-m.szyprowski@samsung.com>
        <CGME20200826063546eucas1p268558dcd08ac9b43843f9f5e23da227d@eucas1p2.samsung.com>
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The Documentation/DMA-API-HOWTO.txt states that the dma_map_sg() function
returns the number of the created entries in the DMA address space.
However the subsequent calls to the dma_sync_sg_for_{device,cpu}() and
dma_unmap_sg must be called with the original number of the entries
passed to the dma_map_sg().

struct sg_table is a common structure used for describing a non-contiguous
memory buffer, used commonly in the DRM and graphics subsystems. It
consists of a scatterlist with memory pages and DMA addresses (sgl entry),
as well as the number of scatterlist entries: CPU pages (orig_nents entry)
and DMA mapped pages (nents entry).

It turned out that it was a common mistake to misuse nents and orig_nents
entries, calling DMA-mapping functions with a wrong number of entries or
ignoring the number of mapped entries returned by the dma_map_sg()
function.

To avoid such issues, lets use a common dma-mapping wrappers operating
directly on the struct sg_table objects and use scatterlist page
iterators where possible. This, almost always, hides references to the
nents and orig_nents entries, making the code robust, easier to follow
and copy/paste safe.

While touching this code, also add missing call to dma_unmap_sgtable.

Signed-off-by: Marek Szyprowski <m.szyprowski@samsung.com>
---
 samples/vfio-mdev/mbochs.c | 3 ++-
 1 file changed, 2 insertions(+), 1 deletion(-)

```
#### [PATCH] selftests: kvm: Fix assert failure in single-step test
##### From: Yang Weijiang <weijiang.yang@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Yang Weijiang <weijiang.yang@intel.com>
X-Patchwork-Id: 11737103
Return-Path: <SRS0=WeJu=CE=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 7B94E138A
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 26 Aug 2020 01:48:30 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 6A0F12075E
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 26 Aug 2020 01:48:30 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726709AbgHZBsR (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 25 Aug 2020 21:48:17 -0400
Received: from mga03.intel.com ([134.134.136.65]:48778 "EHLO mga03.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726611AbgHZBsQ (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 25 Aug 2020 21:48:16 -0400
IronPort-SDR: 
 mBzo4wOnsFQOX075RgTvXVhRj6HiFu3/UWWI4+lCOPVV8m8d7mAjMkxPJo0HQC/M5tmont0S7v
 zpUjm76WoeXQ==
X-IronPort-AV: E=McAfee;i="6000,8403,9724"; a="156211600"
X-IronPort-AV: E=Sophos;i="5.76,354,1592895600";
   d="scan'208";a="156211600"
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from fmsmga005.fm.intel.com ([10.253.24.32])
  by orsmga103.jf.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 25 Aug 2020 18:48:14 -0700
IronPort-SDR: 
 VxTgRoIG+wPYtPsh0xn3ZNHD+gcvoapHV7aOE6er18cHM75TLhQakQ90OMr8W7mjwlBKpXmoSd
 mbDEZIs92FOw==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.76,354,1592895600";
   d="scan'208";a="500074678"
Received: from local-michael-cet-test.sh.intel.com ([10.239.159.128])
  by fmsmga005.fm.intel.com with ESMTP; 25 Aug 2020 18:48:13 -0700
From: Yang Weijiang <weijiang.yang@intel.com>
To: pbonzini@redhat.com, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org, sean.j.christopherson@intel.com
Cc: Yang Weijiang <weijiang.yang@intel.com>
Subject: [PATCH] selftests: kvm: Fix assert failure in single-step test
Date: Wed, 26 Aug 2020 09:55:24 +0800
Message-Id: <20200826015524.13251-1-weijiang.yang@intel.com>
X-Mailer: git-send-email 2.17.2
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This is a follow-up patch to fix an issue left in commit:
98b0bf02738004829d7e26d6cb47b2e469aaba86
selftests: kvm: Use a shorter encoding to clear RAX

With the change in the commit, we also need to modify "xor" instruction
length from 3 to 2 in array ss_size accordingly to pass below check:

for (i = 0; i < (sizeof(ss_size) / sizeof(ss_size[0])); i++) {
        target_rip += ss_size[i];
        CLEAR_DEBUG();
        debug.control = KVM_GUESTDBG_ENABLE | KVM_GUESTDBG_SINGLESTEP;
        debug.arch.debugreg[7] = 0x00000400;
        APPLY_DEBUG();
        vcpu_run(vm, VCPU_ID);
        TEST_ASSERT(run->exit_reason == KVM_EXIT_DEBUG &&
                    run->debug.arch.exception == DB_VECTOR &&
                    run->debug.arch.pc == target_rip &&
                    run->debug.arch.dr6 == target_dr6,
                    "SINGLE_STEP[%d]: exit %d exception %d rip 0x%llx "
                    "(should be 0x%llx) dr6 0x%llx (should be 0x%llx)",
                    i, run->exit_reason, run->debug.arch.exception,
                    run->debug.arch.pc, target_rip, run->debug.arch.dr6,
                    target_dr6);
}

Reported-by: kernel test robot <rong.a.chen@intel.com>
Signed-off-by: Yang Weijiang <weijiang.yang@intel.com>
---
 tools/testing/selftests/kvm/x86_64/debug_regs.c | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
#### [PATCH v5 01/12] KVM: SVM: Introduce vmcb_(set_intercept/clr_intercept/_is_intercept)
##### From: Babu Moger <babu.moger@amd.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Babu Moger <babu.moger@amd.com>
X-Patchwork-Id: 11739527
Return-Path: <SRS0=WeJu=CE=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 6248013A4
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 26 Aug 2020 19:14:07 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 450542083B
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 26 Aug 2020 19:14:07 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=amdcloud.onmicrosoft.com
 header.i=@amdcloud.onmicrosoft.com header.b="vFRBgGPw"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727122AbgHZTOA (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 26 Aug 2020 15:14:00 -0400
Received: from mail-eopbgr770083.outbound.protection.outlook.com
 ([40.107.77.83]:22217
        "EHLO NAM02-SN1-obe.outbound.protection.outlook.com"
        rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org with ESMTP
        id S1727772AbgHZTNz (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 26 Aug 2020 15:13:55 -0400
ARC-Seal: i=1; a=rsa-sha256; s=arcselector9901; d=microsoft.com; cv=none;
 b=oE+NxzmJ+mLhkQOvN+//MtPu5m9MdOVyh24GXJlpG6pkQB1uLTs1TwGPhThualoX0T9C7M5bE5y949+BIiWcZyhlWpjaHaUNoj1P7lQK5jHLHUYt6H5JneyUafUElTYKxPe6KEc8wbJB79owTqPynKW7CP6kYZ70BJjnSOknad2jBew0ydmJjSG4JWzy3GDnyv0Wjw0Hk3yjeOmOYaxIhbYwkoSNiyevJSeDQRlKHcWE8Q1uv3uxUKrW2WebnbQgjuT7tiCrFEWTuGvnS/K4XH/gPjmq2OtrtUmfeCVGQUNZrqUaMY4nfh/DpFZDtk2cf6mRNyfUP4U5upkgKpAD3A==
ARC-Message-Signature: i=1; a=rsa-sha256; c=relaxed/relaxed; d=microsoft.com;
 s=arcselector9901;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=BnA8rp8+HxgO9is7tLLaDPXB8cL3FzUpBFn/5y8ITMY=;
 b=hmyVWBBtyC6VI0zlLmaH7qc0EbWriCG43fqO4Dx3eewo5Uf6sUt81HNy0ibZYt1Wo9b7SWFww+WLAhoLLYLw9ramQXHrrdcg6OgJXnoIUU+5aEMWFFqA9P7C48dCcXqm83f1uzMcjOfZfenYErCFpQvw1lTVcBpQv/8Anlbo4hL4gfFhZEHHAk7AiJ0t1a6lePgJqC40PpMI0ElPIvL7UTbK+ps4mQe+X3xNwUJ5qFgdBMaO9gwjHr8h6gh0KRQa4Jwg0f3iUZe2o2iFFNpn2iNe3K+JUBHS4f+GoZCy22iqcv/7P0R6KqvGtMWniXaeIzvOVaf2KVh1Jh23rlVWrA==
ARC-Authentication-Results: i=1; mx.microsoft.com 1; spf=pass
 smtp.mailfrom=amd.com; dmarc=pass action=none header.from=amd.com; dkim=pass
 header.d=amd.com; arc=none
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
 d=amdcloud.onmicrosoft.com; s=selector2-amdcloud-onmicrosoft-com;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=BnA8rp8+HxgO9is7tLLaDPXB8cL3FzUpBFn/5y8ITMY=;
 b=vFRBgGPwOp2K+5m8T0MoMCj/9lBWh7sE2tZehh2ZpaAPIJ+lO4hVGPbbdF/j5ABgs83cLhI7jBhzSpu99KcSQic5Jlu+dqqiIweJFR0qb5H10wX5kJO5GpBCSVCp4NH4fxNFMuy93lEGmfZvmukl34DnE8c1PuM5iSvEPU3r+OY=
Authentication-Results: tencent.com; dkim=none (message not signed)
 header.d=none;tencent.com; dmarc=none action=none header.from=amd.com;
Received: from SN1PR12MB2560.namprd12.prod.outlook.com (2603:10b6:802:26::19)
 by SN1PR12MB2384.namprd12.prod.outlook.com (2603:10b6:802:25::25) with
 Microsoft SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.3305.26; Wed, 26 Aug
 2020 19:13:54 +0000
Received: from SN1PR12MB2560.namprd12.prod.outlook.com
 ([fe80::ccd9:728:9577:200d]) by SN1PR12MB2560.namprd12.prod.outlook.com
 ([fe80::ccd9:728:9577:200d%4]) with mapi id 15.20.3305.026; Wed, 26 Aug 2020
 19:13:54 +0000
Subject: [PATCH v5 01/12] KVM: SVM: Introduce
 vmcb_(set_intercept/clr_intercept/_is_intercept)
From: Babu Moger <babu.moger@amd.com>
To: pbonzini@redhat.com, vkuznets@redhat.com,
        sean.j.christopherson@intel.com, jmattson@google.com
Cc: wanpengli@tencent.com, kvm@vger.kernel.org, joro@8bytes.org,
        x86@kernel.org, linux-kernel@vger.kernel.org, babu.moger@amd.com,
        mingo@redhat.com, bp@alien8.de, hpa@zytor.com, tglx@linutronix.de
Date: Wed, 26 Aug 2020 14:13:51 -0500
Message-ID: <159846923148.18873.3524447445230117185.stgit@bmoger-ubuntu>
In-Reply-To: <159846887637.18873.14677728679411578606.stgit@bmoger-ubuntu>
References: <159846887637.18873.14677728679411578606.stgit@bmoger-ubuntu>
User-Agent: StGit/0.17.1-dirty
X-ClientProxiedBy: DM6PR21CA0013.namprd21.prod.outlook.com
 (2603:10b6:5:174::23) To SN1PR12MB2560.namprd12.prod.outlook.com
 (2603:10b6:802:26::19)
MIME-Version: 1.0
X-MS-Exchange-MessageSentRepresentingType: 1
Received: from 255.255.255.255 (255.255.255.255) by
 DM6PR21CA0013.namprd21.prod.outlook.com (2603:10b6:5:174::23) with Microsoft
 SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.3348.3 via Frontend
 Transport; Wed, 26 Aug 2020 19:13:52 +0000
X-Originating-IP: [165.204.77.1]
X-MS-PublicTrafficType: Email
X-MS-Office365-Filtering-HT: Tenant
X-MS-Office365-Filtering-Correlation-Id: bd3a577b-397d-4031-d2f5-08d849f42c63
X-MS-TrafficTypeDiagnostic: SN1PR12MB2384:
X-MS-Exchange-Transport-Forked: True
X-Microsoft-Antispam-PRVS: 
 <SN1PR12MB238420B9635D0282EB04489595540@SN1PR12MB2384.namprd12.prod.outlook.com>
X-MS-Oob-TLC-OOBClassifiers: OLM:2449;
X-MS-Exchange-SenderADCheck: 1
X-Microsoft-Antispam: BCL:0;
X-Microsoft-Antispam-Message-Info: 
 G5oeM5eEZu6M5UHPOM6lVRZlWJN9Xcc/+x4HIs11Y+ujDrBddVSn15U53r8PebT2f/5ewYsQhIQQBeth2unnulZezV1PWS/mPliop9bhbhFVYdv7IPpx35UpQVodAPzD0s5e4/sfzueIjTR7+RBYbeGRHpfnIsZeFEdLKd9Wh5iVLO1WsNOcRz/PPWNYErAfj0JymYL1z2FoDXYoZXFSRXodUTdUIjYYBxIufH4iyVZSNspEuG+rHpDNYXM+9nyArMavo6ksSxSghhJ9yExbwjacvxwZeKYJCtzvQS4CEtxHtrpQdI1RRzwxDLFbBpElXHBYD6H+GbIuS2SjS0SEdg==
X-Forefront-Antispam-Report: 
 CIP:255.255.255.255;CTRY:;LANG:en;SCL:1;SRV:;IPV:NLI;SFV:NSPM;H:SN1PR12MB2560.namprd12.prod.outlook.com;PTR:;CAT:NONE;SFS:(4636009)(7916004)(346002)(366004)(136003)(376002)(396003)(39860400002)(103116003)(4326008)(186003)(66946007)(5660300002)(66476007)(66556008)(44832011)(86362001)(33716001)(9686003)(52116002)(7416002)(6486002)(8936002)(8676002)(16576012)(2906002)(316002)(26005)(478600001)(956004);DIR:OUT;SFP:1101;
X-MS-Exchange-AntiSpam-MessageData: 
 c/pIvlwkvV2zIdW+tHu1rh2/z9e+ykuopNWRetMEt5DSPiu3K8V2cOnH+4ikIDJ4GxlD+oJ5p8JILUXUpU/FhzwApL271G2yPPpoXXrJcYdKe2vio0e4bgVzhg2f0+86fz25h73Q4f0v6YuBfEM9ESffWX9vzNCCOtAXGgylIVQEU0DJaCZNfWK46z/+ObqaxMHAlurXEQoG3qlZvp049kqeBz3uRSvNlGgW7zMmEmRdPgXeCxyDqIQDeHDbj00ggRcC4pL7Kl8+X0aIZtOrXVIYyRovcaaBUAp/GyIJwzVphJQ5X9XdwjanOwWLmIJuM77FrznlQjG5BxgwZ6DPbI212Eg7Sxl4hxOogYr8q6KxC57gvbmHkbruUZHu3rGwfs+4k6m6niyKPK1U5wHB6z+Su8g9i6XuDCL7j9qkG6dzEA9OnU0L5+VdXH1PCS0hLXOBi4VYD9bQPi/2LGtdQx63L1weKk48HN+vGenjOY14Mg0zJeO2qjrZ+8yFdj+8NxNfzDPsp5Ny7Gf82+A42soq+EwvzAmz6UWuLwYNIpzFRXeW4v2ehWaMp09XbmKlmbCL3BuZ59x6elE+asr3+VUoJKhA4+WJ4ceYHOdZjPASOFIRLus8FqK/GQSvoORi2BCGmsj0aMWq/3CmrNpiKg==
X-OriginatorOrg: amd.com
X-MS-Exchange-CrossTenant-Network-Message-Id: 
 bd3a577b-397d-4031-d2f5-08d849f42c63
X-MS-Exchange-CrossTenant-AuthSource: SN1PR12MB2560.namprd12.prod.outlook.com
X-MS-Exchange-CrossTenant-AuthAs: Internal
X-MS-Exchange-CrossTenant-OriginalArrivalTime: 26 Aug 2020 19:13:53.9831
 (UTC)
X-MS-Exchange-CrossTenant-FromEntityHeader: Hosted
X-MS-Exchange-CrossTenant-Id: 3dd8961f-e488-4e60-8e11-a82d994e183d
X-MS-Exchange-CrossTenant-MailboxType: HOSTED
X-MS-Exchange-CrossTenant-UserPrincipalName: 
 01Musu7qnrRF8+S2QFrymTzQmq/KGSWVYO+bB/G+ARNN5E3hl3YDuBrZk42DNU4b
X-MS-Exchange-Transport-CrossTenantHeadersStamped: SN1PR12MB2384
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This is in preparation for the future intercept vector additions.

Add new functions vmcb_set_intercept, vmcb_clr_intercept and vmcb_is_intercept
using kernel APIs __set_bit, __clear_bit and test_bit espectively.

Signed-off-by: Babu Moger <babu.moger@amd.com>
Reviewed-by: Jim Mattson <jmattson@google.com>
---
 arch/x86/kvm/svm/svm.h |   15 +++++++++++++++
 1 file changed, 15 insertions(+)

```
#### [PATCH v4 01/10] vfio/fsl-mc: Add VFIO framework skeleton for fsl-mc devices
##### From: Diana Craciun <diana.craciun@oss.nxp.com>

```c
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Bharat Bhushan <Bharat.Bhushan@nxp.com>

DPAA2 (Data Path Acceleration Architecture) consists in
mechanisms for processing Ethernet packets, queue management,
accelerators, etc.

The Management Complex (mc) is a hardware entity that manages the DPAA2
hardware resources. It provides an object-based abstraction for software
drivers to use the DPAA2 hardware. The MC mediates operations such as
create, discover, destroy of DPAA2 objects.
The MC provides memory-mapped I/O command interfaces (MC portals) which
DPAA2 software drivers use to operate on DPAA2 objects.

A DPRC is a container object that holds other types of DPAA2 objects.
Each object in the DPRC is a Linux device and bound to a driver.
The MC-bus driver is a platform driver (different from PCI or platform
bus). The DPRC driver does runtime management of a bus instance. It
performs the initial scan of the DPRC and handles changes in the DPRC
configuration (adding/removing objects).

All objects inside a container share the same hardware isolation
context, meaning that only an entire DPRC can be assigned to
a virtual machine.
When a container is assigned to a virtual machine, all the objects
within that container are assigned to that virtual machine.
The DPRC container assigned to the virtual machine is not allowed
to change contents (add/remove objects) by the guest. The restriction
is set by the host and enforced by the mc hardware.

The DPAA2 objects can be directly assigned to the guest. However
the MC portals (the memory mapped command interface to the MC) need
to be emulated because there are commands that configure the
interrupts and the isolation IDs which are virtual in the guest.

Example:
echo vfio-fsl-mc > /sys/bus/fsl-mc/devices/dprc.2/driver_override
echo dprc.2 > /sys/bus/fsl-mc/drivers/vfio-fsl-mc/bind

The dprc.2 is bound to the VFIO driver and all the objects within
dprc.2 are going to be bound to the VFIO driver.

This patch adds the infrastructure for VFIO support for fsl-mc
devices. Subsequent patches will add support for binding and secure
assigning these devices using VFIO.

More details about the DPAA2 objects can be found here:
Documentation/networking/device_drivers/freescale/dpaa2/overview.rst

Signed-off-by: Bharat Bhushan <Bharat.Bhushan@nxp.com>
Signed-off-by: Diana Craciun <diana.craciun@oss.nxp.com>
---
 MAINTAINERS                               |   6 +
 drivers/vfio/Kconfig                      |   1 +
 drivers/vfio/Makefile                     |   1 +
 drivers/vfio/fsl-mc/Kconfig               |   9 ++
 drivers/vfio/fsl-mc/Makefile              |   4 +
 drivers/vfio/fsl-mc/vfio_fsl_mc.c         | 160 ++++++++++++++++++++++
 drivers/vfio/fsl-mc/vfio_fsl_mc_private.h |  14 ++
 include/uapi/linux/vfio.h                 |   1 +
 8 files changed, 196 insertions(+)
 create mode 100644 drivers/vfio/fsl-mc/Kconfig
 create mode 100644 drivers/vfio/fsl-mc/Makefile
 create mode 100644 drivers/vfio/fsl-mc/vfio_fsl_mc.c
 create mode 100644 drivers/vfio/fsl-mc/vfio_fsl_mc_private.h

```
