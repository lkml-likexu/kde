

#### [PATCH 0/3] x86/KVM/VMX: Introduce and use try_cmpxchg64()
##### From: Uros Bizjak <ubizjak@gmail.com>

```c
From patchwork Tue Dec 15 18:28:02 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Uros Bizjak <ubizjak@gmail.com>
X-Patchwork-Id: 11975597
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-10.7 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,DKIM_VALID_AU,FREEMAIL_FORGED_FROMDOMAIN,FREEMAIL_FROM,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,
	SPF_PASS,URIBL_BLOCKED,USER_AGENT_GIT autolearn=unavailable
	autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 34DA7C2BBCA
	for <kvm@archiver.kernel.org>; Tue, 15 Dec 2020 18:33:59 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 0673022B4B
	for <kvm@archiver.kernel.org>; Tue, 15 Dec 2020 18:33:59 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1731657AbgLOScl (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 15 Dec 2020 13:32:41 -0500
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:51232 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1731227AbgLOS3a (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 15 Dec 2020 13:29:30 -0500
Received: from mail-ej1-x642.google.com (mail-ej1-x642.google.com
 [IPv6:2a00:1450:4864:20::642])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 2C0B2C061257;
        Tue, 15 Dec 2020 10:28:16 -0800 (PST)
Received: by mail-ej1-x642.google.com with SMTP id w1so24451436ejf.11;
        Tue, 15 Dec 2020 10:28:16 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=from:to:cc:subject:date:message-id:mime-version
         :content-transfer-encoding;
        bh=j5Nx3QP2QUef7kqAsxxArhCJKbbh/sB4VAtuIgHpzAY=;
        b=Gt7wfw6zKOz9640y+Pkyf7QD3YEYbL7AQxcBqBO+4SznKXSUJ40g+lwnP5nWJwL2gr
         vWCstbyjibsJ8zQNhOazJEfK2f5z18NyuSluEErqBgrAv/3/4RZ/ZWP8XqNHszdV0Xkn
         cd44ru/YuoUualt+VyBZIoC6mpTMCYHyeygE5SN4ltcm6YMbvHIvA3pHEWankX8GZRmM
         cZJMljLFsGlnnaUhVSFQFz+uUEcpoVQKYFohpydv5SosJh7S/5pXymYeJW8mgYQE/0+X
         0PHOpoMPxSRr3qtOVxjIUZmtfLLGRiLl4Irv1THjXn0SHQDPNvxPs+JPO27jzgW4pb/T
         54vQ==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:mime-version
         :content-transfer-encoding;
        bh=j5Nx3QP2QUef7kqAsxxArhCJKbbh/sB4VAtuIgHpzAY=;
        b=I9SXv/yUbLFn9yya9or8VVc7yB6BBB4K+A+gg/WREW0slRuLaBc9LTT24Msz2S6Ssg
         YaKr/4NBdoCPsqEMzSWps49/WZ9gIh5d5K2sDUDNBXlc6xT3OZSnWbSIfpxB1Fu+faA7
         Ap2xxxzdcJ8uT0j/1Qn9xgU3tvdpxRfRyyFgHANKuw8Gm3OVx0It2NhvRv89CXJJuBgs
         Bc2xBuwRDFTQlntZCNgdSWUPJTvppsopwWZb49+2u3Q4lj7+JADrpalA5RAqC6gzKS5u
         xv6VszMbJ8W7YmZ5LjPLJXf3em0Qn7w1ub5825tlszbJiFwaT50qCCwqwDi7XyrWf0tz
         bbgg==
X-Gm-Message-State: AOAM532ssfylyL7gxnMhjwBoEoXs1I7tmS9/AHu5f8wNDe/xjorOnqoX
        ytmkUZuu36vVsR82vVC8rTE=
X-Google-Smtp-Source: 
 ABdhPJzgkJG3I3krAxjW5y1BK0JBdUBsjzDb5RiaXrUm2dscx5+KLiZP/Q5jBAn6KDXflPv29Viqdg==
X-Received: by 2002:a17:906:ce21:: with SMTP id
 sd1mr27506527ejb.396.1608056894785;
        Tue, 15 Dec 2020 10:28:14 -0800 (PST)
Received: from localhost.localdomain (93-103-18-160.static.t-2.net.
 [93.103.18.160])
        by smtp.gmail.com with ESMTPSA id
 r21sm7369228eds.91.2020.12.15.10.28.13
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Tue, 15 Dec 2020 10:28:14 -0800 (PST)
From: Uros Bizjak <ubizjak@gmail.com>
To: x86@kernel.org, kvm@vger.kernel.org, linux-kernel@vger.kernel.org
Cc: Uros Bizjak <ubizjak@gmail.com>, Will Deacon <will@kernel.org>,
        Peter Zijlstra <peterz@infradead.org>,
        Boqun Feng <boqun.feng@gmail.com>,
        Thomas Gleixner <tglx@linutronix.de>,
        Ingo Molnar <mingo@redhat.com>, Borislav Petkov <bp@alien8.de>,
        "H. Peter Anvin" <hpa@zytor.com>,
        Paolo Bonzini <pbonzini@redhat.com>,
        Sean Christopherson <seanjc@google.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>
Subject: [PATCH 0/3] x86/KVM/VMX: Introduce and use try_cmpxchg64()
Date: Tue, 15 Dec 2020 19:28:02 +0100
Message-Id: <20201215182805.53913-1-ubizjak@gmail.com>
X-Mailer: git-send-email 2.26.2
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This patch series introduces try_cmpxchg64() atomic locking function.

try_cmpxchg64() provides the same interface for 64 bit and 32 bit targets,
emits CMPXCHGQ for 64 bit targets and CMPXCHG8B for 32 bit targets,
and provides appropriate fallbacks when CMPXCHG8B is unavailable.

try_cmpxchg64() reuses flags from CMPXCHGQ/CMPXCHG8B instructions and
avoids unneeded CMP for 64 bit targets or XOR/XOR/OR sequence for
32 bit targets.

Cc: Will Deacon <will@kernel.org>
Cc: Peter Zijlstra <peterz@infradead.org>
Cc: Boqun Feng <boqun.feng@gmail.com>
Cc: Thomas Gleixner <tglx@linutronix.de>
Cc: Ingo Molnar <mingo@redhat.com>
Cc: Borislav Petkov <bp@alien8.de>
Cc: "H. Peter Anvin" <hpa@zytor.com>
Cc: Paolo Bonzini <pbonzini@redhat.com>
Cc: Sean Christopherson <seanjc@google.com>
Cc: Vitaly Kuznetsov <vkuznets@redhat.com>
Cc: Wanpeng Li <wanpengli@tencent.com>
Cc: Jim Mattson <jmattson@google.com>
Cc: Joerg Roedel <joro@8bytes.org>

Uros Bizjak (3):
  asm-generic/atomic: Add try_cmpxchg64() instrumentation
  locking/atomic/x86: Introduce arch_try_cmpxchg64()
  KVM/VMX: Use try_cmpxchg64() in posted_intr.c

 arch/x86/include/asm/cmpxchg_32.h         | 62 +++++++++++++++++++----
 arch/x86/include/asm/cmpxchg_64.h         |  6 +++
 arch/x86/kvm/vmx/posted_intr.c            |  9 ++--
 include/asm-generic/atomic-instrumented.h | 46 ++++++++++++++++-
 scripts/atomic/gen-atomic-instrumented.sh |  2 +-
 5 files changed, 108 insertions(+), 17 deletions(-)
```
#### [PATCH v2 00/24] target/mips: Convert MSA ASE to decodetree
##### From: =?utf-8?q?Philippe_Mathieu-Daud=C3=A9?= <f4bug@amsat.org>

```c
From patchwork Tue Dec 15 22:57:33 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 8bit
X-Patchwork-Submitter: =?utf-8?q?Philippe_Mathieu-Daud=C3=A9?=
 <f4bug@amsat.org>
X-Patchwork-Id: 11975909
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.8 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_PATCH,MAILING_LIST_MULTI,
	MENTIONS_GIT_HOSTING,SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED,USER_AGENT_GIT
	autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 4F6D2C4361B
	for <kvm@archiver.kernel.org>; Tue, 15 Dec 2020 22:58:49 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 11D2922573
	for <kvm@archiver.kernel.org>; Tue, 15 Dec 2020 22:58:49 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727704AbgLOW6n (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 15 Dec 2020 17:58:43 -0500
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:37564 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1727068AbgLOW6m (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 15 Dec 2020 17:58:42 -0500
Received: from mail-ej1-x629.google.com (mail-ej1-x629.google.com
 [IPv6:2a00:1450:4864:20::629])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 7EBC5C0613D3
        for <kvm@vger.kernel.org>; Tue, 15 Dec 2020 14:58:01 -0800 (PST)
Received: by mail-ej1-x629.google.com with SMTP id j22so12047630eja.13
        for <kvm@vger.kernel.org>; Tue, 15 Dec 2020 14:58:01 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=sender:from:to:cc:subject:date:message-id:mime-version
         :content-transfer-encoding;
        bh=XTmTU+I/QeMhja7w9GBCfSdZSiPSigvZOhS987dRJBo=;
        b=oLimqBnxuZ+ao84nN51By9sR65R1eDdf2BZhI5VRg1r+POA1uoJ4yBdwG1eJAvQFZy
         FFr5DVpTqFA0XzgvL2eMlOiyF/VKAZNEHVsK3EYX7AyjtPCDvlL9qeAsSZXVv8aT1RPt
         75HXpCGE1FFe4NRbNP64DXn8giZvtzdbmSJEy5BZNxIpJzJQWUjBA14GanuHOx0SsjAs
         tYu0auLQhExF1bItOUkAFFBv2uYsP60I//0Dc6jeIFr5ms02vzHi32TvIMbhTMLW4OLC
         rkSo8PheSiJs7KHdCw7+vdTnfg9yTZMK1uzI6885ZRZjZD+C7eyjIYm7hvdx61mKGVB0
         uylw==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:sender:from:to:cc:subject:date:message-id
         :mime-version:content-transfer-encoding;
        bh=XTmTU+I/QeMhja7w9GBCfSdZSiPSigvZOhS987dRJBo=;
        b=PYfUibu5YeH5JLkkPrPuI0pW1YuaCFPVWV8vlY7msyVZ/8FDmJBnP6Ar+6xayJEZBh
         vpObczgXqVVLFSro3kdgJ2KPW7tEzVOk/fhUGpLxC6m4bw4DQrFFjG6c1JtNX2xIQZKZ
         2tGTmMVZKP0INS0RyszO+JN1YqOS4K9fFhLj3I34RoQJBxa0GHoPzPvJ5Wn1h0BYpVcO
         j/LzEXREEhD9ZCaw3PQzXG+u9z7xQd+ZBRZNRwtwm9oDW+PvMH5QSCMdqE+ivWCXaDjY
         OlRJzFIi1s6YtV41ZrQoZjQdox1o0VGLUiSfNZZWXLZtzUOcD+8k1lEcKXs0JxhZuqdN
         TO4Q==
X-Gm-Message-State: AOAM531YCuAZHhqeetoPrJ/hy+XxDe1AmnURIBMPPhEqbrNMew4yZWnU
        Yx2Ammrk+nchSpeKUrzbYt6kP8i3WVQMsQ==
X-Google-Smtp-Source: 
 ABdhPJwyuY0SMLuZ8mv7Kg7MS1wODirFHVtTRpqubaTxWcwvu6I18YNN2a8WCyVz7eRcENkMSDW5Xw==
X-Received: by 2002:a17:906:e8b:: with SMTP id
 p11mr18861695ejf.92.1608073080221;
        Tue, 15 Dec 2020 14:58:00 -0800 (PST)
Received: from x1w.redhat.com (101.red-88-21-206.staticip.rima-tde.net.
 [88.21.206.101])
        by smtp.gmail.com with ESMTPSA id
 o13sm19168231edr.94.2020.12.15.14.57.58
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Tue, 15 Dec 2020 14:57:59 -0800 (PST)
Sender: =?utf-8?q?Philippe_Mathieu-Daud=C3=A9?=
  <philippe.mathieu.daude@gmail.com>
From: =?utf-8?q?Philippe_Mathieu-Daud=C3=A9?= <f4bug@amsat.org>
To: Richard Henderson <richard.henderson@linaro.org>,
        qemu-devel@nongnu.org
Cc: kvm@vger.kernel.org, Aleksandar Rikalo <aleksandar.rikalo@syrmia.com>,
 Paolo Bonzini <pbonzini@redhat.com>, Aurelien Jarno <aurelien@aurel32.net>,
 Jiaxun Yang <jiaxun.yang@flygoat.com>, =?utf-8?q?Philippe_Mathieu-Daud?=
	=?utf-8?q?=C3=A9?= <f4bug@amsat.org>, Huacai Chen <chenhuacai@kernel.org>
Subject: [PATCH v2 00/24] target/mips: Convert MSA ASE to decodetree
Date: Tue, 15 Dec 2020 23:57:33 +0100
Message-Id: <20201215225757.764263-1-f4bug@amsat.org>
X-Mailer: git-send-email 2.26.2
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Missing review: 1-3 14 17 19-24

Since v1:
- rebased
- addressed Richard review comments
- reworded some commit descriptions
- avoid 64-bit ifdef'ry

Finally, we use decodetree with the MIPS target.

Starting easy with the MSA ASE. 2700+ lines extracted
from helper.h and translate.c, now built as an new
object: mod-msa_translate.o.

Phil.

Available:
  https://gitlab.com/philmd/qemu/-/commits/mips_msa_decodetree_v2

Based-on: <20201214183739.500368-1-f4bug@amsat.org>

Philippe Mathieu-Daudé (24):
  target/mips/translate: Extract decode_opc_legacy() from decode_opc()
  target/mips/translate: Expose check_mips_64() to 32-bit mode
  target/mips/cpu: Introduce isa_rel6_available() helper
  target/mips: Introduce ase_msa_available() helper
  target/mips: Simplify msa_reset()
  target/mips: Use CP0_Config3 to set MIPS_HFLAG_MSA
  target/mips: Simplify MSA TCG logic
  target/mips: Remove now unused ASE_MSA definition
  target/mips: Alias MSA vector registers on FPU scalar registers
  target/mips: Extract msa_translate_init() from mips_tcg_init()
  target/mips: Remove CPUMIPSState* argument from gen_msa*() methods
  target/mips: Explode gen_msa_branch() as gen_msa_BxZ_V/BxZ()
  target/mips: Rename msa_helper.c as mod-msa_helper.c
  target/mips: Move msa_reset() to mod-msa_helper.c
  target/mips: Extract MSA helpers from op_helper.c
  target/mips: Extract MSA helper definitions
  target/mips: Declare gen_msa/_branch() in 'translate.h'
  target/mips: Extract MSA translation routines
  target/mips: Introduce decode tree bindings for MSA opcodes
  target/mips: Use decode_ase_msa() generated from decodetree
  target/mips: Extract LSA/DLSA translation generators
  target/mips: Introduce decodetree helpers for MSA LSA/DLSA opcodes
  target/mips: Introduce decodetree helpers for Release6 LSA/DLSA
    opcodes
  target/mips/mod-msa: Pass TCGCond argument to gen_check_zero_element()

 target/mips/cpu.h                             |    7 +
 target/mips/helper.h                          |  436 +--
 target/mips/internal.h                        |    4 +-
 target/mips/mips-defs.h                       |    1 -
 target/mips/translate.h                       |   25 +-
 target/mips/isa-mips32r6.decode               |   17 +
 target/mips/isa-mips64r6.decode               |   17 +
 target/mips/mod-msa32.decode                  |   28 +
 target/mips/mod-msa64.decode                  |   17 +
 target/mips/cpu.c                             |   14 +-
 target/mips/isa-mips_rel6_translate.c         |   37 +
 target/mips/kvm.c                             |   12 +-
 .../mips/{msa_helper.c => mod-msa_helper.c}   |  429 +++
 target/mips/mod-msa_translate.c               | 2286 ++++++++++++++++
 target/mips/op_helper.c                       |  394 ---
 target/mips/translate.c                       | 2352 +----------------
 target/mips/translate_addr_const.c            |   52 +
 target/mips/cpu-defs.c.inc                    |   40 +-
 target/mips/meson.build                       |   14 +-
 target/mips/mod-msa_helper.h.inc              |  443 ++++
 20 files changed, 3437 insertions(+), 3188 deletions(-)
 create mode 100644 target/mips/isa-mips32r6.decode
 create mode 100644 target/mips/isa-mips64r6.decode
 create mode 100644 target/mips/mod-msa32.decode
 create mode 100644 target/mips/mod-msa64.decode
 create mode 100644 target/mips/isa-mips_rel6_translate.c
 rename target/mips/{msa_helper.c => mod-msa_helper.c} (93%)
 create mode 100644 target/mips/mod-msa_translate.c
 create mode 100644 target/mips/translate_addr_const.c
 create mode 100644 target/mips/mod-msa_helper.h.inc
```
