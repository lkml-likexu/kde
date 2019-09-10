#### [PATCH 01/17] KVM: arm/arm64: vgic: Add LPI translation cache definition
##### From: Marc Zyngier <maz@kernel.org>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Marc Zyngier <maz@kernel.org>
X-Patchwork-Id: 11137957
Return-Path: <SRS0=hA4U=XE=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 835C014E5
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon,  9 Sep 2019 13:48:55 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 626C320828
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon,  9 Sep 2019 13:48:55 +0000 (UTC)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple; d=kernel.org;
	s=default; t=1568036935;
	bh=4yZn87fpEEnXq5D1OD3Q0UBfkHK4SN/5Z2OkawoffDA=;
	h=From:To:Cc:Subject:Date:In-Reply-To:References:List-ID:From;
	b=FL4TPOFvgVCaNtL7K/aRJ2EkUPnblyqxxZlw4ijHeJ3WAQWmihcqiS+VB6h7RE1/a
	 1s3LvDHNSM8B6m3PSs7HeJMLhQAyrwncs3MIzlrCUHNCnFxrlc3+lYzvvF7gWhaEnY
	 AZG5XA7EfO7rMpA8uZMq7dJ8eOGvjpHqbf+aMOzc=
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1731219AbfIINsy (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 9 Sep 2019 09:48:54 -0400
Received: from foss.arm.com ([217.140.110.172]:50504 "EHLO foss.arm.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1727854AbfIINsx (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 9 Sep 2019 09:48:53 -0400
Received: from usa-sjc-imap-foss1.foss.arm.com (unknown [10.121.207.14])
        by usa-sjc-mx-foss1.foss.arm.com (Postfix) with ESMTP id 21E221570;
        Mon,  9 Sep 2019 06:48:53 -0700 (PDT)
Received: from localhost.localdomain (unknown [172.31.20.19])
        by usa-sjc-imap-foss1.foss.arm.com (Postfix) with ESMTPSA id
 BFB6F3F59C;
        Mon,  9 Sep 2019 06:48:50 -0700 (PDT)
From: Marc Zyngier <maz@kernel.org>
To: Paolo Bonzini <pbonzini@redhat.com>,
 =?utf-8?b?UmFkaW0gS3LEjW3DocWZ?= <rkrcmar@redhat.com>
Cc: Alexandru Elisei <alexandru.elisei@arm.com>,
        Andre Przywara <andre.przywara@arm.com>,
        Eric Auger <eric.auger@redhat.com>,
        James Morse <james.morse@arm.com>,
        Mark Rutland <mark.rutland@arm.com>,
        Zenghui Yu <yuzenghui@huawei.com>, kvm@vger.kernel.org,
        kvmarm@lists.cs.columbia.edu, linux-arm-kernel@lists.infradead.org
Subject: [PATCH 01/17] KVM: arm/arm64: vgic: Add LPI translation cache
 definition
Date: Mon,  9 Sep 2019 14:47:51 +0100
Message-Id: <20190909134807.27978-2-maz@kernel.org>
X-Mailer: git-send-email 2.20.1
In-Reply-To: <20190909134807.27978-1-maz@kernel.org>
References: <20190909134807.27978-1-maz@kernel.org>
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Add the basic data structure that expresses an MSI to LPI
translation as well as the allocation/release hooks.

The size of the cache is arbitrarily defined as 16*nr_vcpus.

Tested-by: Andre Przywara <andre.przywara@arm.com>
Reviewed-by: Eric Auger <eric.auger@redhat.com>
Signed-off-by: Marc Zyngier <maz@kernel.org>
---
 include/kvm/arm_vgic.h        |  3 +++
 virt/kvm/arm/vgic/vgic-init.c |  5 ++++
 virt/kvm/arm/vgic/vgic-its.c  | 49 +++++++++++++++++++++++++++++++++++
 virt/kvm/arm/vgic/vgic.h      |  2 ++
 4 files changed, 59 insertions(+)

```
#### [RFC][PATCH v2 1/1] KVM: nVMX: Don't leak L1 MMIO regions to L2From: Jim Mattson <jmattson@google.com>
##### From: Jim Mattson <jmattson@google.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Jim Mattson <jmattson@google.com>
X-Patchwork-Id: 11138579
Return-Path: <SRS0=hA4U=XE=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 085D1924
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon,  9 Sep 2019 22:28:28 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id D260B21A4A
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon,  9 Sep 2019 22:28:27 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=google.com header.i=@google.com
 header.b="UJs2of+L"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728706AbfIIW21 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 9 Sep 2019 18:28:27 -0400
Received: from mail-pf1-f201.google.com ([209.85.210.201]:33148 "EHLO
        mail-pf1-f201.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1728684AbfIIW20 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 9 Sep 2019 18:28:26 -0400
Received: by mail-pf1-f201.google.com with SMTP id z23so11554404pfn.0
        for <kvm@vger.kernel.org>; Mon, 09 Sep 2019 15:28:24 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=date:in-reply-to:message-id:mime-version:references:subject:from:to
         :cc;
        bh=ksf47/iLkihsux2J4E043zbaHGjc5d9ygBfagTOkxzs=;
        b=UJs2of+LVQFrkmM2qFuN0+WXpGF4L/f2arTvfHNSVXWkKY42dv0zs5ZprRP6suC0PI
         J9IicgRdtfDD1mNsm95ypCfBMHdp9PWJHoETxHFOJT9sU5h6+XFymqbR3KYpLXaY2/CQ
         QycPmCKySCc+YBPPQpa3LVUneVuj9+92X8lSu3nKYyNsdLMqUPAhi75OedPJ2y/3KtRc
         tmYjUf2jaGhfWGu5zVLE4hNLtjVRadFwZ+hLu1IeO3YMjyqz8jw92sEJxbhuYJ4wdBKi
         H7bBIdP6i2beryTTFn82u6N6L5PUDCt8t4e01vHWSalBBYnUd6M10COqZjjvAxj9ze6Y
         Ol1A==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:date:in-reply-to:message-id:mime-version
         :references:subject:from:to:cc;
        bh=ksf47/iLkihsux2J4E043zbaHGjc5d9ygBfagTOkxzs=;
        b=ewpg0klkYBZwcX0hTJwxV62zR3jb8ln1f3Oz40g5tcjyc3YJQCros1HmCCMYVpsKhl
         /0lyEBQZQlMgYW3EK16QX43fOMrebgbrbgx99NsP9mJZC5i/J7G4hxjsERysbft/P7g/
         Rc5uku/SI5xmN7fgS0li7baUhUtrn6rUP0VVhV4Ehbt+mjXKHV68YfEEpXqAI+rNa1Ii
         dreZfSVqmTD5XP2DFYuAHyH3J0uXkhY1OyaiFDri3uDCGoBYe5sjdtJVavcrwQGioKtL
         hG+8iTbLZuGQhokXYbheu5Ls6BOaI668GJGWWDAER/P+lb4dUFinFCtXvE5BCgV4MYzR
         uuYw==
X-Gm-Message-State: APjAAAULL29TqjPSSN1gnqKqgRSAB4MVdYlqw3qzrwslE/+Gy8njLhvG
        KOQTIbHCpktgAFtUaQWVxFS0lENxZl3HWGtGJnzghvBkOHlpk8CmZy9cNb6RL0wzvGFsk5NelNK
        5rwUSYqnNbtQovlmH4Sl3qOlb3FcIIfiOD2gkORueIOqKFauXuU+OLlDIOkCrIu0=
X-Google-Smtp-Source: 
 APXvYqzeIE8yQzHbLFP/6QbSUhVqDL9z6HVnglkqfSro6rWzrvMgf4rdL2sgr2mw1BQyO0uBsvvVbeC0Mmd52Q==
X-Received: by 2002:a63:e14d:: with SMTP id
 h13mr24116867pgk.431.1568068103715;
 Mon, 09 Sep 2019 15:28:23 -0700 (PDT)
Date: Mon,  9 Sep 2019 15:28:12 -0700
In-Reply-To: <20190909222812.232690-1-jmattson@google.com>
Message-Id: <20190909222812.232690-2-jmattson@google.com>
Mime-Version: 1.0
References: <20190909222812.232690-1-jmattson@google.com>
X-Mailer: git-send-email 2.23.0.162.g0b9fbb3734-goog
Subject: [RFC][PATCH v2 1/1] KVM: nVMX: Don't leak L1 MMIO regions to L2
From: Jim Mattson <jmattson@google.com>
To: kvm@vger.kernel.org
Cc: Jim Mattson <jmattson@google.com>, Dan Cross <dcross@google.com>,
        Marc Orr <marcorr@google.com>, Peter Shier <pshier@google.com>
Content-Type: text/plain; charset="UTF-8"
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

If the "virtualize APIC accesses" VM-execution control is set in the
VMCS, the APIC virtualization hardware is triggered when a page walk
in VMX non-root mode terminates at a PTE wherein the address of the 4k
page frame matches the APIC-access address specified in the VMCS. On
hardware, the APIC-access address may be any valid 4k-aligned physical
address.

KVM's nVMX implementation enforces the additional constraint that the
APIC-access address specified in the vmcs12 must be backed by
cacheable memory in L1. If not, L0 will simply clear the "virtualize
APIC accesses" VM-execution control in the vmcs02.

The problem with this approach is that the L1 guest has arranged the
vmcs12 EPT tables--or shadow page tables, if the "enable EPT"
VM-execution control is clear in the vmcs12--so that the L2 guest
physical address(es)--or L2 guest linear address(es)--that reference
the L2 APIC map to the APIC-access address specified in the
vmcs12. Without the "virtualize APIC accesses" VM-execution control in
the vmcs02, the APIC accesses in the L2 guest will directly access the
APIC-access page in L1.

When L0 has no mapping whatsoever for the APIC-access address in L1,
the L2 VM just loses the intended APIC virtualization. However, when
the L2 APIC-access address is mapped to an MMIO region in L1, the L2
guest gets direct access to the L1 MMIO device. For example, if the
APIC-access address specified in the vmcs12 is 0xfee00000, then L2
gets direct access to L1's APIC.

Fixing this correctly is complicated. Since this vmcs12 configuration
is something that KVM cannot faithfully emulate, the appropriate
response is to exit to userspace with
KVM_INTERNAL_ERROR_EMULATION. Sadly, the kvm-unit-tests fail, so I'm
posting this as an RFC.

Note that the 'Code' line emitted by qemu in response to this error
shows the guest %rip two instructions after the
vmlaunch/vmresume. Hmmm.

Fixes: fe3ef05c7572 ("KVM: nVMX: Prepare vmcs02 from vmcs01 and vmcs12")
Reported-by: Dan Cross <dcross@google.com>
Signed-off-by: Jim Mattson <jmattson@google.com>
Reviewed-by: Marc Orr <marcorr@google.com>
Reviewed-by: Peter Shier <pshier@google.com>
Reviewed-by: Dan Cross <dcross@google.com>
---
 arch/x86/include/asm/kvm_host.h |  2 +-
 arch/x86/kvm/vmx/nested.c       | 65 +++++++++++++++++++++------------
 arch/x86/kvm/x86.c              |  9 ++++-
 3 files changed, 49 insertions(+), 27 deletions(-)

```
#### [kvm-unit-tests PATCH] x86: debug: use a constraint that doesn't allow a memory operand
##### From: Bill Wendling <morbo@google.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Bill Wendling <morbo@google.com>
X-Patchwork-Id: 11138557
Return-Path: <SRS0=hA4U=XE=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id A0D0514E5
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon,  9 Sep 2019 21:00:50 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 73D2621924
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon,  9 Sep 2019 21:00:50 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=google.com header.i=@google.com
 header.b="smvs3ouh"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729450AbfIIVAt (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 9 Sep 2019 17:00:49 -0400
Received: from mail-ua1-f65.google.com ([209.85.222.65]:34461 "EHLO
        mail-ua1-f65.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1727265AbfIIVAt (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 9 Sep 2019 17:00:49 -0400
Received: by mail-ua1-f65.google.com with SMTP id f25so4822158uap.1
        for <kvm@vger.kernel.org>; Mon, 09 Sep 2019 14:00:47 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=mime-version:from:date:message-id:subject:to;
        bh=iVGgwSWwHmexfKVbElUaVodcVwvI7SqR7HiFZZHgimI=;
        b=smvs3ouhvA0YvTEpruQ7DAxHZ6sC05J8+PvDKiJ09NEgLC7y8UmM7oXJg/Y896OEi3
         lKLhbCLTGUgXTIkLOxNaZD3QuVqY4P1Qze4wUWuh1B7RI0/7BVEI3HlPb/5rUszemnxl
         eJeN/F8NuoN8XmqCOmqOulRYwXOB8WjLcPUV8hHJXpxY8oK0VVAWGEo3fw6/90oFK0oi
         Hgf/1A1YrpH2paMfvqa4fbf7gIPP59e6ULhv8nZ/ufU83rzyi6JiBpLLAD6Ii6ozWlQY
         m9bsil2Na4tMU1ws8Ig105mHd4c8lAnqXwdMEsB51GGlpNtCMQ7pD8v36aOB1YwjE7wm
         hPxw==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:mime-version:from:date:message-id:subject:to;
        bh=iVGgwSWwHmexfKVbElUaVodcVwvI7SqR7HiFZZHgimI=;
        b=MOfrZ2nx7leAxSEkG7hOwCT5dRhl/8pfsEeDAxzPMZf9pC4dwgNUyZbC3XqhX6yBrr
         BH3o8NQyvnnXlHmE1VGV2hxd/DX87Q0idynF9HmMaIiPcgZ1zF8rPYOcIX+5iY1pxCRh
         MAogiAP8F6ePkbNEsA8/Bo3btASnrF+ht0ogrL9MUcfj5kjIGrxWF4G5CVhTAu52CrdF
         KuKEUrs9opEQsVyFom7V3U3yUd23JlBRcaCD95SPkl35I31a5yJycNji9of4VWlxDvoG
         20gcGntfM1hXI++8pvD/a05qg5fpBuPe4pwGLtZ38eLYH5kCB9mMhR4PKLhyfCzjgZox
         NtmQ==
X-Gm-Message-State: APjAAAX1zfsBH1RQfYaYL0ImTQRJSS9hKk1qHTdKYFyZeOoZ4ljsGjio
        1hRQXTcE1fouNgxC02svJ7WGdq9W/YUleeRxXbGatLiHfKxg
X-Google-Smtp-Source: 
 APXvYqx05tpDmPNJFOG1Q1CFqnMLxIiwOgvv06S0sUxIRp2N/gCHHelerm93DNej+jYdMQl8T2gwhG0Du8PgZeGLIw0=
X-Received: by 2002:ab0:2a8c:: with SMTP id
 h12mr12223915uar.106.1568062846203;
 Mon, 09 Sep 2019 14:00:46 -0700 (PDT)
MIME-Version: 1.0
From: Bill Wendling <morbo@google.com>
Date: Mon, 9 Sep 2019 14:00:35 -0700
Message-ID: 
 <CAGG=3QUHwHsVtrc3UYhhbkBX5WOp4Am=beFnn7yyxh6ykTe_Fw@mail.gmail.com>
Subject: [kvm-unit-tests PATCH] x86: debug: use a constraint that doesn't
 allow a memory operand
To: kvm@vger.kernel.org
Content-Type: text/plain; charset="UTF-8"
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The "lea" instruction cannot load the effective address into a memory
location. The "g" constraint allows a compiler to use a memory location.
A compiler that uses a register destination does so only because one is
available. Use a general register constraint to make sure it always uses
a register.

Signed-off-by: Bill Wendling <morbo@google.com>
---
 x86/debug.c | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
#### [kvm-unit-tests PATCH] x86: emulator: use "q" operand modifierTo: kvm@vger.kernel.org
##### From: Bill Wendling <morbo@google.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Bill Wendling <morbo@google.com>
X-Patchwork-Id: 11138565
Return-Path: <SRS0=hA4U=XE=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 0F70F924
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon,  9 Sep 2019 21:28:38 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id DDE9C218DE
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon,  9 Sep 2019 21:28:37 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=google.com header.i=@google.com
 header.b="DqmJDzLV"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1731619AbfIIV2g (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 9 Sep 2019 17:28:36 -0400
Received: from mail-vs1-f66.google.com ([209.85.217.66]:40859 "EHLO
        mail-vs1-f66.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726823AbfIIV2g (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 9 Sep 2019 17:28:36 -0400
Received: by mail-vs1-f66.google.com with SMTP id v10so6574139vsc.7
        for <kvm@vger.kernel.org>; Mon, 09 Sep 2019 14:28:34 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=mime-version:from:date:message-id:subject:to;
        bh=e2ktFZF09JWLvJgyosojNipCBqZF/U6ANeFGH386vZY=;
        b=DqmJDzLVtc5n3gFDdkT4xNhlH7aB8uCN+EUtM505vt+oBK3bojBx5gsOP2hhjLyF64
         GstoTU5ulX60fo3wrs4+Nc6WN+Wi5dozDJwmJyAn7nTEeQ1Fu75IGIG9dltPwryZMwWF
         rYn3iaSbuTU4JbipfjtyBhwyOp4n85MHdTUKrnCB/uL6ctYndEwAG1i/uIaEwUcisd+l
         0ZvzKAX25ttBV4JSZTW4W2m6HfJSuTelMUu4FJZly11lGcp+Qn3jvPOsUzlXWs/pQTxP
         FQpyN9aZDZK7OOHUwUIkT/kpWwbBSedseQNmC5c/D4Q4iBrd5HVsrVvPpK9jD+wu0PyR
         Qo8A==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:mime-version:from:date:message-id:subject:to;
        bh=e2ktFZF09JWLvJgyosojNipCBqZF/U6ANeFGH386vZY=;
        b=ImKfaprVidOriM0OapQ0rtf+M/i+ETmOzfrYPgfY6G8EBMLGXTXJwUlUqgX5he3dWA
         fMsvnCTiMCNa6edwbH/eFxZVznevPlGJO60ZsxLHtaWTpQa/mPExkwgcMwYek07uw1xz
         KcParLZfgenb9D9wY3tWOhUNfGnPjQuJoxEzg9+TvL9WcIxeNZmWYWdVd3HnXz6sWrwy
         aqECOvQvZ0+XZrY7gDGiSE+k6wynZqpCO9Vv5TfYmjAZ+NhfgP2rrIjg4I7L4S7X7VdZ
         9dyhWLwBc8GqWGYwaH9gqaY7iieFzGvVncKAjOcREon7YwnFz6CD25zNIQ5MeYXiyeuL
         pAxQ==
X-Gm-Message-State: APjAAAWnlI2QGSY/L8JGe9oTN7PgpF1omd1tAO6e/BUj528S+2lADf+3
        ujxhbD5PrKSuEbu9z/fiAt3Tc54pH/uoufTLcqc1/IXG2YDv
X-Google-Smtp-Source: 
 APXvYqxdOt+tN+BcSksjGDxpPNwLV3d8M7uVFuEMzG3E/geIkgYUNmWTOeLa8LB1m950yVTPfbE6mNcNWpFb9Uz3Di4=
X-Received: by 2002:a67:ec18:: with SMTP id d24mr11152565vso.80.1568064513635;
 Mon, 09 Sep 2019 14:28:33 -0700 (PDT)
MIME-Version: 1.0
From: Bill Wendling <morbo@google.com>
Date: Mon, 9 Sep 2019 14:28:22 -0700
Message-ID: 
 <CAGG=3QV-0hPrWx8dFptjqbKMNfne+iTfq2e-KL89ebecO8Ta1w@mail.gmail.com>
Subject: [kvm-unit-tests PATCH] x86: emulator: use "q" operand modifier
To: kvm@vger.kernel.org
Content-Type: text/plain; charset="UTF-8"
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The extended assembly documentation list only "q" as an operand modifier
for DImode registers. The "d" seems to be an AMD-ism, which appears to
be only begrudgingly supported by gcc.

Signed-off-by: Bill Wendling <morbo@google.com>
---
 x86/emulator.c | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
#### [kvm-unit-tests PATCH] x86: remove memory constraint from "mov" instruction
##### From: Bill Wendling <morbo@google.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Bill Wendling <morbo@google.com>
X-Patchwork-Id: 11138561
Return-Path: <SRS0=hA4U=XE=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 8C854924
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon,  9 Sep 2019 21:21:41 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 62514218DE
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon,  9 Sep 2019 21:21:41 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=google.com header.i=@google.com
 header.b="niqtfSAi"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727535AbfIIVTc (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 9 Sep 2019 17:19:32 -0400
Received: from mail-vs1-f67.google.com ([209.85.217.67]:37541 "EHLO
        mail-vs1-f67.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726930AbfIIVTc (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 9 Sep 2019 17:19:32 -0400
Received: by mail-vs1-f67.google.com with SMTP id q9so9815226vsl.4
        for <kvm@vger.kernel.org>; Mon, 09 Sep 2019 14:19:31 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=mime-version:from:date:message-id:subject:to;
        bh=oOiZ1EdVlfm+qg42MPgETyKI/X2VoNKNgczezd9rkcY=;
        b=niqtfSAi4arCrS43bsKpbw7tLD4wRv1qkEhYdKmemq8kaz/qi3M0z/WH4sS5yr5qlb
         hq+Q5liUDXHloON2TX16CetwqArBsS1gPt4ANSnrHWh9pRa79/zzGFCQnHxCrte/lnrP
         MGfJXFEyiEyxERsBb3JzH9YG8aIzvMHam3IbHPaiHnFPIR35n15HO7P5h/zADVNvmAQU
         VYwKHOYWdNokZB6aslV5h6ZiOsv2HCrJZ5Zt+i25l2XkRAzE7Prg+b4TR78RQ3x6WZyg
         LYyGnc3+9nLJ5Ia8xIomEElBFMMaNxp9UGnGt0h1KVQyUSZZO1P6kYfkW80Y09TC0Gde
         5/Sg==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:mime-version:from:date:message-id:subject:to;
        bh=oOiZ1EdVlfm+qg42MPgETyKI/X2VoNKNgczezd9rkcY=;
        b=C0FAAv7dqOKEEG37qi0Wrsn5QWhEtR4S/Fy+dKid2Sped+CKUJWJZNkqoWLhUhARSZ
         4vqmjK+JFi3gnk96EJ5RCTBXgZ9LJcfpqJtQfJ8RHSCuab+pEoaMUXSYNJjDqRNxmOh5
         gGyU+7ZFuTqGOrqb1bq6Rr1+v6rTwjes0aT7aVMLYZeknxcQkdNA4zwnmCY1qL5AqSXU
         wrpLZT5A30Bndu43Q0fGy9yjIAW3bDzv4gxux8jAiYo2J1cdPfPRfTEruuV1IP9muZNw
         3XEqfaw9ezsh18GIwov9BJnBIYEVszEHunVeuaUHOBkFZY//sFYPVDaYMrpNmvfbNk0O
         rs0w==
X-Gm-Message-State: APjAAAWyMEjrAF4DKFlSnZq2R6durPLv73awX/5XW7a880Dapoz7Bk4U
        dfhWj7xbMmE7RsbA056pOhZh7UbzXbOjTFdh6zXHiwP0XZx6
X-Google-Smtp-Source: 
 APXvYqxmn3H2PufT8xzGrLjXW+wOFnhjqfBkdc1pRFw6G3cGmMrNzX+HltgJK46bNz5zdG04R4LiJoevXx8xmEm5AK0=
X-Received: by 2002:a67:2f4b:: with SMTP id v72mr9593621vsv.212.1568063970819;
 Mon, 09 Sep 2019 14:19:30 -0700 (PDT)
MIME-Version: 1.0
From: Bill Wendling <morbo@google.com>
Date: Mon, 9 Sep 2019 14:19:20 -0700
Message-ID: 
 <CAGG=3QWteHe8zCdXQVQv+42pMO2k4XvAbj_A=ptRUi9E2AwT2w@mail.gmail.com>
Subject: [kvm-unit-tests PATCH] x86: remove memory constraint from "mov"
 instruction
To: kvm@vger.kernel.org
Content-Type: text/plain; charset="UTF-8"
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The "mov" instruction to get the error code shouldn't move into a memory
location. Don't allow the compiler to make this decision. Instead
specify that only a register is appropriate here.

Signed-off-by: Bill Wendling <morbo@google.com>
---
 lib/x86/desc.c | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
#### [kvm-unit-tests PATCH] x86: setjmp: ignore clang's "-Wsomtimes-uninitialized" flag
##### From: Bill Wendling <morbo@google.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Bill Wendling <morbo@google.com>
X-Patchwork-Id: 11138559
Return-Path: <SRS0=hA4U=XE=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 9FAC616B1
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon,  9 Sep 2019 21:09:59 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 72ADE21924
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon,  9 Sep 2019 21:09:59 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=google.com header.i=@google.com
 header.b="WSu0jxdm"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1731720AbfIIVJ6 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 9 Sep 2019 17:09:58 -0400
Received: from mail-vk1-f195.google.com ([209.85.221.195]:41554 "EHLO
        mail-vk1-f195.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1727483AbfIIVJ6 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 9 Sep 2019 17:09:58 -0400
Received: by mail-vk1-f195.google.com with SMTP id 70so2171492vkz.8
        for <kvm@vger.kernel.org>; Mon, 09 Sep 2019 14:09:56 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=mime-version:from:date:message-id:subject:to;
        bh=IUKaCUxjYc5VcvRzjcVT6xODxoxaXR4KZGQsmHyhhiM=;
        b=WSu0jxdmORs+9mSLcb4D2+ZNSYtAfNfVY2E0+MTf60v37RGn//6Ojef19CC5H+LXD/
         YCvcLCrFai/KBaddWH0F4VXzEyN1BD0dxBN+y0KLiNp2knRSjYsnGC7KOJ940zAXoqv3
         hylYyO32YaX2Y3zlxz/DgNlX1FmjiAKj62KCAmwSd5MB6y9MaAaVvG1W6xW6Hw5wvPqb
         NZITi4gsbfnyK3XKvyd8spyV1zMb3Jufpmtd343wvjXppLGFMHnOtCYO4Wifaqx3XA8b
         h7mMrP0FKPelCVKa94rKfP5xJb+kMCUbBR2oZleOhs/l9dBWg7jqbGj9bQd1zB7WIq9K
         QbmQ==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:mime-version:from:date:message-id:subject:to;
        bh=IUKaCUxjYc5VcvRzjcVT6xODxoxaXR4KZGQsmHyhhiM=;
        b=ZekU4hKbGGdhB2ePUFkzaitmSPFzt5o0/R9vcAUpjVQGRQICVV7fXb/kxq0dl42nn1
         fn1xc1iS4ObNVxDZKxiMPmepynwrIYo1Dnz18neKcTHQuOaKeylnIVGgcPhGbdT8QODQ
         4N6bvTTQMeRR17zu+m8kePeMKNvgeCUkuFoYFDb5fbu9nBSc4moCzdpKPODqx3OJsau1
         2vtLB0oFljm4Uqg04qhRwx2fcmgz+VIDu+ppc3+zc1LR4p3fQEvmKdMJjlOU99FM3zw1
         T9xlKnWobrAo+JNOlAmorIl9Nis5gTaIH5XZ18ccIGePdyQo3JcDJMzfeTPL/j8jvAgn
         3jpg==
X-Gm-Message-State: APjAAAVpgpwc9LUKTOVReZPHo8NosTHYv3y0PxlMJ6ZcxlyMqMPedxEj
        /1WoaNehKG21ndqisrSi2OhRkIISw2Nj9BK4KY71lzr+CDqY
X-Google-Smtp-Source: 
 APXvYqz6iuI0gHDPymXkyuF36GFsOXPnaOj7f1ySw5rN2X+wZ5DTN7ubaQKok7I1pyA5NGOVo9nWeAI0aFDOt6z2Agg=
X-Received: by 2002:a1f:3cc9:: with SMTP id
 j192mr12284618vka.58.1568063394809;
 Mon, 09 Sep 2019 14:09:54 -0700 (PDT)
MIME-Version: 1.0
From: Bill Wendling <morbo@google.com>
Date: Mon, 9 Sep 2019 14:09:43 -0700
Message-ID: 
 <CAGG=3QWNQKejpwhbgDy-WSV1C2sw9Ms0TUGwVk8fgEbg9n0ryg@mail.gmail.com>
Subject: [kvm-unit-tests PATCH] x86: setjmp: ignore clang's
 "-Wsomtimes-uninitialized" flag
To: kvm@vger.kernel.org
Content-Type: text/plain; charset="UTF-8"
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Clang complains that "i" might be uninitialized in the "printf"
statement. This is a false negative, because it's set in the "if"
statement and then incremented in the loop created by the "longjmp".

Signed-off-by: Bill Wendling <morbo@google.com>
---
 x86/setjmp.c | 4 ++++
 1 file changed, 4 insertions(+)

```
#### [PATCH] Revert "locking/pvqspinlock: Don't wait if vCPU is preempted"
##### From: Wanpeng Li <kernellwp@gmail.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 8bit
X-Patchwork-Submitter: Wanpeng Li <kernellwp@gmail.com>
X-Patchwork-Id: 11137127
Return-Path: <SRS0=hA4U=XE=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 94C3E13B1
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon,  9 Sep 2019 01:40:45 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 6989920863
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon,  9 Sep 2019 01:40:45 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=gmail.com header.i=@gmail.com
 header.b="VV7Wrq6M"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1732416AbfIIBkf (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Sun, 8 Sep 2019 21:40:35 -0400
Received: from mail-pl1-f196.google.com ([209.85.214.196]:45025 "EHLO
        mail-pl1-f196.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1731948AbfIIBkf (ORCPT <rfc822;kvm@vger.kernel.org>);
        Sun, 8 Sep 2019 21:40:35 -0400
Received: by mail-pl1-f196.google.com with SMTP id k1so5798201pls.11;
        Sun, 08 Sep 2019 18:40:34 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=from:to:cc:subject:date:message-id:mime-version
         :content-transfer-encoding;
        bh=k1Kf8xMbkRDHr8n0Ak2LvAQxnQ9bC0rCE/1ZgT65+C4=;
        b=VV7Wrq6MY+yzFcwIwG1efanp6VJ8HOZ3HH9TT5BHjXp0/4DuBcVOdgszMBySBSDaU4
         aW29GAKuwuAweCAxIL4mBethP+Dp9f8+uky/+fop7aBAzRAd/l+trbYZDHUXwuEY4vgt
         Jc2b4Mkej7a3+I+3ngg2BukVELBFUvfQpGQ/1+OZTgyK1VoR2Z6q9SfwZ52ZhNgRSjYk
         fNAhI1QXHeDCa468pwoXpLJhLD6DJirSv2wvwzlmIxD5mwQXOE0unyQkGU0HDAdk1VWR
         FJxyQMpEzUoAr8EqAIoEyT/2kwwbziG0dd1rcMHoZgxvOS3d2TbQXjzQM3idAt+SRUYQ
         lQsw==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:mime-version
         :content-transfer-encoding;
        bh=k1Kf8xMbkRDHr8n0Ak2LvAQxnQ9bC0rCE/1ZgT65+C4=;
        b=oTVdum2OpyBcO5c/7q1MrYJ1Q8khoZIVpzuMeH6+F2xPNxhWGTXen9BrKilAhNHjzp
         H3SBpkoeTgyrxVMUDCm16c5TUJUHlqFSe/glMy2OQVqGE6INUeH//6eD7KpxD9KKBRZI
         wCuPrlykMkWK/Wwq9SW7ngKEa9bVA4R54CfNea+0zXTycaqFLyaYzVayDeIHTPp1InNZ
         9TJyhWYx1tK1CbaiA9fX7JshO3kYAREsGXmJxBfTbq9WFHReQHb4WaOpPme4AD6DNlb6
         KoabJ52u0IJcnj7p77cd5hlzSN5VpsYpxh3p92ZkLKB5i99ewpBL34E9GpNAbDQz68aL
         VGTQ==
X-Gm-Message-State: APjAAAVPvwoNByNg59ckbPNuLxCJfdfdqhzkSMfeTjipXC1Ju92aIkW2
        Nx4636XFXt6tew/f1QP1P/Jbljy3
X-Google-Smtp-Source: 
 APXvYqx/KsEp8b0srchrNLkvc8bnJcJN2/lMsKwOLdoaFG+Diy+DWrPllHpcniCsDmSRUXTwZZilrQ==
X-Received: by 2002:a17:902:7c88:: with SMTP id
 y8mr21451213pll.306.1567993234474;
        Sun, 08 Sep 2019 18:40:34 -0700 (PDT)
Received: from localhost.localdomain ([203.205.141.123])
        by smtp.googlemail.com with ESMTPSA id
 j26sm12413196pfe.181.2019.09.08.18.40.30
        (version=TLS1_2 cipher=ECDHE-RSA-AES128-SHA bits=128/128);
        Sun, 08 Sep 2019 18:40:33 -0700 (PDT)
From: Wanpeng Li <kernellwp@gmail.com>
X-Google-Original-From: Wanpeng Li <wanpengli@tencent.com>
To: linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Cc: Paolo Bonzini <pbonzini@redhat.com>,
 =?utf-8?b?UmFkaW0gS3LEjW3DocWZ?= <rkrcmar@redhat.com>,
 Sean Christopherson <sean.j.christopherson@intel.com>,
 Vitaly Kuznetsov <vkuznets@redhat.com>, Wanpeng Li <wanpengli@tencent.com>,
 Jim Mattson <jmattson@google.com>, Joerg Roedel <joro@8bytes.org>,
 Peter Zijlstra <peterz@infradead.org>, Thomas Gleixner <tglx@linutronix.de>,
 Ingo Molnar <mingo@kernel.org>, Waiman Long <longman@redhat.com>,
 loobinliu@tencent.com, stable@vger.kernel.org
Subject: [PATCH] Revert "locking/pvqspinlock: Don't wait if vCPU is preempted"
Date: Mon,  9 Sep 2019 09:40:28 +0800
Message-Id: <1567993228-23668-1-git-send-email-wanpengli@tencent.com>
X-Mailer: git-send-email 2.7.4
MIME-Version: 1.0
Content-Type: text/plain; charset=UTF-8
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Wanpeng Li <wanpengli@tencent.com>

This patch reverts commit 75437bb304b20 (locking/pvqspinlock: Don't wait if 
vCPU is preempted), we found great regression caused by this commit.

Xeon Skylake box, 2 sockets, 40 cores, 80 threads, three VMs, each is 80 vCPUs.
The score of ebizzy -M can reduce from 13000-14000 records/s to 1700-1800 
records/s with this commit.

          Host                       Guest                score

vanilla + w/o kvm optimizes     vanilla               1700-1800 records/s
vanilla + w/o kvm optimizes     vanilla + revert      13000-14000 records/s
vanilla + w/ kvm optimizes      vanilla               4500-5000 records/s
vanilla + w/ kvm optimizes      vanilla + revert      14000-15500 records/s

Exit from aggressive wait-early mechanism can result in yield premature and 
incur extra scheduling latency in over-subscribe scenario.

kvm optimizes:
[1] commit d73eb57b80b (KVM: Boost vCPUs that are delivering interrupts)
[2] commit 266e85a5ec9 (KVM: X86: Boost queue head vCPU to mitigate lock waiter preemption)

Tested-by: loobinliu@tencent.com
Cc: Peter Zijlstra <peterz@infradead.org>
Cc: Thomas Gleixner <tglx@linutronix.de>
Cc: Ingo Molnar <mingo@kernel.org>
Cc: Waiman Long <longman@redhat.com>
Cc: Paolo Bonzini <pbonzini@redhat.com>
Cc: Radim Krčmář <rkrcmar@redhat.com>
Cc: loobinliu@tencent.com
Cc: stable@vger.kernel.org 
Fixes: 75437bb304b20 (locking/pvqspinlock: Don't wait if vCPU is preempted)
Signed-off-by: Wanpeng Li <wanpengli@tencent.com>
---
 kernel/locking/qspinlock_paravirt.h | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
