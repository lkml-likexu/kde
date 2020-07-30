#### [PATCH 1/5] PCI: Move PCI_VENDOR_ID_REDHAT definition to pci_ids.h
##### From: Huacai Chen <chenhc@lemote.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Huacai Chen <chenhc@lemote.com>
X-Patchwork-Id: 11690425
Return-Path: <SRS0=6Tui=BI=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 51BA314B7
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 29 Jul 2020 06:56:28 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 3689520809
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 29 Jul 2020 06:56:28 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=fail reason="signature verification failed" (2048-bit key)
 header.d=gmail.com header.i=@gmail.com header.b="dgtcd6tj"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727781AbgG2G41 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 29 Jul 2020 02:56:27 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:46540 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726367AbgG2G4Z (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 29 Jul 2020 02:56:25 -0400
Received: from mail-pg1-x541.google.com (mail-pg1-x541.google.com
 [IPv6:2607:f8b0:4864:20::541])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 7076DC061794;
        Tue, 28 Jul 2020 23:56:25 -0700 (PDT)
Received: by mail-pg1-x541.google.com with SMTP id p3so13751766pgh.3;
        Tue, 28 Jul 2020 23:56:25 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=sender:from:to:cc:subject:date:message-id;
        bh=xWIw178xfSixLgPUzYTe7I8j3e6PwAuVlCjEytmrmR0=;
        b=dgtcd6tjh0uEX3rlLPmlMzZu/Uv07s/IsFw3o4l2zLSnE+ho0R2rrG2kcjZFqLY2Pk
         iSs/ZdQRdmlv1ISB9+xV/nep911YhWdIsUyQN7PztMzvlf8hJO2k6JVHCPhpelXRhXxb
         pDZpexNdMWFfQG/IFm2M54P0fi+bYb6/hJWw/a8wYMUWsT3VIhBVWGisXGmAuR8n1aAm
         +xoIa4hipe4/lv1R+KrVvU1FOlRlyl6UPI5pcVLR6ckOG8X5wLO3RKR/tPk1YJLt2WZ9
         yy4h7xNUv+Lz2y+i842tctysMmRV4QkKG5nTGO62/GXnRdMOxExrZSDm6LjRTWqXCRmi
         fG7A==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:sender:from:to:cc:subject:date:message-id;
        bh=xWIw178xfSixLgPUzYTe7I8j3e6PwAuVlCjEytmrmR0=;
        b=ZtUbHStdc0I6Dwjv1oAjzKrFfojsQZLa+dAdemkdeimzXxDqWixA4q94BfBljUotgN
         nHmGXEp/A3e7L8/Ol0iIqBHr1CG2Ae8F+4ZdD4NVKuskBl2961Du95ixy8WMc9WRp4FI
         lDkmM01/fSc6Pbdt9yqBNpgtwrP2yQXmcMoO02esGDauJngRKd3VVhZbM0XXEQafZHQx
         Cw+HS7IHWlADeNfzrcQZvBZh8USIuIIrTztRLuC/9xNnDmh3zYbNAqMVtmN4jCz9JSrf
         HrwjAJa1LQwhlFqN5s17WwXmF7AyLJk9rDV/QHN8JIL2CijzkY36BI/xXWRCh2nSUuec
         QfVQ==
X-Gm-Message-State: AOAM532di70P+VIrh/rQh6pUk+dC0OmqnLvIhohwgWccE0YDzeprBZhJ
        OyWG8Xf0mLlH31pw5PqebpQ=
X-Google-Smtp-Source: 
 ABdhPJygd6nN+UYd24IN0o0Rpe/UczDjuVDaEFQjq54WAbA1vi7+YvcMGLQBvZQq5Zut4N2rVeLGYQ==
X-Received: by 2002:a62:ce88:: with SMTP id
 y130mr28386033pfg.37.1596005784985;
        Tue, 28 Jul 2020 23:56:24 -0700 (PDT)
Received: from software.domain.org (28.144.92.34.bc.googleusercontent.com.
 [34.92.144.28])
        by smtp.gmail.com with ESMTPSA id
 127sm1207202pgf.5.2020.07.28.23.56.21
        (version=TLS1_2 cipher=ECDHE-ECDSA-AES128-GCM-SHA256 bits=128/128);
        Tue, 28 Jul 2020 23:56:24 -0700 (PDT)
From: Huacai Chen <chenhc@lemote.com>
To: Thomas Bogendoerfer <tsbogend@alpha.franken.de>,
        Paolo Bonzini <pbonzini@redhat.com>,
        Aleksandar Markovic <aleksandar.qemu.devel@gmail.com>,
        Rob Herring <robh+dt@kernel.org>
Cc: linux-mips@vger.kernel.org, kvm@vger.kernel.org,
        Fuxin Zhang <zhangfx@lemote.com>,
        Huacai Chen <chenhuacai@gmail.com>,
        Jiaxun Yang <jiaxun.yang@flygoat.com>,
        Huacai Chen <chenhc@lemote.com>
Subject: [PATCH 1/5] PCI: Move PCI_VENDOR_ID_REDHAT definition to pci_ids.h
Date: Wed, 29 Jul 2020 14:58:35 +0800
Message-Id: <1596005919-29365-1-git-send-email-chenhc@lemote.com>
X-Mailer: git-send-email 2.7.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Instead of duplicating the PCI_VENDOR_ID_REDHAT definition everywhere,
move it to include/linux/pci_ids.h is better.

Signed-off-by: Huacai Chen <chenhc@lemote.com>
---
This patch has been merged into PCI tree, but the current MIPS tree need
it to avoid build error.

 drivers/gpu/drm/qxl/qxl_dev.h           | 2 --
 drivers/net/ethernet/rocker/rocker_hw.h | 1 -
 include/linux/pci_ids.h                 | 2 ++
 3 files changed, 2 insertions(+), 3 deletions(-)

```
#### [PATCH 1/4] KVM: SVM: nested: Don't allocate VMCB structures on stack
##### From: Joerg Roedel <joro@8bytes.org>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Joerg Roedel <joro@8bytes.org>
X-Patchwork-Id: 11691019
Return-Path: <SRS0=6Tui=BI=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 2C10C6C1
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 29 Jul 2020 13:23:19 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 1BB0620809
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 29 Jul 2020 13:23:19 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727085AbgG2NWs (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 29 Jul 2020 09:22:48 -0400
Received: from 8bytes.org ([81.169.241.247]:33806 "EHLO theia.8bytes.org"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726353AbgG2NWr (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 29 Jul 2020 09:22:47 -0400
Received: by theia.8bytes.org (Postfix, from userid 1000)
        id 08A37E4; Wed, 29 Jul 2020 15:22:45 +0200 (CEST)
From: Joerg Roedel <joro@8bytes.org>
To: Paolo Bonzini <pbonzini@redhat.com>
Cc: Sean Christopherson <sean.j.christopherson@intel.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org, Joerg Roedel <jroedel@suse.de>
Subject: [PATCH 1/4] KVM: SVM: nested: Don't allocate VMCB structures on stack
Date: Wed, 29 Jul 2020 15:22:31 +0200
Message-Id: <20200729132234.2346-2-joro@8bytes.org>
X-Mailer: git-send-email 2.17.1
In-Reply-To: <20200729132234.2346-1-joro@8bytes.org>
References: <20200729132234.2346-1-joro@8bytes.org>
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Joerg Roedel <jroedel@suse.de>

Do not allocate a vmcb_control_area and a vmcb_save_area on the stack,
as these structures will become larger with future extenstions of
SVM and thus the svm_set_nested_state() function will become a too large
stack frame.

Signed-off-by: Joerg Roedel <jroedel@suse.de>
---
 arch/x86/kvm/svm/nested.c | 44 ++++++++++++++++++++++++++-------------
 1 file changed, 30 insertions(+), 14 deletions(-)

```
#### linux-next: manual merge of the kvm tree with the tip tree
##### From: Stephen Rothwell <sfr@canb.auug.org.au>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Stephen Rothwell <sfr@canb.auug.org.au>
X-Patchwork-Id: 11690413
Return-Path: <SRS0=6Tui=BI=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 97F1F13B1
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 29 Jul 2020 06:47:19 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 7622220809
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 29 Jul 2020 06:47:19 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=canb.auug.org.au header.i=@canb.auug.org.au
 header.b="YjGyXU2U"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726948AbgG2GrQ (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 29 Jul 2020 02:47:16 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:45120 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726286AbgG2GrQ (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 29 Jul 2020 02:47:16 -0400
Received: from ozlabs.org (ozlabs.org [IPv6:2401:3900:2:1::2])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id BF447C061794;
        Tue, 28 Jul 2020 23:47:15 -0700 (PDT)
Received: from authenticated.ozlabs.org (localhost [127.0.0.1])
        (using TLSv1.3 with cipher TLS_AES_256_GCM_SHA384 (256/256 bits)
         key-exchange ECDHE (P-256) server-signature RSA-PSS (4096 bits)
 server-digest SHA256)
        (No client certificate requested)
        by mail.ozlabs.org (Postfix) with ESMTPSA id 4BGkcK12Y3z9sRW;
        Wed, 29 Jul 2020 16:47:13 +1000 (AEST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple; d=canb.auug.org.au;
        s=201702; t=1596005233;
        bh=ijyyUr82wI4HGbRSdFt2yLXZvyup+U2Kte8u90b/Go0=;
        h=Date:From:To:Cc:Subject:From;
        b=YjGyXU2UayxF+EpN+uQL/BM2Hyx/tT2nZSgTgjC1xzEkY6KSF9Yc22ixCNRNu0hjA
         BEAtGCl67giZnwKliNaKWPUhofKH92pD+8XXgyBufPMltFc4xqzmjPxsCbOZVNAkL+
         AwnXvyiM0DBLpTorLCJS7hc2bg7QeJz0oM4v0ennWaW5HD+FLD5Vz5TDO5QN/RsUat
         0QtxeEmGROekvXVZb8CD9BdkNSk2bP0yW61QZa3NdTqjmqGGqcGSriJgVxHEYIdCKR
         UJQuSy4u9FargUgsSz2HwgSLAw0KzDpw0mPGkEujn09EFdB+g6MsogXClPkpFssf9K
         sLZy6z913zr8g==
Date: Wed, 29 Jul 2020 16:47:12 +1000
From: Stephen Rothwell <sfr@canb.auug.org.au>
To: Paolo Bonzini <pbonzini@redhat.com>, KVM <kvm@vger.kernel.org>,
        Thomas Gleixner <tglx@linutronix.de>,
        Ingo Molnar <mingo@elte.hu>, "H. Peter Anvin" <hpa@zytor.com>,
        Peter Zijlstra <peterz@infradead.org>
Cc: Linux Next Mailing List <linux-next@vger.kernel.org>,
        Linux Kernel Mailing List <linux-kernel@vger.kernel.org>,
        Andy Lutomirski <luto@kernel.org>,
        Vitaly Kuznetsov <vkuznets@redhat.com>
Subject: linux-next: manual merge of the kvm tree with the tip tree
Message-ID: <20200729164712.4f429876@canb.auug.org.au>
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Hi all,

Today's linux-next merge of the kvm tree got a conflict in:

  arch/x86/kernel/kvm.c

between commits:

  b037b09b9058 ("x86/entry: Rename idtentry_enter/exit_cond_rcu() to idtentry_enter/exit()")
  a27a0a55495c ("x86/entry: Cleanup idtentry_enter/exit")

from the tip tree and commits:

  b1d405751cd5 ("KVM: x86: Switch KVM guest to using interrupts for page ready APF delivery")
  26d05b368a5c ("Merge branch 'kvm-async-pf-int' into HEAD")

from the kvm tree.

I fixed it up (see below) and can carry the fix as necessary. This
is now fixed as far as linux-next is concerned, but any non trivial
conflicts should be mentioned to your upstream maintainer when your tree
is submitted for merging.  You may also want to consider cooperating
with the maintainer of the conflicting tree to minimise any particularly
complex conflicts.

```
#### [PATCH] perf/x86/svm: Convert 'perf kvm stat report' output lowercase to uppercase
##### From: Haiwei Li <lihaiwei.kernel@gmail.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Haiwei Li <lihaiwei.kernel@gmail.com>
X-Patchwork-Id: 11690385
Return-Path: <SRS0=6Tui=BI=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id E9A6213B1
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 29 Jul 2020 06:24:56 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id BFE13207F5
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 29 Jul 2020 06:24:56 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=gmail.com header.i=@gmail.com
 header.b="J66knnMa"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726797AbgG2GYx (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 29 Jul 2020 02:24:53 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:41684 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726286AbgG2GYw (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 29 Jul 2020 02:24:52 -0400
Received: from mail-pf1-x443.google.com (mail-pf1-x443.google.com
 [IPv6:2607:f8b0:4864:20::443])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id BF9CCC061794;
        Tue, 28 Jul 2020 23:24:52 -0700 (PDT)
Received: by mail-pf1-x443.google.com with SMTP id d188so6365812pfd.2;
        Tue, 28 Jul 2020 23:24:52 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=to:cc:from:subject:message-id:date:user-agent:mime-version
         :content-language:content-transfer-encoding;
        bh=sMFl8A9jPxjNMZOvebjCYmlhRA1mXGyUaqgUwzyXfq0=;
        b=J66knnMasKtQuXL0XnyYfUftY3b90hkTLSjlUXZrnfi3cAomEhuNTUJ04QBBiPbelO
         GBVwvatTo/r1aarV30knngJW3xfSocwQFFkY7jlcEEV4xoyIGxXUTRfD2AsbzPpi0rPz
         VbbaxTZ3AzOIEDKFT2DN/RGAb1A5bbKKeUPh7eDa7mvEPNG09B6aWmoJJeY/GLgTepOE
         gQ0hX44bo6mae/mhLOoGRwyvtdvOrfztmsdda5RrdFMmnw8Mh12muZNS5Noa77Z5xM8K
         rXV1vsG0s05hjPTwFkqXFfh80DCVf7r8PHgkjp+AgdYFI45u84Ppyk20Z8DamAnY02Wd
         J1JQ==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:to:cc:from:subject:message-id:date:user-agent
         :mime-version:content-language:content-transfer-encoding;
        bh=sMFl8A9jPxjNMZOvebjCYmlhRA1mXGyUaqgUwzyXfq0=;
        b=Nq5vh69DLNvI97HPl8XmqzuowjAXFopaIGB2YdLc40O8uUui2bAvztHIkYSmTs8nXG
         rQwxx5xeQ2+knRfgy++D1FEj+eZ31EQBTrQJnzdr5pqmIFul+stAQe3osfBcHBZBSPdp
         5A/8wBaajxRGKks7JD+otYDR/A8uFYYdfONJCt5DZehsGi9OW18G0SbUr3MLV+oD5QMu
         qZC08EjzTnowI1/JeZbBsmBcHcBIu7H66juzBO1vfGuiFy/9ibpr+2fAyV9GFt+yM6hH
         sZaUKviEeGQmTL/edg5TZ0c7zqW8t+7EulVODuWxaZK/p3Qyd8hCjNE+uhEwI4rlSCds
         T4nw==
X-Gm-Message-State: AOAM532vO531AHdZ5WWnVyQ1HXCCpirfVcpDsaOi3AOEv0Fm/26Flt5T
        0lb9OepCK8gawUqdQQ4bPK0pMTjp7w==
X-Google-Smtp-Source: 
 ABdhPJzNBOg0gxTtUNOgmKD3LPQ210Qcu0zYNNCIbxNbYwmbKC2WmetoyLCzCAAygzMobKggZhg2BQ==
X-Received: by 2002:aa7:95b6:: with SMTP id a22mr4885606pfk.152.1596003891707;
        Tue, 28 Jul 2020 23:24:51 -0700 (PDT)
Received: from [127.0.0.1] ([103.7.29.6])
        by smtp.gmail.com with ESMTPSA id
 d22sm996502pgm.93.2020.07.28.23.24.47
        (version=TLS1_3 cipher=TLS_AES_128_GCM_SHA256 bits=128/128);
        Tue, 28 Jul 2020 23:24:51 -0700 (PDT)
To: "linux-kernel@vger.kernel.org" <linux-kernel@vger.kernel.org>,
        kvm@vger.kernel.org, "x86@kernel.org" <x86@kernel.org>
Cc: acme@redhat.com, "hpa@zytor.com" <hpa@zytor.com>,
        "bp@alien8.de" <bp@alien8.de>,
        "mingo@redhat.com" <mingo@redhat.com>,
        "tglx@linutronix.de" <tglx@linutronix.de>,
        "joro@8bytes.org" <joro@8bytes.org>, jmattson@google.com,
        wanpengli@tencent.com, "vkuznets@redhat.com" <vkuznets@redhat.com>,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        "pbonzini@redhat.com" <pbonzini@redhat.com>
From: Haiwei Li <lihaiwei.kernel@gmail.com>
Subject: [PATCH] perf/x86/svm: Convert 'perf kvm stat report' output lowercase
 to uppercase
Message-ID: <fdc7e57d-4fd6-4d49-22e6-b18003034ff5@gmail.com>
Date: Wed, 29 Jul 2020 14:24:39 +0800
User-Agent: Mozilla/5.0 (Macintosh; Intel Mac OS X 10.15; rv:68.0)
 Gecko/20100101 Thunderbird/68.10.0
MIME-Version: 1.0
Content-Language: en-US
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Haiwei Li <lihaiwei@tencent.com>

The reason output of 'perf kvm stat report --event=vmexit' is uppercase 
on VMX and lowercase on SVM.

To be consistent with VMX, convert lowercase to uppercase.

Signed-off-by: Haiwei Li <lihaiwei@tencent.com>
---
  arch/x86/include/uapi/asm/svm.h       | 184 
+++++++++++++++++-----------------
  tools/arch/x86/include/uapi/asm/svm.h | 184 
+++++++++++++++++-----------------
  2 files changed, 184 insertions(+), 184 deletions(-)

diff --git a/arch/x86/include/uapi/asm/svm.h 
```
