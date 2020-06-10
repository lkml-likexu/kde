#### [PATCH 1/2] KVM: arm64: Make vcpu_cp1x() work on Big Endian hosts
##### From: Marc Zyngier <maz@kernel.org>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Marc Zyngier <maz@kernel.org>
X-Patchwork-Id: 11594921
Return-Path: <SRS0=0yM6=7W=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 9867F912
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue,  9 Jun 2020 08:49:47 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 739C62081A
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue,  9 Jun 2020 08:49:47 +0000 (UTC)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple; d=kernel.org;
	s=default; t=1591692587;
	bh=X59E0JdQCbUCQrXwXF6MsA/SOxG0/0G1ya5dh8JIgH8=;
	h=From:To:Cc:Subject:Date:In-Reply-To:References:List-ID:From;
	b=RulkFqyzarv6uwB3/eS9myvCb38yKdy7lZceGyIQaVOMamvltla4QrnoGUGOUjB8M
	 jvgFgY4n4E9SSmxIWB7RQ4LddBptEfQggxVINKQUXC5TOcx0UEUgXeApoEKOlRfGmK
	 F1KbnShA1wJ0egOECNaJhv43yFn+KXSQ6vRjpduw=
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728344AbgFIItp (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 9 Jun 2020 04:49:45 -0400
Received: from mail.kernel.org ([198.145.29.99]:38274 "EHLO mail.kernel.org"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1727124AbgFIItm (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 9 Jun 2020 04:49:42 -0400
Received: from disco-boy.misterjones.org (disco-boy.misterjones.org
 [51.254.78.96])
        (using TLSv1.2 with cipher ECDHE-RSA-AES256-GCM-SHA384 (256/256 bits))
        (No client certificate requested)
        by mail.kernel.org (Postfix) with ESMTPSA id 81E60207ED;
        Tue,  9 Jun 2020 08:49:41 +0000 (UTC)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple; d=kernel.org;
        s=default; t=1591692581;
        bh=X59E0JdQCbUCQrXwXF6MsA/SOxG0/0G1ya5dh8JIgH8=;
        h=From:To:Cc:Subject:Date:In-Reply-To:References:From;
        b=csXoyx6NoetAEumOCwv3V2U08twEkRIfcS+FHU1N0YUiPJgmGLDBJ92AhSmlBKgtf
         yS/+g+zgl2B0wn3f6HmJW+AmecyxIFq6Npn7rzKTblk13J0KWFehuvF21TQX37+EhC
         U3Fj21L2cC73mDm+i2G0P7uH+WC9r7ZCiqlga4Y8=
Received: from 78.163-31-62.static.virginmediabusiness.co.uk ([62.31.163.78]
 helo=why.lan)
        by disco-boy.misterjones.org with esmtpsa
 (TLS1.3:ECDHE_RSA_AES_256_GCM_SHA384:256)
        (Exim 4.92)
        (envelope-from <maz@kernel.org>)
        id 1jiZwy-001PEa-2e; Tue, 09 Jun 2020 09:49:40 +0100
From: Marc Zyngier <maz@kernel.org>
To: kvmarm@lists.cs.columbia.edu, kvm@vger.kernel.org,
        linux-arm-kernel@lists.infradead.org
Cc: James Morse <james.morse@arm.com>,
        Julien Thierry <julien.thierry.kdev@gmail.com>,
        Suzuki K Poulose <suzuki.poulose@arm.com>,
        kernel-team@android.com, stable@vger.kernel.org
Subject: [PATCH 1/2] KVM: arm64: Make vcpu_cp1x() work on Big Endian hosts
Date: Tue,  9 Jun 2020 09:49:20 +0100
Message-Id: <20200609084921.1448445-2-maz@kernel.org>
X-Mailer: git-send-email 2.26.2
In-Reply-To: <20200609084921.1448445-1-maz@kernel.org>
References: <20200609084921.1448445-1-maz@kernel.org>
MIME-Version: 1.0
X-SA-Exim-Connect-IP: 62.31.163.78
X-SA-Exim-Rcpt-To: kvmarm@lists.cs.columbia.edu, kvm@vger.kernel.org,
 linux-arm-kernel@lists.infradead.org, james.morse@arm.com,
 julien.thierry.kdev@gmail.com, suzuki.poulose@arm.com,
 kernel-team@android.com, stable@vger.kernel.org
X-SA-Exim-Mail-From: maz@kernel.org
X-SA-Exim-Scanned: No (on disco-boy.misterjones.org);
 SAEximRunCond expanded to false
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

AArch32 CP1x registers are overlayed on their AArch64 counterparts
in the vcpu struct. This leads to an interesting problem as they
are stored in their CPU-local format, and thus a CP1x register
doesn't "hit" the lower 32bit portion of the AArch64 register on
a BE host.

To workaround this unfortunate situation, introduce a bias trick
in the vcpu_cp1x() accessors which picks the correct half of the
64bit register.

Cc: stable@vger.kernel.org
Reported-by: James Morse <james.morse@arm.com>
Signed-off-by: Marc Zyngier <maz@kernel.org>
---
 arch/arm64/include/asm/kvm_host.h | 10 ++++++++--
 1 file changed, 8 insertions(+), 2 deletions(-)

```
#### [PATCH] KVM: nVMX: Wrap VM-Fail valid path in generic VM-Fail helper
##### From: Sean Christopherson <sean.j.christopherson@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Sean Christopherson <sean.j.christopherson@intel.com>
X-Patchwork-Id: 11594273
Return-Path: <SRS0=0yM6=7W=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 29E18138C
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue,  9 Jun 2020 01:56:31 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 0A79D2078B
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue,  9 Jun 2020 01:56:31 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726992AbgFIB4J (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 8 Jun 2020 21:56:09 -0400
Received: from mga17.intel.com ([192.55.52.151]:53926 "EHLO mga17.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726887AbgFIB4I (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 8 Jun 2020 21:56:08 -0400
IronPort-SDR: 
 JHcyhO/3m2nGyZjtjBcI+SYwiI1uk4NXysBs/l88sYDPz1/y2hzXwSFWy9Glw2giDKNQl7O3Sm
 byz/I/ykzdpQ==
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from orsmga002.jf.intel.com ([10.7.209.21])
  by fmsmga107.fm.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 08 Jun 2020 18:56:07 -0700
IronPort-SDR: 
 PgR7H+/r10o+UHFp4bMpZMT7Lfs8UvfXoFBE09iEk7o7Rp7FfIRkdZG8U6dt8jGXfv9+93YFPA
 tmP7YDWhmqaQ==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.73,490,1583222400";
   d="scan'208";a="288665884"
Received: from sjchrist-coffee.jf.intel.com ([10.54.74.152])
  by orsmga002.jf.intel.com with ESMTP; 08 Jun 2020 18:56:07 -0700
From: Sean Christopherson <sean.j.christopherson@intel.com>
To: Paolo Bonzini <pbonzini@redhat.com>
Cc: Sean Christopherson <sean.j.christopherson@intel.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org
Subject: [PATCH] KVM: nVMX: Wrap VM-Fail valid path in generic VM-Fail helper
Date: Mon,  8 Jun 2020 18:56:07 -0700
Message-Id: <20200609015607.6994-1-sean.j.christopherson@intel.com>
X-Mailer: git-send-email 2.26.0
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Add nested_vmx_fail() to wrap VM-Fail paths that _may_ result in VM-Fail
Valid to make it clear at the call sites that the Valid flavor isn't
guaranteed.

Suggested-by: Vitaly Kuznetsov <vkuznets@redhat.com>
Signed-off-by: Sean Christopherson <sean.j.christopherson@intel.com>
Reviewed-by: Jim Mattson <jmattson@google.com>
---
 arch/x86/kvm/vmx/nested.c | 77 ++++++++++++++++++---------------------
 1 file changed, 36 insertions(+), 41 deletions(-)

```
#### [PATCH] KVM: VMX: Add helpers to identify interrupt type from intr_info
##### From: Sean Christopherson <sean.j.christopherson@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Sean Christopherson <sean.j.christopherson@intel.com>
X-Patchwork-Id: 11594271
Return-Path: <SRS0=0yM6=7W=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 1C53F912
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue,  9 Jun 2020 01:45:35 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 0D21720775
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue,  9 Jun 2020 01:45:35 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727059AbgFIBpU (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 8 Jun 2020 21:45:20 -0400
Received: from mga04.intel.com ([192.55.52.120]:54511 "EHLO mga04.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726960AbgFIBpT (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 8 Jun 2020 21:45:19 -0400
IronPort-SDR: 
 xRMh9Wg0VFmghwz9T2LkQQfCG/Wf3uKhrsi+QjdGJwX3jv+Lw4gvbzroIjUrYnJMkPhmeeg3RU
 XhVGVEIak5ig==
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from fmsmga005.fm.intel.com ([10.253.24.32])
  by fmsmga104.fm.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 08 Jun 2020 18:45:19 -0700
IronPort-SDR: 
 6auMffpAHogoNZdLl96kRkubZyKX4oa5v+nSnAF+pPNwWyX+wnId7tR9InfHw38JwO2kjvDYu0
 ZI5vPhlTbXyA==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.73,490,1583222400";
   d="scan'208";a="472909050"
Received: from sjchrist-coffee.jf.intel.com ([10.54.74.152])
  by fmsmga005.fm.intel.com with ESMTP; 08 Jun 2020 18:45:19 -0700
From: Sean Christopherson <sean.j.christopherson@intel.com>
To: Paolo Bonzini <pbonzini@redhat.com>
Cc: Sean Christopherson <sean.j.christopherson@intel.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org
Subject: [PATCH] KVM: VMX: Add helpers to identify interrupt type from
 intr_info
Date: Mon,  8 Jun 2020 18:45:18 -0700
Message-Id: <20200609014518.26756-1-sean.j.christopherson@intel.com>
X-Mailer: git-send-email 2.26.0
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Add is_intr_type() and is_intr_type_n() to consolidate the boilerplate
code for querying a specific type of interrupt given an encoded value
from VMCS.VM_{ENTER,EXIT}_INTR_INFO, with and without an associated
vector respectively.

Signed-off-by: Sean Christopherson <sean.j.christopherson@intel.com>
---

I wrote and proposed a version of this patch a while back[*], but AFAICT
never posted it as a formal patch.

[*] https://lkml.kernel.org/r/20190819233537.GG1916@linux.intel.com

 arch/x86/kvm/vmx/vmcs.h | 32 ++++++++++++++++++++------------
 1 file changed, 20 insertions(+), 12 deletions(-)

```
