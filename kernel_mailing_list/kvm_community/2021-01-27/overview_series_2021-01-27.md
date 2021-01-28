#### [GIT PULL] KVM fixes for Linux 5.11-rc6
##### From: Paolo Bonzini <pbonzini@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Paolo Bonzini <pbonzini@redhat.com>
X-Patchwork-Id: 12049629
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-21.1 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_PATCH,INCLUDES_PULL_REQUEST,MAILING_LIST_MULTI,MENTIONS_GIT_HOSTING,
	SPF_HELO_NONE,SPF_PASS autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 7F283C43381
	for <kvm@archiver.kernel.org>; Wed, 27 Jan 2021 10:26:11 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 4E9A02072C
	for <kvm@archiver.kernel.org>; Wed, 27 Jan 2021 10:26:11 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S235853AbhA0K0F (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Wed, 27 Jan 2021 05:26:05 -0500
Received: from us-smtp-delivery-124.mimecast.com ([63.128.21.124]:25099 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S233322AbhA0KYR (ORCPT
        <rfc822;kvm@vger.kernel.org>); Wed, 27 Jan 2021 05:24:17 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1611742970;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=jr7D381srKp0j6rCe+jk22uZZDkym4sUt+94TC8WIVE=;
        b=GCop8ywJ9SHLoEF8ZaSl9Lp/EACcifqiZThXxxS4jB2zvHDaPquvYA8SWpME1jxu19XKc3
        1Ml38NjhdSaX4Hc5WTOwJruGWr1YJrlMu91Yq6RezMji6k+Eq1N2/wDTg3qO7uYqtetBYX
        u7N8aiBqBHhlNdnSsKYe63xN7Znybmg=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-264-X0xQ1S6GOFqo42lEBqBvvQ-1; Wed, 27 Jan 2021 05:22:49 -0500
X-MC-Unique: X0xQ1S6GOFqo42lEBqBvvQ-1
Received: from smtp.corp.redhat.com (int-mx01.intmail.prod.int.phx2.redhat.com
 [10.5.11.11])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id E3EEE190B2A0;
        Wed, 27 Jan 2021 10:22:47 +0000 (UTC)
Received: from virtlab701.virt.lab.eng.bos.redhat.com
 (virtlab701.virt.lab.eng.bos.redhat.com [10.19.152.228])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 90A066F92F;
        Wed, 27 Jan 2021 10:22:47 +0000 (UTC)
From: Paolo Bonzini <pbonzini@redhat.com>
To: torvalds@linux-foundation.org
Cc: linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Subject: [GIT PULL] KVM fixes for Linux 5.11-rc6
Date: Wed, 27 Jan 2021 05:22:46 -0500
Message-Id: <20210127102246.1599444-1-pbonzini@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.11
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Linus,

I sent this yesterday but I cannot find it in the archives (weird),
so I am resending it.

The following changes since commit 7c53f6b671f4aba70ff15e1b05148b10d58c2837:

  Linux 5.11-rc3 (2021-01-10 14:34:50 -0800)

are available in the Git repository at:

  https://git.kernel.org/pub/scm/virt/kvm/kvm.git tags/for-linus

for you to fetch changes up to 9a78e15802a87de2b08dfd1bd88e855201d2c8fa:

  KVM: x86: allow KVM_REQ_GET_NESTED_STATE_PAGES outside guest mode for VMX (2021-01-25 18:54:09 -0500)

----------------------------------------------------------------
* x86 bugfixes
* Documentation fixes
* Avoid performance regression due to SEV-ES patches

ARM:
- Don't allow tagged pointers to point to memslots
- Filter out ARMv8.1+ PMU events on v8.0 hardware
- Hide PMU registers from userspace when no PMU is configured
- More PMU cleanups
- Don't try to handle broken PSCI firmware
- More sys_reg() to reg_to_encoding() conversions

----------------------------------------------------------------
Alexandru Elisei (1):
      KVM: arm64: Use the reg_to_encoding() macro instead of sys_reg()

David Brazdil (1):
      KVM: arm64: Allow PSCI SYSTEM_OFF/RESET to return

Jay Zhou (1):
      KVM: x86: get smi pending status correctly

Like Xu (2):
      KVM: x86/pmu: Fix UBSAN shift-out-of-bounds warning in intel_pmu_refresh()
      KVM: x86/pmu: Fix HW_REF_CPU_CYCLES event pseudo-encoding in intel_arch_events[]

Lorenzo Brescia (1):
      kvm: tracing: Fix unmatched kvm_entry and kvm_exit events

Marc Zyngier (4):
      KVM: arm64: Hide PMU registers from userspace when not available
      KVM: arm64: Simplify handling of absent PMU system registers
      KVM: arm64: Filter out v8.1+ events on v8.0 HW
      KVM: Forbid the use of tagged userspace addresses for memslots

Maxim Levitsky (1):
      KVM: nVMX: Sync unsync'd vmcs02 state to vmcs12 on migration

Paolo Bonzini (2):
      Merge tag 'kvmarm-fixes-5.11-2' of git://git.kernel.org/.../kvmarm/kvmarm into HEAD
      KVM: x86: allow KVM_REQ_GET_NESTED_STATE_PAGES outside guest mode for VMX

Quentin Perret (1):
      KVM: Documentation: Fix spec for KVM_CAP_ENABLE_CAP_VM

Sean Christopherson (3):
      KVM: x86: Add more protection against undefined behavior in rsvd_bits()
      KVM: SVM: Unconditionally sync GPRs to GHCB on VMRUN of SEV-ES guest
      KVM: x86: Revert "KVM: x86: Mark GPRs dirty when written"

Steven Price (1):
      KVM: arm64: Compute TPIDR_EL2 ignoring MTE tag

Zenghui Yu (1):
      KVM: Documentation: Update description of KVM_{GET,CLEAR}_DIRTY_LOG

 Documentation/virt/kvm/api.rst       | 21 ++++----
 arch/arm64/kvm/arm.c                 |  3 +-
 arch/arm64/kvm/hyp/nvhe/psci-relay.c | 13 ++---
 arch/arm64/kvm/pmu-emul.c            | 10 ++--
 arch/arm64/kvm/sys_regs.c            | 93 ++++++++++++++++++++++--------------
 arch/x86/kvm/kvm_cache_regs.h        | 51 ++++++++++----------
 arch/x86/kvm/mmu.h                   |  9 +++-
 arch/x86/kvm/svm/nested.c            |  3 ++
 arch/x86/kvm/svm/sev.c               | 15 +++---
 arch/x86/kvm/svm/svm.c               |  2 +
 arch/x86/kvm/vmx/nested.c            | 44 ++++++++++++-----
 arch/x86/kvm/vmx/pmu_intel.c         |  6 ++-
 arch/x86/kvm/vmx/vmx.c               |  2 +
 arch/x86/kvm/x86.c                   | 11 +++--
 virt/kvm/kvm_main.c                  |  1 +
 15 files changed, 172 insertions(+), 112 deletions(-)
```
#### [PATCH v3 1/4] KVM: arm64: GICv4.1: Add function to get VLPI state
##### From: Shenming Lu <lushenming@huawei.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Shenming Lu <lushenming@huawei.com>
X-Patchwork-Id: 12049913
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.7 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED,USER_AGENT_GIT
	autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 8139BC433E9
	for <kvm@archiver.kernel.org>; Wed, 27 Jan 2021 12:19:08 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 463DD20795
	for <kvm@archiver.kernel.org>; Wed, 27 Jan 2021 12:19:08 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S237771AbhA0MSu (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Wed, 27 Jan 2021 07:18:50 -0500
Received: from szxga05-in.huawei.com ([45.249.212.191]:12036 "EHLO
        szxga05-in.huawei.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S237714AbhA0MOz (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 27 Jan 2021 07:14:55 -0500
Received: from DGGEMS404-HUB.china.huawei.com (unknown [172.30.72.60])
        by szxga05-in.huawei.com (SkyGuard) with ESMTP id 4DQjCm6jHMzMQjY;
        Wed, 27 Jan 2021 20:12:36 +0800 (CST)
Received: from DESKTOP-7FEPK9S.china.huawei.com (10.174.186.182) by
 DGGEMS404-HUB.china.huawei.com (10.3.19.204) with Microsoft SMTP Server id
 14.3.498.0; Wed, 27 Jan 2021 20:13:59 +0800
From: Shenming Lu <lushenming@huawei.com>
To: Marc Zyngier <maz@kernel.org>, Eric Auger <eric.auger@redhat.com>,
        "Will Deacon" <will@kernel.org>,
        <linux-arm-kernel@lists.infradead.org>,
        <kvmarm@lists.cs.columbia.edu>, <kvm@vger.kernel.org>,
        <linux-kernel@vger.kernel.org>
CC: Alex Williamson <alex.williamson@redhat.com>,
        Cornelia Huck <cohuck@redhat.com>,
        Lorenzo Pieralisi <lorenzo.pieralisi@arm.com>,
        <wanghaibin.wang@huawei.com>, <yuzenghui@huawei.com>,
        <lushenming@huawei.com>
Subject: [PATCH v3 1/4] KVM: arm64: GICv4.1: Add function to get VLPI state
Date: Wed, 27 Jan 2021 20:13:34 +0800
Message-ID: <20210127121337.1092-2-lushenming@huawei.com>
X-Mailer: git-send-email 2.27.0.windows.1
In-Reply-To: <20210127121337.1092-1-lushenming@huawei.com>
References: <20210127121337.1092-1-lushenming@huawei.com>
MIME-Version: 1.0
X-Originating-IP: [10.174.186.182]
X-CFilter-Loop: Reflected
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

With GICv4.1 and the vPE unmapped, which indicates the invalidation
of any VPT caches associated with the vPE, we can get the VLPI state
by peeking at the VPT. So we add a function for this.

Signed-off-by: Shenming Lu <lushenming@huawei.com>
---
 arch/arm64/kvm/vgic/vgic-v4.c | 19 +++++++++++++++++++
 arch/arm64/kvm/vgic/vgic.h    |  1 +
 2 files changed, 20 insertions(+)

```
#### [PATCH 1/5] KVM: Make the maximum number of user memslots a per-VM thing
##### From: Vitaly Kuznetsov <vkuznets@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Vitaly Kuznetsov <vkuznets@redhat.com>
X-Patchwork-Id: 12050749
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.1 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_CR_TRAILER,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS
	autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 7778DC433E9
	for <kvm@archiver.kernel.org>; Wed, 27 Jan 2021 17:59:36 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 3033764D9A
	for <kvm@archiver.kernel.org>; Wed, 27 Jan 2021 17:59:36 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1344372AbhA0R70 (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Wed, 27 Jan 2021 12:59:26 -0500
Received: from us-smtp-delivery-124.mimecast.com ([216.205.24.124]:50718 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1344345AbhA0R7K (ORCPT
        <rfc822;kvm@vger.kernel.org>); Wed, 27 Jan 2021 12:59:10 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1611770262;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding:
         in-reply-to:in-reply-to:references:references;
        bh=bFzc083SDCVVQmZ3TEE32kOyxiqZz+UgdILDBdrPWO0=;
        b=LXeKf1+vv3y6rkApVVEYY5uUeYq1H8APwKq6v7X1OmIQG+H08PdmrcMWPEAWT8NAClAw3k
        fJC9i5TNm0Rha+1pGvWoOJUnqAIQT29q7/Mdg4LxeAWfhBCb7qttW1TGZ/PZanjGxRNR8W
        XIschmE7GqS/Xs/VQr6EE4JnHOM5faI=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-345-_Z2AUTP_M0O_vX18-8mUUQ-1; Wed, 27 Jan 2021 12:57:41 -0500
X-MC-Unique: _Z2AUTP_M0O_vX18-8mUUQ-1
Received: from smtp.corp.redhat.com (int-mx03.intmail.prod.int.phx2.redhat.com
 [10.5.11.13])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id AB5AD8066EA;
        Wed, 27 Jan 2021 17:57:39 +0000 (UTC)
Received: from vitty.brq.redhat.com (unknown [10.40.195.57])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 8DEB460864;
        Wed, 27 Jan 2021 17:57:37 +0000 (UTC)
From: Vitaly Kuznetsov <vkuznets@redhat.com>
To: kvm@vger.kernel.org, Paolo Bonzini <pbonzini@redhat.com>
Cc: Sean Christopherson <seanjc@google.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Igor Mammedov <imammedo@redhat.com>,
        "Maciej S . Szmigiero" <maciej.szmigiero@oracle.com>
Subject: [PATCH 1/5] KVM: Make the maximum number of user memslots a per-VM
 thing
Date: Wed, 27 Jan 2021 18:57:27 +0100
Message-Id: <20210127175731.2020089-2-vkuznets@redhat.com>
In-Reply-To: <20210127175731.2020089-1-vkuznets@redhat.com>
References: <20210127175731.2020089-1-vkuznets@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.13
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Limiting the maximum number of user memslots globally can be undesirable as
different VMs may have different needs. Generally, a relatively small
number should suffice and a VMM may want to enforce the limitation so a VM
won't accidentally eat too much memory. On the other hand, the number of
required memslots can depend on the number of assigned vCPUs, e.g. each
Hyper-V SynIC may require up to two additional slots per vCPU.

Prepare to limit the maximum number of user memslots per-VM. No real
functional change in this patch as the limit is still hard-coded to
KVM_USER_MEM_SLOTS.

Suggested-by: Sean Christopherson <seanjc@google.com>
Signed-off-by: Vitaly Kuznetsov <vkuznets@redhat.com>
---
 arch/powerpc/kvm/book3s_hv.c |  2 +-
 arch/s390/kvm/kvm-s390.c     |  2 +-
 include/linux/kvm_host.h     |  1 +
 virt/kvm/dirty_ring.c        |  2 +-
 virt/kvm/kvm_main.c          | 11 ++++++-----
 5 files changed, 10 insertions(+), 8 deletions(-)

```
#### [PATCH kvm-unit-tests] x86: use -cpu max instead of -cpu host
##### From: Paolo Bonzini <pbonzini@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Paolo Bonzini <pbonzini@redhat.com>
X-Patchwork-Id: 12049559
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.8 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT autolearn=ham
	autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id A31A5C43381
	for <kvm@archiver.kernel.org>; Wed, 27 Jan 2021 09:57:43 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 4E8EB20739
	for <kvm@archiver.kernel.org>; Wed, 27 Jan 2021 09:57:43 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S234830AbhA0J5j (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Wed, 27 Jan 2021 04:57:39 -0500
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:41548 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S235488AbhA0JxR (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 27 Jan 2021 04:53:17 -0500
Received: from mail-ed1-x52c.google.com (mail-ed1-x52c.google.com
 [IPv6:2a00:1450:4864:20::52c])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 81DADC06178A
        for <kvm@vger.kernel.org>; Wed, 27 Jan 2021 01:52:37 -0800 (PST)
Received: by mail-ed1-x52c.google.com with SMTP id j13so1678235edp.2
        for <kvm@vger.kernel.org>; Wed, 27 Jan 2021 01:52:37 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=sender:from:to:cc:subject:date:message-id:mime-version
         :content-transfer-encoding;
        bh=BKiGeCY30LxdXtXYtI8PHHaDHc9dLjGHHBqPPsCS+f0=;
        b=KPEtaCgfMgXZz0v/ms9wLhVOVP8cpev0WGYEBZIG2PZy+wyV57jCz4pDu0AyXhYIKS
         AznVBThkXIOnhfZtXsL8+gaWaPIGQ4kHOQrUzTa3EZGkkApXnt5irnJWGLhVjp8WpGix
         lHg+oPT9zG4KRyuI3WZ2+uN9nM5FVfgcJtwqlzhlduMIyqLqPLZm2sa1jQmecDc7WSma
         G3MXLQHf2cKMVC4SY0CQmEP+vEsfKGm0zt8SKxEn7JLci0kAC20d14a95TXN5RwBhgWF
         dUw1dC7vhSG7NRP+KCxSROifWFGGKYOV3ClXRG8joQ/NshfYCLwZ9kI/ZbUgo5Tr3dlD
         EBtA==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:sender:from:to:cc:subject:date:message-id
         :mime-version:content-transfer-encoding;
        bh=BKiGeCY30LxdXtXYtI8PHHaDHc9dLjGHHBqPPsCS+f0=;
        b=OI3ay2Qiz05komjIptgl5qOvB6Nrn2sUwARZALh5LJnrnmrnzxAOBoL1u5gCs+fvOV
         YcHbj5F4bOscQzZH3+oR8nln1Vai2H4OyyqKsTl8V+s6hpzefCmBIWuOiXX0029Znl+3
         X4M5DcuTveAQQtfH774QfxxFcP+qHiGZ8fg93/jf42J5hJ6eQlUnA2rpdjqRZ9dWa81h
         iXjR4KxouiEAcig4SjvQRfc0OXtqlEvwyBwnWJYdqPUiIdI3kQu+SXkDNaufwCZVNESd
         jj7uspkuGwLerKliHJjiKmK4pEVv0fD0Ah2bY57IBmFchCP5zUhHi0MoDkg3l+e5A4e0
         eSVQ==
X-Gm-Message-State: AOAM530qW6a+WQf1OR9rv5bmxbjyZLqYEBVMp1y3ijJmkLMmY+NXr5g4
        pqjTzO67HmGEondA5mLEusR/Xn0RYYw7oA==
X-Google-Smtp-Source: 
 ABdhPJxYEgpBZHhMNggQoP1dw8Flw/KobqdraSONmXuE91pWqJV45/ZYJX1JTJbiv9XCrvWfdV5toQ==
X-Received: by 2002:a05:6402:1682:: with SMTP id
 a2mr8458434edv.30.1611741156269;
        Wed, 27 Jan 2021 01:52:36 -0800 (PST)
Received: from avogadro.lan ([2001:b07:6468:f312:c8dd:75d4:99ab:290a])
        by smtp.gmail.com with ESMTPSA id
 x25sm926265edv.65.2021.01.27.01.52.35
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Wed, 27 Jan 2021 01:52:35 -0800 (PST)
Sender: Paolo Bonzini <paolo.bonzini@gmail.com>
From: Paolo Bonzini <pbonzini@redhat.com>
To: kvm@vger.kernel.org
Cc: thuth@redhat.com
Subject: [PATCH kvm-unit-tests] x86: use -cpu max instead of -cpu host
Date: Wed, 27 Jan 2021 10:52:34 +0100
Message-Id: <20210127095234.476291-1-pbonzini@redhat.com>
X-Mailer: git-send-email 2.29.2
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This allows the tests to run under TCG as well.  "-cpu max" is not available on
CentOS 7, however that doesn't change much for our CI since we weren't testing
the CentOS 7 + KVM combination anyway.

Signed-off-by: Paolo Bonzini <pbonzini@redhat.com>
Reviewed-by: Thomas Huth <thuth@redhat.com>
---
 .gitlab-ci.yml    |  4 +++-
 x86/unittests.cfg | 40 ++++++++++++++++++++--------------------
 2 files changed, 23 insertions(+), 21 deletions(-)

```
#### [PATCH] KVM: x86/mmu: Add '__func__' in rmap_printk()
##### From: Stephen Zhang <stephenzhangzsd@gmail.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Stephen Zhang <stephenzhangzsd@gmail.com>
X-Patchwork-Id: 12048885
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-15.8 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,DKIM_VALID_AU,FREEMAIL_FORGED_FROMDOMAIN,FREEMAIL_FROM,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT
	autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 76646C433E0
	for <kvm@archiver.kernel.org>; Wed, 27 Jan 2021 04:27:11 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 2D3C020717
	for <kvm@archiver.kernel.org>; Wed, 27 Jan 2021 04:27:11 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S238615AbhA0E0o (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 26 Jan 2021 23:26:44 -0500
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:37166 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S232155AbhA0DC5 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 26 Jan 2021 22:02:57 -0500
Received: from mail-pf1-x42e.google.com (mail-pf1-x42e.google.com
 [IPv6:2607:f8b0:4864:20::42e])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 000ACC061756;
        Tue, 26 Jan 2021 18:08:53 -0800 (PST)
Received: by mail-pf1-x42e.google.com with SMTP id o20so208449pfu.0;
        Tue, 26 Jan 2021 18:08:53 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=from:to:cc:subject:date:message-id;
        bh=YpCzMfgjbd9EhyR5dL1N/GmWwAHrDvmZHlxmEq38Oio=;
        b=PquFxkORYMlu8/+sBKicjDpcfQEvqgovRJSipjrhZakbngIK1WnjR8VN7Hyf2KgRe5
         OlU8GPQdEqzr3x8dUH6zTNIcAwM1l7ek70K2amHW056j/xRJXgzfxXzfCPxbuht36MEZ
         1D5SaNnm3bpoL//sMa6+fG73hqFw0587W5sBAqSQPVtYWg0jIgB28oFh+4gaoWKcvEBG
         bQgVeKnRF3NqxdEWR0h0kHTtRlUfLyZZYAoItvki6VH9rulVIRJMh1t0IHzunbrg3zE6
         7cSzBH8DV6u8Rc/J0RvwnpLnlaVusd5UpUW25NI8AM9VkoBrejEZbjaHdsVo/9pqzCKS
         mpzQ==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id;
        bh=YpCzMfgjbd9EhyR5dL1N/GmWwAHrDvmZHlxmEq38Oio=;
        b=EgsU9XBIfc02P4xSgiirZlWnd+ODZaPPoKpN52nK1q9DHVjQ9p4osfFc//4oxLPnBC
         z1za0VAW3v74oAMbpaqDEMk0brkYr8nMSpEyT06+zutuGIX4NtR4K2NuGW/9vXHSTYpk
         mgFvMb+3eK3emwRhQ7oy8c4C4PUBoLS5QGne5ksGI8K0dOwvBcppf8pxqfASKybG2+nb
         +vJsur8RBfgUAiLeLTCQ8LTBvWa2nW75m5k+Tb6Zume4MoGFVFbfveSUeqz7PZHINTxV
         jyiYuYLID0WolTPvZI2ytyiBbyIdXhEkw3jmMoX9KL0K1DdubHctJJLM72ijjXLwPCc2
         U3VQ==
X-Gm-Message-State: AOAM532zKTRP1OMTM2THqMQXEdwyzRw/liqNkK0whTuw6NadEX0GoNSl
        TapSY067eLvmaxNljum/APk=
X-Google-Smtp-Source: 
 ABdhPJzZMbtBgsFuAqjEZrQ1KhRA+9m+cvy32JRIBPLkHUaC/9Q5HVWJNHTI0FfvCeG2BKmEP/vtBA==
X-Received: by 2002:a62:1ec1:0:b029:1a8:2c01:13c0 with SMTP id
 e184-20020a621ec10000b02901a82c0113c0mr8093132pfe.8.1611713333595;
        Tue, 26 Jan 2021 18:08:53 -0800 (PST)
Received: from localhost.localdomain ([125.227.22.95])
        by smtp.gmail.com with ESMTPSA id
 j6sm327359pfg.159.2021.01.26.18.08.49
        (version=TLS1_2 cipher=ECDHE-ECDSA-AES128-GCM-SHA256 bits=128/128);
        Tue, 26 Jan 2021 18:08:53 -0800 (PST)
From: Stephen Zhang <stephenzhangzsd@gmail.com>
To: pbonzini@redhat.com, seanjc@google.com, vkuznets@redhat.com,
        wanpengli@tencent.com, jmattson@google.com, joro@8bytes.org,
        tglx@linutronix.de, mingo@redhat.com, bp@alien8.de, x86@kernel.org,
        hpa@zytor.com
Cc: kvm@vger.kernel.org, linux-kernel@vger.kernel.org,
        Stephen Zhang <stephenzhangzsd@gmail.com>
Subject: [PATCH] KVM: x86/mmu: Add '__func__' in rmap_printk()
Date: Wed, 27 Jan 2021 10:08:45 +0800
Message-Id: <1611713325-3591-1-git-send-email-stephenzhangzsd@gmail.com>
X-Mailer: git-send-email 1.8.3.1
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Given the common pattern:

rmap_printk("%s:"..., __func__,...)

we could improve this by adding '__func__' in rmap_printk().

Signed-off-by: Stephen Zhang <stephenzhangzsd@gmail.com>
---
 arch/x86/kvm/mmu/mmu.c          | 20 ++++++++++----------
 arch/x86/kvm/mmu/mmu_internal.h |  2 +-
 2 files changed, 11 insertions(+), 11 deletions(-)

```
#### [PATCH V2] Fix unsynchronized access to sev members through svm_register_enc_region
##### From: Peter Gonda <pgonda@google.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Peter Gonda <pgonda@google.com>
X-Patchwork-Id: 12050539
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-26.2 required=3.0 tests=BAYES_00,DKIMWL_WL_MED,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_CR_TRAILER,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,
	URIBL_BLOCKED,USER_AGENT_GIT,USER_IN_DEF_DKIM_WL autolearn=ham
	autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id A1D75C433DB
	for <kvm@archiver.kernel.org>; Wed, 27 Jan 2021 16:17:54 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 579B4207C5
	for <kvm@archiver.kernel.org>; Wed, 27 Jan 2021 16:17:54 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S237039AbhA0QRi (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Wed, 27 Jan 2021 11:17:38 -0500
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:39284 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S235122AbhA0QQQ (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 27 Jan 2021 11:16:16 -0500
Received: from mail-yb1-xb4a.google.com (mail-yb1-xb4a.google.com
 [IPv6:2607:f8b0:4864:20::b4a])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id C3C17C06178C
        for <kvm@vger.kernel.org>; Wed, 27 Jan 2021 08:15:28 -0800 (PST)
Received: by mail-yb1-xb4a.google.com with SMTP id f127so2747866ybf.12
        for <kvm@vger.kernel.org>; Wed, 27 Jan 2021 08:15:28 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=sender:date:message-id:mime-version:subject:from:to:cc;
        bh=9Xv60zVJdPCczqkiRxegMesI9/uXHmAEZHHrmplL1fM=;
        b=cVjd1wyoIvpXTMR4bPebeDTtMe139pQg6Wa7VaGTxksODku3ExYKVjBYZ6K0bOKjzI
         bvqP6vAWovpeMRFmcg+7WffIPRoHkZKhTNX+c8fQfIcYjuLInGCZkojObUExOqjK/wJ1
         VMG1DUU0CYg28ug47YripMY+WUH5knRtVZfKW3/oIhNtL3AD0+Iv2gtrPxQvBMoFsfUq
         xuaooUZCrVsbefjPisTntTed6/5heZKc0JX/iEuJOvh9rK8QCUIPslHTGkRZwwLARad0
         OI0oS3+VxNZXD4dajHNoYAlhPZaIYcE0AEVBvoVtxEUXYV2gsfqofKmfNIlG0JEkcvod
         LuAw==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:sender:date:message-id:mime-version:subject:from
         :to:cc;
        bh=9Xv60zVJdPCczqkiRxegMesI9/uXHmAEZHHrmplL1fM=;
        b=pg3uDhPwhrrUGOBracv4VOlEi7hW1Z1BcMAtN0Ctm1nx2Khh4RAZ1Sh1HlgIqGIcNM
         tL1yJjDNBoPrRjm5K8YDRUupBoFmAIyIXxUH0D8UNaVQ04li8gxVApdulIbuY4Agj7CG
         tcqcyjzR8aG2wpnoWsCTAoNsaML8K7QI+9gGS9ZzYN3KtjP2A2FTL7QQIR3OWkjGJngG
         qTTw8IgwpA6q59L4N7l60XxNhjs1Zb189J1vMoU6bScJbuJ5wpmwFR3MhBaD7GhXaKfp
         m17+V2v/cRhcxVikn9IMeFR+dGJVofzB7/DKjZDcE4ejir1a282xWhJBSsSnQnIl+34C
         ueRg==
X-Gm-Message-State: AOAM532y0BPhuGk7Y+wDgfVjzsmntBSs8ehKuVn2UpwV+ETLo1X5QFaD
        ccdvLFf+aeVGakR7oE1d7N/5bbr4SVn7qFsNZ8U0HHfHucfGd4DGBESLE/M9TioTpjeSHil+mPr
        LsqDqzmwo7736vXUJC8SYZlEm6sGEIP+AwmNmg3HUouwGp9QlpJqAY7XXgw==
X-Google-Smtp-Source: 
 ABdhPJxOVxm2ehXpuCNpDGvZJ1wvSjsZNmmaqdqSiL7GiFVkCM8pySxbBDfTAkaDvqqyjKZCrZsktPlhq8o=
Sender: "pgonda via sendgmr" <pgonda@pgonda1.kir.corp.google.com>
X-Received: from pgonda1.kir.corp.google.com
 ([2620:0:1008:11:f693:9fff:fef4:e3a2])
 (user=pgonda job=sendgmr) by 2002:a25:f20b:: with SMTP id
 i11mr17672537ybe.273.1611764127400;
 Wed, 27 Jan 2021 08:15:27 -0800 (PST)
Date: Wed, 27 Jan 2021 08:15:24 -0800
Message-Id: <20210127161524.2832400-1-pgonda@google.com>
Mime-Version: 1.0
X-Mailer: git-send-email 2.30.0.280.ga3ce27912f-goog
Subject: [PATCH V2] Fix unsynchronized access to sev members through
 svm_register_enc_region
From: Peter Gonda <pgonda@google.com>
To: kvm@vger.kernel.org
Cc: Peter Gonda <pgonda@google.com>,
        Thomas Gleixner <tglx@linutronix.de>,
        Ingo Molnar <mingo@redhat.com>,
        "H. Peter Anvin" <hpa@zytor.com>,
        Paolo Bonzini <pbonzini@redhat.com>,
        Joerg Roedel <joro@8bytes.org>,
        Tom Lendacky <thomas.lendacky@amd.com>,
        Brijesh Singh <brijesh.singh@amd.com>,
        Sean Christopherson <seanjc@google.com>, x86@kernel.org,
        stable@vger.kernel.org, linux-kernel@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Grab kvm->lock before pinning memory when registering an encrypted
region; sev_pin_memory() relies on kvm->lock being held to ensure
correctness when checking and updating the number of pinned pages.

Add a lockdep assertion to help prevent future regressions.

Cc: Thomas Gleixner <tglx@linutronix.de>
Cc: Ingo Molnar <mingo@redhat.com>
Cc: "H. Peter Anvin" <hpa@zytor.com>
Cc: Paolo Bonzini <pbonzini@redhat.com>
Cc: Joerg Roedel <joro@8bytes.org>
Cc: Tom Lendacky <thomas.lendacky@amd.com>
Cc: Brijesh Singh <brijesh.singh@amd.com>
Cc: Sean Christopherson <seanjc@google.com>
Cc: x86@kernel.org
Cc: kvm@vger.kernel.org
Cc: stable@vger.kernel.org
Cc: linux-kernel@vger.kernel.org
Fixes: 1e80fdc09d12 ("KVM: SVM: Pin guest memory when SEV is active")
Signed-off-by: Peter Gonda <pgonda@google.com>

V2
 - Fix up patch description
 - Correct file paths svm.c -> sev.c
 - Add unlock of kvm->lock on sev_pin_memory error

V1
 - https://lore.kernel.org/kvm/20210126185431.1824530-1-pgonda@google.com/
---
 arch/x86/kvm/svm/sev.c | 17 ++++++++++-------
 1 file changed, 10 insertions(+), 7 deletions(-)

```
#### [PATCH v2] KVM: x86/mmu: consider the hva in mmu_notifier retry
##### From: David Stevens <stevensd@chromium.org>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: David Stevens <stevensd@chromium.org>
X-Patchwork-Id: 12048857
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-19.0 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_CR_TRAILER,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,
	URIBL_BLOCKED,USER_AGENT_GIT autolearn=unavailable autolearn_force=no
	version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id B5C8FC433E0
	for <kvm@archiver.kernel.org>; Wed, 27 Jan 2021 04:26:29 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 6985D20715
	for <kvm@archiver.kernel.org>; Wed, 27 Jan 2021 04:26:29 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S238591AbhA0E0S (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 26 Jan 2021 23:26:18 -0500
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:35920 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S232204AbhA0C50 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 26 Jan 2021 21:57:26 -0500
Received: from mail-pj1-x1033.google.com (mail-pj1-x1033.google.com
 [IPv6:2607:f8b0:4864:20::1033])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id BD456C061220
        for <kvm@vger.kernel.org>; Tue, 26 Jan 2021 18:45:49 -0800 (PST)
Received: by mail-pj1-x1033.google.com with SMTP id e9so429419pjj.0
        for <kvm@vger.kernel.org>; Tue, 26 Jan 2021 18:45:49 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=chromium.org; s=google;
        h=from:to:cc:subject:date:message-id:mime-version
         :content-transfer-encoding;
        bh=7PtWXNzHrzTp7A9th7APDIEImQRlLS2mGOWSoaKCv+4=;
        b=BrtxP2Kw4oAJZWLYhPtp+ptr4ogWuI50wfy8gQE2Ga0c07iSWeUli+TqOMp7KQ3DNM
         HzFzbmh40furMmKuniJgnZFQAs0PI5WDjP97KQMQo/UxgicGFtik8YyomHk4XHAuhukH
         Mlnh6Fo1TdiWgV9bWfXtrj4tb7ZZtvJHcwnD0=
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:mime-version
         :content-transfer-encoding;
        bh=7PtWXNzHrzTp7A9th7APDIEImQRlLS2mGOWSoaKCv+4=;
        b=tC5xkXdtuk3/67FzsVf33v1G5DJTZEYzatpEoSxuQaSjPtsnRMkMv++OW49LihwW2U
         RQpSr8YdCQ/kkcEDqoNLct/IWxyCfJMj/jBISmELJH1BqkOPowdNWuDrupMkHe3XW0fh
         4UKZN6U5i77GNSq4VqIPA4eo3ssGHbE8kr1D4oPaHx7qoP/1O0oR2+W3e8stUWvY6pci
         KGPtKpeOVojW7f7BtpR/pm4iSnLGYUrO95gIyzGwDfgjCCgEUtywVp8J5gnt5WiKSdwf
         oKnVZB9xDC2ROElDsiedh6LFRk2iYVYBKa17vvOA0jmkb3rgzN/lf9dH4Lyzn6/FVs5q
         cRQQ==
X-Gm-Message-State: AOAM533SuYHuPe2e/v21vZGisd+vJ8xRdBhZ8WuUmRI5m4woV9f6fp/K
        xRkGTLZMmKbE7YbIQ4peqshfIg==
X-Google-Smtp-Source: 
 ABdhPJx9soZ2g5SyR6Sp+xlR7Exg7c0f4vDMem4XLIp37iD5OQJdbs3wxxqnvGnGT0/mr+DipLiGCg==
X-Received: by 2002:a17:902:6843:b029:e0:52c:ad88 with SMTP id
 f3-20020a1709026843b02900e0052cad88mr9197016pln.72.1611715549193;
        Tue, 26 Jan 2021 18:45:49 -0800 (PST)
Received: from localhost ([2401:fa00:8f:203:55b7:86cc:655d:9dcb])
        by smtp.gmail.com with ESMTPSA id
 w66sm391620pfd.48.2021.01.26.18.45.44
        (version=TLS1_3 cipher=TLS_AES_128_GCM_SHA256 bits=128/128);
        Tue, 26 Jan 2021 18:45:48 -0800 (PST)
From: David Stevens <stevensd@chromium.org>
X-Google-Original-From: David Stevens <stevensd@google.com>
To: Sean Christopherson <seanjc@google.com>
Cc: Paolo Bonzini <pbonzini@redhat.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org, Marc Zyngier <maz@kernel.org>,
        James Morse <james.morse@arm.com>,
        Julien Thierry <julien.thierry.kdev@gmail.com>,
        Suzuki K Poulose <suzuki.poulose@arm.com>,
        linux-arm-kernel@lists.infradead.org, kvmarm@lists.cs.columbia.edu,
        Huacai Chen <chenhuacai@kernel.org>,
        Aleksandar Markovic <aleksandar.qemu.devel@gmail.com>,
        linux-mips@vger.kernel.org, Paul Mackerras <paulus@ozlabs.org>,
        kvm-ppc@vger.kernel.org,
        Christian Borntraeger <borntraeger@de.ibm.com>,
        Janosch Frank <frankja@linux.ibm.com>,
        David Hildenbrand <david@redhat.com>,
        Cornelia Huck <cohuck@redhat.com>,
        Claudio Imbrenda <imbrenda@linux.ibm.com>,
        David Stevens <stevensd@chromium.org>
Subject: [PATCH v2] KVM: x86/mmu: consider the hva in mmu_notifier retry
Date: Wed, 27 Jan 2021 11:45:04 +0900
Message-Id: <20210127024504.613844-1-stevensd@google.com>
X-Mailer: git-send-email 2.30.0.280.ga3ce27912f-goog
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: David Stevens <stevensd@chromium.org>

Track the range being invalidated by mmu_notifier and skip page fault
retries if the fault address is not affected by the in-progress
invalidation. Handle concurrent invalidations by finding the minimal
range which includes all ranges being invalidated. Although the combined
range may include unrelated addresses and cannot be shrunk as individual
invalidation operations complete, it is unlikely the marginal gains of
proper range tracking are worth the additional complexity.

The primary benefit of this change is the reduction in the likelihood of
extreme latency when handing a page fault due to another thread having
been preempted while modifying host virtual addresses.

Signed-off-by: David Stevens <stevensd@chromium.org>
---
v1 -> v2:
 - improve handling of concurrent invalidation requests by unioning
   ranges, instead of just giving up and using [0, ULONG_MAX).
 - add lockdep check
 - code comments and formatting

 arch/powerpc/kvm/book3s_64_mmu_hv.c    |  2 +-
 arch/powerpc/kvm/book3s_64_mmu_radix.c |  2 +-
 arch/x86/kvm/mmu/mmu.c                 | 16 ++++++++------
 arch/x86/kvm/mmu/paging_tmpl.h         |  7 ++++---
 include/linux/kvm_host.h               | 27 +++++++++++++++++++++++-
 virt/kvm/kvm_main.c                    | 29 ++++++++++++++++++++++----
 6 files changed, 67 insertions(+), 16 deletions(-)

```
