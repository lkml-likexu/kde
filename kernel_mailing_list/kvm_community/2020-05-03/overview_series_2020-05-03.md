#### [PATCH V3 01/14] KVM: MIPS: Define KVM_ENTRYHI_ASID to cpu_asid_mask(&boot_cpu_data)
##### From: Huacai Chen <chenhc@lemote.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Huacai Chen <chenhc@lemote.com>
X-Patchwork-Id: 11524303
Return-Path: <SRS0=cgXy=6R=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 5AB8792A
	for <patchwork-kvm@patchwork.kernel.org>;
 Sun,  3 May 2020 10:07:07 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 423DE206A5
	for <patchwork-kvm@patchwork.kernel.org>;
 Sun,  3 May 2020 10:07:07 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=fail reason="signature verification failed" (2048-bit key)
 header.d=gmail.com header.i=@gmail.com header.b="VTYiLf8K"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728089AbgECKGx (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Sun, 3 May 2020 06:06:53 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:42776 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-FAIL-OK-FAIL)
        by vger.kernel.org with ESMTP id S1727971AbgECKGw (ORCPT
        <rfc822;kvm@vger.kernel.org>); Sun, 3 May 2020 06:06:52 -0400
Received: from mail-pj1-x1042.google.com (mail-pj1-x1042.google.com
 [IPv6:2607:f8b0:4864:20::1042])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 7298BC061A0C;
        Sun,  3 May 2020 03:06:52 -0700 (PDT)
Received: by mail-pj1-x1042.google.com with SMTP id a7so2336591pju.2;
        Sun, 03 May 2020 03:06:52 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=sender:from:to:cc:subject:date:message-id:in-reply-to:references;
        bh=PbRSEAf2iP4s0AdgPIwTBI8UU6TRpGo2RmWTv12T7ho=;
        b=VTYiLf8K3ZXQ03QVxYhF/9uO0E/tOu+kPQwoAc93b3BEAgcVSLQpBRqF2Tf/oUnNLT
         5MfOCVNkyIxmfW6rqRAG/KDOGfJ90qSCOYkyLVyp0kCgfho/WbXvhYjmWOk0cHJ5XATU
         DT0r+nBcu/TmiBtudt7o8B42SrS5xlGZch/1pUGsPFXcIVqwxqDNtPmHwMfsxvoFXZ1A
         7UIBtWfNo9LYAGZPY0CkpTT/Cb9i6S0Nln245se2dLDSKKL+IHXw45JcsEkqVcmoO5VM
         mVffHeh9xVjeJYazs9MkBbMnBRM3I7qierSyZc936jKsNujp4nP3aLs9jchzfKN8CZ1c
         LRVw==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:sender:from:to:cc:subject:date:message-id
         :in-reply-to:references;
        bh=PbRSEAf2iP4s0AdgPIwTBI8UU6TRpGo2RmWTv12T7ho=;
        b=kd2FBUxics+bZfp4qgSj4YoncMeCzVeuG2768QeZgE3M8sRK5AGi143DIW4Bmsfn00
         n9OqyzYrhiefnbnvJ1T44vVSLs384QWzl3sQHTZ4lMRHxMbRhfBjMIlTqEjYtd2xhaEk
         guxJNtD2J14HR32Bl0cBQ2m2/yZQmxxQoCQhob7LI3DdekoZtfP4WkvzNerKS96e+6Qw
         aHEQjMEvbge7SlNJsfHBX1Pg893UF1jCpvgH/CzWxURDVXqTXNWHirPmwj0QJUb9Dptw
         bmdHQVEOVJbLiMe2/gtgk7eqtOOJ0Quvre/JjHGmqCy68NjQne7oCYV1njSax2BumxX5
         4f5Q==
X-Gm-Message-State: AGi0PuZ0cn8iich0ESm/UC/ZqYdLxNcTR/FMyd/BHZf+tNb1G9uZQnro
        PMnv5DmEIWMpX6MYb39S1+k=
X-Google-Smtp-Source: 
 APiQypIMzb4fvmZ2zpKo8dEGVhfSuz5hlvqkKdlygX14KjFPoy1s9T1BV1mrn7vMVcueySXbmeQTHw==
X-Received: by 2002:a17:902:7045:: with SMTP id
 h5mr212211plt.108.1588500411150;
        Sun, 03 May 2020 03:06:51 -0700 (PDT)
Received: from software.domain.org (28.144.92.34.bc.googleusercontent.com.
 [34.92.144.28])
        by smtp.gmail.com with ESMTPSA id
 r26sm6329902pfq.75.2020.05.03.03.06.47
        (version=TLS1_2 cipher=ECDHE-ECDSA-AES128-GCM-SHA256 bits=128/128);
        Sun, 03 May 2020 03:06:50 -0700 (PDT)
From: Huacai Chen <chenhc@lemote.com>
To: Paolo Bonzini <pbonzini@redhat.com>,
        Thomas Bogendoerfer <tsbogend@alpha.franken.de>
Cc: kvm@vger.kernel.org, qemu-devel@nongnu.org, linux-mips@vger.kernel.org,
	=?utf-8?q?Philippe_Mathieu-Daud=C3=A9?= <f4bug@amsat.org>,
 Aleksandar Markovic <aleksandar.qemu.devel@gmail.com>,
 Fuxin Zhang <zhangfx@lemote.com>, Huacai Chen <chenhuacai@gmail.com>,
 Jiaxun Yang <jiaxun.yang@flygoat.com>, Xing Li <lixing@loongson.cn>,
 stable@vger.kernel.org, Huacai Chen <chenhc@lemote.com>
Subject: [PATCH V3 01/14] KVM: MIPS: Define KVM_ENTRYHI_ASID to
 cpu_asid_mask(&boot_cpu_data)
Date: Sun,  3 May 2020 18:05:54 +0800
Message-Id: <1588500367-1056-2-git-send-email-chenhc@lemote.com>
X-Mailer: git-send-email 2.7.0
In-Reply-To: <1588500367-1056-1-git-send-email-chenhc@lemote.com>
References: <1588500367-1056-1-git-send-email-chenhc@lemote.com>
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Xing Li <lixing@loongson.cn>

The code in decode_config4() of arch/mips/kernel/cpu-probe.c

        asid_mask = MIPS_ENTRYHI_ASID;
        if (config4 & MIPS_CONF4_AE)
                asid_mask |= MIPS_ENTRYHI_ASIDX;
        set_cpu_asid_mask(c, asid_mask);

set asid_mask to cpuinfo->asid_mask.

So in order to support variable ASID_MASK, KVM_ENTRYHI_ASID should also
be changed to cpu_asid_mask(&boot_cpu_data).

Cc: stable@vger.kernel.org
Signed-off-by: Xing Li <lixing@loongson.cn>
[Huacai: Change current_cpu_data to boot_cpu_data for optimization]
Signed-off-by: Huacai Chen <chenhc@lemote.com>
---
 arch/mips/include/asm/kvm_host.h | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
#### [PATCH v3] KVM: VMX: Improve handle_external_interrupt_irqoff inline assembly
##### From: Uros Bizjak <ubizjak@gmail.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Uros Bizjak <ubizjak@gmail.com>
X-Patchwork-Id: 11524833
Return-Path: <SRS0=cgXy=6R=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 5C415912
	for <patchwork-kvm@patchwork.kernel.org>;
 Sun,  3 May 2020 22:33:59 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 431FC206E9
	for <patchwork-kvm@patchwork.kernel.org>;
 Sun,  3 May 2020 22:33:59 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=gmail.com header.i=@gmail.com
 header.b="h30bc2gZ"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729197AbgECWd6 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Sun, 3 May 2020 18:33:58 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:45206 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-FAIL-OK-FAIL)
        by vger.kernel.org with ESMTP id S1729174AbgECWd5 (ORCPT
        <rfc822;kvm@vger.kernel.org>); Sun, 3 May 2020 18:33:57 -0400
Received: from mail-wr1-x443.google.com (mail-wr1-x443.google.com
 [IPv6:2a00:1450:4864:20::443])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id A166AC061A0E
        for <kvm@vger.kernel.org>; Sun,  3 May 2020 15:33:57 -0700 (PDT)
Received: by mail-wr1-x443.google.com with SMTP id d15so18727031wrx.3
        for <kvm@vger.kernel.org>; Sun, 03 May 2020 15:33:57 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=from:to:cc:subject:date:message-id:mime-version
         :content-transfer-encoding;
        bh=hAuiYS+rJeIWnpRWOnSqTmst57oP0la/QQB21Glltq8=;
        b=h30bc2gZvKZOb48Bh4oXKnaPyyV30j1pL86UPmoWl7kqJH7pzhgBpCyJxhCmfdpC8d
         cEAz8CT4NyMiNNbn9OLwgJpHVK5xdiFd61vARl0ypP8n/0d0AV06lgfPVmif1PG43BH0
         ALGjLnxFNF/17XxnJ3RI+3HMkqiSnvAbY/Le6VE/I/avzQRw7OU08JTAcyd6Y3QkZXhB
         FhgV1nfhMbML2/uLTLYCxG2qtvrxjpdd4G5kX2OSa/KBemzUF6LHWA1AwpAi41gA1lG0
         STtQDpX8NqgqDv2ggq/heJCzMgeZrGCYOC0hNt7M7T77KzdxHhAU5dA6RLfCphA74C1u
         RhZw==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:mime-version
         :content-transfer-encoding;
        bh=hAuiYS+rJeIWnpRWOnSqTmst57oP0la/QQB21Glltq8=;
        b=QSgoegrqSer+fA1OYxLpT4PcZ/NNXy+sTBVkGvYO/Si8yCa7lYrHcS4RHAyLgW2qe6
         OlUh3JjYCwQs7IhExwriqUkJ+BkH5l6MkEJvJti+Llut1Cp8VLnK5ThiM+U8MZIWz8ll
         t04o45RGRNJHu58bwI1qifFRduoldv7hMAZjdYCg0g1kSpef3Tk5wq3TKFk7l/7UVn7w
         syuyQAExDRYdTtVq8mgH7PlLdsYTs5L/GKlscUDZPPtxSulJoFXtoBG+5aNfdgLFLotK
         CuaKb5dg/NiIzz9rIXDtQZHzZjnuTTjO8xiNoGMzcEViS303zz9DhVzi41uu/kfAaxaL
         pPwQ==
X-Gm-Message-State: AGi0PuZowJJTEu/Kh4u3SdeQ86bOY4ukuXvHE46vdxSUXkFJAv3PbeGS
        E/oUQesI3fPCl1WlUjhf5souriyjQmo=
X-Google-Smtp-Source: 
 APiQypLQg7/H2HazrEILkrURaF5ETH8o+lfKjzkBgxjeCE5u+SGaSAPIRJLchwZQYUXP8o2LqF4JxA==
X-Received: by 2002:adf:fd83:: with SMTP id d3mr13068526wrr.249.1588545236156;
        Sun, 03 May 2020 15:33:56 -0700 (PDT)
Received: from localhost.localdomain (93-103-18-160.static.t-2.net.
 [93.103.18.160])
        by smtp.gmail.com with ESMTPSA id
 u5sm2765150wrm.35.2020.05.03.15.33.54
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Sun, 03 May 2020 15:33:55 -0700 (PDT)
From: Uros Bizjak <ubizjak@gmail.com>
To: kvm@vger.kernel.org
Cc: Uros Bizjak <ubizjak@gmail.com>,
        Paolo Bonzini <pbonzini@redhat.com>,
        Sean Christopherson <sean.j.christopherson@intel.com>
Subject: [PATCH v3] KVM: VMX: Improve handle_external_interrupt_irqoff inline
 assembly
Date: Mon,  4 May 2020 00:33:42 +0200
Message-Id: <20200503223342.440441-1-ubizjak@gmail.com>
X-Mailer: git-send-email 2.25.4
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Improve handle_external_interrupt_irqoff inline assembly in several ways:
- use "rme" operand constraint instead of "i" and remove
  unneeded %c operand modifiers and "$" prefixes
- use %rsp instead of _ASM_SP, since we are in CONFIG_X86_64 part
- use $-16 immediate to align %rsp
- remove unneeded use of __ASM_SIZE macro
- define "ss" named operand only for X86_64

The patch introduces no functional changes.

Cc: Paolo Bonzini <pbonzini@redhat.com>
Cc: Sean Christopherson <sean.j.christopherson@intel.com>
Signed-off-by: Uros Bizjak <ubizjak@gmail.com>
---
 arch/x86/kvm/vmx/vmx.c | 14 ++++++++------
 1 file changed, 8 insertions(+), 6 deletions(-)

```
#### [PATCH v4] KVM: VMX: Improve handle_external_interrupt_irqoff inline assembly
##### From: Uros Bizjak <ubizjak@gmail.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Uros Bizjak <ubizjak@gmail.com>
X-Patchwork-Id: 11524837
Return-Path: <SRS0=cgXy=6R=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 38339139A
	for <patchwork-kvm@patchwork.kernel.org>;
 Sun,  3 May 2020 23:06:04 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 15CF720735
	for <patchwork-kvm@patchwork.kernel.org>;
 Sun,  3 May 2020 23:06:04 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=gmail.com header.i=@gmail.com
 header.b="PeU7ScfB"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726291AbgECXGD (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Sun, 3 May 2020 19:06:03 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:50216 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-FAIL-OK-FAIL)
        by vger.kernel.org with ESMTP id S1725844AbgECXGC (ORCPT
        <rfc822;kvm@vger.kernel.org>); Sun, 3 May 2020 19:06:02 -0400
Received: from mail-wm1-x342.google.com (mail-wm1-x342.google.com
 [IPv6:2a00:1450:4864:20::342])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 3EC2DC061A0E
        for <kvm@vger.kernel.org>; Sun,  3 May 2020 16:06:02 -0700 (PDT)
Received: by mail-wm1-x342.google.com with SMTP id y24so6816032wma.4
        for <kvm@vger.kernel.org>; Sun, 03 May 2020 16:06:02 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=from:to:cc:subject:date:message-id:mime-version
         :content-transfer-encoding;
        bh=hVr7vzsal3m7P4Y5nEVSiXRYbrfFcH85cwwpdr26ZwA=;
        b=PeU7ScfBMxPlh1ueMzgw2R52MggxaS7bWMZXO5gkDaJt4FTVW9seMMBLs+ElbvDYvC
         WWOUkrX9kRV4OrRmLZ96EQmGiu/Ztq2dRnNtwWJ3c2FMEJr6viKbNjLSg8wkAMUdR+DS
         SAh54vjYJrQimB3iHBQ/KHNKqWVCdCgBV4YatfTrZkQ9xTENn5za5ZhUjDhf66nkbGlT
         L86qo4qz9N8ct9gc1iuz/SQBdoyta1B4JBS/R8BF8BWrjg2z+d/+sodC2SrsD6naZ5VP
         2T1PjgLTk6X9ooSyiEFEA4RkQMnPzIi7GpCB7WB0i7oeTQ8Qov4mwzEFR+nCg48qbNfh
         r07Q==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:mime-version
         :content-transfer-encoding;
        bh=hVr7vzsal3m7P4Y5nEVSiXRYbrfFcH85cwwpdr26ZwA=;
        b=jvgUUK8AQvCzV0YOGwDsTPBNUJXxqn4rQ/Meya9fYEMayxP1XCZt3fPOwy7qnXIle1
         3rFxe3/v9sX7yXmQ+z7V6SyGpdVYyutuzEbxRYKg7jLxqQ5DuRQ+bhVLWKmiOFm4HxJ8
         LabOMi2tcveeMwt+MKA2bJ3KtWM6aGwMQfR1f8QDmo6yx7Gg1mEGxC1veLMcLJlkitgc
         /IfsViqxcxKG20gnfGojQRg+4UctuoKvVsbK/siZbGcTOqQqwmSkGfU6ZkSV+whLEMwa
         oysW/QYPg8NaAumD9955+EQBP+xlRJamP87nVwcm7JxjgroP9fyx/2iomVJ2t2twcxac
         ASkg==
X-Gm-Message-State: AGi0PuYoZQKuuRg0VPgQ5zT22+/WWs5qWReYUn2MW62ULXTru/s1pMt2
        rPe2JXdRQJNUw5QqY9+plwI2mJj/zPQ=
X-Google-Smtp-Source: 
 APiQypI0g0GbAX/X9FyPgeAwt4W5oaUJq8QnfPndKICqtWvW/tDZeublhRb0I5LjAIJmcK19pB9lRw==
X-Received: by 2002:a7b:c4c9:: with SMTP id g9mr11148747wmk.171.1588547159664;
        Sun, 03 May 2020 16:05:59 -0700 (PDT)
Received: from localhost.localdomain (93-103-18-160.static.t-2.net.
 [93.103.18.160])
        by smtp.gmail.com with ESMTPSA id
 c83sm12044677wmd.23.2020.05.03.16.05.58
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Sun, 03 May 2020 16:05:58 -0700 (PDT)
From: Uros Bizjak <ubizjak@gmail.com>
To: kvm@vger.kernel.org
Cc: Uros Bizjak <ubizjak@gmail.com>,
        Paolo Bonzini <pbonzini@redhat.com>,
        Sean Christopherson <sean.j.christopherson@intel.com>
Subject: [PATCH v4] KVM: VMX: Improve handle_external_interrupt_irqoff inline
 assembly
Date: Mon,  4 May 2020 01:05:45 +0200
Message-Id: <20200503230545.442042-1-ubizjak@gmail.com>
X-Mailer: git-send-email 2.25.4
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Improve handle_external_interrupt_irqoff inline assembly in several ways:
- use "re" operand constraint instead of "i" and remove
  unneeded %c operand modifiers and "$" prefixes
- use %rsp instead of _ASM_SP, since we are in CONFIG_X86_64 part
- use $-16 immediate to align %rsp
- remove unneeded use of __ASM_SIZE macro
- define "ss" named operand only for X86_64

The patch introduces no functional changes.

Cc: Paolo Bonzini <pbonzini@redhat.com>
Cc: Sean Christopherson <sean.j.christopherson@intel.com>
Signed-off-by: Uros Bizjak <ubizjak@gmail.com>
---
 arch/x86/kvm/vmx/vmx.c | 14 ++++++++------
 1 file changed, 8 insertions(+), 6 deletions(-)

```
