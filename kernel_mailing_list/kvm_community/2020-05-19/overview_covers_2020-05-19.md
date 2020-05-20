

#### [patch 0/7] x86/KVM: Async #PF and instrumentation protection
##### From: Thomas Gleixner <tglx@linutronix.de>

```c
From patchwork Tue May 19 20:31:28 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Thomas Gleixner <tglx@linutronix.de>
X-Patchwork-Id: 11558807
Return-Path: <SRS0=rCNo=7B=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 38AAB138A
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 19 May 2020 21:14:09 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 2B7D2207D4
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 19 May 2020 21:14:09 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726823AbgESVN3 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 19 May 2020 17:13:29 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:35556 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1725998AbgESVN2 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 19 May 2020 17:13:28 -0400
Received: from Galois.linutronix.de (Galois.linutronix.de
 [IPv6:2a0a:51c0:0:12e:550::1])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id B4412C08C5C0;
        Tue, 19 May 2020 14:13:28 -0700 (PDT)
Received: from p5de0bf0b.dip0.t-ipconnect.de ([93.224.191.11]
 helo=nanos.tec.linutronix.de)
        by Galois.linutronix.de with esmtpsa
 (TLS1.2:DHE_RSA_AES_256_CBC_SHA256:256)
        (Exim 4.80)
        (envelope-from <tglx@linutronix.de>)
        id 1jb9Y2-0001wp-Uy; Tue, 19 May 2020 23:13:15 +0200
Received: from nanos.tec.linutronix.de (localhost [IPv6:::1])
        by nanos.tec.linutronix.de (Postfix) with ESMTP id 75291100D00;
        Tue, 19 May 2020 23:13:14 +0200 (CEST)
Message-Id: <20200519203128.773151484@linutronix.de>
User-Agent: quilt/0.65
Date: Tue, 19 May 2020 22:31:28 +0200
From: Thomas Gleixner <tglx@linutronix.de>
To: LKML <linux-kernel@vger.kernel.org>
Cc: x86@kernel.org, Paolo Bonzini <pbonzini@redhat.com>,
        kvm@vger.kernel.org,
        Alexandre Chartre <alexandre.chartre@oracle.com>,
        Peter Zijlstra <peterz@infradead.org>,
        Juergen Gross <jgross@suse.com>,
        Tom Lendacky <thomas.lendacky@amd.com>
Subject: [patch 0/7] x86/KVM: Async #PF and instrumentation protection
Content-transfer-encoding: 8-bit
X-Linutronix-Spam-Score: -1.0
X-Linutronix-Spam-Level: -
X-Linutronix-Spam-Status: No , -1.0 points, 5.0 required,
  ALL_TRUSTED=-1,SHORTCIRCUIT=-0.0001
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Folks,

this series is the KVM side of the ongoing quest to confine instrumentation
to safe places and ensure that RCU and context tracking state is correct.

The async #PF changes are in the tip tree already as they conflict with the
entry code rework. The minimal set of commits to carry these have been
isolated and tagged:

  git://git.kernel.org/pub/scm/linux/kernel/git/tip/tip.git noinstr-x86-kvm-2020-05-16

Paolo, please pull this into your next branch to avoid conflicts in
next. The prerequisites for the following KVM specific changes come with
that tag so that you have no merge dependencies.

The tag has also been merged into

  git://git.kernel.org/pub/scm/linux/kernel/git/tip/tip.git x86/entry

where the x86 core #PF entry code changes will be queued soon as well.

The KVM specific patches which deal with the RCU and context tracking state
and the protection against instrumentation in sensitive places have been
split out from the larger entry/noinstr series:

  https://lore.kernel.org/r/20200505134112.272268764@linutronix.de

The patches deal with:

  - Placing the guest_enter/exit() calls at the correct place

  - Moving the sensitive VMENTER/EXIT code into the non-instrumentable code
    section.

  - Fixup the tracing code to comply with the non-instrumentation rules

  - Use native functions to access CR2 and the GS base MSR in the critical
    code pathes to prevent them from being instrumented.

The patches apply on top of

   git://git.kernel.org/pub/scm/linux/kernel/git/kvm/kvm.git next

with the noinstr-x86-kvm-2020-05-16 tag from the tip tree merged in.

For reference the whole lot is available from:

   git://git.kernel.org/pub/scm/linux/kernel/git/tglx/devel.git kvm/noinstr

Thanks,

	tglx
---
 include/asm/hardirq.h  |    4 +-
 include/asm/kvm_host.h |    8 +++++
 kvm/svm/svm.c          |   65 ++++++++++++++++++++++++++++++++++------
 kvm/svm/vmenter.S      |    2 -
 kvm/vmx/ops.h          |    4 ++
 kvm/vmx/vmenter.S      |    5 ++-
 kvm/vmx/vmx.c          |   78 ++++++++++++++++++++++++++++++++++++++-----------
 kvm/x86.c              |    4 --
 8 files changed, 137 insertions(+), 33 deletions(-)
```
#### [PATCH v2 0/2] Fix VMX preemption timer migration
##### From: Makarand Sonare <makarandsonare@google.com>

```c
From patchwork Tue May 19 22:22:36 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Makarand Sonare <makarandsonare@google.com>
X-Patchwork-Id: 11558909
Return-Path: <SRS0=rCNo=7B=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 54D86618
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 19 May 2020 22:22:50 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 39859206C3
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 19 May 2020 22:22:50 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=google.com header.i=@google.com
 header.b="Ky/vgy9i"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726352AbgESWWt (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 19 May 2020 18:22:49 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:46468 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1725998AbgESWWt (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 19 May 2020 18:22:49 -0400
Received: from mail-qt1-x84a.google.com (mail-qt1-x84a.google.com
 [IPv6:2607:f8b0:4864:20::84a])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id DE783C061A0F
        for <kvm@vger.kernel.org>; Tue, 19 May 2020 15:22:48 -0700 (PDT)
Received: by mail-qt1-x84a.google.com with SMTP id o16so1396730qto.12
        for <kvm@vger.kernel.org>; Tue, 19 May 2020 15:22:48 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=date:message-id:mime-version:subject:from:to:cc;
        bh=f0KIoB0Jrpqy1aqVVHDit80BlunnGA67Z/eeJuQ0bUo=;
        b=Ky/vgy9iGi3NHsqz0CzOEKfHuhnFxOCWXWL9Q/t7SgvsSU+aPYy4EehBUG3ho4y6t5
         5sX/m5TLaGBtuE1jbNTfQvE0vHJG81D3Tp4DzqTAAt8rIEgZeDbke0eCLCHIQFMVdr+h
         M3Sgl2gGjMDxLCp/s14X7wofGzwfyfWzwcCzCtP/b0fc9RKLpe6iWeevRvjiPt15cwGU
         NrxBNYI/onaNU6TPv+T8Ndq3t7ZPXCeUYDpbtktJrK4GwCkFcaz795IqM+kTQNTW+Cbp
         dj9+kgZkq03IxYJk0eGGHpRkczwZEeVGhM5Y+EHzAMoy8gusCsk1nG4oCb/EUd4Ap4jc
         KVgA==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:date:message-id:mime-version:subject:from:to:cc;
        bh=f0KIoB0Jrpqy1aqVVHDit80BlunnGA67Z/eeJuQ0bUo=;
        b=h4mQJMq6ZiNvZxHWPFU4XaUYMkSlRtzIK1To7RVjGAsgnFg2zNg/10d3wSIQeAZiAP
         7ZCvWVkPcg93j23moznPKDDPVPuEjOK1bn2yN22+QUM0HOep2iLEXJyJ/aLDxLgO/cpo
         q0j/lSVgpEamSC5eZN0+1p4gWYv9yoFaFYRtGYxj1f1lQEmtnypEfG84Anpy0nYB91XP
         Wxs/FjXaqCjMbmBNrS60jYysTXIfvALZDSm2yvnuO8tnFSmZt77Aflo6XMdFrEcMO7k1
         gUA4Wn5Q/E3M6zp12Dz3GsL2Cwigf5lOypnLo8n6o30HpMPzEL2iPjYUX1ug9X2cMQ0f
         j++A==
X-Gm-Message-State: AOAM532rObF9o7tUW8z9KWIht/++e9b8NofrCXQvYSyH8uX6I/uNwMas
        8dd4SpFTT4rfi40ck1JF56V8w1VXwbdwAMEyamZPj2qInjT2t8vKT+A+PhD96CGCkvyf8aM8pgz
        Ks1vrUaL+46NTKR2nfcGdTu8UXZsBBfYWGH9W8M5TFtrzii50AwA29x0ze8kczU3ry9M6aTznBl
        lK30M=
X-Google-Smtp-Source: 
 ABdhPJyg6hgVvW1cYptCRecHaLVCkGCh/ihKSw22K1AJkzZ34y0RFD74sFGl+0d+LmH12jNTiM/ujlnQ0PV8sw7fECyBhg==
X-Received: by 2002:a05:6214:1422:: with SMTP id
 o2mr1981629qvx.13.1589926967823;
 Tue, 19 May 2020 15:22:47 -0700 (PDT)
Date: Tue, 19 May 2020 15:22:36 -0700
Message-Id: <20200519222238.213574-1-makarandsonare@google.com>
Mime-Version: 1.0
X-Mailer: git-send-email 2.26.2.761.g0e0b3e54be-goog
Subject: [PATCH v2 0/2] Fix VMX preemption timer migration
From: Makarand Sonare <makarandsonare@google.com>
To: kvm@vger.kernel.org, pshier@google.com, jmattson@google.com
Cc: Makarand Sonare <makarandsonare@google.com>
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Fix VMX preemption timer migration. Add a selftest to ensure post migration
both L1 and L2 VM observe the VMX preemption timer exit close to the original
expiration deadline.

Makarand Sonare (1):
  KVM: selftests: VMX preemption timer migration test

Peter Shier (1):
  KVM: nVMX: Fix VMX preemption timer migration

 Documentation/virt/kvm/api.rst                |   4 +
 arch/x86/include/uapi/asm/kvm.h               |   3 +
 arch/x86/kvm/vmx/nested.c                     |  56 +++-
 arch/x86/kvm/vmx/vmx.h                        |   1 +
 arch/x86/kvm/x86.c                            |   3 +-
 include/uapi/linux/kvm.h                      |   1 +
 tools/arch/x86/include/uapi/asm/kvm.h         |   1 +
 tools/testing/selftests/kvm/.gitignore        |   1 +
 tools/testing/selftests/kvm/Makefile          |   1 +
 .../testing/selftests/kvm/include/kvm_util.h  |   2 +
 .../selftests/kvm/include/x86_64/processor.h  |  11 +-
 .../selftests/kvm/include/x86_64/vmx.h        |  27 ++
 .../kvm/x86_64/vmx_preemption_timer_test.c    | 257 ++++++++++++++++++
 13 files changed, 357 insertions(+), 11 deletions(-)
 create mode 100644 tools/testing/selftests/kvm/x86_64/vmx_preemption_timer_test.c
---
2.26.2.761.g0e0b3e54be-goog
```
