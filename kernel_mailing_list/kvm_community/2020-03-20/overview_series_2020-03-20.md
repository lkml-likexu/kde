#### [kvm-unit-tests PATCH 1/2] scripts/arch-run: Support testing of hvf accel
##### From: Roman Bolshakov <r.bolshakov@yadro.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Roman Bolshakov <r.bolshakov@yadro.com>
X-Patchwork-Id: 11449527
Return-Path: <SRS0=CcrQ=5F=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id E4D601864
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 20 Mar 2020 14:57:12 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id C52572076E
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 20 Mar 2020 14:57:12 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=yadro.com header.i=@yadro.com
 header.b="TZZi6xqE"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727226AbgCTO5M (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 20 Mar 2020 10:57:12 -0400
Received: from mta-02.yadro.com ([89.207.88.252]:51178 "EHLO mta-01.yadro.com"
        rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org with ESMTP
        id S1726954AbgCTO5L (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 20 Mar 2020 10:57:11 -0400
Received: from localhost (unknown [127.0.0.1])
        by mta-01.yadro.com (Postfix) with ESMTP id D7499412E5;
        Fri, 20 Mar 2020 14:57:09 +0000 (UTC)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple; d=yadro.com; h=
        content-type:content-type:content-transfer-encoding:mime-version
        :references:in-reply-to:x-mailer:message-id:date:date:subject
        :subject:from:from:received:received:received; s=mta-01; t=
        1584716228; x=1586530629; bh=hXk2I+Uf3B4qG3bY1LH8F04P3dqKkVGLcEc
        7zB2bHMU=; b=TZZi6xqEYLSgSmJYhypUX/vHopxgYdjY2sPwW99Z9z/vA/T7fTd
        PN6R1R6zHQFgZtS7+MVZb8hqa+XpKqCsLNS5Fn4OEcUm4qwuG0PZIOCBVcbfKysV
        1HAKuxzC+5LvIkysrA3d7U0sOj1jQcL/1FRSjKX4Ackk0ZZYsjmTksIA=
X-Virus-Scanned: amavisd-new at yadro.com
Received: from mta-01.yadro.com ([127.0.0.1])
        by localhost (mta-01.yadro.com [127.0.0.1]) (amavisd-new, port 10024)
        with ESMTP id q9bfuiwIYJdN; Fri, 20 Mar 2020 17:57:08 +0300 (MSK)
Received: from T-EXCH-02.corp.yadro.com (t-exch-02.corp.yadro.com
 [172.17.10.102])
        (using TLSv1.2 with cipher ECDHE-RSA-AES256-SHA384 (256/256 bits))
        (No client certificate requested)
        by mta-01.yadro.com (Postfix) with ESMTPS id 9B986412EA;
        Fri, 20 Mar 2020 17:57:07 +0300 (MSK)
Received: from localhost (172.17.204.212) by T-EXCH-02.corp.yadro.com
 (172.17.10.102) with Microsoft SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_CBC_SHA384_P384) id 15.1.669.32; Fri, 20
 Mar 2020 17:57:08 +0300
From: Roman Bolshakov <r.bolshakov@yadro.com>
To: <kvm@vger.kernel.org>
CC: Cameron Esfahani <dirty@apple.com>,
        Roman Bolshakov <r.bolshakov@yadro.com>
Subject: [kvm-unit-tests PATCH 1/2] scripts/arch-run: Support testing of hvf
 accel
Date: Fri, 20 Mar 2020 17:55:40 +0300
Message-ID: <20200320145541.38578-2-r.bolshakov@yadro.com>
X-Mailer: git-send-email 2.24.1
In-Reply-To: <20200320145541.38578-1-r.bolshakov@yadro.com>
References: <20200320145541.38578-1-r.bolshakov@yadro.com>
MIME-Version: 1.0
X-Originating-IP: [172.17.204.212]
X-ClientProxiedBy: T-EXCH-01.corp.yadro.com (172.17.10.101) To
 T-EXCH-02.corp.yadro.com (172.17.10.102)
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The tests can be run if Hypervisor.framework API is available:

  https://developer.apple.com/documentation/hypervisor?language=objc#1676667

Cc: Cameron Esfahani <dirty@apple.com>
Signed-off-by: Roman Bolshakov <r.bolshakov@yadro.com>
---
 scripts/arch-run.bash | 13 +++++++++++++
 1 file changed, 13 insertions(+)

```
#### [kvm-unit-tests PATCH v7 01/13] libcflat: Add other size defines
##### From: Eric Auger <eric.auger@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Eric Auger <eric.auger@redhat.com>
X-Patchwork-Id: 11448713
Return-Path: <SRS0=CcrQ=5F=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id D161B1392
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 20 Mar 2020 09:24:51 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id A7D0220767
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 20 Mar 2020 09:24:51 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="XPDaqeu6"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726913AbgCTJYu (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 20 Mar 2020 05:24:50 -0400
Received: from us-smtp-delivery-74.mimecast.com ([63.128.21.74]:52701 "EHLO
        us-smtp-delivery-74.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1726791AbgCTJYt (ORCPT
        <rfc822;kvm@vger.kernel.org>); Fri, 20 Mar 2020 05:24:49 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1584696289;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding:
         in-reply-to:in-reply-to:references:references;
        bh=g1Y7SAIkQ6YKL70iv+PevVOHVnPkk+5bW/+E3fVVoME=;
        b=XPDaqeu6rrCWTGyDosgmPLheqiMB6puA43tar7wmYFlZHzFK9kck0mQNNIUnZyV6Zl1GbM
        IYLsUrdSlYLRcZsvp7MXSrj++3qUjwTMwldC4J44huCvHDtErjSoGVEM3ESjcwkLG81s4g
        +O2pc6C+v9rza7FGjfwPFlE4i3HFWXg=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-158-YlwQy-4nODS1Pey_klco2g-1; Fri, 20 Mar 2020 05:24:47 -0400
X-MC-Unique: YlwQy-4nODS1Pey_klco2g-1
Received: from smtp.corp.redhat.com (int-mx06.intmail.prod.int.phx2.redhat.com
 [10.5.11.16])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id C092E1083E80;
        Fri, 20 Mar 2020 09:24:45 +0000 (UTC)
Received: from laptop.redhat.com (ovpn-113-142.ams2.redhat.com
 [10.36.113.142])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 0C0785C1D8;
        Fri, 20 Mar 2020 09:24:39 +0000 (UTC)
From: Eric Auger <eric.auger@redhat.com>
To: eric.auger.pro@gmail.com, eric.auger@redhat.com, maz@kernel.org,
        kvmarm@lists.cs.columbia.edu, kvm@vger.kernel.org,
        qemu-devel@nongnu.org, qemu-arm@nongnu.org
Cc: drjones@redhat.com, andre.przywara@arm.com,
        peter.maydell@linaro.org, yuzenghui@huawei.com,
        alexandru.elisei@arm.com, thuth@redhat.com
Subject: [kvm-unit-tests PATCH v7 01/13] libcflat: Add other size defines
Date: Fri, 20 Mar 2020 10:24:16 +0100
Message-Id: <20200320092428.20880-2-eric.auger@redhat.com>
In-Reply-To: <20200320092428.20880-1-eric.auger@redhat.com>
References: <20200320092428.20880-1-eric.auger@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.16
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Introduce additional SZ_256, SZ_8K, SZ_16K macros that will
be used by ITS tests.

Signed-off-by: Eric Auger <eric.auger@redhat.com>
Reviewed-by: Thomas Huth <thuth@redhat.com>
---
 lib/libcflat.h | 3 +++
 1 file changed, 3 insertions(+)

```
#### [PATCH v10 1/8] KVM: VMX: Introduce CET VMX fields and flags
##### From: Yang Weijiang <weijiang.yang@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Yang Weijiang <weijiang.yang@intel.com>
X-Patchwork-Id: 11448361
Return-Path: <SRS0=CcrQ=5F=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 8A61C139A
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 20 Mar 2020 03:40:48 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 6AB4D2072D
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 20 Mar 2020 03:40:48 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727069AbgCTDko (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 19 Mar 2020 23:40:44 -0400
Received: from mga01.intel.com ([192.55.52.88]:27908 "EHLO mga01.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726614AbgCTDko (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 19 Mar 2020 23:40:44 -0400
IronPort-SDR: 
 L/XhEyHv43c494j6BqfoIDsswtbbYtNHwmviatzda9Agl1fpFvu6OdAx/6W7LX4kcOlxzwCk/c
 N5Lw4caBayiQ==
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from orsmga002.jf.intel.com ([10.7.209.21])
  by fmsmga101.fm.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 19 Mar 2020 20:40:44 -0700
IronPort-SDR: 
 YctU/yzzEcXJC+yGogNmsjubAa8wNJJ8mzA9mdvsWe1YSZvvrOHRO+tMCvwQNDgyG1lWAklWCb
 2PaovIA9v0rQ==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.72,283,1580803200";
   d="scan'208";a="263945576"
Received: from local-michael-cet-test.sh.intel.com ([10.239.159.128])
  by orsmga002.jf.intel.com with ESMTP; 19 Mar 2020 20:40:41 -0700
From: Yang Weijiang <weijiang.yang@intel.com>
To: kvm@vger.kernel.org, linux-kernel@vger.kernel.org,
        sean.j.christopherson@intel.com, pbonzini@redhat.com,
        jmattson@google.com
Cc: yu.c.zhang@linux.intel.com, Yang Weijiang <weijiang.yang@intel.com>
Subject: [PATCH v10 1/8] KVM: VMX: Introduce CET VMX fields and flags
Date: Fri, 20 Mar 2020 11:43:34 +0800
Message-Id: <20200320034342.26610-2-weijiang.yang@intel.com>
X-Mailer: git-send-email 2.17.2
In-Reply-To: <20200320034342.26610-1-weijiang.yang@intel.com>
References: <20200320034342.26610-1-weijiang.yang@intel.com>
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

CET(Control-flow Enforcement Technology) is a CPU feature
used to prevent Return/Jump-Oriented Programming(ROP/JOP)
attacks. It provides the following sub-features to defend
against ROP/JOP style control-flow subversion attacks:

Shadow Stack (SHSTK):
  A second stack for program which is used exclusively for
  control transfer operations.

Indirect Branch Tracking (IBT):
  Code branching protection to defend against jump/call oriented
  programming.

Several new CET MSRs are defined in kernel to support CET:
  MSR_IA32_{U,S}_CET: Controls the CET settings for user
                      mode and suervisor mode respectively.

  MSR_IA32_PL{0,1,2,3}_SSP: Stores shadow stack pointers for
                            CPL-0,1,2,3 level respectively.

  MSR_IA32_INT_SSP_TAB: Stores base address of shadow stack
                        pointer table.

Two XSAVES state bits are introduced for CET:
  IA32_XSS:[bit 11]: For saving/restoring user mode CET states
  IA32_XSS:[bit 12]: For saving/restoring supervisor mode CET states.

Six VMCS fields are introduced for CET:
  {HOST,GUEST}_S_CET: Stores CET settings for supervisor mode.
  {HOST,GUEST}_SSP: Stores shadow stack pointer for supervisor mode.
  {HOST,GUEST}_INTR_SSP_TABLE: Stores base address of shadow stack pointer
                               table.

If VM_EXIT_LOAD_HOST_CET_STATE = 1, the host's CET MSRs are restored
from below VMCS fields at VM-Exit:
  HOST_S_CET
  HOST_SSP
  HOST_INTR_SSP_TABLE

If VM_ENTRY_LOAD_GUEST_CET_STATE = 1, the guest's CET MSRs are loaded
from below VMCS fields at VM-Entry:
  GUEST_S_CET
  GUEST_SSP
  GUEST_INTR_SSP_TABLE

Co-developed-by: Zhang Yi Z <yi.z.zhang@linux.intel.com>
Signed-off-by: Zhang Yi Z <yi.z.zhang@linux.intel.com>
Signed-off-by: Yang Weijiang <weijiang.yang@intel.com>
---
 arch/x86/include/asm/vmx.h      | 8 ++++++++
 arch/x86/include/uapi/asm/kvm.h | 1 +
 arch/x86/kvm/x86.c              | 4 ++++
 arch/x86/kvm/x86.h              | 2 +-
 4 files changed, 14 insertions(+), 1 deletion(-)

```
#### [PATCH v6 01/23] irqchip/gic-v3: Use SGIs without active state if offered
##### From: Marc Zyngier <maz@kernel.org>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Marc Zyngier <maz@kernel.org>
X-Patchwork-Id: 11450013
Return-Path: <SRS0=CcrQ=5F=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 5CA7817E6
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 20 Mar 2020 18:25:20 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 3BA1620782
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 20 Mar 2020 18:25:20 +0000 (UTC)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple; d=kernel.org;
	s=default; t=1584728720;
	bh=5jJuGUFWRJ2T6vmHdTiGNL4skAtWIsvs2wOH9lZnqqU=;
	h=From:To:Cc:Subject:Date:In-Reply-To:References:List-ID:From;
	b=bE1ieQshoTHyedkCF/TiBw6jIRFWJkvOsui2Crgw1T6kLOdwUpsbA8YDrchA1Z0tO
	 y30ZHiEtNAAxPdI/QZBsJGrYL3QCwP8CkiinfmQ3Mj5m9f7bZZHCkkku60e9nzj1z/
	 KgtlOINsMhazqO3YEaV2FAUh/sxsQ1/5dr4UXVjM=
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727262AbgCTSYh (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 20 Mar 2020 14:24:37 -0400
Received: from mail.kernel.org ([198.145.29.99]:35672 "EHLO mail.kernel.org"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726878AbgCTSYf (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 20 Mar 2020 14:24:35 -0400
Received: from disco-boy.misterjones.org (disco-boy.misterjones.org
 [51.254.78.96])
        (using TLSv1.2 with cipher ECDHE-RSA-AES256-GCM-SHA384 (256/256 bits))
        (No client certificate requested)
        by mail.kernel.org (Postfix) with ESMTPSA id BBAA620777;
        Fri, 20 Mar 2020 18:24:34 +0000 (UTC)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple; d=kernel.org;
        s=default; t=1584728674;
        bh=5jJuGUFWRJ2T6vmHdTiGNL4skAtWIsvs2wOH9lZnqqU=;
        h=From:To:Cc:Subject:Date:In-Reply-To:References:From;
        b=an0+lGJLD4divYQLnhALD81ChVtAXsT4s3pOr9DJ6ocJPA11eaBb+nGoEVniGh7cT
         alq39eCAkOTHhW88fLeqvCsMflnS1dOv3yd5QQM5QsD72qeu0f643jvxtrq7y/cuNH
         fBiUiTpACwkuYKglEM1Jk28Wqubc2mFzJeio4ZmQ=
Received: from 78.163-31-62.static.virginmediabusiness.co.uk ([62.31.163.78]
 helo=why.lan)
        by disco-boy.misterjones.org with esmtpsa
 (TLS1.3:ECDHE_RSA_AES_256_GCM_SHA384:256)
        (Exim 4.92)
        (envelope-from <maz@kernel.org>)
        id 1jFMJt-00EKAx-1f; Fri, 20 Mar 2020 18:24:33 +0000
From: Marc Zyngier <maz@kernel.org>
To: linux-arm-kernel@lists.infradead.org, kvmarm@lists.cs.columbia.edu,
        kvm@vger.kernel.org, linux-kernel@vger.kernel.org
Cc: Lorenzo Pieralisi <lorenzo.pieralisi@arm.com>,
        Jason Cooper <jason@lakedaemon.net>,
        Thomas Gleixner <tglx@linutronix.de>,
        Zenghui Yu <yuzenghui@huawei.com>,
        Eric Auger <eric.auger@redhat.com>,
        James Morse <james.morse@arm.com>,
        Julien Thierry <julien.thierry.kdev@gmail.com>,
        Suzuki K Poulose <suzuki.poulose@arm.com>
Subject: [PATCH v6 01/23] irqchip/gic-v3: Use SGIs without active state if
 offered
Date: Fri, 20 Mar 2020 18:23:44 +0000
Message-Id: <20200320182406.23465-2-maz@kernel.org>
X-Mailer: git-send-email 2.20.1
In-Reply-To: <20200320182406.23465-1-maz@kernel.org>
References: <20200320182406.23465-1-maz@kernel.org>
MIME-Version: 1.0
X-SA-Exim-Connect-IP: 62.31.163.78
X-SA-Exim-Rcpt-To: linux-arm-kernel@lists.infradead.org,
 kvmarm@lists.cs.columbia.edu, kvm@vger.kernel.org,
 linux-kernel@vger.kernel.org, lorenzo.pieralisi@arm.com,
 jason@lakedaemon.net, tglx@linutronix.de, yuzenghui@huawei.com,
 eric.auger@redhat.com, james.morse@arm.com, julien.thierry.kdev@gmail.com,
 suzuki.poulose@arm.com
X-SA-Exim-Mail-From: maz@kernel.org
X-SA-Exim-Scanned: No (on disco-boy.misterjones.org);
 SAEximRunCond expanded to false
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

To allow the direct injection of SGIs into a guest, the GICv4.1
architecture has to sacrifice the Active state so that SGIs look
a lot like LPIs (they are injected by the same mechanism).

In order not to break existing software, the architecture gives
offers guests OSs the choice: SGIs with or without an active
state. It is the hypervisors duty to honor the guest's choice.

For this, the architecture offers a discovery bit indicating whether
the GIC supports GICv4.1 SGIs (GICD_TYPER2.nASSGIcap), and another
bit indicating whether the guest wants Active-less SGIs or not
(controlled by GICD_CTLR.nASSGIreq).

A hypervisor not supporting GICv4.1 SGIs would leave nASSGIcap
clear, and a guest not knowing about GICv4.1 SGIs (or definitely
wanting an Active state) would leave nASSGIreq clear (both being
thankfully backward compatible with older revisions of the GIC).

Since Linux is perfectly happy without an active state on SGIs,
inform the hypervisor that we'll use that if offered.

Signed-off-by: Marc Zyngier <maz@kernel.org>
Reviewed-by: Zenghui Yu <yuzenghui@huawei.com>
Link: https://lore.kernel.org/r/20200304203330.4967-2-maz@kernel.org
---
 drivers/irqchip/irq-gic-v3.c       | 10 ++++++++--
 include/linux/irqchip/arm-gic-v3.h |  2 ++
 2 files changed, 10 insertions(+), 2 deletions(-)

```
#### [PATCH 1/7] KVM: Fix out of range accesses to memslots
##### From: Sean Christopherson <sean.j.christopherson@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Sean Christopherson <sean.j.christopherson@intel.com>
X-Patchwork-Id: 11450357
Return-Path: <SRS0=CcrQ=5F=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 20C1613B1
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 20 Mar 2020 20:56:36 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 0A4A420775
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 20 Mar 2020 20:56:36 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727441AbgCTU4c (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 20 Mar 2020 16:56:32 -0400
Received: from mga11.intel.com ([192.55.52.93]:32133 "EHLO mga11.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726880AbgCTUzs (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 20 Mar 2020 16:55:48 -0400
IronPort-SDR: 
 zBOXt9AIK2pA/NfnUCLlmB88OZU4UxuqvreV8/at98T3h62uRy2txAGSjOODIIlCzO9UroCUrg
 UeqCv10w1bkA==
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from fmsmga002.fm.intel.com ([10.253.24.26])
  by fmsmga102.fm.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 20 Mar 2020 13:55:47 -0700
IronPort-SDR: 
 OUj5t6iz8d0eZtivRlx4QNpH4zqb8RymZ0YbZYk/OPYGii3ES4xsc5w3DGMWvQqAlBRFaZvkyg
 9q4P3wc+4UTw==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.72,285,1580803200";
   d="scan'208";a="280543317"
Received: from sjchrist-coffee.jf.intel.com ([10.54.74.202])
  by fmsmga002.fm.intel.com with ESMTP; 20 Mar 2020 13:55:47 -0700
From: Sean Christopherson <sean.j.christopherson@intel.com>
To: Christian Borntraeger <borntraeger@de.ibm.com>,
        Janosch Frank <frankja@linux.ibm.com>,
        Paolo Bonzini <pbonzini@redhat.com>
Cc: David Hildenbrand <david@redhat.com>,
        Cornelia Huck <cohuck@redhat.com>, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org, Qian Cai <cai@lca.pw>,
        Peter Xu <peterx@redhat.com>
Subject: [PATCH 1/7] KVM: Fix out of range accesses to memslots
Date: Fri, 20 Mar 2020 13:55:40 -0700
Message-Id: <20200320205546.2396-2-sean.j.christopherson@intel.com>
X-Mailer: git-send-email 2.24.1
In-Reply-To: <20200320205546.2396-1-sean.j.christopherson@intel.com>
References: <20200320205546.2396-1-sean.j.christopherson@intel.com>
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Reset the LRU slot if it becomes invalid when deleting a memslot to fix
an out-of-bounds/use-after-free access when searching through memslots.

Explicitly check for there being no used slots in search_memslots(), and
in the caller of s390's approximation variant.

Fixes: 36947254e5f9 ("KVM: Dynamically size memslot array based on number of used slots")
Reported-by: Qian Cai <cai@lca.pw>
Cc: Peter Xu <peterx@redhat.com>
Signed-off-by: Sean Christopherson <sean.j.christopherson@intel.com>
---
 arch/s390/kvm/kvm-s390.c | 3 +++
 include/linux/kvm_host.h | 3 +++
 virt/kvm/kvm_main.c      | 3 +++
 3 files changed, 9 insertions(+)

```
#### [PATCH] KVM: LAPIC: Mark hrtimer for period or oneshot mode to expire in hard interrupt context
##### From: <zhe.he@windriver.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: He Zhe <zhe.he@windriver.com>
X-Patchwork-Id: 11448485
Return-Path: <SRS0=CcrQ=5F=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 91E21913
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 20 Mar 2020 07:10:07 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 76E8920775
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 20 Mar 2020 07:10:07 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726809AbgCTHKE (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 20 Mar 2020 03:10:04 -0400
Received: from mail5.windriver.com ([192.103.53.11]:35148 "EHLO mail5.wrs.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726603AbgCTHKE (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 20 Mar 2020 03:10:04 -0400
Received: from ALA-HCA.corp.ad.wrs.com (ala-hca.corp.ad.wrs.com
 [147.11.189.40])
        by mail5.wrs.com (8.15.2/8.15.2) with ESMTPS id 02K76MJm001145
        (version=TLSv1 cipher=AES256-SHA bits=256 verify=FAIL);
        Fri, 20 Mar 2020 00:06:32 -0700
Received: from pek-lpg-core2.corp.ad.wrs.com (128.224.153.41) by
 ALA-HCA.corp.ad.wrs.com (147.11.189.40) with Microsoft SMTP Server id
 14.3.487.0; Fri, 20 Mar 2020 00:06:11 -0700
From: <zhe.he@windriver.com>
To: <pbonzini@redhat.com>, <sean.j.christopherson@intel.com>,
        <vkuznets@redhat.com>, <wanpengli@tencent.com>,
        <jmattson@google.com>, <joro@8bytes.org>, <tglx@linutronix.de>,
        <mingo@redhat.com>, <bp@alien8.de>, <hpa@zytor.com>,
        <x86@kernel.org>, <kvm@vger.kernel.org>,
        <linux-kernel@vger.kernel.org>, <bigeasy@linutronix.de>,
        <linux-rt-users@vger.kernel.org>, <zhe.he@windriver.com>
Subject: [PATCH] KVM: LAPIC: Mark hrtimer for period or oneshot mode to expire
 in hard interrupt context
Date: Fri, 20 Mar 2020 15:06:07 +0800
Message-ID: <1584687967-332859-1-git-send-email-zhe.he@windriver.com>
X-Mailer: git-send-email 2.7.4
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: He Zhe <zhe.he@windriver.com>

apic->lapic_timer.timer was initialized with HRTIMER_MODE_ABS_HARD but
started later with HRTIMER_MODE_ABS, which may cause the following warning
in PREEMPT_RT kernel.

WARNING: CPU: 1 PID: 2957 at kernel/time/hrtimer.c:1129 hrtimer_start_range_ns+0x348/0x3f0
CPU: 1 PID: 2957 Comm: qemu-system-x86 Not tainted 5.4.23-rt11 #1
Hardware name: Supermicro SYS-E300-9A-8C/A2SDi-8C-HLN4F, BIOS 1.1a 09/18/2018
RIP: 0010:hrtimer_start_range_ns+0x348/0x3f0
Code: 4d b8 0f 94 c1 0f b6 c9 e8 35 f1 ff ff 4c 8b 45
      b0 e9 3b fd ff ff e8 d7 3f fa ff 48 98 4c 03 34
      c5 a0 26 bf 93 e9 a1 fd ff ff <0f> 0b e9 fd fc ff
      ff 65 8b 05 fa b7 90 6d 89 c0 48 0f a3 05 60 91
RSP: 0018:ffffbc60026ffaf8 EFLAGS: 00010202
RAX: 0000000000000001 RBX: ffff9d81657d4110 RCX: 0000000000000000
RDX: 0000000000000000 RSI: 0000006cc7987bcf RDI: ffff9d81657d4110
RBP: ffffbc60026ffb58 R08: 0000000000000001 R09: 0000000000000010
R10: 0000000000000000 R11: 0000000000000000 R12: 0000006cc7987bcf
R13: 0000000000000000 R14: 0000006cc7987bcf R15: ffffbc60026d6a00
FS: 00007f401daed700(0000) GS:ffff9d81ffa40000(0000) knlGS:0000000000000000
CS: 0010 DS: 0000 ES: 0000 CR0: 0000000080050033
CR2: 00000000ffffffff CR3: 0000000fa7574000 CR4: 00000000003426e0
Call Trace:
? kvm_release_pfn_clean+0x22/0x60 [kvm]
start_sw_timer+0x85/0x230 [kvm]
? vmx_vmexit+0x1b/0x30 [kvm_intel]
kvm_lapic_switch_to_sw_timer+0x72/0x80 [kvm]
vmx_pre_block+0x1cb/0x260 [kvm_intel]
? vmx_vmexit+0xf/0x30 [kvm_intel]
? vmx_vmexit+0x1b/0x30 [kvm_intel]
? vmx_vmexit+0xf/0x30 [kvm_intel]
? vmx_vmexit+0x1b/0x30 [kvm_intel]
? vmx_vmexit+0xf/0x30 [kvm_intel]
? vmx_vmexit+0x1b/0x30 [kvm_intel]
? vmx_vmexit+0xf/0x30 [kvm_intel]
? vmx_vmexit+0xf/0x30 [kvm_intel]
? vmx_vmexit+0x1b/0x30 [kvm_intel]
? vmx_vmexit+0xf/0x30 [kvm_intel]
? vmx_vmexit+0x1b/0x30 [kvm_intel]
? vmx_vmexit+0xf/0x30 [kvm_intel]
? vmx_vmexit+0x1b/0x30 [kvm_intel]
? vmx_vmexit+0xf/0x30 [kvm_intel]
? vmx_vmexit+0x1b/0x30 [kvm_intel]
? vmx_vmexit+0xf/0x30 [kvm_intel]
? vmx_sync_pir_to_irr+0x9e/0x100 [kvm_intel]
? kvm_apic_has_interrupt+0x46/0x80 [kvm]
kvm_arch_vcpu_ioctl_run+0x85b/0x1fa0 [kvm]
? _raw_spin_unlock_irqrestore+0x18/0x50
? _copy_to_user+0x2c/0x30
kvm_vcpu_ioctl+0x235/0x660 [kvm]
? rt_spin_unlock+0x2c/0x50
do_vfs_ioctl+0x3e4/0x650
? __fget+0x7a/0xa0
ksys_ioctl+0x67/0x90
__x64_sys_ioctl+0x1a/0x20
do_syscall_64+0x4d/0x120
entry_SYSCALL_64_after_hwframe+0x44/0xa9
RIP: 0033:0x7f4027cc54a7
Code: 00 00 90 48 8b 05 e9 59 0c 00 64 c7 00 26 00 00
      00 48 c7 c0 ff ff ff ff c3 66 2e 0f 1f 84 00 00
      00 00 00 b8 10 00 00 00 0f 05 <48> 3d 01 f0 ff ff
      73 01 c3 48 8b 0d b9 59 0c 00 f7 d8 64 89 01 48
RSP: 002b:00007f401dae9858 EFLAGS: 00000246 ORIG_RAX: 0000000000000010
RAX: ffffffffffffffda RBX: 00005558bd029690 RCX: 00007f4027cc54a7
RDX: 0000000000000000 RSI: 000000000000ae80 RDI: 000000000000000d
RBP: 00007f4028b72000 R08: 00005558bc829ad0 R09: 00000000ffffffff
R10: 00005558bcf90ca0 R11: 0000000000000246 R12: 0000000000000000
R13: 0000000000000000 R14: 0000000000000000 R15: 00005558bce1c840
--[ end trace 0000000000000002 ]--

Signed-off-by: He Zhe <zhe.he@windriver.com>
Reviewed-by: Wanpeng Li <wanpengli@tencent.com>
---
 arch/x86/kvm/lapic.c | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
#### [PATCH] KVM: SVM: document KVM_MEM_ENCRYPT_OP, let userspace detect if SEV is available
##### From: Paolo Bonzini <pbonzini@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Paolo Bonzini <pbonzini@redhat.com>
X-Patchwork-Id: 11449973
Return-Path: <SRS0=CcrQ=5F=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 8995D6CA
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 20 Mar 2020 17:42:53 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 68A7B20775
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 20 Mar 2020 17:42:53 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="EXteLxpI"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726982AbgCTRmu (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 20 Mar 2020 13:42:50 -0400
Received: from us-smtp-delivery-74.mimecast.com ([63.128.21.74]:27504 "EHLO
        us-smtp-delivery-74.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1726814AbgCTRmu (ORCPT
        <rfc822;kvm@vger.kernel.org>); Fri, 20 Mar 2020 13:42:50 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1584726169;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc; bh=ef36637kDnXkE6FllS0yNPka1X9FChEYgiakf6+7Z7c=;
        b=EXteLxpIPtvpvuZEpCDVmeV2uOacj9OqidEjQBwSo0KCmWWQ8kt2vqFUnpSZGwDt0yEMd3
        IRCpOHiMq2I+M9RalrsJjo1bcIAnPTyQ9bP3KfBYw0td4tJtvxq6TSJhqqMLl4iElLatZD
        5fLn436FeLEV6dUcK5301FNIwD8T+uE=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-308-JCGm1F3lNn-DLjAE_M3WPg-1; Fri, 20 Mar 2020 13:42:47 -0400
X-MC-Unique: JCGm1F3lNn-DLjAE_M3WPg-1
Received: from smtp.corp.redhat.com (int-mx08.intmail.prod.int.phx2.redhat.com
 [10.5.11.23])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 97C389B823;
        Fri, 20 Mar 2020 17:42:46 +0000 (UTC)
Received: from virtlab701.virt.lab.eng.bos.redhat.com
 (virtlab701.virt.lab.eng.bos.redhat.com [10.19.152.228])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 3932D19757;
        Fri, 20 Mar 2020 17:42:46 +0000 (UTC)
From: Paolo Bonzini <pbonzini@redhat.com>
To: linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Cc: Brijesh Singh <brijesh.singh@amd.com>
Subject: [PATCH] KVM: SVM: document KVM_MEM_ENCRYPT_OP,
 let userspace detect if SEV is available
Date: Fri, 20 Mar 2020 13:42:45 -0400
Message-Id: <20200320174245.5220-1-pbonzini@redhat.com>
X-Scanned-By: MIMEDefang 2.84 on 10.5.11.23
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Userspace has no way to query if SEV has been disabled with the
sev module parameter of kvm-amd.ko.  Actually it has one, but it
is a hack: do ioctl(KVM_MEM_ENCRYPT_OP, NULL) and check if it
returns EFAULT.  Make it a little nicer by returning zero for
SEV enabled and NULL argument, and while at it document the
ioctl arguments.

Cc: Brijesh Singh <brijesh.singh@amd.com>
Signed-off-by: Paolo Bonzini <pbonzini@redhat.com>
Reviewed-by: Brijesh Singh <brijesh.singh@amd.com>
---
 .../virt/kvm/amd-memory-encryption.rst        | 25 +++++++++++++++++++
 arch/x86/kvm/svm.c                            |  3 +++
 2 files changed, 28 insertions(+)

```
#### [PATCH] KVM: SVM: Issue WBINVD after deactivating an SEV guest
##### From: Tom Lendacky <thomas.lendacky@amd.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Tom Lendacky <thomas.lendacky@amd.com>
X-Patchwork-Id: 11449711
Return-Path: <SRS0=CcrQ=5F=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 9D6661667
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 20 Mar 2020 16:07:30 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 739DB2076F
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 20 Mar 2020 16:07:30 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=amdcloud.onmicrosoft.com
 header.i=@amdcloud.onmicrosoft.com header.b="aFVwLwZL"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727140AbgCTQH1 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 20 Mar 2020 12:07:27 -0400
Received: from mail-mw2nam12on2055.outbound.protection.outlook.com
 ([40.107.244.55]:29205
        "EHLO NAM12-MW2-obe.outbound.protection.outlook.com"
        rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org with ESMTP
        id S1726801AbgCTQH1 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 20 Mar 2020 12:07:27 -0400
ARC-Seal: i=1; a=rsa-sha256; s=arcselector9901; d=microsoft.com; cv=none;
 b=MsQNDax5xu1dm77EI/fB1uAQwEwFdumaxqyJznNB0V0Kd1Xyf/14YgRxUX9hwEvv+VRfZPnQkKSFkUTJaEDJGWtlTlOQ0+xdV/lmrYa1YNw/KP/s/ig+f+q9Ga3evX/dx7Jxz7ZNYeimneV21yQcLsKVVq67d9c+aLqQZaAzmOSK6IGRZbh/i3JFX1314C7dIh6rCqGge9sZZAF8h9dGrqrJRDpmfktxkrJtR5A5juqMA76ZFrtb9kwcdwUMLTReN9NqKbRWptqcnksEhkzMuF1KzpwOGs+q8Xcrfu0dYBDPAvo6gW/S1lMGg/SO9sV4cO3kHxxpd7bA2WT9F63Klw==
ARC-Message-Signature: i=1; a=rsa-sha256; c=relaxed/relaxed; d=microsoft.com;
 s=arcselector9901;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=jcSUvjmPVj9MOMcNAcCDLYw3mDeUTIfAbz1UKrFI3qA=;
 b=CXUtdFAONT4YDOCnvWspuWBGvJCX1ooK6cg0TZZGlTLAeCEdh6VQbUouPd+jiB1DvylaIDq881tIzile4B6VeLPMVFxLQvWDcCFzJlrryXlfCxpcLLdp69WYRvdhhuh4ynLXtNTBxI6GqlK/vnLJXtL/gDDBBhQxRG+0WhP7MkeyM1ShnUcY+O8vgRfzbUYgJ27f45im+qxOAuoXZSdjIbfp2eNb/Q23TMp6WboO+6Ev3z2rv82eG4bY2quZdjuHWaKQYEnw4U6x88IBQD89VR+544sdh7GGXytgCIrBxKUsOdlQl6Vq0HDGFBtWZd18XPJrdO9MRxi6slIqckmA/w==
ARC-Authentication-Results: i=1; mx.microsoft.com 1; spf=pass
 smtp.mailfrom=amd.com; dmarc=pass action=none header.from=amd.com; dkim=pass
 header.d=amd.com; arc=none
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
 d=amdcloud.onmicrosoft.com; s=selector2-amdcloud-onmicrosoft-com;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=jcSUvjmPVj9MOMcNAcCDLYw3mDeUTIfAbz1UKrFI3qA=;
 b=aFVwLwZL946gHVMubM14TXpiE0auflm190KFCRw7Hq6lXgDzvigS5fV6Ah25I3NBvQ1gWH1wENRphkqac5IxjHgIjuC99ewBUYQTN57Ck9MvqEOPGvuats1Tuil3DtdQC/ropLOM3EH3btTHkSqwsp7EkLwV16IFUXxXiMGvnVQ=
Authentication-Results: spf=none (sender IP is )
 smtp.mailfrom=Thomas.Lendacky@amd.com;
Received: from DM6PR12MB3163.namprd12.prod.outlook.com (2603:10b6:5:15e::26)
 by DM6PR12MB4467.namprd12.prod.outlook.com (2603:10b6:5:2a8::14) with
 Microsoft SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.2835.19; Fri, 20 Mar
 2020 16:07:22 +0000
Received: from DM6PR12MB3163.namprd12.prod.outlook.com
 ([fe80::f0f9:a88f:f840:2733]) by DM6PR12MB3163.namprd12.prod.outlook.com
 ([fe80::f0f9:a88f:f840:2733%7]) with mapi id 15.20.2814.025; Fri, 20 Mar 2020
 16:07:22 +0000
From: Tom Lendacky <thomas.lendacky@amd.com>
To: kvm@vger.kernel.org, linux-kernel@vger.kernel.org
Cc: Paolo Bonzini <pbonzini@redhat.com>,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>,
        Brijesh Singh <brijesh.singh@amd.com>,
        David Rientjes <rientjes@google.com>
Subject: [PATCH] KVM: SVM: Issue WBINVD after deactivating an SEV guest
Date: Fri, 20 Mar 2020 11:07:07 -0500
Message-Id: 
 <c8bf9087ca3711c5770bdeaafa3e45b717dc5ef4.1584720426.git.thomas.lendacky@amd.com>
X-Mailer: git-send-email 2.17.1
X-ClientProxiedBy: DM6PR14CA0045.namprd14.prod.outlook.com
 (2603:10b6:5:18f::22) To DM6PR12MB3163.namprd12.prod.outlook.com
 (2603:10b6:5:15e::26)
MIME-Version: 1.0
X-MS-Exchange-MessageSentRepresentingType: 1
Received: from tlendack-t1.amd.com (165.204.77.1) by
 DM6PR14CA0045.namprd14.prod.outlook.com (2603:10b6:5:18f::22) with Microsoft
 SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.2835.19 via Frontend
 Transport; Fri, 20 Mar 2020 16:07:21 +0000
X-Mailer: git-send-email 2.17.1
X-Originating-IP: [165.204.77.1]
X-MS-PublicTrafficType: Email
X-MS-Office365-Filtering-HT: Tenant
X-MS-Office365-Filtering-Correlation-Id: 5038347a-264c-4821-946f-08d7cce8c5ad
X-MS-TrafficTypeDiagnostic: DM6PR12MB4467:|DM6PR12MB4467:
X-MS-Exchange-Transport-Forked: True
X-Microsoft-Antispam-PRVS: 
 <DM6PR12MB44679A0E04C7E1D40649C7DDECF50@DM6PR12MB4467.namprd12.prod.outlook.com>
X-MS-Oob-TLC-OOBClassifiers: OLM:6430;
X-Forefront-PRVS: 03484C0ABF
X-Forefront-Antispam-Report: 
 SFV:NSPM;SFS:(10009020)(4636009)(396003)(376002)(366004)(39860400002)(136003)(346002)(199004)(956004)(81156014)(16526019)(86362001)(4326008)(8676002)(2906002)(81166006)(186003)(52116002)(26005)(7696005)(6486002)(54906003)(478600001)(8936002)(316002)(2616005)(5660300002)(66946007)(36756003)(66556008)(66476007)(6666004)(136400200001);DIR:OUT;SFP:1101;SCL:1;SRVR:DM6PR12MB4467;H:DM6PR12MB3163.namprd12.prod.outlook.com;FPR:;SPF:None;LANG:en;PTR:InfoNoRecords;A:1;
Received-SPF: None (protection.outlook.com: amd.com does not designate
 permitted sender hosts)
X-MS-Exchange-SenderADCheck: 1
X-Microsoft-Antispam: BCL:0;
X-Microsoft-Antispam-Message-Info: 
 U9TykCzCiLrtdeeZPaZ0/b5Uoq3UmF/uQvCMZ9WWCswDO0hO6UHj/Xt/gYcf+beOsQNnFXb6fVnyx+Y/stw/JwKRkEi2xH9guO2mifnnXjBN0hvA5nzDAOc54rqcY6+nxMO8HTU1PazVafKAvgPnqqw3gLn+H0pH02O0rhoCh6HhJv6uyJm0VJku3JXc5+uipdUznConzXlEEGSBsjdb/FxJXo+oP8dZN3TXNBWapam0hrybawrNjoYA1u/JKknwseTWrY3sLygNsAa5LCMnYe6Vi5j+5e5n9Dev22tjySbsxXcsbZ++wn7g3iU2A0BYRoTqerP9LKrvHGzVgqNISaO9ov1+d5Y2FyiETv0yIoV0I861j/dzUNtE/ywSJL8oU7LbZGrg5jyRzQdK6cjo7KFtTYT8LJGBdnRFfa2Op1sBAdBwx9WgA2TJ+3/JEhOsBG/RIkQ9EDqrFuEg6UeVd7lNNoUEcVS9HDFMVFGA+FdlEySDCKxv0OKJnzKpa1/j
X-MS-Exchange-AntiSpam-MessageData: 
 ndNwna2iAeNBTdImWrM/PBzUDDArBm/RhqgADL7/vAMpnrj6ETEQtOvS3jdFIWDuqW9XB1Nt7EHfxFlXWGRi/smWGlCAnD+vXrDd1qZyx7L0WJT+8bzu/vvr8HO+Cdjxz0tdu+AoZq3vEda8eAol6Q==
X-OriginatorOrg: amd.com
X-MS-Exchange-CrossTenant-Network-Message-Id: 
 5038347a-264c-4821-946f-08d7cce8c5ad
X-MS-Exchange-CrossTenant-OriginalArrivalTime: 20 Mar 2020 16:07:21.9939
 (UTC)
X-MS-Exchange-CrossTenant-FromEntityHeader: Hosted
X-MS-Exchange-CrossTenant-Id: 3dd8961f-e488-4e60-8e11-a82d994e183d
X-MS-Exchange-CrossTenant-MailboxType: HOSTED
X-MS-Exchange-CrossTenant-UserPrincipalName: 
 5eN2YB/iNTM327zoNYjYHXVGywiwZJtow16YYW1PyZHDyNJtvwN6hVURwGEgUSPUVDBhHw2yVgatvSQdJBYuiw==
X-MS-Exchange-Transport-CrossTenantHeadersStamped: DM6PR12MB4467
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Currently, CLFLUSH is used to flush SEV guest memory before the guest is
terminated (or a memory hotplug region is removed). However, CLFLUSH is
not enough to ensure that SEV guest tagged data is flushed from the cache.

With 33af3a7ef9e6 ("KVM: SVM: Reduce WBINVD/DF_FLUSH invocations"), the
original WBINVD was removed. This then exposed crashes at random times
because of a cache flush race with a page that had both a hypervisor and
a guest tag in the cache.

Restore the WBINVD when destroying an SEV guest and add a WBINVD to the
svm_unregister_enc_region() function to ensure hotplug memory is flushed
when removed. The DF_FLUSH can still be avoided at this point.

Fixes: 33af3a7ef9e6 ("KVM: SVM: Reduce WBINVD/DF_FLUSH invocations")
Signed-off-by: Tom Lendacky <thomas.lendacky@amd.com>
Acked-by: David Rientjes <rientjes@google.com>
---
 arch/x86/kvm/svm.c | 22 ++++++++++++++--------
 1 file changed, 14 insertions(+), 8 deletions(-)

```
#### [kvm-unit-tests PATCH] x86: Add tests for user-mode CET
##### From: Yang Weijiang <weijiang.yang@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Yang Weijiang <weijiang.yang@intel.com>
X-Patchwork-Id: 11448367
Return-Path: <SRS0=CcrQ=5F=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id CE40292A
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 20 Mar 2020 03:41:05 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id A6DA62076C
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 20 Mar 2020 03:41:05 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727340AbgCTDlE (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 19 Mar 2020 23:41:04 -0400
Received: from mga01.intel.com ([192.55.52.88]:27908 "EHLO mga01.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1727297AbgCTDlD (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 19 Mar 2020 23:41:03 -0400
IronPort-SDR: 
 UMtGCS3GgoAvCsPkY+JWCORDMfxZ+4WM49KJPnJJyc9uY+EizaCLPHLKJXft7hnTVm8FDDRBIk
 gLbl7fWvdKhg==
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from orsmga002.jf.intel.com ([10.7.209.21])
  by fmsmga101.fm.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 19 Mar 2020 20:41:02 -0700
IronPort-SDR: 
 mg1tMDhMILjFXiZzJxABp+sUbHpvmJ/ZCo5zCNgd2+abd3h7ziaZv6hmECdhPntDuggwhgxmUE
 y1wMQHPJZs2w==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.72,283,1580803200";
   d="scan'208";a="263945633"
Received: from local-michael-cet-test.sh.intel.com ([10.239.159.128])
  by orsmga002.jf.intel.com with ESMTP; 19 Mar 2020 20:40:59 -0700
From: Yang Weijiang <weijiang.yang@intel.com>
To: kvm@vger.kernel.org, linux-kernel@vger.kernel.org,
        sean.j.christopherson@intel.com, pbonzini@redhat.com,
        jmattson@google.com
Cc: yu.c.zhang@linux.intel.com, Yang Weijiang <weijiang.yang@intel.com>
Subject: [kvm-unit-tests PATCH] x86: Add tests for user-mode CET
Date: Fri, 20 Mar 2020 11:43:42 +0800
Message-Id: <20200320034342.26610-10-weijiang.yang@intel.com>
X-Mailer: git-send-email 2.17.2
In-Reply-To: <20200320034342.26610-1-weijiang.yang@intel.com>
References: <20200320034342.26610-1-weijiang.yang@intel.com>
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This unit-test is intended to test user-mode CET support of KVM,
it's tested on Intel new platform. Two CET features: Shadow Stack
Protection(SHSTK) and Indirect-Branch Tracking(IBT) are enclosed.

In SHSTK test, if the function return-address in normal stack is
tampered with a value not equal to the one on shadow-stack, #CP
(Control Protection Exception)will generated on function returning.
This feature is supported by processor itself, no compiler/link
option is required.

However, to enabled IBT, we need to add -fcf-protection=full in
compiler options, this makes the compiler insert endbr64 at the
very beginning of each jmp/call target given the binary is for
x86_64.

To get PASS results, the following conditions must be met:
1) The processor is powered with CET feature.
2) The kernel is patched with the latest CET kernel patches.
3) The KVM and QEMU are patched with the latest CET patches.
4) Use CET-enabled gcc to compile the test app.

Signed-off-by: Yang Weijiang <weijiang.yang@intel.com>
---
 lib/x86/desc.c      |   2 +
 lib/x86/msr.h       |   2 +
 lib/x86/processor.h |   3 +
 x86/Makefile.common |   3 +-
 x86/Makefile.x86_64 |   3 +-
 x86/cet.c           | 212 ++++++++++++++++++++++++++++++++++++++++++++
 x86/unittests.cfg   |   6 ++
 7 files changed, 229 insertions(+), 2 deletions(-)
 create mode 100644 x86/cet.c

```
#### [PATCH v3 01/37] KVM: VMX: Flush all EPTP/VPID contexts on remote TLB flush
##### From: Sean Christopherson <sean.j.christopherson@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Sean Christopherson <sean.j.christopherson@intel.com>
X-Patchwork-Id: 11450459
Return-Path: <SRS0=CcrQ=5F=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 3E7B9913
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 20 Mar 2020 21:31:50 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 286A220775
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 20 Mar 2020 21:31:50 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727054AbgCTV2o (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 20 Mar 2020 17:28:44 -0400
Received: from mga01.intel.com ([192.55.52.88]:48422 "EHLO mga01.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726801AbgCTV2o (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 20 Mar 2020 17:28:44 -0400
IronPort-SDR: 
 WZ3M7p7Pw+L5IFaElIQ6M0/G/r+wQOzsJuUrlUQelK8StVsWEmgvM+UKQyRE/SfjKywTBl5mp4
 zAdrr1SCaBlA==
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from fmsmga004.fm.intel.com ([10.253.24.48])
  by fmsmga101.fm.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 20 Mar 2020 14:28:43 -0700
IronPort-SDR: 
 kRg8672Th143DJPmBX2VmGiCrlwhtjjkTJigxEvDm1JPKQi0yDQ8opP6TPhCTWf6MhrFKkyet6
 Pu7xCLHfsJkw==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.72,286,1580803200";
   d="scan'208";a="269224393"
Received: from sjchrist-coffee.jf.intel.com ([10.54.74.202])
  by fmsmga004.fm.intel.com with ESMTP; 20 Mar 2020 14:28:42 -0700
From: Sean Christopherson <sean.j.christopherson@intel.com>
To: Paolo Bonzini <pbonzini@redhat.com>
Cc: Sean Christopherson <sean.j.christopherson@intel.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org, Ben Gardon <bgardon@google.com>,
        Junaid Shahid <junaids@google.com>,
        Liran Alon <liran.alon@oracle.com>,
        Boris Ostrovsky <boris.ostrovsky@oracle.com>,
        John Haxby <john.haxby@oracle.com>,
        Miaohe Lin <linmiaohe@huawei.com>,
        Tom Lendacky <thomas.lendacky@amd.com>
Subject: [PATCH v3 01/37] KVM: VMX: Flush all EPTP/VPID contexts on remote TLB
 flush
Date: Fri, 20 Mar 2020 14:27:57 -0700
Message-Id: <20200320212833.3507-2-sean.j.christopherson@intel.com>
X-Mailer: git-send-email 2.24.1
In-Reply-To: <20200320212833.3507-1-sean.j.christopherson@intel.com>
References: <20200320212833.3507-1-sean.j.christopherson@intel.com>
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Flush all EPTP/VPID contexts if a TLB flush _may_ have been triggered by
a remote or deferred TLB flush, i.e. by KVM_REQ_TLB_FLUSH.  Remote TLB
flushes require all contexts to be invalidated, not just the active
contexts, e.g. all mappings in all contexts for a given HVA need to be
invalidated on a mmu_notifier invalidation.  Similarly, the instigator
of the deferred TLB flush may be expecting all contexts to be flushed,
e.g. vmx_vcpu_load_vmcs().

Without nested VMX, flushing only the current EPTP/VPID context isn't
problematic because KVM uses a constant VPID for each vCPU, and
mmu_alloc_direct_roots() all but guarantees KVM will use a single EPTP
for L1.  In the rare case where a different EPTP is created or reused,
KVM (currently) unconditionally flushes the new EPTP context prior to
entering the guest.

With nested VMX, KVM conditionally uses a different VPID for L2, and
unconditionally uses a different EPTP for L2.  Because KVM doesn't
_intentionally_ guarantee L2's EPTP/VPID context is flushed on nested
VM-Enter, it'd be possible for a malicious L1 to attack the host and/or
different VMs by exploiting the lack of flushing for L2.

  1) Launch nested guest from malicious L1.

  2) Nested VM-Enter to L2.

  3) Access target GPA 'g'.  CPU inserts TLB entry tagged with L2's ASID
     mapping 'g' to host PFN 'x'.

  2) Nested VM-Exit to L1.

  3) L1 triggers kernel same-page merging (ksm) by duplicating/zeroing
     the page for PFN 'x'.

  4) Host kernel merges PFN 'x' with PFN 'y', i.e. unmaps PFN 'x' and
     remaps the page to PFN 'y'.  mmu_notifier sends invalidate command,
     KVM flushes TLB only for L1's ASID.

  4) Host kernel reallocates PFN 'x' to some other task/guest.

  5) Nested VM-Enter to L2.  KVM does not invalidate L2's EPTP or VPID.

  6) L2 accesses GPA 'g' and gains read/write access to PFN 'x' via its
     stale TLB entry.

However, current KVM unconditionally flushes L1's EPTP/VPID context on
nested VM-Exit.  But, that behavior is mostly unintentional, KVM doesn't
go out of its way to flush EPTP/VPID on nested VM-Enter/VM-Exit, rather
a TLB flush is guaranteed to occur prior to re-entering L1 due to
__kvm_mmu_new_cr3() always being called with skip_tlb_flush=false.  On
nested VM-Enter, this happens via kvm_init_shadow_ept_mmu() (nested EPT
enabled) or in nested_vmx_load_cr3() (nested EPT disabled).  On nested
VM-Exit it occurs via nested_vmx_load_cr3().

This also fixes a bug where a deferred TLB flush in the context of L2,
with EPT disabled, would flush L1's VPID instead of L2's VPID, as
vmx_flush_tlb() flushes L1's VPID regardless of is_guest_mode().

Cc: Vitaly Kuznetsov <vkuznets@redhat.com>
Cc: Ben Gardon <bgardon@google.com>
Cc: Jim Mattson <jmattson@google.com>
Cc: Junaid Shahid <junaids@google.com>
Cc: Liran Alon <liran.alon@oracle.com>
Cc: Boris Ostrovsky <boris.ostrovsky@oracle.com>
Cc: John Haxby <john.haxby@oracle.com>
Reviewed-by: Liran Alon <liran.alon@oracle.com>
Fixes: efebf0aaec3d ("KVM: nVMX: Do not flush TLB on L1<->L2 transitions if L1 uses VPID and EPT")
Signed-off-by: Sean Christopherson <sean.j.christopherson@intel.com>
---
 arch/x86/kvm/vmx/vmx.h | 28 +++++++++++++++++++++++++++-
 1 file changed, 27 insertions(+), 1 deletion(-)

```
#### [RFC PATCH v2.1] x86/sev-es: Handle NMI State
##### From: Joerg Roedel <joro@8bytes.org>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Joerg Roedel <joro@8bytes.org>
X-Patchwork-Id: 11449103
Return-Path: <SRS0=CcrQ=5F=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 07A271668
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 20 Mar 2020 13:17:15 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id E432A2076E
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 20 Mar 2020 13:17:14 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727514AbgCTNRN (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 20 Mar 2020 09:17:13 -0400
Received: from 8bytes.org ([81.169.241.247]:54470 "EHLO theia.8bytes.org"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1727502AbgCTNRL (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 20 Mar 2020 09:17:11 -0400
Received: by theia.8bytes.org (Postfix, from userid 1000)
        id EDAE0364; Fri, 20 Mar 2020 14:17:09 +0100 (CET)
Date: Fri, 20 Mar 2020 14:17:07 +0100
From: Joerg Roedel <joro@8bytes.org>
To: Andy Lutomirski <luto@kernel.org>
Cc: X86 ML <x86@kernel.org>, "H. Peter Anvin" <hpa@zytor.com>,
        Dave Hansen <dave.hansen@linux.intel.com>,
        Peter Zijlstra <peterz@infradead.org>,
        Thomas Hellstrom <thellstrom@vmware.com>,
        Jiri Slaby <jslaby@suse.cz>,
        Dan Williams <dan.j.williams@intel.com>,
        Tom Lendacky <thomas.lendacky@amd.com>,
        Juergen Gross <jgross@suse.com>,
        Kees Cook <keescook@chromium.org>,
        LKML <linux-kernel@vger.kernel.org>,
        kvm list <kvm@vger.kernel.org>,
        Linux Virtualization <virtualization@lists.linux-foundation.org>,
        Joerg Roedel <jroedel@suse.de>
Subject: [RFC PATCH v2.1] x86/sev-es: Handle NMI State
Message-ID: <20200320131707.GF5122@8bytes.org>
References: <20200319091407.1481-1-joro@8bytes.org>
 <20200319091407.1481-71-joro@8bytes.org>
 <CALCETrUOQneBHjoZkP-7T5PDijb=WOyv7xF7TD0GLR2Aw77vyA@mail.gmail.com>
MIME-Version: 1.0
Content-Disposition: inline
In-Reply-To: 
 <CALCETrUOQneBHjoZkP-7T5PDijb=WOyv7xF7TD0GLR2Aw77vyA@mail.gmail.com>
User-Agent: Mutt/1.10.1 (2018-07-13)
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

On Thu, Mar 19, 2020 at 08:35:59AM -0700, Andy Lutomirski wrote:
> 1. Just put the NMI unmask in do_nmi().  The kernel *already* knows
> how to handle running do_nmi() with NMIs unmasked.  This is much, much
> simpler than your code.

Okay, attached is the updated patch which implements this approach. I
tested it in an SEV-ES guest with 'perf top' running for a little more
than 30 minutes and all looked good. I also removed the dead code from
the patch.


From ec3b021c5d9130fd66e00d823c4fabc675c4b49e Mon Sep 17 00:00:00 2001
From: Joerg Roedel <jroedel@suse.de>
Date: Tue, 28 Jan 2020 17:31:05 +0100
Subject: [PATCH] x86/sev-es: Handle NMI State

When running under SEV-ES the kernel has to tell the hypervisor when to
open the NMI window again after an NMI was injected. This is done with
an NMI-complete message to the hypervisor.

Add code to the kernels NMI handler to send this message right at the
beginning of do_nmi(). This always allows nesting NMIs.

Signed-off-by: Joerg Roedel <jroedel@suse.de>
---
 arch/x86/include/asm/sev-es.h   |  2 ++
 arch/x86/include/uapi/asm/svm.h |  1 +
 arch/x86/kernel/nmi.c           |  8 ++++++++
 arch/x86/kernel/sev-es.c        | 18 ++++++++++++++++++
 4 files changed, 29 insertions(+)

```
#### [PATCH v10 01/13] iommu: Introduce attach/detach_pasid_table API
##### From: Eric Auger <eric.auger@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Eric Auger <eric.auger@redhat.com>
X-Patchwork-Id: 11449727
Return-Path: <SRS0=CcrQ=5F=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 5DE42913
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 20 Mar 2020 16:10:10 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 3342720767
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 20 Mar 2020 16:10:10 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="g+p8hTHD"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727494AbgCTQKB (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 20 Mar 2020 12:10:01 -0400
Received: from us-smtp-delivery-74.mimecast.com ([63.128.21.74]:40477 "EHLO
        us-smtp-delivery-74.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1727459AbgCTQKA (ORCPT
        <rfc822;kvm@vger.kernel.org>); Fri, 20 Mar 2020 12:10:00 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1584720599;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding:
         in-reply-to:in-reply-to:references:references;
        bh=JAARb2bDHN2gV5fR00RfsJLGfx43dK1dtt9u5n9rt+0=;
        b=g+p8hTHDiT7U3/msmTpKa7Du8dYAJIpqBJkzwSZ3JNxxPntBt2029+fc+Zng6IUkegJWuM
        I7vrNn9IbrWpvWa2ky/8kC7c6WPeF7aClHw3OEIQzQ29vNceSeMAFn889wuB3Ce1sEKhlw
        JX22V7esW14qvS5PvFYiNb37a6qfMrE=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-340-WLd3y5XyNlO4oGuT5jdzkQ-1; Fri, 20 Mar 2020 12:09:53 -0400
X-MC-Unique: WLd3y5XyNlO4oGuT5jdzkQ-1
Received: from smtp.corp.redhat.com (int-mx06.intmail.prod.int.phx2.redhat.com
 [10.5.11.16])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 62F831137846;
        Fri, 20 Mar 2020 16:09:50 +0000 (UTC)
Received: from laptop.redhat.com (ovpn-113-142.ams2.redhat.com
 [10.36.113.142])
        by smtp.corp.redhat.com (Postfix) with ESMTP id D50735C1D8;
        Fri, 20 Mar 2020 16:09:46 +0000 (UTC)
From: Eric Auger <eric.auger@redhat.com>
To: eric.auger.pro@gmail.com, eric.auger@redhat.com,
        iommu@lists.linux-foundation.org, linux-kernel@vger.kernel.org,
        kvm@vger.kernel.org, kvmarm@lists.cs.columbia.edu, joro@8bytes.org,
        alex.williamson@redhat.com, jacob.jun.pan@linux.intel.com,
        yi.l.liu@intel.com, jean-philippe.brucker@arm.com,
        will.deacon@arm.com, robin.murphy@arm.com
Cc: marc.zyngier@arm.com, peter.maydell@linaro.org,
        zhangfei.gao@gmail.com
Subject: [PATCH v10 01/13] iommu: Introduce attach/detach_pasid_table API
Date: Fri, 20 Mar 2020 17:09:20 +0100
Message-Id: <20200320160932.27222-2-eric.auger@redhat.com>
In-Reply-To: <20200320160932.27222-1-eric.auger@redhat.com>
References: <20200320160932.27222-1-eric.auger@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.16
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Jacob Pan <jacob.jun.pan@linux.intel.com>

In virtualization use case, when a guest is assigned
a PCI host device, protected by a virtual IOMMU on the guest,
the physical IOMMU must be programmed to be consistent with
the guest mappings. If the physical IOMMU supports two
translation stages it makes sense to program guest mappings
onto the first stage/level (ARM/Intel terminology) while the host
owns the stage/level 2.

In that case, it is mandated to trap on guest configuration
settings and pass those to the physical iommu driver.

This patch adds a new API to the iommu subsystem that allows
to set/unset the pasid table information.

A generic iommu_pasid_table_config struct is introduced in
a new iommu.h uapi header. This is going to be used by the VFIO
user API.

Signed-off-by: Jean-Philippe Brucker <jean-philippe.brucker@arm.com>
Signed-off-by: Liu, Yi L <yi.l.liu@linux.intel.com>
Signed-off-by: Ashok Raj <ashok.raj@intel.com>
Signed-off-by: Jacob Pan <jacob.jun.pan@linux.intel.com>
Signed-off-by: Eric Auger <eric.auger@redhat.com>
Reviewed-by: Jean-Philippe Brucker <jean-philippe.brucker@arm.com>
---
 drivers/iommu/iommu.c      | 19 ++++++++++++++
 include/linux/iommu.h      | 18 ++++++++++++++
 include/uapi/linux/iommu.h | 51 ++++++++++++++++++++++++++++++++++++++
 3 files changed, 88 insertions(+)

```
#### [PATCH v10 01/11] vfio: VFIO_IOMMU_SET_PASID_TABLE
##### From: Eric Auger <eric.auger@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Eric Auger <eric.auger@redhat.com>
X-Patchwork-Id: 11449777
Return-Path: <SRS0=CcrQ=5F=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 5B6556CA
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 20 Mar 2020 16:20:03 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 3AA1C20753
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 20 Mar 2020 16:20:03 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="bfFZOk7B"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727562AbgCTQUC (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 20 Mar 2020 12:20:02 -0400
Received: from us-smtp-delivery-74.mimecast.com ([63.128.21.74]:36229 "EHLO
        us-smtp-delivery-74.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1727317AbgCTQUB (ORCPT
        <rfc822;kvm@vger.kernel.org>); Fri, 20 Mar 2020 12:20:01 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1584721201;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding:
         in-reply-to:in-reply-to:references:references;
        bh=IqrZ5PAivz8D0DNnQlULxvOl6hsl7punh73vFXG+XJQ=;
        b=bfFZOk7BWsH8CzDW6/gEQOVASUkV0gLxA3wLtnT2DiIvecDeaHsHzwieorgDOOpXMh2N8g
        KWlESlBlJ8M9UrXJtb3XsnEDPwNNY0sfXLgK5SvTqvMAlYPrKFr+j1yraiWisR/YZ7CuBb
        kHiplQA8NSc5btlUG7hZUclSOyf9pao=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-168-HCiK2-sHOu2SSnIYOI-GIg-1; Fri, 20 Mar 2020 12:19:56 -0400
X-MC-Unique: HCiK2-sHOu2SSnIYOI-GIg-1
Received: from smtp.corp.redhat.com (int-mx02.intmail.prod.int.phx2.redhat.com
 [10.5.11.12])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 42559149C1;
        Fri, 20 Mar 2020 16:19:32 +0000 (UTC)
Received: from laptop.redhat.com (ovpn-113-142.ams2.redhat.com
 [10.36.113.142])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 91F1760BFB;
        Fri, 20 Mar 2020 16:19:25 +0000 (UTC)
From: Eric Auger <eric.auger@redhat.com>
To: eric.auger.pro@gmail.com, eric.auger@redhat.com,
        iommu@lists.linux-foundation.org, linux-kernel@vger.kernel.org,
        kvm@vger.kernel.org, kvmarm@lists.cs.columbia.edu, joro@8bytes.org,
        alex.williamson@redhat.com, jacob.jun.pan@linux.intel.com,
        yi.l.liu@intel.com, jean-philippe.brucker@arm.com,
        will.deacon@arm.com, robin.murphy@arm.com
Cc: marc.zyngier@arm.com, peter.maydell@linaro.org,
        zhangfei.gao@gmail.com
Subject: [PATCH v10 01/11] vfio: VFIO_IOMMU_SET_PASID_TABLE
Date: Fri, 20 Mar 2020 17:19:01 +0100
Message-Id: <20200320161911.27494-2-eric.auger@redhat.com>
In-Reply-To: <20200320161911.27494-1-eric.auger@redhat.com>
References: <20200320161911.27494-1-eric.auger@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.12
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: "Liu, Yi L" <yi.l.liu@linux.intel.com>

This patch adds an VFIO_IOMMU_SET_PASID_TABLE ioctl
which aims to pass the virtual iommu guest configuration
to the host. This latter takes the form of the so-called
PASID table.

Signed-off-by: Jacob Pan <jacob.jun.pan@linux.intel.com>
Signed-off-by: Liu, Yi L <yi.l.liu@linux.intel.com>
Signed-off-by: Eric Auger <eric.auger@redhat.com>
---
v8 -> v9:
- Merge VFIO_IOMMU_ATTACH/DETACH_PASID_TABLE into a single
  VFIO_IOMMU_SET_PASID_TABLE ioctl.

v6 -> v7:
- add a comment related to VFIO_IOMMU_DETACH_PASID_TABLE

v3 -> v4:
- restore ATTACH/DETACH
- add unwind on failure

v2 -> v3:
- s/BIND_PASID_TABLE/SET_PASID_TABLE

v1 -> v2:
- s/BIND_GUEST_STAGE/BIND_PASID_TABLE
- remove the struct device arg
---
 drivers/vfio/vfio_iommu_type1.c | 56 +++++++++++++++++++++++++++++++++
 include/uapi/linux/vfio.h       | 19 +++++++++++
 2 files changed, 75 insertions(+)

```
#### [PATCH] vfio-mdev: support mediated device creation in kernelFrom: Yonghyun Hwang <yonghyun@google.com>
##### From: Yonghyun Hwang <yonghyun@google.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Yonghyun Hwang <yonghyun@google.com>
X-Patchwork-Id: 11449981
Return-Path: <SRS0=CcrQ=5F=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 33923913
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 20 Mar 2020 17:59:20 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 121C720739
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 20 Mar 2020 17:59:20 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=google.com header.i=@google.com
 header.b="WwkwjMkf"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727196AbgCTR7T (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 20 Mar 2020 13:59:19 -0400
Received: from mail-pf1-f201.google.com ([209.85.210.201]:53089 "EHLO
        mail-pf1-f201.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726816AbgCTR7S (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 20 Mar 2020 13:59:18 -0400
Received: by mail-pf1-f201.google.com with SMTP id g8so5054478pfo.19
        for <kvm@vger.kernel.org>; Fri, 20 Mar 2020 10:59:17 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=date:message-id:mime-version:subject:from:to:cc;
        bh=BFKQlA+rN199Va5nr23TqQIycC+OcxA0r1dVNGT3ndc=;
        b=WwkwjMkfWqynU21gEP781F/xVflZE/NNYGlclPqx9ywAgFasUK5BRdkXiEO/2xQ/51
         2Xk+I1WmJSTBxZiaAzPm3nOr365l+PvdkDSfwjOffNT14H0bSUgVbnqgzdLZBbSUtblu
         2+q3FcoYntWBHEqeBZX0kD3P3w8IFRnrL/yzHF8z2OC5mIdPjHvKW49zgEFueK/7tqn3
         ivhbjPu2byo3GLM7K29s3buNddcau6QtYP6Ct5Kb20HEE86ZUHq2pmykK4Zq1snArdQC
         W2Z3eKS9C+DQ6DwdtmMUc9IVpbSyWXWGW6upL7+iaciknJSb47en+Syvht6qk55+takl
         4yDg==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:date:message-id:mime-version:subject:from:to:cc;
        bh=BFKQlA+rN199Va5nr23TqQIycC+OcxA0r1dVNGT3ndc=;
        b=eXKVF6YlYtvCmDKFJdu0PT6vKAHn99zs66DxYmbde4e4x6uakyxktBoXm1VRwuX9gl
         l4lMaouDF6tyvNL8OwA0bpn7H5N9CUpLKf8HBDlEiUSZlkb+eVj6Uyib+wutc27dXkrw
         0rmNlTP152DGB1TD5fCssgshu8zOHITmt/vxK36UEfuqrZZARCNE17J7/LTDMIDHIWvJ
         1Ya2yMTf6abf1Vqik0EAi2lRlQ0ScfuuU5UpEfcD0eEvoh2xl0BzQIcEhXAwOfOabRrh
         QPXV2OxBXnPlyYtWp/BthzpN9x8Wk0NnpaN4qZEoIW792eyhr1M957JsSu7/gcgXxcsJ
         piSQ==
X-Gm-Message-State: ANhLgQ2VvD20SMHjzsY+UoI6tSmTnrKUv51WMCRufa9epo82ml3FHMig
        uHT1QvwZ4YigiTC4Pc4VxI+adYR3Cs0D2Q==
X-Google-Smtp-Source: 
 ADFU+vs8Z2St3JcTr4qu4OOe01NMcgpT5FDfG+os5ZS9ricqsq1zYpSsmAAH0fUB4R4FqDOC2oN6QmtHff8a8w==
X-Received: by 2002:a17:90a:d205:: with SMTP id
 o5mr10592978pju.46.1584727157226;
 Fri, 20 Mar 2020 10:59:17 -0700 (PDT)
Date: Fri, 20 Mar 2020 10:59:10 -0700
Message-Id: <20200320175910.180266-1-yonghyun@google.com>
Mime-Version: 1.0
X-Mailer: git-send-email 2.25.1.696.g5e7596f4ac-goog
Subject: [PATCH] vfio-mdev: support mediated device creation in kernel
From: Yonghyun Hwang <yonghyun@google.com>
To: Kirti Wankhede <kwankhede@nvidia.com>,
        Alex Williamson <alex.williamson@redhat.com>,
        Cornelia Huck <cohuck@redhat.com>, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org,
        Havard Skinnemoen <hskinnemoen@google.com>,
        Moritz Fischer <mdf@kernel.org>
Cc: Yonghyun Hwang <yonghyun@google.com>
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

To enable a mediated device, a device driver registers its device to VFIO
MDev framework. Once the mediated device gets enabled, UUID gets fed onto
the sysfs attribute, "create", to create the mediated device. This
additional step happens after boot-up gets complete. If the driver knows
how many mediated devices need to be created during probing time, the
additional step becomes cumbersome. This commit implements a new function
to allow the driver to create a mediated device in kernel.

Signed-off-by: Yonghyun Hwang <yonghyun@google.com>
---
 drivers/vfio/mdev/mdev_core.c | 45 +++++++++++++++++++++++++++++++++++
 include/linux/mdev.h          |  3 +++
 2 files changed, 48 insertions(+)

```
#### [RESEND][patch V3 01/23] rcu: Dont acquire lock in NMI handler in rcu_nmi_enter_common()
##### From: Thomas Gleixner <tglx@linutronix.de>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Thomas Gleixner <tglx@linutronix.de>
X-Patchwork-Id: 11450519
Return-Path: <SRS0=CcrQ=5F=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 17B7B159A
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 20 Mar 2020 22:05:32 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 012E221473
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 20 Mar 2020 22:05:32 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727721AbgCTWFV (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 20 Mar 2020 18:05:21 -0400
Received: from Galois.linutronix.de ([193.142.43.55]:37498 "EHLO
        Galois.linutronix.de" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1727411AbgCTWEQ (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 20 Mar 2020 18:04:16 -0400
Received: from p5de0bf0b.dip0.t-ipconnect.de ([93.224.191.11]
 helo=nanos.tec.linutronix.de)
        by Galois.linutronix.de with esmtpsa
 (TLS1.2:DHE_RSA_AES_256_CBC_SHA256:256)
        (Exim 4.80)
        (envelope-from <tglx@linutronix.de>)
        id 1jFPk1-0004TO-DC; Fri, 20 Mar 2020 23:03:45 +0100
Received: from nanos.tec.linutronix.de (localhost [IPv6:::1])
        by nanos.tec.linutronix.de (Postfix) with ESMTP id DCEF61039FC;
        Fri, 20 Mar 2020 23:03:44 +0100 (CET)
Message-Id: <20200320180032.523372590@linutronix.de>
User-Agent: quilt/0.65
Date: Fri, 20 Mar 2020 18:59:57 +0100
From: Thomas Gleixner <tglx@linutronix.de>
To: LKML <linux-kernel@vger.kernel.org>
Cc: x86@kernel.org, Paul McKenney <paulmck@kernel.org>,
        Josh Poimboeuf <jpoimboe@redhat.com>,
        "Joel Fernandes (Google)" <joel@joelfernandes.org>,
        "Steven Rostedt (VMware)" <rostedt@goodmis.org>,
        Masami Hiramatsu <mhiramat@kernel.org>,
        Alexei Starovoitov <ast@kernel.org>,
        Frederic Weisbecker <frederic@kernel.org>,
        Mathieu Desnoyers <mathieu.desnoyers@efficios.com>,
        Brian Gerst <brgerst@gmail.com>,
        Juergen Gross <jgross@suse.com>,
        Alexandre Chartre <alexandre.chartre@oracle.com>,
        Peter Zijlstra <peterz@infradead.org>,
        Tom Lendacky <thomas.lendacky@amd.com>,
        Paolo Bonzini <pbonzini@redhat.com>, kvm@vger.kernel.org
Subject: [RESEND][patch V3 01/23] rcu: Dont acquire lock in NMI handler in
 rcu_nmi_enter_common()
References: <20200320175956.033706968@linutronix.de>
MIME-Version: 1.0
Content-transfer-encoding: 8-bit
X-Linutronix-Spam-Score: -1.0
X-Linutronix-Spam-Level: -
X-Linutronix-Spam-Status: No , -1.0 points, 5.0 required,
  ALL_TRUSTED=-1,SHORTCIRCUIT=-0.0001
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: "Paul E. McKenney" <paulmck@kernel.org>

The rcu_nmi_enter_common() function can be invoked both in interrupt
and NMI handlers.  If it is invoked from process context (as opposed
to userspace or idle context) on a nohz_full CPU, it might acquire the
CPU's leaf rcu_node structure's ->lock.  Because this lock is held only
with interrupts disabled, this is safe from an interrupt handler, but
doing so from an NMI handler can result in self-deadlock.

This commit therefore adds "irq" to the "if" condition so as to only
acquire the ->lock from irq handlers or process context, never from
an NMI handler.

Fixes: 5b14557b073c ("rcu: Avoid tick_dep_set_cpu() misordering")
Reported-by: Thomas Gleixner <tglx@linutronix.de>
Signed-off-by: Paul E. McKenney <paulmck@kernel.org>
Signed-off-by: Thomas Gleixner <tglx@linutronix.de>
Reviewed-by: Joel Fernandes (Google) <joel@joelfernandes.org>
Link: https://lkml.kernel.org/r/20200313024046.27622-1-paulmck@kernel.org
---
 kernel/rcu/tree.c |    2 +-
```
#### [PATCH v9 1/6] x86/kvm/hyper-v: Explicitly align hcall param for kvm_hyperv_exit
##### From: Jon Doron <arilou@gmail.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Jon Doron <arilou@gmail.com>
X-Patchwork-Id: 11449959
Return-Path: <SRS0=CcrQ=5F=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 5120F17E6
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 20 Mar 2020 17:28:53 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 3110820767
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 20 Mar 2020 17:28:53 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=gmail.com header.i=@gmail.com
 header.b="k8BJZ4XI"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727041AbgCTR2w (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 20 Mar 2020 13:28:52 -0400
Received: from mail-wr1-f66.google.com ([209.85.221.66]:42499 "EHLO
        mail-wr1-f66.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726814AbgCTR2v (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 20 Mar 2020 13:28:51 -0400
Received: by mail-wr1-f66.google.com with SMTP id v11so8473082wrm.9;
        Fri, 20 Mar 2020 10:28:50 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=from:to:cc:subject:date:message-id:in-reply-to:references
         :mime-version:content-transfer-encoding;
        bh=qORovMW4qFXFXcdoIljFzjQs+83nq3xI2+7AeVXu0Jo=;
        b=k8BJZ4XIzMUsdagDL0oFf2+WVUil6hLei1zA5A8UsReL31QvYybLJA3oP2gIlhD9b4
         A1WHbLZbmJ02lpfpLj2rRRx19teXV/8qMfVkG5XDWYCOYbiYGY/WcxPrXhi3Mj6Egak2
         EJpB8Vl7TEdh75LIgRVMdbPF/UdhGzcUzVmIAerMNuwegLdN+uvz+J0T4VyzRorPOnyu
         ICUMnVmc1XcOeLiCG4FTYcGifqv09UtveNFKA0HLjxoNs2WyBmyU1lK4kGr5vjteKtTe
         TjFJtY7ESlqxoJCirbrOGlAGsirbt/Ms9HuBHunZg2oSv4wFsyitmgkf5C1ilCTduHiv
         7kAw==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:in-reply-to
         :references:mime-version:content-transfer-encoding;
        bh=qORovMW4qFXFXcdoIljFzjQs+83nq3xI2+7AeVXu0Jo=;
        b=SdJe7WJF9LR13w5j2cGxD8pvqTygmX1DQOwnn47F1W9+0qAeRE9YfNkevUbXbLC6QP
         EcL8w6pWxVRlzczeHDauq/aK8mXSplRIeHOJHiMNMYOl1RjAa9G6eSi8MuiZbTq9/c0V
         ZRTepfSIQDpAsCEbg5hpf0ZHGwNL6vDIZmC51sNjVKq8PCHoqXGfCz3H3GLoqyqJOWl8
         KcJOpwYy3zq9EUq2gVHqprWZhPYPiTFX7iF5vw/1/VbQUa3wvETav2UxzHCLgexzvPoP
         0YjliNzTrGOlT8jTiKi9FO69E+OBJ++rA68TZ09YBdWI2VJo/cBVNpvtNb6BC2AU0qdH
         wH3Q==
X-Gm-Message-State: ANhLgQ183uxXiRylsQZ6TL1EY8Me0CoLdBSLGEjakGp32tKOAJpu+Czu
        bKKsojL4l/tkVYrqBcbkgv9mZl5JATE=
X-Google-Smtp-Source: 
 ADFU+vtaj++CrMMhqZXo7hw9Nyt36fJSsYzaZNL6R8wlkUfeeJDDTJl7vl16D+1AoJDsCn6dr/sjzg==
X-Received: by 2002:adf:cd04:: with SMTP id w4mr12707952wrm.280.1584725329242;
        Fri, 20 Mar 2020 10:28:49 -0700 (PDT)
Received: from jondnuc.lan (IGLD-84-229-155-229.inter.net.il.
 [84.229.155.229])
        by smtp.gmail.com with ESMTPSA id
 q4sm11028333wmj.1.2020.03.20.10.28.48
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Fri, 20 Mar 2020 10:28:48 -0700 (PDT)
From: Jon Doron <arilou@gmail.com>
To: kvm@vger.kernel.org, linux-hyperv@vger.kernel.org
Cc: vkuznets@redhat.com, Jon Doron <arilou@gmail.com>
Subject: [PATCH v9 1/6] x86/kvm/hyper-v: Explicitly align hcall param for
 kvm_hyperv_exit
Date: Fri, 20 Mar 2020 19:28:34 +0200
Message-Id: <20200320172839.1144395-2-arilou@gmail.com>
X-Mailer: git-send-email 2.24.1
In-Reply-To: <20200320172839.1144395-1-arilou@gmail.com>
References: <20200320172839.1144395-1-arilou@gmail.com>
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

Signed-off-by: Jon Doron <arilou@gmail.com>
---
 Documentation/virt/kvm/api.rst | 2 ++
 include/uapi/linux/kvm.h       | 2 ++
 2 files changed, 4 insertions(+)

```
