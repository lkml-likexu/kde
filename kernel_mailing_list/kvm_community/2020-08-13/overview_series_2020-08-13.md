#### [RFC 1/4] arm64: add a helper function to traverse arm64_ftr_regs
##### From: Peng Liang <liangpeng10@huawei.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Peng Liang <liangpeng10@huawei.com>
X-Patchwork-Id: 11711697
Return-Path: <SRS0=IfgN=BX=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 8AEDD16B1
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 13 Aug 2020 06:14:24 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 720CA20656
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 13 Aug 2020 06:14:24 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726486AbgHMGOV (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 13 Aug 2020 02:14:21 -0400
Received: from szxga07-in.huawei.com ([45.249.212.35]:34836 "EHLO huawei.com"
        rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org with ESMTP
        id S1726224AbgHMGOV (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 13 Aug 2020 02:14:21 -0400
Received: from DGGEMS401-HUB.china.huawei.com (unknown [172.30.72.60])
        by Forcepoint Email with ESMTP id 55FC52C6ECCEE54F846D;
        Thu, 13 Aug 2020 14:14:14 +0800 (CST)
Received: from localhost.localdomain (10.175.104.175) by
 DGGEMS401-HUB.china.huawei.com (10.3.19.201) with Microsoft SMTP Server id
 14.3.487.0; Thu, 13 Aug 2020 14:14:03 +0800
From: Peng Liang <liangpeng10@huawei.com>
To: <kvmarm@lists.cs.columbia.edu>
CC: <kvm@vger.kernel.org>, <maz@kernel.org>, <will@kernel.org>,
        <zhang.zhanghailiang@huawei.com>, <xiexiangyou@huawei.com>,
        Peng Liang <liangpeng10@huawei.com>
Subject: [RFC 1/4] arm64: add a helper function to traverse arm64_ftr_regs
Date: Thu, 13 Aug 2020 14:05:14 +0800
Message-ID: <20200813060517.2360048-2-liangpeng10@huawei.com>
X-Mailer: git-send-email 2.18.4
In-Reply-To: <20200813060517.2360048-1-liangpeng10@huawei.com>
References: <20200813060517.2360048-1-liangpeng10@huawei.com>
MIME-Version: 1.0
X-Originating-IP: [10.175.104.175]
X-CFilter-Loop: Reflected
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

If we want to emulate ID registers, we need to initialize ID registers
firstly.  This commit is to add a helper function to traverse
arm64_ftr_regs so that we can initialize ID registers from
arm64_ftr_regs.

Signed-off-by: zhanghailiang <zhang.zhanghailiang@huawei.com>
Signed-off-by: Peng Liang <liangpeng10@huawei.com>
---
 arch/arm64/include/asm/cpufeature.h |  2 ++
 arch/arm64/kernel/cpufeature.c      | 13 +++++++++++++
 2 files changed, 15 insertions(+)

```
#### [PATCH v3] PCI: Introduce flag for detached virtual functions
##### From: Matthew Rosato <mjrosato@linux.ibm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Matthew Rosato <mjrosato@linux.ibm.com>
X-Patchwork-Id: 11712625
Return-Path: <SRS0=IfgN=BX=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id E414E722
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 13 Aug 2020 15:41:10 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id B95A620866
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 13 Aug 2020 15:41:10 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=ibm.com header.i=@ibm.com
 header.b="BeTf1pHX"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726749AbgHMPk6 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 13 Aug 2020 11:40:58 -0400
Received: from mx0a-001b2d01.pphosted.com ([148.163.156.1]:21112 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1726305AbgHMPk5 (ORCPT
        <rfc822;kvm@vger.kernel.org>); Thu, 13 Aug 2020 11:40:57 -0400
Received: from pps.filterd (m0098409.ppops.net [127.0.0.1])
        by mx0a-001b2d01.pphosted.com (8.16.0.42/8.16.0.42) with SMTP id
 07DFXi4t001740;
        Thu, 13 Aug 2020 11:40:54 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=ibm.com;
 h=from : to : cc : subject
 : date : message-id : in-reply-to : references; s=pp1;
 bh=WCxdwJfJGY/qv0ic1bER7AHQz7Z11kSc/2Nrj4VfUNs=;
 b=BeTf1pHXn0fRIpibBqI6X/lmpRRU1vW2fZamvXeAxJiwMymGEspAsL6kZNYcXJJWO2Z3
 SkmBH76ZvMImS3l1/fcd857zkljGAkNynwAZocAbhal669NbR956hr8zLxD+bADI1tZR
 jOFAtvtpWPqG1/FWUpMJZ326XaxCjRhAwrfHQBUTWGxTAxK4K5JtJaMEMELB4t/eJhK3
 AgEibW4iKMwYbeYR5RWt4Axlkb2uScEQB3bQJKl7Hlwll1PWf4Rx6d2WsUs++L9nhkzc
 LMKkDCbehUQcMn5IUwwgci63zDt/OsgIf5RJijKLdO02OsuX+bsxEGm0RI8eVRuv7PGP Ug==
Received: from pps.reinject (localhost [127.0.0.1])
        by mx0a-001b2d01.pphosted.com with ESMTP id 32w5mwe6gg-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Thu, 13 Aug 2020 11:40:53 -0400
Received: from m0098409.ppops.net (m0098409.ppops.net [127.0.0.1])
        by pps.reinject (8.16.0.36/8.16.0.36) with SMTP id 07DFXxGF002968;
        Thu, 13 Aug 2020 11:40:53 -0400
Received: from ppma03dal.us.ibm.com (b.bd.3ea9.ip4.static.sl-reverse.com
 [169.62.189.11])
        by mx0a-001b2d01.pphosted.com with ESMTP id 32w5mwe6fg-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Thu, 13 Aug 2020 11:40:53 -0400
Received: from pps.filterd (ppma03dal.us.ibm.com [127.0.0.1])
        by ppma03dal.us.ibm.com (8.16.0.42/8.16.0.42) with SMTP id
 07DFLCHD002809;
        Thu, 13 Aug 2020 15:40:52 GMT
Received: from b01cxnp23032.gho.pok.ibm.com (b01cxnp23032.gho.pok.ibm.com
 [9.57.198.27])
        by ppma03dal.us.ibm.com with ESMTP id 32skp9nx39-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Thu, 13 Aug 2020 15:40:52 +0000
Received: from b01ledav005.gho.pok.ibm.com (b01ledav005.gho.pok.ibm.com
 [9.57.199.110])
        by b01cxnp23032.gho.pok.ibm.com (8.14.9/8.14.9/NCO v10.0) with ESMTP
 id 07DFepMH54657286
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Thu, 13 Aug 2020 15:40:51 GMT
Received: from b01ledav005.gho.pok.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 29087AE062;
        Thu, 13 Aug 2020 15:40:51 +0000 (GMT)
Received: from b01ledav005.gho.pok.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 6B47DAE05C;
        Thu, 13 Aug 2020 15:40:49 +0000 (GMT)
Received: from oc4221205838.ibm.com (unknown [9.163.7.238])
        by b01ledav005.gho.pok.ibm.com (Postfix) with ESMTP;
        Thu, 13 Aug 2020 15:40:49 +0000 (GMT)
From: Matthew Rosato <mjrosato@linux.ibm.com>
To: alex.williamson@redhat.com, bhelgaas@google.com
Cc: schnelle@linux.ibm.com, pmorel@linux.ibm.com, mpe@ellerman.id.au,
        oohall@gmail.com, linux-s390@vger.kernel.org,
        linux-kernel@vger.kernel.org, kvm@vger.kernel.org,
        linux-pci@vger.kernel.org
Subject: [PATCH v3] PCI: Introduce flag for detached virtual functions
Date: Thu, 13 Aug 2020 11:40:43 -0400
Message-Id: <1597333243-29483-2-git-send-email-mjrosato@linux.ibm.com>
X-Mailer: git-send-email 1.8.3.1
In-Reply-To: <1597333243-29483-1-git-send-email-mjrosato@linux.ibm.com>
References: <1597333243-29483-1-git-send-email-mjrosato@linux.ibm.com>
X-TM-AS-GCONF: 00
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.235,18.0.687
 definitions=2020-08-13_14:2020-08-13,2020-08-13 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 bulkscore=0 adultscore=0
 suspectscore=0 clxscore=1015 impostorscore=0 spamscore=0
 priorityscore=1501 mlxlogscore=999 mlxscore=0 lowpriorityscore=0
 phishscore=0 malwarescore=0 classifier=spam adjust=0 reason=mlx
 scancount=1 engine=8.12.0-2006250000 definitions=main-2008130116
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

s390x has the notion of providing VFs to the kernel in a manner
where the associated PF is inaccessible other than via firmware.
These are not treated as typical VFs and access to them is emulated
by underlying firmware which can still access the PF.  After
the referened commit however these detached VFs were no longer able
to work with vfio-pci as the firmware does not provide emulation of
the PCI_COMMAND_MEMORY bit.  In this case, let's explicitly recognize
these detached VFs so that vfio-pci can allow memory access to
them again.

Fixes: abafbc551fdd ("vfio-pci: Invalidate mmaps and block MMIO access on disabled memory")
Signed-off-by: Matthew Rosato <mjrosato@linux.ibm.com>
---
 arch/s390/pci/pci_bus.c            | 13 +++++++++++++
 drivers/vfio/pci/vfio_pci_config.c |  8 ++++----
 include/linux/pci.h                |  4 ++++
 3 files changed, 21 insertions(+), 4 deletions(-)

```
