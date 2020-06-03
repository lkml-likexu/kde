#### [PATCH 1/2] vfio iommu: Use shift operation for 64-bit integer division
##### From: Kirti Wankhede <kwankhede@nvidia.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Kirti Wankhede <kwankhede@nvidia.com>
X-Patchwork-Id: 11584241
Return-Path: <SRS0=c+BJ=7P=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 5B4A814F6
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue,  2 Jun 2020 19:16:00 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 3876D2086A
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue,  2 Jun 2020 19:16:00 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=nvidia.com header.i=@nvidia.com
 header.b="nf74jj68"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726817AbgFBTP7 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 2 Jun 2020 15:15:59 -0400
Received: from hqnvemgate25.nvidia.com ([216.228.121.64]:7494 "EHLO
        hqnvemgate25.nvidia.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726139AbgFBTP7 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 2 Jun 2020 15:15:59 -0400
Received: from hqpgpgate101.nvidia.com (Not Verified[216.228.121.13]) by
 hqnvemgate25.nvidia.com (using TLS: TLSv1.2, DES-CBC3-SHA)
        id <B5ed6a5170000>; Tue, 02 Jun 2020 12:14:31 -0700
Received: from hqmail.nvidia.com ([172.20.161.6])
  by hqpgpgate101.nvidia.com (PGP Universal service);
  Tue, 02 Jun 2020 12:15:58 -0700
X-PGP-Universal: processed;
        by hqpgpgate101.nvidia.com on Tue, 02 Jun 2020 12:15:58 -0700
Received: from HQMAIL105.nvidia.com (172.20.187.12) by HQMAIL105.nvidia.com
 (172.20.187.12) with Microsoft SMTP Server (TLS) id 15.0.1473.3; Tue, 2 Jun
 2020 19:15:48 +0000
Received: from kwankhede-dev.nvidia.com (10.124.1.5) by HQMAIL105.nvidia.com
 (172.20.187.12) with Microsoft SMTP Server (TLS) id 15.0.1473.3 via Frontend
 Transport; Tue, 2 Jun 2020 19:15:42 +0000
From: Kirti Wankhede <kwankhede@nvidia.com>
To: <alex.williamson@redhat.com>, <cjia@nvidia.com>
CC: <kevin.tian@intel.com>, <ziye.yang@intel.com>,
        <changpeng.liu@intel.com>, <yi.l.liu@intel.com>,
        <mlevitsk@redhat.com>, <eskultet@redhat.com>, <cohuck@redhat.com>,
        <dgilbert@redhat.com>, <jonathan.davies@nutanix.com>,
        <eauger@redhat.com>, <aik@ozlabs.ru>, <pasic@linux.ibm.com>,
        <felipe@nutanix.com>, <Zhengxiao.zx@Alibaba-inc.com>,
        <shuangtai.tst@alibaba-inc.com>, <Ken.Xue@amd.com>,
        <zhi.a.wang@intel.com>, <yan.y.zhao@intel.com>,
        <qemu-devel@nongnu.org>, <kvm@vger.kernel.org>,
        Kirti Wankhede <kwankhede@nvidia.com>
Subject: [PATCH 1/2] vfio iommu: Use shift operation for 64-bit integer
 division
Date: Wed, 3 Jun 2020 00:12:36 +0530
Message-ID: <1591123357-18297-1-git-send-email-kwankhede@nvidia.com>
X-Mailer: git-send-email 2.7.0
X-NVConfidentiality: public
MIME-Version: 1.0
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=nvidia.com; s=n1;
        t=1591125272; bh=INqjvK9GUaUbxLFgl48meRA1JF55U/PN28DUQip5ODw=;
        h=X-PGP-Universal:From:To:CC:Subject:Date:Message-ID:X-Mailer:
         X-NVConfidentiality:MIME-Version:Content-Type;
        b=nf74jj68gnc1+aFA7sAwgGRbx3LNaY4TeBPQ1iQ1fiuq9oVC/sks0FPkmP+OyAIDg
         mDBylHAUaDeLLJWJaT+T/w1mlGOAYUcUVbLyyZONgunbPm5OxHOQFN8hsbxq3VVZl8
         kejWb3rY4ofxOVluebAJ6mIUrmj3/Yw45riyYNfTztWXhaW+lY/zqfzuOiT480sMMR
         JLqCRdeTwg+SlA5lNU4T3HZdzjVyTqnSmWFysk3AZJvrxccXJL8G4dE7NmPckvKQ2h
         G9hfHMsBEYBNmbnC6llVX/h8/nyWDtBMIMPXE3KCCTpWa2O4U2KxiowhZGGAGlgo66
         IhQaq+EFYFKmw==
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Fixes compilation error with ARCH=i386.

Error fixed by this commit:
ld: drivers/vfio/vfio_iommu_type1.o: in function `vfio_dma_populate_bitmap':
>> vfio_iommu_type1.c:(.text+0x666): undefined reference to `__udivdi3'

Fixes: d6a4c185660c (vfio iommu: Implementation of ioctl for dirty pages tracking)

Signed-off-by: Kirti Wankhede <kwankhede@nvidia.com>
Reported-by: kbuild test robot <lkp@intel.com>
---
 drivers/vfio/vfio_iommu_type1.c | 3 ++-
 1 file changed, 2 insertions(+), 1 deletion(-)

```
#### [PATCH 1/3] KVM: x86: remove unnecessary rmap walk of read-only memslots
##### From: Anthony Yznaga <anthony.yznaga@oracle.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Anthony Yznaga <anthony.yznaga@oracle.com>
X-Patchwork-Id: 11584277
Return-Path: <SRS0=c+BJ=7P=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 5BA0260D
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue,  2 Jun 2020 20:09:09 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 4233A2072F
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue,  2 Jun 2020 20:09:09 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=oracle.com header.i=@oracle.com
 header.b="XxzlY4sx"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728327AbgFBUJC (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 2 Jun 2020 16:09:02 -0400
Received: from aserp2120.oracle.com ([141.146.126.78]:37812 "EHLO
        aserp2120.oracle.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726130AbgFBUJB (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 2 Jun 2020 16:09:01 -0400
Received: from pps.filterd (aserp2120.oracle.com [127.0.0.1])
        by aserp2120.oracle.com (8.16.0.42/8.16.0.42) with SMTP id
 052JulYa168523;
        Tue, 2 Jun 2020 20:07:42 GMT
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=oracle.com;
 h=from : to : cc :
 subject : date : message-id : in-reply-to : references; s=corp-2020-01-29;
 bh=u/fCzrRFXKu5OAm9GMeH7Ay3Emb8+njH7NIt5wH2t7s=;
 b=XxzlY4sx0sWv3jxz/jxMxRKHZbtYjTb4uPOXU6PqmOUn1rrF8AWxyLpzLb5NsBW8Bgdo
 fA4ldu1DD/ctT2BLahOqOvdaZ39DBwyrCyoEXtRkaWLlQQ6TJKHxp9EjJGpzs9qfDHtV
 wf4RgX3WbfUHm2SLSEc1oATP34jBAPj1ZmqeRbyU8xNV50qps5/GKfuhKLp3zU3RSkNU
 AuOpo/SDe7PJisvroC4QOLKJld8rCZmqmP8OaX/9bo2X1hJ9EJitun2meX/mpzHVc7+w
 bpGVYYeYj6pkUCA4OY1SjjJgOi3BpXer8h9HSn9+H/KxUw88Prj9l597+o/5xnHLXzyW wA==
Received: from userp3030.oracle.com (userp3030.oracle.com [156.151.31.80])
        by aserp2120.oracle.com with ESMTP id 31bfem5uch-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=FAIL);
        Tue, 02 Jun 2020 20:07:42 +0000
Received: from pps.filterd (userp3030.oracle.com [127.0.0.1])
        by userp3030.oracle.com (8.16.0.42/8.16.0.42) with SMTP id
 052JxHrQ135232;
        Tue, 2 Jun 2020 20:07:41 GMT
Received: from aserv0121.oracle.com (aserv0121.oracle.com [141.146.126.235])
        by userp3030.oracle.com with ESMTP id 31c1dxtrmk-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Tue, 02 Jun 2020 20:07:41 +0000
Received: from abhmp0008.oracle.com (abhmp0008.oracle.com [141.146.116.14])
        by aserv0121.oracle.com (8.14.4/8.13.8) with ESMTP id 052K7cb2022814;
        Tue, 2 Jun 2020 20:07:38 GMT
Received: from ayz-linux.us.oracle.com (/10.154.185.88)
        by default (Oracle Beehive Gateway v4.0)
        with ESMTP ; Tue, 02 Jun 2020 13:07:38 -0700
From: Anthony Yznaga <anthony.yznaga@oracle.com>
To: kvm@vger.kernel.org, linux-kernel@vger.kernel.org
Cc: pbonzini@redhat.com, sean.j.christopherson@intel.com,
        vkuznets@redhat.com, wanpengli@tencent.com, jmattson@google.com,
        joro@8bytes.org, tglx@linutronix.de, mingo@redhat.com,
        bp@alien8.de, x86@kernel.org, hpa@zytor.com,
        steven.sistare@oracle.com, anthony.yznaga@oracle.com
Subject: [PATCH 1/3] KVM: x86: remove unnecessary rmap walk of read-only
 memslots
Date: Tue,  2 Jun 2020 13:07:28 -0700
Message-Id: <1591128450-11977-2-git-send-email-anthony.yznaga@oracle.com>
X-Mailer: git-send-email 1.8.3.1
In-Reply-To: <1591128450-11977-1-git-send-email-anthony.yznaga@oracle.com>
References: <1591128450-11977-1-git-send-email-anthony.yznaga@oracle.com>
X-Proofpoint-Virus-Version: vendor=nai engine=6000 definitions=9640
 signatures=668686
X-Proofpoint-Spam-Details: rule=notspam policy=default score=0 phishscore=0
 mlxlogscore=999
 spamscore=0 bulkscore=0 adultscore=0 suspectscore=0 mlxscore=0
 malwarescore=0 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.12.0-2004280000 definitions=main-2006020146
X-Proofpoint-Virus-Version: vendor=nai engine=6000 definitions=9640
 signatures=668686
X-Proofpoint-Spam-Details: rule=notspam policy=default score=0 malwarescore=0
 suspectscore=0
 mlxlogscore=999 priorityscore=1501 bulkscore=0 phishscore=0 clxscore=1015
 impostorscore=0 adultscore=0 spamscore=0 mlxscore=0 lowpriorityscore=0
 cotscore=-2147483648 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.12.0-2004280000 definitions=main-2006020146
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

There's no write access to remove.  An existing memslot cannot be updated
to set or clear KVM_MEM_READONLY, and any mappings established in a newly
created or moved read-only memslot will already be read-only.

Signed-off-by: Anthony Yznaga <anthony.yznaga@oracle.com>
---
 arch/x86/kvm/x86.c | 6 ++----
 1 file changed, 2 insertions(+), 4 deletions(-)

```
#### [PATCH Kernel v24 5/8] vfio iommu: Implementation of ioctl for dirty pages tracking
##### From: Kirti Wankhede <kwankhede@nvidia.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Kirti Wankhede <kwankhede@nvidia.com>
X-Patchwork-Id: 11584077
Return-Path: <SRS0=c+BJ=7P=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id DD7DD618
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue,  2 Jun 2020 16:24:54 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id BA4EA20738
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue,  2 Jun 2020 16:24:54 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=nvidia.com header.i=@nvidia.com
 header.b="VZSYDwxK"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726461AbgFBQYx (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 2 Jun 2020 12:24:53 -0400
Received: from hqnvemgate25.nvidia.com ([216.228.121.64]:13400 "EHLO
        hqnvemgate25.nvidia.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726373AbgFBQYx (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 2 Jun 2020 12:24:53 -0400
Received: from hqpgpgate101.nvidia.com (Not Verified[216.228.121.13]) by
 hqnvemgate25.nvidia.com (using TLS: TLSv1.2, DES-CBC3-SHA)
        id <B5ed67cfe0001>; Tue, 02 Jun 2020 09:23:26 -0700
Received: from hqmail.nvidia.com ([172.20.161.6])
  by hqpgpgate101.nvidia.com (PGP Universal service);
  Tue, 02 Jun 2020 09:24:52 -0700
X-PGP-Universal: processed;
        by hqpgpgate101.nvidia.com on Tue, 02 Jun 2020 09:24:52 -0700
Received: from HQMAIL101.nvidia.com (172.20.187.10) by HQMAIL105.nvidia.com
 (172.20.187.12) with Microsoft SMTP Server (TLS) id 15.0.1473.3; Tue, 2 Jun
 2020 16:24:42 +0000
Received: from kwankhede-dev.nvidia.com (10.124.1.5) by HQMAIL101.nvidia.com
 (172.20.187.10) with Microsoft SMTP Server (TLS) id 15.0.1473.3 via Frontend
 Transport; Tue, 2 Jun 2020 16:24:35 +0000
From: Kirti Wankhede <kwankhede@nvidia.com>
To: <alex.williamson@redhat.com>, <cjia@nvidia.com>
CC: <kevin.tian@intel.com>, <ziye.yang@intel.com>,
        <changpeng.liu@intel.com>, <yi.l.liu@intel.com>,
        <mlevitsk@redhat.com>, <eskultet@redhat.com>, <cohuck@redhat.com>,
        <dgilbert@redhat.com>, <jonathan.davies@nutanix.com>,
        <eauger@redhat.com>, <aik@ozlabs.ru>, <pasic@linux.ibm.com>,
        <felipe@nutanix.com>, <Zhengxiao.zx@Alibaba-inc.com>,
        <shuangtai.tst@alibaba-inc.com>, <Ken.Xue@amd.com>,
        <zhi.a.wang@intel.com>, <yan.y.zhao@intel.com>,
        <qemu-devel@nongnu.org>, <kvm@vger.kernel.org>,
        Kirti Wankhede <kwankhede@nvidia.com>
Subject: [PATCH Kernel v24 5/8] vfio iommu: Implementation of ioctl for dirty
 pages tracking
Date: Tue, 2 Jun 2020 21:21:30 +0530
Message-ID: <1591113090-23640-1-git-send-email-kwankhede@nvidia.com>
X-Mailer: git-send-email 2.7.0
In-Reply-To: <1590697854-21364-6-git-send-email-kwankhede@nvidia.com>
References: <1590697854-21364-6-git-send-email-kwankhede@nvidia.com>
X-NVConfidentiality: public
MIME-Version: 1.0
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=nvidia.com; s=n1;
        t=1591115006; bh=x047pGmnNPLMIZyVXn62psnFmY9fXJDQUKZLrZmhpvk=;
        h=X-PGP-Universal:From:To:CC:Subject:Date:Message-ID:X-Mailer:
         In-Reply-To:References:X-NVConfidentiality:MIME-Version:
         Content-Type;
        b=VZSYDwxKqgDqz/E05DpKZiXlZ/HxmXu6xwhhQ7wBG/SOEaFwV45Eocbodm8EVn3Xh
         KSi8GPlwHCyX/NMniEZHxwBN98zYcF4MidrDcXg6ZZ1Vc3u8ELenYFZA5TVIJ6pqEz
         TpDcaVM00cqxSAW1mZe2TMxPueqsnRbWEK7HxkynE7VKoVzvtjbDSNpfscP7f5L483
         snK1+4FFUGOr6wK84isoxvSMGZpGkyn8tdX8Q2mzsVL38ymGWsyAiLpUKsLxMDEPu+
         ahQfAtJmWKd7PJlbIUkYkq8aNsyY/yJ30t/8+Zqe5tzKYgtxFv0SO/jStflKZk+Y9Y
         ptHSkPjQe1qtQ==
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

VFIO_IOMMU_DIRTY_PAGES ioctl performs three operations:
- Start dirty pages tracking while migration is active
- Stop dirty pages tracking.
- Get dirty pages bitmap. Its user space application's responsibility to
  copy content of dirty pages from source to destination during migration.

To prevent DoS attack, memory for bitmap is allocated per vfio_dma
structure. Bitmap size is calculated considering smallest supported page
size. Bitmap is allocated for all vfio_dmas when dirty logging is enabled

Bitmap is populated for already pinned pages when bitmap is allocated for
a vfio_dma with the smallest supported page size. Update bitmap from
pinning functions when tracking is enabled. When user application queries
bitmap, check if requested page size is same as page size used to
populated bitmap. If it is equal, copy bitmap, but if not equal, return
error.

Signed-off-by: Kirti Wankhede <kwankhede@nvidia.com>
Reviewed-by: Neo Jia <cjia@nvidia.com>
Reviewed-by: Yan Zhao <yan.y.zhao@intel.com>

Fixed error reported by build bot by changing pgsize type from uint64_t
to size_t.
Reported-by: kbuild test robot <lkp@intel.com>
---

Fixed errors and sparse warnings reported by kbuild test robot
Reported-by: kbuild test robot <lkp@intel.com>

ld: drivers/vfio/vfio_iommu_type1.o: in function `vfio_dma_populate_bitmap':
>> vfio_iommu_type1.c:(.text+0x666): undefined reference to `__udivdi3'

 drivers/vfio/vfio_iommu_type1.c | 315 +++++++++++++++++++++++++++++++++++++++-
 1 file changed, 309 insertions(+), 6 deletions(-)

```
#### linux-next: build failure after merge of the hyperv tree
##### From: Stephen Rothwell <sfr@canb.auug.org.au>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Stephen Rothwell <sfr@canb.auug.org.au>
X-Patchwork-Id: 11583319
Return-Path: <SRS0=c+BJ=7P=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 977FB1667
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue,  2 Jun 2020 07:36:03 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 7650F20772
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue,  2 Jun 2020 07:36:03 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=canb.auug.org.au header.i=@canb.auug.org.au
 header.b="W8s81OSJ"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726174AbgFBHgA (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 2 Jun 2020 03:36:00 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:51550 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1725900AbgFBHgA (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 2 Jun 2020 03:36:00 -0400
Received: from ozlabs.org (ozlabs.org [IPv6:2401:3900:2:1::2])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id E25A1C061A0E;
        Tue,  2 Jun 2020 00:35:59 -0700 (PDT)
Received: from authenticated.ozlabs.org (localhost [127.0.0.1])
        (using TLSv1.3 with cipher TLS_AES_256_GCM_SHA384 (256/256 bits)
         key-exchange ECDHE (P-256) server-signature RSA-PSS (4096 bits)
 server-digest SHA256)
        (No client certificate requested)
        by mail.ozlabs.org (Postfix) with ESMTPSA id 49bkNs6kccz9sSd;
        Tue,  2 Jun 2020 17:35:57 +1000 (AEST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple; d=canb.auug.org.au;
        s=201702; t=1591083358;
        bh=zFDmif9p+c0zlYbN9eHIw7rrK7P9YAqGApbV6VPU26I=;
        h=Date:From:To:Cc:Subject:From;
        b=W8s81OSJH/5ai9Sq5ElIvSOdUzp53RKl9FI3Y8i1P5m6NJvGqM3eQCDpmAqib/CFL
         0L/QGUqaIHe2swzXMJikoFP8Syw2GuXmqU1r0wLjw9Nhl9fY+S1gZHxj6WlMoSbKKf
         5VPFxedbFzsYrR0YeoaU9HfNbYcVPQ5BWj0bCwkkFNXn+B++3upKB3d2zsPjpOAAmz
         JMCJwqBml3VdhUA2RxageViW3G0zooM1CpitViLzaNCKiBC7dEkh9szrEhhcGweNGO
         kqWNsJEugFl2v0e3leby+imwYS1dYPWRB8XQqHaIL0nTK2ga777C6FH0rLBEI4DvFS
         UxZg4v+q21Z8Q==
Date: Tue, 2 Jun 2020 17:35:56 +1000
From: Stephen Rothwell <sfr@canb.auug.org.au>
To: Wei Liu <wei.liu@kernel.org>, Paolo Bonzini <pbonzini@redhat.com>,
        KVM <kvm@vger.kernel.org>
Cc: Linux Next Mailing List <linux-next@vger.kernel.org>,
        Linux Kernel Mailing List <linux-kernel@vger.kernel.org>,
        Michael Kelley <mikelley@microsoft.com>,
        Jon Doron <arilou@gmail.com>
Subject: linux-next: build failure after merge of the hyperv tree
Message-ID: <20200602173556.17ad06a1@canb.auug.org.au>
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Hi all,

After merging the hyperv tree, today's linux-next build (x86_64
allmodconfig) failed like this:

arch/x86/kvm/hyperv.c: In function 'kvm_vcpu_ioctl_get_hv_cpuid':
arch/x86/kvm/hyperv.c:2020:16: error: 'HV_X64_DEBUGGING' undeclared (first use in this function); did you mean 'HV_DEBUGGING'?
 2020 |    ent->ebx |= HV_X64_DEBUGGING;
      |                ^~~~~~~~~~~~~~~~
      |                HV_DEBUGGING
arch/x86/kvm/hyperv.c:2020:16: note: each undeclared identifier is reported only once for each function it appears in

Caused by commit

  c55a844f46f9 ("x86/hyperv: Split hyperv-tlfs.h into arch dependent and independent files")

interacting with commit

  f97f5a56f597 ("x86/kvm/hyper-v: Add support for synthetic debugger interface")

from the kvm tree.

I have applied this patch for today:

From: Stephen Rothwell <sfr@canb.auug.org.au>
Date: Tue, 2 Jun 2020 17:31:06 +1000
Subject: [PATCH] x86/hyperv: merge fix for HV_X64_DEBUGGING name change

Signed-off-by: Stephen Rothwell <sfr@canb.auug.org.au>
---
 arch/x86/kvm/hyperv.c | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
#### linux-next: manual merge of the hyperv tree with the kvm tree
##### From: Stephen Rothwell <sfr@canb.auug.org.au>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Stephen Rothwell <sfr@canb.auug.org.au>
X-Patchwork-Id: 11583313
Return-Path: <SRS0=c+BJ=7P=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id B470490
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue,  2 Jun 2020 07:18:10 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 9DEA5207FB
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue,  2 Jun 2020 07:18:10 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=canb.auug.org.au header.i=@canb.auug.org.au
 header.b="N8KtvWTZ"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726241AbgFBHSH (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 2 Jun 2020 03:18:07 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:48798 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1725907AbgFBHSH (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 2 Jun 2020 03:18:07 -0400
Received: from ozlabs.org (ozlabs.org [IPv6:2401:3900:2:1::2])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id A1EE9C061A0E;
        Tue,  2 Jun 2020 00:18:06 -0700 (PDT)
Received: from authenticated.ozlabs.org (localhost [127.0.0.1])
        (using TLSv1.3 with cipher TLS_AES_256_GCM_SHA384 (256/256 bits)
         key-exchange ECDHE (P-256) server-signature RSA-PSS (4096 bits)
 server-digest SHA256)
        (No client certificate requested)
        by mail.ozlabs.org (Postfix) with ESMTPSA id 49bk0C2qSpz9sSc;
        Tue,  2 Jun 2020 17:18:03 +1000 (AEST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple; d=canb.auug.org.au;
        s=201702; t=1591082283;
        bh=MrJSykbWLAXwqJ9lxap8vVIzf19HCg++CsqikCUsi20=;
        h=Date:From:To:Cc:Subject:From;
        b=N8KtvWTZh5CwZEffJ51n/KOsacImwvPLrK9AW+eNpmYa1ENeYZBT5SeJEwXtbJVA5
         EHWrEMfEK6b3jqAL61+SxRAIZ1sNd0dFZHP3LksnZ4qGeLrlr4e6R8PGzq8QTBmRVg
         5+FBURqeV9tPWIP7+cAYDobKTC1jOnmojkB1kjTRYolnnvU1mIY2am4EeWxj8IDUFN
         h822MWaolaMXW025AKc4iTmG+OBr722pu97qlzexKF6Gd5xEM1cfU3AE2zsmkwIh/t
         IuEhMhJJc20rCtDnOWBNGlh0Ik7dgRXMFd4WnFwWMBQhZ15dArF5Fx0y7hbt1GJ8l+
         BnWSa0ygtakiA==
Date: Tue, 2 Jun 2020 17:18:02 +1000
From: Stephen Rothwell <sfr@canb.auug.org.au>
To: Wei Liu <wei.liu@kernel.org>, Paolo Bonzini <pbonzini@redhat.com>,
        KVM <kvm@vger.kernel.org>
Cc: Linux Next Mailing List <linux-next@vger.kernel.org>,
        Linux Kernel Mailing List <linux-kernel@vger.kernel.org>,
        Jon Doron <arilou@gmail.com>,
        Michael Kelley <mikelley@microsoft.com>
Subject: linux-next: manual merge of the hyperv tree with the kvm tree
Message-ID: <20200602171802.560d07bc@canb.auug.org.au>
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Hi all,

Today's linux-next merge of the hyperv tree got a conflict in:

  arch/x86/include/asm/hyperv-tlfs.h

between commit:

  22ad0026d097 ("x86/hyper-v: Add synthetic debugger definitions")

from the kvm tree and commit:

  c55a844f46f9 ("x86/hyperv: Split hyperv-tlfs.h into arch dependent and independent files")

from the hyperv tree.

I fixed it up (I removed the conficting bits from that file and added
the following patch) and can carry the fix as necessary. This is now fixed
as far as linux-next is concerned, but any non trivial conflicts should
be mentioned to your upstream maintainer when your tree is submitted for
merging.  You may also want to consider cooperating with the maintainer
of the conflicting tree to minimise any particularly complex conflicts.

From: Stephen Rothwell <sfr@canb.auug.org.au>
Date: Tue, 2 Jun 2020 17:15:49 +1000
Subject: [PATCH] x86/hyperv: merge fix for hyperv-tlfs.h split

Signed-off-by: Stephen Rothwell <sfr@canb.auug.org.au>
---
 include/asm-generic/hyperv-tlfs.h | 4 ++++
 1 file changed, 4 insertions(+)

```
#### linux-next: manual merge of the kvm tree with the tip tree
##### From: Stephen Rothwell <sfr@canb.auug.org.au>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Stephen Rothwell <sfr@canb.auug.org.au>
X-Patchwork-Id: 11583231
Return-Path: <SRS0=c+BJ=7P=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 9CFC1618
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue,  2 Jun 2020 04:54:06 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 8655E207D5
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue,  2 Jun 2020 04:54:06 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=canb.auug.org.au header.i=@canb.auug.org.au
 header.b="REQ1AbSt"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726240AbgFBEyC (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 2 Jun 2020 00:54:02 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:54796 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1725890AbgFBEyC (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 2 Jun 2020 00:54:02 -0400
Received: from ozlabs.org (bilbo.ozlabs.org [IPv6:2401:3900:2:1::2])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id F2E01C061A0E;
        Mon,  1 Jun 2020 21:54:01 -0700 (PDT)
Received: from authenticated.ozlabs.org (localhost [127.0.0.1])
        (using TLSv1.3 with cipher TLS_AES_256_GCM_SHA384 (256/256 bits)
         key-exchange ECDHE (P-256) server-signature RSA-PSS (4096 bits)
 server-digest SHA256)
        (No client certificate requested)
        by mail.ozlabs.org (Postfix) with ESMTPSA id 49bfnz4bsxz9sSf;
        Tue,  2 Jun 2020 14:53:59 +1000 (AEST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple; d=canb.auug.org.au;
        s=201702; t=1591073640;
        bh=rDyuOagNKw3935ar6u61XTbrq3VfmYxSPPFZvkTS/a4=;
        h=Date:From:To:Cc:Subject:From;
        b=REQ1AbSt8qb5RDz/3aD4wUoufWsmXCOg7kUvF6OzjOBK3U9XDYbI+aj1Vf+hduvZ7
         4VqC6R/nVcaoE32PxKpllqbrgVySqHjli1eA78utQN8r3/fptosamcymYGZfZC61N5
         /VrVWSxzArGm5fLr8CU21RiwwyYSBLf4EFrMsq7z+AvfV3j77oy88slU6OFDidD0EC
         r5aR82dVzi40drsLlzWt3hq2JESSFYzr7a2FA5qpdd4CvmosV7B8mrE9OhWQpnTgOL
         IAnFTQ0DeJD8S9if4nHL3gmoJlQwE7JRcPEbb6w0G9v3BAhbVt541MYKEom5oRdubF
         jR6Dy0cQZghdA==
Date: Tue, 2 Jun 2020 14:53:58 +1000
From: Stephen Rothwell <sfr@canb.auug.org.au>
To: Paolo Bonzini <pbonzini@redhat.com>, KVM <kvm@vger.kernel.org>,
        Thomas Gleixner <tglx@linutronix.de>,
        Ingo Molnar <mingo@elte.hu>, "H. Peter Anvin" <hpa@zytor.com>,
        Peter Zijlstra <peterz@infradead.org>
Cc: Linux Next Mailing List <linux-next@vger.kernel.org>,
        Linux Kernel Mailing List <linux-kernel@vger.kernel.org>,
        Vitaly Kuznetsov <vkuznets@redhat.com>
Subject: linux-next: manual merge of the kvm tree with the tip tree
Message-ID: <20200602145358.0a70f077@canb.auug.org.au>
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Hi all,

Today's linux-next merge of the kvm tree got a conflict in:

  arch/x86/kernel/kvm.c

between commit:

  a707ae1a9bbb ("x86/entry: Switch page fault exception to IDTENTRY_RAW")

from the tip tree and commit:

  68fd66f100d1 ("KVM: x86: extend struct kvm_vcpu_pv_apf_data with token info")

from the kvm tree.

I fixed it up (see below) and can carry the fix as necessary. This
is now fixed as far as linux-next is concerned, but any non trivial
conflicts should be mentioned to your upstream maintainer when your tree
is submitted for merging.  You may also want to consider cooperating
with the maintainer of the conflicting tree to minimise any particularly
complex conflicts.

```
#### [PATCH RFC 01/13] vhost: option to fetch descriptors through an independent struct
##### From: "Michael S. Tsirkin" <mst@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 8bit
X-Patchwork-Submitter: "Michael S. Tsirkin" <mst@redhat.com>
X-Patchwork-Id: 11583809
Return-Path: <SRS0=c+BJ=7P=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 5C6E2159A
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue,  2 Jun 2020 13:08:41 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 331DA2074B
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue,  2 Jun 2020 13:08:41 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="ae6c9cdp"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728080AbgFBNIk (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 2 Jun 2020 09:08:40 -0400
Received: from us-smtp-delivery-1.mimecast.com ([207.211.31.120]:51337 "EHLO
        us-smtp-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org
        with ESMTP id S1727794AbgFBNGF (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 2 Jun 2020 09:06:05 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1591103162;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:content-type:content-type:
         content-transfer-encoding:content-transfer-encoding:
         in-reply-to:in-reply-to:references:references;
        bh=hcgLS8sOOa0jYGy0/GUbI7V052A2CYejMEqoXlLou1w=;
        b=ae6c9cdp3W4XpaX7jbhTMTJzRt6gT30+MGkuWYXKWwBhDoR64K283Nu0zSjpQut/4KiRUz
        8KCAphr0UCjP2Zi3ekGWinrn/7cNxAry8n8sbbchzt9zK2F8rUvkdDHgRR4ozODhx3qxQq
        NiKOVfp2bDCX/sEOPcObj/UDc/b2ReA=
Received: from mail-wm1-f70.google.com (mail-wm1-f70.google.com
 [209.85.128.70]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-495-LCR2CnbROeOkPLJy8oVvkg-1; Tue, 02 Jun 2020 09:06:00 -0400
X-MC-Unique: LCR2CnbROeOkPLJy8oVvkg-1
Received: by mail-wm1-f70.google.com with SMTP id p24so936615wmc.1
        for <kvm@vger.kernel.org>; Tue, 02 Jun 2020 06:06:00 -0700 (PDT)
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:date:from:to:cc:subject:message-id:references
         :mime-version:content-disposition:content-transfer-encoding
         :in-reply-to;
        bh=hcgLS8sOOa0jYGy0/GUbI7V052A2CYejMEqoXlLou1w=;
        b=NTRnalgYJ3lgja5FBLBxDAz222JnuJ19z/+WG6fu/Admux+8/Huoia1pT1EivUS6Dc
         FFsIVKjcB5+fEDoTF0fTh3jgJwhvdOiJTia4MP52UtArdzwWYxnYwX4w1M9xMwCkTIw8
         U72c7rAkKi1VIwPBIx2g+F7JtcOr6AQSo0FaGkqOYqpWJFeKGt2Pr9TgyttvYceDa5Sb
         tZib1wQBs7oiGvKr+Mnygq5Ru70NU2hbNmF3ZPho0en2kvol/hKw7Xf4FXn0AKr3qHJ/
         19RuWIcLvBAaBzrcZLVXExpq17OQL6SxjL3eIg36DJbxxXW8y++tuVZeE/UpLURiQMu+
         N1Vg==
X-Gm-Message-State: AOAM531Ib7RTPC8pjM+jglJYzoEEBMYVTO/GG5gN3srdmgdSeZMOqIej
        bCO0JmEAFJQNA45PQcjVXGIqWBTUHi6q5bL1q19ESUUR4UO0vDX45QXM78382GYLAC9WWCjWqAn
        VH/tj0hKc+Hlh
X-Received: by 2002:a5d:49cd:: with SMTP id
 t13mr28797873wrs.292.1591103159337;
        Tue, 02 Jun 2020 06:05:59 -0700 (PDT)
X-Google-Smtp-Source: 
 ABdhPJxG95U3Hjq7TfVK36tpHBgrirHTNymuvShxx7I3iWEYYOa9vousA3XZILFVeznxGhe2mvUy/A==
X-Received: by 2002:a5d:49cd:: with SMTP id
 t13mr28797839wrs.292.1591103158927;
        Tue, 02 Jun 2020 06:05:58 -0700 (PDT)
Received: from redhat.com (bzq-109-64-41-91.red.bezeqint.net. [109.64.41.91])
        by smtp.gmail.com with ESMTPSA id
 v2sm3783903wrn.21.2020.06.02.06.05.57
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Tue, 02 Jun 2020 06:05:58 -0700 (PDT)
Date: Tue, 2 Jun 2020 09:05:56 -0400
From: "Michael S. Tsirkin" <mst@redhat.com>
To: linux-kernel@vger.kernel.org
Cc: Eugenio =?utf-8?b?UMOpcmV6?= <eperezma@redhat.com>,
 Jason Wang <jasowang@redhat.com>, kvm@vger.kernel.org,
 virtualization@lists.linux-foundation.org, netdev@vger.kernel.org
Subject: [PATCH RFC 01/13] vhost: option to fetch descriptors through an
 independent struct
Message-ID: <20200602130543.578420-2-mst@redhat.com>
References: <20200602130543.578420-1-mst@redhat.com>
MIME-Version: 1.0
Content-Disposition: inline
In-Reply-To: <20200602130543.578420-1-mst@redhat.com>
X-Mailer: git-send-email 2.24.1.751.gd10ce2899c
X-Mutt-Fcc: =sent
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The idea is to support multiple ring formats by converting
to a format-independent array of descriptors.

This costs extra cycles, but we gain in ability
to fetch a batch of descriptors in one go, which
is good for code cache locality.

When used, this causes a minor performance degradation,
it's been kept as simple as possible for ease of review.
A follow-up patch gets us back the performance by adding batching.

To simplify benchmarking, I kept the old code around so one can switch
back and forth between old and new code. This will go away in the final
submission.

Signed-off-by: Michael S. Tsirkin <mst@redhat.com>
Signed-off-by: Eugenio Pérez <eperezma@redhat.com>
Link: https://lore.kernel.org/r/20200401183118.8334-2-eperezma@redhat.com
Signed-off-by: Michael S. Tsirkin <mst@redhat.com>
---
 drivers/vhost/vhost.c | 297 +++++++++++++++++++++++++++++++++++++++++-
 drivers/vhost/vhost.h |  16 +++
 2 files changed, 312 insertions(+), 1 deletion(-)

```
