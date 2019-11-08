#### [PATCH v3 1/5] kvm: nested: Introduce read_and_check_msr_entry()From: Aaron Lewis <aaronlewis@google.com>
##### From: Aaron Lewis <aaronlewis@google.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Aaron Lewis <aaronlewis@google.com>
X-Patchwork-Id: 11233859
Return-Path: <SRS0=VFBJ=Y7=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 88D7913BD
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  7 Nov 2019 22:49:51 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 6627521D82
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  7 Nov 2019 22:49:51 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=google.com header.i=@google.com
 header.b="uixDCo9s"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727994AbfKGWtu (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 7 Nov 2019 17:49:50 -0500
Received: from mail-pl1-f202.google.com ([209.85.214.202]:55161 "EHLO
        mail-pl1-f202.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1725992AbfKGWtu (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 7 Nov 2019 17:49:50 -0500
Received: by mail-pl1-f202.google.com with SMTP id a11so2730468plp.21
        for <kvm@vger.kernel.org>; Thu, 07 Nov 2019 14:49:49 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=date:in-reply-to:message-id:mime-version:references:subject:from:to
         :cc;
        bh=XTXOT3PTQaYYqLr+YkwfmLP4vZijQPTV+yL5uM5usc8=;
        b=uixDCo9sWcFrzbbPJ3qwhEF3MglWdyIZbnTF6Z0mmbqtPwdIO33yUMIZf/wB2crjw7
         cSIqj5EFReWyFUHM5VlOKhG/Kmh+bCJBFyFXQ1cASUxnQwtZgc1h8ZKqk/m4OtRN9E3J
         cUkV9FdJv6N1wtnRs1QuaLpofcjngxaqz+GKku21nLbd/7v8LH9P8FB87L4JfA37qP7e
         WvYQ6/UXXZoW4YvuBw44cC3/WEvPLQV7T1FEKmB58UgXG/4PKuQevZybKf7Rjb1N5xkx
         8aGD8D2lspQkbz8Ef65SypE4kQL8/AX8zqHFwS2KhG7ONeTTsjUa/NL4hV6ygFY8DJ5G
         T3hg==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:date:in-reply-to:message-id:mime-version
         :references:subject:from:to:cc;
        bh=XTXOT3PTQaYYqLr+YkwfmLP4vZijQPTV+yL5uM5usc8=;
        b=ES/FAJyM1jHc2H4xJwQlzZJi713hsZcFF7QGYpVPlKZ9jAQkhwJqQEXk68YRSBoHVc
         U7ErLXAtivEVAl+1vdmO7GvYtauvpU2QwyrNxmTwe48TybxhL/oe8l2EKsUyi2kBzGcJ
         B106F65TGFAMYMi6RU++1CssBV53calh4RU5hVeTTZZ8jPgiwTPHh4XXgHx3c97R1AGI
         UvZv03RttY2Rksnh+1tk2pYLaXv3dn4m8gVYTvfEQ8fi8VkkE5oZ1yjHIKD5skd73dHb
         irC9TW4Yx/XnnbTvO2/KDZtDh1Hsdkk34JuDOzbQBfotwmLebHFjJjWW7b/2VTFsA3lr
         OxiQ==
X-Gm-Message-State: APjAAAVe4NhbSx0cnqx7JOL4gcAOIqTuOW/InyNDtV9J9X1nI01zsC+v
        OTbVVmCSgEscghCFxDPclSFs0VG3jrUrgf6s/nq96EUGPdzLsHTP8z9Qu7PAHp0ik8HF79363wZ
        yeaGeXmHhwggdTNVReHAC3zFMzPYOaqeXOVBARqz9U6XsnzFdTsMTJYji3zNFCd/oDgLR
X-Google-Smtp-Source: 
 APXvYqzU6VmWxUonRHHAaH5w6SCOh10x1jbiy3PifEFWkuoUi3IQHCdDu5ovhE4kB3aVjpsgws3CmwQKlGqExQJG
X-Received: by 2002:a63:115b:: with SMTP id 27mr7153288pgr.298.1573166989202;
 Thu, 07 Nov 2019 14:49:49 -0800 (PST)
Date: Thu,  7 Nov 2019 14:49:37 -0800
In-Reply-To: <20191107224941.60336-1-aaronlewis@google.com>
Message-Id: <20191107224941.60336-2-aaronlewis@google.com>
Mime-Version: 1.0
References: <20191107224941.60336-1-aaronlewis@google.com>
X-Mailer: git-send-email 2.24.0.432.g9d3f5f5b63-goog
Subject: [PATCH v3 1/5] kvm: nested: Introduce read_and_check_msr_entry()
From: Aaron Lewis <aaronlewis@google.com>
To: kvm@vger.kernel.org
Cc: Jim Mattson <jmattson@google.com>,
        Paolo Bonzini <pbonzini@redhat.com>,
        Aaron Lewis <aaronlewis@google.com>,
        Liran Alon <liran.alon@oracle.com>
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Add the function read_and_check_msr_entry() which just pulls some code
out of nested_vmx_store_msr().  This will be useful as reusable code in
upcoming patches.

Reviewed-by: Liran Alon <liran.alon@oracle.com>
Reviewed-by: Jim Mattson <jmattson@google.com>
Signed-off-by: Aaron Lewis <aaronlewis@google.com>
---
 arch/x86/kvm/vmx/nested.c | 35 ++++++++++++++++++++++-------------
 1 file changed, 22 insertions(+), 13 deletions(-)

```
#### [PATCH 1/2] KVM: vgic-v4: Track the number of VLPIs per vcpu
##### From: Marc Zyngier <maz@kernel.org>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Marc Zyngier <maz@kernel.org>
X-Patchwork-Id: 11233269
Return-Path: <SRS0=VFBJ=Y7=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 531C21864
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  7 Nov 2019 16:04:27 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 331D821D7E
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  7 Nov 2019 16:04:27 +0000 (UTC)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple; d=kernel.org;
	s=default; t=1573142667;
	bh=miUY4csEa45vgXox8VqRN6ZLs42kZpo98+sGCOwhIDc=;
	h=From:To:Cc:Subject:Date:In-Reply-To:References:List-ID:From;
	b=Z8wBGgaZBuMk1OapkEkUgDZYpggPy85khVO2aMV3+ZM0fdv15MQR25uq196fSf4+V
	 +BmX0GqlC74ukwsSomAFQKT5b2rPODGEfqmtFONkOXzEsUXmapV9cC+YneeOEAkF0K
	 a5KlI0aLG7vYz1bNmEQX7DbX9eDzm2qAh9hetGVc=
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2387487AbfKGQEZ (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 7 Nov 2019 11:04:25 -0500
Received: from inca-roads.misterjones.org ([213.251.177.50]:48223 "EHLO
        inca-roads.misterjones.org" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1727401AbfKGQEY (ORCPT
        <rfc822;kvm@vger.kernel.org>); Thu, 7 Nov 2019 11:04:24 -0500
Received: from 78.163-31-62.static.virginmediabusiness.co.uk ([62.31.163.78]
 helo=why.lan)
        by cheepnis.misterjones.org with esmtpsa
 (TLSv1.2:DHE-RSA-AES128-GCM-SHA256:128)
        (Exim 4.80)
        (envelope-from <maz@kernel.org>)
        id 1iSkGk-0008Bm-JL; Thu, 07 Nov 2019 17:04:22 +0100
From: Marc Zyngier <maz@kernel.org>
To: kvm@vger.kernel.org, kvmarm@lists.cs.columbia.edu,
        linux-arm-kernel@lists.infradead.org
Cc: James Morse <james.morse@arm.com>,
        Julien Thierry <julien.thierry.kdev@gmail.com>,
        Suzuki K Poulose <suzuki.poulose@arm.com>
Subject: [PATCH 1/2] KVM: vgic-v4: Track the number of VLPIs per vcpu
Date: Thu,  7 Nov 2019 16:04:11 +0000
Message-Id: <20191107160412.30301-2-maz@kernel.org>
X-Mailer: git-send-email 2.20.1
In-Reply-To: <20191107160412.30301-1-maz@kernel.org>
References: <20191107160412.30301-1-maz@kernel.org>
MIME-Version: 1.0
X-SA-Exim-Connect-IP: 62.31.163.78
X-SA-Exim-Rcpt-To: kvm@vger.kernel.org, kvmarm@lists.cs.columbia.edu,
 linux-arm-kernel@lists.infradead.org, james.morse@arm.com,
 julien.thierry.kdev@gmail.com, suzuki.poulose@arm.com
X-SA-Exim-Mail-From: maz@kernel.org
X-SA-Exim-Scanned: No (on cheepnis.misterjones.org);
 SAEximRunCond expanded to false
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

In order to find out whether a vcpu is likely to be the target of
VLPIs (and to further optimize the way we deal with those), let's
track the number of VLPIs a vcpu can receive.

This gets implemented with an atomic variable that gets incremented
or decremented on map, unmap and move of a VLPI.

Signed-off-by: Marc Zyngier <maz@kernel.org>
---
 include/linux/irqchip/arm-gic-v4.h | 2 ++
 virt/kvm/arm/vgic/vgic-init.c      | 1 +
 virt/kvm/arm/vgic/vgic-its.c       | 3 +++
 virt/kvm/arm/vgic/vgic-v4.c        | 2 ++
 4 files changed, 8 insertions(+)

```
#### [PATCH] KVM: coalesced_mmio: cleanup kvm_coalesced_mmio_init()
##### From: Vitaly Kuznetsov <vkuznets@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Vitaly Kuznetsov <vkuznets@redhat.com>
X-Patchwork-Id: 11232453
Return-Path: <SRS0=VFBJ=Y7=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 3617513BD
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  7 Nov 2019 10:10:43 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 11F502077C
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  7 Nov 2019 10:10:43 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1733222AbfKGKKj (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 7 Nov 2019 05:10:39 -0500
Received: from mx1.redhat.com ([209.132.183.28]:46256 "EHLO mx1.redhat.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1727528AbfKGKKi (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 7 Nov 2019 05:10:38 -0500
Received: from mail-wm1-f71.google.com (mail-wm1-f71.google.com
 [209.85.128.71])
        (using TLSv1.2 with cipher ECDHE-RSA-AES128-GCM-SHA256 (128/128 bits))
        (No client certificate requested)
        by mx1.redhat.com (Postfix) with ESMTPS id 66ED67C0A7
        for <kvm@vger.kernel.org>; Thu,  7 Nov 2019 10:10:38 +0000 (UTC)
Received: by mail-wm1-f71.google.com with SMTP id b10so497274wmh.6
        for <kvm@vger.kernel.org>; Thu, 07 Nov 2019 02:10:38 -0800 (PST)
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:mime-version
         :content-transfer-encoding;
        bh=OCIqyJJdOW00bPyctKLkzxNP0EVAczBbs1eO7W8t2tM=;
        b=fR1iY418qnY1SqGTZxoHbg0xOsXSpsGp5mtMZ1+R1MrbR5s6tWbya2DzF66Yx2Zr/v
         Fh+SkF2dE1SFfwe3QPXWyHPQ4myBp31GhGionLGVsLWGJR+KqTocuqT78LIEoJCaKhvY
         l6xguKfjBbmbo2jnBBNzsJG+RO3s83lhKOEsC2spTp+0ZDN2XfsWrl8/s8/0WFd47+Sw
         oawjFyr2v6Bkl6kvtjdXqYmfi3YPsygXjix2WlEGrUDJ2CEfNo+xcsqNj9bkk5jwPAiS
         DwkrY6eptIz+xc1MXzDTq+moZLw0q7PvHxjFuR85BiIqL42fe12a09pSkyL5/kB84Pvk
         9Ytg==
X-Gm-Message-State: APjAAAUblPHbUQ1kuAcyFaeJ3rG3EGfXXvF85a9+JVYyaBRdZZTFKtJx
        bhzd7Ph+JXLvoGsRQ6ASa3sYvfnNLNT2JGP5Yq6cQTtt53zDsLboYiO6Zjqt97rk6IYBLEeAHd7
        Xc4hzCqyq2KI0
X-Received: by 2002:a5d:6789:: with SMTP id v9mr2001967wru.344.1573121436852;
        Thu, 07 Nov 2019 02:10:36 -0800 (PST)
X-Google-Smtp-Source: 
 APXvYqwVrO1kZIfHP7MQ5tgPYumXgK/TKMlvQ8AyGBFuR4+U8dCNxxCN3OTkTO6xgcYkWl6NDneBuw==
X-Received: by 2002:a5d:6789:: with SMTP id v9mr2001944wru.344.1573121436558;
        Thu, 07 Nov 2019 02:10:36 -0800 (PST)
Received: from vitty.brq.redhat.com (nat-pool-brq-t.redhat.com.
 [213.175.37.10])
        by smtp.gmail.com with ESMTPSA id
 y17sm1836077wrs.58.2019.11.07.02.10.35
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Thu, 07 Nov 2019 02:10:35 -0800 (PST)
From: Vitaly Kuznetsov <vkuznets@redhat.com>
To: kvm@vger.kernel.org
Cc: x86@kernel.org, Paolo Bonzini <pbonzini@redhat.com>,
        linux-kernel@vger.kernel.org
Subject: [PATCH] KVM: coalesced_mmio: cleanup kvm_coalesced_mmio_init()
Date: Thu,  7 Nov 2019 11:10:34 +0100
Message-Id: <20191107101034.29675-1-vkuznets@redhat.com>
X-Mailer: git-send-email 2.20.1
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Neither 'ret' variable nor 'out_err' label is really needed.

Signed-off-by: Vitaly Kuznetsov <vkuznets@redhat.com>
---
 virt/kvm/coalesced_mmio.c | 8 ++------
 1 file changed, 2 insertions(+), 6 deletions(-)

```
#### [Patch v2 1/2] KVM: remember position in kvm->vcpus array
##### From: Nitesh Narayan Lal <nitesh@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 8bit
X-Patchwork-Submitter: Nitesh Narayan Lal <nitesh@redhat.com>
X-Patchwork-Id: 11232751
Return-Path: <SRS0=VFBJ=Y7=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 9A49A1599
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  7 Nov 2019 12:54:11 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 6E3B12178F
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  7 Nov 2019 12:54:11 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="jCe1SNin"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2388701AbfKGMyK (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 7 Nov 2019 07:54:10 -0500
Received: from us-smtp-delivery-1.mimecast.com ([207.211.31.120]:57183 "EHLO
        us-smtp-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org
        with ESMTP id S1727619AbfKGMyA (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 7 Nov 2019 07:54:00 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1573131239;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:mime-version:mime-version:content-type:content-type:
         content-transfer-encoding:content-transfer-encoding:
         in-reply-to:in-reply-to:references:references;
        bh=3y0I7IlS4H5f58+QId2pdet5TjErOAhCzPeVmmoAFuQ=;
        b=jCe1SNinnIz56+ejZ0Pq0o7CzojN4Do7BmpsOHhdavUzbHq7Wiilhc1auvnasNNu4c8hh7
        LmS0UtL/qGdPCCg3/9jQY7lBMYZrrWRi9ZX3olG4+8kPDjseEt2Bpp18kS1VPqYErarRcx
        BOlu4zALQDnfhb1knYXX4yTY2IppYdI=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-429-aTBMbFduMU-rfHfqz0ay2A-1; Thu, 07 Nov 2019 07:53:55 -0500
Received: from smtp.corp.redhat.com (int-mx07.intmail.prod.int.phx2.redhat.com
 [10.5.11.22])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id A48F48017DD;
        Thu,  7 Nov 2019 12:53:54 +0000 (UTC)
Received: from virtlab512.virt.lab.eng.bos.redhat.com
 (virtlab512.virt.lab.eng.bos.redhat.com [10.19.152.206])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 9B4041001E75;
        Thu,  7 Nov 2019 12:53:53 +0000 (UTC)
From: Nitesh Narayan Lal <nitesh@redhat.com>
To: kvm@vger.kernel.org, linux-kernel@vger.kernel.org,
        pbonzini@redhat.com, mtosatti@redhat.com, rkrcmar@redhat.com,
        vkuznets@redhat.com, sean.j.christopherson@intel.com,
        wanpengli@tencent.com, jmattson@google.com, joro@8bytes.org
Subject: [Patch v2 1/2] KVM: remember position in kvm->vcpus array
Date: Thu,  7 Nov 2019 07:53:42 -0500
Message-Id: <1573131223-5685-2-git-send-email-nitesh@redhat.com>
In-Reply-To: <1573131223-5685-1-git-send-email-nitesh@redhat.com>
References: <1573131223-5685-1-git-send-email-nitesh@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.84 on 10.5.11.22
X-MC-Unique: aTBMbFduMU-rfHfqz0ay2A-1
X-Mimecast-Spam-Score: 0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Radim Krčmář <rkrcmar@redhat.com>

Fetching an index for any vcpu in kvm->vcpus array by traversing
the entire array everytime is costly.
This patch remembers the position of each vcpu in kvm->vcpus array
by storing it in vcpus_idx under kvm_vcpu structure.

Signed-off-by: Radim Krčmář <rkrcmar@redhat.com>
Signed-off-by: Nitesh Narayan Lal <nitesh@redhat.com>
---
 include/linux/kvm_host.h | 11 +++--------
 virt/kvm/kvm_main.c      |  5 +++--
 2 files changed, 6 insertions(+), 10 deletions(-)

```
#### [PATCH] kvm/x86 : Replace BUG_ON(1) with BUG()X-Priority: 3
##### From: "Peng Hao" <richard.peng@oppo.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 8bit
X-Patchwork-Submitter: Peng Hao <richard.peng@oppo.com>
X-Patchwork-Id: 11231665
Return-Path: <SRS0=VFBJ=Y7=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 1C58B1709
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  7 Nov 2019 02:36:17 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 01E452075C
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  7 Nov 2019 02:36:17 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1732790AbfKGCgO (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 6 Nov 2019 21:36:14 -0500
Received: from m17618.mail.qiye.163.com ([59.111.176.18]:51571 "EHLO
        m17618.mail.qiye.163.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1727778AbfKGCgO (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 6 Nov 2019 21:36:14 -0500
X-Greylist: delayed 549 seconds by postgrey-1.27 at vger.kernel.org;
 Wed, 06 Nov 2019 21:36:12 EST
Received: from P80254710 (unknown [121.12.147.249])
        by m17618.mail.qiye.163.com (Hmail) with ESMTPA id 90E004E17EE;
        Thu,  7 Nov 2019 10:27:01 +0800 (CST)
Date: Thu, 7 Nov 2019 10:27:06 +0800
From: "Peng Hao" <richard.peng@oppo.com>
To: pbonzini <pbonzini@redhat.com>, rkrcmar <rkrcmar@redhat.com>
Cc: kvm <kvm@vger.kernel.org>,
        linux-kernel <linux-kernel@vger.kernel.org>
Subject: [PATCH] kvm/x86 : Replace BUG_ON(1) with BUG()
X-Priority: 3
X-GUID: 608D3069-12C2-46ED-919C-21192C18CDB7
X-Has-Attach: no
X-Mailer: Foxmail 7.2.10.151[en]
Mime-Version: 1.0
Message-ID: <201911071027048908705@oppo.com>
X-HM-Spam-Status: e1kfGhgUHx5ZQUtXWQgYFAkeWUFZVk9VTE5OS0tKTk9PQk5JSEJZV1koWU
        FJSUtLSjdXWS1ZQUlXWQkOFx4IWUFZNTQpNjo3JCkuNz5ZBg++
X-HM-Sender-Digest: e1kMHhlZQR0aFwgeV1kSHx4VD1lBWUc6Mwg6ITo6CDg6DBgMSlYYLy9M
        SjZPCTJVSlVKTkxIS0JITUlJSU5KVTMWGhIXVQkSGBMaCR9VCx4VHDsUCwsUVRgUFkVZV1kSC1lB
        WUpJSlVKSVVKT0xVSU9CWVdZCAFZQUpOQ0M3Bg++
X-HM-Tid: 0a6e43afc0f59376kuws90e004e17ee
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Signed-off-by: Peng Hao <richard.peng@oppo.com>
---
 arch/x86/kvm/vmx/nested.c | 3 +--
 1 file changed, 1 insertion(+), 2 deletions(-)

-- 
2.7.4

```
#### [PATCH V11 1/6] mdev: class id support
##### From: Jason Wang <jasowang@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Jason Wang <jasowang@redhat.com>
X-Patchwork-Id: 11233111
Return-Path: <SRS0=VFBJ=Y7=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 3E39E1599
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  7 Nov 2019 15:12:32 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 0A18C21D82
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  7 Nov 2019 15:12:32 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="ARO+4fUI"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2388997AbfKGPMZ (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 7 Nov 2019 10:12:25 -0500
Received: from us-smtp-delivery-1.mimecast.com ([205.139.110.120]:42145 "EHLO
        us-smtp-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org
        with ESMTP id S2388659AbfKGPMZ (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 7 Nov 2019 10:12:25 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1573139544;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:content-type:content-type:
         content-transfer-encoding:content-transfer-encoding:
         in-reply-to:in-reply-to:references:references;
        bh=ZjglcjJdfJ+rYNda606bWPhtmSxvctdSzvRhdUvjVro=;
        b=ARO+4fUIW9+nUjCyHI8M2W7lc8YKfBuEeeGcEz6sxY0ScoaIDukkrnF+ym096MCnLrvdot
        GxSVEFzv2VHWNeFvSY8eNlz/HUyckLw9/4YsqLnauLGsIAKsxYoK9ZaEp8NxvLDTQZe8OC
        ESS/oZhZ80K7STgea3ycokx34e9uCLs=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-216-l6M2zws_OXibIpCw8_kerw-1; Thu, 07 Nov 2019 10:12:20 -0500
Received: from smtp.corp.redhat.com (int-mx01.intmail.prod.int.phx2.redhat.com
 [10.5.11.11])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id CEF4C107ACC3;
        Thu,  7 Nov 2019 15:12:16 +0000 (UTC)
Received: from jason-ThinkPad-X1-Carbon-6th.redhat.com
 (ovpn-12-21.pek2.redhat.com [10.72.12.21])
        by smtp.corp.redhat.com (Postfix) with ESMTP id CBA64600D1;
        Thu,  7 Nov 2019 15:11:37 +0000 (UTC)
From: Jason Wang <jasowang@redhat.com>
To: kvm@vger.kernel.org, linux-s390@vger.kernel.org,
        linux-kernel@vger.kernel.org, dri-devel@lists.freedesktop.org,
        intel-gfx@lists.freedesktop.org,
        intel-gvt-dev@lists.freedesktop.org, kwankhede@nvidia.com,
        alex.williamson@redhat.com, mst@redhat.com, tiwei.bie@intel.com
Cc: virtualization@lists.linux-foundation.org, netdev@vger.kernel.org,
        cohuck@redhat.com, maxime.coquelin@redhat.com,
        cunming.liang@intel.com, zhihong.wang@intel.com,
        rob.miller@broadcom.com, xiao.w.wang@intel.com,
        haotian.wang@sifive.com, zhenyuw@linux.intel.com,
        zhi.a.wang@intel.com, jani.nikula@linux.intel.com,
        joonas.lahtinen@linux.intel.com, rodrigo.vivi@intel.com,
        airlied@linux.ie, daniel@ffwll.ch, farman@linux.ibm.com,
        pasic@linux.ibm.com, sebott@linux.ibm.com, oberpar@linux.ibm.com,
        heiko.carstens@de.ibm.com, gor@linux.ibm.com,
        borntraeger@de.ibm.com, akrowiak@linux.ibm.com,
        freude@linux.ibm.com, lingshan.zhu@intel.com, eperezma@redhat.com,
        lulu@redhat.com, parav@mellanox.com,
        christophe.de.dinechin@gmail.com, kevin.tian@intel.com,
        stefanha@redhat.com, rdunlap@infradead.org,
        Jason Wang <jasowang@redhat.com>
Subject: [PATCH V11 1/6] mdev: class id support
Date: Thu,  7 Nov 2019 23:11:04 +0800
Message-Id: <20191107151109.23261-2-jasowang@redhat.com>
In-Reply-To: <20191107151109.23261-1-jasowang@redhat.com>
References: <20191107151109.23261-1-jasowang@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.11
X-MC-Unique: l6M2zws_OXibIpCw8_kerw-1
X-Mimecast-Spam-Score: 0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Mdev bus only supports vfio driver right now, so it doesn't implement
match method. But in the future, we may add drivers other than vfio,
the first driver could be virtio-mdev. This means we need to add
device class id support in bus match method to pair the mdev device
and mdev driver correctly.

So this patch adds id_table to mdev_driver and class_id for mdev
device with the match method for mdev bus.

Reviewed-by: Parav Pandit <parav@mellanox.com>
Reviewed-by: Cornelia Huck <cohuck@redhat.com>
Signed-off-by: Jason Wang <jasowang@redhat.com>
Reviewed-by: Kirti Wankhede <kwankhede@nvidia.com>
---
 .../driver-api/vfio-mediated-device.rst       |  5 ++++
 drivers/gpu/drm/i915/gvt/kvmgt.c              |  1 +
 drivers/s390/cio/vfio_ccw_ops.c               |  1 +
 drivers/s390/crypto/vfio_ap_ops.c             |  1 +
 drivers/vfio/mdev/mdev_core.c                 | 17 +++++++++++++
 drivers/vfio/mdev/mdev_driver.c               | 25 +++++++++++++++++++
 drivers/vfio/mdev/mdev_private.h              |  1 +
 drivers/vfio/mdev/vfio_mdev.c                 |  6 +++++
 include/linux/mdev.h                          |  8 ++++++
 include/linux/mod_devicetable.h               |  8 ++++++
 samples/vfio-mdev/mbochs.c                    |  1 +
 samples/vfio-mdev/mdpy.c                      |  1 +
 samples/vfio-mdev/mtty.c                      |  1 +
 13 files changed, 76 insertions(+)

```
#### [PATCH net-next 01/19] net/mlx5: E-switch, Move devlink port close to eswitch port
##### From: Parav Pandit <parav@mellanox.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Parav Pandit <parav@mellanox.com>
X-Patchwork-Id: 11233283
Return-Path: <SRS0=VFBJ=Y7=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 1AE1D1390
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  7 Nov 2019 16:08:52 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id EE66921D7F
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  7 Nov 2019 16:08:51 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2389197AbfKGQIu (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 7 Nov 2019 11:08:50 -0500
Received: from mail-il-dmz.mellanox.com ([193.47.165.129]:53422 "EHLO
        mellanox.co.il" rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org
        with ESMTP id S1729800AbfKGQIu (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 7 Nov 2019 11:08:50 -0500
Received: from Internal Mail-Server by MTLPINE1 (envelope-from
 parav@mellanox.com)
        with ESMTPS (AES256-SHA encrypted); 7 Nov 2019 18:08:42 +0200
Received: from sw-mtx-036.mtx.labs.mlnx (sw-mtx-036.mtx.labs.mlnx
 [10.9.150.149])
        by labmailer.mlnx (8.13.8/8.13.8) with ESMTP id xA7G8d4B007213;
        Thu, 7 Nov 2019 18:08:39 +0200
From: Parav Pandit <parav@mellanox.com>
To: alex.williamson@redhat.com, davem@davemloft.net,
        kvm@vger.kernel.org, netdev@vger.kernel.org
Cc: saeedm@mellanox.com, kwankhede@nvidia.com, leon@kernel.org,
        cohuck@redhat.com, jiri@mellanox.com, linux-rdma@vger.kernel.org,
        Parav Pandit <parav@mellanox.com>
Subject: [PATCH net-next 01/19] net/mlx5: E-switch,
 Move devlink port close to eswitch port
Date: Thu,  7 Nov 2019 10:08:16 -0600
Message-Id: <20191107160834.21087-1-parav@mellanox.com>
X-Mailer: git-send-email 2.19.2
In-Reply-To: <20191107160448.20962-1-parav@mellanox.com>
References: <20191107160448.20962-1-parav@mellanox.com>
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Currently devlink ports are tied to netdev representor.

mlx5_vport structure is better container of e-switch vport
compare to mlx5e_rep_priv.
This enables to extend mlx5_vport easily for mdev flavour.

Hence, move devlink_port from netdev representor to mlx5_vport.

Reviewed-by: Saeed Mahameed <saeedm@mellanox.com>
Signed-off-by: Parav Pandit <parav@mellanox.com>
---
 .../net/ethernet/mellanox/mlx5/core/devlink.c | 63 +++++++++++++
 .../net/ethernet/mellanox/mlx5/core/devlink.h |  8 ++
 .../net/ethernet/mellanox/mlx5/core/en_rep.c  | 94 +++----------------
 .../net/ethernet/mellanox/mlx5/core/en_rep.h  |  2 +-
 .../net/ethernet/mellanox/mlx5/core/eswitch.h |  1 +
 5 files changed, 88 insertions(+), 80 deletions(-)

```
#### [kvm-unit-tests PATCH 1/2] Makefile: use "-Werror" in cc-optionFrom: Bill Wendling <morbo@google.com>
##### From: Bill Wendling <morbo@google.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Bill Wendling <morbo@google.com>
X-Patchwork-Id: 11231475
Return-Path: <SRS0=VFBJ=Y7=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id CF82E1599
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  7 Nov 2019 01:09:02 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id A9E0F21848
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  7 Nov 2019 01:09:02 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=google.com header.i=@google.com
 header.b="I+1tX8Kl"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728366AbfKGBJC (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 6 Nov 2019 20:09:02 -0500
Received: from mail-pg1-f202.google.com ([209.85.215.202]:32996 "EHLO
        mail-pg1-f202.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1728265AbfKGBJB (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 6 Nov 2019 20:09:01 -0500
Received: by mail-pg1-f202.google.com with SMTP id y22so445107pgc.0
        for <kvm@vger.kernel.org>; Wed, 06 Nov 2019 17:08:59 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=date:in-reply-to:message-id:mime-version:references:subject:from:to
         :cc;
        bh=iswOSk/cZ98lnJ7BbrIe/h5JrJo81nLP88Lj3jwN4P0=;
        b=I+1tX8Kl7CXMH+Hz830Y99VMAsMZ/b0El9mFJo3kNwnTRCRKWTpejQKLJz20nv/OFe
         aY/7fDUshnB/CXOrTmjqlJJqueTT6+ZQmqi5CsZu4JlI2rFwqnDSRTiQGTRX6j3WQIQK
         d+BR6uV3C9YPNk1NrZ2wKNkvfQDdwKnBWaCtusdaUgBFiFOpdjgQCT1TGxEm9M+pgaIS
         GM9Z3lWasxEWBCg/YvWkip79fADKf4C+LlXqw+6ZqD/NXfu0vCmMKJkjL9zfaKc1Zjl/
         uTdG7WNYvP3umgQGATBdMPUgQv3p7SYEZHJ6O3HCXYc50K97nd1O1PDB5VT9O38GquQK
         WMSQ==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:date:in-reply-to:message-id:mime-version
         :references:subject:from:to:cc;
        bh=iswOSk/cZ98lnJ7BbrIe/h5JrJo81nLP88Lj3jwN4P0=;
        b=m5gmn709sN45028aH/oRVZnxUYMDm1m4E8Wx78YomH//KbfMWsWPfinLKRmDfxIld+
         9UxK2Noaqzflr9dY3Ph4XEQDssrgx7N3IiEIxbfxjHRNKY4NE5/zo4NxpXHyX2ee6QhQ
         aQm0Zq3vuGESzXaA986XqDBe44xXVCaLp06zBKdkPjtHv9uaqMVJ8slpCKaf9Eec8Rl1
         UY3laZpuVBn1aD03VzFn14SMxWEbfdNyNkACxcnX1Fu+AGSdalUFSzdXBlFpR0+2wuAO
         fdj1wDJOyWZ4ev6eFO6uLPPQAQ7doQPqKqmOVqG9WSO8uJK+/E1e1fn1ETIrf2aj/ohq
         Zx5Q==
X-Gm-Message-State: APjAAAVuLqIySOU6l34gdddiDI+1xsgwDpA7FkS0FQPA59cXnAZiVJhM
        cJDDi3T4EuB+j/o1MifLpakwPHUZNd93Z9ZvDBssEPLluAZIsirn4YXJG8DVxEBf8V+UP2bsMJs
        lG742J0xLG7Ft5YYxd41JrS1PqIWDkB3A79ssl46tYIx2AAhlkmCwdw==
X-Google-Smtp-Source: 
 APXvYqy3gJ0/ynp+CqtY1t9JZ1HQVt0j6B0OPz6rLFZltcjSIj+bbBu1JCmx2qwRT0x92C4m93R1Yf342w==
X-Received: by 2002:a63:1323:: with SMTP id i35mr1039144pgl.450.1573088939030;
 Wed, 06 Nov 2019 17:08:59 -0800 (PST)
Date: Wed,  6 Nov 2019 17:08:43 -0800
In-Reply-To: <20191107010844.101059-1-morbo@google.com>
Message-Id: <20191107010844.101059-2-morbo@google.com>
Mime-Version: 1.0
References: <20191107010844.101059-1-morbo@google.com>
X-Mailer: git-send-email 2.24.0.rc1.363.gb1bccd3e3d-goog
Subject: [kvm-unit-tests PATCH 1/2] Makefile: use "-Werror" in cc-option
From: Bill Wendling <morbo@google.com>
To: kvm@vger.kernel.org, pbonzini@redhat.com
Cc: jmattson@google.com, Bill Wendling <morbo@google.com>
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The "cc-option" macro should use "-Werror" to determine if a flag is
supported. Otherwise the test may not return a nonzero result. Also
conditionalize some of the warning flags which aren't supported by
clang.

Signed-off-by: Bill Wendling <morbo@google.com>
---
 Makefile | 20 ++++++++++++++------
 1 file changed, 14 insertions(+), 6 deletions(-)

```
#### [PATCH v6] vhost: introduce mdev based hardware backend
##### From: Tiwei Bie <tiwei.bie@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Tiwei Bie <tiwei.bie@intel.com>
X-Patchwork-Id: 11231939
Return-Path: <SRS0=VFBJ=Y7=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id F2DD616B1
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  7 Nov 2019 07:34:58 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id BBB9D21D79
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  7 Nov 2019 07:34:58 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726995AbfKGHex (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 7 Nov 2019 02:34:53 -0500
Received: from mga14.intel.com ([192.55.52.115]:56166 "EHLO mga14.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726734AbfKGHew (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 7 Nov 2019 02:34:52 -0500
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from orsmga002.jf.intel.com ([10.7.209.21])
  by fmsmga103.fm.intel.com with ESMTP/TLS/DHE-RSA-AES256-GCM-SHA384;
 06 Nov 2019 23:34:51 -0800
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.68,277,1569308400";
   d="scan'208";a="214515481"
Received: from dpdk-virtio-tbie-2.sh.intel.com ([10.67.104.74])
  by orsmga002.jf.intel.com with ESMTP; 06 Nov 2019 23:34:48 -0800
From: Tiwei Bie <tiwei.bie@intel.com>
To: mst@redhat.com, jasowang@redhat.com, alex.williamson@redhat.com,
        maxime.coquelin@redhat.com
Cc: linux-kernel@vger.kernel.org, kvm@vger.kernel.org,
        virtualization@lists.linux-foundation.org, netdev@vger.kernel.org,
        dan.daly@intel.com, cunming.liang@intel.com,
        zhihong.wang@intel.com, lingshan.zhu@intel.com, tiwei.bie@intel.com
Subject: [PATCH v6] vhost: introduce mdev based hardware backend
Date: Thu,  7 Nov 2019 15:35:30 +0800
Message-Id: <20191107073530.15291-1-tiwei.bie@intel.com>
X-Mailer: git-send-email 2.23.0
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This patch introduces a mdev based hardware vhost backend.
This backend is built on top of the same abstraction used
in virtio-mdev and provides a generic vhost interface for
userspace to accelerate the virtio devices in guest.

This backend is implemented as a mdev device driver on top
of the same mdev device ops used in virtio-mdev but using
a different mdev class id, and it will register the device
as a VFIO device for userspace to use. Userspace can setup
the IOMMU with the existing VFIO container/group APIs and
then get the device fd with the device name. After getting
the device fd, userspace can use vhost ioctls on top of it
to setup the backend.

Signed-off-by: Tiwei Bie <tiwei.bie@intel.com>
Acked-by: Michael S. Tsirkin <mst@redhat.com>
Acked-by: Jason Wang <jasowang@redhat.com>
---
This patch depends on below series:
https://lkml.org/lkml/2019/11/6/538

v5 -> v6:
- Filter out VHOST_SET_LOG_BASE/VHOST_SET_LOG_FD (Jason);
- Simplify len/off check (Jason);
- Address checkpatch warnings, some of them are ignored
  to keep the coding style consistent with existing ones;

v4 -> v5:
- Rebase on top of virtio-mdev series v8;
- Use the virtio_ops of mdev_device in vhost-mdev (Jason);
- Some minor improvements on commit log;

v3 -> v4:
- Rebase on top of virtio-mdev series v6;
- Some minor tweaks and improvements;

v2 -> v3:
- Fix the return value (Jason);
- Don't cache unnecessary information in vhost-mdev (Jason);
- Get rid of the memset in open (Jason);
- Add comments for VHOST_SET_MEM_TABLE, ... (Jason);
- Filter out unsupported features in vhost-mdev (Jason);
- Add _GET_DEVICE_ID ioctl (Jason);
- Add _GET_CONFIG/_SET_CONFIG ioctls (Jason);
- Drop _GET_QUEUE_NUM ioctl (Jason);
- Fix the copy-paste errors in _IOW/_IOR usage;
- Some minor fixes and improvements;

v1 -> v2:
- Replace _SET_STATE with _SET_STATUS (MST);
- Check status bits at each step (MST);
- Report the max ring size and max number of queues (MST);
- Add missing MODULE_DEVICE_TABLE (Jason);
- Only support the network backend w/o multiqueue for now;
- Some minor fixes and improvements;
- Rebase on top of virtio-mdev series v4;

RFC v4 -> v1:
- Implement vhost-mdev as a mdev device driver directly and
  connect it to VFIO container/group. (Jason);
- Pass ring addresses as GPAs/IOVAs in vhost-mdev to avoid
  meaningless HVA->GPA translations (Jason);

RFC v3 -> RFC v4:
- Build vhost-mdev on top of the same abstraction used by
  virtio-mdev (Jason);
- Introduce vhost fd and pass VFIO fd via SET_BACKEND ioctl (MST);

RFC v2 -> RFC v3:
- Reuse vhost's ioctls instead of inventing a VFIO regions/irqs
  based vhost protocol on top of vfio-mdev (Jason);

RFC v1 -> RFC v2:
- Introduce a new VFIO device type to build a vhost protocol
  on top of vfio-mdev;

 drivers/vfio/mdev/mdev_core.c    |  21 ++
 drivers/vhost/Kconfig            |  12 +
 drivers/vhost/Makefile           |   3 +
 drivers/vhost/mdev.c             | 556 +++++++++++++++++++++++++++++++
 include/linux/mdev.h             |   5 +
 include/uapi/linux/vhost.h       |  21 ++
 include/uapi/linux/vhost_types.h |   8 +
 7 files changed, 626 insertions(+)
 create mode 100644 drivers/vhost/mdev.c

```
