#### [kvm-unit-tests PATCH v4 01/11] lib: arm/arm64: gicv3: Add missing barrier when sending IPIs
##### From: Alexandru Elisei <alexandru.elisei@arm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Alexandru Elisei <alexandru.elisei@arm.com>
X-Patchwork-Id: 12095283
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.8 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED,USER_AGENT_GIT
	autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 13CCBC433DB
	for <kvm@archiver.kernel.org>; Fri, 19 Feb 2021 12:14:30 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id B692A64EB8
	for <kvm@archiver.kernel.org>; Fri, 19 Feb 2021 12:14:29 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S230357AbhBSMO2 (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Fri, 19 Feb 2021 07:14:28 -0500
Received: from foss.arm.com ([217.140.110.172]:35018 "EHLO foss.arm.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S229959AbhBSMOV (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 19 Feb 2021 07:14:21 -0500
Received: from usa-sjc-imap-foss1.foss.arm.com (unknown [10.121.207.14])
        by usa-sjc-mx-foss1.foss.arm.com (Postfix) with ESMTP id AE656106F;
        Fri, 19 Feb 2021 04:13:34 -0800 (PST)
Received: from monolith.localdoman (unknown [172.31.20.19])
        by usa-sjc-imap-foss1.foss.arm.com (Postfix) with ESMTPSA id
 D0CCB3F73B;
        Fri, 19 Feb 2021 04:13:33 -0800 (PST)
From: Alexandru Elisei <alexandru.elisei@arm.com>
To: drjones@redhat.com, kvm@vger.kernel.org,
        kvmarm@lists.cs.columbia.edu
Cc: andre.przywara@arm.com, eric.auger@redhat.com
Subject: [kvm-unit-tests PATCH v4 01/11] lib: arm/arm64: gicv3: Add missing
 barrier when sending IPIs
Date: Fri, 19 Feb 2021 12:13:27 +0000
Message-Id: <20210219121337.76533-2-alexandru.elisei@arm.com>
X-Mailer: git-send-email 2.30.1
In-Reply-To: <20210219121337.76533-1-alexandru.elisei@arm.com>
References: <20210219121337.76533-1-alexandru.elisei@arm.com>
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

One common usage for IPIs is for one CPU to write to a shared memory
location, send the IPI to kick another CPU, and the receiver to read from
the same location. Proper synchronization is needed to make sure that the
IPI receiver reads the most recent value and not stale data (for example,
the write from the sender CPU might still be in a store buffer).

For GICv3, IPIs are generated with a write to the ICC_SGI1R_EL1 register.
To make sure the memory stores are observable by other CPUs, we need a
wmb() barrier (DSB ST), which waits for stores to complete.

From the definition of DSB from ARM DDI 0487F.b, page B2-139:

"In addition, no instruction that appears in program order after the DSB
instruction can alter any state of the system or perform any part of its
functionality until the DSB completes other than:

- Being fetched from memory and decoded.
- Reading the general-purpose, SIMD and floating-point, Special-purpose, or
System registers that are directly or indirectly read without causing
side-effects."

Similar definition for armv7 (ARM DDI 0406C.d, page A3-150).

The DSB instruction is enough to prevent reordering of the GIC register
write which comes in program order after the memory access.

This also matches what the Linux GICv3 irqchip driver does (commit
21ec30c0ef52 ("irqchip/gic-v3: Use wmb() instead of smb_wmb() in
gic_raise_softirq()")).

Reviewed-by: Eric Auger <eric.auger@redhat.com>
Reviewed-by: Andre Przywara <andre.przywara@arm.com>
Signed-off-by: Alexandru Elisei <alexandru.elisei@arm.com>
---
 lib/arm/gic-v3.c | 6 ++++++
 arm/gic.c        | 5 +++++
 2 files changed, 11 insertions(+)

```
#### [PATCH v2 01/11] accel/kvm: Check MachineClass kvm_type() return value
##### From: =?utf-8?q?Philippe_Mathieu-Daud=C3=A9?= <philmd@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 8bit
X-Patchwork-Submitter: =?utf-8?q?Philippe_Mathieu-Daud=C3=A9?=
 <philmd@redhat.com>
X-Patchwork-Id: 12095913
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-18.8 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_CR_TRAILER,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,
	USER_AGENT_GIT autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 3EB98C433E0
	for <kvm@archiver.kernel.org>; Fri, 19 Feb 2021 17:40:31 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id E760660295
	for <kvm@archiver.kernel.org>; Fri, 19 Feb 2021 17:40:30 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S229840AbhBSRka (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Fri, 19 Feb 2021 12:40:30 -0500
Received: from us-smtp-delivery-124.mimecast.com ([63.128.21.124]:57693 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S229658AbhBSRk2 (ORCPT
        <rfc822;kvm@vger.kernel.org>); Fri, 19 Feb 2021 12:40:28 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1613756342;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:content-type:content-type:
         content-transfer-encoding:content-transfer-encoding:
         in-reply-to:in-reply-to:references:references;
        bh=98X4DsBNdk1BN09KWcHx0mE3/gzzTZdKxOLSGajyIeI=;
        b=f+zaNRcDyHOGFgQzgmzI1vGQTqanXW+HRFwydtdmYIhDR12kw6EKpXwgZZaeWwq4mSSmMr
        QqjjZCx6PUXvPzANDqTKL7piZRIfBn5rFhCQcEm3zsxEK0eTgXt4Nw317mbdED25dOmSMK
        iHDM9R7tJdN7IxfnkKj20TsYZTc8I0U=
Received: from mail-wm1-f72.google.com (mail-wm1-f72.google.com
 [209.85.128.72]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-410-LrRgB1XcMSit_nQi_B59-Q-1; Fri, 19 Feb 2021 12:38:58 -0500
X-MC-Unique: LrRgB1XcMSit_nQi_B59-Q-1
Received: by mail-wm1-f72.google.com with SMTP id j204so2793868wmj.4
        for <kvm@vger.kernel.org>; Fri, 19 Feb 2021 09:38:57 -0800 (PST)
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:in-reply-to
         :references:mime-version:content-transfer-encoding;
        bh=98X4DsBNdk1BN09KWcHx0mE3/gzzTZdKxOLSGajyIeI=;
        b=PjHVjDJ9iBnbLTf2yoqML5R70DRfSc+fgfeg8xtBkU2/HtpwnL9EWBqKgZFTnSDRdW
         vpJaLo2rAenGCabd8hYSkCLths1wu2Dw9VsJ1xvmSvKU0AODuJny4S7ZXrZRVsOvNCud
         8+O3Emjaw8WEwLxb8pbDhOtVm5Xdl03koeQpFMoIgs6mcqTEQqnfiEatTshmwYNMpoMo
         1OoZtN3whqK+0vJJnD++AD3PFPaSdzOsg34ZP9lr8if9X3Wz3yMvhBP7CnQ75EHfyQsV
         sOz6m/yzDDRkBF/j8NzkbRILyGqPgaDmSHZzL4ULkBvb+2na17X7YOTO3cLF4DBdN8L5
         cTjw==
X-Gm-Message-State: AOAM532DvAsnpT7XXU9cJJJ4Ih0JZ1shr7SQTFqISpRxK0gj7z1UeJ1J
        7XbGcL/kaWyY7ZOg2Z0N+kt25PLMWG8Y+4jsLvegcDq1VKumnS+4O/wlNMj4sRfIo83lx0WCqY8
        H6VMKY6Nrtrff
X-Received: by 2002:adf:b60f:: with SMTP id f15mr10395981wre.83.1613756336824;
        Fri, 19 Feb 2021 09:38:56 -0800 (PST)
X-Google-Smtp-Source: 
 ABdhPJzk+AP79F8l3TWLxyR5RU8SmferiSbz3yhDIC5dQKM04uA2QaqDVPRO6H3UVoBxcUQFmDZVKw==
X-Received: by 2002:adf:b60f:: with SMTP id f15mr10395942wre.83.1613756336683;
        Fri, 19 Feb 2021 09:38:56 -0800 (PST)
Received: from localhost.localdomain (68.red-83-57-175.dynamicip.rima-tde.net.
 [83.57.175.68])
        by smtp.gmail.com with ESMTPSA id
 i7sm23525949wmq.2.2021.02.19.09.38.54
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Fri, 19 Feb 2021 09:38:56 -0800 (PST)
From: =?utf-8?q?Philippe_Mathieu-Daud=C3=A9?= <philmd@redhat.com>
To: qemu-devel@nongnu.org
Cc: Aurelien Jarno <aurelien@aurel32.net>,
 Peter Maydell <peter.maydell@linaro.org>,
 Anthony Perard <anthony.perard@citrix.com>, qemu-ppc@nongnu.org,
 qemu-s390x@nongnu.org, Halil Pasic <pasic@linux.ibm.com>,
 Huacai Chen <chenhuacai@kernel.org>, xen-devel@lists.xenproject.org,
 Marcel Apfelbaum <marcel.apfelbaum@gmail.com>,
 David Gibson <david@gibson.dropbear.id.au>, qemu-arm@nongnu.org,
 Stefano Stabellini <sstabellini@kernel.org>,
 Paolo Bonzini <pbonzini@redhat.com>, kvm@vger.kernel.org,
 BALATON Zoltan <balaton@eik.bme.hu>, Leif Lindholm <leif@nuviainc.com>,
 Richard Henderson <richard.henderson@linaro.org>,
 Radoslaw Biernacki <rad@semihalf.com>,
 Alistair Francis <alistair@alistair23.me>, Paul Durrant <paul@xen.org>,
 Eduardo Habkost <ehabkost@redhat.com>, "Michael S. Tsirkin" <mst@redhat.com>,
 Thomas Huth <thuth@redhat.com>, Jiaxun Yang <jiaxun.yang@flygoat.com>,
	=?utf-8?q?Herv=C3=A9_Poussineau?= <hpoussin@reactos.org>,
 Greg Kurz <groug@kaod.org>, Christian Borntraeger <borntraeger@de.ibm.com>,
 Cornelia Huck <cohuck@redhat.com>,
 "Edgar E. Iglesias" <edgar.iglesias@gmail.com>,
 David Hildenbrand <david@redhat.com>,
 Mark Cave-Ayland <mark.cave-ayland@ilande.co.uk>,
 Aleksandar Rikalo <aleksandar.rikalo@syrmia.com>, =?utf-8?q?Philippe_Mathie?=
	=?utf-8?q?u-Daud=C3=A9?= <f4bug@amsat.org>, =?utf-8?q?Philippe_Mathieu-Daud?=
	=?utf-8?q?=C3=A9?= <philmd@redhat.com>
Subject: [PATCH v2 01/11] accel/kvm: Check MachineClass kvm_type() return
 value
Date: Fri, 19 Feb 2021 18:38:37 +0100
Message-Id: <20210219173847.2054123-2-philmd@redhat.com>
X-Mailer: git-send-email 2.26.2
In-Reply-To: <20210219173847.2054123-1-philmd@redhat.com>
References: <20210219173847.2054123-1-philmd@redhat.com>
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

MachineClass::kvm_type() can return -1 on failure.
Document it, and add a check in kvm_init().

Signed-off-by: Philippe Mathieu-Daudé <philmd@redhat.com>
---
 include/hw/boards.h | 3 ++-
 accel/kvm/kvm-all.c | 6 ++++++
 2 files changed, 8 insertions(+), 1 deletion(-)

```
#### [PATCH 1/7] accel/kvm: Check MachineClass kvm_type() return value
##### From: =?utf-8?q?Philippe_Mathieu-Daud=C3=A9?= <philmd@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 8bit
X-Patchwork-Submitter: =?utf-8?q?Philippe_Mathieu-Daud=C3=A9?=
 <philmd@redhat.com>
X-Patchwork-Id: 12095123
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-18.8 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_CR_TRAILER,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,
	USER_AGENT_GIT autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id B175BC433DB
	for <kvm@archiver.kernel.org>; Fri, 19 Feb 2021 11:46:30 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 69CF364EC0
	for <kvm@archiver.kernel.org>; Fri, 19 Feb 2021 11:46:30 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S230378AbhBSLqJ (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Fri, 19 Feb 2021 06:46:09 -0500
Received: from us-smtp-delivery-124.mimecast.com ([63.128.21.124]:59273 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S230308AbhBSLqH (ORCPT
        <rfc822;kvm@vger.kernel.org>); Fri, 19 Feb 2021 06:46:07 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1613735080;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:content-type:content-type:
         content-transfer-encoding:content-transfer-encoding:
         in-reply-to:in-reply-to:references:references;
        bh=98X4DsBNdk1BN09KWcHx0mE3/gzzTZdKxOLSGajyIeI=;
        b=NtMesX1+Zeqvpm9/jZNRgi1h4EN5bIYdcec9PvD9MpsI067OC7+Ra5jscK2053LG5ADn02
        ekJcpy94Oj5PTsbjMqUN8nO2Z96s9GddyUWYUK98lpmDGPq69H171LQ6jT+YtPC1Z8K52z
        4GSvGFKhHf+SvH375bFUqbRhSelBBow=
Received: from mail-wm1-f71.google.com (mail-wm1-f71.google.com
 [209.85.128.71]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-508-RpR5mxJUPa-9twbBIAnbmQ-1; Fri, 19 Feb 2021 06:44:38 -0500
X-MC-Unique: RpR5mxJUPa-9twbBIAnbmQ-1
Received: by mail-wm1-f71.google.com with SMTP id b201so2353510wmb.9
        for <kvm@vger.kernel.org>; Fri, 19 Feb 2021 03:44:38 -0800 (PST)
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:in-reply-to
         :references:mime-version:content-transfer-encoding;
        bh=98X4DsBNdk1BN09KWcHx0mE3/gzzTZdKxOLSGajyIeI=;
        b=bo8O9xJsG0C37oRFi51piBi3j4+HUu8p182tmWi1O/23aL7GnO77GX9tIkFNRqkuEn
         X2ICIroGFP3Ms9Dna5/bppa0oNLn3K2pNWUAQoSwN/4yMif/54yzPpuIxsrgsQX/RIAI
         RnTaNR7FEBsVQyiTMJFBb3KbSNgSbCzjEKKqhYkD5NP19k+j2mTZkOZWawEHhoKmpcmB
         UZTkLYS/RFLbPpw53tWkPXT8sVR4nZ2OpSWuCaiWM9Gzjvx1gYH9y5My8flQ1UsgKPwM
         FfneMsAfhRqwMJagpDccHFZpn4QkiTd7KFhxE1NzYTTme0hU4BCd87oAaZLyGBlgDVjE
         cI+A==
X-Gm-Message-State: AOAM530yX+t3SPgdKOFH8iDrzmxYi7Mpqilg8USD28TZuIta7MzuN8cQ
        XhjWGYA9tly5+TdpBo7/zMMx6ayrWSZeRYG30OaV6r0hTEurR9dTs4Va3u+1dNJH94OXAf9qn3B
        KLOujmeqS3Maa
X-Received: by 2002:adf:b357:: with SMTP id k23mr8694387wrd.354.1613735077426;
        Fri, 19 Feb 2021 03:44:37 -0800 (PST)
X-Google-Smtp-Source: 
 ABdhPJy8BoyDIy3MZrDx4a9/uBNg8Gu4uQrRfjBpdhkb1HenxWvZ3lMMW1roaXGxl/Jsmb64BZpXBA==
X-Received: by 2002:adf:b357:: with SMTP id k23mr8694350wrd.354.1613735077292;
        Fri, 19 Feb 2021 03:44:37 -0800 (PST)
Received: from localhost.localdomain (68.red-83-57-175.dynamicip.rima-tde.net.
 [83.57.175.68])
        by smtp.gmail.com with ESMTPSA id
 w81sm11424135wmb.3.2021.02.19.03.44.35
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Fri, 19 Feb 2021 03:44:36 -0800 (PST)
From: =?utf-8?q?Philippe_Mathieu-Daud=C3=A9?= <philmd@redhat.com>
To: qemu-devel@nongnu.org
Cc: Radoslaw Biernacki <rad@semihalf.com>,
 Paolo Bonzini <pbonzini@redhat.com>, qemu-s390x@nongnu.org,
 Greg Kurz <groug@kaod.org>, Marcel Apfelbaum <marcel.apfelbaum@gmail.com>,
 qemu-arm@nongnu.org, Cornelia Huck <cohuck@redhat.com>,
 Aleksandar Rikalo <aleksandar.rikalo@syrmia.com>, =?utf-8?q?Philippe_Mathie?=
	=?utf-8?q?u-Daud=C3=A9?= <f4bug@amsat.org>,
 BALATON Zoltan <balaton@eik.bme.hu>, Huacai Chen <chenhuacai@kernel.org>,
 Aurelien Jarno <aurelien@aurel32.net>,
 Richard Henderson <richard.henderson@linaro.org>,
 "Edgar E. Iglesias" <edgar.iglesias@gmail.com>,
 Christian Borntraeger <borntraeger@de.ibm.com>,
 Leif Lindholm <leif@nuviainc.com>, Alistair Francis <alistair@alistair23.me>,
 Thomas Huth <thuth@redhat.com>, Peter Maydell <peter.maydell@linaro.org>,
 Eduardo Habkost <ehabkost@redhat.com>, Jiaxun Yang <jiaxun.yang@flygoat.com>,
 Halil Pasic <pasic@linux.ibm.com>, David Hildenbrand <david@redhat.com>,
 qemu-ppc@nongnu.org,
 =?utf-8?q?Herv=C3=A9_Poussineau?= <hpoussin@reactos.org>,
 David Gibson <david@gibson.dropbear.id.au>,
 Mark Cave-Ayland <mark.cave-ayland@ilande.co.uk>, kvm@vger.kernel.org,
	=?utf-8?q?Philippe_Mathieu-Daud=C3=A9?= <philmd@redhat.com>
Subject: [PATCH 1/7] accel/kvm: Check MachineClass kvm_type() return value
Date: Fri, 19 Feb 2021 12:44:22 +0100
Message-Id: <20210219114428.1936109-2-philmd@redhat.com>
X-Mailer: git-send-email 2.26.2
In-Reply-To: <20210219114428.1936109-1-philmd@redhat.com>
References: <20210219114428.1936109-1-philmd@redhat.com>
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

MachineClass::kvm_type() can return -1 on failure.
Document it, and add a check in kvm_init().

Signed-off-by: Philippe Mathieu-Daudé <philmd@redhat.com>
---
 include/hw/boards.h | 3 ++-
 accel/kvm/kvm-all.c | 6 ++++++
 2 files changed, 8 insertions(+), 1 deletion(-)

```
#### [kvm-unit-tests PATCH] configure: arm/arm64: Add --earlycon option to set UART type and address
##### From: Alexandru Elisei <alexandru.elisei@arm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Alexandru Elisei <alexandru.elisei@arm.com>
X-Patchwork-Id: 12095831
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.8 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED,USER_AGENT_GIT
	autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 7C660C433DB
	for <kvm@archiver.kernel.org>; Fri, 19 Feb 2021 16:37:59 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 4975E64E44
	for <kvm@archiver.kernel.org>; Fri, 19 Feb 2021 16:37:59 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S229979AbhBSQiA (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Fri, 19 Feb 2021 11:38:00 -0500
Received: from foss.arm.com ([217.140.110.172]:40128 "EHLO foss.arm.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S229734AbhBSQhz (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 19 Feb 2021 11:37:55 -0500
Received: from usa-sjc-imap-foss1.foss.arm.com (unknown [10.121.207.14])
        by usa-sjc-mx-foss1.foss.arm.com (Postfix) with ESMTP id C8734ED1;
        Fri, 19 Feb 2021 08:37:07 -0800 (PST)
Received: from monolith.localdoman (unknown [172.31.20.19])
        by usa-sjc-imap-foss1.foss.arm.com (Postfix) with ESMTPSA id
 144FE3F73B;
        Fri, 19 Feb 2021 08:37:06 -0800 (PST)
From: Alexandru Elisei <alexandru.elisei@arm.com>
To: drjones@redhat.com, kvm@vger.kernel.org,
        kvmarm@lists.cs.columbia.edu
Cc: pbonzini@redhat.com
Subject: [kvm-unit-tests PATCH] configure: arm/arm64: Add --earlycon option to
 set UART type and address
Date: Fri, 19 Feb 2021 16:37:18 +0000
Message-Id: <20210219163718.109101-1-alexandru.elisei@arm.com>
X-Mailer: git-send-email 2.30.1
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Currently, the UART early address is set indirectly with the --vmm option
and there are only two possible values: if the VMM is qemu (the default),
then the UART address is set to 0x09000000; if the VMM is kvmtool, then the
UART address is set to 0x3f8.

There several efforts under way to change the kvmtool UART address, and
kvm-unit-tests so far hasn't had mechanism to let the user set a specific
address, which means that the early UART won't be available.

This situation will only become worse as kvm-unit-tests gains support to
run as an EFI app, as each platform will have their own UART type and
address.

To address both issues, a new configure option is added, --earlycon. The
syntax and semantics are identical to the kernel parameter with the same
name. Specifying this option will overwrite the UART address set by --vmm.

At the moment, the UART type and register width parameters are ignored
since both qemu's and kvmtool's UART emulation use the same offset for the
TX register and no other registers are used by kvm-unit-tests, but the
parameters will become relevant once EFI support is added.

Signed-off-by: Alexandru Elisei <alexandru.elisei@arm.com>
---
The kvmtool patches I was referring to are the patches to unify ioport and
MMIO emulation [1] and to allow the user to specify a custom memory layout
for the VM [2] (these patches are very old, but I plan to revive them after
the ioport and MMIO unification series are merged).

[1] https://lore.kernel.org/kvm/20201210142908.169597-1-andre.przywara@arm.com/T/#t
[2] https://lore.kernel.org/kvm/1569245722-23375-1-git-send-email-alexandru.elisei@arm.com/

 configure | 35 +++++++++++++++++++++++++++++++++++
 1 file changed, 35 insertions(+)

```
#### [PATCH v2 1/3] KVM: x86: dump_vmcs should not assume GUEST_IA32_EFER is valid
##### From: David Edmondson <david.edmondson@oracle.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: David Edmondson <david.edmondson@oracle.com>
X-Patchwork-Id: 12095527
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-18.7 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,
	INCLUDES_PATCH,MAILING_LIST_MULTI,MSGID_FROM_MTA_HEADER,SPF_HELO_NONE,
	SPF_PASS,UNPARSEABLE_RELAY,USER_AGENT_GIT autolearn=unavailable
	autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id E3885C433E0
	for <kvm@archiver.kernel.org>; Fri, 19 Feb 2021 14:49:06 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id A9CA264EB2
	for <kvm@archiver.kernel.org>; Fri, 19 Feb 2021 14:49:06 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S229850AbhBSOst (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Fri, 19 Feb 2021 09:48:49 -0500
Received: from aserp2120.oracle.com ([141.146.126.78]:52406 "EHLO
        aserp2120.oracle.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S229587AbhBSOsh (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 19 Feb 2021 09:48:37 -0500
Received: from pps.filterd (aserp2120.oracle.com [127.0.0.1])
        by aserp2120.oracle.com (8.16.0.42/8.16.0.42) with SMTP id
 11JEiHRq111906;
        Fri, 19 Feb 2021 14:46:44 GMT
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=oracle.com;
 h=from : to : cc :
 subject : date : message-id : in-reply-to : references :
 content-transfer-encoding : content-type : mime-version;
 s=corp-2020-01-29; bh=qSdaWzW5cW8G5XAjhyJLFR1zacYsNYVnJkFu9y6tB2I=;
 b=nlVoSlsWhwtDHZdpxgKxONsmwNRgkIbSi7BMwbuURH6Fxf1c82xvgjRJsNRtf+egJnNT
 2sZZ2ZG17dMski+LvfXb6Ulk2mhPk4nx8y5GyOALR9rOT644FfuHDekeIkkcPePWCJNg
 uG8HTb0v99X8p6InRpuhjs9KByiBVl1aNTy/qXfweZdURJHjLdBzJFg76uVzLc8kHtym
 hZsqtG+Opq1haKEQAwXdJV1EUQ6lgBhHydBPXkagQslKS9jMG3ED5+jG/LyfzX11b/Xk
 Z64AljQ3YZ+yOerAOIX4X+mi+G2ajqUWC3ECw2dpmsfH+fWMweohbh12i2ljM3nVCAbr Dw==
Received: from aserp3020.oracle.com (aserp3020.oracle.com [141.146.126.70])
        by aserp2120.oracle.com with ESMTP id 36pd9ah87f-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Fri, 19 Feb 2021 14:46:44 +0000
Received: from pps.filterd (aserp3020.oracle.com [127.0.0.1])
        by aserp3020.oracle.com (8.16.0.42/8.16.0.42) with SMTP id
 11JEkKfT112347;
        Fri, 19 Feb 2021 14:46:44 GMT
Received: from nam11-co1-obe.outbound.protection.outlook.com
 (mail-co1nam11lp2177.outbound.protection.outlook.com [104.47.56.177])
        by aserp3020.oracle.com with ESMTP id 36prp2yfsj-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Fri, 19 Feb 2021 14:46:44 +0000
ARC-Seal: i=1; a=rsa-sha256; s=arcselector9901; d=microsoft.com; cv=none;
 b=JFONimb+hmI3GxtrM57orRREZZfySd3s2ill1hRZ3+lplFGNgGfjE/cgyiZKhr/M8w9Qqo4eLqw8s6eJ3yDqKsZ/8EG4xTkacPOTha2YPckVsbyM8fTeA8yGxmBvpvoeqzWMa5Zt5gz7aUtDoYOJ4ofMGrP8tCxDo/bigWJiYlF2ltoDN0j/5lnn7etYH/6SgecDYJXutvrSMezB+fuEe24Imco5WF+7ekW0oNMPGexXdE/2mA4brGSt9AsX3hY9/0fUGpE6GXD84v2hSUb2fC+Deq8q8E+Uiqd201FmN5CVLVWgC7qk0zKoz7lGO29K+1SI6Qqif5nmJAcLR5VeLw==
ARC-Message-Signature: i=1; a=rsa-sha256; c=relaxed/relaxed; d=microsoft.com;
 s=arcselector9901;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=qSdaWzW5cW8G5XAjhyJLFR1zacYsNYVnJkFu9y6tB2I=;
 b=FNUZzcJxvV3xZSgEfpTxXT9NRElOOdEXaTlfBgX4YUIHppJwQ4xtmMYpU45Jk+++KI6aXUUhey/UFrNmf2B4MaDaKRp9OOWgaj9NKMDb9H3r3iDKlw79V3hOjK9OfVi9p+9xIqAWc0I/1BLAIyw22t8qR3rtdUvVYnnSegR+wvESn+6wy7XVjI5iwDsP7+YwW4+FN3UbhRxIXXR3fL2EQCu8LVdsGMAkkK2eCdWstXJnEF7qrzxM7/0oLov3yXzv7IuvbWAWy5sBMYhVJ4yO0t072T6JgDhPi7RTYR4LR0JkdsgG31q5iDWMIy3/4UVm6iSGXblC2kj3UCSz1jeXvg==
ARC-Authentication-Results: i=1; mx.microsoft.com 1; spf=pass
 smtp.mailfrom=oracle.com; dmarc=pass action=none header.from=oracle.com;
 dkim=pass header.d=oracle.com; arc=none
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
 d=oracle.onmicrosoft.com; s=selector2-oracle-onmicrosoft-com;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=qSdaWzW5cW8G5XAjhyJLFR1zacYsNYVnJkFu9y6tB2I=;
 b=vEQB7x98m57fW4peUP8SYQMxNxnAihq4UfINySnCdW2wxBcCklL0kd9Nnv3s3mOylfIK8MQsRuZaO9+Ufw3srxYBR3zqf7ADFIhkUVoWV6Fj1GqFJTF/1R43Ki7VvLZhKQs5J7T6Xhni9rjYf71YuoB7bKjpM23WzfWTPgHH6Ts=
Authentication-Results: redhat.com; dkim=none (message not signed)
 header.d=none;redhat.com; dmarc=none action=none header.from=oracle.com;
Received: from DM6PR10MB3148.namprd10.prod.outlook.com (2603:10b6:5:1a4::21)
 by DS7PR10MB5280.namprd10.prod.outlook.com (2603:10b6:5:3a7::5) with
 Microsoft SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.3846.27; Fri, 19 Feb
 2021 14:46:42 +0000
Received: from DM6PR10MB3148.namprd10.prod.outlook.com
 ([fe80::f871:5965:2081:3934]) by DM6PR10MB3148.namprd10.prod.outlook.com
 ([fe80::f871:5965:2081:3934%5]) with mapi id 15.20.3846.027; Fri, 19 Feb 2021
 14:46:42 +0000
From: David Edmondson <david.edmondson@oracle.com>
To: linux-kernel@vger.kernel.org
Cc: "H. Peter Anvin" <hpa@zytor.com>, Joerg Roedel <joro@8bytes.org>,
        x86@kernel.org, Thomas Gleixner <tglx@linutronix.de>,
        kvm@vger.kernel.org, Paolo Bonzini <pbonzini@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Ingo Molnar <mingo@redhat.com>,
        Sean Christopherson <seanjc@google.com>,
        Jim Mattson <jmattson@google.com>,
        Borislav Petkov <bp@alien8.de>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        David Edmondson <david.edmondson@oracle.com>
Subject: [PATCH v2 1/3] KVM: x86: dump_vmcs should not assume GUEST_IA32_EFER
 is valid
Date: Fri, 19 Feb 2021 14:46:30 +0000
Message-Id: <20210219144632.2288189-2-david.edmondson@oracle.com>
X-Mailer: git-send-email 2.30.0
In-Reply-To: <20210219144632.2288189-1-david.edmondson@oracle.com>
References: <20210219144632.2288189-1-david.edmondson@oracle.com>
X-Originating-IP: [2001:8b0:bb71:7140:64::1]
X-ClientProxiedBy: LO4P123CA0428.GBRP123.PROD.OUTLOOK.COM
 (2603:10a6:600:18b::19) To DM6PR10MB3148.namprd10.prod.outlook.com
 (2603:10b6:5:1a4::21)
MIME-Version: 1.0
X-MS-Exchange-MessageSentRepresentingType: 1
Received: from disaster-area.hh.sledj.net (2001:8b0:bb71:7140:64::1) by
 LO4P123CA0428.GBRP123.PROD.OUTLOOK.COM (2603:10a6:600:18b::19) with Microsoft
 SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.3846.38 via Frontend
 Transport; Fri, 19 Feb 2021 14:46:38 +0000
Received: from localhost (disaster-area.hh.sledj.net [local])   by
 disaster-area.hh.sledj.net (OpenSMTPD) with ESMTPA id e8c9f414;
      Fri, 19 Feb 2021 14:46:32 +0000 (UTC)
X-MS-PublicTrafficType: Email
X-MS-Office365-Filtering-Correlation-Id: 96188673-0a66-41be-454a-08d8d4e52a82
X-MS-TrafficTypeDiagnostic: DS7PR10MB5280:
X-MS-Exchange-Transport-Forked: True
X-Microsoft-Antispam-PRVS: 
 <DS7PR10MB52809B6159B48B198952782288849@DS7PR10MB5280.namprd10.prod.outlook.com>
X-MS-Oob-TLC-OOBClassifiers: OLM:7219;
X-MS-Exchange-SenderADCheck: 1
X-Microsoft-Antispam: BCL:0;
X-Microsoft-Antispam-Message-Info: 
 De37E6NRFGkJ+jqCMb8+uULTi7B5FOoinV9MU0y0C+iQw0kWYjDVHWs6DqfB/jtqMVrKmjkBGvbOiEJGeser48I9aOjow3l+J/88q1LX22lAZUKQok2DyPr1BMyAIvoaKxH6xtGGWlIa1aIpUqRIRrj+5b7lRCr22PiugXFT9wucl+22pgcwvnHyPAHz8tNdMl/d4MRv8m843myEFQZNiD+tSGzXRHtKT/9CKdyJ564x3cyAfirnqmqJ+E7njosjOmKCMuocUq/ss1w5+k+zMMgi1/ySOzLq1DC298IlPirn5buhNAgZOQv6rqT+xrD/Kxv5Xn3FO5J9qFovJuwgaMWjBKSlZ0AtHvizarjBX6NoWh13dkvx491RaKiu01Mn+2ttKqy8cr3DdyFmVKqCzGXDr25WZZ2+nLdifXFcWkrW7hmoxSM6BV+6EFvAGWIJL6psJwryFalAJu0K2OQDiwP0YZZhJcGrArwSN+JwpKpA08Lk6f6kgu/uqA2igEf62gIkagNGmrmnKvel5xgsuA==
X-Forefront-Antispam-Report: 
 CIP:255.255.255.255;CTRY:;LANG:en;SCL:1;SRV:;IPV:NLI;SFV:NSPM;H:DM6PR10MB3148.namprd10.prod.outlook.com;PTR:;CAT:NONE;SFS:(39860400002)(396003)(366004)(136003)(376002)(346002)(86362001)(44832011)(54906003)(316002)(6916009)(2906002)(66556008)(7416002)(8676002)(186003)(8936002)(36756003)(2616005)(52116002)(66946007)(107886003)(1076003)(478600001)(66476007)(5660300002)(4326008)(83380400001);DIR:OUT;SFP:1101;
X-MS-Exchange-AntiSpam-MessageData: 
 IWdMuuZkXJO2bvA9CZzaNc55ajy8vY91uDz9rjCuH3nyYLb7zI2H9HkveHFdnSPk/cTzc91rhwRR53R+3dfq3EZPoV3ErIl3myv5MSEe+3ybceLYEmuXAR9JuB0vRHtHOGqweSESRPifOe1DViY2rfNdYmxT16Ueix74RLDMzLjICRiEtZVzpORzeY3t3nBLNZuH2bwCMRrwDcavjt6XqPE8+HVE/tjQNpybDDwTXLfxl1mNbjJGKgCMkiAwtSH4D0J+BAiUgIuUPfM9OEkW3qxDWEAvK8YT8unSKa3L5p3dSbFALQZ/YjdxYL7lLf+LNJO58Kq9amWO0zccPFDCL3pndbONYZTYVMxQC24z8VINZB+iOE7Pu40zMQRDGUZnyuDIFfinAwjeVji1qxdXgLMJCRFkZgpIdq0NCBCceouWeIEgzW8482e0IwMU985NhLpR1AqLbduytzC9AeEqTRjHqralpncUv/F8Afnyigc4VaK55MQ13IOYem2rs5OwF49r6kOoNLcNKHYONpgFhD2AxUtu/duFTQEZzOTcESdsAOjqcsNNsRwTqkjHX1ZIFsWIdhldhMCWc2EtS+/Znc9XzB3SdKDcQFk6BeaeadPs+cpRZmdudF3uMI46jIkBM/3K1Pkfy6SKP7XPj3CVvKcnyVJnC1KrQQY0mN+CsKEVcWXfdckqSnqCj8x+wUykNNYMDVp0F2cqkBdGhpPtroykz/0A4HXsqCT/7f7/vifKDxTXYOjvrY2QJ82+KUrPqRlUHRS7oDD6Jd8v+uBTUcHaedKTiZ9FKX/UBZOINnNkgJm4BNd/QC9CkaKhAz3kaNY2IXKUSME/hM/y9vVmpvQE/yf6fPrcPbvjWL2nylq5tMpBkLzlA6CRZgbdh32PyXpdJ6FzMt98aC5rXUaB8+Pq/vOrPVLARG81dOazfSTWVRIsLHljOy6uK9m78y0QQioZb9I1WUk3gv9muBAgnVvtTw2VwpwzCRleGAWz+/IjoEpmuc+P+OyYFRFjr9Un8GMx/hzdVjLAonQLQxn2LVSsACpqWBjCEhyR0Cn4+yA3GISGStfuQ0IwX8479m82PSmaJIIOOpquMBWRq8yxuhj1Mc1L+YshGg2yQvgwPagvW3K4944Zz6Nb6L69tFLNlbKTXVBjkDYiDubyxUC+8liOR3GoptnNl81CUMLXczyc1ML3xenlvw6nwqHlZzhVZ0I+XWnWczFg61816GKgdazjXVJiX4Op1niQkNJPH/hgD/TVsqlUyQrvVn3/Yu8YBdDAfvofzY2wZ7/9BxCdF6PH45wOjvhmozZCmRo5EpTU7Je5wn2mN9saSdxiY+Ib5ewHAEn4MPmibS4MqwJNUw==
X-OriginatorOrg: oracle.com
X-MS-Exchange-CrossTenant-Network-Message-Id: 
 96188673-0a66-41be-454a-08d8d4e52a82
X-MS-Exchange-CrossTenant-AuthSource: DM6PR10MB3148.namprd10.prod.outlook.com
X-MS-Exchange-CrossTenant-AuthAs: Internal
X-MS-Exchange-CrossTenant-OriginalArrivalTime: 19 Feb 2021 14:46:42.0562
 (UTC)
X-MS-Exchange-CrossTenant-FromEntityHeader: Hosted
X-MS-Exchange-CrossTenant-Id: 4e2c6054-71cb-48f1-bd6c-3a9705aca71b
X-MS-Exchange-CrossTenant-MailboxType: HOSTED
X-MS-Exchange-CrossTenant-UserPrincipalName: 
 Q3JCiOl+SZicH5ahM7SxzI5C8+XFSJguP/vS/0EwFMo7PB61CI1o8PAztJPMTtV9XjpTIrE0D+BKu6ByssKkI2lp0unEq/0HtgEi9SK7on0=
X-MS-Exchange-Transport-CrossTenantHeadersStamped: DS7PR10MB5280
X-Proofpoint-Virus-Version: vendor=nai engine=6200 definitions=9899
 signatures=668683
X-Proofpoint-Spam-Details: rule=notspam policy=default score=0 phishscore=0
 mlxlogscore=999
 bulkscore=0 suspectscore=0 spamscore=0 malwarescore=0 mlxscore=0
 adultscore=0 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.12.0-2009150000 definitions=main-2102190119
X-Proofpoint-Virus-Version: vendor=nai engine=6200 definitions=9899
 signatures=668683
X-Proofpoint-Spam-Details: rule=notspam policy=default score=0 clxscore=1015
 impostorscore=0
 mlxscore=0 phishscore=0 mlxlogscore=999 spamscore=0 bulkscore=0
 priorityscore=1501 malwarescore=0 suspectscore=0 adultscore=0
 lowpriorityscore=0 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.12.0-2009150000 definitions=main-2102190119
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

If the VM entry/exit controls for loading/saving MSR_EFER are either
not available (an older processor or explicitly disabled) or not
used (host and guest values are the same), reading GUEST_IA32_EFER
from the VMCS returns an inaccurate value.

Because of this, in dump_vmcs() don't use GUEST_IA32_EFER to decide
whether to print the PDPTRs - do so if the EPT is in use and CR4.PAE
is set.

Fixes: 4eb64dce8d0a ("KVM: x86: dump VMCS on invalid entry")
Signed-off-by: David Edmondson <david.edmondson@oracle.com>
---
 arch/x86/kvm/vmx/vmx.c | 8 +++-----
 1 file changed, 3 insertions(+), 5 deletions(-)

```
#### [PATCH v2 1/3] vfio/type1: Change success value of vaddr_get_pfn()
##### From: Daniel Jordan <daniel.m.jordan@oracle.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Daniel Jordan <daniel.m.jordan@oracle.com>
X-Patchwork-Id: 12095819
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-18.8 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,
	INCLUDES_PATCH,MAILING_LIST_MULTI,MSGID_FROM_MTA_HEADER,SPF_HELO_NONE,
	SPF_PASS,USER_AGENT_GIT autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 3891AC433E9
	for <kvm@archiver.kernel.org>; Fri, 19 Feb 2021 16:14:45 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id F19DC64EDB
	for <kvm@archiver.kernel.org>; Fri, 19 Feb 2021 16:14:44 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S229932AbhBSQOg (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Fri, 19 Feb 2021 11:14:36 -0500
Received: from aserp2130.oracle.com ([141.146.126.79]:60424 "EHLO
        aserp2130.oracle.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S229571AbhBSQOX (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 19 Feb 2021 11:14:23 -0500
Received: from pps.filterd (aserp2130.oracle.com [127.0.0.1])
        by aserp2130.oracle.com (8.16.0.42/8.16.0.42) with SMTP id
 11JGARu3064502;
        Fri, 19 Feb 2021 16:13:23 GMT
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=oracle.com;
 h=from : to : cc :
 subject : date : message-id : in-reply-to : references :
 content-transfer-encoding : content-type : mime-version;
 s=corp-2020-01-29; bh=I8Eue09ui4c6W079IE76+/dJP1KETRcPp5O8R310Q7Y=;
 b=ZzKt7nWQr2voo4GyAiFjwJ9WbCmS3nl4PLdp+F44lFt1L6vRNelYlSNmlEM6Ai2algno
 g9kxM5rM15GBpAnI3tuh7XdVl86Bw7SZsbBE/sSOAo3i5GWHn+vjC+ObPQxoS05LMywF
 pukWaJI1rtvicO1fFppE7pcEAzfF8FkzyHXim3qLz1BGpA31bZdSdnc4nt865Pvfhr+U
 r0IZBctLt0QdtxVilessjziRR+FUB8NA2kgAeyAaqpnQahc6bC5JADF3Ri7eMnWUS2iV
 0mIF3ojaQnyuC7OKwocWANcPKze9AtZrBi3cFNSUmaSKcNrmj1gt8xDXbQFTJlfGAS72 oQ==
Received: from aserp3030.oracle.com (aserp3030.oracle.com [141.146.126.71])
        by aserp2130.oracle.com with ESMTP id 36p49bj6ny-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Fri, 19 Feb 2021 16:13:23 +0000
Received: from pps.filterd (aserp3030.oracle.com [127.0.0.1])
        by aserp3030.oracle.com (8.16.0.42/8.16.0.42) with SMTP id
 11JGAWwP166919;
        Fri, 19 Feb 2021 16:13:22 GMT
Received: from nam02-sn1-obe.outbound.protection.outlook.com
 (mail-sn1nam02lp2054.outbound.protection.outlook.com [104.47.36.54])
        by aserp3030.oracle.com with ESMTP id 36prbs9rm0-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Fri, 19 Feb 2021 16:13:22 +0000
ARC-Seal: i=1; a=rsa-sha256; s=arcselector9901; d=microsoft.com; cv=none;
 b=hlxphXNDtnPFdznuchlB36iJ3M8/wZn+gcHa1UemAe52fV35T7cQRZAkLCAg75QmRySWbPn7Ki+S+s2mLLVxYVRSGyVQQnqPtKP6FTVBGaD85uiSRxUUT49kj6axFLt2g/d3zOcipCukxPeEkEEUP0tJjJds4aTgQK5SPdXmcjEUps9GuAbQObhwu/nvE7l3sH+xaRJf5/95lC2o9xw9BfAaJ94AlkUe3LQNy5xJpnc3RHvxT6g5wcr1exDeFcskXULKB1vnxJOrvTFx5TKidr2Q0B1rWULHkS5ahgDGr8euispabCz5/0Ll/0EuxS8xRknZwoeaUOgzuY06VeyAxA==
ARC-Message-Signature: i=1; a=rsa-sha256; c=relaxed/relaxed; d=microsoft.com;
 s=arcselector9901;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=I8Eue09ui4c6W079IE76+/dJP1KETRcPp5O8R310Q7Y=;
 b=cpP3TFknoHN2knVRQcpN7W5JNVx9u5L4Pyg6zpYfZJWCbZ9Sl7fySc4VOJfB6xvBOP4JCwdo6FUHE0mt0ztnPtCpdm922Jyv+SIPteVsaxgaA6bkejfvNdVnm1z3AlVN/kz9Tj5FEsg4hZJvsydKiSqIh6Rncfx2vnFIPiQ8nkTcjq7jVQVW/XnpOx0gNlvkJnbrUSVtk/Rz3TRUBdSLD69C+6JjkM95Sjtq+K/R6VRHg0wVr29iM6fTDVkHiMfOaXL34tNDzB5l9vlh6AMO48k36e/W9OrHJKkttntpfRqHD25Y/ZgRqej36syMgser/99oeblqUXm8qcFR4Pv+zw==
ARC-Authentication-Results: i=1; mx.microsoft.com 1; spf=pass
 smtp.mailfrom=oracle.com; dmarc=pass action=none header.from=oracle.com;
 dkim=pass header.d=oracle.com; arc=none
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
 d=oracle.onmicrosoft.com; s=selector2-oracle-onmicrosoft-com;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=I8Eue09ui4c6W079IE76+/dJP1KETRcPp5O8R310Q7Y=;
 b=RGPldKZGB8ucvRPR30QqHGFp3IJO41CXwpYg9tEQ4vEG2q6IkVVT1g5G3xQeLKqEwj8FhqYEp3hybfB/eAJiYAvfSmyNV5y0lh93XqBZLlne+8s+28xfEvOHrtMWB/IKMpxed/ViTg5kDKOhG1aE5LBhxX0QetbB0lVdEJY3Eeg=
Authentication-Results: redhat.com; dkim=none (message not signed)
 header.d=none;redhat.com; dmarc=none action=none header.from=oracle.com;
Received: from MWHPR10MB1774.namprd10.prod.outlook.com (2603:10b6:301:9::13)
 by CO1PR10MB4595.namprd10.prod.outlook.com (2603:10b6:303:98::21) with
 Microsoft SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.3846.25; Fri, 19 Feb
 2021 16:13:21 +0000
Received: from MWHPR10MB1774.namprd10.prod.outlook.com
 ([fe80::24eb:1300:dd70:4183]) by MWHPR10MB1774.namprd10.prod.outlook.com
 ([fe80::24eb:1300:dd70:4183%3]) with mapi id 15.20.3846.042; Fri, 19 Feb 2021
 16:13:21 +0000
From: Daniel Jordan <daniel.m.jordan@oracle.com>
To: Alex Williamson <alex.williamson@redhat.com>,
        Cornelia Huck <cohuck@redhat.com>
Cc: Jason Gunthorpe <jgg@nvidia.com>,
        Matthew Wilcox <willy@infradead.org>,
        Pavel Tatashin <pasha.tatashin@soleen.com>,
        Steven Sistare <steven.sistare@oracle.com>,
        kvm@vger.kernel.org, linux-kernel@vger.kernel.org,
        Daniel Jordan <daniel.m.jordan@oracle.com>
Subject: [PATCH v2 1/3] vfio/type1: Change success value of vaddr_get_pfn()
Date: Fri, 19 Feb 2021 11:13:03 -0500
Message-Id: <20210219161305.36522-2-daniel.m.jordan@oracle.com>
X-Mailer: git-send-email 2.30.1
In-Reply-To: <20210219161305.36522-1-daniel.m.jordan@oracle.com>
References: <20210219161305.36522-1-daniel.m.jordan@oracle.com>
X-Originating-IP: [98.229.125.203]
X-ClientProxiedBy: BL0PR0102CA0052.prod.exchangelabs.com
 (2603:10b6:208:25::29) To MWHPR10MB1774.namprd10.prod.outlook.com
 (2603:10b6:301:9::13)
MIME-Version: 1.0
X-MS-Exchange-MessageSentRepresentingType: 1
Received: from localhost.localdomain (98.229.125.203) by
 BL0PR0102CA0052.prod.exchangelabs.com (2603:10b6:208:25::29) with Microsoft
 SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.3868.28 via Frontend
 Transport; Fri, 19 Feb 2021 16:13:19 +0000
X-MS-PublicTrafficType: Email
X-MS-Office365-Filtering-Correlation-Id: 7fe5d379-5006-49b8-a91e-08d8d4f14672
X-MS-TrafficTypeDiagnostic: CO1PR10MB4595:
X-MS-Exchange-Transport-Forked: True
X-Microsoft-Antispam-PRVS: 
 <CO1PR10MB4595623BD680EA740A8FD9A0D9849@CO1PR10MB4595.namprd10.prod.outlook.com>
X-MS-Oob-TLC-OOBClassifiers: OLM:6430;
X-MS-Exchange-SenderADCheck: 1
X-Microsoft-Antispam: BCL:0;
X-Microsoft-Antispam-Message-Info: 
 XLEno0DV+1HhyTeqDjM0JGFzGdFkqLuUuRBcws0Ks49nSQjj8yX841N2kQLNp3Yfq2mSBMHAhOsBSgLpJjedd2Zbqcbbxjli1bLUZLO0X9PH8vqcmpHcRY+k53uI5SVL1DP32ob4CXxCWvTYmbK23ET9BObjZYphmOSA3bOlK/6n/78dIQWBtQTPqktKP7g9so3U5Fcd8Fk7uJY4s4VcE28zge8jaqqKOwP6oPlRe/JE1lcUWeC0KMbxxb2Xu8kaOPBiTEcUranGbULzT9CDJIaBEHCP9jFjULJ7oh3/eY/8tE64SaiezKG28JESQZiXo7RaAsVxPUVPhB5Jhq+xWDLH7E6SRyaNvugYmm5v42yQI25fINFrpDpNyNrii8TaTkIcA8nmPAinGMHhx5q6PP+J7q5MvwIsEOIr9Yl397tFC22aOet/LJzbEFgNj7DrDo0P5LKLgA47sds9kafMc7TFB9TBwcTDEr8WYAH1PO0L2X2+zwx6Ul4xoZof6LK9bwGXaZiBNqQkhYtvqldvWrziWv8l3RaD5qXC6tLUDIOABq+V54s2O+YCy+/1KBsm7m2jQ0CimotekvAEBbhWLw==
X-Forefront-Antispam-Report: 
 CIP:255.255.255.255;CTRY:;LANG:en;SCL:1;SRV:;IPV:NLI;SFV:NSPM;H:MWHPR10MB1774.namprd10.prod.outlook.com;PTR:;CAT:NONE;SFS:(346002)(396003)(376002)(366004)(39860400002)(136003)(2906002)(66556008)(66476007)(107886003)(6486002)(66946007)(6506007)(16526019)(186003)(6512007)(6666004)(4326008)(5660300002)(26005)(52116002)(36756003)(316002)(103116003)(83380400001)(54906003)(2616005)(956004)(1076003)(8676002)(478600001)(110136005)(8936002)(86362001)(69590400012);DIR:OUT;SFP:1101;
X-MS-Exchange-AntiSpam-MessageData: 
 pdspbllJ6YUI2I3pnWFOSrnKFvs+oIArT7HDQBVPPwmMgb1FM4mT8m9Q3zC7vqiN191R37WS8slEg9mHy8jQXg3Pxhg7a6MOiHpA/IQDpk9L9ZRjHElumtPB6PFCvEao25882coujMj7E51wc7Uoq+UiKQOM6Yph44Gk+13vtHU/jMteZ3kVJUlB7ECCalOkJgr5eU+eFsyKkPZ6MGN3Sow2HuvaZ1Ksc5YpU3OMGuF5+LYQJ/WdCSqU3CetytWxWIqevna1Z4iHcFppKIHA7pC6QiW+AXPcuEGHt1wx3tJjnQWR0zAbMuG5k+CfkEsf5urwME/BWXfCopujWmQHzWewLFLJnZnmYoHg4h+jJJiGfHissKRm+60XVy7G6kimO5ptlwZoLi2+ar0fhcZFsffnXwwkmx2VTrGvD2kAsAx6pKw4CbrTIaWKuu/+MEFu4C90L1+Sfw7x6Y6YkEckvnB75uUV/d4zhbE8SY7BfftIy7TecIld/bOAat1u21RfMfmFb47l9eJOlhKh55/npzBBDYEMe2d0pPtj/RiN1jGAWeN/KUZX4B1WmIpEARFxm9Jfm/Eb/Lwk/l0PlUmy7j6erSpbECZ5ejYOYm31mmU0eACR+LIwEettJfYuWBjAph7HKQvsjmKHNsGu8jRMmMohN4xTJ31+toblvzVERJ6znzEb7NH0PLnXTyYFc74zScNjBG8DnxtV2nO1JysQg7HDR93f/stsnb0VfXHBLSb4VNsWTBbR/3HYR3UBSxYLwXXWLc7EEsfILOAIsY7IJRSfwnLfDFxK7N96j+tyvWfevAhU40kSV4SOXnbSf84VXl8bGAoDBMUFLy8R92VAsi92xYTnJ8f5NqSZzaiITjdcPJoIKPspYeWj1mzuLVD+7V7hYyJgOvOcI5bRRrmgEY5twXGtSZ/0gSAfpogk2T6IxDcxd4lI5P9xRZ9KqVpqwCOD9O7lGVc7TGjGbcun/YxSeUrco6aPLtudGrZN9F4f802DrWdyLE3Tbok5IEzAkRcRGU8k+1dvnWscgAjw8YML/XSyovWdxqn4xE0V//h+U5+hY5m5OU0RCyWvVBislHw0HYk6/HAZUY7pxUD/D+KKSbRgqV81KOCVCAZgLeulKiyIBn+4jnZa578lMnHujYl/r//u5kDr7d9uY7mnzGehqOSH37Aq6JbRCu81wI7FA/QMD8eG7d4SKTZCLWANy0k5cRte10z4+vYWvCbHs6++p5lCDR/q3X8eSa27FLlYDA62t3yuzdKPPp0WVPP6WwA9vf2viegYdzOBuL3B1+UssFjrpbbfoWKTwDQ58fPzNEnhkcs79ek9bibePDlR
X-OriginatorOrg: oracle.com
X-MS-Exchange-CrossTenant-Network-Message-Id: 
 7fe5d379-5006-49b8-a91e-08d8d4f14672
X-MS-Exchange-CrossTenant-AuthSource: MWHPR10MB1774.namprd10.prod.outlook.com
X-MS-Exchange-CrossTenant-AuthAs: Internal
X-MS-Exchange-CrossTenant-OriginalArrivalTime: 19 Feb 2021 16:13:20.8900
 (UTC)
X-MS-Exchange-CrossTenant-FromEntityHeader: Hosted
X-MS-Exchange-CrossTenant-Id: 4e2c6054-71cb-48f1-bd6c-3a9705aca71b
X-MS-Exchange-CrossTenant-MailboxType: HOSTED
X-MS-Exchange-CrossTenant-UserPrincipalName: 
 wev8dRjEYgRHkvP9OaDTwHm60CgRXfkbsa2EGS69l4cn+o5fXuDokxBqrRq8ETYI3w9cE5Ez0tqzN0tNeUjyyxZ4E0QGSaPwDbaRz86INwk=
X-MS-Exchange-Transport-CrossTenantHeadersStamped: CO1PR10MB4595
X-Proofpoint-Virus-Version: vendor=nai engine=6200 definitions=9900
 signatures=668683
X-Proofpoint-Spam-Details: rule=notspam policy=default score=0 malwarescore=0
 spamscore=0 mlxscore=0
 phishscore=0 adultscore=0 bulkscore=0 mlxlogscore=999 suspectscore=0
 classifier=spam adjust=0 reason=mlx scancount=1 engine=8.12.0-2009150000
 definitions=main-2102190127
X-Proofpoint-Virus-Version: vendor=nai engine=6200 definitions=9900
 signatures=668683
X-Proofpoint-Spam-Details: rule=notspam policy=default score=0 spamscore=0
 priorityscore=1501
 lowpriorityscore=0 bulkscore=0 impostorscore=0 mlxlogscore=999
 adultscore=0 malwarescore=0 phishscore=0 clxscore=1015 mlxscore=0
 suspectscore=0 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.12.0-2009150000 definitions=main-2102190127
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

vaddr_get_pfn() simply returns 0 on success.  Have it report the number
of pfns successfully gotten instead, whether from page pinning or
follow_fault_pfn(), which will be used later when batching pinning.

Change the last check in vfio_pin_pages_remote() for consistency with
the other two.

Signed-off-by: Daniel Jordan <daniel.m.jordan@oracle.com>
---
 drivers/vfio/vfio_iommu_type1.c | 21 ++++++++++++++-------
 1 file changed, 14 insertions(+), 7 deletions(-)

```
