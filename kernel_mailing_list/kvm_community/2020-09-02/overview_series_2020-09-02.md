#### [PATCH v6 1/7] KVM: x86: Deflect unknown MSR accesses to user space
##### From: Alexander Graf <graf@amazon.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Alexander Graf <graf@amazon.com>
X-Patchwork-Id: 11750637
Return-Path: <SRS0=tgfV=CL=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 4875E109B
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed,  2 Sep 2020 13:26:36 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 256D7207D3
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed,  2 Sep 2020 13:26:36 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=amazon.com header.i=@amazon.com
 header.b="MrhzV9kU"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727064AbgIBNAS (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 2 Sep 2020 09:00:18 -0400
Received: from smtp-fw-4101.amazon.com ([72.21.198.25]:52245 "EHLO
        smtp-fw-4101.amazon.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726948AbgIBNAJ (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 2 Sep 2020 09:00:09 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
  d=amazon.com; i=@amazon.com; q=dns/txt; s=amazon201209;
  t=1599051606; x=1630587606;
  h=from:to:cc:subject:date:message-id:in-reply-to:
   references:mime-version:content-transfer-encoding;
  bh=sVr8f22MaDe/QCgG5Z/gJcf5Swrutmw8uwmX7xhUdug=;
  b=MrhzV9kUEU5kEwIB5unt4OVA2o7ALbc7kxPIDYPbzeiR88WCEq77ZLK6
   v3770NTl15mc4Rp8HNsD+t5CE46Im4ufsfg2w3ZM2I87CWzYzVknDYLml
   p2d43ojQBy6LQixvH9esWQriwIC4zcpTWc1wn5w6kyd4fcLElVHgXb8YF
   Y=;
X-IronPort-AV: E=Sophos;i="5.76,383,1592870400";
   d="scan'208";a="51634662"
Received: from iad12-co-svc-p1-lb1-vlan3.amazon.com (HELO
 email-inbound-relay-2b-4ff6265a.us-west-2.amazon.com) ([10.43.8.6])
  by smtp-border-fw-out-4101.iad4.amazon.com with ESMTP;
 02 Sep 2020 12:59:51 +0000
Received: from EX13MTAUWC002.ant.amazon.com
 (pdx4-ws-svc-p6-lb7-vlan3.pdx.amazon.com [10.170.41.166])
        by email-inbound-relay-2b-4ff6265a.us-west-2.amazon.com (Postfix) with
 ESMTPS id 170EEA013F;
        Wed,  2 Sep 2020 12:59:50 +0000 (UTC)
Received: from EX13D20UWC002.ant.amazon.com (10.43.162.163) by
 EX13MTAUWC002.ant.amazon.com (10.43.162.240) with Microsoft SMTP Server (TLS)
 id 15.0.1497.2; Wed, 2 Sep 2020 12:59:49 +0000
Received: from u79c5a0a55de558.ant.amazon.com (10.43.161.145) by
 EX13D20UWC002.ant.amazon.com (10.43.162.163) with Microsoft SMTP Server (TLS)
 id 15.0.1497.2; Wed, 2 Sep 2020 12:59:46 +0000
From: Alexander Graf <graf@amazon.com>
To: Paolo Bonzini <pbonzini@redhat.com>
CC: Jonathan Corbet <corbet@lwn.net>,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        "Joerg Roedel" <joro@8bytes.org>,
        KarimAllah Raslan <karahmed@amazon.de>,
        Aaron Lewis <aaronlewis@google.com>,
        Dan Carpenter <dan.carpenter@oracle.com>,
        <kvm@vger.kernel.org>, <linux-doc@vger.kernel.org>,
        <linux-kernel@vger.kernel.org>
Subject: [PATCH v6 1/7] KVM: x86: Deflect unknown MSR accesses to user space
Date: Wed, 2 Sep 2020 14:59:29 +0200
Message-ID: <20200902125935.20646-2-graf@amazon.com>
X-Mailer: git-send-email 2.28.0.394.ge197136389
In-Reply-To: <20200902125935.20646-1-graf@amazon.com>
References: <20200902125935.20646-1-graf@amazon.com>
MIME-Version: 1.0
X-Originating-IP: [10.43.161.145]
X-ClientProxiedBy: EX13D08UWB004.ant.amazon.com (10.43.161.232) To
 EX13D20UWC002.ant.amazon.com (10.43.162.163)
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

MSRs are weird. Some of them are normal control registers, such as EFER.
Some however are registers that really are model specific, not very
interesting to virtualization workloads, and not performance critical.
Others again are really just windows into package configuration.

Out of these MSRs, only the first category is necessary to implement in
kernel space. Rarely accessed MSRs, MSRs that should be fine tunes against
certain CPU models and MSRs that contain information on the package level
are much better suited for user space to process. However, over time we have
accumulated a lot of MSRs that are not the first category, but still handled
by in-kernel KVM code.

This patch adds a generic interface to handle WRMSR and RDMSR from user
space. With this, any future MSR that is part of the latter categories can
be handled in user space.

Furthermore, it allows us to replace the existing "ignore_msrs" logic with
something that applies per-VM rather than on the full system. That way you
can run productive VMs in parallel to experimental ones where you don't care
about proper MSR handling.

Signed-off-by: Alexander Graf <graf@amazon.com>
Reviewed-by: Jim Mattson <jmattson@google.com>
---

v1 -> v2:

  - s/ETRAP_TO_USER_SPACE/ENOENT/g
  - deflect all #GP injection events to user space, not just unknown MSRs.
    That was we can also deflect allowlist errors later
  - fix emulator case

v2 -> v3:

  - return r if r == X86EMUL_IO_NEEDED
  - s/KVM_EXIT_RDMSR/KVM_EXIT_X86_RDMSR/g
  - s/KVM_EXIT_WRMSR/KVM_EXIT_X86_WRMSR/g
  - Use complete_userspace_io logic instead of reply field
  - Simplify trapping code

v3 -> v4:

  - Mention exit reasons in re-inter mandatory section of API documentation
  - Clear padding bytes
  - Generalize get/set deflect functions
  - Remove redundant pending_user_msr field

v5 -> v6:

  - Introduce exit reason mask to allow for future expansion and filtering
  - s/emul_to_vcpu(ctxt)/vcpu/
---
 Documentation/virt/kvm/api.rst  |  73 +++++++++++++++++++-
 arch/x86/include/asm/kvm_host.h |   3 +
 arch/x86/kvm/emulate.c          |  18 ++++-
 arch/x86/kvm/x86.c              | 119 ++++++++++++++++++++++++++++++--
 include/trace/events/kvm.h      |   2 +-
 include/uapi/linux/kvm.h        |  12 ++++
 6 files changed, 218 insertions(+), 9 deletions(-)

```
#### [PATCH 59/63] kvm: Rename KVM_STATE to KVM_ACCEL
##### From: Eduardo Habkost <ehabkost@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Eduardo Habkost <ehabkost@redhat.com>
X-Patchwork-Id: 11751909
Return-Path: <SRS0=tgfV=CL=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 6A194109A
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed,  2 Sep 2020 22:45:55 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 4AB6120767
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed,  2 Sep 2020 22:45:55 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="aVbTwAk/"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726674AbgIBWpw (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 2 Sep 2020 18:45:52 -0400
Received: from us-smtp-2.mimecast.com ([207.211.31.81]:23576 "EHLO
        us-smtp-delivery-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S1726247AbgIBWpu (ORCPT
        <rfc822;kvm@vger.kernel.org>); Wed, 2 Sep 2020 18:45:50 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1599086748;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding:
         in-reply-to:in-reply-to:references:references;
        bh=/ktoQfh7Azf87EbiJtqzsLJ4A8BhkUu1bCw5VGpaiJo=;
        b=aVbTwAk/CwQksDiyZlh2Im4hz47ttKXzRjvGxJqlsetcDAmRvEdzylTnJ+UHkgw/BvE7Fn
        48LPDQGbSVM8xDJJJrhKLv0v55rIMYq9+j4rRMmhzphZj8Dtdy/SbwIsJQGKDqpo+sVTyS
        eZqMwTz2N1hpaobZ4VLWe1NekkAMzMg=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-55-6bGZtU9WP1elzVL8WdI9kw-1; Wed, 02 Sep 2020 18:45:46 -0400
X-MC-Unique: 6bGZtU9WP1elzVL8WdI9kw-1
Received: from smtp.corp.redhat.com (int-mx04.intmail.prod.int.phx2.redhat.com
 [10.5.11.14])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 9B59118A2251;
        Wed,  2 Sep 2020 22:45:44 +0000 (UTC)
Received: from localhost (ovpn-66-226.rdu2.redhat.com [10.10.66.226])
        by smtp.corp.redhat.com (Postfix) with ESMTP id E8AC65D9CC;
        Wed,  2 Sep 2020 22:45:43 +0000 (UTC)
From: Eduardo Habkost <ehabkost@redhat.com>
To: qemu-devel@nongnu.org
Cc: berrange@redhat.com, Paolo Bonzini <pbonzini@redhat.com>,
        Peter Maydell <peter.maydell@linaro.org>,
        Marcelo Tosatti <mtosatti@redhat.com>,
        Richard Henderson <rth@twiddle.net>,
        Huacai Chen <chenhc@lemote.com>,
        Aleksandar Markovic <aleksandar.qemu.devel@gmail.com>,
        Aurelien Jarno <aurelien@aurel32.net>,
        Jiaxun Yang <jiaxun.yang@flygoat.com>,
        Aleksandar Rikalo <aleksandar.rikalo@syrmia.com>,
        David Gibson <david@gibson.dropbear.id.au>,
        kvm@vger.kernel.org, qemu-arm@nongnu.org, qemu-ppc@nongnu.org
Subject: [PATCH 59/63] kvm: Rename KVM_STATE to KVM_ACCEL
Date: Wed,  2 Sep 2020 18:43:07 -0400
Message-Id: <20200902224311.1321159-60-ehabkost@redhat.com>
In-Reply-To: <20200902224311.1321159-1-ehabkost@redhat.com>
References: <20200902224311.1321159-1-ehabkost@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.14
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Make the type checking macro name consistent with the TYPE_*
constant.

Signed-off-by: Eduardo Habkost <ehabkost@redhat.com>
---
Cc: Paolo Bonzini <pbonzini@redhat.com>
Cc: Peter Maydell <peter.maydell@linaro.org>
Cc: Marcelo Tosatti <mtosatti@redhat.com>
Cc: Richard Henderson <rth@twiddle.net>
Cc: Eduardo Habkost <ehabkost@redhat.com>
Cc: Huacai Chen <chenhc@lemote.com>
Cc: Aleksandar Markovic <aleksandar.qemu.devel@gmail.com>
Cc: Aurelien Jarno <aurelien@aurel32.net>
Cc: Jiaxun Yang <jiaxun.yang@flygoat.com>
Cc: Aleksandar Rikalo <aleksandar.rikalo@syrmia.com>
Cc: David Gibson <david@gibson.dropbear.id.au>
Cc: kvm@vger.kernel.org
Cc: qemu-devel@nongnu.org
Cc: qemu-arm@nongnu.org
Cc: qemu-ppc@nongnu.org
---
 include/sysemu/kvm.h |  2 +-
 accel/kvm/kvm-all.c  | 18 +++++++++---------
 target/arm/kvm.c     |  2 +-
 target/i386/kvm.c    |  2 +-
 target/mips/kvm.c    |  2 +-
 target/ppc/kvm.c     |  4 ++--
 6 files changed, 15 insertions(+), 15 deletions(-)

```
#### [PATCH v2] KVM: fix memory leak in kvm_io_bus_unregister_dev()
##### From: Rustam Kovhaev <rkovhaev@gmail.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Rustam Kovhaev <rkovhaev@gmail.com>
X-Patchwork-Id: 11751983
Return-Path: <SRS0=tgfV=CL=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 3B46F739
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed,  2 Sep 2020 22:58:08 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 205022078E
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed,  2 Sep 2020 22:58:07 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=gmail.com header.i=@gmail.com
 header.b="EFn8sagT"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726674AbgIBW6D (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 2 Sep 2020 18:58:03 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:34326 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726247AbgIBW6C (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 2 Sep 2020 18:58:02 -0400
Received: from mail-pj1-x1043.google.com (mail-pj1-x1043.google.com
 [IPv6:2607:f8b0:4864:20::1043])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 77119C061244;
        Wed,  2 Sep 2020 15:58:00 -0700 (PDT)
Received: by mail-pj1-x1043.google.com with SMTP id ds1so519258pjb.1;
        Wed, 02 Sep 2020 15:58:00 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=from:to:cc:subject:date:message-id:mime-version
         :content-transfer-encoding;
        bh=XZfw6QbTtE+ig8bz903vOGLjPWd35/ECsGMavmJuypY=;
        b=EFn8sagTMorsR5/jkl/wUofpzJmbCPIma0wCVK84yaTwpnJ0l8C3ts/7jqq3C2xlEF
         Mpen5Hj9djCLDx2DsJFshyL850GLlzwEW7n980XuQxPnOevT5XUhqm6y3Mxe3HOhB4IW
         7/z9HA+7wxuB8DpHWsFDtsuXt+6RWXSQxekf3ylJLDEmH10J/5SBpkEPBo1HEguiG+uu
         4EBV/aFxXe7Dtq/qr5s7s06yPVQ0McfqyyC0WT0cGe6/DNB/5PhyOhOHwZgYVvMEbmdF
         0gCrIRyDbf+WFHAHC9pXCp5wu+6kk3x1cYKi/RCLHz7ZNPvBfvYevy6c1MxGDmv3I3+3
         A+bg==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:mime-version
         :content-transfer-encoding;
        bh=XZfw6QbTtE+ig8bz903vOGLjPWd35/ECsGMavmJuypY=;
        b=o3HTeoQJtlHEdT+I+wb5Op6otuXQcD1kPGuBNSckTcpipezG8Gze1cLwIX/efnR4lb
         Ntu4aZCwo7v9QM9dvWZrpcXo8T2y0AbtegpCime6d4GNbBiEXDBCTYuKh1rzlKCuPD2S
         TaVkSbFITLe8571jiKEStZpTzRLxAbrShc9TJjvWYJCkMYgyEJRlIIQnECiY6XO+w/L7
         UWXPCL07VUbxYs6t2al/wU7+V1WJ34vrn3ur1ZndDDiqi5EehGcD7UaVda6w2cI1np2j
         b978qSOnHdJHJb2nQi1m9c+fuI4VDLWZdwpiB98z6F6vZZMTZIrv3Ih4fi1Z3Dyhcks4
         /rQg==
X-Gm-Message-State: AOAM532Iz0OjyHRQx2i6u8vICVflEU4Vv2SrOcrSKXN/o3YVDI1mFRr5
        rna3HpK+WO9Nnm1b0TtfMCNsdGwliL0wrQ==
X-Google-Smtp-Source: 
 ABdhPJxJ5NCMU7pH1XkDZ7sFHsPUW3bZZckDyxeLpb3i6oVBoc5ezbFSE4vP8Iz4R0KyUAqxXWSf4Q==
X-Received: by 2002:a17:90a:4486:: with SMTP id
 t6mr27512pjg.230.1599087479949;
        Wed, 02 Sep 2020 15:57:59 -0700 (PDT)
Received: from thinkpad.teksavvy.com (104.36.148.139.aurocloud.com.
 [104.36.148.139])
        by smtp.gmail.com with ESMTPSA id
 q25sm579175pfn.181.2020.09.02.15.56.51
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Wed, 02 Sep 2020 15:57:05 -0700 (PDT)
From: Rustam Kovhaev <rkovhaev@gmail.com>
To: pbonzini@redhat.com, vkuznets@redhat.com, kvm@vger.kernel.org
Cc: linux-kernel@vger.kernel.org, gregkh@linuxfoundation.org,
        Rustam Kovhaev <rkovhaev@gmail.com>
Subject: [PATCH v2] KVM: fix memory leak in kvm_io_bus_unregister_dev()
Date: Wed,  2 Sep 2020 15:57:18 -0700
Message-Id: <20200902225718.675314-1-rkovhaev@gmail.com>
X-Mailer: git-send-email 2.28.0
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

when kmalloc() fails in kvm_io_bus_unregister_dev(), before removing
the bus, we should iterate over all other devices linked to it and call
kvm_iodevice_destructor() for them

Reported-and-tested-by: syzbot+f196caa45793d6374707@syzkaller.appspotmail.com
Link: https://syzkaller.appspot.com/bug?extid=f196caa45793d6374707
Signed-off-by: Rustam Kovhaev <rkovhaev@gmail.com>
Reviewed-by: Vitaly Kuznetsov <vkuznets@redhat.com>
---
v2:
- remove redundant whitespace
- remove goto statement and use if/else
---
 virt/kvm/kvm_main.c | 21 ++++++++++++---------
 1 file changed, 12 insertions(+), 9 deletions(-)

```
#### [PATCH V2] kvm x86/mmu: use KVM_REQ_MMU_SYNC to sync when needed
##### From: Lai Jiangshan <jiangshanlai@gmail.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Lai Jiangshan <jiangshanlai@gmail.com>
X-Patchwork-Id: 11750527
Return-Path: <SRS0=tgfV=CL=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 250C5138A
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed,  2 Sep 2020 12:54:13 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 0735E206F0
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed,  2 Sep 2020 12:54:13 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=gmail.com header.i=@gmail.com
 header.b="O3IliV7T"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727024AbgIBMyE (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 2 Sep 2020 08:54:04 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:54042 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726686AbgIBMx7 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 2 Sep 2020 08:53:59 -0400
Received: from mail-pj1-x1043.google.com (mail-pj1-x1043.google.com
 [IPv6:2607:f8b0:4864:20::1043])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id D6829C061244;
        Wed,  2 Sep 2020 05:53:58 -0700 (PDT)
Received: by mail-pj1-x1043.google.com with SMTP id gf14so2260023pjb.5;
        Wed, 02 Sep 2020 05:53:58 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=from:to:cc:subject:date:message-id:in-reply-to:references
         :mime-version:content-transfer-encoding;
        bh=GPYnsVkem3+rGz/hx35DWNwrA6gRvemoFnUQJ0NxbXk=;
        b=O3IliV7T1Fi5FVyDT80cvvfFZipGaOhG7IHj5wmk+aM5nRA+7s6hAcCzbQlG8BwdxX
         54f/Gvy8uAPninfvMtb5FsMDiz3OvpvPWVhF3Q5dML5syZvJF0mgurliqkv009WVDxkV
         DKCIKjfCcCJSb6alglsLEty0+b2/OGbCF7y2MQ8e1IkBpiwfNMd957e6nCfIELviTgwg
         86+eVzUqh36SZuRlLGOkd6BZntCZx7OAJGgYl+4yp86c/EJ/5M4W9JhiDd3rMAq6bFtZ
         A9k+04RosFknwjeAGWeIMUC5Eeb/AU1BIeIHS9R7CkFXuyhhS2qN/YRAsCVrJ0xyGgBZ
         h0gQ==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:in-reply-to
         :references:mime-version:content-transfer-encoding;
        bh=GPYnsVkem3+rGz/hx35DWNwrA6gRvemoFnUQJ0NxbXk=;
        b=rgxVA5l7ZuF2BTUsNVpRp45PBl87Spxe8jfEu75REIHAcYDHOlrTMgCOmSB0rMZYvU
         BjMpZqDGdEA9EHzyWuJ07hUPq2excrQtYtrbWdGTUVXrvsWA2yQLbig0FtGJpKEpDJHj
         M7txCiCysKf6TOWtaGjZUka87U/QLvTmRSX12WLbqPDpLw5ld0aXdTzpX0j5sTNiwyXO
         VqdeDtmZsLWC+OIOza/kpKFlW4971VRX2wpibwBET0LfOdOHtIEPFO+ZPru34p8e/Cza
         y0CmXg9TItwILDG/zuWGNyNJL9m8l6wY6Au+GnIFGKaz8OECnVCHATnlLVD58CnrIa9n
         h21w==
X-Gm-Message-State: AOAM532isjszWnsACXVykOToUA1/36o9a2o36bIN+33/mEpNcvhya6hF
        Rm2evoGHdApGDKZQqidHPbw5IKsIiUDKpg==
X-Google-Smtp-Source: 
 ABdhPJzAP+Z5tZoU/7BeymZD+T3FE/yPFfem59xGZ5yk9RLyR0EfRMQ/J022r+Y1ZzSejAs4fCiUPA==
X-Received: by 2002:a17:90a:e2cc:: with SMTP id
 fr12mr2143502pjb.125.1599051238181;
        Wed, 02 Sep 2020 05:53:58 -0700 (PDT)
Received: from localhost ([121.0.29.56])
        by smtp.gmail.com with ESMTPSA id
 np4sm4243201pjb.4.2020.09.02.05.53.57
        (version=TLS1_2 cipher=ECDHE-ECDSA-AES128-GCM-SHA256 bits=128/128);
        Wed, 02 Sep 2020 05:53:57 -0700 (PDT)
From: Lai Jiangshan <jiangshanlai@gmail.com>
To: linux-kernel@vger.kernel.org
Cc: Lai Jiangshan <laijs@linux.alibaba.com>,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Paolo Bonzini <pbonzini@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>,
        Thomas Gleixner <tglx@linutronix.de>,
        Ingo Molnar <mingo@redhat.com>, Borislav Petkov <bp@alien8.de>,
        x86@kernel.org, "H. Peter Anvin" <hpa@zytor.com>,
        kvm@vger.kernel.org
Subject: [PATCH V2] kvm x86/mmu: use KVM_REQ_MMU_SYNC to sync when needed
Date: Wed,  2 Sep 2020 21:54:21 +0800
Message-Id: <20200902135421.31158-1-jiangshanlai@gmail.com>
X-Mailer: git-send-email 2.19.1.6.gb485710b
In-Reply-To: <87y2ltx6gl.fsf@vitty.brq.redhat.com>
References: <87y2ltx6gl.fsf@vitty.brq.redhat.com>
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Lai Jiangshan <laijs@linux.alibaba.com>

When kvm_mmu_get_page() gets a page with unsynced children, the spt
pagetable is unsynchronized with the guest pagetable. But the
guest might not issue a "flush" operation on it when the pagetable
entry is changed from zero or other cases. The hypervisor has the 
responsibility to synchronize the pagetables.

The linux kernel behaves as above for many years, But
8c8560b83390("KVM: x86/mmu: Use KVM_REQ_TLB_FLUSH_CURRENT for MMU specific flushes)
inadvertently included a line of code to change it without giving any
reason in the changelog. It is clear that the commit's intention was to
change KVM_REQ_TLB_FLUSH -> KVM_REQ_TLB_FLUSH_CURRENT, so we don't
unneedlesly flush other contexts but one of the hunks changed
nearby KVM_REQ_MMU_SYNC instead.

The this patch changes it back.

Link: https://lore.kernel.org/lkml/20200320212833.3507-26-sean.j.christopherson@intel.com/
Cc: Sean Christopherson <sean.j.christopherson@intel.com>
Cc: Vitaly Kuznetsov <vkuznets@redhat.com>
Signed-off-by: Lai Jiangshan <laijs@linux.alibaba.com>
Reviewed-by: Vitaly Kuznetsov <vkuznets@redhat.com>
---
Changed from v1:
	update patch description

 arch/x86/kvm/mmu/mmu.c | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
#### [PATCH v4 1/3] PCI/IOV: Mark VFs as not implementing MSE bit
##### From: Matthew Rosato <mjrosato@linux.ibm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Matthew Rosato <mjrosato@linux.ibm.com>
X-Patchwork-Id: 11751691
Return-Path: <SRS0=tgfV=CL=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 5BE03109B
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed,  2 Sep 2020 19:47:06 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 40EEC208C7
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed,  2 Sep 2020 19:47:06 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=ibm.com header.i=@ibm.com
 header.b="bf62Hpk9"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726400AbgIBTq4 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 2 Sep 2020 15:46:56 -0400
Received: from mx0a-001b2d01.pphosted.com ([148.163.156.1]:37260 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1726140AbgIBTqy (ORCPT
        <rfc822;kvm@vger.kernel.org>); Wed, 2 Sep 2020 15:46:54 -0400
Received: from pps.filterd (m0098409.ppops.net [127.0.0.1])
        by mx0a-001b2d01.pphosted.com (8.16.0.42/8.16.0.42) with SMTP id
 082JgPHx042469;
        Wed, 2 Sep 2020 15:46:47 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=ibm.com;
 h=from : to : cc : subject
 : date : message-id : in-reply-to : references; s=pp1;
 bh=3++UIndG1m1KM9xZicSr0DVbIof7t1DVHs7Tsd9oytE=;
 b=bf62Hpk9JRVtlwLb0KoRpdEItjn6x1+I9PpvwvmPCTrL5SMAM0MK7HHOr7WbGzI5vHWP
 ObLkDKhqjjkmrClDJsikByG8ysSteRzJmpD6fLCB4ev/jQzBZBec5z/WcvPuBzrMgiAe
 SFtNOIAWbJzOmACz6UrbuSVafi7dFfvOgxIMNEX6pDAnu+UIH5abObLhbxNYGl6OC8ng
 sgmknhQMU7Y8TCZ/g6j553PRVpDMkxvYAxjGStMiyRxEGZBPEcV58gcdYOg/oL6lwJaA
 jQyfdP27iTaWrI48fRuP7+rSkaBJjzduOOPyTI8g6htx5NPnyToaPF7tdURDHzaHxtU7 7g==
Received: from pps.reinject (localhost [127.0.0.1])
        by mx0a-001b2d01.pphosted.com with ESMTP id 33ahsfg4kr-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Wed, 02 Sep 2020 15:46:47 -0400
Received: from m0098409.ppops.net (m0098409.ppops.net [127.0.0.1])
        by pps.reinject (8.16.0.36/8.16.0.36) with SMTP id 082Jklcn056649;
        Wed, 2 Sep 2020 15:46:47 -0400
Received: from ppma03wdc.us.ibm.com (ba.79.3fa9.ip4.static.sl-reverse.com
 [169.63.121.186])
        by mx0a-001b2d01.pphosted.com with ESMTP id 33ahsfg4k4-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Wed, 02 Sep 2020 15:46:47 -0400
Received: from pps.filterd (ppma03wdc.us.ibm.com [127.0.0.1])
        by ppma03wdc.us.ibm.com (8.16.0.42/8.16.0.42) with SMTP id
 082JgoD1006123;
        Wed, 2 Sep 2020 19:46:46 GMT
Received: from b01cxnp22036.gho.pok.ibm.com (b01cxnp22036.gho.pok.ibm.com
 [9.57.198.26])
        by ppma03wdc.us.ibm.com with ESMTP id 337en9jdq9-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Wed, 02 Sep 2020 19:46:46 +0000
Received: from b01ledav001.gho.pok.ibm.com (b01ledav001.gho.pok.ibm.com
 [9.57.199.106])
        by b01cxnp22036.gho.pok.ibm.com (8.14.9/8.14.9/NCO v10.0) with ESMTP
 id 082JkjX13212272
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Wed, 2 Sep 2020 19:46:45 GMT
Received: from b01ledav001.gho.pok.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 8BAEE2805A;
        Wed,  2 Sep 2020 19:46:45 +0000 (GMT)
Received: from b01ledav001.gho.pok.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id A0F0828059;
        Wed,  2 Sep 2020 19:46:43 +0000 (GMT)
Received: from oc4221205838.ibm.com (unknown [9.163.10.164])
        by b01ledav001.gho.pok.ibm.com (Postfix) with ESMTP;
        Wed,  2 Sep 2020 19:46:43 +0000 (GMT)
From: Matthew Rosato <mjrosato@linux.ibm.com>
To: alex.williamson@redhat.com, bhelgaas@google.com
Cc: schnelle@linux.ibm.com, pmorel@linux.ibm.com, mpe@ellerman.id.au,
        oohall@gmail.com, cohuck@redhat.com, kevin.tian@intel.com,
        linux-s390@vger.kernel.org, linux-kernel@vger.kernel.org,
        kvm@vger.kernel.org, linux-pci@vger.kernel.org
Subject: [PATCH v4 1/3] PCI/IOV: Mark VFs as not implementing MSE bit
Date: Wed,  2 Sep 2020 15:46:34 -0400
Message-Id: <1599075996-9826-2-git-send-email-mjrosato@linux.ibm.com>
X-Mailer: git-send-email 1.8.3.1
In-Reply-To: <1599075996-9826-1-git-send-email-mjrosato@linux.ibm.com>
References: <1599075996-9826-1-git-send-email-mjrosato@linux.ibm.com>
X-TM-AS-GCONF: 00
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.235,18.0.687
 definitions=2020-09-02_14:2020-09-02,2020-09-02 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 impostorscore=0
 priorityscore=1501 mlxlogscore=999 clxscore=1011 lowpriorityscore=0
 spamscore=0 phishscore=0 malwarescore=0 adultscore=0 mlxscore=0
 bulkscore=0 suspectscore=0 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.12.0-2006250000 definitions=main-2009020178
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Per the PCIe spec, VFs cannot implement the MSE bit
AKA PCI_COMMAND_MEMORY, and it must be hard-wired to 0.
Use a dev_flags bit to signify this requirement.

Signed-off-by: Matthew Rosato <mjrosato@linux.ibm.com>
---
 drivers/pci/iov.c   | 1 +
 include/linux/pci.h | 2 ++
 2 files changed, 3 insertions(+)

```
