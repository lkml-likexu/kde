

#### [RFC v2 00/13] Introduce VDUSE - vDPA Device in Userspace
##### From: Xie Yongji <xieyongji@bytedance.com>

```c
From patchwork Tue Dec 22 14:52:08 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Xie Yongji <xieyongji@bytedance.com>
X-Patchwork-Id: 11986849
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.8 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_PATCH,MAILING_LIST_MULTI,
	MENTIONS_GIT_HOSTING,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT
	autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 0788BC433E9
	for <kvm@archiver.kernel.org>; Tue, 22 Dec 2020 14:53:49 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id CFDB9229C6
	for <kvm@archiver.kernel.org>; Tue, 22 Dec 2020 14:53:48 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727534AbgLVOxp (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 22 Dec 2020 09:53:45 -0500
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:43352 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1727071AbgLVOxp (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 22 Dec 2020 09:53:45 -0500
Received: from mail-pf1-x42e.google.com (mail-pf1-x42e.google.com
 [IPv6:2607:f8b0:4864:20::42e])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 1E83CC0613D6
        for <kvm@vger.kernel.org>; Tue, 22 Dec 2020 06:53:05 -0800 (PST)
Received: by mail-pf1-x42e.google.com with SMTP id f9so8581935pfc.11
        for <kvm@vger.kernel.org>; Tue, 22 Dec 2020 06:53:05 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=bytedance-com.20150623.gappssmtp.com; s=20150623;
        h=from:to:cc:subject:date:message-id:mime-version
         :content-transfer-encoding;
        bh=uiVGkob1gIqqC6Yzdq61jcy8JuwOajeN/SctQX1aUtg=;
        b=ZTxAYCSGC8X1EFhnSJtDZlZc174+Df9IOXG7cK889ItQ/qcEeVbeGRpDqSwh9Z9Mfr
         N7Gb9xP8GDJT4GlkK+Ri/ln1/loWzNHiRlMzzNZgYCqEvqbgkMSlDOmawzAaH7XTXxIp
         +SQd2zkvD9Yxj4r5QKWJuyRD3AJ6mO6D78sXrL3RskvTd+c9Lu4vAjAkPYX9a8zxilIP
         UGfVd70ao7V/bffzBmsyfKOBRctU7PRbHNNWQy9JIjeIzWkscNjH9qWcbnsaB6kpPOVs
         1LDVEgnXfA1dccGSSikvEyIABwt0nwbGSZ2/uOr7efuhnnTOjHcx9WMr52IpTjdRv22O
         TlLg==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:mime-version
         :content-transfer-encoding;
        bh=uiVGkob1gIqqC6Yzdq61jcy8JuwOajeN/SctQX1aUtg=;
        b=JC0ICsH7jCU2BkvtWx/8aojfimKsVhwJKIGqYd7l6RId3GMd/3UgwppRPY2SrUde+D
         dGUSpcA3IXzY3j/NyyixoUSNSRpS/UCymDiAtr5UUKPEFalOvXoiOKaK6SdlEEKFlwAX
         49Pqm5Wa4L9rdPIyh1tMJp8M1J4y78YG0vEaFQLUOTjkOSdW5PA5/fuTbQpeoN7PcJ2z
         ek2jlljfSUy9CXgSKa6lMFgVYACTLSekuQd3+dlNgpJr1oYxc76LuHEjSCTeF1WVn9lW
         VtLJNGpjqHpKfFy+itoPnNC4YMZD18tC/Z82U4amx1PVYzdMhYVYvyRrXa9zHI/eGvRA
         u1MQ==
X-Gm-Message-State: AOAM532GfJmTGdBW5j/AkRNzK1RILJjD2FRvjIyj30ql7qcektm+haIK
        I9RR/5/JH0Mm7B4WFIBFoTtI
X-Google-Smtp-Source: 
 ABdhPJwOMZhlfbC+XRg0aWjA1Uit6jsytMTGwMgMGXRmVCuqrlGhh91ghHicYK7Hi8vTgPn0PDTGfw==
X-Received: by 2002:a63:9dcf:: with SMTP id
 i198mr19940882pgd.242.1608648784515;
        Tue, 22 Dec 2020 06:53:04 -0800 (PST)
Received: from localhost ([139.177.225.248])
        by smtp.gmail.com with ESMTPSA id
 u1sm19156507pjr.51.2020.12.22.06.53.02
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Tue, 22 Dec 2020 06:53:03 -0800 (PST)
From: Xie Yongji <xieyongji@bytedance.com>
To: mst@redhat.com, jasowang@redhat.com, stefanha@redhat.com,
        sgarzare@redhat.com, parav@nvidia.com, akpm@linux-foundation.org,
        rdunlap@infradead.org, willy@infradead.org,
        viro@zeniv.linux.org.uk, axboe@kernel.dk, bcrl@kvack.org,
        corbet@lwn.net
Cc: virtualization@lists.linux-foundation.org, netdev@vger.kernel.org,
        kvm@vger.kernel.org, linux-aio@kvack.org,
        linux-fsdevel@vger.kernel.org, linux-mm@kvack.org
Subject: [RFC v2 00/13] Introduce VDUSE - vDPA Device in Userspace
Date: Tue, 22 Dec 2020 22:52:08 +0800
Message-Id: <20201222145221.711-1-xieyongji@bytedance.com>
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

V1 to V2:
- Add vhost-vdpa support
- Add some documents
- Based on the vdpa management tool
- Introduce a workqueue for irq injection
- Replace interval tree with array map to store the iova_map

Xie Yongji (13):
  mm: export zap_page_range() for driver use
  eventfd: track eventfd_signal() recursion depth separately in different cases
  eventfd: Increase the recursion depth of eventfd_signal()
  vdpa: Remove the restriction that only supports virtio-net devices
  vdpa: Pass the netlink attributes to ops.dev_add()
  vduse: Introduce VDUSE - vDPA Device in Userspace
  vduse: support get/set virtqueue state
  vdpa: Introduce process_iotlb_msg() in vdpa_config_ops
  vduse: Add support for processing vhost iotlb message
  vduse: grab the module's references until there is no vduse device
  vduse/iova_domain: Support reclaiming bounce pages
  vduse: Add memory shrinker to reclaim bounce pages
  vduse: Introduce a workqueue for irq injection

 Documentation/driver-api/vduse.rst                 |   91 ++
 Documentation/userspace-api/ioctl/ioctl-number.rst |    1 +
 drivers/vdpa/Kconfig                               |    8 +
 drivers/vdpa/Makefile                              |    1 +
 drivers/vdpa/vdpa.c                                |    2 +-
 drivers/vdpa/vdpa_sim/vdpa_sim.c                   |    3 +-
 drivers/vdpa/vdpa_user/Makefile                    |    5 +
 drivers/vdpa/vdpa_user/eventfd.c                   |  229 ++++
 drivers/vdpa/vdpa_user/eventfd.h                   |   48 +
 drivers/vdpa/vdpa_user/iova_domain.c               |  517 ++++++++
 drivers/vdpa/vdpa_user/iova_domain.h               |  103 ++
 drivers/vdpa/vdpa_user/vduse.h                     |   59 +
 drivers/vdpa/vdpa_user/vduse_dev.c                 | 1373 ++++++++++++++++++++
 drivers/vhost/vdpa.c                               |   34 +-
 fs/aio.c                                           |    3 +-
 fs/eventfd.c                                       |   20 +-
 include/linux/eventfd.h                            |    5 +-
 include/linux/vdpa.h                               |   11 +-
 include/uapi/linux/vdpa.h                          |    1 +
 include/uapi/linux/vduse.h                         |  119 ++
 mm/memory.c                                        |    1 +
 21 files changed, 2598 insertions(+), 36 deletions(-)
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
#### [PATCH v2 0/2] x86: Add the feature Virtual SPEC_CTRL
##### From: Babu Moger <babu.moger@amd.com>

```c
From patchwork Tue Dec 22 22:31:26 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Babu Moger <babu.moger@amd.com>
X-Patchwork-Id: 11987373
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-8.7 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_PATCH,MAILING_LIST_MULTI,
	MSGID_FROM_MTA_HEADER,SPF_HELO_NONE,SPF_PASS autolearn=ham autolearn_force=no
	version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 00FDEC433E0
	for <kvm@archiver.kernel.org>; Tue, 22 Dec 2020 22:32:40 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id CC6FE22573
	for <kvm@archiver.kernel.org>; Tue, 22 Dec 2020 22:32:39 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728480AbgLVWcX (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 22 Dec 2020 17:32:23 -0500
Received: from mail-bn8nam08on2053.outbound.protection.outlook.com
 ([40.107.100.53]:4961
        "EHLO NAM04-BN8-obe.outbound.protection.outlook.com"
        rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org with ESMTP
        id S1728107AbgLVWcX (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 22 Dec 2020 17:32:23 -0500
ARC-Seal: i=1; a=rsa-sha256; s=arcselector9901; d=microsoft.com; cv=none;
 b=bkzy+SUttUwmMB6gQt9OX4EIKLuxBs/ox8/xtl1AhjwccM5k5bPedFgGjnUoF1j9GhdNJX53zUTkgQaNT0zSB91T0e1RJqvSjY0TjNRGD8Y5bmBYIaFLc3gRKZkE1TmPqSPXtK4oZ6A4eYA6CK7heqohiIA41DsvHkrI5j5t6l3S4lX6ezDOpPr0lxzAT+UrQhLumUgyxvfk7+Y9PQXdBwHbSIFFlO67HjjTtvHwfO8MD1xOpna3zpNjh4RvftvKYi4aSBr2Y1788HFtgdSSGEQNL1RpT4MLMIqFhzQ2kd11EKrqUS24DdhoDtyJtBLPA+QCzyXChi59AhzUV3J5dg==
ARC-Message-Signature: i=1; a=rsa-sha256; c=relaxed/relaxed; d=microsoft.com;
 s=arcselector9901;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=5qYrX56Hz+pCEzPspCsNmO5uEZXRwWohviujneZgWnE=;
 b=Av9b6lXWnvsIVPxbdVotpQYUFSAColuLO+7j46zlwaKSUoekLy8YIOo0z/5li9G2xPxypGuJgwj4UrvzT9IWaaYVE2PClfv8AWO/6IpqY7Qm5o4KeasDpU367avD8oyE3aOkCKEYWtxFu3DEsNvghcKOiFbRLgRbQQCikMZyZYDsU6Wfe63d+8QAEWQhfwExZB/I/+WIAJkjMQq4dQOy9miydwAPGxqzK8k0JQbYexM+p2NH859Bg23FMotFjJuSr/itJyZBFenAQcV4Z3Xru4lnxFRHM30WgOq8OkADESk4xnpruMMkSHGebZV0MfaHSi1cAZ5no1RVMFMkUM/trg==
ARC-Authentication-Results: i=1; mx.microsoft.com 1; spf=pass
 smtp.mailfrom=amd.com; dmarc=pass action=none header.from=amd.com; dkim=pass
 header.d=amd.com; arc=none
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
 d=amdcloud.onmicrosoft.com; s=selector2-amdcloud-onmicrosoft-com;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=5qYrX56Hz+pCEzPspCsNmO5uEZXRwWohviujneZgWnE=;
 b=Ei8H1NtBp1wy9wSRroDNM1k0EGA5L8Eih8tSKLWqE4TN7RYKOevWtDOEqGats8wt0v6nJ126Ma23fTRp5uKeAnJlob5j9WsbY0p+fXH4antnXtsNgK0JcwV3/Jjya1DUP8IjhioBZ8qY9yzuVDTgXXwIyOQZ755zvHYqtf4MwTQ=
Authentication-Results: tencent.com; dkim=none (message not signed)
 header.d=none;tencent.com; dmarc=none action=none header.from=amd.com;
Received: from SN1PR12MB2560.namprd12.prod.outlook.com (2603:10b6:802:26::19)
 by SN1PR12MB2381.namprd12.prod.outlook.com (2603:10b6:802:2f::13) with
 Microsoft SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.3676.33; Tue, 22 Dec
 2020 22:31:27 +0000
Received: from SN1PR12MB2560.namprd12.prod.outlook.com
 ([fe80::8c0e:9a64:673b:4fff]) by SN1PR12MB2560.namprd12.prod.outlook.com
 ([fe80::8c0e:9a64:673b:4fff%5]) with mapi id 15.20.3676.033; Tue, 22 Dec 2020
 22:31:27 +0000
Subject: [PATCH v2 0/2] x86: Add the feature Virtual SPEC_CTRL
From: Babu Moger <babu.moger@amd.com>
To: pbonzini@redhat.com, tglx@linutronix.de, mingo@redhat.com,
        bp@alien8.de
Cc: fenghua.yu@intel.com, tony.luck@intel.com, wanpengli@tencent.com,
        kvm@vger.kernel.org, thomas.lendacky@amd.com, peterz@infradead.org,
        seanjc@google.com, joro@8bytes.org, x86@kernel.org,
        kyung.min.park@intel.com, linux-kernel@vger.kernel.org,
        krish.sadhukhan@oracle.com, hpa@zytor.com, mgross@linux.intel.com,
        vkuznets@redhat.com, kim.phillips@amd.com, wei.huang2@amd.com,
        jmattson@google.com
Date: Tue, 22 Dec 2020 16:31:26 -0600
Message-ID: <160867624053.3471.7106539070175910424.stgit@bmoger-ubuntu>
User-Agent: StGit/0.17.1-dirty
X-Originating-IP: [165.204.77.1]
X-ClientProxiedBy: SN4PR0501CA0154.namprd05.prod.outlook.com
 (2603:10b6:803:2c::32) To SN1PR12MB2560.namprd12.prod.outlook.com
 (2603:10b6:802:26::19)
MIME-Version: 1.0
X-MS-Exchange-MessageSentRepresentingType: 1
Received: from [127.0.1.1] (165.204.77.1) by
 SN4PR0501CA0154.namprd05.prod.outlook.com (2603:10b6:803:2c::32) with
 Microsoft SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.3700.13 via Frontend
 Transport; Tue, 22 Dec 2020 22:31:26 +0000
X-MS-PublicTrafficType: Email
X-MS-Office365-Filtering-HT: Tenant
X-MS-Office365-Filtering-Correlation-Id: b3a1e841-00bc-49cb-f9c5-08d8a6c95291
X-MS-TrafficTypeDiagnostic: SN1PR12MB2381:
X-MS-Exchange-Transport-Forked: True
X-Microsoft-Antispam-PRVS: 
 <SN1PR12MB238180FB02B9050C5AA0F4FE95DF0@SN1PR12MB2381.namprd12.prod.outlook.com>
X-MS-Oob-TLC-OOBClassifiers: OLM:7691;
X-MS-Exchange-SenderADCheck: 1
X-Microsoft-Antispam: BCL:0;
X-Microsoft-Antispam-Message-Info: 
 iw6Qc/kjqqhOdJV0dmMVRGGLhwC4phSLkoX9dKOW5nZ2XvFH/32IKg6vqmuQ2unyylDFSxD2NM4J3gpRlNnDj8arCklACb4H89omdIKBScyZixeLjx2U0vJJ37a8SN2xPgf5lXgGGDGcGWjcIeYJC5alz5HY539qO/20E5OXHM2OScMlRxtqqNKTv6a4WaOsg1FwFe7mh0Q9yWVB/DjDm9OrMcirly+3z1+nnL6YrOi2nfFAdhWNV86hVbCHibgquCv9904l4wpkdo04X3qDRBHrKKsUbQ+KrA5VEVBXBU3irHS93YJs/1ksbl9ninlQQoezPWuhe1nj44q0qbJhJyKOzHva39hjR7C3jqeysGcTEeGqRQqpL9QH5VZYwLdHEq0+o4MYIgEB87dE37EuH8IaeTwbl60ji1RMYDFjxoTZA9xg94FKCMMe+sAWzu6M1yyfuvF+LSWd3ih68kov9A==
X-Forefront-Antispam-Report: 
 CIP:255.255.255.255;CTRY:;LANG:en;SCL:1;SRV:;IPV:NLI;SFV:NSPM;H:SN1PR12MB2560.namprd12.prod.outlook.com;PTR:;CAT:NONE;SFS:(4636009)(7916004)(346002)(376002)(136003)(39840400004)(396003)(366004)(16526019)(66476007)(26005)(186003)(83380400001)(66946007)(4326008)(103116003)(5660300002)(7416002)(9686003)(66556008)(478600001)(966005)(33716001)(956004)(8676002)(6486002)(86362001)(316002)(2906002)(8936002)(52116002)(44832011)(16576012);DIR:OUT;SFP:1101;
X-MS-Exchange-AntiSpam-MessageData: =?utf-8?q?gjO0Ca5EF5P0F8nbzl3OazYAtMF7VK?=
	=?utf-8?q?0otf4Ew/BDjW2B4HNojli45cJ4nuJOvU5UG0BH5tllJ96oJNXjAz9hojIUqwev4jw?=
	=?utf-8?q?01y7cROdI3Lx3dZuST2USMtYX4jRQyIwl4NVDWAL3bx2hdIEHj6z+ik5yql4VlHTx?=
	=?utf-8?q?a03vxAqiTsvJPSV//rgljGjEJwtM1uNEnpy8GkZVTatd3HeH6fVfxgtv5WaMKZUcO?=
	=?utf-8?q?0a2PHZtsuT8oNaOYak1ZY/Hi1Ac0YvIJfX2v72FfGj22DSsxwahSrkOC+lZl3J6om?=
	=?utf-8?q?d0Q2RmISUo9lxaIt63aPmu2agKeA9fHwmhJxaizc56cSESb2TtAgVQYwfaPPD3FSg?=
	=?utf-8?q?2/TiJ7RJnkzUnK5EMHXobzywQ+jO91VLPZnmRa+eaCXtdA3P6LnXUMwILiQeJhHzE?=
	=?utf-8?q?gBkPgSSk2LkofPk3jVo+k9YRzBoKBedHKWVdXJ5JI9Wzp/Wmm4p4RPYyZxP7Q+QYT?=
	=?utf-8?q?b1Sa8fv0UWtOLFbfgnb4h4+7RomdAhpplv8ViOooNnZnsh1xdB5ur3ipXu5+0Cy7g?=
	=?utf-8?q?Fql3Fcyz0AhMAfr0Gi2d0z35Mh5aVfMXxTZN/NgERh0J9y25G7Rm6fSRuxW9GICJ5?=
	=?utf-8?q?Q4iuKBTh/fRKWXHGOVnwNES6LALpy6opm/kErDJxxttrx/m+ARIUjYkicv7wZ6KQd?=
	=?utf-8?q?U5IEqHb7Tjn6VWdwDHErEXEA7MZsvGMUMBi2Ny5Jd+nIC4Y6SdU95EeP7/gN+Wcpf?=
	=?utf-8?q?+XKjaar+j88Ku9VBwQz/GIZmD50ZFh6pFHtRe7farUFZ0wyF0HQf7abRHqrF+j8e7?=
	=?utf-8?q?0OG3GY/3/PqELal9e9IWazao4fJ23B0vkmAyV2dQQ7eAh9Zw8Cnb252/JoP5pyecX?=
	=?utf-8?q?aOW2gWAPIlRK/b4AE2GdZiCZdpQtwqVN2/h+63bZMT/0OZOZca4AFegnxukqpfNaD?=
	=?utf-8?q?V/YhLNQMaOe3+o1LsizoJ13L/moXjt7YVDXYTO6XjHQzH+WEQLQRohOV1vrbzn5iL?=
	=?utf-8?q?JMhEEVGxkEfjvRMUnQ5?=
X-OriginatorOrg: amd.com
X-MS-Exchange-CrossTenant-AuthSource: SN1PR12MB2560.namprd12.prod.outlook.com
X-MS-Exchange-CrossTenant-AuthAs: Internal
X-MS-Exchange-CrossTenant-OriginalArrivalTime: 22 Dec 2020 22:31:27.5131
 (UTC)
X-MS-Exchange-CrossTenant-FromEntityHeader: Hosted
X-MS-Exchange-CrossTenant-Id: 3dd8961f-e488-4e60-8e11-a82d994e183d
X-MS-Exchange-CrossTenant-Network-Message-Id: 
 b3a1e841-00bc-49cb-f9c5-08d8a6c95291
X-MS-Exchange-CrossTenant-MailboxType: HOSTED
X-MS-Exchange-CrossTenant-UserPrincipalName: 
 Rx7iKQ3Sq3cGPQCG6ybybuiLtCWxq0WKPhPl2SbXgsvPtxwzvHiEde/GeCIlQK0L
X-MS-Exchange-Transport-CrossTenantHeadersStamped: SN1PR12MB2381
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Newer AMD processors have a feature to virtualize the use of the
SPEC_CTRL MSR on the guest. The series adds the feature support
and enables the feature on SVM.
---
v2:
  NOTE: This is not final yet. Sending out the patches to make
  sure I captured all the comments correctly.

  1. Most of the changes are related to Jim and Sean's feedback.
  2. Improved the description of patch #2.
  3. Updated the vmcb save area's guest spec_ctrl value(offset 0x2E0)
     properly. Initialized during init_vmcb and svm_set_msr and
     returned the value from save area for svm_get_msr.
  4. As Jim commented, transferred the value into the VMCB prior
     to VMRUN and out of the VMCB after #VMEXIT.
  5. Added kvm-unit-test to detect the SPEC CTRL feature.
     https://lore.kernel.org/kvm/160865324865.19910.5159218511905134908.stgit@bmoger-ubuntu/
  6. Sean mantioned of renaming MSR_AMD64_VIRT_SPEC_CTRL. But, it might
     create even more confusion, so dropped the idea for now.

v1:
https://lore.kernel.org/kvm/160738054169.28590.5171339079028237631.stgit@bmoger-ubuntu/

---

Babu Moger (2):
      x86/cpufeatures: Add the Virtual SPEC_CTRL feature
      KVM: SVM: Add support for Virtual SPEC_CTRL


 arch/x86/include/asm/cpufeatures.h |    1 +
 arch/x86/include/asm/svm.h         |    4 +++-
 arch/x86/kvm/svm/svm.c             |   29 +++++++++++++++++++++++++----
 3 files changed, 29 insertions(+), 5 deletions(-)

--
```
