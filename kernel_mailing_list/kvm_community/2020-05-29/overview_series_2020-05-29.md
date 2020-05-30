#### [PATCH 01/24] KVM: arm64: Move virt/kvm/arm to arch/arm64
##### From: Marc Zyngier <maz@kernel.org>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Marc Zyngier <maz@kernel.org>
X-Patchwork-Id: 11579185
Return-Path: <SRS0=rOkw=7L=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 6AAEF139A
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 29 May 2020 16:01:46 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 3E431214F1
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 29 May 2020 16:01:46 +0000 (UTC)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple; d=kernel.org;
	s=default; t=1590768106;
	bh=NXvLYQdXZzAKf1z0Ejkf6Bxgu0ihaHOZ7/en5bPdiH8=;
	h=From:To:Cc:Subject:Date:In-Reply-To:References:List-ID:From;
	b=n6Op1+V5SycFR2UfYFXNWGTLDbuYfBpZvpPw8/Ev4Gg9l7v9+gOgZCz8HFqqcbVUh
	 frZxau3v1M5J/q7pWrsWz5tPsP2RiD9hDIfjYI6u1iSFCLu+60nLGNDeOTjebAYSUz
	 OubB4ok+4xG9K9fcHvmg+VauT9DnQt3rb6oFSqHc=
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727799AbgE2QBp (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 29 May 2020 12:01:45 -0400
Received: from mail.kernel.org ([198.145.29.99]:40266 "EHLO mail.kernel.org"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726887AbgE2QBo (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 29 May 2020 12:01:44 -0400
Received: from disco-boy.misterjones.org (disco-boy.misterjones.org
 [51.254.78.96])
        (using TLSv1.2 with cipher ECDHE-RSA-AES256-GCM-SHA384 (256/256 bits))
        (No client certificate requested)
        by mail.kernel.org (Postfix) with ESMTPSA id ADB37207F9;
        Fri, 29 May 2020 16:01:41 +0000 (UTC)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple; d=kernel.org;
        s=default; t=1590768102;
        bh=NXvLYQdXZzAKf1z0Ejkf6Bxgu0ihaHOZ7/en5bPdiH8=;
        h=From:To:Cc:Subject:Date:In-Reply-To:References:From;
        b=bkxxk7BFyMJKFz+m8eFzL1RhLvDCUQye8OomEq9kEeFvUYDIRJtwofMEqnf/Q/VcF
         UnFrn7wFue0ek3dEPvAnIiVQJOa5WDr9I5o2C3k9ZkEpn4sh7YFHmHG3Zk1+fwNEvI
         e6TTjq+HaQtNybPnErThZQxtdLz29WyFSE6Sh3AI=
Received: from 78.163-31-62.static.virginmediabusiness.co.uk ([62.31.163.78]
 helo=why.lan)
        by disco-boy.misterjones.org with esmtpsa
 (TLS1.3:ECDHE_RSA_AES_256_GCM_SHA384:256)
        (Exim 4.92)
        (envelope-from <maz@kernel.org>)
        id 1jehRz-00GJKc-Ts; Fri, 29 May 2020 17:01:40 +0100
From: Marc Zyngier <maz@kernel.org>
To: Paolo Bonzini <pbonzini@redhat.com>
Cc: Alexandru Elisei <alexandru.elisei@arm.com>,
        Andrew Scull <ascull@google.com>,
        Ard Biesheuvel <ardb@kernel.org>,
        Christoffer Dall <christoffer.dall@arm.com>,
        David Brazdil <dbrazdil@google.com>,
        Fuad Tabba <tabba@google.com>,
        James Morse <james.morse@arm.com>,
        Jiang Yi <giangyi@amazon.com>,
        Keqian Zhu <zhukeqian1@huawei.com>,
        Mark Rutland <mark.rutland@arm.com>,
        Suzuki K Poulose <suzuki.poulose@arm.com>,
        Will Deacon <will@kernel.org>,
        Zenghui Yu <yuzenghui@huawei.com>,
        Julien Thierry <julien.thierry.kdev@gmail.com>,
        linux-arm-kernel@lists.infradead.org, kvm@vger.kernel.org,
        kvmarm@lists.cs.columbia.edu
Subject: [PATCH 01/24] KVM: arm64: Move virt/kvm/arm to arch/arm64
Date: Fri, 29 May 2020 17:00:58 +0100
Message-Id: <20200529160121.899083-2-maz@kernel.org>
X-Mailer: git-send-email 2.26.2
In-Reply-To: <20200529160121.899083-1-maz@kernel.org>
References: <20200529160121.899083-1-maz@kernel.org>
MIME-Version: 1.0
X-SA-Exim-Connect-IP: 62.31.163.78
X-SA-Exim-Rcpt-To: pbonzini@redhat.com, alexandru.elisei@arm.com,
 ascull@google.com, ardb@kernel.org, christoffer.dall@arm.com,
 dbrazdil@google.com, tabba@google.com, james.morse@arm.com,
 giangyi@amazon.com, zhukeqian1@huawei.com, mark.rutland@arm.com,
 suzuki.poulose@arm.com, will@kernel.org, yuzenghui@huawei.com,
 julien.thierry.kdev@gmail.com, linux-arm-kernel@lists.infradead.org,
 kvm@vger.kernel.org, kvmarm@lists.cs.columbia.edu
X-SA-Exim-Mail-From: maz@kernel.org
X-SA-Exim-Scanned: No (on disco-boy.misterjones.org);
 SAEximRunCond expanded to false
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Now that the 32bit KVM/arm host is a distant memory, let's move the
whole of the KVM/arm64 code into the arm64 tree.

As they said in the song: Welcome Home (Sanitarium).

Signed-off-by: Marc Zyngier <maz@kernel.org>
Acked-by: Will Deacon <will@kernel.org>
Link: https://lore.kernel.org/r/20200513104034.74741-1-maz@kernel.org
---
 MAINTAINERS                                   |   1 -
 arch/arm64/kvm/Makefile                       |  44 ++--
 {virt/kvm/arm => arch/arm64/kvm}/aarch32.c    |   0
 {virt/kvm/arm => arch/arm64/kvm}/arch_timer.c |   0
 {virt/kvm/arm => arch/arm64/kvm}/arm.c        |   2 +-
 arch/arm64/kvm/handle_exit.c                  |   2 +-
 arch/arm64/kvm/hyp/Makefile                   |   9 +-
 .../kvm/arm => arch/arm64/kvm}/hyp/aarch32.c  |   0
 .../kvm/arm => arch/arm64/kvm}/hyp/timer-sr.c |   0
 .../arm => arch/arm64/kvm}/hyp/vgic-v3-sr.c   |   4 -
 {virt/kvm/arm => arch/arm64/kvm}/hypercalls.c |   0
 {virt/kvm/arm => arch/arm64/kvm}/mmio.c       |   0
 {virt/kvm/arm => arch/arm64/kvm}/mmu.c        |   0
 {virt/kvm/arm => arch/arm64/kvm}/perf.c       |   0
 .../arm/pmu.c => arch/arm64/kvm/pmu-emul.c    |   0
 {virt/kvm/arm => arch/arm64/kvm}/psci.c       |   0
 {virt/kvm/arm => arch/arm64/kvm}/pvtime.c     |   0
 arch/arm64/kvm/trace.h                        | 216 +-----------------
 .../arm/trace.h => arch/arm64/kvm/trace_arm.h |  11 +-
 arch/arm64/kvm/trace_handle_exit.h            | 215 +++++++++++++++++
 arch/arm64/kvm/vgic-sys-reg-v3.c              |   2 +-
 {virt/kvm/arm => arch/arm64/kvm}/vgic/trace.h |   2 +-
 .../arm => arch/arm64/kvm}/vgic/vgic-debug.c  |   0
 .../arm => arch/arm64/kvm}/vgic/vgic-init.c   |   0
 .../arm => arch/arm64/kvm}/vgic/vgic-irqfd.c  |   0
 .../arm => arch/arm64/kvm}/vgic/vgic-its.c    |   0
 .../arm64/kvm}/vgic/vgic-kvm-device.c         |   0
 .../arm64/kvm}/vgic/vgic-mmio-v2.c            |   0
 .../arm64/kvm}/vgic/vgic-mmio-v3.c            |   0
 .../arm => arch/arm64/kvm}/vgic/vgic-mmio.c   |   0
 .../arm => arch/arm64/kvm}/vgic/vgic-mmio.h   |   0
 .../kvm/arm => arch/arm64/kvm}/vgic/vgic-v2.c |   0
 .../kvm/arm => arch/arm64/kvm}/vgic/vgic-v3.c |   2 -
 .../kvm/arm => arch/arm64/kvm}/vgic/vgic-v4.c |   0
 {virt/kvm/arm => arch/arm64/kvm}/vgic/vgic.c  |   0
 {virt/kvm/arm => arch/arm64/kvm}/vgic/vgic.h  |   0
 36 files changed, 253 insertions(+), 257 deletions(-)
 rename {virt/kvm/arm => arch/arm64/kvm}/aarch32.c (100%)
 rename {virt/kvm/arm => arch/arm64/kvm}/arch_timer.c (100%)
 rename {virt/kvm/arm => arch/arm64/kvm}/arm.c (99%)
 rename {virt/kvm/arm => arch/arm64/kvm}/hyp/aarch32.c (100%)
 rename {virt/kvm/arm => arch/arm64/kvm}/hyp/timer-sr.c (100%)
 rename {virt/kvm/arm => arch/arm64/kvm}/hyp/vgic-v3-sr.c (99%)
 rename {virt/kvm/arm => arch/arm64/kvm}/hypercalls.c (100%)
 rename {virt/kvm/arm => arch/arm64/kvm}/mmio.c (100%)
 rename {virt/kvm/arm => arch/arm64/kvm}/mmu.c (100%)
 rename {virt/kvm/arm => arch/arm64/kvm}/perf.c (100%)
 rename virt/kvm/arm/pmu.c => arch/arm64/kvm/pmu-emul.c (100%)
 rename {virt/kvm/arm => arch/arm64/kvm}/psci.c (100%)
 rename {virt/kvm/arm => arch/arm64/kvm}/pvtime.c (100%)
 rename virt/kvm/arm/trace.h => arch/arm64/kvm/trace_arm.h (97%)
 create mode 100644 arch/arm64/kvm/trace_handle_exit.h
 rename {virt/kvm/arm => arch/arm64/kvm}/vgic/trace.h (93%)
 rename {virt/kvm/arm => arch/arm64/kvm}/vgic/vgic-debug.c (100%)
 rename {virt/kvm/arm => arch/arm64/kvm}/vgic/vgic-init.c (100%)
 rename {virt/kvm/arm => arch/arm64/kvm}/vgic/vgic-irqfd.c (100%)
 rename {virt/kvm/arm => arch/arm64/kvm}/vgic/vgic-its.c (100%)
 rename {virt/kvm/arm => arch/arm64/kvm}/vgic/vgic-kvm-device.c (100%)
 rename {virt/kvm/arm => arch/arm64/kvm}/vgic/vgic-mmio-v2.c (100%)
 rename {virt/kvm/arm => arch/arm64/kvm}/vgic/vgic-mmio-v3.c (100%)
 rename {virt/kvm/arm => arch/arm64/kvm}/vgic/vgic-mmio.c (100%)
 rename {virt/kvm/arm => arch/arm64/kvm}/vgic/vgic-mmio.h (100%)
 rename {virt/kvm/arm => arch/arm64/kvm}/vgic/vgic-v2.c (100%)
 rename {virt/kvm/arm => arch/arm64/kvm}/vgic/vgic-v3.c (99%)
 rename {virt/kvm/arm => arch/arm64/kvm}/vgic/vgic-v4.c (100%)
 rename {virt/kvm/arm => arch/arm64/kvm}/vgic/vgic.c (100%)
 rename {virt/kvm/arm => arch/arm64/kvm}/vgic/vgic.h (100%)

```
#### [PATCH 1/2] selftests: kvm: introduce cpu_has_svm() check
##### From: Vitaly Kuznetsov <vkuznets@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Vitaly Kuznetsov <vkuznets@redhat.com>
X-Patchwork-Id: 11578517
Return-Path: <SRS0=rOkw=7L=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id B844792A
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 29 May 2020 13:04:18 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 9F7A8207BC
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 29 May 2020 13:04:18 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="d90acfDQ"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726638AbgE2NER (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 29 May 2020 09:04:17 -0400
Received: from us-smtp-delivery-1.mimecast.com ([207.211.31.120]:40173 "EHLO
        us-smtp-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org
        with ESMTP id S1726467AbgE2NEQ (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 29 May 2020 09:04:16 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1590757455;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=NCNyaN4EF9S3QJCaspYw1c/k/yvFSDNyMWE1gpjKqBg=;
        b=d90acfDQ8fgJZ2I5aBvWBxtFKLVsSzP3sJq69iKlaaQoBjtDKd0immbFmKS9OfJroDxI5r
        XbxAHaqQIZAvAuqjAzgomrO1ec4VsqnIlg4f5rKmTEa7XLbMhts5gpY5vpP+1h3ocvBi6p
        e0oX0xExoK5pc88ou1J4cGODK6mmM8k=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-477-C8NwSG5jPjutXSLASIAP7Q-1; Fri, 29 May 2020 09:04:11 -0400
X-MC-Unique: C8NwSG5jPjutXSLASIAP7Q-1
Received: from smtp.corp.redhat.com (int-mx04.intmail.prod.int.phx2.redhat.com
 [10.5.11.14])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 680711054F91;
        Fri, 29 May 2020 13:04:10 +0000 (UTC)
Received: from vitty.brq.redhat.com (unknown [10.40.194.122])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 5C0925D9D5;
        Fri, 29 May 2020 13:04:08 +0000 (UTC)
From: Vitaly Kuznetsov <vkuznets@redhat.com>
To: kvm@vger.kernel.org, Paolo Bonzini <pbonzini@redhat.com>
Cc: Sean Christopherson <sean.j.christopherson@intel.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>
Subject: [PATCH 1/2] selftests: kvm: introduce cpu_has_svm() check
Date: Fri, 29 May 2020 15:04:06 +0200
Message-Id: <20200529130407.57176-1-vkuznets@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.14
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

More tests may want to check if the CPU is Intel or AMD in
guest code, separate cpu_has_svm() and put it as static
inline to svm_util.h.

Signed-off-by: Vitaly Kuznetsov <vkuznets@redhat.com>
---
 tools/testing/selftests/kvm/include/x86_64/svm_util.h | 10 ++++++++++
 tools/testing/selftests/kvm/x86_64/state_test.c       |  9 +--------
 2 files changed, 11 insertions(+), 8 deletions(-)

```
#### [RFC 01/12] ASoC: add function parameters to enable forced path pruning
##### From: Guennadi Liakhovetski <guennadi.liakhovetski@linux.intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Guennadi Liakhovetski
 <guennadi.liakhovetski@linux.intel.com>
X-Patchwork-Id: 11577907
Return-Path: <SRS0=rOkw=7L=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 7701C17C7
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 29 May 2020 07:38:28 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 5DF71207D4
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 29 May 2020 07:38:28 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726837AbgE2Hi0 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 29 May 2020 03:38:26 -0400
Received: from mga07.intel.com ([134.134.136.100]:50710 "EHLO mga07.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726807AbgE2Hhh (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 29 May 2020 03:37:37 -0400
IronPort-SDR: 
 w+9AvCRvP2Om2EUQ/EtI4DL0kvnUh7TggneoiiSCatZBlDA0dGe64LkbqGUmHO4AW2ig/CjRua
 9nS9Es/u3Cww==
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from orsmga004.jf.intel.com ([10.7.209.38])
  by orsmga105.jf.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 29 May 2020 00:37:29 -0700
IronPort-SDR: 
 /+zowXRfLIgZUziE/LHO6wnZjCa8lnJBro4Bkf9/h9KqecEk5lWbj1+eT2Q742ioasx20ZdXZC
 OYJX1cinOkSw==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.73,447,1583222400";
   d="scan'208";a="414890369"
Received: from gliakhov-mobl2.ger.corp.intel.com (HELO
 ubuntu.ger.corp.intel.com) ([10.252.45.157])
  by orsmga004.jf.intel.com with ESMTP; 29 May 2020 00:37:26 -0700
From: Guennadi Liakhovetski <guennadi.liakhovetski@linux.intel.com>
To: kvm@vger.kernel.org
Cc: linux-remoteproc@vger.kernel.org,
        virtualization@lists.linux-foundation.org,
        sound-open-firmware@alsa-project.org,
        Pierre-Louis Bossart <pierre-louis.bossart@linux.intel.com>,
        Liam Girdwood <liam.r.girdwood@linux.intel.com>,
        "Michael S. Tsirkin" <mst@redhat.com>,
        Jason Wang <jasowang@redhat.com>,
        Ohad Ben-Cohen <ohad@wizery.com>,
        Bjorn Andersson <bjorn.andersson@linaro.org>,
        Mathieu Poirier <mathieu.poirier@linaro.org>
Subject: [RFC 01/12] ASoC: add function parameters to enable forced path
 pruning
Date: Fri, 29 May 2020 09:37:11 +0200
Message-Id: <20200529073722.8184-2-guennadi.liakhovetski@linux.intel.com>
X-Mailer: git-send-email 2.20.1
In-Reply-To: <20200529073722.8184-1-guennadi.liakhovetski@linux.intel.com>
References: <20200529073722.8184-1-guennadi.liakhovetski@linux.intel.com>
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This is a preparation for the host part of a virtualised VirtIO audio
host-guest driver pair. It adds a "mode" parameter to
soc_dpcm_runtime_update() to allow it to be used when stopping
streaming in a virtual machine, which requires forced DPCM audio path
pruning.

For audio virtualisation the host side driver will be using the vhost
API, i.e. it will run completely in the kernel. When a guest begins to
stream audio, the vhost calls snd_soc_runtime_activate() and
soc_dpcm_runtime_update() to activate an audio path and update audio
routing. When streaming is stopped, the vhost driver calls
soc_dpcm_runtime_update() and snd_soc_runtime_deactivate(). The latter
doesn't work at the moment, because the DPCM doesn't recognise the
path as inactive. We address this by adding a "mode" parameter to
soc_dpcm_runtime_update(). If virtualisation isn't used, the current
behaviour isn't affected.

Signed-off-by: Guennadi Liakhovetski <guennadi.liakhovetski@linux.intel.com>
---
 include/sound/soc-dpcm.h | 28 ++++++++++++++++----
 sound/soc/soc-compress.c |  2 +-
 sound/soc/soc-dapm.c     |  8 +++---
 sound/soc/soc-pcm.c      | 67 +++++++++++++++++++++++++++++++++---------------
 4 files changed, 74 insertions(+), 31 deletions(-)

```
#### [GIT PULL] KVM/arm64 updates for Linux 5.8
##### From: Marc Zyngier <maz@kernel.org>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Marc Zyngier <maz@kernel.org>
X-Patchwork-Id: 11579177
Return-Path: <SRS0=rOkw=7L=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id B27F4139A
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 29 May 2020 16:01:43 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 8901C208B8
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 29 May 2020 16:01:43 +0000 (UTC)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple; d=kernel.org;
	s=default; t=1590768103;
	bh=yuAO3OKMzQi9yu33GTKm5Be1yABvBfKViwZJPbxtrbw=;
	h=From:To:Cc:Subject:Date:List-ID:From;
	b=ePjBr4RWd6fBgvw9gVS/eL0OkPYoNzK3Q7ymB1xjHqi3MoXW1g07RqjPDX7NoTOxd
	 6YPM2zB38NWtq/gQp407Xfz5iyIyOAfA+G+7htYPHC86LIL5gizB2qN5UsD/b0U+Rj
	 55o8V6r574kjvsaCtzcyLNUajpxijtF05yT1r61E=
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726934AbgE2QBm (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 29 May 2020 12:01:42 -0400
Received: from mail.kernel.org ([198.145.29.99]:40182 "EHLO mail.kernel.org"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726549AbgE2QBm (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 29 May 2020 12:01:42 -0400
Received: from disco-boy.misterjones.org (disco-boy.misterjones.org
 [51.254.78.96])
        (using TLSv1.2 with cipher ECDHE-RSA-AES256-GCM-SHA384 (256/256 bits))
        (No client certificate requested)
        by mail.kernel.org (Postfix) with ESMTPSA id 3F549207BC;
        Fri, 29 May 2020 16:01:40 +0000 (UTC)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple; d=kernel.org;
        s=default; t=1590768100;
        bh=yuAO3OKMzQi9yu33GTKm5Be1yABvBfKViwZJPbxtrbw=;
        h=From:To:Cc:Subject:Date:From;
        b=uRNXbIduzNOlcy1ieQXcPa9ZIUzC1HuPPlNkMrofbvSY2JWmYrABcVUBg/PaTK2Zq
         r+0ngURkqBJ4ysddoONee7c/LU2Ay3VQj8rOaINxNPuzPXK0MgHUBArZZtQlkcdDtG
         VtzZmGd8qSbxPeMqyu9Owx4Sxuis6StlcGU4y2P4=
Received: from 78.163-31-62.static.virginmediabusiness.co.uk ([62.31.163.78]
 helo=why.lan)
        by disco-boy.misterjones.org with esmtpsa
 (TLS1.3:ECDHE_RSA_AES_256_GCM_SHA384:256)
        (Exim 4.92)
        (envelope-from <maz@kernel.org>)
        id 1jehRy-00GJKc-Hx; Fri, 29 May 2020 17:01:38 +0100
From: Marc Zyngier <maz@kernel.org>
To: Paolo Bonzini <pbonzini@redhat.com>
Cc: Alexandru Elisei <alexandru.elisei@arm.com>,
        Andrew Scull <ascull@google.com>,
        Ard Biesheuvel <ardb@kernel.org>,
        Christoffer Dall <christoffer.dall@arm.com>,
        David Brazdil <dbrazdil@google.com>,
        Fuad Tabba <tabba@google.com>,
        James Morse <james.morse@arm.com>,
        Jiang Yi <giangyi@amazon.com>,
        Keqian Zhu <zhukeqian1@huawei.com>,
        Mark Rutland <mark.rutland@arm.com>,
        Suzuki K Poulose <suzuki.poulose@arm.com>,
        Will Deacon <will@kernel.org>,
        Zenghui Yu <yuzenghui@huawei.com>,
        Julien Thierry <julien.thierry.kdev@gmail.com>,
        linux-arm-kernel@lists.infradead.org, kvm@vger.kernel.org,
        kvmarm@lists.cs.columbia.edu
Subject: [GIT PULL] KVM/arm64 updates for Linux 5.8
Date: Fri, 29 May 2020 17:00:57 +0100
Message-Id: <20200529160121.899083-1-maz@kernel.org>
X-Mailer: git-send-email 2.26.2
MIME-Version: 1.0
X-SA-Exim-Connect-IP: 62.31.163.78
X-SA-Exim-Rcpt-To: pbonzini@redhat.com, alexandru.elisei@arm.com,
 ascull@google.com, ardb@kernel.org, christoffer.dall@arm.com,
 dbrazdil@google.com, tabba@google.com, james.morse@arm.com,
 giangyi@amazon.com, zhukeqian1@huawei.com, mark.rutland@arm.com,
 suzuki.poulose@arm.com, will@kernel.org, yuzenghui@huawei.com,
 julien.thierry.kdev@gmail.com, linux-arm-kernel@lists.infradead.org,
 kvm@vger.kernel.org, kvmarm@lists.cs.columbia.edu
X-SA-Exim-Mail-From: maz@kernel.org
X-SA-Exim-Scanned: No (on disco-boy.misterjones.org);
 SAEximRunCond expanded to false
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Hi Paolo,

Here's the (rather small) pull request for the 5.8 updates to
KVM/arm64.  This mostly contains a bunch of cleanups now that can be
done now that we are free of the 32bit legacy, and a number of
refactoring patches that prepare for the eventual landing of the
dreaded nested virt patches.

Two things though:

- there is another bunch of patches that I have routed via the arm64
  tree as they would otherwise very badly conflict if taken via the
  KVM tree

- Depending on how things go during the first week, I may have another
  small set of patches that I'm holding back for now as they also
  conflict very badly with Mike Rapoport's P4D patches.

Please pull,

	M.

The following changes since commit 2ef96a5bb12be62ef75b5828c0aab838ebb29cb8:

  Linux 5.7-rc5 (2020-05-10 15:16:58 -0700)

are available in the Git repository at:

  git://git.kernel.org/pub/scm/linux/kernel/git/kvmarm/kvmarm.git tags/kvmarm-5.8

for you to fetch changes up to 8f7f4fe756bd5cfef73cf8234445081385bdbf7d:

  KVM: arm64: Drop obsolete comment about sys_reg ordering (2020-05-28 13:16:57 +0100)

----------------------------------------------------------------
KVM/arm64 updates for Linux 5.8:

- Move the arch-specific code into arch/arm64/kvm
- Start the post-32bit cleanup
- Cherry-pick a few non-invasive pre-NV patches

----------------------------------------------------------------
Andrew Scull (1):
      KVM: arm64: Remove obsolete kvm_virt_to_phys abstraction

Christoffer Dall (1):
      KVM: arm64: vgic-v3: Take cpu_if pointer directly instead of vcpu

David Brazdil (2):
      KVM: arm64: Clean up cpu_init_hyp_mode()
      KVM: arm64: Fix incorrect comment on kvm_get_hyp_vector()

Fuad Tabba (2):
      KVM: arm64: Clean up kvm makefiles
      KVM: Fix spelling in code comments

Jiang Yi (1):
      KVM: arm/arm64: Release kvm->mmu_lock in loop to prevent starvation

Keqian Zhu (1):
      KVM: arm64: Support enabling dirty log gradually in small chunks

Marc Zyngier (10):
      KVM: arm64: Move virt/kvm/arm to arch/arm64
      KVM: arm64: Simplify __kvm_timer_set_cntvoff implementation
      KVM: arm64: Use cpus_have_final_cap for has_vhe()
      KVM: arm64: Make KVM_CAP_MAX_VCPUS compatible with the selected GIC version
      KVM: arm64: Refactor vcpu_{read,write}_sys_reg
      KVM: arm64: Add missing reset handlers for PMU emulation
      KVM: arm64: Move sysreg reset check to boot time
      KVM: arm64: Don't use empty structures as CPU reset state
      KVM: arm64: Parametrize exception entry with a target EL
      KVM: arm64: Drop obsolete comment about sys_reg ordering

Suzuki K Poulose (2):
      KVM: arm64: Clean up the checking for huge mapping
      KVM: arm64: Unify handling THP backed host memory

Will Deacon (3):
      KVM: arm64: Kill off CONFIG_KVM_ARM_HOST
      KVM: arm64: Update help text
      KVM: arm64: Change CONFIG_KVM to a menuconfig entry

Zenghui Yu (1):
      KVM: arm64: Sidestep stage2_unmap_vm() on vcpu reset when S2FWB is supported

 Documentation/virt/kvm/api.rst                     |   2 +-
 MAINTAINERS                                        |   1 -
 arch/arm64/include/asm/kvm_asm.h                   |   4 +-
 arch/arm64/include/asm/kvm_host.h                  |  44 +----
 arch/arm64/include/asm/kvm_hyp.h                   |  12 +-
 arch/arm64/include/asm/kvm_mmu.h                   |   4 +-
 arch/arm64/include/asm/ptrace.h                    |   1 +
 arch/arm64/include/asm/virt.h                      |   2 +-
 arch/arm64/kernel/asm-offsets.c                    |   2 +-
 arch/arm64/kernel/cpu_errata.c                     |   2 +-
 arch/arm64/kernel/smp.c                            |   2 +-
 arch/arm64/kvm/Kconfig                             |  22 +--
 arch/arm64/kvm/Makefile                            |  46 ++---
 {virt/kvm/arm => arch/arm64/kvm}/aarch32.c         |   0
 {virt/kvm/arm => arch/arm64/kvm}/arch_timer.c      |  12 +-
 {virt/kvm/arm => arch/arm64/kvm}/arm.c             |  60 ++++--
 arch/arm64/kvm/guest.c                             |   4 +-
 arch/arm64/kvm/handle_exit.c                       |   2 +-
 arch/arm64/kvm/hyp/Makefile                        |  16 +-
 {virt/kvm/arm => arch/arm64/kvm}/hyp/aarch32.c     |   0
 arch/arm64/kvm/hyp/switch.c                        |   8 +-
 {virt/kvm/arm => arch/arm64/kvm}/hyp/timer-sr.c    |   3 +-
 {virt/kvm/arm => arch/arm64/kvm}/hyp/vgic-v3-sr.c  |  39 ++--
 {virt/kvm/arm => arch/arm64/kvm}/hypercalls.c      |   0
 arch/arm64/kvm/inject_fault.c                      |  75 +++----
 {virt/kvm/arm => arch/arm64/kvm}/mmio.c            |   2 +-
 {virt/kvm/arm => arch/arm64/kvm}/mmu.c             | 148 ++++++++------
 {virt/kvm/arm => arch/arm64/kvm}/perf.c            |   0
 virt/kvm/arm/pmu.c => arch/arm64/kvm/pmu-emul.c    |   0
 {virt/kvm/arm => arch/arm64/kvm}/psci.c            |   6 +-
 {virt/kvm/arm => arch/arm64/kvm}/pvtime.c          |   0
 arch/arm64/kvm/reset.c                             |  27 ++-
 arch/arm64/kvm/sys_regs.c                          | 212 ++++++++++----------
 arch/arm64/kvm/trace.h                             | 216 +--------------------
 virt/kvm/arm/trace.h => arch/arm64/kvm/trace_arm.h |  11 +-
 arch/arm64/kvm/trace_handle_exit.h                 | 215 ++++++++++++++++++++
 arch/arm64/kvm/vgic-sys-reg-v3.c                   |   2 +-
 {virt/kvm/arm => arch/arm64/kvm}/vgic/trace.h      |   2 +-
 {virt/kvm/arm => arch/arm64/kvm}/vgic/vgic-debug.c |   0
 {virt/kvm/arm => arch/arm64/kvm}/vgic/vgic-init.c  |   0
 {virt/kvm/arm => arch/arm64/kvm}/vgic/vgic-irqfd.c |   0
 {virt/kvm/arm => arch/arm64/kvm}/vgic/vgic-its.c   |   0
 .../arm => arch/arm64/kvm}/vgic/vgic-kvm-device.c  |   0
 .../kvm/arm => arch/arm64/kvm}/vgic/vgic-mmio-v2.c |   0
 .../kvm/arm => arch/arm64/kvm}/vgic/vgic-mmio-v3.c |   0
 {virt/kvm/arm => arch/arm64/kvm}/vgic/vgic-mmio.c  |   0
 {virt/kvm/arm => arch/arm64/kvm}/vgic/vgic-mmio.h  |   0
 {virt/kvm/arm => arch/arm64/kvm}/vgic/vgic-v2.c    |  10 +-
 {virt/kvm/arm => arch/arm64/kvm}/vgic/vgic-v3.c    |  18 +-
 {virt/kvm/arm => arch/arm64/kvm}/vgic/vgic-v4.c    |   0
 {virt/kvm/arm => arch/arm64/kvm}/vgic/vgic.c       |  25 ++-
 {virt/kvm/arm => arch/arm64/kvm}/vgic/vgic.h       |   0
 include/kvm/arm_vgic.h                             |   5 +-
 virt/kvm/coalesced_mmio.c                          |   2 +-
 virt/kvm/eventfd.c                                 |   2 +-
 virt/kvm/kvm_main.c                                |   2 +-
 56 files changed, 629 insertions(+), 639 deletions(-)
 rename {virt/kvm/arm => arch/arm64/kvm}/aarch32.c (100%)
 rename {virt/kvm/arm => arch/arm64/kvm}/arch_timer.c (98%)
 rename {virt/kvm/arm => arch/arm64/kvm}/arm.c (95%)
 rename {virt/kvm/arm => arch/arm64/kvm}/hyp/aarch32.c (100%)
 rename {virt/kvm/arm => arch/arm64/kvm}/hyp/timer-sr.c (89%)
 rename {virt/kvm/arm => arch/arm64/kvm}/hyp/vgic-v3-sr.c (95%)
 rename {virt/kvm/arm => arch/arm64/kvm}/hypercalls.c (100%)
 rename {virt/kvm/arm => arch/arm64/kvm}/mmio.c (98%)
 rename {virt/kvm/arm => arch/arm64/kvm}/mmu.c (96%)
 rename {virt/kvm/arm => arch/arm64/kvm}/perf.c (100%)
 rename virt/kvm/arm/pmu.c => arch/arm64/kvm/pmu-emul.c (100%)
 rename {virt/kvm/arm => arch/arm64/kvm}/psci.c (98%)
 rename {virt/kvm/arm => arch/arm64/kvm}/pvtime.c (100%)
 rename virt/kvm/arm/trace.h => arch/arm64/kvm/trace_arm.h (97%)
 create mode 100644 arch/arm64/kvm/trace_handle_exit.h
 rename {virt/kvm/arm => arch/arm64/kvm}/vgic/trace.h (93%)
 rename {virt/kvm/arm => arch/arm64/kvm}/vgic/vgic-debug.c (100%)
 rename {virt/kvm/arm => arch/arm64/kvm}/vgic/vgic-init.c (100%)
 rename {virt/kvm/arm => arch/arm64/kvm}/vgic/vgic-irqfd.c (100%)
 rename {virt/kvm/arm => arch/arm64/kvm}/vgic/vgic-its.c (100%)
 rename {virt/kvm/arm => arch/arm64/kvm}/vgic/vgic-kvm-device.c (100%)
 rename {virt/kvm/arm => arch/arm64/kvm}/vgic/vgic-mmio-v2.c (100%)
 rename {virt/kvm/arm => arch/arm64/kvm}/vgic/vgic-mmio-v3.c (100%)
 rename {virt/kvm/arm => arch/arm64/kvm}/vgic/vgic-mmio.c (100%)
 rename {virt/kvm/arm => arch/arm64/kvm}/vgic/vgic-mmio.h (100%)
 rename {virt/kvm/arm => arch/arm64/kvm}/vgic/vgic-v2.c (98%)
 rename {virt/kvm/arm => arch/arm64/kvm}/vgic/vgic-v3.c (97%)
 rename {virt/kvm/arm => arch/arm64/kvm}/vgic/vgic-v4.c (100%)
 rename {virt/kvm/arm => arch/arm64/kvm}/vgic/vgic.c (97%)
 rename {virt/kvm/arm => arch/arm64/kvm}/vgic/vgic.h (100%)

From patchwork Fri May 29 16:00:59 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Marc Zyngier <maz@kernel.org>
X-Patchwork-Id: 11579179
Return-Path: <SRS0=rOkw=7L=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id C3909912
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 29 May 2020 16:01:44 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id A435E2145D
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 29 May 2020 16:01:44 +0000 (UTC)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple; d=kernel.org;
	s=default; t=1590768104;
	bh=E/PuPpWmiPrQz16kOxC09voxVIFgWpR67AwcFCKj6rQ=;
	h=From:To:Cc:Subject:Date:In-Reply-To:References:List-ID:From;
	b=00/U86Uj7ecsnd3Td7qyQHqWj6ulAutIBUZ/jb/kNF4DTvAU1GBUsLjUQzZPjZSQa
	 NJFCaVnrXc3Xm6+j5ybHytu7JgAPGKo33kxUuOI90mGeyWGle02yIYORjbUGrHRit8
	 S89UDlwktnIzPyBi/pXnCsyIHRZ9ZIkiPy+o/+zc=
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727071AbgE2QBo (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 29 May 2020 12:01:44 -0400
Received: from mail.kernel.org ([198.145.29.99]:40296 "EHLO mail.kernel.org"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726549AbgE2QBn (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 29 May 2020 12:01:43 -0400
Received: from disco-boy.misterjones.org (disco-boy.misterjones.org
 [51.254.78.96])
        (using TLSv1.2 with cipher ECDHE-RSA-AES256-GCM-SHA384 (256/256 bits))
        (No client certificate requested)
        by mail.kernel.org (Postfix) with ESMTPSA id 8A1B320814;
        Fri, 29 May 2020 16:01:42 +0000 (UTC)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple; d=kernel.org;
        s=default; t=1590768102;
        bh=E/PuPpWmiPrQz16kOxC09voxVIFgWpR67AwcFCKj6rQ=;
        h=From:To:Cc:Subject:Date:In-Reply-To:References:From;
        b=UylOJdpa2G1BF+AHK7NO2WL2jQiwDyDLUoEmpUqst5UC3OjK9JRO6kL5hSC1pyEns
         SS2IMjCSwOpsHzkf79GE/Nrn36yTdzm2/AE+hI6AslyO+1FcFbIdRBI4O/OWYCKkq1
         rtw26Zo64Px2CpAq+xE6hYEvF94pVpxF8My9c2Tc=
Received: from 78.163-31-62.static.virginmediabusiness.co.uk ([62.31.163.78]
 helo=why.lan)
        by disco-boy.misterjones.org with esmtpsa
 (TLS1.3:ECDHE_RSA_AES_256_GCM_SHA384:256)
        (Exim 4.92)
        (envelope-from <maz@kernel.org>)
        id 1jehS0-00GJKc-WB; Fri, 29 May 2020 17:01:41 +0100
From: Marc Zyngier <maz@kernel.org>
To: Paolo Bonzini <pbonzini@redhat.com>
Cc: Alexandru Elisei <alexandru.elisei@arm.com>,
        Andrew Scull <ascull@google.com>,
        Ard Biesheuvel <ardb@kernel.org>,
        Christoffer Dall <christoffer.dall@arm.com>,
        David Brazdil <dbrazdil@google.com>,
        Fuad Tabba <tabba@google.com>,
        James Morse <james.morse@arm.com>,
        Jiang Yi <giangyi@amazon.com>,
        Keqian Zhu <zhukeqian1@huawei.com>,
        Mark Rutland <mark.rutland@arm.com>,
        Suzuki K Poulose <suzuki.poulose@arm.com>,
        Will Deacon <will@kernel.org>,
        Zenghui Yu <yuzenghui@huawei.com>,
        Julien Thierry <julien.thierry.kdev@gmail.com>,
        linux-arm-kernel@lists.infradead.org, kvm@vger.kernel.org,
        kvmarm@lists.cs.columbia.edu
Subject: [PATCH 02/24] KVM: arm64: Kill off CONFIG_KVM_ARM_HOST
Date: Fri, 29 May 2020 17:00:59 +0100
Message-Id: <20200529160121.899083-3-maz@kernel.org>
X-Mailer: git-send-email 2.26.2
In-Reply-To: <20200529160121.899083-1-maz@kernel.org>
References: <20200529160121.899083-1-maz@kernel.org>
MIME-Version: 1.0
X-SA-Exim-Connect-IP: 62.31.163.78
X-SA-Exim-Rcpt-To: pbonzini@redhat.com, alexandru.elisei@arm.com,
 ascull@google.com, ardb@kernel.org, christoffer.dall@arm.com,
 dbrazdil@google.com, tabba@google.com, james.morse@arm.com,
 giangyi@amazon.com, zhukeqian1@huawei.com, mark.rutland@arm.com,
 suzuki.poulose@arm.com, will@kernel.org, yuzenghui@huawei.com,
 julien.thierry.kdev@gmail.com, linux-arm-kernel@lists.infradead.org,
 kvm@vger.kernel.org, kvmarm@lists.cs.columbia.edu
X-SA-Exim-Mail-From: maz@kernel.org
X-SA-Exim-Scanned: No (on disco-boy.misterjones.org);
 SAEximRunCond expanded to false
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Will Deacon <will@kernel.org>

CONFIG_KVM_ARM_HOST is just a proxy for CONFIG_KVM, so remove it in favour
of the latter.

Signed-off-by: Will Deacon <will@kernel.org>
Signed-off-by: Fuad Tabba <tabba@google.com>
Signed-off-by: Marc Zyngier <maz@kernel.org>
Link: https://lore.kernel.org/r/20200505154520.194120-2-tabba@google.com
---
 arch/arm64/kernel/asm-offsets.c |  2 +-
 arch/arm64/kernel/cpu_errata.c  |  2 +-
 arch/arm64/kernel/smp.c         |  2 +-
 arch/arm64/kvm/Kconfig          |  6 ----
 arch/arm64/kvm/Makefile         | 52 ++++++++++++++++-----------------
 arch/arm64/kvm/hyp/Makefile     | 22 +++++++-------
 6 files changed, 40 insertions(+), 46 deletions(-)

```
#### [PATCH 01/30] KVM: x86: track manually whether an event has been injected
##### From: Paolo Bonzini <pbonzini@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Paolo Bonzini <pbonzini@redhat.com>
X-Patchwork-Id: 11579099
Return-Path: <SRS0=rOkw=7L=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 865F2912
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 29 May 2020 15:39:43 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 6F1992077D
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 29 May 2020 15:39:43 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="IDTBj3uH"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727824AbgE2Pjl (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 29 May 2020 11:39:41 -0400
Received: from us-smtp-1.mimecast.com ([205.139.110.61]:53454 "EHLO
        us-smtp-delivery-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S1727793AbgE2Pjk (ORCPT
        <rfc822;kvm@vger.kernel.org>); Fri, 29 May 2020 11:39:40 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1590766779;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding:
         in-reply-to:in-reply-to:references:references;
        bh=cL4gMIny1Mbt/Yoi/DuXPhUBvtXU0cRRx4XztCd3qfI=;
        b=IDTBj3uH+sXK8sJJRL+Sm7HaeTUsWijkDL7SvwYmGJBh8kgKNSTkUz/HhNFxw5OqfW8HCg
        fGQjGACSggd3DL3UU0DPQ6Lf6l5L/4kCHMNQAvw+x4hOpBqmgbFIDPZfs32izfrQaRnov7
        l6JqFh/r3kLqL8eGH2o8U6zhzGONaB8=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-260-y2VFBXPaMCyz1515G0RGZg-1; Fri, 29 May 2020 11:39:37 -0400
X-MC-Unique: y2VFBXPaMCyz1515G0RGZg-1
Received: from smtp.corp.redhat.com (int-mx04.intmail.prod.int.phx2.redhat.com
 [10.5.11.14])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 19AA7464;
        Fri, 29 May 2020 15:39:36 +0000 (UTC)
Received: from virtlab701.virt.lab.eng.bos.redhat.com
 (virtlab701.virt.lab.eng.bos.redhat.com [10.19.152.228])
        by smtp.corp.redhat.com (Postfix) with ESMTP id B59F45D9D5;
        Fri, 29 May 2020 15:39:35 +0000 (UTC)
From: Paolo Bonzini <pbonzini@redhat.com>
To: linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Subject: [PATCH 01/30] KVM: x86: track manually whether an event has been
 injected
Date: Fri, 29 May 2020 11:39:05 -0400
Message-Id: <20200529153934.11694-2-pbonzini@redhat.com>
In-Reply-To: <20200529153934.11694-1-pbonzini@redhat.com>
References: <20200529153934.11694-1-pbonzini@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.14
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Instead of calling kvm_event_needs_reinjection, track its
future return value in a variable.  This will be useful in
the next patch.

Signed-off-by: Paolo Bonzini <pbonzini@redhat.com>
---
 arch/x86/kvm/x86.c | 17 ++++++++++++-----
 1 file changed, 12 insertions(+), 5 deletions(-)

```
#### [PATCH kvm-unit-tests v2] access: disable phys-bits=36 for now
##### From: Paolo Bonzini <pbonzini@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Paolo Bonzini <pbonzini@redhat.com>
X-Patchwork-Id: 11578243
Return-Path: <SRS0=rOkw=7L=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 4FEE1739
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 29 May 2020 09:50:30 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 37E7D207D4
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 29 May 2020 09:50:30 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="Hw5+XGAs"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1725901AbgE2Ju3 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 29 May 2020 05:50:29 -0400
Received: from us-smtp-delivery-1.mimecast.com ([207.211.31.120]:52444 "EHLO
        us-smtp-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org
        with ESMTP id S1725306AbgE2Ju2 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 29 May 2020 05:50:28 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1590745827;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=BwHdRwrK0wPZyetUSej9ICz5eyB+NKkH6EpaQuUXYKw=;
        b=Hw5+XGAs37wjDY5GX7JLQW7Hqv8Bx74RNHIZ6EpicC0k5wr9mZf9l/TFIX2lCDDwIOn64R
        c3Zi3LeFqH5+gAbUf5odd413wP04NEnun4r/1tirsfbhef8OPig457qtzs1j4GeLnilHRX
        zaObPgJtBxpqbtJmRCW/a5D+N7jMzh4=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-33-0E_qsUF9PEGZuZMqI_yy7Q-1; Fri, 29 May 2020 05:50:25 -0400
X-MC-Unique: 0E_qsUF9PEGZuZMqI_yy7Q-1
Received: from smtp.corp.redhat.com (int-mx01.intmail.prod.int.phx2.redhat.com
 [10.5.11.11])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id BFB681005512
        for <kvm@vger.kernel.org>; Fri, 29 May 2020 09:50:24 +0000 (UTC)
Received: from virtlab511.virt.lab.eng.bos.redhat.com
 (virtlab511.virt.lab.eng.bos.redhat.com [10.19.152.198])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 664BE7A8D1;
        Fri, 29 May 2020 09:50:24 +0000 (UTC)
From: Paolo Bonzini <pbonzini@redhat.com>
To: kvm@vger.kernel.org
Cc: Vitaly Kuznetsov <vkuznets@redhat.com>
Subject: [PATCH kvm-unit-tests v2] access: disable phys-bits=36 for now
Date: Fri, 29 May 2020 05:50:23 -0400
Message-Id: <20200529095023.222232-1-pbonzini@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.11
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Support for guest-MAXPHYADDR < host-MAXPHYADDR is not upstream yet,
it should not be enabled.  Otherwise, all the pde.36 and pte.36
fail and the test takes so long that it times out.

Reported-by: Vitaly Kuznetsov <vkuznets@redhat.com>
Signed-off-by: Paolo Bonzini <pbonzini@redhat.com>
---
 x86/unittests.cfg | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
#### [kvm-unit-tests PATCH] x86: pmu: Test full-width counter writes support
##### From: Like Xu <like.xu@linux.intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 8bit
X-Patchwork-Submitter: Like Xu <like.xu@linux.intel.com>
X-Patchwork-Id: 11578027
Return-Path: <SRS0=rOkw=7L=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 0948A92A
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 29 May 2020 07:44:39 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id E95C92100A
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 29 May 2020 07:44:38 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726788AbgE2Hof (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 29 May 2020 03:44:35 -0400
Received: from mga03.intel.com ([134.134.136.65]:51936 "EHLO mga03.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726593AbgE2Hob (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 29 May 2020 03:44:31 -0400
IronPort-SDR: 
 +80ku7H/44UC6FoYahamMgcy9OO7nS7NcKb8KspMvRI/3qsQpYmjiMnQN1pCh/RRarldNv9Uvi
 2cvxkAoVDZuA==
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from fmsmga002.fm.intel.com ([10.253.24.26])
  by orsmga103.jf.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 29 May 2020 00:44:29 -0700
IronPort-SDR: 
 kh8e1JaVGwo3U0lQvu22yLYJ6sIVTXL0BH5pKwMsSYsUcCgVzPRcNvw/e+sglNAjosJtqxSsfk
 WQdMbHlb3wVA==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.73,447,1583222400";
   d="scan'208";a="302754553"
Received: from sqa-gate.sh.intel.com (HELO clx-ap-likexu.tsp.org)
 ([10.239.48.212])
  by fmsmga002.fm.intel.com with ESMTP; 29 May 2020 00:44:27 -0700
From: Like Xu <like.xu@linux.intel.com>
To: Paolo Bonzini <pbonzini@redhat.com>
Cc: Sean Christopherson <sean.j.christopherson@intel.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org, Like Xu <like.xu@linux.intel.com>
Subject: [kvm-unit-tests PATCH] x86: pmu: Test full-width counter writes
 support
Date: Fri, 29 May 2020 15:43:46 +0800
Message-Id: <20200529074347.124619-4-like.xu@linux.intel.com>
X-Mailer: git-send-email 2.21.3
In-Reply-To: <20200529074347.124619-1-like.xu@linux.intel.com>
References: <20200529074347.124619-1-like.xu@linux.intel.com>
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

When the full-width writes capability is set, use the alternative MSR
range to write larger sign counter values (up to GP counter width).

Signed-off-by: Like Xu <like.xu@linux.intel.com>
---
 lib/x86/msr.h |   1 +
 x86/pmu.c     | 125 ++++++++++++++++++++++++++++++++++++++++----------
 2 files changed, 102 insertions(+), 24 deletions(-)

```
#### [kvm-unit-tests PATCH] x86: realmode: Add suffixes for push, pop and iret
##### From: Roman Bolshakov <r.bolshakov@yadro.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Roman Bolshakov <r.bolshakov@yadro.com>
X-Patchwork-Id: 11579639
Return-Path: <SRS0=rOkw=7L=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 900A090
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 29 May 2020 21:26:50 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 675CE20810
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 29 May 2020 21:26:50 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=yadro.com header.i=@yadro.com
 header.b="YLFffMDZ"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728382AbgE2V0t (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 29 May 2020 17:26:49 -0400
Received: from mta-02.yadro.com ([89.207.88.252]:44996 "EHLO mta-01.yadro.com"
        rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org with ESMTP
        id S1727964AbgE2V0s (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 29 May 2020 17:26:48 -0400
Received: from localhost (unknown [127.0.0.1])
        by mta-01.yadro.com (Postfix) with ESMTP id 20E934C879;
        Fri, 29 May 2020 21:26:44 +0000 (UTC)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple; d=yadro.com; h=
        content-type:content-type:content-transfer-encoding:mime-version
        :x-mailer:message-id:date:date:subject:subject:from:from
        :received:received:received; s=mta-01; t=1590787602; x=
        1592602003; bh=Cb10YADitQjUlinhJpS9kzmAGFapgQSiz48tUUd3bQU=; b=Y
        LFffMDZloaEszcT0wpzE1xE1wb9oaLmLVcIUFRN4CAQnfw1xnrn6PzK1WT5J+Yx4
        go6s6fwyf09hXqRWILUyWC+EJaWVcldKXoIeQ0u1m8x3lFMDrl45ZJ8qFdMDojoa
        4N448NXc7KkDM42t0lg/yLPs+3XWYgzYl9p7C5BEds=
X-Virus-Scanned: amavisd-new at yadro.com
Received: from mta-01.yadro.com ([127.0.0.1])
        by localhost (mta-01.yadro.com [127.0.0.1]) (amavisd-new, port 10024)
        with ESMTP id 2V6LZO_XZXdt; Sat, 30 May 2020 00:26:42 +0300 (MSK)
Received: from T-EXCH-02.corp.yadro.com (t-exch-02.corp.yadro.com
 [172.17.10.102])
        (using TLSv1.2 with cipher ECDHE-RSA-AES256-SHA384 (256/256 bits))
        (No client certificate requested)
        by mta-01.yadro.com (Postfix) with ESMTPS id 7D7DB4C856;
        Sat, 30 May 2020 00:26:42 +0300 (MSK)
Received: from localhost (172.17.204.212) by T-EXCH-02.corp.yadro.com
 (172.17.10.102) with Microsoft SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_CBC_SHA384_P384) id 15.1.669.32; Sat, 30
 May 2020 00:26:44 +0300
From: Roman Bolshakov <r.bolshakov@yadro.com>
To: <kvm@vger.kernel.org>
CC: Roman Bolshakov <r.bolshakov@yadro.com>,
        Paolo Bonzini <pbonzini@redhat.com>
Subject: [kvm-unit-tests PATCH] x86: realmode: Add suffixes for push,
 pop and iret
Date: Sat, 30 May 2020 00:26:37 +0300
Message-ID: <20200529212637.5034-1-r.bolshakov@yadro.com>
X-Mailer: git-send-email 2.26.1
MIME-Version: 1.0
X-Originating-IP: [172.17.204.212]
X-ClientProxiedBy: T-EXCH-01.corp.yadro.com (172.17.10.101) To
 T-EXCH-02.corp.yadro.com (172.17.10.102)
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

binutils 2.33 and 2.34 changed generation of PUSH and POP for segment
registers and IRET in '.code16gcc' [1][2][3][4]. gas also yields the
following warnings during the build of realmode.c:

snip.s: Assembler messages:
snip.s:2279: Warning: generating 32-bit `push', unlike earlier gas versions
snip.s:2296: Warning: generating 32-bit `pop', unlike earlier gas versions
snip.s:3633: Warning: generating 16-bit `iret' for .code16gcc directive

This change fixes warnings and failures of the tests:

  push/pop 3
  push/pop 4
  iret 1
  iret 3

1. https://sourceware.org/bugzilla/show_bug.cgi?id=24485
2. https://sourceware.org/git/?p=binutils-gdb.git;h=7cb22ff84745
3. https://sourceware.org/git/?p=binutils-gdb.git;h=06f74c5cb868
4. https://sourceware.org/git/?p=binutils-gdb.git;h=13e600d0f560

Cc: Paolo Bonzini <pbonzini@redhat.com>
Signed-off-by: Roman Bolshakov <r.bolshakov@yadro.com>
---
 x86/realmode.c | 32 ++++++++++++++++----------------
 1 file changed, 16 insertions(+), 16 deletions(-)

```
#### linux-next: manual merge of the kvm tree with the s390 tree
##### From: Stephen Rothwell <sfr@canb.auug.org.au>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Stephen Rothwell <sfr@canb.auug.org.au>
X-Patchwork-Id: 11577811
Return-Path: <SRS0=rOkw=7L=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id DEC611392
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 29 May 2020 06:46:20 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id C39EF2145D
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 29 May 2020 06:46:20 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=canb.auug.org.au header.i=@canb.auug.org.au
 header.b="IJOIS0/Q"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726167AbgE2GqS (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 29 May 2020 02:46:18 -0400
Received: from ozlabs.org ([203.11.71.1]:46139 "EHLO ozlabs.org"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1725681AbgE2GqS (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 29 May 2020 02:46:18 -0400
Received: from authenticated.ozlabs.org (localhost [127.0.0.1])
        (using TLSv1.3 with cipher TLS_AES_256_GCM_SHA384 (256/256 bits)
         key-exchange ECDHE (P-256) server-signature RSA-PSS (4096 bits)
 server-digest SHA256)
        (No client certificate requested)
        by mail.ozlabs.org (Postfix) with ESMTPSA id 49YFTM68PYz9sSp;
        Fri, 29 May 2020 16:46:15 +1000 (AEST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple; d=canb.auug.org.au;
        s=201702; t=1590734776;
        bh=l+Xvu2zy6hKZ6lhYjwD7Ye7643sbaA4BsCh6MX+Mf40=;
        h=Date:From:To:Cc:Subject:From;
        b=IJOIS0/Qce3klupjjUsZu7IruI9fPBWK5y71pBmirNG9rAJQmMgbg4Uh9ohw+i4iX
         bLK1egBbnQevdcHNSGnio/XHHuSxJEjpyNhTJ7XFWKuNiKDGQW/nJszJG8F3vduH7/
         44Dl0y+a17sN1CxqQAWeFnW8LB17zZe39l9MR8b3lcyjTIuPZ/nO17JYJF6IiqifD7
         j9hh4xV/mhiD2RxOiHq0YjWLievOWaIBepZM47EsRnSmT6FZ2xqb478YDbmBLfqWR1
         enZQziWeEWgq8OEfXko5eckwbMGOItE5YhuLymVw+o8+tN3NoO1cLwdr0vLf3U8Ppf
         6GTrVTZ7T6Uyw==
Date: Fri, 29 May 2020 16:46:13 +1000
From: Stephen Rothwell <sfr@canb.auug.org.au>
To: Paolo Bonzini <pbonzini@redhat.com>, KVM <kvm@vger.kernel.org>,
        Heiko Carstens <heiko.carstens@de.ibm.com>,
        Vasily Gorbik <gor@linux.ibm.com>,
        Christian Borntraeger <borntraeger@de.ibm.com>
Cc: Linux Next Mailing List <linux-next@vger.kernel.org>,
        Linux Kernel Mailing List <linux-kernel@vger.kernel.org>,
        David Hildenbrand <david@redhat.com>,
        Sven Schnelle <svens@linux.ibm.com>
Subject: linux-next: manual merge of the kvm tree with the s390 tree
Message-ID: <20200529164613.526f5865@canb.auug.org.au>
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Hi all,

Today's linux-next merge of the kvm tree got a conflict in:

  arch/s390/kvm/vsie.c

between commit:

  0b0ed657fe00 ("s390: remove critical section cleanup from entry.S")

from the s390 tree and commit:

  d075fc3154be ("KVM: s390: vsie: Move conditional reschedule")

from the kvm tree.

I fixed it up (see below) and can carry the fix as necessary. This
is now fixed as far as linux-next is concerned, but any non trivial
conflicts should be mentioned to your upstream maintainer when your tree
is submitted for merging.  You may also want to consider cooperating
with the maintainer of the conflicting tree to minimise any particularly
complex conflicts.

```
#### [Qemu-devel PATCH] target/i386: define a new MSR based feature word - FEAT_PERF_CAPABILITIES
##### From: Like Xu <like.xu@linux.intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Like Xu <like.xu@linux.intel.com>
X-Patchwork-Id: 11578029
Return-Path: <SRS0=rOkw=7L=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 38EB0912
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 29 May 2020 07:44:44 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 24E0B2100A
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 29 May 2020 07:44:44 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726793AbgE2Hoj (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 29 May 2020 03:44:39 -0400
Received: from mga03.intel.com ([134.134.136.65]:51954 "EHLO mga03.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726451AbgE2Hod (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 29 May 2020 03:44:33 -0400
IronPort-SDR: 
 nYWoR4NdbO41jNL4CFubbRPacvA+RiDE5leB4v8CiP2AGq+Nah2SL574rNcnvtLOpNnX26T66i
 TfZgx221iU0Q==
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from fmsmga002.fm.intel.com ([10.253.24.26])
  by orsmga103.jf.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 29 May 2020 00:44:32 -0700
IronPort-SDR: 
 pAtbK/ZL4wacXy7akSK8f7a0OgGWVX08DhI71Z2hZ3eKkQvYg35mTSDAggH76/oKq+wmzgFMJO
 u/2QKvbu0L7A==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.73,447,1583222400";
   d="scan'208";a="302754570"
Received: from sqa-gate.sh.intel.com (HELO clx-ap-likexu.tsp.org)
 ([10.239.48.212])
  by fmsmga002.fm.intel.com with ESMTP; 29 May 2020 00:44:29 -0700
From: Like Xu <like.xu@linux.intel.com>
To: Paolo Bonzini <pbonzini@redhat.com>
Cc: Sean Christopherson <sean.j.christopherson@intel.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org, Like Xu <like.xu@linux.intel.com>,
        Richard Henderson <rth@twiddle.net>,
        Eduardo Habkost <ehabkost@redhat.com>,
        Marcelo Tosatti <mtosatti@redhat.com>, qemu-devel@nongnu.org
Subject: [Qemu-devel PATCH] target/i386: define a new MSR based feature word -
 FEAT_PERF_CAPABILITIES
Date: Fri, 29 May 2020 15:43:47 +0800
Message-Id: <20200529074347.124619-5-like.xu@linux.intel.com>
X-Mailer: git-send-email 2.21.3
In-Reply-To: <20200529074347.124619-1-like.xu@linux.intel.com>
References: <20200529074347.124619-1-like.xu@linux.intel.com>
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The Perfmon and Debug Capability MSR named IA32_PERF_CAPABILITIES is
a feature-enumerating MSR, which only enumerates the feature full-width
write (via bit 13) by now which indicates the processor supports IA32_A_PMCx
interface for updating bits 32 and above of IA32_PMCx.

The existence of MSR IA32_PERF_CAPABILITIES is enumerated by CPUID.1:ECX[15].

Cc: Paolo Bonzini <pbonzini@redhat.com>
Cc: Richard Henderson <rth@twiddle.net>
Cc: Eduardo Habkost <ehabkost@redhat.com>
Cc: Marcelo Tosatti <mtosatti@redhat.com>
Cc: qemu-devel@nongnu.org
Signed-off-by: Like Xu <like.xu@linux.intel.com>
---
 target/i386/cpu.c | 29 +++++++++++++++++++++++++++++
 target/i386/cpu.h |  3 +++
 target/i386/kvm.c | 20 ++++++++++++++++++++
 3 files changed, 52 insertions(+)

```
#### [PATCH 1/6] KVM: X86: Reset vcpu->arch.cpuid_nent to 0 if SET_CPUID fails
##### From: Xiaoyao Li <xiaoyao.li@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Xiaoyao Li <xiaoyao.li@intel.com>
X-Patchwork-Id: 11578177
Return-Path: <SRS0=rOkw=7L=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 63628739
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 29 May 2020 08:55:56 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 54BFE207F5
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 29 May 2020 08:55:56 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726861AbgE2Izx (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 29 May 2020 04:55:53 -0400
Received: from mga02.intel.com ([134.134.136.20]:46106 "EHLO mga02.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1725306AbgE2Izw (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 29 May 2020 04:55:52 -0400
IronPort-SDR: 
 W7Mz2F3EPjCvhPMieqF4F/Ga1RYxZYPIsR1z2aHRfLAgOgQY3hQsVQ/bJqMQxzUR1+crw01zdM
 Pdiy/55UPABA==
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from fmsmga003.fm.intel.com ([10.253.24.29])
  by orsmga101.jf.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 29 May 2020 01:55:51 -0700
IronPort-SDR: 
 a5Oa3r1SQaZiHjHd/srIDIJJaUZFDdCsTEo1FV7EnMltPhAsKVIvH4ZKC8F2saST03ky2nc9+u
 e+Y6zDNcuM7w==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.73,448,1583222400";
   d="scan'208";a="311188298"
Received: from lxy-dell.sh.intel.com ([10.239.159.21])
  by FMSMGA003.fm.intel.com with ESMTP; 29 May 2020 01:55:49 -0700
From: Xiaoyao Li <xiaoyao.li@intel.com>
To: Paolo Bonzini <pbonzini@redhat.com>,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        kvm@vger.kernel.org
Cc: Vitaly Kuznetsov <vkuznets@redhat.com>,
        Jim Mattson <jmattson@google.com>,
        linux-kernel@vger.kernel.org, Xiaoyao Li <xiaoyao.li@intel.com>
Subject: [PATCH 1/6] KVM: X86: Reset vcpu->arch.cpuid_nent to 0 if SET_CPUID
 fails
Date: Fri, 29 May 2020 16:55:40 +0800
Message-Id: <20200529085545.29242-2-xiaoyao.li@intel.com>
X-Mailer: git-send-email 2.18.2
In-Reply-To: <20200529085545.29242-1-xiaoyao.li@intel.com>
References: <20200529085545.29242-1-xiaoyao.li@intel.com>
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

It needs to invalidate CPUID configruations if usersapce provides
illegal input.

Signed-off-by: Xiaoyao Li <xiaoyao.li@intel.com>
---
 arch/x86/kvm/cpuid.c | 4 ++++
 1 file changed, 4 insertions(+)

```
#### [PATCH RESEND v4 1/2] KVM: x86/pmu: Tweak kvm_pmu_get_msr to pass 'struct msr_data' in
##### From: Like Xu <like.xu@linux.intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Like Xu <like.xu@linux.intel.com>
X-Patchwork-Id: 11578023
Return-Path: <SRS0=rOkw=7L=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 8AD1A14C0
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 29 May 2020 07:44:27 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 7BA8F208A7
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 29 May 2020 07:44:27 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726150AbgE2Ho1 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 29 May 2020 03:44:27 -0400
Received: from mga03.intel.com ([134.134.136.65]:51936 "EHLO mga03.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1725993AbgE2Ho0 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 29 May 2020 03:44:26 -0400
IronPort-SDR: 
 X6NfPIJq9kcx9U257LWz75kaZ9rMS4+rR5a63qxf6pZGwFEKWSwPjgDpspi1+/HM3obs98stt4
 M/m/VkOA1tlw==
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from fmsmga002.fm.intel.com ([10.253.24.26])
  by orsmga103.jf.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 29 May 2020 00:44:25 -0700
IronPort-SDR: 
 uGK1bCbbah2Q/JbVkzxjb2MMKU0FGanyEr16422+JSnFmYrTFycc7VvX9ju60mYtyBjKoqJqzQ
 6p55jTyJ+t6w==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.73,447,1583222400";
   d="scan'208";a="302754535"
Received: from sqa-gate.sh.intel.com (HELO clx-ap-likexu.tsp.org)
 ([10.239.48.212])
  by fmsmga002.fm.intel.com with ESMTP; 29 May 2020 00:44:22 -0700
From: Like Xu <like.xu@linux.intel.com>
To: Paolo Bonzini <pbonzini@redhat.com>
Cc: Sean Christopherson <sean.j.christopherson@intel.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org, Wei Wang <wei.w.wang@intel.com>
Subject: [PATCH RESEND v4 1/2] KVM: x86/pmu: Tweak kvm_pmu_get_msr to pass
 'struct msr_data' in
Date: Fri, 29 May 2020 15:43:44 +0800
Message-Id: <20200529074347.124619-2-like.xu@linux.intel.com>
X-Mailer: git-send-email 2.21.3
In-Reply-To: <20200529074347.124619-1-like.xu@linux.intel.com>
References: <20200529074347.124619-1-like.xu@linux.intel.com>
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Wei Wang <wei.w.wang@intel.com>

Change kvm_pmu_get_msr() to get the msr_data struct, as the host_initiated
field from the struct could be used by get_msr. This also makes this API
consistent with kvm_pmu_set_msr. No functional changes.

Signed-off-by: Wei Wang <wei.w.wang@intel.com>
---
 arch/x86/kvm/pmu.c           |  4 ++--
 arch/x86/kvm/pmu.h           |  4 ++--
 arch/x86/kvm/svm/pmu.c       |  7 ++++---
 arch/x86/kvm/vmx/pmu_intel.c | 19 +++++++++++--------
 arch/x86/kvm/x86.c           |  4 ++--
 5 files changed, 21 insertions(+), 17 deletions(-)

```
#### [PATCH v2] virtio_vsock: Fix race condition in virtio_transport_recv_pkt
##### From: Jia He <justin.he@arm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Jia He <justin.he@arm.com>
X-Patchwork-Id: 11579071
Return-Path: <SRS0=rOkw=7L=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 46740739
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 29 May 2020 15:21:49 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 38829206A4
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 29 May 2020 15:21:49 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727914AbgE2PVq (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 29 May 2020 11:21:46 -0400
Received: from foss.arm.com ([217.140.110.172]:37916 "EHLO foss.arm.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726882AbgE2PVp (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 29 May 2020 11:21:45 -0400
Received: from usa-sjc-imap-foss1.foss.arm.com (unknown [10.121.207.14])
        by usa-sjc-mx-foss1.foss.arm.com (Postfix) with ESMTP id 04C941045;
        Fri, 29 May 2020 08:21:45 -0700 (PDT)
Received: from localhost.localdomain (entos-thunderx2-02.shanghai.arm.com
 [10.169.138.74])
        by usa-sjc-imap-foss1.foss.arm.com (Postfix) with ESMTPA id
 A0DC63F718;
        Fri, 29 May 2020 08:21:41 -0700 (PDT)
From: Jia He <justin.he@arm.com>
To: Stefan Hajnoczi <stefanha@redhat.com>,
        Stefano Garzarella <sgarzare@redhat.com>
Cc: "David S. Miller" <davem@davemloft.net>,
        Jakub Kicinski <kuba@kernel.org>, kvm@vger.kernel.org,
        virtualization@lists.linux-foundation.org, netdev@vger.kernel.org,
        linux-kernel@vger.kernel.org, Kaly Xin <Kaly.Xin@arm.com>,
        Jia He <justin.he@arm.com>, stable@vger.kernel.org
Subject: [PATCH v2] virtio_vsock: Fix race condition in
 virtio_transport_recv_pkt
Date: Fri, 29 May 2020 23:21:02 +0800
Message-Id: <20200529152102.58397-1-justin.he@arm.com>
X-Mailer: git-send-email 2.17.1
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

When client tries to connect(SOCK_STREAM) the server in the guest with
NONBLOCK mode, there will be a panic on a ThunderX2 (armv8a server):
[  463.718844][ T5040] Unable to handle kernel NULL pointer dereference at virtual address 0000000000000000
[  463.718848][ T5040] Mem abort info:
[  463.718849][ T5040]   ESR = 0x96000044
[  463.718852][ T5040]   EC = 0x25: DABT (current EL), IL = 32 bits
[  463.718853][ T5040]   SET = 0, FnV = 0
[  463.718854][ T5040]   EA = 0, S1PTW = 0
[  463.718855][ T5040] Data abort info:
[  463.718856][ T5040]   ISV = 0, ISS = 0x00000044
[  463.718857][ T5040]   CM = 0, WnR = 1
[  463.718859][ T5040] user pgtable: 4k pages, 48-bit VAs, pgdp=0000008f6f6e9000
[  463.718861][ T5040] [0000000000000000] pgd=0000000000000000
[  463.718866][ T5040] Internal error: Oops: 96000044 [#1] SMP
[...]
[  463.718977][ T5040] CPU: 213 PID: 5040 Comm: vhost-5032 Tainted: G           O      5.7.0-rc7+ #139
[  463.718980][ T5040] Hardware name: GIGABYTE R281-T91-00/MT91-FS1-00, BIOS F06 09/25/2018
[  463.718982][ T5040] pstate: 60400009 (nZCv daif +PAN -UAO)
[  463.718995][ T5040] pc : virtio_transport_recv_pkt+0x4c8/0xd40 [vmw_vsock_virtio_transport_common]
[  463.718999][ T5040] lr : virtio_transport_recv_pkt+0x1fc/0xd40 [vmw_vsock_virtio_transport_common]
[  463.719000][ T5040] sp : ffff80002dbe3c40
[...]
[  463.719025][ T5040] Call trace:
[  463.719030][ T5040]  virtio_transport_recv_pkt+0x4c8/0xd40 [vmw_vsock_virtio_transport_common]
[  463.719034][ T5040]  vhost_vsock_handle_tx_kick+0x360/0x408 [vhost_vsock]
[  463.719041][ T5040]  vhost_worker+0x100/0x1a0 [vhost]
[  463.719048][ T5040]  kthread+0x128/0x130
[  463.719052][ T5040]  ret_from_fork+0x10/0x18

The race condition as follows:
Task1                            Task2
=====                            =====
__sock_release                   virtio_transport_recv_pkt
  __vsock_release                  vsock_find_bound_socket (found)
    lock_sock_nested
    vsock_remove_sock
    sock_orphan
      sk_set_socket(sk, NULL)
    ...
    release_sock
                                lock_sock
                                   virtio_transport_recv_connecting
                                     sk->sk_socket->state (panic)

The root cause is that vsock_find_bound_socket can't hold the lock_sock,
so there is a small race window between vsock_find_bound_socket() and
lock_sock(). If there is __vsock_release() in another task, sk->sk_socket
will be set to NULL inadvertently.

This fixes it by checking sk->sk_shutdown.

Signed-off-by: Jia He <justin.he@arm.com>
Cc: stable@vger.kernel.org
Cc: Stefano Garzarella <sgarzare@redhat.com>
Reviewed-by: Stefano Garzarella <sgarzare@redhat.com>
---
v2: use lightweight checking suggested by Stefano Garzarella

 net/vmw_vsock/virtio_transport_common.c | 8 ++++++++
 1 file changed, 8 insertions(+)

```
#### [PATCH 1/6] vhost: allow device that does not depend on vhost worker
##### From: Jason Wang <jasowang@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Jason Wang <jasowang@redhat.com>
X-Patchwork-Id: 11578061
Return-Path: <SRS0=rOkw=7L=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 5E830139A
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 29 May 2020 08:03:41 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 3E85F208E4
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 29 May 2020 08:03:41 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="JX1bPUyp"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726575AbgE2IDi (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 29 May 2020 04:03:38 -0400
Received: from us-smtp-delivery-1.mimecast.com ([207.211.31.120]:38106 "EHLO
        us-smtp-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org
        with ESMTP id S1726310AbgE2IDd (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 29 May 2020 04:03:33 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1590739410;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding:
         in-reply-to:in-reply-to:references:references;
        bh=16IIq+gtyyOuTA/+k/mFaqIaYYtPCzydoYwI/b/+K1s=;
        b=JX1bPUyptFB31/1RA0pVqyYlU4Q7hn67MKt0kQpTuZ+59pVONP8WXlyMqSCaF627b9O1O8
        E/3aKcH5fVqf9UtywLG+IfPg+drIDySZFSLANjY9+9c73HASSWcs4ji29xNn3HOFYfqebn
        p9Rpx8zzi0BEKxgjmWtvUbfs63m3x+A=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-487-m3IrS965MNWPb0j_hZqinw-1; Fri, 29 May 2020 04:03:26 -0400
X-MC-Unique: m3IrS965MNWPb0j_hZqinw-1
Received: from smtp.corp.redhat.com (int-mx03.intmail.prod.int.phx2.redhat.com
 [10.5.11.13])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 9F6E8107ACCA;
        Fri, 29 May 2020 08:03:24 +0000 (UTC)
Received: from jason-ThinkPad-X1-Carbon-6th.redhat.com
 (ovpn-13-231.pek2.redhat.com [10.72.13.231])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 06E6199DE6;
        Fri, 29 May 2020 08:03:15 +0000 (UTC)
From: Jason Wang <jasowang@redhat.com>
To: mst@redhat.com, jasowang@redhat.com
Cc: kvm@vger.kernel.org, virtualization@lists.linux-foundation.org,
        netdev@vger.kernel.org, linux-kernel@vger.kernel.org,
        rob.miller@broadcom.com, lingshan.zhu@intel.com,
        eperezma@redhat.com, lulu@redhat.com, shahafs@mellanox.com,
        hanand@xilinx.com, mhabets@solarflare.com, gdawar@xilinx.com,
        saugatm@xilinx.com, vmireyno@marvell.com,
        zhangweining@ruijie.com.cn, eli@mellanox.com
Subject: [PATCH 1/6] vhost: allow device that does not depend on vhost worker
Date: Fri, 29 May 2020 16:02:58 +0800
Message-Id: <20200529080303.15449-2-jasowang@redhat.com>
In-Reply-To: <20200529080303.15449-1-jasowang@redhat.com>
References: <20200529080303.15449-1-jasowang@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.13
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

vDPA device currently relays the eventfd via vhost worker. This is
inefficient due the latency of wakeup and scheduling, so this patch
tries to introduce a use_worker attribute for the vhost device. When
use_worker is not set with vhost_dev_init(), vhost won't try to
allocate a worker thread and the vhost_poll will be processed directly
in the wakeup function.

This help for vDPA since it reduces the latency caused by vhost worker.

In my testing, it saves 0.2 ms in pings between VMs on a mutual host.

Signed-off-by: Zhu Lingshan <lingshan.zhu@intel.com>
Signed-off-by: Jason Wang <jasowang@redhat.com>
---
 drivers/vhost/net.c   |  2 +-
 drivers/vhost/scsi.c  |  2 +-
 drivers/vhost/vdpa.c  |  2 +-
 drivers/vhost/vhost.c | 38 +++++++++++++++++++++++++-------------
 drivers/vhost/vhost.h |  2 ++
 drivers/vhost/vsock.c |  2 +-
 6 files changed, 31 insertions(+), 17 deletions(-)

```
#### [PATCH] virtio_vsock: Fix race condition in virtio_transport_recv_pkt
##### From: Jia He <justin.he@arm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Jia He <justin.he@arm.com>
X-Patchwork-Id: 11578675
Return-Path: <SRS0=rOkw=7L=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 90201739
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 29 May 2020 13:32:30 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 7FF51208B8
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 29 May 2020 13:32:30 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727090AbgE2NcZ (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 29 May 2020 09:32:25 -0400
Received: from foss.arm.com ([217.140.110.172]:36640 "EHLO foss.arm.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726549AbgE2NcY (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 29 May 2020 09:32:24 -0400
Received: from usa-sjc-imap-foss1.foss.arm.com (unknown [10.121.207.14])
        by usa-sjc-mx-foss1.foss.arm.com (Postfix) with ESMTP id C089A55D;
        Fri, 29 May 2020 06:32:23 -0700 (PDT)
Received: from localhost.localdomain (entos-thunderx2-02.shanghai.arm.com
 [10.169.138.74])
        by usa-sjc-imap-foss1.foss.arm.com (Postfix) with ESMTPA id
 66E103F305;
        Fri, 29 May 2020 06:32:20 -0700 (PDT)
From: Jia He <justin.he@arm.com>
To: Stefan Hajnoczi <stefanha@redhat.com>,
        Stefano Garzarella <sgarzare@redhat.com>
Cc: "David S. Miller" <davem@davemloft.net>,
        Jakub Kicinski <kuba@kernel.org>, kvm@vger.kernel.org,
        virtualization@lists.linux-foundation.org, netdev@vger.kernel.org,
        linux-kernel@vger.kernel.org, Kaly Xin <Kaly.Xin@arm.com>,
        Jia He <justin.he@arm.com>, stable@vger.kernel.org
Subject: [PATCH] virtio_vsock: Fix race condition in virtio_transport_recv_pkt
Date: Fri, 29 May 2020 21:31:23 +0800
Message-Id: <20200529133123.195610-1-justin.he@arm.com>
X-Mailer: git-send-email 2.17.1
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

When client tries to connect(SOCK_STREAM) the server in the guest with NONBLOCK
mode, there will be a panic on a ThunderX2 (armv8a server):
[  463.718844][ T5040] Unable to handle kernel NULL pointer dereference at virtual address 0000000000000000
[  463.718848][ T5040] Mem abort info:
[  463.718849][ T5040]   ESR = 0x96000044
[  463.718852][ T5040]   EC = 0x25: DABT (current EL), IL = 32 bits
[  463.718853][ T5040]   SET = 0, FnV = 0
[  463.718854][ T5040]   EA = 0, S1PTW = 0
[  463.718855][ T5040] Data abort info:
[  463.718856][ T5040]   ISV = 0, ISS = 0x00000044
[  463.718857][ T5040]   CM = 0, WnR = 1
[  463.718859][ T5040] user pgtable: 4k pages, 48-bit VAs, pgdp=0000008f6f6e9000
[  463.718861][ T5040] [0000000000000000] pgd=0000000000000000
[  463.718866][ T5040] Internal error: Oops: 96000044 [#1] SMP
[...]
[  463.718977][ T5040] CPU: 213 PID: 5040 Comm: vhost-5032 Tainted: G           O      5.7.0-rc7+ #139
[  463.718980][ T5040] Hardware name: GIGABYTE R281-T91-00/MT91-FS1-00, BIOS F06 09/25/2018
[  463.718982][ T5040] pstate: 60400009 (nZCv daif +PAN -UAO)
[  463.718995][ T5040] pc : virtio_transport_recv_pkt+0x4c8/0xd40 [vmw_vsock_virtio_transport_common]
[  463.718999][ T5040] lr : virtio_transport_recv_pkt+0x1fc/0xd40 [vmw_vsock_virtio_transport_common]
[  463.719000][ T5040] sp : ffff80002dbe3c40
[...]
[  463.719025][ T5040] Call trace:
[  463.719030][ T5040]  virtio_transport_recv_pkt+0x4c8/0xd40 [vmw_vsock_virtio_transport_common]
[  463.719034][ T5040]  vhost_vsock_handle_tx_kick+0x360/0x408 [vhost_vsock]
[  463.719041][ T5040]  vhost_worker+0x100/0x1a0 [vhost]
[  463.719048][ T5040]  kthread+0x128/0x130
[  463.719052][ T5040]  ret_from_fork+0x10/0x18

The race condition as follows:
Task1                            Task2
=====                            =====
__sock_release                   virtio_transport_recv_pkt
  __vsock_release                  vsock_find_bound_socket (found)
    lock_sock_nested
    vsock_remove_sock
    sock_orphan
      sk_set_socket(sk, NULL)
    ...
    release_sock
                                lock_sock
                                   virtio_transport_recv_connecting
                                     sk->sk_socket->state (panic)

This fixes it by checking vsk again whether it is in bound/connected table.

Signed-off-by: Jia He <justin.he@arm.com>
Cc: stable@vger.kernel.org
---
 net/vmw_vsock/virtio_transport_common.c | 11 +++++++++++
 1 file changed, 11 insertions(+)

```
#### [PATCH v12 1/6] x86/kvm/hyper-v: Explicitly align hcall param for kvm_hyperv_exit
##### From: Jon Doron <arilou@gmail.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Jon Doron <arilou@gmail.com>
X-Patchwork-Id: 11578733
Return-Path: <SRS0=rOkw=7L=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 603A5739
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 29 May 2020 13:46:03 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 490A521475
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 29 May 2020 13:46:03 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=gmail.com header.i=@gmail.com
 header.b="Q8FIdXQG"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726966AbgE2NqB (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 29 May 2020 09:46:01 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:33662 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726476AbgE2NqA (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 29 May 2020 09:46:00 -0400
Received: from mail-wm1-x341.google.com (mail-wm1-x341.google.com
 [IPv6:2a00:1450:4864:20::341])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 0AD85C03E969;
        Fri, 29 May 2020 06:45:59 -0700 (PDT)
Received: by mail-wm1-x341.google.com with SMTP id j198so6866867wmj.0;
        Fri, 29 May 2020 06:45:58 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=from:to:cc:subject:date:message-id:in-reply-to:references
         :mime-version:content-transfer-encoding;
        bh=hjT03eHhQ1dE3AJ2qMjxfwTNnQchau8BzAjB0MfMplY=;
        b=Q8FIdXQGiAnfzPYerdUI2ObKUeFZLkPa6hGLB6t8k7w03e1k++0XqNoz+ATgNN/lqG
         5mdnCd7vj1Sqnp/EZLBSS7w4HdAkQ8RsC5fxFvjL50HC+nFf97Phrk8txR5NmZDbGqEX
         odalYUJD35+G14GLhDeaD1qEaPBWfhxMNFqTfNeKNAWT/VUila/h4cusPjCakjvWur1r
         Rmo9S3Zi5aEk4kZrP9yPSR78BG5lvOHN61AfhNl+oMPVfgBkpp4eA5ohdr3RCP4O2geN
         dyDJGJ9xmIkLQkqkpHoJrCTr+z/mAti7hLg/qOUppjhAdKCftcn7mTYy8wx9Z+paD3wy
         EZWw==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:in-reply-to
         :references:mime-version:content-transfer-encoding;
        bh=hjT03eHhQ1dE3AJ2qMjxfwTNnQchau8BzAjB0MfMplY=;
        b=KCLYNQxJfDcyEcvd8TCHmBhC7p0VZp/+25aQ7uV8FJIr32eC3WbVw9PfBxH+kNRzgj
         Ot5gSxTnv/BO2Tko64mqMO075OliNwXCr2JhKjym+Qb1zPS5cUQjbW5Nh9vUyHLl9qe6
         7EwC2KUCtoM28KkLJByKcoN5MoGztuz01vs/JNk8doujq2HETeIaAoqeUsC510pMvV56
         KNN6SZDA7tqARbuUIlIQU0W5RvPl1SNQ5KzccVLLlM1a5GHL0ewtZZm4eeqtoqSgZR/i
         WZMwz3pvPED+7KTQOsky3ziUaWy/RcaEA6fggxdgMgU+bH1p9QAU95envUkMYZi4QagX
         dxDg==
X-Gm-Message-State: AOAM532J/kwGiPaH9KFYtJYmEbZMZevhDT0XQmkgdaIg7ZHUbcUwNVH1
        WE4L8W4abu5RJWxeUTVsY0oBrkFm
X-Google-Smtp-Source: 
 ABdhPJxinWMzhrGuUwG301mAo+1OAUGgdCNtv8YATF709K7bgg8BOM4HDBB2beh7n+ttmVTL6PIWaA==
X-Received: by 2002:a1c:1fc2:: with SMTP id f185mr8336605wmf.4.1590759957544;
        Fri, 29 May 2020 06:45:57 -0700 (PDT)
Received: from jondnuc.lan (IGLD-84-229-154-20.inter.net.il. [84.229.154.20])
        by smtp.gmail.com with ESMTPSA id
 y37sm12347263wrd.55.2020.05.29.06.45.56
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Fri, 29 May 2020 06:45:57 -0700 (PDT)
From: Jon Doron <arilou@gmail.com>
To: kvm@vger.kernel.org, linux-hyperv@vger.kernel.org
Cc: vkuznets@redhat.com, pbonzini@redhat.com, rvkagan@yandex-team.ru,
        Jon Doron <arilou@gmail.com>
Subject: [PATCH v12 1/6] x86/kvm/hyper-v: Explicitly align hcall param for
 kvm_hyperv_exit
Date: Fri, 29 May 2020 16:45:38 +0300
Message-Id: <20200529134543.1127440-2-arilou@gmail.com>
X-Mailer: git-send-email 2.25.1
In-Reply-To: <20200529134543.1127440-1-arilou@gmail.com>
References: <20200529134543.1127440-1-arilou@gmail.com>
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The problem the patch is trying to address is the fact that 'struct
kvm_hyperv_exit' has different layout on when compiling in 32 and 64 bit
modes.

In 64-bit mode the default alignment boundary is 64 bits thus
forcing extra gaps after 'type' and 'msr' but in 32-bit mode the
boundary is at 32 bits thus no extra gaps.

This is an issue as even when the kernel is 64 bit, the userspace using
the interface can be both 32 and 64 bit but the same 32 bit userspace has
to work with 32 bit kernel.

The issue is fixed by forcing the 64 bit layout, this leads to ABI
change for 32 bit builds and while we are obviously breaking '32 bit
userspace with 32 bit kernel' case, we're fixing the '32 bit userspace
with 64 bit kernel' one.

As the interface has no (known) users and 32 bit KVM is rather baroque
nowadays, this seems like a reasonable decision.

Reviewed-by: Vitaly Kuznetsov <vkuznets@redhat.com>
Signed-off-by: Jon Doron <arilou@gmail.com>
---
 Documentation/virt/kvm/api.rst | 2 ++
 include/uapi/linux/kvm.h       | 2 ++
 2 files changed, 4 insertions(+)

```
