#### [RFC PATCH 1/4] arm64: cpufeature: TWED support detection
##### From: Jingyi Wang <wangjingyi11@huawei.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Jingyi Wang <wangjingyi11@huawei.com>
X-Patchwork-Id: 11805419
Return-Path: <SRS0=xlFf=DG=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id A79D4139A
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 29 Sep 2020 09:18:05 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 8635020C09
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 29 Sep 2020 09:18:05 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727691AbgI2JSE (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 29 Sep 2020 05:18:04 -0400
Received: from szxga05-in.huawei.com ([45.249.212.191]:14708 "EHLO huawei.com"
        rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org with ESMTP
        id S1728006AbgI2JSE (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 29 Sep 2020 05:18:04 -0400
Received: from DGGEMS404-HUB.china.huawei.com (unknown [172.30.72.58])
        by Forcepoint Email with ESMTP id 7CC37386EB632C20326B;
        Tue, 29 Sep 2020 17:18:02 +0800 (CST)
Received: from DESKTOP-FPN2511.china.huawei.com (10.174.187.69) by
 DGGEMS404-HUB.china.huawei.com (10.3.19.204) with Microsoft SMTP Server id
 14.3.487.0; Tue, 29 Sep 2020 17:17:56 +0800
From: Jingyi Wang <wangjingyi11@huawei.com>
To: <kvm@vger.kernel.org>, <kvmarm@lists.cs.columbia.edu>,
        <linux-arm-kernel@lists.infradead.org>
CC: <will@kernel.org>, <catalin.marinas@arm.com>, <maz@kernel.org>,
        <james.morse@arm.com>, <julien.thierry.kdev@gmail.com>,
        <suzuki.poulose@arm.com>, <wanghaibin.wang@huawei.com>,
        <yezengruan@huawei.com>, <shameerali.kolothum.thodi@huawei.com>,
        <fanhenglong@huawei.com>, <wangjingyi11@huawei.com>,
        <prime.zeng@hisilicon.com>
Subject: [RFC PATCH 1/4] arm64: cpufeature: TWED support detection
Date: Tue, 29 Sep 2020 17:17:24 +0800
Message-ID: <20200929091727.8692-2-wangjingyi11@huawei.com>
X-Mailer: git-send-email 2.14.1.windows.1
In-Reply-To: <20200929091727.8692-1-wangjingyi11@huawei.com>
References: <20200929091727.8692-1-wangjingyi11@huawei.com>
MIME-Version: 1.0
X-Originating-IP: [10.174.187.69]
X-CFilter-Loop: Reflected
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Zengruan Ye <yezengruan@huawei.com>

TWE Delay is an optional feature in ARMv8.6 Extentions. This patch
detect this feature.

Signed-off-by: Zengruan Ye <yezengruan@huawei.com>
Signed-off-by: Jingyi Wang <wangjingyi11@huawei.com>
---
 arch/arm64/Kconfig               | 10 ++++++++++
 arch/arm64/include/asm/cpucaps.h |  3 ++-
 arch/arm64/kernel/cpufeature.c   | 12 ++++++++++++
 3 files changed, 24 insertions(+), 1 deletion(-)

```
#### [GIT PULL] virtio: last minute fixes
##### From: "Michael S. Tsirkin" <mst@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: "Michael S. Tsirkin" <mst@redhat.com>
X-Patchwork-Id: 11805149
Return-Path: <SRS0=xlFf=DG=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id B7AF36CB
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 29 Sep 2020 07:50:48 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 92D712076A
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 29 Sep 2020 07:50:48 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="KgvHl16W"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727650AbgI2Hur (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 29 Sep 2020 03:50:47 -0400
Received: from us-smtp-delivery-124.mimecast.com ([216.205.24.124]:45711 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1725554AbgI2Hun (ORCPT
        <rfc822;kvm@vger.kernel.org>); Tue, 29 Sep 2020 03:50:43 -0400
Dkim-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1601365842;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:content-type:content-type;
        bh=ZH5RUsiNCBnwQO3HdBH/S2GadrEkNWR9w8D2mfkC+xk=;
        b=KgvHl16Wswmk2dGHcQwcqzyP+ljW5etLxraLl4KE+1U8YzByMKm7xRm8UdCTsl2IwtN/bc
        7iAjJ1jMT4Ljyq9IZio1yl3raXunBvmkWx/8b5L7k8pJLdAihXJhGa90ozQFE0Bp9L0K91
        vGTtFFRUcBGZoSQchuIWT2yJ8p5g1cY=
Received: from mail-wr1-f71.google.com (mail-wr1-f71.google.com
 [209.85.221.71]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-45-mVX7Rs0-Pj-DQ9qrv6_EdQ-1; Tue, 29 Sep 2020 03:50:38 -0400
X-MC-Unique: mVX7Rs0-Pj-DQ9qrv6_EdQ-1
Received: by mail-wr1-f71.google.com with SMTP id v12so1399755wrm.9
        for <kvm@vger.kernel.org>; Tue, 29 Sep 2020 00:50:38 -0700 (PDT)
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:date:from:to:cc:subject:message-id:mime-version
         :content-disposition;
        bh=ZH5RUsiNCBnwQO3HdBH/S2GadrEkNWR9w8D2mfkC+xk=;
        b=Q4jeJA+bnOGlxlRRnhLgxMm/gw3+uaSf8//4hAfn+7/aI/q61LqoR4iaBhqi8O3R9V
         PLFSqyS4Upf5aJyX2y7a7hQRjo+JQHwj37kzbBMfsPK8yeeLjHkOpLwncxjHJ+ppK9CS
         VVzjs1EZ9GZJwym20bfHzDDVwJjaUr1VjQ23K+mSHyFlaf5+h/z/hmdoWL4cuxGMITuX
         IdKhiBCB9gDo8YBGd1J755JyCRdo9nf9wWBw+Gqak5eHdDOfDoS/1yylcsXOswDMtKhd
         LYmNCXwGng+5AG0f+RzJ3jOkQDAlPRSoFbd5bi10wiWuVf9uUQ2dkIq+taNM2sze6IFv
         qz2A==
X-Gm-Message-State: AOAM531xDCnSgG2kHw5rVEAkRAyHTTT7ARagvhX/c/9ytOqVkZp4Mx/q
        8Gd2gjHUjVTZQz3XqIpb75c5OnGCDTsEAG8+8ZawSMsunosukh1SjFk7XaueMVV/qzPVBCmqbDr
        2vJ/GExKNYhQ4
X-Received: by 2002:a5d:660f:: with SMTP id n15mr2849636wru.103.1601365837345;
        Tue, 29 Sep 2020 00:50:37 -0700 (PDT)
X-Google-Smtp-Source: 
 ABdhPJw9yDNuK/HRBfrUSRppU/hB6f1n2dAKzHM+mssOZcfIMLGHfW5jc72hMkHH51Lh+uUsHHthwg==
X-Received: by 2002:a5d:660f:: with SMTP id n15mr2849612wru.103.1601365837164;
        Tue, 29 Sep 2020 00:50:37 -0700 (PDT)
Received: from redhat.com (bzq-79-179-71-128.red.bezeqint.net.
 [79.179.71.128])
        by smtp.gmail.com with ESMTPSA id
 o15sm4204743wmh.29.2020.09.29.00.50.35
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Tue, 29 Sep 2020 00:50:36 -0700 (PDT)
Date: Tue, 29 Sep 2020 03:50:34 -0400
From: "Michael S. Tsirkin" <mst@redhat.com>
To: Linus Torvalds <torvalds@linux-foundation.org>
Cc: kvm@vger.kernel.org, virtualization@lists.linux-foundation.org,
        netdev@vger.kernel.org, linux-kernel@vger.kernel.org,
        elic@nvidia.com, eli@mellanox.com, jasowang@redhat.com,
        lingshan.zhu@intel.com, mst@redhat.com
Subject: [GIT PULL] virtio: last minute fixes
Message-ID: <20200929035034-mutt-send-email-mst@kernel.org>
MIME-Version: 1.0
Content-Disposition: inline
X-Mutt-Fcc: =sent
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Unfortunately there are a couple more reported issues in vhost and vdpa,
but those fixes are still being worked upon, no reason to
delay those that are ready.

The following changes since commit ba4f184e126b751d1bffad5897f263108befc780:

  Linux 5.9-rc6 (2020-09-20 16:33:55 -0700)

are available in the Git repository at:

  https://git.kernel.org/pub/scm/linux/kernel/git/mst/vhost.git tags/for_linus

for you to fetch changes up to a127c5bbb6a8eee851cbdec254424c480b8edd75:

  vhost-vdpa: fix backend feature ioctls (2020-09-24 05:54:36 -0400)

----------------------------------------------------------------
virtio: last minute fixes

A couple of last minute fixes

Signed-off-by: Michael S. Tsirkin <mst@redhat.com>

----------------------------------------------------------------
Eli Cohen (1):
      vhost: Fix documentation

Jason Wang (1):
      vhost-vdpa: fix backend feature ioctls

 drivers/vhost/iotlb.c |  4 ++--
 drivers/vhost/vdpa.c  | 30 ++++++++++++++++--------------
 2 files changed, 18 insertions(+), 16 deletions(-)
```
#### [PATCH] KVM: x86: Add tracepoint for dr_write/dr_read
##### From: lihaiwei.kernel@gmail.com

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Haiwei Li <lihaiwei.kernel@gmail.com>
X-Patchwork-Id: 11805297
Return-Path: <SRS0=xlFf=DG=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id F394C6CB
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 29 Sep 2020 08:55:34 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id CBBCD206DC
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 29 Sep 2020 08:55:34 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=gmail.com header.i=@gmail.com
 header.b="P1SOZ08o"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727931AbgI2Ize (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 29 Sep 2020 04:55:34 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:41048 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1727826AbgI2Izb (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 29 Sep 2020 04:55:31 -0400
Received: from mail-pf1-x444.google.com (mail-pf1-x444.google.com
 [IPv6:2607:f8b0:4864:20::444])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id D6B24C061755;
        Tue, 29 Sep 2020 01:55:29 -0700 (PDT)
Received: by mail-pf1-x444.google.com with SMTP id z19so3845092pfn.8;
        Tue, 29 Sep 2020 01:55:29 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=from:to:cc:subject:date:message-id:mime-version
         :content-transfer-encoding;
        bh=yLZJxx2l7hUl8Pgn3o5psWobrD3TjYQxwKuaDcKpaAs=;
        b=P1SOZ08oNzcpvT4+1QdPJIKbuRcOJfMQYnh/POijnSls+YiMR3I01WSLLQF026Ji+X
         sFBFvMWHQy+8WmXb6uZE4C2CbkWqcJPyLYNTydGkMRnQtnAwU/GUhQhCPptmv+1+9o5m
         x+E8wV87cHvjSDpzqY7+yQchBCePaRo8WyWvXXzySB3dkUhQouA/8T0Qscq4EwhqYyV3
         sSE9LR0vxv3Du/u7SqZj35C3wzKvOJlS1xT0KH+2HXiDPUxmMi+2DUVQFsucygQNj0KR
         1BPzUvV5xbBNyLK/gIgPbQU6XKjaOzNNqRxcQkHb3LygnjzPbQ48YaxitC433eIgUAPv
         wU7g==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:mime-version
         :content-transfer-encoding;
        bh=yLZJxx2l7hUl8Pgn3o5psWobrD3TjYQxwKuaDcKpaAs=;
        b=ZykxsLdlMfhPCpFcfWvFO/SsMlTQ5jIMGKyliPnIh33dLstQNGHFU3iwrEPIV6QNUw
         Z8+hkKj0Fl58iVIi4xfXXup2n9N/eZ3N7+Lt7znnUDPtfPBSVRQ3sWV9rOZiZwlUv39n
         TuiRRLN+Ho+MgbzNODC30xA97FoSzigxBeSSldW1ZNd1JYttdg2JoSV6+AoyX3NeOk7m
         QyJBBfJc+0Xyd2OKZCAVXG7gFYUpR2KN6T0Vj8XumUoIZI0+ukGI0xN6Nd6RkUOhI8T/
         dVv7fO9FMK8PWDUUU02fpIzatKS8m6shX8J10ZtdZmOcGZE7zFTUQ8fkDFNGCFUOewwW
         pMfw==
X-Gm-Message-State: AOAM533cyBxGEu5TUsTgxG74uum6VVZIFrjQXdrzQ5hJ1dvTlAm7hOFL
        ADQI606Gcerc74wEf2QHmG9sbKe02BjH
X-Google-Smtp-Source: 
 ABdhPJzFiU1OJyLuqrPQYy4g/DXmxjdQ1IuHdxUHeRilWdjdpUgleXtTv+wvD1zReMnlywsDc95k7w==
X-Received: by 2002:a63:1925:: with SMTP id z37mr2502003pgl.23.1601369729029;
        Tue, 29 Sep 2020 01:55:29 -0700 (PDT)
Received: from localhost.localdomain ([203.205.141.39])
        by smtp.gmail.com with ESMTPSA id
 x185sm4616952pfc.188.2020.09.29.01.55.25
        (version=TLS1_2 cipher=ECDHE-ECDSA-AES128-GCM-SHA256 bits=128/128);
        Tue, 29 Sep 2020 01:55:28 -0700 (PDT)
From: lihaiwei.kernel@gmail.com
To: linux-kernel@vger.kernel.org, kvm@vger.kernel.org, x86@kernel.org
Cc: pbonzini@redhat.com, sean.j.christopherson@intel.com,
        vkuznets@redhat.com, wanpengli@tencent.com, jmattson@google.com,
        joro@8bytes.org, tglx@linutronix.de, mingo@redhat.com,
        bp@alien8.de, hpa@zytor.com, Haiwei Li <lihaiwei@tencent.com>
Subject: [PATCH] KVM: x86: Add tracepoint for dr_write/dr_read
Date: Tue, 29 Sep 2020 16:55:15 +0800
Message-Id: <20200929085515.24059-1-lihaiwei.kernel@gmail.com>
X-Mailer: git-send-email 2.28.0
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Haiwei Li <lihaiwei@tencent.com>

Add tracepoint trace_kvm_dr_write/trace_kvm_dr_read for x86 kvm.

Signed-off-by: Haiwei Li <lihaiwei@tencent.com>
---
 arch/x86/kvm/svm/svm.c |  2 ++
 arch/x86/kvm/trace.h   | 27 +++++++++++++++++++++++++++
 arch/x86/kvm/vmx/vmx.c | 10 ++++++++--
 arch/x86/kvm/x86.c     |  1 +
 4 files changed, 38 insertions(+), 2 deletions(-)

```
#### [PULL v4 01/48] linux headers: sync to 5.9-rc4
##### From: "Michael S. Tsirkin" <mst@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: "Michael S. Tsirkin" <mst@redhat.com>
X-Patchwork-Id: 11805039
Return-Path: <SRS0=xlFf=DG=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id F0892618
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 29 Sep 2020 07:23:11 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id C0B7920848
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 29 Sep 2020 07:23:11 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="MKtR6KU8"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1725776AbgI2HXK (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 29 Sep 2020 03:23:10 -0400
Received: from us-smtp-delivery-124.mimecast.com ([63.128.21.124]:21959 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1725320AbgI2HXK (ORCPT
        <rfc822;kvm@vger.kernel.org>); Tue, 29 Sep 2020 03:23:10 -0400
Dkim-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1601364186;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:content-type:content-type:
         in-reply-to:in-reply-to:references:references;
        bh=xf2I6AVSrGRq/duV5gv6UTIln0Sg/9kyZt7swxOVAAg=;
        b=MKtR6KU8MOJYZrweibrJ9cXeAt1sPY90V7DW8c4NvdQ/96b1R6qFHrbo97bqA+eZP8LvJn
        WJAvWX1UFVD1koUaTnT8BRaHtRADJTuDHu76j3Dy7S/SBBKY3FUVupdMdachVsR1cMbFn0
        wn/TTYfvI1ApmTUuk6R8vLit849ETEQ=
Received: from mail-wm1-f70.google.com (mail-wm1-f70.google.com
 [209.85.128.70]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-579-VfYAXCLmPPiBL5brNnhgAw-1; Tue, 29 Sep 2020 03:20:58 -0400
X-MC-Unique: VfYAXCLmPPiBL5brNnhgAw-1
Received: by mail-wm1-f70.google.com with SMTP id t10so1343332wmi.9
        for <kvm@vger.kernel.org>; Tue, 29 Sep 2020 00:20:58 -0700 (PDT)
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:date:from:to:cc:subject:message-id:references
         :mime-version:content-disposition:in-reply-to;
        bh=xf2I6AVSrGRq/duV5gv6UTIln0Sg/9kyZt7swxOVAAg=;
        b=M9SDJs8ALqwlfQ5Q4FqcP2yKUUzNxhdSlztONUSFwKMKce4AXyOvNfEtOd81TmS6bW
         aoc/cc8jb6bgWi6wVY9mZvrNnNuCH4npxpN93gElATHh/uNr9fXF9RAVIuU8XoeTQW4N
         e13Cmy3NV/gk25ACdAnVyo2XJ3gXjdk7Vuia9A7qWapUU7H2W/dcX3YRPlWJlfD8C+zx
         EcQdPuWfr3hmGTwtz859zZ9k0HKx3SE/5Aiy1kopEz4RPes7j00JVrRDbIhlWBWgz4uj
         ETfSunGl7zKX1m2szMNaKlWnprfmVzE9NASDHC1rrJKppy6bqnwyXxW99aRctrT9Evt0
         IeCA==
X-Gm-Message-State: AOAM530KqG8xXNY2vFPErRoLpDBXC27penJcA/6FZJoZuRICLzrJYtdb
        Q8GBznqLoJ62N0KqGJuxdcGSLzPP2074lwTlcOCBIYwNa4lt4IKTnBZ4j+dsyemh28NZBQ2IDiB
        a97SQtQQsK1VZ
X-Received: by 2002:adf:828f:: with SMTP id 15mr2483889wrc.49.1601364056070;
        Tue, 29 Sep 2020 00:20:56 -0700 (PDT)
X-Google-Smtp-Source: 
 ABdhPJyfz/pwBn/n5cuZ8m7r2+3BAsg2eNNKKtS1x0nRJrhMo1sB+MI2N7tXszKtLIhrL9l5ZjI0bQ==
X-Received: by 2002:adf:828f:: with SMTP id 15mr2483834wrc.49.1601364055518;
        Tue, 29 Sep 2020 00:20:55 -0700 (PDT)
Received: from redhat.com (bzq-79-179-71-128.red.bezeqint.net.
 [79.179.71.128])
        by smtp.gmail.com with ESMTPSA id
 h17sm4964520wro.27.2020.09.29.00.20.53
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Tue, 29 Sep 2020 00:20:54 -0700 (PDT)
Date: Tue, 29 Sep 2020 03:20:53 -0400
From: "Michael S. Tsirkin" <mst@redhat.com>
To: qemu-devel@nongnu.org
Cc: Peter Maydell <peter.maydell@linaro.org>,
        Jason Wang <jasowang@redhat.com>,
        Cornelia Huck <cohuck@redhat.com>,
        Paolo Bonzini <pbonzini@redhat.com>, kvm@vger.kernel.org
Subject: [PULL v4 01/48] linux headers: sync to 5.9-rc4
Message-ID: <20200929071948.281157-2-mst@redhat.com>
References: <20200929071948.281157-1-mst@redhat.com>
MIME-Version: 1.0
Content-Disposition: inline
In-Reply-To: <20200929071948.281157-1-mst@redhat.com>
X-Mailer: git-send-email 2.27.0.106.g8ac3dc51b1
X-Mutt-Fcc: =sent
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Jason Wang <jasowang@redhat.com>

Update against Linux 5.9-rc4.

Cc: Cornelia Huck <cohuck@redhat.com>
Cc: Paolo Bonzini <pbonzini@redhat.com>
Signed-off-by: Jason Wang <jasowang@redhat.com>
Message-Id: <20200907104903.31551-2-jasowang@redhat.com>
Reviewed-by: Michael S. Tsirkin <mst@redhat.com>
Signed-off-by: Michael S. Tsirkin <mst@redhat.com>
---
 include/standard-headers/drm/drm_fourcc.h     | 140 ++++++++++++++++++
 include/standard-headers/linux/ethtool.h      |  87 +++++++++++
 .../linux/input-event-codes.h                 |   3 +-
 include/standard-headers/linux/vhost_types.h  |  11 ++
 include/standard-headers/linux/virtio_9p.h    |   4 +-
 include/standard-headers/linux/virtio_blk.h   |  26 ++--
 .../standard-headers/linux/virtio_config.h    |   8 +-
 .../standard-headers/linux/virtio_console.h   |   8 +-
 include/standard-headers/linux/virtio_net.h   |   6 +-
 include/standard-headers/linux/virtio_scsi.h  |  20 +--
 linux-headers/asm-generic/unistd.h            |   6 +-
 linux-headers/asm-mips/unistd_n32.h           |   1 +
 linux-headers/asm-mips/unistd_n64.h           |   1 +
 linux-headers/asm-mips/unistd_o32.h           |   1 +
 linux-headers/asm-powerpc/kvm.h               |   5 +
 linux-headers/asm-powerpc/unistd_32.h         |   1 +
 linux-headers/asm-powerpc/unistd_64.h         |   1 +
 linux-headers/asm-s390/kvm.h                  |   7 +-
 linux-headers/asm-s390/unistd_32.h            |   1 +
 linux-headers/asm-s390/unistd_64.h            |   1 +
 linux-headers/asm-x86/unistd_32.h             |   1 +
 linux-headers/asm-x86/unistd_64.h             |   1 +
 linux-headers/asm-x86/unistd_x32.h            |   1 +
 linux-headers/linux/kvm.h                     |   4 +
 linux-headers/linux/vfio.h                    |   2 +-
 linux-headers/linux/vhost.h                   |   2 +
 26 files changed, 308 insertions(+), 41 deletions(-)

```
#### [PATCH v2] vfio/pci: Refine Intel IGD OpRegion support
##### From: Fred Gao <fred.gao@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Fred Gao <fred.gao@intel.com>
X-Patchwork-Id: 11805199
Return-Path: <SRS0=xlFf=DG=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 2A6BC112C
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 29 Sep 2020 08:15:15 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 1AD5C20C09
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 29 Sep 2020 08:15:15 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727679AbgI2IPO (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 29 Sep 2020 04:15:14 -0400
Received: from mga12.intel.com ([192.55.52.136]:6009 "EHLO mga12.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1725536AbgI2IPN (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 29 Sep 2020 04:15:13 -0400
IronPort-SDR: 
 J9cX7kLAZ5XUAARyemAX9Ny7+zpASNeE0ucKIj6+pp0ZYvDf1qqKUfFEwQ0AjexzfejSgLNuKE
 /HS9yYbz9NOg==
X-IronPort-AV: E=McAfee;i="6000,8403,9758"; a="141546655"
X-IronPort-AV: E=Sophos;i="5.77,317,1596524400";
   d="scan'208";a="141546655"
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from fmsmga002.fm.intel.com ([10.253.24.26])
  by fmsmga106.fm.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 29 Sep 2020 01:15:11 -0700
IronPort-SDR: 
 HdJEXw08RW2OmX8vo3ukX1Qwk5R1r9o2nTX3SKpagcWgz+VVDf6bA97Y6oSDzNrn7hKWI2yc+G
 1PYnviIZyXYg==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.77,317,1596524400";
   d="scan'208";a="345187563"
Received: from cfl-host.sh.intel.com ([10.239.158.142])
  by fmsmga002.fm.intel.com with ESMTP; 29 Sep 2020 01:15:07 -0700
From: Fred Gao <fred.gao@intel.com>
To: kvm@vger.kernel.org, intel-gfx@lists.freedesktop.org
Cc: Fred Gao <fred.gao@intel.com>,
        Zhenyu Wang <zhenyuw@linux.intel.com>,
        Xiong Zhang <xiong.y.zhang@intel.com>,
        Hang Yuan <hang.yuan@linux.intel.com>,
        Stuart Summers <stuart.summers@intel.com>,
        Lucas De Marchi <lucas.demarchi@intel.com>
Subject: [PATCH v2] vfio/pci: Refine Intel IGD OpRegion support
Date: Wed, 30 Sep 2020 00:10:38 +0800
Message-Id: <20200929161038.15465-1-fred.gao@intel.com>
X-Mailer: git-send-email 2.24.1.1.gb6d4d82bd5
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Bypass the IGD initialization for Intel's dgfx devices with own expansion
ROM and the host/LPC bridge config space are no longer accessed.

v2: simply test if discrete or integrated gfx device
    with root bus. (Alex Williamson)

Cc: Zhenyu Wang <zhenyuw@linux.intel.com>
Cc: Xiong Zhang <xiong.y.zhang@intel.com>
Cc: Hang Yuan <hang.yuan@linux.intel.com>
Cc: Stuart Summers <stuart.summers@intel.com>
Signed-off-by: Lucas De Marchi <lucas.demarchi@intel.com>
Signed-off-by: Fred Gao <fred.gao@intel.com>
Reviewed-by: Zhenyu Wang <zhenyuw@linux.intel.com>
---
 drivers/vfio/pci/vfio_pci.c | 5 +++--
 1 file changed, 3 insertions(+), 2 deletions(-)

```
#### [PATCH v5 01/10] vfio/fsl-mc: Add VFIO framework skeleton for fsl-mc devices
##### From: Diana Craciun <diana.craciun@oss.nxp.com>

```c
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Bharat Bhushan <Bharat.Bhushan@nxp.com>

DPAA2 (Data Path Acceleration Architecture) consists in
mechanisms for processing Ethernet packets, queue management,
accelerators, etc.

The Management Complex (mc) is a hardware entity that manages the DPAA2
hardware resources. It provides an object-based abstraction for software
drivers to use the DPAA2 hardware. The MC mediates operations such as
create, discover, destroy of DPAA2 objects.
The MC provides memory-mapped I/O command interfaces (MC portals) which
DPAA2 software drivers use to operate on DPAA2 objects.

A DPRC is a container object that holds other types of DPAA2 objects.
Each object in the DPRC is a Linux device and bound to a driver.
The MC-bus driver is a platform driver (different from PCI or platform
bus). The DPRC driver does runtime management of a bus instance. It
performs the initial scan of the DPRC and handles changes in the DPRC
configuration (adding/removing objects).

All objects inside a container share the same hardware isolation
context, meaning that only an entire DPRC can be assigned to
a virtual machine.
When a container is assigned to a virtual machine, all the objects
within that container are assigned to that virtual machine.
The DPRC container assigned to the virtual machine is not allowed
to change contents (add/remove objects) by the guest. The restriction
is set by the host and enforced by the mc hardware.

The DPAA2 objects can be directly assigned to the guest. However
the MC portals (the memory mapped command interface to the MC) need
to be emulated because there are commands that configure the
interrupts and the isolation IDs which are virtual in the guest.

Example:
echo vfio-fsl-mc > /sys/bus/fsl-mc/devices/dprc.2/driver_override
echo dprc.2 > /sys/bus/fsl-mc/drivers/vfio-fsl-mc/bind

The dprc.2 is bound to the VFIO driver and all the objects within
dprc.2 are going to be bound to the VFIO driver.

This patch adds the infrastructure for VFIO support for fsl-mc
devices. Subsequent patches will add support for binding and secure
assigning these devices using VFIO.

More details about the DPAA2 objects can be found here:
Documentation/networking/device_drivers/freescale/dpaa2/overview.rst

Signed-off-by: Bharat Bhushan <Bharat.Bhushan@nxp.com>
Signed-off-by: Diana Craciun <diana.craciun@oss.nxp.com>
---
 MAINTAINERS                               |   6 +
 drivers/vfio/Kconfig                      |   1 +
 drivers/vfio/Makefile                     |   1 +
 drivers/vfio/fsl-mc/Kconfig               |   9 ++
 drivers/vfio/fsl-mc/Makefile              |   4 +
 drivers/vfio/fsl-mc/vfio_fsl_mc.c         | 157 ++++++++++++++++++++++
 drivers/vfio/fsl-mc/vfio_fsl_mc_private.h |  14 ++
 include/uapi/linux/vfio.h                 |   1 +
 8 files changed, 193 insertions(+)
 create mode 100644 drivers/vfio/fsl-mc/Kconfig
 create mode 100644 drivers/vfio/fsl-mc/Makefile
 create mode 100644 drivers/vfio/fsl-mc/vfio_fsl_mc.c
 create mode 100644 drivers/vfio/fsl-mc/vfio_fsl_mc_private.h

```
