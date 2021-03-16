

#### [PATCH v5 00/11] Introduce VDUSE - vDPA Device in Userspace
##### From: Xie Yongji <xieyongji@bytedance.com>

```c
From patchwork Mon Mar 15 05:37:10 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Yongji Xie <xieyongji@bytedance.com>
X-Patchwork-Id: 12138315
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.8 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_PATCH,MAILING_LIST_MULTI,
	MENTIONS_GIT_HOSTING,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT
	autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id E1484C433E9
	for <kvm@archiver.kernel.org>; Mon, 15 Mar 2021 05:38:41 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id B8B1D64E45
	for <kvm@archiver.kernel.org>; Mon, 15 Mar 2021 05:38:41 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S230039AbhCOFiK (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Mon, 15 Mar 2021 01:38:10 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:49392 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S229664AbhCOFhv (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 15 Mar 2021 01:37:51 -0400
Received: from mail-pl1-x636.google.com (mail-pl1-x636.google.com
 [IPv6:2607:f8b0:4864:20::636])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 0EE89C061574
        for <kvm@vger.kernel.org>; Sun, 14 Mar 2021 22:37:51 -0700 (PDT)
Received: by mail-pl1-x636.google.com with SMTP id q12so4253954plr.1
        for <kvm@vger.kernel.org>; Sun, 14 Mar 2021 22:37:51 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=bytedance-com.20150623.gappssmtp.com; s=20150623;
        h=from:to:cc:subject:date:message-id:mime-version
         :content-transfer-encoding;
        bh=nvQIToNG/wrtjBjWPrLmNKC6viXrmX1g7W+XEKqjc8Q=;
        b=G0OkTU3dvcANJhsKkY8h7+Gu2HmdKkHL79Fs+hLFkXcC/efJzrdY5hDHYcbWdD9gvF
         fY84/YUC1tLWw59OB4dwYmW4i6cBB8NPBOtwxl8BisBUgeDe6njXVgFeEtrV5qHoyKEs
         KSUcC7MDJQsrurKIMIkJgpJm4YWorVix8QBBAiY2KQXzVIyJhUWITHodOYnPflxP9sGQ
         +4UdNvmabaFtdwNBodzZCkKyvkSGrZl91NkdlustxzIArWzj8URQuIP2T/8I4ur/McWO
         oXgyC7IqEpKtjHuBMuaf4a47htbAyOAyInWIQhr1yDv8dimflQPATqr2eCTFLqwRCL1L
         zRhQ==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:mime-version
         :content-transfer-encoding;
        bh=nvQIToNG/wrtjBjWPrLmNKC6viXrmX1g7W+XEKqjc8Q=;
        b=sKMpTxAJCc9EXC0mVU1joZWXR5XEhoNnjkGDi4GVvHaeVJGatK55BAq4gVVQ4LaZCP
         0BtAhuKPcFM7UtaBqvMNlqoGmBlePxfTYvGySEPClQQuqtTowScig2FU8ulEQ1wwaVLn
         iu6KrryQGKge8viwKhWqcx9eVBMipzUOYG2r/AGtierYZPQPxVrbuyY1w9HuAVd8xM9W
         0o89gTyTH5a1KhcmiXSqPVlyW28LDBzkApADAEcuQZMygbTBajknO75R+dO57jE0mAr8
         5DgAAWoIiNjp1Z0byGAI83SdufsNSl5CsC4dCtaRbTDuoy0KesjxbDoyQVWLiaLZL2ac
         lxhA==
X-Gm-Message-State: AOAM530HebfWKHHj75IPY+wOeMdezcQ43HeGegId10ULfZaOm2DuyYUI
        g9GGagGA33JNfDA/ult/YyFh
X-Google-Smtp-Source: 
 ABdhPJwuTrVy9ZhBwYi0VhgJ0THxjIUX5gHAZ1MQ0vpU86ObghdijG1plLHRs1ok1flhBXQobTEd2Q==
X-Received: by 2002:a17:90a:281:: with SMTP id
 w1mr10510227pja.201.1615786670580;
        Sun, 14 Mar 2021 22:37:50 -0700 (PDT)
Received: from localhost ([139.177.225.227])
        by smtp.gmail.com with ESMTPSA id
 c193sm12549431pfc.180.2021.03.14.22.37.48
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Sun, 14 Mar 2021 22:37:50 -0700 (PDT)
From: Xie Yongji <xieyongji@bytedance.com>
To: mst@redhat.com, jasowang@redhat.com, stefanha@redhat.com,
        sgarzare@redhat.com, parav@nvidia.com, bob.liu@oracle.com,
        hch@infradead.org, rdunlap@infradead.org, willy@infradead.org,
        viro@zeniv.linux.org.uk, axboe@kernel.dk, bcrl@kvack.org,
        corbet@lwn.net, mika.penttila@nextfour.com,
        dan.carpenter@oracle.com
Cc: virtualization@lists.linux-foundation.org, netdev@vger.kernel.org,
        kvm@vger.kernel.org, linux-fsdevel@vger.kernel.org
Subject: [PATCH v5 00/11] Introduce VDUSE - vDPA Device in Userspace
Date: Mon, 15 Mar 2021 13:37:10 +0800
Message-Id: <20210315053721.189-1-xieyongji@bytedance.com>
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

V4 to V5:
- Remove the patch for irq binding
- Use a single IOTLB for all types of mapping
- Factor out vhost_vdpa_pa_map()
- Add some sample codes in document
- Use receice_fd_user() to pass file descriptor
- Fix some bugs

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
  file: Export __receive_fd() to modules
  eventfd: Increase the recursion depth of eventfd_signal()
  vhost-vdpa: protect concurrent access to vhost device iotlb
  vhost-iotlb: Add an opaque pointer for vhost IOTLB
  vdpa: Add an opaque pointer for vdpa_config_ops.dma_map()
  vdpa: factor out vhost_vdpa_pa_map()
  vdpa: Support transferring virtual addressing during DMA mapping
  vduse: Implement an MMU-based IOMMU driver
  vduse: Introduce VDUSE - vDPA Device in Userspace
  vduse: Add config interrupt support
  Documentation: Add documentation for VDUSE

 Documentation/userspace-api/index.rst              |    1 +
 Documentation/userspace-api/ioctl/ioctl-number.rst |    1 +
 Documentation/userspace-api/vduse.rst              |  209 ++++
 drivers/vdpa/Kconfig                               |   10 +
 drivers/vdpa/Makefile                              |    1 +
 drivers/vdpa/ifcvf/ifcvf_main.c                    |    2 +-
 drivers/vdpa/mlx5/net/mlx5_vnet.c                  |    2 +-
 drivers/vdpa/vdpa.c                                |    9 +-
 drivers/vdpa/vdpa_sim/vdpa_sim.c                   |    8 +-
 drivers/vdpa/vdpa_user/Makefile                    |    5 +
 drivers/vdpa/vdpa_user/iova_domain.c               |  535 ++++++++
 drivers/vdpa/vdpa_user/iova_domain.h               |   75 ++
 drivers/vdpa/vdpa_user/vduse_dev.c                 | 1303 ++++++++++++++++++++
 drivers/vdpa/virtio_pci/vp_vdpa.c                  |    2 +-
 drivers/vhost/iotlb.c                              |   20 +-
 drivers/vhost/vdpa.c                               |  152 ++-
 fs/eventfd.c                                       |    2 +-
 fs/file.c                                          |    1 +
 include/linux/eventfd.h                            |    5 +-
 include/linux/vdpa.h                               |   21 +-
 include/linux/vhost_iotlb.h                        |    3 +
 include/uapi/linux/vduse.h                         |  156 +++
 22 files changed, 2469 insertions(+), 54 deletions(-)
 create mode 100644 Documentation/userspace-api/vduse.rst
 create mode 100644 drivers/vdpa/vdpa_user/Makefile
 create mode 100644 drivers/vdpa/vdpa_user/iova_domain.c
 create mode 100644 drivers/vdpa/vdpa_user/iova_domain.h
 create mode 100644 drivers/vdpa/vdpa_user/vduse_dev.c
 create mode 100644 include/uapi/linux/vduse.h
```
#### [PATCH v4 0/3] CET fix patches for nested guest
##### From: Yang Weijiang <weijiang.yang@intel.com>

```c
From patchwork Mon Mar 15 07:18:38 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Yang Weijiang <weijiang.yang@intel.com>
X-Patchwork-Id: 12138507
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-11.8 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,
	SPF_PASS,USER_AGENT_GIT autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id EF3F2C433DB
	for <kvm@archiver.kernel.org>; Mon, 15 Mar 2021 07:07:26 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id BADE564E64
	for <kvm@archiver.kernel.org>; Mon, 15 Mar 2021 07:07:26 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S230009AbhCOHGp (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Mon, 15 Mar 2021 03:06:45 -0400
Received: from mga18.intel.com ([134.134.136.126]:59702 "EHLO mga18.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S229663AbhCOHGY (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 15 Mar 2021 03:06:24 -0400
IronPort-SDR: 
 brwbhs3xYhwkJto0d0epINfTKjnl8n+9S6isjfOgp1EiE46N8uqqCvmDJxBGYPVuTZiA8aAERU
 UJaGeqHGRR9w==
X-IronPort-AV: E=McAfee;i="6000,8403,9923"; a="176640924"
X-IronPort-AV: E=Sophos;i="5.81,249,1610438400";
   d="scan'208";a="176640924"
Received: from fmsmga005.fm.intel.com ([10.253.24.32])
  by orsmga106.jf.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 15 Mar 2021 00:06:23 -0700
IronPort-SDR: 
 HrLe6NuUVA8LsglYMlLOCgJ8rWa3BO3lB1Mwj7SC4gUtP8p1qr+yCvp3fnIYDhc4qZVL9JOC6B
 DKrbYMkyNIlg==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.81,249,1610438400";
   d="scan'208";a="604749519"
Received: from local-michael-cet-test.sh.intel.com ([10.239.159.166])
  by fmsmga005.fm.intel.com with ESMTP; 15 Mar 2021 00:06:20 -0700
From: Yang Weijiang <weijiang.yang@intel.com>
To: pbonzini@redhat.com, seanjc@google.com, vkuznets@redhat.com,
        kvm@vger.kernel.org, linux-kernel@vger.kernel.org
Cc: Yang Weijiang <weijiang.yang@intel.com>
Subject: [PATCH v4 0/3] CET fix patches for nested guest
Date: Mon, 15 Mar 2021 15:18:38 +0800
Message-Id: <20210315071841.7045-1-weijiang.yang@intel.com>
X-Mailer: git-send-email 2.17.2
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This patch series is to fix a few issues found during patch review and
testing on Linux, also including a patch to explictly disable CET support
in nested guest over Hyper-V(s).

change in v4:
- Added guest CET cpuid check before sync vmcs02 CET state to vmcs12.
- Opportunistically added similar fix for MPX.

Yang Weijiang (3):
  KVM: nVMX: Sync L2 guest CET states between L1/L2
  KVM: nVMX: Set X86_CR4_CET in cr4_fixed1_bits if CET IBT is enabled
  KVM: nVMX: Add CET entry/exit load bits to evmcs unsupported list

 arch/x86/kvm/cpuid.c      |  1 -
 arch/x86/kvm/vmx/evmcs.c  |  4 ++--
 arch/x86/kvm/vmx/evmcs.h  |  6 ++++--
 arch/x86/kvm/vmx/nested.c | 35 +++++++++++++++++++++++++++++++++--
 arch/x86/kvm/vmx/vmx.c    |  1 +
 arch/x86/kvm/vmx/vmx.h    |  3 +++
 6 files changed, 43 insertions(+), 7 deletions(-)
```
#### [PATCH V4 0/7] vDPA/ifcvf: enables Intel C5000X-PL virtio-net
##### From: Zhu Lingshan <lingshan.zhu@intel.com>

```c
From patchwork Mon Mar 15 07:44:54 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Zhu Lingshan <lingshan.zhu@intel.com>
X-Patchwork-Id: 12138543
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-11.8 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,
	SPF_PASS,USER_AGENT_GIT autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 0C5D9C433DB
	for <kvm@archiver.kernel.org>; Mon, 15 Mar 2021 07:51:09 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id D828164E67
	for <kvm@archiver.kernel.org>; Mon, 15 Mar 2021 07:51:08 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S230255AbhCOHuf (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Mon, 15 Mar 2021 03:50:35 -0400
Received: from mga09.intel.com ([134.134.136.24]:17801 "EHLO mga09.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S230266AbhCOHuR (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 15 Mar 2021 03:50:17 -0400
IronPort-SDR: 
 HM6hV8WIXIMI7pmxju6O4ESPn9c6gIBQyB47L3/SMymQjDaECFHQn+byUqnug2Na2uGtlrt2Hw
 qZIzYOvoP7KQ==
X-IronPort-AV: E=McAfee;i="6000,8403,9923"; a="189140884"
X-IronPort-AV: E=Sophos;i="5.81,249,1610438400";
   d="scan'208";a="189140884"
Received: from orsmga008.jf.intel.com ([10.7.209.65])
  by orsmga102.jf.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 15 Mar 2021 00:50:12 -0700
IronPort-SDR: 
 8Od4S3PDuI3+GsFlkIZOaYGUhx+hDVeI5LuaDeiy0gRJ45NjSqZH2PKcmiIYdacEckCxHaaXVT
 hBXzTiFCgLsQ==
X-IronPort-AV: E=Sophos;i="5.81,249,1610438400";
   d="scan'208";a="411752161"
Received: from unknown (HELO localhost.localdomain.bj.intel.com)
 ([10.240.193.73])
  by orsmga008-auth.jf.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 15 Mar 2021 00:50:09 -0700
From: Zhu Lingshan <lingshan.zhu@intel.com>
To: jasowang@redhat.com, mst@redhat.com, lulu@redhat.com,
        leonro@nvidia.com
Cc: virtualization@lists.linux-foundation.org, netdev@vger.kernel.org,
        kvm@vger.kernel.org, linux-kernel@vger.kernel.org,
        Zhu Lingshan <lingshan.zhu@intel.com>
Subject: [PATCH V4 0/7] vDPA/ifcvf: enables Intel C5000X-PL virtio-net
Date: Mon, 15 Mar 2021 15:44:54 +0800
Message-Id: <20210315074501.15868-1-lingshan.zhu@intel.com>
X-Mailer: git-send-email 2.27.0
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This series enabled Intel FGPA SmartNIC C5000X-PL virtio-net for vDPA.

vDPA requires VIRTIO_F_ACCESS_PLATFORM as a must,
this series verify this feature bit when set features.

Changes from V3:
checks features to set in verify_min_features(Jason)
deduce VIRTIO device ID from pdev ids in get_device_id(Jason)

Changes from V2:
verify VIRTIO_F_ACCESS_PLATFORM when set features(Jason)

Changes from V1:
remove version number string(Leon)
add new device ids and remove original device ids
in separate patches(Jason)


Zhu Lingshan (7):
  vDPA/ifcvf: get_vendor_id returns a device specific vendor id
  vDPA/ifcvf: enable Intel C5000X-PL virtio-net for vDPA
  vDPA/ifcvf: rename original IFCVF dev ids to N3000 ids
  vDPA/ifcvf: remove the version number string
  vDPA/ifcvf: fetch device feature bits when probe
  vDPA/ifcvf: verify mandatory feature bits for vDPA
  vDPA/ifcvf: deduce VIRTIO device ID from pdev ids

 drivers/vdpa/ifcvf/ifcvf_base.c | 66 ++++++++++++++++++++++++++++++++-
 drivers/vdpa/ifcvf/ifcvf_base.h | 17 +++++++--
 drivers/vdpa/ifcvf/ifcvf_main.c | 35 +++++++++++++----
 3 files changed, 104 insertions(+), 14 deletions(-)
```
#### [PATCH 0/4] KVM: x86: hyper-v: TSC page fixes
##### From: Vitaly Kuznetsov <vkuznets@redhat.com>

```c
From patchwork Mon Mar 15 14:37:02 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Vitaly Kuznetsov <vkuznets@redhat.com>
X-Patchwork-Id: 12139667
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-11.0 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS autolearn=ham
	autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 60EB2C2BA13
	for <kvm@archiver.kernel.org>; Mon, 15 Mar 2021 14:39:09 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 3C86164E74
	for <kvm@archiver.kernel.org>; Mon, 15 Mar 2021 14:39:09 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S232341AbhCOOif (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Mon, 15 Mar 2021 10:38:35 -0400
Received: from us-smtp-delivery-124.mimecast.com ([216.205.24.124]:56464 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S238626AbhCOOhO (ORCPT
        <rfc822;kvm@vger.kernel.org>); Mon, 15 Mar 2021 10:37:14 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1615819032;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=0LYR6JBqjo2XVOwjxQTLuJ6o2JNXhKkR1znK2FpvTjM=;
        b=IPg23awUmxSTotU4TK6VumeE2IvTt8Y5XtuGO1WwTLXOUhsUARdiICdjSe4fw4uCOQdwnx
        yy/B5RK4ijoqJtEH3m89DWmeQUVIgisTGu6LoqMaeN/N9XSYUaOFYwUCYMKg7VythVIxFl
        ayy5G4pm6odEaCuMiJCJ0GpVmImSGgs=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-195-TdQEF0uUPR2PJhuQmxBClg-1; Mon, 15 Mar 2021 10:37:11 -0400
X-MC-Unique: TdQEF0uUPR2PJhuQmxBClg-1
Received: from smtp.corp.redhat.com (int-mx06.intmail.prod.int.phx2.redhat.com
 [10.5.11.16])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id D63D9107ACCA;
        Mon, 15 Mar 2021 14:37:09 +0000 (UTC)
Received: from vitty.brq.redhat.com (unknown [10.40.195.229])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 04A9C5C3E6;
        Mon, 15 Mar 2021 14:37:07 +0000 (UTC)
From: Vitaly Kuznetsov <vkuznets@redhat.com>
To: kvm@vger.kernel.org, Paolo Bonzini <pbonzini@redhat.com>
Cc: Sean Christopherson <seanjc@google.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Marcelo Tosatti <mtosatti@redhat.com>
Subject: [PATCH 0/4] KVM: x86: hyper-v: TSC page fixes
Date: Mon, 15 Mar 2021 15:37:02 +0100
Message-Id: <20210315143706.859293-1-vkuznets@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.16
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

I'm investigating an issue when Linux guest on nested Hyper-V on KVM 
(WSL2 on Win10 on KVM to be precise) hangs after L1 KVM is migrated. Trace
shows us that L2 is trying to set L1's Synthetic Timer and reacting to
this Hyper-V sets Synthetic Timer in KVM but the target value it sets is
always slightly in the past, this causes the timer to expire immediately
and an interrupt storm is thus observed. L2 is not making much forward
progress.

The issue is only observed when re-enlightenment is exposed to L1. KVM
doesn't really support re-enlightenment notifications upon migration,
userspace is supposed to expose it only when TSC scaling is supported
on the destination host. Without re-enlightenment exposed, Hyper-V will
not expose stable TSC page clocksource to its L2s. The issue is observed
on when migration happens between hosts supporting TSC scaling. Rumor has
it that it is possible to reproduce the problem even when migrating locally
to the same host, though, I wasn't really able to.

The current speculation is that when Hyper-V is migrated, it uses stale
(cached) TSC page values to compute the difference between its own
clocksource (provided by KVM) and its guests' TSC pages to program
synthetic timers and in some cases, when TSC page is updated, this puts all
stimer expirations in the past. This, in its turn, causes an interrupt
storms (both L0-L1 and L1->L2 as Hyper-V mirrors stimer expirations into
L2).

The proposed fix is to skip updating TSC page clocksource when guest opted
for re-enlightenment notifications (PATCH4). Patches 1-3 are slightly
related fixes to the (mostly theoretical) issues I've stumbled upon while
working on the problem.

Vitaly Kuznetsov (4):
  KVM: x86: hyper-v: Limit guest to writing zero to
    HV_X64_MSR_TSC_EMULATION_STATUS
  KVM: x86: hyper-v: Prevent using not-yet-updated TSC page by secondary
    CPUs
  KVM: x86: hyper-v: Track Hyper-V TSC page status
  KVM: x86: hyper-v: Don't touch TSC page values when guest opted for
    re-enlightenment

 arch/x86/include/asm/kvm_host.h |  9 +++++++
 arch/x86/kvm/hyperv.c           | 42 +++++++++++++++++++++++++++++----
 arch/x86/kvm/x86.c              |  5 ++--
 3 files changed, 49 insertions(+), 7 deletions(-)
```
#### [PATCH kvmtool v3 00/22] Unify I/O port and MMIO trap handling
##### From: Andre Przywara <andre.przywara@arm.com>

```c
From patchwork Mon Mar 15 15:33:28 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Andre Przywara <andre.przywara@arm.com>
X-Patchwork-Id: 12139837
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.8 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT
	autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 50921C4360C
	for <kvm@archiver.kernel.org>; Mon, 15 Mar 2021 15:34:59 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 2AAD764E22
	for <kvm@archiver.kernel.org>; Mon, 15 Mar 2021 15:34:59 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S230134AbhCOPeX (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Mon, 15 Mar 2021 11:34:23 -0400
Received: from foss.arm.com ([217.140.110.172]:50604 "EHLO foss.arm.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S230221AbhCOPeL (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 15 Mar 2021 11:34:11 -0400
Received: from usa-sjc-imap-foss1.foss.arm.com (unknown [10.121.207.14])
        by usa-sjc-mx-foss1.foss.arm.com (Postfix) with ESMTP id 382AF1FB;
        Mon, 15 Mar 2021 08:34:11 -0700 (PDT)
Received: from localhost.localdomain (unknown [172.31.20.19])
        by usa-sjc-imap-foss1.foss.arm.com (Postfix) with ESMTPSA id
 E03333F792;
        Mon, 15 Mar 2021 08:34:09 -0700 (PDT)
From: Andre Przywara <andre.przywara@arm.com>
To: Will Deacon <will@kernel.org>,
        Julien Thierry <julien.thierry.kdev@gmail.com>
Cc: Alexandru Elisei <alexandru.elisei@arm.com>, kvm@vger.kernel.org,
        kvmarm@lists.cs.columbia.edu, Marc Zyngier <maz@kernel.org>,
        Sami Mujawar <sami.mujawar@arm.com>
Subject: [PATCH kvmtool v3 00/22] Unify I/O port and MMIO trap handling
Date: Mon, 15 Mar 2021 15:33:28 +0000
Message-Id: <20210315153350.19988-1-andre.przywara@arm.com>
X-Mailer: git-send-email 2.14.1
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Hi,

this version is addressing Alexandru's comments, fixing mostly minor
issues in the naming scheme. The biggest change is to keep the
ioport__read/ioport_write wrappers for the serial device.
For more details see the changelog below.
==============

At the moment we use two separate code paths to handle exits for
KVM_EXIT_IO (ioport.c) and KVM_EXIT_MMIO (mmio.c), even though they
are semantically very similar. Because the trap handler callback routine
is different, devices need to decide on one conduit or need to provide
different handler functions for both of them.

This is not only unnecessary code duplication, but makes switching
devices from I/O port to MMIO a tedious task, even though there is no
real difference between the two, especially on ARM and PowerPC.

For ARM we aim at providing a flexible memory layout, and also have
trouble with the UART and RTC device overlapping with the PCI I/O area,
so it seems indicated to tackle this once and for all.

The first three patches do some cleanup, to simplify things later.

Patch 04/22 lays the groundwork, by extending mmio.c to be able to also
register I/O port trap handlers, using the same callback prototype as
we use for MMIO.

The next 14 patches then convert devices that use the I/O port
interface over to the new joint interface. This requires to rework
the trap handler routine to adhere to the same prototype as the existing
MMIO handlers. For most devices this is done in two steps: a first to
introduce the reworked handler routine, and a second to switch to the new
joint registration routine. For some devices the first step is trivial,
so it's done in one patch.

Patch 19/22 then retires the old I/O port interface, by removing ioport.c
and friends.
Patch 20/22 uses the opportunity to clean up the memory map description,
also declares a new region (from 16MB on), where the final two patches
switch the UART and the RTC device to. They are now registered
on the MMIO "bus", when running on ARM or arm64. This moves them away
from the first 64KB, so they are not in the PCI I/O area anymore.

Please have a look and comment!

Cheers,
Andre

Changelog v2 .. v3:
- use _io as function prefix for x86 I/O port devices
- retain ioport__{read,write}8() wrappers for serial device
- fix memory map ASCII art
- fix serial base declaration
- minor nit fixes
- add Reviewed-by: tags

Changelog v1 .. v2:
- rework memory map definition
- add explicit debug output for debug I/O port
- add explicit check for MMIO coalescing on I/O ports
- drop usage of ioport__{read,write}8() from serial
- drop explicit I/O port cleanup routine (to mimic MMIO operation)
- add comment for IOTRAP_BUS_MASK
- minor cleanups / formatting changes


Andre Przywara (22):
  ioport: Remove ioport__setup_arch()
  hw/serial: Use device abstraction for FDT generator function
  ioport: Retire .generate_fdt_node functionality
  mmio: Extend handling to include ioport emulation
  hw/i8042: Clean up data types
  hw/i8042: Refactor trap handler
  hw/i8042: Switch to new trap handlers
  x86/ioport: Refactor trap handlers
  x86/ioport: Switch to new trap handlers
  hw/rtc: Refactor trap handlers
  hw/rtc: Switch to new trap handler
  hw/vesa: Switch trap handling to use MMIO handler
  hw/serial: Refactor trap handler
  hw/serial: Switch to new trap handlers
  vfio: Refactor ioport trap handler
  vfio: Switch to new ioport trap handlers
  virtio: Switch trap handling to use MMIO handler
  pci: Switch trap handling to use MMIO handler
  Remove ioport specific routines
  arm: Reorganise and document memory map
  hw/serial: ARM/arm64: Use MMIO at higher addresses
  hw/rtc: ARM/arm64: Use MMIO at higher addresses

 Makefile                          |   1 -
 arm/include/arm-common/kvm-arch.h |  47 ++++--
 arm/ioport.c                      |   5 -
 hw/i8042.c                        |  94 +++++-------
 hw/rtc.c                          |  91 ++++++------
 hw/serial.c                       | 126 +++++++++++-----
 hw/vesa.c                         |  19 +--
 include/kvm/i8042.h               |   1 -
 include/kvm/ioport.h              |  32 ----
 include/kvm/kvm.h                 |  49 ++++++-
 ioport.c                          | 235 ------------------------------
 mips/kvm.c                        |   5 -
 mmio.c                            |  65 +++++++--
 pci.c                             |  82 +++--------
 powerpc/ioport.c                  |   6 -
 vfio/core.c                       |  50 ++++---
 virtio/pci.c                      |  46 ++----
 x86/ioport.c                      | 108 +++++++-------
 18 files changed, 421 insertions(+), 641 deletions(-)
 delete mode 100644 ioport.c
```
#### [PATCH v4 00/14] vdpa: add vdpa simulator for block device
##### From: Stefano Garzarella <sgarzare@redhat.com>

```c
From patchwork Mon Mar 15 16:34:36 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Stefano Garzarella <sgarzare@redhat.com>
X-Patchwork-Id: 12140009
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-11.0 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS
	autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id C5DA5C43332
	for <kvm@archiver.kernel.org>; Mon, 15 Mar 2021 16:35:48 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 97B4264F37
	for <kvm@archiver.kernel.org>; Mon, 15 Mar 2021 16:35:48 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S232254AbhCOQfO (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Mon, 15 Mar 2021 12:35:14 -0400
Received: from us-smtp-delivery-124.mimecast.com ([216.205.24.124]:48261 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S232273AbhCOQfE (ORCPT
        <rfc822;kvm@vger.kernel.org>); Mon, 15 Mar 2021 12:35:04 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1615826104;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:content-type:content-type:
         content-transfer-encoding:content-transfer-encoding;
        bh=8E7bQAO4mPMCMNy7czH8SXiPxDN2NhK2/K7/V4lwNsU=;
        b=bK+mEQQOxA7/pIHyPC8GJ/Omz888Jt3qCh6TKZTK9ZOOlwwlXBhg8jW7SPhGsDWTDToVVh
        /DBAD6wify8rAh4Kc2WWMHc9QrxD2EGwwHuqWgSZkZm1JkhBU0boGUoUweqMkia+KFHT9j
        SeA0gy4Eg0N5sPQ+MQN8Tk3TDHpI77g=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-219-3bB14KOROdS3_D81865z-Q-1; Mon, 15 Mar 2021 12:35:01 -0400
X-MC-Unique: 3bB14KOROdS3_D81865z-Q-1
Received: from smtp.corp.redhat.com (int-mx08.intmail.prod.int.phx2.redhat.com
 [10.5.11.23])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id E03A6100C663;
        Mon, 15 Mar 2021 16:34:59 +0000 (UTC)
Received: from steredhat.redhat.com (ovpn-114-1.ams2.redhat.com [10.36.114.1])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 47AD319D7C;
        Mon, 15 Mar 2021 16:34:51 +0000 (UTC)
From: Stefano Garzarella <sgarzare@redhat.com>
To: virtualization@lists.linux-foundation.org
Cc: netdev@vger.kernel.org, Xie Yongji <xieyongji@bytedance.com>,
        Laurent Vivier <lvivier@redhat.com>,
        Stefan Hajnoczi <stefanha@redhat.com>,
        linux-kernel@vger.kernel.org, Max Gurtovoy <mgurtovoy@nvidia.com>,
        Jason Wang <jasowang@redhat.com>,
        Parav Pandit <parav@nvidia.com>,
        "Michael S. Tsirkin" <mst@redhat.com>, kvm@vger.kernel.org
Subject: [PATCH v4 00/14] vdpa: add vdpa simulator for block device
Date: Mon, 15 Mar 2021 17:34:36 +0100
Message-Id: <20210315163450.254396-1-sgarzare@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.84 on 10.5.11.23
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

v4:
- added support for iproute2 vdpa management tool in vdpa_sim_blk
- removed get/set_config patches
  - 'vdpa: add return value to get_config/set_config callbacks'
  - 'vhost/vdpa: remove vhost_vdpa_config_validate()'
- added get_config_size() patches
  - 'vdpa: add get_config_size callback in vdpa_config_ops'
  - 'vhost/vdpa: use get_config_size callback in vhost_vdpa_config_validate()'

v3: https://lore.kernel.org/lkml/20210204172230.85853-1-sgarzare@redhat.com/
v2: https://lore.kernel.org/lkml/20210128144127.113245-1-sgarzare@redhat.com/
v1: https://lore.kernel.org/lkml/93f207c0-61e6-3696-f218-e7d7ea9a7c93@redhat.com/

This series is the second part of the v1 linked above. The first part with
refactoring of vdpa_sim has already been merged.

The patches are based on Max Gurtovoy's work and extend the block simulator to
have a ramdisk behaviour.

As mentioned in the v1 there was 2 issues and I fixed them in this series:
1. The identical mapping in the IOMMU used until now in vdpa_sim created issues
   when mapping different virtual pages with the same physical address.
   Fixed by patch "vdpa_sim: use iova module to allocate IOVA addresses"

2. There was a race accessing the IOMMU between the vdpasim_blk_work() and the
   device driver that map/unmap DMA regions. Fixed by patch "vringh: add
   'iotlb_lock' to synchronize iotlb accesses"

I used the Xie's patch coming from VDUSE series to allow vhost-vdpa to use
block devices, and I added get_config_size() callback to allow any device
in vhost-vdpa.

The series also includes small fixes for vringh, vdpa, and vdpa_sim that I
discovered while implementing and testing the block simulator.

Thanks for your feedback,
Stefano

Max Gurtovoy (1):
  vdpa: add vdpa simulator for block device

Stefano Garzarella (12):
  vdpa_sim: use iova module to allocate IOVA addresses
  vringh: add 'iotlb_lock' to synchronize iotlb accesses
  vringh: reset kiov 'consumed' field in __vringh_iov()
  vringh: explain more about cleaning riov and wiov
  vringh: implement vringh_kiov_advance()
  vringh: add vringh_kiov_length() helper
  vdpa_sim: cleanup kiovs in vdpasim_free()
  vdpa: add get_config_size callback in vdpa_config_ops
  vhost/vdpa: use get_config_size callback in
    vhost_vdpa_config_validate()
  vdpa_sim_blk: implement ramdisk behaviour
  vdpa_sim_blk: handle VIRTIO_BLK_T_GET_ID
  vdpa_sim_blk: add support for vdpa management tool

Xie Yongji (1):
  vhost/vdpa: Remove the restriction that only supports virtio-net
    devices

 drivers/vdpa/vdpa_sim/vdpa_sim.h     |   2 +
 include/linux/vdpa.h                 |   4 +
 include/linux/vringh.h               |  19 +-
 drivers/vdpa/ifcvf/ifcvf_main.c      |   6 +
 drivers/vdpa/mlx5/net/mlx5_vnet.c    |   6 +
 drivers/vdpa/vdpa_sim/vdpa_sim.c     | 127 ++++++----
 drivers/vdpa/vdpa_sim/vdpa_sim_blk.c | 338 +++++++++++++++++++++++++++
 drivers/vdpa/virtio_pci/vp_vdpa.c    |   8 +
 drivers/vhost/vdpa.c                 |  15 +-
 drivers/vhost/vringh.c               |  69 ++++--
 drivers/vdpa/Kconfig                 |   8 +
 drivers/vdpa/vdpa_sim/Makefile       |   1 +
 12 files changed, 529 insertions(+), 74 deletions(-)
 create mode 100644 drivers/vdpa/vdpa_sim/vdpa_sim_blk.c
```
#### [PATCH 0/2] KVM: x86: nSVM: fixes for SYSENTER emulation
##### From: Maxim Levitsky <mlevitsk@redhat.com>

```c
From patchwork Mon Mar 15 17:43:14 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Maxim Levitsky <mlevitsk@redhat.com>
X-Patchwork-Id: 12140295
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-11.0 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS autolearn=ham
	autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 951B2C433DB
	for <kvm@archiver.kernel.org>; Mon, 15 Mar 2021 17:56:35 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 5100A64F09
	for <kvm@archiver.kernel.org>; Mon, 15 Mar 2021 17:56:35 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S229862AbhCOR4D (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Mon, 15 Mar 2021 13:56:03 -0400
Received: from us-smtp-delivery-124.mimecast.com ([216.205.24.124]:50446 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S233192AbhCORsk (ORCPT
        <rfc822;kvm@vger.kernel.org>); Mon, 15 Mar 2021 13:48:40 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1615830340;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=wVIrHu5i7uEomxJk7uMi6tnqyeAug3yjA4h+WiRfCDs=;
        b=bCjjvmgOllhyKk0EVDaP4Encu23Io8humN1jQl/7Xx/WNJTToHesQXzJKArs0k9BW+a7tx
        b7AXj9MzuQGQ7j2sxqzdSIwM5AGKUV8zCU7b7hKPGoz5uQQe7x51oNSGgwQQaaGpruHrcA
        MGCyEsCDBz4gE4QePhnBh+FLE8XtXoM=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-56-p15X9b5UOpygdTl2bJiq-w-1; Mon, 15 Mar 2021 13:43:23 -0400
X-MC-Unique: p15X9b5UOpygdTl2bJiq-w-1
Received: from smtp.corp.redhat.com (int-mx05.intmail.prod.int.phx2.redhat.com
 [10.5.11.15])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id CFDDB80006E;
        Mon, 15 Mar 2021 17:43:21 +0000 (UTC)
Received: from localhost.localdomain (unknown [10.35.207.30])
        by smtp.corp.redhat.com (Postfix) with ESMTP id CCC7F5D745;
        Mon, 15 Mar 2021 17:43:17 +0000 (UTC)
From: Maxim Levitsky <mlevitsk@redhat.com>
To: kvm@vger.kernel.org
Cc: x86@kernel.org (maintainer:X86 ARCHITECTURE (32-BIT AND 64-BIT)),
        "H. Peter Anvin" <hpa@zytor.com>,
        Sean Christopherson <seanjc@google.com>,
        Ingo Molnar <mingo@redhat.com>,
        Jim Mattson <jmattson@google.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Joerg Roedel <joro@8bytes.org>,
        Paolo Bonzini <pbonzini@redhat.com>,
        Thomas Gleixner <tglx@linutronix.de>,
        linux-kernel@vger.kernel.org (open list:X86 ARCHITECTURE (32-BIT AND
        64-BIT)), Wanpeng Li <wanpengli@tencent.com>,
        Borislav Petkov <bp@alien8.de>,
        Maxim Levitsky <mlevitsk@redhat.com>
Subject: [PATCH 0/2] KVM: x86: nSVM: fixes for SYSENTER emulation
Date: Mon, 15 Mar 2021 19:43:14 +0200
Message-Id: <20210315174316.477511-1-mlevitsk@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.15
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This is a result of deep rabbit hole dive in regard to why currently the
nested migration of 32 bit guests is totally broken on AMD.

It turns out that due to slight differences between the original AMD64
implementation and the Intel's remake, SYSENTER instruction behaves a
bit differently on Intel, and to support migration from Intel to AMD we
try to emulate those differences away.

Sadly that collides with virtual vmload/vmsave feature that is used in nesting
such as on migration (and otherwise when userspace
reads MSR_IA32_SYSENTER_EIP/MSR_IA32_SYSENTER_ESP), wrong value is returned,
which leads to #DF in the nested guest when the wrong value is loaded back.

The patch I prepared carefully fixes this, by mostly disabling that SYSCALL
emulation when we don't spoof Intel's vendor ID, and if we do, and yet somehow
SVM is enabled (this is very rare corner case), then virtual vmload/save is
force disabled.

Best regards,
	Maxim Levitsky

Maxim Levitsky (2):
  KVM: x86: add guest_cpuid_is_intel
  KVM: nSVM: improve SYSENTER emulation on AMD

 arch/x86/kvm/cpuid.h   |  8 ++++
 arch/x86/kvm/svm/svm.c | 97 ++++++++++++++++++++++++++++--------------
 arch/x86/kvm/svm/svm.h |  7 +--
 3 files changed, 77 insertions(+), 35 deletions(-)
```
#### [PATCH v2 0/4] Fix RCU warnings in TDP MMU
##### From: Ben Gardon <bgardon@google.com>

```c
From patchwork Mon Mar 15 18:26:39 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Ben Gardon <bgardon@google.com>
X-Patchwork-Id: 12140399
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-21.3 required=3.0 tests=BAYES_00,DKIMWL_WL_MED,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT,
	USER_IN_DEF_DKIM_WL autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id CB6B5C433E0
	for <kvm@archiver.kernel.org>; Mon, 15 Mar 2021 18:27:36 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 941E564F42
	for <kvm@archiver.kernel.org>; Mon, 15 Mar 2021 18:27:36 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S232414AbhCOS1F (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Mon, 15 Mar 2021 14:27:05 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:46736 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S232004AbhCOS0t (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 15 Mar 2021 14:26:49 -0400
Received: from mail-qv1-xf4a.google.com (mail-qv1-xf4a.google.com
 [IPv6:2607:f8b0:4864:20::f4a])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 3DAD4C06174A
        for <kvm@vger.kernel.org>; Mon, 15 Mar 2021 11:26:49 -0700 (PDT)
Received: by mail-qv1-xf4a.google.com with SMTP id t18so23568894qva.6
        for <kvm@vger.kernel.org>; Mon, 15 Mar 2021 11:26:49 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=date:message-id:mime-version:subject:from:to:cc;
        bh=Mx5f7S+/5wRWBEBjRnHorBN6dS5pzBj5+cDT45N3twk=;
        b=PlpPMKkm7qu6wCcvrEVc6KzFMMrjwWRJ198xVmPtC9vIbZPfK6/sbqEIkegXWp8Btu
         MuIQ892Ph6/RTX7ffhra72wj5jtXEQuuBFixDZKDxr+zuyxADYTvREp3L5e5OodF94AT
         lJOhmjpkoeqmxNVRhGJ1hDxkMLk6kujS/9hJsmDQGmqUAMICEn1cY3LZCFyQrcnEhFjC
         okjVPg9vp712MltmkyLQGkoMeCtT4u99CMNjOupbhTJNiAs05rhfyB099QZpl71tRl3R
         6frsQawZnyoA3mdDyxlLQWcSkSJ3nEgD5sCr26s7oxJTLMq717hCj0SqxMVzHHJjuoL7
         l7Ig==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:date:message-id:mime-version:subject:from:to:cc;
        bh=Mx5f7S+/5wRWBEBjRnHorBN6dS5pzBj5+cDT45N3twk=;
        b=oFOWqlCPISoRW2fGwqih7Uk2FKN0+h1cblIbMk/0GszbtMLhrBceT2lWUc0JwZQ7si
         lK0hJlbtS0IPN8FD/WbMfUq6vIx/BvWC7AX8Evqv4uE1/ZGHcW6PENOrnPS5HtcztOAf
         N5mqaAGEOBur28KddZcAJKuHnhmkwCaZZE6JGGGIxEvj7pE3hJvd6UFiVXMNJfasstWI
         szJZWgD9kLGT76Sgd6RSPR0yqDhJTkWTFRcjR87SKHnbe8iv1ajx+5USkhhMGWN1fhA8
         6RVvTcqXOWWLRZdrwRt7xXJNRycYcjXRCDZZ9yWlvz7fVhTtUdgjX5r2+uHiw3bLgnyz
         vlOQ==
X-Gm-Message-State: AOAM532qTG4NN8eh/zkM5eKjHcif0gb3l7LSWZARisiLfposjho29XFX
        5mCmMjr1I6t9i1r+vs8SBld3CBOpZ7e7
X-Google-Smtp-Source: 
 ABdhPJyPnuqH28GMfLvsE6fntxec4xEAKml+R1kWf48drQz3przzmYm9EipdFRGFMISS6+0jw9PngSrS0NY1
X-Received: from bgardon.sea.corp.google.com
 ([2620:15c:100:202:888a:4e22:67:844a])
 (user=bgardon job=sendgmr) by 2002:ad4:5ec9:: with SMTP id
 jm9mr12014461qvb.56.1615832808291; Mon, 15 Mar 2021 11:26:48 -0700 (PDT)
Date: Mon, 15 Mar 2021 11:26:39 -0700
Message-Id: <20210315182643.2437374-1-bgardon@google.com>
Mime-Version: 1.0
X-Mailer: git-send-email 2.31.0.rc2.261.g7f71774620-goog
Subject: [PATCH v2 0/4] Fix RCU warnings in TDP MMU
From: Ben Gardon <bgardon@google.com>
To: linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Cc: Paolo Bonzini <pbonzini@redhat.com>,
        Sean Christopherson <seanjc@google.com>,
        Peter Shier <pshier@google.com>,
        Jim Mattson <jmattson@google.com>,
        Ben Gardon <bgardon@google.com>
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The Linux Test Robot found a few RCU warnings in the TDP MMU:
https://www.spinics.net/lists/kernel/msg3845500.html
https://www.spinics.net/lists/kernel/msg3845521.html

Fix these warnings and cleanup a hack in tdp_mmu_iter_cond_resched.

Tested by compiling as suggested in the test robot report and confirmed
that the warnings go away with this series applied. Also ran
kvm-unit-tests on an Intel Skylake machine with the TDP MMU enabled and
confirmed that the series introduced no new failures.

Ben Gardon (4):
  KVM: x86/mmu: Fix RCU usage in handle_removed_tdp_mmu_page
  KVM: x86/mmu: Fix RCU usage when atomically zapping SPTEs
  KVM: x86/mmu: Factor out tdp_iter_return_to_root
  KVM: x86/mmu: Store the address space ID in the TDP iterator

 arch/x86/kvm/mmu/mmu_internal.h |  5 +++++
 arch/x86/kvm/mmu/tdp_iter.c     | 30 +++++++++++++++----------
 arch/x86/kvm/mmu/tdp_iter.h     |  4 +++-
 arch/x86/kvm/mmu/tdp_mmu.c      | 40 +++++++++++++--------------------
 4 files changed, 41 insertions(+), 38 deletions(-)
```
#### [PATCH v2 0/2] Simple test for sysenter instruction
##### From: Maxim Levitsky <mlevitsk@redhat.com>

```c
From patchwork Mon Mar 15 21:09:19 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Maxim Levitsky <mlevitsk@redhat.com>
X-Patchwork-Id: 12140715
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-11.0 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS autolearn=ham
	autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 1D65FC433E6
	for <kvm@archiver.kernel.org>; Mon, 15 Mar 2021 21:10:25 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id CCF3864F46
	for <kvm@archiver.kernel.org>; Mon, 15 Mar 2021 21:10:24 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S233955AbhCOVJx (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Mon, 15 Mar 2021 17:09:53 -0400
Received: from us-smtp-delivery-124.mimecast.com ([216.205.24.124]:56391 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S234002AbhCOVJ1 (ORCPT
        <rfc822;kvm@vger.kernel.org>); Mon, 15 Mar 2021 17:09:27 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1615842566;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=WaSFqC/ENxU5MJhb5PdNljtQvKtogr2JobEHM9p+t6M=;
        b=UBaBFdYCLGVBeuelQLZENop4yuvRzn7yeLN6IZgkgfKbW3zrEb+U7oC525QxkTCAnwWuFT
        0bBAUSiCzQ2h7pndo5WuI3JXVvYlAY8I8Wcb3ZUpxD/bWZPweKB7/WNVaYqI6e6wnhuUuI
        EdBtXap8Nlqj+0Z6Qfr7RJvU9V14wZ4=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-459-UnlnbXwINsiZlBfNzCz9BQ-1; Mon, 15 Mar 2021 17:09:24 -0400
X-MC-Unique: UnlnbXwINsiZlBfNzCz9BQ-1
Received: from smtp.corp.redhat.com (int-mx02.intmail.prod.int.phx2.redhat.com
 [10.5.11.12])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id BA2DE107465E
        for <kvm@vger.kernel.org>; Mon, 15 Mar 2021 21:09:23 +0000 (UTC)
Received: from localhost.localdomain (unknown [10.35.207.30])
        by smtp.corp.redhat.com (Postfix) with ESMTP id E220417B80;
        Mon, 15 Mar 2021 21:09:22 +0000 (UTC)
From: Maxim Levitsky <mlevitsk@redhat.com>
To: kvm@vger.kernel.org
Cc: Maxim Levitsky <mlevitsk@redhat.com>
Subject: [PATCH v2 0/2] Simple test for sysenter instruction
Date: Mon, 15 Mar 2021 23:09:19 +0200
Message-Id: <20210315210921.626351-1-mlevitsk@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.12
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Hi,

This patch series adds a simple test for sysenter instruction running in
comp32 mode, while using Intel vendor ID.

In this setting, KVM emulates this instruction to help with cross-vendor
migration on AMD.

I also added a patch to 'msr' test to run it with Intel's vendor ID, since this
test tests that SYSENTER EIP/ESP msrs are 64 bit wide which is only true on AMD.

KVM used to emulate these msrs to be always 64 bit on AMD, but this soon will
be changed to do the emulation only when guest CPU vendor ID is of Intel.

Best regards,
    Maxim Levitsky

Maxim Levitsky (2):
  x86/msr: run this test with intel vendor id
  Add a simple test for SYSENTER instruction.

 x86/Makefile.x86_64 |  3 ++
 x86/cstart64.S      |  1 +
 x86/sysenter.c      | 91 +++++++++++++++++++++++++++++++++++++++++++++
 x86/unittests.cfg   |  6 +++
 4 files changed, 101 insertions(+)
 create mode 100644 x86/sysenter.c
```
#### [PATCH 0/3] KVM: my debug patch queue
##### From: Maxim Levitsky <mlevitsk@redhat.com>

```c
From patchwork Mon Mar 15 22:10:17 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Maxim Levitsky <mlevitsk@redhat.com>
X-Patchwork-Id: 12140759
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-11.0 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS autolearn=ham
	autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 0EFC3C43381
	for <kvm@archiver.kernel.org>; Mon, 15 Mar 2021 22:11:14 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id CAF9364F64
	for <kvm@archiver.kernel.org>; Mon, 15 Mar 2021 22:11:13 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S232169AbhCOWKl (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Mon, 15 Mar 2021 18:10:41 -0400
Received: from us-smtp-delivery-124.mimecast.com ([216.205.24.124]:39314 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S232605AbhCOWKb (ORCPT
        <rfc822;kvm@vger.kernel.org>); Mon, 15 Mar 2021 18:10:31 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1615846230;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=GO4Svw6p1VObWYcp8yWMtHx+jBqxgLew+cAErGqrrHw=;
        b=ZXzROqVC+NIBFFOHqbfv4OmaH/FZ9mto+xfqza7ja/Qic/Ra3jRFJF90VENUycRhWj5Y/f
        fhNRL5Z68QNx0Y+hYPLQ8MuHwg/l+8mWsbee5w8mXzUFwgWNpgzdNTp9scovdJJEmGvJty
        mtvU96nhdmNPQDckbi3xXyNmTmOB+vU=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-205-dg5EnmfcNuaKPeeqVJjVGw-1; Mon, 15 Mar 2021 18:10:29 -0400
X-MC-Unique: dg5EnmfcNuaKPeeqVJjVGw-1
Received: from smtp.corp.redhat.com (int-mx06.intmail.prod.int.phx2.redhat.com
 [10.5.11.16])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id D693C801817;
        Mon, 15 Mar 2021 22:10:26 +0000 (UTC)
Received: from localhost.localdomain (unknown [10.35.207.30])
        by smtp.corp.redhat.com (Postfix) with ESMTP id EAD6C5C261;
        Mon, 15 Mar 2021 22:10:21 +0000 (UTC)
From: Maxim Levitsky <mlevitsk@redhat.com>
To: kvm@vger.kernel.org
Cc: Vitaly Kuznetsov <vkuznets@redhat.com>,
        linux-kernel@vger.kernel.org, Thomas Gleixner <tglx@linutronix.de>,
        Wanpeng Li <wanpengli@tencent.com>,
        Kieran Bingham <kbingham@kernel.org>,
        Jessica Yu <jeyu@kernel.org>,
        Jan Kiszka <jan.kiszka@siemens.com>,
        Andrew Morton <akpm@linux-foundation.org>,
        x86@kernel.org (maintainer:X86 ARCHITECTURE (32-BIT AND 64-BIT)),
        Joerg Roedel <joro@8bytes.org>,
        Sean Christopherson <seanjc@google.com>,
        Jim Mattson <jmattson@google.com>,
        Borislav Petkov <bp@alien8.de>,
        Stefano Garzarella <sgarzare@redhat.com>,
        Maxim Levitsky <mlevitsk@redhat.com>,
        "H. Peter Anvin" <hpa@zytor.com>,
        Paolo Bonzini <pbonzini@redhat.com>,
        Ingo Molnar <mingo@redhat.com>
Subject: [PATCH 0/3] KVM: my debug patch queue
Date: Tue, 16 Mar 2021 00:10:17 +0200
Message-Id: <20210315221020.661693-1-mlevitsk@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.16
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Hi!

I would like to publish two debug features which were needed for other stuff
I work on.

One is the reworked lx-symbols script which now actually works on at least
gdb 9.1 (gdb 9.2 was reported to fail to load the debug symbols from the kernel
for some reason, not related to this patch) and upstream qemu.

The other feature is the ability to trap all guest exceptions (on SVM for now)
and see them in kvmtrace prior to potential merge to double/triple fault.

This can be very useful and I already had to manually patch KVM a few
times for this.
I will, once time permits, implement this feature on Intel as well.

Best regards,
        Maxim Levitsky

Maxim Levitsky (3):
  scripts/gdb: rework lx-symbols gdb script
  KVM: x86: guest debug: don't inject interrupts while single stepping
  KVM: SVM: allow to intercept all exceptions for debug

 arch/x86/include/asm/kvm_host.h |   2 +
 arch/x86/kvm/svm/svm.c          |  77 ++++++++++++++++++++++-
 arch/x86/kvm/svm/svm.h          |   5 +-
 arch/x86/kvm/x86.c              |  11 +++-
 kernel/module.c                 |   8 ++-
 scripts/gdb/linux/symbols.py    | 106 +++++++++++++++++++++++---------
 6 files changed, 174 insertions(+), 35 deletions(-)
```
