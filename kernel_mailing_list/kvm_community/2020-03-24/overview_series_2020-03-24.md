#### [GIT PULL 1/2] KVM: s390: Use fallthrough;
##### From: Christian Borntraeger <borntraeger@de.ibm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Christian Borntraeger <borntraeger@de.ibm.com>
X-Patchwork-Id: 11455367
Return-Path: <SRS0=keX+=5J=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id D634192A
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 24 Mar 2020 12:50:40 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id B8A612080C
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 24 Mar 2020 12:50:40 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727485AbgCXMuk (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 24 Mar 2020 08:50:40 -0400
Received: from mx0b-001b2d01.pphosted.com ([148.163.158.5]:21284 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S1727383AbgCXMuj (ORCPT
        <rfc822;kvm@vger.kernel.org>); Tue, 24 Mar 2020 08:50:39 -0400
Received: from pps.filterd (m0098421.ppops.net [127.0.0.1])
        by mx0a-001b2d01.pphosted.com (8.16.0.42/8.16.0.42) with SMTP id
 02OCmiob073388
        for <kvm@vger.kernel.org>; Tue, 24 Mar 2020 08:50:38 -0400
Received: from e06smtp04.uk.ibm.com (e06smtp04.uk.ibm.com [195.75.94.100])
        by mx0a-001b2d01.pphosted.com with ESMTP id 2ywewu0nu8-1
        (version=TLSv1.2 cipher=AES256-GCM-SHA384 bits=256 verify=NOT)
        for <kvm@vger.kernel.org>; Tue, 24 Mar 2020 08:50:38 -0400
Received: from localhost
        by e06smtp04.uk.ibm.com with IBM ESMTP SMTP Gateway: Authorized Use
 Only! Violators will be prosecuted
        for <kvm@vger.kernel.org> from <borntraeger@de.ibm.com>;
        Tue, 24 Mar 2020 12:50:34 -0000
Received: from b06cxnps3075.portsmouth.uk.ibm.com (9.149.109.195)
        by e06smtp04.uk.ibm.com (192.168.101.134) with IBM ESMTP SMTP Gateway:
 Authorized Use Only! Violators will be prosecuted;
        (version=TLSv1/SSLv3 cipher=AES256-GCM-SHA384 bits=256/256)
        Tue, 24 Mar 2020 12:50:30 -0000
Received: from d06av24.portsmouth.uk.ibm.com (d06av24.portsmouth.uk.ibm.com
 [9.149.105.60])
        by b06cxnps3075.portsmouth.uk.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id 02OCoVsE58065068
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Tue, 24 Mar 2020 12:50:31 GMT
Received: from d06av24.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 872C042045;
        Tue, 24 Mar 2020 12:50:31 +0000 (GMT)
Received: from d06av24.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 6DC0E42041;
        Tue, 24 Mar 2020 12:50:31 +0000 (GMT)
Received: from tuxmaker.boeblingen.de.ibm.com (unknown [9.152.85.9])
        by d06av24.portsmouth.uk.ibm.com (Postfix) with ESMTPS;
        Tue, 24 Mar 2020 12:50:31 +0000 (GMT)
Received: by tuxmaker.boeblingen.de.ibm.com (Postfix, from userid 25651)
        id 285A9E149E; Tue, 24 Mar 2020 13:50:31 +0100 (CET)
From: Christian Borntraeger <borntraeger@de.ibm.com>
To: Paolo Bonzini <pbonzini@redhat.com>
Cc: KVM <kvm@vger.kernel.org>,
        Janosch Frank <frankja@linux.vnet.ibm.com>,
        David Hildenbrand <david@redhat.com>,
        Cornelia Huck <cohuck@redhat.com>,
        linux-s390 <linux-s390@vger.kernel.org>,
        Christian Borntraeger <borntraeger@de.ibm.com>,
        Joe Perches <joe@perches.com>
Subject: [GIT PULL 1/2] KVM: s390: Use fallthrough;
Date: Tue, 24 Mar 2020 13:50:29 +0100
X-Mailer: git-send-email 2.24.1
In-Reply-To: <20200324125030.323689-1-borntraeger@de.ibm.com>
References: <20200324125030.323689-1-borntraeger@de.ibm.com>
X-TM-AS-GCONF: 00
x-cbid: 20032412-0016-0000-0000-000002F6DAA8
X-IBM-AV-DETECTION: SAVI=unused REMOTE=unused XFE=unused
x-cbparentid: 20032412-0017-0000-0000-0000335A7870
Message-Id: <20200324125030.323689-2-borntraeger@de.ibm.com>
X-Proofpoint-UnRewURL: 0 URL was un-rewritten
MIME-Version: 1.0
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.138,18.0.645
 definitions=2020-03-24_05:2020-03-23,2020-03-24 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 lowpriorityscore=0
 suspectscore=0 spamscore=0 clxscore=1015 malwarescore=0 impostorscore=0
 bulkscore=0 phishscore=0 mlxscore=0 adultscore=0 mlxlogscore=999
 priorityscore=1501 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.12.0-2003020000 definitions=main-2003240065
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Joe Perches <joe@perches.com>

Convert the various uses of fallthrough comments to fallthrough;

Done via script
Link: https://lore.kernel.org/lkml/b56602fcf79f849e733e7b521bb0e17895d390fa.1582230379.git.joe@perches.com

Signed-off-by: Joe Perches <joe@perches.com>
Link: https://lore.kernel.org/r/d63c86429f3e5aa806aa3e185c97d213904924a5.1583896348.git.joe@perches.com
[borntrager@de.ibm.com: Fix link to tool and subject]
Signed-off-by: Christian Borntraeger <borntraeger@de.ibm.com>
---
 arch/s390/kvm/gaccess.c   | 23 +++++++++++++----------
 arch/s390/kvm/interrupt.c |  2 +-
 arch/s390/kvm/kvm-s390.c  |  4 ++--
 arch/s390/mm/gmap.c       |  6 +++---
 4 files changed, 19 insertions(+), 16 deletions(-)

```
#### [PATCH v16 Kernel 1/7] vfio: KABI for migration interface for device state
##### From: Kirti Wankhede <kwankhede@nvidia.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Kirti Wankhede <kwankhede@nvidia.com>
X-Patchwork-Id: 11456265
Return-Path: <SRS0=keX+=5J=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 2F292913
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 24 Mar 2020 20:06:17 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 00A6E2074D
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 24 Mar 2020 20:06:17 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=nvidia.com header.i=@nvidia.com
 header.b="hm4O0M3s"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727122AbgCXUGQ (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 24 Mar 2020 16:06:16 -0400
Received: from hqnvemgate24.nvidia.com ([216.228.121.143]:16824 "EHLO
        hqnvemgate24.nvidia.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1725927AbgCXUGQ (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 24 Mar 2020 16:06:16 -0400
Received: from hqpgpgate101.nvidia.com (Not Verified[216.228.121.13]) by
 hqnvemgate24.nvidia.com (using TLS: TLSv1.2, DES-CBC3-SHA)
        id <B5e7a67dc0004>; Tue, 24 Mar 2020 13:04:44 -0700
Received: from hqmail.nvidia.com ([172.20.161.6])
  by hqpgpgate101.nvidia.com (PGP Universal service);
  Tue, 24 Mar 2020 13:06:14 -0700
X-PGP-Universal: processed;
        by hqpgpgate101.nvidia.com on Tue, 24 Mar 2020 13:06:14 -0700
Received: from HQMAIL107.nvidia.com (172.20.187.13) by HQMAIL109.nvidia.com
 (172.20.187.15) with Microsoft SMTP Server (TLS) id 15.0.1473.3; Tue, 24 Mar
 2020 20:06:14 +0000
Received: from kwankhede-dev.nvidia.com (172.20.13.39) by HQMAIL107.nvidia.com
 (172.20.187.13) with Microsoft SMTP Server (TLS) id 15.0.1473.3 via Frontend
 Transport; Tue, 24 Mar 2020 20:06:08 +0000
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
Subject: [PATCH v16 Kernel 1/7] vfio: KABI for migration interface for device
 state
Date: Wed, 25 Mar 2020 01:02:33 +0530
Message-ID: <1585078359-20124-2-git-send-email-kwankhede@nvidia.com>
X-Mailer: git-send-email 2.7.0
In-Reply-To: <1585078359-20124-1-git-send-email-kwankhede@nvidia.com>
References: <1585078359-20124-1-git-send-email-kwankhede@nvidia.com>
X-NVConfidentiality: public
MIME-Version: 1.0
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=nvidia.com; s=n1;
        t=1585080284; bh=VITc+kfjKVKuIhAAtCzlW5ife5JxGjdudg+rxyZachI=;
        h=X-PGP-Universal:From:To:CC:Subject:Date:Message-ID:X-Mailer:
         In-Reply-To:References:X-NVConfidentiality:MIME-Version:
         Content-Type;
        b=hm4O0M3smZKHyhprZXjN0ZwmOZSYFfzGCjJExbmrMV0LosUztzroche+HkVMRZHk9
         wBRlcNOMEconBBZnjNql4MLyz6hBUqdDLQX62USEWR37FGXPecmxMNB5uyjQVdXSLJ
         ZPccuCjdf0aiL9ihiTBDYzXUxgkirmFbK9gigkO+tpKjI+SwtyBmlkUyikFQBZ4Rfq
         X1u2J5t4cf9EoQD/8I7L5p+V0Cj34sQz5VQbcVUuQouUUMrBNJ1jDLtaYAHxd20q2m
         JeWwzQAYgcq1IjaB5i7zcBWBtr7x11O7TF9RROBctHP0MZpXHd4janCws3dFRhRk3/
         dBft3iKLkg4TQ==
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

- Defined MIGRATION region type and sub-type.

- Defined vfio_device_migration_info structure which will be placed at the
  0th offset of migration region to get/set VFIO device related
  information. Defined members of structure and usage on read/write access.

- Defined device states and state transition details.

- Defined sequence to be followed while saving and resuming VFIO device.

Signed-off-by: Kirti Wankhede <kwankhede@nvidia.com>
Reviewed-by: Neo Jia <cjia@nvidia.com>
---
 include/uapi/linux/vfio.h | 228 ++++++++++++++++++++++++++++++++++++++++++++++
 1 file changed, 228 insertions(+)

```
#### [PATCH v16 Kernel 4/7] vfio iommu: Implementation of ioctl for dirty pages tracking.
##### From: Kirti Wankhede <kwankhede@nvidia.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Kirti Wankhede <kwankhede@nvidia.com>
X-Patchwork-Id: 11456631
Return-Path: <SRS0=keX+=5J=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 99FB71667
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 24 Mar 2020 21:52:25 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 69E5F2080C
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 24 Mar 2020 21:52:25 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=nvidia.com header.i=@nvidia.com
 header.b="Lqu4w6dP"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728251AbgCXVwW (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 24 Mar 2020 17:52:22 -0400
Received: from hqnvemgate25.nvidia.com ([216.228.121.64]:9383 "EHLO
        hqnvemgate25.nvidia.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1728093AbgCXVwW (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 24 Mar 2020 17:52:22 -0400
Received: from hqpgpgate101.nvidia.com (Not Verified[216.228.121.13]) by
 hqnvemgate25.nvidia.com (using TLS: TLSv1.2, DES-CBC3-SHA)
        id <B5e7a80e80000>; Tue, 24 Mar 2020 14:51:36 -0700
Received: from hqmail.nvidia.com ([172.20.161.6])
  by hqpgpgate101.nvidia.com (PGP Universal service);
  Tue, 24 Mar 2020 14:52:21 -0700
X-PGP-Universal: processed;
        by hqpgpgate101.nvidia.com on Tue, 24 Mar 2020 14:52:21 -0700
Received: from HQMAIL105.nvidia.com (172.20.187.12) by HQMAIL111.nvidia.com
 (172.20.187.18) with Microsoft SMTP Server (TLS) id 15.0.1473.3; Tue, 24 Mar
 2020 21:52:21 +0000
Received: from kwankhede-dev.nvidia.com (10.124.1.5) by HQMAIL105.nvidia.com
 (172.20.187.12) with Microsoft SMTP Server (TLS) id 15.0.1473.3 via Frontend
 Transport; Tue, 24 Mar 2020 21:52:13 +0000
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
        "Kirti Wankhede" <kwankhede@nvidia.com>
Subject: [PATCH v16 Kernel 4/7] vfio iommu: Implementation of ioctl for dirty
 pages tracking.
Date: Wed, 25 Mar 2020 02:48:52 +0530
Message-ID: <1585084732-18473-1-git-send-email-kwankhede@nvidia.com>
X-Mailer: git-send-email 2.7.0
X-NVConfidentiality: public
MIME-Version: 1.0
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=nvidia.com; s=n1;
        t=1585086696; bh=sZ6ZRmSpptOOlUoV0+17uQhikB5z6AzbQu3KoxCZCAY=;
        h=X-PGP-Universal:From:To:CC:Subject:Date:Message-ID:X-Mailer:
         X-NVConfidentiality:MIME-Version:Content-Type;
        b=Lqu4w6dPm/v4CqtY6ggyPTY7tAU7RDAxGmhgyfWzMcg1XZi+xCMVz8Vjz6/e5tN6Z
         qYdXdS8/oIFxp7rw1Tjr7rIapMo6UnMajGuR/D/wTGH0i1omu8oVO7z7cayqopMMap
         tOZt+kMVVLLZI4WYcpCmxkrzkkFlHNNwPSViPpFx3cZyQMzpDD84BwEgDgUCc8crTj
         r4cKo72zauGeoJIpWA3GKygU+/D9nVW9ZybP7SDcApOeK/Ak/xwYvS85eQMBit+WPQ
         Pybh1YmCW3x/mPC+z+28XKrHIFWqk8B6ljvsM3XJAU0PteqRpJkOqmEm9FJPS19KVv
         bfWmhISv5az2g==
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
---
 drivers/vfio/vfio_iommu_type1.c | 266 +++++++++++++++++++++++++++++++++++++++-
 1 file changed, 260 insertions(+), 6 deletions(-)

```
#### [PATCH] KVM: LAPIC: Also cancel preemption timer when disarm LAPIC timer
##### From: Wanpeng Li <kernellwp@gmail.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Wanpeng Li <kernellwp@gmail.com>
X-Patchwork-Id: 11454563
Return-Path: <SRS0=keX+=5J=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 801291392
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 24 Mar 2020 06:32:26 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 5FCCB2074D
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 24 Mar 2020 06:32:26 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=gmail.com header.i=@gmail.com
 header.b="BWEZI2jN"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726257AbgCXGcX (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 24 Mar 2020 02:32:23 -0400
Received: from mail-pg1-f195.google.com ([209.85.215.195]:37158 "EHLO
        mail-pg1-f195.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1725905AbgCXGcX (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 24 Mar 2020 02:32:23 -0400
Received: by mail-pg1-f195.google.com with SMTP id a32so8528282pga.4;
        Mon, 23 Mar 2020 23:32:22 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=from:to:cc:subject:date:message-id;
        bh=RYToHZ+7iNfBZeY3Gu14A1/8MKyc2I2S/2zaDgB0iI4=;
        b=BWEZI2jNvHEI+JUf+q2P+lK3tp7I3a+94lbqrWJ27HAtiosf4mOvGIOSnCq1t2zdX8
         0g954KZ5LWp9K8cQmWUCzE+kQosb0Zs9FuRBxfCegYIxFpxZhSGAw93TPS9ybyN4ThQ9
         qL3OA1haaeFN9HGsJ1eaOZYdcGii2xGhhn4EWzKnSLPD89WKtvphXCMWUlMVqP0LSDb+
         UjSRh/Gqt/MOi4FKIaNRplHzg1dAnIUj8J562uAZUtrjr2dE7wkarIdLM45QzQi+sdfT
         9gLAdYZ/HV8Tl92pn+6Hnb9EEG/2wLRn3czZSNLhJIiK0Gx9jo7n6P03K+TkQ+tDfzTK
         nP5w==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id;
        bh=RYToHZ+7iNfBZeY3Gu14A1/8MKyc2I2S/2zaDgB0iI4=;
        b=fh8h6OFAfZax4lT2twGKYl0MQpME6Y2E7b5JuG7gJOHbRinJsSsCsmRGwCQySgl5yH
         d5TW1OGKsinJA4aKiHVmk776L+a/HAEz1wkzyGXDIWvd3jt5ic33hDgQWS4h6QzUnFTT
         nqbeHacoi59X7Q9ZAImS/aprIk7npjDviGe82zGznVWoxU2r7Jar2/qo76NRDXsyMRDd
         SIDL0DYfF25y0MYHRzvm22LUt0ZQ1ylCyr81zPU8roo+uJ+p+z9C9Q6jI5iJJn7jMjCi
         XiwOxnT4F+jNCy8wEAcQxmcO3GqC0crGsDH2tm8a0kIcqV43hRmfVWk6bS1/L+FpgtfP
         DFLg==
X-Gm-Message-State: ANhLgQ3sVYcFQd9xk6E5KuWbpjBNsiWBuewhZuLBtQ5FkZZWK96QUAnL
        e9KCBhRUokobCK6j3wW3E1RU1tIQ
X-Google-Smtp-Source: 
 ADFU+vtA2k85dAcZkXdqs1gdZC5f7Y3C2ohwOPAYYZpbATGivbbwvStOrdBdFFfCYZDGQ2Ymr1KizA==
X-Received: by 2002:a62:8343:: with SMTP id
 h64mr29451711pfe.166.1585031541385;
        Mon, 23 Mar 2020 23:32:21 -0700 (PDT)
Received: from localhost.localdomain ([103.7.29.6])
        by smtp.googlemail.com with ESMTPSA id
 a15sm15136975pfg.77.2020.03.23.23.32.18
        (version=TLS1_2 cipher=ECDHE-RSA-AES128-SHA bits=128/128);
        Mon, 23 Mar 2020 23:32:20 -0700 (PDT)
From: Wanpeng Li <kernellwp@gmail.com>
X-Google-Original-From: Wanpeng Li <wanpengli@tencent.com>
To: linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Cc: Paolo Bonzini <pbonzini@redhat.com>,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>
Subject: [PATCH] KVM: LAPIC: Also cancel preemption timer when disarm LAPIC
 timer
Date: Tue, 24 Mar 2020 14:32:10 +0800
Message-Id: <1585031530-19823-1-git-send-email-wanpengli@tencent.com>
X-Mailer: git-send-email 2.7.4
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Wanpeng Li <wanpengli@tencent.com>

The timer is disarmed when switching between TSC deadline and other modes, 
we should set everything to disarmed state, however, LAPIC timer can be 
emulated by preemption timer, it still works if vmx->hv_deadline_timer is 
not -1. This patch also cancels preemption timer when disarm LAPIC timer.

Signed-off-by: Wanpeng Li <wanpengli@tencent.com>
---
 arch/x86/kvm/lapic.c | 6 ++++++
 1 file changed, 6 insertions(+)

```
#### [PATCH 1/4] kVM SVM: Move SVM related files to own sub-directory
##### From: Joerg Roedel <joro@8bytes.org>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Joerg Roedel <joro@8bytes.org>
X-Patchwork-Id: 11454905
Return-Path: <SRS0=keX+=5J=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 66A49913
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 24 Mar 2020 09:42:07 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 531FC2080C
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 24 Mar 2020 09:42:07 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727290AbgCXJmC (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 24 Mar 2020 05:42:02 -0400
Received: from 8bytes.org ([81.169.241.247]:55352 "EHLO theia.8bytes.org"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1727227AbgCXJmA (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 24 Mar 2020 05:42:00 -0400
Received: by theia.8bytes.org (Postfix, from userid 1000)
        id 32F62273; Tue, 24 Mar 2020 10:41:59 +0100 (CET)
From: Joerg Roedel <joro@8bytes.org>
To: Paolo Bonzini <pbonzini@redhat.com>
Cc: Sean Christopherson <sean.j.christopherson@intel.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>,
        Suravee Suthikulpanit <suravee.suthikulpanit@amd.com>,
        Tom Lendacky <thomas.lendacky@amd.com>,
        Ashish Kalra <Ashish.Kalra@amd.com>,
        Brijesh Singh <brijesh.singh@amd.com>, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org, Joerg Roedel <jroedel@suse.de>
Subject: [PATCH 1/4] kVM SVM: Move SVM related files to own sub-directory
Date: Tue, 24 Mar 2020 10:41:51 +0100
Message-Id: <20200324094154.32352-2-joro@8bytes.org>
X-Mailer: git-send-email 2.17.1
In-Reply-To: <20200324094154.32352-1-joro@8bytes.org>
References: <20200324094154.32352-1-joro@8bytes.org>
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Joerg Roedel <jroedel@suse.de>

Move svm.c and pmu_amd.c into their own arch/x86/kvm/svm/
subdirectory.

Signed-off-by: Joerg Roedel <jroedel@suse.de>
---
 arch/x86/kvm/Makefile                 | 2 +-
 arch/x86/kvm/{pmu_amd.c => svm/pmu.c} | 0
 arch/x86/kvm/{ => svm}/svm.c          | 0
 3 files changed, 1 insertion(+), 1 deletion(-)
 rename arch/x86/kvm/{pmu_amd.c => svm/pmu.c} (100%)
 rename arch/x86/kvm/{ => svm}/svm.c (100%)

```
#### [PATCH 1/2] s390x: add myself as reviewer
##### From: Cornelia Huck <cohuck@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Cornelia Huck <cohuck@redhat.com>
X-Patchwork-Id: 11455247
Return-Path: <SRS0=keX+=5J=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 9C91014B4
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 24 Mar 2020 12:17:38 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 72D0C20658
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 24 Mar 2020 12:17:38 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="FeSMkoYa"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726968AbgCXMRi (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 24 Mar 2020 08:17:38 -0400
Received: from us-smtp-delivery-74.mimecast.com ([63.128.21.74]:60212 "EHLO
        us-smtp-delivery-74.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1727282AbgCXMRh (ORCPT
        <rfc822;kvm@vger.kernel.org>); Tue, 24 Mar 2020 08:17:37 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1585052257;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding:
         in-reply-to:in-reply-to:references:references;
        bh=gLBlRqL5cZyxvUDZh1B7Yer4tbeYKgyrUrumo9mfBY0=;
        b=FeSMkoYa/SxWQo3RF7EZwh8SRO299U2prgqxiSDDkS6MWvTo7M9ide690i1JDRxHqkUXOc
        EUKBptL8eTxWovRzDai2SJlK6FR5ZR7i0LQ0MbB3NAbDx1LrL0miLLiNbOOZPQngiNo/gN
        /BoQO+CWzuEVhrGl5VAoG26rugtsa+U=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-300-wgsQVnNUMFCE5CDg2FFvig-1; Tue, 24 Mar 2020 08:17:35 -0400
X-MC-Unique: wgsQVnNUMFCE5CDg2FFvig-1
Received: from smtp.corp.redhat.com (int-mx04.intmail.prod.int.phx2.redhat.com
 [10.5.11.14])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 6BE0F107ACC7;
        Tue, 24 Mar 2020 12:17:34 +0000 (UTC)
Received: from localhost (ovpn-113-109.ams2.redhat.com [10.36.113.109])
        by smtp.corp.redhat.com (Postfix) with ESMTPS id 56A1F5D9E5;
        Tue, 24 Mar 2020 12:17:31 +0000 (UTC)
From: Cornelia Huck <cohuck@redhat.com>
To: kvm@vger.kernel.org
Cc: linux-s390@vger.kernel.org, Thomas Huth <thuth@redhat.com>,
        David Hildenbrand <david@redhat.com>,
        Janosch Frank <frankja@linux.ibm.com>,
        Cornelia Huck <cohuck@redhat.com>
Subject: [PATCH 1/2] s390x: add myself as reviewer
Date: Tue, 24 Mar 2020 13:17:21 +0100
Message-Id: <20200324121722.9776-2-cohuck@redhat.com>
In-Reply-To: <20200324121722.9776-1-cohuck@redhat.com>
References: <20200324121722.9776-1-cohuck@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.14
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Signed-off-by: Cornelia Huck <cohuck@redhat.com>
---
 MAINTAINERS | 1 +
 1 file changed, 1 insertion(+)

```
#### [PATCH 1/4] rcuwait: Fix stale wake call name in comment
##### From: Davidlohr Bueso <dave@stgolabs.net>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Davidlohr Bueso <dave@stgolabs.net>
X-Patchwork-Id: 11454441
Return-Path: <SRS0=keX+=5J=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id E45BB14B4
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 24 Mar 2020 04:46:17 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id CFC202074D
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 24 Mar 2020 04:46:17 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726162AbgCXEqK (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 24 Mar 2020 00:46:10 -0400
Received: from mx2.suse.de ([195.135.220.15]:39334 "EHLO mx2.suse.de"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1725853AbgCXEqJ (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 24 Mar 2020 00:46:09 -0400
X-Virus-Scanned: by amavisd-new at test-mx.suse.de
Received: from relay2.suse.de (unknown [195.135.220.254])
        by mx2.suse.de (Postfix) with ESMTP id 774EAB021;
        Tue, 24 Mar 2020 04:46:07 +0000 (UTC)
From: Davidlohr Bueso <dave@stgolabs.net>
To: tglx@linutronix.de, pbonzini@redhat.com
Cc: bigeasy@linutronix.de, peterz@infradead.org, rostedt@goodmis.org,
        torvalds@linux-foundation.org, will@kernel.org,
        joel@joelfernandes.org, linux-kernel@vger.kernel.org,
        kvm@vger.kernel.org, dave@stgolabs.net,
        Davidlohr Bueso <dbueso@suse.de>
Subject: [PATCH 1/4] rcuwait: Fix stale wake call name in comment
Date: Mon, 23 Mar 2020 21:44:50 -0700
Message-Id: <20200324044453.15733-2-dave@stgolabs.net>
X-Mailer: git-send-email 2.16.4
In-Reply-To: <20200324044453.15733-1-dave@stgolabs.net>
References: <20200324044453.15733-1-dave@stgolabs.net>
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The 'trywake' name was renamed to simply 'wake', update the comment.

Signed-off-by: Davidlohr Bueso <dbueso@suse.de>
---
 kernel/exit.c | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
#### [PATCH v2 1/7] arm: Unplug KVM from the build system
##### From: Marc Zyngier <maz@kernel.org>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Marc Zyngier <maz@kernel.org>
X-Patchwork-Id: 11455061
Return-Path: <SRS0=keX+=5J=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id BDCCC174A
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 24 Mar 2020 10:34:04 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 94580208DB
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 24 Mar 2020 10:34:04 +0000 (UTC)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple; d=kernel.org;
	s=default; t=1585046044;
	bh=twI+FrhMAk/LCQP/xGXohCa10/7aYbpXUmUJDbB9Bfc=;
	h=From:To:Cc:Subject:Date:In-Reply-To:References:List-ID:From;
	b=wb585H3KpY/I+6aROoMZ3dLUwchcQ8vMt9ZYbn1RGNPrw1JiGeqx7M1lMYSht24ct
	 ZD/nY/FCw5jgNQFftI72vy54dHz72togctobf0KBGU7935gohrJitm/dEy7LIM+ui2
	 Lhp2YZSGoSbgmV09FUIR+hRU0sFVtoQQEp9CDxxQ=
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727286AbgCXKeE (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 24 Mar 2020 06:34:04 -0400
Received: from mail.kernel.org ([198.145.29.99]:55982 "EHLO mail.kernel.org"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1727112AbgCXKeC (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 24 Mar 2020 06:34:02 -0400
Received: from disco-boy.misterjones.org (disco-boy.misterjones.org
 [51.254.78.96])
        (using TLSv1.2 with cipher ECDHE-RSA-AES256-GCM-SHA384 (256/256 bits))
        (No client certificate requested)
        by mail.kernel.org (Postfix) with ESMTPSA id 94B9F20870;
        Tue, 24 Mar 2020 10:34:01 +0000 (UTC)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple; d=kernel.org;
        s=default; t=1585046041;
        bh=twI+FrhMAk/LCQP/xGXohCa10/7aYbpXUmUJDbB9Bfc=;
        h=From:To:Cc:Subject:Date:In-Reply-To:References:From;
        b=zt9FY9xddS08bQoH+uIDFiRKNTrG15fNN/iWBNJA1jSMAbh9TlygGM/8ScZZiRpyf
         xBusuhmGDlKbUKnBFehqhxlHo8H+Ri2XM31+SGLOTdqBJtCa+6bsOETHBF/mt1FEg0
         QqanZY8CBPn2iAEA3iqJE65jwMeDqW3Yvm3HBAMY=
Received: from 78.163-31-62.static.virginmediabusiness.co.uk ([62.31.163.78]
 helo=why.lan)
        by disco-boy.misterjones.org with esmtpsa
 (TLS1.3:ECDHE_RSA_AES_256_GCM_SHA384:256)
        (Exim 4.92)
        (envelope-from <maz@kernel.org>)
        id 1jGgsh-00FE8V-IV; Tue, 24 Mar 2020 10:34:00 +0000
From: Marc Zyngier <maz@kernel.org>
To: linux-arm-kernel@lists.infradead.org, kvmarm@lists.cs.columbia.edu,
        kvm@vger.kernel.org
Cc: Olof Johansson <olof@lixom.net>, Arnd Bergmann <arnd@arndb.de>,
        Will Deacon <will@kernel.org>,
        Vladimir Murzin <vladimir.murzin@arm.com>,
        Catalin Marinas <catalin.marinas@arm.com>,
        Linus Walleij <linus.walleij@linaro.org>,
        Christoffer Dall <christoffer.dall@arm.com>,
        James Morse <james.morse@arm.com>,
        Julien Thierry <julien.thierry.kdev@gmail.com>,
        Suzuki K Poulose <suzuki.poulose@arm.com>,
        Paolo Bonzini <pbonzini@redhat.com>,
        Quentin Perret <qperret@google.com>,
        Russell King <linux@arm.linux.org.uk>,
        Stefan Agner <stefan@agner.ch>,
        Jan Kiszka <jan.kiszka@siemens.com>,
        Krzysztof Kozlowski <krzk@kernel.org>,
        Bartlomiej Zolnierkiewicz <b.zolnierkie@samsung.com>,
        Marek Szyprowski <m.szyprowski@samsung.com>,
        Takashi Yoshi <takashi@yoshi.email>,
        Daniel Golle <daniel@makrotopia.org>
Subject: [PATCH v2 1/7] arm: Unplug KVM from the build system
Date: Tue, 24 Mar 2020 10:33:44 +0000
Message-Id: <20200324103350.138077-2-maz@kernel.org>
X-Mailer: git-send-email 2.25.0
In-Reply-To: <20200324103350.138077-1-maz@kernel.org>
References: <20200324103350.138077-1-maz@kernel.org>
MIME-Version: 1.0
X-SA-Exim-Connect-IP: 62.31.163.78
X-SA-Exim-Rcpt-To: linux-arm-kernel@lists.infradead.org,
 kvmarm@lists.cs.columbia.edu, kvm@vger.kernel.org, olof@lixom.net,
 arnd@arndb.de, will@kernel.org, vladimir.murzin@arm.com,
 catalin.marinas@arm.com, linus.walleij@linaro.org, christoffer.dall@arm.com,
 james.morse@arm.com, julien.thierry.kdev@gmail.com, suzuki.poulose@arm.com,
 pbonzini@redhat.com, qperret@google.com, linux@arm.linux.org.uk,
 stefan@agner.ch, jan.kiszka@siemens.com, krzk@kernel.org,
 b.zolnierkie@samsung.com, m.szyprowski@samsung.com, takashi@yoshi.email,
 daniel@makrotopia.org
X-SA-Exim-Mail-From: maz@kernel.org
X-SA-Exim-Scanned: No (on disco-boy.misterjones.org);
 SAEximRunCond expanded to false
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

As we're about to drop KVM/arm on the floor, carefully unplug
it from the build system.

Signed-off-by: Marc Zyngier <maz@kernel.org>
Acked-by: Olof Johansson <olof@lixom.net>
Acked-by: Arnd Bergmann <arnd@arndb.de>
Acked-by: Will Deacon <will@kernel.org>
Acked-by: Vladimir Murzin <vladimir.murzin@arm.com>
Acked-by: Catalin Marinas <catalin.marinas@arm.com>
Acked-by: Linus Walleij <linus.walleij@linaro.org>
Acked-by: Christoffer Dall <christoffer.dall@arm.com>
---
 arch/arm/Kconfig             | 2 --
 arch/arm/Makefile            | 1 -
 arch/arm/mach-exynos/Kconfig | 2 +-
 3 files changed, 1 insertion(+), 4 deletions(-)

```
#### [kvm-unit-tests PATCH 01/10] s390x: smp: Test all CRs on initial reset
##### From: Janosch Frank <frankja@linux.ibm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Janosch Frank <frankja@linux.ibm.com>
X-Patchwork-Id: 11454757
Return-Path: <SRS0=keX+=5J=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 4F4AC139A
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 24 Mar 2020 08:13:08 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 3C47820870
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 24 Mar 2020 08:13:08 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727090AbgCXING (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 24 Mar 2020 04:13:06 -0400
Received: from mx0b-001b2d01.pphosted.com ([148.163.158.5]:48438 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S1727066AbgCXINF (ORCPT
        <rfc822;kvm@vger.kernel.org>); Tue, 24 Mar 2020 04:13:05 -0400
Received: from pps.filterd (m0098421.ppops.net [127.0.0.1])
        by mx0a-001b2d01.pphosted.com (8.16.0.42/8.16.0.42) with SMTP id
 02O83xVu009116
        for <kvm@vger.kernel.org>; Tue, 24 Mar 2020 04:13:05 -0400
Received: from e06smtp07.uk.ibm.com (e06smtp07.uk.ibm.com [195.75.94.103])
        by mx0a-001b2d01.pphosted.com with ESMTP id 2ywewtr7ms-1
        (version=TLSv1.2 cipher=AES256-GCM-SHA384 bits=256 verify=NOT)
        for <kvm@vger.kernel.org>; Tue, 24 Mar 2020 04:13:05 -0400
Received: from localhost
        by e06smtp07.uk.ibm.com with IBM ESMTP SMTP Gateway: Authorized Use
 Only! Violators will be prosecuted
        for <kvm@vger.kernel.org> from <frankja@linux.ibm.com>;
        Tue, 24 Mar 2020 08:13:03 -0000
Received: from b06cxnps4074.portsmouth.uk.ibm.com (9.149.109.196)
        by e06smtp07.uk.ibm.com (192.168.101.137) with IBM ESMTP SMTP Gateway:
 Authorized Use Only! Violators will be prosecuted;
        (version=TLSv1/SSLv3 cipher=AES256-GCM-SHA384 bits=256/256)
        Tue, 24 Mar 2020 08:13:00 -0000
Received: from b06wcsmtp001.portsmouth.uk.ibm.com
 (b06wcsmtp001.portsmouth.uk.ibm.com [9.149.105.160])
        by b06cxnps4074.portsmouth.uk.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id 02O8D07l20512888
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Tue, 24 Mar 2020 08:13:00 GMT
Received: from b06wcsmtp001.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 2251EA4064;
        Tue, 24 Mar 2020 08:13:00 +0000 (GMT)
Received: from b06wcsmtp001.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 0AB5EA4060;
        Tue, 24 Mar 2020 08:12:59 +0000 (GMT)
Received: from localhost.localdomain (unknown [9.145.9.40])
        by b06wcsmtp001.portsmouth.uk.ibm.com (Postfix) with ESMTP;
        Tue, 24 Mar 2020 08:12:58 +0000 (GMT)
From: Janosch Frank <frankja@linux.ibm.com>
To: kvm@vger.kernel.org
Cc: thuth@redhat.com, linux-s390@vger.kernel.org, david@redhat.com
Subject: [kvm-unit-tests PATCH 01/10] s390x: smp: Test all CRs on initial
 reset
Date: Tue, 24 Mar 2020 04:12:42 -0400
X-Mailer: git-send-email 2.25.1
In-Reply-To: <20200324081251.28810-1-frankja@linux.ibm.com>
References: <20200324081251.28810-1-frankja@linux.ibm.com>
MIME-Version: 1.0
X-TM-AS-GCONF: 00
x-cbid: 20032408-0028-0000-0000-000003EA6E2D
X-IBM-AV-DETECTION: SAVI=unused REMOTE=unused XFE=unused
x-cbparentid: 20032408-0029-0000-0000-000024AFD6F2
Message-Id: <20200324081251.28810-2-frankja@linux.ibm.com>
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.138,18.0.645
 definitions=2020-03-24_01:2020-03-23,2020-03-24 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 lowpriorityscore=0
 suspectscore=1 spamscore=0 clxscore=1015 malwarescore=0 impostorscore=0
 bulkscore=0 phishscore=0 mlxscore=0 adultscore=0 mlxlogscore=999
 priorityscore=1501 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.12.0-2003020000 definitions=main-2003240039
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

All CRs are set to 0 and CRs 0 and 14 are set to pre-defined values,
so we also need to test 1-13 and 15 for 0.

And while we're at it, let's also set some values to cr 1, 7 and 13, so
we can actually be sure that they will be zeroed.

Signed-off-by: Janosch Frank <frankja@linux.ibm.com>
Reviewed-by: Cornelia Huck <cohuck@redhat.com>
---
 s390x/smp.c | 16 +++++++++++++++-
 1 file changed, 15 insertions(+), 1 deletion(-)

```
#### [PATCH v2] KVM: PPC: Book3S HV: Add a capability for enabling secure guests
##### From: Paul Mackerras <paulus@ozlabs.org>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Paul Mackerras <paulus@ozlabs.org>
X-Patchwork-Id: 11454357
Return-Path: <SRS0=keX+=5J=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id A08AC913
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 24 Mar 2020 00:55:50 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 6CD9720722
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 24 Mar 2020 00:55:50 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=ozlabs.org header.i=@ozlabs.org
 header.b="BWY6fHO8"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727104AbgCXAzt (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 23 Mar 2020 20:55:49 -0400
Received: from bilbo.ozlabs.org ([203.11.71.1]:51929 "EHLO ozlabs.org"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1727030AbgCXAzs (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 23 Mar 2020 20:55:48 -0400
Received: by ozlabs.org (Postfix, from userid 1003)
        id 48mXqP38C5z9sQt; Tue, 24 Mar 2020 11:55:45 +1100 (AEDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple; d=ozlabs.org; s=201707;
        t=1585011345; bh=orGAd6AY4uP0sBwXn2BYvY+3dd++PXcSgm0Dyj3lsJo=;
        h=Date:From:To:Cc:Subject:From;
        b=BWY6fHO8gP8t5apiErS8ghU7MI+IBGHy+OyBTlqaoABB/0jifktVge1epVsYNG7Ef
         sqJd9AkCs7yNBS4pea3ymYyAtESkr19B4zIutJKOGKdED+xWtMBCDLaHjuhyDqWrvm
         R+VS2FmYbUJqCDmYtP2bGKu0igZwPKKYgqZ8nrvBaVoaxg580sxPGuaW3vXMLsYLjA
         hP58yvm92pbXpMXL1EGMSckVgO5b0QVuo/rYq3vEul/nPyhk/a67s8RjvDd8BmOBH3
         eIyabyCDV6BbKnZTSSeOFcXJWOsD5KG5ozBkLMuEMtkzq2xODAOpwqMzW7IEu3XSD9
         y/Xu6X+7jwPUQ==
Date: Tue, 24 Mar 2020 11:55:39 +1100
From: Paul Mackerras <paulus@ozlabs.org>
To: kvm@vger.kernel.org
Cc: kvm-ppc@vger.kernel.org,
        David Gibson <david@gibson.dropbear.id.au>,
        Ram Pai <linuxram@us.ibm.com>
Subject: [PATCH v2] KVM: PPC: Book3S HV: Add a capability for enabling secure
 guests
Message-ID: <20200324005539.GB5604@blackberry>
MIME-Version: 1.0
Content-Disposition: inline
User-Agent: Mutt/1.5.24 (2015-08-30)
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

At present, on Power systems with Protected Execution Facility
hardware and an ultravisor, a KVM guest can transition to being a
secure guest at will.  Userspace (QEMU) has no way of knowing
whether a host system is capable of running secure guests.  This
will present a problem in future when the ultravisor is capable of
migrating secure guests from one host to another, because
virtualization management software will have no way to ensure that
secure guests only run in domains where all of the hosts can
support secure guests.

This adds a VM capability which has two functions: (a) userspace
can query it to find out whether the host can support secure guests,
and (b) userspace can enable it for a guest, which allows that
guest to become a secure guest.  If userspace does not enable it,
KVM will return an error when the ultravisor does the hypercall
that indicates that the guest is starting to transition to a
secure guest.  The ultravisor will then abort the transition and
the guest will terminate.

Signed-off-by: Paul Mackerras <paulus@ozlabs.org>
Reviewed-by: David Gibson <david@gibson.dropbear.id.au>
Reviewed-by: Ram Pai <linuxram@us.ibm.com>
---
v2: Test that KVM uvmem code has initialized successfully as a
condition of reporting that we support secure guests.

 Documentation/virt/kvm/api.rst              | 17 +++++++++++++++++
 arch/powerpc/include/asm/kvm_book3s_uvmem.h |  6 ++++++
 arch/powerpc/include/asm/kvm_host.h         |  1 +
 arch/powerpc/include/asm/kvm_ppc.h          |  1 +
 arch/powerpc/kvm/book3s_hv.c                | 16 ++++++++++++++++
 arch/powerpc/kvm/book3s_hv_uvmem.c          | 13 +++++++++++++
 arch/powerpc/kvm/powerpc.c                  | 14 ++++++++++++++
 include/uapi/linux/kvm.h                    |  1 +
 8 files changed, 69 insertions(+)

```
#### [PATCH V7 1/8] vhost: allow per device message handler
##### From: Jason Wang <jasowang@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Jason Wang <jasowang@redhat.com>
X-Patchwork-Id: 11454415
Return-Path: <SRS0=keX+=5J=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 5F78E1392
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 24 Mar 2020 04:15:41 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 359C42073E
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 24 Mar 2020 04:15:41 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="Z/NWFWzX"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727060AbgCXEPk (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 24 Mar 2020 00:15:40 -0400
Received: from us-smtp-delivery-74.mimecast.com ([63.128.21.74]:38558 "EHLO
        us-smtp-delivery-74.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1725867AbgCXEPj (ORCPT
        <rfc822;kvm@vger.kernel.org>); Tue, 24 Mar 2020 00:15:39 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1585023338;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding:
         in-reply-to:in-reply-to:references:references;
        bh=Qv2sf5ZLe8MVzng446R1oQxVfhG/+fRJUSulJ/I8CAY=;
        b=Z/NWFWzXRjw0YLUn1mpiUvzuulB7ngtEF6ev5DNzF9Xr++tuUUHjyLvjp/4rwqhwGNGggd
        9/43HmVwC9JWiLoxvcDgn5KiYlAKB9Vr+UVdEDf+gsbPpicoReLuuMgdMndlBJ8GXZPjmw
        Cx4Hq1qm5sXT6J0lG3MdhZ9EPoKo3Do=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-90-b4EsYO9ZPkG9IT8PsAlemg-1; Tue, 24 Mar 2020 00:15:34 -0400
X-MC-Unique: b4EsYO9ZPkG9IT8PsAlemg-1
Received: from smtp.corp.redhat.com (int-mx07.intmail.prod.int.phx2.redhat.com
 [10.5.11.22])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 2303B13F5;
        Tue, 24 Mar 2020 04:15:32 +0000 (UTC)
Received: from jason-ThinkPad-X1-Carbon-6th.redhat.com
 (ovpn-13-216.pek2.redhat.com [10.72.13.216])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 122291001B2B;
        Tue, 24 Mar 2020 04:15:20 +0000 (UTC)
From: Jason Wang <jasowang@redhat.com>
To: mst@redhat.com, linux-kernel@vger.kernel.org, kvm@vger.kernel.org,
        virtualization@lists.linux-foundation.org, netdev@vger.kernel.org
Cc: jgg@mellanox.com, maxime.coquelin@redhat.com,
        cunming.liang@intel.com, zhihong.wang@intel.com,
        rob.miller@broadcom.com, xiao.w.wang@intel.com,
        lingshan.zhu@intel.com, eperezma@redhat.com, lulu@redhat.com,
        parav@mellanox.com, kevin.tian@intel.com, stefanha@redhat.com,
        rdunlap@infradead.org, hch@infradead.org, aadam@redhat.com,
        jiri@mellanox.com, shahafs@mellanox.com, hanand@xilinx.com,
        mhabets@solarflare.com, gdawar@xilinx.com, saugatm@xilinx.com,
        vmireyno@marvell.com, Jason Wang <jasowang@redhat.com>
Subject: [PATCH V7 1/8] vhost: allow per device message handler
Date: Tue, 24 Mar 2020 12:14:51 +0800
Message-Id: <20200324041458.27384-2-jasowang@redhat.com>
In-Reply-To: <20200324041458.27384-1-jasowang@redhat.com>
References: <20200324041458.27384-1-jasowang@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.84 on 10.5.11.22
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This patch allow device to register its own message handler during
vhost_dev_init(). vDPA device will use it to implement its own DMA
mapping logic.

Signed-off-by: Jason Wang <jasowang@redhat.com>
---
 drivers/vhost/net.c   |  3 ++-
 drivers/vhost/scsi.c  |  2 +-
 drivers/vhost/vhost.c | 12 ++++++++++--
 drivers/vhost/vhost.h |  6 +++++-
 drivers/vhost/vsock.c |  2 +-
 5 files changed, 19 insertions(+), 6 deletions(-)

```
#### [PATCH v10 1/7] x86/kvm/hyper-v: Explicitly align hcall param for kvm_hyperv_exit
##### From: Jon Doron <arilou@gmail.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Jon Doron <arilou@gmail.com>
X-Patchwork-Id: 11454631
Return-Path: <SRS0=keX+=5J=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 167C215AB
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 24 Mar 2020 07:44:03 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id ED0C92076A
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 24 Mar 2020 07:44:02 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=gmail.com header.i=@gmail.com
 header.b="QAjiwmzn"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727439AbgCXHoC (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 24 Mar 2020 03:44:02 -0400
Received: from mail-wm1-f65.google.com ([209.85.128.65]:53095 "EHLO
        mail-wm1-f65.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1727291AbgCXHoB (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 24 Mar 2020 03:44:01 -0400
Received: by mail-wm1-f65.google.com with SMTP id z18so2095726wmk.2;
        Tue, 24 Mar 2020 00:43:59 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=from:to:cc:subject:date:message-id:in-reply-to:references
         :mime-version:content-transfer-encoding;
        bh=G4SLa8l+3nFk3QG4JtUy0/LZ8zBcZCA5bjAZGfHKUdk=;
        b=QAjiwmznuPXeBwqQ1dlQ7uk23RkAHEa9zHVbzV47FWXOvlrKCu1bRnJKD63JbB53l3
         Pq6EVpKe17Jq/d0Sbz6JeLyXCBDaozAh5+6NpuBGmzbe8yxQQPCU4ktRQprvc9rfury6
         hg0UC4g1xOjKjktltmyEmHncrJPd8Cj/tBvBm2uRQyXP917WiW4+sqolDxWYbOLVaC1B
         WhMDr+4McrxUKr7lCfo9EHLizRoF0o4ZpWg2bYgdOrUcsRuqfZDRv0LT1weOCHYqpUMa
         E09YQzc0l18y/a51TPiWocHgjUuDfhN3qnredyodhA4e299UVcR8nwn+DsPwdLNWz1rc
         v7hQ==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:in-reply-to
         :references:mime-version:content-transfer-encoding;
        bh=G4SLa8l+3nFk3QG4JtUy0/LZ8zBcZCA5bjAZGfHKUdk=;
        b=h2oJFMVwF00eKJT4sdVOC/kS/rr4LiDSr9MJ4MN1R4g8VbjyF1o5aRVCbQ96LGRoUf
         3Z7lMHv+m/umlp1JQPRwaZVRapjw6bcNDspS5yGVG9xLQrmipWg1pKvG+uBkAdBxflIJ
         qWMQ+hEjzWYuaRHGHqcRT7r2OeUC2UkSnNxKbyHBHn3N3EN4hbfxNeVcnG5c29f/j5ZO
         La7+bD1QXB4eujZyX8/m0iL9AuCW80grR15PPmb4mmxd0YBU4bX8ZtE0kB7lSukVFuAS
         CVDH4GHZHm187cxWgfRq9TlHEVeWVkqhMD4A5ft4C8HKKEm66QrAxysinPvWn7TlvIk9
         GyfQ==
X-Gm-Message-State: ANhLgQ3rVzR75nAE+rcl2ECnbuaHYIlWzd7xllsbXvnV5YJMDAaC8PNb
        CdgqA2Vwd2im+8DoLB7rGwcC4XRzGlY=
X-Google-Smtp-Source: 
 ADFU+vvZpLQzvlkI9935lmL7UFek2xUxmHUEUyW6PTRfhwU7zAvV0N8uZmHMJTRoxNeSqAlAR8O2LA==
X-Received: by 2002:a05:600c:24c:: with SMTP id
 12mr1858560wmj.186.1585035838502;
        Tue, 24 Mar 2020 00:43:58 -0700 (PDT)
Received: from jondnuc.lan (IGLD-84-229-155-229.inter.net.il.
 [84.229.155.229])
        by smtp.gmail.com with ESMTPSA id
 r15sm22066122wra.19.2020.03.24.00.43.57
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Tue, 24 Mar 2020 00:43:58 -0700 (PDT)
From: Jon Doron <arilou@gmail.com>
To: kvm@vger.kernel.org, linux-hyperv@vger.kernel.org
Cc: vkuznets@redhat.com, Jon Doron <arilou@gmail.com>
Subject: [PATCH v10 1/7] x86/kvm/hyper-v: Explicitly align hcall param for
 kvm_hyperv_exit
Date: Tue, 24 Mar 2020 09:43:35 +0200
Message-Id: <20200324074341.1770081-2-arilou@gmail.com>
X-Mailer: git-send-email 2.24.1
In-Reply-To: <20200324074341.1770081-1-arilou@gmail.com>
References: <20200324074341.1770081-1-arilou@gmail.com>
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The problem the patch is trying to address is the fact that 'struct
kvm_hyperv_exit' has different layout on when compiling in 32 and 64 bit
modes.

In 64-bit mode the default alignment boundary is 64 bits thus
forcing extra gaps after 'type' and 'msr' but in 32-bit mode the
boundary is at 32 bits thus no extra gaps.

This is an issue as even when the kernel is 64 bit, the userspace using
the interface can be both 32 and 64 bit but the same 32 bit userspace has
to work with 32 bit kernel.

The issue is fixed by forcing the 64 bit layout, this leads to ABI
change for 32 bit builds and while we are obviously breaking '32 bit
userspace with 32 bit kernel' case, we're fixing the '32 bit userspace
with 64 bit kernel' one.

As the interface has no (known) users and 32 bit KVM is rather baroque
nowadays, this seems like a reasonable decision.

Reviewed-by: Vitaly Kuznetsov <vkuznets@redhat.com>
Signed-off-by: Jon Doron <arilou@gmail.com>
---
 Documentation/virt/kvm/api.rst | 2 ++
 include/uapi/linux/kvm.h       | 2 ++
 2 files changed, 4 insertions(+)

```
#### [PATCH v6 1/8] x86/split_lock: Rework the initialization flow of split lock detection
##### From: Xiaoyao Li <xiaoyao.li@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Xiaoyao Li <xiaoyao.li@intel.com>
X-Patchwork-Id: 11455849
Return-Path: <SRS0=keX+=5J=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 2E0A16CA
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 24 Mar 2020 15:39:30 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 10E7220789
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 24 Mar 2020 15:39:30 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728655AbgCXPj0 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 24 Mar 2020 11:39:26 -0400
Received: from mga05.intel.com ([192.55.52.43]:40198 "EHLO mga05.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1728374AbgCXPhJ (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 24 Mar 2020 11:37:09 -0400
IronPort-SDR: 
 q0Nu+ay6Gnp2A1EGMtqJlCc2vU3iiYrlb512VlI65MQjA+vZTV0+l24tpK7t5xYaWMvTGQ7+OK
 VbOVmaOgkOag==
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from orsmga004.jf.intel.com ([10.7.209.38])
  by fmsmga105.fm.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 24 Mar 2020 08:37:08 -0700
IronPort-SDR: 
 i0KfPbMarrj8fNxr1Zrrv+OyGWx6fEUmJk4/fvNl2XBTgyXnHNCrp92he/waQswwyaXk/47/th
 rtv8Xlfyuxqw==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.72,300,1580803200";
   d="scan'208";a="393319675"
Received: from lxy-clx-4s.sh.intel.com ([10.239.43.39])
  by orsmga004.jf.intel.com with ESMTP; 24 Mar 2020 08:37:04 -0700
From: Xiaoyao Li <xiaoyao.li@intel.com>
To: Thomas Gleixner <tglx@linutronix.de>,
        Ingo Molnar <mingo@redhat.com>, Borislav Petkov <bp@alien8.de>,
        hpa@zytor.com, Paolo Bonzini <pbonzini@redhat.com>,
        Sean Christopherson <sean.j.christopherson@intel.com>
Cc: x86@kernel.org, kvm@vger.kernel.org, linux-kernel@vger.kernel.org,
        Andy Lutomirski <luto@kernel.org>,
        Peter Zijlstra <peterz@infradead.org>,
        Arvind Sankar <nivedita@alum.mit.edu>,
        Fenghua Yu <fenghua.yu@intel.com>,
        Tony Luck <tony.luck@intel.com>,
        Xiaoyao Li <xiaoyao.li@intel.com>
Subject: [PATCH v6 1/8] x86/split_lock: Rework the initialization flow of
 split lock detection
Date: Tue, 24 Mar 2020 23:18:52 +0800
Message-Id: <20200324151859.31068-2-xiaoyao.li@intel.com>
X-Mailer: git-send-email 2.20.1
In-Reply-To: <20200324151859.31068-1-xiaoyao.li@intel.com>
References: <20200324151859.31068-1-xiaoyao.li@intel.com>
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Current initialization flow of split lock detection has following
issues:

1. It assumes the initial value of MSR_TEST_CTRL.SPLIT_LOCK_DETECT to be
   zero. However, it's possible that BIOS/firmware has set it.

2. X86_FEATURE_SPLIT_LOCK_DETECT flag is unconditionally set even if
   there is a virtualization flaw that FMS indicates the existence while
   it's actually not supported.

3. Because of #2, for nest virt, L1 KVM cannot rely on flag
   X86_FEATURE_SPLIT_LOCK_DETECT to check the existence of feature.

Rework the initialization flow to solve above issues. In detail,
explicitly set and clear split_lock_detect bit to verify MSR_TEST_CTRL
can be accessed, and rdmsr after wrmsr to ensure bit is set
successfully.

X86_FEATURE_SPLIT_LOCK_DETECT flag is set only when the feature does
exist and the feature is not disabled with kernel param
"split_lock_detect=off"

Originally-by: Thomas Gleixner <tglx@linutronix.de>
Signed-off-by: Xiaoyao Li <xiaoyao.li@intel.com>
---
 arch/x86/kernel/cpu/intel.c | 79 +++++++++++++++++++++----------------
 1 file changed, 46 insertions(+), 33 deletions(-)

```
