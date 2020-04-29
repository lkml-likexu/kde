#### [PATCH] kvm: Fix false positive RCU usage warning
##### From: madhuparnabhowmik10@gmail.com

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Madhuparna Bhowmik <madhuparnabhowmik10@gmail.com>
X-Patchwork-Id: 11515017
Return-Path: <SRS0=1gOX=6M=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 03CC51575
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 28 Apr 2020 15:53:03 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id DF675206C0
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 28 Apr 2020 15:53:02 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=gmail.com header.i=@gmail.com
 header.b="fr2F0Coj"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728174AbgD1Pw7 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 28 Apr 2020 11:52:59 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:47336 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-FAIL-OK-FAIL)
        by vger.kernel.org with ESMTP id S1727920AbgD1Pw7 (ORCPT
        <rfc822;kvm@vger.kernel.org>); Tue, 28 Apr 2020 11:52:59 -0400
Received: from mail-pf1-x443.google.com (mail-pf1-x443.google.com
 [IPv6:2607:f8b0:4864:20::443])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 72448C03C1AB;
        Tue, 28 Apr 2020 08:52:59 -0700 (PDT)
Received: by mail-pf1-x443.google.com with SMTP id y25so10860111pfn.5;
        Tue, 28 Apr 2020 08:52:59 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=from:to:cc:subject:date:message-id;
        bh=2c6uCE675m96/FbxOp/+YpjzTr8Ax/d5qUPMW5Gsuec=;
        b=fr2F0CojibBY6glD0TM6oVEEfkQR6dQ6Xta08+rELpBa63RJXHlQ2mjr8SnXIaQlFy
         9RQMGLd8lLgdOc1MTp+Wi0GWvc8S3nW8SVXeYeY/0/LC0PPafhRG+4JF7ffkYgvIhxDV
         7maE/trbhJ6Ios0CzPbWJTvYGUwsvrflXuGW/+tYnfQG4M7EFqyKKflPqIITL47MKb/Z
         d7VUKbgKbZywljxEDdeQCIfdJ1rAql+/0UW4r3avCnc46Ccf6GpzeSV35ZCihxt4DCZR
         5kD8b0tsu/Fno/T+Ax8w+h8OjNbveBrMTs3Xg8R6+CEP4e6Uzp08FvHSxdaco3GMQ2Zy
         Uqkg==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id;
        bh=2c6uCE675m96/FbxOp/+YpjzTr8Ax/d5qUPMW5Gsuec=;
        b=ozBNndw+QmJnkzo509sjglolW9f6rV4aa+oe1/OYrVNv+5bo2ZgyZX1w3EIHwk01R6
         NWMTtwdlpyXSDB7Yz4B1GDquQBPyq4mGFQitofLX0sDn7Vq2N3LXJOq9LOwg2T+JQ4dW
         i+4x4P19kHW8LffX9ljctvC5JruEGVFI+Uq2i1dtu4e0obDuBft8vdIWwr5vMMdVb8K/
         vlIrAw1CZlvhB9TJnvIvVUyIZ6tAGOxynyb+F4SVPJ+qk4TiUXfY1xPv4LKSYxRiIP3s
         Smd/e4HRSe6DEFtoiJTf4KIK6rs7AlDE+LTHxOXkBeXsXMAyKKau2KA3kKebCarsQcLU
         IvJA==
X-Gm-Message-State: AGi0PuZd0ggDjbLCO+W+M4v/Cml+AXy0P7rLXsJG9bABHWvuOc8TPPh2
        TdoV7flxbgt+BZt72H2HMQ==
X-Google-Smtp-Source: 
 APiQypLkMPf9eFxnHsSePauRQebG54rsN5Dm5KoC2usbs2Crxz6EJNZG48I0Ks+vIHv3SzRpf3pkAg==
X-Received: by 2002:a63:2403:: with SMTP id k3mr28091220pgk.295.1588089179049;
        Tue, 28 Apr 2020 08:52:59 -0700 (PDT)
Received: from localhost.localdomain ([2402:3a80:d33:c58:9c84:8ece:9d0f:426b])
        by smtp.gmail.com with ESMTPSA id
 mn1sm2410814pjb.24.2020.04.28.08.52.53
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Tue, 28 Apr 2020 08:52:58 -0700 (PDT)
From: madhuparnabhowmik10@gmail.com
To: sean.j.christopherson@intel.com, wanpengli@tencent.com,
        jmattson@google.com, tglx@linutronix.de, bp@alien8.de,
        mingo@redhat.com
Cc: cai@lca.pw, paulmck@kernel.org, joel@joelfernandes.org,
        frextrite@gmail.com, x86@kernel.org, kvm@vger.kernel.org,
        linux-kernel-mentees@lists.linuxfoundation.org,
        linux-kernel@vger.kernel.org,
        Madhuparna Bhowmik <madhuparnabhowmik10@gmail.com>
Subject: [PATCH] kvm: Fix false positive RCU usage warning
Date: Tue, 28 Apr 2020 21:22:49 +0530
Message-Id: <20200428155249.19990-1-madhuparnabhowmik10@gmail.com>
X-Mailer: git-send-email 2.17.1
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Madhuparna Bhowmik <madhuparnabhowmik10@gmail.com>

Fix the following false positive warnings:

[ 9403.765413][T61744] =============================
[ 9403.786541][T61744] WARNING: suspicious RCU usage
[ 9403.807865][T61744] 5.7.0-rc1-next-20200417 #4 Tainted: G             L
[ 9403.838945][T61744] -----------------------------
[ 9403.860099][T61744] arch/x86/kvm/mmu/page_track.c:257 RCU-list traversed in non-reader section!!

and

[ 9405.859252][T61751] =============================
[ 9405.859258][T61751] WARNING: suspicious RCU usage
[ 9405.880867][T61755] -----------------------------
[ 9405.911936][T61751] 5.7.0-rc1-next-20200417 #4 Tainted: G             L
[ 9405.911942][T61751] -----------------------------
[ 9405.911950][T61751] arch/x86/kvm/mmu/page_track.c:232 RCU-list traversed in non-reader section!!

Since srcu read lock is held, these are false positive warnings.
Therefore, pass condition srcu_read_lock_held() to
list_for_each_entry_rcu().

Reported-by: kernel test robot <lkp@intel.com>
Signed-off-by: Madhuparna Bhowmik <madhuparnabhowmik10@gmail.com>
---
 arch/x86/kvm/mmu/page_track.c | 6 ++++--
 1 file changed, 4 insertions(+), 2 deletions(-)

```
#### [PATCH] KVM: MIPS/TLB: Remove Unneeded semicolon in tlb.c
##### From: Jason Yan <yanaijie@huawei.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Jason Yan <yanaijie@huawei.com>
X-Patchwork-Id: 11513931
Return-Path: <SRS0=1gOX=6M=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 2626D92C
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 28 Apr 2020 06:34:06 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 1714B20775
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 28 Apr 2020 06:34:06 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726572AbgD1Gdg (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 28 Apr 2020 02:33:36 -0400
Received: from szxga05-in.huawei.com ([45.249.212.191]:3320 "EHLO huawei.com"
        rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org with ESMTP
        id S1726279AbgD1Gdc (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 28 Apr 2020 02:33:32 -0400
Received: from DGGEMS407-HUB.china.huawei.com (unknown [172.30.72.59])
        by Forcepoint Email with ESMTP id 7E2568747B62372AF1AB;
        Tue, 28 Apr 2020 14:33:27 +0800 (CST)
Received: from huawei.com (10.175.124.28) by DGGEMS407-HUB.china.huawei.com
 (10.3.19.207) with Microsoft SMTP Server id 14.3.487.0; Tue, 28 Apr 2020
 14:33:19 +0800
From: Jason Yan <yanaijie@huawei.com>
To: <tsbogend@alpha.franken.de>, <ast@kernel.org>,
        <daniel@iogearbox.net>, <kafai@fb.com>, <songliubraving@fb.com>,
        <yhs@fb.com>, <andriin@fb.com>, <john.fastabend@gmail.com>,
        <kpsingh@chromium.org>, <linux-mips@vger.kernel.org>,
        <kvm@vger.kernel.org>, <linux-kernel@vger.kernel.org>,
        <netdev@vger.kernel.org>, <bpf@vger.kernel.org>
CC: Jason Yan <yanaijie@huawei.com>
Subject: [PATCH] KVM: MIPS/TLB: Remove Unneeded semicolon in tlb.c
Date: Tue, 28 Apr 2020 14:32:45 +0800
Message-ID: <20200428063245.32776-1-yanaijie@huawei.com>
X-Mailer: git-send-email 2.21.1
MIME-Version: 1.0
X-Originating-IP: [10.175.124.28]
X-CFilter-Loop: Reflected
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Fix the following coccicheck warning:

arch/mips/kvm/tlb.c:472:2-3: Unneeded semicolon
arch/mips/kvm/tlb.c:489:2-3: Unneeded semicolon

Signed-off-by: Jason Yan <yanaijie@huawei.com>
---
 arch/mips/kvm/tlb.c | 4 ++--
 1 file changed, 2 insertions(+), 2 deletions(-)

```
#### [PATCH v12 01/17] RISC-V: Add hypervisor extension related CSR defines
##### From: Anup Patel <anup.patel@wdc.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Anup Patel <Anup.Patel@wdc.com>
X-Patchwork-Id: 11513977
Return-Path: <SRS0=1gOX=6M=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 477BF14B4
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 28 Apr 2020 07:33:58 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 254D9206D6
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 28 Apr 2020 07:33:58 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=fail reason="signature verification failed" (2048-bit key)
 header.d=wdc.com header.i=@wdc.com header.b="Vda9aIQr";
	dkim=pass (1024-bit key) header.d=sharedspace.onmicrosoft.com
 header.i=@sharedspace.onmicrosoft.com header.b="XISfYNao"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726423AbgD1Hdx (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 28 Apr 2020 03:33:53 -0400
Received: from esa2.hgst.iphmx.com ([68.232.143.124]:57156 "EHLO
        esa2.hgst.iphmx.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726256AbgD1Hdw (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 28 Apr 2020 03:33:52 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=simple/simple;
  d=wdc.com; i=@wdc.com; q=dns/txt; s=dkim.wdc.com;
  t=1588059274; x=1619595274;
  h=from:to:cc:subject:date:message-id:in-reply-to:
   references:content-transfer-encoding:mime-version;
  bh=fS1pOZ9tSgfBg3vFDRjMcFP/v25WbM3UcpHa2814axo=;
  b=Vda9aIQrTkmB4STDcykj6fXOiPAJBhOzFSFU+S6QahCYqQZ8fthbbBj/
   N/ZJEPk9/gW//V1Po4ghzhcSqkREuqN+r0LmoZn14Kcgo2d3vFcIW4Ky4
   72D8yOPzmq/vu11RHudhgqUzfkyGhAfOFw2z0b5aY9wKGR7t8ZfRT2c/r
   e3tJb7u4DLNSoROV7KBvq4Ubzdaqwg8TCwKSt/BqOoaOenU7BOvs/2M6Z
   IWsBxbtN90zQzdH5JwrCQZS7PWS3kQI7GQkknDcwNLwFOjb65HOOgC9Qn
   J637g+fFj84ZIKMTfHqQUFbt6uyRiDE4sdIJ2eFpMgA1hrJGP/AubEtCQ
   A==;
IronPort-SDR: 
 9pT1nIlVYvyayynuD/4J4rwjUnig2Uhf4RaPA6D6uBWvfjo25+lCh22FcWGiLXGZEKK4t8KObL
 dJPyHSBkrNB9cSicK8Hx46SDVpYNI1vo/Bj5Y7k6Fu7su6oZHqCEBxq1UdkF8EESTnkQci3wxg
 xqclhHKjVccMneoNp0txwMlXS12rEQXEwXyGXGlip+52faZTP1OpL30asz7INYK4MqlrDynY1b
 iozY9zzBwmD5ghPPjxuS1o1zATXrR5+ACTjva3vsJxnkg5vVjoR3sTlkozl9vpGgUoNDRKO6Qt
 OuE=
X-IronPort-AV: E=Sophos;i="5.73,327,1583164800";
   d="scan'208";a="238865794"
Received: from mail-co1nam04lp2056.outbound.protection.outlook.com (HELO
 NAM04-CO1-obe.outbound.protection.outlook.com) ([104.47.45.56])
  by ob1.hgst.iphmx.com with ESMTP; 28 Apr 2020 15:34:32 +0800
ARC-Seal: i=1; a=rsa-sha256; s=arcselector9901; d=microsoft.com; cv=none;
 b=MumHdT1JKCiCbNM1lragTrW6S1AJxgwgsN7HDBZzAkqG/5iEAQWtD1UldFvHH+j2jz2fWGFz/P3pC0urMQyhA28AS/dnOTXd6JDXMAGFEN/PWggHWX6LEnzaS7jWDDuiOz7zm9n3FGhR/j52T5YG8c1z3fBQRfzLkVx5QQmuW4+yt6pbQESmOjJnbwJ9HM0nVX2ZPeobCcf7l6mSJOSZxI0BpfbHdqcpCQSbp8G6OpuXy4481LS7uf60QOd0S318Z3CeCdQQ5SnDVEnSF2tMcZMJprY+zfCNXpGDVLT38+up4qhcUXADrOJyFPs29OShdsmBNax/3SUqrUxwHVgvaA==
ARC-Message-Signature: i=1; a=rsa-sha256; c=relaxed/relaxed; d=microsoft.com;
 s=arcselector9901;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=7cM5zvagwwwCQPQYhTln098aGMAhEwWyhhwu44uXGfs=;
 b=PAFEd1ulqr2sH8UIuz97oU/g2A4sVlKe6usFF1V6ngPnMLhyXLG9aJOCpbvwrvgMOqfmgWQdhjz1LG+RwNH/1GeDBPwidANZhZJP87AGOzbGLAbIudpEek4gD62Z7KFXIXjg57oiphoIx0wyvc9YDWPY6pEWTouNeeJqJg+L/ZhgNEYTwpePBCAsE/lkG30BwIYKdLE3Q7WwmuqEcCfZUROlH2M0L4NzTjeNOkm6f5CzV6bhIbCwD1qommUz9VQPx3qwWFmWPmUFZbFfB7Hnih3woPVMcefoKwoylTKJ4wK5VtjwoVdL/a+yEpIqmPxm2VkvaMHoOIgvquq3bKDNWA==
ARC-Authentication-Results: i=1; mx.microsoft.com 1; spf=pass
 smtp.mailfrom=wdc.com; dmarc=pass action=none header.from=wdc.com; dkim=pass
 header.d=wdc.com; arc=none
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
 d=sharedspace.onmicrosoft.com; s=selector2-sharedspace-onmicrosoft-com;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=7cM5zvagwwwCQPQYhTln098aGMAhEwWyhhwu44uXGfs=;
 b=XISfYNaoR2VW4JvllJEkWtLyB9ECGW21CnBE6ysrk+FqlSxxWKNnjCtoF6eyYNUubFabONNzngUxBClOS26o+cZXzhx1pgjWdEKU/6e2lARhbDSi+qKDdwXtW7OEG4NhewrHVINyIR3tRXt7BEuClyQ+3IQ9E/4GUhfitUQhnaU=
Authentication-Results: dabbelt.com; dkim=none (message not signed)
 header.d=none;dabbelt.com; dmarc=none action=none header.from=wdc.com;
Received: from DM6PR04MB6201.namprd04.prod.outlook.com (2603:10b6:5:127::32)
 by DM6PR04MB4538.namprd04.prod.outlook.com (2603:10b6:5:21::16) with
 Microsoft SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.2937.22; Tue, 28 Apr
 2020 07:33:50 +0000
Received: from DM6PR04MB6201.namprd04.prod.outlook.com
 ([fe80::f8b3:c124:482b:52e0]) by DM6PR04MB6201.namprd04.prod.outlook.com
 ([fe80::f8b3:c124:482b:52e0%5]) with mapi id 15.20.2937.023; Tue, 28 Apr 2020
 07:33:50 +0000
From: Anup Patel <anup.patel@wdc.com>
To: Palmer Dabbelt <palmer@dabbelt.com>,
        Palmer Dabbelt <palmerdabbelt@google.com>,
        Paul Walmsley <paul.walmsley@sifive.com>,
        Albert Ou <aou@eecs.berkeley.edu>,
        Paolo Bonzini <pbonzini@redhat.com>
Cc: Alexander Graf <graf@amazon.com>,
        Atish Patra <atish.patra@wdc.com>,
        Alistair Francis <Alistair.Francis@wdc.com>,
        Damien Le Moal <damien.lemoal@wdc.com>,
        Anup Patel <anup@brainfault.org>, kvm@vger.kernel.org,
        kvm-riscv@lists.infradead.org, linux-riscv@lists.infradead.org,
        linux-kernel@vger.kernel.org, Anup Patel <anup.patel@wdc.com>
Subject: [PATCH v12 01/17] RISC-V: Add hypervisor extension related CSR
 defines
Date: Tue, 28 Apr 2020 13:02:56 +0530
Message-Id: <20200428073312.324684-2-anup.patel@wdc.com>
X-Mailer: git-send-email 2.25.1
In-Reply-To: <20200428073312.324684-1-anup.patel@wdc.com>
References: <20200428073312.324684-1-anup.patel@wdc.com>
X-ClientProxiedBy: MAXPR01CA0073.INDPRD01.PROD.OUTLOOK.COM
 (2603:1096:a00:49::15) To DM6PR04MB6201.namprd04.prod.outlook.com
 (2603:10b6:5:127::32)
MIME-Version: 1.0
X-MS-Exchange-MessageSentRepresentingType: 1
Received: from wdc.com (106.51.31.156) by
 MAXPR01CA0073.INDPRD01.PROD.OUTLOOK.COM (2603:1096:a00:49::15) with Microsoft
 SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.2958.19 via Frontend
 Transport; Tue, 28 Apr 2020 07:33:44 +0000
X-Mailer: git-send-email 2.25.1
X-Originating-IP: [106.51.31.156]
X-MS-PublicTrafficType: Email
X-MS-Office365-Filtering-HT: Tenant
X-MS-Office365-Filtering-Correlation-Id: 4e47d305-d850-4021-01e2-08d7eb467e77
X-MS-TrafficTypeDiagnostic: DM6PR04MB4538:
X-MS-Exchange-Transport-Forked: True
X-Microsoft-Antispam-PRVS: 
 <DM6PR04MB453898547E856B50ED7AAAF58DAC0@DM6PR04MB4538.namprd04.prod.outlook.com>
WDCIPOUTBOUND: EOP-TRUE
X-MS-Oob-TLC-OOBClassifiers: OLM:11;
X-Forefront-PRVS: 0387D64A71
X-Forefront-Antispam-Report: 
 CIP:255.255.255.255;CTRY:;LANG:en;SCL:1;SRV:;IPV:NLI;SFV:NSPM;H:DM6PR04MB6201.namprd04.prod.outlook.com;PTR:;CAT:NONE;SFTY:;SFS:(4636009)(366004)(39860400002)(136003)(396003)(346002)(376002)(55016002)(6666004)(1006002)(8886007)(55236004)(956004)(2906002)(1076003)(2616005)(44832011)(86362001)(8676002)(5660300002)(16526019)(7416002)(478600001)(36756003)(66476007)(54906003)(26005)(186003)(4326008)(110136005)(66946007)(66556008)(8936002)(7696005)(316002)(52116002)(81156014);DIR:OUT;SFP:1102;
X-MS-Exchange-SenderADCheck: 1
X-Microsoft-Antispam: BCL:0;
X-Microsoft-Antispam-Message-Info: 
 Mk6dp0pv9o4jRAhISKvJ5viqXAS+aPV5lCJUg70kX7lXruQMqYl8ne6U+V6x/Wq0Sx7j9He5OM6wkznM4OEcnnuijTxxMxqAI/SJHiqqdXYVn8vxV3yBTvyNDcqtY9Ss5yrHp0xabSbwvZMaYWesiIvAZIDnIfTS9EP4MnZqYLnXdJhDHoFYd6RsPXbyNuQGDWR4JQhIICGteOQde6YmF/P1KoemIfq5wOcEJ1qZ6oHRJqtlRUYlBo2+NhtaDZ67aBW4+MtKfvAJtg6pPPVXV04tWfIdX16JrDh0QcNGQvdJaer7UIbylsdpPq/3LsI4S1Xl6qLRXx+r0Kii9hs9dcJNQQb2TA9GcnMYXy6QLTbaMXji0K65d4Xk01k/AnJe848CL8/BHFvEkzZ8c0OUCbpheZiUL/Wv1M41eDlmOF/cyKuh+UncEttPKbyLH30x
X-MS-Exchange-AntiSpam-MessageData: 
 bq1nsOzZivLxG8FaPBgm26aHhLD+wy+4f6ihl9TWBQ6n2W8ORL9xLPDaPnaFDEyO/Eiuj0jjgjfnkoB/WhkLNJU+Mqknpjr5yo/m/Vs15vKXDRDu9zNbSbclJGlI/OFHUD71nnbAYrJ7hP7OY9dFqaHX2qFbE/zFQ+lvTY545P/aTcaPr3UCYyxrgjZ7cq6rY67qPzCuu1KPe+lfkz8kvLLc5VaHhN6Zt6Ycatu0iDR4/rlmlZbE+rDkY9YxpXwS8FqZrX9/OAVzXzr52Yjzef7DK6QK2eYHoFafoqTG+0r8X1GCFAEAWO8RcCt87k1FiawtlIxWWwa6P7puX3zJtPi6vJwckzpkyFjDAnyHjUJtuK13oWA1tnVKG7VSaICbiDQuBzNEvOs5sC1ZaeWHqIB7NCUC+QHCgfmHGYmNKitjBsLe6wYV5XTJuSmjhx8r04dKLc6Cx4xH+mYmcZWZPct/JweuppIKkSYqr+08fbwtxynhd/ybii3pE36xlRfN2PXRhiEmDidlwacVCVjCZm+2/K2uMmaBXcvWvnlc0UqEE/BlnGs9oMJ7O3TZ6n+1r3s5PPIt09nHWsIFZLuBLlPesBEEIKRXC5GnXXeuSNSiwYbZTrOvE6PnAxhBUJjNF5kyrZf1X+WwszHCkyKUfRLR4Q2kWbbAFcy3GxoErhJ2ED2J5uZVu7aMB+OaV4Tg6vhqtjk4tAr2aawlCblbVUBTJRNBRN0zBuHEp9hQnx8ou8orP//7XiWSYlozkHjFS30Wbn8xt8OADxNwUmD5cbE/pjHDTePWWdlt5SDR9YQ=
X-OriginatorOrg: wdc.com
X-MS-Exchange-CrossTenant-Network-Message-Id: 
 4e47d305-d850-4021-01e2-08d7eb467e77
X-MS-Exchange-CrossTenant-OriginalArrivalTime: 28 Apr 2020 07:33:49.9909
 (UTC)
X-MS-Exchange-CrossTenant-FromEntityHeader: Hosted
X-MS-Exchange-CrossTenant-Id: b61c8803-16f3-4c35-9b17-6f65f441df86
X-MS-Exchange-CrossTenant-MailboxType: HOSTED
X-MS-Exchange-CrossTenant-UserPrincipalName: 
 TcHj9s54Huykl7XaZQ01YjKOhXgAV/nzbUP4QdmYrfij9iO2UehOt8/4ILExVmWXXDcciLeD3kj9k0fMQR342g==
X-MS-Exchange-Transport-CrossTenantHeadersStamped: DM6PR04MB4538
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This patch extends asm/csr.h by adding RISC-V hypervisor extension
related defines.

Signed-off-by: Anup Patel <anup.patel@wdc.com>
Acked-by: Paolo Bonzini <pbonzini@redhat.com>
Reviewed-by: Paolo Bonzini <pbonzini@redhat.com>
Reviewed-by: Alexander Graf <graf@amazon.com>
---
 arch/riscv/include/asm/csr.h | 85 ++++++++++++++++++++++++++++++++++++
 1 file changed, 85 insertions(+)

```
#### [PATCH kvm-unit-tests] svm: Fix nmi hlt test to fail test correctly
##### From: Cathy Avery <cavery@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Cathy Avery <cavery@redhat.com>
X-Patchwork-Id: 11515371
Return-Path: <SRS0=1gOX=6M=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 4589A112C
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 28 Apr 2020 18:48:20 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 2EEFE206A1
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 28 Apr 2020 18:48:20 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="QaeipvLq"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1730683AbgD1SsQ (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 28 Apr 2020 14:48:16 -0400
Received: from us-smtp-1.mimecast.com ([207.211.31.81]:40165 "EHLO
        us-smtp-delivery-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S1730303AbgD1SlG (ORCPT
        <rfc822;kvm@vger.kernel.org>); Tue, 28 Apr 2020 14:41:06 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1588099265;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=2JvJAM5p12RcumIJnmGpEzfcPG1ShzjNWymeqXsNBPQ=;
        b=QaeipvLqHfELP3LhF6d1X+GJiGkD8l89y2zd6KQh4W1KC/Z25xtVvlDN9EDBA96UcpHn2m
        5CLbGoU+r8WtT04A6jN25CSzzWaWh3qDJTNl9nAHQ0Ecs7DsaPtnA97KoSuCDBtJQqVvzZ
        7POmfgEYt2oUIL4K98yc0p8xu+poHAs=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-43-hojDiYcrPpK329HM2OBAGw-1; Tue, 28 Apr 2020 14:41:01 -0400
X-MC-Unique: hojDiYcrPpK329HM2OBAGw-1
Received: from smtp.corp.redhat.com (int-mx06.intmail.prod.int.phx2.redhat.com
 [10.5.11.16])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 0110B107ACCA;
        Tue, 28 Apr 2020 18:41:01 +0000 (UTC)
Received: from virtlab710.virt.lab.eng.bos.redhat.com
 (virtlab710.virt.lab.eng.bos.redhat.com [10.19.152.252])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 6DC085C1BD;
        Tue, 28 Apr 2020 18:41:00 +0000 (UTC)
From: Cathy Avery <cavery@redhat.com>
To: linux-kernel@vger.kernel.org, kvm@vger.kernel.org,
        pbonzini@redhat.com
Subject: [PATCH kvm-unit-tests] svm: Fix nmi hlt test to fail test correctly
Date: Tue, 28 Apr 2020 14:41:00 -0400
Message-Id: <20200428184100.5426-1-cavery@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.16
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The last test does not return vmmcall on fail resulting
in passing the entire test.

Signed-off-by: Cathy Avery <cavery@redhat.com>
---
 x86/svm_tests.c | 1 +
 1 file changed, 1 insertion(+)

```
#### [PATCH v4 1/7] KVM: VMX: Introduce generic fastpath handler
##### From: Wanpeng Li <kernellwp@gmail.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Wanpeng Li <kernellwp@gmail.com>
X-Patchwork-Id: 11513887
Return-Path: <SRS0=1gOX=6M=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id D609B14DD
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 28 Apr 2020 06:23:47 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id BD06A206B9
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 28 Apr 2020 06:23:47 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=gmail.com header.i=@gmail.com
 header.b="fECfBrBs"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726445AbgD1GXo (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 28 Apr 2020 02:23:44 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:42662 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-FAIL-OK-FAIL)
        by vger.kernel.org with ESMTP id S1726430AbgD1GXn (ORCPT
        <rfc822;kvm@vger.kernel.org>); Tue, 28 Apr 2020 02:23:43 -0400
Received: from mail-pg1-x541.google.com (mail-pg1-x541.google.com
 [IPv6:2607:f8b0:4864:20::541])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id BB202C03C1A9;
        Mon, 27 Apr 2020 23:23:42 -0700 (PDT)
Received: by mail-pg1-x541.google.com with SMTP id o15so9829103pgi.1;
        Mon, 27 Apr 2020 23:23:42 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=from:to:cc:subject:date:message-id:in-reply-to:references;
        bh=pyGp7grSiZpObxZrTgZ2GmGoqZvme1lxk38SftFA0lc=;
        b=fECfBrBsZgxeek/QXB19YDGD3bP/vi62URcqoJCCJ5xd9hmkWUhcgCZoLFdi1Full4
         AGxSqhCBJ2KL700zuXaAxmVO+kGsiTMsJmHMLc02bCz06rivuJ0liO7jnqcylYvn0Fe/
         wtMANRLPEI36qRmGcYb3ZE9zGV5aVES+6GETcZt3qCIha0hf4c75VvGq5Ck6AspiLb4v
         dm+EB4lKPMUVv6eCoLY/IoLFXqAc1gpy2XChp5GOq48ZKaX6xhSQjXUqSk2IS7v/gfzo
         x3/HCRnQq7rRz7dD+3JqPvoD6xAO0DWBBWXF1oKulvsU1K3570Zxj1wOVg1P7fhKj8NJ
         j20Q==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:in-reply-to
         :references;
        bh=pyGp7grSiZpObxZrTgZ2GmGoqZvme1lxk38SftFA0lc=;
        b=XS3ScyHGkc9Iexm+R6U1OMUUd8GqvJyyzb9PGu/1XOIXFjOZrq6TMtAn2OoM55H5ys
         +9MT90OPeBenzbtNP5dmk73iLub3Fw6QEW5ewYnkLi32WoE7bXJgjRNXe099VTBOFCrr
         DWG9Z/vo2noxt0cQCwlUUa29KQbsfDuYSN8s5fK7nXFYMyQf7LpYbpyQE6Ax/jBB2IGW
         3Jr476DWsfTW9MUvRSrhWDLM00DSofwf0NkIjiFJwkufGDX4FG3CaZ2t9kcFZyDTZDBN
         l0x8SjLPgHSXFgZL+ut1JyA8WqS73gl0AJK9YTII46XtiTyOM6JQTa2P3g3QcA778H2z
         VdMA==
X-Gm-Message-State: AGi0PuZdp51mWWW9qcg8afCEtMNd2Pi9ASIbR8NZq6Sqbx6VtipvrckU
        Nd6psVRlLinVQv+J/kSL1MMYZneI
X-Google-Smtp-Source: 
 APiQypJqZ0BVbucsAJwdJGRtBft0EMYZR73UQsT9HphY+32jtWyJpChDnKfKU38CrAV0Ime3auGDfA==
X-Received: by 2002:a63:e60a:: with SMTP id g10mr10237869pgh.51.1588055022101;
        Mon, 27 Apr 2020 23:23:42 -0700 (PDT)
Received: from localhost.localdomain ([103.7.29.6])
        by smtp.googlemail.com with ESMTPSA id
 u188sm14183071pfu.33.2020.04.27.23.23.39
        (version=TLS1_2 cipher=ECDHE-ECDSA-AES128-GCM-SHA256 bits=128/128);
        Mon, 27 Apr 2020 23:23:41 -0700 (PDT)
From: Wanpeng Li <kernellwp@gmail.com>
X-Google-Original-From: Wanpeng Li <wanpengli@tencent.com>
To: linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Cc: Paolo Bonzini <pbonzini@redhat.com>,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>,
        Haiwei Li <lihaiwei@tencent.com>
Subject: [PATCH v4 1/7] KVM: VMX: Introduce generic fastpath handler
Date: Tue, 28 Apr 2020 14:23:23 +0800
Message-Id: <1588055009-12677-2-git-send-email-wanpengli@tencent.com>
X-Mailer: git-send-email 2.7.4
In-Reply-To: <1588055009-12677-1-git-send-email-wanpengli@tencent.com>
References: <1588055009-12677-1-git-send-email-wanpengli@tencent.com>
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Wanpeng Li <wanpengli@tencent.com>

Introduce generic fastpath handler to handle MSR fastpath, VMX-preemption
timer fastpath etc, move it after vmx_complete_interrupts() in order that
later patch can catch the case vmexit occurred while another event was
being delivered to guest. There is no obversed performance difference for
IPI fastpath testing after this move.

Tested-by: Haiwei Li <lihaiwei@tencent.com>
Cc: Haiwei Li <lihaiwei@tencent.com>
Signed-off-by: Wanpeng Li <wanpengli@tencent.com>
---
 arch/x86/kvm/vmx/vmx.c | 21 ++++++++++++++++-----
 1 file changed, 16 insertions(+), 5 deletions(-)

```
#### [PATCH] KVM: x86/mmu: Add a helper to consolidate root sp allocation
##### From: Sean Christopherson <sean.j.christopherson@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Sean Christopherson <sean.j.christopherson@intel.com>
X-Patchwork-Id: 11513631
Return-Path: <SRS0=1gOX=6M=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id B6EA092C
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 28 Apr 2020 02:37:20 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id A67EE206D6
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 28 Apr 2020 02:37:20 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726318AbgD1ChR (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 27 Apr 2020 22:37:17 -0400
Received: from mga06.intel.com ([134.134.136.31]:33262 "EHLO mga06.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726263AbgD1ChR (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 27 Apr 2020 22:37:17 -0400
IronPort-SDR: 
 tGAIC0enJoA0wxwuf4kui24US322IphnHaTeNbmpn+D4SwOZt4XDCNUsr6kmL3/6QPzuCF5qo/
 WTg2MfzPTFOQ==
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from fmsmga004.fm.intel.com ([10.253.24.48])
  by orsmga104.jf.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 27 Apr 2020 19:37:16 -0700
IronPort-SDR: 
 MHLSgb9QfWHzePzjt1owK0AshxqFJh558djI8oFxWgEm2rDWlGg9X+DZsSzzQC0bKNUwjk1aNN
 cssbVFYB644w==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.73,326,1583222400";
   d="scan'208";a="281991138"
Received: from sjchrist-coffee.jf.intel.com ([10.54.74.202])
  by fmsmga004.fm.intel.com with ESMTP; 27 Apr 2020 19:37:15 -0700
From: Sean Christopherson <sean.j.christopherson@intel.com>
To: Paolo Bonzini <pbonzini@redhat.com>
Cc: Sean Christopherson <sean.j.christopherson@intel.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org
Subject: [PATCH] KVM: x86/mmu: Add a helper to consolidate root sp allocation
Date: Mon, 27 Apr 2020 19:37:14 -0700
Message-Id: <20200428023714.31923-1-sean.j.christopherson@intel.com>
X-Mailer: git-send-email 2.26.0
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Add a helper, mmu_alloc_root(), to consolidate the allocation of a root
shadow page, which has the same basic mechanics for all flavors of TDP
and shadow paging.

Note, __pa(sp->spt) doesn't need to be protected by mmu_lock, sp->spt
points at a kernel page.

No functional change intended.

Signed-off-by: Sean Christopherson <sean.j.christopherson@intel.com>
---
 arch/x86/kvm/mmu/mmu.c | 88 +++++++++++++++++++-----------------------
 1 file changed, 39 insertions(+), 49 deletions(-)

```
#### [PATCH 1/3] KVM: x86/mmu: Tweak PSE hugepage handling to avoid 2M vs 4M conundrum
##### From: Sean Christopherson <sean.j.christopherson@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Sean Christopherson <sean.j.christopherson@intel.com>
X-Patchwork-Id: 11513537
Return-Path: <SRS0=1gOX=6M=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 3DC8F14DD
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 28 Apr 2020 00:54:33 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 2EBEA2076A
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 28 Apr 2020 00:54:33 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726404AbgD1Ay3 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 27 Apr 2020 20:54:29 -0400
Received: from mga05.intel.com ([192.55.52.43]:42479 "EHLO mga05.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726263AbgD1AyY (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 27 Apr 2020 20:54:24 -0400
IronPort-SDR: 
 oCAsUTRmUMUoMcFnSAKILf8quvrTiuz0fQNeL04Qf3vxggU3hK+RMNNLUrVk4nwCJ8mJDo5uBq
 sJ6asStPOqyg==
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from orsmga006.jf.intel.com ([10.7.209.51])
  by fmsmga105.fm.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 27 Apr 2020 17:54:23 -0700
IronPort-SDR: 
 N1WUVVOvJKgblEUFWbyztygjrYuAyG4M1zEXAKuYoY+LYOYKqHyY+dodY+nMCZV9BI0/ayf61m
 QrPGwJ4ZIp1g==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.73,325,1583222400";
   d="scan'208";a="260920807"
Received: from sjchrist-coffee.jf.intel.com ([10.54.74.202])
  by orsmga006.jf.intel.com with ESMTP; 27 Apr 2020 17:54:23 -0700
From: Sean Christopherson <sean.j.christopherson@intel.com>
To: Paolo Bonzini <pbonzini@redhat.com>
Cc: Sean Christopherson <sean.j.christopherson@intel.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org, Barret Rhoden <brho@google.com>
Subject: [PATCH 1/3] KVM: x86/mmu: Tweak PSE hugepage handling to avoid 2M vs
 4M conundrum
Date: Mon, 27 Apr 2020 17:54:20 -0700
Message-Id: <20200428005422.4235-2-sean.j.christopherson@intel.com>
X-Mailer: git-send-email 2.26.0
In-Reply-To: <20200428005422.4235-1-sean.j.christopherson@intel.com>
References: <20200428005422.4235-1-sean.j.christopherson@intel.com>
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Change the PSE hugepage handling in walk_addr_generic() to fire on any
page level greater than PT_PAGE_TABLE_LEVEL, a.k.a. PG_LEVEL_4K.  PSE
paging only has two levels, so "== 2" and "> 1" are functionally the
seam, i.e. this is a nop.

A future patch will drop KVM's PT_*_LEVEL enums in favor of the kernel's
PG_LEVEL_* enums, at which point "walker->level == PG_LEVEL_2M" is
semantically incorrect (though still functionally ok).

No functional change intended.

Suggested-by: Paolo Bonzini <pbonzini@redhat.com>
Signed-off-by: Sean Christopherson <sean.j.christopherson@intel.com>
---
 arch/x86/kvm/mmu/paging_tmpl.h | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
#### [PATCH] selftests: fix kvm relocatable native/cross builds and installs
##### From: Shuah Khan <skhan@linuxfoundation.org>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Shuah Khan <skhan@linuxfoundation.org>
X-Patchwork-Id: 11513473
Return-Path: <SRS0=1gOX=6M=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 3C5DF15AB
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 28 Apr 2020 00:11:14 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 1F99F2078C
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 28 Apr 2020 00:11:14 +0000 (UTC)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple; d=kernel.org;
	s=default; t=1588032674;
	bh=d2yWWCF78aVlRfdOiEPBd9hlRw4S87mvqWjj204GXBk=;
	h=From:To:Cc:Subject:Date:List-ID:From;
	b=NvUhAae0JJuFZhbqc5Vrs6kQ7sRUtZsTZdnDA63+tL9cDAebKyRtvocuQZ1Cd5g+4
	 Mq/3QXgtnHdmNyetqVMd0mrjnuLKI9ZqnIvQv1NQ+QPusNdsIXJFPZAhCTads9P9qU
	 Y0ENHaLlZrtA5z8RZQcTZ0jQsccWE8OlINxy16+Q=
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726270AbgD1ALN (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 27 Apr 2020 20:11:13 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:40764 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-FAIL-OK-FAIL)
        by vger.kernel.org with ESMTP id S1726386AbgD1ALM (ORCPT
        <rfc822;kvm@vger.kernel.org>); Mon, 27 Apr 2020 20:11:12 -0400
Received: from mail-io1-xd42.google.com (mail-io1-xd42.google.com
 [IPv6:2607:f8b0:4864:20::d42])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id B47DCC0610D5
        for <kvm@vger.kernel.org>; Mon, 27 Apr 2020 17:11:10 -0700 (PDT)
Received: by mail-io1-xd42.google.com with SMTP id u11so21041747iow.4
        for <kvm@vger.kernel.org>; Mon, 27 Apr 2020 17:11:10 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=linuxfoundation.org; s=google;
        h=from:to:cc:subject:date:message-id:mime-version
         :content-transfer-encoding;
        bh=Ip5XKPL15A4yt5XH2ob0YgQ09dtD4HhrbWkXwxt++Q4=;
        b=aO2dI+I3TrK3LiHDpEJ623k8hhROirWFwckfcdAn+yHCE4/y8ssmdcYfeRSVZTC5oW
         LcAYc9jiQkSh+rBVguJuac/L3bT1cx9aINMQABrzO2RX4rhdJihkHSIKBdvHPOrM7xiL
         nCAGtt7P9UdOh2lT/XNWupDaE9O9zUA1hVHGc=
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:mime-version
         :content-transfer-encoding;
        bh=Ip5XKPL15A4yt5XH2ob0YgQ09dtD4HhrbWkXwxt++Q4=;
        b=PjxEFhynWC/3vo0nRRnFMEEjHbbHiFkvhI6/LY7wxIvsw5rKoMd2dTLnLusfnkUWiq
         W3YqZtiz4klpqK9d49nHEf1c1zslisToucSJF6ND7J+xXMWusyqW9PiMBd9mpzG4eEDz
         pZCqiFfhi8Ezr/7nwf9j3gukg4s3Rl7xt+5pfcwQe8I9tIIb2CG/CcdznUUuIaKBUgp5
         oU1vJ1ypEPvi4EIANagkhqL9EbnIbz1XqaA5NUBPLvq1Nodltwk20kIqNqqO+3wl3cqD
         Zqg0iu0fJ0zz8fMP0Hdaa7SmTWfunhp0MhL5yJsOtXaeycfEmAPORg6l7Q9jIhn+PuvS
         i26g==
X-Gm-Message-State: AGi0PubYMK8i/a6oK46rWk8LANVJT4Of4n7xjeUqfQMde4k0ZxfwVvZm
        mJM5nSegj7hN/FQRIOu6W+SWU+/glpw=
X-Google-Smtp-Source: 
 APiQypJwOikjE0kbIVE5N7lK5n4r9xPWCPkC2mlLixbg80Xq950I2YDQgew6ClksYpcG0RUuZYsMKA==
X-Received: by 2002:a02:cbc6:: with SMTP id u6mr23777221jaq.27.1588032670022;
        Mon, 27 Apr 2020 17:11:10 -0700 (PDT)
Received: from shuah-t480s.internal (c-24-9-64-241.hsd1.co.comcast.net.
 [24.9.64.241])
        by smtp.gmail.com with ESMTPSA id
 140sm6028419ilc.44.2020.04.27.17.11.09
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Mon, 27 Apr 2020 17:11:09 -0700 (PDT)
From: Shuah Khan <skhan@linuxfoundation.org>
To: pbonzini@redhat.com, shuah@kernel.org
Cc: Shuah Khan <skhan@linuxfoundation.org>, kvm@vger.kernel.org,
        linux-kselftest@vger.kernel.org, linux-kernel@vger.kernel.org
Subject: [PATCH] selftests: fix kvm relocatable native/cross builds and
 installs
Date: Mon, 27 Apr 2020 18:11:07 -0600
Message-Id: <20200428001107.11281-1-skhan@linuxfoundation.org>
X-Mailer: git-send-email 2.20.1
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

kvm test Makefile doesn't fully support cross-builds and installs.
UNAME_M = $(shell uname -m) variable is used to define the target
programs and libraries to be built from arch specific sources in
sub-directories.

For cross-builds to work, UNAME_M has to map to ARCH and arch specific
directories and targets in this Makefile.

UNAME_M variable to used to run the compiles pointing to the right arch
directories and build the right targets for these supported architectures.

TEST_GEN_PROGS and LIBKVM are set using UNAME_M variable.
LINUX_TOOL_ARCH_INCLUDE is set using ARCH variable.

x86_64 targets are named to include x86_64 as a suffix and directories
for includes are in x86_64 sub-directory. s390x and aarch64 follow the
same convention. "uname -m" doesn't result in the correct mapping for
s390x and aarch64. Fix it to set UNAME_M correctly for s390x and aarch64
cross-builds.

In addition, Makefile doesn't create arch sub-directories in the case of
relocatable builds and test programs under s390x and x86_64 directories
fail to build. This is a problem for native and cross-builds. Fix it to
create all necessary directories keying off of TEST_GEN_PROGS.

The following use-cases work with this change:

Native x86_64:
make O=/tmp/kselftest -C tools/testing/selftests TARGETS=kvm install \
 INSTALL_PATH=$HOME/x86_64

arm64 cross-build:
make O=$HOME/arm64_build/ ARCH=arm64 HOSTCC=gcc \
	CROSS_COMPILE=aarch64-linux-gnu- defconfig

make O=$HOME/arm64_build/ ARCH=arm64 HOSTCC=gcc \
	CROSS_COMPILE=aarch64-linux-gnu- all

make kselftest-install TARGETS=kvm O=$HOME/arm64_build ARCH=arm64 \
	HOSTCC=gcc CROSS_COMPILE=aarch64-linux-gnu-

s390x cross-build:
make O=$HOME/s390x_build/ ARCH=s390 HOSTCC=gcc \
	CROSS_COMPILE=s390x-linux-gnu- defconfig

make O=$HOME/s390x_build/ ARCH=s390 HOSTCC=gcc \
	CROSS_COMPILE=s390x-linux-gnu- all

make kselftest-install TARGETS=kvm O=$HOME/s390x_build/ ARCH=s390 \
	HOSTCC=gcc CROSS_COMPILE=s390x-linux-gnu- all

No regressions in the following use-cases:
make -C tools/testing/selftests TARGETS=kvm
make kselftest-all TARGETS=kvm

Signed-off-by: Shuah Khan <skhan@linuxfoundation.org>
---
 tools/testing/selftests/kvm/Makefile | 29 +++++++++++++++++++++++++++-
 1 file changed, 28 insertions(+), 1 deletion(-)

```
#### [PATCH v2] KVM: nVMX: Tweak handling of failure code for nested VM-Enter failure
##### From: Sean Christopherson <sean.j.christopherson@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Sean Christopherson <sean.j.christopherson@intel.com>
X-Patchwork-Id: 11515285
Return-Path: <SRS0=1gOX=6M=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id F21F992C
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 28 Apr 2020 17:32:23 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id DEE95208FE
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 28 Apr 2020 17:32:23 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728467AbgD1RcU (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 28 Apr 2020 13:32:20 -0400
Received: from mga05.intel.com ([192.55.52.43]:37304 "EHLO mga05.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1728338AbgD1RcU (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 28 Apr 2020 13:32:20 -0400
IronPort-SDR: 
 UamUCxB0+EFyyaxsTLpdyWg4sUdXUyvoueFY8zZXZcxM8LxisX1INKJcYygcliBmzBFycrLTix
 1BRzkuT9zTfQ==
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from fmsmga001.fm.intel.com ([10.253.24.23])
  by fmsmga105.fm.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 28 Apr 2020 10:32:18 -0700
IronPort-SDR: 
 jE8KfGcEeN4UK0e3sfby955MkfVnxiUalJSBy/I/B0c5q9/tGAv00j4AOMrW7/j6hfr5L0duTg
 MjbRj71xLJTg==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.73,328,1583222400";
   d="scan'208";a="367565028"
Received: from sjchrist-coffee.jf.intel.com ([10.54.74.202])
  by fmsmga001.fm.intel.com with ESMTP; 28 Apr 2020 10:32:18 -0700
From: Sean Christopherson <sean.j.christopherson@intel.com>
To: Paolo Bonzini <pbonzini@redhat.com>
Cc: Sean Christopherson <sean.j.christopherson@intel.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org
Subject: [PATCH v2] KVM: nVMX: Tweak handling of failure code for nested
 VM-Enter failure
Date: Tue, 28 Apr 2020 10:32:17 -0700
Message-Id: <20200428173217.5430-1-sean.j.christopherson@intel.com>
X-Mailer: git-send-email 2.26.0
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Use an enum for passing around the failure code for a failed VM-Enter
that results in VM-Exit to provide a level of indirection from the final
resting place of the failure code, vmcs.EXIT_QUALIFICATION.  The exit
qualification field is an unsigned long, e.g. passing around
'u32 exit_qual' throws up red flags as it suggests KVM may be dropping
bits when reporting errors to L1.  This is a red herring because the
only defined failure codes are 0, 2, 3, and 4, i.e. don't come remotely
close to overflowing a u32.

Setting vmcs.EXIT_QUALIFICATION on entry failure is further complicated
by the MSR load list, which returns the (1-based) entry that failed, and
the number of MSRs to load is a 32-bit VMCS field.  At first blush, it
would appear that overflowing a u32 is possible, but the number of MSRs
that can be loaded is hardcapped at 4096 (limited by MSR_IA32_VMX_MISC).

In other words, there are two completely disparate types of data that
eventually get stuffed into vmcs.EXIT_QUALIFICATION, neither of which is
an 'unsigned long' in nature.  This was presumably the reasoning for
switching to 'u32' when the related code was refactored in commit
ca0bde28f2ed6 ("kvm: nVMX: Split VMCS checks from nested_vmx_run()").

Using an enum for the failure code addresses the technically-possible-
but-will-never-happen scenario where Intel defines a failure code that
doesn't fit in a 32-bit integer.  The enum variables and values will
either be automatically sized (gcc 5.4 behavior) or be subjected to some
combination of truncation.  The former case will simply work, while the
latter will trigger a compile-time warning unless the compiler is being
particularly unhelpful.

Separating the failure code from the failed MSR entry allows for
disassociating both from vmcs.EXIT_QUALIFICATION, which avoids the
conundrum where KVM has to choose between 'u32 exit_qual' and tracking
values as 'unsigned long' that have no business being tracked as such.
To cement the split, set vmcs12->exit_qualification directly from the
entry error code or failed MSR index instead of bouncing through a local
variable.

Opportunistically rename the variables in load_vmcs12_host_state() and
vmx_set_nested_state() to call out that they're ignored, set exit_reason
on demand on nested VM-Enter failure, and add a comment in
nested_vmx_load_msr() to call out that returning 'i + 1' can't wrap.

No functional change intended.

Reported-by: Vitaly Kuznetsov <vkuznets@redhat.com>
Cc: Jim Mattson <jmattson@google.com>
Signed-off-by: Sean Christopherson <sean.j.christopherson@intel.com>
Reviewed-by: Jim Mattson <jmattson@google.com>
---

v2:
  - Set vmcs12->exit_qualification directly to avoid writing the failed
    MSR index (a u32) to the entry_failure_code enum. [Jim]
  - Set exit_reason on demand since the "goto vm_exit" paths need to set
    vmcs12->exit_qualification anyways, i.e. already have curly braces.

 arch/x86/include/asm/vmx.h | 10 +++++----
 arch/x86/kvm/vmx/nested.c  | 44 ++++++++++++++++++++++----------------
 2 files changed, 31 insertions(+), 23 deletions(-)

```
#### [PATCH v3 01/75] KVM: SVM: Add GHCB definitions
##### From: Joerg Roedel <joro@8bytes.org>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Joerg Roedel <joro@8bytes.org>
X-Patchwork-Id: 11514993
Return-Path: <SRS0=1gOX=6M=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 90E981575
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 28 Apr 2020 15:24:54 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 79161206E2
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 28 Apr 2020 15:24:54 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728055AbgD1PRr (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 28 Apr 2020 11:17:47 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:41588 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-FAIL-OK-FAIL)
        by vger.kernel.org with ESMTP id S1728028AbgD1PRq (ORCPT
        <rfc822;kvm@vger.kernel.org>); Tue, 28 Apr 2020 11:17:46 -0400
Received: from theia.8bytes.org (8bytes.org
 [IPv6:2a01:238:4383:600:38bc:a715:4b6d:a889])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 2C031C03C1AB;
        Tue, 28 Apr 2020 08:17:46 -0700 (PDT)
Received: by theia.8bytes.org (Postfix, from userid 1000)
        id 756F16BB; Tue, 28 Apr 2020 17:17:42 +0200 (CEST)
From: Joerg Roedel <joro@8bytes.org>
To: x86@kernel.org
Cc: hpa@zytor.com, Andy Lutomirski <luto@kernel.org>,
        Dave Hansen <dave.hansen@linux.intel.com>,
        Peter Zijlstra <peterz@infradead.org>,
        Thomas Hellstrom <thellstrom@vmware.com>,
        Jiri Slaby <jslaby@suse.cz>,
        Dan Williams <dan.j.williams@intel.com>,
        Tom Lendacky <thomas.lendacky@amd.com>,
        Juergen Gross <jgross@suse.com>,
        Kees Cook <keescook@chromium.org>,
        David Rientjes <rientjes@google.com>,
        Cfir Cohen <cfir@google.com>,
        Erdem Aktas <erdemaktas@google.com>,
        Masami Hiramatsu <mhiramat@kernel.org>,
        Mike Stunes <mstunes@vmware.com>,
        Joerg Roedel <joro@8bytes.org>, Joerg Roedel <jroedel@suse.de>,
        linux-kernel@vger.kernel.org, kvm@vger.kernel.org,
        virtualization@lists.linux-foundation.org
Subject: [PATCH v3 01/75] KVM: SVM: Add GHCB definitions
Date: Tue, 28 Apr 2020 17:16:11 +0200
Message-Id: <20200428151725.31091-2-joro@8bytes.org>
X-Mailer: git-send-email 2.17.1
In-Reply-To: <20200428151725.31091-1-joro@8bytes.org>
References: <20200428151725.31091-1-joro@8bytes.org>
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Tom Lendacky <thomas.lendacky@amd.com>

Extend the vmcb_safe_area with SEV-ES fields and add a new
'struct ghcb' which will be used for guest-hypervisor communication.

Signed-off-by: Tom Lendacky <thomas.lendacky@amd.com>
Signed-off-by: Joerg Roedel <jroedel@suse.de>
---
 arch/x86/include/asm/svm.h | 42 ++++++++++++++++++++++++++++++++++++++
 1 file changed, 42 insertions(+)

```
