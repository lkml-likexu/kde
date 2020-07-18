#### [PATCH] drivers: arm arch timer: Correct fault programming of CNTKCTL_EL1.EVNTI
##### From: Keqian Zhu <zhukeqian1@huawei.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Keqian Zhu <zhukeqian1@huawei.com>
X-Patchwork-Id: 11669463
Return-Path: <SRS0=oLpl=A4=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 6EB6314E3
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 17 Jul 2020 08:05:44 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 5F6D420737
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 17 Jul 2020 08:05:44 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728220AbgGQIFk (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 17 Jul 2020 04:05:40 -0400
Received: from szxga06-in.huawei.com ([45.249.212.32]:52240 "EHLO huawei.com"
        rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org with ESMTP
        id S1726233AbgGQIFk (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 17 Jul 2020 04:05:40 -0400
Received: from DGGEMS405-HUB.china.huawei.com (unknown [172.30.72.60])
        by Forcepoint Email with ESMTP id 06DC456026DCBC285F91;
        Fri, 17 Jul 2020 16:05:36 +0800 (CST)
Received: from DESKTOP-5IS4806.china.huawei.com (10.174.187.22) by
 DGGEMS405-HUB.china.huawei.com (10.3.19.205) with Microsoft SMTP Server id
 14.3.487.0; Fri, 17 Jul 2020 16:05:26 +0800
From: Keqian Zhu <zhukeqian1@huawei.com>
To: <linux-kernel@vger.kernel.org>,
        <linux-arm-kernel@lists.infradead.org>,
        <kvmarm@lists.cs.columbia.edu>, <kvm@vger.kernel.org>
CC: Marc Zyngier <maz@kernel.org>,
        Catalin Marinas <catalin.marinas@arm.com>,
        Will Deacon <will@kernel.org>,
        James Morse <james.morse@arm.com>,
        "Suzuki K Poulose" <suzuki.poulose@arm.com>,
        <wanghaibin.wang@huawei.com>, Keqian Zhu <zhukeqian1@huawei.com>
Subject: [PATCH] drivers: arm arch timer: Correct fault programming of
 CNTKCTL_EL1.EVNTI
Date: Fri, 17 Jul 2020 16:05:15 +0800
Message-ID: <20200717080515.19088-1-zhukeqian1@huawei.com>
X-Mailer: git-send-email 2.8.4.windows.1
MIME-Version: 1.0
X-Originating-IP: [10.174.187.22]
X-CFilter-Loop: Reflected
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

ARM virtual counter supports event stream, it can only trigger an event
when the trigger bit (the value of CNTKCTL_EL1.EVNTI) of CNTVCT_EL0 changes,
so the actual period of event stream is 2^(cntkctl_evnti + 1). For example,
when the trigger bit is 0, then virtual counter trigger an event for every
two cycles.

Signed-off-by: Keqian Zhu <zhukeqian1@huawei.com>
---
 drivers/clocksource/arm_arch_timer.c | 17 ++++++++++++++---
 1 file changed, 14 insertions(+), 3 deletions(-)

```
#### [kvm-unit-tests PATCH] arm64: Compile with -mno-outline-atomics for GCC >= 10
##### From: Alexandru Elisei <alexandru.elisei@arm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Alexandru Elisei <alexandru.elisei@arm.com>
X-Patchwork-Id: 11670713
Return-Path: <SRS0=oLpl=A4=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 0D1EB13B6
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 17 Jul 2020 16:46:46 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id E907420704
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 17 Jul 2020 16:46:45 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726393AbgGQQqo (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 17 Jul 2020 12:46:44 -0400
Received: from foss.arm.com ([217.140.110.172]:47390 "EHLO foss.arm.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726221AbgGQQqo (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 17 Jul 2020 12:46:44 -0400
Received: from usa-sjc-imap-foss1.foss.arm.com (unknown [10.121.207.14])
        by usa-sjc-mx-foss1.foss.arm.com (Postfix) with ESMTP id A2E3612FC;
        Fri, 17 Jul 2020 09:46:43 -0700 (PDT)
Received: from monolith.arm.com (unknown [10.37.8.27])
        by usa-sjc-imap-foss1.foss.arm.com (Postfix) with ESMTPSA id
 B06213F68F;
        Fri, 17 Jul 2020 09:46:42 -0700 (PDT)
From: Alexandru Elisei <alexandru.elisei@arm.com>
To: kvm@vger.kernel.org, kvmarm@lists.cs.columbia.edu
Cc: drjones@redhat.com, pbonzini@redhat.com
Subject: [kvm-unit-tests PATCH] arm64: Compile with -mno-outline-atomics for
 GCC >= 10
Date: Fri, 17 Jul 2020 17:47:27 +0100
Message-Id: <20200717164727.75580-1-alexandru.elisei@arm.com>
X-Mailer: git-send-email 2.27.0
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

GCC 10.1.0 introduced the -m{,no-}outline-atomics flags which, according to
man 1 gcc:

"Enable or disable calls to out-of-line helpers to implement atomic
operations.  These helpers will, at runtime, determine if the LSE
instructions from ARMv8.1-A can be used; if not, they will use the
load/store-exclusive instructions that are present in the base ARMv8.0 ISA.
[..] This option is on by default."

Unfortunately the option causes the following error at compile time:

aarch64-linux-gnu-ld -nostdlib -pie -n -o arm/spinlock-test.elf -T /path/to/kvm-unit-tests/arm/flat.lds \
	arm/spinlock-test.o arm/cstart64.o lib/libcflat.a lib/libfdt/libfdt.a /usr/lib/gcc/aarch64-linux-gnu/10.1.0/libgcc.a lib/arm/libeabi.a arm/spinlock-test.aux.o
aarch64-linux-gnu-ld: /usr/lib/gcc/aarch64-linux-gnu/10.1.0/libgcc.a(lse-init.o): in function `init_have_lse_atomics':
lse-init.c:(.text.startup+0xc): undefined reference to `__getauxval'

This is happening because we are linking against our own libcflat which
doesn't implement the function __getauxval().

Disable the use of the out-of-line functions by compiling with
-mno-outline-atomics if we detect a GCC version greater than 10.

Signed-off-by: Alexandru Elisei <alexandru.elisei@arm.com>
---

Tested with gcc versions 10.1.0 and 5.4.0 (cross-compilation), 9.3.0
(native).

I've been able to suss out the reason for the build failure from this
rejected gcc patch [1].

[1] https://patches.openembedded.org/patch/172460/

 arm/Makefile.arm64 | 6 ++++++
 1 file changed, 6 insertions(+)

```
#### linux-next: build failure after merge of the kvm tree
##### From: Stephen Rothwell <sfr@canb.auug.org.au>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Stephen Rothwell <sfr@canb.auug.org.au>
X-Patchwork-Id: 11669015
Return-Path: <SRS0=oLpl=A4=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 726F5138C
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 17 Jul 2020 05:57:13 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 566A220734
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 17 Jul 2020 05:57:13 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=canb.auug.org.au header.i=@canb.auug.org.au
 header.b="Qh6uvWzU"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726386AbgGQF5K (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 17 Jul 2020 01:57:10 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:49778 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1725807AbgGQF5J (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 17 Jul 2020 01:57:09 -0400
Received: from ozlabs.org (ozlabs.org [IPv6:2401:3900:2:1::2])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 0B03EC061755;
        Thu, 16 Jul 2020 22:57:09 -0700 (PDT)
Received: from authenticated.ozlabs.org (localhost [127.0.0.1])
        (using TLSv1.3 with cipher TLS_AES_256_GCM_SHA384 (256/256 bits)
         key-exchange ECDHE (P-256) server-signature RSA-PSS (4096 bits)
 server-digest SHA256)
        (No client certificate requested)
        by mail.ozlabs.org (Postfix) with ESMTPSA id 4B7L3z5kSgz9sQt;
        Fri, 17 Jul 2020 15:57:03 +1000 (AEST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple; d=canb.auug.org.au;
        s=201702; t=1594965425;
        bh=pogloshOGM434OcRKBF6s6ykZvFgAvuWoOESdMeuiYQ=;
        h=Date:From:To:Cc:Subject:From;
        b=Qh6uvWzU9USOoVdsHuNu9fBrdoTUryAb8L7RQvx42+KbM904Jpg/QAkQVAzaoCEWd
         TYd71mEQtOaxgHgVkBEu7L8kn14f2SbliwRKDAcyU/KTeG05Bv+MqKF9Xi//sa5UkL
         BzNBXO6HwX6qz5LmOPHV9eTmhV2YWZS9eyhac3rBSnrRCPAwxackvwxhOU52Ni8uJN
         IzusT8QiRIzNqHR/Les5DWWLeLA96mxB+tLEjAVFP4+yiU6p9BPvpoJHkrLMyEnCKx
         W0pDwPPaZHpO/t+JesjlkDXhVIZbu8pmfJRfkvO08lZRJxAxm7Ekvv8duZRNshXgi+
         rgyqV0Ey1ytXQ==
Date: Fri, 17 Jul 2020 15:57:01 +1000
From: Stephen Rothwell <sfr@canb.auug.org.au>
To: Paolo Bonzini <pbonzini@redhat.com>, KVM <kvm@vger.kernel.org>,
        Thomas Gleixner <tglx@linutronix.de>,
        Ingo Molnar <mingo@elte.hu>, "H. Peter Anvin" <hpa@zytor.com>,
        Peter Zijlstra <peterz@infradead.org>
Cc: Linux Next Mailing List <linux-next@vger.kernel.org>,
        Linux Kernel Mailing List <linux-kernel@vger.kernel.org>
Subject: linux-next: build failure after merge of the kvm tree
Message-ID: <20200717155701.2d7caebb@canb.auug.org.au>
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Hi all,

After merging the kvm tree, today's linux-next build (x86_64 allmodconfig)
failed like this:

arch/x86/kernel/kvm.c: In function '__sysvec_kvm_asyncpf_interrupt':
arch/x86/kernel/kvm.c:275:13: error: implicit declaration of function 'idtentry_enter_cond_rcu'; did you mean 'idtentry_enter_nmi'? [-Werror=implicit-function-declaration]
  275 |  rcu_exit = idtentry_enter_cond_rcu(regs);
      |             ^~~~~~~~~~~~~~~~~~~~~~~
      |             idtentry_enter_nmi
arch/x86/kernel/kvm.c:286:2: error: implicit declaration of function 'idtentry_exit_cond_rcu'; did you mean 'idtentry_exit_nmi'? [-Werror=implicit-function-declaration]
  286 |  idtentry_exit_cond_rcu(regs, rcu_exit);
      |  ^~~~~~~~~~~~~~~~~~~~~~
      |  idtentry_exit_nmi

Caused by commit

  b037b09b9058 ("x86/entry: Rename idtentry_enter/exit_cond_rcu() to idtentry_enter/exit()")

from the tip tree interacting with commit

  26d05b368a5c ("Merge branch 'kvm-async-pf-int' into HEAD")

from the kvm tree.

I have applied the following merge fix patch.

From: Stephen Rothwell <sfr@canb.auug.org.au>
Date: Fri, 17 Jul 2020 15:51:27 +1000
Subject: [PATCH] fix up for idtentry_{enter,exit}_cond_rcu() renaming

Signed-off-by: Stephen Rothwell <sfr@canb.auug.org.au>
---
 arch/x86/kernel/kvm.c | 6 +++---
 1 file changed, 3 insertions(+), 3 deletions(-)

```
#### linux-next: manual merge of the kvm tree with the tip tree
##### From: Stephen Rothwell <sfr@canb.auug.org.au>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Stephen Rothwell <sfr@canb.auug.org.au>
X-Patchwork-Id: 11668969
Return-Path: <SRS0=oLpl=A4=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 359D660D
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 17 Jul 2020 05:26:07 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 1C8E6206BE
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 17 Jul 2020 05:26:07 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=canb.auug.org.au header.i=@canb.auug.org.au
 header.b="HSs0Kgl9"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726634AbgGQF0C (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 17 Jul 2020 01:26:02 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:45012 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1725807AbgGQF0C (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 17 Jul 2020 01:26:02 -0400
Received: from ozlabs.org (bilbo.ozlabs.org [IPv6:2401:3900:2:1::2])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id E44F4C061755;
        Thu, 16 Jul 2020 22:26:01 -0700 (PDT)
Received: from authenticated.ozlabs.org (localhost [127.0.0.1])
        (using TLSv1.3 with cipher TLS_AES_256_GCM_SHA384 (256/256 bits)
         key-exchange ECDHE (P-256) server-signature RSA-PSS (4096 bits)
 server-digest SHA256)
        (No client certificate requested)
        by mail.ozlabs.org (Postfix) with ESMTPSA id 4B7KN65K28z9sRR;
        Fri, 17 Jul 2020 15:25:58 +1000 (AEST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple; d=canb.auug.org.au;
        s=201702; t=1594963560;
        bh=LbMvc5Iklk5Xyio7B6Dc+w1qLyJXPJQeJsnn4jpFg6Y=;
        h=Date:From:To:Cc:Subject:From;
        b=HSs0Kgl9Ta8tvTHe1BgLFTd26tXH473RBtQnTuMJip+2hTgbOqhFvIajhjWyILvAF
         g+EguwyXjq0+GhXfUoV/0j1GM+DaGaBSxkZCOmGNX7PLr4sgF3RsftUYTwQIQwgLOi
         fhnXKyCAMTV9PitJ4MNxcU/v7n6fpOWTmumDIaZMfcmFkeNbXVXlVKUJi6ysLan6JI
         FMo+eMIND3AvXNbCn39S89ng9qYc/49CiVFsLn7GTkx0gs3bG8JBQgWGtgFDGcZl1m
         KUno5e80DQIsubaqIYgJdIWvYtYmsh25MIcy1vxNO+Bycmt5gLddFPnoUR3GE91njm
         Vso4KK27is2Kg==
Date: Fri, 17 Jul 2020 15:25:57 +1000
From: Stephen Rothwell <sfr@canb.auug.org.au>
To: Paolo Bonzini <pbonzini@redhat.com>, KVM <kvm@vger.kernel.org>,
        Thomas Gleixner <tglx@linutronix.de>,
        Ingo Molnar <mingo@elte.hu>, "H. Peter Anvin" <hpa@zytor.com>,
        Peter Zijlstra <peterz@infradead.org>
Cc: Linux Next Mailing List <linux-next@vger.kernel.org>,
        Linux Kernel Mailing List <linux-kernel@vger.kernel.org>,
        Andy Lutomirski <luto@kernel.org>,
        Vitaly Kuznetsov <vkuznets@redhat.com>
Subject: linux-next: manual merge of the kvm tree with the tip tree
Message-ID: <20200717152557.49ca6764@canb.auug.org.au>
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Hi all,

Today's linux-next merge of the kvm tree got a conflict in:

  arch/x86/kernel/kvm.c

between commit:

  b037b09b9058 ("x86/entry: Rename idtentry_enter/exit_cond_rcu() to idtentry_enter/exit()")

from the tip tree and commit:

  b1d405751cd5 ("KVM: x86: Switch KVM guest to using interrupts for page ready APF delivery")

from the kvm tree.

I fixed it up (see below) and can carry the fix as necessary. This
is now fixed as far as linux-next is concerned, but any non trivial
conflicts should be mentioned to your upstream maintainer when your tree
is submitted for merging.  You may also want to consider cooperating
with the maintainer of the conflicting tree to minimise any particularly
complex conflicts.

```
#### [v3 01/15] powerpc/perf: Update cpu_hw_event to use `struct` for storing MMCR registers
##### From: Athira Rajeev <atrajeev@linux.vnet.ibm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Athira Rajeev <atrajeev@linux.vnet.ibm.com>
X-Patchwork-Id: 11670465
Return-Path: <SRS0=oLpl=A4=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id BB3FA13B6
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 17 Jul 2020 14:39:00 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 8AFF021775
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 17 Jul 2020 14:39:00 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727993AbgGQOi7 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 17 Jul 2020 10:38:59 -0400
Received: from mx0b-001b2d01.pphosted.com ([148.163.158.5]:41594 "EHLO
        mx0b-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1726812AbgGQOi4 (ORCPT
        <rfc822;kvm@vger.kernel.org>); Fri, 17 Jul 2020 10:38:56 -0400
Received: from pps.filterd (m0098417.ppops.net [127.0.0.1])
        by mx0a-001b2d01.pphosted.com (8.16.0.42/8.16.0.42) with SMTP id
 06HEXIwh126674;
        Fri, 17 Jul 2020 10:38:39 -0400
Received: from ppma05fra.de.ibm.com (6c.4a.5195.ip4.static.sl-reverse.com
 [149.81.74.108])
        by mx0a-001b2d01.pphosted.com with ESMTP id 32awbsaej4-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Fri, 17 Jul 2020 10:38:39 -0400
Received: from pps.filterd (ppma05fra.de.ibm.com [127.0.0.1])
        by ppma05fra.de.ibm.com (8.16.0.42/8.16.0.42) with SMTP id
 06HEWISn003044;
        Fri, 17 Jul 2020 14:38:37 GMT
Received: from b06avi18626390.portsmouth.uk.ibm.com
 (b06avi18626390.portsmouth.uk.ibm.com [9.149.26.192])
        by ppma05fra.de.ibm.com with ESMTP id 327q2y341k-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Fri, 17 Jul 2020 14:38:37 +0000
Received: from d06av22.portsmouth.uk.ibm.com (d06av22.portsmouth.uk.ibm.com
 [9.149.105.58])
        by b06avi18626390.portsmouth.uk.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id 06HEbBVE51249460
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Fri, 17 Jul 2020 14:37:12 GMT
Received: from d06av22.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id E44FF4C04E;
        Fri, 17 Jul 2020 14:38:34 +0000 (GMT)
Received: from d06av22.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id A7E0E4C046;
        Fri, 17 Jul 2020 14:38:31 +0000 (GMT)
Received: from localhost.localdomain.localdomain (unknown [9.77.207.73])
        by d06av22.portsmouth.uk.ibm.com (Postfix) with ESMTP;
        Fri, 17 Jul 2020 14:38:31 +0000 (GMT)
From: Athira Rajeev <atrajeev@linux.vnet.ibm.com>
To: mpe@ellerman.id.au
Cc: linuxppc-dev@lists.ozlabs.org, maddy@linux.vnet.ibm.com,
        mikey@neuling.org, kvm-ppc@vger.kernel.org, kvm@vger.kernel.org,
        ego@linux.vnet.ibm.com, svaidyan@in.ibm.com, acme@kernel.org,
        jolsa@kernel.org
Subject: [v3 01/15] powerpc/perf: Update cpu_hw_event to use `struct` for
 storing MMCR registers
Date: Fri, 17 Jul 2020 10:38:13 -0400
Message-Id: <1594996707-3727-2-git-send-email-atrajeev@linux.vnet.ibm.com>
X-Mailer: git-send-email 1.8.3.1
In-Reply-To: <1594996707-3727-1-git-send-email-atrajeev@linux.vnet.ibm.com>
References: <1594996707-3727-1-git-send-email-atrajeev@linux.vnet.ibm.com>
X-TM-AS-GCONF: 00
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.235,18.0.687
 definitions=2020-07-17_06:2020-07-17,2020-07-17 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 bulkscore=0 phishscore=0
 impostorscore=0 lowpriorityscore=0 adultscore=0 spamscore=0 mlxscore=0
 malwarescore=0 clxscore=1015 mlxlogscore=875 priorityscore=1501
 suspectscore=1 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.12.0-2006250000 definitions=main-2007170108
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

core-book3s currently uses array to store the MMCR registers as part
of per-cpu `cpu_hw_events`. This patch does a clean up to use `struct`
to store mmcr regs instead of array. This will make code easier to read
and reduces chance of any subtle bug that may come in the future, say
when new registers are added. Patch updates all relevant code that was
using MMCR array ( cpuhw->mmcr[x]) to use newly introduced `struct`.
This includes the PMU driver code for supported platforms (power5
to power9) and ISA macros for counter support functions.

Signed-off-by: Athira Rajeev <atrajeev@linux.vnet.ibm.com>
---
 arch/powerpc/include/asm/perf_event_server.h | 10 ++++--
 arch/powerpc/perf/core-book3s.c              | 53 +++++++++++++---------------
 arch/powerpc/perf/isa207-common.c            | 20 +++++------
 arch/powerpc/perf/isa207-common.h            |  4 +--
 arch/powerpc/perf/mpc7450-pmu.c              | 21 +++++++----
 arch/powerpc/perf/power5+-pmu.c              | 17 ++++-----
 arch/powerpc/perf/power5-pmu.c               | 17 ++++-----
 arch/powerpc/perf/power6-pmu.c               | 16 ++++-----
 arch/powerpc/perf/power7-pmu.c               | 17 ++++-----
 arch/powerpc/perf/ppc970-pmu.c               | 24 ++++++-------
 10 files changed, 105 insertions(+), 94 deletions(-)

```
#### [kvm-unit-tests PATCH 1/3] s390x: Add custom pgm cleanup function
##### From: Janosch Frank <frankja@linux.ibm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Janosch Frank <frankja@linux.ibm.com>
X-Patchwork-Id: 11670567
Return-Path: <SRS0=oLpl=A4=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 572DB13B1
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 17 Jul 2020 14:58:30 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 48EFE2076D
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 17 Jul 2020 14:58:30 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726977AbgGQO63 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 17 Jul 2020 10:58:29 -0400
Received: from mx0b-001b2d01.pphosted.com ([148.163.158.5]:53698 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S1726755AbgGQO62 (ORCPT
        <rfc822;kvm@vger.kernel.org>); Fri, 17 Jul 2020 10:58:28 -0400
Received: from pps.filterd (m0098413.ppops.net [127.0.0.1])
        by mx0b-001b2d01.pphosted.com (8.16.0.42/8.16.0.42) with SMTP id
 06HEUxx3031437;
        Fri, 17 Jul 2020 10:58:27 -0400
Received: from pps.reinject (localhost [127.0.0.1])
        by mx0b-001b2d01.pphosted.com with ESMTP id 32b61knv3e-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Fri, 17 Jul 2020 10:58:27 -0400
Received: from m0098413.ppops.net (m0098413.ppops.net [127.0.0.1])
        by pps.reinject (8.16.0.36/8.16.0.36) with SMTP id 06HEVESE032683;
        Fri, 17 Jul 2020 10:58:27 -0400
Received: from ppma05fra.de.ibm.com (6c.4a.5195.ip4.static.sl-reverse.com
 [149.81.74.108])
        by mx0b-001b2d01.pphosted.com with ESMTP id 32b61knv32-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Fri, 17 Jul 2020 10:58:27 -0400
Received: from pps.filterd (ppma05fra.de.ibm.com [127.0.0.1])
        by ppma05fra.de.ibm.com (8.16.0.42/8.16.0.42) with SMTP id
 06HEpZVZ018424;
        Fri, 17 Jul 2020 14:58:25 GMT
Received: from b06cxnps4074.portsmouth.uk.ibm.com
 (d06relay11.portsmouth.uk.ibm.com [9.149.109.196])
        by ppma05fra.de.ibm.com with ESMTP id 327q2y34a7-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Fri, 17 Jul 2020 14:58:25 +0000
Received: from d06av24.portsmouth.uk.ibm.com (mk.ibm.com [9.149.105.60])
        by b06cxnps4074.portsmouth.uk.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id 06HEwM8r52363336
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Fri, 17 Jul 2020 14:58:22 GMT
Received: from d06av24.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 4CBE142049;
        Fri, 17 Jul 2020 14:58:22 +0000 (GMT)
Received: from d06av24.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 892D842041;
        Fri, 17 Jul 2020 14:58:21 +0000 (GMT)
Received: from linux01.pok.stglabs.ibm.com (unknown [9.114.17.81])
        by d06av24.portsmouth.uk.ibm.com (Postfix) with ESMTP;
        Fri, 17 Jul 2020 14:58:21 +0000 (GMT)
From: Janosch Frank <frankja@linux.ibm.com>
To: kvm@vger.kernel.org
Cc: thuth@redhat.com, linux-s390@vger.kernel.org, david@redhat.com,
        borntraeger@de.ibm.com, cohuck@redhat.com, imbrenda@linux.ibm.com
Subject: [kvm-unit-tests PATCH 1/3] s390x: Add custom pgm cleanup function
Date: Fri, 17 Jul 2020 10:58:11 -0400
Message-Id: <20200717145813.62573-2-frankja@linux.ibm.com>
X-Mailer: git-send-email 2.25.1
In-Reply-To: <20200717145813.62573-1-frankja@linux.ibm.com>
References: <20200717145813.62573-1-frankja@linux.ibm.com>
MIME-Version: 1.0
X-TM-AS-GCONF: 00
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.235,18.0.687
 definitions=2020-07-17_06:2020-07-17,2020-07-17 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 lowpriorityscore=0
 malwarescore=0 mlxscore=0 adultscore=0 impostorscore=0 mlxlogscore=999
 spamscore=0 clxscore=1015 suspectscore=1 phishscore=0 priorityscore=1501
 bulkscore=0 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.12.0-2006250000 definitions=main-2007170103
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Sometimes we need to do cleanup which we don't necessarily want to add
to interrupt.c, so lets add a way to register a cleanup function.

Signed-off-by: Janosch Frank <frankja@linux.ibm.com>
---
 lib/s390x/asm/interrupt.h | 1 +
 lib/s390x/interrupt.c     | 9 +++++++++
 2 files changed, 10 insertions(+)

```
#### [RESEND PATCH] drivers: arm arch timer: Correct fault programming of CNTKCTL_EL1.EVNTI
##### From: Keqian Zhu <zhukeqian1@huawei.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Keqian Zhu <zhukeqian1@huawei.com>
X-Patchwork-Id: 11669651
Return-Path: <SRS0=oLpl=A4=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 4EF7313B1
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 17 Jul 2020 09:21:28 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 3264C20775
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 17 Jul 2020 09:21:28 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726201AbgGQJVX (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 17 Jul 2020 05:21:23 -0400
Received: from szxga05-in.huawei.com ([45.249.212.191]:7780 "EHLO huawei.com"
        rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org with ESMTP
        id S1725864AbgGQJVX (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 17 Jul 2020 05:21:23 -0400
Received: from DGGEMS409-HUB.china.huawei.com (unknown [172.30.72.59])
        by Forcepoint Email with ESMTP id 73228D0B5AF77BBC20AC;
        Fri, 17 Jul 2020 17:21:21 +0800 (CST)
Received: from DESKTOP-5IS4806.china.huawei.com (10.174.187.22) by
 DGGEMS409-HUB.china.huawei.com (10.3.19.209) with Microsoft SMTP Server id
 14.3.487.0; Fri, 17 Jul 2020 17:21:12 +0800
From: Keqian Zhu <zhukeqian1@huawei.com>
To: <linux-kernel@vger.kernel.org>,
        <linux-arm-kernel@lists.infradead.org>,
        <kvmarm@lists.cs.columbia.edu>, <kvm@vger.kernel.org>
CC: Marc Zyngier <maz@kernel.org>,
        Catalin Marinas <catalin.marinas@arm.com>,
        Will Deacon <will@kernel.org>,
        James Morse <james.morse@arm.com>,
        "Suzuki K Poulose" <suzuki.poulose@arm.com>,
        <wanghaibin.wang@huawei.com>, Keqian Zhu <zhukeqian1@huawei.com>
Subject: [RESEND PATCH] drivers: arm arch timer: Correct fault programming of
 CNTKCTL_EL1.EVNTI
Date: Fri, 17 Jul 2020 17:21:04 +0800
Message-ID: <20200717092104.15428-1-zhukeqian1@huawei.com>
X-Mailer: git-send-email 2.8.4.windows.1
MIME-Version: 1.0
X-Originating-IP: [10.174.187.22]
X-CFilter-Loop: Reflected
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

ARM virtual counter supports event stream. It can only trigger an event
when the trigger bit of CNTVCT_EL0 changes from 0 to 1 (or from 1 to 0),
so the actual period of event stream is 2 ^ (cntkctl_evnti + 1). For
example, when the trigger bit is 0, then it triggers an event for every
two cycles.

Signed-off-by: Keqian Zhu <zhukeqian1@huawei.com>
---
 drivers/clocksource/arm_arch_timer.c | 17 ++++++++++++++---
 1 file changed, 14 insertions(+), 3 deletions(-)

```
#### [PATCH kvm-unit-tests v2 1/3] svm: Add ability to execute test via test_run on a vcpu other than vcpu 0
##### From: Cathy Avery <cavery@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Cathy Avery <cavery@redhat.com>
X-Patchwork-Id: 11669995
Return-Path: <SRS0=oLpl=A4=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id C511D14E3
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 17 Jul 2020 11:34:44 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id AB4F620B1F
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 17 Jul 2020 11:34:44 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="HHA7xNGE"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726619AbgGQLeb (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 17 Jul 2020 07:34:31 -0400
Received: from us-smtp-delivery-1.mimecast.com ([205.139.110.120]:58562 "EHLO
        us-smtp-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org
        with ESMTP id S1726198AbgGQLe3 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 17 Jul 2020 07:34:29 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1594985667;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding:
         in-reply-to:in-reply-to:references:references;
        bh=ql4tis1uscIP3qLeTRHhYQZodhivUb4DYruBJ6jvbTs=;
        b=HHA7xNGEVq9SjOGjTBRVGNgmMpFzH4Oa0ChAv58aLYgjXOwiXBa6sr0o7gwuxn56K57H9e
        TJ0XBBqacll4wMwjLt+AeJEqG/1kOQZwbFFcIvZrJyhDLRuawZ96m/3CKcR/iLEuiU2ghz
        2j/cjOdkO40L9CAZq8AWOQaCIhdiD2A=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-412-0O2DYWcYPQe54AGqXQ7A5g-1; Fri, 17 Jul 2020 07:34:26 -0400
X-MC-Unique: 0O2DYWcYPQe54AGqXQ7A5g-1
Received: from smtp.corp.redhat.com (int-mx08.intmail.prod.int.phx2.redhat.com
 [10.5.11.23])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id A1157100A8E8;
        Fri, 17 Jul 2020 11:34:23 +0000 (UTC)
Received: from virtlab710.virt.lab.eng.bos.redhat.com
 (virtlab710.virt.lab.eng.bos.redhat.com [10.19.152.252])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 2CD0619C58;
        Fri, 17 Jul 2020 11:34:23 +0000 (UTC)
From: Cathy Avery <cavery@redhat.com>
To: linux-kernel@vger.kernel.org, kvm@vger.kernel.org,
        pbonzini@redhat.com
Subject: [PATCH kvm-unit-tests v2 1/3] svm: Add ability to execute test via
 test_run on a vcpu other than vcpu 0
Date: Fri, 17 Jul 2020 07:34:20 -0400
Message-Id: <20200717113422.19575-2-cavery@redhat.com>
In-Reply-To: <20200717113422.19575-1-cavery@redhat.com>
References: <20200717113422.19575-1-cavery@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.84 on 10.5.11.23
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

When running tests that can result in a vcpu being left in an
indeterminate state it is useful to be able to run the test on
a vcpu other than 0. This patch allows test_run to be executed
on any vcpu indicated by the on_vcpu member of the svm_test struct.
The initialized state of the vcpu0 registers used to populate the
vmcb is carried forward to the other vcpus.

Signed-off-by: Cathy Avery <cavery@redhat.com>
---
 lib/x86/vm.c | 18 ++++++++++++++++++
 lib/x86/vm.h |  7 +++++++
 x86/svm.c    | 24 +++++++++++++++++++++++-
 x86/svm.h    |  2 ++
 4 files changed, 50 insertions(+), 1 deletion(-)

```
#### [PATCH v1 1/1] x86/kvm/hyper-v: Synic default SCONTROL MSR needs to be enabled
##### From: Jon Doron <arilou@gmail.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Jon Doron <arilou@gmail.com>
X-Patchwork-Id: 11670083
Return-Path: <SRS0=oLpl=A4=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 36B95159A
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 17 Jul 2020 12:52:55 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 1D06120734
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 17 Jul 2020 12:52:55 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=gmail.com header.i=@gmail.com
 header.b="ubnRa417"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726648AbgGQMwy (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 17 Jul 2020 08:52:54 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:57280 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726205AbgGQMwx (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 17 Jul 2020 08:52:53 -0400
Received: from mail-wr1-x442.google.com (mail-wr1-x442.google.com
 [IPv6:2a00:1450:4864:20::442])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 27543C061755
        for <kvm@vger.kernel.org>; Fri, 17 Jul 2020 05:52:53 -0700 (PDT)
Received: by mail-wr1-x442.google.com with SMTP id z13so10963873wrw.5
        for <kvm@vger.kernel.org>; Fri, 17 Jul 2020 05:52:53 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=from:to:cc:subject:date:message-id:in-reply-to:references
         :mime-version:content-transfer-encoding;
        bh=oahFvkWn9xu77yQoX7qxwILoCEWOJVcZ/jZ2Dt3CCSQ=;
        b=ubnRa4178Nm2mxDbZhK4nXMmrWyvh7zjC8mmGU4mcCvpvh7xIVcQ7lAIFwlpzyhd9j
         8uXeqjab/PGn5wDu61cZhyGh5ctswuBMiAXsdCfKWFo2jvr49XacD63+BfcoAgaSm1gK
         p+DXcn9tfRBU6Nk0JOW+5mdJa54eZFFFcpggblwsG5lpPcZOKaT+p3S/KaArrfPQJ0zt
         DeeWVkdviiBNx2rMYkpxuqdMViIXTKmC2qdGdyDKQuNBZnvuXOz5brQNBs09RwLTNYJ4
         gs1Cj1jneIY3XmP7K9C2aekcTb5e2cKyP197vsf5UTry7vBxAfzzjsqFpeRebh7kV+0h
         ZC/w==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:in-reply-to
         :references:mime-version:content-transfer-encoding;
        bh=oahFvkWn9xu77yQoX7qxwILoCEWOJVcZ/jZ2Dt3CCSQ=;
        b=V/NWHfJy0oy3PADlEuZTG6sPBycQwsfMWJLGD8YD3FHV1mpcRF8OEXQ4LZeasIKz4H
         Ux+HdZOiXmLtrmiTTIFZgwG0/nEOXttdhhyBPOdx0SbPvDViTYeWl/6XENhnGJuZPtDT
         JlUio5NXYehlteQlHb8vl10kpPTS2gJL3R8x2WN4/VhOCHp/wkwvYh81EHPhdUWoA8FO
         gWe+KjpIwVHdcGXnbSLu6lKl10wozhcIIDmA1zsV3FT69tLwpkqAnVN9UEjYCBXBrMfq
         gGBPnOs3FMBqLMR5G6UyEU0rw/lej2Nd5f/gdrF+8O8uILMDvoeBvgMW5UZzFnSu3EJf
         N9rA==
X-Gm-Message-State: AOAM532IOAMXj+rlNkXUvRoSuW78U6+Skhu2sZ4+ekIpN6F+p8DUhfFN
        GydYPVsditUVmxN+wK1kmPFW0+1B
X-Google-Smtp-Source: 
 ABdhPJxX+7PYBknUfX1DIm+w+CZnA5xttM2A/g18AdQqPcJxzmStnvpnmX6loPZsQuYxnRMMaNX9CQ==
X-Received: by 2002:a5d:4591:: with SMTP id
 p17mr10153266wrq.343.1594990371449;
        Fri, 17 Jul 2020 05:52:51 -0700 (PDT)
Received: from jondnuc.lan (IGLD-84-229-155-64.inter.net.il. [84.229.155.64])
        by smtp.gmail.com with ESMTPSA id
 z132sm15160699wmb.21.2020.07.17.05.52.50
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Fri, 17 Jul 2020 05:52:51 -0700 (PDT)
From: Jon Doron <arilou@gmail.com>
To: kvm@vger.kernel.org
Cc: vkuznets@redhat.com, pbonzini@redhat.com, rvkagan@yandex-team.ru,
        Jon Doron <arilou@gmail.com>
Subject: [PATCH v1 1/1] x86/kvm/hyper-v: Synic default SCONTROL MSR needs to
 be enabled
Date: Fri, 17 Jul 2020 15:52:38 +0300
Message-Id: <20200717125238.1103096-2-arilou@gmail.com>
X-Mailer: git-send-email 2.26.2
In-Reply-To: <20200717125238.1103096-1-arilou@gmail.com>
References: <20200717125238.1103096-1-arilou@gmail.com>
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Based on an analysis of the HyperV firmwares (Gen1 and Gen2) it seems
like the SCONTROL is not being set to the ENABLED state as like we have
thought.

Also from a test done by Vitaly Kuznetsov, running a nested HyperV it
was concluded that the first access to the SCONTROL MSR with a read
resulted with the value of 0x1, aka HV_SYNIC_CONTROL_ENABLE.

It's important to note that this diverges from the value states in the
HyperV TLFS of 0.

Signed-off-by: Jon Doron <arilou@gmail.com>
---
 arch/x86/kvm/hyperv.c | 1 +
 1 file changed, 1 insertion(+)

```
