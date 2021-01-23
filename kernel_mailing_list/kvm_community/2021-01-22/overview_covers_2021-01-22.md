

#### [RFC PATCH v4 0/2] Some optimization for stage-2 translation
##### From: Yanan Wang <wangyanan55@huawei.com>

```c
From patchwork Fri Jan 22 10:13:56 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Yanan Wang <wangyanan55@huawei.com>
X-Patchwork-Id: 12038839
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-11.8 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,
	SPF_PASS,USER_AGENT_GIT autolearn=unavailable autolearn_force=no
 version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 088C5C433E9
	for <kvm@archiver.kernel.org>; Fri, 22 Jan 2021 10:25:55 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id B897F2376F
	for <kvm@archiver.kernel.org>; Fri, 22 Jan 2021 10:25:54 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727211AbhAVKZh (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Fri, 22 Jan 2021 05:25:37 -0500
Received: from szxga04-in.huawei.com ([45.249.212.190]:11129 "EHLO
        szxga04-in.huawei.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1727777AbhAVKOv (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 22 Jan 2021 05:14:51 -0500
Received: from DGGEMS403-HUB.china.huawei.com (unknown [172.30.72.58])
        by szxga04-in.huawei.com (SkyGuard) with ESMTP id 4DMZp50tyzz15xFK;
        Fri, 22 Jan 2021 18:13:01 +0800 (CST)
Received: from DESKTOP-TMVL5KK.china.huawei.com (10.174.187.128) by
 DGGEMS403-HUB.china.huawei.com (10.3.19.203) with Microsoft SMTP Server id
 14.3.498.0; Fri, 22 Jan 2021 18:14:02 +0800
From: Yanan Wang <wangyanan55@huawei.com>
To: Marc Zyngier <maz@kernel.org>, Will Deacon <will@kernel.org>,
        "Catalin Marinas" <catalin.marinas@arm.com>,
        <kvmarm@lists.cs.columbia.edu>,
        <linux-arm-kernel@lists.infradead.org>, <kvm@vger.kernel.org>,
        <linux-kernel@vger.kernel.org>
CC: James Morse <james.morse@arm.com>,
        Julien Thierry <julien.thierry.kdev@gmail.com>,
        Suzuki K Poulose <suzuki.poulose@arm.com>,
        Gavin Shan <gshan@redhat.com>,
        Quentin Perret <qperret@google.com>,
        <wanghaibin.wang@huawei.com>, <yezengruan@huawei.com>,
        <yuzenghui@huawei.com>, Yanan Wang <wangyanan55@huawei.com>
Subject: [RFC PATCH v4 0/2] Some optimization for stage-2 translation
Date: Fri, 22 Jan 2021 18:13:56 +0800
Message-ID: <20210122101358.379956-1-wangyanan55@huawei.com>
X-Mailer: git-send-email 2.8.4.windows.1
MIME-Version: 1.0
X-Originating-IP: [10.174.187.128]
X-CFilter-Loop: Reflected
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Hi, Will, Marc,
Is there any further comment on the v3 series I post previously?
If they are not fine to you, then I think maybe we should just turn
back to the original solution in v1, where I suggestted to filter out
the case of only updating access permissions in the map handler and
handle it right there.

Here are the reasons for my current opinion:
With an errno returned from the map handler for this single case, there
will be one more vcpu exit from guest and we also have to consider the
spurious dirty pages. Besides, it seems that the EAGAIN errno has been
chosen specially for this case and can not be used elsewhere for other
reasons, as we will change this errno to zero at the end of the function.

The v1 solution looks like more concise at last, so I refine the diff
and post the v4 with two patches here, just for a contrast.

Which solution will you prefer now? Could you please let me know.

Thanks,
Yanan.

Links:
v1: https://lore.kernel.org/lkml/20201211080115.21460-1-wangyanan55@huawei.com
v2: https://lore.kernel.org/lkml/20201216122844.25092-1-wangyanan55@huawei.com
v3: https://lore.kernel.org/lkml/20210114121350.123684-1-wangyanan55@huawei.com
---

About patch-1:
Procedures of hyp stage-1 map and guest stage-2 map are quite different,
but they are now tied closely by function kvm_set_valid_leaf_pte().
So adjust the relative code for ease of code maintenance in the future.

About patch-2:
(1) During running time of a a VM with numbers of vCPUs, if some vCPUs
access the same GPA almost at the same time and the stage-2 mapping of
the GPA has not been built yet, as a result they will all cause
translation faults. The first vCPU builds the mapping, and the followed
ones end up updating the valid leaf PTE. Note that these vCPUs might
want different access permissions (RO, RW, RX, RWX, etc.).

(2) It's inevitable that we sometimes will update an existing valid leaf
PTE in the map path, and we all perform break-before-make in this case.
Then more unnecessary translation faults could be caused if the
*break stage* of BBM is just catched by other vCPUs.

With (1) and (2), something unsatisfactory could happen: vCPU A causes
a translation fault and builds the mapping with RW permissions, vCPU B
then update the valid leaf PTE with break-before-make and permissions
are updated back to RO. Besides, *break stage* of BBM may trigger more
translation faults. Finally, some useless small loops could occur.

We can make some optimization to solve above problems: When we need to
update a valid leaf PTE in the translation fault handler, let's filter
out the case where this update only change access permissions that don't
require break-before-make. If there have already been the permissions
we want, don't bother to update. If still more permissions need to be
added, then update the PTE directly without break-before-make.

---

Changelogs

v4->v3:
- Turn back to the original solution in v1 and refine the diff
- Rebased on top of v5.11-rc4

v2->v3:
- Rebased on top of v5.11-rc3
- Refine the commit messages
- Make some adjustment about return value in patch-2 and patch-3

v1->v2:
- Make part of the diff a seperate patch (patch-1)
- Add Will's Signed-off-by for patch-1
- Return an errno when meeting changing permissions case in map path
- Add a new patch (patch-3)

---

Yanan Wang (2):
  KVM: arm64: Adjust partial code of hyp stage-1 map and guest stage-2
    map
  KVM: arm64: Filter out the case of only changing permissions from
    stage-2 map path

 arch/arm64/include/asm/kvm_pgtable.h |  4 ++
 arch/arm64/kvm/hyp/pgtable.c         | 88 +++++++++++++++++++---------
 2 files changed, 63 insertions(+), 29 deletions(-)
```
#### [PATCH v3 0/2] vfio/iommu_type1: some fixes
##### From: Keqian Zhu <zhukeqian1@huawei.com>

```c
From patchwork Fri Jan 22 09:26:33 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Keqian Zhu <zhukeqian1@huawei.com>
X-Patchwork-Id: 12038993
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-11.8 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,
	SPF_PASS,USER_AGENT_GIT autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id AA05CC433E6
	for <kvm@archiver.kernel.org>; Fri, 22 Jan 2021 11:01:29 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 5E0C523A63
	for <kvm@archiver.kernel.org>; Fri, 22 Jan 2021 11:01:29 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727889AbhAVK6M (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Fri, 22 Jan 2021 05:58:12 -0500
Received: from szxga04-in.huawei.com ([45.249.212.190]:11124 "EHLO
        szxga04-in.huawei.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1727217AbhAVJ1o (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 22 Jan 2021 04:27:44 -0500
Received: from DGGEMS409-HUB.china.huawei.com (unknown [172.30.72.59])
        by szxga04-in.huawei.com (SkyGuard) with ESMTP id 4DMYld4J3Hz15svp;
        Fri, 22 Jan 2021 17:25:49 +0800 (CST)
Received: from DESKTOP-5IS4806.china.huawei.com (10.174.184.42) by
 DGGEMS409-HUB.china.huawei.com (10.3.19.209) with Microsoft SMTP Server id
 14.3.498.0; Fri, 22 Jan 2021 17:26:47 +0800
From: Keqian Zhu <zhukeqian1@huawei.com>
To: <linux-kernel@vger.kernel.org>,
        <linux-arm-kernel@lists.infradead.org>, <kvm@vger.kernel.org>,
        <kvmarm@lists.cs.columbia.edu>, <iommu@lists.linux-foundation.org>,
        Alex Williamson <alex.williamson@redhat.com>,
        Kirti Wankhede <kwankhede@nvidia.com>,
        "Cornelia Huck" <cohuck@redhat.com>
CC: Will Deacon <will@kernel.org>, Marc Zyngier <maz@kernel.org>,
        "Catalin Marinas" <catalin.marinas@arm.com>,
        Mark Rutland <mark.rutland@arm.com>,
        "James Morse" <james.morse@arm.com>,
        Robin Murphy <robin.murphy@arm.com>,
        "Joerg Roedel" <joro@8bytes.org>,
        Daniel Lezcano <daniel.lezcano@linaro.org>,
        "Thomas Gleixner" <tglx@linutronix.de>,
        Suzuki K Poulose <suzuki.poulose@arm.com>,
        Julien Thierry <julien.thierry.kdev@gmail.com>,
        Andrew Morton <akpm@linux-foundation.org>,
        Alexios Zavras <alexios.zavras@intel.com>,
        <wanghaibin.wang@huawei.com>, <jiangkunkun@huawei.com>
Subject: [PATCH v3 0/2] vfio/iommu_type1: some fixes
Date: Fri, 22 Jan 2021 17:26:33 +0800
Message-ID: <20210122092635.19900-1-zhukeqian1@huawei.com>
X-Mailer: git-send-email 2.8.4.windows.1
MIME-Version: 1.0
X-Originating-IP: [10.174.184.42]
X-CFilter-Loop: Reflected
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

v3:
 - Populate bitmap unconditionally.
 - Sanity check notifier when remove all domains.

v2:
 - Address suggestions from Alex.
 - Remove unnecessary patches.
 

Keqian Zhu (2):
  vfio/iommu_type1: Populate full dirty when detach non-pinned group
  vfio/iommu_type1: Fix some sanity checks in detach group

 drivers/vfio/vfio_iommu_type1.c | 50 +++++++++++++++++----------------
 1 file changed, 26 insertions(+), 24 deletions(-)
```
#### [kvm-unit-tests PATCH v5 0/3] s390x: css: pv: css test adaptation for
##### From: Pierre Morel <pmorel@linux.ibm.com>

```c
From patchwork Fri Jan 22 13:27:37 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Pierre Morel <pmorel@linux.ibm.com>
X-Patchwork-Id: 12039447
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-11.8 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_PATCH,MAILING_LIST_MULTI,
	SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT autolearn=ham autolearn_force=no
	version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 0D0F6C433E0
	for <kvm@archiver.kernel.org>; Fri, 22 Jan 2021 13:29:26 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id C844123433
	for <kvm@archiver.kernel.org>; Fri, 22 Jan 2021 13:29:25 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727110AbhAVN3C (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Fri, 22 Jan 2021 08:29:02 -0500
Received: from mx0a-001b2d01.pphosted.com ([148.163.156.1]:58188 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1727681AbhAVN2q (ORCPT
        <rfc822;kvm@vger.kernel.org>); Fri, 22 Jan 2021 08:28:46 -0500
Received: from pps.filterd (m0098393.ppops.net [127.0.0.1])
        by mx0a-001b2d01.pphosted.com (8.16.0.42/8.16.0.42) with SMTP id
 10MD3dI0112907;
        Fri, 22 Jan 2021 08:27:48 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=ibm.com;
 h=from : to : cc : subject
 : date : message-id; s=pp1;
 bh=wkt/YZgm4OBhVRTTECT6wzWMp0unp4VmQx7dqCR87iE=;
 b=CdbGTsDCrLf3peitYtOVUXBYyLLqsxeeJar3nVK/3AnUj724gv1LM4DaoXnYy984NWeL
 f+D6besvaG8SHeUOGD68e4BM4ku+8ggISfU+pLp6cwxKRD1ehNrFWD3SUs6hx2bJO9lA
 kptr/BUGd+KlxLndR/fIBjo01sDBCGkMbm0QoUmgvHfwIyiECNHKCncLzJcyUOWEFcfI
 aJMgIWgsy1ttquRI0uqw03VR1DLCFwDOYT0MmP6ugBmivfPSeRl3oHaB155/CtETufOT
 p5vW/kpX2yQmQ79Pfbm2/5BAs6goyzSAvSk2x19zpoSuGutGcZ8HH7JD14kAj7M0Gklk bg==
Received: from pps.reinject (localhost [127.0.0.1])
        by mx0a-001b2d01.pphosted.com with ESMTP id 367x37b33r-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Fri, 22 Jan 2021 08:27:48 -0500
Received: from m0098393.ppops.net (m0098393.ppops.net [127.0.0.1])
        by pps.reinject (8.16.0.36/8.16.0.36) with SMTP id 10MD4kkX121641;
        Fri, 22 Jan 2021 08:27:48 -0500
Received: from ppma04ams.nl.ibm.com (63.31.33a9.ip4.static.sl-reverse.com
 [169.51.49.99])
        by mx0a-001b2d01.pphosted.com with ESMTP id 367x37b32x-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Fri, 22 Jan 2021 08:27:48 -0500
Received: from pps.filterd (ppma04ams.nl.ibm.com [127.0.0.1])
        by ppma04ams.nl.ibm.com (8.16.0.42/8.16.0.42) with SMTP id
 10MDRJhu003178;
        Fri, 22 Jan 2021 13:27:46 GMT
Received: from b06cxnps3075.portsmouth.uk.ibm.com
 (d06relay10.portsmouth.uk.ibm.com [9.149.109.195])
        by ppma04ams.nl.ibm.com with ESMTP id 367k0s8kv5-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Fri, 22 Jan 2021 13:27:45 +0000
Received: from d06av23.portsmouth.uk.ibm.com (d06av23.portsmouth.uk.ibm.com
 [9.149.105.59])
        by b06cxnps3075.portsmouth.uk.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id 10MDRgrs49807620
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Fri, 22 Jan 2021 13:27:43 GMT
Received: from d06av23.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id B4996A4057;
        Fri, 22 Jan 2021 13:27:42 +0000 (GMT)
Received: from d06av23.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 3B360A4040;
        Fri, 22 Jan 2021 13:27:42 +0000 (GMT)
Received: from oc3016276355.ibm.com (unknown [9.145.82.252])
        by d06av23.portsmouth.uk.ibm.com (Postfix) with ESMTP;
        Fri, 22 Jan 2021 13:27:42 +0000 (GMT)
From: Pierre Morel <pmorel@linux.ibm.com>
To: kvm@vger.kernel.org
Cc: linux-s390@vger.kernel.org, frankja@linux.ibm.com,
        david@redhat.com, thuth@redhat.com, cohuck@redhat.com,
        imbrenda@linux.ibm.com, drjones@redhat.com, pbonzini@redhat.com
Subject: [kvm-unit-tests PATCH v5 0/3] s390x: css: pv: css test adaptation for
 PV
Date: Fri, 22 Jan 2021 14:27:37 +0100
Message-Id: <1611322060-1972-1-git-send-email-pmorel@linux.ibm.com>
X-Mailer: git-send-email 1.8.3.1
X-TM-AS-GCONF: 00
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.343,18.0.737
 definitions=2021-01-22_09:2021-01-21,2021-01-22 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 suspectscore=0
 priorityscore=1501 impostorscore=0 clxscore=1015 lowpriorityscore=0
 mlxlogscore=999 malwarescore=0 bulkscore=0 phishscore=0 spamscore=0
 mlxscore=0 adultscore=0 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.12.0-2009150000 definitions=main-2101220071
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Hi all,
  
To adapt the CSS I/O tests to protected virtualisation we need
utilities to: 

1- allocate the I/O buffers in a private page using (patch 2)
   It must be in a dedicated page to avoid exporting code or
   guest private data to the host.
   We accept a size in byte and flags and allocate page integral
   memory to handle the Protected Virtualization.
 
2- share the I/O buffers with the host (patch 1)
   This patch uses the page allocator reworked by Claudio.
 
The 2 first patches are the implementation of the tools,
patch 3 is the modification of the css.c test for PV.

The checkpatch always asked me to modify MAINTAINERS,
so I added me as reviewer to be in copy for CSS at least.
May be we could create a finer grain MAINTAINERS in the
future.

regards,
Pierre


Pierre Morel (3):
  s390x: pv: implement routine to share/unshare memory
  s390x: define UV compatible I/O allocation
  s390x: css: pv: css test adaptation for PV

 lib/s390x/asm/uv.h    | 39 ++++++++++++++++++++++++
 lib/s390x/css.h       |  3 +-
 lib/s390x/css_lib.c   | 28 +++++------------
 lib/s390x/malloc_io.c | 71 +++++++++++++++++++++++++++++++++++++++++++
 lib/s390x/malloc_io.h | 45 +++++++++++++++++++++++++++
 s390x/Makefile        |  1 +
 s390x/css.c           | 43 ++++++++++++++++++--------
 7 files changed, 196 insertions(+), 34 deletions(-)
 create mode 100644 lib/s390x/malloc_io.c
 create mode 100644 lib/s390x/malloc_io.h
```
#### [PATCH v3 00/13] KVM: SVM: Misc SEV cleanups
##### From: Sean Christopherson <seanjc@google.com>

```c
From patchwork Fri Jan 22 20:21:31 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Sean Christopherson <seanjc@google.com>
X-Patchwork-Id: 12040413
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-21.3 required=3.0 tests=BAYES_00,DKIMWL_WL_MED,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT,
	USER_IN_DEF_DKIM_WL autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 32F25C433DB
	for <kvm@archiver.kernel.org>; Fri, 22 Jan 2021 20:23:56 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id ED5B723AFC
	for <kvm@archiver.kernel.org>; Fri, 22 Jan 2021 20:23:55 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728327AbhAVUXH (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Fri, 22 Jan 2021 15:23:07 -0500
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:43512 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1729823AbhAVUWc (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 22 Jan 2021 15:22:32 -0500
Received: from mail-yb1-xb4a.google.com (mail-yb1-xb4a.google.com
 [IPv6:2607:f8b0:4864:20::b4a])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 5D2E9C06174A
        for <kvm@vger.kernel.org>; Fri, 22 Jan 2021 12:21:52 -0800 (PST)
Received: by mail-yb1-xb4a.google.com with SMTP id c9so6563484ybs.8
        for <kvm@vger.kernel.org>; Fri, 22 Jan 2021 12:21:52 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=sender:reply-to:date:message-id:mime-version:subject:from:to:cc;
        bh=7RwhFYrcnoJXpobXbjPYpOWtvrgfjh0dgKM1o8v6SyQ=;
        b=k0MOtVqkrh587ap4u1TL5jVh9BDawHezCrrcAPdLUOfvQrD7yVpvrHnLcjIrkDKLDD
         u/BK0AYcLMIVZPDmGODEvPHpzZFKWVCQFfIGSvK6sWFS0/eHFOX9EaaPIHS0tYn/3ty0
         ZCUTO0P2vcm5JaV1yrsy7AfkhE9ZG88eick69Yc/WtIoPkwy+Sg9vZNe118M9qJ7Q2bf
         5tumrVEz0bJjWuj8xM1+BGwcOezUqZyqqGvI2Lcb+Ejun+SbrtNY9zxgrx8z1SX/Wt0Y
         Z4F42J6Jt4ZlGpGp0kAG3RblCAwGm+9BUDugBQ8xEDOGvVb0mT0f1WuE6cf/moAztY0x
         xaUA==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:sender:reply-to:date:message-id:mime-version
         :subject:from:to:cc;
        bh=7RwhFYrcnoJXpobXbjPYpOWtvrgfjh0dgKM1o8v6SyQ=;
        b=J7VbwFRAesYB6fBckNuk5VhREo24tgt3bmvNX3qhwPXbK8RKHQUCxqXm/3Z7uvRKJB
         bzrx/a/SiaXIQtofvjO6puLrgk3DBkPwMIgJKPP4YhcUXqyGwf06o3bkPR7B/DJ+x259
         EwRLwZ9rdznlZP1ASTz3whkSpwpU8ZRTKXn9T4XrOr+vxnIslL+KnAG4Z+gJC9/KKfbx
         MoYa7bwYOABof31YW/yH+oBg38iFGK02pR+SoxuX1Tiu99Y5a2Ygc2ToT+uPVqmUEjM0
         vjKiXjyADMleL3ZRZToGxx3wR4zNn41vty5Wx3kc2zbLm0tsDF068UHERzb/tb+Exmm0
         CuTw==
X-Gm-Message-State: AOAM5330mU5f3q9S6UrE6E+g9RUflr485hAvLy+Ky0inbG15iIYovNHW
        jSIwaqBs8aSzjE+XcFvpnzioNw6xjsE=
X-Google-Smtp-Source: 
 ABdhPJwcgryrk4tZExGjyr0534evimoJtjIFiSLe5u1LnX0hMunee/z+PGQjJP3z0dF1B9wvxTPVgd7CI0s=
Sender: "seanjc via sendgmr" <seanjc@seanjc798194.pdx.corp.google.com>
X-Received: from seanjc798194.pdx.corp.google.com
 ([2620:15c:f:10:1ea0:b8ff:fe73:50f5])
 (user=seanjc job=sendgmr) by 2002:a25:e90e:: with SMTP id
 n14mr8872967ybd.185.1611346911657;
 Fri, 22 Jan 2021 12:21:51 -0800 (PST)
Reply-To: Sean Christopherson <seanjc@google.com>
Date: Fri, 22 Jan 2021 12:21:31 -0800
Message-Id: <20210122202144.2756381-1-seanjc@google.com>
Mime-Version: 1.0
X-Mailer: git-send-email 2.30.0.280.ga3ce27912f-goog
Subject: [PATCH v3 00/13] KVM: SVM: Misc SEV cleanups
From: Sean Christopherson <seanjc@google.com>
To: Paolo Bonzini <pbonzini@redhat.com>,
        Dave Hansen <dave.hansen@linux.intel.com>,
        Andy Lutomirski <luto@kernel.org>,
        Peter Zijlstra <peterz@infradead.org>
Cc: Sean Christopherson <seanjc@google.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org, Borislav Petkov <bp@suse.de>,
        Tom Lendacky <thomas.lendacky@amd.com>,
        Brijesh Singh <brijesh.singh@amd.com>
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Minor bug fixes and refactorings of SEV related code, mainly to clean up
the KVM code for tracking whether or not SEV and SEV-ES are enabled.  E.g.
KVM has both sev_es and svm_sev_enabled(), and a global 'sev' flag while
also using 'sev' as a local variable in several places.

Based on v5.11-rc3.

v3:
 - Drop two patches: add a dedicated feature word for CPUID_0x8000001F,
   and use the new word to mask host CPUID in KVM.  I'll send these as a
   separate mini-series so that Boris can take them through tip.
 - Add a patch to remove dependency on
   CONFIG_AMD_MEM_ENCRYPT_ACTIVE_BY_DEFAULT. [Boris / Paolo]
 - Use kcalloc() instead of an open-coded equivalent. [Tom]
 - Nullify sev_asid_bitmap when freeing it during setup. [Tom]
 - Add a comment in sev_hardware_teardown() to document why it's safe to
   query the ASID bitmap without taking the lock. [Tom]
 - Collect reviews. [Tom and Brijesh]
v2:
 - Remove the kernel's sev_enabled instead of renaming it to sev_guest.
 - Fix various build issues. [Tom]
 - Remove stable tag from the patch to free sev_asid_bitmap.  Keeping the
   bitmap on failure is truly only a leak once svm_sev_enabled() is
   dropped later in the series.  It's still arguably a fix since KVM will
   unnecessarily keep memory, but it's not stable material. [Tom]
 - Collect one Ack. [Tom]

v1:
 - https://lkml.kernel.org/r/20210109004714.1341275-1-seanjc@google.com


Sean Christopherson (13):
  KVM: SVM: Zero out the VMCB array used to track SEV ASID association
  KVM: SVM: Free sev_asid_bitmap during init if SEV setup fails
  KVM: SVM: Move SEV module params/variables to sev.c
  x86/sev: Drop redundant and potentially misleading 'sev_enabled'
  KVM: SVM: Append "_enabled" to module-scoped SEV/SEV-ES control
    variables
  KVM: SVM: Condition sev_enabled and sev_es_enabled on
    CONFIG_KVM_AMD_SEV=y
  KVM: SVM: Enable SEV/SEV-ES functionality by default (when supported)
  KVM: SVM: Unconditionally invoke sev_hardware_teardown()
  KVM: SVM: Explicitly check max SEV ASID during sev_hardware_setup()
  KVM: SVM: Move SEV VMCB tracking allocation to sev.c
  KVM: SVM: Drop redundant svm_sev_enabled() helper
  KVM: SVM: Remove an unnecessary prototype declaration of
    sev_flush_asids()
  KVM: SVM: Skip SEV cache flush if no ASIDs have been used

 arch/x86/include/asm/mem_encrypt.h |  1 -
 arch/x86/kvm/svm/sev.c             | 72 +++++++++++++++++++++---------
 arch/x86/kvm/svm/svm.c             | 35 +++++----------
 arch/x86/kvm/svm/svm.h             |  8 +---
 arch/x86/mm/mem_encrypt.c          | 12 +++--
 arch/x86/mm/mem_encrypt_identity.c |  1 -
 6 files changed, 67 insertions(+), 62 deletions(-)
```
#### [PATCH v3 0/2] x86/cpufeatures: KVM: Add mem encrypt word
##### From: Sean Christopherson <seanjc@google.com>

```c
From patchwork Fri Jan 22 20:40:45 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Sean Christopherson <seanjc@google.com>
X-Patchwork-Id: 12040429
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-21.3 required=3.0 tests=BAYES_00,DKIMWL_WL_MED,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT,
	USER_IN_DEF_DKIM_WL autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 3DCFEC433E0
	for <kvm@archiver.kernel.org>; Fri, 22 Jan 2021 20:42:22 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 1067F23B04
	for <kvm@archiver.kernel.org>; Fri, 22 Jan 2021 20:42:22 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1730593AbhAVUmE (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Fri, 22 Jan 2021 15:42:04 -0500
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:47638 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1730424AbhAVUlh (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 22 Jan 2021 15:41:37 -0500
Received: from mail-yb1-xb4a.google.com (mail-yb1-xb4a.google.com
 [IPv6:2607:f8b0:4864:20::b4a])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 7203EC061786
        for <kvm@vger.kernel.org>; Fri, 22 Jan 2021 12:40:56 -0800 (PST)
Received: by mail-yb1-xb4a.google.com with SMTP id v187so6662749ybv.21
        for <kvm@vger.kernel.org>; Fri, 22 Jan 2021 12:40:56 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=sender:reply-to:date:message-id:mime-version:subject:from:to:cc;
        bh=FIOLACkSO6nryo8JeCYd3HKHXp0oZhl7wC2aMQwMaBA=;
        b=SzyXwjEX2caDz80LmuG/3wfIagraEzkLGr5vD9SXkZ1xc4ZDawzMdOrzZ+pdApm9Ba
         eyE5GGffRAqt5F/y9/pnXY7uBdh+MARNJsgF+Xb2tDsXQzrr+Z+pSkdP1mQo1W15Lcgf
         4Q8pORTcoXNTqCpls4c9Pmb4rHE9br3NLgy0+AK7IV8AEJbW7LvzUIOBBYLj9+jLsHq9
         EI5qSXrZdjWbWqFtj7Hcnc+TNjls6BKgUfDIyxVGSX7wuS6Pz884X8N1Ei62u1jjQ2Qe
         oH8PbZ1XFmdOp5V+exKBg2OAiC22iCVyhkF8OZ91T7iRZd1t9wyvQH8Kf6O/Lwefinnr
         ws1A==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:sender:reply-to:date:message-id:mime-version
         :subject:from:to:cc;
        bh=FIOLACkSO6nryo8JeCYd3HKHXp0oZhl7wC2aMQwMaBA=;
        b=ZblefyGDBAaphnd6LiwudGmlKvgBg0Zc02mxEL16/yU8ZhhisLOEXj3a2fI54EUp9D
         VJvIvCLE1/lc+s1bc7jmLX2lnd6b3pgsh+i0xIbD9thjGjDVAZbp8BgIInKc5deYpmnj
         lznOC8PUXH5hGwhj8hREKKD9ANwtaOFQ43/B2AVkDqdR3qa465/Up/X17LVsEHkCZL1j
         a9vwt4BQTgkkFB/jFvByGiOx9Bole5Bsp0Lx7KOgFOYA+xquGK4+MjNp65rZx0PGwjDz
         rRi1KG/Dvm6wqs/G1CG5CLAMx1eDNgbw2AxLIdsS3UDYNmPtAYWsFThCYGpHMhAtiqQ4
         oFBQ==
X-Gm-Message-State: AOAM532+aHDwllvOwiwSYVKl223rN2p4kAqyXb2RIQByKxuA2c6ZzlO5
        i/Dcd3k1TMjRepji2V8oTOGHqkkdBuA=
X-Google-Smtp-Source: 
 ABdhPJxw2kXOylXelY+e+VrRcikSrMQvWa+F8P8gAbto9U4XixM49Rj0DclM5mdOXsaVfZna2NR5UI2F3PE=
Sender: "seanjc via sendgmr" <seanjc@seanjc798194.pdx.corp.google.com>
X-Received: from seanjc798194.pdx.corp.google.com
 ([2620:15c:f:10:1ea0:b8ff:fe73:50f5])
 (user=seanjc job=sendgmr) by 2002:a25:cacc:: with SMTP id
 a195mr9176545ybg.306.1611348055581;
 Fri, 22 Jan 2021 12:40:55 -0800 (PST)
Reply-To: Sean Christopherson <seanjc@google.com>
Date: Fri, 22 Jan 2021 12:40:45 -0800
Message-Id: <20210122204047.2860075-1-seanjc@google.com>
Mime-Version: 1.0
X-Mailer: git-send-email 2.30.0.280.ga3ce27912f-goog
Subject: [PATCH v3 0/2] x86/cpufeatures: KVM: Add mem encrypt word
From: Sean Christopherson <seanjc@google.com>
To: Thomas Gleixner <tglx@linutronix.de>,
        Ingo Molnar <mingo@redhat.com>, Borislav Petkov <bp@alien8.de>,
        x86@kernel.org, Paolo Bonzini <pbonzini@redhat.com>
Cc: "H. Peter Anvin" <hpa@zytor.com>,
        Sean Christopherson <seanjc@google.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>, linux-kernel@vger.kernel.org,
        kvm@vger.kernel.org, Brijesh Singh <brijesh.singh@amd.com>,
        Tom Lendacky <thomas.lendacky@amd.com>
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Gather the AMD memory encryption features into a dedicated word for CPUID
0x8000001F[EAX] and use the new word in KVM to adjust its reporting of SEV
support based on host kernel enabling.

Paolo, can you ack patch 2?  Boris is planning on taking this through the
tip tree.  Thanks!

Split out from a larger KVM SEV cleanup series[*], thus the somewhat
questionable v3 tag.

Based on v5.11-rc4.

[*] https://lkml.kernel.org/r/20210114003708.3798992-1-seanjc@google.com

Sean Christopherson (2):
  x86/cpufeatures: Assign dedicated feature word for
    CPUID_0x8000001F[EAX]
  KVM: x86: Override reported SME/SEV feature flags with host mask

 arch/x86/include/asm/cpufeature.h              |  7 +++++--
 arch/x86/include/asm/cpufeatures.h             | 17 +++++++++++------
 arch/x86/include/asm/disabled-features.h       |  3 ++-
 arch/x86/include/asm/required-features.h       |  3 ++-
 arch/x86/kernel/cpu/common.c                   |  3 +++
 arch/x86/kernel/cpu/scattered.c                |  5 -----
 arch/x86/kvm/cpuid.c                           |  2 ++
 arch/x86/kvm/cpuid.h                           |  1 +
 tools/arch/x86/include/asm/disabled-features.h |  3 ++-
 tools/arch/x86/include/asm/required-features.h |  3 ++-
 10 files changed, 30 insertions(+), 17 deletions(-)
```
