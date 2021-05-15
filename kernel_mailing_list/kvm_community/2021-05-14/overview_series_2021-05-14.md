#### [PATCH v2 1/2] KVM: arm64: Move __adjust_pc out of line
##### From: Marc Zyngier <maz@kernel.org>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Marc Zyngier <maz@kernel.org>
X-Patchwork-Id: 12257445
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No,
 score=-17.0 required=3.0 tests=BAYES_00,INCLUDES_CR_TRAILER,
	INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT
	autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 41427C43461
	for <kvm@archiver.kernel.org>; Fri, 14 May 2021 10:40:51 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 276A361461
	for <kvm@archiver.kernel.org>; Fri, 14 May 2021 10:40:51 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S231926AbhENKmB (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Fri, 14 May 2021 06:42:01 -0400
Received: from mail.kernel.org ([198.145.29.99]:46934 "EHLO mail.kernel.org"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S230509AbhENKl7 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 14 May 2021 06:41:59 -0400
Received: from disco-boy.misterjones.org (disco-boy.misterjones.org
 [51.254.78.96])
        (using TLSv1.2 with cipher ECDHE-RSA-AES256-GCM-SHA384 (256/256 bits))
        (No client certificate requested)
        by mail.kernel.org (Postfix) with ESMTPSA id 520F261458;
        Fri, 14 May 2021 10:40:48 +0000 (UTC)
Received: from 78.163-31-62.static.virginmediabusiness.co.uk ([62.31.163.78]
 helo=why.lan)
        by disco-boy.misterjones.org with esmtpsa  (TLS1.3) tls
 TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384
        (Exim 4.94.2)
        (envelope-from <maz@kernel.org>)
        id 1lhVFO-001N6Q-MS; Fri, 14 May 2021 11:40:46 +0100
From: Marc Zyngier <maz@kernel.org>
To: kvm@vger.kernel.org, kvmarm@lists.cs.columbia.edu,
        linux-arm-kernel@lists.infradead.org
Cc: Zenghui Yu <yuzenghui@huawei.com>, Fuad Tabba <tabba@google.com>,
        James Morse <james.morse@arm.com>,
        Suzuki K Poulose <suzuki.poulose@arm.com>,
        Alexandru Elisei <alexandru.elisei@arm.com>,
        kernel-team@android.com, stable@vger.kernel.org
Subject: [PATCH v2 1/2] KVM: arm64: Move __adjust_pc out of line
Date: Fri, 14 May 2021 11:40:41 +0100
Message-Id: <20210514104042.1929168-2-maz@kernel.org>
X-Mailer: git-send-email 2.29.2
In-Reply-To: <20210514104042.1929168-1-maz@kernel.org>
References: <20210514104042.1929168-1-maz@kernel.org>
MIME-Version: 1.0
X-SA-Exim-Connect-IP: 62.31.163.78
X-SA-Exim-Rcpt-To: kvm@vger.kernel.org, kvmarm@lists.cs.columbia.edu,
 linux-arm-kernel@lists.infradead.org, yuzenghui@huawei.com, tabba@google.com,
 james.morse@arm.com, suzuki.poulose@arm.com, alexandru.elisei@arm.com,
 kernel-team@android.com, stable@vger.kernel.org
X-SA-Exim-Mail-From: maz@kernel.org
X-SA-Exim-Scanned: No (on disco-boy.misterjones.org);
 SAEximRunCond expanded to false
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

In order to make it easy to call __adjust_pc() from the EL1 code
(in the case of nVHE), rename it to __kvm_adjust_pc() and move
it out of line.

No expected functional change.

Signed-off-by: Marc Zyngier <maz@kernel.org>
Cc: stable@vger.kernel.org # 5.11
Reviewed-by: Alexandru Elisei <alexandru.elisei@arm.com>
---
 arch/arm64/include/asm/kvm_asm.h           |  2 ++
 arch/arm64/kvm/hyp/exception.c             | 18 +++++++++++++++++-
 arch/arm64/kvm/hyp/include/hyp/adjust_pc.h | 18 ------------------
 arch/arm64/kvm/hyp/nvhe/switch.c           |  3 +--
 arch/arm64/kvm/hyp/vhe/switch.c            |  3 +--
 5 files changed, 21 insertions(+), 23 deletions(-)

```
#### [PATCH] KVM: selftests: Fix hang in hardware_disable_testFrom: David Matlack <dmatlack@google.com>
##### From: David Matlack <dmatlack@google.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: David Matlack <dmatlack@google.com>
X-Patchwork-Id: 12259265
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-26.3 required=3.0 tests=BAYES_00,DKIMWL_WL_MED,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_CR_TRAILER,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,
	USER_AGENT_GIT,USER_IN_DEF_DKIM_WL autolearn=ham autolearn_force=no
	version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 8DAA3C433B4
	for <kvm@archiver.kernel.org>; Fri, 14 May 2021 23:05:26 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 674326141F
	for <kvm@archiver.kernel.org>; Fri, 14 May 2021 23:05:26 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S234254AbhENXGh (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Fri, 14 May 2021 19:06:37 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:54988 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S230371AbhENXGg (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 14 May 2021 19:06:36 -0400
Received: from mail-pj1-x1049.google.com (mail-pj1-x1049.google.com
 [IPv6:2607:f8b0:4864:20::1049])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 0FD1FC06174A
        for <kvm@vger.kernel.org>; Fri, 14 May 2021 16:05:25 -0700 (PDT)
Received: by mail-pj1-x1049.google.com with SMTP id
 w1-20020a17090a0281b0290156f7df20a0so622783pja.8
        for <kvm@vger.kernel.org>; Fri, 14 May 2021 16:05:24 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=date:message-id:mime-version:subject:from:to:cc;
        bh=omC2Zg3MHlKG1tFQ/HKAY2Wl9w/KEfII3rpZaUlUwlA=;
        b=IcWPM2X4gSxjrlaqq2+nJCq2C9taSNotXHB2J54HQtG+ir8xjoedSW4oony2RGvkAA
         vrzWOP1AqpJxhf3nAyBqVUXyRz1G7s9u9futHi4msXqEoJDVXek7AVGBpuy8PgrPj1ZE
         jrgGeMJdnvpWgIl8LC21O3UD9DHmhiu+2kh036CUvn7kUtWe8vddXzqJwKpS/SSxHtE0
         BWXMqOTEqXCahdgRTQF6Z/n8pyLZsYA7GJ/assbtBxn8C416H/q8uHVGQDs2enihB6U9
         G2Cn5ueqXJrGCVJKA+MN3ITG7Pj/9cF2ehGaykyeBeT/Zwjh1uNKsWko/9ZqKbL8wSjy
         bAOg==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:date:message-id:mime-version:subject:from:to:cc;
        bh=omC2Zg3MHlKG1tFQ/HKAY2Wl9w/KEfII3rpZaUlUwlA=;
        b=KAVD+FG4NX7Y6R8i9Hhxil/Oyi8vmtZUKfMW/4UOtwaAnHBpOwcXtJWza+52ku6G4y
         ZGyHVT/ZB/m3wXNESF5PutrJKq0t8dC//oKwLlYXKl79pj6s3vSQ2tDzjnlkBv+COq9d
         X8N28JecPisrjdOJeKnkBPFqcwrqWXOpBD75yT+R95VO/tL15U418rez1ybgHlEfVgk/
         YeN24V5jOb6jBnqmA4d9JXAH0T67LVADAXKLb81uuuOH4DofZNyjiAETUeAoE1M1S9ti
         BpPQFBT1qSQ7sxyJyc93Ma+C/SS/zBQkHcZmGKg7SCsTdUxneVGiU+5ZcusKDOI4gIOt
         NlnQ==
X-Gm-Message-State: AOAM532DXhVrv6++FiUe/uc/GsEf0UE7WXbTPBXHf9UuZ35rmF7F3qjr
        kMQR6hGypCTbacBX26LxQdTUZHPZbXFLMh6TZooLp/9Zi6gEAPek9OjfQvo4pk2YLgy6QER2YPo
        3672G1ByAcKqrQMJer1FB8ZHifufZkZRkb1o0tERdj+dMZNomyGO4+prj2pQm/T0=
X-Google-Smtp-Source: 
 ABdhPJxwnWVSDfrxHHAz5FGSdRlfK2vgesG3/qH5vIABnY7JmjsShWtUIIxnjieKSfrvGy+sp1Xe7OSDpmJ5fA==
X-Received: from dmatlack-heavy.c.googlers.com
 ([fda3:e722:ac3:10:7f:e700:c0a8:19cd])
 (user=dmatlack job=sendgmr) by 2002:a17:90a:6309:: with SMTP id
 e9mr14178719pjj.20.1621033523813; Fri, 14 May 2021 16:05:23 -0700 (PDT)
Date: Fri, 14 May 2021 23:05:21 +0000
Message-Id: <20210514230521.2608768-1-dmatlack@google.com>
Mime-Version: 1.0
X-Mailer: git-send-email 2.31.1.751.gd2f1c929bd-goog
Subject: [PATCH] KVM: selftests: Fix hang in hardware_disable_test
From: David Matlack <dmatlack@google.com>
To: kvm@vger.kernel.org
Cc: Paolo Bonzini <pbonzini@redhat.com>,
        Andrew Jones <drjones@redhat.com>,
        Ignacio Alvarado <ikalvarado@google.com>,
        David Matlack <dmatlack@google.com>
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

If /dev/kvm is not available then hardware_disable_test will hang
indefinitely because the child process exits before posting to the
semaphore for which the parent is waiting.

Fix this by making the parent periodically check if the child has
exited. We have to be careful to forward the child's exit status to
preserve a KSFT_SKIP status.

I considered just checking for /dev/kvm before creating the child
process, but there are so many other reasons why the child could exit
early that it seemed better to handle that as general case.

Tested:

$ ./hardware_disable_test
/dev/kvm not available, skipping test
$ echo $?
4
$ modprobe kvm_intel
$ ./hardware_disable_test
$ echo $?
0

Signed-off-by: David Matlack <dmatlack@google.com>
---
 .../selftests/kvm/hardware_disable_test.c     | 32 ++++++++++++++++++-
 1 file changed, 31 insertions(+), 1 deletion(-)

```
#### [PATCH] KVM: SVM: Do not terminate SEV-ES guests on GHCB validation failure
##### From: Tom Lendacky <thomas.lendacky@amd.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Tom Lendacky <thomas.lendacky@amd.com>
X-Patchwork-Id: 12258689
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-18.8 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,
	INCLUDES_PATCH,MAILING_LIST_MULTI,MSGID_FROM_MTA_HEADER,SPF_HELO_NONE,
	SPF_PASS,USER_AGENT_GIT autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 1FE0CC433B4
	for <kvm@archiver.kernel.org>; Fri, 14 May 2021 19:22:50 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id ECC306145B
	for <kvm@archiver.kernel.org>; Fri, 14 May 2021 19:22:49 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S231628AbhENTYA (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Fri, 14 May 2021 15:24:00 -0400
Received: from mail-bn7nam10on2073.outbound.protection.outlook.com
 ([40.107.92.73]:43105
        "EHLO NAM10-BN7-obe.outbound.protection.outlook.com"
        rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org with ESMTP
        id S229610AbhENTYA (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 14 May 2021 15:24:00 -0400
ARC-Seal: i=1; a=rsa-sha256; s=arcselector9901; d=microsoft.com; cv=none;
 b=h7IySrd8MSi73peX7Dz76sGHYK4mCsVbFe34Ln67PaF6lRFnjqjI4yOhYffT/ooZ7MXBewIPCCABLv/p3nAbuvdS1PUoIRlf+H7stK9/sxjSiHUYNRNHFPni/O51/YD6UQpUOjE7eF566fa47CS00FzsAQZoX8u/iNlKjvmAFUDimxuACULQl5bxgWwwOt2wRkvksp7EPYadVtKR2Jth5bxpQAU/OPq7sxhRz02jVAKwQQPgrIDEaFbE7WEBYQNINJWc+GO8Ptg+hhjgF7CYMpRs3Br+Wcin9iGPOnLRQqyd1POoLtUym/Py+MJF5WBIsTENjgM3NOU0EiD0ny3m0w==
ARC-Message-Signature: i=1; a=rsa-sha256; c=relaxed/relaxed; d=microsoft.com;
 s=arcselector9901;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=VepO996Q8zEYKgkFLldzaVYVigxqVmFwVN6bfx3fTb8=;
 b=getjErUrs4AureTy/ZwbvL6pvamx503KE2mr1Ihce0GRN2a1sy68dAhXMGTY6qUYKdjrbnk8Y/usJSSyogTSYnHePucSo5rBvHJZ39+jUmlYR6ASf9ErsDWTDBeyvN9yJPyG2cH9WK6VqoepWlAAAZdxxt6XY/Zx6ykuf3tnf14i/oPbfuszr7FqCuXF1SFJ2tV1zAbdf5EQWWQvy8bEsUrrgnIChCPdADgem6tlATr3HWQYMg0eGtLr0BEjLdSwD/YwgopKG1CEPDQygthvvtu4Uly8vHKA20XQxMm+UubeNaUJP7uscwOMIb70CsJM/Ikd2fsnvdabPfjxWCoA3w==
ARC-Authentication-Results: i=1; mx.microsoft.com 1; spf=pass
 smtp.mailfrom=amd.com; dmarc=pass action=none header.from=amd.com; dkim=pass
 header.d=amd.com; arc=none
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=amd.com; s=selector1;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=VepO996Q8zEYKgkFLldzaVYVigxqVmFwVN6bfx3fTb8=;
 b=RB771S9AuPe1jrD0E4R9cJMIHVsI1osn+DcAEV1+LpQfc9qacfiGoo+wj0UscIquAWUKQfR0UXomqssl+gFBIUK40AE99eIVaawBXMg6RaJnNMDjL3pa50bbjxzB3K6wFlywD6xtUbgOajPsUXS36qTEbfNcNg7RLppJB+H1kDM=
Authentication-Results: vger.kernel.org; dkim=none (message not signed)
 header.d=none;vger.kernel.org; dmarc=none action=none header.from=amd.com;
Received: from DM5PR12MB1355.namprd12.prod.outlook.com (10.168.234.7) by
 DM6PR12MB4337.namprd12.prod.outlook.com (20.180.254.76) with Microsoft SMTP
 Server (version=TLS1_2, cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id
 15.20.4129.25; Fri, 14 May 2021 19:22:46 +0000
Received: from DM5PR12MB1355.namprd12.prod.outlook.com
 ([fe80::b914:4704:ad6f:aba9]) by DM5PR12MB1355.namprd12.prod.outlook.com
 ([fe80::b914:4704:ad6f:aba9%12]) with mapi id 15.20.4129.025; Fri, 14 May
 2021 19:22:46 +0000
From: Tom Lendacky <thomas.lendacky@amd.com>
To: kvm@vger.kernel.org, linux-kernel@vger.kernel.org, x86@kernel.org
Cc: Paolo Bonzini <pbonzini@redhat.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>,
        Sean Christopherson <seanjc@google.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Borislav Petkov <bp@alien8.de>, Ingo Molnar <mingo@redhat.com>,
        Thomas Gleixner <tglx@linutronix.de>,
        Brijesh Singh <brijesh.singh@amd.com>
Subject: [PATCH] KVM: SVM: Do not terminate SEV-ES guests on GHCB validation
 failure
Date: Fri, 14 May 2021 14:22:38 -0500
Message-Id: 
 <f8811b3768c4306af7fb2732b6b3755489832c55.1621020158.git.thomas.lendacky@amd.com>
X-Mailer: git-send-email 2.31.0
X-Originating-IP: [165.204.77.1]
X-ClientProxiedBy: SN1PR12CA0101.namprd12.prod.outlook.com
 (2603:10b6:802:21::36) To DM5PR12MB1355.namprd12.prod.outlook.com
 (2603:10b6:3:6e::7)
MIME-Version: 1.0
X-MS-Exchange-MessageSentRepresentingType: 1
Received: from tlendack-t1.amd.com (165.204.77.1) by
 SN1PR12CA0101.namprd12.prod.outlook.com (2603:10b6:802:21::36) with Microsoft
 SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.4108.24 via Frontend
 Transport; Fri, 14 May 2021 19:22:45 +0000
X-MS-PublicTrafficType: Email
X-MS-Office365-Filtering-Correlation-Id: 8f477576-9e5d-4adb-4647-08d9170da768
X-MS-TrafficTypeDiagnostic: DM6PR12MB4337:
X-MS-Exchange-Transport-Forked: True
X-Microsoft-Antispam-PRVS: 
 <DM6PR12MB4337AAF005C7964657440F85EC509@DM6PR12MB4337.namprd12.prod.outlook.com>
X-MS-Oob-TLC-OOBClassifiers: OLM:4941;
X-MS-Exchange-SenderADCheck: 1
X-Microsoft-Antispam: BCL:0;
X-Microsoft-Antispam-Message-Info: 
 2ZxxIlxL6rBZhLr8WYxbyxqc9W1nrhh4GZFA5PC6VaLT7rGJBg0WmVZN1lOvnFwPZEkVHChaQGVcPBxk/Kw09KOsJRsSslaUPgHzn0pVUkm2UrVYKDjnlN3FDtp+xcNTkgq+DAnX3Eo+YQDGPXylex1/7MQHICwQd9sO0STPnpA/DiShKl5zIzk+SosQTfXs3TN6FCTWl8BUuPn+h4akeoa4G1tyo/WJa34+kTD9n/iveGCRXe1HXDSo47Ua1ua7IfYKqHSM20TrkZQK6nWXj9wD2UMDGYNaNu9STMLtINdFh7nkmTOUzo9b7Yi71gDh5tH3EoywpF/Ncly6MXANKBNaGf80E6R1IiVXqbCCqkbKpeJbnfx0LEDpkSk5Kt7Rl11X1lfxIlGT54RHRytilFOfb491F3YLW2VMm7RFI7ktQrQvyXb/Nr8DKjPiodJzHB3dtY6pMeF698cft0ulfFHAlFl3z2rc7lVNVdsk0+BjABl3JYNOC8V3aZfv+i1HtQNSN2gsSc6VIT4y5UQqscvPkbCgK0nmoxfJfTjJdvObyVGgb9/zITZavhz4nfexPa29QKD7I5t+4hgmPOmyFCJkmZMLviVs1y/yjyCkkXVrmgUJmIA9oR3MlPEigTyrd3nf/sPpQsoJyJIWQce7HA7BVqt4A6b3Xm0rshR0yFI=
X-Forefront-Antispam-Report: 
 CIP:255.255.255.255;CTRY:;LANG:en;SCL:1;SRV:;IPV:NLI;SFV:NSPM;H:DM5PR12MB1355.namprd12.prod.outlook.com;PTR:;CAT:NONE;SFS:(4636009)(136003)(39860400002)(376002)(396003)(366004)(346002)(83380400001)(4326008)(6666004)(26005)(54906003)(38350700002)(66946007)(66476007)(7696005)(8676002)(7416002)(316002)(52116002)(66556008)(478600001)(86362001)(5660300002)(8936002)(2906002)(186003)(16526019)(2616005)(36756003)(38100700002)(956004)(6486002);DIR:OUT;SFP:1101;
X-MS-Exchange-AntiSpam-MessageData: 
 1uyv9d6pUDNEzsVSwuinIZ6jozMq78paiwjNtDIc6c2nThsgwQzvATD73I2qxNOTYKva8Z/LSUhHavjBaPV0BqX0scZLaDYQS6XgNO5RLCSGkiOobWNNcOT0MVn/DjUn0Pe1VnYx4qozRwockGKcCgCsVYDVdFUbh9DxQHmG1Tp313v0Py6/YbJeGMaOBKv9Lc4fp8gZKdoYJAh5AMdugHa17ECdE78zvOnA9qkm0YVJovDirO9kVIoCrUNCe6HDlZgYycRUHY7QW4Phrn7jp99D6D0meWuAnpaOjNT62HGzeXNNXEZgWKb46wGPfBOkrpac4tx80pUS0nXnqgy8e7eRyZHNwyleV0ePyj6DvwwsVlS6Do2NJKGHHbTV6LlvUUHKsB4JewtmKifKVHMX9IEYJ0tdEMGh5bEpMfR9aiL3Q0DPBMh0EYqewpVmq7WHbNjYfRS26HtB9mgJSZvnfv30ussor95iaHyV7KK6IXRjvqa4b84ktTPEwDM5Y1jpwLPN0JK/9xLPrYz82STvaR+T4usQV2dj+j1FUQJxVPo3u4gNqBjYtIkOS2ioR6eGyIRvcgfPVIz1B6tiHLN6OGp8KFguwVWDi8G+mlvbseQ1yg8w0Pa9qXxPVXEgvf2K8yXlAHALljLHPgT+NPsRBql2Zy9IJ2i+mVMEqE0Kc6EpTYEYqN+PlA/MTKNHhDqHaHXWdmD3oLDrG7x4SQnsAyWgJRZYIcFwsFjgnb+n8IsaV5wN2J8nN5CFkwsBZoHkqRx6P/oOwuVynf9kSwNlK7u1AguV48NksOqNW7bdYiwaIaUYSqIzDdfik7Xkua0VOF4hEMuEmKkvJrugiO6ODQktuaQQ4UKrI8DqECSQaoHkFkuC0M4ApaKAgkLRZu5oYJ5sIrNHxicM4/CnPp71hO1+patGdHDoBELooIY6TYFFoFfvH28yT/EOm5GVuUagoWeDaSVfBJlgtxN5n5FeK68R1Yi7/7B7MfAoXZJiGz1cpspUTiEUyd19KTDCBoplUgHCrCgl//9rbbv/2VPZ6qtToVNrtKFz7ifJxUKE/sMkye7v5tMepRzPs7IzvC2LXPClDBE+fG/fngOqfVO9uOmj5w/fM66UzzRzxn3ztW5jLFtz6FjvLpV9E+GtT058szlgsCUZNxb2eJRtZhKoKZTrrb+gTYMKrvy+0H3S3Z6I2qskHaOA5ZXYDrZZ9QWOsP0j1M2U3E/zSuHj9Ve9ShefrSKk5gcBownVylGyMjpxtMQ+ovL3fhhwybVU+bJPnfp/VrYnLnxu0eOoOzO9sOBB7fAucseGX+7fFU638WmhlnBJqRhNtTPLbbSidCUe
X-OriginatorOrg: amd.com
X-MS-Exchange-CrossTenant-Network-Message-Id: 
 8f477576-9e5d-4adb-4647-08d9170da768
X-MS-Exchange-CrossTenant-AuthSource: DM5PR12MB1355.namprd12.prod.outlook.com
X-MS-Exchange-CrossTenant-AuthAs: Internal
X-MS-Exchange-CrossTenant-OriginalArrivalTime: 14 May 2021 19:22:46.1817
 (UTC)
X-MS-Exchange-CrossTenant-FromEntityHeader: Hosted
X-MS-Exchange-CrossTenant-Id: 3dd8961f-e488-4e60-8e11-a82d994e183d
X-MS-Exchange-CrossTenant-MailboxType: HOSTED
X-MS-Exchange-CrossTenant-UserPrincipalName: 
 wl2KnUPAZwn9Pq+fYeM0TyiQLW/yjyf6is7J0v532Mm3S+3Q6fVkyQxBqp+xCVpm5EXOpZVDf9R0e8FxfHI64Q==
X-MS-Exchange-Transport-CrossTenantHeadersStamped: DM6PR12MB4337
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Currently, an SEV-ES guest is terminated if the validation of the VMGEXIT
exit code and parameters fail. Since the VMGEXIT instruction can be issued
from userspace, even though userspace (likely) can't update the GHCB,
don't allow userspace to be able to kill the guest.

Return a #GP request through the GHCB when validation fails, rather than
terminating the guest.

Fixes: 291bd20d5d88 ("KVM: SVM: Add initial support for a VMGEXIT VMEXIT")
Signed-off-by: Tom Lendacky <thomas.lendacky@amd.com>
---
 arch/x86/kvm/svm/sev.c | 24 +++++++++++++-----------
 1 file changed, 13 insertions(+), 11 deletions(-)

```
#### [PATCH] KVM: x86/pt: Do not inject TraceToPAPMI when guest PT isn't supported
##### From: Like Xu <like.xu@linux.intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Like Xu <like.xu@linux.intel.com>
X-Patchwork-Id: 12257255
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.8 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT autolearn=ham
	autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 2F817C433B4
	for <kvm@archiver.kernel.org>; Fri, 14 May 2021 08:45:34 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id ECE8561287
	for <kvm@archiver.kernel.org>; Fri, 14 May 2021 08:45:33 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S233693AbhENIqn (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Fri, 14 May 2021 04:46:43 -0400
Received: from mga06.intel.com ([134.134.136.31]:2925 "EHLO mga06.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S231839AbhENIqn (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 14 May 2021 04:46:43 -0400
IronPort-SDR: 
 l4e5DGRN86ONAeZfXa6utUVo8amSBRPu8oKaJbFwxl80CBXD5WhiV3RWRkwBcqThd5ZaxAq4LS
 o9e3xItDLUMQ==
X-IronPort-AV: E=McAfee;i="6200,9189,9983"; a="261379995"
X-IronPort-AV: E=Sophos;i="5.82,299,1613462400";
   d="scan'208";a="261379995"
Received: from fmsmga001.fm.intel.com ([10.253.24.23])
  by orsmga104.jf.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 14 May 2021 01:45:31 -0700
IronPort-SDR: 
 GWVlx1jD/WhhKk0Pyewb9aPU/D6oWp9TNtglPJKLRhY1pr62N0XD6c5OWGIz0W5r7jqP3JmbpJ
 u4RpKUnL1Dqw==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.82,299,1613462400";
   d="scan'208";a="538739299"
Received: from clx-ap-likexu.sh.intel.com ([10.239.48.108])
  by fmsmga001.fm.intel.com with ESMTP; 14 May 2021 01:45:28 -0700
From: Like Xu <like.xu@linux.intel.com>
To: Paolo Bonzini <pbonzini@redhat.com>
Cc: Alexander Shishkin <alexander.shishkin@linux.intel.com>,
        Peter Zijlstra <peterz@infradead.org>,
        Sean Christopherson <seanjc@google.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>, linux-kernel@vger.kernel.org,
        kvm@vger.kernel.org, Like Xu <like.xu@linux.intel.com>
Subject: [PATCH] KVM: x86/pt: Do not inject TraceToPAPMI when guest PT isn't
 supported
Date: Fri, 14 May 2021 16:44:36 +0800
Message-Id: <20210514084436.848396-1-like.xu@linux.intel.com>
X-Mailer: git-send-email 2.31.1
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

When a PT perf user is running in system-wide mode on the host,
the guest (w/ pt_mode=0) will warn about anonymous NMIs from
kvm_handle_intel_pt_intr():

[   18.126444] Uhhuh. NMI received for unknown reason 10 on CPU 0.
[   18.126447] Do you have a strange power saving mode enabled?
[   18.126448] Dazed and confused, but trying to continue

In this case, these PMIs should be handled by the host PT handler().
When PT is used in guest-only mode, it's harmless to call host handler.

Fix: 8479e04e7d("KVM: x86: Inject PMI for KVM guest")
Signed-off-by: Like Xu <like.xu@linux.intel.com>
---
 arch/x86/events/intel/core.c | 3 +--
 arch/x86/kvm/x86.c           | 3 +++
 2 files changed, 4 insertions(+), 2 deletions(-)

```
#### [PATCH net-next 1/3] stmmac: use XDP helpers
##### From: Matteo Croce <mcroce@linux.microsoft.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Matteo Croce <mcroce@linux.microsoft.com>
X-Patchwork-Id: 12258623
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.8 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT autolearn=ham
	autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id F1193C433B4
	for <kvm@archiver.kernel.org>; Fri, 14 May 2021 18:40:39 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id C984261457
	for <kvm@archiver.kernel.org>; Fri, 14 May 2021 18:40:39 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S232148AbhENSlu (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Fri, 14 May 2021 14:41:50 -0400
Received: from mail-ed1-f52.google.com ([209.85.208.52]:39825 "EHLO
        mail-ed1-f52.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S231834AbhENSlu (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 14 May 2021 14:41:50 -0400
Received: by mail-ed1-f52.google.com with SMTP id h16so1363592edr.6;
        Fri, 14 May 2021 11:40:37 -0700 (PDT)
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:in-reply-to
         :references:mime-version:content-transfer-encoding;
        bh=Y4MTLt5TFZRdEBttrmfCcK1QF/TJDQ6Lo2hOuLadKIY=;
        b=GoacduemQ/+y4JnpILwBtZg0yJyHSLXxW2CKgafxfo7l8KndU5tVU3Q5+UTVeXii6I
         J6au3OZix4r+HjzD3iQs5S/sNj+HaOOTg0qQN9FCUh0opN1R8jTfhsKnsoEvpR3wGReU
         bMacm7vvLIZ5FmcLnD7SbWJo8DFCuEUyn6cvr1l/InWZFQrha2yo/2Mn2DUa9nwEwZiF
         vnNkQSEj2YNGOB0UgQ41GtjnZ8M6UbNYjiy7KqTPpycSIv+FFkrA9sLTUW5QzvrHf6Ab
         LK2X5BO+1btHxpj8zVowbudIAQtmyD9WySmBQ4jxAvIC13hbmCcmGpC5U+rrH4AMYZrQ
         CDbA==
X-Gm-Message-State: AOAM532qfd2l4Ibt1wenDG/WPVwVZWWr1w5f9DWZIX/zVYugcZS3JHEp
        mUhW32tv5oUXIk5hJ25v8yHD0azBl+xrXZWB
X-Google-Smtp-Source: 
 ABdhPJztVPeeFds+ovfXgi5hiN0AM5Kzib6Wesqh/ef775Q8o65ykbVOOjTXi8FRmrOvM5b3sV8Pyw==
X-Received: by 2002:aa7:de99:: with SMTP id j25mr36955284edv.91.1621017637149;
        Fri, 14 May 2021 11:40:37 -0700 (PDT)
Received: from turbo.teknoraver.net (net-5-94-253-60.cust.vodafonedsl.it.
 [5.94.253.60])
        by smtp.gmail.com with ESMTPSA id
 dj17sm5081505edb.7.2021.05.14.11.40.36
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Fri, 14 May 2021 11:40:36 -0700 (PDT)
From: Matteo Croce <mcroce@linux.microsoft.com>
To: netdev@vger.kernel.org, bpf@vger.kernel.org,
        intel-wired-lan@lists.osuosl.org,
        linux-stm32@st-md-mailman.stormreply.com, kvm@vger.kernel.org,
        virtualization@lists.linux-foundation.org
Cc: linux-kernel@vger.kernel.org,
        Jesse Brandeburg <jesse.brandeburg@intel.com>,
        Tony Nguyen <anthony.l.nguyen@intel.com>,
        "David S. Miller" <davem@davemloft.net>,
        Jakub Kicinski <kuba@kernel.org>,
        Giuseppe Cavallaro <peppe.cavallaro@st.com>,
        Alexandre Torgue <alexandre.torgue@foss.st.com>,
        "Michael S. Tsirkin" <mst@redhat.com>,
        Jason Wang <jasowang@redhat.com>
Subject: [PATCH net-next 1/3] stmmac: use XDP helpers
Date: Fri, 14 May 2021 20:39:52 +0200
Message-Id: <20210514183954.7129-2-mcroce@linux.microsoft.com>
X-Mailer: git-send-email 2.31.1
In-Reply-To: <20210514183954.7129-1-mcroce@linux.microsoft.com>
References: <20210514183954.7129-1-mcroce@linux.microsoft.com>
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Matteo Croce <mcroce@microsoft.com>

Make use of the xdp_{init,prepare}_buff() helpers instead of
an open-coded version.

Signed-off-by: Matteo Croce <mcroce@microsoft.com>
---
 drivers/net/ethernet/stmicro/stmmac/stmmac_main.c | 9 +++------
 1 file changed, 3 insertions(+), 6 deletions(-)

```
#### [PATCH V2 1/2] vDPA/ifcvf: record virtio notify base
##### From: Zhu Lingshan <lingshan.zhu@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Zhu Lingshan <lingshan.zhu@intel.com>
X-Patchwork-Id: 12257363
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.8 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT autolearn=ham
	autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id DA280C43461
	for <kvm@archiver.kernel.org>; Fri, 14 May 2021 10:04:46 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id BBAB461451
	for <kvm@archiver.kernel.org>; Fri, 14 May 2021 10:04:46 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S232987AbhENKFz (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Fri, 14 May 2021 06:05:55 -0400
Received: from mga04.intel.com ([192.55.52.120]:4949 "EHLO mga04.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S232800AbhENKFx (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 14 May 2021 06:05:53 -0400
IronPort-SDR: 
 z0S/FA/v/p8vZbUYlCluivB3qonxbG9eilKDqHKLZXkidr7U7dQyHTumbUKGKMIRRcxZvNiOD7
 COXCKp5/oaTw==
X-IronPort-AV: E=McAfee;i="6200,9189,9983"; a="198195255"
X-IronPort-AV: E=Sophos;i="5.82,299,1613462400";
   d="scan'208";a="198195255"
Received: from fmsmga005.fm.intel.com ([10.253.24.32])
  by fmsmga104.fm.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 14 May 2021 03:04:42 -0700
IronPort-SDR: 
 Os7nvULX0grsqC960ZtdHLoskEzG0z4vyNYpLl7H98YLmerkKXa1c+M6gPUGZxgHgQG5pA1yt1
 xQc9H7ECk3Qw==
X-IronPort-AV: E=Sophos;i="5.82,299,1613462400";
   d="scan'208";a="626910435"
Received: from unknown (HELO localhost.localdomain.bj.intel.com)
 ([10.240.193.73])
  by fmsmga005-auth.fm.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 14 May 2021 03:04:41 -0700
From: Zhu Lingshan <lingshan.zhu@intel.com>
To: jasowang@redhat.com, mst@redhat.com
Cc: virtualization@lists.linux-foundation.org, netdev@vger.kernel.org,
        kvm@vger.kernel.org, Zhu Lingshan <lingshan.zhu@intel.com>
Subject: [PATCH V2 1/2] vDPA/ifcvf: record virtio notify base
Date: Fri, 14 May 2021 17:59:12 +0800
Message-Id: <20210514095913.41777-2-lingshan.zhu@intel.com>
X-Mailer: git-send-email 2.27.0
In-Reply-To: <20210514095913.41777-1-lingshan.zhu@intel.com>
References: <20210514095913.41777-1-lingshan.zhu@intel.com>
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This commit records virtio notify base physical addr and
calculate doorbell physical address for vqs.

Signed-off-by: Zhu Lingshan <lingshan.zhu@intel.com>
---
 drivers/vdpa/ifcvf/ifcvf_base.c | 4 ++++
 drivers/vdpa/ifcvf/ifcvf_base.h | 2 ++
 2 files changed, 6 insertions(+)

```
