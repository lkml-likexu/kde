#### [PATCH 1/2] KVM: arm64: CSSELR_EL1 max is 13
##### From: Andrew Jones <drjones@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Andrew Jones <drjones@redhat.com>
X-Patchwork-Id: 11934109
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-15.8 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_CR_TRAILER,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS
	autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 7DA13C56202
	for <kvm@archiver.kernel.org>; Thu, 26 Nov 2020 13:47:05 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 2EC44206C0
	for <kvm@archiver.kernel.org>; Thu, 26 Nov 2020 13:47:05 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="AqP22zNY"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2391102AbgKZNqu (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Thu, 26 Nov 2020 08:46:50 -0500
Received: from us-smtp-delivery-124.mimecast.com ([63.128.21.124]:50116 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S2390834AbgKZNqt (ORCPT
        <rfc822;kvm@vger.kernel.org>); Thu, 26 Nov 2020 08:46:49 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1606398409;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding:
         in-reply-to:in-reply-to:references:references;
        bh=ZV1eVRFg54k0Zal0/KxnT+naLTq9uAHCIPcq+JSenDw=;
        b=AqP22zNYhPZjRXSHmGv4W3TcCBz71USGXO/6B5193vdvKDVZ9kkqjU4xNtj5QxDB4/w7WN
        8B+9aswj2u4iblZBbfiPn+I87JK5Qng8CQu2Vt3r9rJ02jShFok/Kw5uPi5BjJ33R1GvK/
        kDUfGB0LtGuWUmXnseVVkqjWMAulLCc=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-426-Xn-HebAfNb6nwNvM1dGkkQ-1; Thu, 26 Nov 2020 08:46:47 -0500
X-MC-Unique: Xn-HebAfNb6nwNvM1dGkkQ-1
Received: from smtp.corp.redhat.com (int-mx07.intmail.prod.int.phx2.redhat.com
 [10.5.11.22])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 4D2E6193ECE3;
        Thu, 26 Nov 2020 13:46:46 +0000 (UTC)
Received: from kamzik.brq.redhat.com (unknown [10.40.192.141])
        by smtp.corp.redhat.com (Postfix) with ESMTP id D1D1010021AA;
        Thu, 26 Nov 2020 13:46:44 +0000 (UTC)
From: Andrew Jones <drjones@redhat.com>
To: kvm@vger.kernel.org, kvmarm@lists.cs.columbia.edu
Cc: maz@kernel.org, pbonzini@redhat.com
Subject: [PATCH 1/2] KVM: arm64: CSSELR_EL1 max is 13
Date: Thu, 26 Nov 2020 14:46:40 +0100
Message-Id: <20201126134641.35231-2-drjones@redhat.com>
In-Reply-To: <20201126134641.35231-1-drjones@redhat.com>
References: <20201126134641.35231-1-drjones@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.84 on 10.5.11.22
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Not counting TnD, which KVM doesn't currently consider, CSSELR_EL1
can have a maximum value of 0b1101 (13), which corresponds to an
instruction cache at level 7. With CSSELR_MAX set to 12 we can
only select up to cache level 6. Change it to 14.

Signed-off-by: Andrew Jones <drjones@redhat.com>
---
 arch/arm64/kvm/sys_regs.c | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
#### [PATCH] kvm:svm: Return the correct error codeThread-Topic: [PATCH] kvm:svm: Return the correct error code
##### From: =?utf-8?b?5b2t5rWpKFJpY2hhcmQp?= <richard.peng@oppo.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: =?utf-8?b?5b2t5rWpKFJpY2hhcmQp?=
 <richard.peng@oppo.com>
X-Patchwork-Id: 11932763
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-13.8 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS autolearn=unavailable
	autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 42C07C63777
	for <kvm@archiver.kernel.org>; Thu, 26 Nov 2020 07:14:15 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id DD3DF20DD4
	for <kvm@archiver.kernel.org>; Thu, 26 Nov 2020 07:14:14 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=oppoglobal.onmicrosoft.com
 header.i=@oppoglobal.onmicrosoft.com header.b="Se8K1To5"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2388353AbgKZHNc (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Thu, 26 Nov 2020 02:13:32 -0500
Received: from mail-eopbgr1300070.outbound.protection.outlook.com
 ([40.107.130.70]:44583
        "EHLO APC01-HK2-obe.outbound.protection.outlook.com"
        rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org with ESMTP
        id S2388333AbgKZHNa (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 26 Nov 2020 02:13:30 -0500
ARC-Seal: i=1; a=rsa-sha256; s=arcselector9901; d=microsoft.com; cv=none;
 b=RtZ8yXx7cESq2gUAI/Ikjuof0EyfQM9mC2l5CjONk+Gq3jsWi0VddZh5nQer3RwaH5AicGLyi34zWpLx+zPQmq9p5Gh528EP5Y7vrImjaTXrQFRWqiz8xpwXNw6gvYoy42OlmS37wx6pf8QK7T/4d0E4gNV0yZO7c4JQzz5bQuAtK+VpwXSsDTk6kMCrhfuynwPY7eMcORMWREVGXv3Cwzu44cVr5eVC/AnyqibEdXBqdlcubmeFQu/sEUXYBmzC0inux0dSeFfXzycLi8nIQgbdXg5zpjXsoCrL7N874Zv5ft4hRD9G0FtpcoaS2lo/ddUcVHxtA6Oe+XxH+wTgaQ==
ARC-Message-Signature: i=1; a=rsa-sha256; c=relaxed/relaxed; d=microsoft.com;
 s=arcselector9901;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=+TKRrr3oyWGMVGmeIRJ2AOUfHaMeFfHrA8UgydINz24=;
 b=n41GqV4TpTJ/Dk28m3/RwgP1oBJIwDt3g2dZ+nUlgKoMFpcU/ejWv8GPgfyyBPiTCv5TBaqrQwRmGHavVSExEKzKGNT+RYD3R3c0aC3uMuuywrSiCvVrCzbc3VahR9FEwp3+J62zDDf6JkJFa9KO3yYjqvhKzuwrpWsB7MvmiMuHFNUWUA09jQ8WA3U9FqGmbg3ZuYDMEmKIgWxm+pn/0Pla6GIeXUu1dAoPvKXihIuyQTDNNTTdxZuvsCv0hajQFOnMFf990re7LB+VB1nmxUcACZljicSojaIOrf5Sj3C+2hL6s1ogE3ofRK05orVtnJi5NV2SMP/gta1FfcDgkQ==
ARC-Authentication-Results: i=1; mx.microsoft.com 1; spf=pass
 smtp.mailfrom=oppo.com; dmarc=pass action=none header.from=oppo.com;
 dkim=pass header.d=oppo.com; arc=none
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
 d=oppoglobal.onmicrosoft.com; s=selector1-oppoglobal-onmicrosoft-com;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=+TKRrr3oyWGMVGmeIRJ2AOUfHaMeFfHrA8UgydINz24=;
 b=Se8K1To5aHYtBDnSwsimwtWNO1CTllTyEO4Rgd2VaobzuX1GjiHJ76tf9jBJFXJmT1V73HuwFlYHwlMU0rrVwI5VOhnDf60EIxzuITAjfp2VYqypBbL14OQoPhnsyk8hRoqBeDkK+3pjrNCT+7n2YTSi8xc7W7krjok6AqN9Lcc=
Received: from HKAPR02MB4291.apcprd02.prod.outlook.com (2603:1096:203:d3::12)
 by HKAPR02MB4371.apcprd02.prod.outlook.com (2603:1096:203:d4::16) with
 Microsoft SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.3589.21; Thu, 26 Nov
 2020 07:13:25 +0000
Received: from HKAPR02MB4291.apcprd02.prod.outlook.com
 ([fe80::b9b8:aaf4:2afd:218b]) by HKAPR02MB4291.apcprd02.prod.outlook.com
 ([fe80::b9b8:aaf4:2afd:218b%3]) with mapi id 15.20.3611.022; Thu, 26 Nov 2020
 07:13:25 +0000
From: =?utf-8?b?5b2t5rWpKFJpY2hhcmQp?= <richard.peng@oppo.com>
To: Paolo Bonzini <pbonzini@redhat.com>,
        "Suravee.Suthikulpanit@amd.com" <Suravee.Suthikulpanit@amd.com>
CC: "linux-kernel@vger.kernel.org" <linux-kernel@vger.kernel.org>,
        "kvm@vger.kernel.org" <kvm@vger.kernel.org>
Subject: [PATCH] kvm:svm: Return the correct error code
Thread-Topic: [PATCH] kvm:svm: Return the correct error code
Thread-Index: AdbDw07DFQcZfob5RjiYdtD4llKu/w==
Date: Thu, 26 Nov 2020 07:13:25 +0000
Message-ID: 
 <HKAPR02MB42915D77D43D4ED125BD2121E0F90@HKAPR02MB4291.apcprd02.prod.outlook.com>
Accept-Language: zh-CN, en-US
Content-Language: zh-CN
X-MS-Has-Attach: 
X-MS-TNEF-Correlator: 
authentication-results: redhat.com; dkim=none (message not signed)
 header.d=none;redhat.com; dmarc=none action=none header.from=oppo.com;
x-originating-ip: [58.252.5.70]
x-ms-publictraffictype: Email
x-ms-office365-filtering-correlation-id: 6a599748-f468-40eb-8dc0-08d891dac444
x-ms-traffictypediagnostic: HKAPR02MB4371:
x-microsoft-antispam-prvs: 
 <HKAPR02MB437112ABEC0DFF8B82C3DD16E0F90@HKAPR02MB4371.apcprd02.prod.outlook.com>
x-ms-oob-tlc-oobclassifiers: OLM:2733;
x-ms-exchange-senderadcheck: 1
x-microsoft-antispam: BCL:0;
x-microsoft-antispam-message-info: 
 lhrudQuDxtDp4cnuUvn9SB2AK7ivEXxpELMwYIApoGSfXf556DifLdjoiPGpMdgQ5wRRqkuOQ+hLGkJeNSaR5cCYxanEnZb028LpfSWP0YA2wGf6+32PEseqYLwXK/AH0S06LyC6Fb1OOUVYiyvm9TAyFlREdqxTAyTdxO7ZvP5DTfdv/INJk50WYJZrXH7uzsjKc60VVW2OLvdz0x15TyHKw8do6zmAmHxJ0dmij9YG7wAbaJJ2BXuOdi5eAwDhZwJ7SURqWbqkPZDFF3MEHMFAnfhU6QMS/ve0lvZvixyn3SDpCKCciTTIsYPe2TDlOjtyi1sSx27G9f89jgcHjmt02fZixUzz5MQow1OW/OHPl7Xa6Ha89ArriUgN47Mi
x-forefront-antispam-report: 
 CIP:255.255.255.255;CTRY:;LANG:en;SCL:1;SRV:;IPV:NLI;SFV:NSPM;H:HKAPR02MB4291.apcprd02.prod.outlook.com;PTR:;CAT:NONE;SFS:(4636009)(346002)(39860400002)(136003)(396003)(366004)(376002)(4744005)(6506007)(8676002)(83380400001)(4326008)(66946007)(52536014)(7696005)(8936002)(2906002)(86362001)(71200400001)(9686003)(55016002)(110136005)(85182001)(76116006)(66446008)(316002)(186003)(5660300002)(478600001)(66556008)(26005)(66476007)(64756008)(33656002)(54906003)(11606006);DIR:OUT;SFP:1101;
x-ms-exchange-antispam-messagedata: =?utf-8?q?r2YzdCKsqn+V0OtINLRjqWS4rr20To?=
	=?utf-8?q?T/HWrWB+u5V/+wAgkScC0sWYLk0Vio7dMjFhxHMcygV8pSvVmMTHMfW8Hwzqvu4W9?=
	=?utf-8?q?UIJDb73D7U4V7Vm++jUKk/vQb1TpTHkmdy+1Vcx48jBMTom3ondPlCpHrHmcnsQks?=
	=?utf-8?q?hiJ16lbN+FbXhocRzys+UP06TDk7+G5BNUtIsxgv1r0+VKiUD/CoVcb0Zkn3QP65j?=
	=?utf-8?q?GX74sbM7z1SkeEfThhgoYZ0KBHW7fnuc8SKswf9XV0g0k6WkyW6kjph2uipZq8f6t?=
	=?utf-8?q?HFkLtgBa7QweGK8WVXrlEq3LpXiMaVsdiPn8hGuNzO8B6/ye63J8Ctylfhv6LbCSo?=
	=?utf-8?q?q6H5wpmDxsYiggMIZncKdAehroPY9Nhu2AkXUvT0j1aj4bmmx9mlF1tpkVcfpvHof?=
	=?utf-8?q?Bg6pC9abU1LsoIis6QtK2E7Oh2rety5fZoPabK0Jb3D2ztOEuhPM48wJZZcG6r18c?=
	=?utf-8?q?s4fxcGfqIJRNd8Icp5IApRMSjX9dTM9waJNLuaHCeeuSFvXCwNB7E4ofF3NHd6wMB?=
	=?utf-8?q?T81tJ5/W/1lu8OM419EdtSd5GJq7shGKaoxEvOP+2HE8pQHLUijfT2LbmrcsmM1uR?=
	=?utf-8?q?NeRDyU4KLK0GNOUSBB/FXT/3KzLzTuCg0ABx+tC10S+1yUIuvmIlZm6xyO/NP/+Fm?=
	=?utf-8?q?IOO8V7EaayrRUHr4QRWEcKnFWseqHdXl3AjssMIPuQbgPwiyMah2p0/S1QhxXjnqE?=
	=?utf-8?q?9sKh5xYNgFN0EyiJr7t4BE4JTvbcQfxNOS5FbdD31yn/JJWy9If+NcWhJpRsStcy/?=
	=?utf-8?q?pEF38u7+qUpcJdP1Use8AaxHI9uTP9BfuV0c14e6XL6mSdUgf94a6IhHwjTe3PzVF?=
	=?utf-8?q?63SpxLjbeBL0/MnQ1/VoaEoS1hKOHXr+A/2hu9193KwiCGC/M2dmflp3n0DbWZCNt?=
	=?utf-8?q?ZsM0LATZ7u58YUlhiO1TraREcmKVipPpx1wKq/F1J20iEcDW0SpmM8Jha6zCdfE?=
	=?utf-8?q?=3D?=
x-ms-exchange-transport-forked: True
MIME-Version: 1.0
X-OriginatorOrg: oppo.com
X-MS-Exchange-CrossTenant-AuthAs: Internal
X-MS-Exchange-CrossTenant-AuthSource: HKAPR02MB4291.apcprd02.prod.outlook.com
X-MS-Exchange-CrossTenant-Network-Message-Id: 
 6a599748-f468-40eb-8dc0-08d891dac444
X-MS-Exchange-CrossTenant-originalarrivaltime: 26 Nov 2020 07:13:25.3405
 (UTC)
X-MS-Exchange-CrossTenant-fromentityheader: Hosted
X-MS-Exchange-CrossTenant-id: f1905eb1-c353-41c5-9516-62b4a54b5ee6
X-MS-Exchange-CrossTenant-mailboxtype: HOSTED
X-MS-Exchange-CrossTenant-userprincipalname: 
 8022BFKxVRNZrz8zG//NzvZfzFjG65vKHQ+fua2finVIwUCeRgvpo0nliW8BlI28nTAj+36gP0jTpET1+QwOJw==
X-MS-Exchange-Transport-CrossTenantHeadersStamped: HKAPR02MB4371
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The return value of sev_asid_new is assigned to the variable asid, which
should be returned directly if the asid is an error code.

Fixes: 1654efcbc431 ("KVM: SVM: Add KVM_SEV_INIT command")
Signed-off-by: Peng Hao <richard.peng@oppo.com>
---
 arch/x86/kvm/svm/sev.c | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

--
2.18.4

```
#### [PATCH] kvm/x86: Fix simultaneous ExtINT and lapic interrupt handling with APICv
##### From: David Woodhouse <dwmw2@infradead.org>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: David Woodhouse <dwmw2@infradead.org>
X-Patchwork-Id: 11933401
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-17.2 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,
	INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,USER_AGENT_SANE_2
	autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id E2945C56202
	for <kvm@archiver.kernel.org>; Thu, 26 Nov 2020 12:05:49 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 39C6320857
	for <kvm@archiver.kernel.org>; Thu, 26 Nov 2020 12:05:49 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=infradead.org header.i=@infradead.org
 header.b="MG6ZlfcF"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728364AbgKZMFs (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Thu, 26 Nov 2020 07:05:48 -0500
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:43606 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726321AbgKZMFs (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 26 Nov 2020 07:05:48 -0500
Received: from merlin.infradead.org (merlin.infradead.org
 [IPv6:2001:8b0:10b:1231::1])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 9C63EC0613D4
        for <kvm@vger.kernel.org>; Thu, 26 Nov 2020 04:05:47 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; q=dns/txt; c=relaxed/relaxed;
        d=infradead.org; s=merlin.20170209;
 h=Mime-Version:Content-Type:References:
        In-Reply-To:Date:Cc:To:From:Subject:Message-ID:Sender:Reply-To:
        Content-Transfer-Encoding:Content-ID:Content-Description;
        bh=0U9ehtY9XGUy3iyYnIyiQ5B+rTrgXoQsjFNpkMxJDNY=;
 b=MG6ZlfcF53BNOdLR8cydrJ8fAI
        5xwyeTCovYXydSanISXabf5SISO22WOyioNFEuAmTiROY0/niRLqcEbQqCxFSXs8emqGTI1Nolx6Q
        KOKBZeDl/oeKj2yD0tQdo+09MHxlslJ0KeiuUtNzVF+ARpuV7PJIafa1ir0e4KEc0rWMFZv0ZEoEp
        53/VnI4n9JRi9nurxlhC63o9L9GyNgdCFku/PEreVQu9HC8mu23tCZ6iM2vq23zo57/zolOlmniPj
        i5V7068lnNqQaJeneHxIzV8tg9N3r8hky2r0Batx7Lpar6UzYyag6kj96Aec/1KvYZc+W1Z2SZ9MP
        zlV9n6Ug==;
Received: from 54-240-197-230.amazon.com ([54.240.197.230]
 helo=freeip.amazon.com)
        by merlin.infradead.org with esmtpsa (Exim 4.92.3 #3 (Red Hat Linux))
        id 1kiG1r-00060V-QS; Thu, 26 Nov 2020 12:05:40 +0000
Message-ID: <6a8897917188a3a23710199f8da3f5f33670b80f.camel@infradead.org>
Subject: [PATCH] kvm/x86: Fix simultaneous ExtINT and lapic interrupt
 handling with APICv
From: David Woodhouse <dwmw2@infradead.org>
To: Sean Christopherson <seanjc@google.com>,
        Paolo Bonzini <pbonzini@redhat.com>
Cc: kvm <kvm@vger.kernel.org>, "Sironi, Filippo" <sironi@amazon.de>,
        "Raslan, KarimAllah" <karahmed@amazon.de>,
        Matt Gingell <gingell@google.com>,
        Steve Rutherford <srutherford@google.com>, liran@amazon.com
Date: Thu, 26 Nov 2020 12:05:37 +0000
In-Reply-To: <99a9c1dfbb21744e5081d924291d3b09ab055813.camel@infradead.org>
References: <62918f65ec78f8990278a6a0db0567968fa23e49.camel@infradead.org>
         <017de9019136b5d2ec34132b96b9f0273c21d6f1.camel@infradead.org>
         <20201125211955.GA450871@google.com>
         <99a9c1dfbb21744e5081d924291d3b09ab055813.camel@infradead.org>
X-Mailer: Evolution 3.28.5-0ubuntu0.18.04.2 
Mime-Version: 1.0
X-SRS-Rewrite: SMTP reverse-path rewritten from <dwmw2@infradead.org> by
 merlin.infradead.org. See http://www.infradead.org/rpr.html
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: David Woodhouse <dwmw@amazon.co.uk>

Booting a guest with 'noapic' with split irqchip and APICv enabled leads
to a livelock in vcpu_run().

When the userspace PIC has an IRQ to deliver, the VMM sets
kvm_run->request_interrupt_window and vcpu_enter_guest() duly enables the
corresponding VMexit, which happens immediately.

However, if an interrupt also exists in the local APIC, that causes
kvm_cpu_has_interrupt() to be true and thus causes
kvm_vcpu_ready_for_interrupt_injection() to return false; the intent
being that the kernel will use this interrupt window to inject its own
interrupt from the LAPIC. So vcpu_run() doesn't exit all the way to
userspace, and just loops.

However, when APICv is in use there is no interrupt to be injected since
that happens automatically. So the guest vCPU is launched again, exits
again immediately, and the loop repeats ad infinitum without making any
progress.

It looks like this was introduced in commit 782d422bcaee, when
dm_request_for_irq_injection() started returning true based purely
on the fact that userspace had requested the interrupt window, without
heed to kvm_cpu_has_interrupt() also being true.

Fix it by allowing userspace to use the interrupt window with priority
over the interrupt that is already in the LAPIC, for both APICv and
legacy injection alike. Instead of '!kvm_cpu_has_interrupt()', the
condition becomes '!(lapic_in_kernel(vcpu) && kvm_cpu_has_extint(vcpu))'

Fixes: 782d422bcaee ("KVM: x86: split kvm_vcpu_ready_for_interrupt_injection out of dm_request_for_irq_injection")
Signed-off-by: David Woodhouse <dwmw@amazon.co.uk>
Cc: stable@vger.kernel.org
---
 arch/x86/include/asm/kvm_host.h | 1 +
 arch/x86/kvm/irq.c              | 2 +-
 arch/x86/kvm/x86.c              | 6 ++++--
 3 files changed, 6 insertions(+), 3 deletions(-)

```
#### [PATCH] kvm: x86/mmu: Fix get_mmio_spte() on CPUs supporting 5-level PT
##### From: Vitaly Kuznetsov <vkuznets@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Vitaly Kuznetsov <vkuznets@redhat.com>
X-Patchwork-Id: 11933221
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-15.8 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_CR_TRAILER,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS
	autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id CDEA7C63777
	for <kvm@archiver.kernel.org>; Thu, 26 Nov 2020 11:02:19 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 4AECF221FB
	for <kvm@archiver.kernel.org>; Thu, 26 Nov 2020 11:02:19 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="MJz8GNIy"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1730128AbgKZLCP (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Thu, 26 Nov 2020 06:02:15 -0500
Received: from us-smtp-delivery-124.mimecast.com ([216.205.24.124]:29129 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1729663AbgKZLCP (ORCPT
        <rfc822;kvm@vger.kernel.org>); Thu, 26 Nov 2020 06:02:15 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1606388534;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=wRLRXSeehVYPVGuCA1d0o01Y+gIuPbLbz2602T4YeXA=;
        b=MJz8GNIycgMjs3uiRGTFuyENpaPTEYm600V7oDtz6TG9cL180qcERgTztvq5ND8fa0MXO2
        mEfK2Amj5lpm/p4zEyk8cQrOW7zD1S8ynHvNUqkpYsldtI9stVWduu9p981GGNkkF8nvrZ
        N+2R322Dk/xgm2GmdxXZ7v2wee47d+0=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-531-La-84-XrMvy6T0qdNSLkKw-1; Thu, 26 Nov 2020 06:02:11 -0500
X-MC-Unique: La-84-XrMvy6T0qdNSLkKw-1
Received: from smtp.corp.redhat.com (int-mx02.intmail.prod.int.phx2.redhat.com
 [10.5.11.12])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id EE509805C06;
        Thu, 26 Nov 2020 11:02:09 +0000 (UTC)
Received: from vitty.brq.redhat.com (unknown [10.40.195.61])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 1446260C05;
        Thu, 26 Nov 2020 11:02:07 +0000 (UTC)
From: Vitaly Kuznetsov <vkuznets@redhat.com>
To: kvm@vger.kernel.org, Paolo Bonzini <pbonzini@redhat.com>
Cc: Sean Christopherson <seanjc@google.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Ben Gardon <bgardon@google.com>
Subject: [PATCH] kvm: x86/mmu: Fix get_mmio_spte() on CPUs supporting 5-level
 PT
Date: Thu, 26 Nov 2020 12:02:06 +0100
Message-Id: <20201126110206.2118959-1-vkuznets@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.12
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Commit 95fb5b0258b7 ("kvm: x86/mmu: Support MMIO in the TDP MMU") caused
the following WARNING on an Intel Ice Lake CPU:

 get_mmio_spte: detect reserved bits on spte, addr 0xb80a0, dump hierarchy:
 ------ spte 0xb80a0 level 5.
 ------ spte 0xfcd210107 level 4.
 ------ spte 0x1004c40107 level 3.
 ------ spte 0x1004c41107 level 2.
 ------ spte 0x1db00000000b83b6 level 1.
 WARNING: CPU: 109 PID: 10254 at arch/x86/kvm/mmu/mmu.c:3569 kvm_mmu_page_fault.cold.150+0x54/0x22f [kvm]
...
 Call Trace:
  ? kvm_io_bus_get_first_dev+0x55/0x110 [kvm]
  vcpu_enter_guest+0xaa1/0x16a0 [kvm]
  ? vmx_get_cs_db_l_bits+0x17/0x30 [kvm_intel]
  ? skip_emulated_instruction+0xaa/0x150 [kvm_intel]
  kvm_arch_vcpu_ioctl_run+0xca/0x520 [kvm]

The guest triggering this crashes. Note, this happens with the traditional
MMU and EPT enabled, not with the newly introduced TDP MMU. Turns out,
there was a subtle change in the above mentioned commit. Previously,
walk_shadow_page_get_mmio_spte() was setting 'root' to 'iterator.level'
which is returned by shadow_walk_init() and this equals to
'vcpu->arch.mmu->shadow_root_level'. Now, get_mmio_spte() sets it to
'int root = vcpu->arch.mmu->root_level'.

The difference between 'root_level' and 'shadow_root_level' on CPUs
supporting 5-level page tables is that in some case we don't want to
use 5-level, in particular when 'cpuid_maxphyaddr(vcpu) <= 48'
kvm_mmu_get_tdp_level() returns '4'. In case upper layer is not used,
the corresponding SPTE will fail '__is_rsvd_bits_set()' check.

Revert to using 'shadow_root_level'.

Fixes: 95fb5b0258b7 ("kvm: x86/mmu: Support MMIO in the TDP MMU")
Signed-off-by: Vitaly Kuznetsov <vkuznets@redhat.com>
---
- The usual (for KVM MMU) caveat 'I may be missing everything' applies,
 please review)
---
 arch/x86/kvm/mmu/mmu.c | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
#### [PATCH v2 1/1] vfio/type1: Add vfio_group_domain()
##### From: Lu Baolu <baolu.lu@linux.intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Lu Baolu <baolu.lu@linux.intel.com>
X-Patchwork-Id: 11932459
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.8 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT
	autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 6CAFEC63798
	for <kvm@archiver.kernel.org>; Thu, 26 Nov 2020 01:35:10 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 1DD1F20B1F
	for <kvm@archiver.kernel.org>; Thu, 26 Nov 2020 01:35:10 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1730646AbgKZBex (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Wed, 25 Nov 2020 20:34:53 -0500
Received: from mga09.intel.com ([134.134.136.24]:29161 "EHLO mga09.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726483AbgKZBex (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 25 Nov 2020 20:34:53 -0500
IronPort-SDR: 
 3GkKJmJXyIoTS+CKb0TJCwuFIkeg0UAYJMTFrqX4Iwpr18Hx2r2eKgfzetug2rB/n6KtDMV0kG
 BCaQnDsJU3Ww==
X-IronPort-AV: E=McAfee;i="6000,8403,9816"; a="172379669"
X-IronPort-AV: E=Sophos;i="5.78,370,1599548400";
   d="scan'208";a="172379669"
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from fmsmga004.fm.intel.com ([10.253.24.48])
  by orsmga102.jf.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 25 Nov 2020 17:34:52 -0800
IronPort-SDR: 
 Ju/OJVcePi+BPbWhGCJq86Ftbi/dH9cTkOGoM3RgHSHroeUUJ8o7RywvcZXioaOeD0L39E0YrN
 pDlm5itLN/bw==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.78,370,1599548400";
   d="scan'208";a="362616801"
Received: from allen-box.sh.intel.com ([10.239.159.28])
  by fmsmga004.fm.intel.com with ESMTP; 25 Nov 2020 17:34:49 -0800
From: Lu Baolu <baolu.lu@linux.intel.com>
To: Alex Williamson <alex.williamson@redhat.com>,
        Cornelia Huck <cohuck@redhat.com>
Cc: Joerg Roedel <joro@8bytes.org>, Will Deacon <will@kernel.org>,
        Robin Murphy <robin.murphy@arm.com>,
        Jean-Philippe Brucker <jean-philippe@linaro.org>,
        Kevin Tian <kevin.tian@intel.com>,
        Ashok Raj <ashok.raj@intel.com>,
        Dave Jiang <dave.jiang@intel.com>,
        Liu Yi L <yi.l.liu@intel.com>, Zeng Xin <xin.zeng@intel.com>,
        iommu@lists.linux-foundation.org, linux-kernel@vger.kernel.org,
        kvm@vger.kernel.org, Lu Baolu <baolu.lu@linux.intel.com>
Subject: [PATCH v2 1/1] vfio/type1: Add vfio_group_domain()
Date: Thu, 26 Nov 2020 09:27:26 +0800
Message-Id: <20201126012726.1185171-1-baolu.lu@linux.intel.com>
X-Mailer: git-send-email 2.25.1
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Add the API for getting the domain from a vfio group. This could be used
by the physical device drivers which rely on the vfio/mdev framework for
mediated device user level access. The typical use case like below:

	unsigned int pasid;
	struct vfio_group *vfio_group;
	struct iommu_domain *iommu_domain;
	struct device *dev = mdev_dev(mdev);
	struct device *iommu_device = mdev_get_iommu_device(dev);

	if (!iommu_device ||
	    !iommu_dev_feature_enabled(iommu_device, IOMMU_DEV_FEAT_AUX))
		return -EINVAL;

	vfio_group = vfio_group_get_external_user_from_dev(dev);(dev);
	if (IS_ERR_OR_NULL(vfio_group))
		return -EFAULT;

	iommu_domain = vfio_group_domain(vfio_group);
	if (IS_ERR_OR_NULL(iommu_domain)) {
		vfio_group_put_external_user(vfio_group);
		return -EFAULT;
	}

	pasid = iommu_aux_get_pasid(iommu_domain, iommu_device);
	if (pasid < 0) {
		vfio_group_put_external_user(vfio_group);
		return -EFAULT;
	}

	/* Program device context with pasid value. */
	...

Signed-off-by: Lu Baolu <baolu.lu@linux.intel.com>
---
 drivers/vfio/vfio.c             | 18 ++++++++++++++++++
 drivers/vfio/vfio_iommu_type1.c | 23 +++++++++++++++++++++++
 include/linux/vfio.h            |  3 +++
 3 files changed, 44 insertions(+)

Change log:
 - v1: https://lore.kernel.org/linux-iommu/20201112022407.2063896-1-baolu.lu@linux.intel.com/
 - Changed according to comments @ https://lore.kernel.org/linux-iommu/20201116125631.2d043fcd@w520.home/

```
