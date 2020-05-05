#### [Bug 207551] unable to handle kernel paging request for VMX
##### From: bugzilla-daemon@bugzilla.kernel.org

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: bugzilla-daemon@bugzilla.kernel.org
X-Patchwork-Id: 11526821
Return-Path: <SRS0=Q5Yu=6S=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 91C7A1668
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon,  4 May 2020 17:08:24 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 79B6A20721
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon,  4 May 2020 17:08:24 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1730035AbgEDRIX convert rfc822-to-8bit (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 4 May 2020 13:08:23 -0400
Received: from mail.kernel.org ([198.145.29.99]:41812 "EHLO mail.kernel.org"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1730004AbgEDRIW (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 4 May 2020 13:08:22 -0400
From: bugzilla-daemon@bugzilla.kernel.org
To: kvm@vger.kernel.org
Subject: [Bug 207551] unable to handle kernel paging request for VMX
Date: Mon, 04 May 2020 17:08:21 +0000
X-Bugzilla-Reason: None
X-Bugzilla-Type: changed
X-Bugzilla-Watch-Reason: AssignedTo virtualization_kvm@kernel-bugs.osdl.org
X-Bugzilla-Product: Virtualization
X-Bugzilla-Component: kvm
X-Bugzilla-Version: unspecified
X-Bugzilla-Keywords: 
X-Bugzilla-Severity: normal
X-Bugzilla-Who: sean.j.christopherson@intel.com
X-Bugzilla-Status: NEW
X-Bugzilla-Resolution: 
X-Bugzilla-Priority: P1
X-Bugzilla-Assigned-To: virtualization_kvm@kernel-bugs.osdl.org
X-Bugzilla-Flags: 
X-Bugzilla-Changed-Fields: 
Message-ID: <bug-207551-28872-CSaG1fmToc@https.bugzilla.kernel.org/>
In-Reply-To: <bug-207551-28872@https.bugzilla.kernel.org/>
References: <bug-207551-28872@https.bugzilla.kernel.org/>
X-Bugzilla-URL: https://bugzilla.kernel.org/
Auto-Submitted: auto-generated
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

https://bugzilla.kernel.org/show_bug.cgi?id=207551

--- Comment #2 from Sean Christopherson (sean.j.christopherson@intel.com) ---
Ugh, I forgot much of a trainwreck the inline VM-Enter asm blob was in 4.19. 
Fixing this isn't nearly as straightforward as it should be, i.e. it'll take a
while to get a proper patch sent.

In the meantime, you should be able to avoid this by deleting the zeroing of
%rcx, e.g.

                "xor %%edi, %%edi \n\t"

```
#### [GIT PULL] vhost: fixes
##### From: "Michael S. Tsirkin" <mst@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: "Michael S. Tsirkin" <mst@redhat.com>
X-Patchwork-Id: 11525643
Return-Path: <SRS0=Q5Yu=6S=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 93366913
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon,  4 May 2020 12:15:53 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 7AC38206A5
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon,  4 May 2020 12:15:53 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="BoupBZji"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728734AbgEDMPt (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 4 May 2020 08:15:49 -0400
Received: from us-smtp-delivery-1.mimecast.com ([205.139.110.120]:20421 "EHLO
        us-smtp-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org
        with ESMTP id S1728592AbgEDMPs (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 4 May 2020 08:15:48 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1588594547;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:content-type:content-type;
        bh=q5qLe/YbLa8g+76m0wKCJz9sEFGWHkbwiwLtZx/ZVFk=;
        b=BoupBZjinqWOG60CRL1nwi+ttchJJbX0UNYWrTc0U4ZfNvu8j01xdyxYUaoMen9ob3/VDH
        7+LD20bUUoSII35T8mXnqx1GIKOuO0P4it5g/LcjFyLFTrwGngSlhuHxMoamfcPP0o91iJ
        2DHfcVLnxELFkWrWpBwBu80wkVqpQRI=
Received: from mail-wm1-f71.google.com (mail-wm1-f71.google.com
 [209.85.128.71]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-346-CKNQnk91P8CmDVosj7Xg8g-1; Mon, 04 May 2020 08:15:43 -0400
X-MC-Unique: CKNQnk91P8CmDVosj7Xg8g-1
Received: by mail-wm1-f71.google.com with SMTP id j5so4754081wmi.4
        for <kvm@vger.kernel.org>; Mon, 04 May 2020 05:15:43 -0700 (PDT)
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:date:from:to:cc:subject:message-id:mime-version
         :content-disposition;
        bh=q5qLe/YbLa8g+76m0wKCJz9sEFGWHkbwiwLtZx/ZVFk=;
        b=OOaJQ76+aFh9ivsxBHSoYkxc2H0aFoxrvb3HVcE5OalE0OmZbXeaJcXRsAOJE1GAGE
         2UKFrZGahU2Gfm4WV3iISDiBFGkIr8YnrifF3uZnB6h5WteUJ1Tgec34AMQ660C30mZt
         7K3mnpOJ4F78w7IoK/243MWXyFq8ioVVWo4XP26NXMETeJwv23IdZXm9niowlUqXQLvN
         GZLdfv16dZn+EWbZKqdNHEGH8XNRICzeFhHeYzsRbuR3w48Z+cwm6FZvM7NaGL1e6Cdb
         TwT55AnkH0TF1u9XLF5M+9vlxho2z07/Pe6RB4JdwuiXFcjMzKOwRvc+HqUOyBuaCDQA
         pcBg==
X-Gm-Message-State: AGi0PuZB9XBOAKuvVnbwahEngcuwmi/bXxQBXuXef5CuFev4nJg9N/n4
        +3akgWwPmALse8hOxOflPLMW7Tx2hWK2NM8xFn6BGuoIJxh/2F202uLRSgTw7TsSeISZlTM/ypp
        lkiQxukiXLqFn
X-Received: by 2002:a1c:4e06:: with SMTP id g6mr14085622wmh.186.1588594542756;
        Mon, 04 May 2020 05:15:42 -0700 (PDT)
X-Google-Smtp-Source: 
 APiQypIAWbJGa73k/tJK0QUm1DfayD29dwoou70hN0HhHJnMSNr/UKPo3sTuvVCseBF2z+tgI/8tzQ==
X-Received: by 2002:a1c:4e06:: with SMTP id g6mr14085601wmh.186.1588594542532;
        Mon, 04 May 2020 05:15:42 -0700 (PDT)
Received: from redhat.com (bzq-109-66-7-121.red.bezeqint.net. [109.66.7.121])
        by smtp.gmail.com with ESMTPSA id
 s24sm13455322wmj.28.2020.05.04.05.15.40
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Mon, 04 May 2020 05:15:41 -0700 (PDT)
Date: Mon, 4 May 2020 08:15:40 -0400
From: "Michael S. Tsirkin" <mst@redhat.com>
To: Linus Torvalds <torvalds@linux-foundation.org>
Cc: kvm@vger.kernel.org, virtualization@lists.linux-foundation.org,
        netdev@vger.kernel.org, linux-kernel@vger.kernel.org,
        justin.he@arm.com, ldigby@redhat.com, mst@redhat.com, n.b@live.com,
        stefanha@redhat.com
Subject: [GIT PULL] vhost: fixes
Message-ID: <20200504081540-mutt-send-email-mst@kernel.org>
MIME-Version: 1.0
Content-Disposition: inline
X-Mutt-Fcc: =sent
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The following changes since commit 6a8b55ed4056ea5559ebe4f6a4b247f627870d4c:

  Linux 5.7-rc3 (2020-04-26 13:51:02 -0700)

are available in the Git repository at:

  https://git.kernel.org/pub/scm/linux/kernel/git/mst/vhost.git tags/for_linus

for you to fetch changes up to 0b841030625cde5f784dd62aec72d6a766faae70:

  vhost: vsock: kick send_pkt worker once device is started (2020-05-02 10:28:21 -0400)

----------------------------------------------------------------
virtio: fixes

A couple of bug fixes.

Signed-off-by: Michael S. Tsirkin <mst@redhat.com>

----------------------------------------------------------------
Jia He (1):
      vhost: vsock: kick send_pkt worker once device is started

Stefan Hajnoczi (1):
      virtio-blk: handle block_device_operations callbacks after hot unplug

 drivers/block/virtio_blk.c | 86 +++++++++++++++++++++++++++++++++++++++++-----
 drivers/vhost/vsock.c      |  5 +++
 2 files changed, 83 insertions(+), 8 deletions(-)
```
#### [PATCH Kernel v18 1/7] vfio: UAPI for migration interface for device state
##### From: Kirti Wankhede <kwankhede@nvidia.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Kirti Wankhede <kwankhede@nvidia.com>
X-Patchwork-Id: 11526683
Return-Path: <SRS0=Q5Yu=6S=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id EA9B415AB
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon,  4 May 2020 16:32:23 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id C97AE20705
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon,  4 May 2020 16:32:23 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=nvidia.com header.i=@nvidia.com
 header.b="ovmFnVyo"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729669AbgEDQcX (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 4 May 2020 12:32:23 -0400
Received: from hqnvemgate26.nvidia.com ([216.228.121.65]:16259 "EHLO
        hqnvemgate26.nvidia.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1729604AbgEDQcW (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 4 May 2020 12:32:22 -0400
Received: from hqpgpgate101.nvidia.com (Not Verified[216.228.121.13]) by
 hqnvemgate26.nvidia.com (using TLS: TLSv1.2, DES-CBC3-SHA)
        id <B5eb043890001>; Mon, 04 May 2020 09:32:09 -0700
Received: from hqmail.nvidia.com ([172.20.161.6])
  by hqpgpgate101.nvidia.com (PGP Universal service);
  Mon, 04 May 2020 09:32:22 -0700
X-PGP-Universal: processed;
        by hqpgpgate101.nvidia.com on Mon, 04 May 2020 09:32:22 -0700
Received: from HQMAIL101.nvidia.com (172.20.187.10) by HQMAIL105.nvidia.com
 (172.20.187.12) with Microsoft SMTP Server (TLS) id 15.0.1473.3; Mon, 4 May
 2020 16:32:21 +0000
Received: from kwankhede-dev.nvidia.com (10.124.1.5) by HQMAIL101.nvidia.com
 (172.20.187.10) with Microsoft SMTP Server (TLS) id 15.0.1473.3 via Frontend
 Transport; Mon, 4 May 2020 16:32:15 +0000
From: Kirti Wankhede <kwankhede@nvidia.com>
To: <alex.williamson@redhat.com>, <cjia@nvidia.com>
CC: <kevin.tian@intel.com>, <ziye.yang@intel.com>,
        <changpeng.liu@intel.com>, <yi.l.liu@intel.com>,
        <mlevitsk@redhat.com>, <eskultet@redhat.com>, <cohuck@redhat.com>,
        <dgilbert@redhat.com>, <jonathan.davies@nutanix.com>,
        <eauger@redhat.com>, <aik@ozlabs.ru>, <pasic@linux.ibm.com>,
        <felipe@nutanix.com>, <Zhengxiao.zx@Alibaba-inc.com>,
        <shuangtai.tst@alibaba-inc.com>, <Ken.Xue@amd.com>,
        <zhi.a.wang@intel.com>, <yan.y.zhao@intel.com>,
        <qemu-devel@nongnu.org>, <kvm@vger.kernel.org>,
        Kirti Wankhede <kwankhede@nvidia.com>
Subject: [PATCH Kernel v18 1/7] vfio: UAPI for migration interface for device
 state
Date: Mon, 4 May 2020 21:28:53 +0530
Message-ID: <1588607939-26441-2-git-send-email-kwankhede@nvidia.com>
X-Mailer: git-send-email 2.7.0
In-Reply-To: <1588607939-26441-1-git-send-email-kwankhede@nvidia.com>
References: <1588607939-26441-1-git-send-email-kwankhede@nvidia.com>
X-NVConfidentiality: public
MIME-Version: 1.0
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=nvidia.com; s=n1;
        t=1588609929; bh=s4Iv0GJDj+1bhl4jbE8YcxRvsfl81dyjXBeOzB1RdI0=;
        h=X-PGP-Universal:From:To:CC:Subject:Date:Message-ID:X-Mailer:
         In-Reply-To:References:X-NVConfidentiality:MIME-Version:
         Content-Type;
        b=ovmFnVyohig/KuDQa0HbHvS3tH9giqkbs+jnwIAumdMc+gtv0Pay7ojojQjiXfbYc
         V+K1I093YciTBciEAX1IwFZyY1FC3zBtoWA5u9bdVGnIYmcUAvdOdqJSdtooFGZYdg
         bi6VPuPvkyxZcC59zAk+pGF4lH+bEs/Y/oKUKHVW/s5jz/7HX71ox0ptP7ZO+wvw6R
         DQ/3z2njIEa8gLCovOTlECn0PRhUXjO9mEadLMJ0pPmxNUqK9I4LiaBnT8tyMQYKuc
         jONXh3kiHRP9P3GdWQvZ+QQ0eJX/XijHBC3psDQfNytAf+vOIXDCdVAnmummCVcx35
         NzN/Sc92dFLAQ==
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

- Defined MIGRATION region type and sub-type.

- Defined vfio_device_migration_info structure which will be placed at the
  0th offset of migration region to get/set VFIO device related
  information. Defined members of structure and usage on read/write access.

- Defined device states and state transition details.

- Defined sequence to be followed while saving and resuming VFIO device.

Signed-off-by: Kirti Wankhede <kwankhede@nvidia.com>
Reviewed-by: Neo Jia <cjia@nvidia.com>
---
 include/uapi/linux/vfio.h | 228 ++++++++++++++++++++++++++++++++++++++++++++++
 1 file changed, 228 insertions(+)

```
#### [PATCH] KVM: Fix a warning in __kvm_gfn_to_hva_cache_init()
##### From: Peter Xu <peterx@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 8bit
X-Patchwork-Submitter: Peter Xu <peterx@redhat.com>
X-Patchwork-Id: 11527457
Return-Path: <SRS0=Q5Yu=6S=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 2F79C81
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon,  4 May 2020 19:05:37 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 17260206C0
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon,  4 May 2020 19:05:37 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="RNKVBW/k"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727950AbgEDTFe (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 4 May 2020 15:05:34 -0400
Received: from us-smtp-delivery-1.mimecast.com ([207.211.31.120]:50728 "EHLO
        us-smtp-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org
        with ESMTP id S1727855AbgEDTFc (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 4 May 2020 15:05:32 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1588619131;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:content-type:content-type:
         content-transfer-encoding:content-transfer-encoding;
        bh=qIVg0JQeyCu7kn+dY+lPaTgPQT/NdBxPgGWYbUJIIXA=;
        b=RNKVBW/kf7N18LPuDJNpGkbK9WE5VtNg0xVlxj1q4mBz8Z2Wwy39VN83wxFqrrwh0omSZ+
        +lX7zlbBu6BogIXPURUhAtkGJ42z5lfG0DO7TA7Vml21aMeDDRxoJFpOmN/OGgCIBMV3LW
        LErSltT83vlvN/kmg1Fu9Iu4abS1L8Y=
Received: from mail-qv1-f72.google.com (mail-qv1-f72.google.com
 [209.85.219.72]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-149-A86VbsMsN5e0KR8N3EXGaQ-1; Mon, 04 May 2020 15:05:30 -0400
X-MC-Unique: A86VbsMsN5e0KR8N3EXGaQ-1
Received: by mail-qv1-f72.google.com with SMTP id fe18so485186qvb.11
        for <kvm@vger.kernel.org>; Mon, 04 May 2020 12:05:30 -0700 (PDT)
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:mime-version
         :content-transfer-encoding;
        bh=qIVg0JQeyCu7kn+dY+lPaTgPQT/NdBxPgGWYbUJIIXA=;
        b=DrBLiADI4/OqYd3k/jQ5CzMRLwN8DEYi1O8aaG9xa/YTXoz8vjU3GHMHU7xPgVnIJ2
         gI9rPu8B+2K+k8Ba0PLUBjPByc8T0HFF/BAcTWf1DYXwCLVvNZxcAQ8UqZOvSJsHvPTb
         ePaRp5rVvVe+WcBTRcMr8pSa0698Ev6KFQGFEPQli5Im3zNEeTgCO+ymxxhJMSC6pVcN
         0CFibp3v6Ga00fvFEilQv3Hvi53f0WWVNGtlo1h2chJgGxbY4j6jnmv67aBJr0pwvhV7
         znybitykfD4MCR7SY6WbS0PxzGEdrEJ7TLntqbBlkZrgdrTFsrtDDrKzpI7nPMevUoJ0
         5K5Q==
X-Gm-Message-State: AGi0PubK0jw+HDHenEarjxV1E5U4ZkSlCQsARaKGgdER+cVTI2md/wGH
        eNcAynBubx/YRKzUA0t9eRolsh+8yTvbsQy7ef+WzV9M1Awh2t42OsfUn5GJPHl6Ih1lF4SfcL6
        ZKf8UN7TThMj8
X-Received: by 2002:ac8:44d6:: with SMTP id b22mr640167qto.366.1588619128935;
        Mon, 04 May 2020 12:05:28 -0700 (PDT)
X-Google-Smtp-Source: 
 APiQypICFt1DWmxwrFZqvsi6oraH8Ztk1a0hOa6r+UUKVpePo5HU+yUDiugMPSKG00KJ7y+T26omxQ==
X-Received: by 2002:ac8:44d6:: with SMTP id b22mr640146qto.366.1588619128682;
        Mon, 04 May 2020 12:05:28 -0700 (PDT)
Received: from xz-x1.redhat.com ([2607:9880:19c0:32::2])
        by smtp.gmail.com with ESMTPSA id
 p22sm12111549qte.2.2020.05.04.12.05.27
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Mon, 04 May 2020 12:05:27 -0700 (PDT)
From: Peter Xu <peterx@redhat.com>
To: kvm@vger.kernel.org, linux-kernel@vger.kernel.org
Cc: Paolo Bonzini <pbonzini@redhat.com>, peterx@redhat.com
Subject: [PATCH] KVM: Fix a warning in __kvm_gfn_to_hva_cache_init()
Date: Mon,  4 May 2020 15:05:26 -0400
Message-Id: <20200504190526.84456-1-peterx@redhat.com>
X-Mailer: git-send-email 2.26.2
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

GCC 10.0.1 gives me this warning when building KVM:

  warning: ‘nr_pages_avail’ may be used uninitialized in this function [-Wmaybe-uninitialized]
  2442 |  for ( ; start_gfn <= end_gfn; start_gfn += nr_pages_avail) {

It should not happen, but silent it.

Signed-off-by: Peter Xu <peterx@redhat.com>
---
 virt/kvm/kvm_main.c | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
#### [PATCH] kvm: ioapic: Restrict lazy EOI update to edge-triggered interrupts
##### From: Paolo Bonzini <pbonzini@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Paolo Bonzini <pbonzini@redhat.com>
X-Patchwork-Id: 11526675
Return-Path: <SRS0=Q5Yu=6S=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 94F6515AB
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon,  4 May 2020 16:29:04 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 7B59224959
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon,  4 May 2020 16:29:04 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="Esnrn88K"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729598AbgEDQ3A (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 4 May 2020 12:29:00 -0400
Received: from us-smtp-delivery-1.mimecast.com ([207.211.31.120]:54661 "EHLO
        us-smtp-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org
        with ESMTP id S1729590AbgEDQ3A (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 4 May 2020 12:29:00 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1588609739;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc; bh=vyYYYfDE98dZ74NRX6gFiGAARZEAda2ko5w/z7U1TOY=;
        b=Esnrn88KsElsfJxD8Dn6pk1Cca7jpfOPsFAUv15nAzf5BVB3R6aHtNDIiqfqRT7dDHInw8
        wxtXHwC3DSR3o/BMdKv1qanOOdLqUqD4VcAhaM0gzCFa590ya9NN+UYoJxbHfRIBtecxtG
        CM0hcoHH7dtayFyy4sED4xAoyS0zW5I=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-423-desGePx4MY68frG5i3_GMQ-1; Mon, 04 May 2020 12:28:55 -0400
X-MC-Unique: desGePx4MY68frG5i3_GMQ-1
Received: from smtp.corp.redhat.com (int-mx02.intmail.prod.int.phx2.redhat.com
 [10.5.11.12])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 23F818014D5;
        Mon,  4 May 2020 16:28:54 +0000 (UTC)
Received: from virtlab511.virt.lab.eng.bos.redhat.com
 (virtlab511.virt.lab.eng.bos.redhat.com [10.19.152.198])
        by smtp.corp.redhat.com (Postfix) with ESMTP id A1FDA60C81;
        Mon,  4 May 2020 16:28:53 +0000 (UTC)
From: Paolo Bonzini <pbonzini@redhat.com>
To: linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Cc: Suravee Suthikulpanit <suravee.suthikulpanit@amd.com>
Subject: [PATCH] kvm: ioapic: Restrict lazy EOI update to edge-triggered
 interrupts
Date: Mon,  4 May 2020 12:28:52 -0400
Message-Id: <20200504162852.404422-1-pbonzini@redhat.com>
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.12
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Commit f458d039db7e ("kvm: ioapic: Lazy update IOAPIC EOI") introduces
the following infinite loop:

BUG: stack guard page was hit at 000000008f595917 \
(stack is 00000000bdefe5a4..00000000ae2b06f5)
kernel stack overflow (double-fault): 0000 [#1] SMP NOPTI
RIP: 0010:kvm_set_irq+0x51/0x160 [kvm]
Call Trace:
 irqfd_resampler_ack+0x32/0x90 [kvm]
 kvm_notify_acked_irq+0x62/0xd0 [kvm]
 kvm_ioapic_update_eoi_one.isra.0+0x30/0x120 [kvm]
 ioapic_set_irq+0x20e/0x240 [kvm]
 kvm_ioapic_set_irq+0x5c/0x80 [kvm]
 kvm_set_irq+0xbb/0x160 [kvm]
 ? kvm_hv_set_sint+0x20/0x20 [kvm]
 irqfd_resampler_ack+0x32/0x90 [kvm]
 kvm_notify_acked_irq+0x62/0xd0 [kvm]
 kvm_ioapic_update_eoi_one.isra.0+0x30/0x120 [kvm]
 ioapic_set_irq+0x20e/0x240 [kvm]
 kvm_ioapic_set_irq+0x5c/0x80 [kvm]
 kvm_set_irq+0xbb/0x160 [kvm]
 ? kvm_hv_set_sint+0x20/0x20 [kvm]
....

The re-entrancy happens because the irq state is the OR of
the interrupt state and the resamplefd state.  That is, we don't
want to show the state as 0 until we've had a chance to set the
resamplefd.  But if the interrupt has _not_ gone low then
ioapic_set_irq is invoked again, causing an infinite loop.

This can only happen for a level-triggered interrupt, otherwise
irqfd_inject would immediately set the KVM_USERSPACE_IRQ_SOURCE_ID high
and then low.  Fortunately, in the case of level-triggered interrupts the VMEXIT already happens because
TMR is set.  Thus, fix the bug by restricting the lazy invocation
of the ack notifier to edge-triggered interrupts, the only ones that
need it.

Tested-by: Suravee Suthikulpanit <suravee.suthikulpanit@amd.com>
Reported-by: borisvk@bstnet.org
Suggested-by: Paolo Bonzini <pbonzini@redhat.com>
Link: https://www.spinics.net/lists/kvm/msg213512.html
Fixes: f458d039db7e ("kvm: ioapic: Lazy update IOAPIC EOI")
Bugzilla: https://bugzilla.kernel.org/show_bug.cgi?id=207489
Signed-off-by: Suravee Suthikulpanit <suravee.suthikulpanit@amd.com>
---
 arch/x86/kvm/ioapic.c | 10 +++++-----
 1 file changed, 5 insertions(+), 5 deletions(-)

```
#### [PATCH] kvm: ioapic: Restrict lazy EOI update to edge-triggered interrupts
##### From: Paolo Bonzini <pbonzini@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Paolo Bonzini <pbonzini@redhat.com>
X-Patchwork-Id: 11526677
Return-Path: <SRS0=Q5Yu=6S=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 7266414C0
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon,  4 May 2020 16:29:30 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 55B8F206D9
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon,  4 May 2020 16:29:30 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="gNNs7gzK"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729626AbgEDQ31 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 4 May 2020 12:29:27 -0400
Received: from us-smtp-1.mimecast.com ([205.139.110.61]:36203 "EHLO
        us-smtp-delivery-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S1729614AbgEDQ31 (ORCPT
        <rfc822;kvm@vger.kernel.org>); Mon, 4 May 2020 12:29:27 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1588609765;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc; bh=u9wd2N5ZqA9eKBgCPlh0DHQo6aOCCyRgqsmnMGl7hh0=;
        b=gNNs7gzK+PcP1UxfPL5XIdWtY4c9nzWZGPfzg2asIXDjm3PxZggBRtWQ8TuhUznQ8ydgpv
        8t6bYfDwkA8HzOpp3dHO8JbFIfRfaOBZxPo+9sMsMGFYhBS07W2lYuWvT7hCQ7QNy9wp2K
        LD9/tBuAHBBo1Lafxxrvm8RT8dW69Mo=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-32-Byz0ITRxPLWl15gL0K7H1g-1; Mon, 04 May 2020 12:29:24 -0400
X-MC-Unique: Byz0ITRxPLWl15gL0K7H1g-1
Received: from smtp.corp.redhat.com (int-mx04.intmail.prod.int.phx2.redhat.com
 [10.5.11.14])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 2430E8014D5;
        Mon,  4 May 2020 16:29:23 +0000 (UTC)
Received: from virtlab511.virt.lab.eng.bos.redhat.com
 (virtlab511.virt.lab.eng.bos.redhat.com [10.19.152.198])
        by smtp.corp.redhat.com (Postfix) with ESMTP id D2D875D9D5;
        Mon,  4 May 2020 16:29:22 +0000 (UTC)
From: Paolo Bonzini <pbonzini@redhat.com>
To: linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Subject: [PATCH] kvm: ioapic: Restrict lazy EOI update to edge-triggered
 interrupts
Date: Mon,  4 May 2020 12:29:22 -0400
Message-Id: <20200504162922.404532-1-pbonzini@redhat.com>
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.14
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Commit f458d039db7e ("kvm: ioapic: Lazy update IOAPIC EOI") introduces
the following infinite loop:

BUG: stack guard page was hit at 000000008f595917 \
(stack is 00000000bdefe5a4..00000000ae2b06f5)
kernel stack overflow (double-fault): 0000 [#1] SMP NOPTI
RIP: 0010:kvm_set_irq+0x51/0x160 [kvm]
Call Trace:
 irqfd_resampler_ack+0x32/0x90 [kvm]
 kvm_notify_acked_irq+0x62/0xd0 [kvm]
 kvm_ioapic_update_eoi_one.isra.0+0x30/0x120 [kvm]
 ioapic_set_irq+0x20e/0x240 [kvm]
 kvm_ioapic_set_irq+0x5c/0x80 [kvm]
 kvm_set_irq+0xbb/0x160 [kvm]
 ? kvm_hv_set_sint+0x20/0x20 [kvm]
 irqfd_resampler_ack+0x32/0x90 [kvm]
 kvm_notify_acked_irq+0x62/0xd0 [kvm]
 kvm_ioapic_update_eoi_one.isra.0+0x30/0x120 [kvm]
 ioapic_set_irq+0x20e/0x240 [kvm]
 kvm_ioapic_set_irq+0x5c/0x80 [kvm]
 kvm_set_irq+0xbb/0x160 [kvm]
 ? kvm_hv_set_sint+0x20/0x20 [kvm]
....

The re-entrancy happens because the irq state is the OR of
the interrupt state and the resamplefd state.  That is, we don't
want to show the state as 0 until we've had a chance to set the
resamplefd.  But if the interrupt has _not_ gone low then
ioapic_set_irq is invoked again, causing an infinite loop.

This can only happen for a level-triggered interrupt, otherwise
irqfd_inject would immediately set the KVM_USERSPACE_IRQ_SOURCE_ID high
and then low.  Fortunately, in the case of level-triggered interrupts the VMEXIT already happens because
TMR is set.  Thus, fix the bug by restricting the lazy invocation
of the ack notifier to edge-triggered interrupts, the only ones that
need it.

Tested-by: Suravee Suthikulpanit <suravee.suthikulpanit@amd.com>
Reported-by: borisvk@bstnet.org
Suggested-by: Paolo Bonzini <pbonzini@redhat.com>
Link: https://www.spinics.net/lists/kvm/msg213512.html
Fixes: f458d039db7e ("kvm: ioapic: Lazy update IOAPIC EOI")
Bugzilla: https://bugzilla.kernel.org/show_bug.cgi?id=207489
Signed-off-by: Paolo Bonzini <pbonzini@redhat.com>
---
 arch/x86/kvm/ioapic.c | 10 +++++-----
 1 file changed, 5 insertions(+), 5 deletions(-)

```
#### [PATCH] KVM: nVMX: Replace a BUG_ON(1) with BUG() to squash clang warning
##### From: Sean Christopherson <sean.j.christopherson@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Sean Christopherson <sean.j.christopherson@intel.com>
X-Patchwork-Id: 11526549
Return-Path: <SRS0=Q5Yu=6S=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id C9BA892A
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon,  4 May 2020 15:35:10 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id BBD04206D7
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon,  4 May 2020 15:35:10 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729422AbgEDPfI (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 4 May 2020 11:35:08 -0400
Received: from mga02.intel.com ([134.134.136.20]:8045 "EHLO mga02.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726509AbgEDPfH (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 4 May 2020 11:35:07 -0400
IronPort-SDR: 
 E4U8WfJvNQf6Ivjag9VoKvEDaRXwmAJqDa+o/HMvZkzZHJZPvCvRciT4+dQ7qVYm5po8yUEWZt
 ItuySFAmcB5A==
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from orsmga008.jf.intel.com ([10.7.209.65])
  by orsmga101.jf.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 04 May 2020 08:35:07 -0700
IronPort-SDR: 
 wNG88MpeGTwh5P0sEpGjUgEXobg6Tuh4Dw7tF62ERYYy7EVobg60aKBCGDXVM1zVyjZPLLOarf
 zL/glzex/T+g==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.73,352,1583222400";
   d="scan'208";a="295533046"
Received: from sjchrist-coffee.jf.intel.com ([10.54.74.152])
  by orsmga008.jf.intel.com with ESMTP; 04 May 2020 08:35:07 -0700
From: Sean Christopherson <sean.j.christopherson@intel.com>
To: Paolo Bonzini <pbonzini@redhat.com>
Cc: Sean Christopherson <sean.j.christopherson@intel.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>, kvm@vger.kernel.org,
        clang-built-linux@googlegroups.com, linux-kernel@vger.kernel.org
Subject: [PATCH] KVM: nVMX: Replace a BUG_ON(1) with BUG() to squash clang
 warning
Date: Mon,  4 May 2020 08:35:06 -0700
Message-Id: <20200504153506.28898-1-sean.j.christopherson@intel.com>
X-Mailer: git-send-email 2.26.0
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Use BUG() in the impossible-to-hit default case when switching on the
scope of INVEPT to squash a warning with clang 11 due to clang treating
the BUG_ON() as conditional.

  >> arch/x86/kvm/vmx/nested.c:5246:3: warning: variable 'roots_to_free'
     is used uninitialized whenever 'if' condition is false
     [-Wsometimes-uninitialized]
                   BUG_ON(1);

Reported-by: kbuild test robot <lkp@intel.com>
Fixes: ce8fe7b77bd8 ("KVM: nVMX: Free only the affected contexts when emulating INVEPT")
Signed-off-by: Sean Christopherson <sean.j.christopherson@intel.com>
---
 arch/x86/kvm/vmx/nested.c | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
#### [PATCH] KVM: selftests: Fix build for evmcs.h
##### From: Peter Xu <peterx@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Peter Xu <peterx@redhat.com>
X-Patchwork-Id: 11527661
Return-Path: <SRS0=Q5Yu=6S=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 8CADB81
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon,  4 May 2020 22:06:18 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 73E0B206C0
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon,  4 May 2020 22:06:18 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="L5MjTEka"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727890AbgEDWGQ (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 4 May 2020 18:06:16 -0400
Received: from us-smtp-1.mimecast.com ([207.211.31.81]:51644 "EHLO
        us-smtp-delivery-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S1726334AbgEDWGO (ORCPT
        <rfc822;kvm@vger.kernel.org>); Mon, 4 May 2020 18:06:14 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1588629972;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=ldiUHTo4H9fOXrlK9CdJK+WOClXBqbBS4tE+9OydXYY=;
        b=L5MjTEkanNOZ7Enp+O6rAlTi4fu/Qw2VOyXYtM95dze+2RLqmXjHP5NCWsKq9B4jDY6Nki
        j3S1u86dwC0M5G0x1iCGUNHjbB9vKc0M9IHmXqac+/6sjLVTzi2V98KvPnQ4FE+FrWuXJ6
        FlU0NkpllTiUFDDklLDOSEuZMGFOVxk=
Received: from mail-qt1-f200.google.com (mail-qt1-f200.google.com
 [209.85.160.200]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-507-IQgfwITeMSOXx403ewmwjw-1; Mon, 04 May 2020 18:06:11 -0400
X-MC-Unique: IQgfwITeMSOXx403ewmwjw-1
Received: by mail-qt1-f200.google.com with SMTP id g8so1224503qtq.2
        for <kvm@vger.kernel.org>; Mon, 04 May 2020 15:06:11 -0700 (PDT)
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:mime-version
         :content-transfer-encoding;
        bh=ldiUHTo4H9fOXrlK9CdJK+WOClXBqbBS4tE+9OydXYY=;
        b=gcEg6WLna068ctqYDVvWSZbz/+cBlWBtoFXYskOMImUF4ABLq/27DqFo0COjzN9mJ2
         somipdaaO77cNz6hTUhL13qXAlYLC0MjQiZVzCOofJj942tyiC5gNJFhl4xILL/b4c6I
         DPQjJghFkJSzHDXSkacY43Q35VqZgYHXLqPubHiwRoKUVBCX//w77mW6OO5RtL5DqZwV
         WFacIE4d/FX0DvOGxfQboc3aIjgoIrrp/+04hewabylbX3fiZiJFsE/UPXxSp/TtXSll
         7C7t6LzeMLvsnX2bsEBfWysFR/MyKsdyvtBTOdxds9FgdnbTOAjMw04jgPFCGJQ1gfOF
         1ZaA==
X-Gm-Message-State: AGi0PuY5GU1MTQrKrkrDFGO9NTMylrHcX6Gj6qXsCuWIxzRE2yMp0D2n
        icoFEEoOtimUKex7OGtte2zXQSiqcIOgn453+D0RFyvkC8wu6zPJHkAPv2CUjEgljRQ+YT5Ubpq
        SBBxmVrsMH4Px
X-Received: by 2002:a37:9ed5:: with SMTP id h204mr526772qke.446.1588629970536;
        Mon, 04 May 2020 15:06:10 -0700 (PDT)
X-Google-Smtp-Source: 
 APiQypI5ratxafcXWdXR+7DiDQCFg9ET2QsWxNKpq+Gblz9ExXQG316TfcD4OkoqLvruQxBYtCMisg==
X-Received: by 2002:a37:9ed5:: with SMTP id h204mr526742qke.446.1588629970165;
        Mon, 04 May 2020 15:06:10 -0700 (PDT)
Received: from xz-x1.redhat.com ([2607:9880:19c0:32::2])
        by smtp.gmail.com with ESMTPSA id
 w18sm279534qkw.113.2020.05.04.15.06.08
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Mon, 04 May 2020 15:06:09 -0700 (PDT)
From: Peter Xu <peterx@redhat.com>
To: kvm@vger.kernel.org, linux-kernel@vger.kernel.org
Cc: peterx@redhat.com, Paolo Bonzini <pbonzini@redhat.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>
Subject: [PATCH] KVM: selftests: Fix build for evmcs.h
Date: Mon,  4 May 2020 18:06:07 -0400
Message-Id: <20200504220607.99627-1-peterx@redhat.com>
X-Mailer: git-send-email 2.26.2
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

I got this error when building kvm selftests:

/usr/bin/ld: /home/xz/git/linux/tools/testing/selftests/kvm/libkvm.a(vmx.o):/home/xz/git/linux/tools/testing/selftests/kvm/include/evmcs.h:222: multiple definition of `current_evmcs'; /tmp/cco1G48P.o:/home/xz/git/linux/tools/testing/selftests/kvm/include/evmcs.h:222: first defined here
/usr/bin/ld: /home/xz/git/linux/tools/testing/selftests/kvm/libkvm.a(vmx.o):/home/xz/git/linux/tools/testing/selftests/kvm/include/evmcs.h:223: multiple definition of `current_vp_assist'; /tmp/cco1G48P.o:/home/xz/git/linux/tools/testing/selftests/kvm/include/evmcs.h:223: first defined here

I think it's because evmcs.h is included both in a test file and a lib file so
the structs have multiple declarations when linking.  After all it's not a good
habit to declare structs in the header files.

Cc: Vitaly Kuznetsov <vkuznets@redhat.com>
Signed-off-by: Peter Xu <peterx@redhat.com>
---

I initially thought it was something about my GCC 10 upgrade that I recently
did to my laptop - gcc10 even fails the build of the latest kernel after
all (though it turns out to be a kernel bug on build system rather than a gcc
bug). but I'm not sure about this one...
---
 tools/testing/selftests/kvm/include/evmcs.h  | 4 ++--
 tools/testing/selftests/kvm/lib/x86_64/vmx.c | 3 +++
 2 files changed, 5 insertions(+), 2 deletions(-)

```
#### [PATCH] KVM: VMX: Fix operand constraint of PUSH instructions
##### From: Uros Bizjak <ubizjak@gmail.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Uros Bizjak <ubizjak@gmail.com>
X-Patchwork-Id: 11527407
Return-Path: <SRS0=Q5Yu=6S=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 6CE5692A
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon,  4 May 2020 18:47:11 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 54A142073E
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon,  4 May 2020 18:47:11 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=gmail.com header.i=@gmail.com
 header.b="gsTMd9Li"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727860AbgEDSrK (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 4 May 2020 14:47:10 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:36130 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-FAIL-OK-FAIL)
        by vger.kernel.org with ESMTP id S1727799AbgEDSrJ (ORCPT
        <rfc822;kvm@vger.kernel.org>); Mon, 4 May 2020 14:47:09 -0400
Received: from mail-wm1-x343.google.com (mail-wm1-x343.google.com
 [IPv6:2a00:1450:4864:20::343])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 86EECC061A0E
        for <kvm@vger.kernel.org>; Mon,  4 May 2020 11:47:09 -0700 (PDT)
Received: by mail-wm1-x343.google.com with SMTP id x4so654515wmj.1
        for <kvm@vger.kernel.org>; Mon, 04 May 2020 11:47:09 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=from:to:cc:subject:date:message-id:mime-version
         :content-transfer-encoding;
        bh=MgCs0wkVJtVHte9mm7xQ9ul/9fE/hpJWdtuiVOjQk7o=;
        b=gsTMd9LifTAISFhc6cN82h70sRdFoOz/zSiSbTjT/DpfUMiMAb/oYemkZG+pA6Swy0
         qO9Hb+DTok5EYTsfmcNL/B4ZO2KiWr6Q2B9kscHkmP+OM4g7c5Xd/vV/8M5swSKV0clJ
         9Qsrn/ZoD1sv2lw0iISCqnFq5nqIQosaJPdiaByycbnVcXACO1PA5BSnFxg4vkfgFYcK
         LdYRCTq2wfXVeyAUgQ8f2o2kAIm9bFGGOc+qyfj6pXK94MwSpbHdSFAOlHuKQ5QVA4am
         H39L2E40UFeKvBmncGs0EPPq50hU+usoVxmlEnskw1UUkKsfBYytYjzmpbG8od55HfKx
         /y7w==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:mime-version
         :content-transfer-encoding;
        bh=MgCs0wkVJtVHte9mm7xQ9ul/9fE/hpJWdtuiVOjQk7o=;
        b=XonbQcEMT1KfC4SNzeFKWsu7NM+WLuQQSk1g1UsVvRUhnDi/a1azVknMqvIiya6MrL
         +ky3oF7X9VZeSyE6pmpg/wpgMd/R/Zi77+gnWICXKxWZYvtc6U+3ruWICLzGcXAf530R
         TYMsI/HlL0OlYCzXKZ0tDwE07ZJT/ke0/cnr/ehaDWLqeSf7XsXVZVzXCYCUZu74NSuC
         HD4yQ6M9+sGj+8IAQCip6UGwzmj8Sv9bwO/tQd57kal/XJAIBxOMx2DxqkYU678LVjAX
         928KGRWI7zNXSbQ6fbZdvxxzteDJlegjgo0wk4+QsMczRYWlh6cotR0IifxZYGz72hz0
         Y8Yg==
X-Gm-Message-State: AGi0PuZrB17tHgRBRmY5jt5h4x3ep/GJkMD44tjRlvFh4icK3T69FfwY
        EFO50zpdM29hm2HBOlkbaLXcS3c8G5Y=
X-Google-Smtp-Source: 
 APiQypL+ZUWqwyqa9k4GbCajREHbBcPh5EauxpvUjaZvLpKERGfUgLegtliUFDSPMUj65kur6eXbtg==
X-Received: by 2002:a1c:4d17:: with SMTP id o23mr15395855wmh.47.1588618027914;
        Mon, 04 May 2020 11:47:07 -0700 (PDT)
Received: from localhost.localdomain (93-103-18-160.static.t-2.net.
 [93.103.18.160])
        by smtp.gmail.com with ESMTPSA id
 y18sm470842wmc.45.2020.05.04.11.47.06
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Mon, 04 May 2020 11:47:07 -0700 (PDT)
From: Uros Bizjak <ubizjak@gmail.com>
To: kvm@vger.kernel.org
Cc: Uros Bizjak <ubizjak@gmail.com>,
        Paolo Bonzini <pbonzini@redhat.com>,
        Sean Christopherson <sean.j.christopherson@intel.com>
Subject: [PATCH] KVM: VMX: Fix operand constraint of PUSH instructions
Date: Mon,  4 May 2020 20:47:00 +0200
Message-Id: <20200504184700.3078839-1-ubizjak@gmail.com>
X-Mailer: git-send-email 2.25.4
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

PUSH instructions can't handle 64-bit immediate operands, so "i"
operand constraint is not correct. Use "re" operand constraint
to limit the range of the immediate operand to a signed 32-bit
value and also to leave the compiler the freedom to pass the value
via a register.

Please note that memory operands are not allowed here. These
operands include stack slots, and these are not valid in this
asm block due to the clobbered %rsp register.

Cc: Paolo Bonzini <pbonzini@redhat.com>
Cc: Sean Christopherson <sean.j.christopherson@intel.com>
Signed-off-by: Uros Bizjak <ubizjak@gmail.com>
---
 arch/x86/kvm/vmx/vmx.c | 4 ++--
 1 file changed, 2 insertions(+), 2 deletions(-)

```
#### [PATCH 1/3] KVM: SVM: fill in kvm_run->debug.arch.dr[67]
##### From: Paolo Bonzini <pbonzini@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Paolo Bonzini <pbonzini@redhat.com>
X-Patchwork-Id: 11526611
Return-Path: <SRS0=Q5Yu=6S=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 08AFA14C0
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon,  4 May 2020 15:56:18 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id E2D7020721
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon,  4 May 2020 15:56:17 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="a0iGO8PW"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728294AbgEDP4R (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 4 May 2020 11:56:17 -0400
Received: from us-smtp-delivery-1.mimecast.com ([207.211.31.120]:32749 "EHLO
        us-smtp-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org
        with ESMTP id S1726551AbgEDP4F (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 4 May 2020 11:56:05 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1588607764;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:in-reply-to:in-reply-to:references:references;
        bh=OYHq7rOire7Ktnkt0RBpmRo6SGj1PKuzNi8M05DTLkI=;
        b=a0iGO8PWquu5Xz9xjdy4uKd1JSP6AY/A93URKqUoxhfVyDG+QvNL1fhANN77AHo5rGP+Nk
        22gGgNErLDCMqE++2tcW4dS1vArYHWT2UxgqVxAL8bHsYXY2IJ9rX353ouVZgc0ifM+lOs
        tzGe8prs9+UKbtmLllol7Yukw824BZQ=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-175-FAE15sngPOCntJdqAkUTZg-1; Mon, 04 May 2020 11:56:00 -0400
X-MC-Unique: FAE15sngPOCntJdqAkUTZg-1
Received: from smtp.corp.redhat.com (int-mx03.intmail.prod.int.phx2.redhat.com
 [10.5.11.13])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id B279D800687;
        Mon,  4 May 2020 15:55:59 +0000 (UTC)
Received: from virtlab511.virt.lab.eng.bos.redhat.com
 (virtlab511.virt.lab.eng.bos.redhat.com [10.19.152.198])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 2D75F57990;
        Mon,  4 May 2020 15:55:59 +0000 (UTC)
From: Paolo Bonzini <pbonzini@redhat.com>
To: linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Cc: Sean Christopherson <sean.j.christopherson@intel.com>,
        stable@vger.kernel.org
Subject: [PATCH 1/3] KVM: SVM: fill in kvm_run->debug.arch.dr[67]
Date: Mon,  4 May 2020 11:55:56 -0400
Message-Id: <20200504155558.401468-2-pbonzini@redhat.com>
In-Reply-To: <20200504155558.401468-1-pbonzini@redhat.com>
References: <20200504155558.401468-1-pbonzini@redhat.com>
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.13
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The corresponding code was added for VMX in commit 42dbaa5a057
("KVM: x86: Virtualize debug registers, 2008-12-15) but never for AMD.
Fix this.

Cc: stable@vger.kernel.org
Fixes: 42dbaa5a057 ("KVM: x86: Virtualize debug registers")
Signed-off-by: Paolo Bonzini <pbonzini@redhat.com>
---
 arch/x86/kvm/svm/svm.c | 2 ++
 1 file changed, 2 insertions(+)

```
#### [PATCH v1 1/2] Sample mtty: Add sysfs interface to pin pages
##### From: Kirti Wankhede <kwankhede@nvidia.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Kirti Wankhede <kwankhede@nvidia.com>
X-Patchwork-Id: 11527395
Return-Path: <SRS0=Q5Yu=6S=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id D63731668
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon,  4 May 2020 18:27:45 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id BA2AB24963
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon,  4 May 2020 18:27:45 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=nvidia.com header.i=@nvidia.com
 header.b="hpPDYMTI"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1730821AbgEDS1o (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 4 May 2020 14:27:44 -0400
Received: from hqnvemgate24.nvidia.com ([216.228.121.143]:6452 "EHLO
        hqnvemgate24.nvidia.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1730700AbgEDS1o (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 4 May 2020 14:27:44 -0400
Received: from hqpgpgate101.nvidia.com (Not Verified[216.228.121.13]) by
 hqnvemgate24.nvidia.com (using TLS: TLSv1.2, DES-CBC3-SHA)
        id <B5eb05e200000>; Mon, 04 May 2020 11:25:36 -0700
Received: from hqmail.nvidia.com ([172.20.161.6])
  by hqpgpgate101.nvidia.com (PGP Universal service);
  Mon, 04 May 2020 11:27:43 -0700
X-PGP-Universal: processed;
        by hqpgpgate101.nvidia.com on Mon, 04 May 2020 11:27:43 -0700
Received: from HQMAIL105.nvidia.com (172.20.187.12) by HQMAIL101.nvidia.com
 (172.20.187.10) with Microsoft SMTP Server (TLS) id 15.0.1473.3; Mon, 4 May
 2020 18:27:43 +0000
Received: from kwankhede-dev.nvidia.com (10.124.1.5) by HQMAIL105.nvidia.com
 (172.20.187.12) with Microsoft SMTP Server (TLS) id 15.0.1473.3 via Frontend
 Transport; Mon, 4 May 2020 18:27:36 +0000
From: Kirti Wankhede <kwankhede@nvidia.com>
To: <alex.williamson@redhat.com>, <cjia@nvidia.com>
CC: <kevin.tian@intel.com>, <ziye.yang@intel.com>,
        <changpeng.liu@intel.com>, <yi.l.liu@intel.com>,
        <mlevitsk@redhat.com>, <eskultet@redhat.com>, <cohuck@redhat.com>,
        <dgilbert@redhat.com>, <jonathan.davies@nutanix.com>,
        <eauger@redhat.com>, <aik@ozlabs.ru>, <pasic@linux.ibm.com>,
        <felipe@nutanix.com>, <Zhengxiao.zx@Alibaba-inc.com>,
        <shuangtai.tst@alibaba-inc.com>, <Ken.Xue@amd.com>,
        <zhi.a.wang@intel.com>, <yan.y.zhao@intel.com>,
        <qemu-devel@nongnu.org>, <kvm@vger.kernel.org>,
        "Kirti Wankhede" <kwankhede@nvidia.com>
Subject: [PATCH v1 1/2] Sample mtty: Add sysfs interface to pin pages
Date: Mon, 4 May 2020 23:24:19 +0530
Message-ID: <1588614860-16330-2-git-send-email-kwankhede@nvidia.com>
X-Mailer: git-send-email 2.7.0
In-Reply-To: <1588614860-16330-1-git-send-email-kwankhede@nvidia.com>
References: <1588614860-16330-1-git-send-email-kwankhede@nvidia.com>
X-NVConfidentiality: public
MIME-Version: 1.0
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=nvidia.com; s=n1;
        t=1588616736; bh=LM7O/QtPrNroYPHMAw1tDGhJJm1iWHCvYUgOsUsGJ7U=;
        h=X-PGP-Universal:From:To:CC:Subject:Date:Message-ID:X-Mailer:
         In-Reply-To:References:X-NVConfidentiality:MIME-Version:
         Content-Type;
        b=hpPDYMTIWyA3RSFu+DgJWyk3YbCP/vjKSL74Gb5ZdospGbspIf2/V1Feypa9UgNrU
         aePDwyyivOy/Ul61M29DEr6mv+M0TWUs7YlRQKLdAZVcQ1ROs5FV/ciu60/Ht/P1a9
         a9+p2Z6J2cG6zY0CSzOiqV73QCUFztxnN5KFzO2ymaDrnfIGGE7T4lzRcUcrH9dM7H
         yRAHOBcevjE9pUCPVU7GBlH87wfVnKxpP7+27dRC1J/xOrPVlkKA/IjIsS4ZzUap6y
         xreQplhyETU3I/mkFFnVKzWVkOkZ9M/cSc0NXReD93bmy8LkO9HDoi5V6mtoDp6QMi
         d9m1JVpb8j5QA==
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Added sysfs interface to pin pages which will be used to test migration
when vendor driver pins pages.

Read on pin_pages shows number of pages pinned:
 $ cat /sys/bus/mdev/devices/<mdev UUID>/vendor/pin_pages
Pinned 0x0 pages

Write gpfn to pin_pages to pin that page. One page pinned on write
 $ echo 0x20 > /sys/bus/mdev/devices/<mdev UUID>/vendor/pin_pages

Limitation: Buffer for 2GB system memory is created to track pinned
pages.

This is for testing purpose only.

Signed-off-by: Kirti Wankhede <kwankhede@nvidia.com>
---
 samples/vfio-mdev/mtty.c | 176 ++++++++++++++++++++++++++++++++++++++++++++++-
 1 file changed, 175 insertions(+), 1 deletion(-)

```
#### [PATCH v2 1/5] refcount, kref: add dec-and-test wrappers for rw_semaphores
##### From: Emanuele Giuseppe Esposito <eesposit@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Emanuele Giuseppe Esposito <eesposit@redhat.com>
X-Patchwork-Id: 11525499
Return-Path: <SRS0=Q5Yu=6S=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 7E03D92A
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon,  4 May 2020 11:04:51 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 65D142073E
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon,  4 May 2020 11:04:51 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="Px3HqRrx"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728437AbgEDLD6 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 4 May 2020 07:03:58 -0400
Received: from us-smtp-delivery-1.mimecast.com ([207.211.31.120]:51545 "EHLO
        us-smtp-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org
        with ESMTP id S1728296AbgEDLD5 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 4 May 2020 07:03:57 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1588590235;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding:
         in-reply-to:in-reply-to:references:references;
        bh=09losalqRUJ7midVbFAi44IAzVHZ/Wi/7WIU6kwrX9U=;
        b=Px3HqRrxhIQEBqoJODUfdvZOKYEbaPkqTxR1AB8J6KU/wKd/KwHuXZu3S6hj6wPPfR+mgk
        Mzi1HnCUJFKYTI+Xlk0GVmxv1HZ1Pb1ItyZXhjdtHcqtAQLxRj4YVXasAXCX9K2C9Hbvx2
        1XO0wADAYa0t0upc2vA9t7I9Sb7D4h8=
Received: from mail-wr1-f71.google.com (mail-wr1-f71.google.com
 [209.85.221.71]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-349-JFnBHC4vNECDk89lch5ZbA-1; Mon, 04 May 2020 07:03:54 -0400
X-MC-Unique: JFnBHC4vNECDk89lch5ZbA-1
Received: by mail-wr1-f71.google.com with SMTP id q13so1692836wrn.14
        for <kvm@vger.kernel.org>; Mon, 04 May 2020 04:03:54 -0700 (PDT)
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:in-reply-to
         :references:mime-version:content-transfer-encoding;
        bh=09losalqRUJ7midVbFAi44IAzVHZ/Wi/7WIU6kwrX9U=;
        b=FE5XqrDn8CSiXa+/jvIxezESPzgeUQk8tZwCcqjbayJN9wZ+L07SJKos2SeeI/gmVD
         5dE0+NUmIpvsyT3clKofZ8Gf6DKjgpZX64NnEmOZQ7cOrlVN0KDq3KWFDRNStQM0vlT4
         eF76PNJp8OhOBbgi5w1lkWSiNrg3ZFmXOBsR95AyK0MvvOqI6SvFVN2sJ1Nhmust3ATL
         em5fgFBidik7ga7U5bNprSwxX4ZX2TOheG4IwVjEOu49LPbhgrM90UO15mLhTDfjfDF3
         tsGAtxuKewIQh8kr53UEuKDxxZs59Y78k1WmglNxO+nOJ3yAArATGvpGmPMsrEBACZHd
         rrsw==
X-Gm-Message-State: AGi0PuaRkxJZIZiAwmp19r6dmpx8hlOQEqd2keAo0YbDbs1gh1Dn8EbY
        q40DFiCv+Xg56M3MUkywjlidEcYQTCHcfL31Dw09UKkMPNB21xqVLPGHcdgYNvdvNWCvSBzs/k2
        l6fLAdZSREa9h
X-Received: by 2002:a5d:5261:: with SMTP id l1mr6739125wrc.24.1588590232890;
        Mon, 04 May 2020 04:03:52 -0700 (PDT)
X-Google-Smtp-Source: 
 APiQypJvuRFnJ0VBK5Hu4muwInjRtI3dy4S4pn3siD3o26S579ZPY0C/y2BIROU3uJD8eKGxaBWo7w==
X-Received: by 2002:a5d:5261:: with SMTP id l1mr6739098wrc.24.1588590232648;
        Mon, 04 May 2020 04:03:52 -0700 (PDT)
Received: from localhost.localdomain.com ([194.230.155.213])
        by smtp.gmail.com with ESMTPSA id
 a13sm10885750wrv.67.2020.05.04.04.03.50
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Mon, 04 May 2020 04:03:52 -0700 (PDT)
From: Emanuele Giuseppe Esposito <eesposit@redhat.com>
To: kvm@vger.kernel.org
Cc: Christian Borntraeger <borntraeger@de.ibm.com>,
        David Hildenbrand <david@redhat.com>,
        Cornelia Huck <cohuck@redhat.com>,
        Paolo Bonzini <pbonzini@redhat.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Jim Mattson <jmattson@google.com>,
        Alexander Viro <viro@zeniv.linux.org.uk>,
        Emanuele Giuseppe Esposito <e.emanuelegiuseppe@gmail.com>,
        linux-kernel@vger.kernel.org, linux-mips@vger.kernel.org,
        kvm-ppc@vger.kernel.org, linuxppc-dev@lists.ozlabs.org,
        linux-s390@vger.kernel.org, linux-fsdevel@vger.kernel.org,
        Emanuele Giuseppe Esposito <eesposit@redhat.com>
Subject: [PATCH v2 1/5] refcount,
 kref: add dec-and-test wrappers for rw_semaphores
Date: Mon,  4 May 2020 13:03:40 +0200
Message-Id: <20200504110344.17560-2-eesposit@redhat.com>
X-Mailer: git-send-email 2.25.2
In-Reply-To: <20200504110344.17560-1-eesposit@redhat.com>
References: <20200504110344.17560-1-eesposit@redhat.com>
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Similar to the existing functions that take a mutex or spinlock if and
only if a reference count is decremented to zero, these new function
take an rwsem for writing just before the refcount reaches 0 (and
call a user-provided function in the case of kref_put_rwsem).

These will be used for stats_fs_source data structures, which are
protected by an rw_semaphore to allow concurrent sysfs reads.

Signed-off-by: Emanuele Giuseppe Esposito <eesposit@redhat.com>
---
 include/linux/kref.h     | 11 +++++++++++
 include/linux/refcount.h |  2 ++
 lib/refcount.c           | 32 ++++++++++++++++++++++++++++++++
 3 files changed, 45 insertions(+)

```
#### [PATCH v5] KVM: VMX: Improve handle_external_interrupt_irqoff inline assembly
##### From: Uros Bizjak <ubizjak@gmail.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Uros Bizjak <ubizjak@gmail.com>
X-Patchwork-Id: 11526615
Return-Path: <SRS0=Q5Yu=6S=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 745C814C0
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon,  4 May 2020 15:57:24 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 5C4A42073E
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon,  4 May 2020 15:57:24 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=gmail.com header.i=@gmail.com
 header.b="r6p8lve4"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729507AbgEDP5X (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 4 May 2020 11:57:23 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:37540 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-FAIL-OK-FAIL)
        by vger.kernel.org with ESMTP id S1726551AbgEDP5P (ORCPT
        <rfc822;kvm@vger.kernel.org>); Mon, 4 May 2020 11:57:15 -0400
Received: from mail-wm1-x343.google.com (mail-wm1-x343.google.com
 [IPv6:2a00:1450:4864:20::343])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 8275BC061A0E
        for <kvm@vger.kernel.org>; Mon,  4 May 2020 08:57:15 -0700 (PDT)
Received: by mail-wm1-x343.google.com with SMTP id x4so55969wmj.1
        for <kvm@vger.kernel.org>; Mon, 04 May 2020 08:57:15 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=from:to:cc:subject:date:message-id:mime-version
         :content-transfer-encoding;
        bh=X1WqU9HNBXbnLtwhNjQWNZBJ+A0XFPN2T0T20+XM+FU=;
        b=r6p8lve4t2fTdGX29pInoSZbKrDADNQLJHVOm5YwQAq13OxxihnpYfNa26bdga78Fu
         ig2KRr7cXrtrbbN6EHmOHn5k/yiU/5pkXmj8Au9iT0k0lmTQVLYxOGumAE/qaTxX1WD/
         04grJ2RIN6sPqnYqSFmY+TKbTThrCVzWUr5jiygcW2WRzdt3CpCkR3OD2qELX6NSGnnB
         QBmF1V7qT5DkGZ4TBwSLBqm7+RzRQzgfugo4YENi0gIHRRiBkb9jpQzGrvOHZOlN0OrW
         UtYr6Mc/g7hoD5WxiXLkzwdVEgk2AjZc4Y+FgOyv7VeHNv4w8wpxJw3H6YATh+P16J16
         BmjA==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:mime-version
         :content-transfer-encoding;
        bh=X1WqU9HNBXbnLtwhNjQWNZBJ+A0XFPN2T0T20+XM+FU=;
        b=OpV7zo7EJtVc6xhEncC/lqzt0/JhH9XVK0uljIMkE+h0uHC3HzAoExRiz7BrB8jxEk
         MV5uTnygqh+KsvPK9xzUmcHoOwGwVmJ+A6y8xhJTYzmPrdNiMwdsVrHsost8q1HZ55D9
         t+HfrclIdgR1armsxMspXQooMX/xzcGKCalvtWYJ7PKBFPoXxHUepc3Nn3UKQ8Sg1Wqb
         wvgjrRLk+oefKKaEtBq1Si6iWV8zLsGIixwmGJFdK/qegcajUWUrHksEeMzkyupIkWUN
         Lk8q423OGbQAeuAq0hV6xqBF7nBYBY5V4G4crPosE0jPrUXLLxd/KEyg3oKw1D5cf22W
         zRhw==
X-Gm-Message-State: AGi0PuZKnT/l7EoJ6a7MbTP+c5d0RAgfkDOi0hPX20yQDjo5RVAcKRav
        vuJY945T7HDVB+2x8sCGEOsrr/t1Q88=
X-Google-Smtp-Source: 
 APiQypKGX0gm27mN8Mfsm008qocKLMe8Tj3esRGrj9PoTav/ZRjxJ2U+Z+V2Z5ZI20gabDwH65ao0g==
X-Received: by 2002:a05:600c:218e:: with SMTP id
 e14mr16453544wme.140.1588607833947;
        Mon, 04 May 2020 08:57:13 -0700 (PDT)
Received: from localhost.localdomain (93-103-18-160.static.t-2.net.
 [93.103.18.160])
        by smtp.gmail.com with ESMTPSA id
 n6sm13827545wmc.28.2020.05.04.08.57.12
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Mon, 04 May 2020 08:57:13 -0700 (PDT)
From: Uros Bizjak <ubizjak@gmail.com>
To: kvm@vger.kernel.org
Cc: Uros Bizjak <ubizjak@gmail.com>,
        Paolo Bonzini <pbonzini@redhat.com>,
        Sean Christopherson <sean.j.christopherson@intel.com>
Subject: [PATCH v5] KVM: VMX: Improve handle_external_interrupt_irqoff inline
 assembly
Date: Mon,  4 May 2020 17:57:06 +0200
Message-Id: <20200504155706.2516956-1-ubizjak@gmail.com>
X-Mailer: git-send-email 2.25.4
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Improve handle_external_interrupt_irqoff inline assembly in several ways:
- remove unneeded %c operand modifiers and "$" prefixes
- use %rsp instead of _ASM_SP, since we are in CONFIG_X86_64 part
- use $-16 immediate to align %rsp
- remove unneeded use of __ASM_SIZE macro
- define "ss" named operand only for X86_64

The patch introduces no functional changes.

Cc: Paolo Bonzini <pbonzini@redhat.com>
Cc: Sean Christopherson <sean.j.christopherson@intel.com>
Signed-off-by: Uros Bizjak <ubizjak@gmail.com>
---
 arch/x86/kvm/vmx/vmx.c | 10 ++++++----
 1 file changed, 6 insertions(+), 4 deletions(-)

```
