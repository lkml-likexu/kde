#### [PATCH 1/3] accel: Only include TCG stubs in user-mode only builds
##### From: =?utf-8?q?Philippe_Mathieu-Daud=C3=A9?= <f4bug@amsat.org>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 8bit
X-Patchwork-Submitter: =?utf-8?q?Philippe_Mathieu-Daud=C3=A9?=
 <f4bug@amsat.org>
X-Patchwork-Id: 11890807
Return-Path: <SRS0=zqVv=EP=vger.kernel.org=kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-12.8 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_PATCH,MAILING_LIST_MULTI,
	SIGNED_OFF_BY,SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED,USER_AGENT_GIT
	autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id D7CF0C56201
	for <kvm@archiver.kernel.org>; Mon,  9 Nov 2020 09:45:58 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 8C88A207BC
	for <kvm@archiver.kernel.org>; Mon,  9 Nov 2020 09:45:58 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=gmail.com header.i=@gmail.com
 header.b="lfFJ0JNb"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729008AbgKIJp5 (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Mon, 9 Nov 2020 04:45:57 -0500
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:46730 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1728866AbgKIJp5 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 9 Nov 2020 04:45:57 -0500
Received: from mail-wr1-x443.google.com (mail-wr1-x443.google.com
 [IPv6:2a00:1450:4864:20::443])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id C9C96C0613CF
        for <kvm@vger.kernel.org>; Mon,  9 Nov 2020 01:45:55 -0800 (PST)
Received: by mail-wr1-x443.google.com with SMTP id p1so7918411wrf.12
        for <kvm@vger.kernel.org>; Mon, 09 Nov 2020 01:45:55 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=sender:from:to:cc:subject:date:message-id:in-reply-to:references
         :mime-version:content-transfer-encoding;
        bh=1o8lO3koG16AlBbmrKd/snSNhrR/M4yhMjnc+WbIftA=;
        b=lfFJ0JNb2rBiiklBvMRWfCR2xuij+pgMCgqsLCy81HP4dnZsGa9ab/tral6KSdVN/S
         b4DSOQga0Gi+UYhfqO328qbmbgMW+VMAqCGR4HrGkoy2LrW1g6x80sYavGnSv1s98F5v
         XumyaGK5Or9PB2BeK7vAxuNBbdg1E3V2cPYRJ40N7a7NeO4KY70hCSOoP1Uy4dCvDKWA
         RqBJfzxMsqqYdwpfdzrM+vVZk8hugomSvGJeExtnJemU135/1Bsnwnhi1ipEEk0qTuVT
         rRrW9PLQOu7nPQq052VIQSaJT5fJF4/YsBg78TsY0MfddTYxudPiqIVcZgwELwdU5ejr
         4nwQ==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:sender:from:to:cc:subject:date:message-id
         :in-reply-to:references:mime-version:content-transfer-encoding;
        bh=1o8lO3koG16AlBbmrKd/snSNhrR/M4yhMjnc+WbIftA=;
        b=OtyJmlU8Qo1NP+gWAKEucyDgKAgftNUzxBPCYBetpuUlBFgK/bvHFlvGQ3iqkOmwji
         SeSdokeG6KiNWLhtvINA+0Ju1vddbInR9twdb8cEG90YMF0oWIRwCMK51q7qUgQMDiDi
         U41JG0hlY3J4TW2C6Uh5/r5yxefTCQp3EAjt1Et1I1vDs39P358kwyrqSIyhkCVZTdIM
         jsm2yXEyrJER2XRy7KQs1ap4dtHdWdymuWnz+DG0CBl8pOm0S5wGuXl+yQ98PmNICjY0
         nE1uytQ1idAEpReNAiEZ3zuTlbcfmMgbg3MycGC2PugWgIzCAy9iXMNMdAIrpj4MNBwt
         LedQ==
X-Gm-Message-State: AOAM530kblgysvjgrKf2vgFmPfNBkZZtDJACvz0labTSEFr8m3J4SDe/
        GK81xLp/2DD5/XpjdnzvhRU=
X-Google-Smtp-Source: 
 ABdhPJxc4TZdtgyhqebFbBYMGgeJ98UQ+2SDOy/fHp3mL6Ipg+mK+zm9sk7kmSq1DbuRl+juTBkF8g==
X-Received: by 2002:adf:e64e:: with SMTP id b14mr16979874wrn.68.1604915154540;
        Mon, 09 Nov 2020 01:45:54 -0800 (PST)
Received: from localhost.localdomain (234.red-83-42-66.dynamicip.rima-tde.net.
 [83.42.66.234])
        by smtp.gmail.com with ESMTPSA id
 z191sm12223304wme.30.2020.11.09.01.45.53
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Mon, 09 Nov 2020 01:45:53 -0800 (PST)
Sender: =?utf-8?q?Philippe_Mathieu-Daud=C3=A9?=
  <philippe.mathieu.daude@gmail.com>
From: =?utf-8?q?Philippe_Mathieu-Daud=C3=A9?= <f4bug@amsat.org>
To: qemu-devel@nongnu.org
Cc: Paolo Bonzini <pbonzini@redhat.com>, Laurent Vivier <laurent@vivier.eu>,
 kvm@vger.kernel.org,
 =?utf-8?q?Philippe_Mathieu-Daud=C3=A9?= <f4bug@amsat.org>
Subject: [PATCH 1/3] accel: Only include TCG stubs in user-mode only builds
Date: Mon,  9 Nov 2020 10:45:45 +0100
Message-Id: <20201109094547.2456385-2-f4bug@amsat.org>
X-Mailer: git-send-email 2.26.2
In-Reply-To: <20201109094547.2456385-1-f4bug@amsat.org>
References: <20201109094547.2456385-1-f4bug@amsat.org>
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

We only require TCG stubs in user-mode emulation.
Do not build stubs restricted to system-mode emulation
in a user-mode only build.

Signed-off-by: Philippe Mathieu-Daudé <f4bug@amsat.org>
---
 accel/meson.build | 10 ++++++----
 1 file changed, 6 insertions(+), 4 deletions(-)

```
#### [PATCH v15 05/17] RISC-V: KVM: Implement KVM_GET_ONE_REG/KVM_SET_ONE_REG ioctls
##### From: Anup Patel <anup.patel@wdc.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Anup Patel <Anup.Patel@wdc.com>
X-Patchwork-Id: 11891213
Return-Path: <SRS0=zqVv=EP=vger.kernel.org=kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-12.7 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_PATCH,MAILING_LIST_MULTI,
	MSGID_FROM_MTA_HEADER,SIGNED_OFF_BY,SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED,
	USER_AGENT_GIT autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id A7B79C2D0A3
	for <kvm@archiver.kernel.org>; Mon,  9 Nov 2020 11:34:09 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 29340206ED
	for <kvm@archiver.kernel.org>; Mon,  9 Nov 2020 11:34:09 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=fail reason="signature verification failed" (2048-bit key)
 header.d=wdc.com header.i=@wdc.com header.b="CDn6TKrq";
	dkim=pass (1024-bit key) header.d=sharedspace.onmicrosoft.com
 header.i=@sharedspace.onmicrosoft.com header.b="mngBEc7/"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729958AbgKILeH (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Mon, 9 Nov 2020 06:34:07 -0500
Received: from esa5.hgst.iphmx.com ([216.71.153.144]:19249 "EHLO
        esa5.hgst.iphmx.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1729506AbgKILeA (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 9 Nov 2020 06:34:00 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=simple/simple;
  d=wdc.com; i=@wdc.com; q=dns/txt; s=dkim.wdc.com;
  t=1604921639; x=1636457639;
  h=from:to:cc:subject:date:message-id:in-reply-to:
   references:content-transfer-encoding:mime-version;
  bh=FncAVryU/X1o20r0vZwUwJRglWAImrSDWppEwgMxLbw=;
  b=CDn6TKrqbVB/mG9zJsLTzzkMQocEFhes9BhyeedUGQXb4khN/ytWUkYi
   s+sw2WpImt/87IcXbTJK3CVnbbk60DirAHd44veB8nldGkgSUNyU/tpQa
   Cv3VujHCubFdwatRXLZQn+s/5X/ODz0KRKMWnN+ESqItb2c5x46pt8WFL
   RShOAq6eG5eqm9Bj6V7oWHBkJ0u4tjUtysqdftYDzRp9/bG3Y04AO4OQf
   ZoYGLhi35auriclZ6FmsXirCT2ce6z1VQuyan613KMElTo7rAHLFD9zh2
   M2OH9M+60c48JiZLHsxa9Xei83yJIPWob/vXdFdve4K231knTbI9BjDwx
   A==;
IronPort-SDR: 
 ojLL2ipCLacXF0fzSAbz1/2BG/prSpKqUtQS0ciB+1t9UcqBgJZlRT0n5/eKCa2+llgaDcVC0u
 zpU2YynCGx5u6lau9Yi3/OfdRqqic6t3U6qwJuXYI1GzEU929SDvCWWD7yKcnrzG3rn0Vqq8Nl
 THBUyHdwjXGYLBGp/LVb4N8PGeFtE0hoBAyMjHMhrF+bzxyugjknZaHb4uBC+x6+mjnyt8J6PU
 5kaD5o9omTxXqwHu2KWL9inqvYb6mijrctCPieQG5er752zy4lpBk2FUoM9dHcUb0qs55h6woa
 cYo=
X-IronPort-AV: E=Sophos;i="5.77,463,1596470400";
   d="scan'208";a="152286360"
Received: from mail-bn8nam11lp2168.outbound.protection.outlook.com (HELO
 NAM11-BN8-obe.outbound.protection.outlook.com) ([104.47.58.168])
  by ob1.hgst.iphmx.com with ESMTP; 09 Nov 2020 19:33:57 +0800
ARC-Seal: i=1; a=rsa-sha256; s=arcselector9901; d=microsoft.com; cv=none;
 b=OSQhRYjTfnoCjqScJEi8JSZTaWcohslmYWbdXsN4rUIltbP9HjyaTei9r1d8APp35+RsgEiL6G/v2i7Um5dFNFvE46frs+7a6H5/fl3v5yZa3GlnyNG4EJZ4qCi6LQKKfXrbiPy0fMoqOhnpt2TspQ3kxIkfSif5pwLHwyN5Nnog6tF/1UPau0HTFyVIMsiPuSD2XSZNo9y+mzHL7dnE5HWQAgteWW/2xBmTX/dtSX3GNn6pulMLeXBoC+qhuOUsc2Nn1pOpzMHAqCF1U4pcBsdasldrDBXVwanlxqe71XIjUR502CUQjSMRWkJiy5aIVBQgLf7hrOncxxfrxq+3BQ==
ARC-Message-Signature: i=1; a=rsa-sha256; c=relaxed/relaxed; d=microsoft.com;
 s=arcselector9901;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=U6LMW+fHg5VBUnqkV8Ik1nLvno9fSpvyyG6lGVDAUu8=;
 b=kQbaeqjaLLCH+cpM4jsmaH3sDK1EurYU4lE/UhWfTsDJ+wWAv32n3XgprKytbQispjZgsak1lvVcyTZMhyrePdL4+W+9pd/yJK/X4RXCX44u0SWgPpXNpgCXvPx+kmGdHME1MdxYKTfnAaZi3VLvdy5hrTe52wq0l2sUoKAh+1ERGOmDv/8vS4Rc70HWIhnISwkKGtdUvAeeMX7EDh0i+qSE/f0a04X8Hb58oD6heHqsm/peR8zb/MsU5MWhwKHLAX2nLSrzlNg5q5IvXzlSeNFu77CDGF/B+tO8Fq+baM3Wbu6gLL4WxP/AonwCnHo07jR1PX4UyAXUwlE886cFNQ==
ARC-Authentication-Results: i=1; mx.microsoft.com 1; spf=pass
 smtp.mailfrom=wdc.com; dmarc=pass action=none header.from=wdc.com; dkim=pass
 header.d=wdc.com; arc=none
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
 d=sharedspace.onmicrosoft.com; s=selector2-sharedspace-onmicrosoft-com;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=U6LMW+fHg5VBUnqkV8Ik1nLvno9fSpvyyG6lGVDAUu8=;
 b=mngBEc7/F1q9t2lZa29pT1Wy8HvZdcYKD36qhQC0ngUz1p9q1gqwSx5AWsFG7iNz808EMXJTjDLSQv2T8sjL1H/crTOo4Mtij7l2E1CZzUL13FgwOFleZH/N/1yv/vYLwbSSmbHK9QNhk7o1V7+DG4k8iuR+r76UsH/yQmy0v0s=
Authentication-Results: dabbelt.com; dkim=none (message not signed)
 header.d=none;dabbelt.com; dmarc=none action=none header.from=wdc.com;
Received: from DM6PR04MB6201.namprd04.prod.outlook.com (2603:10b6:5:127::32)
 by DM6PR04MB3866.namprd04.prod.outlook.com (2603:10b6:5:ad::19) with
 Microsoft SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.3541.21; Mon, 9 Nov
 2020 11:33:56 +0000
Received: from DM6PR04MB6201.namprd04.prod.outlook.com
 ([fe80::d035:e2c6:c11:51dd]) by DM6PR04MB6201.namprd04.prod.outlook.com
 ([fe80::d035:e2c6:c11:51dd%6]) with mapi id 15.20.3541.025; Mon, 9 Nov 2020
 11:33:56 +0000
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
Subject: [PATCH v15 05/17] RISC-V: KVM: Implement
 KVM_GET_ONE_REG/KVM_SET_ONE_REG ioctls
Date: Mon,  9 Nov 2020 17:02:28 +0530
Message-Id: <20201109113240.3733496-6-anup.patel@wdc.com>
X-Mailer: git-send-email 2.25.1
In-Reply-To: <20201109113240.3733496-1-anup.patel@wdc.com>
References: <20201109113240.3733496-1-anup.patel@wdc.com>
X-Originating-IP: [122.171.188.68]
X-ClientProxiedBy: MAXPR01CA0099.INDPRD01.PROD.OUTLOOK.COM
 (2603:1096:a00:5d::17) To DM6PR04MB6201.namprd04.prod.outlook.com
 (2603:10b6:5:127::32)
MIME-Version: 1.0
X-MS-Exchange-MessageSentRepresentingType: 1
Received: from wdc.com (122.171.188.68) by
 MAXPR01CA0099.INDPRD01.PROD.OUTLOOK.COM (2603:1096:a00:5d::17) with Microsoft
 SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.3541.21 via Frontend
 Transport; Mon, 9 Nov 2020 11:33:52 +0000
X-MS-PublicTrafficType: Email
X-MS-Office365-Filtering-HT: Tenant
X-MS-Office365-Filtering-Correlation-Id: b5f1d5f6-c6a0-4fc3-3a51-08d884a35822
X-MS-TrafficTypeDiagnostic: DM6PR04MB3866:
X-MS-Exchange-Transport-Forked: True
X-Microsoft-Antispam-PRVS: 
 <DM6PR04MB38660B9D15D188216C72C16A8DEA0@DM6PR04MB3866.namprd04.prod.outlook.com>
WDCIPOUTBOUND: EOP-TRUE
X-MS-Oob-TLC-OOBClassifiers: OLM:7219;
X-MS-Exchange-SenderADCheck: 1
X-Microsoft-Antispam: BCL:0;
X-Microsoft-Antispam-Message-Info: 
 gVw7lXBuncMBAp17bGoGdpAJr34ovJeQmQzhInfpALel4sF/42lbgm2k6e1RQb5p46Cxw1ip3XaJ7PqcpXmrFdcNv+Tvc6HcsbUtchPqghpyH+S/1Ef5ZT7K455CDWErUW3EUNWKHno0KxYgKiQHHRWXLy+UxX2kkE0dZYL4R36GbGimHRt/gEjz9iy83Jor4KHvxlDyIER3kN28OOQm3z8pWgw1VCeic+p4prN1vGl0ygZA2S+BwZWGdJGavOcnd7bS/iwxlDjZtbUlqCZUTRMcEwknd5R81Ejz8gCuAuW6eqjgrcRfUOToujtg0vAX
X-Forefront-Antispam-Report: 
 CIP:255.255.255.255;CTRY:;LANG:en;SCL:1;SRV:;IPV:NLI;SFV:NSPM;H:DM6PR04MB6201.namprd04.prod.outlook.com;PTR:;CAT:NONE;SFS:(4636009)(366004)(346002)(396003)(136003)(39860400002)(376002)(55016002)(7416002)(83380400001)(1076003)(44832011)(16526019)(186003)(316002)(26005)(8676002)(110136005)(54906003)(5660300002)(52116002)(7696005)(956004)(30864003)(2616005)(478600001)(66476007)(66556008)(4326008)(66946007)(6666004)(2906002)(36756003)(86362001)(8886007)(8936002);DIR:OUT;SFP:1102;
X-MS-Exchange-AntiSpam-MessageData: 
 tu6A1poedo8gAExcDWcrGr0SJ4xPSfyPE+goKp6X35/b3fsRnBXvJxffCJ7LTDHPg/PrzviI65S9Tnw/7tBt+Ik/Fqxmqz6QMGdN1S5zlzFLAh3d/bpxkudLTZts31Q7G5gYfmdL9QcOIWHSgVKKipFSJH+2QzZztZWGuxelkR1QPYTNKrm3rpiMtWYu0Qncb26pwxqbHA16rH6bMK+OxpTRopAszm8gbEC+qjE8+7nPb9MNbx1+rtxG8fHzOuc/VnAUXwf25bhKO6dPTxsx34GL43amTdyJ54E3dAhFqDjmVACWn6/gTeW4a+UejXan2Obd1as3PQGH6QK+o/1DgsEZvp7UKipRxOf3uEuyBnwtqEIbR+px2MmXABoEaL/Dd1NNC1H6wneJ6zQbtLMcTSHOVCaBy/0g7e+KpIpEl2NNz8mMxntGWNv6giKSy0rcGddf69Tzsyqc6FEzvkEhymn8MWwOI5ftR8or95aZg7CYdDJRO7pgeQjHyDw83K2UdInt09iLqrd8E3IOUYfNru+MGEfkGuniFRYdGz6YDiq/0cx7Xp2TmGz8vuEL+RxCP1XRFetG5JqeWhEdnZQAF9iaxZREcAwMWDwGRIo3lnUbACM6D34T7mXSAmxOwi/nLwpIdSm0ZCCYnRvbIRMZ8w==
X-OriginatorOrg: wdc.com
X-MS-Exchange-CrossTenant-Network-Message-Id: 
 b5f1d5f6-c6a0-4fc3-3a51-08d884a35822
X-MS-Exchange-CrossTenant-AuthSource: DM6PR04MB6201.namprd04.prod.outlook.com
X-MS-Exchange-CrossTenant-AuthAs: Internal
X-MS-Exchange-CrossTenant-OriginalArrivalTime: 09 Nov 2020 11:33:56.7937
 (UTC)
X-MS-Exchange-CrossTenant-FromEntityHeader: Hosted
X-MS-Exchange-CrossTenant-Id: b61c8803-16f3-4c35-9b17-6f65f441df86
X-MS-Exchange-CrossTenant-MailboxType: HOSTED
X-MS-Exchange-CrossTenant-UserPrincipalName: 
 DR6om+0hzcEUVliCWpYVPQ0ebLKQCA4ER00R3lNZzqsuuObpemL228w0sLSWa69vS2sxUcvjYl9/mpEVNizdJw==
X-MS-Exchange-Transport-CrossTenantHeadersStamped: DM6PR04MB3866
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

For KVM RISC-V, we use KVM_GET_ONE_REG/KVM_SET_ONE_REG ioctls to access
VCPU config and registers from user-space.

We have three types of VCPU registers:
1. CONFIG - these are VCPU config and capabilities
2. CORE   - these are VCPU general purpose registers
3. CSR    - these are VCPU control and status registers

The CONFIG register available to user-space is ISA. The ISA register is
a read and write register where user-space can only write the desired
VCPU ISA capabilities before running the VCPU.

The CORE registers available to user-space are PC, RA, SP, GP, TP, A0-A7,
T0-T6, S0-S11 and MODE. Most of these are RISC-V general registers except
PC and MODE. The PC register represents program counter whereas the MODE
register represent VCPU privilege mode (i.e. S/U-mode).

The CSRs available to user-space are SSTATUS, SIE, STVEC, SSCRATCH, SEPC,
SCAUSE, STVAL, SIP, and SATP. All of these are read/write registers.

In future, more VCPU register types will be added (such as FP) for the
KVM_GET_ONE_REG/KVM_SET_ONE_REG ioctls.

Signed-off-by: Anup Patel <anup.patel@wdc.com>
Acked-by: Paolo Bonzini <pbonzini@redhat.com>
Reviewed-by: Paolo Bonzini <pbonzini@redhat.com>
---
 arch/riscv/include/uapi/asm/kvm.h |  53 ++++++-
 arch/riscv/kvm/vcpu.c             | 246 +++++++++++++++++++++++++++++-
 2 files changed, 295 insertions(+), 4 deletions(-)

```
#### [RFC PATCH v5 7/8] riscv: Handle SBI calls forwarded to user space
##### From: Anup Patel <anup.patel@wdc.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Anup Patel <Anup.Patel@wdc.com>
X-Patchwork-Id: 11891275
Return-Path: <SRS0=zqVv=EP=vger.kernel.org=kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-12.7 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_PATCH,MAILING_LIST_MULTI,
	MSGID_FROM_MTA_HEADER,SIGNED_OFF_BY,SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED,
	USER_AGENT_GIT autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 609E2C2D0A3
	for <kvm@archiver.kernel.org>; Mon,  9 Nov 2020 11:38:02 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 03D3D20731
	for <kvm@archiver.kernel.org>; Mon,  9 Nov 2020 11:38:01 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=fail reason="signature verification failed" (2048-bit key)
 header.d=wdc.com header.i=@wdc.com header.b="DO78LhUk";
	dkim=pass (1024-bit key) header.d=sharedspace.onmicrosoft.com
 header.i=@sharedspace.onmicrosoft.com header.b="GzVWvlLc"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729961AbgKILiB (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Mon, 9 Nov 2020 06:38:01 -0500
Received: from esa6.hgst.iphmx.com ([216.71.154.45]:28190 "EHLO
        esa6.hgst.iphmx.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1729658AbgKILiA (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 9 Nov 2020 06:38:00 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=simple/simple;
  d=wdc.com; i=@wdc.com; q=dns/txt; s=dkim.wdc.com;
  t=1604921880; x=1636457880;
  h=from:to:cc:subject:date:message-id:in-reply-to:
   references:content-transfer-encoding:mime-version;
  bh=lDq+FKo7RmMLlDr7OA4J8sRiNlAUgKGsONyvb6DEe/M=;
  b=DO78LhUkjh8jIAzJGWQENNk8pXX7JYaiPTtKWi0dxcKVDPtmRZJ9oU6M
   aZnW41bZmUzfaokPVFB/UlwDeM2h651MwQGgl9XTfN8IpN/p+ujM8bUii
   0s+eRiUKwfGV9iDCCdzjgMMscjaLuI8ogTB+fjZE1/zNDsZJQEwDen3fS
   KaD3hINPsWIeqJXMUpLP463WC0t3zQJA+wMGJTUxOFWIs9wecuFFidl9K
   tF+ytWbjr5ej06T0zrg1KSAMchY2KWEDcfZOPuYQuGyaXGOPjccxIUXVO
   QR+F+iWWPncQH/wZVdW0aE7JegIdPOSMb5hRAt9NXn1BpfbnPgK+sYSt/
   g==;
IronPort-SDR: 
 12ylTgOEkeexxzE02yus3jRJ2c+XmpcGdIhr4OZmDWaznOZrwRCJFJvBs19bmH61xNiy6vMvxy
 NiFwOlQgknWeoFvmpR01/HpjRfgpVk+vFNTVtwrh0gyF4PI7lWOUdajZEN/+ZJSLNm30c1M9f1
 ebE5bSN+9cC8KjwLBq0IF4r1mcjPamlIBJ17CXTVrs1E56W6fiIeywM138p6pZnYPmgZWoL6Rr
 /xC65815lI37g68KsdEo3Ln6rECJP8LOLamhSLsa0N26ws8XiYSYLhglkOnRqsiWAaQttKipJ+
 q1A=
X-IronPort-AV: E=Sophos;i="5.77,463,1596470400";
   d="scan'208";a="153383071"
Received: from mail-dm6nam10lp2106.outbound.protection.outlook.com (HELO
 NAM10-DM6-obe.outbound.protection.outlook.com) ([104.47.58.106])
  by ob1.hgst.iphmx.com with ESMTP; 09 Nov 2020 19:37:59 +0800
ARC-Seal: i=1; a=rsa-sha256; s=arcselector9901; d=microsoft.com; cv=none;
 b=PTXvnXR1J6YILVwzVE0d804WeobCs36drpFMIhpJxOrrmNK3hG2XyXnu5BhLJX/c5LUGJ03XwyinlEAt2V+yOdaN0wAzi3Y2uM6r4l3TlKtPDGQeZ3QwEIkmfq7F87z7Bx17tF3DBAqKBqSMpyInMZZApIoTuK2m3Yo3wDeunnFUyJ9VN8fusvh06cSS4PCu85rj3nk50p4olMm5C5Tp3iGAeB4UvMWcHP7DrU6NNO7Dok3TpguN2WgpiH/wpNWi1ezvCJSW33sxM5weRwpp1GH69rhb8ZwdkLIWZ6FptarzPNIBJFZvPTdk8kH1lpuDbV1jL8mAGmw14j4ES8OwqA==
ARC-Message-Signature: i=1; a=rsa-sha256; c=relaxed/relaxed; d=microsoft.com;
 s=arcselector9901;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=yrurI0CrHyGTFt1VaTothhQZAEntRUm1BYM8Wyf5F+M=;
 b=QlVjgY8IVD1qD6EZRkdnx93pGLjUQhDCLBR2egCMrBWAqvHw7whM8WLvF0uBhUgfICO6iJvO+XH1Q3AIJWwe9GBLblwMPh0zKBiLFobdBIv+lAt3D3eue/rTGbvOJznPxahONbJ5C612JNGzr8hYNvVeWreSkjhWa5Rc8u897h2r5vjVVKQY1Sfe0jDUpqm3/xCj3DFEex9ERB2kMWDej9DCIvMCK/L9ZyXwS7l0V4sQ44rF7wx8K8zf1mvyKSsVXsqnUAG/nOq4ZIPOCxQJEKZnBuImxTy5fa6iDvnIN7rl4zZn9FJo6izjbLGfnkcrE2vgLNxaYA5GNukoyxAxng==
ARC-Authentication-Results: i=1; mx.microsoft.com 1; spf=pass
 smtp.mailfrom=wdc.com; dmarc=pass action=none header.from=wdc.com; dkim=pass
 header.d=wdc.com; arc=none
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
 d=sharedspace.onmicrosoft.com; s=selector2-sharedspace-onmicrosoft-com;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=yrurI0CrHyGTFt1VaTothhQZAEntRUm1BYM8Wyf5F+M=;
 b=GzVWvlLczVssmoO4sUWMwZX6y1kKTMS7Ul/iLA0vrryiJ3WmKs9ZX44Gbq9nVt6vs1P4vMzL4EogOLJ+5d3bIaOjz1vKa2b458FsV717cddlIUKgX7O0YnEn87Bxrn1SYxy/a141MCWoM5EP9cY8kFVk5sKfRJKSCcXU/QH/vfQ=
Authentication-Results: kernel.org; dkim=none (message not signed)
 header.d=none;kernel.org; dmarc=none action=none header.from=wdc.com;
Received: from DM6PR04MB6201.namprd04.prod.outlook.com (2603:10b6:5:127::32)
 by DM6PR04MB5961.namprd04.prod.outlook.com (2603:10b6:5:126::22) with
 Microsoft SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.3541.21; Mon, 9 Nov
 2020 11:37:58 +0000
Received: from DM6PR04MB6201.namprd04.prod.outlook.com
 ([fe80::d035:e2c6:c11:51dd]) by DM6PR04MB6201.namprd04.prod.outlook.com
 ([fe80::d035:e2c6:c11:51dd%6]) with mapi id 15.20.3541.025; Mon, 9 Nov 2020
 11:37:58 +0000
From: Anup Patel <anup.patel@wdc.com>
To: Will Deacon <will@kernel.org>
Cc: Paolo Bonzini <pbonzini@redhat.com>,
        Atish Patra <atish.patra@wdc.com>,
        Alistair Francis <Alistair.Francis@wdc.com>,
        Anup Patel <anup@brainfault.org>, kvm@vger.kernel.org,
        kvm-riscv@lists.infradead.org, Anup Patel <anup.patel@wdc.com>
Subject: [RFC PATCH v5 7/8] riscv: Handle SBI calls forwarded to user space
Date: Mon,  9 Nov 2020 17:06:54 +0530
Message-Id: <20201109113655.3733700-8-anup.patel@wdc.com>
X-Mailer: git-send-email 2.25.1
In-Reply-To: <20201109113655.3733700-1-anup.patel@wdc.com>
References: <20201109113655.3733700-1-anup.patel@wdc.com>
X-Originating-IP: [122.171.188.68]
X-ClientProxiedBy: MA1PR01CA0094.INDPRD01.PROD.OUTLOOK.COM (2603:1096:a00::34)
 To DM6PR04MB6201.namprd04.prod.outlook.com (2603:10b6:5:127::32)
MIME-Version: 1.0
X-MS-Exchange-MessageSentRepresentingType: 1
Received: from wdc.com (122.171.188.68) by
 MA1PR01CA0094.INDPRD01.PROD.OUTLOOK.COM (2603:1096:a00::34) with Microsoft
 SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.3541.21 via Frontend
 Transport; Mon, 9 Nov 2020 11:37:55 +0000
X-MS-PublicTrafficType: Email
X-MS-Office365-Filtering-HT: Tenant
X-MS-Office365-Filtering-Correlation-Id: 11c109d6-92f0-45d2-f975-08d884a3e7eb
X-MS-TrafficTypeDiagnostic: DM6PR04MB5961:
X-MS-Exchange-Transport-Forked: True
X-Microsoft-Antispam-PRVS: 
 <DM6PR04MB5961C263191B96FDAF46E5048DEA0@DM6PR04MB5961.namprd04.prod.outlook.com>
WDCIPOUTBOUND: EOP-TRUE
X-MS-Oob-TLC-OOBClassifiers: OLM:2803;
X-MS-Exchange-SenderADCheck: 1
X-Microsoft-Antispam: BCL:0;
X-Microsoft-Antispam-Message-Info: 
 S/1D3IZmNkaM8oDVSy/Yib53hbp2HbQTuPqhXBapMqXYmsw0Rb7YGLBeK02Y5/jA05d2lLWFjvPIZnyVZK7PiSLm9SwLVYgRyVqijYHGg68bhpPjDVjV6IWg9ihG7yioPrLGilr3qvPPM3+iTSlPVR61EjUYAiNHH5OIBDgPL7aeuixwxNJYT4cHxlyx+tWj7eQXxSc6CsgqSsTVFtRkIMKgKkz9pXxbGUak8RUerm1xrvdHyH0plok5DF44GstPFqdQcZuoN/U2rfeojmv1tdp3KO65oO94KtedgFmNSEzL+CKJa+qgcldDsdyWE4ZO
X-Forefront-Antispam-Report: 
 CIP:255.255.255.255;CTRY:;LANG:en;SCL:1;SRV:;IPV:NLI;SFV:NSPM;H:DM6PR04MB6201.namprd04.prod.outlook.com;PTR:;CAT:NONE;SFS:(4636009)(366004)(396003)(39860400002)(376002)(136003)(346002)(8936002)(8676002)(86362001)(956004)(2616005)(44832011)(55016002)(66946007)(2906002)(83380400001)(4326008)(66556008)(478600001)(316002)(7696005)(6916009)(66476007)(1076003)(5660300002)(26005)(16526019)(186003)(36756003)(52116002)(8886007)(54906003);DIR:OUT;SFP:1102;
X-MS-Exchange-AntiSpam-MessageData: 
 vG7I4jcyg0BvC/3kLd++a2SDbnTqlFECl85e0MCdrtBesePpmrP4eiCPiTS1dtcQR59dsvYusFdT9biMclrscI/6GixSCo+Zv0FI/KqKQMzEVwKqOAIkfWtuA90bx6nQCiv7iCLl1PSmsjp74aRUCjFc8+W4pTe2xikXmSOvSDK4b+21ixVvH39mzEXAqyU5aQk3oXCQ+VtOMEM7TvpFY/r09WfwQkjejlGXgyxQ3+ZqGiV8KNUabMtK0qCOczeJLu6QAWmsMD2rDsZjJ8/l9xsOaTc/wR6+rsfF/ic+LDBKE3DzvRThANq9qs05maIgjJj/yzcMrBb7FXdMpMnn7ZOoobWViY2PxeVAC4Th/zb9hpeFUqrXqV5uAUTRoxX4wrGIUxFaSBkuNkvps/QDU+LEqKMKay3tLOx3hzjrTjT8JkdAfor7ulHin6qcq/vup+dMapDq9o6ewxlJGzPDHWo6DFkSfCj6rVDIu3V5VDSVKDB5joNA7KehJn3YvcnTZeDdktwBh8ebFvl03W0oT7cw1mNc/h/u6CU7CMo5/WMNk98ecnS2PyOdXX4W4LOkHq0Z1KQpGAnp8EPoO+I0wGYj3kHazfhKTIizo1gxLMOy90Q3VSg03g0bvXtFPl6bhyF6BzofBGHaRgRi3nuGiQ==
X-OriginatorOrg: wdc.com
X-MS-Exchange-CrossTenant-Network-Message-Id: 
 11c109d6-92f0-45d2-f975-08d884a3e7eb
X-MS-Exchange-CrossTenant-AuthSource: DM6PR04MB6201.namprd04.prod.outlook.com
X-MS-Exchange-CrossTenant-AuthAs: Internal
X-MS-Exchange-CrossTenant-OriginalArrivalTime: 09 Nov 2020 11:37:58.0221
 (UTC)
X-MS-Exchange-CrossTenant-FromEntityHeader: Hosted
X-MS-Exchange-CrossTenant-Id: b61c8803-16f3-4c35-9b17-6f65f441df86
X-MS-Exchange-CrossTenant-MailboxType: HOSTED
X-MS-Exchange-CrossTenant-UserPrincipalName: 
 FpSD2VulN0WHuqLPNBM/Tt8dWLdhNMng+sXtzY8GpWy24JvML/CPm8iLOBCZNHE0jlcAseUyJcv0/HMm2+AK5w==
X-MS-Exchange-Transport-CrossTenantHeadersStamped: DM6PR04MB5961
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The kernel KVM RISC-V module will forward certain SBI calls
to user space. These forwared SBI calls will usually be the
SBI calls which cannot be emulated in kernel space such as
PUTCHAR and GETCHAR calls.

This patch extends kvm_cpu__handle_exit() to handle SBI calls
forwarded to user space.

Signed-off-by: Atish Patra <atish.patra@wdc.com>
Signed-off-by: Anup Patel <anup.patel@wdc.com>
---
 riscv/include/kvm/sbi.h | 48 ++++++++++++++++++++++++++++++++++++++++
 riscv/kvm-cpu.c         | 49 ++++++++++++++++++++++++++++++++++++++++-
 2 files changed, 96 insertions(+), 1 deletion(-)
 create mode 100644 riscv/include/kvm/sbi.h

diff --git a/riscv/include/kvm/sbi.h b/riscv/include/kvm/sbi.h
new file mode 100644
index 0000000..f4b4182
--- /dev/null
+++ b/riscv/include/kvm/sbi.h
@@ -0,0 +1,48 @@
+/* SPDX-License-Identifier: GPL-2.0-only */
+/*
+ * Common SBI related defines and macros to be used by RISC-V kernel,
+ * RISC-V KVM and userspace.
+ *
+ * Copyright (c) 2019 Western Digital Corporation or its affiliates.
+ */
+
+#ifndef __RISCV_SBI_H__
+#define __RISCV_SBI_H__
+
+enum sbi_ext_id {
+	SBI_EXT_0_1_SET_TIMER = 0x0,
+	SBI_EXT_0_1_CONSOLE_PUTCHAR = 0x1,
+	SBI_EXT_0_1_CONSOLE_GETCHAR = 0x2,
+	SBI_EXT_0_1_CLEAR_IPI = 0x3,
+	SBI_EXT_0_1_SEND_IPI = 0x4,
+	SBI_EXT_0_1_REMOTE_FENCE_I = 0x5,
+	SBI_EXT_0_1_REMOTE_SFENCE_VMA = 0x6,
+	SBI_EXT_0_1_REMOTE_SFENCE_VMA_ASID = 0x7,
+	SBI_EXT_0_1_SHUTDOWN = 0x8,
+	SBI_EXT_BASE = 0x10,
+};
+
+enum sbi_ext_base_fid {
+	SBI_BASE_GET_SPEC_VERSION = 0,
+	SBI_BASE_GET_IMP_ID,
+	SBI_BASE_GET_IMP_VERSION,
+	SBI_BASE_PROBE_EXT,
+	SBI_BASE_GET_MVENDORID,
+	SBI_BASE_GET_MARCHID,
+	SBI_BASE_GET_MIMPID,
+};
+
+#define SBI_SPEC_VERSION_DEFAULT	0x1
+#define SBI_SPEC_VERSION_MAJOR_OFFSET	24
+#define SBI_SPEC_VERSION_MAJOR_MASK	0x7f
+#define SBI_SPEC_VERSION_MINOR_MASK	0xffffff
+
+/* SBI return error codes */
+#define SBI_SUCCESS		0
+#define SBI_ERR_FAILURE		-1
+#define SBI_ERR_NOT_SUPPORTED	-2
+#define SBI_ERR_INVALID_PARAM   -3
+#define SBI_ERR_DENIED		-4
+#define SBI_ERR_INVALID_ADDRESS -5
+
+#endif
```
#### [GIT PULL] KVM fixes and selftests for 5.10-rc4
##### From: Paolo Bonzini <pbonzini@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Paolo Bonzini <pbonzini@redhat.com>
X-Patchwork-Id: 11892431
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-13.9 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_PULL_REQUEST,MAILING_LIST_MULTI,MENTIONS_GIT_HOSTING,SPF_HELO_NONE,
	SPF_PASS autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id A5F8BC388F7
	for <kvm@archiver.kernel.org>; Mon,  9 Nov 2020 19:47:50 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 585CC206E3
	for <kvm@archiver.kernel.org>; Mon,  9 Nov 2020 19:47:50 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="Aq6w4iL2"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1730191AbgKITrr (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Mon, 9 Nov 2020 14:47:47 -0500
Received: from us-smtp-delivery-124.mimecast.com ([63.128.21.124]:37998 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1729871AbgKITrp (ORCPT
        <rfc822;kvm@vger.kernel.org>); Mon, 9 Nov 2020 14:47:45 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1604951263;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=iirdq/1QAXSS1CYrhUM7nQnhEWfqB2KCd2Phwct/ZcQ=;
        b=Aq6w4iL2V/EIBBF+QFjfKDZQS+HrxjMBUG5wi2aBb70WroroSIdqv9HanpkqTqOaro9/Ru
        g0JLXdsY/N8GBVUCQ1+yHi74veLaWLauN0kACfQ+dlhPktAKfNWEUgoMHt1pkXHWBd8Ysh
        I5q30HkopvfCWRNkjPwfvTuZW3pa6KI=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-582-8_nzRj1DMR-Q5o7iVbJLhw-1; Mon, 09 Nov 2020 14:47:41 -0500
X-MC-Unique: 8_nzRj1DMR-Q5o7iVbJLhw-1
Received: from smtp.corp.redhat.com (int-mx01.intmail.prod.int.phx2.redhat.com
 [10.5.11.11])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id C45AB1074652;
        Mon,  9 Nov 2020 19:47:40 +0000 (UTC)
Received: from virtlab701.virt.lab.eng.bos.redhat.com
 (virtlab701.virt.lab.eng.bos.redhat.com [10.19.152.228])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 5EAAB5B4BB;
        Mon,  9 Nov 2020 19:47:40 +0000 (UTC)
From: Paolo Bonzini <pbonzini@redhat.com>
To: torvalds@linux-foundation.org
Cc: linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Subject: [GIT PULL] KVM fixes and selftests for 5.10-rc4
Date: Mon,  9 Nov 2020 14:47:39 -0500
Message-Id: <20201109194739.1035120-1-pbonzini@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.11
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Linus,

The following changes since commit 9478dec3b5e79a1431e2e2b911e32e52a11c6320:

  KVM: vmx: remove unused variable (2020-10-31 11:38:43 -0400)

are available in the Git repository at:

  https://git.kernel.org/pub/scm/virt/kvm/kvm.git tags/for-linus

for you to fetch changes up to 6d6a18fdde8b86b919b740ad629153de432d12a8:

  KVM: selftests: allow two iterations of dirty_log_perf_test (2020-11-09 09:45:17 -0500)

----------------------------------------------------------------
ARM:
- Fix compilation error when PMD and PUD are folded
- Fix regression in reads-as-zero behaviour of ID_AA64ZFR0_EL1
- Add aarch64 get-reg-list test

x86:
- fix semantic conflict between two series merged for 5.10
- fix (and test) enforcement of paravirtual cpuid features

Generic:
- various cleanups to memory management selftests
- new selftests testcase for performance of dirty logging

----------------------------------------------------------------

In case the selftests changes are too big, I placed them on top so they
can easily be deferred to 5.11.

Thanks,

Paolo

Aaron Lewis (3):
      selftests: kvm: Fix the segment descriptor layout to match the actual layout
      selftests: kvm: Clear uc so UCALL_NONE is being properly reported
      selftests: kvm: Add exception handling to selftests

Andrew Jones (9):
      KVM: arm64: Don't hide ID registers from userspace
      KVM: arm64: Consolidate REG_HIDDEN_GUEST/USER
      KVM: arm64: Check RAZ visibility in ID register accessors
      KVM: arm64: Remove AA64ZFR0_EL1 accessors
      KVM: selftests: Add aarch64 get-reg-list test
      KVM: selftests: Add blessed SVE registers to get-reg-list
      KVM: selftests: Drop pointless vm_create wrapper
      KVM: selftests: Make the per vcpu memory size global
      KVM: selftests: Make the number of vcpus global

Ben Gardon (5):
      KVM: selftests: Factor code out of demand_paging_test
      KVM: selftests: Remove address rounding in guest code
      KVM: selftests: Simplify demand_paging_test with timespec_diff_now
      KVM: selftests: Add wrfract to common guest code
      KVM: selftests: Introduce the dirty log perf test

Gavin Shan (1):
      KVM: arm64: Fix build error in user_mem_abort()

Li RongQing (1):
      KVM: x86/mmu: fix counting of rmap entries in pte_list_add

Maxim Levitsky (1):
      KVM: x86: use positive error values for msr emulation that causes #GP

Oliver Upton (4):
      kvm: x86: reads of restricted pv msrs should also result in #GP
      kvm: x86: ensure pv_cpuid.features is initialized when enabling cap
      kvm: x86: request masterclock update any time guest uses different msr
      selftests: kvm: test enforcement of paravirtual cpuid features

Pankaj Gupta (1):
      KVM: x86: handle MSR_IA32_DEBUGCTLMSR with report_ignored_msrs

Paolo Bonzini (2):
      Merge tag 'kvmarm-fixes-5.10-2' of git://git.kernel.org/.../kvmarm/kvmarm into HEAD
      KVM: selftests: allow two iterations of dirty_log_perf_test

Peter Xu (4):
      KVM: Documentation: Update entry for KVM_X86_SET_MSR_FILTER
      KVM: Documentation: Update entry for KVM_CAP_ENFORCE_PV_CPUID
      KVM: selftests: Always clear dirty bitmap after iteration
      KVM: selftests: Use a single binary for dirty/clear log test

 Documentation/virt/kvm/api.rst                     |   5 +-
 arch/arm64/kvm/mmu.c                               |   2 +
 arch/arm64/kvm/sys_regs.c                          | 108 +--
 arch/arm64/kvm/sys_regs.h                          |  16 +-
 arch/x86/kvm/cpuid.c                               |  23 +-
 arch/x86/kvm/cpuid.h                               |   1 +
 arch/x86/kvm/mmu/mmu.c                             |  12 +-
 arch/x86/kvm/x86.c                                 |  72 +-
 arch/x86/kvm/x86.h                                 |   8 +-
 tools/testing/selftests/kvm/.gitignore             |   4 +
 tools/testing/selftests/kvm/Makefile               |  25 +-
 .../selftests/kvm/aarch64/get-reg-list-sve.c       |   3 +
 tools/testing/selftests/kvm/aarch64/get-reg-list.c | 841 +++++++++++++++++++++
 tools/testing/selftests/kvm/clear_dirty_log_test.c |   6 -
 tools/testing/selftests/kvm/demand_paging_test.c   | 269 ++-----
 tools/testing/selftests/kvm/dirty_log_perf_test.c  | 376 +++++++++
 tools/testing/selftests/kvm/dirty_log_test.c       | 191 ++++-
 tools/testing/selftests/kvm/include/kvm_util.h     |   7 +-
 .../testing/selftests/kvm/include/perf_test_util.h | 198 +++++
 tools/testing/selftests/kvm/include/test_util.h    |   2 +
 .../selftests/kvm/include/x86_64/processor.h       |  38 +-
 .../testing/selftests/kvm/lib/aarch64/processor.c  |   4 +
 tools/testing/selftests/kvm/lib/aarch64/ucall.c    |   3 +
 tools/testing/selftests/kvm/lib/kvm_util.c         |  67 +-
 .../testing/selftests/kvm/lib/kvm_util_internal.h  |   2 +
 tools/testing/selftests/kvm/lib/s390x/processor.c  |   4 +
 tools/testing/selftests/kvm/lib/s390x/ucall.c      |   3 +
 tools/testing/selftests/kvm/lib/test_util.c        |  22 +-
 tools/testing/selftests/kvm/lib/x86_64/handlers.S  |  81 ++
 tools/testing/selftests/kvm/lib/x86_64/processor.c | 146 +++-
 tools/testing/selftests/kvm/lib/x86_64/ucall.c     |   3 +
 tools/testing/selftests/kvm/x86_64/kvm_pv_test.c   | 234 ++++++
 32 files changed, 2383 insertions(+), 393 deletions(-)
 create mode 100644 tools/testing/selftests/kvm/aarch64/get-reg-list-sve.c
 create mode 100644 tools/testing/selftests/kvm/aarch64/get-reg-list.c
 delete mode 100644 tools/testing/selftests/kvm/clear_dirty_log_test.c
 create mode 100644 tools/testing/selftests/kvm/dirty_log_perf_test.c
 create mode 100644 tools/testing/selftests/kvm/include/perf_test_util.h
 create mode 100644 tools/testing/selftests/kvm/lib/x86_64/handlers.S
 create mode 100644 tools/testing/selftests/kvm/x86_64/kvm_pv_test.c
```
#### [PATCH v2 2/5] KVM: arm64: Turn host HVC handling into a dispatch table
##### From: Marc Zyngier <maz@kernel.org>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Marc Zyngier <maz@kernel.org>
X-Patchwork-Id: 11892151
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-13.1 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,INCLUDES_PATCH,MAILING_LIST_MULTI,
	SIGNED_OFF_BY,SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED,USER_AGENT_GIT
	autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 815AEC55ABD
	for <kvm@archiver.kernel.org>; Mon,  9 Nov 2020 17:59:35 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 2AF302068D
	for <kvm@archiver.kernel.org>; Mon,  9 Nov 2020 17:59:35 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=kernel.org header.i=@kernel.org
 header.b="waEzZM9v"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1730327AbgKIR7e (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Mon, 9 Nov 2020 12:59:34 -0500
Received: from mail.kernel.org ([198.145.29.99]:47238 "EHLO mail.kernel.org"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1730017AbgKIR7c (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 9 Nov 2020 12:59:32 -0500
Received: from disco-boy.misterjones.org (disco-boy.misterjones.org
 [51.254.78.96])
        (using TLSv1.2 with cipher ECDHE-RSA-AES256-GCM-SHA384 (256/256 bits))
        (No client certificate requested)
        by mail.kernel.org (Postfix) with ESMTPSA id 6A83B2067D;
        Mon,  9 Nov 2020 17:59:30 +0000 (UTC)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple; d=kernel.org;
        s=default; t=1604944770;
        bh=nGVW/NiwG8KzPVzwo3qIsfuk1pq1h3XDKPnw04oTURI=;
        h=From:To:Cc:Subject:Date:In-Reply-To:References:From;
        b=waEzZM9ve6jspeN4wZ2KJ4dc41WrmnWpvUAgJAdCw3j3f/cAhTNpG8ZR/2G/S7Q+m
         st7DL7xwxHju8qqFdpX6ffWExdj5Zxx2HJJAqHCcqX0Ni82d7R9Bc5lErTa5/OTUwU
         5589mK0CxmFzXjFdlFzpxqKFiqQZryPuM9gvd9lM=
Received: from 78.163-31-62.static.virginmediabusiness.co.uk ([62.31.163.78]
 helo=why.lan)
        by disco-boy.misterjones.org with esmtpsa  (TLS1.3) tls
 TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384
        (Exim 4.94)
        (envelope-from <maz@kernel.org>)
        id 1kcBRw-009BQs-KS; Mon, 09 Nov 2020 17:59:28 +0000
From: Marc Zyngier <maz@kernel.org>
To: linux-arm-kernel@lists.infradead.org, kvmarm@lists.cs.columbia.edu,
        kvm@vger.kernel.org
Cc: James Morse <james.morse@arm.com>,
        Julien Thierry <julien.thierry.kdev@gmail.com>,
        Suzuki K Poulose <suzuki.poulose@arm.com>,
        Alexandru Elisei <alexandru.elisei@arm.com>,
        Andrew Scull <ascull@google.com>,
        Will Deacon <will@kernel.org>,
        Quentin Perret <qperret@google.com>, ndesaulniers@google.com,
        dbrazdil@google.com, kernel-team@android.com
Subject: [PATCH v2 2/5] KVM: arm64: Turn host HVC handling into a dispatch
 table
Date: Mon,  9 Nov 2020 17:59:20 +0000
Message-Id: <20201109175923.445945-3-maz@kernel.org>
X-Mailer: git-send-email 2.28.0
In-Reply-To: <20201109175923.445945-1-maz@kernel.org>
References: <20201109175923.445945-1-maz@kernel.org>
MIME-Version: 1.0
X-SA-Exim-Connect-IP: 62.31.163.78
X-SA-Exim-Rcpt-To: linux-arm-kernel@lists.infradead.org,
 kvmarm@lists.cs.columbia.edu, kvm@vger.kernel.org, james.morse@arm.com,
 julien.thierry.kdev@gmail.com, suzuki.poulose@arm.com,
 alexandru.elisei@arm.com, ascull@google.com, will@kernel.org,
 qperret@google.com, ndesaulniers@google.com, dbrazdil@google.com,
 kernel-team@android.com
X-SA-Exim-Mail-From: maz@kernel.org
X-SA-Exim-Scanned: No (on disco-boy.misterjones.org);
 SAEximRunCond expanded to false
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Now that we can use function pointer, use a dispatch table to call
the individual HVC handlers, leading to more maintainable code.

Further improvements include helpers to declare the mapping of
local variables to values passed in the host context.

Reviewed-by: Alexandru Elisei <alexandru.elisei@arm.com>
Signed-off-by: Marc Zyngier <maz@kernel.org>
---
 arch/arm64/kernel/image-vars.h     |   1 +
 arch/arm64/kvm/hyp/nvhe/hyp-main.c | 228 +++++++++++++++++------------
 2 files changed, 135 insertions(+), 94 deletions(-)

```
#### [PATCH v15 01/17] RISC-V: Add hypervisor extension related CSR defines
##### From: Anup Patel <anup.patel@wdc.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Anup Patel <Anup.Patel@wdc.com>
X-Patchwork-Id: 11891211
Return-Path: <SRS0=zqVv=EP=vger.kernel.org=kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-12.7 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_PATCH,MAILING_LIST_MULTI,
	MSGID_FROM_MTA_HEADER,SIGNED_OFF_BY,SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED,
	USER_AGENT_GIT autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id CD818C4741F
	for <kvm@archiver.kernel.org>; Mon,  9 Nov 2020 11:33:49 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 64CB42084C
	for <kvm@archiver.kernel.org>; Mon,  9 Nov 2020 11:33:49 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=fail reason="signature verification failed" (2048-bit key)
 header.d=wdc.com header.i=@wdc.com header.b="SlSnl5UP";
	dkim=pass (1024-bit key) header.d=sharedspace.onmicrosoft.com
 header.i=@sharedspace.onmicrosoft.com header.b="U/K03Vzh"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729848AbgKILdm (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Mon, 9 Nov 2020 06:33:42 -0500
Received: from esa6.hgst.iphmx.com ([216.71.154.45]:25576 "EHLO
        esa6.hgst.iphmx.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1729812AbgKILdl (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 9 Nov 2020 06:33:41 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=simple/simple;
  d=wdc.com; i=@wdc.com; q=dns/txt; s=dkim.wdc.com;
  t=1604921620; x=1636457620;
  h=from:to:cc:subject:date:message-id:in-reply-to:
   references:content-transfer-encoding:mime-version;
  bh=EK/5efwN5ctponF7YeDfvp60Cq6LVz8yReJHQCaEMVs=;
  b=SlSnl5UPdGmr/nDoyDL008Q0GCnot070T8DM9u4gSeQCXQFtPMCwJa/D
   jz4nWrm4VyrZkzKPYvzr0cVtKlP28Dz11oOPLA/iLJ+yO86fw6bxAv7ll
   2KkmedS+esiJ56w44lRDCDrCdWbZb4MOcYxoKmiUeTRhkVcUwhFhZTmXr
   eFHou0PO5J9BA4nXB81ljyvSD+W4PpcxeweXIC3W5Vl/luOMlCxh/vMTa
   A7EN+GZ86RSBm+fhFo3zK9Fe1/SEy/wj7NaQahuxG6s5bZfB7PyAxMgIt
   NcVCqQGXOCH83K4STjnfIHonXuhy4zX7UIg9tEPD4H6qSyQrgzsfu5HLJ
   Q==;
IronPort-SDR: 
 5OsgOFmcNpuDX+iGQU/SXNXhGRW0s8qPXfQxakRsreICA8y6GRqz24PhRyP0W7+QIdvOb1w5xb
 SmVfKgJutSpSJpolF1TShM5OnqfmhwBaTLN/13fMY8ZOoManuFqTeP4VPaPrkeeTDZgY8y4tr2
 jFqt3g0/h3WKGl0JFvyhcvmut02xTS1BTDQyn3OVTc9m2En2cX89Ux1Ij0jP9gtf80gNoCYVfQ
 mpKYKbraGcpKKEGVQCAAfjJAW0I8qgqgOWWM6RS7brSo59KaUVdZrErzLZ9Y+fUCXaULqlBkTE
 q3o=
X-IronPort-AV: E=Sophos;i="5.77,463,1596470400";
   d="scan'208";a="153382732"
Received: from mail-bn8nam11lp2172.outbound.protection.outlook.com (HELO
 NAM11-BN8-obe.outbound.protection.outlook.com) ([104.47.58.172])
  by ob1.hgst.iphmx.com with ESMTP; 09 Nov 2020 19:33:38 +0800
ARC-Seal: i=1; a=rsa-sha256; s=arcselector9901; d=microsoft.com; cv=none;
 b=Vj/EXjXoK2jnIkFLtSDAgl5lBRdh9P7U1lhGwZH/ftgEcpUllXWf//NZYfzRMOwWKobYf+0A32wMd4K8cANVM/rvqQiN4hBCZBWdvNM057BYHv1+SD645Jo9oZbe6QmdbazpBlxeNYNL6HrTMU/ZVX6r4skm4MG5ozb6bcFcb2TjrP38VXsTMNocL8q+VnOm86Uj4jA1fNyezq/2ve/SJ43EMni9ij0n9MRPhgutsOHtkGkvRjkcVS4ozhzDCKN63raTRmxMGup+jXBVuU2hChU8IjgVinrTnRRmZJPbAsOo1u1YQcgxjMil16JCK78dHFrB2TEZkg80hA6LELEG8A==
ARC-Message-Signature: i=1; a=rsa-sha256; c=relaxed/relaxed; d=microsoft.com;
 s=arcselector9901;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=mHs+gj89i8AEy86hjmH6iBGFS+byJUeIDojUGHCPg8A=;
 b=kidGzpkKltVf+Ohh7S++9COw1NQGk1K2Cy075ZwhgTMy8WQ5WvP6ETq57S8msV9SWG7fCfJ0bQ1oTG0X+S2LiZjQ1XPTtvh1LTcKHw//DtbmNGnj3q7upX4qEV+/qmM+2YTKzxQcwXsF2Lh8RlHWl+NlEotwzWWWrt29AXqwKVT+yXsJJe4+jmpOjBEHpKfqibeInVCSNQs4qOdU4LhhGDLcm2/FdokEMUeqzA3id0HP04PhZnE78P2Ek1oHAFlanoTHMDrs31VAuGHmqT44Yu7lekF7YivZHtAyuImJji5GUIVUSHMRLy6ROtCX1n0C62Jo0LGO0HnxdI9FB3zc0g==
ARC-Authentication-Results: i=1; mx.microsoft.com 1; spf=pass
 smtp.mailfrom=wdc.com; dmarc=pass action=none header.from=wdc.com; dkim=pass
 header.d=wdc.com; arc=none
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
 d=sharedspace.onmicrosoft.com; s=selector2-sharedspace-onmicrosoft-com;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=mHs+gj89i8AEy86hjmH6iBGFS+byJUeIDojUGHCPg8A=;
 b=U/K03Vzht8AbUctdjvK/Lrs06LS9s9B81/yNeTmnzHxEQHqZgfv/b5OWCYoB/i6ZPunZVjLgB2Vt933kbQ44+ueA+BPTy7ta55DIKP4ZFk2skM1mbktcLDfolpIHv9Kcw9JL5ydDXm8tZn8jWNirmyfF0hyYbcbgDgeRhsknlqs=
Authentication-Results: dabbelt.com; dkim=none (message not signed)
 header.d=none;dabbelt.com; dmarc=none action=none header.from=wdc.com;
Received: from DM6PR04MB6201.namprd04.prod.outlook.com (2603:10b6:5:127::32)
 by DM6PR04MB3866.namprd04.prod.outlook.com (2603:10b6:5:ad::19) with
 Microsoft SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.3541.21; Mon, 9 Nov
 2020 11:33:36 +0000
Received: from DM6PR04MB6201.namprd04.prod.outlook.com
 ([fe80::d035:e2c6:c11:51dd]) by DM6PR04MB6201.namprd04.prod.outlook.com
 ([fe80::d035:e2c6:c11:51dd%6]) with mapi id 15.20.3541.025; Mon, 9 Nov 2020
 11:33:36 +0000
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
Subject: [PATCH v15 01/17] RISC-V: Add hypervisor extension related CSR
 defines
Date: Mon,  9 Nov 2020 17:02:24 +0530
Message-Id: <20201109113240.3733496-2-anup.patel@wdc.com>
X-Mailer: git-send-email 2.25.1
In-Reply-To: <20201109113240.3733496-1-anup.patel@wdc.com>
References: <20201109113240.3733496-1-anup.patel@wdc.com>
X-Originating-IP: [122.171.188.68]
X-ClientProxiedBy: MAXPR01CA0099.INDPRD01.PROD.OUTLOOK.COM
 (2603:1096:a00:5d::17) To DM6PR04MB6201.namprd04.prod.outlook.com
 (2603:10b6:5:127::32)
MIME-Version: 1.0
X-MS-Exchange-MessageSentRepresentingType: 1
Received: from wdc.com (122.171.188.68) by
 MAXPR01CA0099.INDPRD01.PROD.OUTLOOK.COM (2603:1096:a00:5d::17) with Microsoft
 SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.3541.21 via Frontend
 Transport; Mon, 9 Nov 2020 11:33:31 +0000
X-MS-PublicTrafficType: Email
X-MS-Office365-Filtering-HT: Tenant
X-MS-Office365-Filtering-Correlation-Id: dc26e639-e8d5-4553-0466-08d884a34bdc
X-MS-TrafficTypeDiagnostic: DM6PR04MB3866:
X-MS-Exchange-Transport-Forked: True
X-Microsoft-Antispam-PRVS: 
 <DM6PR04MB3866983AA1F5233060533CEA8DEA0@DM6PR04MB3866.namprd04.prod.outlook.com>
WDCIPOUTBOUND: EOP-TRUE
X-MS-Oob-TLC-OOBClassifiers: OLM:11;
X-MS-Exchange-SenderADCheck: 1
X-Microsoft-Antispam: BCL:0;
X-Microsoft-Antispam-Message-Info: 
 PjUh8ZJftseg4VCfPREzifnvfncaK7UURBvxBSr15J2h4d4wAIHBLLMnFQduBZhzWY2aXgqmvGWvVkPuRm2LrN6kKqJKaCGQYeqSfwnK6RbwHHMo+ZjTTOrJfty5osOt697nQmrP6VLTbgnR5H+MpPL4E4zexDjCTchctRdmRcWvSOmwJf9WymXjKFq4swWeejQF5AM9jLGNuf8vAr+8aEfvlmgw2vGM/A1PpvgVTPSpkr6pm/Aj5HrlEsUxYL4rx4cGgVZdWNJWshvGwEGsgNhrCcFezgmpU8t9oAau46BYN4Xr5rCIVKNrFcihU8h44Ch8FlhVG2oNK9XS4/qzCg==
X-Forefront-Antispam-Report: 
 CIP:255.255.255.255;CTRY:;LANG:en;SCL:1;SRV:;IPV:NLI;SFV:NSPM;H:DM6PR04MB6201.namprd04.prod.outlook.com;PTR:;CAT:NONE;SFS:(4636009)(366004)(346002)(396003)(136003)(39860400002)(376002)(55016002)(7416002)(83380400001)(1076003)(44832011)(16526019)(186003)(316002)(26005)(8676002)(110136005)(54906003)(5660300002)(52116002)(7696005)(956004)(2616005)(478600001)(66476007)(66556008)(4326008)(66946007)(6666004)(2906002)(36756003)(86362001)(8886007)(8936002);DIR:OUT;SFP:1102;
X-MS-Exchange-AntiSpam-MessageData: 
 D/Pg7N2nxqBRXQ+NPe+eHa5Z+UQSQ9ZuY7Qbh51UeeK5Ld31ZsNAuObqmYkBl6Ekip8YQ0WCzVz9FJ4VkN2RRS4lgzMMs6WWwY8+A93LCXew0lx3a6LWmFT8A1PC4uya7leTKZuSlySee8HVBl891+OKafvDHxCtg6qzit2kZ+rMuc4ONdrf9nZi75R1kvcoH+slAcpCbnkJT9HD2bVgKpVbJ17MGcz3Dz3af5NxpptswKO7VMygGEju24/m221dXLNbrolSEEvfJYfBn8FO+ZU+WkuXSXYNFnoz6gTGPPhXCIJpED7LEYOCs4kSZjrT+McIXjQ/9m0VEELtuLPOHg9jmAIP722Hyseu58HvMj9iPPpxj8cJUYmu0vJDBru3OWVvX0720isPe7TLXrfzJM0zwwAL72wEXrS0fUF/fcrGSWOP7u11TEDrgfC10UBQLyYSJHybJywSVMD/kiOsYwqY55I/RaaWjoRA5gGxBcmvBPYcAT07tKDg5QIqf7DIG5LTb/SjXS0aRrOLxdWBaouC512hvSxAQBR6quEOuVjb2LgQa+WfYxp+INSNFkmqrCj1kQtWM9deQKCiByC/CT7GcKOYtuvritnLBJoupci7kdiwkiGkEN0UIeF9sJ3frDMC4PYziyu6v7tyZyHFFw==
X-OriginatorOrg: wdc.com
X-MS-Exchange-CrossTenant-Network-Message-Id: 
 dc26e639-e8d5-4553-0466-08d884a34bdc
X-MS-Exchange-CrossTenant-AuthSource: DM6PR04MB6201.namprd04.prod.outlook.com
X-MS-Exchange-CrossTenant-AuthAs: Internal
X-MS-Exchange-CrossTenant-OriginalArrivalTime: 09 Nov 2020 11:33:36.2169
 (UTC)
X-MS-Exchange-CrossTenant-FromEntityHeader: Hosted
X-MS-Exchange-CrossTenant-Id: b61c8803-16f3-4c35-9b17-6f65f441df86
X-MS-Exchange-CrossTenant-MailboxType: HOSTED
X-MS-Exchange-CrossTenant-UserPrincipalName: 
 +Wf+XYY7RTcdrJEEJk8ed/9lK+t7JZK19rLpU6+0ZoTe+2WuTpQLKPyxa7bcu96uKfCcQ6kdcL0so5d05ICZ1g==
X-MS-Exchange-Transport-CrossTenantHeadersStamped: DM6PR04MB3866
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
 arch/riscv/include/asm/csr.h | 89 ++++++++++++++++++++++++++++++++++++
 1 file changed, 89 insertions(+)

```
#### [PATCH] KVM: VMX: Extract vmx_update_secondary_exec_control()
##### From: Robert Hoo <robert.hu@linux.intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Robert Hoo <robert.hu@linux.intel.com>
X-Patchwork-Id: 11890949
Return-Path: <SRS0=zqVv=EP=vger.kernel.org=kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-12.8 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_PATCH,MAILING_LIST_MULTI,SIGNED_OFF_BY,
	SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED,USER_AGENT_GIT autolearn=ham
	autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id EE2F8C2D0A3
	for <kvm@archiver.kernel.org>; Mon,  9 Nov 2020 10:50:07 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id A4A2420674
	for <kvm@archiver.kernel.org>; Mon,  9 Nov 2020 10:50:07 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727774AbgKIKuG (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Mon, 9 Nov 2020 05:50:06 -0500
Received: from mga06.intel.com ([134.134.136.31]:14726 "EHLO mga06.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1727183AbgKIKuG (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 9 Nov 2020 05:50:06 -0500
IronPort-SDR: 
 h4vSZ50VRU06ou2V0efcjioKhylYvXkacJKSIy8eHbhp1trWpPnr260Ecf9XhzWezPV3IP5sT1
 +EJqY1ndJuBw==
X-IronPort-AV: E=McAfee;i="6000,8403,9799"; a="231414470"
X-IronPort-AV: E=Sophos;i="5.77,463,1596524400";
   d="scan'208";a="231414470"
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from fmsmga002.fm.intel.com ([10.253.24.26])
  by orsmga104.jf.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 09 Nov 2020 02:50:05 -0800
IronPort-SDR: 
 V9IQokZaV3BmJAerm00exXl37ZQ/x8K5Gug15Dz3+V7cIGY0nM4nO/gJNDpjnpcNx6/oBdr7zZ
 h6F7xXyGmLxg==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.77,463,1596524400";
   d="scan'208";a="359604402"
Received: from sqa-gate.sh.intel.com (HELO robert-ivt.tsp.org)
 ([10.239.48.212])
  by fmsmga002.fm.intel.com with ESMTP; 09 Nov 2020 02:50:03 -0800
From: Robert Hoo <robert.hu@linux.intel.com>
To: pbonzini@redhat.com, vkuznets@redhat.com, wanpengli@tencent.com,
        jmattson@google.com, joro@8bytes.org, kvm@vger.kernel.org
Cc: robert.hu@intel.com, Robert Hoo <robert.hu@linux.intel.com>
Subject: [PATCH] KVM: VMX: Extract vmx_update_secondary_exec_control()
Date: Mon,  9 Nov 2020 18:49:48 +0800
Message-Id: <1604918988-26884-1-git-send-email-robert.hu@linux.intel.com>
X-Mailer: git-send-email 1.8.3.1
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Currently, vmx_compute_secondary_exec_control() is invoked by init_vmcs()
and vmx_vcpu_after_set_cpuid().
init_vmcs() is called when creating vcpu and vmx_vcpu_after_set_cpuid() is
called when guest cpuid is settled.

vmx_compute_secondary_exec_control() can be divided into 2 parts: 1)
compute guest's effective secondary_exec_control = vmcs_config + guest
settings. 2) further update effective secondary_exec_control on those
fields related to guest's cpuid.

When vmx_create_vcpu() --> init_vmcs() -->
vmx_compute_secondary_exec_control(), guest cpuid is actually blank, so
doing part 2 is non sense; and futher, part 2 involves
vmx.nested.msrs updates, which later, will be overwritten by
copying vmcs_config.nested. This doesn't cause trouble now is because
vmx_vcpu_after_set_cpuid() --> vmx_compute_secondary_exec_control() later
will update again, but it is wrong in essence.

This patch is to extract part 2 into vmx_update_secondary_exec_control(),
which is called only by vmx_vcpu_after_set_cpuid(), when guest cpuid is
settled. And vmx_vcpu_after_set_cpuid() doesn't need to redo part 1, which
has been done by init_vmcs() earlier.


Signed-off-by: Robert Hoo <robert.hu@linux.intel.com>
---
 arch/x86/kvm/vmx/vmx.c | 15 ++++++++++++++-
 1 file changed, 14 insertions(+), 1 deletion(-)

```
#### [PATCH v2 01/17] KVM: x86/pmu: Set MSR_IA32_MISC_ENABLE_EMON bit when vPMU is enabled
##### From: Like Xu <like.xu@linux.intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Like Xu <like.xu@linux.intel.com>
X-Patchwork-Id: 11890313
Return-Path: <SRS0=zqVv=EP=vger.kernel.org=kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-12.7 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_PATCH,MAILING_LIST_MULTI,SIGNED_OFF_BY,
	SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED,USER_AGENT_GIT autolearn=unavailable
	autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 4DD85C56202
	for <kvm@archiver.kernel.org>; Mon,  9 Nov 2020 02:16:58 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 1BE66206E3
	for <kvm@archiver.kernel.org>; Mon,  9 Nov 2020 02:16:57 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729153AbgKICQz (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Sun, 8 Nov 2020 21:16:55 -0500
Received: from mga01.intel.com ([192.55.52.88]:64875 "EHLO mga01.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1729125AbgKICQy (ORCPT <rfc822;kvm@vger.kernel.org>);
        Sun, 8 Nov 2020 21:16:54 -0500
IronPort-SDR: 
 9asik7ZeqCxYAszx8qL1EeLLOBOVd3Wsw8l5BQfZ539BLHpUcjCoXXB1kyeZciDwAJij09sFmD
 j7h5UFQy7UPw==
X-IronPort-AV: E=McAfee;i="6000,8403,9799"; a="187684547"
X-IronPort-AV: E=Sophos;i="5.77,462,1596524400";
   d="scan'208";a="187684547"
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from orsmga005.jf.intel.com ([10.7.209.41])
  by fmsmga101.fm.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 08 Nov 2020 18:16:53 -0800
IronPort-SDR: 
 RHRTPYuFxvARrvejKIp3C65zMLqxBTSqZVLnnyLn0asaQ3RPDqho9kg8zBt7Um72ZJpZdoalGt
 48N1WQVw1H6w==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.77,462,1596524400";
   d="scan'208";a="540646110"
Received: from e5-2699-v4-likexu.sh.intel.com ([10.239.48.39])
  by orsmga005.jf.intel.com with ESMTP; 08 Nov 2020 18:16:49 -0800
From: Like Xu <like.xu@linux.intel.com>
To: Peter Zijlstra <peterz@infradead.org>,
        Paolo Bonzini <pbonzini@redhat.com>, kvm@vger.kernel.org
Cc: Sean Christopherson <sean.j.christopherson@intel.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>,
        Kan Liang <kan.liang@linux.intel.com>, luwei.kang@intel.com,
        Thomas Gleixner <tglx@linutronix.de>, wei.w.wang@intel.com,
        Tony Luck <tony.luck@intel.com>,
        Stephane Eranian <eranian@google.com>,
        Mark Gross <mgross@linux.intel.com>,
        Srinivas Pandruvada <srinivas.pandruvada@linux.intel.com>,
        linux-kernel@vger.kernel.org
Subject: [PATCH v2 01/17] KVM: x86/pmu: Set MSR_IA32_MISC_ENABLE_EMON bit when
 vPMU is enabled
Date: Mon,  9 Nov 2020 10:12:38 +0800
Message-Id: <20201109021254.79755-2-like.xu@linux.intel.com>
X-Mailer: git-send-email 2.21.3
In-Reply-To: <20201109021254.79755-1-like.xu@linux.intel.com>
References: <20201109021254.79755-1-like.xu@linux.intel.com>
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

On Intel platforms, software may uses IA32_MISC_ENABLE[7]
bit to detect whether the performance monitoring facility
is supported in the processor.

It's dependent on the PMU being enabled for the guest and
a write to this PMU available bit will be ignored.

Cc: Yao Yuan <yuan.yao@intel.com>
Signed-off-by: Like Xu <like.xu@linux.intel.com>
---
 arch/x86/kvm/vmx/pmu_intel.c | 2 ++
 arch/x86/kvm/x86.c           | 1 +
 2 files changed, 3 insertions(+)

```
#### [PATCH v2 4/5] KVM: arm64: Simplify __kvm_enable_ssbs()
##### From: Marc Zyngier <maz@kernel.org>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Marc Zyngier <maz@kernel.org>
X-Patchwork-Id: 11892141
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-13.1 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,INCLUDES_PATCH,MAILING_LIST_MULTI,
	SIGNED_OFF_BY,SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED,USER_AGENT_GIT
	autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id B2377C388F7
	for <kvm@archiver.kernel.org>; Mon,  9 Nov 2020 17:59:34 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 642D72067D
	for <kvm@archiver.kernel.org>; Mon,  9 Nov 2020 17:59:34 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=kernel.org header.i=@kernel.org
 header.b="PO3krMRa"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1730303AbgKIR7d (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Mon, 9 Nov 2020 12:59:33 -0500
Received: from mail.kernel.org ([198.145.29.99]:47272 "EHLO mail.kernel.org"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1730090AbgKIR7c (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 9 Nov 2020 12:59:32 -0500
Received: from disco-boy.misterjones.org (disco-boy.misterjones.org
 [51.254.78.96])
        (using TLSv1.2 with cipher ECDHE-RSA-AES256-GCM-SHA384 (256/256 bits))
        (No client certificate requested)
        by mail.kernel.org (Postfix) with ESMTPSA id BAC4C21D7F;
        Mon,  9 Nov 2020 17:59:31 +0000 (UTC)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple; d=kernel.org;
        s=default; t=1604944771;
        bh=wJ6/BUTOMZrzU8+ZiMi/w3DAO5no+Zm2kiKxUJBo+Ko=;
        h=From:To:Cc:Subject:Date:In-Reply-To:References:From;
        b=PO3krMRa3GlFGVqRfOGFGuNXPncdCDVj544IUEu/Erc/J79RXgEvUrJ1XJ0Xv1Dql
         AKUKH6IN2aOIBe07mcnJNhH64gr2kmcpO2chVIGZMw0h8QqKI1qRMeICH+QuGoeCVc
         RiCOc9djjHrrB87RJC/uZe4Jav6XwKOnRfkOew50=
Received: from 78.163-31-62.static.virginmediabusiness.co.uk ([62.31.163.78]
 helo=why.lan)
        by disco-boy.misterjones.org with esmtpsa  (TLS1.3) tls
 TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384
        (Exim 4.94)
        (envelope-from <maz@kernel.org>)
        id 1kcBRx-009BQs-Tx; Mon, 09 Nov 2020 17:59:30 +0000
From: Marc Zyngier <maz@kernel.org>
To: linux-arm-kernel@lists.infradead.org, kvmarm@lists.cs.columbia.edu,
        kvm@vger.kernel.org
Cc: James Morse <james.morse@arm.com>,
        Julien Thierry <julien.thierry.kdev@gmail.com>,
        Suzuki K Poulose <suzuki.poulose@arm.com>,
        Alexandru Elisei <alexandru.elisei@arm.com>,
        Andrew Scull <ascull@google.com>,
        Will Deacon <will@kernel.org>,
        Quentin Perret <qperret@google.com>, ndesaulniers@google.com,
        dbrazdil@google.com, kernel-team@android.com
Subject: [PATCH v2 4/5] KVM: arm64: Simplify __kvm_enable_ssbs()
Date: Mon,  9 Nov 2020 17:59:22 +0000
Message-Id: <20201109175923.445945-5-maz@kernel.org>
X-Mailer: git-send-email 2.28.0
In-Reply-To: <20201109175923.445945-1-maz@kernel.org>
References: <20201109175923.445945-1-maz@kernel.org>
MIME-Version: 1.0
X-SA-Exim-Connect-IP: 62.31.163.78
X-SA-Exim-Rcpt-To: linux-arm-kernel@lists.infradead.org,
 kvmarm@lists.cs.columbia.edu, kvm@vger.kernel.org, james.morse@arm.com,
 julien.thierry.kdev@gmail.com, suzuki.poulose@arm.com,
 alexandru.elisei@arm.com, ascull@google.com, will@kernel.org,
 qperret@google.com, ndesaulniers@google.com, dbrazdil@google.com,
 kernel-team@android.com
X-SA-Exim-Mail-From: maz@kernel.org
X-SA-Exim-Scanned: No (on disco-boy.misterjones.org);
 SAEximRunCond expanded to false
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Move the setting of SSBS directly into the HVC handler, using
the C helpers rather than the inline asssembly code.

Reviewed-by: Alexandru Elisei <alexandru.elisei@arm.com>
Signed-off-by: Marc Zyngier <maz@kernel.org>
---
 arch/arm64/include/asm/kvm_asm.h    |  2 --
 arch/arm64/include/asm/sysreg.h     |  1 +
 arch/arm64/kvm/hyp/nvhe/hyp-main.c  |  6 +++++-
 arch/arm64/kvm/hyp/nvhe/sysreg-sr.c | 11 -----------
 4 files changed, 6 insertions(+), 14 deletions(-)

```
#### [PATCH v2 3/5] KVM: arm64: Patch kimage_voffset instead of loading the EL1 value
##### From: Marc Zyngier <maz@kernel.org>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Marc Zyngier <maz@kernel.org>
X-Patchwork-Id: 11892143
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-13.1 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,INCLUDES_PATCH,MAILING_LIST_MULTI,
	SIGNED_OFF_BY,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT autolearn=ham
	autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 26566C2D0A3
	for <kvm@archiver.kernel.org>; Mon,  9 Nov 2020 17:59:38 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id C379E20781
	for <kvm@archiver.kernel.org>; Mon,  9 Nov 2020 17:59:37 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=kernel.org header.i=@kernel.org
 header.b="UP0l2FB4"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1730125AbgKIR7c (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Mon, 9 Nov 2020 12:59:32 -0500
Received: from mail.kernel.org ([198.145.29.99]:47272 "EHLO mail.kernel.org"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1729973AbgKIR7b (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 9 Nov 2020 12:59:31 -0500
Received: from disco-boy.misterjones.org (disco-boy.misterjones.org
 [51.254.78.96])
        (using TLSv1.2 with cipher ECDHE-RSA-AES256-GCM-SHA384 (256/256 bits))
        (No client certificate requested)
        by mail.kernel.org (Postfix) with ESMTPSA id 170A0216C4;
        Mon,  9 Nov 2020 17:59:31 +0000 (UTC)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple; d=kernel.org;
        s=default; t=1604944771;
        bh=gc4v4mCeLEmNxjSK4Rq4QvjBgesKnjE95kfraj2zIz4=;
        h=From:To:Cc:Subject:Date:In-Reply-To:References:From;
        b=UP0l2FB4cQ1bmzPZIsO7BLCJWfwuCxXGaZ46IG/ucn4B1qnkhdi4uTCUWSRBqCQYW
         nwdENDdHOOAhIll9yTOCeh8B/Gqt9/2murGdmxWPh4kPuhFs24xIvXN1KgUiLkYxmE
         4lGfBsc8fDsj9CEd+2mpfH4X3RLHtT07jFh7Dt80=
Received: from 78.163-31-62.static.virginmediabusiness.co.uk ([62.31.163.78]
 helo=why.lan)
        by disco-boy.misterjones.org with esmtpsa  (TLS1.3) tls
 TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384
        (Exim 4.94)
        (envelope-from <maz@kernel.org>)
        id 1kcBRx-009BQs-8N; Mon, 09 Nov 2020 17:59:29 +0000
From: Marc Zyngier <maz@kernel.org>
To: linux-arm-kernel@lists.infradead.org, kvmarm@lists.cs.columbia.edu,
        kvm@vger.kernel.org
Cc: James Morse <james.morse@arm.com>,
        Julien Thierry <julien.thierry.kdev@gmail.com>,
        Suzuki K Poulose <suzuki.poulose@arm.com>,
        Alexandru Elisei <alexandru.elisei@arm.com>,
        Andrew Scull <ascull@google.com>,
        Will Deacon <will@kernel.org>,
        Quentin Perret <qperret@google.com>, ndesaulniers@google.com,
        dbrazdil@google.com, kernel-team@android.com
Subject: [PATCH v2 3/5] KVM: arm64: Patch kimage_voffset instead of loading
 the EL1 value
Date: Mon,  9 Nov 2020 17:59:21 +0000
Message-Id: <20201109175923.445945-4-maz@kernel.org>
X-Mailer: git-send-email 2.28.0
In-Reply-To: <20201109175923.445945-1-maz@kernel.org>
References: <20201109175923.445945-1-maz@kernel.org>
MIME-Version: 1.0
X-SA-Exim-Connect-IP: 62.31.163.78
X-SA-Exim-Rcpt-To: linux-arm-kernel@lists.infradead.org,
 kvmarm@lists.cs.columbia.edu, kvm@vger.kernel.org, james.morse@arm.com,
 julien.thierry.kdev@gmail.com, suzuki.poulose@arm.com,
 alexandru.elisei@arm.com, ascull@google.com, will@kernel.org,
 qperret@google.com, ndesaulniers@google.com, dbrazdil@google.com,
 kernel-team@android.com
X-SA-Exim-Mail-From: maz@kernel.org
X-SA-Exim-Scanned: No (on disco-boy.misterjones.org);
 SAEximRunCond expanded to false
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Directly using the kimage_voffset variable is fine for now, but
will become more problematic as we start distrusting EL1.

Instead, patch the kimage_voffset into the HYP text, ensuring
we don't have to load an untrusted value later on.

Signed-off-by: Marc Zyngier <maz@kernel.org>
---
 arch/arm64/include/asm/kvm_mmu.h | 22 ++++++++++++++++++++++
 arch/arm64/kernel/image-vars.h   |  4 +---
 arch/arm64/kvm/hyp/nvhe/host.S   |  5 +----
 arch/arm64/kvm/va_layout.c       |  6 ++++++
 4 files changed, 30 insertions(+), 7 deletions(-)

```
#### [RFC PATCH v5 1/8] update_headers: Sync-up ABI headers with Linux-5.10-rc3
##### From: Anup Patel <anup.patel@wdc.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Anup Patel <Anup.Patel@wdc.com>
X-Patchwork-Id: 11891281
Return-Path: <SRS0=zqVv=EP=vger.kernel.org=kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-12.7 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_PATCH,MAILING_LIST_MULTI,
	MSGID_FROM_MTA_HEADER,SIGNED_OFF_BY,SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED,
	USER_AGENT_GIT autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 22E72C4741F
	for <kvm@archiver.kernel.org>; Mon,  9 Nov 2020 11:37:44 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id B135420731
	for <kvm@archiver.kernel.org>; Mon,  9 Nov 2020 11:37:43 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=fail reason="signature verification failed" (2048-bit key)
 header.d=wdc.com header.i=@wdc.com header.b="e4xiXcQ3";
	dkim=pass (1024-bit key) header.d=sharedspace.onmicrosoft.com
 header.i=@sharedspace.onmicrosoft.com header.b="wKzdXx2N"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729681AbgKILhm (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Mon, 9 Nov 2020 06:37:42 -0500
Received: from esa4.hgst.iphmx.com ([216.71.154.42]:38405 "EHLO
        esa4.hgst.iphmx.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1727826AbgKILhl (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 9 Nov 2020 06:37:41 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=simple/simple;
  d=wdc.com; i=@wdc.com; q=dns/txt; s=dkim.wdc.com;
  t=1604921861; x=1636457861;
  h=from:to:cc:subject:date:message-id:in-reply-to:
   references:content-transfer-encoding:mime-version;
  bh=PeAzD5zw4mHq0qHyUvIqrVOZmGhmKRkPqxi8NXc0haM=;
  b=e4xiXcQ32oR+0EJWqYg9UERp6QdzE7ijiwbKlBp/PUi2j1Sxy2ftBS5T
   M+Gy2JOYgEeOjSikzyQ//VlFDw3ucicsnxPJB2i6Y1lgl4clFXgF2TEXR
   1yyzc7yUURm52wpbSMfOl65YtUuKC4/d5K4rrgQ4xES/7CVoeA+FTxuRD
   6N+EcwXknCHVzl6hIiLT+JL4QDU091L1lR+jgm+jf7PMZrJYSBnARqpFX
   vcJSgO7WCl1RTPPptaQIZpXmGKGBFhgGKy/HvAK8A5KCsdFPcqOqgMY4B
   YcsOeV2dF7vhW/y7v0dizR4GJXuXVk33fNrSNhm5u7IwfbjlwRzye1kJK
   w==;
IronPort-SDR: 
 TRgD1oCoLHupdOfnqY0bIJYIhSkqCeAQtQLleCbwUBnJ4stL3AcO0XEkuzx+aIlZchbTt5vgOx
 ENgCnvnDNbfNXz0hN5mYIv2UWWzDFdDPvK4MPCs+mJquWaCFA7ZD4nrfv5DVtTbW8sNuvCJb8u
 BqHQWqpOd2cHdYlU/QiKvU7pOUg3miLbPoGYoADbyJ9/3BRWEv2Vx5LMkT3EOzZWwxEOhur6Dl
 Ag4Vi3MTDelRFViApQTD5Q4txLnTyXikknrDOf5faj3Kn8BURZhIyw99ZXJR4x8imUcZwbh0pq
 xRQ=
X-IronPort-AV: E=Sophos;i="5.77,463,1596470400";
   d="scan'208";a="152081216"
Received: from mail-bn8nam08lp2049.outbound.protection.outlook.com (HELO
 NAM04-BN8-obe.outbound.protection.outlook.com) ([104.47.74.49])
  by ob1.hgst.iphmx.com with ESMTP; 09 Nov 2020 19:37:40 +0800
ARC-Seal: i=1; a=rsa-sha256; s=arcselector9901; d=microsoft.com; cv=none;
 b=lIoQZjpg2B6P/FAijbTEq1kx0zJMs+g+xnLvcquO/soK3IAIPI1s+KPX4h+/1jDMWJa/Yl+ECtTdwGylDt+oPq+Qpzn2XwvVPxdcJYWfBqQWVCxY1jM1nY3407CcE+EmomP/75LPP+8molMGCRyBPTQIkAYdWVndCiFkEQo/dNBJIMfdqMJKvF0cWVxW8lWehPAeA69YMKDeoJ1V1DTraBpQZr7q0ehi4IXkPnaOcP6v4RWs4NIkT6Gw2EvZ1NtdXaiT2PXJDux2/0iH6zaVePyP3kjsOpP3HmLAvpLAV6h2na+WzECX9L1pXFC9nDoEC32xhRSQscDCujjMb+CBcA==
ARC-Message-Signature: i=1; a=rsa-sha256; c=relaxed/relaxed; d=microsoft.com;
 s=arcselector9901;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=WJ5du2pZUuWBNZQ6Yx1nA7mPeQlziEbs2USmtUmTW98=;
 b=OGF2Yk06/4rOYlI3L3gnyrwZovMkjyTEesDCtHilZjoLMKWYCbxeR9sqOi8kZsObkJscNZlKEwxvqwN2SkewxgnrEpQcEvDwIgsLv7mGm/fxJ6FCCOgOJ/9KrZwYYmUrJ1b9CZ/fTyx+V4pLTbtV1b/Xf14iM81dhrqv9QJG7tD2xeCS9CHEBhLk6PPuBj2lezyFES6f1DMouLL59Z08oZxhZ0glFYovfHA8f194vhkXzK+Sf7H4L0I0oj4xHHYRdIS5fDryNXTmiK0736E46eHG8ezccDYbkSdK2kovgnYuObjTPWpIrSu+aUTdVPhIke+uPkUjsaD5Z+QXivYLRQ==
ARC-Authentication-Results: i=1; mx.microsoft.com 1; spf=pass
 smtp.mailfrom=wdc.com; dmarc=pass action=none header.from=wdc.com; dkim=pass
 header.d=wdc.com; arc=none
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
 d=sharedspace.onmicrosoft.com; s=selector2-sharedspace-onmicrosoft-com;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=WJ5du2pZUuWBNZQ6Yx1nA7mPeQlziEbs2USmtUmTW98=;
 b=wKzdXx2N3dhB93/K4VDoAYEBDDCe0skTD6QKo69/xM3J5LXNmSR7gk9IVacrYhGKDGaulwwgxmAIgqa88IAODtmd5DCf/k3CMvyjlR21HL14GDUHl+gH9FcZKhvPeIS+UIlof6iIXLzbkO7+BX8PWIRKNskYYrv4MOxoh+ulK+s=
Authentication-Results: kernel.org; dkim=none (message not signed)
 header.d=none;kernel.org; dmarc=none action=none header.from=wdc.com;
Received: from DM6PR04MB6201.namprd04.prod.outlook.com (2603:10b6:5:127::32)
 by DM6PR04MB3866.namprd04.prod.outlook.com (2603:10b6:5:ad::19) with
 Microsoft SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.3541.21; Mon, 9 Nov
 2020 11:37:38 +0000
Received: from DM6PR04MB6201.namprd04.prod.outlook.com
 ([fe80::d035:e2c6:c11:51dd]) by DM6PR04MB6201.namprd04.prod.outlook.com
 ([fe80::d035:e2c6:c11:51dd%6]) with mapi id 15.20.3541.025; Mon, 9 Nov 2020
 11:37:38 +0000
From: Anup Patel <anup.patel@wdc.com>
To: Will Deacon <will@kernel.org>
Cc: Paolo Bonzini <pbonzini@redhat.com>,
        Atish Patra <atish.patra@wdc.com>,
        Alistair Francis <Alistair.Francis@wdc.com>,
        Anup Patel <anup@brainfault.org>, kvm@vger.kernel.org,
        kvm-riscv@lists.infradead.org, Anup Patel <anup.patel@wdc.com>
Subject: [RFC PATCH v5 1/8] update_headers: Sync-up ABI headers with
 Linux-5.10-rc3
Date: Mon,  9 Nov 2020 17:06:48 +0530
Message-Id: <20201109113655.3733700-2-anup.patel@wdc.com>
X-Mailer: git-send-email 2.25.1
In-Reply-To: <20201109113655.3733700-1-anup.patel@wdc.com>
References: <20201109113655.3733700-1-anup.patel@wdc.com>
X-Originating-IP: [122.171.188.68]
X-ClientProxiedBy: MA1PR01CA0094.INDPRD01.PROD.OUTLOOK.COM (2603:1096:a00::34)
 To DM6PR04MB6201.namprd04.prod.outlook.com (2603:10b6:5:127::32)
MIME-Version: 1.0
X-MS-Exchange-MessageSentRepresentingType: 1
Received: from wdc.com (122.171.188.68) by
 MA1PR01CA0094.INDPRD01.PROD.OUTLOOK.COM (2603:1096:a00::34) with Microsoft
 SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.3541.21 via Frontend
 Transport; Mon, 9 Nov 2020 11:37:35 +0000
X-MS-PublicTrafficType: Email
X-MS-Office365-Filtering-HT: Tenant
X-MS-Office365-Filtering-Correlation-Id: 329c9385-b958-4ff6-87be-08d884a3dc5b
X-MS-TrafficTypeDiagnostic: DM6PR04MB3866:
X-MS-Exchange-Transport-Forked: True
X-Microsoft-Antispam-PRVS: 
 <DM6PR04MB38663863D7023FCB484A55308DEA0@DM6PR04MB3866.namprd04.prod.outlook.com>
WDCIPOUTBOUND: EOP-TRUE
X-MS-Oob-TLC-OOBClassifiers: OLM:3631;
X-MS-Exchange-SenderADCheck: 1
X-Microsoft-Antispam: BCL:0;
X-Microsoft-Antispam-Message-Info: 
 BJTWCzklAPXCmhdCkP/q3uZF3Wzw0WGxGTgNZay/BfW2Scgo7jVDk9qkq58ThxC6lWDvIzobVZBpcOqlkiSbbZP6UF8BmFcff0jB/MZr2riUOz58oo8sHmTRUgL2nxUjF8Ie+KpJQ7Dj1NrdaHVrOEq1dOW8Z+fiLN1dEH9l1XUyPsj7eXnOxddXIENYpDqUq83yi7m80oAq2tPsTM1F1qs/UGqi+799xuux4Q83SoMsSdEsL7r395DLP1lWS3LXyP+Hgtt3Acx5Ru5q13mk6q3BxraEMwoeJDIDsRM+DqJfvMH70i91q4JPDrRbfiqy
X-Forefront-Antispam-Report: 
 CIP:255.255.255.255;CTRY:;LANG:en;SCL:1;SRV:;IPV:NLI;SFV:NSPM;H:DM6PR04MB6201.namprd04.prod.outlook.com;PTR:;CAT:NONE;SFS:(4636009)(366004)(346002)(396003)(136003)(39860400002)(376002)(55016002)(83380400001)(6916009)(1076003)(44832011)(16526019)(186003)(316002)(26005)(8676002)(54906003)(5660300002)(52116002)(7696005)(956004)(30864003)(2616005)(478600001)(66476007)(66556008)(4326008)(66946007)(6666004)(2906002)(36756003)(86362001)(8886007)(8936002);DIR:OUT;SFP:1102;
X-MS-Exchange-AntiSpam-MessageData: 
 MpvAuSKZCFaDqvz5Sf1B/yrj/quPD+pwca/plQH6SjNHtOmj95bZo6Gkq8t3Qk2fM41oKUNHfx/E2cCbeYjX5PO2GDtMqfo728labnj8Gd8BmoUrNaK2bmwQSeN5oz4c11z7bJPVc7+wVq8D8ib89Obo9y/HsjThljcco83fPoXZyXPT14ifkh3wE7K+VsZNPu0zt5BYdw3UlnnyK4AtxvkrXCZpZHDilAoxozZT0xaDJwflGrT/7XLIJuRyPaGsexxhzc+76QqBFeLqsgtD8PsiyUYaU3w64pqmeoLckMmF9iExYscMPm6Z6dNWXGIYNhnN9gn3+UlygjICzMGyoaQWgsBJfEQE2+6CZiB3xMB2Hg79woSItbwdMgTtXt+QtQoe8ft04V8SdyCPn//lky2wdqutScUbwXC4+ZqE0NAk28Nmofs81e3lplUYkQCDNIB3y6UqRpxRr+o2UJ9Fjj1qxAnrWVm3QgLyTzeht3zrap7+C+Lt17IsRQG91i7EZ8jKG+L89n7brpCqBpEPrYbZVA21wT5Aan6ONRiP8+aTY/kDuWVYE0vtXPyRLedRkAjBr91tyPPtKqNeTEkqZ5I/9r8xkbvdHtaWT+2Iu6PxrrynzitTG58J34GP6Urf3dNtr0OcBMH7eNjqeD95/A==
X-OriginatorOrg: wdc.com
X-MS-Exchange-CrossTenant-Network-Message-Id: 
 329c9385-b958-4ff6-87be-08d884a3dc5b
X-MS-Exchange-CrossTenant-AuthSource: DM6PR04MB6201.namprd04.prod.outlook.com
X-MS-Exchange-CrossTenant-AuthAs: Internal
X-MS-Exchange-CrossTenant-OriginalArrivalTime: 09 Nov 2020 11:37:38.8234
 (UTC)
X-MS-Exchange-CrossTenant-FromEntityHeader: Hosted
X-MS-Exchange-CrossTenant-Id: b61c8803-16f3-4c35-9b17-6f65f441df86
X-MS-Exchange-CrossTenant-MailboxType: HOSTED
X-MS-Exchange-CrossTenant-UserPrincipalName: 
 1550gDb0rRSp5sMZWNge0jO+WVVvmwiwq/b6LNPlBt4/zduOP4ojPAtu23OrA3bni7aRSx5Olw/3wNXnjWtcZg==
X-MS-Exchange-Transport-CrossTenantHeadersStamped: DM6PR04MB3866
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

We sync-up all ABI headers with Linux-5.10-rc3 so that RISC-V
specfic changes in include/linux/kvm.h are available.

Signed-off-by: Anup Patel <anup.patel@wdc.com>
---
 arm/aarch64/include/asm/kvm.h |  46 +++++++++++--
 include/linux/kvm.h           | 124 ++++++++++++++++++++++++++++++++--
 powerpc/include/asm/kvm.h     |   8 +++
 x86/include/asm/kvm.h         |  42 +++++++++++-
 4 files changed, 209 insertions(+), 11 deletions(-)

```
#### [PATCH v3 01/34] x86/cpu: Add VM page flush MSR availablility as a CPUID feature
##### From: Tom Lendacky <thomas.lendacky@amd.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Tom Lendacky <thomas.lendacky@amd.com>
X-Patchwork-Id: 11892681
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-12.7 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_PATCH,MAILING_LIST_MULTI,
	MSGID_FROM_MTA_HEADER,SIGNED_OFF_BY,SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED,
	USER_AGENT_GIT autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 465D5C55ABD
	for <kvm@archiver.kernel.org>; Mon,  9 Nov 2020 22:26:30 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id DFD6720789
	for <kvm@archiver.kernel.org>; Mon,  9 Nov 2020 22:26:29 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=amdcloud.onmicrosoft.com
 header.i=@amdcloud.onmicrosoft.com header.b="sEsUcBac"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1731267AbgKIW01 (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Mon, 9 Nov 2020 17:26:27 -0500
Received: from mail-bn8nam12on2045.outbound.protection.outlook.com
 ([40.107.237.45]:49248
        "EHLO NAM12-BN8-obe.outbound.protection.outlook.com"
        rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org with ESMTP
        id S1729874AbgKIW00 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 9 Nov 2020 17:26:26 -0500
ARC-Seal: i=1; a=rsa-sha256; s=arcselector9901; d=microsoft.com; cv=none;
 b=etuSdj4/ne9m54oG1dw48Vdfgr8+LudBx9hIITqwJrA6o5/tlhBj/DKd81Kq7/tUESFnp3spezGyFc00jpx01JG7o0WXjmeKL63PFGHgytgLx8pBqTRwBNu3MJWbuOyM3BRCJYlyJ/ER+ubbI9SebjFi+o9ajWho0XGfzOfMjQo2LA9mLOGZQLiusAnEXW7FIy5txEZgoKMwFnhh2/+wNKcr98a0bV6ydej9VgesScohPHaJC/US2XZwzrVNFT10iOOeua6m3nxXGtkNG4YTAWcKgFGwENZ5vKIY3TkPIaGAuVXso5DGR0Dns3Mm2RtWIaPmnybTci8zvZwvkEZT/A==
ARC-Message-Signature: i=1; a=rsa-sha256; c=relaxed/relaxed; d=microsoft.com;
 s=arcselector9901;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=jIDSQVwBhceTkXrKGCJrfTL5U9e5STc9iqm9UuU3694=;
 b=Bc8W+D64NcIbCY6UYiM5gZOGJguSwi6gFamiZaR/vK3THa+kY99xlDKTNt/Q6+VjPpeDzDFGXjTA+zvV2oFPIpP35p66I1wt15xffXI4/DljfWdIfZ1oVFZq4jcvNdzuc2oXXliv8R7ZW8pk2LxrP++PbSSjC6w89byG2nMSqi2RQZ+VFjRqPwPKpahGiB8A+a3RtaWRFZqGk5NbjfOSvAnjJZnerPtBK4Ca3eFRbREtPXaLtoOBdy++/E/y1K55fcIu0Svtg7t1RH3USxVn29bzYhrIPniddJL/JHcjGsLzkrjneNAj7feff/k/t7Tc1iI6SEb4YOixgmDf0UYcEA==
ARC-Authentication-Results: i=1; mx.microsoft.com 1; spf=pass
 smtp.mailfrom=amd.com; dmarc=pass action=none header.from=amd.com; dkim=pass
 header.d=amd.com; arc=none
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
 d=amdcloud.onmicrosoft.com; s=selector2-amdcloud-onmicrosoft-com;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=jIDSQVwBhceTkXrKGCJrfTL5U9e5STc9iqm9UuU3694=;
 b=sEsUcBacp+56QrbSCo405BDe5GJI65q27/K82zIm9OBlHPFEjxoHkHrOVI0nHydG1MXIBPbriAHX09d86K+NdeYH+vb3XNbrajYoQwDH2376ckXA38uj0J4r4h6gHQaA9GGef581q+OnD1WSGiex7A2w4pVq3gdkuug4vmlDuf0=
Authentication-Results: vger.kernel.org; dkim=none (message not signed)
 header.d=none;vger.kernel.org; dmarc=none action=none header.from=amd.com;
Received: from DM5PR12MB1355.namprd12.prod.outlook.com (2603:10b6:3:6e::7) by
 DM6PR12MB4058.namprd12.prod.outlook.com (2603:10b6:5:21d::16) with Microsoft
 SMTP Server (version=TLS1_2, cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id
 15.20.3541.21; Mon, 9 Nov 2020 22:26:23 +0000
Received: from DM5PR12MB1355.namprd12.prod.outlook.com
 ([fe80::e442:c052:8a2c:5fba]) by DM5PR12MB1355.namprd12.prod.outlook.com
 ([fe80::e442:c052:8a2c:5fba%6]) with mapi id 15.20.3499.032; Mon, 9 Nov 2020
 22:26:23 +0000
From: Tom Lendacky <thomas.lendacky@amd.com>
To: kvm@vger.kernel.org, linux-kernel@vger.kernel.org, x86@kernel.org
Cc: Paolo Bonzini <pbonzini@redhat.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Borislav Petkov <bp@alien8.de>, Ingo Molnar <mingo@redhat.com>,
        Thomas Gleixner <tglx@linutronix.de>,
        Brijesh Singh <brijesh.singh@amd.com>
Subject: [PATCH v3 01/34] x86/cpu: Add VM page flush MSR availablility as a
 CPUID feature
Date: Mon,  9 Nov 2020 16:25:27 -0600
Message-Id: 
 <da22668e810bcfb922349b5ef7c3df53424e48fc.1604960760.git.thomas.lendacky@amd.com>
X-Mailer: git-send-email 2.28.0
In-Reply-To: <cover.1604960760.git.thomas.lendacky@amd.com>
References: <cover.1604960760.git.thomas.lendacky@amd.com>
X-Originating-IP: [165.204.77.1]
X-ClientProxiedBy: SN2PR01CA0035.prod.exchangelabs.com (2603:10b6:804:2::45)
 To DM5PR12MB1355.namprd12.prod.outlook.com (2603:10b6:3:6e::7)
MIME-Version: 1.0
X-MS-Exchange-MessageSentRepresentingType: 1
Received: from tlendack-t1.amd.com (165.204.77.1) by
 SN2PR01CA0035.prod.exchangelabs.com (2603:10b6:804:2::45) with Microsoft SMTP
 Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.3541.21 via Frontend
 Transport; Mon, 9 Nov 2020 22:26:22 +0000
X-MS-PublicTrafficType: Email
X-MS-Office365-Filtering-HT: Tenant
X-MS-Office365-Filtering-Correlation-Id: 2ba750a5-b352-4375-4587-08d884fe7d57
X-MS-TrafficTypeDiagnostic: DM6PR12MB4058:
X-MS-Exchange-Transport-Forked: True
X-Microsoft-Antispam-PRVS: 
 <DM6PR12MB4058E16134B9F39A78F06752ECEA0@DM6PR12MB4058.namprd12.prod.outlook.com>
X-MS-Oob-TLC-OOBClassifiers: OLM:7219;
X-MS-Exchange-SenderADCheck: 1
X-Microsoft-Antispam: BCL:0;
X-Microsoft-Antispam-Message-Info: 
 ajOFnrpiWGv0GHJaU7IUK1iK1O8hqj8bNphC2/g8mu3SSkyNHAFgzhz0/XqIraYWwDINYETcbLkbI2jkVe9s+6U3wCqCxuCeY7MsoUnnc8KE1k3FtDVvUnCIb5cSLcbRReTSHeuzuC2Vb4i/4OYv6X9yyYr8iSZQX37dEzt10vvARpdSxHmqyV42GROaEOK6Li8ujXqjG0IQJugiPkGzu3SQFLKq6RHYCpIfHQbGe7ayQzOnNrmcU9N7FOYebMG8MZ1Iifza4eWAC3tErQc6YWf906BxllHgBhZrwretvyJydKQqwTprAP2Xhi39i8I+5TELqMmoxiyBBhiAb/D6xA==
X-Forefront-Antispam-Report: 
 CIP:255.255.255.255;CTRY:;LANG:en;SCL:1;SRV:;IPV:NLI;SFV:NSPM;H:DM5PR12MB1355.namprd12.prod.outlook.com;PTR:;CAT:NONE;SFS:(4636009)(346002)(376002)(396003)(136003)(39860400002)(366004)(2616005)(956004)(8676002)(16526019)(54906003)(316002)(86362001)(4326008)(26005)(8936002)(7416002)(36756003)(5660300002)(52116002)(7696005)(66556008)(66476007)(66946007)(6486002)(478600001)(2906002)(186003);DIR:OUT;SFP:1101;
X-MS-Exchange-AntiSpam-MessageData: 
 JituLAE1SGjntN4YVAnOJdRxeYPJm6GZhZY5utty3gmacC7612a5DZuLXSho9n8ab9i8m0suVdXBshtIPVoCYwWMRpfZQUKdtsMweOiuUVP9HBPv2Ng+vOGZtGcufFMzSETQewgu7p/TRQBy3lG32sJYS7pf84mQl8g/VSYWc+nWO/feE9LyQiASuAyugtO+4GqbeOYhDCLFNJJebUya6x3xeL2C5SL88trjzUaB/MLruHhdz6nlhbNYiATIyy51QRpth/5Msov2vy31rOaECQK9AksTHWK2DW1IJyNryeZ/34wjRm1kPFnJVZmHHEVi5WP8cVGecJ3EzTk/b1YiG+GVKaKZTkZJiw8JziXKL3EqkIWEotYglLzo3hH5LKSJFOa9Uy5oienR5qZ8Ajq+sS2OOeQtGC0rryAG5/cL1sMMU5epBaYWAxyW06NmfX640g/MPOXdDnMFZFak7lqHAXgf8UtGOsh4dCW5/hSQBSErzzDNOmVpAesgQgjqxBwiQowMEJRqlqKObelzxdSNbRyfmQc3sm01uuSiFP5v7OHoYp0sBVFVEt49sF8b4yzvFX30mfqAFLvGSiIFZILC4YyBKqmSLwPZAHdDGtGVMEEqraXQvX+fTuPWzgYCiBsEyPy1NT0dSuN7Ew2wTB/6kQ==
X-OriginatorOrg: amd.com
X-MS-Exchange-CrossTenant-Network-Message-Id: 
 2ba750a5-b352-4375-4587-08d884fe7d57
X-MS-Exchange-CrossTenant-AuthSource: DM5PR12MB1355.namprd12.prod.outlook.com
X-MS-Exchange-CrossTenant-AuthAs: Internal
X-MS-Exchange-CrossTenant-OriginalArrivalTime: 09 Nov 2020 22:26:23.4465
 (UTC)
X-MS-Exchange-CrossTenant-FromEntityHeader: Hosted
X-MS-Exchange-CrossTenant-Id: 3dd8961f-e488-4e60-8e11-a82d994e183d
X-MS-Exchange-CrossTenant-MailboxType: HOSTED
X-MS-Exchange-CrossTenant-UserPrincipalName: 
 6xG7LUVHxDz9mq0nSftR7F7dxvZ5ner6zA77KZ80+bPdIOa231ACn3JWtU6wiR0wh0EBH1tsYylt6hhTK6CU5g==
X-MS-Exchange-Transport-CrossTenantHeadersStamped: DM6PR12MB4058
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Tom Lendacky <thomas.lendacky@amd.com>

On systems that do not have hardware enforced cache coherency between
encrypted and unencrypted mappings of the same physical page, the
hypervisor can use the VM page flush MSR (0xc001011e) to flush the cache
contents of an SEV guest page. When a small number of pages are being
flushed, this can be used in place of issuing a WBINVD across all CPUs.

CPUID 0x8000001f_eax[2] is used to determine if the VM page flush MSR is
available. Add a CPUID feature to indicate it is supported and define the
MSR.

Signed-off-by: Tom Lendacky <thomas.lendacky@amd.com>
---
 arch/x86/include/asm/cpufeatures.h | 1 +
 arch/x86/include/asm/msr-index.h   | 1 +
 arch/x86/kernel/cpu/scattered.c    | 1 +
 3 files changed, 3 insertions(+)

```
#### [PATCH v3 1/9] mm: slab: clarify krealloc()'s behavior with __GFP_ZERO
##### From: Bartosz Golaszewski <brgl@bgdev.pl>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Bartosz Golaszewski <brgl@bgdev.pl>
X-Patchwork-Id: 11891091
Return-Path: <SRS0=zqVv=EP=vger.kernel.org=kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-12.8 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_PATCH,MAILING_LIST_MULTI,
	SIGNED_OFF_BY,SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED,USER_AGENT_GIT
	autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 10F6BC56201
	for <kvm@archiver.kernel.org>; Mon,  9 Nov 2020 11:08:28 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id ACBD420719
	for <kvm@archiver.kernel.org>; Mon,  9 Nov 2020 11:08:27 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=bgdev-pl.20150623.gappssmtp.com
 header.i=@bgdev-pl.20150623.gappssmtp.com header.b="SLmwWdYm"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729537AbgKILHE (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Mon, 9 Nov 2020 06:07:04 -0500
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:59498 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1729515AbgKILHD (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 9 Nov 2020 06:07:03 -0500
Received: from mail-wr1-x442.google.com (mail-wr1-x442.google.com
 [IPv6:2a00:1450:4864:20::442])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 73CDEC0617A6
        for <kvm@vger.kernel.org>; Mon,  9 Nov 2020 03:07:02 -0800 (PST)
Received: by mail-wr1-x442.google.com with SMTP id 33so8211828wrl.7
        for <kvm@vger.kernel.org>; Mon, 09 Nov 2020 03:07:02 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=bgdev-pl.20150623.gappssmtp.com; s=20150623;
        h=from:to:cc:subject:date:message-id:in-reply-to:references
         :mime-version:content-transfer-encoding;
        bh=2uLK4LNo7fJGEwA0NXfYaAQzvkTW8/WkGHuVu61FcZ4=;
        b=SLmwWdYmA2Su0OyL+219YDZzeVXOkzpy5gortE6aVnwng+6cHrJzhAQJzNByqcPbPZ
         isbE6V3Lb9JgstbUlm/PZvCpNxelIDnwHLTINtWIzMAUAJP+6YLk/AWf+cW33RVJOvLq
         4EQlOOLu8zd+gVrxvr0w9485FxLsZ4uiV1jlwgDMS4E7kDkszYjvid4w0z806pFvA1dO
         U+nHioEgRrLmfLyR8tH/H/Ge3+qH76H09ubPywZEg/u4KcGzZ6YzgnyKXZKxxyWIo1cW
         FT3Tuwvxb43JhyG0QmKnG/8uRrjp2S/bO4jEisldpzuA8EOA5eJuEswwYg/l6KV0K70j
         EAjQ==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:in-reply-to
         :references:mime-version:content-transfer-encoding;
        bh=2uLK4LNo7fJGEwA0NXfYaAQzvkTW8/WkGHuVu61FcZ4=;
        b=jrsxU2XvzQ1l4mRDgmVnQZ9+cdQ4CzoD1UvM2QH3p3Z3TN+kOU5xV1r8GxlR/zeDbi
         mnzHqqcaJlFO0Q7NGz4cHvWaozpsq92QWZuBdOKzO0a2M+Ji/SF08SAAkIToK47H5foZ
         kjFq2C794/71wruXoFjad5OQg+IEAwtAMwGbmjbqE7yomvEtv4KQwxbIXYmNQ0o3wE+N
         d53gmuX09EhYoadyNmfwfLHGtN9Y98WowoO4lJVoJUif5/nSqfM5MLHcSFo9GEAAlOxz
         nmC6J85HaCbk/kjeSX2z7Jleqstei/9OTVX2SAVC04fElfyA/7mK2QJeGdxnic1p574N
         9vhw==
X-Gm-Message-State: AOAM533EQI4iUeNjR4F2xhL+TA/IyaTaRhm61+couRhQRp4E0cmIDXn3
        tS20wqOmx0ZuOYJtzLOm73lyBw==
X-Google-Smtp-Source: 
 ABdhPJwC1VmwvlzIaWje0LLMyGfNJlg7DPW07nQhl2YWyOW+KS6oIpzkSUqvI/A14QOWWdg2F+P+tA==
X-Received: by 2002:adf:9b98:: with SMTP id d24mr16961027wrc.17.1604920021208;
        Mon, 09 Nov 2020 03:07:01 -0800 (PST)
Received: from localhost.localdomain (lfbn-nic-1-190-206.w2-15.abo.wanadoo.fr.
 [2.15.39.206])
        by smtp.gmail.com with ESMTPSA id
 d3sm12815582wre.91.2020.11.09.03.06.59
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Mon, 09 Nov 2020 03:07:00 -0800 (PST)
From: Bartosz Golaszewski <brgl@bgdev.pl>
To: Andy Shevchenko <andriy.shevchenko@linux.intel.com>,
 Sumit Semwal <sumit.semwal@linaro.org>,
 Gustavo Padovan <gustavo@padovan.org>,
 =?utf-8?q?Christian_K=C3=B6nig?= <christian.koenig@amd.com>,
 Mauro Carvalho Chehab <mchehab@kernel.org>, Borislav Petkov <bp@alien8.de>,
 Tony Luck <tony.luck@intel.com>, James Morse <james.morse@arm.com>,
 Robert Richter <rric@kernel.org>,
 Maarten Lankhorst <maarten.lankhorst@linux.intel.com>,
 Maxime Ripard <mripard@kernel.org>, Thomas Zimmermann <tzimmermann@suse.de>,
 David Airlie <airlied@linux.ie>, Daniel Vetter <daniel@ffwll.ch>,
 Alexander Shishkin <alexander.shishkin@linux.intel.com>,
 Linus Walleij <linus.walleij@linaro.org>,
 "Michael S . Tsirkin" <mst@redhat.com>, Jason Wang <jasowang@redhat.com>,
 Christoph Lameter <cl@linux.com>, Pekka Enberg <penberg@kernel.org>,
 David Rientjes <rientjes@google.com>, Joonsoo Kim <iamjoonsoo.kim@lge.com>,
 Andrew Morton <akpm@linux-foundation.org>, Jaroslav Kysela <perex@perex.cz>,
 Takashi Iwai <tiwai@suse.com>
Cc: linux-media@vger.kernel.org, dri-devel@lists.freedesktop.org,
        linaro-mm-sig@lists.linaro.org, linux-kernel@vger.kernel.org,
        linux-edac@vger.kernel.org, linux-gpio@vger.kernel.org,
        kvm@vger.kernel.org, virtualization@lists.linux-foundation.org,
        netdev@vger.kernel.org, linux-mm@kvack.org,
        alsa-devel@alsa-project.org,
        Bartosz Golaszewski <bgolaszewski@baylibre.com>
Subject: [PATCH v3 1/9] mm: slab: clarify krealloc()'s behavior with
 __GFP_ZERO
Date: Mon,  9 Nov 2020 12:06:46 +0100
Message-Id: <20201109110654.12547-2-brgl@bgdev.pl>
X-Mailer: git-send-email 2.29.1
In-Reply-To: <20201109110654.12547-1-brgl@bgdev.pl>
References: <20201109110654.12547-1-brgl@bgdev.pl>
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Bartosz Golaszewski <bgolaszewski@baylibre.com>

__GFP_ZERO is ignored by krealloc() (unless we fall-back to kmalloc()
path, in which case it's honored). Point that out in the kerneldoc.

Signed-off-by: Bartosz Golaszewski <bgolaszewski@baylibre.com>
---
 mm/slab_common.c | 6 +++---
 1 file changed, 3 insertions(+), 3 deletions(-)

```
#### [PATCH v2 1/5] KVM: arm64: Add kimg_hyp_va() helper
##### From: Marc Zyngier <maz@kernel.org>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Marc Zyngier <maz@kernel.org>
X-Patchwork-Id: 11892145
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-13.1 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,INCLUDES_PATCH,MAILING_LIST_MULTI,
	SIGNED_OFF_BY,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT autolearn=ham
	autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 4502CC2D0A3
	for <kvm@archiver.kernel.org>; Mon,  9 Nov 2020 17:59:32 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id CB98B21D93
	for <kvm@archiver.kernel.org>; Mon,  9 Nov 2020 17:59:31 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=kernel.org header.i=@kernel.org
 header.b="FJbXiMxl"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1730080AbgKIR7b (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Mon, 9 Nov 2020 12:59:31 -0500
Received: from mail.kernel.org ([198.145.29.99]:47204 "EHLO mail.kernel.org"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1729973AbgKIR7a (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 9 Nov 2020 12:59:30 -0500
Received: from disco-boy.misterjones.org (disco-boy.misterjones.org
 [51.254.78.96])
        (using TLSv1.2 with cipher ECDHE-RSA-AES256-GCM-SHA384 (256/256 bits))
        (No client certificate requested)
        by mail.kernel.org (Postfix) with ESMTPSA id C129D2068D;
        Mon,  9 Nov 2020 17:59:29 +0000 (UTC)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple; d=kernel.org;
        s=default; t=1604944769;
        bh=PlmXh+r1X4pO3UYVHErEci+hw9LpEvNvwhS6IdOCN3s=;
        h=From:To:Cc:Subject:Date:In-Reply-To:References:From;
        b=FJbXiMxlDC+bMI/qjpViCxFKRw3yOKHOvnZs+t2y9fdEEcaPpk3XIg6HDPYt1vxsz
         7w5QOdxjME20ROoYobdFZ8PnZGmA1Dceq83NgDhDdXDNp9mkwy1yvZaW2Sq7Xu1vWK
         SXnjpVkdFmb9hSoHj/5Al7SUlK7/9MJpRcwBjVYc=
Received: from 78.163-31-62.static.virginmediabusiness.co.uk ([62.31.163.78]
 helo=why.lan)
        by disco-boy.misterjones.org with esmtpsa  (TLS1.3) tls
 TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384
        (Exim 4.94)
        (envelope-from <maz@kernel.org>)
        id 1kcBRv-009BQs-VE; Mon, 09 Nov 2020 17:59:28 +0000
From: Marc Zyngier <maz@kernel.org>
To: linux-arm-kernel@lists.infradead.org, kvmarm@lists.cs.columbia.edu,
        kvm@vger.kernel.org
Cc: James Morse <james.morse@arm.com>,
        Julien Thierry <julien.thierry.kdev@gmail.com>,
        Suzuki K Poulose <suzuki.poulose@arm.com>,
        Alexandru Elisei <alexandru.elisei@arm.com>,
        Andrew Scull <ascull@google.com>,
        Will Deacon <will@kernel.org>,
        Quentin Perret <qperret@google.com>, ndesaulniers@google.com,
        dbrazdil@google.com, kernel-team@android.com
Subject: [PATCH v2 1/5] KVM: arm64: Add kimg_hyp_va() helper
Date: Mon,  9 Nov 2020 17:59:19 +0000
Message-Id: <20201109175923.445945-2-maz@kernel.org>
X-Mailer: git-send-email 2.28.0
In-Reply-To: <20201109175923.445945-1-maz@kernel.org>
References: <20201109175923.445945-1-maz@kernel.org>
MIME-Version: 1.0
X-SA-Exim-Connect-IP: 62.31.163.78
X-SA-Exim-Rcpt-To: linux-arm-kernel@lists.infradead.org,
 kvmarm@lists.cs.columbia.edu, kvm@vger.kernel.org, james.morse@arm.com,
 julien.thierry.kdev@gmail.com, suzuki.poulose@arm.com,
 alexandru.elisei@arm.com, ascull@google.com, will@kernel.org,
 qperret@google.com, ndesaulniers@google.com, dbrazdil@google.com,
 kernel-team@android.com
X-SA-Exim-Mail-From: maz@kernel.org
X-SA-Exim-Scanned: No (on disco-boy.misterjones.org);
 SAEximRunCond expanded to false
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

KVM/arm64 is so far unable to deal with function pointers, as the compiler
will generate the kernel's runtime VA, and not the linear mapping address,
meaning that kern_hyp_va() will give the wrong result.

We so far have been able to use PC-relative addressing, but that's not
always easy to use, and prevents the implementation of things like
the mapping of an index to a pointer.

To allow this, provide a new helper that computes the required
translation from the kernel image to the HYP VA space.

Signed-off-by: Marc Zyngier <maz@kernel.org>
---
 arch/arm64/include/asm/kvm_mmu.h | 18 ++++++++++++
 arch/arm64/kvm/va_layout.c       | 50 ++++++++++++++++++++++++++++++++
 2 files changed, 68 insertions(+)

```
#### [PATCH] x86/mce: Check for hypervisor before enabling additional error logging
##### From: "Luck, Tony" <tony.luck@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Tony Luck <tony.luck@intel.com>
X-Patchwork-Id: 11892775
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-9.8 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_PATCH,MAILING_LIST_MULTI,SIGNED_OFF_BY,
	SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED autolearn=unavailable autolearn_force=no
	version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 13AFBC5517A
	for <kvm@archiver.kernel.org>; Mon,  9 Nov 2020 23:24:08 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id C64CA206ED
	for <kvm@archiver.kernel.org>; Mon,  9 Nov 2020 23:24:07 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1731355AbgKIXYF (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Mon, 9 Nov 2020 18:24:05 -0500
Received: from mga09.intel.com ([134.134.136.24]:7001 "EHLO mga09.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1729740AbgKIXYE (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 9 Nov 2020 18:24:04 -0500
IronPort-SDR: 
 ID0Hd7zq6ENP88mZc7V0tz9D0YDzA4YLVkszv6mgrxKfpJX+Js0e0v4Qy5pox5+D3lPx/5SCan
 PazxTL9ggC5Q==
X-IronPort-AV: E=McAfee;i="6000,8403,9800"; a="170038978"
X-IronPort-AV: E=Sophos;i="5.77,464,1596524400";
   d="scan'208";a="170038978"
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from orsmga004.jf.intel.com ([10.7.209.38])
  by orsmga102.jf.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 09 Nov 2020 15:24:03 -0800
IronPort-SDR: 
 GpZbytWzBTV4P7UoNJU0CtTmo7uvwa2hvA0jdHPZGeGaba7dR/GNinokcc8VgiKXTCs/iFFDHk
 g3eGxblBjDOQ==
X-IronPort-AV: E=Sophos;i="5.77,464,1596524400";
   d="scan'208";a="473180423"
Received: from agluck-desk2.sc.intel.com (HELO
 agluck-desk2.amr.corp.intel.com) ([10.3.52.68])
  by orsmga004-auth.jf.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 09 Nov 2020 15:24:03 -0800
Date: Mon, 9 Nov 2020 15:24:02 -0800
From: "Luck, Tony" <tony.luck@intel.com>
To: Borislav Petkov <bp@alien8.de>, Jim Mattson <jmattson@google.com>
Cc: Qian Cai <cai@redhat.com>,
        "linux-kernel@vger.kernel.org" <linux-kernel@vger.kernel.org>,
        "linux-tip-commits@vger.kernel.org"
        <linux-tip-commits@vger.kernel.org>, Boris Petkov <bp@alien8.de>,
        Borislav Petkov <bp@suse.de>, x86 <x86@kernel.org>,
        Paolo Bonzini <pbonzini@redhat.com>,
        "kvm@vger.kernel.org" <kvm@vger.kernel.org>
Subject: [PATCH] x86/mce: Check for hypervisor before enabling additional
 error logging
Message-ID: <20201109232402.GA25492@agluck-desk2.amr.corp.intel.com>
References: <20201030190807.GA13884@agluck-desk2.amr.corp.intel.com>
 <160431588828.397.16468104725047768957.tip-bot2@tip-bot2>
 <3f863634cd75824907e8ccf8164548c2ef036f20.camel@redhat.com>
 <bfc274fc27724ea39ecac1e7ac834ed8@intel.com>
 <CALMp9eTFaiYkTnVe8xKzg40E4nZ3rAOii0O06bTy0+oLNjyKhA@mail.gmail.com>
 <a22b5468e1c94906b72c4d8bc83c0f64@intel.com>
MIME-Version: 1.0
Content-Disposition: inline
In-Reply-To: <a22b5468e1c94906b72c4d8bc83c0f64@intel.com>
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Booting as a guest under KVM results in error messages about
unchecked MSR access:

[    6.814328][    T0] unchecked MSR access error: RDMSR from 0x17f at rIP: 0xffffffff84483f16 (mce_intel_feature_init+0x156/0x270)

because KVM doesn't provide emulation for random model specific registers.

Check for X86_FEATURE_HYPERVISOR and skip trying to enable the mode (a
guest shouldn't be concerned with corrected errors anyway).

Reported-by: Qian Cai <cai@redhat.com>
Fixes: 68299a42f842 ("x86/mce: Enable additional error logging on certain Intel CPUs")
Signed-off-by: Tony Luck <tony.luck@intel.com>
Nacked-by: Paolo Bonzini <pbonzini@redhat.com>
---
 arch/x86/kernel/cpu/mce/intel.c | 3 +++
 1 file changed, 3 insertions(+)

```
