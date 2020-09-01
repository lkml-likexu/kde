

#### [PATCH v10 0/2] s390: virtio: let arch validate VIRTIO features
##### From: Pierre Morel <pmorel@linux.ibm.com>

```c
From patchwork Mon Aug 31 09:09:44 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Pierre Morel <pmorel@linux.ibm.com>
X-Patchwork-Id: 11745957
Return-Path: <SRS0=MvWC=CJ=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 512521667
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 31 Aug 2020 09:10:38 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 31CA7208DB
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 31 Aug 2020 09:10:38 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=ibm.com header.i=@ibm.com
 header.b="UZWmdfeQ"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728424AbgHaJKa (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 31 Aug 2020 05:10:30 -0400
Received: from mx0b-001b2d01.pphosted.com ([148.163.158.5]:28458 "EHLO
        mx0b-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1728165AbgHaJKG (ORCPT
        <rfc822;kvm@vger.kernel.org>); Mon, 31 Aug 2020 05:10:06 -0400
Received: from pps.filterd (m0127361.ppops.net [127.0.0.1])
        by mx0a-001b2d01.pphosted.com (8.16.0.42/8.16.0.42) with SMTP id
 07V91wx3132558;
        Mon, 31 Aug 2020 05:09:56 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=ibm.com;
 h=from : to : cc : subject
 : date : message-id; s=pp1;
 bh=LAaTEag7rfqT6w9lcK2QWR89UbUVGYDylsa7lF6cjIw=;
 b=UZWmdfeQoqE0x29aj2NVKcoTg1HZsmPFyABaLWS0BSdsXmf2DPiM92qUF/DVUDsFY1ht
 36BYzw2PGlwJ541c7GpHQKNy+uyfqCXOQ3t8VAjwGgPQUjc3mOnCbqBLaFtUR1ADgZEd
 RuF3pM2L2qUgIcCR3PktDwm3xuYFqF4bDZ119CBL42qaPTELKZK13T/Ri6bYx6Bpbrla
 feQ898e8ROMXbSNfMm1TiPZN5wH7HpLnZR2K1y1mgbZYcFii7NeyM9K+X0ayB6ixGu5u
 C42zUin0fpZb69J/nsdxmwuOAK8KHoFU7WpsRlLWZ10qK848+GXYhPAHL9wDoQzSkwOM sQ==
Received: from pps.reinject (localhost [127.0.0.1])
        by mx0a-001b2d01.pphosted.com with ESMTP id 338x2dgcxp-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Mon, 31 Aug 2020 05:09:56 -0400
Received: from m0127361.ppops.net (m0127361.ppops.net [127.0.0.1])
        by pps.reinject (8.16.0.36/8.16.0.36) with SMTP id 07V92Nv4133765;
        Mon, 31 Aug 2020 05:09:55 -0400
Received: from ppma04ams.nl.ibm.com (63.31.33a9.ip4.static.sl-reverse.com
 [169.51.49.99])
        by mx0a-001b2d01.pphosted.com with ESMTP id 338x2dgcw4-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Mon, 31 Aug 2020 05:09:55 -0400
Received: from pps.filterd (ppma04ams.nl.ibm.com [127.0.0.1])
        by ppma04ams.nl.ibm.com (8.16.0.42/8.16.0.42) with SMTP id
 07V8TlVg007596;
        Mon, 31 Aug 2020 09:09:51 GMT
Received: from b06cxnps3074.portsmouth.uk.ibm.com
 (d06relay09.portsmouth.uk.ibm.com [9.149.109.194])
        by ppma04ams.nl.ibm.com with ESMTP id 337en81yac-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Mon, 31 Aug 2020 09:09:51 +0000
Received: from d06av26.portsmouth.uk.ibm.com (d06av26.portsmouth.uk.ibm.com
 [9.149.105.62])
        by b06cxnps3074.portsmouth.uk.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id 07V99mDt29032762
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Mon, 31 Aug 2020 09:09:48 GMT
Received: from d06av26.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 24C4EAE051;
        Mon, 31 Aug 2020 09:09:48 +0000 (GMT)
Received: from d06av26.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 6D51DAE045;
        Mon, 31 Aug 2020 09:09:47 +0000 (GMT)
Received: from oc3016276355.ibm.com (unknown [9.145.40.55])
        by d06av26.portsmouth.uk.ibm.com (Postfix) with ESMTP;
        Mon, 31 Aug 2020 09:09:47 +0000 (GMT)
From: Pierre Morel <pmorel@linux.ibm.com>
To: linux-kernel@vger.kernel.org
Cc: pasic@linux.ibm.com, borntraeger@de.ibm.com, frankja@linux.ibm.com,
        mst@redhat.com, jasowang@redhat.com, cohuck@redhat.com,
        kvm@vger.kernel.org, linux-s390@vger.kernel.org,
        virtualization@lists.linux-foundation.org, thomas.lendacky@amd.com,
        david@gibson.dropbear.id.au, linuxram@us.ibm.com,
        hca@linux.ibm.com, gor@linux.ibm.com
Subject: [PATCH v10 0/2] s390: virtio: let arch validate VIRTIO features
Date: Mon, 31 Aug 2020 11:09:44 +0200
Message-Id: <1598864986-13875-1-git-send-email-pmorel@linux.ibm.com>
X-Mailer: git-send-email 1.8.3.1
X-TM-AS-GCONF: 00
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.235,18.0.687
 definitions=2020-08-31_01:2020-08-28,2020-08-31 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 malwarescore=0 clxscore=1015
 suspectscore=1 bulkscore=0 spamscore=0 adultscore=0 priorityscore=1501
 lowpriorityscore=0 mlxlogscore=999 mlxscore=0 phishscore=0 impostorscore=0
 classifier=spam adjust=0 reason=mlx scancount=1 engine=8.12.0-2006250000
 definitions=main-2008310051
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Hi all,

The goal of the series is to give a chance to the architecture
to validate VIRTIO device features.

The tests are back to virtio_finalize_features.

No more argument for the architecture callback which only reports
if the architecture needs guest memory access restrictions for
VIRTIO.


I renamed the callback to arch_has_restricted_virtio_memory_access,
and the config option to ARCH_HAS_RESTRICTED_VIRTIO_MEMORY_ACCESS.

Regards,
Pierre

Pierre Morel (2):
  virtio: let arch advertise guest's memory access restrictions
  s390: virtio: PV needs VIRTIO I/O device protection

 arch/s390/Kconfig             |  1 +
 arch/s390/mm/init.c           | 10 ++++++++++
 drivers/virtio/Kconfig        |  6 ++++++
 drivers/virtio/virtio.c       | 15 +++++++++++++++
 include/linux/virtio_config.h |  9 +++++++++
 5 files changed, 41 insertions(+)
```
#### [PATCH v1 0/3] s390x: css: adapting the I/O tests for PV
##### From: Pierre Morel <pmorel@linux.ibm.com>

```c
From patchwork Mon Aug 31 12:05:30 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Pierre Morel <pmorel@linux.ibm.com>
X-Patchwork-Id: 11746259
Return-Path: <SRS0=MvWC=CJ=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 0F46E1575
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 31 Aug 2020 12:05:50 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id E2FFA2083E
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 31 Aug 2020 12:05:49 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=ibm.com header.i=@ibm.com
 header.b="JZ/hnNYj"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726121AbgHaMFo (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 31 Aug 2020 08:05:44 -0400
Received: from mx0b-001b2d01.pphosted.com ([148.163.158.5]:48770 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S1726144AbgHaMFl (ORCPT
        <rfc822;kvm@vger.kernel.org>); Mon, 31 Aug 2020 08:05:41 -0400
Received: from pps.filterd (m0098416.ppops.net [127.0.0.1])
        by mx0b-001b2d01.pphosted.com (8.16.0.42/8.16.0.42) with SMTP id
 07VC2aan026056;
        Mon, 31 Aug 2020 08:05:39 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=ibm.com;
 h=from : to : cc : subject
 : date : message-id; s=pp1;
 bh=4If8ZgKPJFBluX6ZF0t25L6SeQXRx/kll/QQACySqwE=;
 b=JZ/hnNYjVtZX7wTDTClcNmzD6DoIihYGzodZcIZZwcGsRzV95/GOGtDMeyXUYRbtgBf/
 ivh5wjkNWkt6rfvBrN3pMGVBXVW0ykIF8mDRbTlLDEsEWz4ZUdTMZOFucufJ8dl7OTx7
 8n1ENTZMaOBFNTtsbEFqmzxcXYfcBseLaM99TDtSSYHRPqkuOxHlDjAJZN2Y1KYwiYfm
 s9BsABKeP+4H7GnfHDbx71pUCrizbKmNbXLtOhf7iH6KvBuymU+OFH2frFMa+asyJW+x
 UXLlRXz868pzefi5O5Lh0LIpRyhsGVq37DgAj68P6lOCog9YXuNOaooiE/bL6HgBDXYu Mw==
Received: from pps.reinject (localhost [127.0.0.1])
        by mx0b-001b2d01.pphosted.com with ESMTP id 3390txg47b-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Mon, 31 Aug 2020 08:05:39 -0400
Received: from m0098416.ppops.net (m0098416.ppops.net [127.0.0.1])
        by pps.reinject (8.16.0.36/8.16.0.36) with SMTP id 07VC5NM4033284;
        Mon, 31 Aug 2020 08:05:39 -0400
Received: from ppma04ams.nl.ibm.com (63.31.33a9.ip4.static.sl-reverse.com
 [169.51.49.99])
        by mx0b-001b2d01.pphosted.com with ESMTP id 3390txg46k-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Mon, 31 Aug 2020 08:05:39 -0400
Received: from pps.filterd (ppma04ams.nl.ibm.com [127.0.0.1])
        by ppma04ams.nl.ibm.com (8.16.0.42/8.16.0.42) with SMTP id
 07VBvYgG017549;
        Mon, 31 Aug 2020 12:05:37 GMT
Received: from b06avi18626390.portsmouth.uk.ibm.com
 (b06avi18626390.portsmouth.uk.ibm.com [9.149.26.192])
        by ppma04ams.nl.ibm.com with ESMTP id 337en8246k-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Mon, 31 Aug 2020 12:05:37 +0000
Received: from b06wcsmtp001.portsmouth.uk.ibm.com
 (b06wcsmtp001.portsmouth.uk.ibm.com [9.149.105.160])
        by b06avi18626390.portsmouth.uk.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id 07VC43T358589658
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Mon, 31 Aug 2020 12:04:03 GMT
Received: from b06wcsmtp001.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id D36E8A4054;
        Mon, 31 Aug 2020 12:05:34 +0000 (GMT)
Received: from b06wcsmtp001.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 8EBDDA405C;
        Mon, 31 Aug 2020 12:05:34 +0000 (GMT)
Received: from oc3016276355.ibm.com (unknown [9.145.160.216])
        by b06wcsmtp001.portsmouth.uk.ibm.com (Postfix) with ESMTP;
        Mon, 31 Aug 2020 12:05:34 +0000 (GMT)
From: Pierre Morel <pmorel@linux.ibm.com>
To: kvm@vger.kernel.org
Cc: linux-s390@vger.kernel.org, frankja@linux.ibm.com,
        david@redhat.com, thuth@redhat.com, cohuck@redhat.com
Subject: [PATCH v1 0/3] s390x: css: adapting the I/O tests for PV
Date: Mon, 31 Aug 2020 14:05:30 +0200
Message-Id: <1598875533-19947-1-git-send-email-pmorel@linux.ibm.com>
X-Mailer: git-send-email 1.8.3.1
X-TM-AS-GCONF: 00
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.235,18.0.687
 definitions=2020-08-31_04:2020-08-31,2020-08-31 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 mlxscore=0 suspectscore=3
 bulkscore=0 phishscore=0 mlxlogscore=873 spamscore=0 clxscore=1015
 impostorscore=0 priorityscore=1501 adultscore=0 lowpriorityscore=0
 malwarescore=0 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.12.0-2006250000 definitions=main-2008310066
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

To adapt the test for PV we need to share the I/O memory with the host.

To do so we:
- implement the share/unshare ultravisor code.
- implement dedicated allocation routine which make sure that
  - the I/O memory is on dedicated pages
  - the I/O memory is shared if the guest is run under PV
- replace the start_single_ccw() by ccw_alloc() and start the
  start_ccw1_chain() directly from the test function.
  This allows to correctly free the I/O memory after the interruption.

Best regards,
Pierre

Pierre Morel (3):
  s390x: pv: implement routine to share/unshare memory
  s390: define UV compatible I/O allocation
  s390x: css: pv: css test adaptation for PV

 lib/s390x/asm/uv.h    | 33 +++++++++++++++++++++++++++
 lib/s390x/css.h       |  3 +--
 lib/s390x/css_lib.c   | 28 +++++++----------------
 lib/s390x/malloc_io.c | 53 +++++++++++++++++++++++++++++++++++++++++++
 lib/s390x/malloc_io.h | 14 ++++++++++++
 s390x/Makefile        |  1 +
 s390x/css.c           | 35 +++++++++++++++++++---------
 7 files changed, 134 insertions(+), 33 deletions(-)
 create mode 100644 lib/s390x/malloc_io.c
 create mode 100644 lib/s390x/malloc_io.h
```
#### [PATCH v14 00/18] KVM RISC-V Support
##### From: Anup Patel <anup.patel@wdc.com>

```c
From patchwork Mon Aug 31 12:25:20 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Anup Patel <Anup.Patel@wdc.com>
X-Patchwork-Id: 11746283
Return-Path: <SRS0=MvWC=CJ=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id AF58313B1
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 31 Aug 2020 12:26:52 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 8BBDA207DA
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 31 Aug 2020 12:26:52 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=fail reason="signature verification failed" (2048-bit key)
 header.d=wdc.com header.i=@wdc.com header.b="RW1+bdPJ";
	dkim=pass (1024-bit key) header.d=sharedspace.onmicrosoft.com
 header.i=@sharedspace.onmicrosoft.com header.b="DZkOHfBC"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727066AbgHaM0k (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 31 Aug 2020 08:26:40 -0400
Received: from esa5.hgst.iphmx.com ([216.71.153.144]:54712 "EHLO
        esa5.hgst.iphmx.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726927AbgHaM0Q (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 31 Aug 2020 08:26:16 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=simple/simple;
  d=wdc.com; i=@wdc.com; q=dns/txt; s=dkim.wdc.com;
  t=1598876777; x=1630412777;
  h=from:to:cc:subject:date:message-id:
   content-transfer-encoding:mime-version;
  bh=/l6V7IghWq9bV8DqtloXg0w7ww8jZzp9oowLpnw3pKk=;
  b=RW1+bdPJR4MueFuNYfIylTJjA+etzQMzrvZRopmMNUghWOK+fjeB+NwK
   ruzB7zvEVXz84Wel7TweeUVXWgXRkM1AYSQBFRIlqR0l1ky02OdaEV35u
   CmvfXG4oydWH7FhgtwQ2NnzUyDsuzHQisfBzZN23P7OlwNxw5QZaYYK7Z
   dBmtxcfF7Y4rJ/Z9o2tyJ6CJIvRBkRUMXA0fxTZxqihehF0SpWNY5Yfbi
   e70QwFp645yCQMwqFXeaL3/uqoDjBgSRORAG3K0urNQZCup/NTnhXv7An
   BWB8bDGqar6VVM+w+r1JMSAPndjFdquKnAvGH76cjLsr6QFh2jzPJoxlI
   A==;
IronPort-SDR: 
 T/BYtcTyw7UwH6KiYl71Na+BtnCAPp4G+QwwQYR1Ke0PXrLsRGcVoWZtYgutAGeidjpUUE5DFU
 OfbJMjiSlsbGjsenvDOYEHphjyrUWpxnV45WCyx7i9rhpg1FqBUl0S9KyTvdiILD1rtvyuDITW
 81mjUb7wkFr2Q8u6xWwlboCXpfj9W+LRDJeUA6cY7L7xxGoUX7Hm20CXLfKVhCzZ/qKT3dr3Hc
 Ihubj90SwqQJTd17orDG+uKQLK4EOMcA63ZuuJHg6caMKJ+VlWDhXSPqrStkXe2uHzDN0vwZ92
 GuE=
X-IronPort-AV: E=Sophos;i="5.76,375,1592841600";
   d="scan'208";a="146216472"
Received: from mail-mw2nam10lp2109.outbound.protection.outlook.com (HELO
 NAM10-MW2-obe.outbound.protection.outlook.com) ([104.47.55.109])
  by ob1.hgst.iphmx.com with ESMTP; 31 Aug 2020 20:26:16 +0800
ARC-Seal: i=1; a=rsa-sha256; s=arcselector9901; d=microsoft.com; cv=none;
 b=JTJXEKu0+7UyziP0Mz1Ib8oQvjOM+a/vIywjOYz8mlBdN69Vk6ZhQFYu2eYSBfBNzD0XWe4kYXeMyeWyvcDA+In9bgdIbh61dYrq8W3nuNjf+8usqWNDH8MgIWqMXEwUQswoLQfyc25+MtI4U/c9l917VCVgrp1nFBRs2EqUCQG8U1MOM24dj7C5Qoaj3eSypsPoj65mgWdtugOYQhfij2M8j43AxitU4sCX7krSULhbpasc1xNfsiI//SQenBA9YjPs1LsRnioL4xeRusq2zysAaXtbg2FIj2rXVnmD75DFqV+A5rVw272mnxJCKOE2YkjQbtkSo5CC4gU8KYK+KA==
ARC-Message-Signature: i=1; a=rsa-sha256; c=relaxed/relaxed; d=microsoft.com;
 s=arcselector9901;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=4cvoeOZthn19X0Ny1hOZClSG0+XGKoTvF5rCPHacwqc=;
 b=g4WOGdXWK/nuaRzlRZCh7Sx8Br7cndC9R+rAOtgIsmfqyGXkAnIYrsh270bsqMcNYsKAMl8LJ+WQDntsV0cXgzB5toeoOi9opSukdNiki1ajeu9OqIcYqUpaKp1lTfO2IPScvz5q/q69J2SB781e8fhLoy18B51T0a3ShIilql4KauOyRjwwt8pWfF9yrBN1BdB5eVdYZTfNI6EX69WgyIiG8Ew/L8CU3oidQMbt1HNhhj5SrevitRbVrN2ddcKMKCpE6JFpQJqCOPNvv6NqPDejSOybr1cZ1KwSYf6ZUOFtDnCzysMXIUs6/Hr0ueus09MK474St8uMXwhCW8an4Q==
ARC-Authentication-Results: i=1; mx.microsoft.com 1; spf=pass
 smtp.mailfrom=wdc.com; dmarc=pass action=none header.from=wdc.com; dkim=pass
 header.d=wdc.com; arc=none
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
 d=sharedspace.onmicrosoft.com; s=selector2-sharedspace-onmicrosoft-com;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=4cvoeOZthn19X0Ny1hOZClSG0+XGKoTvF5rCPHacwqc=;
 b=DZkOHfBCT1O2k9Q/tGptJ89lrdHcjbItvu9J6QrEOFE85DEItnTzBXvxwSZcAphbT6a33ZKEYKwlOkGji9f1UW71xxLlqsEipgHoLATbxnjOfIN6j9EDq7LmEoridXZDbz65ClBiDNuJnrVsgvzbV0lqT2uNZ3yj1fKUx7mAk70=
Authentication-Results: dabbelt.com; dkim=none (message not signed)
 header.d=none;dabbelt.com; dmarc=none action=none header.from=wdc.com;
Received: from DM6PR04MB6201.namprd04.prod.outlook.com (2603:10b6:5:127::32)
 by DM6PR04MB5386.namprd04.prod.outlook.com (2603:10b6:5:106::27) with
 Microsoft SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.3326.24; Mon, 31 Aug
 2020 12:26:13 +0000
Received: from DM6PR04MB6201.namprd04.prod.outlook.com
 ([fe80::607a:44ed:1477:83e]) by DM6PR04MB6201.namprd04.prod.outlook.com
 ([fe80::607a:44ed:1477:83e%7]) with mapi id 15.20.3326.025; Mon, 31 Aug 2020
 12:26:13 +0000
From: Anup Patel <anup.patel@wdc.com>
To: Palmer Dabbelt <palmer@dabbelt.com>,
        Palmer Dabbelt <palmerdabbelt@google.com>,
        Paul Walmsley <paul.walmsley@sifive.com>,
        Albert Ou <aou@eecs.berkeley.edu>,
        Paolo Bonzini <pbonzini@redhat.com>
Cc: Alexander Graf <graf@amazon.com>,
        Atish Patra <atish.patra@wdc.com>,
        Alistair Francis <Alistair.Francis@wdc.com>,
        Damien Le Moal <damien.lemoal@wdc.com>,
        Anup Patel <anup@brainfault.org>, kvm@vger.kernel.org,
        kvm-riscv@lists.infradead.org, linux-riscv@lists.infradead.org,
        linux-kernel@vger.kernel.org, Anup Patel <anup.patel@wdc.com>
Subject: [PATCH v14 00/18] KVM RISC-V Support
Date: Mon, 31 Aug 2020 17:55:20 +0530
Message-Id: <20200831122538.335889-1-anup.patel@wdc.com>
X-Mailer: git-send-email 2.25.1
X-ClientProxiedBy: BM1PR0101CA0038.INDPRD01.PROD.OUTLOOK.COM
 (2603:1096:b00:1a::24) To DM6PR04MB6201.namprd04.prod.outlook.com
 (2603:10b6:5:127::32)
MIME-Version: 1.0
X-MS-Exchange-MessageSentRepresentingType: 1
Received: from 255.255.255.255 (255.255.255.255) by
 BM1PR0101CA0038.INDPRD01.PROD.OUTLOOK.COM (2603:1096:b00:1a::24) with
 Microsoft SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.3326.19 via Frontend
 Transport; Mon, 31 Aug 2020 12:26:08 +0000
X-Mailer: git-send-email 2.25.1
X-Originating-IP: [103.15.57.192]
X-MS-PublicTrafficType: Email
X-MS-Office365-Filtering-HT: Tenant
X-MS-Office365-Filtering-Correlation-Id: 58df00fc-5e4e-474d-e0f4-08d84da90c8a
X-MS-TrafficTypeDiagnostic: DM6PR04MB5386:
X-MS-Exchange-Transport-Forked: True
X-Microsoft-Antispam-PRVS: 
 <DM6PR04MB5386C2211F5E38AA4A860AB18D510@DM6PR04MB5386.namprd04.prod.outlook.com>
WDCIPOUTBOUND: EOP-TRUE
X-MS-Oob-TLC-OOBClassifiers: OLM:79;
X-MS-Exchange-SenderADCheck: 1
X-Microsoft-Antispam: BCL:0;
X-Microsoft-Antispam-Message-Info: 
 5bSVl7Y/7vEKaVuVHzDElOCWLcwKq6D7IH4fMfFL/g8gen+QxJNyv6VOBXPE8iUBLDV+zNMmamJzmhN9c868dn2eMS+UzV6Of5aLwiY7HfJvJCq+Uug8RA3le5d/8+d1At/IF85rFA2KUkZjxjO1brj+mz3Si/WSXb4pGDnF6cjjeHvLkNKpEM64lN4LLIWr3k4a+Um278agk1yYp1zc14iMl+JGbqvjDUwgs7DCFobLcHEY0oEE1D5Ok6UxtnPC23ERPGyXR9nnwtyIN1JOvqLUSM7q5hZKcFBPsfqHOvjPH4H8zgiTh4kLg6UtkL9YdlDHXa3e78MbonMCrcUmGh8DRsRDnXdvgjQvrRh3v8C5ifS0JKm7bh74yhjESN9Ml10nvq4f+oFiCjiOH7toiMcAG9KYx2lL8HAEbeYwjZyhtKjhUXzUau8twWyiL32h+t+GlAp/g4gTJMrrUf5wdg==
X-Forefront-Antispam-Report: 
 CIP:255.255.255.255;CTRY:;LANG:en;SCL:1;SRV:;IPV:NLI;SFV:NSPM;H:DM6PR04MB6201.namprd04.prod.outlook.com;PTR:;CAT:NONE;SFS:(4636009)(376002)(346002)(39860400002)(396003)(136003)(366004)(30864003)(6486002)(478600001)(966005)(110136005)(54906003)(66556008)(83380400001)(66476007)(5660300002)(6666004)(16576012)(316002)(186003)(66946007)(26005)(2906002)(44832011)(8936002)(4326008)(36756003)(956004)(2616005)(52116002)(1076003)(8676002)(86362001)(7416002)(42580500001);DIR:OUT;SFP:1102;
X-MS-Exchange-AntiSpam-MessageData: 
 pEnVRgDbbzR6FHZoGv6F/ah1cq+9EVfcXtQfjXbyBS8Y3/uD7c7ZDVe3kdiBLaAI+krIx+8QxO1PJkTzmCQ577GPrIthwKo5v2o3+e+07Os2CVm7UnBcMqfhO7oIsDqwpnzzw6DMQbupy+n5GkcvWqPsoKhwEqrBFvkWep8LXDHyew6jfsLElSd5ljfMxRbz5ZZgtErxtBs7F4+4B1WXxg8C22ww6qz485dLZjGTE82ta6H2+dwkfMNrTHjik9t3nCdSIDD+MgeV1aWKb2gzHaVhZcvp2zNt3cVALY0nIfOxQN0VXeEv8vhbsViAi6kI7PLAUoJtV0pr/2Oy6C27cBBiUxsBZfVVxsYFGe9Ax7REzmxuV8SsXJ7U8n8FQ3vmudVJKX12rnsAWoJIk0fRx/XCoQuHnnohayt00ahLGDnFpm5iEuTPsiGSXqBrbkvu7B9L3wLTk7ECGGrERZ+bulfA+jI0cHYDwlF18+IxLIk3n3fy7L1F4nnfc0Uwv1HPkD0mVy1G+Bc8ybekoK4O1fIQJTOCwPF95TZfKQVDnrPAnl+ZhmHPkYpjk339mCu9VPQweOK3Kf/lu8FWPPSbUfSmk+WIrUYFCxd08yGEiOLmJ7eYWcBflExZAC/oB6rnEsvvkrA+RfOcdtGdY1bSCw==
X-OriginatorOrg: wdc.com
X-MS-Exchange-CrossTenant-Network-Message-Id: 
 58df00fc-5e4e-474d-e0f4-08d84da90c8a
X-MS-Exchange-CrossTenant-AuthSource: DM6PR04MB6201.namprd04.prod.outlook.com
X-MS-Exchange-CrossTenant-AuthAs: Internal
X-MS-Exchange-CrossTenant-OriginalArrivalTime: 31 Aug 2020 12:26:13.2612
 (UTC)
X-MS-Exchange-CrossTenant-FromEntityHeader: Hosted
X-MS-Exchange-CrossTenant-Id: b61c8803-16f3-4c35-9b17-6f65f441df86
X-MS-Exchange-CrossTenant-MailboxType: HOSTED
X-MS-Exchange-CrossTenant-UserPrincipalName: 
 ZrI68Vx7dl5TBqg/ZxeJsA8Akp/wRBqJVKNnm+NIoSUftnuNlZMbbLDtYotcx+ifA8xYiMCtOB+3/UUFmu7qqA==
X-MS-Exchange-Transport-CrossTenantHeadersStamped: DM6PR04MB5386
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This series adds initial KVM RISC-V support. Currently, we are able to boot
Linux on RV64/RV32 Guest with multiple VCPUs.

Key aspects of KVM RISC-V added by this series are:
1. No RISC-V specific KVM IOCTL
2. Minimal possible KVM world-switch which touches only GPRs and few CSRs
3. Both RV64 and RV32 host supported
4. Full Guest/VM switch is done via vcpu_get/vcpu_put infrastructure
5. KVM ONE_REG interface for VCPU register access from user-space
6. PLIC emulation is done in user-space
7. Timer and IPI emuation is done in-kernel
8. Both Sv39x4 and Sv48x4 supported for RV64 host
9. MMU notifiers supported
10. Generic dirtylog supported
11. FP lazy save/restore supported
12. SBI v0.1 emulation for KVM Guest available
13. Forward unhandled SBI calls to KVM userspace
14. Hugepage support for Guest/VM
15. IOEVENTFD support for Vhost

Here's a brief TODO list which we will work upon after this series:
1. SBI v0.2 emulation in-kernel
2. SBI v0.2 hart state management emulation in-kernel
3. In-kernel PLIC emulation
4. ..... and more .....

This series can be found in riscv_kvm_v14 branch at:
https//github.com/avpatel/linux.git

Our work-in-progress KVMTOOL RISC-V port can be found in riscv_v4 branch
at: https//github.com/avpatel/kvmtool.git

The QEMU RISC-V hypervisor emulation is done by Alistair and is available
in mainline/anup/riscv-hyp-ext-v0.6.1 branch at:
https://github.com/kvm-riscv/qemu.git

To play around with KVM RISC-V, refer KVM RISC-V wiki at:
https://github.com/kvm-riscv/howto/wiki
https://github.com/kvm-riscv/howto/wiki/KVM-RISCV64-on-QEMU
https://github.com/kvm-riscv/howto/wiki/KVM-RISCV64-on-Spike

Changes since v13:
 - Rebased on Linux-5.9-rc3
 - Fixed kvm_riscv_vcpu_set_reg_csr() for SIP updation in PATCH5
 - Fixed instruction length computation in PATCH7
 - Added ioeventfd support in PATCH7
 - Ensure HSTATUS.SPVP is set to correct value before using HLV/HSV
   intructions in PATCH7
 - Fixed stage2_map_page() to set PTE 'A' and 'D' bits correctly
   in PATCH10
 - Added stage2 dirty page logging in PATCH10
 - Allow KVM user-space to SET/GET SCOUNTER CSR in PATCH5
 - Save/restore SCOUNTEREN in PATCH6
 - Reduced quite a few instructions for __kvm_riscv_switch_to() by
   using CSR swap instruction in PATCH6
 - Detect and use Sv48x4 when available in PATCH10

Changes since v12:
 - Rebased patches on Linux-5.8-rc4
 - By default enable all counters in HCOUNTEREN
 - RISC-V H-Extension v0.6.1 spec support

Changes since v11:
 - Rebased patches on Linux-5.7-rc3
 - Fixed typo in typecast of stage2_map_size define
 - Introduced struct kvm_cpu_trap to represent trap details and
   use it as function parameter wherever applicable
 - Pass memslot to kvm_riscv_stage2_map() for supporing dirty page
   logging in future
 - RISC-V H-Extension v0.6 spec support
 - Send-out first three patches as separate series so that it can
   be taken by Palmer for Linux RISC-V

Changes since v10:
 - Rebased patches on Linux-5.6-rc5
 - Reduce RISCV_ISA_EXT_MAX from 256 to 64
 - Separate PATCH for removing N-extension related defines
 - Added comments as requested by Palmer
 - Fixed HIDELEG CSR programming

Changes since v9:
 - Rebased patches on Linux-5.5-rc3
 - Squash PATCH19 and PATCH20 into PATCH5
 - Squash PATCH18 into PATCH11
 - Squash PATCH17 into PATCH16
 - Added ONE_REG interface for VCPU timer in PATCH13
 - Use HTIMEDELTA for VCPU timer in PATCH13
 - Updated KVM RISC-V mailing list in MAINTAINERS entry
 - Update KVM kconfig option to depend on RISCV_SBI and MMU
 - Check for SBI v0.2 and SBI v0.2 RFENCE extension at boot-time
 - Use SBI v0.2 RFENCE extension in VMID implementation
 - Use SBI v0.2 RFENCE extension in Stage2 MMU implementation
 - Use SBI v0.2 RFENCE extension in SBI implementation
 - Moved to RISC-V Hypervisor v0.5 draft spec
 - Updated Documentation/virt/kvm/api.txt for timer ONE_REG interface

Changes since v8:
 - Rebased series on Linux-5.4-rc3 and Atish's SBI v0.2 patches
 - Use HRTIMER_MODE_REL instead of HRTIMER_MODE_ABS in timer emulation
 - Fixed kvm_riscv_stage2_map() to handle hugepages
 - Added patch to forward unhandled SBI calls to user-space
 - Added patch for iterative/recursive stage2 page table programming
 - Added patch to remove per-CPU vsip_shadow variable
 - Added patch to fix race-condition in kvm_riscv_vcpu_sync_interrupts()

Changes since v7:
 - Rebased series on Linux-5.4-rc1 and Atish's SBI v0.2 patches
 - Removed PATCH1, PATCH3, and PATCH20 because these already merged
 - Use kernel doc style comments for ISA bitmap functions
 - Don't parse X, Y, and Z extension in riscv_fill_hwcap() because it will
   be added in-future
 - Mark KVM RISC-V kconfig option as EXPERIMENTAL
 - Typo fix in commit description of PATCH6 of v7 series
 - Use separate structs for CORE and CSR registers of ONE_REG interface
 - Explicitly include asm/sbi.h in kvm/vcpu_sbi.c
 - Removed implicit switch-case fall-through in kvm_riscv_vcpu_exit()
 - No need to set VSSTATUS.MXR bit in kvm_riscv_vcpu_unpriv_read()
 - Removed register for instruction length in kvm_riscv_vcpu_unpriv_read()
 - Added defines for checking/decoding instruction length
 - Added separate patch to forward unhandled SBI calls to userspace tool

Changes since v6:
 - Rebased patches on Linux-5.3-rc7
 - Added "return_handled" in struct kvm_mmio_decode to ensure that
   kvm_riscv_vcpu_mmio_return() updates SEPC only once
 - Removed trap_stval parameter from kvm_riscv_vcpu_unpriv_read()
 - Updated git repo URL in MAINTAINERS entry

Changes since v5:
 - Renamed KVM_REG_RISCV_CONFIG_TIMEBASE register to
   KVM_REG_RISCV_CONFIG_TBFREQ register in ONE_REG interface
 - Update SPEC in kvm_riscv_vcpu_mmio_return() for MMIO exits
 - Use switch case instead of illegal instruction opcode table for simplicity
 - Improve comments in stage2_remote_tlb_flush() for a potential remote TLB
  flush optimization
 - Handle all unsupported SBI calls in default case of
   kvm_riscv_vcpu_sbi_ecall() function
 - Fixed kvm_riscv_vcpu_sync_interrupts() for software interrupts
 - Improved unprivilege reads to handle traps due to Guest stage1 page table
 - Added separate patch to document RISC-V specific things in
   Documentation/virt/kvm/api.txt

Changes since v4:
 - Rebased patches on Linux-5.3-rc5
 - Added Paolo's Acked-by and Reviewed-by
 - Updated mailing list in MAINTAINERS entry

Changes since v3:
 - Moved patch for ISA bitmap from KVM prep series to this series
 - Make vsip_shadow as run-time percpu variable instead of compile-time
 - Flush Guest TLBs on all Host CPUs whenever we run-out of VMIDs

Changes since v2:
 - Removed references of KVM_REQ_IRQ_PENDING from all patches
 - Use kvm->srcu within in-kernel KVM run loop
 - Added percpu vsip_shadow to track last value programmed in VSIP CSR
 - Added comments about irqs_pending and irqs_pending_mask
 - Used kvm_arch_vcpu_runnable() in-place-of kvm_riscv_vcpu_has_interrupt()
   in system_opcode_insn()
 - Removed unwanted smp_wmb() in kvm_riscv_stage2_vmid_update()
 - Use kvm_flush_remote_tlbs() in kvm_riscv_stage2_vmid_update()
 - Use READ_ONCE() in kvm_riscv_stage2_update_hgatp() for vmid

Changes since v1:
 - Fixed compile errors in building KVM RISC-V as module
 - Removed unused kvm_riscv_halt_guest() and kvm_riscv_resume_guest()
 - Set KVM_CAP_SYNC_MMU capability only after MMU notifiers are implemented
 - Made vmid_version as unsigned long instead of atomic
 - Renamed KVM_REQ_UPDATE_PGTBL to KVM_REQ_UPDATE_HGATP
 - Renamed kvm_riscv_stage2_update_pgtbl() to kvm_riscv_stage2_update_hgatp()
 - Configure HIDELEG and HEDELEG in kvm_arch_hardware_enable()
 - Updated ONE_REG interface for CSR access to user-space
 - Removed irqs_pending_lock and use atomic bitops instead
 - Added separate patch for FP ONE_REG interface
 - Added separate patch for updating MAINTAINERS file

Anup Patel (14):
  RISC-V: Add hypervisor extension related CSR defines
  RISC-V: Add initial skeletal KVM support
  RISC-V: KVM: Implement VCPU create, init and destroy functions
  RISC-V: KVM: Implement VCPU interrupts and requests handling
  RISC-V: KVM: Implement KVM_GET_ONE_REG/KVM_SET_ONE_REG ioctls
  RISC-V: KVM: Implement VCPU world-switch
  RISC-V: KVM: Handle MMIO exits for VCPU
  RISC-V: KVM: Handle WFI exits for VCPU
  RISC-V: KVM: Implement VMID allocator
  RISC-V: KVM: Implement stage2 page table programming
  RISC-V: KVM: Implement MMU notifiers
  RISC-V: KVM: Document RISC-V specific parts of KVM API
  RISC-V: KVM: Add MAINTAINERS entry
  RISC-V: Enable KVM for RV64 and RV32

Atish Patra (4):
  RISC-V: KVM: Add timer functionality
  RISC-V: KVM: FP lazy save/restore
  RISC-V: KVM: Implement ONE REG interface for FP registers
  RISC-V: KVM: Add SBI v0.1 support

 Documentation/virt/kvm/api.rst          |  193 ++++-
 MAINTAINERS                             |   11 +
 arch/riscv/Kconfig                      |    2 +
 arch/riscv/Makefile                     |    2 +
 arch/riscv/configs/defconfig            |    3 +
 arch/riscv/configs/rv32_defconfig       |    3 +
 arch/riscv/include/asm/csr.h            |   89 ++
 arch/riscv/include/asm/kvm_host.h       |  278 +++++++
 arch/riscv/include/asm/kvm_types.h      |    7 +
 arch/riscv/include/asm/kvm_vcpu_timer.h |   44 +
 arch/riscv/include/asm/pgtable-bits.h   |    1 +
 arch/riscv/include/uapi/asm/kvm.h       |  128 +++
 arch/riscv/kernel/asm-offsets.c         |  156 ++++
 arch/riscv/kvm/Kconfig                  |   36 +
 arch/riscv/kvm/Makefile                 |   15 +
 arch/riscv/kvm/main.c                   |  118 +++
 arch/riscv/kvm/mmu.c                    |  857 +++++++++++++++++++
 arch/riscv/kvm/tlb.S                    |   74 ++
 arch/riscv/kvm/vcpu.c                   | 1012 +++++++++++++++++++++++
 arch/riscv/kvm/vcpu_exit.c              |  701 ++++++++++++++++
 arch/riscv/kvm/vcpu_sbi.c               |  173 ++++
 arch/riscv/kvm/vcpu_switch.S            |  400 +++++++++
 arch/riscv/kvm/vcpu_timer.c             |  225 +++++
 arch/riscv/kvm/vm.c                     |   81 ++
 arch/riscv/kvm/vmid.c                   |  120 +++
 drivers/clocksource/timer-riscv.c       |    8 +
 include/clocksource/timer-riscv.h       |   16 +
 include/uapi/linux/kvm.h                |    8 +
 28 files changed, 4752 insertions(+), 9 deletions(-)
 create mode 100644 arch/riscv/include/asm/kvm_host.h
 create mode 100644 arch/riscv/include/asm/kvm_types.h
 create mode 100644 arch/riscv/include/asm/kvm_vcpu_timer.h
 create mode 100644 arch/riscv/include/uapi/asm/kvm.h
 create mode 100644 arch/riscv/kvm/Kconfig
 create mode 100644 arch/riscv/kvm/Makefile
 create mode 100644 arch/riscv/kvm/main.c
 create mode 100644 arch/riscv/kvm/mmu.c
 create mode 100644 arch/riscv/kvm/tlb.S
 create mode 100644 arch/riscv/kvm/vcpu.c
 create mode 100644 arch/riscv/kvm/vcpu_exit.c
 create mode 100644 arch/riscv/kvm/vcpu_sbi.c
 create mode 100644 arch/riscv/kvm/vcpu_switch.S
 create mode 100644 arch/riscv/kvm/vcpu_timer.c
 create mode 100644 arch/riscv/kvm/vm.c
 create mode 100644 arch/riscv/kvm/vmid.c
 create mode 100644 include/clocksource/timer-riscv.h
```
#### [PATCH v14 00/17] KVM RISC-V Support
##### From: Anup Patel <anup.patel@wdc.com>

```c
From patchwork Mon Aug 31 12:29:58 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Anup Patel <Anup.Patel@wdc.com>
X-Patchwork-Id: 11746321
Return-Path: <SRS0=MvWC=CJ=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 3721713A4
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 31 Aug 2020 12:40:36 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 1486820782
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 31 Aug 2020 12:40:36 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=fail reason="signature verification failed" (2048-bit key)
 header.d=wdc.com header.i=@wdc.com header.b="bP3D546x";
	dkim=pass (1024-bit key) header.d=sharedspace.onmicrosoft.com
 header.i=@sharedspace.onmicrosoft.com header.b="RClteHMv"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727818AbgHaMkb (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 31 Aug 2020 08:40:31 -0400
Received: from esa2.hgst.iphmx.com ([68.232.143.124]:43760 "EHLO
        esa2.hgst.iphmx.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1727088AbgHaMbB (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 31 Aug 2020 08:31:01 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=simple/simple;
  d=wdc.com; i=@wdc.com; q=dns/txt; s=dkim.wdc.com;
  t=1598877079; x=1630413079;
  h=from:to:cc:subject:date:message-id:
   content-transfer-encoding:mime-version;
  bh=hacVPdlGoODrUIugH9fAKADYdTIXRWTAQKluzRGFl0A=;
  b=bP3D546xGIpgdWn4URO5ePcREav4NKs6LoGJ4s18eqxCE0fvthoB+4od
   W7eOLr2IP/McYPtND4RCG3LbAcfh/mClpcyVubq/H2WuTUV9xUwVlso9F
   KotaSjKgkLxtIiznZy4BaBmfZ7apVyzgg10ruw8jSrwLlZalV8wqFFhZ9
   Wfk73grb0Z3AnB5U52w6EHy4iMtBExMXWkCXSVNqntbc9K7/LOXc/FtKO
   J59iNFdzmGcgcH0E4a8zEC1nThtg4GresHFrjAtKCnG4kU3y/ESnnmOxV
   XPASTGDkqI4CaHdcBS1pWIsE/q0rw4BXtq1AAWhhSLpl8S/T4Z01WH9xb
   Q==;
IronPort-SDR: 
 0cRGDtmeZ1WwGGLRtyfTz8x+HpFC3H6vDpWzwKexAAH6qk/HawEGjl0q8KAvHdu03zxAh40tJ1
 QLFGXrR86si0sM6ZJU3Uqi6PfBg7wHZQFczIwPodDHzk1Q0Z2CSgqxPs96CCpD2q2kfNrke++w
 9iWafx7tCh6DS0NOTzVpQi+lW5pHmk+4839U5usZKBQkltcQdL3UWLH34lRSyzyfrbicLV6nRb
 Is3KSVi1WTz8ac2/tU3FXMOsVMJkK2c7KUeuJiIEg3iXXkMASJBTbfXSWRgNl4HH5ZbObS2ZIE
 b90=
X-IronPort-AV: E=Sophos;i="5.76,375,1592841600";
   d="scan'208";a="249473186"
Received: from mail-dm6nam12lp2174.outbound.protection.outlook.com (HELO
 NAM12-DM6-obe.outbound.protection.outlook.com) ([104.47.59.174])
  by ob1.hgst.iphmx.com with ESMTP; 31 Aug 2020 20:30:51 +0800
ARC-Seal: i=1; a=rsa-sha256; s=arcselector9901; d=microsoft.com; cv=none;
 b=dZPCEhwmnlcvIdS1Hy3TpNcTX5xQ4fblb8nv+eWck3GlHKbtNVHxElJUF0eFNkk7/y4iXXoY7gts3ewFidMG8Uf8L6lJgx/7PVPqufSWJpZO1Eta4Pjszs98own58pl5vBiyHOtLIAizg7GMVUtuCc+A2ycAsN42QDl8UMvWYUVXjrwqdqsaePmH4ANgfGT4eCvg0bdvWv+pV+OqixQkOExumOMxLZ9k3IWmLcpZFTmOfIlHzmGea/tRWsMqME7J7z+KM6juq7O64zl3yEPJo1bMwBfL4tN2IGre8mDeYFlHxnX7fOixeNRkRxPDYR2xCC0EcyaA4dksCWGA3wBLYg==
ARC-Message-Signature: i=1; a=rsa-sha256; c=relaxed/relaxed; d=microsoft.com;
 s=arcselector9901;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=JBsZEJ9IbJ9CF+yqPt1ZvZoasB/CZgFOuZ3BVD6xvFU=;
 b=N0co/wys/iyW1KaIVZ1dnoQTQJ+9wDqM2kLgpUEplRq4eDstz2XOgxHzesto+D1cAVbNZW3QNoP2ItFa3QYzCZeRLC7kfpOEJ72Bf82ZQsTAZ5k+u9UYkFcddZR5mXdVIHpoRjPUDQPjXbaAAffbeW2JK9Roa0s2RpNRoswengjvWmsOfUxAsGOXv9jnIekxqO2b50gJAJ79GNEOQxzgq9HbMsaGCSr9S6bMZhSTPMqN3Km3cmFkyCfl1Ys4KSr2jES+NSCXm8NFqaVy5VxRwyzYCGKMuFlsyMwr6MWXNfKmjy7Rel5q4CvjrZFVEui1jPDrfmNxWT55H0Grf7MNLg==
ARC-Authentication-Results: i=1; mx.microsoft.com 1; spf=pass
 smtp.mailfrom=wdc.com; dmarc=pass action=none header.from=wdc.com; dkim=pass
 header.d=wdc.com; arc=none
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
 d=sharedspace.onmicrosoft.com; s=selector2-sharedspace-onmicrosoft-com;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=JBsZEJ9IbJ9CF+yqPt1ZvZoasB/CZgFOuZ3BVD6xvFU=;
 b=RClteHMva0CwBia83gWA+nbznSj8hJMRbbeVhU4SZSBFWpV404OZDoXoRzTy8Ipisme2jFW7jweMWhDbiM1bRjIPndmrKlgF+GFfareVUFjw3JQS7rKklRn6ALci3kPBOfZEv+hpT2ehjMzeVvNdA7Afgw900jBj7jx2DbSgk+4=
Authentication-Results: dabbelt.com; dkim=none (message not signed)
 header.d=none;dabbelt.com; dmarc=none action=none header.from=wdc.com;
Received: from DM6PR04MB6201.namprd04.prod.outlook.com (2603:10b6:5:127::32)
 by DM6PR04MB6092.namprd04.prod.outlook.com (2603:10b6:5:12b::19) with
 Microsoft SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.3326.23; Mon, 31 Aug
 2020 12:30:40 +0000
Received: from DM6PR04MB6201.namprd04.prod.outlook.com
 ([fe80::607a:44ed:1477:83e]) by DM6PR04MB6201.namprd04.prod.outlook.com
 ([fe80::607a:44ed:1477:83e%7]) with mapi id 15.20.3326.025; Mon, 31 Aug 2020
 12:30:40 +0000
From: Anup Patel <anup.patel@wdc.com>
To: Palmer Dabbelt <palmer@dabbelt.com>,
        Palmer Dabbelt <palmerdabbelt@google.com>,
        Paul Walmsley <paul.walmsley@sifive.com>,
        Albert Ou <aou@eecs.berkeley.edu>,
        Paolo Bonzini <pbonzini@redhat.com>
Cc: Alexander Graf <graf@amazon.com>,
        Atish Patra <atish.patra@wdc.com>,
        Alistair Francis <Alistair.Francis@wdc.com>,
        Damien Le Moal <damien.lemoal@wdc.com>,
        Anup Patel <anup@brainfault.org>, kvm@vger.kernel.org,
        kvm-riscv@lists.infradead.org, linux-riscv@lists.infradead.org,
        linux-kernel@vger.kernel.org, Anup Patel <anup.patel@wdc.com>
Subject: [PATCH v14 00/17] KVM RISC-V Support
Date: Mon, 31 Aug 2020 17:59:58 +0530
Message-Id: <20200831123015.336047-1-anup.patel@wdc.com>
X-Mailer: git-send-email 2.25.1
X-ClientProxiedBy: BM1PR0101CA0046.INDPRD01.PROD.OUTLOOK.COM
 (2603:1096:b00:1a::32) To DM6PR04MB6201.namprd04.prod.outlook.com
 (2603:10b6:5:127::32)
MIME-Version: 1.0
X-MS-Exchange-MessageSentRepresentingType: 1
Received: from 255.255.255.255 (255.255.255.255) by
 BM1PR0101CA0046.INDPRD01.PROD.OUTLOOK.COM (2603:1096:b00:1a::32) with
 Microsoft SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.3326.19 via Frontend
 Transport; Mon, 31 Aug 2020 12:30:35 +0000
X-Mailer: git-send-email 2.25.1
X-Originating-IP: [103.15.57.192]
X-MS-PublicTrafficType: Email
X-MS-Office365-Filtering-HT: Tenant
X-MS-Office365-Filtering-Correlation-Id: a0c893c2-8481-49ad-f902-08d84da9abcb
X-MS-TrafficTypeDiagnostic: DM6PR04MB6092:
X-MS-Exchange-Transport-Forked: True
X-Microsoft-Antispam-PRVS: 
 <DM6PR04MB60924E9B6D75943167526BA88D510@DM6PR04MB6092.namprd04.prod.outlook.com>
WDCIPOUTBOUND: EOP-TRUE
X-MS-Oob-TLC-OOBClassifiers: OLM:79;
X-MS-Exchange-SenderADCheck: 1
X-Microsoft-Antispam: BCL:0;
X-Microsoft-Antispam-Message-Info: 
 CCxZUTgZq5baVepkbG7smmIJsW2GD2QMxsPfkYVdRmwvsZzck+Lct01FPlt4Wb+ctd+N8Z2SRC62N6OcfFGOooXDnMeY5VkIcuxL/PbLCvEKlnrPlr4l2GFzlftBND4eme5UgznPviNjkUqWXawBSA8d5J3R5wBynKUUORhy6MaWxrBDwyo9dg2mmY5IT9IAR/999u7eRk2HicI2rAlZdufYCf8jUY9yWMHzSvLCeUV7VvZ+dq+NXU8YskE00/QZvM9o9kmjOb3gZdwgRBlQJnloMWbvtyr3qDuHEwXoWG51AE3WcoxvFwcpW6sseb8eMKBsIBOseVAMkBWzH+gk/viSe2uac0DeV9RAiRLSksSsmTdlgm9XXFF+EZmkBa/r03VDyMPesqqUCQWHO2vnAbexxSxQcaUd0BdZnAfS1ccj7iIVtrENKlRchdFGF/EYGJ952/94N7CeMGTibDnEQg==
X-Forefront-Antispam-Report: 
 CIP:255.255.255.255;CTRY:;LANG:en;SCL:1;SRV:;IPV:NLI;SFV:NSPM;H:DM6PR04MB6201.namprd04.prod.outlook.com;PTR:;CAT:NONE;SFS:(4636009)(136003)(396003)(366004)(39860400002)(346002)(376002)(44832011)(966005)(6666004)(52116002)(8676002)(86362001)(36756003)(478600001)(6486002)(7416002)(30864003)(110136005)(8936002)(54906003)(83380400001)(66946007)(1076003)(66556008)(2906002)(26005)(186003)(66476007)(956004)(316002)(16576012)(4326008)(5660300002)(2616005)(42580500001);DIR:OUT;SFP:1102;
X-MS-Exchange-AntiSpam-MessageData: 
 jImht/o6OtWs+z7aKIF3BTMFJfUIDhH0erbZ3vEOu8jZYO6N4SgUKB0ZYxL7CLrbvHfEbG4Xn4HsEOYp0Tz/xBOhOvhiTp0EJzgLIWC793GUHb4Xks6kMWq/fuT+7poKgKrgxRMFI2X2FNDQy4E0cG0eG2ZzpsIiezMBcgoGTfXZQjZxfTX9uPJi5uimBF3TbWpc9u1oJP0F3b+hI7DXCDy99B9CiFCgVepix81K99bkvgI5iuGaU+muwGRYSy2Aj979aPpp62pd9qUCH7K/UruzaDdb2R02CJKE06xzqocAiSGgJFd0JyrxLHjCb8vJSP6xocsvphAXPLWhtHxMxlLY6LyNes2R5nzgcw7DzyNx4JuJvQQXfaYU5Zzm7k1t5ypyiZ6eT1CH5tt0Ps3KjQGlrUHtWeV2Gs2U1Z8dd2LOvq/iLrH2FoiYUv3Plhr5tIlGzAqbVSfr1eZAvvo/X8BSwdyFu1mGckKsSsHCd8Q3l5m2P9x+++d9/bDALiEH1wA9E2rL/pi16SkMgoRKqrtQyVRUpdvGAIAERAzEMJSEXN4zmrRm1AkWeO3OqksCIVB5W9mpCX/cvQLHgQQ3ioo9b4KJ16ze8LIoYIyl8iOvMSDzBoMZ7/mPmt0lzIka0aJ2cy+BXb6t0Ozr7jiIXA==
X-OriginatorOrg: wdc.com
X-MS-Exchange-CrossTenant-Network-Message-Id: 
 a0c893c2-8481-49ad-f902-08d84da9abcb
X-MS-Exchange-CrossTenant-AuthSource: DM6PR04MB6201.namprd04.prod.outlook.com
X-MS-Exchange-CrossTenant-AuthAs: Internal
X-MS-Exchange-CrossTenant-OriginalArrivalTime: 31 Aug 2020 12:30:40.4695
 (UTC)
X-MS-Exchange-CrossTenant-FromEntityHeader: Hosted
X-MS-Exchange-CrossTenant-Id: b61c8803-16f3-4c35-9b17-6f65f441df86
X-MS-Exchange-CrossTenant-MailboxType: HOSTED
X-MS-Exchange-CrossTenant-UserPrincipalName: 
 8R+TX709p6xhTTLgnF1O8ZuVDMUd0O27FPYWZiXCri0czuwkooCVnUKvcnSwkb8JJVBSFa4CAvz9pEKV0A7Fqw==
X-MS-Exchange-Transport-CrossTenantHeadersStamped: DM6PR04MB6092
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This series adds initial KVM RISC-V support. Currently, we are able to boot
Linux on RV64/RV32 Guest with multiple VCPUs.

Key aspects of KVM RISC-V added by this series are:
1. No RISC-V specific KVM IOCTL
2. Minimal possible KVM world-switch which touches only GPRs and few CSRs
3. Both RV64 and RV32 host supported
4. Full Guest/VM switch is done via vcpu_get/vcpu_put infrastructure
5. KVM ONE_REG interface for VCPU register access from user-space
6. PLIC emulation is done in user-space
7. Timer and IPI emuation is done in-kernel
8. Both Sv39x4 and Sv48x4 supported for RV64 host
9. MMU notifiers supported
10. Generic dirtylog supported
11. FP lazy save/restore supported
12. SBI v0.1 emulation for KVM Guest available
13. Forward unhandled SBI calls to KVM userspace
14. Hugepage support for Guest/VM
15. IOEVENTFD support for Vhost

Here's a brief TODO list which we will work upon after this series:
1. SBI v0.2 emulation in-kernel
2. SBI v0.2 hart state management emulation in-kernel
3. In-kernel PLIC emulation
4. ..... and more .....

This series can be found in riscv_kvm_v14 branch at:
https//github.com/avpatel/linux.git

Our work-in-progress KVMTOOL RISC-V port can be found in riscv_v4 branch
at: https//github.com/avpatel/kvmtool.git

The QEMU RISC-V hypervisor emulation is done by Alistair and is available
in mainline/anup/riscv-hyp-ext-v0.6.1 branch at:
https://github.com/kvm-riscv/qemu.git

To play around with KVM RISC-V, refer KVM RISC-V wiki at:
https://github.com/kvm-riscv/howto/wiki
https://github.com/kvm-riscv/howto/wiki/KVM-RISCV64-on-QEMU
https://github.com/kvm-riscv/howto/wiki/KVM-RISCV64-on-Spike

Changes since v13:
 - Rebased on Linux-5.9-rc3
 - Fixed kvm_riscv_vcpu_set_reg_csr() for SIP updation in PATCH5
 - Fixed instruction length computation in PATCH7
 - Added ioeventfd support in PATCH7
 - Ensure HSTATUS.SPVP is set to correct value before using HLV/HSV
   intructions in PATCH7
 - Fixed stage2_map_page() to set PTE 'A' and 'D' bits correctly
   in PATCH10
 - Added stage2 dirty page logging in PATCH10
 - Allow KVM user-space to SET/GET SCOUNTER CSR in PATCH5
 - Save/restore SCOUNTEREN in PATCH6
 - Reduced quite a few instructions for __kvm_riscv_switch_to() by
   using CSR swap instruction in PATCH6
 - Detect and use Sv48x4 when available in PATCH10

Changes since v12:
 - Rebased patches on Linux-5.8-rc4
 - By default enable all counters in HCOUNTEREN
 - RISC-V H-Extension v0.6.1 spec support

Changes since v11:
 - Rebased patches on Linux-5.7-rc3
 - Fixed typo in typecast of stage2_map_size define
 - Introduced struct kvm_cpu_trap to represent trap details and
   use it as function parameter wherever applicable
 - Pass memslot to kvm_riscv_stage2_map() for supporing dirty page
   logging in future
 - RISC-V H-Extension v0.6 spec support
 - Send-out first three patches as separate series so that it can
   be taken by Palmer for Linux RISC-V

Changes since v10:
 - Rebased patches on Linux-5.6-rc5
 - Reduce RISCV_ISA_EXT_MAX from 256 to 64
 - Separate PATCH for removing N-extension related defines
 - Added comments as requested by Palmer
 - Fixed HIDELEG CSR programming

Changes since v9:
 - Rebased patches on Linux-5.5-rc3
 - Squash PATCH19 and PATCH20 into PATCH5
 - Squash PATCH18 into PATCH11
 - Squash PATCH17 into PATCH16
 - Added ONE_REG interface for VCPU timer in PATCH13
 - Use HTIMEDELTA for VCPU timer in PATCH13
 - Updated KVM RISC-V mailing list in MAINTAINERS entry
 - Update KVM kconfig option to depend on RISCV_SBI and MMU
 - Check for SBI v0.2 and SBI v0.2 RFENCE extension at boot-time
 - Use SBI v0.2 RFENCE extension in VMID implementation
 - Use SBI v0.2 RFENCE extension in Stage2 MMU implementation
 - Use SBI v0.2 RFENCE extension in SBI implementation
 - Moved to RISC-V Hypervisor v0.5 draft spec
 - Updated Documentation/virt/kvm/api.txt for timer ONE_REG interface

Changes since v8:
 - Rebased series on Linux-5.4-rc3 and Atish's SBI v0.2 patches
 - Use HRTIMER_MODE_REL instead of HRTIMER_MODE_ABS in timer emulation
 - Fixed kvm_riscv_stage2_map() to handle hugepages
 - Added patch to forward unhandled SBI calls to user-space
 - Added patch for iterative/recursive stage2 page table programming
 - Added patch to remove per-CPU vsip_shadow variable
 - Added patch to fix race-condition in kvm_riscv_vcpu_sync_interrupts()

Changes since v7:
 - Rebased series on Linux-5.4-rc1 and Atish's SBI v0.2 patches
 - Removed PATCH1, PATCH3, and PATCH20 because these already merged
 - Use kernel doc style comments for ISA bitmap functions
 - Don't parse X, Y, and Z extension in riscv_fill_hwcap() because it will
   be added in-future
 - Mark KVM RISC-V kconfig option as EXPERIMENTAL
 - Typo fix in commit description of PATCH6 of v7 series
 - Use separate structs for CORE and CSR registers of ONE_REG interface
 - Explicitly include asm/sbi.h in kvm/vcpu_sbi.c
 - Removed implicit switch-case fall-through in kvm_riscv_vcpu_exit()
 - No need to set VSSTATUS.MXR bit in kvm_riscv_vcpu_unpriv_read()
 - Removed register for instruction length in kvm_riscv_vcpu_unpriv_read()
 - Added defines for checking/decoding instruction length
 - Added separate patch to forward unhandled SBI calls to userspace tool

Changes since v6:
 - Rebased patches on Linux-5.3-rc7
 - Added "return_handled" in struct kvm_mmio_decode to ensure that
   kvm_riscv_vcpu_mmio_return() updates SEPC only once
 - Removed trap_stval parameter from kvm_riscv_vcpu_unpriv_read()
 - Updated git repo URL in MAINTAINERS entry

Changes since v5:
 - Renamed KVM_REG_RISCV_CONFIG_TIMEBASE register to
   KVM_REG_RISCV_CONFIG_TBFREQ register in ONE_REG interface
 - Update SPEC in kvm_riscv_vcpu_mmio_return() for MMIO exits
 - Use switch case instead of illegal instruction opcode table for simplicity
 - Improve comments in stage2_remote_tlb_flush() for a potential remote TLB
  flush optimization
 - Handle all unsupported SBI calls in default case of
   kvm_riscv_vcpu_sbi_ecall() function
 - Fixed kvm_riscv_vcpu_sync_interrupts() for software interrupts
 - Improved unprivilege reads to handle traps due to Guest stage1 page table
 - Added separate patch to document RISC-V specific things in
   Documentation/virt/kvm/api.txt

Changes since v4:
 - Rebased patches on Linux-5.3-rc5
 - Added Paolo's Acked-by and Reviewed-by
 - Updated mailing list in MAINTAINERS entry

Changes since v3:
 - Moved patch for ISA bitmap from KVM prep series to this series
 - Make vsip_shadow as run-time percpu variable instead of compile-time
 - Flush Guest TLBs on all Host CPUs whenever we run-out of VMIDs

Changes since v2:
 - Removed references of KVM_REQ_IRQ_PENDING from all patches
 - Use kvm->srcu within in-kernel KVM run loop
 - Added percpu vsip_shadow to track last value programmed in VSIP CSR
 - Added comments about irqs_pending and irqs_pending_mask
 - Used kvm_arch_vcpu_runnable() in-place-of kvm_riscv_vcpu_has_interrupt()
   in system_opcode_insn()
 - Removed unwanted smp_wmb() in kvm_riscv_stage2_vmid_update()
 - Use kvm_flush_remote_tlbs() in kvm_riscv_stage2_vmid_update()
 - Use READ_ONCE() in kvm_riscv_stage2_update_hgatp() for vmid

Changes since v1:
 - Fixed compile errors in building KVM RISC-V as module
 - Removed unused kvm_riscv_halt_guest() and kvm_riscv_resume_guest()
 - Set KVM_CAP_SYNC_MMU capability only after MMU notifiers are implemented
 - Made vmid_version as unsigned long instead of atomic
 - Renamed KVM_REQ_UPDATE_PGTBL to KVM_REQ_UPDATE_HGATP
 - Renamed kvm_riscv_stage2_update_pgtbl() to kvm_riscv_stage2_update_hgatp()
 - Configure HIDELEG and HEDELEG in kvm_arch_hardware_enable()
 - Updated ONE_REG interface for CSR access to user-space
 - Removed irqs_pending_lock and use atomic bitops instead
 - Added separate patch for FP ONE_REG interface
 - Added separate patch for updating MAINTAINERS file

Anup Patel (13):
  RISC-V: Add hypervisor extension related CSR defines
  RISC-V: Add initial skeletal KVM support
  RISC-V: KVM: Implement VCPU create, init and destroy functions
  RISC-V: KVM: Implement VCPU interrupts and requests handling
  RISC-V: KVM: Implement KVM_GET_ONE_REG/KVM_SET_ONE_REG ioctls
  RISC-V: KVM: Implement VCPU world-switch
  RISC-V: KVM: Handle MMIO exits for VCPU
  RISC-V: KVM: Handle WFI exits for VCPU
  RISC-V: KVM: Implement VMID allocator
  RISC-V: KVM: Implement stage2 page table programming
  RISC-V: KVM: Implement MMU notifiers
  RISC-V: KVM: Document RISC-V specific parts of KVM API
  RISC-V: KVM: Add MAINTAINERS entry

Atish Patra (4):
  RISC-V: KVM: Add timer functionality
  RISC-V: KVM: FP lazy save/restore
  RISC-V: KVM: Implement ONE REG interface for FP registers
  RISC-V: KVM: Add SBI v0.1 support

 Documentation/virt/kvm/api.rst          |  193 ++++-
 MAINTAINERS                             |   11 +
 arch/riscv/Kconfig                      |    2 +
 arch/riscv/Makefile                     |    2 +
 arch/riscv/include/asm/csr.h            |   89 ++
 arch/riscv/include/asm/kvm_host.h       |  278 +++++++
 arch/riscv/include/asm/kvm_types.h      |    7 +
 arch/riscv/include/asm/kvm_vcpu_timer.h |   44 +
 arch/riscv/include/asm/pgtable-bits.h   |    1 +
 arch/riscv/include/uapi/asm/kvm.h       |  128 +++
 arch/riscv/kernel/asm-offsets.c         |  156 ++++
 arch/riscv/kvm/Kconfig                  |   36 +
 arch/riscv/kvm/Makefile                 |   15 +
 arch/riscv/kvm/main.c                   |  118 +++
 arch/riscv/kvm/mmu.c                    |  857 +++++++++++++++++++
 arch/riscv/kvm/tlb.S                    |   74 ++
 arch/riscv/kvm/vcpu.c                   | 1012 +++++++++++++++++++++++
 arch/riscv/kvm/vcpu_exit.c              |  701 ++++++++++++++++
 arch/riscv/kvm/vcpu_sbi.c               |  173 ++++
 arch/riscv/kvm/vcpu_switch.S            |  400 +++++++++
 arch/riscv/kvm/vcpu_timer.c             |  225 +++++
 arch/riscv/kvm/vm.c                     |   81 ++
 arch/riscv/kvm/vmid.c                   |  120 +++
 drivers/clocksource/timer-riscv.c       |    8 +
 include/clocksource/timer-riscv.h       |   16 +
 include/uapi/linux/kvm.h                |    8 +
 26 files changed, 4746 insertions(+), 9 deletions(-)
 create mode 100644 arch/riscv/include/asm/kvm_host.h
 create mode 100644 arch/riscv/include/asm/kvm_types.h
 create mode 100644 arch/riscv/include/asm/kvm_vcpu_timer.h
 create mode 100644 arch/riscv/include/uapi/asm/kvm.h
 create mode 100644 arch/riscv/kvm/Kconfig
 create mode 100644 arch/riscv/kvm/Makefile
 create mode 100644 arch/riscv/kvm/main.c
 create mode 100644 arch/riscv/kvm/mmu.c
 create mode 100644 arch/riscv/kvm/tlb.S
 create mode 100644 arch/riscv/kvm/vcpu.c
 create mode 100644 arch/riscv/kvm/vcpu_exit.c
 create mode 100644 arch/riscv/kvm/vcpu_sbi.c
 create mode 100644 arch/riscv/kvm/vcpu_switch.S
 create mode 100644 arch/riscv/kvm/vcpu_timer.c
 create mode 100644 arch/riscv/kvm/vm.c
 create mode 100644 arch/riscv/kvm/vmid.c
 create mode 100644 include/clocksource/timer-riscv.h
```
#### [PATCH v2 0/4] Qemu SEV-ES guest support
##### From: Tom Lendacky <thomas.lendacky@amd.com>
From: Tom Lendacky <thomas.lendacky@amd.com>

```c
From patchwork Mon Aug 31 15:37:09 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Tom Lendacky <thomas.lendacky@amd.com>
X-Patchwork-Id: 11746551
Return-Path: <SRS0=MvWC=CJ=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 82D9E13B6
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 31 Aug 2020 15:38:41 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 63EA020866
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 31 Aug 2020 15:38:41 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=amdcloud.onmicrosoft.com
 header.i=@amdcloud.onmicrosoft.com header.b="SQgSFKsB"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728906AbgHaPik (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 31 Aug 2020 11:38:40 -0400
Received: from mail-dm6nam08on2055.outbound.protection.outlook.com
 ([40.107.102.55]:38992
        "EHLO NAM04-DM6-obe.outbound.protection.outlook.com"
        rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org with ESMTP
        id S1728655AbgHaPhb (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 31 Aug 2020 11:37:31 -0400
ARC-Seal: i=1; a=rsa-sha256; s=arcselector9901; d=microsoft.com; cv=none;
 b=iZBS6/83ZB3hVKddpnqJwL3OmV4qHHOc5AN/LAhgdkSapndor5CRS7zQvPbMH0foK3wQgmTTKOGqnKMmB+D6lKkhBu7FweEJECK7Jf/nSKsp3G2eOyvLdzXD6+SwORq4I2ds/7C/M62LTbVhJA7zVqNkSyDWlLi8qDFkJM5q11waBbgsUDVoagruisZ41PXSC/w9m3Rs9v6DUK4cozXqsM1jFFwlcUAWzYXcJkQMHM64G0R7iUeREj5xvGs6LQ0dRl/A3q8l8cxfh+Ve/S5j4hdR9HbZdoC3AYHw5o4LAdAWOBuZl+yAJIGfrUe69ug6Yjfu/uJ5XDXpUaVRyKmjaA==
ARC-Message-Signature: i=1; a=rsa-sha256; c=relaxed/relaxed; d=microsoft.com;
 s=arcselector9901;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=VZ6+szD+ID4g5++/QKWSa+ebqnmajC9g4WYXGoRXiwQ=;
 b=LowbqtYso7k7WSaZG4R0wS5GAOYoE6tJZjLTWOLd8peVf/neml/xB437GLThmIWla30GTyERYKVZb/lflAMkocllVuKinCsNpYPhgZUelRkdHWjtpVcBpO05xuhM/IeZkT6/cVWLoZwBHvK8MZf0PN5Qd9xEVuXWTCMXkBEtT1GZG2/B1bcO2HT1DBUnvBeDkiNOgb0UQVpKOlnRo4qtYANIdGEC1F2DcrQJhEWzhwK3dwTyITZQ7cD/SD2xPS8rwR9ukiQ83yFVjdGdiSl6nO9rUSoPiEuKM3EjT0rrrmKGZg3bnxkrDWFDKSEY142waYBls7OqX9kn806MAwrGXg==
ARC-Authentication-Results: i=1; mx.microsoft.com 1; spf=pass
 smtp.mailfrom=amd.com; dmarc=pass action=none header.from=amd.com; dkim=pass
 header.d=amd.com; arc=none
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
 d=amdcloud.onmicrosoft.com; s=selector2-amdcloud-onmicrosoft-com;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=VZ6+szD+ID4g5++/QKWSa+ebqnmajC9g4WYXGoRXiwQ=;
 b=SQgSFKsBxN4Z42pvB8kbGI7KsmqbKhE+rDtGZffWH3stiYx+7JafeyHdjmACTmllsB6wGKC8yzGS7OO9LGoTYEQm+ZjxV/P1Qt8GdgMSyuKOENCfMJ7Fu6mO6vGJjxU/ukhxJ2TCiCnSjmRB7JLrCRtPJFZEktJsOpyY+E7wTAg=
Authentication-Results: nongnu.org; dkim=none (message not signed)
 header.d=none;nongnu.org; dmarc=none action=none header.from=amd.com;
Received: from DM5PR12MB1355.namprd12.prod.outlook.com (2603:10b6:3:6e::7) by
 DM6PR12MB4484.namprd12.prod.outlook.com (2603:10b6:5:28f::24) with Microsoft
 SMTP Server (version=TLS1_2, cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id
 15.20.3326.19; Mon, 31 Aug 2020 15:37:28 +0000
Received: from DM5PR12MB1355.namprd12.prod.outlook.com
 ([fe80::299a:8ed2:23fc:6346]) by DM5PR12MB1355.namprd12.prod.outlook.com
 ([fe80::299a:8ed2:23fc:6346%3]) with mapi id 15.20.3326.025; Mon, 31 Aug 2020
 15:37:28 +0000
From: Tom Lendacky <thomas.lendacky@amd.com>
To: qemu-devel@nongnu.org, kvm@vger.kernel.org
Cc: Marcel Apfelbaum <marcel.apfelbaum@gmail.com>,
        Paolo Bonzini <pbonzini@redhat.com>,
        "Dr. David Alan Gilbert" <dgilbert@redhat.com>,
        Eduardo Habkost <ehabkost@redhat.com>,
        Richard Henderson <rth@twiddle.net>,
        Connor Kuehl <ckuehl@redhat.com>,
        Brijesh Singh <brijesh.singh@amd.com>,
        Jiri Slaby <jslaby@suse.cz>,
        Marcelo Tosatti <mtosatti@redhat.com>,
        "Michael S. Tsirkin" <mst@redhat.com>
Subject: [PATCH v2 0/4] Qemu SEV-ES guest support
Date: Mon, 31 Aug 2020 10:37:09 -0500
Message-Id: <cover.1598888232.git.thomas.lendacky@amd.com>
X-Mailer: git-send-email 2.28.0
X-ClientProxiedBy: SN4PR0501CA0011.namprd05.prod.outlook.com
 (2603:10b6:803:40::24) To DM5PR12MB1355.namprd12.prod.outlook.com
 (2603:10b6:3:6e::7)
MIME-Version: 1.0
X-MS-Exchange-MessageSentRepresentingType: 1
Received: from 255.255.255.255 (255.255.255.255) by
 SN4PR0501CA0011.namprd05.prod.outlook.com (2603:10b6:803:40::24) with
 Microsoft SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.3348.7 via Frontend
 Transport; Mon, 31 Aug 2020 15:37:27 +0000
X-Mailer: git-send-email 2.28.0
X-Originating-IP: [165.204.77.1]
X-MS-PublicTrafficType: Email
X-MS-Office365-Filtering-HT: Tenant
X-MS-Office365-Filtering-Correlation-Id: 36f710d3-1b33-4f52-be30-08d84dc3c446
X-MS-TrafficTypeDiagnostic: DM6PR12MB4484:
X-MS-Exchange-Transport-Forked: True
X-Microsoft-Antispam-PRVS: 
 <DM6PR12MB4484A3DDBE68747368978BA3EC510@DM6PR12MB4484.namprd12.prod.outlook.com>
X-MS-Oob-TLC-OOBClassifiers: OLM:5516;
X-MS-Exchange-SenderADCheck: 1
X-Microsoft-Antispam: BCL:0;
X-Microsoft-Antispam-Message-Info: 
 KyXrmsCQqJqETX5jC4xSEe3++XXr1IqP1htfHeJadNlAJmu4n+D13GqTYyd9GlHcQNAm00d3khkCGCBBAs0C3ozbZF9FjUGD7OhbXZMFo679K2dqQdfwz+v7gL43r70wDE2XxtC/h3d3wtbdTfZs1NiBf2lmAtCI5AAMbei4tYApgxcVMH5yZA5aLttwPLLtbh65HuabvDueAe65JnlnEKkunVmnZKCx9Q2J9jXv7gpsWnOzZxDZYskU3xMbgAxThq2F/4NWE2jZ4v4XBLunQfYPdYNqaaeHyRwlHi50GNKzxlIKXrpfiwLgVUQbwBkw16SZw9Tfn9lvpxOHFrmWgi1fmgdMQrEH6NWAewaGtcVsfrqac/gKOnsDk+4PdrgYbk+ChZBh7lYHz7/b+lB8kQ==
X-Forefront-Antispam-Report: 
 CIP:255.255.255.255;CTRY:;LANG:en;SCL:1;SRV:;IPV:NLI;SFV:NSPM;H:DM5PR12MB1355.namprd12.prod.outlook.com;PTR:;CAT:NONE;SFS:(4636009)(396003)(39860400002)(366004)(346002)(376002)(136003)(54906003)(956004)(966005)(16576012)(7416002)(2906002)(6666004)(4326008)(2616005)(6486002)(316002)(66556008)(8676002)(66946007)(478600001)(186003)(5660300002)(8936002)(86362001)(83380400001)(66476007)(36756003)(52116002)(26005);DIR:OUT;SFP:1101;
X-MS-Exchange-AntiSpam-MessageData: 
 I2gbbspU8tDUPtqlRZ4vGDc6kwwJTPu+2NBt7GZTW4zuv8957GNSttltKgi9RRVAKHnl9dTaohZ3/rZHoFl3OkcG5LJraYeFP27lSeB63PKRwcs7SN1hyR3HaKclckXKAy79Dh3fwMKHXojczEi+2h8hijC38gjr3SGERthglseeAEFg8bWbK54IuCL+Tey23kQ8lwcYX2pfzu6olzrlwwR3RjX0/Xa4FAmb90vVHEvBuKtqDA4Scq96rLgUX+ffiXBTEpsGCoGCIf/brcooBVA6g62CX2h3PQDH79XeuixqJlK9MK6NqRE4YmTTmfBU16z92jbQzN8KylFKkP8SxuEatqfSNMjLWwixnRo10nOfQ3tWLdo9/WuNqsLAb+Oz6kxalQCpsPvMASgkshpQ/KsD5HKEvVCaaJvT8T9cgD8jcCXKbhOTkWYi4C2/+IFwTgGaL0HnYBwvFI+IJbKgD1RF4q5//ApRYBS+mLTBqYWPXnd8UDV8HgOaINz2S7yI7KLc05pkuuYothnY0mDnZzRJJeN/wtkvGhbLokoIhNzOtJ3VWSHU8Gzju72vjCOLlL0kUIGsf4DGkVE7rWO73I3c+/GpEmn9PeYFNTucHo2HeVa07gL1fi6K1Byb8PJPBuJqG8zrMTHyx8vCEOGB3g==
X-OriginatorOrg: amd.com
X-MS-Exchange-CrossTenant-Network-Message-Id: 
 36f710d3-1b33-4f52-be30-08d84dc3c446
X-MS-Exchange-CrossTenant-AuthSource: DM5PR12MB1355.namprd12.prod.outlook.com
X-MS-Exchange-CrossTenant-AuthAs: Internal
X-MS-Exchange-CrossTenant-OriginalArrivalTime: 31 Aug 2020 15:37:28.2925
 (UTC)
X-MS-Exchange-CrossTenant-FromEntityHeader: Hosted
X-MS-Exchange-CrossTenant-Id: 3dd8961f-e488-4e60-8e11-a82d994e183d
X-MS-Exchange-CrossTenant-MailboxType: HOSTED
X-MS-Exchange-CrossTenant-UserPrincipalName: 
 6pKzLdbCWHE0mvw5ukuXiyQaDWhTZ2u4eE0RkhrdBcZssfpyYqFTtQiMdSF7kC9x7lQDeubaUQ7n0/pEBjI5mQ==
X-MS-Exchange-Transport-CrossTenantHeadersStamped: DM6PR12MB4484
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Tom Lendacky <thomas.lendacky@amd.com>

This patch series provides support for launching an SEV-ES guest.

Secure Encrypted Virtualization - Encrypted State (SEV-ES) expands on the
SEV support to protect the guest register state from the hypervisor. See
"AMD64 Architecture Programmer's Manual Volume 2: System Programming",
section "15.35 Encrypted State (SEV-ES)" [1].

In order to allow a hypervisor to perform functions on behalf of a guest,
there is architectural support for notifying a guest's operating system
when certain types of VMEXITs are about to occur. This allows the guest to
selectively share information with the hypervisor to satisfy the requested
function. The notification is performed using a new exception, the VMM
Communication exception (#VC). The information is shared through the
Guest-Hypervisor Communication Block (GHCB) using the VMGEXIT instruction.
The GHCB format and the protocol for using it is documented in "SEV-ES
Guest-Hypervisor Communication Block Standardization" [2].

The main areas of the Qemu code that are updated to support SEV-ES are
around the SEV guest launch process and AP booting in order to support
booting multiple vCPUs.

There are no new command line switches required. Instead, the desire for
SEV-ES is presented using the SEV policy object. Bit 2 of the SEV policy
object indicates that SEV-ES is required.

The SEV launch process is updated in two ways. The first is that a the
KVM_SEV_ES_INIT ioctl is used to initialize the guest instead of the
standard KVM_SEV_INIT ioctl. The second is that before the SEV launch
measurement is calculated, the LAUNCH_UPDATE_VMSA SEV API is invoked for
each vCPU that Qemu has created. Once the LAUNCH_UPDATE_VMSA API has been
invoked, no direct changes to the guest register state can be made.

AP booting poses some interesting challenges. The INIT-SIPI-SIPI sequence
is typically used to boot the APs. However, the hypervisor is not allowed
to update the guest registers. For the APs, the reset vector must be known
in advance. An OVMF method to provide a known reset vector address exists
by providing an SEV information block, identified by UUID, near the end of
the firmware [3]. OVMF will program the jump to the actual reset vector in
this area of memory. Since the memory location is known in advance, an AP
can be created with the known reset vector address as its starting CS:IP.
The GHCB document [2] talks about how SMP booting under SEV-ES is
performed.

[1] https://www.amd.com/system/files/TechDocs/24593.pdf
[2] https://developer.amd.com/wp-content/resources/56421.pdf
[3] 30937f2f98c4 ("OvmfPkg: Use the SEV-ES work area for the SEV-ES AP reset vector")
    https://github.com/tianocore/edk2/commit/30937f2f98c42496f2f143fe8374ae7f7e684847
---

These patches are based on commit:
d0ed6a69d3 ("Update version for v5.1.0 release")

(I tried basing on the latest Qemu commit, but I was having build issues
that level)

A version of the tree can be found at:
https://github.com/AMDESE/qemu/tree/sev-es-v10

Changes since v1:
- Fixed checkpatch.pl errors/warnings

Tom Lendacky (4):
  sev/i386: Add initial support for SEV-ES
  sev/i386: Allow AP booting under SEV-ES
  sev/i386: Don't allow a system reset under an SEV-ES guest
  sev/i386: Enable an SEV-ES guest based on SEV policy

 accel/kvm/kvm-all.c       | 73 +++++++++++++++++++++++++++++
 accel/stubs/kvm-stub.c    |  5 ++
 hw/i386/pc_sysfw.c        | 10 +++-
 include/sysemu/cpus.h     |  2 +
 include/sysemu/hw_accel.h |  5 ++
 include/sysemu/kvm.h      | 18 +++++++
 include/sysemu/sev.h      |  3 ++
 softmmu/cpus.c            |  5 ++
 softmmu/vl.c              |  5 +-
 target/i386/cpu.c         |  1 +
 target/i386/kvm.c         |  2 +
 target/i386/sev-stub.c    |  5 ++
 target/i386/sev.c         | 99 ++++++++++++++++++++++++++++++++++++++-
 target/i386/sev_i386.h    |  1 +
 14 files changed, 230 insertions(+), 4 deletions(-)
```
#### [kvm-unit-tests RFC 0/4] KVM: arm64: Statistical Profiling Extension
##### From: Eric Auger <eric.auger@redhat.com>

```c
From patchwork Mon Aug 31 19:34:10 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Eric Auger <eric.auger@redhat.com>
X-Patchwork-Id: 11746903
Return-Path: <SRS0=MvWC=CJ=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 5D0FE722
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 31 Aug 2020 19:34:30 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 3CC182087D
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 31 Aug 2020 19:34:30 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="T9aOyu3f"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728741AbgHaTe2 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 31 Aug 2020 15:34:28 -0400
Received: from us-smtp-delivery-1.mimecast.com ([205.139.110.120]:40064 "EHLO
        us-smtp-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org
        with ESMTP id S1725872AbgHaTe2 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 31 Aug 2020 15:34:28 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1598902467;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=YQWthbnL/F8A9JG87S9VWHvNqxsIM98exPrIcod4sws=;
        b=T9aOyu3fQqH4pxh02B3U6HPr7uEhqdaIEsPnWyY0FZG347GH/d1IV9GqcV0LnH4GPFom6z
        dL1U8Fsm5zsgLtgayVQJDrBUOVENJQOL5n3FxN1fMAza0aWIa9464L513xqvjuRzaU6ouX
        eRnfaMWUbHOGQi3yOLZ3uEVbqm+Dklw=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-274-ei-P5MgSPnS9WN3J5PB5aA-1; Mon, 31 Aug 2020 15:34:25 -0400
X-MC-Unique: ei-P5MgSPnS9WN3J5PB5aA-1
Received: from smtp.corp.redhat.com (int-mx03.intmail.prod.int.phx2.redhat.com
 [10.5.11.13])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 84DCE18A2243;
        Mon, 31 Aug 2020 19:34:22 +0000 (UTC)
Received: from laptop.redhat.com (ovpn-112-112.ams2.redhat.com
 [10.36.112.112])
        by smtp.corp.redhat.com (Postfix) with ESMTP id DE3F37EB7B;
        Mon, 31 Aug 2020 19:34:16 +0000 (UTC)
From: Eric Auger <eric.auger@redhat.com>
To: eric.auger.pro@gmail.com, eric.auger@redhat.com,
        kvm@vger.kernel.org, kvmarm@lists.cs.columbia.edu,
        qemu-devel@nongnu.org, drjones@redhat.com, andrew.murray@arm.com,
        sudeep.holla@arm.com, maz@kernel.org, will@kernel.org,
        haibo.xu@linaro.org
Subject: [kvm-unit-tests RFC 0/4] KVM: arm64: Statistical Profiling Extension
 Tests
Date: Mon, 31 Aug 2020 21:34:10 +0200
Message-Id: <20200831193414.6951-1-eric.auger@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.13
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This series implements tests exercising the Statistical Profiling
Extensions.

This was tested with associated unmerged kernel [1] and QEMU [2]
series.

Depending on the comments, I can easily add other tests checking
more configs, additional events and testing migration too. I hope
this can be useful when respinning both series.

All SPE tests can be launched with:
./run_tests.sh -g spe
Tests also can be launched individually. For example:
./arm-run arm/spe.flat -append 'spe-buffer'

The series can be found at:
https://github.com/eauger/kut/tree/spe_rfc

References:
[1] [PATCH v2 00/18] arm64: KVM: add SPE profiling support
[2] [PATCH 0/7] target/arm: Add vSPE support to KVM guest

Eric Auger (4):
  arm64: Move get_id_aa64dfr0() in processor.h
  spe: Probing and Introspection Test
  spe: Add profiling buffer test
  spe: Test Profiling Buffer Events

 arm/Makefile.common       |   1 +
 arm/pmu.c                 |   1 -
 arm/spe.c                 | 463 ++++++++++++++++++++++++++++++++++++++
 arm/unittests.cfg         |  24 ++
 lib/arm64/asm/barrier.h   |   1 +
 lib/arm64/asm/processor.h |   5 +
 6 files changed, 494 insertions(+), 1 deletion(-)
 create mode 100644 arm/spe.c
```
