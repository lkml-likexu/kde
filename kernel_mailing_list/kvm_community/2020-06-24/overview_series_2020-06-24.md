#### [GIT PULL] virtio: fixes, tests
##### From: "Michael S. Tsirkin" <mst@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 8bit
X-Patchwork-Submitter: "Michael S. Tsirkin" <mst@redhat.com>
X-Patchwork-Id: 11622707
Return-Path: <SRS0=aKHR=AF=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 907C814E3
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 24 Jun 2020 09:08:12 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 7771120823
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 24 Jun 2020 09:08:12 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="F8NLBw5t"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2388615AbgFXJIJ (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 24 Jun 2020 05:08:09 -0400
Received: from us-smtp-2.mimecast.com ([207.211.31.81]:23648 "EHLO
        us-smtp-delivery-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S1728637AbgFXJIJ (ORCPT
        <rfc822;kvm@vger.kernel.org>); Wed, 24 Jun 2020 05:08:09 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1592989687;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:content-type:content-type:
         content-transfer-encoding:content-transfer-encoding;
        bh=VQoY+UTRP06W0gqpd2Juj7Hxof1/RYyQfXylaOH8G2E=;
        b=F8NLBw5tN6xoouLxkIAmkOlqr/gTHC94CEHbImfOM3BtLo8y9a30kna/RJLZh8V9D0PoGk
        YTB4D8EuRUl/NyUSJIDMmMNSXf0tXjixbnYl741kCOjUhW1u3BjcyhOJjI0lvRvJBkm8oB
        zFnUGAGN/X4oSy2Lfb5IiFN/nHmLWXM=
Received: from mail-wr1-f71.google.com (mail-wr1-f71.google.com
 [209.85.221.71]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-483-dj-kGBPRMRG0XPM57Rhjcw-1; Wed, 24 Jun 2020 05:08:05 -0400
X-MC-Unique: dj-kGBPRMRG0XPM57Rhjcw-1
Received: by mail-wr1-f71.google.com with SMTP id g14so2283281wrp.8
        for <kvm@vger.kernel.org>; Wed, 24 Jun 2020 02:08:05 -0700 (PDT)
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:date:from:to:cc:subject:message-id:mime-version
         :content-disposition:content-transfer-encoding;
        bh=VQoY+UTRP06W0gqpd2Juj7Hxof1/RYyQfXylaOH8G2E=;
        b=i6xDhRd7lKyBpgp5BEE1V9G2rkMjm8Bse+HI4fCr6QkQ+0KazJxu6SSKFF8DKPu4e1
         +5If6l4b+x2yFGWJOi8ZS9xSjzpO9yc2ZPRfmJGRFYayE1FP1a4T2j8Yvj+bx15TUBep
         yB2ugtaUY02yKgWcaY8VkrmFHwj53+2FZVqWSoVnDybnJpgTqG5btQsyrZrQLxCsGHS4
         yutVZ69riG8lEvHvyamYWMFKRT8MKW/7YMX7qQfUnQp5k0CzxMYdW7SRUsz8xMPtNoCU
         7y2LTnqnNRMHr3HIfyT0nSCSSyfev1vjUIQnrBNZbXZg8UBOe1IQMWNgwrLT5+cBsqFw
         jJ+g==
X-Gm-Message-State: AOAM532rCMs4t4LE34V1ZoZsdFLdkBVicq0R1rDg9myGJpok5MFNk/5Y
        zn9izpWEjOxQfBzargwEk1XCCoTUT5bGVgRU0ebDn9PWpPWU9dCmIOZGBDLx5/L4T/U7t/Nh7jD
        n4YzKnVlX9gTY
X-Received: by 2002:a7b:cb4c:: with SMTP id v12mr28392153wmj.43.1592989684867;
        Wed, 24 Jun 2020 02:08:04 -0700 (PDT)
X-Google-Smtp-Source: 
 ABdhPJzbEhEN966Il4umYMTMjRrrueqoGcM5lQiV/3BTRS9Bm+7+N7X0YZSdV011xkOJs+ZR2fNnFw==
X-Received: by 2002:a7b:cb4c:: with SMTP id v12mr28392130wmj.43.1592989684670;
        Wed, 24 Jun 2020 02:08:04 -0700 (PDT)
Received: from redhat.com ([82.166.20.53])
        by smtp.gmail.com with ESMTPSA id
 e5sm26714788wrw.19.2020.06.24.02.08.02
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Wed, 24 Jun 2020 02:08:03 -0700 (PDT)
Date: Wed, 24 Jun 2020 05:08:01 -0400
From: "Michael S. Tsirkin" <mst@redhat.com>
To: Linus Torvalds <torvalds@linux-foundation.org>
Cc: kvm@vger.kernel.org, virtualization@lists.linux-foundation.org,
        netdev@vger.kernel.org, linux-kernel@vger.kernel.org,
        dan.carpenter@oracle.com, david@redhat.com, eperezma@redhat.com,
        jasowang@redhat.com, mst@redhat.com, pankaj.gupta.linux@gmail.com,
        teawaterz@linux.alibaba.com
Subject: [GIT PULL] virtio: fixes, tests
Message-ID: <20200624050801-mutt-send-email-mst@kernel.org>
MIME-Version: 1.0
Content-Disposition: inline
X-Mutt-Fcc: =sent
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The following changes since commit 48778464bb7d346b47157d21ffde2af6b2d39110:

  Linux 5.8-rc2 (2020-06-21 15:45:29 -0700)

are available in the Git repository at:

  https://git.kernel.org/pub/scm/linux/kernel/git/mst/vhost.git tags/for_linus

for you to fetch changes up to cb91909e48a4809261ef4e967464e2009b214f06:

  tools/virtio: Use tools/include/list.h instead of stubs (2020-06-22 12:34:22 -0400)

----------------------------------------------------------------
virtio: fixes, tests

Fixes all over the place.

This includes a couple of tests that I would normally defer,
but since they have already been helpful in catching some bugs,
don't build for any users at all, and having them
upstream makes life easier for everyone, I think it's
ok even at this late stage.

Signed-off-by: Michael S. Tsirkin <mst@redhat.com>

----------------------------------------------------------------
Dan Carpenter (2):
      vhost_vdpa: Fix potential underflow in vhost_vdpa_mmap()
      virtio-mem: silence a static checker warning

David Hildenbrand (1):
      virtio-mem: add memory via add_memory_driver_managed()

Eugenio Pérez (7):
      tools/virtio: Add --batch option
      tools/virtio: Add --batch=random option
      tools/virtio: Add --reset
      tools/virtio: Use __vring_new_virtqueue in virtio_test.c
      tools/virtio: Extract virtqueue initialization in vq_reset
      tools/virtio: Reset index in virtio_test --reset.
      tools/virtio: Use tools/include/list.h instead of stubs

Jason Wang (1):
      vdpa: fix typos in the comments for __vdpa_alloc_device()

 drivers/vdpa/vdpa.c         |   2 +-
 drivers/vhost/test.c        |  57 ++++++++++++++++++
 drivers/vhost/test.h        |   1 +
 drivers/vhost/vdpa.c        |   2 +-
 drivers/virtio/virtio_mem.c |  27 +++++++--
 tools/virtio/linux/kernel.h |   7 +--
 tools/virtio/linux/virtio.h |   5 +-
 tools/virtio/virtio_test.c  | 139 +++++++++++++++++++++++++++++++++++++-------
 tools/virtio/vringh_test.c  |   2 +
 9 files changed, 207 insertions(+), 35 deletions(-)
```
#### [PATCH kvm-unit-tests] i386: setup segment registers before percpu areas
##### From: Paolo Bonzini <pbonzini@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Paolo Bonzini <pbonzini@redhat.com>
X-Patchwork-Id: 11623281
Return-Path: <SRS0=aKHR=AF=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id BAF6260D
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 24 Jun 2020 14:14:36 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id A0AAD2076E
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 24 Jun 2020 14:14:36 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="dJnNKjAb"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2390049AbgFXOOf (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 24 Jun 2020 10:14:35 -0400
Received: from us-smtp-1.mimecast.com ([207.211.31.81]:48942 "EHLO
        us-smtp-delivery-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S2389583AbgFXOOe (ORCPT
        <rfc822;kvm@vger.kernel.org>); Wed, 24 Jun 2020 10:14:34 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1593008073;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=ZEqT8Oy86SuWyMii7V54P8YjMki3kKQTmwnWT92jSIM=;
        b=dJnNKjAbHuGjaIHfG/XJkaplIIF091l7p5r0tv1UaCjWHzVkg8+P/eaRPoC1zbnzQVW8ng
        ZPO8YymZv6CUXwKYtU85nfk1cQKFxbM2Z7zpA1j7AKrXR7Wp7iobZzhBexw31PClmPs6jo
        TvTjOiDv5lpZQKlAh9p6hevaFNxm+so=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-393-KSvMrACgOAWHNwbjwLkQmA-1; Wed, 24 Jun 2020 10:14:31 -0400
X-MC-Unique: KSvMrACgOAWHNwbjwLkQmA-1
Received: from smtp.corp.redhat.com (int-mx01.intmail.prod.int.phx2.redhat.com
 [10.5.11.11])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 9D3251940923
        for <kvm@vger.kernel.org>; Wed, 24 Jun 2020 14:14:30 +0000 (UTC)
Received: from virtlab511.virt.lab.eng.bos.redhat.com
 (virtlab511.virt.lab.eng.bos.redhat.com [10.19.152.198])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 4A5F07B600
        for <kvm@vger.kernel.org>; Wed, 24 Jun 2020 14:14:30 +0000 (UTC)
From: Paolo Bonzini <pbonzini@redhat.com>
To: kvm@vger.kernel.org
Subject: [PATCH kvm-unit-tests] i386: setup segment registers before percpu
 areas
Date: Wed, 24 Jun 2020 10:14:29 -0400
Message-Id: <20200624141429.382157-1-pbonzini@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.11
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The base of the percpu area is stored in the %gs base, and writing
to %gs destroys it.  Move setup_segments earlier, before the %gs
base is written.

Signed-off-by: Paolo Bonzini <pbonzini@redhat.com>
Signed-off-by: Nadav Amit <namit@vmware.com>
---
 x86/cstart.S | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
#### [PATCH kvm-unit-tests] x86: move IDT away from address 0
##### From: Paolo Bonzini <pbonzini@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Paolo Bonzini <pbonzini@redhat.com>
X-Patchwork-Id: 11623789
Return-Path: <SRS0=aKHR=AF=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id A11F292A
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 24 Jun 2020 16:55:05 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 897E52073E
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 24 Jun 2020 16:55:05 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="YaazptKH"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2404796AbgFXQzD (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 24 Jun 2020 12:55:03 -0400
Received: from us-smtp-1.mimecast.com ([205.139.110.61]:40315 "EHLO
        us-smtp-delivery-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S2404431AbgFXQzD (ORCPT
        <rfc822;kvm@vger.kernel.org>); Wed, 24 Jun 2020 12:55:03 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1593017702;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=Vip8xwgwmcPl38v+bIxTFJ+koVkwq3bCJZqiOBGmcbM=;
        b=YaazptKHYyTlWEKws59l85RRdbUSF/Kc0wwSxk5jbn4dbJWFPt30mh8AuGqhtSFB0o7hev
        /1/7+NDXGRUAdittrWvxLVg+mluIsrHce7Pjw20ubRRR/8uScUPOgDnDICWq5w/mL59usz
        F+Oi2V72zMWuHe1KQoWTsabvOt43kfQ=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-436-BIc9UCOsMYiMtfQknvvg5g-1; Wed, 24 Jun 2020 12:55:00 -0400
X-MC-Unique: BIc9UCOsMYiMtfQknvvg5g-1
Received: from smtp.corp.redhat.com (int-mx08.intmail.prod.int.phx2.redhat.com
 [10.5.11.23])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 2ECCC800D5C
        for <kvm@vger.kernel.org>; Wed, 24 Jun 2020 16:54:59 +0000 (UTC)
Received: from virtlab701.virt.lab.eng.bos.redhat.com
 (virtlab701.virt.lab.eng.bos.redhat.com [10.19.152.228])
        by smtp.corp.redhat.com (Postfix) with ESMTP id C4EC42B4AB;
        Wed, 24 Jun 2020 16:54:55 +0000 (UTC)
From: Paolo Bonzini <pbonzini@redhat.com>
To: kvm@vger.kernel.org
Cc: mcondotta@redhat.com, Thomas Huth <thuth@redhat.com>
Subject: [PATCH kvm-unit-tests] x86: move IDT away from address 0
Date: Wed, 24 Jun 2020 12:54:55 -0400
Message-Id: <20200624165455.19266-1-pbonzini@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.84 on 10.5.11.23
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Address 0 is also used for the SIPI vector (which is probably something worth
changing as well), and now that we call setup_idt very early the SIPI vector
overwrites the first few bytes of the IDT, and in particular the #DE handler.

Fix this for both 32-bit and 64-bit, even though the different form of the
descriptors meant that only 32-bit showed a failure.

Reported-by: Thomas Huth <thuth@redhat.com>
Signed-off-by: Paolo Bonzini <pbonzini@redhat.com>
---
 x86/cstart.S   | 10 +++++++---
 x86/cstart64.S | 11 ++++++++++-
 2 files changed, 17 insertions(+), 4 deletions(-)

```
#### [PATCH] kvm: x86: limit the maximum number of vPMU fixed counters to 3
##### From: Like Xu <like.xu@linux.intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Like Xu <like.xu@linux.intel.com>
X-Patchwork-Id: 11622215
Return-Path: <SRS0=aKHR=AF=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id B423F90
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 24 Jun 2020 02:00:49 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 99AD72100A
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 24 Jun 2020 02:00:49 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2387692AbgFXCAp (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 23 Jun 2020 22:00:45 -0400
Received: from mga05.intel.com ([192.55.52.43]:12261 "EHLO mga05.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1730898AbgFXCAp (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 23 Jun 2020 22:00:45 -0400
IronPort-SDR: 
 rrS8TqHZfrqc5u3S9NZdlxRhkrtJTqaUj06dnpYqPzPtd2UAStEZksx6uJXTlKkJx/Qblr+o7D
 Bg6ZEWLSoX3Q==
X-IronPort-AV: E=McAfee;i="6000,8403,9661"; a="228978274"
X-IronPort-AV: E=Sophos;i="5.75,273,1589266800";
   d="scan'208";a="228978274"
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from orsmga008.jf.intel.com ([10.7.209.65])
  by fmsmga105.fm.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 23 Jun 2020 19:00:44 -0700
IronPort-SDR: 
 nyusmRsoLpw4RhjXmgQ2g5Ff9IPLjc3Aqcjzxi8zdrmzruuMYtvvxZvnEX1FQas3QtGUjJl3yS
 ns3x6FbD8c/Q==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.75,273,1589266800";
   d="scan'208";a="310649991"
Received: from sqa-gate.sh.intel.com (HELO clx-ap-likexu.tsp.org)
 ([10.239.48.212])
  by orsmga008.jf.intel.com with ESMTP; 23 Jun 2020 19:00:41 -0700
From: Like Xu <like.xu@linux.intel.com>
To: Paolo Bonzini <pbonzini@redhat.com>, kvm@vger.kernel.org
Cc: Sean Christopherson <sean.j.christopherson@intel.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>, linux-kernel@vger.kernel.org,
        Like Xu <like.xu@linux.intel.com>
Subject: [PATCH] kvm: x86: limit the maximum number of vPMU fixed counters to
 3
Date: Wed, 24 Jun 2020 09:59:28 +0800
Message-Id: <20200624015928.118614-1-like.xu@linux.intel.com>
X-Mailer: git-send-email 2.21.3
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Some new Intel platforms (such as TGL) already have the
fourth fixed counter TOPDOWN.SLOTS, but it has not been
fully enabled on KVM and the host.

Therefore, we limit edx.split.num_counters_fixed to 3,
so that it does not break the kvm-unit-tests PMU test
case and bad-handled userspace.

Signed-off-by: Like Xu <like.xu@linux.intel.com>
---
 arch/x86/kvm/cpuid.c | 2 +-
 arch/x86/kvm/pmu.h   | 2 ++
 2 files changed, 3 insertions(+), 1 deletion(-)

```
#### [PATCH 1/2] docs: kvm: add documentation for KVM_CAP_S390_DIAG318
##### From: Collin Walling <walling@linux.ibm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Collin Walling <walling@linux.ibm.com>
X-Patchwork-Id: 11624139
Return-Path: <SRS0=aKHR=AF=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 716841731
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 24 Jun 2020 20:22:41 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 5FFB62084D
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 24 Jun 2020 20:22:41 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2406359AbgFXUWk (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 24 Jun 2020 16:22:40 -0400
Received: from mx0a-001b2d01.pphosted.com ([148.163.156.1]:62600 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S2391392AbgFXUWj (ORCPT
        <rfc822;kvm@vger.kernel.org>); Wed, 24 Jun 2020 16:22:39 -0400
Received: from pps.filterd (m0098393.ppops.net [127.0.0.1])
        by mx0a-001b2d01.pphosted.com (8.16.0.42/8.16.0.42) with SMTP id
 05OK3TxL066233;
        Wed, 24 Jun 2020 16:22:39 -0400
Received: from pps.reinject (localhost [127.0.0.1])
        by mx0a-001b2d01.pphosted.com with ESMTP id 31uwyyxjm5-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Wed, 24 Jun 2020 16:22:38 -0400
Received: from m0098393.ppops.net (m0098393.ppops.net [127.0.0.1])
        by pps.reinject (8.16.0.36/8.16.0.36) with SMTP id 05OK3dfn067092;
        Wed, 24 Jun 2020 16:22:38 -0400
Received: from ppma01dal.us.ibm.com (83.d6.3fa9.ip4.static.sl-reverse.com
 [169.63.214.131])
        by mx0a-001b2d01.pphosted.com with ESMTP id 31uwyyxjkq-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Wed, 24 Jun 2020 16:22:38 -0400
Received: from pps.filterd (ppma01dal.us.ibm.com [127.0.0.1])
        by ppma01dal.us.ibm.com (8.16.0.42/8.16.0.42) with SMTP id
 05OKJtvh005726;
        Wed, 24 Jun 2020 20:22:37 GMT
Received: from b01cxnp22036.gho.pok.ibm.com (b01cxnp22036.gho.pok.ibm.com
 [9.57.198.26])
        by ppma01dal.us.ibm.com with ESMTP id 31uurug6rq-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Wed, 24 Jun 2020 20:22:37 +0000
Received: from b01ledav003.gho.pok.ibm.com (b01ledav003.gho.pok.ibm.com
 [9.57.199.108])
        by b01cxnp22036.gho.pok.ibm.com (8.14.9/8.14.9/NCO v10.0) with ESMTP
 id 05OKMZoC14484082
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Wed, 24 Jun 2020 20:22:35 GMT
Received: from b01ledav003.gho.pok.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 67D95B205F;
        Wed, 24 Jun 2020 20:22:35 +0000 (GMT)
Received: from b01ledav003.gho.pok.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 32EA3B2067;
        Wed, 24 Jun 2020 20:22:35 +0000 (GMT)
Received: from localhost.localdomain.com (unknown [9.85.198.108])
        by b01ledav003.gho.pok.ibm.com (Postfix) with ESMTP;
        Wed, 24 Jun 2020 20:22:35 +0000 (GMT)
From: Collin Walling <walling@linux.ibm.com>
To: kvm@vger.kernel.org, linux-s390@vger.kernel.org
Cc: pbonzini@redhat.com, borntraeger@de.ibm.com, frankja@linux.ibm.com,
        david@redhat.com, cohuck@redhat.com, imbrenda@linux.ibm.com,
        heiko.carstens@de.ibm.com, gor@linux.ibm.com, thuth@redhat.com
Subject: [PATCH 1/2] docs: kvm: add documentation for KVM_CAP_S390_DIAG318
Date: Wed, 24 Jun 2020 16:21:59 -0400
Message-Id: <20200624202200.28209-2-walling@linux.ibm.com>
X-Mailer: git-send-email 2.26.2
In-Reply-To: <20200624202200.28209-1-walling@linux.ibm.com>
References: <20200624202200.28209-1-walling@linux.ibm.com>
MIME-Version: 1.0
X-TM-AS-GCONF: 00
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.216,18.0.687
 definitions=2020-06-24_16:2020-06-24,2020-06-24 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 impostorscore=0 spamscore=0
 clxscore=1015 bulkscore=0 priorityscore=1501 cotscore=-2147483648
 mlxscore=0 lowpriorityscore=0 suspectscore=8 adultscore=0 mlxlogscore=999
 phishscore=0 malwarescore=0 classifier=spam adjust=0 reason=mlx
 scancount=1 engine=8.12.0-2004280000 definitions=main-2006240129
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Documentation for the s390 DIAGNOSE 0x318 instruction handling.

Signed-off-by: Collin Walling <walling@linux.ibm.com>
---
 Documentation/virt/kvm/api.rst | 19 +++++++++++++++++++
 1 file changed, 19 insertions(+)

```
#### [PATCH v3 01/14] vfio/type1: Refactor vfio_iommu_type1_ioctl()
##### From: Liu Yi L <yi.l.liu@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Liu Yi L <yi.l.liu@intel.com>
X-Patchwork-Id: 11622681
Return-Path: <SRS0=aKHR=AF=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 5062E92A
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 24 Jun 2020 08:50:38 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 3434E207DD
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 24 Jun 2020 08:50:38 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2388745AbgFXIs6 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 24 Jun 2020 04:48:58 -0400
Received: from mga01.intel.com ([192.55.52.88]:1312 "EHLO mga01.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S2388488AbgFXIs5 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 24 Jun 2020 04:48:57 -0400
IronPort-SDR: 
 5A/ZSPL9rARm2/YshQjjp/BGuZYVp9klWxuA9DI+BDTbjmojm47maNBTyyN+vXrc86XUEmw60U
 6GGl5ngEQiwQ==
X-IronPort-AV: E=McAfee;i="6000,8403,9661"; a="162484866"
X-IronPort-AV: E=Sophos;i="5.75,274,1589266800";
   d="scan'208";a="162484866"
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from orsmga003.jf.intel.com ([10.7.209.27])
  by fmsmga101.fm.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 24 Jun 2020 01:48:56 -0700
IronPort-SDR: 
 Mshv1yZSW/RDg9neKSin4mVPpUS/9+04XFNCAwKPiJJ5pGmG1KAcsuq7yVn6T5A5Mkcta4MLFd
 sIt1hCcEprBQ==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.75,274,1589266800";
   d="scan'208";a="275624493"
Received: from jacob-builder.jf.intel.com ([10.7.199.155])
  by orsmga003.jf.intel.com with ESMTP; 24 Jun 2020 01:48:55 -0700
From: Liu Yi L <yi.l.liu@intel.com>
To: alex.williamson@redhat.com, eric.auger@redhat.com,
        baolu.lu@linux.intel.com, joro@8bytes.org
Cc: kevin.tian@intel.com, jacob.jun.pan@linux.intel.com,
        ashok.raj@intel.com, yi.l.liu@intel.com, jun.j.tian@intel.com,
        yi.y.sun@intel.com, jean-philippe@linaro.org, peterx@redhat.com,
        hao.wu@intel.com, iommu@lists.linux-foundation.org,
        kvm@vger.kernel.org, linux-kernel@vger.kernel.org
Subject: [PATCH v3 01/14] vfio/type1: Refactor vfio_iommu_type1_ioctl()
Date: Wed, 24 Jun 2020 01:55:14 -0700
Message-Id: <1592988927-48009-2-git-send-email-yi.l.liu@intel.com>
X-Mailer: git-send-email 2.7.4
In-Reply-To: <1592988927-48009-1-git-send-email-yi.l.liu@intel.com>
References: <1592988927-48009-1-git-send-email-yi.l.liu@intel.com>
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This patch refactors the vfio_iommu_type1_ioctl() to use switch instead of
if-else, and each cmd got a helper function.

Cc: Kevin Tian <kevin.tian@intel.com>
CC: Jacob Pan <jacob.jun.pan@linux.intel.com>
Cc: Alex Williamson <alex.williamson@redhat.com>
Cc: Eric Auger <eric.auger@redhat.com>
Cc: Jean-Philippe Brucker <jean-philippe@linaro.org>
Cc: Joerg Roedel <joro@8bytes.org>
Cc: Lu Baolu <baolu.lu@linux.intel.com>
Suggested-by: Christoph Hellwig <hch@infradead.org>
Signed-off-by: Liu Yi L <yi.l.liu@intel.com>
---
 drivers/vfio/vfio_iommu_type1.c | 392 ++++++++++++++++++++++------------------
 1 file changed, 213 insertions(+), 179 deletions(-)

```
#### [PATCH] virtio: VIRTIO_F_IOMMU_PLATFORM -> VIRTIO_F_ACCESS_PLATFORM
##### From: "Michael S. Tsirkin" <mst@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: "Michael S. Tsirkin" <mst@redhat.com>
X-Patchwork-Id: 11624425
Return-Path: <SRS0=aKHR=AF=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 9B0A36C1
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 24 Jun 2020 22:25:58 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 7250A2088E
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 24 Jun 2020 22:25:58 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="ZH6UUHjQ"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2389274AbgFXWZ5 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 24 Jun 2020 18:25:57 -0400
Received: from us-smtp-delivery-1.mimecast.com ([207.211.31.120]:39466 "EHLO
        us-smtp-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org
        with ESMTP id S2388453AbgFXWZ4 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 24 Jun 2020 18:25:56 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1593037553;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:content-type:content-type;
        bh=1qVm+qFHpBcFnajiwKWBoYJyF5SCnRnSLqkqB/nC2LI=;
        b=ZH6UUHjQ2rjcSSkpkeMlAj4F9vgKU0lxT6W9SIxwuyCqba4/ywEh4XR6bvb8xLacF692fA
        2dHVZ9VU3h52lEMsgfYTFFuEGDKHuCLCfU9czgtzfUBQeh/ftXvnCAkuU0wkOnG/Cb+EOb
        MeoI0hz15HF884tLc5zmFgyPCNIndBU=
Received: from mail-wm1-f72.google.com (mail-wm1-f72.google.com
 [209.85.128.72]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-321-BN_p8ucpNWC7b1IziLImnQ-1; Wed, 24 Jun 2020 18:25:52 -0400
X-MC-Unique: BN_p8ucpNWC7b1IziLImnQ-1
Received: by mail-wm1-f72.google.com with SMTP id o138so3339465wme.4
        for <kvm@vger.kernel.org>; Wed, 24 Jun 2020 15:25:51 -0700 (PDT)
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:date:from:to:cc:subject:message-id:mime-version
         :content-disposition;
        bh=1qVm+qFHpBcFnajiwKWBoYJyF5SCnRnSLqkqB/nC2LI=;
        b=EWay/aHy/StK8NVhWvuS3divrLkYGSnr/l/vGPeVtvTnkNxG7UBO855H+4ldzLO65v
         v2BEuKXoA083JA6h7rWmPLGiBvZVlNgF2jBuifztds3Nve7mizOvmFlHKPrUvuTZoOF9
         TEFjO3wTJsrQ+CNg4ugKOjEL3engotaOBdyQm/+jwIWyuukYJp9QTvzcsNLRIe5bv1Rc
         wtAUniyz0zGOskUnxFk30SUKUp7h9B7g7uPknefuudGiiSKih/QUCzu+rs1xfaMPlyg+
         MYnYkn9vcEOwy0+S092de4j3ggKmf7dv6HgkuYHQTrQJc4yUI3Du+BnAc6EH1YcXL8Ig
         rm4A==
X-Gm-Message-State: AOAM532HMhOmJ08SeRELiHkbwbmaQZC5PnsYg6tKXC9EhY+ALmln8jyk
        EVLkbWXa3vuF3vrLjudXxJS5xg/pAuQX4CfEXnqONZ060mSIaRXyF5AcYXB3XaM7/Pdohs9O+mK
        MkS75rs+IeizS
X-Received: by 2002:a5d:5389:: with SMTP id d9mr35177570wrv.77.1593037550095;
        Wed, 24 Jun 2020 15:25:50 -0700 (PDT)
X-Google-Smtp-Source: 
 ABdhPJx5gkNnNw1CL/BcAtvH4812k2atgKf2tuErPH8kANjueWieY9PbxsFzSbaKi8RCVMCZsYBf3w==
X-Received: by 2002:a5d:5389:: with SMTP id d9mr35177546wrv.77.1593037549818;
        Wed, 24 Jun 2020 15:25:49 -0700 (PDT)
Received: from redhat.com (bzq-79-182-31-92.red.bezeqint.net. [79.182.31.92])
        by smtp.gmail.com with ESMTPSA id
 p4sm18772481wrx.63.2020.06.24.15.25.48
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Wed, 24 Jun 2020 15:25:49 -0700 (PDT)
Date: Wed, 24 Jun 2020 18:25:47 -0400
From: "Michael S. Tsirkin" <mst@redhat.com>
To: linux-kernel@vger.kernel.org
Cc: Jeff Dike <jdike@addtoit.com>, Richard Weinberger <richard@nod.at>,
        Anton Ivanov <anton.ivanov@cambridgegreys.com>,
        Jason Wang <jasowang@redhat.com>,
        David Hildenbrand <david@redhat.com>,
        linux-um@lists.infradead.org,
        virtualization@lists.linux-foundation.org, kvm@vger.kernel.org,
        netdev@vger.kernel.org
Subject: [PATCH] virtio: VIRTIO_F_IOMMU_PLATFORM -> VIRTIO_F_ACCESS_PLATFORM
Message-ID: <20200624222540.584772-1-mst@redhat.com>
MIME-Version: 1.0
Content-Disposition: inline
X-Mailer: git-send-email 2.27.0.106.g8ac3dc51b1
X-Mutt-Fcc: =sent
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Rename the bit to match latest virtio spec.
Add a compat macro to avoid breaking existing userspace.

Signed-off-by: Michael S. Tsirkin <mst@redhat.com>
---
 arch/um/drivers/virtio_uml.c       |  2 +-
 drivers/vdpa/ifcvf/ifcvf_base.h    |  2 +-
 drivers/vdpa/vdpa_sim/vdpa_sim.c   |  4 ++--
 drivers/vhost/net.c                |  4 ++--
 drivers/vhost/vdpa.c               |  2 +-
 drivers/virtio/virtio_balloon.c    |  2 +-
 drivers/virtio/virtio_ring.c       |  2 +-
 include/linux/virtio_config.h      |  2 +-
 include/uapi/linux/virtio_config.h | 10 +++++++---
 tools/virtio/linux/virtio_config.h |  2 +-
 10 files changed, 18 insertions(+), 14 deletions(-)

```
#### [PATCH] x86: fix smp_stacktop on 32-bit
##### From: Nadav Amit <namit@vmware.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Nadav Amit <namit@vmware.com>
X-Patchwork-Id: 11624329
Return-Path: <SRS0=aKHR=AF=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id EC53C14F6
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 24 Jun 2020 20:38:26 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 4C8EF2080C
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 24 Jun 2020 20:38:26 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2391490AbgFXUiZ (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 24 Jun 2020 16:38:25 -0400
Received: from ex13-edg-ou-001.vmware.com ([208.91.0.189]:9153 "EHLO
        EX13-EDG-OU-001.vmware.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1727981AbgFXUiX (ORCPT
        <rfc822;kvm@vger.kernel.org>); Wed, 24 Jun 2020 16:38:23 -0400
Received: from sc9-mailhost2.vmware.com (10.113.161.72) by
 EX13-EDG-OU-001.vmware.com (10.113.208.155) with Microsoft SMTP Server id
 15.0.1156.6; Wed, 24 Jun 2020 13:38:18 -0700
Received: from sc2-haas01-esx0118.eng.vmware.com
 (sc2-haas01-esx0118.eng.vmware.com [10.172.44.118])
        by sc9-mailhost2.vmware.com (Postfix) with ESMTP id 6260CB24B4;
        Wed, 24 Jun 2020 16:38:21 -0400 (EDT)
From: Nadav Amit <namit@vmware.com>
To: Paolo Bonzini <pbonzini@redhat.com>
CC: <kvm@vger.kernel.org>, Nadav Amit <namit@vmware.com>
Subject: [PATCH] x86: fix smp_stacktop on 32-bit
Date: Wed, 24 Jun 2020 13:36:02 -0700
Message-ID: <20200624203602.44659-1-namit@vmware.com>
X-Mailer: git-send-email 2.17.1
MIME-Version: 1.0
Received-SPF: None (EX13-EDG-OU-001.vmware.com: namit@vmware.com does not
 designate permitted sender hosts)
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

smp_stacktop in 32-bit is fixed to some magic address. Use the address
of the memory that was reserved for the stack instead.

Signed-off-by: Nadav Amit <namit@vmware.com>
---
 x86/cstart.S | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
