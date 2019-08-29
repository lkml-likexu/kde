#### [PATCH 1/2] vhost/test: fix build for vhost test
##### From: Tiwei Bie <tiwei.bie@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Tiwei Bie <tiwei.bie@intel.com>
X-Patchwork-Id: 11117789
Return-Path: <SRS0=KojS=WY=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 1251914DE
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 28 Aug 2019 05:41:00 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id EF0A122DA7
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 28 Aug 2019 05:40:59 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726300AbfH1Fks (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 28 Aug 2019 01:40:48 -0400
Received: from mga05.intel.com ([192.55.52.43]:18843 "EHLO mga05.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726052AbfH1Fks (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 28 Aug 2019 01:40:48 -0400
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from orsmga004.jf.intel.com ([10.7.209.38])
  by fmsmga105.fm.intel.com with ESMTP/TLS/DHE-RSA-AES256-GCM-SHA384;
 27 Aug 2019 22:40:47 -0700
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.64,440,1559545200";
   d="scan'208";a="332049724"
Received: from dpdk-virtio-tbie-2.sh.intel.com ([10.67.104.71])
  by orsmga004.jf.intel.com with ESMTP; 27 Aug 2019 22:40:45 -0700
From: Tiwei Bie <tiwei.bie@intel.com>
To: mst@redhat.com, jasowang@redhat.com
Cc: kvm@vger.kernel.org, virtualization@lists.linux-foundation.org,
        netdev@vger.kernel.org, linux-kernel@vger.kernel.org,
        stable@vger.kernel.org
Subject: [PATCH 1/2] vhost/test: fix build for vhost test
Date: Wed, 28 Aug 2019 13:36:59 +0800
Message-Id: <20190828053700.26022-1-tiwei.bie@intel.com>
X-Mailer: git-send-email 2.17.1
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Since below commit, callers need to specify the iov_limit in
vhost_dev_init() explicitly.

Fixes: b46a0bf78ad7 ("vhost: fix OOB in get_rx_bufs()")
Cc: stable@vger.kernel.org
Signed-off-by: Tiwei Bie <tiwei.bie@intel.com>
---
 drivers/vhost/test.c | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
#### [kvm-unit-tests RFC PATCH 01/16] arm: selftest.c: Remove redundant check for Exception Level
##### From: Alexandru Elisei <alexandru.elisei@arm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Alexandru Elisei <alexandru.elisei@arm.com>
X-Patchwork-Id: 11119133
Return-Path: <SRS0=KojS=WY=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 27D8B18EC
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 28 Aug 2019 13:38:53 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 128DB22CF8
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 28 Aug 2019 13:38:53 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726448AbfH1Niw (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 28 Aug 2019 09:38:52 -0400
Received: from foss.arm.com ([217.140.110.172]:59510 "EHLO foss.arm.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726197AbfH1Niv (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 28 Aug 2019 09:38:51 -0400
Received: from usa-sjc-imap-foss1.foss.arm.com (unknown [10.121.207.14])
        by usa-sjc-mx-foss1.foss.arm.com (Postfix) with ESMTP id 70766360;
        Wed, 28 Aug 2019 06:38:51 -0700 (PDT)
Received: from e121566-lin.cambridge.arm.com (e121566-lin.cambridge.arm.com
 [10.1.196.217])
        by usa-sjc-imap-foss1.foss.arm.com (Postfix) with ESMTPA id
 498823F246;
        Wed, 28 Aug 2019 06:38:50 -0700 (PDT)
From: Alexandru Elisei <alexandru.elisei@arm.com>
To: kvm@vger.kernel.org, kvmarm@lists.cs.columbia.edu
Cc: drjones@redhat.com, pbonzini@redhat.com, rkrcmar@redhat.com,
        maz@kernel.org, vladimir.murzin@arm.com, andre.przywara@arm.com
Subject: [kvm-unit-tests RFC PATCH 01/16] arm: selftest.c: Remove redundant
 check for Exception Level
Date: Wed, 28 Aug 2019 14:38:16 +0100
Message-Id: <1566999511-24916-2-git-send-email-alexandru.elisei@arm.com>
X-Mailer: git-send-email 2.7.4
In-Reply-To: <1566999511-24916-1-git-send-email-alexandru.elisei@arm.com>
References: <1566999511-24916-1-git-send-email-alexandru.elisei@arm.com>
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

expected_regs.pstate already has PSR_MODE_EL1h set as the expected
Exception Level.

Signed-off-by: Alexandru Elisei <alexandru.elisei@arm.com>
---
 arm/selftest.c | 4 ----
 1 file changed, 4 deletions(-)

```
#### [PATCH v2 1/3] KVM: x86: always stop emulation on page faultThread-Topic: [PATCH v2 1/3] KVM: x86: always stop emulation on page fault
##### From: Jan Dakinevich <jan.dakinevich@virtuozzo.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Jan Dakinevich <jan.dakinevich@virtuozzo.com>
X-Patchwork-Id: 11119487
Return-Path: <SRS0=KojS=WY=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 13B9D14D5
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 28 Aug 2019 17:03:16 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id DF2B72339E
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 28 Aug 2019 17:03:15 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=virtuozzo.com header.i=@virtuozzo.com
 header.b="HEJ4FiAx"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726693AbfH1RDB (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 28 Aug 2019 13:03:01 -0400
Received: from mail-eopbgr140095.outbound.protection.outlook.com
 ([40.107.14.95]:48192
        "EHLO EUR01-VE1-obe.outbound.protection.outlook.com"
        rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org with ESMTP
        id S1726400AbfH1RDA (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 28 Aug 2019 13:03:00 -0400
ARC-Seal: i=1; a=rsa-sha256; s=arcselector9901; d=microsoft.com; cv=none;
 b=O1SgP3pt1F+VplJBID8OtUYTL2SoJYSHOPKvGldbsiKlFAp5b9Xgkf2Mp15Un2JqDUWPBK6VTmOjkLa2Hbv6hGbxQyGfznF2vifKbMPjJRcETozGhYtYdGvvdJTm484ZXzL+3walln30+CQFxKOcmYdDmgfJMq7NScc8Jk38kQ9MYldI+FuyKEtgxSTk4mSZrXJ7ferh151nnhX0SzADcVY9tfjCLwwg+dy45m5iUoesQv20kCy+Ms3OqggeBPhDT/4JvaVdfY6togZLHuwzwtudYwjUU0bw8wkgMcql1EQouklgebf6AgAHaolKIf94e1M6b8sHE9eUuPSAE4Lnvw==
ARC-Message-Signature: i=1; a=rsa-sha256; c=relaxed/relaxed; d=microsoft.com;
 s=arcselector9901;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=Wh3jtT+lXogQSO3KQAYL4qcU6PTMONzl/DOKLnMK8IM=;
 b=eq5aUk0VZ1tHDQiwGvzfTdJPoL0lxWcuBjXIqVt+mzPikUwK40oxD4ZLqoEoH26IsIsnO9tc8wL+9Ez0l/rqS4KNVqZpXxc7RxZGoESHCK1DgehNdJApicFucREDAyw8ZjcRaWMKyjlpwX7oHI/vrqpMHOlTBsDb7b3hh4Ff9CnZ6KEY/jIixUTz3laQsJ3QlQWe/gcFgRJFdt8sbVjI3hUlPf/5cvGC3AkA5KfkNFATL4FDi1ACAOTe/PC2WkhshXkoOR6o1cr4jNHnAoQZeTT5kSsLBc+eVS/+G8B5ZW8LymqQHlbYYxYem0nlWTtFU/TQ1biI/uxAZ6jsp7kHQA==
ARC-Authentication-Results: i=1; mx.microsoft.com 1; spf=pass
 smtp.mailfrom=virtuozzo.com; dmarc=pass action=none
 header.from=virtuozzo.com; dkim=pass header.d=virtuozzo.com; arc=none
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=virtuozzo.com;
 s=selector2;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=Wh3jtT+lXogQSO3KQAYL4qcU6PTMONzl/DOKLnMK8IM=;
 b=HEJ4FiAxcObqo2cRAyi/Jkyq2+mZUWfxpHTaKpsFsmsl20oD63L/AU98ROHZ3uyIE4wCbNU3dRso6PvTuuoSn30ryZ+bp1pcIrU8Wbqx759ddpnKgxodEDXKl4QGgpukyiytvRgwkKfQpPHnh85D5OPV2mRKIazQTgaz2WFWcic=
Received: from VI1PR08MB2782.eurprd08.prod.outlook.com (10.170.236.143) by
 VI1PR08MB3181.eurprd08.prod.outlook.com (52.133.15.144) with Microsoft SMTP
 Server (version=TLS1_2, cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id
 15.20.2199.19; Wed, 28 Aug 2019 17:02:55 +0000
Received: from VI1PR08MB2782.eurprd08.prod.outlook.com
 ([fe80::2969:e370:fb70:71a]) by VI1PR08MB2782.eurprd08.prod.outlook.com
 ([fe80::2969:e370:fb70:71a%3]) with mapi id 15.20.2178.023; Wed, 28 Aug 2019
 17:02:55 +0000
From: Jan Dakinevich <jan.dakinevich@virtuozzo.com>
To: "linux-kernel@vger.kernel.org" <linux-kernel@vger.kernel.org>
CC: Jan Dakinevich <jan.dakinevich@virtuozzo.com>,
 Denis Lunev <den@virtuozzo.com>, Roman Kagan <rkagan@virtuozzo.com>,
 Denis Plotnikov <dplotnikov@virtuozzo.com>,
 Paolo Bonzini <pbonzini@redhat.com>,
 =?iso-8859-2?q?Radim_Kr=E8m=E1=F8?= <rkrcmar@redhat.com>,
 Sean Christopherson <sean.j.christopherson@intel.com>,
 Vitaly Kuznetsov <vkuznets@redhat.com>, Wanpeng Li <wanpengli@tencent.com>,
 Jim Mattson <jmattson@google.com>, Joerg Roedel <joro@8bytes.org>,
 Thomas Gleixner <tglx@linutronix.de>, Ingo Molnar <mingo@redhat.com>,
 Borislav Petkov <bp@alien8.de>, "H. Peter Anvin" <hpa@zytor.com>,
 "x86@kernel.org" <x86@kernel.org>,
 "kvm@vger.kernel.org" <kvm@vger.kernel.org>
Subject: [PATCH v2 1/3] KVM: x86: always stop emulation on page fault
Thread-Topic: [PATCH v2 1/3] KVM: x86: always stop emulation on page fault
Thread-Index: AQHVXcJv3UD3akQ2HkiJEaqhuDTLcQ==
Date: Wed, 28 Aug 2019 17:02:55 +0000
Message-ID: <1567011759-9969-2-git-send-email-jan.dakinevich@virtuozzo.com>
References: <1567011759-9969-1-git-send-email-jan.dakinevich@virtuozzo.com>
In-Reply-To: <1567011759-9969-1-git-send-email-jan.dakinevich@virtuozzo.com>
Accept-Language: en-US
Content-Language: en-US
X-MS-Has-Attach: 
X-MS-TNEF-Correlator: 
x-clientproxiedby: HE1PR05CA0154.eurprd05.prod.outlook.com
 (2603:10a6:7:28::41) To VI1PR08MB2782.eurprd08.prod.outlook.com
 (2603:10a6:802:19::15)
authentication-results: spf=none (sender IP is )
 smtp.mailfrom=jan.dakinevich@virtuozzo.com;
x-ms-exchange-messagesentrepresentingtype: 1
x-mailer: git-send-email 2.1.4
x-originating-ip: [185.231.240.5]
x-ms-publictraffictype: Email
x-ms-office365-filtering-correlation-id: b76d02b3-7759-4981-aafe-08d72bd991bd
x-microsoft-antispam: 
 BCL:0;PCL:0;RULEID:(2390118)(7020095)(4652040)(8989299)(4534185)(4627221)(201703031133081)(201702281549075)(8990200)(5600166)(711020)(4605104)(1401327)(2017052603328)(7193020);SRVR:VI1PR08MB3181;
x-ms-traffictypediagnostic: VI1PR08MB3181:
x-ms-exchange-transport-forked: True
x-microsoft-antispam-prvs: 
 <VI1PR08MB3181FC1ABB7F3A3CA1650A218AA30@VI1PR08MB3181.eurprd08.prod.outlook.com>
x-ms-oob-tlc-oobclassifiers: OLM:1284;
x-forefront-prvs: 014304E855
x-forefront-antispam-report: 
 SFV:NSPM;SFS:(10019020)(376002)(366004)(346002)(39850400004)(136003)(396003)(189003)(199004)(478600001)(26005)(4326008)(8936002)(14444005)(186003)(102836004)(3846002)(256004)(476003)(44832011)(6486002)(66066001)(6512007)(305945005)(2906002)(2501003)(446003)(86362001)(6436002)(6116002)(66446008)(8676002)(66946007)(64756008)(66556008)(76176011)(66476007)(316002)(7736002)(81156014)(52116002)(25786009)(81166006)(71190400001)(71200400001)(6506007)(486006)(386003)(14454004)(53936002)(99286004)(2616005)(5660300002)(6916009)(2351001)(54906003)(5640700003)(36756003)(50226002)(11346002)(7416002);DIR:OUT;SFP:1102;SCL:1;SRVR:VI1PR08MB3181;H:VI1PR08MB2782.eurprd08.prod.outlook.com;FPR:;SPF:None;LANG:en;PTR:InfoNoRecords;MX:1;A:1;
received-spf: None (protection.outlook.com: virtuozzo.com does not designate
 permitted sender hosts)
x-ms-exchange-senderadcheck: 1
x-microsoft-antispam-message-info: 
 0MKtYWJkeb3OZ/91KKHEedEMwjJu7z+alGdFdqTmrl/clHEYXaka8grIbTD5SsCEP+fctdOZ2NruFikW3bVCbUXqu/1oavhA9Ccqx1rRqiBQp9HoHiswG0Cu8gRE64GoUFt5Ut9r1jidcRPrc6FlEXOnTvwgytwg9IPSRDEqwna2lFl4lbDm1YhAh7u9z7Z4cj5+6N20XKtux9ob6yQNiurOHbJC896sQx/4AmaeDktsUMW2GOyNklmiSTQvJ+PhEdl6d1XOurtPNAfnabtGtjY5V2Ezp96TKZH1QKtR6Cd+Vmwt5EGGgpmmoM/J+oStyxn+Jik5mDpzNh0xtoCo16wHgrXO9/w64a9YYEWcP/FtmCXYKHM8OCEAdlr8mcJONtiYbJAHVGXGzd1dILBtSxfcYorgHWt+wkWWbcJwyHc=
Content-Type: text/plain; charset="iso-8859-2"
MIME-Version: 1.0
X-OriginatorOrg: virtuozzo.com
X-MS-Exchange-CrossTenant-Network-Message-Id: 
 b76d02b3-7759-4981-aafe-08d72bd991bd
X-MS-Exchange-CrossTenant-originalarrivaltime: 28 Aug 2019 17:02:55.3276
 (UTC)
X-MS-Exchange-CrossTenant-fromentityheader: Hosted
X-MS-Exchange-CrossTenant-id: 0bc7f26d-0264-416e-a6fc-8352af79c58f
X-MS-Exchange-CrossTenant-mailboxtype: HOSTED
X-MS-Exchange-CrossTenant-userprincipalname: 
 t83KJU1zpEBoq+zSBDdFd//2pN8xrqtCY+Dziha7dgHyXOURf3f1BL9AwlJGbkPS+Rbae747Pe2wp1q0ETBoCt4HjmVhJEovtXuQCT8m+Bw=
X-MS-Exchange-Transport-CrossTenantHeadersStamped: VI1PR08MB3181
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

inject_emulated_exception() returns true if and only if nested page
fault happens. However, page fault can come from guest page tables
walk, either nested or not nested. In both cases we should stop an
attempt to read under RIP and give guest to step over its own page
fault handler.

Fixes: 6ea6e84 ("KVM: x86: inject exceptions produced by x86_decode_insn")
Cc: Denis Lunev <den@virtuozzo.com>
Cc: Roman Kagan <rkagan@virtuozzo.com>
Cc: Denis Plotnikov <dplotnikov@virtuozzo.com>
Signed-off-by: Jan Dakinevich <jan.dakinevich@virtuozzo.com>
---
 arch/x86/kvm/x86.c | 4 +++-
 1 file changed, 3 insertions(+), 1 deletion(-)

```
#### [GIT PULL] arm64: Fixes for -rc7
##### From: Will Deacon <will@kernel.org>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Will Deacon <will@kernel.org>
X-Patchwork-Id: 11119541
Return-Path: <SRS0=KojS=WY=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 8437B1398
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 28 Aug 2019 17:32:43 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 637392339E
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 28 Aug 2019 17:32:43 +0000 (UTC)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple; d=kernel.org;
	s=default; t=1567013563;
	bh=g4OCrTwVa9bGHj9tnxdp3jF6CcqJ8f1XiF9bSopoU3g=;
	h=Date:From:To:Cc:Subject:List-ID:From;
	b=X2/cz9SbpZ95ogj2KSZ47x+PNdIwXzok2/2eqyEz9dE3pui01kkC7Qge0nKGLK2eh
	 nGfZ+mloAunpX6Q7tNE00IhhZYAg7mshakgOavmmNiMUgvfWAWBDwhnqmA2x1F4Nsy
	 BMODNSSg2nBnRlreZSyNiiGzCwH4ayKEXfyv8sQU=
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726623AbfH1Rcj (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 28 Aug 2019 13:32:39 -0400
Received: from mail.kernel.org ([198.145.29.99]:41368 "EHLO mail.kernel.org"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726315AbfH1Rcj (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 28 Aug 2019 13:32:39 -0400
Received: from willie-the-truck (236.31.169.217.in-addr.arpa [217.169.31.236])
        (using TLSv1.2 with cipher ECDHE-RSA-AES256-GCM-SHA384 (256/256 bits))
        (No client certificate requested)
        by mail.kernel.org (Postfix) with ESMTPSA id E5F3222CF8;
        Wed, 28 Aug 2019 17:32:36 +0000 (UTC)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple; d=kernel.org;
        s=default; t=1567013558;
        bh=g4OCrTwVa9bGHj9tnxdp3jF6CcqJ8f1XiF9bSopoU3g=;
        h=Date:From:To:Cc:Subject:From;
        b=a3rf4aOlbouRot3H7YWNOPjdMdjcSi4kuaOwn9XEDNdNwloLChRW0NRPbuHXR9PXS
         C6MgP0i2QWJTMl2Pk08Rc1N/ScAAM4oPGmcweVwXtZ/63yqisTC31BDdQGAwJFmL4V
         GPPOqjrUiOAnRHK07SzjdAwi+63PljkdrwKkNN/A=
Date: Wed, 28 Aug 2019 18:32:33 +0100
From: Will Deacon <will@kernel.org>
To: torvalds@linux-foundation.org
Cc: catalin.marinas@arm.com, marc.zyngier@arm.com, pbonzini@redhat.com,
        rkrcmar@redhat.com, linux-arm-kernel@lists.infradead.org,
        linux-kernel@vger.kernel.org, kvm@vger.kernel.org,
        kvmarm@lists.cs.columbia.edu
Subject: [GIT PULL] arm64: Fixes for -rc7
Message-ID: <20190828173233.zqwm5nd4p5xa4jxi@willie-the-truck>
MIME-Version: 1.0
Content-Type: text/plain; charset=us-ascii
Content-Disposition: inline
User-Agent: NeoMutt/20170113 (1.7.2)
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Hi Linus,

Hot on the heels of our last set of fixes are a few more for -rc7. Two
of them are fixing issues with our virtual interrupt controller
implementation in KVM/arm, while the other is a longstanding but
straightforward kallsyms fix which was been acked by Masami and resolves
an initialisation failure in kprobes observed on arm64.

Please pull, thanks.

Will

--->8

The following changes since commit b6143d10d23ebb4a77af311e8b8b7f019d0163e6:

  arm64: ftrace: Ensure module ftrace trampoline is coherent with I-side (2019-08-16 17:40:03 +0100)

are available in the git repository at:

  git://git.kernel.org/pub/scm/linux/kernel/git/arm64/linux.git tags/arm64-fixes

for you to fetch changes up to 82e40f558de566fdee214bec68096bbd5e64a6a4:

  KVM: arm/arm64: vgic-v2: Handle SGI bits in GICD_I{S,C}PENDR0 as WI (2019-08-28 11:21:42 +0100)

----------------------------------------------------------------
arm64 fixes for -rc7

- Fix GICv2 emulation bug (KVM)

- Fix deadlock in virtual GIC interrupt injection code (KVM)

- Fix kprobes blacklist init failure due to broken kallsyms lookup

----------------------------------------------------------------
Heyi Guo (1):
      KVM: arm/arm64: vgic: Fix potential deadlock when ap_list is long

Marc Zyngier (2):
      kallsyms: Don't let kallsyms_lookup_size_offset() fail on retrieving the first symbol
      KVM: arm/arm64: vgic-v2: Handle SGI bits in GICD_I{S,C}PENDR0 as WI

 kernel/kallsyms.c             |  6 ++++--
 virt/kvm/arm/vgic/vgic-mmio.c | 18 ++++++++++++++++++
 virt/kvm/arm/vgic/vgic-v2.c   |  5 ++++-
 virt/kvm/arm/vgic/vgic-v3.c   |  5 ++++-
 virt/kvm/arm/vgic/vgic.c      |  7 +++++++
 5 files changed, 37 insertions(+), 4 deletions(-)
```
#### [kvm-unit-tests PATCH] x86: VMX: INVEPT after modifying PA mapping in ept_untwiddle
##### From: Oliver Upton <oupton@google.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Oliver Upton <oupton@google.com>
X-Patchwork-Id: 11118213
Return-Path: <SRS0=KojS=WY=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 0E3C9112C
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 28 Aug 2019 08:29:41 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id E2A20235EE
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 28 Aug 2019 08:29:40 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=google.com header.i=@google.com
 header.b="vTrZtWvS"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726297AbfH1I3j (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 28 Aug 2019 04:29:39 -0400
Received: from mail-pf1-f201.google.com ([209.85.210.201]:39494 "EHLO
        mail-pf1-f201.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726253AbfH1I3j (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 28 Aug 2019 04:29:39 -0400
Received: by mail-pf1-f201.google.com with SMTP id n186so1510959pfn.6
        for <kvm@vger.kernel.org>; Wed, 28 Aug 2019 01:29:39 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=date:message-id:mime-version:subject:from:to:cc;
        bh=m26isUzfYfS+tZR7e2mo6xjWcRmXsDiHK/VLJs2n4q4=;
        b=vTrZtWvSHSOXfQNqpOTgwRZteVPk4jzMjJNCA0QBgY8pHQK757xXFgPhJlao4BtxhA
         7V5XpImMMJrHMsPqhCyxNW9ce2F7t1ON5oP9LlbMcBcA/XoGNXH00GllYyL9GB1tSQUi
         70n1y76nfQeVZdTdc5fOd2D1YISsz5ZYPRdu8U0XQD5LCFvL5fQoSIG4AMg2siYfBGmk
         EpjExrVJoMf7PJ5DUZv7eWbFWw4XSiRA3uwTMNr3WHH9+DKovYusmnC+2/fDm+e7RO0J
         qNuNcLh1hhQAaPCf1lrFV6n5J7ujY/+pLl79Nan1il047DKIq1FxWTPMw4bD2UZ5WVaA
         7uYQ==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:date:message-id:mime-version:subject:from:to:cc;
        bh=m26isUzfYfS+tZR7e2mo6xjWcRmXsDiHK/VLJs2n4q4=;
        b=dRP0mU0yKSA4JH7FXufHRyBHy8H12W+nMIP2/xaZKlxIbMETH7C7kq08v1ZY4+8pzJ
         0/2LUea8Y7XqaWammYi4b2CqAe69p4FG41yNFbBeGwFS79+Ud2jmnZjDl31oxsCbXxO+
         wuGW2Vtbr84WPzzk7uAcL+FQkRQXeY69F3w0iAtxAlWd4NUwvQiAlOwaHd5+scCpFJIt
         EVs2yKMh0gTnaZgqmD3Hnib4y3cnoHHcCBMy4RWn/8Q8Pm7WIbLdnnNDu3uoT4r+xd/5
         lzRUzstyesrdmhyn5hQO5yBfMaM15m08mrTSJX/5uM3QaV6RYrppseUk5rXqKw4DNvTD
         dSzA==
X-Gm-Message-State: APjAAAVJfoKMhD5K8AiqQ+SEkHPAgkkcB0a75rHWxGeVyccskpT4D9p/
        r7F289qDDwG2RRi0Amaip2T1p2Z4kFtjjH4zaPttFuLq44Npy5NVnST6WXZgv9LwMsylvEQ+J/q
        163GC8lz366if+lMkKZR1J0NaWLPT0cAlKx7K1IHYuRJePTK+P4uC3H7zgA==
X-Google-Smtp-Source: 
 APXvYqwCQnMr1bdOSCslVxdaQlr8w4xWK0Te2STYsUL7nAN1xaT4pCWNXezZ2HyCYSBW56tkfooXy7cKM3c=
X-Received: by 2002:a63:2a87:: with SMTP id
 q129mr2470692pgq.101.1566980978058;
 Wed, 28 Aug 2019 01:29:38 -0700 (PDT)
Date: Wed, 28 Aug 2019 01:29:00 -0700
Message-Id: <20190828082900.88609-1-oupton@google.com>
Mime-Version: 1.0
X-Mailer: git-send-email 2.23.0.187.g17f5b7556c-goog
Subject: [kvm-unit-tests PATCH] x86: VMX: INVEPT after modifying PA mapping in
 ept_untwiddle
From: Oliver Upton <oupton@google.com>
To: kvm@vger.kernel.org, Paolo Bonzini <pbonzini@redhat.com>, "
	=?utf-8?b?UmFkaW0gS3LEjW3DocWZ?= " <rkrcmar@redhat.com>
Cc: Jim Mattson <jmattson@google.com>,
        Oliver Upton <oupton@google.com>,
        Peter Shier <pshier@google.com>
Content-Type: text/plain; charset="UTF-8"
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

ept_untwiddle modifies a PA mapping in the EPT paging structure.
According to the SDM 28.3.3.4, "Software should use the INVEPT
instruction with the "single-context" INVEPT type after making any of
the following changes to an EPT paging-structure entry ... Changing
the physical address in bits 51:12".

Suggested-by: Peter Shier <pshier@google.com>
Signed-off-by: Oliver Upton <oupton@google.com>
---
 x86/vmx_tests.c | 1 +
 1 file changed, 1 insertion(+)

```
#### [PATCH v2 1/2] KVM: x86: svm: remove unneeded nested_enable_evmcs() hook
##### From: Vitaly Kuznetsov <vkuznets@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Vitaly Kuznetsov <vkuznets@redhat.com>
X-Patchwork-Id: 11118137
Return-Path: <SRS0=KojS=WY=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 3782B1800
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 28 Aug 2019 07:59:14 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 21541205C9
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 28 Aug 2019 07:59:14 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726566AbfH1H7M (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 28 Aug 2019 03:59:12 -0400
Received: from mx1.redhat.com ([209.132.183.28]:48746 "EHLO mx1.redhat.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726368AbfH1H7K (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 28 Aug 2019 03:59:10 -0400
Received: from mail-wr1-f72.google.com (mail-wr1-f72.google.com
 [209.85.221.72])
        (using TLSv1.2 with cipher ECDHE-RSA-AES128-GCM-SHA256 (128/128 bits))
        (No client certificate requested)
        by mx1.redhat.com (Postfix) with ESMTPS id 2A3F9C0568FA
        for <kvm@vger.kernel.org>; Wed, 28 Aug 2019 07:59:10 +0000 (UTC)
Received: by mail-wr1-f72.google.com with SMTP id k15so905166wrw.18
        for <kvm@vger.kernel.org>; Wed, 28 Aug 2019 00:59:10 -0700 (PDT)
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:in-reply-to
         :references:mime-version:content-transfer-encoding;
        bh=lBboHqcZl+GeeqMr+xhVz73awkXrj2sOIO6d13g0iRE=;
        b=hwAgKVbVCk0yCwvqgeT2jo45OSCNg6Iuww63xF0YVrPMXdt32fNAZ6iI4IfRsrv6/y
         PYnSI+ZqZf9YgP2zA21x4YH/oFfWtbBaIWAlOChFAj7SbfkOXZQqMQTg2i2fme7IsCR9
         AHZ84iI2FCJOynlGpyF+UPEDni1j6CY4GJeHY19MOMxXSsA/1cvAlu0Q/JrZQGwhtXoL
         B474D15tvlFQ7n/Ly8jhgkTUQWrAcLAv+PT22Qf/mQXRaOwS+Es3mPTWtf6S3KZgWWMW
         rv26LMqjGgFS3ltGBXO2FEqvZtqAFyV7HBvDJ63i8UCz9IEpXkF0hZP//Lk+WBfnls0U
         B1fw==
X-Gm-Message-State: APjAAAVfvC2d9GTULm2ZpAXIKHEV8bNWfJxx2MjCugDZdbCDGTmydAMp
        VKdFPu60cujnujtX7IJwE5umTRVulis1xv2JTHIDodDsjrlIs1h6Tsud6TFsQfYII530O+qEtDa
        Dwo/d6cKQs2Pn
X-Received: by 2002:adf:f18c:: with SMTP id h12mr2713824wro.47.1566979148632;
        Wed, 28 Aug 2019 00:59:08 -0700 (PDT)
X-Google-Smtp-Source: 
 APXvYqyg75w3y/I6ECh2ht91PCD+cPI1HSKMT6eKRHsTiLiLoq2ckp9NA9BsenuangkEk7V6n9c+3A==
X-Received: by 2002:adf:f18c:: with SMTP id h12mr2713808wro.47.1566979148444;
        Wed, 28 Aug 2019 00:59:08 -0700 (PDT)
Received: from vitty.brq.redhat.com (nat-pool-brq-t.redhat.com.
 [213.175.37.10])
        by smtp.gmail.com with ESMTPSA id
 a190sm2448469wme.8.2019.08.28.00.59.07
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Wed, 28 Aug 2019 00:59:07 -0700 (PDT)
From: Vitaly Kuznetsov <vkuznets@redhat.com>
To: kvm@vger.kernel.org
Cc: linux-kernel@vger.kernel.org, Paolo Bonzini <pbonzini@redhat.com>,
	=?utf-8?b?UmFkaW0gS3LEjW3DocWZ?= <rkrcmar@redhat.com>,
 Joerg Roedel <joro@8bytes.org>, Jim Mattson <jmattson@google.com>,
 Sean Christopherson <sean.j.christopherson@intel.com>,
 Roman Kagan <rkagan@virtuozzo.com>
Subject: [PATCH v2 1/2] KVM: x86: svm: remove unneeded nested_enable_evmcs()
 hook
Date: Wed, 28 Aug 2019 09:59:04 +0200
Message-Id: <20190828075905.24744-2-vkuznets@redhat.com>
X-Mailer: git-send-email 2.20.1
In-Reply-To: <20190828075905.24744-1-vkuznets@redhat.com>
References: <20190828075905.24744-1-vkuznets@redhat.com>
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Since commit 5158917c7b019 ("KVM: x86: nVMX: Allow nested_enable_evmcs to
be NULL") the code in x86.c is prepared to see nested_enable_evmcs being
NULL and in VMX case it actually is when nesting is disabled. Remove the
unneeded stub from SVM code.

Signed-off-by: Vitaly Kuznetsov <vkuznets@redhat.com>
Reviewed-by: Jim Mattson <jmattson@google.com>
---
 arch/x86/kvm/svm.c | 9 +--------
 1 file changed, 1 insertion(+), 8 deletions(-)

```
#### [PULL 1/1] vfio-ccw: add some logging
##### From: Cornelia Huck <cohuck@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Cornelia Huck <cohuck@redhat.com>
X-Patchwork-Id: 11119353
Return-Path: <SRS0=KojS=WY=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id DA53D1399
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 28 Aug 2019 15:57:24 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id AF96122CF8
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 28 Aug 2019 15:57:24 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726896AbfH1P5X (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 28 Aug 2019 11:57:23 -0400
Received: from mx1.redhat.com ([209.132.183.28]:34458 "EHLO mx1.redhat.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726400AbfH1P5X (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 28 Aug 2019 11:57:23 -0400
Received: from smtp.corp.redhat.com (int-mx06.intmail.prod.int.phx2.redhat.com
 [10.5.11.16])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mx1.redhat.com (Postfix) with ESMTPS id 8AFE8882EA;
        Wed, 28 Aug 2019 15:57:22 +0000 (UTC)
Received: from localhost (dhcp-192-222.str.redhat.com [10.33.192.222])
        by smtp.corp.redhat.com (Postfix) with ESMTPS id 148F05C1D6;
        Wed, 28 Aug 2019 15:57:21 +0000 (UTC)
From: Cornelia Huck <cohuck@redhat.com>
To: Heiko Carstens <heiko.carstens@de.ibm.com>,
        Vasily Gorbik <gor@linux.ibm.com>,
        Christian Borntraeger <borntraeger@de.ibm.com>
Cc: Eric Farman <farman@linux.ibm.com>,
        Halil Pasic <pasic@linux.ibm.com>, linux-s390@vger.kernel.org,
        kvm@vger.kernel.org, Cornelia Huck <cohuck@redhat.com>
Subject: [PULL 1/1] vfio-ccw: add some logging
Date: Wed, 28 Aug 2019 17:57:16 +0200
Message-Id: <20190828155716.22809-2-cohuck@redhat.com>
In-Reply-To: <20190828155716.22809-1-cohuck@redhat.com>
References: <20190828155716.22809-1-cohuck@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.16
X-Greylist: Sender IP whitelisted,
 not delayed by milter-greylist-4.5.16 (mx1.redhat.com [10.5.110.28]);
 Wed, 28 Aug 2019 15:57:22 +0000 (UTC)
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Usually, the common I/O layer logs various things into the s390
cio debug feature, which has been very helpful in the past when
looking at crash dumps. As vfio-ccw devices unbind from the
standard I/O subchannel driver, we lose some information there.

Let's introduce some vfio-ccw debug features and log some things
there. (Unfortunately we cannot reuse the cio debug feature from
a module.)

Message-Id: <20190816151505.9853-2-cohuck@redhat.com>
Reviewed-by: Eric Farman <farman@linux.ibm.com>
Signed-off-by: Cornelia Huck <cohuck@redhat.com>
---
 drivers/s390/cio/vfio_ccw_drv.c     | 50 ++++++++++++++++++++++++++--
 drivers/s390/cio/vfio_ccw_fsm.c     | 51 ++++++++++++++++++++++++++++-
 drivers/s390/cio/vfio_ccw_ops.c     | 10 ++++++
 drivers/s390/cio/vfio_ccw_private.h | 17 ++++++++++
 4 files changed, 124 insertions(+), 4 deletions(-)

```
#### [RFC v3] vhost: introduce mdev based hardware vhost backend
##### From: Tiwei Bie <tiwei.bie@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Tiwei Bie <tiwei.bie@intel.com>
X-Patchwork-Id: 11117785
Return-Path: <SRS0=KojS=WY=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id F31BC1399
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 28 Aug 2019 05:40:45 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id C075722CF8
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 28 Aug 2019 05:40:45 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726225AbfH1Fkk (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 28 Aug 2019 01:40:40 -0400
Received: from mga18.intel.com ([134.134.136.126]:51848 "EHLO mga18.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726052AbfH1Fkk (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 28 Aug 2019 01:40:40 -0400
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from orsmga006.jf.intel.com ([10.7.209.51])
  by orsmga106.jf.intel.com with ESMTP/TLS/DHE-RSA-AES256-GCM-SHA384;
 27 Aug 2019 22:40:39 -0700
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.64,440,1559545200";
   d="scan'208";a="185513640"
Received: from dpdk-virtio-tbie-2.sh.intel.com ([10.67.104.71])
  by orsmga006.jf.intel.com with ESMTP; 27 Aug 2019 22:40:36 -0700
From: Tiwei Bie <tiwei.bie@intel.com>
To: mst@redhat.com, jasowang@redhat.com, alex.williamson@redhat.com,
        maxime.coquelin@redhat.com
Cc: linux-kernel@vger.kernel.org, kvm@vger.kernel.org,
        virtualization@lists.linux-foundation.org, netdev@vger.kernel.org,
        dan.daly@intel.com, cunming.liang@intel.com,
        zhihong.wang@intel.com, lingshan.zhu@intel.com, tiwei.bie@intel.com
Subject: [RFC v3] vhost: introduce mdev based hardware vhost backend
Date: Wed, 28 Aug 2019 13:37:12 +0800
Message-Id: <20190828053712.26106-1-tiwei.bie@intel.com>
X-Mailer: git-send-email 2.17.1
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Details about this can be found here:

https://lwn.net/Articles/750770/

What's new in this version
==========================

There are three choices based on the discussion [1] in RFC v2:

> #1. We expose a VFIO device, so we can reuse the VFIO container/group
>     based DMA API and potentially reuse a lot of VFIO code in QEMU.
>
>     But in this case, we have two choices for the VFIO device interface
>     (i.e. the interface on top of VFIO device fd):
>
>     A) we may invent a new vhost protocol (as demonstrated by the code
>        in this RFC) on VFIO device fd to make it work in VFIO's way,
>        i.e. regions and irqs.
>
>     B) Or as you proposed, instead of inventing a new vhost protocol,
>        we can reuse most existing vhost ioctls on the VFIO device fd
>        directly. There should be no conflicts between the VFIO ioctls
>        (type is 0x3B) and VHOST ioctls (type is 0xAF) currently.
>
> #2. Instead of exposing a VFIO device, we may expose a VHOST device.
>     And we will introduce a new mdev driver vhost-mdev to do this.
>     It would be natural to reuse the existing kernel vhost interface
>     (ioctls) on it as much as possible. But we will need to invent
>     some APIs for DMA programming (reusing VHOST_SET_MEM_TABLE is a
>     choice, but it's too heavy and doesn't support vIOMMU by itself).

This version is more like a quick PoC to try Jason's proposal on
reusing vhost ioctls. And the second way (#1/B) in above three
choices was chosen in this version to demonstrate the idea quickly.

Now the userspace API looks like this:

- VFIO's container/group based IOMMU API is used to do the
  DMA programming.

- Vhost's existing ioctls are used to setup the device.

And the device will report device_api as "vfio-vhost".

Note that, there are dirty hacks in this version. If we decide to
go this way, some refactoring in vhost.c/vhost.h may be needed.

PS. The direct mapping of the notify registers isn't implemented
    in this version.

[1] https://lkml.org/lkml/2019/7/9/101

Signed-off-by: Tiwei Bie <tiwei.bie@intel.com>
---
 drivers/vhost/Kconfig      |   9 +
 drivers/vhost/Makefile     |   3 +
 drivers/vhost/mdev.c       | 382 +++++++++++++++++++++++++++++++++++++
 include/linux/vhost_mdev.h |  58 ++++++
 include/uapi/linux/vfio.h  |   2 +
 include/uapi/linux/vhost.h |   8 +
 6 files changed, 462 insertions(+)
 create mode 100644 drivers/vhost/mdev.c
 create mode 100644 include/linux/vhost_mdev.h

```
#### [kvm-unit-tests PATCH v2 1/4] s390x: Move pfmf to lib and make address void
##### From: Janosch Frank <frankja@linux.ibm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Janosch Frank <frankja@linux.ibm.com>
X-Patchwork-Id: 11118741
Return-Path: <SRS0=KojS=WY=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id DC931112C
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 28 Aug 2019 11:36:32 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id BDD2A22CF8
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 28 Aug 2019 11:36:32 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726413AbfH1Lgc (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 28 Aug 2019 07:36:32 -0400
Received: from mx0b-001b2d01.pphosted.com ([148.163.158.5]:35156 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S1726339AbfH1Lga (ORCPT
        <rfc822;kvm@vger.kernel.org>); Wed, 28 Aug 2019 07:36:30 -0400
Received: from pps.filterd (m0098419.ppops.net [127.0.0.1])
        by mx0b-001b2d01.pphosted.com (8.16.0.27/8.16.0.27) with SMTP id
 x7SBX6nN071185
        for <kvm@vger.kernel.org>; Wed, 28 Aug 2019 07:36:29 -0400
Received: from e06smtp04.uk.ibm.com (e06smtp04.uk.ibm.com [195.75.94.100])
        by mx0b-001b2d01.pphosted.com with ESMTP id 2unpue563w-1
        (version=TLSv1.2 cipher=AES256-GCM-SHA384 bits=256 verify=NOT)
        for <kvm@vger.kernel.org>; Wed, 28 Aug 2019 07:36:29 -0400
Received: from localhost
        by e06smtp04.uk.ibm.com with IBM ESMTP SMTP Gateway: Authorized Use
 Only! Violators will be prosecuted
        for <kvm@vger.kernel.org> from <frankja@linux.ibm.com>;
        Wed, 28 Aug 2019 12:36:27 +0100
Received: from b06cxnps4074.portsmouth.uk.ibm.com (9.149.109.196)
        by e06smtp04.uk.ibm.com (192.168.101.134) with IBM ESMTP SMTP Gateway:
 Authorized Use Only! Violators will be prosecuted;
        (version=TLSv1/SSLv3 cipher=AES256-GCM-SHA384 bits=256/256)
        Wed, 28 Aug 2019 12:36:24 +0100
Received: from b06wcsmtp001.portsmouth.uk.ibm.com
 (b06wcsmtp001.portsmouth.uk.ibm.com [9.149.105.160])
        by b06cxnps4074.portsmouth.uk.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id x7SBaNbj46006330
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Wed, 28 Aug 2019 11:36:23 GMT
Received: from b06wcsmtp001.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 3AFA7A4054;
        Wed, 28 Aug 2019 11:36:23 +0000 (GMT)
Received: from b06wcsmtp001.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 79DD8A4067;
        Wed, 28 Aug 2019 11:36:22 +0000 (GMT)
Received: from localhost.localdomain (unknown [9.152.224.131])
        by b06wcsmtp001.portsmouth.uk.ibm.com (Postfix) with ESMTP;
        Wed, 28 Aug 2019 11:36:22 +0000 (GMT)
From: Janosch Frank <frankja@linux.ibm.com>
To: kvm@vger.kernel.org
Cc: linux-s390@vger.kernel.org, david@redhat.com, thuth@redhat.com
Subject: [kvm-unit-tests PATCH v2 1/4] s390x: Move pfmf to lib and make
 address void
Date: Wed, 28 Aug 2019 13:36:12 +0200
X-Mailer: git-send-email 2.17.0
In-Reply-To: <20190828113615.4769-1-frankja@linux.ibm.com>
References: <20190828113615.4769-1-frankja@linux.ibm.com>
X-TM-AS-GCONF: 00
x-cbid: 19082811-0016-0000-0000-000002A3DC73
X-IBM-AV-DETECTION: SAVI=unused REMOTE=unused XFE=unused
x-cbparentid: 19082811-0017-0000-0000-000033042C99
Message-Id: <20190828113615.4769-2-frankja@linux.ibm.com>
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:,,
 definitions=2019-08-28_05:,,
 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 priorityscore=1501
 malwarescore=0 suspectscore=1 phishscore=0 bulkscore=0 spamscore=0
 clxscore=1015 lowpriorityscore=0 mlxscore=0 impostorscore=0
 mlxlogscore=902 adultscore=0 classifier=spam adjust=0 reason=mlx
 scancount=1 engine=8.0.1-1906280000 definitions=main-1908280124
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

It's needed by other tests soon.

Signed-off-by: Janosch Frank <frankja@linux.ibm.com>
Reviewed-by: Thomas Huth <thuth@redhat.com>
---
 lib/s390x/asm/mem.h | 31 ++++++++++++++++++++++++
 s390x/pfmf.c        | 57 +++++++++++----------------------------------
 2 files changed, 44 insertions(+), 44 deletions(-)

```
#### [PATCH v1] cpuidle-haltpoll: vcpu hotplug support
##### From: Joao Martins <joao.m.martins@oracle.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Joao Martins <joao.m.martins@oracle.com>
X-Patchwork-Id: 11119669
Return-Path: <SRS0=KojS=WY=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 626AE1398
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 28 Aug 2019 18:58:33 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 3542E22CF8
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 28 Aug 2019 18:58:33 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=oracle.com header.i=@oracle.com
 header.b="dXBgCddk"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727046AbfH1S63 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 28 Aug 2019 14:58:29 -0400
Received: from aserp2120.oracle.com ([141.146.126.78]:48026 "EHLO
        aserp2120.oracle.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726883AbfH1S62 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 28 Aug 2019 14:58:28 -0400
Received: from pps.filterd (aserp2120.oracle.com [127.0.0.1])
        by aserp2120.oracle.com (8.16.0.27/8.16.0.27) with SMTP id
 x7SIsNP5149828;
        Wed, 28 Aug 2019 18:57:10 GMT
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=oracle.com;
 h=from : to : cc :
 subject : date : message-id : mime-version : content-type :
 content-transfer-encoding; s=corp-2019-08-05;
 bh=DHX8EJq2diorjBQuEzBHm3f716yk934EjUN3J/yyUPg=;
 b=dXBgCddkZg8k1DcUxkjdn2QHj5PC0AAUl8Shme2Czg6WA6JlI0V6DjX/DU7/eY+GXYt3
 MndMKu3XtjVYkorOuwMwwuHBL4b1IZp2upEPibEP+nZxNJH2mQ0oWtqjfeRuvAvwBUMw
 74PrOROBxNCO7UhZVXceXMAvD1FJTEb2or665ZbdB6Vn1pN0dykOMAxa8X+0wTIcqNpV
 QeB/Jr+mh79lni7WuMkJk1nVeLZhmgVxy5oMbS/O588EMssnJ/VL4upf+W7t5179e0MK
 5kvldr9OoY7TJEwxSW4cJUW5/pd9R8g03d/htQBzK8xAM+CzJhfGcrC2iYc2vJD/e6wu jA==
Received: from userp3030.oracle.com (userp3030.oracle.com [156.151.31.80])
        by aserp2120.oracle.com with ESMTP id 2uny3903yh-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Wed, 28 Aug 2019 18:57:10 +0000
Received: from pps.filterd (userp3030.oracle.com [127.0.0.1])
        by userp3030.oracle.com (8.16.0.27/8.16.0.27) with SMTP id
 x7SIrLqI078794;
        Wed, 28 Aug 2019 18:57:09 GMT
Received: from aserv0122.oracle.com (aserv0122.oracle.com [141.146.126.236])
        by userp3030.oracle.com with ESMTP id 2unvtxq6kf-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Wed, 28 Aug 2019 18:57:09 +0000
Received: from abhmp0009.oracle.com (abhmp0009.oracle.com [141.146.116.15])
        by aserv0122.oracle.com (8.14.4/8.14.4) with ESMTP id x7SIv7gv030518;
        Wed, 28 Aug 2019 18:57:07 GMT
Received: from paddy.uk.oracle.com (/10.175.206.216)
        by default (Oracle Beehive Gateway v4.0)
        with ESMTP ; Wed, 28 Aug 2019 11:57:06 -0700
From: Joao Martins <joao.m.martins@oracle.com>
To: kvm@vger.kernel.org
Cc: Joao Martins <joao.m.martins@oracle.com>,
 Marcelo Tosatti <mtosatti@redhat.com>, linux-kernel@vger.kernel.org,
 Paolo Bonzini <pbonzini@redhat.com>,
 =?utf-8?b?UmFkaW0gS3LEjW3DocWZ?= <rkrcmar@redhat.com>,
 Sean Christopherson <sean.j.christopherson@intel.com>,
 Vitaly Kuznetsov <vkuznets@redhat.com>, Wanpeng Li <wanpengli@tencent.com>,
 Jim Mattson <jmattson@google.com>, Joerg Roedel <joro@8bytes.org>,
 "Rafael J. Wysocki" <rjw@rjwysocki.net>,
 Daniel Lezcano <daniel.lezcano@linaro.org>, linux-pm@vger.kernel.org,
 Boris Ostrovsky <boris.ostrovsky@oracle.com>
Subject: [PATCH v1] cpuidle-haltpoll: vcpu hotplug support
Date: Wed, 28 Aug 2019 19:56:50 +0100
Message-Id: <20190828185650.16923-1-joao.m.martins@oracle.com>
X-Mailer: git-send-email 2.11.0
MIME-Version: 1.0
Content-Type: text/plain; charset=utf-8
X-Proofpoint-Virus-Version: vendor=nai engine=6000 definitions=9363
 signatures=668685
X-Proofpoint-Spam-Details: rule=notspam policy=default score=0 suspectscore=3
 malwarescore=0
 phishscore=0 bulkscore=0 spamscore=0 mlxscore=0 mlxlogscore=992
 adultscore=0 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.0.1-1906280000 definitions=main-1908280184
X-Proofpoint-Virus-Version: vendor=nai engine=6000 definitions=9363
 signatures=668685
X-Proofpoint-Spam-Details: rule=notspam policy=default score=0
 priorityscore=1501 malwarescore=0
 suspectscore=3 phishscore=0 bulkscore=0 spamscore=0 clxscore=1011
 lowpriorityscore=0 mlxscore=0 impostorscore=0 mlxlogscore=999 adultscore=0
 classifier=spam adjust=0 reason=mlx scancount=1 engine=8.0.1-1906280000
 definitions=main-1908280184
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

When cpus != maxcpus cpuidle-haltpoll will fail to register all vcpus
past the online ones and thus fail to register the idle driver.
This is because cpuidle_add_sysfs() will return with -ENODEV as a
consequence from get_cpu_device() return no device for a non-existing
CPU.

Instead switch to cpuidle_register_driver() and manually register each
of the present cpus through cpuhp_setup_state() and future ones that
get onlined. This mimics similar logic as intel_idle.

Fixes: fa86ee90eb11 ("add cpuidle-haltpoll driver")
Signed-off-by: Joao Martins <joao.m.martins@oracle.com>
Signed-off-by: Boris Ostrovsky <boris.ostrovsky@oracle.com>
---
 arch/x86/include/asm/cpuidle_haltpoll.h |  4 +-
 arch/x86/kernel/kvm.c                   | 18 +++----
 drivers/cpuidle/cpuidle-haltpoll.c      | 65 +++++++++++++++++++++++--
 include/linux/cpuidle_haltpoll.h        |  4 +-
 4 files changed, 70 insertions(+), 21 deletions(-)

```
#### [PATCH v3 1/2] KVM: LAPIC: Tune lapic_timer_advance_ns smoothly
##### From: Wanpeng Li <kernellwp@gmail.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 8bit
X-Patchwork-Submitter: Wanpeng Li <kernellwp@gmail.com>
X-Patchwork-Id: 11118167
Return-Path: <SRS0=KojS=WY=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id A696114D5
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 28 Aug 2019 08:19:17 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 8697622CF5
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 28 Aug 2019 08:19:17 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=gmail.com header.i=@gmail.com
 header.b="pWudp200"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726397AbfH1ITI (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 28 Aug 2019 04:19:08 -0400
Received: from mail-pf1-f196.google.com ([209.85.210.196]:35107 "EHLO
        mail-pf1-f196.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726292AbfH1ITI (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 28 Aug 2019 04:19:08 -0400
Received: by mail-pf1-f196.google.com with SMTP id d85so1228853pfd.2;
        Wed, 28 Aug 2019 01:19:08 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=from:to:cc:subject:date:message-id:mime-version
         :content-transfer-encoding;
        bh=W7GKLPAGmCBm9bFk16i6qv/H1D4Ue6Mzr647i7CBlq8=;
        b=pWudp200xJPqLG8gbdZmOS6rC3AjwavyXDrm65Uh0QOIEuGy8SI1wF1eEfhT+GssFA
         nRJVI5i83WwNJ4r56NkhqF/Ieny0DrariGtiaT+yYu2zm5Q7zl6PShX4L0mzHpkIM9XT
         fQokuycnWDeZRJTLORLRPCPp/Ln/71vBoraawn3RVZfbZP+mUp3VIU9QYBL3MQVlBmSY
         mdAlt64YdiycL8cJYGsmzF7S3K662B9wgJrf/m8+xaMgNcPnT4y2I10XksQ6o+CyVBcq
         GwZBeZFZ2zm7+jraFi5t4XXTyrhgSB+iAMu9b4b0pO214BzYh1h0z9zrQEbM29h6GHwT
         qDeA==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:mime-version
         :content-transfer-encoding;
        bh=W7GKLPAGmCBm9bFk16i6qv/H1D4Ue6Mzr647i7CBlq8=;
        b=PM0cGRcON27/5MK7z+iMxN6b8V1VMi+L/tfmi68OmgkDS0YYs3n7+kj7/gOwJayNoh
         oAZagQU4LKSBvQSsfNZH2catZ/rEvicmSVvjFbL1xKLaEhoNkTOzqxNKgIiUtKeME4UF
         qjNYmKffcn8cyrkfbkSFCArEPg8FXJ5bsJoudBuWet1UbIV/NNuedojGIKpXlqAqJNJD
         MHmTDL+yw3rdQ6bCAfuJQpvw4T4kdJPFo3cUuI30skIx2S84J5dnuchSyC33wabbOuLX
         MtmtpIfCgzssYkYvUUWaxYlvAU8xVj2N1M0ctLcUqSzC0oHyfNmhR/YEr/Drhq9WvTrI
         yd8g==
X-Gm-Message-State: APjAAAUKxIxjJpNesuj+W5ybm3z7ajkOYNZl/rVUppGrX980kWStIHGV
        9wP7K79WyVrfaIQORSw+hRSbhmSI
X-Google-Smtp-Source: 
 APXvYqxHwaHzAOj0x1bmSnv3GB4eFOeCcWwCxN0e7YwF2BcgKx54IpxvhYZ9fB+7k8TSxktmU2sy8g==
X-Received: by 2002:a63:3148:: with SMTP id x69mr2244026pgx.300.1566980347471;
        Wed, 28 Aug 2019 01:19:07 -0700 (PDT)
Received: from localhost.localdomain ([203.205.141.123])
        by smtp.googlemail.com with ESMTPSA id
 g1sm1787263pgg.27.2019.08.28.01.19.05
        (version=TLS1_2 cipher=ECDHE-RSA-AES128-SHA bits=128/128);
        Wed, 28 Aug 2019 01:19:07 -0700 (PDT)
From: Wanpeng Li <kernellwp@gmail.com>
X-Google-Original-From: Wanpeng Li <wanpengli@tencent.com>
To: linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Cc: Paolo Bonzini <pbonzini@redhat.com>,
 =?utf-8?b?UmFkaW0gS3LEjW3DocWZ?= <rkrcmar@redhat.com>
Subject: [PATCH v3 1/2] KVM: LAPIC: Tune lapic_timer_advance_ns smoothly
Date: Wed, 28 Aug 2019 16:19:01 +0800
Message-Id: <1566980342-22045-1-git-send-email-wanpengli@tencent.com>
X-Mailer: git-send-email 2.7.4
MIME-Version: 1.0
Content-Type: text/plain; charset=UTF-8
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Wanpeng Li <wanpengli@tencent.com>

Using a moving average based on per-vCPU lapic_timer_advance_ns to tune 
smoothly, filter out drastic fluctuation which prevents this before, 
let's assume it is 10000 cycles.

Cc: Paolo Bonzini <pbonzini@redhat.com>
Cc: Radim Krčmář <rkrcmar@redhat.com>
Signed-off-by: Wanpeng Li <wanpengli@tencent.com>
---
 arch/x86/kvm/lapic.c | 18 ++++++++++++------
 1 file changed, 12 insertions(+), 6 deletions(-)

```
