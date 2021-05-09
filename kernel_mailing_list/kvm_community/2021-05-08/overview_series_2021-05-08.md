#### [PATCH 1/3] KVM: PPC: Book3S HV: exit halt polling on need_resched() as well
##### From: Wanpeng Li <kernellwp@gmail.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Wanpeng Li <kernellwp@gmail.com>
X-Patchwork-Id: 12245933
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-15.8 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,DKIM_VALID_AU,FREEMAIL_FORGED_FROMDOMAIN,FREEMAIL_FROM,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT autolearn=ham
	autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id D4702C433B4
	for <kvm@archiver.kernel.org>; Sat,  8 May 2021 09:32:07 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id AC1E861358
	for <kvm@archiver.kernel.org>; Sat,  8 May 2021 09:32:07 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S229947AbhEHJdH (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Sat, 8 May 2021 05:33:07 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:51906 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S229583AbhEHJdG (ORCPT <rfc822;kvm@vger.kernel.org>);
        Sat, 8 May 2021 05:33:06 -0400
Received: from mail-pf1-x42b.google.com (mail-pf1-x42b.google.com
 [IPv6:2607:f8b0:4864:20::42b])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 6F16DC061574;
        Sat,  8 May 2021 02:32:05 -0700 (PDT)
Received: by mail-pf1-x42b.google.com with SMTP id a5so2578352pfa.11;
        Sat, 08 May 2021 02:32:05 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=from:to:cc:subject:date:message-id;
        bh=/AlNh+fXozUg9qKAtn5bD6eiY6c6BSYqdB15v+Gk2f0=;
        b=NCbVoT0Ho0gKDUXeKOE72t2xlQkggYC6StWQDCxhohmv0FUIh+QIkQv/B8I52PN1Ko
         wSgxuJDz3RAuf71FFpOVgU3mDk0fwm/+vGUYMrdk+E9uNSqFhIsYo3OByEGN4g5/8NUY
         2CkfLfmWG+dKOvpoic43mic8fbCYHfgPpXTZFrPWZhuOPTkC6PAxupfKSoW5Km+/ezFq
         O51f3iU7ekx2n4VFoXlk578ru8nrUrDQ/jUS3ksln+uuJwUUJc493tp62+/i1hPYkt/Q
         gs6xEByMzbooVpiEK7jjsdFk20VDWzokGeOOql9sDJwyqXqTupPydwks3oq2Fqh6Cosr
         QVCg==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id;
        bh=/AlNh+fXozUg9qKAtn5bD6eiY6c6BSYqdB15v+Gk2f0=;
        b=YOxAduqPWmdwGOYS4EP/tRb9mvR7oy4WXQaqwyLVet0lo5UOX2QLA2T3yRBqcN656t
         1LcmAQ9MZVpPdQL47oYemBqrUs+gra0GIe48snkfS8PGjYlS3bCl4AsxVqgr/Hs2dPol
         n9K6ZENkffqF+BSsMisrSn9RY6vYhZEugULJ4CbtTZGUUF5EtA7CI6GLy2ZbhtaexfZ7
         qzz4Koiyk8OkJGRvFcpNWYKbUQ3dBKJdweESrnx79aMkWqJp9Hy9nyng9RlvNrDKof4n
         sgfZUG/US0+shRabKuDYZDTU47R1Ripa+dGiZmEGy13CZY+p2qhBhf4FZf/YAP553ViL
         dkkQ==
X-Gm-Message-State: AOAM530fCSTNK0J5Xvbx93ltk4xVGgg0UEa/4ya4CoOhXzBA8T2OliYB
        IpXTHdzfBIuqZTPu9yLXZcRElfB+dqM=
X-Google-Smtp-Source: 
 ABdhPJwMe0nhLb9BY8hozBgV7qkeOlTJPC9ZbtPcg32B9HlEX3vFEMzSTTfgFl7CwwQdW5hD5fWtdg==
X-Received: by 2002:a63:dc57:: with SMTP id
 f23mr14237716pgj.294.1620466324753;
        Sat, 08 May 2021 02:32:04 -0700 (PDT)
Received: from localhost.localdomain ([103.7.29.6])
        by smtp.googlemail.com with ESMTPSA id
 f3sm40437765pjo.3.2021.05.08.02.32.02
        (version=TLS1_2 cipher=ECDHE-ECDSA-AES128-GCM-SHA256 bits=128/128);
        Sat, 08 May 2021 02:32:04 -0700 (PDT)
From: Wanpeng Li <kernellwp@gmail.com>
X-Google-Original-From: Wanpeng Li <wanpengli@tencent.com>
To: linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Cc: Paolo Bonzini <pbonzini@redhat.com>,
        Sean Christopherson <seanjc@google.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>,
        Paul Mackerras <paulus@ozlabs.org>
Subject: [PATCH 1/3] KVM: PPC: Book3S HV: exit halt polling on need_resched()
 as well
Date: Sat,  8 May 2021 17:31:48 +0800
Message-Id: <1620466310-8428-1-git-send-email-wanpengli@tencent.com>
X-Mailer: git-send-email 2.7.4
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Wanpeng Li <wanpengli@tencent.com>

Inspired by commit 262de4102c7bb8 (kvm: exit halt polling on need_resched() 
as well), due to PPC implements an arch specific halt polling logic, we should 
add the need_resched() checking there as well.

Cc: Paul Mackerras <paulus@ozlabs.org>
Signed-off-by: Wanpeng Li <wanpengli@tencent.com>
---
 arch/powerpc/kvm/book3s_hv.c | 3 ++-
 1 file changed, 2 insertions(+), 1 deletion(-)

```
#### [GIT PULL] Second batch of KVM changes for Linux 5.13
##### From: Paolo Bonzini <pbonzini@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Paolo Bonzini <pbonzini@redhat.com>
X-Patchwork-Id: 12246049
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-21.4 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_PATCH,INCLUDES_PULL_REQUEST,MAILING_LIST_MULTI,MENTIONS_GIT_HOSTING,
	SPF_HELO_NONE,SPF_PASS autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 6F2FBC433ED
	for <kvm@archiver.kernel.org>; Sat,  8 May 2021 13:04:48 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 3FAF7610A7
	for <kvm@archiver.kernel.org>; Sat,  8 May 2021 13:04:48 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S231166AbhEHNFs (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Sat, 8 May 2021 09:05:48 -0400
Received: from us-smtp-delivery-124.mimecast.com ([170.10.133.124]:22609 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S231163AbhEHNFk (ORCPT
        <rfc822;kvm@vger.kernel.org>); Sat, 8 May 2021 09:05:40 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1620479079;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=skQAYTO3lrX6st7yGY+MvBv6eqI3dj5Prs9fSDNzCCg=;
        b=LKDanSx4cbrwOx4luiA2djUfPWSAfhiIW9g+lPhmP/MQ1Su0DAfzRXprWCGz5mojfaUKAT
        5izqHm71f2d0uRW9vWeEizBHo0Cdtu5osQzH18Tu84BPbffXCHKiJl4f5oB0liTyGGRprE
        EKWFY18/LzxRdfVmOHxquMxmd+A+KNY=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-586-WRSs63fKMX20D1OlcrG1zw-1; Sat, 08 May 2021 09:04:37 -0400
X-MC-Unique: WRSs63fKMX20D1OlcrG1zw-1
Received: from smtp.corp.redhat.com (int-mx08.intmail.prod.int.phx2.redhat.com
 [10.5.11.23])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 6C39C10066E7;
        Sat,  8 May 2021 13:04:36 +0000 (UTC)
Received: from virtlab701.virt.lab.eng.bos.redhat.com
 (virtlab701.virt.lab.eng.bos.redhat.com [10.19.152.228])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 29499E16B;
        Sat,  8 May 2021 13:04:36 +0000 (UTC)
From: Paolo Bonzini <pbonzini@redhat.com>
To: linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Subject: [GIT PULL] Second batch of KVM changes for Linux 5.13
Date: Sat,  8 May 2021 09:04:35 -0400
Message-Id: <20210508130435.201020-1-pbonzini@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.84 on 10.5.11.23
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Linus,

The following changes since commit 9ccce092fc64d19504fa54de4fd659e279cc92e7:

  Merge tag 'for-linus-5.13-ofs-1' of git://git.kernel.org/pub/scm/linux/kernel/git/hubcap/linux (2021-05-02 14:13:46 -0700)

are available in the Git repository at:

  https://git.kernel.org/pub/scm/virt/kvm/kvm.git tags/for-linus

for you to fetch changes up to ce7ea0cfdc2e9ff31d12da31c3226deddb9644f5:

  KVM: SVM: Move GHCB unmapping to fix RCU warning (2021-05-07 06:06:23 -0400)

----------------------------------------------------------------
* Lots of bug fixes.

* Fix virtualization of RDPID

* Virtualization of DR6_BUS_LOCK

* More nested virtualization migration fixes (nSVM and eVMCS)

* Fix for KVM guest hibernation

* Fix for warning in SEV-ES SRCU usage

----------------------------------------------------------------
Benjamin Segall (1):
      kvm: exit halt polling on need_resched() as well

Bill Wendling (1):
      selftests: kvm: remove reassignment of non-absolute variables

Chenyi Qiang (1):
      KVM: X86: Add support for the emulation of DR6_BUS_LOCK bit

Colin Ian King (1):
      KVM: x86: Fix potential fput on a null source_kvm_file

David Matlack (1):
      kvm: Cap halt polling at kvm->max_halt_poll_ns

Kai Huang (2):
      KVM: x86/mmu: Avoid unnecessary page table allocation in kvm_tdp_mmu_map()
      KVM: x86/mmu: Fix kdoc of __handle_changed_spte

Maxim Levitsky (5):
      KVM: nSVM: fix a typo in svm_leave_nested
      KVM: nSVM: fix few bugs in the vmcb02 caching logic
      KVM: nSVM: leave the guest mode prior to loading a nested state
      KVM: nSVM: always restore the L1's GIF on migration
      KVM: nSVM: remove a warning about vmcb01 VM exit reason

Nicholas Piggin (1):
      KVM: PPC: Book3S HV: Fix conversion to gfn-based MMU notifier callbacks

Paolo Bonzini (1):
      KVM: X86: Expose bus lock debug exception to guest

Sean Christopherson (17):
      KVM: VMX: Do not advertise RDPID if ENABLE_RDTSCP control is unsupported
      KVM: x86: Emulate RDPID only if RDTSCP is supported
      KVM: SVM: Inject #UD on RDTSCP when it should be disabled in the guest
      KVM: x86: Move RDPID emulation intercept to its own enum
      KVM: VMX: Disable preemption when probing user return MSRs
      KVM: SVM: Probe and load MSR_TSC_AUX regardless of RDTSCP support in host
      KVM: x86: Add support for RDPID without RDTSCP
      KVM: VMX: Configure list of user return MSRs at module init
      KVM: VMX: Use flag to indicate "active" uret MSRs instead of sorting list
      KVM: VMX: Use common x86's uret MSR list as the one true list
      KVM: VMX: Disable loading of TSX_CTRL MSR the more conventional way
      KVM: x86: Export the number of uret MSRs to vendor modules
      KVM: x86: Move uret MSR slot management to common x86
      KVM: x86: Tie Intel and AMD behavior for MSR_TSC_AUX to guest CPU model
      KVM: x86: Hide RDTSCP and RDPID if MSR_TSC_AUX probing failed
      KVM: x86: Prevent KVM SVM from loading on kernels with 5-level paging
      KVM: SVM: Invert user pointer casting in SEV {en,de}crypt helpers

Shahin, Md Shahadat Hossain (1):
      kvm/x86: Fix 'lpages' kvm stat for TDM MMU

Siddharth Chandrasekaran (2):
      doc/kvm: Fix wrong entry for KVM_CAP_X86_MSR_FILTER
      KVM: x86: Hoist input checks in kvm_add_msr_filter()

Stefan Raspl (1):
      tools/kvm_stat: Fix documentation typo

Thomas Gleixner (2):
      KVM: x86: Cancel pvclock_gtod_work on module removal
      KVM: x86: Prevent deadlock against tk_core.seq

Tom Lendacky (1):
      KVM: SVM: Move GHCB unmapping to fix RCU warning

Vitaly Kuznetsov (9):
      x86/kvm: Fix pr_info() for async PF setup/teardown
      x86/kvm: Teardown PV features on boot CPU as well
      x86/kvm: Disable kvmclock on all CPUs on shutdown
      x86/kvm: Disable all PV features on crash
      x86/kvm: Unify kvm_pv_guest_cpu_reboot() with kvm_guest_cpu_offline()
      KVM: nVMX: Always make an attempt to map eVMCS after migration
      KVM: selftests: evmcs_test: Check that VMLAUNCH with bogus EVMPTR is causing #UD
      KVM: selftests: evmcs_test: Check that VMCS12 is alway properly synced to eVMCS after restore
      KVM: nVMX: Properly pad 'struct kvm_vmx_nested_state_hdr'

Wanpeng Li (1):
      KVM: LAPIC: Accurately guarantee busy wait for timer to expire when using hv_timer

 Documentation/virt/kvm/api.rst                    |   4 +-
 arch/powerpc/include/asm/kvm_book3s.h             |   2 +-
 arch/powerpc/kvm/book3s_64_mmu_hv.c               |  46 +++--
 arch/powerpc/kvm/book3s_64_mmu_radix.c            |   5 +-
 arch/x86/include/asm/kvm_host.h                   |  15 +-
 arch/x86/include/asm/kvm_para.h                   |  10 +-
 arch/x86/include/uapi/asm/kvm.h                   |   2 +
 arch/x86/kernel/kvm.c                             | 129 ++++++++-----
 arch/x86/kernel/kvmclock.c                        |  26 +--
 arch/x86/kvm/cpuid.c                              |  20 +-
 arch/x86/kvm/emulate.c                            |   2 +-
 arch/x86/kvm/kvm_emulate.h                        |   1 +
 arch/x86/kvm/lapic.c                              |   2 +-
 arch/x86/kvm/mmu/mmu.c                            |  20 +-
 arch/x86/kvm/mmu/tdp_mmu.c                        |  17 +-
 arch/x86/kvm/svm/nested.c                         |  23 ++-
 arch/x86/kvm/svm/sev.c                            |  32 ++--
 arch/x86/kvm/svm/svm.c                            |  62 +++---
 arch/x86/kvm/svm/svm.h                            |   1 +
 arch/x86/kvm/vmx/capabilities.h                   |   3 +
 arch/x86/kvm/vmx/nested.c                         |  29 ++-
 arch/x86/kvm/vmx/vmx.c                            | 220 +++++++++++-----------
 arch/x86/kvm/vmx/vmx.h                            |  12 +-
 arch/x86/kvm/x86.c                                | 153 +++++++++++----
 tools/kvm/kvm_stat/kvm_stat.txt                   |   2 +-
 tools/testing/selftests/kvm/lib/x86_64/handlers.S |   4 +-
 tools/testing/selftests/kvm/x86_64/evmcs_test.c   |  88 +++++++--
 virt/kvm/kvm_main.c                               |   7 +-
 28 files changed, 578 insertions(+), 359 deletions(-)
```
#### [PATCH] Revert "irqbypass: do not start cons/prod when failed connect"
##### From: Zhu Lingshan <lingshan.zhu@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Zhu Lingshan <lingshan.zhu@intel.com>
X-Patchwork-Id: 12245901
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.8 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED,USER_AGENT_GIT
	autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 92E84C433B4
	for <kvm@archiver.kernel.org>; Sat,  8 May 2021 07:17:52 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 4A7D76147D
	for <kvm@archiver.kernel.org>; Sat,  8 May 2021 07:17:52 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S229760AbhEHHSw (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Sat, 8 May 2021 03:18:52 -0400
Received: from mga07.intel.com ([134.134.136.100]:47276 "EHLO mga07.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S229583AbhEHHSv (ORCPT <rfc822;kvm@vger.kernel.org>);
        Sat, 8 May 2021 03:18:51 -0400
IronPort-SDR: 
 yBdZ75bIQn1Hl26P6QEmxPRyaOpaNBUAURl3mCe3XKGVYegBtTeaphoSZt9mwfNRqkxWn29/AP
 BIPgzQcMuoFg==
X-IronPort-AV: E=McAfee;i="6200,9189,9977"; a="262816443"
X-IronPort-AV: E=Sophos;i="5.82,283,1613462400";
   d="scan'208";a="262816443"
Received: from orsmga008.jf.intel.com ([10.7.209.65])
  by orsmga105.jf.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 08 May 2021 00:17:48 -0700
IronPort-SDR: 
 tsgzUZs8tvIizuU72JMmEcN+UYuWGP/CHbcmGM8z+23NbbZK5biOyHJbY9Jc5+K3XprAjh2AvC
 lg6GkNlVctWg==
X-IronPort-AV: E=Sophos;i="5.82,283,1613462400";
   d="scan'208";a="435267317"
Received: from unknown (HELO localhost.localdomain.bj.intel.com)
 ([10.240.193.73])
  by orsmga008-auth.jf.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 08 May 2021 00:17:45 -0700
From: Zhu Lingshan <lingshan.zhu@intel.com>
To: jasowang@redhat.com, mst@redhat.com, maz@kernel.org,
        alex.williamson@redhat.com
Cc: kvm@vger.kernel.org, linux-arm-kernel@lists.infradead.org,
        kvmarm@lists.cs.columbia.edu, cohuck@redhat.com,
        stable@vger.kernel.org, Zhu Lingshan <lingshan.zhu@intel.com>
Subject: [PATCH] Revert "irqbypass: do not start cons/prod when failed
 connect"
Date: Sat,  8 May 2021 15:11:52 +0800
Message-Id: <20210508071152.722425-1-lingshan.zhu@intel.com>
X-Mailer: git-send-email 2.27.0
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This reverts commit a979a6aa009f3c99689432e0cdb5402a4463fb88.

The reverted commit may cause VM freeze on arm64 platform.
Because on arm64 platform, stop a consumer will suspend the VM,
the VM will freeze without a start consumer

Signed-off-by: Zhu Lingshan <lingshan.zhu@intel.com>
Reported-by: Shaokun Zhang <zhangshaokun@hisilicon.com>
Acked-by: Marc Zyngier <maz@kernel.org>
---
 virt/lib/irqbypass.c | 16 ++++++----------
 1 file changed, 6 insertions(+), 10 deletions(-)

```
#### [PATCH v2] KVM: selftests: Print a message if /dev/kvm is missingFrom: David Matlack <dmatlack@google.com>
##### From: David Matlack <dmatlack@google.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: David Matlack <dmatlack@google.com>
X-Patchwork-Id: 12245401
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-26.3 required=3.0 tests=BAYES_00,DKIMWL_WL_MED,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_CR_TRAILER,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,
	USER_AGENT_GIT,USER_IN_DEF_DKIM_WL autolearn=ham autolearn_force=no
	version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id CFE83C433ED
	for <kvm@archiver.kernel.org>; Sat,  8 May 2021 00:29:24 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id A173F60FF3
	for <kvm@archiver.kernel.org>; Sat,  8 May 2021 00:29:24 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S230079AbhEHA3h (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Fri, 7 May 2021 20:29:37 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:47476 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S229880AbhEHA3g (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 7 May 2021 20:29:36 -0400
Received: from mail-pg1-x549.google.com (mail-pg1-x549.google.com
 [IPv6:2607:f8b0:4864:20::549])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 12AB1C061574
        for <kvm@vger.kernel.org>; Fri,  7 May 2021 17:28:36 -0700 (PDT)
Received: by mail-pg1-x549.google.com with SMTP id
 w33-20020a6349210000b029020ed5af91a4so6359114pga.14
        for <kvm@vger.kernel.org>; Fri, 07 May 2021 17:28:36 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=date:message-id:mime-version:subject:from:to:cc;
        bh=SphSvC26ZGxlBkm3BeBKNoj34ApiaYqthl3dh1p5JaA=;
        b=dwdozba0Kg9U9NaGXkRlf8+ZmY43QVsYlEd56RN0AIt9O2vMLU+P3s8uN4ZpKsY9Pu
         uN0FN9xGRXdou1j9Zo3xt/9Werr3j3DumVKd46f01vVRXofLMw7Uxk65HxKrUmCMDXzD
         VCzsoOjIT4pc3XHrw/147XtCmb6j7miL9im6CU2jUMbpyr6lxyMhV/xJLt6nqvcAsVBy
         R3UJHuDfTK/xKeu8hUtNvUWYEol84IdINKnY6wU6NsrOhxmVxN60lu13gZvWyUSXzUnM
         +umuD8BhUoBgnwj4aRgI4+7mUJL5NLJMtwbKlXBU/pG41oK9E6aEI7Zw1LsoPi65ygPB
         xQ7Q==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:date:message-id:mime-version:subject:from:to:cc;
        bh=SphSvC26ZGxlBkm3BeBKNoj34ApiaYqthl3dh1p5JaA=;
        b=s5Nuomacg6eJzYrABx0EcZAOlieg/bcO8UPo5pTR/JDQ1wYw5Z31alCMpixcNbmkNo
         o437HBosVX1HAmV9Wf6O9pbb7TWYddayU4u7H41V5vWXKOg4UamaDESolZqiaDH7kkyw
         rI0Ipd5lgMZsDNrTdtQnXXKNq5NB+sVX4COsK3iXh2TFQZNqTxBQQAVOwP7VC6LGxWaM
         u7r8urVD2ppGR9PrKXaL+UNUtW3v5LlDJux3CXwDKt9CyfvIzTdi0WYyaTeALADUCYM9
         /jDAgA1e7+3nsEM+XTzo1fYIhMn6bz3xSdu398ttJpw2Z8NIIv7ESR9c7jwxgu4Ab4aF
         ohSQ==
X-Gm-Message-State: AOAM531Qf1yx/nIfnVkjLrfAlCucdpYE1PXZTqAiXL/w9AKlXT1cjp20
        Pp4Szq+MBeyHbjrdZFNtclfe9MlTh8r1gk2bMCA9leAf/+Vo6BZVM27qmIBXHeFxx70Rq+r4Nzl
        nBIRqbCeMbnTUov0Lk1eykkraMiVGThLZSgLdjpVygj+mTYMdlkCN4T5WlAOeXGM=
X-Google-Smtp-Source: 
 ABdhPJxFiRAmqpeiaRlsjVw4wHe7AzBIJxMZn2UglcIKWAkWX9bsq06z4g2PNqxFAn/Ucifil5gPLKIe9g9GcA==
X-Received: from dmatlack-heavy.c.googlers.com
 ([fda3:e722:ac3:10:7f:e700:c0a8:19cd])
 (user=dmatlack job=sendgmr) by 2002:a62:25c4:0:b029:276:a40:5729 with SMTP id
 l187-20020a6225c40000b02902760a405729mr13092313pfl.80.1620433715222; Fri, 07
 May 2021 17:28:35 -0700 (PDT)
Date: Sat,  8 May 2021 00:28:32 +0000
Message-Id: <20210508002832.759818-1-dmatlack@google.com>
Mime-Version: 1.0
X-Mailer: git-send-email 2.31.1.607.g51e8a6a459-goog
Subject: [PATCH v2] KVM: selftests: Print a message if /dev/kvm is missing
From: David Matlack <dmatlack@google.com>
To: kvm@vger.kernel.org
Cc: Paolo Bonzini <pbonzini@redhat.com>,
        Andrew Jones <drjones@redhat.com>,
        Aaron Lewis <aaronlewis@google.com>,
        David Matlack <dmatlack@google.com>
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

If a KVM selftest is run on a machine without /dev/kvm, it will exit
silently. Make it easy to tell what's happening by printing an error
message.

Opportunistically consolidate all codepaths that open /dev/kvm into a
single function so they all print the same message.

This slightly changes the semantics of vm_is_unrestricted_guest() by
changing a TEST_ASSERT() to exit(KSFT_SKIP). However
vm_is_unrestricted_guest() is only called in one place
(x86_64/mmio_warning_test.c) and that is to determine if the test should
be skipped or not.

Signed-off-by: David Matlack <dmatlack@google.com>
---
 .../testing/selftests/kvm/include/kvm_util.h  |  1 +
 tools/testing/selftests/kvm/lib/kvm_util.c    | 39 ++++++++++++-------
 .../selftests/kvm/lib/x86_64/processor.c      | 16 ++------
 .../kvm/x86_64/get_msr_index_features.c       |  8 +---
 4 files changed, 32 insertions(+), 32 deletions(-)

```
#### [RFC PATCH v9 01/19] af_vsock: update functions for connectible socket
##### From: Arseny Krasnov <arseny.krasnov@kaspersky.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Arseny Krasnov <arseny.krasnov@kaspersky.com>
X-Patchwork-Id: 12246105
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-19.4 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_CR_TRAILER,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,
	URIBL_BLOCKED,USER_AGENT_GIT autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id CEB12C433B4
	for <kvm@archiver.kernel.org>; Sat,  8 May 2021 16:32:46 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id AC1606140F
	for <kvm@archiver.kernel.org>; Sat,  8 May 2021 16:32:46 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S229765AbhEHQdq (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Sat, 8 May 2021 12:33:46 -0400
Received: from mx13.kaspersky-labs.com ([91.103.66.164]:62453 "EHLO
        mx13.kaspersky-labs.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S229575AbhEHQdp (ORCPT <rfc822;kvm@vger.kernel.org>);
        Sat, 8 May 2021 12:33:45 -0400
Received: from relay13.kaspersky-labs.com (unknown [127.0.0.10])
        by relay13.kaspersky-labs.com (Postfix) with ESMTP id C48A6520FF0;
        Sat,  8 May 2021 19:32:37 +0300 (MSK)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=kaspersky.com;
        s=mail202102; t=1620491557;
        bh=O2X8HgczlbY3D5QaoIUjuA/wlpLEw+fTp5ccpcFwpck=;
        h=From:To:Subject:Date:Message-ID:MIME-Version:Content-Type;
        b=5/MKreaDhaWdwfiwEdOMwq4MLfhdVXQz2RTxUj557GW8MS7J6D4sgpFgaghwIcrwc
         n5ImauVdi6c+saGasvx9VP2+aHKCHJqfPaH0O1qAAlo2i0hDt1ga5y8i99glGsKPrd
         f5De10K7Wh2J6LVwRjLamiAiorATwakltk7K0UfT5XfReBiCY374w8OOiunUKTORVC
         vmgOCfUI1UFqskkHzXfsuMVtEkQSo0WN4akuqgIA4PxmGGTIyOeCTQEy7X7cKI9kbS
         nqElzGHtbtFGKmfM0/8/Ow+7Y4dluzSsinhFuq6aF9jI+CleIfJVVs+JibnKOcQmEA
         BnjrXSc7HZaRQ==
Received: from mail-hq2.kaspersky.com (unknown [91.103.66.206])
        (using TLSv1.2 with cipher ECDHE-RSA-AES128-SHA256 (128/128 bits))
        (Client CN "mail-hq2.kaspersky.com",
 Issuer "Kaspersky MailRelays CA G3" (verified OK))
        by mailhub13.kaspersky-labs.com (Postfix) with ESMTPS id 09698520F1A;
        Sat,  8 May 2021 19:32:36 +0300 (MSK)
Received: from arseniy-pc.avp.ru (10.64.68.129) by hqmailmbx3.avp.ru
 (10.64.67.243) with Microsoft SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_128_CBC_SHA256_P256) id 15.1.2176.2; Sat, 8 May
 2021 19:32:36 +0300
From: Arseny Krasnov <arseny.krasnov@kaspersky.com>
To: Stefan Hajnoczi <stefanha@redhat.com>,
        Stefano Garzarella <sgarzare@redhat.com>,
        "Michael S. Tsirkin" <mst@redhat.com>,
        Jason Wang <jasowang@redhat.com>,
        "David S. Miller" <davem@davemloft.net>,
        Jakub Kicinski <kuba@kernel.org>,
        Arseny Krasnov <arseny.krasnov@kaspersky.com>,
        Jorgen Hansen <jhansen@vmware.com>,
        Colin Ian King <colin.king@canonical.com>,
        Andra Paraschiv <andraprs@amazon.com>,
        Norbert Slusarek <nslusarek@gmx.net>
CC: <kvm@vger.kernel.org>, <virtualization@lists.linux-foundation.org>,
        <netdev@vger.kernel.org>, <linux-kernel@vger.kernel.org>,
        <stsp2@yandex.ru>, <oxffffaa@gmail.com>
Subject: [RFC PATCH v9 01/19] af_vsock: update functions for connectible
 socket
Date: Sat, 8 May 2021 19:32:14 +0300
Message-ID: <20210508163217.3430707-1-arseny.krasnov@kaspersky.com>
X-Mailer: git-send-email 2.25.1
In-Reply-To: <20210508163027.3430238-1-arseny.krasnov@kaspersky.com>
References: <20210508163027.3430238-1-arseny.krasnov@kaspersky.com>
MIME-Version: 1.0
X-Originating-IP: [10.64.68.129]
X-ClientProxiedBy: hqmailmbx2.avp.ru (10.64.67.242) To hqmailmbx3.avp.ru
 (10.64.67.243)
X-KSE-ServerInfo: hqmailmbx3.avp.ru, 9
X-KSE-AntiSpam-Interceptor-Info: scan successful
X-KSE-AntiSpam-Version: 5.9.20, Database issued on: 05/08/2021 16:21:10
X-KSE-AntiSpam-Status: KAS_STATUS_NOT_DETECTED
X-KSE-AntiSpam-Method: none
X-KSE-AntiSpam-Rate: 10
X-KSE-AntiSpam-Info: Lua profiles 163552 [May 08 2021]
X-KSE-AntiSpam-Info: Version: 5.9.20.0
X-KSE-AntiSpam-Info: Envelope from: arseny.krasnov@kaspersky.com
X-KSE-AntiSpam-Info: LuaCore: 445 445 d5f7ae5578b0f01c45f955a2a751ac25953290c9
X-KSE-AntiSpam-Info: {Prob_from_in_msgid}
X-KSE-AntiSpam-Info: {Tracking_from_domain_doesnt_match_to}
X-KSE-AntiSpam-Info: 
 127.0.0.199:7.1.2;arseniy-pc.avp.ru:7.1.1;d41d8cd98f00b204e9800998ecf8427e.com:7.1.1;kaspersky.com:7.1.1
X-KSE-AntiSpam-Info: Rate: 10
X-KSE-AntiSpam-Info: Status: not_detected
X-KSE-AntiSpam-Info: Method: none
X-KSE-Antiphishing-Info: Clean
X-KSE-Antiphishing-ScanningType: Deterministic
X-KSE-Antiphishing-Method: None
X-KSE-Antiphishing-Bases: 05/08/2021 16:24:00
X-KSE-AttachmentFiltering-Interceptor-Info: no applicable attachment filtering
 rules found
X-KSE-Antivirus-Interceptor-Info: scan successful
X-KSE-Antivirus-Info: Clean, bases: 08.05.2021 12:32:00
X-KSE-BulkMessagesFiltering-Scan-Result: InTheLimit
X-KSE-AttachmentFiltering-Interceptor-Info: no applicable attachment filtering
 rules found
X-KSE-BulkMessagesFiltering-Scan-Result: InTheLimit
X-KLMS-Rule-ID: 52
X-KLMS-Message-Action: clean
X-KLMS-AntiSpam-Status: not scanned, disabled by settings
X-KLMS-AntiSpam-Interceptor-Info: not scanned
X-KLMS-AntiPhishing: Clean, bases: 2021/05/08 15:50:00
X-KLMS-AntiVirus: Kaspersky Security for Linux Mail Server, version 8.0.3.30,
 bases: 2021/05/08 12:32:00 #16600610
X-KLMS-AntiVirus-Status: Clean, skipped
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This prepares af_vsock.c for SEQPACKET support: some functions such
as setsockopt(), getsockopt(), connect(), recvmsg(), sendmsg() are
shared between both types of sockets, so rename them in general
manner.

Signed-off-by: Arseny Krasnov <arseny.krasnov@kaspersky.com>
Reviewed-by: Stefano Garzarella <sgarzare@redhat.com>
---
 net/vmw_vsock/af_vsock.c | 64 +++++++++++++++++++++-------------------
 1 file changed, 34 insertions(+), 30 deletions(-)

```
