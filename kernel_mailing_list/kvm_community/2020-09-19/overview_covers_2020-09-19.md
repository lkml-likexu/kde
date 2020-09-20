

#### [PATCH 0/4] Pass zPCI hardware information via VFIO
##### From: Matthew Rosato <mjrosato@linux.ibm.com>

```c
From patchwork Sat Sep 19 15:28:34 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Matthew Rosato <mjrosato@linux.ibm.com>
X-Patchwork-Id: 11787029
Return-Path: <SRS0=KWAa=C4=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 942656CA
	for <patchwork-kvm@patchwork.kernel.org>;
 Sat, 19 Sep 2020 15:28:51 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 782482100A
	for <patchwork-kvm@patchwork.kernel.org>;
 Sat, 19 Sep 2020 15:28:51 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=ibm.com header.i=@ibm.com
 header.b="gGlU2o3Z"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726528AbgISP2r (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Sat, 19 Sep 2020 11:28:47 -0400
Received: from mx0a-001b2d01.pphosted.com ([148.163.156.1]:63292 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1726449AbgISP2r (ORCPT
        <rfc822;kvm@vger.kernel.org>); Sat, 19 Sep 2020 11:28:47 -0400
Received: from pps.filterd (m0098410.ppops.net [127.0.0.1])
        by mx0a-001b2d01.pphosted.com (8.16.0.42/8.16.0.42) with SMTP id
 08JF33g2115289;
        Sat, 19 Sep 2020 11:28:46 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=ibm.com;
 h=from : to : cc : subject
 : date : message-id; s=pp1;
 bh=F5IPuoRy4PpWgpmKafbX47Ict4OA/+gedW/oss+a8mw=;
 b=gGlU2o3Z4EBj991M4DTn898NEQ445s1pscwnU45peq9y8oThQsSQvpc3AO3zGrmpVKWq
 G6teYq6PqSrw8eir0nGk23XpRVKxhFBBCd5m+5lbiOtUNpsl2Rjtmu+BkERUvzyePm+A
 q6uR/Z4i0Gi1rArml53V/D3NTVNvYc5McEFpDhm6c+fNp2nLtQxPRicL14Vgr0WTGaQB
 iqqHcZejGBhsmtLkkHA0Yx7Debud0iukm9TwPyRAVF450/RTpN2unYxgHQdFBHfRgsK2
 tsS2xqVJRYArWcAoktRNWyGG2LvzafjmYkcB3Vy8zhOY6mVfPLygoPFqsMyKytRO26BP Tw==
Received: from pps.reinject (localhost [127.0.0.1])
        by mx0a-001b2d01.pphosted.com with ESMTP id 33nk87hhby-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Sat, 19 Sep 2020 11:28:46 -0400
Received: from m0098410.ppops.net (m0098410.ppops.net [127.0.0.1])
        by pps.reinject (8.16.0.36/8.16.0.36) with SMTP id 08JFSkfM022814;
        Sat, 19 Sep 2020 11:28:46 -0400
Received: from ppma01wdc.us.ibm.com (fd.55.37a9.ip4.static.sl-reverse.com
 [169.55.85.253])
        by mx0a-001b2d01.pphosted.com with ESMTP id 33nk87hhbp-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Sat, 19 Sep 2020 11:28:45 -0400
Received: from pps.filterd (ppma01wdc.us.ibm.com [127.0.0.1])
        by ppma01wdc.us.ibm.com (8.16.0.42/8.16.0.42) with SMTP id
 08JFS6G6019802;
        Sat, 19 Sep 2020 15:28:44 GMT
Received: from b03cxnp08025.gho.boulder.ibm.com
 (b03cxnp08025.gho.boulder.ibm.com [9.17.130.17])
        by ppma01wdc.us.ibm.com with ESMTP id 33n9m8b6s0-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Sat, 19 Sep 2020 15:28:44 +0000
Received: from b03ledav005.gho.boulder.ibm.com
 (b03ledav005.gho.boulder.ibm.com [9.17.130.236])
        by b03cxnp08025.gho.boulder.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id 08JFScfJ60555674
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Sat, 19 Sep 2020 15:28:38 GMT
Received: from b03ledav005.gho.boulder.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id A6439BE054;
        Sat, 19 Sep 2020 15:28:41 +0000 (GMT)
Received: from b03ledav005.gho.boulder.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 87370BE053;
        Sat, 19 Sep 2020 15:28:40 +0000 (GMT)
Received: from oc4221205838.ibm.com (unknown [9.211.74.107])
        by b03ledav005.gho.boulder.ibm.com (Postfix) with ESMTP;
        Sat, 19 Sep 2020 15:28:40 +0000 (GMT)
From: Matthew Rosato <mjrosato@linux.ibm.com>
To: alex.williamson@redhat.com, cohuck@redhat.com,
        schnelle@linux.ibm.com
Cc: pmorel@linux.ibm.com, borntraeger@de.ibm.com, hca@linux.ibm.com,
        gor@linux.ibm.com, gerald.schaefer@linux.ibm.com,
        linux-s390@vger.kernel.org, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org
Subject: [PATCH 0/4] Pass zPCI hardware information via VFIO
Date: Sat, 19 Sep 2020 11:28:34 -0400
Message-Id: <1600529318-8996-1-git-send-email-mjrosato@linux.ibm.com>
X-Mailer: git-send-email 1.8.3.1
X-TM-AS-GCONF: 00
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.235,18.0.687
 definitions=2020-09-19_05:2020-09-16,2020-09-19 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 malwarescore=0 suspectscore=0
 clxscore=1015 impostorscore=0 mlxscore=0 spamscore=0 priorityscore=1501
 bulkscore=0 lowpriorityscore=0 adultscore=0 mlxlogscore=887 phishscore=0
 classifier=spam adjust=0 reason=mlx scancount=1 engine=8.12.0-2006250000
 definitions=main-2009190131
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This patchset provides a means by which hardware information about the
underlying PCI device can be passed up to userspace (ie, QEMU) so that
this hardware information can be used rather than previously hard-coded
assumptions. A new VFIO region type is defined which holds this
information. 

A form of these patches saw some rounds last year but has been back-
tabled for a while.  The original work for this feature was done by Pierre
Morel. I'd like to refresh the discussion on this and get this finished up
so that we can move forward with better-supporting additional types of
PCI-attached devices.  The proposal here presents a completely different
region mapping vs the prior approach, taking inspiration from vfio info
capability chains to provide device CLP information in a way that allows 
for future expansion (new CLP features).

This feature is toggled via the CONFIG_VFIO_PCI_ZDEV configuration entry.

Matthew Rosato (4):
  s390/pci: stash version in the zpci_dev
  s390/pci: track whether util_str is valid in the zpci_dev
  vfio-pci/zdev: define the vfio_zdev header
  vfio-pci/zdev: use a device region to retrieve zPCI information

 arch/s390/include/asm/pci.h         |   4 +-
 arch/s390/pci/pci_clp.c             |   2 +
 drivers/vfio/pci/Kconfig            |  13 ++
 drivers/vfio/pci/Makefile           |   1 +
 drivers/vfio/pci/vfio_pci.c         |   8 ++
 drivers/vfio/pci/vfio_pci_private.h |  10 ++
 drivers/vfio/pci/vfio_pci_zdev.c    | 242 ++++++++++++++++++++++++++++++++++++
 include/uapi/linux/vfio.h           |   5 +
 include/uapi/linux/vfio_zdev.h      | 116 +++++++++++++++++
 9 files changed, 400 insertions(+), 1 deletion(-)
 create mode 100644 drivers/vfio/pci/vfio_pci_zdev.c
 create mode 100644 include/uapi/linux/vfio_zdev.h
```
#### [PATCH 0/7] Retrieve zPCI hardware information from VFIO
##### From: Matthew Rosato <mjrosato@linux.ibm.com>

```c
From patchwork Sat Sep 19 15:34:25 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Matthew Rosato <mjrosato@linux.ibm.com>
X-Patchwork-Id: 11787039
Return-Path: <SRS0=KWAa=C4=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 2D4E9618
	for <patchwork-kvm@patchwork.kernel.org>;
 Sat, 19 Sep 2020 15:35:03 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id F3ED82100A
	for <patchwork-kvm@patchwork.kernel.org>;
 Sat, 19 Sep 2020 15:35:02 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=ibm.com header.i=@ibm.com
 header.b="Pr548/Y7"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726549AbgISPfB (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Sat, 19 Sep 2020 11:35:01 -0400
Received: from mx0b-001b2d01.pphosted.com ([148.163.158.5]:32326 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S1726493AbgISPfB (ORCPT
        <rfc822;kvm@vger.kernel.org>); Sat, 19 Sep 2020 11:35:01 -0400
Received: from pps.filterd (m0098413.ppops.net [127.0.0.1])
        by mx0b-001b2d01.pphosted.com (8.16.0.42/8.16.0.42) with SMTP id
 08JFWQva122398;
        Sat, 19 Sep 2020 11:34:40 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=ibm.com;
 h=from : to : cc : subject
 : date : message-id; s=pp1;
 bh=Nz7EIAmjTHE8p8vA1pGiLUfb76hGCXkomL4v8MnpNCY=;
 b=Pr548/Y7lwBJMIKDlp7bUHMdlO/vxjVvvP636IjpeYdZr1IKwuFYduIq2dTt/hOWsHgS
 zNTR+paAJjAOsI89uPAHfu5VlqG6Ai9wzUvh8xpsRLwH8lvaQtoq4RKFjJN7BECP/2ZJ
 6EFyEAnWB/KsK1i0qmr3K2im5PGqsJjcYM1qQ4F8AgN9ksj7UvsXV/1cqv1RQ6LFfNWJ
 5lxlxSXHYJnB+RtPRCHSiGnRHHz9rxZsZ00krNhacwojK432zNCu0qf5CVjQ3srkhxSm
 pnMLeVL9ROrZtEyy0tsjAxukynEkXsSINyaSXrdbuMyXECzSrzRhDa3h0n80KpS+YuZP lQ==
Received: from pps.reinject (localhost [127.0.0.1])
        by mx0b-001b2d01.pphosted.com with ESMTP id 33ng7h4t68-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Sat, 19 Sep 2020 11:34:40 -0400
Received: from m0098413.ppops.net (m0098413.ppops.net [127.0.0.1])
        by pps.reinject (8.16.0.36/8.16.0.36) with SMTP id 08JFWlqO123959;
        Sat, 19 Sep 2020 11:34:40 -0400
Received: from ppma02dal.us.ibm.com (a.bd.3ea9.ip4.static.sl-reverse.com
 [169.62.189.10])
        by mx0b-001b2d01.pphosted.com with ESMTP id 33ng7h4t62-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Sat, 19 Sep 2020 11:34:40 -0400
Received: from pps.filterd (ppma02dal.us.ibm.com [127.0.0.1])
        by ppma02dal.us.ibm.com (8.16.0.42/8.16.0.42) with SMTP id
 08JFQuFc003319;
        Sat, 19 Sep 2020 15:34:39 GMT
Received: from b03cxnp07029.gho.boulder.ibm.com
 (b03cxnp07029.gho.boulder.ibm.com [9.17.130.16])
        by ppma02dal.us.ibm.com with ESMTP id 33n9m8c1b6-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Sat, 19 Sep 2020 15:34:39 +0000
Received: from b03ledav004.gho.boulder.ibm.com
 (b03ledav004.gho.boulder.ibm.com [9.17.130.235])
        by b03cxnp07029.gho.boulder.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id 08JFYbsn2294362
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Sat, 19 Sep 2020 15:34:37 GMT
Received: from b03ledav004.gho.boulder.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 938BA7805E;
        Sat, 19 Sep 2020 15:34:37 +0000 (GMT)
Received: from b03ledav004.gho.boulder.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 3C07D7805C;
        Sat, 19 Sep 2020 15:34:36 +0000 (GMT)
Received: from oc4221205838.ibm.com (unknown [9.211.74.107])
        by b03ledav004.gho.boulder.ibm.com (Postfix) with ESMTP;
        Sat, 19 Sep 2020 15:34:36 +0000 (GMT)
From: Matthew Rosato <mjrosato@linux.ibm.com>
To: cohuck@redhat.com, thuth@redhat.com
Cc: pmorel@linux.ibm.com, schnelle@linux.ibm.com, rth@twiddle.net,
        david@redhat.com, pasic@linux.ibm.com, borntraeger@de.ibm.com,
        mst@redhat.com, pbonzini@redhat.com, alex.williamson@redhat.com,
        qemu-s390x@nongnu.org, qemu-devel@nongnu.org, kvm@vger.kernel.org
Subject: [PATCH 0/7] Retrieve zPCI hardware information from VFIO
Date: Sat, 19 Sep 2020 11:34:25 -0400
Message-Id: <1600529672-10243-1-git-send-email-mjrosato@linux.ibm.com>
X-Mailer: git-send-email 1.8.3.1
X-TM-AS-GCONF: 00
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.235,18.0.687
 definitions=2020-09-19_05:2020-09-16,2020-09-19 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 malwarescore=0 phishscore=0
 mlxlogscore=999 mlxscore=0 clxscore=1015 lowpriorityscore=0 spamscore=0
 priorityscore=1501 suspectscore=0 impostorscore=0 adultscore=0 bulkscore=0
 classifier=spam adjust=0 reason=mlx scancount=1 engine=8.12.0-2006250000
 definitions=main-2009190131
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This patchset exploits the VFIO ZPCI CLP region, which provides hardware
information about passed-through s390 PCI devices that can be shared with
the guest.

The retrieval of this information is done once per function (and for a
subset of data, once per function group) and is performed at time of device
plug.  Some elements provided in the CLP region must still be forced to
default values for now to reflect what QEMU actually provides support for.

The original work for this feature was done by Pierre Morel.

Note: This patchset will overlap with "s390x/pci: Accomodate vfio DMA
limiting" because they both add hw/s390x/s390-pci-vfio.* - This is
intentional as both patchsets add functionality that belongs in these new
files.  Once one set is taken, I'll rebase the other on top of it.

Associated kernel patchset:
https://marc.info/?l=kvm&m=160052933112238&w=2

Matthew Rosato (4):
  update-linux-headers: Add vfio_zdev.h
  linux-headers: update against 5.9-rc5
  s390x/pci: clean up s390 PCI groups
  s390x/pci: get zPCI function info from host

Pierre Morel (3):
  s390x/pci: create a header dedicated to PCI CLP
  s390x/pci: use a PCI Group structure
  s390x/pci: use a PCI Function structure

 hw/s390x/meson.build                               |   1 +
 hw/s390x/s390-pci-bus.c                            |  82 ++++++-
 hw/s390x/s390-pci-bus.h                            |  13 ++
 hw/s390x/s390-pci-clp.h                            | 215 +++++++++++++++++++
 hw/s390x/s390-pci-inst.c                           |  28 +--
 hw/s390x/s390-pci-inst.h                           | 196 -----------------
 hw/s390x/s390-pci-vfio.c                           | 235 +++++++++++++++++++++
 hw/s390x/s390-pci-vfio.h                           |  19 ++
 include/standard-headers/drm/drm_fourcc.h          | 140 ++++++++++++
 include/standard-headers/linux/ethtool.h           |  87 ++++++++
 include/standard-headers/linux/input-event-codes.h |   3 +-
 include/standard-headers/linux/vhost_types.h       |  11 +
 include/standard-headers/linux/virtio_9p.h         |   4 +-
 include/standard-headers/linux/virtio_blk.h        |  26 +--
 include/standard-headers/linux/virtio_config.h     |   8 +-
 include/standard-headers/linux/virtio_console.h    |   8 +-
 include/standard-headers/linux/virtio_net.h        |   6 +-
 include/standard-headers/linux/virtio_scsi.h       |  20 +-
 linux-headers/asm-generic/unistd.h                 |   6 +-
 linux-headers/asm-mips/unistd_n32.h                |   1 +
 linux-headers/asm-mips/unistd_n64.h                |   1 +
 linux-headers/asm-mips/unistd_o32.h                |   1 +
 linux-headers/asm-powerpc/kvm.h                    |   5 +
 linux-headers/asm-powerpc/unistd_32.h              |   1 +
 linux-headers/asm-powerpc/unistd_64.h              |   1 +
 linux-headers/asm-s390/kvm.h                       |   7 +-
 linux-headers/asm-s390/unistd_32.h                 |   1 +
 linux-headers/asm-s390/unistd_64.h                 |   1 +
 linux-headers/asm-x86/unistd_32.h                  |   1 +
 linux-headers/asm-x86/unistd_64.h                  |   1 +
 linux-headers/asm-x86/unistd_x32.h                 |   1 +
 linux-headers/linux/kvm.h                          |  10 +-
 linux-headers/linux/vfio.h                         |   7 +-
 linux-headers/linux/vfio_zdev.h                    | 116 ++++++++++
 linux-headers/linux/vhost.h                        |   2 +
 scripts/update-linux-headers.sh                    |   2 +-
 36 files changed, 1007 insertions(+), 260 deletions(-)
 create mode 100644 hw/s390x/s390-pci-clp.h
 create mode 100644 hw/s390x/s390-pci-vfio.c
 create mode 100644 hw/s390x/s390-pci-vfio.h
 create mode 100644 linux-headers/linux/vfio_zdev.h
```
