

#### [PATCH 0/3] SELinux support for anonymous inodes and UFFD
##### From: Daniel Colascione <dancol@google.com>

```c
From patchwork Fri Feb 14 03:26:32 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Daniel Colascione <dancol@google.com>
X-Patchwork-Id: 11381607
Return-Path: <SRS0=AN0r=4C=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 67BD6139A
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 14 Feb 2020 03:27:01 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 472B92168B
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 14 Feb 2020 03:27:01 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=google.com header.i=@google.com
 header.b="d7u2Fkhw"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728550AbgBND06 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 13 Feb 2020 22:26:58 -0500
Received: from mail-pl1-f201.google.com ([209.85.214.201]:50691 "EHLO
        mail-pl1-f201.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1728089AbgBND05 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 13 Feb 2020 22:26:57 -0500
Received: by mail-pl1-f201.google.com with SMTP id g5so4365854plq.17
        for <kvm@vger.kernel.org>; Thu, 13 Feb 2020 19:26:56 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=date:in-reply-to:message-id:mime-version:references:subject:from:to
         :cc;
        bh=0WYp+nOc4W1ueTL6njcvhwE6Wrya56t+7LdjPX2+2/g=;
        b=d7u2FkhwK0FN7IXYD8paZmQSKyhKm96rk0yh6wSPXStrq+ZyUe0RBJ0cSR/kkVrTZ7
         yyAcca7EmJ6rSMeEPPDmRMQPnPyEsl8d+DvxOEmq0DTwgrwmiGE7SqOajaQIzDeOuqcf
         Dup93fAzq0KZymXZwZ+fiEXw7p7pZvYsz9Sd3yWE6XW47saWou3JDaduJwLGhI/6aCvr
         jXEAo8CTJA5tMyHfa2LpOlraU1cl+g4iI3Mmkp15BOF9zeBzfcEkhcK1YsPI+ryUiGy1
         60g7n05mvI2V1MgGUXg5cFf4vvol75AtiWxiV1xP9EDlQm2jLHIy74/BgTZiK6/Tk6+T
         /DFg==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:date:in-reply-to:message-id:mime-version
         :references:subject:from:to:cc;
        bh=0WYp+nOc4W1ueTL6njcvhwE6Wrya56t+7LdjPX2+2/g=;
        b=aOEWBh1LKQqmnv7ChyFfFpfnwSatIRLQ2id8KZctzT1MbzaNv0PiSV/9+NRkS249DE
         1zzhxQBf0+sW3CTUntZ9fj5K8QiSjyGnWLo4Hh6STq1aGzLBiTyGBpx4zuZ9Jq7m7CvR
         1CXzT6BXNliJm99vTq+Y4HZ12zEdEBqjqMNkPeo0y9da3nXZJ+yz6+jRBPhIRyhp1Jkh
         LfuMQSZjEpXL+0MMg/V+8nE+cvVxHC+3Srmt6Ls+TA6VZa+u/CKPRTvlJmALR6aALbp/
         mgrIiIIGOg0hpvV0JkR1xmDOu1niyunupjoZCGOS1kmnbDmS/Xnh0JcszK6oyitucW8X
         fDfA==
X-Gm-Message-State: APjAAAXyywJUuyLVXF+vNo2BAI65VwbuTxxAQURmNYzBYXTsCO5oJq8X
        wZOgKHZKOh8AcwIClLwfK3DABXYZLSw=
X-Google-Smtp-Source: 
 APXvYqycI2BpuraXCc3IrQ2spptnq0wpysgGaSnKRL3VQeWA2X/FZ9eFhD8j0BwJp3nlWxw33egBUz7gUsU=
X-Received: by 2002:a63:5a11:: with SMTP id o17mr1256158pgb.60.1581650815604;
 Thu, 13 Feb 2020 19:26:55 -0800 (PST)
Date: Thu, 13 Feb 2020 19:26:32 -0800
In-Reply-To: <20200211225547.235083-1-dancol@google.com>
Message-Id: <20200214032635.75434-1-dancol@google.com>
Mime-Version: 1.0
References: <20200211225547.235083-1-dancol@google.com>
X-Mailer: git-send-email 2.25.0.265.gbab2e86ba0-goog
Subject: [PATCH 0/3] SELinux support for anonymous inodes and UFFD
From: Daniel Colascione <dancol@google.com>
To: timmurray@google.com, selinux@vger.kernel.org,
        linux-security-module@vger.kernel.org,
        linux-fsdevel@vger.kernel.org, linux-kernel@vger.kernel.org,
        kvm@vger.kernel.org, viro@zeniv.linux.org.uk, paul@paul-moore.com,
        nnk@google.com, sds@tycho.nsa.gov, lokeshgidra@google.com
Cc: Daniel Colascione <dancol@google.com>
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Userfaultfd in unprivileged contexts could be potentially very
useful. We'd like to harden userfaultfd to make such unprivileged use
less risky. This patch series allows SELinux to manage userfaultfd
file descriptors and in the future, other kinds of
anonymous-inode-based file descriptor.  SELinux policy authors can
apply policy types to anonymous inodes by providing name-based
transition rules keyed off the anonymous inode internal name (
"[userfaultfd]" in the case of userfaultfd(2) file descriptors) and
applying policy to the new SIDs thus produced.

Inside the kernel, a pair of new anon_inodes interface,
anon_inode_getfile_secure and anon_inode_getfd_secure, allow callers
to opt into this SELinux management. In this new "secure" mode,
anon_inodes creates new ephemeral inodes for anonymous file objects
instead of reusing the normal anon_inodes singleton dummy inode. A new
LSM hook gives security modules an opportunity to configure and veto
these ephemeral inodes.

This patch series is one of two fork of [1] and is an
alternative to [2].

The primary difference between the two patch series is that this
partch series creates a unique inode for each "secure" anonymous
inode, while the other patch series ([2]) continues using the
singleton dummy anonymous inode and adds a way to attach SELinux
security information directly to file objects.

I prefer the approach in this patch series because 1) it's a smaller
patch than [2], and 2) it produces a more regular security
architecture: in this patch series, secure anonymous inodes aren't
S_PRIVATE and they maintain the SELinux property that the label for a
file is in its inode. We do need an additional inode per anonymous
file, but per-struct-file inode creation doesn't seem to be a problem
for pipes and sockets.

The previous version of this feature ([1]) created a new SELinux
security class for userfaultfd file descriptors. This version adopts
the generic transition-based approach of [2].

This patch series also differs from [2] in that it doesn't affect all
anonymous inodes right away --- instead requiring anon_inodes callers
to opt in --- but this difference isn't one of basic approach. The
important question to resolve is whether we should be creating new
inodes or enhancing per-file data.

[1] https://lore.kernel.org/lkml/20200211225547.235083-1-dancol@google.com/
[2] https://lore.kernel.org/linux-fsdevel/20200213194157.5877-1-sds@tycho.nsa.gov/

Daniel Colascione (3):
  Add a new LSM-supporting anonymous inode interface
  Teach SELinux about anonymous inodes
  Wire UFFD up to SELinux

 fs/anon_inodes.c            | 196 ++++++++++++++++++++++++++++--------
 fs/userfaultfd.c            |  34 +++++--
 include/linux/anon_inodes.h |  13 +++
 include/linux/lsm_hooks.h   |   9 ++
 include/linux/security.h    |   4 +
 security/security.c         |  10 ++
 security/selinux/hooks.c    |  57 +++++++++++
 7 files changed, 274 insertions(+), 49 deletions(-)
```
#### [PATCH v4 00/20] irqchip/gic-v4: GICv4.1 architecture support
##### From: Marc Zyngier <maz@kernel.org>
X-SA-Exim-Mail-From: maz@kernel.org

```c
From patchwork Fri Feb 14 14:57:16 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Marc Zyngier <maz@kernel.org>
X-Patchwork-Id: 11382383
Return-Path: <SRS0=AN0r=4C=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 21390109A
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 14 Feb 2020 14:58:31 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id EB78324654
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 14 Feb 2020 14:58:30 +0000 (UTC)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple; d=kernel.org;
	s=default; t=1581692311;
	bh=2K+sV3mhy23v6Bq9vMnU/WU2vw9ePyOV5iKw3thp48A=;
	h=From:To:Cc:Subject:Date:List-ID:From;
	b=MruzVLMC7d+vTH7tlhe3z2d1lDsh6uezU94hnf9OpGZPzAPR41WBkO7RthrTaNp7t
	 UIUChjiI9Lw6a1ByTtQ9xiCIvWaqhLHVqU7m5wVmQbKoYGZ47BGes+IP83NC+0nokf
	 HJWMjnEZ6FUtFX78Gknn2z9cdiIXAyEcfeL7pt8E=
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729439AbgBNO5s (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 14 Feb 2020 09:57:48 -0500
Received: from mail.kernel.org ([198.145.29.99]:50952 "EHLO mail.kernel.org"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1729241AbgBNO5s (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 14 Feb 2020 09:57:48 -0500
Received: from disco-boy.misterjones.org (disco-boy.misterjones.org
 [51.254.78.96])
        (using TLSv1.2 with cipher ECDHE-RSA-AES256-GCM-SHA384 (256/256 bits))
        (No client certificate requested)
        by mail.kernel.org (Postfix) with ESMTPSA id D481624654;
        Fri, 14 Feb 2020 14:57:46 +0000 (UTC)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple; d=kernel.org;
        s=default; t=1581692267;
        bh=2K+sV3mhy23v6Bq9vMnU/WU2vw9ePyOV5iKw3thp48A=;
        h=From:To:Cc:Subject:Date:From;
        b=rrFRAEx5RHOLyG1IgXafbX5FY6M1AdYoSrNOgU8IwpdqmGbiscDh7atSMJsDh8WzL
         JZEopblx7bJMnlcoH30Rfvi2E98soWbCyeFlNn+9iP2VJpmbWtrnq2gELYUpP68JpL
         9gLR0sHW3tSThQ+gtPaV+IqGvCdjy+I2aH/8/Cj0=
Received: from 78.163-31-62.static.virginmediabusiness.co.uk ([62.31.163.78]
 helo=why.lan)
        by disco-boy.misterjones.org with esmtpsa
 (TLS1.3:ECDHE_RSA_AES_256_GCM_SHA384:256)
        (Exim 4.92)
        (envelope-from <maz@kernel.org>)
        id 1j2cPZ-0057sw-7b; Fri, 14 Feb 2020 14:57:45 +0000
From: Marc Zyngier <maz@kernel.org>
To: linux-arm-kernel@lists.infradead.org, kvmarm@lists.cs.columbia.edu,
        kvm@vger.kernel.org, linux-kernel@vger.kernel.org
Cc: Lorenzo Pieralisi <lorenzo.pieralisi@arm.com>,
        Jason Cooper <jason@lakedaemon.net>,
        Robert Richter <rrichter@marvell.com>,
        Thomas Gleixner <tglx@linutronix.de>,
        Zenghui Yu <yuzenghui@huawei.com>,
        Eric Auger <eric.auger@redhat.com>,
        James Morse <james.morse@arm.com>,
        Julien Thierry <julien.thierry.kdev@gmail.com>,
        Suzuki K Poulose <suzuki.poulose@arm.com>
Subject: [PATCH v4 00/20] irqchip/gic-v4: GICv4.1 architecture support
Date: Fri, 14 Feb 2020 14:57:16 +0000
Message-Id: <20200214145736.18550-1-maz@kernel.org>
X-Mailer: git-send-email 2.20.1
MIME-Version: 1.0
X-SA-Exim-Connect-IP: 62.31.163.78
X-SA-Exim-Rcpt-To: linux-arm-kernel@lists.infradead.org,
 kvmarm@lists.cs.columbia.edu, kvm@vger.kernel.org,
 linux-kernel@vger.kernel.org, lorenzo.pieralisi@arm.com,
 jason@lakedaemon.net, rrichter@marvell.com, tglx@linutronix.de,
 yuzenghui@huawei.com, eric.auger@redhat.com, james.morse@arm.com,
 julien.thierry.kdev@gmail.com, suzuki.poulose@arm.com
X-SA-Exim-Mail-From: maz@kernel.org
X-SA-Exim-Scanned: No (on disco-boy.misterjones.org);
 SAEximRunCond expanded to false
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This (now shorter) series expands the existing GICv4 support to deal
with the new GICv4.1 architecture, which comes with a set of major
improvements compared to v4.0:

- One architectural doorbell per vcpu, instead of one doorbell per VLPI

- Doorbell entirely managed by the HW, with an "at most once" delivery
  guarantee per non-residency phase and only when requested by the
  hypervisor

- A shared memory scheme between ITSs and redistributors, allowing for an
  optimised residency sequence (the use of VMOVP becomes less frequent)

- Support for direct virtual SGI delivery (the injection path still involves
  the hypervisor), at the cost of losing the active state on SGIs. It
  shouldn't be a big deal, but some guest operating systems might notice
  (Linux definitely won't care).

On the other hand, public documentation is not available yet, so that's a
bit annoying...

The series is roughly organised in 3 parts:

(1) v4.1 doorbell management
(2) Virtual SGI support
(3) Plumbing of virtual SGIs in KVM

Notes:

  - The whole thing is tested on a FVP model, which can be obtained
    free of charge on ARM's developer website. It requires you to
    create an account, unfortunately... You'll need a fix for the
    devicetree that is in the kernel tree (should be merged before
    the 5.6 release).

  - This series has uncovered a behaviour that looks like a HW bug on
    the Cavium ThunderX (aka TX1) platform. I'd very much welcome some
    clarification from the Marvell/Cavium folks on Cc, as well as an
    official erratum number if this happens to be an actual bug.

    [v3 update]
    People have ignored for two months now, and it is fairly obvious
    that support for this machine is slowly bit-rotting. Maybe I'll
    drop the patch and instead start the process of removing all TX1
    support from the kernel (we'd certainly be better off without it).

    [v4 update]
    TX1 is now broken in mainline, and nobody cares. Make of this what
    you want.

* From v3 [3]:
  - Rebased on v5.6-rc1
  - Considerably smaller thanks to the initial patches being merged
  - Small bug fix after the v5.6 merge window

* From v2 [2]:
  - Another bunch of fixes thanks to Zenghui Yu's very careful review
  - HW-accelerated SGIs are now optional thanks to new architected
    discovery/selection bits exposed by KVM and used by the guest kernel
  - Rebased on v5.5-rc2

* From v1 [1]:
  - A bunch of minor reworks after Zenghui Yu's review
  - A workaround for what looks like a new and unexpected TX1 bug
  - A subtle reorder of the series so that some patches can go in early

[1] https://lore.kernel.org/lkml/20190923182606.32100-1-maz@kernel.org/
[2] https://lore.kernel.org/lkml/20191027144234.8395-1-maz@kernel.org/
[3] https://lore.kernel.org/r/20191224111055.11836-1-maz@kernel.org/

Marc Zyngier (20):
  irqchip/gic-v4.1: Skip absent CPUs while iterating over redistributors
  irqchip/gic-v3: Use SGIs without active state if offered
  irqchip/gic-v4.1: Advertise support v4.1 to KVM
  irqchip/gic-v4.1: Map the ITS SGIR register page
  irqchip/gic-v4.1: Plumb skeletal VSGI irqchip
  irqchip/gic-v4.1: Add initial SGI configuration
  irqchip/gic-v4.1: Plumb mask/unmask SGI callbacks
  irqchip/gic-v4.1: Plumb get/set_irqchip_state SGI callbacks
  irqchip/gic-v4.1: Plumb set_vcpu_affinity SGI callbacks
  irqchip/gic-v4.1: Move doorbell management to the GICv4 abstraction
    layer
  irqchip/gic-v4.1: Add VSGI allocation/teardown
  irqchip/gic-v4.1: Add VSGI property setup
  irqchip/gic-v4.1: Eagerly vmap vPEs
  KVM: arm64: GICv4.1: Let doorbells be auto-enabled
  KVM: arm64: GICv4.1: Add direct injection capability to SGI registers
  KVM: arm64: GICv4.1: Allow SGIs to switch between HW and SW interrupts
  KVM: arm64: GICv4.1: Plumb SGI implementation selection in the
    distributor
  KVM: arm64: GICv4.1: Reload VLPI configuration on distributor
    enable/disable
  KVM: arm64: GICv4.1: Allow non-trapping WFI when using HW SGIs
  KVM: arm64: GICv4.1: Expose HW-based SGIs in debugfs

 arch/arm/include/asm/kvm_host.h        |   1 +
 arch/arm64/include/asm/kvm_emulate.h   |   3 +-
 arch/arm64/include/asm/kvm_host.h      |   1 +
 drivers/irqchip/irq-gic-v3-its.c       | 301 ++++++++++++++++++++++++-
 drivers/irqchip/irq-gic-v3.c           |  12 +-
 drivers/irqchip/irq-gic-v4.c           | 134 ++++++++++-
 include/kvm/arm_vgic.h                 |   4 +
 include/linux/irqchip/arm-gic-common.h |   2 +
 include/linux/irqchip/arm-gic-v3.h     |  19 +-
 include/linux/irqchip/arm-gic-v4.h     |  20 +-
 virt/kvm/arm/arm.c                     |   8 +
 virt/kvm/arm/vgic/vgic-debug.c         |  14 +-
 virt/kvm/arm/vgic/vgic-mmio-v3.c       |  68 +++++-
 virt/kvm/arm/vgic/vgic-mmio.c          |  88 +++++++-
 virt/kvm/arm/vgic/vgic-v3.c            |   6 +-
 virt/kvm/arm/vgic/vgic-v4.c            | 139 ++++++++++--
 virt/kvm/arm/vgic/vgic.h               |   1 +
 17 files changed, 763 insertions(+), 58 deletions(-)
```
#### [PATCH 00/13] KVM: selftests: Various fixes and cleanups
##### From: Andrew Jones <drjones@redhat.com>

```c
From patchwork Fri Feb 14 14:59:07 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Andrew Jones <drjones@redhat.com>
X-Patchwork-Id: 11382399
Return-Path: <SRS0=AN0r=4C=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 9B392109A
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 14 Feb 2020 14:59:31 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 7A4C524654
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 14 Feb 2020 14:59:31 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="JAGZr0xT"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2387409AbgBNO7a (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 14 Feb 2020 09:59:30 -0500
Received: from us-smtp-delivery-1.mimecast.com ([205.139.110.120]:43052 "EHLO
        us-smtp-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org
        with ESMTP id S1729475AbgBNO7a (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 14 Feb 2020 09:59:30 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1581692369;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=Q8mBykA1ZCQGjZjERbWNXzyTekBEukYGYJt2eGuJVbA=;
        b=JAGZr0xTnxx3sFEBYNXUfvqQXDlgSpgLjZ1cdyysrxtBm6FRBSb9kwyrFjDMm7B2r1s2RS
        noDNcxD+IliPlR7bX/oOGMUIeP9BZVkDp1EprvlHN6C5x8JrsMVeudC5kzkKAeObzALAVV
        yhoO5/6I1TPpPun3GCPu+kS1odqmisI=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-212-LK8OgRnePEKLOmp8raSWaw-1; Fri, 14 Feb 2020 09:59:27 -0500
X-MC-Unique: LK8OgRnePEKLOmp8raSWaw-1
Received: from smtp.corp.redhat.com (int-mx01.intmail.prod.int.phx2.redhat.com
 [10.5.11.11])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 24D81A0CBF;
        Fri, 14 Feb 2020 14:59:26 +0000 (UTC)
Received: from kamzik.brq.redhat.com (unknown [10.43.2.160])
        by smtp.corp.redhat.com (Postfix) with ESMTP id ECDA419E9C;
        Fri, 14 Feb 2020 14:59:21 +0000 (UTC)
From: Andrew Jones <drjones@redhat.com>
To: kvm@vger.kernel.org
Cc: pbonzini@redhat.com, bgardon@google.com, borntraeger@de.ibm.com,
        frankja@linux.ibm.com, thuth@redhat.com, peterx@redhat.com
Subject: [PATCH 00/13] KVM: selftests: Various fixes and cleanups
Date: Fri, 14 Feb 2020 15:59:07 +0100
Message-Id: <20200214145920.30792-1-drjones@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.11
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This series has several parts:

 * First, a hack to get x86 to compile. The missing __NR_userfaultfd
   define should be fixed a better way.

 * Then, fixups for several commits in kvm/queue. These fixups correspond
   to review comments that didn't have a chance to get addressed before
   the commits were applied.

 * Next, a few unnecessary #define/#ifdef deletions.

 * Then, a rework of debug and info message printing.

 * Finally, an addition to the API, num-pages conversion utilities,
   which cleans up all the num-pages calculations.


Andrew Jones (13):
  HACK: Ensure __NR_userfaultfd is defined
  fixup! KVM: selftests: Add support for vcpu_args_set to aarch64 and
    s390x
  fixup! KVM: selftests: Support multiple vCPUs in demand paging test
  fixup! KVM: selftests: Add memory size parameter to the demand paging
    test
  fixup! KVM: selftests: Time guest demand paging
  KVM: selftests: Remove unnecessary defines
  KVM: selftests: aarch64: Remove unnecessary ifdefs
  KVM: selftests: aarch64: Use stream when given
  KVM: selftests: Rework debug message printing
  KVM: selftests: Convert some printf's to pr_info's
  KVM: selftests: Rename vm_guest_mode_params
  KVM: selftests: Introduce vm_guest_mode_params
  KVM: selftests: Introduce num-pages conversion utilities

 .../selftests/kvm/demand_paging_test.c        | 148 ++++++++----------
 tools/testing/selftests/kvm/dirty_log_test.c  |  78 +++++----
 .../testing/selftests/kvm/include/kvm_util.h  |  14 +-
 .../testing/selftests/kvm/include/test_util.h |  18 +++
 .../selftests/kvm/kvm_create_max_vcpus.c      |   8 +-
 .../selftests/kvm/lib/aarch64/processor.c     |  30 +---
 tools/testing/selftests/kvm/lib/kvm_util.c    |  89 +++++++----
 .../selftests/kvm/lib/kvm_util_internal.h     |  11 --
 tools/testing/selftests/kvm/lib/test_util.c   |  90 ++++++-----
 tools/testing/selftests/kvm/s390x/resets.c    |   6 +-
 .../selftests/kvm/x86_64/mmio_warning_test.c  |   2 +-
 tools/testing/selftests/kvm/x86_64/smm_test.c |   2 +-
 .../testing/selftests/kvm/x86_64/state_test.c |   2 +-
 .../kvm/x86_64/vmx_tsc_adjust_test.c          |   4 +-
 .../selftests/kvm/x86_64/xss_msr_test.c       |   2 +-
 15 files changed, 258 insertions(+), 246 deletions(-)
```
#### [PATCH 0/2] KVM: arm64: Filtering PMU events
##### From: Marc Zyngier <maz@kernel.org>
X-SA-Exim-Mail-From: maz@kernel.org

```c
From patchwork Fri Feb 14 18:36:13 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Marc Zyngier <maz@kernel.org>
X-Patchwork-Id: 11382979
Return-Path: <SRS0=AN0r=4C=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 3839E159A
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 14 Feb 2020 18:36:32 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 16CC124650
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 14 Feb 2020 18:36:31 +0000 (UTC)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple; d=kernel.org;
	s=default; t=1581705392;
	bh=T+ilQI9wpmnmJVmL5LiaSl2V8wIK4X9cI78O+ANnNOE=;
	h=From:To:Cc:Subject:Date:List-ID:From;
	b=odgWRLYle70my7LJeMa5nZ/L48ZYoyX+dcrzZ1WMwmuEpDngyuP4YBFmfLTu/y/Zd
	 EGowMCAagOcBdY5CP0U0e+ZINkwbif8V0v83Mkak9J9Ysdt++8JKtKX3M4DJef3rzU
	 86hhZ7OMxXYRSXvSWr7xFBWZEIGMzyuweuKcPm6M=
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729760AbgBNSgb (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 14 Feb 2020 13:36:31 -0500
Received: from mail.kernel.org ([198.145.29.99]:37376 "EHLO mail.kernel.org"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1728239AbgBNSga (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 14 Feb 2020 13:36:30 -0500
Received: from disco-boy.misterjones.org (disco-boy.misterjones.org
 [51.254.78.96])
        (using TLSv1.2 with cipher ECDHE-RSA-AES256-GCM-SHA384 (256/256 bits))
        (No client certificate requested)
        by mail.kernel.org (Postfix) with ESMTPSA id BEBCD20848;
        Fri, 14 Feb 2020 18:36:29 +0000 (UTC)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple; d=kernel.org;
        s=default; t=1581705389;
        bh=T+ilQI9wpmnmJVmL5LiaSl2V8wIK4X9cI78O+ANnNOE=;
        h=From:To:Cc:Subject:Date:From;
        b=IlBTVTsHr/G7gWRjLL220TV6NPEbmZBkt9QuKo/4Rpgju5AedYJhyRse2UusxxeJZ
         zzQOay2oAzn6jKo984xRFeUNONIWdX8k3ofL0/Ht5Z6qAuuwpqXhUf2Vr9Bvb8Mum0
         iOe4t7QGTnK4VAYcCWHOKefn2AH6GdhFEEE6YaWo=
Received: from 78.163-31-62.static.virginmediabusiness.co.uk ([62.31.163.78]
 helo=why.lan)
        by disco-boy.misterjones.org with esmtpsa
 (TLS1.3:ECDHE_RSA_AES_256_GCM_SHA384:256)
        (Exim 4.92)
        (envelope-from <maz@kernel.org>)
        id 1j2fpE-005J5c-2m; Fri, 14 Feb 2020 18:36:28 +0000
From: Marc Zyngier <maz@kernel.org>
To: linux-arm-kernel@lists.infradead.org, kvmarm@lists.cs.columbia.edu,
        kvm@vger.kernel.org
Cc: James Morse <james.morse@arm.com>,
        Julien Thierry <julien.thierry.kdev@gmail.com>,
        Suzuki K Poulose <suzuki.poulose@arm.com>
Subject: [PATCH 0/2] KVM: arm64: Filtering PMU events
Date: Fri, 14 Feb 2020 18:36:13 +0000
Message-Id: <20200214183615.25498-1-maz@kernel.org>
X-Mailer: git-send-email 2.20.1
MIME-Version: 1.0
X-SA-Exim-Connect-IP: 62.31.163.78
X-SA-Exim-Rcpt-To: linux-arm-kernel@lists.infradead.org,
 kvmarm@lists.cs.columbia.edu, kvm@vger.kernel.org, james.morse@arm.com,
 julien.thierry.kdev@gmail.com, suzuki.poulose@arm.com
X-SA-Exim-Mail-From: maz@kernel.org
X-SA-Exim-Scanned: No (on disco-boy.misterjones.org);
 SAEximRunCond expanded to false
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

It is at times necessary to prevent a guest from being able to sample
certain events if multiple CPUs share resources such as a cache level.
In this case, it would be interesting if the VMM could simply prevent
certain events from being counted instead of simply not exposing a PMU.

Given that most events are not architected, there is no easy way
to designate which events shouldn't be counted other than specifying
the raw event number.

Since I have no idea whether it is better to use an event whitelist
or blacklist, the proposed API takes a cue from the x86 version and
allows either allowing or denying counting of ranges of events.
The event space being pretty large (16bits on ARMv8.1), the default
policy is set by the first filter that gets installed (default deny if
we first allow, default allow if we first deny).

The filter state is global to the guest, despite the PMU being per
CPU. I'm not sure whether it would be worth it making it CPU-private.

Anyway, I'd be interesting in comments on how people would use this.
I'll try to push a patch against kvmtool that implement this shortly
(what I have currently is a harcoded set of hacks).

Marc Zyngier (2):
  KVM: arm64: Add PMU event filtering infrastructure
  KVM: arm64: Document PMU filtering API

 Documentation/virt/kvm/devices/vcpu.txt | 28 +++++++++
 arch/arm64/include/asm/kvm_host.h       |  6 ++
 arch/arm64/include/uapi/asm/kvm.h       | 16 ++++++
 virt/kvm/arm/arm.c                      |  2 +
 virt/kvm/arm/pmu.c                      | 76 +++++++++++++++++++++----
 5 files changed, 116 insertions(+), 12 deletions(-)
```
#### [PATCH v2 00/42] KVM: s390: Add support for protected VMs
##### From: Christian Borntraeger <borntraeger@de.ibm.com>

```c
From patchwork Fri Feb 14 22:26:16 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Christian Borntraeger <borntraeger@de.ibm.com>
X-Patchwork-Id: 11383335
Return-Path: <SRS0=AN0r=4C=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 66C4E186E
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 14 Feb 2020 22:27:14 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 45E892082F
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 14 Feb 2020 22:27:14 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727798AbgBNW1N (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 14 Feb 2020 17:27:13 -0500
Received: from mx0a-001b2d01.pphosted.com ([148.163.156.1]:50894 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1727620AbgBNW1M (ORCPT
        <rfc822;kvm@vger.kernel.org>); Fri, 14 Feb 2020 17:27:12 -0500
Received: from pps.filterd (m0098410.ppops.net [127.0.0.1])
        by mx0a-001b2d01.pphosted.com (8.16.0.42/8.16.0.42) with SMTP id
 01EMNtuQ012917;
        Fri, 14 Feb 2020 17:27:07 -0500
Received: from pps.reinject (localhost [127.0.0.1])
        by mx0a-001b2d01.pphosted.com with ESMTP id 2y4j8h1d8n-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Fri, 14 Feb 2020 17:27:07 -0500
Received: from m0098410.ppops.net (m0098410.ppops.net [127.0.0.1])
        by pps.reinject (8.16.0.36/8.16.0.36) with SMTP id 01EMOrtM014415;
        Fri, 14 Feb 2020 17:27:06 -0500
Received: from ppma02wdc.us.ibm.com (aa.5b.37a9.ip4.static.sl-reverse.com
 [169.55.91.170])
        by mx0a-001b2d01.pphosted.com with ESMTP id 2y4j8h1d85-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Fri, 14 Feb 2020 17:27:06 -0500
Received: from pps.filterd (ppma02wdc.us.ibm.com [127.0.0.1])
        by ppma02wdc.us.ibm.com (8.16.0.27/8.16.0.27) with SMTP id
 01EMP5hN011565;
        Fri, 14 Feb 2020 22:27:05 GMT
Received: from b03cxnp08026.gho.boulder.ibm.com
 (b03cxnp08026.gho.boulder.ibm.com [9.17.130.18])
        by ppma02wdc.us.ibm.com with ESMTP id 2y5bc09wq3-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Fri, 14 Feb 2020 22:27:05 +0000
Received: from b03ledav002.gho.boulder.ibm.com
 (b03ledav002.gho.boulder.ibm.com [9.17.130.233])
        by b03cxnp08026.gho.boulder.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id 01EMR2X156951146
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Fri, 14 Feb 2020 22:27:02 GMT
Received: from b03ledav002.gho.boulder.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 2E162136094;
        Fri, 14 Feb 2020 22:27:02 +0000 (GMT)
Received: from b03ledav002.gho.boulder.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 2FF33136091;
        Fri, 14 Feb 2020 22:27:01 +0000 (GMT)
Received: from localhost.localdomain (unknown [9.114.17.106])
        by b03ledav002.gho.boulder.ibm.com (Postfix) with ESMTP;
        Fri, 14 Feb 2020 22:27:01 +0000 (GMT)
From: Christian Borntraeger <borntraeger@de.ibm.com>
To: Christian Borntraeger <borntraeger@de.ibm.com>,
        Janosch Frank <frankja@linux.vnet.ibm.com>,
        Andrew Morton <akpm@linux-foundation.org>
Cc: KVM <kvm@vger.kernel.org>, Cornelia Huck <cohuck@redhat.com>,
        David Hildenbrand <david@redhat.com>,
        Thomas Huth <thuth@redhat.com>,
        Ulrich Weigand <Ulrich.Weigand@de.ibm.com>,
        Claudio Imbrenda <imbrenda@linux.ibm.com>,
        linux-s390 <linux-s390@vger.kernel.org>,
        Michael Mueller <mimu@linux.ibm.com>,
        Vasily Gorbik <gor@linux.ibm.com>,
        Andrea Arcangeli <aarcange@redhat.com>, linux-mm@kvack.org,
        Will Deacon <will@kernel.org>,
        Sean Christopherson <sean.j.christopherson@intel.com>
Subject: [PATCH v2 00/42] KVM: s390: Add support for protected VMs
Date: Fri, 14 Feb 2020 17:26:16 -0500
Message-Id: <20200214222658.12946-1-borntraeger@de.ibm.com>
X-Mailer: git-send-email 2.25.0
MIME-Version: 1.0
X-TM-AS-GCONF: 00
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.138,18.0.572
 definitions=2020-02-14_08:2020-02-14,2020-02-14 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 suspectscore=0 clxscore=1015
 phishscore=0 impostorscore=0 bulkscore=0 malwarescore=0 mlxscore=0
 adultscore=0 spamscore=0 priorityscore=1501 mlxlogscore=999
 lowpriorityscore=0 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.12.0-2001150001 definitions=main-2002140165
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

mm people: This series contains a "pretty small" common code memory
management change that will allow paging, guest backing with files etc
almost just like normal VMs. It should be a no-op for all architectures
not opting in. And it should be usable for others that also try to get
notified on "the pages are in the process of being used for things like
I/O". At the end of the series are two sample patches as these hooks
seem to be useful for other with error handling/call information.  I
would suggest to keep the patch as is and add the additional things when
intel/arm know exactly what they need.

mm-related patches CCed on linux-mm, the complete list can be found on
the KVM and linux-s390 list. 

Andrew, any chance to either take " mm:gup/writeback: add callbacks for
inaccessible pages" or ACK so that I can take it?

Overview
--------
Protected VMs (PVM) are KVM VMs, where KVM can't access the VM's state
like guest memory and guest registers anymore. Instead the PVMs are
mostly managed by a new entity called Ultravisor (UV), which provides
an API, so KVM and the PV can request management actions.

PVMs are encrypted at rest and protected from hypervisor access while
running. They switch from a normal operation into protected mode, so
we can still use the standard boot process to load a encrypted blob
and then move it into protected mode.

Rebooting is only possible by passing through the unprotected/normal
mode and switching to protected again.

All patches are in the protvirtv4 branch of the korg s390 kvm git
https://git.kernel.org/pub/scm/linux/kernel/git/kvms390/linux.git/log/?h=protvirtv4

Claudio presented the technology at his presentation at KVM Forum
2019.

https://static.sched.com/hosted_files/kvmforum2019/3b/ibm_protected_vms_s390x.pdf


v-> v2
- rebase on top of kvm/master
- pipe through rc and rrc. This might have created some churn here and
  there
- turn off sclp masking when rebooting into "unsecure"
- memory management simplification
- prefix page handling now via intercept 112
- io interrupt intervention request fix (do not use GISA)
- api.txt conversion to rst
- sample patches on top of mm/gup/writeback
- tons of review feedback
- kvm_uv debug feature fixes and unifications
- ultravisor information for /sys/firmware
- 

RFCv2 -> v1 (you can diff the protvirtv2 and the protvirtv3 branch)
- tons of review feedback integrated (see mail thread)
- memory management now complete and working
- Documentation patches merged
- interrupt patches merged
- CONFIG_KVM_S390_PROTECTED_VIRTUALIZATION_HOST removed
- SIDA interface integrated into memop
- for merged patches I removed reviews that were not in all patches

Christian Borntraeger (5):
  KVM: s390/mm: Make pages accessible before destroying the guest
  KVM: s390: protvirt: Add SCLP interrupt handling
  KVM: s390: protvirt: do not inject interrupts after start
  s390/uv: Fix handling of length extensions (already in s390 tree)
  KVM: s390: rstify new ioctls in api.rst

Claudio Imbrenda (6):
  mm:gup/writeback: add callbacks for inaccessible pages
  s390/mm: provide memory management functions for protected KVM guests
  KVM: s390/mm: handle guest unpin events
  example for future extension: mm:gup/writeback: add callbacks for
    inaccessible pages: error cases
  example for future extension: mm:gup/writeback: add callbacks for
    inaccessible pages: source indication
  potential fixup for "s390/mm: provide memory management functions for
    protected KVM guests"

Janosch Frank (25):
  KVM: s390: protvirt: Add UV debug trace
  KVM: s390: add new variants of UV CALL
  KVM: s390: protvirt: Add initial vm and cpu lifecycle handling
  KVM: s390: protvirt: Add KVM api documentation
  KVM: s390: protvirt: Secure memory is not mergeable
  KVM: s390: protvirt: Handle SE notification interceptions
  KVM: s390: protvirt: Instruction emulation
  KVM: s390: protvirt: Handle spec exception loops
  KVM: s390: protvirt: Add new gprs location handling
  KVM: S390: protvirt: Introduce instruction data area bounce buffer
  KVM: s390: protvirt: handle secure guest prefix pages
  KVM: s390: protvirt: Write sthyi data to instruction data area
  KVM: s390: protvirt: STSI handling
  KVM: s390: protvirt: disallow one_reg
  KVM: s390: protvirt: Do only reset registers that are accessible
  KVM: s390: protvirt: Only sync fmt4 registers
  KVM: s390: protvirt: Add program exception injection
  KVM: s390: protvirt: Add diag 308 subcode 8 - 10 handling
  KVM: s390: protvirt: UV calls in support of diag308 0, 1
  KVM: s390: protvirt: Report CPU state to Ultravisor
  KVM: s390: protvirt: Support cmd 5 operation state
  KVM: s390: protvirt: Mask PSW interrupt bits for interception 104 and
    112
  KVM: s390: protvirt: Add UV cpu reset calls
  DOCUMENTATION: Protected virtual machine introduction and IPL
  s390: protvirt: Add sysfs firmware interface for Ultravisor
    information

Michael Mueller (2):
  KVM: s390: protvirt: Add interruption injection controls
  KVM: s390: protvirt: Implement interruption injection

Ulrich Weigand (1):
  KVM: s390/interrupt: do not pin adapter interrupt pages

Vasily Gorbik (3):
  s390/protvirt: introduce host side setup
  s390/protvirt: add ultravisor initialization
  s390/mm: add (non)secure page access exceptions handlers

 .../admin-guide/kernel-parameters.txt         |   5 +
 Documentation/virt/kvm/api.rst                | 108 +++-
 Documentation/virt/kvm/devices/s390_flic.rst  |  11 +-
 Documentation/virt/kvm/index.rst              |   2 +
 Documentation/virt/kvm/s390-pv-boot.rst       |  83 +++
 Documentation/virt/kvm/s390-pv.rst            | 116 +++++
 MAINTAINERS                                   |   1 +
 arch/s390/boot/Makefile                       |   2 +-
 arch/s390/boot/uv.c                           |  23 +-
 arch/s390/include/asm/gmap.h                  |   6 +
 arch/s390/include/asm/kvm_host.h              | 113 ++++-
 arch/s390/include/asm/mmu.h                   |   2 +
 arch/s390/include/asm/mmu_context.h           |   1 +
 arch/s390/include/asm/page.h                  |   5 +
 arch/s390/include/asm/pgtable.h               |  35 +-
 arch/s390/include/asm/uv.h                    | 251 ++++++++-
 arch/s390/kernel/Makefile                     |   1 +
 arch/s390/kernel/pgm_check.S                  |   4 +-
 arch/s390/kernel/setup.c                      |   9 +-
 arch/s390/kernel/uv.c                         | 412 +++++++++++++++
 arch/s390/kvm/Makefile                        |   2 +-
 arch/s390/kvm/intercept.c                     | 111 +++-
 arch/s390/kvm/interrupt.c                     | 391 ++++++++------
 arch/s390/kvm/kvm-s390.c                      | 479 ++++++++++++++++--
 arch/s390/kvm/kvm-s390.h                      |  40 ++
 arch/s390/kvm/priv.c                          |  11 +-
 arch/s390/kvm/pv.c                            | 295 +++++++++++
 arch/s390/mm/fault.c                          |  78 +++
 arch/s390/mm/gmap.c                           |  65 ++-
 include/linux/gfp.h                           |  12 +
 include/uapi/linux/kvm.h                      |  44 +-
 mm/gup.c                                      |  15 +-
 mm/page-writeback.c                           |   5 +
 33 files changed, 2438 insertions(+), 300 deletions(-)
 create mode 100644 Documentation/virt/kvm/s390-pv-boot.rst
 create mode 100644 Documentation/virt/kvm/s390-pv.rst
 create mode 100644 arch/s390/kernel/uv.c
 create mode 100644 arch/s390/kvm/pv.c
```
