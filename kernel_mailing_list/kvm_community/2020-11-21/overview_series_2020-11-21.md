#### [PATCH v2] vfio iommu type1: Improve vfio_iommu_type1_pin_pages performance
##### From: "xuxiaoyang (C)" <xuxiaoyang2@huawei.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: "xuxiaoyang (C)" <xuxiaoyang2@huawei.com>
X-Patchwork-Id: 11923249
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-14.3 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,HK_RANDOM_FROM,INCLUDES_CR_TRAILER,
	INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED,
	USER_AGENT_SANE_1 autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 5B6E5C63697
	for <kvm@archiver.kernel.org>; Sat, 21 Nov 2020 07:59:07 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 1D0AF22240
	for <kvm@archiver.kernel.org>; Sat, 21 Nov 2020 07:59:07 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727127AbgKUH6p (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Sat, 21 Nov 2020 02:58:45 -0500
Received: from szxga08-in.huawei.com ([45.249.212.255]:2312 "EHLO
        szxga08-in.huawei.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726483AbgKUH6p (ORCPT <rfc822;kvm@vger.kernel.org>);
        Sat, 21 Nov 2020 02:58:45 -0500
Received: from dggeme753-chm.china.huawei.com (unknown [172.30.72.56])
        by szxga08-in.huawei.com (SkyGuard) with ESMTP id 4CdQl32JYqz13Kkm;
        Sat, 21 Nov 2020 15:58:07 +0800 (CST)
Received: from [10.174.184.120] (10.174.184.120) by
 dggeme753-chm.china.huawei.com (10.3.19.99) with Microsoft SMTP Server
 (version=TLS1_2, cipher=TLS_ECDHE_RSA_WITH_AES_128_CBC_SHA256_P256) id
 15.1.1913.5; Sat, 21 Nov 2020 15:58:37 +0800
To: <linux-kernel@vger.kernel.org>, <kvm@vger.kernel.org>,
        Alex Williamson <alex.williamson@redhat.com>
CC: <kwankhede@nvidia.com>, <wu.wubin@huawei.com>,
        <maoming.maoming@huawei.com>, <xieyingtai@huawei.com>,
        <lizhengui@huawei.com>, <wubinfeng@huawei.com>,
        "xuxiaoyang (C)" <xuxiaoyang2@huawei.com>
From: "xuxiaoyang (C)" <xuxiaoyang2@huawei.com>
Subject: [PATCH v2] vfio iommu type1: Improve vfio_iommu_type1_pin_pages
 performance
Message-ID: <60d22fc6-88d6-c7c2-90bd-1e8eccb1fdcc@huawei.com>
Date: Sat, 21 Nov 2020 15:58:37 +0800
User-Agent: Mozilla/5.0 (Windows NT 10.0; Win64; x64; rv:78.0) Gecko/20100101
 Thunderbird/78.3.2
MIME-Version: 1.0
Content-Language: en-GB
X-Originating-IP: [10.174.184.120]
X-ClientProxiedBy: dggeme709-chm.china.huawei.com (10.1.199.105) To
 dggeme753-chm.china.huawei.com (10.3.19.99)
X-CFilter-Loop: Reflected
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

vfio_pin_pages() accepts an array of unrelated iova pfns and processes
each to return the physical pfn.  When dealing with large arrays of
contiguous iovas, vfio_iommu_type1_pin_pages is very inefficient because
it is processed page by page.In this case, we can divide the iova pfn
array into multiple continuous ranges and optimize them.  For example,
when the iova pfn array is {1,5,6,7,9}, it will be divided into three
groups {1}, {5,6,7}, {9} for processing.  When processing {5,6,7}, the
number of calls to pin_user_pages_remote is reduced from 3 times to once.
For single page or large array of discontinuous iovas, we still use
vfio_pin_page_external to deal with it to reduce the performance loss
caused by refactoring.

Signed-off-by: Xiaoyang Xu <xuxiaoyang2@huawei.com>
---
v1 -> v2:
 * make vfio_iommu_type1_pin_contiguous_pages use vfio_pin_page_external
 to pin single page when npage=1
 * make vfio_pin_contiguous_pages_external use set npage to mark
 consecutive pages as dirty. simplify the processing logic of unwind
 * remove unnecessary checks in vfio_get_contiguous_pages_length, put
 the least costly judgment logic at the top, and replace
 vfio_iova_get_vfio_pfn with vfio_find_vpfn

 drivers/vfio/vfio_iommu_type1.c | 231 ++++++++++++++++++++++++++++----
 1 file changed, 204 insertions(+), 27 deletions(-)

--
2.19.1

```
