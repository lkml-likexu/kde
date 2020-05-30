

#### [RFC 00/12] Audio DSP VirtIO and vhost drivers
##### From: Guennadi Liakhovetski <guennadi.liakhovetski@linux.intel.com>

```c
From patchwork Fri May 29 07:37:10 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Guennadi Liakhovetski
 <guennadi.liakhovetski@linux.intel.com>
X-Patchwork-Id: 11577889
Return-Path: <SRS0=rOkw=7L=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 7523714C0
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 29 May 2020 07:37:28 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 6698420897
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 29 May 2020 07:37:28 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726805AbgE2Hh1 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 29 May 2020 03:37:27 -0400
Received: from mga07.intel.com ([134.134.136.100]:50710 "EHLO mga07.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726774AbgE2Hh1 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 29 May 2020 03:37:27 -0400
IronPort-SDR: 
 8XHlXtBxMELKDHXEYnoKaocDE2hOjoMxfSkaxEixGNJpEusGJ7PmCg3Q9B9SDr/b8CDy/aUDIB
 fIpTfQgBuA0g==
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from orsmga004.jf.intel.com ([10.7.209.38])
  by orsmga105.jf.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 29 May 2020 00:37:26 -0700
IronPort-SDR: 
 HcCYIZYD/Z4CmmflZf6FQUC70P+hV24/JFkV51FSThkviFTiLcVQ44QuNUxtvENiDwXZD0muGY
 s8tcJ0WmV2/g==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.73,447,1583222400";
   d="scan'208";a="414890362"
Received: from gliakhov-mobl2.ger.corp.intel.com (HELO
 ubuntu.ger.corp.intel.com) ([10.252.45.157])
  by orsmga004.jf.intel.com with ESMTP; 29 May 2020 00:37:23 -0700
From: Guennadi Liakhovetski <guennadi.liakhovetski@linux.intel.com>
To: kvm@vger.kernel.org
Cc: linux-remoteproc@vger.kernel.org,
        virtualization@lists.linux-foundation.org,
        sound-open-firmware@alsa-project.org,
        Pierre-Louis Bossart <pierre-louis.bossart@linux.intel.com>,
        Liam Girdwood <liam.r.girdwood@linux.intel.com>,
        "Michael S. Tsirkin" <mst@redhat.com>,
        Jason Wang <jasowang@redhat.com>,
        Ohad Ben-Cohen <ohad@wizery.com>,
        Bjorn Andersson <bjorn.andersson@linaro.org>,
        Mathieu Poirier <mathieu.poirier@linaro.org>
Subject: [RFC 00/12] Audio DSP VirtIO and vhost drivers
Date: Fri, 29 May 2020 09:37:10 +0200
Message-Id: <20200529073722.8184-1-guennadi.liakhovetski@linux.intel.com>
X-Mailer: git-send-email 2.20.1
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This patch set is a follow up to "Add a vhost RPMsg API" [1], it is
marked as an RFC because firstly it depends on the RPMsg API series
and secondly it is currently being reviewed on ALSA and SOF mailing
lists, but any early comments from virtualisation developers would be
highly appreciated too!

Thanks
Guennadi

[1] https://mailman.alsa-project.org/pipermail/sound-open-firmware/2020-May/003879.html

Guennadi Liakhovetski (12):
  ASoC: add function parameters to enable forced path pruning
  ASoC: SOF: extract firmware-related operation into a function
  ASoC: SOF: support IPC with immediate response
  ASoC: SOF: add a power status IPC
  ASoC: SOF: add two helper lookup functions
  ASoC: SOF: add an RPMsg VirtIO DSP driver
  ASoC: SOF: use a macro instead of a hard-coded value
  ASoC: SOF: add a vhost driver: sound part
  ASoC: SOF: VirtIO: free guest pipelines upon termination
  vhost: add an SOF Audio DSP driver
  rpmsg: increase buffer size and reduce buffer number
  rpmsg: add a device ID to also bind to the ADSP device

 drivers/rpmsg/virtio_rpmsg_bus.c |    1 +
 drivers/vhost/Kconfig            |   10 +
 drivers/vhost/Makefile           |    3 +
 drivers/vhost/adsp.c             |  618 +++++++++++++++++++
 include/linux/virtio_rpmsg.h     |    4 +-
 include/sound/soc-dpcm.h         |   28 +-
 include/sound/soc-topology.h     |    3 +
 include/sound/sof.h              |    4 +
 include/sound/sof/header.h       |    3 +
 include/sound/sof/rpmsg.h        |  196 ++++++
 include/sound/sof/topology.h     |    9 +-
 include/uapi/linux/vhost.h       |    5 +
 include/uapi/linux/vhost_types.h |    7 +
 include/uapi/linux/virtio_ids.h  |    1 +
 sound/soc/soc-compress.c         |    2 +-
 sound/soc/soc-dapm.c             |    8 +-
 sound/soc/soc-pcm.c              |   98 ++-
 sound/soc/sof/Kconfig            |    7 +
 sound/soc/sof/Makefile           |    2 +
 sound/soc/sof/core.c             |  114 ++--
 sound/soc/sof/ipc.c              |   34 +-
 sound/soc/sof/loader.c           |    4 +
 sound/soc/sof/ops.h              |   10 +-
 sound/soc/sof/pcm.c              |   13 +-
 sound/soc/sof/pm.c               |    6 +-
 sound/soc/sof/rpmsg-vfe.c        |  881 ++++++++++++++++++++++++++
 sound/soc/sof/sof-audio.c        |   33 +
 sound/soc/sof/sof-audio.h        |   21 +
 sound/soc/sof/sof-priv.h         |   48 ++
 sound/soc/sof/topology.c         |   71 ++-
 sound/soc/sof/vhost-vbe.c        | 1258 ++++++++++++++++++++++++++++++++++++++
 31 files changed, 3391 insertions(+), 111 deletions(-)
 create mode 100644 drivers/vhost/adsp.c
 create mode 100644 include/sound/sof/rpmsg.h
 create mode 100644 sound/soc/sof/rpmsg-vfe.c
 create mode 100644 sound/soc/sof/vhost-vbe.c
```
#### [PATCH 0/6] vDPA: doorbell mapping
##### From: Jason Wang <jasowang@redhat.com>

```c
From patchwork Fri May 29 08:02:57 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Jason Wang <jasowang@redhat.com>
X-Patchwork-Id: 11578059
Return-Path: <SRS0=rOkw=7L=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id A3BF592A
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 29 May 2020 08:03:29 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 8AC9A2145D
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 29 May 2020 08:03:29 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="NXGc9dxk"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1725993AbgE2IDY (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 29 May 2020 04:03:24 -0400
Received: from us-smtp-1.mimecast.com ([205.139.110.61]:44585 "EHLO
        us-smtp-delivery-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S1725710AbgE2IDW (ORCPT
        <rfc822;kvm@vger.kernel.org>); Fri, 29 May 2020 04:03:22 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1590739401;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=3sCGk2CMdXKSPjF97sMoZKCNplEGrPAt2s8qgubR3U8=;
        b=NXGc9dxktScpRFql32ZoSC/MK5TEiok6xcFFT2hlT3RpxmqN5sYjQTz/Q5gZgeMbuktDvB
        43UmJffJRncZaouHRYhgTL3SDV87crq3ZlVEXjW1MU+PcguwNC0oLdkbAVUmpO/Dx3JZBl
        tmKitkzvDurn+Dx7Wy4a6sF+lT0kufs=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-36-vz3bxBC7PT6Fd61srtV9jg-1; Fri, 29 May 2020 04:03:17 -0400
X-MC-Unique: vz3bxBC7PT6Fd61srtV9jg-1
Received: from smtp.corp.redhat.com (int-mx03.intmail.prod.int.phx2.redhat.com
 [10.5.11.13])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 6B0801855A14;
        Fri, 29 May 2020 08:03:15 +0000 (UTC)
Received: from jason-ThinkPad-X1-Carbon-6th.redhat.com
 (ovpn-13-231.pek2.redhat.com [10.72.13.231])
        by smtp.corp.redhat.com (Postfix) with ESMTP id DCEA499DE6;
        Fri, 29 May 2020 08:03:06 +0000 (UTC)
From: Jason Wang <jasowang@redhat.com>
To: mst@redhat.com, jasowang@redhat.com
Cc: kvm@vger.kernel.org, virtualization@lists.linux-foundation.org,
        netdev@vger.kernel.org, linux-kernel@vger.kernel.org,
        rob.miller@broadcom.com, lingshan.zhu@intel.com,
        eperezma@redhat.com, lulu@redhat.com, shahafs@mellanox.com,
        hanand@xilinx.com, mhabets@solarflare.com, gdawar@xilinx.com,
        saugatm@xilinx.com, vmireyno@marvell.com,
        zhangweining@ruijie.com.cn, eli@mellanox.com
Subject: [PATCH 0/6] vDPA: doorbell mapping
Date: Fri, 29 May 2020 16:02:57 +0800
Message-Id: <20200529080303.15449-1-jasowang@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.13
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Hi all:

This series introduce basic functionality of doorbell mapping support
for vhost-vDPA. Userspace program may use mmap() to map a the doorbell
of a specific virtqueue into its address space. This is help to reudce
the syscall or vmexit overhead.

A new vdpa_config_ops was introduced to report the location of the
doorbell, vhost_vdpa may then choose to map the doorbell when:

- The doorbell register is localted at page boundary
- The doorbell register does not share page with non doorbell
  registers.

With these two requriements, doorbells layout could be modelled more
easily from guest (e.g Qemu's page-per-vq model) and it would be more
safe to avoid exposing other registers to userspace directly.

IFCVF was reported to support this feature but unfortuantely the one I
used does not meet those requirements. So a new virtio-pci driver for
vDPA bus is introduced, and I verify this with page-per-vq=on with a
userspace vhost-vdpa driver in guest.

Please review.

Thanks

Jason Wang (6):
  vhost: allow device that does not depend on vhost worker
  vhost: use mmgrab() instead of mmget() for non worker device
  vdpa: introduce get_vq_notification method
  vhost_vdpa: support doorbell mapping via mmap
  vdpa: introduce virtio pci driver
  vdpa: vp_vdpa: report doorbell location

 drivers/vdpa/Kconfig           |   6 +
 drivers/vdpa/Makefile          |   1 +
 drivers/vdpa/vp_vdpa/Makefile  |   2 +
 drivers/vdpa/vp_vdpa/vp_vdpa.c | 604 +++++++++++++++++++++++++++++++++
 drivers/vhost/net.c            |   2 +-
 drivers/vhost/scsi.c           |   2 +-
 drivers/vhost/vdpa.c           |  61 +++-
 drivers/vhost/vhost.c          |  80 +++--
 drivers/vhost/vhost.h          |   2 +
 drivers/vhost/vsock.c          |   2 +-
 include/linux/vdpa.h           |  16 +
 11 files changed, 753 insertions(+), 25 deletions(-)
 create mode 100644 drivers/vdpa/vp_vdpa/Makefile
 create mode 100644 drivers/vdpa/vp_vdpa/vp_vdpa.c
```
#### [PATCH 0/6] Refactor handling flow of SET_CPUID*
##### From: Xiaoyao Li <xiaoyao.li@intel.com>

```c
From patchwork Fri May 29 08:55:39 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Xiaoyao Li <xiaoyao.li@intel.com>
X-Patchwork-Id: 11578189
Return-Path: <SRS0=rOkw=7L=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 4434D912
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 29 May 2020 08:56:22 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 2D1CE20776
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 29 May 2020 08:56:22 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726735AbgE2Izv (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 29 May 2020 04:55:51 -0400
Received: from mga02.intel.com ([134.134.136.20]:46106 "EHLO mga02.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1725306AbgE2Izv (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 29 May 2020 04:55:51 -0400
IronPort-SDR: 
 8ex6SwceJnB4TZAx47LIO3i7So8Ew13I3c4EPKDOHuRfoiDV2fe5ZBejuVqhAYnskElO/3nv1G
 vXYHLawXBtPA==
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from fmsmga003.fm.intel.com ([10.253.24.29])
  by orsmga101.jf.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 29 May 2020 01:55:49 -0700
IronPort-SDR: 
 Ul+ulAZFCXjFc9vftd+oM/y7uubCSqC0boFt6Dw0DI5xn9ovGP/gPLoIO7WZSRmYp1K1M7EiUS
 zmAvp/1lpnzA==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.73,448,1583222400";
   d="scan'208";a="311188287"
Received: from lxy-dell.sh.intel.com ([10.239.159.21])
  by FMSMGA003.fm.intel.com with ESMTP; 29 May 2020 01:55:47 -0700
From: Xiaoyao Li <xiaoyao.li@intel.com>
To: Paolo Bonzini <pbonzini@redhat.com>,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        kvm@vger.kernel.org
Cc: Vitaly Kuznetsov <vkuznets@redhat.com>,
        Jim Mattson <jmattson@google.com>,
        linux-kernel@vger.kernel.org, Xiaoyao Li <xiaoyao.li@intel.com>
Subject: [PATCH 0/6] Refactor handling flow of SET_CPUID*
Date: Fri, 29 May 2020 16:55:39 +0800
Message-Id: <20200529085545.29242-1-xiaoyao.li@intel.com>
X-Mailer: git-send-email 2.18.2
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This serial is the extended version of
https://lkml.kernel.org/r/20200528151927.14346-1-xiaoyao.li@intel.com

First two patches are bug fixing, and the other aim to refactor the flow
of SET_CPUID* as:
1. cpuid check: check if userspace provides legal CPUID settings;

2. cpuid update: Update some special CPUID bits based on current vcpu
                 state, e.g., OSXSAVE, OSPKE, ...

3. update KVM state: Update KVM states based on the final CPUID
                     settings. 

Xiaoyao Li (6):
  KVM: X86: Reset vcpu->arch.cpuid_nent to 0 if SET_CPUID fails
  KVM: X86: Go on updating other CPUID leaves when leaf 1 is absent
  KVM: X86: Introduce kvm_check_cpuid()
  KVM: X86: Split kvm_update_cpuid()
  KVM: X86: Move kvm_x86_ops.cpuid_update() into
    kvm_update_state_based_on_cpuid()
  KVM: X86: Move kvm_apic_set_version() to
    kvm_update_state_based_on_cpuid()

 arch/x86/kvm/cpuid.c | 107 +++++++++++++++++++++++++++----------------
 arch/x86/kvm/cpuid.h |   3 +-
 arch/x86/kvm/x86.c   |   1 +
 3 files changed, 70 insertions(+), 41 deletions(-)
```
#### [PATCH v12 0/6] x86/kvm/hyper-v: add support for synthetic
##### From: Jon Doron <arilou@gmail.com>

```c
From patchwork Fri May 29 13:45:37 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Jon Doron <arilou@gmail.com>
X-Patchwork-Id: 11578729
Return-Path: <SRS0=rOkw=7L=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 808C7912
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 29 May 2020 13:45:59 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 682E420C09
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 29 May 2020 13:45:59 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=gmail.com header.i=@gmail.com
 header.b="LVrxuwSZ"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726943AbgE2Np6 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 29 May 2020 09:45:58 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:33658 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726476AbgE2Np6 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 29 May 2020 09:45:58 -0400
Received: from mail-wm1-x342.google.com (mail-wm1-x342.google.com
 [IPv6:2a00:1450:4864:20::342])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id BA10EC03E969;
        Fri, 29 May 2020 06:45:57 -0700 (PDT)
Received: by mail-wm1-x342.google.com with SMTP id f185so3626352wmf.3;
        Fri, 29 May 2020 06:45:57 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=from:to:cc:subject:date:message-id:mime-version
         :content-transfer-encoding;
        bh=Lt8GDMAcJKU5ya03CSoRbKBcFkXL1yVXIOxpta4MSb8=;
        b=LVrxuwSZmt9IGUEYm/FhDtReg7fS7VlQC1m48P9ftkfwz0YB9ZSmw8NubX768fo6ZF
         x94Dr4f9aTQzWsmxefJKzeL2GKHe0EAgxMkaqNJyyGxyMHNJGaV7NF+Su1IGtOPSAdrI
         E95tQ7LdV7Ox+34FLaq1sxvFCsHxUVkTGdnJEwO4E5sLwEFmWO8WqnXn4IviY7ex0UpA
         +62FzQzuHlQyEnWn37I6PtnIqORtiPDHvHH+jbE9QqW1fvzIQOTvFzixN+lsWQobwRTm
         sW5iAYARcz8TsD1gpObS255gnkrnRHGhJzJKwyJQvSUeLkqoQavkdPENAWpNTDKKV8Qe
         AGDg==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:mime-version
         :content-transfer-encoding;
        bh=Lt8GDMAcJKU5ya03CSoRbKBcFkXL1yVXIOxpta4MSb8=;
        b=b/3fh9l/fP4X9kJtncebsBj7NFLPQaFQXEKb0z50+gFtTnGXZd2vOzcXL2H4Th3pYw
         IR2L/exSJaDZv1RTJ0nFGSyo7jsoOjIXF9vCOyVkYdDUHXEpDPU+XqE7ReI5ddR/2LUY
         ZV9gJH3CvNe3b3/dXAfFEZmjV/X6nwAZ1C5pkN2Ra3JzkouSG6PDXpuaPiERW9lxifj8
         Oc9eM4w+eDJix97AMFLPYc+zIv5RxT3jpEyj1nMtk+TJDJ0b4I/IpbK9lo1bknUnILJK
         Mscsm6CN3m4QTZeHCdgWKIvvWKxfDKhk+y7VGUEjmuMMR99BtgMz0Q87JUkN0lUPYYQP
         1KfQ==
X-Gm-Message-State: AOAM5301N3YGea/y3nOJNZ1lOFEgm2b3x7JWnmlZR8pTd5fyZlLIy4pO
        6JMzhFhKBCE4ETmhE0Mh3bBg3Q8g
X-Google-Smtp-Source: 
 ABdhPJyZGd1D68ogyDq+rAQAHt7NL0PRFJ25fZc7vLzDOHQq8zhKw3JzPTtp/nMfVS6pxIcpefvMSw==
X-Received: by 2002:a05:600c:23ce:: with SMTP id
 p14mr8690786wmb.77.1590759956289;
        Fri, 29 May 2020 06:45:56 -0700 (PDT)
Received: from jondnuc.lan (IGLD-84-229-154-20.inter.net.il. [84.229.154.20])
        by smtp.gmail.com with ESMTPSA id
 y37sm12347263wrd.55.2020.05.29.06.45.54
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Fri, 29 May 2020 06:45:55 -0700 (PDT)
From: Jon Doron <arilou@gmail.com>
To: kvm@vger.kernel.org, linux-hyperv@vger.kernel.org
Cc: vkuznets@redhat.com, pbonzini@redhat.com, rvkagan@yandex-team.ru,
        Jon Doron <arilou@gmail.com>
Subject: [PATCH v12 0/6] x86/kvm/hyper-v: add support for synthetic
Date: Fri, 29 May 2020 16:45:37 +0300
Message-Id: <20200529134543.1127440-1-arilou@gmail.com>
X-Mailer: git-send-email 2.25.1
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Add support for the synthetic debugger interface of hyper-v, the synthetic
debugger has 2 modes.
1. Use a set of MSRs to send/recv information (undocumented so it's not
   going to the hyperv-tlfs.h)
2. Use hypercalls

The first mode is based the following MSRs:
1. Control/Status MSRs which either asks for a send/recv .
2. Send/Recv MSRs each holds GPA where the send/recv buffers are.
3. Pending MSR, holds a GPA to a PAGE that simply has a boolean that
   indicates if there is data pending to issue a recv VMEXIT.

The first mode implementation is to simply exit to user-space when
either the control MSR or the pending MSR are being set.
Then it's up-to userspace to implement the rest of the logic of sending/recving.

In the second mode instead of using MSRs KNet will simply issue
Hypercalls with the information to send/recv, in this mode the data
being transferred is UDP encapsulated, unlike in the previous mode in
which you get just the data to send.

The new hypercalls will exit to userspace which will be incharge of
re-encapsulating if needed the UDP packets to be sent.

There is an issue though in which KDNet does not respect the hypercall
page and simply issues vmcall/vmmcall instructions depending on the cpu
type expecting them to be handled as it a real hypercall was issued.

It's important to note that part of this feature has been subject to be
removed in future versions of Windows, which is why some of the
defintions will not be present the the TLFS but in the kvm hyperv header
instead.

v12:
- Rebased on latest origin/master
- Make the KVM_CAP_HYPERV_SYNDBG always enabled, in previous version
  userspace was required to explicitly enable the syndbg capability just
  like with the EVMCS feature.

Jon Doron (5):
  x86/kvm/hyper-v: Explicitly align hcall param for kvm_hyperv_exit
  x86/hyper-v: Add synthetic debugger definitions
  x86/kvm/hyper-v: Add support for synthetic debugger capability
  x86/kvm/hyper-v: enable hypercalls regardless of hypercall page
  x86/kvm/hyper-v: Add support for synthetic debugger via hypercalls

Vitaly Kuznetsov (1):
  KVM: selftests: update hyperv_cpuid with SynDBG tests

 Documentation/virt/kvm/api.rst                |  18 ++
 arch/x86/include/asm/hyperv-tlfs.h            |   6 +
 arch/x86/include/asm/kvm_host.h               |  13 ++
 arch/x86/kvm/hyperv.c                         | 180 +++++++++++++++++-
 arch/x86/kvm/hyperv.h                         |  32 ++++
 arch/x86/kvm/trace.h                          |  51 +++++
 arch/x86/kvm/x86.c                            |   9 +
 include/uapi/linux/kvm.h                      |  13 ++
 .../selftests/kvm/x86_64/hyperv_cpuid.c       | 103 +++++-----
 9 files changed, 374 insertions(+), 51 deletions(-)
```
#### [PATCH v3 00/28] KVM: nSVM: event fixes and migration support
##### From: Paolo Bonzini <pbonzini@redhat.com>

```c
From patchwork Fri May 29 15:39:04 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Paolo Bonzini <pbonzini@redhat.com>
X-Patchwork-Id: 11579159
Return-Path: <SRS0=rOkw=7L=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 3B5FA13B4
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 29 May 2020 15:42:37 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 241E22077D
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 29 May 2020 15:42:37 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="OuzTJwLJ"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727800AbgE2Pjk (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 29 May 2020 11:39:40 -0400
Received: from us-smtp-2.mimecast.com ([205.139.110.61]:21780 "EHLO
        us-smtp-delivery-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S1726838AbgE2Pjj (ORCPT
        <rfc822;kvm@vger.kernel.org>); Fri, 29 May 2020 11:39:39 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1590766778;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=Epmn3nYr/N8EeZcVRj2tMv+zsjPgz0Zj5jT0wPI9k18=;
        b=OuzTJwLJ/gRUd+XXuuGOGOgWt+ARRTmzoGsWPIyVCtq/OA5P9N9jImDlomIwDvdGafo9ji
        9XMoiru0UmjU4XHS0u+cBVvY4j+j0yDP4tMouF2/c6zNI3lrfmnn06V427r7eqipF/i8eb
        JupSoSpxKM2T/Nrcl1fiJMxpvhzxd/U=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-258-PRPaYUAxOfmdd1dwkdvrdA-1; Fri, 29 May 2020 11:39:36 -0400
X-MC-Unique: PRPaYUAxOfmdd1dwkdvrdA-1
Received: from smtp.corp.redhat.com (int-mx04.intmail.prod.int.phx2.redhat.com
 [10.5.11.14])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 8F031460;
        Fri, 29 May 2020 15:39:35 +0000 (UTC)
Received: from virtlab701.virt.lab.eng.bos.redhat.com
 (virtlab701.virt.lab.eng.bos.redhat.com [10.19.152.228])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 3622F5D9EF;
        Fri, 29 May 2020 15:39:35 +0000 (UTC)
From: Paolo Bonzini <pbonzini@redhat.com>
To: linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Subject: [PATCH v3 00/28] KVM: nSVM: event fixes and migration support
Date: Fri, 29 May 2020 11:39:04 -0400
Message-Id: <20200529153934.11694-1-pbonzini@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.14
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This is basically the same as v2 except that it has a small fix to
"KVM: x86: enable event window in inject_pending_event", where
a second pending interrupt or NMI was not enabling the window-open
vmexit (caught by apic.flat).  In addition I've renamed
inject_pending_event to handle_processor_events.

The series now passes kvm-unit-tests and various nested hypervisor tests
so now it's *really* ready for review!  (Thanks Krish for looking at
it so far).

I'm quite pleased with the overall look of the code, though the
INT_CTL arbitration is a bit ugly.  I have plans to implement nested
vGIF and vLS, and then I will probably clean it up.

Paolo

Paolo Bonzini (28):
  KVM: x86: track manually whether an event has been injected
  KVM: x86: enable event window in inject_pending_event
  KVM: nSVM: inject exceptions via svm_check_nested_events
  KVM: nSVM: remove exit_required
  KVM: nSVM: correctly inject INIT vmexits
  KVM: SVM: always update CR3 in VMCB
  KVM: nVMX: always update CR3 in VMCS
  KVM: nSVM: move map argument out of enter_svm_guest_mode
  KVM: nSVM: extract load_nested_vmcb_control
  KVM: nSVM: extract preparation of VMCB for nested run
  KVM: nSVM: move MMU setup to nested_prepare_vmcb_control
  KVM: nSVM: clean up tsc_offset update
  KVM: nSVM: pass vmcb_control_area to copy_vmcb_control_area
  KVM: nSVM: remove trailing padding for struct vmcb_control_area
  KVM: nSVM: save all control fields in svm->nested
  KVM: nSVM: restore clobbered INT_CTL fields after clearing VINTR
  KVM: nSVM: synchronize VMCB controls updated by the processor on every
    vmexit
  KVM: nSVM: remove unnecessary if
  KVM: nSVM: extract svm_set_gif
  KVM: SVM: preserve VGIF across VMCB switch
  KVM: nSVM: synthesize correct EXITINTINFO on vmexit
  KVM: nSVM: remove HF_VINTR_MASK
  KVM: nSVM: remove HF_HIF_MASK
  KVM: nSVM: split nested_vmcb_check_controls
  KVM: nSVM: leave guest mode when clearing EFER.SVME
  KVM: MMU: pass arbitrary CR0/CR4/EFER to kvm_init_shadow_mmu
  selftests: kvm: add a SVM version of state-test
  KVM: nSVM: implement KVM_GET_NESTED_STATE and KVM_SET_NESTED_STATE

Vitaly Kuznetsov (2):
  selftests: kvm: introduce cpu_has_svm() check
  selftests: kvm: fix smm test on SVM

 arch/x86/include/asm/kvm_host.h               |  12 +-
 arch/x86/include/asm/svm.h                    |   9 +-
 arch/x86/include/uapi/asm/kvm.h               |  17 +-
 arch/x86/kvm/cpuid.h                          |   5 +
 arch/x86/kvm/irq.c                            |   1 +
 arch/x86/kvm/mmu.h                            |   2 +-
 arch/x86/kvm/mmu/mmu.c                        |  14 +-
 arch/x86/kvm/svm/nested.c                     | 624 ++++++++++++------
 arch/x86/kvm/svm/svm.c                        | 154 ++---
 arch/x86/kvm/svm/svm.h                        |  33 +-
 arch/x86/kvm/vmx/nested.c                     |   5 -
 arch/x86/kvm/vmx/vmx.c                        |  25 +-
 arch/x86/kvm/x86.c                            | 146 ++--
 .../selftests/kvm/include/x86_64/svm_util.h   |  10 +
 tools/testing/selftests/kvm/x86_64/smm_test.c |  19 +-
 .../testing/selftests/kvm/x86_64/state_test.c |  62 +-
 16 files changed, 708 insertions(+), 430 deletions(-)
```
