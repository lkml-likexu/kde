

#### [kvm-unit-tests PATCH v3 0/2] arm64: Add support for configuring the
##### From: Nikos Nikoleris <nikos.nikoleris@arm.com>

```c
From patchwork Wed Nov  4 13:03:50 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Nikos Nikoleris <nikos.nikoleris@arm.com>
X-Patchwork-Id: 11880575
Return-Path: <SRS0=TbV3=EK=vger.kernel.org=kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-6.8 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,
	USER_AGENT_GIT autolearn=no autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id C06CAC2D0A3
	for <kvm@archiver.kernel.org>; Wed,  4 Nov 2020 13:03:57 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 62E142071A
	for <kvm@archiver.kernel.org>; Wed,  4 Nov 2020 13:03:57 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729794AbgKDND4 (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Wed, 4 Nov 2020 08:03:56 -0500
Received: from foss.arm.com ([217.140.110.172]:36812 "EHLO foss.arm.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726350AbgKDND4 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 4 Nov 2020 08:03:56 -0500
Received: from usa-sjc-imap-foss1.foss.arm.com (unknown [10.121.207.14])
        by usa-sjc-mx-foss1.foss.arm.com (Postfix) with ESMTP id 2714E139F;
        Wed,  4 Nov 2020 05:03:55 -0800 (PST)
Received: from camtx2.cambridge.arm.com (camtx2.cambridge.arm.com [10.1.7.22])
        by usa-sjc-imap-foss1.foss.arm.com (Postfix) with ESMTPSA id
 269693F719;
        Wed,  4 Nov 2020 05:03:54 -0800 (PST)
From: Nikos Nikoleris <nikos.nikoleris@arm.com>
To: kvm@vger.kernel.org
Cc: mark.rutland@arm.com, jade.alglave@arm.com, luc.maranget@inria.fr,
        andre.przywara@arm.com, alexandru.elisei@arm.com,
        drjones@redhat.com
Subject: [kvm-unit-tests PATCH v3 0/2] arm64: Add support for configuring the
 translation granule
Date: Wed,  4 Nov 2020 13:03:50 +0000
Message-Id: <20201104130352.17633-1-nikos.nikoleris@arm.com>
X-Mailer: git-send-email 2.17.1
X-ARM-No-Footer: FoSSMail
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Hi all,

One more update to the series that allows us to configure the
translation granule in arm64. Again, thanks to Drew and Alex for
their reviews and their suggestions.

v1: 
https://lore.kernel.org/kvm/006a19c0-cdf7-e76c-8335-03034bea9c7e@arm.com/T
v2: 
https://lore.kernel.org/kvm/20201102113444.103536-1-nikos.nikoleris@arm.com/


Changes in v3:
  - Re-ordered the two changes in the series
  - Moved much of the code to check the configured granule from the C
    preprocessor to run time.
  - Avoid block mappings at the PUD level (Thanks Alex!)
  - Formatting changes

Changes in v2:
  - Change the configure option from page-shift to page-size
  - Check and warn if the configured granule is not supported

Thanks,

Nikos


Nikos Nikoleris (2):
  arm64: Check if the configured translation granule is supported
  arm64: Add support for configuring the translation granule

 configure                     | 27 ++++++++++++++
 lib/arm/asm/page.h            |  4 +++
 lib/arm/asm/pgtable-hwdef.h   |  4 +++
 lib/arm/asm/pgtable.h         |  6 ++++
 lib/arm/asm/thread_info.h     |  4 ++-
 lib/arm64/asm/page.h          | 35 ++++++++++++++----
 lib/arm64/asm/pgtable-hwdef.h | 42 +++++++++++++++++-----
 lib/arm64/asm/pgtable.h       | 68 +++++++++++++++++++++++++++++++++--
 lib/arm64/asm/processor.h     | 36 +++++++++++++++++++
 lib/libcflat.h                | 20 ++++++-----
 lib/arm/mmu.c                 | 31 ++++++++++------
 arm/cstart64.S                | 10 +++++-
 12 files changed, 249 insertions(+), 38 deletions(-)
```
#### [PATCH 00/11] KVM: selftests: Cleanups
##### From: Andrew Jones <drjones@redhat.com>

```c
From patchwork Wed Nov  4 21:23:46 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Andrew Jones <drjones@redhat.com>
X-Patchwork-Id: 11882161
Return-Path: <SRS0=TbV3=EK=vger.kernel.org=kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-3.9 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS autolearn=no autolearn_force=no
	version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 49929C2D0A3
	for <kvm@archiver.kernel.org>; Wed,  4 Nov 2020 21:24:11 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id D77C32080D
	for <kvm@archiver.kernel.org>; Wed,  4 Nov 2020 21:24:10 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="e8+D35su"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1731945AbgKDVYK (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Wed, 4 Nov 2020 16:24:10 -0500
Received: from us-smtp-delivery-124.mimecast.com ([63.128.21.124]:30190 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1729828AbgKDVYJ (ORCPT
        <rfc822;kvm@vger.kernel.org>); Wed, 4 Nov 2020 16:24:09 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1604525048;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=CtHJUodkPPfSp3arc0rIE1/C6vgxP55R/RVEpoV7kdc=;
        b=e8+D35su0Ny7kAe/bs1g81mvgcWV0tz//GcgU/OPpDdwJwg/qpcXB5XLZB0TCqCiGncsWf
        5cccmSATKemGLMXB4YqFD9cFQbmDhtUUgJTWbU/Og7PyjokMtcISiclaPpv7z20PjTreXl
        350Z+MpMrAuRBV399P+XCJPAiFYs6g8=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-572-dIEsXAIdMciSChjPFGPYCg-1; Wed, 04 Nov 2020 16:24:04 -0500
X-MC-Unique: dIEsXAIdMciSChjPFGPYCg-1
Received: from smtp.corp.redhat.com (int-mx04.intmail.prod.int.phx2.redhat.com
 [10.5.11.14])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 78994184214C;
        Wed,  4 Nov 2020 21:24:03 +0000 (UTC)
Received: from kamzik.brq.redhat.com (unknown [10.40.192.66])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 9F0A65DA33;
        Wed,  4 Nov 2020 21:23:58 +0000 (UTC)
From: Andrew Jones <drjones@redhat.com>
To: kvm@vger.kernel.org
Cc: pbonzini@redhat.com, borntraeger@de.ibm.com, frankja@linux.ibm.com,
        bgardon@google.com, peterx@redhat.com
Subject: [PATCH 00/11] KVM: selftests: Cleanups
Date: Wed,  4 Nov 2020 22:23:46 +0100
Message-Id: <20201104212357.171559-1-drjones@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.14
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This series attempts to clean up demand_paging_test and dirty_log_test
by factoring out common code, creating some new API along the way. It's
main goal is to prepare for even more factoring that Ben and Peter want
to do. The series would have a nice negative diff stat, but it also
picks up a few of Peter's patches for his new dirty log test. So, the
+/- diff stat is close to equal. It's not as close as an electoral vote
count, but it's close.

I've tested on x86 and AArch64 (one config each), but not s390x.

Thanks,
drew


Andrew Jones (8):
  KVM: selftests: Add x86_64/tsc_msrs_test to .gitignore
  KVM: selftests: Drop pointless vm_create wrapper
  KVM: selftests: Make the per vcpu memory size global
  KVM: selftests: Make the number of vcpus global
  KVM: selftests: Factor out guest mode code
  KVM: selftests: Make vm_create_default common
  KVM: selftests: Introduce vm_create_[default_]vcpus
  KVM: selftests: Remove create_vm

Peter Xu (3):
  KVM: selftests: Always clear dirty bitmap after iteration
  KVM: selftests: Use a single binary for dirty/clear log test
  KVM: selftests: Introduce after_vcpu_run hook for dirty log test

 tools/testing/selftests/kvm/.gitignore        |   2 +-
 tools/testing/selftests/kvm/Makefile          |   4 +-
 .../selftests/kvm/clear_dirty_log_test.c      |   6 -
 .../selftests/kvm/demand_paging_test.c        | 213 +++-------
 tools/testing/selftests/kvm/dirty_log_test.c  | 372 ++++++++++--------
 .../selftests/kvm/include/aarch64/processor.h |   3 +
 .../selftests/kvm/include/guest_modes.h       |  21 +
 .../testing/selftests/kvm/include/kvm_util.h  |  20 +-
 .../selftests/kvm/include/s390x/processor.h   |   4 +
 .../selftests/kvm/include/x86_64/processor.h  |   4 +
 .../selftests/kvm/lib/aarch64/processor.c     |  17 -
 tools/testing/selftests/kvm/lib/guest_modes.c |  70 ++++
 tools/testing/selftests/kvm/lib/kvm_util.c    |  62 ++-
 .../selftests/kvm/lib/s390x/processor.c       |  22 --
 .../selftests/kvm/lib/x86_64/processor.c      |  32 --
 15 files changed, 445 insertions(+), 407 deletions(-)
 delete mode 100644 tools/testing/selftests/kvm/clear_dirty_log_test.c
 create mode 100644 tools/testing/selftests/kvm/include/guest_modes.h
 create mode 100644 tools/testing/selftests/kvm/lib/guest_modes.c
```
