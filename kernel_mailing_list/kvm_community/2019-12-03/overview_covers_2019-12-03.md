

#### [PATCH v3 00/12] video, drm, etc: constify fbops in struct fb_info
##### From: Jani Nikula <jani.nikula@intel.com>

```c
From patchwork Tue Dec  3 16:38:42 2019
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 8bit
X-Patchwork-Submitter: Jani Nikula <jani.nikula@intel.com>
X-Patchwork-Id: 11271617
Return-Path: <SRS0=eZxF=ZZ=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 7A49B930
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue,  3 Dec 2019 16:39:08 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 4F52A2073B
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue,  3 Dec 2019 16:39:08 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727009AbfLCQjH (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 3 Dec 2019 11:39:07 -0500
Received: from mga03.intel.com ([134.134.136.65]:34141 "EHLO mga03.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726186AbfLCQjG (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 3 Dec 2019 11:39:06 -0500
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from orsmga008.jf.intel.com ([10.7.209.65])
  by orsmga103.jf.intel.com with ESMTP/TLS/DHE-RSA-AES256-GCM-SHA384;
 03 Dec 2019 08:39:05 -0800
X-IronPort-AV: E=Sophos;i="5.69,273,1571727600";
   d="scan'208";a="205035803"
Received: from jnikula-mobl3.fi.intel.com (HELO localhost) ([10.237.66.161])
  by orsmga008-auth.jf.intel.com with ESMTP/TLS/DHE-RSA-AES256-GCM-SHA384;
 03 Dec 2019 08:38:58 -0800
From: Jani Nikula <jani.nikula@intel.com>
To: dri-devel@lists.freedesktop.org, linux-fbdev@vger.kernel.org
Cc: intel-gfx@lists.freedesktop.org, jani.nikula@intel.com,
 Andy Walls <awalls@md.metrocast.net>, Bernie Thompson <bernie@plugable.com>,
	=?utf-8?q?Bruno_Pr=C3=A9mont?= <bonbons@linux-vserver.org>,
 Daniel Vetter <daniel@ffwll.ch>, Hans Verkuil <hverkuil@xs4all.nl>,
 Jaya Kumar <jayalk@intworks.biz>, Kirti Wankhede <kwankhede@nvidia.com>,
 Miguel Ojeda Sandonis <miguel.ojeda.sandonis@gmail.com>, =?utf-8?q?Noralf_T?=
	=?utf-8?q?r=C3=B8nnes?= <noralf@tronnes.org>,
 Robin van der Gracht <robin@protonic.nl>,
 Steve Glendinning <steve.glendinning@shawell.net>, =?utf-8?b?VmlsbGUgU3ly?=
	=?utf-8?b?asOkbMOk?=  <ville.syrjala@linux.intel.com>,
 ivtv-devel@ivtvdriver.org, kvm@vger.kernel.org, linux-input@vger.kernel.org,
 linux-media@vger.kernel.org, linux-omap@vger.kernel.org
Subject: [PATCH v3 00/12] video, drm, etc: constify fbops in struct fb_info
Date: Tue,  3 Dec 2019 18:38:42 +0200
Message-Id: <cover.1575390740.git.jani.nikula@intel.com>
X-Mailer: git-send-email 2.20.1
MIME-Version: 1.0
Organization: Intel Finland Oy - BIC 0357606-4 - Westendinkatu 7, 02160 Espoo
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This is v3 of https://patchwork.freedesktop.org/series/70198/.

0day reported some build failures, and I needed to add patches 1-5 and 7
to address them. Patch 8 was amended accordingly (dropped some consts),
but the other patches remain the same from v2, except the ones I merged
already.

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

Jani Nikula (12):
  video: fbdev: atyfb: modify the static fb_ops directly
  video: fbdev: mb862xx: modify the static fb_ops directly
  video: fbdev: nvidia: modify the static fb_ops directly
  video: fbdev: uvesafb: modify the static fb_ops directly
  video: fbdev: make fbops member of struct fb_info a const pointer
  drm: constify fb ops across all drivers
  video: fbdev: intelfb: use const pointer for fb_ops
  video: constify fb ops across all drivers
  HID: picoLCD: constify fb ops
  media: constify fb ops across all drivers
  samples: vfio-mdev: constify fb ops
  auxdisplay: constify fb ops

 drivers/auxdisplay/cfag12864bfb.c             |  2 +-
 drivers/auxdisplay/ht16k33.c                  |  2 +-
 drivers/gpu/drm/amd/amdgpu/amdgpu_fb.c        |  2 +-
 drivers/gpu/drm/armada/armada_fbdev.c         |  2 +-
 drivers/gpu/drm/drm_fb_helper.c               |  2 +-
 drivers/gpu/drm/exynos/exynos_drm_fbdev.c     |  2 +-
 .../gpu/drm/hisilicon/hibmc/hibmc_drm_fbdev.c |  2 +-
 drivers/gpu/drm/i915/display/intel_fbdev.c    |  2 +-
 drivers/gpu/drm/msm/msm_fbdev.c               |  2 +-
 drivers/gpu/drm/nouveau/nouveau_fbcon.c       |  4 ++--
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
 drivers/video/fbdev/aty/atyfb.h               |  2 +-
 drivers/video/fbdev/aty/atyfb_base.c          |  6 +++---
 drivers/video/fbdev/aty/mach64_cursor.c       |  4 ++--
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
 drivers/video/fbdev/intelfb/intelfb.h         |  2 +-
 drivers/video/fbdev/intelfb/intelfbdrv.c      |  2 +-
 drivers/video/fbdev/kyro/fbdev.c              |  2 +-
 drivers/video/fbdev/leo.c                     |  2 +-
 drivers/video/fbdev/macfb.c                   |  2 +-
 drivers/video/fbdev/matrox/matroxfb_crtc2.c   |  2 +-
 drivers/video/fbdev/maxinefb.c                |  2 +-
 drivers/video/fbdev/mb862xx/mb862xxfb.h       |  2 +-
 drivers/video/fbdev/mb862xx/mb862xxfb_accel.c | 15 +++++++-------
 drivers/video/fbdev/mb862xx/mb862xxfbdrv.c    |  4 +++-
 drivers/video/fbdev/mbx/mbxfb.c               |  2 +-
 drivers/video/fbdev/metronomefb.c             |  2 +-
 drivers/video/fbdev/mmp/fb/mmpfb.c            |  2 +-
 drivers/video/fbdev/mx3fb.c                   |  5 +++--
 drivers/video/fbdev/neofb.c                   |  2 +-
 drivers/video/fbdev/nvidia/nvidia.c           | 20 ++++++++++---------
 drivers/video/fbdev/ocfb.c                    |  2 +-
 drivers/video/fbdev/offb.c                    |  2 +-
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
 drivers/video/fbdev/pxafb.c                   |  4 ++--
 drivers/video/fbdev/q40fb.c                   |  2 +-
 drivers/video/fbdev/riva/fbdev.c              |  2 +-
 drivers/video/fbdev/s3c-fb.c                  |  2 +-
 drivers/video/fbdev/s3c2410fb.c               |  2 +-
 drivers/video/fbdev/s3fb.c                    |  2 +-
 drivers/video/fbdev/sa1100fb.c                |  2 +-
 drivers/video/fbdev/savage/savagefb_driver.c  |  2 +-
 drivers/video/fbdev/sh7760fb.c                |  2 +-
 drivers/video/fbdev/sh_mobile_lcdcfb.c        |  4 ++--
 drivers/video/fbdev/simplefb.c                |  2 +-
 drivers/video/fbdev/sis/sis_main.c            |  2 +-
 drivers/video/fbdev/skeletonfb.c              |  2 +-
 drivers/video/fbdev/sm712fb.c                 |  2 +-
 drivers/video/fbdev/smscufx.c                 |  2 +-
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
 drivers/video/fbdev/uvesafb.c                 |  4 ++--
 drivers/video/fbdev/valkyriefb.c              |  2 +-
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
 136 files changed, 163 insertions(+), 162 deletions(-)
```
#### [PATCH v4 0/6] KVM: X86: Cleanups on dest_mode and headers
##### From: Peter Xu <peterx@redhat.com>

```c
From patchwork Tue Dec  3 16:58:57 2019
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Peter Xu <peterx@redhat.com>
X-Patchwork-Id: 11271715
Return-Path: <SRS0=eZxF=ZZ=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 992AA6C1
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue,  3 Dec 2019 16:59:44 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 76E3B20833
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue,  3 Dec 2019 16:59:44 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="cGGXHtKA"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727085AbfLCQ7J (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 3 Dec 2019 11:59:09 -0500
Received: from us-smtp-delivery-1.mimecast.com ([207.211.31.120]:55382 "EHLO
        us-smtp-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org
        with ESMTP id S1726074AbfLCQ7J (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 3 Dec 2019 11:59:09 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1575392347;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:content-type:content-type:
         content-transfer-encoding:content-transfer-encoding;
        bh=9idJJsQV/2uEwKnGkN4mjfcfOqrJXpGQnakfdpkG6DI=;
        b=cGGXHtKA+seDsh6eU6dLZin/AyVSU9ZyJkvkuwD93zh3Nhk5uQmXhnxsBvhdNkuT0efJki
        oaIDNaqaWpwt/C0XP9TvPOHjV5K+VmBBcfAyEYwTQG/h14wDW773pDTfRGb4an5tO43iqO
        W9cui3U8Zyfpk+gzZmtbij0k1cVc6XA=
Received: from mail-qk1-f200.google.com (mail-qk1-f200.google.com
 [209.85.222.200]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-63-KTl2_h25Pa-AKp3lvIqyjw-1; Tue, 03 Dec 2019 11:59:06 -0500
Received: by mail-qk1-f200.google.com with SMTP id a1so2597364qkn.15
        for <kvm@vger.kernel.org>; Tue, 03 Dec 2019 08:59:06 -0800 (PST)
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:mime-version
         :content-transfer-encoding;
        bh=Ki0zcq1Hd91HT74Xqb0k5NM023hUsBT8hpjru9BF2VU=;
        b=suZgdlwL1uOpIeTVAdOZ1OfHm8i5upMuzartUQCKWe7BVnYWU1B4JlEseKs3VXcY+O
         z5PxABYpwCelpX3ZtHqHLpCYmnCii8PtzMkwtRImayMzrrmhfDEGhecXnhXPDDrE9j9i
         h0mWwJS9EZbqkMPRdkvjG+1MWyLdOUkFJ866cjLkuIgGbDo0JzvkfUtssuP76bYC29s+
         a8R/YUijGpRHGBkpd5OzCYgzmtBzsI2Sru1cQlXsxZDl0z9CLHbS9sEwqEuz7q2BLBlJ
         zwVVeIzBy/Y2hVChIpVGpdmWl8EvoUMY4J5Mu3Kd34wR9Hl+oFczWjk2QzzDWff3RUaa
         gZ2Q==
X-Gm-Message-State: APjAAAUkw0AVXyp5YjXxUk8UoPQDz38cND/QMiNM0uJ6fKTClymtQQLe
        RfrasM62te+EYEUdcYKC+nBuPDUh89CrejwZw54i4xJOEQfOa+3CxiiIUBhzBpfUnZlXNbDgy8h
        3wRyFnIxZ70q6
X-Received: by 2002:ac8:1017:: with SMTP id z23mr5922474qti.154.1575392345722;
        Tue, 03 Dec 2019 08:59:05 -0800 (PST)
X-Google-Smtp-Source: 
 APXvYqyJfsAGRsZ+YvZuBbG3sFkoCk1FF9Ev5phxgEhOfqT73zztJ/7/gzPmD1aFE0Ca9XawO46P9Q==
X-Received: by 2002:ac8:1017:: with SMTP id z23mr5922449qti.154.1575392345471;
        Tue, 03 Dec 2019 08:59:05 -0800 (PST)
Received: from xz-x1.yyz.redhat.com ([104.156.64.74])
        by smtp.gmail.com with ESMTPSA id
 a16sm482585qkn.48.2019.12.03.08.59.04
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Tue, 03 Dec 2019 08:59:04 -0800 (PST)
From: Peter Xu <peterx@redhat.com>
To: linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Cc: Nitesh Narayan Lal <nitesh@redhat.com>,
        Paolo Bonzini <pbonzini@redhat.com>,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        peterx@redhat.com, Vitaly Kuznetsov <vkuznets@redhat.com>
Subject: [PATCH v4 0/6] KVM: X86: Cleanups on dest_mode and headers
Date: Tue,  3 Dec 2019 11:58:57 -0500
Message-Id: <20191203165903.22917-1-peterx@redhat.com>
X-Mailer: git-send-email 2.21.0
MIME-Version: 1.0
X-MC-Unique: KTl2_h25Pa-AKp3lvIqyjw-1
X-Mimecast-Spam-Score: 0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

v4:
- address all comments from Vitaly, adding r-bs properly
- added one more trivial patch:
  "KVM: X86: Conert the last users of "shorthand = 0" to use macros"

v3:
- address all the comments from both Vitaly and Sean
- since at it, added patches:
  "KVM: X86: Fix kvm_bitmap_or_dest_vcpus() to use irq shorthand"
  "KVM: X86: Drop KVM_APIC_SHORT_MASK and KVM_APIC_DEST_MASK"

Each patch explains itself.

Please have a look, thanks.

Peter Xu (6):
  KVM: X86: Fix kvm_bitmap_or_dest_vcpus() to use irq shorthand
  KVM: X86: Move irrelevant declarations out of ioapic.h
  KVM: X86: Use APIC_DEST_* macros properly in kvm_lapic_irq.dest_mode
  KVM: X86: Drop KVM_APIC_SHORT_MASK and KVM_APIC_DEST_MASK
  KVM: X86: Fix callers of kvm_apic_match_dest() to use correct macros
  KVM: X86: Conert the last users of "shorthand = 0" to use macros

 arch/x86/include/asm/kvm_host.h |  5 +++++
 arch/x86/kvm/hyperv.c           |  1 +
 arch/x86/kvm/ioapic.c           | 24 +++++++++++++++---------
 arch/x86/kvm/ioapic.h           |  6 ------
 arch/x86/kvm/irq.h              |  3 +++
 arch/x86/kvm/irq_comm.c         | 12 +++++++-----
 arch/x86/kvm/lapic.c            |  5 +----
 arch/x86/kvm/lapic.h            |  7 ++++---
 arch/x86/kvm/svm.c              |  4 ++--
 arch/x86/kvm/x86.c              |  4 ++--
 10 files changed, 40 insertions(+), 31 deletions(-)
```
