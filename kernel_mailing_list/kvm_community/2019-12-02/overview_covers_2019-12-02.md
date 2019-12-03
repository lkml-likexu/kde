

#### [PATCH kernel RFC 0/4] powerpc/powenv/ioda: Allow huge DMA window at
##### From: Alexey Kardashevskiy <aik@ozlabs.ru>

```c
From patchwork Mon Dec  2 01:59:49 2019
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Alexey Kardashevskiy <aik@ozlabs.ru>
X-Patchwork-Id: 11268675
Return-Path: <SRS0=t74V=ZY=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 6B3C517F0
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon,  2 Dec 2019 02:09:42 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 49D6B215F1
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon,  2 Dec 2019 02:09:42 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727409AbfLBCJi (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Sun, 1 Dec 2019 21:09:38 -0500
Received: from 107-174-27-60-host.colocrossing.com ([107.174.27.60]:38182
 "EHLO
        ozlabs.ru" rhost-flags-OK-FAIL-OK-OK) by vger.kernel.org with ESMTP
        id S1727358AbfLBCJi (ORCPT <rfc822;kvm@vger.kernel.org>);
        Sun, 1 Dec 2019 21:09:38 -0500
Received: from fstn1-p1.ozlabs.ibm.com (localhost [IPv6:::1])
        by ozlabs.ru (Postfix) with ESMTP id AC719AE800ED;
        Sun,  1 Dec 2019 20:58:54 -0500 (EST)
From: Alexey Kardashevskiy <aik@ozlabs.ru>
To: linuxppc-dev@lists.ozlabs.org
Cc: David Gibson <david@gibson.dropbear.id.au>, kvm@vger.kernel.org,
        Alistair Popple <alistair@popple.id.au>,
        Alex Williamson <alex.williamson@redhat.com>,
        Oliver O'Halloran <oohall@gmail.com>,
        Alexey Kardashevskiy <aik@ozlabs.ru>
Subject: [PATCH kernel RFC 0/4] powerpc/powenv/ioda: Allow huge DMA window at
 4GB
Date: Mon,  2 Dec 2019 12:59:49 +1100
Message-Id: <20191202015953.127902-1-aik@ozlabs.ru>
X-Mailer: git-send-email 2.17.1
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Here is an attempt to support bigger DMA space for devices
supporting DMA masks less than 59 bits (GPUs come into mind
first). POWER9 PHBs have an option to map 2 windows at 0
and select a windows based on DMA address being below or above
4GB.

This adds the "iommu=iommu_bypass" kernel parameter and
supports VFIO+pseries machine - current this requires telling
upstream+unmodified QEMU about this via
-global spapr-pci-host-bridge.dma64_win_addr=0x100000000
or per-phb property. 4/4 advertises the new option but
there is no automation around it in QEMU (should it be?).

For now it is either 1<<59 or 4GB mode; dynamic switching is
not supported (could be via sysfs).

This is based on sha1
a6ed68d6468b Linus Torvalds "Merge tag 'drm-next-2019-11-27' of git://anongit.freedesktop.org/drm/drm".

Please comment. Thanks.



Alexey Kardashevskiy (4):
  powerpc/powernv/ioda: Rework for huge DMA window at 4GB
  powerpc/powernv/ioda: Allow smaller TCE table levels
  powerpc/powernv/phb4: Add 4GB IOMMU bypass mode
  vfio/spapr_tce: Advertise and allow a huge DMA windows at 4GB

 arch/powerpc/include/asm/iommu.h              |   1 +
 arch/powerpc/include/asm/opal-api.h           |  11 +-
 arch/powerpc/include/asm/opal.h               |   2 +
 arch/powerpc/platforms/powernv/pci.h          |   1 +
 include/uapi/linux/vfio.h                     |   2 +
 arch/powerpc/platforms/powernv/opal-call.c    |   2 +
 arch/powerpc/platforms/powernv/pci-ioda-tce.c |   4 +-
 arch/powerpc/platforms/powernv/pci-ioda.c     | 219 ++++++++++++++----
 drivers/vfio/vfio_iommu_spapr_tce.c           |  10 +-
 9 files changed, 202 insertions(+), 50 deletions(-)
```
#### [PATCH v3 0/5] KVM: X86: Cleanups on dest_mode and headers
##### From: Peter Xu <peterx@redhat.com>

```c
From patchwork Mon Dec  2 20:13:09 2019
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Peter Xu <peterx@redhat.com>
X-Patchwork-Id: 11269879
Return-Path: <SRS0=t74V=ZY=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 7958C112B
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon,  2 Dec 2019 20:13:20 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 4D98C20848
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon,  2 Dec 2019 20:13:20 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="hh7zvWu/"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728001AbfLBUNT (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 2 Dec 2019 15:13:19 -0500
Received: from us-smtp-1.mimecast.com ([207.211.31.81]:26533 "EHLO
        us-smtp-delivery-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S1727586AbfLBUNT (ORCPT
        <rfc822;kvm@vger.kernel.org>); Mon, 2 Dec 2019 15:13:19 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1575317598;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:content-type:content-type:
         content-transfer-encoding:content-transfer-encoding;
        bh=AAoHzUyrY/MGtK6MVYph2Nv7coxAjaKdNzJNELfvGio=;
        b=hh7zvWu/EmPaLwU0HVeOKSQ7vII0zoX82F31VxGcl5v/7449E86RR2Henbxri+G4+woJPa
        HI8b0Q//tVW7I7pYw+IG1Pp4B+l8lyFk9LT7jbjsApmKuu3TslFkYnjszJ3jgRt16iVzMh
        kk1tLCy5aMevOzV64oxfe8vgfzvvC2M=
Received: from mail-qv1-f70.google.com (mail-qv1-f70.google.com
 [209.85.219.70]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-173-awn2022RPpKOQRa1kgr8Jw-1; Mon, 02 Dec 2019 15:13:17 -0500
Received: by mail-qv1-f70.google.com with SMTP id g33so540954qvd.7
        for <kvm@vger.kernel.org>; Mon, 02 Dec 2019 12:13:16 -0800 (PST)
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:mime-version
         :content-transfer-encoding;
        bh=MeEk0ij29n0kTPi4OJez+UYNwIiLUI6R5zpd+TNY67M=;
        b=ueUSj1dJ1A6E7BfZO5O9q0bG59xcYa65n7Rp8E7+dh73EVI7YziEFd5naU8T6n+Bli
         Fv+epMu4Wnv9294Ix7cryWlWW+iQ9BQYwmUWau8D1BgaBa3M5tsBz9CHFNja8O6PCkp+
         XCn1hMbIost4AHtaqKMB3NOPiVTFFHY2HODHfHbO9xxcjsCmlFe7GuROtzjRNl8Iwpws
         oMptabuy7u2oo9Rld8dVBDOhuG6qSi881s6E8FjtirfLPdjpQgoYIE1U6FDOIgwYhjPS
         IrO39A8D6txvu+p4SzjqCYTy9aljCE0xXeWmzdYyIhmjLNIhIOWg88cQ6SKus7+qy/6O
         NiMg==
X-Gm-Message-State: APjAAAXQtcc6i4cTf/ARrFCSPDWtXzFGiriWqQ0hVaGIc5W2seyd5YS/
        fAUjRnGVuCQjEZF759Zh6fIH3uI56aqLtArt77Fbtz7/1HsvbpgZ5doTA8HlfsGe6XMLKfZQPCu
        zdKIP8RK6M5v4
X-Received: by 2002:ac8:607:: with SMTP id d7mr1330141qth.186.1575317596607;
        Mon, 02 Dec 2019 12:13:16 -0800 (PST)
X-Google-Smtp-Source: 
 APXvYqxEDymFkNuWxzKe4cUT0lCYk0JjSaaXOL4ga2ZDAhsswgDBqGmNFtJsj4EG2GiyhikKxlMgHA==
X-Received: by 2002:ac8:607:: with SMTP id d7mr1330123qth.186.1575317596342;
        Mon, 02 Dec 2019 12:13:16 -0800 (PST)
Received: from xz-x1.yyz.redhat.com ([104.156.64.74])
        by smtp.gmail.com with ESMTPSA id b6sm342410qtp.5.2019.12.02.12.13.15
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Mon, 02 Dec 2019 12:13:15 -0800 (PST)
From: Peter Xu <peterx@redhat.com>
To: linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Cc: Nitesh Narayan Lal <nitesh@redhat.com>,
        Paolo Bonzini <pbonzini@redhat.com>,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        peterx@redhat.com, Vitaly Kuznetsov <vkuznets@redhat.com>
Subject: [PATCH v3 0/5] KVM: X86: Cleanups on dest_mode and headers
Date: Mon,  2 Dec 2019 15:13:09 -0500
Message-Id: <20191202201314.543-1-peterx@redhat.com>
X-Mailer: git-send-email 2.21.0
MIME-Version: 1.0
X-MC-Unique: awn2022RPpKOQRa1kgr8Jw-1
X-Mimecast-Spam-Score: 0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

v3:
- address all the comments from both Vitaly and Sean
- since at it, added patches:
  "KVM: X86: Fix kvm_bitmap_or_dest_vcpus() to use irq shorthand"
  "KVM: X86: Drop KVM_APIC_SHORT_MASK and KVM_APIC_DEST_MASK"

Each patch explains itself.

Please have a look, thanks.

Peter Xu (5):
  KVM: X86: Fix kvm_bitmap_or_dest_vcpus() to use irq shorthand
  KVM: X86: Move irrelevant declarations out of ioapic.h
  KVM: X86: Use APIC_DEST_* macros properly in kvm_lapic_irq.dest_mode
  KVM: X86: Drop KVM_APIC_SHORT_MASK and KVM_APIC_DEST_MASK
  KVM: X86: Fix callers of kvm_apic_match_dest() to use correct macros

 arch/x86/include/asm/kvm_host.h |  5 +++++
 arch/x86/kvm/hyperv.c           |  1 +
 arch/x86/kvm/ioapic.c           | 19 ++++++++++++-------
 arch/x86/kvm/ioapic.h           |  6 ------
 arch/x86/kvm/irq.h              |  3 +++
 arch/x86/kvm/irq_comm.c         | 10 ++++++----
 arch/x86/kvm/lapic.c            |  5 +----
 arch/x86/kvm/lapic.h            |  7 ++++---
 arch/x86/kvm/svm.c              |  4 ++--
 arch/x86/kvm/x86.c              |  2 +-
 10 files changed, 35 insertions(+), 27 deletions(-)
```
