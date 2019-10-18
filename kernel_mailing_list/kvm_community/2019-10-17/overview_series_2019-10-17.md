#### [PATCH] crypto: ccp - Retry SEV INIT command in case of integrity check failure.
##### From: "Kalra, Ashish" <Ashish.Kalra@amd.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: "Kalra, Ashish" <Ashish.Kalra@amd.com>
X-Patchwork-Id: 11197273
Return-Path: <SRS0=YJ/O=YK=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id BB302912
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 17 Oct 2019 22:35:18 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 8C21B21A4C
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 17 Oct 2019 22:35:18 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=amdcloud.onmicrosoft.com
 header.i=@amdcloud.onmicrosoft.com header.b="C3mvvFnG"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2438308AbfJQWfO (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 17 Oct 2019 18:35:14 -0400
Received: from mail-eopbgr770072.outbound.protection.outlook.com
 ([40.107.77.72]:11598
        "EHLO NAM02-SN1-obe.outbound.protection.outlook.com"
        rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org with ESMTP
        id S1732705AbfJQWfO (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 17 Oct 2019 18:35:14 -0400
ARC-Seal: i=1; a=rsa-sha256; s=arcselector9901; d=microsoft.com; cv=none;
 b=nf261NBMIa7E9oKVYM2TsR/796qIn1LrC/UuGs0nnPcllxjx3w9W6RaUg/EhNLzQ75Hu1avRMJ3ZyN8Jl38WhPyJA5WiZeF5O/6mCP+qDTaF+yr5awLef2OwGnPNNJrL87n3nFxQBHGbh11VHK033p+znbXy3dAoWWCAS1EPbv9Y112hekOXJZgk062uFJnzirxo9P0gphKwhxfk4q7J51H7Gpp3JCBdLiqt5Qk3WECIeHc2QF1hvtwoO8Mu649CA1uv/Rwzdp8rQKbvk5mvphsn1Q2h9xQsH/z2m2hVrPM5IpEDHg4hfoH5FyrrSS+IaFqzazkSp3AY0hwaYnXFZA==
ARC-Message-Signature: i=1; a=rsa-sha256; c=relaxed/relaxed; d=microsoft.com;
 s=arcselector9901;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=lceMN9I1E4Upy+a0YsUY7jbAUM/eE5edwQW28O+Oh/8=;
 b=GxiM/cy9ao5ZQJr6WDY52aygm3VhaEOJQWBF9r8DwkGfjEUf7NF3O93336GzrhA0IGep/W4BA53nfHeM2mcGeJyep0LX3kWF/rPi3dLOAIyUay94ID077GO61dx5YTC0Qe82aKDbIOSeo0+rdlEjDaIcTMNB9C84FxUtg51wS9XZ/LpVkuq6G+0kBUk1w4NoEl93Sj457W3P4lXP6qDS9d6he+ugpvnxOmYqQw35Qj1XB8jjD6ooNMTaPDXa0FXqiRJFVpG7drh+hFoHCl5Qzc/1bia/xA2FX64QbhJ+GFNewYGJ8k1IRkOug6VH+/of4Op1ZM2JnlJSr6iKDwhu1g==
ARC-Authentication-Results: i=1; mx.microsoft.com 1; spf=pass
 smtp.mailfrom=amd.com; dmarc=pass action=none header.from=amd.com; dkim=pass
 header.d=amd.com; arc=none
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
 d=amdcloud.onmicrosoft.com; s=selector2-amdcloud-onmicrosoft-com;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=lceMN9I1E4Upy+a0YsUY7jbAUM/eE5edwQW28O+Oh/8=;
 b=C3mvvFnGuL+LII95Szv4TMdlLy/4R3my8JCJNcAI0TbEcyCGYiot2SRE0N/90mVGndnY3BNY7EtqWGDO18XG4VDUfftS/oJW4copWNC/rhtVblcXAb61o0l3pfwyTi7pStzFBga6G+W1Xs60FtUWCZDBBZ3SNJbGDwksTa7GZfg=
Received: from DM6PR12MB3610.namprd12.prod.outlook.com (20.178.199.84) by
 DM6PR12MB3979.namprd12.prod.outlook.com (10.255.175.12) with Microsoft SMTP
 Server (version=TLS1_2, cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id
 15.20.2347.17; Thu, 17 Oct 2019 22:35:11 +0000
Received: from DM6PR12MB3610.namprd12.prod.outlook.com
 ([fe80::718a:a9ab:540c:7df4]) by DM6PR12MB3610.namprd12.prod.outlook.com
 ([fe80::718a:a9ab:540c:7df4%2]) with mapi id 15.20.2347.023; Thu, 17 Oct 2019
 22:35:11 +0000
From: "Kalra, Ashish" <Ashish.Kalra@amd.com>
To: "Lendacky, Thomas" <Thomas.Lendacky@amd.com>,
        "Hook, Gary" <Gary.Hook@amd.com>,
        "herbert@gondor.apana.org.au" <herbert@gondor.apana.org.au>,
        "davem@davemloft.net" <davem@davemloft.net>,
        "gregkh@linuxfoundation.org" <gregkh@linuxfoundation.org>,
        "tglx@linutronix.de" <tglx@linutronix.de>,
        "allison@lohutok.net" <allison@lohutok.net>,
        "info@metux.net" <info@metux.net>,
        "yamada.masahiro@socionext.com" <yamada.masahiro@socionext.com>,
        "Singh, Brijesh" <brijesh.singh@amd.com>,
        "linux-crypto@vger.kernel.org" <linux-crypto@vger.kernel.org>,
        "linux-kernel@vger.kernel.org" <linux-kernel@vger.kernel.org>,
        "kvm@vger.kernel.org" <kvm@vger.kernel.org>
Subject: [PATCH] crypto: ccp - Retry SEV INIT command in case of integrity
 check failure.
Thread-Topic: [PATCH] crypto: ccp - Retry SEV INIT command in case of
 integrity check failure.
Thread-Index: AQHVhTsiVAXVZvJHqE+F84WTgpVS9A==
Date: Thu, 17 Oct 2019 22:35:11 +0000
Message-ID: <20191017223459.64281-1-Ashish.Kalra@amd.com>
Accept-Language: en-US
Content-Language: en-US
X-MS-Has-Attach: 
X-MS-TNEF-Correlator: 
x-clientproxiedby: SN4PR0601CA0017.namprd06.prod.outlook.com
 (2603:10b6:803:2f::27) To DM6PR12MB3610.namprd12.prod.outlook.com
 (2603:10b6:5:3d::20)
authentication-results: spf=none (sender IP is )
 smtp.mailfrom=Ashish.Kalra@amd.com;
x-ms-exchange-messagesentrepresentingtype: 1
x-mailer: git-send-email 2.17.1
x-originating-ip: [165.204.77.1]
x-ms-publictraffictype: Email
x-ms-office365-filtering-correlation-id: d35d8056-9403-4806-670b-08d753524526
x-ms-office365-filtering-ht: Tenant
x-ms-traffictypediagnostic: DM6PR12MB3979:
x-ms-exchange-transport-forked: True
x-microsoft-antispam-prvs: 
 <DM6PR12MB3979AB7CAEFE4E6FAFC3FE978E6D0@DM6PR12MB3979.namprd12.prod.outlook.com>
x-ms-oob-tlc-oobclassifiers: OLM:2958;
x-forefront-prvs: 01930B2BA8
x-forefront-antispam-report: 
 SFV:NSPM;SFS:(10009020)(4636009)(366004)(346002)(376002)(39860400002)(396003)(136003)(189003)(199004)(102836004)(64756008)(1076003)(1250700005)(2201001)(478600001)(26005)(2906002)(6116002)(6506007)(5660300002)(6436002)(386003)(52116002)(305945005)(6486002)(186003)(66476007)(7736002)(66446008)(36756003)(3846002)(25786009)(14454004)(66066001)(71190400001)(71200400001)(2616005)(486006)(81166006)(66556008)(2501003)(66946007)(8936002)(99286004)(110136005)(6512007)(86362001)(81156014)(50226002)(8676002)(316002)(14444005)(7416002)(256004)(476003)(921003)(1121003);DIR:OUT;SFP:1101;SCL:1;SRVR:DM6PR12MB3979;H:DM6PR12MB3610.namprd12.prod.outlook.com;FPR:;SPF:None;LANG:en;PTR:InfoNoRecords;MX:1;A:1;
received-spf: None (protection.outlook.com: amd.com does not designate
 permitted sender hosts)
x-ms-exchange-senderadcheck: 1
x-microsoft-antispam: BCL:0;
x-microsoft-antispam-message-info: 
 ZiRIJ38AU4dTC04A0RdD8tB01/sEJQQGmByVXEBkOxYPU0JBSHgkpd4rEshN3YHCz4ARFlSOyQ4tgdkHSVdBARghrwZe6dQ6PpQa0VEu2pzb5F6Sn7LbA7oH6vchtX8tVa4R3hWy/+BdXpW2UPB5sAr/HacMlE5WpXGgNFpXpiKKR66dEJSBe/q6O3BFZ4sUuH1lQIkOrxeawcKQI+nh3s+OmS6BCaoF/YedvCuhpOg1o4mP8TGOXbtN8ciHd7f9b5V0j7ooStBJD4cAuuYbBID05Kdb3sxsxX+KeJPKO5MCfg2bQi60PVOBmtnBYsNL40R9euqAyq1MyXCe8o5jFuFhhgT6hF8xadjk3jlhrEbU0Ry/dUG5a10ZIw+6Awh08dVY6OU5lpJ22hgU2ZAnvsVFEXEN7L8El25fUD4OBHA=
MIME-Version: 1.0
X-OriginatorOrg: amd.com
X-MS-Exchange-CrossTenant-Network-Message-Id: 
 d35d8056-9403-4806-670b-08d753524526
X-MS-Exchange-CrossTenant-originalarrivaltime: 17 Oct 2019 22:35:11.1771
 (UTC)
X-MS-Exchange-CrossTenant-fromentityheader: Hosted
X-MS-Exchange-CrossTenant-id: 3dd8961f-e488-4e60-8e11-a82d994e183d
X-MS-Exchange-CrossTenant-mailboxtype: HOSTED
X-MS-Exchange-CrossTenant-userprincipalname: 
 434S2xwEyfwlTTR/6jymePq2fPNjijLM0XAv4zpu5/YQBGulqeur3e2yzMUAbdzyFBET3nfqs+R39gEKmPewsw==
X-MS-Exchange-Transport-CrossTenantHeadersStamped: DM6PR12MB3979
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Ashish Kalra <ashish.kalra@amd.com>

SEV INIT command loads the SEV related persistent data from NVS
and initializes the platform context. The firmware validates the
persistent state. If validation fails, the firmware will reset
the persisent state and return an integrity check failure status.

At this point, a subsequent INIT command should succeed, so retry
the command. The INIT command retry is only done during driver
initialization.

Additional enums along with SEV_RET_SECURE_DATA_INVALID are added
to sev_ret_code to maintain continuity and relevance of enum values.

Signed-off-by: Ashish Kalra <ashish.kalra@amd.com>
---
 drivers/crypto/ccp/psp-dev.c | 12 ++++++++++++
 include/uapi/linux/psp-sev.h |  3 +++
 2 files changed, 15 insertions(+)

```
#### [PATCH RFC 1/3] kcov: remote coverage supportFrom: Andrey Konovalov <andreyknvl@google.com>
##### From: Andrey Konovalov <andreyknvl@google.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Andrey Konovalov <andreyknvl@google.com>
X-Patchwork-Id: 11196507
Return-Path: <SRS0=YJ/O=YK=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 461B9912
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 17 Oct 2019 17:44:47 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 09C6521A49
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 17 Oct 2019 17:44:47 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=google.com header.i=@google.com
 header.b="IMqb/Iqt"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2394602AbfJQRo1 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 17 Oct 2019 13:44:27 -0400
Received: from mail-vs1-f73.google.com ([209.85.217.73]:42913 "EHLO
        mail-vs1-f73.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1727096AbfJQRoY (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 17 Oct 2019 13:44:24 -0400
Received: by mail-vs1-f73.google.com with SMTP id p6so709294vsq.9
        for <kvm@vger.kernel.org>; Thu, 17 Oct 2019 10:44:23 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=date:in-reply-to:message-id:mime-version:references:subject:from:to
         :cc;
        bh=tyumDhI2rfukPZzY0lW4M6LvzfSRQOmNm2Hi9G/GYr4=;
        b=IMqb/Iqts/+eMdyADvzktOc2Fw1pZPjutbX6y8rnj/FS8HJ1kb95eiXX23ZJpcSLo4
         06A9vwAztfE1sGG5CxxtxhCktt6IB41wHM+WW7CGkUOxmoaAkX8Fq9Vl1SpEW3khIwd2
         RpUTIuY9aeJxfGYEgeaqR9VYe5H3llLPi15Mhx2Tn6D40KK0Xge7tafvy0HheRkZ1l3y
         bHve5Hq+zwDzmjN9MfYwJPbX1m3RvMY2VitfiogrsyEUt+XEC86Bw3/5/HZXfwPjwfbj
         crltWV7LPr1k3TRe9HKETgpd2Wl/96mmb9HWgY+8bOabt8ioXv5E71WGUkmDyELPFOwy
         xkIg==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:date:in-reply-to:message-id:mime-version
         :references:subject:from:to:cc;
        bh=tyumDhI2rfukPZzY0lW4M6LvzfSRQOmNm2Hi9G/GYr4=;
        b=NRxmXzkCF/o7pVbFZvS4br1bXUzxozLVjgeyaNNiwN/1fnFVRnvazhd/5KPL7qKejs
         6NzkOJ2py4Nkmcd5HJF6Eg1KTOFRyx8ZJSA5hj8VzIKU18p9ETq2w3z6EjRg4hq8s7ft
         drDT8EaSmSd+vwATQypups4f/URnsDc5XXHf3x7QfCkKScaJS05fEjm2JzmlKD/oJVNt
         XY83ls0nUor3eewgeX5i+o3Lc3zVXZGdY19afpQNA+ubuHDSaMeTAu/OlPJPpy1e0VQf
         SH2dEpr0RN5c1r/uDoeLrZWENqnz9aZk5j9GShIu2uGE6bqv0nERxdtigcfOKe4kK6vC
         gBPQ==
X-Gm-Message-State: APjAAAWZMInBWb6rgJBqhAeyv3MURRYUsO21MtAlqBV0pEXJ8JLDyfNL
        VDa9CRQIoZlt4tApk681ButvZnWaIm7FOOpr
X-Google-Smtp-Source: 
 APXvYqwgmp4bHeG4S2IcfkN+cjFOf0tE6EOWQ6NeZvvVL+LEu55zqRnofR9NTbkajL9pJTxcSlXuJQcHonTMXixj
X-Received: by 2002:a1f:1ad4:: with SMTP id a203mr2734239vka.81.1571334262648;
 Thu, 17 Oct 2019 10:44:22 -0700 (PDT)
Date: Thu, 17 Oct 2019 19:44:13 +0200
In-Reply-To: <cover.1571333592.git.andreyknvl@google.com>
Message-Id: 
 <65fed562d5e6571ece5e3f507ee3701b3f0dd8c9.1571333592.git.andreyknvl@google.com>
Mime-Version: 1.0
References: <cover.1571333592.git.andreyknvl@google.com>
X-Mailer: git-send-email 2.23.0.866.gb869b98d4c-goog
Subject: [PATCH RFC 1/3] kcov: remote coverage support
From: Andrey Konovalov <andreyknvl@google.com>
To: linux-usb@vger.kernel.org, kvm@vger.kernel.org,
        virtualization@lists.linux-foundation.org, netdev@vger.kernel.org,
        linux-kernel@vger.kernel.org, Dmitry Vyukov <dvyukov@google.com>,
        Greg Kroah-Hartman <gregkh@linuxfoundation.org>,
        Alan Stern <stern@rowland.harvard.edu>,
        "Michael S . Tsirkin" <mst@redhat.com>,
        Jason Wang <jasowang@redhat.com>
Cc: Andrew Morton <akpm@linux-foundation.org>,
        Arnd Bergmann <arnd@arndb.de>,
        Steven Rostedt <rostedt@goodmis.org>,
        David Windsor <dwindsor@gmail.com>,
        Elena Reshetova <elena.reshetova@intel.com>,
        Anders Roxell <anders.roxell@linaro.org>,
        Andrey Konovalov <andreyknvl@google.com>
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Currently kcov can only collect coverage for syscalls that are issued
from the current process. This patch adds support for KCOV_REMOTE_ENABLE,
that makes it possible to collect coverage for arbitrary parts of the
kernel code, provided that this part is annotated with kcov_remote_start
and kcov_remote_stop.

This allows to collect coverage from two types of kernel background
threads: the global ones, that are spawned during kernel boot and are
always running (e.g. USB hub_event); and the local ones, that are spawned
when a user interacts with some kernel interfaces (e.g. vhost).

To enable collecting coverage from a global background thread, a unique
global id must be assigned and passed to the corresponding
kcov_remote_start annotation call. Then a userspace process can pass this
id to the KCOV_REMOTE_ENABLE ioctl in the handles array field of the
kcov_remote_arg struct. This will attach kcov device to the code section,
that is referenced by this id. Multiple ids can be targeted with the same
kcov device simultaneously.

Since there might be many local background threads spawned from different
userspace processes, we can't use a single global id per annotation.
Instead, the userspace process passes an id through the common_handle
field of the kcov_remote_arg struct. This id gets saved to the kcov_handle
field in the current task_struct and needs to be passed to the newly
spawned threads via custom annotations. Those threads should be in turn
annotated with kcov_remote_start/kcov_remote_stop.

Signed-off-by: Andrey Konovalov <andreyknvl@google.com>
---
 Documentation/dev-tools/kcov.rst |  99 +++++++
 include/linux/kcov.h             |   9 +
 include/linux/sched.h            |   6 +
 include/uapi/linux/kcov.h        |  11 +
 kernel/kcov.c                    | 434 ++++++++++++++++++++++++++++---
 5 files changed, 524 insertions(+), 35 deletions(-)

```
#### [PATCH V4 1/6] mdev: class id support
##### From: Jason Wang <jasowang@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Jason Wang <jasowang@redhat.com>
X-Patchwork-Id: 11195413
Return-Path: <SRS0=YJ/O=YK=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 92E04112B
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 17 Oct 2019 10:50:10 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 6895C21848
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 17 Oct 2019 10:50:10 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2409032AbfJQKuB (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 17 Oct 2019 06:50:01 -0400
Received: from mx1.redhat.com ([209.132.183.28]:38578 "EHLO mx1.redhat.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S2405514AbfJQKt7 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 17 Oct 2019 06:49:59 -0400
Received: from smtp.corp.redhat.com (int-mx05.intmail.prod.int.phx2.redhat.com
 [10.5.11.15])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mx1.redhat.com (Postfix) with ESMTPS id 734DE302C09E;
        Thu, 17 Oct 2019 10:49:58 +0000 (UTC)
Received: from jason-ThinkPad-X1-Carbon-6th.redhat.com
 (ovpn-12-185.pek2.redhat.com [10.72.12.185])
        by smtp.corp.redhat.com (Postfix) with ESMTP id E3A1E5D70D;
        Thu, 17 Oct 2019 10:49:04 +0000 (UTC)
From: Jason Wang <jasowang@redhat.com>
To: kvm@vger.kernel.org, linux-s390@vger.kernel.org,
        linux-kernel@vger.kernel.org, dri-devel@lists.freedesktop.org,
        intel-gfx@lists.freedesktop.org,
        intel-gvt-dev@lists.freedesktop.org, kwankhede@nvidia.com,
        alex.williamson@redhat.com, mst@redhat.com, tiwei.bie@intel.com
Cc: virtualization@lists.linux-foundation.org, netdev@vger.kernel.org,
        cohuck@redhat.com, maxime.coquelin@redhat.com,
        cunming.liang@intel.com, zhihong.wang@intel.com,
        rob.miller@broadcom.com, xiao.w.wang@intel.com,
        haotian.wang@sifive.com, zhenyuw@linux.intel.com,
        zhi.a.wang@intel.com, jani.nikula@linux.intel.com,
        joonas.lahtinen@linux.intel.com, rodrigo.vivi@intel.com,
        airlied@linux.ie, daniel@ffwll.ch, farman@linux.ibm.com,
        pasic@linux.ibm.com, sebott@linux.ibm.com, oberpar@linux.ibm.com,
        heiko.carstens@de.ibm.com, gor@linux.ibm.com,
        borntraeger@de.ibm.com, akrowiak@linux.ibm.com,
        freude@linux.ibm.com, lingshan.zhu@intel.com, idos@mellanox.com,
        eperezma@redhat.com, lulu@redhat.com, parav@mellanox.com,
        christophe.de.dinechin@gmail.com, kevin.tian@intel.com,
        stefanha@redhat.com, Jason Wang <jasowang@redhat.com>
Subject: [PATCH V4 1/6] mdev: class id support
Date: Thu, 17 Oct 2019 18:48:31 +0800
Message-Id: <20191017104836.32464-2-jasowang@redhat.com>
In-Reply-To: <20191017104836.32464-1-jasowang@redhat.com>
References: <20191017104836.32464-1-jasowang@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.15
X-Greylist: Sender IP whitelisted,
 not delayed by milter-greylist-4.5.16 (mx1.redhat.com [10.5.110.46]);
 Thu, 17 Oct 2019 10:49:58 +0000 (UTC)
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Mdev bus only supports vfio driver right now, so it doesn't implement
match method. But in the future, we may add drivers other than vfio,
the first driver could be virtio-mdev. This means we need to add
device class id support in bus match method to pair the mdev device
and mdev driver correctly.

So this patch adds id_table to mdev_driver and class_id for mdev
device with the match method for mdev bus.

Signed-off-by: Jason Wang <jasowang@redhat.com>
---
 .../driver-api/vfio-mediated-device.rst       |  7 +++++-
 drivers/gpu/drm/i915/gvt/kvmgt.c              |  1 +
 drivers/s390/cio/vfio_ccw_ops.c               |  1 +
 drivers/s390/crypto/vfio_ap_ops.c             |  1 +
 drivers/vfio/mdev/mdev_core.c                 | 18 +++++++++++++++
 drivers/vfio/mdev/mdev_driver.c               | 22 +++++++++++++++++++
 drivers/vfio/mdev/mdev_private.h              |  1 +
 drivers/vfio/mdev/vfio_mdev.c                 |  6 +++++
 include/linux/mdev.h                          |  8 +++++++
 include/linux/mod_devicetable.h               |  8 +++++++
 samples/vfio-mdev/mbochs.c                    |  1 +
 samples/vfio-mdev/mdpy.c                      |  1 +
 samples/vfio-mdev/mtty.c                      |  1 +
 13 files changed, 75 insertions(+), 1 deletion(-)

```
#### [kvm-unit-tests v2 PATCH 1/2] x86: realmode: explicitly copy regs structure
##### From: Bill Wendling <morbo@google.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Bill Wendling <morbo@google.com>
X-Patchwork-Id: 11194615
Return-Path: <SRS0=YJ/O=YK=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id D9EA51575
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 17 Oct 2019 01:25:19 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id B573A21D7A
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 17 Oct 2019 01:25:19 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=google.com header.i=@google.com
 header.b="GLW2gUOk"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2405934AbfJQBZS (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 16 Oct 2019 21:25:18 -0400
Received: from mail-yw1-f74.google.com ([209.85.161.74]:54958 "EHLO
        mail-yw1-f74.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S2405786AbfJQBZS (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 16 Oct 2019 21:25:18 -0400
Received: by mail-yw1-f74.google.com with SMTP id 123so636207ywq.21
        for <kvm@vger.kernel.org>; Wed, 16 Oct 2019 18:25:16 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=date:in-reply-to:message-id:mime-version:references:subject:from:to
         :cc;
        bh=2aXT99zRhARLZKfxO/1NXEG4WuQJvIfJjA9M7hKv2ns=;
        b=GLW2gUOkhgb4Kadhs5jiBl7jfhmtDnHJyD86dUzQh+Wf3Pi9xxA6/RtaDDMiDH6l4/
         N9dFGBxzXLNGH6xF7mO/wZ0NTEeqo490GHTAvRsdyhyUMSTbHgCe84vs+8XG9KaGi9O9
         4I67RAQ9Sjz6QoaXrqpjNXfSFnwZ2UsNMFCehZp9srdxHaM6hQ+g6F6FfHvg7WeaNrUF
         29701FAjEojNtWkKc1oli7VoLmBUlELuK04FbQ+7L97R+QLFjjJXlSpF1B7XA2bjlGkm
         WFoq8D4OsjU+olWCWov9ZV0qMtpmlAS7rGDwBjd118biWDtQvYU6gFIPfA20qwrntOnh
         nD6g==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:date:in-reply-to:message-id:mime-version
         :references:subject:from:to:cc;
        bh=2aXT99zRhARLZKfxO/1NXEG4WuQJvIfJjA9M7hKv2ns=;
        b=aNGdr6KICiaGIz6AM6np2R+cehDp+BUhxydqcsearsxLOGu6rZB2DnbYimt5kWYQln
         cQjpgtezseFiMDZPqdo2wCSAYq7Oy9YadQlCoi8dSzTtOtIwuENky3ZU2YV3Hf3Dy0jj
         9cXm7StisMRZJNMzOlWxbRF+kk7TNR3UU6vZTcCtJgV4PXzfDMHlYY3l8BW/AWo4hMFK
         Hbo0op1/Lk/8P2d7YmFe6Pj0eYNBZYOPRmYyOV/vlCl+Tiim/mBGxtZcRtVhwP+d/IWk
         2jB09pjD1dRZiHXPBcSaqmvKZ/AF5N7lMVfxB7FN0b5sm+h7dsC34KwU5+gYqcsfbkTN
         UXHw==
X-Gm-Message-State: APjAAAV7duFUKr0fxqhvo3M3HjYJk5Wmj1Cy5u52SmrxOV3IdkFbnZ3G
        Fv7LCddp8w3PsfcFaZHURC7bZErArf5Dyc2sIcX/ds35GydxoGcpUUTbRThxYOcTnbIoZ6XPADn
        h0DCMSSgZZtrmgDQadzlwH9uFxx9apPJfHpvVZ9yDm6Pm3iUTzP7BdA==
X-Google-Smtp-Source: 
 APXvYqyEqhxaqDleID8GRQkQIPOau8Dk/yvQpG0AV6j2z47E94b5IXI9WaRyics5JOqi1vepixopZTbf9g==
X-Received: by 2002:a25:72c1:: with SMTP id n184mr491531ybc.388.1571275515804;
 Wed, 16 Oct 2019 18:25:15 -0700 (PDT)
Date: Wed, 16 Oct 2019 18:25:01 -0700
In-Reply-To: <20191017012502.186146-1-morbo@google.com>
Message-Id: <20191017012502.186146-2-morbo@google.com>
Mime-Version: 1.0
References: <20191012235859.238387-1-morbo@google.com>
 <20191017012502.186146-1-morbo@google.com>
X-Mailer: git-send-email 2.23.0.700.g56cf767bdb-goog
Subject: [kvm-unit-tests v2 PATCH 1/2] x86: realmode: explicitly copy regs
 structure
From: Bill Wendling <morbo@google.com>
To: kvm@vger.kernel.org, pbonzini@redhat.com, alexandru.elisei@arm.com,
        thuth@redhat.com
Cc: jmattson@google.com, Bill Wendling <morbo@google.com>
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Clang prefers to use a "rep;movsl" (or equivalent) to copy the "regs"
structure. This doesn't work in 16-bit mode, as it will end up copying
over half the number of bytes. Avoid this by copying over the structure
a byte at a time.

Signed-off-by: Bill Wendling <morbo@google.com>
---
 x86/realmode.c | 17 ++++++++++++++---
 1 file changed, 14 insertions(+), 3 deletions(-)

```
#### [PATCH net 1/2] vsock/virtio: send a credit update when buffer size is changed
##### From: Stefano Garzarella <sgarzare@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Stefano Garzarella <sgarzare@redhat.com>
X-Patchwork-Id: 11195639
Return-Path: <SRS0=YJ/O=YK=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 481C01668
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 17 Oct 2019 12:44:18 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 3058320869
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 17 Oct 2019 12:44:18 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2502488AbfJQMoN (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 17 Oct 2019 08:44:13 -0400
Received: from mx1.redhat.com ([209.132.183.28]:55236 "EHLO mx1.redhat.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S2388531AbfJQMoL (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 17 Oct 2019 08:44:11 -0400
Received: from smtp.corp.redhat.com (int-mx04.intmail.prod.int.phx2.redhat.com
 [10.5.11.14])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mx1.redhat.com (Postfix) with ESMTPS id 1713D300C5A9;
        Thu, 17 Oct 2019 12:44:11 +0000 (UTC)
Received: from steredhat.redhat.com (ovpn-117-195.ams2.redhat.com
 [10.36.117.195])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 9FE075D9CA;
        Thu, 17 Oct 2019 12:44:09 +0000 (UTC)
From: Stefano Garzarella <sgarzare@redhat.com>
To: netdev@vger.kernel.org
Cc: kvm@vger.kernel.org, linux-kernel@vger.kernel.org,
        "David S. Miller" <davem@davemloft.net>,
        Stefan Hajnoczi <stefanha@redhat.com>,
        virtualization@lists.linux-foundation.org
Subject: [PATCH net 1/2] vsock/virtio: send a credit update when buffer size
 is changed
Date: Thu, 17 Oct 2019 14:44:02 +0200
Message-Id: <20191017124403.266242-2-sgarzare@redhat.com>
In-Reply-To: <20191017124403.266242-1-sgarzare@redhat.com>
References: <20191017124403.266242-1-sgarzare@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.14
X-Greylist: Sender IP whitelisted,
 not delayed by milter-greylist-4.5.16 (mx1.redhat.com [10.5.110.45]);
 Thu, 17 Oct 2019 12:44:11 +0000 (UTC)
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

When the user application set a new buffer size value, we should
update the remote peer about this change, since it uses this
information to calculate the credit available.

Signed-off-by: Stefano Garzarella <sgarzare@redhat.com>
---
 net/vmw_vsock/virtio_transport_common.c | 3 +++
 1 file changed, 3 insertions(+)

```
