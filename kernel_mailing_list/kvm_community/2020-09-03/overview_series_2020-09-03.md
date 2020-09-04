#### [PATCH 01/23] irqchip: Add Reduced Virtual Interrupt Controller driver
##### From: Marc Zyngier <maz@kernel.org>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Marc Zyngier <maz@kernel.org>
X-Patchwork-Id: 11754131
Return-Path: <SRS0=jm+8=CM=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 07EAC1575
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  3 Sep 2020 15:27:29 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id D5D92208C7
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  3 Sep 2020 15:27:28 +0000 (UTC)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple; d=kernel.org;
	s=default; t=1599146848;
	bh=dx03lYO45BaSF7PbrJoHAEWSdMagfqHrhZh0pzeUc2A=;
	h=From:To:Cc:Subject:Date:In-Reply-To:References:List-ID:From;
	b=0XyJccxrjO2tbR83J7pepfKW/OxAOHJL92abKhZBOSqRPfPW9LJKt42nO5Nvlarhf
	 8PSFe4QMxtGt0Nu2FjJzVgc1i0gTaF90pqJfUhh5kJjPF0L0Xu0rhAt1xnSEAE054A
	 5eJdhjirURsLZb6mQuEEtW3qfSkOH7CIz1Z0NLBM=
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729010AbgICP1R (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 3 Sep 2020 11:27:17 -0400
Received: from mail.kernel.org ([198.145.29.99]:42302 "EHLO mail.kernel.org"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1727786AbgICP0Y (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 3 Sep 2020 11:26:24 -0400
Received: from disco-boy.misterjones.org (disco-boy.misterjones.org
 [51.254.78.96])
        (using TLSv1.2 with cipher ECDHE-RSA-AES256-GCM-SHA384 (256/256 bits))
        (No client certificate requested)
        by mail.kernel.org (Postfix) with ESMTPSA id 3388E20786;
        Thu,  3 Sep 2020 15:26:23 +0000 (UTC)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple; d=kernel.org;
        s=default; t=1599146783;
        bh=dx03lYO45BaSF7PbrJoHAEWSdMagfqHrhZh0pzeUc2A=;
        h=From:To:Cc:Subject:Date:In-Reply-To:References:From;
        b=d/cumSf48v1zSIa0Sv8iWR6AvTERgVoDBKP9OFgw0SQTBD072ur1dBS7srs3u0Gm3
         x9guaYCU1Vwt+v5gAYcVApKvf+PLgW7CFiWWhc+CNiaBSAwDEhxdI7VW6JNmZQ3AJJ
         kGiYK8hlKVv6hHAwzReURj6gbnBN/PkykEOtR1zE=
Received: from 78.163-31-62.static.virginmediabusiness.co.uk ([62.31.163.78]
 helo=why.lan)
        by disco-boy.misterjones.org with esmtpsa
 (TLS1.3:ECDHE_RSA_AES_256_GCM_SHA384:256)
        (Exim 4.92)
        (envelope-from <maz@kernel.org>)
        id 1kDr81-008vT9-EX; Thu, 03 Sep 2020 16:26:21 +0100
From: Marc Zyngier <maz@kernel.org>
To: kvm@vger.kernel.org, kvmarm@lists.cs.columbia.edu,
        linux-arm-kernel@lists.infradead.org
Cc: kernel-team@android.com,
        Christoffer Dall <Christoffer.Dall@arm.com>,
        Lorenzo Pieralisi <lorenzo.pieralisi@arm.com>,
        James Morse <james.morse@arm.com>,
        Julien Thierry <julien.thierry.kdev@gmail.com>,
        Suzuki K Poulose <suzuki.poulose@arm.com>
Subject: [PATCH 01/23] irqchip: Add Reduced Virtual Interrupt Controller
 driver
Date: Thu,  3 Sep 2020 16:25:48 +0100
Message-Id: <20200903152610.1078827-2-maz@kernel.org>
X-Mailer: git-send-email 2.27.0
In-Reply-To: <20200903152610.1078827-1-maz@kernel.org>
References: <20200903152610.1078827-1-maz@kernel.org>
MIME-Version: 1.0
X-SA-Exim-Connect-IP: 62.31.163.78
X-SA-Exim-Rcpt-To: kvm@vger.kernel.org, kvmarm@lists.cs.columbia.edu,
 linux-arm-kernel@lists.infradead.org, kernel-team@android.com,
 Christoffer.Dall@arm.com, lorenzo.pieralisi@arm.com, james.morse@arm.com,
 julien.thierry.kdev@gmail.com, suzuki.poulose@arm.com
X-SA-Exim-Mail-From: maz@kernel.org
X-SA-Exim-Scanned: No (on disco-boy.misterjones.org);
 SAEximRunCond expanded to false
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The ARM rVIC is the simplest PV interrupt controller on this side
of the universe. I mean it!

Signed-off-by: Marc Zyngier <maz@kernel.org>
---
 drivers/irqchip/Kconfig          |   6 +
 drivers/irqchip/Makefile         |   1 +
 drivers/irqchip/irq-rvic.c       | 554 +++++++++++++++++++++++++++++++
 include/linux/cpuhotplug.h       |   1 +
 include/linux/irqchip/irq-rvic.h |  77 +++++
 5 files changed, 639 insertions(+)
 create mode 100644 drivers/irqchip/irq-rvic.c
 create mode 100644 include/linux/irqchip/irq-rvic.h

```
#### [PATCH] KVM: PPC: Book3S HV: Set LPCR[HDICE] before writing HDEC
##### From: Paul Mackerras <paulus@ozlabs.org>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Paul Mackerras <paulus@ozlabs.org>
X-Patchwork-Id: 11752597
Return-Path: <SRS0=jm+8=CM=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 51172109A
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  3 Sep 2020 07:55:49 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 2CA62208CA
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  3 Sep 2020 07:55:49 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=ozlabs.org header.i=@ozlabs.org
 header.b="pQ/e8HC6"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727989AbgICHzs (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 3 Sep 2020 03:55:48 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:60014 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1725943AbgICHzr (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 3 Sep 2020 03:55:47 -0400
Received: from ozlabs.org (bilbo.ozlabs.org [IPv6:2401:3900:2:1::2])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 30506C061244;
        Thu,  3 Sep 2020 00:55:47 -0700 (PDT)
Received: by ozlabs.org (Postfix, from userid 1003)
        id 4BhtQm5Y36z9sTS; Thu,  3 Sep 2020 17:55:44 +1000 (AEST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple; d=ozlabs.org; s=201707;
        t=1599119744; bh=jRwtZaqyDLSCz72Xr7M2N9uVo/tZDt0H0qRqtsza/Bc=;
        h=Date:From:To:Cc:Subject:From;
        b=pQ/e8HC6ttrrnnRVFDykJdAHgfhg36bjgP6Wg1KB2tP5ohAubzxIR/G0qXcX1xnBt
         WJikdvk39Hf4BmUy8MLo32+kdDA7l5Qmg0cbh4fDGR25LzGG5qpDF77EzPfe6QUSwO
         C1J9MO75Ljay2m9y+4t9ez0Hl+S/G570GguS0LaPoRjDyDKPblhakRYPXrRC2kGTUA
         ZDVU+/NesBfxA6gFh67qGVqGBUXbsqR4yll7ZvcRjRnMmmtiCiuCz+GkvrrwrQi8ld
         OLaASjb5S4buRUdpkzuLHgjJaT5ZecRtwKDQjfmFOWZQwy/HVDzTYDMn8E8oir5vV2
         cJr01SGGMO7rA==
Date: Thu, 3 Sep 2020 17:55:40 +1000
From: Paul Mackerras <paulus@ozlabs.org>
To: kvm-ppc@vger.kernel.org, kvm@vger.kernel.org
Cc: David Gibson <david@gibson.dropbear.id.au>
Subject: [PATCH] KVM: PPC: Book3S HV: Set LPCR[HDICE] before writing HDEC
Message-ID: <20200903075540.GI272502@thinks.paulus.ozlabs.org>
MIME-Version: 1.0
Content-Disposition: inline
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

POWER8 and POWER9 machines have a hardware deviation where generation
of a hypervisor decrementer exception is suppressed if the HDICE bit
in the LPCR register is 0 at the time when the HDEC register
decrements from 0 to -1.  When entering a guest, KVM first writes the
HDEC register with the time until it wants the CPU to exit the guest,
and then writes the LPCR with the guest value, which includes
HDICE = 1.  If HDEC decrements from 0 to -1 during the interval
between those two events, it is possible that we can enter the guest
with HDEC already negative but no HDEC exception pending, meaning that
no HDEC interrupt will occur while the CPU is in the guest, or at
least not until HDEC wraps around.  Thus it is possible for the CPU to
keep executing in the guest for a long time; up to about 4 seconds on
POWER8, or about 4.46 years on POWER9 (except that the host kernel
hard lockup detector will fire first).

To fix this, we set the LPCR[HDICE] bit before writing HDEC on guest
entry.

Signed-off-by: Paul Mackerras <paulus@ozlabs.org>
---
 arch/powerpc/kvm/book3s_hv.c            | 14 ++++++++++++--
 arch/powerpc/kvm/book3s_hv_interrupts.S |  9 ++++++---
 2 files changed, 18 insertions(+), 5 deletions(-)

```
#### [PATCH] KVM: x86: VMX: Make smaller physical guest address space support user-configurable
##### From: Mohammed Gamal <mgamal@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Mohammed Gamal <mgamal@redhat.com>
X-Patchwork-Id: 11753889
Return-Path: <SRS0=jm+8=CM=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id BE48B722
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  3 Sep 2020 14:53:48 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 9AA30208C7
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  3 Sep 2020 14:53:48 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="IEUXwMWc"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729333AbgICOxf (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 3 Sep 2020 10:53:35 -0400
Received: from us-smtp-2.mimecast.com ([205.139.110.61]:31993 "EHLO
        us-smtp-delivery-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S1729198AbgICOMD (ORCPT
        <rfc822;kvm@vger.kernel.org>); Thu, 3 Sep 2020 10:12:03 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1599142317;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=CT+BTbU04vXEyP9pdcH57nOtkyvU1kgH7PF3bGLUJr8=;
        b=IEUXwMWcXiIqHYPAIxe4CJSi7Eovn2LhMucfZrlKnWkjidGEHHygsX0Oln7ATTQj9qN+wZ
        qiqTPK0MWmY6IXIfoYdSQlQEmFiqys1I/T9PnrGjPLoPc4ryef2ioUCCIOUwGsqHLSbIxF
        3dGKMbnc5lBBG9Qe413Is9dsnynEsIw=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-92-gECEWAk0PASqH66S4LxuRQ-1; Thu, 03 Sep 2020 10:11:56 -0400
X-MC-Unique: gECEWAk0PASqH66S4LxuRQ-1
Received: from smtp.corp.redhat.com (int-mx08.intmail.prod.int.phx2.redhat.com
 [10.5.11.23])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 61C0510051D3;
        Thu,  3 Sep 2020 14:11:54 +0000 (UTC)
Received: from localhost.localdomain.com (ovpn-114-36.ams2.redhat.com
 [10.36.114.36])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 3160319C78;
        Thu,  3 Sep 2020 14:11:43 +0000 (UTC)
From: Mohammed Gamal <mgamal@redhat.com>
To: kvm@vger.kernel.org, pbonzini@redhat.com
Cc: linux-kernel@vger.kernel.org, sean.j.christopherson@intel.com,
        vkuznets@redhat.com, wanpengli@tencent.com, jmattson@google.com,
        joro@8bytes.org, Mohammed Gamal <mgamal@redhat.com>
Subject: [PATCH] KVM: x86: VMX: Make smaller physical guest address space
 support user-configurable
Date: Thu,  3 Sep 2020 16:11:22 +0200
Message-Id: <20200903141122.72908-1-mgamal@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.84 on 10.5.11.23
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This patch exposes allow_smaller_maxphyaddr to the user as a module parameter.

Since smaller physical address spaces are only supported on VMX, the parameter
is only exposed in the kvm_intel module.
Modifications to VMX page fault and EPT violation handling will depend on whether
that parameter is enabled.

Also disable support by default, and let the user decide if they want to enable
it.

Signed-off-by: Mohammed Gamal <mgamal@redhat.com>
---
 arch/x86/kvm/vmx/vmx.c | 15 ++++++---------
 arch/x86/kvm/vmx/vmx.h |  3 +++
 arch/x86/kvm/x86.c     |  2 +-
 3 files changed, 10 insertions(+), 10 deletions(-)

```
#### [PATCH 1/2] s390x: uv: Add destroy page call
##### From: Janosch Frank <frankja@linux.ibm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Janosch Frank <frankja@linux.ibm.com>
X-Patchwork-Id: 11753891
Return-Path: <SRS0=jm+8=CM=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 659B7722
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  3 Sep 2020 14:53:50 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 45E5C20786
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  3 Sep 2020 14:53:50 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=ibm.com header.i=@ibm.com
 header.b="n8IunAJE"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728913AbgICOxc (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 3 Sep 2020 10:53:32 -0400
Received: from mx0a-001b2d01.pphosted.com ([148.163.156.1]:51048 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1729348AbgICOxU (ORCPT
        <rfc822;kvm@vger.kernel.org>); Thu, 3 Sep 2020 10:53:20 -0400
Received: from pps.filterd (m0098404.ppops.net [127.0.0.1])
        by mx0a-001b2d01.pphosted.com (8.16.0.42/8.16.0.42) with SMTP id
 083DCrXw190943;
        Thu, 3 Sep 2020 09:15:06 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=ibm.com;
 h=from : to : cc : subject
 : date : message-id : in-reply-to : references : mime-version :
 content-transfer-encoding; s=pp1;
 bh=mwtDiKbzMzLqIeuSUmKOUDweb6dyUA6eoU+zVUlhshI=;
 b=n8IunAJEevLM46Y5DjEaFv8XdQDHX0m44JjF+HdQytEwKbmeUgJeQmAD+CHDHmUUUTS7
 onSdKAZXBmFE4YDiGvEgnwgmtu24mP2YRcJgHKMY+B30c29Fvlx5EP0v3lIDwCPHVnLZ
 d6Kz0i95qEUVWBJOiDYtlpcO2hSOVJCEJZ7YWHM+Z879WI7Ltl+W9Gtbk7+v7pPCOdXK
 h/VK9bAtHfReFPcv6rU4L44bv6taucx1JDJ3UfXQPu6v0P5VcVm+5UckRBGaeFkW++5a
 Qy9aqpfxSCPbSNZcIELlGvfZtH74qHBmbxnruye+3t5kLZrtNUxG+qGwZplyIJvc+hfu Gw==
Received: from pps.reinject (localhost [127.0.0.1])
        by mx0a-001b2d01.pphosted.com with ESMTP id 33b16081ua-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Thu, 03 Sep 2020 09:15:06 -0400
Received: from m0098404.ppops.net (m0098404.ppops.net [127.0.0.1])
        by pps.reinject (8.16.0.36/8.16.0.36) with SMTP id 083DCtQe191106;
        Thu, 3 Sep 2020 09:15:05 -0400
Received: from ppma06fra.de.ibm.com (48.49.7a9f.ip4.static.sl-reverse.com
 [159.122.73.72])
        by mx0a-001b2d01.pphosted.com with ESMTP id 33b16081sv-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Thu, 03 Sep 2020 09:15:05 -0400
Received: from pps.filterd (ppma06fra.de.ibm.com [127.0.0.1])
        by ppma06fra.de.ibm.com (8.16.0.42/8.16.0.42) with SMTP id
 083D7dl8009160;
        Thu, 3 Sep 2020 13:15:03 GMT
Received: from b06cxnps3074.portsmouth.uk.ibm.com
 (d06relay09.portsmouth.uk.ibm.com [9.149.109.194])
        by ppma06fra.de.ibm.com with ESMTP id 337e9h3kmm-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Thu, 03 Sep 2020 13:15:03 +0000
Received: from d06av26.portsmouth.uk.ibm.com (d06av26.portsmouth.uk.ibm.com
 [9.149.105.62])
        by b06cxnps3074.portsmouth.uk.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id 083DF04u29098408
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Thu, 3 Sep 2020 13:15:00 GMT
Received: from d06av26.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 7BFE1AE045;
        Thu,  3 Sep 2020 13:15:00 +0000 (GMT)
Received: from d06av26.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id C8536AE053;
        Thu,  3 Sep 2020 13:14:59 +0000 (GMT)
Received: from linux01.pok.stglabs.ibm.com (unknown [9.114.17.81])
        by d06av26.portsmouth.uk.ibm.com (Postfix) with ESMTP;
        Thu,  3 Sep 2020 13:14:59 +0000 (GMT)
From: Janosch Frank <frankja@linux.ibm.com>
To: linux-s390@vger.kernel.org
Cc: borntraeger@de.ibm.com, gor@linux.ibm.com, imbrenda@linux.ibm.com,
        kvm@vger.kernel.org, david@redhat.com
Subject: [PATCH 1/2] s390x: uv: Add destroy page call
Date: Thu,  3 Sep 2020 09:14:34 -0400
Message-Id: <20200903131435.2535-2-frankja@linux.ibm.com>
X-Mailer: git-send-email 2.25.1
In-Reply-To: <20200903131435.2535-1-frankja@linux.ibm.com>
References: <20200903131435.2535-1-frankja@linux.ibm.com>
MIME-Version: 1.0
X-TM-AS-GCONF: 00
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.235,18.0.687
 definitions=2020-09-03_06:2020-09-03,2020-09-03 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 suspectscore=1 mlxscore=0
 priorityscore=1501 lowpriorityscore=0 phishscore=0 spamscore=0
 impostorscore=0 clxscore=1015 bulkscore=0 malwarescore=0 mlxlogscore=999
 adultscore=0 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.12.0-2006250000 definitions=main-2009030117
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

We don't need to export pages if we destroy the VM configuration
afterwards anyway. Instead we can destroy the page which will zero it
and then make it accessible to the host.

Destroying is about twice as fast as the export.

Signed-off-by: Janosch Frank <frankja@linux.ibm.com>
Reviewed-by: Claudio Imbrenda <imbrenda@linux.ibm.com>
---
 arch/s390/include/asm/uv.h |  7 +++++++
 arch/s390/kernel/uv.c      | 21 +++++++++++++++++++++
 arch/s390/mm/gmap.c        |  2 +-
 3 files changed, 29 insertions(+), 1 deletion(-)

```
#### [PATCH v2] KVM: Check the allocation of pv cpu mask
##### From: Haiwei Li <lihaiwei.kernel@gmail.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Haiwei Li <lihaiwei.kernel@gmail.com>
X-Patchwork-Id: 11752171
Return-Path: <SRS0=jm+8=CM=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 4BD67138A
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  3 Sep 2020 01:59:25 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 33E3520786
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  3 Sep 2020 01:59:25 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=gmail.com header.i=@gmail.com
 header.b="iZyTWfoL"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727850AbgICB7V (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 2 Sep 2020 21:59:21 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:33888 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726177AbgICB7U (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 2 Sep 2020 21:59:20 -0400
Received: from mail-pj1-x1041.google.com (mail-pj1-x1041.google.com
 [IPv6:2607:f8b0:4864:20::1041])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id AF525C061244;
        Wed,  2 Sep 2020 18:59:20 -0700 (PDT)
Received: by mail-pj1-x1041.google.com with SMTP id g6so681789pjl.0;
        Wed, 02 Sep 2020 18:59:20 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=to:cc:from:subject:message-id:date:user-agent:mime-version
         :content-language:content-transfer-encoding;
        bh=HvNuZt8AdbQ59bEl2yv+x8KAP+HdurnJ4QylHSI1Jw0=;
        b=iZyTWfoL34ZD3AtkfjK4Vob+sMZOthj0FCXBVjQ69gyIn7b8LhJJhN1cTFdhFxwMmi
         0Fab62bpQrPcLwbiD3fOqok3FDs5gE25ZwJeZ4KEAHEoZAZegu/JfeifjdKe6AsgnH1G
         KLuzIQxuUq683FkB+bSVd422lwYW+3NU26ARFGiS4OuvOPdsk9XDo5PFQBuGd/vhyfzV
         X4FCxLmDvvHO67KjBjXp+unjmn30XiipXoJSqM6NSGd3MuQg3QYBE8TvM9pZFmKKJICD
         RvnH1z39804+mI71J1DFL5iWUv5vzfOwUnMh5yKONIJ3GedpOvzdfTX0Ted8bhzzAn9j
         0IVg==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:to:cc:from:subject:message-id:date:user-agent
         :mime-version:content-language:content-transfer-encoding;
        bh=HvNuZt8AdbQ59bEl2yv+x8KAP+HdurnJ4QylHSI1Jw0=;
        b=sJdT0FEHUNsaoxwx2P7ZSfLcRCOdi/n3PMc9Zsg29MB2D5DSrPt1TsB9vwXq/MhTzd
         whyPBt2gqCjebA1Og0me5yew1zO82YGh30RZy0YhZKIu9+BTxuUw/++mWaiZ6vtZ9eBR
         Dq8ZVt9NReZa266Xw26w2DGxvnH2QNXBEmEJDhlgJUBnOfMZLeIajLQXtvYGibyUoxxr
         BbRGfFF8ZJTBYryGNN4NjAbZG+SESVmNvISVapZqKmz1IoH/RJcPHOpkLw4686zW5+z4
         AYzcsiAFfw97wY8ihLANHJ3nt21yEUtBEtwz/8mZQUCw/iAwPYYBBfaNRMJFQfnZOPlN
         JYfw==
X-Gm-Message-State: AOAM531vSLmScCWY5N7XllxdWuWX2qirpLN9F0QN0UigidAT8nAK6fyy
        BTmRnHEBu7/sa0rct8TivQ==
X-Google-Smtp-Source: 
 ABdhPJwU2eKyicXIBEODibPKw990WbBr45xLwxtQkefF2dMzMcVA9hRRWPo2BRtt8ZjEAVe4HPZdsg==
X-Received: by 2002:a17:90a:9307:: with SMTP id
 p7mr707705pjo.105.1599098359776;
        Wed, 02 Sep 2020 18:59:19 -0700 (PDT)
Received: from [127.0.0.1] ([103.7.29.7])
        by smtp.gmail.com with ESMTPSA id
 n128sm891812pfd.29.2020.09.02.18.59.15
        (version=TLS1_3 cipher=TLS_AES_128_GCM_SHA256 bits=128/128);
        Wed, 02 Sep 2020 18:59:19 -0700 (PDT)
To: "linux-kernel@vger.kernel.org" <linux-kernel@vger.kernel.org>,
        "kvm@vger.kernel.org" <kvm@vger.kernel.org>,
        "x86@kernel.org" <x86@kernel.org>
Cc: "pbonzini@redhat.com" <pbonzini@redhat.com>,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        "vkuznets@redhat.com" <vkuznets@redhat.com>,
        "wanpengli@tencent.com" <wanpengli@tencent.com>,
        "jmattson@google.com" <jmattson@google.com>,
        "joro@8bytes.org" <joro@8bytes.org>, tglx@linutronix.de,
        mingo@redhat.com, "bp@alien8.de" <bp@alien8.de>,
        "hpa@zytor.com" <hpa@zytor.com>
From: Haiwei Li <lihaiwei.kernel@gmail.com>
Subject: [PATCH v2] KVM: Check the allocation of pv cpu mask
Message-ID: <654d8c60-49f0-e398-be25-24aed352360d@gmail.com>
Date: Thu, 3 Sep 2020 09:59:09 +0800
User-Agent: Mozilla/5.0 (Macintosh; Intel Mac OS X 10.15; rv:68.0)
 Gecko/20100101 Thunderbird/68.12.0
MIME-Version: 1.0
Content-Language: en-US
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Haiwei Li <lihaiwei@tencent.com>

check the allocation of per-cpu __pv_cpu_mask. Initialize ops only when
successful.

Signed-off-by: Haiwei Li <lihaiwei@tencent.com>
---
  arch/x86/kernel/kvm.c | 24 ++++++++++++++++++++----
  1 file changed, 20 insertions(+), 4 deletions(-)


@@ -654,7 +653,6 @@ static void __init kvm_guest_init(void)
  	}

  	if (pv_tlb_flush_supported()) {
-		pv_ops.mmu.flush_tlb_others = kvm_flush_tlb_others;
  		pv_ops.mmu.tlb_remove_table = tlb_remove_table;
  		pr_info("KVM setup pv remote TLB flush\n");
  	}
@@ -767,6 +765,14 @@ static __init int activate_jump_labels(void)
  }
  arch_initcall(activate_jump_labels);

+static void kvm_free_pv_cpu_mask(void)
+{
+	unsigned int cpu;
+
+	for_each_possible_cpu(cpu)
+		free_cpumask_var(per_cpu(__pv_cpu_mask, cpu));
+}
+
  static __init int kvm_alloc_cpumask(void)
  {
  	int cpu;
@@ -785,11 +791,21 @@ static __init int kvm_alloc_cpumask(void)

  	if (alloc)
  		for_each_possible_cpu(cpu) {
-			zalloc_cpumask_var_node(per_cpu_ptr(&__pv_cpu_mask, cpu),
-				GFP_KERNEL, cpu_to_node(cpu));
+			if (!zalloc_cpumask_var_node(
+				per_cpu_ptr(&__pv_cpu_mask, cpu),
+				GFP_KERNEL, cpu_to_node(cpu)))
+				goto zalloc_cpumask_fail;
  		}

+#if defined(CONFIG_SMP)
+	apic->send_IPI_mask_allbutself = kvm_send_ipi_mask_allbutself;
+#endif
+	pv_ops.mmu.flush_tlb_others = kvm_flush_tlb_others;
  	return 0;
+
+zalloc_cpumask_fail:
+	kvm_free_pv_cpu_mask();
+	return -ENOMEM;
  }
  arch_initcall(kvm_alloc_cpumask);

--
2.18.4

```
#### [PATCH v2] nSVM: Add a test for the P (present) bit in NPT entry
##### From: Krish Sadhukhan <krish.sadhukhan@oracle.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Krish Sadhukhan <krish.sadhukhan@oracle.com>
X-Patchwork-Id: 11752345
Return-Path: <SRS0=jm+8=CM=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 38D85722
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  3 Sep 2020 04:26:57 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 20B772072A
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  3 Sep 2020 04:26:57 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=oracle.com header.i=@oracle.com
 header.b="WkS7ePnX"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726047AbgICE0v (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 3 Sep 2020 00:26:51 -0400
Received: from aserp2120.oracle.com ([141.146.126.78]:36922 "EHLO
        aserp2120.oracle.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1725851AbgICE0u (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 3 Sep 2020 00:26:50 -0400
Received: from pps.filterd (aserp2120.oracle.com [127.0.0.1])
        by aserp2120.oracle.com (8.16.0.42/8.16.0.42) with SMTP id
 0831Oawc169739;
        Thu, 3 Sep 2020 01:29:10 GMT
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=oracle.com;
 h=from : to : cc :
 subject : date : message-id : in-reply-to : references; s=corp-2020-01-29;
 bh=8d2PA+bnb3BaMMxU1VUW8GlQFSzjZAyv9cMxQHig4i8=;
 b=WkS7ePnXeGzpc2eoVM/1PX9oczmvnD4z+3LMVEBp6hqvMfHPCBWEguPz6Q6cGAxJwJv/
 JvnnhIFT2k5c0O1ABQvmSvS5D6o6R5cLG6YR7XN5/A/Rfke9NB2NkMTG2U8sdnswnwXL
 ikdW0gmxv+6SV4pVlThWETodtUdjqdaSS51xsXj0WP0K5hPNPPbZ28xXqvUKaGd+qvd+
 sN2Ba/65OTTsJSMKkzVxkVJaTg7po6xo9a1wt7tfeRuv2Yqa6NXE95Gull4VCgZuPuCT
 6w4uzNZb7KaKIr+CxIofVeA2um39LdzThYuak4gYm06COjmxGE/EoliENKrOMdqPPPwU 9A==
Received: from aserp3020.oracle.com (aserp3020.oracle.com [141.146.126.70])
        by aserp2120.oracle.com with ESMTP id 337eymdwa5-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=FAIL);
        Thu, 03 Sep 2020 01:29:10 +0000
Received: from pps.filterd (aserp3020.oracle.com [127.0.0.1])
        by aserp3020.oracle.com (8.16.0.42/8.16.0.42) with SMTP id
 0831Oea1109426;
        Thu, 3 Sep 2020 01:29:10 GMT
Received: from userv0122.oracle.com (userv0122.oracle.com [156.151.31.75])
        by aserp3020.oracle.com with ESMTP id 3380x8cjh0-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Thu, 03 Sep 2020 01:29:10 +0000
Received: from abhmp0008.oracle.com (abhmp0008.oracle.com [141.146.116.14])
        by userv0122.oracle.com (8.14.4/8.14.4) with ESMTP id 0831T8Hm003229;
        Thu, 3 Sep 2020 01:29:08 GMT
Received: from nsvm-sadhukhan-1.osdevelopmeniad.oraclevcn.com
 (/100.100.230.216)
        by default (Oracle Beehive Gateway v4.0)
        with ESMTP ; Wed, 02 Sep 2020 18:29:08 -0700
From: Krish Sadhukhan <krish.sadhukhan@oracle.com>
To: kvm@vger.kernel.org
Cc: pbonzini@redhat.com, jmattson@google.com
Subject: [PATCH v2] nSVM: Add a test for the P (present) bit in NPT entry
Date: Thu,  3 Sep 2020 01:28:51 +0000
Message-Id: <20200903012851.22299-2-krish.sadhukhan@oracle.com>
X-Mailer: git-send-email 2.18.4
In-Reply-To: <20200903012851.22299-1-krish.sadhukhan@oracle.com>
References: <20200903012851.22299-1-krish.sadhukhan@oracle.com>
X-Proofpoint-Virus-Version: vendor=nai engine=6000 definitions=9732
 signatures=668679
X-Proofpoint-Spam-Details: rule=notspam policy=default score=0 mlxscore=0
 spamscore=0 phishscore=0
 mlxlogscore=999 adultscore=0 suspectscore=1 bulkscore=0 malwarescore=0
 classifier=spam adjust=0 reason=mlx scancount=1 engine=8.12.0-2006250000
 definitions=main-2009030010
X-Proofpoint-Virus-Version: vendor=nai engine=6000 definitions=9732
 signatures=668679
X-Proofpoint-Spam-Details: rule=notspam policy=default score=0 suspectscore=1
 adultscore=0
 priorityscore=1501 phishscore=0 mlxlogscore=999 mlxscore=0
 lowpriorityscore=0 clxscore=1015 spamscore=0 bulkscore=0 impostorscore=0
 malwarescore=0 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.12.0-2006250000 definitions=main-2009030009
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

If the P (present) bit in an NPT entry is cleared, page translation will
fail at the level where the final guest physical address is translated to
the host physical address and the guest will VMEXIT to the host with an
exit code of 0x400 (#NPF). Additionally, the EXITINFO1 field will have
the following bit pattern set on VMEXIT:

	Bit# 0: Cleared due to the nested page not being preset (P bit cleared)
	Bit# 1: Cleared due to the access to the NPT being a read-access
	Bit# 2: Set due to the access to the NPT by MMU is a user-level access
	Bit# 3: Cleared due to no reserved bits being set in the NPT entry
	Bit# 4: Cleared due to the NPT walk being a code-read-access
	Bit# 32: Set due to the NPF occurring at the level where the final
		 guest physical address gets translated to host physical address

Signed-off-by: Krish Sadhukhan <krish.sadhukhan@oracle.com>
---
 x86/svm_tests.c | 29 +++++++++++++++++++++++++++++
 1 file changed, 29 insertions(+)

```
#### [PATCH V3] kvm x86/mmu: use KVM_REQ_MMU_SYNC to sync when needed
##### From: Lai Jiangshan <jiangshanlai@gmail.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Lai Jiangshan <jiangshanlai@gmail.com>
X-Patchwork-Id: 11754089
Return-Path: <SRS0=jm+8=CM=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 700BD17D5
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  3 Sep 2020 15:23:32 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 56F48208B3
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  3 Sep 2020 15:23:32 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=gmail.com header.i=@gmail.com
 header.b="HaXeOZLH"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728544AbgICPXF (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 3 Sep 2020 11:23:05 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:44352 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1728642AbgICPWn (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 3 Sep 2020 11:22:43 -0400
Received: from mail-pj1-x1041.google.com (mail-pj1-x1041.google.com
 [IPv6:2607:f8b0:4864:20::1041])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 0EE35C061249;
        Thu,  3 Sep 2020 08:22:43 -0700 (PDT)
Received: by mail-pj1-x1041.google.com with SMTP id gf14so1628174pjb.5;
        Thu, 03 Sep 2020 08:22:43 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=from:to:cc:subject:date:message-id:in-reply-to:references
         :mime-version:content-transfer-encoding;
        bh=lcQkM04dJjt5Getpu5T9KGprYqJgTjrGD05xLf6xlJY=;
        b=HaXeOZLHfdo/16NXDGDjO2lPxZWwj3Gm71jwz7RJg0LmPWXx1HctW+SxkT+x414sG2
         Eh/K3t3iCT1WhPoGSaNeeHmBFEpuN35q5PIH2vAYis8yGGEbIQwwqjQWU5ur9Lzt/T84
         DEXIvfLsHMKOA0hAJUlzU1gvKDt0/NvJbCguB3Oe6EIV9sQe0mVBkAP8/LjcPP3gCzeg
         wGG60AJRk4vXLW8vEuLltOvZ6C2DM7noqXm6eGzF4XByEbtsXlVixBCFCVMApOTqS0q0
         fy/fAliMHrRsUpwzzbfH7RVhI+oybNwDZ8sXwg+l39JTGxvS2+SafN9nadJM8n2TEa4k
         +Bog==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:in-reply-to
         :references:mime-version:content-transfer-encoding;
        bh=lcQkM04dJjt5Getpu5T9KGprYqJgTjrGD05xLf6xlJY=;
        b=ZFdp3p63AD6i64k3GiZP7xbKhXiVWeRDLwsi6q++VEpTeHfA/sS5jFSUBqEWGFhGj7
         S/rvpiCTA82yuCQnv2xRrzsxMdTvufQ29BUNBCd2TqXgGBFEMhd0kH7DzfuzTcMWoPWx
         Ws/og+tyWZSgOWL4fWNFVHSmVnCgtiIQf00roQz9Qgp2/qGrwzjQCK37lxn5umP5pqbD
         ARjeF9ysMD6EifPKmYvF5fVrtN4HBcU1o4Uh4ik4Pk74rt17wpz2r7GvphWVwpB4m/XV
         SkE1axlyRSOIr44/rExwGZwGbz3Q2a0pfII/KlnsKyZiMS0fVKh7TRSmHEIM8gJ/DKST
         KxOg==
X-Gm-Message-State: AOAM530OvLHvvDBtK7JqJovHp7fe5z4krneGqqOjvoXUMoQh5cb7ywF2
        J8pg4+pIMnmT2AVkO/l2gdLGNd+FY0e87g==
X-Google-Smtp-Source: 
 ABdhPJzLGpBfCgsWkYgtmAGFFuFFR16B4JeChVvuPseDTtA690faOIHaTtrsUsn6q+I26JJE/5ffTA==
X-Received: by 2002:a17:90b:4a51:: with SMTP id
 lb17mr3634586pjb.235.1599146562303;
        Thu, 03 Sep 2020 08:22:42 -0700 (PDT)
Received: from localhost ([121.0.29.56])
        by smtp.gmail.com with ESMTPSA id
 o15sm3140855pgi.74.2020.09.03.08.22.41
        (version=TLS1_2 cipher=ECDHE-ECDSA-AES128-GCM-SHA256 bits=128/128);
        Thu, 03 Sep 2020 08:22:41 -0700 (PDT)
From: Lai Jiangshan <jiangshanlai@gmail.com>
To: linux-kernel@vger.kernel.org
Cc: Lai Jiangshan <laijs@linux.alibaba.com>,
        Paolo Bonzini <pbonzini@redhat.com>,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>,
        Thomas Gleixner <tglx@linutronix.de>,
        Ingo Molnar <mingo@redhat.com>, Borislav Petkov <bp@alien8.de>,
        x86@kernel.org, "H. Peter Anvin" <hpa@zytor.com>,
        kvm@vger.kernel.org
Subject: [PATCH V3] kvm x86/mmu: use KVM_REQ_MMU_SYNC to sync when needed
Date: Fri,  4 Sep 2020 00:23:04 +0800
Message-Id: <20200903162304.19694-1-jiangshanlai@gmail.com>
X-Mailer: git-send-email 2.19.1.6.gb485710b
In-Reply-To: <20200903012224.GL11695@sjchrist-ice>
References: <20200903012224.GL11695@sjchrist-ice>
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Lai Jiangshan <laijs@linux.alibaba.com>

When kvm_mmu_get_page() gets a page with unsynced children, the spt
pagetable is unsynchronized with the guest pagetable. But the
guest might not issue a "flush" operation on it when the pagetable
entry is changed from zero or other cases. The hypervisor has the 
responsibility to synchronize the pagetables.

The linux kernel behaves correctly as above for many years, but a recent
commit 8c8560b83390 ("KVM: x86/mmu: Use KVM_REQ_TLB_FLUSH_CURRENT for
MMU specific flushes") inadvertently included a line of code to change it
without giving any reason in the changelog. It is clear that the commit's
intention was to change KVM_REQ_TLB_FLUSH -> KVM_REQ_TLB_FLUSH_CURRENT,
so we don't unneedlesly flush other contexts but one of the hunks changed
nearby KVM_REQ_MMU_SYNC instead.

This patch changes it back.

Fixes: 8c8560b83390("KVM: x86/mmu: Use KVM_REQ_TLB_FLUSH_CURRENT for MMU specific flushes)
Link: https://lore.kernel.org/lkml/20200320212833.3507-26-sean.j.christopherson@intel.com/
Reviewed-by: Sean Christopherson <sean.j.christopherson@intel.com>
Reviewed-by: Vitaly Kuznetsov <vkuznets@redhat.com>
Signed-off-by: Lai Jiangshan <laijs@linux.alibaba.com>
---
Changed from v1:
	update patch description

Changed form v2:
	update patch description

 arch/x86/kvm/mmu/mmu.c | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
