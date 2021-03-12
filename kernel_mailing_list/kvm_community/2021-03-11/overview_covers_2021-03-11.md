

#### [PATCH v3 0/2] KVM: arm64: Assorted IPA size fixes
##### From: Marc Zyngier <maz@kernel.org>
X-SA-Exim-Mail-From: maz@kernel.org

```c
From patchwork Thu Mar 11 10:00:14 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Marc Zyngier <maz@kernel.org>
X-Patchwork-Id: 12130765
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-12.0 required=3.0 tests=BAYES_00,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT autolearn=ham
	autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 1655CC433E6
	for <kvm@archiver.kernel.org>; Thu, 11 Mar 2021 10:01:31 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id B794164F38
	for <kvm@archiver.kernel.org>; Thu, 11 Mar 2021 10:01:30 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S232149AbhCKKBA (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Thu, 11 Mar 2021 05:01:00 -0500
Received: from mail.kernel.org ([198.145.29.99]:56284 "EHLO mail.kernel.org"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S232106AbhCKKA1 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 11 Mar 2021 05:00:27 -0500
Received: from disco-boy.misterjones.org (disco-boy.misterjones.org
 [51.254.78.96])
        (using TLSv1.2 with cipher ECDHE-RSA-AES256-GCM-SHA384 (256/256 bits))
        (No client certificate requested)
        by mail.kernel.org (Postfix) with ESMTPSA id BA0D364E55;
        Thu, 11 Mar 2021 10:00:26 +0000 (UTC)
Received: from 78.163-31-62.static.virginmediabusiness.co.uk ([62.31.163.78]
 helo=why.lan)
        by disco-boy.misterjones.org with esmtpsa  (TLS1.3) tls
 TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384
        (Exim 4.94)
        (envelope-from <maz@kernel.org>)
        id 1lKI7E-000xb0-FG; Thu, 11 Mar 2021 10:00:24 +0000
From: Marc Zyngier <maz@kernel.org>
To: linux-arm-kernel@lists.infradead.org, kvmarm@lists.cs.columbia.edu,
        kvm@vger.kernel.org
Cc: James Morse <james.morse@arm.com>,
        Julien Thierry <julien.thierry.kdev@gmail.com>,
        Suzuki K Poulose <suzuki.poulose@arm.com>,
        Will Deacon <will@kernel.org>,
        Andrew Jones <drjones@redhat.com>,
        Eric Auger <eric.auger@redhat.com>,
        Alexandru Elisei <alexandru.elisei@arm.com>,
        kernel-team@android.com
Subject: [PATCH v3 0/2] KVM: arm64: Assorted IPA size fixes
Date: Thu, 11 Mar 2021 10:00:14 +0000
Message-Id: <20210311100016.3830038-1-maz@kernel.org>
X-Mailer: git-send-email 2.29.2
MIME-Version: 1.0
X-SA-Exim-Connect-IP: 62.31.163.78
X-SA-Exim-Rcpt-To: linux-arm-kernel@lists.infradead.org,
 kvmarm@lists.cs.columbia.edu, kvm@vger.kernel.org, james.morse@arm.com,
 julien.thierry.kdev@gmail.com, suzuki.poulose@arm.com, will@kernel.org,
 drjones@redhat.com, eric.auger@redhat.com, alexandru.elisei@arm.com,
 kernel-team@android.com
X-SA-Exim-Mail-From: maz@kernel.org
X-SA-Exim-Scanned: No (on disco-boy.misterjones.org);
 SAEximRunCond expanded to false
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This is a rework of an initial patch posted a couple of days back[1]

While working on enabling KVM on "reduced IPA size" systems, I realise
we have a couple of issues, some of while do impact userspace.

The first issue is that we accept the creation of a "default IPA size"
VM (40 bits) even when the HW doesn't support it. Not good.

The second one is that we disallow a memslot to end right where the
IPA limit is. One page less and you're good, but that's not quite what
it should be.

I intend for both patches to be backported to -stable.

Thanks,

	M.

* From v2 [2]:
  - Fix silly printk blunder
  - Added Cc-stable and Fixes tags

* From v1 [1]:
  - Don't try to cap the default IPA size. If userspace uses 0 with an
    expectation that it will get 40bits, we should abide by it and
    return an error immediately (noticed by Andrew)
  - Added a new patch to fix the exclusive nature of the IPA limit
  
[1] https://lore.kernel.org/r/20210308174643.761100-1-maz@kernel.org
[2] https://lore.kernel.org/r/20210310104208.3819061-1-maz@kernel.org

Marc Zyngier (2):
  KVM: arm64: Reject VM creation when the default IPA size is
    unsupported
  KVM: arm64: Fix exclusive limit for IPA size

 Documentation/virt/kvm/api.rst |  3 +++
 arch/arm64/kvm/mmu.c           |  3 +--
 arch/arm64/kvm/reset.c         | 12 ++++++++----
 3 files changed, 12 insertions(+), 6 deletions(-)
```
#### [PATCH 0/2] vhost-vdpa: fix issues around v->config_ctx handling
##### From: Stefano Garzarella <sgarzare@redhat.com>

```c
From patchwork Thu Mar 11 13:52:55 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Stefano Garzarella <sgarzare@redhat.com>
X-Patchwork-Id: 12131411
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.0 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_PATCH,MAILING_LIST_MULTI,MENTIONS_GIT_HOSTING,SPF_HELO_NONE,SPF_PASS
	autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 14525C433DB
	for <kvm@archiver.kernel.org>; Thu, 11 Mar 2021 13:53:54 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id B92B464F9F
	for <kvm@archiver.kernel.org>; Thu, 11 Mar 2021 13:53:53 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S233814AbhCKNxW (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Thu, 11 Mar 2021 08:53:22 -0500
Received: from us-smtp-delivery-124.mimecast.com ([63.128.21.124]:47169 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S233803AbhCKNxJ (ORCPT
        <rfc822;kvm@vger.kernel.org>); Thu, 11 Mar 2021 08:53:09 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1615470788;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:content-type:content-type:
         content-transfer-encoding:content-transfer-encoding;
        bh=59EuosthGHx5pcdxoFo5VSdTfTOx4fAiPVEz1PyRq70=;
        b=MvjvTvU9I+BRyLrlPjOXsXa3NYFzRJDanzmt3m/H3CcOUQOe19UmGwzHeF9/yyRd07/wyY
        /UH1h+Wz8pAlFqqL+CvkONYkQXQ5ND2a1IxXhDnGvXmuE4eb/hwESghBQ6ou+pjTo8f812
        +WOSccn2cCDDEoGKYzzpo4xPkpGeD6o=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-326--AguXVqBONyBY1GEZFmkUw-1; Thu, 11 Mar 2021 08:53:04 -0500
X-MC-Unique: -AguXVqBONyBY1GEZFmkUw-1
Received: from smtp.corp.redhat.com (int-mx08.intmail.prod.int.phx2.redhat.com
 [10.5.11.23])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id B554C100C618;
        Thu, 11 Mar 2021 13:53:03 +0000 (UTC)
Received: from steredhat.redhat.com (ovpn-113-146.ams2.redhat.com
 [10.36.113.146])
        by smtp.corp.redhat.com (Postfix) with ESMTP id D748A196E3;
        Thu, 11 Mar 2021 13:52:58 +0000 (UTC)
From: Stefano Garzarella <sgarzare@redhat.com>
To: virtualization@lists.linux-foundation.org
Cc: Jason Wang <jasowang@redhat.com>, netdev@vger.kernel.org,
        Zhu Lingshan <lingshan.zhu@intel.com>,
        "Michael S. Tsirkin" <mst@redhat.com>,
        linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Subject: [PATCH 0/2] vhost-vdpa: fix issues around v->config_ctx handling
Date: Thu, 11 Mar 2021 14:52:55 +0100
Message-Id: <20210311135257.109460-1-sgarzare@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.84 on 10.5.11.23
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

While writing a test for a Rust library [1] to handle vhost-vdpa devices,
I experienced the 'use-after-free' issue fixed in patch 1, then I
discovered the potential issue when eventfd_ctx_fdget() fails fixed in
patch 2.

Do you think it might be useful to write a vdpa test suite, perhaps using
this Rust library [2] ?
Could we put it in the kernel tree in tool/testing?

Thanks,
Stefano

[1] https://github.com/stefano-garzarella/vhost/tree/vdpa
[2] https://github.com/rust-vmm/vhost

Stefano Garzarella (2):
  vhost-vdpa: fix use-after-free of v->config_ctx
  vhost-vdpa: set v->config_ctx to NULL if eventfd_ctx_fdget() fails

 drivers/vhost/vdpa.c | 12 +++++++++---
 1 file changed, 9 insertions(+), 3 deletions(-)
```
#### [PATCH v7 00/14] x86: major paravirt cleanup
##### From: Juergen Gross <jgross@suse.com>

```c
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=suse.com; s=susede1;
        t=1615472603;
 h=from:from:reply-to:date:date:message-id:message-id:to:to:cc:cc:
         mime-version:mime-version:
  content-transfer-encoding:content-transfer-encoding;
        bh=po4QZsHAN+vzX5uvzJmshXlPCac7n69c5r9Fdn0dvCo=;
        b=sjqqOUQpbELgunG51bLYnaAneLdLoAHn6rXcSwK/DsFchfLZJWPal7opKb2RUZtxFSKIEo
        JbtKBiDJ2iWmLlE8dN17PcQJiP6NCqXX2GAZhWcMmbQgbNa+4/4kethaBp09UxMuCAjwFQ
        d8u620eAOSyPtbAZDTHxKFPkybBM2LQ=
Received: from relay2.suse.de (unknown [195.135.221.27])
        by mx2.suse.de (Postfix) with ESMTP id DB47BAC23;
        Thu, 11 Mar 2021 14:23:22 +0000 (UTC)
From: Juergen Gross <jgross@suse.com>
To: xen-devel@lists.xenproject.org, x86@kernel.org,
        linux-kernel@vger.kernel.org,
        virtualization@lists.linux-foundation.org,
        linux-arm-kernel@lists.infradead.org, linux-hyperv@vger.kernel.org,
        kvm@vger.kernel.org, clang-built-linux@googlegroups.com
Cc: Juergen Gross <jgross@suse.com>, Andy Lutomirski <luto@kernel.org>,
        Thomas Gleixner <tglx@linutronix.de>,
        Ingo Molnar <mingo@redhat.com>, Borislav Petkov <bp@alien8.de>,
        "H. Peter Anvin" <hpa@zytor.com>,
        Peter Zijlstra <peterz@infradead.org>,
        Josh Poimboeuf <jpoimboe@redhat.com>,
        Jason Baron <jbaron@akamai.com>,
        Steven Rostedt <rostedt@goodmis.org>,
        Ard Biesheuvel <ardb@kernel.org>, Deep Shah <sdeep@vmware.com>,
        "VMware, Inc." <pv-drivers@vmware.com>,
        Russell King <linux@armlinux.org.uk>,
        Catalin Marinas <catalin.marinas@arm.com>,
        Will Deacon <will@kernel.org>,
        "K. Y. Srinivasan" <kys@microsoft.com>,
        Haiyang Zhang <haiyangz@microsoft.com>,
        Stephen Hemminger <sthemmin@microsoft.com>,
        Wei Liu <wei.liu@kernel.org>,
        Paolo Bonzini <pbonzini@redhat.com>,
        Sean Christopherson <seanjc@google.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>,
        Boris Ostrovsky <boris.ostrovsky@oracle.com>,
        Stefano Stabellini <sstabellini@kernel.org>,
        Nathan Chancellor <nathan@kernel.org>,
        Nick Desaulniers <ndesaulniers@google.com>
Subject: [PATCH v7 00/14] x86: major paravirt cleanup
Date: Thu, 11 Mar 2021 15:23:05 +0100
Message-Id: <20210311142319.4723-1-jgross@suse.com>
X-Mailer: git-send-email 2.26.2
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This is a major cleanup of the paravirt infrastructure aiming at
eliminating all custom code patching via paravirt patching.

This is achieved by using ALTERNATIVE instead, leading to the ability
to give objtool access to the patched in instructions.

In order to remove most of the 32-bit special handling from pvops the
time related operations are switched to use static_call() instead.

At the end of this series all paravirt patching has to do is to
replace indirect calls with direct ones. In a further step this could
be switched to static_call(), too.

Changes in V7:
- dropped patch 3, as already applied on tip tree
- new patch 3 (patches 1 and 7 have been added to V6 late)
- addressed comments by Boris

Changes in V6:
- switched back to "not" bit in feature value for "not feature"
- other minor comments addressed

Changes in V5:
- patches 1-5 of V4 dropped, as already applied
- new patches 1+3
- fixed patch 2
- split V4 patch 8 into patches 4+5
- use flag byte instead of negative feature bit for "not feature"

Changes in V4:
- fixed several build failures
- removed objtool patch, as objtool patches are in tip now
- added patch 1 for making usage of static_call easier
- even more cleanup

Changes in V3:
- added patches 7 and 12
- addressed all comments

Changes in V2:
- added patches 5-12

Juergen Gross (14):
  x86/alternative: merge include files
  static_call: move struct static_call_key definition to
    static_call_types.h
  static_call: add function to query current function
  x86/paravirt: switch time pvops functions to use static_call()
  x86/alternative: support not-feature
  x86/alternative: support ALTERNATIVE_TERNARY
  x86/alternative: don't open code ALTERNATIVE_TERNARY() in
    _static_cpu_has()
  x86: add new features for paravirt patching
  x86/paravirt: remove no longer needed 32-bit pvops cruft
  x86/paravirt: simplify paravirt macros
  x86/paravirt: switch iret pvops to ALTERNATIVE
  x86/paravirt: add new macros PVOP_ALT* supporting pvops in
    ALTERNATIVEs
  x86/paravirt: switch functions with custom code to ALTERNATIVE
  x86/paravirt: have only one paravirt patch function

 arch/arm/include/asm/paravirt.h          |  14 +-
 arch/arm/kernel/paravirt.c               |   9 +-
 arch/arm64/include/asm/paravirt.h        |  14 +-
 arch/arm64/kernel/paravirt.c             |  13 +-
 arch/x86/Kconfig                         |   1 +
 arch/x86/entry/entry_32.S                |   6 +-
 arch/x86/entry/entry_64.S                |   2 +-
 arch/x86/entry/vdso/vdso32/system_call.S |   2 +-
 arch/x86/include/asm/alternative-asm.h   | 114 ------------
 arch/x86/include/asm/alternative.h       | 126 +++++++++++++-
 arch/x86/include/asm/cpufeature.h        |  41 +----
 arch/x86/include/asm/cpufeatures.h       |   2 +
 arch/x86/include/asm/irqflags.h          |   7 +-
 arch/x86/include/asm/mshyperv.h          |   2 +-
 arch/x86/include/asm/nospec-branch.h     |   1 -
 arch/x86/include/asm/paravirt.h          | 167 ++++++++----------
 arch/x86/include/asm/paravirt_types.h    | 210 +++++++++--------------
 arch/x86/include/asm/smap.h              |   5 +-
 arch/x86/kernel/Makefile                 |   3 +-
 arch/x86/kernel/alternative.c            |  52 +++++-
 arch/x86/kernel/asm-offsets.c            |   7 -
 arch/x86/kernel/cpu/vmware.c             |   5 +-
 arch/x86/kernel/kvm.c                    |   2 +-
 arch/x86/kernel/kvmclock.c               |   2 +-
 arch/x86/kernel/paravirt-spinlocks.c     |   9 +
 arch/x86/kernel/paravirt.c               |  75 ++------
 arch/x86/kernel/paravirt_patch.c         |  99 -----------
 arch/x86/kernel/tsc.c                    |   3 +-
 arch/x86/lib/atomic64_386_32.S           |   2 +-
 arch/x86/lib/atomic64_cx8_32.S           |   2 +-
 arch/x86/lib/copy_page_64.S              |   2 +-
 arch/x86/lib/copy_user_64.S              |   2 +-
 arch/x86/lib/memcpy_64.S                 |   2 +-
 arch/x86/lib/memmove_64.S                |   2 +-
 arch/x86/lib/memset_64.S                 |   2 +-
 arch/x86/lib/retpoline.S                 |   2 +-
 arch/x86/xen/enlighten_pv.c              |   4 +-
 arch/x86/xen/time.c                      |  26 +--
 drivers/xen/time.c                       |   3 +-
 include/linux/static_call.h              |  26 +--
 include/linux/static_call_types.h        |  18 ++
 tools/include/linux/static_call_types.h  |  18 ++
 42 files changed, 473 insertions(+), 631 deletions(-)
 delete mode 100644 arch/x86/include/asm/alternative-asm.h
 delete mode 100644 arch/x86/kernel/paravirt_patch.c
```
