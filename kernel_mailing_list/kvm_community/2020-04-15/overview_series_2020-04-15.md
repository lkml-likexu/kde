#### [PATCH 1/1] KVM: pass through CPUID(0x80000006)From: Jon Cargille <jcargill@google.com>
##### From: Jon Cargille <jcargill@google.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Jon Cargille <jcargill@google.com>
X-Patchwork-Id: 11489581
Return-Path: <SRS0=TyQv=57=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 3076B14B4
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 15 Apr 2020 01:24:14 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 173FC2087E
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 15 Apr 2020 01:24:14 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=google.com header.i=@google.com
 header.b="oqpB2vuB"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2392508AbgDOBX6 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 14 Apr 2020 21:23:58 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:58202 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-FAIL-OK-FAIL)
        by vger.kernel.org with ESMTP id S2392479AbgDOBXz (ORCPT
        <rfc822;kvm@vger.kernel.org>); Tue, 14 Apr 2020 21:23:55 -0400
Received: from mail-qv1-xf49.google.com (mail-qv1-xf49.google.com
 [IPv6:2607:f8b0:4864:20::f49])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id DA60CC061A0C
        for <kvm@vger.kernel.org>; Tue, 14 Apr 2020 18:23:54 -0700 (PDT)
Received: by mail-qv1-xf49.google.com with SMTP id dh19so1569742qvb.23
        for <kvm@vger.kernel.org>; Tue, 14 Apr 2020 18:23:54 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=date:message-id:mime-version:subject:from:to:cc;
        bh=+UiXyULlzq60JcrYizZG5xR6t3RIPIiANzzV8jZ5et4=;
        b=oqpB2vuBxzx65QrcJ0rQHZsF96i4qH7Ccf1rFMcJ6KOnPS2CNK2G/i+chkrdb9a2Ye
         fX6rGMu9RPCe4ZDmyHLd5d4qmhvuPwD0hOrJGwMw5nORi9st6VrLGQ45nlHi2RyMkxHw
         sT0Q/Lq/ib1UjQN672r4x39sYLOTMS6E5jC4JiK68o8u8FG0SJaWourIl4/l/zSoLU8P
         dS5s0Xjb7hinQYUflvWzNAddQsBycWP8wR0GNb8lFPoVv+XGbEik7X6N/9ilApkXTYvX
         vmUWUTbiMWpBvtYwR8BzNY1zoDGx25l3yFRiOgbO4PbrsLgoGMCamPcPhfwY4HOZ7nXo
         MkgA==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:date:message-id:mime-version:subject:from:to:cc;
        bh=+UiXyULlzq60JcrYizZG5xR6t3RIPIiANzzV8jZ5et4=;
        b=TWrAi7YfKGR5+u6hdw/4vHsqLiyt7f8z3yPX8X4q4iKgpkex5FJPG76cgfz44Z3zR0
         pbuJMWCoxhZvBtSXkoxF2YKoe7Hn6GsM6dqJv+OAXrJbIBx0IquoFVBruQ9I4wWF1jJY
         chjoL1nonqV18vSv04NGOle8K2x2C2VQSilWC0hn8fsJdywWv2ScJ9ZCEmXSxVeD6H9n
         sdJjt8b3hyloVJhIONbucEkfFYOFjBTNVC0WdlWWciZG+xMvYWdUcV/EBsuZPSDwTMCX
         lil5HIOihI5s3PkFOl+YqhS54PLEu/YsFn6ingSaE4thxBNbwU/jGc6QFflQaQgWSQV/
         clxA==
X-Gm-Message-State: AGi0PuYPV5rI42jYjt1hRgNs2DOZ0bIpMCj3cRlJ4BFbW3dyRNC1QYAB
        NGXUCZpc5tOMiJ3ReEKTfA6vdo1fxKCbHw==
X-Google-Smtp-Source: 
 APiQypJFWJeQvzBXxj3d9pW4mxjnL9s22hQArYDAnHt6z6K0vobYszap9H2qGKlaKJvejbA00rEqZ5icFY1N/w==
X-Received: by 2002:ad4:55c4:: with SMTP id bt4mr2703843qvb.225.1586913833875;
 Tue, 14 Apr 2020 18:23:53 -0700 (PDT)
Date: Tue, 14 Apr 2020 18:23:20 -0700
Message-Id: <20200415012320.236065-1-jcargill@google.com>
Mime-Version: 1.0
X-Mailer: git-send-email 2.26.0.110.g2183baf09c-goog
Subject: [PATCH 1/1] KVM: pass through CPUID(0x80000006)
From: Jon Cargille <jcargill@google.com>
To: Paolo Bonzini <pbonzini@redhat.com>,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>,
        Thomas Gleixner <tglx@linutronix.de>,
        Ingo Molnar <mingo@redhat.com>, Borislav Petkov <bp@alien8.de>,
        "H. Peter Anvin" <hpa@zytor.com>, x86@kernel.org,
        kvm@vger.kernel.org, linux-kernel@vger.kernel.org
Cc: Eric Northup <digitaleric@gmail.com>,
        Eric Northup <digitaleric@google.com>,
        Jon Cargille <jcargill@google.com>
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Eric Northup <digitaleric@gmail.com>

Return L2 cache and TLB information to guests.
They could have been set before, but the defaults that KVM returns will be
necessary for usermode that doesn't supply their own CPUID tables.

Signed-off-by: Eric Northup <digitaleric@google.com>
Signed-off-by: Eric Northup <digitaleric@gmail.com>
Signed-off-by: Jon Cargille <jcargill@google.com>
Signed-off-by: Jim Mattson <jmattson@google.com>
---
 arch/x86/kvm/cpuid.c | 3 +++
 1 file changed, 3 insertions(+)

```
#### [PATCH V2] vhost: do not enable VHOST_MENU by default
##### From: Jason Wang <jasowang@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Jason Wang <jasowang@redhat.com>
X-Patchwork-Id: 11489611
Return-Path: <SRS0=TyQv=57=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 473281392
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 15 Apr 2020 02:44:20 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 28DD820784
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 15 Apr 2020 02:44:20 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="JS/LjGe9"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1732777AbgDOCoO (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 14 Apr 2020 22:44:14 -0400
Received: from us-smtp-delivery-1.mimecast.com ([205.139.110.120]:34399 "EHLO
        us-smtp-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org
        with ESMTP id S1728267AbgDOCoM (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 14 Apr 2020 22:44:12 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1586918650;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=FTv5AkLYQ+5KJ9sSK50BNsriwFY0NMNF1swhxtvNcFc=;
        b=JS/LjGe9aDi/50oN3rvU/WqguHt2shehJeBu1Qg9mwTA4peBuQDtZmHeR4btvVLv0kfcy9
        8FDwgN/M627iKU3SVDSzp0CDp4EoCMd0MLlMIEJieEAoOmWvLxt/T9LDYjrVLVn2QCnYjk
        ImmpvQUpmXAno2yprBs6SFA9LX3F4OM=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-364-4zcwoXPfPQaXvOe1_HQyAA-1; Tue, 14 Apr 2020 22:44:08 -0400
X-MC-Unique: 4zcwoXPfPQaXvOe1_HQyAA-1
Received: from smtp.corp.redhat.com (int-mx01.intmail.prod.int.phx2.redhat.com
 [10.5.11.11])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id B0981800D53;
        Wed, 15 Apr 2020 02:44:06 +0000 (UTC)
Received: from jason-ThinkPad-X1-Carbon-6th.redhat.com
 (ovpn-12-184.pek2.redhat.com [10.72.12.184])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 48DDF12656E;
        Wed, 15 Apr 2020 02:43:57 +0000 (UTC)
From: Jason Wang <jasowang@redhat.com>
To: jasowang@redhat.com, mst@redhat.com
Cc: linux-mips@vger.kernel.org, linux-kernel@vger.kernel.org,
        linuxppc-dev@lists.ozlabs.org, linux-s390@vger.kernel.org,
        kvm@vger.kernel.org, virtualization@lists.linux-foundation.org,
        netdev@vger.kernel.org, geert@linux-m68k.org,
        tsbogend@alpha.franken.de, benh@kernel.crashing.org,
        paulus@samba.org, heiko.carstens@de.ibm.com, gor@linux.ibm.com,
        borntraeger@de.ibm.com, Michael Ellerman <mpe@ellerman.id.au>
Subject: [PATCH V2] vhost: do not enable VHOST_MENU by default
Date: Wed, 15 Apr 2020 10:43:56 +0800
Message-Id: <20200415024356.23751-1-jasowang@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.11
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

We try to keep the defconfig untouched after decoupling CONFIG_VHOST
out of CONFIG_VIRTUALIZATION in commit 20c384f1ea1a
("vhost: refine vhost and vringh kconfig") by enabling VHOST_MENU by
default. Then the defconfigs can keep enabling CONFIG_VHOST_NET
without the caring of CONFIG_VHOST.

But this will leave a "CONFIG_VHOST_MENU=y" in all defconfigs and even
for the ones that doesn't want vhost. So it actually shifts the
burdens to the maintainers of all other to add "CONFIG_VHOST_MENU is
not set". So this patch tries to enable CONFIG_VHOST explicitly in
defconfigs that enables CONFIG_VHOST_NET and CONFIG_VHOST_VSOCK.

Acked-by: Christian Borntraeger <borntraeger@de.ibm.com> (s390)
Acked-by: Michael Ellerman <mpe@ellerman.id.au> (powerpc)
Cc: Thomas Bogendoerfer <tsbogend@alpha.franken.de>
Cc: Benjamin Herrenschmidt <benh@kernel.crashing.org>
Cc: Paul Mackerras <paulus@samba.org>
Cc: Michael Ellerman <mpe@ellerman.id.au>
Cc: Heiko Carstens <heiko.carstens@de.ibm.com>
Cc: Vasily Gorbik <gor@linux.ibm.com>
Cc: Christian Borntraeger <borntraeger@de.ibm.com>
Reported-by: Geert Uytterhoeven <geert@linux-m68k.org>
Signed-off-by: Jason Wang <jasowang@redhat.com>
---
Change since V1:
- depends on EVENTFD for VHOST
---
 arch/mips/configs/malta_kvm_defconfig  |  1 +
 arch/powerpc/configs/powernv_defconfig |  1 +
 arch/powerpc/configs/ppc64_defconfig   |  1 +
 arch/powerpc/configs/pseries_defconfig |  1 +
 arch/s390/configs/debug_defconfig      |  1 +
 arch/s390/configs/defconfig            |  1 +
 drivers/vhost/Kconfig                  | 26 +++++++++-----------------
 7 files changed, 15 insertions(+), 17 deletions(-)

```
#### [PATCH] x86/kvm: make steal_time static
##### From: Jason Yan <yanaijie@huawei.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Jason Yan <yanaijie@huawei.com>
X-Patchwork-Id: 11490375
Return-Path: <SRS0=TyQv=57=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 1C66314B4
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 15 Apr 2020 08:23:27 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 0CE93208FE
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 15 Apr 2020 08:23:27 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2635892AbgDOIXY (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 15 Apr 2020 04:23:24 -0400
Received: from szxga06-in.huawei.com ([45.249.212.32]:59446 "EHLO huawei.com"
        rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org with ESMTP
        id S2635882AbgDOIXW (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 15 Apr 2020 04:23:22 -0400
Received: from DGGEMS402-HUB.china.huawei.com (unknown [172.30.72.58])
        by Forcepoint Email with ESMTP id 04D32D7354590BD9E99B;
        Wed, 15 Apr 2020 16:23:20 +0800 (CST)
Received: from huawei.com (10.175.124.28) by DGGEMS402-HUB.china.huawei.com
 (10.3.19.202) with Microsoft SMTP Server id 14.3.487.0; Wed, 15 Apr 2020
 16:23:12 +0800
From: Jason Yan <yanaijie@huawei.com>
To: <pbonzini@redhat.com>, <sean.j.christopherson@intel.com>,
        <vkuznets@redhat.com>, <wanpengli@tencent.com>,
        <jmattson@google.com>, <joro@8bytes.org>, <tglx@linutronix.de>,
        <mingo@redhat.com>, <bp@alien8.de>, <x86@kernel.org>,
        <hpa@zytor.com>, <kvm@vger.kernel.org>,
        <linux-kernel@vger.kernel.org>
CC: Jason Yan <yanaijie@huawei.com>, Hulk Robot <hulkci@huawei.com>
Subject: [PATCH] x86/kvm: make steal_time static
Date: Wed, 15 Apr 2020 16:49:39 +0800
Message-ID: <20200415084939.6367-1-yanaijie@huawei.com>
X-Mailer: git-send-email 2.21.1
MIME-Version: 1.0
X-Originating-IP: [10.175.124.28]
X-CFilter-Loop: Reflected
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Fix the following sparse warning:

arch/x86/kernel/kvm.c:58:1: warning: symbol '__pcpu_scope_steal_time'
was not declared. Should it be static?

Reported-by: Hulk Robot <hulkci@huawei.com>
Signed-off-by: Jason Yan <yanaijie@huawei.com>
Reported-by: kbuild test robot <lkp@intel.com>
---
 arch/x86/kernel/kvm.c | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
