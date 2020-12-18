#### [kvm-unit-tests PATCH 1/1] arm: pmu: Don't read PMCR if PMU is not present
##### From: Alexandru Elisei <alexandru.elisei@arm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Alexandru Elisei <alexandru.elisei@arm.com>
X-Patchwork-Id: 11979669
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.7 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED,USER_AGENT_GIT
	autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 75394C2BB48
	for <kvm@archiver.kernel.org>; Thu, 17 Dec 2020 12:02:01 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 2F36A2395C
	for <kvm@archiver.kernel.org>; Thu, 17 Dec 2020 12:02:01 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1725950AbgLQMB5 (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Thu, 17 Dec 2020 07:01:57 -0500
Received: from foss.arm.com ([217.140.110.172]:60200 "EHLO foss.arm.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726155AbgLQMBz (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 17 Dec 2020 07:01:55 -0500
Received: from usa-sjc-imap-foss1.foss.arm.com (unknown [10.121.207.14])
        by usa-sjc-mx-foss1.foss.arm.com (Postfix) with ESMTP id 70D84101E;
        Thu, 17 Dec 2020 04:01:09 -0800 (PST)
Received: from monolith.localdoman (unknown [172.31.20.19])
        by usa-sjc-imap-foss1.foss.arm.com (Postfix) with ESMTPSA id
 D539F3F66B;
        Thu, 17 Dec 2020 04:01:08 -0800 (PST)
From: Alexandru Elisei <alexandru.elisei@arm.com>
To: drjones@redhat.com, kvm@vger.kernel.org,
        kvmarm@lists.cs.columbia.edu
Subject: [kvm-unit-tests PATCH 1/1] arm: pmu: Don't read PMCR if PMU is not
 present
Date: Thu, 17 Dec 2020 12:00:57 +0000
Message-Id: <20201217120057.88562-2-alexandru.elisei@arm.com>
X-Mailer: git-send-email 2.29.2
In-Reply-To: <20201217120057.88562-1-alexandru.elisei@arm.com>
References: <20201217120057.88562-1-alexandru.elisei@arm.com>
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

For arm and arm64, the PMU is an optional part of the architecture.
According to ARM DDI 0487F.b, page D13-3683, accessing PMCR_EL0 when the
PMU is not present generates an undefined exception (one would assume that
this is also true for arm).

The pmu_probe() function reads the register before checking that a PMU is
present, so defer accessing PMCR_EL0 until after we know that it is safe.

This hasn't been a problem so far because there's no hardware in the wild
without a PMU and KVM, contrary to the architecture, has treated the PMU
registers as RAZ/WI if the VCPU doesn't have the PMU feature. However,
that's about to change as KVM will start treating the registers as
undefined when the guest doesn't have a PMU.

Signed-off-by: Alexandru Elisei <alexandru.elisei@arm.com>
---
 arm/pmu.c | 3 ++-
 1 file changed, 2 insertions(+), 1 deletion(-)

```
#### [kvm-unit-tests PATCH v2 01/12] lib: arm/arm64: gicv3: Add missing barrier when sending IPIs
##### From: Alexandru Elisei <alexandru.elisei@arm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Alexandru Elisei <alexandru.elisei@arm.com>
X-Patchwork-Id: 11979809
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.7 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED,USER_AGENT_GIT
	autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id BC72AC2BB48
	for <kvm@archiver.kernel.org>; Thu, 17 Dec 2020 14:15:13 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 5FE9C2360D
	for <kvm@archiver.kernel.org>; Thu, 17 Dec 2020 14:15:13 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728096AbgLQOO4 (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Thu, 17 Dec 2020 09:14:56 -0500
Received: from foss.arm.com ([217.140.110.172]:38398 "EHLO foss.arm.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726998AbgLQOO4 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 17 Dec 2020 09:14:56 -0500
Received: from usa-sjc-imap-foss1.foss.arm.com (unknown [10.121.207.14])
        by usa-sjc-mx-foss1.foss.arm.com (Postfix) with ESMTP id 6E4BD101E;
        Thu, 17 Dec 2020 06:14:10 -0800 (PST)
Received: from monolith.localdoman (unknown [172.31.20.19])
        by usa-sjc-imap-foss1.foss.arm.com (Postfix) with ESMTPSA id
 801553F66B;
        Thu, 17 Dec 2020 06:14:09 -0800 (PST)
From: Alexandru Elisei <alexandru.elisei@arm.com>
To: drjones@redhat.com, kvm@vger.kernel.org,
        kvmarm@lists.cs.columbia.edu
Cc: andre.przywara@arm.com, eric.auger@redhat.com, yuzenghui@huawei.com
Subject: [kvm-unit-tests PATCH v2 01/12] lib: arm/arm64: gicv3: Add missing
 barrier when sending IPIs
Date: Thu, 17 Dec 2020 14:13:49 +0000
Message-Id: <20201217141400.106137-2-alexandru.elisei@arm.com>
X-Mailer: git-send-email 2.29.2
In-Reply-To: <20201217141400.106137-1-alexandru.elisei@arm.com>
References: <20201217141400.106137-1-alexandru.elisei@arm.com>
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

One common usage for IPIs is for one CPU to write to a shared memory
location, send the IPI to kick another CPU, and the receiver to read from
the same location. Proper synchronization is needed to make sure that the
IPI receiver reads the most recent value and not stale data (for example,
the write from the sender CPU might still be in a store buffer).

For GICv3, IPIs are generated with a write to the ICC_SGI1R_EL1 register.
To make sure the memory stores are observable by other CPUs, we need a
wmb() barrier (DSB ST), which waits for stores to complete.

From the definition of DSB from ARM DDI 0487F.b, page B2-139:

"In addition, no instruction that appears in program order after the DSB
instruction can alter any state of the system or perform any part of its
functionality until the DSB completes other than:

- Being fetched from memory and decoded.
- Reading the general-purpose, SIMD and floating-point, Special-purpose, or
System registers that are directly or indirectly read without causing
side-effects."

Similar definition for armv7 (ARM DDI 0406C.d, page A3-150).

The DSB instruction is enough to prevent reordering of the GIC register
write which comes in program order after the memory access.

This also matches what the Linux GICv3 irqchip driver does (commit
21ec30c0ef52 ("irqchip/gic-v3: Use wmb() instead of smb_wmb() in
gic_raise_softirq()")).

Reviewed-by: Eric Auger <eric.auger@redhat.com>
Signed-off-by: Alexandru Elisei <alexandru.elisei@arm.com>
---
 lib/arm/gic-v3.c | 6 ++++++
 arm/gic.c        | 5 +++++
 2 files changed, 11 insertions(+)

```
#### [PATCH] KVM: mmu: Fix SPTE encoding of MMIO generation upper half
##### From: "Maciej S. Szmigiero" <mail@maciej.szmigiero.name>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: "Maciej S. Szmigiero" <mail@maciej.szmigiero.name>
X-Patchwork-Id: 11979799
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.8 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT autolearn=ham
	autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 61A87C4361B
	for <kvm@archiver.kernel.org>; Thu, 17 Dec 2020 13:47:30 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 1E98E238EF
	for <kvm@archiver.kernel.org>; Thu, 17 Dec 2020 13:47:30 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728406AbgLQNrN (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Thu, 17 Dec 2020 08:47:13 -0500
Received: from vps-vb.mhejs.net ([37.28.154.113]:36594 "EHLO vps-vb.mhejs.net"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1727437AbgLQNrN (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 17 Dec 2020 08:47:13 -0500
Received: from MUA
        by vps-vb.mhejs.net with esmtps
 (TLS1.2:ECDHE-RSA-AES256-GCM-SHA384:256)
        (Exim 4.93.0.4)
        (envelope-from <mail@maciej.szmigiero.name>)
        id 1kptbo-0007Nj-Md; Thu, 17 Dec 2020 14:46:21 +0100
From: "Maciej S. Szmigiero" <mail@maciej.szmigiero.name>
To: stable@vger.kernel.org
Cc: Paolo Bonzini <pbonzini@redhat.com>,
        Sean Christopherson <seanjc@google.com>,
        Joerg Roedel <joro@8bytes.org>,
        Jim Mattson <jmattson@google.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Jonathan Corbet <corbet@lwn.net>, kvm@vger.kernel.org
Subject: [PATCH] KVM: mmu: Fix SPTE encoding of MMIO generation upper half
Date: Thu, 17 Dec 2020 14:46:13 +0100
Message-Id: 
 <8bf9d5caf338d705744764c60256ace1d3f1d252.1608168540.git.maciej.szmigiero@oracle.com>
X-Mailer: git-send-email 2.29.2
In-Reply-To: <1607955408254166@kroah.com>
References: <1607955408254166@kroah.com>
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: "Maciej S. Szmigiero" <maciej.szmigiero@oracle.com>

Commit cae7ed3c2cb0 ("KVM: x86: Refactor the MMIO SPTE generation handling")
cleaned up the computation of MMIO generation SPTE masks, however it
introduced a bug how the upper part was encoded:
SPTE bits 52-61 were supposed to contain bits 10-19 of the current
generation number, however a missing shift encoded bits 1-10 there instead
(mostly duplicating the lower part of the encoded generation number that
then consisted of bits 1-9).

In the meantime, the upper part was shrunk by one bit and moved by
subsequent commits to become an upper half of the encoded generation number
(bits 9-17 of bits 0-17 encoded in a SPTE).

In addition to the above, commit 56871d444bc4 ("KVM: x86: fix overlap between SPTE_MMIO_MASK and generation")
has changed the SPTE bit range assigned to encode the generation number and
the total number of bits encoded but did not update them in the comment
attached to their defines, nor in the KVM MMU doc.
Let's do it here, too, since it is too trivial thing to warrant a separate
commit.

This is a backport of the upstream commit for 5.4.x stable series, which
has KVM docs still in a raw text format and the x86 KVM MMU isn't yet split
into separate files under "mmu" directory.
Other than that, it's a straightforward port.

Fixes: cae7ed3c2cb0 ("KVM: x86: Refactor the MMIO SPTE generation handling")
Signed-off-by: Maciej S. Szmigiero <maciej.szmigiero@oracle.com>
[Reorganize macros so that everything is computed from the bit ranges. - Paolo]
Signed-off-by: Paolo Bonzini <pbonzini@redhat.com>
(cherry picked from commit 34c0f6f2695a2db81e09a3ab7bdb2853f45d4d3d)
Cc: stable@vger.kernel.org # 5.4.x
Acked-by: Paolo Bonzini <pbonzini@redhat.com>
---
 Documentation/virt/kvm/mmu.txt |  2 +-
 arch/x86/kvm/mmu.c             | 29 ++++++++++++++++++++---------
 2 files changed, 21 insertions(+), 10 deletions(-)

```
#### [PATCH] KVM: mmu: Fix SPTE encoding of MMIO generation upper half
##### From: "Maciej S. Szmigiero" <mail@maciej.szmigiero.name>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: "Maciej S. Szmigiero" <mail@maciej.szmigiero.name>
X-Patchwork-Id: 11979801
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.8 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT autolearn=ham
	autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 56E55C4361B
	for <kvm@archiver.kernel.org>; Thu, 17 Dec 2020 13:47:51 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 1CD8F238EF
	for <kvm@archiver.kernel.org>; Thu, 17 Dec 2020 13:47:51 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727529AbgLQNru (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Thu, 17 Dec 2020 08:47:50 -0500
Received: from vps-vb.mhejs.net ([37.28.154.113]:36802 "EHLO vps-vb.mhejs.net"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1727656AbgLQNrt (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 17 Dec 2020 08:47:49 -0500
Received: from MUA
        by vps-vb.mhejs.net with esmtps
 (TLS1.2:ECDHE-RSA-AES256-GCM-SHA384:256)
        (Exim 4.93.0.4)
        (envelope-from <mail@maciej.szmigiero.name>)
        id 1kptcO-0007O0-36; Thu, 17 Dec 2020 14:46:56 +0100
From: "Maciej S. Szmigiero" <mail@maciej.szmigiero.name>
To: stable@vger.kernel.org
Cc: Paolo Bonzini <pbonzini@redhat.com>,
        Sean Christopherson <seanjc@google.com>,
        Joerg Roedel <joro@8bytes.org>,
        Jim Mattson <jmattson@google.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Jonathan Corbet <corbet@lwn.net>, kvm@vger.kernel.org
Subject: [PATCH] KVM: mmu: Fix SPTE encoding of MMIO generation upper half
Date: Thu, 17 Dec 2020 14:46:49 +0100
Message-Id: 
 <f5cb26d9a45cbaf617928d1314e7c0efea597e05.1608169775.git.maciej.szmigiero@oracle.com>
X-Mailer: git-send-email 2.29.2
In-Reply-To: <1607955407131211@kroah.com>
References: <1607955407131211@kroah.com>
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: "Maciej S. Szmigiero" <maciej.szmigiero@oracle.com>

Commit cae7ed3c2cb0 ("KVM: x86: Refactor the MMIO SPTE generation handling")
cleaned up the computation of MMIO generation SPTE masks, however it
introduced a bug how the upper part was encoded:
SPTE bits 52-61 were supposed to contain bits 10-19 of the current
generation number, however a missing shift encoded bits 1-10 there instead
(mostly duplicating the lower part of the encoded generation number that
then consisted of bits 1-9).

In the meantime, the upper part was shrunk by one bit and moved by
subsequent commits to become an upper half of the encoded generation number
(bits 9-17 of bits 0-17 encoded in a SPTE).

In addition to the above, commit 56871d444bc4 ("KVM: x86: fix overlap between SPTE_MMIO_MASK and generation")
has changed the SPTE bit range assigned to encode the generation number and
the total number of bits encoded but did not update them in the comment
attached to their defines, nor in the KVM MMU doc.
Let's do it here, too, since it is too trivial thing to warrant a separate
commit.

This is a backport of the upstream commit for 5.9.x stable series, in which
the x86 KVM MMU SPTE handling isn't yet split out to spte.{c,h} files.
Other than that, it's a straightforward port.

Fixes: cae7ed3c2cb0 ("KVM: x86: Refactor the MMIO SPTE generation handling")
Signed-off-by: Maciej S. Szmigiero <maciej.szmigiero@oracle.com>
[Reorganize macros so that everything is computed from the bit ranges. - Paolo]
Signed-off-by: Paolo Bonzini <pbonzini@redhat.com>
(cherry picked from commit 34c0f6f2695a2db81e09a3ab7bdb2853f45d4d3d)
Cc: stable@vger.kernel.org # 5.9.x
Acked-by: Paolo Bonzini <pbonzini@redhat.com>
---
 Documentation/virt/kvm/mmu.rst |  2 +-
 arch/x86/kvm/mmu/mmu.c         | 29 ++++++++++++++++++++---------
 2 files changed, 21 insertions(+), 10 deletions(-)

```
#### [PATCH] KVM/nVMX: Use __vmx_vcpu_run in nested_vmx_check_vmentry_hw
##### From: Uros Bizjak <ubizjak@gmail.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Uros Bizjak <ubizjak@gmail.com>
X-Patchwork-Id: 11980635
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-15.7 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,DKIM_VALID_AU,FREEMAIL_FORGED_FROMDOMAIN,FREEMAIL_FROM,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED,USER_AGENT_GIT
	autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id B5725C4361B
	for <kvm@archiver.kernel.org>; Thu, 17 Dec 2020 18:45:57 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 808FD238EF
	for <kvm@archiver.kernel.org>; Thu, 17 Dec 2020 18:45:57 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729995AbgLQSpj (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Thu, 17 Dec 2020 13:45:39 -0500
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:47706 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1728182AbgLQSpi (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 17 Dec 2020 13:45:38 -0500
Received: from mail-ed1-x529.google.com (mail-ed1-x529.google.com
 [IPv6:2a00:1450:4864:20::529])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 0A7C3C0617A7;
        Thu, 17 Dec 2020 10:44:58 -0800 (PST)
Received: by mail-ed1-x529.google.com with SMTP id cm17so29727334edb.4;
        Thu, 17 Dec 2020 10:44:57 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=from:to:cc:subject:date:message-id:mime-version
         :content-transfer-encoding;
        bh=a9fRIqvzJymHT2HZ/FU26JTBjEDUTwr5tEPTmXqVJpM=;
        b=MwjMOllUK0/NSsp+i51FRUdBQl1xYyWF180W81NE+Ll3OUdEyyhvKWcvoTFQT7idAL
         aAhOtYgN+59eBv7CDVMuRuYTkkl4OiJBQZEK8iTdp3SLX1oTgW6V+1rurF+BI4+i9CWp
         JKy3wYAyIYCrjOIWrtwK29weGiMXKfmI3hYqnaxwnoYYNXA0vtix3i1sRJ1jGkOndvdm
         +ALJH3T6vclBHkH9rei3Wo++kFHz2AmpMKxGDcGrO+gUNfTQ14oXBuyShBX67UKDzhVl
         GkbD8zzPWTBnsdtpZcIRa/hMyDCIrvMsajgmfG4PBP7yBCDvTijo//X9FduCgzxIfSSa
         xw/w==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:mime-version
         :content-transfer-encoding;
        bh=a9fRIqvzJymHT2HZ/FU26JTBjEDUTwr5tEPTmXqVJpM=;
        b=PDtTCPjHi7s408g4TXSMtqfGQbbQBqKUymSJbc1RVMfAqIsGq8Fd9QnwS7AIRUwqn0
         n3FGMMVgVwrDH2RIiZ/+yn/kqLfeF9qnW1sEIHLwoMiBGC4b8I6h5M9Rwwy+hRCG/uLW
         3CF3qHR6v4jT1ibaKCbZqWeTXeeF+YCu0N2iLQ5l+cGCTZ6cMOBx0JI1J3ZesJTH5Ij4
         t3TQxpn3mDSlihJxwh2H122S/WCz4qBAWy9FXoPEqKOMyx1AFwhu2DqE90K0U1xLNZzi
         wHMAU1YojweGplh+a6WntxbqJKkT2CDMIlIPrEeHX0cLGkcHPM7i4nU1q3kQTE10Ply2
         uWFQ==
X-Gm-Message-State: AOAM533KXzM29Tb6Axl79zSeKoGT1F70G5bEfPPnG/evhsLdvSXjy1Fd
        hxLv6HYiusApI+JH6jn3o3Z9uZy9WznakA==
X-Google-Smtp-Source: 
 ABdhPJxvQPAIj76o5mOi9AIT9d+pRI5J4Gg8nLlRTQcN/prDDqJGBUHEHS85KXt2kfGvCtmjpFt2YQ==
X-Received: by 2002:a50:fe8d:: with SMTP id d13mr738395edt.132.1608230696344;
        Thu, 17 Dec 2020 10:44:56 -0800 (PST)
Received: from localhost.localdomain (93-103-18-160.static.t-2.net.
 [93.103.18.160])
        by smtp.gmail.com with ESMTPSA id
 k3sm10849713eds.87.2020.12.17.10.44.55
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Thu, 17 Dec 2020 10:44:55 -0800 (PST)
From: Uros Bizjak <ubizjak@gmail.com>
To: kvm@vger.kernel.org, linux-kernel@vger.kernel.org
Cc: Uros Bizjak <ubizjak@gmail.com>,
        Paolo Bonzini <pbonzini@redhat.com>,
        Sean Christopherson <seanjc@google.com>
Subject: [PATCH] KVM/nVMX: Use __vmx_vcpu_run in nested_vmx_check_vmentry_hw
Date: Thu, 17 Dec 2020 19:44:51 +0100
Message-Id: <20201217184451.201311-1-ubizjak@gmail.com>
X-Mailer: git-send-email 2.26.2
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Replace inline assembly in nested_vmx_check_vmentry_hw
with a call to __vmx_vcpu_run.  The function is not
performance critical, so (double) GPR save/restore
in __vmx_vcpu_run can be tolerated, as far as performance
effects are concerned.

v2: Mark vmx_vmenter SYM_FUNC_START_LOCAL.

Cc: Paolo Bonzini <pbonzini@redhat.com>
Cc: Sean Christopherson <seanjc@google.com>
Reviewed-and-tested-by: Sean Christopherson <seanjc@google.com>
Signed-off-by: Uros Bizjak <ubizjak@gmail.com>
---
 arch/x86/kvm/vmx/nested.c  | 32 +++-----------------------------
 arch/x86/kvm/vmx/vmenter.S |  2 +-
 arch/x86/kvm/vmx/vmx.c     |  2 --
 arch/x86/kvm/vmx/vmx.h     |  1 +
 4 files changed, 5 insertions(+), 32 deletions(-)

```
#### linux-next: manual merge of the kvm tree with Linus' tree
##### From: Stephen Rothwell <sfr@canb.auug.org.au>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Stephen Rothwell <sfr@canb.auug.org.au>
X-Patchwork-Id: 11979025
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-10.8 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS autolearn=unavailable
	autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 5C3A0C1B0D8
	for <kvm@archiver.kernel.org>; Thu, 17 Dec 2020 02:57:12 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 2084023406
	for <kvm@archiver.kernel.org>; Thu, 17 Dec 2020 02:57:12 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727620AbgLQC44 (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Wed, 16 Dec 2020 21:56:56 -0500
Received: from bilbo.ozlabs.org ([203.11.71.1]:59597 "EHLO ozlabs.org"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1727115AbgLQC44 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 16 Dec 2020 21:56:56 -0500
Received: from authenticated.ozlabs.org (localhost [127.0.0.1])
        (using TLSv1.3 with cipher TLS_AES_256_GCM_SHA384 (256/256 bits)
         key-exchange ECDHE (P-256) server-signature RSA-PSS (4096 bits)
 server-digest SHA256)
        (No client certificate requested)
        by mail.ozlabs.org (Postfix) with ESMTPSA id 4CxGpg5JCjz9sRR;
        Thu, 17 Dec 2020 13:56:11 +1100 (AEDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple; d=canb.auug.org.au;
        s=201702; t=1608173773;
        bh=0BUN17/xDSq7+CWgU8wi0dZDg7QZRtEzB1WlEheKggE=;
        h=Date:From:To:Cc:Subject:From;
        b=TpWRTGPMExPzxK4g6VJFBkIPYYtyYT4sVp8ZeelQHmrO+qbYC7mvlB2fWDyd++g7k
         NQWfs75u66yPdiG8dTWmlqfSj0vmQt0SYH6dNZZXcUgiRjf03597lrr6HmScTzLG6b
         jdF8cQEPnVlA4XKrndHBSu1ozFroi5JlXplqHyM28V6SS4LsYV/W5s1NBqgiEGjpk/
         knO6reWL99Zo6oC0EKRMc8QeZim3R0VLRrYw9YmvBB4jv2B2N+m3K3glziFJ/P97wz
         P/+M5WCjpv5ZW072G9zJ8x4Yv9s/l88nKMONdppCsMxrgivTukK2WXByGn0RMXBZ3n
         9xmcNUdmuRO8g==
Date: Thu, 17 Dec 2020 13:56:09 +1100
From: Stephen Rothwell <sfr@canb.auug.org.au>
To: Paolo Bonzini <pbonzini@redhat.com>, KVM <kvm@vger.kernel.org>
Cc: Chen Zhou <chenzhou10@huawei.com>,
        Linux Kernel Mailing List <linux-kernel@vger.kernel.org>,
        Linux Next Mailing List <linux-next@vger.kernel.org>,
        Tom Lendacky <thomas.lendacky@amd.com>
Subject: linux-next: manual merge of the kvm tree with Linus' tree
Message-ID: <20201217135609.6543533c@canb.auug.org.au>
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Hi all,

Today's linux-next merge of the kvm tree got a conflict in:

  arch/x86/kvm/svm/svm.c

between commit:

  054409ab253d ("KVM: SVM: fix error return code in svm_create_vcpu()")

from Linus' tree and commit:

  add5e2f04541 ("KVM: SVM: Add support for the SEV-ES VMSA")

from the kvm tree.

I fixed it up (see below) and can carry the fix as necessary. This
is now fixed as far as linux-next is concerned, but any non trivial
conflicts should be mentioned to your upstream maintainer when your tree
is submitted for merging.  You may also want to consider cooperating
with the maintainer of the conflicting tree to minimise any particularly
complex conflicts.

```
#### [PATCH V3] kvm: check tlbs_dirty directly
##### From: Lai Jiangshan <jiangshanlai@gmail.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Lai Jiangshan <jiangshanlai@gmail.com>
X-Patchwork-Id: 11979919
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-15.7 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,DKIM_VALID_AU,FREEMAIL_FORGED_FROMDOMAIN,FREEMAIL_FROM,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT
	autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 162FDC2BB9A
	for <kvm@archiver.kernel.org>; Thu, 17 Dec 2020 14:41:42 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id D52932399C
	for <kvm@archiver.kernel.org>; Thu, 17 Dec 2020 14:41:41 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728431AbgLQOlZ (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Thu, 17 Dec 2020 09:41:25 -0500
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:38072 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726291AbgLQOlZ (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 17 Dec 2020 09:41:25 -0500
Received: from mail-pf1-x42e.google.com (mail-pf1-x42e.google.com
 [IPv6:2607:f8b0:4864:20::42e])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 513E1C061794;
        Thu, 17 Dec 2020 06:40:45 -0800 (PST)
Received: by mail-pf1-x42e.google.com with SMTP id w6so19185002pfu.1;
        Thu, 17 Dec 2020 06:40:45 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=from:to:cc:subject:date:message-id:in-reply-to:references
         :mime-version:content-transfer-encoding;
        bh=enLPOtX+RwuUEW41weEYdgVO7wJosn5W764QBKADpC0=;
        b=MIwIlFomCfpcfTP7hoYKE80dMrXthuwfQfIE41Eh9iO9XuLzVC0MHAVozM9FFECa4u
         4auSn9F6mNrNxMIow8KyfmaaUqNnMwtiJ920yky/TQomMa2FqHvTDSCDrBMBKlMXG5gk
         JsrjEq79Q0zxgvWEEH3w99F88LWoPr8/8A3UCCSaBvFhfE3NIBoU5sm7aSRlG6JbuRpr
         Do2E8DA14oXXi9EOclDV2pGwUg6m+RPSTg7zzZYx+Bti4MpgiqDH80cibISlp4Dybgs8
         mfWQZmMbFrv3yCD7xTNjUxBWuiQ/2p4egc0gxipwIPMiszEbN3gxHjL256OVu04uNZyA
         qSWA==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:in-reply-to
         :references:mime-version:content-transfer-encoding;
        bh=enLPOtX+RwuUEW41weEYdgVO7wJosn5W764QBKADpC0=;
        b=J7ZZYeLzzxGogyT83B1+y7a5S1ZSuKwXFEYDa1n7DS1caOBWPrXJM4SNFa9Tp8wZ7z
         TSm1dg8qIxJqxi383QYeUfK6y9c6oTpfHhWr4n+dkw+NmK9J6CSfcOJRGI710vIUg7vB
         ecgJaex1ONLI7zAXJ1GVKpO/9Ku9atmfgCO0D5qwoeyNk3RNeTxSgMDKkL18enbpHQ0H
         AVFmKg9eqAOPjk7VRYW3hi6lOrxlDiIBkXXVgTCzbea6RopADYRwV6bIFYANBEF6CCMv
         GBIdYoWxaN6Fx65+vqxhnafq6Ugy4FZ9RrNAkWIRf4let5jsX84Z291dOt2iJqTnHDST
         eVjw==
X-Gm-Message-State: AOAM532C7YFqSMLSpwcpxZ+iRVB8EziYRW1Q9Gj4Uwk5J12K7sBhowV0
        FUeHYIqwwVXjLLfYMdURYekDYo96leX8PA==
X-Google-Smtp-Source: 
 ABdhPJyHFpraaFLk+3QhMHDpQ4btopHivgWaat0v6SLM6H6sHi26qZvrt5X38vYkRmFQBca9pqKJcw==
X-Received: by 2002:a65:534d:: with SMTP id
 w13mr37761820pgr.107.1608216044599;
        Thu, 17 Dec 2020 06:40:44 -0800 (PST)
Received: from localhost ([47.251.4.198])
        by smtp.gmail.com with ESMTPSA id
 p16sm5294396pju.47.2020.12.17.06.40.43
        (version=TLS1_2 cipher=ECDHE-ECDSA-AES128-GCM-SHA256 bits=128/128);
        Thu, 17 Dec 2020 06:40:44 -0800 (PST)
From: Lai Jiangshan <jiangshanlai@gmail.com>
To: linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Cc: Paolo Bonzini <pbonzini@redhat.com>,
        Sean Christopherson <seanjc@google.com>,
        Lai Jiangshan <laijs@linux.alibaba.com>, stable@vger.kernel.org
Subject: [PATCH V3] kvm: check tlbs_dirty directly
Date: Thu, 17 Dec 2020 23:41:18 +0800
Message-Id: <20201217154118.16497-1-jiangshanlai@gmail.com>
X-Mailer: git-send-email 2.19.1.6.gb485710b
In-Reply-To: <X9kEAh7z1rmlmyhZ@google.com>
References: <X9kEAh7z1rmlmyhZ@google.com>
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Lai Jiangshan <laijs@linux.alibaba.com>

In kvm_mmu_notifier_invalidate_range_start(), tlbs_dirty is used as:
        need_tlb_flush |= kvm->tlbs_dirty;
with need_tlb_flush's type being int and tlbs_dirty's type being long.

It means that tlbs_dirty is always used as int and the higher 32 bits
is useless.  We need to check tlbs_dirty in a correct way and this
change checks it directly without propagating it to need_tlb_flush.

Note: it's _extremely_ unlikely this neglecting of higher 32 bits can
cause problems in practice.  It would require encountering tlbs_dirty
on a 4 billion count boundary, and KVM would need to be using shadow
paging or be running a nested guest.

Cc: stable@vger.kernel.org
Fixes: a4ee1ca4a36e ("KVM: MMU: delay flush all tlbs on sync_page path")
Signed-off-by: Lai Jiangshan <laijs@linux.alibaba.com>
---
Changed from V1:
        Update the patch and the changelog as Sean Christopherson suggested.

Changed from v2:
	don't change the type of need_tlb_flush

 virt/kvm/kvm_main.c | 3 +--
 1 file changed, 1 insertion(+), 2 deletions(-)

```
#### [PATCH v3 06/15] x86/paravirt: switch time pvops functions to use static_call()
##### From: Juergen Gross <jgross@suse.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: =?utf-8?b?SsO8cmdlbiBHcm/Dnw==?= <jgross@suse.com>
X-Patchwork-Id: 11979383
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-18.7 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,
	INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED,
	USER_AGENT_GIT autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id BC865C2BB48
	for <kvm@archiver.kernel.org>; Thu, 17 Dec 2020 09:34:24 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 6437D2389E
	for <kvm@archiver.kernel.org>; Thu, 17 Dec 2020 09:34:24 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727992AbgLQJeE (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Thu, 17 Dec 2020 04:34:04 -0500
Received: from mx2.suse.de ([195.135.220.15]:43658 "EHLO mx2.suse.de"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1727119AbgLQJdT (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 17 Dec 2020 04:33:19 -0500
X-Virus-Scanned: by amavisd-new at test-mx.suse.de
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=suse.com; s=susede1;
        t=1608197508;
 h=from:from:reply-to:date:date:message-id:message-id:to:to:cc:cc:
         mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding:
         in-reply-to:in-reply-to:references:references;
        bh=j6gxliSCsh3WKILmxj4RJn4SpdlW/0yI/QevTH0przg=;
        b=kwgvz+7bk8SUbt9TMo5E0AtpcQKuGkGIdhTz/B272guohLREgzNYP6Uy2FZyXZ1hNFXD4C
        ehDwVXEgZ1cNADdlNf25z7q0dWGCZYTw4BBwg1bvjOAkRFRxsHc5o2QdQvPxSnFF6jzzgz
        qLKKeB1GzE4cCsH8sAFFQPrx9N7v4qw=
Received: from relay2.suse.de (unknown [195.135.221.27])
        by mx2.suse.de (Postfix) with ESMTP id 0861FB718;
        Thu, 17 Dec 2020 09:31:48 +0000 (UTC)
From: Juergen Gross <jgross@suse.com>
To: xen-devel@lists.xenproject.org, x86@kernel.org,
        linux-kernel@vger.kernel.org, linux-hyperv@vger.kernel.org,
        virtualization@lists.linux-foundation.org, kvm@vger.kernel.org
Cc: Juergen Gross <jgross@suse.com>,
        Thomas Gleixner <tglx@linutronix.de>,
        Ingo Molnar <mingo@redhat.com>, Borislav Petkov <bp@alien8.de>,
        "H. Peter Anvin" <hpa@zytor.com>,
        "K. Y. Srinivasan" <kys@microsoft.com>,
        Haiyang Zhang <haiyangz@microsoft.com>,
        Stephen Hemminger <sthemmin@microsoft.com>,
        Wei Liu <wei.liu@kernel.org>, Deep Shah <sdeep@vmware.com>,
        "VMware, Inc." <pv-drivers@vmware.com>,
        Paolo Bonzini <pbonzini@redhat.com>,
        Sean Christopherson <seanjc@google.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>,
        Boris Ostrovsky <boris.ostrovsky@oracle.com>,
        Stefano Stabellini <sstabellini@kernel.org>,
        Daniel Lezcano <daniel.lezcano@linaro.org>,
        Peter Zijlstra <peterz@infradead.org>,
        Juri Lelli <juri.lelli@redhat.com>,
        Vincent Guittot <vincent.guittot@linaro.org>,
        Dietmar Eggemann <dietmar.eggemann@arm.com>,
        Steven Rostedt <rostedt@goodmis.org>,
        Ben Segall <bsegall@google.com>, Mel Gorman <mgorman@suse.de>,
        Daniel Bristot de Oliveira <bristot@redhat.com>
Subject: [PATCH v3 06/15] x86/paravirt: switch time pvops functions to use
 static_call()
Date: Thu, 17 Dec 2020 10:31:24 +0100
Message-Id: <20201217093133.1507-7-jgross@suse.com>
X-Mailer: git-send-email 2.26.2
In-Reply-To: <20201217093133.1507-1-jgross@suse.com>
References: <20201217093133.1507-1-jgross@suse.com>
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The time pvops functions are the only ones left which might be
used in 32-bit mode and which return a 64-bit value.

Switch them to use the static_call() mechanism instead of pvops, as
this allows quite some simplification of the pvops implementation.

Due to include hell this requires to split out the time interfaces
into a new header file.

Signed-off-by: Juergen Gross <jgross@suse.com>
---
 arch/x86/Kconfig                      |  1 +
 arch/x86/include/asm/mshyperv.h       | 11 --------
 arch/x86/include/asm/paravirt.h       | 14 ----------
 arch/x86/include/asm/paravirt_time.h  | 38 +++++++++++++++++++++++++++
 arch/x86/include/asm/paravirt_types.h |  6 -----
 arch/x86/kernel/cpu/vmware.c          |  5 ++--
 arch/x86/kernel/kvm.c                 |  3 ++-
 arch/x86/kernel/kvmclock.c            |  3 ++-
 arch/x86/kernel/paravirt.c            | 16 ++++++++---
 arch/x86/kernel/tsc.c                 |  3 ++-
 arch/x86/xen/time.c                   | 12 ++++-----
 drivers/clocksource/hyperv_timer.c    |  5 ++--
 drivers/xen/time.c                    |  3 ++-
 kernel/sched/sched.h                  |  1 +
 14 files changed, 71 insertions(+), 50 deletions(-)
 create mode 100644 arch/x86/include/asm/paravirt_time.h

```
