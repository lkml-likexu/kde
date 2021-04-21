

#### [RFC PATCH 00/10] KVM: x86/mmu: simplify argument to kvm page fault
##### From: Isaku Yamahata <isaku.yamahata@intel.com>

```c
From patchwork Tue Apr 20 10:39:10 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Isaku Yamahata <isaku.yamahata@intel.com>
X-Patchwork-Id: 12213707
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-11.8 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,
	SPF_PASS,USER_AGENT_GIT autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 5A0D0C433ED
	for <kvm@archiver.kernel.org>; Tue, 20 Apr 2021 10:41:45 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 2297261354
	for <kvm@archiver.kernel.org>; Tue, 20 Apr 2021 10:41:45 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S231660AbhDTKmO (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 20 Apr 2021 06:42:14 -0400
Received: from mga01.intel.com ([192.55.52.88]:42730 "EHLO mga01.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S231616AbhDTKmO (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 20 Apr 2021 06:42:14 -0400
IronPort-SDR: 
 lG7L4W8RnIU5MD3t9L40ScotXDyhO78ah+b969iYS5qieuQo8UnlF1oUWYKhWT4z7mHIniMQp1
 9daQSdPkLgUg==
X-IronPort-AV: E=McAfee;i="6200,9189,9959"; a="216071823"
X-IronPort-AV: E=Sophos;i="5.82,236,1613462400";
   d="scan'208";a="216071823"
Received: from fmsmga008.fm.intel.com ([10.253.24.58])
  by fmsmga101.fm.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 20 Apr 2021 03:41:43 -0700
IronPort-SDR: 
 6ZzKjAGijILXCQakuNDkwtxSKSSj4WG7QnTq/nfOJEwHo+leqxCC6uKaiDMHlZs6c19yChpgOu
 RDVc4UFZ5DtA==
X-IronPort-AV: E=Sophos;i="5.82,236,1613462400";
   d="scan'208";a="420359503"
Received: from ls.sc.intel.com (HELO localhost) ([143.183.96.54])
  by fmsmga008-auth.fm.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 20 Apr 2021 03:41:43 -0700
From: Isaku Yamahata <isaku.yamahata@intel.com>
To: kvm@vger.kernel.org, linux-kernel@vger.kernel.org,
        Paolo Bonzini <pbonzini@redhat.com>,
        Sean Christopherson <seanjc@google.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>
Cc: isaku.yamahata@gmail.com, Isaku Yamahata <isaku.yamahata@intel.com>
Subject: [RFC PATCH 00/10] KVM: x86/mmu: simplify argument to kvm page fault
 handler
Date: Tue, 20 Apr 2021 03:39:10 -0700
Message-Id: <cover.1618914692.git.isaku.yamahata@intel.com>
X-Mailer: git-send-email 2.25.1
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This is a preliminary clean up for TDX which complicates KVM page fault
execution path. simplify those execution path as preparation.

The current kvm page fault handlers passes around many arguments to the
functions.
To simplify those arguments and local variables, introduce data structure,
struct kvm_page_fault,  to hold those arguments, variables, and passes around the pointer
to struct kvm_page_fault.

struct kvm_page_fault is allocated on stack on the caller of kvm fault handler,
kvm_mmu_do_page_fault().
And then  push down the pointer to inner functions step by step.
The conversion order is as follows
. kvm_mmu_do_page_fault() with introducing struct kvm_page_fault
. kvm_mmu.page_fault(): kvm_tdp_page_fault(), nonpaging_page_fault(), FNAME(page_fault)
. direct_page_fault()
. try_async_pf()
. page_fault_handle_page_track()
. handle_abnormal_pfn()
. fast_page_fault()
. __direct_map()
. kvm_tdp_mmu_map()
. FNAME(fetch)

Probably more functions should be converted. or some should not converted.
Only code refactoring and no functional change is intended.

Isaku Yamahata (10):
  KVM: x86/mmu: make kvm_mmu_do_page_fault() receive single argument
  KVM: x86/mmu: make kvm_mmu:page_fault receive single argument
  KVM: x86/mmu: make direct_page_fault() receive single argument
  KVM: x86/mmu: make try_async_pf() receive single argument
  KVM: x86/mmu: make page_fault_handle_page_track() receive single
    argument
  KVM: x86/mmu: make handle_abnormal_pfn() receive single argument
  KVM: x86/mmu: make fast_page_fault() receive single argument
  KVM: x86/mmu: make __direct_map() receive single argument
  KVM: x86/mmu: make kvm_tdp_mmu_map() receive single argument
  KVM: x86/mmu: make FNAME(fetch) receive single argument

 arch/x86/include/asm/kvm_host.h |   4 +-
 arch/x86/kvm/mmu.h              |  49 ++++++++++--
 arch/x86/kvm/mmu/mmu.c          | 130 +++++++++++++++++---------------
 arch/x86/kvm/mmu/paging_tmpl.h  |  60 +++++++--------
 arch/x86/kvm/mmu/tdp_mmu.c      |  21 +++---
 arch/x86/kvm/mmu/tdp_mmu.h      |   4 +-
 arch/x86/kvm/x86.c              |   4 +-
 7 files changed, 156 insertions(+), 116 deletions(-)
```
#### [PATCH v4 0/2] KVM: selftests: fix races in dirty log test
##### From: Peter Xu <peterx@redhat.com>

```c
From patchwork Tue Apr 20 15:39:27 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Peter Xu <peterx@redhat.com>
X-Patchwork-Id: 12214521
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-13.8 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT
	autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 11FFDC433B4
	for <kvm@archiver.kernel.org>; Tue, 20 Apr 2021 15:39:45 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id D4BD361354
	for <kvm@archiver.kernel.org>; Tue, 20 Apr 2021 15:39:44 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S233019AbhDTPkP (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 20 Apr 2021 11:40:15 -0400
Received: from us-smtp-delivery-124.mimecast.com ([170.10.133.124]:53004 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S233022AbhDTPkN (ORCPT
        <rfc822;kvm@vger.kernel.org>); Tue, 20 Apr 2021 11:40:13 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1618933181;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:content-type:content-type:
         content-transfer-encoding:content-transfer-encoding;
        bh=coXw7bSB92l2OSOi2Pskhossq8vZZCyQYfDdNtE51LI=;
        b=dOEt/yAUasv/0PvUhQPYQRPHrt8eAJsHHfxMsqZjwqDAwnLaT9wo4QUU7Ob8ZKwxCrwexi
        fcaI5VnjjghSSnk5ieVBYKwN7Z8XDky6OEz4spGE9peVlXlBsHSPBrSWTCsUaz2FYUHWCQ
        c6uHCRHAcnBqzi0jncO+6YACboNFuHE=
Received: from mail-qv1-f70.google.com (mail-qv1-f70.google.com
 [209.85.219.70]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-576-D5jmD-_QNS-TNVQZfn9jwA-1; Tue, 20 Apr 2021 11:39:32 -0400
X-MC-Unique: D5jmD-_QNS-TNVQZfn9jwA-1
Received: by mail-qv1-f70.google.com with SMTP id
 m19-20020a0cdb930000b029019a25080c40so11634892qvk.11
        for <kvm@vger.kernel.org>; Tue, 20 Apr 2021 08:39:32 -0700 (PDT)
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:mime-version
         :content-transfer-encoding;
        bh=coXw7bSB92l2OSOi2Pskhossq8vZZCyQYfDdNtE51LI=;
        b=mH1kkGrMB/LBSNUwbZ5BU444G4lf/UEePA9Z+aAZl7hfcEltZPHCGS++jiOw3m5YJ7
         m2aydhSmsT6rCNpT+hL2x3rr/nEdE+ay3Qd8Oym0td+wxY4xl5xvf8NdB0/iiEKJC/m2
         4bLpGN67s0Qy7Xw89XSr10KE4J2pla/t9oww1BveWQeTCoB6t8X62+DgXc67Ye/eJfIy
         UhQdxUXOw28Wv9+UsCXehhA4YUgWJNFjREdtQLsU5e2Y6G19Jc+446q3H6zknXorVCfv
         aHVEBWYYnJ3cTAqIIXkyERxiyRqr+tvYStu6rubfx5TdUIHXFrqYjkBjadkif1cQVFQ7
         8EOA==
X-Gm-Message-State: AOAM530WtdXRyUN5D1ZVf5X8yjicHXtG3jhoKznvABabwAH1XknBn9t9
        mXA9PRFjG+rma+sDsyfJst6eb+ro2+ME76hFeqjnjXzTLpcYV7hYiUkii6KK81AxOugTpbdgHoD
        JIkNbvsDXjOUyhWM2me7gLBlaqn+Vbgt54IUAigRhxZOp5QdV4q5aqWZjzrIMyg==
X-Received: by 2002:ac8:4e16:: with SMTP id
 c22mr10856584qtw.354.1618933171911;
        Tue, 20 Apr 2021 08:39:31 -0700 (PDT)
X-Google-Smtp-Source: 
 ABdhPJyE/oMaWgtfj/To4K6pA6L6aSzn9oP92etGjIRHkk4pGYIgEbMrwLhaCy0IueXIi8VP6xiH0Q==
X-Received: by 2002:ac8:4e16:: with SMTP id
 c22mr10856551qtw.354.1618933171631;
        Tue, 20 Apr 2021 08:39:31 -0700 (PDT)
Received: from xz-x1.redhat.com
 (bras-base-toroon474qw-grc-88-174-93-75-154.dsl.bell.ca. [174.93.75.154])
        by smtp.gmail.com with ESMTPSA id
 f12sm11633325qtq.84.2021.04.20.08.39.30
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Tue, 20 Apr 2021 08:39:31 -0700 (PDT)
From: Peter Xu <peterx@redhat.com>
To: kvm@vger.kernel.org, linux-kernel@vger.kernel.org
Cc: Paolo Bonzini <pbonzini@redhat.com>, peterx@redhat.com,
        Sean Christopherson <seanjc@google.com>,
        Andrew Jones <drjones@redhat.com>
Subject: [PATCH v4 0/2] KVM: selftests: fix races in dirty log test
Date: Tue, 20 Apr 2021 11:39:27 -0400
Message-Id: <20210420153929.482810-1-peterx@redhat.com>
X-Mailer: git-send-email 2.26.2
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

v4:
- add missing vcpu_handle_sync_stop() call in dirty ring test

The other solution of patch 2 is here [1]

I got another report that there seems to still be a race, but that one seems
extremely hard to trigger, even so far we don't know whether that could be
ARM-only.  Since current fix should make sense already and fix real problems,
IMHO we don't need to wait for that.

Paolo, I still kept the 2nd patch just for completeness, but feel free to
ignore the 2nd patch if you prefer the other version, and I'll follow your
preference.

Thanks!

[1] https://lore.kernel.org/kvm/20210420081614.684787-1-pbonzini@redhat.com/

Peter Xu (2):
  KVM: selftests: Sync data verify of dirty logging with guest sync
  KVM: selftests: Wait for vcpu thread before signal setup

 tools/testing/selftests/kvm/dirty_log_test.c | 70 +++++++++++++++++---
 1 file changed, 59 insertions(+), 11 deletions(-)
```
#### [kvm-unit-tests RFC PATCH 0/1] configure: arm: Replace --vmm with
##### From: Alexandru Elisei <alexandru.elisei@arm.com>

```c
From patchwork Tue Apr 20 16:13:37 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Alexandru Elisei <alexandru.elisei@arm.com>
X-Patchwork-Id: 12214623
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-11.8 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,
	SPF_PASS,USER_AGENT_GIT autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 9919DC433ED
	for <kvm@archiver.kernel.org>; Tue, 20 Apr 2021 16:13:12 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 609CB613C9
	for <kvm@archiver.kernel.org>; Tue, 20 Apr 2021 16:13:12 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S232910AbhDTQNn (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 20 Apr 2021 12:13:43 -0400
Received: from foss.arm.com ([217.140.110.172]:37748 "EHLO foss.arm.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S232174AbhDTQNl (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 20 Apr 2021 12:13:41 -0400
Received: from usa-sjc-imap-foss1.foss.arm.com (unknown [10.121.207.14])
        by usa-sjc-mx-foss1.foss.arm.com (Postfix) with ESMTP id E1B751474;
        Tue, 20 Apr 2021 09:13:09 -0700 (PDT)
Received: from monolith.localdoman (unknown [172.31.20.19])
        by usa-sjc-imap-foss1.foss.arm.com (Postfix) with ESMTPSA id
 1BF7C3F73B;
        Tue, 20 Apr 2021 09:13:08 -0700 (PDT)
From: Alexandru Elisei <alexandru.elisei@arm.com>
To: drjones@redhat.com, kvm@vger.kernel.org,
        kvmarm@lists.cs.columbia.edu
Cc: pbonzini@redhat.com
Subject: [kvm-unit-tests RFC PATCH 0/1] configure: arm: Replace --vmm with
 --target
Date: Tue, 20 Apr 2021 17:13:37 +0100
Message-Id: <20210420161338.70914-1-alexandru.elisei@arm.com>
X-Mailer: git-send-email 2.31.1
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This is an RFC because it's not exactly clear to me that this is the best
approach. I'm also open to using a different name for the new option, maybe
something like --platform if it makes more sense.

I see two use cases for the patch:

1. Using different files when compiling kvm-unit-tests to run as an EFI app
as opposed to a KVM guest (described in the commit message).

2. This is speculation on my part, but I can see extending
arm/unittests.cfg with a "target" test option which can be used to decide
which tests need to be run based on the configure --target value. For
example, migration tests don't make much sense on kvmtool, which doesn't
have migration support. Similarly, the micro-bench test doesn't make much
sense (to me, at least) as an EFI app. Of course, this is only useful if
there are automated scripts to run the tests under kvmtool or EFI, which
doesn't look likely at the moment, so I left it out of the commit message.

Using --vmm will trigger a warning. I was thinking about removing it entirely in
a about a year's time, but that's not set in stone. Note that qemu users
(probably the vast majority of people) will not be affected by this change as
long as they weren't setting --vmm explicitely to its default value of "qemu".

Alexandru Elisei (1):
  configure: arm: Replace --vmm with --target

 configure | 30 +++++++++++++++++++++++-------
 1 file changed, 23 insertions(+), 7 deletions(-)
```
#### [PATCH kvm-unit-tests v2 0/8] arm/arm64: Prepare for target-efi
##### From: Andrew Jones <drjones@redhat.com>

```c
From patchwork Tue Apr 20 18:59:54 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Andrew Jones <drjones@redhat.com>
X-Patchwork-Id: 12214985
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-15.8 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_PATCH,MAILING_LIST_MULTI,MENTIONS_GIT_HOSTING,SPF_HELO_NONE,SPF_PASS
	autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id BE3B0C433ED
	for <kvm@archiver.kernel.org>; Tue, 20 Apr 2021 19:00:23 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 86F44613E0
	for <kvm@archiver.kernel.org>; Tue, 20 Apr 2021 19:00:23 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S233675AbhDTTAy (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 20 Apr 2021 15:00:54 -0400
Received: from us-smtp-delivery-124.mimecast.com ([216.205.24.124]:20727 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S233509AbhDTTAx (ORCPT
        <rfc822;kvm@vger.kernel.org>); Tue, 20 Apr 2021 15:00:53 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1618945221;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=gSPrCdS8K6lmsfPZiEVs50IuL/jRIZqevIBdwa4YXJQ=;
        b=iTUWG0+nFCuMAZFaibC+uZgIzYb/w1vmXzEAtLIMhhBo0dj/R+FZcsMLZmPAUceFO7kYEp
        SvLutNfYwOLQVwx6Y/eTWQC0B5+BQqyABcFXA6bSseNZXL7aL4rjG7+XFeK+JhTjWFewDc
        GrQbiwun9xcjZBYxBi44YP3kd3j4KMs=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-445-9-3-fQj6NgKE2I8v4s83kw-1; Tue, 20 Apr 2021 15:00:17 -0400
X-MC-Unique: 9-3-fQj6NgKE2I8v4s83kw-1
Received: from smtp.corp.redhat.com (int-mx08.intmail.prod.int.phx2.redhat.com
 [10.5.11.23])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 450C187A82A;
        Tue, 20 Apr 2021 19:00:16 +0000 (UTC)
Received: from gator.home (unknown [10.40.195.207])
        by smtp.corp.redhat.com (Postfix) with ESMTP id F22F319D9B;
        Tue, 20 Apr 2021 19:00:03 +0000 (UTC)
From: Andrew Jones <drjones@redhat.com>
To: kvm@vger.kernel.org
Cc: alexandru.elisei@arm.com, nikos.nikoleris@arm.com,
        andre.przywara@arm.com, eric.auger@redhat.com
Subject: [PATCH kvm-unit-tests v2 0/8] arm/arm64: Prepare for target-efi
Date: Tue, 20 Apr 2021 20:59:54 +0200
Message-Id: <20210420190002.383444-1-drjones@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.84 on 10.5.11.23
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

v2:
 - Addressed all comments from Nikos and Alex
 - The biggest changes are
   * dropping the weird persistent map stuff that I never liked by taking
     Alex's suggestion to just create the idmap early
   * adding mem_region_add() to clean up memory region adding code, also
     improved the assignment of region fields
 - Also, while we found that we still have a memory map assumption
   (3G-4G reserved for virtual memory allocation), I only make that
   assumption clear. I've left removing it for an additional patch
   for another day.
 - Added psci_invoke_none() to use prior to the PSCI method being set
 - Added r-b's for each patch given, unless the commit changed too much
 - Didn't take Alex's suggestion to use x5 for stacktop when calling
   setup from start. I prefer explicitly loading it again.


This series is a collection of patches derived from [1] that pave the
way for new targets, e.g. target-efi[2]. These patches mostly address
the elimination of memory map assumptions and they shouldn't have any
functional changes. The last two patches are a couple of patches not
related to the memory map, but they also prepare for bare metal targets.
I tossed them in since I don't think they should be too controversial.
This patch series is also available here [3].

[1] https://github.com/rhdrjones/kvm-unit-tests/commits/target-efi
[2] https://www.youtube.com/watch?v=kvaufVrL0J0
[3] https://gitlab.com/rhdrjones/kvm-unit-tests/-/commits/efiprep

Thanks,
drew


Andrew Jones (8):
  arm/arm64: Reorganize cstart assembler
  arm/arm64: Move setup_vm into setup
  pci-testdev: ioremap regions
  arm/arm64: mmu: Stop mapping an assumed IO region
  arm/arm64: mmu: Remove memory layout assumptions
  arm/arm64: setup: Consolidate memory layout assumptions
  chr-testdev: Silently fail init
  arm/arm64: psci: don't assume method is hvc

 arm/cstart.S           |  92 ++++++++++++++--------
 arm/cstart64.S         |  45 ++++++++---
 arm/flat.lds           |  23 ++++++
 arm/selftest.c         |  34 ++------
 lib/arm/asm/io.h       |   6 ++
 lib/arm/asm/mmu.h      |   1 +
 lib/arm/asm/page.h     |   2 +
 lib/arm/asm/psci.h     |  10 ++-
 lib/arm/asm/setup.h    |   7 +-
 lib/arm/mmu.c          |  53 +++++++++----
 lib/arm/psci.c         |  37 +++++++--
 lib/arm/setup.c        | 175 ++++++++++++++++++++++++-----------------
 lib/arm64/asm/io.h     |   6 ++
 lib/arm64/asm/mmu.h    |   1 +
 lib/arm64/asm/page.h   |   2 +
 lib/chr-testdev.c      |   5 +-
 lib/pci-host-generic.c |   5 +-
 lib/pci-host-generic.h |   4 +-
 lib/pci-testdev.c      |   4 +
 19 files changed, 333 insertions(+), 179 deletions(-)
```
