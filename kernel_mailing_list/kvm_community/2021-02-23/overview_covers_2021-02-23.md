

#### [RFC v4 00/11] Introduce VDUSE - vDPA Device in Userspace
##### From: Xie Yongji <xieyongji@bytedance.com>

```c
From patchwork Tue Feb 23 11:50:37 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Xie Yongji <xieyongji@bytedance.com>
X-Patchwork-Id: 12100211
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.8 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_PATCH,MAILING_LIST_MULTI,
	MENTIONS_GIT_HOSTING,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT
	autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 2128FC433DB
	for <kvm@archiver.kernel.org>; Tue, 23 Feb 2021 11:53:37 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id C3AB264E32
	for <kvm@archiver.kernel.org>; Tue, 23 Feb 2021 11:53:36 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S232431AbhBWLx2 (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 23 Feb 2021 06:53:28 -0500
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:51718 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S232452AbhBWLwc (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 23 Feb 2021 06:52:32 -0500
Received: from mail-pj1-x1029.google.com (mail-pj1-x1029.google.com
 [IPv6:2607:f8b0:4864:20::1029])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 72A66C061574
        for <kvm@vger.kernel.org>; Tue, 23 Feb 2021 03:51:46 -0800 (PST)
Received: by mail-pj1-x1029.google.com with SMTP id t5so1514017pjd.0
        for <kvm@vger.kernel.org>; Tue, 23 Feb 2021 03:51:46 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=bytedance-com.20150623.gappssmtp.com; s=20150623;
        h=from:to:cc:subject:date:message-id:mime-version
         :content-transfer-encoding;
        bh=Xdz76Pr5X2U4qGHNaBUqTnUQFn7wjtLgR16d6odDiDY=;
        b=KqAJzp4Ub9NgdWZX0Vx+kHhWD2qcuxAU6AlaIr1cTEa34WXruEbOqzAduVnsyuTiVq
         Qrj6vhsW64HXdsYLwgt1DG1lA+9TBfZc692wNCowM9cPgj7jJnYpvmm/cvgJvHoJExvV
         Xxv9RFF5PRqatMwzSs7jXOqar4QnqNbmRljz1DSrtU5dIG0PRZ6lgyriHVoG9LQCpKAG
         CPGyxiEwaf+JQABA6jerjDMlAAj+c7c0yRibE9YyayEvUVlVTFEnuSSb1M8pu50stbnL
         LGbS+/8NrESm09jnrN+7TNWR7JMY7D24qOMgkvxMbUPorHkxamXnkMMD8Ks3aGu/oSOZ
         kaUw==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:mime-version
         :content-transfer-encoding;
        bh=Xdz76Pr5X2U4qGHNaBUqTnUQFn7wjtLgR16d6odDiDY=;
        b=BzNoMZQubi9lQunxFQKJJmeRXZIkOWuXv0xUexKxuMB5KHuluziS93TFb9ZpTLvpua
         Klrj2wosJEeB3HQFmbIm8sL9PzP1QOgNiRC9gRAdyyiawkCJ8UOgTXHE3gnziY/cC3hm
         NkJIPtYdNjLBjxgsi/fvLktKcwA4Qbx9zGJ1rJhAD3NlKXadx6TXMpAxPGdPuY0X9zcx
         bOVLz84+mqMnuZqKU3RTa8HJdSmQNbstKhHzghM0a9buJtKcLw7ryofE/NIGldEJPP4U
         jBis/qW1kGjSZ4qkD+epNmF75b+D3lu12dhqvwmIU07sE2qOKxefz1ieZusLTMbsl1rK
         jMXA==
X-Gm-Message-State: AOAM533ajGSa8C1A34axYyBOSWkH62Sl3eei0W6ym6B/gj4LkU11z3qx
        ySZJNMP1o8rLMNv15a6JRk41
X-Google-Smtp-Source: 
 ABdhPJz+79mE6shXBsPb0acvIFtMPBgzHOe2E85ktwi8FRo2C3PHXFv0KX2CxiJB+oN/aw8FRop8mg==
X-Received: by 2002:a17:90a:ba02:: with SMTP id
 s2mr29110785pjr.53.1614081105834;
        Tue, 23 Feb 2021 03:51:45 -0800 (PST)
Received: from localhost ([139.177.225.253])
        by smtp.gmail.com with ESMTPSA id
 ca19sm3086493pjb.31.2021.02.23.03.51.44
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Tue, 23 Feb 2021 03:51:45 -0800 (PST)
From: Xie Yongji <xieyongji@bytedance.com>
To: mst@redhat.com, jasowang@redhat.com, stefanha@redhat.com,
        sgarzare@redhat.com, parav@nvidia.com, bob.liu@oracle.com,
        hch@infradead.org, rdunlap@infradead.org, willy@infradead.org,
        viro@zeniv.linux.org.uk, axboe@kernel.dk, bcrl@kvack.org,
        corbet@lwn.net
Cc: virtualization@lists.linux-foundation.org, netdev@vger.kernel.org,
        kvm@vger.kernel.org, linux-aio@kvack.org,
        linux-fsdevel@vger.kernel.org
Subject: [RFC v4 00/11] Introduce VDUSE - vDPA Device in Userspace
Date: Tue, 23 Feb 2021 19:50:37 +0800
Message-Id: <20210223115048.435-1-xieyongji@bytedance.com>
X-Mailer: git-send-email 2.25.1
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This series introduces a framework, which can be used to implement
vDPA Devices in a userspace program. The work consist of two parts:
control path forwarding and data path offloading.

In the control path, the VDUSE driver will make use of message
mechnism to forward the config operation from vdpa bus driver
to userspace. Userspace can use read()/write() to receive/reply
those control messages.

In the data path, the core is mapping dma buffer into VDUSE
daemon's address space, which can be implemented in different ways
depending on the vdpa bus to which the vDPA device is attached.

In virtio-vdpa case, we implements a MMU-based on-chip IOMMU driver with
bounce-buffering mechanism to achieve that. And in vhost-vdpa case, the dma
buffer is reside in a userspace memory region which can be shared to the
VDUSE userspace processs via transferring the shmfd.

The details and our user case is shown below:

------------------------    -------------------------   ----------------------------------------------
|            Container |    |              QEMU(VM) |   |                               VDUSE daemon |
|       ---------      |    |  -------------------  |   | ------------------------- ---------------- |
|       |dev/vdx|      |    |  |/dev/vhost-vdpa-x|  |   | | vDPA device emulation | | block driver | |
------------+-----------     -----------+------------   -------------+----------------------+---------
            |                           |                            |                      |
            |                           |                            |                      |
------------+---------------------------+----------------------------+----------------------+---------
|    | block device |           |  vhost device |            | vduse driver |          | TCP/IP |    |
|    -------+--------           --------+--------            -------+--------          -----+----    |
|           |                           |                           |                       |        |
| ----------+----------       ----------+-----------         -------+-------                |        |
| | virtio-blk driver |       |  vhost-vdpa driver |         | vdpa device |                |        |
| ----------+----------       ----------+-----------         -------+-------                |        |
|           |      virtio bus           |                           |                       |        |
|   --------+----+-----------           |                           |                       |        |
|                |                      |                           |                       |        |
|      ----------+----------            |                           |                       |        |
|      | virtio-blk device |            |                           |                       |        |
|      ----------+----------            |                           |                       |        |
|                |                      |                           |                       |        |
|     -----------+-----------           |                           |                       |        |
|     |  virtio-vdpa driver |           |                           |                       |        |
|     -----------+-----------           |                           |                       |        |
|                |                      |                           |    vdpa bus           |        |
|     -----------+----------------------+---------------------------+------------           |        |
|                                                                                        ---+---     |
-----------------------------------------------------------------------------------------| NIC |------
                                                                                         ---+---
                                                                                            |
                                                                                   ---------+---------
                                                                                   | Remote Storages |
                                                                                   -------------------

We make use of it to implement a block device connecting to
our distributed storage, which can be used both in containers and
VMs. Thus, we can have an unified technology stack in this two cases.

To test it with null-blk:

  $ qemu-storage-daemon \
      --chardev socket,id=charmonitor,path=/tmp/qmp.sock,server,nowait \
      --monitor chardev=charmonitor \
      --blockdev driver=host_device,cache.direct=on,aio=native,filename=/dev/nullb0,node-name=disk0 \
      --export type=vduse-blk,id=test,node-name=disk0,writable=on,name=vduse-null,num-queues=16,queue-size=128

The qemu-storage-daemon can be found at https://github.com/bytedance/qemu/tree/vduse

Future work:
  - Improve performance
  - Userspace library (find a way to reuse device emulation code in qemu/rust-vmm)

V3 to V4:
- Rebase to vhost.git
- Split some patches
- Add some documents
- Use ioctl to inject interrupt rather than eventfd
- Enable config interrupt support
- Support binding irq to the specified cpu
- Add two module parameter to limit bounce/iova size
- Create char device rather than anon inode per vduse
- Reuse vhost IOTLB for iova domain
- Rework the message mechnism in control path

V2 to V3:
- Rework the MMU-based IOMMU driver
- Use the iova domain as iova allocator instead of genpool
- Support transferring vma->vm_file in vhost-vdpa
- Add SVA support in vhost-vdpa
- Remove the patches on bounce pages reclaim

V1 to V2:
- Add vhost-vdpa support
- Add some documents
- Based on the vdpa management tool
- Introduce a workqueue for irq injection
- Replace interval tree with array map to store the iova_map

Xie Yongji (11):
  eventfd: Increase the recursion depth of eventfd_signal()
  vhost-vdpa: protect concurrent access to vhost device iotlb
  vhost-iotlb: Add an opaque pointer for vhost IOTLB
  vdpa: Add an opaque pointer for vdpa_config_ops.dma_map()
  vdpa: Support transferring virtual addressing during DMA mapping
  vduse: Implement an MMU-based IOMMU driver
  vduse: Introduce VDUSE - vDPA Device in Userspace
  vduse: Add config interrupt support
  Documentation: Add documentation for VDUSE
  vduse: Introduce a workqueue for irq injection
  vduse: Support binding irq to the specified cpu

 Documentation/userspace-api/index.rst              |    1 +
 Documentation/userspace-api/ioctl/ioctl-number.rst |    1 +
 Documentation/userspace-api/vduse.rst              |  112 ++
 drivers/vdpa/Kconfig                               |   10 +
 drivers/vdpa/Makefile                              |    1 +
 drivers/vdpa/ifcvf/ifcvf_main.c                    |    2 +-
 drivers/vdpa/mlx5/net/mlx5_vnet.c                  |    2 +-
 drivers/vdpa/vdpa.c                                |    9 +-
 drivers/vdpa/vdpa_sim/vdpa_sim.c                   |    8 +-
 drivers/vdpa/vdpa_user/Makefile                    |    5 +
 drivers/vdpa/vdpa_user/iova_domain.c               |  486 +++++++
 drivers/vdpa/vdpa_user/iova_domain.h               |   61 +
 drivers/vdpa/vdpa_user/vduse_dev.c                 | 1399 ++++++++++++++++++++
 drivers/vhost/iotlb.c                              |   20 +-
 drivers/vhost/vdpa.c                               |  106 +-
 fs/eventfd.c                                       |    2 +-
 include/linux/eventfd.h                            |    5 +-
 include/linux/vdpa.h                               |   22 +-
 include/linux/vhost_iotlb.h                        |    3 +
 include/uapi/linux/vduse.h                         |  144 ++
 20 files changed, 2363 insertions(+), 36 deletions(-)
 create mode 100644 Documentation/userspace-api/vduse.rst
 create mode 100644 drivers/vdpa/vdpa_user/Makefile
 create mode 100644 drivers/vdpa/vdpa_user/iova_domain.c
 create mode 100644 drivers/vdpa/vdpa_user/iova_domain.h
 create mode 100644 drivers/vdpa/vdpa_user/vduse_dev.c
 create mode 100644 include/uapi/linux/vduse.h
```
#### [kvm-unit-tests PATCH v2 0/5] s390: Add support for large pages
##### From: Claudio Imbrenda <imbrenda@linux.ibm.com>

```c
From patchwork Tue Feb 23 14:07:54 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Claudio Imbrenda <imbrenda@linux.ibm.com>
X-Patchwork-Id: 12100379
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-11.8 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_PATCH,MAILING_LIST_MULTI,
	SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT autolearn=unavailable
	autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 42393C433E9
	for <kvm@archiver.kernel.org>; Tue, 23 Feb 2021 14:08:52 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 13FA964E4B
	for <kvm@archiver.kernel.org>; Tue, 23 Feb 2021 14:08:52 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S231478AbhBWOIu (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 23 Feb 2021 09:08:50 -0500
Received: from mx0a-001b2d01.pphosted.com ([148.163.156.1]:45176 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S230165AbhBWOIr (ORCPT
        <rfc822;kvm@vger.kernel.org>); Tue, 23 Feb 2021 09:08:47 -0500
Received: from pps.filterd (m0098396.ppops.net [127.0.0.1])
        by mx0a-001b2d01.pphosted.com (8.16.0.43/8.16.0.43) with SMTP id
 11NE4804036949;
        Tue, 23 Feb 2021 09:08:07 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=ibm.com;
 h=from : to : cc : subject
 : date : message-id : mime-version : content-transfer-encoding; s=pp1;
 bh=ySQiB4YasbBPzqhTJdzSqSt993KdrOQGK0tllJJ677Y=;
 b=b4gm3v7q+xxQjPPmOYEsfU0sdAhJr6Ol+nwYOOLtvfo3hxxmmn+CfW7qmG8V0BAIOsJD
 5S/c3flhU/guaXmj6MypMjL2kUESUXCkOpui0xaNUs5TQ1EXhN5MTzU7fPP5nOWzjqhn
 g9/yYisdhy7GXfDHZNWy0zrvXDEP07JbqueC6fdbAD/YAFEtExG8mSBkkThJkeEpQLUJ
 sWQTqjE2CQ5jV+8x11TaPPeH5muz8CPrLCqejSKdsxomuVw/QlUQ12VAS5gjeTsgjtiC
 a+g770okmrr1V3jCPvTDpAgqTj5+7hoAaFQPtIJ+hT+uDbk2+diRafbPEIsJ2mup2V/R ng==
Received: from pps.reinject (localhost [127.0.0.1])
        by mx0a-001b2d01.pphosted.com with ESMTP id 36vkfuaay7-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Tue, 23 Feb 2021 09:08:06 -0500
Received: from m0098396.ppops.net (m0098396.ppops.net [127.0.0.1])
        by pps.reinject (8.16.0.43/8.16.0.43) with SMTP id 11NE4J73037532;
        Tue, 23 Feb 2021 09:08:06 -0500
Received: from ppma04fra.de.ibm.com (6a.4a.5195.ip4.static.sl-reverse.com
 [149.81.74.106])
        by mx0a-001b2d01.pphosted.com with ESMTP id 36vkfuaaww-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Tue, 23 Feb 2021 09:08:06 -0500
Received: from pps.filterd (ppma04fra.de.ibm.com [127.0.0.1])
        by ppma04fra.de.ibm.com (8.16.0.42/8.16.0.42) with SMTP id
 11NE7xrd002394;
        Tue, 23 Feb 2021 14:08:03 GMT
Received: from b06cxnps3074.portsmouth.uk.ibm.com
 (d06relay09.portsmouth.uk.ibm.com [9.149.109.194])
        by ppma04fra.de.ibm.com with ESMTP id 36tt289d68-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Tue, 23 Feb 2021 14:08:03 +0000
Received: from b06wcsmtp001.portsmouth.uk.ibm.com
 (b06wcsmtp001.portsmouth.uk.ibm.com [9.149.105.160])
        by b06cxnps3074.portsmouth.uk.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id 11NE80Qx28705044
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Tue, 23 Feb 2021 14:08:00 GMT
Received: from b06wcsmtp001.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 969BFA4083;
        Tue, 23 Feb 2021 14:08:00 +0000 (GMT)
Received: from b06wcsmtp001.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 384BCA4082;
        Tue, 23 Feb 2021 14:08:00 +0000 (GMT)
Received: from ibm-vm.ibmuc.com (unknown [9.145.5.213])
        by b06wcsmtp001.portsmouth.uk.ibm.com (Postfix) with ESMTP;
        Tue, 23 Feb 2021 14:08:00 +0000 (GMT)
From: Claudio Imbrenda <imbrenda@linux.ibm.com>
To: kvm@vger.kernel.org
Cc: linux-s390@vger.kernel.org, david@redhat.com, thuth@redhat.com,
        frankja@linux.ibm.com, cohuck@redhat.com, pmorel@linux.ibm.com
Subject: [kvm-unit-tests PATCH v2 0/5] s390: Add support for large pages
Date: Tue, 23 Feb 2021 15:07:54 +0100
Message-Id: <20210223140759.255670-1-imbrenda@linux.ibm.com>
X-Mailer: git-send-email 2.26.2
MIME-Version: 1.0
X-TM-AS-GCONF: 00
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.369,18.0.761
 definitions=2021-02-23_07:2021-02-23,2021-02-23 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 mlxscore=0 mlxlogscore=999
 phishscore=0 spamscore=0 impostorscore=0 malwarescore=0 bulkscore=0
 adultscore=0 suspectscore=0 priorityscore=1501 lowpriorityscore=0
 clxscore=1015 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.12.0-2009150000 definitions=main-2102230119
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Introduce support for large (1M) and huge (2G) pages.

Add a simple testcase for EDAT1 and EDAT2.

v1->v2

* split patch 2 -> new patch 2 and new patch 3
* patch 2: fixes pgtable.h, also fixes wrong usage of REGION_TABLE_LENGTH
  instead of SEGMENT_TABLE_LENGTH
* patch 3: introduces new macros and functions for large pages
* patch 4: remove erroneous double call to pte_alloc in get_pte
* patch 4: added comment in mmu.c to bridge the s390x architecural names
  with the Linux ones used in the kvm-unit-tests
* patch 5: added and fixed lots of comments to explain what's going on
* patch 5: set FC for region 3 after writing the canary, like for segments
* patch 5: use uintptr_t instead of intptr_t for set_prefix
* patch 5: introduce new macro PGD_PAGE_SHIFT instead of using magic value 41
* patch 5: use VIRT(0) instead of mem to make it more clear what we are
  doing, even though VIRT(0) expands to mem

Claudio Imbrenda (5):
  libcflat: add SZ_1M and SZ_2G
  s390x: lib: fix pgtable.h
  s390x: lib: improve pgtable.h
  s390x: mmu: add support for large pages
  s390x: edat test

 s390x/Makefile          |   1 +
 lib/s390x/asm/pgtable.h |  40 +++++-
 lib/libcflat.h          |   2 +
 lib/s390x/mmu.h         |  73 +++++++++-
 lib/s390x/mmu.c         | 260 ++++++++++++++++++++++++++++++++----
 s390x/edat.c            | 285 ++++++++++++++++++++++++++++++++++++++++
 s390x/unittests.cfg     |   3 +
 7 files changed, 633 insertions(+), 31 deletions(-)
 create mode 100644 s390x/edat.c
```
#### [kvm-unit-tests PATCH v2 0/2] s390x: mvpg test
##### From: Claudio Imbrenda <imbrenda@linux.ibm.com>

```c
From patchwork Tue Feb 23 14:24:27 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Claudio Imbrenda <imbrenda@linux.ibm.com>
X-Patchwork-Id: 12100397
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-11.8 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_PATCH,MAILING_LIST_MULTI,
	SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT autolearn=ham autolearn_force=no
	version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 340BEC433E0
	for <kvm@archiver.kernel.org>; Tue, 23 Feb 2021 14:25:53 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id EA7F164E60
	for <kvm@archiver.kernel.org>; Tue, 23 Feb 2021 14:25:52 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S232923AbhBWOZb (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 23 Feb 2021 09:25:31 -0500
Received: from mx0b-001b2d01.pphosted.com ([148.163.158.5]:46318 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S233016AbhBWOZR (ORCPT
        <rfc822;kvm@vger.kernel.org>); Tue, 23 Feb 2021 09:25:17 -0500
Received: from pps.filterd (m0098414.ppops.net [127.0.0.1])
        by mx0b-001b2d01.pphosted.com (8.16.0.43/8.16.0.43) with SMTP id
 11NE3ucf193085
        for <kvm@vger.kernel.org>; Tue, 23 Feb 2021 09:24:35 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=ibm.com;
 h=from : to : cc : subject
 : date : message-id : mime-version : content-transfer-encoding; s=pp1;
 bh=H5vKPjD25lRMEQ55cQ0nHIOU7Rkj2x9070/l/fWXPOQ=;
 b=eis6e6HHWz/1VO31slGbCksFPQRgHF3lYqYO4b8TT+k/yueEXYLTA5ipOE8/EkS/KItj
 YSnpUvfUBxw8gaPMtitw6RpMs8UUCJFCxTX8G3ztuwD/8IznQcbatHAZZUkj4cj0fyL+
 1WDIA4p7owTDVXeV9Ziwcp/ARL+Kjn5rw8IO58yF/owS2G9Yg5TJCLf53tGxopNbFDlH
 oLgFZDn0JbjxLl2t5TSNaym3Vs/0sdasEIUKx/g8xRCEC8VBvwRaNgwygUddzUkQgvd0
 MFSVupa9A7M4trve9DnuyTC85WhOY43XbHd9TGI+VIwRrUkaVxsO4E2RRzIxDBVQrs/Q mQ==
Received: from pps.reinject (localhost [127.0.0.1])
        by mx0b-001b2d01.pphosted.com with ESMTP id 36vkmyg4ta-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT)
        for <kvm@vger.kernel.org>; Tue, 23 Feb 2021 09:24:35 -0500
Received: from m0098414.ppops.net (m0098414.ppops.net [127.0.0.1])
        by pps.reinject (8.16.0.43/8.16.0.43) with SMTP id 11NE4FQj195054
        for <kvm@vger.kernel.org>; Tue, 23 Feb 2021 09:24:35 -0500
Received: from ppma03ams.nl.ibm.com (62.31.33a9.ip4.static.sl-reverse.com
 [169.51.49.98])
        by mx0b-001b2d01.pphosted.com with ESMTP id 36vkmyg4sq-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Tue, 23 Feb 2021 09:24:35 -0500
Received: from pps.filterd (ppma03ams.nl.ibm.com [127.0.0.1])
        by ppma03ams.nl.ibm.com (8.16.0.42/8.16.0.42) with SMTP id
 11NEOQqW031336;
        Tue, 23 Feb 2021 14:24:33 GMT
Received: from b06avi18878370.portsmouth.uk.ibm.com
 (b06avi18878370.portsmouth.uk.ibm.com [9.149.26.194])
        by ppma03ams.nl.ibm.com with ESMTP id 36tt282p79-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Tue, 23 Feb 2021 14:24:33 +0000
Received: from d06av23.portsmouth.uk.ibm.com (d06av23.portsmouth.uk.ibm.com
 [9.149.105.59])
        by b06avi18878370.portsmouth.uk.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id 11NEOIea23331110
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Tue, 23 Feb 2021 14:24:18 GMT
Received: from d06av23.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id A51D0A4051;
        Tue, 23 Feb 2021 14:24:30 +0000 (GMT)
Received: from d06av23.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 450CEA404D;
        Tue, 23 Feb 2021 14:24:30 +0000 (GMT)
Received: from ibm-vm.ibmuc.com (unknown [9.145.5.213])
        by d06av23.portsmouth.uk.ibm.com (Postfix) with ESMTP;
        Tue, 23 Feb 2021 14:24:30 +0000 (GMT)
From: Claudio Imbrenda <imbrenda@linux.ibm.com>
To: kvm@vger.kernel.org
Cc: david@redhat.com, thuth@redhat.com, frankja@linux.ibm.com,
        cohuck@redhat.com, pmorel@linux.ibm.com, borntraeger@de.ibm.com
Subject: [kvm-unit-tests PATCH v2 0/2] s390x: mvpg test
Date: Tue, 23 Feb 2021 15:24:27 +0100
Message-Id: <20210223142429.256420-1-imbrenda@linux.ibm.com>
X-Mailer: git-send-email 2.26.2
MIME-Version: 1.0
X-TM-AS-GCONF: 00
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.369,18.0.761
 definitions=2021-02-23_07:2021-02-23,2021-02-23 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 adultscore=0
 priorityscore=1501 bulkscore=0 spamscore=0 clxscore=1015
 lowpriorityscore=0 mlxlogscore=742 malwarescore=0 impostorscore=0
 mlxscore=0 phishscore=0 suspectscore=0 classifier=spam adjust=0 reason=mlx
 scancount=1 engine=8.12.0-2009150000 definitions=main-2102230119
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

A simple unit test for the MVPG instruction.

The timeout is set to 10 seconds because the test should complete in a
fraction of a second even on busy machines. If the test is run in VSIE
and the host of the host is not handling MVPG properly, the test will
probably hang.

Testing MVPG behaviour in VSIE is the main motivation for this test.

Anything related to storage keys is not tested.

v1->v2
* droppped patch 2 which introduced is_pgm();
* patch 1: replace a hardcoded value with the new macro SVC_LEAVE_PSTATE
* patch 2: clear_pgm_int() returns the old value, use that instad of is_pgm()

Claudio Imbrenda (2):
  s390x: introduce leave_pstate to leave userspace
  s390x: mvpg: simple test

 s390x/Makefile           |   1 +
 lib/s390x/asm/arch_def.h |   7 ++
 lib/s390x/interrupt.c    |  12 +-
 s390x/mvpg.c             | 266 +++++++++++++++++++++++++++++++++++++++
 s390x/unittests.cfg      |   4 +
 5 files changed, 288 insertions(+), 2 deletions(-)
 create mode 100644 s390x/mvpg.c
```
#### [PATCH v4 0/2] s390/kvm: fix MVPG when in VSIE
##### From: Claudio Imbrenda <imbrenda@linux.ibm.com>

```c
From patchwork Tue Feb 23 19:13:51 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Claudio Imbrenda <imbrenda@linux.ibm.com>
X-Patchwork-Id: 12100773
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-11.8 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_PATCH,MAILING_LIST_MULTI,
	SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT autolearn=unavailable
	autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id E3BEFC433DB
	for <kvm@archiver.kernel.org>; Tue, 23 Feb 2021 19:14:58 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id B25A964E20
	for <kvm@archiver.kernel.org>; Tue, 23 Feb 2021 19:14:58 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S231905AbhBWTOl (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 23 Feb 2021 14:14:41 -0500
Received: from mx0a-001b2d01.pphosted.com ([148.163.156.1]:23520 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S230114AbhBWTOk (ORCPT
        <rfc822;kvm@vger.kernel.org>); Tue, 23 Feb 2021 14:14:40 -0500
Received: from pps.filterd (m0098410.ppops.net [127.0.0.1])
        by mx0a-001b2d01.pphosted.com (8.16.0.43/8.16.0.43) with SMTP id
 11NJ2h1q011765;
        Tue, 23 Feb 2021 14:13:59 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=ibm.com;
 h=from : to : cc : subject
 : date : message-id : mime-version : content-transfer-encoding; s=pp1;
 bh=ykJhJz2Y/yV96Zls5vPfzXgD4YnQ1pOgma5Gqu5wE/I=;
 b=r2cyRqBsjTf+8nNDdroxL72ER4uj2NbHkK2aZU3KOxupSI1H94vF/v+LD3LlSPCPyqTq
 yyrbAtGmLprEKFHM4n9Qme092SfEFOVEXGPy2HxgxhCmmSonJLt6OD20JA4zLXhwLdtI
 VOFvcwGOqqZxULbW019bgKg1L+mvC3CPZbpYl5xCqq0xpcwB82Skzcuqt0vk6nipmJu5
 jWyuHNLgoyqeM6SarWs2oPEunNbRrEA+r6gnZMO/wClkiQB6DTk37Xyb118wDpX6hgwi
 66QB331VUmrmZxxxN0Sn+KX9Zv5O6SnAZI9obPG7wZJib4OnGGZF0KcFSeYasuInbLET yw==
Received: from pps.reinject (localhost [127.0.0.1])
        by mx0a-001b2d01.pphosted.com with ESMTP id 36vkg3csgx-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Tue, 23 Feb 2021 14:13:59 -0500
Received: from m0098410.ppops.net (m0098410.ppops.net [127.0.0.1])
        by pps.reinject (8.16.0.43/8.16.0.43) with SMTP id 11NJ3BGq017316;
        Tue, 23 Feb 2021 14:13:59 -0500
Received: from ppma03ams.nl.ibm.com (62.31.33a9.ip4.static.sl-reverse.com
 [169.51.49.98])
        by mx0a-001b2d01.pphosted.com with ESMTP id 36vkg3csgc-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Tue, 23 Feb 2021 14:13:59 -0500
Received: from pps.filterd (ppma03ams.nl.ibm.com [127.0.0.1])
        by ppma03ams.nl.ibm.com (8.16.0.42/8.16.0.42) with SMTP id
 11NJC9cp014507;
        Tue, 23 Feb 2021 19:13:56 GMT
Received: from b06avi18626390.portsmouth.uk.ibm.com
 (b06avi18626390.portsmouth.uk.ibm.com [9.149.26.192])
        by ppma03ams.nl.ibm.com with ESMTP id 36tt282w2u-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Tue, 23 Feb 2021 19:13:56 +0000
Received: from d06av23.portsmouth.uk.ibm.com (d06av23.portsmouth.uk.ibm.com
 [9.149.105.59])
        by b06avi18626390.portsmouth.uk.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id 11NJDfkv36503892
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Tue, 23 Feb 2021 19:13:41 GMT
Received: from d06av23.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id C7CE2A4040;
        Tue, 23 Feb 2021 19:13:53 +0000 (GMT)
Received: from d06av23.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 6543FA404D;
        Tue, 23 Feb 2021 19:13:53 +0000 (GMT)
Received: from ibm-vm.ibmuc.com (unknown [9.145.5.213])
        by d06av23.portsmouth.uk.ibm.com (Postfix) with ESMTP;
        Tue, 23 Feb 2021 19:13:53 +0000 (GMT)
From: Claudio Imbrenda <imbrenda@linux.ibm.com>
To: linux-kernel@vger.kernel.org
Cc: borntraeger@de.ibm.com, frankja@linux.ibm.com, david@redhat.com,
        cohuck@redhat.com, kvm@vger.kernel.org, linux-s390@vger.kernel.org
Subject: [PATCH v4 0/2] s390/kvm: fix MVPG when in VSIE
Date: Tue, 23 Feb 2021 20:13:51 +0100
Message-Id: <20210223191353.267981-1-imbrenda@linux.ibm.com>
X-Mailer: git-send-email 2.26.2
MIME-Version: 1.0
X-TM-AS-GCONF: 00
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.369,18.0.761
 definitions=2021-02-23_08:2021-02-23,2021-02-23 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 lowpriorityscore=0
 clxscore=1015 adultscore=0 priorityscore=1501 malwarescore=0
 mlxlogscore=679 mlxscore=0 impostorscore=0 bulkscore=0 spamscore=0
 phishscore=0 suspectscore=0 classifier=spam adjust=0 reason=mlx
 scancount=1 engine=8.12.0-2009150000 definitions=main-2102230158
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The current handling of the MVPG instruction when executed in a nested
guest is wrong, and can lead to the nested guest hanging.

This patchset fixes the behaviour to be more architecturally correct,
and fixes the hangs observed.

v3->v4
* added PEI_ prefix to DAT_PROT and NOT_PTE macros
* added small comment to explain what they are about

v2->v3
* improved some comments
* improved some variable and parameter names for increased readability
* fixed missing handling of page faults in the MVPG handler
* small readability improvements

v1->v2
* complete rewrite

Claudio Imbrenda (2):
  s390/kvm: extend kvm_s390_shadow_fault to return entry pointer
  s390/kvm: VSIE: correctly handle MVPG when in VSIE

 arch/s390/kvm/gaccess.c |  30 ++++++++++--
 arch/s390/kvm/gaccess.h |   6 ++-
 arch/s390/kvm/vsie.c    | 101 ++++++++++++++++++++++++++++++++++++----
 3 files changed, 122 insertions(+), 15 deletions(-)
```
#### [PATCH 0/3] Tidy some parts of the VFIO kconfig world
##### From: Jason Gunthorpe <jgg@nvidia.com>

```c
From patchwork Tue Feb 23 19:17:45 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Jason Gunthorpe <jgg@nvidia.com>
X-Patchwork-Id: 12100807
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-10.8 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_PATCH,MAILING_LIST_MULTI,MSGID_FROM_MTA_HEADER,SPF_HELO_NONE,
	SPF_PASS autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id C26B1C433DB
	for <kvm@archiver.kernel.org>; Tue, 23 Feb 2021 19:20:28 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 95FF464DE8
	for <kvm@archiver.kernel.org>; Tue, 23 Feb 2021 19:20:28 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S233920AbhBWTTs (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 23 Feb 2021 14:19:48 -0500
Received: from hqnvemgate24.nvidia.com ([216.228.121.143]:7675 "EHLO
        hqnvemgate24.nvidia.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S233757AbhBWTSf (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 23 Feb 2021 14:18:35 -0500
Received: from hqmail.nvidia.com (Not Verified[216.228.121.13]) by
 hqnvemgate24.nvidia.com (using TLS: TLSv1.2, AES256-SHA)
        id <B603554df0001>; Tue, 23 Feb 2021 11:17:51 -0800
Received: from HQMAIL111.nvidia.com (172.20.187.18) by HQMAIL111.nvidia.com
 (172.20.187.18) with Microsoft SMTP Server (TLS) id 15.0.1497.2; Tue, 23 Feb
 2021 19:17:51 +0000
Received: from NAM10-DM6-obe.outbound.protection.outlook.com (104.47.58.105)
 by HQMAIL111.nvidia.com (172.20.187.18) with Microsoft SMTP Server (TLS) id
 15.0.1497.2 via Frontend Transport; Tue, 23 Feb 2021 19:17:51 +0000
ARC-Seal: i=1; a=rsa-sha256; s=arcselector9901; d=microsoft.com; cv=none;
 b=I7O4te2H0NiCD3JaEBl8IWRvvu1zsXXjPV1znlpTOPpm+juCQo1iTtt2uKt+Tlea2OeMj2VpMrdCVPJxZYywzVev7Dr4ftpV48JiksFkTZNuLnzR1QsdzbhjKvHdqI2NlZXZbINZagr8jHawE26SBvzPCg/SZjO+sWdvy9FOT1MdwQjJ16B6Pl5+BVjDZOGedM3RYOa5Kb7Gepw0kpebSZptgP80vqxi46VC3FQP/Py6218ZwFS1lQ7TbM2vm03Buvisl2LcvhA62pg4FW/PxL9babg4PHrwl3QTPXOAJqVKHvv4eWYXUrTIKTwm6tuCvOk5DckaK1muWIedQHXA6Q==
ARC-Message-Signature: i=1; a=rsa-sha256; c=relaxed/relaxed; d=microsoft.com;
 s=arcselector9901;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=ZEvFFnG5G/GcMyoaDl1jgbqBRpvcbgg2WZ80/0T+MhM=;
 b=Ti2WT2lohY2mRmQk8yvAfgycYScPEKx+H1HTu+N75/4KBkUR1sWdvlOB8XBWI+7C/9TUIzTHts49WBWLrhcSojpVZfN1A5759pLurcoAi+Xy3sx2Nw2XloTMail5djHGK/Ex/u8nV5QpmnypkavYWMdIZ9IIHNwj8OSQcvTwE6PKYPVbuM4CXx3w4YBBuX69hA6n86eyHON3SQQ4OObbYUhW6GSZNf2pmckC6zvPt+boR3i772Mq+msuT6kBd4nskROJCZuNxzOV0MGbEV66UfkwhMINfrRFawzvT1VCaQE2GOVZ8hTxqH3axe9q4+Otw8pCBeK3FrJQc9B2Ax6TlA==
ARC-Authentication-Results: i=1; mx.microsoft.com 1; spf=pass
 smtp.mailfrom=nvidia.com; dmarc=pass action=none header.from=nvidia.com;
 dkim=pass header.d=nvidia.com; arc=none
Received: from DM6PR12MB3834.namprd12.prod.outlook.com (2603:10b6:5:14a::12)
 by DM6PR12MB4943.namprd12.prod.outlook.com (2603:10b6:5:1bc::21) with
 Microsoft SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.3868.32; Tue, 23 Feb
 2021 19:17:50 +0000
Received: from DM6PR12MB3834.namprd12.prod.outlook.com
 ([fe80::1c62:7fa3:617b:ab87]) by DM6PR12MB3834.namprd12.prod.outlook.com
 ([fe80::1c62:7fa3:617b:ab87%6]) with mapi id 15.20.3868.033; Tue, 23 Feb 2021
 19:17:50 +0000
From: Jason Gunthorpe <jgg@nvidia.com>
To: Alex Williamson <alex.williamson@redhat.com>,
        Cornelia Huck <cohuck@redhat.com>,
        Eric Auger <eric.auger@redhat.com>, <kvm@vger.kernel.org>,
        Russell King <linux@armlinux.org.uk>
Subject: [PATCH 0/3] Tidy some parts of the VFIO kconfig world
Date: Tue, 23 Feb 2021 15:17:45 -0400
Message-ID: <0-v1-df057e0f92c3+91-vfio_arm_compile_test_jgg@nvidia.com>
X-ClientProxiedBy: BL1PR13CA0057.namprd13.prod.outlook.com
 (2603:10b6:208:257::32) To DM6PR12MB3834.namprd12.prod.outlook.com
 (2603:10b6:5:14a::12)
MIME-Version: 1.0
X-MS-Exchange-MessageSentRepresentingType: 1
Received: from mlx.ziepe.ca (142.162.115.133) by
 BL1PR13CA0057.namprd13.prod.outlook.com (2603:10b6:208:257::32) with
 Microsoft SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.3890.9 via Frontend
 Transport; Tue, 23 Feb 2021 19:17:50 +0000
Received: from jgg by mlx with local (Exim 4.94)        (envelope-from
 <jgg@nvidia.com>)        id 1lEdBs-00FUTT-Gx; Tue, 23 Feb 2021 15:17:48 -0400
X-Header: ProcessedBy-CMR-outbound
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=nvidia.com; s=n1;
        t=1614107871; bh=ezgvw1LUjTmgiG7YLWyTtj/1hC/Tex+d7AIF5J30xd8=;
        h=ARC-Seal:ARC-Message-Signature:ARC-Authentication-Results:From:To:
         Subject:Date:Message-ID:Content-Transfer-Encoding:Content-Type:
         X-ClientProxiedBy:MIME-Version:
         X-MS-Exchange-MessageSentRepresentingType:X-Header;
        b=PAOvZgeYw5zuG6ygbyct1Ni5+rVQieaXvJ+Uzf8UfS3MIfzKvaGQFe3N21/vpaBAC
         ZBZCHQpL6t2BW7lPM8zJ775autqP+/uiKYgKtyiSsuX3W/EH4m414dL+eLKbbQPn88
         2s6neaheKR+VfEjlD61fH/HJKhMoT+iKd+5xOp3CMW9P6bA6t1h0GzAk1toDnVjKP+
         6V6TVOWFOwtS88HOGoRy0aXQ8W548uspdhMJ0aUCrZyi6HHMyRtoC93PWO/F4lLegR
         Z+qOpSYtqKH/TL0rgJPMx0fU1qH4+QBrldTnrUkMb6yXhN/4mud+GVb7/rylkk9jRb
         a1L+Jix9icvdg==
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The main goal here is to add enough COMPILE_TEST that an ARM cross
compiler is not needed to be able to get compile coverage on VFIO. A
normal x86 compiler with COMPILE_TEST will do the job.

s390 and ppc are still needed, and I'm looking to see if any of that is
reasonable to change too.

Thanks,
Jason

Jason Gunthorpe (3):
  vfio: IOMMU_API should be selected
  vfio-platform: Add COMPILE_TEST to VFIO_PLATFORM
  ARM: amba: Allow some ARM_AMBA users to compile with COMPILE_TEST

 drivers/vfio/Kconfig          |  2 +-
 drivers/vfio/platform/Kconfig |  4 ++--
 include/linux/amba/bus.h      | 11 +++++++++++
 3 files changed, 14 insertions(+), 3 deletions(-)
```
#### [PATCH 0/4 v3] nSVM: Test host RFLAGS.TF on VMRUN
##### From: Krish Sadhukhan <krish.sadhukhan@oracle.com>

```c
From patchwork Tue Feb 23 19:19:54 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Krish Sadhukhan <krish.sadhukhan@oracle.com>
X-Patchwork-Id: 12100821
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-13.7 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_PATCH,
	MAILING_LIST_MULTI,MSGID_FROM_MTA_HEADER,SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED,
	USER_AGENT_GIT autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 1517CC433E0
	for <kvm@archiver.kernel.org>; Tue, 23 Feb 2021 20:10:37 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id D694464E6C
	for <kvm@archiver.kernel.org>; Tue, 23 Feb 2021 20:10:36 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S234194AbhBWUKS (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 23 Feb 2021 15:10:18 -0500
Received: from userp2120.oracle.com ([156.151.31.85]:39198 "EHLO
        userp2120.oracle.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S234167AbhBWUJB (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 23 Feb 2021 15:09:01 -0500
Received: from pps.filterd (userp2120.oracle.com [127.0.0.1])
        by userp2120.oracle.com (8.16.0.42/8.16.0.42) with SMTP id
 11NK4a8O022746;
        Tue, 23 Feb 2021 20:08:17 GMT
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=oracle.com;
 h=from : to : cc :
 subject : date : message-id : content-transfer-encoding : content-type :
 mime-version; s=corp-2020-01-29;
 bh=JneJPKbSra/GI9r1iQ0mWuD3uWqlyEAq2XW8g0EpLgU=;
 b=UsQYVKnyPBXawPBlXGVsuw3I8QA70v62BjGtpBzkpWDAkEVv5nm4p8FwY2Pe33J437Vt
 /h9tctd4N3/sXUQTEAFFiMNyYE0+IQWFIxYuXQt2bGAUa1zronsLNQBeJKz5vPOxJuR/
 Ey1FK/IvCbr1yAZlzFri1BUr+zMPbF++5KJT/TrtZJ8ARzZSgJ9RDyGIeePn1kBcPgLH
 VgHqTUaUTtmfW2/SaazU9xBOD1qnTTxH/rXq7BBvCEPyOS7pa0kaDcOb3LhOqTSIZ6hw
 3MurbsC9iXWqm1zHYCjvo5px6O/QKNVn/NHDnU3oQrFMdJmYz2rgmBqTaOaVdXEwqnAD gQ==
Received: from userp3030.oracle.com (userp3030.oracle.com [156.151.31.80])
        by userp2120.oracle.com with ESMTP id 36ugq3fjer-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Tue, 23 Feb 2021 20:08:16 +0000
Received: from pps.filterd (userp3030.oracle.com [127.0.0.1])
        by userp3030.oracle.com (8.16.0.42/8.16.0.42) with SMTP id
 11NK6Vd5106920;
        Tue, 23 Feb 2021 20:08:16 GMT
Received: from nam12-bn8-obe.outbound.protection.outlook.com
 (mail-bn8nam12lp2175.outbound.protection.outlook.com [104.47.55.175])
        by userp3030.oracle.com with ESMTP id 36ucbxyc3h-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Tue, 23 Feb 2021 20:08:16 +0000
ARC-Seal: i=1; a=rsa-sha256; s=arcselector9901; d=microsoft.com; cv=none;
 b=mLOVrg6ZY+r/aWmYEqaPuvlFGWOEnBW6+E/2uj44lZ3yoLOirxwjPeb5kbk8zKHjjRFgQHy4O+WktJuLyL4gXbLfc+vG5bLNhzAQrq7ldmsfpQbicgtM/0s2LmL905eaZlRZMXlAaVPY/gnou2zWhv2RCn9rIL2mKGj4kPNIetfjDm0LVO6BRBMguCGz48nqdsX4BAhklrRlBjwcEpqX5BJOAy4O3VhpW5x1+Ho7jolJzRVO9C59jSRAIo6rQ1KBvqZRpxnn/Dx2aPgpssOGu0aJBCaqm9iePOA/7OZldmOmMC/GWuJxQN9tb1Bje7R/jHoCAp9zD35itVpYGlCKug==
ARC-Message-Signature: i=1; a=rsa-sha256; c=relaxed/relaxed; d=microsoft.com;
 s=arcselector9901;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=JneJPKbSra/GI9r1iQ0mWuD3uWqlyEAq2XW8g0EpLgU=;
 b=W2CH0Z+oDyRi1o1BkA/ailrOX0h7Heo3ROw0VPbxSYazMjLI/XU1Uuw9s5FQk0lHNDS5v2BONNbuKaOdDdKG+QRMFvatzwQ1pF9qAmJ0U6casXLG08+6Rbe4z30PVMKfik1A1ay9mM5jvd9P3ePkBuWCHzJyOs8FwzXL3KS4MhxwRIrCS9P8HL+Qvparo0FKRFqLDoz6g0hByjMeXkhx4PDRduhFpxxBgM8TGUJfzNC4+oVQVDf3BgBrGpJGfxKn4zhz1vrg+XYkR8WATNLf+uAGsYUugHzonrnGoxZFo8zJc9xUJTCwh+t4ftLDfdGKulkBHfsQdZGsF667JH6Euw==
ARC-Authentication-Results: i=1; mx.microsoft.com 1; spf=pass
 smtp.mailfrom=oracle.com; dmarc=pass action=none header.from=oracle.com;
 dkim=pass header.d=oracle.com; arc=none
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
 d=oracle.onmicrosoft.com; s=selector2-oracle-onmicrosoft-com;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=JneJPKbSra/GI9r1iQ0mWuD3uWqlyEAq2XW8g0EpLgU=;
 b=O0G1EwCINm9A+I4JMwWBEzm4KqLaT0+aIB5Dw/p3b73LJKWLNPa/gQw4/DiEEvxkWAjRKUqttzAcmYuL8lVLvJGRsMvpfITT5EFDuB19XhqzKQnKGBlwwYvG2UPJhpXfq5/IV4Ecthg+qEvVUm6xDvKmGBGipSqSxvVDORhnIu0=
Authentication-Results: vger.kernel.org; dkim=none (message not signed)
 header.d=none;vger.kernel.org; dmarc=none action=none header.from=oracle.com;
Received: from SN6PR10MB3021.namprd10.prod.outlook.com (2603:10b6:805:cc::19)
 by SN6PR10MB3022.namprd10.prod.outlook.com (2603:10b6:805:d8::25) with
 Microsoft SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.3868.27; Tue, 23 Feb
 2021 20:08:14 +0000
Received: from SN6PR10MB3021.namprd10.prod.outlook.com
 ([fe80::1871:3741:cc17:bcf7]) by SN6PR10MB3021.namprd10.prod.outlook.com
 ([fe80::1871:3741:cc17:bcf7%7]) with mapi id 15.20.3868.033; Tue, 23 Feb 2021
 20:08:14 +0000
From: Krish Sadhukhan <krish.sadhukhan@oracle.com>
To: kvm@vger.kernel.org
Cc: pbonzini@redhat.com, jmattson@google.com, seanjc@google.com
Subject: [PATCH 0/4 v3] nSVM: Test host RFLAGS.TF on VMRUN
Date: Tue, 23 Feb 2021 14:19:54 -0500
Message-Id: <20210223191958.24218-1-krish.sadhukhan@oracle.com>
X-Mailer: git-send-email 2.25.4
X-Originating-IP: [138.3.200.29]
X-ClientProxiedBy: BY3PR05CA0026.namprd05.prod.outlook.com
 (2603:10b6:a03:254::31) To SN6PR10MB3021.namprd10.prod.outlook.com
 (2603:10b6:805:cc::19)
MIME-Version: 1.0
X-MS-Exchange-MessageSentRepresentingType: 1
Received: from ban25x6uut29.us.oracle.com (138.3.200.29) by
 BY3PR05CA0026.namprd05.prod.outlook.com (2603:10b6:a03:254::31) with
 Microsoft SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.3890.10 via Frontend
 Transport; Tue, 23 Feb 2021 20:08:13 +0000
X-MS-PublicTrafficType: Email
X-MS-Office365-Filtering-Correlation-Id: c72b458b-2b08-4464-b9d7-08d8d836c039
X-MS-TrafficTypeDiagnostic: SN6PR10MB3022:
X-Microsoft-Antispam-PRVS: 
 <SN6PR10MB3022A0FA1AE19E40413DEF3681809@SN6PR10MB3022.namprd10.prod.outlook.com>
X-MS-Oob-TLC-OOBClassifiers: OLM:8882;
X-MS-Exchange-SenderADCheck: 1
X-Microsoft-Antispam: BCL:0;
X-Microsoft-Antispam-Message-Info: 
 qEgQKTQhcfc9rxMw8Ix88DrMtQ7NWsEECYIC4cHFAC+Vxu/28n2VdXmr5YlE+QlVovLbaoiJPtVIi/q1tLI8MCmKvZpDhX3IBeHEIhLEQFvo8ciJUSaOkWAcuO98dculNrMyOGJyjttg4uXfcfdzjbOfAh29MXvXblBL1scCFFV6OgpMsp53wnG4zuBqf6IbPIF6vvrQmR3iUAoi2feCcIuwjx16hZnHpHqYeoS/zB2srUijFl/RyWcLcmEaS4SkYebhGZa2J284A0oRIEvgaGq7EADn6YkO8tElCgSy4K+p2vX+0D3CRMXGeQR3JBT1XqlieZcQZdtcZ+jq8/94VbkDVpEMjOuzv/4KLZN0BmTM+HpMHJtTzIUe9Cf+qQibgSpxOHXMl6TBivNcrLK+4fN2wbh59hPMnAGO1Vp1sleMOvEYwdrDo13AnsdMG3BEmT6GKa0qHmnFNf7uLj239eFZbXfz+3VVvBsEU2P8x+/p2fsdsY1ctk3eIlobGfgTNIpIL0OqSXHKUeJr130q+Q==
X-Forefront-Antispam-Report: 
 CIP:255.255.255.255;CTRY:;LANG:en;SCL:1;SRV:;IPV:NLI;SFV:NSPM;H:SN6PR10MB3021.namprd10.prod.outlook.com;PTR:;CAT:NONE;SFS:(39860400002)(346002)(366004)(396003)(376002)(136003)(66946007)(26005)(86362001)(7696005)(66476007)(66556008)(52116002)(1076003)(186003)(44832011)(16526019)(36756003)(6666004)(316002)(956004)(2616005)(6916009)(5660300002)(6486002)(4326008)(83380400001)(2906002)(478600001)(8676002)(8936002);DIR:OUT;SFP:1101;
X-MS-Exchange-AntiSpam-MessageData: 
 8dm8XTjH+YxMiNPorIDX8aKlwmiPzY0wmD255lypIY0+E3+kSDR7Se2PUlYtBFgyjYhh+M5mM9PRZpZyV6uS0f6LCu4Hz2wOUPLxYp2v3qiIf7/TJ8TpLt9N6RKdbq/NeqYJWnwozDBXrVCZ8SpM0oZL7SvfnfvI9mKq0vOjXhwX70vaJ4frKjtKU4WbR8fFsR68mpHa+SUIJZvvZWyLQ5yNbhRsnm0T2qJuoKPmBYuaJkRgblTbwoVUmdUetLoOP5L9xN8HHtBz9HKeXidXxhdiqLpL3jnC+V87O6dgSrMTpY7fuYD5aPbQq6hgCX7PPvHjugESKvmpTaeNpMFiMD8tl43b0Z+zCG127SacJFZPyHFHMJYvGmIlMOC59nbYWYaX23XzEnrL9puLGF4vE9Y3cu/NHtRQhSGWCZF3VYnaAdVCqFaIuwsDkXO4L4hhH/LuWo33mj8EyhvfMA/VRwecWjduuYrJaDGGbnC5YzRiMDtuwW4jY5xJQsodvNMyOXEbEErbWl0hHaByYJ2vuNuviPCfDYBJxOeT+ISNXCjwXorL4mKulfwkn+8bdYLQ45XrYS7z4Qh2/vPenDf1k8bYD06sglJKceBoGit2vDW4N3l0eIvR7WQU1DcQo2L4aNWnmTc2r2dPL7hdU31KAbvo2/CV4w1WMDheTZ9qOFHSo8SBIVvY0wXqA+lmEjjsfA5HrjyTbomEnqdCZ+8OW2C3poME7hlZJyUgaUW7wpQP3VP/ya6y7Jxiw2LdHFa71qBweRGF4DQ/2l+cwhAp3k+V97mpgJSVVpit6wGOKSEInDMAVAF0uQTQxHKLNUWxByfbh9Cjoc+n8z+XAkKw4OgEMmvjQclqQPjIx6IEL3F/yJV1+5CB6RPuoYaoEo17REqvvbBIGBr9dMmpvgI3/217mF2bAIMzXBFbje/fi6lFPlW8lCTb/rzbnb4r2wg9HOaZ6D4Tu36vu/yOVqCTEiA1Kw2oqAUM5K3evXQA1TEIRgJ3FaO7FYazNXq1OtW1Jz/oPeY71FooErHsu5+eZKMrxZIExaLMrkadCB50EGCfk0jpgizMBr+c3qJk+uWGL1Q8l4fz/DUw7RiN9l5m36TH/eR0IXeMvzzeQYnZh17yFOR4po3DLWJjDbyYY+Ya0t0dENDrPd/pHaVZDbbQ2vTEk4gYKmHvffNnhxxeAaXJL3CVDvAnL507vGK5JgrSGsQEziY50SQc6mp4QjpmmvHhRknI40bJFrQIOJq3edEBJMu9XR0CaLSLcE2gP+DfYQs3vPiIGlp8Bgs2b8Tz3MPkoIKK5huIna+otZs/Imev/TVYa//GZZ77ewrJfXkh
X-OriginatorOrg: oracle.com
X-MS-Exchange-CrossTenant-Network-Message-Id: 
 c72b458b-2b08-4464-b9d7-08d8d836c039
X-MS-Exchange-CrossTenant-AuthSource: SN6PR10MB3021.namprd10.prod.outlook.com
X-MS-Exchange-CrossTenant-AuthAs: Internal
X-MS-Exchange-CrossTenant-OriginalArrivalTime: 23 Feb 2021 20:08:14.1435
 (UTC)
X-MS-Exchange-CrossTenant-FromEntityHeader: Hosted
X-MS-Exchange-CrossTenant-Id: 4e2c6054-71cb-48f1-bd6c-3a9705aca71b
X-MS-Exchange-CrossTenant-MailboxType: HOSTED
X-MS-Exchange-CrossTenant-UserPrincipalName: 
 6pBitsZ0h/dkbioGhnXxsR7IOyaGXSH3307eCUeE3m/knbrNegcVsCNW2jqXIkTbNVYD8+7yjpLVmF9I6Z/sZdDtlHtM9Lq1dtUNkxgppEQ=
X-MS-Exchange-Transport-CrossTenantHeadersStamped: SN6PR10MB3022
X-Proofpoint-Virus-Version: vendor=nai engine=6200 definitions=9904
 signatures=668683
X-Proofpoint-Spam-Details: rule=notspam policy=default score=0 mlxlogscore=828
 adultscore=0
 phishscore=0 spamscore=0 suspectscore=0 bulkscore=0 malwarescore=0
 mlxscore=0 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.12.0-2009150000 definitions=main-2102230169
X-Proofpoint-Virus-Version: vendor=nai engine=6200 definitions=9904
 signatures=668683
X-Proofpoint-Spam-Details: rule=notspam policy=default score=0 adultscore=0
 phishscore=0
 malwarescore=0 spamscore=0 mlxscore=0 suspectscore=0 priorityscore=1501
 clxscore=1015 impostorscore=0 lowpriorityscore=0 mlxlogscore=997
 bulkscore=0 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.12.0-2009150000 definitions=main-2102230169
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

v2 -> v3:
        Patch# 1: It's a new patch for SVM. It fixes the SVM bug that advances
                  the RIP following the #VMEXIT from a VMRUN that is being
                  single-stepped.
        Patch# 2: It's a new patch for the test framework. It adds a utility
                   function to read the current RIP.
        Patch# 3: It's a new patch for the test framework. It adds an 
                  assembly label to the VMRUN instruction so that the RIP
                  of VMRUN can be known to tests.
        Patch# 4: It's the updated test from v2. The test uses the VMRUN
                  instruction label, added by the previous patch, in order
                  know its RIP. The part of the test that tests single-stepping
                  on VMRUN, uses the difference between the VMRUN RIP and its
                  next RIP, in order to determine success.

[PATCH 1/4 v3] KVM: nSVM: Do not advance RIP following VMRUN completion if the
[PATCH 2/4 v3] KVM: X86: Add a utility function to read current RIP
[PATCH 3/4 v3] KVM: nSVM: Add assembly label to VMRUN instruction
[PATCH 4/4 v3] KVM: nSVM: Test effect of host RFLAGS.TF on VMRUN

 arch/x86/kvm/svm/svm.c | 12 +++++++++++-
 1 file changed, 11 insertions(+), 1 deletion(-)

Krish Sadhukhan (1):
      nSVM: Do not advance RIP following VMRUN completion if the latter is single-stepped

 lib/x86/processor.h |   7 ++++
 x86/svm.c           |  16 ++++++--
 x86/svm_tests.c     | 115 ++++++++++++++++++++++++++++++++++++++++++++++++++++
 3 files changed, 134 insertions(+), 4 deletions(-)

Krish Sadhukhan (3):
      KVM: X86: Add a utility function to read current RIP
      KVM: nSVM: Add assembly label to VMRUN instruction
      nSVM: Test effect of host RFLAGS.TF on VMRUN
```
#### [PATCH v14 00/13] SMMUv3 Nested Stage Setup (IOMMU part)
##### From: Eric Auger <eric.auger@redhat.com>

```c
From patchwork Tue Feb 23 20:56:21 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Eric Auger <eric.auger@redhat.com>
X-Patchwork-Id: 12100899
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-15.8 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_PATCH,MAILING_LIST_MULTI,MENTIONS_GIT_HOSTING,SPF_HELO_NONE,SPF_PASS
	autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 8999BC433E0
	for <kvm@archiver.kernel.org>; Tue, 23 Feb 2021 20:59:23 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 5AC6864E02
	for <kvm@archiver.kernel.org>; Tue, 23 Feb 2021 20:59:23 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S234563AbhBWU7Q (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 23 Feb 2021 15:59:16 -0500
Received: from us-smtp-delivery-124.mimecast.com ([63.128.21.124]:23031 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S234536AbhBWU7B (ORCPT
        <rfc822;kvm@vger.kernel.org>); Tue, 23 Feb 2021 15:59:01 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1614113855;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=dspjyoruL6FYvLVfk5NSTgJZHzGM/NlapNw3ZfaV3DI=;
        b=SIXOPfo6TSbrbyYHIjCVHPIxbYU1TihXTK+UWqPc/UKRLA7HXWQ3n6pl7PyOkSUaPmkmBx
        uXOlpzEOyBu5wzsMrHd6P+ebRva6Q11xTXaGi58umFfKvpdw/l8WhvC2r6jL/GhFQFeIkb
        PwTcvUKS96v3Qezjm/+TcbHQgO1dPbY=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-358-iiKcvpHJP16wVJHD1fCK1Q-1; Tue, 23 Feb 2021 15:56:51 -0500
X-MC-Unique: iiKcvpHJP16wVJHD1fCK1Q-1
Received: from smtp.corp.redhat.com (int-mx04.intmail.prod.int.phx2.redhat.com
 [10.5.11.14])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 306A3835E25;
        Tue, 23 Feb 2021 20:56:48 +0000 (UTC)
Received: from laptop.redhat.com (ovpn-114-34.ams2.redhat.com [10.36.114.34])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 6207F5D9D0;
        Tue, 23 Feb 2021 20:56:36 +0000 (UTC)
From: Eric Auger <eric.auger@redhat.com>
To: eric.auger.pro@gmail.com, eric.auger@redhat.com,
        iommu@lists.linux-foundation.org, linux-kernel@vger.kernel.org,
        kvm@vger.kernel.org, kvmarm@lists.cs.columbia.edu, will@kernel.org,
        maz@kernel.org, robin.murphy@arm.com, joro@8bytes.org,
        alex.williamson@redhat.com, tn@semihalf.com, zhukeqian1@huawei.com
Cc: jacob.jun.pan@linux.intel.com, yi.l.liu@intel.com,
        wangxingang5@huawei.com, jiangkunkun@huawei.com,
        jean-philippe@linaro.org, zhangfei.gao@linaro.org,
        zhangfei.gao@gmail.com, vivek.gautam@arm.com,
        shameerali.kolothum.thodi@huawei.com, yuzenghui@huawei.com,
        nicoleotsuka@gmail.com, lushenming@huawei.com, vsethi@nvidia.com
Subject: [PATCH v14 00/13] SMMUv3 Nested Stage Setup (IOMMU part)
Date: Tue, 23 Feb 2021 21:56:21 +0100
Message-Id: <20210223205634.604221-1-eric.auger@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.14
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This series brings the IOMMU part of HW nested paging support
in the SMMUv3. The VFIO part is submitted separately.

This is based on Jean-Philippe's
[PATCH v12 00/10] iommu: I/O page faults for SMMUv3
https://lore.kernel.org/linux-arm-kernel/YBfij71tyYvh8LhB@myrica/T/

The IOMMU API is extended to support 2 new API functionalities:
1) pass the guest stage 1 configuration
2) pass stage 1 MSI bindings

Then those capabilities gets implemented in the SMMUv3 driver.

The virtualizer passes information through the VFIO user API
which cascades them to the iommu subsystem. This allows the guest
to own stage 1 tables and context descriptors (so-called PASID
table) while the host owns stage 2 tables and main configuration
structures (STE).

Best Regards

Eric

This series can be found at:
https://github.com/eauger/linux/tree/v5.11-stallv12-2stage-v14
(including the VFIO part in its last version: v12)

The VFIO series is sent separately.

History:

Previous version (v13):
https://github.com/eauger/linux/tree/5.10-rc4-2stage-v13

v13 -> v14:
- Took into account all received comments I think. Great
  thanks to all the testers for their effort and sometimes
  fixes. I am really grateful to you!
- numerous fixes including guest running in
  noiommu, iommu.strict=0, iommu.passthrough=on,
  enable_unsafe_noiommu_mode

v12 -> v13:
- fixed compilation issue with CONFIG_ARM_SMMU_V3_SVA
  reported by Shameer. This urged me to revisit patch 4 into
  iommu/smmuv3: Allow s1 and s2 configs to coexist where
  s1_cfg and s2_cfg are not dynamically allocated anymore.
  Instead I use a new set field in existing structs
- fixed 2 others config checks
- Updated "iommu/arm-smmu-v3: Maintain a SID->device structure"
  according to the last version

v11 -> v12:
- rebase on top of v5.10-rc4

Eric Auger (13):
  iommu: Introduce attach/detach_pasid_table API
  iommu: Introduce bind/unbind_guest_msi
  iommu/smmuv3: Allow s1 and s2 configs to coexist
  iommu/smmuv3: Get prepared for nested stage support
  iommu/smmuv3: Implement attach/detach_pasid_table
  iommu/smmuv3: Allow stage 1 invalidation with unmanaged ASIDs
  iommu/smmuv3: Implement cache_invalidate
  dma-iommu: Implement NESTED_MSI cookie
  iommu/smmuv3: Nested mode single MSI doorbell per domain enforcement
  iommu/smmuv3: Enforce incompatibility between nested mode and HW MSI
    regions
  iommu/smmuv3: Implement bind/unbind_guest_msi
  iommu/smmuv3: report additional recoverable faults
  iommu/smmuv3: Accept configs with more than one context descriptor

 drivers/iommu/arm/arm-smmu-v3/arm-smmu-v3.c | 444 ++++++++++++++++++--
 drivers/iommu/arm/arm-smmu-v3/arm-smmu-v3.h |  14 +-
 drivers/iommu/dma-iommu.c                   | 142 ++++++-
 drivers/iommu/iommu.c                       | 106 +++++
 include/linux/dma-iommu.h                   |  16 +
 include/linux/iommu.h                       |  47 +++
 include/uapi/linux/iommu.h                  |  54 +++
 7 files changed, 781 insertions(+), 42 deletions(-)
```
#### [PATCH v12 00/13] SMMUv3 Nested Stage Setup (VFIO part)
##### From: Eric Auger <eric.auger@redhat.com>

```c
From patchwork Tue Feb 23 21:06:12 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Eric Auger <eric.auger@redhat.com>
X-Patchwork-Id: 12100935
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-15.8 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_PATCH,MAILING_LIST_MULTI,MENTIONS_GIT_HOSTING,SPF_HELO_NONE,SPF_PASS
	autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 828FEC433DB
	for <kvm@archiver.kernel.org>; Tue, 23 Feb 2021 21:09:59 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 4A18B64E00
	for <kvm@archiver.kernel.org>; Tue, 23 Feb 2021 21:09:59 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S234568AbhBWVJg (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 23 Feb 2021 16:09:36 -0500
Received: from us-smtp-delivery-124.mimecast.com ([216.205.24.124]:33017 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S233095AbhBWVJK (ORCPT
        <rfc822;kvm@vger.kernel.org>); Tue, 23 Feb 2021 16:09:10 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1614114464;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=Rtjtw1poVfgkNxDSJEk53QVG2EcVM1YLyFA8X3R621o=;
        b=Vp1m+uctMW5S9VDbPA3Ls0PEXbH3aACQR/RkFLvwGaR+W9CCFhlpqmxKaD2SKOxbTjh2iq
        1ogjgEBjxtMUBaWtweqWlpxldCBb1E2W8Bsf5I444PbJaH2C365Yag2vXsr47VtTOHPoog
        lvApapy+hpvyJktp2yW3wecWYEOf4ew=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-47-bzSJvXt6NHOnRIBkfNXl-g-1; Tue, 23 Feb 2021 16:06:37 -0500
X-MC-Unique: bzSJvXt6NHOnRIBkfNXl-g-1
Received: from smtp.corp.redhat.com (int-mx04.intmail.prod.int.phx2.redhat.com
 [10.5.11.14])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id AA46ECC620;
        Tue, 23 Feb 2021 21:06:33 +0000 (UTC)
Received: from laptop.redhat.com (ovpn-114-34.ams2.redhat.com [10.36.114.34])
        by smtp.corp.redhat.com (Postfix) with ESMTP id B69535D9D0;
        Tue, 23 Feb 2021 21:06:27 +0000 (UTC)
From: Eric Auger <eric.auger@redhat.com>
To: eric.auger.pro@gmail.com, eric.auger@redhat.com,
        iommu@lists.linux-foundation.org, linux-kernel@vger.kernel.org,
        kvm@vger.kernel.org, kvmarm@lists.cs.columbia.edu, will@kernel.org,
        maz@kernel.org, robin.murphy@arm.com, joro@8bytes.org,
        alex.williamson@redhat.com, tn@semihalf.com, zhukeqian1@huawei.com
Cc: jacob.jun.pan@linux.intel.com, yi.l.liu@intel.com,
        wangxingang5@huawei.com, jiangkunkun@huawei.com,
        jean-philippe@linaro.org, zhangfei.gao@linaro.org,
        zhangfei.gao@gmail.com, vivek.gautam@arm.com,
        shameerali.kolothum.thodi@huawei.com, yuzenghui@huawei.com,
        nicoleotsuka@gmail.com, lushenming@huawei.com, vsethi@nvidia.com
Subject: [PATCH v12 00/13] SMMUv3 Nested Stage Setup (VFIO part)
Date: Tue, 23 Feb 2021 22:06:12 +0100
Message-Id: <20210223210625.604517-1-eric.auger@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.14
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This series brings the VFIO part of HW nested paging support
in the SMMUv3.

This is a rebase on top of v5.11

The series depends on:
[PATCH v14 00/13] SMMUv3 Nested Stage Setup (IOMMU part)

3 new IOCTLs are introduced that allow the userspace to
1) pass the guest stage 1 configuration
2) pass stage 1 MSI bindings
3) invalidate stage 1 related caches

They map onto the related new IOMMU API functions.

We introduce the capability to register specific interrupt
indexes (see [1]). A new DMA_FAULT interrupt index allows to register
an eventfd to be signaled whenever a stage 1 related fault
is detected at physical level. Also two specific regions allow to
- expose the fault records to the user space and
- inject page responses.

This latter functionality is not exercised in this series
but is provided as a POC for further vSVA activities (Shameer's input).

Best Regards

Eric

This series can be found at:
https://github.com/eauger/linux/tree/v5.11-stallv12-2stage-v14

The series series includes Tina's patch steming from
[1] "[RFC PATCH v2 1/3] vfio: Use capability chains to handle device
specific irq" plus patches originally contributed by Yi.

History:

v11 -> v12:
- numerous fixes following feedbacks. Many thanks to all of you
- See individual history log.

v10 -> v11:
- rebase on top of v5.10-rc4
- adapt to changes on the IOMMU API (compliant with the doc
  written by Jacob/Yi)
- addition of the page response region
- Took into account Zenghui's comments
- In this version I have kept the ioctl separate. Since
  Yi's series [2] is currently stalled, I've just rebased here.

[2] [PATCH v7 00/16] vfio: expose virtual Shared Virtual Addressing
to VMs

v9 -> v10
- rebase on top of 5.6.0-rc3 (no change versus v9)

v8 -> v9:
- introduce specific irq framework
- single fault region
- iommu_unregister_device_fault_handler failure case not handled
  yet.

v7 -> v8:
- rebase on top of v5.2-rc1 and especially
  8be39a1a04c1  iommu/arm-smmu-v3: Add a master->domain pointer
- dynamic alloc of s1_cfg/s2_cfg
- __arm_smmu_tlb_inv_asid/s1_range_nosync
- check there is no HW MSI regions
- asid invalidation using pasid extended struct (change in the uapi)
- add s1_live/s2_live checks
- move check about support of nested stages in domain finalise
- fixes in error reporting according to the discussion with Robin
- reordered the patches to have first iommu/smmuv3 patches and then
  VFIO patches

v6 -> v7:
- removed device handle from bind/unbind_guest_msi
- added "iommu/smmuv3: Nested mode single MSI doorbell per domain
  enforcement"
- added few uapi comments as suggested by Jean, Jacop and Alex

v5 -> v6:
- Fix compilation issue when CONFIG_IOMMU_API is unset

v4 -> v5:
- fix bug reported by Vincent: fault handler unregistration now happens in
  vfio_pci_release
- IOMMU_FAULT_PERM_* moved outside of struct definition + small
  uapi changes suggested by Kean-Philippe (except fetch_addr)
- iommu: introduce device fault report API: removed the PRI part.
- see individual logs for more details
- reset the ste abort flag on detach

v3 -> v4:
- took into account Alex, jean-Philippe and Robin's comments on v3
- rework of the smmuv3 driver integration
- add tear down ops for msi binding and PASID table binding
- fix S1 fault propagation
- put fault reporting patches at the beginning of the series following
  Jean-Philippe's request
- update of the cache invalidate and fault API uapis
- VFIO fault reporting rework with 2 separate regions and one mmappable
  segment for the fault queue
- moved to PATCH

v2 -> v3:
- When registering the S1 MSI binding we now store the device handle. This
  addresses Robin's comment about discimination of devices beonging to
  different S1 groups and using different physical MSI doorbells.
- Change the fault reporting API: use VFIO_PCI_DMA_FAULT_IRQ_INDEX to
  set the eventfd and expose the faults through an mmappable fault region

v1 -> v2:
- Added the fault reporting capability
- asid properly passed on invalidation (fix assignment of multiple
  devices)
- see individual change logs for more info


Eric Auger (10):
  vfio: VFIO_IOMMU_SET_MSI_BINDING
  vfio/pci: Add VFIO_REGION_TYPE_NESTED region type
  vfio/pci: Register an iommu fault handler
  vfio/pci: Allow to mmap the fault queue
  vfio/pci: Add framework for custom interrupt indices
  vfio: Add new IRQ for DMA fault reporting
  vfio/pci: Register and allow DMA FAULT IRQ signaling
  vfio: Document nested stage control
  vfio/pci: Register a DMA fault response region
  vfio/pci: Inject page response upon response region fill

Liu, Yi L (2):
  vfio: VFIO_IOMMU_SET_PASID_TABLE
  vfio: VFIO_IOMMU_CACHE_INVALIDATE

Tina Zhang (1):
  vfio: Use capability chains to handle device specific irq

 Documentation/driver-api/vfio.rst   |  77 +++++
 drivers/vfio/pci/vfio_pci.c         | 447 ++++++++++++++++++++++++++--
 drivers/vfio/pci/vfio_pci_intrs.c   |  62 ++++
 drivers/vfio/pci/vfio_pci_private.h |  33 ++
 drivers/vfio/pci/vfio_pci_rdwr.c    |  84 ++++++
 drivers/vfio/vfio_iommu_type1.c     | 178 +++++++++++
 include/uapi/linux/vfio.h           | 141 ++++++++-
 7 files changed, 1002 insertions(+), 20 deletions(-)
```
