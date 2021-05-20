#### [PATCH 02/10] docs: vcpu-requests.rst: fix reference for atomic ops
##### From: Mauro Carvalho Chehab <mchehab+huawei@kernel.org>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Mauro Carvalho Chehab <mchehab+huawei@kernel.org>
X-Patchwork-Id: 12266667
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-19.4 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED,USER_AGENT_GIT
	autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 6B973C433ED
	for <kvm@archiver.kernel.org>; Wed, 19 May 2021 08:51:58 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 4B44E61355
	for <kvm@archiver.kernel.org>; Wed, 19 May 2021 08:51:58 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1343943AbhESIxN (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Wed, 19 May 2021 04:53:13 -0400
Received: from mail.kernel.org ([198.145.29.99]:60288 "EHLO mail.kernel.org"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1343824AbhESIxL (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 19 May 2021 04:53:11 -0400
Received: by mail.kernel.org (Postfix) with ESMTPSA id 61AAE610CC;
        Wed, 19 May 2021 08:51:51 +0000 (UTC)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple; d=kernel.org;
        s=k20201202; t=1621414311;
        bh=H2xJFaGOtqmzr2+rgfc0d9kbWgFeN1e+g9wwRpKEzOU=;
        h=From:To:Cc:Subject:Date:In-Reply-To:References:From;
        b=pt+WA0+fV9R+WI3t2smfUI4i5eFl++NvT/52lMLfuC8CQSRc14L6dfXtrYz1s72Jc
         FqTusu+ZG9VaAC+0pVznHudjcyS6VIuuHzZRJFXv3O3BHZT7TpYQSJi48PutdiIEct
         XeSkNTauBx0UvChbXsAjiGQGCj1lNBMu4xCsnW/Imr9Cq+HOe2gxBZu4rda+HK5qDq
         EsVG/EVpDi8LWFEfx9RtqQUkETpCiJZBsSsW+++Vpl0o1OgZ5zF464DVWuIGdUkLHO
         if/pFsqmwElkFCrMxVdvyKNNXJJGT7OFTe1236OMcB3ZTw6gSPljsuq/PUgNimAy5G
         kzOeHLhvi0amw==
Received: by mail.kernel.org with local (Exim 4.94.2)
        (envelope-from <mchehab@kernel.org>)
        id 1ljHvh-007gY2-CM; Wed, 19 May 2021 10:51:49 +0200
From: Mauro Carvalho Chehab <mchehab+huawei@kernel.org>
To: Linux Doc Mailing List <linux-doc@vger.kernel.org>,
        Jonathan Corbet <corbet@lwn.net>
Cc: Mauro Carvalho Chehab <mchehab+huawei@kernel.org>,
        Paolo Bonzini <pbonzini@redhat.com>,
        Peter Zijlstra <peterz@infradead.org>, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org
Subject: [PATCH 02/10] docs: vcpu-requests.rst: fix reference for atomic ops
Date: Wed, 19 May 2021 10:51:39 +0200
Message-Id: 
 <703af756ac26a06c2185c05dfe6d902253f11161.1621413933.git.mchehab+huawei@kernel.org>
X-Mailer: git-send-email 2.31.1
In-Reply-To: <cover.1621413933.git.mchehab+huawei@kernel.org>
References: <cover.1621413933.git.mchehab+huawei@kernel.org>
MIME-Version: 1.0
Sender: Mauro Carvalho Chehab <mchehab@kernel.org>
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Changeset f0400a77ebdc ("atomic: Delete obsolete documentation")
got rid of atomic_ops.rst, pointing that this was superseded by
Documentation/atomic_*.txt.

Update its reference accordingly.

Fixes: f0400a77ebdc ("atomic: Delete obsolete documentation")
Signed-off-by: Mauro Carvalho Chehab <mchehab+huawei@kernel.org>
---
 Documentation/virt/kvm/vcpu-requests.rst | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
#### [PATCH v18 01/18] RISC-V: Add hypervisor extension related CSR defines
##### From: Anup Patel <anup.patel@wdc.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Anup Patel <Anup.Patel@wdc.com>
X-Patchwork-Id: 12266105
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.7 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,MSGID_FROM_MTA_HEADER,SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED,
	USER_AGENT_GIT autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id E32DCC433ED
	for <kvm@archiver.kernel.org>; Wed, 19 May 2021 03:36:26 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id CE55460FD8
	for <kvm@archiver.kernel.org>; Wed, 19 May 2021 03:36:26 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S237776AbhESDho (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 18 May 2021 23:37:44 -0400
Received: from esa2.hgst.iphmx.com ([68.232.143.124]:13857 "EHLO
        esa2.hgst.iphmx.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S237662AbhESDhn (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 18 May 2021 23:37:43 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=simple/simple;
  d=wdc.com; i=@wdc.com; q=dns/txt; s=dkim.wdc.com;
  t=1621395385; x=1652931385;
  h=from:to:cc:subject:date:message-id:in-reply-to:
   references:content-transfer-encoding:mime-version;
  bh=S2fFIWw5p5IOD0E/nP1OdlY0BHyCpMdiGuq37tgZXX4=;
  b=evkRufbDq8f+RbRjIBvydkOiwssIqa/NdyoYMFjils1wP89lzPPxAWkG
   WIEdrbxtRsuEO7r6GR+9v4RUbDwBLVL9W2rBxDhgF7Dq0CWmnG+oWbRIs
   YwH+z1F++koqeR/wlCEJKvML7s3FC2Rjgs495/anSO1wecY5SIvKmgFXr
   uJC9G7NUP1pWl5q8fnE2SGevQtHHsqYkdgUuwDsD4qaUWTeenzPcJMLbY
   h+uFnq160RX9gAQOfwxKO3EiA4XKHEelKJKoL48oQJcVJNnTZV6wZqLQi
   A6W2VbosTx4UoF+PS9DsNHbnqCiWIBxOJOx9aDYGpzd5vvFDHlngakvXN
   A==;
IronPort-SDR: 
 C9L6lpsfnc8g1r7whvxbo4JfOwO/J1/rKf56EQg2b3XeSLb04+xYBWg7f2buFw8MZkrxjQ0HHC
 COsmshYcRLEXrMDNb1kvCxDuVX6J61uJv0EY+xw8bYC5YX/E628HI7OqSfCXk8QRJRdkMvwMWZ
 d2ywAumL/T9tmcjDcE0aKNItOw/GUy5Wdd4kjj7Ebe+lC5PYmHWy4F+MJR7WwrNRr9jYhDydB+
 aYP04upUlIszIGY3uHbvvm9VTjHhm5POS9yo5HyloaFEKF1PFRePaRUr/+0xDwQRko/v78Z/+R
 q10=
X-IronPort-AV: E=Sophos;i="5.82,311,1613404800";
   d="scan'208";a="272597123"
Received: from mail-co1nam11lp2169.outbound.protection.outlook.com (HELO
 NAM11-CO1-obe.outbound.protection.outlook.com) ([104.47.56.169])
  by ob1.hgst.iphmx.com with ESMTP; 19 May 2021 11:36:24 +0800
ARC-Seal: i=1; a=rsa-sha256; s=arcselector9901; d=microsoft.com; cv=none;
 b=mzDNNqYXnUbmkKk0J7NYBNdHybMYx1lFOSyAiecbk+CkbgLiAiSygaC70NjxENrzp1cKfP3um3DMhyT/Ah13OA+rw40e/wqqkO/5nvLGgOJox+4Z0gj9cNR2ZAb9kH4n9+fSYuf+43Tj/LUwVB8wG9XfOtaz0oJ0UvySIVvZc7z8vAsm1Wloj9x8POZ+GYyyzfYEd4NI+ydOoAwnkTVsaWJRgfc2smqapjTkLtrvD1yW0LTOYIf5HzaS4YaHF63Q+YJMIoHF8rXslPyAhnNCH68ExT/+EsHzgk05ovLqG5rKc5G+rOZ/wKdo0SgmRN619CzWmEojuCth4S6uACdN4A==
ARC-Message-Signature: i=1; a=rsa-sha256; c=relaxed/relaxed; d=microsoft.com;
 s=arcselector9901;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=Sk8XpE13dIHDod3PMQVNO/6aEAf+gNs78hGIAdi/9cw=;
 b=S20f5K/sHEU4ca5PgXaEsRV+QGScHoozIGLl2Z9mfRQO13hCfObbLxKdoo4oRhDXzUmJV5C4wJ+a9nNALP2FPE8UGJh7xmdzBapDMrTxvO8slpvwodJM+aSvWABWXmDYpBOaOta5avXsqswDufHA7pjlTmXpaWt68fcY+YOFD5L7br0iojaj5KHM8V+JdnXI4ySDzVZoxGzdlJyqveSl90vsmK/FGdfUg9hugGFs5OF1s5Tn1LolNYFLOwjBr3JSVBUyt5rLWKlfaxWIi59MjCUmO4KGr7XejQ7JN5C+XXES+9IDsbz+Yf8Dl4JnJhLWz0CkOfZD+aVAz9hKDHwl0g==
ARC-Authentication-Results: i=1; mx.microsoft.com 1; spf=pass
 smtp.mailfrom=wdc.com; dmarc=pass action=none header.from=wdc.com; dkim=pass
 header.d=wdc.com; arc=none
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
 d=sharedspace.onmicrosoft.com; s=selector2-sharedspace-onmicrosoft-com;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=Sk8XpE13dIHDod3PMQVNO/6aEAf+gNs78hGIAdi/9cw=;
 b=tB/l0ITpWXv4MazsbWZnjlNm1jGTVirSKMT1gJi+0f0Dz2IRI9J4zO/xbLPFYP1w9KEjr9YBpsBDFoht0rZhUqqgpuw4gStLSmE/Qc32jRElDilRjMxkx4CMa7N4YI9905g36qTJT79Saw6Sl3cquAOtbDE4op6MmUVEaA1CPFc=
Authentication-Results: dabbelt.com; dkim=none (message not signed)
 header.d=none;dabbelt.com; dmarc=none action=none header.from=wdc.com;
Received: from CO6PR04MB7812.namprd04.prod.outlook.com (2603:10b6:303:138::6)
 by CO6PR04MB7761.namprd04.prod.outlook.com (2603:10b6:5:35f::10) with
 Microsoft SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.4129.26; Wed, 19 May
 2021 03:36:22 +0000
Received: from CO6PR04MB7812.namprd04.prod.outlook.com
 ([fe80::88a0:bf18:b01d:1a50]) by CO6PR04MB7812.namprd04.prod.outlook.com
 ([fe80::88a0:bf18:b01d:1a50%4]) with mapi id 15.20.4129.033; Wed, 19 May 2021
 03:36:22 +0000
From: Anup Patel <anup.patel@wdc.com>
To: Palmer Dabbelt <palmer@dabbelt.com>,
        Palmer Dabbelt <palmerdabbelt@google.com>,
        Paul Walmsley <paul.walmsley@sifive.com>,
        Albert Ou <aou@eecs.berkeley.edu>,
        Paolo Bonzini <pbonzini@redhat.com>,
        Jonathan Corbet <corbet@lwn.net>,
        Greg Kroah-Hartman <gregkh@linuxfoundation.org>
Cc: Alexander Graf <graf@amazon.com>,
        Atish Patra <atish.patra@wdc.com>,
        Alistair Francis <Alistair.Francis@wdc.com>,
        Damien Le Moal <damien.lemoal@wdc.com>,
        Anup Patel <anup@brainfault.org>, kvm@vger.kernel.org,
        kvm-riscv@lists.infradead.org, linux-riscv@lists.infradead.org,
        linux-doc@vger.kernel.org, linux-kernel@vger.kernel.org,
        linux-staging@lists.linux.dev, Anup Patel <anup.patel@wdc.com>
Subject: [PATCH v18 01/18] RISC-V: Add hypervisor extension related CSR
 defines
Date: Wed, 19 May 2021 09:05:36 +0530
Message-Id: <20210519033553.1110536-2-anup.patel@wdc.com>
X-Mailer: git-send-email 2.25.1
In-Reply-To: <20210519033553.1110536-1-anup.patel@wdc.com>
References: <20210519033553.1110536-1-anup.patel@wdc.com>
X-Originating-IP: [122.179.32.148]
X-ClientProxiedBy: MA1PR0101CA0057.INDPRD01.PROD.OUTLOOK.COM
 (2603:1096:a00:20::19) To CO6PR04MB7812.namprd04.prod.outlook.com
 (2603:10b6:303:138::6)
MIME-Version: 1.0
X-MS-Exchange-MessageSentRepresentingType: 1
Received: from wdc.com (122.179.32.148) by
 MA1PR0101CA0057.INDPRD01.PROD.OUTLOOK.COM (2603:1096:a00:20::19) with
 Microsoft SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.4129.25 via Frontend
 Transport; Wed, 19 May 2021 03:36:17 +0000
X-MS-PublicTrafficType: Email
X-MS-Office365-Filtering-Correlation-Id: 2d701162-f522-4caa-28c2-08d91a7745a8
X-MS-TrafficTypeDiagnostic: CO6PR04MB7761:
X-MS-Exchange-Transport-Forked: True
X-Microsoft-Antispam-PRVS: 
 <CO6PR04MB7761E1219DAC3C39EF5D77B38D2B9@CO6PR04MB7761.namprd04.prod.outlook.com>
WDCIPOUTBOUND: EOP-TRUE
X-MS-Oob-TLC-OOBClassifiers: OLM:580;
X-MS-Exchange-SenderADCheck: 1
X-Microsoft-Antispam: BCL:0;
X-Microsoft-Antispam-Message-Info: 
 92NPoQ8pmIw4k14dRzPL3ZRjS/YXiuQGAjC/NnEzmsQa/pybYIAB35Yo0QtGpCFAnmsgNJTs/YKi6OqUs71fa+gOEK8hcvksyKiOu8sbZzm3dz8APA9nh8Q0iqvskV/OCKMx9bDQEmGcKBpdf3kBNGFfKqOSEPEOko2RRtG2YTfINy5lRBg13KRw8180KvVtyPwKv6hQysQGeqyfJiHjyDidS2BtXwwc4BCLlWzHw3EDcUZjO3X0zYQ9wDhIvTdVvqcRwvoONw3gkJABt25/2XLHPRbfa0iKMcdmQyIo39Bcl8Uj86uMth/ewg2MYOFwHzvxjD6Sh7Aa7JzSzBpRQm//5mBy5ovkiXoTDlpgATesYZJJKfAkyxwCEnyXSnTFvIA2aoSAbo7cxD67gXdMrBKGPPKM8fpLcZyFJq0XMJflTiYiYh2ueOA8/jKHUCRbGAztB1bQfbtl+bfAgpOi3p2XAhzJQaBKMfIWQcha4r8ILIO86cwEY7KbmgAo3G1xLkju29wrnTyS6oWWPwjT4j59n/PjE2jtmPOq969t0LQ5c5BlqkT2jOo4BUZ7ZVURCc5j0woe+2O++Qbvvd17G3ayodLmXo9KjJUK8DxslPt/4peev+9ExVjUscXoDVQA8nBeVv5Gv94+jBurVZm2Vnr7D1ig9QLVRWPh3xSefGk=
X-Forefront-Antispam-Report: 
 CIP:255.255.255.255;CTRY:;LANG:en;SCL:1;SRV:;IPV:NLI;SFV:NSPM;H:CO6PR04MB7812.namprd04.prod.outlook.com;PTR:;CAT:NONE;SFS:(4636009)(366004)(396003)(136003)(376002)(39860400002)(346002)(316002)(38350700002)(55016002)(38100700002)(66476007)(66946007)(1076003)(2616005)(186003)(5660300002)(4326008)(26005)(8936002)(478600001)(86362001)(2906002)(52116002)(7696005)(16526019)(110136005)(8676002)(6666004)(66556008)(36756003)(7416002)(956004)(54906003)(44832011)(8886007);DIR:OUT;SFP:1102;
X-MS-Exchange-AntiSpam-MessageData: 
 /nxSsT7H60HXmxk132lWMjpXqx5dYxl0Z77yNJx1ehrhAG+CiBq8SeyAOZkRbdnQKF869TwjUZLwo3YCaFWGr3LhmG1JTyF/IPObDLUlkWCCldd22CWri4RjrnHYFxwJ0JKx/TpsK3JtWH2SKaYLjHWRJM74qcwTI2M557rBI9npiYZlcNVrOOQu8v2VKqn6EPxSjMThJUW7sPlGeEZp4MHPXSWkOsXFKZfK7PrMXYmr56aejQ9ETWpxlRg3YAn+X86AX0ySPHsG0xL4PhuSgZYT22FEl+uao34TJAU6PDI5bD56jrIrlb9i8m1KrTKRd97Y7/ZDpHBoXJdr4X1tRHRmqqS+rGnjLwLb7DHz/xGkHro5z4LwsUhNjhmvPuuxnUrU3OipvlpqqDOKNP23fCAgWzqN2s7jeYq5JnEfDJQ09m8jUpJV6AOOz2yyl6pqeMwoxUhS0N9Sd/QnOsPBFf6uBlTa7EKjGCQShlrZ/ZIgkwWXoj1u+ye4Msl4q9UmOiy4UMoIziaIszvuavEGIVjAryyf8XbrdgDJYjeIqwG6u9/cSt7b+7Xc2NTWvr6yjMJ3Ranmqr6UHBsHv/cqiO6obWfZhvUOkyy3hpBT4cgG4CMV5CNz3B+0BcFAf3seh4rdC4i4lKuTu9M1p4iZgf/2Hn45bN+5987bwabCBKbT+UBK0abDi0eAeuq9n2JKEP/BP36p815TUNrrW7FPMJHfGCrjrII3DaSEa0XviB5PH3HT+p1Vnq0t/9/Hapq97Dgq7XcBmWaVix7y6EwP4r0oDJByFMG00iWo8s+c+ewam2cYgI7A7pnygTtBDvcNPq3/4CXjq+ldpGLe5Wjtlyh6fYxBSEr29csMUhEiJrJWeNxtaFUet6DzaSrghfKFw8beQixrpDLySiXKZywxKkyOHNBL3AJqNh8P2yjHSrAt7QEpHKaGBoHllDM0VMlVDUES8BCPKScGu037nz5oZMdtxkJ9L0YjcN1kfuzo2EHIinjYnpY7Qy06RQBqf69HqZ7euv5p0G0Q8z97abzZQEQmVrjJTI1Jz1zkydQlTd43xMotVwDSOYlk83Gq9BPI6vo/p/80UbXa33edKYy9lEO52e4w2EgLZ0dFRiE+hjGJV807zbkUV78sTJQ2IZrnELjn4DDeBTuJj+em+fwCO7vmpUlf29qC7bYIuEa2p4YGoAq0DzEWRfuC+1WbfoW6KExm//KLvjBxm8+ENSLaadEza76oVtRF0lZGe7vWnJt4ImX0TUonSySDGGqTdvLM+0rqqSuOsfOLHp4gyu8YzQUfnF5gP/5tBsPHKE/20zeKeyUsUOsfdg9M9vfewC6Z
X-OriginatorOrg: wdc.com
X-MS-Exchange-CrossTenant-Network-Message-Id: 
 2d701162-f522-4caa-28c2-08d91a7745a8
X-MS-Exchange-CrossTenant-AuthSource: CO6PR04MB7812.namprd04.prod.outlook.com
X-MS-Exchange-CrossTenant-AuthAs: Internal
X-MS-Exchange-CrossTenant-OriginalArrivalTime: 19 May 2021 03:36:22.2899
 (UTC)
X-MS-Exchange-CrossTenant-FromEntityHeader: Hosted
X-MS-Exchange-CrossTenant-Id: b61c8803-16f3-4c35-9b17-6f65f441df86
X-MS-Exchange-CrossTenant-MailboxType: HOSTED
X-MS-Exchange-CrossTenant-UserPrincipalName: 
 7XFIJR0L1DbRDRGJIWwj6uIHLw3GteXgGkMWEQlFzYN35UOyxEGYLareKhhob6iPkb+zeiCRB2i7vLg5oiYyFQ==
X-MS-Exchange-Transport-CrossTenantHeadersStamped: CO6PR04MB7761
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This patch adds asm/kvm_csr.h for RISC-V hypervisor extension
related defines.

Signed-off-by: Anup Patel <anup.patel@wdc.com>
Acked-by: Paolo Bonzini <pbonzini@redhat.com>
Reviewed-by: Paolo Bonzini <pbonzini@redhat.com>
Reviewed-by: Alexander Graf <graf@amazon.com>
---
 arch/riscv/include/asm/kvm_csr.h | 105 +++++++++++++++++++++++++++++++
 1 file changed, 105 insertions(+)
 create mode 100644 arch/riscv/include/asm/kvm_csr.h

diff --git a/arch/riscv/include/asm/kvm_csr.h b/arch/riscv/include/asm/kvm_csr.h
new file mode 100644
index 000000000000..def91f53514c
--- /dev/null
+++ b/arch/riscv/include/asm/kvm_csr.h
@@ -0,0 +1,105 @@
+/* SPDX-License-Identifier: GPL-2.0-only */
+/*
+ * Copyright (C) 2021 Western Digital Corporation or its affiliates.
+ *
+ * Authors:
+ *     Anup Patel <anup.patel@wdc.com>
+ */
+
+#ifndef __RISCV_KVM_CSR_H__
+#define __RISCV_KVM_CSR_H__
+
+#include <asm/csr.h>
+
+/* Interrupt causes (minus the high bit) */
+#define IRQ_VS_SOFT		2
+#define IRQ_VS_TIMER		6
+#define IRQ_VS_EXT		10
+
+ /* Exception causes */
+#define EXC_INST_ILLEGAL	2
+#define EXC_HYPERVISOR_SYSCALL	9
+#define EXC_SUPERVISOR_SYSCALL	10
+#define EXC_INST_GUEST_PAGE_FAULT	20
+#define EXC_LOAD_GUEST_PAGE_FAULT	21
+#define EXC_VIRTUAL_INST_FAULT	22
+#define EXC_STORE_GUEST_PAGE_FAULT	23
+
+/* HSTATUS flags */
+#ifdef CONFIG_64BIT
+#define HSTATUS_VSXL		_AC(0x300000000, UL)
+#define HSTATUS_VSXL_SHIFT	32
+#endif
+#define HSTATUS_VTSR		_AC(0x00400000, UL)
+#define HSTATUS_VTW		_AC(0x00200000, UL)
+#define HSTATUS_VTVM		_AC(0x00100000, UL)
+#define HSTATUS_VGEIN		_AC(0x0003f000, UL)
+#define HSTATUS_VGEIN_SHIFT	12
+#define HSTATUS_HU		_AC(0x00000200, UL)
+#define HSTATUS_SPVP		_AC(0x00000100, UL)
+#define HSTATUS_SPV		_AC(0x00000080, UL)
+#define HSTATUS_GVA		_AC(0x00000040, UL)
+#define HSTATUS_VSBE		_AC(0x00000020, UL)
+
+/* HGATP flags */
+#define HGATP_MODE_OFF		_AC(0, UL)
+#define HGATP_MODE_SV32X4	_AC(1, UL)
+#define HGATP_MODE_SV39X4	_AC(8, UL)
+#define HGATP_MODE_SV48X4	_AC(9, UL)
+
+#define HGATP32_MODE_SHIFT	31
+#define HGATP32_VMID_SHIFT	22
+#define HGATP32_VMID_MASK	_AC(0x1FC00000, UL)
+#define HGATP32_PPN		_AC(0x003FFFFF, UL)
+
+#define HGATP64_MODE_SHIFT	60
+#define HGATP64_VMID_SHIFT	44
+#define HGATP64_VMID_MASK	_AC(0x03FFF00000000000, UL)
+#define HGATP64_PPN		_AC(0x00000FFFFFFFFFFF, UL)
+
+#define HGATP_PAGE_SHIFT	12
+
+#ifdef CONFIG_64BIT
+#define HGATP_PPN		HGATP64_PPN
+#define HGATP_VMID_SHIFT	HGATP64_VMID_SHIFT
+#define HGATP_VMID_MASK		HGATP64_VMID_MASK
+#define HGATP_MODE_SHIFT	HGATP64_MODE_SHIFT
+#else
+#define HGATP_PPN		HGATP32_PPN
+#define HGATP_VMID_SHIFT	HGATP32_VMID_SHIFT
+#define HGATP_VMID_MASK		HGATP32_VMID_MASK
+#define HGATP_MODE_SHIFT	HGATP32_MODE_SHIFT
+#endif
+
+/* VSIP & HVIP relation */
+#define VSIP_TO_HVIP_SHIFT	(IRQ_VS_SOFT - IRQ_S_SOFT)
+#define VSIP_VALID_MASK		((_AC(1, UL) << IRQ_S_SOFT) | \
+				 (_AC(1, UL) << IRQ_S_TIMER) | \
+				 (_AC(1, UL) << IRQ_S_EXT))
+
+#define CSR_VSSTATUS		0x200
+#define CSR_VSIE		0x204
+#define CSR_VSTVEC		0x205
+#define CSR_VSSCRATCH		0x240
+#define CSR_VSEPC		0x241
+#define CSR_VSCAUSE		0x242
+#define CSR_VSTVAL		0x243
+#define CSR_VSIP		0x244
+#define CSR_VSATP		0x280
+
+#define CSR_HSTATUS		0x600
+#define CSR_HEDELEG		0x602
+#define CSR_HIDELEG		0x603
+#define CSR_HIE			0x604
+#define CSR_HTIMEDELTA		0x605
+#define CSR_HCOUNTEREN		0x606
+#define CSR_HGEIE		0x607
+#define CSR_HTIMEDELTAH		0x615
+#define CSR_HTVAL		0x643
+#define CSR_HIP			0x644
+#define CSR_HVIP		0x645
+#define CSR_HTINST		0x64a
+#define CSR_HGATP		0x680
+#define CSR_HGEIP		0xe12
+
+#endif

From patchwork Wed May 19 03:35:37 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Anup Patel <Anup.Patel@wdc.com>
X-Patchwork-Id: 12266107
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.7 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,MSGID_FROM_MTA_HEADER,SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED,
	USER_AGENT_GIT autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 4CDA9C433B4
	for <kvm@archiver.kernel.org>; Wed, 19 May 2021 03:36:36 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 3151760FD8
	for <kvm@archiver.kernel.org>; Wed, 19 May 2021 03:36:36 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S240428AbhESDht (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 18 May 2021 23:37:49 -0400
Received: from esa2.hgst.iphmx.com ([68.232.143.124]:13878 "EHLO
        esa2.hgst.iphmx.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S238157AbhESDhs (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 18 May 2021 23:37:48 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=simple/simple;
  d=wdc.com; i=@wdc.com; q=dns/txt; s=dkim.wdc.com;
  t=1621395389; x=1652931389;
  h=from:to:cc:subject:date:message-id:in-reply-to:
   references:content-transfer-encoding:mime-version;
  bh=9rHYAsNKtstOK9+Yf1PjZJp04ECAoXFA9BkQ7vM+Low=;
  b=laEe8i16nbRTCPSqU+pHHLkQdTZpT+DX7e6BEq9Pvsftuf7hMAKXmA/O
   Ivi7Ukk0IltJ0MySzw0N9Sk2tYOYIksTeokx4VqgFaqNswa6USZZZjKbC
   YY/ga068/LvVBXRLClysyqGc17U13ESPWGpyWqB1oQ6PEcpU9hhXC/zwJ
   hIg610mBF2jsxgWib3CyGOvog1QfzUWLJ0d3MijLvUGyd0ZsfrUItqetD
   HsPJU7g+m7LyImhkDikBZmSmR4h0hYUFoh1Z+JicJpEnAPYM6nj7QADlC
   8l87lkt1PspP1PDYylEugF+CgLLAfDJpXVINVpc27kVnwoQbzpmoSdaod
   w==;
IronPort-SDR: 
 kseP4D9cnVstHmDgs9k1De6N8qBWR+wjLaRj44etLTkB1JSTGGDUJRyYKHbVfO6zEUdhGGm6E5
 RHVoXvSsN3It/SBtSCD/WX2WtPMaZoMLus5zuSy3eJThKDc748Jo0dpFdi2POXVlhsc7MsRU0z
 2IV8IzeDD9bXVpPibI9M5pt2vYunOlq0Km+1cISxRaYu85UVr9d7vJMq1bNDPLv0nd4tYNdhzl
 k/liQfwE+kHmSl11WegGl1jICwIvZBGXeEgE4aRE9sFguSeNDYZUVGTjIrfWumoh6sYcTel6nj
 4p8=
X-IronPort-AV: E=Sophos;i="5.82,311,1613404800";
   d="scan'208";a="272597130"
Received: from mail-co1nam11lp2176.outbound.protection.outlook.com (HELO
 NAM11-CO1-obe.outbound.protection.outlook.com) ([104.47.56.176])
  by ob1.hgst.iphmx.com with ESMTP; 19 May 2021 11:36:30 +0800
ARC-Seal: i=1; a=rsa-sha256; s=arcselector9901; d=microsoft.com; cv=none;
 b=BjQAKg3aqKBCOh06I2o714M0iVQHTMtk2qI4U9vwg8YEwmRcAOb/OtezIN/wIeUorm1UFe/NnPQRTNyjM34qXoBKJKupiBVZXBTgEvJFSi4R/IqYsG5887dP6pV9NValFgNLCGXJNa669VNYtSB1yplymz0WFO4xa/E3RI8Fwq37ZiR150UWijbwvgdN0X/cf+RRdAMKXAYUO3E5tv51qVUoZMlQrQn9nRF8L9yREN7Ld9U+tJ1rtKFIXInplVb5R0JUO9QAPL6tQrYOhCig95Lzs0VYXY/MWZ8ptrpSUJDdviMW2gVY7+tSp2aWRN1e75CSdSBcImED8/fnld6TZg==
ARC-Message-Signature: i=1; a=rsa-sha256; c=relaxed/relaxed; d=microsoft.com;
 s=arcselector9901;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=KWwKrZea1O1wNmb7sURWpjLWgYK7o8TusBtqqoYS7Bw=;
 b=mw7+/YftqdlYVVMd7ajdv8ecilssT4cN7jaAfbsvaxJfJRbnBAEz2UNe7mk21m3vbeak7tIy4nABhW61K/i96ey4aVINvDc3TK4+aYIuaEJQH7gEb818oY2gIFD8aB9eh1ib8dS4i1wMEk1a3iKobxIIyTnzcFMo8hzScCi1pqAp+VYV5yvqh7rwRntOrS6gSFE/DTWVHNqp4Vqdz9jpQ6hIJr1Cat2l5cF8fc+DrFwOOfx8oL9yhtaifk8aNCJ4m/q3c6vJxcJA3tB9Dz0siARGifw3D3iWk4ymWtppPkmDMrVd5zCVDvGH9Xl+e5FaMwsLeleUugwGMFxlk0UVvw==
ARC-Authentication-Results: i=1; mx.microsoft.com 1; spf=pass
 smtp.mailfrom=wdc.com; dmarc=pass action=none header.from=wdc.com; dkim=pass
 header.d=wdc.com; arc=none
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
 d=sharedspace.onmicrosoft.com; s=selector2-sharedspace-onmicrosoft-com;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=KWwKrZea1O1wNmb7sURWpjLWgYK7o8TusBtqqoYS7Bw=;
 b=CH8IUV04VE5dgrMWV4jm27X/wZjMTC8zp6Dgj5GLaBHujqHXoyMVvq74yvrdOi63DIhDLzA5a2hW2oU6eojlmNAn+g6gX5KTfzqG4fhZPG5Rj4a8xsd9JS783ClNtS+H25Wbwj0XeQxbEtWOsLHtL0TBji0k2WFRhl1cDvuHidY=
Authentication-Results: dabbelt.com; dkim=none (message not signed)
 header.d=none;dabbelt.com; dmarc=none action=none header.from=wdc.com;
Received: from CO6PR04MB7812.namprd04.prod.outlook.com (2603:10b6:303:138::6)
 by CO6PR04MB7761.namprd04.prod.outlook.com (2603:10b6:5:35f::10) with
 Microsoft SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.4129.26; Wed, 19 May
 2021 03:36:27 +0000
Received: from CO6PR04MB7812.namprd04.prod.outlook.com
 ([fe80::88a0:bf18:b01d:1a50]) by CO6PR04MB7812.namprd04.prod.outlook.com
 ([fe80::88a0:bf18:b01d:1a50%4]) with mapi id 15.20.4129.033; Wed, 19 May 2021
 03:36:27 +0000
From: Anup Patel <anup.patel@wdc.com>
To: Palmer Dabbelt <palmer@dabbelt.com>,
        Palmer Dabbelt <palmerdabbelt@google.com>,
        Paul Walmsley <paul.walmsley@sifive.com>,
        Albert Ou <aou@eecs.berkeley.edu>,
        Paolo Bonzini <pbonzini@redhat.com>,
        Jonathan Corbet <corbet@lwn.net>,
        Greg Kroah-Hartman <gregkh@linuxfoundation.org>
Cc: Alexander Graf <graf@amazon.com>,
        Atish Patra <atish.patra@wdc.com>,
        Alistair Francis <Alistair.Francis@wdc.com>,
        Damien Le Moal <damien.lemoal@wdc.com>,
        Anup Patel <anup@brainfault.org>, kvm@vger.kernel.org,
        kvm-riscv@lists.infradead.org, linux-riscv@lists.infradead.org,
        linux-doc@vger.kernel.org, linux-kernel@vger.kernel.org,
        linux-staging@lists.linux.dev, Anup Patel <anup.patel@wdc.com>
Subject: [PATCH v18 02/18] RISC-V: Add initial skeletal KVM support
Date: Wed, 19 May 2021 09:05:37 +0530
Message-Id: <20210519033553.1110536-3-anup.patel@wdc.com>
X-Mailer: git-send-email 2.25.1
In-Reply-To: <20210519033553.1110536-1-anup.patel@wdc.com>
References: <20210519033553.1110536-1-anup.patel@wdc.com>
X-Originating-IP: [122.179.32.148]
X-ClientProxiedBy: MA1PR0101CA0057.INDPRD01.PROD.OUTLOOK.COM
 (2603:1096:a00:20::19) To CO6PR04MB7812.namprd04.prod.outlook.com
 (2603:10b6:303:138::6)
MIME-Version: 1.0
X-MS-Exchange-MessageSentRepresentingType: 1
Received: from wdc.com (122.179.32.148) by
 MA1PR0101CA0057.INDPRD01.PROD.OUTLOOK.COM (2603:1096:a00:20::19) with
 Microsoft SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.4129.25 via Frontend
 Transport; Wed, 19 May 2021 03:36:22 +0000
X-MS-PublicTrafficType: Email
X-MS-Office365-Filtering-Correlation-Id: cccb6109-47b3-4e4d-6645-08d91a77488b
X-MS-TrafficTypeDiagnostic: CO6PR04MB7761:
X-MS-Exchange-Transport-Forked: True
X-Microsoft-Antispam-PRVS: 
 <CO6PR04MB776167D29CCC126F276C3D2D8D2B9@CO6PR04MB7761.namprd04.prod.outlook.com>
WDCIPOUTBOUND: EOP-TRUE
X-MS-Oob-TLC-OOBClassifiers: OLM:214;
X-MS-Exchange-SenderADCheck: 1
X-Microsoft-Antispam: BCL:0;
X-Microsoft-Antispam-Message-Info: 
 SwKGXW67Tgv+GwprBIw61Uvo7CyBY6jJtauM9sBpxynkAOtTqGG0CtDL4IIlfaXEVH6IbLpeyUCMX2Zk5WLFZUUKSxkRxL3zwEKRiR8Gr52yUmIooLfvB7uTMjb95OoK8E52qVmddd1DZZZW0fei9jREHG4LiUI8+chGgI5q2B2amiGkyFlzWssM3UVGez2u/fqaJJiN0H9u5TJtcx49gfsqRr2flQq1yB+IAbsiZP/mA6f8XfMV7AArkZz0q07kql0uA6Jjvhnnb6kna6tQ+MyC3g5wjiDvcJQyi0ZEpYga/SMvgqk+mHv3mw3DgSSH4dodQKID0hDlIfM6KoaXr4wR2XYV0DiiEWAaLsHqmIiA01iwaXbYtnOwkAJL/EW8+p2HjzUmrVfzx92YdYba/XYHp25n96gYdNhaU1X42dM4nvoGy8LChD8kka4tE5972i8LWF6QpWVLPDZkRxHiw9VhNPJQc/ym9WYef3o7NtlZ1P+qV100zsLL7OCLXjDlZaN2PQ5Hc7qcsjadmPFDbndH3z2TsjFodRrWqBHv7rXFaTxw/wTHy4xHoW7I5zfMLmwkvLkf0w4HiXZm3VWj7m/1U/qUySf4BTNaviEp+FamVh8yIemheMMPrY1YrsmAXve5v/sLvCptP4kIQsbXuw==
X-Forefront-Antispam-Report: 
 CIP:255.255.255.255;CTRY:;LANG:en;SCL:1;SRV:;IPV:NLI;SFV:NSPM;H:CO6PR04MB7812.namprd04.prod.outlook.com;PTR:;CAT:NONE;SFS:(4636009)(366004)(396003)(136003)(376002)(39860400002)(346002)(316002)(38350700002)(55016002)(38100700002)(66476007)(66946007)(1076003)(2616005)(186003)(5660300002)(4326008)(26005)(8936002)(478600001)(86362001)(2906002)(52116002)(7696005)(16526019)(110136005)(83380400001)(8676002)(6666004)(66556008)(36756003)(30864003)(7416002)(956004)(54906003)(44832011)(8886007);DIR:OUT;SFP:1102;
X-MS-Exchange-AntiSpam-MessageData: 
 f8EIXjAekpRiguPxpCUk19XqCfcTo7XqU+Cmm/eg+Mqy7BqJaoE3OlCkjgPIW8Ip9482gf3FeFCeNYFR2f1wZnW+dQIOoLnwJ50IOMP+AoJkyZIP1WsPsZEJuXXWbTxQJPZ176scYNZgh97d/AB6rlHaBLTbYFH0NZzy558f1akDnpvzjpSsdVhmjtmLGnbI418tVlqPpzupazvQvppFO6zgzWIxTNrzfvzwpVazUt8jK+GpjfsgquP/38M4B3nCrBXLFubJXuA4P+ABlmKJXVAVkCOExMD+3h5WQSBABM2uKYaGlomUzpjIupxyyClL46+jqtH7Z2gKTzYOotLH0xw4bW1aJZtIQsEQsdJ2bnL3RnGphzwDOD0MiVj+7Z4PIC2CkHViY+ZVZLAM8Rvk25MyMvXZDHVDd5zYYAKGhHTFMIvscYbFPkKv9mB7tNUgb8YW6WC+TnokaDC7LTpWiotRhhRKZEwuFcoq0wK6dFBBydcHwcw3vxdEgSzE2m8C7QmQK1uKZpR++7dYVdDMqaxrJc30R6PkrcZKqYylUgsVm/TLndNYFM/3VeHAEIu0vjAQB9G/oOc7rTh3aCseEHsdEFMlkf5KygjAJQKKIP9kfy/uT8x+R+BAGpKuZrhyfPyL07F6anRM9hRm94Ugd4/HpYXozIJD/JszWPOG9lwXzhP4yJPdR73YOulymYVGOt6XMvTCwWvdPT0NBOtRMkzgw4Mg3sfWKPc+xrqqsh6Tcf6+CjYqfxdgqIAfRxkwAkIenObRnc08N4gYqRjz1rwQDlCIEINCNU6Eb+S0Eay4yafMtulXIvyKrDmMwG8Zf12Tzxk1ARHofNWny0pYrenpM8k+v6hX72/MRcQXOwuHMv1GGgsO8Ykwi/CK/o6SAf43MMUw32mfsvrVL4DBhKf5yF+mskm34J9qG2VuOA6Oa7svyIpiezQiMgtIOrv+du2VCgQr8+9O4UVpcFXLUvwdfAlbYGrERmaQklB+rf7gFpudZQk8pPKq8S9srkKNgIyDm3PPOUcmvAb1CsWuDNR7glT11ueUlH4vfCn3WiNLeL6jogplDNgDS4Cta/U/C/FYR5omhBrCaDeIKJz5781ePp+fQbylDg3jAOSSTahQgEDP0fIwoa/RAAZMpARo3pH/zHjq9lexUs7CrY4gpVTgi6F2mpgsRrrl5B3YorOwJSGFx5qkop9d6vvC771Hqxn1ExrYiJ4U9SH3FMDLsCmXgYD3cr67LBIF7GvvRLYcHG48DPcaQTjAIQ/LCz04LSJc7zrt6oK+5MJ7poX0v0/aJoHXx8PhvhWb79YtCkIbRiXBiOqctsu6qElkL9sa
X-OriginatorOrg: wdc.com
X-MS-Exchange-CrossTenant-Network-Message-Id: 
 cccb6109-47b3-4e4d-6645-08d91a77488b
X-MS-Exchange-CrossTenant-AuthSource: CO6PR04MB7812.namprd04.prod.outlook.com
X-MS-Exchange-CrossTenant-AuthAs: Internal
X-MS-Exchange-CrossTenant-OriginalArrivalTime: 19 May 2021 03:36:27.1674
 (UTC)
X-MS-Exchange-CrossTenant-FromEntityHeader: Hosted
X-MS-Exchange-CrossTenant-Id: b61c8803-16f3-4c35-9b17-6f65f441df86
X-MS-Exchange-CrossTenant-MailboxType: HOSTED
X-MS-Exchange-CrossTenant-UserPrincipalName: 
 TBTrot7DYrv+cuyeymV7+f1CMxfymHamKhcYuq+Kswn/AemC3TQe3tAhL7wj/CegTbTYDJTbvobFzaWB92WeUQ==
X-MS-Exchange-Transport-CrossTenantHeadersStamped: CO6PR04MB7761
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This patch adds initial skeletal KVM RISC-V support which has:
1. A simple implementation of arch specific VM functions
   except kvm_vm_ioctl_get_dirty_log() which will implemeted
   in-future as part of stage2 page loging.
2. Stubs of required arch specific VCPU functions except
   kvm_arch_vcpu_ioctl_run() which is semi-complete and
   extended by subsequent patches.
3. Stubs for required arch specific stage2 MMU functions.

Signed-off-by: Anup Patel <anup.patel@wdc.com>
Acked-by: Paolo Bonzini <pbonzini@redhat.com>
Reviewed-by: Paolo Bonzini <pbonzini@redhat.com>
Reviewed-by: Alexander Graf <graf@amazon.com>
---
 arch/riscv/Kconfig                 |   1 +
 arch/riscv/Makefile                |   1 +
 arch/riscv/include/asm/kvm_host.h  |  89 +++++++++
 arch/riscv/include/asm/kvm_types.h |   7 +
 arch/riscv/include/uapi/asm/kvm.h  |  47 +++++
 arch/riscv/kvm/Kconfig             |  33 +++
 arch/riscv/kvm/Makefile            |  13 ++
 arch/riscv/kvm/main.c              |  95 +++++++++
 arch/riscv/kvm/mmu.c               |  80 ++++++++
 arch/riscv/kvm/vcpu.c              | 311 +++++++++++++++++++++++++++++
 arch/riscv/kvm/vcpu_exit.c         |  35 ++++
 arch/riscv/kvm/vm.c                |  79 ++++++++
 12 files changed, 791 insertions(+)
 create mode 100644 arch/riscv/include/asm/kvm_host.h
 create mode 100644 arch/riscv/include/asm/kvm_types.h
 create mode 100644 arch/riscv/include/uapi/asm/kvm.h
 create mode 100644 arch/riscv/kvm/Kconfig
 create mode 100644 arch/riscv/kvm/Makefile
 create mode 100644 arch/riscv/kvm/main.c
 create mode 100644 arch/riscv/kvm/mmu.c
 create mode 100644 arch/riscv/kvm/vcpu.c
 create mode 100644 arch/riscv/kvm/vcpu_exit.c
 create mode 100644 arch/riscv/kvm/vm.c

```
#### [kvm-unit-tests PATCH v2 1/3] s390x: sclp: Only fetch read info byte 134 if cpu entries are above it
##### From: Janosch Frank <frankja@linux.ibm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Janosch Frank <frankja@linux.ibm.com>
X-Patchwork-Id: 12266633
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.8 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT
	autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 717CBC433B4
	for <kvm@archiver.kernel.org>; Wed, 19 May 2021 08:29:28 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 51DFB60240
	for <kvm@archiver.kernel.org>; Wed, 19 May 2021 08:29:28 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S245202AbhESI3H (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Wed, 19 May 2021 04:29:07 -0400
Received: from mx0b-001b2d01.pphosted.com ([148.163.158.5]:22488 "EHLO
        mx0b-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S245142AbhESI3G (ORCPT
        <rfc822;kvm@vger.kernel.org>); Wed, 19 May 2021 04:29:06 -0400
Received: from pps.filterd (m0127361.ppops.net [127.0.0.1])
        by mx0a-001b2d01.pphosted.com (8.16.0.43/8.16.0.43) with SMTP id
 14J83piO073952;
        Wed, 19 May 2021 04:27:46 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=ibm.com;
 h=from : to : cc : subject
 : date : message-id : in-reply-to : references : mime-version :
 content-transfer-encoding; s=pp1;
 bh=wm8EzEp0hbruUfdJVkUo5iG8w+LwCA4Z3V8AkVbpEus=;
 b=Q4TTDnIOiohW6VGC2P0Ph+0bsq2I8GhgR8RXjCrI+8ltPBaDvYUMVOd8aO0fqNGbKmvj
 0ZdWhOCvffcrI4equb/nTySABNqAE1YWv1tKmt9DDMvLebPHnXBPWsvPwhcQgdIzSmuR
 wrlDH/MNa2QQwx3VoL/bvUx0ytF5hKhPFIvjCDSs+eLCDE9R630rpNvcMGocpdrB05MU
 H+Z0inW+JW8sJg29wBrEXyG+D+O5GcJM8BgXWmZqbuIUTY4ulyDCpAzqK0oabOaBNmN3
 mH+uy3PSn5erq+sY8Uplyf9W1BfkgVr6Mw6PQtq8sXj57RRNuuq/DsRv6RXOhK+E3GNy xg==
Received: from pps.reinject (localhost [127.0.0.1])
        by mx0a-001b2d01.pphosted.com with ESMTP id 38mxj1162y-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Wed, 19 May 2021 04:27:46 -0400
Received: from m0127361.ppops.net (m0127361.ppops.net [127.0.0.1])
        by pps.reinject (8.16.0.43/8.16.0.43) with SMTP id 14J8Rksp192724;
        Wed, 19 May 2021 04:27:46 -0400
Received: from ppma02fra.de.ibm.com (47.49.7a9f.ip4.static.sl-reverse.com
 [159.122.73.71])
        by mx0a-001b2d01.pphosted.com with ESMTP id 38mxj1162d-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Wed, 19 May 2021 04:27:45 -0400
Received: from pps.filterd (ppma02fra.de.ibm.com [127.0.0.1])
        by ppma02fra.de.ibm.com (8.16.0.43/8.16.0.43) with SMTP id
 14J8M9Ja022436;
        Wed, 19 May 2021 08:27:44 GMT
Received: from b06avi18878370.portsmouth.uk.ibm.com
 (b06avi18878370.portsmouth.uk.ibm.com [9.149.26.194])
        by ppma02fra.de.ibm.com with ESMTP id 38mceh8ad0-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Wed, 19 May 2021 08:27:44 +0000
Received: from d06av24.portsmouth.uk.ibm.com (mk.ibm.com [9.149.105.60])
        by b06avi18878370.portsmouth.uk.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id 14J8RD4B34144738
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Wed, 19 May 2021 08:27:13 GMT
Received: from d06av24.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 0A46D42041;
        Wed, 19 May 2021 08:27:41 +0000 (GMT)
Received: from d06av24.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 3DF3B42042;
        Wed, 19 May 2021 08:27:40 +0000 (GMT)
Received: from linux01.pok.stglabs.ibm.com (unknown [9.114.17.81])
        by d06av24.portsmouth.uk.ibm.com (Postfix) with ESMTP;
        Wed, 19 May 2021 08:27:40 +0000 (GMT)
From: Janosch Frank <frankja@linux.ibm.com>
To: kvm@vger.kernel.org
Cc: frankja@linux.ibm.com, david@redhat.com, cohuck@redhat.com,
        linux-s390@vger.kernel.org, imbrenda@linux.ibm.com,
        thuth@redhat.com
Subject: [kvm-unit-tests PATCH v2 1/3] s390x: sclp: Only fetch read info byte
 134 if cpu entries are above it
Date: Wed, 19 May 2021 08:26:46 +0000
Message-Id: <20210519082648.46803-2-frankja@linux.ibm.com>
X-Mailer: git-send-email 2.30.2
In-Reply-To: <20210519082648.46803-1-frankja@linux.ibm.com>
References: <20210519082648.46803-1-frankja@linux.ibm.com>
MIME-Version: 1.0
X-TM-AS-GCONF: 00
X-Proofpoint-GUID: YLOFJvebgh-j4HBMJuFB8KUkbzNK_Qan
X-Proofpoint-ORIG-GUID: i6th0VspFX8HMN-O0vVKpOtXl1SMxyfF
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.391,18.0.761
 definitions=2021-05-19_02:2021-05-18,2021-05-19 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 priorityscore=1501
 malwarescore=0 mlxlogscore=999 impostorscore=0 adultscore=0 bulkscore=0
 clxscore=1015 suspectscore=0 mlxscore=0 spamscore=0 lowpriorityscore=0
 phishscore=0 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.12.0-2104190000 definitions=main-2105190059
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The cpu offset tells us where the cpu entries are in the sclp read
info structure.

Signed-off-by: Janosch Frank <frankja@linux.ibm.com>
Reviewed-by: Claudio Imbrenda <imbrenda@linux.ibm.com>
Reviewed-by: David Hildenbrand <david@redhat.com>
Reviewed-by: Cornelia Huck <cohuck@redhat.com>
---
 lib/s390x/sclp.c | 3 ++-
 1 file changed, 2 insertions(+), 1 deletion(-)

```
#### [kvm-unit-tests PATCH v3 1/6] s390x: uv-guest: Add invalid share location test
##### From: Janosch Frank <frankja@linux.ibm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Janosch Frank <frankja@linux.ibm.com>
X-Patchwork-Id: 12266501
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.8 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT
	autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id AF06DC433B4
	for <kvm@archiver.kernel.org>; Wed, 19 May 2021 07:40:43 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 89BEC61364
	for <kvm@archiver.kernel.org>; Wed, 19 May 2021 07:40:43 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S240567AbhESHmB (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Wed, 19 May 2021 03:42:01 -0400
Received: from mx0b-001b2d01.pphosted.com ([148.163.158.5]:28416 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S238476AbhESHmB (ORCPT
        <rfc822;kvm@vger.kernel.org>); Wed, 19 May 2021 03:42:01 -0400
Received: from pps.filterd (m0098419.ppops.net [127.0.0.1])
        by mx0b-001b2d01.pphosted.com (8.16.0.43/8.16.0.43) with SMTP id
 14J7Ztdf107203;
        Wed, 19 May 2021 03:40:41 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=ibm.com;
 h=from : to : cc : subject
 : date : message-id : in-reply-to : references : mime-version :
 content-transfer-encoding; s=pp1;
 bh=3uZmSI77E5TGNyfkRuQlpsM6Hja+QeN+kVV0qwniZ1M=;
 b=PntznEl3JYZ7ruiC+RIQlVLj6KXmcsJPqD/qIURi2Akdd678MNd68qUnPhlwbSZZLjJD
 HxuG9wBKA6iv3MGdBH7CVpZC8gR9OFimu8Y+B0gF2oZ7oPvAzBUWXgIKdtSk/JZLbjYH
 Pbc1WYQYVhCvLvFJ5WwiBd86nbmUobEau1qHroXsYv6bvZCG5xymn9RFU6ABNbCceubU
 Fga/jAfA9WLQ8igtaY30HnJsCnFC4nGCvxIJ+dXQOgrmqk4CuSwLl3wU8c0/PtR2Qe5/
 IiODsjKRESGUOQufoCXIa1MOWx1ut3/l1S0aClQBE9Iy1Acq/7M6kgHd97F+YnvsJAae JQ==
Received: from pps.reinject (localhost [127.0.0.1])
        by mx0b-001b2d01.pphosted.com with ESMTP id 38mx73ggg5-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Wed, 19 May 2021 03:40:41 -0400
Received: from m0098419.ppops.net (m0098419.ppops.net [127.0.0.1])
        by pps.reinject (8.16.0.43/8.16.0.43) with SMTP id 14J7aMuN108593;
        Wed, 19 May 2021 03:40:41 -0400
Received: from ppma04ams.nl.ibm.com (63.31.33a9.ip4.static.sl-reverse.com
 [169.51.49.99])
        by mx0b-001b2d01.pphosted.com with ESMTP id 38mx73gget-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Wed, 19 May 2021 03:40:41 -0400
Received: from pps.filterd (ppma04ams.nl.ibm.com [127.0.0.1])
        by ppma04ams.nl.ibm.com (8.16.0.43/8.16.0.43) with SMTP id
 14J7bdQM004010;
        Wed, 19 May 2021 07:40:39 GMT
Received: from b06cxnps4076.portsmouth.uk.ibm.com
 (d06relay13.portsmouth.uk.ibm.com [9.149.109.198])
        by ppma04ams.nl.ibm.com with ESMTP id 38j5x89x73-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Wed, 19 May 2021 07:40:39 +0000
Received: from b06wcsmtp001.portsmouth.uk.ibm.com
 (b06wcsmtp001.portsmouth.uk.ibm.com [9.149.105.160])
        by b06cxnps4076.portsmouth.uk.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id 14J7eaLB40829338
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Wed, 19 May 2021 07:40:36 GMT
Received: from b06wcsmtp001.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 70E3AA4060;
        Wed, 19 May 2021 07:40:36 +0000 (GMT)
Received: from b06wcsmtp001.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id A38CAA405C;
        Wed, 19 May 2021 07:40:35 +0000 (GMT)
Received: from linux01.pok.stglabs.ibm.com (unknown [9.114.17.81])
        by b06wcsmtp001.portsmouth.uk.ibm.com (Postfix) with ESMTP;
        Wed, 19 May 2021 07:40:35 +0000 (GMT)
From: Janosch Frank <frankja@linux.ibm.com>
To: kvm@vger.kernel.org
Cc: frankja@linux.ibm.com, david@redhat.com, cohuck@redhat.com,
        linux-s390@vger.kernel.org, imbrenda@linux.ibm.com,
        thuth@redhat.com
Subject: [kvm-unit-tests PATCH v3 1/6] s390x: uv-guest: Add invalid share
 location test
Date: Wed, 19 May 2021 07:40:17 +0000
Message-Id: <20210519074022.7368-2-frankja@linux.ibm.com>
X-Mailer: git-send-email 2.30.2
In-Reply-To: <20210519074022.7368-1-frankja@linux.ibm.com>
References: <20210519074022.7368-1-frankja@linux.ibm.com>
MIME-Version: 1.0
X-TM-AS-GCONF: 00
X-Proofpoint-GUID: NcMP3Ne4QutKwu4WEXMCDZ2oYWUkbfzL
X-Proofpoint-ORIG-GUID: OlhwDVqisi7uqM7cQ-BGzNzJcyEVNCzT
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.391,18.0.761
 definitions=2021-05-19_02:2021-05-18,2021-05-19 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 suspectscore=0
 mlxlogscore=999 clxscore=1015 impostorscore=0 malwarescore=0
 lowpriorityscore=0 priorityscore=1501 adultscore=0 mlxscore=0 bulkscore=0
 spamscore=0 phishscore=0 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.12.0-2104190000 definitions=main-2105190055
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Let's also test sharing unavailable memory.

Signed-off-by: Janosch Frank <frankja@linux.ibm.com>
Reviewed-by: Claudio Imbrenda <imbrenda@linux.ibm.com>
Reviewed-by: Cornelia Huck <cohuck@redhat.com>
Reviewed-by: Thomas Huth <thuth@redhat.com>
---
 s390x/uv-guest.c | 5 +++++
 1 file changed, 5 insertions(+)

```
#### [PATCH v2 1/8] x86/sev-es: Don't return NULL from sev_es_get_ghcb()
##### From: Joerg Roedel <joro@8bytes.org>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Joerg Roedel <joro@8bytes.org>
X-Patchwork-Id: 12267387
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.7 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED,USER_AGENT_GIT
	autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 3EE28C433B4
	for <kvm@archiver.kernel.org>; Wed, 19 May 2021 13:53:18 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 29357611AE
	for <kvm@archiver.kernel.org>; Wed, 19 May 2021 13:53:18 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1353808AbhESNyg (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Wed, 19 May 2021 09:54:36 -0400
Received: from 8bytes.org ([81.169.241.247]:40008 "EHLO theia.8bytes.org"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1353773AbhESNyc (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 19 May 2021 09:54:32 -0400
Received: from cap.home.8bytes.org (p549ad305.dip0.t-ipconnect.de
 [84.154.211.5])
        (using TLSv1.3 with cipher TLS_AES_256_GCM_SHA384 (256/256 bits))
        (No client certificate requested)
        by theia.8bytes.org (Postfix) with ESMTPSA id 82BEC2FA;
        Wed, 19 May 2021 15:53:08 +0200 (CEST)
From: Joerg Roedel <joro@8bytes.org>
To: x86@kernel.org, Hyunwook Baek <baekhw@google.com>
Cc: Joerg Roedel <joro@8bytes.org>, Joerg Roedel <jroedel@suse.de>,
        stable@vger.kernel.org, hpa@zytor.com,
        Andy Lutomirski <luto@kernel.org>,
        Dave Hansen <dave.hansen@linux.intel.com>,
        Peter Zijlstra <peterz@infradead.org>,
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
        Sean Christopherson <seanjc@google.com>,
        Martin Radev <martin.b.radev@gmail.com>,
        Arvind Sankar <nivedita@alum.mit.edu>,
        linux-coco@lists.linux.dev, linux-kernel@vger.kernel.org,
        kvm@vger.kernel.org, virtualization@lists.linux-foundation.org
Subject: [PATCH v2 1/8] x86/sev-es: Don't return NULL from sev_es_get_ghcb()
Date: Wed, 19 May 2021 15:52:44 +0200
Message-Id: <20210519135251.30093-2-joro@8bytes.org>
X-Mailer: git-send-email 2.31.1
In-Reply-To: <20210519135251.30093-1-joro@8bytes.org>
References: <20210519135251.30093-1-joro@8bytes.org>
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Joerg Roedel <jroedel@suse.de>

The sev_es_get_ghcb() is called from several places, but only one of
them checks the return value. The reaction to returning NULL is always
the same: Calling panic() and kill the machine.

Instead of adding checks to all call-places, move the panic() into the
function itself so that it will no longer return NULL.

Fixes: 0786138c78e7 ("x86/sev-es: Add a Runtime #VC Exception Handler")
Cc: stable@vger.kernel.org # v5.10+
Signed-off-by: Joerg Roedel <jroedel@suse.de>
---
 arch/x86/kernel/sev.c | 25 ++++++++++++-------------
 1 file changed, 12 insertions(+), 13 deletions(-)

```
