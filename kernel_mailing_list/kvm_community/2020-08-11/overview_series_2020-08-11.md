#### [GIT PULL] virtio: features, fixes
##### From: "Michael S. Tsirkin" <mst@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: "Michael S. Tsirkin" <mst@redhat.com>
X-Patchwork-Id: 11708885
Return-Path: <SRS0=hsEk=BV=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 9E922159A
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 11 Aug 2020 08:56:32 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 75FB220772
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 11 Aug 2020 08:56:32 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="ZfVtKnrQ"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728416AbgHKI41 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 11 Aug 2020 04:56:27 -0400
Received: from us-smtp-delivery-1.mimecast.com ([205.139.110.120]:41616 "EHLO
        us-smtp-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org
        with ESMTP id S1728390AbgHKI4Z (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 11 Aug 2020 04:56:25 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1597136183;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:content-type:content-type;
        bh=d88xcVVVwUczUwSPBmg1oFZLtRXHohyyivhvTCzox5c=;
        b=ZfVtKnrQy2+ll3udE0z7QQEMpTxd+3kCFg6tYlIVwODRNFzv41YlFM1QhKh5LGaKeTlxUr
        ChU1DgfQVncsFdzArq7T2nopNrIvHOZxf29VsqZbEIGe6SvVc+99jW6mqk560hXo6sKGBI
        rDRm1/ar03FyecR5sD8HEzOTafw4hfU=
Received: from mail-wm1-f69.google.com (mail-wm1-f69.google.com
 [209.85.128.69]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-242-V_UW6fNtPv6fYYUKeTOIEQ-1; Tue, 11 Aug 2020 04:56:21 -0400
X-MC-Unique: V_UW6fNtPv6fYYUKeTOIEQ-1
Received: by mail-wm1-f69.google.com with SMTP id h205so621023wmf.0
        for <kvm@vger.kernel.org>; Tue, 11 Aug 2020 01:56:21 -0700 (PDT)
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:date:from:to:cc:subject:message-id:mime-version
         :content-disposition;
        bh=d88xcVVVwUczUwSPBmg1oFZLtRXHohyyivhvTCzox5c=;
        b=DFepOHYPPOh0xwaIfDya2vRXbW64dPsOkiGywHeCG7E0nDYaJ3GeKWK5M1KSk6++zm
         rpknsD53VQATOJmgqR+6RxQ3Wm5fsS4PrGikohxgfXMINQLHmf2sRYbmak5aA/NrVBIi
         6TkP42uQqyW2r5/2BDk0Fdnu/sLsgIcaok0HqOCv2QEEZjuicYvvSKAjAgrBM2jaLt6l
         wZyVqyOM7N4IWIYO48BlDo7Pc2VXNk9irC2EJzErpH6Do8MpbWmhTNb/+yb5AxGj6Tay
         jqLu4AQM2K9GphTh8ZC5QCH/fVS85rRyK9WePFavwjWRhVW+0Jh9L4G202N7XYPPXRmq
         FjdQ==
X-Gm-Message-State: AOAM531VLfpzWSd7Ey3fKBFsISrHUhbnjO/aCiMFnrNcU/eSAvBTr9xT
        oRkbUd2sNhx5wFvKJ1tnBwK8KrYvKbmllosEoIkwgtUvfUkixp1dQ3F3tBV1/VYrSoYymsPPULs
        ayR9da2NFjbqb
X-Received: by 2002:adf:f248:: with SMTP id b8mr30092861wrp.247.1597136180005;
        Tue, 11 Aug 2020 01:56:20 -0700 (PDT)
X-Google-Smtp-Source: 
 ABdhPJytzwO8E3CNR4SmeuTaD5pfM/K8artOAdX7C77z9smbpOM/a84oJwE9y6glNyYTcgPnJ5upKw==
X-Received: by 2002:adf:f248:: with SMTP id b8mr30092826wrp.247.1597136179687;
        Tue, 11 Aug 2020 01:56:19 -0700 (PDT)
Received: from redhat.com (bzq-79-180-0-181.red.bezeqint.net. [79.180.0.181])
        by smtp.gmail.com with ESMTPSA id
 c4sm25337308wrt.41.2020.08.11.01.56.14
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Tue, 11 Aug 2020 01:56:18 -0700 (PDT)
Date: Tue, 11 Aug 2020 04:56:13 -0400
From: "Michael S. Tsirkin" <mst@redhat.com>
To: Linus Torvalds <torvalds@linux-foundation.org>
Cc: kvm@vger.kernel.org, virtualization@lists.linux-foundation.org,
        netdev@vger.kernel.org, linux-kernel@vger.kernel.org,
        alex.dewar@gmx.co.uk, andy.shevchenko@gmail.com, cohuck@redhat.com,
        colin.king@canonical.com, dan.carpenter@oracle.com,
        david@redhat.com, elic@nvidia.com, eli@mellanox.com,
        gustavoars@kernel.org, jasowang@redhat.com, leonro@mellanox.com,
        liao.pingfang@zte.com.cn, lingshan.zhu@intel.com, lkp@intel.com,
        lulu@redhat.com, maorg@mellanox.com, maxg@mellanox.com,
        meirl@mellanox.com, michaelgur@mellanox.com, mst@redhat.com,
        parav@mellanox.com, rong.a.chen@intel.com, saeedm@mellanox.com,
        stable@vger.kernel.org, tariqt@mellanox.com, vgoyal@redhat.com,
        wang.yi59@zte.com.cn, wenan.mao@linux.alibaba.com
Subject: [GIT PULL] virtio: features, fixes
Message-ID: <20200811045613-mutt-send-email-mst@kernel.org>
MIME-Version: 1.0
Content-Disposition: inline
X-Mutt-Fcc: =sent
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

OK, some patches in the series add buggy code which is then fixed by
follow-up patches, but none of the bugs fixed are severe regressions on
common configs (e.g. compiler warnings, lockdep/rt errors, or bugs in
new drivers). So I thought it's more important to preserve the credit
for the fixes.

I had to pull 5 patches from git://git.kernel.org/pub/scm/linux/kernel/git/mellanox/linux mlx5-next
to get the mlx5 things to work, this seems to be how mellanox guys are
always managing things, and they told me they are ok with it.

The following changes since commit bcf876870b95592b52519ed4aafcf9d95999bc9c:

  Linux 5.8 (2020-08-02 14:21:45 -0700)

are available in the Git repository at:

  https://git.kernel.org/pub/scm/linux/kernel/git/mst/vhost.git tags/for_linus

for you to fetch changes up to 8a7c3213db068135e816a6a517157de6443290d6:

  vdpa/mlx5: fix up endian-ness for mtu (2020-08-10 10:38:55 -0400)

----------------------------------------------------------------
virtio: fixes, features

IRQ bypass support for vdpa and IFC
MLX5 vdpa driver
Endian-ness fixes for virtio drivers
Misc other fixes

Signed-off-by: Michael S. Tsirkin <mst@redhat.com>

----------------------------------------------------------------
Alex Dewar (1):
      vdpa/mlx5: Fix uninitialised variable in core/mr.c

Colin Ian King (1):
      vdpa/mlx5: fix memory allocation failure checks

Dan Carpenter (2):
      vdpa/mlx5: Fix pointer math in mlx5_vdpa_get_config()
      vdpa: Fix pointer math bug in vdpasim_get_config()

Eli Cohen (9):
      net/mlx5: Support setting access rights of dma addresses
      net/mlx5: Add VDPA interface type to supported enumerations
      net/mlx5: Add interface changes required for VDPA
      net/vdpa: Use struct for set/get vq state
      vdpa: Modify get_vq_state() to return error code
      vdpa/mlx5: Add hardware descriptive header file
      vdpa/mlx5: Add support library for mlx5 VDPA implementation
      vdpa/mlx5: Add shared memory registration code
      vdpa/mlx5: Add VDPA driver for supported mlx5 devices

Gustavo A. R. Silva (1):
      vhost: Use flex_array_size() helper in copy_from_user()

Jason Wang (6):
      vhost: vdpa: remove per device feature whitelist
      vhost-vdpa: refine ioctl pre-processing
      vhost: generialize backend features setting/getting
      vhost-vdpa: support get/set backend features
      vhost-vdpa: support IOTLB batching hints
      vdpasim: support batch updating

Liao Pingfang (1):
      virtio_pci_modern: Fix the comment of virtio_pci_find_capability()

Mao Wenan (1):
      virtio_ring: Avoid loop when vq is broken in virtqueue_poll

Maor Gottlieb (2):
      net/mlx5: Export resource dump interface
      net/mlx5: Add support in query QP, CQ and MKEY segments

Max Gurtovoy (2):
      vdpasim: protect concurrent access to iommu iotlb
      vdpa: remove hard coded virtq num

Meir Lichtinger (1):
      RDMA/mlx5: ConnectX-7 new capabilities to set relaxed ordering by UMR

Michael Guralnik (2):
      net/mlx5: Enable QP number request when creating IPoIB underlay QP
      net/mlx5: Enable count action for rules with allow action

Michael S. Tsirkin (44):
      virtio: VIRTIO_F_IOMMU_PLATFORM -> VIRTIO_F_ACCESS_PLATFORM
      virtio: virtio_has_iommu_quirk -> virtio_has_dma_quirk
      virtio_balloon: fix sparse warning
      virtio_ring: sparse warning fixup
      virtio: allow __virtioXX, __leXX in config space
      virtio_9p: correct tags for config space fields
      virtio_balloon: correct tags for config space fields
      virtio_blk: correct tags for config space fields
      virtio_console: correct tags for config space fields
      virtio_crypto: correct tags for config space fields
      virtio_fs: correct tags for config space fields
      virtio_gpu: correct tags for config space fields
      virtio_input: correct tags for config space fields
      virtio_iommu: correct tags for config space fields
      virtio_mem: correct tags for config space fields
      virtio_net: correct tags for config space fields
      virtio_pmem: correct tags for config space fields
      virtio_scsi: correct tags for config space fields
      virtio_config: disallow native type fields
      mlxbf-tmfifo: sparse tags for config access
      vdpa: make sure set_features is invoked for legacy
      vhost/vdpa: switch to new helpers
      virtio_vdpa: legacy features handling
      vdpa_sim: fix endian-ness of config space
      virtio_config: cread/write cleanup
      virtio_config: rewrite using _Generic
      virtio_config: disallow native type fields (again)
      virtio_config: LE config space accessors
      virtio_caif: correct tags for config space fields
      virtio_config: add virtio_cread_le_feature
      virtio_balloon: use LE config space accesses
      virtio_input: convert to LE accessors
      virtio_fs: convert to LE accessors
      virtio_crypto: convert to LE accessors
      virtio_pmem: convert to LE accessors
      drm/virtio: convert to LE accessors
      virtio_mem: convert to LE accessors
      virtio-iommu: convert to LE accessors
      virtio_config: drop LE option from config space
      virtio_net: use LE accessors for speed/duplex
      Merge branch 'mlx5-next' of git://git.kernel.org/.../mellanox/linux into HEAD
      virtio_config: fix up warnings on parisc
      vdpa_sim: init iommu lock
      vdpa/mlx5: fix up endian-ness for mtu

Parav Pandit (2):
      net/mlx5: Avoid RDMA file inclusion in core driver
      net/mlx5: Avoid eswitch header inclusion in fs core layer

Tariq Toukan (1):
      net/mlx5: kTLS, Improve TLS params layout structures

Zhu Lingshan (7):
      vhost: introduce vhost_vring_call
      kvm: detect assigned device via irqbypass manager
      vDPA: add get_vq_irq() in vdpa_config_ops
      vhost_vdpa: implement IRQ offloading in vhost_vdpa
      ifcvf: implement vdpa_config_ops.get_vq_irq()
      irqbypass: do not start cons/prod when failed connect
      vDPA: dont change vq irq after DRIVER_OK

 arch/um/drivers/virtio_uml.c                       |    2 +-
 arch/x86/kvm/x86.c                                 |   12 +-
 drivers/crypto/virtio/virtio_crypto_core.c         |   46 +-
 drivers/gpu/drm/virtio/virtgpu_kms.c               |   16 +-
 drivers/gpu/drm/virtio/virtgpu_object.c            |    2 +-
 drivers/gpu/drm/virtio/virtgpu_vq.c                |    4 +-
 drivers/iommu/virtio-iommu.c                       |   34 +-
 drivers/net/ethernet/mellanox/mlx5/core/alloc.c    |   11 +-
 .../ethernet/mellanox/mlx5/core/diag/rsc_dump.c    |    6 +
 .../ethernet/mellanox/mlx5/core/diag/rsc_dump.h    |   33 +-
 drivers/net/ethernet/mellanox/mlx5/core/en/txrx.h  |    2 +-
 .../ethernet/mellanox/mlx5/core/en_accel/ktls.h    |    2 +-
 .../ethernet/mellanox/mlx5/core/en_accel/ktls_tx.c |   14 +-
 .../mellanox/mlx5/core/en_accel/tls_rxtx.c         |    2 +-
 drivers/net/ethernet/mellanox/mlx5/core/eswitch.h  |   10 -
 drivers/net/ethernet/mellanox/mlx5/core/fs_core.c  |    2 +-
 drivers/net/ethernet/mellanox/mlx5/core/fs_core.h  |   10 +
 .../net/ethernet/mellanox/mlx5/core/ipoib/ipoib.c  |    7 +
 drivers/net/ethernet/mellanox/mlx5/core/main.c     |    3 +
 drivers/net/virtio_net.c                           |    9 +-
 drivers/nvdimm/virtio_pmem.c                       |    4 +-
 drivers/platform/mellanox/mlxbf-tmfifo.c           |   13 +-
 drivers/scsi/virtio_scsi.c                         |    4 +-
 drivers/vdpa/Kconfig                               |   19 +
 drivers/vdpa/Makefile                              |    1 +
 drivers/vdpa/ifcvf/ifcvf_base.c                    |    4 +-
 drivers/vdpa/ifcvf/ifcvf_base.h                    |    6 +-
 drivers/vdpa/ifcvf/ifcvf_main.c                    |   31 +-
 drivers/vdpa/mlx5/Makefile                         |    4 +
 drivers/vdpa/mlx5/core/mlx5_vdpa.h                 |   91 +
 drivers/vdpa/mlx5/core/mlx5_vdpa_ifc.h             |  168 ++
 drivers/vdpa/mlx5/core/mr.c                        |  486 +++++
 drivers/vdpa/mlx5/core/resources.c                 |  284 +++
 drivers/vdpa/mlx5/net/main.c                       |   76 +
 drivers/vdpa/mlx5/net/mlx5_vnet.c                  | 1974 ++++++++++++++++++++
 drivers/vdpa/mlx5/net/mlx5_vnet.h                  |   24 +
 drivers/vdpa/vdpa.c                                |    4 +
 drivers/vdpa/vdpa_sim/vdpa_sim.c                   |  124 +-
 drivers/vhost/Kconfig                              |    1 +
 drivers/vhost/net.c                                |   22 +-
 drivers/vhost/vdpa.c                               |  183 +-
 drivers/vhost/vhost.c                              |   39 +-
 drivers/vhost/vhost.h                              |   11 +-
 drivers/virtio/virtio_balloon.c                    |   30 +-
 drivers/virtio/virtio_input.c                      |   32 +-
 drivers/virtio/virtio_mem.c                        |   30 +-
 drivers/virtio/virtio_pci_modern.c                 |    1 +
 drivers/virtio/virtio_ring.c                       |    7 +-
 drivers/virtio/virtio_vdpa.c                       |    9 +-
 fs/fuse/virtio_fs.c                                |    4 +-
 include/linux/mlx5/cq.h                            |    1 -
 include/linux/mlx5/device.h                        |   13 +-
 include/linux/mlx5/driver.h                        |    2 +
 include/linux/mlx5/mlx5_ifc.h                      |  134 +-
 include/linux/mlx5/qp.h                            |    2 +-
 include/linux/mlx5/rsc_dump.h                      |   51 +
 include/linux/vdpa.h                               |   66 +-
 include/linux/virtio_caif.h                        |    6 +-
 include/linux/virtio_config.h                      |  191 +-
 include/linux/virtio_ring.h                        |   19 +-
 include/uapi/linux/vhost.h                         |    2 +
 include/uapi/linux/vhost_types.h                   |   11 +
 include/uapi/linux/virtio_9p.h                     |    4 +-
 include/uapi/linux/virtio_balloon.h                |   10 +-
 include/uapi/linux/virtio_blk.h                    |   26 +-
 include/uapi/linux/virtio_config.h                 |   10 +-
 include/uapi/linux/virtio_console.h                |    8 +-
 include/uapi/linux/virtio_crypto.h                 |   26 +-
 include/uapi/linux/virtio_fs.h                     |    2 +-
 include/uapi/linux/virtio_gpu.h                    |    8 +-
 include/uapi/linux/virtio_input.h                  |   18 +-
 include/uapi/linux/virtio_iommu.h                  |   12 +-
 include/uapi/linux/virtio_mem.h                    |   14 +-
 include/uapi/linux/virtio_net.h                    |    8 +-
 include/uapi/linux/virtio_pmem.h                   |    4 +-
 include/uapi/linux/virtio_scsi.h                   |   20 +-
 tools/virtio/linux/virtio_config.h                 |    6 +-
 virt/lib/irqbypass.c                               |   16 +-
 78 files changed, 4116 insertions(+), 487 deletions(-)
 create mode 100644 drivers/vdpa/mlx5/Makefile
 create mode 100644 drivers/vdpa/mlx5/core/mlx5_vdpa.h
 create mode 100644 drivers/vdpa/mlx5/core/mlx5_vdpa_ifc.h
 create mode 100644 drivers/vdpa/mlx5/core/mr.c
 create mode 100644 drivers/vdpa/mlx5/core/resources.c
 create mode 100644 drivers/vdpa/mlx5/net/main.c
 create mode 100644 drivers/vdpa/mlx5/net/mlx5_vnet.c
 create mode 100644 drivers/vdpa/mlx5/net/mlx5_vnet.h
 create mode 100644 include/linux/mlx5/rsc_dump.h
```
#### [PATCH 1/2] KVM: Pass MMU notifier range flags to kvm_unmap_hva_range()
##### From: Will Deacon <will@kernel.org>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Will Deacon <will@kernel.org>
X-Patchwork-Id: 11709035
Return-Path: <SRS0=hsEk=BV=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 1F0AA618
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 11 Aug 2020 10:27:37 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 02A672078E
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 11 Aug 2020 10:27:37 +0000 (UTC)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple; d=kernel.org;
	s=default; t=1597141657;
	bh=XE668iD9SY5/XC9Cg7O/2rDRshSZB0RRnCkW1VOO3lQ=;
	h=From:To:Cc:Subject:Date:In-Reply-To:References:List-ID:From;
	b=iXihp9g1k3XOCnXvOIZd+gQeDrYvcsoxjgElqwZNf/dWfv4pG3/uSxNyAIpp6150x
	 LtN6k0TeXySwSAOCQSmEkWbxhspmkmQSn7dVJ2smlNku0hYwnWNjUKEBQI2cNm1PXG
	 7vlMrRHVVoy05/2Gw2e3jU6zvYm4A6aEUA82QOyQ=
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728649AbgHKK1g (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 11 Aug 2020 06:27:36 -0400
Received: from mail.kernel.org ([198.145.29.99]:54478 "EHLO mail.kernel.org"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1728390AbgHKK1f (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 11 Aug 2020 06:27:35 -0400
Received: from localhost.localdomain (236.31.169.217.in-addr.arpa
 [217.169.31.236])
        (using TLSv1.2 with cipher ECDHE-RSA-AES128-GCM-SHA256 (128/128 bits))
        (No client certificate requested)
        by mail.kernel.org (Postfix) with ESMTPSA id EBDA02076C;
        Tue, 11 Aug 2020 10:27:31 +0000 (UTC)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple; d=kernel.org;
        s=default; t=1597141653;
        bh=XE668iD9SY5/XC9Cg7O/2rDRshSZB0RRnCkW1VOO3lQ=;
        h=From:To:Cc:Subject:Date:In-Reply-To:References:From;
        b=oHO37VV8kzVVBguWg3LiimrpRMAN6X4DdPsl5c5W2usH8CIxFIqenaE/rRcFPs1nY
         lYCVFen5VOzTrFFjUjplWadFNPPPZ+xSF1ycvG7HdCd7CuoOBs+EXhklt3rNySyg1/
         sWFEUNs8G6ShTHTd17qf588YzfAEEblSdjdg8xb8=
From: Will Deacon <will@kernel.org>
To: kvmarm@lists.cs.columbia.edu, linux-kernel@vger.kernel.org,
        kvm@vger.kernel.org
Cc: Will Deacon <will@kernel.org>, Marc Zyngier <maz@kernel.org>,
        Suzuki K Poulose <suzuki.poulose@arm.com>,
        James Morse <james.morse@arm.com>,
        Thomas Bogendoerfer <tsbogend@alpha.franken.de>,
        Paul Mackerras <paulus@ozlabs.org>,
        Paolo Bonzini <pbonzini@redhat.com>,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        stable@vger.kernel.org
Subject: [PATCH 1/2] KVM: Pass MMU notifier range flags to
 kvm_unmap_hva_range()
Date: Tue, 11 Aug 2020 11:27:24 +0100
Message-Id: <20200811102725.7121-2-will@kernel.org>
X-Mailer: git-send-email 2.20.1
In-Reply-To: <20200811102725.7121-1-will@kernel.org>
References: <20200811102725.7121-1-will@kernel.org>
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The 'flags' field of 'struct mmu_notifier_range' is used to indicate
whether invalidate_range_{start,end}() are permitted to block. In the
case of kvm_mmu_notifier_invalidate_range_start(), this field is not
forwarded on to the architecture-specific implementation of
kvm_unmap_hva_range() and therefore the backend cannot sensibly decide
whether or not to block.

Add an extra 'flags' parameter to kvm_unmap_hva_range() so that
architectures are aware as to whether or not they are permitted to block.

Cc: <stable@vger.kernel.org>
Cc: Marc Zyngier <maz@kernel.org>
Cc: Suzuki K Poulose <suzuki.poulose@arm.com>
Cc: James Morse <james.morse@arm.com>
Signed-off-by: Will Deacon <will@kernel.org>
---
 arch/arm64/include/asm/kvm_host.h   | 2 +-
 arch/arm64/kvm/mmu.c                | 2 +-
 arch/mips/include/asm/kvm_host.h    | 2 +-
 arch/mips/kvm/mmu.c                 | 3 ++-
 arch/powerpc/include/asm/kvm_host.h | 3 ++-
 arch/powerpc/kvm/book3s.c           | 3 ++-
 arch/powerpc/kvm/e500_mmu_host.c    | 3 ++-
 arch/x86/include/asm/kvm_host.h     | 3 ++-
 arch/x86/kvm/mmu/mmu.c              | 3 ++-
 virt/kvm/kvm_main.c                 | 3 ++-
 10 files changed, 17 insertions(+), 10 deletions(-)

```
#### [PATCH] powerpc: kvm: Increase HDEC threshold to enter guest
##### From: David Gibson <david@gibson.dropbear.id.au>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 8bit
X-Patchwork-Submitter: David Gibson <david@gibson.dropbear.id.au>
X-Patchwork-Id: 11708527
Return-Path: <SRS0=hsEk=BV=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id D60C513B6
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 11 Aug 2020 04:19:29 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id B99E8206DA
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 11 Aug 2020 04:19:29 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=gibson.dropbear.id.au
 header.i=@gibson.dropbear.id.au header.b="WH64YnKM"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726317AbgHKETU (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 11 Aug 2020 00:19:20 -0400
Received: from bilbo.ozlabs.org ([203.11.71.1]:33701 "EHLO ozlabs.org"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1725837AbgHKETU (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 11 Aug 2020 00:19:20 -0400
Received: by ozlabs.org (Postfix, from userid 1007)
        id 4BQfjf3pLbz9sTS; Tue, 11 Aug 2020 14:19:18 +1000 (AEST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple;
        d=gibson.dropbear.id.au; s=201602; t=1597119558;
        bh=2NZiS/B9GDmUuTZl+DIdhj2fNIhZ6RGfvaIFICHqFSM=;
        h=From:To:Cc:Subject:Date:From;
        b=WH64YnKMptRO4Eox2YloZbysBg7ADBHWYMCYZMpjNkFkZ7mEP/KxNx5G3tL1CKXQu
         uhBEtjcHOmb30U2vTPlkz9eIoTSffzJN8sLu7PUF5NjsEsY4f3vQru3UoQGzwgIqFU
         0ONoy5meOvv+eWlw4dGBg3SCcKueEgHNmY1/1gNM=
From: David Gibson <david@gibson.dropbear.id.au>
To: paulus@samba.org, mpe@ellerman.id.au
Cc: linuxppc-dev@lists.ozlabs.org, linux-kernel@vger.kernel.org,
        kvm@vger.kernel.org, kvm-ppc@vger.kernel.org,
        David Gibson <david@gibson.dropbear.id.au>
Subject: [PATCH] powerpc: kvm: Increase HDEC threshold to enter guest
Date: Tue, 11 Aug 2020 14:08:34 +1000
Message-Id: <20200811040834.45930-1-david@gibson.dropbear.id.au>
X-Mailer: git-send-email 2.26.2
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Before entering a guest, we need to set the HDEC to pull us out again
when the guest's time is up.  This needs some care, though, because the
HDEC is edge triggered, which means that if it expires before entering the
guest, the interrupt will be lost, meaning we stay in the guest
indefinitely (in practice, until the the hard lockup detector pulls us out
with an NMI).

For the POWER9, independent threads mode specific path, we attempt to
prevent that, by testing time has already expired before setting the HDEC
in kvmhv_load_regs_and_go().  However, that doesn't account for the case
where the timer expires between that test and the actual guest entry.
Preliminary instrumentation suggests that can take as long as 1.5µs under
certain load conditions, and simply checking the HDEC value we're going to
load is positive isn't enough to guarantee that leeway.

That test here is sometimes masked by a test in kvmhv_p9_guest_entry(), its
caller.  That checks that the remaining time is at 1µs.  However as noted
above that doesn't appear to be sufficient in all circumstances even
from the point HDEC is set, let alone this earlier point.

Therefore, increase the threshold we check for in both locations to 4µs
(2048 timebase ticks).  This is a pretty crude approach, but it addresses
a real problem where guest load can trigger a host hard lockup.

We're hoping to refine this in future by gathering more data on exactly
how long these paths can take, and possibly by moving the check closer to
the actual guest entry point to reduce the variance.  Getting the details
for that might take some time however.

NOTE: For reasons I haven't yet tracked down yet, I haven't actually
managed to reproduce this on current upstream.  I have reproduced it on
RHEL kernels without obvious differences in this area.  I'm still trying
to determine what the cause of that difference is, but I think it's worth
applying this change as a precaution in the interim.

Signed-off-by: David Gibson <david@gibson.dropbear.id.au>
---
 arch/powerpc/kvm/book3s_hv.c | 4 ++--
 1 file changed, 2 insertions(+), 2 deletions(-)

```
#### [PATCH RESEND] KVM: MIPS/VZ: Fix build error caused by 'kvm_run' cleanup
##### From: Xingxing Su <suxingxing@loongson.cn>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 8bit
X-Patchwork-Submitter: Xingxing Su <suxingxing@loongson.cn>
X-Patchwork-Id: 11708913
Return-Path: <SRS0=hsEk=BV=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id B660513A4
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 11 Aug 2020 09:31:49 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id A5BCC20774
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 11 Aug 2020 09:31:49 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728471AbgHKJbp (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 11 Aug 2020 05:31:45 -0400
Received: from mail.loongson.cn ([114.242.206.163]:39742 "EHLO loongson.cn"
        rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org with ESMTP
        id S1728397AbgHKJbo (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 11 Aug 2020 05:31:44 -0400
Received: from bogon.localdomain (unknown [113.200.148.30])
        by mail.loongson.cn (Coremail) with SMTP id
 AQAAf9DxT9x6ZTJfGGAHAA--.60S2;
        Tue, 11 Aug 2020 17:31:38 +0800 (CST)
From: Xingxing Su <suxingxing@loongson.cn>
To: Huacai Chen <chenhc@lemote.com>,
        Thomas Bogendoerfer <tsbogend@alpha.franken.de>,
        Aleksandar Markovic <aleksandar.qemu.devel@gmail.com>,
        Paolo Bonzini <pbonzini@redhat.com>
Cc: kvm@vger.kernel.org, linux-mips@vger.kernel.org,
        linux-kernel@vger.kernel.org
Subject: [PATCH RESEND] KVM: MIPS/VZ: Fix build error caused by 'kvm_run'
 cleanup
Date: Tue, 11 Aug 2020 17:31:37 +0800
Message-Id: <1597138297-2105-1-git-send-email-suxingxing@loongson.cn>
X-Mailer: git-send-email 2.1.0
MIME-Version: 1.0
X-CM-TRANSID: AQAAf9DxT9x6ZTJfGGAHAA--.60S2
X-Coremail-Antispam: 1UD129KBjDUn29KB7ZKAUJUUUUU529EdanIXcx71UUUUU7v73
        VFW2AGmfu7bjvjm3AaLaJ3UjIYCTnIWjp_UUUYl7k0a2IF6F4UM7kC6x804xWl14x267AK
        xVW8JVW5JwAFc2x0x2IEx4CE42xK8VAvwI8IcIk0rVWrJVCq3wAFIxvE14AKwVWUJVWUGw
        A2ocxC64kIII0Yj41l84x0c7CEw4AK67xGY2AK021l84ACjcxK6xIIjxv20xvE14v26r4j
        6ryUM28EF7xvwVC0I7IYx2IY6xkF7I0E14v26r4j6F4UM28EF7xvwVC2z280aVAFwI0_Cr
        1j6rxdM28EF7xvwVC2z280aVCY1x0267AKxVW0oVCq3wAS0I0E0xvYzxvE52x082IY62kv
        0487M2AExVAIFx02aVAFz4v204v7Mc02F40EFcxC0VAKzVAqx4xG6I80ewAv7VC0I7IYx2
        IY67AKxVWUGVWUXwAv7VC2z280aVAFwI0_Cr0_Gr1UMcvjeVCFs4IE7xkEbVWUJVW8JwAC
        jcxG0xvY0x0EwIxGrwAKzVC20s0267AEwI8IwI0ExsIj0wCY02Avz4vE14v_GFWl42xK82
        IYc2Ij64vIr41l4I8I3I0E4IkC6x0Yz7v_Jr0_Gr1lx2IqxVAqx4xG67AKxVWUJVWUGwC2
        0s026x8GjcxK67AKxVWUJVWUGwC2zVAF1VAY17CE14v26r126r1DMIIYrxkI7VAKI48JMI
        IF0xvE2Ix0cI8IcVAFwI0_Jr0_JF4lIxAIcVC0I7IYx2IY6xkF7I0E14v26r1j6r4UMIIF
        0xvE42xK8VAvwI8IcIk0rVWrJr0_WFyUJwCI42IY6I8E87Iv67AKxVWUJVW8JwCI42IY6I
        8E87Iv6xkF7I0E14v26r4j6r4UJbIYCTnIWIevJa73UjIFyTuYvjxUzMa0DUUUU
X-CM-SenderInfo: pvx0x0xj0l0wo6or00hjvr0hdfq/1tbiAQAFC13QvMLodgACsg
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Commit c34b26b98caca48ec9ee9 ("KVM: MIPS: clean up redundant 'kvm_run'
parameters") remove the 'kvm_run' parameter in kvm_vz_gpsi_lwc2.

The following build error:

arch/mips/kvm/vz.c: In function ‘kvm_trap_vz_handle_gpsi’:
arch/mips/kvm/vz.c:1243:43: error: ‘run’ undeclared (first use in this function)
   er = kvm_vz_gpsi_lwc2(inst, opc, cause, run, vcpu);
                                           ^~~
arch/mips/kvm/vz.c:1243:43: note: each undeclared identifier is reported only 
once for each function it appears in
scripts/Makefile.build:283: recipe for target 'arch/mips/kvm/vz.o' failed
make[2]: *** [arch/mips/kvm/vz.o] Error 1
scripts/Makefile.build:500: recipe for target 'arch/mips/kvm' failed
make[1]: *** [arch/mips/kvm] Error 2
Makefile:1785: recipe for target 'arch/mips' failed
make: *** [arch/mips] Error 2

Signed-off-by: Xingxing Su <suxingxing@loongson.cn>
---
 +cc Paolo Bonzini <pbonzini@redhat.com> and kvm@vger.kernel.org.

 arch/mips/kvm/vz.c | 3 +--
 1 file changed, 1 insertion(+), 2 deletions(-)

```
#### [PATCH v2] kvm-unit-tests: nSVM: Test combination of EFER.LME, CR0.PG and CR4.PAE on VMRUN of nested guests
##### From: Krish Sadhukhan <krish.sadhukhan@oracle.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Krish Sadhukhan <krish.sadhukhan@oracle.com>
X-Patchwork-Id: 11709767
Return-Path: <SRS0=hsEk=BV=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id B2833913
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 11 Aug 2020 22:26:07 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 9A42720771
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 11 Aug 2020 22:26:07 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=oracle.com header.i=@oracle.com
 header.b="x2sATOwr"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726179AbgHKW0G (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 11 Aug 2020 18:26:06 -0400
Received: from aserp2120.oracle.com ([141.146.126.78]:43270 "EHLO
        aserp2120.oracle.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726164AbgHKW0G (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 11 Aug 2020 18:26:06 -0400
Received: from pps.filterd (aserp2120.oracle.com [127.0.0.1])
        by aserp2120.oracle.com (8.16.0.42/8.16.0.42) with SMTP id
 07BMMoDa029220;
        Tue, 11 Aug 2020 22:26:04 GMT
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=oracle.com;
 h=from : to : cc :
 subject : date : message-id : in-reply-to : references; s=corp-2020-01-29;
 bh=j+QIbryDM816c8or5qAtzjNLcN/qyAOC1CKju0VyeVk=;
 b=x2sATOwrEINLyXiQy20+MPJmyGS7Amnk2tbzr5kLPBiL+HTiSpnLILaysBbfiFUpILFq
 ELI0vBByZ1pyH6fUg+J/ZEHOvh4yRJqXw5cuoS59N9ofOtTidIdSoOd+uQlR0JcFpJDw
 a5NwMlJh2O1EUGc/rXIazMAhFYieJavuX9YOLjsdGMqhyxeWG/IduJZ3a74Pp96wkyKJ
 pVlAH6wLcDLGeK7S7mpmMZRlWFfwO0jmJdcSbwC2XYKoTXbonfwo96duWObGIm5ivF2h
 ALWk3USLI6aJ2wLz2VvOwdrsKs2LxwGyHou9lzqt7TXNCFQLBMElTu9hp5h08ZvnI0PZ zQ==
Received: from aserp3020.oracle.com (aserp3020.oracle.com [141.146.126.70])
        by aserp2120.oracle.com with ESMTP id 32sm0mqf9w-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=FAIL);
        Tue, 11 Aug 2020 22:26:04 +0000
Received: from pps.filterd (aserp3020.oracle.com [127.0.0.1])
        by aserp3020.oracle.com (8.16.0.42/8.16.0.42) with SMTP id
 07BMNMZu094639;
        Tue, 11 Aug 2020 22:24:03 GMT
Received: from aserv0122.oracle.com (aserv0122.oracle.com [141.146.126.236])
        by aserp3020.oracle.com with ESMTP id 32t5y54rpx-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Tue, 11 Aug 2020 22:24:03 +0000
Received: from abhmp0012.oracle.com (abhmp0012.oracle.com [141.146.116.18])
        by aserv0122.oracle.com (8.14.4/8.14.4) with ESMTP id 07BMO3GU027586;
        Tue, 11 Aug 2020 22:24:03 GMT
Received: from nsvm-sadhukhan-1.osdevelopmeniad.oraclevcn.com
 (/100.100.230.216)
        by default (Oracle Beehive Gateway v4.0)
        with ESMTP ; Tue, 11 Aug 2020 22:24:03 +0000
From: Krish Sadhukhan <krish.sadhukhan@oracle.com>
To: kvm@vger.kernel.org
Cc: pbonzini@redhat.com
Subject: [PATCH v2] kvm-unit-tests: nSVM: Test combination of EFER.LME,
 CR0.PG and CR4.PAE on VMRUN of nested guests
Date: Tue, 11 Aug 2020 22:23:53 +0000
Message-Id: <20200811222353.41414-2-krish.sadhukhan@oracle.com>
X-Mailer: git-send-email 2.18.4
In-Reply-To: <20200811222353.41414-1-krish.sadhukhan@oracle.com>
References: <20200811222353.41414-1-krish.sadhukhan@oracle.com>
X-Proofpoint-Virus-Version: vendor=nai engine=6000 definitions=9710
 signatures=668679
X-Proofpoint-Spam-Details: rule=notspam policy=default score=0 spamscore=0
 malwarescore=0
 suspectscore=15 mlxscore=0 adultscore=0 bulkscore=0 phishscore=0
 mlxlogscore=948 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.12.0-2006250000 definitions=main-2008110161
X-Proofpoint-Virus-Version: vendor=nai engine=6000 definitions=9710
 signatures=668679
X-Proofpoint-Spam-Details: rule=notspam policy=default score=0 phishscore=0
 clxscore=1015
 suspectscore=15 mlxlogscore=930 priorityscore=1501 adultscore=0
 impostorscore=0 spamscore=0 bulkscore=0 mlxscore=0 lowpriorityscore=0
 malwarescore=0 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.12.0-2006250000 definitions=main-2008110161
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

According to section "Canonicalization and Consistency Checks" in APM vol. 2
the following guest state combinations are illegal:

	* EFER.LME and CR0.PG are both set and CR4.PAE is zero.
	* EFER.LME and CR0.PG are both non-zero and CR0.PE is zero.
	* EFER.LME, CR0.PG, CR4.PAE, CS.L, and CS.D are all non-zero

Signed-off-by: Krish Sadhukhan <krish.sadhukhan@oracle.com>
---
 x86/svm_tests.c | 45 +++++++++++++++++++++++++++++++++++++++++++++
 1 file changed, 45 insertions(+)

```
