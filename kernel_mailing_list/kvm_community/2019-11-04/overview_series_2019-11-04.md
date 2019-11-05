#### [PATCH 1/2] KVM: Fix NULL-ptr defer after kvm_create_vm fails
##### From: Wanpeng Li <kernellwp@gmail.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Wanpeng Li <kernellwp@gmail.com>
X-Patchwork-Id: 11224967
Return-Path: <SRS0=wa+l=Y4=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id EB2BD1599
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon,  4 Nov 2019 06:28:17 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id CA086222C6
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon,  4 Nov 2019 06:28:17 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=gmail.com header.i=@gmail.com
 header.b="bi7os8Mn"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728332AbfKDG2K (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 4 Nov 2019 01:28:10 -0500
Received: from mail-pg1-f196.google.com ([209.85.215.196]:40432 "EHLO
        mail-pg1-f196.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1727911AbfKDG2J (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 4 Nov 2019 01:28:09 -0500
Received: by mail-pg1-f196.google.com with SMTP id 15so10602674pgt.7;
        Sun, 03 Nov 2019 22:28:07 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=from:to:cc:subject:date:message-id;
        bh=ZYR0xt4j6M9ghT6gn2+jBhsiyfXvuB7wHMizn4V6mhs=;
        b=bi7os8MneiCUSdHm3w8wp6PYtlt3SIcJpGjVPC3e9PC3Q7uf1JJ/E2TQSeIP+gqb3N
         D3FMWZI+HlqfshmITItNDVbMPqlniVZRuFlIt/FhUHWSDA7zXLRJ5btK6I7DiKQqerjW
         kPgBxmJSEx8H8XwSlpqIzbZ0Kkij1iTwhHr9xrzJVbImrHUpc10HxAQfctJ5ZIwv8Tp0
         RrdynQhshXrRMJbsFEoJxc9Qih15/k9oYheyVLasu0NeSUNATDb8AYGRrgSfKNlg7E6o
         GQDJESuDTlAgRmrlTCYupV6HbZ/BuhHTKPmKgbrT+Zyg5txGL2Ha/y/MpQVkBwWobKuz
         xfxg==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id;
        bh=ZYR0xt4j6M9ghT6gn2+jBhsiyfXvuB7wHMizn4V6mhs=;
        b=e7Xj4HOCJtISrSryKgwFTvlYew/iwyn/HgOXWBMRZSQns0VVPc1hQ4fGBcYGpE1cL+
         +CETdfVF435rfwckyM8QjxZaZufait46EpN5CzQOXWdPGvtzWSBHnwcpSgYU71dR8xlt
         lPHtA3b3J2wrepZbAbhN20jCtbT50c9fvaubrFYIyGknePUlrwVwrfXm+28Djbs4sxvV
         5YvAOJmfq2NPWNx9VWNBfAFHrZK+a+1mBa/YvBYTFW5y+MHdqvVvHt7pyD0AzCSLS8er
         nJM5qKkrm8rzw4xkY8dabyAm77hsnkmuyclvPs/dd052pNoU4+mlcWKT7MNQSyqnNlG3
         Zd4Q==
X-Gm-Message-State: APjAAAXV73YGyhHkyfGXQXPIrmLyrXf/59DDyzCOtIy3H7RGp7zoM6sk
        vr9RZDXP5OYg8jNxUB2oNRaD/kCP
X-Google-Smtp-Source: 
 APXvYqxkJtkIRCkBSJNATceZJHKNaDtsagBi74sUOjSxtwBqNhWjB7hIbN0o0A/qXdoLJzjQSsqBFg==
X-Received: by 2002:a17:90a:bb0a:: with SMTP id
 u10mr33656628pjr.14.1572848887315;
        Sun, 03 Nov 2019 22:28:07 -0800 (PST)
Received: from localhost.localdomain ([203.205.141.123])
        by smtp.googlemail.com with ESMTPSA id
 z7sm7810505pgk.10.2019.11.03.22.28.04
        (version=TLS1_2 cipher=ECDHE-RSA-AES128-SHA bits=128/128);
        Sun, 03 Nov 2019 22:28:06 -0800 (PST)
From: Wanpeng Li <kernellwp@gmail.com>
X-Google-Original-From: Wanpeng Li <wanpengli@tencent.com>
To: linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Cc: Paolo Bonzini <pbonzini@redhat.com>,
 =?utf-8?b?UmFkaW0gS3LEjW3DocWZ?= <rkrcmar@redhat.com>,
 Sean Christopherson <sean.j.christopherson@intel.com>,
 Vitaly Kuznetsov <vkuznets@redhat.com>, Wanpeng Li <wanpengli@tencent.com>,
 Jim Mattson <jmattson@google.com>, Joerg Roedel <joro@8bytes.org>
Subject: [PATCH 1/2] KVM: Fix NULL-ptr defer after kvm_create_vm fails
Date: Mon,  4 Nov 2019 14:27:58 +0800
Message-Id: <1572848879-21011-1-git-send-email-wanpengli@tencent.com>
X-Mailer: git-send-email 2.7.4
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Wanpeng Li <wanpengli@tencent.com>

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

syz repro: https://syzkaller.appspot.com/x/repro.syz?x=13509b84e00000

Reported-by: syzbot+89a8060879fa0bd2db4f@syzkaller.appspotmail.com
Fixes: 9121923c457d ("kvm: Allocate memslots and buses before calling kvm_arch_init_vm") 
Cc: Jim Mattson <jmattson@google.com>
Signed-off-by: Wanpeng Li <wanpengli@tencent.com>
---
 virt/kvm/kvm_main.c | 1 +
 1 file changed, 1 insertion(+)

```
#### [PATCH v21 1/6] hw/arm/virt: Introduce a RAS machine option
##### From: Xiang Zheng <zhengxiang9@huawei.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Xiang Zheng <zhengxiang9@huawei.com>
X-Patchwork-Id: 11225693
Return-Path: <SRS0=wa+l=Y4=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id C06E616B1
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon,  4 Nov 2019 12:16:33 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id A2ECC2184C
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon,  4 Nov 2019 12:16:33 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728902AbfKDMQc (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 4 Nov 2019 07:16:32 -0500
Received: from szxga04-in.huawei.com ([45.249.212.190]:5700 "EHLO huawei.com"
        rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org with ESMTP
        id S1727913AbfKDMQc (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 4 Nov 2019 07:16:32 -0500
Received: from DGGEMS403-HUB.china.huawei.com (unknown [172.30.72.59])
        by Forcepoint Email with ESMTP id 908ACFC3B13359B9CC1A;
        Mon,  4 Nov 2019 20:16:30 +0800 (CST)
Received: from HGHY4Z004218071.china.huawei.com (10.133.224.57) by
 DGGEMS403-HUB.china.huawei.com (10.3.19.203) with Microsoft SMTP Server id
 14.3.439.0; Mon, 4 Nov 2019 20:16:21 +0800
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
Subject: [PATCH v21 1/6] hw/arm/virt: Introduce a RAS machine option
Date: Mon, 4 Nov 2019 20:14:53 +0800
Message-ID: <20191104121458.29208-2-zhengxiang9@huawei.com>
X-Mailer: git-send-email 2.15.1.windows.2
In-Reply-To: <20191104121458.29208-1-zhengxiang9@huawei.com>
References: <20191104121458.29208-1-zhengxiang9@huawei.com>
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
#### [PATCH 01/13] KVM: monolithic: x86: remove kvm.ko
##### From: Andrea Arcangeli <aarcange@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Andrea Arcangeli <aarcange@redhat.com>
X-Patchwork-Id: 11226741
Return-Path: <SRS0=wa+l=Y4=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 985071747
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon,  4 Nov 2019 23:01:13 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 77A77214D9
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon,  4 Nov 2019 23:01:13 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="PSddy8ZY"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1730037AbfKDXAN (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 4 Nov 2019 18:00:13 -0500
Received: from us-smtp-delivery-1.mimecast.com ([205.139.110.120]:45959 "EHLO
        us-smtp-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org
        with ESMTP id S1729194AbfKDXAM (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 4 Nov 2019 18:00:12 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1572908411;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:content-type:content-type:
         content-transfer-encoding:content-transfer-encoding:
         in-reply-to:in-reply-to:references:references;
        bh=tktmbgMbA44XbKL0C1wWEcJpxBYyzYw3dy09GJTCB3c=;
        b=PSddy8ZYP+HimJ1X3wd/oKMDnkjtie2fCftkQYUOcLvtJ2mnGgMgz5LD+gebNr2hyt4ipQ
        xMl2H6Hcw1BWxAwsbnSBMMVrpXmOdcj1ZJ3/MBzXYfPAICerzayqerPFyxim7yUjNqcAiE
        jp01MnofLUpy2qhCEfGD5+z32FttK30=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-248-8Y_kaONzMEuyO5vOv_3xzg-1; Mon, 04 Nov 2019 18:00:08 -0500
Received: from smtp.corp.redhat.com (int-mx07.intmail.prod.int.phx2.redhat.com
 [10.5.11.22])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 44F0E1800DFB;
        Mon,  4 Nov 2019 23:00:07 +0000 (UTC)
Received: from mail (ovpn-121-157.rdu2.redhat.com [10.10.121.157])
        by smtp.corp.redhat.com (Postfix) with ESMTPS id B0E1B1001B34;
        Mon,  4 Nov 2019 23:00:02 +0000 (UTC)
From: Andrea Arcangeli <aarcange@redhat.com>
To: kvm@vger.kernel.org, linux-kernel@vger.kernel.org
Cc: Paolo Bonzini <pbonzini@redhat.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Sean Christopherson <sean.j.christopherson@intel.com>
Subject: [PATCH 01/13] KVM: monolithic: x86: remove kvm.ko
Date: Mon,  4 Nov 2019 17:59:49 -0500
Message-Id: <20191104230001.27774-2-aarcange@redhat.com>
In-Reply-To: <20191104230001.27774-1-aarcange@redhat.com>
References: <20191104230001.27774-1-aarcange@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.84 on 10.5.11.22
X-MC-Unique: 8Y_kaONzMEuyO5vOv_3xzg-1
X-Mimecast-Spam-Score: 0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This is the first commit of a patch series that aims to replace the
modular kvm.ko kernel module with a monolithic kvm-intel/kvm-amd
model. This change has the only possible cons of wasting some disk
space in /lib/modules/. The pros are that it saves CPUS and some minor
iTLB and RAM which are more scarse resources than disk space.

The pointer to function virtual template model cannot provide any
runtime benefit because kvm-intel and kvm-amd can't be loaded at the
same time.

This removes kvm.ko and it links and duplicates all kvm.ko objects to
both kvm-amd and kvm-intel.

Linking both vmx and svm into the kernel at the same time isn't
possible anymore or the kvm_x86/kvm_x86_pmu external function names
would collide.

Explanation of Kbuild from Paolo Bonzini follows:

===
The left side of the "||" ensures that, if KVM=m, you can only choose
module build for both KVM_INTEL and KVM_AMD.  Having just "depends on
KVM" would allow a pre-existing .config to choose the now-invalid
combination

        CONFIG_KVM=y
        CONFIG_KVM_INTEL=y
        CONFIG_KVM_AMD=y

The right side of the "||" part is just for documentation, to avoid
that a selected symbol does not satisfy its dependencies.
====

Signed-off-by: Andrea Arcangeli <aarcange@redhat.com>
---
 arch/x86/kvm/Kconfig  | 30 ++++++++++++++++++++++++++----
 arch/x86/kvm/Makefile |  5 ++---
 2 files changed, 28 insertions(+), 7 deletions(-)

```
#### [kvm-unit-tests PATCH] alloc: Add more memalign asserts
##### From: Janosch Frank <frankja@linux.ibm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Janosch Frank <frankja@linux.ibm.com>
X-Patchwork-Id: 11225295
Return-Path: <SRS0=wa+l=Y4=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 491A5913
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon,  4 Nov 2019 09:20:17 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 30F9D222D3
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon,  4 Nov 2019 09:20:17 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727499AbfKDJUQ (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 4 Nov 2019 04:20:16 -0500
Received: from mx0a-001b2d01.pphosted.com ([148.163.156.1]:32022 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1726364AbfKDJUQ (ORCPT
        <rfc822;kvm@vger.kernel.org>); Mon, 4 Nov 2019 04:20:16 -0500
Received: from pps.filterd (m0098409.ppops.net [127.0.0.1])
        by mx0a-001b2d01.pphosted.com (8.16.0.27/8.16.0.27) with SMTP id
 xA49IP4k090981
        for <kvm@vger.kernel.org>; Mon, 4 Nov 2019 04:20:15 -0500
Received: from e06smtp04.uk.ibm.com (e06smtp04.uk.ibm.com [195.75.94.100])
        by mx0a-001b2d01.pphosted.com with ESMTP id 2w2f99cdx5-1
        (version=TLSv1.2 cipher=AES256-GCM-SHA384 bits=256 verify=NOT)
        for <kvm@vger.kernel.org>; Mon, 04 Nov 2019 04:20:14 -0500
Received: from localhost
        by e06smtp04.uk.ibm.com with IBM ESMTP SMTP Gateway: Authorized Use
 Only! Violators will be prosecuted
        for <kvm@vger.kernel.org> from <frankja@linux.ibm.com>;
        Mon, 4 Nov 2019 09:20:12 -0000
Received: from b06avi18626390.portsmouth.uk.ibm.com (9.149.26.192)
        by e06smtp04.uk.ibm.com (192.168.101.134) with IBM ESMTP SMTP Gateway:
 Authorized Use Only! Violators will be prosecuted;
        (version=TLSv1/SSLv3 cipher=AES256-GCM-SHA384 bits=256/256)
        Mon, 4 Nov 2019 09:20:09 -0000
Received: from d06av25.portsmouth.uk.ibm.com (d06av25.portsmouth.uk.ibm.com
 [9.149.105.61])
        by b06avi18626390.portsmouth.uk.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id xA49JYeP26083686
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Mon, 4 Nov 2019 09:19:34 GMT
Received: from d06av25.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 9FB1B11C05B;
        Mon,  4 Nov 2019 09:20:08 +0000 (GMT)
Received: from d06av25.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 62F5A11C052;
        Mon,  4 Nov 2019 09:20:07 +0000 (GMT)
Received: from localhost.localdomain (unknown [9.145.70.20])
        by d06av25.portsmouth.uk.ibm.com (Postfix) with ESMTP;
        Mon,  4 Nov 2019 09:20:07 +0000 (GMT)
From: Janosch Frank <frankja@linux.ibm.com>
To: kvm@vger.kernel.org
Cc: thuth@redhat.com, david@redhat.com, pbonzini@redhat.com
Subject: [kvm-unit-tests PATCH] alloc: Add more memalign asserts
Date: Mon,  4 Nov 2019 04:20:55 -0500
X-Mailer: git-send-email 2.20.1
MIME-Version: 1.0
X-TM-AS-GCONF: 00
x-cbid: 19110409-0016-0000-0000-000002C07ACE
X-IBM-AV-DETECTION: SAVI=unused REMOTE=unused XFE=unused
x-cbparentid: 19110409-0017-0000-0000-00003321E9BF
Message-Id: <20191104092055.5679-1-frankja@linux.ibm.com>
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:,,
 definitions=2019-11-04_06:,,
 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 priorityscore=1501
 malwarescore=0 suspectscore=1 phishscore=0 bulkscore=0 spamscore=0
 clxscore=1015 lowpriorityscore=0 mlxscore=0 impostorscore=0
 mlxlogscore=984 adultscore=0 classifier=spam adjust=0 reason=mlx
 scancount=1 engine=8.0.1-1908290000 definitions=main-1911040092
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Let's test for size and alignment in memalign to catch invalid input
data. Also we need to test for NULL after calling the memalign
function of the registered alloc operations.

Signed-off-by: Janosch Frank <frankja@linux.ibm.com>
Reviewed-by: David Hildenbrand <david@redhat.com>
---

Tested only under s390, tests under other architectures are highly
appreciated.

---
 lib/alloc.c | 3 +++
 1 file changed, 3 insertions(+)

```
#### [kvm-unit-tests PATCH] s390x: Use loop to save and restore fprs
##### From: Janosch Frank <frankja@linux.ibm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Janosch Frank <frankja@linux.ibm.com>
X-Patchwork-Id: 11225171
Return-Path: <SRS0=wa+l=Y4=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id B902113A4
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon,  4 Nov 2019 08:56:38 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id A0D8E222CA
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon,  4 Nov 2019 08:56:38 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727553AbfKDI4h (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 4 Nov 2019 03:56:37 -0500
Received: from mx0b-001b2d01.pphosted.com ([148.163.158.5]:39232 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S1726100AbfKDI4h (ORCPT
        <rfc822;kvm@vger.kernel.org>); Mon, 4 Nov 2019 03:56:37 -0500
Received: from pps.filterd (m0098413.ppops.net [127.0.0.1])
        by mx0b-001b2d01.pphosted.com (8.16.0.27/8.16.0.27) with SMTP id
 xA48qcrx063700
        for <kvm@vger.kernel.org>; Mon, 4 Nov 2019 03:56:36 -0500
Received: from e06smtp07.uk.ibm.com (e06smtp07.uk.ibm.com [195.75.94.103])
        by mx0b-001b2d01.pphosted.com with ESMTP id 2w2eapmtck-1
        (version=TLSv1.2 cipher=AES256-GCM-SHA384 bits=256 verify=NOT)
        for <kvm@vger.kernel.org>; Mon, 04 Nov 2019 03:56:25 -0500
Received: from localhost
        by e06smtp07.uk.ibm.com with IBM ESMTP SMTP Gateway: Authorized Use
 Only! Violators will be prosecuted
        for <kvm@vger.kernel.org> from <frankja@linux.ibm.com>;
        Mon, 4 Nov 2019 08:54:44 -0000
Received: from b06avi18878370.portsmouth.uk.ibm.com (9.149.26.194)
        by e06smtp07.uk.ibm.com (192.168.101.137) with IBM ESMTP SMTP Gateway:
 Authorized Use Only! Violators will be prosecuted;
        (version=TLSv1/SSLv3 cipher=AES256-GCM-SHA384 bits=256/256)
        Mon, 4 Nov 2019 08:54:41 -0000
Received: from d06av22.portsmouth.uk.ibm.com (d06av22.portsmouth.uk.ibm.com
 [9.149.105.58])
        by b06avi18878370.portsmouth.uk.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id xA48sedA47514050
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Mon, 4 Nov 2019 08:54:41 GMT
Received: from d06av22.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id DDDB14C040;
        Mon,  4 Nov 2019 08:54:40 +0000 (GMT)
Received: from d06av22.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id A65B34C044;
        Mon,  4 Nov 2019 08:54:39 +0000 (GMT)
Received: from localhost.localdomain (unknown [9.145.70.20])
        by d06av22.portsmouth.uk.ibm.com (Postfix) with ESMTP;
        Mon,  4 Nov 2019 08:54:39 +0000 (GMT)
From: Janosch Frank <frankja@linux.ibm.com>
To: kvm@vger.kernel.org
Cc: linux-s390@vger.kernel.org, thuth@redhat.com, david@redhat.com,
        pmorel@linux.ibm.com
Subject: [kvm-unit-tests PATCH] s390x: Use loop to save and restore fprs
Date: Mon,  4 Nov 2019 03:55:33 -0500
X-Mailer: git-send-email 2.20.1
MIME-Version: 1.0
X-TM-AS-GCONF: 00
x-cbid: 19110408-0028-0000-0000-000003B26ED6
X-IBM-AV-DETECTION: SAVI=unused REMOTE=unused XFE=unused
x-cbparentid: 19110408-0029-0000-0000-00002474C153
Message-Id: <20191104085533.2892-1-frankja@linux.ibm.com>
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:,,
 definitions=2019-11-04_06:,,
 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 priorityscore=1501
 malwarescore=0 suspectscore=1 phishscore=0 bulkscore=0 spamscore=0
 clxscore=1015 lowpriorityscore=0 mlxscore=0 impostorscore=0
 mlxlogscore=582 adultscore=0 classifier=spam adjust=0 reason=mlx
 scancount=1 engine=8.0.1-1908290000 definitions=main-1911040088
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Let's save some lines in the assembly by using a loop to save and
restore the fprs.

Signed-off-by: Janosch Frank <frankja@linux.ibm.com>
---
 s390x/cstart64.S | 38 ++++++--------------------------------
 1 file changed, 6 insertions(+), 32 deletions(-)

```
#### [kvm-unit-tests PATCH v2] alloc: Add memalign error checks
##### From: Janosch Frank <frankja@linux.ibm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Janosch Frank <frankja@linux.ibm.com>
X-Patchwork-Id: 11225343
Return-Path: <SRS0=wa+l=Y4=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id ECCC614E5
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon,  4 Nov 2019 10:29:27 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id D3CBD21D81
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon,  4 Nov 2019 10:29:27 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728437AbfKDK30 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 4 Nov 2019 05:29:26 -0500
Received: from mx0b-001b2d01.pphosted.com ([148.163.158.5]:5810 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S1726364AbfKDK30 (ORCPT
        <rfc822;kvm@vger.kernel.org>); Mon, 4 Nov 2019 05:29:26 -0500
Received: from pps.filterd (m0098413.ppops.net [127.0.0.1])
        by mx0b-001b2d01.pphosted.com (8.16.0.27/8.16.0.27) with SMTP id
 xA49xYiO086778
        for <kvm@vger.kernel.org>; Mon, 4 Nov 2019 05:29:25 -0500
Received: from e06smtp03.uk.ibm.com (e06smtp03.uk.ibm.com [195.75.94.99])
        by mx0b-001b2d01.pphosted.com with ESMTP id 2w2hubrs04-1
        (version=TLSv1.2 cipher=AES256-GCM-SHA384 bits=256 verify=NOT)
        for <kvm@vger.kernel.org>; Mon, 04 Nov 2019 05:29:24 -0500
Received: from localhost
        by e06smtp03.uk.ibm.com with IBM ESMTP SMTP Gateway: Authorized Use
 Only! Violators will be prosecuted
        for <kvm@vger.kernel.org> from <frankja@linux.ibm.com>;
        Mon, 4 Nov 2019 10:29:22 -0000
Received: from b06avi18626390.portsmouth.uk.ibm.com (9.149.26.192)
        by e06smtp03.uk.ibm.com (192.168.101.133) with IBM ESMTP SMTP Gateway:
 Authorized Use Only! Violators will be prosecuted;
        (version=TLSv1/SSLv3 cipher=AES256-GCM-SHA384 bits=256/256)
        Mon, 4 Nov 2019 10:29:20 -0000
Received: from d06av26.portsmouth.uk.ibm.com (d06av26.portsmouth.uk.ibm.com
 [9.149.105.62])
        by b06avi18626390.portsmouth.uk.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id xA4ASiML40698146
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Mon, 4 Nov 2019 10:28:45 GMT
Received: from d06av26.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 988D4AE04D;
        Mon,  4 Nov 2019 10:29:19 +0000 (GMT)
Received: from d06av26.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 9EC54AE059;
        Mon,  4 Nov 2019 10:29:18 +0000 (GMT)
Received: from localhost.localdomain (unknown [9.145.70.20])
        by d06av26.portsmouth.uk.ibm.com (Postfix) with ESMTP;
        Mon,  4 Nov 2019 10:29:18 +0000 (GMT)
From: Janosch Frank <frankja@linux.ibm.com>
To: kvm@vger.kernel.org
Cc: thuth@redhat.com, david@redhat.com, pbonzini@redhat.com
Subject: [kvm-unit-tests PATCH v2] alloc: Add memalign error checks
Date: Mon,  4 Nov 2019 05:29:16 -0500
X-Mailer: git-send-email 2.20.1
MIME-Version: 1.0
X-TM-AS-GCONF: 00
x-cbid: 19110410-0012-0000-0000-000003607A50
X-IBM-AV-DETECTION: SAVI=unused REMOTE=unused XFE=unused
x-cbparentid: 19110410-0013-0000-0000-0000219BCE50
Message-Id: <20191104102916.10554-1-frankja@linux.ibm.com>
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:,,
 definitions=2019-11-04_06:,,
 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 priorityscore=1501
 malwarescore=0 suspectscore=1 phishscore=0 bulkscore=0 spamscore=0
 clxscore=1015 lowpriorityscore=0 mlxscore=0 impostorscore=0
 mlxlogscore=999 adultscore=0 classifier=spam adjust=0 reason=mlx
 scancount=1 engine=8.0.1-1908290000 definitions=main-1911040100
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Let's test for size and alignment in memalign to catch invalid input
data. Also we need to test for NULL after calling the memalign
function of the registered alloc operations.

Signed-off-by: Janosch Frank <frankja@linux.ibm.com>
Reviewed-by: David Hildenbrand <david@redhat.com>
Reviewed-by: David Hildenbrand <david@redhat.com>
---
 lib/alloc.c | 3 +++
 1 file changed, 3 insertions(+)

```
#### [PATCH V7 1/6] mdev: class id support
##### From: Jason Wang <jasowang@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Jason Wang <jasowang@redhat.com>
X-Patchwork-Id: 11225731
Return-Path: <SRS0=wa+l=Y4=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 460C713A4
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon,  4 Nov 2019 12:43:16 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 1050121D7D
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon,  4 Nov 2019 12:43:16 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="aRjZjkt+"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728923AbfKDMnJ (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 4 Nov 2019 07:43:09 -0500
Received: from us-smtp-delivery-1.mimecast.com ([205.139.110.120]:52470 "EHLO
        us-smtp-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org
        with ESMTP id S1727782AbfKDMnJ (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 4 Nov 2019 07:43:09 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1572871387;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:content-type:content-type:
         content-transfer-encoding:content-transfer-encoding:
         in-reply-to:in-reply-to:references:references;
        bh=j3uX4xKUPpnTCQ7S+H5OVBiI//DbCpSXZrAOsfut9UQ=;
        b=aRjZjkt+RtPAZP3H++M03wAzBCWTwvg0oEWkdiVheWZoTPUybZo4MycAt92fU8VL60WuGu
        Ijg//Zsy6A0qsT6kXvJ73TK23LZQHVHJAZ6mLVg0cgoacjcXGubNxbMjPG6ETPIe7ZfgDV
        m/wO/vZc+hH6aWSPNbxae3e7Dv+RO7I=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-28-2G__RSVRPBKBWJJih5i-Fw-1; Mon, 04 Nov 2019 07:43:04 -0500
Received: from smtp.corp.redhat.com (int-mx02.intmail.prod.int.phx2.redhat.com
 [10.5.11.12])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 67699800C73;
        Mon,  4 Nov 2019 12:43:00 +0000 (UTC)
Received: from jason-ThinkPad-X1-Carbon-6th.redhat.com
 (ovpn-12-65.pek2.redhat.com [10.72.12.65])
        by smtp.corp.redhat.com (Postfix) with ESMTP id EA45B60CD0;
        Mon,  4 Nov 2019 12:41:26 +0000 (UTC)
From: Jason Wang <jasowang@redhat.com>
To: kvm@vger.kernel.org, linux-s390@vger.kernel.org,
        linux-kernel@vger.kernel.org, dri-devel@lists.freedesktop.org,
        intel-gfx@lists.freedesktop.org,
        intel-gvt-dev@lists.freedesktop.org, kwankhede@nvidia.com,
        alex.williamson@redhat.com, mst@redhat.com, tiwei.bie@intel.com
Cc: virtualization@lists.linux-foundation.org, netdev@vger.kernel.org,
        cohuck@redhat.com, maxime.coquelin@redhat.com,
        cunming.liang@intel.com, zhihong.wang@intel.com,
        rob.miller@broadcom.com, xiao.w.wang@intel.com,
        haotian.wang@sifive.com, zhenyuw@linux.intel.com,
        zhi.a.wang@intel.com, jani.nikula@linux.intel.com,
        joonas.lahtinen@linux.intel.com, rodrigo.vivi@intel.com,
        airlied@linux.ie, daniel@ffwll.ch, farman@linux.ibm.com,
        pasic@linux.ibm.com, sebott@linux.ibm.com, oberpar@linux.ibm.com,
        heiko.carstens@de.ibm.com, gor@linux.ibm.com,
        borntraeger@de.ibm.com, akrowiak@linux.ibm.com,
        freude@linux.ibm.com, lingshan.zhu@intel.com, idos@mellanox.com,
        eperezma@redhat.com, lulu@redhat.com, parav@mellanox.com,
        christophe.de.dinechin@gmail.com, kevin.tian@intel.com,
        stefanha@redhat.com, Jason Wang <jasowang@redhat.com>
Subject: [PATCH V7 1/6] mdev: class id support
Date: Mon,  4 Nov 2019 20:39:47 +0800
Message-Id: <20191104123952.17276-2-jasowang@redhat.com>
In-Reply-To: <20191104123952.17276-1-jasowang@redhat.com>
References: <20191104123952.17276-1-jasowang@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.12
X-MC-Unique: 2G__RSVRPBKBWJJih5i-Fw-1
X-Mimecast-Spam-Score: 0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Mdev bus only supports vfio driver right now, so it doesn't implement
match method. But in the future, we may add drivers other than vfio,
the first driver could be virtio-mdev. This means we need to add
device class id support in bus match method to pair the mdev device
and mdev driver correctly.

So this patch adds id_table to mdev_driver and class_id for mdev
device with the match method for mdev bus.

Reviewed-by: Parav Pandit <parav@mellanox.com>
Signed-off-by: Jason Wang <jasowang@redhat.com>
---
 .../driver-api/vfio-mediated-device.rst       |  5 ++++
 drivers/gpu/drm/i915/gvt/kvmgt.c              |  1 +
 drivers/s390/cio/vfio_ccw_ops.c               |  1 +
 drivers/s390/crypto/vfio_ap_ops.c             |  1 +
 drivers/vfio/mdev/mdev_core.c                 | 16 ++++++++++++
 drivers/vfio/mdev/mdev_driver.c               | 25 +++++++++++++++++++
 drivers/vfio/mdev/mdev_private.h              |  1 +
 drivers/vfio/mdev/vfio_mdev.c                 |  6 +++++
 include/linux/mdev.h                          |  8 ++++++
 include/linux/mod_devicetable.h               |  8 ++++++
 samples/vfio-mdev/mbochs.c                    |  1 +
 samples/vfio-mdev/mdpy.c                      |  1 +
 samples/vfio-mdev/mtty.c                      |  1 +
 13 files changed, 75 insertions(+)

```
#### [PATCH v2] x86/Kconfig: Rename UMIP config parameterThread-Topic: [PATCH v2] x86/Kconfig: Rename UMIP config parameter
##### From: "Moger, Babu" <Babu.Moger@amd.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: "Moger, Babu" <babu.moger@amd.com>
X-Patchwork-Id: 11226525
Return-Path: <SRS0=wa+l=Y4=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 6CBFF112B
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon,  4 Nov 2019 20:51:01 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 35C85214E0
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon,  4 Nov 2019 20:51:01 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=amdcloud.onmicrosoft.com
 header.i=@amdcloud.onmicrosoft.com header.b="LeNdSKGZ"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729194AbfKDUu5 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 4 Nov 2019 15:50:57 -0500
Received: from mail-eopbgr730056.outbound.protection.outlook.com
 ([40.107.73.56]:40965
        "EHLO NAM05-DM3-obe.outbound.protection.outlook.com"
        rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org with ESMTP
        id S1728709AbfKDUu5 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 4 Nov 2019 15:50:57 -0500
ARC-Seal: i=1; a=rsa-sha256; s=arcselector9901; d=microsoft.com; cv=none;
 b=HLAhDeJq8Jm9Z8PaIiHrwlNEdl5v+l69tIZzjxyU/RYk7IYEj0B9XwgTUnQZVdVwg7V+MhmKD8wBkvkq23bsCR7TCsJPg0H6dGejzwRSSZFNjreGxH9gz27cEgf4R/z5CB5AimIJVmEzSPTHxfvTHAxTNAUAxHXPsbgvHhqhkKqAhvJ0eNlQ/0W0IcksP37id5TfJv8iQEGzWf9lEYTzDYllmlQ67tXLOp38sH3FdkaJJpC+0E3E3h4ojsGc2Yo7IlXMWdxTcrVoC15Yw3jhcIr7mr4uL7zwszKUxHkIGLMFShaHk8ZddKvs7rU/Ntg6udT8KINmdAw9FF7wmxkang==
ARC-Message-Signature: i=1; a=rsa-sha256; c=relaxed/relaxed; d=microsoft.com;
 s=arcselector9901;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=+hIm65fFHkWsdG3pG0gTYIsbsd41pXbC++QaJQTsW2E=;
 b=Aqd1Q15dp9yXCCkTabanD6oKWifJIJzLiwQBMUYG3QAePSjAqbbqV8ozUbOfYgCyppOWfUgIG7mF5dGDhuZFu1+T8WKJitjEwTqGq0jJwLNpWvy6ZAO22DCKvyUlmk0gytxXk99pyJSzF/xt2pqMVWRli64LcQVapVJRhqg38t6z6jGhcyJSpAEaEQp7y8N5DJnFJAcJEPgriFA2JEo/HOBxRhKGG68JbOcVMm1fk6cmYm1FXTDubFYuXbWYjLuXGsSDdCEHXHljKcN14SiiKUmAcF1JKwrZGEi3Hw4IO9QGoQ/EA3oxQ0BQe98k2nG4kpASEdATeFbFgjgBeof4dA==
ARC-Authentication-Results: i=1; mx.microsoft.com 1; spf=pass
 smtp.mailfrom=amd.com; dmarc=pass action=none header.from=amd.com; dkim=pass
 header.d=amd.com; arc=none
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
 d=amdcloud.onmicrosoft.com; s=selector2-amdcloud-onmicrosoft-com;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=+hIm65fFHkWsdG3pG0gTYIsbsd41pXbC++QaJQTsW2E=;
 b=LeNdSKGZa8/37w23wtS4c8deSAetSreZzWc3dl3afupg5M/vTySgIUZnx//yTBIx3umnEGpEqyvwLr0YyuAsfVztpBLuqCR6uFvB4/ugn4xvLu+vy0z5VKdsiqOCDCrq0cKEN5A4DemiiqA07UaQOvKqTDy059kID4A2bL5aFKk=
Received: from DM5PR12MB2471.namprd12.prod.outlook.com (52.132.141.138) by
 DM5PR12MB1387.namprd12.prod.outlook.com (10.168.233.16) with Microsoft SMTP
 Server (version=TLS1_2, cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id
 15.20.2387.31; Mon, 4 Nov 2019 20:50:51 +0000
Received: from DM5PR12MB2471.namprd12.prod.outlook.com
 ([fe80::c5a3:6a2e:8699:1999]) by DM5PR12MB2471.namprd12.prod.outlook.com
 ([fe80::c5a3:6a2e:8699:1999%6]) with mapi id 15.20.2408.024; Mon, 4 Nov 2019
 20:50:51 +0000
From: "Moger, Babu" <Babu.Moger@amd.com>
To: "tglx@linutronix.de" <tglx@linutronix.de>,
        "mingo@redhat.com" <mingo@redhat.com>,
        "bp@alien8.de" <bp@alien8.de>, "hpa@zytor.com" <hpa@zytor.com>,
        "pbonzini@redhat.com" <pbonzini@redhat.com>,
        "rkrcmar@redhat.com" <rkrcmar@redhat.com>,
        "sean.j.christopherson@intel.com" <sean.j.christopherson@intel.com>,
        "vkuznets@redhat.com" <vkuznets@redhat.com>,
        "wanpengli@tencent.com" <wanpengli@tencent.com>,
        "jmattson@google.com" <jmattson@google.com>
CC: "x86@kernel.org" <x86@kernel.org>,
        "joro@8bytes.org" <joro@8bytes.org>,
        "Moger, Babu" <Babu.Moger@amd.com>,
        "luto@kernel.org" <luto@kernel.org>,
        "zohar@linux.ibm.com" <zohar@linux.ibm.com>,
        "yamada.masahiro@socionext.com" <yamada.masahiro@socionext.com>,
        "nayna@linux.ibm.com" <nayna@linux.ibm.com>,
        "linux-kernel@vger.kernel.org" <linux-kernel@vger.kernel.org>,
        "kvm@vger.kernel.org" <kvm@vger.kernel.org>
Subject: [PATCH v2] x86/Kconfig: Rename UMIP config parameter
Thread-Topic: [PATCH v2] x86/Kconfig: Rename UMIP config parameter
Thread-Index: AQHVk1GLQf345nN80kenPnepADNDDg==
Date: Mon, 4 Nov 2019 20:50:51 +0000
Message-ID: <157290058655.2477.5193340480187879024.stgit@naples-babu.amd.com>
Accept-Language: en-US
Content-Language: en-US
X-MS-Has-Attach: 
X-MS-TNEF-Correlator: 
x-clientproxiedby: SN6PR15CA0011.namprd15.prod.outlook.com
 (2603:10b6:805:16::24) To DM5PR12MB2471.namprd12.prod.outlook.com
 (2603:10b6:4:b5::10)
authentication-results: spf=none (sender IP is )
 smtp.mailfrom=Babu.Moger@amd.com;
x-ms-exchange-messagesentrepresentingtype: 1
x-originating-ip: [165.204.78.2]
x-ms-publictraffictype: Email
x-ms-office365-filtering-ht: Tenant
x-ms-office365-filtering-correlation-id: 29a8e5a2-2388-4dc8-80fd-08d76168ada3
x-ms-traffictypediagnostic: DM5PR12MB1387:
x-ms-exchange-transport-forked: True
x-microsoft-antispam-prvs: 
 <DM5PR12MB138727A0EDE23AEFB7E9D139957F0@DM5PR12MB1387.namprd12.prod.outlook.com>
x-ms-oob-tlc-oobclassifiers: OLM:6108;
x-forefront-prvs: 0211965D06
x-forefront-antispam-report: 
 SFV:NSPM;SFS:(10009020)(4636009)(366004)(346002)(376002)(396003)(39860400002)(136003)(189003)(199004)(305945005)(26005)(54906003)(316002)(66066001)(66476007)(2201001)(6436002)(103116003)(14444005)(71200400001)(5660300002)(3846002)(6116002)(4326008)(256004)(2906002)(7416002)(386003)(6506007)(102836004)(14454004)(8676002)(8936002)(81156014)(81166006)(25786009)(6486002)(7736002)(66446008)(66946007)(64756008)(66556008)(86362001)(6512007)(71190400001)(110136005)(478600001)(2501003)(476003)(186003)(99286004)(52116002)(486006)(921003)(1121003);DIR:OUT;SFP:1101;SCL:1;SRVR:DM5PR12MB1387;H:DM5PR12MB2471.namprd12.prod.outlook.com;FPR:;SPF:None;LANG:en;PTR:InfoNoRecords;MX:1;A:1;
received-spf: None (protection.outlook.com: amd.com does not designate
 permitted sender hosts)
x-ms-exchange-senderadcheck: 1
x-microsoft-antispam: BCL:0;
x-microsoft-antispam-message-info: 
 3qcjTzdD+dE2Ay5b8StNudg/5fshAwQxWF9WPwps4P9Lc0T2Kw8ZOnPKr9KCr/V1MhkNzLTBTo6fVy5MzgcwTSuExaIbllr61PfvdUGBk6AU8gIs2AfstTy+mMUt2r6GibgUkZyliwiPacvSCmAsrWPzYVyC9Vv6mOFIJhc/AMFMeWZ8q+9PTVZz7ROdyZtrQZPrWkoKA1dfkTznxr3nkhjiKASDakEGX8s6eMy/9Npu2fFRcHqqZb8wxWtNdoN+yS409lynG7NGYFKzuKZ38ppTnncF1GvMUBa7rZMIe6/z8PRQM2e87Z7t3dnZ8rOQUeqpIJPjMfmda50OCeUqqWTcNqyiPHct4KfNWXWE82pMxpYs4bb3glmALYDMWoTDdFqz62Dxcc9GoMhHQYkI8uK6r/b6WSKe3LC3JlM1PRUKi3UtjWbxQgB+khT2Sa5R
Content-ID: <F516C8705528BB4A97430686265FF341@namprd12.prod.outlook.com>
MIME-Version: 1.0
X-OriginatorOrg: amd.com
X-MS-Exchange-CrossTenant-Network-Message-Id: 
 29a8e5a2-2388-4dc8-80fd-08d76168ada3
X-MS-Exchange-CrossTenant-originalarrivaltime: 04 Nov 2019 20:50:51.6030
 (UTC)
X-MS-Exchange-CrossTenant-fromentityheader: Hosted
X-MS-Exchange-CrossTenant-id: 3dd8961f-e488-4e60-8e11-a82d994e183d
X-MS-Exchange-CrossTenant-mailboxtype: HOSTED
X-MS-Exchange-CrossTenant-userprincipalname: 
 smQOp3TKevWys9tbIIgK5X5kOHHxfd+AM+oXx31rDgKu1XWYTCdilJDagIDlN22p
X-MS-Exchange-Transport-CrossTenantHeadersStamped: DM5PR12MB1387
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

AMD 2nd generation EPYC processors support the UMIP (User-Mode
Instruction Prevention) feature. So, rename X86_INTEL_UMIP to
generic X86_UMIP and modify the text to cover both Intel and AMD.

Signed-off-by: Babu Moger <babu.moger@amd.com>
---
v2:
  Learned that for the hardware that support UMIP, we dont need to
  emulate. Removed the emulation related code and just submitting
  the config changes.

 arch/x86/Kconfig                         |    8 ++++----
 arch/x86/include/asm/disabled-features.h |    2 +-
 arch/x86/include/asm/umip.h              |    4 ++--
 arch/x86/kernel/Makefile                 |    2 +-
 4 files changed, 8 insertions(+), 8 deletions(-)

```
