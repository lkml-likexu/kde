#### [PATCH 1/6] KVM: Fix some wrong function names in comment
##### From: linmiaohe <linmiaohe@huawei.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: linmiaohe <linmiaohe@huawei.com>
X-Patchwork-Id: 11284349
Return-Path: <SRS0=dbDR=2B=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 2347C188B
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 11 Dec 2019 06:27:26 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 02AA52173E
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 11 Dec 2019 06:27:26 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727814AbfLKG0r (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 11 Dec 2019 01:26:47 -0500
Received: from szxga05-in.huawei.com ([45.249.212.191]:7214 "EHLO huawei.com"
        rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org with ESMTP
        id S1727777AbfLKG0r (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 11 Dec 2019 01:26:47 -0500
Received: from DGGEMS407-HUB.china.huawei.com (unknown [172.30.72.60])
        by Forcepoint Email with ESMTP id 493B8CE977B0D7BFD3AD;
        Wed, 11 Dec 2019 14:26:45 +0800 (CST)
Received: from huawei.com (10.175.105.18) by DGGEMS407-HUB.china.huawei.com
 (10.3.19.207) with Microsoft SMTP Server id 14.3.439.0; Wed, 11 Dec 2019
 14:26:38 +0800
From: linmiaohe <linmiaohe@huawei.com>
To: <pbonzini@redhat.com>, <rkrcmar@redhat.com>,
        <sean.j.christopherson@intel.com>, <vkuznets@redhat.com>,
        <wanpengli@tencent.com>, <jmattson@google.com>, <joro@8bytes.org>,
        <tglx@linutronix.de>, <mingo@redhat.com>, <bp@alien8.de>,
        <hpa@zytor.com>
CC: <linmiaohe@huawei.com>, <kvm@vger.kernel.org>,
        <linux-kernel@vger.kernel.org>, <x86@kernel.org>
Subject: [PATCH 1/6] KVM: Fix some wrong function names in comment
Date: Wed, 11 Dec 2019 14:26:20 +0800
Message-ID: <1576045585-8536-2-git-send-email-linmiaohe@huawei.com>
X-Mailer: git-send-email 1.8.3.1
In-Reply-To: <1576045585-8536-1-git-send-email-linmiaohe@huawei.com>
References: <1576045585-8536-1-git-send-email-linmiaohe@huawei.com>
MIME-Version: 1.0
X-Originating-IP: [10.175.105.18]
X-CFilter-Loop: Reflected
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Miaohe Lin <linmiaohe@huawei.com>

Fix some wrong function names in comment. mmu_check_roots is a typo for
mmu_check_root, vmcs_read_any should be vmcs12_read_any and so on.

Signed-off-by: Miaohe Lin <linmiaohe@huawei.com>
---
 arch/x86/kvm/vmx/vmcs_shadow_fields.h | 2 +-
 virt/kvm/kvm_main.c                   | 2 +-
 2 files changed, 2 insertions(+), 2 deletions(-)

```
#### [kvm-unit-tests PATCH 1/4] scripts: Fix premature_failure() check with newer versions of QEMU
##### From: Thomas Huth <thuth@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Thomas Huth <thuth@redhat.com>
X-Patchwork-Id: 11284587
Return-Path: <SRS0=dbDR=2B=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 8A47F138D
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 11 Dec 2019 09:42:33 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 5F921214D8
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 11 Dec 2019 09:42:33 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="Pq5VyOlx"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728653AbfLKJmc (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 11 Dec 2019 04:42:32 -0500
Received: from us-smtp-delivery-1.mimecast.com ([205.139.110.120]:48927 "EHLO
        us-smtp-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org
        with ESMTP id S1728590AbfLKJmc (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 11 Dec 2019 04:42:32 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1576057351;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:content-type:content-type:
         content-transfer-encoding:content-transfer-encoding:
         in-reply-to:in-reply-to:references:references;
        bh=R3qlUCV9KAzTRD5BLeh8Hw9oSDfU4THuhXKb8NvAbCk=;
        b=Pq5VyOlxmfWEfWw3z/Rw3qYSCO/QaT4aLWEZeKb7f4SrRztX6TwBgeGzhLO7F+JVxO51US
        6rb6Hwb0QiP9jums+Ceczz9nLuBCRjxJbdXqttBGbwrYgj6FyibEcsn2AhhqAiscO6YeAO
        6RjIeW1ePcNEIoujIB6eXgv6gNm0JqQ=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-180-RmA6yfBXPnC75X-WRRUQ3g-1; Wed, 11 Dec 2019 04:42:28 -0500
Received: from smtp.corp.redhat.com (int-mx05.intmail.prod.int.phx2.redhat.com
 [10.5.11.15])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 85D67800D4C
        for <kvm@vger.kernel.org>; Wed, 11 Dec 2019 09:42:27 +0000 (UTC)
Received: from thuth.com (ovpn-117-11.ams2.redhat.com [10.36.117.11])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 7AFB763629;
        Wed, 11 Dec 2019 09:42:26 +0000 (UTC)
From: Thomas Huth <thuth@redhat.com>
To: Paolo Bonzini <pbonzini@redhat.com>, kvm@vger.kernel.org
Cc: Drew Jones <drjones@redhat.com>
Subject: [kvm-unit-tests PATCH 1/4] scripts: Fix premature_failure() check
 with newer versions of QEMU
Date: Wed, 11 Dec 2019 10:42:18 +0100
Message-Id: <20191211094221.7030-2-thuth@redhat.com>
In-Reply-To: <20191211094221.7030-1-thuth@redhat.com>
References: <20191211094221.7030-1-thuth@redhat.com>
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.15
X-MC-Unique: RmA6yfBXPnC75X-WRRUQ3g-1
X-Mimecast-Spam-Score: 0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

QEMU recently changed its output if it could not open a kernel file
from "could not load kernel ..." to "could not open kernel ...", see
QEMU commit 350f5233d755 ("hw/i386/pc: avoid an assignment in if
condition in x86_load_linux()"). Thus we have to adapt our script
that looks for this string accordingly.

Signed-off-by: Thomas Huth <thuth@redhat.com>
---
 scripts/runtime.bash | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
#### [PATCH 1/3] KVM: arm/arm64: Properly handle faulting of device mappings
##### From: Marc Zyngier <maz@kernel.org>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Marc Zyngier <maz@kernel.org>
X-Patchwork-Id: 11285743
Return-Path: <SRS0=dbDR=2B=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 0B0CB1593
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 11 Dec 2019 16:57:12 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id DD952214AF
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 11 Dec 2019 16:57:11 +0000 (UTC)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple; d=kernel.org;
	s=default; t=1576083431;
	bh=GcFpvt75Xp6DJ4rGymnbWlL6+QOGJHhpt4xnoVMl6UE=;
	h=From:To:Cc:Subject:Date:In-Reply-To:References:List-ID:From;
	b=Lt9iAsRAXUYJ5V+sixf/CSZY8kUeAvih9j0ABdxnLuu5qtzSdTq8Nv+5xyaqfHKm3
	 09HXFEmh9AyTX5BUVBrbQZFwWCqBePK8fJafVLMMAunjX8MHHLLrtprOvJ8P1HQ5IX
	 4ddlEtPnzZxWKbzAIM/pPH8Hg4eodxaOuEF98zAM=
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1730591AbfLKQ5L (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 11 Dec 2019 11:57:11 -0500
Received: from inca-roads.misterjones.org ([213.251.177.50]:36508 "EHLO
        inca-roads.misterjones.org" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1726444AbfLKQ5K (ORCPT
        <rfc822;kvm@vger.kernel.org>); Wed, 11 Dec 2019 11:57:10 -0500
Received: from 78.163-31-62.static.virginmediabusiness.co.uk ([62.31.163.78]
 helo=why.lan)
        by cheepnis.misterjones.org with esmtpsa
 (TLSv1.2:DHE-RSA-AES128-GCM-SHA256:128)
        (Exim 4.80)
        (envelope-from <maz@kernel.org>)
        id 1if5IO-00076q-HF; Wed, 11 Dec 2019 17:57:04 +0100
From: Marc Zyngier <maz@kernel.org>
To: kvm@vger.kernel.org, kvmarm@lists.cs.columbia.edu,
        linux-arm-kernel@lists.infradead.org
Cc: James Morse <james.morse@arm.com>,
        Julien Thierry <julien.thierry.kdev@gmail.com>,
        Suzuki K Poulose <suzuki.poulose@arm.com>,
        Christoffer Dall <Christoffer.Dall@arm.com>,
        Alexandru Elisei <alexandru.elisei@arm.com>,
        stable@vger.kernel.org
Subject: [PATCH 1/3] KVM: arm/arm64: Properly handle faulting of device
 mappings
Date: Wed, 11 Dec 2019 16:56:48 +0000
Message-Id: <20191211165651.7889-2-maz@kernel.org>
X-Mailer: git-send-email 2.20.1
In-Reply-To: <20191211165651.7889-1-maz@kernel.org>
References: <20191211165651.7889-1-maz@kernel.org>
MIME-Version: 1.0
X-SA-Exim-Connect-IP: 62.31.163.78
X-SA-Exim-Rcpt-To: kvm@vger.kernel.org, kvmarm@lists.cs.columbia.edu,
 linux-arm-kernel@lists.infradead.org, james.morse@arm.com,
 julien.thierry.kdev@gmail.com, suzuki.poulose@arm.com,
 Christoffer.Dall@arm.com, alexandru.elisei@arm.com, stable@vger.kernel.org
X-SA-Exim-Mail-From: maz@kernel.org
X-SA-Exim-Scanned: No (on cheepnis.misterjones.org);
 SAEximRunCond expanded to false
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

A device mapping is normally always mapped at Stage-2, since there
is very little gain in having it faulted in.

Nonetheless, it is possible to end-up in a situation where the device
mapping has been removed from Stage-2 (userspace munmaped the VFIO
region, and the MMU notifier did its job), but present in a userspace
mapping (userpace has mapped it back at the same address). In such
a situation, the device mapping will be demand-paged as the guest
performs memory accesses.

This requires to be careful when dealing with mapping size, cache
management, and to handle potential execution of a device mapping.

Cc: stable@vger.kernel.org
Reported-by: Alexandru Elisei <alexandru.elisei@arm.com>
Signed-off-by: Marc Zyngier <maz@kernel.org>
Tested-by: Alexandru Elisei <alexandru.elisei@arm.com>
---
 virt/kvm/arm/mmu.c | 21 +++++++++++++++++----
 1 file changed, 17 insertions(+), 4 deletions(-)

```
#### [PATCH v4 1/2] mm: make dev_pagemap_mapping_shift() externally visible
##### From: Barret Rhoden <brho@google.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Barret Rhoden <brho@google.com>
X-Patchwork-Id: 11286481
Return-Path: <SRS0=dbDR=2B=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id A0DA314BD
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 11 Dec 2019 21:32:33 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 7DB572054F
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 11 Dec 2019 21:32:33 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=google.com header.i=@google.com
 header.b="EsxnNiRN"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726769AbfLKVcZ (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 11 Dec 2019 16:32:25 -0500
Received: from mail-qk1-f202.google.com ([209.85.222.202]:39507 "EHLO
        mail-qk1-f202.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726708AbfLKVcZ (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 11 Dec 2019 16:32:25 -0500
Received: by mail-qk1-f202.google.com with SMTP id g28so45346qkl.6
        for <kvm@vger.kernel.org>; Wed, 11 Dec 2019 13:32:24 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=date:in-reply-to:message-id:mime-version:references:subject:from:to
         :cc;
        bh=sDaCcLT3BcQJ23kfy/HaXZtjLV54Z/X5vMBQ4m0F9ws=;
        b=EsxnNiRNv8If11+vloXSQ7nwWN1lItAewnF+sLDaSlmolmYksUpNvpwBYaM7L41HUd
         uWxT5Uu6Hic1c/J1Y90egmD8MQQddHSFtNUFiZ5CgltHtE64rJa9kd7xChSG2D/6uEYH
         tso9FlUjwcWCykQdNsAPbyh3GEyMbxk8q6nPIK6Itca/A4kuMsDUiiPT4l8tKvAc7+4P
         TfcrFl85CPUmcmMtw5eYhoZX333AYEy6qoWY13yAKMWwOQP/bqViTLN5LEzAoWkVYn4+
         9YSHcl3zD7aKQyQ02OdDsUczHpKePD6qPvej9G3oRirDEbrbz7oIgSvbjWHtU4syo/ie
         grnQ==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:date:in-reply-to:message-id:mime-version
         :references:subject:from:to:cc;
        bh=sDaCcLT3BcQJ23kfy/HaXZtjLV54Z/X5vMBQ4m0F9ws=;
        b=E+uMiPa/rj05aKB9RygGePA0ZcLnZVXk8SfJeWkdj9PJjzeHi7TwTdSk8Iccj6yTiB
         l8ZtfI7eQWIMdWbXzDlfqi4bJFdIhGebPWX/qgKQK2V8rklk7c6Z2R6FjcLVpthzRtDY
         YmeH31lJaIO9D8nE8V+JRl6G4X48ehUNL9aGh5XwOsLYS+TUzRBzlrfX3XThBnc/oe6L
         b/GNFYVtw0PsujPSamSBxrBKktEKlORxH4Gcls7TIfODEDcekdeCZ3YANR+38BvczEjt
         AjQ0hWa0l33jgI/vYsy8UtyYSHHnMn6Sod9FdILnG4cBYJHBhOhHcbp3zbQPfmKbPhJj
         kpoQ==
X-Gm-Message-State: APjAAAXK1WbIiLVTqrPCGWe+vW4j6ZIq2geYYy8Dk8cixGs1E2IAuNDA
        qmsGrpDrv4Ryv7At6JhqCGp8rCQa
X-Google-Smtp-Source: 
 APXvYqymtB08I22rTfCyFtgWxWJ8AqN73LVOvZo61CMncBXCwtep0KelAX9VW18l1EiAV26YFXB+Df9C
X-Received: by 2002:a05:6214:209:: with SMTP id
 i9mr5144868qvt.54.1576099944237;
 Wed, 11 Dec 2019 13:32:24 -0800 (PST)
Date: Wed, 11 Dec 2019 16:32:06 -0500
In-Reply-To: <20191211213207.215936-1-brho@google.com>
Message-Id: <20191211213207.215936-2-brho@google.com>
Mime-Version: 1.0
References: <20191211213207.215936-1-brho@google.com>
X-Mailer: git-send-email 2.24.0.525.g8f36a354ae-goog
Subject: [PATCH v4 1/2] mm: make dev_pagemap_mapping_shift() externally
 visible
From: Barret Rhoden <brho@google.com>
To: Paolo Bonzini <pbonzini@redhat.com>,
        Dan Williams <dan.j.williams@intel.com>,
        David Hildenbrand <david@redhat.com>,
        Dave Jiang <dave.jiang@intel.com>,
        Alexander Duyck <alexander.h.duyck@linux.intel.com>
Cc: linux-nvdimm@lists.01.org, x86@kernel.org, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org, jason.zeng@intel.com
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

KVM has a use case for determining the size of a dax mapping.  The KVM
code has easy access to the address and the mm; hence the change in
parameters.

Signed-off-by: Barret Rhoden <brho@google.com>
Reviewed-by: David Hildenbrand <david@redhat.com>
Acked-by: Dan Williams <dan.j.williams@intel.com>
---
 include/linux/mm.h  |  3 +++
 mm/memory-failure.c | 38 +++-----------------------------------
 mm/util.c           | 34 ++++++++++++++++++++++++++++++++++
 3 files changed, 40 insertions(+), 35 deletions(-)

```
#### [PATCH v2 01/13] KVM: x86: Protect x86_decode_insn from Spectre-v1/L1TF attacks
##### From: Marios Pomonis <pomonis@google.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Marios Pomonis <pomonis@google.com>
X-Patchwork-Id: 11286345
Return-Path: <SRS0=dbDR=2B=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 13A1215AB
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 11 Dec 2019 20:48:25 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id E6C3322B48
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 11 Dec 2019 20:48:24 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=google.com header.i=@google.com
 header.b="ICYTPZ7c"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727126AbfLKUsY (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 11 Dec 2019 15:48:24 -0500
Received: from mail-qv1-f73.google.com ([209.85.219.73]:41193 "EHLO
        mail-qv1-f73.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726743AbfLKUsX (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 11 Dec 2019 15:48:23 -0500
Received: by mail-qv1-f73.google.com with SMTP id 75so18400qva.8
        for <kvm@vger.kernel.org>; Wed, 11 Dec 2019 12:48:22 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=date:in-reply-to:message-id:mime-version:references:subject:from:to
         :cc;
        bh=U1oRaOu4UKf7viNh4ANM8AYZUjuVHiI8DgaphOB3TV4=;
        b=ICYTPZ7c3Ur5ji8A/GJ8r6Yn1LPj2qOZ9iFVliX5y5EvvrQPEtD5bKeM/hIMzjzCdK
         9C7fqVZq5Dodo44qG4g3RI5a3sa9BWGW4OF6fXSYHtZClT+iMYX/X7zQKDgdGl5FTZkD
         VuZu07R6o/rPbJPedX7bDEBazLxwFoDm24MpXgvIBQCPXX+zjyDwOiwiKP7NdG7Y8ssE
         iFJNFPbtO5ZxdEojvVvyHPe94c+j7EC7ZLrgvsLPknHsYHF2CixJ3hzKeK60f4Z4F/aZ
         BGyVsAd4TsviSx5CLpkcieupXvevViyqB0BurofDUPCmizeEZDllBrv/MNt6YYaQr4Hx
         bbTw==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:date:in-reply-to:message-id:mime-version
         :references:subject:from:to:cc;
        bh=U1oRaOu4UKf7viNh4ANM8AYZUjuVHiI8DgaphOB3TV4=;
        b=DbuMl1ax2f25NCFB2xVfGqmYY732PJkmKFCmqDO6bLjMUXh5+wk8bWS9UaS5N5ivsb
         NPTvo91G9QEoZh3dlZf+56BQ3ZW65vh+gDfubt1YpImvJBuH37HMZL/MSl1lRv7z8fgQ
         ct+YKchcS+362MhtH38ZnolzF1s9kMK7Wq+NwSnDj8wqwT6kBYcRiO6WV0ijDrAoHULL
         p5WnG5BxOcELcRUkCBrzJT8KiSdw4Kvzc893/6OUqtPvJs0jOsUlUfGIUvyMkqhONuA3
         oTC+jbtbGgr/bFK04D07zo/3FWP92gyauk9dBkLoAGyqYdQUq9lxf50BXq5lWB6CFzV3
         GHXQ==
X-Gm-Message-State: APjAAAXLxv/TXP90ORmUxh6+WLMu5IfCF0ytwEr0LKwEL68czAewDSJ/
        lGaMrltjKlOGGJPZu/Jbin+oU1Swzavr
X-Google-Smtp-Source: 
 APXvYqwORnaDd0KerPCPPUjx9L0EkYqP+ngKokQFztfluoaxHnjP5honJKrXV1BllWzCwrUlPRfMnV7hPMj/
X-Received: by 2002:a37:9ace:: with SMTP id
 c197mr4955885qke.482.1576097302014;
 Wed, 11 Dec 2019 12:48:22 -0800 (PST)
Date: Wed, 11 Dec 2019 12:47:41 -0800
In-Reply-To: <20191211204753.242298-1-pomonis@google.com>
Message-Id: <20191211204753.242298-2-pomonis@google.com>
Mime-Version: 1.0
References: <20191211204753.242298-1-pomonis@google.com>
X-Mailer: git-send-email 2.24.0.525.g8f36a354ae-goog
Subject: [PATCH v2 01/13] KVM: x86: Protect x86_decode_insn from
 Spectre-v1/L1TF attacks
From: Marios Pomonis <pomonis@google.com>
To: Paolo Bonzini <pbonzini@redhat.com>, rkrcmar@redhat.com,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>
Cc: Thomas Gleixner <tglx@linutronix.de>,
        Ingo Molnar <mingo@redhat.com>, Borislav Petkov <bp@alien8.de>,
        "H. Peter Anvin" <hpa@zytor.com>, x86@kernel.org,
        kvm@vger.kernel.org, linux-kernel@vger.kernel.org,
        Nick Finco <nifi@google.com>, Andrew Honig <ahonig@google.com>,
        Marios Pomonis <pomonis@google.com>, stable@vger.kernel.org
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This fixes a Spectre-v1/L1TF vulnerability in x86_decode_insn().
kvm_emulate_instruction() (an ancestor of x86_decode_insn()) is an exported
symbol, so KVM should treat it conservatively from a security perspective.

Fixes: commit 045a282ca415 ("KVM: emulator: implement fninit, fnstsw, fnstcw")

Signed-off-by: Nick Finco <nifi@google.com>
Signed-off-by: Marios Pomonis <pomonis@google.com>
Reviewed-by: Andrew Honig <ahonig@google.com>
Cc: stable@vger.kernel.org
---
 arch/x86/kvm/emulate.c | 11 ++++++++---
 1 file changed, 8 insertions(+), 3 deletions(-)

```
#### [PATCH 1/2] KVM: x86: Add build-time assertion on usage of bit()
##### From: Sean Christopherson <sean.j.christopherson@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Sean Christopherson <sean.j.christopherson@intel.com>
X-Patchwork-Id: 11285895
Return-Path: <SRS0=dbDR=2B=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 00BC114B7
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 11 Dec 2019 17:58:30 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id DE99E24653
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 11 Dec 2019 17:58:29 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1730970AbfLKR6Y (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 11 Dec 2019 12:58:24 -0500
Received: from mga02.intel.com ([134.134.136.20]:29189 "EHLO mga02.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1730918AbfLKR6X (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 11 Dec 2019 12:58:23 -0500
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from orsmga007.jf.intel.com ([10.7.209.58])
  by orsmga101.jf.intel.com with ESMTP/TLS/DHE-RSA-AES256-GCM-SHA384;
 11 Dec 2019 09:58:22 -0800
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.69,302,1571727600";
   d="scan'208";a="203645151"
Received: from sjchrist-coffee.jf.intel.com ([10.54.74.202])
  by orsmga007.jf.intel.com with ESMTP; 11 Dec 2019 09:58:22 -0800
From: Sean Christopherson <sean.j.christopherson@intel.com>
To: Paolo Bonzini <pbonzini@redhat.com>
Cc: Sean Christopherson <sean.j.christopherson@intel.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org
Subject: [PATCH 1/2] KVM: x86: Add build-time assertion on usage of bit()
Date: Wed, 11 Dec 2019 09:58:21 -0800
Message-Id: <20191211175822.1925-2-sean.j.christopherson@intel.com>
X-Mailer: git-send-email 2.24.0
In-Reply-To: <20191211175822.1925-1-sean.j.christopherson@intel.com>
References: <20191211175822.1925-1-sean.j.christopherson@intel.com>
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Add build-time checks to ensure KVM isn't trying to do a reverse CPUID
lookup on Linux-defined feature bits, along with comments to explain
the gory details of X86_FEATUREs and bit().

Signed-off-by: Sean Christopherson <sean.j.christopherson@intel.com>
---

Note, the premature newline in the first line of the second comment is
intentional to reduce churn in the next patch.

 arch/x86/kvm/x86.h | 23 +++++++++++++++++++++--
 1 file changed, 21 insertions(+), 2 deletions(-)

```
#### [PATCH v9 01/25] mm/gup: factor out duplicate code from four routines
##### From: John Hubbard <jhubbard@nvidia.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 8bit
X-Patchwork-Submitter: John Hubbard <jhubbard@nvidia.com>
X-Patchwork-Id: 11284167
Return-Path: <SRS0=dbDR=2B=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 8695514B7
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 11 Dec 2019 02:57:41 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 5B1B0208C3
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 11 Dec 2019 02:57:41 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=nvidia.com header.i=@nvidia.com
 header.b="VS6zga5F"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727780AbfLKC5k (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 10 Dec 2019 21:57:40 -0500
Received: from hqnvemgate26.nvidia.com ([216.228.121.65]:16074 "EHLO
        hqnvemgate26.nvidia.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726619AbfLKCx1 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 10 Dec 2019 21:53:27 -0500
Received: from hqpgpgate101.nvidia.com (Not Verified[216.228.121.13]) by
 hqnvemgate26.nvidia.com (using TLS: TLSv1.2, DES-CBC3-SHA)
        id <B5df05a1b0000>; Tue, 10 Dec 2019 18:53:15 -0800
Received: from hqmail.nvidia.com ([172.20.161.6])
  by hqpgpgate101.nvidia.com (PGP Universal service);
  Tue, 10 Dec 2019 18:53:22 -0800
X-PGP-Universal: processed;
        by hqpgpgate101.nvidia.com on Tue, 10 Dec 2019 18:53:22 -0800
Received: from HQMAIL111.nvidia.com (172.20.187.18) by HQMAIL107.nvidia.com
 (172.20.187.13) with Microsoft SMTP Server (TLS) id 15.0.1473.3; Wed, 11 Dec
 2019 02:53:21 +0000
Received: from rnnvemgw01.nvidia.com (10.128.109.123) by HQMAIL111.nvidia.com
 (172.20.187.18) with Microsoft SMTP Server (TLS) id 15.0.1473.3 via Frontend
 Transport; Wed, 11 Dec 2019 02:53:21 +0000
Received: from blueforge.nvidia.com (Not Verified[10.110.48.28]) by
 rnnvemgw01.nvidia.com with Trustwave SEG (v7,5,8,10121)
        id <B5df05a200000>; Tue, 10 Dec 2019 18:53:20 -0800
From: John Hubbard <jhubbard@nvidia.com>
To: Andrew Morton <akpm@linux-foundation.org>
CC: Al Viro <viro@zeniv.linux.org.uk>,
 Alex Williamson <alex.williamson@redhat.com>,
 Benjamin Herrenschmidt <benh@kernel.crashing.org>, =?utf-8?b?QmrDtnJuIFQ=?=
	=?utf-8?b?w7ZwZWw=?= <bjorn.topel@intel.com>,
 Christoph Hellwig <hch@infradead.org>,
 Dan Williams <dan.j.williams@intel.com>, Daniel Vetter <daniel@ffwll.ch>,
 Dave Chinner <david@fromorbit.com>, David Airlie <airlied@linux.ie>,
 "David S . Miller" <davem@davemloft.net>, Ira Weiny <ira.weiny@intel.com>,
 Jan Kara <jack@suse.cz>, Jason Gunthorpe <jgg@ziepe.ca>,
 Jens Axboe <axboe@kernel.dk>, Jonathan Corbet <corbet@lwn.net>,
	=?utf-8?b?SsOpcsO0bWUgR2xpc3Nl?= <jglisse@redhat.com>,
 Magnus Karlsson <magnus.karlsson@intel.com>,
 Mauro Carvalho Chehab <mchehab@kernel.org>,
 Michael Ellerman <mpe@ellerman.id.au>, Michal Hocko <mhocko@suse.com>,
 Mike Kravetz <mike.kravetz@oracle.com>, Paul Mackerras <paulus@samba.org>,
 Shuah Khan <shuah@kernel.org>, Vlastimil Babka <vbabka@suse.cz>,
 <bpf@vger.kernel.org>, <dri-devel@lists.freedesktop.org>,
 <kvm@vger.kernel.org>, <linux-block@vger.kernel.org>,
 <linux-doc@vger.kernel.org>, <linux-fsdevel@vger.kernel.org>,
 <linux-kselftest@vger.kernel.org>, <linux-media@vger.kernel.org>,
 <linux-rdma@vger.kernel.org>, <linuxppc-dev@lists.ozlabs.org>,
 <netdev@vger.kernel.org>, <linux-mm@kvack.org>,
 LKML <linux-kernel@vger.kernel.org>, John Hubbard <jhubbard@nvidia.com>,
 Christoph Hellwig <hch@lst.de>,
 "Aneesh Kumar K . V" <aneesh.kumar@linux.ibm.com>
Subject: [PATCH v9 01/25] mm/gup: factor out duplicate code from four routines
Date: Tue, 10 Dec 2019 18:52:54 -0800
Message-ID: <20191211025318.457113-2-jhubbard@nvidia.com>
X-Mailer: git-send-email 2.24.0
In-Reply-To: <20191211025318.457113-1-jhubbard@nvidia.com>
References: <20191211025318.457113-1-jhubbard@nvidia.com>
MIME-Version: 1.0
X-NVConfidentiality: public
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=nvidia.com; s=n1;
        t=1576032796; bh=NjEUDVUY50BsRhke7z2S9TxhDwSe8KFPL35zO7aJjtI=;
        h=X-PGP-Universal:From:To:CC:Subject:Date:Message-ID:X-Mailer:
         In-Reply-To:References:MIME-Version:X-NVConfidentiality:
         Content-Type:Content-Transfer-Encoding;
        b=VS6zga5FiY7Vu66DRYjf2gKJmJHPntw8N8mBDsBSBO08ZCOCzw/y/IbIGZV7w6+rK
         E+0FFACMPbHQ8Ryk7Oh0Y+s6QwvjGNX5RFVxx65xXffaFuxKNEohDdD2uu2AeZGf8T
         0aNaGlfh+cFBX66CJL9rmJ8Sfhg2Wjp8E17AsstVPnU2q+jf97ejc7LMnamFN+MquO
         2souh8lQc9PrY4yN96BUULvxuG/fKmgjYyM04w35bMHMiSedO6olkvsI5KBpnLhtS6
         0zjzxArIxB/90HbuneEtdobksiH9+Dxg/voSuHfJAuJJCMhD4L5rof98Otg3ghAxW3
         HyRwaPmyoZPOQ==
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

There are four locations in gup.c that have a fair amount of code
duplication. This means that changing one requires making the same
changes in four places, not to mention reading the same code four
times, and wondering if there are subtle differences.

Factor out the common code into static functions, thus reducing the
overall line count and the code's complexity.

Also, take the opportunity to slightly improve the efficiency of the
error cases, by doing a mass subtraction of the refcount, surrounded
by get_page()/put_page().

Also, further simplify (slightly), by waiting until the the successful
end of each routine, to increment *nr.

Reviewed-by: Christoph Hellwig <hch@lst.de>
Reviewed-by: Jérôme Glisse <jglisse@redhat.com>
Reviewed-by: Jan Kara <jack@suse.cz>
Cc: Ira Weiny <ira.weiny@intel.com>
Cc: Christoph Hellwig <hch@lst.de>
Cc: Aneesh Kumar K.V <aneesh.kumar@linux.ibm.com>
Signed-off-by: John Hubbard <jhubbard@nvidia.com>
---
 mm/gup.c | 91 ++++++++++++++++++++++----------------------------------
 1 file changed, 36 insertions(+), 55 deletions(-)

```
#### [kvm-unit-tests PATCH 1/2] s390x: smp: Use full PSW to bringup new cpu
##### From: Janosch Frank <frankja@linux.ibm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Janosch Frank <frankja@linux.ibm.com>
X-Patchwork-Id: 11284793
Return-Path: <SRS0=dbDR=2B=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 5F1396C1
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 11 Dec 2019 11:59:37 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 47EDC21556
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 11 Dec 2019 11:59:37 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729108AbfLKL7g (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 11 Dec 2019 06:59:36 -0500
Received: from mx0a-001b2d01.pphosted.com ([148.163.156.1]:51056 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1727365AbfLKL7g (ORCPT
        <rfc822;kvm@vger.kernel.org>); Wed, 11 Dec 2019 06:59:36 -0500
Received: from pps.filterd (m0098396.ppops.net [127.0.0.1])
        by mx0a-001b2d01.pphosted.com (8.16.0.42/8.16.0.42) with SMTP id
 xBBBqJSQ136084
        for <kvm@vger.kernel.org>; Wed, 11 Dec 2019 06:59:35 -0500
Received: from e06smtp02.uk.ibm.com (e06smtp02.uk.ibm.com [195.75.94.98])
        by mx0a-001b2d01.pphosted.com with ESMTP id 2wtfbxag8u-1
        (version=TLSv1.2 cipher=AES256-GCM-SHA384 bits=256 verify=NOT)
        for <kvm@vger.kernel.org>; Wed, 11 Dec 2019 06:59:34 -0500
Received: from localhost
        by e06smtp02.uk.ibm.com with IBM ESMTP SMTP Gateway: Authorized Use
 Only! Violators will be prosecuted
        for <kvm@vger.kernel.org> from <frankja@linux.ibm.com>;
        Wed, 11 Dec 2019 11:59:32 -0000
Received: from b06cxnps4074.portsmouth.uk.ibm.com (9.149.109.196)
        by e06smtp02.uk.ibm.com (192.168.101.132) with IBM ESMTP SMTP Gateway:
 Authorized Use Only! Violators will be prosecuted;
        (version=TLSv1/SSLv3 cipher=AES256-GCM-SHA384 bits=256/256)
        Wed, 11 Dec 2019 11:59:30 -0000
Received: from d06av24.portsmouth.uk.ibm.com (mk.ibm.com [9.149.105.60])
        by b06cxnps4074.portsmouth.uk.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id xBBBxTQi19529826
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Wed, 11 Dec 2019 11:59:29 GMT
Received: from d06av24.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id D489F42041;
        Wed, 11 Dec 2019 11:59:29 +0000 (GMT)
Received: from d06av24.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 26CFC4203F;
        Wed, 11 Dec 2019 11:59:29 +0000 (GMT)
Received: from localhost.localdomain (unknown [9.152.224.149])
        by d06av24.portsmouth.uk.ibm.com (Postfix) with ESMTP;
        Wed, 11 Dec 2019 11:59:29 +0000 (GMT)
From: Janosch Frank <frankja@linux.ibm.com>
To: kvm@vger.kernel.org
Cc: thuth@redhat.com, david@redhat.com, linux-s390@vger.kernel.org
Subject: [kvm-unit-tests PATCH 1/2] s390x: smp: Use full PSW to bringup new
 cpu
Date: Wed, 11 Dec 2019 06:59:22 -0500
X-Mailer: git-send-email 2.20.1
In-Reply-To: <20191211115923.9191-1-frankja@linux.ibm.com>
References: <20191211115923.9191-1-frankja@linux.ibm.com>
MIME-Version: 1.0
X-TM-AS-GCONF: 00
x-cbid: 19121111-0008-0000-0000-0000033FC7E6
X-IBM-AV-DETECTION: SAVI=unused REMOTE=unused XFE=unused
x-cbparentid: 19121111-0009-0000-0000-00004A5EFDDA
Message-Id: <20191211115923.9191-2-frankja@linux.ibm.com>
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.95,18.0.572
 definitions=2019-12-11_02:2019-12-11,2019-12-11 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 suspectscore=1 spamscore=0
 mlxlogscore=818 malwarescore=0 phishscore=0 priorityscore=1501 bulkscore=0
 adultscore=0 mlxscore=0 lowpriorityscore=0 clxscore=1015 impostorscore=0
 classifier=spam adjust=0 reason=mlx scancount=1 engine=8.12.0-1910280000
 definitions=main-1912110103
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Up to now we ignored the psw mask and only used the psw address when
bringing up a new cpu. For DAT we need to also load the mask, so let's
do that.

Signed-off-by: Janosch Frank <frankja@linux.ibm.com>
Reviewed-by: David Hildenbrand <david@redhat.com>
---
 lib/s390x/smp.c  | 2 ++
 s390x/cstart64.S | 2 +-
 2 files changed, 3 insertions(+), 1 deletion(-)

```
#### [kvm-unit-tests PATCH v4 1/9] s390x: saving regs for interrupts
##### From: Pierre Morel <pmorel@linux.ibm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Pierre Morel <pmorel@linux.ibm.com>
X-Patchwork-Id: 11285505
Return-Path: <SRS0=dbDR=2B=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 3C54E14BD
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 11 Dec 2019 15:46:33 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 24265208C3
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 11 Dec 2019 15:46:33 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2388765AbfLKPqb (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 11 Dec 2019 10:46:31 -0500
Received: from mx0a-001b2d01.pphosted.com ([148.163.156.1]:20048 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S2388743AbfLKPqS (ORCPT
        <rfc822;kvm@vger.kernel.org>); Wed, 11 Dec 2019 10:46:18 -0500
Received: from pps.filterd (m0098410.ppops.net [127.0.0.1])
        by mx0a-001b2d01.pphosted.com (8.16.0.42/8.16.0.42) with SMTP id
 xBBFhRV5041237
        for <kvm@vger.kernel.org>; Wed, 11 Dec 2019 10:46:18 -0500
Received: from e06smtp04.uk.ibm.com (e06smtp04.uk.ibm.com [195.75.94.100])
        by mx0a-001b2d01.pphosted.com with ESMTP id 2wsrdqag9p-1
        (version=TLSv1.2 cipher=AES256-GCM-SHA384 bits=256 verify=NOT)
        for <kvm@vger.kernel.org>; Wed, 11 Dec 2019 10:46:17 -0500
Received: from localhost
        by e06smtp04.uk.ibm.com with IBM ESMTP SMTP Gateway: Authorized Use
 Only! Violators will be prosecuted
        for <kvm@vger.kernel.org> from <pmorel@linux.ibm.com>;
        Wed, 11 Dec 2019 15:46:15 -0000
Received: from b06cxnps3074.portsmouth.uk.ibm.com (9.149.109.194)
        by e06smtp04.uk.ibm.com (192.168.101.134) with IBM ESMTP SMTP Gateway:
 Authorized Use Only! Violators will be prosecuted;
        (version=TLSv1/SSLv3 cipher=AES256-GCM-SHA384 bits=256/256)
        Wed, 11 Dec 2019 15:46:12 -0000
Received: from d06av22.portsmouth.uk.ibm.com (d06av22.portsmouth.uk.ibm.com
 [9.149.105.58])
        by b06cxnps3074.portsmouth.uk.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id xBBFkBFc40435914
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Wed, 11 Dec 2019 15:46:11 GMT
Received: from d06av22.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 396814C059;
        Wed, 11 Dec 2019 15:46:11 +0000 (GMT)
Received: from d06av22.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 0B0E14C040;
        Wed, 11 Dec 2019 15:46:11 +0000 (GMT)
Received: from oc3016276355.ibm.com (unknown [9.152.222.89])
        by d06av22.portsmouth.uk.ibm.com (Postfix) with ESMTP;
        Wed, 11 Dec 2019 15:46:10 +0000 (GMT)
From: Pierre Morel <pmorel@linux.ibm.com>
To: kvm@vger.kernel.org
Cc: linux-s390@vger.kernel.org, frankja@linux.ibm.com,
        david@redhat.com, thuth@redhat.com, cohuck@redhat.com
Subject: [kvm-unit-tests PATCH v4 1/9] s390x: saving regs for interrupts
Date: Wed, 11 Dec 2019 16:46:02 +0100
X-Mailer: git-send-email 1.8.3.1
In-Reply-To: <1576079170-7244-1-git-send-email-pmorel@linux.ibm.com>
References: <1576079170-7244-1-git-send-email-pmorel@linux.ibm.com>
X-TM-AS-GCONF: 00
x-cbid: 19121115-0016-0000-0000-000002D3DDDB
X-IBM-AV-DETECTION: SAVI=unused REMOTE=unused XFE=unused
x-cbparentid: 19121115-0017-0000-0000-00003335FDD5
Message-Id: <1576079170-7244-2-git-send-email-pmorel@linux.ibm.com>
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.95,18.0.572
 definitions=2019-12-11_04:2019-12-11,2019-12-11 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 spamscore=0 phishscore=0
 impostorscore=0 mlxlogscore=694 priorityscore=1501 adultscore=0
 bulkscore=0 mlxscore=0 malwarescore=0 suspectscore=1 lowpriorityscore=0
 clxscore=1015 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.12.0-1910280000 definitions=main-1912110132
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

If we use multiple source of interrupts, for exemple, using SCLP
console to print information while using I/O interrupts, we need
to have a re-entrant register saving interruption handling.

Instead of saving at a static memory address, let's save the base
registers and the floating point registers on the stack.

Note that we keep the static register saving to recover from the
RESET tests.

Signed-off-by: Pierre Morel <pmorel@linux.ibm.com>
---
 s390x/cstart64.S | 25 +++++++++++++++++++++++--
 1 file changed, 23 insertions(+), 2 deletions(-)

```
#### [PATCH v3 1/6] iommu/vt-d: Identify domains using first level page table
##### From: Lu Baolu <baolu.lu@linux.intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Lu Baolu <baolu.lu@linux.intel.com>
X-Patchwork-Id: 11283745
Return-Path: <SRS0=dbDR=2B=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 92204930
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 11 Dec 2019 02:13:20 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 7AB4B206EC
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 11 Dec 2019 02:13:20 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727571AbfLKCNT (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 10 Dec 2019 21:13:19 -0500
Received: from mga04.intel.com ([192.55.52.120]:52878 "EHLO mga04.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1727536AbfLKCNT (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 10 Dec 2019 21:13:19 -0500
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from orsmga002.jf.intel.com ([10.7.209.21])
  by fmsmga104.fm.intel.com with ESMTP/TLS/DHE-RSA-AES256-GCM-SHA384;
 10 Dec 2019 18:13:18 -0800
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.69,301,1571727600";
   d="scan'208";a="225352983"
Received: from allen-box.sh.intel.com ([10.239.159.136])
  by orsmga002.jf.intel.com with ESMTP; 10 Dec 2019 18:13:15 -0800
From: Lu Baolu <baolu.lu@linux.intel.com>
To: Joerg Roedel <joro@8bytes.org>,
        David Woodhouse <dwmw2@infradead.org>,
        Alex Williamson <alex.williamson@redhat.com>
Cc: ashok.raj@intel.com, sanjay.k.kumar@intel.com,
        jacob.jun.pan@linux.intel.com, kevin.tian@intel.com,
        yi.l.liu@intel.com, yi.y.sun@intel.com,
        Peter Xu <peterx@redhat.com>, iommu@lists.linux-foundation.org,
        kvm@vger.kernel.org, linux-kernel@vger.kernel.org,
        Lu Baolu <baolu.lu@linux.intel.com>
Subject: [PATCH v3 1/6] iommu/vt-d: Identify domains using first level page
 table
Date: Wed, 11 Dec 2019 10:12:14 +0800
Message-Id: <20191211021219.8997-2-baolu.lu@linux.intel.com>
X-Mailer: git-send-email 2.17.1
In-Reply-To: <20191211021219.8997-1-baolu.lu@linux.intel.com>
References: <20191211021219.8997-1-baolu.lu@linux.intel.com>
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This checks whether a domain should use the first level page
table for map/unmap and marks it in the domain structure.

Signed-off-by: Lu Baolu <baolu.lu@linux.intel.com>
---
 drivers/iommu/intel-iommu.c | 39 +++++++++++++++++++++++++++++++++++++
 1 file changed, 39 insertions(+)

```
