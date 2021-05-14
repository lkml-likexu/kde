

#### [PATCH v3 0/5] KVM: selftests: arm64 exception handling and debug
##### From: Ricardo Koller <ricarkol@google.com>

```c
From patchwork Thu May 13 00:27:57 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Ricardo Koller <ricarkol@google.com>
X-Patchwork-Id: 12255005
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-21.3 required=3.0 tests=BAYES_00,DKIMWL_WL_MED,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT,
	USER_IN_DEF_DKIM_WL autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id B82B9C433ED
	for <kvm@archiver.kernel.org>; Thu, 13 May 2021 00:37:14 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 982A96100A
	for <kvm@archiver.kernel.org>; Thu, 13 May 2021 00:37:14 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S239372AbhEMAiS (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Wed, 12 May 2021 20:38:18 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:56008 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1346474AbhEMAge (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 12 May 2021 20:36:34 -0400
Received: from mail-qv1-xf49.google.com (mail-qv1-xf49.google.com
 [IPv6:2607:f8b0:4864:20::f49])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id BE4C9C061361
        for <kvm@vger.kernel.org>; Wed, 12 May 2021 17:28:06 -0700 (PDT)
Received: by mail-qv1-xf49.google.com with SMTP id
 b24-20020a0cb3d80000b02901e78b82d74aso10153590qvf.20
        for <kvm@vger.kernel.org>; Wed, 12 May 2021 17:28:06 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=date:message-id:mime-version:subject:from:to:cc;
        bh=Q0AXb1y4mM0XDKonC9J0l8yMJqRoopU+CAh1mjQac5o=;
        b=CrI++EttyKCarsBHhj1NIQX1W4Ytekgna+XEc9ugobp0lUmmfIwZzFo1y6719X4mWa
         ooESkvHZZiXHLMJiUzFUa3jQ8is6sMQs66uj87aggctlJoUiOXzdNg5xNeRbPlyxwswt
         nzVEsXMgWAMJ7eFqvvONv0zXveT8YQkG5zoKsobt8vgpdjS4zhdnmkl2Zauylo0xQcRq
         gDQKSzHpD3Yj+drg8Tpqc1PvoJXRwIHYU2O8RVLyZ8vxUEDHKq4X9kQfRwd10ncllZRB
         Br4lXRxacQze9mIF9bm6EbcfXQa4TSUVRhvxdRUsEBFMJK78I1GY7nZKnq2GKDsGUN8x
         I4wA==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:date:message-id:mime-version:subject:from:to:cc;
        bh=Q0AXb1y4mM0XDKonC9J0l8yMJqRoopU+CAh1mjQac5o=;
        b=Dovcp8ak+9+BHZOQDOGd6d96uhXtccXbWh3fl9HehMD9mWmpx8MsrEVvbQJCTwjrzm
         +0LHyqJQoUikAwr0WEjDHzb6Ux6xK8cJMvVXT1EfYb23FSPAm4DCz/WN9kqQBkRcxgYE
         BINSX+YxOxHt7PA3RQulF0I10lcMCe4dd2cSVuYldfKI7GoYryU7XXImS3bVMxjJwg2D
         J0VQFwaxpwCfTHMONf3n6DNqFOMRflEjIAIXALYvDUBanO6zbZOTt9S1vwjjh+D4ja7e
         nrMZTl+C6WYp1sboq4piRzCAtm/OfY3OKPNgAiJFRFveRWdZEd6mX7++pJEI+kOtuYyk
         03ng==
X-Gm-Message-State: AOAM532yasSNbiOXkJrEFX9uRDXdJwBZRrVQOCUyFT3Kdag7UcqRhxht
        BO7ILW+LPzBHdCaD/u6j6m4J6rZjdSlEBZq/H9WCIAZykQnw92WEnwrUS0HUqUMSrBT6Qn5zjUY
        TsL+MRSzKpqz6lvBrOMbUQpbCtfa1uTf0oCs2O89tXj9W3I6vBkgmSet6rjkOe/w=
X-Google-Smtp-Source: 
 ABdhPJxhFvkTjka33EvfCorfu2A02LxQsuxtWR2/unbLQbI0MG7cVU2h5YFOzLNjwwnPjheVBuGa9gkKTi3q2Q==
X-Received: from ricarkol2.c.googlers.com
 ([fda3:e722:ac3:10:24:72f4:c0a8:62fe])
 (user=ricarkol job=sendgmr) by 2002:a0c:ef42:: with SMTP id
 t2mr34819008qvs.48.1620865685059; Wed, 12 May 2021 17:28:05 -0700 (PDT)
Date: Wed, 12 May 2021 17:27:57 -0700
Message-Id: <20210513002802.3671838-1-ricarkol@google.com>
Mime-Version: 1.0
X-Mailer: git-send-email 2.31.1.607.g51e8a6a459-goog
Subject: [PATCH v3 0/5] KVM: selftests: arm64 exception handling and debug
 test
From: Ricardo Koller <ricarkol@google.com>
To: kvm@vger.kernel.org, kvmarm@lists.cs.columbia.edu
Cc: pbonzini@redhat.com, maz@kernel.org, drjones@redhat.com,
        alexandru.elisei@arm.com, eric.auger@redhat.com,
        Ricardo Koller <ricarkol@google.com>
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Hi,

These patches add a debug exception test in aarch64 KVM selftests while
also adding basic exception handling support.

The structure of the exception handling is based on its x86 counterpart.
Tests use the same calls to initialize exception handling and both
architectures allow tests to override the handler for a particular
vector, or (vector, ec) for synchronous exceptions in the arm64 case.

The debug test is similar to x86_64/debug_regs, except that the x86 one
controls the debugging from outside the VM. This proposed arm64 test
controls and handles debug exceptions from the inside.

Thanks,
Ricardo

v2 -> v3:

Addressed comments from Andrew and Marc (thanks again). Also, many thanks for
the reviews and tests from Eric and Zenghui.
- add missing ISBs after writing into debug registers.
- not store/restore of sp_el0 on exceptions.
- add default handlers for Error and FIQ.
- change multiple TEST_ASSERT(false, ...) to TEST_FAIL.
- use Andrew's suggestion regarding __GUEST_ASSERT modifications
  in order to easier implement GUEST_ASSERT_EQ (Thanks Andrew).

v1 -> v2:

Addressed comments from Andrew and Marc (thank you very much):
- rename vm_handle_exception in all tests.
- introduce UCALL_UNHANDLED in x86 first.
- move GUEST_ASSERT_EQ to common utils header.
- handle sync and other exceptions separately: use two tables (like
  kvm-unit-tests).
- add two separate functions for installing sync versus other exceptions
- changes in handlers.S: use the same layout as user_pt_regs, treat the
  EL1t vectors as invalid, refactor the vector table creation to not use
  manual numbering, add comments, remove LR from the stored registers.
- changes in debug-exceptions.c: remove unused headers, use the common
  GUEST_ASSERT_EQ, use vcpu_run instead of _vcpu_run.
- changes in processor.h: write_sysreg with support for xzr, replace EL1
  with current in macro names, define ESR_EC_MASK as ESR_EC_NUM-1.

Ricardo Koller (5):
  KVM: selftests: Rename vm_handle_exception
  KVM: selftests: Introduce UCALL_UNHANDLED for unhandled vector
    reporting
  KVM: selftests: Move GUEST_ASSERT_EQ to utils header
  KVM: selftests: Add exception handling support for aarch64
  KVM: selftests: Add aarch64/debug-exceptions test

 tools/testing/selftests/kvm/.gitignore        |   1 +
 tools/testing/selftests/kvm/Makefile          |   3 +-
 .../selftests/kvm/aarch64/debug-exceptions.c  | 250 ++++++++++++++++++
 .../selftests/kvm/include/aarch64/processor.h |  83 +++++-
 .../testing/selftests/kvm/include/kvm_util.h  |  23 +-
 .../selftests/kvm/include/x86_64/processor.h  |   4 +-
 .../selftests/kvm/lib/aarch64/handlers.S      | 124 +++++++++
 .../selftests/kvm/lib/aarch64/processor.c     | 131 +++++++++
 .../selftests/kvm/lib/x86_64/processor.c      |  22 +-
 .../selftests/kvm/x86_64/kvm_pv_test.c        |   2 +-
 .../selftests/kvm/x86_64/tsc_msrs_test.c      |   9 -
 .../kvm/x86_64/userspace_msr_exit_test.c      |   8 +-
 .../selftests/kvm/x86_64/xapic_ipi_test.c     |   2 +-
 13 files changed, 615 insertions(+), 47 deletions(-)
 create mode 100644 tools/testing/selftests/kvm/aarch64/debug-exceptions.c
 create mode 100644 tools/testing/selftests/kvm/lib/aarch64/handlers.S
```
#### [PATCH 0/2] KVM: x86: hyper-v: Conditionally allow SynIC with
##### From: Vitaly Kuznetsov <vkuznets@redhat.com>

```c
From patchwork Thu May 13 11:37:08 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Vitaly Kuznetsov <vkuznets@redhat.com>
X-Patchwork-Id: 12255627
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-11.5 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS autolearn=ham
	autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 2D0A0C433B4
	for <kvm@archiver.kernel.org>; Thu, 13 May 2021 11:37:23 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id E6B4661443
	for <kvm@archiver.kernel.org>; Thu, 13 May 2021 11:37:22 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S233429AbhEMLia (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Thu, 13 May 2021 07:38:30 -0400
Received: from us-smtp-delivery-124.mimecast.com ([216.205.24.124]:30955 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S232342AbhEMLi2 (ORCPT
        <rfc822;kvm@vger.kernel.org>); Thu, 13 May 2021 07:38:28 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1620905838;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=uFzW4jQ7R2znAA/1j+DeYPq3FnZ8NbG7egg4F1SWsZ8=;
        b=VrDRCmWHRvNRVSk5JNPG9UXSb8KSI9oHwYi1AKwn51rWWjjRgajIaxYwDxN6bjRShE3aAq
        9WcCViLev2Im+oJNT5YTqonB2jIgIttr9vIdKReiRLpbsThy7G/A2TxgFDTyX2j3J3G2xc
        bGmKk5ucj41Kfsz7OL2c6CelWo5HviU=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-155-ng8dP8LrN6CCgVo2NrGVJw-1; Thu, 13 May 2021 07:37:16 -0400
X-MC-Unique: ng8dP8LrN6CCgVo2NrGVJw-1
Received: from smtp.corp.redhat.com (int-mx07.intmail.prod.int.phx2.redhat.com
 [10.5.11.22])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 29DEC8015DB;
        Thu, 13 May 2021 11:37:15 +0000 (UTC)
Received: from vitty.brq.redhat.com (unknown [10.40.193.2])
        by smtp.corp.redhat.com (Postfix) with ESMTP id D4C0E10016F8;
        Thu, 13 May 2021 11:37:11 +0000 (UTC)
From: Vitaly Kuznetsov <vkuznets@redhat.com>
To: kvm@vger.kernel.org, Paolo Bonzini <pbonzini@redhat.com>
Cc: Sean Christopherson <seanjc@google.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Kechen Lu <kechenl@nvidia.com>,
        Maxim Levitsky <mlevitsk@redhat.com>,
        linux-kernel@vger.kernel.org
Subject: [PATCH 0/2] KVM: x86: hyper-v: Conditionally allow SynIC with
 APICv/AVIC
Date: Thu, 13 May 2021 13:37:08 +0200
Message-Id: <20210513113710.1740398-1-vkuznets@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.84 on 10.5.11.22
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

APICV_INHIBIT_REASON_HYPERV is currently unconditionally forced upon
SynIC activation as SynIC's AutoEOI is incompatible with APICv/AVIC. It is,
however, possible to track whether the feature was actually used by the
guest and only inhibit APICv/AVIC when needed.

The feature can be tested with QEMU's 'hv-passthrough' debug mode.

Note, 'avic' kvm-amd module parameter is '0' by default and thus needs to
be explicitly enabled.

Vitaly Kuznetsov (2):
  KVM: x86: Invert APICv/AVIC enablement check
  KVM: x86: hyper-v: Deactivate APICv only when AutoEOI feature is in
    use

 arch/x86/include/asm/kvm_host.h |  5 ++++-
 arch/x86/kvm/hyperv.c           | 27 +++++++++++++++++++++------
 arch/x86/kvm/svm/svm.c          |  7 ++++++-
 arch/x86/kvm/vmx/vmx.c          |  7 ++++++-
 arch/x86/kvm/x86.c              |  6 +++---
 5 files changed, 40 insertions(+), 12 deletions(-)
```
