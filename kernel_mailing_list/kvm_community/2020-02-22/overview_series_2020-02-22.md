#### [RFC v3.1 01/22] scripts/update-linux-headers: Import iommu.h
##### From: Liu Yi L <yi.l.liu@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Liu Yi L <yi.l.liu@intel.com>
X-Patchwork-Id: 11397839
Return-Path: <SRS0=FEMj=4K=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 76A7092A
	for <patchwork-kvm@patchwork.kernel.org>;
 Sat, 22 Feb 2020 08:02:07 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 5F5DA214DB
	for <patchwork-kvm@patchwork.kernel.org>;
 Sat, 22 Feb 2020 08:02:07 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726928AbgBVIB6 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Sat, 22 Feb 2020 03:01:58 -0500
Received: from mga05.intel.com ([192.55.52.43]:63020 "EHLO mga05.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726883AbgBVIB6 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Sat, 22 Feb 2020 03:01:58 -0500
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from orsmga006.jf.intel.com ([10.7.209.51])
  by fmsmga105.fm.intel.com with ESMTP/TLS/DHE-RSA-AES256-GCM-SHA384;
 22 Feb 2020 00:01:57 -0800
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.70,471,1574150400";
   d="scan'208";a="240547653"
Received: from jacob-builder.jf.intel.com ([10.7.199.155])
  by orsmga006.jf.intel.com with ESMTP; 22 Feb 2020 00:01:56 -0800
From: Liu Yi L <yi.l.liu@intel.com>
To: qemu-devel@nongnu.org, alex.williamson@redhat.com,
        peterx@redhat.com
Cc: pbonzini@redhat.com, mst@redhat.com, eric.auger@redhat.com,
        david@gibson.dropbear.id.au, kevin.tian@intel.com,
        yi.l.liu@intel.com, jun.j.tian@intel.com, yi.y.sun@intel.com,
        kvm@vger.kernel.org, Jacob Pan <jacob.jun.pan@linux.intel.com>,
        Yi Sun <yi.y.sun@linux.intel.com>,
        Cornelia Huck <cohuck@redhat.com>
Subject: [RFC v3.1 01/22] scripts/update-linux-headers: Import iommu.h
Date: Sat, 22 Feb 2020 00:07:02 -0800
Message-Id: <1582358843-51931-2-git-send-email-yi.l.liu@intel.com>
X-Mailer: git-send-email 2.7.4
In-Reply-To: <1582358843-51931-1-git-send-email-yi.l.liu@intel.com>
References: <1582358843-51931-1-git-send-email-yi.l.liu@intel.com>
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Eric Auger <eric.auger@redhat.com>

Update the script to import the new iommu.h uapi header.

Cc: Kevin Tian <kevin.tian@intel.com>
Cc: Jacob Pan <jacob.jun.pan@linux.intel.com>
Cc: Peter Xu <peterx@redhat.com>
Cc: Yi Sun <yi.y.sun@linux.intel.com>
Cc: Michael S. Tsirkin <mst@redhat.com>
Cc: Cornelia Huck <cohuck@redhat.com>
Cc: Paolo Bonzini <pbonzini@redhat.com>
Acked-by: Cornelia Huck <cohuck@redhat.com>
Signed-off-by: Eric Auger <eric.auger@redhat.com>
---
 scripts/update-linux-headers.sh | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
#### [PATCH] KVM: x86: Adjust counter sample period after a wrmsrFrom: Eric Hankland <ehankland@google.com>
##### From: Eric Hankland <ehankland@google.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Eric Hankland <ehankland@google.com>
X-Patchwork-Id: 11397793
Return-Path: <SRS0=FEMj=4K=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id CC69314E3
	for <patchwork-kvm@patchwork.kernel.org>;
 Sat, 22 Feb 2020 02:35:42 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id A6184206EF
	for <patchwork-kvm@patchwork.kernel.org>;
 Sat, 22 Feb 2020 02:35:42 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=google.com header.i=@google.com
 header.b="eBgFXXFG"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727874AbgBVCfT (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 21 Feb 2020 21:35:19 -0500
Received: from mail-pl1-f201.google.com ([209.85.214.201]:50542 "EHLO
        mail-pl1-f201.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1727646AbgBVCfT (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 21 Feb 2020 21:35:19 -0500
Received: by mail-pl1-f201.google.com with SMTP id g5so2185655plq.17
        for <kvm@vger.kernel.org>; Fri, 21 Feb 2020 18:35:17 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=date:message-id:mime-version:subject:from:to:cc;
        bh=YWE+MLnOjK4IvZZLwvQEPG2A0OjN+JMmVnFRhQHYJMc=;
        b=eBgFXXFGkeT5/uAIvCLjYTs5ZF9zNsG77UJxFH5+o2fO8jOjzd7BGMrmBVaoruIcmq
         0A3nJSGzQJTcqWdmwClNEhhIfJT3RlBglY+KM212kLV0k99Kbd5YtWGs1PoXp9H5jKW7
         fOVGEWwtGLq/x6MQYFehTUpvgfVhndZL3KtWiczoGdaDqaOkzgAe2HIPD1oYzkop/d27
         bXetWVCGNsizjssAiZ9RuI2W44NN+s0ZBRdbbT2JTQeO7T2JvyAGrQlT75NsjEnh0hXu
         nA+4nlUufuZ0rl4P2+7v2D0jKFxRABY0AtwEUBgHKOAZbdzS1ZRBPGY3g0DaClPuv9pw
         NDjw==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:date:message-id:mime-version:subject:from:to:cc;
        bh=YWE+MLnOjK4IvZZLwvQEPG2A0OjN+JMmVnFRhQHYJMc=;
        b=Mo/vYEux0So3aQQAkSKV2TeZwYNp55zPFjvi7XXM86DLfqEf9PzbN6jCVLNqOM+Anw
         gsiA9e4IGWeyq6z22Lrwy3zHAQmuwcF4dvWx9X52hDUxeb70R+xeBAy7X3KhGFHTOahg
         qEtOB5LgOLmy5Bwnrc2Ma43JbnFKuPG5bD43+omvrFnAY09zVRHPOQfSZYrcCDNL1Zoi
         EDiHsrlqfhSA4LcH/bognDUPFVu090hVzTbwRzWdlXQKFaF58XhucTtuNZIv46sKaXFa
         ojnGiO32h/4PMceiu/EDX+wNzDjVjCfnge84ROLp5K9UZax5sdUA+WHfgBlXq2z48dyZ
         Zv2w==
X-Gm-Message-State: APjAAAVKStRZOceonxN0lP8g5EEy75D9juMzr//Z37qgvYVudXNDH92A
        55+62YZOXJQ6npeLz7VZW63MveyAODe9ilw=
X-Google-Smtp-Source: 
 APXvYqz/5nZSxiCEMANum1t9/MuA4rvyDGQUbSoYAmrDG89Qk66FIjDXtoFPXPLbgqYWY+92O8YQeM6VQxVkOk8=
X-Received: by 2002:a63:a807:: with SMTP id o7mr40015719pgf.407.1582338917117;
 Fri, 21 Feb 2020 18:35:17 -0800 (PST)
Date: Fri, 21 Feb 2020 18:34:13 -0800
Message-Id: <20200222023413.78202-1-ehankland@google.com>
Mime-Version: 1.0
X-Mailer: git-send-email 2.25.0.265.gbab2e86ba0-goog
Subject: [PATCH] KVM: x86: Adjust counter sample period after a wrmsr
From: Eric Hankland <ehankland@google.com>
To: Jim Mattson <jmattson@google.com>, Peter Shier <pshier@google.com>
Cc: Paolo Bonzini <pbonzini@redhat.com>, linux-kernel@vger.kernel.org,
        kvm@vger.kernel.org, Eric Hankland <ehankland@google.com>
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The sample_period of a counter tracks when that counter will
overflow and set global status/trigger a PMI. However this currently
only gets set when the initial counter is created or when a counter is
resumed; this updates the sample period after a wrmsr so running
counters will accurately reflect their new value.

Signed-off-by: Eric Hankland <ehankland@google.com>
---
 arch/x86/kvm/pmu.c           | 4 ++--
 arch/x86/kvm/pmu.h           | 8 ++++++++
 arch/x86/kvm/vmx/pmu_intel.c | 6 ++++++
 3 files changed, 16 insertions(+), 2 deletions(-)

```
#### [PATCH 3/7] docs: fix broken references to text files
##### From: Mauro Carvalho Chehab <mchehab+huawei@kernel.org>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 8bit
X-Patchwork-Submitter: Mauro Carvalho Chehab <mchehab+huawei@kernel.org>
X-Patchwork-Id: 11397977
Return-Path: <SRS0=FEMj=4K=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 370B914BC
	for <patchwork-kvm@patchwork.kernel.org>;
 Sat, 22 Feb 2020 09:00:24 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id E60942071E
	for <patchwork-kvm@patchwork.kernel.org>;
 Sat, 22 Feb 2020 09:00:23 +0000 (UTC)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple; d=kernel.org;
	s=default; t=1582362024;
	bh=KNCy8VqB8kUqNlZwdsMXuwJI3wKdtk11kLwmKelzDd8=;
	h=From:To:Cc:Subject:Date:In-Reply-To:References:List-ID:From;
	b=qQxeEYBfkhRfzR70wV9FKxRrrmqxJvqNRPuWM2q9zHbbKTYMWWDg1NoUORkTIEDUR
	 Zq0BbIRGf0giPVpZJBsBqhVbSaP7yJq85hq6CiNHhxySxTk+Ved+veIgXXVqqiU2r4
	 R5y8A2XF+ruw3kzwG+rOV8PJAzeqRudN2xgIv6NQ=
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727174AbgBVJAV (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Sat, 22 Feb 2020 04:00:21 -0500
Received: from bombadil.infradead.org ([198.137.202.133]:60550 "EHLO
        bombadil.infradead.org" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1727046AbgBVJAU (ORCPT <rfc822;kvm@vger.kernel.org>);
        Sat, 22 Feb 2020 04:00:20 -0500
DKIM-Signature: v=1; a=rsa-sha256; q=dns/txt; c=relaxed/relaxed;
        d=infradead.org; s=bombadil.20170209;
 h=Sender:Content-Transfer-Encoding:
        Content-Type:MIME-Version:References:In-Reply-To:Message-Id:Date:Subject:Cc:
        To:From:Reply-To:Content-ID:Content-Description;
        bh=abVL8ItEnCR/87zoT6gMplji+J0Sp3G5w+9DSLKwp/g=;
 b=ZxrqYZQ2hwN/SgyIRlnkorjMWk
        J9o0hZxy+CurOX+1I+7hbCiGEKbQ83DaxlUiWkZFue47/5Yp5JmpuGWI21byivd/2lL/kKLlrQpit
        TP+VaPuuPWbQkjTroHG8o4Dsq6U9Ta7NaElhLpn69DjQufWAmqAOES/6+tlgznwQ4HqJWe2X9kSPD
        cCF3w+/aqLvxI+eEF6ay+eAIFdoiQrV1xuOFymKX70wqngwThvHRwaYb6Rip68wzisUMjc3iVQdiq
        2R0XGptfSc+54Ih+da9xD2HaWEYTPOWByK1vocsvkv7dYzichZUfQlTDBXkkSoVh3AMFdj5hrQocL
        Rghl6wmA==;
Received: from [80.156.29.194] (helo=bombadil.infradead.org)
        by bombadil.infradead.org with esmtpsa (Exim 4.92.3 #3 (Red Hat
 Linux))
        id 1j5Qdz-0007Ho-8v; Sat, 22 Feb 2020 09:00:15 +0000
Received: from mchehab by bombadil.infradead.org with local (Exim 4.92.3)
        (envelope-from <mchehab@bombadil.infradead.org>)
        id 1j5Qdx-001N4M-Iz; Sat, 22 Feb 2020 10:00:13 +0100
From: Mauro Carvalho Chehab <mchehab+huawei@kernel.org>
To: Linux Doc Mailing List <linux-doc@vger.kernel.org>
Cc: Mauro Carvalho Chehab <mchehab+huawei@kernel.org>,
        Jonathan Corbet <corbet@lwn.net>, linux-arch@vger.kernel.org,
        kvm@vger.kernel.org, kvm-ppc@vger.kernel.org,
        linuxppc-dev@lists.ozlabs.org, dri-devel@lists.freedesktop.org,
        linux-arm-kernel@lists.infradead.org,
        linux-fsdevel@vger.kernel.org, linux-nfs@vger.kernel.org,
        linux-unionfs@vger.kernel.org, linux-mm@kvack.org,
        linux-rdma@vger.kernel.org, netdev@vger.kernel.org,
        kvmarm@lists.cs.columbia.edu
Subject: [PATCH 3/7] docs: fix broken references to text files
Date: Sat, 22 Feb 2020 10:00:03 +0100
Message-Id: 
 <5cfeed6df208b74913312a1c97235ee615180f91.1582361737.git.mchehab+huawei@kernel.org>
X-Mailer: git-send-email 2.24.1
In-Reply-To: <cover.1582361737.git.mchehab+huawei@kernel.org>
References: <cover.1582361737.git.mchehab+huawei@kernel.org>
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Several references got broken due to txt to ReST conversion.

Several of them can be automatically fixed with:

	scripts/documentation-file-ref-check --fix

Signed-off-by: Mauro Carvalho Chehab <mchehab+huawei@kernel.org>
Acked-by: Daniel Vetter <daniel.vetter@ffwll.ch>
---
 Documentation/admin-guide/kernel-parameters.txt      | 10 +++++-----
 Documentation/filesystems/cifs/cifsroot.txt          |  2 +-
 Documentation/memory-barriers.txt                    |  2 +-
 Documentation/process/submit-checklist.rst           |  2 +-
 .../translations/it_IT/process/submit-checklist.rst  |  2 +-
 Documentation/translations/ko_KR/memory-barriers.txt |  2 +-
 .../translations/zh_CN/filesystems/sysfs.txt         |  2 +-
 .../translations/zh_CN/process/submit-checklist.rst  |  2 +-
 Documentation/virt/kvm/arm/pvtime.rst                |  2 +-
 Documentation/virt/kvm/devices/vcpu.rst              |  2 +-
 Documentation/virt/kvm/hypercalls.rst                |  4 ++--
 arch/powerpc/include/uapi/asm/kvm_para.h             |  2 +-
 drivers/gpu/drm/Kconfig                              |  2 +-
 drivers/gpu/drm/drm_ioctl.c                          |  2 +-
 drivers/hwtracing/coresight/Kconfig                  |  2 +-
 fs/fat/Kconfig                                       |  8 ++++----
 fs/fuse/Kconfig                                      |  2 +-
 fs/fuse/dev.c                                        |  2 +-
 fs/nfs/Kconfig                                       |  2 +-
 fs/overlayfs/Kconfig                                 |  6 +++---
 include/linux/mm.h                                   |  4 ++--
 include/uapi/linux/ethtool_netlink.h                 |  2 +-
 include/uapi/rdma/rdma_user_ioctl_cmds.h             |  2 +-
 mm/gup.c                                             | 12 ++++++------
 net/ipv4/Kconfig                                     |  6 +++---
 net/ipv4/ipconfig.c                                  |  2 +-
 virt/kvm/arm/vgic/vgic-mmio-v3.c                     |  2 +-
 virt/kvm/arm/vgic/vgic.h                             |  4 ++--
 28 files changed, 47 insertions(+), 47 deletions(-)

```
#### [PATCH v2] mm/hugetlb: fix a addressing exception caused by huge_pte_offset()
##### From: "Longpeng(Mike)" <longpeng2@huawei.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: "Longpeng(Mike)" <longpeng2@huawei.com>
X-Patchwork-Id: 11397813
Return-Path: <SRS0=FEMj=4K=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id D947C159A
	for <patchwork-kvm@patchwork.kernel.org>;
 Sat, 22 Feb 2020 03:35:06 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id B7FB6206DB
	for <patchwork-kvm@patchwork.kernel.org>;
 Sat, 22 Feb 2020 03:35:06 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726691AbgBVDee (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 21 Feb 2020 22:34:34 -0500
Received: from szxga05-in.huawei.com ([45.249.212.191]:10670 "EHLO huawei.com"
        rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org with ESMTP
        id S1726032AbgBVDee (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 21 Feb 2020 22:34:34 -0500
Received: from DGGEMS407-HUB.china.huawei.com (unknown [172.30.72.60])
        by Forcepoint Email with ESMTP id DF35AB523A292F0A1675;
        Sat, 22 Feb 2020 11:34:30 +0800 (CST)
Received: from localhost (10.177.246.209) by DGGEMS407-HUB.china.huawei.com
 (10.3.19.207) with Microsoft SMTP Server id 14.3.439.0; Sat, 22 Feb 2020
 11:34:24 +0800
From: "Longpeng(Mike)" <longpeng2@huawei.com>
To: <akpm@linux-foundation.org>, <mike.kravetz@oracle.com>
CC: <kirill.shutemov@linux.intel.com>, <linux-kernel@vger.kernel.org>,
        <arei.gonglei@huawei.com>, <weidong.huang@huawei.com>,
        <weifuqiang@huawei.com>, <kvm@vger.kernel.org>,
        <linux-mm@kvack.org>, Longpeng <longpeng2@huawei.com>,
        Matthew Wilcox <willy@infradead.org>,
        "Sean Christopherson" <sean.j.christopherson@intel.com>,
        <stable@vger.kernel.org>
Subject: [PATCH v2] mm/hugetlb: fix a addressing exception caused by
 huge_pte_offset()
Date: Sat, 22 Feb 2020 11:33:47 +0800
Message-ID: <1582342427-230392-1-git-send-email-longpeng2@huawei.com>
X-Mailer: git-send-email 1.8.4.msysgit.0
MIME-Version: 1.0
X-Originating-IP: [10.177.246.209]
X-CFilter-Loop: Reflected
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Longpeng <longpeng2@huawei.com>

Our machine encountered a panic(addressing exception) after run
for a long time and the calltrace is:
RIP: 0010:[<ffffffff9dff0587>]  [<ffffffff9dff0587>] hugetlb_fault+0x307/0xbe0
RSP: 0018:ffff9567fc27f808  EFLAGS: 00010286
RAX: e800c03ff1258d48 RBX: ffffd3bb003b69c0 RCX: e800c03ff1258d48
RDX: 17ff3fc00eda72b7 RSI: 00003ffffffff000 RDI: e800c03ff1258d48
RBP: ffff9567fc27f8c8 R08: e800c03ff1258d48 R09: 0000000000000080
R10: ffffaba0704c22a8 R11: 0000000000000001 R12: ffff95c87b4b60d8
R13: 00005fff00000000 R14: 0000000000000000 R15: ffff9567face8074
FS:  00007fe2d9ffb700(0000) GS:ffff956900e40000(0000) knlGS:0000000000000000
CS:  0010 DS: 0000 ES: 0000 CR0: 0000000080050033
CR2: ffffd3bb003b69c0 CR3: 000000be67374000 CR4: 00000000003627e0
DR0: 0000000000000000 DR1: 0000000000000000 DR2: 0000000000000000
DR3: 0000000000000000 DR6: 00000000fffe0ff0 DR7: 0000000000000400
Call Trace:
 [<ffffffff9df9b71b>] ? unlock_page+0x2b/0x30
 [<ffffffff9dff04a2>] ? hugetlb_fault+0x222/0xbe0
 [<ffffffff9dff1405>] follow_hugetlb_page+0x175/0x540
 [<ffffffff9e15b825>] ? cpumask_next_and+0x35/0x50
 [<ffffffff9dfc7230>] __get_user_pages+0x2a0/0x7e0
 [<ffffffff9dfc648d>] __get_user_pages_unlocked+0x15d/0x210
 [<ffffffffc068cfc5>] __gfn_to_pfn_memslot+0x3c5/0x460 [kvm]
 [<ffffffffc06b28be>] try_async_pf+0x6e/0x2a0 [kvm]
 [<ffffffffc06b4b41>] tdp_page_fault+0x151/0x2d0 [kvm]
 [<ffffffffc075731c>] ? vmx_vcpu_run+0x2ec/0xc80 [kvm_intel]
 [<ffffffffc0757328>] ? vmx_vcpu_run+0x2f8/0xc80 [kvm_intel]
 [<ffffffffc06abc11>] kvm_mmu_page_fault+0x31/0x140 [kvm]
 [<ffffffffc074d1ae>] handle_ept_violation+0x9e/0x170 [kvm_intel]
 [<ffffffffc075579c>] vmx_handle_exit+0x2bc/0xc70 [kvm_intel]
 [<ffffffffc074f1a0>] ? __vmx_complete_interrupts.part.73+0x80/0xd0 [kvm_intel]
 [<ffffffffc07574c0>] ? vmx_vcpu_run+0x490/0xc80 [kvm_intel]
 [<ffffffffc069f3be>] vcpu_enter_guest+0x7be/0x13a0 [kvm]
 [<ffffffffc06cf53e>] ? kvm_check_async_pf_completion+0x8e/0xb0 [kvm]
 [<ffffffffc06a6f90>] kvm_arch_vcpu_ioctl_run+0x330/0x490 [kvm]
 [<ffffffffc068d919>] kvm_vcpu_ioctl+0x309/0x6d0 [kvm]
 [<ffffffff9deaa8c2>] ? dequeue_signal+0x32/0x180
 [<ffffffff9deae34d>] ? do_sigtimedwait+0xcd/0x230
 [<ffffffff9e03aed0>] do_vfs_ioctl+0x3f0/0x540
 [<ffffffff9e03b0c1>] SyS_ioctl+0xa1/0xc0
 [<ffffffff9e53879b>] system_call_fastpath+0x22/0x27

( The kernel we used is older, but we think the latest kernel also has this
  bug after dig into this problem. )

For 1G hugepages, huge_pte_offset() wants to return NULL or pudp, but it
may return a wrong 'pmdp' if there is a race. Please look at the following
code snippet:
    ...
    pud = pud_offset(p4d, addr);
    if (sz != PUD_SIZE && pud_none(*pud))
        return NULL;
    /* hugepage or swap? */
    if (pud_huge(*pud) || !pud_present(*pud))
        return (pte_t *)pud;

    pmd = pmd_offset(pud, addr);
    if (sz != PMD_SIZE && pmd_none(*pmd))
        return NULL;
    /* hugepage or swap? */
    if (pmd_huge(*pmd) || !pmd_present(*pmd))
        return (pte_t *)pmd;
    ...

The following sequence would trigger this bug:
1. CPU0: sz = PUD_SIZE and *pud = 0 , continue
1. CPU0: "pud_huge(*pud)" is false
2. CPU1: calling hugetlb_no_page and set *pud to xxxx8e7(PRESENT)
3. CPU0: "!pud_present(*pud)" is false, continue
4. CPU0: pmd = pmd_offset(pud, addr) and maybe return a wrong pmdp
However, we want CPU0 to return NULL or pudp.

We can avoid this race by read the pud only once. What's more, we also use
READ_ONCE to access the entries for safe(e.g. avoid the compilier mischief)

Cc: Matthew Wilcox <willy@infradead.org>
Cc: Sean Christopherson <sean.j.christopherson@intel.com>
Cc: Mike Kravetz <mike.kravetz@oracle.com>
Cc: stable@vger.kernel.org
Signed-off-by: Longpeng <longpeng2@huawei.com>
---
v1 -> v2:
  - avoid renaming    [Matthew, Mike]

---
 mm/hugetlb.c | 18 ++++++++++--------
 1 file changed, 10 insertions(+), 8 deletions(-)

```
