#### [GIT PULL] VFIO fix for v5.8-rc7
##### From: Alex Williamson <alex.williamson@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Alex Williamson <alex.williamson@redhat.com>
X-Patchwork-Id: 11674095
Return-Path: <SRS0=/Nc8=A7=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id F414C913
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 20 Jul 2020 14:34:37 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id DC4C422B4D
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 20 Jul 2020 14:34:37 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="KJDaus+J"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728409AbgGTOef (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 20 Jul 2020 10:34:35 -0400
Received: from us-smtp-delivery-1.mimecast.com ([205.139.110.120]:25636 "EHLO
        us-smtp-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org
        with ESMTP id S1726520AbgGTOee (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 20 Jul 2020 10:34:34 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1595255671;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:content-type:content-type:
         content-transfer-encoding:content-transfer-encoding;
        bh=yRLvzSgd5JXKqp0y2dRzttHbtXvNZ2pju4sRCN1pW8Y=;
        b=KJDaus+JD+5/TkLohfLX4SkrDWUc7Hfrk+SgZzgdrLsXacluQhjIyJtX2qELN9cqdsiEYg
        uBvldFguNSiG+uQzWQ2p6QPSazuq/LllDWg6VwnVd6j+RtYqFvOWoIyogyWuHi7pKg219o
        lifxptAI1jutJZagA1MG6Vf7upwwFk0=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-138-Qviih4syMtqsophRGSqoIQ-1; Mon, 20 Jul 2020 10:34:29 -0400
X-MC-Unique: Qviih4syMtqsophRGSqoIQ-1
Received: from smtp.corp.redhat.com (int-mx06.intmail.prod.int.phx2.redhat.com
 [10.5.11.16])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 738B2800460;
        Mon, 20 Jul 2020 14:34:28 +0000 (UTC)
Received: from x1.home (ovpn-112-71.phx2.redhat.com [10.3.112.71])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 3B1255C1D4;
        Mon, 20 Jul 2020 14:34:28 +0000 (UTC)
Date: Mon, 20 Jul 2020 08:34:27 -0600
From: Alex Williamson <alex.williamson@redhat.com>
To: Linus Torvalds <torvalds@linux-foundation.org>
Cc: "kvm@vger.kernel.org" <kvm@vger.kernel.org>,
        "linux-kernel@vger.kernel.org" <linux-kernel@vger.kernel.org>
Subject: [GIT PULL] VFIO fix for v5.8-rc7
Message-ID: <20200720083427.50202e82@x1.home>
Organization: Red Hat
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.16
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Hi Linus,

The following changes since commit 11ba468877bb23f28956a35e896356252d63c983:

  Linux 5.8-rc5 (2020-07-12 16:34:50 -0700)

are available in the Git repository at:

  git://github.com/awilliam/linux-vfio.git tags/vfio-v5.8-rc7

for you to fetch changes up to b872d0640840018669032b20b6375a478ed1f923:

  vfio/pci: fix racy on error and request eventfd ctx (2020-07-17 08:28:40 -0600)

----------------------------------------------------------------
VFIO fixes for v5.8-rc7

 - Fix race with eventfd ctx cleared outside of mutex (Zeng Tao)

----------------------------------------------------------------
Zeng Tao (1):
      vfio/pci: fix racy on error and request eventfd ctx

 drivers/vfio/pci/vfio_pci.c | 5 +++++
 1 file changed, 5 insertions(+)
```
#### [kvm-unit-tests PATCH v2] s390x: Ultavisor guest API test
##### From: Janosch Frank <frankja@linux.ibm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Janosch Frank <frankja@linux.ibm.com>
X-Patchwork-Id: 11673975
Return-Path: <SRS0=/Nc8=A7=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id B0F766C1
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 20 Jul 2020 13:36:10 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 922B022C9C
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 20 Jul 2020 13:36:10 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726390AbgGTNgK (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 20 Jul 2020 09:36:10 -0400
Received: from mx0a-001b2d01.pphosted.com ([148.163.156.1]:31304 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1725792AbgGTNgJ (ORCPT
        <rfc822;kvm@vger.kernel.org>); Mon, 20 Jul 2020 09:36:09 -0400
Received: from pps.filterd (m0187473.ppops.net [127.0.0.1])
        by mx0a-001b2d01.pphosted.com (8.16.0.42/8.16.0.42) with SMTP id
 06KDWVCm127041;
        Mon, 20 Jul 2020 09:36:09 -0400
Received: from pps.reinject (localhost [127.0.0.1])
        by mx0a-001b2d01.pphosted.com with ESMTP id 32bvquk55y-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Mon, 20 Jul 2020 09:36:08 -0400
Received: from m0187473.ppops.net (m0187473.ppops.net [127.0.0.1])
        by pps.reinject (8.16.0.36/8.16.0.36) with SMTP id 06KDWoTw127754;
        Mon, 20 Jul 2020 09:36:08 -0400
Received: from ppma03fra.de.ibm.com (6b.4a.5195.ip4.static.sl-reverse.com
 [149.81.74.107])
        by mx0a-001b2d01.pphosted.com with ESMTP id 32bvquk54u-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Mon, 20 Jul 2020 09:36:08 -0400
Received: from pps.filterd (ppma03fra.de.ibm.com [127.0.0.1])
        by ppma03fra.de.ibm.com (8.16.0.42/8.16.0.42) with SMTP id
 06KDU8X9025790;
        Mon, 20 Jul 2020 13:36:05 GMT
Received: from b06cxnps3074.portsmouth.uk.ibm.com
 (d06relay09.portsmouth.uk.ibm.com [9.149.109.194])
        by ppma03fra.de.ibm.com with ESMTP id 32brq81c4q-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Mon, 20 Jul 2020 13:36:05 +0000
Received: from d06av25.portsmouth.uk.ibm.com (d06av25.portsmouth.uk.ibm.com
 [9.149.105.61])
        by b06cxnps3074.portsmouth.uk.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id 06KDa20h29884900
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Mon, 20 Jul 2020 13:36:02 GMT
Received: from d06av25.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 5E6F011C04C;
        Mon, 20 Jul 2020 13:36:02 +0000 (GMT)
Received: from d06av25.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 9809A11C05B;
        Mon, 20 Jul 2020 13:36:01 +0000 (GMT)
Received: from linux01.pok.stglabs.ibm.com (unknown [9.114.17.81])
        by d06av25.portsmouth.uk.ibm.com (Postfix) with ESMTP;
        Mon, 20 Jul 2020 13:36:01 +0000 (GMT)
From: Janosch Frank <frankja@linux.ibm.com>
To: kvm@vger.kernel.org
Cc: thuth@redhat.com, linux-s390@vger.kernel.org, david@redhat.com,
        borntraeger@de.ibm.com, cohuck@redhat.com, imbrenda@linux.ibm.com
Subject: [kvm-unit-tests PATCH v2] s390x: Ultavisor guest API test
Date: Mon, 20 Jul 2020 09:35:59 -0400
Message-Id: <20200720133559.69898-1-frankja@linux.ibm.com>
X-Mailer: git-send-email 2.25.1
In-Reply-To: <20200717145813.62573-4-frankja@linux.ibm.com>
References: <20200717145813.62573-4-frankja@linux.ibm.com>
MIME-Version: 1.0
X-TM-AS-GCONF: 00
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.235,18.0.687
 definitions=2020-07-20_09:2020-07-20,2020-07-20 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 mlxlogscore=999 spamscore=0
 bulkscore=0 impostorscore=0 malwarescore=0 mlxscore=0 lowpriorityscore=0
 suspectscore=3 adultscore=0 clxscore=1015 phishscore=0 priorityscore=1501
 classifier=spam adjust=0 reason=mlx scancount=1 engine=8.12.0-2006250000
 definitions=main-2007200095
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Test the error conditions of guest 2 Ultravisor calls, namely:
     * Query Ultravisor information
     * Set shared access
     * Remove shared access

Signed-off-by: Janosch Frank <frankja@linux.ibm.com>
Reviewed-by: Claudio Imbrenda <imbrenda@linux.ibm.com>
---
 lib/s390x/asm/uv.h  |  68 +++++++++++++++++++
 s390x/Makefile      |   1 +
 s390x/unittests.cfg |   3 +
 s390x/uv-guest.c    | 158 ++++++++++++++++++++++++++++++++++++++++++++
 4 files changed, 230 insertions(+)
 create mode 100644 lib/s390x/asm/uv.h
 create mode 100644 s390x/uv-guest.c

diff --git a/lib/s390x/asm/uv.h b/lib/s390x/asm/uv.h
new file mode 100644
index 0000000..14ab5cc
--- /dev/null
+++ b/lib/s390x/asm/uv.h
@@ -0,0 +1,68 @@
+/*
+ * s390x Ultravisor related definitions
+ *
+ * Copyright (c) 2020 IBM Corp
+ *
+ * Authors:
+ *  Janosch Frank <frankja@linux.ibm.com>
+ *
+ * This code is free software; you can redistribute it and/or modify it
+ * under the terms of the GNU General Public License version 2.
+ */
+#ifndef UV_H
+#define UV_H
+
+#define UVC_RC_EXECUTED		0x0001
+#define UVC_RC_INV_CMD		0x0002
+#define UVC_RC_INV_STATE	0x0003
+#define UVC_RC_INV_LEN		0x0005
+#define UVC_RC_NO_RESUME	0x0007
+
+#define UVC_CMD_QUI			0x0001
+#define UVC_CMD_SET_SHARED_ACCESS	0x1000
+#define UVC_CMD_REMOVE_SHARED_ACCESS	0x1001
+
+/* Bits in installed uv calls */
+enum uv_cmds_inst {
+	BIT_UVC_CMD_QUI = 0,
+	BIT_UVC_CMD_SET_SHARED_ACCESS = 8,
+	BIT_UVC_CMD_REMOVE_SHARED_ACCESS = 9,
+};
+
+struct uv_cb_header {
+	u16 len;
+	u16 cmd;	/* Command Code */
+	u16 rc;		/* Response Code */
+	u16 rrc;	/* Return Reason Code */
+} __attribute__((packed))  __attribute__((aligned(8)));
+
+struct uv_cb_qui {
+	struct uv_cb_header header;
+	u64 reserved08;
+	u64 inst_calls_list[4];
+	u64 reserved30[15];
+} __attribute__((packed))  __attribute__((aligned(8)));
+
+struct uv_cb_share {
+	struct uv_cb_header header;
+	u64 reserved08[3];
+	u64 paddr;
+	u64 reserved28;
+} __attribute__((packed))  __attribute__((aligned(8)));
+
+static inline int uv_call(unsigned long r1, unsigned long r2)
+{
+	int cc;
+
+	asm volatile(
+		"0:	.insn rrf,0xB9A40000,%[r1],%[r2],0,0\n"
+		"		brc	3,0b\n"
+		"		ipm	%[cc]\n"
+		"		srl	%[cc],28\n"
+		: [cc] "=d" (cc)
+		: [r1] "a" (r1), [r2] "a" (r2)
+		: "memory", "cc");
+	return cc;
+}
+
+#endif
```
#### [PATCH] KVM: x86: Fix names of implemented kvm_x86_ops in VMX and SVM modules
##### From: Krish Sadhukhan <krish.sadhukhan@oracle.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Krish Sadhukhan <krish.sadhukhan@oracle.com>
X-Patchwork-Id: 11674645
Return-Path: <SRS0=/Nc8=A7=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 7F5E46C1
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 20 Jul 2020 22:55:56 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 5034922CAF
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 20 Jul 2020 22:55:56 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=oracle.com header.i=@oracle.com
 header.b="KspMPLYc"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726555AbgGTWzz (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 20 Jul 2020 18:55:55 -0400
Received: from userp2130.oracle.com ([156.151.31.86]:51392 "EHLO
        userp2130.oracle.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726109AbgGTWzy (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 20 Jul 2020 18:55:54 -0400
Received: from pps.filterd (userp2130.oracle.com [127.0.0.1])
        by userp2130.oracle.com (8.16.0.42/8.16.0.42) with SMTP id
 06KMkU3Y183178;
        Mon, 20 Jul 2020 22:55:48 GMT
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=oracle.com;
 h=from : to : cc :
 subject : date : message-id : in-reply-to : references : mime-version :
 content-transfer-encoding; s=corp-2020-01-29;
 bh=lAMDmMSPe03TMVD16HrjbUC1k3xBR2s09sagwjo/1zo=;
 b=KspMPLYcXm9yrjGUvFLOwk1kRULFpfsXjHgfiY1TVgQ5vDCiSKAwCUukWW1KWGnL9+xh
 GLaX1tGLgTThDQmYRV6hgCk/sktMkbY+6lic8sV11sPiTNlC2lKd9abAlJLaotjc6TA6
 l/vLYwYvb5RYdwH0hObpJJBGcfUYpCcnWWyhRlukhtw2pWA6WW3b2DOUR/W9yiZ/VYlJ
 JgrimEmxZRUT/6iMCKriKjE0zgpXfdT2j8fhFmtWyH+mqmftzLxNoHIoEnqse38pjT8X
 8TuH/s9tt71F1jOJfNCPBgOheT2b/1/PwyTTZp95OtEc9u48N81AY7n6XF3YTw8un6A4 LA==
Received: from userp3030.oracle.com (userp3030.oracle.com [156.151.31.80])
        by userp2130.oracle.com with ESMTP id 32brgr9rxb-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=FAIL);
        Mon, 20 Jul 2020 22:55:48 +0000
Received: from pps.filterd (userp3030.oracle.com [127.0.0.1])
        by userp3030.oracle.com (8.16.0.42/8.16.0.42) with SMTP id
 06KMmxid120275;
        Mon, 20 Jul 2020 22:53:48 GMT
Received: from userv0122.oracle.com (userv0122.oracle.com [156.151.31.75])
        by userp3030.oracle.com with ESMTP id 32djyx4vt4-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Mon, 20 Jul 2020 22:53:47 +0000
Received: from abhmp0008.oracle.com (abhmp0008.oracle.com [141.146.116.14])
        by userv0122.oracle.com (8.14.4/8.14.4) with ESMTP id 06KMmoP3007303;
        Mon, 20 Jul 2020 22:48:50 GMT
Received: from ban25x6uut29.us.oracle.com (/10.153.73.29)
        by default (Oracle Beehive Gateway v4.0)
        with ESMTP ; Mon, 20 Jul 2020 15:48:49 -0700
From: Krish Sadhukhan <krish.sadhukhan@oracle.com>
To: kvm@vger.kernel.org
Cc: jmattson@google.com, sean.j.christopherson@intel.com,
        pbonzini@redhat.com
Subject: [PATCH] KVM: x86: Fix names of implemented kvm_x86_ops in VMX and SVM
 modules
Date: Mon, 20 Jul 2020 18:07:28 -0400
Message-Id: <20200720220728.11140-2-krish.sadhukhan@oracle.com>
X-Mailer: git-send-email 2.20.1
In-Reply-To: <20200720220728.11140-1-krish.sadhukhan@oracle.com>
References: <20200720220728.11140-1-krish.sadhukhan@oracle.com>
MIME-Version: 1.0
X-Proofpoint-Virus-Version: vendor=nai engine=6000 definitions=9688
 signatures=668680
X-Proofpoint-Spam-Details: rule=notspam policy=default score=0 mlxscore=0
 spamscore=0 adultscore=0
 suspectscore=3 phishscore=0 bulkscore=0 malwarescore=0 mlxlogscore=999
 classifier=spam adjust=0 reason=mlx scancount=1 engine=8.12.0-2006250000
 definitions=main-2007200142
X-Proofpoint-Virus-Version: vendor=nai engine=6000 definitions=9688
 signatures=668680
X-Proofpoint-Spam-Details: rule=notspam policy=default score=0 malwarescore=0
 bulkscore=0 spamscore=0
 impostorscore=0 suspectscore=3 adultscore=0 clxscore=1015 mlxlogscore=999
 priorityscore=1501 phishscore=0 lowpriorityscore=0 mlxscore=0
 classifier=spam adjust=0 reason=mlx scancount=1 engine=8.12.0-2006250000
 definitions=main-2007200142
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Some of the names do not have a corresponding 'vmx_' or 'svm_' prefix. Also,
the order of the words in some of the names is not the same as that in the
kvm_x86_ops structure. Fixing the naming will help in better readability of
the code and maintenance.

Signed-off-by: Krish Sadhukhan <krish.sadhukhan@oracle.com>
---
 arch/x86/kvm/svm/avic.c   |  4 +--
 arch/x86/kvm/svm/svm.c    | 46 ++++++++++++++++----------------
 arch/x86/kvm/svm/svm.h    |  2 +-
 arch/x86/kvm/vmx/nested.c |  4 +--
 arch/x86/kvm/vmx/vmx.c    | 56 +++++++++++++++++++--------------------
 arch/x86/kvm/vmx/vmx.h    |  4 +--
 6 files changed, 58 insertions(+), 58 deletions(-)

```
#### [PATCH v9 01/15] s390/vfio-ap: add version vfio_ap module
##### From: Tony Krowiak <akrowiak@linux.ibm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Tony Krowiak <akrowiak@linux.ibm.com>
X-Patchwork-Id: 11674141
Return-Path: <SRS0=/Nc8=A7=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id BC054913
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 20 Jul 2020 15:05:28 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id AE5022065D
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 20 Jul 2020 15:05:28 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729108AbgGTPFW (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 20 Jul 2020 11:05:22 -0400
Received: from mx0a-001b2d01.pphosted.com ([148.163.156.1]:15450 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1728448AbgGTPEK (ORCPT
        <rfc822;kvm@vger.kernel.org>); Mon, 20 Jul 2020 11:04:10 -0400
Received: from pps.filterd (m0098394.ppops.net [127.0.0.1])
        by mx0a-001b2d01.pphosted.com (8.16.0.42/8.16.0.42) with SMTP id
 06KF3Qlo176309;
        Mon, 20 Jul 2020 11:04:09 -0400
Received: from pps.reinject (localhost [127.0.0.1])
        by mx0a-001b2d01.pphosted.com with ESMTP id 32bwk775vr-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Mon, 20 Jul 2020 11:04:05 -0400
Received: from m0098394.ppops.net (m0098394.ppops.net [127.0.0.1])
        by pps.reinject (8.16.0.36/8.16.0.36) with SMTP id 06KF3mEi178731;
        Mon, 20 Jul 2020 11:04:03 -0400
Received: from ppma03wdc.us.ibm.com (ba.79.3fa9.ip4.static.sl-reverse.com
 [169.63.121.186])
        by mx0a-001b2d01.pphosted.com with ESMTP id 32bwk775q5-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Mon, 20 Jul 2020 11:04:02 -0400
Received: from pps.filterd (ppma03wdc.us.ibm.com [127.0.0.1])
        by ppma03wdc.us.ibm.com (8.16.0.42/8.16.0.42) with SMTP id
 06KEito6031921;
        Mon, 20 Jul 2020 15:03:56 GMT
Received: from b03cxnp07028.gho.boulder.ibm.com
 (b03cxnp07028.gho.boulder.ibm.com [9.17.130.15])
        by ppma03wdc.us.ibm.com with ESMTP id 32brq8t1bn-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Mon, 20 Jul 2020 15:03:55 +0000
Received: from b03ledav001.gho.boulder.ibm.com
 (b03ledav001.gho.boulder.ibm.com [9.17.130.232])
        by b03cxnp07028.gho.boulder.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id 06KF3r7q51183932
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Mon, 20 Jul 2020 15:03:53 GMT
Received: from b03ledav001.gho.boulder.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id EC16B6E05B;
        Mon, 20 Jul 2020 15:03:52 +0000 (GMT)
Received: from b03ledav001.gho.boulder.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id BA8286E04E;
        Mon, 20 Jul 2020 15:03:51 +0000 (GMT)
Received: from cpe-172-100-175-116.stny.res.rr.com.com (unknown [9.85.188.6])
        by b03ledav001.gho.boulder.ibm.com (Postfix) with ESMTP;
        Mon, 20 Jul 2020 15:03:51 +0000 (GMT)
From: Tony Krowiak <akrowiak@linux.ibm.com>
To: linux-s390@vger.kernel.org, linux-kernel@vger.kernel.org,
        kvm@vger.kernel.org
Cc: freude@linux.ibm.com, borntraeger@de.ibm.com, cohuck@redhat.com,
        mjrosato@linux.ibm.com, pasic@linux.ibm.com,
        alex.williamson@redhat.com, kwankhede@nvidia.com,
        fiuczy@linux.ibm.com, Tony Krowiak <akrowiak@linux.ibm.com>
Subject: [PATCH v9 01/15] s390/vfio-ap: add version vfio_ap module
Date: Mon, 20 Jul 2020 11:03:30 -0400
Message-Id: <20200720150344.24488-2-akrowiak@linux.ibm.com>
X-Mailer: git-send-email 2.21.1
In-Reply-To: <20200720150344.24488-1-akrowiak@linux.ibm.com>
References: <20200720150344.24488-1-akrowiak@linux.ibm.com>
MIME-Version: 1.0
X-TM-AS-GCONF: 00
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.235,18.0.687
 definitions=2020-07-20_09:2020-07-20,2020-07-20 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 malwarescore=0 spamscore=0
 lowpriorityscore=0 clxscore=1015 mlxscore=0 bulkscore=0 adultscore=0
 phishscore=0 priorityscore=1501 suspectscore=3 mlxlogscore=999
 impostorscore=0 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.12.0-2006250000 definitions=main-2007200104
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Let's set a version for the vfio_ap module so that automated regression
tests can determine whether dynamic configuration tests can be run or
not.

Signed-off-by: Tony Krowiak <akrowiak@linux.ibm.com>
---
 drivers/s390/crypto/vfio_ap_drv.c | 2 ++
 1 file changed, 2 insertions(+)

```
#### [PATCH v4] kvm,x86: Exit to user space in case page fault error
##### From: Vivek Goyal <vgoyal@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Vivek Goyal <vgoyal@redhat.com>
X-Patchwork-Id: 11674575
Return-Path: <SRS0=/Nc8=A7=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 5BEF4618
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 20 Jul 2020 21:14:15 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 3F48422BEF
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 20 Jul 2020 21:14:15 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="KRY9NHdj"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726691AbgGTVOL (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 20 Jul 2020 17:14:11 -0400
Received: from us-smtp-delivery-1.mimecast.com ([205.139.110.120]:34779 "EHLO
        us-smtp-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org
        with ESMTP id S1726535AbgGTVOK (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 20 Jul 2020 17:14:10 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1595279648;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:content-type:content-type;
        bh=z7LXMfKrfk7Wfv9dC4SyiwCUIm3g3Kz7EvEC6sGdKYI=;
        b=KRY9NHdjFaNcKmn6Ozq7fYEZ7j/Kxyf8wiT8vg1k2bbbGCiDH2DVbNItKC+ZpDKaLhIGIz
        Dc7ByK0z/o5gf/7i1Ap64FG6V4KoCS3UPKEqgYpEgVYXGU8i2C9YyFTK1rzMIAf8+GWG5d
        CYHwPhqfniugFve940gQsLdn0MK4tng=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-158-Hs-IMMLAN_CDHwyZ-nWThA-1; Mon, 20 Jul 2020 17:14:04 -0400
X-MC-Unique: Hs-IMMLAN_CDHwyZ-nWThA-1
Received: from smtp.corp.redhat.com (int-mx07.intmail.prod.int.phx2.redhat.com
 [10.5.11.22])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 356DB57;
        Mon, 20 Jul 2020 21:14:03 +0000 (UTC)
Received: from horse.redhat.com (ovpn-115-128.rdu2.redhat.com [10.10.115.128])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 18A2210002B5;
        Mon, 20 Jul 2020 21:14:00 +0000 (UTC)
Received: by horse.redhat.com (Postfix, from userid 10451)
        id 8EE77220203; Mon, 20 Jul 2020 17:13:59 -0400 (EDT)
Date: Mon, 20 Jul 2020 17:13:59 -0400
From: Vivek Goyal <vgoyal@redhat.com>
To: kvm@vger.kernel.org, linux-kernel@vger.kernel.org
Cc: virtio-fs-list <virtio-fs@redhat.com>, vkuznets@redhat.com,
        pbonzini@redhat.com, sean.j.christopherson@intel.com
Subject: [PATCH v4] kvm,x86: Exit to user space in case page fault error
Message-ID: <20200720211359.GF502563@redhat.com>
MIME-Version: 1.0
Content-Disposition: inline
X-Scanned-By: MIMEDefang 2.84 on 10.5.11.22
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Page fault error handling behavior in kvm seems little inconsistent when
page fault reports error. If we are doing fault synchronously
then we capture error (-EFAULT) returned by __gfn_to_pfn_memslot() and
exit to user space and qemu reports error, "error: kvm run failed Bad address".

But if we are doing async page fault, then async_pf_execute() will simply
ignore the error reported by get_user_pages_remote() or
by kvm_mmu_do_page_fault(). It is assumed that page fault was successful
and either a page ready event is injected in guest or guest is brought
out of artificial halt state and run again. In both the cases when guest
retries the instruction, it takes exit again as page fault was not
successful in previous attempt. And then this infinite loop continues
forever.

Trying fault in a loop will make sense if error is temporary and will
be resolved on retry. But I don't see any intention in the code to
determine if error is temporary or not.  Whether to do fault synchronously
or asynchronously, depends on so many variables but none of the varibales
is whether error is temporary or not. (kvm_can_do_async_pf()).

And that makes it very inconsistent or unpredictable to figure out whether
kvm will exit to qemu with error or it will just retry and go into an
infinite loop.

This patch tries to make this behavior consistent. That is instead of
getting into infinite loop of retrying page fault, exit to user space
and stop VM if page fault error happens.

In future this can be improved by injecting errors into guest. As of
now we don't have any race free method to inject errors in guest.

When page fault error happens in async path save that pfn and when next
time guest retries, do a sync fault instead of async fault. So that if error
is encountered, we exit to qemu and avoid infinite loop.

We maintain a cache of error gfns and force sync fault if a gfn is
found in cache of error gfn. There is a small possibility that we
miss an error gfn (as it got overwritten by a new error gfn). But
its just a hint and sooner or later some error pfn will match
and we will force sync fault and exit to user space.

Changes from v3:
- Added function kvm_find_and_remove_error_gfn() and removed
  kvm_find_error_gfn() and kvm_del_error_gfn(). (Vitaly)

- Added a macro GFN_INVALID (Vitaly).

- Used gpa_to_gfn() to convert gpa to gfn (Vitaly)

Change from v2:
- Fixed a warning by converting kvm_find_error_gfn() static.

Change from v1:
- Maintain a cache of error gfns, instead of single gfn. (Vitaly)

Signed-off-by: Vivek Goyal <vgoyal@redhat.com>
---
 arch/x86/include/asm/kvm_host.h |  2 ++
 arch/x86/kvm/mmu.h              |  2 +-
 arch/x86/kvm/mmu/mmu.c          |  2 +-
 arch/x86/kvm/x86.c              | 54 +++++++++++++++++++++++++++++++--
 include/linux/kvm_types.h       |  1 +
 5 files changed, 56 insertions(+), 5 deletions(-)

```
#### [PATCH] vfio dma_map/unmap: optimized for hugetlbfs pages
##### From: Jay Zhou <jianjay.zhou@huawei.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Jay Zhou <jianjay.zhou@huawei.com>
X-Patchwork-Id: 11673211
Return-Path: <SRS0=/Nc8=A7=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 822E41392
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 20 Jul 2020 08:30:10 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 5FAE321775
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 20 Jul 2020 08:30:10 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727905AbgGTIaG (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 20 Jul 2020 04:30:06 -0400
Received: from szxga04-in.huawei.com ([45.249.212.190]:8333 "EHLO huawei.com"
        rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org with ESMTP
        id S1727809AbgGTIaG (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 20 Jul 2020 04:30:06 -0400
Received: from DGGEMS401-HUB.china.huawei.com (unknown [172.30.72.58])
        by Forcepoint Email with ESMTP id B96D04557B5E0E7B3366;
        Mon, 20 Jul 2020 16:30:01 +0800 (CST)
Received: from localhost (10.174.149.93) by DGGEMS401-HUB.china.huawei.com
 (10.3.19.201) with Microsoft SMTP Server id 14.3.487.0; Mon, 20 Jul 2020
 16:29:51 +0800
From: Jay Zhou <jianjay.zhou@huawei.com>
To: <linux-kernel@vger.kernel.org>, <kvm@vger.kernel.org>
CC: <alex.williamson@redhat.com>, <cohuck@redhat.com>,
        <maoming.maoming@huawei.com>, <jianjay.zhou@huawei.com>,
        <weidong.huang@huawei.com>
Subject: [PATCH] vfio dma_map/unmap: optimized for hugetlbfs pages
Date: Mon, 20 Jul 2020 16:29:47 +0800
Message-ID: <20200720082947.1770-1-jianjay.zhou@huawei.com>
X-Mailer: git-send-email 2.14.1.windows.1
MIME-Version: 1.0
X-Originating-IP: [10.174.149.93]
X-CFilter-Loop: Reflected
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Ming Mao <maoming.maoming@huawei.com>

Hi all,
I'm working on starting lots of big size
Virtual Machines(memory: >128GB) with VFIO-devices. And I
encounter a problem that is the waiting time of starting
all Virtual Machines is too long. I analyze the startup log
and find that the time of pinning/unpinning pages could be reduced.

In the original process, to make sure the pages are contiguous,
we have to check all pages one by one. I think maybe we can use
hugetlbfs pages which can skip this step.
So I create a patch to do this.
According to my test, the result of this patch is pretty well.

Virtual Machine: 50G memory, 32 CPU, 1 VFIO-device, 1G hugetlbfs page
        original   after optimization
pin time   700ms          0.1ms

I Suppose that:
1)the hugetlbfs page should not be split
2)PG_reserved is not relevant for hugetlbfs pages
3)we can delete the for loops and use some operations
(such as atomic_add,page_ref_add) instead

please correct me if I am wrong.

Thanks.

Signed-off-by: Ming Mao <maoming.maoming@huawei.com>
Reported-by: kernel test robot <lkp@intel.com>
---
 drivers/vfio/vfio_iommu_type1.c | 236 ++++++++++++++++++++++++++++++--
 include/linux/vfio.h            |  20 +++
 2 files changed, 246 insertions(+), 10 deletions(-)

```
#### [PATCH] vfio/pci: Hold igate across releasing eventfd contextsFrom: Alex Williamson <alex.williamson@redhat.com>
##### From: Alex Williamson <alex.williamson@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Alex Williamson <alex.williamson@redhat.com>
X-Patchwork-Id: 11674571
Return-Path: <SRS0=/Nc8=A7=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id BBD711510
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 20 Jul 2020 21:09:38 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 9FD5522B51
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 20 Jul 2020 21:09:38 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="WWarP0NI"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726530AbgGTVJf (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 20 Jul 2020 17:09:35 -0400
Received: from us-smtp-2.mimecast.com ([207.211.31.81]:28644 "EHLO
        us-smtp-delivery-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S1726046AbgGTVJe (ORCPT
        <rfc822;kvm@vger.kernel.org>); Mon, 20 Jul 2020 17:09:34 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1595279373;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:content-type:content-type:
         content-transfer-encoding:content-transfer-encoding;
        bh=mlHthLgSXx+0yukG47QpZktLnXxCHnNa5qkendynQ2U=;
        b=WWarP0NI0eAqiVyUopWQyBPrp9wat8QuH4IMT4MJAmqqIK5eZ2e2dzQQfOy5nk5IDfFA5n
        2LEAhmBiqCeUuJ2uvzFHjwrJiYwN+2xqLNu7f+8lT0jnrbFOqyRpCwJd580r0wPaOwuF21
        vbjnX0p+WsOA0CFczMqH2XSEPRJvqt4=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-305-nSOylXgzOdqC6eVgTMJPiw-1; Mon, 20 Jul 2020 17:09:31 -0400
X-MC-Unique: nSOylXgzOdqC6eVgTMJPiw-1
Received: from smtp.corp.redhat.com (int-mx03.intmail.prod.int.phx2.redhat.com
 [10.5.11.13])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id BC3D41902EA0;
        Mon, 20 Jul 2020 21:09:30 +0000 (UTC)
Received: from gimli.home (ovpn-112-71.phx2.redhat.com [10.3.112.71])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 3CB2176214;
        Mon, 20 Jul 2020 21:09:27 +0000 (UTC)
Subject: [PATCH] vfio/pci: Hold igate across releasing eventfd contexts
From: Alex Williamson <alex.williamson@redhat.com>
To: alex.williamson@redhat.com
Cc: linux-kernel@vger.kernel.org, kvm@vger.kernel.org,
        cohuck@redhat.com, prime.zeng@hisilicon.com
Date: Mon, 20 Jul 2020 15:09:27 -0600
Message-ID: <159527934542.26615.503005826695043299.stgit@gimli.home>
User-Agent: StGit/0.19-dirty
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.13
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

No need to release and immediately re-acquire igate while clearing
out the eventfd ctxs.

Signed-off-by: Alex Williamson <alex.williamson@redhat.com>
---
 drivers/vfio/pci/vfio_pci.c |    4 +---
 1 file changed, 1 insertion(+), 3 deletions(-)

```
#### [PATCH] vhost: vdpa: remove per device feature whitelist
##### From: Jason Wang <jasowang@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Jason Wang <jasowang@redhat.com>
X-Patchwork-Id: 11673219
Return-Path: <SRS0=/Nc8=A7=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 3888B13A4
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 20 Jul 2020 08:51:01 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 1D0FD21775
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 20 Jul 2020 08:51:01 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="JwbAu9Pr"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728033AbgGTIu7 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 20 Jul 2020 04:50:59 -0400
Received: from us-smtp-delivery-1.mimecast.com ([207.211.31.120]:60676 "EHLO
        us-smtp-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org
        with ESMTP id S1728025AbgGTIu6 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 20 Jul 2020 04:50:58 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1595235057;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=Y9alvxXRA5HGHZ+mBaUFBL6krSh1l8I0iweYECqaRAI=;
        b=JwbAu9PrIH9ldzdzBukxFqWWXhSu8kAPolV4efZUzbHckIjm1E5vC0SH+UzR4y/7QzTMGu
        WU292x1FRwC4JhAJALbGhAXZi8nsqHuztetZ6mBaLAy4cMb0roRYgGG8SGulDRY1B1Bw0p
        XWA2eI54S6DuwUsfzlQ2Tn/KjJYVET8=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-159-OjPYk_K7ONe759fJWsHSAw-1; Mon, 20 Jul 2020 04:50:53 -0400
X-MC-Unique: OjPYk_K7ONe759fJWsHSAw-1
Received: from smtp.corp.redhat.com (int-mx07.intmail.prod.int.phx2.redhat.com
 [10.5.11.22])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 103071932480;
        Mon, 20 Jul 2020 08:50:52 +0000 (UTC)
Received: from jason-ThinkPad-X1-Carbon-6th.redhat.com
 (ovpn-12-53.pek2.redhat.com [10.72.12.53])
        by smtp.corp.redhat.com (Postfix) with ESMTP id E95181001B07;
        Mon, 20 Jul 2020 08:50:45 +0000 (UTC)
From: Jason Wang <jasowang@redhat.com>
To: mst@redhat.com, jasowang@redhat.com, kvm@vger.kernel.org,
        virtualization@lists.linux-foundation.org, netdev@vger.kernel.org,
        linux-kernel@vger.kernel.org
Cc: eli@mellanox.com, lulu@redhat.com
Subject: [PATCH] vhost: vdpa: remove per device feature whitelist
Date: Mon, 20 Jul 2020 16:50:43 +0800
Message-Id: <20200720085043.16485-1-jasowang@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.84 on 10.5.11.22
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

We used to have a per device feature whitelist to filter out the
unsupported virtio features. But this seems unnecessary since:

- the main idea behind feature whitelist is to block control vq
  feature until we finalize the control virtqueue API. But the current
  vhost-vDPA uAPI is sufficient to support control virtqueue. For
  device that has hardware control virtqueue, the vDPA device driver
  can just setup the hardware virtqueue and let userspace to use
  hardware virtqueue directly. For device that doesn't have a control
  virtqueue, the vDPA device driver need to use e.g vringh to emulate
  a software control virtqueue.
- we don't do it in virtio-vDPA driver

So remove this limitation.

Signed-off-by: Jason Wang <jasowang@redhat.com>
---
 drivers/vhost/vdpa.c | 37 -------------------------------------
 1 file changed, 37 deletions(-)

```
