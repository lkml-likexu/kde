#### [PATCH v3 01/35] x86/apic: Fix x2apic enablement without interrupt remapping
##### From: David Woodhouse <dwmw2@infradead.org>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: David Woodhouse <dwmw2@infradead.org>
X-Patchwork-Id: 11854991
Return-Path: <SRS0=sCQZ=D7=vger.kernel.org=kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-12.8 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SIGNED_OFF_BY,SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED,
	USER_AGENT_GIT autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 637B8C56202
	for <kvm@archiver.kernel.org>; Sat, 24 Oct 2020 21:35:47 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 0C4842226B
	for <kvm@archiver.kernel.org>; Sat, 24 Oct 2020 21:35:47 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=infradead.org header.i=@infradead.org
 header.b="c4PrqY0S"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1764673AbgJXVfp (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Sat, 24 Oct 2020 17:35:45 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:33832 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1764652AbgJXVfo (ORCPT <rfc822;kvm@vger.kernel.org>);
        Sat, 24 Oct 2020 17:35:44 -0400
Received: from casper.infradead.org (casper.infradead.org
 [IPv6:2001:8b0:10b:1236::1])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 7D9E7C0613D4;
        Sat, 24 Oct 2020 14:35:44 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; q=dns/txt; c=relaxed/relaxed;
        d=infradead.org; s=casper.20170209;
 h=Sender:Content-Transfer-Encoding:
        MIME-Version:References:In-Reply-To:Message-Id:Date:Subject:Cc:To:From:
        Reply-To:Content-Type:Content-ID:Content-Description;
        bh=j8yx8UZGkkgJFZytyZ6qp2N6IE4R2j2WOfRw0cU2eg0=;
 b=c4PrqY0Sw2gyT5FhUqzJHyXFpX
        9RfjAP4Dhw2AKcmR9PtzNHMnOf5hPAi+yquiWwoNlA871X+qNPC/7SpDCBNx3xz/wsqG/iB+wjd0Y
        jAkl2FAD4QTDHF3k48QuLt+fAKwOssUFb3bEfec5cQwhmnSgMU726YLLNoyitQgqEBsrzcRqKIDs+
        tPuno7XMj3Ae77yIDTJ5I80NPe1LQNQx5P9ztCppsD9OaHWpgogD7l1MoszYtaNGJlldzolP3tkYF
        /ZiuY4JC9JmxQwTaimrifxv6lu3Pa9Cu3ZreP2dE9sljzvfb6Q0eeFBfjnm+JNg2Z15w+jjag0b3N
        PTUC5J9Q==;
Received: from i7.infradead.org ([2001:8b0:10b:1:21e:67ff:fecb:7a92])
        by casper.infradead.org with esmtpsa (Exim 4.92.3 #3 (Red Hat Linux))
        id 1kWRCN-0006Ge-Uw; Sat, 24 Oct 2020 21:35:41 +0000
Received: from dwoodhou by i7.infradead.org with local (Exim 4.93 #3 (Red Hat
 Linux))
        id 1kWRCM-001rNc-JR; Sat, 24 Oct 2020 22:35:38 +0100
From: David Woodhouse <dwmw2@infradead.org>
To: x86@kernel.org
Cc: kvm <kvm@vger.kernel.org>, iommu@lists.linux-foundation.org,
        joro@8bytes.org, Thomas Gleixner <tglx@linutronix.de>,
        Paolo Bonzini <pbonzini@redhat.com>,
        linux-kernel <linux-kernel@vger.kernel.org>,
        linux-hyperv@vger.kernel.org, maz@misterjones.org,
        Dexuan Cui <decui@microsoft.com>
Subject: [PATCH v3 01/35] x86/apic: Fix x2apic enablement without interrupt
 remapping
Date: Sat, 24 Oct 2020 22:35:01 +0100
Message-Id: <20201024213535.443185-2-dwmw2@infradead.org>
X-Mailer: git-send-email 2.26.2
In-Reply-To: <20201024213535.443185-1-dwmw2@infradead.org>
References: <e6601ff691afb3266e365a91e8b221179daf22c2.camel@infradead.org>
 <20201024213535.443185-1-dwmw2@infradead.org>
MIME-Version: 1.0
Sender: David Woodhouse <dwmw2@infradead.org>
X-SRS-Rewrite: SMTP reverse-path rewritten from <dwmw2@infradead.org> by
 casper.infradead.org. See http://www.infradead.org/rpr.html
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: David Woodhouse <dwmw@amazon.co.uk>

Currently, Linux as a hypervisor guest will enable x2apic only if there are
no CPUs present at boot time with an APIC ID above 255.

Hotplugging a CPU later with a higher APIC ID would result in a CPU which
cannot be targeted by external interrupts.

Add a filter in x2apic_apic_id_valid() which can be used to prevent such
CPUs from coming online, and allow x2apic to be enabled even if they are
present at boot time.

Fixes: ce69a784504 ("x86/apic: Enable x2APIC without interrupt remapping under KVM")
Signed-off-by: David Woodhouse <dwmw@amazon.co.uk>
Signed-off-by: Thomas Gleixner <tglx@linutronix.de>
---
 arch/x86/include/asm/apic.h        |  1 +
 arch/x86/kernel/apic/apic.c        | 14 ++++++++------
 arch/x86/kernel/apic/x2apic_phys.c |  9 +++++++++
 3 files changed, 18 insertions(+), 6 deletions(-)

```
#### [GIT PULL] KVM fixes for Linux 5.10-rc1
##### From: Paolo Bonzini <pbonzini@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Paolo Bonzini <pbonzini@redhat.com>
X-Patchwork-Id: 11854785
Return-Path: <SRS0=sCQZ=D7=vger.kernel.org=kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-13.9 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_PULL_REQUEST,MAILING_LIST_MULTI,MENTIONS_GIT_HOSTING,SPF_HELO_NONE,
	SPF_PASS autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id D94D7C55178
	for <kvm@archiver.kernel.org>; Sat, 24 Oct 2020 09:02:05 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 97C2C22280
	for <kvm@archiver.kernel.org>; Sat, 24 Oct 2020 09:02:05 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="dEKjDMwE"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1760185AbgJXJCD (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Sat, 24 Oct 2020 05:02:03 -0400
Received: from us-smtp-delivery-124.mimecast.com ([63.128.21.124]:24942 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S464830AbgJXJCC (ORCPT
        <rfc822;kvm@vger.kernel.org>); Sat, 24 Oct 2020 05:02:02 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1603530121;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=WsLnm4h/QDa//59tO5yt/GI/Eb0fBcrMjcG64YafxHk=;
        b=dEKjDMwE8BlznUw+sjvdtYP/ByKlRPkH44Vq1T+Y6hTT+CGIdDz6LM2cAXU76LVgbnxwLr
        VjeHTK9rgptFvNp8856Za7A9NHdeUEBXhFc+fZnHoAVSYi8KTwgPz8WyEJWDWgYmVkpMHh
        ZkLmk4HYIYsr9/7IVUrIcHIClbH3b2Y=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-10-qpo_KEXKO6acdAvr6sRrLA-1; Sat, 24 Oct 2020 05:01:59 -0400
X-MC-Unique: qpo_KEXKO6acdAvr6sRrLA-1
Received: from smtp.corp.redhat.com (int-mx07.intmail.prod.int.phx2.redhat.com
 [10.5.11.22])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 58DD85F9E8;
        Sat, 24 Oct 2020 09:01:58 +0000 (UTC)
Received: from virtlab701.virt.lab.eng.bos.redhat.com
 (virtlab701.virt.lab.eng.bos.redhat.com [10.19.152.228])
        by smtp.corp.redhat.com (Postfix) with ESMTP id E903D10027AB;
        Sat, 24 Oct 2020 09:01:57 +0000 (UTC)
From: Paolo Bonzini <pbonzini@redhat.com>
To: torvalds@linux-foundation.org
Cc: linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Subject: [GIT PULL] KVM fixes for Linux 5.10-rc1
Date: Sat, 24 Oct 2020 05:01:57 -0400
Message-Id: <20201024090157.2818024-1-pbonzini@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.84 on 10.5.11.22
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Linus,

The following changes since commit 29cf0f5007a215b51feb0ae25ca5353480d53ead:

  kvm: x86/mmu: NX largepage recovery for TDP MMU (2020-10-23 03:42:16 -0400)

are available in the Git repository at:

  https://git.kernel.org/pub/scm/virt/kvm/kvm.git tags/for-linus

for you to fetch changes up to 77377064c3a94911339f13ce113b3abf265e06da:

  KVM: ioapic: break infinite recursion on lazy EOI (2020-10-24 04:42:06 -0400)

----------------------------------------------------------------
Two fixes for the pull request, and an unrelated bugfix for
a host hang.

----------------------------------------------------------------

Paolo Bonzini (1):
      KVM: vmx: rename pi_init to avoid conflict with paride

Sean Christopherson (1):
      KVM: x86/mmu: Avoid modulo operator on 64-bit value to fix i386 build

Vitaly Kuznetsov (1):
      KVM: ioapic: break infinite recursion on lazy EOI

 arch/x86/kvm/ioapic.c          | 5 +----
 arch/x86/kvm/mmu/tdp_mmu.c     | 2 +-
 arch/x86/kvm/vmx/posted_intr.c | 2 +-
 arch/x86/kvm/vmx/posted_intr.h | 4 ++--
 arch/x86/kvm/vmx/vmx.c         | 2 +-
 5 files changed, 6 insertions(+), 9 deletions(-)
```
#### [PATCH] KVM: ioapic: break infinite recursion on lazy EOI
##### From: Paolo Bonzini <pbonzini@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Paolo Bonzini <pbonzini@redhat.com>
X-Patchwork-Id: 11854783
Return-Path: <SRS0=sCQZ=D7=vger.kernel.org=kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-9.9 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_PATCH,MAILING_LIST_MULTI,SIGNED_OFF_BY,SPF_HELO_NONE,SPF_PASS
	autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 9FBEBC55178
	for <kvm@archiver.kernel.org>; Sat, 24 Oct 2020 08:17:38 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 6288420FC3
	for <kvm@archiver.kernel.org>; Sat, 24 Oct 2020 08:17:38 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="h2JcgShC"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1760013AbgJXIRe (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Sat, 24 Oct 2020 04:17:34 -0400
Received: from us-smtp-delivery-124.mimecast.com ([63.128.21.124]:48030 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1755393AbgJXIRc (ORCPT
        <rfc822;kvm@vger.kernel.org>); Sat, 24 Oct 2020 04:17:32 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1603527451;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=NnkQ/HnGwhFyFBjodi9ogghF5+/5xJZIfgVYIwXmUTg=;
        b=h2JcgShCFpwz+n9UvuGz4QWmbMqwIeeiHvfATPfmlwYoiKS2fy4kWrYWYoYvGezO3+A52Y
        5kQQVssmkNHAbAuGUkSfBLGJSgLwrxeJy0Q1cmu4YeLOysV6Q170SeE1c/5urnG9kdZ33m
        0+rJI/XJ+IHMT8rILhKPVGFM6Ui+bYI=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-352-4TJLjx1CP72pHzZhqzXkRw-1; Sat, 24 Oct 2020 04:17:28 -0400
X-MC-Unique: 4TJLjx1CP72pHzZhqzXkRw-1
Received: from smtp.corp.redhat.com (int-mx06.intmail.prod.int.phx2.redhat.com
 [10.5.11.16])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id DF25F805F0D;
        Sat, 24 Oct 2020 08:17:27 +0000 (UTC)
Received: from virtlab701.virt.lab.eng.bos.redhat.com
 (virtlab701.virt.lab.eng.bos.redhat.com [10.19.152.228])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 95F1A5C1C4;
        Sat, 24 Oct 2020 08:17:24 +0000 (UTC)
From: Paolo Bonzini <pbonzini@redhat.com>
To: linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Cc: Vitaly Kuznetsov <vkuznets@redhat.com>,
        Alex Williamson <alex.williamson@redhat.com>
Subject: [PATCH] KVM: ioapic: break infinite recursion on lazy EOI
Date: Sat, 24 Oct 2020 04:17:24 -0400
Message-Id: <20201024081724.2799401-1-pbonzini@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.16
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Vitaly Kuznetsov <vkuznets@redhat.com>

During shutdown the IOAPIC trigger mode is reset to edge triggered
while the vfio-pci INTx is still registered with a resampler.
This allows us to get into an infinite loop:

ioapic_set_irq
  -> ioapic_lazy_update_eoi
  -> kvm_ioapic_update_eoi_one
  -> kvm_notify_acked_irq
  -> kvm_notify_acked_gsi
  -> (via irq_acked fn ptr) irqfd_resampler_ack
  -> kvm_set_irq
  -> (via set fn ptr) kvm_set_ioapic_irq
  -> kvm_ioapic_set_irq
  -> ioapic_set_irq

Commit 7faab2faca0c acknowledges that this recursion loop exists
and tries to avoid it at the call to ioapic_lazy_update_eoi, but at
this point the scenario is already set, we have an edge interrupt with
resampler on the same gsi.

Fortunately, the only user of irq ack notifiers (in addition to resamplefd)
is i8254 timer interrupt reinjection.  These are edge-triggered, so in
principle they would need the call to kvm_ioapic_update_eoi_one from
ioapic_lazy_update_eoi, but they already disable AVIC(*), so they don't
need the lazy EOI behavior.  Therefore, remove the call to
kvm_ioapic_update_eoi_one from ioapic_lazy_update_eoi.

This fixes CVE-2020-27152.  Note that this issue cannot happen with
SR-IOV assigned devices because virtual functions do not have INTx,
only MSI.

Suggested-by: Paolo Bonzini <pbonzini@redhat.com>
Tested-by: Alex Williamson <alex.williamson@redhat.com>
Signed-off-by: Vitaly Kuznetsov <vkuznets@redhat.com>
Signed-off-by: Paolo Bonzini <pbonzini@redhat.com>
---
 arch/x86/kvm/ioapic.c | 5 +----
 1 file changed, 1 insertion(+), 4 deletions(-)

```
#### [PATCH] KVM: vmx: rename pi_init to avoid conflict with paride
##### From: Paolo Bonzini <pbonzini@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Paolo Bonzini <pbonzini@redhat.com>
X-Patchwork-Id: 11854781
Return-Path: <SRS0=sCQZ=D7=vger.kernel.org=kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-9.8 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_PATCH,MAILING_LIST_MULTI,SIGNED_OFF_BY,SPF_HELO_NONE,SPF_PASS,
	URIBL_BLOCKED autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 73D24C2D0A3
	for <kvm@archiver.kernel.org>; Sat, 24 Oct 2020 08:13:44 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 0D1F62177B
	for <kvm@archiver.kernel.org>; Sat, 24 Oct 2020 08:13:43 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="fNT5fTGO"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1759993AbgJXINd (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Sat, 24 Oct 2020 04:13:33 -0400
Received: from us-smtp-delivery-124.mimecast.com ([216.205.24.124]:34089 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1759987AbgJXIKd (ORCPT
        <rfc822;kvm@vger.kernel.org>); Sat, 24 Oct 2020 04:10:33 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1603527029;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=MxP14utHMULsl3WXK0dJ6zVnCUZr6qoeodCunclasgs=;
        b=fNT5fTGOhUPuPL2XrMp8Ii2z8qmB+Sic+g/rNl+0w6Sl+TnJufasAP1uG+WwmewsB/KTHj
        GKDQVSMeelZ3C0YjbEgUvuDwtnlheVgBvBAhhb1sMXHhN7hCSXx9IW4xYzrqAShuu7Tk9v
        Go1U2aQoETR35koGkHGhuh8MITH1+lU=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-485-yLgipaYwOY2OHFz0_xmqIg-1; Sat, 24 Oct 2020 04:10:27 -0400
X-MC-Unique: yLgipaYwOY2OHFz0_xmqIg-1
Received: from smtp.corp.redhat.com (int-mx05.intmail.prod.int.phx2.redhat.com
 [10.5.11.15])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id D9A95186DD23;
        Sat, 24 Oct 2020 08:10:25 +0000 (UTC)
Received: from virtlab701.virt.lab.eng.bos.redhat.com
 (virtlab701.virt.lab.eng.bos.redhat.com [10.19.152.228])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 5CE025578A;
        Sat, 24 Oct 2020 08:10:25 +0000 (UTC)
From: Paolo Bonzini <pbonzini@redhat.com>
To: linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Cc: Jens Axboe <axboe@kernel.dk>
Subject: [PATCH] KVM: vmx: rename pi_init to avoid conflict with paride
Date: Sat, 24 Oct 2020 04:10:24 -0400
Message-Id: <20201024081024.2798990-1-pbonzini@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.15
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

allyesconfig results in:

ld: drivers/block/paride/paride.o: in function `pi_init':
(.text+0x1340): multiple definition of `pi_init'; arch/x86/kvm/vmx/posted_intr.o:posted_intr.c:(.init.text+0x0): first defined here
make: *** [Makefile:1164: vmlinux] Error 1

because commit:

commit 8888cdd0996c2d51cd417f9a60a282c034f3fa28
Author: Xiaoyao Li <xiaoyao.li@intel.com>
Date:   Wed Sep 23 11:31:11 2020 -0700

    KVM: VMX: Extract posted interrupt support to separate files

added another pi_init(), though one already existed in the paride code.

Reported-by: Jens Axboe <axboe@kernel.dk>
Signed-off-by: Paolo Bonzini <pbonzini@redhat.com>
---
 arch/x86/kvm/vmx/posted_intr.c | 2 +-
 arch/x86/kvm/vmx/posted_intr.h | 4 ++--
 arch/x86/kvm/vmx/vmx.c         | 2 +-
 3 files changed, 4 insertions(+), 4 deletions(-)

```
#### [PATCH] KVM: x86/mmu: Avoid modulo operator on 64-bit value to fix i386 build
##### From: Sean Christopherson <sean.j.christopherson@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 8bit
X-Patchwork-Submitter: Sean Christopherson <sean.j.christopherson@intel.com>
X-Patchwork-Id: 11854687
Return-Path: <SRS0=sCQZ=D7=vger.kernel.org=kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-12.7 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_PATCH,MAILING_LIST_MULTI,SIGNED_OFF_BY,
	SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED,USER_AGENT_GIT autolearn=unavailable
	autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 478ECC55178
	for <kvm@archiver.kernel.org>; Sat, 24 Oct 2020 03:12:12 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id E7F8720578
	for <kvm@archiver.kernel.org>; Sat, 24 Oct 2020 03:12:11 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1759315AbgJXDMI (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Fri, 23 Oct 2020 23:12:08 -0400
Received: from mga06.intel.com ([134.134.136.31]:38867 "EHLO mga06.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1759309AbgJXDMH (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 23 Oct 2020 23:12:07 -0400
IronPort-SDR: 
 D5OXP6KpamIb9aVNOSFKkZTTJQT7tLUkUDHFFUhlJuDOi3uzpsPSYjD3vlYiti0N+VOhBuitJp
 /2r60hwkENaA==
X-IronPort-AV: E=McAfee;i="6000,8403,9783"; a="229389569"
X-IronPort-AV: E=Sophos;i="5.77,410,1596524400";
   d="scan'208";a="229389569"
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from fmsmga002.fm.intel.com ([10.253.24.26])
  by orsmga104.jf.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 23 Oct 2020 20:11:59 -0700
IronPort-SDR: 
 bIZ2xj+aw96+Sk1yGTWgbb5Ogmaor9oKaSj9duSyedbvH1saqltNxrA9rOPpS3/YmqrJibpRFZ
 nKVX7ZkXQj6w==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.77,410,1596524400";
   d="scan'208";a="354637310"
Received: from sjchrist-coffee.jf.intel.com ([10.54.74.160])
  by fmsmga002.fm.intel.com with ESMTP; 23 Oct 2020 20:11:59 -0700
From: Sean Christopherson <sean.j.christopherson@intel.com>
To: Paolo Bonzini <pbonzini@redhat.com>,
        Linus Torvalds <torvalds@linux-foundation.org>
Cc: Sean Christopherson <sean.j.christopherson@intel.com>,
 Vitaly Kuznetsov <vkuznets@redhat.com>, Wanpeng Li <wanpengli@tencent.com>,
 Jim Mattson <jmattson@google.com>, Joerg Roedel <joro@8bytes.org>,
 kvm@vger.kernel.org, linux-kernel@vger.kernel.org, =?utf-8?q?Daniel_D=C3=AD?=
	=?utf-8?q?az?= <daniel.diaz@linaro.org>
Subject: [PATCH] KVM: x86/mmu: Avoid modulo operator on 64-bit value to fix
 i386 build
Date: Fri, 23 Oct 2020 20:11:50 -0700
Message-Id: <20201024031150.9318-1-sean.j.christopherson@intel.com>
X-Mailer: git-send-email 2.28.0
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Replace a modulo operator with the more common pattern for computing the
gfn "offset" of a huge page to fix an i386 build error.

  arch/x86/kvm/mmu/tdp_mmu.c:212: undefined reference to `__umoddi3'

Fixes: 2f2fad0897cb ("kvm: x86/mmu: Add functions to handle changed TDP SPTEs")
Reported-by: Daniel Díaz <daniel.diaz@linaro.org>
Signed-off-by: Sean Christopherson <sean.j.christopherson@intel.com>
---

Linus, do you want to take this directly so that it's in rc1?  I don't
know whether Paolo will be checking mail before then.

 arch/x86/kvm/mmu/tdp_mmu.c | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
