#### [PATCH 1/3] KVM: Add a stub for invpcid in the emulator table
##### From: Bandan Das <bsd@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Bandan Das <bsd@redhat.com>
X-Patchwork-Id: 12084185
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.3 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_CR_TRAILER,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS
	autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id BE800C433DB
	for <kvm@archiver.kernel.org>; Thu, 11 Feb 2021 21:25:18 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 8811364E42
	for <kvm@archiver.kernel.org>; Thu, 11 Feb 2021 21:25:18 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S229933AbhBKVZO (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Thu, 11 Feb 2021 16:25:14 -0500
Received: from us-smtp-delivery-124.mimecast.com ([216.205.24.124]:26456 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S229886AbhBKVZK (ORCPT
        <rfc822;kvm@vger.kernel.org>); Thu, 11 Feb 2021 16:25:10 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1613078624;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding:
         in-reply-to:in-reply-to:references:references;
        bh=el7j+rmZA3EiDQrnbTpaheKflbW47Lq347I0dXbFzvo=;
        b=DC/ncbTOqr3IwAzch22v9kE3+h6vnXqFJxMnbVF07N7DDADuWNrCCdLBNZr127o1kas4hZ
        quEmr/IZfUWiM6Lb+lPMh5bvLFWrocPnMNrdcQoZ/MSaKPs54Pd71fWGq2gA0a28fZhlz9
        djbOQF/JQt6ou9qOs5VvLyvfOL1L3sk=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-361-9Hx285pvPc6GFFye5jsYoA-1; Thu, 11 Feb 2021 16:23:41 -0500
X-MC-Unique: 9Hx285pvPc6GFFye5jsYoA-1
Received: from smtp.corp.redhat.com (int-mx02.intmail.prod.int.phx2.redhat.com
 [10.5.11.12])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id E77DB192D786;
        Thu, 11 Feb 2021 21:23:39 +0000 (UTC)
Received: from gigantic.usersys.redhat.com (helium.bos.redhat.com
 [10.18.17.132])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 7231D60C0F;
        Thu, 11 Feb 2021 21:23:39 +0000 (UTC)
From: Bandan Das <bsd@redhat.com>
To: kvm@vger.kernel.org
Cc: pbonzini@redhat.com, jmattson@google.com, wei.huang2@amd.com,
        babu.moger@amd.com
Subject: [PATCH 1/3] KVM: Add a stub for invpcid in the emulator table
Date: Thu, 11 Feb 2021 16:22:37 -0500
Message-Id: <20210211212241.3958897-2-bsd@redhat.com>
In-Reply-To: <20210211212241.3958897-1-bsd@redhat.com>
References: <20210211212241.3958897-1-bsd@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.12
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Upon an exception, this can be used to successfully
decode the instruction and will be used by the next patch
to inject the correct exception.

Signed-off-by: Bandan Das <bsd@redhat.com>
---
 arch/x86/kvm/emulate.c | 3 ++-
 1 file changed, 2 insertions(+), 1 deletion(-)

```
#### [GIT PULL] Please pull my kvm-ppc-next-5.12-1 tag
##### From: Paul Mackerras <paulus@ozlabs.org>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Paul Mackerras <paulus@ozlabs.org>
X-Patchwork-Id: 12082425
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-20.8 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_PATCH,
	INCLUDES_PULL_REQUEST,MAILING_LIST_MULTI,MENTIONS_GIT_HOSTING,SPF_HELO_NONE,
	SPF_PASS autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 5BB08C433E0
	for <kvm@archiver.kernel.org>; Thu, 11 Feb 2021 07:27:01 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 2F5D164E05
	for <kvm@archiver.kernel.org>; Thu, 11 Feb 2021 07:27:01 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S229544AbhBKH0p (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Thu, 11 Feb 2021 02:26:45 -0500
Received: from bilbo.ozlabs.org ([203.11.71.1]:41973 "EHLO ozlabs.org"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S229480AbhBKH0n (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 11 Feb 2021 02:26:43 -0500
Received: by ozlabs.org (Postfix, from userid 1003)
        id 4Dbp881PbXz9sB4; Thu, 11 Feb 2021 18:25:59 +1100 (AEDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple; d=ozlabs.org; s=201707;
        t=1613028360; bh=qu6nEoHZwmR4++I5Abr6z1RTfdyjVVJh3qE95Ap47aM=;
        h=Date:From:To:Cc:Subject:From;
        b=trt6YQD90kPke0B9zfpErNFjIIXhro2YWGjuYHgUXMof6m/hWBMC3zh98FS0podHT
         h+EvZUd7g/lAsuOPSQzsDRLybQlrDga8eDhLp6EvSfbkmV57Sb47HlSNJivs+ac+A3
         YeW1gqdSZExk/AgyVhmLMoHNKcBiVzolsqXkCgPT/gysf4srXOkfwNzIVBhCeQeB8J
         ZGNFr5etZCGkt4pmkh79262BL+yGYT7+mHDFdimbZPMRchy4EICHSlcL1luumOL3Qt
         rpOXwOo//Kohs1GaMcxebOqg61O9R9anjGg9myHkkWlqBBUxSNhSF/lk5uUds4vcRA
         x40/8rH6Kbv9A==
Date: Thu, 11 Feb 2021 18:25:53 +1100
From: Paul Mackerras <paulus@ozlabs.org>
To: Paolo Bonzini <pbonzini@redhat.com>, kvm@vger.kernel.org
Cc: kvm-ppc@vger.kernel.org
Subject: [GIT PULL] Please pull my kvm-ppc-next-5.12-1 tag
Message-ID: <20210211072553.GA2877131@thinks.paulus.ozlabs.org>
MIME-Version: 1.0
Content-Disposition: inline
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Paolo,

Please do a pull from my kvm-ppc-next-5.12-1 tag to get a PPC KVM
update for 5.12.  This one is quite small, with just one new feature,
support for the second data watchpoint in POWER10.

Thanks,
Paul.

The following changes since commit 9294b8a12585f8b4ccb9c060b54bab0bd13f24b9:

  Documentation: kvm: fix warning (2021-02-09 08:42:10 -0500)

are available in the git repository at:

  git://git.kernel.org/pub/scm/linux/kernel/git/paulus/powerpc tags/kvm-ppc-next-5.12-1

for you to fetch changes up to 72476aaa469179222b92c380de60c76b4cb9a318:

  KVM: PPC: Book3S HV: Fix host radix SLB optimisation with hash guests (2021-02-11 17:28:15 +1100)

----------------------------------------------------------------
PPC KVM update for 5.12

- Support for second data watchpoint on POWER10, from Ravi Bangoria
- Remove some complex workarounds for buggy early versions of POWER9
- Guest entry/exit fixes from Nick Piggin and Fabiano Rosas

----------------------------------------------------------------
Fabiano Rosas (2):
      KVM: PPC: Book3S HV: Save and restore FSCR in the P9 path
      KVM: PPC: Don't always report hash MMU capability for P9 < DD2.2

Nicholas Piggin (5):
      KVM: PPC: Book3S HV: Remove support for running HPT guest on RPT host without mixed mode support
      KVM: PPC: Book3S HV: Fix radix guest SLB side channel
      KVM: PPC: Book3S HV: No need to clear radix host SLB before loading HPT guest
      KVM: PPC: Book3S HV: Use POWER9 SLBIA IH=6 variant to clear SLB
      KVM: PPC: Book3S HV: Fix host radix SLB optimisation with hash guests

Paul Mackerras (1):
      KVM: PPC: Book3S HV: Ensure radix guest has no SLB entries

Ravi Bangoria (4):
      KVM: PPC: Book3S HV: Allow nested guest creation when L0 hv_guest_state > L1
      KVM: PPC: Book3S HV: Rename current DAWR macros and variables
      KVM: PPC: Book3S HV: Add infrastructure to support 2nd DAWR
      KVM: PPC: Book3S HV: Introduce new capability for 2nd DAWR

Yang Li (1):
      KVM: PPC: remove unneeded semicolon

 Documentation/virt/kvm/api.rst            |  12 ++
 arch/powerpc/include/asm/hvcall.h         |  25 ++++-
 arch/powerpc/include/asm/kvm_book3s_asm.h |  11 --
 arch/powerpc/include/asm/kvm_host.h       |   7 +-
 arch/powerpc/include/asm/kvm_ppc.h        |   2 +
 arch/powerpc/include/uapi/asm/kvm.h       |   2 +
 arch/powerpc/kernel/asm-offsets.c         |   9 +-
 arch/powerpc/kvm/book3s_hv.c              | 149 +++++++++++++++----------
 arch/powerpc/kvm/book3s_hv_builtin.c      | 108 +-----------------
 arch/powerpc/kvm/book3s_hv_nested.c       |  70 +++++++++---
 arch/powerpc/kvm/book3s_hv_rmhandlers.S   | 175 ++++++++++++++++--------------
 arch/powerpc/kvm/booke.c                  |   2 +-
 arch/powerpc/kvm/powerpc.c                |  14 ++-
 include/uapi/linux/kvm.h                  |   1 +
 tools/arch/powerpc/include/uapi/asm/kvm.h |   2 +
 tools/include/uapi/linux/kvm.h            |   1 +
 16 files changed, 309 insertions(+), 281 deletions(-)
```
#### [PATCH 4.19 19/24] Fix unsynchronized access to sev members through svm_register_enc_region
##### From: Greg Kroah-Hartman <gregkh@linuxfoundation.org>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Greg KH <gregkh@linuxfoundation.org>
X-Patchwork-Id: 12083527
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-19.3 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_CR_TRAILER,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,
	URIBL_BLOCKED,USER_AGENT_GIT autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id F19B3C433E9
	for <kvm@archiver.kernel.org>; Thu, 11 Feb 2021 15:23:42 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id C229B64F11
	for <kvm@archiver.kernel.org>; Thu, 11 Feb 2021 15:23:42 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S230355AbhBKPXJ (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Thu, 11 Feb 2021 10:23:09 -0500
Received: from mail.kernel.org ([198.145.29.99]:52624 "EHLO mail.kernel.org"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S230333AbhBKPUh (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 11 Feb 2021 10:20:37 -0500
Received: by mail.kernel.org (Postfix) with ESMTPSA id 5151464F2E;
        Thu, 11 Feb 2021 15:07:00 +0000 (UTC)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple; d=linuxfoundation.org;
        s=korg; t=1613056020;
        bh=MftR7VMP18psrqPKCYg64fQdJg2Q5xCCr+TeihrSvm0=;
        h=From:To:Cc:Subject:Date:In-Reply-To:References:From;
        b=c8gw9etrzq5oQ1oE5KKkNGzZzvF07HcMHGF9naYJt2Rg2shZLeT/5hyGbxK54OnvD
         AyxvSWO+xx9XH2AAncqEGlPYjNAgvQO0EaPUb203XBicVdJGgKYwdMH3/JR25Sae2r
         UYXHNh15+HQYyMg1o/sy4Dled8gDT6R45V7FBcT0=
From: Greg Kroah-Hartman <gregkh@linuxfoundation.org>
To: linux-kernel@vger.kernel.org
Cc: Greg Kroah-Hartman <gregkh@linuxfoundation.org>,
        stable@vger.kernel.org, Thomas Gleixner <tglx@linutronix.de>,
        Ingo Molnar <mingo@redhat.com>,
        "H. Peter Anvin" <hpa@zytor.com>,
        Paolo Bonzini <pbonzini@redhat.com>,
        Joerg Roedel <joro@8bytes.org>,
        Tom Lendacky <thomas.lendacky@amd.com>,
        Brijesh Singh <brijesh.singh@amd.com>,
        Sean Christopherson <seanjc@google.com>, x86@kernel.org,
        kvm@vger.kernel.org, Peter Gonda <pgonda@google.com>
Subject: [PATCH 4.19 19/24] Fix unsynchronized access to sev members through
 svm_register_enc_region
Date: Thu, 11 Feb 2021 16:02:53 +0100
Message-Id: <20210211150148.593771643@linuxfoundation.org>
X-Mailer: git-send-email 2.30.1
In-Reply-To: <20210211150147.743660073@linuxfoundation.org>
References: <20210211150147.743660073@linuxfoundation.org>
User-Agent: quilt/0.66
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Peter Gonda <pgonda@google.com>

commit 19a23da53932bc8011220bd8c410cb76012de004 upstream.

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

Message-Id: <20210127161524.2832400-1-pgonda@google.com>
Signed-off-by: Paolo Bonzini <pbonzini@redhat.com>
Signed-off-by: Greg Kroah-Hartman <gregkh@linuxfoundation.org>
---
 arch/x86/kvm/svm.c |   18 +++++++++++-------
```
#### [PATCH] KVM: arm64: Handle CMOs on Read Only memslots
##### From: Marc Zyngier <maz@kernel.org>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Marc Zyngier <maz@kernel.org>
X-Patchwork-Id: 12083477
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No,
 score=-17.0 required=3.0 tests=BAYES_00,INCLUDES_CR_TRAILER,
	INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED,
	USER_AGENT_GIT autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 3E7CFC433DB
	for <kvm@archiver.kernel.org>; Thu, 11 Feb 2021 14:31:32 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 0B52F60C3E
	for <kvm@archiver.kernel.org>; Thu, 11 Feb 2021 14:31:32 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S231263AbhBKObL (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Thu, 11 Feb 2021 09:31:11 -0500
Received: from mail.kernel.org ([198.145.29.99]:44706 "EHLO mail.kernel.org"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S232400AbhBKO2y (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 11 Feb 2021 09:28:54 -0500
Received: from disco-boy.misterjones.org (disco-boy.misterjones.org
 [51.254.78.96])
        (using TLSv1.2 with cipher ECDHE-RSA-AES256-GCM-SHA384 (256/256 bits))
        (No client certificate requested)
        by mail.kernel.org (Postfix) with ESMTPSA id CEEC364E14;
        Thu, 11 Feb 2021 14:27:52 +0000 (UTC)
Received: from 78.163-31-62.static.virginmediabusiness.co.uk ([62.31.163.78]
 helo=hot-poop.lan)
        by disco-boy.misterjones.org with esmtpsa  (TLS1.3) tls
 TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384
        (Exim 4.94)
        (envelope-from <maz@kernel.org>)
        id 1lACwg-00DYwa-7G; Thu, 11 Feb 2021 14:27:50 +0000
From: Marc Zyngier <maz@kernel.org>
To: kvmarm@lists.cs.columbia.edu, linux-arm-kernel@lists.infradead.org,
        kvm@vger.kernel.org
Cc: James Morse <james.morse@arm.com>,
        Julien Thierry <julien.thierry.kdev@gmail.com>,
        Suzuki K Poulose <suzuki.poulose@arm.com>,
        Alexandru Elisei <alexandru.elisei@arm.com>,
        Will Deacon <will@kernel.org>, kernel-team@android.com,
        Jianyong Wu <jianyong.wu@arm.com>
Subject: [PATCH] KVM: arm64: Handle CMOs on Read Only memslots
Date: Thu, 11 Feb 2021 14:27:38 +0000
Message-Id: <20210211142738.1478292-1-maz@kernel.org>
X-Mailer: git-send-email 2.30.0
MIME-Version: 1.0
X-SA-Exim-Connect-IP: 62.31.163.78
X-SA-Exim-Rcpt-To: kvmarm@lists.cs.columbia.edu,
 linux-arm-kernel@lists.infradead.org, kvm@vger.kernel.org,
 james.morse@arm.com, julien.thierry.kdev@gmail.com, suzuki.poulose@arm.com,
 alexandru.elisei@arm.com, will@kernel.org, kernel-team@android.com,
 jianyong.wu@arm.com
X-SA-Exim-Mail-From: maz@kernel.org
X-SA-Exim-Scanned: No (on disco-boy.misterjones.org);
 SAEximRunCond expanded to false
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

It appears that when a guest traps into KVM because it is
performing a CMO on a Read Only memslot, our handling of
this operation is "slightly suboptimal", as we treat it as
an MMIO access without a valid syndrome.

The chances that userspace is adequately equiped to deal
with such an exception being slim, it would be better to
handle it in the kernel.

What we need to provide is roughly as follows:

(a) if a CMO hits writeable memory, handle it as a normal memory acess
(b) if a CMO hits non-memory, skip it
(c) if a CMO hits R/O memory, that's where things become fun:
  (1) if the CMO is DC IVAC, the architecture says this should result
      in a permission fault
  (2) if the CMO is DC CIVAC, it should work similarly to (a)

We already perform (a) and (b) correctly, but (c) is a total mess.
Hence we need to distinguish between IVAC (c.1) and CIVAC (c.2).

One way to do it is to treat CMOs generating a translation fault as
a *read*, even when they are on a RW memslot. This allows us to
further triage things:

If they come back with a permission fault, that is because this is
a DC IVAC instruction:
- inside a RW memslot: no problem, treat it as a write (a)(c.2)
- inside a RO memslot: inject a data abort in the guest (c.1)

The only drawback is that DC IVAC on a yet unmapped page faults
twice: one for the initial translation fault that result in a RO
mapping, and once for the permission fault. I think we can live with
that.

Reported-by: Jianyong Wu <jianyong.wu@arm.com>
Signed-off-by: Marc Zyngier <maz@kernel.org>
---

Notes:
    I have taken the option to inject an abort in the guest when
    it issues a DC IVAC on a R/O memslot, but another option would
    be to just perform the invalidation ourselves as a DC CIAVAC.
    
    This would have the advantage of being consistent with what we
    do for emulated MMIO.

 arch/arm64/kvm/mmu.c | 53 ++++++++++++++++++++++++++++++++++----------
 1 file changed, 41 insertions(+), 12 deletions(-)

```
