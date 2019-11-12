#### [RESEND PATCH v21 1/6] hw/arm/virt: Introduce a RAS machine option
##### From: Xiang Zheng <zhengxiang9@huawei.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Xiang Zheng <zhengxiang9@huawei.com>
X-Patchwork-Id: 11236411
Return-Path: <SRS0=QoBT=ZD=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id BA7551390
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 11 Nov 2019 01:44:28 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id A29C1206DF
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 11 Nov 2019 01:44:28 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726845AbfKKBo1 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Sun, 10 Nov 2019 20:44:27 -0500
Received: from szxga07-in.huawei.com ([45.249.212.35]:55648 "EHLO huawei.com"
        rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org with ESMTP
        id S1726754AbfKKBo1 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Sun, 10 Nov 2019 20:44:27 -0500
Received: from DGGEMS403-HUB.china.huawei.com (unknown [172.30.72.59])
        by Forcepoint Email with ESMTP id 07E0995406B7BB897352;
        Mon, 11 Nov 2019 09:44:21 +0800 (CST)
Received: from HGHY4Z004218071.china.huawei.com (10.133.224.57) by
 DGGEMS403-HUB.china.huawei.com (10.3.19.203) with Microsoft SMTP Server id
 14.3.439.0; Mon, 11 Nov 2019 09:44:14 +0800
From: Xiang Zheng <zhengxiang9@huawei.com>
To: <pbonzini@redhat.com>, <mst@redhat.com>, <imammedo@redhat.com>,
        <shannon.zhaosl@gmail.com>, <peter.maydell@linaro.org>,
        <lersek@redhat.com>, <james.morse@arm.com>,
        <gengdongjiu@huawei.com>, <mtosatti@redhat.com>, <rth@twiddle.net>,
        <ehabkost@redhat.com>, <jonathan.cameron@huawei.com>,
        <xuwei5@huawei.com>, <kvm@vger.kernel.org>,
        <qemu-devel@nongnu.org>, <qemu-arm@nongnu.org>,
        <linuxarm@huawei.com>
CC: <zhengxiang9@huawei.com>, <wanghaibin.wang@huawei.com>
Subject: [RESEND PATCH v21 1/6] hw/arm/virt: Introduce a RAS machine option
Date: Mon, 11 Nov 2019 09:40:43 +0800
Message-ID: <20191111014048.21296-2-zhengxiang9@huawei.com>
X-Mailer: git-send-email 2.15.1.windows.2
In-Reply-To: <20191111014048.21296-1-zhengxiang9@huawei.com>
References: <20191111014048.21296-1-zhengxiang9@huawei.com>
MIME-Version: 1.0
X-Originating-IP: [10.133.224.57]
X-CFilter-Loop: Reflected
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Dongjiu Geng <gengdongjiu@huawei.com>

RAS Virtualization feature is not supported now, so add a RAS machine
option and disable it by default.

Signed-off-by: Dongjiu Geng <gengdongjiu@huawei.com>
Signed-off-by: Xiang Zheng <zhengxiang9@huawei.com>
---
 hw/arm/virt.c         | 23 +++++++++++++++++++++++
 include/hw/arm/virt.h |  1 +
 2 files changed, 24 insertions(+)

```
#### [PATCH 1/2] KVM: Fix NULL-ptr deref after kvm_create_vm fails
##### From: Paolo Bonzini <pbonzini@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Paolo Bonzini <pbonzini@redhat.com>
X-Patchwork-Id: 11236983
Return-Path: <SRS0=QoBT=ZD=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 1B2891515
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 11 Nov 2019 13:25:53 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id E385C21D7F
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 11 Nov 2019 13:25:52 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=fail reason="signature verification failed" (2048-bit key)
 header.d=gmail.com header.i=@gmail.com header.b="HlJap5qg"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727050AbfKKNZt (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 11 Nov 2019 08:25:49 -0500
Received: from mail-wr1-f67.google.com ([209.85.221.67]:44181 "EHLO
        mail-wr1-f67.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726853AbfKKNZr (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 11 Nov 2019 08:25:47 -0500
Received: by mail-wr1-f67.google.com with SMTP id f2so14578439wrs.11;
        Mon, 11 Nov 2019 05:25:45 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=sender:from:to:cc:subject:date:message-id:in-reply-to:references;
        bh=cgaP4CM+Ld92kjauj0hAJd9jloxavzxYcznYyyWs8P0=;
        b=HlJap5qgPKeyY2OAT0xD92x9hUvjG4dAsQe7r3A9RrIxakt1TdKMQqZW+17e3rHq8x
         yIySwRidYiAa4PsLGQ2xLuxJkc3K5H9Zd4DLzbZHECqi9nC7nWWDg0o4MUXHeSSjUcsD
         bTVBK2A6NnqTn8xwsKyoHQZsl6EMgPNgrqO8R0C0mz9J3urvgZE7LM0DHTOljsqZ3lF9
         d5kY7AYtuybCV2IZW3cTHCRzawI9cp3Oi45UtGaf8jpp0TEGBOLOsZpPbLm/Tu5Th8Ap
         LKgChbyZ4EyDsqbxFq7Yt1qrpP29bi4g9YyoNkb/ze3ShoqZIAK5xsXhKZZc/aNzWGoi
         8mjw==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:sender:from:to:cc:subject:date:message-id
         :in-reply-to:references;
        bh=cgaP4CM+Ld92kjauj0hAJd9jloxavzxYcznYyyWs8P0=;
        b=G5bs23f9RjcUpywUZD1FLK66WdxlrYjUSjv/Uo3yKQwYewNqVIj80e9pjfjBcMG2PC
         J6Uai+vRtUZcza4Ir6ejf7B0xISVLRsn8XYhJYboGGWkcUg/BBIDCRLzcEi9g3RzyEB2
         wPCCZvEA6NcKs1Ht/8uCf/11Gf/m+Otu3ZndN6PmNNq/a4+shQ0TkOVp9SJm9mkiBxFa
         UDiOu1UfA22ETulKnnSZC10wE5i0sRL1/D0yQW8weTpJ6Vk2bLB03qCK6izuSXPxHVme
         y1MMKU04zdbNfeTIDsKuF/reEZmDfYIZOoKXSpzZk1M7bvUpdS6PSAk6S5XfsthDIFf2
         7TEw==
X-Gm-Message-State: APjAAAVNDnza2uFQo7rswqIerS5rA41QoS4sBYuhFqEKOBy9HJK4RtQu
        /CM0mccDyi5UhmLLAcGG0g6nz2Md
X-Google-Smtp-Source: 
 APXvYqzN1OYAw3H9KqAqbBcd0+XqONzKKF2E681lwA/dCOhnt2xUF7u7CCvTlZ6F3DhOYhByafUi8w==
X-Received: by 2002:adf:e78c:: with SMTP id n12mr19268205wrm.94.1573478744817;
        Mon, 11 Nov 2019 05:25:44 -0800 (PST)
Received: from 640k.lan ([93.56.166.5])
        by smtp.gmail.com with ESMTPSA id
 p1sm7555131wmc.38.2019.11.11.05.25.43
        (version=TLS1_2 cipher=ECDHE-RSA-AES128-GCM-SHA256 bits=128/128);
        Mon, 11 Nov 2019 05:25:43 -0800 (PST)
From: Paolo Bonzini <pbonzini@redhat.com>
To: linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Cc: jmattson@google.com, wanpengli@tencent.com,
        Junaid Shahid <junaids@google.com>
Subject: [PATCH 1/2] KVM: Fix NULL-ptr deref after kvm_create_vm fails
Date: Mon, 11 Nov 2019 14:25:40 +0100
Message-Id: <1573478741-30959-2-git-send-email-pbonzini@redhat.com>
X-Mailer: git-send-email 1.8.3.1
In-Reply-To: <1573478741-30959-1-git-send-email-pbonzini@redhat.com>
References: <1573478741-30959-1-git-send-email-pbonzini@redhat.com>
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Reported by syzkaller:

    kasan: CONFIG_KASAN_INLINE enabled
    kasan: GPF could be caused by NULL-ptr deref or user memory access
    general protection fault: 0000 [#1] PREEMPT SMP KASAN
    CPU: 0 PID: 14727 Comm: syz-executor.3 Not tainted 5.4.0-rc4+ #0
    RIP: 0010:kvm_coalesced_mmio_init+0x5d/0x110 arch/x86/kvm/../../../virt/kvm/coalesced_mmio.c:121
    Call Trace:
     kvm_dev_ioctl_create_vm arch/x86/kvm/../../../virt/kvm/kvm_main.c:3446 [inline]
     kvm_dev_ioctl+0x781/0x1490 arch/x86/kvm/../../../virt/kvm/kvm_main.c:3494
     vfs_ioctl fs/ioctl.c:46 [inline]
     file_ioctl fs/ioctl.c:509 [inline]
     do_vfs_ioctl+0x196/0x1150 fs/ioctl.c:696
     ksys_ioctl+0x62/0x90 fs/ioctl.c:713
     __do_sys_ioctl fs/ioctl.c:720 [inline]
     __se_sys_ioctl fs/ioctl.c:718 [inline]
     __x64_sys_ioctl+0x6e/0xb0 fs/ioctl.c:718
     do_syscall_64+0xca/0x5d0 arch/x86/entry/common.c:290
     entry_SYSCALL_64_after_hwframe+0x49/0xbe

Commit 9121923c457d ("kvm: Allocate memslots and buses before calling kvm_arch_init_vm")
moves memslots and buses allocations around, however, if kvm->srcu/irq_srcu fails
initialization, NULL will be returned instead of error code, NULL will not be intercepted
in kvm_dev_ioctl_create_vm() and be deferenced by kvm_coalesced_mmio_init(), this patch
fixes it.

Moving the initialization is required anyway to avoid an incorrect synchronize_srcu that
was also reported by syzkaller:

 wait_for_completion+0x29c/0x440 kernel/sched/completion.c:136
 __synchronize_srcu+0x197/0x250 kernel/rcu/srcutree.c:921
 synchronize_srcu_expedited kernel/rcu/srcutree.c:946 [inline]
 synchronize_srcu+0x239/0x3e8 kernel/rcu/srcutree.c:997
 kvm_page_track_unregister_notifier+0xe7/0x130 arch/x86/kvm/page_track.c:212
 kvm_mmu_uninit_vm+0x1e/0x30 arch/x86/kvm/mmu.c:5828
 kvm_arch_destroy_vm+0x4a2/0x5f0 arch/x86/kvm/x86.c:9579
 kvm_create_vm arch/x86/kvm/../../../virt/kvm/kvm_main.c:702 [inline]

so do it.

Reported-by: syzbot+89a8060879fa0bd2db4f@syzkaller.appspotmail.com
Reported-by: syzbot+e27e7027eb2b80e44225@syzkaller.appspotmail.com
Fixes: 9121923c457d ("kvm: Allocate memslots and buses before calling kvm_arch_init_vm")
Cc: Jim Mattson <jmattson@google.com>
Cc: Wanpeng Li <wanpengli@tencent.com>
Signed-off-by: Paolo Bonzini <pbonzini@redhat.com>
---
 virt/kvm/kvm_main.c | 18 +++++++++---------
 1 file changed, 9 insertions(+), 9 deletions(-)

```
#### [PATCH v2 1/3] KVM: MMU: Do not treat ZONE_DEVICE pages as being reserved
##### From: Sean Christopherson <sean.j.christopherson@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Sean Christopherson <sean.j.christopherson@intel.com>
X-Patchwork-Id: 11237941
Return-Path: <SRS0=QoBT=ZD=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id B8D4E13BD
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 11 Nov 2019 22:12:42 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 970D22184C
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 11 Nov 2019 22:12:42 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727133AbfKKWMd (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 11 Nov 2019 17:12:33 -0500
Received: from mga03.intel.com ([134.134.136.65]:2932 "EHLO mga03.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1727053AbfKKWMb (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 11 Nov 2019 17:12:31 -0500
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from orsmga001.jf.intel.com ([10.7.209.18])
  by orsmga103.jf.intel.com with ESMTP/TLS/DHE-RSA-AES256-GCM-SHA384;
 11 Nov 2019 14:12:30 -0800
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.68,294,1569308400";
   d="scan'208";a="287302341"
Received: from sjchrist-coffee.jf.intel.com ([10.54.74.41])
  by orsmga001.jf.intel.com with ESMTP; 11 Nov 2019 14:12:29 -0800
From: Sean Christopherson <sean.j.christopherson@intel.com>
To: Paolo Bonzini <pbonzini@redhat.com>,
 =?utf-8?b?UmFkaW0gS3LEjW3DocWZ?= <rkrcmar@redhat.com>
Cc: Sean Christopherson <sean.j.christopherson@intel.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org, Adam Borowski <kilobyte@angband.pl>,
        David Hildenbrand <david@redhat.com>,
        Dan Williams <dan.j.williams@intel.com>
Subject: [PATCH v2 1/3] KVM: MMU: Do not treat ZONE_DEVICE pages as being
 reserved
Date: Mon, 11 Nov 2019 14:12:27 -0800
Message-Id: <20191111221229.24732-2-sean.j.christopherson@intel.com>
X-Mailer: git-send-email 2.24.0
In-Reply-To: <20191111221229.24732-1-sean.j.christopherson@intel.com>
References: <20191111221229.24732-1-sean.j.christopherson@intel.com>
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Explicitly exempt ZONE_DEVICE pages from kvm_is_reserved_pfn() and
instead manually handle ZONE_DEVICE on a case-by-case basis.  For things
like page refcounts, KVM needs to treat ZONE_DEVICE pages like normal
pages, e.g. put pages grabbed via gup().  But for flows such as setting
A/D bits or shifting refcounts for transparent huge pages, KVM needs to
to avoid processing ZONE_DEVICE pages as the flows in question lack the
underlying machinery for proper handling of ZONE_DEVICE pages.

This fixes a hang reported by Adam Borowski[*] in dev_pagemap_cleanup()
when running a KVM guest backed with /dev/dax memory, as KVM straight up
doesn't put any references to ZONE_DEVICE pages acquired by gup().

Note, Dan Williams proposed an alternative solution of doing put_page()
on ZONE_DEVICE pages immediately after gup() in order to simplify the
auditing needed to ensure is_zone_device_page() is called if and only if
the backing device is pinned (via gup()).  But that approach would break
kvm_vcpu_{un}map() as KVM requires the page to be pinned from map() 'til
unmap() when accessing guest memory, unlike KVM's secondary MMU, which
coordinates with mmu_notifier invalidations to avoid creating stale
page references, i.e. doesn't rely on pages being pinned.

[*] http://lkml.kernel.org/r/20190919115547.GA17963@angband.pl

Reported-by: Adam Borowski <kilobyte@angband.pl>
Debugged-by: David Hildenbrand <david@redhat.com>
Cc: Dan Williams <dan.j.williams@intel.com>
Cc: stable@vger.kernel.org
Signed-off-by: Sean Christopherson <sean.j.christopherson@intel.com>
Acked-by: Dan Williams <dan.j.williams@intel.com>
---
 arch/x86/kvm/mmu.c       |  8 ++++----
 include/linux/kvm_host.h |  1 +
 virt/kvm/kvm_main.c      | 26 +++++++++++++++++++++++---
 3 files changed, 28 insertions(+), 7 deletions(-)

```
#### [PATCH 1/2] KVM: VMX: Refactor update_cr8_intercept()
##### From: Liran Alon <liran.alon@oracle.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Liran Alon <liran.alon@oracle.com>
X-Patchwork-Id: 11236919
Return-Path: <SRS0=QoBT=ZD=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 2A1821515
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 11 Nov 2019 12:31:16 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 0781821D7F
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 11 Nov 2019 12:31:16 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=oracle.com header.i=@oracle.com
 header.b="ORcOgt1z"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726939AbfKKMbP (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 11 Nov 2019 07:31:15 -0500
Received: from userp2120.oracle.com ([156.151.31.85]:41928 "EHLO
        userp2120.oracle.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726832AbfKKMbP (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 11 Nov 2019 07:31:15 -0500
Received: from pps.filterd (userp2120.oracle.com [127.0.0.1])
        by userp2120.oracle.com (8.16.0.27/8.16.0.27) with SMTP id
 xABCTIRF001057;
        Mon, 11 Nov 2019 12:31:08 GMT
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=oracle.com;
 h=from : to : cc :
 subject : date : message-id : in-reply-to : references : mime-version :
 content-transfer-encoding; s=corp-2019-08-05;
 bh=aKddiHHlVYayzovRuxrKfK4LF30Fl4qYwwIV3QezfQk=;
 b=ORcOgt1zFWsJ8hsl39fomvtp+oMxAWMh56vrK2yCE1h9KKwzsAjQu48iK24rcEcdxgri
 qtk+jqRMj0IFookPU4RLoHhRwaCKAeg34WSUYx9sLm+tdfC86CcT0+rqQEJ1TFba/zGR
 Tua1f2aYlZH2qwvO/NHYe8wMyWpiU2E+Tay+nFRFWze3MoAAApFUa9gczAc9ADVpmaNB
 OrWpSo9qlVp8jeBtW/PnaNlonLNa9tKIgL1NzkqGkkkSK3yHJ6uSXuncobNKVzLX4IGb
 4MCQJ9rlcqXVz3lkVA6cq7S/GINoNNd+B6DTl3COtFvCuErjd4YRyRmsqn21SjNOrdbA fQ==
Received: from userp3030.oracle.com (userp3030.oracle.com [156.151.31.80])
        by userp2120.oracle.com with ESMTP id 2w5p3qenc9-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Mon, 11 Nov 2019 12:31:07 +0000
Received: from pps.filterd (userp3030.oracle.com [127.0.0.1])
        by userp3030.oracle.com (8.16.0.27/8.16.0.27) with SMTP id
 xABCSH3U188339;
        Mon, 11 Nov 2019 12:31:07 GMT
Received: from userv0121.oracle.com (userv0121.oracle.com [156.151.31.72])
        by userp3030.oracle.com with ESMTP id 2w66wm1cyq-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Mon, 11 Nov 2019 12:31:07 +0000
Received: from abhmp0015.oracle.com (abhmp0015.oracle.com [141.146.116.21])
        by userv0121.oracle.com (8.14.4/8.13.8) with ESMTP id xABCV69E026854;
        Mon, 11 Nov 2019 12:31:06 GMT
Received: from Lirans-MBP.Home (/79.182.207.213)
        by default (Oracle Beehive Gateway v4.0)
        with ESMTP ; Mon, 11 Nov 2019 04:31:06 -0800
From: Liran Alon <liran.alon@oracle.com>
To: pbonzini@redhat.com, rkrcmar@redhat.com, kvm@vger.kernel.org
Cc: sean.j.christopherson@intel.com, jmattson@google.com,
        vkuznets@redhat.com, Liran Alon <liran.alon@oracle.com>,
        Joao Martins <joao.m.martins@oracle.com>
Subject: [PATCH 1/2] KVM: VMX: Refactor update_cr8_intercept()
Date: Mon, 11 Nov 2019 14:30:54 +0200
Message-Id: <20191111123055.93270-2-liran.alon@oracle.com>
X-Mailer: git-send-email 2.20.1
In-Reply-To: <20191111123055.93270-1-liran.alon@oracle.com>
References: <20191111123055.93270-1-liran.alon@oracle.com>
MIME-Version: 1.0
X-Proofpoint-Virus-Version: vendor=nai engine=6000 definitions=9437
 signatures=668685
X-Proofpoint-Spam-Details: rule=notspam policy=default score=0 suspectscore=0
 malwarescore=0
 phishscore=0 bulkscore=0 spamscore=0 mlxscore=0 mlxlogscore=672
 adultscore=0 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.0.1-1910280000 definitions=main-1911110119
X-Proofpoint-Virus-Version: vendor=nai engine=6000 definitions=9437
 signatures=668685
X-Proofpoint-Spam-Details: rule=notspam policy=default score=0
 priorityscore=1501 malwarescore=0
 suspectscore=0 phishscore=0 bulkscore=0 spamscore=0 clxscore=1015
 lowpriorityscore=0 mlxscore=0 impostorscore=0 mlxlogscore=739 adultscore=0
 classifier=spam adjust=0 reason=mlx scancount=1 engine=8.0.1-1910280000
 definitions=main-1911110119
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

No functional changes.

Reviewed-by: Joao Martins <joao.m.martins@oracle.com>
Signed-off-by: Liran Alon <liran.alon@oracle.com>
---
 arch/x86/kvm/vmx/vmx.c | 9 +++------
 1 file changed, 3 insertions(+), 6 deletions(-)

```
#### [PATCH] KVM: SVM: Remove check if APICv enabled in SVM update_cr8_intercept() handler
##### From: Liran Alon <liran.alon@oracle.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Liran Alon <liran.alon@oracle.com>
X-Patchwork-Id: 11236903
Return-Path: <SRS0=QoBT=ZD=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id DA3551747
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 11 Nov 2019 12:26:46 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id B83552190F
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 11 Nov 2019 12:26:46 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=oracle.com header.i=@oracle.com
 header.b="NR6i4N4O"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726927AbfKKM0p (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 11 Nov 2019 07:26:45 -0500
Received: from userp2130.oracle.com ([156.151.31.86]:40422 "EHLO
        userp2130.oracle.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726810AbfKKM0p (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 11 Nov 2019 07:26:45 -0500
Received: from pps.filterd (userp2130.oracle.com [127.0.0.1])
        by userp2130.oracle.com (8.16.0.27/8.16.0.27) with SMTP id
 xABCOPCK029593;
        Mon, 11 Nov 2019 12:26:38 GMT
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=oracle.com;
 h=from : to : cc :
 subject : date : message-id : mime-version : content-transfer-encoding;
 s=corp-2019-08-05; bh=r1rjcAgGAp5ZY3/IGNXNwWzPRleq75n5kBIEIXj0QQQ=;
 b=NR6i4N4OtzWbs/JtyaLFfuVypnSvE17e3PrXVg3akcIaMtRDg7g1qSQkNMrzmXnxuID8
 +cxO4KQ6MRdZIigtBMHk8BFCDNATU6QcWAOJGRct7O+g0bq9Wlpdd9PCI/Fe83LxuuAJ
 rjIn+OdO91a/1R8G9iOkm5AXkRTmElBiTs2lTlsMb+iDTuY4UfEGoSW0WE06iueySRi1
 sFcAWgB5XrLOknDWdMmy8pOGfdMZL69KejxcFGzXQnxkJuLmxzPHfj/yU+ngtfJ9cpq0
 tK3ZSAGZKirjARKhyjbztf7r86Qr1NoZXt2glLD6JXcqgn+v7FV5tV7vhlraao/Zr/3N +A==
Received: from userp3020.oracle.com (userp3020.oracle.com [156.151.31.79])
        by userp2130.oracle.com with ESMTP id 2w5mvtes4y-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Mon, 11 Nov 2019 12:26:38 +0000
Received: from pps.filterd (userp3020.oracle.com [127.0.0.1])
        by userp3020.oracle.com (8.16.0.27/8.16.0.27) with SMTP id
 xABCNQSQ058167;
        Mon, 11 Nov 2019 12:26:37 GMT
Received: from aserv0121.oracle.com (aserv0121.oracle.com [141.146.126.235])
        by userp3020.oracle.com with ESMTP id 2w67kkx1cw-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Mon, 11 Nov 2019 12:26:37 +0000
Received: from abhmp0002.oracle.com (abhmp0002.oracle.com [141.146.116.8])
        by aserv0121.oracle.com (8.14.4/8.13.8) with ESMTP id xABCQaQR004949;
        Mon, 11 Nov 2019 12:26:36 GMT
Received: from Lirans-MBP.Home (/79.182.207.213)
        by default (Oracle Beehive Gateway v4.0)
        with ESMTP ; Mon, 11 Nov 2019 12:26:36 +0000
From: Liran Alon <liran.alon@oracle.com>
To: pbonzini@redhat.com, rkrcmar@redhat.com, kvm@vger.kernel.org
Cc: sean.j.christopherson@intel.com, jmattson@google.com,
        vkuznets@redhat.com, Liran Alon <liran.alon@oracle.com>,
        Joao Martins <joao.m.martins@oracle.com>
Subject: [PATCH] KVM: SVM: Remove check if APICv enabled in SVM
 update_cr8_intercept() handler
Date: Mon, 11 Nov 2019 14:26:21 +0200
Message-Id: <20191111122621.93151-1-liran.alon@oracle.com>
X-Mailer: git-send-email 2.20.1
MIME-Version: 1.0
X-Proofpoint-Virus-Version: vendor=nai engine=6000 definitions=9437
 signatures=668685
X-Proofpoint-Spam-Details: rule=notspam policy=default score=0 suspectscore=0
 malwarescore=0
 phishscore=0 bulkscore=0 spamscore=0 mlxscore=0 mlxlogscore=891
 adultscore=0 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.0.1-1910280000 definitions=main-1911110118
X-Proofpoint-Virus-Version: vendor=nai engine=6000 definitions=9437
 signatures=668685
X-Proofpoint-Spam-Details: rule=notspam policy=default score=0
 priorityscore=1501 malwarescore=0
 suspectscore=0 phishscore=0 bulkscore=0 spamscore=0 clxscore=1015
 lowpriorityscore=0 mlxscore=0 impostorscore=0 mlxlogscore=967 adultscore=0
 classifier=spam adjust=0 reason=mlx scancount=1 engine=8.0.1-1910280000
 definitions=main-1911110118
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This check is unnecessary as x86 update_cr8_intercept() which calls
this VMX/SVM specific callback already performs this check.

Reviewed-by: Joao Martins <joao.m.martins@oracle.com>
Signed-off-by: Liran Alon <liran.alon@oracle.com>
---
 arch/x86/kvm/svm.c | 3 +--
 1 file changed, 1 insertion(+), 2 deletions(-)

```
#### [PATCH] KVM: VMX: Consume pending LAPIC INIT event when exit on INIT_SIGNAL
##### From: Liran Alon <liran.alon@oracle.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 8bit
X-Patchwork-Submitter: Liran Alon <liran.alon@oracle.com>
X-Patchwork-Id: 11236869
Return-Path: <SRS0=QoBT=ZD=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 05D9A1515
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 11 Nov 2019 12:18:28 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id CF74E21783
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 11 Nov 2019 12:18:27 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=oracle.com header.i=@oracle.com
 header.b="EGZHbrrY"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726879AbfKKMS0 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 11 Nov 2019 07:18:26 -0500
Received: from userp2130.oracle.com ([156.151.31.86]:60032 "EHLO
        userp2130.oracle.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726810AbfKKMS0 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 11 Nov 2019 07:18:26 -0500
Received: from pps.filterd (userp2130.oracle.com [127.0.0.1])
        by userp2130.oracle.com (8.16.0.27/8.16.0.27) with SMTP id
 xABCEQUA022403;
        Mon, 11 Nov 2019 12:18:17 GMT
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=oracle.com;
 h=from : to : cc :
 subject : date : message-id : mime-version : content-type :
 content-transfer-encoding; s=corp-2019-08-05;
 bh=mn46o40bNlnHnMHAQWtCaKOscO0mRPRb40Zp9eE01xI=;
 b=EGZHbrrYotyV67VM6J6lvXs6kSMwZEZYacvcf/XuieRp3EM50S5ECcyEBXaRRZuEHkJA
 gRvB7MD0NScHOSZVj4k5C1nbtComlb0+n8b8IM8DOGDCPX5Uj4MLlxGL4eT3ylqyleyZ
 coB0zUo4e+tSSJ4OummphU9sPBW44tWKVTakIuH72zNrMzQn99NEsq85K7eHXPUqFUA8
 2urCYL5aqgUxcIPWS7M74L9WCxKa9ELMFdHS33XoQLA6A/skNdc2EGfysvO+C0hhrZ84
 qN59GKY4zojIAQnO9z/YYISqzasY/ILBWvF+x8uNUHhjmUpZmT3fSue2GepyuaJfN0XT /g==
Received: from aserp3030.oracle.com (aserp3030.oracle.com [141.146.126.71])
        by userp2130.oracle.com with ESMTP id 2w5mvter53-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Mon, 11 Nov 2019 12:18:17 +0000
Received: from pps.filterd (aserp3030.oracle.com [127.0.0.1])
        by aserp3030.oracle.com (8.16.0.27/8.16.0.27) with SMTP id
 xABC92XF026325;
        Mon, 11 Nov 2019 12:16:16 GMT
Received: from userv0122.oracle.com (userv0122.oracle.com [156.151.31.75])
        by aserp3030.oracle.com with ESMTP id 2w6r8jfs5v-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Mon, 11 Nov 2019 12:16:16 +0000
Received: from abhmp0022.oracle.com (abhmp0022.oracle.com [141.146.116.28])
        by userv0122.oracle.com (8.14.4/8.14.4) with ESMTP id xABCGE2p014775;
        Mon, 11 Nov 2019 12:16:15 GMT
Received: from Lirans-MBP.Home (/79.182.207.213)
        by default (Oracle Beehive Gateway v4.0)
        with ESMTP ; Mon, 11 Nov 2019 12:16:14 +0000
From: Liran Alon <liran.alon@oracle.com>
To: pbonzini@redhat.com, rkrcmar@redhat.com, kvm@vger.kernel.org
Cc: sean.j.christopherson@intel.com, jmattson@google.com,
        vkuznets@redhat.com, nadav.amit@gmail.com,
        Liran Alon <liran.alon@oracle.com>,
        Mihai Carabas <mihai.carabas@oracle.com>,
        Joao Martins <joao.m.martins@oracle.com>
Subject: [PATCH] KVM: VMX: Consume pending LAPIC INIT event when exit on
 INIT_SIGNAL
Date: Mon, 11 Nov 2019 14:16:05 +0200
Message-Id: <20191111121605.92972-1-liran.alon@oracle.com>
X-Mailer: git-send-email 2.20.1
MIME-Version: 1.0
X-Proofpoint-Virus-Version: vendor=nai engine=6000 definitions=9437
 signatures=668685
X-Proofpoint-Spam-Details: rule=notspam policy=default score=0 suspectscore=0
 malwarescore=0
 phishscore=0 bulkscore=0 spamscore=0 mlxscore=0 mlxlogscore=999
 adultscore=0 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.0.1-1910280000 definitions=main-1911110116
X-Proofpoint-Virus-Version: vendor=nai engine=6000 definitions=9437
 signatures=668685
X-Proofpoint-Spam-Details: rule=notspam policy=default score=0
 priorityscore=1501 malwarescore=0
 suspectscore=0 phishscore=0 bulkscore=0 spamscore=0 clxscore=1011
 lowpriorityscore=0 mlxscore=0 impostorscore=0 mlxlogscore=999 adultscore=0
 classifier=spam adjust=0 reason=mlx scancount=1 engine=8.0.1-1910280000
 definitions=main-1911110117
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Intel SDM section 25.2 OTHER CAUSES OF VM EXITS specifies the following
on INIT signals: "Such exits do not modify register state or clear pending
events as they would outside of VMX operation."

When commit 4b9852f4f389 ("KVM: x86: Fix INIT signal handling in various CPU states")
was applied, I interepted above Intel SDM statement such that
INIT_SIGNAL exit don’t consume the LAPIC INIT pending event.

However, when Nadav Amit run matching kvm-unit-test on a bare-metal
machine, it turned out my interpetation was wrong. i.e. INIT_SIGNAL
exit does consume the LAPIC INIT pending event.
(See: https://www.spinics.net/lists/kvm/msg196757.html)

Therefore, fix KVM code to behave as observed on bare-metal.

Fixes: 4b9852f4f389 ("KVM: x86: Fix INIT signal handling in various CPU states")
Reported-by: Nadav Amit <nadav.amit@gmail.com>
Reviewed-by: Mihai Carabas <mihai.carabas@oracle.com>
Reviewed-by: Joao Martins <joao.m.martins@oracle.com>
Signed-off-by: Liran Alon <liran.alon@oracle.com>
---
 arch/x86/kvm/vmx/nested.c | 1 +
 1 file changed, 1 insertion(+)

```
#### [PATCH] KVM: VMX: Fix comment to specify PID.ON instead of PIR.ON
##### From: Liran Alon <liran.alon@oracle.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Liran Alon <liran.alon@oracle.com>
X-Patchwork-Id: 11236901
Return-Path: <SRS0=QoBT=ZD=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 09E8C1515
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 11 Nov 2019 12:25:49 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id DC6CF2196E
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 11 Nov 2019 12:25:48 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=oracle.com header.i=@oracle.com
 header.b="I5FhCS6V"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726903AbfKKMZs (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 11 Nov 2019 07:25:48 -0500
Received: from aserp2120.oracle.com ([141.146.126.78]:38234 "EHLO
        aserp2120.oracle.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726811AbfKKMZr (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 11 Nov 2019 07:25:47 -0500
Received: from pps.filterd (aserp2120.oracle.com [127.0.0.1])
        by aserp2120.oracle.com (8.16.0.27/8.16.0.27) with SMTP id
 xABCOTI5017521;
        Mon, 11 Nov 2019 12:25:40 GMT
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=oracle.com;
 h=from : to : cc :
 subject : date : message-id : mime-version : content-transfer-encoding;
 s=corp-2019-08-05; bh=P0K6cU96LNxUK1pAoLlienSjeAcEI6JVMleECctv77I=;
 b=I5FhCS6VeYZpYGJLChbpahladJdORA4yX29aW2vCzypq9c0Sn4E9+0opWoXU7iXMUT9V
 D2OKPvOeXmtrvNoVkzZSjt7hshc27O5t1WeRdxp6oDUpdRgqzrV1dn+pHc4u1AqsuzJu
 DcndsCUUDiw2qEeN2TgaU0flWYtHPLeyXpTPRLq/7GwMA/T+eU3XKdu0nrb+cCSTXZoV
 hn42ROh7IYR5jJcI/r8CMJk0oK4lYiIiHlQJI2XlLrKbb4sydE95fQXl6HTvyMhVlq9d
 /DlwJmsA+tcjbLGQq+4loyPHt9WZ1PzumAzXd5SLalTUFG5onMvi7xL9NktjOpskSna3 5g==
Received: from userp3020.oracle.com (userp3020.oracle.com [156.151.31.79])
        by aserp2120.oracle.com with ESMTP id 2w5ndpxr5d-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Mon, 11 Nov 2019 12:25:40 +0000
Received: from pps.filterd (userp3020.oracle.com [127.0.0.1])
        by userp3020.oracle.com (8.16.0.27/8.16.0.27) with SMTP id
 xABCNND7057998;
        Mon, 11 Nov 2019 12:25:39 GMT
Received: from aserv0121.oracle.com (aserv0121.oracle.com [141.146.126.235])
        by userp3020.oracle.com with ESMTP id 2w67kkww6n-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Mon, 11 Nov 2019 12:25:39 +0000
Received: from abhmp0011.oracle.com (abhmp0011.oracle.com [141.146.116.17])
        by aserv0121.oracle.com (8.14.4/8.13.8) with ESMTP id xABCPbZm004494;
        Mon, 11 Nov 2019 12:25:37 GMT
Received: from Lirans-MBP.Home (/79.182.207.213)
        by default (Oracle Beehive Gateway v4.0)
        with ESMTP ; Mon, 11 Nov 2019 04:25:37 -0800
From: Liran Alon <liran.alon@oracle.com>
To: pbonzini@redhat.com, rkrcmar@redhat.com, kvm@vger.kernel.org
Cc: sean.j.christopherson@intel.com, jmattson@google.com,
        vkuznets@redhat.com, Liran Alon <liran.alon@oracle.com>,
        Joao Martins <joao.m.martins@oracle.com>
Subject: [PATCH] KVM: VMX: Fix comment to specify PID.ON instead of PIR.ON
Date: Mon, 11 Nov 2019 14:25:25 +0200
Message-Id: <20191111122525.93098-1-liran.alon@oracle.com>
X-Mailer: git-send-email 2.20.1
MIME-Version: 1.0
X-Proofpoint-Virus-Version: vendor=nai engine=6000 definitions=9437
 signatures=668685
X-Proofpoint-Spam-Details: rule=notspam policy=default score=0 suspectscore=0
 malwarescore=0
 phishscore=0 bulkscore=0 spamscore=0 mlxscore=0 mlxlogscore=428
 adultscore=0 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.0.1-1910280000 definitions=main-1911110118
X-Proofpoint-Virus-Version: vendor=nai engine=6000 definitions=9437
 signatures=668685
X-Proofpoint-Spam-Details: rule=notspam policy=default score=0
 priorityscore=1501 malwarescore=0
 suspectscore=0 phishscore=0 bulkscore=0 spamscore=0 clxscore=1015
 lowpriorityscore=0 mlxscore=0 impostorscore=0 mlxlogscore=499 adultscore=0
 classifier=spam adjust=0 reason=mlx scancount=1 engine=8.0.1-1910280000
 definitions=main-1911110118
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The Outstanding Notification (ON) bit is part of the Posted Interrupt
Descriptor (PID) as opposed to the Posted Interrupts Register (PIR).
The latter is a bitmap for pending vectors.

Reviewed-by: Joao Martins <joao.m.martins@oracle.com>
Signed-off-by: Liran Alon <liran.alon@oracle.com>
---
 arch/x86/kvm/vmx/vmx.c | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
#### [PATCH v2 1/3] KVM: VMX: Consider PID.PIR to determine if vCPU has pending interrupts
##### From: Joao Martins <joao.m.martins@oracle.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Joao Martins <joao.m.martins@oracle.com>
X-Patchwork-Id: 11237379
Return-Path: <SRS0=QoBT=ZD=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id C2DB714ED
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 11 Nov 2019 17:21:38 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 9F3DD214DB
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 11 Nov 2019 17:21:38 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=oracle.com header.i=@oracle.com
 header.b="VI7Vbmgn"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726981AbfKKRVf (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 11 Nov 2019 12:21:35 -0500
Received: from userp2120.oracle.com ([156.151.31.85]:40092 "EHLO
        userp2120.oracle.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726915AbfKKRVe (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 11 Nov 2019 12:21:34 -0500
Received: from pps.filterd (userp2120.oracle.com [127.0.0.1])
        by userp2120.oracle.com (8.16.0.27/8.16.0.27) with SMTP id
 xABH9AoR033271;
        Mon, 11 Nov 2019 17:20:28 GMT
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=oracle.com;
 h=from : to : cc :
 subject : date : message-id : in-reply-to : references : mime-version :
 content-type : content-transfer-encoding; s=corp-2019-08-05;
 bh=426E+3tZ3P7XAvx0RdbuUGJqDwgjBVmFHPsj3Cn88VA=;
 b=VI7VbmgnGf6rV6T1muUGly0uwijnTrelnAepUJfbfmWVM0Wh/LXLY1CAyd+KHkLStT3h
 vyxU493FkviyTW/pbcDKIaEjdE2pxoMZjf4AgDys1zuEjinhucrP2uw0e3tO8wvJ5z6M
 auYL6NNvwk8hegrw19LzksU8suXJA5fXGVSd7Ot3fc56kNQ6pYDpRfUpIEewvvj96vXG
 B5IAjfDberXUFtzVobK6MMTr/EjyMfKyHhlCNr2oS74FeP3NQrlwtHJqxFA7h2dFJzT0
 oN6JSbgfUH5C8ZLqfLyUY81ek0S3XDHAj4ZU4w6oFSKjs9b60GmcC2RmXj23eod2Si+q fg==
Received: from aserp3030.oracle.com (aserp3030.oracle.com [141.146.126.71])
        by userp2120.oracle.com with ESMTP id 2w5p3qg2ek-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Mon, 11 Nov 2019 17:20:27 +0000
Received: from pps.filterd (aserp3030.oracle.com [127.0.0.1])
        by aserp3030.oracle.com (8.16.0.27/8.16.0.27) with SMTP id
 xABHEbKm130490;
        Mon, 11 Nov 2019 17:20:27 GMT
Received: from aserv0122.oracle.com (aserv0122.oracle.com [141.146.126.236])
        by aserp3030.oracle.com with ESMTP id 2w6r8jx9wc-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Mon, 11 Nov 2019 17:20:26 +0000
Received: from abhmp0014.oracle.com (abhmp0014.oracle.com [141.146.116.20])
        by aserv0122.oracle.com (8.14.4/8.14.4) with ESMTP id xABHKQx7032399;
        Mon, 11 Nov 2019 17:20:26 GMT
Received: from paddy.uk.oracle.com (/10.175.169.52)
        by default (Oracle Beehive Gateway v4.0)
        with ESMTP ; Mon, 11 Nov 2019 09:20:26 -0800
From: Joao Martins <joao.m.martins@oracle.com>
To: kvm@vger.kernel.org
Cc: Joao Martins <joao.m.martins@oracle.com>, linux-kernel@vger.kernel.org,
 Paolo Bonzini <pbonzini@redhat.com>,
 =?utf-8?b?UmFkaW0gS3LEjW3DocWZ?= <rkrcmar@redhat.com>,
 Sean Christopherson <sean.j.christopherson@intel.com>,
 Vitaly Kuznetsov <vkuznets@redhat.com>, Wanpeng Li <wanpengli@tencent.com>,
 Jim Mattson <jmattson@google.com>, Joerg Roedel <joro@8bytes.org>,
 Liran Alon <liran.alon@oracle.com>, Jag Raman <jag.raman@oracle.com>
Subject: [PATCH v2 1/3] KVM: VMX: Consider PID.PIR to determine if vCPU has
 pending interrupts
Date: Mon, 11 Nov 2019 17:20:10 +0000
Message-Id: <20191111172012.28356-2-joao.m.martins@oracle.com>
X-Mailer: git-send-email 2.11.0
In-Reply-To: <20191111172012.28356-1-joao.m.martins@oracle.com>
References: <20191111172012.28356-1-joao.m.martins@oracle.com>
MIME-Version: 1.0
X-Proofpoint-Virus-Version: vendor=nai engine=6000 definitions=9438
 signatures=668685
X-Proofpoint-Spam-Details: rule=notspam policy=default score=0 suspectscore=1
 malwarescore=0
 phishscore=0 bulkscore=0 spamscore=0 mlxscore=0 mlxlogscore=948
 adultscore=0 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.0.1-1910280000 definitions=main-1911110155
X-Proofpoint-Virus-Version: vendor=nai engine=6000 definitions=9438
 signatures=668685
X-Proofpoint-Spam-Details: rule=notspam policy=default score=0
 priorityscore=1501 malwarescore=0
 suspectscore=1 phishscore=0 bulkscore=0 spamscore=0 clxscore=1015
 lowpriorityscore=0 mlxscore=0 impostorscore=0 mlxlogscore=999 adultscore=0
 classifier=spam adjust=0 reason=mlx scancount=1 engine=8.0.1-1910280000
 definitions=main-1911110155
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Commit 17e433b54393 ("KVM: Fix leak vCPU's VMCS value into other pCPU")
introduced vmx_dy_apicv_has_pending_interrupt() in order to determine
if a vCPU have a pending posted interrupt. This routine is used by
kvm_vcpu_on_spin() when searching for a a new runnable vCPU to schedule
on pCPU instead of a vCPU doing busy loop.

vmx_dy_apicv_has_pending_interrupt() determines if a
vCPU has a pending posted interrupt solely based on PID.ON. However,
when a vCPU is preempted, vmx_vcpu_pi_put() sets PID.SN which cause
raised posted interrupts to only set bit in PID.PIR without setting
PID.ON (and without sending notification vector), as depicted in VT-d
manual section 5.2.3 "Interrupt-Posting Hardware Operation".

Therefore, checking PID.ON is insufficient to determine if a vCPU has
pending posted interrupts and instead we should also check if there is
some bit set on PID.PIR if PID.SN=1.

Fixes: 17e433b54393 ("KVM: Fix leak vCPU's VMCS value into other pCPU")
Reviewed-by: Jagannathan Raman <jag.raman@oracle.com>
Co-developed-by: Liran Alon <liran.alon@oracle.com>
Signed-off-by: Liran Alon <liran.alon@oracle.com>
Signed-off-by: Joao Martins <joao.m.martins@oracle.com>
---
v2:
* Fixed broken Sob Chain;
* Add missing tags;
* Only test PID.PIR if PID.SN=1 and reflect that in commit message last
paragraph;
---
 arch/x86/kvm/vmx/vmx.c | 6 +++++-
 1 file changed, 5 insertions(+), 1 deletion(-)

```
#### [PATCH 1/2] KVM: x86: Evaluate latched_init in KVM_SET_VCPU_EVENTS when vCPU not in SMM
##### From: Liran Alon <liran.alon@oracle.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Liran Alon <liran.alon@oracle.com>
X-Patchwork-Id: 11236719
Return-Path: <SRS0=QoBT=ZD=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 5FA851515
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 11 Nov 2019 09:17:15 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 3E77020818
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 11 Nov 2019 09:17:15 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=oracle.com header.i=@oracle.com
 header.b="pMyTqQtr"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726982AbfKKJRO (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 11 Nov 2019 04:17:14 -0500
Received: from userp2120.oracle.com ([156.151.31.85]:39948 "EHLO
        userp2120.oracle.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726768AbfKKJRO (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 11 Nov 2019 04:17:14 -0500
Received: from pps.filterd (userp2120.oracle.com [127.0.0.1])
        by userp2120.oracle.com (8.16.0.27/8.16.0.27) with SMTP id
 xAB9EKQ0035056;
        Mon, 11 Nov 2019 09:17:07 GMT
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=oracle.com;
 h=from : to : cc :
 subject : date : message-id : in-reply-to : references : mime-version :
 content-transfer-encoding; s=corp-2019-08-05;
 bh=vlYPEE4YvT8Ta4VzqQljjC/3m4BtHqGyWCZYnNL3vxM=;
 b=pMyTqQtrgxrI/OptHwcarmAQlVywVq1mIquh6n/fsCS0BxaOVDfkpgMcZdAYfJqew+ab
 p+muzH2DkWjrDgB1CB+7VVhkNDP7YyUrvqTkjOe2vQb61jhEwQtHG+f5qNw/zpTwMhWN
 TdPmFImAhtfdRY2gI2nQRQ+LNAToONxn+PyLOY85NSpIPkXP6cFBkdEWs7zE8S/engcr
 cX1i1Min+UCyQgI58RHtaow7xayzY2XEWDfm3yhtmlIWtPW0hAsGgE32tVKChTc2vtxY
 pd2L+a+3d1VF/gGKxyVfNhWxwz8IP4EIt1tSyOz0kg8tdvsc0ZlaMO+yOB8pnB1OXy2G oA==
Received: from aserp3020.oracle.com (aserp3020.oracle.com [141.146.126.70])
        by userp2120.oracle.com with ESMTP id 2w5p3qdny9-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Mon, 11 Nov 2019 09:17:07 +0000
Received: from pps.filterd (aserp3020.oracle.com [127.0.0.1])
        by aserp3020.oracle.com (8.16.0.27/8.16.0.27) with SMTP id
 xAB9Dswf174232;
        Mon, 11 Nov 2019 09:17:06 GMT
Received: from aserv0121.oracle.com (aserv0121.oracle.com [141.146.126.235])
        by aserp3020.oracle.com with ESMTP id 2w66yw7ch6-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Mon, 11 Nov 2019 09:17:06 +0000
Received: from abhmp0019.oracle.com (abhmp0019.oracle.com [141.146.116.25])
        by aserv0121.oracle.com (8.14.4/8.13.8) with ESMTP id xAB9H5am013688;
        Mon, 11 Nov 2019 09:17:05 GMT
Received: from localhost.localdomain (/77.139.185.199)
        by default (Oracle Beehive Gateway v4.0)
        with ESMTP ; Mon, 11 Nov 2019 01:17:05 -0800
From: Liran Alon <liran.alon@oracle.com>
To: pbonzini@redhat.com, rkrcmar@redhat.com, kvm@vger.kernel.org
Cc: sean.j.christopherson@intel.com, jmattson@google.com,
        vkuznets@redhat.com, Liran Alon <liran.alon@oracle.com>,
        Mihai Carabas <mihai.carabas@oracle.com>
Subject: [PATCH 1/2] KVM: x86: Evaluate latched_init in KVM_SET_VCPU_EVENTS
 when vCPU not in SMM
Date: Mon, 11 Nov 2019 11:16:39 +0200
Message-Id: <20191111091640.92660-2-liran.alon@oracle.com>
X-Mailer: git-send-email 2.20.1
In-Reply-To: <20191111091640.92660-1-liran.alon@oracle.com>
References: <20191111091640.92660-1-liran.alon@oracle.com>
MIME-Version: 1.0
X-Proofpoint-Virus-Version: vendor=nai engine=6000 definitions=9437
 signatures=668685
X-Proofpoint-Spam-Details: rule=notspam policy=default score=0 suspectscore=0
 malwarescore=0
 phishscore=0 bulkscore=0 spamscore=0 mlxscore=0 mlxlogscore=994
 adultscore=0 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.0.1-1910280000 definitions=main-1911110091
X-Proofpoint-Virus-Version: vendor=nai engine=6000 definitions=9437
 signatures=668685
X-Proofpoint-Spam-Details: rule=notspam policy=default score=0
 priorityscore=1501 malwarescore=0
 suspectscore=0 phishscore=0 bulkscore=0 spamscore=0 clxscore=1015
 lowpriorityscore=0 mlxscore=0 impostorscore=0 mlxlogscore=999 adultscore=0
 classifier=spam adjust=0 reason=mlx scancount=1 engine=8.0.1-1910280000
 definitions=main-1911110092
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Commit 4b9852f4f389 ("KVM: x86: Fix INIT signal handling in various CPU states")
fixed KVM to also latch pending LAPIC INIT event when vCPU is in VMX
operation.

However, current API of KVM_SET_VCPU_EVENTS defines this field as
part of SMM state and only set pending LAPIC INIT event if vCPU is
specified to be in SMM mode (events->smi.smm is set).

Change KVM_SET_VCPU_EVENTS handler to set pending LAPIC INIT event
by latched_init field regardless of if vCPU is in SMM mode or not.

Fixes: 4b9852f4f389 ("KVM: x86: Fix INIT signal handling in various CPU states")
Reviewed-by: Mihai Carabas <mihai.carabas@oracle.com>
Signed-off-by: Liran Alon <liran.alon@oracle.com>
---
 arch/x86/kvm/x86.c | 13 +++++++------
 1 file changed, 7 insertions(+), 6 deletions(-)

```
#### [PULL 1/4] vfio-ccw: Refactor how the traces are built
##### From: Cornelia Huck <cohuck@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Cornelia Huck <cohuck@redhat.com>
X-Patchwork-Id: 11237035
Return-Path: <SRS0=QoBT=ZD=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id BC79214E5
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 11 Nov 2019 13:50:33 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 9B96B2196E
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 11 Nov 2019 13:50:33 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="hQ/JKrWv"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727102AbfKKNud (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 11 Nov 2019 08:50:33 -0500
Received: from us-smtp-2.mimecast.com ([205.139.110.61]:43643 "EHLO
        us-smtp-delivery-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S1726991AbfKKNuc (ORCPT
        <rfc822;kvm@vger.kernel.org>); Mon, 11 Nov 2019 08:50:32 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1573480231;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:content-type:content-type:
         content-transfer-encoding:content-transfer-encoding:
         in-reply-to:in-reply-to:references:references;
        bh=Brq/3pphcVVk4h6b8P5vZKQckG6x+T1r/FKIQE1VPN0=;
        b=hQ/JKrWv8dMzjBKr/T876NmfqSovC7Amo0EzXQTrdJvtbJOqHJCS3ocpsJlsqHhG8VLkYf
        WSw8L1S8qz7Hz0vKiI7+nZC2E4WoUB17v6KXSF/BHpheUU1dXLuKtjyPjoEQLx/ESp2onK
        c/uyF2ATMJemhkd9uLV4cxJG2dLayB4=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-248-DFrBsO1zMlG_HXcW86rFlw-1; Mon, 11 Nov 2019 08:50:27 -0500
Received: from smtp.corp.redhat.com (int-mx06.intmail.prod.int.phx2.redhat.com
 [10.5.11.16])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 3C32B1800D48;
        Mon, 11 Nov 2019 13:50:26 +0000 (UTC)
Received: from localhost (ovpn-117-4.ams2.redhat.com [10.36.117.4])
        by smtp.corp.redhat.com (Postfix) with ESMTPS id CFED45C651;
        Mon, 11 Nov 2019 13:50:25 +0000 (UTC)
From: Cornelia Huck <cohuck@redhat.com>
To: Heiko Carstens <heiko.carstens@de.ibm.com>,
        Vasily Gorbik <gor@linux.ibm.com>,
        Christian Borntraeger <borntraeger@de.ibm.com>
Cc: Eric Farman <farman@linux.ibm.com>,
        Halil Pasic <pasic@linux.ibm.com>, linux-s390@vger.kernel.org,
        kvm@vger.kernel.org, Cornelia Huck <cohuck@redhat.com>
Subject: [PULL 1/4] vfio-ccw: Refactor how the traces are built
Date: Mon, 11 Nov 2019 14:50:16 +0100
Message-Id: <20191111135019.2394-2-cohuck@redhat.com>
In-Reply-To: <20191111135019.2394-1-cohuck@redhat.com>
References: <20191111135019.2394-1-cohuck@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.16
X-MC-Unique: DFrBsO1zMlG_HXcW86rFlw-1
X-Mimecast-Spam-Score: 0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Eric Farman <farman@linux.ibm.com>

Commit 3cd90214b70f ("vfio: ccw: add tracepoints for interesting error
paths") added a quick trace point to determine where a channel program
failed while being processed.  It's a great addition, but adding more
traces to vfio-ccw is more cumbersome than it needs to be.

Let's refactor how this is done, so that additional traces are easier
to add and can exist outside of the FSM if we ever desire.

Signed-off-by: Eric Farman <farman@linux.ibm.com>
Reviewed-by: Cornelia Huck <cohuck@redhat.com>
Message-Id: <20191016142040.14132-2-farman@linux.ibm.com>
Acked-by: Halil Pasic <pasic@linux.ibm.com>
Signed-off-by: Cornelia Huck <cohuck@redhat.com>
---
 drivers/s390/cio/Makefile         |  4 ++--
 drivers/s390/cio/vfio_ccw_cp.h    |  1 +
 drivers/s390/cio/vfio_ccw_fsm.c   |  3 ---
 drivers/s390/cio/vfio_ccw_trace.c | 12 ++++++++++++
 drivers/s390/cio/vfio_ccw_trace.h |  2 ++
 5 files changed, 17 insertions(+), 5 deletions(-)
 create mode 100644 drivers/s390/cio/vfio_ccw_trace.c

```
#### [kvm-unit-tests PATCH v2 1/3] s390x: Fix initial cr0 load comments
##### From: Janosch Frank <frankja@linux.ibm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Janosch Frank <frankja@linux.ibm.com>
X-Patchwork-Id: 11237235
Return-Path: <SRS0=QoBT=ZD=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 8D92716B1
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 11 Nov 2019 15:35:11 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 75FA52184C
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 11 Nov 2019 15:35:11 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726983AbfKKPfK (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 11 Nov 2019 10:35:10 -0500
Received: from mx0b-001b2d01.pphosted.com ([148.163.158.5]:10904 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S1726912AbfKKPfK (ORCPT
        <rfc822;kvm@vger.kernel.org>); Mon, 11 Nov 2019 10:35:10 -0500
Received: from pps.filterd (m0098417.ppops.net [127.0.0.1])
        by mx0a-001b2d01.pphosted.com (8.16.0.27/8.16.0.27) with SMTP id
 xABFXRSx114905
        for <kvm@vger.kernel.org>; Mon, 11 Nov 2019 10:35:08 -0500
Received: from e06smtp01.uk.ibm.com (e06smtp01.uk.ibm.com [195.75.94.97])
        by mx0a-001b2d01.pphosted.com with ESMTP id 2w7987bvuy-1
        (version=TLSv1.2 cipher=AES256-GCM-SHA384 bits=256 verify=NOT)
        for <kvm@vger.kernel.org>; Mon, 11 Nov 2019 10:34:45 -0500
Received: from localhost
        by e06smtp01.uk.ibm.com with IBM ESMTP SMTP Gateway: Authorized Use
 Only! Violators will be prosecuted
        for <kvm@vger.kernel.org> from <frankja@linux.ibm.com>;
        Mon, 11 Nov 2019 15:33:56 -0000
Received: from b06cxnps4075.portsmouth.uk.ibm.com (9.149.109.197)
        by e06smtp01.uk.ibm.com (192.168.101.131) with IBM ESMTP SMTP Gateway:
 Authorized Use Only! Violators will be prosecuted;
        (version=TLSv1/SSLv3 cipher=AES256-GCM-SHA384 bits=256/256)
        Mon, 11 Nov 2019 15:33:53 -0000
Received: from d06av21.portsmouth.uk.ibm.com (d06av21.portsmouth.uk.ibm.com
 [9.149.105.232])
        by b06cxnps4075.portsmouth.uk.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id xABFXrW953412010
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Mon, 11 Nov 2019 15:33:53 GMT
Received: from d06av21.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 05D6952050;
        Mon, 11 Nov 2019 15:33:53 +0000 (GMT)
Received: from localhost.localdomain (unknown [9.145.179.89])
        by d06av21.portsmouth.uk.ibm.com (Postfix) with ESMTP id D659852057;
        Mon, 11 Nov 2019 15:33:51 +0000 (GMT)
From: Janosch Frank <frankja@linux.ibm.com>
To: kvm@vger.kernel.org
Cc: linux-s390@vger.kernel.org, david@redhat.com, thuth@redhat.com
Subject: [kvm-unit-tests PATCH v2 1/3] s390x: Fix initial cr0 load comments
Date: Mon, 11 Nov 2019 10:33:43 -0500
X-Mailer: git-send-email 2.20.1
In-Reply-To: <20191111153345.22505-1-frankja@linux.ibm.com>
References: <20191111153345.22505-1-frankja@linux.ibm.com>
MIME-Version: 1.0
X-TM-AS-GCONF: 00
x-cbid: 19111115-4275-0000-0000-0000037CC698
X-IBM-AV-DETECTION: SAVI=unused REMOTE=unused XFE=unused
x-cbparentid: 19111115-4276-0000-0000-00003890203B
Message-Id: <20191111153345.22505-2-frankja@linux.ibm.com>
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:,,
 definitions=2019-11-11_05:,,
 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 priorityscore=1501
 malwarescore=0 suspectscore=1 phishscore=0 bulkscore=0 spamscore=0
 clxscore=1015 lowpriorityscore=0 mlxscore=0 impostorscore=0
 mlxlogscore=876 adultscore=0 classifier=spam adjust=0 reason=mlx
 scancount=1 engine=8.0.1-1910280000 definitions=main-1911110142
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

We need to load cr0 to have access to all fprs during save and restore
of fprs. Saving conditionally on basis of the CR0 AFP bit would be a
pain.

Signed-off-by: Janosch Frank <frankja@linux.ibm.com>
---
 s390x/cstart64.S | 4 ++--
 1 file changed, 2 insertions(+), 2 deletions(-)

```
#### [kvm-unit-tests PATCH v3 1/2] s390x: sclp: add service call instruction wrapper
##### From: Claudio Imbrenda <imbrenda@linux.ibm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Claudio Imbrenda <imbrenda@linux.ibm.com>
X-Patchwork-Id: 11237375
Return-Path: <SRS0=QoBT=ZD=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id C2D021747
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 11 Nov 2019 17:20:36 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id AB5E221E6F
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 11 Nov 2019 17:20:36 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727077AbfKKRUf (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 11 Nov 2019 12:20:35 -0500
Received: from mx0a-001b2d01.pphosted.com ([148.163.156.1]:50918 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1727059AbfKKRUf (ORCPT
        <rfc822;kvm@vger.kernel.org>); Mon, 11 Nov 2019 12:20:35 -0500
Received: from pps.filterd (m0098404.ppops.net [127.0.0.1])
        by mx0a-001b2d01.pphosted.com (8.16.0.27/8.16.0.27) with SMTP id
 xABHEHC9072874
        for <kvm@vger.kernel.org>; Mon, 11 Nov 2019 12:20:34 -0500
Received: from e06smtp05.uk.ibm.com (e06smtp05.uk.ibm.com [195.75.94.101])
        by mx0a-001b2d01.pphosted.com with ESMTP id 2w7ac8mktc-1
        (version=TLSv1.2 cipher=AES256-GCM-SHA384 bits=256 verify=NOT)
        for <kvm@vger.kernel.org>; Mon, 11 Nov 2019 12:20:34 -0500
Received: from localhost
        by e06smtp05.uk.ibm.com with IBM ESMTP SMTP Gateway: Authorized Use
 Only! Violators will be prosecuted
        for <kvm@vger.kernel.org> from <imbrenda@linux.ibm.com>;
        Mon, 11 Nov 2019 17:20:31 -0000
Received: from b06avi18626390.portsmouth.uk.ibm.com (9.149.26.192)
        by e06smtp05.uk.ibm.com (192.168.101.135) with IBM ESMTP SMTP Gateway:
 Authorized Use Only! Violators will be prosecuted;
        (version=TLSv1/SSLv3 cipher=AES256-GCM-SHA384 bits=256/256)
        Mon, 11 Nov 2019 17:20:29 -0000
Received: from d06av21.portsmouth.uk.ibm.com (d06av21.portsmouth.uk.ibm.com
 [9.149.105.232])
        by b06avi18626390.portsmouth.uk.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id xABHJpM925428420
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Mon, 11 Nov 2019 17:19:52 GMT
Received: from d06av21.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id C4ACB5204F;
        Mon, 11 Nov 2019 17:20:27 +0000 (GMT)
Received: from p-imbrenda.boeblingen.de.ibm.com (unknown [9.152.224.39])
        by d06av21.portsmouth.uk.ibm.com (Postfix) with ESMTPS id 8C6EA52067;
        Mon, 11 Nov 2019 17:20:27 +0000 (GMT)
From: Claudio Imbrenda <imbrenda@linux.ibm.com>
To: kvm@vger.kernel.org
Cc: linux-s390@vger.kernel.org, thuth@redhat.com, david@redhat.com,
        borntraeger@de.ibm.com, frankja@linux.ibm.com
Subject: [kvm-unit-tests PATCH v3 1/2] s390x: sclp: add service call
 instruction wrapper
Date: Mon, 11 Nov 2019 18:20:25 +0100
X-Mailer: git-send-email 2.7.4
In-Reply-To: <1573492826-24589-1-git-send-email-imbrenda@linux.ibm.com>
References: <1573492826-24589-1-git-send-email-imbrenda@linux.ibm.com>
X-TM-AS-GCONF: 00
x-cbid: 19111117-0020-0000-0000-0000038544AD
X-IBM-AV-DETECTION: SAVI=unused REMOTE=unused XFE=unused
x-cbparentid: 19111117-0021-0000-0000-000021DB48A8
Message-Id: <1573492826-24589-2-git-send-email-imbrenda@linux.ibm.com>
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:,,
 definitions=2019-11-11_05:,,
 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 priorityscore=1501
 malwarescore=0 suspectscore=1 phishscore=0 bulkscore=0 spamscore=0
 clxscore=1015 lowpriorityscore=0 mlxscore=0 impostorscore=0
 mlxlogscore=999 adultscore=0 classifier=spam adjust=0 reason=mlx
 scancount=1 engine=8.0.1-1910280000 definitions=main-1911110155
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Add a wrapper for the service call instruction, and use it for SCLP
interactions instead of using inline assembly everywhere.

Signed-off-by: Claudio Imbrenda <imbrenda@linux.ibm.com>
Reviewed-by: David Hildenbrand <david@redhat.com>
Reviewed-by: Thomas Huth <thuth@redhat.com>
Reviewed-by: Janosch Frank <frankja@linux.ibm.com>
---
 lib/s390x/asm/arch_def.h | 13 +++++++++++++
 lib/s390x/sclp.c         |  7 +------
 2 files changed, 14 insertions(+), 6 deletions(-)

```
#### [PATCH] VFIO/VMBUS: Add VFIO VMBUS driver support
##### From: lantianyu1986@gmail.com

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Tianyu Lan <lantianyu1986@gmail.com>
X-Patchwork-Id: 11236705
Return-Path: <SRS0=QoBT=ZD=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 36AD716B1
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 11 Nov 2019 08:45:22 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id EB889214DB
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 11 Nov 2019 08:45:21 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=gmail.com header.i=@gmail.com
 header.b="EbVbNdoi"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726983AbfKKIpS (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 11 Nov 2019 03:45:18 -0500
Received: from mail-pf1-f196.google.com ([209.85.210.196]:40342 "EHLO
        mail-pf1-f196.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726871AbfKKIpR (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 11 Nov 2019 03:45:17 -0500
Received: by mail-pf1-f196.google.com with SMTP id r4so10223324pfl.7;
        Mon, 11 Nov 2019 00:45:17 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=from:to:cc:subject:date:message-id;
        bh=aoNsXrqb/4m251g26a9JnAvsvd+FQZ6xqhju3XhJrIw=;
        b=EbVbNdoiiY9078yEneNR4t9k1ZvvZhAdnTZydsMhAA10u8k8uzLa0sTOTisqlZB2Wl
         EDKSuORWt+WQ+R52MKozTXNks+gAeMByfRUZxxNVvT8vpyh9oDEYAKluFbfaoPnL6FcM
         aSXUspT/jAFEMhDt3BYjzv7EOL/KM1g16N7DxkBwMvqVDGTDne/1YvkbML5Hs+HgNtp4
         eXTTVbvYt9uzVitQ886V+DemCEZH2w5vPlOJvk1L7lZNTai2YZ4KmVRIsqps9XBHsbrX
         BUsbsn2FEdnmusRSHqKl7jHuLRAZ1bXC+iMHsJ5AaZxgBQsq4BfsE8dWJLopBVwT3wYF
         xigg==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id;
        bh=aoNsXrqb/4m251g26a9JnAvsvd+FQZ6xqhju3XhJrIw=;
        b=JlsoOzGNpkZlW0GHzuFb4SWmTU7sSU3UUyZujGq0+k8fJHMTuZllxZYc7naFP1GeQ+
         azHs9jHGjjPeGVrZAqX4EhEGwTqSejFOuGGrJenb1fjznBdOYjyDTPMXxs3sDGgl2qKX
         ev4me43UMrA+I7jrPkNTQedzlRikSqoffjVtnEzRjUOtHak59r7urz/1wnipCBdigd80
         IHt1Af/3lAQr9fvGJ2sPpORXvgtApyTCNudtWWm8V9PBrRg9FsznfRTm55dqFwwSkKbs
         UN2R0yDb1SlgVIul5kp/Co0nZIZQgfDIYNcxC2nN64+XR3c9l8HFyGgH09koA9qLljsj
         F1vw==
X-Gm-Message-State: APjAAAWOYt8YrDIXEzpcNWxE7Rzp7/yLsV1gLClqTnStQNUX8UWuGpwY
        bbdPRLictLKFmKhUzlqT7cY=
X-Google-Smtp-Source: 
 APXvYqxfF87VnZCZ3h3mE1UM/Hs6U59rWnYNg+94zrR6b9Dw2eLKBjZXKlWQ4dSNddoUonF53yaScA==
X-Received: by 2002:a63:2c3:: with SMTP id 186mr27460715pgc.166.1573461916560;
        Mon, 11 Nov 2019 00:45:16 -0800 (PST)
Received: from dell.guest.corp.microsoft.com ([167.220.255.69])
        by smtp.googlemail.com with ESMTPSA id
 z16sm15642656pge.55.2019.11.11.00.45.11
        (version=TLS1_2 cipher=ECDHE-RSA-CHACHA20-POLY1305 bits=256/256);
        Mon, 11 Nov 2019 00:45:15 -0800 (PST)
From: lantianyu1986@gmail.com
X-Google-Original-From: Tianyu.Lan@microsoft.com
To: alex.williamson@redhat.com, cohuck@redhat.com, kys@microsoft.com,
        haiyangz@microsoft.com, sthemmin@microsoft.com, sashal@kernel.org,
        mchehab+samsung@kernel.org, davem@davemloft.net,
        gregkh@linuxfoundation.org, robh@kernel.org,
        Jonathan.Cameron@huawei.com, paulmck@linux.ibm.com,
        michael.h.kelley@microsoft.com
Cc: Tianyu Lan <Tianyu.Lan@microsoft.com>,
        linux-kernel@vger.kernel.org, kvm@vger.kernel.org,
        linux-hyperv@vger.kernel.org, vkuznets@redhat.com
Subject: [PATCH] VFIO/VMBUS: Add VFIO VMBUS driver support
Date: Mon, 11 Nov 2019 16:45:07 +0800
Message-Id: <20191111084507.9286-1-Tianyu.Lan@microsoft.com>
X-Mailer: git-send-email 2.14.5
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Tianyu Lan <Tianyu.Lan@microsoft.com>

This patch is to add VFIO VMBUS driver support in order to expose
VMBUS devices to user space drivers(Reference Hyper-V UIO driver).
DPDK now has netvsc PMD driver support and it may get VMBUS resources
via VFIO interface with new driver support.

So far, Hyper-V doesn't provide virtual IOMMU support and so this
driver needs to be used with VFIO noiommu mode.

Current netvsc PMD driver in DPDK doesn't have IRQ mode support.
This driver version skips IRQ control part and adds later when
there is a real request.

Signed-off-by: Tianyu Lan <Tianyu.Lan@microsoft.com>
---
 MAINTAINERS                     |   1 +
 drivers/vfio/Kconfig            |   1 +
 drivers/vfio/Makefile           |   1 +
 drivers/vfio/vmbus/Kconfig      |   9 +
 drivers/vfio/vmbus/vfio_vmbus.c | 407 ++++++++++++++++++++++++++++++++++++++++
 include/uapi/linux/vfio.h       |  12 ++
 6 files changed, 431 insertions(+)
 create mode 100644 drivers/vfio/vmbus/Kconfig
 create mode 100644 drivers/vfio/vmbus/vfio_vmbus.c

```
#### [PATCH] x86: vmx: Verify L2 modification to L1 LAPIC TPR works when L0 use TPR threshold
##### From: Liran Alon <liran.alon@oracle.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Liran Alon <liran.alon@oracle.com>
X-Patchwork-Id: 11236951
Return-Path: <SRS0=QoBT=ZD=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 0016F13BD
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 11 Nov 2019 12:37:50 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id C86E521872
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 11 Nov 2019 12:37:50 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=oracle.com header.i=@oracle.com
 header.b="WgPY+vHQ"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726834AbfKKMht (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 11 Nov 2019 07:37:49 -0500
Received: from userp2130.oracle.com ([156.151.31.86]:52528 "EHLO
        userp2130.oracle.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726810AbfKKMht (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 11 Nov 2019 07:37:49 -0500
Received: from pps.filterd (userp2130.oracle.com [127.0.0.1])
        by userp2130.oracle.com (8.16.0.27/8.16.0.27) with SMTP id
 xABCXsab036981;
        Mon, 11 Nov 2019 12:37:42 GMT
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=oracle.com;
 h=from : to : cc :
 subject : date : message-id : mime-version : content-transfer-encoding;
 s=corp-2019-08-05; bh=A/h2k5pYXiiPYsO4+8nBEWU9QH45SNQYUUhYsaX3vTc=;
 b=WgPY+vHQcc5CLbM/z3bPEdrmme9JjhinVfwCWb9IbNp5nhf1TiY5JdWEO/CF3v/F1L0v
 2hcy1LduioKaG3BZiqnwMqMMQEry3vF7+hcJH8XWdQPDx6VpvYhdAMO6VG2Ef5zrBkM6
 ij3lC01aVy5QAWa4CoXS4mQa52IqwXFgvLSMdS09B5DMyqUN3htCfJKbY5hgX19UkSA1
 /f223V9y/rOM8wARYNXXD8NFv8bnkGjH6EFW9AuwEfo7W13SqIpzeIfcPHNk3TMl0BYT
 GRn+aZJThAGPDFKMrcR9DNCw6WFqnI58Awt4GkrPT55TpFQjZ00vXht09yUml7xH70qZ AQ==
Received: from aserp3020.oracle.com (aserp3020.oracle.com [141.146.126.70])
        by userp2130.oracle.com with ESMTP id 2w5mvtetp7-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Mon, 11 Nov 2019 12:37:42 +0000
Received: from pps.filterd (aserp3020.oracle.com [127.0.0.1])
        by aserp3020.oracle.com (8.16.0.27/8.16.0.27) with SMTP id
 xABCXe9x026203;
        Mon, 11 Nov 2019 12:37:41 GMT
Received: from aserv0121.oracle.com (aserv0121.oracle.com [141.146.126.235])
        by aserp3020.oracle.com with ESMTP id 2w66yx989y-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Mon, 11 Nov 2019 12:37:41 +0000
Received: from abhmp0008.oracle.com (abhmp0008.oracle.com [141.146.116.14])
        by aserv0121.oracle.com (8.14.4/8.13.8) with ESMTP id xABCbejE010714;
        Mon, 11 Nov 2019 12:37:40 GMT
Received: from Lirans-MBP.Home (/79.182.207.213)
        by default (Oracle Beehive Gateway v4.0)
        with ESMTP ; Mon, 11 Nov 2019 12:37:40 +0000
From: Liran Alon <liran.alon@oracle.com>
To: pbonzini@redhat.com, rkrcmar@redhat.com, kvm@vger.kernel.org
Cc: sean.j.christopherson@intel.com, jmattson@google.com,
        vkuznets@redhat.com, Liran Alon <liran.alon@oracle.com>,
        Joao Martins <joao.m.martins@oracle.com>
Subject: [PATCH] x86: vmx: Verify L2 modification to L1 LAPIC TPR works when
 L0 use TPR threshold
Date: Mon, 11 Nov 2019 14:37:26 +0200
Message-Id: <20191111123726.93391-1-liran.alon@oracle.com>
X-Mailer: git-send-email 2.20.1
MIME-Version: 1.0
X-Proofpoint-Virus-Version: vendor=nai engine=6000 definitions=9437
 signatures=668685
X-Proofpoint-Spam-Details: rule=notspam policy=default score=0 suspectscore=0
 malwarescore=0
 phishscore=0 bulkscore=0 spamscore=0 mlxscore=0 mlxlogscore=794
 adultscore=0 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.0.1-1910280000 definitions=main-1911110120
X-Proofpoint-Virus-Version: vendor=nai engine=6000 definitions=9437
 signatures=668685
X-Proofpoint-Spam-Details: rule=notspam policy=default score=0
 priorityscore=1501 malwarescore=0
 suspectscore=0 phishscore=0 bulkscore=0 spamscore=0 clxscore=1015
 lowpriorityscore=0 mlxscore=0 impostorscore=0 mlxlogscore=866 adultscore=0
 classifier=spam adjust=0 reason=mlx scancount=1 engine=8.0.1-1910280000
 definitions=main-1911110120
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Test aims to verify that the issue fixed by commit ("KVM: nVMX: Update
vmcs01 TPR_THRESHOLD if L2 changed L1 TPR") is indeed fixed.

Test performs the following steps:
1) Disable interrupts.
2) Raise TPR to high value and queue a pending interrupt in LAPIC by
issueing a self-IPI with lower priority.
3) Launch guest such that it is provided with passthrough access to
LAPIC.
4) Inside guest, disable interrupts and lower TPR to 0 and then exit guest.
5) Back on host, verify that indeed TPR was set to 0 and that enabling
interrupts indeed deliever pending interrupt in LAPIC.

Without above mentioned commit in L0, step (2) will cause L0 to raise
TPR-threshold to self-IPI vector priority and step (4) will *not* change
vmcs01 TPR-threshold to 0. This will result in infinite loop of VMExits
on TPR_BELOW_THRESHOLD every time L0 attempts to enter L1. Which will
cause test to hang and eventually fail on timeout.

Reviewed-by: Joao Martins <joao.m.martins@oracle.com>
Signed-off-by: Liran Alon <liran.alon@oracle.com>
---
 x86/unittests.cfg |  9 ++++++++-
 x86/vmx_tests.c   | 43 +++++++++++++++++++++++++++++++++++++++++++
 2 files changed, 51 insertions(+), 1 deletion(-)

```
#### [PATCH] x86: vmx: Verify pending LAPIC INIT event consume when exit on VMX_INIT
##### From: Liran Alon <liran.alon@oracle.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 8bit
X-Patchwork-Submitter: Liran Alon <liran.alon@oracle.com>
X-Patchwork-Id: 11236961
Return-Path: <SRS0=QoBT=ZD=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id C2AEA14E5
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 11 Nov 2019 12:42:50 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 963F12067B
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 11 Nov 2019 12:42:50 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=oracle.com header.i=@oracle.com
 header.b="AaQTgIqU"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726877AbfKKMmt (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 11 Nov 2019 07:42:49 -0500
Received: from userp2130.oracle.com ([156.151.31.86]:58172 "EHLO
        userp2130.oracle.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726843AbfKKMmt (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 11 Nov 2019 07:42:49 -0500
Received: from pps.filterd (userp2130.oracle.com [127.0.0.1])
        by userp2130.oracle.com (8.16.0.27/8.16.0.27) with SMTP id
 xABCdMVC041136;
        Mon, 11 Nov 2019 12:42:39 GMT
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=oracle.com;
 h=from : to : cc :
 subject : date : message-id : mime-version : content-type :
 content-transfer-encoding; s=corp-2019-08-05;
 bh=YqBAOEZMh3KGZ+O3/laMDeTAk2++y7gLpfILzynibmU=;
 b=AaQTgIqUO5mtblH9H/2BiWbHlIb2nAKpP8WccRStD2sqM3RFACjsbJalZhdiujBEYcKb
 b/TgFz26qQRO9xcVY7wp7WzNGmWDLcdAkgGU4tOjQ0Bw0jXXBbTxFyoEG017YcIo+h5T
 zey4AF4eKatNCKnmjQYlm2h1SUAi52ToALwiDMI+Fbi9eJmrWAs79j3zmhqPbYJmos/s
 YvymxYt2lkuNJtkYIVfRF95Tp4fm4PXntRWvl/yc5H4wEhR+DdQTZXxmuHjdTab7xrjx
 Dmz2keRlqzYBb93VcEpDO3lJk5o2pLAOgRnXOk73yBbczu7DCJWlv7w3koFjXTwiU7OW ng==
Received: from aserp3020.oracle.com (aserp3020.oracle.com [141.146.126.70])
        by userp2130.oracle.com with ESMTP id 2w5mvteubd-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Mon, 11 Nov 2019 12:42:39 +0000
Received: from pps.filterd (aserp3020.oracle.com [127.0.0.1])
        by aserp3020.oracle.com (8.16.0.27/8.16.0.27) with SMTP id
 xABCcriQ036332;
        Mon, 11 Nov 2019 12:40:38 GMT
Received: from userv0121.oracle.com (userv0121.oracle.com [156.151.31.72])
        by aserp3020.oracle.com with ESMTP id 2w66yx9mgm-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Mon, 11 Nov 2019 12:40:38 +0000
Received: from abhmp0007.oracle.com (abhmp0007.oracle.com [141.146.116.13])
        by userv0121.oracle.com (8.14.4/8.13.8) with ESMTP id xABCeamf031449;
        Mon, 11 Nov 2019 12:40:36 GMT
Received: from Lirans-MBP.Home (/79.182.207.213)
        by default (Oracle Beehive Gateway v4.0)
        with ESMTP ; Mon, 11 Nov 2019 04:40:36 -0800
From: Liran Alon <liran.alon@oracle.com>
To: pbonzini@redhat.com, rkrcmar@redhat.com, kvm@vger.kernel.org
Cc: sean.j.christopherson@intel.com, jmattson@google.com,
        vkuznets@redhat.com, Liran Alon <liran.alon@oracle.com>,
        Nadav Amit <nadav.amit@gmail.com>,
        Mihai Carabas <mihai.carabas@oracle.com>
Subject: [PATCH] x86: vmx: Verify pending LAPIC INIT event consume when exit
 on VMX_INIT
Date: Mon, 11 Nov 2019 14:40:23 +0200
Message-Id: <20191111124023.93449-1-liran.alon@oracle.com>
X-Mailer: git-send-email 2.20.1
MIME-Version: 1.0
X-Proofpoint-Virus-Version: vendor=nai engine=6000 definitions=9437
 signatures=668685
X-Proofpoint-Spam-Details: rule=notspam policy=default score=0 suspectscore=0
 malwarescore=0
 phishscore=0 bulkscore=0 spamscore=0 mlxscore=0 mlxlogscore=999
 adultscore=0 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.0.1-1910280000 definitions=main-1911110121
X-Proofpoint-Virus-Version: vendor=nai engine=6000 definitions=9437
 signatures=668685
X-Proofpoint-Spam-Details: rule=notspam policy=default score=0
 priorityscore=1501 malwarescore=0
 suspectscore=0 phishscore=0 bulkscore=0 spamscore=0 clxscore=1015
 lowpriorityscore=0 mlxscore=0 impostorscore=0 mlxlogscore=999 adultscore=0
 classifier=spam adjust=0 reason=mlx scancount=1 engine=8.0.1-1910280000
 definitions=main-1911110121
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Intel SDM section 25.2 OTHER CAUSES OF VM EXITS specifies the following
on INIT signals: "Such exits do not modify register state or clear pending
events as they would outside of VMX operation."

When commit 48adfb0f2e8e ("x86: vmx: Test INIT processing during various CPU VMX states")
was applied, I interepted above Intel SDM statement such that
VMX_INIT exit don’t consume the pending LAPIC INIT event.

However, when Nadav Amit run the unit-test on a bare-metal
machine, it turned out my interpetation was wrong. i.e. VMX_INIT
exit does consume the pending LAPIC INIT event.
(See: https://www.spinics.net/lists/kvm/msg196757.html)

Therefore, fix unit-test code to behave as observed on bare-metal.
i.e. End unit-test with the following steps:
1) Exit VMX operation and verify it still continues to run properly
as pending LAPIC INIT event should have been already consumed by
VMX_INIT exit.
2) Re-enter VMX operation and send another INIT signal to keep it
blocked until exit from VMX operation.
3) Exit VMX operation and verify that pending LAPIC INIT signal
is processed when exiting VMX operation.

Fixes: 48adfb0f2e8e ("x86: vmx: Test INIT processing during various CPU VMX states")
Reported-by: Nadav Amit <nadav.amit@gmail.com>
Reviewed-by: Mihai Carabas <mihai.carabas@oracle.com>
Signed-off-by: Liran Alon <liran.alon@oracle.com>
---
 x86/vmx_tests.c | 45 +++++++++++++++++++++++++++++++++++++++++++--
 1 file changed, 43 insertions(+), 2 deletions(-)

```
