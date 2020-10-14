

#### [PATCH 0/9] Remove irq_remapping_get_irq_domain()
##### From: David Woodhouse <dwmw2@infradead.org>

```c
From patchwork Tue Oct 13 08:11:30 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 8bit
X-Patchwork-Submitter: David Woodhouse <dwmw2@infradead.org>
X-Patchwork-Id: 11835175
Return-Path: <SRS0=tiWW=DU=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 8392B1592
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 13 Oct 2020 08:12:56 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 5B696207C3
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 13 Oct 2020 08:12:56 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=infradead.org header.i=@infradead.org
 header.b="I6ttXtQg"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2391315AbgJMIMm (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 13 Oct 2020 04:12:42 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:34086 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S2391113AbgJMIML (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 13 Oct 2020 04:12:11 -0400
Received: from casper.infradead.org (casper.infradead.org
 [IPv6:2001:8b0:10b:1236::1])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 11E0AC0613D0;
        Tue, 13 Oct 2020 01:12:08 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; q=dns/txt; c=relaxed/relaxed;
        d=infradead.org; s=casper.20170209;
 h=Sender:Content-Transfer-Encoding:
        Content-Type:MIME-Version:References:In-Reply-To:Message-Id:Date:Subject:Cc:
        To:From:Reply-To:Content-ID:Content-Description;
        bh=RgWc9nkynvcBFppQsEDwLqzLhZzcJ5woAloxK69DHIY=;
 b=I6ttXtQgUdffmuQ7izO5ZTJ+aR
        5Wk4Qq54h7x2WilXjyV4qwN72fxXZpRyMItZOj1qf3eB9+MvjcyWI5lvWlrGqymrsuZc+tGESrje1
        WlxrbcO455lesZYUd3Lu8CyyunuIbv4CbzoN7Ve9Lcoi9TV7oyUBR0mjsnnG6UFaoudzR2j2X8Au3
        t0jJJbMgIAgMvhzVVlVzHvsu5QjdfCB4Y/E1h4CNKXoG9Brv81RYmEwOzdzfQQ2gaEBWAEyX4urR/
        TvEiPUnTzM6Ol2B8GSbH8epMHYQpOnx2GOYoeU91aTGe6p4/41zlvxat5LVdgCEkmbNJiMPweczgK
        cVf0rsxA==;
Received: from i7.infradead.org ([2001:8b0:10b:1:21e:67ff:fecb:7a92])
        by casper.infradead.org with esmtpsa (Exim 4.92.3 #3 (Red Hat Linux))
        id 1kSFPM-0006fN-QR; Tue, 13 Oct 2020 08:12:01 +0000
Received: from dwoodhou by i7.infradead.org with local (Exim 4.93 #3 (Red Hat
 Linux))
        id 1kSFPM-006XXJ-BR; Tue, 13 Oct 2020 09:11:44 +0100
From: David Woodhouse <dwmw2@infradead.org>
To: x86@kernel.org
Cc: kvm <kvm@vger.kernel.org>, iommu@lists.linux-foundation.org,
        joro@8bytes.org, Thomas Gleixner <tglx@linutronix.de>,
        Paolo Bonzini <pbonzini@redhat.com>,
        linux-kernel <linux-kernel@vger.kernel.org>,
        linux-hyperv@vger.kernel.org, maz@misterjones.org
Subject: [PATCH 0/9] Remove irq_remapping_get_irq_domain()
Date: Tue, 13 Oct 2020 09:11:30 +0100
Message-Id: <20201013081139.1558200-1-dwmw2@infradead.org>
X-Mailer: git-send-email 2.26.2
In-Reply-To: <0de733f6384874d68afba2606119d0d9b1e8b34e.camel@infradead.org>
References: <0de733f6384874d68afba2606119d0d9b1e8b34e.camel@infradead.org>
MIME-Version: 1.0
Sender: David Woodhouse <dwmw2@infradead.org>
X-SRS-Rewrite: SMTP reverse-path rewritten from <dwmw2@infradead.org> by
 casper.infradead.org. See http://www.infradead.org/rpr.html
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

I didn't much like the I/OAPIC and HPET drivers having magical knowledge
that they had to substitute x86_vector_domain if their call to
irq_remapping_get_irq_domain() returned NULL.

When Thomas tried to make it handle error returns from …get_irq_domain() 
distinctly from the NULL case too, it made me even sadder. So I killed 
it with fire.

Now they just use irq_find_matching_fwspec() to find an appropriate
irqdomain. Each remapping irqdomain just needs to say 'yep, that's me'
for the HPETs or I/OAPICs which are within their scope, while the
x86_vector_domain accepts them all but only if interrupt remapping
is *disabled*. No more special knowledge in the caller.

If IR is enabled and there's a child device which escapes the scope of
all remapping units, it gets NULL for its parent irqdomain and will
fail to initialise, which is the correct thing to do in that "should
never happen" case. For HPET that'll mean that it just doesn't support
MSI, while I/OAPIC will refuse to initialise and trigger a BUG_ON
because Linux quite likes it when *all* the I/OAPICs it knows about get
initialised successfully.

This is on top of the previous 'ext_dest_id' series at
https://patchwork.kernel.org/project/kvm/list/?series=362037

https://git.infradead.org/users/dwmw2/linux.git/shortlog/refs/heads/ext_dest_id

David Woodhouse (9):
      genirq/irqdomain: Implement get_name() method on irqchip fwnodes
      x86/apic: Add select() method on vector irqdomain
      iommu/amd: Implement select() method on remapping irqdomain
      iommu/vt-d: Implement select() method on remapping irqdomain
      iommu/hyper-v: Implement select() method on remapping irqdomain
      x86/hpet: Use irq_find_matching_fwspec() to find remapping irqdomain
      x86/ioapic: Use irq_find_matching_fwspec() to find remapping irqdomain
      x86: Kill all traces of irq_remapping_get_irq_domain()
      iommu/vt-d: Simplify intel_irq_remapping_select()

 arch/x86/include/asm/hw_irq.h        |  2 --
 arch/x86/include/asm/irq_remapping.h |  9 ---------
 arch/x86/include/asm/irqdomain.h     |  3 +++
 arch/x86/kernel/apic/io_apic.c       | 24 ++++++++++++------------
 arch/x86/kernel/apic/vector.c        | 43 +++++++++++++++++++++++++++++++++++++++++++
 arch/x86/kernel/hpet.c               | 23 +++++++++++++----------
 drivers/iommu/amd/iommu.c            | 53 +++++++++++++++++++----------------------------------
 drivers/iommu/hyperv-iommu.c         | 18 +++++++++---------
 drivers/iommu/intel/irq_remapping.c  | 43 +++++++++++++++++--------------------------
 drivers/iommu/irq_remapping.c        | 14 --------------
 drivers/iommu/irq_remapping.h        |  3 ---
 kernel/irq/irqdomain.c               | 11 ++++++++++-
 12 files changed, 126 insertions(+), 120 deletions(-)
```
