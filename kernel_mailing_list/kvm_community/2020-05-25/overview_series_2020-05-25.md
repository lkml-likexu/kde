#### [PATCH v2 1/5] vhost: convert VHOST_VSOCK_SET_RUNNING to a generic ioctl
##### From: Guennadi Liakhovetski <guennadi.liakhovetski@linux.intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Guennadi Liakhovetski
 <guennadi.liakhovetski@linux.intel.com>
X-Patchwork-Id: 11568945
Return-Path: <SRS0=SRxi=7H=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 3A975912
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 25 May 2020 14:45:07 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 23DD92087D
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 25 May 2020 14:45:07 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2390992AbgEYOpG (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 25 May 2020 10:45:06 -0400
Received: from mga04.intel.com ([192.55.52.120]:34251 "EHLO mga04.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S2388687AbgEYOpF (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 25 May 2020 10:45:05 -0400
IronPort-SDR: 
 Bmo5vKki7nsXC8+8CfFruKuVs+SOW0nk9i2DtYF9+3p6W/MNCkD+Z7CIknsSt/AXsfwuFo1Yza
 QK5SA7vd7eEw==
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from orsmga003.jf.intel.com ([10.7.209.27])
  by fmsmga104.fm.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 25 May 2020 07:45:05 -0700
IronPort-SDR: 
 ZARH7TqTOXBIcr+UZK902lPAlXXpqow1iZGtYTLq/gULvQT3CpFEc0h4G1Cl9XllPA056+uEUx
 UDdP3ZSLQoXA==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.73,433,1583222400";
   d="scan'208";a="266165828"
Received: from gliakhov-mobl2.ger.corp.intel.com (HELO
 ubuntu.ger.corp.intel.com) ([10.249.41.109])
  by orsmga003.jf.intel.com with ESMTP; 25 May 2020 07:45:02 -0700
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
        Bjorn Andersson <bjorn.andersson@linaro.org>
Subject: [PATCH v2 1/5] vhost: convert VHOST_VSOCK_SET_RUNNING to a generic
 ioctl
Date: Mon, 25 May 2020 16:44:54 +0200
Message-Id: <20200525144458.8413-2-guennadi.liakhovetski@linux.intel.com>
X-Mailer: git-send-email 2.20.1
In-Reply-To: <20200525144458.8413-1-guennadi.liakhovetski@linux.intel.com>
References: <20200525144458.8413-1-guennadi.liakhovetski@linux.intel.com>
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
#### [PATCH v3 01/18] nitro_enclaves: Add ioctl interface definition
##### From: Andra Paraschiv <andraprs@amazon.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Andra Paraschiv <andraprs@amazon.com>
X-Patchwork-Id: 11569603
Return-Path: <SRS0=SRxi=7H=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 20BFB90
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 25 May 2020 22:14:08 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 02C582075F
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 25 May 2020 22:14:07 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=amazon.com header.i=@amazon.com
 header.b="DV/WS2SE"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1731235AbgEYWOF (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 25 May 2020 18:14:05 -0400
Received: from smtp-fw-4101.amazon.com ([72.21.198.25]:8233 "EHLO
        smtp-fw-4101.amazon.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1729589AbgEYWOE (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 25 May 2020 18:14:04 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
  d=amazon.com; i=@amazon.com; q=dns/txt; s=amazon201209;
  t=1590444842; x=1621980842;
  h=from:to:cc:subject:date:message-id:in-reply-to:
   references:mime-version:content-transfer-encoding;
  bh=J+W1uF/+pHzCPt7+R5eOTYXFdxlNyATSaaicqu0ygi4=;
  b=DV/WS2SEsl6SN7mojgkKHKccRJXPIQQYjY7shJa+vE+S+cX1aC53pA6K
   C91u0weH7SxRkcT8iLVXYqyR4K99jIyO1FMpmBccSc2WXGszsX6YIuJH6
   LsizebSBWExKRHFqKOJGcbEeKPKi5O+EvsxUelnwGNDFq+DlGIlIkErQc
   M=;
IronPort-SDR: 
 ufGBgo4KxIqswKpBp10OaHci71Oh2zVMMMtxLHse5CRqI8VsWAEmGO9NwwFAnlutgpp/CTWwuS
 1aWhJXJcC2Ag==
X-IronPort-AV: E=Sophos;i="5.73,435,1583193600";
   d="scan'208";a="32159712"
Received: from iad12-co-svc-p1-lb1-vlan3.amazon.com (HELO
 email-inbound-relay-1e-27fb8269.us-east-1.amazon.com) ([10.43.8.6])
  by smtp-border-fw-out-4101.iad4.amazon.com with ESMTP;
 25 May 2020 22:14:01 +0000
Received: from EX13MTAUEA002.ant.amazon.com
 (iad55-ws-svc-p15-lb9-vlan3.iad.amazon.com [10.40.159.166])
        by email-inbound-relay-1e-27fb8269.us-east-1.amazon.com (Postfix) with
 ESMTPS id 33E3CA1B68;
        Mon, 25 May 2020 22:14:00 +0000 (UTC)
Received: from EX13D16EUB003.ant.amazon.com (10.43.166.99) by
 EX13MTAUEA002.ant.amazon.com (10.43.61.77) with Microsoft SMTP Server (TLS)
 id 15.0.1497.2; Mon, 25 May 2020 22:13:59 +0000
Received: from 38f9d34ed3b1.ant.amazon.com (10.43.160.90) by
 EX13D16EUB003.ant.amazon.com (10.43.166.99) with Microsoft SMTP Server (TLS)
 id 15.0.1497.2; Mon, 25 May 2020 22:13:49 +0000
From: Andra Paraschiv <andraprs@amazon.com>
To: <linux-kernel@vger.kernel.org>
CC: Anthony Liguori <aliguori@amazon.com>,
        Benjamin Herrenschmidt <benh@kernel.crashing.org>,
        Colm MacCarthaigh <colmmacc@amazon.com>,
        "Bjoern Doebel" <doebel@amazon.de>,
        David Woodhouse <dwmw@amazon.co.uk>,
        "Frank van der Linden" <fllinden@amazon.com>,
        Alexander Graf <graf@amazon.de>,
        "Martin Pohlack" <mpohlack@amazon.de>,
        Matt Wilson <msw@amazon.com>,
        Paolo Bonzini <pbonzini@redhat.com>,
        Balbir Singh <sblbir@amazon.com>,
        Stefano Garzarella <sgarzare@redhat.com>,
        Stefan Hajnoczi <stefanha@redhat.com>,
        Stewart Smith <trawets@amazon.com>,
        Uwe Dannowski <uwed@amazon.de>, <kvm@vger.kernel.org>,
        <ne-devel-upstream@amazon.com>,
        Andra Paraschiv <andraprs@amazon.com>
Subject: [PATCH v3 01/18] nitro_enclaves: Add ioctl interface definition
Date: Tue, 26 May 2020 01:13:17 +0300
Message-ID: <20200525221334.62966-2-andraprs@amazon.com>
X-Mailer: git-send-email 2.20.1 (Apple Git-117)
In-Reply-To: <20200525221334.62966-1-andraprs@amazon.com>
References: <20200525221334.62966-1-andraprs@amazon.com>
MIME-Version: 1.0
X-Originating-IP: [10.43.160.90]
X-ClientProxiedBy: EX13D12UWC004.ant.amazon.com (10.43.162.182) To
 EX13D16EUB003.ant.amazon.com (10.43.166.99)
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The Nitro Enclaves driver handles the enclave lifetime management. This
includes enclave creation, termination and setting up its resources such
as memory and CPU.

An enclave runs alongside the VM that spawned it. It is abstracted as a
process running in the VM that launched it. The process interacts with
the NE driver, that exposes an ioctl interface for creating an enclave
and setting up its resources.

Include part of the KVM ioctls in the provided ioctl interface, with
additional NE ioctl commands that e.g. triggers the enclave run.

Signed-off-by: Alexandru Vasile <lexnv@amazon.com>
Signed-off-by: Andra Paraschiv <andraprs@amazon.com>
---
Changelog

v2 -> v3

* Remove the GPL additional wording as SPDX-License-Identifier is already in
place.

v1 -> v2

* Add ioctl for getting enclave image load metadata.
* Update NE_ENCLAVE_START ioctl name to NE_START_ENCLAVE. 
* Add entry in Documentation/userspace-api/ioctl/ioctl-number.rst for NE ioctls.
* Update NE ioctls definition based on the updated ioctl range for major and
minor.
---
 .../userspace-api/ioctl/ioctl-number.rst      |  5 +-
 include/linux/nitro_enclaves.h                | 11 ++++
 include/uapi/linux/nitro_enclaves.h           | 65 +++++++++++++++++++
 3 files changed, 80 insertions(+), 1 deletion(-)
 create mode 100644 include/linux/nitro_enclaves.h
 create mode 100644 include/uapi/linux/nitro_enclaves.h

```
#### [RFC PATCH 1/7] KVM: arm64: Add some basic functions for hw DBM
##### From: Keqian Zhu <zhukeqian1@huawei.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Keqian Zhu <zhukeqian1@huawei.com>
X-Patchwork-Id: 11568605
Return-Path: <SRS0=SRxi=7H=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 0887A1392
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 25 May 2020 11:26:02 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id E463A20787
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 25 May 2020 11:26:01 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2390160AbgEYLZM (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 25 May 2020 07:25:12 -0400
Received: from szxga06-in.huawei.com ([45.249.212.32]:36940 "EHLO huawei.com"
        rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org with ESMTP
        id S2389897AbgEYLZL (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 25 May 2020 07:25:11 -0400
Received: from DGGEMS401-HUB.china.huawei.com (unknown [172.30.72.58])
        by Forcepoint Email with ESMTP id 6B0142A7762008D953ED;
        Mon, 25 May 2020 19:25:09 +0800 (CST)
Received: from DESKTOP-5IS4806.china.huawei.com (10.173.221.230) by
 DGGEMS401-HUB.china.huawei.com (10.3.19.201) with Microsoft SMTP Server id
 14.3.487.0; Mon, 25 May 2020 19:25:02 +0800
From: Keqian Zhu <zhukeqian1@huawei.com>
To: <linux-kernel@vger.kernel.org>,
        <linux-arm-kernel@lists.infradead.org>,
        <kvmarm@lists.cs.columbia.edu>, <kvm@vger.kernel.org>
CC: Catalin Marinas <catalin.marinas@arm.com>,
        Marc Zyngier <maz@kernel.org>,
        James Morse <james.morse@arm.com>,
        Will Deacon <will@kernel.org>,
        "Suzuki K Poulose" <suzuki.poulose@arm.com>,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        Julien Thierry <julien.thierry.kdev@gmail.com>,
        Mark Brown <broonie@kernel.org>,
        "Thomas Gleixner" <tglx@linutronix.de>,
        Andrew Morton <akpm@linux-foundation.org>,
        Alexios Zavras <alexios.zavras@intel.com>,
        <wanghaibin.wang@huawei.com>, <zhengxiang9@huawei.com>,
        Keqian Zhu <zhukeqian1@huawei.com>,
        Peng Liang <liangpeng10@huawei.com>
Subject: [RFC PATCH 1/7] KVM: arm64: Add some basic functions for hw DBM
Date: Mon, 25 May 2020 19:24:00 +0800
Message-ID: <20200525112406.28224-2-zhukeqian1@huawei.com>
X-Mailer: git-send-email 2.8.4.windows.1
In-Reply-To: <20200525112406.28224-1-zhukeqian1@huawei.com>
References: <20200525112406.28224-1-zhukeqian1@huawei.com>
MIME-Version: 1.0
X-Originating-IP: [10.173.221.230]
X-CFilter-Loop: Reflected
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Prepare some basic functions used by following patches to support
hardware DBM.

Signed-off-by: Keqian Zhu <zhukeqian1@huawei.com>
Signed-off-by: Peng Liang <liangpeng10@huawei.com>
---
 arch/arm64/include/asm/kvm_mmu.h | 24 ++++++++++++++++++++++++
 1 file changed, 24 insertions(+)

```
#### [kvm-unit-tests PATCH] s390x: stsi: Make output tap13 compatible
##### From: Janosch Frank <frankja@linux.ibm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Janosch Frank <frankja@linux.ibm.com>
X-Patchwork-Id: 11568283
Return-Path: <SRS0=SRxi=7H=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 44BAD90
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 25 May 2020 08:43:55 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 37BAB2071A
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 25 May 2020 08:43:55 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2388465AbgEYIny (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 25 May 2020 04:43:54 -0400
Received: from mx0a-001b2d01.pphosted.com ([148.163.156.1]:21718 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S2388367AbgEYInx (ORCPT
        <rfc822;kvm@vger.kernel.org>); Mon, 25 May 2020 04:43:53 -0400
Received: from pps.filterd (m0187473.ppops.net [127.0.0.1])
        by mx0a-001b2d01.pphosted.com (8.16.0.42/8.16.0.42) with SMTP id
 04P8Wpus027649;
        Mon, 25 May 2020 04:43:53 -0400
Received: from pps.reinject (localhost [127.0.0.1])
        by mx0a-001b2d01.pphosted.com with ESMTP id 316yga5ck5-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Mon, 25 May 2020 04:43:52 -0400
Received: from m0187473.ppops.net (m0187473.ppops.net [127.0.0.1])
        by pps.reinject (8.16.0.36/8.16.0.36) with SMTP id 04P8X3IR028139;
        Mon, 25 May 2020 04:43:52 -0400
Received: from ppma04ams.nl.ibm.com (63.31.33a9.ip4.static.sl-reverse.com
 [169.51.49.99])
        by mx0a-001b2d01.pphosted.com with ESMTP id 316yga5cj0-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Mon, 25 May 2020 04:43:52 -0400
Received: from pps.filterd (ppma04ams.nl.ibm.com [127.0.0.1])
        by ppma04ams.nl.ibm.com (8.16.0.42/8.16.0.42) with SMTP id
 04P8bJpC016007;
        Mon, 25 May 2020 08:43:49 GMT
Received: from b06cxnps4074.portsmouth.uk.ibm.com
 (d06relay11.portsmouth.uk.ibm.com [9.149.109.196])
        by ppma04ams.nl.ibm.com with ESMTP id 316uf8uqtx-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Mon, 25 May 2020 08:43:49 +0000
Received: from d06av24.portsmouth.uk.ibm.com (d06av24.portsmouth.uk.ibm.com
 [9.149.105.60])
        by b06cxnps4074.portsmouth.uk.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id 04P8hlkO47644708
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Mon, 25 May 2020 08:43:47 GMT
Received: from d06av24.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 2B79B42042;
        Mon, 25 May 2020 08:43:47 +0000 (GMT)
Received: from d06av24.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id D65794203F;
        Mon, 25 May 2020 08:43:46 +0000 (GMT)
Received: from m46lp67.lnxne.boe (unknown [9.152.108.100])
        by d06av24.portsmouth.uk.ibm.com (Postfix) with ESMTP;
        Mon, 25 May 2020 08:43:46 +0000 (GMT)
From: Janosch Frank <frankja@linux.ibm.com>
To: kvm@vger.kernel.org
Cc: linux-s390@vger.kernel.org, thuth@redhat.com, stzi@linux.ibm.com,
        mhartmay@linux.ibm.com, david@redhat.com, cohuck@redhat.com
Subject: [kvm-unit-tests PATCH] s390x: stsi: Make output tap13 compatible
Date: Mon, 25 May 2020 10:43:40 +0200
Message-Id: <20200525084340.1454-1-frankja@linux.ibm.com>
X-Mailer: git-send-email 2.25.1
MIME-Version: 1.0
X-TM-AS-GCONF: 00
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.216,18.0.676
 definitions=2020-05-25_02:2020-05-22,2020-05-25 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 phishscore=0 impostorscore=0
 cotscore=-2147483648 spamscore=0 lowpriorityscore=0 suspectscore=1
 bulkscore=0 mlxlogscore=911 mlxscore=0 clxscore=1011 malwarescore=0
 adultscore=0 priorityscore=1501 classifier=spam adjust=0 reason=mlx
 scancount=1 engine=8.12.0-2004280000 definitions=main-2005250068
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

In tap13 output # is a special character and only "skip" and "todo"
are allowed to come after it. Let's appease our CI environment and
replace # with "count".

Signed-off-by: Janosch Frank <frankja@linux.ibm.com>
Reviewed-by: Thomas Huth <thuth@redhat.com>
Reviewed-by: David Hildenbrand <david@redhat.com>
Reviewed-by: Cornelia Huck <cohuck@redhat.com>
---
 s390x/stsi.c | 6 +++---
 1 file changed, 3 insertions(+), 3 deletions(-)

```
#### [PATCH v2 01/10] Revert "KVM: async_pf: Fix #DF due to inject "Page not Present" and "Page Ready" exceptions simultaneously"
##### From: Vitaly Kuznetsov <vkuznets@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Vitaly Kuznetsov <vkuznets@redhat.com>
X-Patchwork-Id: 11568917
Return-Path: <SRS0=SRxi=7H=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id AEE54912
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 25 May 2020 14:41:44 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 96734208C7
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 25 May 2020 14:41:44 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="LaQIIE6m"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2403943AbgEYOlm (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 25 May 2020 10:41:42 -0400
Received: from us-smtp-delivery-1.mimecast.com ([207.211.31.120]:44833 "EHLO
        us-smtp-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org
        with ESMTP id S2390896AbgEYOll (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 25 May 2020 10:41:41 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1590417699;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding:
         in-reply-to:in-reply-to:references:references;
        bh=0tW/ADyX9zwrjBKIKvd0UbIE8BCH3HnzV4Z5WBcx4X0=;
        b=LaQIIE6mtmy+/3ACBFnWKSTeSSqf13RtMyRGxwa1AS/f1S/Xg6Bj19lRpbvNpTvebQsuQ4
        HEUFAFzlr2dfAwkXwU/PFNQjYVGuDKQvMRGfiwUUwjUhBiT2ky3D/kBL408a3YGDFjl3xW
        xlHWynHJqZdX6VFyBCHvAHhVxKtxYXI=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-483-nIPtE7cxPyiXF7F5II2QMw-1; Mon, 25 May 2020 10:41:35 -0400
X-MC-Unique: nIPtE7cxPyiXF7F5II2QMw-1
Received: from smtp.corp.redhat.com (int-mx04.intmail.prod.int.phx2.redhat.com
 [10.5.11.14])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 2F3C31005510;
        Mon, 25 May 2020 14:41:33 +0000 (UTC)
Received: from vitty.brq.redhat.com (unknown [10.40.194.114])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 2E6645D9C5;
        Mon, 25 May 2020 14:41:30 +0000 (UTC)
From: Vitaly Kuznetsov <vkuznets@redhat.com>
To: kvm@vger.kernel.org, x86@kernel.org
Cc: Paolo Bonzini <pbonzini@redhat.com>,
        Andy Lutomirski <luto@kernel.org>,
        Thomas Gleixner <tglx@linutronix.de>,
        Borislav Petkov <bp@alien8.de>,
        "H. Peter Anvin" <hpa@zytor.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        Jim Mattson <jmattson@google.com>,
        Vivek Goyal <vgoyal@redhat.com>, Gavin Shan <gshan@redhat.com>,
        Peter Zijlstra <peterz@infradead.org>,
        linux-kernel@vger.kernel.org
Subject: [PATCH v2 01/10] Revert "KVM: async_pf: Fix #DF due to inject "Page
 not Present" and "Page Ready" exceptions simultaneously"
Date: Mon, 25 May 2020 16:41:16 +0200
Message-Id: <20200525144125.143875-2-vkuznets@redhat.com>
In-Reply-To: <20200525144125.143875-1-vkuznets@redhat.com>
References: <20200525144125.143875-1-vkuznets@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.14
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Commit 9a6e7c39810e (""KVM: async_pf: Fix #DF due to inject "Page not
Present" and "Page Ready" exceptions simultaneously") added a protection
against 'page ready' notification coming before 'page not present' is
delivered. This situation seems to be impossible since commit 2a266f23550b
("KVM MMU: check pending exception before injecting APF) which added
'vcpu->arch.exception.pending' check to kvm_can_do_async_pf.

On x86, kvm_arch_async_page_present() has only one call site:
kvm_check_async_pf_completion() loop and we only enter the loop when
kvm_arch_can_inject_async_page_present(vcpu) which when async pf msr
is enabled, translates into kvm_can_do_async_pf().

There is also one problem with the cancellation mechanism. We don't seem
to check that the 'page not present' notification we're canceling matches
the 'page ready' notification so in theory, we may erroneously drop two
valid events.

Revert the commit.

Reviewed-by: Gavin Shan <gshan@redhat.com>
Signed-off-by: Vitaly Kuznetsov <vkuznets@redhat.com>
---
 arch/x86/kvm/x86.c | 23 +----------------------
 1 file changed, 1 insertion(+), 22 deletions(-)

```
#### [linux-next PATCH] mm/gup.c: Convert to use get_user_{page|pages}_fast_only()
##### From: Souptick Joarder <jrdr.linux@gmail.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Souptick Joarder <jrdr.linux@gmail.com>
X-Patchwork-Id: 11568285
Return-Path: <SRS0=SRxi=7H=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 7394090
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 25 May 2020 08:45:30 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 5156F207FB
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 25 May 2020 08:45:30 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=gmail.com header.i=@gmail.com
 header.b="eHKd4FJ/"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2388979AbgEYIpa (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 25 May 2020 04:45:30 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:48740 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S2388182AbgEYIp3 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 25 May 2020 04:45:29 -0400
Received: from mail-pj1-x1043.google.com (mail-pj1-x1043.google.com
 [IPv6:2607:f8b0:4864:20::1043])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id F0E60C061A0E;
        Mon, 25 May 2020 01:45:28 -0700 (PDT)
Received: by mail-pj1-x1043.google.com with SMTP id l73so3786503pjb.1;
        Mon, 25 May 2020 01:45:28 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=from:to:cc:subject:date:message-id;
        bh=xIp7S4eKuJwr9rPto7gGDP32MbTGjMG7xWgiGrxqaa8=;
        b=eHKd4FJ/LhnxCwbYJd9xJpPseL8ZeTbzp30ima/s7CvTvyoNyDAHun3DlYplnaoUmm
         WmdWbAsB+uWL6loIkOkF2P4meXj9ZAxJRXF2jYx8O+rWmgk9tXUQp/A7rg3NChZvujQg
         Z32uzzHBKZN+ASv36UWG9w07CmxJ59Rkf97VAfK4qYPa5j3i89kgk3qmijK9/tQF5571
         l5kD8krIrZ0q/ClDhTGUfsLZDuPDCSlzAZ4knZuKBYNKZdGA7vae5ISjUA7H9hK0zfux
         oSOYRMxPzVmYKxtB6a7L9/GSenDxkQrDE6DdvAz9CFsy3nb6Lg+TZwsw4yvB4wjE6+GX
         G8Ow==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id;
        bh=xIp7S4eKuJwr9rPto7gGDP32MbTGjMG7xWgiGrxqaa8=;
        b=uZcIjNWTQgy9XQWJbUe+OxAr7pBj6t6LtRVeaT2l7PCxoKs+7qQ09YbRK+xlVUeiui
         ffpnnjuEkYO0BuRSeZk4O/9ICXI7VYwOjGX7CICPk63mazD3Df44r/lJsqc3YRJzXwUX
         sJZs8f6GtVefhM1Wzf3Vh8rmma4xHDKG8jF2BfalIyaHj/cZeuKZxN5OYi3kRNiRPBTx
         qoehUuUCBiJwQV0OBGpi+KleDbt1v5eHmmf9NsrmL8N4ZlcXzvBssvakD23mZpBWBZjS
         +LFHY3180Djm3mLbZ6xz4thOvQDcayhWDUk//becY5m/OARS2cSxRd6u1GD3bKuLh8kx
         VfPg==
X-Gm-Message-State: AOAM533Yqm87b3ACGIbn65qYDJ2Lhjajh8YI8FpLrdjdrAH7Uo7gehxU
        tmtlYQDFj6P9XAnEstPNFh0=
X-Google-Smtp-Source: 
 ABdhPJyFbgAkG8HlyfL5SMh79GjfF5CAWLWF+UjQrHsrcVuTuiwVpsTNDu8PyJZubtZx619YVmie7w==
X-Received: by 2002:a17:90a:ba8b:: with SMTP id
 t11mr20539106pjr.191.1590396328257;
        Mon, 25 May 2020 01:45:28 -0700 (PDT)
Received: from jordon-HP-15-Notebook-PC.domain.name ([122.179.55.198])
        by smtp.gmail.com with ESMTPSA id
 i10sm12491108pfa.166.2020.05.25.01.45.21
        (version=TLS1_2 cipher=ECDHE-ECDSA-AES128-GCM-SHA256 bits=128/128);
        Mon, 25 May 2020 01:45:27 -0700 (PDT)
From: Souptick Joarder <jrdr.linux@gmail.com>
To: paulus@ozlabs.org, mpe@ellerman.id.au, benh@kernel.crashing.org,
        akpm@linux-foundation.org, peterz@infradead.org, mingo@redhat.com,
        acme@kernel.org, mark.rutland@arm.com,
        alexander.shishkin@linux.intel.com, jolsa@redhat.com,
        namhyung@kernel.org, pbonzini@redhat.com, sfr@canb.auug.org.au,
        rppt@linux.ibm.com, aneesh.kumar@linux.ibm.com, msuchanek@suse.de
Cc: kvm-ppc@vger.kernel.org, linuxppc-dev@lists.ozlabs.org,
        linux-kernel@vger.kernel.org, linux-mm@kvack.org,
        kvm@vger.kernel.org, Souptick Joarder <jrdr.linux@gmail.com>,
        Matthew Wilcox <willy@infradead.org>,
        John Hubbard <jhubbard@nvidia.com>
Subject: [linux-next PATCH] mm/gup.c: Convert to use
 get_user_{page|pages}_fast_only()
Date: Mon, 25 May 2020 14:23:32 +0530
Message-Id: <1590396812-31277-1-git-send-email-jrdr.linux@gmail.com>
X-Mailer: git-send-email 1.9.1
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

API __get_user_pages_fast() renamed to get_user_pages_fast_only()
to align with pin_user_pages_fast_only().

As part of this we will get rid of write parameter.
Instead caller will pass FOLL_WRITE to get_user_pages_fast_only().
This will not change any existing functionality of the API.

All the callers are changed to pass FOLL_WRITE.

Also introduce get_user_page_fast_only(), and use it in a few
places that hard-code nr_pages to 1.

Updated the documentation of the API.

Signed-off-by: Souptick Joarder <jrdr.linux@gmail.com>
Reviewed-by: John Hubbard <jhubbard@nvidia.com>
Cc: Matthew Wilcox <willy@infradead.org>
Cc: John Hubbard <jhubbard@nvidia.com>
---
 arch/powerpc/kvm/book3s_64_mmu_hv.c    |  2 +-
 arch/powerpc/kvm/book3s_64_mmu_radix.c |  2 +-
 arch/powerpc/perf/callchain_64.c       |  4 +---
 include/linux/mm.h                     | 10 ++++++++--
 kernel/events/core.c                   |  4 ++--
 mm/gup.c                               | 29 ++++++++++++++++-------------
 virt/kvm/kvm_main.c                    |  8 +++-----
 7 files changed, 32 insertions(+), 27 deletions(-)

```
#### [PULL 01/10] vfio-ccw: Enable transparent CCW IPL from DASD
##### From: Cornelia Huck <cohuck@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Cornelia Huck <cohuck@redhat.com>
X-Patchwork-Id: 11568485
Return-Path: <SRS0=SRxi=7H=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 657FF1391
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 25 May 2020 09:41:33 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 4E8772078B
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 25 May 2020 09:41:33 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="d4P1rfRx"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2389627AbgEYJlc (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 25 May 2020 05:41:32 -0400
Received: from us-smtp-delivery-1.mimecast.com ([207.211.31.120]:44818 "EHLO
        us-smtp-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org
        with ESMTP id S2389623AbgEYJlb (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 25 May 2020 05:41:31 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1590399688;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding:
         in-reply-to:in-reply-to:references:references;
        bh=22uv9msgebjtsAwkM95GhvpaRamwNmglM2omeg33d04=;
        b=d4P1rfRxIPsMevMcu4rwlLIwCAv6wBywtS6S4uGPSAKCI7Y/imrS8J4hZuF+1aGA3YJisB
        wOy1HNYnD+HwJahMaayF3wluIfj38h5mU2k65l9n9yhiZFUH8HiHCeCiFf/xQbHf/HLPez
        mMLihtyrxoHjg1FJ3CInYnmQKTvksd4=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-163-j4sEfD5ZNpKPy9uAk_5HUg-1; Mon, 25 May 2020 05:41:24 -0400
X-MC-Unique: j4sEfD5ZNpKPy9uAk_5HUg-1
Received: from smtp.corp.redhat.com (int-mx05.intmail.prod.int.phx2.redhat.com
 [10.5.11.15])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 213A78015D2;
        Mon, 25 May 2020 09:41:23 +0000 (UTC)
Received: from localhost (ovpn-112-215.ams2.redhat.com [10.36.112.215])
        by smtp.corp.redhat.com (Postfix) with ESMTPS id 8B3DB768A0;
        Mon, 25 May 2020 09:41:21 +0000 (UTC)
From: Cornelia Huck <cohuck@redhat.com>
To: Heiko Carstens <heiko.carstens@de.ibm.com>,
        Vasily Gorbik <gor@linux.ibm.com>,
        Christian Borntraeger <borntraeger@de.ibm.com>
Cc: Eric Farman <farman@linux.ibm.com>,
        Halil Pasic <pasic@linux.ibm.com>, linux-s390@vger.kernel.org,
        kvm@vger.kernel.org, Jared Rossi <jrossi@linux.ibm.com>,
        Cornelia Huck <cohuck@redhat.com>
Subject: [PULL 01/10] vfio-ccw: Enable transparent CCW IPL from DASD
Date: Mon, 25 May 2020 11:41:06 +0200
Message-Id: <20200525094115.222299-2-cohuck@redhat.com>
In-Reply-To: <20200525094115.222299-1-cohuck@redhat.com>
References: <20200525094115.222299-1-cohuck@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.15
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Jared Rossi <jrossi@linux.ibm.com>

Remove the explicit prefetch check when using vfio-ccw devices.
This check does not trigger in practice as all Linux channel programs
are intended to use prefetch.

It is expected that all ORBs issued by Linux will request prefetch.
Although non-prefetching ORBs are not rejected, they will prefetch
nonetheless. A warning is issued up to once per 5 seconds when a
forced prefetch occurs.

A non-prefetch ORB does not necessarily result in an error, however
frequent encounters with non-prefetch ORBs indicate that channel
programs are being executed in a way that is inconsistent with what
the guest is requesting. While there is currently no known case of an
error caused by forced prefetch, it is possible in theory that forced
prefetch could result in an error if applied to a channel program that
is dependent on non-prefetch.

Signed-off-by: Jared Rossi <jrossi@linux.ibm.com>
Reviewed-by: Eric Farman <farman@linux.ibm.com>
Message-Id: <20200506212440.31323-2-jrossi@linux.ibm.com>
Signed-off-by: Cornelia Huck <cohuck@redhat.com>
---
 Documentation/s390/vfio-ccw.rst |  6 ++++++
 drivers/s390/cio/vfio_ccw_cp.c  | 19 ++++++++++++-------
 2 files changed, 18 insertions(+), 7 deletions(-)

```
