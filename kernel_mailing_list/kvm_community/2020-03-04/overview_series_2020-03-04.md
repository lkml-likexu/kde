#### [PATCH v5 01/23] irqchip/gic-v3: Use SGIs without active state if offered
##### From: Marc Zyngier <maz@kernel.org>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Marc Zyngier <maz@kernel.org>
X-Patchwork-Id: 11420703
Return-Path: <SRS0=VNnu=4V=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 542B31395
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed,  4 Mar 2020 20:35:19 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 3572C2146E
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed,  4 Mar 2020 20:35:19 +0000 (UTC)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple; d=kernel.org;
	s=default; t=1583354119;
	bh=Y2twFTizyQFJpwdfCf8dMfeH0eDUliV8ynLpzQaEOOk=;
	h=From:To:Cc:Subject:Date:In-Reply-To:References:List-ID:From;
	b=feMAMfzMR/wQFIFe6wLbQ4XnNJBayAG2xJwlbpY+H0diEvooMxTTgn5HVkTOaRydj
	 jkIZke1U/7CX6MoLH8q9gtaf6y1TzJ6NXnxap42TyiEXH20abGFNzc/NQMIKeaL/Af
	 Wl+nlp6xiAKJH0Ax/UhnyOr9g25XG1PTjO/dcXzM=
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2388154AbgCDUem (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 4 Mar 2020 15:34:42 -0500
Received: from mail.kernel.org ([198.145.29.99]:34684 "EHLO mail.kernel.org"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1728614AbgCDUel (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 4 Mar 2020 15:34:41 -0500
Received: from disco-boy.misterjones.org (disco-boy.misterjones.org
 [51.254.78.96])
        (using TLSv1.2 with cipher ECDHE-RSA-AES256-GCM-SHA384 (256/256 bits))
        (No client certificate requested)
        by mail.kernel.org (Postfix) with ESMTPSA id 0603221739;
        Wed,  4 Mar 2020 20:34:40 +0000 (UTC)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple; d=kernel.org;
        s=default; t=1583354080;
        bh=Y2twFTizyQFJpwdfCf8dMfeH0eDUliV8ynLpzQaEOOk=;
        h=From:To:Cc:Subject:Date:In-Reply-To:References:From;
        b=jQCm6u6ov3clu11Tpu16iB6eud04xmTb6leQX144II07jFu3DMu0Me3FtIK5jXu7e
         3PETV2VDmeHwvWD81tKWYH+lk6l5WOalBRrKooNXFHJGif0P7RZama9SbhEuTerZqX
         8yTJywqonD9skfAKpFvISmAMttMnquqvUgSfaNTM=
Received: from 78.163-31-62.static.virginmediabusiness.co.uk ([62.31.163.78]
 helo=why.lan)
        by disco-boy.misterjones.org with esmtpsa
 (TLS1.3:ECDHE_RSA_AES_256_GCM_SHA384:256)
        (Exim 4.92)
        (envelope-from <maz@kernel.org>)
        id 1j9aj0-00A59R-51; Wed, 04 Mar 2020 20:34:38 +0000
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
Subject: [PATCH v5 01/23] irqchip/gic-v3: Use SGIs without active state if
 offered
Date: Wed,  4 Mar 2020 20:33:08 +0000
Message-Id: <20200304203330.4967-2-maz@kernel.org>
X-Mailer: git-send-email 2.20.1
In-Reply-To: <20200304203330.4967-1-maz@kernel.org>
References: <20200304203330.4967-1-maz@kernel.org>
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
---
 drivers/irqchip/irq-gic-v3.c       | 10 ++++++++--
 include/linux/irqchip/arm-gic-v3.h |  2 ++
 2 files changed, 10 insertions(+), 2 deletions(-)

```
#### [PATCH v5 01/14] KVM: X86: Change parameter for fast_page_fault tracepoint
##### From: Peter Xu <peterx@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Peter Xu <peterx@redhat.com>
X-Patchwork-Id: 11420539
Return-Path: <SRS0=VNnu=4V=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 88CD7921
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed,  4 Mar 2020 17:49:57 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 696E322B48
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed,  4 Mar 2020 17:49:57 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="GHnVeEFJ"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1730038AbgCDRt5 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 4 Mar 2020 12:49:57 -0500
Received: from us-smtp-delivery-1.mimecast.com ([207.211.31.120]:24442 "EHLO
        us-smtp-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org
        with ESMTP id S1729600AbgCDRt4 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 4 Mar 2020 12:49:56 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1583344195;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding:
         in-reply-to:in-reply-to:references:references;
        bh=zL6sq31OFwBXF/RS7PK1GArrpq69jRR45bepTSw46TU=;
        b=GHnVeEFJSTGLz91LkNZEHvh2zeylxJCjSuMipTyfiyRxY6hWmTJsXNDuyBI4QENpB4a18j
        f0I6mTOp95Ze2n6Ar/iBRha3T0O493d/6WoqddVELKryW4r5wcH2v77gkvFWf4ePb2XTG5
        iSuiVhb/mKP3/kuV76jeKDAOJ2NuQ7o=
Received: from mail-qv1-f70.google.com (mail-qv1-f70.google.com
 [209.85.219.70]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-69-I6GU12VgOFC8gqPqTlBX3A-1; Wed, 04 Mar 2020 12:49:54 -0500
X-MC-Unique: I6GU12VgOFC8gqPqTlBX3A-1
Received: by mail-qv1-f70.google.com with SMTP id l7so1418237qvt.22
        for <kvm@vger.kernel.org>; Wed, 04 Mar 2020 09:49:54 -0800 (PST)
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:in-reply-to
         :references:mime-version:content-transfer-encoding;
        bh=zL6sq31OFwBXF/RS7PK1GArrpq69jRR45bepTSw46TU=;
        b=oeGU5gVGBGFkH56B/RnNO3o+PqhLJ0ugZ0ya4bHFCuOOFJlXXpz9ZUJcvGEaQhm1kL
         3Yun1sqbPiV6IE+vBfRKw5JP3cVLUUwltWBjrb8ThjESdKkr3F9+7LwpgUSoO8vZYRpR
         IoLN+LPyNan1Qnoi/RscRX5KTJmmaseJE5npifi6mYdAU17ZFP/b1KxjKXIQN8OdkKpl
         0aLmLvAignWINtN27HbqSh+TLUHZgehS3lkuiO4327x/UOpkNStViRuzdf0eDUiYMWKd
         Qq+GyWDiw4b90/tCT1rNMBR2HvTkwhO9aTQJPINb6cifTHyFH1kom81TTwIkfNl8OfaD
         GsvA==
X-Gm-Message-State: ANhLgQ2YNo87UC14d4pCbq1xAT6yzwW1P9pnXHQGdjwBs3EHh08Npi6i
        +2il+uWM3wlZWufYrpk46zwAI/WDttVV96L/NmHZqrbC7xqnsJbzWBRjnPhlA62VSoqKa9R13Tc
        zlV5PcsnpqK3F
X-Received: by 2002:ac8:534b:: with SMTP id d11mr3512254qto.101.1583344194069;
        Wed, 04 Mar 2020 09:49:54 -0800 (PST)
X-Google-Smtp-Source: 
 ADFU+vsEcJ8+mn9bDrZSYhkrNp5+S9+YoenWyrwAv3oEiBqUoFFjT9yfw5nnfEEcipf3nFOz7+yVbQ==
X-Received: by 2002:ac8:534b:: with SMTP id d11mr3512237qto.101.1583344193844;
        Wed, 04 Mar 2020 09:49:53 -0800 (PST)
Received: from xz-x1.redhat.com ([2607:9880:19c0:32::2])
        by smtp.gmail.com with ESMTPSA id
 j4sm6990420qtv.45.2020.03.04.09.49.52
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Wed, 04 Mar 2020 09:49:53 -0800 (PST)
From: Peter Xu <peterx@redhat.com>
To: linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Cc: Yan Zhao <yan.y.zhao@intel.com>, peterx@redhat.com,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        "Michael S . Tsirkin" <mst@redhat.com>,
        Alex Williamson <alex.williamson@redhat.com>,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        "Dr . David Alan Gilbert" <dgilbert@redhat.com>,
        Jason Wang <jasowang@redhat.com>,
        Kevin Tian <kevin.tian@intel.com>,
        Paolo Bonzini <pbonzini@redhat.com>,
        Christophe de Dinechin <dinechin@redhat.com>
Subject: [PATCH v5 01/14] KVM: X86: Change parameter for fast_page_fault
 tracepoint
Date: Wed,  4 Mar 2020 12:49:34 -0500
Message-Id: <20200304174947.69595-2-peterx@redhat.com>
X-Mailer: git-send-email 2.24.1
In-Reply-To: <20200304174947.69595-1-peterx@redhat.com>
References: <20200304174947.69595-1-peterx@redhat.com>
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

It would be clearer to dump the return value to know easily on whether
did we go through the fast path for handling current page fault.
Remove the old two last parameters because after all the old/new sptes
were dumped in the same line.

Signed-off-by: Peter Xu <peterx@redhat.com>
---
 arch/x86/kvm/mmutrace.h | 9 ++-------
 1 file changed, 2 insertions(+), 7 deletions(-)

```
#### [PATCH] KVM: Drop gfn_to_pfn_atomic()
##### From: Peter Xu <peterx@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Peter Xu <peterx@redhat.com>
X-Patchwork-Id: 11420575
Return-Path: <SRS0=VNnu=4V=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 7AC3B921
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed,  4 Mar 2020 17:52:03 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 5A69921D56
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed,  4 Mar 2020 17:52:03 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="akvkN1fH"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1730146AbgCDRv7 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 4 Mar 2020 12:51:59 -0500
Received: from us-smtp-delivery-1.mimecast.com ([205.139.110.120]:57554 "EHLO
        us-smtp-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org
        with ESMTP id S1730108AbgCDRv5 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 4 Mar 2020 12:51:57 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1583344316;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=IJXI3OyHBMNvDSp9XDQtawbxBSkKafXuFCrtPHquIJw=;
        b=akvkN1fHlnK7OgqWCEJIp1VwCHIjSu5Rdeb+ujQEUW4IL8h/UtVnARklOIF8mAqgazOeXo
        01KoownD91HYeEdBJDBT2TQF+qu+tgb9L48+BWV5niFwc+K/Xyl0YZaer0V9R49b8m/QQ4
        EjiyiAqaYfJ3Ew4HLTGjRinHzf9FJ6w=
Received: from mail-qv1-f69.google.com (mail-qv1-f69.google.com
 [209.85.219.69]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-352-8olOCbdmOTCF1QC9Z6HswA-1; Wed, 04 Mar 2020 12:51:55 -0500
X-MC-Unique: 8olOCbdmOTCF1QC9Z6HswA-1
Received: by mail-qv1-f69.google.com with SMTP id l16so1342173qvo.15
        for <kvm@vger.kernel.org>; Wed, 04 Mar 2020 09:51:55 -0800 (PST)
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:mime-version
         :content-transfer-encoding;
        bh=IJXI3OyHBMNvDSp9XDQtawbxBSkKafXuFCrtPHquIJw=;
        b=K5F49Dm9+qaMYGcKyYRPb5IBEpXFznZIaoaXXCDx8KGlFc/aAiPXa4DVz0wQhs6QgA
         T5iJ8cussetQEGCMzBjsUPhdfO/ZwI9xTjTEbY5JnUKyxZ+nPzvTkMMzucqzpb0xsuva
         wOQ62fpuFi6IRlg0OCWkrkij+dku2xNe9QY3Pd1VatcaZUErw6Bee+7T3CwK8BuVadJ4
         NI3JB/4wSTOlO6wRRi8koaYao6qrTY4OMPzLDx9lQW2ozEUaE3zXdJr/5Su16pKP5mt4
         0jwKUD3jZj+geaoZLAR3Jfh8t8Yg4nWzDOvMrmZLoW6aca9QrpauUH52dLPk0CoNiY4P
         dAUQ==
X-Gm-Message-State: ANhLgQ06spDYdoQTOEzF5gtQFUw1GuUQ70nJQDhflZVEa2LE5T6Ncb/k
        AyEmrrambnjeC7BaC5CW8HLlbYfzB9OzahijxYLo/W7lQHQ34uyQ8JZXTZfdtmU4T8TXXy6UvDD
        b3f+FNcks2pjK
X-Received: by 2002:ac8:5190:: with SMTP id c16mr3490703qtn.200.1583344314481;
        Wed, 04 Mar 2020 09:51:54 -0800 (PST)
X-Google-Smtp-Source: 
 ADFU+vtWEE5pJUAb30CAlOc0HdE+PUBn4KyN4CpVzLvvvPRbZcbJ8+PWR7QVW9jUIxp3W8cZRXvkfA==
X-Received: by 2002:ac8:5190:: with SMTP id c16mr3490689qtn.200.1583344314257;
        Wed, 04 Mar 2020 09:51:54 -0800 (PST)
Received: from xz-x1.redhat.com ([2607:9880:19c0:32::2])
        by smtp.gmail.com with ESMTPSA id
 o4sm14008251qki.26.2020.03.04.09.51.53
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Wed, 04 Mar 2020 09:51:53 -0800 (PST)
From: Peter Xu <peterx@redhat.com>
To: linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Cc: peterx@redhat.com, Paolo Bonzini <pbonzini@redhat.com>
Subject: [PATCH] KVM: Drop gfn_to_pfn_atomic()
Date: Wed,  4 Mar 2020 12:51:52 -0500
Message-Id: <20200304175152.70471-1-peterx@redhat.com>
X-Mailer: git-send-email 2.24.1
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

It's never used anywhere now.

Signed-off-by: Peter Xu <peterx@redhat.com>
---
 include/linux/kvm_host.h | 1 -
 virt/kvm/kvm_main.c      | 6 ------
 2 files changed, 7 deletions(-)

```
#### [PATCH] KVM: fix Kconfig menu text for -Werror
##### From: "Jason A. Donenfeld" <Jason@zx2c4.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: "Jason A. Donenfeld" <Jason@zx2c4.com>
X-Patchwork-Id: 11419845
Return-Path: <SRS0=VNnu=4V=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 0300A921
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed,  4 Mar 2020 10:42:52 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id D80242166E
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed,  4 Mar 2020 10:42:51 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=zx2c4.com header.i=@zx2c4.com
 header.b="0xbXKYD5"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2387860AbgCDKms (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 4 Mar 2020 05:42:48 -0500
Received: from frisell.zx2c4.com ([192.95.5.64]:37919 "EHLO frisell.zx2c4.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S2387396AbgCDKms (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 4 Mar 2020 05:42:48 -0500
Received: by frisell.zx2c4.com (ZX2C4 Mail Server) with ESMTP id 320b1e17;
        Wed, 4 Mar 2020 10:38:14 +0000 (UTC)
DKIM-Signature: v=1; a=rsa-sha1; c=relaxed; d=zx2c4.com; h=from:to:cc
        :subject:date:message-id:mime-version:content-transfer-encoding;
         s=mail; bh=woDMe5KTrxlQuzyXF8mQxtdX4Mo=; b=0xbXKYD5rqE3JWWxTtse
        Bv4B/YLWwA7hDha5wuHTUmcnS3M9aBoyrna1pQQvJtebgO0bOaVldaJal1KYvxgD
        WrpwNR5+MB/tBJQeY6tW1xwvrAH3nF4IiPg+pEoRBz/LG170DRwfB3+lrIPHieH9
        aCJd7Ng9p+504S8yoHC1Fv7SFPbE7EslRkRB4KFI1wi2CYsO+njwCvXSiobO1/Vh
        OxARR7tFSa/GHUPWkFKYcjiXiezSxjEZmC4jFlbkbG1UK5rfyD5t7UDEmTHuv7Yt
        Ep1IawimLNuGwem1LjHk7xDKwAxOZEMQdgAjo1qY55zR3rFWOnw7E2wo7c5m/bJt
        zw==
Received: by frisell.zx2c4.com (ZX2C4 Mail Server) with ESMTPSA id 0033f560
 (TLSv1.2:ECDHE-RSA-AES256-GCM-SHA384:256:NO);
        Wed, 4 Mar 2020 10:38:13 +0000 (UTC)
From: "Jason A. Donenfeld" <Jason@zx2c4.com>
To: pbonzini@redhat.com, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org
Cc: "Jason A. Donenfeld" <Jason@zx2c4.com>
Subject: [PATCH] KVM: fix Kconfig menu text for -Werror
Date: Wed,  4 Mar 2020 18:42:21 +0800
Message-Id: <20200304104221.2977-1-Jason@zx2c4.com>
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This was evidently copy and pasted from the i915 driver, but the text
wasn't updated.

Fixes: 4f337faf1c55 ("KVM: allow disabling -Werror")
Signed-off-by: Jason A. Donenfeld <Jason@zx2c4.com>
---
 arch/x86/kvm/Kconfig | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
#### [PATCH] kvm: support to get/set dirty log initial-all-set capability
##### From: Jay Zhou <jianjay.zhou@huawei.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Jay Zhou <jianjay.zhou@huawei.com>
X-Patchwork-Id: 11419191
Return-Path: <SRS0=VNnu=4V=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 0619A92A
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed,  4 Mar 2020 02:56:11 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id E2F2C20866
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed,  4 Mar 2020 02:56:10 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2387532AbgCDC4K (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 3 Mar 2020 21:56:10 -0500
Received: from szxga05-in.huawei.com ([45.249.212.191]:10721 "EHLO huawei.com"
        rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org with ESMTP
        id S2387398AbgCDC4K (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 3 Mar 2020 21:56:10 -0500
Received: from DGGEMS403-HUB.china.huawei.com (unknown [172.30.72.58])
        by Forcepoint Email with ESMTP id B3FB6199FD87F02F1DFD;
        Wed,  4 Mar 2020 10:56:07 +0800 (CST)
Received: from localhost (10.173.228.206) by DGGEMS403-HUB.china.huawei.com
 (10.3.19.203) with Microsoft SMTP Server id 14.3.439.0; Wed, 4 Mar 2020
 10:55:57 +0800
From: Jay Zhou <jianjay.zhou@huawei.com>
To: <qemu-devel@nongnu.org>, <kvm@vger.kernel.org>
CC: <pbonzini@redhat.com>, <mst@redhat.com>, <cohuck@redhat.com>,
        <peterx@redhat.com>, <wangxinxin.wang@huawei.com>,
        <weidong.huang@huawei.com>, <liu.jinsong@huawei.com>,
        <jianjay.zhou@huawei.com>
Subject: [PATCH] kvm: support to get/set dirty log initial-all-set capability
Date: Wed, 4 Mar 2020 10:55:54 +0800
Message-ID: <20200304025554.2159-1-jianjay.zhou@huawei.com>
X-Mailer: git-send-email 2.14.1.windows.1
MIME-Version: 1.0
X-Originating-IP: [10.173.228.206]
X-CFilter-Loop: Reflected
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Since the new capability KVM_DIRTY_LOG_INITIALLY_SET of
KVM_CAP_MANUAL_DIRTY_LOG_PROTECT2 has been introduced in the
kernel, tweak the userspace side to detect and enable this
capability.

Signed-off-by: Jay Zhou <jianjay.zhou@huawei.com>
Reviewed-by: Peter Xu <peterx@redhat.com>
---
 accel/kvm/kvm-all.c       | 21 ++++++++++++++-------
 linux-headers/linux/kvm.h |  3 +++
 2 files changed, 17 insertions(+), 7 deletions(-)

```
#### [kvm-unit-tests PATCH] x86: Move definition of some exception vectors into processor.h
##### From: Xiaoyao Li <xiaoyao.li@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Xiaoyao Li <xiaoyao.li@intel.com>
X-Patchwork-Id: 11419567
Return-Path: <SRS0=VNnu=4V=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 9905B92A
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed,  4 Mar 2020 08:06:51 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 818D1214D8
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed,  4 Mar 2020 08:06:51 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727176AbgCDIGu (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 4 Mar 2020 03:06:50 -0500
Received: from mga06.intel.com ([134.134.136.31]:29965 "EHLO mga06.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1725271AbgCDIGu (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 4 Mar 2020 03:06:50 -0500
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from orsmga008.jf.intel.com ([10.7.209.65])
  by orsmga104.jf.intel.com with ESMTP/TLS/DHE-RSA-AES256-GCM-SHA384;
 04 Mar 2020 00:06:49 -0800
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.70,513,1574150400";
   d="scan'208";a="233948346"
Received: from lxy-clx-4s.sh.intel.com ([10.239.43.160])
  by orsmga008.jf.intel.com with ESMTP; 04 Mar 2020 00:06:47 -0800
From: Xiaoyao Li <xiaoyao.li@intel.com>
To: pbonzini@redhat.com
Cc: kvm@vger.kernel.org, Xiaoyao Li <xiaoyao.li@intel.com>
Subject: [kvm-unit-tests PATCH] x86: Move definition of some exception vectors
 into processor.h
Date: Wed,  4 Mar 2020 15:49:32 +0800
Message-Id: <20200304074932.77095-1-xiaoyao.li@intel.com>
X-Mailer: git-send-email 2.20.1
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Both processor.h and desc.h hold some definitions of exception vector.
put them together in processor.h

Signed-off-by: Xiaoyao Li <xiaoyao.li@intel.com>
---
 lib/x86/desc.h      | 5 -----
 lib/x86/processor.h | 3 +++
 x86/debug.c         | 1 +
 x86/idt_test.c      | 1 +
 4 files changed, 5 insertions(+), 5 deletions(-)

```
#### [PATCH] KVM: X86: Avoid explictly fetch instruction in x86_decode_insn()
##### From: Peter Xu <peterx@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Peter Xu <peterx@redhat.com>
X-Patchwork-Id: 11419105
Return-Path: <SRS0=VNnu=4V=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id DC20D924
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed,  4 Mar 2020 02:17:04 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id BD9E12073D
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed,  4 Mar 2020 02:17:04 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="RkMGg80R"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2387432AbgCDCRB (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 3 Mar 2020 21:17:01 -0500
Received: from us-smtp-1.mimecast.com ([205.139.110.61]:29910 "EHLO
        us-smtp-delivery-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S2387397AbgCDCRA (ORCPT
        <rfc822;kvm@vger.kernel.org>); Tue, 3 Mar 2020 21:17:00 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1583288219;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=zwpmLVhYAg+RzC4wgoFG5yb2Ol28WwASDz+oEeK9Uow=;
        b=RkMGg80ReMekloKrhUk7steiD/j0iRh1+Vg3U/b+El4vCyvrWwy7FAqUmhwkFEumaMavTB
        yyo4gZhAS0aiTs+3CflFE1aYwSnfRmDEMhiMnSKZzylnMYVUWBF+GFNB9acgZlPZw8QwKi
        zUM2QXWC7m24dzz5CaeSzNhmK7aZvFo=
Received: from mail-qv1-f69.google.com (mail-qv1-f69.google.com
 [209.85.219.69]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-88-f7HNbWEsPbCV5WQKnCRhXw-1; Tue, 03 Mar 2020 21:16:54 -0500
X-MC-Unique: f7HNbWEsPbCV5WQKnCRhXw-1
Received: by mail-qv1-f69.google.com with SMTP id l16so93519qvo.15
        for <kvm@vger.kernel.org>; Tue, 03 Mar 2020 18:16:54 -0800 (PST)
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:mime-version
         :content-transfer-encoding;
        bh=zwpmLVhYAg+RzC4wgoFG5yb2Ol28WwASDz+oEeK9Uow=;
        b=ff+avXzZPEbV4bsd2xdAJdGcXvc7kr38TaxFaTyGElVcKvCJlrBMPPk80LZoCl2WjH
         XOFkOgkmD0SekmIOOZK/RQ3Dmhz+APR0swsAMJDeYLTKLoVBlgS+ZzEGRtPwOa5R8HTe
         ukwxH7Keeoz1VgPR5T5KohRV8yAnzSkCXY83vaX0aAt9O5WLJVYkoHKMlR0Xp2R/RStB
         9hNaN6OEjy3unyqc2VfQXnfAVbYg0Hih4dAt5XSKY7BrxAIi/gkGYxHF1MKMtbdPz8D3
         EPDj1FHwoecJbR3FQix40IADXC05++MfITVpFJ0dpnI0088brmRi5R24IU2fEEPZCtXD
         IPOw==
X-Gm-Message-State: ANhLgQ2y0WySlIBfHct3eXOYdNNUnGgTZvhndNFNeLwKqtxrkp2MT2+I
        5orfGQ4x2y4xJJ0qXQd/qKh9X87jaD44YETHMlTColQXGoDzl+z6MkI2p+qr4Z7aSz6Fnq1h8Qp
        0kl2n8yla/5Zm
X-Received: by 2002:a05:620a:350:: with SMTP id
 t16mr936781qkm.238.1583288214462;
        Tue, 03 Mar 2020 18:16:54 -0800 (PST)
X-Google-Smtp-Source: 
 ADFU+vu1ZMXcr1gqC/Zi87ZN+GHeSsAkSbjaQbQrEwLisqJpF+0jVmM6F3RpKZnuzgvqnsEWVWUn7Q==
X-Received: by 2002:a05:620a:350:: with SMTP id
 t16mr936762qkm.238.1583288214196;
        Tue, 03 Mar 2020 18:16:54 -0800 (PST)
Received: from xz-x1.hitronhub.home ([2607:9880:19c0:32::2])
        by smtp.gmail.com with ESMTPSA id
 n59sm4185363qtd.77.2020.03.03.18.16.52
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Tue, 03 Mar 2020 18:16:53 -0800 (PST)
From: Peter Xu <peterx@redhat.com>
To: linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Cc: Paolo Bonzini <pbonzini@redhat.com>,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        peterx@redhat.com, Vitaly Kuznetsov <vkuznets@redhat.com>
Subject: [PATCH] KVM: X86: Avoid explictly fetch instruction in
 x86_decode_insn()
Date: Tue,  3 Mar 2020 21:16:37 -0500
Message-Id: <20200304021637.17856-1-peterx@redhat.com>
X-Mailer: git-send-email 2.24.1
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

insn_fetch() will always implicitly refill instruction buffer properly
when the buffer is empty, so we don't need to explicitly fetch it even
if insn_len==0 for x86_decode_insn().

Signed-off-by: Peter Xu <peterx@redhat.com>
---
 arch/x86/kvm/emulate.c | 5 -----
 1 file changed, 5 deletions(-)

```
#### [PATCH v2] cpuidle-haltpoll: allow force loading on hosts without the REALTIME hint
##### From: "Maciej S. Szmigiero" <mail@maciej.szmigiero.name>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: "Maciej S. Szmigiero" <mail@maciej.szmigiero.name>
X-Patchwork-Id: 11419913
Return-Path: <SRS0=VNnu=4V=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 6E2F314B4
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed,  4 Mar 2020 11:33:03 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 4EF7621739
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed,  4 Mar 2020 11:33:03 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2387772AbgCDLdB (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 4 Mar 2020 06:33:01 -0500
Received: from vps-vb.mhejs.net ([37.28.154.113]:57462 "EHLO vps-vb.mhejs.net"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1729256AbgCDLdA (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 4 Mar 2020 06:33:00 -0500
Received: from MUA
        by vps-vb.mhejs.net with esmtps
 (TLSv1.2:ECDHE-RSA-AES256-GCM-SHA384:256)
        (Exim 4.92.3)
        (envelope-from <mail@maciej.szmigiero.name>)
        id 1j9SGj-0000pl-Un; Wed, 04 Mar 2020 12:32:53 +0100
From: "Maciej S. Szmigiero" <mail@maciej.szmigiero.name>
To: "Rafael J. Wysocki" <rjw@rjwysocki.net>,
        Daniel Lezcano <daniel.lezcano@linaro.org>
Cc: Joao Martins <joao.m.martins@oracle.com>,
        Boris Ostrovsky <boris.ostrovsky@oracle.com>,
        Marcelo Tosatti <mtosatti@redhat.com>, kvm@vger.kernel.org,
        linux-pm@vger.kernel.org, linux-kernel@vger.kernel.org
Subject: [PATCH v2] cpuidle-haltpoll: allow force loading on hosts without the
 REALTIME hint
Date: Wed,  4 Mar 2020 12:32:48 +0100
Message-Id: <20200304113248.1143057-1-mail@maciej.szmigiero.name>
X-Mailer: git-send-email 2.25.1
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: "Maciej S. Szmigiero" <maciej.szmigiero@oracle.com>

Before commit 1328edca4a14 ("cpuidle-haltpoll: Enable kvm guest polling
when dedicated physical CPUs are available") the cpuidle-haltpoll driver
could also be used in scenarios when the host does not advertise the
KVM_HINTS_REALTIME hint.

While the behavior introduced by the aforementioned commit makes sense as
the default there are cases where the old behavior is desired, for example,
when other kernel changes triggered by presence by this hint are unwanted,
for some workloads where the latency benefit from polling overweights the
loss from idle CPU capacity that otherwise would be available, or just when
running under older Qemu versions that lack this hint.

Let's provide a typical "force" module parameter that allows restoring the
old behavior.

Signed-off-by: Maciej S. Szmigiero <maciej.szmigiero@oracle.com>
---
 drivers/cpuidle/cpuidle-haltpoll.c | 12 ++++++++++--
 1 file changed, 10 insertions(+), 2 deletions(-)

Changes from v1:
Make the module parameter description more general, don't unnecessarily
break a line in haltpoll_init().

```
