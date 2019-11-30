

#### [PATCH v2 00/14] video, drm, etc: constify fbops in struct fb_info
##### From: Jani Nikula <jani.nikula@intel.com>

```c
From patchwork Fri Nov 29 10:29:30 2019
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 8bit
X-Patchwork-Submitter: Jani Nikula <jani.nikula@intel.com>
X-Patchwork-Id: 11266895
Return-Path: <SRS0=D48H=ZV=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 29AAC195A
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 29 Nov 2019 10:30:01 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 118F0215F1
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 29 Nov 2019 10:30:01 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726800AbfK2KaA (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 29 Nov 2019 05:30:00 -0500
Received: from mga11.intel.com ([192.55.52.93]:27927 "EHLO mga11.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1725892AbfK2KaA (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 29 Nov 2019 05:30:00 -0500
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from orsmga008.jf.intel.com ([10.7.209.65])
  by fmsmga102.fm.intel.com with ESMTP/TLS/DHE-RSA-AES256-GCM-SHA384;
 29 Nov 2019 02:29:58 -0800
X-IronPort-AV: E=Sophos;i="5.69,257,1571727600";
   d="scan'208";a="203694628"
Received: from jnikula-mobl3.fi.intel.com (HELO localhost) ([10.237.66.161])
  by orsmga008-auth.jf.intel.com with ESMTP/TLS/DHE-RSA-AES256-GCM-SHA384;
 29 Nov 2019 02:29:50 -0800
From: Jani Nikula <jani.nikula@intel.com>
To: dri-devel@lists.freedesktop.org, linux-fbdev@vger.kernel.org
Cc: intel-gfx@lists.freedesktop.org, jani.nikula@intel.com,
 ville.syrjala@linux.intel.com, Andy Walls <awalls@md.metrocast.net>,
 Bernie Thompson <bernie@plugable.com>,
 =?utf-8?q?Bruno_Pr=C3=A9mont?= <bonbons@linux-vserver.org>,
 Daniel Vetter <daniel@ffwll.ch>, Hans Verkuil <hverkuil@xs4all.nl>,
 Jaya Kumar <jayalk@intworks.biz>, Kirti Wankhede <kwankhede@nvidia.com>,
 Miguel Ojeda Sandonis <miguel.ojeda.sandonis@gmail.com>, =?utf-8?q?Noralf_T?=
	=?utf-8?q?r=C3=B8nnes?= <noralf@tronnes.org>,
 Robin van der Gracht <robin@protonic.nl>,
 Steve Glendinning <steve.glendinning@shawell.net>, ivtv-devel@ivtvdriver.org,
 kvm@vger.kernel.org, linux-input@vger.kernel.org,
 linux-media@vger.kernel.org, linux-omap@vger.kernel.org
Subject: [PATCH v2 00/14] video, drm, etc: constify fbops in struct fb_info
Date: Fri, 29 Nov 2019 12:29:30 +0200
Message-Id: <cover.1575022735.git.jani.nikula@intel.com>
X-Mailer: git-send-email 2.20.1
MIME-Version: 1.0
Organization: Intel Finland Oy - BIC 0357606-4 - Westendinkatu 7, 02160 Espoo
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This is v2 of https://patchwork.freedesktop.org/series/70119/

I wanted to make our struct fb_ops const because we don't modify
it... and this is what I ended up with to fix it and a bunch of others.

I would appreciate acks to merge all this via the drm-misc tree. This is
especially important for patches 1-8 to reasonably get the job
done. Patches 9-14 are somewhat easier to merge at leisure afterwards,
but there really isn't much conflict potential IMO.

Daniel, please double-check me adding your Reviewed-by on the later
patches wasn't overzealous.

BR,
Jani.


Cc: Andy Walls <awalls@md.metrocast.net>
Cc: Bernie Thompson <bernie@plugable.com>
Cc: Bruno Prémont <bonbons@linux-vserver.org>
Cc: Daniel Vetter <daniel@ffwll.ch>
Cc: Hans Verkuil <hverkuil@xs4all.nl>
Cc: Jaya Kumar <jayalk@intworks.biz>
Cc: Kirti Wankhede <kwankhede@nvidia.com>
Cc: Miguel Ojeda Sandonis <miguel.ojeda.sandonis@gmail.com>
Cc: Noralf Trønnes <noralf@tronnes.org>
Cc: Robin van der Gracht <robin@protonic.nl>
Cc: Steve Glendinning <steve.glendinning@shawell.net>
Cc: Ville Syrjälä <ville.syrjala@linux.intel.com>
Cc: dri-devel@lists.freedesktop.org
Cc: ivtv-devel@ivtvdriver.org
Cc: kvm@vger.kernel.org
Cc: linux-fbdev@vger.kernel.org
Cc: linux-input@vger.kernel.org
Cc: linux-media@vger.kernel.org
Cc: linux-omap@vger.kernel.org


Jani Nikula (14):
  video: fb_defio: preserve user fb_ops
  drm/fb-helper: don't preserve fb_ops across deferred IO use
  video: smscufx: don't restore fb_mmap after deferred IO cleanup
  video: udlfb: don't restore fb_mmap after deferred IO cleanup
  video: fbdev: vesafb: modify the static fb_ops directly
  video: fbmem: use const pointer for fb_ops
  video: omapfb: use const pointer for fb_ops
  video: fbdev: make fbops member of struct fb_info a const pointer
  drm: constify fb ops across all drivers
  video: constify fb ops across all drivers
  HID: picoLCD: constify fb ops
  media: constify fb ops across all drivers
  samples: vfio-mdev: constify fb ops
  auxdisplay: constify fb ops

 drivers/auxdisplay/cfag12864bfb.c             |  2 +-
 drivers/auxdisplay/ht16k33.c                  |  2 +-
 drivers/gpu/drm/amd/amdgpu/amdgpu_fb.c        |  2 +-
 drivers/gpu/drm/armada/armada_fbdev.c         |  2 +-
 drivers/gpu/drm/drm_fb_helper.c               | 27 +++----------------
 drivers/gpu/drm/exynos/exynos_drm_fbdev.c     |  2 +-
 .../gpu/drm/hisilicon/hibmc/hibmc_drm_fbdev.c |  2 +-
 drivers/gpu/drm/i915/display/intel_fbdev.c    |  2 +-
 drivers/gpu/drm/msm/msm_fbdev.c               |  2 +-
 drivers/gpu/drm/nouveau/nouveau_fbcon.c       |  4 +--
 drivers/gpu/drm/omapdrm/omap_fbdev.c          |  2 +-
 drivers/gpu/drm/radeon/radeon_fb.c            |  2 +-
 drivers/gpu/drm/rockchip/rockchip_drm_fbdev.c |  2 +-
 drivers/gpu/drm/tegra/fb.c                    |  2 +-
 drivers/gpu/drm/vmwgfx/vmwgfx_fb.c            |  2 +-
 drivers/hid/hid-picolcd_fb.c                  |  3 +--
 drivers/media/pci/ivtv/ivtvfb.c               |  3 +--
 drivers/media/platform/vivid/vivid-osd.c      |  3 +--
 drivers/video/fbdev/68328fb.c                 |  2 +-
 drivers/video/fbdev/acornfb.c                 |  2 +-
 drivers/video/fbdev/amba-clcd.c               |  2 +-
 drivers/video/fbdev/amifb.c                   |  2 +-
 drivers/video/fbdev/arcfb.c                   |  2 +-
 drivers/video/fbdev/arkfb.c                   |  2 +-
 drivers/video/fbdev/asiliantfb.c              |  2 +-
 drivers/video/fbdev/atmel_lcdfb.c             |  2 +-
 drivers/video/fbdev/aty/aty128fb.c            |  2 +-
 drivers/video/fbdev/aty/atyfb_base.c          |  2 +-
 drivers/video/fbdev/aty/radeon_base.c         |  2 +-
 drivers/video/fbdev/au1100fb.c                |  2 +-
 drivers/video/fbdev/au1200fb.c                |  2 +-
 drivers/video/fbdev/broadsheetfb.c            |  2 +-
 drivers/video/fbdev/bw2.c                     |  2 +-
 drivers/video/fbdev/carminefb.c               |  2 +-
 drivers/video/fbdev/cg14.c                    |  2 +-
 drivers/video/fbdev/cg3.c                     |  2 +-
 drivers/video/fbdev/cg6.c                     |  2 +-
 drivers/video/fbdev/chipsfb.c                 |  2 +-
 drivers/video/fbdev/cirrusfb.c                |  2 +-
 drivers/video/fbdev/clps711x-fb.c             |  2 +-
 drivers/video/fbdev/cobalt_lcdfb.c            |  2 +-
 drivers/video/fbdev/controlfb.c               |  2 +-
 drivers/video/fbdev/core/fb_defio.c           |  3 ---
 drivers/video/fbdev/core/fbmem.c              | 19 ++++++++-----
 drivers/video/fbdev/cyber2000fb.c             |  2 +-
 drivers/video/fbdev/da8xx-fb.c                |  2 +-
 drivers/video/fbdev/dnfb.c                    |  2 +-
 drivers/video/fbdev/efifb.c                   |  2 +-
 drivers/video/fbdev/ep93xx-fb.c               |  2 +-
 drivers/video/fbdev/fb-puv3.c                 |  2 +-
 drivers/video/fbdev/ffb.c                     |  2 +-
 drivers/video/fbdev/fm2fb.c                   |  2 +-
 drivers/video/fbdev/fsl-diu-fb.c              |  2 +-
 drivers/video/fbdev/g364fb.c                  |  2 +-
 drivers/video/fbdev/gbefb.c                   |  2 +-
 drivers/video/fbdev/geode/gx1fb_core.c        |  2 +-
 drivers/video/fbdev/geode/gxfb_core.c         |  2 +-
 drivers/video/fbdev/geode/lxfb_core.c         |  2 +-
 drivers/video/fbdev/goldfishfb.c              |  2 +-
 drivers/video/fbdev/grvga.c                   |  2 +-
 drivers/video/fbdev/gxt4500.c                 |  2 +-
 drivers/video/fbdev/hecubafb.c                |  2 +-
 drivers/video/fbdev/hgafb.c                   |  2 +-
 drivers/video/fbdev/hitfb.c                   |  2 +-
 drivers/video/fbdev/hpfb.c                    |  2 +-
 drivers/video/fbdev/hyperv_fb.c               |  2 +-
 drivers/video/fbdev/i740fb.c                  |  2 +-
 drivers/video/fbdev/imsttfb.c                 |  2 +-
 drivers/video/fbdev/imxfb.c                   |  2 +-
 drivers/video/fbdev/intelfb/intelfbdrv.c      |  2 +-
 drivers/video/fbdev/kyro/fbdev.c              |  2 +-
 drivers/video/fbdev/leo.c                     |  2 +-
 drivers/video/fbdev/macfb.c                   |  2 +-
 drivers/video/fbdev/matrox/matroxfb_crtc2.c   |  2 +-
 drivers/video/fbdev/maxinefb.c                |  2 +-
 drivers/video/fbdev/mb862xx/mb862xxfbdrv.c    |  2 +-
 drivers/video/fbdev/mbx/mbxfb.c               |  2 +-
 drivers/video/fbdev/metronomefb.c             |  2 +-
 drivers/video/fbdev/mmp/fb/mmpfb.c            |  2 +-
 drivers/video/fbdev/mx3fb.c                   |  5 ++--
 drivers/video/fbdev/neofb.c                   |  2 +-
 drivers/video/fbdev/nvidia/nvidia.c           |  2 +-
 drivers/video/fbdev/ocfb.c                    |  2 +-
 drivers/video/fbdev/offb.c                    |  2 +-
 drivers/video/fbdev/omap/omapfb_main.c        |  2 +-
 .../video/fbdev/omap2/omapfb/omapfb-main.c    |  2 +-
 drivers/video/fbdev/p9100.c                   |  2 +-
 drivers/video/fbdev/platinumfb.c              |  2 +-
 drivers/video/fbdev/pm2fb.c                   |  2 +-
 drivers/video/fbdev/pm3fb.c                   |  2 +-
 drivers/video/fbdev/pmag-aa-fb.c              |  2 +-
 drivers/video/fbdev/pmag-ba-fb.c              |  2 +-
 drivers/video/fbdev/pmagb-b-fb.c              |  2 +-
 drivers/video/fbdev/ps3fb.c                   |  2 +-
 drivers/video/fbdev/pvr2fb.c                  |  2 +-
 drivers/video/fbdev/pxa168fb.c                |  2 +-
 drivers/video/fbdev/pxafb.c                   |  4 +--
 drivers/video/fbdev/q40fb.c                   |  2 +-
 drivers/video/fbdev/riva/fbdev.c              |  2 +-
 drivers/video/fbdev/s3c-fb.c                  |  2 +-
 drivers/video/fbdev/s3c2410fb.c               |  2 +-
 drivers/video/fbdev/s3fb.c                    |  2 +-
 drivers/video/fbdev/sa1100fb.c                |  2 +-
 drivers/video/fbdev/savage/savagefb_driver.c  |  2 +-
 drivers/video/fbdev/sh7760fb.c                |  2 +-
 drivers/video/fbdev/sh_mobile_lcdcfb.c        |  4 +--
 drivers/video/fbdev/simplefb.c                |  2 +-
 drivers/video/fbdev/sis/sis_main.c            |  2 +-
 drivers/video/fbdev/skeletonfb.c              |  2 +-
 drivers/video/fbdev/sm712fb.c                 |  2 +-
 drivers/video/fbdev/smscufx.c                 |  3 +--
 drivers/video/fbdev/ssd1307fb.c               |  2 +-
 drivers/video/fbdev/sstfb.c                   |  2 +-
 drivers/video/fbdev/stifb.c                   |  2 +-
 drivers/video/fbdev/sunxvr1000.c              |  2 +-
 drivers/video/fbdev/sunxvr2500.c              |  2 +-
 drivers/video/fbdev/sunxvr500.c               |  2 +-
 drivers/video/fbdev/tcx.c                     |  2 +-
 drivers/video/fbdev/tdfxfb.c                  |  2 +-
 drivers/video/fbdev/tgafb.c                   |  2 +-
 drivers/video/fbdev/tmiofb.c                  |  2 +-
 drivers/video/fbdev/tridentfb.c               |  2 +-
 drivers/video/fbdev/udlfb.c                   |  1 -
 drivers/video/fbdev/uvesafb.c                 |  2 +-
 drivers/video/fbdev/valkyriefb.c              |  2 +-
 drivers/video/fbdev/vesafb.c                  |  6 ++---
 drivers/video/fbdev/vfb.c                     |  2 +-
 drivers/video/fbdev/vga16fb.c                 |  2 +-
 drivers/video/fbdev/vt8500lcdfb.c             |  2 +-
 drivers/video/fbdev/vt8623fb.c                |  2 +-
 drivers/video/fbdev/w100fb.c                  |  2 +-
 drivers/video/fbdev/wm8505fb.c                |  2 +-
 drivers/video/fbdev/xen-fbfront.c             |  2 +-
 drivers/video/fbdev/xilinxfb.c                |  2 +-
 include/linux/fb.h                            |  2 +-
 samples/vfio-mdev/mdpy-fb.c                   |  2 +-
 136 files changed, 156 insertions(+), 175 deletions(-)
```
#### [PATCH v2 0/3] KVM: X86: Cleanups on dest_mode and headers
##### From: Peter Xu <peterx@redhat.com>

```c
From patchwork Fri Nov 29 16:32:31 2019
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Peter Xu <peterx@redhat.com>
X-Patchwork-Id: 11267339
Return-Path: <SRS0=D48H=ZV=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 6DC1114B7
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 29 Nov 2019 16:32:41 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 4C2E221736
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 29 Nov 2019 16:32:41 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="S3zxl2u7"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727028AbfK2Qcj (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 29 Nov 2019 11:32:39 -0500
Received: from us-smtp-delivery-1.mimecast.com ([207.211.31.120]:45436 "EHLO
        us-smtp-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org
        with ESMTP id S1726608AbfK2Qcj (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 29 Nov 2019 11:32:39 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1575045158;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:content-type:content-type:
         content-transfer-encoding:content-transfer-encoding;
        bh=9V/qFvH8waqtXVKvhRpmWCEM/9qP0sAeZeU83cy8EOE=;
        b=S3zxl2u7OacaWD/m2W8RQhJXmuV7EEVAXmBkH1S0n6gH8kJ9uvTgHmcndmLjMmW3JyauZd
        1TBa23TcFcqyVJG7mC9fSjtzrf+2Db/rcALIvQLjsPL0jPYLel7+BgF6m2iJcqVXta1DID
        c3GMlboYEGwjR9W9Zk/tGeyVeGbP2/Y=
Received: from mail-qv1-f70.google.com (mail-qv1-f70.google.com
 [209.85.219.70]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-87-Jif7Uz9rNsy4cEGHlBvNbQ-1; Fri, 29 Nov 2019 11:32:37 -0500
Received: by mail-qv1-f70.google.com with SMTP id y9so7400431qvi.10
        for <kvm@vger.kernel.org>; Fri, 29 Nov 2019 08:32:37 -0800 (PST)
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:mime-version
         :content-transfer-encoding;
        bh=5iCofYmIjfyUSG8vHZf7wpoJnDoheL6AALy8kyz1tx8=;
        b=nraLA4io4oGKokG3v3KgSA0VAcL9yQ4Jbot9w1ST1wuMlHj7t9iGCMZGigj6B315Uc
         xub1A0pO6eV4u6PB5gZSHHsOQToZROYDgTfH8oWc1hW30ISkhU9NiI2E1gCKN+SGHcQf
         l+p8quSco+VYDqajDk//4Hl8aqeKdQ7j+oCNo2uFZzMb4T58p37MjI/gHNyOh9kM9sDu
         CjOivsewjI9MpjBDkCBEog9IPpXbJTIUmFxjbw3BwP7Dr9u/z1sr8SDLyO4Sy1+EqUYm
         wD9NUKbJRhe/afEOMGizITZkHLwUTXQXlCZEb6n6IEWKalXqPQ9Ktt/cbPtPce0ZtTJm
         zvFg==
X-Gm-Message-State: APjAAAUk0WpRh1/Fv3ehzC6b8dWNdbwQKBOOflYo3JNKoi+DlG6VaFhr
        1KeCqwHsCJF/xcs33JMluIiApQIiw/9HQd33t8L3i4Rygmsf3ImSZQHiW4zHOjGP6XnNp1Nt6/T
        +yRuAJDMu/XtW
X-Received: by 2002:a05:620a:2f1:: with SMTP id
 a17mr9045639qko.252.1575045156580;
        Fri, 29 Nov 2019 08:32:36 -0800 (PST)
X-Google-Smtp-Source: 
 APXvYqwt6klFGFPdiFCxtdNXCaWr4i8+5EKri2pR8sDM3UzAXUglAuAkDeGNQx+NxQAmWUnSI1w0ew==
X-Received: by 2002:a05:620a:2f1:: with SMTP id
 a17mr9045611qko.252.1575045156321;
        Fri, 29 Nov 2019 08:32:36 -0800 (PST)
Received: from xz-x1.yyz.redhat.com ([104.156.64.74])
        by smtp.gmail.com with ESMTPSA id
 d9sm4568329qtj.52.2019.11.29.08.32.35
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Fri, 29 Nov 2019 08:32:35 -0800 (PST)
From: Peter Xu <peterx@redhat.com>
To: linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Cc: Nitesh Narayan Lal <nitesh@redhat.com>,
        Paolo Bonzini <pbonzini@redhat.com>,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        peterx@redhat.com, Vitaly Kuznetsov <vkuznets@redhat.com>
Subject: [PATCH v2 0/3] KVM: X86: Cleanups on dest_mode and headers
Date: Fri, 29 Nov 2019 11:32:31 -0500
Message-Id: <20191129163234.18902-1-peterx@redhat.com>
X-Mailer: git-send-email 2.21.0
MIME-Version: 1.0
X-MC-Unique: Jif7Uz9rNsy4cEGHlBvNbQ-1
X-Mimecast-Spam-Score: 0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Each patch explains itself.

Please have a look, thanks.

Peter Xu (3):
  KVM: X86: Some cleanups in ioapic.h/lapic.h
  KVM: X86: Use APIC_DEST_* macros properly
  KVM: X86: Fixup kvm_apic_match_dest() dest_mode parameter

 arch/x86/kvm/ioapic.c   | 9 ++++++---
 arch/x86/kvm/ioapic.h   | 6 ------
 arch/x86/kvm/irq_comm.c | 7 ++++---
 arch/x86/kvm/lapic.c    | 5 +++--
 arch/x86/kvm/lapic.h    | 7 +++++--
 arch/x86/kvm/x86.c      | 2 +-
 6 files changed, 19 insertions(+), 17 deletions(-)
```
#### [PATCH v8 00/10] Enable Sub-Page Write Protection Support
##### From: Yang Weijiang <weijiang.yang@intel.com>

```c
From patchwork Fri Nov 29 17:26:59 2019
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Yang Weijiang <weijiang.yang@intel.com>
X-Patchwork-Id: 11267403
Return-Path: <SRS0=D48H=ZV=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 8C774175D
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 29 Nov 2019 17:25:34 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 65DC3208E4
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 29 Nov 2019 17:25:34 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727030AbfK2RZ3 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 29 Nov 2019 12:25:29 -0500
Received: from mga14.intel.com ([192.55.52.115]:64167 "EHLO mga14.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726909AbfK2RZ2 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 29 Nov 2019 12:25:28 -0500
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from fmsmga002.fm.intel.com ([10.253.24.26])
  by fmsmga103.fm.intel.com with ESMTP/TLS/DHE-RSA-AES256-GCM-SHA384;
 29 Nov 2019 09:25:28 -0800
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.69,257,1571727600";
   d="scan'208";a="241108952"
Received: from unknown (HELO local-michael-cet-test.sh.intel.com)
 ([10.239.159.128])
  by fmsmga002.fm.intel.com with ESMTP; 29 Nov 2019 09:25:26 -0800
From: Yang Weijiang <weijiang.yang@intel.com>
To: kvm@vger.kernel.org, linux-kernel@vger.kernel.org,
        pbonzini@redhat.com, jmattson@google.com,
        sean.j.christopherson@intel.com
Cc: yu.c.zhang@linux.intel.com, alazar@bitdefender.com,
        edwin.zhai@intel.com, Yang Weijiang <weijiang.yang@intel.com>
Subject: [PATCH v8 00/10] Enable Sub-Page Write Protection Support
Date: Sat, 30 Nov 2019 01:26:59 +0800
Message-Id: <20191129172709.11347-1-weijiang.yang@intel.com>
X-Mailer: git-send-email 2.17.2
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

EPT-Based Sub-Page write Protection(SPP) allows Virtual Machine Monitor(VMM)
specify write-permission for guest physical memory at a sub-page(128 byte)
granularity. When SPP works, HW enforces write-access check for sub-pages
within a protected 4KB page.

The feature targets to provide fine-grained memory protection for
usages such as memory guard and VM introspection etc.

SPP is active when the "sub-page write protection" (bit 23) is 1 in
Secondary VM-Execution Controls. The feature is backed with a Sub-Page
Permission Table(SPPT), and subpage permission vector is stored in the
leaf entry of SPPT. The root page is referenced via a Sub-Page Permission
Table Pointer (SPPTP) in VMCS.

To enable SPP for guest memory, the guest page should be first mapped
to a 4KB EPT entry, then set SPP bit 61 of the corresponding entry. 
While HW walks EPT, it traverses SPPT with the gpa to look up the sub-page
permission vector within SPPT leaf entry. If the corresponding bit is set,
write to sub-page is permitted, otherwise, SPP induced EPT violation is generated.

This patch serial passed SPP function test and selftest on Ice-Lake platform.

Please refer to the SPP introduction document in this patch set and
Intel SDM for details:

Intel SDM:
https://software.intel.com/sites/default/files/managed/39/c5/325462-sdm-vol-1-2abcd-3abcd.pdf

Patch 1: Documentation for SPP and related API.
Patch 2: Add control flags for Sub-Page Protection(SPP).
Patch 3: Add SPP Table setup functions.
Patch 4: Add functions to create/destroy SPP bitmap block.
Patch 5: Introduce user-space SPP IOCTLs.
Patch 6: Set up SPP paging table at vmentry/vmexit.
Patch 7: Enable Lazy mode SPP protection.
Patch 8: Handle SPP protected pages when VM memory changes.
Patch 9: Add SPP protection check in emulation case.
Patch 10: SPP selftest.

Change logs:
V7 -> V8:
  1. Changed ioctl interface definition per Paolo's comments.
  2. Replaced SPP_INIT ioctl funciton with KVM_ENABLE_CAP.
  3. Removed SPP bit from X86 feature word.
  4. Returned instruction length to user-space when SPP induced EPT
     violation happens, this is to provide flexibility to use SPP,
     revert write or track write.
  5. Modified selftest application and added into this serial.
  6. Simplified SPP permission vector check.
  7. Moved spp.c and spp.h to kvm/mmu folder.
  8. Other code fix according to Paolo's feedback and testing.

V6 -> V7:
  1. Configured all available protected pages once SPP induced vmexit
     happens since there's no PRESENT bit in SPPT leaf entry.
  2. Changed SPP protection check flow in tdp_page_fault().
  3. Code refactor and minior fixes.

V5 -> V6:
  1. Added SPP protection patch for emulation cases per Jim's review.
  2. Modified documentation and added API description per Jim's review.
  3. Other minior changes suggested by Jim.

V4 -> V5:
  1. Enable SPP support for Hugepage(1GB/2MB) to extend application.
  2. Make SPP miss vm-exit handler as the unified place to set up SPPT.
  3. If SPP protected pages are access-tracked or dirty-page-tracked,
     store SPP flag in reserved address bit, restore it in
     fast_page_fault() handler.
  4. Move SPP specific functions to vmx/spp.c and vmx/spp.h
  5. Rebased code to kernel v5.3
  6. Other change suggested by KVM community.
  
V3 -> V4:
  1. Modified documentation to make it consistent with patches.
  2. Allocated SPPT root page in init_spp() instead of vmx_set_cr3() to
     avoid SPPT miss error.
  3. Added back co-developers and sign-offs.

V2 -> V3:                                                                
  1. Rebased patches to kernel 5.1 release                                
  2. Deferred SPPT setup to EPT fault handler if the page is not
     available while set_subpage() is being called.
  3. Added init IOCTL to reduce extra cost if SPP is not used.
  4. Refactored patch structure, cleaned up cross referenced functions.
  5. Added code to deal with memory swapping/migration/shrinker cases.

V2 -> V1:
  1. Rebased to 4.20-rc1
  2. Move VMCS change to a separated patch.
  3. Code refine and Bug fix 


Yang Weijiang (10):
  Documentation: Introduce EPT based Subpage Protection and related APIs
  vmx: spp: Add control flags for Sub-Page Protection(SPP)
  mmu: spp: Add SPP Table setup functions
  mmu: spp: Add functions to operate SPP access bitmap
  x86: spp: Introduce user-space SPP IOCTLs
  vmx: spp: Set up SPP paging table at vmentry/vmexit
  mmu: spp: Enable Lazy mode SPP protection
  mmu: spp: Handle SPP protected pages when VM memory changes
  x86: spp: Add SPP protection check in emulation
  kvm: selftests: selftest for Sub-Page protection

 Documentation/virt/kvm/api.txt                |  38 ++
 Documentation/virtual/kvm/spp_kvm.txt         | 180 ++++++
 arch/x86/include/asm/kvm_host.h               |  11 +-
 arch/x86/include/asm/vmx.h                    |  10 +
 arch/x86/include/uapi/asm/vmx.h               |   2 +
 arch/x86/kvm/mmu.h                            |   2 +
 arch/x86/kvm/mmu/mmu.c                        |  75 ++-
 arch/x86/kvm/mmu/spp.c                        | 611 ++++++++++++++++++
 arch/x86/kvm/mmu/spp.h                        |  35 +
 arch/x86/kvm/vmx/capabilities.h               |   5 +
 arch/x86/kvm/vmx/vmx.c                        | 102 +++
 arch/x86/kvm/x86.c                            | 134 +++-
 include/uapi/linux/kvm.h                      |  18 +
 tools/testing/selftests/kvm/Makefile          |   2 +-
 tools/testing/selftests/kvm/lib/kvm_util.c    |   1 +
 tools/testing/selftests/kvm/x86_64/spp_test.c | 234 +++++++
 16 files changed, 1455 insertions(+), 5 deletions(-)
 create mode 100644 Documentation/virtual/kvm/spp_kvm.txt
 create mode 100644 arch/x86/kvm/mmu/spp.c
 create mode 100644 arch/x86/kvm/mmu/spp.h
 create mode 100644 tools/testing/selftests/kvm/x86_64/spp_test.c
```
#### [PATCH RFC 00/15] KVM: Dirty ring interface
##### From: Peter Xu <peterx@redhat.com>

```c
From patchwork Fri Nov 29 21:32:27 2019
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Peter Xu <peterx@redhat.com>
X-Patchwork-Id: 11267621
Return-Path: <SRS0=D48H=ZV=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 95610109A
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 29 Nov 2019 21:33:05 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 67395206B5
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 29 Nov 2019 21:33:05 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="jSNTEX5O"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727187AbfK2Vcu (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 29 Nov 2019 16:32:50 -0500
Received: from us-smtp-1.mimecast.com ([205.139.110.61]:49966 "EHLO
        us-smtp-delivery-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S1727116AbfK2Vcu (ORCPT
        <rfc822;kvm@vger.kernel.org>); Fri, 29 Nov 2019 16:32:50 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1575063169;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:content-type:content-type:
         content-transfer-encoding:content-transfer-encoding;
        bh=peI3w5GhWEX1JieJHH29KyaSX4w2AsTjOin5SLB/5Gw=;
        b=jSNTEX5OfiErFkF8aJvja4ywZY9ZK6PYxAMszHX4xtvrXwQZQKE/B0kFm/6sIQE5OH1qwJ
        naWT5q9y9lVYVCo34HLhnJSkGu3o4bkddnLetn3jKtYbztuCw60H3mUG0T6KCN23RuXJz8
        lUXm3wq3yMZt4AQkHa+sEOJq7CfiFas=
Received: from mail-qv1-f71.google.com (mail-qv1-f71.google.com
 [209.85.219.71]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-358-5OIN4PcGNI2DbeqWSDHIXg-1; Fri, 29 Nov 2019 16:32:45 -0500
Received: by mail-qv1-f71.google.com with SMTP id q2so19609884qvo.23
        for <kvm@vger.kernel.org>; Fri, 29 Nov 2019 13:32:45 -0800 (PST)
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:mime-version
         :content-transfer-encoding;
        bh=cn7j7/8SJgeM/ER61fZ1AdZGSd2mYCJ7pUgcBKPF2KQ=;
        b=M9Z1kNk/KCnC3ihrbHEO0DJbfi8mBlisq4QevcLOr+/2D5LqPifgw7xRLRb1RreM1H
         +N5r9jTxU8w1DNWHZnGdcD/0+cA6ZJEhxjeSUXsx5LHoZ9ox9ly9h39lSpu8uI4c920B
         Uj68bQQHKAkO0hj18aH+Ugweu+MCADUdXw+u6NhMqeQrasd39WLvg/SDh8iISLG3ffpp
         5Iu+AMU9ljOewOdn/3Ke+LIxF6i6QjUvdXWaGMJkNzVOF7anG3rmZxpUkSeFWW/q92qU
         n74FqpZZMl09Nz3UilYTWMEJjfF4kaUL/wdUVMVOxG9RtJPS5tUOqos5mDti+/w5+6K8
         TYXg==
X-Gm-Message-State: APjAAAWNZaFjE+Ur5aa/n/0ArLqneEvG2ggmGZ8yKEGX5KiR3qRV4ooY
        PY/zOznrw/FlnlnhPIziWm9+GUZedrNP76+jgVEZKzHGb+8M4WS6Uwx7B/fHYQIS1AETTlCwpIv
        +uq5/6R+ZFopc
X-Received: by 2002:ad4:588d:: with SMTP id
 dz13mr19982295qvb.86.1575063164827;
        Fri, 29 Nov 2019 13:32:44 -0800 (PST)
X-Google-Smtp-Source: 
 APXvYqy5eIATWxerwmd03ez0vmrXtvk2z5PAQi557Z+8gFzf+IEvRetJH80wrZlItjYLRMnxc+PPpA==
X-Received: by 2002:ad4:588d:: with SMTP id
 dz13mr19982258qvb.86.1575063164469;
        Fri, 29 Nov 2019 13:32:44 -0800 (PST)
Received: from xz-x1.yyz.redhat.com ([104.156.64.74])
        by smtp.gmail.com with ESMTPSA id
 n5sm10634817qkf.48.2019.11.29.13.32.43
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Fri, 29 Nov 2019 13:32:43 -0800 (PST)
From: Peter Xu <peterx@redhat.com>
To: linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Cc: Paolo Bonzini <pbonzini@redhat.com>, Cao Lei <Lei.Cao@stratus.com>,
        peterx@redhat.com, "Dr . David Alan Gilbert" <dgilbert@redhat.com>,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>
Subject: [PATCH RFC 00/15] KVM: Dirty ring interface
Date: Fri, 29 Nov 2019 16:32:27 -0500
Message-Id: <20191129213242.17144-1-peterx@redhat.com>
X-Mailer: git-send-email 2.21.0
MIME-Version: 1.0
X-MC-Unique: 5OIN4PcGNI2DbeqWSDHIXg-1
X-Mimecast-Spam-Score: 0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Branch is here: https://github.com/xzpeter/linux/tree/kvm-dirty-ring

Overview
============

This is a continued work from Lei Cao <lei.cao@stratus.com> and Paolo
on the KVM dirty ring interface.  To make it simple, I'll still start
with version 1 as RFC.

The new dirty ring interface is another way to collect dirty pages for
the virtual machine, but it is different from the existing dirty
logging interface in a few ways, majorly:

  - Data format: The dirty data was in a ring format rather than a
    bitmap format, so the size of data to sync for dirty logging does
    not depend on the size of guest memory any more, but speed of
    dirtying.  Also, the dirty ring is per-vcpu (currently plus
    another per-vm ring, so total ring number is N+1), while the dirty
    bitmap is per-vm.

  - Data copy: The sync of dirty pages does not need data copy any more,
    but instead the ring is shared between the userspace and kernel by
    page sharings (mmap() on either the vm fd or vcpu fd)

  - Interface: Instead of using the old KVM_GET_DIRTY_LOG,
    KVM_CLEAR_DIRTY_LOG interfaces, the new ring uses a new interface
    called KVM_RESET_DIRTY_RINGS when we want to reset the collected
    dirty pages to protected mode again (works like
    KVM_CLEAR_DIRTY_LOG, but ring based)

And more.

I would appreciate if the reviewers can start with patch "KVM:
Implement ring-based dirty memory tracking", especially the document
update part for the big picture.  Then I'll avoid copying into most of
them into cover letter again.

I marked this series as RFC because I'm at least uncertain on this
change of vcpu_enter_guest():

        if (kvm_check_request(KVM_REQ_DIRTY_RING_FULL, vcpu)) {
                vcpu->run->exit_reason = KVM_EXIT_DIRTY_RING_FULL;
                /*
                        * If this is requested, it means that we've
                        * marked the dirty bit in the dirty ring BUT
                        * we've not written the date.  Do it now.
                        */
                r = kvm_emulate_instruction(vcpu, 0);
                r = r >= 0 ? 0 : r;
                goto out;
        }

I did a kvm_emulate_instruction() when dirty ring reaches softlimit
and want to exit to userspace, however I'm not really sure whether
there could have any side effect.  I'd appreciate any comment of
above, or anything else.

Tests
===========

I wanted to continue work on the QEMU part, but after I noticed that
the interface might still prone to change, I posted this series first.
However to make sure it's at least working, I've provided unit tests
together with the series.  The unit tests should be able to test the
series in at least three major paths:

  (1) ./dirty_log_test -M dirty-ring

      This tests async ring operations: this should be the major work
      mode for the dirty ring interface, say, when the kernel is
      queuing more data, the userspace is collecting too.  Ring can
      hardly reaches full when working like this, because in most
      cases the collection could be fast.

  (2) ./dirty_log_test -M dirty-ring -c 1024

      This set the ring size to be very small so that ring soft-full
      always triggers (soft-full is a soft limit of the ring state,
      when the dirty ring reaches the soft limit it'll do a userspace
      exit and let the userspace to collect the data).

  (3) ./dirty_log_test -M dirty-ring-wait-queue

      This sololy test the extreme case where ring is full.  When the
      ring is completely full, the thread (no matter vcpu or not) will
      be put onto a per-vm waitqueue, and KVM_RESET_DIRTY_RINGS will
      wake the threads up (assuming until which the ring will not be
      full any more).

Thanks,

Cao, Lei (2):
  KVM: Add kvm/vcpu argument to mark_dirty_page_in_slot
  KVM: X86: Implement ring-based dirty memory tracking

Paolo Bonzini (1):
  KVM: Move running VCPU from ARM to common code

Peter Xu (12):
  KVM: Add build-time error check on kvm_run size
  KVM: Implement ring-based dirty memory tracking
  KVM: Make dirty ring exclusive to dirty bitmap log
  KVM: Introduce dirty ring wait queue
  KVM: selftests: Always clear dirty bitmap after iteration
  KVM: selftests: Sync uapi/linux/kvm.h to tools/
  KVM: selftests: Use a single binary for dirty/clear log test
  KVM: selftests: Introduce after_vcpu_run hook for dirty log test
  KVM: selftests: Add dirty ring buffer test
  KVM: selftests: Let dirty_log_test async for dirty ring test
  KVM: selftests: Add "-c" parameter to dirty log test
  KVM: selftests: Test dirty ring waitqueue

 Documentation/virt/kvm/api.txt                | 116 +++++
 arch/arm/include/asm/kvm_host.h               |   2 -
 arch/arm64/include/asm/kvm_host.h             |   2 -
 arch/x86/include/asm/kvm_host.h               |   5 +
 arch/x86/include/uapi/asm/kvm.h               |   1 +
 arch/x86/kvm/Makefile                         |   3 +-
 arch/x86/kvm/mmu/mmu.c                        |   6 +
 arch/x86/kvm/vmx/vmx.c                        |   7 +
 arch/x86/kvm/x86.c                            |  12 +
 include/linux/kvm_dirty_ring.h                |  67 +++
 include/linux/kvm_host.h                      |  37 ++
 include/linux/kvm_types.h                     |   1 +
 include/uapi/linux/kvm.h                      |  36 ++
 tools/include/uapi/linux/kvm.h                |  47 ++
 tools/testing/selftests/kvm/Makefile          |   2 -
 .../selftests/kvm/clear_dirty_log_test.c      |   2 -
 tools/testing/selftests/kvm/dirty_log_test.c  | 452 ++++++++++++++++--
 .../testing/selftests/kvm/include/kvm_util.h  |   6 +
 tools/testing/selftests/kvm/lib/kvm_util.c    | 103 ++++
 .../selftests/kvm/lib/kvm_util_internal.h     |   5 +
 virt/kvm/arm/arm.c                            |  29 --
 virt/kvm/arm/perf.c                           |   6 +-
 virt/kvm/arm/vgic/vgic-mmio.c                 |  15 +-
 virt/kvm/dirty_ring.c                         | 156 ++++++
 virt/kvm/kvm_main.c                           | 315 +++++++++++-
 25 files changed, 1329 insertions(+), 104 deletions(-)
 create mode 100644 include/linux/kvm_dirty_ring.h
 delete mode 100644 tools/testing/selftests/kvm/clear_dirty_log_test.c
 create mode 100644 virt/kvm/dirty_ring.c
```
#### [PATCH RFC 00/15] KVM: Dirty ring interface
##### From: Peter Xu <peterx@redhat.com>

```c
From patchwork Fri Nov 29 21:33:07 2019
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Peter Xu <peterx@redhat.com>
X-Patchwork-Id: 11267627
Return-Path: <SRS0=D48H=ZV=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 7D9B4109A
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 29 Nov 2019 21:33:36 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 5A8F02424D
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 29 Nov 2019 21:33:36 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="MoG69TE2"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727286AbfK2Vd2 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 29 Nov 2019 16:33:28 -0500
Received: from us-smtp-2.mimecast.com ([207.211.31.81]:25329 "EHLO
        us-smtp-delivery-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S1727230AbfK2Vd2 (ORCPT
        <rfc822;kvm@vger.kernel.org>); Fri, 29 Nov 2019 16:33:28 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1575063206;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:content-type:content-type:
         content-transfer-encoding:content-transfer-encoding;
        bh=peI3w5GhWEX1JieJHH29KyaSX4w2AsTjOin5SLB/5Gw=;
        b=MoG69TE2Ud0V4TI56GPIT9dsPqVt9S2bRpiQvQ4xygb2rkst4W312opa4np3I6YM5yig2V
        iIn9pv+6S0nIN3QyGf2+jdCBWtCaPyUzojOxbYO107sSSKg50TplB/R9P0Z28inlHzUHpE
        4cttmkfWef7s5aNZHxG1JnTymbUUmZ4=
Received: from mail-qv1-f71.google.com (mail-qv1-f71.google.com
 [209.85.219.71]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-171-h_JXXPeCPGCH0SG7vjmw8Q-1; Fri, 29 Nov 2019 16:33:25 -0500
Received: by mail-qv1-f71.google.com with SMTP id y9so7861674qvi.10
        for <kvm@vger.kernel.org>; Fri, 29 Nov 2019 13:33:25 -0800 (PST)
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:mime-version
         :content-transfer-encoding;
        bh=cn7j7/8SJgeM/ER61fZ1AdZGSd2mYCJ7pUgcBKPF2KQ=;
        b=r8ViEKkICbI1Tj5Y9BRmBao5pxTq/teE0ppV5Wdjw3hb15W9xYYIKApPKxDsTiQKd1
         Gt6tfDIwMnxn56FOCaenQ8TlI+NkIroftaobcGEYQldv4LN4ZrPgflcgIC/imdFUslsn
         2sYo/geI2n3TEETUH+EFAY4fCBRMpWokyTSLmu+6IhoRFB7bg+3TbFos238bi8/ow+0U
         B3an/YcnOK+hrMkPq+ipa64A5lgkQ4kD+Rc0i01nE0yS/XzaRmbz0mmVsRgocqZYn22J
         T54KKstxe8rRi6AASID30mtc/5VlBcTKcRmBMCj5SuqNhdXGGaBdz9EDKh7Q2YpBApLY
         QiWA==
X-Gm-Message-State: APjAAAXtE8jqxNXuwrVhvO8jf9Y+pUdD64RmNPH7l275MZrtTmfCtumX
        NhFWUzFQkmM7E1SbJBdZYecwTKgl2T2XHgBgpK3+xrkyPl13rbyUXAA7mIEcvtrLTBvzQ/S9Pz5
        Ta47CuJI0OV+E
X-Received: by 2002:a05:620a:1127:: with SMTP id
 p7mr13986171qkk.287.1575063204805;
        Fri, 29 Nov 2019 13:33:24 -0800 (PST)
X-Google-Smtp-Source: 
 APXvYqyBO9lODIMQRDHVwBS9dO8Hq/Ou+bAcJbw+JnpSvy8a7ZA7c0L5zwPT/av4zppUYYFTuWWbhw==
X-Received: by 2002:a05:620a:1127:: with SMTP id
 p7mr13986137qkk.287.1575063204428;
        Fri, 29 Nov 2019 13:33:24 -0800 (PST)
Received: from xz-x1.yyz.redhat.com ([104.156.64.74])
        by smtp.gmail.com with ESMTPSA id
 g11sm10584673qkm.82.2019.11.29.13.33.23
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Fri, 29 Nov 2019 13:33:23 -0800 (PST)
From: Peter Xu <peterx@redhat.com>
To: linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Cc: Sean Christopherson <sean.j.christopherson@intel.com>,
        Paolo Bonzini <pbonzini@redhat.com>,
        "Dr . David Alan Gilbert" <dgilbert@redhat.com>, peterx@redhat.com,
        Vitaly Kuznetsov <vkuznets@redhat.com>
Subject: [PATCH RFC 00/15] KVM: Dirty ring interface
Date: Fri, 29 Nov 2019 16:33:07 -0500
Message-Id: <20191129213322.17386-1-peterx@redhat.com>
X-Mailer: git-send-email 2.21.0
MIME-Version: 1.0
X-MC-Unique: h_JXXPeCPGCH0SG7vjmw8Q-1
X-Mimecast-Spam-Score: 0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Branch is here: https://github.com/xzpeter/linux/tree/kvm-dirty-ring

Overview
============

This is a continued work from Lei Cao <lei.cao@stratus.com> and Paolo
on the KVM dirty ring interface.  To make it simple, I'll still start
with version 1 as RFC.

The new dirty ring interface is another way to collect dirty pages for
the virtual machine, but it is different from the existing dirty
logging interface in a few ways, majorly:

  - Data format: The dirty data was in a ring format rather than a
    bitmap format, so the size of data to sync for dirty logging does
    not depend on the size of guest memory any more, but speed of
    dirtying.  Also, the dirty ring is per-vcpu (currently plus
    another per-vm ring, so total ring number is N+1), while the dirty
    bitmap is per-vm.

  - Data copy: The sync of dirty pages does not need data copy any more,
    but instead the ring is shared between the userspace and kernel by
    page sharings (mmap() on either the vm fd or vcpu fd)

  - Interface: Instead of using the old KVM_GET_DIRTY_LOG,
    KVM_CLEAR_DIRTY_LOG interfaces, the new ring uses a new interface
    called KVM_RESET_DIRTY_RINGS when we want to reset the collected
    dirty pages to protected mode again (works like
    KVM_CLEAR_DIRTY_LOG, but ring based)

And more.

I would appreciate if the reviewers can start with patch "KVM:
Implement ring-based dirty memory tracking", especially the document
update part for the big picture.  Then I'll avoid copying into most of
them into cover letter again.

I marked this series as RFC because I'm at least uncertain on this
change of vcpu_enter_guest():

        if (kvm_check_request(KVM_REQ_DIRTY_RING_FULL, vcpu)) {
                vcpu->run->exit_reason = KVM_EXIT_DIRTY_RING_FULL;
                /*
                        * If this is requested, it means that we've
                        * marked the dirty bit in the dirty ring BUT
                        * we've not written the date.  Do it now.
                        */
                r = kvm_emulate_instruction(vcpu, 0);
                r = r >= 0 ? 0 : r;
                goto out;
        }

I did a kvm_emulate_instruction() when dirty ring reaches softlimit
and want to exit to userspace, however I'm not really sure whether
there could have any side effect.  I'd appreciate any comment of
above, or anything else.

Tests
===========

I wanted to continue work on the QEMU part, but after I noticed that
the interface might still prone to change, I posted this series first.
However to make sure it's at least working, I've provided unit tests
together with the series.  The unit tests should be able to test the
series in at least three major paths:

  (1) ./dirty_log_test -M dirty-ring

      This tests async ring operations: this should be the major work
      mode for the dirty ring interface, say, when the kernel is
      queuing more data, the userspace is collecting too.  Ring can
      hardly reaches full when working like this, because in most
      cases the collection could be fast.

  (2) ./dirty_log_test -M dirty-ring -c 1024

      This set the ring size to be very small so that ring soft-full
      always triggers (soft-full is a soft limit of the ring state,
      when the dirty ring reaches the soft limit it'll do a userspace
      exit and let the userspace to collect the data).

  (3) ./dirty_log_test -M dirty-ring-wait-queue

      This sololy test the extreme case where ring is full.  When the
      ring is completely full, the thread (no matter vcpu or not) will
      be put onto a per-vm waitqueue, and KVM_RESET_DIRTY_RINGS will
      wake the threads up (assuming until which the ring will not be
      full any more).

Thanks,

Cao, Lei (2):
  KVM: Add kvm/vcpu argument to mark_dirty_page_in_slot
  KVM: X86: Implement ring-based dirty memory tracking

Paolo Bonzini (1):
  KVM: Move running VCPU from ARM to common code

Peter Xu (12):
  KVM: Add build-time error check on kvm_run size
  KVM: Implement ring-based dirty memory tracking
  KVM: Make dirty ring exclusive to dirty bitmap log
  KVM: Introduce dirty ring wait queue
  KVM: selftests: Always clear dirty bitmap after iteration
  KVM: selftests: Sync uapi/linux/kvm.h to tools/
  KVM: selftests: Use a single binary for dirty/clear log test
  KVM: selftests: Introduce after_vcpu_run hook for dirty log test
  KVM: selftests: Add dirty ring buffer test
  KVM: selftests: Let dirty_log_test async for dirty ring test
  KVM: selftests: Add "-c" parameter to dirty log test
  KVM: selftests: Test dirty ring waitqueue

 Documentation/virt/kvm/api.txt                | 116 +++++
 arch/arm/include/asm/kvm_host.h               |   2 -
 arch/arm64/include/asm/kvm_host.h             |   2 -
 arch/x86/include/asm/kvm_host.h               |   5 +
 arch/x86/include/uapi/asm/kvm.h               |   1 +
 arch/x86/kvm/Makefile                         |   3 +-
 arch/x86/kvm/mmu/mmu.c                        |   6 +
 arch/x86/kvm/vmx/vmx.c                        |   7 +
 arch/x86/kvm/x86.c                            |  12 +
 include/linux/kvm_dirty_ring.h                |  67 +++
 include/linux/kvm_host.h                      |  37 ++
 include/linux/kvm_types.h                     |   1 +
 include/uapi/linux/kvm.h                      |  36 ++
 tools/include/uapi/linux/kvm.h                |  47 ++
 tools/testing/selftests/kvm/Makefile          |   2 -
 .../selftests/kvm/clear_dirty_log_test.c      |   2 -
 tools/testing/selftests/kvm/dirty_log_test.c  | 452 ++++++++++++++++--
 .../testing/selftests/kvm/include/kvm_util.h  |   6 +
 tools/testing/selftests/kvm/lib/kvm_util.c    | 103 ++++
 .../selftests/kvm/lib/kvm_util_internal.h     |   5 +
 virt/kvm/arm/arm.c                            |  29 --
 virt/kvm/arm/perf.c                           |   6 +-
 virt/kvm/arm/vgic/vgic-mmio.c                 |  15 +-
 virt/kvm/dirty_ring.c                         | 156 ++++++
 virt/kvm/kvm_main.c                           | 315 +++++++++++-
 25 files changed, 1329 insertions(+), 104 deletions(-)
 create mode 100644 include/linux/kvm_dirty_ring.h
 delete mode 100644 tools/testing/selftests/kvm/clear_dirty_log_test.c
 create mode 100644 virt/kvm/dirty_ring.c
```
#### [PATCH RFC 00/15] KVM: Dirty ring interface
##### From: Peter Xu <peterx@redhat.com>

```c
From patchwork Fri Nov 29 21:34:50 2019
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Peter Xu <peterx@redhat.com>
X-Patchwork-Id: 11267629
Return-Path: <SRS0=D48H=ZV=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 2182215AB
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 29 Nov 2019 21:35:13 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id E7628207FA
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 29 Nov 2019 21:35:12 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="OZSRmaJI"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727261AbfK2VfM (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 29 Nov 2019 16:35:12 -0500
Received: from us-smtp-delivery-1.mimecast.com ([207.211.31.120]:27121 "EHLO
        us-smtp-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org
        with ESMTP id S1727124AbfK2VfL (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 29 Nov 2019 16:35:11 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1575063309;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:content-type:content-type:
         content-transfer-encoding:content-transfer-encoding;
        bh=peI3w5GhWEX1JieJHH29KyaSX4w2AsTjOin5SLB/5Gw=;
        b=OZSRmaJIBNUIjtG7J2HNje16ZdKX14cYF9hlnTLP2kij6cNIT3cu/Mu12pS53gsijytSkm
        BSh5XyYull4QTvXaj0CQePKTmspY+bSEBVA9jyzA3rTJvRf2OmHmVt8x0iDtHY/icXaX8Q
        TaLccjUcn+Fif13WMAPTMmwtGgRyJ34=
Received: from mail-qk1-f198.google.com (mail-qk1-f198.google.com
 [209.85.222.198]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-377-K-smAi2ZPDi7bLK_1yNISw-1; Fri, 29 Nov 2019 16:35:08 -0500
Received: by mail-qk1-f198.google.com with SMTP id 143so1177506qkg.12
        for <kvm@vger.kernel.org>; Fri, 29 Nov 2019 13:35:08 -0800 (PST)
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:mime-version
         :content-transfer-encoding;
        bh=cn7j7/8SJgeM/ER61fZ1AdZGSd2mYCJ7pUgcBKPF2KQ=;
        b=eCA3aqpLoYXlPtIRfShMaRZXdMwK+c0MIH/f1zPV/dOTQnmuqeeksaP4KozlMMznGd
         8O75lPsEW6p30H8Gv/6ll+KPx7sI0thJ7XH+5UmcI3iuY4SKN3GX44+Ict7XnBfyIGAO
         kobsC3zv9vCDfYWNTtT/eyAk3EuGRbBcU1t7aoRNbjPSgxTeJr5zF7V93gujANdnYFS0
         zhAG7lyRfWaGDiC3DmUmCBCWj0586mJzAAfIbjxk01b0zhTd+7yq/bV1epJXrUtt3a/9
         LvIro/rsM9y3OEGssOqE+EXQT1v90EDqBST9NhX1VVc8VI3XQB5ljiROgrkMoxB83wom
         m6xg==
X-Gm-Message-State: APjAAAWAKqi+ROTImqUgxK8Tpetp1Zrr0rYb1zrsN+4LBGYaZ77G4idQ
        ichaxP1eeP3/eaAnD93C8k2AYXhc1vodOndd5iT5RLETI1KzomX0oFY9sYK9VHSnAOT6dVnkX+a
        8ltjUQEIdg3E8
X-Received: by 2002:ad4:496f:: with SMTP id
 p15mr15077446qvy.191.1575063307657;
        Fri, 29 Nov 2019 13:35:07 -0800 (PST)
X-Google-Smtp-Source: 
 APXvYqy+F7JzYzopvUpB24O6OCI7HE/jzlGe7t2/G4p0IAFt48bwCRZggAZbC53gs3tGy/Q0CXlFkQ==
X-Received: by 2002:ad4:496f:: with SMTP id
 p15mr15077413qvy.191.1575063307313;
        Fri, 29 Nov 2019 13:35:07 -0800 (PST)
Received: from xz-x1.yyz.redhat.com ([104.156.64.74])
        by smtp.gmail.com with ESMTPSA id
 h186sm10679046qkf.64.2019.11.29.13.35.06
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Fri, 29 Nov 2019 13:35:06 -0800 (PST)
From: Peter Xu <peterx@redhat.com>
To: linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Cc: Sean Christopherson <sean.j.christopherson@intel.com>,
        Paolo Bonzini <pbonzini@redhat.com>,
        "Dr . David Alan Gilbert" <dgilbert@redhat.com>, peterx@redhat.com,
        Vitaly Kuznetsov <vkuznets@redhat.com>
Subject: [PATCH RFC 00/15] KVM: Dirty ring interface
Date: Fri, 29 Nov 2019 16:34:50 -0500
Message-Id: <20191129213505.18472-1-peterx@redhat.com>
X-Mailer: git-send-email 2.21.0
MIME-Version: 1.0
X-MC-Unique: K-smAi2ZPDi7bLK_1yNISw-1
X-Mimecast-Spam-Score: 0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Branch is here: https://github.com/xzpeter/linux/tree/kvm-dirty-ring

Overview
============

This is a continued work from Lei Cao <lei.cao@stratus.com> and Paolo
on the KVM dirty ring interface.  To make it simple, I'll still start
with version 1 as RFC.

The new dirty ring interface is another way to collect dirty pages for
the virtual machine, but it is different from the existing dirty
logging interface in a few ways, majorly:

  - Data format: The dirty data was in a ring format rather than a
    bitmap format, so the size of data to sync for dirty logging does
    not depend on the size of guest memory any more, but speed of
    dirtying.  Also, the dirty ring is per-vcpu (currently plus
    another per-vm ring, so total ring number is N+1), while the dirty
    bitmap is per-vm.

  - Data copy: The sync of dirty pages does not need data copy any more,
    but instead the ring is shared between the userspace and kernel by
    page sharings (mmap() on either the vm fd or vcpu fd)

  - Interface: Instead of using the old KVM_GET_DIRTY_LOG,
    KVM_CLEAR_DIRTY_LOG interfaces, the new ring uses a new interface
    called KVM_RESET_DIRTY_RINGS when we want to reset the collected
    dirty pages to protected mode again (works like
    KVM_CLEAR_DIRTY_LOG, but ring based)

And more.

I would appreciate if the reviewers can start with patch "KVM:
Implement ring-based dirty memory tracking", especially the document
update part for the big picture.  Then I'll avoid copying into most of
them into cover letter again.

I marked this series as RFC because I'm at least uncertain on this
change of vcpu_enter_guest():

        if (kvm_check_request(KVM_REQ_DIRTY_RING_FULL, vcpu)) {
                vcpu->run->exit_reason = KVM_EXIT_DIRTY_RING_FULL;
                /*
                        * If this is requested, it means that we've
                        * marked the dirty bit in the dirty ring BUT
                        * we've not written the date.  Do it now.
                        */
                r = kvm_emulate_instruction(vcpu, 0);
                r = r >= 0 ? 0 : r;
                goto out;
        }

I did a kvm_emulate_instruction() when dirty ring reaches softlimit
and want to exit to userspace, however I'm not really sure whether
there could have any side effect.  I'd appreciate any comment of
above, or anything else.

Tests
===========

I wanted to continue work on the QEMU part, but after I noticed that
the interface might still prone to change, I posted this series first.
However to make sure it's at least working, I've provided unit tests
together with the series.  The unit tests should be able to test the
series in at least three major paths:

  (1) ./dirty_log_test -M dirty-ring

      This tests async ring operations: this should be the major work
      mode for the dirty ring interface, say, when the kernel is
      queuing more data, the userspace is collecting too.  Ring can
      hardly reaches full when working like this, because in most
      cases the collection could be fast.

  (2) ./dirty_log_test -M dirty-ring -c 1024

      This set the ring size to be very small so that ring soft-full
      always triggers (soft-full is a soft limit of the ring state,
      when the dirty ring reaches the soft limit it'll do a userspace
      exit and let the userspace to collect the data).

  (3) ./dirty_log_test -M dirty-ring-wait-queue

      This sololy test the extreme case where ring is full.  When the
      ring is completely full, the thread (no matter vcpu or not) will
      be put onto a per-vm waitqueue, and KVM_RESET_DIRTY_RINGS will
      wake the threads up (assuming until which the ring will not be
      full any more).

Thanks,

Cao, Lei (2):
  KVM: Add kvm/vcpu argument to mark_dirty_page_in_slot
  KVM: X86: Implement ring-based dirty memory tracking

Paolo Bonzini (1):
  KVM: Move running VCPU from ARM to common code

Peter Xu (12):
  KVM: Add build-time error check on kvm_run size
  KVM: Implement ring-based dirty memory tracking
  KVM: Make dirty ring exclusive to dirty bitmap log
  KVM: Introduce dirty ring wait queue
  KVM: selftests: Always clear dirty bitmap after iteration
  KVM: selftests: Sync uapi/linux/kvm.h to tools/
  KVM: selftests: Use a single binary for dirty/clear log test
  KVM: selftests: Introduce after_vcpu_run hook for dirty log test
  KVM: selftests: Add dirty ring buffer test
  KVM: selftests: Let dirty_log_test async for dirty ring test
  KVM: selftests: Add "-c" parameter to dirty log test
  KVM: selftests: Test dirty ring waitqueue

 Documentation/virt/kvm/api.txt                | 116 +++++
 arch/arm/include/asm/kvm_host.h               |   2 -
 arch/arm64/include/asm/kvm_host.h             |   2 -
 arch/x86/include/asm/kvm_host.h               |   5 +
 arch/x86/include/uapi/asm/kvm.h               |   1 +
 arch/x86/kvm/Makefile                         |   3 +-
 arch/x86/kvm/mmu/mmu.c                        |   6 +
 arch/x86/kvm/vmx/vmx.c                        |   7 +
 arch/x86/kvm/x86.c                            |  12 +
 include/linux/kvm_dirty_ring.h                |  67 +++
 include/linux/kvm_host.h                      |  37 ++
 include/linux/kvm_types.h                     |   1 +
 include/uapi/linux/kvm.h                      |  36 ++
 tools/include/uapi/linux/kvm.h                |  47 ++
 tools/testing/selftests/kvm/Makefile          |   2 -
 .../selftests/kvm/clear_dirty_log_test.c      |   2 -
 tools/testing/selftests/kvm/dirty_log_test.c  | 452 ++++++++++++++++--
 .../testing/selftests/kvm/include/kvm_util.h  |   6 +
 tools/testing/selftests/kvm/lib/kvm_util.c    | 103 ++++
 .../selftests/kvm/lib/kvm_util_internal.h     |   5 +
 virt/kvm/arm/arm.c                            |  29 --
 virt/kvm/arm/perf.c                           |   6 +-
 virt/kvm/arm/vgic/vgic-mmio.c                 |  15 +-
 virt/kvm/dirty_ring.c                         | 156 ++++++
 virt/kvm/kvm_main.c                           | 315 +++++++++++-
 25 files changed, 1329 insertions(+), 104 deletions(-)
 create mode 100644 include/linux/kvm_dirty_ring.h
 delete mode 100644 tools/testing/selftests/kvm/clear_dirty_log_test.c
 create mode 100644 virt/kvm/dirty_ring.c
```
