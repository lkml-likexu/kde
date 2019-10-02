#### [PATCH 1/4] arm64: KVM: Drop hyp_alternate_select for checking for ARM64_WORKAROUND_834220
##### From: Marc Zyngier <maz@kernel.org>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Marc Zyngier <maz@kernel.org>
X-Patchwork-Id: 11168327
Return-Path: <SRS0=7VF/=X2=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 49DB41599
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue,  1 Oct 2019 09:21:16 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 1DCC721927
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue,  1 Oct 2019 09:21:16 +0000 (UTC)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple; d=kernel.org;
	s=default; t=1569921676;
	bh=5mQA8NV7WVrW/SENkldsXs9O2vstxhQifxg90ihOBVA=;
	h=From:To:Cc:Subject:Date:In-Reply-To:References:List-ID:From;
	b=RD83zGOBjFk58kigz7lzVmRJbNUuG8h1FvX44uxSGIJnsj5u4L9iX7ufczWvpXiqc
	 BtxI5unfPpDuNUwuMYyIwZppaBqeNMUuHaZJPWX4QblbJMlczd3Wxdacl35r/MKYah
	 7+0xGFQjJUtDqJA3BHWfyuxTv5K/nJzYZhPYEmvA=
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2387558AbfJAJVM (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 1 Oct 2019 05:21:12 -0400
Received: from inca-roads.misterjones.org ([213.251.177.50]:55261 "EHLO
        inca-roads.misterjones.org" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S2387487AbfJAJVM (ORCPT
        <rfc822;kvm@vger.kernel.org>); Tue, 1 Oct 2019 05:21:12 -0400
Received: from 78.163-31-62.static.virginmediabusiness.co.uk ([62.31.163.78]
 helo=why.lan)
        by cheepnis.misterjones.org with esmtpsa
 (TLSv1.2:DHE-RSA-AES128-GCM-SHA256:128)
        (Exim 4.80)
        (envelope-from <maz@kernel.org>)
        id 1iFEL5-00019A-Lt; Tue, 01 Oct 2019 11:20:59 +0200
From: Marc Zyngier <maz@kernel.org>
To: Paolo Bonzini <pbonzini@redhat.com>,
 =?utf-8?b?UmFkaW0gS3LEjW3DocWZ?= <rkrcmar@redhat.com>
Cc: Andrew Jones <drjones@redhat.com>,
        Christoffer Dall <christoffer.dall@arm.com>,
        Masahiro Yamada <yamada.masahiro@socionext.com>,
        Zenghui Yu <yuzenghui@huawei.com>,
        James Morse <james.morse@arm.com>,
        Julien Thierry <julien.thierry.kdev@gmail.com>,
        Suzuki K Poulose <suzuki.poulose@arm.com>,
        linux-arm-kernel@lists.infradead.org, kvmarm@lists.cs.columbia.edu,
        kvm@vger.kernel.org
Subject: [PATCH 1/4] arm64: KVM: Drop hyp_alternate_select for checking for
 ARM64_WORKAROUND_834220
Date: Tue,  1 Oct 2019 10:20:35 +0100
Message-Id: <20191001092038.17097-2-maz@kernel.org>
X-Mailer: git-send-email 2.20.1
In-Reply-To: <20191001092038.17097-1-maz@kernel.org>
References: <20191001092038.17097-1-maz@kernel.org>
MIME-Version: 1.0
X-SA-Exim-Connect-IP: 62.31.163.78
X-SA-Exim-Rcpt-To: pbonzini@redhat.com, rkrcmar@redhat.com,
 drjones@redhat.com, christoffer.dall@arm.com, yamada.masahiro@socionext.com,
 yuzenghui@huawei.com, james.morse@arm.com, julien.thierry.kdev@gmail.com,
 suzuki.poulose@arm.com, linux-arm-kernel@lists.infradead.org,
 kvmarm@lists.cs.columbia.edu, kvm@vger.kernel.org
X-SA-Exim-Mail-From: maz@kernel.org
X-SA-Exim-Scanned: No (on cheepnis.misterjones.org);
 SAEximRunCond expanded to false
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

There is no reason for using hyp_alternate_select when checking
for ARM64_WORKAROUND_834220, as each of the capabilities is
also backed by a static key. Just replace the KVM-specific
construct with cpus_have_const_cap(ARM64_WORKAROUND_834220).

Signed-off-by: Marc Zyngier <maz@kernel.org>
Reviewed-by: Christoffer Dall <christoffer.dall@arm.com>
Reviewed-by: Andrew Jones <drjones@redhat.com>
---
 arch/arm64/kvm/hyp/switch.c | 17 ++---------------
 1 file changed, 2 insertions(+), 15 deletions(-)

```
#### [PATCH v11 QEMU 2/3] virtio-balloon: Add bit to notify guest of unused page reporting
##### From: Alexander Duyck <alexander.duyck@gmail.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Alexander Duyck <alexander.duyck@gmail.com>
X-Patchwork-Id: 11169081
Return-Path: <SRS0=7VF/=X2=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 03CB617EE
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue,  1 Oct 2019 15:31:17 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id D6DB620842
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue,  1 Oct 2019 15:31:16 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=gmail.com header.i=@gmail.com
 header.b="L5Twh0Jh"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2389747AbfJAPbO (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 1 Oct 2019 11:31:14 -0400
Received: from mail-pl1-f193.google.com ([209.85.214.193]:42884 "EHLO
        mail-pl1-f193.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S2389674AbfJAPbN (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 1 Oct 2019 11:31:13 -0400
Received: by mail-pl1-f193.google.com with SMTP id e5so5644384pls.9;
        Tue, 01 Oct 2019 08:31:13 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=subject:from:to:cc:date:message-id:in-reply-to:references
         :user-agent:mime-version:content-transfer-encoding;
        bh=VitjQQFQG7H0A5JYqbYhHy/YWDiYO6QESupJyX3H62U=;
        b=L5Twh0JhZGvdhXHXw1oaxNXeSNQCxXg+4kR8o8X1F1TzlD00uzAO3QGcQGeCH+pYyv
         eM9UzTiOoj4NhZ/y/SfE4biRkKz0cfZib7gcIwCdBqTO0mnj3MDDRzQ0MbZPocBM+B5h
         msJsxIMWdqcGBjoeyS0PE3+F5FIPQogg6c3lfPb8yAknZ2IT7jOdFrlCQjYDtCtMWPhl
         4w7vbAU55orIiWGUYtYwdGgYBtWzc+mw27eRVFrAhrP6HZJdSIZmDr6LwANpN6U01hfj
         YkPCSsjAhoW6bmeFIjD638fXGmLVvvBI8kOBrNNBTD3nuHzYxjT+4gohPDBQIy3H/4oR
         +rjQ==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:subject:from:to:cc:date:message-id:in-reply-to
         :references:user-agent:mime-version:content-transfer-encoding;
        bh=VitjQQFQG7H0A5JYqbYhHy/YWDiYO6QESupJyX3H62U=;
        b=YcLd3FoBytgdAicc+ykwfb7UF37KZbW/O59GoKaRaWRd0K9k0+CL9yulgUlI5Xkgbo
         hb7Cotdu9uRGIK/4bu4XJkDWDuGft1GJTdMnZyNT9K4ijwMWih3dLpqTpaCVwUGkNPhe
         /4X5ntUzuHlFNY3CLMWqhbg0eBVj4NdwAZeDpULbvpUpyJXQvpfB7z7fJDu0rawUJdhd
         sgKEW1onvXI0CUV7MHbAGEzmOUu7ePf5sPQ0AmDUmPeDqaNMXeQbP0g4FQBY8K9WvNpa
         e181soijUx+yY/GcrV47a+vAnOu7QkfeuEV1BoZU7BpEpsqEywX7FZfi9rXpEMxR5gtf
         H+uw==
X-Gm-Message-State: APjAAAUGsbCAWkhWx4FRqbREMd5y0EoVasIgjfG4mP0lQXg0chjOL7EG
        lOTkGpgNGG7xCTsQHxxJ7bg=
X-Google-Smtp-Source: 
 APXvYqzm4jBxzqNzEFwRHGBmE42pgOuyceYI3OqLlxS3hh8mqGpCUV/zK2gp1R2fYuXU9RD1oRP5gw==
X-Received: by 2002:a17:902:82c8:: with SMTP id
 u8mr16796422plz.38.1569943872768;
        Tue, 01 Oct 2019 08:31:12 -0700 (PDT)
Received: from localhost.localdomain ([2001:470:b:9c3:9e5c:8eff:fe4f:f2d0])
        by smtp.gmail.com with ESMTPSA id
 c8sm20343042pga.42.2019.10.01.08.31.11
        (version=TLS1_2 cipher=ECDHE-RSA-AES128-GCM-SHA256 bits=128/128);
        Tue, 01 Oct 2019 08:31:12 -0700 (PDT)
Subject: [PATCH v11 QEMU 2/3] virtio-balloon: Add bit to notify guest of
 unused page reporting
From: Alexander Duyck <alexander.duyck@gmail.com>
To: virtio-dev@lists.oasis-open.org, kvm@vger.kernel.org,
        mst@redhat.com, david@redhat.com, dave.hansen@intel.com,
        linux-kernel@vger.kernel.org, willy@infradead.org,
        mhocko@kernel.org, linux-mm@kvack.org, akpm@linux-foundation.org,
        mgorman@techsingularity.net, vbabka@suse.cz, osalvador@suse.de
Cc: yang.zhang.wz@gmail.com, pagupta@redhat.com,
        konrad.wilk@oracle.com, nitesh@redhat.com, riel@surriel.com,
        lcapitulino@redhat.com, wei.w.wang@intel.com, aarcange@redhat.com,
        pbonzini@redhat.com, dan.j.williams@intel.com,
        alexander.h.duyck@linux.intel.com
Date: Tue, 01 Oct 2019 08:31:10 -0700
Message-ID: <20191001153110.4422.81414.stgit@localhost.localdomain>
In-Reply-To: <20191001152441.27008.99285.stgit@localhost.localdomain>
References: <20191001152441.27008.99285.stgit@localhost.localdomain>
User-Agent: StGit/0.17.1-dirty
MIME-Version: 1.0
Content-Type: text/plain; charset="utf-8"
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Alexander Duyck <alexander.h.duyck@linux.intel.com>

Add a bit for the page reporting feature provided by virtio-balloon.

This patch should be replaced once the feature is added to the Linux kernel
and the bit is backported into this exported kernel header.

Signed-off-by: Alexander Duyck <alexander.h.duyck@linux.intel.com>
---
 include/standard-headers/linux/virtio_balloon.h |    1 +
 1 file changed, 1 insertion(+)

```
#### [PATCH v11 QEMU 3/3] virtio-balloon: Provide a interface for unused page reporting
##### From: Alexander Duyck <alexander.duyck@gmail.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Alexander Duyck <alexander.duyck@gmail.com>
X-Patchwork-Id: 11169085
Return-Path: <SRS0=7VF/=X2=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 750DD15AB
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue,  1 Oct 2019 15:31:24 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 4866320842
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue,  1 Oct 2019 15:31:24 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=gmail.com header.i=@gmail.com
 header.b="fFf/s9L/"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2389763AbfJAPbU (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 1 Oct 2019 11:31:20 -0400
Received: from mail-pg1-f195.google.com ([209.85.215.195]:37639 "EHLO
        mail-pg1-f195.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S2389757AbfJAPbU (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 1 Oct 2019 11:31:20 -0400
Received: by mail-pg1-f195.google.com with SMTP id c17so9907520pgg.4;
        Tue, 01 Oct 2019 08:31:19 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=subject:from:to:cc:date:message-id:in-reply-to:references
         :user-agent:mime-version:content-transfer-encoding;
        bh=IYnIZF3ya8GRMyw0Z8v44wRFjachYcZ/Qaw0Oz7Yqys=;
        b=fFf/s9L/WVB7bjmw9fJPe2WCP680R1hAwuz1EqtrpqaGDESC6QFN2j2SXFOiAJg48C
         QnQhC/HuBLM4hw4d4aGJ9GMH+NahcRJzzAfWlDiQem/OQ6HTAv0fMd1BeY9U1lQ/GSge
         Me1yyZXkd7tOvHMyE79qhoufjm0W3V9RiZ4BajjbmZ2I7jx0AgLfZwuHR98ZhjI1xS6x
         6wKWChettN4aTn+SOWX6b2RqdJSknjPHojz6q/AqeS0Emtu4rXj02fEx4X7/r9KZk0nq
         V6As+NbPDdINtRfRk95OxlyONVc8iPdBVtjmmXBl4YE4jeGWo7lhRl42+2ZHCEmSq6KA
         HTuQ==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:subject:from:to:cc:date:message-id:in-reply-to
         :references:user-agent:mime-version:content-transfer-encoding;
        bh=IYnIZF3ya8GRMyw0Z8v44wRFjachYcZ/Qaw0Oz7Yqys=;
        b=SkC7AUxdxsQD+cbFSx+lt9Gnosm3Y++WaJTeX67LnL3xnVgk4NU6+NZCkOsdszXa7k
         29Q3B2+9gW4+ssakpxbw77ltzWST2qa7ud9fY+cykjtVwVrcabq2U1Op1YW+WitN0wny
         2rv+P+OcLAiW/aVlrY2u/bNQMub1tk0PTvODhwHg2vBFB0zj6/3ba2P/quSNF6RXyl0H
         Ss10BcSyerV2tcTBDYQHJPufU7R/da7YeitAKBc3ZOuj1+2/F0L6rVEOT1gGo8RxthSz
         3pFZfbS4QYl/tCv28iNDOrA7ugqFHyDT+3GBF2T6gWi8G/3DQa6IPnVRV1KiTHOpw8jz
         XUTQ==
X-Gm-Message-State: APjAAAXmBbBk85aDXDfxC2EE1K9PLKVTLhzhVCOmyuHcF31BKkJBfVzD
        1qQPP3It48Ga6hxdhw60dIs=
X-Google-Smtp-Source: 
 APXvYqyJ7G21Slmmp/tSoYHHg2Wj1SXXe+iZkfjyVs/U7WtIKdIWA4ZHjBpG89+YrZqmxqOcv//CQQ==
X-Received: by 2002:a62:d152:: with SMTP id t18mr4342674pfl.259.1569943879123;
        Tue, 01 Oct 2019 08:31:19 -0700 (PDT)
Received: from localhost.localdomain ([2001:470:b:9c3:9e5c:8eff:fe4f:f2d0])
        by smtp.gmail.com with ESMTPSA id
 2sm16384053pfo.91.2019.10.01.08.31.18
        (version=TLS1_2 cipher=ECDHE-RSA-AES128-GCM-SHA256 bits=128/128);
        Tue, 01 Oct 2019 08:31:18 -0700 (PDT)
Subject: [PATCH v11 QEMU 3/3] virtio-balloon: Provide a interface for unused
 page reporting
From: Alexander Duyck <alexander.duyck@gmail.com>
To: virtio-dev@lists.oasis-open.org, kvm@vger.kernel.org,
        mst@redhat.com, david@redhat.com, dave.hansen@intel.com,
        linux-kernel@vger.kernel.org, willy@infradead.org,
        mhocko@kernel.org, linux-mm@kvack.org, akpm@linux-foundation.org,
        mgorman@techsingularity.net, vbabka@suse.cz, osalvador@suse.de
Cc: yang.zhang.wz@gmail.com, pagupta@redhat.com,
        konrad.wilk@oracle.com, nitesh@redhat.com, riel@surriel.com,
        lcapitulino@redhat.com, wei.w.wang@intel.com, aarcange@redhat.com,
        pbonzini@redhat.com, dan.j.williams@intel.com,
        alexander.h.duyck@linux.intel.com
Date: Tue, 01 Oct 2019 08:31:17 -0700
Message-ID: <20191001153117.4422.30512.stgit@localhost.localdomain>
In-Reply-To: <20191001152441.27008.99285.stgit@localhost.localdomain>
References: <20191001152441.27008.99285.stgit@localhost.localdomain>
User-Agent: StGit/0.17.1-dirty
MIME-Version: 1.0
Content-Type: text/plain; charset="utf-8"
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Alexander Duyck <alexander.h.duyck@linux.intel.com>

Add support for what I am referring to as "unused page reporting".
Basically the idea is to function very similar to how the balloon works
in that we basically end up madvising the page as not being used. However
we don't really need to bother with any deflate type logic since the page
will be faulted back into the guest when it is read or written to.

This is meant to be a simplification of the existing balloon interface
to use for providing hints to what memory needs to be freed. I am assuming
this is safe to do as the deflate logic does not actually appear to do very
much other than tracking what subpages have been released and which ones
haven't.

Signed-off-by: Alexander Duyck <alexander.h.duyck@linux.intel.com>
---
 hw/virtio/virtio-balloon.c         |   46 ++++++++++++++++++++++++++++++++++--
 include/hw/virtio/virtio-balloon.h |    2 +-
 2 files changed, 45 insertions(+), 3 deletions(-)

```
#### [kvm-unit-tests RFC PATCH v2 01/19] lib: arm/arm64: Remove unused CPU_OFF parameter
##### From: Alexandru Elisei <alexandru.elisei@arm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Alexandru Elisei <alexandru.elisei@arm.com>
X-Patchwork-Id: 11168399
Return-Path: <SRS0=7VF/=X2=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id CA6AD16B1
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue,  1 Oct 2019 10:23:40 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id A81D921A4A
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue,  1 Oct 2019 10:23:40 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729675AbfJAKXj (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 1 Oct 2019 06:23:39 -0400
Received: from foss.arm.com ([217.140.110.172]:45848 "EHLO foss.arm.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726190AbfJAKXj (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 1 Oct 2019 06:23:39 -0400
Received: from usa-sjc-imap-foss1.foss.arm.com (unknown [10.121.207.14])
        by usa-sjc-mx-foss1.foss.arm.com (Postfix) with ESMTP id 5EC651570;
        Tue,  1 Oct 2019 03:23:39 -0700 (PDT)
Received: from e123195-lin.cambridge.arm.com (e123195-lin.cambridge.arm.com
 [10.1.196.63])
        by usa-sjc-imap-foss1.foss.arm.com (Postfix) with ESMTPA id
 191BD3F739;
        Tue,  1 Oct 2019 03:23:37 -0700 (PDT)
From: Alexandru Elisei <alexandru.elisei@arm.com>
To: kvm@vger.kernel.org, kvmarm@lists.cs.columbia.edu
Cc: drjones@redhat.com, pbonzini@redhat.com, rkrcmar@redhat.com,
        maz@kernel.org, vladimir.murzin@arm.com, andre.przywara@arm.com,
        mark.rutland@arm.com
Subject: [kvm-unit-tests RFC PATCH v2 01/19] lib: arm/arm64: Remove unused
 CPU_OFF parameter
Date: Tue,  1 Oct 2019 11:23:05 +0100
Message-Id: <20191001102323.27628-2-alexandru.elisei@arm.com>
X-Mailer: git-send-email 2.20.1
In-Reply-To: <20191001102323.27628-1-alexandru.elisei@arm.com>
References: <20191001102323.27628-1-alexandru.elisei@arm.com>
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The first version of PSCI required an argument for CPU_OFF, the power_state
argument, which was removed in version 0.2 of the specification [1].
kvm-unit-tests supports PSCI 0.2, and KVM ignores any CPU_OFF parameters,
so let's remove the PSCI_POWER_STATE_TYPE_POWER_DOWN parameter.

[1] ARM DEN 0022D, section 7.3.

Signed-off-by: Alexandru Elisei <alexandru.elisei@arm.com>
---
 lib/arm/psci.c | 4 +---
 1 file changed, 1 insertion(+), 3 deletions(-)

```
#### [PATCH] KVM: nVMX: Fix consistency check on injected exception error code
##### From: Sean Christopherson <sean.j.christopherson@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Sean Christopherson <sean.j.christopherson@intel.com>
X-Patchwork-Id: 11169245
Return-Path: <SRS0=7VF/=X2=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id CE9B61599
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue,  1 Oct 2019 16:21:29 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id B65C1222CB
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue,  1 Oct 2019 16:21:29 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2389916AbfJAQVZ (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 1 Oct 2019 12:21:25 -0400
Received: from mga17.intel.com ([192.55.52.151]:54870 "EHLO mga17.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S2389776AbfJAQVZ (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 1 Oct 2019 12:21:25 -0400
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from fmsmga002.fm.intel.com ([10.253.24.26])
  by fmsmga107.fm.intel.com with ESMTP/TLS/DHE-RSA-AES256-GCM-SHA384;
 01 Oct 2019 09:21:24 -0700
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.64,571,1559545200";
   d="scan'208";a="221059554"
Received: from sjchrist-coffee.jf.intel.com ([10.54.74.41])
  by fmsmga002.fm.intel.com with ESMTP; 01 Oct 2019 09:21:24 -0700
From: Sean Christopherson <sean.j.christopherson@intel.com>
To: Paolo Bonzini <pbonzini@redhat.com>,
 =?utf-8?b?UmFkaW0gS3LEjW3DocWZ?= <rkrcmar@redhat.com>
Cc: Sean Christopherson <sean.j.christopherson@intel.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org, Nadav Amit <nadav.amit@gmail.com>
Subject: [PATCH] KVM: nVMX: Fix consistency check on injected exception error
 code
Date: Tue,  1 Oct 2019 09:21:23 -0700
Message-Id: <20191001162123.26992-1-sean.j.christopherson@intel.com>
X-Mailer: git-send-email 2.22.0
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Current versions of Intel's SDM incorrectly state that "bits 31:15 of
the VM-Entry exception error-code field" must be zero.  In reality, bits
31:16 must be zero, i.e. error codes are 16-bit values.

The bogus error code check manifests as an unexpected VM-Entry failure
due to an invalid code field (error number 7) in L1, e.g. when injecting
a #GP with error_code=0x9f00.

Nadav previously reported the bug[*], both to KVM and Intel, and fixed
the associated kvm-unit-test.

[*] https://patchwork.kernel.org/patch/11124749/

Reported-by: Nadav Amit <namit@vmware.com>
Cc: stable@vger.kernel.org
Signed-off-by: Sean Christopherson <sean.j.christopherson@intel.com>
Reviewed-by: Jim Mattson <jmattson@google.com>
---
 arch/x86/kvm/vmx/nested.c | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
#### [PATCH] KVM: VMX: Refactor to not compare set PI control bits directly to 1
##### From: Liran Alon <liran.alon@oracle.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Liran Alon <liran.alon@oracle.com>
X-Patchwork-Id: 11167915
Return-Path: <SRS0=7VF/=X2=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id C8CE215AB
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue,  1 Oct 2019 00:54:54 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 9B9FB20815
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue,  1 Oct 2019 00:54:54 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=oracle.com header.i=@oracle.com
 header.b="MlfXtjzG"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726504AbfJAAyx (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 30 Sep 2019 20:54:53 -0400
Received: from userp2130.oracle.com ([156.151.31.86]:46480 "EHLO
        userp2130.oracle.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726106AbfJAAyx (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 30 Sep 2019 20:54:53 -0400
Received: from pps.filterd (userp2130.oracle.com [127.0.0.1])
        by userp2130.oracle.com (8.16.0.27/8.16.0.27) with SMTP id
 x910sPFZ044141;
        Tue, 1 Oct 2019 00:54:25 GMT
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=oracle.com;
 h=from : to : cc :
 subject : date : message-id : mime-version : content-transfer-encoding;
 s=corp-2019-08-05; bh=ONs2SYLamQotGg6e7nWLECdwnmymLC6XzGH89lGa0q4=;
 b=MlfXtjzG5jwNI2YrVFFxytoIBParj18rUsOewqPvr0o/TAn4cYgi5dJdhcL4y7Bl1hXT
 ZS++1WWWkviahaAo5GTlPjXe5Mi3+Cy0Sx/i26kfl2EnTmZLAjdrBC+O6BI7RRZSSpFC
 xdVlX/f4GYPVj4TIWevdbUG+dzY+9jpo5fun+Th1JIh0VAOyWIVspdTD3XdhcOK90uf1
 W5Q/dNHxQwsHTFw5IhAyWd3N0MzVuf6YjkoivhEKyS0PYQMEv/ubV0KctVq6/Egddyq3
 4vgyua24QCwxYbcyYkARqALBZxq6hhOElAeCFZdU+imzOxVbpF/mHUbKKB05fqJFUzvJ OQ==
Received: from userp3020.oracle.com (userp3020.oracle.com [156.151.31.79])
        by userp2130.oracle.com with ESMTP id 2v9xxujkq1-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Tue, 01 Oct 2019 00:54:25 +0000
Received: from pps.filterd (userp3020.oracle.com [127.0.0.1])
        by userp3020.oracle.com (8.16.0.27/8.16.0.27) with SMTP id
 x910rJXT040250;
        Tue, 1 Oct 2019 00:54:24 GMT
Received: from aserv0122.oracle.com (aserv0122.oracle.com [141.146.126.236])
        by userp3020.oracle.com with ESMTP id 2vbnqbr3rb-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Tue, 01 Oct 2019 00:54:24 +0000
Received: from abhmp0009.oracle.com (abhmp0009.oracle.com [141.146.116.15])
        by aserv0122.oracle.com (8.14.4/8.14.4) with ESMTP id x910sN8t002278;
        Tue, 1 Oct 2019 00:54:23 GMT
Received: from spark.ravello.local (/213.57.127.2)
        by default (Oracle Beehive Gateway v4.0)
        with ESMTP ; Mon, 30 Sep 2019 17:54:23 -0700
From: Liran Alon <liran.alon@oracle.com>
To: pbonzini@redhat.com, rkrcmar@redhat.com, kvm@vger.kernel.org
Cc: sean.j.christopherson@intel.com, jmattson@google.com,
        vkuznets@redhat.com, Liran Alon <liran.alon@oracle.com>,
        Krish Sadhukhan <krish.sadhukhan@oracle.com>
Subject: [PATCH] KVM: VMX: Refactor to not compare set PI control bits
 directly to 1
Date: Tue,  1 Oct 2019 03:54:08 +0300
Message-Id: <20191001005408.129099-1-liran.alon@oracle.com>
X-Mailer: git-send-email 2.20.1
MIME-Version: 1.0
X-Proofpoint-Virus-Version: vendor=nai engine=6000 definitions=9396
 signatures=668685
X-Proofpoint-Spam-Details: rule=notspam policy=default score=0 suspectscore=0
 malwarescore=0
 phishscore=0 bulkscore=0 spamscore=0 mlxscore=0 mlxlogscore=765
 adultscore=0 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.0.1-1908290000 definitions=main-1910010008
X-Proofpoint-Virus-Version: vendor=nai engine=6000 definitions=9396
 signatures=668685
X-Proofpoint-Spam-Details: rule=notspam policy=default score=0
 priorityscore=1501 malwarescore=0
 suspectscore=0 phishscore=0 bulkscore=0 spamscore=0 clxscore=1015
 lowpriorityscore=0 mlxscore=0 impostorscore=0 mlxlogscore=849 adultscore=0
 classifier=spam adjust=0 reason=mlx scancount=1 engine=8.0.1-1908290000
 definitions=main-1910010008
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This is a pure code refactoring.
No semantic change is expected.

Reviewed-by: Krish Sadhukhan <krish.sadhukhan@oracle.com>
Signed-off-by: Liran Alon <liran.alon@oracle.com>
Reviewed-by: Jim Mattson <jmattson@google.com>
---
 arch/x86/kvm/vmx/vmx.c | 18 ++++++++----------
 1 file changed, 8 insertions(+), 10 deletions(-)

```
#### [PATCH] KVM: x86: omit "impossible" pmu MSRs from MSR list
##### From: Paolo Bonzini <pbonzini@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Paolo Bonzini <pbonzini@redhat.com>
X-Patchwork-Id: 11168805
Return-Path: <SRS0=7VF/=X2=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 39DD813BD
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue,  1 Oct 2019 13:33:16 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 176EF21906
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue,  1 Oct 2019 13:33:16 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=fail reason="signature verification failed" (2048-bit key)
 header.d=gmail.com header.i=@gmail.com header.b="ReaAukld"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2388433AbfJANdM (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 1 Oct 2019 09:33:12 -0400
Received: from mail-wr1-f67.google.com ([209.85.221.67]:35531 "EHLO
        mail-wr1-f67.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726710AbfJANdL (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 1 Oct 2019 09:33:11 -0400
Received: by mail-wr1-f67.google.com with SMTP id v8so15585966wrt.2;
        Tue, 01 Oct 2019 06:33:10 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=sender:from:to:cc:subject:date:message-id;
        bh=c4RlMElRapjcKytoDFpBCb3LWrmJDVBw/FZtdDDpZ7M=;
        b=ReaAukldOTH7DgxKYY1FpLm0deK+WPWVtPBXFNwMoZpHBlAqxrnJ5iwa7AlOltDiad
         ci5R/iWReKZ9jPh2M+b2zSrcl9Go4kGDztbpvC5uanP73qT5bxyQvH7Qw3BmkpwxkY4f
         6Uj8n9CEhlSSRKftU1ZwCUUtnu/mLjH/2+rrcbMKMcq+Swp2CVy9mWXEtocmMWwKK9YO
         204nTn+MhW9F5ogSr8xns5C/GiwxN5vuMLl+9g1ud1cpdFLLGssKcOmtrSUw5Z/+yamj
         pdL1zRC1GUCNHNQpsx6/gYnhMIjm0pgjL5hyWLa5lCAwpF6X7+9QzIIBtecfrgI2bnPW
         Kr5g==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:sender:from:to:cc:subject:date:message-id;
        bh=c4RlMElRapjcKytoDFpBCb3LWrmJDVBw/FZtdDDpZ7M=;
        b=iWPrQdhb+TDU+DPPBV5b3f39Wfv/FVtQnDthLEOOw3HA0YR5T23996lwvKg0e+bv3j
         6IwRWEtPrk6p7OutmjO5KQb1r1xrn0f4iql1PcbwqNWd3Xzv1WlwRI0bT7Wo4ZXJ3yp6
         0nhxpS/Tj3g3Yd/vxih1oREUhWJOzfSmCzFnFcFjkYOO3/25DF01HOGZy+hHsJ41euvR
         Ylexd9V4a1JYUnNu2AvEbC40IyZB5fzkZ2P3Jc0Maq5nG7PhaJAQYUlkiFvtQlwnlx0g
         3awJKkc+Sml/vluI+PPuNAWNeaWJ6q2z6TegLXHCRIHKAX2/ylq/aoSrgkSLGdCARsi+
         tdoA==
X-Gm-Message-State: APjAAAXxbzWij6oKK7ItzCClv5VVUKiz6m8qOp2UgUy4jYIlchiRWQBk
        eoM5L5c2lA+duaTFeNyaitTZT4TG
X-Google-Smtp-Source: 
 APXvYqwC2c5XZwSfhL82+feZqCE+1GNRkJYO4+W95yyUGIENFaeaJrv0VmZlL3HZmbAfB6VThUyFMg==
X-Received: by 2002:adf:828d:: with SMTP id 13mr18346412wrc.115.1569936789559;
        Tue, 01 Oct 2019 06:33:09 -0700 (PDT)
Received: from 640k.localdomain ([93.56.166.5])
        by smtp.gmail.com with ESMTPSA id
 u25sm3091302wml.4.2019.10.01.06.33.07
        (version=TLS1_2 cipher=ECDHE-RSA-AES128-GCM-SHA256 bits=128/128);
        Tue, 01 Oct 2019 06:33:08 -0700 (PDT)
From: Paolo Bonzini <pbonzini@redhat.com>
To: linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Cc: vkuznets@redhat.com, Jim Mattson <jamttson@google.com>
Subject: [PATCH] KVM: x86: omit "impossible" pmu MSRs from MSR list
Date: Tue,  1 Oct 2019 15:33:07 +0200
Message-Id: <1569936787-56615-1-git-send-email-pbonzini@redhat.com>
X-Mailer: git-send-email 1.8.3.1
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

INTEL_PMC_MAX_GENERIC is currently 32, which exceeds the 18
contiguous MSR indices reserved by Intel for event selectors.
Since some machines actually have MSRs past the reserved range,
these may survive the filtering of msrs_to_save array and would
be rejected by KVM_GET/SET_MSR.  Cut the list to 18 entries to
avoid this.

Reported-by: Vitaly Kuznetsov <vkuznets@redhat.com>
Suggested-by: Vitaly Kuznetsov <vkuznets@redhat.com>
Cc: Jim Mattson <jamttson@google.com>
Fixes: e2ada66ec418 ("kvm: x86: Add Intel PMU MSRs to msrs_to_save[]", 2019-08-21)
Signed-off-by: Paolo Bonzini <pbonzini@redhat.com>
---
 arch/x86/kvm/x86.c | 14 --------------
 1 file changed, 14 deletions(-)

```
#### [PATCH v11 1/6] mm: Adjust shuffle code to allow for future coalescing
##### From: Alexander Duyck <alexander.duyck@gmail.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Alexander Duyck <alexander.duyck@gmail.com>
X-Patchwork-Id: 11169053
Return-Path: <SRS0=7VF/=X2=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id E462415AB
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue,  1 Oct 2019 15:29:28 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id B9AE621855
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue,  1 Oct 2019 15:29:28 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=gmail.com header.i=@gmail.com
 header.b="lx1oVk9a"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2389604AbfJAP3Z (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 1 Oct 2019 11:29:25 -0400
Received: from mail-pg1-f193.google.com ([209.85.215.193]:39530 "EHLO
        mail-pg1-f193.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S2389599AbfJAP3Y (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 1 Oct 2019 11:29:24 -0400
Received: by mail-pg1-f193.google.com with SMTP id e1so4373550pgj.6;
        Tue, 01 Oct 2019 08:29:24 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=subject:from:to:cc:date:message-id:in-reply-to:references
         :user-agent:mime-version:content-transfer-encoding;
        bh=Tg18ELn2yO5mcuA4hxXn6maR2nECizjJ7QIklFwPvZY=;
        b=lx1oVk9a+K28U2Q4cIxXEnv2szQ55+pVMEJbqitaU78Q9t6pOGpbqBFo9JgVDqkk7Y
         BAP8Gp/iLZZYowCaiahV22PwkOxuN2SrO/wFKvrzbgNB01XLsTdgW0AgCwXANCk5pd3U
         RnutPSXmj9y26VPc3eXfdJg0ScrTKXsFITcV6oJm3l4UNcRQz5iR+zi9LD+1JvG0uybr
         g/2qB0PbzVl9uRsJMGYbJL6E4PIC2Swqgeo8VuZkm9rTacz7n2xFI29IoyY01jbvRBBO
         ioQQmBVOopuw9V4ZUbAUBGKgUZCJDTUcZc+QOJUmZSRffxZTE2ys0U32nypNgZW/apUu
         dtUg==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:subject:from:to:cc:date:message-id:in-reply-to
         :references:user-agent:mime-version:content-transfer-encoding;
        bh=Tg18ELn2yO5mcuA4hxXn6maR2nECizjJ7QIklFwPvZY=;
        b=tanUmvmDMYCrPY+Q13b4xOBgVzPgqaEVeMxi3CKh/GJW5kCuaNOl17WU7d7dAvNqFU
         mOzaiLh++U7jF1VwqN+iPS5DaxBVAapYu2o5Yr9AO3hKl5kQ1aRZYkv8q+0OzO3tswrx
         DRukEZOJVpEXx3ddPD9IcRPbBR7DDbZp/VSXh6u3VMd3enOfL1S+T569L03siSZQcxPV
         xSkxOe2qkuJwUIibc+sDlpeauHeapDOLDHDTtD+Ut5aoi184sVmDwDoC5C2TXA9GOu/Z
         N7QW/JWK9LS3MAhob5/OMJDMGl5tzxxES/0YsFPqNRdxdunRuASLdJhz+crjWGDbKC9K
         XQKQ==
X-Gm-Message-State: APjAAAX8m9olonet/1h9WGucvpYE/lllSFj5gQtHsouh0ZEGKVWkE6hc
        BrfKKEeWwtlOsh8Rey6VDIY=
X-Google-Smtp-Source: 
 APXvYqyHYHJwcWxzkd4NhdCH54CaB7vgm6krCM92IUZUhaDZPWi4HQ6ltB3UP1AlBMlsNjIktZRFTw==
X-Received: by 2002:a17:90a:850c:: with SMTP id
 l12mr6347604pjn.9.1569943763533;
        Tue, 01 Oct 2019 08:29:23 -0700 (PDT)
Received: from localhost.localdomain ([2001:470:b:9c3:9e5c:8eff:fe4f:f2d0])
        by smtp.gmail.com with ESMTPSA id
 o64sm11445923pjb.24.2019.10.01.08.29.22
        (version=TLS1_2 cipher=ECDHE-RSA-AES128-GCM-SHA256 bits=128/128);
        Tue, 01 Oct 2019 08:29:22 -0700 (PDT)
Subject: [PATCH v11 1/6] mm: Adjust shuffle code to allow for future
 coalescing
From: Alexander Duyck <alexander.duyck@gmail.com>
To: virtio-dev@lists.oasis-open.org, kvm@vger.kernel.org,
        mst@redhat.com, david@redhat.com, dave.hansen@intel.com,
        linux-kernel@vger.kernel.org, willy@infradead.org,
        mhocko@kernel.org, linux-mm@kvack.org, akpm@linux-foundation.org,
        mgorman@techsingularity.net, vbabka@suse.cz, osalvador@suse.de
Cc: yang.zhang.wz@gmail.com, pagupta@redhat.com,
        konrad.wilk@oracle.com, nitesh@redhat.com, riel@surriel.com,
        lcapitulino@redhat.com, wei.w.wang@intel.com, aarcange@redhat.com,
        pbonzini@redhat.com, dan.j.williams@intel.com,
        alexander.h.duyck@linux.intel.com
Date: Tue, 01 Oct 2019 08:29:21 -0700
Message-ID: <20191001152921.27008.56300.stgit@localhost.localdomain>
In-Reply-To: <20191001152441.27008.99285.stgit@localhost.localdomain>
References: <20191001152441.27008.99285.stgit@localhost.localdomain>
User-Agent: StGit/0.17.1-dirty
MIME-Version: 1.0
Content-Type: text/plain; charset="utf-8"
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Alexander Duyck <alexander.h.duyck@linux.intel.com>

Move the head/tail adding logic out of the shuffle code and into the
__free_one_page function since ultimately that is where it is really
needed anyway. By doing this we should be able to reduce the overhead
and can consolidate all of the list addition bits in one spot.

Acked-by: David Hildenbrand <david@redhat.com>
Reviewed-by: Dan Williams <dan.j.williams@intel.com>
Signed-off-by: Alexander Duyck <alexander.h.duyck@linux.intel.com>
---
 include/linux/mmzone.h |   12 --------
 mm/page_alloc.c        |   71 ++++++++++++++++++++++++++++--------------------
 mm/shuffle.c           |   12 ++++----
 mm/shuffle.h           |    6 ++++
 4 files changed, 54 insertions(+), 47 deletions(-)

```
#### [PATCH v11 QEMU 1/3] virtio-ballon: Implement support for page poison tracking feature
##### From: Alexander Duyck <alexander.duyck@gmail.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Alexander Duyck <alexander.duyck@gmail.com>
X-Patchwork-Id: 11169077
Return-Path: <SRS0=7VF/=X2=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id CB75B17EE
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue,  1 Oct 2019 15:31:10 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id A037B21920
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue,  1 Oct 2019 15:31:10 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=gmail.com header.i=@gmail.com
 header.b="V8K9ubyP"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2389733AbfJAPbH (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 1 Oct 2019 11:31:07 -0400
Received: from mail-pf1-f181.google.com ([209.85.210.181]:39447 "EHLO
        mail-pf1-f181.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S2388916AbfJAPbG (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 1 Oct 2019 11:31:06 -0400
Received: by mail-pf1-f181.google.com with SMTP id v4so8249737pff.6;
        Tue, 01 Oct 2019 08:31:06 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=subject:from:to:cc:date:message-id:in-reply-to:references
         :user-agent:mime-version:content-transfer-encoding;
        bh=yOvpSx16yNanZpbvFfAUMxFv0SM7m3MFplEES/wscuI=;
        b=V8K9ubyPUrdpnrmSOAC73089fGmxD7KrIocxPwWm1QzVfdt3FcuTZEGONzAFdyth6u
         sGefLFPqh2EbWni4qEdxD2GIeZLuWpOLwO6ECoPUxIooVjs/9rQSXRaQVdUG+ywp/EH3
         dYWS5wMSb6sbqVPzIHlDDnm78+QO1dVNS1a8IVvIxM/fZnkZ/OnRRywNonMqTz3cN+cw
         gkYozCp/HqkY2G471L9pfTKkYJ6N5IRWdIn+FYFCh/9eMNyT+KShuHDhu3W8u6O7/C3x
         iFdFYddCLvcLG/g6nYfLePdjN5uOwn1bcRm21Yegjb5L0reVWMxPb17QJEiLaSVhLtq+
         D1sA==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:subject:from:to:cc:date:message-id:in-reply-to
         :references:user-agent:mime-version:content-transfer-encoding;
        bh=yOvpSx16yNanZpbvFfAUMxFv0SM7m3MFplEES/wscuI=;
        b=URb7lOKry2qiFkGH/vmXLS+7U5SKxLM4DPw/W0s1CcGCT8Vy4QIKBQddBx+EbhHh4u
         YuLy4JXExFSfEOHjhequQuR8FbV9OqJe+rdi0xpzB2dnuWBex5b1agNtdfiqSy9C3qYW
         pzsMAj2ZhQsA7Gbgj1suCF3w3xjSoeHZuTFoVj1rt7KVZ4HrjZRNnKsYrCN/0/kq3Sdv
         WCt5RtBK7frQUEs/z0YGRUkNZZ7bpWg93O/76W9m8E/ZqcMmgOFsUb/a8Ixb6JxQ0cl8
         ADF/DrcTmZHq9lodqbO2GGpi+omTjZif7cZr+jhNv6hsIhKfWGVCNTb7c9DEDwonAeu7
         YmqA==
X-Gm-Message-State: APjAAAUyj6OdEpMZzDAf/7aC0po81jBRAvYzAErakTbleQzywZAU0C2Q
        ZNeibPoowLVr/TK5UMbrcvI=
X-Google-Smtp-Source: 
 APXvYqy5jTzWyFjT2sA9x7lttfBhyQ4DIf4lDr9fYdux1MCucUsEe+ziZfR1t5cq8ZSqgxo/kOtPWg==
X-Received: by 2002:aa7:870a:: with SMTP id b10mr28512461pfo.5.1569943865813;
        Tue, 01 Oct 2019 08:31:05 -0700 (PDT)
Received: from localhost.localdomain ([2001:470:b:9c3:9e5c:8eff:fe4f:f2d0])
        by smtp.gmail.com with ESMTPSA id
 l12sm21924491pgs.44.2019.10.01.08.31.04
        (version=TLS1_2 cipher=ECDHE-RSA-AES128-GCM-SHA256 bits=128/128);
        Tue, 01 Oct 2019 08:31:05 -0700 (PDT)
Subject: [PATCH v11 QEMU 1/3] virtio-ballon: Implement support for page
 poison tracking feature
From: Alexander Duyck <alexander.duyck@gmail.com>
To: virtio-dev@lists.oasis-open.org, kvm@vger.kernel.org,
        mst@redhat.com, david@redhat.com, dave.hansen@intel.com,
        linux-kernel@vger.kernel.org, willy@infradead.org,
        mhocko@kernel.org, linux-mm@kvack.org, akpm@linux-foundation.org,
        mgorman@techsingularity.net, vbabka@suse.cz, osalvador@suse.de
Cc: yang.zhang.wz@gmail.com, pagupta@redhat.com,
        konrad.wilk@oracle.com, nitesh@redhat.com, riel@surriel.com,
        lcapitulino@redhat.com, wei.w.wang@intel.com, aarcange@redhat.com,
        pbonzini@redhat.com, dan.j.williams@intel.com,
        alexander.h.duyck@linux.intel.com
Date: Tue, 01 Oct 2019 08:31:04 -0700
Message-ID: <20191001153104.4422.12747.stgit@localhost.localdomain>
In-Reply-To: <20191001152441.27008.99285.stgit@localhost.localdomain>
References: <20191001152441.27008.99285.stgit@localhost.localdomain>
User-Agent: StGit/0.17.1-dirty
MIME-Version: 1.0
Content-Type: text/plain; charset="utf-8"
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Alexander Duyck <alexander.h.duyck@linux.intel.com>

We need to make certain to advertise support for page poison tracking if
we want to actually get data on if the guest will be poisoning pages. So
if free page hinting is active we should add page poisoning support and
let the guest disable it if it isn't using it.

Page poisoning will result in a page being dirtied on free. As such we
cannot really avoid having to copy the page at least one more time since
we will need to write the poison value to the destination. As such we can
just ignore free page hinting if page poisoning is enabled as it will
actually reduce the work we have to do.

Signed-off-by: Alexander Duyck <alexander.h.duyck@linux.intel.com>
---
 hw/virtio/virtio-balloon.c         |   25 +++++++++++++++++++++----
 include/hw/virtio/virtio-balloon.h |    1 +
 2 files changed, 22 insertions(+), 4 deletions(-)

```
