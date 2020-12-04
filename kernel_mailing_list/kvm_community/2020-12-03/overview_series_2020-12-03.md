#### [PATCH RFC v4 01/15] linux-header: Update linux/kvm.h
##### From: Yifei Jiang <jiangyifei@huawei.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Yifei Jiang <jiangyifei@huawei.com>
X-Patchwork-Id: 11948663
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-18.9 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,MENTIONS_GIT_HOSTING,SPF_HELO_NONE,SPF_PASS,
	UNWANTED_LANGUAGE_BODY,URIBL_BLOCKED,USER_AGENT_GIT autolearn=ham
	autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 276B5C83016
	for <kvm@archiver.kernel.org>; Thu,  3 Dec 2020 12:48:26 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id DAECD22245
	for <kvm@archiver.kernel.org>; Thu,  3 Dec 2020 12:48:25 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2387813AbgLCMsO (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Thu, 3 Dec 2020 07:48:14 -0500
Received: from szxga04-in.huawei.com ([45.249.212.190]:8624 "EHLO
        szxga04-in.huawei.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S2387653AbgLCMsO (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 3 Dec 2020 07:48:14 -0500
Received: from DGGEMS403-HUB.china.huawei.com (unknown [172.30.72.60])
        by szxga04-in.huawei.com (SkyGuard) with ESMTP id 4CmwZk5Mrdz15X06;
        Thu,  3 Dec 2020 20:46:54 +0800 (CST)
Received: from huawei.com (10.174.186.236) by DGGEMS403-HUB.china.huawei.com
 (10.3.19.203) with Microsoft SMTP Server id 14.3.487.0; Thu, 3 Dec 2020
 20:47:14 +0800
From: Yifei Jiang <jiangyifei@huawei.com>
To: <qemu-devel@nongnu.org>, <qemu-riscv@nongnu.org>
CC: <kvm-riscv@lists.infradead.org>, <kvm@vger.kernel.org>,
        <libvir-list@redhat.com>, <anup.patel@wdc.com>,
        <palmer@dabbelt.com>, <Alistair.Francis@wdc.com>,
        <sagark@eecs.berkeley.edu>, <kbastian@mail.uni-paderborn.de>,
        <victor.zhangxiaofeng@huawei.com>, <wu.wubin@huawei.com>,
        <zhang.zhanghailiang@huawei.com>, <dengkai1@huawei.com>,
        <yinyipeng1@huawei.com>, Yifei Jiang <jiangyifei@huawei.com>
Subject: [PATCH RFC v4 01/15] linux-header: Update linux/kvm.h
Date: Thu, 3 Dec 2020 20:46:49 +0800
Message-ID: <20201203124703.168-2-jiangyifei@huawei.com>
X-Mailer: git-send-email 2.26.2.windows.1
In-Reply-To: <20201203124703.168-1-jiangyifei@huawei.com>
References: <20201203124703.168-1-jiangyifei@huawei.com>
MIME-Version: 1.0
X-Originating-IP: [10.174.186.236]
X-CFilter-Loop: Reflected
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Update linux-headers/linux/kvm.h from
https://github.com/avpatel/linux/tree/riscv_kvm_v15.
Only use this header file, so here do not update all linux headers by
update-linux-headers.sh before above KVM series is accepted.

Signed-off-by: Yifei Jiang <jiangyifei@huawei.com>
Signed-off-by: Yipeng Yin <yinyipeng1@huawei.com>
---
 linux-headers/linux/kvm.h | 8 ++++++++
 1 file changed, 8 insertions(+)

```
#### [PATCH v3 1/2] vfio-mdev: Wire in a request handler for mdev parent
##### From: Eric Farman <farman@linux.ibm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Eric Farman <farman@linux.ibm.com>
X-Patchwork-Id: 11949677
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.8 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT autolearn=ham
	autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 85BDAC433FE
	for <kvm@archiver.kernel.org>; Thu,  3 Dec 2020 21:38:52 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 2E785207C9
	for <kvm@archiver.kernel.org>; Thu,  3 Dec 2020 21:38:51 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1731516AbgLCVig (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Thu, 3 Dec 2020 16:38:36 -0500
Received: from mx0a-001b2d01.pphosted.com ([148.163.156.1]:4074 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1731401AbgLCVif (ORCPT
        <rfc822;kvm@vger.kernel.org>); Thu, 3 Dec 2020 16:38:35 -0500
Received: from pps.filterd (m0098394.ppops.net [127.0.0.1])
        by mx0a-001b2d01.pphosted.com (8.16.0.42/8.16.0.42) with SMTP id
 0B3LX00g115821;
        Thu, 3 Dec 2020 16:37:52 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=ibm.com;
 h=from : to : cc : subject
 : date : message-id : in-reply-to : references; s=pp1;
 bh=5xi0ktPHLi1lr5LE+kg0/pYOT31VTadV+xm+i4uAEjw=;
 b=LuZsRmJEX7kl8ZPW5x6sVZKtjmPDOW1v8oJbtUUgWPVDxb1rzn+EkAccWi+BRaOV1gOi
 hxw5LPz0Vchz49YoUJ+XGp9tykb6TAM5WEaO7JKhcyQob91NotyRTBJegbeO6AcbiDh5
 72a2XylYVu12XnJfF+xDaNkVy2SaR0Sbr0aNxgH0c72iEBiJ2kYNCd4czMxJzTOeomQE
 HvqRNy+8Kc541+wZkZashBelIFaIp2K8McX+YAOlUmR4lZP7T/V/Wqaw3Sbu8rFMrpOD
 kmSYq6HXf/+JG7rgMLMIuaz2A4vtLqvb6Q4njyUfFfPC94AEozr7rdq5nIu9HF8slzTM GA==
Received: from pps.reinject (localhost [127.0.0.1])
        by mx0a-001b2d01.pphosted.com with ESMTP id 35773w9uus-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Thu, 03 Dec 2020 16:37:52 -0500
Received: from m0098394.ppops.net (m0098394.ppops.net [127.0.0.1])
        by pps.reinject (8.16.0.36/8.16.0.36) with SMTP id 0B3LWxwG115700;
        Thu, 3 Dec 2020 16:37:51 -0500
Received: from ppma03fra.de.ibm.com (6b.4a.5195.ip4.static.sl-reverse.com
 [149.81.74.107])
        by mx0a-001b2d01.pphosted.com with ESMTP id 35773w9uta-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Thu, 03 Dec 2020 16:37:51 -0500
Received: from pps.filterd (ppma03fra.de.ibm.com [127.0.0.1])
        by ppma03fra.de.ibm.com (8.16.0.42/8.16.0.42) with SMTP id
 0B3LXBoO025210;
        Thu, 3 Dec 2020 21:37:48 GMT
Received: from b06cxnps3074.portsmouth.uk.ibm.com
 (d06relay09.portsmouth.uk.ibm.com [9.149.109.194])
        by ppma03fra.de.ibm.com with ESMTP id 353e688b2t-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Thu, 03 Dec 2020 21:37:48 +0000
Received: from d06av21.portsmouth.uk.ibm.com (d06av21.portsmouth.uk.ibm.com
 [9.149.105.232])
        by b06cxnps3074.portsmouth.uk.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id 0B3LZF8I26608102
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Thu, 3 Dec 2020 21:35:15 GMT
Received: from d06av21.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id B287A52050;
        Thu,  3 Dec 2020 21:35:15 +0000 (GMT)
Received: from tuxmaker.boeblingen.de.ibm.com (unknown [9.152.85.9])
        by d06av21.portsmouth.uk.ibm.com (Postfix) with ESMTPS id 907045204F;
        Thu,  3 Dec 2020 21:35:15 +0000 (GMT)
Received: by tuxmaker.boeblingen.de.ibm.com (Postfix, from userid 4958)
        id 15FF1E01DC; Thu,  3 Dec 2020 22:35:15 +0100 (CET)
From: Eric Farman <farman@linux.ibm.com>
To: Alex Williamson <alex.williamson@redhat.com>,
        Cornelia Huck <cohuck@redhat.com>
Cc: Kirti Wankhede <kwankhede@nvidia.com>,
        Halil Pasic <pasic@linux.ibm.com>,
        Matthew Rosato <mjrosato@linux.ibm.com>,
        linux-s390@vger.kernel.org, kvm@vger.kernel.org,
        Eric Farman <farman@linux.ibm.com>
Subject: [PATCH v3 1/2] vfio-mdev: Wire in a request handler for mdev parent
Date: Thu,  3 Dec 2020 22:35:11 +0100
Message-Id: <20201203213512.49357-2-farman@linux.ibm.com>
X-Mailer: git-send-email 2.17.1
In-Reply-To: <20201203213512.49357-1-farman@linux.ibm.com>
References: <20201203213512.49357-1-farman@linux.ibm.com>
X-TM-AS-GCONF: 00
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.312,18.0.737
 definitions=2020-12-03_12:2020-12-03,2020-12-03 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 bulkscore=0 phishscore=0
 clxscore=1015 lowpriorityscore=0 impostorscore=0 suspectscore=0 mlxscore=0
 malwarescore=0 adultscore=0 spamscore=0 mlxlogscore=999 priorityscore=1501
 classifier=spam adjust=0 reason=mlx scancount=1 engine=8.12.0-2009150000
 definitions=main-2012030124
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

While performing some destructive tests with vfio-ccw, where the
paths to a device are forcible removed and thus the device itself
is unreachable, it is rather easy to end up in an endless loop in
vfio_del_group_dev() due to the lack of a request callback for the
associated device.

In this example, one MDEV (77c) is used by a guest, while another
(77b) is not. The symptom is that the iommu is detached from the
mdev for 77b, but not 77c, until that guest is shutdown:

    [  238.794867] vfio_ccw 0.0.077b: MDEV: Unregistering
    [  238.794996] vfio_mdev 11f2d2bc-4083-431d-a023-eff72715c4f0: Removing from iommu group 2
    [  238.795001] vfio_mdev 11f2d2bc-4083-431d-a023-eff72715c4f0: MDEV: detaching iommu
    [  238.795036] vfio_ccw 0.0.077c: MDEV: Unregistering
    ...silence...

Let's wire in the request call back to the mdev device, so that a
device being physically removed from the host can be (gracefully?)
handled by the parent device at the time the device is removed.

Add a message when registering the device if a driver doesn't
provide this callback, so a clue is given that this same loop
may be encountered in a similar situation, and a message when
this occurs instead of the awkward silence noted above.

Signed-off-by: Eric Farman <farman@linux.ibm.com>
Reviewed-by: Cornelia Huck <cohuck@redhat.com>
---
 drivers/vfio/mdev/mdev_core.c |  4 ++++
 drivers/vfio/mdev/vfio_mdev.c | 13 +++++++++++++
 include/linux/mdev.h          |  4 ++++
 3 files changed, 21 insertions(+)

```
#### [PATCH 1/1] KVM: x86: ignore SIPIs that are received while not in wait-for-sipi state
##### From: Maxim Levitsky <mlevitsk@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Maxim Levitsky <mlevitsk@redhat.com>
X-Patchwork-Id: 11948961
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-17.2 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_CR_TRAILER,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS
	autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 8B6CBC1B0D9
	for <kvm@archiver.kernel.org>; Thu,  3 Dec 2020 14:51:32 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 6670F222A4
	for <kvm@archiver.kernel.org>; Thu,  3 Dec 2020 14:35:21 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2436616AbgLCOfI (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Thu, 3 Dec 2020 09:35:08 -0500
Received: from us-smtp-delivery-124.mimecast.com ([216.205.24.124]:35325 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S2436598AbgLCOfI (ORCPT
        <rfc822;kvm@vger.kernel.org>); Thu, 3 Dec 2020 09:35:08 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1607006022;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding:
         in-reply-to:in-reply-to:references:references;
        bh=1XqBhc/70x5UiCX+gliKZSRAhGKjt02d3xbD8cQLd3A=;
        b=UqO0jNHp7Gy5jPvUVFieqKSdNpUajrPKQUX0Dn5YcGLFEpvxac4sWhV8b3DET538hqMR1z
        5aRuQKbQBgoCpfqjokMwyyjt1Wg1pU/O1V2kySeDSDCHMouFgOJRWEg6XMkDTr/AM9fycI
        4CJk8HrCekdFzf6/0N8yyhl9swQaKNA=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-299-sEQTVC7HM7iPVfFkzPwXPA-1; Thu, 03 Dec 2020 09:33:40 -0500
X-MC-Unique: sEQTVC7HM7iPVfFkzPwXPA-1
Received: from smtp.corp.redhat.com (int-mx01.intmail.prod.int.phx2.redhat.com
 [10.5.11.11])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 841931076029;
        Thu,  3 Dec 2020 14:33:38 +0000 (UTC)
Received: from localhost.localdomain (unknown [10.35.206.228])
        by smtp.corp.redhat.com (Postfix) with ESMTP id D839D5B4A0;
        Thu,  3 Dec 2020 14:33:25 +0000 (UTC)
From: Maxim Levitsky <mlevitsk@redhat.com>
To: kvm@vger.kernel.org
Cc: Sean Christopherson <sean.j.christopherson@intel.com>,
        Joerg Roedel <joro@8bytes.org>, Ingo Molnar <mingo@redhat.com>,
        x86@kernel.org (maintainer:X86 ARCHITECTURE (32-BIT AND 64-BIT)),
        "H. Peter Anvin" <hpa@zytor.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Paolo Bonzini <pbonzini@redhat.com>,
        Borislav Petkov <bp@alien8.de>,
        Jim Mattson <jmattson@google.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        linux-kernel@vger.kernel.org, Thomas Gleixner <tglx@linutronix.de>,
        Maxim Levitsky <mlevitsk@redhat.com>
Subject: [PATCH 1/1] KVM: x86: ignore SIPIs that are received while not in
 wait-for-sipi state
Date: Thu,  3 Dec 2020 16:33:19 +0200
Message-Id: <20201203143319.159394-2-mlevitsk@redhat.com>
In-Reply-To: <20201203143319.159394-1-mlevitsk@redhat.com>
References: <20201203143319.159394-1-mlevitsk@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.11
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

In the commit 1c96dcceaeb3
("KVM: x86: fix apic_accept_events vs check_nested_events"),

we accidently started latching SIPIs that are received while the cpu is not
waiting for them.

This causes vCPUs to never enter a halted state.

Fixes: 1c96dcceaeb3 ("KVM: x86: fix apic_accept_events vs check_nested_events")
Signed-off-by: Maxim Levitsky <mlevitsk@redhat.com>
---
 arch/x86/kvm/lapic.c | 15 ++++++++-------
 1 file changed, 8 insertions(+), 7 deletions(-)

```
#### [PATCH RFC 1/3] RISC-V: KVM: Change the method of calculating cycles to nanoseconds
##### From: Yifei Jiang <jiangyifei@huawei.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Yifei Jiang <jiangyifei@huawei.com>
X-Patchwork-Id: 11948605
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.7 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED,USER_AGENT_GIT
	autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id E918EC83013
	for <kvm@archiver.kernel.org>; Thu,  3 Dec 2020 12:22:18 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 9D6B922244
	for <kvm@archiver.kernel.org>; Thu,  3 Dec 2020 12:22:18 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2388739AbgLCMV4 (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Thu, 3 Dec 2020 07:21:56 -0500
Received: from szxga05-in.huawei.com ([45.249.212.191]:9098 "EHLO
        szxga05-in.huawei.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1730455AbgLCMVz (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 3 Dec 2020 07:21:55 -0500
Received: from DGGEMS406-HUB.china.huawei.com (unknown [172.30.72.60])
        by szxga05-in.huawei.com (SkyGuard) with ESMTP id 4Cmw0N6GcxzLywj;
        Thu,  3 Dec 2020 20:20:36 +0800 (CST)
Received: from huawei.com (10.174.186.236) by DGGEMS406-HUB.china.huawei.com
 (10.3.19.206) with Microsoft SMTP Server id 14.3.487.0; Thu, 3 Dec 2020
 20:21:05 +0800
From: Yifei Jiang <jiangyifei@huawei.com>
To: <anup.patel@wdc.com>, <atish.patra@wdc.com>,
        <paul.walmsley@sifive.com>, <palmer@dabbelt.com>,
        <aou@eecs.berkeley.edu>, <pbonzini@redhat.com>
CC: <kvm-riscv@lists.infradead.org>, <kvm@vger.kernel.org>,
        <linux-riscv@lists.infradead.org>, <linux-kernel@vger.kernel.org>,
        <victor.zhangxiaofeng@huawei.com>, <wu.wubin@huawei.com>,
        <zhang.zhanghailiang@huawei.com>, <dengkai1@huawei.com>,
        <yinyipeng1@huawei.com>, Yifei Jiang <jiangyifei@huawei.com>
Subject: [PATCH RFC 1/3] RISC-V: KVM: Change the method of calculating cycles
 to nanoseconds
Date: Thu, 3 Dec 2020 20:18:37 +0800
Message-ID: <20201203121839.308-2-jiangyifei@huawei.com>
X-Mailer: git-send-email 2.26.2.windows.1
In-Reply-To: <20201203121839.308-1-jiangyifei@huawei.com>
References: <20201203121839.308-1-jiangyifei@huawei.com>
MIME-Version: 1.0
X-Originating-IP: [10.174.186.236]
X-CFilter-Loop: Reflected
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Because we will introduce the dynamic guest frequency later, we
can't use the fixed mult and shift to calculate nanoseconds.

Signed-off-by: Yifei Jiang <jiangyifei@huawei.com>
Signed-off-by: Yipeng Yin <yinyipeng1@huawei.com>
---
 arch/riscv/include/asm/kvm_vcpu_timer.h | 3 ---
 arch/riscv/kvm/vcpu_timer.c             | 3 +--
 2 files changed, 1 insertion(+), 5 deletions(-)

```
#### [PATCH] kvm: svm: de-allocate svm_cpu_data for all cpus in svm_cpu_uninit()
##### From: Jacob Xu <jacobhxu@google.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Jacob Xu <jacobhxu@google.com>
X-Patchwork-Id: 11949593
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-26.3 required=3.0 tests=BAYES_00,DKIMWL_WL_MED,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_CR_TRAILER,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,
	USER_AGENT_GIT,USER_IN_DEF_DKIM_WL autolearn=ham autolearn_force=no
	version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 8D5F6C433FE
	for <kvm@archiver.kernel.org>; Thu,  3 Dec 2020 20:57:12 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 37FAB207A8
	for <kvm@archiver.kernel.org>; Thu,  3 Dec 2020 20:57:12 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2387520AbgLCU5H (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Thu, 3 Dec 2020 15:57:07 -0500
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:43916 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726920AbgLCU5H (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 3 Dec 2020 15:57:07 -0500
Received: from mail-pj1-x1049.google.com (mail-pj1-x1049.google.com
 [IPv6:2607:f8b0:4864:20::1049])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 06336C061A52
        for <kvm@vger.kernel.org>; Thu,  3 Dec 2020 12:56:27 -0800 (PST)
Received: by mail-pj1-x1049.google.com with SMTP id o13so2015886pjp.1
        for <kvm@vger.kernel.org>; Thu, 03 Dec 2020 12:56:27 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=sender:date:message-id:mime-version:subject:from:to:cc;
        bh=S5ra3fFtwyrR4DBSDAkXB7bmFSTJjJvoJm1aScqSvD8=;
        b=LBTW4G1yq8Tlr8j60sdrqz5HWAARs1V+8aIMhV3V5AQLPx6JTlpixUJ5GfUFelcDwW
         wXHs1SeZdVZXtuID6Oekg9t3XeAP4+ILetytMukbpIbSjcIGt0KpUh7r5ihOA7uYlvcY
         jnb7iYbl4p7UsgRbX5OuBqAKSmm0x4WiiStX7RazsIyIWOfnXG6avJc44OEP48/9R/FI
         WHXpHTzUZKF35lQZHHryI4l7Up3rMNW6Rhz+YFgAY6Pf/AKrOYpY0k3maORqmuMNkB+9
         UeqK8C2XVnlf+XLCKB7Zfa+8p68DYcRLpmc5CQKVcQ53zzlquK/3bKdiJjp8cunqIhUt
         UYoA==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:sender:date:message-id:mime-version:subject:from
         :to:cc;
        bh=S5ra3fFtwyrR4DBSDAkXB7bmFSTJjJvoJm1aScqSvD8=;
        b=FOyOmLbU79UPWOWV2jN95sca667+p89w64PkatQcyKG3YCVcsjd70YV6DbAq55Dym8
         QIh5hHQ6AN+E5Rp3CdtRgxMaX/SLGZdFpMrg5A1h/kt88NwfFIbW3W+PGZwrNm1rvfE4
         fm3FV8qNEGFzjOMBCYfA72yJOVBRQ/TsJkWluh/XA/BNiDrNAUsiM/xcsXqPae2TlZRL
         KAXVBKNwpdcnd5BGpVtVgIvmnbMDfdcynFBw0Xb6xpKJamgLY1oX0H7Oqo1i7rnfq0tM
         djTfoUBdc6GxKymXGCPG7M8zunhM/oLVVhjuB6cDLvX08lO8aCt8UlUeydDCZSd10vZz
         bhSw==
X-Gm-Message-State: AOAM532c23JllwpdK07I23AgdeN9kps2v/XVKu5SEVBClYLE4Uz3aN10
        w/CALXz+U0ZyPYj0fB02CyR1vdRQ7J2w1w==
X-Google-Smtp-Source: 
 ABdhPJwsY5PNMZvpoZhrIaqeJ0b9FPlsxwsCuhz3fm3arOdqksu0Bt1ad3hJMyJCA0wd5j0AzpgGDqTjitcjcg==
Sender: "jacobhxu via sendmgr" <jacobhxu@mhmmm.sea.corp.google.com>
X-Received: from mhmmm.sea.corp.google.com
 ([2620:15c:100:202:f693:9fff:feef:a9a1])
 (user=jacobhxu job=sendmgr) by 2002:a17:90a:bc0a:: with SMTP id
 w10mr847025pjr.79.1607028986454; Thu, 03 Dec 2020 12:56:26 -0800 (PST)
Date: Thu,  3 Dec 2020 12:56:19 -0800
Message-Id: <20201203205619.1776417-1-jacobhxu@google.com>
Mime-Version: 1.0
X-Mailer: git-send-email 2.29.2.576.ga3fc446d84-goog
Subject: [PATCH] kvm: svm: de-allocate svm_cpu_data for all cpus in
 svm_cpu_uninit()
From: Jacob Xu <jacobhxu@google.com>
To: Paolo Bonzini <pbonzini@redhat.com>,
        Sean Christopherson <seanjc@google.com>,
        Jim Mattson <jmattson@google.com>,
        Oliver Upton <oupton@google.com>
Cc: kvm@vger.kernel.org, linux-kernel@vger.kernel.org,
        Jacob Xu <jacobhxu@google.com>
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The cpu arg for svm_cpu_uninit() was previously ignored resulting in the
per cpu structure svm_cpu_data not being de-allocated for all cpus.

Signed-off-by: Jacob Xu <jacobhxu@google.com>
---
 arch/x86/kvm/svm/svm.c | 4 ++--
 1 file changed, 2 insertions(+), 2 deletions(-)

```
#### [PATCH] kvm: svm: de-allocate svm_cpu_data for all cpus in svm_cpu_uninit()
##### From: Jacob Xu <jacobhxu@google.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Jacob Xu <jacobhxu@google.com>
X-Patchwork-Id: 11949595
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-26.3 required=3.0 tests=BAYES_00,DKIMWL_WL_MED,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_CR_TRAILER,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,
	USER_AGENT_GIT,USER_IN_DEF_DKIM_WL autolearn=unavailable autolearn_force=no
	version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 185A6C4361A
	for <kvm@archiver.kernel.org>; Thu,  3 Dec 2020 21:00:42 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id AC8A3221F0
	for <kvm@archiver.kernel.org>; Thu,  3 Dec 2020 21:00:41 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727850AbgLCVAX (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Thu, 3 Dec 2020 16:00:23 -0500
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:44416 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726314AbgLCVAX (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 3 Dec 2020 16:00:23 -0500
Received: from mail-pl1-x64a.google.com (mail-pl1-x64a.google.com
 [IPv6:2607:f8b0:4864:20::64a])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 43B93C061A51
        for <kvm@vger.kernel.org>; Thu,  3 Dec 2020 12:59:43 -0800 (PST)
Received: by mail-pl1-x64a.google.com with SMTP id 4so1881373pla.6
        for <kvm@vger.kernel.org>; Thu, 03 Dec 2020 12:59:43 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=sender:date:message-id:mime-version:subject:from:to:cc;
        bh=S5ra3fFtwyrR4DBSDAkXB7bmFSTJjJvoJm1aScqSvD8=;
        b=CMgmPGQ3LRAJ91emyWbIDeeu4Npdy86zsS9HBSAc8ghZ8AyFtq8IPAKujurb3BXMl6
         qydVnY5AUbZc+vdzxNbWWmIYmU4B56Pn368RqYqcA/O84Rn1fAmI+r5iI/4QxefdR5L4
         iQPuaefyDoLSUm69oF0b5m4cjGZdtvwKugIsWO4AGpChjbjG3aZNa/TpTARfvmP7XDMv
         kYG4ybDJe0sJEk612YLAPX11BceZM8h3ap3K0/bEhhEFT2n2BI4/ChT6ITK0bUC3ZAtT
         gej5444rFOdUyWbg53TWG8bvVleKc4MyYctWo1+IF5Y2QdMGnyziGqHn4tNa6P/rBz3k
         R3fw==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:sender:date:message-id:mime-version:subject:from
         :to:cc;
        bh=S5ra3fFtwyrR4DBSDAkXB7bmFSTJjJvoJm1aScqSvD8=;
        b=l4BaOkRfV1slAQ+wc0ZcLOYJjE1qKRS6Lm5xQg9ubGuA0XDKjkHgn4b5yatlHBBpNI
         coQkwpeJ+j/c0RoDAICE1AwKNRX8gZ7aOUgF9ZShlu+pWo324RpVZnJV+/Lg36vMjzd+
         plBjBSL38yTjXMMHpR9ASQpP7hINkauNm84hMzH9defslcWWIlqp2eKGngtbmQPrnpoZ
         vY3/ARr99Yi5wYiDFp1zMJzqaQVEB5R8UOjO+iyYJiotnf63VoXB1OfDvc8hurSVdkeI
         sKgtwi4P3JyALzWFZXyADjk97YvH8k6OvsS5bBHiSQTUaYWDtkY8MRzrFGqd0CSF3Uax
         jwPw==
X-Gm-Message-State: AOAM5335QjkkKNvlCq9pd4ZcrQ0z2+qh4DVf8k+HE45g0zd2ogHF145F
        Bzl44WAaFfCQtbLdSJjCNABm3AFbXih8Ng==
X-Google-Smtp-Source: 
 ABdhPJzp6sEpJwizJg9kJ4t6HFh8/cL5/4seSshW8xQdAExolaPsro05znE1zqmIooU9dIASPm7CyJikDZMC8w==
Sender: "jacobhxu via sendmgr" <jacobhxu@mhmmm.sea.corp.google.com>
X-Received: from mhmmm.sea.corp.google.com
 ([2620:15c:100:202:f693:9fff:feef:a9a1])
 (user=jacobhxu job=sendmgr) by 2002:a62:1a16:0:b029:197:eabc:9b74 with SMTP
 id a22-20020a621a160000b0290197eabc9b74mr683802pfa.62.1607029182775; Thu, 03
 Dec 2020 12:59:42 -0800 (PST)
Date: Thu,  3 Dec 2020 12:59:39 -0800
Message-Id: <20201203205939.1783969-1-jacobhxu@google.com>
Mime-Version: 1.0
X-Mailer: git-send-email 2.29.2.576.ga3fc446d84-goog
Subject: [PATCH] kvm: svm: de-allocate svm_cpu_data for all cpus in
 svm_cpu_uninit()
From: Jacob Xu <jacobhxu@google.com>
To: Paolo Bonzini <pbonzini@redhat.com>,
        Sean Christopherson <seanjc@google.com>,
        Jim Mattson <jmattson@google.com>,
        Oliver Upton <oupton@google.com>
Cc: kvm@vger.kernel.org, linux-kernel@vger.kernel.org,
        Jacob Xu <jacobhxu@google.com>
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The cpu arg for svm_cpu_uninit() was previously ignored resulting in the
per cpu structure svm_cpu_data not being de-allocated for all cpus.

Signed-off-by: Jacob Xu <jacobhxu@google.com>
---
 arch/x86/kvm/svm/svm.c | 4 ++--
 1 file changed, 2 insertions(+), 2 deletions(-)

```
#### [PATCH] KVM: x86: reinstate vendor-agnostic check on SPEC_CTRL cpuid bits
##### From: Paolo Bonzini <pbonzini@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Paolo Bonzini <pbonzini@redhat.com>
X-Patchwork-Id: 11948971
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-17.2 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_CR_TRAILER,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,
	URIBL_BLOCKED autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id E65D2C4361B
	for <kvm@archiver.kernel.org>; Thu,  3 Dec 2020 15:17:05 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 92AA2206D8
	for <kvm@archiver.kernel.org>; Thu,  3 Dec 2020 15:17:03 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728830AbgLCPQr (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Thu, 3 Dec 2020 10:16:47 -0500
Received: from us-smtp-delivery-124.mimecast.com ([63.128.21.124]:42678 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1726202AbgLCPQr (ORCPT
        <rfc822;kvm@vger.kernel.org>); Thu, 3 Dec 2020 10:16:47 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1607008520;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=DyM6M0CaXHuUyJ1W1c9GKjJJgZPBG5nzEO24r4+1bEU=;
        b=i7KFhesaXxLnBsgiysKBEpCLWC4f4HWO0YCyKF3LoYO4SZOiCNVBRdnHtyZhainRd32tMz
        eW9BtqFvC79j53mGCVfuT1siolP9YpMzozAUa3UFhNtcCxbr0TOKjCsuJ0IWxMmCX0eHRf
        xYd4A8wn696etgF9zmPKtIb5QRpfctM=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-56-iio3t5tINAOA8sJd5cCiLQ-1; Thu, 03 Dec 2020 10:15:18 -0500
X-MC-Unique: iio3t5tINAOA8sJd5cCiLQ-1
Received: from smtp.corp.redhat.com (int-mx08.intmail.prod.int.phx2.redhat.com
 [10.5.11.23])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 77E96800D62;
        Thu,  3 Dec 2020 15:15:17 +0000 (UTC)
Received: from virtlab701.virt.lab.eng.bos.redhat.com
 (virtlab701.virt.lab.eng.bos.redhat.com [10.19.152.228])
        by smtp.corp.redhat.com (Postfix) with ESMTP id DDB0E1F075;
        Thu,  3 Dec 2020 15:15:16 +0000 (UTC)
From: Paolo Bonzini <pbonzini@redhat.com>
To: linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Cc: stable@vger.kernel.org, "Denis V . Lunev" <den@openvz.org>
Subject: [PATCH] KVM: x86: reinstate vendor-agnostic check on SPEC_CTRL cpuid
 bits
Date: Thu,  3 Dec 2020 10:15:16 -0500
Message-Id: <20201203151516.14441-1-pbonzini@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.84 on 10.5.11.23
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Until commit e7c587da1252 ("x86/speculation: Use synthetic bits for IBRS/IBPB/STIBP",
2018-05-17), KVM was testing both Intel and AMD CPUID bits before allowing the
guest to write MSR_IA32_SPEC_CTRL and MSR_IA32_PRED_CMD.  Testing only Intel bits
on VMX processors, or only AMD bits on SVM processors, fails if the guests are
created with the "opposite" vendor as the host.

While at it, also tweak the host CPU check to use the vendor-agnostic feature bit
X86_FEATURE_IBPB, since we only care about the availability of the MSR on the host
here and not about specific CPUID bits.

Fixes: e7c587da1252 ("x86/speculation: Use synthetic bits for IBRS/IBPB/STIBP")
Cc: stable@vger.kernel.org
Reported-by: Denis V. Lunev <den@openvz.org>
Signed-off-by: Paolo Bonzini <pbonzini@redhat.com>
---
 arch/x86/kvm/svm/svm.c |  3 ++-
 arch/x86/kvm/vmx/vmx.c | 10 +++++++---
 2 files changed, 9 insertions(+), 4 deletions(-)

```
#### [PATCH v2 1/3] KVM: x86: implement KVM_{GET|SET}_TSC_STATE
##### From: Maxim Levitsky <mlevitsk@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Maxim Levitsky <mlevitsk@redhat.com>
X-Patchwork-Id: 11949165
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-17.2 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_CR_TRAILER,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS
	autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id A2A70C18E57
	for <kvm@archiver.kernel.org>; Thu,  3 Dec 2020 17:13:56 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 5B851206B6
	for <kvm@archiver.kernel.org>; Thu,  3 Dec 2020 17:13:56 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1731466AbgLCRNf (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Thu, 3 Dec 2020 12:13:35 -0500
Received: from us-smtp-delivery-124.mimecast.com ([216.205.24.124]:54263 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1731441AbgLCRNe (ORCPT
        <rfc822;kvm@vger.kernel.org>); Thu, 3 Dec 2020 12:13:34 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1607015526;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding:
         in-reply-to:in-reply-to:references:references;
        bh=Jmr/JFRgIc7BBDuWcf7Mzpm7NP0GuJrUZZKAzRa6tmY=;
        b=G0F1s4wcb5fnTWozB9SPKGFcVAD/C1jtRJ5IK9ZA07WA7wFHt35VG4rjz0z9G+LjKTo/9h
        e0AMtpWuMbqw+QA1J+bQEkZL9ha28pR3Dflm21kG0OYE3dDHOb6vmgMuD0hZObYzf/BsQi
        DVt/ChiqMerkBgTNzir/cCfVZuwPhuI=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-345-z18ZtV5cMmaOU8BVu94eGQ-1; Thu, 03 Dec 2020 12:12:02 -0500
X-MC-Unique: z18ZtV5cMmaOU8BVu94eGQ-1
Received: from smtp.corp.redhat.com (int-mx03.intmail.prod.int.phx2.redhat.com
 [10.5.11.13])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id E174E1016CB2;
        Thu,  3 Dec 2020 17:11:34 +0000 (UTC)
Received: from localhost.localdomain (unknown [10.35.206.228])
        by smtp.corp.redhat.com (Postfix) with ESMTP id E0E1560854;
        Thu,  3 Dec 2020 17:11:27 +0000 (UTC)
From: Maxim Levitsky <mlevitsk@redhat.com>
To: kvm@vger.kernel.org
Cc: "H. Peter Anvin" <hpa@zytor.com>,
        Paolo Bonzini <pbonzini@redhat.com>,
        Jonathan Corbet <corbet@lwn.net>,
        Jim Mattson <jmattson@google.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        linux-kselftest@vger.kernel.org (open list:KERNEL SELFTEST FRAMEWORK),
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Marcelo Tosatti <mtosatti@redhat.com>,
        Thomas Gleixner <tglx@linutronix.de>,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        linux-kernel@vger.kernel.org (open list),
        Ingo Molnar <mingo@redhat.com>,
        x86@kernel.org (maintainer:X86 ARCHITECTURE (32-BIT AND 64-BIT)),
        Joerg Roedel <joro@8bytes.org>, Borislav Petkov <bp@alien8.de>,
        Shuah Khan <shuah@kernel.org>,
        Maxim Levitsky <mlevitsk@redhat.com>,
        Andrew Jones <drjones@redhat.com>,
        Oliver Upton <oupton@google.com>,
        linux-doc@vger.kernel.org (open list:DOCUMENTATION)
Subject: [PATCH v2 1/3] KVM: x86: implement KVM_{GET|SET}_TSC_STATE
Date: Thu,  3 Dec 2020 19:11:16 +0200
Message-Id: <20201203171118.372391-2-mlevitsk@redhat.com>
In-Reply-To: <20201203171118.372391-1-mlevitsk@redhat.com>
References: <20201203171118.372391-1-mlevitsk@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.13
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

These two new ioctls allow to more precisly capture and
restore guest's TSC state.

Both ioctls are meant to be used to accurately migrate guest TSC
even when there is a significant downtime during the migration.

Suggested-by: Paolo Bonzini <pbonzini@redhat.com>
Signed-off-by: Maxim Levitsky <mlevitsk@redhat.com>
---
 Documentation/virt/kvm/api.rst | 65 ++++++++++++++++++++++++++++++
 arch/x86/kvm/x86.c             | 73 ++++++++++++++++++++++++++++++++++
 include/uapi/linux/kvm.h       | 15 +++++++
 3 files changed, 153 insertions(+)

```
#### [PATCH v2 1/2] Update the kernel headers for 5.10-rc5 + TSC
##### From: Maxim Levitsky <mlevitsk@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Maxim Levitsky <mlevitsk@redhat.com>
X-Patchwork-Id: 11949185
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-17.2 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_CR_TRAILER,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS
	autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id DEEC9C4361A
	for <kvm@archiver.kernel.org>; Thu,  3 Dec 2020 17:17:42 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 8DCE8207B0
	for <kvm@archiver.kernel.org>; Thu,  3 Dec 2020 17:17:42 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1731533AbgLCRR2 (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Thu, 3 Dec 2020 12:17:28 -0500
Received: from us-smtp-delivery-124.mimecast.com ([216.205.24.124]:46860 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1726840AbgLCRR2 (ORCPT
        <rfc822;kvm@vger.kernel.org>); Thu, 3 Dec 2020 12:17:28 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1607015761;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding:
         in-reply-to:in-reply-to:references:references;
        bh=grc6F8c3fmP/azS2NlheMCW0ADUX5FyBaSdYDLtMfXY=;
        b=FRRZQntRNMz/bx4XXOEpagyIY28jUO0DjoOiZZaI2h+cl77TtcaMjDgq4kM1NxyCgoPIRz
        /ik2BCj6J0AfTe5xPFR/cl+biqFWNOVzVOGUbitfergp8Kr50yfw0fl+q/LVmUfiBgWBdJ
        513hCs2miSdxebU+H8KHi3ZuK/8AlKA=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-223-1LLL5z8jPvKDKrBUYSZPPQ-1; Thu, 03 Dec 2020 12:15:59 -0500
X-MC-Unique: 1LLL5z8jPvKDKrBUYSZPPQ-1
Received: from smtp.corp.redhat.com (int-mx05.intmail.prod.int.phx2.redhat.com
 [10.5.11.15])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 7CCBD858183;
        Thu,  3 Dec 2020 17:15:58 +0000 (UTC)
Received: from localhost.localdomain (unknown [10.35.206.228])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 2D7025D6AC;
        Thu,  3 Dec 2020 17:15:54 +0000 (UTC)
From: Maxim Levitsky <mlevitsk@redhat.com>
To: qemu-devel@nongnu.org
Cc: Paolo Bonzini <pbonzini@redhat.com>,
        "Michael S. Tsirkin" <mst@redhat.com>,
        Marcelo Tosatti <mtosatti@redhat.com>,
        Eduardo Habkost <ehabkost@redhat.com>, kvm@vger.kernel.org,
        Richard Henderson <richard.henderson@linaro.org>,
        Cornelia Huck <cohuck@redhat.com>,
        Maxim Levitsky <mlevitsk@redhat.com>
Subject: [PATCH v2 1/2] Update the kernel headers for 5.10-rc5 + TSC
Date: Thu,  3 Dec 2020 19:15:45 +0200
Message-Id: <20201203171546.372686-2-mlevitsk@redhat.com>
In-Reply-To: <20201203171546.372686-1-mlevitsk@redhat.com>
References: <20201203171546.372686-1-mlevitsk@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.15
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Signed-off-by: Maxim Levitsky <mlevitsk@redhat.com>
---
 include/standard-headers/asm-x86/kvm_para.h |  1 +
 linux-headers/asm-x86/kvm.h                 |  2 +
 linux-headers/linux/kvm.h                   | 71 ++++++++++++++++++++-
 3 files changed, 73 insertions(+), 1 deletion(-)

```
#### [PATCH v3] self_tests/kvm: sync_regs test for diag318
##### From: Collin Walling <walling@linux.ibm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Collin Walling <walling@linux.ibm.com>
X-Patchwork-Id: 11949723
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.8 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT
	autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id ED3D0C433FE
	for <kvm@archiver.kernel.org>; Thu,  3 Dec 2020 21:54:33 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 9337122285
	for <kvm@archiver.kernel.org>; Thu,  3 Dec 2020 21:54:33 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1731561AbgLCVyS (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Thu, 3 Dec 2020 16:54:18 -0500
Received: from mx0a-001b2d01.pphosted.com ([148.163.156.1]:36990 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1727700AbgLCVyR (ORCPT
        <rfc822;kvm@vger.kernel.org>); Thu, 3 Dec 2020 16:54:17 -0500
Received: from pps.filterd (m0098394.ppops.net [127.0.0.1])
        by mx0a-001b2d01.pphosted.com (8.16.0.42/8.16.0.42) with SMTP id
 0B3Lnt5I019408;
        Thu, 3 Dec 2020 16:53:35 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=ibm.com;
 h=from : to : cc : subject
 : date : message-id : mime-version : content-transfer-encoding; s=pp1;
 bh=3Hd9j3hFs4weXwaG88xkWKV9KCVXZBnMUzv9qdVBMG4=;
 b=PcCiftvyinC7NuW4C1SWmJLZHICZW81De+go9K5CuceShK5+ma2DON0FSktgFZSsTqFn
 owvw8rWls7SMvcZx/Tsb+BXKDtbtoRbARQp9fzYJFlqWmdKp228GXTDDMQ9HTWGQ7USL
 fdAIEbaP8zRJQcm206RqzZhogefc2Eozw5W60JLGmo7ZBI6FzN7ae9SekpMOzeWk4eiF
 UzNjc0SuELkTwGiil4M1V0evUxYTcycaOjvJGNvYiXxx4cTIefi6AADGUHx2+LHpNW40
 9tMkb0cUeHcIOuTXo3zLuCw3aa0vzfnSCC3LalEhgeFsLiD6IS7wNbb4IzCcr9K0jCvN pg==
Received: from pps.reinject (localhost [127.0.0.1])
        by mx0a-001b2d01.pphosted.com with ESMTP id 357897g273-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Thu, 03 Dec 2020 16:53:34 -0500
Received: from m0098394.ppops.net (m0098394.ppops.net [127.0.0.1])
        by pps.reinject (8.16.0.36/8.16.0.36) with SMTP id 0B3LoLAe022335;
        Thu, 3 Dec 2020 16:53:34 -0500
Received: from ppma01wdc.us.ibm.com (fd.55.37a9.ip4.static.sl-reverse.com
 [169.55.85.253])
        by mx0a-001b2d01.pphosted.com with ESMTP id 357897g26s-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Thu, 03 Dec 2020 16:53:34 -0500
Received: from pps.filterd (ppma01wdc.us.ibm.com [127.0.0.1])
        by ppma01wdc.us.ibm.com (8.16.0.42/8.16.0.42) with SMTP id
 0B3LVsh9011671;
        Thu, 3 Dec 2020 21:53:33 GMT
Received: from b03cxnp08026.gho.boulder.ibm.com
 (b03cxnp08026.gho.boulder.ibm.com [9.17.130.18])
        by ppma01wdc.us.ibm.com with ESMTP id 355vrg4pe2-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Thu, 03 Dec 2020 21:53:33 +0000
Received: from b03ledav005.gho.boulder.ibm.com
 (b03ledav005.gho.boulder.ibm.com [9.17.130.236])
        by b03cxnp08026.gho.boulder.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id 0B3LqFMJ18940400
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Thu, 3 Dec 2020 21:52:15 GMT
Received: from b03ledav005.gho.boulder.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 7194BBE058;
        Thu,  3 Dec 2020 21:52:15 +0000 (GMT)
Received: from b03ledav005.gho.boulder.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 96E32BE053;
        Thu,  3 Dec 2020 21:52:14 +0000 (GMT)
Received: from localhost.localdomain.com (unknown [9.85.190.183])
        by b03ledav005.gho.boulder.ibm.com (Postfix) with ESMTP;
        Thu,  3 Dec 2020 21:52:14 +0000 (GMT)
From: Collin Walling <walling@linux.ibm.com>
To: kvm@vger.kernel.org, linux-kselftest@vger.kernel.org
Cc: frankja@linux.ibm.com, david@redhat.com, thuth@redhat.com,
        cohuck@redhat.com, borntraeger@de.ibm.com, pbonzini@redhat.com,
        imbrenda@linux.ibm.com
Subject: [PATCH v3] self_tests/kvm: sync_regs test for diag318
Date: Thu,  3 Dec 2020 16:52:12 -0500
Message-Id: <20201203215212.243145-1-walling@linux.ibm.com>
X-Mailer: git-send-email 2.26.2
MIME-Version: 1.0
X-TM-AS-GCONF: 00
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.312,18.0.737
 definitions=2020-12-03_12:2020-12-03,2020-12-03 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 mlxscore=0 lowpriorityscore=0
 suspectscore=25 bulkscore=0 impostorscore=0 spamscore=0 clxscore=1011
 phishscore=0 adultscore=0 mlxlogscore=999 malwarescore=0
 priorityscore=1501 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.12.0-2009150000 definitions=main-2012030124
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The DIAGNOSE 0x0318 instruction, unique to s390x, is a privileged call
that must be intercepted via SIE, handled in userspace, and the
information set by the instruction is communicated back to KVM.

To test the instruction interception, an ad-hoc handler is defined which
simply has a VM execute the instruction and then userspace will extract
the necessary info. The handler is defined such that the instruction
invocation occurs only once. It is up to the caller to determine how the
info returned by this handler should be used.

The diag318 info is communicated from userspace to KVM via a sync_regs
call. This is tested during a sync_regs test, where the diag318 info is
requested via the handler, then the info is stored in the appropriate
register in KVM via a sync registers call.

If KVM does not support diag318, then the tests will print a message
stating that diag318 was skipped, and the asserts will simply test
against a value of 0.

Signed-off-by: Collin Walling <walling@linux.ibm.com>
---

v3 changes: no longer testing the reset code, as it is handled
entirely via userspace. The respective reset tests have been removed

---
 tools/testing/selftests/kvm/Makefile          |  2 +-
 .../kvm/include/s390x/diag318_test_handler.h  | 13 +++
 .../kvm/lib/s390x/diag318_test_handler.c      | 82 +++++++++++++++++++
 tools/testing/selftests/kvm/s390x/resets.c    |  1 +
 .../selftests/kvm/s390x/sync_regs_test.c      | 16 +++-
 5 files changed, 112 insertions(+), 2 deletions(-)
 create mode 100644 tools/testing/selftests/kvm/include/s390x/diag318_test_handler.h
 create mode 100644 tools/testing/selftests/kvm/lib/s390x/diag318_test_handler.c

```
