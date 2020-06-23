#### [PATCH v4 01/18] nitro_enclaves: Add ioctl interface definition
##### From: Andra Paraschiv <andraprs@amazon.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Andra Paraschiv <andraprs@amazon.com>
X-Patchwork-Id: 11618863
Return-Path: <SRS0=pCMg=AD=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 00A5B912
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 22 Jun 2020 20:04:02 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id D717420776
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 22 Jun 2020 20:04:01 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=amazon.com header.i=@amazon.com
 header.b="afcyCd/T"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728724AbgFVUD6 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 22 Jun 2020 16:03:58 -0400
Received: from smtp-fw-9101.amazon.com ([207.171.184.25]:63405 "EHLO
        smtp-fw-9101.amazon.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1728705AbgFVUD5 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 22 Jun 2020 16:03:57 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
  d=amazon.com; i=@amazon.com; q=dns/txt; s=amazon201209;
  t=1592856235; x=1624392235;
  h=from:to:cc:subject:date:message-id:in-reply-to:
   references:mime-version:content-transfer-encoding;
  bh=HN3iuqvXzazy6PTJ1frneZ9rbwR5fbtHmHH+MbPMD/k=;
  b=afcyCd/TgZsvLt0UxUSA3wJhYuj9cpvUkDaYeaSLB2V+tg+YHQBSvxT5
   +cbCTS3CqoIOO7i1BObngJMgaDk/ewbRiOVC43C222L7hiKhQG2WCiJ7E
   WDVOB3U62hdxpCourCM0xhVA64U/oienNy4o/1jB1Hf2+WR5B/DwBr7Pc
   A=;
IronPort-SDR: 
 NHQe3lmSg5yRLmjpRtheXB8GcwxwC8mkmRcPoh84ltl9ccV1yGNluRsTraI2rTXK7iWkuO3mJ4
 J1GXhPMt3eYQ==
X-IronPort-AV: E=Sophos;i="5.75,268,1589241600";
   d="scan'208";a="46040881"
Received: from sea32-co-svc-lb4-vlan3.sea.corp.amazon.com (HELO
 email-inbound-relay-2c-4e7c8266.us-west-2.amazon.com) ([10.47.23.38])
  by smtp-border-fw-out-9101.sea19.amazon.com with ESMTP;
 22 Jun 2020 20:03:55 +0000
Received: from EX13MTAUEA002.ant.amazon.com
 (pdx4-ws-svc-p6-lb7-vlan2.pdx.amazon.com [10.170.41.162])
        by email-inbound-relay-2c-4e7c8266.us-west-2.amazon.com (Postfix) with
 ESMTPS id A0D72A1D12;
        Mon, 22 Jun 2020 20:03:54 +0000 (UTC)
Received: from EX13D16EUB003.ant.amazon.com (10.43.166.99) by
 EX13MTAUEA002.ant.amazon.com (10.43.61.77) with Microsoft SMTP Server (TLS)
 id 15.0.1497.2; Mon, 22 Jun 2020 20:03:54 +0000
Received: from 38f9d34ed3b1.ant.amazon.com (10.43.161.145) by
 EX13D16EUB003.ant.amazon.com (10.43.166.99) with Microsoft SMTP Server (TLS)
 id 15.0.1497.2; Mon, 22 Jun 2020 20:03:44 +0000
From: Andra Paraschiv <andraprs@amazon.com>
To: <linux-kernel@vger.kernel.org>
CC: Anthony Liguori <aliguori@amazon.com>,
        Benjamin Herrenschmidt <benh@kernel.crashing.org>,
        Colm MacCarthaigh <colmmacc@amazon.com>,
        "Bjoern Doebel" <doebel@amazon.de>,
        David Woodhouse <dwmw@amazon.co.uk>,
        "Frank van der Linden" <fllinden@amazon.com>,
        Alexander Graf <graf@amazon.de>,
        Greg KH <gregkh@linuxfoundation.org>,
        Martin Pohlack <mpohlack@amazon.de>,
        "Matt Wilson" <msw@amazon.com>,
        Paolo Bonzini <pbonzini@redhat.com>,
        Balbir Singh <sblbir@amazon.com>,
        Stefano Garzarella <sgarzare@redhat.com>,
        "Stefan Hajnoczi" <stefanha@redhat.com>,
        Stewart Smith <trawets@amazon.com>,
        "Uwe Dannowski" <uwed@amazon.de>, <kvm@vger.kernel.org>,
        <ne-devel-upstream@amazon.com>,
        Andra Paraschiv <andraprs@amazon.com>
Subject: [PATCH v4 01/18] nitro_enclaves: Add ioctl interface definition
Date: Mon, 22 Jun 2020 23:03:12 +0300
Message-ID: <20200622200329.52996-2-andraprs@amazon.com>
X-Mailer: git-send-email 2.20.1 (Apple Git-117)
In-Reply-To: <20200622200329.52996-1-andraprs@amazon.com>
References: <20200622200329.52996-1-andraprs@amazon.com>
MIME-Version: 1.0
X-Originating-IP: [10.43.161.145]
X-ClientProxiedBy: EX13D12UWC002.ant.amazon.com (10.43.162.253) To
 EX13D16EUB003.ant.amazon.com (10.43.166.99)
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The Nitro Enclaves driver handles the enclave lifetime management. This
includes enclave creation, termination and setting up its resources such
as memory and CPU.

An enclave runs alongside the VM that spawned it. It is abstracted as a
process running in the VM that launched it. The process interacts with
the NE driver, that exposes an ioctl interface for creating an enclave
and setting up its resources.

Signed-off-by: Alexandru Vasile <lexnv@amazon.com>
Signed-off-by: Andra Paraschiv <andraprs@amazon.com>
---
Changelog

v3 -> v4

* Decouple NE ioctl interface from KVM API.
* Add NE API version and the corresponding ioctl call.
* Add enclave / image load flags options.

v2 -> v3

* Remove the GPL additional wording as SPDX-License-Identifier is
  already in place.

v1 -> v2

* Add ioctl for getting enclave image load metadata.
* Update NE_ENCLAVE_START ioctl name to NE_START_ENCLAVE.
* Add entry in Documentation/userspace-api/ioctl/ioctl-number.rst for NE
  ioctls.
* Update NE ioctls definition based on the updated ioctl range for major
  and minor.
---
 .../userspace-api/ioctl/ioctl-number.rst      |   5 +-
 include/linux/nitro_enclaves.h                |  11 ++
 include/uapi/linux/nitro_enclaves.h           | 137 ++++++++++++++++++
 3 files changed, 152 insertions(+), 1 deletion(-)
 create mode 100644 include/linux/nitro_enclaves.h
 create mode 100644 include/uapi/linux/nitro_enclaves.h

```
#### [PATCH v2 1/5] KVM: arm64: Enable Address Authentication at EL2 if available
##### From: Marc Zyngier <maz@kernel.org>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Marc Zyngier <maz@kernel.org>
X-Patchwork-Id: 11617169
Return-Path: <SRS0=pCMg=AD=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 6A10D913
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 22 Jun 2020 08:06:56 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 4612920C09
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 22 Jun 2020 08:06:56 +0000 (UTC)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple; d=kernel.org;
	s=default; t=1592813216;
	bh=0gZJhb39igS0hzVb6zMN/tZFT8C1rNqIbw7RukeMKqc=;
	h=From:To:Cc:Subject:Date:In-Reply-To:References:List-ID:From;
	b=xyJcW/IViABF/qXUaen5nrCR0nXbskDsJMsOOiHoDfER3gd6UDB3NhNXtdSfkJBXX
	 TiXvkP6dQ3/1rPU/YHCddDoy/6LJp/Bsi1gkxASTIwRgZT3axbFxr/th9yFUIgZFj0
	 l9DPq5Z/QnJWTn4WiMQlxJfKfHf0QSw+unPjRlcg=
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1725925AbgFVIGz (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 22 Jun 2020 04:06:55 -0400
Received: from mail.kernel.org ([198.145.29.99]:42076 "EHLO mail.kernel.org"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1725820AbgFVIGy (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 22 Jun 2020 04:06:54 -0400
Received: from disco-boy.misterjones.org (disco-boy.misterjones.org
 [51.254.78.96])
        (using TLSv1.2 with cipher ECDHE-RSA-AES256-GCM-SHA384 (256/256 bits))
        (No client certificate requested)
        by mail.kernel.org (Postfix) with ESMTPSA id 80B7A207F5;
        Mon, 22 Jun 2020 08:06:53 +0000 (UTC)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple; d=kernel.org;
        s=default; t=1592813213;
        bh=0gZJhb39igS0hzVb6zMN/tZFT8C1rNqIbw7RukeMKqc=;
        h=From:To:Cc:Subject:Date:In-Reply-To:References:From;
        b=FK0x9M3Xz92zroB0HDA8eCvUmbWChlJfvuB2LSTzLrPtpLgywvtwHIMmpCTfRWChr
         lQMeCDv05vV+0B15CS5sjekcrtbN8YqkNOYVEXteRaa6lT/KMNew8PNFiOe1FOZgwq
         EpyuN/Fbgq6P34uvJM88tie1bAHO2yjFlTF/LsHI=
Received: from 78.163-31-62.static.virginmediabusiness.co.uk ([62.31.163.78]
 helo=why.lan)
        by disco-boy.misterjones.org with esmtpsa
 (TLS1.3:ECDHE_RSA_AES_256_GCM_SHA384:256)
        (Exim 4.92)
        (envelope-from <maz@kernel.org>)
        id 1jnHTg-005FG8-0v; Mon, 22 Jun 2020 09:06:52 +0100
From: Marc Zyngier <maz@kernel.org>
To: kvm@vger.kernel.org, linux-arm-kernel@lists.infradead.org,
        kvmarm@lists.cs.columbia.edu
Cc: James Morse <james.morse@arm.com>,
        Julien Thierry <julien.thierry.kdev@gmail.com>,
        Suzuki K Poulose <suzuki.poulose@arm.com>,
        Mark Rutland <mark.rutland@arm.com>,
        Andrew Scull <ascull@google.com>,
        Dave Martin <Dave.Martin@arm.com>, kernel-team@android.com
Subject: [PATCH v2 1/5] KVM: arm64: Enable Address Authentication at EL2 if
 available
Date: Mon, 22 Jun 2020 09:06:39 +0100
Message-Id: <20200622080643.171651-2-maz@kernel.org>
X-Mailer: git-send-email 2.27.0
In-Reply-To: <20200622080643.171651-1-maz@kernel.org>
References: <20200622080643.171651-1-maz@kernel.org>
MIME-Version: 1.0
X-SA-Exim-Connect-IP: 62.31.163.78
X-SA-Exim-Rcpt-To: kvm@vger.kernel.org, linux-arm-kernel@lists.infradead.org,
 kvmarm@lists.cs.columbia.edu, james.morse@arm.com,
 julien.thierry.kdev@gmail.com, suzuki.poulose@arm.com, mark.rutland@arm.com,
 ascull@google.com, Dave.Martin@arm.com, kernel-team@android.com
X-SA-Exim-Mail-From: maz@kernel.org
X-SA-Exim-Scanned: No (on disco-boy.misterjones.org);
 SAEximRunCond expanded to false
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

While initializing EL2, enable Address Authentication if detected
from EL1. We still use the EL1-provided keys though.

Acked-by: Andrew Scull <ascull@google.com>
Signed-off-by: Marc Zyngier <maz@kernel.org>
Acked-by: Mark Rutland <mark.rutland@arm.com>
---
 arch/arm64/kvm/hyp-init.S | 5 +++++
 1 file changed, 5 insertions(+)

```
#### [PATCH v2 01/21] KVM: x86/mmu: Track the associated kmem_cache in the MMU caches
##### From: Sean Christopherson <sean.j.christopherson@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Sean Christopherson <sean.j.christopherson@intel.com>
X-Patchwork-Id: 11618983
Return-Path: <SRS0=pCMg=AD=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 1EAE2913
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 22 Jun 2020 20:11:33 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 11A23207DD
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 22 Jun 2020 20:11:33 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1730393AbgFVUJO (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 22 Jun 2020 16:09:14 -0400
Received: from mga12.intel.com ([192.55.52.136]:60195 "EHLO mga12.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1728545AbgFVUJI (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 22 Jun 2020 16:09:08 -0400
IronPort-SDR: 
 LHgdYx+YHRowd1VmxdaVQ2sIf3s6ASX9acNEl745hLmjZSp7+BZSqKXBMOdddFPmLrT5xEuiIk
 DbBBszADphCA==
X-IronPort-AV: E=McAfee;i="6000,8403,9660"; a="123527697"
X-IronPort-AV: E=Sophos;i="5.75,268,1589266800";
   d="scan'208";a="123527697"
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from fmsmga003.fm.intel.com ([10.253.24.29])
  by fmsmga106.fm.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 22 Jun 2020 13:09:07 -0700
IronPort-SDR: 
 vXb76dirRUAUgp/uOEGjgnvj/Ui+8YdfKo+tBiS+YyELBpeXM4tbMO7/ZRvLDb7nWDLaKxYnPx
 pCdlG1JSFAiQ==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.75,268,1589266800";
   d="scan'208";a="318877042"
Received: from sjchrist-coffee.jf.intel.com ([10.54.74.152])
  by FMSMGA003.fm.intel.com with ESMTP; 22 Jun 2020 13:09:07 -0700
From: Sean Christopherson <sean.j.christopherson@intel.com>
To: Marc Zyngier <maz@kernel.org>, Paolo Bonzini <pbonzini@redhat.com>,
        Arnd Bergmann <arnd@arndb.de>
Cc: James Morse <james.morse@arm.com>,
        Julien Thierry <julien.thierry.kdev@gmail.com>,
        Suzuki K Poulose <suzuki.poulose@arm.com>,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>,
        linux-arm-kernel@lists.infradead.org, kvmarm@lists.cs.columbia.edu,
        linux-mips@vger.kernel.org, kvm@vger.kernel.org,
        linux-arch@vger.kernel.org, linux-kernel@vger.kernel.org,
        Ben Gardon <bgardon@google.com>,
        Peter Feiner <pfeiner@google.com>,
        Peter Shier <pshier@google.com>,
        Junaid Shahid <junaids@google.com>,
        Christoffer Dall <christoffer.dall@arm.com>
Subject: [PATCH v2 01/21] KVM: x86/mmu: Track the associated kmem_cache in the
 MMU caches
Date: Mon, 22 Jun 2020 13:08:02 -0700
Message-Id: <20200622200822.4426-2-sean.j.christopherson@intel.com>
X-Mailer: git-send-email 2.26.0
In-Reply-To: <20200622200822.4426-1-sean.j.christopherson@intel.com>
References: <20200622200822.4426-1-sean.j.christopherson@intel.com>
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Track the kmem_cache used for non-page KVM MMU memory caches instead of
passing in the associated kmem_cache when filling the cache.  This will
allow consolidating code and other cleanups.

No functional change intended.

Reviewed-by: Ben Gardon <bgardon@google.com>
Signed-off-by: Sean Christopherson <sean.j.christopherson@intel.com>
---
 arch/x86/include/asm/kvm_host.h |  1 +
 arch/x86/kvm/mmu/mmu.c          | 24 +++++++++++-------------
 2 files changed, 12 insertions(+), 13 deletions(-)

```
#### [PATCH] KVM: LAPIC: ensure APIC map is up to date on concurrent update requests
##### From: Paolo Bonzini <pbonzini@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Paolo Bonzini <pbonzini@redhat.com>
X-Patchwork-Id: 11618079
Return-Path: <SRS0=pCMg=AD=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id C4F2113A0
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 22 Jun 2020 15:00:05 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id A49A42073E
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 22 Jun 2020 15:00:05 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=fail reason="signature verification failed" (2048-bit key)
 header.d=gmail.com header.i=@gmail.com header.b="QdC4ageF"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729439AbgFVPAC (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 22 Jun 2020 11:00:02 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:33518 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1729399AbgFVO75 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 22 Jun 2020 10:59:57 -0400
Received: from mail-wm1-x342.google.com (mail-wm1-x342.google.com
 [IPv6:2a00:1450:4864:20::342])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 407B9C061573;
        Mon, 22 Jun 2020 07:59:57 -0700 (PDT)
Received: by mail-wm1-x342.google.com with SMTP id r9so15190105wmh.2;
        Mon, 22 Jun 2020 07:59:57 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=sender:from:to:cc:subject:date:message-id:mime-version
         :content-transfer-encoding;
        bh=qjSTpOx1f56iFgaO+NU8TyLZb7WbmaX8dzGpT5a8k9c=;
        b=QdC4ageFNjGFqfuJ5zOPmcy0Zek9teeLvjDxiAasLgYKuvtzSjOhecWkqBbc45SJ9W
         VgC46xc3TLSFCXuxzIJc/CTLCt/Vqp1OV+AHKkbsdIUXCK/MnhkGoVfeqJd7111qLDf4
         ZPubLr7Z2ppru/kZd8ZHORwzmTRWUnCbWcT4+9dyn6/oMb6YbK5wOOSQOLENgf5HYGvw
         iN5SYNTaEB3Jzb7+vd4LEffa3YXPgrlydmD9HyibTvpM1kjTZNxOwjV6neUezXy7rh6u
         TQUAy5XENnnGjD3E28ifKViGlJGvXNLQPfjlaKPp4P3hJ6bQl7zLoVULgna/wof1I6Jl
         EhOw==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:sender:from:to:cc:subject:date:message-id
         :mime-version:content-transfer-encoding;
        bh=qjSTpOx1f56iFgaO+NU8TyLZb7WbmaX8dzGpT5a8k9c=;
        b=JwXoPQqNtbLWrT0WNiINfzwbnwtXib0LrwwYlPA5MGyflFfX+MFX4vRNcjHgCoj2A6
         FLlz1kAvB2S7afk4DyFDB1A5frRfkyr3S9bAGIAHNXGV1ZgAzTYj22dBtpfBL0vkP9K1
         CwCP0vKGg8Y5UlnYSM7+UUV5UfcujTadKLJXcXvPj+H2OReNW7gXEyBPVlZapoqJtDJy
         J7nbH2VyXLiAOOH2/jhm/kzCXIngsQ5UR0cIwElq/Q1oIuxbIhkiFblR4HTeCkrrQqt+
         FuhFsGS4hFCSpx2GB0pkZTIy8XeWgKnDdIf1Z/d/3sB77MDIuitTuAend68hmzFj2OpN
         n93w==
X-Gm-Message-State: AOAM532QHZ+E3SYFNIUxa6Ata+amqeMs+gDIvQQ9PwP/wQYb8YmMd8Cj
        bZtNBaTN//9qM2V+QNorvSHFxq28srU=
X-Google-Smtp-Source: 
 ABdhPJwA8xXLcqPBJmCRdS3o9ebWim/QBXgcamtIJm1bEpbBLy5MWC1znFH7T51ioAPZ8Enl5lU4ow==
X-Received: by 2002:a7b:c7d2:: with SMTP id
 z18mr19420099wmk.149.1592837995575;
        Mon, 22 Jun 2020 07:59:55 -0700 (PDT)
Received: from donizetti.redhat.com ([2001:b07:6468:f312:fd64:dd90:5ad5:d2e1])
        by smtp.gmail.com with ESMTPSA id 1sm13135806wmf.0.2020.06.22.07.59.54
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Mon, 22 Jun 2020 07:59:54 -0700 (PDT)
From: Paolo Bonzini <pbonzini@redhat.com>
To: linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Cc: Igor Mammedov <imammedo@redhat.com>
Subject: [PATCH] KVM: LAPIC: ensure APIC map is up to date on concurrent
 update requests
Date: Mon, 22 Jun 2020 16:59:53 +0200
Message-Id: <20200622145953.41931-1-pbonzini@redhat.com>
X-Mailer: git-send-email 2.25.4
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The following race can cause lost map update events:

         cpu1                            cpu2

                                apic_map_dirty = true
  ------------------------------------------------------------
                                kvm_recalculate_apic_map:
                                     pass check
                                         mutex_lock(&kvm->arch.apic_map_lock);
                                         if (!kvm->arch.apic_map_dirty)
                                     and in process of updating map
  -------------------------------------------------------------
    other calls to
       apic_map_dirty = true         might be too late for affected cpu
  -------------------------------------------------------------
                                     apic_map_dirty = false
  -------------------------------------------------------------
    kvm_recalculate_apic_map:
    bail out on
      if (!kvm->arch.apic_map_dirty)

To fix it, record the beginning of an update of the APIC map in
apic_map_dirty.  If another APIC map change switches apic_map_dirty
back to DIRTY, kvm_recalculate_apic_map should not make it CLEAN and
let the other caller go through the slow path.

Reported-by: Igor Mammedov <imammedo@redhat.com>
---
 arch/x86/include/asm/kvm_host.h |  2 +-
 arch/x86/kvm/lapic.c            | 45 +++++++++++++++++++--------------
 2 files changed, 27 insertions(+), 20 deletions(-)

```
#### [PATCH] kvm: lapic: fix broken vcpu hotplug
##### From: Igor Mammedov <imammedo@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Igor Mammedov <imammedo@redhat.com>
X-Patchwork-Id: 11618341
Return-Path: <SRS0=pCMg=AD=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 408AD90
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 22 Jun 2020 16:08:43 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 2852B2076E
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 22 Jun 2020 16:08:43 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="PK+e1cLp"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729604AbgFVQIm (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 22 Jun 2020 12:08:42 -0400
Received: from us-smtp-delivery-1.mimecast.com ([207.211.31.120]:53770 "EHLO
        us-smtp-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org
        with ESMTP id S1726328AbgFVQIl (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 22 Jun 2020 12:08:41 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1592842120;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=oLt4zilRnLpSNkiF0C8oekFwW4sIceZdS9Lxg4NGfQA=;
        b=PK+e1cLpHraM4um6ix+qtFJ1R5QX9DKFempRhpHpyYXR3KGLUAnsLQuQNdMA7Ne2LPWSyN
        gyE2b4xdkfipTppjgTIOrHSbVLhGXuO4NYs0pMQT6uu/PV7/JBOk4+D+0qwF9HUq2aPt/r
        utnGwO+YqUWBGUECrSHv9KM4VNBPwYI=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-327-IPnes8dvMvar_MJTs1dysA-1; Mon, 22 Jun 2020 12:08:35 -0400
X-MC-Unique: IPnes8dvMvar_MJTs1dysA-1
Received: from smtp.corp.redhat.com (int-mx05.intmail.prod.int.phx2.redhat.com
 [10.5.11.15])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 545F5A0BD9;
        Mon, 22 Jun 2020 16:08:33 +0000 (UTC)
Received: from dell-r430-03.lab.eng.brq.redhat.com
 (dell-r430-03.lab.eng.brq.redhat.com [10.37.153.18])
        by smtp.corp.redhat.com (Postfix) with ESMTP id ECEC45BACD;
        Mon, 22 Jun 2020 16:08:31 +0000 (UTC)
From: Igor Mammedov <imammedo@redhat.com>
To: linux-kernel@vger.kernel.org
Cc: pbonzini@redhat.com, sean.j.christopherson@intel.com,
        vkuznets@redhat.com, kvm@vger.kernel.org, wanpengli@tencent.com
Subject: [PATCH] kvm: lapic: fix broken vcpu hotplug
Date: Mon, 22 Jun 2020 12:08:30 -0400
Message-Id: <20200622160830.426022-1-imammedo@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.15
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Guest fails to online hotplugged CPU with error
  smpboot: do_boot_cpu failed(-1) to wakeup CPU#4

It's caused by the fact that kvm_apic_set_state(), which used to call
recalculate_apic_map() unconditionally and pulled hotplugged CPU into
apic map, is updating map conditionally [1] on state change which doesn't
happen in this case and apic map update is skipped.

Note:
new CPU during kvm_arch_vcpu_create() is not visible to
kvm_recalculate_apic_map(), so all related update calls endup
as NOP and only follow up kvm_apic_set_state() used to trigger map
update that counted in hotplugged CPU.
Fix issue by forcing unconditional update from kvm_apic_set_state(),
like it used to be.

1)
Fixes: (4abaffce4d25a KVM: LAPIC: Recalculate apic map in batch)
Signed-off-by: Igor Mammedov <imammedo@redhat.com>
---
PS:
it's alternative to full revert of [1], I've posted earlier
https://www.mail-archive.com/linux-kernel@vger.kernel.org/msg2205600.html
so fii free to pick up whatever is better by now
---
 arch/x86/kvm/lapic.c | 1 +
 1 file changed, 1 insertion(+)

```
#### [PATCH 1/2] KVM: X86: Move ignore_msrs handling upper the stack
##### From: Peter Xu <peterx@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Peter Xu <peterx@redhat.com>
X-Patchwork-Id: 11619255
Return-Path: <SRS0=pCMg=AD=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 004AE6C1
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 22 Jun 2020 22:05:07 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id D85362076E
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 22 Jun 2020 22:05:06 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="HaaSEpFV"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1730942AbgFVWEz (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 22 Jun 2020 18:04:55 -0400
Received: from us-smtp-1.mimecast.com ([205.139.110.61]:31111 "EHLO
        us-smtp-delivery-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S1730794AbgFVWEz (ORCPT
        <rfc822;kvm@vger.kernel.org>); Mon, 22 Jun 2020 18:04:55 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1592863493;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding:
         in-reply-to:in-reply-to:references:references;
        bh=92xlo56NnQbKrNJm5mldzyMce3skYCA3gpK4Ws+GIX4=;
        b=HaaSEpFVYPjsqICjv2RQhacI1wO6GXV7A4y5TBzvlO8359EE52v+keaVMsYd+Ux6sIxhtR
        HLpwcK8QATcCF1XTftfR79weBBqqEGk8OlNoqpwkPF3/9TooVA9WSQg6RiR/7pBPnNSsE0
        FFo+C0sf2+EjjE7+UBEvG1+/OTNRcnM=
Received: from mail-qk1-f198.google.com (mail-qk1-f198.google.com
 [209.85.222.198]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-468-s0HoMUk5Om-LOQzYoBfBvA-1; Mon, 22 Jun 2020 18:04:51 -0400
X-MC-Unique: s0HoMUk5Om-LOQzYoBfBvA-1
Received: by mail-qk1-f198.google.com with SMTP id i6so2684106qkn.22
        for <kvm@vger.kernel.org>; Mon, 22 Jun 2020 15:04:51 -0700 (PDT)
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:in-reply-to
         :references:mime-version:content-transfer-encoding;
        bh=92xlo56NnQbKrNJm5mldzyMce3skYCA3gpK4Ws+GIX4=;
        b=lhF6ujVstpi9KrInMoySDK+5PK3bkKO7uH+9CcVbDDXgzYdmn+w13MOZWb/V6BbT0l
         HiWLB+MNBy1bf2vGoJYn41BfmQ4Csclq6YUnahNFzdtWmeacXg3vVLEUV97jwSFhM92x
         okaZKMjPtqcziBnuuTAtOYaT3gE5yKPKJvHUVGI27LRzrcx+zYpdv6f9m/hrAPUuGWIg
         6xVR3uiO8oXqTVc0sO+tvDiGVRe7ZynOSFqahskkf3nXLkzr6dvV20LvN2f0ilohB4YM
         Yx26dR1G/9tRButLKdK7eHwKMWp0GxTYAJfyQJ4tVqnS9EudZOy9+UWReiQgXuT6RY8c
         H0tA==
X-Gm-Message-State: AOAM530m3XhmzPodlVIst+35RS3G0hF8Q4Dm4aQ16JUAakdo2xx44KkD
        9PceZopvQrFyk+dRM6MbceNkM2KmzFvlVhOTJtVxlLvTvQdYsMRPDiJrKRrM7ERG5lbW7FcfjRp
        IRH4FI6NgKXQ7
X-Received: by 2002:a37:44d5:: with SMTP id
 r204mr7294737qka.113.1592863490935;
        Mon, 22 Jun 2020 15:04:50 -0700 (PDT)
X-Google-Smtp-Source: 
 ABdhPJzwpw9hXXzrRoZ7uBlSGesnncpPEpLsS//WL8KZ5yVPHkbD2TpWTGus3gca62CrS2n80xyqrg==
X-Received: by 2002:a37:44d5:: with SMTP id
 r204mr7294705qka.113.1592863490646;
        Mon, 22 Jun 2020 15:04:50 -0700 (PDT)
Received: from xz-x1.redhat.com ([2607:9880:19c0:32::2])
        by smtp.gmail.com with ESMTPSA id h6sm3506810qtu.2.2020.06.22.15.04.47
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Mon, 22 Jun 2020 15:04:50 -0700 (PDT)
From: Peter Xu <peterx@redhat.com>
To: linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Cc: Sean Christopherson <sean.j.christopherson@intel.com>,
        Paolo Bonzini <pbonzini@redhat.com>, peterx@redhat.com,
        Vitaly Kuznetsov <vkuznets@redhat.com>
Subject: [PATCH 1/2] KVM: X86: Move ignore_msrs handling upper the stack
Date: Mon, 22 Jun 2020 18:04:41 -0400
Message-Id: <20200622220442.21998-2-peterx@redhat.com>
X-Mailer: git-send-email 2.26.2
In-Reply-To: <20200622220442.21998-1-peterx@redhat.com>
References: <20200622220442.21998-1-peterx@redhat.com>
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

MSR accesses can be one of:

  (1) KVM internal access,
  (2) userspace access (e.g., via KVM_SET_MSRS ioctl),
  (3) guest access.

The ignore_msrs was previously handled by kvm_get_msr_common() and
kvm_set_msr_common(), which is the bottom of the msr access stack.  It's
working in most cases, however it could dump unwanted warning messages to dmesg
even if kvm get/set the msrs internally when calling __kvm_set_msr() or
__kvm_get_msr() (e.g. kvm_cpuid()).  Ideally we only want to trap cases (2)
or (3), but not (1) above.

To achieve this, move the ignore_msrs handling upper until the callers of
__kvm_get_msr() and __kvm_set_msr().  To identify the "msr missing" event, a
new return value (KVM_MSR_RET_INVALID==2) is used for that.

Signed-off-by: Peter Xu <peterx@redhat.com>
---
 arch/x86/kvm/x86.c | 80 +++++++++++++++++++++++++++++++---------------
 arch/x86/kvm/x86.h |  2 ++
 2 files changed, 56 insertions(+), 26 deletions(-)

```
#### [PATCH] KVM: x86/mmu: Avoid mixing gpa_t with gfn_t in walk_addr_generic()
##### From: Vitaly Kuznetsov <vkuznets@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Vitaly Kuznetsov <vkuznets@redhat.com>
X-Patchwork-Id: 11618117
Return-Path: <SRS0=pCMg=AD=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id CCEB913B1
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 22 Jun 2020 15:14:50 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id B34C420739
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 22 Jun 2020 15:14:50 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="PndyeTcr"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729296AbgFVPOr (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 22 Jun 2020 11:14:47 -0400
Received: from us-smtp-delivery-1.mimecast.com ([207.211.31.120]:51864 "EHLO
        us-smtp-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org
        with ESMTP id S1729199AbgFVPOq (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 22 Jun 2020 11:14:46 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1592838885;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=NIQCA5ZckTuLuocOtdMBGLUU2Sj+VfxVeRxU4kvLvWg=;
        b=PndyeTcrL8jquNZf4pLLLz3+hxIW6+xKHp7LjOtmNl+LFIASh1SGH+VWnb+cKKa/xDJypT
        b/6w1KVbtiMVQFPnkzsIxGrqEhENIjY63sIcR4qdiwiFB1q0BPNZzbo66QSB5tyhxmzZei
        UOKjKnP6JgHnO3p6dRYRmaKLfozGKjQ=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-19-9ya5N6rCP0iHAeJJWgqevw-1; Mon, 22 Jun 2020 11:14:40 -0400
X-MC-Unique: 9ya5N6rCP0iHAeJJWgqevw-1
Received: from smtp.corp.redhat.com (int-mx02.intmail.prod.int.phx2.redhat.com
 [10.5.11.12])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id E5F3C107ACF6;
        Mon, 22 Jun 2020 15:14:38 +0000 (UTC)
Received: from vitty.brq.redhat.com (unknown [10.40.195.104])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 2551B60BE2;
        Mon, 22 Jun 2020 15:14:36 +0000 (UTC)
From: Vitaly Kuznetsov <vkuznets@redhat.com>
To: kvm@vger.kernel.org
Cc: Paolo Bonzini <pbonzini@redhat.com>,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>, linux-kernel@vger.kernel.org
Subject: [PATCH] KVM: x86/mmu: Avoid mixing gpa_t with gfn_t in
 walk_addr_generic()
Date: Mon, 22 Jun 2020 17:14:35 +0200
Message-Id: <20200622151435.752560-1-vkuznets@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.12
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

translate_gpa() returns a GPA, assigning it to 'real_gfn' seems obviously
wrong. There is no real issue because both 'gpa_t' and 'gfn_t' are u64 and
we don't use the value in 'real_gfn' as a GFN, we do

 real_gfn = gpa_to_gfn(real_gfn);

instead. 'If you see a "buffalo" sign on an elephant's cage, do not trust
your eyes', but let's fix it for good.

No functional change intended.

Signed-off-by: Vitaly Kuznetsov <vkuznets@redhat.com>
---
 arch/x86/kvm/mmu/paging_tmpl.h | 9 +++------
 1 file changed, 3 insertions(+), 6 deletions(-)

```
#### [PATCH] KVM: x86/mmu: Don't put invalid SPs back on the list of active pages
##### From: Sean Christopherson <sean.j.christopherson@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Sean Christopherson <sean.j.christopherson@intel.com>
X-Patchwork-Id: 11618729
Return-Path: <SRS0=pCMg=AD=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 26DC660D
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 22 Jun 2020 19:18:57 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 10FA92075A
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 22 Jun 2020 19:18:56 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728294AbgFVTSy (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 22 Jun 2020 15:18:54 -0400
Received: from mga11.intel.com ([192.55.52.93]:65396 "EHLO mga11.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1728068AbgFVTSx (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 22 Jun 2020 15:18:53 -0400
IronPort-SDR: 
 wrrSBOPmd16Q1WVpsKl6gCnksCDNcI2K4n6bbk+3Sdw9iZXUWzqNpWfF2YEno758VxMJoKNEUg
 AAyyGUgw0egA==
X-IronPort-AV: E=McAfee;i="6000,8403,9660"; a="142104136"
X-IronPort-AV: E=Sophos;i="5.75,268,1589266800";
   d="scan'208";a="142104136"
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from fmsmga006.fm.intel.com ([10.253.24.20])
  by fmsmga102.fm.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 22 Jun 2020 12:18:52 -0700
IronPort-SDR: 
 YVmGmOk4LxL2JOfJJgRpdCtim8lytnwabCI48Si0wsEpZcel5g8mmnT70/lza4l6ki1cS5jCpe
 8nU3TqECXK3w==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.75,268,1589266800";
   d="scan'208";a="478491690"
Received: from sjchrist-coffee.jf.intel.com ([10.54.74.152])
  by fmsmga006.fm.intel.com with ESMTP; 22 Jun 2020 12:18:51 -0700
From: Sean Christopherson <sean.j.christopherson@intel.com>
To: Paolo Bonzini <pbonzini@redhat.com>
Cc: Sean Christopherson <sean.j.christopherson@intel.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org
Subject: [PATCH] KVM: x86/mmu: Don't put invalid SPs back on the list of
 active pages
Date: Mon, 22 Jun 2020 12:18:50 -0700
Message-Id: <20200622191850.8529-1-sean.j.christopherson@intel.com>
X-Mailer: git-send-email 2.26.0
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Delete a shadow page from the invalidation list instead of throwing it
back on the list of active pages when it's a root shadow page with
active users.  Invalid active root pages will be explicitly freed by
mmu_free_root_page() when the root_count hits zero, i.e. they don't need
to be put on the active list to avoid leakage.

Use sp->role.invalid to detect that a shadow page has already been
zapped, i.e. is not on a list.

WARN if an invalid page is encountered when zapping pages, as it should
now be impossible.

Signed-off-by: Sean Christopherson <sean.j.christopherson@intel.com>
---
 arch/x86/kvm/mmu/mmu.c | 18 ++++++++++--------
 1 file changed, 10 insertions(+), 8 deletions(-)

```
#### [PATCH 1/6] KVM: x86/mmu: Move mmu_audit.c and mmutrace.h into the mmu/ sub-directory
##### From: Sean Christopherson <sean.j.christopherson@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Sean Christopherson <sean.j.christopherson@intel.com>
X-Patchwork-Id: 11619085
Return-Path: <SRS0=pCMg=AD=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id A6A8060D
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 22 Jun 2020 20:21:14 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 8BF4820732
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 22 Jun 2020 20:21:14 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1730479AbgFVUVK (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 22 Jun 2020 16:21:10 -0400
Received: from mga07.intel.com ([134.134.136.100]:62017 "EHLO mga07.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1728443AbgFVUUh (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 22 Jun 2020 16:20:37 -0400
IronPort-SDR: 
 l++Z9FGEOun75Bma4YL2fqDjTbkidsGgIqjwxyGG+gFMkhv8npLztpRvT8+JcTqQ99C4Vw7Uf3
 fut/k88NdSjg==
X-IronPort-AV: E=McAfee;i="6000,8403,9660"; a="209057476"
X-IronPort-AV: E=Sophos;i="5.75,268,1589266800";
   d="scan'208";a="209057476"
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from fmsmga006.fm.intel.com ([10.253.24.20])
  by orsmga105.jf.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 22 Jun 2020 13:20:36 -0700
IronPort-SDR: 
 qjf8BmVwwTKKh/NfBlovYCte1uRmUHIAlDQbELvRqqYzpAqCUiCRvslgcuqZ7mrybfQy+OIqW5
 7GhoD3xuUE8Q==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.75,268,1589266800";
   d="scan'208";a="478506318"
Received: from sjchrist-coffee.jf.intel.com ([10.54.74.152])
  by fmsmga006.fm.intel.com with ESMTP; 22 Jun 2020 13:20:36 -0700
From: Sean Christopherson <sean.j.christopherson@intel.com>
To: Paolo Bonzini <pbonzini@redhat.com>
Cc: Sean Christopherson <sean.j.christopherson@intel.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org
Subject: [PATCH 1/6] KVM: x86/mmu: Move mmu_audit.c and mmutrace.h into the
 mmu/ sub-directory
Date: Mon, 22 Jun 2020 13:20:29 -0700
Message-Id: <20200622202034.15093-2-sean.j.christopherson@intel.com>
X-Mailer: git-send-email 2.26.0
In-Reply-To: <20200622202034.15093-1-sean.j.christopherson@intel.com>
References: <20200622202034.15093-1-sean.j.christopherson@intel.com>
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Move mmu_audit.c and mmutrace.h under mmu/ where they belong.

Signed-off-by: Sean Christopherson <sean.j.christopherson@intel.com>
---
 arch/x86/kvm/{ => mmu}/mmu_audit.c | 0
 arch/x86/kvm/{ => mmu}/mmutrace.h  | 2 +-
 2 files changed, 1 insertion(+), 1 deletion(-)
 rename arch/x86/kvm/{ => mmu}/mmu_audit.c (100%)
 rename arch/x86/kvm/{ => mmu}/mmutrace.h (99%)

diff --git a/arch/x86/kvm/mmu_audit.c b/arch/x86/kvm/mmu/mmu_audit.c
similarity index 100%
rename from arch/x86/kvm/mmu_audit.c
rename to arch/x86/kvm/mmu/mmu_audit.c
diff --git a/arch/x86/kvm/mmutrace.h b/arch/x86/kvm/mmu/mmutrace.h
similarity index 99%
rename from arch/x86/kvm/mmutrace.h
```
#### [PATCH 1/4] KVM: nVMX: Plumb L2 GPA through to PML emulation
##### From: Sean Christopherson <sean.j.christopherson@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Sean Christopherson <sean.j.christopherson@intel.com>
X-Patchwork-Id: 11619237
Return-Path: <SRS0=pCMg=AD=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 5657F13B1
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 22 Jun 2020 21:58:39 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 4889520767
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 22 Jun 2020 21:58:39 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1730917AbgFVV6i (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 22 Jun 2020 17:58:38 -0400
Received: from mga11.intel.com ([192.55.52.93]:15498 "EHLO mga11.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1730756AbgFVV6g (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 22 Jun 2020 17:58:36 -0400
IronPort-SDR: 
 aIkEwIzzf17Cim69ChfKJ9Vgt1V+++clzShtOc9NNP12MAqcB3PHK8xcqJgUdJ1C0+8J1M2C1J
 icJNOZgITk5w==
X-IronPort-AV: E=McAfee;i="6000,8403,9660"; a="142148015"
X-IronPort-AV: E=Sophos;i="5.75,268,1589266800";
   d="scan'208";a="142148015"
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from fmsmga004.fm.intel.com ([10.253.24.48])
  by fmsmga102.fm.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 22 Jun 2020 14:58:34 -0700
IronPort-SDR: 
 CAppCz7dXbT4sTVSv+h8HAXnPOaxC+Y+sZTw0KHOjIoygjPGkrEqK/vQlmndC3uPLddFqHGO4+
 6IaMd5IF1uGw==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.75,268,1589266800";
   d="scan'208";a="300987310"
Received: from sjchrist-coffee.jf.intel.com ([10.54.74.152])
  by fmsmga004.fm.intel.com with ESMTP; 22 Jun 2020 14:58:34 -0700
From: Sean Christopherson <sean.j.christopherson@intel.com>
To: Paolo Bonzini <pbonzini@redhat.com>
Cc: Sean Christopherson <sean.j.christopherson@intel.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org
Subject: [PATCH 1/4] KVM: nVMX: Plumb L2 GPA through to PML emulation
Date: Mon, 22 Jun 2020 14:58:29 -0700
Message-Id: <20200622215832.22090-2-sean.j.christopherson@intel.com>
X-Mailer: git-send-email 2.26.0
In-Reply-To: <20200622215832.22090-1-sean.j.christopherson@intel.com>
References: <20200622215832.22090-1-sean.j.christopherson@intel.com>
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Explicitly pass the L2 GPA to kvm_arch_write_log_dirty(), which for all
intents and purposes is vmx_write_pml_buffer(), instead of having the
latter pull the GPA from vmcs.GUEST_PHYSICAL_ADDRESS.  If the dirty bit
update is the result of KVM emulation (rare for L2), then the GPA in the
VMCS may be stale and/or hold a completely unrelated GPA.

Fixes: c5f983f6e8455 ("nVMX: Implement emulated Page Modification Logging")
Cc: stable@vger.kernel.org
Signed-off-by: Sean Christopherson <sean.j.christopherson@intel.com>
---
 arch/x86/include/asm/kvm_host.h | 2 +-
 arch/x86/kvm/mmu.h              | 2 +-
 arch/x86/kvm/mmu/mmu.c          | 4 ++--
 arch/x86/kvm/mmu/paging_tmpl.h  | 7 ++++---
 arch/x86/kvm/vmx/vmx.c          | 6 +++---
 5 files changed, 11 insertions(+), 10 deletions(-)

```
#### [PATCH 01/15] KVM: x86: Rename "shared_msrs" to "user_return_msrs"
##### From: Sean Christopherson <sean.j.christopherson@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Sean Christopherson <sean.j.christopherson@intel.com>
X-Patchwork-Id: 11619329
Return-Path: <SRS0=pCMg=AD=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id A6D0913A0
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 22 Jun 2020 22:45:34 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 9050A2073E
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 22 Jun 2020 22:45:34 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1731589AbgFVWpd (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 22 Jun 2020 18:45:33 -0400
Received: from mga18.intel.com ([134.134.136.126]:27425 "EHLO mga18.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1730785AbgFVWmy (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 22 Jun 2020 18:42:54 -0400
IronPort-SDR: 
 G6SSKvUj6zHHGtv7PjRMcnMXFEy8oKPMkQlbnxl37s19r/DZUdkAxmJ5MdxVV0dT3pqrY9G9Lv
 STxQo3RbZURg==
X-IronPort-AV: E=McAfee;i="6000,8403,9660"; a="131303561"
X-IronPort-AV: E=Sophos;i="5.75,268,1589266800";
   d="scan'208";a="131303561"
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from fmsmga008.fm.intel.com ([10.253.24.58])
  by orsmga106.jf.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 22 Jun 2020 15:42:51 -0700
IronPort-SDR: 
 Dl8zm+EQRZM85TtvD8EIwG92M6HXrFkskY7uvVjO5nZcuTdxX1e49dv9KEePjG6D9bqzoO5tr+
 UhJzx6KWATRw==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.75,268,1589266800";
   d="scan'208";a="264634901"
Received: from sjchrist-coffee.jf.intel.com ([10.54.74.152])
  by fmsmga008.fm.intel.com with ESMTP; 22 Jun 2020 15:42:50 -0700
From: Sean Christopherson <sean.j.christopherson@intel.com>
To: Paolo Bonzini <pbonzini@redhat.com>
Cc: Sean Christopherson <sean.j.christopherson@intel.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org
Subject: [PATCH 01/15] KVM: x86: Rename "shared_msrs" to "user_return_msrs"
Date: Mon, 22 Jun 2020 15:42:35 -0700
Message-Id: <20200622224249.29562-2-sean.j.christopherson@intel.com>
X-Mailer: git-send-email 2.26.0
In-Reply-To: <20200622224249.29562-1-sean.j.christopherson@intel.com>
References: <20200622224249.29562-1-sean.j.christopherson@intel.com>
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Rename the "shared_msrs" mechanism, which is used to defer restoring
MSRs that are only consumed when running in userspace, to a more banal
but less likely to be confusing "user_return_msrs".

The "shared" nomenclature is confusing as it's not obvious who is
sharing what, e.g. reasonable interpretations are that the guest value
is shared by vCPUs in a VM, or that the MSR value is shared/common to
guest and host, both of which are wrong.

"shared" is also misleading as the MSR value (in hardware) is not
guaranteed to be shared/reused between VMs (if that's indeed the correct
interpretation of the name), as the ability to share values between VMs
is simply a side effect (albiet a very nice side effect) of deferring
restoration of the host value until returning from userspace.

"user_return" avoids the above confusion by describing the mechanism
itself instead of its effects.

Signed-off-by: Sean Christopherson <sean.j.christopherson@intel.com>
---
 arch/x86/include/asm/kvm_host.h |   4 +-
 arch/x86/kvm/vmx/vmx.c          |  11 ++--
 arch/x86/kvm/x86.c              | 101 +++++++++++++++++---------------
 3 files changed, 60 insertions(+), 56 deletions(-)

```
#### [kvm-unit-tests PATCH v1 1/8] x86/cstart.S: initialize stack before using it
##### From: Claudio Imbrenda <imbrenda@linux.ibm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Claudio Imbrenda <imbrenda@linux.ibm.com>
X-Patchwork-Id: 11618377
Return-Path: <SRS0=pCMg=AD=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 9FA1A90
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 22 Jun 2020 16:21:55 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 8F33220760
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 22 Jun 2020 16:21:55 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729655AbgFVQVy (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 22 Jun 2020 12:21:54 -0400
Received: from mx0a-001b2d01.pphosted.com ([148.163.156.1]:21496 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1729671AbgFVQVx (ORCPT
        <rfc822;kvm@vger.kernel.org>); Mon, 22 Jun 2020 12:21:53 -0400
Received: from pps.filterd (m0098396.ppops.net [127.0.0.1])
        by mx0a-001b2d01.pphosted.com (8.16.0.42/8.16.0.42) with SMTP id
 05MG4VGB102606
        for <kvm@vger.kernel.org>; Mon, 22 Jun 2020 12:21:53 -0400
Received: from pps.reinject (localhost [127.0.0.1])
        by mx0a-001b2d01.pphosted.com with ESMTP id 31tysp8tfa-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT)
        for <kvm@vger.kernel.org>; Mon, 22 Jun 2020 12:21:52 -0400
Received: from m0098396.ppops.net (m0098396.ppops.net [127.0.0.1])
        by pps.reinject (8.16.0.36/8.16.0.36) with SMTP id 05MGC0iB140491
        for <kvm@vger.kernel.org>; Mon, 22 Jun 2020 12:21:52 -0400
Received: from ppma05fra.de.ibm.com (6c.4a.5195.ip4.static.sl-reverse.com
 [149.81.74.108])
        by mx0a-001b2d01.pphosted.com with ESMTP id 31tysp8te6-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Mon, 22 Jun 2020 12:21:52 -0400
Received: from pps.filterd (ppma05fra.de.ibm.com [127.0.0.1])
        by ppma05fra.de.ibm.com (8.16.0.42/8.16.0.42) with SMTP id
 05MG1BPv029895;
        Mon, 22 Jun 2020 16:21:49 GMT
Received: from b06cxnps3074.portsmouth.uk.ibm.com
 (d06relay09.portsmouth.uk.ibm.com [9.149.109.194])
        by ppma05fra.de.ibm.com with ESMTP id 31sa37seg5-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Mon, 22 Jun 2020 16:21:49 +0000
Received: from d06av21.portsmouth.uk.ibm.com (d06av21.portsmouth.uk.ibm.com
 [9.149.105.232])
        by b06cxnps3074.portsmouth.uk.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id 05MGLggm48824486
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Mon, 22 Jun 2020 16:21:42 GMT
Received: from d06av21.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 270F952052;
        Mon, 22 Jun 2020 16:21:42 +0000 (GMT)
Received: from ibm-vm.ibmuc.com (unknown [9.145.9.197])
        by d06av21.portsmouth.uk.ibm.com (Postfix) with ESMTP id CBAF15205F;
        Mon, 22 Jun 2020 16:21:41 +0000 (GMT)
From: Claudio Imbrenda <imbrenda@linux.ibm.com>
To: kvm@vger.kernel.org, pbonzini@redhat.com
Cc: frankja@linux.ibm.com, thuth@redhat.com, david@redhat.com
Subject: [kvm-unit-tests PATCH v1 1/8] x86/cstart.S: initialize stack before
 using it
Date: Mon, 22 Jun 2020 18:21:34 +0200
Message-Id: <20200622162141.279716-2-imbrenda@linux.ibm.com>
X-Mailer: git-send-email 2.26.2
In-Reply-To: <20200622162141.279716-1-imbrenda@linux.ibm.com>
References: <20200622162141.279716-1-imbrenda@linux.ibm.com>
MIME-Version: 1.0
X-TM-AS-GCONF: 00
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.216,18.0.687
 definitions=2020-06-22_09:2020-06-22,2020-06-22 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 malwarescore=0 spamscore=0
 lowpriorityscore=0 clxscore=1015 cotscore=-2147483648 impostorscore=0
 phishscore=0 mlxlogscore=999 priorityscore=1501 bulkscore=0 suspectscore=0
 adultscore=0 mlxscore=0 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.12.0-2004280000 definitions=main-2006220117
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

It seems the 32-bit initialization code uses the stack before actually
initializing it.

Probably the boot loader leaves a reasonable value in the stack pointer so
this issue has not been noticed before.

Signed-off-by: Claudio Imbrenda <imbrenda@linux.ibm.com>
---
 x86/cstart.S | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
#### [PATCH] Revert "KVM: LAPIC: Recalculate apic map in batch"
##### From: Igor Mammedov <imammedo@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Igor Mammedov <imammedo@redhat.com>
X-Patchwork-Id: 11617571
Return-Path: <SRS0=pCMg=AD=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id F3287913
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 22 Jun 2020 12:08:11 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id CF8A72074D
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 22 Jun 2020 12:08:11 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="WwCCF/Er"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728153AbgFVMIK (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 22 Jun 2020 08:08:10 -0400
Received: from us-smtp-delivery-1.mimecast.com ([205.139.110.120]:60452 "EHLO
        us-smtp-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org
        with ESMTP id S1726889AbgFVMIK (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 22 Jun 2020 08:08:10 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1592827688;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=nnx9W/qLm351r2r0o603cG4pwGJORxcYfoZb+ozOfFI=;
        b=WwCCF/Eri/gsYbYfDLqTjrzqZ0LLKPMa4Ffe2VOFbsvgB21jR89FyGJZ1elj7GmEN53obV
        Bxey1e+Xw1sSlkqSxQVZ9B8e62JZxOTgdSa0kQzednDmh0he53Eg8Y11BRGYXzVDyYOnz0
        jwstkgEKKPbxJBnGIizjXGLxN+bkJaY=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-260-lzU-v-1EO_-5Rk4xIBq9rg-1; Mon, 22 Jun 2020 08:08:06 -0400
X-MC-Unique: lzU-v-1EO_-5Rk4xIBq9rg-1
Received: from smtp.corp.redhat.com (int-mx07.intmail.prod.int.phx2.redhat.com
 [10.5.11.22])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 8AB1E18A8221;
        Mon, 22 Jun 2020 12:08:05 +0000 (UTC)
Received: from dell-r430-03.lab.eng.brq.redhat.com
 (dell-r430-03.lab.eng.brq.redhat.com [10.37.153.18])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 06AD210013D2;
        Mon, 22 Jun 2020 12:08:03 +0000 (UTC)
From: Igor Mammedov <imammedo@redhat.com>
To: linux-kernel@vger.kernel.org
Cc: pbonzini@redhat.com, sean.j.christopherson@intel.com,
        vkuznets@redhat.com, kvm@vger.kernel.org, wanpengli@tencent.com
Subject: [PATCH] Revert "KVM: LAPIC: Recalculate apic map in batch"
Date: Mon, 22 Jun 2020 08:08:02 -0400
Message-Id: <20200622120802.376848-1-imammedo@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.84 on 10.5.11.22
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Guest fails to online hotplugged CPU with error
  smpboot: do_boot_cpu failed(-1) to wakeup CPU#4

It's caused by the fact that kvm_apic_set_state(), which used to call
recalculate_apic_map() unconditionally and pulled hotplugged CPU into
apic map, is updating map conditionally on state change which doesn't
happen in this case and apic map update is skipped.

Also subj commit introduces a race which can make apic map update
events loss, in case one CPU is already in process of updating
apic map and another CPU flags map as dirty asking for another
update. But the first CPU will clear update request set by another
CPU when update in progress is finished.

  CPU1 kvm_recalculate_apic_map()
     .. updating
  CPU2 apic_map_dirty = true
  CPU1 apic_map_dirty = false
  CPU2 kvm_recalculate_apic_map()
         nop due to apic_map_dirty == false

This reverts commit 4abaffce4d25aa41392d2e81835592726d757857.

Signed-off-by: Igor Mammedov <imammedo@redhat.com>
---
 arch/x86/include/asm/kvm_host.h |  1 -
 arch/x86/kvm/lapic.h            |  1 -
 arch/x86/kvm/lapic.c            | 46 +++++++--------------------------
 arch/x86/kvm/x86.c              |  1 -
 4 files changed, 10 insertions(+), 39 deletions(-)

```
#### [PATCH] SVM: add test for nested guest RIP corruption
##### From: Maxim Levitsky <mlevitsk@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Maxim Levitsky <mlevitsk@redhat.com>
X-Patchwork-Id: 11618459
Return-Path: <SRS0=pCMg=AD=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 1134E618
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 22 Jun 2020 16:55:41 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id EDB2220767
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 22 Jun 2020 16:55:40 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="Pa1yS9Mu"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729886AbgFVQzj (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 22 Jun 2020 12:55:39 -0400
Received: from us-smtp-2.mimecast.com ([205.139.110.61]:50367 "EHLO
        us-smtp-delivery-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S1729533AbgFVQzj (ORCPT
        <rfc822;kvm@vger.kernel.org>); Mon, 22 Jun 2020 12:55:39 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1592844938;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=JPZ1oZkRtOQHIXgR2lWhqUAok6RlbzPjapkz8FfXuXo=;
        b=Pa1yS9MubgLXT3aBU4ahlIOPEs5GRF9HQk5ZTL7KfShsmq9e8UZ8MmaqaanGPROZ/Y47XS
        TW6wMOYfI43DRe2O7wjereleXZAjlFDSvyhaOChH0Tr7nwjm1pUyJ+vCJmKQ7tZWUUok9I
        dJK+65jOJR5uSQBA42w8cLsWhecIgW4=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-294-LZWDzJnCNFGp9rbcX0ZcuQ-1; Mon, 22 Jun 2020 12:55:36 -0400
X-MC-Unique: LZWDzJnCNFGp9rbcX0ZcuQ-1
Received: from smtp.corp.redhat.com (int-mx06.intmail.prod.int.phx2.redhat.com
 [10.5.11.16])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id A742118FE861
        for <kvm@vger.kernel.org>; Mon, 22 Jun 2020 16:55:35 +0000 (UTC)
Received: from starship.redhat.com (unknown [10.35.206.247])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 5E8FF5C1BD;
        Mon, 22 Jun 2020 16:55:34 +0000 (UTC)
From: Maxim Levitsky <mlevitsk@redhat.com>
To: kvm@vger.kernel.org
Cc: Paolo Bonzini <pbonzini@redhat.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Maxim Levitsky <mlevitsk@redhat.com>
Subject: [PATCH] SVM: add test for nested guest RIP corruption
Date: Mon, 22 Jun 2020 19:55:33 +0300
Message-Id: <20200622165533.145882-1-mlevitsk@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.16
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This adds a unit test for SVM nested register corruption that happened when
L0 was emulating an instruction, but then injecting an interrupt intercept to L1, which
lead it to give L1 vmexit handler stale (pre emulation) values of RAX,RIP and RSP.

This test detects the RIP corruption (situation when RIP is at the start of
the emulated instruction but the instruction, was already executed.

The upstream commit that fixed this bug is b6162e82aef19fee9c32cb3fe9ac30d9116a8c73
  KVM: nSVM: Preserve registers modifications done before nested_svm_vmexit()

Signed-off-by: Maxim Levitsky <mlevitsk@redhat.com>
---
 x86/svm_tests.c | 103 ++++++++++++++++++++++++++++++++++++++++++++++++
 1 file changed, 103 insertions(+)

```
#### [PATCH v9 1/2] s390/setup: diag 318: refactor struct
##### From: Collin Walling <walling@linux.ibm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Collin Walling <walling@linux.ibm.com>
X-Patchwork-Id: 11618303
Return-Path: <SRS0=pCMg=AD=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id D4C6D14B7
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 22 Jun 2020 15:46:54 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id C401620760
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 22 Jun 2020 15:46:54 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729482AbgFVPqy (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 22 Jun 2020 11:46:54 -0400
Received: from mx0a-001b2d01.pphosted.com ([148.163.156.1]:3486 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1729259AbgFVPqx (ORCPT
        <rfc822;kvm@vger.kernel.org>); Mon, 22 Jun 2020 11:46:53 -0400
Received: from pps.filterd (m0098409.ppops.net [127.0.0.1])
        by mx0a-001b2d01.pphosted.com (8.16.0.42/8.16.0.42) with SMTP id
 05MFWgLB145080;
        Mon, 22 Jun 2020 11:46:52 -0400
Received: from pps.reinject (localhost [127.0.0.1])
        by mx0a-001b2d01.pphosted.com with ESMTP id 31swph5bn1-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Mon, 22 Jun 2020 11:46:52 -0400
Received: from m0098409.ppops.net (m0098409.ppops.net [127.0.0.1])
        by pps.reinject (8.16.0.36/8.16.0.36) with SMTP id 05MFXGul148014;
        Mon, 22 Jun 2020 11:46:52 -0400
Received: from ppma03wdc.us.ibm.com (ba.79.3fa9.ip4.static.sl-reverse.com
 [169.63.121.186])
        by mx0a-001b2d01.pphosted.com with ESMTP id 31swph5bmp-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Mon, 22 Jun 2020 11:46:52 -0400
Received: from pps.filterd (ppma03wdc.us.ibm.com [127.0.0.1])
        by ppma03wdc.us.ibm.com (8.16.0.42/8.16.0.42) with SMTP id
 05MFa7QB001574;
        Mon, 22 Jun 2020 15:46:50 GMT
Received: from b03cxnp08025.gho.boulder.ibm.com
 (b03cxnp08025.gho.boulder.ibm.com [9.17.130.17])
        by ppma03wdc.us.ibm.com with ESMTP id 31sa388nqe-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Mon, 22 Jun 2020 15:46:50 +0000
Received: from b03ledav002.gho.boulder.ibm.com
 (b03ledav002.gho.boulder.ibm.com [9.17.130.233])
        by b03cxnp08025.gho.boulder.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id 05MFkkR216843112
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Mon, 22 Jun 2020 15:46:46 GMT
Received: from b03ledav002.gho.boulder.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 4203013604F;
        Mon, 22 Jun 2020 15:46:47 +0000 (GMT)
Received: from b03ledav002.gho.boulder.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 69C66136055;
        Mon, 22 Jun 2020 15:46:46 +0000 (GMT)
Received: from localhost.localdomain.com (unknown [9.85.169.243])
        by b03ledav002.gho.boulder.ibm.com (Postfix) with ESMTP;
        Mon, 22 Jun 2020 15:46:46 +0000 (GMT)
From: Collin Walling <walling@linux.ibm.com>
To: kvm@vger.kernel.org, linux-s390@vger.kernel.org
Cc: pbonzini@redhat.com, borntraeger@de.ibm.com, frankja@linux.ibm.com,
        david@redhat.com, cohuck@redhat.com, imbrenda@linux.ibm.com,
        heiko.carstens@de.ibm.com, gor@linux.ibm.com, thuth@redhat.com
Subject: [PATCH v9 1/2] s390/setup: diag 318: refactor struct
Date: Mon, 22 Jun 2020 11:46:35 -0400
Message-Id: <20200622154636.5499-2-walling@linux.ibm.com>
X-Mailer: git-send-email 2.26.2
In-Reply-To: <20200622154636.5499-1-walling@linux.ibm.com>
References: <20200622154636.5499-1-walling@linux.ibm.com>
MIME-Version: 1.0
X-TM-AS-GCONF: 00
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.216,18.0.687
 definitions=2020-06-22_08:2020-06-22,2020-06-22 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 mlxscore=0 suspectscore=0
 spamscore=0 phishscore=0 impostorscore=0 mlxlogscore=999
 lowpriorityscore=0 bulkscore=0 clxscore=1015 malwarescore=0 adultscore=0
 priorityscore=1501 cotscore=-2147483648 classifier=spam adjust=0
 reason=mlx scancount=1 engine=8.12.0-2004280000
 definitions=main-2006220114
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The diag 318 struct introduced in include/asm/diag.h can be
reused in KVM, so let's condense the version code fields in the
diag318_info struct for easier usage and simplify it until we
can determine how the data should be formatted.

Signed-off-by: Collin Walling <walling@linux.ibm.com>
Reviewed-by: David Hildenbrand <david@redhat.com>
Reviewed-by: Cornelia Huck <cohuck@redhat.com>
Reviewed-by: Thomas Huth <thuth@redhat.com>
Reviewed-by: Janosch Frank <frankja@linux.ibm.com>
---
 arch/s390/include/asm/diag.h | 6 ++----
 arch/s390/kernel/setup.c     | 3 +--
 2 files changed, 3 insertions(+), 6 deletions(-)

```
#### [PATCH] vfio/type1: Add conditional rescheduling after iommu map failed
##### From: Xiang Zheng <zhengxiang9@huawei.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Xiang Zheng <zhengxiang9@huawei.com>
X-Patchwork-Id: 11617025
Return-Path: <SRS0=pCMg=AD=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id DA41C138C
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 22 Jun 2020 07:07:33 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id CCA2B248FF
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 22 Jun 2020 07:07:33 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1731319AbgFVHHb (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 22 Jun 2020 03:07:31 -0400
Received: from szxga04-in.huawei.com ([45.249.212.190]:6381 "EHLO huawei.com"
        rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org with ESMTP
        id S1731258AbgFVHHb (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 22 Jun 2020 03:07:31 -0400
Received: from DGGEMS402-HUB.china.huawei.com (unknown [172.30.72.58])
        by Forcepoint Email with ESMTP id 9387677F378764EFCB63;
        Mon, 22 Jun 2020 15:07:28 +0800 (CST)
Received: from DESKTOP-J8O3A6U.china.huawei.com (10.173.221.213) by
 DGGEMS402-HUB.china.huawei.com (10.3.19.202) with Microsoft SMTP Server id
 14.3.487.0; Mon, 22 Jun 2020 15:07:22 +0800
From: Xiang Zheng <zhengxiang9@huawei.com>
To: <kvm@vger.kernel.org>, <linux-kernel@vger.kernel.org>
CC: <alex.williamson@redhat.com>, <cohuck@redhat.com>,
        <wanghaibin.wang@huawei.com>
Subject: [PATCH] vfio/type1: Add conditional rescheduling after iommu map
 failed
Date: Mon, 22 Jun 2020 15:02:17 +0800
Message-ID: <20200622070217.4768-1-zhengxiang9@huawei.com>
X-Mailer: git-send-email 2.15.1.windows.2
MIME-Version: 1.0
X-Originating-IP: [10.173.221.213]
X-CFilter-Loop: Reflected
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

c5e6688752c25 ("vfio/type1: Add conditional rescheduling") missed
a "cond_resched()" in vfio_iommu_map if iommu map failed.

This is a very tiny optimization and the case can hardly happen.

Signed-off-by: Xiang Zheng <zhengxiang9@huawei.com>
---
 drivers/vfio/vfio_iommu_type1.c | 4 +++-
 1 file changed, 3 insertions(+), 1 deletion(-)

```
