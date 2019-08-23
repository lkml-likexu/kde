#### [PATCH] i386: Omit all-zeroes entries from KVM CPUID table
##### From: Eduardo Habkost <ehabkost@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Eduardo Habkost <ehabkost@redhat.com>
X-Patchwork-Id: 11110211
Return-Path: <SRS0=oWd0=WS=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id AE86A112C
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 22 Aug 2019 22:52:14 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 95EDA205ED
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 22 Aug 2019 22:52:14 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2405128AbfHVWwN (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 22 Aug 2019 18:52:13 -0400
Received: from mx1.redhat.com ([209.132.183.28]:50230 "EHLO mx1.redhat.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1732657AbfHVWwN (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 22 Aug 2019 18:52:13 -0400
Received: from smtp.corp.redhat.com (int-mx01.intmail.prod.int.phx2.redhat.com
 [10.5.11.11])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mx1.redhat.com (Postfix) with ESMTPS id 173A387633;
        Thu, 22 Aug 2019 22:52:13 +0000 (UTC)
Received: from localhost (ovpn-116-73.gru2.redhat.com [10.97.116.73])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 7D6BB600CD;
        Thu, 22 Aug 2019 22:52:12 +0000 (UTC)
From: Eduardo Habkost <ehabkost@redhat.com>
To: qemu-devel@nongnu.org
Cc: Paolo Bonzini <pbonzini@redhat.com>, kvm@vger.kernel.org,
        Eduardo Habkost <ehabkost@redhat.com>,
        Marcelo Tosatti <mtosatti@redhat.com>,
        Igor Mammedov <imammedo@redhat.com>,
        Richard Henderson <rth@twiddle.net>,
        Yumei Huang <yuhuang@redhat.com>
Subject: [PATCH] i386: Omit all-zeroes entries from KVM CPUID table
Date: Thu, 22 Aug 2019 19:52:10 -0300
Message-Id: <20190822225210.32541-1-ehabkost@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.11
X-Greylist: Sender IP whitelisted,
 not delayed by milter-greylist-4.5.16 (mx1.redhat.com [10.5.110.26]);
 Thu, 22 Aug 2019 22:52:13 +0000 (UTC)
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

KVM has a 80-entry limit at KVM_SET_CPUID2.  With the
introduction of CPUID[0x1F], it is now possible to hit this limit
with unusual CPU configurations, e.g.:

  $ ./x86_64-softmmu/qemu-system-x86_64 \
    -smp 1,dies=2,maxcpus=2 \
    -cpu EPYC,check=off,enforce=off \
    -machine accel=kvm
  qemu-system-x86_64: kvm_init_vcpu failed: Argument list too long

This happens because QEMU adds a lot of all-zeroes CPUID entries
for unused CPUID leaves.  In the example above, we end up
creating 48 all-zeroes CPUID entries.

KVM already returns all-zeroes when emulating the CPUID
instruction if an entry is missing, so the all-zeroes entries are
redundant.  Skip those entries.  This reduces the CPUID table
size by half while keeping CPUID output unchanged.

Reported-by: Yumei Huang <yuhuang@redhat.com>
Fixes: https://bugzilla.redhat.com/show_bug.cgi?id=1741508
Signed-off-by: Eduardo Habkost <ehabkost@redhat.com>
Acked-by: Paolo Bonzini <pbonzini@redhat.com>
---
 target/i386/kvm.c | 14 ++++++++++++++
 1 file changed, 14 insertions(+)

```
#### [PATCH V4 1/3] x86/Hyper-V: Fix definition of struct hv_vp_assist_page
##### From: lantianyu1986@gmail.com

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Tianyu Lan <lantianyu1986@gmail.com>
X-Patchwork-Id: 11109457
Return-Path: <SRS0=oWd0=WS=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 94B9013B1
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 22 Aug 2019 14:30:44 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 72EE123400
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 22 Aug 2019 14:30:44 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=gmail.com header.i=@gmail.com
 header.b="bqTEvUnG"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2388753AbfHVOak (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 22 Aug 2019 10:30:40 -0400
Received: from mail-pl1-f193.google.com ([209.85.214.193]:42535 "EHLO
        mail-pl1-f193.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1732001AbfHVOak (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 22 Aug 2019 10:30:40 -0400
Received: by mail-pl1-f193.google.com with SMTP id y1so3565592plp.9;
        Thu, 22 Aug 2019 07:30:39 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=from:to:cc:subject:date:message-id:in-reply-to:references;
        bh=oI7D6WyA6/0Ot6DL7sm+Im0+wd1osEcKoYF4hLt/A6Q=;
        b=bqTEvUnG9CkxP0I0rRb+w5sdxJLU17GgXMeLehe0ZeJLc1H8Q+A/G63lfshJ7dSmBs
         4QuzgmIPwYM/yc7IJm1Q/tyT7TvUu76f+teotVFE79psBYuRFKjV59gMb9fVnbK3/Lav
         Yugy/a96E6FUTbV55wqOr2NI4vUXMd+FHoa/sdzrQ4E5k2IZiw4Vbxrm72TgaOiqrIxW
         j2kQOyLzNDZ4T8mvNIWwJkFr01XmjHI8ACD8VpJ99URVNWHAxtDsTRealke7jl3RLMNA
         ST5FqTS7Lo8hxUERZMN0+LZX8djDFwjOElp1UyDs3l75RZXCugFq+S5jae5G61u7XKnL
         5pMQ==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:in-reply-to
         :references;
        bh=oI7D6WyA6/0Ot6DL7sm+Im0+wd1osEcKoYF4hLt/A6Q=;
        b=VW37oEMPF/rJlmz4ekRezqVZvylWaGnz4SCnDS0I9k5xxHmmBB2Ayv7xtApWnzzTsK
         AU4YbJ62gm0hSwi0qmKUancqEVQwDwe3ILHMkDYJqtChkywUfCCM587atThm7+V2yCTy
         ZiIsUWYyhwOkYMYgOKlU0dkwhxFxBiRMbrN7s69RyG0N6gipiowwFeXmchC0IAO3kByK
         CkCfikmMnXWxvQv1k0lo+3/UQVpZR1wqaOgWa2Rr3ZxuSkzJGaQF+vYBius5MqixBIOv
         y1VfMP4VtYGt4upNsukrI3PY+WVo3/M62LSJZAn2Bz0v4vi18WMD3nQOGLZb9TdoUVdq
         brrw==
X-Gm-Message-State: APjAAAWhRVgWg5xO4aWKY0ALz6XeTC5ZnjJS3gjDTm3H0wxqb6CK6j8P
        +wGF4dFlMa2tJ1SMgrbSYtA=
X-Google-Smtp-Source: 
 APXvYqx/ED9fclzrzlKYk9uUT7m5f+KXtvtU5E2+5f5yuk7lBLyiPkGogN/krQ53jkucRpYQSLrw3g==
X-Received: by 2002:a17:902:9895:: with SMTP id
 s21mr25242438plp.255.1566484239694;
        Thu, 22 Aug 2019 07:30:39 -0700 (PDT)
Received: from localhost.corp.microsoft.com ([167.220.255.114])
        by smtp.googlemail.com with ESMTPSA id
 r23sm32263161pfg.10.2019.08.22.07.30.34
        (version=TLS1_2 cipher=ECDHE-RSA-CHACHA20-POLY1305 bits=256/256);
        Thu, 22 Aug 2019 07:30:39 -0700 (PDT)
From: lantianyu1986@gmail.com
X-Google-Original-From: Tianyu.Lan@microsoft.com
To: pbonzini@redhat.com, rkrcmar@redhat.com, corbet@lwn.net,
        kys@microsoft.com, haiyangz@microsoft.com, sthemmin@microsoft.com,
        sashal@kernel.org, tglx@linutronix.de, mingo@redhat.com,
        bp@alien8.de, hpa@zytor.com, x86@kernel.org,
        michael.h.kelley@microsoft.com
Cc: Tianyu Lan <Tianyu.Lan@microsoft.com>, kvm@vger.kernel.org,
        linux-doc@vger.kernel.org, linux-kernel@vger.kernel.org,
        linux-hyperv@vger.kernel.org, vkuznets@redhat.com
Subject: [PATCH V4 1/3] x86/Hyper-V: Fix definition of struct
 hv_vp_assist_page
Date: Thu, 22 Aug 2019 22:30:19 +0800
Message-Id: <20190822143021.7518-2-Tianyu.Lan@microsoft.com>
X-Mailer: git-send-email 2.14.5
In-Reply-To: <20190822143021.7518-1-Tianyu.Lan@microsoft.com>
References: <20190822143021.7518-1-Tianyu.Lan@microsoft.com>
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Tianyu Lan <Tianyu.Lan@microsoft.com>

The struct hv_vp_assist_page was defined incorrectly.
The "vtl_control" should be u64[3], "nested_enlightenments
_control" should be a u64 and there are 7 reserved bytes
following "enlighten_vmentry". Fix the definition.

Signed-off-by: Tianyu Lan <Tianyu.Lan@microsoft.com>
---
Change since v3:
	- Update changelog 
Change since v1:
	- Move definition of struct hv_nested_enlightenments_control
       into this patch to fix offset issue.
---
 arch/x86/include/asm/hyperv-tlfs.h | 20 +++++++++++++++-----
 1 file changed, 15 insertions(+), 5 deletions(-)

```
#### [PATCH v5 01/20] KVM: RISC-V: Add KVM_REG_RISCV for ONE_REG interfaceThread-Topic: [PATCH v5 01/20] KVM: RISC-V: Add KVM_REG_RISCV for ONE_REG
##### From: Anup Patel <Anup.Patel@wdc.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Anup Patel <Anup.Patel@wdc.com>
X-Patchwork-Id: 11108759
Return-Path: <SRS0=oWd0=WS=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 48C2B912
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 22 Aug 2019 08:42:39 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 1D31722CE3
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 22 Aug 2019 08:42:39 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=fail reason="signature verification failed" (2048-bit key)
 header.d=wdc.com header.i=@wdc.com header.b="U5fVGGDL";
	dkim=pass (1024-bit key) header.d=sharedspace.onmicrosoft.com
 header.i=@sharedspace.onmicrosoft.com header.b="A9BuANOl"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1732499AbfHVImd (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 22 Aug 2019 04:42:33 -0400
Received: from esa4.hgst.iphmx.com ([216.71.154.42]:23990 "EHLO
        esa4.hgst.iphmx.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1732500AbfHVImc (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 22 Aug 2019 04:42:32 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=simple/simple;
  d=wdc.com; i=@wdc.com; q=dns/txt; s=dkim.wdc.com;
  t=1566463352; x=1597999352;
  h=from:to:cc:subject:date:message-id:references:
   in-reply-to:content-transfer-encoding:mime-version;
  bh=9wly2ZqB8szYB10REO9hVQXoBMbrUmZ3YdQFqShIxWQ=;
  b=U5fVGGDLpKpv135GFUPnpmXaCHfDVuc9IXN0//GQe6vN/Sgi3V/3rVZu
   boW+hdL8sSmjKMZlJyffo+jHim4ibF/OuPSWo2qq3vZYZDSADjr907gBP
   5ThdPsgHpZ1KmkCRBOXVe0PTN5t5PP4bIDOHLtaFkyqE8CMV5VUfSwGDi
   lWcpmziVq+B/RXBd2SXyk2x4a/ovwcuAcDit00Ed4arKlIu6rGNs5mY2o
   WjujCfttOcsV0ih7r5C35L59K5xA+R7Y+otLJoKbsJL3UjlIUqKSXVrYM
   Ydtjrfqkgnn1cVCOzrRYWKumzxkTT6w9EQgWtO8xGs8rzZUNcdxou0Kd8
   w==;
IronPort-SDR: 
 QSr15ROykkQ6HgOv0PrQcuu2UlP7FbfvHDbrg+IefkS/UNwXoIqBNejL1GHo8+hYg4xhzAzPbN
 PTG22Xc/oGMKs43ZEwdm4UbIYoXD3Dc0wfkIhgMEEmARKRxF/h/2WpWw/nqH7TSKPD3c91g3WT
 DK4urRC48Q74KK1FUT1mc8kxtYdvdDKXbp1qDCyfv3yccGjOyaURiGfSH/T6okTuc1MPOIF5ck
 UfAvQnbSNyc9EGLkNytMX06Dsl3w/KFGosfCKkjg4fskT1VwkKTJrK3hPlFvKwEgsCBC+LforF
 v0M=
X-IronPort-AV: E=Sophos;i="5.64,416,1559491200";
   d="scan'208";a="116400162"
Received: from mail-bl2nam02lp2056.outbound.protection.outlook.com (HELO
 NAM02-BL2-obe.outbound.protection.outlook.com) ([104.47.38.56])
  by ob1.hgst.iphmx.com with ESMTP; 22 Aug 2019 16:42:31 +0800
ARC-Seal: i=1; a=rsa-sha256; s=arcselector9901; d=microsoft.com; cv=none;
 b=Fkkr+zDN+l3TO8WQRvrU8f4GIjaI/t3g3REEt5fZhEXE4zV5jr3GOG780+vX+oqZm3aCZlFcqJzCGhUuorfsXvf0oRNaR7aFvUafWdc+loU4vC8Seld4/NuL1CbNhCQQkqvEqVTZFl5h38v5AiwkoP/LmuszyMu1d05YvDFtv76qYEsWugrjjKbFEQuHvUdO9R4ZyEWfgNPfsnqx3pYfU9WlY7FjsOHz5iZrUy5+x4pojmUAm8b6rk5BuwhuyK4jaOLLP9MJ1PfTVZGWZecpORkvRKDbHHHH3M7+JofYm4jh/5blTVB9om7oTBl8usv9QCwPab+3tPdu7Y/irPNxRg==
ARC-Message-Signature: i=1; a=rsa-sha256; c=relaxed/relaxed; d=microsoft.com;
 s=arcselector9901;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=3QIaUtavuVeCoWdfgfjqxFFAzYWV6HZkJPA+thztH6o=;
 b=nHAWFj4g+8c0BnqAZqXb9HFvGGyBvOWb/ypJ9g0RC3OlXLMdqyS04NU1dcQeN/QcsO+7gdaI+erPRDwOnz8vuHz2JwCR2U1Uh9tY5Dm0Tn8LAYVE/WPvgNdaOBHU1AIQEx8aH1crvZ46Nmrj0fba6qrcRLW/anoImAu3GhIWyD76Q7WnU1lKzPJBBn8liNlp+WLoEZ8+FWMeJNQv+/QJDSI9D5+skV1XLDjbm1HKL8+dUAkSYsyANytXkOkIKuRheIJYoCvIEyMk5qr5xGqqraAtX+jrio5dS7rm4yzUdyvGJNxWFylYU16fKajQxhRjzzVRbdgEJOvGznufGX74cg==
ARC-Authentication-Results: i=1; mx.microsoft.com 1; spf=pass
 smtp.mailfrom=wdc.com; dmarc=pass action=none header.from=wdc.com; dkim=pass
 header.d=wdc.com; arc=none
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
 d=sharedspace.onmicrosoft.com; s=selector2-sharedspace-onmicrosoft-com;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=3QIaUtavuVeCoWdfgfjqxFFAzYWV6HZkJPA+thztH6o=;
 b=A9BuANOlt+joTQ/TFtcKCifD42xnA2H46Tts8GleoGjPUIqkav/6TAXn56bIr/MMyBterIsCV/krp8O6Xe6SZdeIGB8eOS/aGVwx6FpJa93riwhi7fTRuCKpPzxpMCNoleDqLXtQCG5RmQjcT1IU05v9JNdxSgBvL359BpevhO0=
Received: from MN2PR04MB6061.namprd04.prod.outlook.com (20.178.246.15) by
 MN2PR04MB7070.namprd04.prod.outlook.com (10.186.146.18) with Microsoft SMTP
 Server (version=TLS1_2, cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id
 15.20.2178.16; Thu, 22 Aug 2019 08:42:30 +0000
Received: from MN2PR04MB6061.namprd04.prod.outlook.com
 ([fe80::a815:e61a:b4aa:60c8]) by MN2PR04MB6061.namprd04.prod.outlook.com
 ([fe80::a815:e61a:b4aa:60c8%7]) with mapi id 15.20.2178.018; Thu, 22 Aug 2019
 08:42:30 +0000
From: Anup Patel <Anup.Patel@wdc.com>
To: Palmer Dabbelt <palmer@sifive.com>,
        Paul Walmsley <paul.walmsley@sifive.com>,
        Paolo Bonzini <pbonzini@redhat.com>,
        Radim K <rkrcmar@redhat.com>
CC: Daniel Lezcano <daniel.lezcano@linaro.org>,
        Thomas Gleixner <tglx@linutronix.de>,
        Atish Patra <Atish.Patra@wdc.com>,
        Alistair Francis <Alistair.Francis@wdc.com>,
        Damien Le Moal <Damien.LeMoal@wdc.com>,
        Christoph Hellwig <hch@infradead.org>,
        Anup Patel <anup@brainfault.org>,
        "kvm@vger.kernel.org" <kvm@vger.kernel.org>,
        "linux-riscv@lists.infradead.org" <linux-riscv@lists.infradead.org>,
        "linux-kernel@vger.kernel.org" <linux-kernel@vger.kernel.org>,
        Anup Patel <Anup.Patel@wdc.com>
Subject: [PATCH v5 01/20] KVM: RISC-V: Add KVM_REG_RISCV for ONE_REG interface
Thread-Topic: [PATCH v5 01/20] KVM: RISC-V: Add KVM_REG_RISCV for ONE_REG
 interface
Thread-Index: AQHVWMWIsBQjRK+t0E6B2vDaDS4FuA==
Date: Thu, 22 Aug 2019 08:42:30 +0000
Message-ID: <20190822084131.114764-2-anup.patel@wdc.com>
References: <20190822084131.114764-1-anup.patel@wdc.com>
In-Reply-To: <20190822084131.114764-1-anup.patel@wdc.com>
Accept-Language: en-US
Content-Language: en-US
X-MS-Has-Attach: 
X-MS-TNEF-Correlator: 
x-clientproxiedby: MA1PR01CA0118.INDPRD01.PROD.OUTLOOK.COM
 (2603:1096:a00:1::34) To MN2PR04MB6061.namprd04.prod.outlook.com
 (2603:10b6:208:d8::15)
authentication-results: spf=none (sender IP is )
 smtp.mailfrom=Anup.Patel@wdc.com;
x-ms-exchange-messagesentrepresentingtype: 1
x-mailer: git-send-email 2.17.1
x-originating-ip: [199.255.44.175]
x-ms-publictraffictype: Email
x-ms-office365-filtering-correlation-id: e25e022e-3c3a-4f01-b5d2-08d726dcaaad
x-ms-office365-filtering-ht: Tenant
x-microsoft-antispam: 
 BCL:0;PCL:0;RULEID:(2390118)(7020095)(4652040)(8989299)(5600166)(711020)(4605104)(1401327)(4618075)(4534185)(4627221)(201703031133081)(201702281549075)(8990200)(2017052603328)(7193020);SRVR:MN2PR04MB7070;
x-ms-traffictypediagnostic: MN2PR04MB7070:
x-ms-exchange-transport-forked: True
x-microsoft-antispam-prvs: 
 <MN2PR04MB7070777C5DECBD768FDB171F8DA50@MN2PR04MB7070.namprd04.prod.outlook.com>
wdcipoutbound: EOP-TRUE
x-ms-oob-tlc-oobclassifiers: OLM:147;
x-forefront-prvs: 01371B902F
x-forefront-antispam-report: 
 SFV:NSPM;SFS:(10019020)(4636009)(366004)(396003)(376002)(136003)(39860400002)(346002)(189003)(199004)(86362001)(25786009)(110136005)(486006)(316002)(52116002)(446003)(54906003)(76176011)(476003)(11346002)(36756003)(14454004)(8676002)(44832011)(6506007)(81166006)(256004)(386003)(2906002)(99286004)(2616005)(66446008)(81156014)(66556008)(64756008)(66476007)(3846002)(6512007)(4326008)(1076003)(305945005)(7736002)(50226002)(66946007)(53936002)(4744005)(186003)(26005)(478600001)(6436002)(102836004)(6486002)(5660300002)(71200400001)(6116002)(8936002)(66066001)(71190400001)(7416002);DIR:OUT;SFP:1102;SCL:1;SRVR:MN2PR04MB7070;H:MN2PR04MB6061.namprd04.prod.outlook.com;FPR:;SPF:None;LANG:en;PTR:InfoNoRecords;MX:1;A:1;
x-ms-exchange-senderadcheck: 1
x-microsoft-antispam-message-info: 
 TY/4wPSjoTlsNHAe/1lsCNKPKBLj9wNKUOYH5V8oN8//tWCcX5dBceE/L/ipi0lxLKpJ2nKHyygOavb/Jipab4rDD59iDcMH0vBT8RWw5xvDPZ4XhGyiSgtpBLSkUKNW5/D0fkvTZid5UDl6MOPmImDPfXtDaTdt1xz8YLPtrntqaLiWlGYWnrdGfiyr2Zc6pQ9824V0XMW5FwZ+TvUVCscyrx55Tpc3aXeYojDlRevJpqYHacqko/rjYBedaHIkOdGzuca4aAKNer8HK7XCNWElUkoeAJ/2wIPYsJgQ12Rt9OErDFd2NAhDmQhmF2rW+uHSTCb16HRj5ng5vvuLHBrNDI3YorUpnvXMtapKeq5D+uh3WCYi8FZvLdvF4OFC1QNwmyv7l64aGe2zVEAS3mO+U63NhG3yLhEVAF06+Lc=
Content-Type: text/plain; charset="iso-8859-1"
MIME-Version: 1.0
X-OriginatorOrg: wdc.com
X-MS-Exchange-CrossTenant-Network-Message-Id: 
 e25e022e-3c3a-4f01-b5d2-08d726dcaaad
X-MS-Exchange-CrossTenant-originalarrivaltime: 22 Aug 2019 08:42:30.2291
 (UTC)
X-MS-Exchange-CrossTenant-fromentityheader: Hosted
X-MS-Exchange-CrossTenant-id: b61c8803-16f3-4c35-9b17-6f65f441df86
X-MS-Exchange-CrossTenant-mailboxtype: HOSTED
X-MS-Exchange-CrossTenant-userprincipalname: 
 uNs1z9u3vpBLupsabeSgZPXV8zwlg8kPLSzOiAt9kjcQfdhd+DS62ebiodZz5zBI+Hz+ck0dB5a9H+oeYNTX4w==
X-MS-Exchange-Transport-CrossTenantHeadersStamped: MN2PR04MB7070
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

We will be using ONE_REG interface accessing VCPU registers from
user-space hence we add KVM_REG_RISCV for RISC-V VCPU registers.

Signed-off-by: Anup Patel <anup.patel@wdc.com>
Acked-by: Paolo Bonzini <pbonzini@redhat.com>
Reviewed-by: Paolo Bonzini <pbonzini@redhat.com>
---
 include/uapi/linux/kvm.h | 1 +
 1 file changed, 1 insertion(+)

```
#### [kvm-unit-tests PATCH] s390x: Add diag308 subcode 0 testing
##### From: Janosch Frank <frankja@linux.ibm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Janosch Frank <frankja@linux.ibm.com>
X-Patchwork-Id: 11109077
Return-Path: <SRS0=oWd0=WS=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id BB2C113B1
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 22 Aug 2019 11:11:20 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id A1E5822CE3
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 22 Aug 2019 11:11:20 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2388084AbfHVLLT (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 22 Aug 2019 07:11:19 -0400
Received: from mx0a-001b2d01.pphosted.com ([148.163.156.1]:23030 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S2388071AbfHVLLT (ORCPT
        <rfc822;kvm@vger.kernel.org>); Thu, 22 Aug 2019 07:11:19 -0400
Received: from pps.filterd (m0098394.ppops.net [127.0.0.1])
        by mx0a-001b2d01.pphosted.com (8.16.0.27/8.16.0.27) with SMTP id
 x7MB8LmL125110
        for <kvm@vger.kernel.org>; Thu, 22 Aug 2019 07:11:17 -0400
Received: from e06smtp04.uk.ibm.com (e06smtp04.uk.ibm.com [195.75.94.100])
        by mx0a-001b2d01.pphosted.com with ESMTP id 2uhqy351nn-1
        (version=TLSv1.2 cipher=AES256-GCM-SHA384 bits=256 verify=NOT)
        for <kvm@vger.kernel.org>; Thu, 22 Aug 2019 07:11:17 -0400
Received: from localhost
        by e06smtp04.uk.ibm.com with IBM ESMTP SMTP Gateway: Authorized Use
 Only! Violators will be prosecuted
        for <kvm@vger.kernel.org> from <frankja@linux.ibm.com>;
        Thu, 22 Aug 2019 12:11:15 +0100
Received: from b06avi18626390.portsmouth.uk.ibm.com (9.149.26.192)
        by e06smtp04.uk.ibm.com (192.168.101.134) with IBM ESMTP SMTP Gateway:
 Authorized Use Only! Violators will be prosecuted;
        (version=TLSv1/SSLv3 cipher=AES256-GCM-SHA384 bits=256/256)
        Thu, 22 Aug 2019 12:11:11 +0100
Received: from d06av25.portsmouth.uk.ibm.com (d06av25.portsmouth.uk.ibm.com
 [9.149.105.61])
        by b06avi18626390.portsmouth.uk.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id x7MBAo9K39911880
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Thu, 22 Aug 2019 11:10:50 GMT
Received: from d06av25.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id B593A11C052;
        Thu, 22 Aug 2019 11:11:10 +0000 (GMT)
Received: from d06av25.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id ED95D11C05C;
        Thu, 22 Aug 2019 11:11:09 +0000 (GMT)
Received: from localhost.localdomain (unknown [9.152.224.131])
        by d06av25.portsmouth.uk.ibm.com (Postfix) with ESMTP;
        Thu, 22 Aug 2019 11:11:09 +0000 (GMT)
From: Janosch Frank <frankja@linux.ibm.com>
To: kvm@vger.kernel.org
Cc: linux-s390@vger.kernel.org, david@redhat.com, thuth@redhat.com
Subject: [kvm-unit-tests PATCH] s390x: Add diag308 subcode 0 testing
Date: Thu, 22 Aug 2019 13:11:00 +0200
X-Mailer: git-send-email 2.17.0
In-Reply-To: <20190821104736.1470-1-frankja@linux.ibm.com>
References: <20190821104736.1470-1-frankja@linux.ibm.com>
X-TM-AS-GCONF: 00
x-cbid: 19082211-0016-0000-0000-000002A174B7
X-IBM-AV-DETECTION: SAVI=unused REMOTE=unused XFE=unused
x-cbparentid: 19082211-0017-0000-0000-00003301AD6B
Message-Id: <20190822111100.4444-1-frankja@linux.ibm.com>
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:,,
 definitions=2019-08-22_07:,,
 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 priorityscore=1501
 malwarescore=0 suspectscore=1 phishscore=0 bulkscore=0 spamscore=0
 clxscore=1015 lowpriorityscore=0 mlxscore=0 impostorscore=0
 mlxlogscore=999 adultscore=0 classifier=spam adjust=0 reason=mlx
 scancount=1 engine=8.0.1-1906280000 definitions=main-1908220120
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

By adding a load reset routine to cstart.S we can also test the clear
reset done by subcode 0, as we now can restore our registers again.

Signed-off-by: Janosch Frank <frankja@linux.ibm.com>
---
I managed to extract this from another bigger test, so let's add it to the bunch.
I'd be very happy about assembly review :-)
---
 s390x/cstart64.S | 27 +++++++++++++++++++++++++++
 s390x/diag308.c  | 31 ++++++++++---------------------
 2 files changed, 37 insertions(+), 21 deletions(-)

```
#### [PATCH v2] arm64: KVM: Only skip MMIO insn once
##### From: Andrew Jones <drjones@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Andrew Jones <drjones@redhat.com>
X-Patchwork-Id: 11109063
Return-Path: <SRS0=oWd0=WS=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id B62BB13B1
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 22 Aug 2019 11:03:09 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 9491B233A0
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 22 Aug 2019 11:03:09 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1731403AbfHVLDI (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 22 Aug 2019 07:03:08 -0400
Received: from mx1.redhat.com ([209.132.183.28]:51934 "EHLO mx1.redhat.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1729922AbfHVLDI (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 22 Aug 2019 07:03:08 -0400
Received: from smtp.corp.redhat.com (int-mx02.intmail.prod.int.phx2.redhat.com
 [10.5.11.12])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mx1.redhat.com (Postfix) with ESMTPS id 6BA6A3082128;
        Thu, 22 Aug 2019 11:03:08 +0000 (UTC)
Received: from kamzik.brq.redhat.com (unknown [10.43.2.160])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 4199160CCD;
        Thu, 22 Aug 2019 11:03:07 +0000 (UTC)
From: Andrew Jones <drjones@redhat.com>
To: kvmarm@lists.cs.columbia.edu, kvm@vger.kernel.org
Cc: maz@kernel.org, mark.rutland@arm.com
Subject: [PATCH v2] arm64: KVM: Only skip MMIO insn once
Date: Thu, 22 Aug 2019 13:03:05 +0200
Message-Id: <20190822110305.18035-1-drjones@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.12
X-Greylist: Sender IP whitelisted,
 not delayed by milter-greylist-4.5.16 (mx1.redhat.com [10.5.110.42]);
 Thu, 22 Aug 2019 11:03:08 +0000 (UTC)
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

If after an MMIO exit to userspace a VCPU is immediately run with an
immediate_exit request, such as when a signal is delivered or an MMIO
emulation completion is needed, then the VCPU completes the MMIO
emulation and immediately returns to userspace. As the exit_reason
does not get changed from KVM_EXIT_MMIO in these cases we have to
be careful not to complete the MMIO emulation again, when the VCPU is
eventually run again, because the emulation does an instruction skip
(and doing too many skips would be a waste of guest code :-) We need
to use additional VCPU state to track if the emulation is complete.
As luck would have it, we already have 'mmio_needed', which even
appears to be used in this way by other architectures already.

Fixes: 0d640732dbeb ("arm64: KVM: Skip MMIO insn after emulation")
Signed-off-by: Andrew Jones <drjones@redhat.com>
Acked-by: Mark Rutland <mark.rutland@arm.com>
---
v2: move mmio_needed use closer to other mmio state use [maz]

 virt/kvm/arm/mmio.c | 7 +++++++
 1 file changed, 7 insertions(+)

```
#### [PATCH v3] vfio_pci: Restore original state on release
##### From: hexin <hexin.op@gmail.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: hexin <hexin.op@gmail.com>
X-Patchwork-Id: 11108377
Return-Path: <SRS0=oWd0=WS=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id EBF2B1398
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 22 Aug 2019 03:35:31 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id CA87E20856
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 22 Aug 2019 03:35:31 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=gmail.com header.i=@gmail.com
 header.b="mRigY60/"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1730172AbfHVDf1 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 21 Aug 2019 23:35:27 -0400
Received: from mail-wm1-f66.google.com ([209.85.128.66]:38823 "EHLO
        mail-wm1-f66.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1728332AbfHVDf1 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 21 Aug 2019 23:35:27 -0400
Received: by mail-wm1-f66.google.com with SMTP id m125so4187240wmm.3;
        Wed, 21 Aug 2019 20:35:25 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=from:to:cc:subject:date:message-id;
        bh=WsaYFeAkte2NretrOo8yB7eLtn2MeRH7ZtBbeHqK9ss=;
        b=mRigY60/acd7r9AbKb68l4BZVAfI6iTkq9tIoOCP/NzynKBOPNFtBnMgl88G3vKpv9
         4nbLjfEHxDEUn+KlYQfPXsu/23xyYA8DfzDkwoT0ssJWXao7V6c1pvw7hol3oKDUdNEQ
         lJLMOh2e7VXr5Tvep4FUu9ywmFnwGShlGQ7RybJqG+Ey6Ff1b7AqseT0+MqEtDudQHTo
         HediKQtaQUxtLainWjPbEz7dUfZPht5bp8BB3FRsUN6cgUer1mD35+igZNtL+iZLlbAC
         DEGVfj5bYxoghKLBjDbg0HMmJKas/B+ZMu+cPtjgLzWgZaQVrqVHIycJstWAUJT4Vd9z
         6V8A==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id;
        bh=WsaYFeAkte2NretrOo8yB7eLtn2MeRH7ZtBbeHqK9ss=;
        b=KXW9d8SJejRgTsTIrJZGHVIdm5bed49HCRmXeJwYn8D2rkgAZMlR+wkdGNWx2E8Y57
         sHDirt0El6N+kJPSsZj+vq+laPt9mMJYfYGQL0e5UH974p5jTn1jdysxb5V49ky1UpU/
         bHNR2vMMV4ORr0Zxdb436a9GX3e32miYs+nTpALv/B0u6u1/wdExRXvEwjNaL+X5HQZV
         IhhAACheuMLsbiMf9rSGvsKqKNSmVar5kgXESzoPsUGCiWCsrUMR5VsUNrP1ovjSXgSh
         Yn8rS5ysRUJ9JxYrgwF12lT6j9tjjASgl0WzWHLPP3B02gU64486erDM8ocsXcO9kFD9
         f3Sw==
X-Gm-Message-State: APjAAAUtgtQL3gcgK7Bo6iDiq+BJeZPq6FmRGMroQHAOlj90bmH2TgFb
        zCvC7YDYjkehtIh/aecwUlw=
X-Google-Smtp-Source: 
 APXvYqxpplXAscH90uc7IVjMnTI5K8IsuLoHO6ctq9wYYw2C2y4eh3XV0YiP0nw2niEWn1ZjB0odjw==
X-Received: by 2002:a1c:d108:: with SMTP id i8mr3609222wmg.28.1566444924948;
        Wed, 21 Aug 2019 20:35:24 -0700 (PDT)
Received: from localhost ([165.22.121.176])
        by smtp.gmail.com with ESMTPSA id
 o11sm17971037wrw.19.2019.08.21.20.35.24
        (version=TLS1_2 cipher=ECDHE-RSA-AES128-GCM-SHA256 bits=128/128);
        Wed, 21 Aug 2019 20:35:24 -0700 (PDT)
From: hexin <hexin.op@gmail.com>
X-Google-Original-From: hexin <hexin15@baidu.com>
To: Alex Williamson <alex.williamson@redhat.com>, kvm@vger.kernel.org,
        linux-pci@vger.kernel.org, linux-kernel@vger.kernel.org
Cc: hexin <hexin15@baidu.com>, Liu Qi <liuqi16@baidu.com>,
        Zhang Yu <zhangyu31@baidu.com>
Subject: [PATCH v3] vfio_pci: Restore original state on release
Date: Thu, 22 Aug 2019 11:35:19 +0800
Message-Id: <1566444919-3331-1-git-send-email-hexin15@baidu.com>
X-Mailer: git-send-email 1.8.3.1
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

vfio_pci_enable() saves the device's initial configuration information
with the intent that it is restored in vfio_pci_disable().  However,
the commit referenced in Fixes: below replaced the call to
__pci_reset_function_locked(), which is not wrapped in a state save
and restore, with pci_try_reset_function(), which overwrites the
restored device state with the current state before applying it to the
device.  Reinstate use of __pci_reset_function_locked() to return to
the desired behavior.

Fixes: 890ed578df82 ("vfio-pci: Use pci "try" reset interface")
Signed-off-by: hexin <hexin15@baidu.com>
Signed-off-by: Liu Qi <liuqi16@baidu.com>
Signed-off-by: Zhang Yu <zhangyu31@baidu.com>
---
v2->v3:
- change commit log 
v1->v2:
- add fixes tag
- add comment to warn 

[1] https://lore.kernel.org/linux-pci/1565926427-21675-1-git-send-email-hexin15@baidu.com
[2] https://lore.kernel.org/linux-pci/1566042663-16694-1-git-send-email-hexin15@baidu.com

 drivers/vfio/pci/vfio_pci.c | 17 +++++++++++++----
 1 file changed, 13 insertions(+), 4 deletions(-)

```
#### [PATCH] x86/retpoline: Don't clobber RFLAGS during CALL_NOSPEC on i386
##### From: Sean Christopherson <sean.j.christopherson@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Sean Christopherson <sean.j.christopherson@intel.com>
X-Patchwork-Id: 11110125
Return-Path: <SRS0=oWd0=WS=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 317F8112C
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 22 Aug 2019 21:11:34 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 19E3123401
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 22 Aug 2019 21:11:34 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2388778AbfHVVLa (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 22 Aug 2019 17:11:30 -0400
Received: from mga07.intel.com ([134.134.136.100]:61963 "EHLO mga07.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1730991AbfHVVL3 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 22 Aug 2019 17:11:29 -0400
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from fmsmga003.fm.intel.com ([10.253.24.29])
  by orsmga105.jf.intel.com with ESMTP/TLS/DHE-RSA-AES256-GCM-SHA384;
 22 Aug 2019 14:11:29 -0700
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.64,418,1559545200";
   d="scan'208";a="186688734"
Received: from sjchrist-coffee.jf.intel.com ([10.54.74.41])
  by FMSMGA003.fm.intel.com with ESMTP; 22 Aug 2019 14:11:28 -0700
From: Sean Christopherson <sean.j.christopherson@intel.com>
To: Thomas Gleixner <tglx@linutronix.de>,
        Ingo Molnar <mingo@redhat.com>, Borislav Petkov <bp@alien8.de>,
        x86@kernel.org
Cc: "H. Peter Anvin" <hpa@zytor.com>, linux-kernel@vger.kernel.org,
        Peter Zijlstra <peterz@infradead.org>,
        Paolo Bonzini <pbonzini@redhat.com>, kvm@vger.kernel.org
Subject: [PATCH] x86/retpoline: Don't clobber RFLAGS during CALL_NOSPEC on
 i386
Date: Thu, 22 Aug 2019 14:11:22 -0700
Message-Id: <20190822211122.27579-1-sean.j.christopherson@intel.com>
X-Mailer: git-send-email 2.22.0
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Use 'lea' instead of 'add' when adjusting %rsp in CALL_NOSPEC so as to
avoid clobbering flags.

KVM's emulator makes indirect calls into a jump table of sorts, where
the destination of the CALL_NOSPEC is a small blob of code that performs
fast emulation by executing the target instruction with fixed operands.

  adcb_al_dl:
     0x000339f8 <+0>:   adc    %dl,%al
     0x000339fa <+2>:   ret

A major motiviation for doing fast emulation is to leverage the CPU to
handle consumption and manipulation of arithmetic flags, i.e. RFLAGS is
both an input and output to the target of CALL_NOSPEC.  Clobbering flags
results in all sorts of incorrect emulation, e.g. Jcc instructions often
take the wrong path.  Sans the nops...

  asm("push %[flags]; popf; " CALL_NOSPEC " ; pushf; pop %[flags]\n"
     0x0003595a <+58>:  mov    0xc0(%ebx),%eax
     0x00035960 <+64>:  mov    0x60(%ebx),%edx
     0x00035963 <+67>:  mov    0x90(%ebx),%ecx
     0x00035969 <+73>:  push   %edi
     0x0003596a <+74>:  popf
     0x0003596b <+75>:  call   *%esi
     0x000359a0 <+128>: pushf
     0x000359a1 <+129>: pop    %edi
     0x000359a2 <+130>: mov    %eax,0xc0(%ebx)
     0x000359b1 <+145>: mov    %edx,0x60(%ebx)

  ctxt->eflags = (ctxt->eflags & ~EFLAGS_MASK) | (flags & EFLAGS_MASK);
     0x000359a8 <+136>: mov    -0x10(%ebp),%eax
     0x000359ab <+139>: and    $0x8d5,%edi
     0x000359b4 <+148>: and    $0xfffff72a,%eax
     0x000359b9 <+153>: or     %eax,%edi
     0x000359bd <+157>: mov    %edi,0x4(%ebx)

For the most part this has gone unnoticed as emulation of guest code
that can trigger fast emulation is effectively limited to MMIO when
running on modern hardware, and MMIO is rarely, if ever, accessed by
instructions that affect or consume flags.

Breakage is almost instantaneous when running with unrestricted guest
disabled, in which case KVM must emulate all instructions when the guest
has invalid state, e.g. when the guest is in Big Real Mode during early
BIOS.

Cc: Peter Zijlstra <peterz@infradead.org>
Cc: Paolo Bonzini <pbonzini@redhat.com>
Cc: <kvm@vger.kernel.org>
Cc: <stable@vger.kernel.org>
Fixes: 1a29b5b7f347a ("KVM: x86: Make indirect calls in emulator speculation safe")
Signed-off-by: Sean Christopherson <sean.j.christopherson@intel.com>
---
 arch/x86/include/asm/nospec-branch.h | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
