#### [PATCH 1/5] drivers/powerpc: Replace _ALIGN_UP() by ALIGN()To: Benjamin Herrenschmidt <benh@kernel.crashing.org>,
##### From: Christophe Leroy <christophe.leroy@c-s.fr>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Christophe Leroy <christophe.leroy@c-s.fr>
X-Patchwork-Id: 11499631
Return-Path: <SRS0=GaVw=6E=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id F2D7213B2
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 20 Apr 2020 18:37:01 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id DB27D208FE
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 20 Apr 2020 18:37:01 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=c-s.fr header.i=@c-s.fr header.b="E+DWEZwJ"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727969AbgDTSgi (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 20 Apr 2020 14:36:38 -0400
Received: from pegase1.c-s.fr ([93.17.236.30]:61324 "EHLO pegase1.c-s.fr"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1725613AbgDTSgh (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 20 Apr 2020 14:36:37 -0400
Received: from localhost (mailhub1-int [192.168.12.234])
        by localhost (Postfix) with ESMTP id 495b4z3MXVz9v1w9;
        Mon, 20 Apr 2020 20:36:35 +0200 (CEST)
Authentication-Results: localhost; dkim=pass
        reason="1024-bit key; insecure key"
        header.d=c-s.fr header.i=@c-s.fr header.b=E+DWEZwJ; dkim-adsp=pass;
        dkim-atps=neutral
X-Virus-Scanned: Debian amavisd-new at c-s.fr
Received: from pegase1.c-s.fr ([192.168.12.234])
        by localhost (pegase1.c-s.fr [192.168.12.234]) (amavisd-new,
 port 10024)
        with ESMTP id L4mwlUXAK_-i; Mon, 20 Apr 2020 20:36:35 +0200 (CEST)
Received: from messagerie.si.c-s.fr (messagerie.si.c-s.fr [192.168.25.192])
        by pegase1.c-s.fr (Postfix) with ESMTP id 495b4z2JLhz9v95f;
        Mon, 20 Apr 2020 20:36:35 +0200 (CEST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=c-s.fr; s=mail;
        t=1587407795; bh=0fa57ddsyHEgiUKKkj3rA4MemZZkyaFbgYjKejGShaM=;
        h=From:Subject:To:Cc:Date:From;
        b=E+DWEZwJhz6Y/xgde33hxmuD3rGUtiRxeI/8EM0ccVSx3KfiQ4f7G5tlyiclyZlTv
         G3EZfX0BGGT6pW9WIfnMkWEKqCSDbnWxGkJCDbptk9jvRRwxinuBROxEoLLsiTAxU+
         2fc5X+q61AH6lsZ6C9gAPrkXh1oIdYDt+A1N76WQ=
Received: from localhost (localhost [127.0.0.1])
        by messagerie.si.c-s.fr (Postfix) with ESMTP id 4F6AA8B78A;
        Mon, 20 Apr 2020 20:36:35 +0200 (CEST)
X-Virus-Scanned: amavisd-new at c-s.fr
Received: from messagerie.si.c-s.fr ([127.0.0.1])
        by localhost (messagerie.si.c-s.fr [127.0.0.1]) (amavisd-new,
 port 10023)
        with ESMTP id 7Voh0XE4aIU2; Mon, 20 Apr 2020 20:36:35 +0200 (CEST)
Received: from pc16570vm.idsi0.si.c-s.fr (unknown [192.168.4.90])
        by messagerie.si.c-s.fr (Postfix) with ESMTP id EFABD8B77E;
        Mon, 20 Apr 2020 20:36:34 +0200 (CEST)
Received: by pc16570vm.idsi0.si.c-s.fr (Postfix, from userid 0)
        id B0D97657AE; Mon, 20 Apr 2020 18:36:34 +0000 (UTC)
Message-Id: 
 <a5945463f86c984151962a475a3ee56a2893e85d.1587407777.git.christophe.leroy@c-s.fr>
From: Christophe Leroy <christophe.leroy@c-s.fr>
Subject: [PATCH 1/5] drivers/powerpc: Replace _ALIGN_UP() by ALIGN()
To: Benjamin Herrenschmidt <benh@kernel.crashing.org>,
        Paul Mackerras <paulus@samba.org>,
        Michael Ellerman <mpe@ellerman.id.au>
Cc: linux-kernel@vger.kernel.org, linuxppc-dev@lists.ozlabs.org,
        kvm@vger.kernel.org, dri-devel@lists.freedesktop.org,
        linux-fbdev@vger.kernel.org, alsa-devel@alsa-project.org
Date: Mon, 20 Apr 2020 18:36:34 +0000 (UTC)
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

_ALIGN_UP() is specific to powerpc
ALIGN() is generic and does the same

Replace _ALIGN_UP() by ALIGN()

Signed-off-by: Christophe Leroy <christophe.leroy@c-s.fr>
---
 drivers/ps3/ps3-lpm.c               | 6 +++---
 drivers/vfio/pci/vfio_pci_nvlink2.c | 2 +-
 drivers/video/fbdev/ps3fb.c         | 4 ++--
 sound/ppc/snd_ps3.c                 | 2 +-
 4 files changed, 7 insertions(+), 7 deletions(-)

```
#### [GIT PULL v2] vhost: cleanups and fixes
##### From: "Michael S. Tsirkin" <mst@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 8bit
X-Patchwork-Submitter: "Michael S. Tsirkin" <mst@redhat.com>
X-Patchwork-Id: 11499773
Return-Path: <SRS0=GaVw=6E=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 46D781892
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 20 Apr 2020 20:00:14 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 281B2208FE
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 20 Apr 2020 20:00:14 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="frFIeFvB"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728245AbgDTUAM (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 20 Apr 2020 16:00:12 -0400
Received: from us-smtp-2.mimecast.com ([207.211.31.81]:55144 "EHLO
        us-smtp-delivery-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S1726412AbgDTUAL (ORCPT
        <rfc822;kvm@vger.kernel.org>); Mon, 20 Apr 2020 16:00:11 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1587412809;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:content-type:content-type:
         content-transfer-encoding:content-transfer-encoding;
        bh=+20lqtsdLoetbi1VKrLQV/f/K/xwxYS/9ftQPVBgJ9o=;
        b=frFIeFvB88aMDcJ6igS/aDBKi3T1xldX3PIzPhYcljPwdZlnLG7mC/DfVFy4pRtHsXNkqh
        oT4AlUgq+BVSudR4M+OUyS7cBGglqO+mzXMFlOl3kwa1ZSGjfYDQnGPSwsoV7Zx8CzNx1R
        nPSK9MeDxRJ9QWn7vTP01Scvgb0NE2g=
Received: from mail-wr1-f71.google.com (mail-wr1-f71.google.com
 [209.85.221.71]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-255-TaIhbuThMniXyITOr9DJ1Q-1; Mon, 20 Apr 2020 16:00:06 -0400
X-MC-Unique: TaIhbuThMniXyITOr9DJ1Q-1
Received: by mail-wr1-f71.google.com with SMTP id 11so6297364wrc.3
        for <kvm@vger.kernel.org>; Mon, 20 Apr 2020 13:00:06 -0700 (PDT)
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:date:from:to:cc:subject:message-id:mime-version
         :content-disposition:content-transfer-encoding;
        bh=+20lqtsdLoetbi1VKrLQV/f/K/xwxYS/9ftQPVBgJ9o=;
        b=axM7suSqWe19iVDxQMQoNraTJnZKSjx++FCvXPJPyOCKFYtLBqtUs6q2UpFlxzRHFP
         60baCmILl30jQbJl4ArOW10dmBKTy0LKUrMcm5FdgqGaqG4K2Pju8cpCsx3xA4mnTVeF
         qVFz6i8NrjVCnfpBvqWOnBHagnyNHBA/PL7aNVXgEtvCxZ4uVVAFSWXIaIAPxBEf5TLA
         q20mB5bAGeIFlD2SoM3AB61dBX36wZcUf2ERfQ7tXZQNEr+ywbvdplBzXwXzmUhmidqo
         D1YbEjyPTHbNbNWioTgMcoFe5QftSGkDc+J5tmFzJxP3D+XW0peAZ8eeUDpxUpKhkZoN
         8LxQ==
X-Gm-Message-State: AGi0PuYeeNb1EjvUNcCn5HntD1bTO28UTLHBXRY2Poxf5b7O0nH9+fR7
        miNqdcBwHSxmqLo15H2+jYj3Ta/MYrgbSGz3ODn2J8AXg4a9JoDAMJ2k9nrkf19PMOuMGdfeqAb
        WBvXtGvtq2fty
X-Received: by 2002:adf:f881:: with SMTP id u1mr20010569wrp.348.1587412804909;
        Mon, 20 Apr 2020 13:00:04 -0700 (PDT)
X-Google-Smtp-Source: 
 APiQypJIVhqetK7aUCHYEkuU804XOceo66/cE0Dx1Q5aW14bSOsutRUOmxAsjw6JtGgBkBYwz6DrLg==
X-Received: by 2002:adf:f881:: with SMTP id u1mr20010546wrp.348.1587412804645;
        Mon, 20 Apr 2020 13:00:04 -0700 (PDT)
Received: from redhat.com (bzq-79-183-51-3.red.bezeqint.net. [79.183.51.3])
        by smtp.gmail.com with ESMTPSA id m1sm677467wro.64.2020.04.20.13.00.02
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Mon, 20 Apr 2020 13:00:03 -0700 (PDT)
Date: Mon, 20 Apr 2020 16:00:01 -0400
From: "Michael S. Tsirkin" <mst@redhat.com>
To: Linus Torvalds <torvalds@linux-foundation.org>
Cc: kvm@vger.kernel.org, virtualization@lists.linux-foundation.org,
        netdev@vger.kernel.org, linux-kernel@vger.kernel.org,
        alexander.h.duyck@linux.intel.com, arnd@arndb.de,
        bjorn.andersson@linaro.org, eli@mellanox.com, eperezma@redhat.com,
        gustavo@embeddedor.com, hulkci@huawei.com, jasowang@redhat.com,
        mst@redhat.com, sfr@canb.auug.org.au, yanaijie@huawei.com,
        yuehaibing@huawei.com
Subject: [GIT PULL v2] vhost: cleanups and fixes
Message-ID: <20200420160001-mutt-send-email-mst@kernel.org>
MIME-Version: 1.0
Content-Disposition: inline
X-Mutt-Fcc: =sent
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The following changes since commit 8f3d9f354286745c751374f5f1fcafee6b3f3136:

  Linux 5.7-rc1 (2020-04-12 12:35:55 -0700)

are available in the Git repository at:

  https://git.kernel.org/pub/scm/linux/kernel/git/mst/vhost.git tags/for_linus

for you to fetch changes up to d085eb8ce727e581abf8145244eaa3339021be2f:

  vhost: disable for OABI (2020-04-20 10:19:22 -0400)

Changes from v1:
	Dropped a bunch of cleanups which turned out to be controversial

This has been in next for a while, though I tweaked some commit
logs so the hashes differ.

----------------------------------------------------------------
virtio: fixes, cleanups

Some bug fixes.
Cleanup a couple of issues that surfaced meanwhile.
Disable vhost on ARM with OABI for now - to be fixed
fully later in the cycle or in the next release.

Signed-off-by: Michael S. Tsirkin <mst@redhat.com>

----------------------------------------------------------------
Alexander Duyck (1):
      virtio-balloon: Avoid using the word 'report' when referring to free page hinting

Eugenio Pérez (1):
      vhost: Create accessors for virtqueues private_data

Gustavo A. R. Silva (1):
      vhost: vdpa: remove unnecessary null check

Jason Wang (1):
      vdpa: fix comment of vdpa_register_device()

Jason Yan (2):
      vhost: remove set but not used variable 'status'
      virtio-balloon: make virtballoon_free_page_report() static

Michael S. Tsirkin (15):
      vdpa-sim: depend on HAS_DMA
      virtio/test: fix up after IOTLB changes
      tools/virtio: define aligned attribute
      tools/virtio: make asm/barrier.h self contained
      virtgpu: pull in uaccess.h
      virtio-rng: pull in slab.h
      remoteproc: pull in slab.h
      virtio_input: pull in slab.h
      rpmsg: pull in slab.h
      remoteproc: pull in slab.h
      vdpa: allow a 32 bit vq alignment
      vdpa: make vhost, virtio depend on menu
      virtio_blk: add a missing include
      virtio: drop vringh.h dependency
      vhost: disable for OABI

Stephen Rothwell (1):
      drm/virtio: fix up for include file changes

YueHaibing (2):
      vdpa: remove unused variables 'ifcvf' and 'ifcvf_lm'
      vdpasim: Return status in vdpasim_get_status

 drivers/block/virtio_blk.c             |  1 +
 drivers/char/hw_random/virtio-rng.c    |  1 +
 drivers/gpu/drm/virtio/virtgpu_ioctl.c |  1 +
 drivers/gpu/drm/virtio/virtgpu_kms.c   |  1 +
 drivers/misc/mic/Kconfig               |  2 +-
 drivers/net/caif/Kconfig               |  2 +-
 drivers/remoteproc/remoteproc_sysfs.c  |  1 +
 drivers/remoteproc/stm32_rproc.c       |  1 +
 drivers/rpmsg/mtk_rpmsg.c              |  1 +
 drivers/vdpa/Kconfig                   | 18 ++++++------------
 drivers/vdpa/ifcvf/ifcvf_base.c        |  2 --
 drivers/vdpa/ifcvf/ifcvf_main.c        |  4 +---
 drivers/vdpa/vdpa.c                    |  2 +-
 drivers/vdpa/vdpa_sim/vdpa_sim.c       |  4 ++--
 drivers/vhost/Kconfig                  | 21 ++++++++++++++++-----
 drivers/vhost/net.c                    | 28 +++++++++++++++-------------
 drivers/vhost/scsi.c                   | 14 +++++++-------
 drivers/vhost/test.c                   | 14 +++++++-------
 drivers/vhost/vdpa.c                   |  5 -----
 drivers/vhost/vhost.h                  | 27 +++++++++++++++++++++++++++
 drivers/vhost/vringh.c                 |  5 +++++
 drivers/vhost/vsock.c                  | 14 +++++++-------
 drivers/virtio/Kconfig                 |  2 +-
 drivers/virtio/virtio_balloon.c        |  4 ++--
 drivers/virtio/virtio_input.c          |  1 +
 include/linux/vdpa.h                   |  2 +-
 include/linux/virtio.h                 |  1 -
 include/linux/vringh.h                 |  6 ++++++
 include/uapi/linux/virtio_balloon.h    | 11 +++++++++--
 tools/virtio/Makefile                  |  5 +++--
 tools/virtio/asm/barrier.h             |  1 +
 tools/virtio/generated/autoconf.h      |  0
 tools/virtio/linux/compiler.h          |  1 +
 33 files changed, 128 insertions(+), 75 deletions(-)
 create mode 100644 tools/virtio/generated/autoconf.h
```
#### [PATCH] kvm: Disable objtool frame pointer checking for vmenter.S
##### From: Josh Poimboeuf <jpoimboe@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Josh Poimboeuf <jpoimboe@redhat.com>
X-Patchwork-Id: 11499299
Return-Path: <SRS0=GaVw=6E=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id A1F571575
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 20 Apr 2020 16:17:51 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 7F1DA206F6
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 20 Apr 2020 16:17:51 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="HnLsVv5l"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728287AbgDTQRu (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 20 Apr 2020 12:17:50 -0400
Received: from us-smtp-delivery-1.mimecast.com ([205.139.110.120]:29563 "EHLO
        us-smtp-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org
        with ESMTP id S1726061AbgDTQRu (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 20 Apr 2020 12:17:50 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1587399467;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=aVmMlP4bgEOgyhPBBrYrGgIG5tzuNNZSz4+8vsE0HJo=;
        b=HnLsVv5lsKBB1lu5s0gWnTn0S1z5AGyTKHoNbNRCDt0jgZPucd4D4QFySgkMPDxtgB7Xh4
        yWcXj6/yndTR4sYJuo824bX53dbQ0oyAzndD3SGPOkIum33OQ9g4UjFI1pGrRlY8WNEhOq
        c8Wm/r8upuEF3+70pZ82tcYpvvg8faY=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-436-4C7849F1MoOjHETHB0DVtQ-1; Mon, 20 Apr 2020 12:17:45 -0400
X-MC-Unique: 4C7849F1MoOjHETHB0DVtQ-1
Received: from smtp.corp.redhat.com (int-mx06.intmail.prod.int.phx2.redhat.com
 [10.5.11.16])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 33106190B2B3;
        Mon, 20 Apr 2020 16:17:44 +0000 (UTC)
Received: from treble.redhat.com (ovpn-116-8.rdu2.redhat.com [10.10.116.8])
        by smtp.corp.redhat.com (Postfix) with ESMTP id EA1295C64E;
        Mon, 20 Apr 2020 16:17:41 +0000 (UTC)
From: Josh Poimboeuf <jpoimboe@redhat.com>
To: Paolo Bonzini <pbonzini@redhat.com>
Cc: kvm@vger.kernel.org, Peter Zijlstra <peterz@infradead.org>,
        Randy Dunlap <rdunlap@infradead.org>
Subject: [PATCH] kvm: Disable objtool frame pointer checking for vmenter.S
Date: Mon, 20 Apr 2020 11:17:37 -0500
Message-Id: 
 <01fae42917bacad18be8d2cbc771353da6603473.1587398610.git.jpoimboe@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.16
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Frame pointers are completely broken by vmenter.S because it clobbers
RBP:

  arch/x86/kvm/svm/vmenter.o: warning: objtool: __svm_vcpu_run()+0xe4: BP used as a scratch register

That's unavoidable, so just skip checking that file when frame pointers
are configured in.

On the other hand, ORC can handle that code just fine, so leave objtool
enabled in the !FRAME_POINTER case.

Reported-by: Randy Dunlap <rdunlap@infradead.org>
Signed-off-by: Josh Poimboeuf <jpoimboe@redhat.com>
Acked-by: Randy Dunlap <rdunlap@infradead.org> # build-tested
---
 arch/x86/kvm/Makefile | 4 ++++
 1 file changed, 4 insertions(+)

```
#### [PATCH] kvm/eventfd: remove unneeded conversion to bool
##### From: Jason Yan <yanaijie@huawei.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Jason Yan <yanaijie@huawei.com>
X-Patchwork-Id: 11498791
Return-Path: <SRS0=GaVw=6E=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id AB77081
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 20 Apr 2020 12:11:37 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 9AD6B2075A
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 20 Apr 2020 12:11:37 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726872AbgDTMLe (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 20 Apr 2020 08:11:34 -0400
Received: from szxga06-in.huawei.com ([45.249.212.32]:38476 "EHLO huawei.com"
        rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org with ESMTP
        id S1726262AbgDTMLe (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 20 Apr 2020 08:11:34 -0400
Received: from DGGEMS403-HUB.china.huawei.com (unknown [172.30.72.59])
        by Forcepoint Email with ESMTP id B7A27F04CFD1B40AC454;
        Mon, 20 Apr 2020 20:11:32 +0800 (CST)
Received: from huawei.com (10.175.124.28) by DGGEMS403-HUB.china.huawei.com
 (10.3.19.203) with Microsoft SMTP Server id 14.3.487.0; Mon, 20 Apr 2020
 20:11:23 +0800
From: Jason Yan <yanaijie@huawei.com>
To: <pbonzini@redhat.com>, <peterx@redhat.com>, <tglx@linutronix.de>,
        <kvm@vger.kernel.org>, <linux-kernel@vger.kernel.org>
CC: Jason Yan <yanaijie@huawei.com>
Subject: [PATCH] kvm/eventfd: remove unneeded conversion to bool
Date: Mon, 20 Apr 2020 20:38:05 +0800
Message-ID: <20200420123805.4494-1-yanaijie@huawei.com>
X-Mailer: git-send-email 2.21.1
MIME-Version: 1.0
X-Originating-IP: [10.175.124.28]
X-CFilter-Loop: Reflected
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The '==' expression itself is bool, no need to convert it to bool again.
This fixes the following coccicheck warning:

virt/kvm/eventfd.c:724:38-43: WARNING: conversion to bool not needed
here

Signed-off-by: Jason Yan <yanaijie@huawei.com>
Reviewed-by: Peter Xu <peterx@redhat.com>
---
 virt/kvm/eventfd.c | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
#### [kvm-unit-tests PATCH v3] x86: nVMX: add new test for vmread/vmwrite flags preservation
##### From: Simon Smith <brigidsmith@google.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Simon Smith <brigidsmith@google.com>
X-Patchwork-Id: 11499547
Return-Path: <SRS0=GaVw=6E=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id CC766913
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 20 Apr 2020 17:59:23 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id AFD032145D
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 20 Apr 2020 17:59:23 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=google.com header.i=@google.com
 header.b="BdBtj6dA"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727775AbgDTR7W (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 20 Apr 2020 13:59:22 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:54116 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726013AbgDTR7W (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 20 Apr 2020 13:59:22 -0400
Received: from mail-yb1-xb49.google.com (mail-yb1-xb49.google.com
 [IPv6:2607:f8b0:4864:20::b49])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id D6A97C061A0C
        for <kvm@vger.kernel.org>; Mon, 20 Apr 2020 10:59:20 -0700 (PDT)
Received: by mail-yb1-xb49.google.com with SMTP id y73so4717784ybe.22
        for <kvm@vger.kernel.org>; Mon, 20 Apr 2020 10:59:20 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=date:message-id:mime-version:subject:from:to:cc;
        bh=FNiVif2OGs+DEb/0JGe/lmn9AvD2UyqpmhDBJ0M7DiI=;
        b=BdBtj6dAXNTjrn5LHd5QUsXYKI5HfnUqrgXaaL6L1AzEhlw/0PANMnlRu1dQC7kCVb
         wQxAYz3VcbwD4ehXOwkfzOBfqEMwNtE/1uSS06Mb4DfJ8K7PcmGcuWMDp2ClBKwm+62C
         irTHKpGA7iUUtcgaarriZx4uHctZoY+8dsENgR0m536/NJZfHFN+5r2x4YC4JyI8MNzb
         ldcxVZKpOuKsOZp2CVkFTxhhYv+r1b2qsPao4EDIZJ7DnOdNluAww1K8GILXNo3xXtWD
         GQ3jjOWDoDGoPuGQUTgcdmUTxGp493zsxkkDbDimIjye0CaMm9C8NeAVL5GRyFHaR+nG
         6/tg==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:date:message-id:mime-version:subject:from:to:cc;
        bh=FNiVif2OGs+DEb/0JGe/lmn9AvD2UyqpmhDBJ0M7DiI=;
        b=VMNwLk3S4f6CSUnByhfaHs9eh3cFjWuuDWoI5X0hYbXaX9p5T1/gJERYZfMNJuiSA9
         Hw/BqPbA6E3/UU5CiL5p0NdblTLHnzRDWO6gosIpPytsxY4ZWMwhcARuab7p3Hi35jja
         kZuvnnK7p74AHQFeskpy2FPVk/gqOiMw0El1j72HSD4P2ARqIyFxkCOMBUyDu8kxj5am
         34ROBBJ9iRznEPGqSjJFbe9jS0EYOwEZ06pmqRRkArUvbKONI0Yz5aL0EpRQKzxkmPY4
         nAQ54Mfi9zhD2UspqTx/A2vMFG6gnyhjvSB+tsSUlzKsGU0Kl14RlOWOao8OEdFZoVeN
         TkMg==
X-Gm-Message-State: AGi0Puaz10O4JVWlxoji8Ac6MW5SfLJybdbXGqIiaYNhFitEdRtUVNxk
        8pgnh4U5a7ElMAoUu1wgySt1/NQggs8gUURFAM7MqtrC7RPl5fJGuZnFuVPaLNch+hOult4rPNg
        Ut4jyTyxZL2gHOrWVUKfskqAY2Fr2qcEGGhdL8G8E5kcBsu2zO6SOKOTF7tmHYZ9w0bVW2p0=
X-Google-Smtp-Source: 
 APiQypJTSwql/zEgDxhAIO0C/xVMA0IBQfDwR9/++glCbi3BtIbmXdnSBP6nkiPrh1FdWrod08wMdfR5p1stG2PZ4Q==
X-Received: by 2002:a25:5057:: with SMTP id
 e84mr19773139ybb.198.1587405560005;
 Mon, 20 Apr 2020 10:59:20 -0700 (PDT)
Date: Mon, 20 Apr 2020 10:58:34 -0700
Message-Id: <20200420175834.258122-1-brigidsmith@google.com>
Mime-Version: 1.0
X-Mailer: git-send-email 2.26.1.301.g55bc3eb7cb9-goog
Subject: [kvm-unit-tests PATCH v3] x86: nVMX: add new test for vmread/vmwrite
 flags preservation
From: Simon Smith <brigidsmith@google.com>
To: kvm@vger.kernel.org
Cc: Simon Smith <brigidsmith@google.com>,
        Jim Mattson <jmattson@google.com>,
        Peter Shier <pshier@google.com>,
        Krish Sadhukhan <krish.sadhukhan@oracle.com>,
        Oliver Upton <oupton@google.com>
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This commit adds new unit tests for commit a4d956b93904 ("KVM: nVMX:
vmread should not set rflags to specify success in case of #PF")

The two new tests force a vmread and a vmwrite on an unmapped
address to cause a #PF and verify that the low byte of %rflags is
preserved and that %rip is not advanced.  The commit fixed a
bug in vmread, but we include a test for vmwrite as well for
completeness.

Before the aforementioned commit, the ALU flags would be incorrectly
cleared and %rip would be advanced (for vmread).

Signed-off-by: Simon Smith <brigidsmith@google.com>
Reviewed-by: Jim Mattson <jmattson@google.com>
Reviewed-by: Peter Shier <pshier@google.com>
Reviewed-by: Krish Sadhukhan <krish.sadhukhan@oracle.com>
Reviewed-by: Oliver Upton <oupton@google.com>
---
 x86/vmx.c | 140 ++++++++++++++++++++++++++++++++++++++++++++++++++++++
 1 file changed, 140 insertions(+)

```
#### [PATCH 1/4] KVM: x86: hyperv: Remove duplicate definitions of Reference TSC Page
##### From: Michael Kelley <mikelley@microsoft.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Michael Kelley <mikelley@microsoft.com>
X-Patchwork-Id: 11499517
Return-Path: <SRS0=GaVw=6E=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 37B9C92C
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 20 Apr 2020 17:39:38 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 1A11E20B1F
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 20 Apr 2020 17:39:38 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=microsoft.com header.i=@microsoft.com
 header.b="Gm3Iqql1"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726833AbgDTRjf (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 20 Apr 2020 13:39:35 -0400
Received: from mail-mw2nam12on2124.outbound.protection.outlook.com
 ([40.107.244.124]:36000
        "EHLO NAM12-MW2-obe.outbound.protection.outlook.com"
        rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org with ESMTP
        id S1726021AbgDTRjd (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 20 Apr 2020 13:39:33 -0400
ARC-Seal: i=1; a=rsa-sha256; s=arcselector9901; d=microsoft.com; cv=none;
 b=G2tspkJ5QPOZzpHHZL3+YNleYT3Xqsg497ES5sP972QQAyWPkdxkUBMvhXWMyloOkLokxEW03GvZ2r2pwqbF+/98ehlIJ5YwWtAVhKSRwHfdW+KwdKqfSAX8tjj8afCUJCuOU9N+8oSwGe1c3wdMMggtGhvmD4HiKkGeRTbKjdGFCbYYg1ZF9O3YPWxGYfIo7vZGhuHzC+OuzRfuOk7/iwzJ+J7VCW//M2rmHPgkJeZ0j8/wyx0eew5lbTPoluBmbxANG9MxhbA/p/MdzmnNVPE+/iisHsuWQ/+By+SQCSmBCWFHze+fTkEkgiBYnTL0NjPRb0lk2+7eW9L0dw3/1g==
ARC-Message-Signature: i=1; a=rsa-sha256; c=relaxed/relaxed; d=microsoft.com;
 s=arcselector9901;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=rURpkildjr2k32/HcTJXbyFaUgkXhqE2Pfu/AMJr+e4=;
 b=WzcP70q0CSxzk3Y1dXHQoZC0YUDCB4+xLyyydTYI7gokJYyBvcK8qE4DO0EKtE5MdKEZ5chYApLzDt4b1BvffHBMR94DIg7LnYvjaMz0tIoNBKmYljJ+8gRSm8shsTRfMsKaRsEc+RNNak/GCylRzOHd3XUuwyZM4xF9Jsi1HRoH+SbX0NZQOYbqMNY1vqrQ0Xw9MZOSHhZHOuFo4AdAna8wu0q4suR9zxViXsG4N62qUNCba/13y2z049VAihZchtW1d/zPf/RaQnfmDo/3vmBELIaNMqGj0C2din6+LbIR+XGX2ypy/S5RWapr5ijtdUDnox7cEZav0LHGF0VjWw==
ARC-Authentication-Results: i=1; mx.microsoft.com 1; spf=pass
 smtp.mailfrom=microsoft.com; dmarc=pass action=none
 header.from=microsoft.com; dkim=pass header.d=microsoft.com; arc=none
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=microsoft.com;
 s=selector2;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=rURpkildjr2k32/HcTJXbyFaUgkXhqE2Pfu/AMJr+e4=;
 b=Gm3Iqql1yvUvGgs3xsHXgmv7vhjxUm6JJXnGNuWo1wWd5FN7Q4RSU69ahPyf7LQ6dUfdCU5ySyBe/fPOLxAAVlpXPlQ6DSjX2UT10dQGe6jn4z0vdq9fvQBciQnZr3JMaB6fb53J6xjMn9rApAPgRUmRbMZObk1S5uXQA40PqqA=
Authentication-Results: spf=none (sender IP is )
 smtp.mailfrom=mikelley@microsoft.com;
Received: from BN6PR21MB0178.namprd21.prod.outlook.com (2603:10b6:404:94::12)
 by BN6PR21MB0691.namprd21.prod.outlook.com (2603:10b6:404:11b::13) with
 Microsoft SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.2958.2; Mon, 20 Apr
 2020 17:39:28 +0000
Received: from BN6PR21MB0178.namprd21.prod.outlook.com
 ([fe80::a97c:360c:9ed2:12ec]) by BN6PR21MB0178.namprd21.prod.outlook.com
 ([fe80::a97c:360c:9ed2:12ec%11]) with mapi id 15.20.2958.001; Mon, 20 Apr
 2020 17:39:28 +0000
From: Michael Kelley <mikelley@microsoft.com>
To: kys@microsoft.com, haiyangz@microsoft.com, sthemmin@microsoft.com,
        wei.liu@kernel.org, tglx@linutronix.de, mingo@redhat.com,
        bp@alien8.de, x86@kernel.org, hpa@zytor.com, pbonzini@redhat.com,
        sean.j.christopherson@intel.com, vkuznets@redhat.com,
        wanpengli@tencent.com, jmattson@google.com, joro@8bytes.org,
        kvm@vger.kernel.org, linux-kernel@vger.kernel.org,
        linux-hyperv@vger.kernel.org
Cc: mikelley@microsoft.com
Subject: [PATCH 1/4] KVM: x86: hyperv: Remove duplicate definitions of
 Reference TSC Page
Date: Mon, 20 Apr 2020 10:38:35 -0700
Message-Id: <20200420173838.24672-2-mikelley@microsoft.com>
X-Mailer: git-send-email 2.18.2
In-Reply-To: <20200420173838.24672-1-mikelley@microsoft.com>
References: <20200420173838.24672-1-mikelley@microsoft.com>
X-ClientProxiedBy: MWHPR08CA0047.namprd08.prod.outlook.com
 (2603:10b6:300:c0::21) To BN6PR21MB0178.namprd21.prod.outlook.com
 (2603:10b6:404:94::12)
MIME-Version: 1.0
X-MS-Exchange-MessageSentRepresentingType: 1
Received: from MHKdev.corp.microsoft.com (131.107.160.236) by
 MWHPR08CA0047.namprd08.prod.outlook.com (2603:10b6:300:c0::21) with Microsoft
 SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.2921.25 via Frontend
 Transport; Mon, 20 Apr 2020 17:39:26 +0000
X-Mailer: git-send-email 2.18.2
X-Originating-IP: [131.107.160.236]
X-MS-PublicTrafficType: Email
X-MS-Office365-Filtering-HT: Tenant
X-MS-Office365-Filtering-Correlation-Id: 0597de61-168d-46bc-82eb-08d7e551c671
X-MS-TrafficTypeDiagnostic: BN6PR21MB0691:|BN6PR21MB0691:|BN6PR21MB0691:
X-MS-Exchange-Transport-Forked: True
X-LD-Processed: 72f988bf-86f1-41af-91ab-2d7cd011db47,ExtAddr
X-Microsoft-Antispam-PRVS: 
 <BN6PR21MB069162D3419ABB03EF26FF0BD7D40@BN6PR21MB0691.namprd21.prod.outlook.com>
X-MS-Oob-TLC-OOBClassifiers: OLM:7219;
X-Forefront-PRVS: 03793408BA
X-Forefront-Antispam-Report: 
 CIP:255.255.255.255;CTRY:;LANG:en;SCL:1;SRV:;IPV:NLI;SFV:NSPM;H:BN6PR21MB0178.namprd21.prod.outlook.com;PTR:;CAT:NONE;SFTY:;SFS:(4636009)(39860400002)(366004)(376002)(136003)(396003)(346002)(7416002)(66556008)(66946007)(66476007)(6486002)(16526019)(36756003)(6666004)(1076003)(186003)(7696005)(52116002)(86362001)(26005)(5660300002)(4326008)(2616005)(10290500003)(8676002)(956004)(316002)(478600001)(2906002)(82960400001)(82950400001)(81156014)(8936002)(107886003)(921003);DIR:OUT;SFP:1102;
Received-SPF: None (protection.outlook.com: microsoft.com does not designate
 permitted sender hosts)
X-MS-Exchange-SenderADCheck: 1
X-Microsoft-Antispam: BCL:0;
X-Microsoft-Antispam-Message-Info: 
 jZeCwuwfbV6U01ZgoCdkjDEUVhVFn1XQ6nTbukuru7qtYoKE/oHoO/dsweZtDDxZZ8/ed2N5iSRDrLGjuAmv786C+iv2UkrlZKaLcwU6OyZ7Yf0xtqN7EOkz5cjrBWr4ZG3w8qkWH69Cf3kKxszg9QaBDLbe3h+sT+bNmGcmMK8FgUlKBvNa8G9tMTemaBRcCtpskWgOAoT59EcfcAlmDIFX6LLCpZDt7Q2u2zN/r9vtGOEe6pz+m38wPfB663S9dJPJdw8thQik6x9M2XGlELGcPldEzpVX0QtexeOu5KhGQdVspHzH+kH8dK0J7zlGghTVgNH1yLeEgjxqwGc/MFr9L/VrUnh0j5pMNX2Zy3sBoHThXjyIfN8FIBdQtX2Hd64ykVwkon+t+0jyQQAIGYHwmnmvqbJ+KFrGjg0qfXbjAu6o9I9iGIWjoRcvFqs+HWLEipQz5DdTaOpN9pC7dUj2gqiE3BecbQJXGzQMbtA=
X-MS-Exchange-AntiSpam-MessageData: 
 1WuR1oguNIZ1njAjorC3PE5uWuQH4MA5m/X9+Wvd+c5pveSj8SDk3AZW1y9Y/VzlhOkIpMk2DKceHYAw89/VV3f1wGbSZSH30CdP+N3S9SnnGxHYxuXjfVLo7RO3RMC00NkHthAEGF9Rpl8qYRjhlQzij0E9VPT9wzGWN/UH/ejiu70qf7WN2CUv5J2jkifgrGuRcVGEwfhcw69WP0FFpySCqWrMcgJQdQgXWmvY9hXHtXCKHJV8F73OSJ39/98COYQHQVijjUXDJJRQjbm6zB5cK61UGW/n7q954ZQlpeLdMo4IRaUk4YqsqqG5ufwzHJF2BvRrdgduLqZZRaZ4QD0cny13nNfVTWJdMlWiScm1GJVJcXljrYTs/CxTeRmlxCUGWL4VYHRAfb433nJWDhXUOvmsKa+771/wrbtFh2O4pRoHJsgf3JWre2UK4hAqmb6v0c2nteyIS0atA9gN4reL3fG9oECD2NE32jR3udZMSuShkUbECfSgRZH1PiM/fHQSWeiO4qr98UHV3Q03iBJNMN18Y/P6QzasqMsFRsa28hHESsZQxDv7AvucD0r8bgoDq9Su17PjXhch5qltCy8IMALjI36HBZfJ2HcA6pYt1GuuCqqQl+xC9sxZQ7ds/WV4pY/4ss7R9q8LOfjSwqtZwkalOrRHQuqK5DcCQfROM4ADwMsNsIVgS0lelai0nR+6wKWzbxkClcBsOAlYrf6fHiFPoGY4OhMvT1tli/Vdi0B3X1z53R8ruxm1QNza+YwEvKMhAu653r6paKhaYAboKImad+R7rm0XjRUfP6gu2Q8J/CdnceJyTLL/qpfK
X-OriginatorOrg: microsoft.com
X-MS-Exchange-CrossTenant-Network-Message-Id: 
 0597de61-168d-46bc-82eb-08d7e551c671
X-MS-Exchange-CrossTenant-OriginalArrivalTime: 20 Apr 2020 17:39:28.2393
 (UTC)
X-MS-Exchange-CrossTenant-FromEntityHeader: Hosted
X-MS-Exchange-CrossTenant-Id: 72f988bf-86f1-41af-91ab-2d7cd011db47
X-MS-Exchange-CrossTenant-MailboxType: HOSTED
X-MS-Exchange-CrossTenant-UserPrincipalName: 
 k/iABEmlEjUlIr49f0J0P8ibccjxY/odeu06iD8gNtE/6HKpD+R3+6KxwXdWdvXOjiZyNkTJqhtUbgAu7y4Npg==
X-MS-Exchange-Transport-CrossTenantHeadersStamped: BN6PR21MB0691
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The Hyper-V Reference TSC Page structure is defined twice. struct
ms_hyperv_tsc_page has padding out to a full 4 Kbyte page size. But
the padding is not needed because the declaration includes a union
with HV_HYP_PAGE_SIZE.  KVM uses the second definition, which is
struct _HV_REFERENCE_TSC_PAGE, because it does not have the padding.

Fix the duplication by removing the padding from ms_hyperv_tsc_page.
Fix up the KVM code to use it. Remove the no longer used struct
_HV_REFERENCE_TSC_PAGE.

There is no functional change.

Signed-off-by: Michael Kelley <mikelley@microsoft.com>
---
 arch/x86/include/asm/hyperv-tlfs.h | 8 --------
 arch/x86/include/asm/kvm_host.h    | 2 +-
 arch/x86/kvm/hyperv.c              | 4 ++--
 3 files changed, 3 insertions(+), 11 deletions(-)

```
#### [PATCH v2] docs/virt/kvm: Document running nested guests
##### From: Kashyap Chamarthy <kchamart@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 8bit
X-Patchwork-Submitter: Kashyap Chamarthy <kchamart@redhat.com>
X-Patchwork-Id: 11498613
Return-Path: <SRS0=GaVw=6E=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 68B9A92C
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 20 Apr 2020 11:18:20 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 459E020735
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 20 Apr 2020 11:18:20 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="MlIF+F5y"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1725994AbgDTLST (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 20 Apr 2020 07:18:19 -0400
Received: from us-smtp-delivery-1.mimecast.com ([205.139.110.120]:56303 "EHLO
        us-smtp-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org
        with ESMTP id S1725865AbgDTLSS (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 20 Apr 2020 07:18:18 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1587381495;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:content-type:content-type:
         content-transfer-encoding:content-transfer-encoding;
        bh=N4Nv0L7gLINJLh/GBzj1ejbE1VahAD0xEelofG7KQVE=;
        b=MlIF+F5y5gWs3i2lTMKi3s0I7n7/SBOyEwgvG44QHPxey64HfiaTrdGAphR/rdUPjuyN+y
        25vAyEEXFJTeow+hWG6suBlN/41OIpBT19avxa8Y0Llw+3mRn/ZgNK+FVzeWFuocj32asW
        cnERHZNk127EQwNajjCqwg0SHFGyC70=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-322-11HRul0xM_iE6Rdpe9_ECg-1; Mon, 20 Apr 2020 07:18:10 -0400
X-MC-Unique: 11HRul0xM_iE6Rdpe9_ECg-1
Received: from smtp.corp.redhat.com (int-mx06.intmail.prod.int.phx2.redhat.com
 [10.5.11.16])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 88E41800D53
        for <kvm@vger.kernel.org>; Mon, 20 Apr 2020 11:18:09 +0000 (UTC)
Received: from paraplu.localdomain (unknown [10.36.110.20])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 69F275C1C3;
        Mon, 20 Apr 2020 11:18:07 +0000 (UTC)
From: Kashyap Chamarthy <kchamart@redhat.com>
To: kvm@vger.kernel.org
Cc: pbonzini@redhat.com, cohuck@redhat.com, dgilbert@redhat.com,
        vkuznets@redhat.com, kchamart@redhat.com
Subject: [PATCH v2] docs/virt/kvm: Document running nested guests
Date: Mon, 20 Apr 2020 13:17:55 +0200
Message-Id: <20200420111755.2926-1-kchamart@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.16
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This is a rewrite of this[1] Wiki page with further enhancements.  The
doc also includes a section on debugging problems in nested
environments.

[1] https://www.linux-kvm.org/page/Nested_Guests

Signed-off-by: Kashyap Chamarthy <kchamart@redhat.com>
---
v1 is here: https://marc.info/?l=kvm&m=158108941605311&w=2

In v2:
  - Address Cornelia's feedback v1:
    https://marc.info/?l=kvm&m=158109042605606&w=2
  - Address Dave's feedback from v1:
    https://marc.info/?l=kvm&m=158109134905930&w=2
---
 .../virt/kvm/running-nested-guests.rst        | 275 ++++++++++++++++++
 1 file changed, 275 insertions(+)
 create mode 100644 Documentation/virt/kvm/running-nested-guests.rst

diff --git a/Documentation/virt/kvm/running-nested-guests.rst b/Documentation/virt/kvm/running-nested-guests.rst
new file mode 100644
index 0000000000000000000000000000000000000000..c6c9ccfa0c00e3cbfd65782ceae962b7ef52b34b
--- /dev/null
+++ b/Documentation/virt/kvm/running-nested-guests.rst
@@ -0,0 +1,275 @@
+==============================
+Running nested guests with KVM
+==============================
+
+A nested guest is the ability to run a guest inside another guest (it
+can be KVM-based or a different hypervisor).  The straightforward
+example is a KVM guest that in turn runs on KVM a guest (the rest of
+this document is built on this example)::
+
+              .----------------.  .----------------.
+              |                |  |                |
+              |      L2        |  |      L2        |
+              | (Nested Guest) |  | (Nested Guest) |
+              |                |  |                |
+              |----------------'--'----------------|
+              |                                    |
+              |       L1 (Guest Hypervisor)        |
+              |          KVM (/dev/kvm)            |
+              |                                    |
+      .------------------------------------------------------.
+      |                 L0 (Host Hypervisor)                 |
+      |                    KVM (/dev/kvm)                    |
+      |------------------------------------------------------|
+      |        Hardware (with virtualization extensions)     |
+      '------------------------------------------------------'
+
+Terminology:
+
+- L0 – level-0; the bare metal host, running KVM
+
+- L1 – level-1 guest; a VM running on L0; also called the "guest
+  hypervisor", as it itself is capable of running KVM.
+
+- L2 – level-2 guest; a VM running on L1, this is the "nested guest"
+
+.. note:: The above diagram is modelled after x86 architecture; s390x,
+          ppc64 and other architectures are likely to have different
+          design for nesting.
+
+          For example, s390x has an additional layer, called "LPAR
+          hypervisor" (Logical PARtition) on the baremetal, resulting in
+          "four levels" in a nested setup — L0 (bare metal, running the
+          LPAR hypervisor), L1 (host hypervisor), L2 (guest hypervisor),
+          L3 (nested guest).
+
+          This document will stick with the three-level terminology (L0,
+          L1, and L2) for all architectures; and will largely focus on
+          x86.
+
+
+Use Cases
+---------
+
+There are several scenarios where nested KVM can be useful, to name a
+few:
+
+- As a developer, you want to test your software on different operating
+  systems (OSes).  Instead of renting multiple VMs from a Cloud
+  Provider, using nested KVM lets you rent a large enough "guest
+  hypervisor" (level-1 guest).  This in turn allows you to create
+  multiple nested guests (level-2 guests), running different OSes, on
+  which you can develop and test your software.
+
+- Live migration of "guest hypervisors" and their nested guests, for
+  load balancing, disaster recovery, etc.
+
+- VM image creation tools (e.g. ``virt-install``,  etc) often run
+  their own VM, and users expect these to work inside a VM.
+
+- Some OSes use virtualization internally for security (e.g. to let
+  applications run safely in isolation).
+
+
+Enabling "nested" (x86)
+-----------------------
+
+From Linux kernel v4.19 onwards, the ``nested`` KVM parameter is enabled
+by default for Intel x86, but *not* for AMD.  (Though your Linux
+distribution might override this default.)
+
+In case you are running a Linux kernel older than v4.19, to enable
+nesting, set the ``nested`` KVM module parameter to ``Y`` or ``1``.  To
+persist this setting across reboots, you can add it in a config file, as
+shown below:
+
+1. On the bare metal host (L0), list the kernel modules and ensure that
+   the KVM modules::
+
+    $ lsmod | grep -i kvm
+    kvm_intel             133627  0
+    kvm                   435079  1 kvm_intel
+
+2. Show information for ``kvm_intel`` module::
+
+    $ modinfo kvm_intel | grep -i nested
+    parm:           nested:boolkvm                   435079  1 kvm_intel
+
+3. For the nested KVM configuration to persist across reboots, place the
+   below in ``/etc/modprobed/kvm_intel.conf`` (create the file if it
+   doesn't exist)::
+
+    $ cat /etc/modprobe.d/kvm_intel.conf
+    options kvm-intel nested=y
+
+4. Unload and re-load the KVM Intel module::
+
+    $ sudo rmmod kvm-intel
+    $ sudo modprobe kvm-intel
+
+5. Verify if the ``nested`` parameter for KVM is enabled::
+
+    $ cat /sys/module/kvm_intel/parameters/nested
+    Y
+
+For AMD hosts, the process is the same as above, except that the module
+name is ``kvm-amd``.
+
+
+Additional nested-related kernel parameters (x86)
+-------------------------------------------------
+
+If your hardware is sufficiently advanced (Intel Haswell processor or
+above which has newer hardware virt extensions), you might want to
+enable additional features: "Shadow VMCS (Virtual Machine Control
+Structure)", APIC Virtualization on your bare metal host (L0).
+Parameters for Intel hosts::
+
+    $ cat /sys/module/kvm_intel/parameters/enable_shadow_vmcs
+    Y
+
+    $ cat /sys/module/kvm_intel/parameters/enable_apicv
+    N
+
+    $ cat /sys/module/kvm_intel/parameters/ept
+    Y
+
+Again, to persist the above values across reboot, append them to
+``/etc/modprobe.d/kvm_intel.conf``::
+
+    options kvm-intel nested=y
+    options kvm-intel enable_shadow_vmcs=y
+    options kvm-intel enable_apivc=y
+    options kvm-intel ept=y
+
+.. note:: Depending on the hardware and kernel versions, some of the
+          above might be automatically enabled; so check before you do
+          the above.
+
+
+Starting a nested guest (x86)
+-----------------------------
+
+Once your bare metal host (L0) is configured for nesting, you should be
+able to start an L1 guest with::
+
+    $ qemu-kvm -cpu host [...]
+
+The above will pass through the host CPU's capabilities as-is to the
+gues); or for better live migration compatibility, use a named CPU
+model supported by QEMU. e.g.::
+
+    $ qemu-kvm -cpu Haswell-noTSX-IBRS,vmx=on
+
+then the guest hypervisor will subsequently be capable of running a
+nested guest with accelerated KVM.
+
+
+Enabling "nested" (s390x)
+-------------------------
+
+1. On the host hypervisor (L0), enable the ``nested`` parameter on
+   s390x::
+
+    $ rmmod kvm
+    $ modprobe kvm nested=1
+
+.. note:: On s390x, the kernel parameter ``hpage`` parameter is mutually
+          exclusive with the ``nested`` paramter; i.e. to have
+          ``nested`` enabled you _must_ disable the ``hpage`` parameter.
+
+2. The guest hypervisor (L1) must be allowed to have ``sie`` CPU
+   feature — with QEMU, this is possible by using "host passthrough"
+   (via the command-line ``-cpu host``).
+
+3. Now the KVM module can be enabled in the L1 (guest hypervisor)::
+
+    $ modprobe kvm
+
+
+Live migration with nested KVM
+------------------------------
+
+The below live migration scenarios should work as of Linux kernel 5.3
+and QEMU 4.2.0.  In all the below cases, L1 exposes ``/dev/kvm`` in
+it, i.e. the L2 guest is a "KVM-accelerated guest", not a "plain
+emulated guest" (as done by QEMU's TCG).
+
+- Migrating a nested guest (L2) to another L1 guest on the *same* bare
+  metal host.
+
+- Migrating a nested guest (L2) to another L1 guest on a *different*
+  bare metal host.
+
+- Migrating an L1 guest, with an *offline* nested guest in it, to
+  another bare metal host.
+
+- Migrating an L1 guest, with a  *live* nested guest in it, to another
+  bare metal host.
+
+Limitations on Linux kernel versions older than 5.3
+---------------------------------------------------
+
+On x86 systems-only (as this does *not* apply for s390x):
+
+On Linux kernel versions older than 5.3, once an L1 guest has started an
+L2 guest, the L1 guest would no longer capable of being migrated, saved,
+or loaded (refer to QEMU documentation on "save"/"load") until the L2
+guest shuts down.
+
+Attempting to migrate or save-and-load an L1 guest while an L2 guest is
+running will result in undefined behavior.  You might see a ``kernel
+BUG!`` entry in ``dmesg``, a kernel 'oops', or an outright kernel panic.
+Such a migrated or loaded L1 guest can no longer be considered stable or
+secure, and must be restarted.
+
+Migrating an L1 guest merely configured to support nesting, while not
+actually running L2 guests, is expected to function normally.
+Live-migrating an L2 guest from one L1 guest to another is also expected
+to succeed.
+
+Reporting bugs from "nested" setups
+-----------------------------------
+
+(This is written with x86 terminology in mind, but similar should apply
+for other architectures.)
+
+Debugging "nested" problems can involve sifting through log files across
+L0, L1 and L2; this can result in tedious back-n-forth between the bug
+reporter and the bug fixer.
+
+- Mention that you are in a "nested" setup.  If you are running any kind
+  of "nesting" at all, say so.  Unfortunately, this needs to be called
+  out because when reporting bugs, people tend to forget to even
+  *mention* that they're using nested virtualization.
+
+- Ensure you are actually running KVM on KVM.  Sometimes people do not
+  have KVM enabled for their guest hypervisor (L1), which results in
+  them running with pure emulation or what QEMU calls it as "TCG", but
+  they think they're running nested KVM.  Thus confusing "nested Virt"
+  (which could also mean, QEMU on KVM) with "nested KVM" (KVM on KVM).
+
+- What information to collect?  The following; it's not an exhaustive
+  list, but a very good starting point:
+
+  - Kernel, libvirt, and QEMU version from L0
+
+  - Kernel, libvirt and QEMU version from L1
+
+  - QEMU command-line of L1 -- preferably full log from
+    ``/var/log/libvirt/qemu/instance.log``
+
+  - QEMU command-line of L2 -- preferably full log from
+    ``/var/log/libvirt/qemu/instance.log``
+
+  - Full ``dmesg`` output from L0
+
+  - Full ``dmesg`` output from L1
+
+  - Output of: ``x86info -a`` (& ``lscpu``) from L0
+
+  - Output of: ``x86info -a`` (& ``lscpu``) from L1
+
+  - Output of: ``dmidecode`` from L0
+
+  - Output of: ``dmidecode`` from L1
```
#### [PATCH v2] kvm: Replace vcpu->swait with rcuwait
##### From: Davidlohr Bueso <dave@stgolabs.net>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Davidlohr Bueso <dave@stgolabs.net>
X-Patchwork-Id: 11499425
Return-Path: <SRS0=GaVw=6E=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 349816CA
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 20 Apr 2020 16:45:07 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 1CA8A2082E
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 20 Apr 2020 16:45:07 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726105AbgDTQpD (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 20 Apr 2020 12:45:03 -0400
Received: from mx2.suse.de ([195.135.220.15]:46888 "EHLO mx2.suse.de"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1725773AbgDTQpD (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 20 Apr 2020 12:45:03 -0400
X-Virus-Scanned: by amavisd-new at test-mx.suse.de
Received: from relay2.suse.de (unknown [195.135.220.254])
        by mx2.suse.de (Postfix) with ESMTP id CEBECACA2;
        Mon, 20 Apr 2020 16:44:59 +0000 (UTC)
Date: Mon, 20 Apr 2020 09:41:32 -0700
From: Davidlohr Bueso <dave@stgolabs.net>
To: tglx@linutronix.de, pbonzini@redhat.com
Cc: bigeasy@linutronix.de, peterz@infradead.org, rostedt@goodmis.org,
        torvalds@linux-foundation.org, will@kernel.org,
        joel@joelfernandes.org, linux-kernel@vger.kernel.org,
        kvm@vger.kernel.org, Paul Mackerras <paulus@ozlabs.org>,
        kvmarm@lists.cs.columbia.edu, linux-mips@vger.kernel.org,
        Davidlohr Bueso <dbueso@suse.de>
Subject: [PATCH v2] kvm: Replace vcpu->swait with rcuwait
Message-ID: <20200420164132.tjzk5ebx35m66yce@linux-p48b>
References: <20200324044453.15733-1-dave@stgolabs.net>
 <20200324044453.15733-4-dave@stgolabs.net>
MIME-Version: 1.0
Content-Disposition: inline
In-Reply-To: <20200324044453.15733-4-dave@stgolabs.net>
User-Agent: NeoMutt/20180716
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The use of any sort of waitqueue (simple or regular) for
wait/waking vcpus has always been an overkill and semantically
wrong. Because this is per-vcpu (which is blocked) there is
only ever a single waiting vcpu, thus no need for any sort of
queue.

As such, make use of the rcuwait primitive, with the following
considerations:

  - rcuwait already provides the proper barriers that serialize
  concurrent waiter and waker.

  - Task wakeup is done in rcu read critical region, with a
  stable task pointer.

  - Because there is no concurrency among waiters, we need
  not worry about rcuwait_wait_event() calls corrupting
  the wait->task. As a consequence, this saves the locking
  done in swait when modifying the queue. This also applies
  to per-vcore wait for powerpc kvm-hv.

The x86-tscdeadline_latency test mentioned in 8577370fb0cb
("KVM: Use simple waitqueue for vcpu->wq") shows that, on avg,
latency is reduced by around 15-20% with this change.

This patch also changes TASK_INTERRUPTIBLE for TASK_IDLE, as
kvm is (ab)using the former such that idle vcpus do no contribute
to the loadavg. Let use the correct semantics for this.

Cc: Paul Mackerras <paulus@ozlabs.org>
Cc: kvmarm@lists.cs.columbia.edu
Cc: linux-mips@vger.kernel.org
Signed-off-by: Davidlohr Bueso <dbueso@suse.de>
---
v2: Added missing semicolon in mips change.

The rest of the patches in this series continues to apply on tip,
as such I am only sending a v2 for this particular patch.

 arch/mips/kvm/mips.c                  |  6 ++----
 arch/powerpc/include/asm/kvm_book3s.h |  2 +-
 arch/powerpc/include/asm/kvm_host.h   |  2 +-
 arch/powerpc/kvm/book3s_hv.c          | 22 ++++++++--------------
 arch/powerpc/kvm/powerpc.c            |  2 +-
 arch/x86/kvm/lapic.c                  |  2 +-
 include/linux/kvm_host.h              | 10 +++++-----
 virt/kvm/arm/arch_timer.c             |  2 +-
 virt/kvm/arm/arm.c                    |  9 +++++----
 virt/kvm/async_pf.c                   |  3 +--
 virt/kvm/kvm_main.c                   | 31 +++++++++++--------------------
 11 files changed, 37 insertions(+), 54 deletions(-)

```
#### [PATCH v2] virtio: force spec specified alignment on types
##### From: "Michael S. Tsirkin" <mst@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: "Michael S. Tsirkin" <mst@redhat.com>
X-Patchwork-Id: 11499787
Return-Path: <SRS0=GaVw=6E=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 24FA381
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 20 Apr 2020 20:09:19 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 078D920782
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 20 Apr 2020 20:09:19 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="ZwmxI4M7"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726699AbgDTUJP (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 20 Apr 2020 16:09:15 -0400
Received: from us-smtp-2.mimecast.com ([207.211.31.81]:44177 "EHLO
        us-smtp-1.mimecast.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1725918AbgDTUJO (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 20 Apr 2020 16:09:14 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1587413352;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:content-type:content-type;
        bh=3cdUNjir+RJ29IhWI2+VQqP/CP/QCzQGQxj8crbt+CU=;
        b=ZwmxI4M7/usPm0jf49pg3ANFqH3rQY4bWt3+d9VrE6okk9eZtADXu5JDCPDTtlTfCOnKkS
        r2szUzTqMP8mjdjoa8+18kvWttXSVfiKm40punHVTYiXqbwCyYAP6tKjwOAZCEmobkGtZi
        to5sediPD4xlIk7tdFn6VqJjhNr8KlU=
Received: from mail-wm1-f71.google.com (mail-wm1-f71.google.com
 [209.85.128.71]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-5-QjVUmpDzOWiYTVKDZXGs6g-1; Mon, 20 Apr 2020 16:09:08 -0400
X-MC-Unique: QjVUmpDzOWiYTVKDZXGs6g-1
Received: by mail-wm1-f71.google.com with SMTP id l21so381339wmh.2
        for <kvm@vger.kernel.org>; Mon, 20 Apr 2020 13:09:08 -0700 (PDT)
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:date:from:to:cc:subject:message-id:mime-version
         :content-disposition;
        bh=3cdUNjir+RJ29IhWI2+VQqP/CP/QCzQGQxj8crbt+CU=;
        b=c6VK6oK6OXp2zTaRoU9HdZWL6QBR6Xfadqhw9URTiAR07ZhZ1mrabB+9UZnVUml7oQ
         299sD/KFttNgxXeES3IV7DuG5nf9r93W6W/HmZmvEoN/9ebIHOpHjRZqYgqOwCBfjdNS
         q+UWdr3/ac2R0l4ycLwB2jNoTN2dQLPWYtA0mhpcWUTwrZGd0/409K6qtPJKcWO39yTi
         0/N+nLwPNc42PXrLRIJDifNXsibMqXGWrgi2A8DnMJbYEk5TjI6R1MxnFaL+cysIu4WL
         WAeT8pS88Ptkp2z4mrGc7U5qUoJmvcXgQltt3QUPPsndpcN3ksOGIenUriVBEgQRVumP
         /jXw==
X-Gm-Message-State: AGi0Puab6A8mDyKp/y+Pdsr4GyAEUYyXjgofPpFM+fFgQGyE4rF//Bgd
        PmnnXBviCg0dFc8JMKkHL6D20TpgZV8++JogCQB4xhZAL9oh4pPo09xtWmYySeZ5QwI5K/Oax1v
        ZOHQbiIJoXsX8
X-Received: by 2002:adf:f48f:: with SMTP id
 l15mr14175271wro.161.1587413347519;
        Mon, 20 Apr 2020 13:09:07 -0700 (PDT)
X-Google-Smtp-Source: 
 APiQypLkaZVhyiGNviDtldj3DJMdeZ39eLj1tjCm5p8aa1AKRsrwnukiu6MtIA4c2rwxsEck4bJl5Q==
X-Received: by 2002:adf:f48f:: with SMTP id
 l15mr14175249wro.161.1587413347145;
        Mon, 20 Apr 2020 13:09:07 -0700 (PDT)
Received: from redhat.com (bzq-79-183-51-3.red.bezeqint.net. [79.183.51.3])
        by smtp.gmail.com with ESMTPSA id
 c83sm618373wmd.23.2020.04.20.13.09.05
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Mon, 20 Apr 2020 13:09:06 -0700 (PDT)
Date: Mon, 20 Apr 2020 16:09:04 -0400
From: "Michael S. Tsirkin" <mst@redhat.com>
To: linux-kernel@vger.kernel.org
Cc: Jason Wang <jasowang@redhat.com>, kvm@vger.kernel.org,
        virtualization@lists.linux-foundation.org, netdev@vger.kernel.org
Subject: [PATCH v2] virtio: force spec specified alignment on types
Message-ID: <20200420200550.254983-1-mst@redhat.com>
MIME-Version: 1.0
Content-Disposition: inline
X-Mailer: git-send-email 2.24.1.751.gd10ce2899c
X-Mutt-Fcc: =sent
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The ring element addresses are passed between components with different
alignments assumptions. Thus, if guest/userspace selects a pointer and
host then gets and dereferences it, we might need to decrease the
compiler-selected alignment to prevent compiler on the host from
assuming pointer is aligned.

This actually triggers on ARM with -mabi=apcs-gnu - which is a
deprecated configuration, but it seems safer to handle this
generally.

Note that userspace that allocates the memory is actually OK and does
not need to be fixed, but userspace that gets it from guest or another
process does need to be fixed. The later doesn't generally talk to the
kernel so while it might be buggy it's not talking to the kernel in the
buggy way - it's just using the header in the buggy way - so fixing
header and asking userspace to recompile is the best we can do.

I verified that the produced kernel binary on x86 is exactly identical
before and after the change.

Signed-off-by: Michael S. Tsirkin <mst@redhat.com>
---

Changes from v1:
	update vhost, vringh pointers to use the new typedefs

 drivers/vhost/vhost.c            |  8 +++----
 drivers/vhost/vhost.h            |  6 ++---
 drivers/vhost/vringh.c           |  6 ++---
 include/linux/vringh.h           |  6 ++---
 include/uapi/linux/virtio_ring.h | 38 +++++++++++++++++++++++---------
 5 files changed, 41 insertions(+), 23 deletions(-)

```
#### [PATCH v3] virtio: force spec specified alignment on types
##### From: "Michael S. Tsirkin" <mst@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: "Michael S. Tsirkin" <mst@redhat.com>
X-Patchwork-Id: 11499833
Return-Path: <SRS0=GaVw=6E=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 8A40181
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 20 Apr 2020 20:46:34 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 6D35120BED
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 20 Apr 2020 20:46:34 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="B/xDlFmV"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726788AbgDTUqa (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 20 Apr 2020 16:46:30 -0400
Received: from us-smtp-delivery-1.mimecast.com ([205.139.110.120]:54505 "EHLO
        us-smtp-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org
        with ESMTP id S1726677AbgDTUq3 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 20 Apr 2020 16:46:29 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1587415587;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:content-type:content-type;
        bh=zitm8y/YEtvxoae4RHGKvdioLUb/8tpbBBFZl1ezpPQ=;
        b=B/xDlFmV1aA/LcPiZwvO4ttyhmVnBuj3y8/Oy3JtC7+u69upANwIYdC1atpVwAH/Gz8j2c
        rtFZ9C8BJSpw6vpfx7a5aZVZHcKntkMKG8tF7UV/WmOV6xC2NFv8F2ale5m7sg1YN3evdJ
        TDTJWQdRsGfN2U0qJNEGl+Ez7nIZYEk=
Received: from mail-wm1-f72.google.com (mail-wm1-f72.google.com
 [209.85.128.72]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-254-GIJ2cTItND-klbXaKBV9ug-1; Mon, 20 Apr 2020 16:46:24 -0400
X-MC-Unique: GIJ2cTItND-klbXaKBV9ug-1
Received: by mail-wm1-f72.google.com with SMTP id y1so423742wmj.3
        for <kvm@vger.kernel.org>; Mon, 20 Apr 2020 13:46:24 -0700 (PDT)
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:date:from:to:cc:subject:message-id:mime-version
         :content-disposition;
        bh=zitm8y/YEtvxoae4RHGKvdioLUb/8tpbBBFZl1ezpPQ=;
        b=kn9VabQK5QkFZPFvTKgEkcfZpSA5VdGlsL/t2PISV+ZhAgxkaec2YUeoXMudfPnWeq
         P5SQLkLb+0JKYyKgEeoNq9etUoNxazwjeSwzAYvL8n1PeFRHi6FrpbNZ5njaFfvOZeo5
         6l+wC/kDkJwpuSEvhupvPbx+UZdSRVorMq/7t3I/nQ8gVKIHJIKC/XHqEo0pVw5IpQee
         pI8aN/zio7K2mL16B9LdJf3dsIenIm58Kq+gfN91XbnDMryL4N6IqhpEEfX9UnvXrS9i
         hU+ckhWs0MCd2R/HIO/KQGdU1L6Iv88AR3ROwN6PMwPeGKmACdjECfSNr6qladLExLS4
         4Jwg==
X-Gm-Message-State: AGi0PuYKElIc69WFGBAreSmuRFPe6WOpyQUXdjIIbyxKRAAlKWOZPbGy
        7+C7trCUiw7XVOxjiFaW/RUfvKXfIGj37Dsl32Aa6q4zuMCdPd7niZqbZWDABre8ZuNoTPrYQoj
        4WhZ8yizmeMF2
X-Received: by 2002:a1c:e906:: with SMTP id q6mr1207570wmc.62.1587415581307;
        Mon, 20 Apr 2020 13:46:21 -0700 (PDT)
X-Google-Smtp-Source: 
 APiQypKyJsF+0b/+QmhBX/Xb7KPgYRkuoZmP6Tl3OAkh2e8A5WhnWdTS0+NP9bpkrzJ76sID8W8HIQ==
X-Received: by 2002:a1c:e906:: with SMTP id q6mr1207549wmc.62.1587415581012;
        Mon, 20 Apr 2020 13:46:21 -0700 (PDT)
Received: from redhat.com (bzq-79-183-51-3.red.bezeqint.net. [79.183.51.3])
        by smtp.gmail.com with ESMTPSA id
 q187sm666370wma.41.2020.04.20.13.46.19
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Mon, 20 Apr 2020 13:46:20 -0700 (PDT)
Date: Mon, 20 Apr 2020 16:46:18 -0400
From: "Michael S. Tsirkin" <mst@redhat.com>
To: linux-kernel@vger.kernel.org
Cc: Jason Wang <jasowang@redhat.com>, kvm@vger.kernel.org,
        virtualization@lists.linux-foundation.org, netdev@vger.kernel.org
Subject: [PATCH v3] virtio: force spec specified alignment on types
Message-ID: <20200420204448.377168-1-mst@redhat.com>
MIME-Version: 1.0
Content-Disposition: inline
X-Mailer: git-send-email 2.24.1.751.gd10ce2899c
X-Mutt-Fcc: =sent
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The ring element addresses are passed between components with different
alignments assumptions. Thus, if guest/userspace selects a pointer and
host then gets and dereferences it, we might need to decrease the
compiler-selected alignment to prevent compiler on the host from
assuming pointer is aligned.

This actually triggers on ARM with -mabi=apcs-gnu - which is a
deprecated configuration, but it seems safer to handle this
generally.

Note that userspace that allocates the memory is actually OK and does
not need to be fixed, but userspace that gets it from guest or another
process does need to be fixed. The later doesn't generally talk to the
kernel so while it might be buggy it's not talking to the kernel in the
buggy way - it's just using the header in the buggy way - so fixing
header and asking userspace to recompile is the best we can do.

I verified that the produced kernel binary on x86 is exactly identical
before and after the change.

Signed-off-by: Michael S. Tsirkin <mst@redhat.com>
---

changes from v2:
	add vring_used_elem_t to ensure alignment for substructures
changes from v1:
	swicth all __user to the new typedefs

 drivers/vhost/vhost.c            |  8 +++---
 drivers/vhost/vhost.h            |  6 ++---
 drivers/vhost/vringh.c           |  6 ++---
 include/linux/vringh.h           |  6 ++---
 include/uapi/linux/virtio_ring.h | 43 ++++++++++++++++++++++++--------
 5 files changed, 45 insertions(+), 24 deletions(-)

```
#### [PATCH v4] vhost: disable for OABI
##### From: "Michael S. Tsirkin" <mst@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: "Michael S. Tsirkin" <mst@redhat.com>
X-Patchwork-Id: 11499099
Return-Path: <SRS0=GaVw=6E=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id B1BD01392
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 20 Apr 2020 14:34:35 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 9543320735
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 20 Apr 2020 14:34:35 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="TUAKkkcA"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729910AbgDTOee (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 20 Apr 2020 10:34:34 -0400
Received: from us-smtp-delivery-1.mimecast.com ([207.211.31.120]:25523 "EHLO
        us-smtp-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org
        with ESMTP id S1726895AbgDTOed (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 20 Apr 2020 10:34:33 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1587393270;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:content-type:content-type;
        bh=QKgQlmHl/vlNhHGtLDszGPS70GFdJJv30q0eyxymYP8=;
        b=TUAKkkcAPRD+FoHSsvNTrzV8G5iGoVXWH/ATz8QYO7UMUCPZ0bdTt8hj3xK3YI0rqVJTMj
        ZGcq/Uz5VSkbtwfwJTW1GNHAT+Okc7tLaa/fqTrIMA1C5CJDnxG3grOGtexsLmPw4xd0km
        amsroRdOFc+b9fi723Fa7Clle/vY/Mc=
Received: from mail-wm1-f70.google.com (mail-wm1-f70.google.com
 [209.85.128.70]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-329-qvEFNmO8PG2JlRpbFAF20A-1; Mon, 20 Apr 2020 10:34:27 -0400
X-MC-Unique: qvEFNmO8PG2JlRpbFAF20A-1
Received: by mail-wm1-f70.google.com with SMTP id o26so3576765wmh.1
        for <kvm@vger.kernel.org>; Mon, 20 Apr 2020 07:34:27 -0700 (PDT)
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:date:from:to:cc:subject:message-id:mime-version
         :content-disposition;
        bh=QKgQlmHl/vlNhHGtLDszGPS70GFdJJv30q0eyxymYP8=;
        b=RXJMTB1iv6HMn8iNJRXEIxYo/BxGmr3fydilj4xj1fOH2Fm6zKlRmQO95ZlZD1IWWw
         VT1qSGn42ZAw04mqyMrrj8U9dr64oczqS0bUuJbRaIdbgdwM6npj1JLl8CnIhaehZdBC
         1Qh7gjzutK9k0afMDVxCesf8wEVKsUjCcTaw01/wEXCgOturzAoqE3+LAkMHEiptshAX
         e4v60+gXVYZOaalgwkCapT5bPj+c2ZBqX0Rn/uPvW7knfDcHBNnj/jtil1xHze2rw+XR
         /j6g8Vd1ygvCKR0D0/XCafcwPOX93mijIpVmnDVbdUK4X7pxIIBrAHk4gqUvgz4cRO4q
         tBGA==
X-Gm-Message-State: AGi0PuYMiCg9e/WBWKjSEOXHRCd7tAjqJ0Lu1DJoNhtplrblWOnSz59x
        fjOjvi1L4LijrW+htD3Jrt4oHYlauP3VPGkxEjBbBa/08oyDSNqE0kJkz8OpfmgUiRKvmh9DuPt
        LzJ1LNHKvLFJ+
X-Received: by 2002:a5d:4e02:: with SMTP id p2mr19097331wrt.302.1587393266214;
        Mon, 20 Apr 2020 07:34:26 -0700 (PDT)
X-Google-Smtp-Source: 
 APiQypJPCB2aIBVyG+epiQn8wefNJaBqE0mL7KfjY5M7sLpr1ftDgKPHhXnntLSPOZw2XTiIctqPcQ==
X-Received: by 2002:a5d:4e02:: with SMTP id p2mr19097299wrt.302.1587393265925;
        Mon, 20 Apr 2020 07:34:25 -0700 (PDT)
Received: from redhat.com (bzq-79-183-51-3.red.bezeqint.net. [79.183.51.3])
        by smtp.gmail.com with ESMTPSA id
 u12sm1690368wmu.25.2020.04.20.07.34.24
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Mon, 20 Apr 2020 07:34:25 -0700 (PDT)
Date: Mon, 20 Apr 2020 10:34:23 -0400
From: "Michael S. Tsirkin" <mst@redhat.com>
To: linux-kernel@vger.kernel.org
Cc: Ard Biesheuvel <ardb@kernel.org>,
        Richard Earnshaw <Richard.Earnshaw@arm.com>,
        Sudeep Dutt <sudeep.dutt@intel.com>,
        Ashutosh Dixit <ashutosh.dixit@intel.com>,
        Arnd Bergmann <arnd@arndb.de>,
        Greg Kroah-Hartman <gregkh@linuxfoundation.org>,
        "David S. Miller" <davem@davemloft.net>,
        Jason Wang <jasowang@redhat.com>, netdev@vger.kernel.org,
        virtualization@lists.linux-foundation.org, kvm@vger.kernel.org,
        Christoph Hellwig <hch@infradead.org>
Subject: [PATCH v4] vhost: disable for OABI
Message-ID: <20200420143229.245488-1-mst@redhat.com>
MIME-Version: 1.0
Content-Disposition: inline
X-Mailer: git-send-email 2.24.1.751.gd10ce2899c
X-Mutt-Fcc: =sent
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

vhost is currently broken on the some ARM configs.

The reason is that the ring element addresses are passed between
components with different alignments assumptions. Thus, if
guest selects a pointer and host then gets and dereferences
it, then alignment assumed by the host's compiler might be
greater than the actual alignment of the pointer.
compiler on the host from assuming pointer is aligned.

This actually triggers on ARM with -mabi=apcs-gnu - which is a
deprecated configuration. With this OABI, compiler assumes that
all structures are 4 byte aligned - which is stronger than
virtio guarantees for available and used rings, which are
merely 2 bytes. Thus a guest without -mabi=apcs-gnu running
on top of host with -mabi=apcs-gnu will be broken.

The correct fix is to force alignment of structures - however
that is an intrusive fix that's best deferred until the next release.

We didn't previously support such ancient systems at all - this surfaced
after vdpa support prompted removing dependency of vhost on
VIRTULIZATION. So for now, let's just add something along the lines of

	depends on !ARM || AEABI

to the virtio Kconfig declaration, and add a comment that it has to do
with struct member alignment.

Note: we can't make VHOST and VHOST_RING themselves have
a dependency since these are selected. Add a new symbol for that.

We should be able to drop this dependency down the road.

Fixes: 20c384f1ea1a0bc7 ("vhost: refine vhost and vringh kconfig")
Suggested-by: Ard Biesheuvel <ardb@kernel.org>
Suggested-by: Richard Earnshaw <Richard.Earnshaw@arm.com>
Signed-off-by: Michael S. Tsirkin <mst@redhat.com>
---

changes from v3:
	update commit log clarifying the motivation and that
	it's a temporary fix.

	suggested by Christoph Hellwig

 drivers/misc/mic/Kconfig |  2 +-
 drivers/net/caif/Kconfig |  2 +-
 drivers/vdpa/Kconfig     |  2 +-
 drivers/vhost/Kconfig    | 17 +++++++++++++----
 4 files changed, 16 insertions(+), 7 deletions(-)

```
