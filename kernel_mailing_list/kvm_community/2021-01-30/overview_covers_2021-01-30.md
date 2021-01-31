

#### [PATCH v5 00/11] Support disabling TCG on ARM (part 2)
##### From: =?utf-8?q?Philippe_Mathieu-Daud=C3=A9?= <f4bug@amsat.org>

```c
From patchwork Sat Jan 30 01:52:16 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 8bit
X-Patchwork-Submitter: =?utf-8?q?Philippe_Mathieu-Daud=C3=A9?=
 <f4bug@amsat.org>
X-Patchwork-Id: 12056725
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-11.8 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_PATCH,MAILING_LIST_MULTI,
	SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED,USER_AGENT_GIT autolearn=unavailable
	autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 3FA31C433E0
	for <kvm@archiver.kernel.org>; Sat, 30 Jan 2021 01:56:37 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id EE9B064E08
	for <kvm@archiver.kernel.org>; Sat, 30 Jan 2021 01:56:36 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S232683AbhA3B4W (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Fri, 29 Jan 2021 20:56:22 -0500
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:46240 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S232821AbhA3BxV (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 29 Jan 2021 20:53:21 -0500
Received: from mail-wm1-x32d.google.com (mail-wm1-x32d.google.com
 [IPv6:2a00:1450:4864:20::32d])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id E76C7C061574
        for <kvm@vger.kernel.org>; Fri, 29 Jan 2021 17:52:31 -0800 (PST)
Received: by mail-wm1-x32d.google.com with SMTP id c127so8514628wmf.5
        for <kvm@vger.kernel.org>; Fri, 29 Jan 2021 17:52:31 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=sender:from:to:cc:subject:date:message-id:mime-version
         :content-transfer-encoding;
        bh=adQegksKyg6ypqy8yaNY4IxRFUUd8NlguDdBcG0O0Dc=;
        b=Jify+HIvCRI6v2kFDWjTZrLVCkFPKsirwWVmqbOedbFWxEWVegCK8Kfa5vj1pFUxNR
         uVc5o1KEC4qiu0zDMpLGV/D0/60D4MPbPGua/hCXEYPst1Gv7htKhNx4uEL6eT4mq1+u
         xrIxvT+4cmFzEtGbbarSXi7wPPUsqpBBh2xGR088evTJQDO5hPAkzcAnHItmWFdxuCtm
         th5XWIsnQ2N49bSnJC6+lJtaNE46hgI0naP5dMuR0EKp4QP815M06UqGrxn62rOTX72K
         b4eZU7IMeR8PULGxqjQi4Df8MG49oURxPLIda+TTg4pBpWCFlHieW7lxwh/2o1n0irDR
         eUhg==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:sender:from:to:cc:subject:date:message-id
         :mime-version:content-transfer-encoding;
        bh=adQegksKyg6ypqy8yaNY4IxRFUUd8NlguDdBcG0O0Dc=;
        b=a5hAFV+bwK1TJ4PYjDMtL5PEPdLLRzLmktvxjokfGaxGghLxhQoaJLQ9O8UQ2agVul
         yIoFVBGmJEo8cj3NXx31LEU5XNkXLE1dVuQtitTTB5DZRZ6J0UVAmvxBfEgORK8Z7mI7
         cDVr5VIZy2HAWZvK21Fq36FMNpkSQ6O7N2QTHgquqTAot3Kqi7pWwmpM2yoeWtUEwCs8
         0t2vfmy7PslggSWqdvJvC0maFkiqu7L8ebAaMSG1GXfE1ncmpgHs+wya1r+WzKhS1fER
         WS0j7SaEPnfh0STA3OoCjCWAmtmV/JNa750c0YQgovNidZtwIFqUUQEgAVIRrmlYVVuk
         Uzpw==
X-Gm-Message-State: AOAM531wulKHptTp9DyooAp6KIUb+W6nWr/pHyzYq86Ia9ydgYsBnArp
        ehRXqDtFVBLqDoVNCxo3vG4=
X-Google-Smtp-Source: 
 ABdhPJzAZ1zraX1+wErsQAoxLg/4/5cge/k+zf+9AXuQRmCgsUUA0TAkV3aDzuzdcsuTqEd2pjPmTg==
X-Received: by 2002:a1c:b087:: with SMTP id
 z129mr1504698wme.147.1611971550627;
        Fri, 29 Jan 2021 17:52:30 -0800 (PST)
Received: from localhost.localdomain (13.red-83-57-169.dynamicip.rima-tde.net.
 [83.57.169.13])
        by smtp.gmail.com with ESMTPSA id
 e4sm15520107wrw.96.2021.01.29.17.52.28
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Fri, 29 Jan 2021 17:52:29 -0800 (PST)
Sender: =?utf-8?q?Philippe_Mathieu-Daud=C3=A9?=
  <philippe.mathieu.daude@gmail.com>
From: =?utf-8?q?Philippe_Mathieu-Daud=C3=A9?= <f4bug@amsat.org>
To: qemu-devel@nongnu.org
Cc: Richard Henderson <richard.henderson@linaro.org>, kvm@vger.kernel.org,
 Peter Maydell <peter.maydell@linaro.org>, Fam Zheng <fam@euphon.net>,
 Thomas Huth <thuth@redhat.com>, Paolo Bonzini <pbonzini@redhat.com>,
	=?utf-8?q?Philippe_Mathieu-Daud=C3=A9?= <philmd@redhat.com>,
 Richard Henderson <rth@twiddle.net>, Claudio Fontana <cfontana@suse.de>,
	=?utf-8?q?Alex_Benn=C3=A9e?= <alex.bennee@linaro.org>, qemu-arm@nongnu.org,
	=?utf-8?q?Philippe_Mathieu-Daud=C3=A9?= <f4bug@amsat.org>
Subject: [PATCH v5 00/11] Support disabling TCG on ARM (part 2)
Date: Sat, 30 Jan 2021 02:52:16 +0100
Message-Id: <20210130015227.4071332-1-f4bug@amsat.org>
X-Mailer: git-send-email 2.26.2
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Cover from Samuel Ortiz from (part 1) [1]:

  This patchset allows for building and running ARM targets with TCG
  disabled. [...]

  The rationale behind this work comes from the NEMU project where we're
  trying to only support x86 and ARM 64-bit architectures, without
  including the TCG code base. We can only do so if we can build and run
  ARM binaries with TCG disabled.

v5:
- addressed Paolo/Richard/Thomas review comments from v4 [5].

v4 almost 2 years later... [2]:
- Rebased on Meson
- Addressed Richard review comments
- Addressed Claudio review comments

v3 almost 18 months later [3]:
- Rebased
- Addressed Thomas review comments
- Added Travis-CI job to keep building --disable-tcg on ARM

v2 [4]:
- Addressed review comments from Richard and Thomas from v1 [1]

Regards,

Phil.

[1]: https://lists.gnu.org/archive/html/qemu-devel/2018-11/msg02451.html
[2]: https://www.mail-archive.com/qemu-devel@nongnu.org/msg689168.html
[3]: https://www.mail-archive.com/qemu-devel@nongnu.org/msg641796.html
[4]: https://lists.gnu.org/archive/html/qemu-devel/2019-08/msg05003.html
[5]: https://www.mail-archive.com/qemu-devel@nongnu.org/msg746041.html

Philippe Mathieu-Daudé (9):
  exec: Restrict TCG specific headers
  default-configs: Remove unnecessary SEMIHOSTING selection
  target/arm: Restrict ARMv4 cpus to TCG accel
  target/arm: Restrict ARMv5 cpus to TCG accel
  target/arm: Restrict ARMv6 cpus to TCG accel
  target/arm: Restrict ARMv7 R-profile cpus to TCG accel
  target/arm: Restrict ARMv7 M-profile cpus to TCG accel
  target/arm: Reorder meson.build rules
  .travis.yml: Add a KVM-only Aarch64 job

Samuel Ortiz (1):
  target/arm: Do not build TCG objects when TCG is off

Thomas Huth (1):
  target/arm: Make m_helper.c optional via CONFIG_ARM_V7M

 default-configs/devices/aarch64-softmmu.mak |  1 -
 default-configs/devices/arm-softmmu.mak     | 28 --------
 include/exec/helper-proto.h                 |  2 +
 target/arm/cpu.h                            | 12 ----
 hw/arm/realview.c                           |  7 +-
 target/arm/cpu_tcg.c                        |  4 +-
 target/arm/helper.c                         |  7 --
 target/arm/m_helper-stub.c                  | 73 +++++++++++++++++++++
 .travis.yml                                 | 32 +++++++++
 hw/arm/Kconfig                              | 66 +++++++++++++++++--
 target/arm/meson.build                      | 28 +++++---
 11 files changed, 196 insertions(+), 64 deletions(-)
 create mode 100644 target/arm/m_helper-stub.c
```
