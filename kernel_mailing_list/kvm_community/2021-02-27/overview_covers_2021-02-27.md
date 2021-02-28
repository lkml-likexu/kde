

#### [kvm-unit-tests PATCH 0/6] Misc assembly fixes and cleanups
##### From: Alexandru Elisei <alexandru.elisei@arm.com>

```c
From patchwork Sat Feb 27 10:41:55 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Alexandru Elisei <alexandru.elisei@arm.com>
X-Patchwork-Id: 12107635
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-11.8 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,
	SPF_PASS,USER_AGENT_GIT autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id A62EDC433E0
	for <kvm@archiver.kernel.org>; Sat, 27 Feb 2021 10:42:58 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 6759464ECE
	for <kvm@archiver.kernel.org>; Sat, 27 Feb 2021 10:42:58 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S230124AbhB0Kmn (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Sat, 27 Feb 2021 05:42:43 -0500
Received: from foss.arm.com ([217.140.110.172]:42996 "EHLO foss.arm.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S229912AbhB0Kmf (ORCPT <rfc822;kvm@vger.kernel.org>);
        Sat, 27 Feb 2021 05:42:35 -0500
Received: from usa-sjc-imap-foss1.foss.arm.com (unknown [10.121.207.14])
        by usa-sjc-mx-foss1.foss.arm.com (Postfix) with ESMTP id 3673431B;
        Sat, 27 Feb 2021 02:41:48 -0800 (PST)
Received: from monolith.localdoman (unknown [172.31.20.19])
        by usa-sjc-imap-foss1.foss.arm.com (Postfix) with ESMTPSA id
 927E53F73B;
        Sat, 27 Feb 2021 02:41:47 -0800 (PST)
From: Alexandru Elisei <alexandru.elisei@arm.com>
To: drjones@redhat.com, kvm@vger.kernel.org,
        kvmarm@lists.cs.columbia.edu
Subject: [kvm-unit-tests PATCH 0/6] Misc assembly fixes and cleanups
Date: Sat, 27 Feb 2021 10:41:55 +0000
Message-Id: <20210227104201.14403-1-alexandru.elisei@arm.com>
X-Mailer: git-send-email 2.30.1
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This series is mostly fixes and cleanups for things I found when playing
with EFI support. Most of them I hope are fairly self-explanatory.

What is clearly aimed at running on baremetal is patch #2 ("arm/arm64:
Remove dcache_line_size global variable"), which is needed because the
startup environment is different for EFI apps and we're going to need to do
cache maintenance before setup() is run.

Patch #4 ("lib: arm64: Consolidate register definitions to sysreg.h") is
there to make importing register definitions and other header files from
Linux (like el2_setup.h) easier by switching to the same layout. And arm
is already using sysreg.h for SCTLR fields.

Alexandru Elisei (6):
  arm64: Remove unnecessary ISB when writing to SPSel
  arm/arm64: Remove dcache_line_size global variable
  arm/arm64: Remove unnecessary ISB when doing dcache maintenance
  lib: arm64: Consolidate register definitions to sysreg.h
  arm64: Configure SCTLR_EL1 at boot
  arm64: Disable TTBR1_EL1 translation table walks

 lib/arm/asm/assembler.h       | 44 +++++++++++++++++++++++++++++
 lib/arm/asm/processor.h       |  7 -----
 lib/arm64/asm/arch_gicv3.h    |  6 ----
 lib/arm64/asm/assembler.h     | 53 +++++++++++++++++++++++++++++++++++
 lib/arm64/asm/pgtable-hwdef.h |  1 +
 lib/arm64/asm/processor.h     | 17 -----------
 lib/arm64/asm/sysreg.h        | 24 ++++++++++++++++
 lib/arm/setup.c               |  7 -----
 arm/cstart.S                  | 19 ++-----------
 arm/cstart64.S                | 28 +++++++-----------
 10 files changed, 135 insertions(+), 71 deletions(-)
 create mode 100644 lib/arm/asm/assembler.h
 create mode 100644 lib/arm64/asm/assembler.h
```
