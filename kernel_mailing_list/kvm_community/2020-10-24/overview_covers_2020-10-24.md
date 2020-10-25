

#### [PATCH v3 00/35] Fix x2apic enablement and allow more CPUs,
##### From: David Woodhouse <dwmw2@infradead.org>

```c
From patchwork Sat Oct 24 21:35:00 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 8bit
X-Patchwork-Submitter: David Woodhouse <dwmw2@infradead.org>
X-Patchwork-Id: 11855057
Return-Path: <SRS0=sCQZ=D7=vger.kernel.org=kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-6.8 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,MAILING_LIST_MULTI,
	SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT autolearn=no autolearn_force=no
	version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 0C8A8C56201
	for <kvm@archiver.kernel.org>; Sat, 24 Oct 2020 21:39:02 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id CAFFD22210
	for <kvm@archiver.kernel.org>; Sat, 24 Oct 2020 21:39:01 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=infradead.org header.i=@infradead.org
 header.b="3Zk5cnG6"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1765132AbgJXVjB (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Sat, 24 Oct 2020 17:39:01 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:33842 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1764667AbgJXVfp (ORCPT <rfc822;kvm@vger.kernel.org>);
        Sat, 24 Oct 2020 17:35:45 -0400
Received: from merlin.infradead.org (merlin.infradead.org
 [IPv6:2001:8b0:10b:1231::1])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 25DFEC0613D4;
        Sat, 24 Oct 2020 14:35:45 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; q=dns/txt; c=relaxed/relaxed;
        d=infradead.org; s=merlin.20170209;
 h=Sender:Content-Transfer-Encoding:
        Content-Type:MIME-Version:References:In-Reply-To:Message-Id:Date:Subject:Cc:
        To:From:Reply-To:Content-ID:Content-Description;
        bh=BB0rtOqqhF/O+4Eyi+jPOjXIPrc5yFSdnqnIg/CmQXM=;
 b=3Zk5cnG6/nm0qE6vEP5tNuuvKL
        FLwPSenwz6cySsnsI/i4ie8PSqyWUnjLgI25kG+98FxyD1nyee567XX7S6dwocmjdruxLkkMb3vYI
        GlvHkiy4hE1FgEAH14b0gaADbnRoQ+MJwuqcZjV38y6M7nSv6e1KIMPK7o/zwomzABdP/3RhvNnXy
        er4F+f9OPWoe3KlH4RPvBEtg/ZuvqR5CTUowY9JaUd0geghKIQTdIb7TTfbCz0WQ6KnhUXOVidmbX
        IxvTCcHaTCqSien6sc03PRyh/99ZBPUAgi5n1mDsu1aCdzAEdH0J+L62RbK/f+CAiM9vTLcWBGfQ1
        Zri9K4fQ==;
Received: from i7.infradead.org ([2001:8b0:10b:1:21e:67ff:fecb:7a92])
        by merlin.infradead.org with esmtpsa (Exim 4.92.3 #3 (Red Hat Linux))
        id 1kWRCO-0008B1-GY; Sat, 24 Oct 2020 21:35:40 +0000
Received: from dwoodhou by i7.infradead.org with local (Exim 4.93 #3 (Red Hat
 Linux))
        id 1kWRCM-001rNZ-IO; Sat, 24 Oct 2020 22:35:38 +0100
From: David Woodhouse <dwmw2@infradead.org>
To: x86@kernel.org
Cc: kvm <kvm@vger.kernel.org>, iommu@lists.linux-foundation.org,
        joro@8bytes.org, Thomas Gleixner <tglx@linutronix.de>,
        Paolo Bonzini <pbonzini@redhat.com>,
        linux-kernel <linux-kernel@vger.kernel.org>,
        linux-hyperv@vger.kernel.org, maz@misterjones.org,
        Dexuan Cui <decui@microsoft.com>
Subject: [PATCH v3 00/35] Fix x2apic enablement and allow more CPUs,
 clean up I/OAPIC and MSI bitfields
Date: Sat, 24 Oct 2020 22:35:00 +0100
Message-Id: <20201024213535.443185-1-dwmw2@infradead.org>
X-Mailer: git-send-email 2.26.2
In-Reply-To: <e6601ff691afb3266e365a91e8b221179daf22c2.camel@infradead.org>
References: <e6601ff691afb3266e365a91e8b221179daf22c2.camel@infradead.org>
MIME-Version: 1.0
Sender: David Woodhouse <dwmw2@infradead.org>
X-SRS-Rewrite: SMTP reverse-path rewritten from <dwmw2@infradead.org> by
 merlin.infradead.org. See http://www.infradead.org/rpr.html
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Fix the conditions for enabling x2apic on guests without interrupt 
remapping, and support 15-bit Extended Destination ID to allow 32768 
CPUs without IR on hypervisors that support it.

Make the I/OAPIC code generate its RTE directly from the MSI message
created by the parent irqchip, and fix up a bunch of magic mask/shift
macros to use bitfields for MSI messages and I/OAPIC RTEs while we're
at it.

v3:
 • Lots of bitfield cleanups from Thomas.
 • Disable hyperv-iommu if 15-bit extension is present.
 • Fix inconsistent CONFIG_PCI_MSI/CONFIG_GENERIC_MSI_IRQ in hpet.c
 • Split KVM_FEATURE_MSI_EXT_DEST_ID patch, half of which is going upstream
   through KVM tree (and the other half needs to wait, or have an #ifdef) so
   is left at the top of the tree.

v2:
 • Minor cleanups.
 • Move __irq_msi_compose_msg() to apic.c, make virt_ext_dest_id static.
 • Generate I/OAPIC RTE directly from parent irqchip's MSI messages.
 • Clean up HPET MSI support into hpet.c now that we can.

David Woodhouse (19):
      x86/apic: Fix x2apic enablement without interrupt remapping
      x86/msi: Only use high bits of MSI address for DMAR unit
      x86/apic: Always provide irq_compose_msi_msg() method for vector domain
      x86/hpet: Move MSI support into hpet.c
      x86/ioapic: Generate RTE directly from parent irqchip's MSI message
      genirq/irqdomain: Implement get_name() method on irqchip fwnodes
      x86/apic: Add select() method on vector irqdomain
      iommu/amd: Implement select() method on remapping irqdomain
      iommu/vt-d: Implement select() method on remapping irqdomain
      iommu/hyper-v: Implement select() method on remapping irqdomain
      x86/hpet: Use irq_find_matching_fwspec() to find remapping irqdomain
      x86/ioapic: Use irq_find_matching_fwspec() to find remapping irqdomain
      x86: Kill all traces of irq_remapping_get_irq_domain()
      iommu/vt-d: Simplify intel_irq_remapping_select()
      x86/ioapic: Handle Extended Destination ID field in RTE
      x86/apic: Support 15 bits of APIC ID in MSI where available
      iommu/hyper-v: Disable IRQ pseudo-remapping if 15 bit APIC IDs are available
      x86/kvm: Reserve KVM_FEATURE_MSI_EXT_DEST_ID
      x86/kvm: Enable 15-bit extension when KVM_FEATURE_MSI_EXT_DEST_ID detected

Thomas Gleixner (16):
      x86/apic/uv: Fix inconsistent destination mode
      x86/devicetree: Fix the ioapic interrupt type table
      x86/apic: Cleanup delivery mode defines
      x86/apic: Replace pointless apic::dest_logical usage
      x86/apic: Get rid of apic::dest_logical
      x86/apic: Cleanup destination mode
      genirq/msi: Allow shadow declarations of msi_msg::$member
      x86/msi: Provide msi message shadow structs
      iommu/intel: Use msi_msg shadow structs
      iommu/amd: Use msi_msg shadow structs
      PCI: vmd: Use msi_msg shadow structs
      x86/kvm: Use msi_msg shadow structs
      x86/pci/xen: Use msi_msg shadow structs
      x86/msi: Remove msidef.h
      x86/io_apic: Cleanup trigger/polarity helpers
      x86/ioapic: Cleanup IO/APIC route entry structs

 Documentation/virt/kvm/cpuid.rst      |   4 +
 arch/x86/include/asm/apic.h           |  16 +-
 arch/x86/include/asm/apicdef.h        |  16 +-
 arch/x86/include/asm/hpet.h           |  11 -
 arch/x86/include/asm/hw_irq.h         |  13 +-
 arch/x86/include/asm/io_apic.h        |  79 ++----
 arch/x86/include/asm/irq_remapping.h  |   9 -
 arch/x86/include/asm/irqdomain.h      |   3 +
 arch/x86/include/asm/msi.h            |  50 ++++
 arch/x86/include/asm/msidef.h         |  57 ----
 arch/x86/include/asm/x86_init.h       |   2 +
 arch/x86/include/uapi/asm/kvm_para.h  |   1 +
 arch/x86/kernel/apic/apic.c           |  73 ++++-
 arch/x86/kernel/apic/apic_flat_64.c   |  18 +-
 arch/x86/kernel/apic/apic_noop.c      |  10 +-
 arch/x86/kernel/apic/apic_numachip.c  |  16 +-
 arch/x86/kernel/apic/bigsmp_32.c      |   9 +-
 arch/x86/kernel/apic/io_apic.c        | 503 ++++++++++++++++++----------------
 arch/x86/kernel/apic/ipi.c            |   6 +-
 arch/x86/kernel/apic/msi.c            | 153 +----------
 arch/x86/kernel/apic/probe_32.c       |   9 +-
 arch/x86/kernel/apic/vector.c         |  49 ++++
 arch/x86/kernel/apic/x2apic_cluster.c |  10 +-
 arch/x86/kernel/apic/x2apic_phys.c    |  17 +-
 arch/x86/kernel/apic/x2apic_uv_x.c    |  12 +-
 arch/x86/kernel/devicetree.c          |  30 +-
 arch/x86/kernel/hpet.c                | 122 ++++++++-
 arch/x86/kernel/kvm.c                 |   6 +
 arch/x86/kernel/smpboot.c             |   8 +-
 arch/x86/kernel/x86_init.c            |   1 +
 arch/x86/kvm/irq_comm.c               |  31 +--
 arch/x86/pci/intel_mid_pci.c          |   8 +-
 arch/x86/pci/xen.c                    |  26 +-
 arch/x86/platform/uv/uv_irq.c         |   4 +-
 arch/x86/xen/apic.c                   |   7 +-
 drivers/iommu/amd/amd_iommu_types.h   |   2 +-
 drivers/iommu/amd/init.c              |  46 ++--
 drivers/iommu/amd/iommu.c             |  93 +++----
 drivers/iommu/hyperv-iommu.c          |  44 +--
 drivers/iommu/intel/irq_remapping.c   | 102 +++----
 drivers/iommu/irq_remapping.c         |  14 -
 drivers/iommu/irq_remapping.h         |   3 -
 drivers/pci/controller/pci-hyperv.c   |   6 +-
 drivers/pci/controller/vmd.c          |   9 +-
 include/asm-generic/msi.h             |   4 +
 include/linux/msi.h                   |  46 +++-
 kernel/irq/irqdomain.c                |  11 +-
 47 files changed, 890 insertions(+), 879 deletions(-)
```
