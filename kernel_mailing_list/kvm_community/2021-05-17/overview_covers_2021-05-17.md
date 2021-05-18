

#### [PATCH v7 00/12] Introduce VDUSE - vDPA Device in Userspace
##### From: Xie Yongji <xieyongji@bytedance.com>

```c
From patchwork Mon May 17 09:55:01 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Xie Yongji <xieyongji@bytedance.com>
X-Patchwork-Id: 12261393
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.8 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_PATCH,MAILING_LIST_MULTI,
	MENTIONS_GIT_HOSTING,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT
	autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 2AA61C43460
	for <kvm@archiver.kernel.org>; Mon, 17 May 2021 09:55:59 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id F356D610FC
	for <kvm@archiver.kernel.org>; Mon, 17 May 2021 09:55:58 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S229474AbhEQJ5N (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Mon, 17 May 2021 05:57:13 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:35118 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S230248AbhEQJ5M (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 17 May 2021 05:57:12 -0400
Received: from mail-pj1-x102d.google.com (mail-pj1-x102d.google.com
 [IPv6:2607:f8b0:4864:20::102d])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id E5F85C061573
        for <kvm@vger.kernel.org>; Mon, 17 May 2021 02:55:56 -0700 (PDT)
Received: by mail-pj1-x102d.google.com with SMTP id q6so3376564pjj.2
        for <kvm@vger.kernel.org>; Mon, 17 May 2021 02:55:56 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=bytedance-com.20150623.gappssmtp.com; s=20150623;
        h=from:to:cc:subject:date:message-id:mime-version
         :content-transfer-encoding;
        bh=MouAXVU0J/gA4I5GTy8SeyqWRECXQkyC0TfR7o+Hz5c=;
        b=X0NTR58R14qMnCCKXWSzamLPSdg5ExgcnZ0DImKaOvMCmLt88fIAkwnd6J2goufzIn
         LZOX15kilgG1Dpn4/vP2PG+4Fhi9vZbkrEJqmJZewuKtHtv9oigd8ov8uQnpZhAzXzzZ
         HznvMz8uE0gElfCIgP2ZD95kpy/KRxDkVIqHHTv9FWNUnsQIHKAIXZ4iZfJ5B87lJ3EE
         ls2Ts5Iq15VVio05oK4AXMznPbS+avf5o5+LNh2/OC2v2z84gqMWLsSyQHn35jYspPDH
         Snhgb9KU1Bbc4vtTjC0l7f8i4UFqNtKCOGkMtTUJP80evpQj9KsuMqb0xS+rNEXU/L94
         UBtg==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:mime-version
         :content-transfer-encoding;
        bh=MouAXVU0J/gA4I5GTy8SeyqWRECXQkyC0TfR7o+Hz5c=;
        b=YEQ7J9/QpOq8BQP0pl4xv8kcLa3cQ5fu6F/JHiVHyMt33v66LLB4kjqI5ORWmeXd+M
         RNqHqWvCObPD2g/LNsvzlgyNO1VXDwNhC6kNZPA9sxz76qPg43kf5P/Q3UxcW0QkKOcV
         4opXJwUARGAPs+DnFC6XonbzGZyc54UIHop/qeYaWryw65hE2uplso2K9SWZQWwhwfxA
         gfWkMCj1nIDeZ0TE+RcXDhFPn3LIvEVxFo3K2f6md5hEcYTuf9MC9dOBSWsgNrO4V0ht
         WpvFKqorrzxXdaaJi1PNUm3AhKIKUZLuWKdRk4Hrm9niod+db43tkNJhQkXczbfefSWG
         UJyA==
X-Gm-Message-State: AOAM53193sGTzgMMSgPDPwbSkbeaYW+tPtR0OHZHgx9n/vafLC26kkwd
        U2a4MKpEjQw6giJh72eLpU8G
X-Google-Smtp-Source: 
 ABdhPJy1ehb6Kie4m4QxEvvF1uyhuUm0zgw7klsdTztxYar5dk7+iQLkZ++eK/Arz2ab9Zz4tUZOzQ==
X-Received: by 2002:a17:90a:bc0c:: with SMTP id
 w12mr26427487pjr.213.1621245356449;
        Mon, 17 May 2021 02:55:56 -0700 (PDT)
Received: from localhost ([139.177.225.253])
        by smtp.gmail.com with ESMTPSA id
 h19sm10062442pgm.40.2021.05.17.02.55.54
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Mon, 17 May 2021 02:55:56 -0700 (PDT)
From: Xie Yongji <xieyongji@bytedance.com>
To: mst@redhat.com, jasowang@redhat.com, stefanha@redhat.com,
        sgarzare@redhat.com, parav@nvidia.com, hch@infradead.org,
        christian.brauner@canonical.com, rdunlap@infradead.org,
        willy@infradead.org, viro@zeniv.linux.org.uk, axboe@kernel.dk,
        bcrl@kvack.org, corbet@lwn.net, mika.penttila@nextfour.com,
        dan.carpenter@oracle.com, joro@8bytes.org
Cc: virtualization@lists.linux-foundation.org, netdev@vger.kernel.org,
        kvm@vger.kernel.org, linux-fsdevel@vger.kernel.org,
        iommu@lists.linux-foundation.org, linux-kernel@vger.kernel.org
Subject: [PATCH v7 00/12] Introduce VDUSE - vDPA Device in Userspace
Date: Mon, 17 May 2021 17:55:01 +0800
Message-Id: <20210517095513.850-1-xieyongji@bytedance.com>
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

To make the userspace VDUSE processes such as qemu-storage-daemon able to
run unprivileged. We did some works on virtio driver to avoid trusting
device, including:

  - validating the device status:

    * https://lore.kernel.org/lkml/20210517093428.670-1-xieyongji@bytedance.com/

  - validating the used length: 

    * https://lore.kernel.org/lkml/20210517090836.533-1-xieyongji@bytedance.com/

  - validating the device config:
    
    * patch 4 ("virtio-blk: Add validation for block size in config space")

  - validating the device response:

    * patch 5 ("virtio_scsi: Add validation for residual bytes from response")

Since I'm not sure if I missing something during auditing, especially on some
virtio device drivers that I'm not familiar with, now we only support emualting
a few vDPA devices by default, including: virtio-net device, virtio-blk device,
virtio-scsi device and virtio-fs device. This limitaion can help to reduce
security risks. When a sysadmin trusts the userspace process enough, it can relax
the limitation with a 'allow_unsafe_device_emulation' module parameter.

Future work:
  - Improve performance
  - Userspace library (find a way to reuse device emulation code in qemu/rust-vmm)

V6 to V7:
- Export alloc_iova_fast()
- Add get_config_size() callback
- Add some patches to avoid trusting virtio devices
- Add limited device emulation
- Add some documents
- Use workqueue to inject config irq
- Add parameter on vq irq injecting
- Rename vduse_domain_get_mapping_page() to vduse_domain_get_coherent_page()
- Add WARN_ON() to catch message failure
- Add some padding/reserved fields to uAPI structure
- Fix some bugs
- Rebase to vhost.git

V5 to V6:
- Export receive_fd() instead of __receive_fd()
- Factor out the unmapping logic of pa and va separatedly
- Remove the logic of bounce page allocation in page fault handler
- Use PAGE_SIZE as IOVA allocation granule
- Add EPOLLOUT support
- Enable setting API version in userspace
- Fix some bugs

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

Xie Yongji (12):
  iova: Export alloc_iova_fast()
  file: Export receive_fd() to modules
  eventfd: Increase the recursion depth of eventfd_signal()
  virtio-blk: Add validation for block size in config space
  virtio_scsi: Add validation for residual bytes from response
  vhost-iotlb: Add an opaque pointer for vhost IOTLB
  vdpa: Add an opaque pointer for vdpa_config_ops.dma_map()
  vdpa: factor out vhost_vdpa_pa_map() and vhost_vdpa_pa_unmap()
  vdpa: Support transferring virtual addressing during DMA mapping
  vduse: Implement an MMU-based IOMMU driver
  vduse: Introduce VDUSE - vDPA Device in Userspace
  Documentation: Add documentation for VDUSE

 Documentation/userspace-api/index.rst              |    1 +
 Documentation/userspace-api/ioctl/ioctl-number.rst |    1 +
 Documentation/userspace-api/vduse.rst              |  243 ++++
 drivers/block/virtio_blk.c                         |    2 +-
 drivers/iommu/iova.c                               |    1 +
 drivers/scsi/virtio_scsi.c                         |    2 +-
 drivers/vdpa/Kconfig                               |   10 +
 drivers/vdpa/Makefile                              |    1 +
 drivers/vdpa/ifcvf/ifcvf_main.c                    |    2 +-
 drivers/vdpa/mlx5/net/mlx5_vnet.c                  |    2 +-
 drivers/vdpa/vdpa.c                                |    9 +-
 drivers/vdpa/vdpa_sim/vdpa_sim.c                   |    8 +-
 drivers/vdpa/vdpa_user/Makefile                    |    5 +
 drivers/vdpa/vdpa_user/iova_domain.c               |  531 +++++++
 drivers/vdpa/vdpa_user/iova_domain.h               |   70 +
 drivers/vdpa/vdpa_user/vduse_dev.c                 | 1453 ++++++++++++++++++++
 drivers/vdpa/virtio_pci/vp_vdpa.c                  |    2 +-
 drivers/vhost/iotlb.c                              |   20 +-
 drivers/vhost/vdpa.c                               |  148 +-
 fs/eventfd.c                                       |    2 +-
 fs/file.c                                          |    6 +
 include/linux/eventfd.h                            |    5 +-
 include/linux/file.h                               |    7 +-
 include/linux/vdpa.h                               |   21 +-
 include/linux/vhost_iotlb.h                        |    3 +
 include/uapi/linux/vduse.h                         |  178 +++
 26 files changed, 2681 insertions(+), 52 deletions(-)
 create mode 100644 Documentation/userspace-api/vduse.rst
 create mode 100644 drivers/vdpa/vdpa_user/Makefile
 create mode 100644 drivers/vdpa/vdpa_user/iova_domain.c
 create mode 100644 drivers/vdpa/vdpa_user/iova_domain.h
 create mode 100644 drivers/vdpa/vdpa_user/vduse_dev.c
 create mode 100644 include/uapi/linux/vduse.h
```
#### [PATCH v2 0/7] KVM: nVMX: Fixes for nested state migration when eVMCS
##### From: Vitaly Kuznetsov <vkuznets@redhat.com>

```c
From patchwork Mon May 17 13:50:47 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Vitaly Kuznetsov <vkuznets@redhat.com>
X-Patchwork-Id: 12262035
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-11.1 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS autolearn=ham
	autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 23D7EC433B4
	for <kvm@archiver.kernel.org>; Mon, 17 May 2021 13:51:03 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 03DB061209
	for <kvm@archiver.kernel.org>; Mon, 17 May 2021 13:51:02 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S237549AbhEQNwR (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Mon, 17 May 2021 09:52:17 -0400
Received: from us-smtp-delivery-124.mimecast.com ([170.10.133.124]:59811 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S233139AbhEQNwR (ORCPT
        <rfc822;kvm@vger.kernel.org>); Mon, 17 May 2021 09:52:17 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1621259460;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=C+tg4c3vND5Z6+PsNiPP16d8jOHSNadBgt74LgH79DM=;
        b=EYDrNMP92yCUa6d3wixDYUGfjhqrJsktX7HJob+vAMJPguJZFXrEQ+RNkfkaaL1vdw1r4i
        1QQtOrdibo7XXNXHiGcQi2ja0zKEiYakBmc+OH0lHJpEzLzqQbskYarDCA5XDUDN4m54iy
        mBnCt2cGez/sBBFxhXUVsniwl4usQ1Q=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-248-6QNT2PQ7MiqH4mdwbB0tGg-1; Mon, 17 May 2021 09:50:59 -0400
X-MC-Unique: 6QNT2PQ7MiqH4mdwbB0tGg-1
Received: from smtp.corp.redhat.com (int-mx06.intmail.prod.int.phx2.redhat.com
 [10.5.11.16])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id CC973801106;
        Mon, 17 May 2021 13:50:57 +0000 (UTC)
Received: from vitty.brq.redhat.com (unknown [10.40.194.112])
        by smtp.corp.redhat.com (Postfix) with ESMTP id C08985C1A1;
        Mon, 17 May 2021 13:50:55 +0000 (UTC)
From: Vitaly Kuznetsov <vkuznets@redhat.com>
To: kvm@vger.kernel.org, Paolo Bonzini <pbonzini@redhat.com>
Cc: Sean Christopherson <seanjc@google.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Maxim Levitsky <mlevitsk@redhat.com>,
        linux-kernel@vger.kernel.org
Subject: [PATCH v2 0/7] KVM: nVMX: Fixes for nested state migration when eVMCS
 is in use
Date: Mon, 17 May 2021 15:50:47 +0200
Message-Id: <20210517135054.1914802-1-vkuznets@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.16
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Changes since v1 (Sean):
- Drop now-unneeded curly braces in nested_sync_vmcs12_to_shadow().
- Pass 'evmcs->hv_clean_fields' instead of 'bool from_vmentry' to
  copy_enlightened_to_vmcs12().

Commit f5c7e8425f18 ("KVM: nVMX: Always make an attempt to map eVMCS after
migration") fixed the most obvious reason why Hyper-V on KVM (e.g. Win10
 + WSL2) was crashing immediately after migration. It was also reported
that we have more issues to fix as, while the failure rate was lowered 
signifincatly, it was still possible to observe crashes after several
dozens of migration. Turns out, the issue arises when we manage to issue
KVM_GET_NESTED_STATE right after L2->L2 VMEXIT but before L1 gets a chance
to run. This state is tracked with 'need_vmcs12_to_shadow_sync' flag but
the flag itself is not part of saved nested state. A few other less 
significant issues are fixed along the way.

While there's no proof this series fixes all eVMCS related problems,
Win10+WSL2 was able to survive 3333 (thanks, Max!) migrations without
crashing in testing.

Patches are based on the current kvm/next tree.

Vitaly Kuznetsov (7):
  KVM: nVMX: Introduce nested_evmcs_is_used()
  KVM: nVMX: Release enlightened VMCS on VMCLEAR
  KVM: nVMX: Ignore 'hv_clean_fields' data when eVMCS data is copied in
    vmx_get_nested_state()
  KVM: nVMX: Force enlightened VMCS sync from nested_vmx_failValid()
  KVM: nVMX: Reset eVMCS clean fields data from prepare_vmcs02()
  KVM: nVMX: Request to sync eVMCS from VMCS12 after migration
  KVM: selftests: evmcs_test: Test that KVM_STATE_NESTED_EVMCS is never
    lost

 arch/x86/kvm/vmx/nested.c                     | 110 ++++++++++++------
 .../testing/selftests/kvm/x86_64/evmcs_test.c |  64 +++++-----
 2 files changed, 115 insertions(+), 59 deletions(-)
```
#### [PATCH v5 0/4] KVM statistics data fd-based binary interface
##### From: Jing Zhang <jingzhangos@google.com>

```c
From patchwork Mon May 17 14:53:10 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Jing Zhang <jingzhangos@google.com>
X-Patchwork-Id: 12262413
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-21.3 required=3.0 tests=BAYES_00,DKIMWL_WL_MED,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED,
	USER_AGENT_GIT,USER_IN_DEF_DKIM_WL autolearn=unavailable autolearn_force=no
	version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id D6E0BC433B4
	for <kvm@archiver.kernel.org>; Mon, 17 May 2021 16:23:54 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id C20CB61019
	for <kvm@archiver.kernel.org>; Mon, 17 May 2021 16:23:54 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S245059AbhEQQZK (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Mon, 17 May 2021 12:25:10 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:37694 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1346369AbhEQQYa (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 17 May 2021 12:24:30 -0400
Received: from mail-yb1-xb49.google.com (mail-yb1-xb49.google.com
 [IPv6:2607:f8b0:4864:20::b49])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 60E7AC034616
        for <kvm@vger.kernel.org>; Mon, 17 May 2021 07:53:20 -0700 (PDT)
Received: by mail-yb1-xb49.google.com with SMTP id
 q6-20020a25bfc60000b02904f9715cd13cso9636524ybm.3
        for <kvm@vger.kernel.org>; Mon, 17 May 2021 07:53:20 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=date:message-id:mime-version:subject:from:to:cc;
        bh=4HJ66++ZeWXgUMvYaSH59XIw9b5t7+bKx/IVCdRe4G0=;
        b=tEchB3/NvHaS2iYBDSPPFoO6QDvpctN/kh8GNdmz+3BV51fgxznShQgFUWKmVHsnCB
         aIexAfoWXg6sUKvOWx3mQ0ROzie/dXZfhTjzynlDE/FK5ic3y2TmhEJfI8B7wwhTPFpn
         5h+DUByZwY/YPA72ASBm/UMCFkrOZA/0KTlulemK4yZ/LlMl38QNjbYECaAyv39jZ2PN
         kDcNISNoaDXMKrAuVsEts6T5iHO9gRSmdqijjd9/w146GvRse1G4R+oaPhYi9pQfgSH5
         oDg000282+nVSW7qP3y3olOlbJ9JWfuRlxcA2Gv3VnuXIzwfdrZZ4BCdlEpRaNi4S8X0
         BP7w==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:date:message-id:mime-version:subject:from:to:cc;
        bh=4HJ66++ZeWXgUMvYaSH59XIw9b5t7+bKx/IVCdRe4G0=;
        b=O8P5OhGGFXAS0ltBpaRdszHzOp/W0mSO5nL9gxF7C4XrvRxcegTIk3w61DU3VYvk1W
         Rq0rLFjL1amdAM38SHBJiB5fC8xb0IlXydq84jKb2gGIZTcoC7G3hHlWJzOppbexAVwI
         QAJhZMPsqrzJv+XuUor59ywTt4DF/Tqn1EEqgkA+78oNAVSZuYGB7yS1RrlEVSQnYHTZ
         of0WYuZEb0QSY628SRfaCkyy1AQKLsP2+0xYlABBoeDq219JFjWvH3UWn6iGk1PYHH9b
         ERj6bmrsVeh86lF7PXCuz+zSAH7wRfM28HsWacRzs0CIl6hssOWHOnahDmAMRqUnA2Nn
         gLDA==
X-Gm-Message-State: AOAM530T64DhaNBmZE1AX7cMkZZfsli4sxd5t3+1Otod9ItZZb5kHH/j
        gbX+mQHO3K+1GXABxsRZ5YWbPgnZ084IlvDTkoa9tttlkz5K3f0OSe62ruYDHPcY1+YtrTQQ4fL
        M6M9LEGuQDnqTPhbcojQV+HK5Gjp3DzxNmcr5kRG0MXnP1F4/pgkqV4fBtDWEqykfRJlpgXc=
X-Google-Smtp-Source: 
 ABdhPJxVSYPxCoq4VDHfaNcpUYnOeavMMHtUfXfKI9+aR8ach/FPO0fxCU0HVpVBmnunXxkvJEfDJDgTUXDf+b1H8A==
X-Received: from jgzg.c.googlers.com ([fda3:e722:ac3:10:7f:e700:c0a8:1acf])
 (user=jingzhangos job=sendgmr) by 2002:a5b:1c8:: with SMTP id
 f8mr317938ybp.44.1621263199546; Mon, 17 May 2021 07:53:19 -0700 (PDT)
Date: Mon, 17 May 2021 14:53:10 +0000
Message-Id: <20210517145314.157626-1-jingzhangos@google.com>
Mime-Version: 1.0
X-Mailer: git-send-email 2.31.1.751.gd2f1c929bd-goog
Subject: [PATCH v5 0/4] KVM statistics data fd-based binary interface
From: Jing Zhang <jingzhangos@google.com>
To: KVM <kvm@vger.kernel.org>, KVMARM <kvmarm@lists.cs.columbia.edu>,
        LinuxMIPS <linux-mips@vger.kernel.org>,
        KVMPPC <kvm-ppc@vger.kernel.org>,
        LinuxS390 <linux-s390@vger.kernel.org>,
        Linuxkselftest <linux-kselftest@vger.kernel.org>,
        Paolo Bonzini <pbonzini@redhat.com>,
        Marc Zyngier <maz@kernel.org>,
        James Morse <james.morse@arm.com>,
        Julien Thierry <julien.thierry.kdev@gmail.com>,
        Suzuki K Poulose <suzuki.poulose@arm.com>,
        Will Deacon <will@kernel.org>,
        Huacai Chen <chenhuacai@kernel.org>,
        Aleksandar Markovic <aleksandar.qemu.devel@gmail.com>,
        Thomas Bogendoerfer <tsbogend@alpha.franken.de>,
        Paul Mackerras <paulus@ozlabs.org>,
        Christian Borntraeger <borntraeger@de.ibm.com>,
        Janosch Frank <frankja@linux.ibm.com>,
        David Hildenbrand <david@redhat.com>,
        Cornelia Huck <cohuck@redhat.com>,
        Claudio Imbrenda <imbrenda@linux.ibm.com>,
        Sean Christopherson <seanjc@google.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Jim Mattson <jmattson@google.com>,
        Peter Shier <pshier@google.com>,
        Oliver Upton <oupton@google.com>,
        David Rientjes <rientjes@google.com>,
        Emanuele Giuseppe Esposito <eesposit@redhat.com>
Cc: Jing Zhang <jingzhangos@google.com>
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This patchset provides a file descriptor for every VM and VCPU to read
KVM statistics data in binary format.
It is meant to provide a lightweight, flexible, scalable and efficient
lock-free solution for user space telemetry applications to pull the
statistics data periodically for large scale systems. The pulling
frequency could be as high as a few times per second.
In this patchset, every statistics data are treated to have some
attributes as below:
  * architecture dependent or common
  * VM statistics data or VCPU statistics data
  * type: cumulative, instantaneous,
  * unit: none for simple counter, nanosecond, microsecond,
    millisecond, second, Byte, KiByte, MiByte, GiByte. Clock Cycles
Since no lock/synchronization is used, the consistency between all
the statistics data is not guaranteed. That means not all statistics
data are read out at the exact same time, since the statistics date
are still being updated by KVM subsystems while they are read out.
---

* v4 -> v5
  - Rebase to kvm/queue, commit a4345a7cecfb ("Merge tag
    'kvmarm-fixes-5.13-1'")
  - Change maximum stats name length to 48
  - Replace VM_STATS_COMMON/VCPU_STATS_COMMON macros with stats
    descriptor definition macros.
  - Fixed some errors/warnings reported by checkpatch.pl

* v3 -> v4
  - Rebase to kvm/queue, commit 9f242010c3b4 ("KVM: avoid "deadlock"
    between install_new_memslots and MMU notifier")
  - Use C-stype comments in the whole patch
  - Fix wrong count for x86 VCPU stats descriptors
  - Fix KVM stats data size counting and validity check in selftest

* v2 -> v3
  - Rebase to kvm/queue, commit edf408f5257b ("KVM: avoid "deadlock"
    between install_new_memslots and MMU notifier")
  - Resolve some nitpicks about format

* v1 -> v2
  - Use ARRAY_SIZE to count the number of stats descriptors
  - Fix missing `size` field initialization in macro STATS_DESC

[1] https://lore.kernel.org/kvm/20210402224359.2297157-1-jingzhangos@google.com
[2] https://lore.kernel.org/kvm/20210415151741.1607806-1-jingzhangos@google.com
[3] https://lore.kernel.org/kvm/20210423181727.596466-1-jingzhangos@google.com
[4] https://lore.kernel.org/kvm/20210429203740.1935629-1-jingzhangos@google.com

---

Jing Zhang (4):
  KVM: stats: Separate common stats from architecture specific ones
  KVM: stats: Add fd-based API to read binary stats data
  KVM: stats: Add documentation for statistics data binary interface
  KVM: selftests: Add selftest for KVM statistics data binary interface

 Documentation/virt/kvm/api.rst                | 171 ++++++++
 arch/arm64/include/asm/kvm_host.h             |   9 +-
 arch/arm64/kvm/guest.c                        |  38 +-
 arch/mips/include/asm/kvm_host.h              |   9 +-
 arch/mips/kvm/mips.c                          |  64 ++-
 arch/powerpc/include/asm/kvm_host.h           |   9 +-
 arch/powerpc/kvm/book3s.c                     |  64 ++-
 arch/powerpc/kvm/book3s_hv.c                  |  12 +-
 arch/powerpc/kvm/book3s_pr.c                  |   2 +-
 arch/powerpc/kvm/book3s_pr_papr.c             |   2 +-
 arch/powerpc/kvm/booke.c                      |  59 ++-
 arch/s390/include/asm/kvm_host.h              |   9 +-
 arch/s390/kvm/kvm-s390.c                      | 129 +++++-
 arch/x86/include/asm/kvm_host.h               |   9 +-
 arch/x86/kvm/x86.c                            |  67 +++-
 include/linux/kvm_host.h                      | 136 ++++++-
 include/linux/kvm_types.h                     |  12 +
 include/uapi/linux/kvm.h                      |  50 +++
 tools/testing/selftests/kvm/.gitignore        |   1 +
 tools/testing/selftests/kvm/Makefile          |   3 +
 .../testing/selftests/kvm/include/kvm_util.h  |   3 +
 .../selftests/kvm/kvm_bin_form_stats.c        | 379 ++++++++++++++++++
 tools/testing/selftests/kvm/lib/kvm_util.c    |  12 +
 virt/kvm/kvm_main.c                           | 237 ++++++++++-
 24 files changed, 1396 insertions(+), 90 deletions(-)
 create mode 100644 tools/testing/selftests/kvm/kvm_bin_form_stats.c


base-commit: a4345a7cecfb91ae78cd43d26b0c6a956420761a
```
#### [PATCH v1 00/11] KVM: s390: pv: implement lazy destroy
##### From: Claudio Imbrenda <imbrenda@linux.ibm.com>

```c
From patchwork Mon May 17 20:07:47 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Claudio Imbrenda <imbrenda@linux.ibm.com>
X-Patchwork-Id: 12263055
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-11.8 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_PATCH,MAILING_LIST_MULTI,
	SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT autolearn=unavailable
	autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id B3181C433B4
	for <kvm@archiver.kernel.org>; Mon, 17 May 2021 20:08:07 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 8F75361004
	for <kvm@archiver.kernel.org>; Mon, 17 May 2021 20:08:07 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S237576AbhEQUJW (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Mon, 17 May 2021 16:09:22 -0400
Received: from mx0b-001b2d01.pphosted.com ([148.163.158.5]:46510 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S236354AbhEQUJW (ORCPT
        <rfc822;kvm@vger.kernel.org>); Mon, 17 May 2021 16:09:22 -0400
Received: from pps.filterd (m0098416.ppops.net [127.0.0.1])
        by mx0b-001b2d01.pphosted.com (8.16.0.43/8.16.0.43) with SMTP id
 14HK3YOe092009;
        Mon, 17 May 2021 16:08:05 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=ibm.com;
 h=from : to : cc : subject
 : date : message-id : mime-version : content-transfer-encoding; s=pp1;
 bh=j1vLWN6i9enhktiCETvIhTZ3O+xze4qWVqlCsrnxkWw=;
 b=qYbr/kNsUYqSygtI7mDr1Bxrrw916PVN+6zUPw1OUiGfyRbhFsAD5fb2DHN3h3qXUt4q
 tnmtdQArdviB9H+o1UzcFFhyJgnIQROw5z6+8V+J7dJVRBdY2AAdFDbkpqIAlhrUrwwg
 +UT1KSt11LFfpG0FZQOlSkJRPAfXR6Mtz0olnmm0PdUefi5EnuEeun72CDKaqQk5s+2o
 T9pqFxwGvI1X75EaiASLtERMji+o7KGxt85NeVnkT7xMxU9gQzv4G97ha/dZ4v5a98kf
 a5+eSViD3XKnpqHOMAtZdhSA5XpDR9JQkkiu4FTsCb1txaBLz4wVrnRS+LlWzDnTuIlf Ew==
Received: from pps.reinject (localhost [127.0.0.1])
        by mx0b-001b2d01.pphosted.com with ESMTP id 38kuk3egbw-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Mon, 17 May 2021 16:08:04 -0400
Received: from m0098416.ppops.net (m0098416.ppops.net [127.0.0.1])
        by pps.reinject (8.16.0.43/8.16.0.43) with SMTP id 14HK4RoL098401;
        Mon, 17 May 2021 16:08:04 -0400
Received: from ppma06ams.nl.ibm.com (66.31.33a9.ip4.static.sl-reverse.com
 [169.51.49.102])
        by mx0b-001b2d01.pphosted.com with ESMTP id 38kuk3egbe-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Mon, 17 May 2021 16:08:04 -0400
Received: from pps.filterd (ppma06ams.nl.ibm.com [127.0.0.1])
        by ppma06ams.nl.ibm.com (8.16.0.43/8.16.0.43) with SMTP id
 14HK7SPm028451;
        Mon, 17 May 2021 20:08:02 GMT
Received: from b06avi18878370.portsmouth.uk.ibm.com
 (b06avi18878370.portsmouth.uk.ibm.com [9.149.26.194])
        by ppma06ams.nl.ibm.com with ESMTP id 38j5jgs2ua-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Mon, 17 May 2021 20:08:02 +0000
Received: from d06av21.portsmouth.uk.ibm.com (d06av21.portsmouth.uk.ibm.com
 [9.149.105.232])
        by b06avi18878370.portsmouth.uk.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id 14HK7Vmu21561750
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Mon, 17 May 2021 20:07:31 GMT
Received: from d06av21.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 7356A52051;
        Mon, 17 May 2021 20:07:59 +0000 (GMT)
Received: from ibm-vm.ibmuc.com (unknown [9.145.14.34])
        by d06av21.portsmouth.uk.ibm.com (Postfix) with ESMTP id 109B052050;
        Mon, 17 May 2021 20:07:59 +0000 (GMT)
From: Claudio Imbrenda <imbrenda@linux.ibm.com>
To: kvm@vger.kernel.org
Cc: cohuck@redhat.com, borntraeger@de.ibm.com, frankja@linux.ibm.com,
        thuth@redhat.com, pasic@linux.ibm.com, david@redhat.com,
        linux-s390@vger.kernel.org, linux-kernel@vger.kernel.org
Subject: [PATCH v1 00/11] KVM: s390: pv: implement lazy destroy
Date: Mon, 17 May 2021 22:07:47 +0200
Message-Id: <20210517200758.22593-1-imbrenda@linux.ibm.com>
X-Mailer: git-send-email 2.31.1
MIME-Version: 1.0
X-TM-AS-GCONF: 00
X-Proofpoint-GUID: ExXuGPCt5hxBFRYdGVfjbCtb4H7e0DRc
X-Proofpoint-ORIG-GUID: hm8PRwMcf2gCUfsos0KqPNdvMdqEfIW0
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.391,18.0.761
 definitions=2021-05-17_08:2021-05-17,2021-05-17 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 lowpriorityscore=0
 clxscore=1011 bulkscore=0 adultscore=0 malwarescore=0 phishscore=0
 spamscore=0 priorityscore=1501 mlxlogscore=873 suspectscore=0 mlxscore=0
 impostorscore=0 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.12.0-2104190000 definitions=main-2105170140
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Previously, when a protected VM was rebooted or when it was shut down,
its memory was made unprotected, and then the protected VM itself was
destroyed. Looping over the whole address space can take some time,
considering the overhead of the various Ultravisor Calls (UVCs).  This
means that a reboot or a shutdown would take a potentially long amount
of time, depending on the amount of used memory.

This patchseries implements a deferred destroy mechanism for protected
guests. When a protected guest is destroyed, its memory is cleared in
background, allowing the guest to restart or terminate significantly
faster than before.

There are 2 possibilities when a protected VM is torn down:
* it still has an address space associated (reboot case)
* it does not have an address space anymore (shutdown case)

For the reboot case, the reference count of the mm is increased, and
then a background thread is started to clean up. Once the thread went
through the whole address space, the protected VM is actually
destroyed.

For the shutdown case, a list of pages to be destroyed is formed when
the mm is torn down. Instead of just unmapping the pages when the
address space is being torn down, they are also set aside. Later when
KVM cleans up the VM, a thread is started to clean up the pages from
the list.

This means that the same address space can have memory belonging to
more than one protected guest, although only one will be running, the
others will in fact not even have any CPUs.

Claudio Imbrenda (11):
  KVM: s390: pv: leak the ASCE page when destroy fails
  KVM: s390: pv: properly handle page flags for protected guests
  KVM: s390: pv: handle secure storage violations for protected guests
  KVM: s390: pv: handle secure storage exceptions for normal guests
  KVM: s390: pv: refactor s390_reset_acc
  KVM: s390: pv: usage counter instead of flag
  KVM: s390: pv: add export before import
  KVM: s390: pv: lazy destroy for reboot
  KVM: s390: pv: extend lazy destroy to handle shutdown
  KVM: s390: pv: module parameter to fence lazy destroy
  KVM: s390: pv: add support for UV feature bits

 arch/s390/boot/uv.c                 |   1 +
 arch/s390/include/asm/gmap.h        |   5 +-
 arch/s390/include/asm/mmu.h         |   3 +
 arch/s390/include/asm/mmu_context.h |   2 +
 arch/s390/include/asm/pgtable.h     |  16 +-
 arch/s390/include/asm/uv.h          |  35 ++++-
 arch/s390/kernel/uv.c               | 133 +++++++++++++++-
 arch/s390/kvm/kvm-s390.c            |   6 +-
 arch/s390/kvm/kvm-s390.h            |   2 +-
 arch/s390/kvm/pv.c                  | 230 ++++++++++++++++++++++++++--
 arch/s390/mm/fault.c                |  22 ++-
 arch/s390/mm/gmap.c                 |  86 +++++++----
 12 files changed, 490 insertions(+), 51 deletions(-)
```
