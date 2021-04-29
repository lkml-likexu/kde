

#### [PATCH 0/2] vDPA/ifcvf: implement doorbell mapping feature
##### From: Zhu Lingshan <lingshan.zhu@intel.com>

```c
From patchwork Wed Apr 28 08:21:31 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: "Zhu, Lingshan" <lingshan.zhu@intel.com>
X-Patchwork-Id: 12228341
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-11.8 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,
	SPF_PASS,USER_AGENT_GIT autolearn=unavailable autolearn_force=no
 version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id E1D8BC43462
	for <kvm@archiver.kernel.org>; Wed, 28 Apr 2021 08:27:00 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id A536561428
	for <kvm@archiver.kernel.org>; Wed, 28 Apr 2021 08:27:00 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S237390AbhD1I1m (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Wed, 28 Apr 2021 04:27:42 -0400
Received: from mga04.intel.com ([192.55.52.120]:7991 "EHLO mga04.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S231635AbhD1I1l (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 28 Apr 2021 04:27:41 -0400
IronPort-SDR: 
 GV4zPRzt18lYSfuj9k66bqi1VfLDjUDe5Skko7GPdtucHOsB/B30Vssloj6UGFCki9fnTXBbm6
 mkz6etNK3XfA==
X-IronPort-AV: E=McAfee;i="6200,9189,9967"; a="194573420"
X-IronPort-AV: E=Sophos;i="5.82,257,1613462400";
   d="scan'208";a="194573420"
Received: from orsmga008.jf.intel.com ([10.7.209.65])
  by fmsmga104.fm.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 28 Apr 2021 01:26:57 -0700
IronPort-SDR: 
 YjGMFsJNq223qMC1ebGzPDpsavJXVWkcNwLS/EBYCkjZqq73lfcboVBxk14WyFJsMokTj3hoa6
 05bwGXoyJTiw==
X-IronPort-AV: E=Sophos;i="5.82,257,1613462400";
   d="scan'208";a="430192218"
Received: from unknown (HELO localhost.localdomain.bj.intel.com)
 ([10.240.193.73])
  by orsmga008-auth.jf.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 28 Apr 2021 01:26:53 -0700
From: Zhu Lingshan <lingshan.zhu@intel.com>
To: jasowang@redhat.com, mst@redhat.com
Cc: virtualization@lists.linux-foundation.org, netdev@vger.kernel.org,
        kvm@vger.kernel.org, linux-kernel@vger.kernel.org,
        Zhu Lingshan <lingshan.zhu@intel.com>
Subject: [PATCH 0/2] vDPA/ifcvf: implement doorbell mapping feature
Date: Wed, 28 Apr 2021 16:21:31 +0800
Message-Id: <20210428082133.6766-1-lingshan.zhu@intel.com>
X-Mailer: git-send-email 2.27.0
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This series implements doorbell mapping feature for ifcvf.

Please help review

Thanks!

Zhu Lingshan (2):
  vDPA/ifcvf: record virtio notify base
  vDPA/ifcvf: implement doorbell mapping for ifcvf

 drivers/vdpa/ifcvf/ifcvf_base.c |  1 +
 drivers/vdpa/ifcvf/ifcvf_base.h |  1 +
 drivers/vdpa/ifcvf/ifcvf_main.c | 18 ++++++++++++++++++
 3 files changed, 20 insertions(+)
```
#### [kvm-unit-tests PATCH v1 0/4] enable LPI and ITS for TCG
  [PATCH v2 0/8] GICv3 LPI and ITS feature implementation
##### From: =?utf-8?q?Alex_Benn=C3=A9e?= <alex.bennee@linaro.org>
  From: Shashi Mallela <shashi.mallela@linaro.org>

```c
From patchwork Wed Apr 28 10:18:40 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 8bit
X-Patchwork-Submitter: =?utf-8?q?Alex_Benn=C3=A9e?= <alex.bennee@linaro.org>
X-Patchwork-Id: 12228499
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-13.8 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT autolearn=ham
	autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 658F7C43462
	for <kvm@archiver.kernel.org>; Wed, 28 Apr 2021 10:18:49 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 2EF9A613F8
	for <kvm@archiver.kernel.org>; Wed, 28 Apr 2021 10:18:49 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S239198AbhD1KTd (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Wed, 28 Apr 2021 06:19:33 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:34508 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S239179AbhD1KTc (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 28 Apr 2021 06:19:32 -0400
Received: from mail-wm1-x333.google.com (mail-wm1-x333.google.com
 [IPv6:2a00:1450:4864:20::333])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 50E19C061574
        for <kvm@vger.kernel.org>; Wed, 28 Apr 2021 03:18:47 -0700 (PDT)
Received: by mail-wm1-x333.google.com with SMTP id
 a22-20020a05600c2256b029014294520f18so4144123wmm.1
        for <kvm@vger.kernel.org>; Wed, 28 Apr 2021 03:18:47 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=linaro.org; s=google;
        h=from:to:cc:subject:date:message-id:mime-version
         :content-transfer-encoding;
        bh=PKGDTgiVcM/lQ6iRrmAsUOi9EArz4u3h1iRq434eRSA=;
        b=KR9NTcMYjJQLFeqrQ2TR6ifAqSo99rz39UJx//d3x6y1Dy1pWofUW08E+LT0G8mVAu
         1IM32Pw4NlYnD+xTg/GD6c9VGP7xlLlG9Y2F8puVHsRfS6nDxFa18AxQoLHqOEEiDhFD
         CYUxDhIHvSkLOYmsljUOkO0Pc96WjOXotVbjEexdG/4GSmx91wy1wz3Yo5tqu5m7YE+z
         0ZaBAmhS4XQ54zJmw/RMOXvBqZhFFJ8zXcLcP4QHA4ByKgyzYDoGTPRNb/OtE5I0ZTTr
         nSsnifL9HuaMPbTmyJO09WDgQ3PpZisNvjT6fIKEq7wyFN0EhJEa3+WDeIHyObwh4Rvu
         UZxQ==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:mime-version
         :content-transfer-encoding;
        bh=PKGDTgiVcM/lQ6iRrmAsUOi9EArz4u3h1iRq434eRSA=;
        b=lyfRZq+cyOCGBrKO8h4MCQbIY4QdiEXBkZirr+Ysec3xhIAb8jINPkV6egKmQtO4Li
         wQP7ZfUSkuABex09B+5PiPMiwGSB9pJ0sF7066dyouRTgSEcQ1lChpvIVf++83JGC3Q2
         aPUdrkc0FwAAUnfPsI/b+B7tYC2u7lE+YElWPWJItl5Mz+j4Usi3Zyo/59q1ANqIUtH5
         I9p0hap3k66OXnQV1TcNEWKxPyV4sVv9ayWW0Bv70nFtjs6lsUSPZt/2q+dflqGObFZz
         NvUYi9C1HiDSBUgJqwks5zOpoC7fVepCa2WLCSJoVb3tRGXAqFJYS3Tht077ke4ZWH+/
         CTdg==
X-Gm-Message-State: AOAM531MX94S1QrpeLlzUAaRE45sUWrGsZBOglHibKKuoDU8fmDjR8ye
        SkfKE+V8GqYkoKS7PVyQ7Oa0IA==
X-Google-Smtp-Source: 
 ABdhPJzL3juJCDl3XA6F0deoJp88yUP3zghVWwtGs9VLwPOsZipRSr61EUnv0vcux7XC7IERZPmCgQ==
X-Received: by 2002:a05:600c:228a:: with SMTP id
 10mr30822102wmf.115.1619605126000;
        Wed, 28 Apr 2021 03:18:46 -0700 (PDT)
Received: from zen.linaroharston ([51.148.130.216])
        by smtp.gmail.com with ESMTPSA id
 l14sm7760562wrv.94.2021.04.28.03.18.44
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Wed, 28 Apr 2021 03:18:44 -0700 (PDT)
Received: from zen.lan (localhost [127.0.0.1])
        by zen.linaroharston (Postfix) with ESMTP id 1B26B1FF7E;
        Wed, 28 Apr 2021 11:18:44 +0100 (BST)
From: =?utf-8?q?Alex_Benn=C3=A9e?= <alex.bennee@linaro.org>
To: kvm@vger.kernel.org
Cc: shashi.mallela@linaro.org, alexandru.elisei@arm.com,
 eric.auger@redhat.com, qemu-arm@nongnu.org,
 linux-arm-kernel@lists.infradead.org, kvmarm@lists.cs.columbia.edu,
 christoffer.dall@arm.com, maz@kernel.org,
 =?utf-8?q?Alex_Benn=C3=A9e?= <alex.bennee@linaro.org>
Subject: [kvm-unit-tests PATCH v1 0/4] enable LPI and ITS for TCG
Date: Wed, 28 Apr 2021 11:18:40 +0100
Message-Id: <20210428101844.22656-1-alex.bennee@linaro.org>
X-Mailer: git-send-email 2.20.1
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This is a companion to Shashi's series enabling LPI and ITS features
for QEMU's TCG emulation. This is part of our push for a sbsa-ref
platform which needs a more modern set of features.

  From: Shashi Mallela <shashi.mallela@linaro.org>
  Subject: [PATCH v2 0/8] GICv3 LPI and ITS feature implementation
  Date: Wed, 31 Mar 2021 22:41:44 -0400
  Message-Id: <20210401024152.203896-1-shashi.mallela@linaro.org>

Most of the changes are minor except the its-trigger test which skips
invall handling checks which I think is relying on IMPDEF behaviour
which we can't probe for. There is also a hilarious work around to
some limitations in the run_migration() script in the last patch.

Alex Bennée (4):
  arm64: split its-trigger test into KVM and TCG variants
  scripts/arch-run: don't use deprecated server/nowait options
  arm64: enable its-migration tests for TCG
  arm64: split its-migrate-unmapped-collection into KVM and TCG variants

 scripts/arch-run.bash |  4 +--
 arm/gic.c             | 67 ++++++++++++++++++++++++++-----------------
 arm/unittests.cfg     | 23 ++++++++++++---
 3 files changed, 62 insertions(+), 32 deletions(-)
```
#### [PATCH v2 0/6] KVM: x86: Use kernel x86 cpuid utilities in KVM
##### From: Ricardo Koller <ricarkol@google.com>

```c
From patchwork Wed Apr 28 19:37:50 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Ricardo Koller <ricarkol@google.com>
X-Patchwork-Id: 12229977
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-21.3 required=3.0 tests=BAYES_00,DKIMWL_WL_MED,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT,
	USER_IN_DEF_DKIM_WL autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 45507C433ED
	for <kvm@archiver.kernel.org>; Wed, 28 Apr 2021 19:38:24 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 06AA161151
	for <kvm@archiver.kernel.org>; Wed, 28 Apr 2021 19:38:23 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S241876AbhD1TjB (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Wed, 28 Apr 2021 15:39:01 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:46058 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S241840AbhD1Ti6 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 28 Apr 2021 15:38:58 -0400
Received: from mail-yb1-xb4a.google.com (mail-yb1-xb4a.google.com
 [IPv6:2607:f8b0:4864:20::b4a])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 7F982C061573
        for <kvm@vger.kernel.org>; Wed, 28 Apr 2021 12:38:02 -0700 (PDT)
Received: by mail-yb1-xb4a.google.com with SMTP id
 l17-20020a25ad510000b02904ee2dd236d5so6963127ybe.18
        for <kvm@vger.kernel.org>; Wed, 28 Apr 2021 12:38:02 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=date:message-id:mime-version:subject:from:to:cc;
        bh=6lY0wVxKSFoGmS9bVqfbfPkbINkSpYIK0/Bfq4EeuDU=;
        b=UHp/r+M7gHphcpiU1e7jr9u5gX7d0CIPQhlJzPJs034WaUGDGPnQ5PWWpQjxogK9jR
         gRV2eCkUHTvUiuwFj08bK1QVFGzZKdIm/cxyZeoimqYttKlPB2BbBvam4admXBTXw7Cb
         N8/u+1A+HNsv8z7rqATlxasT/vEyQqwmg0wKHPT0GOaXCpjifjz7BPfscAqXv0tPFgkY
         DdXDtrSOsQgTbIzh9Nb9bn53/ZG8gorrB0YoK08kKJBz/uGhw/BOD1AhCuRHyDa4R8jt
         kiNi7SB6DEdr6n/oVZ7YoxoMni0C7Zl9c5/nmXuzpoWJ7mlUeetO7QM5xKNMYbgB8f+D
         rZkA==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:date:message-id:mime-version:subject:from:to:cc;
        bh=6lY0wVxKSFoGmS9bVqfbfPkbINkSpYIK0/Bfq4EeuDU=;
        b=kGQBQmoBt8s0aH4BpkHTDATnIL47R/ZJZxEq/KYAOT6t/QzF7FqUSoEYGO2qRuuM1u
         kicHoE6zQcu0YJrYKD5cCZhZHWnWlaph5eDBVGuluxfgdDnHSxCPWju/JGB5PlZjblXX
         9Z+190NIbf1O0h+nKoF1l8/OBtz2Aegcl4jkkmEzLSXGxKAXgjPOhZ3Q/AAE8KWsTxtQ
         jeQdP1dxBvSyBvPbUB1TNowB7360bFJZuK5Mi0ZtSg9BDPqTNu0poVPCvfJS2VDBAsjS
         ATPlTMP5yTDUF/chhKT2hCtDo/eS/cFMiVYigeLnrOzg5I2BHHOgqFgkjylp7rv8PP86
         M1zQ==
X-Gm-Message-State: AOAM531egIlIYxpmxCpPYlA+ngB0fu5w9se/vekIg9b081m2sPCM/s8t
        r0yW/R5bFubZ6mrSMrTUOgkLYxfXcalkoQ==
X-Google-Smtp-Source: 
 ABdhPJwBsfmNpvwW8rlmlnImBF6/Yn0bEE8RY/muQwjlhKwnzdbXRK8OsoZ5gVqEj7Y4ZZ66XeKQEI7IUq38XA==
X-Received: from ricarkol2.c.googlers.com
 ([fda3:e722:ac3:10:24:72f4:c0a8:62fe])
 (user=ricarkol job=sendgmr) by 2002:a25:99c1:: with SMTP id
 q1mr40283071ybo.517.1619638681487; Wed, 28 Apr 2021 12:38:01 -0700 (PDT)
Date: Wed, 28 Apr 2021 12:37:50 -0700
Message-Id: <20210428193756.2110517-1-ricarkol@google.com>
Mime-Version: 1.0
X-Mailer: git-send-email 2.31.1.498.g6c1eba8ee3d-goog
Subject: [PATCH v2 0/6] KVM: x86: Use kernel x86 cpuid utilities in KVM
 selftests
From: Ricardo Koller <ricarkol@google.com>
To: Paolo Bonzini <pbonzini@redhat.com>
Cc: kvm@vger.kernel.org, Peter Zijlstra <peterz@infradead.org>,
        Ingo Molnar <mingo@redhat.com>,
        Arnaldo Carvalho de Melo <acme@kernel.org>,
        Mark Rutland <mark.rutland@arm.com>,
        Alexander Shishkin <alexander.shishkin@linux.intel.com>,
        Jiri Olsa <jolsa@redhat.com>,
        Namhyung Kim <namhyung@kernel.org>,
        "H. Peter Anvin" <hpa@zytor.com>,
        Sean Christopherson <seanjc@google.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>,
        Nathan Chancellor <nathan@kernel.org>,
        Nick Desaulniers <ndesaulniers@google.com>,
        linux-kernel@vger.kernel.org, clang-built-linux@googlegroups.com,
        Ricardo Koller <ricarkol@google.com>
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The kernel has a set of utilities and definitions to deal with x86 cpu
features.  The x86 KVM selftests don't use them, and instead have
evolved to use differing and ad-hoc methods for checking features. The
advantage of the kernel feature definitions is that they use a format
that embeds the info needed to extract them from cpuid (function, index,
and register to use).

Patches 1 and 2 add a script for checking that kernel headers don't
drift from their original copies. Patches 3 and 4 massage the related
cpuid header files in the kernel side, then copy them into tools/ so
they can be included by selftests.  The last 2 patches replace the tests
checking for cpu features to use the definitions and utilities
introduced from the kernel.

Tested the arch/x86 patches by building these combinations:
  ARCH=i386 allmodconfig
  ARCH=i386 allyesconfig
  ARCH=x86_64 allyesconfig
  ARCH=x86_64 allmodconfig
  ARCH=um alldefconfig
  ARCH=i386 alldefconfig
and the selftest changes on both x86 and arm64.

Thanks,
Ricardo

v2:
- Add script to check for kernel headers drift in tools
- Sync header that is currently failing the check
- Move header copies under tools/testing/selftests/kvm/include/x86
  instead of tools/arch/x86/include
v1: https://lore.kernel.org/kvm/20210422005626.564163-1-ricarkol@google.com

Ricardo Koller (6):
  KVM: selftests: Add kernel headers sync check
  tools headers x86: Update bitsperlong.h in tools
  x86/cpu: Expose CPUID regs, leaf and index definitions to tools
  tools headers x86: Copy cpuid helpers from the kernel
  KVM: selftests: Introduce utilities for checking x86 features
  KVM: selftests: Use kernel x86 cpuid features format

 arch/x86/events/intel/pt.c                    |   1 +
 arch/x86/include/asm/cpufeature.h             |  23 +-
 arch/x86/include/asm/processor.h              |  11 -
 arch/x86/kernel/cpu/scattered.c               |   2 +-
 arch/x86/kernel/cpuid.c                       |   2 +-
 tools/arch/x86/include/asm/cpufeatures.h      |   3 +
 tools/include/uapi/asm-generic/bitsperlong.h  |   1 +
 tools/testing/selftests/kvm/Makefile          |   2 +
 tools/testing/selftests/kvm/check-headers.sh  |  64 +++++
 .../kvm/include/x86_64/asm/cpufeature.h       | 257 ++++++++++++++++++
 .../selftests/kvm/include/x86_64/cpuid.h      |  61 +++++
 .../selftests/kvm/include/x86_64/processor.h  |  16 --
 .../kvm/include/x86_64/reverse_cpuid.h        | 185 +++++++++++++
 .../selftests/kvm/include/x86_64/svm_util.h   |  11 +-
 tools/testing/selftests/kvm/lib/x86_64/svm.c  |   6 +-
 tools/testing/selftests/kvm/lib/x86_64/vmx.c  |   5 +-
 tools/testing/selftests/kvm/steal_time.c      |   5 +-
 .../kvm/x86_64/cr4_cpuid_sync_test.c          |  23 +-
 .../selftests/kvm/x86_64/set_sregs_test.c     |  25 +-
 .../selftests/kvm/x86_64/vmx_pmu_msrs_test.c  |   8 +-
 .../kvm/x86_64/vmx_set_nested_state_test.c    |   5 +-
 .../selftests/kvm/x86_64/xss_msr_test.c       |  10 +-
 22 files changed, 630 insertions(+), 96 deletions(-)
 create mode 100755 tools/testing/selftests/kvm/check-headers.sh
 create mode 100644 tools/testing/selftests/kvm/include/x86_64/asm/cpufeature.h
 create mode 100644 tools/testing/selftests/kvm/include/x86_64/cpuid.h
 create mode 100644 tools/testing/selftests/kvm/include/x86_64/reverse_cpuid.h
```
