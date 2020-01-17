

#### [PATCH 0/2 v3] KVM: nVMX: Check GUEST_DR7 on vmentry of nested guests
##### From: Krish Sadhukhan <krish.sadhukhan@oracle.com>

```c
From patchwork Thu Jan 16 00:54:31 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Krish Sadhukhan <krish.sadhukhan@oracle.com>
X-Patchwork-Id: 11335809
Return-Path: <SRS0=nLL1=3F=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id BDF371398
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 16 Jan 2020 01:31:38 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 9BB272084D
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 16 Jan 2020 01:31:38 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=oracle.com header.i=@oracle.com
 header.b="dLPkorPV"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729587AbgAPBbh (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 15 Jan 2020 20:31:37 -0500
Received: from aserp2120.oracle.com ([141.146.126.78]:57960 "EHLO
        aserp2120.oracle.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1729043AbgAPBbh (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 15 Jan 2020 20:31:37 -0500
Received: from pps.filterd (aserp2120.oracle.com [127.0.0.1])
        by aserp2120.oracle.com (8.16.0.27/8.16.0.27) with SMTP id
 00G1Ujfr012744;
        Thu, 16 Jan 2020 01:31:33 GMT
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=oracle.com;
 h=from : to : cc :
 subject : date : message-id : mime-version : content-transfer-encoding;
 s=corp-2019-08-05; bh=6jxd9Fk5Y4ntwdDAXooxwdtLtWDkZZ/v2lQ6bDXbZzk=;
 b=dLPkorPVHsgZzd2ka15buvY1WkogWYOU+rHxHmYWRtG9vGO+/0kKzC6rcL4x5n5wDW1p
 QZUSCW4UpsPNT7VYKr0/YaAZtCedk4iK05GY4jsM3fSygGHaxcmu0CN7X+8ARvFtuv5b
 jtDwG+yxUbKm1v1qO8wsl//AjZnE2NhUQuLfTPjVzUYbE7nTctWjvKi3eKPu2pDsaisB
 tv41r8uCN6Oe1lxoUgGHd36ofG5ojE+MA45q2rcnLGaI3x88LLIUtSSYBQ/YKSN5WRDO
 rgQnA22E7IwmihLaaxqx5Te+9uZQK4pBaCvOxryg7zrtan2CIHjy4eWC32RNOVw+MXSp tg==
Received: from aserp3020.oracle.com (aserp3020.oracle.com [141.146.126.70])
        by aserp2120.oracle.com with ESMTP id 2xf73tykem-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Thu, 16 Jan 2020 01:31:33 +0000
Received: from pps.filterd (aserp3020.oracle.com [127.0.0.1])
        by aserp3020.oracle.com (8.16.0.27/8.16.0.27) with SMTP id
 00G1UkgW016072;
        Thu, 16 Jan 2020 01:31:33 GMT
Received: from aserv0122.oracle.com (aserv0122.oracle.com [141.146.126.236])
        by aserp3020.oracle.com with ESMTP id 2xj1as8601-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Thu, 16 Jan 2020 01:31:33 +0000
Received: from abhmp0015.oracle.com (abhmp0015.oracle.com [141.146.116.21])
        by aserv0122.oracle.com (8.14.4/8.14.4) with ESMTP id 00G1VVDX027951;
        Thu, 16 Jan 2020 01:31:32 GMT
Received: from ban25x6uut29.us.oracle.com (/10.153.73.29)
        by default (Oracle Beehive Gateway v4.0)
        with ESMTP ; Wed, 15 Jan 2020 17:31:31 -0800
From: Krish Sadhukhan <krish.sadhukhan@oracle.com>
To: kvm@vger.kernel.org
Cc: pbonzini@redhat.com, jmattson@google.com
Subject: [PATCH 0/2 v3] KVM: nVMX: Check GUEST_DR7 on vmentry of nested guests
Date: Wed, 15 Jan 2020 19:54:31 -0500
Message-Id: <20200116005433.5242-1-krish.sadhukhan@oracle.com>
X-Mailer: git-send-email 2.20.1
MIME-Version: 1.0
X-Proofpoint-Virus-Version: vendor=nai engine=6000 definitions=9501
 signatures=668685
X-Proofpoint-Spam-Details: rule=notspam policy=default score=0 suspectscore=1
 malwarescore=0
 phishscore=0 bulkscore=0 spamscore=0 mlxscore=0 mlxlogscore=788
 adultscore=0 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.0.1-1911140001 definitions=main-2001160010
X-Proofpoint-Virus-Version: vendor=nai engine=6000 definitions=9501
 signatures=668685
X-Proofpoint-Spam-Details: rule=notspam policy=default score=0
 priorityscore=1501 malwarescore=0
 suspectscore=1 phishscore=0 bulkscore=0 spamscore=0 clxscore=1015
 lowpriorityscore=0 mlxscore=0 impostorscore=0 mlxlogscore=848 adultscore=0
 classifier=spam adjust=0 reason=mlx scancount=1 engine=8.0.1-1911140001
 definitions=main-2001160010
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

v2 -> v3:
	The following changes have been made to patch# 1:
	  i) Commit message body mentions the reason for doing this check in
	     software.
	  i) The CONFIG_X86_64 guard in nested_vmx_check_guest_state() is
	     removed.
	  ii) The data type of the parameter to kvm_dr7_valid() is
	      'unsigned long'.


[PATCH 1/2 v3] KVM: nVMX: Check GUEST_DR7 on vmentry of nested guests
[PATCH 2/2 v3] kvm-unit-test: nVMX: Test GUEST_DR7 on vmentry of nested guests

 arch/x86/kvm/vmx/nested.c | 4 ++++
 arch/x86/kvm/x86.c        | 2 +-
 arch/x86/kvm/x86.h        | 6 ++++++
 3 files changed, 11 insertions(+), 1 deletion(-)

Krish Sadhukhan (1):
      nVMX: Check GUEST_DR7 on vmentry of nested guests

 x86/vmx_tests.c | 44 ++++++++++++++++++++++++++++++++++++++++++++
 1 file changed, 44 insertions(+)

Krish Sadhukhan (1):
      nVMX: Test GUEST_DR7 on vmentry of nested guests
```
#### [kvm-unit-tests PATCH v2 0/7] s390x: smp: Improve smp code and reset
##### From: Janosch Frank <frankja@linux.ibm.com>

```c
From patchwork Thu Jan 16 12:05:06 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Janosch Frank <frankja@linux.ibm.com>
X-Patchwork-Id: 11336635
Return-Path: <SRS0=nLL1=3F=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id C70171398
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 16 Jan 2020 12:05:36 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id ACE8120663
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 16 Jan 2020 12:05:36 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726974AbgAPMFg (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 16 Jan 2020 07:05:36 -0500
Received: from mx0a-001b2d01.pphosted.com ([148.163.156.1]:32890 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1726928AbgAPMFf (ORCPT
        <rfc822;kvm@vger.kernel.org>); Thu, 16 Jan 2020 07:05:35 -0500
Received: from pps.filterd (m0187473.ppops.net [127.0.0.1])
        by mx0a-001b2d01.pphosted.com (8.16.0.42/8.16.0.42) with SMTP id
 00GBvfHT023764
        for <kvm@vger.kernel.org>; Thu, 16 Jan 2020 07:05:34 -0500
Received: from e06smtp01.uk.ibm.com (e06smtp01.uk.ibm.com [195.75.94.97])
        by mx0a-001b2d01.pphosted.com with ESMTP id 2xfaw2cp9j-1
        (version=TLSv1.2 cipher=AES256-GCM-SHA384 bits=256 verify=NOT)
        for <kvm@vger.kernel.org>; Thu, 16 Jan 2020 07:05:32 -0500
Received: from localhost
        by e06smtp01.uk.ibm.com with IBM ESMTP SMTP Gateway: Authorized Use
 Only! Violators will be prosecuted
        for <kvm@vger.kernel.org> from <frankja@linux.ibm.com>;
        Thu, 16 Jan 2020 12:05:28 -0000
Received: from b06cxnps3074.portsmouth.uk.ibm.com (9.149.109.194)
        by e06smtp01.uk.ibm.com (192.168.101.131) with IBM ESMTP SMTP Gateway:
 Authorized Use Only! Violators will be prosecuted;
        (version=TLSv1/SSLv3 cipher=AES256-GCM-SHA384 bits=256/256)
        Thu, 16 Jan 2020 12:05:24 -0000
Received: from d06av21.portsmouth.uk.ibm.com (d06av21.portsmouth.uk.ibm.com
 [9.149.105.232])
        by b06cxnps3074.portsmouth.uk.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id 00GC5N2544761290
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Thu, 16 Jan 2020 12:05:23 GMT
Received: from d06av21.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id AC6815205A;
        Thu, 16 Jan 2020 12:05:23 +0000 (GMT)
Received: from localhost.localdomain (unknown [9.152.224.123])
        by d06av21.portsmouth.uk.ibm.com (Postfix) with ESMTP id C2E0952052;
        Thu, 16 Jan 2020 12:05:22 +0000 (GMT)
From: Janosch Frank <frankja@linux.ibm.com>
To: kvm@vger.kernel.org
Cc: thuth@redhat.com, borntraeger@de.ibm.com,
        linux-s390@vger.kernel.org, david@redhat.com, cohuck@redhat.com
Subject: [kvm-unit-tests PATCH v2 0/7] s390x: smp: Improve smp code and reset
 checks
Date: Thu, 16 Jan 2020 07:05:06 -0500
X-Mailer: git-send-email 2.20.1
MIME-Version: 1.0
X-TM-AS-GCONF: 00
x-cbid: 20011612-4275-0000-0000-0000039813C6
X-IBM-AV-DETECTION: SAVI=unused REMOTE=unused XFE=unused
x-cbparentid: 20011612-4276-0000-0000-000038AC129A
Message-Id: <20200116120513.2244-1-frankja@linux.ibm.com>
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.138,18.0.572
 definitions=2020-01-16_03:2020-01-16,2020-01-15 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 impostorscore=0 spamscore=0
 suspectscore=0 adultscore=0 priorityscore=1501 lowpriorityscore=0
 malwarescore=0 phishscore=0 mlxlogscore=465 bulkscore=0 mlxscore=0
 clxscore=1015 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.12.0-1910280000 definitions=main-2001160103
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Let's extend sigp reset testing and clean up the smp library as well.

GIT: https://github.com/frankjaa/kvm-unit-tests/tree/smp_cleanup

v2:
	* Added cpu stop to test_store_status()
	* Added smp_cpu_destroy() to the end of smp.c main()
	* New patch that prints cpu id on interrupt errors
	* New patch that reworks cpu start in the smp library (needed for lpar)
	* New patch that waits for cpu setup in smp_cpu_setup() (needed for lpar)
	* nullp is now an array

Janosch Frank (7):
  s390x: smp: Cleanup smp.c
  s390x: smp: Only use smp_cpu_setup once
  s390x: Add cpu id to interrupt error prints
  s390x: smp: Rework cpu start and active tracking
  s390x: smp: Wait for cpu setup to finish
  s390x: smp: Test all CRs on initial reset
  s390x: smp: Dirty fpc before initial reset test

 lib/s390x/interrupt.c | 20 +++++------
 lib/s390x/smp.c       | 47 +++++++++++++-----------
 s390x/cstart64.S      |  2 ++
 s390x/smp.c           | 84 +++++++++++++++++++++++++++++--------------
 4 files changed, 96 insertions(+), 57 deletions(-)
```
#### [PATCH 0/5] vDPA support
##### From: Jason Wang <jasowang@redhat.com>

```c
From patchwork Thu Jan 16 12:42:26 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Jason Wang <jasowang@redhat.com>
X-Patchwork-Id: 11336669
Return-Path: <SRS0=nLL1=3F=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 2E9AA1398
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 16 Jan 2020 12:42:57 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 0BC7C206E6
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 16 Jan 2020 12:42:57 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="e5PLuWH4"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726706AbgAPMm4 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 16 Jan 2020 07:42:56 -0500
Received: from us-smtp-delivery-1.mimecast.com ([205.139.110.120]:51320 "EHLO
        us-smtp-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org
        with ESMTP id S1726688AbgAPMmz (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 16 Jan 2020 07:42:55 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1579178575;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=WoZ0K4rRpiCW2qZjV/rJhDzQmCc+LfTgnMm+6gb2PKw=;
        b=e5PLuWH4GY8a3WNn6r9eqt5OPvBfw2AYbDBHeGNA3NaqiGOL6WvRVpkaHdqGwZLlxJnhGS
        TE+99FG5MnYzd9rMs2ZHuV6YOYUG8VMvlTdRTSa/tJuHYh/3ymvh2SnADZ/91JfAMMek0J
        LrImgMgsagkVeGMG7eNlT6uePpzlqrI=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-234-PcWvHHUMNVOFfEm04vtmnQ-1; Thu, 16 Jan 2020 07:42:52 -0500
X-MC-Unique: PcWvHHUMNVOFfEm04vtmnQ-1
Received: from smtp.corp.redhat.com (int-mx06.intmail.prod.int.phx2.redhat.com
 [10.5.11.16])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id A4009DB61;
        Thu, 16 Jan 2020 12:42:49 +0000 (UTC)
Received: from jason-ThinkPad-X1-Carbon-6th.redhat.com
 (ovpn-12-70.pek2.redhat.com [10.72.12.70])
        by smtp.corp.redhat.com (Postfix) with ESMTP id EBB995C1C3;
        Thu, 16 Jan 2020 12:42:33 +0000 (UTC)
From: Jason Wang <jasowang@redhat.com>
To: mst@redhat.com, jasowang@redhat.com, linux-kernel@vger.kernel.org,
        kvm@vger.kernel.org, virtualization@lists.linux-foundation.org,
        netdev@vger.kernel.org
Cc: tiwei.bie@intel.com, jgg@mellanox.com, maxime.coquelin@redhat.com,
        cunming.liang@intel.com, zhihong.wang@intel.com,
        rob.miller@broadcom.com, xiao.w.wang@intel.com,
        haotian.wang@sifive.com, lingshan.zhu@intel.com,
        eperezma@redhat.com, lulu@redhat.com, parav@mellanox.com,
        kevin.tian@intel.com, stefanha@redhat.com, rdunlap@infradead.org,
        hch@infradead.org, aadam@redhat.com, jakub.kicinski@netronome.com,
        jiri@mellanox.com, shahafs@mellanox.com, hanand@xilinx.com,
        mhabets@solarflare.com
Subject: [PATCH 0/5] vDPA support
Date: Thu, 16 Jan 2020 20:42:26 +0800
Message-Id: <20200116124231.20253-1-jasowang@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.16
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Hi all:

Based on the comments and discussion for mdev based hardware virtio
offloading support[1]. A different approach to support vDPA device is
proposed in this series.

Instead of leveraging VFIO/mdev which may not work for some
vendors. This series tries to introduce a dedicated vDPA bus and
leverage vhost for userspace drivers. This help for the devices that
are not fit for VFIO and may reduce the conflict when try to propose a
bus template for virtual devices in [1].

The vDPA support is split into following parts:

1) vDPA core (bus, device and driver abstraction)
2) virtio vDPA transport for kernel virtio driver to control vDPA
   device
3) vhost vDPA bus driver for userspace vhost driver to control vDPA
   device
4) vendor vDPA drivers
5) management API

Both 1) and 2) are included in this series. Tiwei will work on part
3). For 4), Ling Shan will work and post IFCVF driver. For 5) we leave
it to vendor to implement, but it's better to come into an agreement
for management to create/configure/destroy vDPA device.

The sample driver is kept but renamed to vdap_sim. An on-chip IOMMU
implementation is added to sample device to make it work for both
kernel virtio driver and userspace vhost driver. It implements a sysfs
based management API, but it can switch to any other (e.g devlink) if
necessary.

Please refer each patch for more information.

Comments are welcomed.

[1] https://lkml.org/lkml/2019/11/18/261

Jason Wang (5):
  vhost: factor out IOTLB
  vringh: IOTLB support
  vDPA: introduce vDPA bus
  virtio: introduce a vDPA based transport
  vdpasim: vDPA device simulator

 MAINTAINERS                    |   2 +
 drivers/vhost/Kconfig          |   7 +
 drivers/vhost/Kconfig.vringh   |   1 +
 drivers/vhost/Makefile         |   2 +
 drivers/vhost/net.c            |   2 +-
 drivers/vhost/vhost.c          | 221 +++------
 drivers/vhost/vhost.h          |  36 +-
 drivers/vhost/vhost_iotlb.c    | 171 +++++++
 drivers/vhost/vringh.c         | 434 +++++++++++++++++-
 drivers/virtio/Kconfig         |  15 +
 drivers/virtio/Makefile        |   2 +
 drivers/virtio/vdpa/Kconfig    |  26 ++
 drivers/virtio/vdpa/Makefile   |   3 +
 drivers/virtio/vdpa/vdpa.c     | 141 ++++++
 drivers/virtio/vdpa/vdpa_sim.c | 796 +++++++++++++++++++++++++++++++++
 drivers/virtio/virtio_vdpa.c   | 400 +++++++++++++++++
 include/linux/vdpa.h           | 191 ++++++++
 include/linux/vhost_iotlb.h    |  45 ++
 include/linux/vringh.h         |  36 ++
 19 files changed, 2327 insertions(+), 204 deletions(-)
 create mode 100644 drivers/vhost/vhost_iotlb.c
 create mode 100644 drivers/virtio/vdpa/Kconfig
 create mode 100644 drivers/virtio/vdpa/Makefile
 create mode 100644 drivers/virtio/vdpa/vdpa.c
 create mode 100644 drivers/virtio/vdpa/vdpa_sim.c
 create mode 100644 drivers/virtio/virtio_vdpa.c
 create mode 100644 include/linux/vdpa.h
 create mode 100644 include/linux/vhost_iotlb.h
```
#### [PATCH v3 0/8] KVM: arm64: vCPU preempted check support
##### From: Zengruan Ye <yezengruan@huawei.com>

```c
From patchwork Thu Jan 16 12:46:18 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Zengruan Ye <yezengruan@huawei.com>
X-Patchwork-Id: 11336693
Return-Path: <SRS0=nLL1=3F=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 092E913B4
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 16 Jan 2020 12:47:25 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id E566F206D5
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 16 Jan 2020 12:47:24 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726924AbgAPMq6 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 16 Jan 2020 07:46:58 -0500
Received: from szxga04-in.huawei.com ([45.249.212.190]:9640 "EHLO huawei.com"
        rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org with ESMTP
        id S1726406AbgAPMq5 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 16 Jan 2020 07:46:57 -0500
Received: from DGGEMS401-HUB.china.huawei.com (unknown [172.30.72.59])
        by Forcepoint Email with ESMTP id 9C97F30E39BD4543FFB2;
        Thu, 16 Jan 2020 20:46:54 +0800 (CST)
Received: from DESKTOP-1NISPDV.china.huawei.com (10.173.221.248) by
 DGGEMS401-HUB.china.huawei.com (10.3.19.201) with Microsoft SMTP Server id
 14.3.439.0; Thu, 16 Jan 2020 20:46:44 +0800
From: Zengruan Ye <yezengruan@huawei.com>
To: <linux-kernel@vger.kernel.org>,
        <linux-arm-kernel@lists.infradead.org>,
        <kvmarm@lists.cs.columbia.edu>, <kvm@vger.kernel.org>,
        <linux-doc@vger.kernel.org>,
        <virtualization@lists.linux-foundation.org>
CC: <yezengruan@huawei.com>, <maz@kernel.org>, <james.morse@arm.com>,
        <linux@armlinux.org.uk>, <suzuki.poulose@arm.com>,
        <julien.thierry.kdev@gmail.com>, <catalin.marinas@arm.com>,
        <mark.rutland@arm.com>, <will@kernel.org>, <steven.price@arm.com>,
        <daniel.lezcano@linaro.org>, <wanghaibin.wang@huawei.com>,
        <peterz@infradead.org>, <longman@redhat.com>
Subject: [PATCH v3 0/8] KVM: arm64: vCPU preempted check support
Date: Thu, 16 Jan 2020 20:46:18 +0800
Message-ID: <20200116124626.1155-1-yezengruan@huawei.com>
X-Mailer: git-send-email 2.23.0.windows.1
MIME-Version: 1.0
X-Originating-IP: [10.173.221.248]
X-CFilter-Loop: Reflected
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This patch set aims to support the vcpu_is_preempted() functionality
under KVM/arm64, which allowing the guest to obtain the vCPU is
currently running or not. This will enhance lock performance on
overcommitted hosts (more runnable vCPUs than physical CPUs in the
system) as doing busy waits for preempted vCPUs will hurt system
performance far worse than early yielding.

We have observed some performace improvements in uninx benchmark tests.

unix benchmark result:
  host:  kernel 5.5.0-rc5, HiSilicon Kunpeng920, 8 CPUs
  guest: kernel 5.5.0-rc5, 16 vCPUs

               test-case                |    after-patch    |   before-patch
----------------------------------------+-------------------+------------------
 Dhrystone 2 using register variables   | 334600751.0 lps   | 335319028.3 lps
 Double-Precision Whetstone             |     32856.1 MWIPS |     32849.6 MWIPS
 Execl Throughput                       |      3662.1 lps   |      2718.0 lps
 File Copy 1024 bufsize 2000 maxblocks  |    432906.4 KBps  |    158011.8 KBps
 File Copy 256 bufsize 500 maxblocks    |    116023.0 KBps  |     37664.0 KBps
 File Copy 4096 bufsize 8000 maxblocks  |   1432769.8 KBps  |    441108.8 KBps
 Pipe Throughput                        |   6405029.6 lps   |   6021457.6 lps
 Pipe-based Context Switching           |    185872.7 lps   |    184255.3 lps
 Process Creation                       |      4025.7 lps   |      3706.6 lps
 Shell Scripts (1 concurrent)           |      6745.6 lpm   |      6436.1 lpm
 Shell Scripts (8 concurrent)           |       998.7 lpm   |       931.1 lpm
 System Call Overhead                   |   3913363.1 lps   |   3883287.8 lps
----------------------------------------+-------------------+------------------
 System Benchmarks Index Score          |      1835.1       |      1327.6

Changes from v2:
https://lore.kernel.org/lkml/20191226135833.1052-1-yezengruan@huawei.com/
 * Post Will's patches as part of this series [1][2], and add the
   probing logic for checking whether the hypervisor is KVM or not
 * Clear PV-lock interface documentation
 * Remove preempted state field
 * Fix build error when CONFIG_PARAVIRT is not set
 * Bunch of typo fixes.

Changes from v1:
https://lore.kernel.org/lkml/20191217135549.3240-1-yezengruan@huawei.com/
 * Guest kernel no longer allocates the PV lock structure, instead it
   is allocated by user space to avoid lifetime issues about kexec.
 * Provide vCPU attributes for PV lock.
 * Update SMC number of PV lock features.
 * Report some basic validation when PV lock init.
 * Document preempted field.
 * Bunch of typo fixes.

[1] https://git.kernel.org/pub/scm/linux/kernel/git/will/linux.git/commit/?h=kvm/hvc&id=464f5a1741e5959c3e4d2be1966ae0093b4dce06

[2] https://git.kernel.org/pub/scm/linux/kernel/git/will/linux.git/commit/?h=kvm/hvc&id=6597490e005d0eeca8ed8c1c1d7b4318ee014681

Will Deacon (2):
  arm64: Probe for the presence of KVM hypervisor services during boot
  arm/arm64: KVM: Advertise KVM UID to guests via SMCCC

Zengruan Ye (6):
  KVM: arm64: Document PV-lock interface
  KVM: arm64: Add SMCCC paravirtualised lock calls
  KVM: arm64: Support pvlock preempted via shared structure
  KVM: arm64: Provide vCPU attributes for PV lock
  KVM: arm64: Add interface to support vCPU preempted check
  KVM: arm64: Support the vCPU preemption check

 Documentation/virt/kvm/arm/pvlock.rst   |  68 +++++++++++++
 Documentation/virt/kvm/devices/vcpu.txt |  14 +++
 arch/arm/include/asm/kvm_host.h         |  18 ++++
 arch/arm64/include/asm/hypervisor.h     |  11 ++
 arch/arm64/include/asm/kvm_host.h       |  27 +++++
 arch/arm64/include/asm/paravirt.h       |  15 +++
 arch/arm64/include/asm/pvlock-abi.h     |  16 +++
 arch/arm64/include/asm/spinlock.h       |   9 ++
 arch/arm64/include/uapi/asm/kvm.h       |   2 +
 arch/arm64/kernel/Makefile              |   2 +-
 arch/arm64/kernel/paravirt-spinlocks.c  |  13 +++
 arch/arm64/kernel/paravirt.c            | 129 +++++++++++++++++++++++-
 arch/arm64/kernel/setup.c               |  37 +++++++
 arch/arm64/kvm/Makefile                 |   1 +
 arch/arm64/kvm/guest.c                  |   9 ++
 include/linux/arm-smccc.h               |  36 +++++++
 include/linux/cpuhotplug.h              |   1 +
 include/uapi/linux/kvm.h                |   2 +
 virt/kvm/arm/arm.c                      |   8 ++
 virt/kvm/arm/hypercalls.c               |  54 +++++++---
 virt/kvm/arm/pvlock.c                   | 102 +++++++++++++++++++
 21 files changed, 559 insertions(+), 15 deletions(-)
 create mode 100644 Documentation/virt/kvm/arm/pvlock.rst
 create mode 100644 arch/arm64/include/asm/pvlock-abi.h
 create mode 100644 arch/arm64/kernel/paravirt-spinlocks.c
 create mode 100644 virt/kvm/arm/pvlock.c
```
#### [RFC PATCH 0/3] vfio/type1: Reduce vfio_iommu.lock contention
##### From: Alex Williamson <alex.williamson@redhat.com>

```c
From patchwork Thu Jan 16 18:17:49 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Alex Williamson <alex.williamson@redhat.com>
X-Patchwork-Id: 11337537
Return-Path: <SRS0=nLL1=3F=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 2117A14B7
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 16 Jan 2020 18:18:04 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 0062B2073A
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 16 Jan 2020 18:18:03 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="MCMP8aKt"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2387958AbgAPSSD (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 16 Jan 2020 13:18:03 -0500
Received: from us-smtp-delivery-1.mimecast.com ([205.139.110.120]:36775 "EHLO
        us-smtp-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org
        with ESMTP id S2404253AbgAPSR5 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 16 Jan 2020 13:17:57 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1579198676;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:content-type:content-type:
         content-transfer-encoding:content-transfer-encoding;
        bh=t3VlM5eWHxNK3W2wSrtp5Pl0J5UynFugOHYM0lHZotI=;
        b=MCMP8aKtmhJ9hHoIca3ND1Foz/tXeXOu3vJpf3Uua8HkjxSKtroeAvvUrtGLr+wyvmxZzk
        nuFaor1SwiOCTY3ZGmxQoXnHfJtvALgdZVlv7CoKBArg68UmVkPKIXw7qxqOhlYYrJls0b
        nnKHkk9zoSZGI1Gqp4+9x0PcmFbbqek=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-276-aZJcF4RYP-a0nsHacWQwpA-1; Thu, 16 Jan 2020 13:17:53 -0500
X-MC-Unique: aZJcF4RYP-a0nsHacWQwpA-1
Received: from smtp.corp.redhat.com (int-mx06.intmail.prod.int.phx2.redhat.com
 [10.5.11.16])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 5FD4C18C35A0;
        Thu, 16 Jan 2020 18:17:52 +0000 (UTC)
Received: from gimli.home (ovpn-116-28.phx2.redhat.com [10.3.116.28])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 1A8AC5C241;
        Thu, 16 Jan 2020 18:17:49 +0000 (UTC)
Subject: [RFC PATCH 0/3] vfio/type1: Reduce vfio_iommu.lock contention
From: Alex Williamson <alex.williamson@redhat.com>
To: yan.y.zhao@intel.com
Cc: kvm@vger.kernel.org, linux-kernel@vger.kernel.org
Date: Thu, 16 Jan 2020 11:17:49 -0700
Message-ID: <157919849533.21002.4782774695733669879.stgit@gimli.home>
User-Agent: StGit/0.19-dirty
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.16
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Hi Yan,

I wonder if this might reduce the lock contention you're seeing in the
vfio_dma_rw series.  These are only compile tested on my end, so I hope
they're not too broken to test.  Thanks,

Alex
---

Alex Williamson (3):
      vfio/type1: Convert vfio_iommu.lock from mutex to rwsem
      vfio/type1: Replace obvious read lock instances
      vfio/type1: Introduce pfn_list mutex


 drivers/vfio/vfio_iommu_type1.c |   67 ++++++++++++++++++++++++---------------
 1 file changed, 41 insertions(+), 26 deletions(-)
```
#### [PATCH net-next 0/3] vsock: support network namespace
##### From: Stefano Garzarella <sgarzare@redhat.com>

```c
From patchwork Thu Jan 16 17:24:25 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Stefano Garzarella <sgarzare@redhat.com>
X-Patchwork-Id: 11337565
Return-Path: <SRS0=nLL1=3F=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id EE8BC92A
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 16 Jan 2020 18:33:57 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id CEEE3208C3
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 16 Jan 2020 18:33:57 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="XJinJ0kC"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2436739AbgAPSdw (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 16 Jan 2020 13:33:52 -0500
Received: from us-smtp-1.mimecast.com ([205.139.110.61]:51082 "EHLO
        us-smtp-delivery-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S2403805AbgAPRYq (ORCPT
        <rfc822;kvm@vger.kernel.org>); Thu, 16 Jan 2020 12:24:46 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1579195485;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=L1usH87y9Hi/ZiYHMXoHuhdmW1E/8d47ArLsZBDzX7o=;
        b=XJinJ0kCHyHfEdMKr9DwZZk5Js+UaAI/mIyiqZFM7u+NaTHK0Gp9c8GYI/bKEw3ftfisH4
        Tomc0I9edkmGHe3lL1XoUx7YOn42wgRqabaQzsWz/zHet9DZabRo/JzqNrEqwHAkkMYLqw
        MmMwUVWa3qCol1gNEMzhsOG0tFeEthQ=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-206-dO0yLECUNPe09s1O855Low-1; Thu, 16 Jan 2020 12:24:44 -0500
X-MC-Unique: dO0yLECUNPe09s1O855Low-1
Received: from smtp.corp.redhat.com (int-mx06.intmail.prod.int.phx2.redhat.com
 [10.5.11.16])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 397941137843;
        Thu, 16 Jan 2020 17:24:42 +0000 (UTC)
Received: from steredhat.redhat.com (ovpn-117-242.ams2.redhat.com
 [10.36.117.242])
        by smtp.corp.redhat.com (Postfix) with ESMTP id ACF8C5C28F;
        Thu, 16 Jan 2020 17:24:30 +0000 (UTC)
From: Stefano Garzarella <sgarzare@redhat.com>
To: davem@davemloft.net, netdev@vger.kernel.org
Cc: linux-kernel@vger.kernel.org, Jorgen Hansen <jhansen@vmware.com>,
        Jason Wang <jasowang@redhat.com>, kvm@vger.kernel.org,
        Stefan Hajnoczi <stefanha@redhat.com>,
        Stefano Garzarella <sgarzare@redhat.com>,
        virtualization@lists.linux-foundation.org,
        linux-hyperv@vger.kernel.org,
        "Michael S. Tsirkin" <mst@redhat.com>,
        Dexuan Cui <decui@microsoft.com>
Subject: [PATCH net-next 0/3] vsock: support network namespace
Date: Thu, 16 Jan 2020 18:24:25 +0100
Message-Id: <20200116172428.311437-1-sgarzare@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.16
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

RFC -> v1:
 * added 'netns' module param to vsock.ko to enable the
   network namespace support (disabled by default)
 * added 'vsock_net_eq()' to check the "net" assigned to a socket
   only when 'netns' support is enabled

RFC: https://patchwork.ozlabs.org/cover/1202235/

Now that we have multi-transport upstream, I started to take a look to
support network namespace in vsock.

As we partially discussed in the multi-transport proposal [1], it could
be nice to support network namespace in vsock to reach the following
goals:
- isolate host applications from guest applications using the same ports
  with CID_ANY
- assign the same CID of VMs running in different network namespaces
- partition VMs between VMMs or at finer granularity

This new feature is disabled by default, because it changes vsock's
behavior with network namespaces and could break existing applications.
It can be enabled with the new 'netns' module parameter of vsock.ko.

This implementation provides the following behavior:
- packets received from the host (received by G2H transports) are
  assigned to the default netns (init_net)
- packets received from the guest (received by H2G - vhost-vsock) are
  assigned to the netns of the process that opens /dev/vhost-vsock
  (usually the VMM, qemu in my tests, opens the /dev/vhost-vsock)
    - for vmci I need some suggestions, because I don't know how to do
      and test the same in the vmci driver, for now vmci uses the
      init_net
- loopback packets are exchanged only in the same netns

I tested the series in this way:
l0_host$ qemu-system-x86_64 -m 4G -M accel=kvm -smp 4 \
            -drive file=/tmp/vsockvm0.img,if=virtio --nographic \
            -device vhost-vsock-pci,guest-cid=3

l1_vm$ echo 1 > /sys/module/vsock/parameters/netns

l1_vm$ ip netns add ns1
l1_vm$ ip netns add ns2
 # same CID on different netns
l1_vm$ ip netns exec ns1 qemu-system-x86_64 -m 1G -M accel=kvm -smp 2 \
            -drive file=/tmp/vsockvm1.img,if=virtio --nographic \
            -device vhost-vsock-pci,guest-cid=4
l1_vm$ ip netns exec ns2 qemu-system-x86_64 -m 1G -M accel=kvm -smp 2 \
            -drive file=/tmp/vsockvm2.img,if=virtio --nographic \
            -device vhost-vsock-pci,guest-cid=4

 # all iperf3 listen on CID_ANY and port 5201, but in different netns
l1_vm$ ./iperf3 --vsock -s # connection from l0 or guests started
                           # on default netns (init_net)
l1_vm$ ip netns exec ns1 ./iperf3 --vsock -s
l1_vm$ ip netns exec ns1 ./iperf3 --vsock -s

l0_host$ ./iperf3 --vsock -c 3
l2_vm1$ ./iperf3 --vsock -c 2
l2_vm2$ ./iperf3 --vsock -c 2

[1] https://www.spinics.net/lists/netdev/msg575792.html

Stefano Garzarella (3):
  vsock: add network namespace support
  vsock/virtio_transport_common: handle netns of received packets
  vhost/vsock: use netns of process that opens the vhost-vsock device

 drivers/vhost/vsock.c                   | 29 ++++++++++++-----
 include/linux/virtio_vsock.h            |  2 ++
 include/net/af_vsock.h                  |  7 +++--
 net/vmw_vsock/af_vsock.c                | 41 +++++++++++++++++++------
 net/vmw_vsock/hyperv_transport.c        |  5 +--
 net/vmw_vsock/virtio_transport.c        |  2 ++
 net/vmw_vsock/virtio_transport_common.c | 12 ++++++--
 net/vmw_vsock/vmci_transport.c          |  5 +--
 8 files changed, 78 insertions(+), 25 deletions(-)
```
