

#### [RFC v3 00/11] Introduce VDUSE - vDPA Device in Userspace
##### From: Xie Yongji <xieyongji@bytedance.com>

```c
From patchwork Tue Jan 19 04:59:09 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Xie Yongji <xieyongji@bytedance.com>
X-Patchwork-Id: 12028731
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.8 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_PATCH,MAILING_LIST_MULTI,
	MENTIONS_GIT_HOSTING,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT
	autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id D3D18C433E6
	for <kvm@archiver.kernel.org>; Tue, 19 Jan 2021 05:21:39 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id A7F0722C9D
	for <kvm@archiver.kernel.org>; Tue, 19 Jan 2021 05:21:39 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1732211AbhASFUi (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 19 Jan 2021 00:20:38 -0500
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:44138 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726716AbhASFFP (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 19 Jan 2021 00:05:15 -0500
Received: from mail-pf1-x433.google.com (mail-pf1-x433.google.com
 [IPv6:2607:f8b0:4864:20::433])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 0356CC061575
        for <kvm@vger.kernel.org>; Mon, 18 Jan 2021 21:04:34 -0800 (PST)
Received: by mail-pf1-x433.google.com with SMTP id w18so228822pfu.9
        for <kvm@vger.kernel.org>; Mon, 18 Jan 2021 21:04:34 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=bytedance-com.20150623.gappssmtp.com; s=20150623;
        h=from:to:cc:subject:date:message-id:mime-version
         :content-transfer-encoding;
        bh=8jWaaLZ6u+//lYSPDVEE3dbvuuSNRm/3gTqtS9kbnx0=;
        b=ji14BKRL8km3ujzp9UXDrCdLxYqio1bJdNPB8i24chKWjS842AG68AXO7EXyNe4GOy
         tN7mQEJa6LUIT8EwlVa84DC9oYeQTUFIjbRBN+VgJ6RWzfhdp3ykNONliiDnxzkhDppT
         4Zr9/ylh3jUWmyUJiSC+s8pxZcrSkDNUmVGCtMq0N9o7yfnw8KKfL4eHBPLKScP7vOyl
         OT9Rd6r6vHjAhX9YeMznm0doniZwc6cnT+2mdrKp7IL0QoAtQIUQq4lRetEogSRL5Ua4
         Xvd5N8keEi8DwbTw5+y0Ai3RWeC2+Ua7Omu4/KSKGnp+HRBRXJMBEFxnryorxyaf+0lw
         yiEw==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:mime-version
         :content-transfer-encoding;
        bh=8jWaaLZ6u+//lYSPDVEE3dbvuuSNRm/3gTqtS9kbnx0=;
        b=PWI54XHNm85VKVl9QtUakmuX+GcAUjQDGX+QWI69GNOJ7w/Bu+d/NUnUS3zjpd8mb/
         zpXFko+GJx6socaqIaU9gtET9N6a4j5+zOOb3vFmZ2Sxa529/hRceO+NLbyyf6wre9Ue
         sbc88CrxdCHJC+U9eH5cLGF5WDxDFaJGUhONuX++i0A0OnlfzloaFTfnXL3nSUwLSEcu
         P5l4lUfX66tHwUyN0q4C/zUwlu3JdiUbYawh+5XE/gWRsKKhVfrr4l8gjgByKlUNuTKi
         vn/wrXhVo+WkFYTM4FCNMrfarX2O8pwtG7E0JFFpRhHt9A50pGG7t5CB6z4tFNrtYJ8l
         vwBQ==
X-Gm-Message-State: AOAM532gewxhttdkA2/xENHXr8kZA0mummtWVyMPUgcZ4/24R/PTojrv
        BtijhIS+gdPM5vD6pB2EAlYZ
X-Google-Smtp-Source: 
 ABdhPJyFpBRTz/MrkTBJo4nBAwtDEt9Gy16vrdty4l78WVcz2wkkIZh+z2RUkx80eIw41g+lZuUNbg==
X-Received: by 2002:a62:8fca:0:b029:1a9:39bc:ed37 with SMTP id
 n193-20020a628fca0000b02901a939bced37mr2632663pfd.61.1611032674277;
        Mon, 18 Jan 2021 21:04:34 -0800 (PST)
Received: from localhost ([139.177.225.243])
        by smtp.gmail.com with ESMTPSA id
 m27sm641344pgn.62.2021.01.18.21.04.32
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Mon, 18 Jan 2021 21:04:33 -0800 (PST)
From: Xie Yongji <xieyongji@bytedance.com>
To: mst@redhat.com, jasowang@redhat.com, stefanha@redhat.com,
        sgarzare@redhat.com, parav@nvidia.com, bob.liu@oracle.com,
        hch@infradead.org, rdunlap@infradead.org, willy@infradead.org,
        viro@zeniv.linux.org.uk, axboe@kernel.dk, bcrl@kvack.org,
        corbet@lwn.net
Cc: virtualization@lists.linux-foundation.org, netdev@vger.kernel.org,
        kvm@vger.kernel.org, linux-aio@kvack.org,
        linux-fsdevel@vger.kernel.org
Subject: [RFC v3 00/11] Introduce VDUSE - vDPA Device in Userspace
Date: Tue, 19 Jan 2021 12:59:09 +0800
Message-Id: <20210119045920.447-1-xieyongji@bytedance.com>
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
      --export vduse-blk,id=test,node-name=disk0,writable=on,vduse-id=1,num-queues=16,queue-size=128

The qemu-storage-daemon can be found at https://github.com/bytedance/qemu/tree/vduse

Future work:
  - Improve performance (e.g. zero copy implementation in datapath)
  - Config interrupt support
  - Userspace library (find a way to reuse device emulation code in qemu/rust-vmm)

This is now based on below series:
https://lore.kernel.org/netdev/20201112064005.349268-1-parav@nvidia.com/

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
  eventfd: track eventfd_signal() recursion depth separately in different cases
  eventfd: Increase the recursion depth of eventfd_signal()
  vdpa: Remove the restriction that only supports virtio-net devices
  vhost-vdpa: protect concurrent access to vhost device iotlb
  vdpa: shared virtual addressing support
  vhost-vdpa: Add an opaque pointer for vhost IOTLB
  vdpa: Pass the netlink attributes to ops.dev_add()
  vduse: Introduce VDUSE - vDPA Device in Userspace
  vduse: Add VDUSE_GET_DEV ioctl
  vduse: grab the module's references until there is no vduse device
  vduse: Introduce a workqueue for irq injection

 Documentation/driver-api/vduse.rst                 |   85 ++
 Documentation/userspace-api/ioctl/ioctl-number.rst |    1 +
 drivers/vdpa/Kconfig                               |    7 +
 drivers/vdpa/Makefile                              |    1 +
 drivers/vdpa/ifcvf/ifcvf_main.c                    |    2 +-
 drivers/vdpa/mlx5/net/mlx5_vnet.c                  |    2 +-
 drivers/vdpa/vdpa.c                                |    7 +-
 drivers/vdpa/vdpa_sim/vdpa_sim.c                   |   17 +-
 drivers/vdpa/vdpa_user/Makefile                    |    5 +
 drivers/vdpa/vdpa_user/eventfd.c                   |  229 ++++
 drivers/vdpa/vdpa_user/eventfd.h                   |   48 +
 drivers/vdpa/vdpa_user/iova_domain.c               |  426 +++++++
 drivers/vdpa/vdpa_user/iova_domain.h               |   68 ++
 drivers/vdpa/vdpa_user/vduse.h                     |   62 +
 drivers/vdpa/vdpa_user/vduse_dev.c                 | 1249 ++++++++++++++++++++
 drivers/vhost/iotlb.c                              |    5 +-
 drivers/vhost/vdpa.c                               |  130 +-
 drivers/vhost/vhost.c                              |    4 +-
 fs/aio.c                                           |    3 +-
 fs/eventfd.c                                       |   20 +-
 include/linux/eventfd.h                            |    5 +-
 include/linux/vdpa.h                               |   17 +-
 include/linux/vhost_iotlb.h                        |    8 +-
 include/uapi/linux/vdpa.h                          |    1 +
 include/uapi/linux/vduse.h                         |  126 ++
 25 files changed, 2458 insertions(+), 70 deletions(-)
 create mode 100644 Documentation/driver-api/vduse.rst
 create mode 100644 drivers/vdpa/vdpa_user/Makefile
 create mode 100644 drivers/vdpa/vdpa_user/eventfd.c
 create mode 100644 drivers/vdpa/vdpa_user/eventfd.h
 create mode 100644 drivers/vdpa/vdpa_user/iova_domain.c
 create mode 100644 drivers/vdpa/vdpa_user/iova_domain.h
 create mode 100644 drivers/vdpa/vdpa_user/vduse.h
 create mode 100644 drivers/vdpa/vdpa_user/vduse_dev.c
 create mode 100644 include/uapi/linux/vduse.h
```
#### [PATCH 0/2] s390: uv: small UV fixes
##### From: Janosch Frank <frankja@linux.ibm.com>

```c
From patchwork Tue Jan 19 10:04:00 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Janosch Frank <frankja@linux.ibm.com>
X-Patchwork-Id: 12030465
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-11.8 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_PATCH,MAILING_LIST_MULTI,
	SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT autolearn=unavailable
	autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id A5EFCC4160E
	for <kvm@archiver.kernel.org>; Tue, 19 Jan 2021 18:27:12 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 714D722CAD
	for <kvm@archiver.kernel.org>; Tue, 19 Jan 2021 18:27:12 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2389448AbhASOum (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 19 Jan 2021 09:50:42 -0500
Received: from mx0a-001b2d01.pphosted.com ([148.163.156.1]:64088 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S2389581AbhASKGR (ORCPT
        <rfc822;kvm@vger.kernel.org>); Tue, 19 Jan 2021 05:06:17 -0500
Received: from pps.filterd (m0187473.ppops.net [127.0.0.1])
        by mx0a-001b2d01.pphosted.com (8.16.0.42/8.16.0.42) with SMTP id
 10JA1X6G151764;
        Tue, 19 Jan 2021 05:05:36 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=ibm.com;
 h=from : to : cc : subject
 : date : message-id : mime-version : content-transfer-encoding; s=pp1;
 bh=MvkOlGB+RFnvJiq75XxoiH7oyCh3GyINVvbzK2tCWM4=;
 b=K9U6X4TN/FiYk/SyYKH13ymxkQjDqsLpZxYnTW3BkrL5BRs6s1RkT+6bKGFTBO7SS7Ht
 CoJTdETT+FEyu7Pbpti2cHsprWZ3AnQxOPG/JHvdMZV2wTSyal1GN5e0HKvW+pBTEoq7
 j3idvfbP6d7TYhYwvGzlO/rbVC/oz+BmzHJqn9f9LWzvs3pX95T8mx7zq5qeELAQw1M6
 NfkkqdEprbwJ40CZ6dntk/clGg8PqTVv7Al4FGPTh9+TxJEMErVl0nijp8ZNoN6SwUvx
 ooHAiATBj5IxyQxAHQXnA5F33MZsyggd8XU6Omo4dZrnDH0lbfRa8woIvlppXldF5aSu tw==
Received: from pps.reinject (localhost [127.0.0.1])
        by mx0a-001b2d01.pphosted.com with ESMTP id 365vx10rf7-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Tue, 19 Jan 2021 05:05:35 -0500
Received: from m0187473.ppops.net (m0187473.ppops.net [127.0.0.1])
        by pps.reinject (8.16.0.36/8.16.0.36) with SMTP id 10JA1X3u151767;
        Tue, 19 Jan 2021 05:05:28 -0500
Received: from ppma06fra.de.ibm.com (48.49.7a9f.ip4.static.sl-reverse.com
 [159.122.73.72])
        by mx0a-001b2d01.pphosted.com with ESMTP id 365vx10r3b-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Tue, 19 Jan 2021 05:05:28 -0500
Received: from pps.filterd (ppma06fra.de.ibm.com [127.0.0.1])
        by ppma06fra.de.ibm.com (8.16.0.42/8.16.0.42) with SMTP id
 10JA3xb0022520;
        Tue, 19 Jan 2021 10:05:02 GMT
Received: from b06avi18626390.portsmouth.uk.ibm.com
 (b06avi18626390.portsmouth.uk.ibm.com [9.149.26.192])
        by ppma06fra.de.ibm.com with ESMTP id 363qdh9h41-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Tue, 19 Jan 2021 10:05:02 +0000
Received: from d06av22.portsmouth.uk.ibm.com (d06av22.portsmouth.uk.ibm.com
 [9.149.105.58])
        by b06avi18626390.portsmouth.uk.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id 10JA4rdZ16122366
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Tue, 19 Jan 2021 10:04:53 GMT
Received: from d06av22.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 65E804C04A;
        Tue, 19 Jan 2021 10:04:59 +0000 (GMT)
Received: from d06av22.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 57E324C05C;
        Tue, 19 Jan 2021 10:04:58 +0000 (GMT)
Received: from linux01.pok.stglabs.ibm.com (unknown [9.114.17.81])
        by d06av22.portsmouth.uk.ibm.com (Postfix) with ESMTP;
        Tue, 19 Jan 2021 10:04:58 +0000 (GMT)
From: Janosch Frank <frankja@linux.ibm.com>
To: linux-kernel@vger.kernel.org
Cc: kvm@vger.kernel.org, thuth@redhat.com, david@redhat.com,
        borntraeger@de.ibm.com, imbrenda@linux.ibm.com, cohuck@redhat.com,
        linux-s390@vger.kernel.org, gor@linux.ibm.com,
        mihajlov@linux.ibm.com
Subject: [PATCH 0/2] s390: uv: small UV fixes
Date: Tue, 19 Jan 2021 05:04:00 -0500
Message-Id: <20210119100402.84734-1-frankja@linux.ibm.com>
X-Mailer: git-send-email 2.25.1
MIME-Version: 1.0
X-TM-AS-GCONF: 00
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.343,18.0.737
 definitions=2021-01-19_02:2021-01-18,2021-01-19 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 spamscore=0 phishscore=0
 adultscore=0 impostorscore=0 mlxlogscore=719 priorityscore=1501
 lowpriorityscore=0 bulkscore=0 suspectscore=0 mlxscore=0 clxscore=1015
 malwarescore=0 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.12.0-2009150000 definitions=main-2101190058
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Two small fixes:
    * Handle 3d PGMs where the address space id is not known
    * Clean up the UV query VCPU number field naming (it's N-1 not N as number in this context means ID)

Janosch Frank (2):
  s390: uv: Fix sysfs max number of VCPUs reporting
  s390: mm: Fix secure storage access exception handling

 arch/s390/boot/uv.c        |  2 +-
 arch/s390/include/asm/uv.h |  4 ++--
 arch/s390/kernel/uv.c      |  2 +-
 arch/s390/mm/fault.c       | 14 ++++++++++++++
 4 files changed, 18 insertions(+), 4 deletions(-)
```
#### [PATCH V2 0/9] vfio virtual address update
##### From: Steve Sistare <steven.sistare@oracle.com>

```c
From patchwork Tue Jan 19 17:48:20 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Steven Sistare <steven.sistare@oracle.com>
X-Patchwork-Id: 12030483
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-13.9 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,UNPARSEABLE_RELAY,
	USER_AGENT_GIT autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 93135C4151A
	for <kvm@archiver.kernel.org>; Tue, 19 Jan 2021 18:30:15 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 6DA6F22CAD
	for <kvm@archiver.kernel.org>; Tue, 19 Jan 2021 18:30:15 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2392593AbhASSZu (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 19 Jan 2021 13:25:50 -0500
Received: from aserp2120.oracle.com ([141.146.126.78]:41650 "EHLO
        aserp2120.oracle.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1731808AbhASSQr (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 19 Jan 2021 13:16:47 -0500
Received: from pps.filterd (aserp2120.oracle.com [127.0.0.1])
        by aserp2120.oracle.com (8.16.0.42/8.16.0.42) with SMTP id
 10JIADZs064407;
        Tue, 19 Jan 2021 18:16:02 GMT
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=oracle.com;
 h=from : to : cc :
 subject : date : message-id; s=corp-2020-01-29;
 bh=vgp9jsVnFm/gP6aJyenQcGYZM+2qBozeWW8dnlKiEEo=;
 b=qHU0go1B6VsVYjzpALx9Y1o/w7OLso2lPAuiV/zNipaUWqQAXRDNvPYqkR39chtleZm2
 PhRkgAWRo7NEtl+nWUuJH0qbKM8YP4BRvuFXn/bQojA68XtdUW4FwVqADevDB6M7Mzf7
 X6XPJgjy1ROWC+0fzfwAi3EXynyMo05vv/R/oyQBSqulHhULO+0+Y2kR2qg+G25tvrPp
 G70eyHiphjEr8Umk08E8KDLeGOMkokCh8dHzjS0UaVVfUJRbW/qJv4euGpAFStFFnolS
 mA91/jvmsyIY3/oQX2I0NdORwo3M41tJhS5ERsgAjAdxiF1iW0TtCqCYeTBWlPVjwDJ+ dQ==
Received: from userp3020.oracle.com (userp3020.oracle.com [156.151.31.79])
        by aserp2120.oracle.com with ESMTP id 363r3ktcpb-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Tue, 19 Jan 2021 18:16:02 +0000
Received: from pps.filterd (userp3020.oracle.com [127.0.0.1])
        by userp3020.oracle.com (8.16.0.42/8.16.0.42) with SMTP id
 10JIAdkQ051066;
        Tue, 19 Jan 2021 18:16:00 GMT
Received: from aserv0121.oracle.com (aserv0121.oracle.com [141.146.126.235])
        by userp3020.oracle.com with ESMTP id 3661khmfr8-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Tue, 19 Jan 2021 18:16:00 +0000
Received: from abhmp0001.oracle.com (abhmp0001.oracle.com [141.146.116.7])
        by aserv0121.oracle.com (8.14.4/8.13.8) with ESMTP id 10JIFxPc027489;
        Tue, 19 Jan 2021 18:15:59 GMT
Received: from ca-dev63.us.oracle.com (/10.211.8.221)
        by default (Oracle Beehive Gateway v4.0)
        with ESMTP ; Tue, 19 Jan 2021 10:15:59 -0800
From: Steve Sistare <steven.sistare@oracle.com>
To: kvm@vger.kernel.org
Cc: Alex Williamson <alex.williamson@redhat.com>,
        Cornelia Huck <cohuck@redhat.com>,
        Kirti Wankhede <kwankhede@nvidia.com>,
        Steve Sistare <steven.sistare@oracle.com>
Subject: [PATCH V2 0/9] vfio virtual address update
Date: Tue, 19 Jan 2021 09:48:20 -0800
Message-Id: <1611078509-181959-1-git-send-email-steven.sistare@oracle.com>
X-Mailer: git-send-email 1.8.3.1
X-Proofpoint-Virus-Version: vendor=nai engine=6000 definitions=9869
 signatures=668683
X-Proofpoint-Spam-Details: rule=notspam policy=default score=0 mlxlogscore=999
 malwarescore=0
 phishscore=0 mlxscore=0 adultscore=0 spamscore=0 bulkscore=0
 suspectscore=0 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.12.0-2009150000 definitions=main-2101190102
X-Proofpoint-Virus-Version: vendor=nai engine=6000 definitions=9869
 signatures=668683
X-Proofpoint-Spam-Details: rule=notspam policy=default score=0 mlxlogscore=999
 bulkscore=0 spamscore=0
 clxscore=1015 lowpriorityscore=0 priorityscore=1501 mlxscore=0
 malwarescore=0 phishscore=0 suspectscore=0 impostorscore=0 adultscore=0
 classifier=spam adjust=0 reason=mlx scancount=1 engine=8.12.0-2009150000
 definitions=main-2101190102
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Add interfaces that allow the underlying memory object of an iova range
to be mapped to a new virtual address in the host process:

  - VFIO_DMA_UNMAP_FLAG_VADDR for VFIO_IOMMU_UNMAP_DMA
  - VFIO_DMA_MAP_FLAG_VADDR flag for VFIO_IOMMU_MAP_DMA
  - VFIO_UPDATE_VADDR for VFIO_CHECK_EXTENSION
  - VFIO_DMA_UNMAP_FLAG_ALL for VFIO_IOMMU_UNMAP_DMA
  - VFIO_UNMAP_ALL for VFIO_CHECK_EXTENSION

Unmap-vaddr invalidates the host virtual address in an iova range and blocks
vfio translation of host virtual addresses, but DMA to already-mapped pages
continues.  Map-vaddr updates the base VA and resumes translation.  The
implementation supports iommu type1 and mediated devices.  Unmap-all allows
all ranges to be unmapped or invalidated in a single ioctl, which simplifies
userland code.

This functionality is necessary for live update, in which a host process
such as qemu exec's an updated version of itself, while preserving its
guest and vfio devices.  The process blocks vfio VA translation, exec's
its new self, mmap's the memory object(s) underlying vfio object, updates
the VA, and unblocks translation.  For a working example that uses these
new interfaces, see the QEMU patch series "[PATCH V2] Live Update" at
https://lore.kernel.org/qemu-devel/1609861330-129855-1-git-send-email-steven.sistare@oracle.com

Patches 1-4 define and implement the flag to unmap all ranges.
Patches 5-6 define and implement the flags to update vaddr.
Patches 7-9 add blocking to complete the implementation.

Changes from V1:
 - define a flag for unmap all instead of special range values
 - define the VFIO_UNMAP_ALL extension
 - forbid the combination of unmap-all and get-dirty-bitmap
 - unwind in unmap on vaddr error
 - add a new function to find first dma in a range instead of modifying
   an existing function
 - change names of update flags
 - fix concurrency bugs due to iommu lock being dropped
 - call down from from vfio to a new backend interface instead of up from
   driver to detect container close
 - use wait/wake instead of sleep and polling
 - refine the uapi specification
 - split patches into vfio vs type1

Steve Sistare (9):
  vfio: option to unmap all
  vfio/type1: find first dma
  vfio/type1: unmap cleanup
  vfio/type1: implement unmap all
  vfio: interfaces to update vaddr
  vfio/type1: implement interfaces to update vaddr
  vfio: iommu driver notify callback
  vfio/type1: implement notify callback
  vfio/type1: block on invalid vaddr

 drivers/vfio/vfio.c             |   5 +
 drivers/vfio/vfio_iommu_type1.c | 229 ++++++++++++++++++++++++++++++++++------
 include/linux/vfio.h            |   5 +
 include/uapi/linux/vfio.h       |  27 +++++
 4 files changed, 231 insertions(+), 35 deletions(-)
```
#### [kvm-unit-tests PATCH v3 0/3] s390x: css: pv: css test adaptation for
##### From: Pierre Morel <pmorel@linux.ibm.com>

```c
From patchwork Tue Jan 19 19:52:21 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Pierre Morel <pmorel@linux.ibm.com>
X-Patchwork-Id: 12030651
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-11.8 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_PATCH,MAILING_LIST_MULTI,
	SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT autolearn=ham autolearn_force=no
	version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id D1255C433E0
	for <kvm@archiver.kernel.org>; Tue, 19 Jan 2021 19:53:53 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 7E3C223107
	for <kvm@archiver.kernel.org>; Tue, 19 Jan 2021 19:53:53 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729215AbhASTxf (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 19 Jan 2021 14:53:35 -0500
Received: from mx0a-001b2d01.pphosted.com ([148.163.156.1]:57702 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1729810AbhASTxM (ORCPT
        <rfc822;kvm@vger.kernel.org>); Tue, 19 Jan 2021 14:53:12 -0500
Received: from pps.filterd (m0098399.ppops.net [127.0.0.1])
        by mx0a-001b2d01.pphosted.com (8.16.0.42/8.16.0.42) with SMTP id
 10JJqBEd140590;
        Tue, 19 Jan 2021 14:52:31 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=ibm.com;
 h=from : to : cc : subject
 : date : message-id; s=pp1;
 bh=HEBdN8lbpr3SIK7UyL8oZxUuzKeTZ2/1D2AcPLYxDlQ=;
 b=aHnVcxgIIvZ0u5MKQYyy3I6uX8agqHc6cQL5LZ9lKYlkmxydwx46EOU5l/33pEs7On6B
 qTclfkcXXhXsQfWDoYgtSYQdzfPYlhpZoofhYUJgYeDsaNkU2f9nbr7Kz3MFpRI8Cj+h
 MECmdYB5zu7NcbYzsQHlt3hYiFRbP8acdfWGH7u7l0yla2a8ihJxDX2dKPyh84rjSRGS
 8kWDB+GN/QN89QgHdV6yn3HjqNxL2ZiC4maJzWzKvUC8YTgC9T+3zfYC11RsRDCHWBYv
 /CwQ4K+xk6KeL9AqvAmxBSuu+ZIgjcekKjbbeO1HIWKEUyojd0fv+yG7yUZrgRhvHadt Sg==
Received: from pps.reinject (localhost [127.0.0.1])
        by mx0a-001b2d01.pphosted.com with ESMTP id 3665y3004q-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Tue, 19 Jan 2021 14:52:31 -0500
Received: from m0098399.ppops.net (m0098399.ppops.net [127.0.0.1])
        by pps.reinject (8.16.0.36/8.16.0.36) with SMTP id 10JJqTJR140934;
        Tue, 19 Jan 2021 14:52:31 -0500
Received: from ppma04fra.de.ibm.com (6a.4a.5195.ip4.static.sl-reverse.com
 [149.81.74.106])
        by mx0a-001b2d01.pphosted.com with ESMTP id 3665y30046-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Tue, 19 Jan 2021 14:52:31 -0500
Received: from pps.filterd (ppma04fra.de.ibm.com [127.0.0.1])
        by ppma04fra.de.ibm.com (8.16.0.42/8.16.0.42) with SMTP id
 10JJq7PC029857;
        Tue, 19 Jan 2021 19:52:28 GMT
Received: from b06cxnps3075.portsmouth.uk.ibm.com
 (d06relay10.portsmouth.uk.ibm.com [9.149.109.195])
        by ppma04fra.de.ibm.com with ESMTP id 363t0y9qf1-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Tue, 19 Jan 2021 19:52:28 +0000
Received: from d06av24.portsmouth.uk.ibm.com (d06av24.portsmouth.uk.ibm.com
 [9.149.105.60])
        by b06cxnps3075.portsmouth.uk.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id 10JJqPoG49086814
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Tue, 19 Jan 2021 19:52:26 GMT
Received: from d06av24.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id D6CE042041;
        Tue, 19 Jan 2021 19:52:25 +0000 (GMT)
Received: from d06av24.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 675B14203F;
        Tue, 19 Jan 2021 19:52:25 +0000 (GMT)
Received: from oc3016276355.ibm.com (unknown [9.145.38.46])
        by d06av24.portsmouth.uk.ibm.com (Postfix) with ESMTP;
        Tue, 19 Jan 2021 19:52:25 +0000 (GMT)
From: Pierre Morel <pmorel@linux.ibm.com>
To: kvm@vger.kernel.org
Cc: linux-s390@vger.kernel.org, frankja@linux.ibm.com,
        david@redhat.com, thuth@redhat.com, cohuck@redhat.com,
        imbrenda@linux.ibm.com, drjones@redhat.com, pbonzini@redhat.com
Subject: [kvm-unit-tests PATCH v3 0/3] s390x: css: pv: css test adaptation for
 PV
Date: Tue, 19 Jan 2021 20:52:21 +0100
Message-Id: <1611085944-21609-1-git-send-email-pmorel@linux.ibm.com>
X-Mailer: git-send-email 1.8.3.1
X-TM-AS-GCONF: 00
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.343,18.0.737
 definitions=2021-01-19_09:2021-01-18,2021-01-19 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 priorityscore=1501
 impostorscore=0 mlxscore=0 adultscore=0 phishscore=0 bulkscore=0
 malwarescore=0 lowpriorityscore=0 suspectscore=0 clxscore=1015 spamscore=0
 mlxlogscore=999 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.12.0-2009150000 definitions=main-2101190106
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Hi all,

To adapt the CSS I/O tests to protected virtualisation we need
utilities to:

1- allocate the I/O buffers in a private page using (patch 2)
   It must be in a dedicated page to avoid exporting code or
   guest private data to the host.

2- share the I/O buffers with the host (patch 1)
   This patch uses the page allocator reworked by Claudio.

The 2 first patches are the implementation of the tools,
patch 3 is the modification of the css.c test for PV.

regards,
Pierre

Pierre Morel (3):
  s390x: pv: implement routine to share/unshare memory
  s390x: define UV compatible I/O allocation
  s390x: css: pv: css test adaptation for PV

 lib/s390x/asm/uv.h    | 38 ++++++++++++++++++++++++++++++++
 lib/s390x/css.h       |  3 +--
 lib/s390x/css_lib.c   | 28 +++++++-----------------
 lib/s390x/malloc_io.c | 50 +++++++++++++++++++++++++++++++++++++++++++
 lib/s390x/malloc_io.h | 18 ++++++++++++++++
 s390x/Makefile        |  1 +
 s390x/css.c           | 35 ++++++++++++++++++++----------
 7 files changed, 140 insertions(+), 33 deletions(-)
 create mode 100644 lib/s390x/malloc_io.c
 create mode 100644 lib/s390x/malloc_io.h
```
#### [PATCH 0/4] vfio-pci/zdev: Fixing s390 vfio-pci ISM support
##### From: Matthew Rosato <mjrosato@linux.ibm.com>

```c
From patchwork Tue Jan 19 20:02:26 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Matthew Rosato <mjrosato@linux.ibm.com>
X-Patchwork-Id: 12030713
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-11.8 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_PATCH,MAILING_LIST_MULTI,
	SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT autolearn=unavailable
	autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 4C10AC433DB
	for <kvm@archiver.kernel.org>; Tue, 19 Jan 2021 20:26:49 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 089D523107
	for <kvm@archiver.kernel.org>; Tue, 19 Jan 2021 20:26:49 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2390207AbhASUYd (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 19 Jan 2021 15:24:33 -0500
Received: from mx0a-001b2d01.pphosted.com ([148.163.156.1]:17452 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1729879AbhASUYS (ORCPT
        <rfc822;kvm@vger.kernel.org>); Tue, 19 Jan 2021 15:24:18 -0500
Received: from pps.filterd (m0098394.ppops.net [127.0.0.1])
        by mx0a-001b2d01.pphosted.com (8.16.0.42/8.16.0.42) with SMTP id
 10JK9IDq030472;
        Tue, 19 Jan 2021 15:23:37 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=ibm.com;
 h=from : to : cc : subject
 : date : message-id; s=pp1;
 bh=CgSsfo6tp9hSiTZkAFnCJTkRoXKqZJ7jQPMtbVTHtPk=;
 b=ky+EvvPueMNC2hLk6CBsStkhxNJ/8OSE32/EWHBN7zz0eOkbVR9Ri1F1Ou3xvo094kRW
 KyL4KnnYshnpE6U2BYCz9aHbagFwqZITaRJ/+XlnPzcVRMfljKplFTDvaqQCDEOlSQto
 ge1Zv+sAf+7ukKGbujCU2raBBVZRpwOot1B3roKKKeBLeEqDca+I0e7+mrH4Av1tj6jd
 5SF9l9UzyWXDcVh2f8i6L7a5T0YDvYm+dooiM2RLgEabUzNAIMAndoCSOWxyFgu0LVTK
 lQ0CZvMxSWTd0/i82/k5zQsLN2zM2Z0d/OpOTeLvQLO0zhJHPjcFdagMsrqZt5x6bSBj Ug==
Received: from pps.reinject (localhost [127.0.0.1])
        by mx0a-001b2d01.pphosted.com with ESMTP id 3665wngp45-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Tue, 19 Jan 2021 15:23:37 -0500
Received: from m0098394.ppops.net (m0098394.ppops.net [127.0.0.1])
        by pps.reinject (8.16.0.36/8.16.0.36) with SMTP id 10JKAdK3037857;
        Tue, 19 Jan 2021 15:23:37 -0500
Received: from ppma01wdc.us.ibm.com (fd.55.37a9.ip4.static.sl-reverse.com
 [169.55.85.253])
        by mx0a-001b2d01.pphosted.com with ESMTP id 3665wngp3e-2
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Tue, 19 Jan 2021 15:23:37 -0500
Received: from pps.filterd (ppma01wdc.us.ibm.com [127.0.0.1])
        by ppma01wdc.us.ibm.com (8.16.0.42/8.16.0.42) with SMTP id
 10JJqvs9013310;
        Tue, 19 Jan 2021 20:02:36 GMT
Received: from b01cxnp22035.gho.pok.ibm.com (b01cxnp22035.gho.pok.ibm.com
 [9.57.198.25])
        by ppma01wdc.us.ibm.com with ESMTP id 363qs90qq2-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Tue, 19 Jan 2021 20:02:36 +0000
Received: from b01ledav006.gho.pok.ibm.com (b01ledav006.gho.pok.ibm.com
 [9.57.199.111])
        by b01cxnp22035.gho.pok.ibm.com (8.14.9/8.14.9/NCO v10.0) with ESMTP
 id 10JK2Zaa31064398
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Tue, 19 Jan 2021 20:02:35 GMT
Received: from b01ledav006.gho.pok.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 414DDAC05E;
        Tue, 19 Jan 2021 20:02:35 +0000 (GMT)
Received: from b01ledav006.gho.pok.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 4F4E3AC05B;
        Tue, 19 Jan 2021 20:02:33 +0000 (GMT)
Received: from oc4221205838.ibm.com (unknown [9.211.56.144])
        by b01ledav006.gho.pok.ibm.com (Postfix) with ESMTP;
        Tue, 19 Jan 2021 20:02:33 +0000 (GMT)
From: Matthew Rosato <mjrosato@linux.ibm.com>
To: alex.williamson@redhat.com, cohuck@redhat.com,
        schnelle@linux.ibm.com
Cc: pmorel@linux.ibm.com, borntraeger@de.ibm.com, hca@linux.ibm.com,
        gor@linux.ibm.com, gerald.schaefer@linux.ibm.com,
        linux-s390@vger.kernel.org, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org
Subject: [PATCH 0/4] vfio-pci/zdev: Fixing s390 vfio-pci ISM support
Date: Tue, 19 Jan 2021 15:02:26 -0500
Message-Id: <1611086550-32765-1-git-send-email-mjrosato@linux.ibm.com>
X-Mailer: git-send-email 1.8.3.1
X-TM-AS-GCONF: 00
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.343,18.0.737
 definitions=2021-01-19_09:2021-01-18,2021-01-19 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 malwarescore=0
 mlxlogscore=999 mlxscore=0 lowpriorityscore=0 adultscore=0 suspectscore=0
 priorityscore=1501 spamscore=0 impostorscore=0 bulkscore=0 clxscore=1015
 phishscore=0 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.12.0-2009150000 definitions=main-2101190110
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Today, ISM devices are completely disallowed for vfio-pci passthrough as
QEMU will reject the device due to an (inappropriate) MSI-X check.
However, in an effort to enable ISM device passthrough, I realized that the
manner in which ISM performs block write operations is highly incompatible
with the way that QEMU s390 PCI instruction interception and
vfio_pci_bar_rw break up I/O operations into 8B and 4B operations -- ISM
devices have particular requirements in regards to the alignment, size and
order of writes performed.  Furthermore, they require that legacy/non-MIO
s390 PCI instructions are used, which is also not guaranteed when the I/O
is passed through the typical userspace channels.

As a result, this patchset proposes a new VFIO region to allow a guest to
pass certain PCI instruction intercepts directly to the s390 host kernel
PCI layer for execution, pinning the guest buffer in memory briefly in
order to execute the requested PCI instruction.

Changes from RFC -> v1:
- No functional changes, just minor commentary changes -- Re-posting along
with updated QEMU set.

Matthew Rosato (4):
  s390/pci: track alignment/length strictness for zpci_dev
  vfio-pci/zdev: Pass the relaxed alignment flag
  s390/pci: Get hardware-reported max store block length
  vfio-pci/zdev: Introduce the zPCI I/O vfio region

 arch/s390/include/asm/pci.h         |   4 +-
 arch/s390/include/asm/pci_clp.h     |   7 +-
 arch/s390/pci/pci_clp.c             |   2 +
 drivers/vfio/pci/vfio_pci.c         |   8 ++
 drivers/vfio/pci/vfio_pci_private.h |   6 ++
 drivers/vfio/pci/vfio_pci_zdev.c    | 160 ++++++++++++++++++++++++++++++++++++
 include/uapi/linux/vfio.h           |   4 +
 include/uapi/linux/vfio_zdev.h      |  34 ++++++++
 8 files changed, 222 insertions(+), 3 deletions(-)
```
