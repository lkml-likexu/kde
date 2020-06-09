#### [PATCH 1/2] KVM: selftests: Add x86_64/debug_regs to .gitignore
##### From: Vitaly Kuznetsov <vkuznets@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Vitaly Kuznetsov <vkuznets@redhat.com>
X-Patchwork-Id: 11593157
Return-Path: <SRS0=GUoK=7V=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 58005138C
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon,  8 Jun 2020 11:24:18 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 3321620775
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon,  8 Jun 2020 11:24:18 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="aGd3ubY7"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729706AbgFHLYB (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 8 Jun 2020 07:24:01 -0400
Received: from us-smtp-delivery-1.mimecast.com ([205.139.110.120]:20779 "EHLO
        us-smtp-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org
        with ESMTP id S1729565AbgFHLYA (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 8 Jun 2020 07:24:00 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1591615439;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=zpkcgamnoQZWwxd6fU5WrGz2mHKzjvnnrxEBUwMVz5w=;
        b=aGd3ubY7Ag39eRW0mFbwYGa7rxYcODMHssippt/bp5fJ7DCsScwItsuTP8rmiqGlKohQpU
        O960DIRs9cVPYof5P+3w0o8ZNN/YxIkAAERAPbKcaUFgA8E+4tm+A5MXNKMynxDRT1YhaI
        tieRQw2FFEThM5+5RDbIh9i7+7pVrrM=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-474-3wVxRvGdORmKEV7ifNC61Q-1; Mon, 08 Jun 2020 07:23:58 -0400
X-MC-Unique: 3wVxRvGdORmKEV7ifNC61Q-1
Received: from smtp.corp.redhat.com (int-mx04.intmail.prod.int.phx2.redhat.com
 [10.5.11.14])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id CFE56107ACF2;
        Mon,  8 Jun 2020 11:23:56 +0000 (UTC)
Received: from vitty.brq.redhat.com (unknown [10.40.195.132])
        by smtp.corp.redhat.com (Postfix) with ESMTP id DF5335D9E4;
        Mon,  8 Jun 2020 11:23:47 +0000 (UTC)
From: Vitaly Kuznetsov <vkuznets@redhat.com>
To: kvm@vger.kernel.org
Cc: Paolo Bonzini <pbonzini@redhat.com>,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Marcelo Bandeira Condotta <mcondotta@redhat.com>,
        Makarand Sonare <makarandsonare@google.com>,
        Peter Xu <peterx@redhat.com>, linux-kernel@vger.kernel.org
Subject: [PATCH 1/2] KVM: selftests: Add x86_64/debug_regs to .gitignore
Date: Mon,  8 Jun 2020 13:23:45 +0200
Message-Id: <20200608112346.593513-1-vkuznets@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.14
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Add x86_64/debug_regs to .gitignore.

Reported-by: Marcelo Bandeira Condotta <mcondotta@redhat.com>
Fixes: 449aa906e67e ("KVM: selftests: Add KVM_SET_GUEST_DEBUG test")
Signed-off-by: Vitaly Kuznetsov <vkuznets@redhat.com>
---
 tools/testing/selftests/kvm/.gitignore | 1 +
 1 file changed, 1 insertion(+)

```
#### [Bug 208081] Memory leak in kvm_async_pf_task_wake
##### From: bugzilla-daemon@bugzilla.kernel.org

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: bugzilla-daemon@bugzilla.kernel.org
X-Patchwork-Id: 11592391
Return-Path: <SRS0=GUoK=7V=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 53031618
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon,  8 Jun 2020 00:46:53 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 30304207C3
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon,  8 Jun 2020 00:46:53 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728055AbgFHAqv convert rfc822-to-8bit (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Sun, 7 Jun 2020 20:46:51 -0400
Received: from mail.kernel.org ([198.145.29.99]:33954 "EHLO mail.kernel.org"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1728001AbgFHAqv (ORCPT <rfc822;kvm@vger.kernel.org>);
        Sun, 7 Jun 2020 20:46:51 -0400
From: bugzilla-daemon@bugzilla.kernel.org
To: kvm@vger.kernel.org
Subject: [Bug 208081] Memory leak in kvm_async_pf_task_wake
Date: Mon, 08 Jun 2020 00:46:50 +0000
X-Bugzilla-Reason: None
X-Bugzilla-Type: changed
X-Bugzilla-Watch-Reason: AssignedTo virtualization_kvm@kernel-bugs.osdl.org
X-Bugzilla-Product: Virtualization
X-Bugzilla-Component: kvm
X-Bugzilla-Version: unspecified
X-Bugzilla-Keywords: 
X-Bugzilla-Severity: normal
X-Bugzilla-Who: wanpeng.li@hotmail.com
X-Bugzilla-Status: NEW
X-Bugzilla-Resolution: 
X-Bugzilla-Priority: P1
X-Bugzilla-Assigned-To: virtualization_kvm@kernel-bugs.osdl.org
X-Bugzilla-Flags: 
X-Bugzilla-Changed-Fields: cc
Message-ID: <bug-208081-28872-82mfGYMepi@https.bugzilla.kernel.org/>
In-Reply-To: <bug-208081-28872@https.bugzilla.kernel.org/>
References: <bug-208081-28872@https.bugzilla.kernel.org/>
X-Bugzilla-URL: https://bugzilla.kernel.org/
Auto-Submitted: auto-generated
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

https://bugzilla.kernel.org/show_bug.cgi?id=208081

Wanpeng Li (wanpeng.li@hotmail.com) changed:

           What    |Removed                     |Added
----------------------------------------------------------------------------
                 CC|                            |wanpeng.li@hotmail.com

--- Comment #2 from Wanpeng Li (wanpeng.li@hotmail.com) ---
Could you apply below to the guest kernel and have a try again?

```
#### [PATCH] KVM: arm64: Stop sparse from moaning at __hyp_this_cpu_ptr
##### From: Marc Zyngier <maz@kernel.org>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Marc Zyngier <maz@kernel.org>
X-Patchwork-Id: 11592767
Return-Path: <SRS0=GUoK=7V=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id D806E90
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon,  8 Jun 2020 08:57:39 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id B597D2078D
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon,  8 Jun 2020 08:57:39 +0000 (UTC)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple; d=kernel.org;
	s=default; t=1591606659;
	bh=1jjVeWaGUx/kF/HqHOM8YQv2fZBnnOM3q+tHNHIFYFw=;
	h=From:To:Cc:Subject:Date:List-ID:From;
	b=GxacoeMM7XdpNWD2zarrAuLsLuRNR/3BoSJDE3REa4kDCt7Vclky6LhVmqsl4Rvsw
	 olor/hcG6rdjK3cscoLnv1VGn9Ggo5EFjaZInwteUqy/tdwrvtvtvlvKF1lPsTysLd
	 iwgX1wcn4/470RD0uXQJEfTKNnMIm2xifdPKcZ+I=
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729177AbgFHI5i (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 8 Jun 2020 04:57:38 -0400
Received: from mail.kernel.org ([198.145.29.99]:38442 "EHLO mail.kernel.org"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1725965AbgFHI5i (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 8 Jun 2020 04:57:38 -0400
Received: from disco-boy.misterjones.org (disco-boy.misterjones.org
 [51.254.78.96])
        (using TLSv1.2 with cipher ECDHE-RSA-AES256-GCM-SHA384 (256/256 bits))
        (No client certificate requested)
        by mail.kernel.org (Postfix) with ESMTPSA id B800A2067B;
        Mon,  8 Jun 2020 08:57:37 +0000 (UTC)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple; d=kernel.org;
        s=default; t=1591606657;
        bh=1jjVeWaGUx/kF/HqHOM8YQv2fZBnnOM3q+tHNHIFYFw=;
        h=From:To:Cc:Subject:Date:From;
        b=OzXF5RzAUEJ0g14wlYmEZt2t4Rh6LFZBxDi/WVEybHBjWRvx5wxHE1x+eWp/ZgTOe
         uV06Z1DIwbKN64xBPA2OZNtIR/Zj34IKTgQ6qt9JZEjHXZE2KExlqiVwY5eovimJa+
         GzfFtVbUyAO3cdQlkBP8q/CYvA1s4clOGWNDglXY=
Received: from 78.163-31-62.static.virginmediabusiness.co.uk ([62.31.163.78]
 helo=why.lan)
        by disco-boy.misterjones.org with esmtpsa
 (TLS1.3:ECDHE_RSA_AES_256_GCM_SHA384:256)
        (Exim 4.92)
        (envelope-from <maz@kernel.org>)
        id 1jiDb5-0015Cp-O0; Mon, 08 Jun 2020 09:57:36 +0100
From: Marc Zyngier <maz@kernel.org>
To: kvm@vger.kernel.org, kvmarm@lists.cs.columbia.edu,
        linux-arm-kernel@lists.infradead.org
Cc: James Morse <james.morse@arm.com>,
        Julien Thierry <julien.thierry.kdev@gmail.com>,
        Suzuki K Poulose <suzuki.poulose@arm.com>,
        kernel-team@android.com
Subject: [PATCH] KVM: arm64: Stop sparse from moaning at __hyp_this_cpu_ptr
Date: Mon,  8 Jun 2020 09:57:31 +0100
Message-Id: <20200608085731.1405854-1-maz@kernel.org>
X-Mailer: git-send-email 2.26.2
MIME-Version: 1.0
X-SA-Exim-Connect-IP: 62.31.163.78
X-SA-Exim-Rcpt-To: kvm@vger.kernel.org, kvmarm@lists.cs.columbia.edu,
 linux-arm-kernel@lists.infradead.org, james.morse@arm.com,
 julien.thierry.kdev@gmail.com, suzuki.poulose@arm.com,
 kernel-team@android.com
X-SA-Exim-Mail-From: maz@kernel.org
X-SA-Exim-Scanned: No (on disco-boy.misterjones.org);
 SAEximRunCond expanded to false
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Sparse complains that __hyp_this_cpu_ptr() returns something
that is flagged noderef and not in the correct address space
(both being the result of the __percpu annotation).

Pretend that __hyp_this_cpu_ptr() knows what it is doing by
forcefully casting the pointer with __kernel __force.

Signed-off-by: Marc Zyngier <maz@kernel.org>
---
 arch/arm64/include/asm/kvm_asm.h | 9 +++++++--
 1 file changed, 7 insertions(+), 2 deletions(-)

```
#### [PATCH] KVM: PPC: Book3S HV: increase KVMPPC_NR_LPIDS on POWER8 and POWER9
##### From: =?utf-8?q?C=C3=A9dric_Le_Goater?= <clg@kaod.org>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 8bit
X-Patchwork-Submitter: =?utf-8?q?C=C3=A9dric_Le_Goater?= <clg@kaod.org>
X-Patchwork-Id: 11593329
Return-Path: <SRS0=GUoK=7V=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 27218912
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon,  8 Jun 2020 13:13:05 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 111862076C
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon,  8 Jun 2020 13:13:04 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729069AbgFHNM6 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 8 Jun 2020 09:12:58 -0400
Received: from 10.mo178.mail-out.ovh.net ([46.105.76.150]:32931 "EHLO
        10.mo178.mail-out.ovh.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1728938AbgFHNM6 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 8 Jun 2020 09:12:58 -0400
X-Greylist: delayed 2399 seconds by postgrey-1.27 at vger.kernel.org;
 Mon, 08 Jun 2020 09:12:57 EDT
Received: from player699.ha.ovh.net (unknown [10.108.42.184])
        by mo178.mail-out.ovh.net (Postfix) with ESMTP id 0137DA5553
        for <kvm@vger.kernel.org>; Mon,  8 Jun 2020 13:57:25 +0200 (CEST)
Received: from kaod.org (82-64-250-170.subs.proxad.net [82.64.250.170])
        (Authenticated sender: clg@kaod.org)
        by player699.ha.ovh.net (Postfix) with ESMTPSA id E1AEA131F7A48;
        Mon,  8 Jun 2020 11:57:18 +0000 (UTC)
Authentication-Results: garm.ovh;
 auth=pass
 (GARM-100R0039a28aace-0423-48ac-9d27-88d758f13fba,B6B0473EF73D0859AD85419D5DB97E88249038E4)
 smtp.auth=clg@kaod.org
From: =?utf-8?q?C=C3=A9dric_Le_Goater?= <clg@kaod.org>
To: Michael Ellerman <mpe@ellerman.id.au>
Cc: Paul Mackerras <paulus@samba.org>, Nicholas Piggin <npiggin@gmail.com>,
 linuxppc-dev@lists.ozlabs.org, kvm-ppc@vger.kernel.org, kvm@vger.kernel.org,
	=?utf-8?q?C=C3=A9dric_Le_Goater?= <clg@kaod.org>
Subject: [PATCH] KVM: PPC: Book3S HV: increase KVMPPC_NR_LPIDS on POWER8 and
 POWER9
Date: Mon,  8 Jun 2020 13:57:14 +0200
Message-Id: <20200608115714.1139735-1-clg@kaod.org>
X-Mailer: git-send-email 2.25.4
MIME-Version: 1.0
X-Ovh-Tracer-Id: 2856689540546005937
X-VR-SPAMSTATE: OK
X-VR-SPAMSCORE: -100
X-VR-SPAMCAUSE: 
 gggruggvucftvghtrhhoucdtuddrgeduhedrudehuddggeekucetufdoteggodetrfdotffvucfrrhhofhhilhgvmecuqfggjfdpvefjgfevmfevgfenuceurghilhhouhhtmecuhedttdenucesvcftvggtihhpihgvnhhtshculddquddttddmnecujfgurhephffvufffkffogggtgfesthekredtredtjeenucfhrhhomhepveorughrihgtucfnvgcuifhorghtvghruceotghlgheskhgrohgurdhorhhgqeenucggtffrrghtthgvrhhnpeeikeekleffteegleevveejheetuddviedvleejvedvueevtdfgieduieeviedugfenucfkpheptddrtddrtddrtddpkedvrdeigedrvdehtddrudejtdenucevlhhushhtvghrufhiiigvpedtnecurfgrrhgrmhepmhhouggvpehsmhhtphdqohhuthdphhgvlhhopehplhgrhigvrheileelrdhhrgdrohhvhhdrnhgvthdpihhnvghtpedtrddtrddtrddtpdhmrghilhhfrhhomheptghlgheskhgrohgurdhorhhgpdhrtghpthhtohepkhhvmhesvhhgvghrrdhkvghrnhgvlhdrohhrgh
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

POWER8 and POWER9 have 12-bit LPIDs. Change LPID_RSVD to support up to
(4096 - 2) guests on these processors. POWER7 is kept the same with a
limitation of (1024 - 2), but it might be time to drop KVM support for
POWER7.

Tested with 2048 guests * 4 vCPUs on a witherspoon system with 512G
RAM and a bit of swap.

Signed-off-by: Cédric Le Goater <clg@kaod.org>
---
 arch/powerpc/include/asm/reg.h      | 3 ++-
 arch/powerpc/kvm/book3s_64_mmu_hv.c | 8 ++++++--
 2 files changed, 8 insertions(+), 3 deletions(-)

```
#### [PATCH] KVM: SVM: fix calls to is_intercept
##### From: Paolo Bonzini <pbonzini@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Paolo Bonzini <pbonzini@redhat.com>
X-Patchwork-Id: 11593247
Return-Path: <SRS0=GUoK=7V=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id AD363913
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon,  8 Jun 2020 12:14:41 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 87AA2206C3
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon,  8 Jun 2020 12:14:41 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="FpMLK4cy"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729733AbgFHMOg (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 8 Jun 2020 08:14:36 -0400
Received: from us-smtp-delivery-1.mimecast.com ([205.139.110.120]:25029 "EHLO
        us-smtp-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org
        with ESMTP id S1729628AbgFHMOf (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 8 Jun 2020 08:14:35 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1591618473;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=n0WTesSFX4GdOnD7OP8HwiFpZRIS/BtZoZgv9wJXix0=;
        b=FpMLK4cysvzA2/JuboYEUkDTyjAIV/Pjs0/5abTN9g4cBO9GjgPWFXu9wfPrKFMuEhHN7e
        8bcUSoqcafEO8sxRlQNnrDCTrclmVmj6PCS24u/yG7Z67ZXPTACUyB/f57nZjXhjJ4GZVl
        58c5zFI+0E2uH6Y1CRF7fOsCw4fQrZc=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-168-MXyvpYL0M9uFpPHUudC0sA-1; Mon, 08 Jun 2020 08:14:31 -0400
X-MC-Unique: MXyvpYL0M9uFpPHUudC0sA-1
Received: from smtp.corp.redhat.com (int-mx02.intmail.prod.int.phx2.redhat.com
 [10.5.11.12])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id D50DB8014D4;
        Mon,  8 Jun 2020 12:14:30 +0000 (UTC)
Received: from virtlab701.virt.lab.eng.bos.redhat.com
 (virtlab701.virt.lab.eng.bos.redhat.com [10.19.152.228])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 326FC619C4;
        Mon,  8 Jun 2020 12:14:29 +0000 (UTC)
From: Paolo Bonzini <pbonzini@redhat.com>
To: linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Cc: vkuznets@redhat.com, Qian Cai <cai@lca.pw>
Subject: [PATCH] KVM: SVM: fix calls to is_intercept
Date: Mon,  8 Jun 2020 08:14:28 -0400
Message-Id: <20200608121428.9214-1-pbonzini@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.12
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

is_intercept takes an INTERCEPT_* constant, not SVM_EXIT_*; because
of this, the compiler was removing the body of the conditionals,
as if is_intercept returned 0.

This unveils a latent bug: when clearing the VINTR intercept,
int_ctl must also be changed in the L1 VMCB (svm->nested.hsave),
just like the intercept itself is also changed in the L1 VMCB.
Otherwise V_IRQ remains set and, due to the VINTR intercept being clear,
we get a spurious injection of a vector 0 interrupt on the next
L2->L1 vmexit.

Reported-by: Qian Cai <cai@lca.pw>
Signed-off-by: Paolo Bonzini <pbonzini@redhat.com>
---
	Vitaly, can you give this a shot with Hyper-V?  I have already
	placed it on kvm/queue, it passes both svm.flat and KVM-on-KVM
	smoke tests.

 arch/x86/kvm/svm/nested.c | 2 +-
 arch/x86/kvm/svm/svm.c    | 4 +++-
 2 files changed, 4 insertions(+), 2 deletions(-)

```
#### [PATCH kvm-unit-tests] remove unused file
##### From: Paolo Bonzini <pbonzini@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Paolo Bonzini <pbonzini@redhat.com>
X-Patchwork-Id: 11593279
Return-Path: <SRS0=GUoK=7V=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 6FE92913
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon,  8 Jun 2020 12:42:33 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 4BEE82076A
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon,  8 Jun 2020 12:42:33 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="IORKHG+y"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728245AbgFHMmc (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 8 Jun 2020 08:42:32 -0400
Received: from us-smtp-2.mimecast.com ([205.139.110.61]:22660 "EHLO
        us-smtp-delivery-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S1727052AbgFHMmb (ORCPT
        <rfc822;kvm@vger.kernel.org>); Mon, 8 Jun 2020 08:42:31 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1591620150;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=BHiSv3/XIs4p+ocNnWY97Q87sD+jZaEpUwxAP3vu2p8=;
        b=IORKHG+yEHNJ7Jlyp9R5FEGjRzChjqlnav5Cr0j2wqCiYhO5tSShZY8XaQ5TGp/czCI9k+
        6lu150s5oCVvVhi7+igUT1WI6M2PGMX7Vw7RX3qmKosTA5K2fpXC8SwxFz+UTmqtmTmboc
        iFj6NQ3YojsfFjs2T8uSmHV1iv6JIp8=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-418-pIkcH4Q9NFW_DvQcTMdNIA-1; Mon, 08 Jun 2020 08:42:23 -0400
X-MC-Unique: pIkcH4Q9NFW_DvQcTMdNIA-1
Received: from smtp.corp.redhat.com (int-mx06.intmail.prod.int.phx2.redhat.com
 [10.5.11.16])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id E5D75EC1A0
        for <kvm@vger.kernel.org>; Mon,  8 Jun 2020 12:42:22 +0000 (UTC)
Received: from virtlab511.virt.lab.eng.bos.redhat.com
 (virtlab511.virt.lab.eng.bos.redhat.com [10.19.152.198])
        by smtp.corp.redhat.com (Postfix) with ESMTP id A2E8C5C1D6
        for <kvm@vger.kernel.org>; Mon,  8 Jun 2020 12:42:22 +0000 (UTC)
From: Paolo Bonzini <pbonzini@redhat.com>
To: kvm@vger.kernel.org
Subject: [PATCH kvm-unit-tests] remove unused file
Date: Mon,  8 Jun 2020 08:42:22 -0400
Message-Id: <20200608124222.371807-1-pbonzini@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.16
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

---
 lib/x86/fake-apic.h | 14 --------------
 1 file changed, 14 deletions(-)
 delete mode 100644 lib/x86/fake-apic.h

diff --git a/lib/x86/fake-apic.h b/lib/x86/fake-apic.h
```
#### [PATCH kvm-unit-tests] x86: always set up SMP
##### From: Paolo Bonzini <pbonzini@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Paolo Bonzini <pbonzini@redhat.com>
X-Patchwork-Id: 11593473
Return-Path: <SRS0=GUoK=7V=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id F043F90
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon,  8 Jun 2020 16:00:45 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id CD47A206C3
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon,  8 Jun 2020 16:00:45 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="IjYPLawD"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1730380AbgFHQAo (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 8 Jun 2020 12:00:44 -0400
Received: from us-smtp-delivery-1.mimecast.com ([207.211.31.120]:40567 "EHLO
        us-smtp-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org
        with ESMTP id S1730231AbgFHQAn (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 8 Jun 2020 12:00:43 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1591632040;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=YnXWU+VOYKQA/aDp0JdHDPTAh2f+1i7H5RxXYKlXZYw=;
        b=IjYPLawDkzuIVVTclwTOl2dysd3cm5t2crY4fXohqTGHp1kSJ6Yk/hBN6WGZ1srxkk965d
        WoRovhTVhTbwmpN1MO2plR3HCXy0WfbRTjIudWJcvRvVhxAcA3MSU22tp5x5xwsmNHwWAf
        h4KC6Qg+lLirwRKrNgAvt3CNyDB5vu8=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-287-5oYXFxx1P_e9zbALYgt8Rg-1; Mon, 08 Jun 2020 12:00:35 -0400
X-MC-Unique: 5oYXFxx1P_e9zbALYgt8Rg-1
Received: from smtp.corp.redhat.com (int-mx04.intmail.prod.int.phx2.redhat.com
 [10.5.11.14])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 354FA800053
        for <kvm@vger.kernel.org>; Mon,  8 Jun 2020 16:00:34 +0000 (UTC)
Received: from virtlab511.virt.lab.eng.bos.redhat.com
 (virtlab511.virt.lab.eng.bos.redhat.com [10.19.152.198])
        by smtp.corp.redhat.com (Postfix) with ESMTP id B9F005D9C9;
        Mon,  8 Jun 2020 16:00:33 +0000 (UTC)
From: Paolo Bonzini <pbonzini@redhat.com>
To: kvm@vger.kernel.org
Cc: cavery@redhat.com
Subject: [PATCH kvm-unit-tests] x86: always set up SMP
Date: Mon,  8 Jun 2020 12:00:33 -0400
Message-Id: <20200608160033.392059-1-pbonzini@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.14
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Currently setup_vm cannot assume that it can invoke IPIs, and therefore
only initializes CR0/CR3/CR4 on the CPU it runs on.  In order to keep the
initialization code clean, let's just call smp_init (and therefore
setup_idt) unconditionally.

Signed-off-by: Paolo Bonzini <pbonzini@redhat.com>
---
 x86/access.c              | 2 --
 x86/apic.c                | 1 -
 x86/asyncpf.c             | 1 -
 x86/cmpxchg8b.c           | 1 -
 x86/cstart.S              | 6 +++---
 x86/cstart64.S            | 6 +++---
 x86/debug.c               | 1 -
 x86/emulator.c            | 1 -
 x86/eventinj.c            | 1 -
 x86/hypercall.c           | 1 -
 x86/hyperv_clock.c        | 1 -
 x86/hyperv_connections.c  | 1 -
 x86/hyperv_stimer.c       | 1 -
 x86/hyperv_synic.c        | 1 -
 x86/idt_test.c            | 1 -
 x86/intel-iommu.c         | 1 -
 x86/ioapic.c              | 1 -
 x86/kvmclock_test.c       | 2 --
 x86/memory.c              | 1 -
 x86/pcid.c                | 2 --
 x86/pmu.c                 | 1 -
 x86/rdpru.c               | 2 --
 x86/smptest.c             | 2 --
 x86/svm.c                 | 1 -
 x86/syscall.c             | 1 -
 x86/taskswitch2.c         | 1 -
 x86/tscdeadline_latency.c | 1 -
 x86/umip.c                | 1 -
 x86/vmexit.c              | 1 -
 x86/vmware_backdoors.c    | 1 -
 x86/vmx.c                 | 1 -
 x86/xsave.c               | 1 -
 32 files changed, 6 insertions(+), 41 deletions(-)

```
#### [kvm-unit-tests PATCH v8 01/12] s390x: Use PSW bits definitions in cstart
##### From: Pierre Morel <pmorel@linux.ibm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Pierre Morel <pmorel@linux.ibm.com>
X-Patchwork-Id: 11592725
Return-Path: <SRS0=GUoK=7V=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 3656C60D
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon,  8 Jun 2020 08:13:13 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 278262072F
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon,  8 Jun 2020 08:13:13 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729105AbgFHINM (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 8 Jun 2020 04:13:12 -0400
Received: from mx0a-001b2d01.pphosted.com ([148.163.156.1]:13654 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1729054AbgFHINK (ORCPT
        <rfc822;kvm@vger.kernel.org>); Mon, 8 Jun 2020 04:13:10 -0400
Received: from pps.filterd (m0098399.ppops.net [127.0.0.1])
        by mx0a-001b2d01.pphosted.com (8.16.0.42/8.16.0.42) with SMTP id
 05883LKR165246;
        Mon, 8 Jun 2020 04:13:09 -0400
Received: from pps.reinject (localhost [127.0.0.1])
        by mx0a-001b2d01.pphosted.com with ESMTP id 31g7a0vn1e-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Mon, 08 Jun 2020 04:13:09 -0400
Received: from m0098399.ppops.net (m0098399.ppops.net [127.0.0.1])
        by pps.reinject (8.16.0.36/8.16.0.36) with SMTP id 05884dW6176782;
        Mon, 8 Jun 2020 04:13:08 -0400
Received: from ppma01fra.de.ibm.com (46.49.7a9f.ip4.static.sl-reverse.com
 [159.122.73.70])
        by mx0a-001b2d01.pphosted.com with ESMTP id 31g7a0vmyd-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Mon, 08 Jun 2020 04:13:08 -0400
Received: from pps.filterd (ppma01fra.de.ibm.com [127.0.0.1])
        by ppma01fra.de.ibm.com (8.16.0.42/8.16.0.42) with SMTP id
 05885Cww016001;
        Mon, 8 Jun 2020 08:13:06 GMT
Received: from b06avi18878370.portsmouth.uk.ibm.com
 (b06avi18878370.portsmouth.uk.ibm.com [9.149.26.194])
        by ppma01fra.de.ibm.com with ESMTP id 31g2s7se9u-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Mon, 08 Jun 2020 08:13:05 +0000
Received: from d06av22.portsmouth.uk.ibm.com (d06av22.portsmouth.uk.ibm.com
 [9.149.105.58])
        by b06avi18878370.portsmouth.uk.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id 0588D31h65405242
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Mon, 8 Jun 2020 08:13:03 GMT
Received: from d06av22.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 8DD2F4C050;
        Mon,  8 Jun 2020 08:13:03 +0000 (GMT)
Received: from d06av22.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 3B3BC4C058;
        Mon,  8 Jun 2020 08:13:03 +0000 (GMT)
Received: from oc3016276355.ibm.com (unknown [9.145.43.245])
        by d06av22.portsmouth.uk.ibm.com (Postfix) with ESMTP;
        Mon,  8 Jun 2020 08:13:03 +0000 (GMT)
From: Pierre Morel <pmorel@linux.ibm.com>
To: kvm@vger.kernel.org
Cc: linux-s390@vger.kernel.org, frankja@linux.ibm.com,
        david@redhat.com, thuth@redhat.com, cohuck@redhat.com
Subject: [kvm-unit-tests PATCH v8 01/12] s390x: Use PSW bits definitions in
 cstart
Date: Mon,  8 Jun 2020 10:12:50 +0200
Message-Id: <1591603981-16879-2-git-send-email-pmorel@linux.ibm.com>
X-Mailer: git-send-email 1.8.3.1
In-Reply-To: <1591603981-16879-1-git-send-email-pmorel@linux.ibm.com>
References: <1591603981-16879-1-git-send-email-pmorel@linux.ibm.com>
X-TM-AS-GCONF: 00
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.216,18.0.687
 definitions=2020-06-08_04:2020-06-08,2020-06-08 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 suspectscore=1 bulkscore=0
 adultscore=0 phishscore=0 mlxlogscore=999 spamscore=0 cotscore=-2147483648
 clxscore=1015 priorityscore=1501 lowpriorityscore=0 malwarescore=0
 impostorscore=0 mlxscore=0 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.12.0-2004280000 definitions=main-2006080062
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This patch defines the PSW bits EA/BA used to initialize the PSW masks
for exceptions.

Since some PSW mask definitions exist already in arch_def.h we add these
definitions there.
We move all PSW definitions together and protect assembler code against
C syntax.

Signed-off-by: Pierre Morel <pmorel@linux.ibm.com>
Reviewed-by: Janosch Frank <frankja@linux.ibm.com>
Acked-by: Thomas Huth <thuth@redhat.com>
---
 lib/s390x/asm/arch_def.h | 15 +++++++++++----
 s390x/cstart64.S         | 15 ++++++++-------
 2 files changed, 19 insertions(+), 11 deletions(-)

```
#### [PATCH kvm-unit-tests 1/2] svm: Add ability to execute test via test_run on a vcpu other than vcpu 0
##### From: Cathy Avery <cavery@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Cathy Avery <cavery@redhat.com>
X-Patchwork-Id: 11593259
Return-Path: <SRS0=GUoK=7V=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 61276913
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon,  8 Jun 2020 12:28:15 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 474BB2076C
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon,  8 Jun 2020 12:28:15 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="VLGGDM4O"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729753AbgFHM2O (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 8 Jun 2020 08:28:14 -0400
Received: from us-smtp-delivery-1.mimecast.com ([205.139.110.120]:44998 "EHLO
        us-smtp-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org
        with ESMTP id S1729668AbgFHM2M (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 8 Jun 2020 08:28:12 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1591619290;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding:
         in-reply-to:in-reply-to:references:references;
        bh=t1ZQ22N4GS1aOVvRJb6q+OxNNqR941WJ3Ue4dl0p7rw=;
        b=VLGGDM4ORtDVTA6AG1/XrP0t+Lc00UvHWnBQNnEFVnp+c5Gj3KnLxsgBPuEZNC3boKGQL8
        xb7/3q+JhxghQ5G+Esh2nNicEdk7s64N4uz5IqrvaX5W4h70BZAGoTrQkOqzgEL6AfEedX
        bHQ10Z7Oqc13cgsaT5xvufVhea5mYiU=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-286-fonlKfq2PLiCRa6Xci7Qkg-1; Mon, 08 Jun 2020 08:28:04 -0400
X-MC-Unique: fonlKfq2PLiCRa6Xci7Qkg-1
Received: from smtp.corp.redhat.com (int-mx05.intmail.prod.int.phx2.redhat.com
 [10.5.11.15])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 51AC6108BD0A;
        Mon,  8 Jun 2020 12:28:03 +0000 (UTC)
Received: from virtlab710.virt.lab.eng.bos.redhat.com
 (virtlab710.virt.lab.eng.bos.redhat.com [10.19.152.252])
        by smtp.corp.redhat.com (Postfix) with ESMTP id A4822768BB;
        Mon,  8 Jun 2020 12:28:02 +0000 (UTC)
From: Cathy Avery <cavery@redhat.com>
To: linux-kernel@vger.kernel.org, kvm@vger.kernel.org,
        pbonzini@redhat.com
Subject: [PATCH kvm-unit-tests 1/2] svm: Add ability to execute test via
 test_run on a vcpu other than vcpu 0
Date: Mon,  8 Jun 2020 08:27:59 -0400
Message-Id: <20200608122800.6315-2-cavery@redhat.com>
In-Reply-To: <20200608122800.6315-1-cavery@redhat.com>
References: <20200608122800.6315-1-cavery@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.15
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

When running tests that can result in a vcpu being left in an
indeterminate state it is useful to be able to run the test on
a vcpu other than 0. This patch allows test_run to be executed
on any vcpu indicated by the on_vcpu member of the svm_test struct.
The initialized state of the vcpu0 registers used to populate the
vmcb is carried forward to the other vcpus.

Signed-off-by: Cathy Avery <cavery@redhat.com>
---
 x86/svm.c | 49 ++++++++++++++++++++++++++++++++++++++++++++++++-
 x86/svm.h | 13 +++++++++++++
 2 files changed, 61 insertions(+), 1 deletion(-)

```
#### [PATCH v2] KVM: arm64: Remove host_cpu_context member from vcpu structure
##### From: Marc Zyngier <maz@kernel.org>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Marc Zyngier <maz@kernel.org>
X-Patchwork-Id: 11592763
Return-Path: <SRS0=GUoK=7V=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 311B790
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon,  8 Jun 2020 08:57:14 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 1477E207F9
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon,  8 Jun 2020 08:57:14 +0000 (UTC)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple; d=kernel.org;
	s=default; t=1591606634;
	bh=Z+v/XPM1/PmMjTBq3xkoyGiM8DRyZsFhG1jTBdZEKE0=;
	h=From:To:Cc:Subject:Date:List-ID:From;
	b=jWVuN6D7HyYOCfWjOK3BBLvxcq23vWCqm0JSqwuSeEN7LrCL0EzYAWh0SSggqKDnL
	 fVYa+0N45rEajvvGa55d/Zby+a+PUap0ApDZKq5k0CYBfawQDCAh3Xylc7eWg36w9g
	 O7XGvJYmgss8pfaIH11cBD9VhwSIYwxHDgUsQ2MU=
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729156AbgFHI5N (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 8 Jun 2020 04:57:13 -0400
Received: from mail.kernel.org ([198.145.29.99]:38074 "EHLO mail.kernel.org"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1725965AbgFHI5J (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 8 Jun 2020 04:57:09 -0400
Received: from disco-boy.misterjones.org (disco-boy.misterjones.org
 [51.254.78.96])
        (using TLSv1.2 with cipher ECDHE-RSA-AES256-GCM-SHA384 (256/256 bits))
        (No client certificate requested)
        by mail.kernel.org (Postfix) with ESMTPSA id 7636C2067B;
        Mon,  8 Jun 2020 08:57:08 +0000 (UTC)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple; d=kernel.org;
        s=default; t=1591606628;
        bh=Z+v/XPM1/PmMjTBq3xkoyGiM8DRyZsFhG1jTBdZEKE0=;
        h=From:To:Cc:Subject:Date:From;
        b=0V7OXheOm8eSne7gCQbbgH9QibTufb0fA5KTEQcIT5G4wzMzKpEb13oH6PEqDPhvN
         ZuyLd5secqqjp589tYUgacIqCTDebeEo+wkGdLBfy/CRU+rEkH+wfJ+2PrnLsAnDgN
         ibOpg0nJ66IEaLpxOhZQObLSZlyXSVF/S5KFbxZ4=
Received: from 78.163-31-62.static.virginmediabusiness.co.uk ([62.31.163.78]
 helo=why.lan)
        by disco-boy.misterjones.org with esmtpsa
 (TLS1.3:ECDHE_RSA_AES_256_GCM_SHA384:256)
        (Exim 4.92)
        (envelope-from <maz@kernel.org>)
        id 1jiDac-0015Ac-L5; Mon, 08 Jun 2020 09:57:06 +0100
From: Marc Zyngier <maz@kernel.org>
To: kvm@vger.kernel.org, kvmarm@lists.cs.columbia.edu,
        linux-arm-kernel@lists.infradead.org
Cc: James Morse <james.morse@arm.com>,
        Julien Thierry <julien.thierry.kdev@gmail.com>,
        Suzuki K Poulose <suzuki.poulose@arm.com>,
        Mark Rutland <mark.rutland@arm.com>, kernel-team@android.com,
        Andrew Scull <ascull@google.com>
Subject: [PATCH v2] KVM: arm64: Remove host_cpu_context member from vcpu
 structure
Date: Mon,  8 Jun 2020 09:56:57 +0100
Message-Id: <20200608085657.1405730-1-maz@kernel.org>
X-Mailer: git-send-email 2.26.2
MIME-Version: 1.0
X-SA-Exim-Connect-IP: 62.31.163.78
X-SA-Exim-Rcpt-To: kvm@vger.kernel.org, kvmarm@lists.cs.columbia.edu,
 linux-arm-kernel@lists.infradead.org, james.morse@arm.com,
 julien.thierry.kdev@gmail.com, suzuki.poulose@arm.com, mark.rutland@arm.com,
 kernel-team@android.com, ascull@google.com
X-SA-Exim-Mail-From: maz@kernel.org
X-SA-Exim-Scanned: No (on disco-boy.misterjones.org);
 SAEximRunCond expanded to false
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

For very long, we have kept this pointer back to the per-cpu
host state, despite having working per-cpu accessors at EL2
for some time now.

Recent investigations have shown that this pointer is easy
to abuse in preemptible context, which is a sure sign that
it would better be gone. Not to mention that a per-cpu
pointer is faster to access at all times.

Reported-by: Andrew Scull <ascull@google.com>
Signed-off-by: Marc Zyngier <maz@kernel.org>
Acked-by: Mark Rutland <mark.rutland@arm.com>
Reviewed-by: Andrew Scull <ascull@google.com>
---

Notes:
    v2: Stick to this_cpu_ptr() in pmu.c, as this only used on the
        kernel side and not the hypervisor.

 arch/arm64/include/asm/kvm_host.h | 3 ---
 arch/arm64/kvm/arm.c              | 3 ---
 arch/arm64/kvm/hyp/debug-sr.c     | 4 ++--
 arch/arm64/kvm/hyp/switch.c       | 6 +++---
 arch/arm64/kvm/hyp/sysreg-sr.c    | 6 ++++--
 arch/arm64/kvm/pmu.c              | 8 ++------
 6 files changed, 11 insertions(+), 19 deletions(-)

```
#### [PATCH v2] KVM: nVMX: Consult only the "basic" exit reason when routing nested exit
##### From: Sean Christopherson <sean.j.christopherson@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Sean Christopherson <sean.j.christopherson@intel.com>
X-Patchwork-Id: 11593869
Return-Path: <SRS0=GUoK=7V=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id E59C490
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon,  8 Jun 2020 19:19:04 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id D52BF206A4
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon,  8 Jun 2020 19:19:04 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726537AbgFHTTA (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 8 Jun 2020 15:19:00 -0400
Received: from mga02.intel.com ([134.134.136.20]:41852 "EHLO mga02.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726409AbgFHTS7 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 8 Jun 2020 15:18:59 -0400
IronPort-SDR: 
 TX0auy171xg/88bbdvUy0RNU/eN06UqdDle9Lx8xatxU3JYUVM9CEqS8nogwL0wpdeNqXVMwn7
 xCntn4YniymQ==
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from orsmga005.jf.intel.com ([10.7.209.41])
  by orsmga101.jf.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 08 Jun 2020 12:18:59 -0700
IronPort-SDR: 
 WIvzDvt6qXPnDtoGlEHqhyfaeHGmYNE6iID2/o8ODo6ZAgHRcxd0ILtw4JJz9RY545QtW3RS/V
 PzvkvaUlqvhw==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.73,487,1583222400";
   d="scan'208";a="446851097"
Received: from sjchrist-coffee.jf.intel.com ([10.54.74.152])
  by orsmga005.jf.intel.com with ESMTP; 08 Jun 2020 12:18:58 -0700
From: Sean Christopherson <sean.j.christopherson@intel.com>
To: Paolo Bonzini <pbonzini@redhat.com>
Cc: Sean Christopherson <sean.j.christopherson@intel.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org, Xiaoyao Li <xiaoyao.li@intel.com>,
        Oliver Upton <oupton@google.com>,
        Krish Sadhukhan <krish.sadhukhan@oracle.com>,
        Miaohe Lin <linmiaohe@huawei.com>
Subject: [PATCH v2] KVM: nVMX: Consult only the "basic" exit reason when
 routing nested exit
Date: Mon,  8 Jun 2020 12:18:57 -0700
Message-Id: <20200608191857.30319-1-sean.j.christopherson@intel.com>
X-Mailer: git-send-email 2.26.0
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Consult only the basic exit reason, i.e. bits 15:0 of vmcs.EXIT_REASON,
when determining whether a nested VM-Exit should be reflected into L1 or
handled by KVM in L0.

For better or worse, the switch statements nested_vmx_l0_wants_exit()
and nested_vmx_l1_wants_exit() default to reflecting the VM-Exit into L1
for any nested VM-Exit without dedicated logic.  Because the case
statements only contain the basic exit reason, any VM-Exit with modifier
bits set will be reflected to L1, even if KVM intended to handle it in
L0.

Practically speaking, this only affects EXIT_REASON_MCE_DURING_VMENTRY,
i.e. a #MC that occurs on nested VM-Enter would be incorrectly routed to
L1, as "failed VM-Entry" is the only modifier that KVM can currently
encounter.  The SMM modifiers will never be generated as KVM doesn't
support/employ a SMI Transfer Monitor.  Ditto for "exit from enclave",
as KVM doesn't yet support virtualizing SGX, i.e. it's impossible to
enter an enclave in a KVM guest (L1 or L2).

Note, the original version of this fix[*] is functionally equivalent and
far more suited to backporting as the affected code was refactored since
the original patch was posted.

[*] https://lkml.kernel.org/r/20200227174430.26371-1-sean.j.christopherson@intel.com

Fixes: 644d711aa0e1 ("KVM: nVMX: Deciding if L0 or L1 should handle an L2 exit")
Cc: Jim Mattson <jmattson@google.com>
Cc: Xiaoyao Li <xiaoyao.li@intel.com>
Cc: stable@vger.kernel.org
Cc: Oliver Upton <oupton@google.com>
Cc: Krish Sadhukhan <krish.sadhukhan@oracle.com>
Cc: Miaohe Lin <linmiaohe@huawei.com>
Signed-off-by: Sean Christopherson <sean.j.christopherson@intel.com>
Reviewed-by: Oliver Upton <oupton@google.com>
---

Another wounded soldier. 

Oliver, Krish, and Miaohe all provided reviews for v1, but I didn't feel
comfortable adding the tags to v2 because this is far from a straight
rebase.

v2: Rebased to kvm/queue, commit fb7333dfd812 ("KVM: SVM: fix calls ...").

 arch/x86/kvm/vmx/nested.c | 4 ++--
 1 file changed, 2 insertions(+), 2 deletions(-)

```
#### [PATCH v2] KVM: x86: Unexport x86_fpu_cache and make it static
##### From: Sean Christopherson <sean.j.christopherson@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Sean Christopherson <sean.j.christopherson@intel.com>
X-Patchwork-Id: 11593775
Return-Path: <SRS0=GUoK=7V=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id BA3AB913
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon,  8 Jun 2020 18:02:25 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id AAB4E2083E
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon,  8 Jun 2020 18:02:25 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1730032AbgFHSCU (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 8 Jun 2020 14:02:20 -0400
Received: from mga01.intel.com ([192.55.52.88]:63692 "EHLO mga01.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726097AbgFHSCU (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 8 Jun 2020 14:02:20 -0400
IronPort-SDR: 
 BWsp7jq2/P+QY63eZe+zpDk52wUN52prRwfnxpkthowefhEU+Vg2JazxY9zHvJhe/01NRq0J/U
 TNRud+cg5gdw==
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from fmsmga002.fm.intel.com ([10.253.24.26])
  by fmsmga101.fm.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 08 Jun 2020 11:02:19 -0700
IronPort-SDR: 
 CqJczIq6TqtAxKiVtFFGKyTnFMmMbjgc7uBzNNMGRdMFzfBQSdcjC9UbzbWaspO1jIh2GpMHJv
 YbwDq50K1bAg==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.73,487,1583222400";
   d="scan'208";a="305910978"
Received: from sjchrist-coffee.jf.intel.com ([10.54.74.152])
  by fmsmga002.fm.intel.com with ESMTP; 08 Jun 2020 11:02:19 -0700
From: Sean Christopherson <sean.j.christopherson@intel.com>
To: Paolo Bonzini <pbonzini@redhat.com>
Cc: Sean Christopherson <sean.j.christopherson@intel.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org
Subject: [PATCH v2] KVM: x86: Unexport x86_fpu_cache and make it static
Date: Mon,  8 Jun 2020 11:02:18 -0700
Message-Id: <20200608180218.20946-1-sean.j.christopherson@intel.com>
X-Mailer: git-send-email 2.26.0
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Make x86_fpu_cache static now that FPU allocation and destruction is
handled entirely by common x86 code.

Signed-off-by: Sean Christopherson <sean.j.christopherson@intel.com>
---

v2: Rebased to kvm/queue, commit fb7333dfd812 ("KVM: SVM: fix calls ...").

 arch/x86/include/asm/kvm_host.h | 1 -
 arch/x86/kvm/x86.c              | 3 +--
 2 files changed, 1 insertion(+), 3 deletions(-)

```
#### [PATCH v2] x86/cpu: Reinitialize IA32_FEAT_CTL MSR on BSP during wakeup
##### From: Sean Christopherson <sean.j.christopherson@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Sean Christopherson <sean.j.christopherson@intel.com>
X-Patchwork-Id: 11593773
Return-Path: <SRS0=GUoK=7V=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 504F990
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon,  8 Jun 2020 17:49:51 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 3D80E20814
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon,  8 Jun 2020 17:49:51 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1730341AbgFHRts (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 8 Jun 2020 13:49:48 -0400
Received: from mga04.intel.com ([192.55.52.120]:11150 "EHLO mga04.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1730247AbgFHRts (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 8 Jun 2020 13:49:48 -0400
IronPort-SDR: 
 v62WnqnW/CNcsjzCc9QHAvI9TpTWk+je1kVzaCUA47AuXms0bY1oJc1ghoBt0hiPKXapZXIYfU
 Eew0dxRKRusg==
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from orsmga004.jf.intel.com ([10.7.209.38])
  by fmsmga104.fm.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 08 Jun 2020 10:49:45 -0700
IronPort-SDR: 
 plH9hL/3uaiz4LrI869hiDPlJo9zwuQekZQbWDqHmJq3YVsL3tRjGOPHnyUBU1u01b1h6neVw0
 9hO14zg240mA==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.73,487,1583222400";
   d="scan'208";a="418133308"
Received: from sjchrist-coffee.jf.intel.com ([10.54.74.152])
  by orsmga004.jf.intel.com with ESMTP; 08 Jun 2020 10:49:45 -0700
From: Sean Christopherson <sean.j.christopherson@intel.com>
To: Thomas Gleixner <tglx@linutronix.de>,
        Ingo Molnar <mingo@redhat.com>, Borislav Petkov <bp@alien8.de>,
        x86@kernel.org, Tony W Wang-oc <TonyWWang-oc@zhaoxin.com>,
        "Rafael J. Wysocki" <rjw@rjwysocki.net>,
        Pavel Machek <pavel@ucw.cz>
Cc: "H. Peter Anvin" <hpa@zytor.com>, linux-kernel@vger.kernel.org,
        linux-pm@vger.kernel.org,
        Brad Campbell <lists2009@fnarfbargle.com>,
        Liam Merwick <liam.merwick@oracle.com>,
        Maxim Levitsky <mlevitsk@redhat.com>,
        Paolo Bonzini <pbonzini@redhat.com>, kvm@vger.kernel.org,
        Sean Christopherson <sean.j.christopherson@intel.com>
Subject: [PATCH v2] x86/cpu: Reinitialize IA32_FEAT_CTL MSR on BSP during
 wakeup
Date: Mon,  8 Jun 2020 10:41:34 -0700
Message-Id: <20200608174134.11157-1-sean.j.christopherson@intel.com>
X-Mailer: git-send-email 2.26.0
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Reinitialize IA32_FEAT_CTL on the BSP during wakeup to handle the case
where firmware doesn't initialize or save/restore across S3.  This fixes
a bug where IA32_FEAT_CTL is left uninitialized and results in VMXON
taking a #GP due to VMX not being fully enabled, i.e. breaks KVM.

Use init_ia32_feat_ctl() to "restore" IA32_FEAT_CTL as it already deals
with the case where the MSR is locked, and because APs already redo
init_ia32_feat_ctl() during suspend by virtue of the SMP boot flow being
used to reinitialize APs upon wakeup.  Do the call in the early wakeup
flow to avoid dependencies in the syscore_ops chain, e.g. simply adding
a resume hook is not guaranteed to work, as KVM does VMXON in its own
resume hook, kvm_resume(), when KVM has active guests.

Reported-by: Brad Campbell <lists2009@fnarfbargle.com>
Tested-by: Brad Campbell <lists2009@fnarfbargle.com>
Reviewed-by: Liam Merwick <liam.merwick@oracle.com>
Reviewed-by: Maxim Levitsky <mlevitsk@redhat.com>
Cc: Paolo Bonzini <pbonzini@redhat.com>
Cc: kvm@vger.kernel.org
Cc: stable@vger.kernel.org # v5.6
Fixes: 21bd3467a58e ("KVM: VMX: Drop initialization of IA32_FEAT_CTL MSR")
Signed-off-by: Sean Christopherson <sean.j.christopherson@intel.com>
---

v2:
  - Collect Reviewed/Tested tags. [Brad, Liam, Maxim].
  - Include asm/cpu.h to fix Zhaoxin and Centaur builds. [Brad, LKP]
  - Add Cc to stable. [Liam]

 arch/x86/include/asm/cpu.h    | 5 +++++
 arch/x86/kernel/cpu/centaur.c | 1 +
 arch/x86/kernel/cpu/cpu.h     | 4 ----
 arch/x86/kernel/cpu/zhaoxin.c | 1 +
 arch/x86/power/cpu.c          | 6 ++++++
 5 files changed, 13 insertions(+), 4 deletions(-)

```
#### [PATCH][v7] KVM: X86: support APERF/MPERF registers
##### From: Li RongQing <lirongqing@baidu.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Li RongQing <lirongqing@baidu.com>
X-Patchwork-Id: 11592871
Return-Path: <SRS0=GUoK=7V=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 3FA08913
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon,  8 Jun 2020 09:34:41 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 272D12076C
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon,  8 Jun 2020 09:34:41 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729196AbgFHJeg (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 8 Jun 2020 05:34:36 -0400
Received: from mx57.baidu.com ([61.135.168.57]:37536 "EHLO
        tc-sys-mailedm05.tc.baidu.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S1729156AbgFHJef (ORCPT
        <rfc822;kvm@vger.kernel.org>); Mon, 8 Jun 2020 05:34:35 -0400
Received: from localhost (cp01-cos-dev01.cp01.baidu.com [10.92.119.46])
        by tc-sys-mailedm05.tc.baidu.com (Postfix) with ESMTP id 9C1AF1EBA001;
        Mon,  8 Jun 2020 17:34:18 +0800 (CST)
From: Li RongQing <lirongqing@baidu.com>
To: linux-kernel@vger.kernel.org, kvm@vger.kernel.org, x86@kernel.org,
        hpa@zytor.com, bp@alien8.de, mingo@redhat.com, tglx@linutronix.de,
        jmattson@google.com, wanpengli@tencent.com, vkuznets@redhat.com,
        sean.j.christopherson@intel.com, pbonzini@redhat.com,
        xiaoyao.li@intel.com, lirongqing@baidu.com, wei.huang2@amd.com
Subject: [PATCH][v7] KVM: X86: support APERF/MPERF registers
Date: Mon,  8 Jun 2020 17:34:18 +0800
Message-Id: <1591608858-10935-1-git-send-email-lirongqing@baidu.com>
X-Mailer: git-send-email 1.7.1
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Guest kernel reports a fixed cpu frequency in /proc/cpuinfo,
this is confused to user when turbo is enable, and aperf/mperf
can be used to show current cpu frequency after 7d5905dc14a
"(x86 / CPU: Always show current CPU frequency in /proc/cpuinfo)"
so guest should support aperf/mperf capability

This patch implements aperf/mperf by three mode: none, software
emulation, and pass-through

None: default mode, guest does not support aperf/mperf

Software emulation: the period of aperf/mperf in guest mode are
accumulated as emulated value

Pass-though: it is only suitable for pinned vcpu

And a per-VM capability is added to configure aperfmperf mode

Signed-off-by: Li RongQing <lirongqing@baidu.com>
Signed-off-by: Chai Wen <chaiwen@baidu.com>
Signed-off-by: Jia Lina <jialina01@baidu.com>

diff v6:
drop the unneed check from kvm_update_cpuid and __do_cpuid_func
add the validation check in kvm_vm_ioctl_enable_cap
thank for Jim Mattson,  Paolo Bonzini and Xiaoyao Li

diff v5:
return error if guest is configured with aperf/mperf, but host cpu has not

diff v4:
fix maybe-uninitialized warning

diff v3:
fix interception of MSR_IA32_APERF/MPERF in svm
thanks for wei.huang2 

diff v2:
support aperfmperf pass though
move common codes to kvm_get_msr_common
thanks for Xiaoyao Li and Peter Zijlstra

diff v1:
1. support AMD, but not test
2. support per-vm capability to enable
Documentation/virt/kvm/api.rst  | 16 ++++++++++++
 arch/x86/include/asm/kvm_host.h | 11 ++++++++
 arch/x86/kvm/svm/svm.c          |  8 ++++++
 arch/x86/kvm/vmx/vmx.c          |  6 +++++
 arch/x86/kvm/x86.c              | 56 +++++++++++++++++++++++++++++++++++++++++
 arch/x86/kvm/x86.h              | 15 +++++++++++
 include/uapi/linux/kvm.h        |  1 +
 7 files changed, 113 insertions(+)

```
#### [PATCH RFC v6 01/11] vhost: option to fetch descriptors through an independent struct
##### From: "Michael S. Tsirkin" <mst@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 8bit
X-Patchwork-Submitter: "Michael S. Tsirkin" <mst@redhat.com>
X-Patchwork-Id: 11593319
Return-Path: <SRS0=GUoK=7V=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 10B3E90
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon,  8 Jun 2020 12:55:15 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id DCACA2078D
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon,  8 Jun 2020 12:55:14 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="ZvBEBVz2"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729831AbgFHMyd (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 8 Jun 2020 08:54:33 -0400
Received: from us-smtp-1.mimecast.com ([205.139.110.61]:24955 "EHLO
        us-smtp-delivery-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S1729562AbgFHMxO (ORCPT
        <rfc822;kvm@vger.kernel.org>); Mon, 8 Jun 2020 08:53:14 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1591620791;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:content-type:content-type:
         content-transfer-encoding:content-transfer-encoding:
         in-reply-to:in-reply-to:references:references;
        bh=pyZgoc1IoaMWB9Jefr7e/GoAFJJxo7imj3dgpBB/etA=;
        b=ZvBEBVz2xIoW3KgMCmE7cwtAtKilrGaCLLOPI34JEdebZpArFaYtHTddj+SF6m3RyHvMGh
        5YsLrY7nNd5TSa/UeCLJZOpmXbVNQG1XYDUjuyeGsWQjs2PX/ymMsKvz6ckkdxHzn8tQUj
        LV0zruHvqbKgAgZG4e3t90t42uEvYWs=
Received: from mail-wm1-f70.google.com (mail-wm1-f70.google.com
 [209.85.128.70]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-344-E4aHXkM3OeOUUYv2wu6yGg-1; Mon, 08 Jun 2020 08:52:58 -0400
X-MC-Unique: E4aHXkM3OeOUUYv2wu6yGg-1
Received: by mail-wm1-f70.google.com with SMTP id p24so1497796wma.4
        for <kvm@vger.kernel.org>; Mon, 08 Jun 2020 05:52:57 -0700 (PDT)
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:date:from:to:cc:subject:message-id:references
         :mime-version:content-disposition:content-transfer-encoding
         :in-reply-to;
        bh=pyZgoc1IoaMWB9Jefr7e/GoAFJJxo7imj3dgpBB/etA=;
        b=j/1k4me6ZoYYF4TkyBlveXbFDuvB2x2qZaBAk3vDF1dvsb5nD0H6wfSoY+7QVcdnv6
         weiZqwhY9CfOqk4vkS5PyS+VDBDCHQbqPsNsSrGFQIxLoTfyo89cH79ktdPmajcpjBMR
         ePKvJ/3NkCLojljaYrU19skTCsbpj8Qu+lkJG2BsPbIZmh/239/dY79qlnBM6sVucN1h
         Q5X+cBa69guXHZF51gdu9pw9MojvqKixrewr35wnfXfgqRqUAV+bgZLkLb2AoCzCaUZR
         4aw5Wz+tbWDQjN4W8PGq79c5jL6ZicOdyjJ3EHXD4vX8vxSJ7cVsXt6hlu2w2TgKRWi3
         XuvA==
X-Gm-Message-State: AOAM531WCGb9rWIIGJ0Xv7RI3GBgirYHrFGKLDIxgITHuC0yBdY9fFtM
        lECO9GrQVvF69Z3YgRmbUA6UqkXQwkNtV66/eXJwr6bHuFZDf/sUwurZ0Kb4K26rWdBIueWS2+o
        2XvxbPWyQU+zy
X-Received: by 2002:a7b:cb93:: with SMTP id
 m19mr17016542wmi.165.1591620776336;
        Mon, 08 Jun 2020 05:52:56 -0700 (PDT)
X-Google-Smtp-Source: 
 ABdhPJzEdknqoJU3HSkUfhKPXzphp7+7B7/1HQpacB61dXsZyraKBYychpqxInl7px+4iWcK/8HI/Q==
X-Received: by 2002:a7b:cb93:: with SMTP id
 m19mr17016499wmi.165.1591620775843;
        Mon, 08 Jun 2020 05:52:55 -0700 (PDT)
Received: from redhat.com (bzq-109-64-41-91.red.bezeqint.net. [109.64.41.91])
        by smtp.gmail.com with ESMTPSA id
 g187sm22919251wma.17.2020.06.08.05.52.54
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Mon, 08 Jun 2020 05:52:55 -0700 (PDT)
Date: Mon, 8 Jun 2020 08:52:53 -0400
From: "Michael S. Tsirkin" <mst@redhat.com>
To: linux-kernel@vger.kernel.org
Cc: kvm@vger.kernel.org, virtualization@lists.linux-foundation.org,
        netdev@vger.kernel.org, Jason Wang <jasowang@redhat.com>,
        eperezma@redhat.com
Subject: [PATCH RFC v6 01/11] vhost: option to fetch descriptors through an
 independent struct
Message-ID: <20200608125238.728563-2-mst@redhat.com>
References: <20200608125238.728563-1-mst@redhat.com>
MIME-Version: 1.0
Content-Disposition: inline
In-Reply-To: <20200608125238.728563-1-mst@redhat.com>
X-Mailer: git-send-email 2.24.1.751.gd10ce2899c
X-Mutt-Fcc: =sent
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The idea is to support multiple ring formats by converting
to a format-independent array of descriptors.

This costs extra cycles, but we gain in ability
to fetch a batch of descriptors in one go, which
is good for code cache locality.

When used, this causes a minor performance degradation,
it's been kept as simple as possible for ease of review.
A follow-up patch gets us back the performance by adding batching.

To simplify benchmarking, I kept the old code around so one can switch
back and forth between old and new code. This will go away in the final
submission.

Signed-off-by: Michael S. Tsirkin <mst@redhat.com>
Signed-off-by: Eugenio Pérez <eperezma@redhat.com>
Link: https://lore.kernel.org/r/20200401183118.8334-2-eperezma@redhat.com
Signed-off-by: Michael S. Tsirkin <mst@redhat.com>
---
 drivers/vhost/vhost.c | 305 +++++++++++++++++++++++++++++++++++++++++-
 drivers/vhost/vhost.h |  16 +++
 2 files changed, 320 insertions(+), 1 deletion(-)

```
#### [PATCH] vhost/test: fix up after API change
##### From: "Michael S. Tsirkin" <mst@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: "Michael S. Tsirkin" <mst@redhat.com>
X-Patchwork-Id: 11593281
Return-Path: <SRS0=GUoK=7V=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 630441391
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon,  8 Jun 2020 12:43:29 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 46B492072F
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon,  8 Jun 2020 12:43:29 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="TyCgMLOD"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729040AbgFHMn0 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 8 Jun 2020 08:43:26 -0400
Received: from us-smtp-delivery-1.mimecast.com ([207.211.31.120]:49498 "EHLO
        us-smtp-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org
        with ESMTP id S1728684AbgFHMnY (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 8 Jun 2020 08:43:24 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1591620202;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:content-type:content-type;
        bh=utvLOGjABWchDzVBBNcvjGgT0Uw4uVA8BCJYHrkDTYE=;
        b=TyCgMLODxX0a9jzlp75v5jJdlB/ziQNUZGG1WFR4A1VSJIXaKZL0jHDPKPxvBk36zGfPGV
        Wm68hG1vlF+FKx1KiRVln78MzBLMBXw9e1DoWFHgU0c44YVcA0QoVqCJ97sc0Dxg4+L062
        DBCepTeUpfOWILkpU7co5aKxYyNROn8=
Received: from mail-wm1-f69.google.com (mail-wm1-f69.google.com
 [209.85.128.69]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-283-MAajVjWZM92dYktXTB2bTg-1; Mon, 08 Jun 2020 08:42:59 -0400
X-MC-Unique: MAajVjWZM92dYktXTB2bTg-1
Received: by mail-wm1-f69.google.com with SMTP id k185so3890044wme.8
        for <kvm@vger.kernel.org>; Mon, 08 Jun 2020 05:42:59 -0700 (PDT)
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:date:from:to:cc:subject:message-id:mime-version
         :content-disposition;
        bh=utvLOGjABWchDzVBBNcvjGgT0Uw4uVA8BCJYHrkDTYE=;
        b=Mcf/6vmQ3TK/xzZA3GvMMghpmymXDAj1zDDRuuYbsBNEJTy7GXdbVvppxKXrwJFqFa
         MywLSkju4V4+ylzEeQ/mHjfuotl13MrGZxqo2ECmYWZEhJWDC8OWb3gDYBrSezDit8gY
         SkaScSAEtNey9miMAeVyASj9MicDJJWIHqyXcBCL3O+foqvbgURGK9IRyUn6A6tli2In
         k/xmq4Liv1iuauG/suW02Qo9ROsEkR86jIrn/GQzr5ZSo4MEHzfoqgyy756vzmiSAuid
         JITD2mI6Sch7I845S/pYTqFEHTMrb8NCOqMZIoRMR/frb9EPip5soa/tRC4piwM7JARW
         Or0g==
X-Gm-Message-State: AOAM5326FF91+NylQ3zo/+AYa67ArQImamfrj3WsoFOyszo8duxLEanc
        gzYmASsYBwUaX+bFXCjBzaNmxFwUivxHp8CIJ0mK6yKN8Ckr6/H0rYGxexXdfVdN1tei5JQ8Rp8
        8UJUnr78iHrX9
X-Received: by 2002:a1c:5411:: with SMTP id
 i17mr17027053wmb.137.1591620178213;
        Mon, 08 Jun 2020 05:42:58 -0700 (PDT)
X-Google-Smtp-Source: 
 ABdhPJxxHCDKaiMql4q+MgfnmT9afh3wFAhLtf//8SgAbDqi4VLnsVn3wc/xBGn3Rmk2vnzUyPWpJw==
X-Received: by 2002:a1c:5411:: with SMTP id
 i17mr17027042wmb.137.1591620178029;
        Mon, 08 Jun 2020 05:42:58 -0700 (PDT)
Received: from redhat.com (bzq-109-64-41-91.red.bezeqint.net. [109.64.41.91])
        by smtp.gmail.com with ESMTPSA id
 g82sm22458959wmf.1.2020.06.08.05.42.56
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Mon, 08 Jun 2020 05:42:57 -0700 (PDT)
Date: Mon, 8 Jun 2020 08:42:56 -0400
From: "Michael S. Tsirkin" <mst@redhat.com>
To: linux-kernel@vger.kernel.org
Cc: Jason Wang <jasowang@redhat.com>,
        Zhu Lingshan <lingshan.zhu@intel.com>, kvm@vger.kernel.org,
        virtualization@lists.linux-foundation.org, netdev@vger.kernel.org
Subject: [PATCH] vhost/test: fix up after API change
Message-ID: <20200608124254.727184-1-mst@redhat.com>
MIME-Version: 1.0
Content-Disposition: inline
X-Mailer: git-send-email 2.24.1.751.gd10ce2899c
X-Mutt-Fcc: =sent
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Pass a flag to request kernel thread use.

Fixes: 01fcb1cbc88e ("vhost: allow device that does not depend on vhost worker")
Signed-off-by: Michael S. Tsirkin <mst@redhat.com>
---
 drivers/vhost/test.c | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
